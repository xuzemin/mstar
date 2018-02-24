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

////////////////////////////////////////////////////////////////////////////////
//
/// @file msAPI_Flash.h
/// This file includes MStar Flash control application interface
/// @brief API for Flash
/// @author MStar Semiconductor, Inc.
///
////////////////////////////////////////////////////////////////////////////////

#define MSAPI_FLASH_C

/******************************************************************************/
/*                              Header Files                                  */
/******************************************************************************/
// C Library
#include <stdio.h>

// Global Layer
#include "sysinfo.h"
#include "assert.h"

// Driver Layer
#include "msFlash.h"
#include "drvSERFLASH.h"

// API Layer
#include "msAPI_Flash.h"
#include "msAPI_Timer.h"
#include "MApp_SaveData.h"
#include "msAPI_MIU.h"
#include "datatype.h"
#include "msAPI_Memory.h"
#include "Utl.h"
#include "drvWDT.h"


/******************************************************************************/
/*                                 Macro                                      */
/******************************************************************************/
#define APIFLASH_DBG(y)         // y

#define DEBUG_FLASH_WRITE(x)    //x
#define DEBUG_FLASH_WP(x)       //x

/******************************************************************************/
/*                                 Local                                      */
/******************************************************************************/
#define ENABLE_FLASH_TEST_WRITE_BANK    0
#define ENABLE_FLASH_TEST_WRITE_DATA    0


#define MSIF_FLASH_BUILD_VERSION        0x09

#define FLASH_BUF_SIZE                  1024

#if(ENABLE_FLASH_WRITE_PROTECT_METHOD_M12)
static U8 u8FlashBlockProtectValue      = 0;
#endif

#define FLASH_REDUCE_WRITE_STATUS_TIME  0
#if(FLASH_REDUCE_WRITE_STATUS_TIME)
#define FLASH_IS_PROTECT_ALL    0xFFFFFFFF
static U32 s_Flash_u32LastUnprotectStartAddr = 0;
#endif

/******************************************************************************/
/*                               Functions                                    */
/******************************************************************************/

static U16 s_Flash_WP_u16WriteProtectDisableStatus = 0;

#define FLASH_WP_CLIENT__DB_GEN         BIT0
#define FLASH_WP_CLIENT__DB_CH_DATA     BIT1
//#define FLASH_WP_CLIENT__DB_FACTORY     BIT2
//#define FLASH_WP_CLIENT__DB_HDCP        BIT3


//==========================================================

static U32 s_Flash_u32WriteValidAddr_Start;
static U32 s_Flash_u32WriteValidAddr_End;
void msAPI_Flash_Init(void)
{
    U32 u32FlashSize;

    //PRINT_CURRENT_LINE();

    printf("msAPI_Flash_Init()\n");

    if( MDrv_SERFLASH_DetectSize(&u32FlashSize) )
    {
        printf(" => u32FlashSize=0x%X\n", u32FlashSize);
    }
    else
    {
        printf(" MDrv_SERFLASH_DetectSize() failed!\n");
        printf(" => u32FlashSize=0x%X\n", u32FlashSize);

        u32FlashSize = FLASH_SIZE;
        printf(" => FLASH_SIZE=0x%x\n", FLASH_SIZE);
    }

    s_Flash_u32WriteValidAddr_Start = 0x10000*FMAP_TOTAL_USE_BANK_END;
    s_Flash_u32WriteValidAddr_End = u32FlashSize - 1;

    printf(" => s_Flash_u32WriteValidAddr_Start=0x%x\n", s_Flash_u32WriteValidAddr_Start);
    printf(" => s_Flash_u32WriteValidAddr_End=0x%x\n", s_Flash_u32WriteValidAddr_End);

    if( u32FlashSize < s_Flash_u32WriteValidAddr_Start )
    {
        msDebug_FatalErrorHandler(FATAL_ERR_ID_FLASH_SIZE_INVALID, u32FlashSize);
    }

    // Test
    /*
    msAPI_Flash_Check_WriteAddressValid(0x770000, 0x10000);
    msAPI_Flash_Check_WriteAddressValid(0x780000, 0x10000);
    msAPI_Flash_Check_WriteAddressValid(0x7F0000, 0x10000);
    msAPI_Flash_Check_WriteAddressValid(0x800000, 0x10000);
    */
}

BOOL msAPI_Flash_Check_WriteAddressValid(U32 u32StartAddr, U32 u32Size )
{
    U32 u32Addr_End = u32StartAddr + u32Size - 1;
    BOOL bRtn = TRUE;


    // Check address - start
    if( (u32StartAddr < s_Flash_u32WriteValidAddr_Start)
      ||(u32StartAddr > s_Flash_u32WriteValidAddr_End)
      )
    {
        bRtn = FALSE;
    }

    // Check address - End
    if( (u32Addr_End < s_Flash_u32WriteValidAddr_Start)
      ||(u32Addr_End > s_Flash_u32WriteValidAddr_End)
      )
    {
        bRtn = FALSE;
    }

    if( FALSE == bRtn )
    {
        printf("\nError: The flash range(0x%X ~ 0x%X) should not be write! \n", u32StartAddr, u32Addr_End);
        msDebug_FatalErrorHandler(FATAL_ERR_ID_FLASH_WRITE_ADDR_INVALID, u32StartAddr);
    }

    return bRtn;
}

