
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
/*
++++++++++++++++++++++++++++++++++???????????????++++++++++++++++++++++++++++++++++++++++++??????????????????????++++++++++++++++++++++++++++++++++++++++=++????
++++++++++++++++++++++++++++++++++IIIIIIIIIIIIII????????????????????????????????????????????IIIIIIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++++++++++++++++++++++++++++++++IIIIIIIIIIII????????????????????????????????????????????????IIIIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++++=+IIIIIIIIIII+++++++++++++++?$$$$$$$$$77II??????????I???????????????????????????????????IIIIIIIIIIIIIII?III??????????????????????????????????????????IIIII
+++++++DMMMMMMMMMMMZI++++++++++++=NMMMMMMMMMMMZ$?I77$$$$$$I?????????????????????????????????????IIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++++=8MMMMMMMMMMMMD7=+++++++++IMMMMMMMMMMMMM8OZZ$7I???????????????????????????????????????????IIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++++=8MMMMMMMMMMMMM8++++++++++DMMMMMMMMMMMMMD8$I?????????????????III???????????????????????????IIIIIIIIIIII?III??????????????????????????????????????????IIIII
+++=+?=8MMMMMMMMMMMMMMZZ++++++?DMMMMMMMMMMMMMMZZ???????????????IIIIIIIIIII????????????????????????IIIIIIIIIII?III??????????????????????????????????????????IIIII
+++++I=DMMMMMMMMMMMMMMMN?=++++8MMMMMMMMMMMMMMMZ$??????????????IIIIIIIIIIIIII??????????????????????IIIIIIIIIII?III??????????????????????????????????????????IIIII
+++++I+8MMMMMMMMMMMMMMMMD?=+IDMMMMMMMMMMMMMMMM$$?????????????IIIIIIIIIIIIIIII????????????????????IIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++?I+8MMMMMMMMMMMMMMMMMOI~OMMMMMMMMMMMMMMMMM$$?????????????IIIIIIIIIIIIIIIII????????????IIIIIIIIIIIIIIIIIII?III??????????????????????????????????????????IIIII
++++II+8MMMMMMMMMMMNNMMNMND8MMNNMMNNMMMMMMMMMMZ$????????????IZZ8888OZ7IIIIIIIIIIIIIIIIIIIIIIZD7IIIIIIIIIIIIII?IIIIIIIIIII???????????????????????IIIIIIIIIIIIIIII
++++II+8MMMMMMMMMMII????????OOOOOOZ8MMMMMMMMMMZ$??????????ZDMMMMMDDDNND87IIIIIIIIIIIIIII?Z8MMDIIIIIIIIIIIIIII?IIIIIIIIIII???????????????????????IIIIIIIIIIIIIIII
+++III+8MMMMMMMMMMI++++++7$ZZZZZZZOOMMMMMMMMMMZ$??????IINMMMMMMD+IIII7I7DMMIIIIIIII?I8NMMMMMMD?IIIIIIIIIIIIII?IIIIIIIIIII???????????????????????IIIIIIIIIIIIIIII
+++III+8MMMMMMMMMMI+++++I$ZZZZZZZZ$ZMMMMMMMMMMZ$??????IMMMMMMMMMI??????IIO87IIIIII?DMMMMMMMMMD?IIIIIIIIIIIIII?IIIIIIIIIII???????????????????????IIIIIIIIIIIIIIII
++?III+8MMMMMMMMMMI++=$$ZZZZZZZZZIIZMMMMMMMMMMZ$??????MMMMMMMMMMMZ??????????????IIIMMMMMMMMMMD$ZZZZIIIIIIIIII+Z8DDNMMMDDDOO$I?????????????IIIII$ZZZ7IIII7O8887II
+?IIII+8MMMMMMMMMMI++7ZZZZZZZZZZI+IZMMMMMMMMMMZ$????7ZMMMMMMMMMMMM$????????????OMMMMMMMMMMMMMMMMMMNIIIIIIIII8MMMD888DMMMMMMMND$?????????8MMMMMMMMMMOII78MMMMM8?I
+?IIII+8MMMMMMMMMMI?7ZZZZZZZZZZ?++IZMMMMMMMMMMZ$????7ZMMMMMMMMMMMMMM8??????????+++?MMMMMMMMMM8IIIIIIIIIIIZMMM77IIIIIII8MMMMMMMMND?II????8MMMMMMMMMMOODNZII7Z8I7I
?IIIII+8MMMMMMMMMMZZZZZZZZZZZZI+++IZMMMMMMMMMMZ$??????NMMMMMMMMMMMMMMDII??????????IMMMMMMMMMM8IIIIIIIIIIIO8ZI?IIIIIIIIZDMMMMMMMMMD??????8MMMMMMMMMMN8D7IIIIIIIII
?IIIII+8MMMMMMMMMNZZZZZZZZZZZZ++++?ZMMMMMMMMMMZ$??????ZMMMMMMMMMMMMMMMMN7?????????IMMMMMMMMMM8IIIIIIIIIIIIIII?IIIIIIIIZDMMMMMMMMMMI?????8MMMMMMMMMM8IIIIIIIIIIII
?IIIII+8MMMMMMMMN8ZZZZZZZZZZZ?++++?ZMMMMMMMMMMZ$??????I8MMMMMMMMMMMMMMMM8?????????IMMMMMMMMMMO?IIIIIIIIIIIII7I7777777IODMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMMNZZZZZZZZZZZZ7+++++?ZMMMMMMMMMMZ$????????8MMMMMMMMMMMMMMMMDD???????IMMMMMMMMMMO??IIIIIIIII7DMMMMMMMDDMDDNMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMNZZZZZZZZZZZZ$++++++?ZMMMMMMMMMMZ$I????????7NMMMMMMMMMMMMMMMMDI?????IMMMMMMMMMMO????IIIIIZ8MMMMMMMM7III7ONMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMNOZZZZZZZZZZZ7++++++?ZMMMMMMMMMMZ$III??????+IMMMMMMMMMMMMMMMMN$+????IMMMMMMMMMMO????IIII?NMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMMMMNOZZZZZZZZ?++++++?ZMMMMMMMMMMZ$IIII????????ZMMMMMMMMMMMMMMMO?????IMMMMMMMMMMZ?????III$MMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII+8MMMMMMMMMM?$ZZZZZZ$+++++++?ZMMMMMMMMMMZ$IIIIIIIIII???ZMMMMMMMMMMMMMMDZ????IMMMMMMMMMMZ?????IIIZMMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIII=DMMMMMMMMMM?++7ZZZ7?+++++++IZMMMMMMMMMMZ$IIIIIIIIIIIIII7OMMMMMMMMMMMM8?????IMMMMMMMMMMZ????IIIIZMMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?II?II+8MMMMMMMMMMI++?ZOZ7?+++++++?ZMMMMMMMMMMZ$IIII7OZIIIIIIIII8MMMMMMMMMMMZ?????IMMMMMMMMMM$???OOD7IIMMMMMMMMMN?IIIIZDMMMMMMMMMMI?????8MMMMMMMMMMOIIIIIIIIIIII
?IIIMMMMMMMMMMMMMMNNNN8O$I++++?NMNNMMMMMMMMMMMMMMD8I77NM8IIIIIIIIOMMMMMMMMMO??????+8MMMMMMMMMZ??$MM$?IIZMMMMMMMMM?IIIZNMMMMMMMMMMMZ?????8MMMMMMMMMMOIIIIIIIIIIII
?II?MMMMMMMMMMMMMMMMMM88??++++?MMMMMMMMMMMMMMMMMMD8II7IDMMOIIIIIIOMMMMMMMDOIIII??I??NMMMMMMMMMO8MZ$?IIIIZMMMMMMMMZIZ8MDMMMMMMMMMMMO?????8MMMMMMMMMMOIIIIIIIIIIII
?II?DDDDDDDDDDDDDDD8DDZ$++++++?D8D8DDDDDDDDDDDDDDOZIIIIII?7ODMMMMMMMNDZ7?IIIIIII??????ZDMMMMN8Z7??I?IIIIIIIZ8MMMMN8Z??7$ZZZZZZZZZZZ+????IZZZZZZZZZZ7IIIIIIIIIIII
?IIIII++++++++++++++++=+++++++++++IIIIIIIIIIIIIIIIII???I?????I77ZZ77IIIIIIIIIIIII????I???II??????????IIIIIIII?777IIIIIIII???????????????????????IIIIIIIIIIIIIIII
*/
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

#define MSAPI_PLAYER_C

#include <string.h>
#include "Board.h"                  //For pvr select
#include "MsCommon.h"
#ifdef PVR_8051
#include "drvUART.h"                //For compiled error
#endif

#if ENABLE_PVR

//driver
#include "SysInit.h"                 //For window1 switch
#ifdef PVR_8051
#ifndef S3PLUS
#include "drvByteDMA.h"             //For pattern search
#endif
#endif
#include "GPIO.h"                   //For audio
//#include "drvaudvb.h"             //For audio
#ifdef PVR_8051
#include "drvMVD.h"                 //For video
#else
//#include "drvmvd_if.h"            //For video
#endif
#ifndef S3PLUS
#include "drvPQ.h"                  //For reduce scaler bw usage
#endif
#include "drvTVEncoder.h"           //For video encoder

//api
#include "msAPI_Timer.h"            //For timer
#include "msAPI_MIU.h"              //For memory dma
//#include "msAPI_Demux.h"          //For demux part
//#include "msAPI_SIF.h"            //For audio
//#include "msapi_audio.h"          //For audio
#include "msAPI_PVR.h"              //For pvr
#include "MApp_TimeShift.h"
#ifdef PVR_8051
#include "msAPI_Scaler.h"           //For scaler
#else
//#include "mvideo_if.h"
//#include "apiXC_Ext.h"
//#include "msAPI_Scaler_Front.h"     //For scaler
#include "apiDMX.h"                 //For demux part
#include "apiXC_Adc.h"              //For scaler
#include "apiXC.h"                  //For scaler
#include "apiXC_Sys.h"              //For scaler
#endif
#include "msAPI_Video.h"            //For video
#ifdef PVR_8051
#include "msAPI_MPEG2.h"            //For video
#endif
#include "msAPI_Player.h"           //For itself

//app <--better not be here
#include "MApp_MVDMode.h"           //for video
#include "MApp_ChannelChange.h"     //For channel change
#include "MApp_Audio.h"

/*************************************************************************************************/

#define DEBUG_API_PLAYER(x) //x
/*************************************************************************************************/

/*###############################################################################################*/
/*/////////////////////////////////////// audio control /////////////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
void msAPI_Player_AudioInit(enPlayAudioType enType, enPlaySource enSource, BOOLEAN bEnableAD, enPlayAudioType enAdType)
{
    if ((enSource == E_PLAY_SOURCE_LIVE)||(enSource == E_PLAY_SOURCE_FILE))
    {
        /* Audio */
        #ifdef PVR_8051
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_SWITCH_AUDIOSTREAMMODE, enType, 0);
        #else
        #ifdef PVR_UTOPIA
        MApp_ChannelChange_Set_Audio_Decoder_System((WORD)enType);
        #else
        msAPI_AUD_SetDecSystem((En_DVB_decSystemType)enType);
        #endif
        #endif

        /* AD */
        #ifdef PVR_8051
            #if (defined(S3PLUS) || defined(S4LITE))
            UNUSED(bEnableAD);
            UNUSED(enAdType);
            //enAdType = E_PLAY_AUDIO_TYPE_INVALID;
            #else
            if (bEnableAD)
            {
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_SWITCH_AUDIOSTREAMMODE, enAdType, 0);
                msAPI_AUD_SetADOutputMode(stGenSetting.g_SoundSetting.ADOutput);
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_DTV_AUDIO_COMMAND, E_AUDIO_DVB2_COM_PLAY, 0);
            }
            #endif
        #else
        UNUSED(bEnableAD);
        UNUSED(enAdType);
        //enAdType = E_PLAY_AUDIO_TYPE_INVALID;
        #endif
    }
}

