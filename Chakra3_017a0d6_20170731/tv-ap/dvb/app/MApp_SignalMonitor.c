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

#define MAPP_SIGNAL_MONITOR_C

/******************************************************************************/
/*                            Header Files                                    */
/******************************************************************************/
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"

// Common Definition
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "msAPI_Video.h"
#include "msAPI_Timer.h"
#include "msAPI_DTVSystem.h"
#if (ENABLE_CI)
#include "msAPI_CI.h"
#endif
#include "msAPI_audio.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_SignalMonitor.h"
#include "MApp_TV.h"
#include "MApp_AnalogInputs.h"

#include "MApp_Scan.h"
#include "MApp_ChannelChange.h"
#include "MApp_GlobalVar.h"
#include "MApp_Audio.h"
#include "MApp_MVDMode.h"
#include "MApp_UiEpg.h"
#include "MApp_MultiTasks.h"

#if (ENABLE_DTV_EPG)
#include "mapp_eit.h"
#endif

#if (ENABLE_TTX)
#include "mapp_ttx.h"
#endif
#include "MApp_ATVProc.h"
#include "MApp_PlayCard.h"

#if ENABLE_DVB
//#include "MApp_Dvb_SI.h"
#endif

#if ( ((BRAZIL_CC))||(ATSC_CC == ATV_CC))
#include "mapp_closedcaption.h"
#endif
#include "MApp_UiMenuDef.h" //ZUI:
#include "MApp_GlobalFunction.h"
#if MHEG5_ENABLE
#include "MApp_MHEG5_Main.h"
#endif
#if ENABLE_PVR
#include "MApp_PVR.h"
#endif
#include <string.h>
#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
#include "ZUI_exefunc.h"
#include "MApp_ZUI_Main.h"
#endif
#if ENABLE_OAD
#include "MApp_OAD.h"
#endif

#if ENABLE_PIP
#include "MApp_PIP.h"
#endif

#include "MApp_ParentalRating.h"

#include "ZUI_exefunc.h"

#if ENABLE_ATSC
#include "msAPI_Tuner_ATSC.h"
#endif

#if(CHAKRA3_AUTO_TEST)
#include "MApp_AutoTest.h"
#endif

/********************************************************************************/
/*                              Macro                                           */
/********************************************************************************/
#define SIGNAL_MONITOR_DBG(y) //y


/********************************************************************************/
/*                     Local                                                      */
/********************************************************************************/
static U32 u32SignalMonitorTimer; //ms
static U32 u32SignalMonitorPeriod; //ms
static EN_SIGNAL_LOCK_STATUS enPrevSignalLockStatus;
#if (ENABLE_OAD && ENABLE_DVB)
static U32 enFrotEndLockSignalLossTimer;
#endif
#if ENABLE_DTV
static BOOLEAN fTmpCurScrambleFlag;
#endif
#if ENABLE_CI
static BOOLEAN _bCITSState = 0;
static U32 _u32CITimer=0;
#define SIGNAL_CHK_TIME_CI_STATE          3000 //ms    //CUS03 Spec.
#endif
//////////////////////////////////////////////////////////////////////////////////////////
#define SIGNAL_CHK_TIME_LOCK_STATE          100 //ms    //CUS03 Spec.
#define SIGNAL_CHK_TIME_UNLOCK_STATE        300 //ms    //CUS03 Spec.
#define SIGNAL_CHK_TIME_ANALOG_LOCK_STATE   500 //ms    //CUS03 Spec.
#define SIGNAL_CHK_TIME_ANALOG_UNLOCK_STATE 500 //ms    //CUS03 Spec.
#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
static BOOLEAN _bSignal_lost_lock;
#endif


static U32 u32AudioReadyTimer;

void MApp_SignalMonitor_Init(void)
{
    enFrotEndLockStatus = FRONTEND_UNKNOWN;
    u32SignalMonitorPeriod = SIGNAL_CHK_TIME_LOCK_STATE;
    enPrevSignalLockStatus = SIGNAL_UNKNOWN;
    u32SignalMonitorTimer = msAPI_Timer_GetTime0();
#if ENABLE_CI
    _u32CITimer=0;
#endif

  #if (ENABLE_DTV_EPG)
    MApp_EIT_All_Sche_ResetFilter();
  #endif  //#if (ENABLE_DTV_EPG)
}

void MApp_Set_Audio_Mute_Timer(BOOLEAN bStartTimer)
{
    if(bStartTimer)
        u32AudioReadyTimer=msAPI_Timer_GetTime0();
    else
        u32AudioReadyTimer=0;
}