U16 msAPI_Flash_Get_WriteProtectStatus(void)
{
    //printf(" => s_Flash_WP_u16WriteProtectDisableStatus=%X\n", s_Flash_WP_u16WriteProtectDisableStatus);

    return s_Flash_WP_u16WriteProtectDisableStatus;
}

BOOL msAPI_Flash_IsAnyClientWantDisableWP(void)
{
    return (msAPI_Flash_Get_WriteProtectStatus() != 0);
}

void msAPI_Flash_Set_WriteProtectDisableStatus(U16 u16Client, BOOL bDisableWP)
{
    DEBUG_FLASH_WP( printf("msAPI_Flash_Set_WriteProtectDisableStatus(0x%X, disable=%u)\n", u16Client, bDisableWP); );

    if( bDisableWP )
    {
        s_Flash_WP_u16WriteProtectDisableStatus |= u16Client;
    }
    else
    {
        s_Flash_WP_u16WriteProtectDisableStatus &= (~u16Client);
    }

    DEBUG_FLASH_WP( printf(" ==> 0x%X\n", s_Flash_WP_u16WriteProtectDisableStatus); );
}

BOOL msAPI_Flash_WaitWriteDone(U32 u32Timeout)
{
    U32 u32CurTime = MsOS_GetSystemTime();
    U32 u32UseTime;

    while( MDrv_SERFLASH_CheckWriteDone() == FALSE )
    {
        // Clear watch dog
    #if ( WATCH_DOG )
        MDrv_Sys_ClearWatchDog();
    #endif

        if( u32Timeout ) // Check timeout
        {
            u32UseTime = msAPI_Timer_DiffTime_2(u32CurTime, MsOS_GetSystemTime());
            if( u32UseTime > u32Timeout )
            {
                printf("\nError: Wait flash write done timeout=%u!\n", u32Timeout);
                return FALSE;
            }
        }

        msAPI_Timer_Delayms_2(1, E_DELAY_ID_API_FLASH_WRITE_DONE);
    }

    u32UseTime = msAPI_Timer_DiffTime_2( u32CurTime, MsOS_GetSystemTime() );
    if( u32UseTime > 20 )
    {
        printf("Wait flash write done use %u ms.\n", u32UseTime);
    }

    return TRUE;
}

//-------------------------------------------------------------------------------------------------
/// Description :  Set active flash among multi-spi flashes
/// @param  eFlashChipSel   \b IN: The Flash index, 0 for external #1 spi flash, 1 for external #2 spi flash
/// @return TRUE : succeed
/// @return FALSE : not succeed
/// @note   For Secure booting = 0, please check hw_strapping or e-fuse (the board needs to jump)
//----------------------------------------------------------------------------------------------
BOOLEAN msAPI_Flash_ChipSelect(FLASH_CHIP_SELECT eFlashChipSel)
{
    return msFlash_ChipSelect((U8)eFlashChipSel);
}

U16 msAPI_Flash_Get_StatusRegister(void)
{
   U8 u8StatusReg;

   MDrv_FLASH_ReadStatusRegister(&u8StatusReg);

   return u8StatusReg;
}

void msAPI_Flash_PrintProtectStatus(void)
{
    U16 u16Status = msAPI_Flash_Get_StatusRegU16();

    printf("ProtectStatus: F=0x%X(0x%X)", u16Status, (u16Status>>2)&0xF );

#if(FLASH_REDUCE_WRITE_STATUS_TIME)
    printf(", UnprotectStart=0x%X", s_Flash_u32LastUnprotectStartAddr );
#endif

    printf("\n");
}

void _msAPI_Flash_Disable_DB_GEN_WP(void)
{
    U32 u32FlashAddr = FMAP_GEN_SETTING_BANK_START * 0x10000;
    U32 u32Size = 0x10000 * 2;

    DEBUG_FLASH_WP( printf("_msAPI_Flash_Disable_DB_GEN_WP()\n"); );

    msAPI_Flash_Set_WriteProtectDisableStatus(FLASH_WP_CLIENT__DB_GEN, TRUE);

    msAPI_Flash_Set_WriteProtect_Disable_Range(u32FlashAddr, u32Size);

    DEBUG_FLASH_WP( printf("%s() => ", __FUNCTION__); );
    DEBUG_FLASH_WP( msAPI_Flash_PrintProtectStatus(); );
}

//-------------------------------------------------------------------------------------------------
/// Description : Protect whole Flash chip
/// @param  bEnable \b IN: TRUE/FALSE: enable/disable protection
/// @return TRUE : succeed
/// @return FALSE : fail before timeout
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
#if 1 // Only for internal use
BOOLEAN msAPI_Flash_WriteProtect(BOOL bEnable)
{
    BOOL bRtn;

    DEBUG_FLASH_WP( printf("msAPI_Flash_WriteProtect(bEn=%u)\n", bEnable); );

    if( bEnable )
    {
        s_Flash_WP_u16WriteProtectDisableStatus = 0;
    }

    bRtn = MDrv_FLASH_WriteProtect(bEnable);

#if(FLASH_REDUCE_WRITE_STATUS_TIME)
    if( bEnable )
    {
        s_Flash_u32LastUnprotectStartAddr = FLASH_IS_PROTECT_ALL;
    }
    else
    {
        s_Flash_u32LastUnprotectStartAddr = 0;
    }
#endif

    DEBUG_FLASH_WP( printf("%s() => ", __FUNCTION__); );
    DEBUG_FLASH_WP( msAPI_Flash_PrintProtectStatus(); );

    return bRtn;
}
#endif

