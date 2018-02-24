#include "Board.h"


#include "MApp_GlobalSettingSt.h"

#include "MApp_BlockSys.h"
#include "MApp_UiMenuDef.h"

#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
#include "MApp_CIPVR_Adaption.h"              //For pvr
#endif

#if (ENABLE_DTV_EPG)
#include "mapp_eit.h"
#endif
#if (ENABLE_PVR)
#include "MApp_PVR.h"
#include "MApp_UiPvr.h"
//#include "MApp_TimeShift.h"
#include "MApp_Playback.h"
#include "MApp_Record.h"
#endif

#include "MApp_ParentalRating.h"

#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_ACTmsgbox.h"

#include "ZUI_tables_h.inl"
#include "ZUI_exefunc.h"
#include "msAPI_Timer.h"

//=================================================================


#if(ENABLE_DTV)
extern BOOLEAN bCheckParentalPW;

static BOOLEAN _bParentalBlock = FALSE;

#if ENABLE_CHG_CH_DEFAULT_LOCK
static BOOLEAN g_ParentalRating_bResetAge = FALSE;
static U32 g_ParentalRating_u32LockTimer;
#endif

#endif
U8 g_ParentalRating_u8PreParental_Control = 0xFF;

#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
extern EN_CC_PVR_OPERATING_MODE m_eOperatingMode;
#endif

void MApp_Set_MonitorParental(BOOLEAN bEnable)
{
    stGenSetting.g_BlockSysSetting.u8MonitorParental=bEnable;
}

BOOLEAN MApp_Get_MonitorParental(void)
{
    return stGenSetting.g_BlockSysSetting.u8MonitorParental;
}

#if(ENABLE_DTV)
BOOLEAN MApp_Get_ParentalBlock_state(void)
{
    return _bParentalBlock;
}

void MApp_Set_ParentalBlock_state(BOOLEAN bEnable)
{
    _bParentalBlock = bEnable;
}

void MApp_ParentalRating_PasswordInputMessageHandle(BOOL ActOnOff)
{
    if( _bParentalBlock
      && MApp_ParentalControl_GetBlockStatus()
      && IsDVBInUse()/*IsDTVInUse()*/
      )
    {
       ;
    }
    else
    {
       return;
    }

    if(ActOnOff)
    {
        MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_PASSWORD_INPUT_MSGBOX);
        SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW) = EN_SCREENSAVER_BLOCKRATING;
    }
    else
    {
        if(MApp_ZUI_API_IsSuccessor(HWND_MSGBOX_PASSWORD_PANE, MApp_ZUI_API_GetFocus()))
        {
            SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW) = EN_SCREENSAVER_NOSIGNAL;
            MApp_ZUI_ACT_ExecuteMessageBoxAction(EN_EXE_CLOSE_CURRENT_OSD);
        }
    }
}

void MApp_CheckParentalRatingBlockPWOSD(void)
{
    if(MApp_ZUI_GetActiveOSD() == E_OSD_MESSAGE_BOX)
    {
#if ((ENABLE_CI_PLUS == 1) && (ENABLE_CIPLUS_PVR == 1))
        if((MApp_ZUI_ACT_GetMessageBoxMode() != EN_MSGBOX_MODE_PVR_CI_PLUS_CAM_PINCODE)
            && (MApp_ZUI_ACT_GetMessageBoxMode() != EN_MSGBOX_MODE_PVR_CI_PLUS_CAM_PINCODE_WRONG)
            && (MApp_ZUI_ACT_GetMessageBoxMode() != EN_MSGBOX_MODE_PVR_TIMESHIFT_CI_PLUS_CAM_PINCODE)
            && (MApp_ZUI_ACT_GetMessageBoxMode() != EN_MSGBOX_MODE_PVR_TIMESHIFT_CI_PLUS_CAM_PINCODE_WRONG))
#endif
        {
            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
        }
    }
}

#if ENABLE_DVB

#if 0//ENABLE_ZIGGO
static BOOLEAN bPRChannelChange = 0;//channel changed
#endif

