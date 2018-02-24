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

#define MAPP_CHANNEL_CHANGEGE_C
////////////////////////////////////////////////////////////////////////////////
/// @file MApp_ChannelChange.c
/// @author MStar Semiconductor Inc.
/// @brief Channel Change control for APP layer
////////////////////////////////////////////////////////////////////////////////

//******************************************************************************
//                    Header Files
//*****************************************************************************
#include <string.h>
#include <stdio.h>

#include "Board.h"

#include "datatype.h"
#include "debug.h"

#if ENABLE_DLC
#include "apiXC_Dlc.h"
#endif

#include "msAPI_Timer.h"
#include "msAPI_audio.h"
#include "msAPI_Video.h"
#include "msAPI_VD.h"
#include "msAPI_MIU.h"
#include "mapi_cc_monitor.h"
#include "msAPI_Tuner.h"
#if ENABLE_ATSC
#include "msAPI_Tuner_ATSC.h"
#endif
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "apiXC_Sys.h"

#include "MApp_SaveData.h"
#include "MApp_Exit.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalVar.h"
#include "MApp_GlobalVar_ATSC.h"
#include "MApp_GlobalFunction.h"
#include "MApp_Audio.h"
#include "MApp_InputSource.h"
#include "MApp_MVDMode.h"
#include "MApp_ChannelProc_ATSC.h"
#include "MApp_DataBase_ATSC.h"
#include "MApp_ChannelChange.h"
#include "MApp_SignalMonitor.h"
#include "MApp_Psip.h"
#include "mapp_closedcaption.h"
#include "MApp_VChip.h"

#if ENABLE_ATSC
#include "MApp_Audio_ATSC.h"
#endif
#if( CHAKRA3_AUTO_TEST )
#include "MApp_AutoTest.h"
#endif


extern U32 g_u32StreamTime;
//extern THR_TBL_TYPE code AuSifInitThreshold[];
extern MS_U8 bPreviousSoundMode, bCurrentSoundMode;

//==============================================================================
/*                     Macro                    */
//==============================================================================
#ifndef ENABLE_ATV_CHANNEL_CHANGE_FINETUNING
#define ENABLE_ATV_CHANNEL_CHANGE_FINETUNING    ENABLE
#endif

//#define CHANNELCHANGE_DBINFO(y)         y
#define DEBUG_ENABLE_CHANNEL_ATSC(x)    //x

#define ENABLE_CH_CHANGE_TIMER_DEBUG    0

/*********************************************************************************/
//                     Local
/*********************************************************************************/
U8 fEnableCCWhenMuteFunc; // Need rename!

static U8 u8CurrentPsyNumber;
static U8 u8PrevPsyNumber;

static U16 g_ChChg_u16CurChAudioPid = 0;
static U16 g_ChChg_u16CurChVideoPid = 0;

/*********************************************************************************/

void MApp_ChannelChange_DisableChannel_ATSC ( void ) ///*U8 u8ChanBufIdx*/ ) //for change channel
{
    //VDEC_Status vdecStatus;
    //memset(&vdecStatus, 0, sizeof(VDEC_Status));
    //MS_BOOL bRet = MApi_VDEC_GetStatus(&vdecStatus);
    DEBUG_ENABLE_CHANNEL_ATSC( printf("%s()\n", __FUNCTION__); );

    if ( !fEnableSignalCheck )
    {
        return;
    }

    //printf("===> [%s] Line=%d\n",__FUNCTION__, __LINE__);

    #if (ENABLE_CH_CHANGE_TIMER_DEBUG == 1)
    g_u32ChannelChangeTimer1 = msAPI_Timer_GetTime0();
    #endif

    MApp_ChannelChange_DisableAV(MAIN_WINDOW);

#if (ENABLE_CHCHANGETIME)
    printf("\n>>>[ChChangeTime][DisableAV_Done]=[%d]\r\n",msAPI_Timer_DiffTimeFromNow(gU32ChChangeTime));
#endif

    if ( IsDTVInUse() )
    {
        /* Use for from DTV scramble to ATV protect */
        //msAPI_AUD_SetPaser(MSAPI_AUD_PASER_STOP);

        //pstVirtualCh = &astChannelBuf[u8ChanBufIdx].stSrvInfo;

        //if(pstVirtualCh->astSoundTrack[g_u8AudLangSelected].u16AudioPid /*< MSAPI_DMX_INVALID_PID*/)
        {
            /* stop audio decoder */
            MApi_AUDIO_SetCommand( (En_DVB_decCmdType)MSAPI_AUD_STOP );
          #if (ENABLE_ATSC_AD_FUNC)
            if(stGenSetting.g_SoundSetting.bEnableAD)
                MApi_AUDIO_SetCommand(MSAPI_AUD_DVB2_DECCMD_STOP);
          #endif

            /* stop audio filter */
            msAPI_DMX_Stop( u8AudFid );
        }

        //if(pstVirtualCh->u16VideoPid /*< MSAPI_DMX_INVALID_PID*/)
        {
            /* yym@2013-4-16 */
            /* When changing channel from AudioOnly to Normal, it will not stop MVDParser, so CC driver will not be init. */
            //if(bRet == TRUE && vdecStatus.bInit == TRUE)
            {
                CC_SourceFuns.StopMVDParser();
                // Stop CC parser
                CC_SourceFuns.Stop708Parsing();
            }

            /* stop video filter */
            msAPI_DMX_Stop( u8VidFid );

            /* stop video decoder */
            msAPI_VID_Command( MSAPI_VID_STOP );

            /*stop VOP*/
            MDrv_MVOP_Enable(FALSE);
        }

        //if(pstVirtualCh->u16PcrPid /*< MSAPI_DMX_INVALID_PID*/)
        {
            /* stop pcr filter */
            msAPI_DMX_Stop( u8PcrFid );
        }
        MApp_Dmx_DisableTableMonitor_ATSC();
    }
    else
    {
        /* stop audio decoder */
        MApi_AUDIO_SIF_SendCmd(MSAPI_AUD_SIF_CMD_SET_STOP, NULL, NULL);
    }

    fSignalLockStatus = FE_NOT_LOCK;
    fEnableSignalCheck = FALSE;

    #if (ENABLE_CH_CHANGE_TIMER_DEBUG == 1)
    g_u32ChannelChangeTimer2 = msAPI_Timer_GetTime0();
    #endif

#if (ENABLE_CHCHANGETIME)
    printf("\n>>>[ChChangeTime][Disable CH done]=[%d]\r\n",msAPI_Timer_DiffTimeFromNow(gU32ChChangeTime));
#endif

}
/*********************************************************************************/

