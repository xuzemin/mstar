//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////
// This file is commonly used by bootloader code and system(main) code.
// Must be backward compatible with previously released version of bootloader code.
////////////////////////////////////////////////////////////////////////////////////////////

#define MSAPI_BOOTLOADER_C

/******************************************************************************/
/*                              Header Files                                  */
/******************************************************************************/
// C Library
#include <stdio.h>

// Global Layer
#include "sysinfo.h"

// Driver Layer
#include "hwreg.h"
#include "SysInit.h"
#include "drvSERFLASH.h"
#include "drvpower_if.h"

// API Layer
#include "msAPI_Ram.h"
#include "msAPI_Bootloader.h"
#include "msFlash.h"
#include "msAPI_Flash.h"
#include "msAPI_FreqTableCommon.h"
//#include "msAPI_DTVSystem.h"

// Image
#include "imginfo.h"
#include "BinInfo.h"
//APP
#include "MApp_SaveData.h"

// Device
#include "GPIO.h"

#define ISP_UPDATE              ( (MAGIC_IMAGE_END >> 24) & 0xFF) // Must not be 0
#define NON_ISP_UPDATE          0x00        // Do not choose 0xFF because it is programmed to flash without flash erasure.

extern U32 u32ImgInfoOffset;

U8 code u8Dummy;
/******************************************************************************/
/*                                 Macro                                      */
/******************************************************************************/
#define BL_DBG(x)   //x
#define BOOTLOADER_ASSERT(x)  x

#define MEMBER_OFFSET(struct_name, member_name) ( (U32) &(((struct_name *)0)->member_name) )                        // 16-bit Offset
#define EEPROM_OFFSET(member_name)              (RM_ADDR_DOWNLOAD+MEMBER_OFFSET(ST_DOWNLOAD_INFO, member_name))     // ST_DOWNLOAD_INFO member offset on EEPROM

/******************************************************************************/
/*                          Local Variables                                   */
/******************************************************************************/
#if 0 // only for test
static U8 _u8BootupDownloadType = (U8)DOWNLOAD_TYPE_OAD_USER; //(U8)DOWNLOAD_TYPE_NONE;
#endif

/******************************************************************************/
/*                          Local Functions                                   */
/******************************************************************************/
 // Get flash position of the second magic number (end magic number)
// Return 0 if error
static U32 GetFlashPosOf2ndMagicNo(void)
{
    U16         u16PackCount;
    U32         u32FlashOffset;
    BININFO   Fmt;

    u32FlashOffset = u32ImgInfoOffset + BOOTLOADER_CODE_SIZE + MEMBER_OFFSET(MS_IMG_INFO, u16PackInfoFlashBankNo);
    MDrv_FLASH_Read(u32FlashOffset, 4, (U8 *)&u32FlashOffset);
    u32FlashOffset += BOOTLOADER_CODE_SIZE;
    BL_DBG(printf("App image info addr: 0x%LX\n", u32FlashOffset));

    // Get the total bin count in the pack header
    MDrv_FLASH_Read(u32FlashOffset, 2, (U8 *)&u16PackCount);
    if (u16PackCount > 0)
    {
        MDrv_FLASH_Read(u32FlashOffset+2 + ((u16PackCount-1) * sizeof(BININFO)), sizeof(BININFO), (U8 *)&Fmt);

        if ( Fmt.B_ID == BIN_ID_MAGIC_55AAABCD )
        {
            u32FlashOffset = Fmt.B_FAddr + BOOTLOADER_CODE_SIZE;
            BL_DBG(printf("Flash pos: 0x%LX\n", u32FlashOffset));
            return u32FlashOffset;
        }
        else
        {
            BL_DBG(printf("Invalid Bin ID\n"));
        }
    }
    else
    {
        BL_DBG(printf("Pack count=0\n"));
    }

    return 0;
}

/******************************************************************************/
/*                          Global Functions                                  */
/******************************************************************************/