#if ENABLE_DVB
void MApp_AudioMuteMonitor(void)
{
#if ENABLE_MEDIA_BROADCAST
    if(u32AudioReadyTimer && msAPI_Timer_DiffTimeFromNow(u32AudioReadyTimer) > 1000)
#else
    if(u32AudioReadyTimer && msAPI_Timer_DiffTimeFromNow(u32AudioReadyTimer) > 10000)
#endif
    {
        //if(enMVDVideoStatus != MVD_GOOD_VIDEO && IS_MADGOOD())
        if(enMVDVideoStatus != MVD_GOOD_VIDEO && MApi_AUDIO_IsMadLock())
        {
            if(!MApp_SI_Is_Running(NULL)&& (MApp_SI_CheckMHEG5Status() == SI_MHEG5_DISABLE))
            {
                return;
            }
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            u32AudioReadyTimer=0;
        }
    }
}

#define SIGNAL_MONITOR_TRACE()   //printf("SIG_MONITOR -%u at %u\n", __LINE__, MsOS_GetSystemTime() )
void MApp_SignalMonitor(void)
{
    BOOLEAN Check_FE_Result;
#if ENABLE_DTV
    MEMBER_SERVICETYPE bServiceType = msAPI_CM_GetCurrentServiceType();
#endif

#if ENABLE_CI
    if( (_bCITSState != msAPI_CI_CardDetect()) )
    {
        _bCITSState=msAPI_CI_CardDetect();
        if(_bCITSState)
        {
            _u32CITimer=msAPI_Timer_GetTime0();
        }
        else
        {
            _u32CITimer=0;
        }
    }
    if(_u32CITimer)
    {
        if( msAPI_Timer_DiffTimeFromNow(_u32CITimer) < SIGNAL_CHK_TIME_CI_STATE)
        {
            return;
        }
        else
        {
            _u32CITimer=0;
        }
    }
#endif


//    U16 u16CurPosition = msAPI_CM_GetCurrentPosition(bServiceType);
    Check_FE_Result = FALSE;

    if(msAPI_Timer_DiffTimeFromNow(u32SignalMonitorTimer) > u32SignalMonitorPeriod) //unit = ms
    {
	#if ENABLE_DTV
      #if (ENABLE_PIP)
        if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
            ||(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) && (MApp_Get_PIPMode() != EN_PIP_MODE_OFF)))
      #else
        if( IsDTVInUse() )
      #endif
        {
            SIGNAL_MONITOR_TRACE();

            if( msAPI_Tuner_CheckLock( &Check_FE_Result,FALSE) == FALSE )
            {
                SIGNAL_MONITOR_TRACE();
                SIGNAL_MONITOR_DBG(printf("FE Fail!\n"));
                if(enFrotEndLockStatus == FRONTEND_LOCK || enFrotEndLockStatus == FRONTEND_UNKNOWN)
                {
                    #if PLAYCARD_DISABLE // if you want use play card turn off this
                        enFrotEndLockStatus = FRONTEND_UNLOCK;
                    #else
                    enFrotEndLockStatus = FRONTEND_LOCK;
                    #endif
                    u32SignalMonitorPeriod = SIGNAL_CHK_TIME_UNLOCK_STATE; //ms
                }
            }
            else
            {
                if(Check_FE_Result==FE_LOCK)
                {
                    SIGNAL_MONITOR_TRACE();
                    if(enFrotEndLockStatus == FRONTEND_UNLOCK || enFrotEndLockStatus == FRONTEND_UNKNOWN)
                    {
                        enFrotEndLockStatus = FRONTEND_LOCK;
                        u32SignalMonitorPeriod = SIGNAL_CHK_TIME_LOCK_STATE;
                #if (ENABLE_AUTOTEST || ENABLE_BOOTTIME)
                        if (gbBootTimeFinish == FALSE)
                        {
                            PRINT_AUTOTEST_CHECKPT_TIME("start video decoder");
                        }
                #endif
                    }
                }
                else
                {
                    SIGNAL_MONITOR_TRACE();
                    if(enFrotEndLockStatus == FRONTEND_LOCK || enFrotEndLockStatus == FRONTEND_UNKNOWN)
                    {
					#if PLAYCARD_DISABLE // if you want use play card turn off this
						enFrotEndLockStatus = FRONTEND_UNLOCK;
					#if ENABLE_OAD
						enFrotEndLockSignalLossTimer = msAPI_Timer_GetTime0();
					#endif
					#else
						enFrotEndLockStatus = FRONTEND_LOCK;
					#endif
                        u32SignalMonitorPeriod = SIGNAL_CHK_TIME_UNLOCK_STATE; //ms
                    }
                }
            }
        }
        else
	#endif
        {
          #if 0 //Modified by coverity
            Check_FE_Result = FE_LOCK;//Temp

            if(Check_FE_Result == FE_LOCK)
            {
                enFrotEndLockStatus = FRONTEND_LOCK;
                u32SignalMonitorPeriod=SIGNAL_CHK_TIME_ANALOG_LOCK_STATE;   //ms
            }
            else
            {
                u32SignalMonitorPeriod = SIGNAL_CHK_TIME_ANALOG_UNLOCK_STATE;
                #if PLAYCARD_DISABLE // if you want use play card turn off this
                enFrotEndLockStatus = FRONTEND_UNLOCK;
                #else
                enFrotEndLockStatus = FRONTEND_LOCK;
                #endif
            }
          #else
            enFrotEndLockStatus = FRONTEND_LOCK;
            u32SignalMonitorPeriod=SIGNAL_CHK_TIME_ANALOG_LOCK_STATE;   //ms
          #endif
        }

        if(MApp_GetSignalStatus()==SIGNAL_LOCK)
        {
            SIGNAL_MONITOR_TRACE();

            if(enPrevSignalLockStatus == SIGNAL_UNLOCK || enPrevSignalLockStatus == SIGNAL_UNKNOWN)
            {
#if ENABLE_DTV
              #if (ENABLE_PIP)
                if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
                    ||(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) && (MApp_Get_PIPMode() != EN_PIP_MODE_OFF)))
              #else
                if(IsDTVInUse())
              #endif
                {
                    //bServiceType = msAPI_CM_GetCurrentServiceType();
                    //u16CurPosition = msAPI_CM_GetCurrentPosition(bServiceType);

                  #if 1//modify by leo.wang 2007/11/26
                    //if radio channel, unmute audio directly.
                    //if still picture, unmute audio after mvd get sync in MApp_ScreenMuteMonitor()
                    if(bServiceType == E_SERVICETYPE_RADIO &&
                        MApp_TV_IsProgramRunning()) //audio only condition.
                  #else
                    if((bServiceType == E_SERVICETYPE_RADIO) || //audio only condition.
                        (msAPI_CM_GetProgramAttribute(bServiceType,u16CurPosition, E_ATTRIBUTE_IS_STILL_PICTURE) == TRUE))//still picture channel.
                  #endif
                    {
                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYSYNC_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    }

                    SIGNAL_MONITOR_TRACE();

                #if (ENABLE_DTV_EPG)
                    MApp_EIT_All_Sche_ResetFilter();
                #endif  //#if (ENABLE_DTV_EPG)

                    SIGNAL_MONITOR_TRACE();

            #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
                    if (OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY)
                    {
                        if (LOSS_SIGNAL_CONFIRM_MSG == MApp_DTV_Scan_GetLossSignalState())
                        {
                            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
                        }
                        MApp_DTV_Scan_SetLossSignalState(LOSS_SIGNAL_INIT);
                        _bSignal_lost_lock = FALSE;
                    }
            #endif
                    SIGNAL_MONITOR_TRACE();

                    if( //stSystemInfo[MAIN_WINDOW].u8PanelPowerStatus & PANEL_POWER_BLUESCREEN
                        ( TRUE == MApi_XC_Sys_Get_BlueScreenStatus(MAIN_WINDOW) )
                    #if (ENABLE_PIP)
                        //|| (IsPIPSupported() && (stSystemInfo[SUB_WINDOW].u8PanelPowerStatus & PANEL_POWER_BLUESCREEN))
                        || (IsPIPSupported() && ( TRUE == MApi_XC_Sys_Get_BlueScreenStatus(SUB_WINDOW) ) )
                    #endif
                        )
                    {
                        MApp_ChannelChange_EnableAV();
                    }

                    SIGNAL_MONITOR_TRACE();

                    MApp_TV_Force2MonitorIdleModeWindows();
                    fTmpCurScrambleFlag = FALSE;

                    SIGNAL_MONITOR_TRACE();

                  #if(ENABLE_TTX_SHOW_OFF_SIGNAL)//Refresh TTX when signal is on
                    MApp_TTX_TeletextCommand(TTX_TV);
                    MApp_TTX_Reflesh();
                  #endif
                    SIGNAL_MONITOR_TRACE();
                }
