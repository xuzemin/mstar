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

#ifndef MAPP_SAVEDATA_H
#define MAPP_SAVEDATA_H

#include "Board.h"

#include "msAPI_Global.h"
#include "msAPI_ATVSystem.h"
#include "msAPI_DTVSystem.h"
#include "apiXC_ModeParse.h"
#include "apiXC_Sys.h"

#if (ENABLE_DTV_EPG)
#include "MApp_EpgTimer.h"
#endif

#include "MApp_GlobalSettingSt.h" //ZUI

#if 1//(ENABLE_SAVE_DATA_TO_EEPROM)
#include "MApp_EEPROM_Map.h"
#endif

#if ENABLE_CI
#include "msAPI_CI.h"
#include "msAPI_OpCache.h"
#endif
#if(ENABLE_S2)
#include "apiDTVSatTable.h"
#endif

#include "MApp_FlashMap.h"

#if(ENABLE_ATSC)
    #include "MApp_SaveData_ATSC.h"
#endif



#ifdef MAPP_SAVEDATA_C
    #define INTERFACE
#else
    #define INTERFACE extern
#endif



#define DB_CH_VERSION_ID        0xA55A5679

//================================================================================
// Check EEPROM ID
#define USR_EEPROM_ID                   ((U8)((TV_SYSTEM<<6)+(MS_BOARD_TYPE_SEL)+(g_PNL_TypeSel)))


#define SIZE_SYS_SETTING                ((U16)sizeof(MS_USER_SYSTEM_SETTING))
#define SIZE_VIDEO_DATA                 ( (U16)sizeof(T_MS_VIDEO) )
#define SIZE_WHITEBALANCE_DATA          ( (U16)sizeof(T_MS_WHITEBALANCE) )
#define SIZE_SUBCOLOR_DATA              ( (U16)sizeof(T_MS_SUB_COLOR) )
#define SIZE_SOUND_SETTING              ( (U16)sizeof(stUserSoundSettingType) )
#define SIZE_TIME_DATA                  ( (U16)sizeof(MS_TIME) )
#define SIZE_SCANMENU_SETTING           ( (U16)sizeof(MS_SCANMENU_SETTING) )
#define SIZE_BLOCK_DATA                 ( (U16)sizeof(MS_BLOCKSYS_SETTING) )
#define SIZE_SSC_DATA                   ( (U16)sizeof(MS_SSC_SETTING) )
#if ENABLE_GAMMA_ADJUST
#define SIZE_GAMMA_SETTING              ( (U16)sizeof(stUserGammaSetting) )
#endif
#if (ENABLE_NONLINEAR_CURVE)
#define SIZE_NONLINER_CURVE_SETTING     ( (U16)sizeof(MS_NONLINEAR_CURVE_SETTING) )
#endif

#if(ENABLE_CI)
#define SIZE_CIINFORMATION_SETTING      ( (U16)sizeof(CI_SETTING) )
#endif

#if ENABLE_DRM
#define SIZE_DRM_DATA                   ( (U16)sizeof(VDplayerDRMInfo) )
#endif

//#if (ENABLE_PIP)
#define SIZE_PIP_DATA                   ( (U16)sizeof(MS_PIP_SETTING) )
//#endif

#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
#define SIZE_NETWORK_INFO_DATA          ((U16)sizeof(MS_ALL_NETWORKID_INFO))
#endif

#if ENABLE_CI
    #define SIZE_CI_DATA                ((U16)sizeof(CI_SETTING))
#endif
#if (ENABLE_CI && ENABLE_CI_PLUS)
    #define SIZE_CI_PLUS_DATA           ((U16)sizeof(MS_CI_PLUS_SETTING))
#endif

#if (ENABLE_LAST_MEMORY==1)&&(ENABLE_LAST_MEMORY_STORAGE_SAVE==1)
#define SIZE_MM_LASTMEMORY_SETTING      ( (U16)sizeof(MS_MM_LASTMEMORY_SETTING))
#endif

#if ENABLE_SZ_FACTORY_OVER_SCAN_FUNCTION
#define SIZE_OVERSCAN_DATA                   ( (U16)sizeof(MS_OVERSCAN_SETTING))
#endif

//================================================================================
#if(ENABLE_ATSC) // tmp
    #define QUICK_DB_GENST_SIZE     (0x2000) // 8K
