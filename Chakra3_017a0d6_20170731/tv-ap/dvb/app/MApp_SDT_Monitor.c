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
#define MAPP_SDT_MONITOR_C

//==============================================================================
/*                            Header Files                                      */
//==============================================================================

// Global Layer
#include "Board.h"

#if(ENABLE_DVB)

#include "datatype.h"
#include "debug.h"

#include "msAPI_MW_GlobalSt.h"


#include "msAPI_Global.h"
#include "msAPI_Timer.h"

#include "msAPI_DTVSystem.h"
#include "msAPI_audio.h"
#include "apiXC_Sys.h"


//#include "mapp_si.h"
#include "MApp_Dvb_SI.h"

#include "MApp_GlobalFunction.h"
#include "MApp_SDT_Monitor.h"

#include "MApp_ChannelChange.h"
#include "MApp_SignalMonitor.h"


//=============================================================================

#define MAX_SI_SDT_WAIT_FREECA_TIME     1000 // Wait MAD/MVD decode time when scramble


//-----------------------------------------------------------------------------------------

static U32 _u32SdtFreeCaCheckTime = 0;
static U8 _u8SdtFreeCaCheckTimes = 0;
static SI_SDT_RUNNINGSTATUS enPreSdtRunniungSts = SI_SDT_RUN_RUNNING;

#if ENABLE_SDT_OTHER_MONITOR
U32 g_SDT_u32CheckMovServieTimer;
//static U16 _u16UserSID=0;
//static U16 _u16UserLCN=0;
//static MEMBER_SERVICETYPE _eUserServiceType;
static MEMBER_SERVICETYPE g_SDT_eUserServiceType;
static U16 g_SDT_u16UserSID = 0;
static U16 g_SDT_u16UserLCN = 0;
#endif


//-----------------------------------------------------------------------------------------

#if(SDT_AUTO_CHANGE_CH_TO_ORIGINAL)
static U16 s_SDT_u16OrgServiceId = 0;
static U16 s_SDT_u16OrgTS_Id = 0;
static U16 s_SDT_u16OrgON_Id = 0;
void MApp_SDT_ResetAutoChangeChVar(void)
{
    s_SDT_u16OrgServiceId = 0;
    s_SDT_u16OrgTS_Id = 0;
    s_SDT_u16OrgON_Id = 0;
}
#endif

//****************************************************************************
/// enPreSdtRunniungSts variable initilize
/// @return none
//****************************************************************************
void MApp_SDT_ResetRunningStatus(void)
{
    enPreSdtRunniungSts = SI_SDT_RUN_RUNNING;
}

static void _MApp_SDT_FreeCAModeCheck(void)
{
    //BOOLEAN bReplaceSuccess = TRUE;
    MEMBER_SERVICETYPE eGotServiceType;
    U16 u16GotPosition;
    RP_SERVICE_INFO stRPServiceInfo;

    MApp_SI_Get_Service_Replacement_Info(&stRPServiceInfo);

    if ((SI_SDT_FREECA_FTA == stRPServiceInfo.u8FreeCAMode) ||
        (stRPServiceInfo.u8LinkageType != CA_REPLACEMENT_SERVICE) ||
        (stRPServiceInfo.u8Ser_Replacement != TRUE))
    {
        return;
    }
    else
    {
        if (_u32SdtFreeCaCheckTime == 0)
        {
            _u32SdtFreeCaCheckTime = msAPI_Timer_GetTime0();
            if (MApp_GetSignalStatus_UnCheckMHEG5() == SIGNAL_LOCK)
            {
                _u8SdtFreeCaCheckTimes=0;
                return;
            }

            _u8SdtFreeCaCheckTimes+=3;
        }
        else
        {
            if (msAPI_Timer_DiffTimeFromNow(_u32SdtFreeCaCheckTime) < MAX_SI_SDT_WAIT_FREECA_TIME)
            {
                // Need to wait MVD/MAD check.
                return;
            }
            else
            {
                _u32SdtFreeCaCheckTime = msAPI_Timer_GetTime0();
                //g_stSIInfo.stSdtMonInfo.stSdtLN.u8Ser_Replacement = FALSE;
                if (MApp_GetSignalStatus_UnCheckMHEG5() == SIGNAL_LOCK)
                {
                    _u8SdtFreeCaCheckTimes=0;
                    return;
                }
                _u8SdtFreeCaCheckTimes++;
            }
        }
    }

    if(_u8SdtFreeCaCheckTimes < 6)
    {
        return;
    }

    _u8SdtFreeCaCheckTimes=0;

    switch ( stRPServiceInfo.u8FreeCAMode )
    {
        default:
        case SI_SDT_FREECA_FTA:
            break;
        case SI_SDT_FREECA_SCR:
            if (stRPServiceInfo.u8Ser_Replacement == TRUE)
            {
                if (TRUE == msAPI_CM_GetServiceTypeAndPositionWithIDs(stRPServiceInfo.u16TSId, stRPServiceInfo.u16ONId, stRPServiceInfo.u16ServiceId, 1, &eGotServiceType, &u16GotPosition, TRUE))
                {
                    if (TRUE != MApp_ChannelChange_ChangeSpeciChannel(stRPServiceInfo.u16ServiceId, stRPServiceInfo.u16ONId, stRPServiceInfo.u16TSId, TYPE_CHANNEL_CHANGE_SER_ID, TRUE, TRUE))
                    {
                        // ??
                    }
                }
            }
            break;
    }

}