#endif

                enPrevSignalLockStatus=SIGNAL_LOCK;

            #if (ENABLE_PIP)
                //This is a patch for TV Monitor. MApp_SI_Is_Running() always return TRUE, and
                //  it is used for special case(Jupiter said). So, SYS_SCREEN_SAVER_TYPE cannot
                //  be set to EN_SCREENSAVER_NULL when cable is inserted to the tuner when PIP
                //  is enabled. (May 5, 2009)
                if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
                {
                    if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))
                        && SYS_SCREEN_SAVER_TYPE(SUB_WINDOW) != EN_SCREENSAVER_NULL)
                    {
                        SYS_SCREEN_SAVER_TYPE(SUB_WINDOW) = EN_SCREENSAVER_NULL;
                    }
                }
            #endif

                SIGNAL_MONITOR_TRACE();

                MApp_ParentalRating_PasswordInputMessageHandle(_ON);

                SIGNAL_MONITOR_TRACE();

                SIGNAL_MONITOR_DBG(printf("Signal Recovery!\n"));
            }
        }
        else if(MApp_GetSignalStatus()==SIGNAL_UNLOCK)
        {
            SIGNAL_MONITOR_TRACE();

            if(enPrevSignalLockStatus == SIGNAL_LOCK || enPrevSignalLockStatus == SIGNAL_UNKNOWN)
            {

             #if (ENABLE_PIP)
                if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
                    ||(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) && (MApp_Get_PIPMode() != EN_PIP_MODE_OFF)))
             #else
                if(IsDTVInUse())
             #endif
                {

            #if MHEG5_ENABLE
                #if MHEG5_WITH_OSD
                    if(msAPI_MHEG5_checkGoBackMHEG5()==true)
                        MApp_MHEG5_Force_Exit();
                #endif
            #endif

                    SIGNAL_MONITOR_TRACE();

        #if 0//ENABLE_PVR
                    if (!MApp_PVR_IsPlaybacking() && !MApp_PVR_IsRecording())
        #endif

                #if( BRAZIL_CC )
                    if( msAPI_SRC_IS_SBTVD_InUse() )
                    {
                        if ((IsDTVInUse() && DB_CC_SETTING.enDTVCaptionType != DTV_CAPTION_OFF)
                          ||(IsATVInUse() && DB_CC_SETTING.enATVCaptionType != ATV_CAPTION_TYPE_OFF))
                        {
                            if(MApp_CC_GetInfo(CC_SELECTOR_STATUS_CODE) == STATE_CAPTION_PARSER)
                            {
                                MApp_CC_StopParser();
                                MApp_Dmx_PES_Stop();
                            }
                        }
                    }
                #endif

                    SIGNAL_MONITOR_TRACE();

                    {
                        if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) )
                        {
                          #if ENABLE_PVR
                            if (!MApp_PVR_IsPlaybacking() && !MApp_PVR_IsRecording()) //to prevent blue screen when recording & playbacking
                          #endif
                            MApp_ChannelChange_DisableAV(MAIN_WINDOW);
                        }
                      #if (ENABLE_PIP)
                        if((MApp_Get_PIPMode() != EN_PIP_MODE_OFF) && IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) )
                        {
                            MApp_ChannelChange_DisableAV(SUB_WINDOW);
                        }
                      #endif
                    }

                    SIGNAL_MONITOR_TRACE();

                    MApp_TV_Force2MonitorIdleModeWindows();

                    SIGNAL_MONITOR_TRACE();
        #if ENABLE_TTX
			   #if(0 == ENABLE_TTX_SHOW_OFF_SIGNAL)//Don't exit TTX mode when signal is off
                    MApp_TTX_TeletextCommand(TTX_TV);
                    MApp_TTX_Reflesh();             //reset TTX status
			   #endif
        #endif
                }

                enPrevSignalLockStatus=SIGNAL_UNLOCK;

                MApp_ParentalRating_PasswordInputMessageHandle(_OFF);

                SIGNAL_MONITOR_DBG(printf("Signal Lost!\n"));
            }