U8 MApp_ParentalRating_Get_Rating(void)
{
    U8 u8Parental_Control = 0;

#if ENABLE_PVR
    if (E_PVR_STATE_PLAYBACK == MApp_PVR_StateMachineGet() &&  E_PLAYBACK_STATE_PLAYBACKING== MApp_Playback_StateMachineGet())
    {
        u8Parental_Control = MApp_Playback_GetParentRating();
    }
    else
#endif
    {
    #if (ENABLE_DTV_EPG)
        u8Parental_Control = MApp_EIT_GetCurParentControl();
    #endif
    }

    return u8Parental_Control;
}

#define RATING_NO_LOCK      0
#define RATING_NEED_LOCK    1

BOOLEAN MApp_ParentalRating_CompareRating(U8 u8UserRating, U8 u8ProgRating)
{
    // Check user setting: If < min
    if( u8UserRating <= EN_F4_LockSystem_Min )
    {
        return RATING_NO_LOCK;
    }

    U8 u8LockAgeValid_Max = EN_F4_LockSystem_Max;

#if(ENABLE_ZIGGO&&ENABLE_DVBT)
  #if(ENABLE_ISDBT)
    BOOLEAN bIsZiggo = FALSE;
    if( IS_COUNTRY_USE_SBTVD() )
    {
        bIsZiggo = FALSE;
    }
    else
    {
        bIsZiggo = TRUE;
    }
  #else // No isdbt
    #define bIsZiggo    TRUE
  #endif
#endif


#if(ENABLE_ZIGGO&&ENABLE_DVBT)
    if( bIsZiggo )
    {
        u8LockAgeValid_Max = EN_F4_LockSystem_AllLock;
    }
#endif

    // Check user setting: If > max
    if( u8UserRating > u8LockAgeValid_Max )
    {
        return RATING_NO_LOCK;
    }

    // Compare user setting with prog rating
#if(ENABLE_ZIGGO&&ENABLE_DVBT)
    if( bIsZiggo )
    {
        if( u8UserRating < u8ProgRating )
        {
            return RATING_NEED_LOCK;
        }

        if( u8UserRating == EN_F4_LockSystem_AllLock )
        {
            return RATING_NEED_LOCK;
        }
    }
    else
#endif
    {
        if( u8UserRating <= u8ProgRating )
        {
            return RATING_NEED_LOCK;
        }
    }

    return RATING_NO_LOCK;
}

void MApp_ParentalRating_BlockStatus_Monitor(void)
{
    if( FALSE == MApp_Get_MonitorParental() )
    {
        return;
    }

    U8 u8Parental_Control = MApp_ParentalRating_Get_Rating();

    printf("u8Parental_Control=%u\n", u8Parental_Control);

    if(g_ParentalRating_u8PreParental_Control == u8Parental_Control)
    {
    #if ENABLE_CHG_CH_DEFAULT_LOCK
        if(g_ParentalRating_bResetAge)
        {
             //after time out,if we don't parse any age info.let it go on to deal with it
            if (msAPI_Timer_DiffTimeFromNow(g_ParentalRating_u32LockTimer) > 2500 )
            {
                 g_ParentalRating_u8PreParental_Control = 0XFF;
                 g_ParentalRating_bResetAge = FALSE;
            }
        }
    #endif
        return;
    }

    g_ParentalRating_u8PreParental_Control = u8Parental_Control;


    //printf(".......1.24.pinevent mute .MApp_ParentalRating_BlockStatus_Monitor...%d.........\n",u8Parental_Control);

#if (ENABLE_CI_PLUS == 1)
#if (ENABLE_CIPLUS_PVR == 1)
    if( (RATING_NEED_LOCK == MApp_ParentalRating_CompareRating(stGenSetting.g_BlockSysSetting.u8ParentalControl, u8Parental_Control))
    #if (ENABLE_PVR)
       && (!(MApp_PVR_IsRecording() && (MApp_PVR_StateMachineGet() == E_PVR_STATE_TIMESHIFT)))
       && (FALSE == MApp_PVR_IsPlaybacking())
    #endif
      )
    {
        if(TRUE == MAPP_CIPVR_CICheckCCPinCapabilities(FALSE,TRUE,FALSE))
        {
            U16 u16Password = stGenSetting.g_BlockSysSetting.u8ParentalControl;
            printf(".......1.24.pinevent mute .MAPP_CIPVR_CICheckCCPinCapabilities true............\n");
            MApp_ParentalControl_SetBlockStatus(FALSE);
            _bParentalBlock = FALSE;
            bCheckParentalPW = TRUE;
            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_LIVE_PIN_EVENT, ENABLE, NULL, MAIN_WINDOW);
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            MAPP_CIPVR_CISendCCPin(TRUE,u16Password);
            return;
        }
        else if(EN_CC_PVR_OPERATING_MODE_RESERVED != m_eOperatingMode)
        {
            printf(".......1.24.MAPP_CIPVR_CICheckCCPinCapabilities false............\n");
            MApp_ParentalControl_SetBlockStatus(FALSE);
            _bParentalBlock = FALSE;
            bCheckParentalPW = TRUE;
            return;
        }
    }
    else if(MApp_PVR_IsRecording() && (!MApp_PVR_IsPlaybacking()) && (MApp_PVR_StateMachineGet() == E_PVR_STATE_TIMESHIFT))
    {
        return;
    }
    else if (MApp_PVR_IsPlaybacking())
    {
        if( (TRUE == MAPP_CIPVR_PinEventPlaybackingRunning())
          &&(TRUE == MAPP_CIPVR_CICheckCCPinCapabilities(TRUE,FALSE,FALSE))
          )//avoid normal parental control in CI Pin Event process
        {
            return;
        }
    }
