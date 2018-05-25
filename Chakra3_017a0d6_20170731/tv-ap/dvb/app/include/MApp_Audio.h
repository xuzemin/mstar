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

#ifndef _MAPP_AUDIO_H
#define _MAPP_AUDIO_H

#include "datatype.h"
#include "drvXC_HDMI_if.h"
#include "MApp_GlobalSettingSt.h"
#if ENABLE_EWS
#include "mapp_si.h"
#endif

#ifdef _MAPP_AUDIO_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

///////////////////////////////////////////////////////////////////////////////

#define MAX_NUM_OF_VOL_LEVEL       100

// equalizer
#define SOUND_MODE_STANDARD_BAND1   50
#define SOUND_MODE_STANDARD_BAND2   50
#define SOUND_MODE_STANDARD_BAND3   50
#define SOUND_MODE_STANDARD_BAND4   50
#define SOUND_MODE_STANDARD_BAND5   50
#define SOUND_MODE_STANDARD_BAND6   50
#define SOUND_MODE_STANDARD_BAND7   50

#define SOUND_MODE_MUSIC_BAND1      73
#define SOUND_MODE_MUSIC_BAND2      70
#define SOUND_MODE_MUSIC_BAND3      48
#define SOUND_MODE_MUSIC_BAND4      70
#define SOUND_MODE_MUSIC_BAND5      73
#define SOUND_MODE_MUSIC_BAND6      70
#define SOUND_MODE_MUSIC_BAND7      73

#define SOUND_MODE_MOVIE_BAND1      45
#define SOUND_MODE_MOVIE_BAND2      50
#define SOUND_MODE_MOVIE_BAND3      48
#define SOUND_MODE_MOVIE_BAND4      50
#define SOUND_MODE_MOVIE_BAND5      45
#define SOUND_MODE_MOVIE_BAND6      50
#define SOUND_MODE_MOVIE_BAND7      45

#define SOUND_MODE_SPORTS_BAND1     35
#define SOUND_MODE_SPORTS_BAND2     38
#define SOUND_MODE_SPORTS_BAND3     50
#define SOUND_MODE_SPORTS_BAND4     50
#define SOUND_MODE_SPORTS_BAND5     45
#define SOUND_MODE_SPORTS_BAND6     50
#define SOUND_MODE_SPORTS_BAND7     45

INTERFACE BOOLEAN bEnableAC3Check;
INTERFACE U32 u32AC3CheckTimer;
INTERFACE U8  u8AC3CheckTimes;
INTERFACE U8 u8PollingStereo;
//INTERFACE U8  u8HDMIchkflag;

#if ENABLE_DTV
#if ENABLE_EWS
BOOLEAN MApp_Audio_SetEWSAudio(MS_EWSAUDIOINFO mEwsAudioinfo);
#endif

INTERFACE BOOLEAN MApp_Audio_SetAudioLanguage(U8 u8AudSelectedIndex);
INTERFACE void MApp_Audio_SetAdAudio(U8 u8AudSelectedIndex);
INTERFACE void MApp_Audio_SearchAdAudio(void);

#if ENABLE_CI_PLUS
INTERFACE void MApp_Audio_OpSearchAdAudio(void);
#endif
#endif

INTERFACE BOOLEAN MApp_Audio_IsAC3AudioExist(void);        // to show "DOLBY DIGITAL" icon in channel info OSD
INTERFACE void MApp_Audio_AdjustSoundMode(void);            // surround mode
INTERFACE void  MApp_Aud_Banlace_Init(void);
INTERFACE void MApp_Aud_AutoVolume_Init(void);
#if 0//(CHIP_FAMILY_TYPE == CHIP_FAMILY_A7)
INTERFACE void MApp_Aud_AudioDelay_Init(void);
#endif
INTERFACE void MApp_Aud_PEQ_Init(void);
INTERFACE void MApp_Aud_EQ_Init(void); // MP333
/*
     MApp_Aud_SetSurroundMode is used to set a specific surround mode.

*/
INTERFACE void MApp_Aud_SetSurroundMode(U8 u8SurroundMode);

INTERFACE void MApp_Audio_HDMI_MODE_CONFIG(HDMI_POLLING_STATUS_t enHDMIPollingStatus, HDMI_PACKET_INFO_t *enHDMIPackInfo);
INTERFACE void MApp_Aud_SetTVSpeaker(void);

//INTERFACE void MApp_Aud_EnableMute(BOOLEAN bEnableMute);

#if(ENABLE_ATSC)
#define AUD_APP_VOLUME_UNMUTE   0
#define PreferSoundTrack_Number     1
INTERFACE void MApp_AudioStreamMonitor(void);
INTERFACE BOOLEAN MApp_Aud_SetMtsMode(void);
INTERFACE void MApp_AUD_PreferSoundTrack_Checker(void);
INTERFACE MS_U8 MApp_SoundMtsSifSoundModeTrans(MS_U8 App_MTS);
INTERFACE MS_BOOL MApp_AUDIO_IsSifSoundModeExist(EN_SOUND_MTS_TYPE enSifSoundMode);
INTERFACE void MApp_Aud_SetPathUnMute(void);
INTERFACE BOOLEAN MApp_Aud_GetMuteStatus(void);
INTERFACE void MApp_Aud_GetNextAvailableMtsMode ( BOOLEAN bForce );
INTERFACE void MApp_Aud_SetBass ( U8 u8Bass );
INTERFACE void MApp_Aud_SetTreble ( U8 u8Treble );
INTERFACE void MApp_Aud_SetEqValue(void);
#if (ENABLE_ATSC_AD_FUNC)
INTERFACE void MApp_Audio_SearchAdAudio_ATSC(void);
INTERFACE void MApp_Audio_SetAdAudio_ATSC(U8 u8AudSelectedIndex);
#endif
#endif

//================================================================
// Add audio APP functions here
//================================================================

void MApp_Audio_AdjustPreScale(U8 InputSource);
void MApp_Audio_AdjustAVCThreshold(U8 InputSource);
void MApp_Audio_AdjustMainVolume(U8 VolumePercent);
void MApp_Audio_AdjustADVolume(U8 VolumePercent);

void MApp_Audio_Task(BOOL bRealTimeOnly);

#define AUDIO_AMP_OFF   0
#define AUDIO_AMP_ON    1
void MApp_Audio_Set_AmpOnOff(BOOL bAmpOn);

#define AUDIO_AMP_MUTE_OFF  0
#define AUDIO_AMP_MUTE_ON   1
void MApp_Audio_Set_AmpMute(BOOL bAmpMute);


//******************************************************************************

#undef INTERFACE

//******************************************************************************

#endif // #ifndef _MAPP_AUDIO_H

