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

#ifndef MAPP_INPUTSOURCE_H
#define MAPP_INPUTSOURCE_H

#include "MsCommon.h"
#include "MApp_Exit.h"
#include "MApp_GlobalSettingSt.h"


#ifdef MAPP_INPUTSOURCE_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

typedef enum
{
    /// SPDIF Channel Status CategoryCode
    SPDIF_CS_CategoryCode_                  = 0x0,
    /// SPDIF Channel Status CopyRight
    SPDIF_CS_CopyRight_                     = 0x1,
    /// SPDIF Channel Status Source Number
    SPDIF_CS_SourceNumber_                  = 0x2,
    /// SPDIF Channel Status Channel Number
    SPDIF_CS_ChannelNumber_                 = 0x3,
    /// SPDIF Channel Status Sampling Frequency
    SPDIF_CS_SmpFreq_                       = 0x4,
    /// SPDIF Channel Status Channel Clock Acc
    SPDIF_CS_ClockAcc_                      = 0x5,
    /// SPDIF Channel Status Channel_A & Channel_B
    SPDIF_ChannelAB_                        = 0x6,
} AUDIO_SPDIF_CS_TYPE_;

typedef enum
{
    /// SPDIF Channel Status CategoryCode is BroadCast mode
    SPDIF_CS_Category_BroadCast_            = 0x00,
    /// SPDIF Channel Status CategoryCode is General mode
    SPDIF_CS_Category_General_              = 0x01,
    /// SPDIF Channel Status CategoryCode is BroadCast Japan mode
    SPDIF_CS_Category_BroadCast_JP_         = 0x02,
    /// SPDIF Channel Status CategoryCode is BroadCast Europe mode
    SPDIF_CS_Category_BroadCast_EU_         = 0x03,
    /// SPDIF Channel Status CategoryCode is BroadCast USA mode
    SPDIF_CS_Category_BroadCast_USA_        = 0x04,
    /// SPDIF Channel Status CategoryCode is Reserve
    SPDIF_CS_Category_Rev4_                 = 0x05,
    /// SPDIF Channel Status CategoryCode is Reserve
    SPDIF_CS_Category_Rev5_                 = 0x06,
    /// SPDIF Channel Status CategoryCode is Reserve
    SPDIF_CS_Category_Rev6_                 = 0x07,
    /// SPDIF Channel Status CopyRight is ON
    SPDIF_CS_CopyRight_CP_                  = 0x08,
    /// SPDIF Channel Status CopyRight is OFF
    SPDIF_CS_CopyRight_NonCP_               = 0x09,
    /// SPDIF Channel Status Source Number is 2 Channel
    SPDIF_CS_SourceNumber_2_                = 0x0A,
    /// SPDIF Channel Status Source Number is 5 Channel
    SPDIF_CS_SourceNumber_5_                = 0x0B,
    /// SPDIF Channel Status Source Number is 6 Channel
    SPDIF_CS_SourceNumber_6_                = 0x0C,
    /// SPDIF Channel Status Source Number is Reserve
    SPDIF_CS_SourceNumber_Rev1_             = 0x0D,
    /// SPDIF Channel Status Source Number is Reserve
    SPDIF_CS_SourceNumber_Rev2_             = 0x0E,
    /// SPDIF Channel Status Source Number is Reserve
    SPDIF_CS_SourceNumber_Rev3_             = 0x0F,
    /// SPDIF Channel Status Channel Number is Stereo Left Channel
    SPDIF_CS_ChannelNumber_A_Left_          = 0x10,
    /// SPDIF Channel Status Channel Number is Stereo Right Channel
    SPDIF_CS_ChannelNumber_B_Right_         = 0x11,
    /// SPDIF Channel Status Channel Number
    SPDIF_CS_ChannelNumber_C_               = 0x12,
    /// SPDIF Channel Status Channel Number
    SPDIF_CS_ChannelNumber_D_               = 0x13,
    /// SPDIF Channel Status Channel Number
    SPDIF_CS_ChannelNumber_E_               = 0x14,
    /// SPDIF Channel Status Channel Number
    SPDIF_CS_ChannelNumber_F_               = 0x15,
    /// SPDIF Channel Status Channel Number
    SPDIF_CS_ChannelNumber_G_               = 0x16,
    /// SPDIF Channel Status Channel Number
    SPDIF_CS_ChannelNumber_H_               = 0x17,
    /// SPDIF Channel Status Channel Number
    SPDIF_CS_ChannelNumber_I_               = 0x18,
    /// SPDIF Channel Status Channel Number
    SPDIF_CS_ChannelNumber_J_               = 0x19,
    /// SPDIF Channel Status Channel Number
    SPDIF_CS_ChannelNumber_K_               = 0x1A,
    /// SPDIF Channel Status Sampling Frequency is 192K
    SPDIF_CS_SmpFreq_192_                   = 0x1B,
    /// SPDIF Channel Status Sampling Frequency is 176.4K
    SPDIF_CS_SmpFreq_176_                   = 0x1C,
    /// SPDIF Channel Status Sampling Frequency is 128K
    SPDIF_CS_SmpFreq_128_                   = 0x1D,
    /// SPDIF Channel Status Sampling Frequency is 96K
    SPDIF_CS_SmpFreq_96_                    = 0x1E,
    /// SPDIF Channel Status Sampling Frequency is 88.2K
    SPDIF_CS_SmpFreq_88_                    = 0x1F,
    /// SPDIF Channel Status Sampling Frequency is 64K
    SPDIF_CS_SmpFreq_64_                    = 0x20,
    /// SPDIF Channel Status Sampling Frequency is 48K
    SPDIF_CS_SmpFreq_48_                    = 0x21,
    /// SPDIF Channel Status Sampling Frequency is 44.1K
    SPDIF_CS_SmpFreq_44_                    = 0x22,
    /// SPDIF Channel Status Sampling Frequency is 32K
    SPDIF_CS_SmpFreq_32_                    = 0x23,
    /// SPDIF Channel Status Sampling Frequency is 24K
    SPDIF_CS_SmpFreq_24_                    = 0x24,
    /// SPDIF Channel Status Sampling Frequency is 22.05K
    SPDIF_CS_SmpFreq_22_                    = 0x25,
    /// SPDIF Channel Status Sampling Frequency is 16K
    SPDIF_CS_SmpFreq_16_                    = 0x26,
    /// SPDIF Channel Status Sampling Frequency is Reserve
    SPDIF_CS_SmpFreq_Rev1_                  = 0x27,
    /// SPDIF Channel Status Sampling Frequency is Reserve
    SPDIF_CS_SmpFreq_Rev2_                  = 0x28,
    /// SPDIF Channel Status Sampling Frequency is Reserve
    SPDIF_CS_SmpFreq_Rev3_                  = 0x29,
    /// SPDIF Channel Status Sampling Frequency is Reserve
    SPDIF_CS_SmpFreq_Rev4_                  = 0x2A,
    /// SPDIF Channel Status Sampling Frequency is Reserve
    SPDIF_CS_SmpFreq_Rev5_                  = 0x2B,
    /// SPDIF Channel Status Clock Accuracy is Level-1
    SPDIF_CS_ClockAcc_Lev1_                 = 0x2C,
    /// SPDIF Channel Status Clock Accuracy is Level-2
    SPDIF_CS_ClockAcc_Lev2_                 = 0x2D,
    /// SPDIF Channel Status Clock Accuracy is Level-3
    SPDIF_CS_ClockAcc_Lev3_                 = 0x2E,
    /// SPDIF Channel Status Clock Accuracy is not match
    SPDIF_CS_ClockAcc_NotMatch_             = 0x2F,
    /// SPDIF Channel Status ChannelAB is ON
    SPDIF_ChannelAB_Invalid_ON_             = 0x30,
    /// SPDIF Channel Status ChannelAB is OFF
    SPDIF_ChannelAB_Invalid_OFF_            = 0x31,
} AUDIO_SPDIF_CS_TYPE_STATUS_;