BOOLEAN msAPI_Flash_Set_WriteProtect(BOOL bEnable)
{
    BOOL bRtn;

    DEBUG_FLASH_WP( printf("msAPI_Flash_Set_WriteProtect(bEn=%u)\n", bEnable); );

#if(FLASH_ALWAYS_NOT_PROTECT_DB_GEN)
    if( (bEnable) && (s_Flash_WP_u16WriteProtectDisableStatus==FLASH_WP_CLIENT__DB_GEN) )
    {
        _msAPI_Flash_Disable_DB_GEN_WP();
        return TRUE;
    }
#endif

    if( (bEnable) && msAPI_Flash_IsAnyClientWantDisableWP() )
    {
        printf("\nWarning: Someone want enable WP, but another one is in use!(0x%X)\n", msAPI_Flash_Get_WriteProtectStatus());
        return TRUE;
    }

    bRtn = MDrv_FLASH_WriteProtect(bEnable);

#if(FLASH_REDUCE_WRITE_STATUS_TIME)
    if( bEnable )
    {
        s_Flash_u32LastUnprotectStartAddr = FLASH_IS_PROTECT_ALL;
    }
    else
    {
        s_Flash_u32LastUnprotectStartAddr = 0;
    }
#endif

    DEBUG_FLASH_WP( printf("%s() => ", __FUNCTION__); );
    DEBUG_FLASH_WP( msAPI_Flash_PrintProtectStatus(); );

    return bRtn;
}

//-------------------------------------------------------------------------------------------------
/// Description : Erase Flash by the specific Flash address
/// @param  u32StartAddr    \b IN: the start address of the Flash
/// @param  u32EraseSize  \b IN: the Size to erase
/// @param  bWait  \b IN: wait write done or not
/// @return TRUE : succeed
/// @return FALSE : illegal parameters or fail.
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
BOOLEAN msAPI_Flash_AddressErase(U32 u32StartAddr,U32 u32EraseSize,BOOL bWait)
{
    BOOL bRet = TRUE;


    // Check write address
    if( FALSE == msAPI_Flash_Check_WriteAddressValid(u32StartAddr, u32EraseSize) )
    {
        return FALSE;
    }

    //MDrv_FLASH_WriteProtect(DISABLE);
    msAPI_Flash_Set_WriteProtect_Disable_Range(u32StartAddr, u32EraseSize);

    bRet = MDrv_FLASH_AddressErase(u32StartAddr, u32EraseSize, bWait);

    //MDrv_FLASH_WriteProtect(ENABLE);
    msAPI_Flash_Set_WriteProtect(ENABLE);

    return bRet;
}

//-------------------------------------------------------------------------------------------------
/// Description : Erase Flash by the specific Flash block
/// @param  u32StartBlock    \b IN: the start block of the Flash
/// @param  u32EndBlock  \b IN: the end block of the Flash
/// @param  bWait  \b IN: wait write done or not
/// @return TRUE : succeed
/// @return FALSE : illegal parameters or fail.
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
#if 0
BOOLEAN msAPI_Flash_BlockErase(U32 u32StartBlock, U32 u32EndBlock, BOOL bWait)
{
    BOOL bRet = TRUE;

    //MS_BOOL MDrv_FLASH_BlockToAddress(MS_U32 u32BlockIndex, MS_U32 *pu32FlashAddr);
/*
    // Check write address
    if( FALSE == msAPI_Flash_Check_WriteAddressValid(u32StartAddr, u32EraseSize) )
    {
        return FALSE;
    }
*/
    MDrv_FLASH_WriteProtect(DISABLE);

    bRet = MDrv_SERFLASH_BlockErase(u32StartBlock, u32EndBlock, bWait);

    //MDrv_FLASH_WriteProtect(ENABLE);
    msAPI_Flash_Set_WriteProtect(ENABLE);

    return bRet;
}
#endif

//-------------------------------------------------------------------------------------------------
/// Description : Write data to Flash by the sprcific flash address
/// @param  u32StartAddr    \b IN: the start address of the Flash (4-B aligned)
/// @param  u32WriteSize    \b IN: write data size in Bytes (4-B aligned)
/// @param  user_buffer \b IN: Virtual Buffer Address ptr to flash write data
/// @return TRUE : succeed
/// @return FALSE : fail before timeout or illegal parameters
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
BOOLEAN msAPI_Flash_Write(U32 u32StartAddr, U32 u32WriteSize, U8 * user_buffer)
{
    BOOL bRet = TRUE;
    //U32 u32FlashSize = 0;


    DEBUG_FLASH_WRITE(printf("msAPI_Flash_Write(u32StartAddr=%X, u32WriteSize=%X)\n", u32StartAddr, u32WriteSize););

    // Check if size valid
    //MDrv_SERFLASH_DetectSize(&u32FlashSize);
    //ASSERT((u32StartAddr < u32FlashSize));
    //ASSERT((u32WriteSize < u32FlashSize));

    // Check write address
    if( FALSE == msAPI_Flash_Check_WriteAddressValid(u32StartAddr, u32WriteSize) )
    {
        return FALSE;
    }


    // Wait write done
    msAPI_Flash_WaitWriteDone(5000);

    //MDrv_FLASH_WriteProtect(DISABLE);
    msAPI_Flash_Set_WriteProtect_Disable_Range(u32StartAddr, u32WriteSize);

    // TODOl Check write protect range ...

    bRet = MDrv_SERFLASH_Write(u32StartAddr, u32WriteSize, user_buffer);

    //MDrv_FLASH_WriteProtect(ENABLE);
    msAPI_Flash_Set_WriteProtect(ENABLE);

    return bRet;
}