static void MApp_ChChg_EnCh_Reset_CC_VChip(void)
{
    /* Reset ACC Existing Scheme */
    msAPI_CC_Reset();

#if(ENABLE_ATSC_VCHIP)
    MApp_VChip_Init();
#endif

    msAPI_CC_VchipRateReset();
    CC_SourceFuns.ResetXDSInfo();   //benny added for mantis 1202661 in 20160919!

    fVChipPassWordEntered = FALSE;
}

static void MApp_ChChg_EnCh_ReInit_CC_VChip(void)
{
#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("EnCh CC - Start" );
#endif

    if( IsAtscInUse() )
    {
        printf("ReInit CC for DTV\n");

        // for channel change, caption mode must change back to 708
        if ( stGenSetting.g_CaptionSetting.u8CCMode == CAPTIONMENU_MODE_ON )
        {
            if (stGenSetting.g_CaptionSetting.u8CaptionServiceModeDTV != CAPTIONMENU_SERVICE_OFF)
               stGenSetting.g_CaptionSetting.u8CaptionServiceMode = stGenSetting.g_CaptionSetting.u8CaptionServiceModeDTV;
            else
               stGenSetting.g_CaptionSetting.u8CaptionServiceMode = stGenSetting.g_CaptionSetting.u8CaptionServiceModeATV;
         }
      #if (PARSING_CC_WHENMUTE)
        else if (stGenSetting.g_CaptionSetting.u8CCMode == CAPTIONMENU_MODE_CC_WHEN_MUTE)
        {
               fEnableCCWhenMuteFunc = FALSE;
               stGenSetting.g_CaptionSetting.u8CaptionServiceMode = CS_OFF;
               MApp_ClosedCaption_GetUserCmd();
               if (MApp_Aud_GetMuteStatus())
               {
                    fEnableCCWhenMuteFunc = TRUE;
                    fEnableClosedCaptionFunc = TRUE;
               }
       }
      #endif

    #if(DEBUG_CHG_SRC_TIME)
        msDebug_PrintChgSrcTime("EnCh CC - 2" );
    #endif

        MApp_ClosedCaption_Set_ProgramChange();

    #if(DEBUG_CHG_SRC_TIME)
        msDebug_PrintChgSrcTime("EnCh CC - 3" );
    #endif

        if (stGenSetting.g_CaptionSetting.u8CCMode != CAPTIONMENU_MODE_CC_WHEN_MUTE)
            MApp_ClosedCaption_GetUserCmd();

    }
    else
    {
        printf("ReInit CC for ATV\n");
        // todo...
    }

#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("EnCh CC - 5" );
#endif


#if(ENABLE_ATSC_VCHIP)
    MApp_VChip_Init();
#endif

#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("EnCh CC - 6" );
#endif

    MApp_CC_Initialize();

#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("EnCh CC - 7" );
#endif

    fVChipPassWordEntered = FALSE;

#if CUSTOMER_FOR_UI_CC_708_608_APPEARING
    /* Reset ACC Existing Scheme */
    msAPI_CC_CCInfoInit();

    // Stop CC parser
    MApp_ClosedCaption_Parser_Stop();


    MApp_ClosedCaption_Parser_Init();
#endif

#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("EnCh CC - End" );
#endif

}

static void MApp_ChChg_EnCh_Setup_Audio(void)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("EnCh Setup_Audio - Start" );
#endif

    //Remapping Audio language
    MApp_ATSC_ReMapAudioLanguage();


    U16 u16AudioPID = MSAPI_DMX_INVALID_PID;


    #if(ENABLE_ATSC_VIDEO_DESC)
        if(stGenSetting.g_SoundSetting.enVideoDescription == EN_VIDEO_DESCRIPTION_ITEM_ON)
            u16AudioPID = MApp_SetPreferAudioSoundTrackPID(0);
        else //if(stGenSetting.g_SoundSetting.enVideoDescription == EN_VIDEO_DESCRIPTION_ITEM_OFF)
    #endif
        {
            u16AudioPID = MApp_SetPreferAudioSoundTrackPIDNew();
        }

