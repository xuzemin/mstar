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
\
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////


#ifndef _SW_CONFIG_H_
#define _SW_CONFIG_H_

//SW FEATURES Definition


// EULER
#define SW_CONFIG_TRUNK_EULER_64M_DVBT                  0x0090
#define SW_CONFIG_TRUNK_EULER_128M_DVBT                 0x0091
#define SW_CONFIG_TRUNK_EULER_128M_DVBT_PLUS_T2         0x0092
#define SW_CONFIG_TRUNK_EULER_128M_DVBT_TW              0x0093
#define SW_CONFIG_TRUNK_EULER_64M_ISDBT                 0x0094
#define SW_CONFIG_TRUNK_EULER_128M_ISDBT                0x0095
#define SW_CONFIG_TRUNK_EULER_128M_DTMB                 0x0096
#define SW_CONFIG_TRUNK_EULER_64M_ATVMM                 0x009A
#define SW_CONFIG_TRUNK_EULER_128M_ATVMM                0x009B

// EDEN
#define SW_CONFIG_TRUNK_EDEN_64M_ATVMM                  0x0011
#define SW_CONFIG_TRUNK_EDEN_32M_ATVMM                  0x0012
#define SW_CONFIG_TRUNK_EDEN_64M_ATSC                   0x0013
#define SW_CONFIG_TRUNK_EDEN_64M_ALL                    0x0014
//#define SW_CONFIG_TRUNK_EDEN_64M_ATSC_TTS               0x0015


// EMERALD
#define SW_CONFIG_TRUNK_EMERALD_128M_DVBT               0x0100
#define SW_CONFIG_TRUNK_EMERALD_256M_DVBT               0x0101
#define SW_CONFIG_TRUNK_EMERALD_128M_DVBT_CI_PLUS       0x0102
#define SW_CONFIG_TRUNK_EMERALD_128M_DVBT_CI_PLUS_T2    0x0103
#define SW_CONFIG_TRUNK_EMERALD_128M_DVBT_TW            0x0104
#define SW_CONFIG_TRUNK_EMERALD_128M_DVBT_PlUS_DVBC     0x0105
#define SW_CONFIG_TRUNK_EMERALD_128M_DTMB               0x0106
#define SW_CONFIG_TRUNK_EMERALD_128M_DVBS               0x0107

// NASA
#define SW_CONFIG_TRUNK_NASA_64M_ATVMM                  0x0110
#define SW_CONFIG_TRUNK_NASA_32M_ATVMM                  0x0111
#define SW_CONFIG_TRUNK_NASA_64M_DTMB                   0x0112
#define SW_CONFIG_TRUNK_NASA_64M_DTMB_SZ                0x0113
#define SW_CONFIG_TRUNK_NASA_64M_ALL                    0x0114

// MILAN
#define SW_CONFIG_TRUNK_MILAN_128M_ALL                  0x0120
#define SW_CONFIG_TRUNK_MILAN_64M_ALL                   0x0121

// MULAN
#define SW_CONFIG_TRUNK_MULAN_128M_ALL                  0x0130

// WHISKY
#define SW_CONFIG_TRUNK_WHISKY_64M_ALL                  0x0140
#define SW_CONFIG_TRUNK_WHISKY_128M_ALL                 0x0141
#define SW_CONFIG_TRUNK_WHISKY_128M_AtvMM               0x0142
#define SW_CONFIG_TRUNK_WHISKY_128M_KOR                 0x0143
#define SW_CONFIG_TRUNK_WHISKY_64M_AtvMM                0x0144
#define SW_CONFIG_TRUNK_WHISKY_32M_ALL                  0x0145


// MAYA
#define SW_CONFIG_TRUNK_MAYA_128M_ALL                   0x0150

// MELODY
#define SW_CONFIG_TRUNK_MELODY_32M_AtvMM                0x0160
#define SW_CONFIG_TRUNK_MELODY_64M_AtvMM                0x0161
#define SW_CONFIG_TRUNK_MELODY_64M_ISDB_SZ              0x0162
#define SW_CONFIG_TRUNK_MELODY_32M_AtvMM_CUS_SZ         0x0163