//-------------------------------------------------------------------------------------------------
/// Description : Read data from Flash by the sprcific flash address
/// @param  u32StartAddr    \b IN: the start address of the Flash (4-B aligned)
/// @param  u32ReadSize    \b IN: read data size in Bytes (4-B aligned)
/// @param  user_buffer \b OUT: Virtual Buffer Address ptr to flash write data
/// @return TRUE : succeed
/// @return FALSE : fail before timeout or illegal parameters
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
BOOLEAN msAPI_Flash_Read(U32 u32StartAddr, U32 u32ReadSize, U8 * user_buffer)
{
    U32 u32FlashSize = 0;

    MDrv_SERFLASH_DetectSize(&u32FlashSize);

    ASSERT((u32StartAddr < u32FlashSize));
    ASSERT((u32ReadSize < u32FlashSize));

    // Wait write done
    msAPI_Flash_WaitWriteDone(5000);

    return MDrv_FLASH_Read(u32StartAddr, u32ReadSize, user_buffer);
}

//-------------------------------------------------------------------------------------------------
/// Description : Detect flash type by reading the MID and DID
/// @return TRUE : succeed
/// @return FALSE : unknown flash type (if it occurs, please inform flash maintainer.)
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
BOOLEAN msAPI_Flash_DetectType(void)
{
    return MDrv_SERFLASH_DetectType();
}

//-------------------------------------------------------------------------------------------------
/// Description : Get flash start block index of the flash address
/// @param  u32FlashAddr    \b IN: flash address
/// @param  pu32BlockIndex    \b OUT: poniter to store the returning block index
/// @return TRUE : succeed
/// @return FALSE : illegal parameters
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
BOOLEAN msAPI_Flash_AddressToBlock(U32 u32FlashAddr, U32 *pu32BlockIndex)
{
    return MDrv_SERFLASH_AddressToBlock(u32FlashAddr, pu32BlockIndex);
}

//-------------------------------------------------------------------------------------------------
/// Description : Get flash start address of a block index
/// @param  u32BlockIndex    \b IN: block index
/// @param  pu32FlashAddr    \b OUT: pointer to store the returning flash address
/// @return TRUE : succeed
/// @return FALSE : illegal parameters
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
BOOLEAN msAPI_Flash_BlockToAddress(U32 u32BlockIndex, U32 *pu32FlashAddr)
{
    return MDrv_SERFLASH_BlockToAddress(u32BlockIndex, pu32FlashAddr);
}

//-------------------------------------------------------------------------------------------------
/// Description : Check write done in Serial Flash
/// @return TRUE : Done
/// @return FALSE : Wait until TimeOut
/// @note   Not allowed in interrupt context
//-------------------------------------------------------------------------------------------------
BOOLEAN msAPI_Flash_CheckWriteDone()
{
    return MDrv_SERFLASH_CheckWriteDone();
}

//-------------------------------------------------------------------------------------------------
/// Description  : Check DateBase/GenSetting area whether be protected.
/// @return TRUE : Not be protected
/// @return FALSE: been protected
/// @note
//-------------------------------------------------------------------------------------------------
#if(ENABLE_FLASH_WRITE_PROTECT_METHOD_M12)

#define g_bOpenGenstStoreDBG 0
BOOLEAN msAPI_Flash_WriteProtect_GetBPStatus(void)
{
    U8 u8BPStatus = 0;

    MDrv_FLASH_ReadStatusRegister(&u8BPStatus);

    if(u8FlashBlockProtectValue == (u8BPStatus&0xFC))//don't judge the wip/wel bit of BP Register
    {
        if(g_bOpenGenstStoreDBG)
        {
            printf("[GetBPStatus] TRUE >> u8FlashBlockProtectValue = 0x%X\n", u8FlashBlockProtectValue);
        }
        return TRUE;
    }

    if(g_bOpenGenstStoreDBG)
    {
        printf("[GetBPStatus] FAIL >> u8FlashBlockProtectValue = 0x%X\n", u8FlashBlockProtectValue);
    }

    return FALSE;
}

//-------------------------------------------------------------------------------------------------
/// Description  : Set DateBase/GenSetting area not to be protected.
/// @note
//-------------------------------------------------------------------------------------------------
void msAPI_Flash_WriteProtect_SetBPStatus(void)
{
    U8 u8GetBPStatus = 0;

    if(g_bOpenGenstStoreDBG)
    {
        printf("[WriteProtect_SetBPStatus_1] u8FlashBlockProtectValue =0x%X\n" , u8FlashBlockProtectValue);
    }

    msAPI_Flash_Set_WriteProtectDisableStatus( FLASH_WP_CLIENT__DB_GEN, TRUE);
    msAPI_Flash_Set_WriteProtectDisableStatus( FLASH_WP_CLIENT__DB_CH_DATA, TRUE);

    msAPI_Flash_Set_WriteProtect_Disable_Range(SYSTEM_BANK_SIZE * FMAP_CH_DB_BANK_START, (FLASH_SIZE - FMAP_CH_DB_BANK_START*SYSTEM_BANK_SIZE));
    //printf("WP_Range: Start=%X, size=%X\n", SYSTEM_BANK_SIZE * QUICK_DB_GENSETTING_BANK, (FLASH_SIZE - QUICK_DB_GENSETTING_BANK*SYSTEM_BANK_SIZE));

    MDrv_FLASH_ReadStatusRegister(&u8GetBPStatus);
    u8FlashBlockProtectValue = (u8GetBPStatus&0xFC);//don't judge the wip/wel bit of BP Register

    if(g_bOpenGenstStoreDBG)
    {
        printf("[WriteProtect_SetBPStatus_2] u8GetBPStatus =0x%X\n" , u8GetBPStatus);
        printf("[WriteProtect_SetBPStatus_2] u8FlashBlockProtectValue =0x%X\n" , u8FlashBlockProtectValue);
    }
}
#endif