typedef enum
{
    E_VIF_NOT_NECESSARY,
    E_VIF_ON_ATV_DISPLAY,
    E_VIF_ON_ATV_CVBSOUT,
} EN_VIF_WORKING_STATUS;

//*************************************************************************
//              Function prototypes
//*************************************************************************

INTERFACE void MApp_InputSource_ChangeAudioSource( INPUT_SOURCE_TYPE_t enInputSourceType, E_UI_INPUT_SOURCE enUiInputSourceType);

#if 0
#define MApp_InputSource_SwitchSource( enUiInputSourceType,eWindow )    do{ \
    PRINT_CURRENT_LINE(); \
    printf(" call switch source\n");    \
    MApp_InputSource_SwitchSource_2(enUiInputSourceType,eWindow); \
} while(0)
INTERFACE void MApp_InputSource_SwitchSource_2 ( E_UI_INPUT_SOURCE enUiInputSourceType,SCALER_WIN eWindow );
#else
INTERFACE void MApp_InputSource_SwitchSource( E_UI_INPUT_SOURCE enUiInputSourceType,SCALER_WIN eWindow );
#endif

INTERFACE void MAPP_InputSource_SwitchHDMI_DVI( U8 Source_Type);

INTERFACE void MApp_InputSource_RecordSource( E_UI_INPUT_SOURCE enUiInputSourceType);
INTERFACE E_UI_INPUT_SOURCE MApp_InputSource_GetRecordSource(void);
INTERFACE void MApp_InputSource_RestoreSource(void);