#elif (DB_MANUAL_EVENT_SAVE_IN_DB_GEN || DB_PC_MODE_SAVE_TO_DB_GEN )
    #if (PICTURE_NATURAL_SPORTS_LIGHTNESS || ENABLE_FM_RADIO)
        #define QUICK_DB_GENST_SIZE     (0x4000)//16K
    #else
        #define QUICK_DB_GENST_SIZE     (0x2000) // 8K
    #endif
#else
    #if PICTURE_NATURAL_SPORTS_LIGHTNESS
        #define QUICK_DB_GENST_SIZE     (0x2000) // 8K
    #else
        #define QUICK_DB_GENST_SIZE     (4096) // 4K
    #endif
#endif


//#define RM_64K_SIZE                     0x10000
//#define RM_GEN_SIZE                     QUICK_DB_GENST_SIZE//0x0800  // 2K, for GENSETTING

//================================================================================
//#define RM_DB_CH_START_ADDR             (RM_GEN_USAGE) // Need alignment?
//#define RM_DB_CH_START_ADDR             //MemAlign( (RM_GEN_USAGE), 16 ) // Need alignment?
#define RM_DB_CH_START_ADDR             QUICK_DB_GENST_SIZE

//---------------------------------------------------------------------------------------------
#define RM_OAD_SETTING_START_ADDR       (RM_DB_CH_START_ADDR)
#if( ENABLE_OAD && (ENABLE_OAD_DATA_SAVE_TO_DB_CH) )
    #define RM_OAD_SETTING_SIZE         0x80
#else
    #define RM_OAD_SETTING_SIZE         0
#endif
#define RM_OAD_SETTING_END_ADDR         (RM_OAD_SETTING_START_ADDR + RM_OAD_SETTING_SIZE)

//---------------------------------------------------------------------------------------------

//#define RM_VIDEO_DATA_START_ADDR        (RM_DB_CH_START_ADDR)
//#define RM_VIDEO_DATA_ADDRESS(i)        (RM_VIDEO_DATA_START_ADDR + (U16)(SIZE_VIDEO_DATA*(i)))
//#define RM_VIDEO_DATA_SIZE              (SIZE_VIDEO_DATA*DATA_INPUT_SOURCE_NUM)
//#define RM_VIDEO_DATA_END_ADDR          (RM_VIDEO_DATA_START_ADDR + RM_VIDEO_DATA_SIZE)

//-------------------------------------------------------------------------------------------
#define RM_TIMER_MANUAL_EVENT_START_ADR     (RM_OAD_SETTING_END_ADDR)
#if (ENABLE_DTV_EPG&&(DB_MANUAL_EVENT_SAVE_IN_DB_GEN==0))
    #define RM_SIZE_MANUAL_TIMER_EVENT      ((U16)sizeof(MS_EPG_TIMER) * EPG_TIMER_MAX_NUM)
#else
    #define RM_SIZE_MANUAL_TIMER_EVENT      0
#endif
#define RM_TIMER_MANUAL_EVENT_END_ADR       (RM_TIMER_MANUAL_EVENT_START_ADR + RM_SIZE_MANUAL_TIMER_EVENT)

//--------------------------------------------------------------------------------------------
#define RM_TIMER_CHECKSUM_START_ADR         (RM_TIMER_MANUAL_EVENT_END_ADR)
#if (ENABLE_DTV_EPG&&(DB_MANUAL_EVENT_SAVE_IN_DB_GEN==0))
#define RM_SIZE_TIMER_CHECKSUM              ((U16)sizeof(U16))
#else
#define RM_SIZE_TIMER_CHECKSUM              0
#endif
#define RM_TIMER_CHECKSUM_END_ADR           (RM_TIMER_CHECKSUM_START_ADR + RM_SIZE_TIMER_CHECKSUM)

//--------------------------------------------------------------------------------------------

#define RM_TV_COMMON_DATA_START_ADR         (RM_TIMER_CHECKSUM_END_ADR)
#define RM_SIZE_TV_COMMON_DATA              ((U16)sizeof(COMMON_DATA_STRUCTURE))
#define RM_TV_COMMON_DATA_END_ADR           (RM_TV_COMMON_DATA_START_ADR + RM_SIZE_TV_COMMON_DATA)

//--------------------------------------------------------------------------------------------

#define RM_ATV_CHSET_START_ADDR             (RM_TV_COMMON_DATA_END_ADR)
#define RM_ATV_CHSET_SIZE                   (sizeof(ATV_PROGRAM_DATA_STRUCTURE))
#define RM_ATV_CHSET_END_ADDR               (RM_ATV_CHSET_START_ADDR + RM_ATV_CHSET_SIZE)

