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

#define MAPP_DATABASE_C


/******************************************************************************/
/*                            Header Files                                    */
/******************************************************************************/
#include <stdlib.h>
#include <string.h>

#include "debug.h"

// Common Definition
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "apiXC.h"
#include "apiXC_Adc.h"

#include "msAPI_ATVSystem.h"
#include "msAPI_DTVSystem.h"
#include "msAPI_MIU.h"
#include "msAPI_Flash.h"
#include "msAPI_Ram.h"
#include "msAPI_Timer.h"
#include "apiXC_Sys.h"
#include "apiXC_ModeParse.h"
#include "apiXC_Cus.h"
#include "msAPI_DB_CH.h"

#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalVar.h"
#include "MApp_DataBase.h"
#include "MApp_DataBase_CH.h"
#include "MApp_DataBase_Gen.h"

#include "MApp_Scan.h"
#include "MApp_SaveData.h"
#include "MApp_RestoreToDefault.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_Main.h"
#include "MApp_Key.h"
#include "MsOS.h"

#include "ZUI_tables_h.inl"

#if(ENABLE_S2_8M_FLASH)
#include "apiDTVSatTable.h"
#endif

//#include "msAPI_DTVSystem.h"
#include "MApp_ChannelList.h"

#if ENABLE_SECURITY_R2_HDCP22
#include "msAPI_SecurityR2.h"
#endif
//===============================================================


#ifndef MemAlign
#define MemAlign(n, unit)           ((((n)+(unit)-1)/(unit))*(unit))
#endif

#define QUICK_DATABASE_MONITOR_PERIOD  50


#if(ENABLE_S2_CHCHANGE_NOT_SAVE_DTAR)
U32 u32Enable_Change_Timer=0;
#endif


#if (HDCP_KEY_TYPE==HDCP_KEY_IN_DB)
//*************************************************************************
//Function name:        MApp_DB_LoadHDCP_KEY
//Passing parameter:    none
//Return parameter:     none
//Description:          Dump hdcp key
//*************************************************************************

extern MS_U8 _u8HdcpKey[HDCP_KEY_SIZE];

void MApp_DB_LoadHDCP_KEY(MS_U8 *u8HdcpKey)
{
    U32 dst;
    U16 i;

    dst = (SYSTEM_BANK_SIZE * HDCP_DB_BANK) ;

    msAPI_Flash_WaitWriteDone(FLASH_BLOCK_ERASE_MAX_TIME);

    MDrv_FLASH_Read(dst, HDCP_KEY_SIZE, u8HdcpKey);


    printf("MApp_DB_LoadHDCP_KEY\n");
    printf("HDCP_DB_BANK 0x%x\n", HDCP_DB_BANK);

    for (i=0; i<HDCP_KEY_SIZE; i++)
    {
        printf("%x ", u8HdcpKey[i]);
        if(i%16==15) printf("\n");
    }

    printf("\n");
}

void MApp_DB_SaveHDCP_KEY( U32 u16Offset)
{
    U32 dst;

    msAPI_Flash_WaitWriteDone(FLASH_BLOCK_ERASE_MAX_TIME);

    msAPI_Flash_Set_WriteProtect_Disable_Range(SYSTEM_BANK_SIZE * HDCP_DB_BANK, SYSTEM_BANK_SIZE); // MDrv_FLASH_WriteProtect(DISABLE); // <-@@@

    dst = (SYSTEM_BANK_SIZE * HDCP_DB_BANK) + u16Offset;

    // Check write address
    if( FALSE == msAPI_Flash_Check_WriteAddressValid(dst, HDCP_KEY_SIZE) )
    {
        // TODO
    }

    //MDrv_FLASH_AddressErase(dst, SYSTEM_BANK_SIZE, TRUE);

    MDrv_FLASH_Write(dst, HDCP_KEY_SIZE, _u8HdcpKey);

    printf("MApp_DB_SaveHDCP_KEY 000 \n");
    printf("HDCP_DB_BANK 0x%x\n", HDCP_DB_BANK);
    printf("dst 0x%x\n", dst);
    printf("u16Offset 0x%x\n", u16Offset);

	//MDrv_FLASH_WriteProtect(ENABLE);

    msAPI_Flash_Set_WriteProtect(ENABLE);
}
#endif