#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
            else if(enPrevSignalLockStatus == SIGNAL_UNLOCK && _bSignal_lost_lock == FALSE)
            {
                if ((OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY))
                {
                    _bSignal_lost_lock = TRUE;
                }
            }
#endif
        }

        u32SignalMonitorTimer = msAPI_Timer_GetTime0();
    }

#if (ENABLE_OAD)
	if(enPrevSignalLockStatus == SIGNAL_UNLOCK && MApp_OAD_GetSignalForStandby()
		 &&(OSD_COUNTRY_SETTING == OSD_COUNTRY_NEWZEALAND)&& msAPI_Timer_DiffTimeFromNow(enFrotEndLockSignalLossTimer) > 30000)//MONITOR_DSI_TIME_OUT
	{
		enFrotEndLockSignalLossTimer = msAPI_Timer_GetTime0();
		MApp_OAD_SetMonitorState( EN_OAD_MONITOR_STATE_STOP);
	}
#endif
}
#endif

BOOLEAN MApp_Scramble_GetCurStatus(void)
{
#if ENABLE_DTV
  #if (ENABLE_PIP)
    if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
        ||(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) && (MApp_Get_PIPMode() != EN_PIP_MODE_OFF)))
  #else
    if(IsDTVInUse())
  #endif
    {
        //printf("Scram %bu\n",fTmpCurScrambleFlag);
        return fTmpCurScrambleFlag;
    }
    else
#endif
        return FALSE;
}

EN_SIGNAL_LOCK_STATUS MApp_GetSignalStatus_UnCheckMHEG5(void)
{
#if ENABLE_DTV
  #if (ENABLE_PIP)
    if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
        ||(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) && (MApp_Get_PIPMode() != EN_PIP_MODE_OFF)))
  #else
    if(IsDTVInUse())
  #endif
    {
        if(enFrotEndLockStatus == FRONTEND_LOCK)
        {
            //if(enMVDVideoStatus == MVD_GOOD_VIDEO || IS_MADGOOD())
            if(enMVDVideoStatus == MVD_GOOD_VIDEO || MApi_AUDIO_IsMadLock())
            {
                return SIGNAL_LOCK;
            }
        }
    }
#endif
    return SIGNAL_UNLOCK;
}