//--------------------------------------------------------------------------------------------

#define RM_CATV_CHSET_START_ADDR            (RM_ATV_CHSET_END_ADDR)

#if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_ATV_SYSTEM || (TV_SYSTEM == TV_NTSC) )
    #define RM_CATV_CHSET_SIZE              (sizeof(CATV_PROGRAM_DATA_STRUCTURE))
#else
    #define RM_CATV_CHSET_SIZE              0
#endif

#define RM_CATV_CHSET_END_ADDR              (RM_CATV_CHSET_START_ADDR + RM_CATV_CHSET_SIZE)

//------------ Over Scan ----------------------------------------------------------------------
#define RM_OVERSCAN_DATA_START_ADR         (RM_CATV_CHSET_END_ADDR)
#if ENABLE_SZ_FACTORY_OVER_SCAN_FUNCTION
#define RM_SIZE_OVERSCAN_DATA               ((U16)SIZE_OVERSCAN_DATA * EN_FACTORY_OverScan_NUM)
#else
#define RM_SIZE_OVERSCAN_DATA                0
#endif
#define RM_OVERSCAN_DATA_END_ADR            (RM_OVERSCAN_DATA_START_ADR + RM_SIZE_OVERSCAN_DATA)

//--------------------------------------------------------------------------------------------

#if( DB_PC_MODE_SAVE_TO_DB_GEN )
#define RM_MODE_SETTING_END_ADR             (RM_OVERSCAN_DATA_END_ADR)
#else
#define RM_MODE_SETTING_START_ADR           (RM_OVERSCAN_DATA_END_ADR) // (RM_CATV_CHSET_END_ADDR)
#define RM_SIZE_MODE_SETTING                (sizeof(MS_PCADC_MODESETTING_TYPE) * MAX_MODE_NUM)
#define RM_MODE_SETTING_END_ADR             (RM_MODE_SETTING_START_ADR + RM_SIZE_MODE_SETTING)
#endif

//--------------------------------------------------------------------------------------------
#if (ENABLE_S2)
#define RM_START_ADDRESS_OF_SAT_DATA_STRUCTURE  (RM_MODE_SETTING_END_ADR)
#define RM_SAT_DATA_STRUCTURE_SIZE              (sizeof(SAT_DATA_STRUCTURE))

#define RM_START_ADDRESS_OF_TP_DATA_STRUCTURE   (RM_START_ADDRESS_OF_SAT_DATA_STRUCTURE+RM_SAT_DATA_STRUCTURE_SIZE)
#define RM_TP_DATA_STRUCTURE_SIZE               (sizeof(TP_DATA_STRUCTURE))

#define RM_S2_SAT_TP_END_ADDR                   (RM_START_ADDRESS_OF_TP_DATA_STRUCTURE + RM_TP_DATA_STRUCTURE_SIZE)

#define RM_DTV_S2_CHSET_START_ADDR              (RM_S2_SAT_TP_END_ADDR)
#define RM_DTV_S2_CHSET_SIZE                    (sizeof(DTV_S2_CHANNEL_DATA_STRUCTURE))
#define RM_DTV_S2_CHSET_END_ADDR                (RM_DTV_S2_CHSET_START_ADDR + RM_DTV_S2_CHSET_SIZE)
#else
#define RM_DTV_S2_CHSET_END_ADDR                (RM_MODE_SETTING_END_ADR)
#endif

//--------------------------------------------------------------------------------------------
#define RM_DTV_CHSET_START_ADDR             RM_DTV_S2_CHSET_END_ADDR
#if( ENABLE_DTV )
#define RM_DTV_CHSET_SIZE               (sizeof(DTV_CHANNEL_DATA_STRUCTURE))
#else
#define RM_DTV_CHSET_SIZE               0
#endif

#define RM_DTV_CHSET_END_ADDR               (RM_DTV_CHSET_START_ADDR + RM_DTV_CHSET_SIZE )

//--------------------------------------------------------------------------------------------

#if (ENABLE_DVBC&&DVB_T_C_DIFF_DB)
    #define RM_DTV_C_CHSET_START_ADDR       (RM_DTV_CHSET_END_ADDR)
    #define RM_DTV_C_CHSET_SIZE             (sizeof(DTV_C_CHANNEL_DATA_STRUCTURE))
    #define RM_DTV_C_CHSET_END_ADDR         (RM_DTV_C_CHSET_START_ADDR+RM_DTV_C_CHSET_SIZE)