#define ENABLE_854x480_UI ENABLE //gchen @ 20171214
#define VOLUME_STEP 	10 //10 //MP333 gchen @ 20180426
#define VOLUME_THRESHOLD 	0x0C //MP333 // gchen @ 20180526
#define VOLUME_AT	0 //MP333 // gchen @ 20180526 //0:20ms 1:100ms 2: 200ms 3:1000ms
#define VOLUME_RT 	2 //MP333 // gchen @ 20180526 //2: 100ms


// MARLON
#define SW_CONFIG_TRUNK_MARLON_128M_ALL                 0x0170
#define SW_CONFIG_TRUNK_MARLON_64M_ALL                  0x0171
#define SW_CONFIG_TRUNK_MARLON_128M_NTSC                0x0172

// Mazda
#define SW_CONFIG_TRUNK_MAZDA_128M_128M_ALL 0x0180
#define SW_CONFIG_TRUNK_MAZDA_256M_ALL 0x0181
#define SW_CONFIG_TRUNK_MAZDA_256M_ATSC                 0x0182


////////////////////////////////////////////////////////////////////////////////

#define ENABLE_RTC                  1   // 1: Enable RTC Function, 0: Disable RTC Function


//--------- ZUI, related with Panel resolution ----------------------------------
#define UI_SKIN_1280X1024X565       0
#define UI_SKIN_1366X768X565        1
#define UI_SKIN_1440X900X565        2
#define UI_SKIN_1366X768X4444       3
#define UI_SKIN_1366X768X8888       4
//#define UI_SKIN_1280X720X565        5
#define UI_SKIN_960X540X565         6
#define UI_SKIN_960X540XI8          7
#define UI_SKIN_1920X1080X565       8
//*****************************************************************

#ifndef MAYA_LITE
    #define MAYA_LITE 0
#endif

#ifndef ENABLE_ATSC_KOR
    #define ENABLE_ATSC_KOR  0
#endif
//=====================================================================

#define FLASH_SIZE_1MB          0x100000
#define FLASH_SIZE_2MB          0x200000
#define FLASH_SIZE_4MB          0x400000
#define FLASH_SIZE_8MB          0x800000
#define FLASH_SIZE_16MB         0x1000000

#ifndef FORCE_FLASH_SIZE_4M
    #define FORCE_FLASH_SIZE_4M 0
#endif

#ifndef ENABLE_AUDIO_R2_LITE
#define ENABLE_AUDIO_R2_LITE DISABLE
#endif
#ifndef MM_PHOTO_MUSIC_ONLY
#define MM_PHOTO_MUSIC_ONLY DISABLE
#endif

#ifndef ENABLE_FORCE_MM_HD_FB
    #define ENABLE_FORCE_MM_HD_FB    ENABLE //gchen @ 20171220 //for fix video running
#endif
//=====================================================================

// EULER
#if ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_EULER_128M_ATVMM)
    #include "SW_Config_Trunk_EULER_128M_AtvMM.h"
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_EULER_64M_ATVMM)
    #include "SW_Config_Trunk_EULER_64M_AtvMM.h"
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_EULER_64M_DVBT)
    #include "SW_Config_Trunk_EULER_64M_DVBT.h"
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_EULER_128M_DVBT)
    #include "SW_Config_Trunk_EULER_128M_DVBT.h"
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_EULER_128M_DVBT_PLUS_T2)
    #include "SW_Config_Trunk_EULER_128M_DVBT_PLUS_T2.h"
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_EULER_128M_DVBT_TW)
    #include "SW_Config_Trunk_EULER_128M_DVBT_TW.h"
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_EULER_64M_ISDBT)
    #include "SW_Config_Trunk_EULER_64M_ISDBT.h"
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_EULER_128M_ISDBT)
    #include "SW_Config_Trunk_EULER_128M_ISDBT.h"
#elif (MS_SW_CUS_SEL == SW_CONFIG_TRUNK_EULER_128M_DTMB)
    #include "SW_Config_Trunk_EULER_128M_DTMB.h"

// EDEN
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_EDEN_64M_ATVMM)
    #include "SW_Config_Trunk_EDEN_64M_AtvMM.h"
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_EDEN_32M_ATVMM)
    #include "SW_Config_Trunk_EDEN_32M_AtvMM.h"
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_EDEN_64M_ATSC)
    #include "SW_Config_Truck_EDEN_64_ATSC.h"