#if ENABLE_CI
static BOOLEAN MApp_SignalMonitor_CheckIfNeed2TryMPEG2( void )
{
    #define CIINFO_LENGTH 24
    U8 manufacturer[CIINFO_LENGTH];
    U8 product[CIINFO_LENGTH];
    U8 Info1[CIINFO_LENGTH];

    if(g_eCodecType == E_VDEC_CODEC_TYPE_MPEG2)
    {
        return FALSE;
    }

    else if( (g_eCodecType == E_VDEC_CODEC_TYPE_H264)
       #if ( CHIP_SUPPORT_HEVC ) //IMPLEMENT_DTV_H265
           ||(g_eCodecType == E_VDEC_CODEC_TYPE_HEVC)
       #endif
           )
    {
        if(msAPI_CI_CardDetect() == FALSE || msAPI_CI_GetCardState() != EN_MODULE_READY)
        {
            //printf("Not ready\n");
            return FALSE;
        }
        else
        {
            if(msAPI_Timer_DiffTimeFromNow( u32ChkTry2ChgMpeg2Time ) > 4000 &&
               msAPI_Timer_DiffTimeFromNow( u32ChkTry2ChgMpeg2Time ) < 5000)
            {
                U8 u8ManufacturerLen = CIINFO_LENGTH;
                U8 u8ProductLen = CIINFO_LENGTH;
                U8 u8Info1Len = CIINFO_LENGTH;

                msAPI_CI_GetCIS( manufacturer, &u8ManufacturerLen, product, &u8ProductLen, Info1, &u8Info1Len );
                //printf("%s:%s:%d:%d\n",manufacturer,product,bAVCH264,msAPI_CI_GetCardType());
                if(/*msAPI_CI_GetCardType()               == EN_SMARTCARD_TYPE_NEOTNT   &&*/
                   strcmp((char*)manufacturer,"NEOTION")== 0            &&
                   strcmp((char*)product,"NP4")         == 0)
                {
                    //printf("try mepg2\n");
                    return TRUE;
                }
                else
                {
                    //printf("Don't try\n");
                    return FALSE;
                }
            }
            else return FALSE;
        }

    }
    return FALSE;
}

static void MApp_SignalMonitor_ChangeMVD2MPEG2( void )
{
    SHOW_VIDEO_INFO(("MApp_SignalMonitor_ChangeMVD2MPEG2"));



    //printf("Switch MVD to MPEG2 to check again\n");
    msAPI_VID_Command( MSAPI_VID_STOP );
//    msAPI_VID_Command( MSAPI_VID_RESET );

    msAPI_VID_SetMappingAVCParameter(E_VDEC_CODEC_TYPE_MPEG2);

//    MAPI_VID_Init(msAPI_VID_GetCodecType(),FALSE);
    msAPI_VID_Init(FALSE, E_VDEC_SRC_MODE_DTV);

    MApp_VID_VariableInit();
    msAPI_VID_Command( MSAPI_VID_PLAY );
}
#endif

EN_SIGNAL_LOCK_STATUS MApp_GetSignalStatus(void)
{
#if ENABLE_DVB
    MEMBER_SERVICETYPE bServiceType = msAPI_CM_GetCurrentServiceType();
    U16 u16CurPosition = msAPI_CM_GetCurrentPosition(bServiceType);


#if (ENABLE_PIP)
    if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
    ||(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) && (MApp_Get_PIPMode() != EN_PIP_MODE_OFF)))
#else
    if( IsDTVInUse() )