#else
        if(msAPI_CI_CardDetect())
        {
            if(MApp_SI_CheckCurProgScramble()&&msAPI_CI_CC_GetCicamRating()!=0&& msAPI_CI_CC_GetCicamRating() < u8Parental_Control)
            {
                  switch(msAPI_CI_CC_GetCicamPinCapability())
                  {
                    case EN_CC_CICAM_PIN_CAPABILITIES_CICAM_PIN_ONLY:
                    case EN_CC_CICAM_PIN_CAPABILITIES_BOTH_PIN :
                    case EN_CC_CICAM_PIN_CAPABILITIES_CICAM_PIN_ONLY_CACHED:
                    case EN_CC_CICAM_PIN_CAPABILITIES_BOTH_PIN_CACHED:
                    {
                        MApp_ParentalControl_SetBlockStatus(FALSE);
                        _bParentalBlock = FALSE;
                        bCheckParentalPW = TRUE;

                    #if ENABLE_PVR
                        if(MApp_PVR_StateMachineGet() == E_PVR_STATE_TIMESHIFT||MApp_PVR_StateMachineGet() == E_PVR_STATE_RECORDnPLAYBACK)
                         {
                             MApp_UiPvr_PlaybackStop();
                             MApp_UiPvr_RecordStop();
                         }
                         else if(MApp_PVR_StateMachineGet() == E_PVR_STATE_RECORD)
                         {
                              MApp_UiPvr_RecordStop();
                         }
                    #endif
                         return;
                    }
                    default:
                         break;
                    }
             }
        }
#endif
#endif


#if 1 // Refine flow...
    if( RATING_NEED_LOCK == MApp_ParentalRating_CompareRating(stGenSetting.g_BlockSysSetting.u8ParentalControl, u8Parental_Control) ) // If need lock
    {
        // Need lock
        if (FALSE == _bParentalBlock)
        {
            MApp_ParentalControl_SetBlockStatus(TRUE);
            _bParentalBlock = TRUE;
            bCheckParentalPW = FALSE;

         #if ENABLE_PVR
            if(MApp_PVR_StateMachineGet() == E_PVR_STATE_TIMESHIFT||MApp_PVR_StateMachineGet() == E_PVR_STATE_RECORDnPLAYBACK)
            {
                MApp_UiPvr_PlaybackStop();
                MApp_UiPvr_RecordStop();
            }
            else if(MApp_PVR_StateMachineGet() == E_PVR_STATE_RECORD)
            {
                 MApp_UiPvr_RecordStop();
            }
            else if(E_PVR_STATE_PLAYBACK == MApp_PVR_StateMachineGet() &&  E_PLAYBACK_STATE_PLAYBACKING== MApp_Playback_StateMachineGet())
            {
                 MApp_ParentalControl_SetBlockStatus(TRUE);
            }
         #endif
        }

    }
    else
    {
        // Need unlock...
        if( TRUE == _bParentalBlock )
        {
            MApp_ParentalControl_SetBlockStatus(FALSE);
            _bParentalBlock = FALSE;
            bCheckParentalPW = FALSE;

            if( IsDTVInUse() )
            {
               MApp_CheckParentalRatingBlockPWOSD();
            }
        }
    }