#else
    #define RM_DTV_C_CHSET_END_ADDR         (RM_DTV_CHSET_END_ADDR)
#endif

//--------------------------------------------------------------------------------------------

#define RM_DTV_ATSC_CHDATA_START_ADDR       RM_DTV_C_CHSET_END_ADDR

#if(ENABLE_ATSC)
    #define RM_AIR_VIR_CH_START_ADR         (RM_DTV_ATSC_CHDATA_START_ADDR)
    #define RM_AIR_VIR_CH_LEN               ((U16)sizeof(MS_VIRTUAL_CHANNEL) * (MAX_NUM_OF_AIR_VIR_CH+1))

    #define RM_AIR_CH_SETTING_START_ADR     (RM_AIR_VIR_CH_START_ADR + RM_AIR_VIR_CH_LEN)
    #define RM_AIR_CH_SETTING_LEN           ((U16)sizeof(MS_CHANNEL_SETTING))

    #define RM_CATV_VIR_CH_START_ADR        (RM_AIR_CH_SETTING_START_ADR + RM_AIR_CH_SETTING_LEN)
    #define RM_CATV_VIR_CH_LEN              ((U16)sizeof(MS_VIRTUAL_CHANNEL) * (MAX_NUM_OF_CATV_VIR_CH+1))

    #define RM_CATV_CH_SETTING_START_ADR    (RM_CATV_VIR_CH_START_ADR + RM_CATV_VIR_CH_LEN)
    #define RM_CATV_CH_SETTING_LEN          ((U16)sizeof(MS_CHANNEL_SETTING))


    #define RM_ATSC_RF_CH_START_ADR         (RM_CATV_CH_SETTING_START_ADR+RM_CATV_CH_SETTING_LEN)
  #if 1//(NEW_VIRTUAL_CHANNEL_STRUCTURE == ENABLE)
    #define RM_ATSC_AIR_RF_CH_START_ADR     (RM_ATSC_RF_CH_START_ADR)
    #define RM_ATSC_AIR_RF_CH_LEN           (sizeof(MS_RF_CHANNEL_new) * (MAX_AIR_PHYSICAL_CH_NUM+1))
    #define RM_ATSC_CATV_RF_CH_START_ADR    (RM_ATSC_AIR_RF_CH_START_ADR + RM_ATSC_AIR_RF_CH_LEN)
    #define RM_ATSC_CATV_RF_CH_LEN          (sizeof(MS_RF_CHANNEL_new) * (MAX_CATV_PHYSICAL_CH_NUM+1))
    #define RM_ATSC_RF_CH_LEN               (RM_ATSC_AIR_RF_CH_LEN + RM_ATSC_CATV_RF_CH_LEN)
  #else
    #define RM_ATSC_RF_CH_LEN                    0
  #endif

    // MGT+misc
    #define ATSC_RRT5_SETTING_START_ADDR    (RM_ATSC_RF_CH_START_ADR+RM_ATSC_RF_CH_LEN)
    #define ATSC_RRT5_SETTING_SIZE          (sizeof(MS_REGION5_RATING))
    // RRT Descriptor
    #define ATSC_RRT5_DESCRIPTOR_START_ADDR (ATSC_RRT5_SETTING_START_ADDR+ATSC_RRT5_SETTING_SIZE)
    #define ATSC_RRT5_DESCRIPTOR_SIZE       (SIZE_RRT_ALL_DESCRIPTORS)
    // RRT * n
    #define ATSC_RRT5_EZ_REGION_START_ADDR  (ATSC_RRT5_DESCRIPTOR_START_ADDR+ATSC_RRT5_DESCRIPTOR_SIZE)
    #define ATSC_RRT5_EZ_REGION_SIZE        (RRT_SETTING_MEMORIZE_SIZE)

    //#define RM_DTV_ATSC_CHDATA_END_ADDR     (ATSC_RRT5_SETTING_START_ADDR+ATSC_RRT5_SETTING_SIZE)
    #define RM_DTV_ATSC_CHDATA_END_ADDR     (ATSC_RRT5_EZ_REGION_START_ADDR+ATSC_RRT5_EZ_REGION_SIZE)

#else
    #define RM_DTV_ATSC_CHDATA_END_ADDR     RM_DTV_ATSC_CHDATA_START_ADDR
