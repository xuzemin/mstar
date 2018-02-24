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

#define MAPP_SAVEDATA_C

/******************************************************************************/
/*                            Header Files                                    */
/******************************************************************************/

#include "Board.h"

#include <stddef.h>
#include <string.h>

#include "msAPI_MIU.h"
#include "msAPI_Flash.h"
#include "msAPI_Ram.h"
#include "msAPI_Timer.h"
#if ENABLE_CI
#include "msAPI_OpCache.h"
#endif
#include "MApp_ChannelList.h"
#include "MApp_Scaler.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "apiXC_Sys.h"
#include "apiXC_ModeParse.h"
#include "apiXC_Cus.h"
#include "msAPI_DTVSystem.h"

#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalVar.h"
#include "MApp_GlobalFunction.h"
#include "MApp_RestoreToDefault.h"
#include "MApp_SaveData.h"
#include "MApp_DataBase.h"
#include "MApp_DataBase_CH.h"
#include "MApp_DataBase_Factory.h"

#if ENABLE_ATSC
#include "MApp_DataBase_ATSC.h"
#include "MApp_ChannelProc_ATSC.h"
#endif

#include "MApp_IR.h"
#include "MApp_PCMode.h"
//ZUI_TODO: #include "MApp_UiMenuFunc.h"
#include "MApp_EpgTimer.h"
#include "GPIO.h"
#include "MApp_ATVProc.h"
#if ENABLE_CI
#include "msAPI_CI.h"
#endif
#include "debug.h"

#include "MsOS.h"

#if ENABLE_SZ_FACTORY_OVER_SCAN_FUNCTION
#include"MApp_MVDMode.h"
#include"msAPI_Video.h"
#include"msAPI_VD.h"
#include"drvXC_HDMI_if.h"
#endif

#if ENABLE_PIP
#include "MApp_PIP.h"
#endif
#include "MApp_TopStateMachine.h"
//#include "MApp_ZUI_Main.h"

#include "msAPI_Bootloader.h"

#if ENABLE_ATSC_TTS
#include "MApp_TTSControlHandler.h"
#endif

#if(ENABLE_FM_RADIO)
#include "MApp_Radio.h"
#endif



#define DEBUG_SAVE_DATA(x)  //x

#define DEBUG_GEN_SETTING(x)    //x

#define DEBUG_DATA_CHECK_HANDLER(x)     x



#if (ENABLE_UPGRADE_CIPLUSKEY_BY_USB)
extern BOOLEAN b_isWriteCIkey;
extern BOOLEAN b_isCIkeyFileExit;
#endif

#ifdef EEPROM_DEBUG
    #define EE_PUTSTR(str)          printf(str)
    #define EE_PRINTF(str,val)      printf(str,val)
    #define EE_VALIDATE(x)          x
    #define EE_LOAD(x)              x
#else
    #define EE_PUTSTR(str)
    #define EE_PRINTF(str,val)
    #define EE_VALIDATE(x)
    #define EE_LOAD(x)
#endif

//********************************************************************************
//                     Macro
//********************************************************************************
#define CHECK_DATA_CHANGED_PERIOD   (2000)


/******************************************************************************/
/*                            Local variable                                 */
/******************************************************************************/


/******************************************************************************/
/*                                 Local                                        */
/******************************************************************************/

WORD checkSum;
static U32 su32DataSavePeriod = 0;
//static BOOLEAN sbPcModeSaveFlag = FALSE;

BOOL g_SaveData_bDebug = 0;

BOOL MApp_ReadDatabase(U32 srcIndex, U8* dstAddr, U16 size)
{
    //printf("MApp_ReadDatabase(srcIndex=0x%X, size=%u)\n", srcIndex, size);

    // Check address of ramdisk:
    if( (srcIndex > RM_DB_TOTAL_USAGE)
      ||(srcIndex > DATABASE_START_LEN)
      )
    {
        printf("\nError: WriteDatabase: address(0x%X) is over range!", srcIndex);
        return FALSE;
    }

    //if( srcIndex < RM_GEN_USAGE )
    if( srcIndex < RM_DB_CH_START_ADDR )
    {
      #if (ENABLE_DRAM_GEN_SAVE_TO_FLASH)
        memcpy(dstAddr,(void *)_PA2VA(srcIndex+RAM_DISK_MEM_ADDR),size);
      #else
        msAPI_rmBurstReadBytes(srcIndex, dstAddr, size);
      #endif
    }
    else //if(srcIndex>=RM_GEN_USAGE && srcIndex<(RM_64K_SIZE+RM_GEN_USAGE))
    {
      #if (ENABLE_DRAM_DB_CH_SAVE_TO_EEPROM)
        msAPI_rmBurstReadBytes(srcIndex, dstAddr, size);
      #else
        memcpy(dstAddr,(void *)_PA2VA(srcIndex+RAM_DISK_MEM_ADDR),size);
      #endif
    }
    /*else
    {
        printf("\n MApp_ReadDatabase index overflow...!!!");
        return FALSE;
    }*/

    //printf("MApp_ReadDatabase(srcIndex=0x%X, size=%u) end\n", srcIndex, size);

    return TRUE;
}

BOOL MApp_WriteDatabase(U32 dstIndex, U8* srcAddr, U16 size)
{
    if (g_SaveData_bDebug)
    {
        printf("MApp_WriteDatabase(dstIndex=0x%X, size=%u)\n", dstIndex, size);
    }

    // Check address of ramdisk:
    if( (dstIndex > RM_DB_TOTAL_USAGE)
      ||(dstIndex > DATABASE_START_LEN)
      )
    {
        printf("\nError: WriteDatabase: address(0x%X) is over range!\n", dstIndex);
        printf(" RM_DB_TOTAL_USAGE=%X\n", RM_DB_TOTAL_USAGE);
        printf(" DATABASE_START_LEN=%X\n", DATABASE_START_LEN);
        return FALSE;
    }

    //if( dstIndex < RM_GEN_USAGE )
    if( dstIndex < RM_DB_CH_START_ADDR )
    {
      #if (ENABLE_DRAM_GEN_SAVE_TO_FLASH)
        memcpy((void *)_PA2VA(dstIndex+RAM_DISK_MEM_ADDR),srcAddr,size);

        //g_u8QuickDataBase |= QUICK_DB_GENST_MODIFIED;
        MApp_DB_GEN_Set_DataChanged(TRUE);
      #else
        msAPI_rmBurstWriteBytes(dstIndex, srcAddr, size);
      #endif
    }
    else //if(dstIndex>=RM_GEN_USAGE && dstIndex<(RM_64K_SIZE+RM_GEN_USAGE))
    {
        //PRINT_CURRENT_LINE();
      #if (ENABLE_DRAM_DB_CH_SAVE_TO_EEPROM)
        msAPI_rmBurstWriteBytes(dstIndex, srcAddr, size);
      #else

        if( TRUE == msAPI_MIU_CompareBuf(dstIndex+RAM_DISK_MEM_ADDR, srcAddr, size) )
        {
            memcpy((void *)_PA2VA(dstIndex+RAM_DISK_MEM_ADDR), srcAddr, size);

            //g_u8QuickDataBase |= QUICK_DB_UPDATE;
            MApp_DB_CH_Set_DataChanged(TRUE);
        }
        else
        {
            if( g_SaveData_bDebug )
            {
                printf(" DB: Data no changed!\n");
            }
        }
      #endif
    }
    /*else
    {
        printf("\n MApp_WriteDatabase index overflow...!!!");
        return FALSE;
    }*/

    //printf("MApp_WriteDatabase(dstIndex=0x%X, size=%u) end\n", dstIndex, size);

    return TRUE;
}

//*************************************************************************
//Function name:
//Passing parameter:
//Return parameter:
//Description:
//*************************************************************************

U16 MApp_CalCheckSum_SkipFirst2Byte( BYTE *pBuf, WORD wBufLen )
{
#if ENABLE_SW_CRC16 // Use CRC16 to cal checksum
    U16 u16CheckSum;


    if( wBufLen <= 2 )
        return 0;

    u16CheckSum = msAPI_CRC16_Cal(pBuf+2, wBufLen-2);

    //printf("0x%X,%u => 0x%X\n", pBuf, wBufLen, u16CheckSum);

    return u16CheckSum;

#else

    U16 CheckSum;

    CheckSum = 0;

    while( wBufLen > 2 )//calculate pBuf[2]~pBuf[End] do not count pBuf[0] pBuf[1],it is checksum
    {
        -- wBufLen;
        CheckSum += pBuf[wBufLen];
    }

    //ask to mstar
    return (CheckSum+0x55);
#endif
}

U16 MApp_CalCheckSum( BYTE *pBuf, WORD wBufLen )
{
#if ENABLE_SW_CRC16 // Use CRC16 to cal checksum
    U16 u16CheckSum;

    u16CheckSum = msAPI_CRC16_Cal(pBuf, wBufLen);

    //printf("0x%X,%u => 0x%X\n", pBuf, wBufLen, u16CheckSum);

    return u16CheckSum;

#else
    U16 CheckSum;

    CheckSum = 0;

    while( wBufLen )
    {
        -- wBufLen;
        CheckSum += pBuf[wBufLen];
    }

    //ask to mstar
    return (CheckSum+0x55);
#endif
}

#if (EEPROM_DB_STORAGE != EEPROM_SAVE_NONE)
void MApp_CheckEEPROM(void)
{
    BYTE ucTmp;
    BYTE bInitEEPROM = FALSE;  // if eeprom test error init variable by default

    // if you want erase database, change database version which is defined in MApp_RestoreToDefault.h
    ucTmp = msAPI_rmReadByte(RM_EEPROM_ID_ADDRESS);

    // Check EEPROM ...
    if (ucTmp != USR_EEPROM_ID/*+randTimeText[7]*/) // check EEPROM ID
    {
        EE_PUTSTR("\r\nEEPROM ID Invalid!");
        bInitEEPROM = TRUE;
    }
    else // general
    {
        EE_PUTSTR("\r\nEEPROM ID OK! ");
    }

    //bInitEEPROM = TRUE;
    if( bInitEEPROM ) // EEPROM need init
    {
        msAPI_rmWriteByte(RM_EEPROM_ID_ADDRESS, USR_EEPROM_ID); // reset EEPROM ID

        MApp_InitGenSetting(); // initialize general setting

    #if 0//(EEPROM_DB_STORAGE == EEPROM_SAVE_ALL)
      #if(ENABLE_API_DTV_SYSTEM)
        msAPI_CM_ResetDTVDataManager(FALSE);
      #endif

        msAPI_ATV_ResetATVDataManager();

        MApp_SaveData_InitGenSettingExt();
    #endif

        EE_PUTSTR("\r\nEEPROM reloaded!");
    }
    else
    {
        MApp_LoadGenSetting(); // load general setting

    #if 0//(EEPROM_DB_STORAGE == EEPROM_SAVE_ALL)

     #if (ENABLE_DTV == 1)
        msAPI_CM_InitDTVDataManager();
     #endif

        MApp_SaveData_LoadGenSettingExt();
        //msAPI_ATV_InitATVDataManager();
    #endif
    }
}
#endif

#if (EEPROM_DB_STORAGE != EEPROM_SAVE_ALL)
void MApp_CheckFlash(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

#if( ENABLE_FACTORY_SETTING_IN_SEPERATE_BANK )
    MApp_DB_Factory_Init();
#endif


    // Init database-Gen
    MApp_DB_GEN_Init();

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_CheckFlash_DB_CH(void)
{
#if ENABLE_ATSC
    // This must be after DB_GEN, and Before DB_CH
    MApp_DB_ATSC_InitBaseAddr((EN_ANT_TYPE)ANT_TYPE);
#endif

    // Init DB-CH ...
    MApp_DB_CH_Init();
}

#endif

//============================================================

typedef struct
{
    U8 u8Id;
    char* pcSettingName;
    U8* pu8Data;
    U16 u16DataSize;
    U32 u32DramAddr;
    void (*fpRestoreDefaultValueFunc)(void);
} StuDBSettingInfo;

#define GEN_SETTING_CHILD(id,name,var,type,RestoreDefaultFunc)     {   \
    (id),                           \
    (name),                         \
    (U8*)&(stGenSetting.var),       \
    sizeof(type),                   \
    RM_GENSET_START_ADR + (U32)(offsetof(MS_GENSETTING, var)),  \
    RestoreDefaultFunc,             \
}

#define FACTORY_SETTING_CHILD(id,name,var,type,RestoreDefaultFunc)     {   \
    (id),                           \
    (name),                         \
    (U8*)&(g_stFactorySetting.var),       \
    sizeof(type),                   \
    RM_FACTORY_START_ADDR + (U32)(offsetof(MS_FACTORY_SETTING, var)),  \
    RestoreDefaultFunc,             \
}

static StuDBSettingInfo s_astDBSettingInfo[] =
{
    GEN_SETTING_CHILD( E_SAVE_DATA_ID_DEBUG,    "debugSetting", stDebugSetting, MS_DEBUG_SETTING,   MApp_DataBase_RestoreDefault_DebugSetting   ),
    GEN_SETTING_CHILD( E_SAVE_DATA_ID_MISC,     "MiscSetting",  stMiscSetting,  MS_MISC_SETTING,    MApp_DataBase_RestoreDefault_MiscSetting    ),
    GEN_SETTING_CHILD( E_SAVE_DATA_ID_TV,       "TvSetting",    stTvSetting,    MS_TV_SETTING,      MApp_DataBase_RestoreDefault_TVSetting      ),
    GEN_SETTING_CHILD( E_SAVE_DATA_ID_HDMI,     "HdmiSetting",  stHDMISetting,  Stru_DB_HDMI_SETTING,MApp_DataBase_RestoreDefault_HDMISetting   ),

#if(ENABLE_DTV_EPG&&DB_MANUAL_EVENT_SAVE_IN_DB_GEN)
    GEN_SETTING_CHILD( E_SAVE_DATA_ID_MANUAL_EVENT, "ManualEventSetting", stManualEventSetting, Stru_DB_MANUAL_EVENT, MApp_DataBase_RestoreDefault_ManualEvent ),
#endif

#if ((BRAZIL_CC)||(ATSC_CC == ATV_CC))
    GEN_SETTING_CHILD( E_SAVE_DATA_ID_CLOSE_CAPTION, "CCSetting",stCCSetting,   Stru_DB_CC_SETTING, MApp_DataBase_RestoreDefault_CloseCaptionSetting ),
#endif

#if (ENABLE_MFC_6M20||ENABLE_MFC_6M30)
    GEN_SETTING_CHILD( E_SAVE_DATA_ID_MISC,     "DevMfcSetting",stDevMfcSetting,MS_DEV_MFC_SETTING, MApp_DataBase_RestoreDefault_DevMfcSetting ),
#endif

#if ENABLE_3D_PROCESS
    GEN_SETTING_CHILD( E_SAVE_DATA_ID_3D_SETTING,"3DSetting",   st3DSetting,    Stru3DSetting,  MApp_DataBase_RestoreDefault_3DSetting ),
#endif

#if (ENABLE_S2)
    GEN_SETTING_CHILD( E_SAVE_DATA_ID_DVBS,     "DvbsSetting",  stDvbsSetting,  MS_DVBS_SETTING,    MApp_DataBase_RestoreDefault_DvbsSetting ),
#endif

#if( DB_PC_MODE_SAVE_TO_DB_GEN )
    GEN_SETTING_CHILD( E_SAVE_DATA_ID_PC_MODE, "PcModeSetting",  stDBPcModeSetting,  Stru_DB_PcModeSetting, MApp_DataBase_RestoreDefault_PcModeSetting ),
#endif

#if (ENABLE_ATSC)
    // stCaptionSetting_Type g_CaptionSetting;
    //E_SAVE_DATA_ID_ATSC_CAPTION_SETTING,
    GEN_SETTING_CHILD( E_SAVE_DATA_ID_ATSC_CAPTION_SETTING, "AtscCaptionSetting",  g_CaptionSetting,  stCaptionSetting_Type, MApp_DataBase_RestoreDefault_CaptionSetting ),

    // MS_VCHIP_SETTING g_VChipSetting;
    // E_SAVE_DATA_ID_ATSC_VCHIP_SETTING
    GEN_SETTING_CHILD( E_SAVE_DATA_ID_ATSC_VCHIP_SETTING, "AtscVChipSetting",  g_VChipSetting,  MS_VCHIP_SETTING, MApp_DataBase_RestoreDefault_VChip ),
#endif

#if(ENABLE_FM_RADIO)
    //E_SAVE_DATA_ID_RADIO_SETTING, //  StuRadioSetting stRadioSetting;
    GEN_SETTING_CHILD( E_SAVE_DATA_ID_RADIO_SETTING, "RadioSetting", stRadioSetting, StuRadioSetting, MApp_FMRadio_DB_RestoreToDefault ),
#endif


// ------------------------------------------------------------
    FACTORY_SETTING_CHILD( E_SAVE_DATA_FACTORY_VD_SETTING,
        "FacVdSetting", stVDSetting, StruFacVDSetting, MApp_DataBase_RestoreDefault_FactoryVDSetting   ),
    FACTORY_SETTING_CHILD( E_SAVE_DATA_FACTORY_MISC_SETTING,
        "FacMiscSetting",  stFacMiscSetting,  StruFacMiscSetting, MApp_DataBase_RestoreDefault_FactoryMiscSetting    ),

  #if ENABLE_PANEL_BIN
    FACTORY_SETTING_CHILD( E_SAVE_DATA_FACTORY_PNL_SETTING,
        "FacPnlSetting",  stFacPnlSetting,  StruFacPnlSetting, MApp_DataBase_RestoreDefault_FactoryPnlSetting    ),
  #endif


};

#define DB_SETTING_INFO_NUM     (sizeof(s_astDBSettingInfo)/sizeof(StuDBSettingInfo))

#define DB_SETTING_INFO_CHECK_GEN_ID(id)        ((id>E_SAVE_DATA_GEN_SETTING_START)&&(id<E_SAVE_DATA_GEN_SETTING_END))
#define DB_SETTING_INFO_CHECK_FACTORY_ID(id)    ((id>E_SAVE_DATA_FACTORY_SETTING_START)&&(id<E_SAVE_DATA_FACTORY_SETTING_END))


StuDBSettingInfo* MApp_SaveData_Get_SettingInfo(U8 u8SaveDataId)
{
    U8 u8CurId;

    for( u8CurId = 0; u8CurId < DB_SETTING_INFO_NUM; ++ u8CurId )
    {
        if( s_astDBSettingInfo[u8CurId].u8Id == u8SaveDataId )
        {
            return &(s_astDBSettingInfo[u8CurId]);
        }
    }

    printf("\nError: Can not find saveId=%u\n", u8SaveDataId);
    return NULL;
}

U16 MApp_SaveData_CalCheckSum_BySettingInfo(StuDBSettingInfo* pSettingInfo)
{
    if( pSettingInfo == NULL )
    {
        return 0;
    }

    if( pSettingInfo->u16DataSize <= 2 )
    {
        return 0;
    }

    return MApp_CalCheckSum_SkipFirst2Byte( pSettingInfo->pu8Data, pSettingInfo->u16DataSize );
}

/*U16 MApp_SaveData_CalCheckSum_ById(U8 u8SaveDataId)
{
    StuDBSettingInfo* pSettingInfo = MApp_SaveData_Get_SettingInfo(u8SaveDataId);

    if( pSettingInfo == NULL )
    {
        return 0;
    }

    return MApp_SaveData_CalCheckSum_BySettingInfo(pSettingInfo);
}*/

void MApp_SaveData_Update_CheckSum_BySettingInfo(StuDBSettingInfo* pSettingInfo)
{
    U16 u16CheckSum = 0;

    if( pSettingInfo == NULL )
    {
        return;
    }

    DEBUG_SAVE_DATA( printf("MApp_SaveData_Update_CheckSum_BySettingInfo(Id=%)\n", pSettingInfo->u8Id); );

    // Check sum must at first 2 byte
    if( pSettingInfo->u16DataSize > 2 )
    {
        u16CheckSum = MApp_SaveData_CalCheckSum_BySettingInfo(pSettingInfo);
        pSettingInfo->pu8Data[0] = u16CheckSum&0xFF;
        pSettingInfo->pu8Data[1] = u16CheckSum>>8;
        //*((U16*)(pSettingInfo->pu8Data)) = u16CheckSum;
        //printf("CS: %X,%X,%X\n", u16CheckSum, pSettingInfo->pu8Data[0], pSettingInfo->pu8Data[1]);
    }
}

void MApp_SaveData_Update_CheckSum(U8 u8SaveDataId)
{
    U8 u8CurId;
    StuDBSettingInfo* pSettingInfo = NULL;

    DEBUG_SAVE_DATA( printf("MApp_SaveData_Update_CheckSum(id=%u)!\n", u8SaveDataId); );

    //printf("stGenSetting.stDebugSetting.u8Flag1=%u\n", stGenSetting.stDebugSetting.u8Flag1);

    if( u8SaveDataId == E_SAVE_DATA_ID_ALL )
    {
        for( u8CurId = 0; u8CurId < DB_SETTING_INFO_NUM; ++ u8CurId )
        {
            MApp_SaveData_Update_CheckSum_BySettingInfo( &(s_astDBSettingInfo[u8CurId]) );
        }
    }
    else if( (u8SaveDataId == E_SAVE_DATA_ID_GEN_ALL)
           ||(u8SaveDataId == E_SAVE_DATA_ID_FACTORY_ALL)
           )
    {
        for( u8CurId = 0; u8CurId < DB_SETTING_INFO_NUM; ++ u8CurId )
        {
            if( ((u8SaveDataId == E_SAVE_DATA_ID_GEN_ALL)&&DB_SETTING_INFO_CHECK_GEN_ID(s_astDBSettingInfo[u8CurId].u8Id) )
              ||((u8SaveDataId == E_SAVE_DATA_ID_FACTORY_ALL)&&DB_SETTING_INFO_CHECK_FACTORY_ID(s_astDBSettingInfo[u8CurId].u8Id) )
              )
            {
                MApp_SaveData_Update_CheckSum_BySettingInfo( &(s_astDBSettingInfo[u8CurId]) );
            }
        }
    }
    else
    {
        pSettingInfo = MApp_SaveData_Get_SettingInfo(u8SaveDataId);
        MApp_SaveData_Update_CheckSum_BySettingInfo(pSettingInfo);
    }
}