/***************************************************************************************/
void msAPI_Player_AudioStop(void)
{
//    MUTE_On();     //no need it, it may cause some pop noise when play/stop PVR

    #ifdef S3PLUS
    msAPI_AUD_SetDecCommand(AU_DVB_FreeRunMode_AVsync);
    #endif

    #ifdef PVR_UTOPIA
    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_STOP);
    #else
    msAPI_AUD_SetDecCommand(MSAPI_AUD_DVB_DECCMD_STOP);
    #endif
}

/***************************************************************************************/
void msAPI_Player_AudioPause(void)
{
//    MUTE_On();    //no need it, it may cause some pop noise when play/stop PVR

    #ifdef PVR_UTOPIA
    MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PAUSE);
    #else
    msAPI_AUD_SetDecCommand(MSAPI_AUD_DVB_DECCMD_PAUSE);
    #endif
}

/***************************************************************************************/
void msAPI_Player_AudioPlay(enPlaySource enSource)
{
    if(enSource == E_PLAY_SOURCE_LIVE)
    {
    #ifndef S3PLUS

      #ifdef PVR_UTOPIA
        MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAY);
      #else
        msAPI_AUD_SetDecCommand(MSAPI_AUD_DVB_DECCMD_PLAY);
      #endif

        MApp_Audio_Set_AmpMute(AUDIO_AMP_MUTE_OFF);

    #else

        msAPI_AUD_SetDecCommand(MSAPI_AUD_DVB_DECCMD_PLAY);
        msAPI_AUD_SetDecCommand(MSAPI_AUD_DVB_DECCMD_AVSYNC);

        MApp_Audio_Set_AmpMute(AUDIO_AMP_MUTE_OFF);
    #endif
    }
    else
    {
    #ifndef S3PLUS

      #ifdef PVR_UTOPIA
        MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAY);
      #else
        msAPI_AUD_SetDecCommand(MSAPI_AUD_DVB_DECCMD_PLAY);
      #endif

        MApp_Audio_Set_AmpMute(AUDIO_AMP_MUTE_OFF);

    #else

        msAPI_AUD_SetDecCommand(MSAPI_AUD_DVB_DECCMD_PLAYFILETSP);
        msAPI_AUD_SetDecCommand(MSAPI_AUD_DVB_DECCMD_FREE_RUN);

        MApp_Audio_Set_AmpMute(AUDIO_AMP_MUTE_OFF);
    #endif
    }
}

/***************************************************************************************/
enPlayAudioType msAPI_Player_Convert_AudioStreamType_To_PlayAudioType(AUDIOSTREAM_TYPE eAUDIOSTREAM_TYPE)
{
    enPlayAudioType ePlayAudioType = E_PLAY_AUDIO_TYPE_INVALID;

    switch(eAUDIOSTREAM_TYPE)
    {
        case E_AUDIOSTREAM_MPEG:
            ePlayAudioType = E_PLAY_AUDIO_TYPE_MPEG;
            break;

        case E_AUDIOSTREAM_AC3:
            ePlayAudioType = E_PLAY_AUDIO_TYPE_AC3;
            break;

        case E_AUDIOSTREAM_MPEG_AD:
            ePlayAudioType = E_PLAY_AUDIO_TYPE_MPEG_AD;
            break;
        case E_AUDIOSTREAM_MPEG4:
            ePlayAudioType = E_PLAY_AUDIO_TYPE_MPEG4;
            break;
        case E_AUDIOSTREAM_AAC:
            ePlayAudioType = E_PLAY_AUDIO_TYPE_AAC;
            break;
        case E_AUDIOSTREAM_AC3P:
            ePlayAudioType = E_PLAY_AUDIO_TYPE_AC3P;
            break;
        case E_AUDIOSTREAM_AC3_AD:
            ePlayAudioType = E_PLAY_AUDIO_TYPE_AC3_AD;
            break;
        case E_AUDIOSTREAM_AC3P_AD:
            ePlayAudioType = E_PLAY_AUDIO_TYPE_AC3P_AD;
            break;

        case E_AUDIOSTREAM_AACP_AD:
            ePlayAudioType = E_PLAY_AUDIO_TYPE_AACP_AD;
            break;

        case E_AUDIOSTREAM_DRA:
            ePlayAudioType = E_PLAY_AUDIO_TYPE_DTS;
            break;

        //case E_AUDIOSTREAM_MP3:
        //    ePlayAudioType = E_PLAY_AUDIO_TYPE_MP3;
        //    break;

        default:
        case E_AUDIOSTREAM_INVALID:
            ePlayAudioType = E_PLAY_AUDIO_TYPE_INVALID;
            break;

    }

    return ePlayAudioType;
}

void msAPI_Player_AudioRestore(BOOLEAN bEnableAD)
{
    enPlayAudioType eCurPlayAudType = msAPI_Player_Convert_AudioStreamType_To_PlayAudioType(g_wCurrent_AudioType);

    if( eCurPlayAudType != E_PLAY_AUDIO_TYPE_INVALID )
    {
        #if (defined(S3PLUS) || defined(S4LITE))
        msAPI_Player_AudioInit(eCurPlayAudType, E_PLAY_SOURCE_LIVE, bEnableAD, E_PLAY_AUDIO_TYPE_INVALID);
        #else
        msAPI_Player_AudioInit(eCurPlayAudType, E_PLAY_SOURCE_LIVE, bEnableAD, msAPI_Player_Convert_AudioStreamType_To_PlayAudioType(g_enCurrent_AudioDescriptorType));
        #endif
    }
}

/***************************************************************************************/
enPlayAudioType msAPI_Player_AudioGetType(void)
{
    //enPlayAudioType enRet = (enPlayAudioType)g_wCurrent_AudioType;
    enPlayAudioType enRet = msAPI_Player_Convert_AudioStreamType_To_PlayAudioType(g_wCurrent_AudioType);
    return enRet;
}

/***************************************************************************************/
enPlayAudioType msAPI_Player_AdAudioGetType(void)
{
    #if (defined(S3PLUS) || defined(S4LITE))
    enPlayAudioType enRet = E_PLAY_AUDIO_TYPE_INVALID;
    #else
    //enPlayAudioType enRet = (enPlayAudioType)g_enCurrent_AudioDescriptorType;
    enPlayAudioType enRet = msAPI_Player_Convert_AudioStreamType_To_PlayAudioType(g_enCurrent_AudioDescriptorType);
    #endif

    return enRet;
}

/***************************************************************************************/

/*###############################################################################################*/
/*/////////////////////////////////////// scaler control ////////////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
static BOOLEAN _bPlaybackScalerNeedFree          = FALSE;
static U32     _u32PlaybackScalerWaitFreezeTime  = 0;
static U32     _u32PlaybackScalerCheckFreezeTime = 0;

/***************************************************************************************/
void msAPI_Player_ScalerFreeze(void)
{
    if( MApi_XC_IsCurrentFrameBufferLessMode() )
    {
        //MApi_XC_GenerateBlackVideo(TRUE,MAIN_WINDOW);
        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_PVR, ENABLE, 0, MAIN_WINDOW);
    }
    else
    {
        MApi_XC_FreezeImg(TRUE, MAIN_WINDOW);
    }
}

/***************************************************************************************/
void msAPI_Player_ScalerFree(void)
{
    if( IsDTVInUse() )
    {
        msAPI_VID_Command(MSAPI_VID_PLAY);
    }
    else
    {
        MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);
    }

    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_PVR, DISABLE, 0, MAIN_WINDOW);
}

/***************************************************************************************/
void msAPI_Player_ScalerWaitFree(U32 u32WaitTime)
{
    _bPlaybackScalerNeedFree          = TRUE;
    _u32PlaybackScalerWaitFreezeTime  = u32WaitTime;
    _u32PlaybackScalerCheckFreezeTime = msAPI_Timer_GetTime0();
  //printf("Before Free Image\n");
}

/***************************************************************************************/
void msAPI_Player_ScalerCheckFree(void)
{
    if(_bPlaybackScalerNeedFree == TRUE)
    {
        if(msAPI_Timer_DiffTimeFromNow(_u32PlaybackScalerCheckFreezeTime) > _u32PlaybackScalerWaitFreezeTime)
        {
            _bPlaybackScalerNeedFree          = FALSE;
            _u32PlaybackScalerWaitFreezeTime  = 0;
            _u32PlaybackScalerCheckFreezeTime = 0;

            MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);

            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_PVR, DISABLE, 0, MAIN_WINDOW);

          //printf("After Free Image\n");
        }
    }
}

/***************************************************************************************/
void msAPI_Player_ScalerMute(U32 u32MuteTime)
{
    //MApi_XC_GenerateBlackVideo(TRUE, MAIN_WINDOW);
    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, u32MuteTime, MAIN_WINDOW);
}

/***************************************************************************************/
#ifndef PVR_UTOPIA
static BOOLEAN msAPI_Player_VideoGetInfo(MMSAPI_VID_STATUS *pstVidStatus);
#endif
void msAPI_Player_ScalerReduceBW(BOOLEAN bEnable)
{
    #ifdef PVR_UTOPIA
    VDEC_DispInfo stVidInfo;
    #else
    MMSAPI_VID_STATUS stVidInfo;
    #endif

  //printf("msAPI_Player_ScalerReduceBW: %d\n", bEnable);

    if (bEnable)
    {
        #ifdef PVR_UTOPIA
        if (msAPI_VID_GetVidInfo(&stVidInfo))
        #else
        if (msAPI_Player_VideoGetInfo(&stVidInfo))
        #endif
        {
            //printf("H: %d, V=%d\n", stVidInfo.u16HorSize, stVidInfo.u16VerSize);

            #ifndef S3PLUS
            if (stVidInfo.u16HorSize > 720)
            #endif
            {
                #ifdef PVR_8051
                #ifndef S3PLUS
                MDrv_PQ_ReduceBW_ForPVR(TRUE);
                #else
                MDrv_Scaler_SetMADI_2RMode(TRUE);
                MDrv_Scaler_ReduceBW_ForPVR(TRUE);
                #endif
                #else
                #ifdef PVR_UTOPIA
                MDrv_PQ_ReduceBW_ForPVR(PQ_MAIN_WINDOW,TRUE);
                #else
                MDrv_PQ_ReduceBW_ForPVR(MAIN_WINDOW,TRUE);
                #endif
                #endif
            }
        }
        else
        {
            #ifdef PVR_8051
            #ifndef S3PLUS
            MDrv_PQ_ReduceBW_ForPVR(TRUE);
            #else
            MDrv_Scaler_SetMADI_2RMode(TRUE);
            MDrv_Scaler_ReduceBW_ForPVR(TRUE);
            #endif
            #else
            #ifdef PVR_UTOPIA
            MDrv_PQ_ReduceBW_ForPVR(PQ_MAIN_WINDOW,TRUE);
            #else
            MDrv_PQ_ReduceBW_ForPVR(MAIN_WINDOW,TRUE);
            #endif
            #endif
        }
    }
    else
    {
        #ifdef PVR_8051
        #ifndef S3PLUS
        MDrv_PQ_ReduceBW_ForPVR(FALSE);
        #else
        MDrv_Scaler_SetMADI_2RMode(FALSE);
        MDrv_Scaler_ReduceBW_ForPVR(FALSE);
        #endif
        #else
        #ifdef PVR_UTOPIA
        MDrv_PQ_ReduceBW_ForPVR(PQ_MAIN_WINDOW,FALSE);
        #else
        MDrv_PQ_ReduceBW_ForPVR(MAIN_WINDOW,FALSE);
        #endif
        #endif
    }
}