//#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_EDEN_64M_ATSC_TTS)
//    #include "SW_Config_Truck_EDEN_64_ATSC_TTS.h"
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_EDEN_64M_ALL)
    #include "SW_Config_Truck_EDEN_64_ALL.h"


// EMERALD
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_EMERALD_128M_DVBT)
    #include "SW_CONFIG_TRUNK_EMERALD_128M_DVBT.h"
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_EMERALD_128M_DVBS)
    #include "SW_CONFIG_TRUNK_EMERALD_128M_DVBS.h"
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_EMERALD_256M_DVBT)
    #include "SW_CONFIG_TRUNK_EMERALD_256M_DVBT.h"
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_EMERALD_128M_DVBT_CI_PLUS)
    #include "SW_CONFIG_TRUNK_EMERALD_128M_DVBT_CI_PLUS.h"
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_EMERALD_128M_DVBT_CI_PLUS_T2)
    #include "SW_CONFIG_TRUNK_EMERALD_128M_DVBT_CI_PLUS_T2.h"
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_EMERALD_128M_DVBT_TW)
    #include "SW_CONFIG_TRUNK_EMERALD_128M_DVBT_TW.h"
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_EMERALD_128M_DVBT_PlUS_DVBC)
    #include "SW_CONFIG_TRUNK_EMERALD_128M_DVBT_Plus_DVBC.h"
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_EMERALD_128M_DTMB)
    #include "SW_CONFIG_TRUNK_EMERALD_128M_DTMB.h"


// Milan
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_MILAN_128M_ALL)
    #include "SW_CONFIG_TRUNK_MILAN_128M_ALL.h"
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_MILAN_64M_ALL)
    #include "SW_CONFIG_TRUNK_MILAN_64M_ALL.h"


//Mulan
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_MULAN_128M_ALL)
    #include "SW_CONFIG_TRUNK_MILAN_128M_ALL.h"


// Nasa
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_NASA_32M_ATVMM)
    #include "SW_Config_Trunk_NASA_32M_AtvMM.h"
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_NASA_64M_ATVMM)
    #include "SW_Config_Trunk_NASA_64M_AtvMM.h"
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_NASA_64M_DTMB || MS_SW_CUS_SEL == SW_CONFIG_TRUNK_NASA_64M_DTMB_SZ)
    #include "SW_Config_Trunk_NASA_64M_DTMB.h"
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_NASA_64M_ALL )
    #include "SW_Config_Trunk_NASA_64M_ALL.h"


// Maya
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_MAYA_128M_ALL)
    #include "SW_CONFIG_TRUNK_MAYA_128M_ALL.h"


//Whisky
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_WHISKY_128M_ALL)
    #include "SW_CONFIG_TRUNK_WHISKY_128M_ALL.h"
#elif (MS_SW_CUS_SEL == SW_CONFIG_TRUNK_WHISKY_128M_AtvMM)
    #include "SW_CONFIG_TRUNK_WHISKY_128M_AtvMM.h"
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_WHISKY_64M_ALL)
    #include "SW_CONFIG_TRUNK_WHISKY_64M_ALL.h"
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_WHISKY_32M_ALL)
    #include "SW_CONFIG_TRUNK_WHISKY_32M_ALL.h"
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_WHISKY_64M_AtvMM)
    #include "SW_CONFIG_TRUNK_WHISKY_64M_AtvMM.h"


// MELODY
#elif ( MS_SW_CUS_SEL == SW_CONFIG_TRUNK_MELODY_32M_AtvMM)
    #include "SW_Config_Trunk_MELODY_32M_AtvMM.h"
#elif (MS_SW_CUS_SEL == SW_CONFIG_TRUNK_MELODY_64M_AtvMM)
    #include "SW_Config_Trunk_MELODY_64M_AtvMM.h"
#elif (MS_SW_CUS_SEL == SW_CONFIG_TRUNK_MELODY_64M_ISDB_SZ)
    #include "SW_Config_Trunk_MELODY_64M_ISDB_SZ.h"