#else

    if ((stGenSetting.g_BlockSysSetting.u8ParentalControl<=EN_F4_LockSystem_Min) ||
#if ENABLE_ZIGGO
        (stGenSetting.g_BlockSysSetting.u8ParentalControl>EN_F4_LockSystem_AllLock))
#else
        (stGenSetting.g_BlockSysSetting.u8ParentalControl>EN_F4_LockSystem_Max))
#endif
    { // Do unlock
        //if (TRUE == _bParentalBlock)
        {
            MApp_ParentalControl_SetBlockStatus(FALSE);
            _bParentalBlock =FALSE;
            bCheckParentalPW = FALSE;
        }
    }
    #if(ENABLE_ZIGGO)
      else if (stGenSetting.g_BlockSysSetting.u8ParentalControl < u8Parental_Control)
    #else
      else if (stGenSetting.g_BlockSysSetting.u8ParentalControl <= u8Parental_Control)
    #endif
    { // Do Lock
        if (FALSE == _bParentalBlock)
        {
            MApp_ParentalControl_SetBlockStatus(TRUE);
            _bParentalBlock = TRUE;
            bCheckParentalPW = FALSE;
           #if ENABLE_PVR
            if(MApp_PVR_StateMachineGet() == E_PVR_STATE_TIMESHIFT||MApp_PVR_StateMachineGet() == E_PVR_STATE_RECORDnPLAYBACK)
            {
                MApp_UiPvr_PlaybackStop();
                MApp_UiPvr_RecordStop();
            }
            else if(MApp_PVR_StateMachineGet() == E_PVR_STATE_RECORD)
            {
                 MApp_UiPvr_RecordStop();
            }
            else if(E_PVR_STATE_PLAYBACK == MApp_PVR_StateMachineGet() &&  E_PLAYBACK_STATE_PLAYBACKING== MApp_Playback_StateMachineGet())
            {
                 MApp_ParentalControl_SetBlockStatus(TRUE);
            }
           #endif
        }
    }
#if ENABLE_ZIGGO
    else if(stGenSetting.g_BlockSysSetting.u8ParentalControl == EN_F4_LockSystem_AllLock)
    { //Do  Lock
        if(FALSE==_bParentalBlock)
        {
            MApp_ParentalControl_SetBlockStatus(TRUE);
            _bParentalBlock = TRUE;
            bCheckParentalPW = FALSE;
        }
        else
        {
            if(bPRChannelChange)
            {
                MApp_ParentalControl_SetBlockStatus(FALSE);
                _bParentalBlock= FALSE;
                bCheckParentalPW = FALSE;
                bPRChannelChange = FALSE;
                if(IsDTVInUse())
                   MApp_CheckParentalRatingBlockPWOSD();
            }
        }
    }
#endif
    else
    { // Do unlock
        //if (TRUE == _bParentalBlock)
        {
            MApp_ParentalControl_SetBlockStatus(FALSE);
            _bParentalBlock= FALSE;
            bCheckParentalPW = FALSE;
            if(IsDTVInUse())
               MApp_CheckParentalRatingBlockPWOSD();

        }
    }
#endif
}

void MApp_ParentalRating_DisableChannel(void)
{
    MApp_ParentalControl_SetBlockStatus(DISABLE);
    _bParentalBlock = FALSE;

#if 0//ENABLE_ZIGGO
    bPRChannelChange = TRUE;
#endif
}

void MApp_ParentalRating_EnableChannel(void)
{
#if (ENABLE_CHG_CH_DEFAULT_LOCK)
    g_ParentalRating_u8PreParental_Control = 0;
    if( (MApp_Get_MonitorParental())
     &&(stGenSetting.g_BlockSysSetting.u8ParentalControl > EN_F4_LockSystem_Min)
     &&(stGenSetting.g_BlockSysSetting.u8ParentalControl <= EN_F4_LockSystem_Max)
    )
    {
        g_ParentalRating_bResetAge = TRUE;
        g_ParentalRating_u32LockTimer = msAPI_Timer_GetTime0();
        MApp_Set_ParentalBlock_state(FALSE);
        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_RATING, ENABLE, NULL, MAIN_WINDOW);
    }
#else
    g_ParentalRating_u8PreParental_Control = 0xFF;
#endif
}

#endif
#endif