#endif

//--------------------------------------------------------------------------------------------
#define RM_DB_CH_END_ADDR                   (RM_DTV_ATSC_CHDATA_END_ADDR)

#define RM_DB_CH_TOTAL_USAGE_REAL           (RM_DB_CH_END_ADDR - RM_DB_CH_START_ADDR)

#define RM_64K_USAGE                        MemAlign((RM_DB_CH_TOTAL_USAGE_REAL),8)

//--------------------------------------------------------------------------------------------
// Database version for flash case only
// This value is the offset in DB bank
#define RM_DB_VERSION_START_ADDR            (RM_DB_CH_START_ADDR+RM_64K_USAGE)
#define RM_DB_VERSION_SIZE                  12 // DATABASE_ID(x4) + VERSION(x4)
#define RM_DB_VERSION_END_ADDR              (RM_DB_VERSION_START_ADDR + RM_DB_VERSION_SIZE)

//--------------------------------------------------------------------------------------------
// This define is for check ...
#define RM_DB_TOTAL_USAGE                   (RM_DB_VERSION_END_ADDR)

#define RM_DB_CH_AND_VERSION_TOTAL_USAGE    (RM_64K_USAGE + RM_DB_VERSION_SIZE)
//--------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------
// Mapping: The physical memory address to ramdisk
#define RAM_DISK_MEM_ADDR                   ((DATABASE_START_MEMORY_TYPE & MIU1) ? (DATABASE_START_ADR | MIU_INTERVAL) : (DATABASE_START_ADR))
#define RAM_DISK_DB_GEN_START_ADDR          (RAM_DISK_MEM_ADDR + 0)
#define RAM_DISK_DB_GEN_END_ADDR            (RAM_DISK_DB_GEN_START_ADDR + RM_GEN_USAGE)

#define RAM_DISK_DB_64K_START_ADDR          (RAM_DISK_MEM_ADDR + RM_DB_CH_START_ADDR)
#define RAM_DISK_DB_64K_END_ADDR            (RAM_DISK_DB_64K_START_ADDR + RM_DB_CH_AND_VERSION_TOTAL_USAGE)


#if(ENABLE_COMPRESS_DATA)
//    #define DRAM_DB_TOTAL_BANK              (10)
//    #define RM_640K_USAGE                   (RM_64K_USAGE)
    //#define DRAM_640K_DB_START(db_start)    ((db_start)+RM_GEN_SIZE+DRAM_DB_TOTAL_BANK*RM_64K_SIZE-RM_640K_USAGE)
    //#define DRAM_64K_DB_START(db_start)     RAM_DISK_DB_64K_START_ADDR//((db_start)+RM_GEN_SIZE+DRAM_DB_TOTAL_BANK*RM_64K_SIZE-RM_640K_USAGE)
#else
    //#define DRAM_DB_TOTAL_BANK          (10)
    //#define DRAM_64K_DB_START(db_start)         ((db_start)+RM_GEN_SIZE+DB_BANK_COUNT*RM_64K_SIZE-RM_64K_USAGE)
    //#define DRAM_64K_DB_START(db_start)     RAM_DISK_DB_64K_START_ADDR//((db_start)+RM_GEN_SIZE)
#endif

//--------------------------------------------------------------------------------------------

#if (EEPROM_DB_STORAGE!=EEPROM_SAVE_NONE)
INTERFACE void MApp_CheckEEPROM(void);
#endif
#if (EEPROM_DB_STORAGE!=EEPROM_SAVE_ALL)
void MApp_CheckFlash(void);
void MApp_CheckFlash_DB_CH(void);
#endif

//--------------------------------------------------------------------------------------------

INTERFACE U16 MApp_CalCheckSum( BYTE *pBuf, WORD wBufLen );
INTERFACE U16 MApp_CalCheckSum_SkipFirst2Byte( BYTE *pBuf, WORD wBufLen );

//--------------------------------------------------------------------------------------------

INTERFACE void MApp_InitGenSetting(void);
INTERFACE void MApp_LoadGenSetting(void);
INTERFACE void MApp_SaveGenSetting(void);

INTERFACE void MApp_ResetGenUserSetting(void);
INTERFACE void MApp_UpdateGenSettingCS(void);

INTERFACE void MApp_GenSetting_DataCheckHandler(void);

//--------------------------------------------------------------------------------------------

void MApp_SaveData_CallBack_BeforeWriteFlash(void);
//--------------------------------------------------------------------------------------------

