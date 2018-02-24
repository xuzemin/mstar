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

#ifndef MAPP_RESTORETODEFAULT_H
#define MAPP_RESTORETODEFAULT_H

#include "MApp_GlobalSettingSt.h"

//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
#if ENABLE_ATSC_EPG_UI
/* total accumulative seconds from 1980 Jan/6 00:00:00 to 2000 Jan/1 00:00:00 */
//hint: (2000 1/1 0:0:0 ~ 1980 1/1 0:0:0) - (1980 1/6 0:0:0 ~ 1980 1/1 0:0:0)
#define DEFAULT_SYSTEM_TIME                0    // 630720000
#endif

#define DEFAULT_DATABASE_VERSION                0x06//0x05
#define DEFAULT_DATABASE_VERSION_COM            0xF3//0xF2

#define DEFAULT_VCH_DATABASE_VERSION            0xAA58

#define DEFAULT_SCAN_SRV_TYPE                   FTA
#define DEFAULT_RF_CHANNEL                      CHAN_AIR_MIN
#define DEFAULT_CABLE_SYSTEM                    CABLE_SYSTEM_AUTO //Mantis 960766 fixed//CABLE_SYSTEM_STD

#define DEFAULT_VOLUME_SETTING                  20
#define DEFAULT_AD_MIX_SETTING                  25
#define DEFAULT_BALANCE_SETTING                 50
#define DEFAULT_TIME_ZONE                       EN_D1_Clock_TimeZone_Eastern

#define DEFAULT_TIME_DST                        TIME_DST_OFF

#define DEFAULT_GENERAL_PASSWORD                0x00
#define DEFAULT_AUTO_VOLUME                     0x00    //Film Mode
#define DEFAULT_ENABLE_CINEMA                   0x00    //Film Mode

////////////////////////////////////////////////////////////////////////////////
// default base date = 1980 Jan/1 00:00:00
#define DEFAULT_MJD                             44239 //51544
#define DEFAULT_YEAR                            1980  //2000
#define DEFAULT_MONTH                           1
#define DEFAULT_DAY                             1
#define DEFAULT_DAY_ATSC                        6
#define DEFAULT_HOUR                            0
#define DEFAULT_MIN                             0
#define DEFAULT_SEC                             0

////////////////////////////////////////////////////////////////////////////////

#define DEFAULT_OSD_DURATION                    OSD_DURATION_40_SEC
#define DEFAULT_INFO_DURATION                   INFO_DURATION_4_SEC

//--------------------------------------------------------------------------
#if(ENABLE_ATSC)
   #define DEFAULT_TRANSPARENCY                   (63*100/7) // 0
   #define TRANSPARENCY_0_PERCENTAGE_VALUE (DEFAULT_TRANSPARENCY)
 #if OSD_TRANSPARENCY_PER25
   #define TRANSPARENCY_25_PERCENTAGE_VALUE       DEFAULT_TRANSPARENCY-100
   #define TRANSPARENCY_50_PERCENTAGE_VALUE       DEFAULT_TRANSPARENCY-100*2
   #define TRANSPARENCY_75_PERCENTAGE_VALUE       DEFAULT_TRANSPARENCY-100*3
   #define TRANSPARENCY_100_PERCENTAGE_VALUE       DEFAULT_TRANSPARENCY-100*4
 #else
   #define TRANSPARENCY_15_PERCENTAGE_VALUE (DEFAULT_TRANSPARENCY-(100*1))
   #define TRANSPARENCY_30_PERCENTAGE_VALUE (DEFAULT_TRANSPARENCY-(100*2))
   #define TRANSPARENCY_45_PERCENTAGE_VALUE (DEFAULT_TRANSPARENCY-(100*3))
   #define TRANSPARENCY_60_PERCENTAGE_VALUE (DEFAULT_TRANSPARENCY-(100*4))
   #define TRANSPARENCY_75_PERCENTAGE_VALUE (DEFAULT_TRANSPARENCY-(100*5))
   #define TRANSPARENCY_100_PERCENTAGE_VALUE (DEFAULT_TRANSPARENCY-(100*6))
 #endif
#endif
//--------------------------------------------------------------------------


#if (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP||CHINESE_SIMP_FONT_ENABLE ||CHINESE_BIG5_FONT_ENABLE)
#define DEFAULT_MENU_LANG                       LANGUAGE_CHINESE
#else
#define DEFAULT_MENU_LANG                       LANGUAGE_ENGLISH
#endif
#define DEFAULT_SUB_LANG                        LANGUAGE_ENGLISH


#if(ENABLE_ISDBT_AND_DVB)
    EN_OSD_COUNTRY_SETTING MApp_DataBase_Get_Default_Country(void);
    #define DEFAULT_TUNING_COUNTRY              MApp_DataBase_Get_Default_Country()
#elif (ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
    #define DEFAULT_TUNING_COUNTRY              OSD_COUNTRY_CHINA
#elif (ENABLE_ISDBT_NO_DVB)
    #define DEFAULT_TUNING_COUNTRY              OSD_COUNTRY_BRAZIL
#else
    #define DEFAULT_TUNING_COUNTRY              OSD_COUNTRY_UK