#if( (HDCP_KEY_TYPE==HDCP_KEY_IN_DB) || (HDCP22_KEY_TYPE==HDCP22_KEY_IN_DB))
void MApp_DB_EraseHDCPBank(void)
{
    U32 dst;

    dst = (SYSTEM_BANK_SIZE * HDCP_DB_BANK);

    // Check write address
    if( FALSE == msAPI_Flash_Check_WriteAddressValid(dst, SYSTEM_BANK_SIZE) )
    {
        // TODO
    }

    msAPI_Flash_WaitWriteDone(FLASH_BLOCK_ERASE_MAX_TIME);

    msAPI_Flash_Set_WriteProtect_Disable_Range(dst, SYSTEM_BANK_SIZE);

    MDrv_FLASH_AddressErase(dst, SYSTEM_BANK_SIZE, TRUE);

    //MDrv_FLASH_WriteProtect(ENABLE);
    msAPI_Flash_Set_WriteProtect(ENABLE);
}
#endif

#if ENABLE_SECURITY_R2_HDCP22
#if (HDCP22_KEY_TYPE==HDCP22_KEY_IN_DB)
//*************************************************************************
//Function name:        MApp_DB_LoadHDCP_KEY
//Passing parameter:    none
//Return parameter:     none
//Description:          Dump hdcp key
//*************************************************************************

void MApp_DB_LoadHDCP22_KEY(U8 *au8AesKey, U8 *au8Hdcp22Key)
{
    U32 dst;
    U8 au8Key[HDCP22_AES_KEY_SIZE+HDCP22_AES_KEY_DISCARD_ID_SIZE];
    U8 u8UseEfuseKey=0;

#if DEBUG_HDCP22_KEY_IN_DB
    U16 i;
#endif
    dst = (SYSTEM_BANK_SIZE * HDCP_DB_BANK) ;

    msAPI_Flash_WaitWriteDone(FLASH_BLOCK_ERASE_MAX_TIME);

    // read AES key & check efuse key is used or not
    MDrv_FLASH_Read(dst+HDCP22_AES_START, HDCP22_AES_READ_FROM_SPI_SIZE, au8Key);
#if (HDCP22_AES_KEY_TYPE==HDCP22_AES_KEY_IN_DB)
    if(au8AesKey)
    {
        memcpy(au8AesKey, au8Key, HDCP22_AES_KEY_SIZE);
    }
#else
    UNUSED(au8AesKey);
#endif
    if(
        (au8Key[HDCP22_AES_KEY_SIZE]==HDCP_AES_MAGIC_0) &&
        (au8Key[HDCP22_AES_KEY_SIZE+1]==HDCP_AES_MAGIC_1) &&
        (au8Key[HDCP22_AES_KEY_SIZE+2]==HDCP_AES_MAGIC_2) &&
        (au8Key[HDCP22_AES_KEY_SIZE+3]==HDCP_AES_MAGIC_3)
    )
    {
        msAPI_HDCP22_UseEfuseKey();
        u8UseEfuseKey=1;
    }

    if(u8UseEfuseKey)
    {
        printf("[HDCP22] External AES key used\n");
        MDrv_FLASH_Read(dst+HDCP22_ENCRYPTED_BY_EFUSE_KEY_START, HDCP22_KEY_SIZE, au8Hdcp22Key);
    }
    else
    {
        printf("[HDCP22] Internal e-fuse key used\n");
        MDrv_FLASH_Read(dst+HDCP22_ENCRYPTED_BY_EX_AES_KEY_START, HDCP22_KEY_SIZE, au8Hdcp22Key);
    }


    printf("[HDCP22] MApp_DB_LoadHDCP22_KEY fro SPI flash\n");
    printf("HDCP_DB_BANK 0x%x\n", HDCP_DB_BANK);
#if DEBUG_HDCP22_KEY_IN_DB
    printf("\n");
    for(i=0; i<HDCP22_AES_KEY_SIZE; i++)
    {
        printf("%x ", au8AesKey[i]);
        if(i%16==15) printf("\n");
    }

    printf("\n");
    for(i=0; i<HDCP22_KEY_SIZE; i++)
    {
        printf("%x ", au8Hdcp22Key[i]);
        if(i%16==15) printf("\n");
    }

    printf("\n");
#endif
}