void msAPI_Flash_Init_WriteProtect(void)
{
    DEBUG_FLASH_WP( printf("msAPI_Flash_Init_WriteProtect()\n"); );

#if 0 // Test WP
    U16 u16Status;
    PRINT_CURRENT_LINE();
    printf("Test WP\n");

//    MDrv_SERFLASH_SetDbgLevel(E_SERFLASH_DBGLV_DEBUG);

    MDrv_FLASH_WriteProtect(ENABLE);
    u16Status = msAPI_Flash_Get_StatusRegU16();
    printf("Enable WP => 0x%04X\n", u16Status);

    //MDrv_FLASH_WriteProtect(DISABLE);
    //u16Status = msAPI_Flash_Get_StatusRegU16();
    //printf("Disable WP => 0x%04X\n", u16Status);

    U32 u32UnProtectSize;
    U32 u32UnProtectStart;
    for( u32UnProtectSize = 0x20000; u32UnProtectSize <= (0x10000 * 20); u32UnProtectSize += 0x20000 )
    {
        u32UnProtectStart = FLASH_SIZE - u32UnProtectSize;
        if( FALSE == MDrv_FLASH_WriteProtect_Disable_Range_Set(u32UnProtectStart, u32UnProtectSize) )
        {
            printf("WriteProtect_Disable_Range faile!\n");
        }

        msAPI_Timer_Delayms(4);
        u16Status = msAPI_Flash_Get_StatusRegU16();
        printf("UnProtect: 0x%X, 0x%X => 0x%04X\n", u32UnProtectStart, u32UnProtectSize, u16Status);
    }

    u32UnProtectStart = FLASH_SIZE - 0x20000;
    u32UnProtectSize = 0x20000;
    MDrv_FLASH_WriteProtect_Disable_Range_Set(u32UnProtectStart, u32UnProtectSize);
    u16Status = msAPI_Flash_Get_StatusRegU16();
    printf("UnProtect: 0x%X, 0x%X => 0x%04X\n", u32UnProtectStart, u32UnProtectSize, u16Status);

    //MDrv_SERFLASH_WriteStatusRegister(0x88);
    //u16Status = msAPI_Flash_Get_StatusRegU16();
    //printf("=> 0x%04X\n",  u16Status);

#endif

    s_Flash_WP_u16WriteProtectDisableStatus = 0;


#if(ENABLE_FLASH_TEST_WRITE_DATA)
    msAPI_Flash_Test_WriteData();
#endif

#if(ENABLE_FLASH_TEST_WRITE_BANK)
    msAPI_Flash_Test_WriteBank(0x7F);
    msAPI_Flash_Test_WriteBank(0x7e);
#endif

#if (ENABLE_FLASH_WRITE_PROTECT_METHOD_M12)
    msAPI_Flash_WriteProtect_SetBPStatus();


#elif( FLASH_ALWAYS_NOT_PROTECT_DB_GEN )

    //msAPI_Flash_Disable_DB_GEN_WP();
    msAPI_Flash_Set_WP_DB_GEN(DISABLE);

#else

    //msAPI_Flash_WriteProtect(ENABLE);
    msAPI_Flash_Set_WriteProtect(ENABLE);

#endif

    DEBUG_FLASH_WP( printf("%s() => ", __FUNCTION__); );
    DEBUG_FLASH_WP( msAPI_Flash_PrintProtectStatus(); );
}

void msAPI_Flash_Set_WP_DB_CH(BOOL bEnable )
{
    DEBUG_FLASH_WP( printf("msAPI_Flash_Set_WP_DB_CH(bEn=%u)\n", bEnable); );

    if( bEnable == ENABLE ) // Enable write protect
    {
    #if(ENABLE_FLASH_WRITE_PROTECT_METHOD_M12)
    #else
        {
            msAPI_Flash_Set_WriteProtectDisableStatus(FLASH_WP_CLIENT__DB_CH_DATA, FALSE);

            msAPI_Flash_Set_WriteProtect(ENABLE);
        }
    #endif
    }
    else // Disable write protect
    {
        U32 u32FlashAddr = FMAP_CH_DB_BANK_START * 0x10000;
        U32 u32Size = FMAP_CH_DB_BANK_COUNT * 0x10000;

        msAPI_Flash_Set_WriteProtectDisableStatus(FLASH_WP_CLIENT__DB_CH_DATA, TRUE);

    #if(ENABLE_FLASH_WRITE_PROTECT_METHOD_M12)
        if( !msAPI_Flash_WriteProtect_GetBPStatus() )
        {
            msAPI_Flash_WriteProtect_SetBPStatus();
        }
    #else
        {
            msAPI_Flash_Set_WriteProtect_Disable_Range(u32FlashAddr, u32Size); // MDrv_FLASH_WriteProtect(DISABLE); // <-@@@
        }
    #endif
    }

    //DEBUG_FLASH_WP( printf("msAPI_Flash_Set_WP_DB_CH(bEn=%u) => 0x%X\n", bEnable, msAPI_Flash_Get_StatusRegU16()); );
    //DEBUG_FLASH_WP( msAPI_Flash_PrintProtectStatus(); );
}