#endif
    {
        if( enFrotEndLockStatus == FRONTEND_UNKNOWN )
        {
            fTmpCurScrambleFlag = FALSE;

        #if(CHAKRA3_AUTO_TEST&&ENABLE_AT_DEBUG_INPUT_SIGNAL)
            if( g_AT_bDebugInputSignal )
            {
                printf("1 enFrotEndLockStatus==FRONTEND_UNKNOWN\n");
            }
        #endif

            return SIGNAL_UNKNOWN;
        }
        else if( enFrotEndLockStatus == FRONTEND_UNLOCK )
        {
            fTmpCurScrambleFlag = FALSE;

        #if(CHAKRA3_AUTO_TEST&&ENABLE_AT_DEBUG_INPUT_SIGNAL)
            if( g_AT_bDebugInputSignal )
            {
                printf("1 enFrotEndLockStatus==FRONTEND_UNLOCK\n");
            }
        #endif

            return SIGNAL_UNLOCK;
        }
        else if( enFrotEndLockStatus == FRONTEND_LOCK ) //
        {
            if( enMVDVideoStatus == MVD_UNKNOWN_VIDEO)
            {
                if ( msAPI_CM_GetProgramAttribute(bServiceType, u16CurPosition, E_ATTRIBUTE_IS_SERVICE_ID_ONLY) == TRUE )
                {
                #if(CHAKRA3_AUTO_TEST&&ENABLE_AT_DEBUG_INPUT_SIGNAL)
                    if( g_AT_bDebugInputSignal )
                    {
                        printf("2 enMVDVideoStatus == MVD_UNKNOWN_VIDEO\n");
                    }
                #endif

                    return SIGNAL_UNLOCK;
                }

                if(bServiceType == E_SERVICETYPE_RADIO)
                {
                    //if((!IS_MADGOOD() || (!MApp_SI_Is_Running()))&& (MApp_SI_CheckMHEG5Status() == SI_MHEG5_DISABLE))
                    if((!MApi_AUDIO_IsMadLock() || (!MApp_TV_IsProgramRunning()))&& (MApp_SI_CheckMHEG5Status() == SI_MHEG5_DISABLE))
                    {
                        if(MApp_SI_CheckCurProgScramble())
                            fTmpCurScrambleFlag = TRUE;
                        else
                            fTmpCurScrambleFlag = FALSE;
                        //printf("audio unlock\n");

                    #if(CHAKRA3_AUTO_TEST&&ENABLE_AT_DEBUG_INPUT_SIGNAL)
                        if( g_AT_bDebugInputSignal )
                        {
                            printf("3 audio no lock\n");
                        }
                    #endif

                        return SIGNAL_UNLOCK;
                    }

                    //printf("audio lock\n");
                    //fTmpCurScrambleFlag = FALSE;
                    return SIGNAL_LOCK;
                }
                else
                {
                    if((MApp_SI_CheckCurProgScramble() || (!MApp_TV_IsProgramRunning())) && (MApp_SI_CheckMHEG5Status() == SI_MHEG5_DISABLE))
                    {
                        if( MApp_SI_CheckCurProgScramble() )
                        {
                          #if ENABLE_CI
                            if(MApp_SignalMonitor_CheckIfNeed2TryMPEG2() == TRUE)
                            {
                                MApp_SignalMonitor_ChangeMVD2MPEG2();
                                //printf("MVDVideoStatus %d\n",enMVDVideoStatus);
                                return SIGNAL_LOCK;
                            }
                            else
                          #endif
                            {
                                fTmpCurScrambleFlag = TRUE;
                                //printf("Vid unlock1\n");
                            #if(CHAKRA3_AUTO_TEST&&ENABLE_AT_DEBUG_INPUT_SIGNAL)
                                if( g_AT_bDebugInputSignal )
                                {
                                    printf("4 Scramble, \n");
                                }
                            #endif

                                return SIGNAL_UNLOCK;
                            }
                        }
                        else
                        {
                            fTmpCurScrambleFlag = FALSE;
                            //printf("Vid unlock\n");
                        #if(CHAKRA3_AUTO_TEST&&ENABLE_AT_DEBUG_INPUT_SIGNAL)
                            if( g_AT_bDebugInputSignal )
                            {
                                printf("5 Not Scramble, \n");
                            }
                        #endif

                            return SIGNAL_UNLOCK;
                        }
                    }

                  #if ENABLE_CI
                    if(MApp_SignalMonitor_CheckIfNeed2TryMPEG2() == TRUE)
                    {
                        MApp_SignalMonitor_ChangeMVD2MPEG2();
                    }
                  #endif
                    //printf("Vid lock\n");
                    return SIGNAL_LOCK;
                }
            }
            else if( enMVDVideoStatus == MVD_GOOD_VIDEO)
            {
                fTmpCurScrambleFlag = FALSE;
                if((!MApp_TV_IsProgramRunning())&& (MApp_SI_CheckMHEG5Status() == SI_MHEG5_DISABLE))
                {
                #if(CHAKRA3_AUTO_TEST&&ENABLE_AT_DEBUG_INPUT_SIGNAL)
                    if( g_AT_bDebugInputSignal )
                    {
                        printf("7 (!MApp_TV_IsProgramRunning()) \n");
                    }
                #endif

                    return SIGNAL_UNLOCK;
                }
                return SIGNAL_LOCK;
            }
        #if (MHEG5_ENABLE)
            else if( (enMVDVideoStatus == MVD_BAD_VIDEO && !g_MHEG5Video.bIFrame))
            {
                if((msAPI_MHEG5_IsRunning()||msAPI_MHEG5_checkGoBackMHEG5())&& msAPI_VID_GetPlayMode() != MSAPI_VID_PLAY)
                {
                    return SIGNAL_LOCK;
                }
                else
        #else
            else if( (enMVDVideoStatus == MVD_BAD_VIDEO ) )
            {
        #endif

                if( MApp_SI_CheckCurProgScramble() )
                {
                  #if ENABLE_CI
                    if(MApp_SignalMonitor_CheckIfNeed2TryMPEG2() == TRUE)
                    {
                        MApp_SignalMonitor_ChangeMVD2MPEG2();
                    }
                    else
                  #endif
                    {
                        fTmpCurScrambleFlag = TRUE;

                    #if(CHAKRA3_AUTO_TEST&&ENABLE_AT_DEBUG_INPUT_SIGNAL)
                        if( g_AT_bDebugInputSignal )
                        {
                            printf("8 MVD_BAD_VIDEO && Scramble\n");
                        }
                    #endif

                        return SIGNAL_UNLOCK;
                    }

                }

                if((!MApp_TV_IsProgramRunning())&& (MApp_SI_CheckMHEG5Status() == SI_MHEG5_DISABLE))
                {
                #if(CHAKRA3_AUTO_TEST&&ENABLE_AT_DEBUG_INPUT_SIGNAL)
                    if( g_AT_bDebugInputSignal )
                    {
                        printf("9 MVD_BAD_VIDEO && !MApp_TV_IsProgramRunning()\n");
                    }
                #endif

                    return SIGNAL_UNLOCK;
                }

                //if(IS_MADGOOD())return SIGNAL_LOCK;
                if( MApi_AUDIO_IsMadLock() )
                    return SIGNAL_LOCK;

            #if(CHAKRA3_AUTO_TEST&&ENABLE_AT_DEBUG_INPUT_SIGNAL)
                if( g_AT_bDebugInputSignal )
                {
                    printf("10 audio no lock\n");
                }
            #endif

                return SIGNAL_UNLOCK;

            }

            return SIGNAL_LOCK;
        }

    }
#endif

    return SIGNAL_UNKNOWN;
}

