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
///////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _MAPP_CHANNEL_CHANGE_H
#define _MAPP_CHANNEL_CHANGE_H

#include "apiVDEC.h"
#include "MApp_Exit.h"
#include "msAPI_Global.h"
#include "msAPI_MW_GlobalSt.h"
#include "MApp_GlobalSettingSt.h"
#include "apiAUDIO.h"

#if MHEG5_ENABLE
#include "msAPI_MHEG5.h"
#endif
#if (ENABLE_DTV_EPG)
#include "mapp_eit.h"
#endif
typedef enum
{
    STATE_CHANNELCHANGE_INIT,
    STATE_CHANNELCHANGE_SHOWINFO,
    STATE_CHANNELCHANGE_WAITKEY,
    STATE_CHANNELCHANGE_DISPLAY,
    STATE_CHANNELCHANGE_MSGBOX_FADING,
    STATE_CHANNELCHANGE_EXIT,
} EN_CHANNELCHANGE_STATE;

/*
typedef enum
{
    TYPE_TV,
    TYPE_ATV,
    TYPE_DTV,
    TYPE_ANALOG,
    TYPE_PC,
    TYPE_YPBPR,
    TYPE_AV,
} EN_INPUT_TYPE;
*/

typedef enum
{
    STATE_DETECT_SIGNAL_INPROGRESS_NOSIGNAL,
    STATE_DETECT_SIGNAL_INPROGRESS_UNSUPPORT_MODE,
    STATE_DETECT_SIGNAL_NOSIGNAL,
    STATE_DETECT_SIGNAL_OK,
    STATE_DETECT_SIGNAL_PC_UNSUPPORT_MODE,
    STATE_DETECT_SIGNAL_ERROR,
} EN_DETECT_SIGNAL_STATE;

typedef enum
{
    TYPE_CHANNEL_CHANGE_SER_ID,
    TYPE_TUNE_STREAM_SER_ID,
    TYPE_CHANNEL_CHANGE_SER_ID_QUIETLY,
    TYPE_CHANNEL_CHANGE_LCN,
    TYPE_TUNE_STREAM_LCN,
    TYPE_CHANNEL_CHANGE_LCN_QUIETLY,
    TYPE_CHANNEL_CHANGE_SER_ID_NDT,             // ndt
    TYPE_CHANNEL_CHANGE_SER_ID_QUIETLY_NDT,     // ndt
    TYPE_CHANNEL_CHANGE_LCN_NDT,                // ndt
    TYPE_CHANNEL_CHANGE_LCN_QUIETLY_NDT,        // ndt
} EN_MHEG_5_TUNE_TYPE;

typedef enum
{
    PVR_DEMUX_CHANGE_INPUTSOURCE,
    PVR_DEMUX_CHANGE_CH_PLUS, //change RF by KEY_CH_PLUS
    PVR_DEMUX_CHANGE_CH_MINUS,
    PVR_DEMUX_CHANGE_CH_CHANGE, //change RF by channel list

}EN_PVR_DEMUX_CHANGE_TYPE;

#ifdef MAPP_CHANNEL_CHANGE_C
#define INTERFACE
#else
#define INTERFACE extern
#endif


#define CHANNEL_CHANGE_KEY_REPEAT_DELAY 300 //ms
INTERFACE void MApp_ChannelChange_VariableInit( void );
//INTERFACE EN_DETECT_SIGNAL_STATE MApp_ChannelChange_DetectSignalStatus(E_UI_INPUT_SOURCE input_type);
INTERFACE void MApp_ChannelChange_DisableAV(SCALER_WIN eWindow);
INTERFACE void MApp_ChannelChange_EnableAV(void);

INTERFACE void MApp_ChannelChange_DisableChannel(BOOLEAN u8IfStopDsmcc, SCALER_WIN eWindow/*U8 u8ChanBufIdx*/);