void MApp_SaveData_SaveSetting_BySettingInfo(StuDBSettingInfo* pSettingInfo)
{
    U16 u16CheckSum = 0;

    if( pSettingInfo == NULL )
    {
        return;
    }

    DEBUG_SAVE_DATA(printf("MApp_SaveData_SaveSetting_BySettingInfo(Id=%d)\n", pSettingInfo->u8Id););

    // Check sum must at first 2 byte
    if( pSettingInfo->u16DataSize > 2 )
    {
        u16CheckSum = MApp_SaveData_CalCheckSum_BySettingInfo(pSettingInfo);
        pSettingInfo->pu8Data[0] = u16CheckSum&0xFF;
        pSettingInfo->pu8Data[1] = u16CheckSum>>8;
        //*((U16*)(pSettingInfo->pu8Data)) = u16CheckSum;
        DEBUG_SAVE_DATA(printf("CS: 0x%X, 0x%X, 0x%X\n", u16CheckSum, pSettingInfo->pu8Data[0], pSettingInfo->pu8Data[1]););
    }

    DEBUG_SAVE_DATA( printf("Write DB: memAdr=%X, VarAdr=%X, size=%X\n", pSettingInfo->u32DramAddr, pSettingInfo->pu8Data, pSettingInfo->u16DataSize););

    MApp_WriteDatabase( pSettingInfo->u32DramAddr, pSettingInfo->pu8Data, pSettingInfo->u16DataSize);

}

void MApp_SaveData_SaveSetting(U8 u8SaveDataId)
{
    StuDBSettingInfo* pSettingInfo = MApp_SaveData_Get_SettingInfo(u8SaveDataId);

    MApp_SaveData_SaveSetting_BySettingInfo(pSettingInfo);
}

void MApp_SaveData_RestoreToDefault_BySettingInfo(StuDBSettingInfo* pSettingInfo)
{
    printf("MApp_SaveData_RestoreToDefault_BySettingInfo!\n");

    if( pSettingInfo == NULL )
    {
        return;
    }

    // Restore to default value
    if( pSettingInfo->fpRestoreDefaultValueFunc != NULL )
    {
        pSettingInfo->fpRestoreDefaultValueFunc();
    }
}

void MApp_SaveData_RestoreToDefault(U8 u8SaveDataId)
{
    U8 u8CurId;
    StuDBSettingInfo* pSettingInfo = NULL;

    DEBUG_SAVE_DATA( printf("MApp_SaveData_RestoreToDefault(id=%u)!\n", u8SaveDataId); );

    //printf("stGenSetting.stDebugSetting.u8Flag1=%u\n", stGenSetting.stDebugSetting.u8Flag1);

    if( (u8SaveDataId == E_SAVE_DATA_ID_ALL) )
    {
        for( u8CurId = 0; u8CurId < DB_SETTING_INFO_NUM; ++ u8CurId )
        {
            MApp_SaveData_RestoreToDefault_BySettingInfo( &(s_astDBSettingInfo[u8CurId]) );
        }
    }
    else if( (u8SaveDataId == E_SAVE_DATA_ID_GEN_ALL)
            ||(u8SaveDataId == E_SAVE_DATA_ID_FACTORY_ALL)
            )
    {
        for( u8CurId = 0; u8CurId < DB_SETTING_INFO_NUM; ++ u8CurId )
        {
            if( ((u8SaveDataId == E_SAVE_DATA_ID_GEN_ALL)&&DB_SETTING_INFO_CHECK_GEN_ID(s_astDBSettingInfo[u8CurId].u8Id) )
              ||((u8SaveDataId == E_SAVE_DATA_ID_FACTORY_ALL)&&DB_SETTING_INFO_CHECK_FACTORY_ID(s_astDBSettingInfo[u8CurId].u8Id) )
              )
            {
                MApp_SaveData_RestoreToDefault_BySettingInfo( &(s_astDBSettingInfo[u8CurId]) );
            }
        }
    }
    else
    {
        pSettingInfo = MApp_SaveData_Get_SettingInfo(u8SaveDataId);
        MApp_SaveData_RestoreToDefault_BySettingInfo(pSettingInfo);
    }
}

void MApp_SaveData_ResetAndSave_BySettingInfo(StuDBSettingInfo* pSettingInfo)
{
    printf("MApp_SaveData_ResetAndSave_BySettingInfo!\n");

    if( pSettingInfo == NULL )
    {
        return;
    }

    // Restore to default value
    MApp_SaveData_RestoreToDefault_BySettingInfo(pSettingInfo);

    // Save to dram
    MApp_SaveData_SaveSetting_BySettingInfo(pSettingInfo);
}

void MApp_SaveData_Check_IfDataCorrect_BySettingInfo(StuDBSettingInfo* pSettingInfo)
{
    DEBUG_SAVE_DATA( printf("MApp_SaveData_Check_IfDataCorrect_BySettingInfo!\n"); );

    if( pSettingInfo == NULL )
    {
        return;
    }

    U16 u16CheckSum = MApp_SaveData_CalCheckSum_BySettingInfo(pSettingInfo);
    U16 u16CurCheckSum = (pSettingInfo->pu8Data[1]<<8) + pSettingInfo->pu8Data[0];

    // Check if data is invalid
    if( u16CurCheckSum != u16CheckSum )
    {
        printf("%s setting check sum is wrong(%x,%x)!", pSettingInfo->pcSettingName, u16CurCheckSum, u16CheckSum);
        MApp_SaveData_ResetAndSave_BySettingInfo(pSettingInfo);
    }
}

void MApp_SaveData_Check_IfDataCorrect(U8 u8SaveDataId)
{
    U8 u8CurId;
    StuDBSettingInfo* pSettingInfo = NULL;

    DEBUG_SAVE_DATA( printf("MApp_SaveData_Check_IfDataCorrect(id=%u)!\n", u8SaveDataId); );

    //printf("stGenSetting.stDebugSetting.u8Flag1=%u\n", stGenSetting.stDebugSetting.u8Flag1);

    if( u8SaveDataId == E_SAVE_DATA_ID_ALL )
    {
        for( u8CurId = 0; u8CurId < DB_SETTING_INFO_NUM; ++ u8CurId )
        {
            MApp_SaveData_Check_IfDataCorrect_BySettingInfo( &(s_astDBSettingInfo[u8CurId]) );
        }
    }
    else if( (u8SaveDataId == E_SAVE_DATA_ID_GEN_ALL)
            ||(u8SaveDataId == E_SAVE_DATA_ID_FACTORY_ALL)
            )
    {
        for( u8CurId = 0; u8CurId < DB_SETTING_INFO_NUM; ++ u8CurId )
        {
            if( ((u8SaveDataId == E_SAVE_DATA_ID_GEN_ALL)&&DB_SETTING_INFO_CHECK_GEN_ID(s_astDBSettingInfo[u8CurId].u8Id) )
              ||((u8SaveDataId == E_SAVE_DATA_ID_FACTORY_ALL)&&DB_SETTING_INFO_CHECK_FACTORY_ID(s_astDBSettingInfo[u8CurId].u8Id) )
              )
            {
                MApp_SaveData_Check_IfDataCorrect_BySettingInfo( &(s_astDBSettingInfo[u8CurId]) );
            }
        }
    }
    else
    {
        pSettingInfo = MApp_SaveData_Get_SettingInfo(u8SaveDataId);
        MApp_SaveData_Check_IfDataCorrect_BySettingInfo(pSettingInfo);
    }

    //printf("stGenSetting.stDebugSetting.u8Flag1=%u\n", stGenSetting.stDebugSetting.u8Flag1);
}

BOOL MApp_SaveData_Check_IfDataChanged_BySettingInfo(StuDBSettingInfo* pSettingInfo)
{
    //printf("MApp_SaveData_Check_IfDataChanged_BySettingInfo!\n");

    if( pSettingInfo == NULL )
    {
        return FALSE;
    }

    U16 u16CheckSum = MApp_SaveData_CalCheckSum_BySettingInfo(pSettingInfo);
    U16 u16CurCheckSum = (pSettingInfo->pu8Data[1]<<8) + pSettingInfo->pu8Data[0];

    // Check if data changed
    if( u16CurCheckSum != u16CheckSum )
    {
        printf("%s setting changed(%x,%x)\n", pSettingInfo->pcSettingName, u16CheckSum, u16CurCheckSum);
        MApp_SaveData_SaveSetting_BySettingInfo(pSettingInfo);
        return TRUE;
    }

    return FALSE;
}

BOOL MApp_SaveData_Check_IfDataChanged(U8 u8SaveDataId)
{
    U8 u8CurId;
    StuDBSettingInfo* pSettingInfo = NULL;
    BOOL bChanged = FALSE;


    //printf("MApp_SaveData_Check_IfDataChanged(id=%u)\n", u8SaveDataId);

    if( u8SaveDataId == E_SAVE_DATA_ID_ALL )
    {
        for( u8CurId = 0; u8CurId < DB_SETTING_INFO_NUM; ++ u8CurId )
        {
            if( MApp_SaveData_Check_IfDataChanged_BySettingInfo( &(s_astDBSettingInfo[u8CurId]) ) )
            {
                bChanged = TRUE;
            }
        }
    }
    else if( (u8SaveDataId == E_SAVE_DATA_ID_GEN_ALL)
            ||(u8SaveDataId == E_SAVE_DATA_ID_FACTORY_ALL)
            )
    {
        for( u8CurId = 0; u8CurId < DB_SETTING_INFO_NUM; ++ u8CurId )
        {
            if( ((u8SaveDataId == E_SAVE_DATA_ID_GEN_ALL)&&DB_SETTING_INFO_CHECK_GEN_ID(s_astDBSettingInfo[u8CurId].u8Id) )
              ||((u8SaveDataId == E_SAVE_DATA_ID_FACTORY_ALL)&&DB_SETTING_INFO_CHECK_FACTORY_ID(s_astDBSettingInfo[u8CurId].u8Id) )
              )
            {
                if( MApp_SaveData_Check_IfDataChanged_BySettingInfo( &(s_astDBSettingInfo[u8CurId]) ) )
                {
                    bChanged = TRUE;
                }
            }
        }
    }
    else
    {
        pSettingInfo = MApp_SaveData_Get_SettingInfo(u8SaveDataId);
        bChanged = MApp_SaveData_Check_IfDataChanged_BySettingInfo( pSettingInfo );
    }

    return bChanged;
}

void MApp_InitGenSetting(void)
{
    printf("MApp_InitGenSetting()\n");

    MApp_DataBase_RestoreDefaultValue(RESTORE_KEEP_NONE);

    MApp_SaveGenSetting();
}

void MApp_UpdateGenSettingCS(void)
{
    DEBUG_GEN_SETTING(printf("MApp_UpdateGenSettingCS()\n"););

    //stGenSetting.g_SysSetting.SystemSettingCS = MApp_SysSetting_CalChecksum();
    MApp_SysSetting_UpdateChecksum();


    stGenSetting.g_SoundSetting.soundSettingCS =
    MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_SoundSetting), SIZE_SOUND_SETTING );

    stGenSetting.g_Time.wTimeDataCS =
    MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_Time), SIZE_TIME_DATA  );

    stGenSetting.stScanMenuSetting.ScanMenuSettingCS=
    MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.stScanMenuSetting), SIZE_SCANMENU_SETTING );

    stGenSetting.g_BlockSysSetting.vchipSettingCS =
    MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_BlockSysSetting), SIZE_BLOCK_DATA);

#if (ENABLE_SSC)
    stGenSetting.g_SSCSetting.SscSettingCS =
    MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_SSCSetting), SIZE_SSC_DATA );
#endif

#if (ENABLE_CI)
    stGenSetting.g_CISetting.CISettingCS = MApp_CiSetting_CalCheckSum();
  #if( ENABLE_CI_PLUS )
    DB_CI_PLUS_SETTING.CIKeyCS = MApp_CiPlusSetting_CalCheckSum();
  #endif
#endif

#if (ENABLE_NONLINEAR_CURVE)
    stGenSetting.g_NonLinearCurveSetting.NonLinearCurveSettingCS =
    MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_NonLinearCurveSetting), SIZE_NONLINER_CURVE_SETTING);
#endif

#if (ENABLE_PIP)
    stGenSetting.g_stPipSetting.PIPSetupInfoCS =
    MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_stPipSetting), SIZE_PIP_DATA );
#endif

#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
    stGenSetting.g_Network_TS.NetWorkInfoCS =
    MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_Network_TS), SIZE_NETWORK_INFO_DATA );
#endif

#if ENABLE_DRM
    stGenSetting.g_VDplayerDRMInfo.VDplayerDRMInfoCS = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_VDplayerDRMInfo), SIZE_DRM_DATA );
#endif

#if (ENABLE_LAST_MEMORY==1)&&(ENABLE_LAST_MEMORY_STORAGE_SAVE==1)
    stGenSetting.g_MmLastMemorySetting.MmLastMemorySettignCS = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_MmLastMemorySetting), SIZE_MM_LASTMEMORY_SETTING-sizeof(checkSum));
#endif

#if ENABLE_GAMMA_ADJUST
    stGenSetting.g_GammaSetting.u16GammaAdjustCS =
    MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_GammaSetting), SIZE_GAMMA_SETTING );
#endif

    MApp_SaveData_Update_CheckSum(E_SAVE_DATA_ID_GEN_ALL);

}

void MApp_LoadGenSetting(void)
{
    EE_VALIDATE(U32 StartTime = msAPI_Timer_GetTime0());

    DEBUG_GEN_SETTING(printf("MApp_LoadGenSetting()\n"););

    MApp_ReadDatabase(RM_GENSET_START_ADR, (BYTE *)&stGenSetting, RM_SIZE_GENSET);

    MApp_CheckSysSetting();

    MApp_SaveData_Video_CheckIfDataCorrect();

    MApp_CheckSoundSetting();
    MApp_CheckScanMenuSetting();
    MApp_CheckTimeData();
    MApp_CheckBlockData();
  #if ENABLE_GAMMA_ADJUST
    MApp_CheckGammaSetting();
  #endif
  #if ENABLE_SSC
    MApp_CheckSSCData();
  #endif

  #if (ENABLE_NONLINEAR_CURVE)
    MApp_CheckNonLinearCurveSetting();
  #endif

  #if ENABLE_DRM
    MApp_CheckDrmSetting();
  #endif

#if (ENABLE_PIP)
    MApp_CheckPipSetting();
#endif

#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
    MApp_CheckNetworkInfoSetting();
#endif

  #if (ENABLE_LAST_MEMORY==1)&&(ENABLE_LAST_MEMORY_STORAGE_SAVE==1)
    MApp_CheckMmLastMemorySetting();
  #endif

#if( ENABLE_CI )
    MApp_CheckCISetting();
  #if( ENABLE_CI_PLUS )
    MApp_CheckCIPlusSetting();
  #endif
#endif

    MApp_SaveData_Check_IfDataCorrect(E_SAVE_DATA_ID_GEN_ALL);

    EE_VALIDATE(printf("Reload Period: %Lu ms\n", msAPI_Timer_DiffTimeFromNow(StartTime)));
}

void MApp_SaveGenSetting(void)
{
    DEBUG_GEN_SETTING(printf("MApp_SaveGenSetting()\n"););

    MApp_UpdateGenSettingCS();

    MApp_WriteDatabase(RM_GENSET_START_ADR, (BYTE *)&stGenSetting, RM_SIZE_GENSET);

    EE_PUTSTR("\r\nEEPROM saved!");
}

void MApp_ResetGenUserSetting(void)
{
    MApp_DataBase_RestoreUserSettingDefaultValue(RESTORE_KEEP_SYSTEM_PASSWORD);

    MApp_SaveGenSetting();
}

void MApp_SaveData_CallBack_BeforeWriteFlash(void)
{
    //PRINT_CUR_FUNCTION();

    // Copy gen settgin to dram
    //memcpy((void*) _PA2VA((U32)(g_u32DataBaseAddr+g_RM_GENSET_START_ADR)),
    //       (void*) &stGenSetting, g_RM_SIZE_GENSET);

    // Before write to flash, Save all genSetting to dram again to makesure
    // the dram data is the newest
    MApp_SaveGenSetting();

#if(ENABLE_FACTORY_SETTING_IN_SEPERATE_BANK==FALSE)
    // Force save variable to ramDisk
    MApp_DB_Factory_SaveData();
#endif

    MApp_DB_GEN_Set_DataChanged(FALSE);
}

#if ENABLE_DRM
void MApp_InitDrmSetting(void)
{

    MApp_Drm_RestoreDefaultSetupInfo();

    MApp_SaveDrmSetting();
}

void MApp_CheckDrmSetting(void)
{
    checkSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_VDplayerDRMInfo), SIZE_DRM_DATA);

    if( stGenSetting.g_VDplayerDRMInfo.VDplayerDRMInfoCS != checkSum )
    {
        MApp_InitDrmSetting();
        EE_LOAD(printf("MApp_InitDrmSetting!\n"));
    }
}

void MApp_LoadDrmSetting(void)
{
    MApp_ReadDatabase(RM_DRM_DATA_ADDRESS, (BYTE *)&(stGenSetting.g_VDplayerDRMInfo), SIZE_DRM_DATA);
    checkSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_VDplayerDRMInfo), SIZE_DRM_DATA );
    if( stGenSetting.g_VDplayerDRMInfo.VDplayerDRMInfoCS != checkSum )
    {
        MApp_InitDrmSetting();
        EE_LOAD(printf("MApp_InitDrmSetting!\n"));
    }
}

void MApp_SaveDrmSetting(void)
{
    stGenSetting.g_VDplayerDRMInfo.VDplayerDRMInfoCS = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_VDplayerDRMInfo), SIZE_DRM_DATA );
    MApp_WriteDatabase(RM_DRM_DATA_ADDRESS, (BYTE *)&(stGenSetting.g_VDplayerDRMInfo), SIZE_DRM_DATA);
    EE_PUTSTR("\n MApp_SaveDrmSetting!\n");
}
#endif

#if (ENABLE_PIP)
void MApp_InitPipSetting(void)
{
    MApp_DataBase_RestoreDefaultPIP();
    MApp_SavePipSetting();
}

void MApp_CheckPipSetting(void)
{
    checkSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_stPipSetting), SIZE_PIP_DATA);

    if( stGenSetting.g_stPipSetting.PIPSetupInfoCS != checkSum )
    {
        MApp_InitPipSetting();
        EE_LOAD(printf("MApp_InitPipSetting!\n"));
    }
}

void MApp_LoadPipSetting(void)
{
    MApp_ReadDatabase(RM_PIP_DATA_ADDRESS, (BYTE *)&(stGenSetting.g_stPipSetting), SIZE_PIP_DATA);
    checkSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_stPipSetting), SIZE_PIP_DATA );
    if( stGenSetting.g_stPipSetting.PIPSetupInfoCS != checkSum )
    {
        MApp_InitPipSetting();
        EE_LOAD(printf("MApp_InitPipSetting!\n"));
    }
}

void MApp_SavePipSetting(void)
{
    stGenSetting.g_stPipSetting.PIPSetupInfoCS = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_stPipSetting), SIZE_PIP_DATA );
    MApp_WriteDatabase(RM_PIP_DATA_ADDRESS, (BYTE *)&(stGenSetting.g_stPipSetting), SIZE_PIP_DATA);
    EE_PUTSTR("\n MApp_SavePipSetting!\n");
}
#endif

U16 MApp_SysSetting_CalChecksum(void)
{
    return MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_SysSetting), SIZE_SYS_SETTING );
}
BOOL MApp_SysSetting_IfCheckSumCorrect(void)
{
    if( stGenSetting.g_SysSetting.SystemSettingCS != MApp_SysSetting_CalChecksum() )
        return FALSE;

    return TRUE;
}
void MApp_SysSetting_UpdateChecksum(void)
{
    stGenSetting.g_SysSetting.SystemSettingCS = MApp_SysSetting_CalChecksum();
}

void MApp_InitSysSetting(void)
{
    SET_OSD_MENU_LANGUAGE(LANGUAGE_ENGLISH); // menu language

    MApp_DataBase_RestoreDefaultSystem(RESTORE_KEEP_NONE);

    MApp_SaveSysSetting();

#if 0//ENABLE_ATSC_TTS
    //MApp_TTSControlSetLanguage(stGenSetting.g_SysSetting.Language);
#endif
}

void MApp_CheckSysSetting(void)
{
    //msAPI_rmBurstReadBytes(RM_SYS_SETTING_ADDRESS, (BYTE *)&(stGenSetting.g_SysSetting), SIZE_SYS_SETTING);

    //checkSum = MApp_SysSetting_CalChecksum();
    //if( stGenSetting.g_SysSetting.SystemSettingCS != checkSum )
    if( FALSE == MApp_SysSetting_IfCheckSumCorrect() )
    {
        MApp_InitSysSetting();
        EE_LOAD(printf("MApp_InitSysSetting!\n"));
    }
}

/*
void MApp_LoadSysSetting(void)
{
    MApp_ReadDatabase(RM_SYS_SETTING_ADDRESS, (BYTE *)&(stGenSetting.g_SysSetting), SIZE_SYS_SETTING);
    checkSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_SysSetting), SIZE_SYS_SETTING );
    if( stGenSetting.g_SysSetting.SystemSettingCS != checkSum )
    {
        MApp_InitSysSetting();
        EE_LOAD(printf("MApp_InitSysSetting!\n"));
    }
}
*/

void MApp_SaveSysSetting(void)
{
    //stGenSetting.g_SysSetting.SystemSettingCS = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_SysSetting), SIZE_SYS_SETTING );
    MApp_SysSetting_UpdateChecksum();

    MApp_WriteDatabase(RM_SYS_SETTING_ADDRESS, (BYTE *)&(stGenSetting.g_SysSetting), SIZE_SYS_SETTING);

    EE_PUTSTR("\n MApp_SaveSysSetting!\n");
}

//=======================================================================

#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
#define DEBUG_NETWORK_INFO(x)   //x
void MApp_InitNetworkInfoSetting(void)
{
    DEBUG_NETWORK_INFO( PRINT_CURRENT_LINE(); );

    MApp_DataBase_RestoreDefaultNetworkInfo();

    MApp_SaveNetworkInfoSetting();
}

void MApp_CheckNetworkInfoSetting(void)
{
    DEBUG_NETWORK_INFO( PRINT_CURRENT_LINE(); );

    checkSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_Network_TS), SIZE_NETWORK_INFO_DATA);

    if( stGenSetting.g_Network_TS.NetWorkInfoCS != checkSum )
    {
        printf("Check NetworkInfoSetting changed!\n");

        MApp_InitNetworkInfoSetting();
    }
}