/***************************************************************************************/

/*###############################################################################################*/
/*/////////////////////////////////// video encoder control /////////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
void msAPI_Player_VideoEncoderReset(void)
{
    #ifdef PVR_8051
    #ifndef S3PLUS
    MDrv_VE_Set_BlackScreen(ENABLE);
    #endif
    #else
    #ifdef PVR_UTOPIA
    //PARDAI VERSION {  }
    #else
    MDrv_VE_set_blackscreen(ENABLE);
    #endif
    #endif
}

/***************************************************************************************/

/*###############################################################################################*/
/*/////////////////////////////////////// video control /////////////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
static U32 m_u32GOPtotal = 0;
static U32 m_u32GOPSize = 16; /// Set the min GOP = 16;
static U32 m_u32GOPTimes = 0; /// Recall times that get GOP count times

/***************************************************************************************/
void msAPI_Player_VideoInit(enPlayVideoType enVideoType, enPlaySource enSource)
{
    #ifndef S3PLUS
    if(enVideoType == E_PLAY_VIDEO_TYPE_H264)
    {
        #ifdef PVR_UTOPIA
        g_eCodecType = E_VDEC_CODEC_TYPE_H264;
        msAPI_VID_SetMappingAVCParameter(g_eCodecType);
        #else
        bAVCH264 = TRUE;
        #endif
    }
    else if(enVideoType == E_PLAY_VIDEO_TYPE_AVS)
    {
        g_eCodecType = E_VDEC_CODEC_TYPE_AVS;
        msAPI_VID_SetMappingAVCParameter(g_eCodecType);
    }
     #if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)    \
        ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)  \
        ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)    \
        ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA))
    else if(enVideoType == E_PLAY_VIDEO_TYPE_HEVC)
    {
        g_eCodecType = E_VDEC_CODEC_TYPE_HEVC;
        msAPI_VID_SetMappingAVCParameter(g_eCodecType);
    }
    #endif
    else
    {
        #ifdef PVR_UTOPIA
        g_eCodecType = E_VDEC_CODEC_TYPE_MPEG2;
        msAPI_VID_SetMappingAVCParameter(g_eCodecType);
        #else
        bAVCH264 = FALSE;
        #endif
    }
    #else
    enVideoType = enVideoType;
    #endif

    MApp_VID_VariableInit();

    #ifndef S3PLUS
    #ifdef PVR_UTOPIA
    if(enSource == E_PLAY_SOURCE_LIVE)
    {
        msAPI_VID_Init(FALSE, E_VDEC_SRC_MODE_DTV);
    }
    else
    {
        msAPI_VID_Init(FALSE, E_VDEC_SRC_MODE_TS_FILE);
    }
    #else
    msAPI_VID_Init();
    #endif
    #endif

    #ifndef S3PLUS
    #ifdef PVR_UTOPIA
    if(msAPI_VID_GetCodecType() == E_VDEC_CODEC_TYPE_H264)
    #else
    if ( bAVCH264 )
    #endif
    {
        if(enSource == E_PLAY_SOURCE_LIVE)
        {
            #ifdef PVR_UTOPIA
            //PARDAI VERSION {  }
            #else
            msAPI_VID_AVCH264EnableParserStop(0);
            #endif
        }
        else
        {
            #ifdef PVR_UTOPIA
            //PARDAI VERSION {  }
            #else
            #ifndef PVR_8051 //Chakra1
            if (eCurVdecType == E_VDEC_SVD_FW)
                msAPI_VID_AVCH264Init(); //force to init. H264 to enable write pointer in bitstream bufffer.
            #endif
            msAPI_VID_AVCH264EnableParserStop(1);
            #endif

            msAPI_VID_SetTrickModeInfo(0, 1); /// Normal play
        }
    }
    else
    #endif
    {
        if(enSource == E_PLAY_SOURCE_LIVE)
        {
            #ifdef PVR_8051
            #ifndef S3PLUS
            MDrv_Mvd_SetCodecInfo(CODEC_MPEG2, TS_MODE     , ENABLE_PARSER);
            #else
            MDrv_Mvd_SetPlayMode(FALSE, FALSE);
            #endif
            #else
            #ifdef PVR_UTOPIA
            //PARDAI VERSION {  }
            #else
            MDrv_MVD_SetCodecInfo(E_MVD_CODEC_MPEG2, E_MVD_TS_MODE, ENABLE_PARSER);
            #endif
            #endif
        }
        else
        {
            #ifdef PVR_8051
            MDrv_Mvd_SetUnderflowTH((((MVD_BITSTREAM_LEN_EX*15)/16)>>3)<<3);
            MDrv_Mvd_SetOverflowTH(((MVD_BITSTREAM_LEN_EX-0x400)>>3)<<3);
            #ifndef S3PLUS
            MDrv_Mvd_SetCodecInfo(CODEC_MPEG2, TS_FILE_MODE, ENABLE_PARSER);
            #else
            MDrv_Mvd_SetPlayMode(TRUE, FALSE);
            #endif
            #else
            #ifdef PVR_UTOPIA
            //PARDAI VERSION {  }
            #else
            MDrv_MVD_SetUnderflowTH((((MVD_BITSTREAM_LEN_EX*15)/16)>>3)<<3);
            MDrv_MVD_SetOverflowTH(((MVD_BITSTREAM_LEN_EX-0x400)>>3)<<3);
            MDrv_MVD_SetCodecInfo(E_MVD_CODEC_MPEG2, E_MVD_TS_FILE_MODE, ENABLE_PARSER);
            #endif
            #endif
            #ifdef PVR_UTOPIA
            //PARDAI VERSION {  }
            #else
            msAPI_VID_DropErrorFrame(TRUE);
            #endif
            msAPI_VID_SetTrickModeInfo(0, 1); /// Normal play
        }
    }
}

/***************************************************************************************/
void msAPI_Player_VideoStop(void)
{
    #ifndef S3PLUS
    msAPI_VID_Command(MSAPI_VID_STOP);
    #else
    msAPI_VID_Command(MSAPI_VID_RESET);
    #endif
}

/***************************************************************************************/
void msAPI_Player_VideoReset(enPlaySource enSource)
{
    MApp_VID_VariableInit();
    msAPI_VID_Command(MSAPI_VID_RESET);

    #ifndef S3PLUS
    #ifdef PVR_UTOPIA
    if(msAPI_VID_GetCodecType() == E_VDEC_CODEC_TYPE_H264)
    #else
    if (bAVCH264)
    #endif
    {
        if(enSource == E_PLAY_SOURCE_LIVE)
        {
            #ifdef PVR_UTOPIA
            //PARDAI VERSION {  }
            #else
            msAPI_VID_AVCH264EnableParserStop(0);
            #endif
        }
        else
        {
            #ifdef PVR_UTOPIA
            //PARDAI VERSION {  }
            #else
            msAPI_VID_AVCH264EnableParserStop(1);
            #endif
        }
    }
    else
    #endif
    {
        if(enSource == E_PLAY_SOURCE_LIVE)
        {
            #ifdef PVR_8051
            #ifndef S3PLUS
            MDrv_Mvd_SetCodecInfo(CODEC_MPEG2, TS_MODE     , ENABLE_PARSER);
            #else
            MDrv_Mvd_SetPlayMode(FALSE, FALSE);
            #endif
            #else
            #ifdef PVR_UTOPIA
            //PARDAI VERSION {  }
            #else
            MDrv_MVD_SetCodecInfo(E_MVD_CODEC_MPEG2, E_MVD_TS_MODE, ENABLE_PARSER);
            #endif
            #endif
        }
        else
        {
            #ifdef PVR_8051
            MDrv_Mvd_SetUnderflowTH((((MVD_BITSTREAM_LEN_EX*15)/16)>>3)<<3);
            MDrv_Mvd_SetOverflowTH(((MVD_BITSTREAM_LEN_EX-0x400)>>3)<<3);
            #ifndef S3PLUS
            MDrv_Mvd_SetCodecInfo(CODEC_MPEG2, TS_FILE_MODE, ENABLE_PARSER);
            #else
            MDrv_Mvd_SetPlayMode(TRUE, FALSE);
            #endif
            #else
            #ifdef PVR_UTOPIA
            //PARDAI VERSION {  }
            #else
            MDrv_MVD_SetUnderflowTH((((MVD_BITSTREAM_LEN_EX*15)/16)>>3)<<3);
            MDrv_MVD_SetOverflowTH(((MVD_BITSTREAM_LEN_EX-0x400)>>3)<<3);
            #endif
            #ifdef PVR_UTOPIA
            //PARDAI VERSION {  }
            #else
            MDrv_MVD_SetCodecInfo(E_MVD_CODEC_MPEG2, E_MVD_TS_FILE_MODE, ENABLE_PARSER);
            #endif
            #endif
            #ifdef PVR_UTOPIA
            //PARDAI VERSION {  }
            #else
            msAPI_VID_DropErrorFrame(FALSE);
            #endif
        }
    }
    msAPI_VID_SetTrickModeInfo(0, 1); /// Normal play
}

/***************************************************************************************/
void msAPI_Player_VideoPlay(enPlayMode enMode)
{
    if(enMode == E_PLAY_MODE_NORMAL)
    {
        msAPI_VID_Command(MSAPI_VID_PLAY);
    }
    else
    {
        msAPI_VID_Command(MSAPI_VID_TRICK_PLAY);
    }
}

/***************************************************************************************/
void msAPI_Player_VideoPause(void)
{
    #ifdef PVR_8051
    #ifndef S3PLUS
    msAPI_VID_Command(MSAPI_VID_FILE_MODE_PAUSE);
    #else
    msAPI_VID_Command(MSAPI_VID_PAUSE);
    #endif
    #else
    msAPI_VID_Command(MSAPI_VID_PAUSE);
    #endif
}

/***************************************************************************************/
void msAPI_Player_VideoResume(void)
{
    #ifndef S3PLUS
    msAPI_VID_Command(MSAPI_VID_RESUME);
    #else
    msAPI_VID_Command(MSAPI_VID_PLAY);
    #endif
}

