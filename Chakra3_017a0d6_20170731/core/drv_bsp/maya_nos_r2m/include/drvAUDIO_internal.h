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
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
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
////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_AUDIO_INTERNAL_H_
#define _DRV_AUDIO_INTERNAL_H_

#include "MsTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define MAX_AUDIO_BASE_ADDRESS_NUM2              3

//=====================================================
typedef enum
{
    AUDIO_ETMODE_DTV,     // DTV Mode
    AUDIO_ETMODE_KTV,     // KTV Mode 1
    AUDIO_ETMODE_GAME,  // GAME Mode
    AUDIO_ETMODE_KTV2,   // KTV Mode 2
    AUDIO_ETMODE_VOIP_ON,
    AUDIO_ETMODE_VOIP_OFF,
    AUDIO_ETMODE_KTV_STB, // STB KTV Mode, forward mix ch.6 and ch.7
}AUDIO_ENTERTAINMENT_MODE;

typedef struct
{
    MS_BOOL          bDecInUsed;
    AUDIO_USAGE_TYPE eUsageType;
    MMA_AudioType    eAudioType;
} AUDIO_DSP_USAGE;

typedef struct
{
    MS_U32  g_ShmID;

    MS_BOOL g_bDecPlayFileFlag;   // DEC MM interrupt flag
    MS_BOOL g_bSePlayFileFlag;    // SE  MM interrupt flag
    MS_BOOL g_bMMPlayFlag;        // MM  play flag
    MS_BOOL g_Audio_PreInitFlag;
    MS_BOOL g_Audio_InitFlag;
    MS_BOOL g_SPDIF_MuteStatus;
    AUDIO_SPDIF_OUTPUT_TYPE g_eSpdifOutputType;
    MS_U8   g_SpdifNpcmPath;

    MS_BOOL g_dolbyLoudness_Enable;
    MS_U8   g_dolbyLoudness_DTVsystem;

    MS_U8   g_u8DspCodeType;
    MS_U8   g_u8Dsp2CodeType;

    MS_U8   g_u8MADSkipResetFlag;                         //add for STB PVR skip-> play reset use
    MS_U8   g_u8MAD2SkipResetFlag;                       //add for STB PVR skip-> play reset use

    MS_U16  u16DecodeFrmCnt[AU_DEC_MAX];

    MS_U8   g_u8AdvSndEffDspCodeType;
    MS_U8   g_u8DspAliveFlag;
    MS_U8   g_u8AudioCrashFlag;    

    MS_U8   g_u8SifDspType;
    MS_U16  sif_gain_0[6];
    MS_U16  sif_shift_0[6];

    MS_U8   g_u8IntTag;   // DEC MM interrupt flag
    MS_U16  int_mb_cnt;

    MS_U8   CompressInfo;
    MS_U8   g_DSPMadMIUBank[MAX_AUDIO_BASE_ADDRESS_NUM2];
    MS_U32  g_DSPBinBaseAddress[MAX_AUDIO_BASE_ADDRESS_NUM2];
    MS_U32  g_DSPMadBaseBufferAdr[MAX_AUDIO_BASE_ADDRESS_NUM2];
    MS_U32  g_DSPDDRBinBaseAddress[MAX_AUDIO_BASE_ADDRESS_NUM2];

    MS_U32  g_u32ClientCounter;

    AUDIO_SOURCE_INFO_TYPE eMainSourceType;
    AUDIO_SOURCE_INFO_TYPE ePrevSourceType;
    AUDIO_DSP_USAGE        DspUsage[AU_DEC_MAX];
    AudioDecStatus_t            AudioDecStatus[AU_DEC_MAX];

    AUDIO_SOURCE_INFO_TYPE eAudioSource;
    AUDIO_INPUT_TYPE       eMainAudioSource;
    AUDIO_INPUT_TYPE       eSubAudioSource;
    AUDIO_INPUT_TYPE       eScartAudioSource;

    AUDIO_INIT_INFO        AudioSystemInfo;
    AUDIO_OUT_INFO         AudioOutputInfo;             // Store the connectivity of audio output device
    AUDIO_PATH_INFO        AudioPathInfo;               // Store the connectivity of audio DSP & output path
    OUTPUT_SOURCE_INFO     AudioOutputSourceInfo;       // Store the output port source setting

    DigitalOutSetting_t stDigitalOutSetting[DIGITAL_MAX_OUTPUT];
    Digital_Out_Channel_Status_t stDigitalOutChannelStatus[DIGITAL_MAX_OUTPUT];

    MS_U16  mainAudioDelay;
    MS_U8   ChipRevision;
    MS_U8   g_dolby_truehd_enable;

    AUDIO_CAPABILITIES AudioCaps[AU_DEC_MAX];

    Digital_Out_Device_Capability_t stDigitalOutCodecCapability[2][CODEC_MAX];

    MS_U8 g_PreMainDspCodeType;
    MS_BOOL DolbyAACFlag;
    MS_BOOL DolbyEncFlag;
    MS_BOOL g_bHashkeyFlag;
} AUDIO_SHARED_VARS2;

//=====================================================

void MDrv_AUDIO_SetEntertainmentMode(AUDIO_ENTERTAINMENT_MODE u16Mode);
void MDrv_AUDIO_SPDIF_SetOutputType (AUDIO_SOURCE_INFO_TYPE eSource, AUDIO_SPDIF_OUTPUT_TYPE eType);
MS_BOOL MDrv_AUDIO_SetDataCaptureSource(AUDIO_DEVICE_TYPE eID, AUDIO_CAPTURE_SOURCE_TYPE eSource);
AUDIO_DEC_ID MDrv_AUDIO_OpenDecodeSystem(AudioDecStatus_t * p_AudioDecStatus);
MS_BOOL MDrv_AUDIO_CheckPlayDone(void);

#ifdef __cplusplus
}
#endif

#endif // _DRV_AUDIO_IF_H_