#elif (MS_SW_CUS_SEL == SW_CONFIG_TRUNK_MELODY_32M_AtvMM_CUS_SZ)
    #include "SW_Config_Trunk_MELODY_32M_AtvMM_CUS_SZ.h"

// MARLON
#elif (MS_SW_CUS_SEL == SW_CONFIG_TRUNK_MARLON_128M_ALL)
    #include "SW_CONFIG_TRUNK_MARLON_128M_ALL.h"
#elif (MS_SW_CUS_SEL == SW_CONFIG_TRUNK_MARLON_64M_ALL)
    #include "SW_CONFIG_TRUNK_MARLON_64M_ALL.h"
//#elif (MS_SW_CUS_SEL == SW_CONFIG_TRUNK_MARLON_128M_NTSC)
//    #include "SW_CONFIG_TRUNK_MARLON_128M_NTSC.h"

// Mazda
#elif (MS_SW_CUS_SEL == SW_CONFIG_TRUNK_MAZDA_128M_128M_ALL)
    #include "SW_CONFIG_TRUNK_MAZDA_128M_128M_ALL.h"
#elif (MS_SW_CUS_SEL == SW_CONFIG_TRUNK_MAZDA_256M_ALL)
    #include "SW_CONFIG_TRUNK_MAZDA_256M_ALL.h"
#elif (MS_SW_CUS_SEL == SW_CONFIG_TRUNK_MAZDA_256M_ATSC)
    #include "SW_CONFIG_TRUNK_MAZDA_256M_ATSC.h"

#else
    #error "Unknow SW_Feature type"

#endif

/***************************************************************************************/

#include "SW_Config_Default_DTV.h"

#include "SW_Config_Default_DVBS.h"

#include "SW_Config_Default_Scaler.h"

#include "SW_Config_Default_UI.h"


/***************************************************************************************/
#ifndef ENABLE_AUDIO_ONLY_CUSTOMERMODE
#define ENABLE_AUDIO_ONLY_CUSTOMERMODE  DISABLE
#endif

#if(UI_SKIN_SEL ==  UI_SKIN_1366X768X565)

    #define UI_OSD_PANE_W   1366  //not real panel height,the max size of UI area
    #define UI_OSD_PANE_H   768  //not real panel width,the max size of UI area

#elif(UI_SKIN_SEL ==  UI_SKIN_960X540X565 || UI_SKIN_SEL ==  UI_SKIN_960X540XI8)
	#if ENABLE_854x480_UI
	#define UI_OSD_PANE_W	854  //not real panel height,the max size of UI area
	#define UI_OSD_PANE_H	480  //not real panel width,the max size of UI area
	#else
    #define UI_OSD_PANE_W   960  //not real panel height,the max size of UI area
    #define UI_OSD_PANE_H   540  //not real panel width,the max size of UI area
    #endif
#elif(UI_SKIN_SEL ==  UI_SKIN_1920X1080X565)
    #define UI_OSD_PANE_W   1920  //not real panel height,the max size of UI area
    #define UI_OSD_PANE_H   1080  //not real panel width,the max size of UI area

#else
    #panle size define error
#endif


#ifndef ENABLE_LANGUAGE_KOREA
#define ENABLE_LANGUAGE_KOREA                   DISABLE
#endif
/***************************************************************************************/

#ifndef ENABLE_VE
    #define ENABLE_VE   0
#endif

// Force disable function for Boot Lorder

#if (BLOADER)
    #undef  ENABLE_VE
    #define ENABLE_VE   0
#endif


#if (ENABLE_VE == DISABLE)
//Macro comments: all below MACOR must be controlled by ENABLE_VE, it is the head gate.
//    ENABLE_MM_VE_OUTPUT---Enable MM video play output by VE
//    FORCE_ALL_OUTPUT_THROUGH_VE---Enable all input source output through VE, including AV/ATV.
//    ENABLE_OP2_TO_VE---Relative to IP to VE, this output type will output all the mainwindow display to VE, including OSD
#define ENABLE_MM_VE_OUTPUT                 DISABLE
#define FORCE_ALL_OUTPUT_THROUGH_VE         DISABLE
#define ENABLE_OP2_TO_VE                    DISABLE
#endif //#if (ENABLE_VE == DISABLE)