/***************************************************************************************/
void msAPI_Player_VideoRestore(void)
{
    #ifndef S3PLUS
    #ifdef PVR_UTOPIA
    if(g_eCurrent_PVR_VideoType == E_VDEC_CODEC_TYPE_H264)
    #else
    if(g_bCurrent_PVR_AVCH264)
    #endif
    {
        msAPI_Player_VideoInit(E_PLAY_VIDEO_TYPE_H264,  E_PLAY_SOURCE_LIVE);
    }
    else if(g_eCurrent_PVR_VideoType == E_VDEC_CODEC_TYPE_AVS)
    {
        msAPI_Player_VideoInit(E_PLAY_VIDEO_TYPE_AVS,  E_PLAY_SOURCE_LIVE);
    }
    #if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)    \
        ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)  \
        ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)    \
        ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA))
    else if(g_eCurrent_PVR_VideoType == E_VDEC_CODEC_TYPE_HEVC)
    {
        msAPI_Player_VideoInit(E_PLAY_VIDEO_TYPE_HEVC,  E_PLAY_SOURCE_LIVE);
    }
    #endif
    else
    #endif
    {
        msAPI_Player_VideoInit(E_PLAY_VIDEO_TYPE_MPEG2, E_PLAY_SOURCE_LIVE);
    }
}

/***************************************************************************************/
enPlayVideoType msAPI_Player_VideoGetType(void)
{
    #ifndef S3PLUS
    #ifdef PVR_UTOPIA
    if(msAPI_VID_GetCodecType() == E_VDEC_CODEC_TYPE_H264)
    #else
    if(bAVCH264)
    #endif
    {
        return E_PLAY_VIDEO_TYPE_H264;
    }
    else if(msAPI_VID_GetCodecType() == E_VDEC_CODEC_TYPE_AVS)
    {
        return E_PLAY_VIDEO_TYPE_AVS;
    }
    #if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)    \
        ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)  \
        ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)    \
        ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA))
    else if(msAPI_VID_GetCodecType() == E_VDEC_CODEC_TYPE_HEVC)
    {
        return E_PLAY_VIDEO_TYPE_HEVC;
    }
    #endif
    else
    #endif
    {
        return E_PLAY_VIDEO_TYPE_MPEG2;
    }
}

/***************************************************************************************/
#ifndef PVR_UTOPIA
static BOOLEAN msAPI_Player_VideoGetInfo(MMSAPI_VID_STATUS *pstVidStatus )
{
    #ifndef S3PLUS
    if (bAVCH264)
    {
        return msAPI_VID_AVCH264GetSeqInfo(pstVidStatus);
    }
    else
    #endif
    {
        return msAPI_VID_GetVidInfo(pstVidStatus);
    }
}
#endif
/***************************************************************************************/

/*###############################################################################################*/
/*/////////////////////////////////// video advanced control ////////////////////////////////////*/
/*###############################################################################################*/

/***************************************************************************************/
enPlaySpeed _enForwardSpeed  = E_PLAY_SPEED_1X;
enPlaySpeed _enBackwardSpeed = E_PLAY_SPEED_1X;
enPlaySpeed _enSlowForwardSpeed  = E_PLAY_SPEED_1X;

/***************************************************************************************/
U32 msAPI_Player_VideoGetPicCount(void)
{
    #ifdef PVR_UTOPIA
    return MApi_VDEC_GetFrameCnt();
    #else
    return msAPI_VID_GetPicCount();
    #endif
}

/***************************************************************************************/
void msAPI_Player_VideoMonitor(BOOLEAN bReCalculate)
{
    if(bReCalculate == FALSE)
    {
        /// Check Speed_1x mode to get GOP info.
        if(m_u32GOPTimes < 1000)
        {
            /// Get GOP count frmo API.
            #ifdef PVR_UTOPIA
            #else
            U32 u32GOPSize;
            /// Get GOP count frmo API.
            u32GOPSize = msAPI_VID_GetGOPCount();
            //printf("msAPI_Player_VideoGetGOPInfo: Get new GOP info frames = %lu.\n",u32GOPSize);

            /// Recall the GOP info.
            if(u32GOPSize > 9 && u32GOPSize < 60 )
            {
                m_u32GOPtotal += u32GOPSize;
                m_u32GOPTimes++;
                m_u32GOPSize = m_u32GOPtotal/m_u32GOPTimes;

                if(m_u32GOPSize<4)
                    m_u32GOPSize= 4;
            }
            #endif
        }
        //printf("_MApp_TS_GOPInfo: Ave GOP info frames = %lu.\n",m_u32GOPSize);
    }
    else    /// bflag = FALSE, reset data.
    {
        m_u32GOPtotal = 0;
        m_u32GOPSize = 16;  /// The default number
        m_u32GOPTimes = 0;  /// Reset to zero
    }
}

/***************************************************************************************/
static BOOLEAN msAPI_Player_VideoCheckInterlace(U8 *u8Interlace)
{
    #ifdef PVR_UTOPIA
    VDEC_DispInfo stVidInfo;
    memset(&stVidInfo, 0, sizeof(stVidInfo));
    #else
    MMSAPI_VID_STATUS stVidInfo;
    #endif

    #ifndef S3PLUS
    #ifdef PVR_UTOPIA
    if(msAPI_VID_GetCodecType() == E_VDEC_CODEC_TYPE_H264)
    #else
    if(bAVCH264)
    #endif
    {
        #ifdef PVR_UTOPIA
        //PARDAI VERSION {  }
        #else
        if( msAPI_VID_AVCH264GetDispRdy() )
        #endif
        {
            #ifdef PVR_UTOPIA
            //PARDAI VERSION {  }
            #else
            if(msAPI_VID_AVCH264GetSeqInfo(&stVidInfo))
            #endif
            {

                //printf("H.264 Video Resolution: HxV %ux%u, Frame rate: %u\n", stVidInfo.u16HorSize, stVidInfo.u16VerSize, stVidInfo.u16FrameRate);
                if ((stVidInfo.u16HorSize == 0) || (stVidInfo.u16VerSize == 0) ||
                    (stVidInfo.u16HorSize > 2048) || (stVidInfo.u16VerSize > 2048))
                {
                    return FALSE;
                }

                if (stVidInfo.u8Interlace == 1)
                {
                    *u8Interlace = 1; // Interlace
                    #ifdef PVR_UTOPIA
                    //PARDAI VERSION {  }
                    #else
                    g_u8CurrentSyncStatus |= MD_INTERLACE_BIT;
                    #endif
                }
                else
                {
                    *u8Interlace= 0; // Progressive
                    #ifdef PVR_UTOPIA
                    //PARDAI VERSION {  }
                    #else
                    g_u8CurrentSyncStatus &= ~MD_INTERLACE_BIT;
                    #endif
                }

                return TRUE;
            }

            return FALSE;
        }

        return FALSE;
    }
    else
    #else
    *u8Interlace = *u8Interlace;
    #endif

    #ifdef PVR_UTOPIA
    if(1)
    #else
    if(msAPI_VID_GetDispRdy())
    #endif
    {
        //printf(" msAPI_VID_GetDispRdy()==1\n");
        if(msAPI_VID_GetVidInfo(&stVidInfo))
        {
            //printf("MPEG-2 Video Resolution: HxV %ux%u, Frame rate: %u\n", stVidInfo.u16HorSize, stVidInfo.u16VerSize, stVidInfo.u16FrameRate);
            if ((stVidInfo.u16HorSize == 0) || (stVidInfo.u16VerSize == 0) ||
                (stVidInfo.u16HorSize > 2048) || (stVidInfo.u16VerSize > 2048) )
            {
                return FALSE;
            }

            if (stVidInfo.u8Interlace == 1)
            {
                #ifdef PVR_UTOPIA
                //PARDAI VERSION {  }
                #else
                g_u8CurrentSyncStatus |= MD_INTERLACE_BIT;
                #endif
            }
            else
            {
                #ifdef PVR_UTOPIA
                //PARDAI VERSION {  }
                #else
                g_u8CurrentSyncStatus &= ~MD_INTERLACE_BIT;
                #endif
            }

            return TRUE;
        }

        return FALSE;
    }
    else
    {
        return FALSE;
    }
}

/***************************************************************************************/
void msAPI_Player_VideoConfigSlowForwardSpeed(enPlaySpeed enSpeed)
{
    U8 u8FrameDuration,u8DecodeType;
    U8 m_u8Interlace = 0;
  #ifdef PVR_UTOPIA
    VDEC_DispSpeed eDispSpeed = E_VDEC_DISP_SPEED_1X;
  #endif

    _enSlowForwardSpeed = enSpeed;

    switch (enSpeed)
    {
        case E_PLAY_SPEED_1X:
        {
            eDispSpeed = E_VDEC_DISP_SPEED_1X;
            u8FrameDuration = 1;
            break;
        }
        case E_PLAY_SPEED_2X:
        {
            eDispSpeed = E_VDEC_DISP_SPEED_2X;
            u8FrameDuration = 1;
            break;
        }
        case E_PLAY_SPEED_4X:
        {
            eDispSpeed = E_VDEC_DISP_SPEED_4X;
            u8FrameDuration = (U8)(m_u32GOPSize>>2);
            break;
        }
        case E_PLAY_SPEED_8X:
        {
            eDispSpeed   = E_VDEC_DISP_SPEED_8X;
            u8FrameDuration = (U8)(m_u32GOPSize>>2);
            break;
        }
        case E_PLAY_SPEED_16X:
        {
            eDispSpeed = E_VDEC_DISP_SPEED_16X;
            u8FrameDuration = (U8)(m_u32GOPSize>>2);
            break;
        }
        case E_PLAY_SPEED_32X:
        {
            eDispSpeed = E_VDEC_DISP_SPEED_32X;
            u8FrameDuration = (U8)(m_u32GOPSize>>2);
            break;
        }
        default:
        {
            eDispSpeed = E_VDEC_DISP_SPEED_2X;
            u8FrameDuration=1;
            break;
        }
    }

    u8DecodeType = E_VDEC_TRICK_DEC_ALL;
    #ifndef S3PLUS
    msAPI_VID_Command(MSAPI_VID_RESUME);
    #else
    msAPI_VID_Command(MSAPI_VID_PLAY);
    #endif
    /// if this stream was H264 and interlace mode, the duration would need to modify.
    msAPI_Player_VideoCheckInterlace(&m_u8Interlace);
    #ifndef S3PLUS
    #ifdef PVR_UTOPIA
    if((msAPI_VID_GetCodecType() == E_VDEC_CODEC_TYPE_H264) && m_u8Interlace)
    #else
    if(bAVCH264 && m_u8Interlace)
    #endif
        u8FrameDuration <<= 1;
    #endif
    #ifdef PVR_UTOPIA
    MApi_VDEC_SetTrickMode((VDEC_TrickDec)u8DecodeType);
    MApi_VDEC_SetSpeed(E_VDEC_SPEED_SLOW, eDispSpeed);
    #else
    msAPI_VID_SetTrickModeInfo(u8DecodeType, u8FrameDuration);
    msAPI_VID_Command(MSAPI_VID_TRICK_PLAY);
    #endif

    #if 0 //=======================================================================//
    printf("Forward Speed: %s, FrameDuration: %u [GOPSize %u]\n",(enSpeed == E_PLAY_SPEED_2X)?"2X":
                                 (enSpeed == E_PLAY_SPEED_4X)?"4X":
                                 (enSpeed == E_PLAY_SPEED_8X)?"8X":
                                 (enSpeed == E_PLAY_SPEED_16X)?"16X":
                                 (enSpeed == E_PLAY_SPEED_32X)?"32X":"Not support speed",
                                 u8FrameDuration, m_u32GOPSize);
    #endif //=======================================================================//

}

