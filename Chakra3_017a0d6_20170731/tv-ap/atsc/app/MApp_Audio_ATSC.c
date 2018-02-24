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
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
/// @file MApp_ATSC_Audio.c
/// @author MStar Semiconductor Inc.
/// @brief Channel Change control for APP layer
////////////////////////////////////////////////////////////////////////////////

//******************************************************************************
//                    Header Files
//*****************************************************************************

#include "Board.h"

#if(ENABLE_ATSC)

#include "apiAUDIO.h"

#include "msAPI_audio.h"
#include "msAPI_demux.h"

#include "MApp_Audio_ATSC.h"

#include "MApp_GlobalFunction.h"

#include "MApp_Psip.h"

#if(ENABLE_ATSC_TTS)
#include "MApp_TTSControlHandler.h"
#endif

char* MApp_Audio_ATSC_Get_StreamTypeString(EN_AUD_STREAM_TYPE eAUD_STREAM_TYPE)
{
    char* pcStreamTypeStr = "";

    switch(eAUD_STREAM_TYPE)
    {
        case AUD_STREAM_TYPE_MPEG:
            pcStreamTypeStr = "MPEG";
            break;

        case AUD_STREAM_TYPE_AAC:
            pcStreamTypeStr = "AAC";
            break;

        case AUD_STREAM_TYPE_AC3:
            pcStreamTypeStr = "AC3";
            break;

        default:
            pcStreamTypeStr = "Unknown";
            break;
    }

    return pcStreamTypeStr;
}

void MApp_Audio_ATSC_Set_DecodeSystem(EN_AUD_STREAM_TYPE eAUD_STREAM_TYPE)
{
    //PRINT_CURRENT_LINE();
    DEBUG_ATSC_AUDIO_SYS( printf("MApp_Audio_ATSC_Set_DecodeSystem(eAUD_STREAM_TYPE=%u(%s))\n",
        eAUD_STREAM_TYPE, MApp_Audio_ATSC_Get_StreamTypeString(eAUD_STREAM_TYPE) ); );

    if( eAUD_STREAM_TYPE >= AUD_STREAM_TYPE_NUMS )
    {
        printf("\nWarning: eAUD_STREAM_TYPE=%u!\n", eAUD_STREAM_TYPE);
        return;
    }


/*
    if( bAutoStop )
    {
        MApi_AUDIO_SetCommand( MSAPI_AUD_DVB_DECCMD_STOP );
    }
    */

    /* set decoder system and reload firmware code */
    En_DVB_decSystemType eDecSystemType = MSAPI_AUD_DVB_INVALID;
    AUDIO_DSP_SYSTEM eAudioDSPSystem = E_AUDIO_DSP_INVALID;

    switch(eAUD_STREAM_TYPE)
    {
        case AUD_STREAM_TYPE_MPEG:
            eDecSystemType = MSAPI_AUD_DVB_MPEG;
            eAudioDSPSystem = E_AUDIO_DSP_MPEG;
            break;

        case AUD_STREAM_TYPE_AAC:
            eDecSystemType = MSAPI_AUD_DVB_AAC;
            eAudioDSPSystem = E_AUDIO_DSP_AACP;
            break;

        default:
        case AUD_STREAM_TYPE_AC3:
            eDecSystemType = MSAPI_AUD_DVB_AC3;
            eAudioDSPSystem = E_AUDIO_DSP_AC3;
            break;
    }

    MApi_AUDIO_SetSystem(eDecSystemType);
    msAPI_AUD_Set_CurDspSystem(eAudioDSPSystem);

/*
    if( bAutoPlay )
    {
        // todo
        MApi_AUDIO_SetCommand( MSAPI_AUD_DVB_DECCMD_PLAY );
    }
*/

    DEBUG_ATSC_AUDIO_SYS( printf("MApp_Audio_ATSC_Set_DecodeSystem() end at %u\n", MsOS_GetSystemTime()); );
}