void MApp_SDT_Set_AVMUTE(BOOLEAN bAVMute)
{
    if( bAVMute )
    {
        //if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
        {
            //if (!(stSystemInfo[MAIN_WINDOW].u8PanelPowerStatus & PANEL_POWER_BLUESCREEN))
            {
                msAPI_Scaler_SetBlueScreen( ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
            }
        }

        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
    }
    else
    {
        //if (stSystemInfo.u8PanelPowerStatus & PANEL_POWER_BLUESCREEN)
        {
            msAPI_Scaler_SetBlueScreen( DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
        }

        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
    }
}

static void _MApp_SDT_RunningStatusCheck( void )
{
    static U32 _s_SDT_RunningStatusCheck_LastTime;

    if( msAPI_Timer_DiffTime_2(_s_SDT_RunningStatusCheck_LastTime, MsOS_GetSystemTime()) < 500 )
    {
        return;
    }

    _s_SDT_RunningStatusCheck_LastTime = MsOS_GetSystemTime();
    //printf("_s_SDT_RunningStatusCheck_LastTime=%u\n", _s_SDT_RunningStatusCheck_LastTime);

    //BOOLEAN bReplaceSuccess = TRUE;
    MEMBER_SERVICETYPE eGotServiceType;
    U16 u16GotPosition;
    RP_SERVICE_INFO stRPServiceInfo;

    MApp_SI_Get_Service_Replacement_Info(&stRPServiceInfo);

    if (stRPServiceInfo.u8Ser_Replacement == TRUE && stRPServiceInfo.u8LinkageType == NORDIG_SIMULCAST_REPLACEMENT_SERVICE)
    {
        if (TRUE == msAPI_CM_GetServiceTypeAndPositionWithIDs(stRPServiceInfo.u16TSId, stRPServiceInfo.u16ONId, stRPServiceInfo.u16ServiceId, 1, &eGotServiceType, &u16GotPosition, TRUE))
        {
            MEMBER_SERVICETYPE eTempCurServiceType;
            U16 u16TempCurPosition;

            eTempCurServiceType = msAPI_CM_GetCurrentServiceType();
            u16TempCurPosition = msAPI_CM_GetCurrentPosition(eTempCurServiceType);
            if (TRUE == MApp_ChannelChange_ChangeSpeciChannel(stRPServiceInfo.u16ServiceId, stRPServiceInfo.u16ONId, stRPServiceInfo.u16TSId, TYPE_CHANNEL_CHANGE_SER_ID, TRUE, TRUE))
            {
                MEMBER_SERVICETYPE eCurServiceType;
                U16 u16CurPosition;
                WORD wService_ID;
                WORD wTransportStream_ID;
                WORD wOriginalNetwork_ID;
                eCurServiceType = msAPI_CM_GetCurrentServiceType();
                u16CurPosition = msAPI_CM_GetCurrentPosition(eCurServiceType);
                wService_ID = msAPI_CM_GetService_ID(eCurServiceType, u16CurPosition);
                wTransportStream_ID = msAPI_CM_GetTS_ID(eCurServiceType, u16CurPosition);
                wOriginalNetwork_ID = msAPI_CM_GetON_ID(eCurServiceType,u16CurPosition);
                msAPI_CM_ReplaceDelProgram( eTempCurServiceType, u16TempCurPosition, TRUE );
                msAPI_CM_DeleteProgram( eTempCurServiceType, u16TempCurPosition, TRUE );
                if (TRUE == msAPI_CM_GetServiceTypeAndPositionWithIDs(  wTransportStream_ID, wOriginalNetwork_ID, wService_ID, 1, &eGotServiceType, &u16GotPosition, TRUE))
                {
                    msAPI_CM_SetCurrentServiceType(eGotServiceType);
                    msAPI_CM_SetCurrentPosition(eGotServiceType,u16GotPosition);
                }

                enPreSdtRunniungSts = SI_SDT_RUN_UNDEFINED;
                return;
            }
        }
    }


#if(SDT_AUTO_CHANGE_CH_TO_ORIGINAL)
    if( (s_SDT_u16OrgServiceId != 0)
      &&(MApp_SI_GetRunningStatus() == SI_SDT_RUN_RUNNING)
      )
    {
        if( MApp_ChannelChange_ChangeSpeciChannel(s_SDT_u16OrgServiceId, s_SDT_u16OrgON_Id, s_SDT_u16OrgTS_Id, TYPE_CHANNEL_CHANGE_SER_ID, TRUE, TRUE) )
        {
            //msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
        }

        MApp_SDT_ResetAutoChangeChVar();

        enPreSdtRunniungSts = SI_SDT_RUN_UNDEFINED;
        return;
    }
#endif


    if (stRPServiceInfo.u8RunningStatus == enPreSdtRunniungSts /*|| stRPServiceInfo.u8LinkageType != SERVICE_REPLACEMENT_SERVICE*/)
    {
        return;
    }

    switch ( stRPServiceInfo.u8RunningStatus )
    {
        case SI_SDT_RUN_UNDEFINED:
            break;

        case SI_SDT_RUN_RUNNING:
          #if 0
            if (enPreSdtRunniungSts != SI_SDT_RUN_UNDEFINED && enPreSdtRunniungSts != SI_SDT_RUN_RUNNING)
            {
                MApp_SDT_Set_AVMUTE(FALSE);
            }
          #endif
           break;

        case SI_SDT_RUN_NOT_RUN:
            if (stRPServiceInfo.u8Ser_Replacement && stRPServiceInfo.u8LinkageType == SERVICE_REPLACEMENT_SERVICE)
            {
                BOOLEAN bReplaceSuccessful = FALSE;

                if (TRUE == msAPI_CM_GetServiceTypeAndPositionWithIDs(stRPServiceInfo.u16TSId, stRPServiceInfo.u16ONId, stRPServiceInfo.u16ServiceId, 1, &eGotServiceType, &u16GotPosition, TRUE))
                {
                    EN_MHEG_5_TUNE_TYPE type;

                    if(OSD_COUNTRY_SETTING == OSD_COUNTRY_AUSTRALIA)
                    {
                        type = TYPE_CHANNEL_CHANGE_LCN_NDT;
                    }
                    else
                    {
                        type = TYPE_CHANNEL_CHANGE_SER_ID;
                    }

                #if(SDT_AUTO_CHANGE_CH_TO_ORIGINAL)
                    MEMBER_SERVICETYPE eCurServiceType = msAPI_CM_GetCurrentServiceType();
                    U16 u16CurPosition = msAPI_CM_GetCurrentPosition(eCurServiceType);

                    s_SDT_u16OrgServiceId = msAPI_CM_GetService_ID(eCurServiceType, u16CurPosition);
                    s_SDT_u16OrgTS_Id = msAPI_CM_GetTS_ID(eCurServiceType, u16CurPosition);
                    s_SDT_u16OrgON_Id = msAPI_CM_GetON_ID(eCurServiceType,u16CurPosition);
                #endif

                    bReplaceSuccessful = MApp_ChannelChange_ChangeSpeciChannel(stRPServiceInfo.u16ServiceId, stRPServiceInfo.u16ONId, stRPServiceInfo.u16TSId, type, TRUE, TRUE);
                }

                if( bReplaceSuccessful )
                {
                #if(SDT_AUTO_CHANGE_CH_TO_ORIGINAL)
                    // Add monitor to original service Id
                    MApp_SI_MonitorRunningStatusbyServiceid(s_SDT_u16OrgServiceId);
                #endif
                }
                else
                {   // Replace fail
                    // It should not mute here!?
                    //MApp_SDT_Set_AVMUTE(TRUE);

                #if(SDT_AUTO_CHANGE_CH_TO_ORIGINAL)
                    MApp_SDT_ResetAutoChangeChVar();
                #endif
                }

            }

            break;

        case SI_SDT_RUN_START_SOON:
        case SI_SDT_RUN_PAUSE:
          #if 0
            if (enPreSdtRunniungSts != SI_SDT_RUN_START_SOON && enPreSdtRunniungSts != SI_SDT_RUN_PAUSE)
            {
                MApp_SDT_Set_AVMUTE(TRUE);
            }
          #endif
            break;
    }

    //if( bReplaceSuccess == TRUE )
    {
        enPreSdtRunniungSts = (SI_SDT_RUNNINGSTATUS)stRPServiceInfo.u8RunningStatus;
    }
}

#if ENABLE_SDT_OTHER_MONITOR

void MApp_SDT_Set_UserService(MEMBER_SERVICETYPE eServiceType, U16 u16SID, U16 u16LCN )
{
    g_SDT_eUserServiceType = eServiceType;
    g_SDT_u16UserSID = u16SID;
    g_SDT_u16UserLCN = u16LCN;
}

void MApp_SDT_Get_UserService(MEMBER_SERVICETYPE* peServiceType, U16* pu16SID, U16* pu16LCN )
{
    *peServiceType = g_SDT_eUserServiceType;
    *pu16SID = g_SDT_u16UserSID;
    *pu16LCN = g_SDT_u16UserLCN;
}

void MApp_Update_User_Service(void)
{
    WORD wCurPos;
    g_SDT_eUserServiceType = msAPI_CM_GetCurrentServiceType();
    wCurPos = msAPI_CM_GetCurrentPosition( g_SDT_eUserServiceType );
    g_SDT_u16UserSID = msAPI_CM_GetService_ID( g_SDT_eUserServiceType,  wCurPos);
    g_SDT_u16UserLCN = msAPI_CM_GetLogicalChannelNumber( g_SDT_eUserServiceType,  wCurPos);
    //printf("update user service %u\n",g_SDT_u16UserLCN);
}

static BOOLEAN _MApp_ChangeToSame_Channel(void)
{
    WORD wNewPos;

    if (msAPI_CM_GetSameServiceInOtherMux(g_SDT_eUserServiceType,g_SDT_u16UserLCN, g_SDT_u16UserSID, &wNewPos))
    {
        if ((msAPI_CM_GetCurrentServiceType() != g_SDT_eUserServiceType)||
            (wNewPos != msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType())))
        {
            msAPI_CM_SetCurrentServiceType(g_SDT_eUserServiceType);
            msAPI_CM_SetCurrentPosition(g_SDT_eUserServiceType, wNewPos);
            MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, DISABLE, 0, MAIN_WINDOW);
            MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
            MApp_SI_Reset_CheckSameServiceTimer();
            //printf("change to same channel...2\n");
            return TRUE;
        }
    }

    return FALSE;
}

static void _MApp_Check_ChangeToSameService(void)
{
    if (MApp_SI_Is_ChangeTOSameService())
    {
        if (_MApp_ChangeToSame_Channel()== FALSE)
        {
            if (_MApp_SI_IsServiceMove(g_SDT_u16UserSID, g_SDT_u16UserLCN))
            {
                msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, 8000, MAIN_WINDOW);
            }
        }
    }
}
#endif

void MApp_SDT_Monitor(void)
{
    if( !IsDVBInUse() )
        return;

#if 0 // todo:  Check time
    static U32 _s_u32SDT_Monitor_LastTime = 0;
    if( msAPI_Timer_DiffTime_2(_s_u32SDT_Monitor_LastTime, MsOS_GetSystemTime()) < 300 )
    {
        return;
    }
#endif

#if ENABLE_SDT_OTHER_MONITOR
    _MApp_Check_ChangeToSameService(); // Move to MApp_SDT_Monitor()
#endif

    _MApp_SDT_FreeCAModeCheck();

    _MApp_SDT_RunningStatusCheck();

}

#endif

#undef MAPP_SDT_MONITOR_C