/***************************************************************************************/
#define ENABLE_MUSIC_EQ_MODE 				ENABLE
#define ENABLE_FIX_GREENPANEL_BUG        	DISABLE//wht121220_3 ENABLE   //wht120814_1
#define NEW_MENU_ADJUST_MODE      DISABLE//ENABLE  //wht121116_1
#define SOUNDMODE_EQ                        ENABLE
#define SOUNDMODE_TONE                      ENABLE
#define SOUNDMODE                           SOUNDMODE_EQ
#define SOUND_EQMODE_ENABLE					ENABLE
#define ENABLE_BRAZIL_CC_DETECT_FLAG        DISABLE
#define EANBLE_V56_IO_KEY					ENABLE //gchen @ 20180202 //IO Key Control
#define ENABLE_CHINESE                    DISABLE//ENABLE   //wht121020_2
#define ENABLE_CHINESE_TRADITIONAL DISABLE//ENABLE  //wht121130_1
/***************************************************************************************/

//Note: for demo only!! we use LANGUAGE_SPANISH to display arabic UI, default set to DISABLE.
/// 1. <Mstar_DVB.est> should include Arabic strings.
/// 2. FONT_START_LEN should enlarge for Arabic vector Font.
/// 3. .mk file should include Arabic files.
/// 4. BinInfo.h shold include Arabic files.
#if (ENABLE_ARABIC_OSD)
    #define ENABLE_ARABIC_TEST_UI                   ENABLE
#else
    #define ENABLE_ARABIC_TEST_UI                   DISABLE
#endif

#ifndef ENABLE_TCON_BIN_IN_DB
#define ENABLE_TCON_BIN_IN_DB   DISABLE
#endif

#ifndef CHINESE_SIMP_FONT_ENABLE
    #define CHINESE_SIMP_FONT_ENABLE                DISABLE
#endif


#ifndef CHINESE_BIG5_FONT_ENABLE
    #define CHINESE_BIG5_FONT_ENABLE                DISABLE
#endif

#ifndef ENABLE_TTSTEST_FROM_USB
    #define ENABLE_TTSTEST_FROM_USB                DISABLE
#endif

#ifndef ENABLE_TARGET_REGION
    #define ENABLE_TARGET_REGION                    DISABLE
#endif


#ifndef ENABLE_SAVE_MULTILINGUAL_SERVICE_NAME
    #define ENABLE_SAVE_MULTILINGUAL_SERVICE_NAME   DISABLE
#endif

#ifndef ENABLE_PARENTAL_GUIDANCE_CLASSIFICATION
    #define ENABLE_PARENTAL_GUIDANCE_CLASSIFICATION DISABLE
#endif


#ifndef ENABLE_LCN_CONFLICT
    #define ENABLE_LCN_CONFLICT                     DISABLE
#endif


#define GENSETTING_STORE_USE_NEW_METHOD             ENABLE
#ifndef GENSETTING_STORE_USE_NEW_METHOD
    #define GENSETTING_STORE_USE_NEW_METHOD         DISABLE
#endif

#ifndef ENABLE_FLASH_WRITE_PROTECT_METHOD_M12
    #define ENABLE_FLASH_WRITE_PROTECT_METHOD_M12   0
#endif


#ifndef ENABLE_NO_AUDIO_INPUT_AUTO_MUTE
    #define ENABLE_NO_AUDIO_INPUT_AUTO_MUTE         DISABLE
#endif

#ifndef LOSS_SIGNAL_ALTERNATIVE_ENABLE
    #define LOSS_SIGNAL_ALTERNATIVE_ENABLE          DISABLE
#endif

#ifndef HK_STREAM_NO_NIT_TABLE
    #define HK_STREAM_NO_NIT_TABLE                  DISABLE
#endif

#ifndef MM_1080I_USE_FB
    #define MM_1080I_USE_FB                         DISABLE
#endif

#ifndef ENABLE_EPG_MUX
    #define ENABLE_EPG_MUX                          DISABLE
#endif

#ifndef ENABLE_NZ_FREEVIEW
    #define ENABLE_NZ_FREEVIEW                      DISABLE
#endif

