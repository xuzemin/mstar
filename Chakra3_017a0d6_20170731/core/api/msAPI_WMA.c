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

////////////////////////////////////////////////////////////////////////////////
//
/// @file msAPI_MP3.c
/// @brief API for MP3 decoding and display
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////

#define MSAPI_WMA_C

#include <stdio.h>
#include <string.h>

#include "sysinfo.h"
#include "hwreg.h"
#include "MsTypes.h"
#include "drvBDMA.h"
#include "BinInfo.h"
#include "drvAUDIO.h"
#include "SysInit.h"
//#include "msGPIO.h"
#include "drvGPIO.h"
#include "GPIO.h"

//#include "msAPI_ADC.h"
#include "msAPI_MIU.h"
#include "msAPI_WMA.h"
#include "msAPI_Memory.h"
#include "msAPI_Timer.h"
#include "msAPI_audio.h"
#include "msAPI_Music.h"

#include "IOUtil.h"

#include "msAPI_audio.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalVar.h"
#include "msAPI_OSD.h"
#define WMA_DBG(x)     //x

//**********************************************************
//**********************************************************

void msAPI_WMA_Init(En_DVB_decSystemType enDecSystem)
{
//    BININFO BinInfo;
    BOOLEAN bUserMute = msAPI_AUD_IsAudioMutedByUser();
//    BOOLEAN bResult;

    //MApp_InputSource_ChangeAudioSource( stSystemInfo.enInputSourceType,UI_INPUT_SOURCE_NONE );
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);

    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_STOP);

    MDrv_AUDIO_SetPlayFileFlag(DSP_DEC, 0);
    MApi_AUDIO_SetSystem(enDecSystem);

    if(!bUserMute)
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);

    //force unmute ... the mute might be triggerrd from SIF which we can hardly
    // determine which type it is...
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
	msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYSYNC_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE); //gchen @ 20180129 //wma patch
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, stGenSetting.g_SoundSetting.Volume, 0);
}

void msAPI_WMA_StartDecode(void)
{
    //MDrv_MAD_SetDecCmd(0x04);
    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAYFILE);
}

void msAPI_WMA_StopDecode(void)
{
    //MDrv_MAD_SetDecCmd(0x00);
    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_STOP);
}

void msAPI_WMA_PauseDecode(void)
{
    //MDrv_MAD_SetDecCmd(0x06);
    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PAUSE);
}

U8 msAPI_WMA_CheckPlayDone(void)
{
    if (MApi_AUDIO_CheckPlayDone() == 1)
    {
        msAPI_WMA_StopDecode();
        WMA_DBG(printf("\nPlay done"));
        return TRUE;
    }
    return FALSE;
}

U32 msAPI_WMA_GetCurrentFrameNumber(void)
{
    //return MDrv_MAD_MPEG_GetframeNum();
    return MApi_AUDIO_GetMpegInfo(Audio_MPEG_infoType_FrameNum);
}

U16 msAPI_WMA_GetSampleRate(void)
{
    return MApi_AUDIO_GetWmaInfo(Audio_WMA_infoType_SampleRate);
}

U32 msAPI_WMA_GetBitRate(void)
{
    return MApi_AUDIO_GetWmaInfo(Audio_WMA_infoType_BitRate);
}

void msAPI_WMA_SetInput(void)
{
    MApi_AUDIO_SetInput();
}

void msAPI_WMA_FileEndNotification(void)
{
    MApi_AUDIO_FileEndNotification();
}

void msAPI_WMA_FileEndDataHandle(U32 u32DataLeft)
{
    MApi_AUDIO_FileEndDataHandle(u32DataLeft);
}

U8 msAPI_WMA_CheckInputRequest(U32 *pU32WrtAddr, U32 *pU32WrtBytes)
{
     if (MDrv_AUDIO_GetPlayFileFlag(DSP_DEC))
    {

        MDrv_AUDIO_SetPlayFileFlag(DSP_DEC, 0);

        *pU32WrtAddr = MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_DEC1_BufferAddr);
        *pU32WrtAddr += (U32)(msAPI_AUD_GetDspMadBaseAddr(DSP_DEC));
        *pU32WrtBytes = MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_DEC1_BufferSize);

        return TRUE;
    }
    return FALSE;

}

void msAPI_WMA_CleanFileEndData(U32 StrAddr, U32 length, U32 ClearValue)
{
    //MApi_GFX_ClearFrameBufferByWord() didn't work in T4 m4a case??
    //anyway, use memset to clear
    //MApi_GFX_ClearFrameBufferByWord(StrAddr, length, ClearValue);
    memset((void*)_PA2VA(StrAddr), ClearValue, length);
    MApi_GFX_FlushQueue();
}

U32 msAPI_WMA_GetPlayTick(void)
{
    return MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_1ms_PTS);
}

U16 msAPI_WMA_GetEsMEMCnt(void)
{
    return (U16)MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_ADEC1_esBuf_currLevel); // Unit : Byte
}

#if ENABLE_ASF_PARSING
void msAPI_WMA_SetASFParm(WMA_ASF_PARMTYPE parm_type, U32 value)
{
    MApi_AUDIO_SetWmaInfo(Audio_WMA_infoType_Asf_Param, parm_type, value);
}
#endif

#undef MSAPI_WMA_C