/*
void MApp_LoadNetworkInfoSetting(void)
{
    DEBUG_NETWORK_INFO( PRINT_CURRENT_LINE(); );

    MApp_ReadDatabase(RM_NETWORK_INFO_DATA_ADDRESS, (BYTE *)&(stGenSetting.g_Network_TS), SIZE_NETWORK_INFO_DATA);

    checkSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_Network_TS), SIZE_NETWORK_INFO_DATA );

    if( stGenSetting.g_Network_TS.NetWorkInfoCS != checkSum )
    {
        MApp_InitNetworkInfoSetting();
        EE_LOAD(printf("MApp_InitNetworkInfo!\n"));
    }
} */

void MApp_SaveNetworkInfoSetting(void)
{
    DEBUG_NETWORK_INFO( PRINT_CURRENT_LINE(); );
    DEBUG_NETWORK_INFO( printf("MApp_SaveNetworkInfoSetting()\n"); );

    stGenSetting.g_Network_TS.NetWorkInfoCS = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_Network_TS), SIZE_NETWORK_INFO_DATA );
    MApp_WriteDatabase(RM_NETWORK_INFO_DATA_ADDRESS, (BYTE *)&stGenSetting.g_Network_TS,SIZE_NETWORK_INFO_DATA);
}

MS_NETWORKID_TS* MApp_GetNetworkInfo(U8 u8NetworkIndex)
{
    DEBUG_NETWORK_INFO( PRINT_CURRENT_LINE(); );

    if(u8NetworkIndex >= SI_MAX_NETWORK)
        return NULL;

    return &stGenSetting.g_Network_TS.astNetworkInfo[u8NetworkIndex];
}
#endif

#if (ENABLE_CI )
void MApp_InitCISetting(void)
{
    MApp_DataBase_RestoreDefault_CI();

    MApp_SaveCISetting();
}

U16 MApp_CiSetting_CalCheckSum(void)
{
    return MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_CISetting), SIZE_CI_DATA );
}

void MApp_CheckCISetting(void)
{
    if( stGenSetting.g_CISetting.CISettingCS != MApp_CiSetting_CalCheckSum() )
    {
        MApp_InitCISetting();
        EE_LOAD(printf("MApp_CheckCISetting!\n"));
    }
}

/*void MApp_LoadCISetting(void)
{
    MApp_ReadDatabase(RM_CI_DATA_ADDRESS, (BYTE *)&(stGenSetting.g_CISetting), SIZE_CI_DATA);

    if( stGenSetting.g_CISetting.CISettingCS != MApp_CiSetting_CalCheckSum() )
    {
        MApp_InitCISetting();
        EE_LOAD(printf("MApp_InitCI!\n"));
    }
}*/

void MApp_SaveCISetting(void)
{
    stGenSetting.g_CISetting.CISettingCS = MApp_CiSetting_CalCheckSum();

    MApp_WriteDatabase(RM_CI_DATA_ADDRESS, (BYTE *)&stGenSetting.g_CISetting, SIZE_CI_DATA);

    EE_PUTSTR("\n MApp_SaveCISetting!\n");
}
#endif

#if (ENABLE_CI && ENABLE_CI_PLUS)
void MApp_InitCIPlusSetting(void)
{
    MApp_DataBase_RestoreDefault_CIPlus();

    MApp_SaveCIPlusSetting();
}

U16 MApp_CiPlusSetting_CalCheckSum(void)
{
    return MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(DB_CI_PLUS_SETTING), SIZE_CI_PLUS_DATA );
}

void MApp_CheckCIPlusSetting(void)
{
    if( DB_CI_PLUS_SETTING.CIKeyCS != MApp_CiPlusSetting_CalCheckSum() )
    {
        MApp_InitCIPlusSetting();
        EE_LOAD(printf("MApp_CheckCIPlusSetting!\n"));
    }
}

/*void MApp_LoadCIPlusSetting(void)
{
    MApp_ReadDatabase(RM_CI_PLUS_DATA_ADDRESS, (BYTE *)&(DB_CI_PLUS_SETTING), SIZE_CI_PLUS_DATA);

    if( DB_CI_PLUS_SETTING.CIKeyCS != MApp_CiPlusSetting_CalCheckSum() )
    {
        MApp_InitCIPlusSetting();
        EE_LOAD(printf("MApp_InitCI!\n"));
    }
}*/

void MApp_SaveCIPlusSetting(void)
{
    DB_CI_PLUS_SETTING.CIKeyCS = MApp_CiPlusSetting_CalCheckSum();

    MApp_WriteDatabase(RM_CI_PLUS_DATA_ADDRESS, (BYTE *)&DB_CI_PLUS_SETTING, SIZE_CI_PLUS_DATA);

    EE_PUTSTR("\n MApp_SaveCISetting!\n");
}
#endif

//=============================================================================================
#define DEBUG_SAVE_DATA_ADC(x)  //x

#define SIZE_ADC_SETTING        (sizeof(MS_ADC_SETTING))

U16 MApp_SaveData_ADC_CalChecksum(U8 u8AdcSettingIdx)
{
    if( u8AdcSettingIdx >= ADC_SET_NUMS )
        return 0;

    return MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(G_ADC_SETTING[u8AdcSettingIdx]), SIZE_ADC_SETTING );
}

void MApp_SaveData_ADC_ResetAllSetting(void)
{
    BYTE i;

    for( i = 0; i < ADC_SET_NUMS; i++ )
    {
        MApp_DataBase_RestoreDefaultADC((E_ADC_SET_INDEX)i);
        G_ADC_SETTING[i].u16ADCDataCS = MApp_SaveData_ADC_CalChecksum(i);
    }
}

void MApp_SaveData_ADC_InitSetting(E_ADC_SET_INDEX eAdcIndex )
{
    DEBUG_SAVE_DATA_ADC(printf("MApp_SaveData_ADC_InitSetting(eAdcIndex=%u)\n", eAdcIndex););

    if( eAdcIndex >= ADC_SET_NUMS )
        return;

    MApp_DataBase_RestoreDefaultADC(eAdcIndex);

    MApp_SaveData_ADC_SaveSetting(eAdcIndex);
}

/*
void MApp_LoadADCSetting(E_ADC_SET_INDEX eAdcIndex )
{
    MApp_ReadDatabase(RM_ADC_SETTING_ADDRESS(eAdcIndex), (BYTE *)&(G_ADC_SETTING[eAdcIndex] ), SIZE_ADC_SETTING);
    checkSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(G_ADC_SETTING[eAdcIndex]), SIZE_ADC_SETTING );
    if( G_ADC_SETTING[eAdcIndex].u16ADCDataCS != checkSum )
    {
        MApp_SaveData_ADC_InitSetting((E_ADC_SET_INDEX) eAdcIndex);
    }
}
*/

#if 0//( ENABLE_FACTORY_SETTING_IN_SEPERATE_BANK == FALSE )
#define RM_ADC_SETTING_START_ADDR   (RM_FACTORY_SETTING_DATA_ADDRESS + (U32)(offsetof(MS_FACTORY_SETTING, g_AdcSetting)) )
#define RM_ADC_SETTING_ADDRESS(i)   (RM_ADC_SETTING_START_ADDR  + (U16)(SIZE_ADC_SETTING*(i)))
#endif

void MApp_SaveData_ADC_CheckIfDataCorrect(void)
{
    BYTE i;

    DEBUG_SAVE_DATA_ADC(printf("MApp_SaveData_ADC_CheckIfDataCorrect()\n"););

    for( i = 0; i < ADC_SET_NUMS; i++ )
    {
        //printf(" Check G_ADC_SETTING[%u]=%X\n", i, (U32)&(G_ADC_SETTING[i]) );

        //msAPI_rmBurstReadBytes(RM_ADC_SETTING_ADDRESS + (SIZE_ADC_SETTING * i ), (BYTE *)&(G_ADC_SETTING[i]), SIZE_ADC_SETTING);
        checkSum = MApp_SaveData_ADC_CalChecksum(i);
        if( G_ADC_SETTING[i].u16ADCDataCS != checkSum )
        {
            printf("AdcSetting checksum error\n");
            MApp_SaveData_ADC_InitSetting( (E_ADC_SET_INDEX) i);
        }
    }
}

U8 MApp_GetCalibrationMode(E_ADC_SET_INDEX eAdcIndex)
{
    //MApp_LoadADCSetting(eAdcIndex);
    return G_ADC_SETTING[eAdcIndex].u8CalibrationMode;
}

//void MApp_SaveADCSetting(E_ADC_SET_INDEX eAdcIndex )
void MApp_SaveData_ADC_SaveSetting(E_ADC_SET_INDEX eAdcIndex )
{
    if( eAdcIndex >= ADC_SET_NUMS )
        return;

    G_ADC_SETTING[eAdcIndex].u16ADCDataCS = MApp_SaveData_ADC_CalChecksum(eAdcIndex);

#if( ENABLE_FACTORY_SETTING_IN_SEPERATE_BANK )
    //MApp_SaveFactorySetting();
#else
    // factory setting is in GenSetting:

    //MApp_WriteDatabase(RM_ADC_SETTING_ADDRESS(eAdcIndex), (BYTE *)&(G_ADC_SETTING[eAdcIndex]), SIZE_ADC_SETTING);
#endif

}

//=============================================================================================
#define DEBUG_SAVE_DATA_VIDEO(x)    //x
U16 MApp_SaveData_Video_CalCheckSum(U8 u8DataIdx)
{
    if( u8DataIdx >= DATA_INPUT_SOURCE_NUM )
    {
        printf("\nError: Video_CalCheckSum: DataIdx=%u\n", u8DataIdx);
        return 0;
    }

    return MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(G_VEDIO_SETTING[u8DataIdx]), sizeof(T_MS_VIDEO) );
}

#define RM_VIDEO_DATA_SIZE          (SIZE_VIDEO_DATA*DATA_INPUT_SOURCE_NUM)
#define RM_VIDEO_DATA_ADDRESS(i)    ( RM_GENSET_START_ADR + (U32)&(((MS_GENSETTING*)0)->g_astVideo[i]) )

void MApp_SaveData_Video_SaveSetting(E_DATA_INPUT_SOURCE enDataInputSource)
{
    DEBUG_SAVE_DATA_VIDEO(printf("MApp_SaveData_Video_SaveSetting(enDataInputSource=%u)\n", enDataInputSource););

    if( enDataInputSource >= DATA_INPUT_SOURCE_NUM )
    {
        BYTE i;
        for( i = 0; i < DATA_INPUT_SOURCE_NUM; i++ )
        {
            G_VEDIO_SETTING[i].wVideoDataCS = MApp_SaveData_Video_CalCheckSum(i);

            MApp_WriteDatabase( RM_VIDEO_DATA_ADDRESS(i),
                                    (BYTE *)&(G_VEDIO_SETTING[i]), sizeof(T_MS_VIDEO));
        }
    }
    else
    {
        //printf("RM_VIDEO_DATA_ADDRESS(i) = 0x%X\n", enDataInputSource, RM_VIDEO_DATA_ADDRESS(enDataInputSource) );

        G_VEDIO_SETTING[enDataInputSource].wVideoDataCS = MApp_SaveData_Video_CalCheckSum(enDataInputSource);
        MApp_WriteDatabase( RM_VIDEO_DATA_ADDRESS(enDataInputSource),
                                (BYTE *)&(G_VEDIO_SETTING[enDataInputSource]), sizeof(T_MS_VIDEO));
    }
}

void MApp_SaveData_Video_InitSetting(E_DATA_INPUT_SOURCE enDataInputSource)
{
    DEBUG_SAVE_DATA_VIDEO(printf("MApp_SaveData_Video_InitSetting(enDataInputSource=%u)\n", enDataInputSource););

    MApp_DataBase_RestoreDefaultVideo(enDataInputSource);

    MApp_SaveData_Video_SaveSetting(enDataInputSource);
}

/*
void MApp_LoadVideoSetting(E_DATA_INPUT_SOURCE enDataInputSource)
{
    MApp_ReadDatabase(RM_VIDEO_DATA_ADDRESS(enDataInputSource), (BYTE *)&(G_VEDIO_SETTING[enDataInputSource] ), SIZE_VIDEO_DATA);
    checkSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(G_VEDIO_SETTING[enDataInputSource]), SIZE_VIDEO_DATA );
    if( G_VEDIO_SETTING[enDataInputSource].wVideoDataCS != checkSum )
    {
        MApp_SaveData_Video_InitSetting((E_DATA_INPUT_SOURCE) enDataInputSource);
    }
}
*/

void MApp_SaveData_Video_CheckIfDataCorrect(void)
{
    BYTE i;
    U16 u16CS;


    DEBUG_SAVE_DATA_VIDEO(printf("MApp_SaveData_Video_CheckIfDataCorrect()\n"););

    for( i = 0; i < DATA_INPUT_SOURCE_NUM; i++ )
    {
        //printf("RM_VIDEO_DATA_ADDRESS(%u) = 0x%X\n", i, RM_VIDEO_DATA_ADDRESS(i) );

        u16CS = MApp_SaveData_Video_CalCheckSum(i);
        if( G_VEDIO_SETTING[i].wVideoDataCS != u16CS )
        {
            printf("CS1=%X, CS2=%X\n", u16CS, G_VEDIO_SETTING[i].wVideoDataCS);
            printf("VideoSetting[%u] CS error!\n", i);
            MApp_SaveData_Video_InitSetting((E_DATA_INPUT_SOURCE) i);
        }
    }
}

BOOL MApp_SaveData_Video_CheckIfDataChanged(void)
{
    BOOL bDataChanged = FALSE;
    BYTE i = DATA_INPUT_SOURCE_TYPE(MAIN_WINDOW);
    U16 u16CS;


    if( i >= DATA_INPUT_SOURCE_NUM )
    {
        return bDataChanged;
    }

    u16CS = MApp_SaveData_Video_CalCheckSum(i);

    if( G_VEDIO_SETTING[i].wVideoDataCS != u16CS )
    {
        //DEBUG_DATA_CHECK_HANDLER( printf("g_astVideo[%u] changed(%X,%X)\n", i, G_VEDIO_SETTING[i].wVideoDataCS, u16CS ); );
        DEBUG_DATA_CHECK_HANDLER( printf("g_astVideo[%u] changed\n", i ); );
        MApp_SaveData_Video_SaveSetting((E_DATA_INPUT_SOURCE)i);
        bDataChanged = TRUE;
    }
/*
    for( i = 0; i < DATA_INPUT_SOURCE_NUM; i++ )
    {
        if( G_VEDIO_SETTING[i].wVideoDataCS != MApp_SaveData_Video_CalCheckSum(i) )
        {
            printf("VideoSetting[%u] CS changed\n", i);
            MApp_SaveData_Video_SaveSetting((E_DATA_INPUT_SOURCE) i);
        }
    }
    */

    return bDataChanged;
}

//================================================================================

#define DEBUG_SAVE_DATA_WB(x)   //x

U16 MApp_SaveData_WB_CalCheckSum(U8 u8DataInputSource)
{
    DEBUG_SAVE_DATA_WB(printf("MApp_SaveData_WB_CalCheckSum(%u)", u8DataInputSource););

    if( u8DataInputSource >= DATA_INPUT_SOURCE_NUM)
    {
        printf("\nError: SaveData_WB_CalCheckSum: idx=%u\n", u8DataInputSource );
        return 0;
    }

    return MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(G_WHITE_BALANCE_SETTING[u8DataInputSource]), SIZE_WHITEBALANCE_DATA );
}

void MApp_InitWhiteBalanceSetting(E_DATA_INPUT_SOURCE enDataInputSource)
{
    DEBUG_SAVE_DATA_WB(printf("MApp_InitWhiteBalanceSetting(%u)", enDataInputSource););

    if( enDataInputSource >= DATA_INPUT_SOURCE_NUM)
    {
        printf("\nError: MApp_InitWhiteBalanceSetting: idx=%u\n", enDataInputSource );
        return ;
    }

    MApp_DataBase_RestoreDefaultWhiteBalance(enDataInputSource);

    MApp_SaveWhiteBalanceSetting(enDataInputSource);
}

/*
void MApp_LoadWhiteBalanceSetting(E_DATA_INPUT_SOURCE enDataInputSource)
{
    DEBUG_SAVE_DATA_WB(printf("MApp_LoadWhiteBalanceSetting(%u)", enDataInputSource););

    if( enDataInputSource >= DATA_INPUT_SOURCE_NUM)
    {
        printf("\nError: MApp_LoadWhiteBalanceSetting: idx=%u\n", enDataInputSource );
        return ;
    }

    //MApp_ReadDatabase(RM_WHITEBALANCE_DATA_ADDRESS(enDataInputSource), (BYTE *)&(G_WHITE_BALANCE_SETTING[enDataInputSource] ), SIZE_WHITEBALANCE_DATA);

    checkSum = MApp_SaveData_WB_CalCheckSum(enDataInputSource);

    if( G_WHITE_BALANCE_SETTING[enDataInputSource].wWhiteBalanceDataCS != checkSum )
    {
        MApp_InitWhiteBalanceSetting( (E_DATA_INPUT_SOURCE) enDataInputSource);
        EE_LOAD(printf("MApp_InitWhiteBalanceSetting(%bu)!\n", enDataInputSource));
    }
} */

void MApp_CheckWhiteBalanceSetting(void)
{
    BYTE i;
    U16 u16CheckSum;

    DEBUG_SAVE_DATA_WB(printf("MApp_CheckWhiteBalanceSetting()"););

    for( i = 0; i < DATA_INPUT_SOURCE_NUM; i++ )
    {
        //printf(" Check G_WHITE_BALANCE_SETTING[%u]=%X\n", i, (U32)&(G_WHITE_BALANCE_SETTING[i]) );

        //msAPI_rmBurstReadBytes(RM_WHITEBALANCE_DATA_ADDRESS, (BYTE *)&(G_WHITE_BALANCE_SETTING[i] ), SIZE_WHITEBALANCE_DATA);
        u16CheckSum = MApp_SaveData_WB_CalCheckSum((E_DATA_INPUT_SOURCE)i);
        if( G_WHITE_BALANCE_SETTING[i].wWhiteBalanceDataCS != u16CheckSum )
        {
            printf("WhiteBalance Setting checksum error\n");
            MApp_InitWhiteBalanceSetting( (E_DATA_INPUT_SOURCE) i);
            //EE_LOAD(printf("MApp_InitWhiteBalanceSetting(%bu)!\n", i));
        }
    }
}

void MApp_SaveWhiteBalanceSetting(E_DATA_INPUT_SOURCE enDataInputSource)
{
    BYTE i;

    DEBUG_SAVE_DATA_WB(printf("MApp_SaveWhiteBalanceSetting(%u)", enDataInputSource););

    if( enDataInputSource >= DATA_INPUT_SOURCE_NUM )
    {
        for( i = 0; i < DATA_INPUT_SOURCE_NUM; i++ )
        {
            G_WHITE_BALANCE_SETTING[i].wWhiteBalanceDataCS = MApp_SaveData_WB_CalCheckSum((E_DATA_INPUT_SOURCE)i);
            //MApp_WriteDatabase(RM_WHITEBALANCE_DATA_ADDRESS(i),
            //                        (BYTE *)&(G_WHITE_BALANCE_SETTING[i]), SIZE_WHITEBALANCE_DATA);
        }
    }
    else
    {
        G_WHITE_BALANCE_SETTING[enDataInputSource].wWhiteBalanceDataCS = MApp_SaveData_WB_CalCheckSum(enDataInputSource);
        // MApp_WriteDatabase(RM_WHITEBALANCE_DATA_ADDRESS(enDataInputSource),
        //                         (BYTE *)&(G_WHITE_BALANCE_SETTING[enDataInputSource]), SIZE_WHITEBALANCE_DATA);
    }

}

void MApp_CopyWhiteBalanceSettingToAllInput(void)
{
    U8 i;

    DEBUG_SAVE_DATA_WB(printf("MApp_CopyWhiteBalanceSettingToAllInput()"););

    if( DATA_INPUT_SOURCE_TYPE(MAIN_WINDOW) >= DATA_INPUT_SOURCE_NUM )
        return;

    for(i = 0; i < DATA_INPUT_SOURCE_NUM; i++)
    {
        G_WHITE_BALANCE_SETTING[i] = G_WHITE_BALANCE_SETTING[DATA_INPUT_SOURCE_TYPE(MAIN_WINDOW)];
        MApp_SaveWhiteBalanceSetting((E_DATA_INPUT_SOURCE) i);
    }
//    printf("MApp_CopyWhiteBalanceSettingToAllInput\n");
}

//================================================================================

#define DEBUG_SAVE_DATA_SUBCOLOR(x) x
U16 MApp_SaveData_SubColor_CalCheckSum(U8 u8DataIdx)
{
    if( u8DataIdx >= DATA_INPUT_SOURCE_NUM )
    {
        return 0;
    }

    return MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(G_SUB_COLOR_SETTING[u8DataIdx]), SIZE_SUBCOLOR_DATA );
}
void MApp_InitSubColorSetting(E_DATA_INPUT_SOURCE enDataInputSource)
{
    DEBUG_SAVE_DATA_SUBCOLOR(printf("MApp_InitSubColorSetting(%u)\n", enDataInputSource););

    if( enDataInputSource >= DATA_INPUT_SOURCE_NUM )
    {
        return ;
    }

    MApp_DataBase_RestoreDefaultSubColor(enDataInputSource);

    MApp_SaveSubColorSetting(enDataInputSource);
}

/*
void MApp_LoadSubColorSetting(E_DATA_INPUT_SOURCE enDataInputSource)
{
    if( enDataInputSource >= DATA_INPUT_SOURCE_NUM )
    {
        return ;
    }

    MApp_ReadDatabase(RM_SUBCOLOR_DATA_ADDRESS(enDataInputSource), (BYTE *)&(G_SUB_COLOR_SETTING[enDataInputSource] ), SIZE_SUBCOLOR_DATA);
    checkSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(G_SUB_COLOR_SETTING[enDataInputSource]), SIZE_SUBCOLOR_DATA );
    if( G_SUB_COLOR_SETTING[enDataInputSource].u16SubColorDataCS != checkSum )
    {
        MApp_InitSubColorSetting((E_DATA_INPUT_SOURCE) enDataInputSource);
        EE_LOAD(printf("MApp_InitSubColorSetting(%bu)!\n", enDataInputSource));
    }
}
*/