void msAPI_Flash_Set_WP_DB_GEN(BOOL bEnable )
{
    DEBUG_FLASH_WP( printf("msAPI_Flash_Set_WP_DB_GEN(bEn=%u)\n", bEnable); );

    if( bEnable == ENABLE ) // Enable write protect
    {
    #if(ENABLE_FLASH_WRITE_PROTECT_METHOD_M12)

    #elif(FLASH_ALWAYS_NOT_PROTECT_DB_GEN)
        // Do nothing

    #else
        {
            msAPI_Flash_Set_WriteProtectDisableStatus(FLASH_WP_CLIENT__DB_GEN, FALSE);

            msAPI_Flash_Set_WriteProtect(ENABLE);
        }
    #endif
    }
    else // Disable write protect
    {
    #if(ENABLE_FLASH_WRITE_PROTECT_METHOD_M12)
        {
            if( !msAPI_Flash_WriteProtect_GetBPStatus() )
            {
                msAPI_Flash_WriteProtect_SetBPStatus();
            }
        }

    #elif(FLASH_ALWAYS_NOT_PROTECT_DB_GEN)
        if( 0 == (s_Flash_WP_u16WriteProtectDisableStatus&FLASH_WP_CLIENT__DB_GEN) )
        {
            _msAPI_Flash_Disable_DB_GEN_WP();
        }
    #else

        _msAPI_Flash_Disable_DB_GEN_WP();
    #endif
    }

    //DEBUG_FLASH_WP( printf("msAPI_Flash_Set_WP_DB_GEN(bEn=%u) => ", bEnable); );
    //DEBUG_FLASH_WP( msAPI_Flash_PrintProtectStatus(); );
}

BOOL msAPI_Flash_StoreDramData2Flash(U32 u32FlashAddr, U32 u32srcaddr, U32 u32Size, BOOL bControlWP)    // SRAM2Flash
{
    BOOL bResult = TRUE;
    //U32 u32Time;


    APIFLASH_DBG( printf(" StoreDramData2Flash(u32FlashAddr=0x%X, src=0x%X, size=%d, bControlWP=%u)\n", u32FlashAddr, u32srcaddr, u32Size, bControlWP); );

    //u32Time = msAPI_Timer_GetTime0();

    msAPI_Flash_WaitWriteDone(3000);

    msAPI_Flash_ChipSelect((FLASH_CHIP_SELECT)0);

    if( bControlWP )
    {
        //msAPI_Flash_Set_WP_DB_CH(DISABLE);
    }

    //printf("t4=%u,", msAPI_Timer_GetTime0());

    {
        // Write data to flash - new unit
        U32 u32DataVirAddr = MsOS_PA2KSEG0(u32srcaddr);
        //printf("u32DataVirAddr=0x%X\n", u32DataVirAddr);

        // Flush D-cache
        MsOS_Dcache_Flush( u32DataVirAddr, u32Size );

        // Flush Memory
        MsOS_FlushMemory();

        // Write data to falsh
        bResult = MDrv_FLASH_Write( u32FlashAddr,
                                    u32Size,
                                    (U8*)MsOS_PA2KSEG1(u32srcaddr) );
        if( bResult == FALSE )
        {
            printf("\nError: StoreDataBase2Flash: Write data failed\n");
        }
    }

    //printf("t5=%u,", msAPI_Timer_GetTime0());

    if( bControlWP )
    {
        //msAPI_Flash_Set_WP_DB_CH(ENABLE);
    }

    //printf("tt=%u,", msAPI_Timer_DiffTime_2(u32Time, msAPI_Timer_GetTime0()));

    return bResult;
}

/******************************************************************************/
/// API for MIU Store Database::
/// Copy database information from SDRAM to flash
/// @param u32srcaddr \b IN SDRAM address for Database information
/// @param s32size \b IN Database information size
/******************************************************************************/
/*
BOOLEAN msAPI_MIU_QuickDataBaseCheck(void)
{
    return MDrv_FLASH_CheckWriteDone();
}
*/

/*
void MApp_Printf_Flash_Variable(void)
{
    printf("MApp_Printf_Flash_Variable()\n");

    printf("\r\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("\r\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}
*/

U16 msAPI_Flash_GetVersion(void)
{
     printf(" Flash Build Version=%x\n",MSIF_FLASH_BUILD_VERSION);
     return  MSIF_FLASH_BUILD_VERSION;
}

U16 msAPI_Flash_Get_StatusRegU16(void)
{
    U8 u8Status1 = 0, u8Status2 = 0;

    MDrv_SERFLASH_ReadStatusRegister(&u8Status1);
    MDrv_SERFLASH_ReadStatusRegister2(&u8Status2);

    return (u8Status2<<8)|u8Status1;
}

void msAPI_Flash_Set_StatusRegU16(U16 u16Mask, U16 u16Value)
{
    U16 u16Tmp;

    printf("msAPI_Flash_Set_StatusRegU16(u16Mask=0x%X, u16Value=0x%X)\n", u16Mask, u16Value);

    msAPI_Flash_WaitWriteDone(5000);

    u16Tmp = msAPI_Flash_Get_StatusRegU16();
    //printf(" 1 u16Tmp=0x%X\n", u16Tmp);

    u16Tmp &= (~u16Mask);
    //printf(" 2 u16Tmp=0x%X\n", u16Tmp);

    u16Tmp |= (u16Value&u16Mask);
    //printf(" 3 u16Tmp=0x%X\n", u16Tmp);

    MDrv_SERFLASH_WriteStatusRegister(u16Tmp);

    msAPI_Flash_WaitWriteDone(5000);

    u16Tmp = msAPI_Flash_Get_StatusRegU16();
    printf(" => 0x%X\n", u16Tmp);
}