void MApp_Audio_ATSC_ReInit_DecodeSystem(EN_AUD_STREAM_TYPE eAudStreamType, U16 u16AudioPid)
{
    DEBUG_ATSC_AUDIO_SYS( printf("MApp_Audio_ATSC_ReInit_DecodeSystem(eAudStreamType=%u(%s), u16AudioPid=%u)\n",
        eAudStreamType, MApp_Audio_ATSC_Get_StreamTypeString(eAudStreamType),  u16AudioPid); );

#if(CHIP_FAMILY_EDEN == CHIP_FAMILY_TYPE)
 #if (ENABLE_ATSC_TTS)
    // Check TTS status: If TTS is in speaking, wait speak end
    if( MApp_TTS_Is_InSpeaking() )
    {
        //PRINT_CURRENT_LINE();
        MApp_TTS_WaitSayFinish(TTS_NO_TIMEOUT);
    }
 #endif
#endif

    /* mute */
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);

    /* stop audio decoder */
    MApi_AUDIO_SetCommand( (En_DVB_decCmdType)MSAPI_AUD_STOP );

    /* stop audio filter */
    if( u16AudioPid && (u16AudioPid != MSAPI_DMX_INVALID_PID) )
    {
        msAPI_DMX_Stop( u8AudFid );
    }

    DEBUG_AU_LOAD_CODE( printf("eAudStreamType=%u\n", eAudStreamType); );

    MApp_Audio_ATSC_Set_DecodeSystem(eAudStreamType);


    // start filter should be after than start audio decoder to prevent audio ES buffer overflow
    /* set audio PID & start filter */
    if( u16AudioPid && (u16AudioPid != MSAPI_DMX_INVALID_PID) )
    {
        msAPI_DMX_StartFilter( u16AudioPid, MSAPI_DMX_FILTER_TYPE_AUDIO, &u8AudFid );
    }

    /* start audio decoder */
    MApi_AUDIO_SetCommand( (En_DVB_decCmdType)MSAPI_AUD_PLAY );

    /* unmute */
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);

}

void MApp_Audio_ATSC_ReInit_DecodeSystem_ByAudLangIdx(U8 u8AudLangIdx )
{
    DEBUG_ATSC_AUDIO_SYS( printf("MApp_Audio_ATSC_ReInit_DecodeSystem_ByAudLangIdx(u8AudLangIdx=%u)\n", u8AudLangIdx); );

    U16 u16AudioPid = MApp_GetAudioSoundTrackPID( u8AudLangIdx );

    EN_AUD_STREAM_TYPE eAudStreamType = MApp_ATSC_Get_AudioStreamType();

    MApp_Audio_ATSC_ReInit_DecodeSystem(eAudStreamType, u16AudioPid);
}

#if (ENABLE_ATSC_AD_FUNC)
void MApp_Audio_ATSC_Set_DecodeSystem_AD(EN_AUD_STREAM_TYPE eAUD_STREAM_TYPE)
{
    DEBUG_AU_LOAD_CODE( printf("MApp_Audio_ATSC_Set_DecodeSystem_AD(eAUD_STREAM_TYPE=%u)\n", eAUD_STREAM_TYPE); );

    En_DVB_decSystemType eDecSystemType = MSAPI_AUD_DVB_INVALID;
    AUDIO_DSP_SYSTEM eAudioDSPSystem = E_AUDIO_DSP_INVALID;

    switch(eAUD_STREAM_TYPE)
    {
        case AUD_STREAM_TYPE_MPEG:
            eDecSystemType = MSAPI_AUD_DVB2_MPEG;
            eAudioDSPSystem = E_AUDIO_DSP_MPEG_AD;
            break;

        case AUD_STREAM_TYPE_AAC:
            eDecSystemType = MSAPI_AUD_DVB2_AAC;
            eAudioDSPSystem = E_AUDIO_DSP_AACP_AD;
            break;

        default:
            printf("\nWarning: eAUD_STREAM_TYPE=%u!\n", eAUD_STREAM_TYPE);

        case AUD_STREAM_TYPE_AC3:
            eDecSystemType = MSAPI_AUD_DVB2_AC3;
            eAudioDSPSystem = E_AUDIO_DSP_AC3_AD;
            break;
    }

    MApi_AUDIO_SetSystem(eDecSystemType);

    msAPI_AUD_Set_CurDspSystem(eAudioDSPSystem);

}

#endif // ENABLE_ATSC_AD_FUNC

#endif