void  MApp_CheckSubColorSetting(void)
{
    BYTE i;

    for( i = 0; i < DATA_INPUT_SOURCE_NUM; i++ )
    {
        if( G_SUB_COLOR_SETTING[i].u16SubColorDataCS != MApp_SaveData_SubColor_CalCheckSum(i) )
        {
            DEBUG_SAVE_DATA_SUBCOLOR(printf("SubColor Setting(%u) CS error\n", i););
            MApp_InitSubColorSetting( (E_DATA_INPUT_SOURCE) i);
        }
    }
}

void MApp_SaveSubColorSetting(E_DATA_INPUT_SOURCE enDataInputSource)
{
    BYTE i;

    if( enDataInputSource >= DATA_INPUT_SOURCE_NUM )
    {
        for( i = 0; i < DATA_INPUT_SOURCE_NUM; i++ )
        {
            G_SUB_COLOR_SETTING[i].u16SubColorDataCS = MApp_SaveData_SubColor_CalCheckSum(i);
            //MApp_WriteDatabase(RM_SUBCOLOR_DATA_ADDRESS(i),
            //                        (BYTE *)&(G_SUB_COLOR_SETTING[i]), SIZE_SUBCOLOR_DATA);
        }
    }
    else
    {
        G_SUB_COLOR_SETTING[enDataInputSource].u16SubColorDataCS = MApp_SaveData_SubColor_CalCheckSum(enDataInputSource);

        //MApp_WriteDatabase(RM_SUBCOLOR_DATA_ADDRESS(enDataInputSource),
        //                        (BYTE *)&(G_SUB_COLOR_SETTING[enDataInputSource]), SIZE_SUBCOLOR_DATA);
    }

    EE_PUTSTR("\n MApp_SaveSubColorSetting!\n");
}

void MApp_CopySubColorDataToAllInput(void)
{
    U8 i;
    for(i = 0; i < DATA_INPUT_SOURCE_NUM; i++)
    {
        G_SUB_COLOR_SETTING[i] = G_SUB_COLOR_SETTING[DATA_INPUT_SOURCE_TYPE(MAIN_WINDOW)];
        MApp_SaveSubColorSetting( (E_DATA_INPUT_SOURCE) i);
    }
//    printf("MApp_CopySubColorDataToAllInput\n");
}

//================================================================================

void MApp_InitSoundSetting(void)
{
    MApp_DataBase_RestoreDefaultAudio(FALSE);

    MApp_SaveSoundSetting();
}

void MApp_CheckSoundSetting(void)
{
    //msAPI_rmBurstReadBytes(RM_SOUND_SETTING_ADDRESS, (BYTE *)&(stGenSetting.g_SoundSetting), SIZE_SOUND_SETTING);
    checkSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_SoundSetting), SIZE_SOUND_SETTING );
    if( stGenSetting.g_SoundSetting.soundSettingCS != checkSum )
    {
        MApp_InitSoundSetting();
        EE_LOAD(printf("MApp_InitSoundSetting!\n"));
    }
}
void MApp_LoadSoundSetting(void)
{
    MApp_ReadDatabase(RM_SOUND_SETTING_ADDRESS, (BYTE *)&(stGenSetting.g_SoundSetting), SIZE_SOUND_SETTING);
    checkSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_SoundSetting), SIZE_SOUND_SETTING );
    if( stGenSetting.g_SoundSetting.soundSettingCS != checkSum )
    {
        MApp_InitSoundSetting();
        EE_LOAD(printf("MApp_InitSoundSetting!\n"));
    }
}

void MApp_SaveSoundSetting(void)
{
    stGenSetting.g_SoundSetting.soundSettingCS =
    MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_SoundSetting), SIZE_SOUND_SETTING );
    MApp_WriteDatabase(RM_SOUND_SETTING_ADDRESS, (BYTE *)&(stGenSetting.g_SoundSetting), SIZE_SOUND_SETTING);
    EE_PUTSTR("\n MApp_SaveSoundSetting!\n");
}

void MApp_InitScanMenuSetting(void)
{
    MApp_DataBase_RestoreDefaultScanMenu();

    MApp_SaveScanMenuSetting();
}

void MApp_CheckScanMenuSetting(void)
{
    //msAPI_rmBurstReadBytes(RM_SOUND_SETTING_ADDRESS, (BYTE *)&(stGenSetting.g_SoundSetting), SIZE_SOUND_SETTING);
    checkSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.stScanMenuSetting), SIZE_SCANMENU_SETTING );
    if( stGenSetting.stScanMenuSetting.ScanMenuSettingCS != checkSum )
    {
        MApp_InitScanMenuSetting();
        EE_LOAD(printf("MApp_InitScanMenuSetting!\n"));
    }
}

/*
void MApp_LoadScanMenuSetting(void)
{
    MApp_ReadDatabase(RM_SOUND_SETTING_ADDRESS, (BYTE *)&(stGenSetting.g_SoundSetting), SIZE_SOUND_SETTING);
    checkSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.stScanMenuSetting), SIZE_SCANMENU_SETTING );
    if( stGenSetting.stScanMenuSetting.ScanMenuSettingCS != checkSum )
    {
        MApp_InitScanMenuSetting();
        EE_LOAD(printf("MApp_InitScanMenuSetting!\n"));
    }
}
*/

void MApp_SaveScanMenuSetting(void)
{
    stGenSetting.stScanMenuSetting.ScanMenuSettingCS=
    MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.stScanMenuSetting), SIZE_SCANMENU_SETTING );
    MApp_WriteDatabase(RM_SCANMENU_SETTING_ADDRESS, (BYTE *)&(stGenSetting.stScanMenuSetting), SIZE_SCANMENU_SETTING);
    EE_PUTSTR("\n MApp_SaveScanMenuSetting!\n");
}

//========================================
void MApp_InitTimeData(void)
{
    MApp_DataBase_RestoreDefaultTime();

    MApp_SaveTimeData();
}

void MApp_CheckTimeData(void)
{
    //msAPI_rmBurstReadBytes(RM_TIME_DATA_ADDRESS, (BYTE *)&(stGenSetting.g_Time), SIZE_TIME_DATA);
    checkSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_Time), SIZE_TIME_DATA );
    if( stGenSetting.g_Time.wTimeDataCS != checkSum )
    {
        MApp_InitTimeData();
        EE_LOAD(printf("MApp_InitTimeData!\n"));
    }
}

void MApp_LoadTimeData(void)
{
    MApp_ReadDatabase(RM_TIME_DATA_ADDRESS, (BYTE *)&(stGenSetting.g_Time), SIZE_TIME_DATA);
    checkSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_Time), SIZE_TIME_DATA );
    if( stGenSetting.g_Time.wTimeDataCS != checkSum )
    {
        MApp_InitTimeData();
        EE_LOAD(printf("MApp_InitTimeData!\n"));
    }
}

void MApp_SaveTimeData(void)
{
    stGenSetting.g_Time.wTimeDataCS =
    MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_Time), SIZE_TIME_DATA  );
    MApp_WriteDatabase(RM_TIME_DATA_ADDRESS, (BYTE *)&(stGenSetting.g_Time), SIZE_TIME_DATA);
    EE_PUTSTR("\n MApp_SaveTimeData!\n");
}

void MApp_InitBlockData(void)
{
    App_DataBase_RestoreDefaultBlock();
    MApp_SaveBlockData();
}

void MApp_CheckBlockData(void)
{
    checkSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_BlockSysSetting), SIZE_BLOCK_DATA );

    if( stGenSetting.g_BlockSysSetting.vchipSettingCS != checkSum )
    {
        MApp_InitBlockData();
        EE_LOAD(printf("MApp_InitBlockData!\n"));
    }
}

void MApp_LoadBlockData(void)
{
    MApp_ReadDatabase(RM_BLOCK_DATA_ADDRESS, (BYTE *)&(stGenSetting.g_BlockSysSetting), SIZE_BLOCK_DATA);

    checkSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_BlockSysSetting), SIZE_BLOCK_DATA );

    if( stGenSetting.g_BlockSysSetting.vchipSettingCS != checkSum )
    {
        MApp_InitBlockData();
        EE_LOAD(printf("MApp_InitBlockData!\n"));
    }
}

void MApp_SaveBlockData(void)
{
    stGenSetting.g_BlockSysSetting.vchipSettingCS =
        MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_BlockSysSetting), SIZE_BLOCK_DATA );
    MApp_WriteDatabase(RM_BLOCK_DATA_ADDRESS, (BYTE *)&(stGenSetting.g_BlockSysSetting), SIZE_BLOCK_DATA);
    EE_PUTSTR("\n MApp_SaveBlockData!\n");
}
#if ENABLE_GAMMA_ADJUST
void MApp_InitGammaSetting(void)
{
    MApp_DataBase_RestoreDefaultTime();

    MApp_SaveGammaSetting();
}
void MApp_CheckGammaSetting(void)
{
    checkSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_GammaSetting), SIZE_GAMMA_SETTING );
    if( stGenSetting.g_GammaSetting.u16GammaAdjustCS != checkSum )
    {
        MApp_InitGammaSetting();
        EE_LOAD(printf("MApp_InitGammaSetting!\n"));
    }
}

void MApp_LoadGammaSetting(void)
{
    MApp_ReadDatabase(RM_GAMMA_SETTING_ADDRESS, (BYTE *)&(stGenSetting.g_GammaSetting), SIZE_GAMMA_SETTING);
    checkSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_GammaSetting), SIZE_GAMMA_SETTING );
    if( stGenSetting.g_GammaSetting.u16GammaAdjustCS != checkSum )
    {
        MApp_InitGammaSetting();
        EE_LOAD(printf("MApp_InitGammaSetting!\n"));
    }
}

void MApp_SaveGammaSetting(void)
{
    stGenSetting.g_GammaSetting.u16GammaAdjustCS =
    MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_GammaSetting), SIZE_GAMMA_SETTING );
    MApp_WriteDatabase(RM_GAMMA_SETTING_ADDRESS, (BYTE *)&(stGenSetting.g_GammaSetting), SIZE_GAMMA_SETTING);
    EE_PUTSTR("\n MApp_SaveGammaSetting!\n");
}
#endif

//=========SSC SETTING============================
#if ENABLE_SSC
void App_InitSSCData(void)
{
    MApp_DataBase_RestoreDefaultSSC();
    MApp_SaveSSCData();
}

void MApp_CheckSSCData(void)
{
    checkSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_SSCSetting), SIZE_SSC_DATA );

    if( stGenSetting.g_SSCSetting.SscSettingCS != checkSum )
    {
        App_InitSSCData();
        EE_LOAD(printf("App_InitSSCData!\n"));
    }
}

void MApp_LoadSSCData(void)
{
    MApp_ReadDatabase(RM_SSC_DATA_ADDRESS, (BYTE *)&(stGenSetting.g_SSCSetting), SIZE_SSC_DATA);

    checkSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_SSCSetting), SIZE_SSC_DATA );

    if( stGenSetting.g_SSCSetting.SscSettingCS != checkSum )
    {
        App_InitSSCData();
        EE_LOAD(printf("App_InitSSCData!\n"));
    }
}


void MApp_SaveSSCData(void)
{
    stGenSetting.g_SSCSetting.SscSettingCS =
        MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_SSCSetting), SIZE_SSC_DATA );
    MApp_WriteDatabase(RM_SSC_DATA_ADDRESS, (BYTE *)&(stGenSetting.g_SSCSetting), SIZE_SSC_DATA);
    EE_PUTSTR("\n MApp_SaveBlockData!\n");
}
#endif

#if (ENABLE_NONLINEAR_CURVE)
void MApp_InitNonLinearCurveSetting(void)
{
    MApp_DataBase_RestoreDefaultNonLinearCurve();

    MApp_SaveNonLinearCurveSetting();
}

void MApp_CheckNonLinearCurveSetting(void)
{
    checkSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_NonLinearCurveSetting), SIZE_NONLINER_CURVE_SETTING);
    if( stGenSetting.g_NonLinearCurveSetting.NonLinearCurveSettingCS != checkSum )
    {
        MApp_InitNonLinearCurveSetting();
        EE_LOAD(printf("MApp_InitNonLinearCurveSetting()!\n"));
    }
}

void MApp_SaveNonLinearCurveSetting(void)
{
    stGenSetting.g_NonLinearCurveSetting.NonLinearCurveSettingCS = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_NonLinearCurveSetting), SIZE_NONLINER_CURVE_SETTING);
    MApp_WriteDatabase(RM_NONLINER_SETTING_ADDRESS, (BYTE *)&(stGenSetting.g_NonLinearCurveSetting), SIZE_NONLINER_CURVE_SETTING);
    EE_PUTSTR("\n MApp_SaveNonLinearCurveSetting!\n");
}
#endif

//=============================================================================================



#if (ENABLE_LAST_MEMORY==1)&&(ENABLE_LAST_MEMORY_STORAGE_SAVE==1)
void MApp_InitMmLastMemorySetting(void)
{
    MApp_DataBase_RestoreDefaultMmLastMemorySetting();

    MApp_SaveMmLastMemorySetting();
}

void MApp_CheckMmLastMemorySetting(void)
{
    checkSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_MmLastMemorySetting), SIZE_MM_LASTMEMORY_SETTING );

    if( stGenSetting.g_MmLastMemorySetting.MmLastMemorySettignCS != checkSum )
    {
        MApp_InitMmLastMemorySetting();
        EE_LOAD(printf("MApp_InitMmLastMemorySetting!\n"));
    }
}

void MApp_LoadMmLastMemorySetting(void)
{
    MApp_ReadDatabase(RM_MM_LASTMEMORY_SETTING_ADDRESS, (BYTE *)&(stGenSetting.g_MmLastMemorySetting), SIZE_MM_LASTMEMORY_SETTING);
    checkSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_MmLastMemorySetting), SIZE_MM_LASTMEMORY_SETTING);
    if( stGenSetting.g_MmLastMemorySetting.MmLastMemorySettignCS != checkSum )
    {
        MApp_InitMmLastMemorySetting();
        EE_LOAD(printf("MApp_InitMmLastMemorySetting!\n"));
    }
}

void MApp_SaveMmLastMemorySetting(void)
{
    stGenSetting.g_MmLastMemorySetting.MmLastMemorySettignCS = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_MmLastMemorySetting), SIZE_MM_LASTMEMORY_SETTING);
    MApp_WriteDatabase(RM_MM_LASTMEMORY_SETTING_ADDRESS, (BYTE *)&stGenSetting.g_MmLastMemorySetting,SIZE_MM_LASTMEMORY_SETTING);
    EE_PUTSTR("\n MApp_SaveMmLastMemorySetting!\n");
}
#endif

//*************************************************************************
// General Setting Checking Fucntion === Start
//*************************************************************************
void MApp_GenSetting_DataCheckHandler(void)
{
    U16 u16CheckSum;
    EN_TOP_STATE enCurTopState;


    // Repeat key is coming
    if( MApp_KeyIsReapeatStatus() == TRUE )
        return;


    enCurTopState = MApp_TopStateMachine_GetTopState();

    // If in auto scan, return
#if 1
    if( MApp_Is_InAutoScan_DTV() || MApp_Is_InAutoScan_ATV() )
        return;
#else
    if( (enCurTopState == STATE_TOP_ATV_SCAN)
    #if ENABLE_DVB
      ||(enCurTopState == STATE_TOP_DTV_SCAN)
      #endif
    #if ENABLE_SBTVD_ATV_SYSTEM
      ||(enCurTopState == STATE_TOP_CATV_SCAN)
    #endif
      )
        return;
#endif

    // Check OSD status??
    //if( _eActiveOSD==E_OSD_EMPTY) && (_eZUIState==E_ZUI_STATE_STANDBY)
    //printf("_eZUIState=%u\n", MApp_ZUI_GetState());
    //printf("_eActiveOSD=%u\n", MApp_ZUI_GetActiveOSD());


    // Check time period
    if( msAPI_Timer_DiffTimeFromNow(su32DataSavePeriod) < CHECK_DATA_CHANGED_PERIOD )
    {
        return;
    }

    su32DataSavePeriod = msAPI_Timer_GetTime0();



    // Check variable checksum,
    // If checksum changed, save data to dram...

    // Check System setting
    //u16CheckSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_SysSetting), SIZE_SYS_SETTING );
    //u16CheckSum = MApp_SysSetting_CalChecksum();
    //if( stGenSetting.g_SysSetting.SystemSettingCS != u16CheckSum )
    if( FALSE == MApp_SysSetting_IfCheckSumCorrect() )
    {
        DEBUG_DATA_CHECK_HANDLER( printf("g_SysSetting changed!\n"); );
        MApp_SaveSysSetting();
    }

    // Check g_SoundSetting
    u16CheckSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_SoundSetting), SIZE_SOUND_SETTING );
    if( stGenSetting.g_SoundSetting.soundSettingCS != u16CheckSum )
    {
        DEBUG_DATA_CHECK_HANDLER( printf("g_SoundSetting changed!\n"); );
        MApp_SaveSoundSetting();
    }

    // Check g_astVideo
    MApp_SaveData_Video_CheckIfDataChanged();

    // Check g_Time
    u16CheckSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_Time), SIZE_TIME_DATA );
    if( stGenSetting.g_Time.wTimeDataCS != u16CheckSum )
    {
        DEBUG_DATA_CHECK_HANDLER( printf("g_Time changed!\n"); );
        MApp_SaveTimeData();
    }

    // Check g_BlockSysSetting
    u16CheckSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_BlockSysSetting), SIZE_BLOCK_DATA );
    if( stGenSetting.g_BlockSysSetting.vchipSettingCS != u16CheckSum )
    {
        DEBUG_DATA_CHECK_HANDLER( printf("g_BlockSysSetting changed!\n"); );
        MApp_SaveBlockData();
    }


    // Check PcMode
    /*
    if( sbPcModeSaveFlag == TRUE )
    {
        sbPcModeSaveFlag = FALSE;
        DEBUG_DATA_CHECK_HANDLER( printf("PcModeSetting changed!\n"); );

#if (ENABLE_PIP)
        if((MApp_Get_PIPMode() != EN_PIP_MODE_OFF)&& (IsSrcTypeVga(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))||IsSrcTypeYPbPr(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))))
        {
            MApp_PCMode_SaveModeRamSetting(SUB_WINDOW);
        }
        else
#endif
        {
            MApp_PCMode_SaveModeRamSetting(MAIN_WINDOW);
        }
    }
    */


    // Check stScanMenuSetting
    u16CheckSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.stScanMenuSetting), SIZE_SCANMENU_SETTING );
    if( stGenSetting.stScanMenuSetting.ScanMenuSettingCS != u16CheckSum )
    {
        DEBUG_DATA_CHECK_HANDLER( printf("stScanMenuSetting changed!\n"); );
        MApp_SaveScanMenuSetting();
    }

#if ENABLE_GAMMA_ADJUST
    u16CheckSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_GammaSetting), SIZE_GAMMA_SETTING );
    if( stGenSetting.g_GammaSetting.u16GammaAdjustCS != u16CheckSum )
    {
        DEBUG_DATA_CHECK_HANDLER( printf("g_GammaSetting changed!\n"); );
        MApp_SaveGammaSetting();
    }
#endif

    // Check g_stPipSetting
#if (ENABLE_PIP)
    //In some cases, system data & PIP data will be changed at the same time;
    //  and caused data reloading and some abnormal situations occured.
    //  ex. PIP is enabled, do auto-scan in DTV src.
    u16CheckSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_stPipSetting), SIZE_PIP_DATA);
    if( stGenSetting.g_stPipSetting.PIPSetupInfoCS != u16CheckSum )
    {
        DEBUG_DATA_CHECK_HANDLER( printf("g_stPipSetting changed!\n"); );
        MApp_SavePipSetting();
    }
#endif

    // Check g_Network_TS
#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
    u16CheckSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_Network_TS), SIZE_NETWORK_INFO_DATA);
    if( stGenSetting.g_Network_TS.NetWorkInfoCS!= u16CheckSum )
    {
        DEBUG_DATA_CHECK_HANDLER( printf("g_Network_TS changed!\n"); );
        MApp_SaveNetworkInfoSetting();
    }
#endif

    // Check g_CISetting
#if (ENABLE_CI )
    if( stGenSetting.g_CISetting.CISettingCS != MApp_CiSetting_CalCheckSum() )
    {
        DEBUG_DATA_CHECK_HANDLER( printf("g_CISetting changed!\n"); );
        MApp_SaveCISetting();
    }
#endif

    // Check g_CIKeySetting
#if (ENABLE_CI && ENABLE_CI_PLUS)
    if( DB_CI_PLUS_SETTING.CIKeyCS != MApp_CiPlusSetting_CalCheckSum() )
    {
        DEBUG_DATA_CHECK_HANDLER( printf("g_CIKeySetting changed!\n"); );
        MApp_SaveCIPlusSetting();
    }
#endif

    // Check g_MmLastMemorySetting
#if (ENABLE_LAST_MEMORY==1)&&(ENABLE_LAST_MEMORY_STORAGE_SAVE==1)
    u16CheckSum = MApp_CalCheckSum_SkipFirst2Byte((BYTE *)&(stGenSetting.g_MmLastMemorySetting), SIZE_MM_LASTMEMORY_SETTING);
    if( stGenSetting.g_MmLastMemorySetting.MmLastMemorySettignCS!= u16CheckSum )
    {
        DEBUG_DATA_CHECK_HANDLER( printf("g_MmLastMemorySetting changed!\n"); );
        MApp_SaveMmLastMemorySetting();
    }
#endif


    // Check all genSetting child setting
    MApp_SaveData_Check_IfDataChanged(E_SAVE_DATA_ID_GEN_ALL);


#if( ENABLE_FACTORY_SETTING_IN_SEPERATE_BANK == FALSE )
    // Check factory setting
    if( MApp_DB_Factory_CheckIfDataChanged() )
    {
        //DEBUG_DATA_CHECK_HANDLER( printf(" changed!\n"); );
    }
#endif

}

//========================================

#define DEBUG_SAVE_PCMODE(x)    //x

