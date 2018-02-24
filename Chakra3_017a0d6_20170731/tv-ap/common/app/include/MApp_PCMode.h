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

#ifndef MAPP_PCMODE_H
#define MAPP_PCMODE_H

#include "Board.h"

#include "apiXC_Auto.h"

#include "MApp_GlobalSettingSt.h"           ///< for ADC setting structure


/********************************************************************************/
/*                               Macro                                          */
/********************************************************************************/

#ifdef MAPP_PCMODE_C
    #define INTERFACE
#else
    #define INTERFACE extern
#endif

typedef enum
{
    E_PCMODE_NOSYNC = 0,                ///< Input timing stable, no input sync detected
    E_PCMODE_STABLE_SUPPORT_MODE,       ///< Input timing stable, has stable input sync and support this timing
    E_PCMODE_STABLE_UN_SUPPORT_MODE,    ///< Input timing stable, has stable input sync but this timing is not supported
    E_PCMODE_UNSTABLE,                  ///< Timing change, has to wait InfoFrame if HDMI input
} PCMODE_SyncStatus;

#if ENABLE_3D_PROCESS
INTERFACE E_XC_3D_INPUT_MODE    g_HdmiInput3DFormat;
INTERFACE E_XC_3D_INPUT_MODE    g_HdmiInput3DFormatStatus;
#endif
#if (ENABLE_HDMI_4K_2K)
INTERFACE BOOLEAN    g_HdmiInput4Kx2KFormat;
#endif

//*************************************************************************
//              Function prototypes
//*************************************************************************
E_ADC_SET_INDEX MApp_PCMode_Get_AdcSetIdx(INPUT_SOURCE_TYPE_t enInputSourceType, SCALER_WIN eWindow );

typedef enum
{
    ADC_AUTO_CAL_FOR_INIT,
    ADC_AUTO_CAL_FOR_FAC_MENU,

}EnuAdcAutoCalUseCase;

INTERFACE BOOLEAN MApp_YPbPr_Setting_Auto(XC_Auto_CalibrationType type, SCALER_WIN eWindow, EnuAdcAutoCalUseCase eAdcAutoCalUseCase, BOOLEAN bSrcIsHD);
INTERFACE BOOLEAN MApp_RGB_Setting_Auto(XC_Auto_CalibrationType type, SCALER_WIN eWindow, EnuAdcAutoCalUseCase eAdcAutoCalUseCase);
INTERFACE BOOLEAN MApp_SCART_RGB_Setting_Auto(XC_Auto_CalibrationType type, SCALER_WIN eWindow, EnuAdcAutoCalUseCase eAdcAutoCalUseCase);


INTERFACE BOOLEAN MApp_PCMode_Enable_SelfAuto(BOOLEAN EnableAuto, SCALER_WIN eWindow);
INTERFACE void MApp_PCMode_RunSelfAuto(SCALER_WIN eWindow);

INTERFACE void MApp_PCMode_LoadModeData(SCALER_WIN eWindow, U8 u8ModeIndex, BOOLEAN bIsNewMode);
INTERFACE void MApp_PCMode_SaveModeRamSetting(SCALER_WIN eWindow);

INTERFACE void MApp_PC_MainWin_Handler(INPUT_SOURCE_TYPE_t src, BOOLEAN bRealTimeMonitorOnly);
#if (ENABLE_PIP)
INTERFACE void MApp_PC_SubWin_Handler(INPUT_SOURCE_TYPE_t src, BOOLEAN bRealTimeMonitorOnly);
#endif

INTERFACE PCMODE_SyncStatus MApp_PCMode_GetCurrentState(SCALER_WIN eWindow);
INTERFACE BOOLEAN MApp_PCMode_IsAspectRatioWide(INPUT_SOURCE_TYPE_t enInputSourceType);
MS_U8 MApp_PCMode_Get_Mode_Idx(SCALER_WIN eWindow);
MS_U16 MApp_PCMode_Get_HResolution(SCALER_WIN eWindow,MS_BOOL IsYpbprOrVga);
MS_U16 MApp_PCMode_Get_VResolution(SCALER_WIN eWindow,MS_BOOL IsYpbprOrVga);
void MApp_PCMode_Reset( SCALER_WIN eWindow);
INTERFACE void MAPP_PCMode_PIP_ChangeAudioSource2HDMI(SCALER_WIN eWindow);

//BOOLEAN MApp_ADC_HW_SaveGainOffset(void);
BOOLEAN MApp_ADC_Init(void);

BOOLEAN MApp_PCMode_GetCurrentHdmiAvgMode(void);

void MApp_PCMode_Reset_TimingMonitor(SCALER_WIN eWindow);

BOOLEAN MApp_PCMode_Get_CurModeInfo(SCALER_WIN eWindow, INPUT_SOURCE_TYPE_t enInputSourceType, MS_WINDOW_TYPE *pstDEWin);

//*************************************************************************
//              Global Variables
//*************************************************************************

#undef INTERFACE
#endif  /*MAPP_PCMODE_H*/