#if( ENABLE_DVB )

#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
BOOLEAN MApp_Is_SignalLostLock(void)
{
    if (OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY)
    {
        return _bSignal_lost_lock;
    }
    return FALSE;
}
void MApp_Reset_SignalLostLockStatus(void)
{
     _bSignal_lost_lock = FALSE;
}
#endif

#endif // #if( ENABLE_DVB )

#if (ENABLE_ATSC)
#include "MApp_Psip.h"
#include "MApp_Scan.h"
#include "MApp_VChip.h"
#include "MApp_ChannelProc_ATSC.h"

#define SIGNAL_CHECK_DBG(y) //y

#define MAX_SIGNAL_LOST_COUNT    4

static U8 u8SignalLostCounter;
static U32 u32SignalCheckTimer; //ms
static U32 u32SignalCheckPeriod; //ms

extern MS_U8 bPreviousSoundMode, bCurrentSoundMode;

void MApp_SignalCheck_Init(void)
{
    u8SignalLostCounter     = 0;
    fSignalLockStatus       = FE_LOCK;
    u32SignalCheckPeriod    = SIGNAL_CHK_TIME_LOCK_STATE;
    u32SignalCheckTimer     = msAPI_Timer_GetTime0();
#if 0//def PATCH_BBY_VP403_TIMING_CHANGE
    u8VP403MonitorState=0;
#endif
}

#define DEBUG_ATSC_SIGNAL_CHECK_TIME    0

void MApp_SignalCheckMonitor(void)
{
#if(DEBUG_ATSC_SIGNAL_CHECK_TIME)
    U32 u32Time_Start = MsOS_GetSystemTime();
#endif

#if 0//def PATCH_BBY_VP403_TIMING_CHANGE
  #if (FRONTEND_DEMOD_TYPE == SAMSUNG_S5H1409_DEMODE)
    if(IsDTVInUse())
    {
        if ( msAPI_Tuner_CheckSignalSNR() == SIGNAL_VERY_STRONG )
        {
            if ( u16StrongSignalCount < 200 ) u16StrongSignalCount++;
        }
        else
        {
            if ( u16StrongSignalCount > 0 ) u16StrongSignalCount--;
        }
        switch ( u8VP403MonitorState)
        {
            case 0: // initial
                u8FreezeImageCount=0;
                u16StrongSignalCount=0;
                u8VP403MonitorState=1;
                break;
            case 1: // wait signal stable
                if ( u16StrongSignalCount >=200 )
                {
                    u8VP403MonitorState=2;
                }
                break;
            case 2: // strong signal state
                if ( u16StrongSignalCount >=50 )
                {
                    if (MApp_Check_FE_Status( MApp_ChanProc_GetCurChannelPointer()) == FE_LOCK)
                    {
                        u8FreezeImageCount=0;
                    }
                    else
                    {
                        if ( u8FreezeImageCount <5)
                            u8FreezeImageCount++;
                        if ( u8FreezeImageCount >=5)
                        {
                            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, 2000, MAIN_WINDOW);
                            u8VP403MonitorState=0;
                        }
                    }
                }
                else{
                    u8VP403MonitorState=1;
                }
                break;
            default:
                u8VP403MonitorState=0;
                break;
        }
    }
  #endif