#if 0
#define MApp_ChannelChange_EnableChannel(win)   do { \
    printf("%u: %s call EnableChannel()\n", __LINE__, __FILE__);\
    MApp_ChannelChange_EnableChannel_2(win);    \
} while(0)
#else
#define MApp_ChannelChange_EnableChannel(win)   do { \
    MApp_ChannelChange_EnableChannel_2(win);    \
} while(0)
#endif
INTERFACE void MApp_ChannelChange_EnableChannel_2(SCALER_WIN eWindow);

INTERFACE void MApp_ChannelChange_PIP_ChangeAudioSource2TV(SCALER_WIN eWindow);
INTERFACE void MApp_ChannelChange_CheckBlockChannelPW(void);
INTERFACE EN_RET MApp_ChannelChange(void);
INTERFACE EN_RET MApp_ChannelChange_ShowAnalogBanner ( void );
#if ENABLE_DVB
INTERFACE BOOLEAN MApp_ChannelChange_ChangeSpeciChannel( U16 u16InputValue, U16 wOriginalNetwork_ID, U16 wTransportStream_ID, EN_MHEG_5_TUNE_TYPE bType, BOOLEAN bCheckTsID, BOOLEAN bShowDisplayInfo );
#endif
INTERFACE void MApp_ChannelPosition_Restore(void);
#if MHEG5_ENABLE
INTERFACE EN_RET MApp_ChannelChange_GoBackDataMode(void);
#endif
INTERFACE void MApp_ChannelChange_SearchDefaultAudioLang(void);
#if (ENABLE_CI_PLUS)
INTERFACE void MApp_ChannelChange_SearchDefaultOPAudioLang(void);
#endif
#if(ENABLE_DVB_AUDIO_DESC)
INTERFACE void MApp_ChannelChange_SearchBroadcastMixAudio(void);
#endif
INTERFACE void MApp_ChannelChange_SetupVdForceMode(void);
#if ENABLE_AD_DISABLE_MAINAUDIO
INTERFACE void MApp_Audio_SwitchtoADAudio(BOOL ADEnable);
#endif

#if ENABLE_EWS
INTERFACE BOOL MApp_ChannelChange_SearchEwsAudioTrack(void);
#endif
INTERFACE MEMBER_SERVICETYPE g_eCurrentUserServiceType;

#if MHEG5_ENABLE
INTERFACE U16  g_u16Current_AudioPID;
INTERFACE U16  g_u16Current_VideoPID;
//INTERFACE U16  g_u16Current_AudioType;
INTERFACE AUDIOSTREAM_TYPE  g_u16Current_AudioType;

INTERFACE VDEC_CodecType g_eCurrent_VideoType;
INTERFACE U16 g_u16CurrentServiceID;
INTERFACE WORD g_wCurrentTS_ID,g_wCurrent_ONID;
INTERFACE WORD g_wCurrentTVUserServicePosition,g_wCurrentRadioUserServicePosition;
INTERFACE MEMBER_SERVICETYPE g_eCurrentRealServiceType;
INTERFACE WORD g_wCurrentTVRealServicePosition,g_wCurrentRadioRealServicePosition;
#if NORDIG_FUNC //for Nordig Spec v2.0
INTERFACE WORD g_wCurrentDataUserServicePosition,g_wCurrentDataRealServicePosition;
#endif
INTERFACE BOOLEAN g_bMHEG5Service;
#endif

#if ENABLE_PVR
INTERFACE U16  g_u16Current_PCRPID;
INTERFACE U16  g_u16Current_PVR_VideoPID;
INTERFACE U16  g_u16Current_PVR_AudioPID;
INTERFACE U16  g_u16Current_AudioDescriptorPID;
INTERFACE AUDIOSTREAM_TYPE  g_enCurrent_AudioDescriptorType;
//INTERFACE U16  g_wCurrent_AudioType;
INTERFACE AUDIOSTREAM_TYPE  g_wCurrent_AudioType;

INTERFACE VDEC_CodecType g_eCurrent_PVR_VideoType;
INTERFACE void MApp_ChannelChange_Set_Audio_Decoder_System(WORD wAudType);
#endif


BOOLEAN MApp_ChChg_IsInEnableChannel(void);


#if (ENABLE_ATSC)
#include "MApp_ChannelChange_ATSC.h"
#endif

#undef INTERFACE
#endif