#endif


#if(DVBC_CERTIFICATION_AUTOSCAN_ENABLE)
#define DEFAULT_TUNING_CERTIFICATION             OSD_CERTIFICATION_OTHER
#define DEFAULT_TUNING_UNITYMEDIA_COUNTRY        OSD_UNITYMEDIA_COUNTRY_GERMANY
#define DEFAULT_TUNING_ZIGGO_COUNTRY             OSD_ZIGGO_COUNTRY_NETHERLANDS
#endif

//#ifdef TV_SETTING//kitty0928
#define INIT_VEDIO_SDTV_BRI_STD                 50//00//50
#define INIT_VEDIO_SDTV_CON_STD                 50//33//50
#define INIT_VEDIO_SDTV_HUE_STD                 50
#define INIT_VEDIO_SDTV_SAT_STD                 50
#define INIT_VEDIO_SDTV_SHARP_STD               47

#define INIT_VEDIO_HDTV_BRI_STD                 50
#define INIT_VEDIO_HTDV_CON_STD                 50
#define INIT_VEDIO_HDTV_HUE_STD                 50
#define INIT_VEDIO_HDTV_SAT_STD                 50
#define INIT_VEDIO_HDTV_SHARP_STD               47

#define INIT_VEDIO_SDTV_BRI_MOVIE               50
#define INIT_VEDIO_SDTV_CON_MOVIE               40
#define INIT_VEDIO_SDTV_HUE_MOVIE               50
#define INIT_VEDIO_SDTV_SAT_MOVIE               30
#define INIT_VEDIO_SDTV_SHARP_MOVIE             20

#define INIT_VEDIO_HDTV_BRI_MOVIE               00//50
#define INIT_VEDIO_HTDV_CON_MOVIE               33//40
#define INIT_VEDIO_HDTV_HUE_MOVIE               50
#define INIT_VEDIO_HDTV_SAT_MOVIE               30
#define INIT_VEDIO_HDTV_SHARP_MOVIE             10//20

#define INIT_VEDIO_SDTV_BRI_VIVID               80
#define INIT_VEDIO_SDTV_CON_VIVID               70
#define INIT_VEDIO_SDTV_HUE_VIVID               50
#define INIT_VEDIO_SDTV_SAT_VIVID               70
#define INIT_VEDIO_SDTV_SHARP_VIVID             60

#define INIT_VEDIO_HDTV_BRI_VIVID               80
#define INIT_VEDIO_HTDV_CON_VIVID               70
#define INIT_VEDIO_HDTV_HUE_VIVID               50
#define INIT_VEDIO_HDTV_SAT_VIVID               70
#define INIT_VEDIO_HDTV_SHARP_VIVID             60

#define INIT_VEDIO_SDTV_BRI_USER                50
#define INIT_VEDIO_SDTV_CON_USER                50
#define INIT_VEDIO_SDTV_HUE_USER                50
#define INIT_VEDIO_SDTV_SAT_USER                70
#define INIT_VEDIO_SDTV_SHARP_USER              70

#define INIT_VEDIO_HDTV_BRI_USER                50
#define INIT_VEDIO_HTDV_CON_USER                50
#define INIT_VEDIO_HDTV_HUE_USER                50
#define INIT_VEDIO_HDTV_SAT_USER                50
#define INIT_VEDIO_HDTV_SHARP_USER              50
//#endif //~TV_SETTING

////////////////////////////////////////////////////////////////////////////////
// restore all mask
#define RESTORE_KEEP_NONE                       (0x0)

#define RESTORE_KEEP_SYSTEM_LANGUAGE            (0x0001)
#define RESTORE_KEEP_SYSTEM_PASSWORD            (0x0002)
#define RESTORE_KEEP_SYSTEM_TIME                (0x0004)

#define DEFAULT_D_ONTIME_CH  0 // this value must be 1,
                               // bcz when we restore both general and channel setting
                               // the database only have 1 dummy ch "2-1"

#define RESTORE_GENSETTING      0x01
#define RESTORE_DATABASE        0x02
#define RESTORE_USERSETTING     0x03

typedef enum
{
    OSD_DURATION_5_SEC,
    OSD_DURATION_10_SEC,
    OSD_DURATION_15_SEC,
    OSD_DURATION_20_SEC,
    OSD_DURATION_25_SEC,
    OSD_DURATION_30_SEC,
    OSD_DURATION_35_SEC,
    OSD_DURATION_40_SEC,
    OSD_DURATION_45_SEC,
    OSD_DURATION_50_SEC,
    OSD_DURATION_55_SEC,
    OSD_DURATION_60_SEC,
    OSD_DURATION_NUM
} EN_OSD_DURATION;

typedef enum
{
    //INFO_DURATION_0_SEC,
    INFO_DURATION_2_SEC,
    INFO_DURATION_4_SEC,
    INFO_DURATION_6_SEC,
    INFO_DURATION_8_SEC,
    INFO_DURATION_10_SEC,
    INFO_DURATION_NUM
} EN_INFO_DURATION;