BOOL msAPI_Flash_Set_WriteProtect_Disable_Range(U32 u32DisableLowerBound, U32 u32DisableSize)
{
    DEBUG_FLASH_WP( printf("msAPI_Flash_Set_WriteProtect_Disable_Range(u32DisableStart=%X, u32DisableSize=%X\n)\n", u32DisableLowerBound, u32DisableSize); );

#if ( FLASH_ONLY_FULL_RANGE_WP )
    u32DisableLowerBound=u32DisableLowerBound;
    u32DisableSize=u32DisableSize;

    //PRINT_CURRENT_LINE();
    //printf("[MAYA-PATCH] Set Flash Status to 0x00!\n");
    //msAPI_Flash_Set_StatusRegU16( 0x00FF, 0x0000);
    msAPI_Flash_Set_WriteProtect(DISABLE);

    DEBUG_FLASH_WP( printf("%s() => ", __FUNCTION__); );
    DEBUG_FLASH_WP( msAPI_Flash_PrintProtectStatus(); );

    return TRUE;
#else

    BOOL bRtn = TRUE;

  #if(FLASH_REDUCE_WRITE_STATUS_TIME)
    if( s_Flash_u32LastUnprotectStartAddr != u32DisableLowerBound )
    {
        bRtn = MDrv_FLASH_WriteProtect_Disable_Range_Set(u32DisableLowerBound, u32DisableSize);
        if( bRtn )
        {
            s_Flash_u32LastUnprotectStartAddr = u32DisableLowerBound;
            DEBUG_FLASH_WP( printf("s_Flash_u32LastUnprotectStartAddr = 0x%X\n", s_Flash_u32LastUnprotectStartAddr ); );
        }
    }
  #else

    TIMER_SET_DELAY_ID_START(E_DELAY_ID_DRV_FLASH);
    bRtn = MDrv_FLASH_WriteProtect_Disable_Range_Set(u32DisableLowerBound, u32DisableSize);
    TIMER_SET_DELAY_ID_END();

  #endif


    DEBUG_FLASH_WP( printf("%s() => ", __FUNCTION__); );
    DEBUG_FLASH_WP( msAPI_Flash_PrintProtectStatus(); );

    return bRtn;
#endif
}

void msAPI_Flash_PrintData(U32 u32FlashAddr, U32 u32Size)
{
    U32 i,j;
    U8 au8FlashDataTmp[16];
    //Coverity 186415
    memset(au8FlashDataTmp, 0, 16);


    printf("\n==========  Flash %u(0x%X)  ==========\n", (U32)u32FlashAddr, (U32)u32FlashAddr);

    if( u32FlashAddr&0x0F )
    {
        u32FlashAddr &= 0xFFFFFFF0;
        u32Size += 16;
    }

    msAPI_Flash_WaitWriteDone(5000);

    for( i = 0; i < u32Size; i += 16 )
    {
        // Read flash to tmp buf
        msAPI_Flash_Read(u32FlashAddr, 16, au8FlashDataTmp);

        printf("0x%06X : ", u32FlashAddr);

        for( j = 0; j < 16; ++j )
        {
            printf("%02X ", au8FlashDataTmp[j]);
        }

        printf("\n");

        u32FlashAddr += 16;
    }

    printf("\n--------------------------------------------------\n");
}