/***************************************************************************************/
enPlaySpeed msAPI_Player_VideoGetSlowForwardSpeed(void)
{
    return _enSlowForwardSpeed;
}

/***************************************************************************************/
void msAPI_Player_VideoConfigForwardSpeed(enPlaySpeed enSpeed)
{
    U8 u8FrameDuration,u8DecodeType;
    U8 m_u8Interlace = 0;
  #ifdef PVR_UTOPIA
    VDEC_DispSpeed eDispSpeed = E_VDEC_DISP_SPEED_1X;
  #endif

    DEBUG_API_PLAYER( printf("msAPI_Player_VideoConfigForwardSpeed(enSpeed=%u)\n", enSpeed); );

    _enForwardSpeed = enSpeed;

    /*##=======U_N_B_E_L_I_E_V_A_B_L_E=========##*/
#ifndef S3PLUS
  #ifdef PVR_UTOPIA
    //PARDAI VERSION {  }
  #else
    msAPI_VID_AVCH264EnableParserStop(1);
  #endif
#endif
    /*##=======_M_S_T_A_R_S_E_M_I_(C)_=========##*/

    switch (enSpeed)
    {
        case E_PLAY_SPEED_1X:
        {
        #ifdef PVR_UTOPIA
            u8DecodeType    = E_VDEC_TRICK_DEC_ALL;
            eDispSpeed = E_VDEC_DISP_SPEED_1X;
        #else
            u8DecodeType    = 0; //E_VDEC_TRICK_DEC_ALL
        #endif
            u8FrameDuration = 1;
            break;
        }
        case E_PLAY_SPEED_2X:
        {
            #if 0
            u8DecodeType    = 1;
            u8FrameDuration = (U8)(m_u32GOPSize>>1);
            #else
#ifndef S3PLUS
        #ifdef PVR_UTOPIA
            u8DecodeType    = E_VDEC_TRICK_DEC_ALL;
            eDispSpeed = E_VDEC_DISP_SPEED_2X;
        #else
            u8DecodeType    = 2;
        #endif
#else
            u8DecodeType    = 1;//2;//FastForward 2X (I/P)
#endif
            u8FrameDuration = 1;
            #endif
            break;
        }
        case E_PLAY_SPEED_4X:
        {
#ifndef S3PLUS
        #ifdef PVR_UTOPIA
            u8DecodeType    = E_VDEC_TRICK_DEC_ALL;
            eDispSpeed = E_VDEC_DISP_SPEED_4X;
        #else
            u8DecodeType    = 1;
        #endif
#else
            u8DecodeType    = 0;//FastForward 4X (I only)
#endif
            u8FrameDuration = (U8)(m_u32GOPSize>>2);
            break;
        }
        case E_PLAY_SPEED_8X:
        {
#ifndef S3PLUS
        #ifdef PVR_UTOPIA
            u8DecodeType = E_VDEC_TRICK_DEC_ALL;
            eDispSpeed   = E_VDEC_DISP_SPEED_8X;
        #else
            u8DecodeType    = 1;
        #endif
#else
            u8DecodeType    = 0;//FastForward 8X (I only)
#endif
            u8FrameDuration = (U8)(m_u32GOPSize>>2);
            break;
        }
        case E_PLAY_SPEED_16X:
        {
#ifndef S3PLUS
        #ifdef PVR_UTOPIA
            u8DecodeType    = E_VDEC_TRICK_DEC_ALL;
            eDispSpeed = E_VDEC_DISP_SPEED_16X;
        #else
            u8DecodeType    = 1;
        #endif
#else
            u8DecodeType = 0;//FastForward 16X (I only)
#endif
            u8FrameDuration = (U8)(m_u32GOPSize>>2);
            break;
        }
        case E_PLAY_SPEED_32X:
        {
        #ifdef PVR_UTOPIA
            u8DecodeType    = E_VDEC_TRICK_DEC_I;
            eDispSpeed = E_VDEC_DISP_SPEED_1X;
        #else
            u8DecodeType    = 1;
        #endif
            u8FrameDuration = (U8)(m_u32GOPSize>>2);
            break;
        }
        default:
        {
#ifndef S3PLUS
        #ifdef PVR_UTOPIA
            u8DecodeType    = E_VDEC_TRICK_DEC_IP;
            eDispSpeed = E_VDEC_DISP_SPEED_2X;
        #else
            u8DecodeType    = 2;
        #endif
#else
            u8DecodeType=1;
#endif
            u8FrameDuration=1;
            break;
        }
    }

    #ifndef S3PLUS
    msAPI_VID_Command(MSAPI_VID_RESUME);
    #else
    msAPI_VID_Command(MSAPI_VID_PLAY);
    #endif

    /// if this stream was H264 and interlace mode, the duration would need to modify.
    msAPI_Player_VideoCheckInterlace(&m_u8Interlace);

  #ifndef S3PLUS
    #ifdef PVR_UTOPIA
    if((msAPI_VID_GetCodecType() == E_VDEC_CODEC_TYPE_H264) && m_u8Interlace)
    #else
    if(bAVCH264 && m_u8Interlace)
    #endif
        u8FrameDuration <<= 1;
  #endif

  #ifdef PVR_UTOPIA

    DEBUG_API_PLAYER(printf("MApi_VDEC_SetTrickMode(u8DecodeType=%u)\n", u8DecodeType); );
    MApi_VDEC_SetTrickMode((VDEC_TrickDec)u8DecodeType);

    DEBUG_API_PLAYER(printf("MApi_VDEC_SetSpeed(eDispSpeed=%u)\n", eDispSpeed););

    if(eDispSpeed != E_VDEC_DISP_SPEED_1X)
        MApi_VDEC_SetSpeed(E_VDEC_SPEED_FAST, eDispSpeed);
    else
        MApi_VDEC_SetSpeed(E_VDEC_SPEED_DEFAULT, eDispSpeed);

  #else
    msAPI_VID_SetTrickModeInfo(u8DecodeType, u8FrameDuration);
    msAPI_VID_Command(MSAPI_VID_TRICK_PLAY);
  #endif

    #if 0 //=======================================================================//
    printf("Forward Speed: %s, FrameDuration: %u [GOPSize %u]\n",(enSpeed == E_PLAY_SPEED_2X)?"2X":
                                 (enSpeed == E_PLAY_SPEED_4X)?"4X":
                                 (enSpeed == E_PLAY_SPEED_8X)?"8X":
                                 (enSpeed == E_PLAY_SPEED_16X)?"16X":
                                 (enSpeed == E_PLAY_SPEED_32X)?"32X":"Not support speed",
                                 u8FrameDuration, m_u32GOPSize);
    #endif //=======================================================================//

}

/***************************************************************************************/
enPlaySpeed msAPI_Player_VideoGetForwardSpeed(void)
{
    return _enForwardSpeed;
}

/***************************************************************************************/
void msAPI_Player_VideoConfigBackwardSpeed(enPlaySpeed enSpeed)
{
    U8 u8FrameDuration;
    U8 m_u8Interlace = 0;
  #ifdef PVR_UTOPIA
    VDEC_DispSpeed eDispSpeed = E_VDEC_DISP_SPEED_1X;
  #endif

    DEBUG_API_PLAYER( printf("msAPI_Player_VideoConfigBackwardSpeed(enSpeed=%u)\n", enSpeed); );

    /*##=======U_N_B_E_L_I_E_V_A_B_L_E=========##*/
#ifndef S3PLUS
  #ifdef PVR_UTOPIA
    //PARDAI VERSION {  }
  #else
    msAPI_VID_AVCH264EnableParserStop(0);
  #endif
#endif
    /*##=======_M_S_T_A_R_S_E_M_I_(C)_=========##*/

    _enBackwardSpeed = enSpeed;

    switch (enSpeed)
    {
        case E_PLAY_SPEED_1X:
        {
            u8FrameDuration = 16;
        #ifdef PVR_UTOPIA
            eDispSpeed = E_VDEC_DISP_SPEED_1X;
        #endif
            break;
        }
        case E_PLAY_SPEED_2X:
        {
            u8FrameDuration = (U8)(m_u32GOPSize>>1);
        #ifdef PVR_UTOPIA
            eDispSpeed = E_VDEC_DISP_SPEED_2X;
        #endif
            break;
        }
        case E_PLAY_SPEED_4X:
        {
            u8FrameDuration = (U8)(m_u32GOPSize>>2);
        #ifdef PVR_UTOPIA
            eDispSpeed = E_VDEC_DISP_SPEED_4X;
        #endif
            break;
        }
        case E_PLAY_SPEED_8X:
        {
            u8FrameDuration = (U8)(m_u32GOPSize>>2);
        #ifdef PVR_UTOPIA
            eDispSpeed = E_VDEC_DISP_SPEED_8X;
        #endif
            break;
        }
        case E_PLAY_SPEED_16X:
        {
            u8FrameDuration = (U8)(m_u32GOPSize>>2);
        #ifdef PVR_UTOPIA
            eDispSpeed = E_VDEC_DISP_SPEED_16X;
        #endif
            break;
        }
        case E_PLAY_SPEED_32X:
        {
            u8FrameDuration = (U8)(m_u32GOPSize>>2);
        #ifdef PVR_UTOPIA
            eDispSpeed = E_VDEC_DISP_SPEED_32X;
        #endif
            break;
        }
        default:
        {
            u8FrameDuration = (U8)(m_u32GOPSize>>1);
        #ifdef PVR_UTOPIA
            eDispSpeed = E_VDEC_DISP_SPEED_1X;
        #endif
            break;
        }
    }

    /// if this stream was H264 and interlace mode, the duration would need to modify.
    msAPI_Player_VideoCheckInterlace(&m_u8Interlace);

    #ifndef S3PLUS
    #ifdef PVR_UTOPIA
    if((msAPI_VID_GetCodecType() == E_VDEC_CODEC_TYPE_H264) && m_u8Interlace)
    #else
    if(bAVCH264 && m_u8Interlace)
    #endif
        u8FrameDuration <<= 1;
    #endif

    #ifndef S3PLUS
    msAPI_VID_Command(MSAPI_VID_RESUME);
    #else
    msAPI_VID_Command(MSAPI_VID_PLAY);
    #endif

#ifdef PVR_UTOPIA

   // MApi_VDEC_SetTrickMode(E_VDEC_TRICK_DEC_I);
    //MApi_VDEC_SetSpeed(E_VDEC_SPEED_FAST, eDispSpeed);
#else

  #if 0//ndef S3PLUS
    #ifdef PVR_UTOPIA
    if(msAPI_VID_GetCodecType() == E_VDEC_CODEC_TYPE_H264)
    #else
    if(bAVCH264)
    #endif
    {
        msAPI_VID_SetTrickModeInfo(1, u8FrameDuration);

        /*##=======U_N_B_E_L_I_E_V_A_B_L_E=========##*/
        #ifdef PVR_8051
        MDrv_AVCH264_SetPicErrTH(1);
        #endif
        /*##=======_M_S_T_A_R_S_E_M_I_(C)_=========##*/
    }
    else
  #endif
    {
        /// Mark here, TS_FILE_MODE of MPEG2 parser had issue to let data error.
       #ifdef PVR_UTOPIA
        //PARDAI VERSION {  }
       #else
        msAPI_VID_DropErrorFrame(TRUE);
       #endif

    #ifndef S3PLUS
        msAPI_VID_SetTrickModeInfo(1, u8FrameDuration);
    #else
        msAPI_VID_SetTrickModeInfo(2, u8FrameDuration);
    #endif
    }

    msAPI_VID_Command(MSAPI_VID_TRICK_PLAY);

  #if (!defined(PVR_8051) && !defined(PVR_UTOPIA)) //Chakra1 only
    if (!bAVCH264){
        //enable decode order in MVD
        MDrv_MVD_DispCtrl(TRUE, FALSE, FALSE, E_MVD_FRC_NORMAL);
    }
  #endif
#endif

  #if 0 //=======================================================================//
    printf("Backward Speed: %s, FrameDuration: %u [GOPSize %u]\n",(enSpeed == E_PLAY_SPEED_2X)?"2X":
                                 (enSpeed == E_PLAY_SPEED_4X)?"4X":
                                 (enSpeed == E_PLAY_SPEED_8X)?"8X":
                                 (enSpeed == E_PLAY_SPEED_16X)?"16X":
                                 (enSpeed == E_PLAY_SPEED_32X)?"32X":"Not support speed",
                                 u8FrameDuration, m_u32GOPSize);
  #endif //=======================================================================//

}