typedef enum
{
    MODE_ON,
    MODE_OFF,
    MODE_NUM
} EN_ONOFF_MODE;

//------------------------------------------------------------------------------
// Function Prototypes
//------------------------------------------------------------------------------
#ifdef MAPP_RESTORETODEFAULT_C
#define INTERFACE
#else
#define INTERFACE extern
#endif


void MApp_DataBase_RestoreDefault_By_Country(EN_OSD_COUNTRY_SETTING eOSD_Country);

INTERFACE void MApp_DataBase_RestoreDefaultSystem(U16 u16KeepSetting);
void MApp_DataBase_RestoreDefault_TVSetting(void);

INTERFACE void MApp_DataBase_RestoreDefaultVideo(E_DATA_INPUT_SOURCE enDataInputSource);
INTERFACE void MApp_DataBase_RestoreDefaultWhiteBalance(E_DATA_INPUT_SOURCE enDataInputSource);
INTERFACE void MApp_DataBase_PictureResetWhiteBalance(E_DATA_INPUT_SOURCE enDataInputSource);

INTERFACE void MApp_DataBase_RestoreDefaultSubColor(E_DATA_INPUT_SOURCE enDataInputSource);

INTERFACE void MApp_DataBase_RestoreDefaultAudio(BOOL bSetDriver);
INTERFACE void MApp_DataBase_RestoreDefaultScanMenu(void);
INTERFACE void MApp_DataBase_RestoreDefaultTime(void);

#if( ENABLE_ISDBT_AND_DVB )
U8 MApp_DataBase_Get_Default_LockSystem_Min(void);
#endif
INTERFACE void App_DataBase_RestoreDefaultBlock(void);
INTERFACE void MApp_DataBase_RestoreDefaultGammaTable(void);

INTERFACE void MApp_DataBase_RestoreDefaultSSC(void);

#if (ENABLE_NONLINEAR_CURVE)
INTERFACE void MApp_DataBase_RestoreDefaultNonLinearCurve(void);
#endif

INTERFACE void MApp_DataBase_RestoreDefault_FactoryVDSetting(void);
INTERFACE void MApp_DataBase_RestoreDefault_FactoryMiscSetting(void);
#if ENABLE_PANEL_BIN
INTERFACE void MApp_DataBase_RestoreDefault_FactoryPnlSetting(void);
#endif


INTERFACE void MApp_DataBase_RestoreDefaultFactorySetting(void);

INTERFACE void MApp_DataBase_RestoreDefaultValue(U16 u16KeepSetting);

INTERFACE void MApp_DataBase_RestoreUserSettingDefaultValue(U16 u16KeepSetting);

INTERFACE void MApp_DataBase_RestoreDefaultADC(E_ADC_SET_INDEX eAdcIndex );
#if ENABLE_DRM
INTERFACE void MApp_Drm_RestoreDefaultSetupInfo(void);
#endif

//#if (ENABLE_PIP)
INTERFACE void MApp_DataBase_RestoreDefaultPIP(void);
//#endif
#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
INTERFACE void MApp_DataBase_RestoreDefaultNetworkInfo(void);
#endif
INTERFACE void MApp_DataBase_RestoreFactoryDefault(U8 u8RestoreMask);
INTERFACE void MApp_DataBase_RestoreUserSettingDefault(U8 u8RestoreMask);

#if ENABLE_CI
void MApp_DataBase_RestoreDefault_CI(void);
INTERFACE void MApp_DataBase_RestoreDefault_CIPlus(void);
#endif

#if (ENABLE_LAST_MEMORY==1)&&(ENABLE_LAST_MEMORY_STORAGE_SAVE==1)
INTERFACE void MApp_DataBase_RestoreDefaultMmLastMemorySetting(void);
#endif

#if(ENABLE_S2)
INTERFACE void MApp_DataBase_RestoreDefaultSatlite(void);
void MApp_DataBase_RestoreDefault_DvbsSetting(void);
#endif

void MApp_DataBase_RestoreDefault_MiscSetting(void);

void MApp_DataBase_RestoreDefault_DebugSetting(void);

#if (ENABLE_MFC_6M20||ENABLE_MFC_6M30)
void MApp_DataBase_RestoreDefault_DevMfcSetting(void);
#endif
#if ENABLE_3D_PROCESS
void MApp_DataBase_RestoreDefault_3DSetting(void);
#endif
#if ((BRAZIL_CC)||(ATSC_CC == ATV_CC))
void MApp_DataBase_RestoreDefault_CloseCaptionSetting(void);
#endif

void MApp_DataBase_RestoreDefault_HDMISetting(void);

#if(ENABLE_DTV_EPG)
void MApp_DataBase_RestoreDefault_ManualEvent(void);
#endif

#if( DB_PC_MODE_SAVE_TO_DB_GEN )
void MApp_DataBase_RestoreDefault_PcModeSetting(void);
#endif


#if(ENABLE_ATSC)
void MApp_DataBase_RestoreDefault_CaptionSetting(void);
void MApp_DataBase_RestoreDefault_VChip(void);
void MApp_DataBase_RestoreDefault_VChipRegion5(void);
#endif

#undef INTERFACE

#endif