#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("EnCh Au - 3" );
#endif

    U8 u8CurChLangNum = MApp_ChanProc_GetCurChannelPointer()->u8AudLangNum;

    if( (MSAPI_DMX_INVALID_PID == u16AudioPID)
      ||(u16AudioPID == 0 )
      )
    {
        printf("\nWarning: Audio Pid invalid!\n");
        g_ChChg_u16CurChAudioPid = 0;
    }
    else
    {
        g_ChChg_u16CurChAudioPid = u16AudioPID;

        //printf("u16AudioPID=%u\n", u16AudioPID);
        //printf("u8AudFid=%u\n", u8AudFid);
        /* set audio PID & start filter */
        DMX_FILTER_STATUS eDMX_FILTER_STATUS = msAPI_DMX_StartFilter( u16AudioPID, MSAPI_DMX_FILTER_TYPE_AUDIO, &u8AudFid );
        if( eDMX_FILTER_STATUS != DMX_FILTER_STATUS_OK )
        {
            printf("\nError: Start Audio filter failed\n");
        }

        //printf("u8AudFid=%u\n", u8AudFid);

    #if(DEBUG_CHG_SRC_TIME)
        msDebug_PrintChgSrcTime("EnCh Au - 4" );
    #endif

        /* set decoder system and reload firmware code */
        MApi_AUDIO_SetCommand( (En_DVB_decCmdType)MSAPI_AUD_STOP );

    #if(DEBUG_CHG_SRC_TIME)
        msDebug_PrintChgSrcTime("EnCh Au - 5" );
    #endif

        EN_AUD_STREAM_TYPE enTempStreamType = MApp_ATSC_Get_AudioStreamType();
        DEBUG_AU_LOAD_CODE( printf("enTempStreamType=%u\n", enTempStreamType); );

        // Stop decode & change decoder system
        MApp_Audio_ATSC_Set_DecodeSystem(enTempStreamType); // Use 130ms

        //msAPI_Timer_Delayms(150); // to make sure it's ready.....

    #if(DEBUG_CHG_SRC_TIME)
        msDebug_PrintChgSrcTime("EnCh Au - Set_DecodeSystem" );
    #endif

        if ( enTempStreamType == AUD_STREAM_TYPE_AC3 || enTempStreamType == AUD_STREAM_TYPE_AAC)
        {
           #if (ENABLE_UI_SPDIF_SETTING==ENABLE)
            if( stGenSetting.g_SysSetting.fSPDIFMODE == 0) // PCM mode
            {
                MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM); // 60ms
            }
            else // Non-PCM
            {
                MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM);
            }
           #else
                MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM);
           #endif
        }
        else
        {
            MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
        }

    #if(DEBUG_CHG_SRC_TIME)
        msDebug_PrintChgSrcTime("EnCh Au - 7" );
    #endif

    #if (ENABLE_ATSC_AD_FUNC)
        if ((u8CurChLangNum > 1) && (stGenSetting.g_SoundSetting.bEnableAD))
        {
            U16 u16AudioPID2;
            if(g_u8AudLangSelected == 0)
            {
                u16AudioPID2 = astgSoundTrack[1].u16AudioPid;
            }
            else
            {
                u16AudioPID2 = astgSoundTrack[0].u16AudioPid;
            }
            msAPI_DMX_StartFilter(u16AudioPID2, MSAPI_DMX_FILTER_TYPE_AUDIO2, &u8AudFid2);

            DEBUG_AU_LOAD_CODE( printf("enTempStreamType=%u\n", enTempStreamType); );

          #if 1
            MApp_Audio_ATSC_Set_DecodeSystem_AD(enTempStreamType);
          #else
            if(enTempStreamType == AUD_STREAM_TYPE_MPEG)
            {
                MApi_AUDIO_SetSystem(MSAPI_AUD_DVB2_MPEG);
            }
            else if(enTempStreamType == AUD_STREAM_TYPE_AAC)
            {
                MApi_AUDIO_SetSystem(MSAPI_AUD_DVB2_AAC);
            }
            else
            {
                MApi_AUDIO_SetSystem(MSAPI_AUD_DVB2_AC3);
            }
          #endif

        }

        //MApi_AUDIO_SetCommand( (En_DVB_decCmdType)MSAPI_AUD_PLAY );
    #endif

    #if(DEBUG_CHG_SRC_TIME)
        msDebug_PrintChgSrcTime("EnCh Au - 8" );
    #endif

        /* re-sync audio decoder */
        //MApi_AUDIO_SetCommand(MSAPI_AUD_RESYNC);

        /* Use for from DTV scramble to ATV protect */
        //msAPI_AUD_SetPaser(MSAPI_AUD_PASER_PLAY);

        /* start audio decoder */
        MApi_AUDIO_SetCommand( (En_DVB_decCmdType)MSAPI_AUD_PLAY );

      #if (ENABLE_ATSC_AD_FUNC)
        if((u8CurChLangNum > 1) && (stGenSetting.g_SoundSetting.bEnableAD))
            MApi_AUDIO_SetCommand(MSAPI_AUD_DVB2_DECCMD_PLAY);
      #endif

    #if(DEBUG_CHG_SRC_TIME)
        msDebug_PrintChgSrcTime("EnCh Au - 9" );
    #endif


      #if (ENABLE_AUDIOBYPASS)
        if (astgSoundTrack[g_u8AudLangSelected].u8AudAc3Bsmod == 0x02)// u16AudioPID /*< MSAPI_DMX_INVALID_PID*/ )
        {
            //Remapping Audio language
            //MApp_ReMapAudioLanguage();

            u16AudioPID = MApp_SetPreferAudioSoundTrackPID(1);
            /* stop audio decoder */
            MApi_AUDIO_SetCommand( (En_DVB_decCmdType)MSAPI_AUD_STOP );
            /* stop audio filter */
            msAPI_DMX_Stop( u8AudFid );

            /* set audio PID & start filter */
            msAPI_DMX_StartFilter( u16AudioPID, MSAPI_DMX_FILTER_TYPE_AUDIO, &u8AudFid );
            /* set decoder system and reload firmware code */
            MApi_AUDIO_SetCommand( (En_DVB_decCmdType)MSAPI_AUD_STOP );
            /* start audio decoder */
            MApi_AUDIO_SetCommand( (En_DVB_decCmdType)MSAPI_AUD_PLAY );
        }
      #endif

    #if(DEBUG_CHG_SRC_TIME)
        msDebug_PrintChgSrcTime("EnCh Au - 10" );
    #endif
    }