INTERFACE void MApp_InitSysSetting(void);
INTERFACE void MApp_CheckSysSetting(void);
//INTERFACE void MApp_LoadSysSetting(void);
INTERFACE void MApp_SaveSysSetting(void);
void MApp_SysSetting_UpdateChecksum(void);
BOOL MApp_SysSetting_IfCheckSumCorrect(void);

//--------------------------------------------------------------------------------------------

#if ENABLE_DRM
INTERFACE void MApp_InitDrmSetting(void);
INTERFACE void MApp_CheckDrmSetting(void);
INTERFACE void MApp_LoadDrmSetting(void);
INTERFACE void MApp_SaveDrmSetting(void);
#endif
//--------------------------------------------------------------------------------------------

//#if (ENABLE_PIP)
INTERFACE void MApp_InitPipSetting(void);
INTERFACE void MApp_CheckPipSetting(void);
INTERFACE void MApp_LoadPipSetting(void);
INTERFACE void MApp_SavePipSetting(void);
//#endif
//--------------------------------------------------------------------------------------------

#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
INTERFACE void MApp_InitNetworkInfoSetting(void);
INTERFACE void MApp_CheckNetworkInfoSetting(void);
INTERFACE void MApp_LoadNetworkInfoSetting(void);
INTERFACE void MApp_SaveNetworkInfoSetting(void);
INTERFACE MS_NETWORKID_TS* MApp_GetNetworkInfo(U8 u8NetworkIndex);
#endif

#if ENABLE_CI
U16 MApp_CiSetting_CalCheckSum(void);
INTERFACE void MApp_InitCISetting(void);
INTERFACE void MApp_CheckCISetting(void);
//INTERFACE void MApp_LoadCISetting(void);
INTERFACE void MApp_SaveCISetting(void);
#endif
//--------------------------------------------------------------------------------------------

#if ENABLE_CI && ENABLE_CI_PLUS
U16 MApp_CiPlusSetting_CalCheckSum(void);
INTERFACE void MApp_InitCIPlusSetting(void);
INTERFACE void MApp_CheckCIPlusSetting(void);
//INTERFACE void MApp_LoadCIPlusSetting(void);
INTERFACE void MApp_SaveCIPlusSetting(void);
#endif

//====================================================================
INTERFACE void MApp_SaveData_ADC_InitSetting(E_ADC_SET_INDEX eAdcIndex );
//INTERFACE void MApp_LoadADCSetting(E_ADC_SET_INDEX eAdcIndex );
//void MApp_SaveADCSetting(E_ADC_SET_INDEX eAdcIndex);
#define MApp_SaveADCSetting MApp_SaveData_ADC_SaveSetting
U8 MApp_GetCalibrationMode(E_ADC_SET_INDEX eAdcIndex);
void MApp_SaveData_ADC_SaveSetting(E_ADC_SET_INDEX eAdcIndex );

void MApp_SaveData_ADC_CheckIfDataCorrect(void);
void MApp_SaveData_ADC_ResetAllSetting(void);

//====================================================================

void MApp_SaveData_Video_InitSetting(E_DATA_INPUT_SOURCE enDataInputSource);
void MApp_SaveData_Video_SaveSetting(E_DATA_INPUT_SOURCE enDataInputSource);
//void MApp_LoadVideoSetting(E_DATA_INPUT_SOURCE enDataInputSource);
void MApp_SaveData_Video_CheckIfDataCorrect(void);
BOOL MApp_SaveData_Video_CheckIfDataChanged(void);

//--------------------------------------------------------------------------------------------

INTERFACE void MApp_InitWhiteBalanceSetting(E_DATA_INPUT_SOURCE enDataInputSource);
INTERFACE void MApp_SaveWhiteBalanceSetting(E_DATA_INPUT_SOURCE enDataInputSource);
INTERFACE void MApp_CopyWhiteBalanceSettingToAllInput(void);
INTERFACE void MApp_CheckWhiteBalanceSetting(void);
//INTERFACE void MApp_LoadWhiteBalanceSetting(E_DATA_INPUT_SOURCE enDataInputSource);
U16 MApp_SaveData_WB_CalCheckSum(U8 u8DataInputSource);
//--------------------------------------------------------------------------------------------

