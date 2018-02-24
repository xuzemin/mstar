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

#ifndef MAPP_GlOBALVAL_H
#define MAPP_GlOBALVAL_H

#include "Board.h"
#include "datatype.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "apiDMX.h"
#include "apiXC_Sys.h"
#include "msAPI_Global.h"
#include "msAPI_OSD.h"
#include "msAPI_DTVSystem.h"

#if ENABLE_DMP
#include "MApp_Scaler.h"
#endif
#include "MApp_GlobalSettingSt.h"
#if 0//(ENABLE_S2)
#include "MApp_GlobalSettingSt_tv_S2.h"
#endif

#include "msAPI_Tuner.h"

#if ENABLE_DTV
#include "mapp_demux.h"
#endif

#if (ENABLE_ATSC)
#include "MApp_GlobalVar_ATSC.h"
#endif

#ifdef MAPP_MAIN_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

INTERFACE U8 u8KeyCode;
/* ~ ir_drv.c */


//ZUI_TODO: INTERFACE U8 u8ServiceTypeForMenuStr;
//ZUI_TODO: INTERFACE U16 g_wProgramPosition; // for text call back to get program name and number by index.
INTERFACE S16 g_u16ChannelOrinigalIndex;

//ZUI_TODO: INTERFACE U16 g_u16RecentMajor, g_u16RecentMinor;
//ZUI_TODO: INTERFACE U8 g_u8RecentSourceType;
//ZUI_TODO: INTERFACE U16 g_fRecentIsOnePartCh;



//INTERFACE S32 s32OffsetTime;
INTERFACE ST_TIME _stDate;


//ZUI_TODO: INTERFACE U8 iu8Loop_i,iu8Loop_j;
//ZUI_TODO: INTERFACE U8 iu8Buffer_i;

//ZUI_TODO: INTERFACE U16 iu16Loop_i;
//ZUI_TODO: INTERFACE U16 iu16Buffer_i;

//ZUI_TODO: INTERFACE U8 *iu8Ptr;

INTERFACE U8 iu8Loop_i,iu8Loop_j;

INTERFACE U16 iu16Loop_i;
//INTERFACE U16 iu16Buffer_i;

INTERFACE U8 *iu8Ptr;


#if ENABLE_DMP
INTERFACE U8 u8MainOSDWinId;
INTERFACE U8 g_u8MuteStatus;
#endif

#if  ((ATSC_CC == ATV_CC)||BRAZIL_CC)
INTERFACE BOOLEAN fEnableClosedCaptionFunc;// user decide from OSD Menu
INTERFACE U8 g_u8CCType_Option;
#endif

//ZUI_TODO: INTERFACE U8 u8OSDGWinTbl[MAXNUM_GWIN];

//ZUI_TODO: INTERFACE U8 OSDDuration;            // OSD idle time
//INTERFACE U8 InfoDuration;           // Info plate idle time
//ZUI_TODO: INTERFACE U8 Transparency;

INTERFACE U32 g_u32Section[4096/sizeof(U32)];    //section data buffer
#define au8Section ((U8*)g_u32Section)

// 2048 -> 3076
//INTERFACE U16 au8StringBuffer[1024];// U32 (au8Section+((MSAPI_DMX_SECTION_1K<<2)/sizeof(U32)))
// 3076 -> 4096
//INTERFACE U16 au8StringBuffer2[1024];// (au8Section+((MSAPI_DMX_SECTION_1K<<2)/sizeof(U32))+(MSAPI_DMX_SECTION_1K/sizeof(U32)))

//INTERFACE U8 cIsBlocked;
//INTERFACE BOOLEAN bIsBlocked;
INTERFACE OSDClrBtn clrBtn1;
INTERFACE OSDClrLine g_ClrLine;
INTERFACE MSAPI_GEBitmapFmt gbmpfmt;

#if (ENABLE_MFC_6M20||ENABLE_MFC_6M30)
INTERFACE U8 g_u8MEMCFlag;
#endif

//ZUI_TODO: INTERFACE U8 u8ChannelLabel[MAX_STATION_NAME];
//ZUI_TODO: INTERFACE U8 IsInEditChannelName;
//ZUI_TODO: INTERFACE U8 InEditChannelNameOrder;


