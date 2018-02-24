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

#ifndef MAPP_TV_H
#define MAPP_TV_H

#include "datatype.h"
#include "MApp_Exit.h"
#include "MApp_GlobalVar.h"

#ifdef MAPP_TV_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

// TV states
typedef enum
{
    STATE_TV_INIT,
    STATE_TV_WAIT,
    // STATE_TV_CHANNEL_LIST,
    // STATE_TV_NINE_LATTICE,
    STATE_TV_SOURCE,
    STATE_TV_CARDREADER,
} EN_TV_STATE;

#if (ENABLE_SBTVD_DTV_SYSTEM)
typedef enum
{
    MAJOR_CH_NUM,
    MINOR_CH_NUM
} EN_LCN_TYPE;
#endif

#if (ENABLE_ATSC)
typedef enum
{
    MAJOR_CH_NUM,
    MINOR_CH_NUM
} EN_VIRTUAL_CHANNEL_TYPE;

INTERFACE MS_VIRTUAL_CHANNEL_NUM stVirtualChNum;
INTERFACE EN_VIRTUAL_CHANNEL_TYPE enVirChType2bVerified;
INTERFACE U8 u8MajorNumDigitCount;
INTERFACE U8 u8ManualScanStatus;
#if ENABLE_ATSC_SCAN_NEW_MODE
INTERFACE U8 u8TenKeyManualScanStatus;
#endif
#endif


#ifdef ENABLE_SELECT_NONESEARCH_CH
  #define IVALID_TV_RETURN_NUM    0xFFFF
  INTERFACE U16 u16ChannelReturn_Num1;
  INTERFACE U16 u16ChannelReturn_Num2;
#endif

INTERFACE EN_TV_STATE MApp_TV_GetState(void);

INTERFACE EN_RET MApp_TV(void);
INTERFACE void MApp_TV_NumWinProcDigitKey(U8 bKeyValue);
INTERFACE void MApp_TV_Force2MonitorIdleModeWindows(void);
INTERFACE void MApp_TV_Initial_IdleCount(void);
INTERFACE BOOLEAN MApp_TV_MHEG_Loading_Monitor(void);
INTERFACE void MApp_TV_DSMCC_Trigger_Monitor(void);
INTERFACE void MApp_TV_ExitAndGotoMenuState(void);
INTERFACE void MApp_TV_ClearCIFlag(void);
INTERFACE U16 MApp_TV_NumWinVerifyInputValue(U16 u16Value);
INTERFACE BOOLEAN MApp_TV_SelectSubtileLang(void);
INTERFACE BOOLEAN MApp_TV_Menu_SelectSubtileLang(void);
INTERFACE void MApp_TV_ProcessUserInput(void);     //xzm @20171228 add
#if ENABLE_COUNTRY_SINGAPORE
INTERFACE EN_LANGUAGE MApp_TV_GetMinPidSubtitleLang(void);
#endif

INTERFACE U16 u16IdleInputValue;
#if ENABLE_SBTVD_DTV_SYSTEM
INTERFACE U8 u8IdleMajorValue;
INTERFACE U8 u8IdleMinorValue;
INTERFACE EN_LCN_TYPE enLCNTypeVerified;
#endif
INTERFACE U8 u8IdleDigitCount;
INTERFACE U8 u8MaxDigiKeyNum;
INTERFACE U32 u32NumChannChangeTimer;

INTERFACE void MApp_TV_ProcessInstallWizard(void);
#if (ENABLE_EASMONITOR)
INTERFACE void MAPP_TV_ProcessEAS(void);
#endif
//////////////////////////////////////////////////////////
//ZUI: idle mode key process functions
INTERFACE BOOLEAN MApp_TV_ProcessAudioVolumeKey(U8 key);
INTERFACE BOOLEAN MApp_TV_ProcessKeystoneAngleKey(U8 key);   //xzm @20171228 add
INTERFACE BOOLEAN MApp_TV_ProcessChannelInfoKey(U8 key);
INTERFACE BOOLEAN MApp_TV_ProcessMessageBoxKey(U8 key);
INTERFACE BOOLEAN MApp_TV_ProcessHotkeyOptionKey(U8 key);
INTERFACE void MApp_Set_IdleDigitCount(U8 u8NewCount);
INTERFACE void MApp_Set_IdleInputValue(U16 u16NewInputVal);
INTERFACE U8 MApp_Get_IdleDigitCount(void);
INTERFACE U16 MApp_Get_IdleInputValue(void);
//////////////////////////////////////////////////////////
//ZUI: moved from MApp_UiMenu2.c
INTERFACE BOOLEAN MApp_TV_ScreenSaverClear(SCALER_WIN eWindow);
#if(ENABLE_DVB)
INTERFACE BOOLEAN MApp_TV_IsInvalidService(void);
#endif
INTERFACE BOOLEAN MApp_TV_IsProgramRunning(void);
#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
INTERFACE void MApp_TV_SetCheckAlternativeFlag(BOOLEAN bFlag);
INTERFACE BOOLEAN MApp_TV_GetCheckAlternativeFlag(void);
INTERFACE BOOLEAN MApp_TV_CheckLossSignal30Days(void);
#endif
INTERFACE BOOLEAN MApp_Get_CheckParentalPWStatus(void);
INTERFACE void MApp_Set_CheckParentalPWStatus(BOOLEAN bStatus);
#if ENABLE_EPGTIMER_RECORDER_TURNOFFPANEL
INTERFACE void MApp_SetActiveStandbyMode(BOOL bActive);
INTERFACE BOOLEAN MApp_GetActiveStandbyMode(void);
#endif
#if ENABLE_OAD
INTERFACE void MApp_OAD_PanelPowerOn(void);
INTERFACE void MApp_OAD_PanelPowerOff(void);
#endif
#if ENABLE_ATSC_INSTALLGUIDE
INTERFACE void MApp_TV_ResetTvState( void );
#endif

#if (ENABLE_CI_PLUS_V1_4)
INTERFACE BOOL MApp_TV_TuneCILCNProgram(U16 u16LCN, BOOLEAN bShowInfo);

#endif

#undef INTERFACE

#endif