#if ENABLE_SOUNDTRACK_CHECKER_NEW
    start_decode_audio_time = 0;
    unchecked_audio_track_num = u8CurChLangNum;
    unchecked_audio_track_num *= 3;
    //u8AudioCheckLoop =  0;
    u8AudioType =  0;
    bFlagTrackChecker = 0;

#else

    start_decode_audio_time = msAPI_Timer_GetTime0();
    unchecked_audio_track_num = ++(MApp_ChanProc_GetCurChannelPointer()->u8AudLangNum);
    unchecked_audio_track_num <<= 1;
    u8AudioType =  0;
#endif

#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("EnCh Setup_Audio - End" );
#endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

static void MApp_ChChg_EnCh_Setup_Video(MS_VIRTUAL_CHANNEL * pVirCh)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("EnCh_A - Setup_Video - Start" );
#endif

    U16 u16CurChVideoPid = pVirCh->u16VideoPid;

    if( (0 == u16CurChVideoPid)
      ||(MSAPI_DMX_INVALID_PID == u16CurChVideoPid)
      )
    {
        printf("\nError: VideoPid invalid!\n");
        g_ChChg_u16CurChVideoPid = 0;
        return;
    }

    g_ChChg_u16CurChVideoPid = u16CurChVideoPid;

    // Stop VDEC ...
    VDEC_Status stVdecStatus;
    memset( &stVdecStatus, 0, sizeof(VDEC_Status) );
    MApi_VDEC_GetStatus(&stVdecStatus);

    // Stop vdec
    if( stVdecStatus.bInit )
        msAPI_VID_Command( MSAPI_VID_STOP );



    /* set video PID & start filter */
    msAPI_DMX_StartFilter( u16CurChVideoPid, MSAPI_DMX_FILTER_TYPE_VIDEO, &u8VidFid );

#if 1 // Refine
    switch( pVirCh->stVirtualChNum.u8VideoStreamType )
    {
        default:
            printf("\nError: Unknown u8VideoStreamType=%u\n", pVirCh->stVirtualChNum.u8VideoStreamType);
            break;

    #if (ENABLE_H265) // need check
        case VIDEO_STREAM_TYPE_H265:
            msAPI_VID_SetMappingAVCParameter(E_VDEC_CODEC_TYPE_HEVC);
            break;
    #endif

    #if( (MEMORY_MAP > MMAP_32MB) \
       ||((MEMORY_MAP == MMAP_32MB) && (ENABLE_32M_H264 == ENABLE)) \
       )
        case VIDEO_STREAM_TYPE_H264:
            msAPI_VID_SetMappingAVCParameter(E_VDEC_CODEC_TYPE_H264);
            break;
    #endif

        case VIDEO_STREAM_TYPE_MPEG1:
        case VIDEO_STREAM_TYPE_MPEG2:
        case VIDEO_STREAM_TYPE_OPTION_MPEG2:
            msAPI_VID_SetMappingAVCParameter(E_VDEC_CODEC_TYPE_MPEG2);
            break;
    }

#else

  #if (ENABLE_H265) // need check
    if (pVirCh->stVirtualChNum.u8VideoStreamType == VIDEO_STREAM_TYPE_H265)
    {
        msAPI_VID_SetMappingAVCParameter(E_VDEC_CODEC_TYPE_HEVC);
    }
  #endif

#if (MEMORY_MAP > MMAP_32MB)
    if (pVirCh->stVirtualChNum.u8VideoStreamType == VIDEO_STREAM_TYPE_H264)
    {
        msAPI_VID_SetMappingAVCParameter(E_VDEC_CODEC_TYPE_H264);
    }
#endif

#if((MEMORY_MAP == MMAP_32MB) && (ENABLE_32M_H264 == ENABLE))
    if (pVirCh->stVirtualChNum.u8VideoStreamType == VIDEO_STREAM_TYPE_H264)
    {
        msAPI_VID_SetMappingAVCParameter(E_VDEC_CODEC_TYPE_H264);
    }
#endif

    if( (pVirCh->stVirtualChNum.u8VideoStreamType == VIDEO_STREAM_TYPE_MPEG1)
      ||(pVirCh->stVirtualChNum.u8VideoStreamType == VIDEO_STREAM_TYPE_MPEG2)
      ||(pVirCh->stVirtualChNum.u8VideoStreamType == VIDEO_STREAM_TYPE_OPTION_MPEG2)
      )
    {
        msAPI_VID_SetMappingAVCParameter(E_VDEC_CODEC_TYPE_MPEG2);
    }
#endif

#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("EnCh_A - Setup_Video - 5" );
#endif

    // Init Vdec ...
    //msAPI_VID_SetVdecFrameMode(TRUE);
    msAPI_VID_Init(FALSE, E_VDEC_SRC_MODE_DTV); // use 128ms

#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("EnCh_A - Setup_Video - VDEC_Init" );
#endif