void MApp_SetSaveModeDataFlag(void)
{
    //sbPcModeSaveFlag = TRUE;
    DEBUG_SAVE_PCMODE( printf("MApp_SetSaveModeDataFlag()\n"); );

#if (ENABLE_PIP)
    if( (MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
       &&(IsSrcTypeVga(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))||IsSrcTypeYPbPr(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
      )
    {
        MApp_PCMode_SaveModeRamSetting(SUB_WINDOW);
    }
    else
#endif
    {
        MApp_PCMode_SaveModeRamSetting(MAIN_WINDOW);
    }
}

void MApp_DataInitVariable(void)
{
//    sbPcModeSaveFlag = FALSE;
    su32DataSavePeriod = msAPI_Timer_GetTime0();
#if(ASTRA_HD_ENABLE)
    msAPI_CM_SetCurrentServiceListID(stGenSetting.g_SysSetting.u8ServiceListID);
#endif

}
//*************************************************************************
// General Setting Checking Fucntion === End
//*************************************************************************

//*************************************************************************
//Function name:    MApp_DB_LoadModeSetting
//Passing parameter:    U8 u8ModeIndex: mode index
//Return parameter:     none
//Description:      Load mode setting from SDRAM to XDATASDRAM
//*************************************************************************

#if( DB_PC_MODE_SAVE_TO_DB_GEN )
    #define RM_MODE_SETTING_ADDR(i) (RM_GENSET_START_ADR + (U32)&(((MS_GENSETTING*)0)->stDBPcModeSetting.astMsPcAdcModeSetting[i]) )
    //#define RM_MODE_SETTING_ADDR(i) (RM_GEN_MODE_SETTING_START_ADR + (U32)&(((Stru_DB_PcModeSetting*)0)->astMsPcAdcModeSetting[i]) )
#else
    #define RM_MODE_SETTING_ADDR(i) (RM_MODE_SETTING_START_ADR + i*sizeof(MS_PCADC_MODESETTING_TYPE))
#endif
void MApp_DB_LoadModeSetting ( SCALER_WIN eWindow, U8 u8ModeIndex )
{
    DEBUG_SAVE_PCMODE( printf("MApp_DB_LoadModeSetting(u8ModeIndex=%u)\n", u8ModeIndex); );

    if( u8ModeIndex >= MAX_MODE_NUM )
    {
        printf("\nError: Mode index=%u is invalid!\n", u8ModeIndex);
        return;
    }

#if( DB_PC_MODE_SAVE_TO_DB_GEN )

    memcpy( (U8*)&g_PcadcModeSetting[eWindow],
            (U8*)&(stGenSetting.stDBPcModeSetting.astMsPcAdcModeSetting[u8ModeIndex]),
            sizeof(MS_PCADC_MODESETTING_TYPE));

#else
    MApp_ReadDatabase( RM_MODE_SETTING_ADDR(u8ModeIndex),
                (BYTE *)&g_PcadcModeSetting[eWindow],
                sizeof(MS_PCADC_MODESETTING_TYPE));
#endif
}
//*************************************************************************
//Function name:    MApp_DB_SaveModeSetting
//Passing parameter:    U8 u8ModeIndex: mode index
//Return parameter:     none
//Description:      Save mode setting from XDATSDRAM to SDRAM
//*************************************************************************
void MApp_DB_SaveModeSetting ( SCALER_WIN eWindow, U8 u8ModeIndex )
{
    DEBUG_SAVE_PCMODE( printf("MApp_DB_SaveModeSetting(u8ModeIndex=%u)\n", u8ModeIndex); );

    if( u8ModeIndex >= MAX_MODE_NUM )
    {
        printf("\nError: Mode index=%u is invalid!\n", u8ModeIndex);
        return;
    }

#if( DB_PC_MODE_SAVE_TO_DB_GEN )
    memcpy( (U8*)&(stGenSetting.stDBPcModeSetting.astMsPcAdcModeSetting[u8ModeIndex]),
            (U8*)&g_PcadcModeSetting[eWindow],
            sizeof(MS_PCADC_MODESETTING_TYPE));
#else
    MApp_WriteDatabase(
        RM_MODE_SETTING_ADDR(u8ModeIndex),
        (BYTE *)&g_PcadcModeSetting[eWindow],
        sizeof(MS_PCADC_MODESETTING_TYPE));
#endif
}

void MApp_DB_LoadDefaultTable( SCALER_WIN eWindow, U8 u8ModeIndex)
{
    MS_PCADC_MODETABLE_TYPE_EX sModeTbl;

    DEBUG_SAVE_PCMODE( printf("MApp_DB_LoadDefaultTable(u8ModeIndex=%u)\n", u8ModeIndex); );

    MApi_XC_ModeParse_GetModeTbl(u8ModeIndex, &sModeTbl);

    g_PcadcModeSetting[eWindow].u8ModeIndex = u8ModeIndex;
    g_PcadcModeSetting[eWindow].u16HorizontalStart = sModeTbl.u16HorizontalStart;
    g_PcadcModeSetting[eWindow].u16VerticalStart = sModeTbl.u16VerticalStart;
    g_PcadcModeSetting[eWindow].u16HorizontalTotal = sModeTbl.u16HorizontalTotal;
    g_PcadcModeSetting[eWindow].u16Phase = sModeTbl.u16AdcPhase;
    g_PcadcModeSetting[eWindow].u16DefaultHStart = g_PcadcModeSetting[eWindow].u16HorizontalStart;
    g_PcadcModeSetting[eWindow].u16DefaultVStart = g_PcadcModeSetting[eWindow].u16VerticalStart;
    g_PcadcModeSetting[eWindow].u16DefaultHTotal = g_PcadcModeSetting[eWindow].u16HorizontalTotal;
    g_PcadcModeSetting[eWindow].u8SyncStatus = sModeTbl.u8StatusFlag;
    g_PcadcModeSetting[eWindow].u8AutoSign = 0;
}

//*************************************************************************
//Function name:    MApp_DB_RestoreAllModeTable
//Passing parameter:    none
//Return parameter:     none
//Description:      Load default standard mode settings to SDRAM
//*************************************************************************
void MApp_RestoreAllModeTable(SCALER_WIN eWindow)
{
    U8 u8Loop;
    U8 NumberOfItems= MApi_XC_GetTotalModeCount();

    DEBUG_SAVE_PCMODE( printf("MApp_RestoreAllModeTable()\n"); );


    for(u8Loop = 0 ; u8Loop < NumberOfItems ; u8Loop++)
    {
        MApp_DB_LoadDefaultTable(eWindow, u8Loop);

        MApp_DB_SaveModeSetting(eWindow, u8Loop);
    }

    for(u8Loop = 0 ; u8Loop < MAX_USER_MODE_NUM ; u8Loop++)
    {
        g_PcadcModeSetting[eWindow].u8ModeIndex = 0xFF;

        g_PcadcModeSetting[eWindow].u16HorizontalStart = 0xFF;
        g_PcadcModeSetting[eWindow].u16VerticalStart = 0xFF;
        g_PcadcModeSetting[eWindow].u16HorizontalTotal = 0xFF;
        g_PcadcModeSetting[eWindow].u16Phase = 0x3FF;
        g_PcadcModeSetting[eWindow].u16DefaultHStart = 0xFF;
        g_PcadcModeSetting[eWindow].u16DefaultVStart = 0xFF;
        g_PcadcModeSetting[eWindow].u16DefaultHTotal = 0xFF;
        g_PcadcModeSetting[eWindow].u8SyncStatus = 0xFF;
        g_PcadcModeSetting[eWindow].u8AutoSign = 0;
        MApp_DB_SaveModeSetting(eWindow, u8Loop+NumberOfItems);
    }

    stGenSetting.g_SysSetting.NextNewRamIndex = 0; // user mode index

    MApp_SaveSysSetting();
}

void MApp_RestorePCModeTable(SCALER_WIN eWindow)
{
    U8 u8Loop;
    U8 NumberOfItems = MApi_XC_GetTotalModeCount();

    DEBUG_SAVE_PCMODE( printf("MApp_RestorePCModeTable()\n"); );


    for(u8Loop = 0 ; u8Loop < MIN_STD_COMPO_NUM ; u8Loop++)
    {
        MApp_DB_LoadDefaultTable(eWindow, u8Loop);

        MApp_DB_SaveModeSetting(eWindow, u8Loop);
    }
    for(u8Loop = MAX_STD_COMPO_NUM+1 ; u8Loop < NumberOfItems ; u8Loop++)
    {
        MApp_DB_LoadDefaultTable(eWindow, u8Loop);

        MApp_DB_SaveModeSetting(eWindow, u8Loop);
    }
    for(u8Loop = 0 ; u8Loop < MAX_USER_MODE_NUM ; u8Loop++)
    {
        g_PcadcModeSetting[eWindow].u8ModeIndex = 0xFF;

        g_PcadcModeSetting[eWindow].u16HorizontalStart = 0xFF;
        g_PcadcModeSetting[eWindow].u16VerticalStart = 0xFF;
        g_PcadcModeSetting[eWindow].u16HorizontalTotal = 0xFF;
        g_PcadcModeSetting[eWindow].u16Phase = 0x3FF;
        g_PcadcModeSetting[eWindow].u16DefaultHStart = 0xFF;
        g_PcadcModeSetting[eWindow].u16DefaultVStart = 0xFF;
        g_PcadcModeSetting[eWindow].u16DefaultHTotal = 0xFF;
        g_PcadcModeSetting[eWindow].u8SyncStatus = 0xFF;
        g_PcadcModeSetting[eWindow].u8AutoSign = 0;
        MApp_DB_SaveModeSetting(eWindow, u8Loop+NumberOfItems);
    }
    stGenSetting.g_SysSetting.NextNewRamIndex = 0; // user mode index
    MApp_SaveSysSetting();
}

void MApp_RestoreComponentModeTable(void)
{
    U8 u8Loop;

    DEBUG_SAVE_PCMODE( printf("MApp_RestoreComponentModeTable()\n"); );

    for(u8Loop = MIN_STD_COMPO_NUM ; u8Loop < MAX_STD_COMPO_NUM+1 ; u8Loop++)
    {
      #if (ENABLE_PIP)
        if((MApp_Get_PIPMode() != EN_PIP_MODE_OFF)&&(IsSrcTypeVga(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))&&IsSrcTypeVga(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))))
        {
            MApp_DB_LoadDefaultTable(SUB_WINDOW, u8Loop);

            MApp_DB_SaveModeSetting(SUB_WINDOW, u8Loop);
        }
        else
      #endif
        {
            MApp_DB_LoadDefaultTable(MAIN_WINDOW, u8Loop);

            MApp_DB_SaveModeSetting(MAIN_WINDOW, u8Loop);
        }
    }
    MApp_SaveSysSetting();
}


#if ENABLE_SZ_FACTORY_OVER_SCAN_FUNCTION
static U32 wRmOverscanAddress;
code MS_OVERSCAN_SETTING tOVerScanInitValue[EN_FACTORY_OverScan_NUM]=
{
/*OverScanHRatio; OverScanHposition; OverScanVRatio; OverScanVposition*/
#if( CHIP_FAMILY_NASA == CHIP_FAMILY_TYPE )
//ATV
    {0, 40, 38, 20, 28},//NTSC
    {0, 42, 42, 18, 18},//PAL
    {0, 25, 25, 13, 13},//SECAM
    {0, 25, 25, 11, 11},//NTSC443
    {0, 22, 22, 11, 11},//PALM
    {0, 25, 25, 14, 14},//PALN
//AV
    {0, 40, 38, 20, 28},//NTSC
    {0, 42, 42, 18, 18},//PAL
    {0, 25, 25, 13, 13},//SECAM
    {0, 25, 25, 11, 11},//NTSC443
    {0, 22, 22, 11, 11},//PALM
    {0, 25, 25, 14, 14},//PALN

#elif( CHIP_FAMILY_WHISKY == CHIP_FAMILY_TYPE )
//ATV
  {0, 40, 0, 20, 28},//NTSC
  {0, 40, 0, 18, 18},//PAL
  {0, 25, 0, 13, 13},//SECAM
  {0, 25, 0, 11, 11},//NTSC443
  {0, 22, 0, 11, 11},//PALM
  {0, 25, 0, 14, 14},//PALN
//AV

  {0,40,  6, 20,  2},//NTSC
	{0,42, 42, 18, 18},//PAL
	{0,25, 25, 13, 13},//SECAM
	{0,25, 25, 11, 11},//NTSC443
	{0,22, 22, 11, 11},//PALM
	{0,25, 25, 14, 14},//PALN

#else  // Milan and Other chip
//ATV
    {0, 40, 0, 20, 28},//NTSC
    {0, 40, 0, 18, 18},//PAL
    {0, 25, 0, 13, 13},//SECAM
    {0, 25, 0, 11, 11},//NTSC443
    {0, 22, 0, 11, 11},//PALM
    {0, 25, 0, 14, 14},//PALN
//AV
    {0, 40, 0, 20, 28},//NTSC
    {0, 40, 0, 18, 18},//PAL
    {0, 25, 0, 13, 13},//SECAM
    {0, 25, 0, 11, 11},//NTSC443
    {0, 22, 0, 11, 11},//PALM
    {0, 25, 0, 14, 14},//PALN
#endif

//SV
    {0, 40, 38, 20, 28},//NTSC
    {0, 42, 42, 18, 18},//PAL
    {0, 25, 25, 13, 13},//SECAM
    {0, 25, 25, 11, 11},//NTSC443
    {0, 22, 22, 11, 11},//PALM
    {0, 25, 25, 14, 14},//PALN

//SCART-RGB
    {0, 40, 38, 20, 28},//NTSC
    {0, 42, 42, 18, 18},//PAL
    {0, 25, 25, 13, 13},//SECAM
    {0, 25, 25, 11, 11},//NTSC443
    {0, 22, 22, 11, 11},//PALM
    {0, 25, 25, 14, 14},//PALN

//HDMI
    {0, 16, 0, 13, 0},//480I
    {0, 16, 0, 13, 0},//480P
    {0, 50, 0, 20, 0},//1440*480I
    {0, 50, 0, 20, 0},//1440*480P
    {0, 12, 0, 12, 0},//576I
    {0, 50, 0, 20, 0},//576P
    {0, 50, 0, 20, 0},//1440*576I
    {0, 50, 0, 20, 0},//1440*576P
    {0, 0, 0, 0, 0},//720P
    {0, 0, 0, 0, 0},//1080I
    {0, 0, 0, 0, 0},//1080P

    {0,  0,  0,  0,  0},//Default// for some VESA timing

#if( CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA )
//YPBPR
    {0,  5,  0, 15,  0},//480I
    {0, 50, 50, 20, 20},//480P
    {0, 40, 40, 20, 20},//576I
    {0, 50, 50, 20, 20},//576P
    {0, 10, 10, 10, 10},//720P50
    {0, 10, 10, 10, 10},//720P60
    {0, 10, 10, 10, 10},//1080I50
    {0, 10, 10, 10, 10},//1080I60
#else
//YPBPR
    {0, 32, 41, 20, 33},//480I
    {0, 50, 50, 20, 20},//480P
    {0, 40, 40, 20, 20},//576I
    {0, 50, 50, 20, 20},//576P
    {0, 10, 10, 10, 10},//720P50
    {0, 10, 10, 10, 10},//720P60
    {0, 10, 10, 10, 10},//1080I50
    {0, 10, 10, 10, 10},//1080I60
#endif
#if (SUPPORT_EURO_HDTV)
    {0, 10, 10, 10, 10},//1080I50EURO
#endif

    {0, 10, 10, 10, 10},//1080P24
    {0, 10, 10, 10, 10},//1080P25
    {0, 10, 10, 10, 10},//1080P30

    {0, 10, 10, 10, 10},//1080P50
    {0, 10, 10, 10, 10},//1080P60
//DTV MPEG
    {0, 12,  0, 28,  0},//480i
    {0, 12,  0, 28,  0},//480P
    {0, 12,  0, 28,  0},//576i **
    {0, 12,  0, 28,  0},//576P
    {0, 22,  2, 28,  0},//720P
    {0, 22,  2, 28,  0},//1080i**
    {0, 22,  2, 28,  0},//1080P
//DTV H264
    {0, 12,  0,  6,  0},//480i
    {0, 12,  0,  6,  0},//480P
    {0, 12,  0,  6,  0},//576i **
    {0, 12,  0,  6,  0},//576P
    {0, 22,  2,  6,  0},//720P
    {0, 22,  2,  6,  0},//1080i**
    {0, 22,  2,  6,  0},//1080P
};
U32 CalculatorOverScanAddress(void)
{

    U32 wRmAddress=0;

    if(IsATVInUse())
    {
        wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+mvideo_vd_get_videosystem()*SIZE_OVERSCAN_DATA);
    }
    else if(IsAVInUse())
    {
        wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+(mvideo_vd_get_videosystem()+EN_FACTORY_OverScan_AVNTSC)*SIZE_OVERSCAN_DATA);
    }
    else if(IsSVInUse())
    {
        wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+(mvideo_vd_get_videosystem()+EN_FACTORY_OverScan_SVNTSC)*SIZE_OVERSCAN_DATA);
    }

#if (INPUT_SCART_VIDEO_COUNT > 0)
    else if(IsScartInUse())//scart1
    {
        SCART_SOURCE_TYPE _ScarSrcTypeTemp = E_SCART_SRC_TYPE_UNKNOWN;

        if(IsSrcTypeScart(INPUT_SOURCE_SCART))
        {
            if(msAPI_AVD_GetScart1SrcType())
                _ScarSrcTypeTemp = E_SCART_SRC_TYPE_RGB;
            else
            {
                if(IsSrcTypeScart(INPUT_SOURCE_SCART))
                {
                    _ScarSrcTypeTemp = E_SCART_SRC_TYPE_CVBS;
                }
                else
                {
                    switch (stGenSetting.g_SysSetting.fSCARTInputSel)
                    {
                        case EN_SCART_SEL_AV:
                            _ScarSrcTypeTemp = E_SCART_SRC_TYPE_CVBS;
                            break;
                        case EN_SCART_SEL_SV:
                            _ScarSrcTypeTemp = E_SCART_SRC_TYPE_SVIDEO;
                            break;
                        default:
                            _ScarSrcTypeTemp = E_SCART_SRC_TYPE_UNKNOWN;
                            break;
                    }
                }
            }
        }
    #if (INPUT_SCART_VIDEO_COUNT == 2)
        else if(IsSrcTypeScart(INPUT_SOURCE_SCART2))//scart2
        {
            _ScarSrcTypeTemp = E_SCART_SRC_TYPE_CVBS;
            //_ScarSrcTypeTemp = msAPI_VD_GetScart2SrcType();
        }
    #endif //end of (INPUT_SCART_VIDEO_COUNT == 2)

        //printf("_ScarSrcTypeTemp=%u\n", _ScarSrcTypeTemp);
        //printf("Force overscan use Scart-CVBS\n");
        //_ScarSrcTypeTemp=E_SCART_SRC_TYPE_CVBS;

        switch(_ScarSrcTypeTemp)
        {
            case E_SCART_SRC_TYPE_CVBS:
                wRmAddress = (U32)(RM_OVERSCAN_DATA_START_ADR + (mvideo_vd_get_videosystem()+EN_FACTORY_OverScan_AVNTSC) * SIZE_OVERSCAN_DATA); //morgan.smc as av setting.
                break;
            case E_SCART_SRC_TYPE_RGB:
                //To get a table for Scart RGB, if need
                //printf("g_VdInfo.ucVideoSystem is %u\n",mvideo_vd_get_videosystem());
                //wRmAddress = (U32)(RM_OVERSCAN_DATA_START_ADR + (mvideo_vd_get_videosystem() + EN_FACTORY_OverScan_SCARTRGB_NTSC)*SIZE_OVERSCAN_DATA);
                wRmAddress = (U32)(RM_OVERSCAN_DATA_START_ADR + (mvideo_vd_get_videosystem()+EN_FACTORY_OverScan_AVNTSC) * SIZE_OVERSCAN_DATA); //morgan.smc as av setting.
                break;
            case E_SCART_SRC_TYPE_SVIDEO:
                wRmAddress = (U32)(RM_OVERSCAN_DATA_START_ADR + (mvideo_vd_get_videosystem()+ EN_FACTORY_OverScan_SVNTSC)*SIZE_OVERSCAN_DATA);
                break;
            case E_SCART_SRC_TYPE_UNKNOWN:
            default:
                break;
        }
    }