#ifndef ENABLE_RIKS_TV
    #define ENABLE_RIKS_TV                          DISABLE
#endif

#ifndef ENABLE_ZIGGO
#define ENABLE_ZIGGO                                DISABLE
#endif

#ifndef ENABLE_CANAL_DIGITAL
#define ENABLE_CANAL_DIGITAL                        DISABLE
#endif

#ifndef ENABLE_FAVORITE_NETWORK
  #if ENABLE_RIKS_TV
    #define ENABLE_FAVORITE_NETWORK                 ENABLE
#else
    #define ENABLE_FAVORITE_NETWORK                 DISABLE
  #endif
#endif

#ifndef ENABLE_UART2
    #define ENABLE_UART2                            DISABLE
#endif

#ifndef ENABLE_ARC_CHANGE_SPDIF
#define ENABLE_ARC_CHANGE_SPDIF                     DISABLE
#endif

#ifndef ENABLE_SUPPORT_MM_PHOTO_4K_2K
    #define ENABLE_SUPPORT_MM_PHOTO_4K_2K           DISABLE
#endif


#ifndef ENABLE_MSTV_UART_DEBUG
    #define ENABLE_MSTV_UART_DEBUG          1
#endif

#define ROBUST_TEST_ENABLE              0

#if ROBUST_TEST_ENABLE
#undef ENABLE_MSTV_UART_DEBUG
#define ENABLE_MSTV_UART_DEBUG          1
#endif

#ifndef ENABLE_MMS
    #define ENABLE_MMS      0
#endif

#ifndef ENABLE_DOLBY_BULLETIN24
#define ENABLE_DOLBY_BULLETIN24     0
#endif

#ifndef ENABLE_AFD_FOR_SGP_MDA
#define ENABLE_AFD_FOR_SGP_MDA                  DISABLE
#endif

//---- Autotest ----------------------------------------------------------------
#ifndef CHAKRA3_AUTO_TEST
    #define CHAKRA3_AUTO_TEST       DISABLE
#endif

#define ENABLE_AUTOTEST             CHAKRA3_AUTO_TEST


#ifndef ENABLE_SAVE_DATA_TO_EEPROM
    #define ENABLE_SAVE_DATA_TO_EEPROM  0
#endif

//******************************************************************************

#ifndef ENABLE_AEON_MEM_USE_MIU_PROTECT
    #define ENABLE_AEON_MEM_USE_MIU_PROTECT     TRUE
#endif
#if( ENABLE_AEON_MEM_USE_MIU_PROTECT )
    #define AEON_MEM_USE_MIU_PROTECT_BLOCK_ID   2
#endif

//******************************************************************************

#ifndef ENABLE_DATA_BASE_GEN_USE_2014
    #define ENABLE_DATA_BASE_GEN_USE_2014   1
#endif

#ifndef ENABLE_DRAM_GEN_SAVE_TO_FLASH
    #define ENABLE_DRAM_GEN_SAVE_TO_FLASH   (EEPROM_DB_STORAGE==EEPROM_SAVE_NONE)
#endif

#ifndef ENABLE_DRAM_GEN_SAVE_TO_EEPROM
    #define ENABLE_DRAM_GEN_SAVE_TO_EEPROM  (EEPROM_DB_STORAGE!=EEPROM_SAVE_NONE)
#endif

#ifndef ENABLE_DRAM_DB_CH_SAVE_TO_FLASH
    #define ENABLE_DRAM_DB_CH_SAVE_TO_FLASH (EEPROM_DB_STORAGE!=EEPROM_SAVE_ALL)
#endif

#ifndef ENABLE_DRAM_DB_CH_SAVE_TO_EEPROM
    #define ENABLE_DRAM_DB_CH_SAVE_TO_EEPROM (EEPROM_DB_STORAGE==EEPROM_SAVE_ALL)
#endif

#ifndef ENABLE_FACTORY_SETTING_IN_SEPERATE_BANK
    #define ENABLE_FACTORY_SETTING_IN_SEPERATE_BANK     0
#endif