#if (ENABLE_VDEC_AVSYNC_REPEAT)
    MApi_VDEC_SetControl(VDEC_USER_CMD_AVSYNC_REPEAT_TH, 0xFF);  //restore setting
#endif
    #if(CHIP_FAMILY_TYPE == CHIP_FAMILY_WHISKY)
    {
        //init Vdec callback function
        MApp_VID_CBInit();
    }
    #endif

    /* start video decoder */
    msAPI_VID_Command( MSAPI_VID_PLAY );

    MDrv_MVOP_Enable ( TRUE );

#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("EnCh_A - Setup_Video - End" );
#endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());
}

void MApp_ChannelChange_EnableChannel_ATSC (void)
{
    DMX_FILTER_STATUS eDMX_FILTER_STATUS = DMX_FILTER_STATUS_OK;

    DEBUG_ENABLE_CHANNEL_ATSC( printf("%s()\n", __FUNCTION__); );

#if (ENABLE_CHCHANGETIME)
     printf("\n>>>[ChChangeTime][Start_EnableCH]=[%d]\r\n",msAPI_Timer_DiffTimeFromNow(gU32ChChangeTime));
#endif
#if(CHAKRA3_AUTO_TEST)
    AT_LOG("EnableChannel start");
#endif


  #if (ENABLE_CH_CHANGE_TIMER_DEBUG == 1)
    g_u32ChannelChangeTimer3 = msAPI_Timer_GetTime0();
  #endif

#if ENABLE_ATSC_CHLIST_DISP_TOGETHER
    if (MApp_ChanProc_IsCurProgIndexAir())
        ANT_TYPE = ANT_AIR;
    else
        ANT_TYPE = ANT_CATV;
    MApp_DB_ATSC_SaveCurChSetting();
    MApp_DB_ATSC_InitBaseAddr((EN_ANT_TYPE) ANT_TYPE);
    MApp_DB_ATSC_LoadCurChSetting();
#endif

    //printf("stChSetting.u16TotalHideSrvNum=%u\n", stChSetting.u16TotalHideSrvNum);
    //printf("stChSetting.u16MainListSrvNum=%u\n", stChSetting.u16MainListSrvNum);

    if ( ( fEnableSignalCheck ) // Already enable channel
    #if 0//ndef CHANNEL_HIDE_AS_SKIP_ONLY
        || ( stChSetting.u16TotalHideSrvNum == stChSetting.u16MainListSrvNum )
    #endif
    )
    {
        //PRINT_CURRENT_LINE();
        //printf("fEnableSignalCheck=%u\n", fEnableSignalCheck);
        return;
    }

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START(););

    // Check  current channel para...
    DEBUG_ENABLE_CHANNEL_ATSC( printf("Cur Prog List=%u\n", MApp_ChanProc_GetCurProgListType() ); );

    DEBUG_ENABLE_CHANNEL_ATSC( U16 u16CurListProgIdx = MApp_ChanProc_GetCurProgIndex(); );
    U16 u16MainListProgIdx = MApp_ChanProc_GetCurMainListProgIndex();
    DEBUG_ENABLE_CHANNEL_ATSC( printf("u16CurListProgIdx=%u, u16MainListProgIdx=%u\n", u16CurListProgIdx, u16MainListProgIdx ); );


#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("EnCh_A - Start" );
#endif

    //u8CurrentPsyNumber = PHY_CH_IDX(u16CurListProgIdx);
  #if ENABLE_ATSC_CHLIST_DISP_TOGETHER
    if (MApp_ChanProc_IsCurProgIndexAir())
    {
        u8CurrentPsyNumber = PHY_CH_IDX_AIR(u16MainListProgIdx);
    }
    else
    {
        u8CurrentPsyNumber = PHY_CH_IDX_CATV(u16MainListProgIdx - stChSettingDisp[ANT_AIR].u16MainListSrvNum);
    }
  #else
    u8CurrentPsyNumber = PHY_CH_IDX(u16MainListProgIdx);
  #endif

    DEBUG_ENABLE_CHANNEL_ATSC( printf(" u8CurrentPsyNumber=%u\n", u8CurrentPsyNumber ); );

    if( FALSE == msAPI_DtvATSC_IsValidRfNumber(u8CurrentPsyNumber) )
    {
        printf("\nError: RF num=%u is invalid! => Skip enable channel\n", u8CurrentPsyNumber);
        return;
    }

    if(u8PrevPsyNumber != u8CurrentPsyNumber)
    {
        g_u32StreamTime = 0; // reset stream time info
        u8PrevPsyNumber = u8CurrentPsyNumber;
    }
    g_u8AudLangSelected = 0;

#if ENABLE_ATSC_CHLIST_DISP_TOGETHER
    U16 u16VirChIdx ;
    if (MApp_ChanProc_IsCurProgIndexAir())
    {
        MApp_DB_ATSC_InitBaseAddr(ANT_AIR);
       u16VirChIdx = VIR_CH_IDX_AIR(u16MainListProgIdx);
    }
    else
    {
        MApp_DB_ATSC_InitBaseAddr(ANT_CATV);
        u16VirChIdx = VIR_CH_IDX_CATV(u16MainListProgIdx - stChSettingDisp[ANT_AIR].u16MainListSrvNum);
    }
    pstVirtualCh = MApp_ChanProc_GetChannelPointer( u16VirChIdx );
    MApp_DB_ATSC_InitBaseAddr((EN_ANT_TYPE)ANT_TYPE);
#else
    U16 u16VirChIdx = VIR_CH_IDX(u16MainListProgIdx);

    DEBUG_ENABLE_CHANNEL_ATSC( printf(" u16VirChIdx=%u\n", u16VirChIdx ); );

    pstVirtualCh = MApp_ChanProc_GetChannelPointer( u16VirChIdx );