INTERFACE void MApp_InitSubColorSetting(E_DATA_INPUT_SOURCE enDataInputSource);
//INTERFACE void MApp_LoadSubColorSetting(E_DATA_INPUT_SOURCE enDataInputSource);
INTERFACE void MApp_CheckSubColorSetting(void);
INTERFACE void MApp_SaveSubColorSetting(E_DATA_INPUT_SOURCE enDataInputSource);
INTERFACE void MApp_CopySubColorDataToAllInput(void);
//--------------------------------------------------------------------------------------------

INTERFACE void MApp_InitSoundSetting(void);
INTERFACE void MApp_SaveSoundSetting(void);
INTERFACE void MApp_CheckSoundSetting(void);
//--------------------------------------------------------------------------------------------

#if ENABLE_GAMMA_ADJUST
INTERFACE void MApp_InitGammaSetting(void);
INTERFACE void MApp_SaveGammaSetting(void);
INTERFACE void MApp_CheckGammaSetting(void);
INTERFACE void MApp_LoadGammaSetting(void);
#endif
//--------------------------------------------------------------------------------------------
INTERFACE void MApp_InitTimeData(void);
INTERFACE void MApp_SaveTimeData(void);
INTERFACE void MApp_CheckTimeData(void);
INTERFACE void MApp_LoadTimeData(void);
//--------------------------------------------------------------------------------------------

INTERFACE void MApp_InitBlockData(void);
INTERFACE void MApp_CheckBlockData(void);
INTERFACE void MApp_LoadBlockData(void);
INTERFACE void MApp_SaveBlockData(void);
//--------------------------------------------------------------------------------------------

#if ENABLE_SSC
INTERFACE void App_InitSSCData(void);
INTERFACE void MApp_CheckSSCData(void);
INTERFACE void MApp_LoadSSCData(void);
INTERFACE void MApp_SaveSSCData(void);
#endif
//--------------------------------------------------------------------------------------------

#if (ENABLE_NONLINEAR_CURVE)
INTERFACE void MApp_InitNonLinearCurveSetting(void);
INTERFACE void MApp_CheckNonLinearCurveSetting(void);
INTERFACE void MApp_SaveNonLinearCurveSetting(void);
#endif
//--------------------------------------------------------------------------------------------

#if (ENABLE_LAST_MEMORY==1)&&(ENABLE_LAST_MEMORY_STORAGE_SAVE==1)
INTERFACE void MApp_InitMmLastMemorySetting(void);
INTERFACE void MApp_CheckMmLastMemorySetting(void);
INTERFACE void MApp_LoadMmLastMemorySetting(void);
INTERFACE void MApp_SaveMmLastMemorySetting(void);
#endif
//--------------------------------------------------------------------------------------------

INTERFACE void MApp_SetSaveModeDataFlag(void);
INTERFACE void MApp_DataInitVariable(void);

INTERFACE void MApp_DB_LoadModeSetting ( SCALER_WIN eWindow, U8 u8ModeIndex );
INTERFACE void MApp_DB_SaveModeSetting ( SCALER_WIN eWindow, U8 u8ModeIndex );

INTERFACE void MApp_RestoreAllModeTable(SCALER_WIN eWindow);
INTERFACE void MApp_DB_LoadDefaultTable( SCALER_WIN eWindow, U8 u8ModeIndex );
INTERFACE void MApp_RestorePCModeTable( SCALER_WIN eWindow );
INTERFACE void MApp_RestoreComponentModeTable(void);
//--------------------------------------------------------------------------------------------

INTERFACE void MApp_CheckScanMenuSetting(void);
//INTERFACE void MApp_LoadScanMenuSetting(void);
INTERFACE void MApp_InitScanMenuSetting(void);
INTERFACE void MApp_SaveScanMenuSetting(void);
//--------------------------------------------------------------------------------------------

INTERFACE void MApp_SaveData_InitGenSettingExt(void);
INTERFACE void MApp_SaveData_LoadGenSettingExt(void);
//--------------------------------------------------------------------------------------------

INTERFACE BOOL MApp_ReadDatabase(U32 srcIndex, U8* dstAddr, U16 size);
INTERFACE BOOL MApp_WriteDatabase(U32 dstIndex, U8* srcAddr, U16 size);
//--------------------------------------------------------------------------------------------

#if ENABLE_SZ_FACTORY_OVER_SCAN_FUNCTION
INTERFACE void MApp_LoadOverScanData (void);
INTERFACE void MApp_SaveOverScanData (void );
INTERFACE void MApp_InitOverScanData(void);
#endif

//--------------------------------------------------------------------------------------------