void MApp_DB_SaveHDCP22_KEY(U8 *au8AesKey, U8 *au8Hdcp22Key)
{
    U32 dst;
#if DEBUG_HDCP22_KEY_IN_DB
    U16 i;
#endif

    dst = (SYSTEM_BANK_SIZE * HDCP_DB_BANK);

    // Check write address
    if( FALSE == msAPI_Flash_Check_WriteAddressValid(dst, SYSTEM_BANK_SIZE) )
    {
        // TODO
    }

    msAPI_Flash_WaitWriteDone(FLASH_BLOCK_ERASE_MAX_TIME);

    msAPI_Flash_Set_WriteProtect_Disable_Range(dst, SYSTEM_BANK_SIZE);


    //MDrv_FLASH_AddressErase(dst, SYSTEM_BANK_SIZE, TRUE);
#if (HDCP22_AES_KEY_TYPE==HDCP22_AES_KEY_IN_DB)
    if(au8AesKey!=NULL)
    {
        MDrv_FLASH_Write(dst+RESERVED_HDCP14_SIZE, HDCP22_AES_KEY_SIZE, au8AesKey);
    }
#else
    UNUSED(au8AesKey);
#endif

#if 1
    MDrv_FLASH_Write(dst+RESERVED_HDCP14_SIZE+RESERVED_HDCP22_AES_SIZE, HDCP22_KEY_SIZE, au8Hdcp22Key);
#elif 0
    MDrv_FLASH_Write(dst+RESERVED_HDCP14_SIZE+HDCP22_AES_KEY_SIZE, HDCP22_KEY_SIZE, au8Hdcp22Key);
#else
    MDrv_FLASH_Write(dst+RESERVED_HDCP14_SIZE+HDCP22_AES_KEY_SIZE, HDCP22_KEY_SIZE-HDCP22_AES_KEY_SIZE, au8Hdcp22Key);
    MDrv_FLASH_Write(dst+RESERVED_HDCP14_SIZE+HDCP22_KEY_SIZE-HDCP22_AES_KEY_SIZE, HDCP22_AES_KEY_SIZE, &au8Hdcp22Key[HDCP22_KEY_SIZE-HDCP22_AES_KEY_SIZE]);
#endif

#if DEBUG_HDCP22_KEY_IN_DB
    printf("MApp_DB_SaveHDCP_KEY  \n");
    printf("HDCP_DB_BANK 0x%x\n", HDCP_DB_BANK);
    printf("dst 0x%x\n", dst);
    //printf("u16Offset 0x%x\n", u16Offset);

    printf("\n");
    for(i=0; i<HDCP22_AES_KEY_SIZE; i++)
    {
        printf("%x ", au8AesKey[i]);
        if(i%16==15) printf("\n");
    }
    printf("\n");

    for(i=0; i<HDCP22_KEY_SIZE; i++)
    {
        printf("%x ", au8Hdcp22Key[i]);
        if(i%16==15) printf("\n");
    }

    //MDrv_FLASH_WriteProtect(ENABLE);
    msAPI_Flash_Set_WriteProtect(ENABLE);
#endif
}
#endif
#endif

//*************************************************************************
//Function name:        MApp_DB_SaveDataBase
//Passing parameter:    none
//Return parameter:     none
//Description:          Save database from SDRAM to EEPROM/Flash
//*************************************************************************
void MApp_DB_SaveDataBase_RightNow(U8 u8SaveDBFlag)
{
    BOOL bSaveDB_CH = TRUE;


    printf("MApp_DB_SaveDataBase_RightNow(0x%X)\n", u8SaveDBFlag);

    MApp_DB_GEN_SaveData_RightNow();
    //printf("MApp_DB_SaveDataBase_RightNow() ... 50%\n");

    if( u8SaveDBFlag&SAVE_DB_FLAG_CHECK_DB_CH_CHANGED )
    {
        if( MApp_DB_CH_Get_DataChanged() )
            bSaveDB_CH = TRUE;
        else
            bSaveDB_CH = FALSE;
    }

    if( bSaveDB_CH )
    {
        MApp_DB_CH_SaveData_RightNow();
    }
    else
    {
        // Check if API_DB_CH is busy, if yes , wait it finish
        MApp_DB_CH_WaitJobFinish();
    }

    printf("MApp_DB_SaveDataBase_RightNow() done~\n");
}

#if 1//(EEPROM_DB_STORAGE!=EEPROM_SAVE_ALL)
void MApp_DB_QuickDatabaseMonitor(void)
{
    MApp_DB_CH_Task();

    if( FALSE == msAPI_DB_CH_Is_Busy() )
    {
        MApp_DB_GEN_Task();
    }
}

#endif

//==========================================================================================

#undef MAPP_DATABASE_C