#endif //end of (INPUT_SCART_VIDEO_COUNT > 0)
    else if( IsHDMIInUse()&& (g_HdmiPollingStatus.bIsHDMIMode == TRUE))
    {
        U16 u16HSize = MApp_PCMode_Get_HResolution(MAIN_WINDOW,FALSE);
        U16 u16VSize = MApp_PCMode_Get_VResolution(MAIN_WINDOW,FALSE);
        BOOL bInterlace;
        bInterlace = MApi_XC_PCMonitor_GetSyncStatus(MAIN_WINDOW) & XC_MD_INTERLACE_BIT ? TRUE : FALSE;

        if((u16HSize>=710 && u16HSize<=730) && (u16VSize>=470 && u16VSize<=490))
        {// 720
            if(bInterlace)
            {// 480i
                wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+EN_FACTORY_OverScan_HDMI480I*SIZE_OVERSCAN_DATA);
            }
            else
            {// 480p
                wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+EN_FACTORY_OverScan_HDMI480P*SIZE_OVERSCAN_DATA);
            }
        }
        else if((u16HSize>=710 && u16HSize<=730) && (u16VSize>=566 && u16VSize<=586))
        {// 720
            if(bInterlace)
            {// 576i
                wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+EN_FACTORY_OverScan_HDMI576I*SIZE_OVERSCAN_DATA);
            }
            else
            {// 576p
                wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+EN_FACTORY_OverScan_HDMI576P*SIZE_OVERSCAN_DATA);
            }
        }
        else if((u16HSize>=1430 && u16HSize<=1450) && (u16VSize>=470 && u16VSize<=490))
        {// 1440
            if(bInterlace)
            {// 480i
                wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+EN_FACTORY_OverScan_HDMI1440_480I*SIZE_OVERSCAN_DATA);
            }
            else
            {// 480p
                wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+EN_FACTORY_OverScan_HDMI1440_480P*SIZE_OVERSCAN_DATA);
            }
        }
        else if((u16HSize>=1430 && u16HSize<=1450) && (u16VSize>=566 && u16VSize<=586))
        {// 1440
            if(bInterlace)
            {// 576I
                wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+EN_FACTORY_OverScan_HDMI1440_576I*SIZE_OVERSCAN_DATA);
            }
            else
            {//576P
                wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+EN_FACTORY_OverScan_HDMI1440_576P*SIZE_OVERSCAN_DATA);
            }
        }
        else if((u16HSize>=1270 && u16HSize<=1290) && (u16VSize>=710 && u16VSize<=730))
        {// 1280
            // 720P
            wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+EN_FACTORY_OverScan_HDMI720P*SIZE_OVERSCAN_DATA);
        }
        else if((u16HSize>=1910 && u16HSize<=1930) && (u16VSize>=1070 && u16VSize<=1090))
        {// 1920
            if (bInterlace)
            {//1080i
                wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+EN_FACTORY_OverScan_HDMI1080I*SIZE_OVERSCAN_DATA);
            }
            else
            {// 1080P
                wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+EN_FACTORY_OverScan_HDMI1080P*SIZE_OVERSCAN_DATA);
            }
        }
        else//default
        {
            wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+EN_FACTORY_OverScan_HDMIDefault*SIZE_OVERSCAN_DATA);
        }
    }
    else if(IsYPbPrInUse())
    {
        wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+(g_PcadcModeSetting[MAIN_WINDOW].u8ModeIndex -MD_720x480_60I+EN_FACTORY_OverScan_YPBPR480I)*SIZE_OVERSCAN_DATA);
    }
    else if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) ||
    (IsSrcTypeStorage(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) && !IsSrcTypeJpeg(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))) // storage type except JPEG
    {
        U16 u16HSize,u16VSize;
        U8 bInterlace;
        msAPI_VID_GetVidInfo(&gstVidStatus);
        // if( TRUE == msAPI_VID_GetVidInfo(&gstVidStatus))
        {
            u16HSize = gstVidStatus.u16HorSize;
            u16VSize = gstVidStatus.u16VerSize;
            bInterlace = gstVidStatus.u8Interlace;
        }
        if(IS_HVD_CODEC(msAPI_VID_GetCodecType()))
        {
            if(u16HSize <= 750 && u16VSize <= 500)
            {
                if(bInterlace)//(g_DisplayWindowSetting.u8DisplayStatus & DISPLAYWINDOW_INTERLACE)
                {// 480i
                    wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+EN_FACTORY_OverScan_H264_DTV480I*SIZE_OVERSCAN_DATA);
                }
                else
                {// 480p
                    wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+EN_FACTORY_OverScan_H264_DTVR480P*SIZE_OVERSCAN_DATA);
                }
            }
            else if(u16HSize <= 750 && u16VSize <= 600)
            {
                if(bInterlace)// (g_DisplayWindowSetting.u8DisplayStatus & DISPLAYWINDOW_INTERLACE)
                {// 576i
                    wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+EN_FACTORY_OverScan_H264_DTV576I*SIZE_OVERSCAN_DATA);
                }
                else
                {// 576p
                    wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+EN_FACTORY_OverScan_H264_DTV576P*SIZE_OVERSCAN_DATA);
                }
            }
            else if(u16HSize <= 1300 && u16VSize <= 750)
            {   //720P
                wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+EN_FACTORY_OverScan_H264_DTV720P*SIZE_OVERSCAN_DATA);
            }
            else if(u16HSize <= 1950 && u16VSize <= 1200)
            {
                if (bInterlace)//(g_DisplayWindowSetting.u8DisplayStatus & DISPLAYWINDOW_INTERLACE)
                {//1080i
                    wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+EN_FACTORY_OverScan_H264_DTV1080I*SIZE_OVERSCAN_DATA);
                }
                else
                {// 1080P
                    wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+EN_FACTORY_OverScan_H264_DTV1080P*SIZE_OVERSCAN_DATA);
                }
            }
        }
        else
        {
            if(u16HSize <= 750 && u16VSize <= 500)
            {
                if(bInterlace)//(g_DisplayWindowSetting.u8DisplayStatus & DISPLAYWINDOW_INTERLACE)
                {// 480i
                    wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+EN_FACTORY_OverScan_DTV480I*SIZE_OVERSCAN_DATA);
                }
                else
                {// 480p
                    wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+EN_FACTORY_OverScan_DTVR480P*SIZE_OVERSCAN_DATA);
                }
            }
            else if(u16HSize <= 750 && u16VSize <= 600)
            {
                if(bInterlace)// (g_DisplayWindowSetting.u8DisplayStatus & DISPLAYWINDOW_INTERLACE)
                {// 576i
                    wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+EN_FACTORY_OverScan_DTV576I*SIZE_OVERSCAN_DATA);
                }
                else
                {// 576p
                    wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+EN_FACTORY_OverScan_DTV576P*SIZE_OVERSCAN_DATA);
                }
            }
            else if(u16HSize <= 1300 && u16VSize <= 750)
            {   //720P
                wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+EN_FACTORY_OverScan_DTV720P*SIZE_OVERSCAN_DATA);
            }
            else if(u16HSize <= 1950 && u16VSize <= 1200)
            {
                if (bInterlace)//(g_DisplayWindowSetting.u8DisplayStatus & DISPLAYWINDOW_INTERLACE)
                {//1080i
                    wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+EN_FACTORY_OverScan_DTV1080I*SIZE_OVERSCAN_DATA);
                }
                else
                {// 1080P
                    wRmAddress=(U32)(RM_OVERSCAN_DATA_START_ADR+EN_FACTORY_OverScan_DTV1080P*SIZE_OVERSCAN_DATA);
                }
            }
        }
    }
return wRmAddress;
}

void MApp_InitOverScanData(void)
{
    U8 OverScanIndex;
    //   U32 wRmAddress;
    wRmOverscanAddress = RM_OVERSCAN_DATA_START_ADR;

    for(OverScanIndex=0;OverScanIndex<EN_FACTORY_OverScan_NUM;OverScanIndex++)
    {
        g_OverScan = tOVerScanInitValue[OverScanIndex];
        MApp_SaveOverScanData();
        wRmOverscanAddress += SIZE_OVERSCAN_DATA;
    }
}

#define DEBUG_OVERSCAN(x) //x
void MApp_LoadOverScanData (void)
{
    DEBUG_OVERSCAN( printf("MApp_LoadOverScanData()\n"); );

// U32 wRmAddress;
    wRmOverscanAddress = CalculatorOverScanAddress();
    if(wRmOverscanAddress!=0)
    {
        MApp_ReadDatabase((U32)wRmOverscanAddress, (BYTE *)&g_OverScan, SIZE_OVERSCAN_DATA);
        checkSum = MApp_CalCheckSum((BYTE *)&g_OverScan + 2, SIZE_OVERSCAN_DATA - sizeof(checkSum));
        if( g_OverScan.Checksum != checkSum )
        {
            // Load default and save.
            g_OverScan = tOVerScanInitValue[(wRmOverscanAddress - RM_OVERSCAN_DATA_START_ADR)/SIZE_OVERSCAN_DATA];
            MApp_SaveOverScanData();
        }
    }
    else
    {
        g_OverScan.OverScanHRatio=0;
        g_OverScan.OverScanHposition=0;
        g_OverScan.OverScanVRatio=0;
        g_OverScan.OverScanVposition=0;
    }

    DEBUG_OVERSCAN(printf("g_OverScan.OverScanHRatio=%u\n", g_OverScan.OverScanHRatio););
    DEBUG_OVERSCAN(printf("g_OverScan.OverScanHposition=%u\n", g_OverScan.OverScanHposition););
    DEBUG_OVERSCAN(printf("g_OverScan.OverScanVRatio=%u\n", g_OverScan.OverScanVRatio););
    DEBUG_OVERSCAN(printf("g_OverScan.OverScanVposition=%u\n", g_OverScan.OverScanVposition););
}

void MApp_SaveOverScanData (void )
{
// U32 wRmAddress;
  //   wRmAddress = CalculatorOverScanAddress();
    g_OverScan.Checksum=
        MApp_CalCheckSum((BYTE *)&g_OverScan + 2, SIZE_OVERSCAN_DATA - sizeof(checkSum));
    if (wRmOverscanAddress != 0)// write safe.
    {
        MApp_WriteDatabase((U32)wRmOverscanAddress, (BYTE *)&g_OverScan, SIZE_OVERSCAN_DATA);
    }
}
#endif

#if (ENABLE_SZ_FACTORY_USB_SAVE_DATABASE_FUNCTION == ENABLE || ENABLE_UPGRADE_CIPLUSKEY_BY_USB == ENABLE || ENABLE_UPGRADE_HDCPKEY_BY_USB == ENABLE)
#include "msAPI_FCtrl.h"
#include "IOUtil.h"
#include "mw_usbdownload.h"
#include "msAPI_FSCommon.h"
#include "msAPI_Memory.h"
#include "MApp_FileBrowser.h"
#include "mw_usbdownload.h"

extern BOOLEAN MDrv_UsbDeviceConnect(void);
extern void msAPI_BLoader_Reboot(void);
extern BOOLEAN MApp_UsbSaveData_SearchFileInRoot(U8* pu8FileName, FileEntry* pFileEntry);
extern U8 MDrv_USBGetPortEnableStatus(void);
extern void Mapp_SetCurrentOrderForRestore(void);
#endif

#if (ENABLE_SZ_FACTORY_USB_SAVE_DATABASE_FUNCTION == ENABLE)
#define SW_DATABASE "DATABASE.bin"
static FileEntry g_fileEntry;

static void _MApp_CopyDB2GenSetting(void)
{
    MApp_ReadDatabase(RM_GENSET_START_ADR, (BYTE *)&stGenSetting, RM_SIZE_GENSET);
}

void MApp_BackupDatabase(void)
{
    while (!MDrv_UsbDeviceConnect())
    {
        EE_LOAD(printf("\n init USB__fail \n"));
        return;
    }

    U8 u8PortEnStatus = MDrv_USBGetPortEnableStatus();

    if((u8PortEnStatus & BIT0) == BIT0)
    {
        MApp_UsbSaveData_SetPort(BIT0);
    }
    else if((u8PortEnStatus & BIT1) == BIT1)
    {
        MApp_UsbSaveData_SetPort(BIT1);
    }
    else
    {
        EE_LOAD(printf("Error> Unknown USB port\n"));
        return;
    }

    if (!MApp_UsbSaveData_InitFileSystem())
    {
        MApp_UsbSaveData_Exit();
        EE_LOAD(printf("Exit"));
        return ;
    }

#if (WATCH_DOG == ENABLE)
    msAPI_Timer_ResetWDT();
#endif

    U8 u8HandleNo;
    U8 u8FileName[40] = SW_DATABASE;
    U16 u16FileName[20];

    // step 1  setup environment
    if(MApp_UsbSaveData_SearchFileInRoot((U8 *)u8FileName, &g_fileEntry))
    {
        msAPI_FCtrl_FileDelete(&g_fileEntry);
        EE_LOAD(printf("Found and Deleted\n"));
    }
    else
    {
        EE_LOAD(printf("Not Found\n"));
    }

    // step 2
    ASCIItoUnicode2((S8*)u8FileName, strlen((char *)u8FileName));

    memset(u16FileName, 0, sizeof(u16FileName));

    memcpy(u16FileName, u8FileName, sizeof(u16FileName));

    u8HandleNo = MApp_UsbSaveData_OpenNewFileForWrite((U16 *)u16FileName, UnicodeLen((S8*)u16FileName));

    EE_LOAD( printf("OpenForWrite Passed\n") );

    EE_LOAD( printf("HandleNo is 0x%x\n",u8HandleNo) );
    if(u8HandleNo != FCTRL_INVALID_FILE_HANDLE)
    {
        MApp_SaveGenSetting();      //General setting

        MApp_DB_CH_LoadDataBase();   //Channel list

        EE_LOAD( printf("start  write\n") );
        msAPI_FCtrl_FileWrite(u8HandleNo, RAM_DISK_MEM_ADDR, DATABASE_START_LEN);

        EE_LOAD( printf("Save to file: msAPI_FCtrl_FileClose\n") );
        msAPI_FCtrl_FileClose(u8HandleNo);
    }
}

void MApp_RestoreDatabase(void)
{
    while (!MDrv_UsbDeviceConnect())
    {
        EE_LOAD(printf("init USB fail\n"));
        return ;
    }

    U8 u8PortEnStatus = MDrv_USBGetPortEnableStatus();

    if((u8PortEnStatus & BIT0) == BIT0)
    {
        MApp_UsbSaveData_SetPort(BIT0);
    }
    else if((u8PortEnStatus & BIT1) == BIT1)
    {
        MApp_UsbSaveData_SetPort(BIT1);
    }
    else
    {
        EE_LOAD(printf("Error> Unknown USB port\n"));
        return;
    }

    if (!MApp_UsbSaveData_InitFileSystem())
    {
        MApp_UsbSaveData_Exit();
        EE_LOAD(printf("Exit"));
        return ;
    }

    U8 u8HandleNo;
    U8 u8FileName[20] = SW_DATABASE;

    if (MApp_UsbSaveData_SearchFileInRoot((U8 *)u8FileName, &g_fileEntry))
    {
        u8HandleNo = msAPI_FCtrl_FileOpen(&g_fileEntry, OPEN_MODE_FOR_READ);

        if(u8HandleNo != FCTRL_INVALID_FILE_HANDLE)
        {
            EE_LOAD(printf("current file is exist\r\n"));

            msAPI_FCtrl_FileRead(u8HandleNo, RAM_DISK_MEM_ADDR, DATABASE_START_LEN);

            EE_LOAD( printf("Close file: msAPI_FCtrl_FileClose\n") );
            msAPI_FCtrl_FileClose(u8HandleNo);
        }
        else
        {
            EE_LOAD(printf("Open file fail\n"));
            return;
        }
    }
    else
    {
        EE_LOAD(printf("database file is not exist\r\n"));
        return;
    }

    //store to flash immediately
#if (EEPROM_DB_STORAGE == EEPROM_SAVE_NONE)
    _MApp_CopyDB2GenSetting();

    {
        printf("\n----RestoreDatabase----\n");
    }
    //MApp_DB_SaveNowGenSetting();
    MApp_DB_GEN_SaveData_RightNow();

    //MApp_DB_SaveDataBase();
    MApp_DB_CH_SaveData_RightNow();
#endif

    //while(msAPI_MIU_QuickDataBaseCheck() != TRUE);
    msAPI_Flash_WaitWriteDone(3000);

    MApp_CheckFlash();

    MApp_CheckFlash_DB_CH();

    msAPI_BLoader_Reboot();
}

#endif

#if (ENABLE_UPGRADE_CIPLUSKEY_BY_USB)
extern BOOLEAN Mapp_check_valid_key(void);
BOOLEAN MApp_WriteCiPlus_Key(void)
{

    U8 u8PortEnStatus = 0;
    BOOLEAN bUSBIsConnected = FALSE;
    U8 u8HandleNo = 0;
    U8 u8Len = 0;
    U32 i = 0;
    U32 u32CopySection = 0;
    FileEntry stfileEntry;
    U8 *pu8FileName=NULL;

    u8PortEnStatus = MDrv_USBGetPortEnableStatus();
    printf("\nUSB Port:%bu\n",(u8PortEnStatus & 0x03));
    if((u8PortEnStatus & BIT0) == BIT0)
    {
        if (!MDrv_UsbDeviceConnect())
        {
            MsOS_DelayTask(1000);
        }

        if (!MDrv_UsbDeviceConnect())
        {
            printf("\nNo USB Device1!\n");
            return FALSE;
        }
        MW_UsbDownload_SetUSBPortNo(1);
        bUSBIsConnected = TRUE;
    }

    if((!bUSBIsConnected) && ((u8PortEnStatus & BIT1) == BIT1))
    {
        if (!MDrv_UsbDeviceConnect_Port2())
        {
            MsOS_DelayTask(1000);
        }

        if (!MDrv_UsbDeviceConnect_Port2())
        {
            printf("\nNo USB Device2!\n");
            return FALSE;
        }
        MW_UsbDownload_SetUSBPortNo(2);
        bUSBIsConnected = TRUE;
    }

    // Init USB and file system, ...
    msAPI_Timer_ResetWDT();

    if (!MApp_UsbSaveData_InitFileSystem())
    {
        MApp_UsbSaveData_Exit();
        printf("\nFS Init Fail!\n");
        MApp_FileBrowser_DeInit();
        return FALSE;
    }

    MApp_FileBrowser_Init(0);
    // Search files
    msAPI_Timer_ResetWDT();

    u8Len = strlen("CIPLUSKEY.bin");
    pu8FileName = (U8*)msAPI_Memory_Allocate(u8Len*sizeof(U8)+1, BUF_ID_FILEBROWER);

    if(pu8FileName == NULL)
    {
        printf("\nGet Memory Null! u8\n");
        MApp_FileBrowser_DeInit();
        return FALSE;
    }

    memcpy(pu8FileName, "CIPLUSKEY.bin", u8Len);
    pu8FileName[u8Len]='\0';
    b_isWriteCIkey = TRUE;
    if(MApp_UsbSaveData_SearchFileInRoot((U8 *)(pu8FileName), &stfileEntry))
    {
        u8HandleNo = msAPI_FCtrl_FileOpen(&stfileEntry, OPEN_MODE_FOR_READ);
        b_isWriteCIkey = FALSE;
        b_isCIkeyFileExit = TRUE;
    }
    else
    {
        //printf("\nSearch File Error\n");
        MApp_FileBrowser_DeInit();
        b_isWriteCIkey = FALSE;
        b_isCIkeyFileExit = FALSE;
        return FALSE;
    }
    msAPI_Memory_Free(pu8FileName, BUF_ID_FILEBROWER);
    //printf("\nStart read%bu\n",u8HandleNo);
    if(u8HandleNo != FCTRL_INVALID_FILE_HANDLE)
    {
        //printf("\nSearch File OK\n");

        u32CopySection = 0x1800;//SYSTEM_BANK_SIZE;//6k
        u32CopySection /= 2048;

        for (i = 0; i < u32CopySection; i++)
        {
            msAPI_Timer_ResetWDT();
            msAPI_FCtrl_FileSeek(u8HandleNo, i*2048, FILE_SEEK_SET);
            msAPI_FCtrl_FileRead(u8HandleNo, (CIPLUST_KEY_BUFFER_ADR + i*2048), 2048);
            //Copy2kbFromMemPoolToDb(i * 2048);
        }
        msAPI_FCtrl_FileClose(u8HandleNo);
    }
    else
    {
        //printf("\n FCTRL_INVALID_FILE_HANDLE\n");
    }


    // Disable write protect
    U32 u32DramAddr = (((CIPLUST_KEY_BUFFER_MEMORY_TYPE & MIU1) ? (CIPLUST_KEY_BUFFER_ADR | MIU_INTERVAL) : (CIPLUST_KEY_BUFFER_ADR)));
    U32 u32DramDataSize = CIPLUST_KEY_BUFFER_LEN;
    U32 u32FlashAddr = 0x10000ul * CIPLUS_KEY_BANK;
    U32 u32EraseSize = 0x10000;

    msAPI_Flash_WaitWriteDone(3000);

    msAPI_Flash_Set_WriteProtect_Disable_Range(u32FlashAddr, u32EraseSize);

    // Erase flash and wait done
    MDrv_FLASH_AddressErase(u32FlashAddr, u32EraseSize, TRUE);

    //while(msAPI_MIU_QuickDataBaseCheck() != TRUE);
    msAPI_Flash_WaitWriteDone(3000);

    // Write date to flash
    msAPI_Flash_StoreDramData2Flash( u32FlashAddr, u32DramAddr, u32DramDataSize, FALSE);    // SRAM2Flash

    // Enable write protect
    msAPI_Flash_Set_WriteProtect(ENABLE);

    if(Mapp_check_valid_key())//move to [USED]
    {
        //printf("\n delete");
        if (msAPI_FCtrl_FileClose(u8HandleNo) == FILE_CLOSE_RESULT_ERROR)
        {
            //printf("\n close error");
            MApp_FileBrowser_DeInit();
            return FALSE;
        }

        //if (!msAPI_FCtrl_FileDelete(&stfileEntry))
        if (!MApp_FileBrowser_DeleteFileByFileEntry(&stfileEntry))
        {
            //printf("\n del error");
            MApp_FileBrowser_DeInit();
            return FALSE;
        }
    }
    MApp_FileBrowser_DeInit();
    return TRUE;
}
#endif

#if (ENABLE_UPGRADE_HDCPKEY_BY_USB)
static U16 g_u16HDCPKey_Pos = 0;
#define HDCP_KEY_HEADER_LEN 16
#define HDCP_KEY_LEN         304
#define HDCP_KEY_ALL_LEN    3072

U16 DEC_TO_HEX(U16 u16DecValue)
{
    U16 u16HexValue_Integer = 0;
    U16 u16HexValue_Remainder = 0;
    U16 u16HexValue = 0;

    u16HexValue_Integer = u16DecValue/16;
    if(u16DecValue%16 < 10)
    {
        u16HexValue_Remainder = u16DecValue%16;
    }
    else
    {
        u16HexValue_Remainder = (0x0A + (u16DecValue%16 - 10));
    }

    u16HexValue = (u16HexValue_Integer<<4)|u16HexValue_Remainder;
    return u16HexValue;
}