//INTERFACE BOOLEAN g_bPCSignalMonitor;
INTERFACE U8 g_u8PCSignalMonitorCounter;

//use for 1st time, clock setting from manual to auto (if default is manual)
//ZUI_TODO: INTERFACE BOOLEAN g_bFirstManual2Auto;
//use for redraw time val in clock setting
//ZUI_TODO: INTERFACE BOOLEAN g_bAutoTimeRedraw;
//ZUI_TODO: INTERFACE U8 u8PreviousPCModeIndex;


INTERFACE BOOLEAN bNextEvent;
//INTERFACE DTV_CHANNEL_INFO  chData;
//INTERFACE U16 u16RADIO_Num;
//INTERFACE U16 u16TV_Num;
//INTERFACE BOOLEAN bIsInsideDTVManualScanMenu;

//INTERFACE BOOLEAN bFoundOAD;
//INTERFACE BOOLEAN bNitFoundInvalidOAD;

INTERFACE U32 u32ScartSwitchDuration;


#if EAR_PHONE_POLLING
INTERFACE BOOLEAN PreEarphoneState;
#endif

#define ZUI_ALIGNED_VALUE(value, align)  ( (value) & ~((align)-1) )

//INTERFACE BOOLEAN g_bIsImageFrozen;


typedef enum
{
    CC_FONT_UNLOAD,
    CC_FONT_UNLOAD_SPEEDUP,
    CC_FONT_LOAD
} EN_CC_FONT_STATUS;
INTERFACE EN_CC_FONT_STATUS enCCFontStatus;

// Scan related
INTERFACE U8        u8ScanAtvChNum;                 // add for Auto Tune menu
INTERFACE U16        u16ScanDtvChNum;                 // add for Auto Tune menu
INTERFACE U16        u16ScanRadioChNum;               // add for Auto Tune menu


INTERFACE BOOLEAN   fEnableMvdTimingMonitor;        //<---should be moved to other place

#if ENABLE_ISDBT
INTERFACE U8        u8ScanCATVChNum;                 // add for Auto Tune menu
INTERFACE U8        u8ScanAirTVChNum;                 // add for Auto Tune menu
#endif

#if NORDIG_FUNC //for Nordig Spec v2.0
INTERFACE U16        u16ScanDataChNum;                 // add for Auto Tune menu
#endif
INTERFACE U8        u8ScanPercentageNum;            // add for Auto Tune menu

//#if (ENABLE_PIP)
//PIP sub window
INTERFACE MS_WINDOW_TYPE stSubWindowPosition;
//#endif

INTERFACE U32       gCurValidSubtitleIndex;
INTERFACE U8        gu8TTXSubtitleServiceNum;


//INTERFACE BOOLEAN _bOCPFromMem;  //20091124EL
#if ENABLE_SHOW_PHASE_FACTORY
INTERFACE U16 g_u16Miu0_Dqs0;
INTERFACE U16 g_u16Miu0_Dqs1;
 #if 1// (ENABLE_MIU_1)
INTERFACE U16 g_u16Miu1_Dqs0;
INTERFACE U16 g_u16Miu1_Dqs1;
 #endif
#endif


#if ENABLE_DVBC     //for test without UI
INTERFACE U8 DVBCSymbolRateScanType;      //1:auto mode; 0:manual mode
INTERFACE U8 DVBCFreqScanType;                //1:auto mode; 0:manual mode
INTERFACE U8 DVBCNetworkIdScanType;       //1:auto mode; 0:manual mode
INTERFACE U8 DVBCModulationScanType;      //1:auto mode; 0:manual mode
#endif

#if ENABLE_OAD
INTERFACE BOOLEAN bShowOadScanPage;
INTERFACE BOOLEAN bNITSignalSSU;
INTERFACE U8 u8OADpercentage;
#endif
#if ENABLE_S2
INTERFACE BOOLEAN Test_Dvbs2;
#endif
#if ENABLE_CI_PLUS
INTERFACE BOOLEAN bPowerOnEnterOPMode;
#if ( ENABLE_CI_PLUS_V1_4 )
INTERFACE BOOLEAN g_bPowerDownCheckCICAM;
INTERFACE BOOLEAN g_bCallbackOKFromCICAM;
#endif  //ENABLE_CI_PLUS_V1_4