#if(ENABLE_FLASH_TEST_WRITE_DATA)
void msAPI_Flash_Test_WriteData(void)
{
    PRINT_CURRENT_LINE();

    msAPI_Flash_WaitWriteDone(5000);

    U32 u32FlashSize = 0;
    U32 u32EraseAddr;
    U8 i;
    U8 au8FlashData[16] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
        0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xF0};
    U8 au8FlashDataR[16] = {0};
    U8 j, u8VerifyOKCount;
    BOOL bRtn;


    // Check flash size
    printf("MDrv_SERFLASH_DetectSize()\n");
    MDrv_SERFLASH_DetectSize(&u32FlashSize);
    printf(" => u32FlashSize=0x%X\n", u32FlashSize);


    printf("WP=0\n");
    // Use full range WP
    msAPI_Flash_WriteProtect(DISABLE);

    for( i = 1; i <= 4; ++ i )
    {
        u32EraseAddr = u32FlashSize - (0x10000 * i);
        printf("u32EraseAddr=0x%X\n", u32EraseAddr);

        msAPI_Flash_PrintData(u32EraseAddr, 16);

        printf("Erase bank: u32EraseAddr=0x%X\n", u32EraseAddr);
        MDrv_FLASH_AddressErase(u32EraseAddr, 0x10000, TRUE);

        msAPI_Flash_PrintData(u32EraseAddr, 16);

        printf("Write data\n");
        bRtn = MDrv_SERFLASH_Write(u32EraseAddr, 16, au8FlashData);

        msAPI_Flash_PrintData(u32EraseAddr, 16);

        // Verify
        printf("Verify Data...\n" );
        memset(au8FlashDataR, 0, 16);

        MDrv_SERFLASH_Read(u32EraseAddr, 16, au8FlashDataR);
        u8VerifyOKCount = 0;
        for( j = 0; j < 16; ++ j )
        {
            if( au8FlashDataR[j] != au8FlashData[j] )
            {
                printf("Verify failed! j = %u, 0x%X, 0x%X\n", j, au8FlashDataR[j], au8FlashData[j]);
            }
            else
            {
                u8VerifyOKCount += 1;
            }
        }
        if( u8VerifyOKCount < 16 )
        {
            printf("Verify Failed!\n");
        }
        else
        {
            printf("Verify OK\n");
        }
    }

    printf("WP=1\n");
    msAPI_Flash_WriteProtect(ENABLE);


    // Use range WP
    for( i = 1; i <= 4; ++ i )
    {
        u32EraseAddr = u32FlashSize - (0x10000 * i);
        printf("u32EraseAddr=0x%X\n", u32EraseAddr);

        msAPI_Flash_PrintData(u32EraseAddr, 16);

        // Set unprotect
        printf("Set WP_Range: u32EraseAddr=0x%X\n", u32EraseAddr);
        msAPI_Flash_Set_WriteProtect_Disable_Range( u32EraseAddr, 0x10000);

        printf("Erase bank: u32EraseAddr=0x%X\n", u32EraseAddr);
        MDrv_FLASH_AddressErase(u32EraseAddr, 0x10000, TRUE);

        msAPI_Flash_PrintData(u32EraseAddr, 16);

        printf("Write data\n");
        bRtn = MDrv_SERFLASH_Write(u32EraseAddr, 16, au8FlashData);

        printf("WP=1\n");
        msAPI_Flash_WriteProtect(ENABLE);

        msAPI_Flash_PrintData(u32EraseAddr, 16);

        // Verify
        printf("Verify Data...\n" );
        memset(au8FlashDataR, 0, 16);

        MDrv_SERFLASH_Read(u32EraseAddr, 16, au8FlashDataR);
        u8VerifyOKCount = 0;
        for( j = 0; j < 16; ++ j )
        {
            if( au8FlashDataR[j] != au8FlashData[j] )
            {
                printf("Verify failed! j = %u, 0x%X, 0x%X\n", j, au8FlashDataR[j], au8FlashData[j]);
            }
            else
            {
                u8VerifyOKCount += 1;
            }
        }
        if( u8VerifyOKCount < 16 )
        {
            printf("Verify Failed!\n");
        }
        else
        {
            printf("Verify OK\n");
        }

    }

    printf("WP=1\n");
    msAPI_Flash_WriteProtect(ENABLE);
}
#endif

#if(ENABLE_FLASH_TEST_WRITE_BANK)
#define TEST_WRITE_BANK_SIZE    0x10000
U8 g_au8TestFlash[TEST_WRITE_BANK_SIZE];
void msAPI_Flash_Test_WriteBank(U8 u8Bank)
{
    U32 u32FlashAddr = u8Bank * 0x10000;
    U32 i;
    BOOL bRtn;

    PRINT_CURRENT_LINE();
    printf("msAPI_Flash_Test_WriteBank(0x%X)\n", u8Bank);
    printf("u32FlashAddr=0x%X\n", u32FlashAddr);

    // init arary
    for( i = 0; i < TEST_WRITE_BANK_SIZE; ++ i )
    {
        g_au8TestFlash[i] = i&0xFF;
    }

    msAPI_Flash_WaitWriteDone(5000);

    // Check flash size
    U32 u32FlashSize = 0;
    printf("MDrv_SERFLASH_DetectSize()\n");
    MDrv_SERFLASH_DetectSize(&u32FlashSize);
    printf(" => u32FlashSize=0x%X\n", u32FlashSize);


    printf("WP=0\n");
    // Use full range WP
    //msAPI_Flash_WriteProtect(DISABLE);
    MDrv_FLASH_WriteProtect(DISABLE);

    printf("Erase bank: u32EraseAddr=0x%X at %u\n", u32FlashAddr, MsOS_GetSystemTime());
    MDrv_FLASH_AddressErase(u32FlashAddr, 0x10000, TRUE);
    printf("Erase done: at %u\n", MsOS_GetSystemTime());

    printf("Write data: u32FlashAddr=%X at %u\n", u32FlashAddr, MsOS_GetSystemTime());
    bRtn = MDrv_SERFLASH_Write(u32FlashAddr, TEST_WRITE_BANK_SIZE, g_au8TestFlash);
    printf("Write data done at %u\n", MsOS_GetSystemTime());

    // Clear array
    memset(g_au8TestFlash, 0, sizeof(TEST_WRITE_BANK_SIZE));

    printf("Read data at %u\n", MsOS_GetSystemTime());
    MDrv_SERFLASH_Read(u32FlashAddr, TEST_WRITE_BANK_SIZE, g_au8TestFlash);
    printf("Read done at %u\n", MsOS_GetSystemTime());

    // Check data
    printf("Check data...\n");
    U8 u8ErrCount = 0;
    for( i = 0; i < TEST_WRITE_BANK_SIZE; ++ i )
    {
        if( g_au8TestFlash[i] != (i&0xFF) )
        {
            printf("Err at 0x%X : 0x%X\n", i, g_au8TestFlash[i]);
            u8ErrCount += 1;

            if( u8ErrCount >= 10 )
                break;
        }
    }
    printf("Check data finish\n");

    printf("WP=1\n");
    //msAPI_Flash_WriteProtect(ENABLE);
    MDrv_FLASH_WriteProtect(ENABLE);

}
#endif

#undef MSAPI_FLASH_C