//ZUI:
#if 1
#define MApp_InputSource_ChangeInputSource(eWindow) do {                                    \
    MApp_InputSource_ChangeInputSource_2(eWindow);                                          \
} while(0)
#else
#define MApp_InputSource_ChangeInputSource(eWindow) do {                                    \
    PRINT_CURRENT_LINE(); printf(" Call MApp_InputSource_ChangeInputSource()\n");           \
    MApp_InputSource_ChangeInputSource_2(eWindow);                                          \
} while(0)
#endif
INTERFACE void MApp_InputSource_ChangeInputSource_2(SCALER_WIN eWindow);

#if (INPUT_SCART_VIDEO_COUNT > 0)
INTERFACE void MApp_InputSource_ScartIOMonitor(void);
#endif

INTERFACE void MApp_InputSource_SetSystemmInfo( E_UI_INPUT_SOURCE enUiInputSourceType, MS_SYS_INFO *penMsSysInfo , E_DATA_INPUT_SOURCE *penDataInpSrcType);

/********************************************************************************/
/*                               Macro                                          */
/********************************************************************************/
#if ENABLE_OFFLINE_SIGNAL_DETECTION
#define AIS_DOS_TIMES   6//10
#define TIMER_STOP      0
#define TIMER_GO        1
#define DETECT_SOURCE_NUM   4

typedef struct
{
    U8 bUISourceID;
    U8 bLevel;
    U8 bChangeFlag:1;
    U8 bHaveSignal:1;
}_stAISSrcList;

typedef struct
{
    E_UI_INPUT_SOURCE bSrcCnt;
    U8 bUICHSourceFlag;
    U8 bAISSrcPush;
    U32 bSysTimeDuty;
    //BOOLEAN bAISLock;    // 1:lock polling;0:Detect; When Switch Source ,Lock AIS Polling;
    U16 dLockCnt;
    U8 bDotimes;
    U8 strResult[AIS_DOS_TIMES];
    U8 bNoSignal;           //1:NoSignal, 0:Signal in
    U8 bDetectCnt;          //
    U8 bDetectStart;        //
}_stAISCtrl;

INTERFACE _stAISCtrl    stAISCtrl;
INTERFACE _stAISSrcList stAISSrcList[UI_INPUT_SOURCE_NUM];
INTERFACE void MApp_OffLineInit(void);
INTERFACE void MApp_AISMonitor(void);
INTERFACE U8 MApp_MapUIInputTypeToCheckSrc(U8 bUIInput);
#endif

//-----------------------------
// PIP Function
//-----------------------------
INTERFACE E_UI_INPUT_SOURCE MApp_InputSource_GetUIInputSourceType(INPUT_SOURCE_TYPE_t stInputSrc);

INTERFACE INPUT_SOURCE_TYPE_t MApp_InputSource_GetInputSourceType(E_UI_INPUT_SOURCE stInputSrc);

INTERFACE void MApp_InputSource_EnableReloadDemod(BOOLEAN bRelaod);

#if ENABLE_DTV_CHCEK_USB_DELAY_2S
INTERFACE void MApp_DTV_USB_CheckMonitor(void);
#endif
INTERFACE EN_VIF_WORKING_STATUS MApp_InputSource_GetVifWorkingStatus(void);

INTERFACE INPUT_SOURCE_TYPE_t MApp_InputSource_Get_CVBSOut_Src(U8 u8CvbsOutIdx, INPUT_SOURCE_TYPE_t eInputSource);

//INTERFACE BOOLEAN MApp_Is_UI_INPUT_SOURCE_DTV(E_UI_INPUT_SOURCE eUiInputSourceType);


//-----------------------------------------------------------------------------------
// UI Inputsource control
void MApp_InputSrc_Set_UiInputSrcType(E_UI_INPUT_SOURCE enUiInputSourceType);
E_UI_INPUT_SOURCE MApp_InputSrc_Get_UiInputSrcType(void);
E_UI_INPUT_SOURCE MApp_InputSrc_Get_LastDtvUiSrcType(void);
void MApp_InputSrc_Set_PrevUiInputSrcType(E_UI_INPUT_SOURCE enUiInputSourceType);
E_UI_INPUT_SOURCE MApp_InputSrc_Get_PrevUiInputSrcType(void);
BOOL MApp_InputSrc_Is_UiInputSrcTypeDtv(E_UI_INPUT_SOURCE enUiInputSourceType);
BOOL MApp_InputSrc_Is_CurUiInputSrcTypeDtv(void);
BOOL MApp_InputSrc_Is_PrevUiInputSrcTypeDtv(void);

BOOL MApp_InputSrc_Is_UiInputSrcTypeHDMI(E_UI_INPUT_SOURCE enUiInputSourceType);

char* MApp_InputSrc_Get_UiInputSrcName(E_UI_INPUT_SOURCE enUiInputSourceType);
//-----------------------------------------------------------------------------------

void MApp_InputSrc_ChangeToLastUiDtvSrc(void);



/***************************************************************************************/
#undef INTERFACE

/***************************************************************************************/
#endif  /*MAPP_INPUTSOURCE_H*/