#endif
#if ENABLE_S2
INTERFACE BOOLEAN Dvbs2_Default_Scan;
INTERFACE MS_U8 _lnb_satelliteID[MAX_NUM_OF_SAT];

#if(ENABLE_S2_CH_CHANGE_TO_SEARCHPOSITION)
INTERFACE U16 g_u16SearchPosition;
#endif

//===========================================================================

INTERFACE MS_U16 _u16MultiTPNum;//for add tp
INTERFACE MS_U8  _u8MultiSatNum;//for add sat
INTERFACE MS_U16 u32TPSCount;
INTERFACE MS_U32 _u32Frequency;
INTERFACE MS_U8  _u16RFCh;
INTERFACE MS_U32 _u32NumOfChanScan;
INTERFACE MS_U16 _u16GetTPSNum;
INTERFACE MS_U8 _u8SATTotalNum;
INTERFACE MS_U8 _u8CurScanSATPos;
INTERFACE MS_U16 _u16AddTPSNum;
INTERFACE MS_U8 _u8TPBlindScanProgress;
INTERFACE MS_U8 _u8MotorPosition;
INTERFACE EN_FE_TUNE_MODE eAutoTune;
INTERFACE MS_U16 _maxDtvProgramNum;


#endif



#if ENABLE_FAVORITE_NETWORK
INTERFACE BOOLEAN g_bSetFavoriteNetwork;
INTERFACE U8      g_u8NetworkIndex;
INTERFACE U8      g_u8NetworkTotal;
#endif
INTERFACE BOOLEAN g_bPvrChgSrcInitFs;

#if SCART_ALWAYS_OUTPUT_ATV
INTERFACE U8 g_u8switchsourceprocessing;
#endif

#if FIXED_SCART_OUT_GARBAGE_SWITCH_AR
INTERFACE U8 g_u8switchAspectFlag;
#endif
#if HDMI_DVI_AUDIO_MODE_CONFIG
INTERFACE BOOLEAN g_HdmiAudioModeChanged;
#endif

#if FIXED_3D_SWITCH_PIC_MODE_GARBAGE
INTERFACE U8 g_u8switchPicModeFlag;
#endif

#if FIXED_SI2158_FINE_TUNE_GARBAGE
INTERFACE int g_u16Si2158FineTuneCenterFreq;
#endif

#if ENABLE_DTV_CHCEK_USB_DELAY_2S
INTERFACE U8 g_u8DTVCheckUSBFlag;
#define DTV_CHECK_USB_MONITOR_START_BIT	BIT0
#define DTV_CHECK_USB_WAIT_BIT	BIT1
#define DTV_CHECK_USB_ENABLE	0
#endif

#if ENABLE_TCON
INTERFACE BOOLEAN g_bTCONPowerOnFlag;
#endif

#if PVR_AND_TTX_DIFF_WITH_MHEG5
typedef enum
{
    TTX_ON,
    MHEG5_ON,
    TTX_MHEG5_NUM
} TTX_MHEG_ON_TYPE;

INTERFACE TTX_MHEG_ON_TYPE g_enTurnOnTTX;
#endif

INTERFACE U8 g_u8USBdetectflag;
INTERFACE U8 g_u8USBValidflag;




INTERFACE BOOLEANS  g_globalVal1;
#define g_bIsImageFrozen            g_globalVal1.bBOOL_0
#define bNitFoundInvalidOAD         g_globalVal1.bBOOL_1
#define bFoundOAD                   g_globalVal1.bBOOL_2
#define bIsInsideDTVManualScanMenu  g_globalVal1.bBOOL_3
#define g_bInputBlocked             g_globalVal1.bBOOL_4
#define g_bPCSignalMonitor          g_globalVal1.bBOOL_5
#define bIsBlocked                  g_globalVal1.bBOOL_6
#define _bOCPFromMem                g_globalVal1.bBOOL_7


#undef INTERFACE

#endif