#endif
    //printf("pstVirtualCh.fModulation=%u\n", pstVirtualCh->stTPSetting.fModulation);


    // Get TPSetting
    MS_TP_SETTING_ATSC stTPSettingAtscTmp;
    MApp_ChanProc_Get_TPSetting(pstVirtualCh, &stTPSettingAtscTmp);


    // Reset CC/VChip
    MApp_ChChg_EnCh_Reset_CC_VChip();


#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("EnCh_A - 5" );
#endif

    //printf("stTPSettingAtscTmp.fModulation=%u\n", stTPSettingAtscTmp.fModulation);
    if( stTPSettingAtscTmp.fModulation == DEMOD_ATSC_MODE_NTSC )
    {
        printf("Cur Ch is ATV\n");
        if ( SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) != INPUT_SOURCE_TV )
        {
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ATV;
            MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_ATV, MAIN_WINDOW );
          #if (ENABLE_CHCHANGETIME)
            printf("\n>>>[ChChangeTime][End_SwitchToATVSource]=[%d]\r\n",msAPI_Timer_DiffTimeFromNow(gU32ChChangeTime));
          #endif
        }
        else
        {
            //UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ATV;
            //msAPI_AVD_Parameter_Initial();
        }

        /* tune to new TP, if TP change */
        msAPI_Tuner_Tune2RfCh_ATSC( &stTPSettingAtscTmp );

#if (ENABLE_CHCHANGETIME)
     printf("\n>>>[ChChangeTime][End_Tune2RfCh]=[%d]\r\n",msAPI_Timer_DiffTimeFromNow(gU32ChChangeTime));
#endif

//#if ENABLE_ATV_CHANNEL_CHANGE_FINETUNING
#if(ENABLE_ATSC_ATV_ONLY_NTSC)
        msAPI_AVD_SetChannelChange();
        msAPI_AVD_SetVideoStandard(E_VIDEOSTANDARD_NTSC_M/*msAPI_AVD_GetVideoStandard()*/);
        msAPI_AVD_ForceVideoStandard(E_VIDEOSTANDARD_NTSC_M/*msAPI_AVD_GetVideoStandard()*/);
        //msAPI_AVD_WaitForVideoSyncLock();
    #if (ENABLE_CHCHANGETIME)
        printf(">>>[ChChangeTime][Wait VD Sync lock done]=[%d]\r\n",msAPI_Timer_DiffTimeFromNow(gU32ChChangeTime));
    #endif