/***************************************************************************************/
enPlaySpeed msAPI_Player_VideoGetBackwardSpeed(void)
{
    return _enBackwardSpeed;
}

/***************************************************************************************/
U8 msAPI_Player_VideoSearchIFrame(U32 u32BufStr, U32 u32BufLen, U16 u16VidPID, U32 u32IframeStart[], U32 u32IframeLength[], U8 u8MaxIFrameNum)
{
    #define VIDEO_HEADER_LEN    16
    #define SEQUENCE_START_CODE 0xB3010000
    #define PICTURE_START_CODE  0x00010000
    #define START_CODE_UNMASK   0x00000000
    #ifndef S3PLUS
    #define TS_PACKET_LEN       192  //PVR
    #define TS_PACKET_SEARCH_LEN    (TS_PACKET_LEN-8)
    #else
    #define TS_PACKET_LEN       188  //PVR
    #define TS_PACKET_SEARCH_LEN    (TS_PACKET_LEN)
    #endif
    /// H.264 Info.
    #define H264SYNTAX          0x01000000
    #define NAL_SPS             0x07
    #define NAL_PPS             0x08
    #define NAL_SLICE           0x01
    #define NAL_ACCESS_UNIT_DELIMITER   0x09

    #define VIDEO_PATTERN_UNMASK            0xFF00E000

    U32 u32VideoPattern, u32ReadPos, u32Addr, u32Len;
    #ifndef PVR_8051
    #ifndef PVR_UTOPIA
    U32 u32AddrResult;
    #endif
    #endif
    U32 u32StartPos = 0xFFFFFFFF, u32PacketPos = 0xFFFFFFFF;
    U8 u8Counter2 = 0, u8PicType = 0, u8BackwardTBCtr = 0;
    U8 u8Data[TS_PACKET_LEN];
    BOOLEAN bFoundSeq = FALSE;

    u32VideoPattern = ((U32)0x47) |
                      ((U32)LOBYTE(u16VidPID)<<16)|
                      ((U32)HIBYTE(u16VidPID)<<8);

    u32ReadPos = u32BufStr + u32BufLen;
    u32Addr = u32BufStr;

    #ifndef S3PLUS
    #ifdef PVR_UTOPIA
    if(msAPI_VID_GetCodecType() == E_VDEC_CODEC_TYPE_H264)
    #else
    if(bAVCH264)
    #endif
    {
        while(u32Addr != 0xFFFFFFFF)
        {
            u32Len = u32ReadPos - u32Addr;

            /// Fine SPS position within D-FIFO
            #ifdef PVR_8051
            u32Addr = MDrv_BDMA_Search(u32Addr,
                           u32Len,
                           H264SYNTAX,
                           START_CODE_UNMASK,
                           BDMACOPY_SRCMIU0 | BDMASEARCH_POLLING);
            #else
            #ifdef PVR_UTOPIA
            u32Addr = MDrv_BDMA_Search(u32Addr,
                           u32Len,
                           H264SYNTAX,
                           START_CODE_UNMASK,
                           E_BDMA_SRCDEV_MIU0);
            #else
            u32AddrResult = 0xFFFFFFFF;
            MDrv_BDMA_Search(u32Addr,
                           u32Len,
                           H264SYNTAX,
                           START_CODE_UNMASK,
                           &u32AddrResult,
                           BDMACOPY_SRCMIU0 | BDMASEARCH_POLLING);
            u32Addr = u32AddrResult;
            #endif
            #endif
            /// Check NAL Type, SPS nal type = 0x07
            if(u32Addr != 0xFFFFFFFF)
            {
            #ifdef PVR_UTOPIA
                msAPI_MIU_Copy(u32Addr, _VA2PA((U32)&u8Data[0]), VIDEO_HEADER_LEN, MIU_SDRAM2SDRAM);
            #else
                msAPI_MIU_Copy(u32Addr, XD2PHY(&u8Data[0]), VIDEO_HEADER_LEN, MIU_SDRAM2SDRAM);
            #endif


                //u8PicType = (u8Data[4]&0x1F);
                /// Check NAL type
                if( (u8Data[4]&0x1F) == NAL_SPS)
                {
                    /// Check video PID if play program or not.
                    #ifdef PVR_8051
                    u32PacketPos = MDrv_BDMA_Search(u32Addr - TS_PACKET_SEARCH_LEN,
                                                   TS_PACKET_SEARCH_LEN,
                                                   u32VideoPattern,
                                                   VIDEO_PATTERN_UNMASK,
                                                   BDMACOPY_SRCMIU0 | BDMASEARCH_POLLING);
                    #else
                    #ifdef PVR_UTOPIA
                    u32PacketPos = MDrv_BDMA_Search(u32Addr - TS_PACKET_SEARCH_LEN,
                                                   TS_PACKET_SEARCH_LEN,
                                                   u32VideoPattern,
                                                   VIDEO_PATTERN_UNMASK,
                                                   E_BDMA_SRCDEV_MIU0);
                    #else
                    u32PacketPos = 0xFFFFFFFF;
                    MDrv_BDMA_Search(u32Addr - TS_PACKET_SEARCH_LEN,
                                                   TS_PACKET_SEARCH_LEN,
                                                   u32VideoPattern,
                                                   VIDEO_PATTERN_UNMASK,
                                                   &u32PacketPos,
                                                   BDMACOPY_SRCMIU0 | BDMASEARCH_POLLING);
                    #endif
                    #endif

                    if(u32PacketPos != 0xFFFFFFFF)
                    {
                        /// Recall position of start packet.
                        u32StartPos = u32PacketPos;
                        bFoundSeq = TRUE;
                        //printf("BDMA Search =%lx, Found SPS.\n", u32StartPos);
                    }
                }
            }

            /// If found the SPS then find I-frame.
            while(u32Addr != 0xFFFFFFFF && bFoundSeq && (u8Counter2 < 1/*2*/) ) /// Slice change to access unit delimiter
            {
                u32Addr++;
                u32Len = u32ReadPos - u32Addr;
                /// Fine slice header (or NAL)
                #ifdef PVR_8051
                u32Addr = MDrv_BDMA_Search(u32Addr,
                               u32Len,
                               H264SYNTAX,
                               START_CODE_UNMASK,
                               BDMACOPY_SRCMIU0 | BDMASEARCH_POLLING);
                #else
                #ifdef PVR_UTOPIA
                u32Addr = MDrv_BDMA_Search(u32Addr,
                               u32Len,
                               H264SYNTAX,
                               START_CODE_UNMASK,
                               E_BDMA_SRCDEV_MIU0);
                #else
                u32AddrResult = 0xFFFFFFFF;
                MDrv_BDMA_Search(u32Addr,
                               u32Len,
                               H264SYNTAX,
                               START_CODE_UNMASK,
                               &u32AddrResult,
                               BDMACOPY_SRCMIU0 | BDMASEARCH_POLLING);
                u32Addr = u32AddrResult;
                #endif
                #endif

                if( (u32Addr != 0xFFFFFFFF) )
                {
                    /// chech NAL_SLICE header
                #ifdef PVR_UTOPIA
                    msAPI_MIU_Copy(u32Addr, _VA2PA((U32)&u8Data[0]), VIDEO_HEADER_LEN, MIU_SDRAM2SDRAM);
                #else
                    msAPI_MIU_Copy(u32Addr, XD2PHY(&u8Data[0]), VIDEO_HEADER_LEN, MIU_SDRAM2SDRAM);
                #endif

                    /// If need to decide the frame, the would decode VLC or CAVLC.
                    /// This function was not implement.
                    if( (u8Data[4]&0x1F) == NAL_ACCESS_UNIT_DELIMITER /*NAL_SLICE*/)    /// Slice change to access unit delimiter
                    {
                        /// Check video PID if play program or not.
                        #ifdef PVR_8051
                        u32PacketPos = MDrv_BDMA_Search(u32Addr - TS_PACKET_SEARCH_LEN,
                                       TS_PACKET_SEARCH_LEN,
                                       u32VideoPattern,
                                       VIDEO_PATTERN_UNMASK,
                                       BDMACOPY_SRCMIU0 | BDMASEARCH_POLLING);
                        #else
                        #ifdef PVR_UTOPIA
                        u32PacketPos = MDrv_BDMA_Search(u32Addr - TS_PACKET_SEARCH_LEN,
                                       TS_PACKET_SEARCH_LEN,
                                       u32VideoPattern,
                                       VIDEO_PATTERN_UNMASK,
                                       E_BDMA_SRCDEV_MIU0);
                        #else
                        u32PacketPos = 0xFFFFFFFF;
                        MDrv_BDMA_Search(u32Addr - TS_PACKET_SEARCH_LEN,
                                       TS_PACKET_SEARCH_LEN,
                                       u32VideoPattern,
                                       VIDEO_PATTERN_UNMASK,
                                       &u32PacketPos,
                                       BDMACOPY_SRCMIU0 | BDMASEARCH_POLLING);
                        #endif
                        #endif
                        if(u32PacketPos != 0xFFFFFFFF)
                        {
                            //printf("BDMA Search =%lx, Found Slice.\n", u32PacketPos);
                            u8Counter2++;

                            /// Set PtrTB to recall the slice header pointer.
                            if(u8Counter2 == 1/*2*/)  /// Slice change to access unit delimiter
                            {
                                bFoundSeq = FALSE;
                                //printf("Found two slice, Set CmdQ Pos:%lx, len:%lx.\n",u32StartPos,(u32PacketPos - u32StartPos));
                                /// Recall frame information into backward table.
                                /// The NAL_ACCESS_UNIT_DELIMITER nal would be included. The decoder need it to decoder better for backward.
                                if(u8BackwardTBCtr < u8MaxIFrameNum)
                                {

                                U8 len;
                                for (len = 0;len<TS_PACKET_LEN;len++)
                                    u8Data[len] = 0;
                                if (TS_PACKET_LEN == 188)
                                    len = TS_PACKET_LEN - (u32Addr - u32PacketPos);
                                else
                                    len = TS_PACKET_LEN - (u32Addr - u32PacketPos+4);

                                #ifdef PVR_UTOPIA
                                    msAPI_MIU_Copy(_VA2PA((U32)&u8Data[0]), u32Addr, len, MIU_SDRAM2SDRAM);
                                #else
                                    msAPI_MIU_Copy( XD2PHY(&u8Data[0]),u32Addr, len, MIU_SDRAM2SDRAM);
                                #endif

                                    #if (TS_PACKET_LEN == 192)
                                    u32IframeStart[u8BackwardTBCtr] = u32StartPos - TS_PACKET_LEN - 4;
                                    #else
                                    u32IframeStart[u8BackwardTBCtr] = u32StartPos - TS_PACKET_LEN;
                                    #endif
                                    u32IframeLength[u8BackwardTBCtr] = u32PacketPos - u32StartPos + TS_PACKET_LEN*2;
                                    //printf("Found two slice, Set CmdQ Pos:%lx, len:%lx.\n",u32IframeStart[u8BackwardTBCtr],u32IframeLength[u8BackwardTBCtr]);
                                    u8BackwardTBCtr++;
                                }
                            }
                        }
                    }
                }
            }

            /// Setting to find next SPS.
            if((u32Addr != 0xFFFFFFFF) )
            {
                u8Counter2 = 0;
                u32Addr++;
            }

        }
    }
    else
    #endif
    {
        while((u32Addr != 0xFFFFFFFF))
        {
            u32Len = u32ReadPos - u32Addr;
            /// Find the Sequence header position within D-FIFO.
            #ifdef PVR_8051
            #ifndef S3PLUS
            u32Addr = MDrv_BDMA_Search(u32Addr,
                                       u32Len,
                                       SEQUENCE_START_CODE,
                                       START_CODE_UNMASK,
                                       BDMACOPY_SRCMIU0 | BDMASEARCH_POLLING);
            #else
            u32Addr = msAPI_Player_AeonPatternSearch(u32Addr,
                                                     u32Len,
                                                     SEQUENCE_START_CODE,
                                                     START_CODE_UNMASK);
            #endif
            #else
            #ifdef PVR_UTOPIA
            u32Addr = MDrv_BDMA_Search(u32Addr,
                                       u32Len,
                                       SEQUENCE_START_CODE,
                                       START_CODE_UNMASK,
                                       E_BDMA_SRCDEV_MIU0);
            #else
            u32AddrResult = 0xFFFFFFFF;
            MDrv_BDMA_Search(u32Addr,
                                       u32Len,
                                       SEQUENCE_START_CODE,
                                       START_CODE_UNMASK,
                                       &u32AddrResult,
                                       BDMACOPY_SRCMIU0 | BDMASEARCH_POLLING);
            u32Addr = u32AddrResult;
            #endif
            #endif
            /// Check video PID if play program or not.
            if(u32Addr != 0xFFFFFFFF)
            {
                #ifdef PVR_8051
                #ifndef S3PLUS
                u32PacketPos = MDrv_BDMA_Search(u32Addr - TS_PACKET_SEARCH_LEN,
                                               TS_PACKET_SEARCH_LEN,
                                               u32VideoPattern,
                                               VIDEO_PATTERN_UNMASK,
                                               BDMACOPY_SRCMIU0 | BDMASEARCH_POLLING);
                #else
                u32PacketPos = msAPI_Player_AeonPatternSearch(u32Addr - TS_PACKET_LEN,
                                                              TS_PACKET_LEN,
                                                              u32VideoPattern,
                                                              VIDEO_PATTERN_UNMASK);
                #endif
                #else
                #ifdef PVR_UTOPIA
                u32PacketPos = MDrv_BDMA_Search(u32Addr - TS_PACKET_SEARCH_LEN,
                                               TS_PACKET_SEARCH_LEN,
                                               u32VideoPattern,
                                               VIDEO_PATTERN_UNMASK,
                                               E_BDMA_SRCDEV_MIU0);
                #else
                u32PacketPos = 0xFFFFFFFF;
                MDrv_BDMA_Search(u32Addr - TS_PACKET_SEARCH_LEN,
                                               TS_PACKET_SEARCH_LEN,
                                               u32VideoPattern,
                                               VIDEO_PATTERN_UNMASK,
                                               &u32PacketPos,
                                               BDMACOPY_SRCMIU0 | BDMASEARCH_POLLING);
                #endif
                #endif
                /// Record Start Packet Position
                if(u32PacketPos != 0xFFFFFFFF)
                {
                    u32StartPos = u32PacketPos;
                    bFoundSeq = TRUE;
                    u8Counter2 = 0; /// When found sequence header to reset frame counter.
                    //printf("BDMA Search =%lx, Found header = 0xB3.\n", u32StartPos);
                }
            }

            /// Find picture start code when found sequence start code.
            /// Find two picture, 1st one would be I-frame that could know start position;
            /// 2rd one would be IPB-frame that could know end position.
            while((u32Addr != 0xFFFFFFFF) && (u8Counter2 < 2) && bFoundSeq )
            {
                u32Len = u32ReadPos - u32Addr;
                /// Find Picture start code position within D-FIFO.
                #ifdef PVR_8051
                #ifndef S3PLUS
                u32Addr = MDrv_BDMA_Search(u32Addr,
                                           u32Len,
                                           PICTURE_START_CODE,
                                           START_CODE_UNMASK,
                                           BDMACOPY_SRCMIU0 | BDMASEARCH_POLLING);
                #else
                u32Addr = msAPI_Player_AeonPatternSearch(u32Addr,
                                                         u32Len,
                                                         PICTURE_START_CODE,
                                                         START_CODE_UNMASK);
                #endif
                #else
                #ifdef PVR_UTOPIA
                u32Addr = MDrv_BDMA_Search(u32Addr,
                                           u32Len,
                                           PICTURE_START_CODE,
                                           START_CODE_UNMASK,
                                           E_BDMA_SRCDEV_MIU0);
                #else
                u32AddrResult = 0xFFFFFFFF;
                MDrv_BDMA_Search(u32Addr,
                                           u32Len,
                                           PICTURE_START_CODE,
                                           START_CODE_UNMASK,
                                           &u32AddrResult,
                                           BDMACOPY_SRCMIU0 | BDMASEARCH_POLLING);
                u32Addr = u32AddrResult;
                #endif
                #endif
                /// Check video PID if play program or not.
                if(u32Addr != 0xFFFFFFFF)
                {
                    #ifdef PVR_8051
                    #ifndef S3PLUS
                    u32PacketPos = MDrv_BDMA_Search(u32Addr - TS_PACKET_SEARCH_LEN,
                                                   TS_PACKET_SEARCH_LEN,
                                                   u32VideoPattern,
                                                   VIDEO_PATTERN_UNMASK,
                                                   BDMACOPY_SRCMIU0 | BDMASEARCH_POLLING);
                    #else
                    u32PacketPos = msAPI_Player_AeonPatternSearch(u32Addr - TS_PACKET_SEARCH_LEN,
                                                                 TS_PACKET_SEARCH_LEN,
                                                                 u32VideoPattern,
                                                                 VIDEO_PATTERN_UNMASK);
                    #endif
                    #else
                    #ifdef PVR_UTOPIA
                    u32PacketPos = MDrv_BDMA_Search(u32Addr - TS_PACKET_SEARCH_LEN,
                                                   TS_PACKET_SEARCH_LEN,
                                                   u32VideoPattern,
                                                   VIDEO_PATTERN_UNMASK,
                                                   E_BDMA_SRCDEV_MIU0);
                    #else
                    u32PacketPos = 0xFFFFFFFF;
                    MDrv_BDMA_Search(u32Addr - TS_PACKET_SEARCH_LEN,
                                                   TS_PACKET_SEARCH_LEN,
                                                   u32VideoPattern,
                                                   VIDEO_PATTERN_UNMASK,
                                                   &u32PacketPos,
                                                   BDMACOPY_SRCMIU0 | BDMASEARCH_POLLING);
                    #endif
                    #endif

                    /// Check picture type and record information.
                    if(u32PacketPos != 0xFFFFFFFF)
                    {
                    #ifdef PVR_UTOPIA
                        msAPI_MIU_Copy(u32Addr, _VA2PA((U32)&u8Data[0]), VIDEO_HEADER_LEN, MIU_SDRAM2SDRAM);
                    #else
                        msAPI_MIU_Copy(u32Addr, XD2PHY(&u8Data[0]), VIDEO_HEADER_LEN, MIU_SDRAM2SDRAM);
                    #endif
                        u8PicType = ((u8Data[5]>>3)&0x07);
                        //printf("BDMA Search =%lx, Found header = 0x00, Type = %u.\n", u32Addr,u8PicType);
                        if(u8Counter2 == 0 && u8PicType == 1)
                        {
                            //printf("Found I-frame position.\n");
                            u8Counter2++;
                        }
                        else
                        {
                            if( u8Counter2 == 1 && u8PicType > 0 && u8PicType < 4)
                            {
                                //printf("Found 2rd frame position.\n");
                                /// I-frame = b001, P-frame = b010, B-frame = b011;
                                u8Counter2++;
                            }
                        }
                        if(u8Counter2 == 2)
                        {
                            bFoundSeq = FALSE;
                            //printf("Found two picture, Set CmdQ Pos:%lx, len:%lx.\n",u32StartPos,(u32PacketPos - u32StartPos));
                            /// Recall frame information into backward table.
                            //msAPI_DMX_TSPlayback(u32StartPos - PLAYBACK_TIMESTAMP_LENGTH, u32PacketPos - u32StartPos + TS_PACKET_LEN + PLAYBACK_TIMESTAMP_LENGTH);
                            if(u8BackwardTBCtr < u8MaxIFrameNum)
                            {
                            //#ifdef PVR_UTOPIA
                            //    u32IframeStart[u8BackwardTBCtr] = _PA2VA(u32StartPos - TS_PACKET_LEN);
                            //#else
                            {
                                U8 len;
                                for (len = 0;len<TS_PACKET_LEN;len++)
                                    u8Data[len] = 0;
                                if (TS_PACKET_LEN == 188)
                                    len = TS_PACKET_LEN - (u32Addr - u32PacketPos);
                                else
                                    len = TS_PACKET_LEN - (u32Addr - u32PacketPos+4);

                                #ifdef PVR_UTOPIA
                                    msAPI_MIU_Copy(_VA2PA((U32)&u8Data[0]), u32Addr, len, MIU_SDRAM2SDRAM);
                                #else
                                    msAPI_MIU_Copy( XD2PHY(&u8Data[0]),u32Addr, len, MIU_SDRAM2SDRAM);
                                #endif
                            }

                                #if (TS_PACKET_LEN == 192)
                                u32IframeStart[u8BackwardTBCtr] = u32StartPos - TS_PACKET_LEN - 4;
                                #else
                                u32IframeStart[u8BackwardTBCtr] = u32StartPos - TS_PACKET_LEN;
                                #endif
                                u32IframeLength[u8BackwardTBCtr] = u32PacketPos - u32StartPos + TS_PACKET_LEN*2;
                                //printf("Found two slice, Set CmdQ Pos:%lx, len:%lx.\n",u32IframeStart[u8BackwardTBCtr],u32IframeLength[u8BackwardTBCtr]);
                                u8BackwardTBCtr++;
                            }
                        }
                    }

                    u32Addr++;
                }

            }

            /// Setting to find next sequence header.
            if((u32Addr != 0xFFFFFFFF) /*&& (u8Counter2 == 2)*/)
            {
                u8Counter2 = 0;
                u32Addr++;
            }
        }
    }

    return u8BackwardTBCtr;
}