BOOLEAN MApp_ParseHDCP_Key(void)
{
    U8 u8HandleNo = 0;
    U8 u8Len = 0;
    FileEntry stfileEntry;
    U8 *pu8FileName=NULL;
    U8 u8HDCPKeyHeader[16];
    U8 u16HDCPKey_Pos_Hex = 0;

    memset(u8HDCPKeyHeader,0,16);
    // Search files
    msAPI_Timer_ResetWDT();

    u8Len = strlen("HDCPKEY.bin");
    pu8FileName = (U8*)msAPI_Memory_Allocate(u8Len*sizeof(U8)+1, BUF_ID_FILEBROWER);

    if(pu8FileName == NULL)
    {
        printf("\nGet Memory Null! u8\n");
        MApp_FileBrowser_DeInit();
        return FALSE;
    }

    memcpy(pu8FileName, "HDCPKEY.bin", u8Len);
    pu8FileName[u8Len]='\0';
    if(MApp_UsbSaveData_SearchFileInRoot((U8 *)(pu8FileName), &stfileEntry))
    {
        u8HandleNo = msAPI_FCtrl_FileOpen(&stfileEntry, OPEN_MODE_BINARY_FOR_READ);
    }
    else
    {
        MApp_FileBrowser_DeInit();
        return FALSE;
    }

    if(u8HandleNo != FCTRL_INVALID_FILE_HANDLE)
    {
        msAPI_Timer_ResetWDT();

        msAPI_FCtrl_FileRead(u8HandleNo, HDCP_KEY_BUF_ADR, HDCP_KEY_ALL_LEN);
        msAPI_FCtrl_FileClose(u8HandleNo);

        memcpy(u8HDCPKeyHeader,(void *)_PA2VA(((HDCP_KEY_BUF_MEMORY_TYPE & MIU1) ? (HDCP_KEY_BUF_ADR | MIU_INTERVAL) : (HDCP_KEY_BUF_ADR)) + 0x10),HDCP_KEY_HEADER_LEN);
        if(u8HDCPKeyHeader[0] == 'C' && u8HDCPKeyHeader[1] == 'U' && u8HDCPKeyHeader[2] == 'S' && u8HDCPKeyHeader[3] == '_' && u8HDCPKeyHeader[4] == 'H' && u8HDCPKeyHeader[5] == 'D'
           &&u8HDCPKeyHeader[6] == 'C' && u8HDCPKeyHeader[7] == 'P' && u8HDCPKeyHeader[8] == '_')
        {
            g_u16HDCPKey_Pos = ((u8HDCPKeyHeader[9] - 0x30) << 12) | ((u8HDCPKeyHeader[10] - 0x30) << 8) | ((u8HDCPKeyHeader[11] - 0x30) << 4) | ((u8HDCPKeyHeader[12] - 0x30));
            g_u16HDCPKey_Pos++;
        }
        else
        {
            g_u16HDCPKey_Pos = 0;
            memcpy(u8HDCPKeyHeader,"CUS_HDCP_0000",14);
        }
        u16HDCPKey_Pos_Hex = DEC_TO_HEX(g_u16HDCPKey_Pos);
        u8HDCPKeyHeader[0] = 'C';
        u8HDCPKeyHeader[1] = 'U';
        u8HDCPKeyHeader[2] = 'S';
        u8HDCPKeyHeader[3] = '_';
        u8HDCPKeyHeader[4] = 'H';
        u8HDCPKeyHeader[5] = 'D';
        u8HDCPKeyHeader[6] = 'C';
        u8HDCPKeyHeader[7] = 'P';
        u8HDCPKeyHeader[8] = '_';
        u8HDCPKeyHeader[9]  = ((u16HDCPKey_Pos_Hex>>12)&0x0F)|0x30;
        u8HDCPKeyHeader[10] = ((u16HDCPKey_Pos_Hex>>8)&0x0F)|0x30;
        u8HDCPKeyHeader[11] = ((u16HDCPKey_Pos_Hex>>4)&0x0F)|0x30;
        u8HDCPKeyHeader[12] = (u16HDCPKey_Pos_Hex&0x0F)|0x30;
        memcpy((void *)_PA2VA(((HDCP_KEY_BUF_MEMORY_TYPE & MIU1) ? (HDCP_KEY_BUF_ADR | MIU_INTERVAL) : (HDCP_KEY_BUF_ADR)) + 0x10),u8HDCPKeyHeader,HDCP_KEY_HEADER_LEN);

        if(MApp_UsbSaveData_SearchFileInRoot((U8 *)(pu8FileName), &stfileEntry))
        {
            u8HandleNo = msAPI_FCtrl_FileOpen(&stfileEntry, OPEN_MODE_BINARY_FOR_READ_WRITE);
            msAPI_FCtrl_FileWrite(u8HandleNo,((HDCP_KEY_BUF_MEMORY_TYPE & MIU1) ? (HDCP_KEY_BUF_ADR | MIU_INTERVAL) : (HDCP_KEY_BUF_ADR)),HDCP_KEY_ALL_LEN);
            msAPI_Memory_Free(pu8FileName, BUF_ID_FILEBROWER);
        }
        else
        {
            msAPI_Memory_Free(pu8FileName, BUF_ID_FILEBROWER);
            MApp_FileBrowser_DeInit();
            return FALSE;
        }
        msAPI_FCtrl_FileClose(u8HandleNo);
    }
    else
    {
        //printf("\n FCTRL_INVALID_FILE_HANDLE\n");
    }
    return TRUE;
}


BOOLEAN MApp_WriteHDCP_Key(void)
{
    U8 u8PortEnStatus = 0;
    BOOLEAN bUSBIsConnected = FALSE;
    U8 u8HandleNo = 0;
    U8 u8Len = 0;
    U32 i = 0;
    U32 u32CopySection = 0;
    FileEntry stfileEntry;
    U8 *pu8FileName=NULL;
    U8 u8BPStatus = 0;
    U8 u8HDCPKey[HDCP_KEY_LEN];

    memset(u8HDCPKey,0xFF,HDCP_KEY_LEN);
    u8PortEnStatus = MDrv_USBGetPortEnableStatus();
    printf("\nUSB Port:%bu\n",(u8PortEnStatus & 0x03));
    if((u8PortEnStatus & BIT0) == BIT0)
    {
        if (!MDrv_UsbDeviceConnect())
        {
            MsOS_DelayTask(1000);
        }

        if (!MDrv_UsbDeviceConnect())
        {
            printf("\nNo USB Device1!\n");
            return FALSE;
        }
        MW_UsbDownload_SetUSBPortNo(1);
        bUSBIsConnected = TRUE;
    }

    if((!bUSBIsConnected) && ((u8PortEnStatus & BIT1) == BIT1))
    {
        if (!MDrv_UsbDeviceConnect_Port2())
        {
            MsOS_DelayTask(1000);
        }

        if (!MDrv_UsbDeviceConnect_Port2())
        {
            printf("\nNo USB Device2!\n");
            return FALSE;
        }
        MW_UsbDownload_SetUSBPortNo(2);
        bUSBIsConnected = TRUE;
    }

    // Init USB and file system, ...
    msAPI_Timer_ResetWDT();

    if (!MApp_UsbSaveData_InitFileSystem())
    {
        MApp_UsbSaveData_Exit();
        printf("\nFS Init Fail!\n");
        MApp_FileBrowser_DeInit();
        return FALSE;
    }

    MApp_FileBrowser_Init(0);
    // Search files
    msAPI_Timer_ResetWDT();
    MApp_ParseHDCP_Key();

    u8Len = strlen("HDCPKEY.bin");
    pu8FileName = (U8*)msAPI_Memory_Allocate(u8Len*sizeof(U8)+1, BUF_ID_FILEBROWER);

    if(pu8FileName == NULL)
    {
        printf("\nGet Memory Null! u8\n");
        MApp_FileBrowser_DeInit();
        return FALSE;
    }

    memcpy(pu8FileName, "HDCPKEY.bin", u8Len);
    pu8FileName[u8Len]='\0';
    if(MApp_UsbSaveData_SearchFileInRoot((U8 *)(pu8FileName), &stfileEntry))
    {
        u8HandleNo = msAPI_FCtrl_FileOpen(&stfileEntry, OPEN_MODE_FOR_READ);
    }
    else
    {
        //printf("\nSearch File Error\n");
        MApp_FileBrowser_DeInit();
        return FALSE;
    }
    msAPI_Memory_Free(pu8FileName, BUF_ID_FILEBROWER);
    //printf("\nStart read%bu\n",u8HandleNo);
    if(u8HandleNo != FCTRL_INVALID_FILE_HANDLE)
    {
        msAPI_Timer_ResetWDT();

        msAPI_FCtrl_FileSeek(u8HandleNo, (g_u16HDCPKey_Pos*HDCP_KEY_LEN) + 0x20, FILE_SEEK_SET);
        msAPI_FCtrl_FileRead(u8HandleNo, HDCP_KEY_BUF_ADR, HDCP_KEY_LEN);
        msAPI_FCtrl_FileClose(u8HandleNo);
    }
    else
    {
        //printf("\n FCTRL_INVALID_FILE_HANDLE\n");
    }

    msAPI_Flash_Set_WriteProtect_Disable_Range(SYSTEM_BANK_SIZE * HDCP_DB_BANK, SYSTEM_BANK_SIZE); // MDrv_FLASH_WriteProtect(DISABLE); // <-@@@
    MDrv_FLASH_AddressErase((SYSTEM_BANK_SIZE * HDCP_DB_BANK), SYSTEM_BANK_SIZE, TRUE);
    memcpy(u8HDCPKey,(void *)_PA2VA(((HDCP_KEY_BUF_MEMORY_TYPE & MIU1) ? (HDCP_KEY_BUF_ADR | MIU_INTERVAL) : (HDCP_KEY_BUF_ADR))),HDCP_KEY_LEN);
    MDrv_FLASH_Write((SYSTEM_BANK_SIZE * HDCP_DB_BANK), HDCP_KEY_SIZE, u8HDCPKey);

    MApp_FileBrowser_DeInit();
    return TRUE;
}
#endif
/******************************************************************************/
/// - This API will write OpCache Buf Data from Dram to Flash.
/// @param WriteBankIndex:OpCache Data will be write to which Bank of Flash
/// @param WriteBankNum:How many Banks will be written
/// @param WriteFinished:whether write success.
/* ****************************************************************************/
#if (ENABLE_CI && ENABLE_CI_PLUS)
void MApp_SaveOpCacheDate(U8 WriteBankIndex, U8 WriteBankNum, BOOLEAN*WriteFinished)
{
    msAPI_Flash_WaitWriteDone(5000);
    msAPI_Timer_ResetWDT();
    msAPI_Flash_Set_WriteProtect_Disable_Range(SYSTEM_BANK_SIZE * WriteBankIndex, SYSTEM_BANK_SIZE*WriteBankNum);
    MDrv_FLASH_AddressErase((SYSTEM_BANK_SIZE * WriteBankIndex), SYSTEM_BANK_SIZE*WriteBankNum, TRUE);
    if(TRUE == MDrv_FLASH_Write((SYSTEM_BANK_SIZE * WriteBankIndex), SYSTEM_BANK_SIZE*WriteBankNum, (void *)_PA2VA(((OPCACHE_BUF_MEMORY_TYPE & MIU1) ? (OPCACHE_BUF_ADR | MIU_INTERVAL) : (OPCACHE_BUF_ADR)))))
    {
        *WriteFinished = TRUE;
    }
}


#if(ENABLE_CI_PLUS_V1_4)
void MApp_SaveCIVirtualChannel(U8 WriteBankIndex, U8 WriteBankNum, BOOLEAN*WriteFinished)
{
    msAPI_Flash_WaitWriteDone(5000);
    msAPI_Timer_ResetWDT();
    msAPI_Flash_Set_WriteProtect_Disable_Range(SYSTEM_BANK_SIZE * WriteBankIndex, SYSTEM_BANK_SIZE*WriteBankNum);
    MDrv_FLASH_AddressErase((SYSTEM_BANK_SIZE * WriteBankIndex), SYSTEM_BANK_SIZE*WriteBankNum, TRUE);
    if(TRUE == MDrv_FLASH_Write((SYSTEM_BANK_SIZE * WriteBankIndex), SYSTEM_BANK_SIZE*WriteBankNum, (void *)_PA2VA(((OPCACHE_BUF_MEMORY_TYPE & MIU1) ? (OPCACHE_BUF_ADR | MIU_INTERVAL) : (OPCACHE_BUF_ADR)))))
    {
        *WriteFinished = TRUE;
    }
}

#endif


#endif

void MApp_SaveData_InitGenSettingExt(void)
{
    BYTE i;

    for( i = 0; i < DATA_INPUT_SOURCE_NUM; i++ )
    {
        //MApp_SaveData_Video_InitSetting((E_DATA_INPUT_SOURCE)i);
        //MApp_InitWhiteBalanceSetting((E_DATA_INPUT_SOURCE)i);
        //MApp_InitSubColorSetting((E_DATA_INPUT_SOURCE)i);
    }
}

void MApp_SaveData_LoadGenSettingExt(void)
{
    BYTE i;

/*
    for( i = 0; i < ADC_SET_NUMS; i++ )
    {
        MApp_LoadADCSetting((E_ADC_SET_INDEX)i);
    }
*/
    for( i = 0; i < DATA_INPUT_SOURCE_NUM; i++ )
    {
        ///MApp_LoadVideoSetting((E_DATA_INPUT_SOURCE)i);
        //MApp_LoadWhiteBalanceSetting((E_DATA_INPUT_SOURCE)i);
        //MApp_LoadSubColorSetting((E_DATA_INPUT_SOURCE)i);
    }
}

#if(ENABLE_DTV_EPG)

#define DEBUG_DB_MANUAL_EVENT(x)    //x
void MApp_DB_Load_ManualEventSetting(U8* pu8ManualEventData, U32 u32Size)
{
    DEBUG_DB_MANUAL_EVENT(printf("Load_ManualEventSetting()\n"););

#if DB_MANUAL_EVENT_SAVE_IN_DB_GEN
    U32 u32MaxSize = SIZE_EPG_MANUAL_TIMER_EVENT;


    if( u32Size == 0 )
    {
        printf("\nError: Get_ManualEventSetting: size=0!\n");
        return;
    }
    if( u32Size > u32MaxSize )
    {
        printf("\nError: Get_ManualEventSetting: size=%u over!\n", u32Size);
        u32Size = u32MaxSize;
    }

    //memcpy((BYTE *)_pstEpgTimer, &stGenSetting.g_SysSetting.u8EpgTimerSetting, RM_SIZE_MANUAL_TIMER_EVENT);
    memcpy( pu8ManualEventData, &(stGenSetting.stManualEventSetting.au8EpgTimerSetting[0]), u32Size);

#else

    U32 u32MaxSize = RM_SIZE_MANUAL_TIMER_EVENT;
    U16 u16CheckSum1, u16CheckSum2;


    if( u32Size > u32MaxSize )
    {
        printf("\nError: Get_ManualEventSetting: size=%u over!\n", u32Size);
        u32Size = u32MaxSize;
    }

    MApp_ReadDatabase(RM_TIMER_MANUAL_EVENT_START_ADR, pu8ManualEventData, u32Size);

    // Check checksum...
    u16CheckSum1 = MApp_CalCheckSum(pu8ManualEventData, u32Size);

    MApp_ReadDatabase(RM_TIMER_CHECKSUM_START_ADR, (BYTE *)(&u16CheckSum2), sizeof(U16));

    if( u16CheckSum1 != u16CheckSum2 )
    {
        printf(" ManualEvent Setting CS wrong!\n");
        // Clear all
        memset( pu8ManualEventData, 0, u32Size);
        MApp_DB_Save_ManualEventSetting(pu8ManualEventData, u32Size);
    }
#endif

}

void MApp_DB_Save_ManualEventSetting(U8* pu8ManualEventData, U32 u32Size)
{
    DEBUG_DB_MANUAL_EVENT(printf("Save_ManualEventSetting(u32Size=%u)\n", u32Size););

#if DB_MANUAL_EVENT_SAVE_IN_DB_GEN
    U32 u32MaxSize = SIZE_EPG_MANUAL_TIMER_EVENT;

    if( u32Size == 0 )
    {
        printf("\nError: Save_ManualEventSetting: size=0!\n");
        return;
    }

    if( u32Size > u32MaxSize )
    {
        printf("\nError: Save_ManualEventSetting: size=%u over!\n", u32Size);
        u32Size = u32MaxSize;
    }

    memcpy( &(stGenSetting.stManualEventSetting.au8EpgTimerSetting[0]), pu8ManualEventData, u32Size);

    //printf("_pstEpgTimer(%u) CRC=0x%X\n", u32Size, msAPI_CRC16_Cal( &(stGenSetting.stManualEventSetting.au8EpgTimerSetting[0]), u32Size) );

    //stGenSetting.stManualEventSetting.u16CheckSum = MApp_CalCheckSum(pu8ManualEventData, u32Size);
#else

    U32 u32MaxSize = RM_SIZE_MANUAL_TIMER_EVENT;
    U16 u16CheckSum;

    if( u32Size > u32MaxSize )
    {
        printf("\nError: Get_ManualEventSetting: size=%u over!\n", u32Size);
        u32Size = u32MaxSize;
    }

    MApp_WriteDatabase(RM_TIMER_MANUAL_EVENT_START_ADR, pu8ManualEventData, u32Size);

    //u16CheckSum = _MApp_EpgTimer_GetCheckSum();
    u16CheckSum = MApp_CalCheckSum(pu8ManualEventData, u32Size);

    MApp_WriteDatabase(RM_TIMER_CHECKSUM_START_ADR, (BYTE *)(&u16CheckSum), sizeof(U16));
#endif

}
#endif

//==========================================================