#endif
        //AT_LOG("Set VD done");

      #if ((TV_SYSTEM == TV_NTSC) && (AUDIO_SYSTEM_SEL == AUDIO_SYSTEM_A2))
        MApi_AUDIO_SIF_SendCmd(MSAPI_AUD_SIF_STANDARD_RESET, NULL, NULL);
        MApi_AUDIO_SIF_SetStandard( E_AUDIOSTANDARD_M_A2);
        MApi_AUDIO_SIF_SetPALType(AU_SIF_PAL_A2);
      #else
        MApi_AUDIO_SIF_SetStandard( E_AUDIOSTANDARD_M_BTSC );
      #endif

        //AT_LOG("Set Audio-1 done");

        // Set BTSC Threshold
    //#if  (AUDIO_SYSTEM_SEL == AUDIO_SYSTEM_BTSC)
        //MApi_AUDIO_SIF_SetThreshold(AuSifInitThreshold);
        msAPI_AUD_SIF_SetThreshold();
    //#endif

        /* start audio decoder */
        MApi_AUDIO_SIF_SendCmd(MSAPI_AUD_SIF_CMD_SET_PLAY, NULL, NULL);

        //AT_LOG("Set Audio-2 done");

        //MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);

      #if ( MTS_MONITOR_BY_HOUSEKEEPING)
        MApp_Aud_EnablePollingStereo();

        // check MTS before umute...
        bCurrentSoundMode = MApi_AUDIO_SIF_GetSoundMode();
        if ( MApp_AUDIO_IsSifSoundModeExist( stGenSetting.g_SoundSetting.Mts ) )
        {
            g_u8AudLangSelected = stGenSetting.g_SoundSetting.Mts;
            MApi_AUDIO_SIF_SetSoundMode(MApp_SoundMtsSifSoundModeTrans(g_u8AudLangSelected));
            bPreviousSoundMode = bCurrentSoundMode;
        }
        else if( MApp_AUDIO_IsSifSoundModeExist( SOUND_MTS_STEREO ) )
        {
            g_u8AudLangSelected = SOUND_MTS_STEREO;
            MApi_AUDIO_SIF_SetSoundMode(MApp_SoundMtsSifSoundModeTrans(g_u8AudLangSelected));
            bPreviousSoundMode = bCurrentSoundMode;
        }
      #else
         // check MTS before umute...
        bCurrentSoundMode = MApi_AUDIO_SIF_GetSoundMode();

        if ( MApp_AUDIO_IsSifSoundModeExist( stGenSetting.g_SoundSetting.Mts ) )
        {
            g_u8AudLangSelected = stGenSetting.g_SoundSetting.Mts;
        }
        else if( MApp_AUDIO_IsSifSoundModeExist( SOUND_MTS_STEREO ) )
        {
            g_u8AudLangSelected = SOUND_MTS_STEREO;
        }
        else
        {
            //  g_u8AudLangSelected=SOUND_MTS_MONO;
            g_u8AudLangSelected = stGenSetting.g_SoundSetting.Mts;
        }
        //printf(">>>>>>>enable channel bCurrentSoundMode=%d>>>>>>>\n",bCurrentSoundMode);
        //printf(">>>>>>>enable channel MTS=%d>>>>>>>\n",g_u8AudLangSelected);
       // printf(">>>>>>>enable channel SetSoundMode=%d>>>>>>>\n",MApp_SoundMtsSifSoundModeTrans( g_u8AudLangSelected));
        MApi_AUDIO_SIF_SetSoundMode(MApp_SoundMtsSifSoundModeTrans(g_u8AudLangSelected));
        bPreviousSoundMode = bCurrentSoundMode;
        stGenSetting.g_SoundSetting.Mts=(EN_SOUND_MTS_TYPE)g_u8AudLangSelected;
      #endif

        //AT_LOG("Set Audio-4 done");

        MApp_ChannelChange_EnableAV();

        //AT_LOG("EnableAV done");

    #if (ENABLE_CHCHANGETIME)
        printf("\n>>>[ChChangeTime][EnableAV_Done]=[%d]\r\n",msAPI_Timer_DiffTimeFromNow(gU32ChChangeTime));
    #endif

    }
    else
    {
        printf("Cur Ch is DTV\n");

      #if ENABLE_DMXMONITOR
        if (fReInitDemux == TRUE)
        {
            printf("MApi_DMX_Init() !! \n");
            MApp_Dmx_CloseAllFilters_ATSC();
            MApi_DMX_Init();
            fReInitDemux = FALSE;
        }
      #endif

        /* enable table monitor should be before than TP change */
        MApp_Dmx_EnableTableMonitor_ATSC();

    #if(DEBUG_CHG_SRC_TIME)
        msDebug_PrintChgSrcTime("EnCh_A - 7" );
    #endif

        if ( SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) != INPUT_SOURCE_DTV )
        {
            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ATSC;
            MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_TYPE, MAIN_WINDOW );
            #if (ENABLE_CHCHANGETIME)
              printf("\n>>>[ChChangeTime][End_SwitchToDTVSource]=[%d]\r\n",msAPI_Timer_DiffTimeFromNow(gU32ChChangeTime));
            #endif
        }

    #if(DEBUG_CHG_SRC_TIME)
        msDebug_PrintChgSrcTime("EnCh_A - 8" );
    #endif

        /* tune to new TP, if TP change */
        msAPI_Tuner_Tune2RfCh_ATSC( &stTPSettingAtscTmp ); // 90ms

    #if (ENABLE_CHCHANGETIME)
        printf("\n>>>[ChChangeTime][End_Tune2RfCh]=[%d]\r\n",msAPI_Timer_DiffTimeFromNow(gU32ChChangeTime));
    #endif

    #if(DEBUG_CHG_SRC_TIME)
        msDebug_PrintChgSrcTime("EnCh_A - 9" );
    #endif

        MApp_Dmx_PMT_ChChange();


        //printf("pstVirtualCh->u16PcrPid=%u\n", pstVirtualCh->u16PcrPid);
        if ( pstVirtualCh->u16PcrPid /*< MSAPI_DMX_INVALID_PID*/ )
        {
            //printf("u8PcrFid=%u\n", u8PcrFid);

            /* set pcr PID & start filter */
            eDMX_FILTER_STATUS = msAPI_DMX_StartFilter( pstVirtualCh->u16PcrPid, MSAPI_DMX_FILTER_TYPE_PCR, &u8PcrFid );
            //printf("eDMX_FILTER_STATUS=%u\n", eDMX_FILTER_STATUS);

            //printf("u8PcrFid=%u\n", u8PcrFid);
        }
        else if( pstVirtualCh_VCT->u16PcrPid )
        {
             msAPI_DMX_StartFilter( pstVirtualCh_VCT->u16PcrPid, MSAPI_DMX_FILTER_TYPE_PCR, &u8PcrFid );
        }

    #if(DEBUG_CHG_SRC_TIME)
        msDebug_PrintChgSrcTime("EnCh_A - 11" );
    #endif

        // Setup video...
        MApp_ChChg_EnCh_Setup_Video(pstVirtualCh);


        // Setup audio...
        MApp_ChChg_EnCh_Setup_Audio();

    #if(DEBUG_CHG_SRC_TIME)
        msDebug_PrintChgSrcTime("EnCh_A - 13" );
    #endif

        // If no audio pid, vdec freerun
        if( 0 == g_ChChg_u16CurChAudioPid )
        {
            msAPI_VID_Command( MSAPI_VID_FREERUN );
        }

    #if (STORE_RD_CH_ENABLE == 1)
        if( pstVirtualCh->u16VideoPid != 0 )
        {
            fEnableMvdTimingMonitor = TRUE;
            if(pstVirtualCh->astSoundTrack[0].u16AudioPid != 0)
            {
                MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_AVSYNC);
            }
        }
        else
        {
            fEnableMvdTimingMonitor = FALSE;
            if(pstVirtualCh->astSoundTrack[0].u16AudioPid != 0)
            {
                MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_FREE_RUN);
            }
        }
    #endif //(STORE_RD_CH_ENABLE == 1)

    #if(DEBUG_CHG_SRC_TIME)
        msDebug_PrintChgSrcTime("EnCh_A - 14" );
    #endif

        //For display AV simultaneously.
        MApp_VID_VariableInit();

    #if(DEBUG_CHG_SRC_TIME)
        msDebug_PrintChgSrcTime("EnCh_A - 18" );
    #endif

        // move unmute here to avoid POP noise
        if( pstVirtualCh->astSoundTrack[0].u16AudioPid != 0 )
        {
            MApp_Aud_SetPathUnMute();
            //MApi_AUDIO_SPDIF_SetMute(FALSE);
        }
    }// Src is DTV - End