/***************************************************************************************/

/*###############################################################################################*/
/*//////////////////////////////////// AEON pattern search //////////////////////////////////////*/
/*###############################################################################################*/

#ifdef S3PLUS
/***************************************************************************************/
#include <string.h>
#include "drvCPU.h"

// Data operation
    #define GetByte3(x)     (((x)&0xff000000)>>24)
    #define GetByte2(x)     (((x)&0x00ff0000)>>16)
    #define GetByte1(x)     (((x)&0x0000ff00)>> 8)
    #define GetByte0(x)     (((x)&0x000000ff)>> 0)

// Macros define
    #define MB_TS_SEARCH_TEST       0x01
    #define MB_TS_SEARCH_TEST_ACK   0x02
    #define MB_TS_SEARCH_FIND       0x10
    #define MB_TS_SEARCH_FIND_ACK   0x11
    #define MB_TS_SEARCH_INIT       0x12
    #define MB_TS_SEARCH_INIT_ACK   0x13

// Stucture
    typedef enum
    {
        E_SHAREMEM_STARTADDR,   //4 bytes
        E_SHAREMEM_LENGTH,      //4 bytes
        E_SHAREMEM_PATTERN,     //4 bytes
        E_SHAREMEM_UNMASK,      //4 bytes
        E_SHAREMEM_PKTLEN,      //4 byte
        E_SHAREMEM_RETADDR,     //4 bytes
    }enumShareMemory;