void MApp_DB_PrintVar(U8 u8Flag)
{
    msDebug_ANSI_SetColorText(E_FONT_ATTRIBUTE_BOLD);
    msDebug_ANSI_SetColorText(E_FONT_COLOR_GREEN);
    //msDebug_ANSI_SetColorText(E_FONT_COLOR_BLACK);
    //msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_GREEN);

    printf("\n==============================================\n");

    printf("MApp_DB_PrintVar()\n");

    if( u8Flag&DB_VAR_FMAP )
    {
        printf("=============== Flash Map ==============\n");
        printf("FLASH_SIZE=0x%X\n", FLASH_SIZE);
        printf("FLASH_BLOCK_SIZE=0x%X\n", FLASH_BLOCK_SIZE);
        printf("FLASH_LAST_BANK=0x%X\n", FLASH_LAST_BANK);

        printf("FMAP_GEN_SETTING_BANK_COUNT=0x%X\n", FMAP_GEN_SETTING_BANK_COUNT);
        printf("FMAP_GEN_SETTING_BANK_START=0x%X ~ 0x%X\n",
                FMAP_GEN_SETTING_BANK_START, FMAP_GEN_SETTING_BANK_START + FMAP_GEN_SETTING_BANK_COUNT -1);
        printf(" QUICK_DB_GENSETTING_BANK=0x%X\n", QUICK_DB_GENSETTING_BANK);

        printf("FMAP_CH_DB_BANK_COUNT=0x%X\n", FMAP_CH_DB_BANK_COUNT);
        printf("FMAP_CH_DB_BANK_START=0x%X ~ 0x%X\n",
                FMAP_CH_DB_BANK_START, FMAP_CH_DB_BANK_START + FMAP_CH_DB_BANK_COUNT - 1);

        printf(" DB_BANK_COUNT=0x%X\n", DB_BANK_COUNT);
        printf(" SYSTEM_BANK_DATABASE0=0x%X\n", SYSTEM_BANK_DATABASE0);
        //printf(" SYSTEM_BANK_DATABASE0_SIZE=0x%X\n", SYSTEM_BANK_DATABASE0_SIZE);
        printf(" SYSTEM_BANK_DATABASE1=0x%X\n", SYSTEM_BANK_DATABASE1);
        //printf(" SYSTEM_BANK_DATABASE1_SIZE=0x%X\n", SYSTEM_BANK_DATABASE1_SIZE);


        printf("FMAP_FACTORY_SETTING_BANK_COUNT=0x%X\n", FMAP_FACTORY_SETTING_BANK_COUNT);
        printf("FMAP_FACTORY_SETTING_BANK_START=0x%X\n", FMAP_FACTORY_SETTING_BANK_START);

        printf("FMAP_HDCP_KEY_BANK_COUNT=0x%X\n", FMAP_HDCP_KEY_BANK_COUNT);
        printf("FMAP_HDCP_KEY_BANK_START=0x%X\n", FMAP_HDCP_KEY_BANK_START);
        printf(" HDCP_DB_BANK=0x%X\n", HDCP_DB_BANK);


        printf("FMAP_VERSION_DB_BANK_COUNT=0x%X\n", FMAP_VERSION_DB_BANK_COUNT);
        printf("FMAP_VERSION_DB_BANK_START=0x%X\n", FMAP_VERSION_DB_BANK_START);
        //printf(" VERSION_DB_BANK0=0x%X\n", VERSION_DB_BANK0);
        //printf(" VERSION_DB_BANK1=0x%X\n", VERSION_DB_BANK1);

    #if( ENABLE_OAD && (ENABLE_OAD_DATA_SAVE_TO_DB_CH==0) )
        printf("FMAP_OAD_BANK_COUNT=0x%X\n", FMAP_OAD_BANK_COUNT);
        printf("FMAP_OAD_BANK_START=0x%X\n", FMAP_OAD_BANK_START);
        printf(" OAD_DB_BANK=0x%X\n", OAD_DB_BANK);
    #endif

        // CIPLUS-KEY setting database flash map...
        printf("FMAP_CI_BANK_COUNT=0x%X\n", FMAP_CI_BANK_COUNT);
        printf("FMAP_CI_BANK_START=0x%X\n", FMAP_CI_BANK_START);
        printf(" CIPLUS_KEY_BANK=0x%X\n", CIPLUS_KEY_BANK);
        //printf(" CIPLUS_KEY_SIZE=0x%X\n", CIPLUS_KEY_SIZE);

        printf("FMAP_CI_PLUS_BANK_COUNT=0x%X\n", FMAP_CI_PLUS_BANK_COUNT);
        printf("FMAP_CI_PLUS_BANK_START=0x%X ~ 0x%X\n",
            FMAP_CI_PLUS_BANK_START, FMAP_CI_PLUS_BANK_START+FMAP_CI_PLUS_BANK_COUNT-1);
    #if(ENABLE_CI_PLUS)
        printf("CIPLUS_1_3_BANK_CAM_INFO_DATA=0x%X\n", CIPLUS_1_3_BANK_CAM_INFO_DATA);
        {
            U8 i;
            for( i = 0; i < MAX_OP_CACHE_NUM; ++ i )
            {
                printf("CIPLUS_1_3_BANK_CAM_NIT_DATA(%u)=0x%X\n", i, CIPLUS_1_3_BANK_CAM_NIT_DATA(i));
            }
        }
    #endif

        printf(" FMAP_CANALREADY_AUTH_START=0x%X, size=0x%X\n", FMAP_CANALREADY_AUTH_BANK, FMAP_CANALREADY_AUTH_SIZE);

        printf("FMAP_TOTAL_USE_BANK_END=0x%X\n", FMAP_TOTAL_USE_BANK_END);
        printf("MERGE.bin max size=0x%X\n", (FMAP_TOTAL_USE_BANK_END)*FLASH_BLOCK_SIZE );
    }

    if( u8Flag&DB_VAR_RAMMAP )
    {
        printf("\n==============================================\n");

        printf(" QUICK_DB_GENST_SIZE=0x%X\n", QUICK_DB_GENST_SIZE);
        //printf(" RM_GEN_SIZE=0x%X\n", RM_GEN_SIZE);

    #if( ENABLE_OAD )
        printf(" sizeof(ST_DOWNLOAD_INFO)=0x%X\n", sizeof(ST_DOWNLOAD_INFO));
    #endif

        printf(" RM_BOOTLOADER_ADDR=0x%X, size=0x%X\n", RM_BOOTLOADER_ADDR, RM_SIZE_BOOTLOADER);
        printf(" RM_HDCP_KEY_ADDR=0x%X, size=0x%X\n", RM_HDCP_KEY_ADDR, RM_SIZE_HDCP_KEY);

        printf(" RM_FACTORY_START_ADDR=0x%X, size=0x%X\n", RM_FACTORY_START_ADDR, RM_FACTORY_SIZE);
        printf(" RM_GENSET_START_ADR=0x%X, size=0x%X\n", RM_GENSET_START_ADR, RM_SIZE_GENSET);
        printf(" - RM_VIDEO_DATA_ADDRESS(0)=0x%X,  size=0x%X\n", RM_VIDEO_DATA_ADDRESS(0), RM_VIDEO_DATA_SIZE);

    #if( DB_PC_MODE_SAVE_TO_DB_GEN  )
        printf(" - RM_MODE_SETTING_ADDR(0)=0x%X,  size=%u=%u * %u\n", RM_MODE_SETTING_ADDR(0),
                (sizeof(MS_PCADC_MODESETTING_TYPE) * MAX_MODE_NUM), sizeof(MS_PCADC_MODESETTING_TYPE), MAX_MODE_NUM);
    #endif

        //--------------------------------------------------------------------------------
        printf("-- RM_GEN_BLOCK_TOTAL_USAGE_REAL=0x%X \n", RM_GEN_BLOCK_TOTAL_USAGE_REAL);

        printf("------ RM_GEN_USAGE=0x%X -----\n", RM_GEN_USAGE);

        // ====================================================================

        printf("======== RM_DB_CH_START_ADDR=0x%X ========\n", RM_DB_CH_START_ADDR );

    #if (ENABLE_DTV_EPG)
        printf(" RM_TIMER_MANUAL_EVENT_START_ADR=0x%X, size=0x%X\n", RM_TIMER_MANUAL_EVENT_START_ADR, RM_SIZE_MANUAL_TIMER_EVENT);
        printf(" RM_TIMER_CHECKSUM_START_ADR=0x%X, size=0x%X\n", RM_TIMER_CHECKSUM_START_ADR, RM_SIZE_TIMER_CHECKSUM);
    #endif
        printf(" RM_TV_COMMON_DATA_START_ADR=0x%X, size=0x%X\n", RM_TV_COMMON_DATA_START_ADR, RM_SIZE_TV_COMMON_DATA);

        printf(" RM_ATV_CHSET_START_ADDR=0x%X,    size=0x%X\n", RM_ATV_CHSET_START_ADDR, RM_ATV_CHSET_SIZE);

    #if( DB_PC_MODE_SAVE_TO_DB_GEN == 0 )
        printf(" RM_MODE_SETTING_START_ADR=0x%X,  size=0x%X\n", RM_MODE_SETTING_START_ADR, RM_SIZE_MODE_SETTING);
    #endif


    #if( ENABLE_DTV )
        printf("\n=== DTV ===\n");
        printf(" sizeof(CHANNEL_ATTRIBUTE)=0x%X\n", sizeof(CHANNEL_ATTRIBUTE));
        printf(" sizeof(DTV_CHANNEL_INFO)=0x%X\n", sizeof(DTV_CHANNEL_INFO));
        printf(" sizeof(DTVPROGRAMID_M)=0x%X\n", sizeof(DTVPROGRAMID_M));
        printf(" sizeof(DTVNETWORK)=0x%X\n", sizeof(DTVNETWORK));
        printf(" sizeof(AUD_INFO)=%u, MAX_AUD_LANG_NUM=%u\n", sizeof(AUD_INFO), MAX_AUD_LANG_NUM );
    #endif

    #if (ENABLE_S2)
        printf("--- MAX_DTV_S2_PROGRAM=%u\n", MAX_DTV_S2_PROGRAM);
        printf(" RM_START_ADDRESS_OF_SAT_DATA_STRUCTURE=0x%X,   size=0x%X\n", RM_START_ADDRESS_OF_SAT_DATA_STRUCTURE, RM_SAT_DATA_STRUCTURE_SIZE);
        printf(" RM_START_ADDRESS_OF_TP_DATA_STRUCTURE=0x%X,   size=0x%X\n", RM_START_ADDRESS_OF_TP_DATA_STRUCTURE, RM_TP_DATA_STRUCTURE_SIZE);
        printf(" RM_DTV_S2_CHSET_START_ADDR=0x%X,   size=0x%X\n", RM_DTV_S2_CHSET_START_ADDR, RM_DTV_S2_CHSET_SIZE);

        printf(" MAX_S2_CHANNELTABLE_MAP=%u\n", MAX_S2_CHANNELTABLE_MAP);
        //printf(" MAX_DTV_S2_PROGRAM=%u\n", MAX_DTV_S2_PROGRAM);
        printf(" MAX_S2_IDTABLE_MAP=%u\n", MAX_S2_IDTABLE_MAP);
        printf(" MAX_DTV_S2_MUX_NUMBER=%u\n", MAX_DTV_S2_MUX_NUMBER);
        printf(" MAX_NETWOEK_S2_NUMBER=%u\n", MAX_NETWOEK_S2_NUMBER);
      #if(ENABLE_CM_STORE_AUD_INFO_NEW_METHOD)
        printf(" CM_AUDINFO_MAX_NUM_DVBS=%u\n", CM_AUDINFO_MAX_NUM_DVBS);
      #endif
    #endif

        printf("--- RM_DTV_CHSET_START_ADDR=0x%X,  size=0x%X\n", RM_DTV_CHSET_START_ADDR, RM_DTV_CHSET_SIZE);
    #if( ENABLE_DTV )
        //printf(" offsetof(DTV_CHANNEL_DATA_STRUCTURE, astAudInfoTab)=%u\n", offsetof(DTV_CHANNEL_DATA_STRUCTURE, astAudInfoTab));
        //printf(" sizeof(DTV_CHANNEL_DATA_STRUCTURE)=0x%X\n", sizeof(DTV_CHANNEL_DATA_STRUCTURE));
        printf(" MAX_DTVCHANNELTABLE_MAP=%u\n", MAX_DTVCHANNELTABLE_MAP);
        printf(" MAX_DTVPROGRAM=%u\n", MAX_DTVPROGRAM);
        printf(" MAX_DTVIDTABLE_MAP=%u\n", MAX_DTVIDTABLE_MAP);
        printf(" MAX_MUX_NUMBER=%u\n", MAX_MUX_NUMBER);
        printf(" MAX_NETWOEK_NUMBER=%u\n", MAX_NETWOEK_NUMBER);
      #if(ENABLE_CM_STORE_AUD_INFO_NEW_METHOD)
        printf(" CM_AUDINFO_MAX_NUM_DVB=%u\n", CM_AUDINFO_MAX_NUM_DVB);
      #endif
    #endif

    #if 0
        printf(" RM_DTV_CHSET_START_ADDR.wCurOrderOfTV=0x%X\n", RM_DTV_CHSET_START_ADDR + offsetof(DTV_CHANNEL_DATA_STRUCTURE, wCurOrderOfTV) );
        printf(" RM_DTV_CHSET_START_ADDR.wCurOrderOfRadio=0x%X\n", RM_DTV_CHSET_START_ADDR + offsetof(DTV_CHANNEL_DATA_STRUCTURE, wCurOrderOfRadio) );
        printf(" RM_DTV_CHSET_START_ADDR.wCurOrderOfData=0x%X\n", RM_DTV_CHSET_START_ADDR + offsetof(DTV_CHANNEL_DATA_STRUCTURE, wCurOrderOfData) );
        printf(" RM_DTV_CHSET_START_ADDR.eDTVCurrentServiceType=0x%X\n", RM_DTV_CHSET_START_ADDR + offsetof(DTV_CHANNEL_DATA_STRUCTURE, eDTVCurrentServiceType) );
        printf(" RM_DTV_CHSET_START_ADDR.bDTVChannelTableMap=0x%X\n", RM_DTV_CHSET_START_ADDR + offsetof(DTV_CHANNEL_DATA_STRUCTURE, bDTVChannelTableMap) );
        printf(" RM_DTV_CHSET_START_ADDR.astDTVChannelTable=0x%X\n", RM_DTV_CHSET_START_ADDR + offsetof(DTV_CHANNEL_DATA_STRUCTURE, astDTVChannelTable) );
        printf(" RM_DTV_CHSET_START_ADDR.bDTVIDtableMap=0x%X\n", RM_DTV_CHSET_START_ADDR + offsetof(DTV_CHANNEL_DATA_STRUCTURE, bDTVIDtableMap) );
        printf(" RM_DTV_CHSET_START_ADDR.astDtvIDTable=0x%X\n", RM_DTV_CHSET_START_ADDR + offsetof(DTV_CHANNEL_DATA_STRUCTURE, astDtvIDTable) );
        printf(" RM_DTV_CHSET_START_ADDR.astDtvNetwork=0x%X\n", RM_DTV_CHSET_START_ADDR + offsetof(DTV_CHANNEL_DATA_STRUCTURE, astDtvNetwork) );
    #endif

    #if (ENABLE_DVBC&&DVB_T_C_DIFF_DB)
        printf("--- RM_DTV_C_CHSET_START_ADDR=0x%X,   size=0x%X\n", RM_DTV_C_CHSET_START_ADDR, RM_DTV_C_CHSET_SIZE);
        printf(" MAX_DTVPROGRAM_DVBC=%u\n", MAX_DTVPROGRAM_DVBC);
        printf(" MAX_MUX_NUMBER_DVBC=%u\n", MAX_MUX_NUMBER_DVBC);
        printf(" MAX_NETWOEK_NUMBER=%u\n", MAX_NETWOEK_NUMBER);
      #if(ENABLE_CM_STORE_AUD_INFO_NEW_METHOD)
        printf(" CM_AUDINFO_MAX_NUM_DVBC=%u\n", CM_AUDINFO_MAX_NUM_DVBC);
      #endif
    #endif

    #if(ENABLE_ATSC)
        printf(" ---------- ATSC Start ----------\n");
        printf(" sizeof(MS_VIRTUAL_CHANNEL)=0x%X\n", sizeof(MS_VIRTUAL_CHANNEL));
        printf(" sizeof(MS_CHANNEL_SETTING)=0x%X\n", sizeof(MS_CHANNEL_SETTING));

        printf(" sizeof(MS_RF_CHANNEL_new)=0x%X\n", sizeof(MS_RF_CHANNEL_new));

        printf(" MAX_NUM_OF_AIR_VIR_CH=%u\n", MAX_NUM_OF_AIR_VIR_CH);
        printf(" MAX_NUM_OF_CATV_VIR_CH=%u\n", MAX_NUM_OF_CATV_VIR_CH);

        printf(" RM_AIR_VIR_CH_START_ADR=0x%X, size=0x%X\n", RM_AIR_VIR_CH_START_ADR, RM_AIR_VIR_CH_LEN);
        printf(" RM_AIR_CH_SETTING_START_ADR=0x%X, size=0x%X\n", RM_AIR_CH_SETTING_START_ADR, RM_AIR_CH_SETTING_LEN);
        printf(" RM_CATV_VIR_CH_START_ADR=0x%X, size=0x%X\n", RM_CATV_VIR_CH_START_ADR, RM_CATV_VIR_CH_LEN);
        printf(" RM_CATV_CH_SETTING_START_ADR=0x%X, size=0x%X\n", RM_CATV_CH_SETTING_START_ADR, RM_CATV_CH_SETTING_LEN);

        printf(" RM_ATSC_AIR_RF_CH_START_ADR=0x%X, size=0x%X\n", RM_ATSC_AIR_RF_CH_START_ADR, RM_ATSC_AIR_RF_CH_LEN);
        printf(" RM_ATSC_CATV_RF_CH_START_ADR=0x%X, size=0x%X\n", RM_ATSC_CATV_RF_CH_START_ADR, RM_ATSC_CATV_RF_CH_LEN);

        printf(" ATSC_RRT5_SETTING_START_ADDR=0x%X, size=0x%X\n", ATSC_RRT5_SETTING_START_ADDR, ATSC_RRT5_SETTING_SIZE);
        printf(" ATSC_RRT5_DESCRIPTOR_START_ADDR=0x%X, size=0x%X\n", ATSC_RRT5_DESCRIPTOR_START_ADDR, ATSC_RRT5_DESCRIPTOR_SIZE);
        printf(" ATSC_RRT5_EZ_REGION_START_ADDR=0x%X, size=0x%X\n", ATSC_RRT5_EZ_REGION_START_ADDR, ATSC_RRT5_EZ_REGION_SIZE);
        printf(" sizeof(MS_EZ_REGION5_RATING)=0x%X\n", sizeof(MS_EZ_REGION5_RATING));

        printf(" ---------- ATSC End ----------\n");
    #endif

        printf("== RM_DB_CH_END_ADDR=0x%X\n", RM_DB_CH_END_ADDR);

        printf("== RM_DB_CH_TOTAL_USAGE_REAL=0x%X\n", RM_DB_CH_TOTAL_USAGE_REAL);

        printf("== RM_64K_USAGE=0x%X\n", RM_64K_USAGE);

        printf("** RM_DB_VERSION_START_ADDR=0x%X, size=0x%X\n", RM_DB_VERSION_START_ADDR, RM_DB_VERSION_SIZE);

        printf("=== RM_DB_CH_AND_VERSION_TOTAL_USAGE=0x%X\n", RM_DB_CH_AND_VERSION_TOTAL_USAGE);
        printf("=== RM_DB_TOTAL_USAGE=0x%X\n", RM_DB_TOTAL_USAGE);

    }

    printf("===== RamDisk mapping to dram =====\n");
    printf(" RAM_DISK_MEM_ADDR=0x%X\n", RAM_DISK_MEM_ADDR);
    printf(" RAM_DISK_DB_GEN_START_ADDR=0x%X, End=0x%X\n", RAM_DISK_DB_GEN_START_ADDR, RAM_DISK_DB_GEN_END_ADDR);
    printf(" RAM_DISK_DB_64K_START_ADDR=0x%X, End=0x%X\n", RAM_DISK_DB_64K_START_ADDR, RAM_DISK_DB_64K_END_ADDR);

    printf("==============================================\n");

    msDebug_ANSI_AllAttrOffText();
}

// Must keep this function be compiled
void MApp_DB_Check_Build(void)
{
// #define FLASH_LAST_BANK     (FLASH_SIZE/FLASH_BLOCK_SIZE -1)
// ==> 0x3F

//#define FMAP_GEN_SETTING_BANK_COUNT     2
//#define FMAP_GEN_SETTING_BANK_START     (FLASH_LAST_BANK - FMAP_GEN_SETTING_BANK_COUNT +1)
// => 0x3E

#define FMAP_GEN_SETTING_BANK_END       (FMAP_GEN_SETTING_BANK_START+FMAP_GEN_SETTING_BANK_COUNT-1)
// => 0x3F

//#define FMAP_CH_DB_BANK_START           (FMAP_GEN_SETTING_BANK_START - FMAP_CH_DB_BANK_COUNT)
// => 0x3C
//#define FMAP_CH_DB_BANK_COUNT               (DB_BANK_COUNT*2)
#define FMAP_CH_DB_BANK_END             (FMAP_CH_DB_BANK_START+FMAP_CH_DB_BANK_COUNT-1)
// => 0x3D

    // Check DB_GEN,DB_CH use flash overlay
    BUILD_ERROR_IF_TRUE( ((FMAP_CH_DB_BANK_START>=FMAP_GEN_SETTING_BANK_START)&&(FMAP_CH_DB_BANK_START<=FMAP_GEN_SETTING_BANK_END)) );
    BUILD_ERROR_IF_TRUE( ((FMAP_CH_DB_BANK_END>=FMAP_GEN_SETTING_BANK_START)&&(FMAP_CH_DB_BANK_END<=FMAP_GEN_SETTING_BANK_END)) );

}

BOOL MApp_DB_Check(void)
{
    BOOL bReturn = TRUE;
    U32 u32FlashSize;
    U8 i;

    //PRINT_CURRENT_LINE();
    //printf("MApp_DB_Check()\n");


#if 0//( RM_GEN_SIZE != QUICK_DB_GENST_SIZE )
    #error "RM_GEN_SIZE != QUICK_DB_GENST_SIZE"
#endif


    // Check if flash size correct
    if( MDrv_SERFLASH_DetectSize(&u32FlashSize) )
    {
        //printf(" u32FlashSize=0x%x\n", u32FlashSize);
        if( u32FlashSize != FLASH_SIZE )
        {
            for( i = 0; i < 5; ++ i )
            {
                msDebug_ANSI_SetColorText(E_FONT_ATTRIBUTE_BOLD);
                msDebug_ANSI_SetColorText(E_FONT_COLOR_WHITE);
                msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_RED);
                printf("Warnning: u32FlashSize=0x%X is not equal to FLASH_SIZE(0x%X)", u32FlashSize, FLASH_SIZE);
                msDebug_ANSI_AllAttrOffText();
            }
            //msAPI_Timer_Delayms(1000);
        }
    }
    else
    {
        printf("\nError: MDrv_SERFLASH_DetectSize() failed\n");
    }


    // Assert:  BD_GEN real usage  <  Flash save unit size
    /*if( RM_GEN_BLOCK_TOTAL_USAGE_REAL > QUICK_DB_GENST_SIZE )
    {
        bReturn = FALSE;
        printf("\nFatal Error: RM_GEN_BLOCK_TOTAL_USAGE_REAL=0x%X > QUICK_DB_GENST_SIZE=0x%X\n", RM_GEN_BLOCK_TOTAL_USAGE_REAL, QUICK_DB_GENST_SIZE);
        msAPI_Timer_Delayms(5000);
    }*/
    BUILD_ERROR_IF_TRUE( (RM_GEN_BLOCK_TOTAL_USAGE_REAL > QUICK_DB_GENST_SIZE) );

    // Assert:  BD_GEN usage  <  Flash save unit size
    /*
    if( RM_GEN_USAGE > QUICK_DB_GENST_SIZE )
    {
        bReturn = FALSE;
        printf("\nFatal Error: RM_GEN_USAGE=0x%X > QUICK_DB_GENST_SIZE=0x%X\n", RM_GEN_USAGE, QUICK_DB_GENST_SIZE);
        msAPI_Timer_Delayms(5000);
    }*/
    BUILD_ERROR_IF_TRUE( (RM_GEN_USAGE > QUICK_DB_GENST_SIZE) );


    // Assert: DB_CH + DB info <  DB_CH flash size
    /*if( RM_DB_CH_AND_VERSION_TOTAL_USAGE > (0x10000*DB_BANK_COUNT) )
    {
        bReturn = FALSE;
        printf("\nFatal Error: RM_64K_USAGE=0x%X > (0x10000*DB_BANK_COUNT)=0x%X\n", RM_64K_USAGE, (0x10000*DB_BANK_COUNT) );
        msAPI_Timer_Delayms(5000);
    }*/
    BUILD_ERROR_IF_TRUE( (RM_DB_CH_AND_VERSION_TOTAL_USAGE > (0x10000*DB_BANK_COUNT)) );



    // Assert: Total Gen usage + Total DB usage must < dram size
    /*if( (RM_GEN_USAGE + RM_DB_CH_AND_VERSION_TOTAL_USAGE ) > DATABASE_START_LEN )
    {
        bReturn = FALSE;
        printf("\nFatal Error: RM_GEN_USAGE=0x%X + RM_DB_CH_USAGE=0x%X > DATABASE_START_LEN=0x%X\n",
                            RM_GEN_USAGE, RM_DB_CH_AND_VERSION_TOTAL_USAGE, DATABASE_START_LEN);
        msAPI_Timer_Delayms(5000);
    }*/
    BUILD_ERROR_IF_TRUE( (RM_GEN_USAGE + RM_DB_CH_AND_VERSION_TOTAL_USAGE ) > DATABASE_START_LEN );


    // Assert: Total Gen usage + Total DB usage must < dram size
    /*if( (RM_DB_TOTAL_USAGE ) > DATABASE_START_LEN )
    {
        bReturn = FALSE;
        printf("\nFatal Error: RM_DB_TOTAL_USAGE=0x%X > DATABASE_START_LEN=0x%X\n",
                            RM_DB_TOTAL_USAGE, DATABASE_START_LEN);
        msAPI_Timer_Delayms(5000);
    }*/
    BUILD_ERROR_IF_TRUE( RM_DB_TOTAL_USAGE > DATABASE_START_LEN );
    //printf("RM_DB_TOTAL_USAGE=0x%X\n", RM_DB_TOTAL_USAGE );

#if(ENABLE_DTV_EPG)
    // Check if driver use size > dram size
    BUILD_ERROR_IF_TRUE( EPG_REAL_USE_DB_SIZE > SCHEDULE_LIST_LEN );

  #if (DB_MANUAL_EVENT_SAVE_IN_DB_GEN) // EPG ManualEvent save in DB_GEN
    // Check if driver use size > GenSetting alloc size
    BUILD_ERROR_IF_TRUE( EPG_REAL_USE_DB_SIZE > SIZE_EPG_MANUAL_TIMER_EVENT );
  #else  // EPG ManualEvent save in DB_CH
    // Check if driver use size > DB_CH alloc size
    BUILD_ERROR_IF_TRUE( EPG_REAL_USE_DB_SIZE > RM_SIZE_MANUAL_TIMER_EVENT );
  #endif
#endif

#if( BLOADER && ENABLE_OAD_DATA_SAVE_TO_DB_CH )
    // Check if struct size > db size
    BUILD_ERROR_IF_TRUE( sizeof(ST_DOWNLOAD_INFO) > RM_OAD_SETTING_SIZE );
#endif


#if(ENABLE_ATSC)
    // Check RRT5 dram size
    BUILD_ERROR_IF_TRUE( (SIZE_RRT_ALL_DESCRIPTORS+RRT_SETTING_MEMORIZE_SIZE) > RRT5_DIM_START_LEN );
#endif


    if( bReturn )
    {

    }
    else
    {
        MApp_DB_PrintVar(0xFF);
    }


    //MApp_DB_PrintVar(0xFF);
    //while(10){}

    return TRUE;
}


#undef MAPP_SAVEDATA_C