// Need select FLASH_ID1 or FLASH_ID2 before calling this subroutine
BOOLEAN msAPI_BLoader_ClearIspUpdate(void)
{
    U8   u8UpdateType;
    U32  u32FlashOffset;
    BOOLEAN bReturnValue;

    bReturnValue = TRUE;
    u32FlashOffset = GetFlashPosOf2ndMagicNo();
    u8UpdateType = NON_ISP_UPDATE;

    msAPI_Flash_Set_WriteProtect( DISABLE );
    if ( !msAPI_Flash_Write( u32FlashOffset, 1, &u8UpdateType ) )
    {
        BL_DBG (printf("Failed to clear ISP update\n"));
        bReturnValue = FALSE;
    }

    //MDrv_FLASH_WriteProtect(ENABLE);
    msAPI_Flash_Set_WriteProtect(ENABLE);

    return bReturnValue;
}

// Need select FLASH_ID1 or FLASH_ID2 before calling this subroutine
BOOLEAN msAPI_BLoader_IsIspUpdate(void)
{
    U8      u8UpdateType;
    U32     u32FlashOffset;

    u32FlashOffset = GetFlashPosOf2ndMagicNo();
    MDrv_FLASH_Read(u32FlashOffset, 1, (U8 *)&u8UpdateType);

    if (u8UpdateType == ISP_UPDATE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/******************************************************************************/
/// API to do whole-chip reset to run bootloader
/// Use watchdog reset to do whole-chip reset
/******************************************************************************/
void msAPI_BLoader_Reboot(void)
{
    //MDrv_MIU_SPI_SetOffset(0LU);

    #if 0
    MDrv_Sys_SetWatchDogTimer(0);
    MDrv_Sys_EnableWatchDog();
    while(1);   // Necessary because of using watch dog reset
    #else
    MDrv_Sys_WholeChipReset();
    #endif
}

#ifdef TWO_AP_IN_FLASH_TWO_4MB
BOOLEAN msAPI_BLoader_CheckIntegrity3()
{
    U32         u32Value;
    U32         u32FlashOffset;
    U16         u16PackCount;
    BININFO   Fmt;
    U8 apSelect=0;
    U8 ap1Ok=0;
    U8 ap2Ok=0;
    U8 ap1IsFromIsp=0;





    //AP1
     // Read system code magic number
    msAPI_Flash_ChipSelect((EN_FLASH_ID)0);
    u32FlashOffset =  u32ImgInfoOffset +BOOTLOADER_CODE_SIZE + MEMBER_OFFSET(MS_IMG_INFO, u32Magic);
    MDrv_FLASH_Read(u32FlashOffset, 4, (U8 *)&u32Value);

    // Check system code magic number
    if (u32Value == MAGIC_APP)
    {
        u32FlashOffset = u32ImgInfoOffset + BOOTLOADER_CODE_SIZE + MEMBER_OFFSET(MS_IMG_INFO, u16PackInfoFlashBankNo);
        MDrv_FLASH_Read(u32FlashOffset, 4, (U8 *)&u32FlashOffset);
        u32FlashOffset += BOOTLOADER_CODE_SIZE;
        BL_DBG(printf("System image pack info addr: 0x%LX\n", u32FlashOffset));

        // Get the total count in the pack header
        MDrv_FLASH_Read(u32FlashOffset, 2, (U8 *)&u16PackCount);
        if (u16PackCount > 0)
        {
            MDrv_FLASH_Read(u32FlashOffset+2 + ((u16PackCount-1) * sizeof(BININFO)), sizeof(BININFO), (U8 *)&Fmt);
            if ( Fmt.B_ID == BIN_ID_MAGIC_55AAABCD )
            {
                u32FlashOffset = Fmt.B_FAddr + BOOTLOADER_CODE_SIZE;
                // Read image end magic number
                MDrv_FLASH_Read(u32FlashOffset, 4, (U8 *)&u32Value);
                // Check image end magic number
                if (u32Value == MAGIC_IMAGE_END)
                {
                      ap1Ok=1;
                      ap1IsFromIsp=1;
                      printf("AP1:OK  from ISP\n");
                }
                else if (u32Value == (MAGIC_IMAGE_END&0x00ffffff))
                {
                      ap1Ok=1;
                      ap1IsFromIsp=0;
                      printf("AP1:OK\n");
                }
            }
        }
      }


     //AP2
     // Read system code magic number
     msAPI_Flash_ChipSelect((EN_FLASH_ID)1);
    u32FlashOffset =  u32ImgInfoOffset +BOOTLOADER_CODE_SIZE + MEMBER_OFFSET(MS_IMG_INFO, u32Magic);
    MDrv_FLASH_Read(u32FlashOffset, 4, (U8 *)&u32Value);

    // Check system code magic number
    if (u32Value == MAGIC_APP)
    {
        u32FlashOffset = u32ImgInfoOffset + BOOTLOADER_CODE_SIZE + MEMBER_OFFSET(MS_IMG_INFO, u16PackInfoFlashBankNo);
        MDrv_FLASH_Read(u32FlashOffset, 4, (U8 *)&u32FlashOffset);
        u32FlashOffset += BOOTLOADER_CODE_SIZE;
        BL_DBG(printf("System image pack info addr: 0x%LX\n", u32FlashOffset));
        // Get the total count in the pack header
        MDrv_FLASH_Read(u32FlashOffset, 2, (U8 *)&u16PackCount);
        if (u16PackCount > 0)
        {
            MDrv_FLASH_Read(u32FlashOffset+2 + ((u16PackCount-1) * sizeof(BININFO)), sizeof(BININFO), (U8 *)&Fmt);
            if ( Fmt.B_ID == BIN_ID_MAGIC_55AAABCD )
            {
                u32FlashOffset = Fmt.B_FAddr + BOOTLOADER_CODE_SIZE;
                // Read image end magic number
                MDrv_FLASH_Read(u32FlashOffset, 4, (U8 *)&u32Value);
                // Check image end magic number
                if (u32Value == MAGIC_IMAGE_END)
                {
                      ap2Ok=1;
                      printf("AP2:OK\n");
                }
            }
        }
      }


      apSelect = msAPI_rmReadByte(EEPROM_OFFSET(u8DL_DefaultAPSelection));
      printf("AP select: %bd\n",apSelect);

      if(ap1IsFromIsp)
      {
          msAPI_BLoader_ClearIspUpdate();

          printf("run ISP updated firmware!\n");
          if(apSelect==2)
              msAPI_rmWriteByte(EEPROM_OFFSET(u8DL_DefaultAPSelection),1);
          msAPI_Flash_ChipSelect((EN_FLASH_ID)0);
          return TRUE;
      }


      if(apSelect==1)
      {
          if(ap1Ok)
         {
            printf("go AP1\n");
            msAPI_Flash_ChipSelect((EN_FLASH_ID)0);
            return TRUE;
         }
      }

      else if(apSelect==2)
      {
          if(ap2Ok)
         {
            printf("go AP2\n");
            msAPI_Flash_ChipSelect((EN_FLASH_ID)1);
            return TRUE;
         }
      }


      {
         if(ap1Ok)
         {
            msAPI_rmWriteByte(EEPROM_OFFSET(u8DL_DefaultAPSelection),1);
            apSelect = msAPI_rmReadByte(EEPROM_OFFSET(u8DL_DefaultAPSelection));
            printf("comfirm AP select: %bd\n",apSelect);
            msAPI_Flash_ChipSelect((EN_FLASH_ID)0);
            return TRUE;
         }
         else if(ap2Ok)
         {
            msAPI_rmWriteByte(EEPROM_OFFSET(u8DL_DefaultAPSelection),2);
            apSelect = msAPI_rmReadByte(EEPROM_OFFSET(u8DL_DefaultAPSelection));
            printf("comfirm AP select: %bd\n",apSelect);
            msAPI_Flash_ChipSelect((EN_FLASH_ID)1);
            return TRUE;
         }

      }


      msAPI_Flash_ChipSelect((EN_FLASH_ID)0);
      printf("NO AP OK!\n");
      return FALSE;

}
#endif



#ifdef TWO_AP_IN_FLASH_ONE_8MB
BOOLEAN msAPI_BLoader_CheckIntegrity2(U32* startAddr)
{
    U32         u32Value;
    U32         u32FlashOffset;
    U16         u16PackCount;
    BININFO   Fmt;
    U32 ap2BaseOffset=SIZE_4MB;
    U8 apSelect=0;
    U8 ap1Ok=0;
    U8 ap2Ok=0;


    //AP1
     // Read system code magic number
    u32FlashOffset =  u32ImgInfoOffset +BOOTLOADER_CODE_SIZE + MEMBER_OFFSET(MS_IMG_INFO, u32Magic);
    MDrv_FLASH_Read(u32FlashOffset, 4, (U8 *)&u32Value);

    // Check system code magic number
    if (u32Value == MAGIC_APP)
    {
        u32FlashOffset = u32ImgInfoOffset + BOOTLOADER_CODE_SIZE + MEMBER_OFFSET(MS_IMG_INFO, u16PackInfoFlashBankNo);
        MDrv_FLASH_Read(u32FlashOffset, 4, (U8 *)&u32FlashOffset);
        u32FlashOffset += BOOTLOADER_CODE_SIZE;
        BL_DBG(printf("System image pack info addr: 0x%LX\n", u32FlashOffset));

        // Get the total count in the pack header
        MDrv_FLASH_Read(u32FlashOffset, 2, (U8 *)&u16PackCount);
        if (u16PackCount > 0)
        {
            MDrv_FLASH_Read(u32FlashOffset+2 + ((u16PackCount-1) * sizeof(BININFO)), sizeof(BININFO), (U8 *)&Fmt);
            if ( Fmt.B_ID == BIN_ID_MAGIC_55AAABCD )
            {
                u32FlashOffset = Fmt.B_FAddr + BOOTLOADER_CODE_SIZE;
                // Read image end magic number
                MDrv_FLASH_Read(u32FlashOffset, 4, (U8 *)&u32Value);
                // Check image end magic number
                if (u32Value == MAGIC_IMAGE_END)
                {
                      ap1Ok=1;
                      printf("AP1:OK\n");
                }
            }
        }
      }


     //AP2
     // Read system code magic number
    u32FlashOffset =  ap2BaseOffset+u32ImgInfoOffset +BOOTLOADER_CODE_SIZE + MEMBER_OFFSET(MS_IMG_INFO, u32Magic);
    MDrv_FLASH_Read(u32FlashOffset, 4, (U8 *)&u32Value);

    // Check system code magic number
    if (u32Value == MAGIC_APP)
    {
        u32FlashOffset = ap2BaseOffset+u32ImgInfoOffset + BOOTLOADER_CODE_SIZE + MEMBER_OFFSET(MS_IMG_INFO, u16PackInfoFlashBankNo);
        MDrv_FLASH_Read(u32FlashOffset, 4, (U8 *)&u32FlashOffset);
        u32FlashOffset += BOOTLOADER_CODE_SIZE;
        BL_DBG(printf("System image pack info addr: 0x%LX\n", u32FlashOffset));
        // Get the total count in the pack header
        MDrv_FLASH_Read(ap2BaseOffset+u32FlashOffset, 2, (U8 *)&u16PackCount);
        if (u16PackCount > 0)
        {
            MDrv_FLASH_Read(ap2BaseOffset+u32FlashOffset+2 + ((u16PackCount-1) * sizeof(BININFO)), sizeof(BININFO), (U8 *)&Fmt);
            if ( Fmt.B_ID == BIN_ID_MAGIC_55AAABCD )
            {
                u32FlashOffset = ap2BaseOffset+Fmt.B_FAddr + BOOTLOADER_CODE_SIZE;
                // Read image end magic number
                MDrv_FLASH_Read(u32FlashOffset, 4, (U8 *)&u32Value);
                // Check image end magic number
                if (u32Value == MAGIC_IMAGE_END)
                {
                      ap2Ok=1;
                      printf("AP2:OK\n");
                }
            }
        }
      }


      apSelect = msAPI_rmReadByte(EEPROM_OFFSET(u8DL_DefaultAPSelection));
      printf("AP select: %bd\n",apSelect);
      if(apSelect==1)
      {
          if(ap1Ok)
         {
            printf("go AP1\n");
            *startAddr=BOOTLOADER_CODE_SIZE;
            return TRUE;
         }
      }

      else if(apSelect==2)
      {
          if(ap2Ok)
         {
            printf("go AP2\n");
            *startAddr=BOOTLOADER_CODE_SIZE+ap2BaseOffset;
            return TRUE;
         }
      }


      {
         if(ap1Ok)
         {
            msAPI_rmWriteByte(EEPROM_OFFSET(u8DL_DefaultAPSelection),1);
            apSelect = msAPI_rmReadByte(EEPROM_OFFSET(u8DL_DefaultAPSelection));
            printf("comfirm AP select: %bd\n",apSelect);
            *startAddr=BOOTLOADER_CODE_SIZE;
            return TRUE;
         }
         else if(ap2Ok)
         {
            msAPI_rmWriteByte(EEPROM_OFFSET(u8DL_DefaultAPSelection),2);
            apSelect = msAPI_rmReadByte(EEPROM_OFFSET(u8DL_DefaultAPSelection));
            printf("comfirm AP select: %bd\n",apSelect);
            *startAddr=BOOTLOADER_CODE_SIZE+ap2BaseOffset;
            return TRUE;
         }

      }



      printf("NO AP OK!\n");
      return FALSE;

}
#endif

#if ENABLE_OAD
/******************************************************************************/
/// API to clear download information to zeros
/******************************************************************************/
void msAPI_BLoader_ClearDownloadInfo(void)
{
    U16 u16Index;

    for (u16Index=0; u16Index<RM_SIZE_DOWNLOAD; u16Index++)
    {
        msAPI_rmWriteByte(RM_ADDR_DOWNLOAD+u16Index, 0x00);
    }
    msAPI_rmWriteByte(RM_ADDR_DOWNLOAD, DL_INTEGRITY_ID);
}

#if (BLOADER)
/******************************************************************************/
/// API to get download type
/// @param EN_DOWNLOAD_TYPE \b IN Get Download type in EEPROM
/// @return BOOLEAN
///   - # TRUE Check EEPROM ID is OK, and Read the download type
///   - # FALSE EEPROM ID is wrong.
/******************************************************************************/
#if 0 // daniel
BOOLEAN msAPI_BLoader_GetDownloadType(EN_DOWNLOAD_TYPE * pu8Type)
{
#if 1
    if (msAPI_rmReadByte(EEPROM_OFFSET(u8DL_ID)) == DL_INTEGRITY_ID)
    {
        *pu8Type = (EN_DOWNLOAD_TYPE)msAPI_rmReadByte(EEPROM_OFFSET(u8DL_DWNType));
        printf("G DL: %bx\n", *pu8Type);
        return TRUE;
    }
    else
    {
        BOOTLOADER_ASSERT(printf("EEPROM Error\n"));
        return FALSE;
    }
#else // only for test
    //*pu8Type = DOWNLOAD_TYPE_OAD_USER;
    *pu8Type = _u8BootupDownloadType;
    return TRUE;
#endif
}
#endif
#endif //(BLOADER)

void msAPI_BLoader_SetCountry(U8 u8Country)
{
#if 1 // daniel
    u8Country=u8Country;
#else
    msAPI_rmWriteByte(EEPROM_OFFSET(u8DL_OAD_Country), u8Country);
#endif
}

#endif //ENABLE_OAD

#if (ENABLE_OAD)
/******************************************************************************/
/// API to set download type
/// @param u8DownloadType \b IN Download tpye defined in EN_DOWNLOAD_TYPE
/******************************************************************************/
void msAPI_BLoader_SetDownloadType(EN_DOWNLOAD_TYPE u8DownloadType)
{
#if 1 // daniel
    u8DownloadType=u8DownloadType;

#elif 1
    //printf("S DL: %bx\n", u8DownloadType);
    msAPI_rmWriteByte(EEPROM_OFFSET(u8DL_ID), DL_INTEGRITY_ID);
    msAPI_rmWriteByte(EEPROM_OFFSET(u8DL_DWNType), u8DownloadType);
#else // only for test
    _u8BootupDownloadType = (U8)u8DownloadType;
    return TRUE;
#endif
}
#endif

#undef MSAPI_BOOTLOADER_C