#if (ENABLE_SZ_FACTORY_USB_SAVE_DATABASE_FUNCTION == ENABLE)
INTERFACE void MApp_BackupDatabase(void);
INTERFACE void MApp_RestoreDatabase(void);
#endif
//--------------------------------------------------------------------------------------------

#if (ENABLE_UPGRADE_CIPLUSKEY_BY_USB)
BOOLEAN MApp_WriteCiPlus_Key(void);
#endif
#if (ENABLE_UPGRADE_HDCPKEY_BY_USB)
BOOLEAN MApp_WriteHDCP_Key(void);
#endif
#if (ENABLE_CI && ENABLE_CI_PLUS)
INTERFACE void MApp_SaveOpCacheDate(U8 WriteBankIndex, U8 WriteBankNum, BOOLEAN*WriteFinished);

#if(ENABLE_CI_PLUS_V1_4)
INTERFACE void MApp_SaveCIVirtualChannel(U8 WriteBankIndex, U8 WriteBankNum, BOOLEAN*WriteFinished);
#endif
#endif

//--------------------------------------------------------------------------------------------

#if(ENABLE_DTV_EPG)
void MApp_DB_Load_ManualEventSetting(U8* pu8ManualEventData, U32 u32Size);
void MApp_DB_Save_ManualEventSetting(U8* pu8ManualEventData, U32 u32Size);
#endif


//===========================================================
#define DB_VAR_FMAP     BIT0
#define DB_VAR_RAMMAP   BIT1
//#define DB_VAR_RAMMAP   BIT1

void MApp_DB_PrintVar(U8 u8Flag);
BOOL MApp_DB_Check(void);

//=============================================================

typedef enum
{
    E_SAVE_DATA_GEN_SETTING_START,

    E_SAVE_DATA_ID_TV,
    E_SAVE_DATA_ID_HDMI,
    E_SAVE_DATA_ID_DEBUG,
    E_SAVE_DATA_ID_MISC,

#if(ENABLE_DTV_EPG&&DB_MANUAL_EVENT_SAVE_IN_DB_GEN)
    E_SAVE_DATA_ID_MANUAL_EVENT,
#endif

#if ((BRAZIL_CC)||(ATSC_CC == ATV_CC))
    E_SAVE_DATA_ID_CLOSE_CAPTION,
    //Stru_DB_CC_SETTING stCCSetting;
#endif

#if (ENABLE_MFC_6M20||ENABLE_MFC_6M30)
    E_SAVE_DATA_ID_DEV_MFC,
#endif

#if ENABLE_3D_PROCESS
    //Stru3DSetting st3DSetting;
    E_SAVE_DATA_ID_3D_SETTING,
#endif

#if (ENABLE_S2)
    E_SAVE_DATA_ID_DVBS,
#endif

#if( DB_PC_MODE_SAVE_TO_DB_GEN )
    E_SAVE_DATA_ID_PC_MODE,
#endif

#if (ENABLE_ATSC)
    E_SAVE_DATA_ID_ATSC_CAPTION_SETTING,

    E_SAVE_DATA_ID_ATSC_VCHIP_SETTING,
#endif

#if(ENABLE_FM_RADIO)
    E_SAVE_DATA_ID_RADIO_SETTING, //  StuRadioSetting stRadioSetting;
#endif

    E_SAVE_DATA_GEN_SETTING_END,
//--------------------------------------------
    E_SAVE_DATA_FACTORY_SETTING_START,

    E_SAVE_DATA_FACTORY_VD_SETTING,
    E_SAVE_DATA_FACTORY_MISC_SETTING,
  #if ENABLE_PANEL_BIN
    E_SAVE_DATA_FACTORY_PNL_SETTING,
  #endif


    E_SAVE_DATA_FACTORY_SETTING_END,
//----------------------------------------------

    E_SAVE_DATA_ID_GEN_ALL = 0xFD,
    E_SAVE_DATA_ID_FACTORY_ALL = 0xFE,

    E_SAVE_DATA_ID_ALL = 0xFF,
} EnuSaveDataId;

void MApp_SaveData_Check_IfDataCorrect(U8 u8SaveDataId);
BOOL MApp_SaveData_Check_IfDataChanged(U8 u8SaveDataId);
void MApp_SaveData_Update_CheckSum(U8 u8SaveDataId);
void MApp_SaveData_RestoreToDefault(U8 u8SaveDataId);

//==============================================================



#undef INTERFACE

#endif