#ifndef DB_MANUAL_EVENT_SAVE_IN_DB_GEN
    #if(ENABLE_CI_PLUS )
        #define DB_MANUAL_EVENT_SAVE_IN_DB_GEN      1
    #else
        #define DB_MANUAL_EVENT_SAVE_IN_DB_GEN      0
    #endif
#endif

//******************************************************************************
#ifndef ENABLE_AUDIO_DSP_BIN
    #define ENABLE_AUDIO_DSP_BIN        FALSE
#endif

#ifndef ENABLE_AUDIO_DEC_R2_BIN
    #define ENABLE_AUDIO_DEC_R2_BIN        FALSE
#endif

#ifndef ENABLE_AUDIO_DEC_R2_BIN_COMPRESS
    #define ENABLE_AUDIO_DEC_R2_BIN_COMPRESS    FALSE
#endif


#ifndef ENABLE_HK_LOAD_MM_VDEC
    #define ENABLE_HK_LOAD_MM_VDEC          FALSE
#endif

#ifndef ENABLE_OD_BIN
    #define ENABLE_OD_BIN           0
#endif

//******************************************************************************

#ifndef ENABLE_SWITCH_CHANNEL_TIME
    #define ENABLE_SWITCH_CHANNEL_TIME      DISABLE
#endif

//******************************************************************************

#ifndef ENABLE_TEST_PATTERN
    #define ENABLE_TEST_PATTERN         DISABLE
#endif
#ifndef ENABLE_BMP_TEST_PATTERN
    #define ENABLE_BMP_TEST_PATTERN     0
#endif

//******************************************************************************
// ZUI option:
#ifndef ENABLE_FACTORY_POWER_ON_MODE
    #define ENABLE_FACTORY_POWER_ON_MODE    DISABLE
#endif

#ifndef ENABLE_DESIGN_POWER_ON_MODE
    #define ENABLE_DESIGN_POWER_ON_MODE     DISABLE
#endif

#ifndef ENABLE_DESIGN_WHITE_BALANCE_TEST_PATTERN
    #define ENABLE_DESIGN_WHITE_BALANCE_TEST_PATTERN    DISABLE
#endif

//******************************************************************************
#ifndef ENABLE_R2_BACKTRACE
    #define ENABLE_R2_BACKTRACE     0
#endif

//******************************************************************************
#ifndef ENABLE_VCHIP_REGION5
    #define ENABLE_VCHIP_REGION5        0
#endif

//=======================================================
// ATSC-ZUI option:
#ifndef ENABLE_ATSC_EPG_UI
    #define ENABLE_ATSC_EPG_UI          DISABLE
#endif
#ifndef ENABLE_ATSC_MENU_UI
    #define ENABLE_ATSC_MENU_UI         DISABLE
#endif
#ifndef ENABLE_ATSC_MENU_LOCK_UI
    #define ENABLE_ATSC_MENU_LOCK_UI    DISABLE
#endif
#ifndef ENABLE_ATSC_MENU_OPTION_UI
    #define ENABLE_ATSC_MENU_OPTION_UI  DISABLE
#endif
#ifndef ENABLE_ATSC_INSTALLGUIDE
    #define ENABLE_ATSC_INSTALLGUIDE    DISABLE
#endif
#ifndef OSD_TRANSPARENCY_PER25
    #define OSD_TRANSPARENCY_PER25      ENABLE
#endif

#ifndef ENABLE_EASMONITOR
    #define ENABLE_EASMONITOR   DISABLE
#endif

#ifndef ENABLE_ATSC_AD_FUNC
    #define ENABLE_ATSC_AD_FUNC DISABLE
#endif

//----------------------------------------------------------------------------

#ifndef ENABLE_ATSC_TTS
    #define ENABLE_ATSC_TTS     DISABLE
#endif

#ifndef TTS_IS_ON_HK
    #define TTS_IS_ON_HK    1//DISABLE
#endif
//******************************************************************************

#ifndef ENABLE_SECURITY_R2_HDCP22
    #define ENABLE_SECURITY_R2_HDCP22      0
#endif

#ifndef ENABLE_SECURITY_R2
    #if( (!BLOADER) \
       &&(ENABLE_SECURITY_R2_HDCP22 || (ENABLE_ATSC_TTS && (TTS_IS_ON_HK == 0)) ) \
       )
        #define ENABLE_SECURITY_R2 1
    #else
        #define ENABLE_SECURITY_R2 0
    #endif
