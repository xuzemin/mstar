
#include "Board.h"

#include "msAPI_Global.h"

#include "apiXC_Hdmi.h"

#include "msAPI_CEC.h"

#include "msAPI_audio.h"

#include "MApp_Audio.h"

#include "MApp_Func_HDMI.h"

#if ENABLE_EDID_SWITCH
void MApp_Func_HDMI_Set_EdidSel(E_USER_HDMI_EDID_SEL eUserEdid)
{
    INPUT_SOURCE_TYPE_t enInputSourceType = stSystemInfo[MAIN_WINDOW].enInputSourceType;

    MApi_XC_Sys_Set_UserEdidSel(eUserEdid);

    MApi_XC_HDMI_EdidSwitch_ResetSM();

    switch( MApi_XC_Sys_Get_UserEdidSel() )
    {
        default:
        case E_USER_HDMI_EDID_1p4:
            MApi_XC_Sys_Reload_Edid(enInputSourceType, XC_HDMI_EDID_1p4, TRUE);
            break;

        case E_USER_HDMI_EDID_2p0:
            MApi_XC_Sys_Reload_Edid(enInputSourceType, XC_HDMI_EDID_2p0, TRUE);
            break;

        case E_USER_HDMI_EDID_AUTO:
            MApi_XC_Sys_Reload_Edid(enInputSourceType, XC_HDMI_EDID_2p0, TRUE);
            break;
    }

}
#endif

#if(ENABLE_CEC)

#if(CEC_VERSION_USING == CEC_NEW_VERSION)
extern void msAPI_CEC_SetSystemUnMute(void);
#endif

BOOLEAN MApp_CEC_Set_Enable(BOOLEAN bCecEnable)
{
    PRINT_CURRENT_LINE();

    printf("MApp_CEC_Set_Enable(En=%u)\n", bCecEnable);

    if( stGenSetting.stHDMISetting.g_bHdmiCecMode == bCecEnable )
    {
        return TRUE;
    }

    if( bCecEnable )
    {
        msAPI_CEC_EmptyAllMsgFifo();

        MApi_CEC_Enabled(ENABLE);   // Enable CEC HW

        stGenSetting.stHDMISetting.g_bHdmiCecMode = ENABLE;

        msAPI_CEC_ForceImmediatelyPolling(FALSE);

        // Todo:  Set all HDMI port low to high
    #if(ENABLE_CEC)
        MApi_XC_HPD_Do_Reset_ForCECOnOff();
    #endif
    }
    else
    {
    #if (CEC_VERSION_USING == CEC_NEW_VERSION)

      #if (!ENABLE_ARC_CHANGE_SPDIF)
        msAPI_CEC_ARC_TX_Control(FALSE);
      #endif

        if ( msAPI_CEC_IsDeviceExist(E_LA_AUDIO_SYS) )
        {
            if (stGenSetting.stHDMISetting.g_enHDMIARC == TRUE)
            {
                msAPI_CEC_PostMsg_RequestARCTermination(DIRECTMSG, E_LA_AUDIO_SYS);
            }

          #if (AMP_OFF_IF_CEC_OFF)
            msAPI_CEC_TxMsgSystemAudioModeRequest(DIRECTMSG, FALSE);
          #else
            msAPI_CEC_TxMsgSystemAudioModeRequest(DIRECTMSG, TRUE);
          #endif
        }

        msAPI_CEC_SetSystemUnMute();

    #else

        MDrv_HDMI_ARC_PINControl(INPUT_PORT_DVI0, FALSE, FALSE);

        if (msAPI_AUD_IsAudioMutedByUser()==TRUE)
        {
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
        }

    #endif

        MApp_Audio_Set_AmpMute(AUDIO_AMP_MUTE_OFF);

        MApi_CEC_Enabled(DISABLE);  // Disable CEC HW

        stGenSetting.stHDMISetting.g_bHdmiCecMode = DISABLE;
        stGenSetting.stHDMISetting.g_enHDMIARC = ENABLE;
        stGenSetting.stHDMISetting.g_bHdmiCecAutoTvOn = ENABLE;
        stGenSetting.stHDMISetting.g_bHdmiCecDeviceAutoStandby = ENABLE;
        stGenSetting.stHDMISetting.g_bHdmiCecDeviceControl = ENABLE;

        // Todo:  Set HDMI port that not in used high to low
    #if(ENABLE_CEC)
        MApi_XC_HPD_Do_Reset_ForCECOnOff();
    #endif

        MsOS_DelayTask(500);
        msAPI_CEC_EmptyAllMsgFifo();
    }

    return TRUE;
}

#endif