static U8 _pu8ShareMemory[27];  //24+3 for alignment
static U32 _u32ShareMemoryAddress;
static U8  _u8ShareMemoryOffset;
/***************************************************************************************/
void msAPI_Player_AeonPatternSearchInit(void)
{
    U32 u32Time1, u32Time2;

    MDrv_Aeon_Enable();
    MDrv_InitMailBoxQueue();

    // Send init message
    _u32ShareMemoryAddress = msAPI_MIU_XData2SDRAMAddr((U16)_pu8ShareMemory);
    _u8ShareMemoryOffset   = 4-_u32ShareMemoryAddress%4;
    _u32ShareMemoryAddress = _u32ShareMemoryAddress+_u8ShareMemoryOffset;
  //printf("_u32ShareMemoryAddress = 0x%08lx \n", _u32ShareMemoryAddress);

  //XBYTE[0x1EAA] = 0xC; // Uart switch to AEON

    if (MDrv_WaitMailBoxReady())
    {
        memset((U8 *)&MailBoxPara, 0x00, sizeof(MailBoxPara));
        MailBoxPara.u8CmdClass  = MB_CLASS_TS_SEARCH;
        MailBoxPara.u8CmdIdx    = MB_TS_SEARCH_INIT;
        MailBoxPara.ParamCnt    = 4;

        MailBoxPara.CMDType     = MB_CMD_TYPE_DEFAULT;

        MailBoxPara.u8Param[0]  = (U8)GetByte0(_u32ShareMemoryAddress);
        MailBoxPara.u8Param[1]  = (U8)GetByte1(_u32ShareMemoryAddress);
        MailBoxPara.u8Param[2]  = (U8)GetByte2(_u32ShareMemoryAddress);
        MailBoxPara.u8Param[3]  = (U8)GetByte3(_u32ShareMemoryAddress);

        MDrv_SendMailBoxMsg();
    }

    // Receive init ACK message
    u32Time1 = msAPI_Timer_GetTime0();
    while(1)
    {
        msAPI_Timer_Delayms(10);

        memset((U8 *)&MailBoxPara, 0x00, sizeof(MailBoxPara));
        if (MDrv_GetMailBoxMsg(Q_STATE, (U8*)&MailBoxPara) == MB_GET_MSG_OK)
        {
            MailBox *pMB;
            pMB = (MailBox*)&MailBoxPara;

            if ((pMB->u8CmdClass == MB_CLASS_TS_SEARCH) &&
                (pMB->u8CmdIdx   == MB_TS_SEARCH_INIT_ACK) )
            {
              //printf("Got ack from AEON\n");
            }
            else
            {
                U8 * pu8ParaArray = (U8 *)&MailBoxPara;
                U8 u8ByteNo;
                for(u8ByteNo=0; u8ByteNo<24; u8ByteNo++)
                    printf("%02bx ", pu8ParaArray[u8ByteNo]);
                printf("\n");
            }
            break;
        }
        else
        {
            u32Time2 = msAPI_Timer_GetTime0();
            if((u32Time2-u32Time1)>=100)
            {
                printf("AEON mailbox timeout\n");
                break;
            }
          //printf("Wait ack from AEON\n");
        }
    }

  //XBYTE[0x1EAA] &= ~0xC; // Uart switch to 51
}

/***************************************************************************************/
U32 msAPI_Player_AeonPatternSearch(U32 srcaddr, U32 len, U32 pattern, U32 unmask)
{
    U32 u32Time1, u32Time2;

    U32 u32PatternFoundAddress;

  //printf("srcaddr=0x%08lx ; len=0x%08lx; pattern=0x%08lx; unmask=0x%08lx =>",
  //        srcaddr,          len,         pattern,         unmask           );

  //XBYTE[0x1EAA] = 0xC; // Uart switch to AEON

    // Send search message
    if (MDrv_WaitMailBoxReady())
    {
        memset((U8 *)&MailBoxPara, 0x00, sizeof(MailBoxPara));
        MailBoxPara.u8CmdClass  = MB_CLASS_TS_SEARCH;
        MailBoxPara.u8CmdIdx    = MB_TS_SEARCH_FIND;
        MailBoxPara.ParamCnt    = 0;

        MailBoxPara.CMDType     = MB_CMD_TYPE_DEFAULT;

        memset(_pu8ShareMemory, 0x00, sizeof(_pu8ShareMemory));
        _pu8ShareMemory[_u8ShareMemoryOffset+0]  = (U8)GetByte0(srcaddr);
        _pu8ShareMemory[_u8ShareMemoryOffset+1]  = (U8)GetByte1(srcaddr);
        _pu8ShareMemory[_u8ShareMemoryOffset+2]  = (U8)GetByte2(srcaddr);
        _pu8ShareMemory[_u8ShareMemoryOffset+3]  = (U8)GetByte3(srcaddr);

        _pu8ShareMemory[_u8ShareMemoryOffset+4]  = (U8)GetByte0(len);
        _pu8ShareMemory[_u8ShareMemoryOffset+5]  = (U8)GetByte1(len);
        _pu8ShareMemory[_u8ShareMemoryOffset+6]  = (U8)GetByte2(len);
        _pu8ShareMemory[_u8ShareMemoryOffset+7]  = (U8)GetByte3(len);

        _pu8ShareMemory[_u8ShareMemoryOffset+8]  = (U8)GetByte0(pattern);
        _pu8ShareMemory[_u8ShareMemoryOffset+9]  = (U8)GetByte1(pattern);
        _pu8ShareMemory[_u8ShareMemoryOffset+10] = (U8)GetByte2(pattern);
        _pu8ShareMemory[_u8ShareMemoryOffset+11] = (U8)GetByte3(pattern);

        _pu8ShareMemory[_u8ShareMemoryOffset+12] = (U8)GetByte0(unmask);
        _pu8ShareMemory[_u8ShareMemoryOffset+13] = (U8)GetByte1(unmask);
        _pu8ShareMemory[_u8ShareMemoryOffset+14] = (U8)GetByte2(unmask);
        _pu8ShareMemory[_u8ShareMemoryOffset+15] = (U8)GetByte3(unmask);

        _pu8ShareMemory[_u8ShareMemoryOffset+16] = 188;
        _pu8ShareMemory[_u8ShareMemoryOffset+17] = 0;
        _pu8ShareMemory[_u8ShareMemoryOffset+18] = 0;
        _pu8ShareMemory[_u8ShareMemoryOffset+19] = 0;

        _pu8ShareMemory[_u8ShareMemoryOffset+20] = 0xff;
        _pu8ShareMemory[_u8ShareMemoryOffset+21] = 0xff;
        _pu8ShareMemory[_u8ShareMemoryOffset+22] = 0xff;
        _pu8ShareMemory[_u8ShareMemoryOffset+23] = 0xff;

        MDrv_SendMailBoxMsg();
    }

    // Receive serarch ACK message
    u32Time1 = msAPI_Timer_GetTime0();
    while(1)
    {
        msAPI_Timer_Delayms(10);

        memset((U8 *)&MailBoxPara, 0x00, sizeof(MailBoxPara));
        if (MDrv_GetMailBoxMsg(Q_STATE, (U8*)&MailBoxPara) == MB_GET_MSG_OK)
        {
            MailBox *pMB;
            pMB = (MailBox*)&MailBoxPara;

            if ((pMB->u8CmdClass == MB_CLASS_TS_SEARCH) &&
                (pMB->u8CmdIdx   == MB_TS_SEARCH_FIND_ACK) )
            {
              //printf("Got ack from AEON\n");
            }
            else
            {
                U8 * pu8ParaArray = (U8 *)&MailBoxPara;
                U8 u8ByteNo;
                for(u8ByteNo=0; u8ByteNo<24; u8ByteNo++)
                    printf("%02bx ", pu8ParaArray[u8ByteNo]);
                printf("\n");
            }
            break;
        }
        else
        {
            u32Time2 = msAPI_Timer_GetTime0();
            if((u32Time2-u32Time1)>=100)
            {
                printf("AEON mailbox timeout\n");
                break;
            }
          //printf("Wait ack from AEON\n");
        }
    }

  //XBYTE[0x1EAA] &= ~0xC; // Uart switch to 51

  //printf("%02bx%02bx%02bx%02bx \n", _pu8ShareMemory[_u8ShareMemoryOffset+23],_pu8ShareMemory[_u8ShareMemoryOffset+22],_pu8ShareMemory[_u8ShareMemoryOffset+21],_pu8ShareMemory[_u8ShareMemoryOffset+20]);
    u32PatternFoundAddress  = _pu8ShareMemory[_u8ShareMemoryOffset+23];
    u32PatternFoundAddress  = u32PatternFoundAddress<<8;
    u32PatternFoundAddress |= _pu8ShareMemory[_u8ShareMemoryOffset+22];
    u32PatternFoundAddress  = u32PatternFoundAddress<<8;
    u32PatternFoundAddress |= _pu8ShareMemory[_u8ShareMemoryOffset+21];
    u32PatternFoundAddress  = u32PatternFoundAddress<<8;
    u32PatternFoundAddress |= _pu8ShareMemory[_u8ShareMemoryOffset+20];

    return u32PatternFoundAddress;
}

#endif
/***************************************************************************************/

BOOLEAN code compile_msapi_player;

#else
BOOLEAN code compile_msapi_player;
#endif//ENABLE_PVR

#undef MSAPI_PLAYER_C