#endif


    // For the first time after init
    if( IsDTVInUse() )// ATV
    {
        if( fSignalLockStatus == FE_LOCK )
        {
            u32SignalCheckPeriod = SIGNAL_CHK_TIME_LOCK_STATE;
        }
        else
        {
            u32SignalCheckPeriod = SIGNAL_CHK_TIME_UNLOCK_STATE;
        }
    }
    else // ATV
    {
        if( fSignalLockStatus == FE_LOCK )
        {
            u32SignalCheckPeriod = SIGNAL_CHK_TIME_ANALOG_LOCK_STATE;
        }
        else
        {
            u32SignalCheckPeriod = SIGNAL_CHK_TIME_ANALOG_UNLOCK_STATE;
        }
    }

    if( msAPI_Timer_DiffTimeFromNow(u32SignalCheckTimer) > u32SignalCheckPeriod ) //unit = ms
    {
        if( MApp_Check_FE_Status( MApp_ChanProc_GetCurChannelPointer() ) == FE_LOCK )
        {
            SIGNAL_CHECK_DBG( printf(" FE Lock; "); );
            u8SignalLostCounter = 0;
            if(fSignalLockStatus == FE_NOT_LOCK)
            {
                SIGNAL_CHECK_DBG(printf(" fSignalLockStatus == FE_NOT_LOCK; "););
                if( IsDTVInUse() )
                {
                    #ifdef LOCK_USE_BLACK_VIDEO
                    MApp_VID_VariableInit();
                    #endif
                    MApp_ChannelChange_EnableAV();
                    MApp_SignalCheck_Init();
                    if(!g_bInputBlocked&&(!MApp_VChip_GetCurVChipBlockStatus()))
                    {
                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYSYNC_MUTEOFF, E_AUDIOMUTESOURCE_AC3);

                        MApi_AUDIO_SPDIF_SetMute(FALSE);
                    }
                }
                else
                {
                    // check MTS before umute...
                  #if 0
                    MApi_AUDIO_SIF_GetSoundMode();
                    if ( MApp_AUDIO_IsSifSoundModeExist( stGenSetting.g_SoundSetting.Mts ) )
                    {
                        g_u8AudLangSelected = stGenSetting.g_SoundSetting.Mts;
                        MApi_AUDIO_SIF_SetSoundMode(g_u8AudLangSelected);
                    }
                    else if( MApp_AUDIO_IsSifSoundModeExist( SOUND_MTS_STEREO ) )
                    {
                        g_u8AudLangSelected = SOUND_MTS_STEREO;
                        MApi_AUDIO_SIF_SetSoundMode(g_u8AudLangSelected);
                    }
                  #else
                    g_u8AudLangSelected = stGenSetting.g_SoundSetting.Mts;
                    MApi_AUDIO_SIF_SetSoundMode(MApp_SoundMtsSifSoundModeTrans(g_u8AudLangSelected));
                    bPreviousSoundMode = bCurrentSoundMode;
                  #endif

                    MApp_ChannelChange_EnableAV();
                    //MApp_AnalogInputs_Force2MonitorWindows();
                    fSignalLockStatus = FE_LOCK;
                    u32SignalCheckPeriod=SIGNAL_CHK_TIME_ANALOG_LOCK_STATE;   //ms
                }

                SIGNAL_CHECK_DBG(printf("Signal Recovery!\r\n"));
            }
        }
        else
        {
            SIGNAL_CHECK_DBG(printf(" FE No Lock; "););
            if(fSignalLockStatus == FE_LOCK)
            {
                SIGNAL_CHECK_DBG(printf(" fSignalLockStatus == FE_LOCK; "););
                if( IsDTVInUse() )
                {

                  #if ENABLE_ATV_CHANNEL_CHANGE_FINETUNING
                    MApp_SetChChangeState(FALSE);
                  #endif

                    u8SignalLostCounter++;
                    if(u8SignalLostCounter > MAX_SIGNAL_LOST_COUNT)
                    {
                        SIGNAL_CHECK_DBG(printf("DTV Signal Lost!\r\n"));
                        MApp_ChannelChange_DisableAV(MAIN_WINDOW);
                        fSignalLockStatus = FE_NOT_LOCK;

                      #if (ENABLE_MEXICO_VCHIP)
                        u8CurrentRrtRegionNo = 0;
                        u8LastRrtRegionNo = 0;
                      #endif
                    }
                    u32SignalCheckPeriod = SIGNAL_CHK_TIME_UNLOCK_STATE; //ms
                }
                else
                {
                    #ifdef DISABLE_ATV_NOSIGNAL_SNOW
                    SIGNAL_CHECK_DBG(printf("ATV Signal Lost!\r\n"));
                    MApp_ChannelChange_DisableAV(MAIN_WINDOW); // ATV needs snow screen when it doesn't have signal.
                    #endif
                    u32SignalCheckPeriod = SIGNAL_CHK_TIME_ANALOG_UNLOCK_STATE;
                    fSignalLockStatus = FE_NOT_LOCK;
                }

            }
        }
        u32SignalCheckTimer = msAPI_Timer_GetTime0();
    }

#if(DEBUG_ATSC_SIGNAL_CHECK_TIME)
    U32 u32Time_End = MsOS_GetSystemTime();
    U32 u32Time_Use = msAPI_Timer_DiffTime_2(u32Time_Start, u32Time_End);
    if( u32Time_Use > 20 )
    {
        printf(" SignalCheck use %ums\n", u32Time_Use);
    }
#endif

}

U8 MApp_GetSignalLockStatus(void)
{
    return fSignalLockStatus;
}

#endif // #if (ENABLE_ATSC)

//******************************************************************************

#undef MAPP_SIGNAL_MONITOR_C