#endif

#define ENABLE_SECU_R2 ENABLE_SECURITY_R2

//----------------------------------------------------------------------------

#ifndef HDCP22_KEY_TYPE
    #define HDCP22_KEY_TYPE      HDCP22_KEY_NONE
#endif

#ifndef ENABLE_TTX_ANALOG
    #define ENABLE_TTX_ANALOG       (ENABLE_TTX&&(!ENABLE_ATSC))
#endif

//----------------------------------------------------------------------------
#ifndef ENABLE_3D_PROCESS
    #define ENABLE_3D_PROCESS  0
#endif
//******************************************************************************

#ifndef ENABLE_CVBSOUT_2
    #define ENABLE_CVBSOUT_2    0
#endif

#ifndef KOREAN_CC_ENABLE
    #define KOREAN_CC_ENABLE        DISABLE
#endif

#ifndef ATSC_READY
    #define ATSC_READY              0
#endif

#ifndef ENABLE_NO_OPERATE_AUTO_SLEEP
    #define ENABLE_NO_OPERATE_AUTO_SLEEP    ENABLE
#endif

#ifndef ENABLE_SBOOT_LOAD_BIN
    #define ENABLE_SBOOT_LOAD_BIN   DISABLE
#endif

#ifndef FORCE_VDEC_BIN_NO_COMPRESS
    #define FORCE_VDEC_BIN_NO_COMPRESS  DISABLE
#endif

#ifndef ENABLE_GAMMA_ADJUST
    #define ENABLE_GAMMA_ADJUST         DISABLE
#endif

#ifndef ENABLE_S2_FAST_SCAN
    #define ENABLE_S2_FAST_SCAN         DISABLE
#endif

#ifndef MEDIASET_PREMIUM_SMART_CAM
    #define MEDIASET_PREMIUM_SMART_CAM  DISABLE
#endif


#ifndef ENABLE_CIPLUS_PVR
    #define ENABLE_CIPLUS_PVR                                 DISABLE
#endif

#ifndef ENABLE_FLASH_ON_DRAM
    #define ENABLE_FLASH_ON_DRAM    DISABLE
#endif

#ifndef ENABLE_PQ_TABTYPE_XVYCC
    #define ENABLE_PQ_TABTYPE_XVYCC    DISABLE
#endif

#ifndef ENABLE_IC_LVDS_SWAP
    #define ENABLE_IC_LVDS_SWAP    DISABLE
#endif

#ifndef ENABLE_BIN_FILE_CRC
    #define ENABLE_BIN_FILE_CRC     0
#endif

#ifndef ENABLE_DMP_MINI_MENU
    #define ENABLE_DMP_MINI_MENU        DISABLE
#endif

#ifndef ENABLE_HDR
    #define ENABLE_HDR        DISABLE
#endif

#ifndef ENABLE_OPEN_HDR
    #define ENABLE_OPEN_HDR        DISABLE
#endif

#ifndef ENABLE_DOLBY_HDR
    #define ENABLE_DOLBY_HDR       DISABLE
#endif

#define ENABLE_LIGHT_MODE                 DISABLE//wht1200906_2 ENABLE   //wht120725_2
//=================================================================
//gchen @ 20171207 //V56 Projector
#define ENABLE_HIGH_AND_LOW_LIGHT_SWITCH 	DISABLE
#define FIX_STARTUP_COLOR_DISTORTION 		ENABLE //MP333
#define ENABLE_USB_ITEM_IN_SOURCE_MENU    	ENABLE
#define REMOVE_DRIVE_SELECT_TO_FILE_LIST                ENABLE//DISABLE  //wht120418_1
#define ENABLE_PROGRESS_BAR						ENABLE
#define ENABLE_DPP3435						DISABLE	//gchen @ 20180317
#define ENABLE_DPP2607						ENABLE	//gchen @ 20180317
#define ENABLE_EAR_PHONE_VALUME_LINE		ENABLE  //MP333
//=================================================================
#include "sw_config_force_off_for_bloader.h"
//******************************************************************************

#endif // #ifndef _SW_CONFIG_H_