#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("EnCh_A - 20" );
#endif

    // Re-init CC-VChip
    MApp_ChChg_EnCh_ReInit_CC_VChip();


    bEpgEventSorted = FALSE;

#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("EnCh_A - 25" );
#endif

    // Reset signal monitor
    //MApp_SignalMonitor_Init();
    MApp_SignalCheck_Init();
    fEnableSignalCheck = TRUE;

  #if 0//(ENABLE_MAX_RRT_DIMENSION_NUMBER == 0)
    u8LastPatItemNo = 0;
  #endif

#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("EnCh_A - 26" );
#endif

    MApp_ChanProc_SaveLastWatched();

  #if (ENABLE_CH_CHANGE_TIMER_DEBUG == 1)
    g_u32ChannelChangeTimer4 = msAPI_Timer_GetTime0();
  #endif

  #if (ENABLE_AUDIO_ONLY_FULL_FEATURE == 1)
    if( (IsDTVInUse())
        &&(pstVirtualCh->u16VideoPid==0)
        && (pstVirtualCh->astSoundTrack[0].u16AudioPid !=0))
    {
        DBG_AUDIOONLY(printf("\r\ng_bRadioChannel=TRUE");)
        g_bRadioChannel = TRUE;
        MApp_StartAudioOnlyMonitor();
    }
    else
    {
        DBG_AUDIOONLY(printf("\r\ng_bRadioChannel=FALSE");)
        g_bRadioChannel = FALSE;
        MApp_StopAudioOnlyMonitor();
    }
    //enAudioOnly  = AUDIO_ONLY_OFF;//for cus01x display,
  #elif (ENABLE_AUDIO_ONLY_CUSTOMERMODE == 1)
    //MApp_UiMenuFunc_SetAudioOnlyItem();
  #endif

#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("EnCh_A - 27" );
#endif


    if( /*(IsDTVInUse())*/
        (IsAtscInUse())
        &&((pstVirtualCh->u16VideoPid==0) || (pstVirtualCh->u16ScrambleChStatus && SCRAMBLE_VIDEO))
        && (pstVirtualCh->astSoundTrack[0].u16AudioPid !=0))
    {
        if(!MApp_Aud_GetMuteStatus())
        {
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYSYNC_MUTEOFF, E_AUDIOMUTESOURCE_ATV);
            MApi_AUDIO_SPDIF_SetMute(FALSE);
        }
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
    }

#if ENABLE_PVR
    g_u16Current_PCRPID = pstVirtualCh->u16PcrPid ;
    g_u16Current_PVR_VideoPID = pstVirtualCh->u16VideoPid;
    g_u16Current_PVR_AudioPID = pstVirtualCh->astSoundTrack[0].u16AudioPid;
    g_wCurrent_AudioType = pstVirtualCh->astSoundTrack[0].u16AudStreamType;
  //  g_eCurrent_PVR_VideoType = g_eCodecType;
    g_u16Current_AudioDescriptorPID = pstVirtualCh->astSoundTrack[0].u16AudioPid;;
#endif

#if(CHAKRA3_AUTO_TEST)
    AT_LOG("EnableChannel end");
#endif

#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("EnCh_A - End");
#endif
#if (ENABLE_CHCHANGETIME)
     printf("\n>>>[ChChangeTime][End_EnableCH]=[%d]\r\n",msAPI_Timer_DiffTimeFromNow(gU32ChChangeTime));
     gbReadyTimingMonitorFlag = TRUE;
#endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END(););
}

/************************************************************************************/

void MApp_ChannelChange_ChangeProgramList ( EN_ANT_TYPE enAntennaType )
{
    MApp_ChannelChange_DisableChannel(TRUE, MAIN_WINDOW);

    //store stChSetting to RamDisk
    MApp_DB_ATSC_SaveCurChSetting();

    MApp_DB_ATSC_InitBaseAddr( enAntennaType );

    //get stChSetting from 64K database
    MApp_DB_ATSC_LoadCurChSetting();
#if ENABLE_ATSC_CHLIST_DISP_TOGETHER
    if(stGenSetting.g_SysSetting.u16MainListLastWatched >(stChSettingDisp[ANT_AIR].u16MainListSrvNum + stChSettingDisp[ANT_CATV].u16MainListSrvNum) || stGenSetting.g_SysSetting.u16MainListLastWatched == 0)
        stGenSetting.g_SysSetting.u16MainListLastWatched = 1;

    MApp_ChanProc_ResetAllIndex(stGenSetting.g_SysSetting.u16MainListLastWatched);
#else
    if(stGenSetting.g_SysSetting.u16MainListLastWatched[ANT_TYPE] >stChSetting.u16MainListSrvNum ||stGenSetting.g_SysSetting.u16MainListLastWatched[ANT_TYPE] == 0)
        stGenSetting.g_SysSetting.u16MainListLastWatched[ANT_TYPE] = 1;

    MApp_ChanProc_ResetAllIndex(stGenSetting.g_SysSetting.u16MainListLastWatched[ANT_TYPE]);
#endif
    if(MApp_ChanProc_RefreshChannelBuffer(MAIN_LIST))
    {
        MApp_ChannelChange_EnableChannel_ATSC();
    }

}

//------------------------------------------------------------------------------

#undef  MAPP_CHANNEL_CHANGEGE_C

