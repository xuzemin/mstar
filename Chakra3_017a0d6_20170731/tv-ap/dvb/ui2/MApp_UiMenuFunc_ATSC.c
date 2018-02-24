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

#define MAPP_UI_MENUFUNC_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"

#include "apiAUDIO.h"

#include "msAPI_audio.h"
#include "msAPI_Timer.h"
#include "msAPI_MIU.h"
#include "msAPI_Tuner_ATSC.h"
#if(ENABLE_CEC)
#include "msAPI_CEC.h"
#endif

#include "MApp_Audio.h"
#include "MApp_PCMode.h"
#include "MApp_Psip.h"
#include "MApp_GlobalVar.h"
#include "MApp_GlobalFunction.h"
#include "MApp_UiMenuFunc_ATSC.h"
#include "MApp_DataBase_CH.h"
#include "MApp_Scan_ATSC.h"
#include "MApp_DataBase_ATSC.h"
#include "MApp_ChannelChange_ATSC.h"
#include "MApp_ChannelProc_ATSC.h"

#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_APIstrings.h"

#include "ZUI_tables_h.inl"
#include "OSDcp_String_EnumIndex.h"

#if ENABLE_ATSC_TTS
#include "MApp_TTSControlHandler.h"
#include "MApp_TTS_Cus.h"
#endif
//===========================================================================//

extern U32 g_u32StreamTime;
extern BOOLEAN MApp_UiMenu_CC_Preview(void);

#define OSDDBG(x) //x


#if 1//(AUDIO_MODE_USE_EQUALIZER==ENABLE)
static code stSoundEqSetting tAudioEqSetting[SOUND_MODE_NUM]=
{
    {70, 60, 65, 70, 40},
    {40, 50, 70, 20, 30},
    {50, 50, 70, 60, 70},
    {30, 30, 40, 60, 80},
    {50, 50, 50, 50, 50},
};
#endif

//============================================================================
U16 MApp_UiMenuFunc_DecIncValue(BOOLEAN action, U16 u16Value, U16 u16MinValue, U16 u16MaxValue, U8 u8Step)
{
    if(action == TRUE)
    {
        if(u16Value >= u16MaxValue)
            return u16MaxValue;
        u16Value += u8Step;
        if(u16Value > u16MaxValue)
            u16Value = u16MaxValue;
    }
    else if(action== FALSE)
    {
        if(u16Value <= u16MinValue)
            return u16MinValue;
        if(u16Value < u8Step)
            u16Value = 0;
        else
            u16Value -= u8Step;
        if(u16Value < u16MinValue)
            u16Value = u16MinValue;
    }
    return u16Value;
}

extern EN_SCAN_CHANNEL_TYPE enScanChannelType;
#if ENABLE_ATSC_TTS
void MApp_UiMenuFunc_SetTTSVolume(U8 u8Volume)
{
    U16 u16ActualValue;//driver value: 0 ~ 500; default 100
    switch(u8Volume)
    {
        case EN_VOICE_GUIDE_VOLUME_LOW:
            u16ActualValue = 50;
            break;
        case EN_VOICE_GUIDE_VOLUME_MEDIUM:
            u16ActualValue = 100;
            break;
        case EN_VOICE_GUIDE_VOLUME_HIGH:
            u16ActualValue = 300;
            break;
        default:
             u16ActualValue = 100;
            break;
    }
    MApp_TTSControlSetVolume(u16ActualValue);
}
void MApp_UiMenuFunc_SetTTSPitch(U8 u8Pitch)
{
    U16 u16ActualValue;//driver value: 100 ~ 400; default 200
    switch(u8Pitch)
    {
        case EN_VOICE_GUIDE_PITCH_LOW:
            u16ActualValue = 160;
            break;
        case EN_VOICE_GUIDE_PITCH_MEDIUM:
            u16ActualValue = 200;
            break;
        case EN_VOICE_GUIDE_PITCH_HIGH:
            u16ActualValue = 240;
            break;
        default:
             u16ActualValue = 200;
            break;
    }
    MApp_TTSControlSetPitch(u16ActualValue);
}
void MApp_UiMenuFunc_SetTTSSpeed(U8 u8Speed)
{
    U16 u16ActualValue;//Range: 80 ~ 400; default 167
    switch(u8Speed)
    {
        case EN_VOICE_GUIDE_SPEED_SLOW:
            u16ActualValue = 80;
            break;
        case EN_VOICE_GUIDE_SPEED_NORMAL:
            u16ActualValue = 167;
            break;
        case EN_VOICE_GUIDE_SPEED_FAST:
            u16ActualValue = 250;
            break;
        default:
            u16ActualValue = 167;
            break;
    }
    MApp_TTSControlSetSpeed(u16ActualValue);

}
#endif
BOOLEAN MApp_UiMenuFunc_AdjAudioLanguage(BOOLEAN action)
{
    if(IsATVInUse())
    {
        stGenSetting.g_SoundSetting.Mts =
        (EN_SOUND_MTS_TYPE)MApp_UiMenuFunc_DecIncValue_Cycle(action, stGenSetting.g_SoundSetting.Mts, SOUND_MTS_MONO, SOUND_MTS_NUM-1, 1);
    }
    else
    {
        stGenSetting.g_SoundSetting.enSoundAudioLan =
        (EN_ADUIO_LAN)MApp_UiMenuFunc_DecIncValue_Cycle(action, stGenSetting.g_SoundSetting.enSoundAudioLan, SOUND_AUDIO_LAN_ENGLISH, SOUND_AUDIO_LAN_SPANISH, 1);
    }

    MApp_Aud_GetNextAvailableMtsMode(TRUE);

    if ( IsDTVInUse() )
    {
        // ?? Who will use u16AudioPID??
        //u16AudioPID = MApp_SetPreferAudioSoundTrackPID(1);
    /*
        if(stGenSetting.g_SoundSetting.enVideoDescription == EN_VIDEO_DESCRIPTION_ITEM_OFF)
            MApp_SetPreferAudioSoundTrackPIDNew();
        else
            MApp_SetPreferAudioSoundTrackPID(0);
    */

    #if(ENABLE_ATSC_VIDEO_DESC)
        if(stGenSetting.g_SoundSetting.enVideoDescription == EN_VIDEO_DESCRIPTION_ITEM_ON)
            MApp_SetPreferAudioSoundTrackPID(0);
        else //if(stGenSetting.g_SoundSetting.enVideoDescription == EN_VIDEO_DESCRIPTION_ITEM_OFF)
    #endif
        {
            MApp_SetPreferAudioSoundTrackPIDNew();
        }

    }

    MApp_Aud_SetMtsMode();

  #if ENABLE_SOUNDTRACK_CHECKER_NEW
    MsOS_DelayTask(100);
  #endif

    return TRUE;
}

//============================================================================
U16 MApp_UiMenuFunc_DecIncATSCLanguage_Cycle(BOOLEAN action, U16 u16Value)
{
    if(action == TRUE)
    {
        if(u16Value == LANGUAGE_ENGLISH)
            u16Value = LANGUAGE_FRENCH;
        else if(u16Value == LANGUAGE_FRENCH)
            u16Value = LANGUAGE_SPANISH;
        else if(u16Value == LANGUAGE_SPANISH)
            u16Value = LANGUAGE_ENGLISH;
        else
            u16Value = LANGUAGE_ENGLISH;
    }
    else if(action == FALSE)
    {
        if(u16Value == LANGUAGE_ENGLISH)
            u16Value = LANGUAGE_SPANISH;
        else if(u16Value == LANGUAGE_FRENCH)
            u16Value = LANGUAGE_ENGLISH;
        else if(u16Value == LANGUAGE_SPANISH)
            u16Value = LANGUAGE_FRENCH;
        else
            u16Value = LANGUAGE_ENGLISH;
    }
    return u16Value;
}

BOOLEAN MApp_UiMenuFunc_AdjustOptionLanguage(BOOLEAN action)
{
    stGenSetting.g_SysSetting.Language =
    (EN_LANGUAGE)MApp_UiMenuFunc_DecIncATSCLanguage_Cycle(action, MENU_LANGUAGE);

#if ENABLE_ATSC_TTS

    printf("action=%d\n", action);
    printf("stGenSetting.g_SysSetting.Language=%d\n", stGenSetting.g_SysSetting.Language);

    //MApp_TTSControlSetLanguage(stGenSetting.g_SysSetting.Language);
    MApp_TTS_Cus_Set_Lang(stGenSetting.g_SysSetting.Language);
#endif

  #if ENABLE_CEC
    //fixed 11.1.6-4
    U8 u8CecLangCode[MAX_ISO639CODE_LENGTH] = { 0 };
    EN_LANGUAGE eLanguage = stGenSetting.g_SysSetting.Language; // OSD language

    if( MApp_GetOSDLangCodeFromIndex(eLanguage, u8CecLangCode)==TRUE)
    {
        msAPI_CEC_PostMsg_SetMenuLang(DIRECTMSG, u8CecLangCode);
    }
  #endif

#if ( ENABLE_LANGUAGE_KOREA)
   if(stGenSetting.g_SysSetting.Language==LANGUAGE_SPANISH)
  {
       msAPI_OSD_SetOSDLanguage(LANGUAGE_OSD_KOREAN);
  }
#endif

    return TRUE;
}

//============================================================================
BOOLEAN MApp_UiMenuFunc_AdjTimeZone(BOOLEAN action)
{

    stGenSetting.g_SysSetting.u8TimeZone=MApp_UiMenuFunc_DecIncValue_Cycle(action, stGenSetting.g_SysSetting.u8TimeZone, TIME_ZONE_ATLANTIC, TIME_ZONE_NUM-1, 1);
    stGenSetting.g_Time.s32Offset_Time = (U32)MApp_GetTimeZoneOffset(stGenSetting.g_SysSetting.u8TimeZone);
    msAPI_Timer_SetOffsetTime(stGenSetting.g_Time.s32Offset_Time);
    return TRUE;
}

//============================================================================
#if 0
BOOLEAN MApp_UiMenuFunc_AdjTimeDST(BOOLEAN action)
{
    stGenSetting.g_SysSetting.fTimeDST=MApp_UiMenuFunc_DecIncValue_Cycle(action, stGenSetting.g_SysSetting.fTimeDST, TIME_DST_OFF, TIME_DST_ITEM_NUM-1, 1);
    stGenSetting.g_Time.s32Offset_Time = (U32)MApp_GetTimeZoneOffset(stGenSetting.g_SysSetting.u8TimeZone);
    msAPI_Timer_SetOffsetTime(stGenSetting.g_Time.s32Offset_Time);
    return TRUE;
}
#endif
BOOLEAN MApp_UiMenuFunc_AdjTimeFormat()
{
    stGenSetting.g_SysSetting.fTimeFormat ^= 1;
    return TRUE;
}

//============================================================================
BOOLEAN MApp_UiMenuFunc_AdjChannelAntenna(BOOLEAN action)
{
    stGenSetting.stScanMenuSetting.u8Antenna =
        MApp_UiMenuFunc_DecIncValue_Cycle(action, stGenSetting.stScanMenuSetting.u8Antenna, ANT_CATV, ANT_TYPE_NUM-1, 1);
    MApp_ChannelChange_ChangeProgramList((EN_ANT_TYPE)ANT_TYPE);

    return TRUE;
}

#if 1
//============================================================================
BOOLEAN MApp_UiMenuFunc_AdjAudioMode(BOOLEAN action)
{
    stGenSetting.g_SoundSetting.SoundMode =
    (EN_SOUND_MODE)MApp_UiMenuFunc_DecIncValue_Cycle(action, stGenSetting.g_SoundSetting.SoundMode, SOUND_MODE_STANDARD, SOUND_MODE_NUM-1, 1);
    /* mute */

    msAPI_Timer_Delayms(10);
    MApp_Aud_SetBass(stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Bass);
    MApp_Aud_SetTreble(stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Treble);
    MApi_AUDIO_SetBalance(stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Balance);

#if 1//(AUDIO_MODE_USE_EQUALIZER==ENABLE)
    if(stGenSetting.g_SoundSetting.SoundMode == SOUND_MODE_USER)
    {
        //MApp_Aud_SetEqValue();
    }
#endif

    /* unmute */
    if(g_bInputBlocked||( MApp_VChip_GetCurVChipBlockStatus()))
    {
        // do nothing...
    }
    else
    {
    }

    return TRUE;
}
#endif
//============================================================================
BOOLEAN MApp_UiMenuFunc_SetAudio_Language(U8 u8Index)
{
    pstVirtualCh = MApp_ChanProc_GetCurChannelPointer();
    if(u8Index >= pstVirtualCh->u8AudLangNum)
    {
        return FALSE;
    }
    g_u8AudLangSelected = u8Index;
    MApp_Aud_SetMtsMode();

    #if ENABLE_SOUNDTRACK_CHECKER_NEW
    MsOS_DelayTask(100);
    #endif

    return TRUE;
}

//============================================================================
#if 1//(AUDIO_MODE_USE_EQUALIZER==ENABLE)

BOOLEAN MApp_UiMenuFunc_CheckAudioMode(void)
{
    if(stGenSetting.g_SoundSetting.SoundMode != SOUND_MODE_USER)
    {
        stGenSetting.g_SoundSetting.astSoundEqSetting.u8_150Hz = tAudioEqSetting[stGenSetting.g_SoundSetting.SoundMode].u8_150Hz;;
        stGenSetting.g_SoundSetting.astSoundEqSetting.u8_500Hz = tAudioEqSetting[stGenSetting.g_SoundSetting.SoundMode].u8_500Hz;;
        stGenSetting.g_SoundSetting.astSoundEqSetting.u8_1000Hz = tAudioEqSetting[stGenSetting.g_SoundSetting.SoundMode].u8_1000Hz;;
        stGenSetting.g_SoundSetting.astSoundEqSetting.u8_2000Hz = tAudioEqSetting[stGenSetting.g_SoundSetting.SoundMode].u8_2000Hz;;
        stGenSetting.g_SoundSetting.astSoundEqSetting.u8_4000Hz = tAudioEqSetting[stGenSetting.g_SoundSetting.SoundMode].u8_4000Hz;;

        stGenSetting.g_SoundSetting.SoundMode = SOUND_MODE_USER;
    }

    return TRUE;
}

//============================================================================
U16 MApp_UiMenuFunc_GetAudio150HzValue(void)
{
    if(stGenSetting.g_SoundSetting.SoundMode==SOUND_MODE_USER)
        return stGenSetting.g_SoundSetting.astSoundEqSetting.u8_150Hz;
    else
        return tAudioEqSetting[stGenSetting.g_SoundSetting.SoundMode].u8_150Hz;
}

BOOLEAN MApp_UiMenuFunc_AdjustAudio150Hz(BOOLEAN action)
{
    MApp_UiMenuFunc_CheckAudioMode();

    stGenSetting.g_SoundSetting.astSoundEqSetting.u8_150Hz =
        MApp_UiMenuFunc_DecIncValue(action, stGenSetting.g_SoundSetting.astSoundEqSetting.u8_150Hz, 0, 100, 1);
    MApi_AUDIO_EnableEQ(TRUE);
    MApp_Aud_SetEqValue();

    return TRUE;
}

//============================================================================
U16 MApp_UiMenuFunc_GetAudio500HzValue(void)
{
    if(stGenSetting.g_SoundSetting.SoundMode==SOUND_MODE_USER)
        return stGenSetting.g_SoundSetting.astSoundEqSetting.u8_500Hz;
    else
        return tAudioEqSetting[stGenSetting.g_SoundSetting.SoundMode].u8_500Hz;
}

BOOLEAN MApp_UiMenuFunc_AdjustAudio500Hz(BOOLEAN action)
{
    MApp_UiMenuFunc_CheckAudioMode();

    stGenSetting.g_SoundSetting.astSoundEqSetting.u8_500Hz =
        MApp_UiMenuFunc_DecIncValue(action, stGenSetting.g_SoundSetting.astSoundEqSetting.u8_500Hz, 0, 100, 1);
    MApi_AUDIO_EnableEQ(TRUE);
    MApp_Aud_SetEqValue();

    return TRUE;
}

//============================================================================
U16 MApp_UiMenuFunc_GetAudio1000HzValue(void)
{
    if(stGenSetting.g_SoundSetting.SoundMode==SOUND_MODE_USER)
        return stGenSetting.g_SoundSetting.astSoundEqSetting.u8_1000Hz;
    else
        return tAudioEqSetting[stGenSetting.g_SoundSetting.SoundMode].u8_1000Hz;
}

BOOLEAN MApp_UiMenuFunc_AdjustAudio1000Hz(BOOLEAN action)
{
    MApp_UiMenuFunc_CheckAudioMode();

    stGenSetting.g_SoundSetting.astSoundEqSetting.u8_1000Hz =
        MApp_UiMenuFunc_DecIncValue(action, stGenSetting.g_SoundSetting.astSoundEqSetting.u8_1000Hz, 0, 100, 1);
    MApi_AUDIO_EnableEQ(TRUE);
    MApp_Aud_SetEqValue();

    return TRUE;
}

//============================================================================
U16 MApp_UiMenuFunc_GetAudio2000HzValue(void)
{
    if(stGenSetting.g_SoundSetting.SoundMode==SOUND_MODE_USER)
        return stGenSetting.g_SoundSetting.astSoundEqSetting.u8_2000Hz;
    else
        return tAudioEqSetting[stGenSetting.g_SoundSetting.SoundMode].u8_2000Hz;
}

BOOLEAN MApp_UiMenuFunc_AdjustAudio2000Hz(BOOLEAN action)
{
    MApp_UiMenuFunc_CheckAudioMode();

    stGenSetting.g_SoundSetting.astSoundEqSetting.u8_2000Hz =
        MApp_UiMenuFunc_DecIncValue(action, stGenSetting.g_SoundSetting.astSoundEqSetting.u8_2000Hz, 0, 100, 1);
    MApi_AUDIO_EnableEQ(TRUE);
    MApp_Aud_SetEqValue();

    return TRUE;
}

//============================================================================
U16 MApp_UiMenuFunc_GetAudio4000HzValue(void)
{
    if(stGenSetting.g_SoundSetting.SoundMode==SOUND_MODE_USER)
        return stGenSetting.g_SoundSetting.astSoundEqSetting.u8_4000Hz;
    else
        return tAudioEqSetting[stGenSetting.g_SoundSetting.SoundMode].u8_4000Hz;
}

BOOLEAN MApp_UiMenuFunc_AdjustAudio4000Hz(BOOLEAN action)
{
    MApp_UiMenuFunc_CheckAudioMode();

    stGenSetting.g_SoundSetting.astSoundEqSetting.u8_4000Hz =
        MApp_UiMenuFunc_DecIncValue(action, stGenSetting.g_SoundSetting.astSoundEqSetting.u8_4000Hz, 0, 100, 1);
    MApi_AUDIO_EnableEQ(TRUE);
    MApp_Aud_SetEqValue();

    return TRUE;
}

#else // --------------------------------------------------------------------

BOOLEAN MApp_UiMenuFunc_CheckAudioMode(void)
{
    if(stGenSetting.g_SoundSetting.SoundMode != SOUND_MODE_USER)
    {
        stGenSetting.g_SoundSetting.astSoundModeSetting[SOUND_MODE_USER].Bass =
        stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Bass;
        stGenSetting.g_SoundSetting.astSoundModeSetting[SOUND_MODE_USER].Treble =
        stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Treble;
        stGenSetting.g_SoundSetting.astSoundModeSetting[SOUND_MODE_USER].Balance =
        stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Balance;

        stGenSetting.g_SoundSetting.SoundMode = SOUND_MODE_USER;
    }

    return TRUE;
}

//============================================================================
U16 MApp_UiMenuFunc_GetAudioBassValue(void)
{
    return stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Bass;
}

//============================================================================
BOOLEAN MApp_UiMenuFunc_AdjustAudioBass(BOOLEAN action)
{
    MApp_UiMenuFunc_CheckAudioMode();

    stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Bass =
        MApp_UiMenuFunc_DecIncValue(action, stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Bass, 0, 100, 1);

    MApp_Aud_SetBass(stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Bass);
    return TRUE;
}

//============================================================================
U16 MApp_UiMenuFunc_GetAudioTrebleValue(void)
{
    return stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Treble;
}

//============================================================================
BOOLEAN MApp_UiMenuFunc_AdjustAudioTreble(BOOLEAN action)
{
    MApp_UiMenuFunc_CheckAudioMode();

    stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Treble =
        MApp_UiMenuFunc_DecIncValue(action, stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Treble, 0, 100, 1);

    MApp_Aud_SetTreble(stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Treble);
    return TRUE;
}
#endif


//============================================================================
U16 MApp_UiMenuFunc_GetAudioBalanceValue(void)
{
    return stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Balance;
}


//============================================================================
BOOLEAN MApp_UiMenuFunc_AdjustAudioBalance(BOOLEAN action)
{
    U8 SoundModeBuffer;
    SoundModeBuffer = stGenSetting.g_SoundSetting.SoundMode;
    MApp_UiMenuFunc_CheckAudioMode();

    stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Balance =
        MApp_UiMenuFunc_DecIncValue(action, stGenSetting.g_SoundSetting.astSoundModeSetting[SoundModeBuffer].Balance, 0, 100, 1);

    MApi_AUDIO_SetBalance(stGenSetting.g_SoundSetting.astSoundModeSetting[stGenSetting.g_SoundSetting.SoundMode].Balance);
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_AdjustAudioOnly(BOOLEAN action)
{
#if (ENABLE_AUDIO_ONLY_CUSTOMERMODE == 1)

    if(g_AudioOnly == AUDIO_ONLY_OFF)
    {
        g_AudioOnly = AUDIO_ONLY_ON ;
        u32MonitorAudioOnlyTimer = msAPI_Timer_GetTime0();
        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_AUDIO_ONLY, ENABLE, 0, MAIN_WINDOW);
    }
    else
    {
        g_AudioOnly = AUDIO_ONLY_OFF ;
        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_AUDIO_ONLY, DISABLE, 0, MAIN_WINDOW);
    }
#endif
    action= action;
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_AdjustAVC(BOOLEAN action)
{
        stGenSetting.g_SoundSetting.bEnableAVC =
        (EN_AUD_SPDIF_MODE)MApp_UiMenuFunc_DecIncValue_Cycle( action, stGenSetting.g_SoundSetting.bEnableAVC, 0, 1, 1 );
       msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
       msAPI_Timer_Delayms(30);
       MApi_AUDIO_EnableAutoVolume(stGenSetting.g_SoundSetting.bEnableAVC);
       msAPI_Timer_Delayms(256);
       msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
       return TRUE;
}

//============================================================================
BOOLEAN MApp_UiMenuFunc_AdjTimeAutoSync(BOOLEAN action)
{
    stGenSetting.g_SysSetting.fTimeAutoSync =
        MApp_UiMenuFunc_DecIncValue_Cycle(
                    action, stGenSetting.g_SysSetting.fTimeAutoSync,
                    TIME_AUTO_SYNC_OFF, TIME_AUTO_SYNC_ITEM_NUM-1, 1);

    if ( (stGenSetting.g_SysSetting.fTimeAutoSync == TIME_AUTO_SYNC_ON)
       &&(g_u32StreamTime) )
    {
        msAPI_Timer_SetSystemTime(g_u32StreamTime);
    }

    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_AdjTimeWakeUpClockSetting_Year(BOOLEAN action)
{
    g_MsDateWakeUpSetting.u16Year = MApp_UiMenuFunc_DecIncValue_Cycle(action, g_MsDateWakeUpSetting.u16Year, 1980 , 2046 , 1);
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_AdjTimeWakeUpClockSetting_Month(BOOLEAN action)
{
    g_MsDateWakeUpSetting.u8Month = MApp_UiMenuFunc_DecIncValue_Cycle(action, g_MsDateWakeUpSetting.u8Month, 1 , 12 , 1);
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_AdjTimeWakeUpClockSetting_Day(BOOLEAN action)
{
    U16 u16DaysOfThisMonth;
     u16DaysOfThisMonth = MApp_GetDaysOfThisMonth( g_MsDateWakeUpSetting.u16Year, g_MsDateWakeUpSetting.u8Month );
     if( g_MsDateWakeUpSetting.u8Day > u16DaysOfThisMonth )
         g_MsDateWakeUpSetting.u8Day = u16DaysOfThisMonth;
     g_MsDateWakeUpSetting.u8Day = MApp_UiMenuFunc_DecIncValue_Cycle(action, g_MsDateWakeUpSetting.u8Day, 1 , u16DaysOfThisMonth , 1);
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_AdjTimeWakeUpClockSetting_Hour(BOOLEAN action)
{
    g_MsDateWakeUpSetting.u8Hour = MApp_UiMenuFunc_DecIncValue_Cycle(action, g_MsDateWakeUpSetting.u8Hour, 0 , 23 , 1);
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_AdjTimeWakeUpClockSetting_Min(BOOLEAN action)
{
    g_MsDateWakeUpSetting.u8Min = MApp_UiMenuFunc_DecIncValue_Cycle(action, g_MsDateWakeUpSetting.u8Min, 0 , 59 , 1);
    return TRUE;
}


BOOLEAN MApp_UiMenuFunc_EnterWakeUpClockSetting( void )
{

    MApp_ConvertLocalTime2Date(
                    (S32)msAPI_Timer_GetRTCWakeUpTime() +
                    (S32)MApp_GetTimeZoneOffset(stGenSetting.g_SysSetting.u8TimeZone),
                    &g_MsDateWakeUpSetting);
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_SaveWakeUpClockSetting( void )
{
    S32 seconds = MApp_ConvertDate2Seconds(&g_MsDateWakeUpSetting);
    S32 OffsetTime = MApp_GetTimeZoneOffset(stGenSetting.g_SysSetting.u8TimeZone);
    seconds -= OffsetTime;

    if( seconds < 0 )
        seconds = OffsetTime;

    msAPI_Timer_SetWakeupTime( seconds );

    msAPI_Timer_EnableRTCWakeUp(TRUE);
    msAPI_Timer_SetRTCWakeUpTime( seconds );
    return TRUE;
}

//============================================================================
U16 MApp_UiMenuFunc_GetCCFontStyleValue(void)
{
    return stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSFontStyle;
}

//============================================================================
BOOLEAN MApp_UiMenuFunc_AdjustCCFontStyle(BOOLEAN action)
{
    stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSFontStyle = MApp_UiMenuFunc_DecIncValue_Cycle(action, stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSFontStyle , CAPTIONMENU_FONT_STYLE_DEFAULT, CAPTIONMENU_FONT_STYLE_7, 1);

    switch (stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSFontStyle)
    {
      #if !Support_Caption_Preview
        default:
        case CAPTIONMENU_FONT_STYLE_DEFAULT:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSFontStyle = CAPTION_FONTSTYLE_DEFAULT;
        break;
      #else
        default:
        case CAPTIONMENU_FONT_STYLE_DEFAULT:
      #endif
        case CAPTIONMENU_FONT_STYLE_0:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSFontStyle = CAPTION_FONTSTYLE_0;
        break;
        case CAPTIONMENU_FONT_STYLE_1:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSFontStyle = CAPTION_FONTSTYLE_1;
        break;
        case CAPTIONMENU_FONT_STYLE_2:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSFontStyle = CAPTION_FONTSTYLE_2;
        break;
        case CAPTIONMENU_FONT_STYLE_3:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSFontStyle = CAPTION_FONTSTYLE_3;
        break;
        case CAPTIONMENU_FONT_STYLE_4:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSFontStyle = CAPTION_FONTSTYLE_4;
        break;
        case CAPTIONMENU_FONT_STYLE_5:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSFontStyle = CAPTION_FONTSTYLE_5;
        break;
        case CAPTIONMENU_FONT_STYLE_6:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSFontStyle = CAPTION_FONTSTYLE_6;
        break;
        case CAPTIONMENU_FONT_STYLE_7:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSFontStyle = CAPTION_FONTSTYLE_7;
        break;
    }

    MApp_UiMenu_CC_Preview();
    return TRUE;
}

//============================================================================
U16 MApp_UiMenuFunc_GetCCFontSizeValue(void)
{
    return stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSFontSize;
}

//============================================================================
BOOLEAN MApp_UiMenuFunc_AdjustCCFontSize(BOOLEAN action)
{
    stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSFontSize = MApp_UiMenuFunc_DecIncValue_Cycle(action, stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSFontSize , CAPTIONMENU_FONT_SIZE_DEFAULT, CAPTIONMENU_FONT_SIZE_SMALL, 1);

    switch(stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSFontSize)
    {
      #if !Support_Caption_Preview
        default:
        case CAPTIONMENU_FONT_SIZE_DEFAULT:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSFontSize = CAPTION_FONTSIZE_DEFAULT;
        break;
      #else
        default:
        case CAPTIONMENU_FONT_SIZE_DEFAULT:
      #endif
        case CAPTIONMENU_FONT_SIZE_NORMAL:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSFontSize = CAPTION_FONTSIZE_NORMAL;
        break;
        case CAPTIONMENU_FONT_SIZE_LARGE:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSFontSize = CAPTION_FONTSIZE_LARGE;
        break;
        case CAPTIONMENU_FONT_SIZE_SMALL:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSFontSize = CAPTION_FONTSIZE_SMALL;
        break;
    }
    MApp_UiMenu_CC_Preview();
    return TRUE;
}

#if (PARSING_CC_FONTEDGE)
//============================================================================
U16 MApp_UiMenuFunc_GetCCFontEdgeStyleValue(void)
{
    return stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionEdgeStyle;
}

//============================================================================
BOOLEAN MApp_UiMenuFunc_AdjustCCFontEdgeStyle(BOOLEAN action)
{
    stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionEdgeStyle = MApp_UiMenuFunc_DecIncValue_Cycle(action, stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionEdgeStyle , CAPTIONMENU_FONT_EDGESTYLE_DEFAULT, CAPTIONMENU_FONT_EDGESTYLE_RIGHTDROPSHADOW, 1);

    switch(stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionEdgeStyle)
    {
      #if !Support_Caption_Preview
        default:
        case CAPTIONMENU_FONT_EDGESTYLE_DEFAULT:
              stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionEdgeStyle = CAPTION_EDGESTYLE_DEFAULT;
        break;
      #else
        default:
        case CAPTIONMENU_FONT_EDGESTYLE_DEFAULT:
      #endif
        case CAPTIONMENU_FONT_EDGESTYLE_NONE:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionEdgeStyle = CAPTION_EDGESTYLE_NONE;
        break;
        case CAPTIONMENU_FONT_EDGESTYLE_RAISED:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionEdgeStyle = CAPTION_EDGESTYLE_RAISE;
        break;
        case CAPTIONMENU_FONT_EDGESTYLE_DEPRESSED:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionEdgeStyle = CAPTION_EDGESTYLE_DEPRESSED;
        break;
        case CAPTIONMENU_FONT_EDGESTYLE_UNIFORM:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionEdgeStyle = CAPTION_EDGESTYLE_UNIFORM;
        break;
        case CAPTIONMENU_FONT_EDGESTYLE_LEFTDROPSHADOW:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionEdgeStyle = CAPTION_EDGESTYLE_LIGHTDROPSHADOW;
        break;
        case CAPTIONMENU_FONT_EDGESTYLE_RIGHTDROPSHADOW:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionEdgeStyle = CAPTION_EDGESTYLE_RIGHTDROPSHADOW;
        break;
    }
    MApp_UiMenu_CC_Preview();
    return TRUE;
}

//============================================================================
U16 MApp_UiMenuFunc_GetCCFontEdgeColorValue(void)
{
    return stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionEdgeColor;
}

//============================================================================
BOOLEAN MApp_UiMenuFunc_AdjustCCFontEdgeColor(BOOLEAN action)
{
    stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionEdgeColor = MApp_UiMenuFunc_DecIncValue_Cycle(action, stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionEdgeColor , CAPTIONMENU_FONT_EDGECOLOR_DEFAULT, CAPTIONMENU_FONT_EDGECOLOR_CYAN, 1);

    switch (stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionEdgeColor)
    {
      #if !Support_Caption_Preview
        default:
        case CAPTIONMENU_FONT_EDGECOLOR_DEFAULT:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionEdgeColor = CAPTION_EDGECOLOR_DEFAULT;
        break;
      #else
        default:
        case CAPTIONMENU_FONT_EDGECOLOR_DEFAULT:
     #endif
        case CAPTIONMENU_FONT_EDGECOLOR_BLACK:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionEdgeColor = CAPTION_EDGECOLOR_BLACK;
        break;
        case CAPTIONMENU_FONT_EDGECOLOR_WHITE:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionEdgeColor = CAPTION_EDGECOLOR_WHITE;
        break;
        case CAPTIONMENU_FONT_EDGECOLOR_RED:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionEdgeColor = CAPTION_EDGECOLOR_RED;
        break;
        case CAPTIONMENU_FONT_EDGECOLOR_GREEN:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionEdgeColor = CAPTION_EDGECOLOR_GREEN;
        break;
        case CAPTIONMENU_FONT_EDGECOLOR_BLUE:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionEdgeColor = CAPTION_EDGECOLOR_BLUE;
        break;
        case CAPTIONMENU_FONT_EDGECOLOR_YELLOW:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionEdgeColor = CAPTION_EDGECOLOR_YELLOW;
        break;
        case CAPTIONMENU_FONT_EDGECOLOR_MAGENTA:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionEdgeColor = CAPTION_EDGECOLOR_MAGENTA;
        break;
        case CAPTIONMENU_FONT_EDGECOLOR_CYAN:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionEdgeColor = CAPTION_EDGECOLOR_CYAN;
        break;
    }
    MApp_UiMenu_CC_Preview();
    return TRUE;
}
#endif

//============================================================================
U16 MApp_UiMenuFunc_GetCCFGColorValue(void)
{
    return stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionFGColor;
}

//============================================================================
BOOLEAN MApp_UiMenuFunc_AdjustCCFGColor(BOOLEAN action)
{
    stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionFGColor = MApp_UiMenuFunc_DecIncValue_Cycle(action, stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionFGColor , CAPTIONMENU_FG_COLOR_DEFAULT, CAPTIONMENU_FG_COLOR_CYAN, 1);

    if(stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionFGColor > CAPTIONMENU_FG_COLOR_BLACK)
    {
        if(stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionFGColor == stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionBGColor)
        {
            stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionFGColor = MApp_UiMenuFunc_DecIncValue_Cycle(action, stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionFGColor , CAPTIONMENU_FG_COLOR_DEFAULT, CAPTIONMENU_FG_COLOR_CYAN, 1);
        }
    }
    else
    {
        if(stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionBGColor == CAPTIONMENU_BG_COLOR_WHITE)
        {
            while(stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionFGColor <= CAPTIONMENU_FG_COLOR_WHITE)
                stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionFGColor = MApp_UiMenuFunc_DecIncValue_Cycle(action, stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionFGColor , CAPTIONMENU_FG_COLOR_DEFAULT, CAPTIONMENU_FG_COLOR_CYAN, 1);
        }
        else if(stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionBGColor <= CAPTIONMENU_BG_COLOR_BLACK)
        {
            while(stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionFGColor == CAPTIONMENU_FG_COLOR_BLACK)
                stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionFGColor = MApp_UiMenuFunc_DecIncValue_Cycle(action, stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionFGColor , CAPTIONMENU_FG_COLOR_DEFAULT, CAPTIONMENU_FG_COLOR_CYAN, 1);
        }
    }

    switch (stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionFGColor)
    {
       #if !Support_Caption_Preview
        default:
        case CAPTIONMENU_FG_COLOR_DEFAULT:
             stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionFGColor = CAPTION_FGCOLOR_DEFAULT;
        break;
      #else
        default:
        case CAPTIONMENU_FG_COLOR_DEFAULT:
      #endif
        case CAPTIONMENU_FG_COLOR_WHITE:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionFGColor = CAPTION_FG_WHITE;
        break;
        case CAPTIONMENU_FG_COLOR_BLACK:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionFGColor = CAPTION_FG_BLACK;
        break;
        case CAPTIONMENU_FG_COLOR_RED:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionFGColor = CAPTION_FG_RED;
        break;
        case CAPTIONMENU_FG_COLOR_GREEN:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionFGColor = CAPTION_FG_GREEN;
        break;
        case CAPTIONMENU_FG_COLOR_BLUE:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionFGColor = CAPTION_FG_BLUE;
        break;
        case CAPTIONMENU_FG_COLOR_YELLOW:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionFGColor = CAPTION_FG_YELLOW;
        break;
        case CAPTIONMENU_FG_COLOR_MAGENTA:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionFGColor = CAPTION_FG_MAGENTA;
        break;
        case CAPTIONMENU_FG_COLOR_CYAN:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionFGColor = CAPTION_FG_CYAN;
        break;
    }
    MApp_UiMenu_CC_Preview();
    return TRUE;
}

//============================================================================
U16 MApp_UiMenuFunc_GetCCBGColorValue(void)
{
    return stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionBGColor;
}

//============================================================================
BOOLEAN MApp_UiMenuFunc_AdjustCCBGColor(BOOLEAN action)
{
    stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionBGColor = MApp_UiMenuFunc_DecIncValue_Cycle(action, stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionBGColor , CAPTIONMENU_BG_COLOR_DEFAULT, CAPTIONMENU_BG_COLOR_CYAN, 1);

    if(stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionBGColor > CAPTIONMENU_BG_COLOR_WHITE)
    {
        if(stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionBGColor == stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionFGColor)
        {
            stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionBGColor = MApp_UiMenuFunc_DecIncValue_Cycle(action, stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionBGColor , CAPTIONMENU_BG_COLOR_DEFAULT, CAPTIONMENU_BG_COLOR_CYAN, 1);
        }
    }
    else
    {
        if(stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionFGColor == CAPTIONMENU_FG_COLOR_BLACK)
        {
            while(stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionBGColor <= CAPTIONMENU_BG_COLOR_BLACK)
            {
                stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionBGColor = MApp_UiMenuFunc_DecIncValue_Cycle(action, stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionBGColor , CAPTIONMENU_BG_COLOR_DEFAULT, CAPTIONMENU_BG_COLOR_CYAN, 1);
            }
        }
        else if(stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionFGColor <= CAPTIONMENU_FG_COLOR_WHITE)
        {
            while(stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionBGColor == CAPTIONMENU_BG_COLOR_WHITE)
            {
                stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionBGColor = MApp_UiMenuFunc_DecIncValue_Cycle(action, stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionBGColor , CAPTIONMENU_BG_COLOR_DEFAULT, CAPTIONMENU_BG_COLOR_CYAN, 1);
            }
        }
    }

    switch (stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionBGColor)
    {
      #if !Support_Caption_Preview
        default:
        case CAPTIONMENU_BG_COLOR_DEFAULT:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionBGColor = CAPTION_BGCOLOR_DEFAULT;
        break;
      #else
        default:
        case CAPTIONMENU_BG_COLOR_DEFAULT:
      #endif
        case CAPTIONMENU_BG_COLOR_BLACK:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionBGColor = CAPTION_BG_BLACK;
        break;
        case CAPTIONMENU_BG_COLOR_WHITE:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionBGColor = CAPTION_BG_WHITE;
        break;
        case CAPTIONMENU_BG_COLOR_RED:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionBGColor = CAPTION_BG_RED;
        break;
        case CAPTIONMENU_BG_COLOR_GREEN:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionBGColor = CAPTION_BG_GREEN;
        break;
        case CAPTIONMENU_BG_COLOR_BLUE:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionBGColor = CAPTION_BG_BLUE;
        break;
        case CAPTIONMENU_BG_COLOR_YELLOW:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionBGColor = CAPTION_BG_YELLOW;
        break;
        case CAPTIONMENU_BG_COLOR_MAGENTA:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionBGColor = CAPTION_BG_MAGENTA;
        break;
        case CAPTIONMENU_BG_COLOR_CYAN:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionBGColor = CAPTION_BG_CYAN;
        break;
    }
    MApp_UiMenu_CC_Preview();
    return TRUE;
}

//============================================================================
U16 MApp_UiMenuFunc_GetCCWindowColorValue(void)
{
    return stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionWindowColor;
}

//============================================================================
BOOLEAN MApp_UiMenuFunc_AdjustCCWindowColor(BOOLEAN action)
{
    stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionWindowColor = MApp_UiMenuFunc_DecIncValue_Cycle(action, stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionWindowColor , CAPTIONMENU_WINDOW_COLOR_DEFAULT, CAPTIONMENU_WINDOW_COLOR_CYAN, 1);

    switch (stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionWindowColor)
    {
      #if !Support_Caption_Preview
        default:
        case CAPTIONMENU_WINDOW_COLOR_DEFAULT:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionWindowColor = CAPTION_WINDOWCOLOR_DEFAULT;
        break;
      #else
        default:
        case CAPTIONMENU_WINDOW_COLOR_DEFAULT:
      #endif
        case CAPTIONMENU_WINDOW_COLOR_BLACK:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionWindowColor = CAPTION_WINDOW_BLACK;
        break;
        case CAPTIONMENU_WINDOW_COLOR_WHITE:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionWindowColor = CAPTION_WINDOW_WHITE;
        break;
        case CAPTIONMENU_WINDOW_COLOR_RED:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionWindowColor = CAPTION_WINDOW_RED;
        break;
        case CAPTIONMENU_WINDOW_COLOR_GREEN:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionWindowColor = CAPTION_WINDOW_GREEN;
        break;
        case CAPTIONMENU_WINDOW_COLOR_BLUE:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionWindowColor = CAPTION_WINDOW_BLUE;
        break;
        case CAPTIONMENU_WINDOW_COLOR_YELLOW:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionWindowColor = CAPTION_WINDOW_YELLOW;
        break;
        case CAPTIONMENU_WINDOW_COLOR_MAGENTA:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionWindowColor = CAPTION_WINDOW_MAGENTA;
        break;
        case CAPTIONMENU_WINDOW_COLOR_CYAN:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionWindowColor = CAPTION_WINDOW_CYAN;
        break;
    }
    MApp_UiMenu_CC_Preview();
    return TRUE;
}

//============================================================================
U16 MApp_UiMenuFunc_GetCCFGOpacityValue(void)
{
    return stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionFGOpacity;
}

//============================================================================
BOOLEAN MApp_UiMenuFunc_AdjustCCFGOpacity(BOOLEAN action)
{
    stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionFGOpacity = MApp_UiMenuFunc_DecIncValue_Cycle(action, stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionFGOpacity , CAPTIONMENU_FG_OPACITY_DEFAULT, CAPTIONMENU_FG_OPACITY_TRANSPARENT, 1);

    switch (stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionFGOpacity)
    {
      #if !Support_Caption_Preview
        default:
        case CAPTIONMENU_FG_OPACITY_DEFAULT:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionFGOpacity = CAPTION_FGOPACITY_DEFAULT;
        break;
      #else
        default:
        case CAPTIONMENU_FG_OPACITY_DEFAULT:
      #endif
        case CAPTIONMENU_FG_OPACITY_SOLID:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionFGOpacity = CAPTION_FG_SOLID;
        break;
        case CAPTIONMENU_FG_OPACITY_FLASHING:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionFGOpacity = CAPTION_FG_FLASHING;
        break;
        case CAPTIONMENU_FG_OPACITY_TRANSLUCENT:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionFGOpacity = CAPTION_FG_TRANSLUCENT;
        break;
        case CAPTIONMENU_FG_OPACITY_TRANSPARENT:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionFGOpacity = CAPTION_FG_TRANSPARENT;
        break;
    }
    MApp_UiMenu_CC_Preview();
    return TRUE;
}

//============================================================================
U16 MApp_UiMenuFunc_GetCCBGOpacityValue(void)
{
    return stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionBGOpacity;
}

//============================================================================
BOOLEAN MApp_UiMenuFunc_AdjustCCBGOpacity(BOOLEAN action)
{
    stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionBGOpacity = MApp_UiMenuFunc_DecIncValue_Cycle(action, stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionBGOpacity , CAPTIONMENU_BG_OPACITY_DEFAULT, CAPTIONMENU_BG_OPACITY_TRANSPARENT, 1);

    switch (stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionBGOpacity)
    {
      #if !Support_Caption_Preview
        default:
        case CAPTIONMENU_BG_OPACITY_DEFAULT:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionBGOpacity = CAPTION_BGOPACITY_DEFAULT;
        break;
      #else
        default:
        case CAPTIONMENU_BG_OPACITY_DEFAULT:
      #endif
        case CAPTIONMENU_BG_OPACITY_SOLID:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionBGOpacity = CAPTION_BG_SOLID;
        break;
        case CAPTIONMENU_BG_OPACITY_FLASHING:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionBGOpacity = CAPTION_BG_FLASHING;
        break;
        case CAPTIONMENU_BG_OPACITY_TRANSLUCENT:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionBGOpacity = CAPTION_BG_TRANSLUCENT;
        break;
        case CAPTIONMENU_BG_OPACITY_TRANSPARENT:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionBGOpacity = CAPTION_BG_TRANSPARENT;
        break;
    }
    MApp_UiMenu_CC_Preview();
    return TRUE;
}

//============================================================================
U16 MApp_UiMenuFunc_GetCCWindowOpacityValue(void)
{
    return stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionWindowOpacity;
}

//============================================================================
BOOLEAN MApp_UiMenuFunc_AdjustCCWindowOpacity(BOOLEAN action)
{
    stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionWindowOpacity = MApp_UiMenuFunc_DecIncValue_Cycle(action, stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionWindowOpacity , CAPTIONMENU_WINDOW_OPACITY_DEFAULT, CAPTIONMENU_WINDOW_OPACITY_TRANSPARENT, 1);

    switch (stGenSetting.g_CaptionSetting.astCaptionOptionMenu.u8CSOptionWindowOpacity)
    {
      #if !Support_Caption_Preview
        default:
        case CAPTIONMENU_WINDOW_OPACITY_DEFAULT:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionWindowOpacity = CAPTION_WINDOWOPACITY_DEFAULT;
        break;
      #else
        default:
        case CAPTIONMENU_WINDOW_OPACITY_DEFAULT:
      #endif
        case CAPTIONMENU_WINDOW_OPACITY_SOLID:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionWindowOpacity = CAPTION_WINDOW_SOLID;
        break;
        case CAPTIONMENU_WINDOW_OPACITY_FLASHING:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionWindowOpacity = CAPTION_WINDOW_FLASHING;
        break;
        case CAPTIONMENU_WINDOW_OPACITY_TRANSLUCENT:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionWindowOpacity = CAPTION_WINDOW_TRANSLUCENT;
        break;
        case CAPTIONMENU_WINDOW_OPACITY_TRANSPARENT:
            stGenSetting.g_CaptionSetting.astCaptionOptionCustom.u8CSOptionWindowOpacity = CAPTION_WINDOW_TRANSPARENT;
        break;
    }
    MApp_UiMenu_CC_Preview();
    return TRUE;
}
// ================================== Lock Menu ================================
//============================================================================

BOOLEAN MApp_UiMenuFunc_AdjSystemLockMode(void)
{
    BOOLEAN bPreInputBlock = MApp_UiMenuFunc_CheckInputLock();
    stGenSetting.g_VChipSetting.u8VChipLockMode ^=1;

#if(ENABLE_ATSC_VCHIP)
    MApp_VChip_Init();
#endif

    fVChipPassWordEntered = FALSE;

#if ENABLE_INPUT_LOCK
    g_bInputBlocked = MApp_UiMenuFunc_CheckInputLock();

  #if 1//def LOCK_USE_BLACK_VIDEO
    if (g_bInputBlocked)
    {
        MApp_MuteAvByLock(E_SCREEN_MUTE_BY_UI, TRUE);
    }
    else if (bPreInputBlock)
    {
        MApp_MuteAvByLock(E_SCREEN_MUTE_BY_UI, FALSE);
    }
  #else
    if (g_bInputBlocked)
    {
        MApp_MuteAvByLock(TRUE);
    }
    else if (bPreInputBlock)
    {
        MApp_MuteAvByLock(FALSE);
    }
  #endif
#endif


    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_AdjustDigitalAudioSelect( BOOLEAN action)
{
    stGenSetting.g_SoundSetting.enSoundDigitalSelect =
    (EN_DIGITAL_AUDIO_SECLECTION)MApp_UiMenuFunc_DecIncValue_Cycle( action, stGenSetting.g_SoundSetting.enSoundDigitalSelect, SOUND_AUDIO_DIGITAL_DEFAULT, SOUND_AUDIO_DIGITAL_NUM-1, 1 );
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_AdjustAccessibility( BOOLEAN action)
{
    stGenSetting.g_SoundSetting.enAccessibility =
    (EN_ACCESSIBILITY)MApp_UiMenuFunc_DecIncValue_Cycle( action, stGenSetting.g_SoundSetting.enAccessibility, SOUND_MAIN_AUDIO, SOUND_HI, 1 );
    return TRUE;
}

#if(ENABLE_ATSC_VIDEO_DESC)
BOOLEAN MApp_UiMenuFunc_SelectVideoDescription(void)
{
    stGenSetting.g_SoundSetting.enVideoDescription=
    (EN_VIDEO_DESCRIPTION_ITEM)MApp_UiMenuFunc_DecIncValue_Cycle( 1, stGenSetting.g_SoundSetting.enVideoDescription, EN_VIDEO_DESCRIPTION_ITEM_ON, EN_VIDEO_DESCRIPTION_ITEM_OFF, 1 );

      MApp_ReMapAudioLanguage();
      switch(stGenSetting.g_SoundSetting.enVideoDescription)
      {
          case EN_VIDEO_DESCRIPTION_ITEM_ON:
              MApp_SetPreferAudioSoundTrackPID(0);
              break;
          case EN_VIDEO_DESCRIPTION_ITEM_OFF:
              MApp_SetPreferAudioSoundTrackPIDNew();
              break;
          default:
              break;
      }
      MApp_Aud_SetMtsMode();
    return TRUE;
}
#endif

BOOLEAN MApp_UiMenuFunc_AdjustAudioLanguage( BOOLEAN action)
{
    stGenSetting.g_SoundSetting.enDAPAudioLanguage =
    (EN_DAP_AUDIO_LANGUAGE)MApp_UiMenuFunc_DecIncValue_Cycle( action, stGenSetting.g_SoundSetting.enDAPAudioLanguage, DAP_SOUND_LANGUAGE_ENGLISH, DAP_SOUND_LANGUAGE_SPANISH, 1 );

    //Remapping Audio language // Mantis 0939960 fixed 20150817 // sync from Chakra2
    MApp_ReMapAudioLanguage();

    // !!! No one will use u16AudioPID!???
    //U16 u16AudioPID;

/*
    //if(stGenSetting.g_SoundSetting.enSoundDigitalSelect == SOUND_AUDIO_DIGITAL_DEFAULT
    if(stGenSetting.g_SoundSetting.enVideoDescription == EN_VIDEO_DESCRIPTION_ITEM_OFF)
        //u16AudioPID = MApp_SetPreferAudioSoundTrackPIDNew();
        MApp_SetPreferAudioSoundTrackPIDNew();
    else
        //u16AudioPID = MApp_SetPreferAudioSoundTrackPID(0);
        MApp_SetPreferAudioSoundTrackPID(0);
*/

#if(ENABLE_ATSC_VIDEO_DESC)
    if(stGenSetting.g_SoundSetting.enVideoDescription == EN_VIDEO_DESCRIPTION_ITEM_ON)
        MApp_SetPreferAudioSoundTrackPID(0);
    else //if(stGenSetting.g_SoundSetting.enVideoDescription == EN_VIDEO_DESCRIPTION_ITEM_OFF)
#endif
    {
        MApp_SetPreferAudioSoundTrackPIDNew();
    }


    stGenSetting.g_SoundSetting.Mts = (EN_SOUND_MTS_TYPE)g_u8AudLangSelected;

    MApp_Aud_SetMtsMode();

    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_AdjustPrimartAudioPmt( BOOLEAN action)
{
    stGenSetting.g_SoundSetting.enPrimartAudioPmt =
    (EN_PRIMART_AUDIO_PARAMETER)MApp_UiMenuFunc_DecIncValue_Cycle( action, stGenSetting.g_SoundSetting.enPrimartAudioPmt, SOUND_ACCESSIBILITY, SOUND_AUDIO_LANGUAGE, 1 );
    return TRUE;
}

void MApp_UiMenuFunc_SaveCurrentRegion5Ratings(void)
{
    BOOLEAN bSavedRRT = FALSE;
    U8 u8ExceedDimentionNum = 0;
    U8 u8Loop1=0, u8Loop2=0;
    MS_EZ_REGION5_RATING stEZ_VchipRegion5;

    // Find if this RRT has been saved before........
    for (u8Loop1=0; u8Loop1<stGenSettingVchipRegion5.u8NoSavedRRT; u8Loop1++)
    {
        // Load from DB
    #if( ENABLE_DB_ATSC_RRT5_API )
        MApp_DB_ATSC_Load_RRT_EZ_REGION(u8Loop1, &stEZ_VchipRegion5 );
    #else
        memcpy((U8*)&stEZ_VchipRegion5,(U8*)_PA2VA(GET_SAVED_RRT_SETTING_ADDRESS(u8Loop1)),sizeof(MS_EZ_REGION5_RATING));
    #endif

    #if (ENABLE_RRT5_UPDATE_BY_LATEST_VERSION)
        {  //only save in same addr
            bSavedRRT = TRUE;
            break;
        }
    #else
        if(strcmp((const char*)stGenSettingVchipRegion5.u8Region5Name, (const char*)stEZ_VchipRegion5.u8EZRegion5Name)==0)
        {
            if((stGenSettingVchipRegion5.u8NoDimension == stEZ_VchipRegion5.u8NoDimension))
            {// this RRT is already in the memory....
                if( (stGenSettingVchipRegion5.u8VersionNo == INVALID_VERSION_NUM) ||
                     (stGenSettingVchipRegion5.u8VersionNo == stEZ_VchipRegion5.u8VersionNo) )
                {
                    bSavedRRT = TRUE;
                    break;
                }
            }
        }
    #endif
    }

    // fill the structure...
    if(stGenSettingVchipRegion5.u8VersionNo != INVALID_VERSION_NUM)
    {
        stEZ_VchipRegion5.u8VersionNo = stGenSettingVchipRegion5.u8VersionNo;
    }

    memcpy(stEZ_VchipRegion5.u8EZRegion5Name, stGenSettingVchipRegion5.u8Region5Name, sizeof(stEZ_VchipRegion5.u8EZRegion5Name));

    // Check if dimension number over range
    if( stGenSettingVchipRegion5.u8NoDimension > REGION5_DIMENSION_NUM )
    {
         stGenSettingVchipRegion5.u8NoDimension = REGION5_DIMENSION_NUM;
    }

    stEZ_VchipRegion5.u8NoDimension = stGenSettingVchipRegion5.u8NoDimension;

    if( stGenSettingVchipRegion5.u8NoDimension >= REGION5_DIMENSION_NUM )
    {
         u8ExceedDimentionNum = REGION5_DIMENSION_NUM;
    }
    else
    {
         u8ExceedDimentionNum = stGenSettingVchipRegion5.u8NoDimension;
    }

    for(u8Loop2=0; u8Loop2 < u8ExceedDimentionNum; u8Loop2++)
    {
        stEZ_VchipRegion5.stRegin5Dimension[u8Loop2].u32CurrentOption = stGenSettingVchipRegion5.stRegin5Dimension[u8Loop2].u32CurrentOption;
        stEZ_VchipRegion5.stRegin5Dimension[u8Loop2].u16Graduated_Scale = stGenSettingVchipRegion5.stRegin5Dimension[u8Loop2].u16Graduated_Scale;
        stEZ_VchipRegion5.stRegin5Dimension[u8Loop2].u8Values_Defined = stGenSettingVchipRegion5.stRegin5Dimension[u8Loop2].u8Values_Defined;
    }

    if (!bSavedRRT)
    {
        if (stGenSettingVchipRegion5.u8NoSavedRRT == MAX_RRT_SAVED)
        {
            if (stGenSettingVchipRegion5.u8IdxLastSavedRRT >= (MAX_RRT_SAVED-1))
            {
                stGenSettingVchipRegion5.u8IdxLastSavedRRT = 0;
                u8Loop1 = stGenSettingVchipRegion5.u8IdxLastSavedRRT;
            }
            else
            {
                stGenSettingVchipRegion5.u8IdxLastSavedRRT++;
                u8Loop1 = stGenSettingVchipRegion5.u8IdxLastSavedRRT;
            }
        }
        else
        {
            u8Loop1 = stGenSettingVchipRegion5.u8IdxLastSavedRRT;
            stGenSettingVchipRegion5.u8NoSavedRRT++;
            stGenSettingVchipRegion5.u8IdxLastSavedRRT++;
        }
    }

    // Save to DB
#if( ENABLE_DB_ATSC_RRT5_API )
    MApp_DB_ATSC_Save_RRT_EZ_REGION(u8Loop1, &stEZ_VchipRegion5 );
#else
    memcpy((U8*)_PA2VA(GET_SAVED_RRT_SETTING_ADDRESS(u8Loop1)),(U8*)&stEZ_VchipRegion5, sizeof(MS_EZ_REGION5_RATING));
#endif
}

BOOLEAN MApp_UiMenuFunc_ResetRatingTable(void)
{
    //Always unblock CH after reseting RRT.
    memset(&stGenSettingVchipRegion5, 0, sizeof(MS_REGION5_RATING));
    stGenSettingVchipRegion5.u8NoSavedRRT = 0;
    stGenSettingVchipRegion5.u8IdxLastSavedRRT = 0;
    stGenSettingVchipRegion5.u8VersionNo=INVALID_VERSION_NUM;
    stGenSettingVchipRegion5.u8NoDimension = 0;
//#if (ENABLE_MEXICO_VCHIP)
    //MApp_Dmx_RRT_Reset();
//#endif
    MApp_UiMenuFunc_SaveCurrentRegion5Ratings();
    //MApp_DB_SaveDataBase();
    MApp_DB_CH_SaveData_RightNow();

#if(ENABLE_ATSC_VCHIP)
    MApp_VChip_Init();
#endif

    return TRUE;
}

#if ENABLE_UNRATED_LOCK
BOOLEAN MApp_UiMenuFunc_AdjUnRatedLockMode(void)
{
    stGenSetting.g_VChipSetting.u8UnRatedLock ^=1;

    if (g_stVChipRatingInfo.RatingType == VCHIP_RATING_TYPE_NONE)
        fVChipPassWordEntered = FALSE;

    memset(&g_stVChipRatingInfo, 0, sizeof(g_stVChipRatingInfo));

    return TRUE;
}
#endif

BOOLEAN MApp_UiMenuFunc_CheckInputLock(void)
{
    if (!stGenSetting.g_VChipSetting.u8VChipLockMode)
        return FALSE;

    if ( IsAnyTVSourceInUse() )
        {
            if(( stGenSetting.g_VChipSetting.u8InputBlockItem & INPUT_BLOCK_TV)!=0)
            return TRUE;
        }
    else if ( IsVgaInUse() )
        {
            if(( stGenSetting.g_VChipSetting.u8InputBlockItem & INPUT_BLOCK_PC)!=0)
            return TRUE;
        }
    else if ( IsYPbPrInUse() )
        {
            if(( stGenSetting.g_VChipSetting.u8InputBlockItem & INPUT_BLOCK_YPBPR)!=0)
            return TRUE;
        }
    else if ( IsAVInUse() )
        {
            if(( stGenSetting.g_VChipSetting.u8InputBlockItem & INPUT_BLOCK_AV)!=0)
            return TRUE;
        }
    else if ( IsSVInUse() )
        {
            if(( stGenSetting.g_VChipSetting.u8InputBlockItem & INPUT_BLOCK_SV)!=0)
            return TRUE;
        }

#if (ENABLE_HDMI)
    else if ( IsHDMIInUse() )
        {
            if(( stGenSetting.g_VChipSetting.u8InputBlockItem & INPUT_BLOCK_HDMI)!=0)
            return TRUE;
        }
#endif

#if (ENABLE_SCART_VIDEO)
    else if ( IsScartInUse() )
        {
            if(( stGenSetting.g_VChipSetting.u8InputBlockItem & INPUT_BLOCK_SCART)!=0)
            return TRUE;
        }
#endif

    return FALSE;
}

#if ENABLE_INPUT_LOCK
BOOLEAN MApp_UiMenuFunc_AdjustInputLockTV(void)
{
    stGenSetting.g_VChipSetting.u8InputBlockItem ^= INPUT_BLOCK_TV;
    g_bInputBlocked = MApp_UiMenuFunc_CheckInputLock ();

    if ( IsAnyTVSourceInUse() )
    {
      #if 1//def LOCK_USE_BLACK_VIDEO
        MApp_MuteAvByLock(E_SCREEN_MUTE_BY_UI, g_bInputBlocked);
      #else
        MApp_MuteAvByLock(g_bInputBlocked);
      #endif
    }
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_AdjustInputLockAV(void)
{
    stGenSetting.g_VChipSetting.u8InputBlockItem ^= INPUT_BLOCK_AV;
    g_bInputBlocked = MApp_UiMenuFunc_CheckInputLock ();

    if ( IsAVInUse() )
    {
    #if 1//def LOCK_USE_BLACK_VIDEO
        MApp_MuteAvByLock(E_SCREEN_MUTE_BY_UI, g_bInputBlocked);
    #else
        MApp_MuteAvByLock(g_bInputBlocked);
    #endif
    }
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_AdjustInputLockSV(void)
{
    stGenSetting.g_VChipSetting.u8InputBlockItem ^= INPUT_BLOCK_SV;
    g_bInputBlocked = MApp_UiMenuFunc_CheckInputLock ();

    if ( IsSVInUse() )
    {
    #if 1//def LOCK_USE_BLACK_VIDEO
        MApp_MuteAvByLock(E_SCREEN_MUTE_BY_UI, g_bInputBlocked);
    #else
        MApp_MuteAvByLock(g_bInputBlocked);
    #endif
    }
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_AdjustInputLockYPbPr(void)
{
    stGenSetting.g_VChipSetting.u8InputBlockItem ^= INPUT_BLOCK_YPBPR;
    g_bInputBlocked = MApp_UiMenuFunc_CheckInputLock ();

    if ( IsYPbPrInUse() )
    {
    #if 1//def LOCK_USE_BLACK_VIDEO
        MApp_MuteAvByLock(E_SCREEN_MUTE_BY_UI, g_bInputBlocked);
    #else
        MApp_MuteAvByLock(g_bInputBlocked);
    #endif
    }
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_AdjustInputLockSCART(void)
{
    stGenSetting.g_VChipSetting.u8InputBlockItem ^= INPUT_BLOCK_SCART;
    g_bInputBlocked = MApp_UiMenuFunc_CheckInputLock ();

#if (ENABLE_SCART_VIDEO)
    if ( IsScartInUse() )
    {
    #if 1//def LOCK_USE_BLACK_VIDEO
        MApp_MuteAvByLock(E_SCREEN_MUTE_BY_UI, g_bInputBlocked);
    #else
        MApp_MuteAvByLock(g_bInputBlocked);
    #endif
    }
#endif

    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_AdjustInputLockHDMI(void)
{
    stGenSetting.g_VChipSetting.u8InputBlockItem ^= INPUT_BLOCK_HDMI;
    g_bInputBlocked = MApp_UiMenuFunc_CheckInputLock ();

#if (ENABLE_HDMI)
    if ( IsHDMIInUse() )
    {
    #if 1//def LOCK_USE_BLACK_VIDEO
        MApp_MuteAvByLock(E_SCREEN_MUTE_BY_UI, g_bInputBlocked);
    #else
        MApp_MuteAvByLock(g_bInputBlocked);
    #endif
    }
#endif

    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_AdjustInputLockPC(void)
{
    stGenSetting.g_VChipSetting.u8InputBlockItem ^= INPUT_BLOCK_PC;
    g_bInputBlocked = MApp_UiMenuFunc_CheckInputLock ();

    if ( IsVgaInUse() )
    {
    #if 1//def LOCK_USE_BLACK_VIDEO
        MApp_MuteAvByLock(E_SCREEN_MUTE_BY_UI, g_bInputBlocked);
    #else
        MApp_MuteAvByLock(g_bInputBlocked);
    #endif
    }

    return TRUE;
}
#endif // end of ENABLE_INPUT_LOCK

#if 0
void MApp_UiMenuFunc_VChip_CompareRating(void)
{
#if(ENABLE_ATSC_VCHIP)
    BOOLEAN bPreLockStatus = MApp_VChip_GetCurVChipBlockStatus();
    BOOLEAN fVChipPassWordEnteredBk;

    fVChipPassWordEnteredBk = fVChipPassWordEntered;
    fVChipPassWordEntered = FALSE;
    if (bPreLockStatus != MApp_VChip_CompareRating(&g_stVChipRatingInfo, &stGenSetting.g_VChipSetting))
    {
        fVChipPassWordEntered = FALSE;
        memset(&g_stVChipRatingInfo, 0, sizeof(g_stVChipRatingInfo));
        g_stVChipRatingInfo.u8EIA608Data1 = BIT6;
    }
    else
    {
        fVChipPassWordEntered = fVChipPassWordEnteredBk;
    }
#endif
}

BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_NONE_ALL(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_NONE & VCHIP_TVRATING_ALL)
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_NONE &= ~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV_NONE_ALL_BG, TRUE);
    }
    else
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_NONE = VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y = VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 = VCHIP_TVRATING_FV|VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G |= VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG = VCHIP_TVRATING_VSLD|VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 = VCHIP_TVRATING_VSLD|VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA = VCHIP_TVRATING_VSL|VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV_NONE_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG, FALSE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_NONE = VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV_NONE_ALL_BG, FALSE);
      #endif
    }
    MApp_UiMenuFunc_VChip_CompareRating();
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_Y_ALL(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y & VCHIP_TVRATING_ALL)
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y &= ~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY_ALL_BG, TRUE);
    }
    else
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y = VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 = VCHIP_TVRATING_FV|VCHIP_TVRATING_ALL;
         stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G |= VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG = VCHIP_TVRATING_VSLD|VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 = VCHIP_TVRATING_VSLD|VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA = VCHIP_TVRATING_VSL|VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_ALL_BG, FALSE);
         MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG, FALSE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y = VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 = VCHIP_TVRATING_FV|VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG, FALSE);
      #endif
    }
    MApp_UiMenuFunc_VChip_CompareRating();
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_Y7_ALL(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 & VCHIP_TVRATING_ALL)
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y = 0;//~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY_ALL_BG, TRUE);
    }
    else
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 = VCHIP_TVRATING_FV|VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G |= VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG = VCHIP_TVRATING_VSLD|VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 = VCHIP_TVRATING_VSLD|VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA = VCHIP_TVRATING_VSL|VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG, FALSE);
     #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 = VCHIP_TVRATING_FV|VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG, FALSE);
     #endif
    }
    MApp_UiMenuFunc_VChip_CompareRating();
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_G_ALL(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G & VCHIP_TVRATING_ALL)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y = 0;//~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G = 0;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
      #endif
    }
    else
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G |= VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG = VCHIP_TVRATING_VSLD|VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 = VCHIP_TVRATING_VSLD|VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA = VCHIP_TVRATING_VSL|VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG, FALSE);
    }
    MApp_UiMenuFunc_VChip_CompareRating();
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_PG_ALL(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG & VCHIP_TVRATING_ALL)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y = 0;//~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, TRUE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G = 0;//~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
      #endif
    }
    else
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG = VCHIP_TVRATING_VSLD|VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 = VCHIP_TVRATING_VSLD|VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA = VCHIP_TVRATING_VSL|VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG, FALSE);
    }
    MApp_UiMenuFunc_VChip_CompareRating();
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_14_ALL(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 & VCHIP_TVRATING_ALL)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y = 0;//~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG, TRUE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G = 0;//~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
      #endif
    }
    else
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 = VCHIP_TVRATING_VSLD|VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA = VCHIP_TVRATING_VSL|VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG, FALSE);
    }
    MApp_UiMenuFunc_VChip_CompareRating();
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_MA_ALL(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_ALL)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y = 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA &= 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G &= 0;//~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG, TRUE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA &= 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= 0;//~VCHIP_TVRATING_ALL;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G &= 0;//~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
      #endif
    }
    else
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA = VCHIP_TVRATING_VSL|VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG, FALSE);
    }
    MApp_UiMenuFunc_VChip_CompareRating();
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_Y7_FV(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 & VCHIP_TVRATING_FV)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 &= ~VCHIP_TVRATING_FV;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG, TRUE);
     #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 = 0;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y = 0;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY_ALL_BG, TRUE);
     #endif
    }
    else
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 |= VCHIP_TVRATING_FV;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG, FALSE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_Y7 = VCHIP_TVRATING_FV|VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_ALL_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG, FALSE);
      #endif
    }
    MApp_UiMenuFunc_VChip_CompareRating();
    return TRUE;
}
#if (!ENABLE_VCHIP_ALL_AS_AGEBASED)
static void MApp_UiMenuFunc_CheckVChip_TVRating_TV_PG(void)
{
    if((stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG & VCHIP_TVRATING_V)
    &&(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG & VCHIP_TVRATING_S)
    &&(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG & VCHIP_TVRATING_L)
    &&(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG & VCHIP_TVRATING_D)
    &&(!(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG & VCHIP_TVRATING_ALL))
    )
    {
        MApp_UiMenuFunc_SetVChip_TVRating_TV_PG_ALL();
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, FALSE);
        if(!(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 & VCHIP_TVRATING_ALL))
        {
            MApp_UiMenuFunc_SetVChip_TVRating_TV_14_ALL();
            MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, FALSE);
        }
        if(!(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_ALL))
        {
            MApp_UiMenuFunc_SetVChip_TVRating_TV_MA_ALL();
            MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, FALSE);
        }

    }
    else if((stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_V)
    &&(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_S)
    &&(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_L)
    &&(!(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_ALL)))
    {
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, FALSE);
    }
}

static void MApp_UiMenuFunc_CheckVChip_TVRating_TV_14(void)
{
    if((stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 & VCHIP_TVRATING_V)
    &&(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 & VCHIP_TVRATING_S)
    &&(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 & VCHIP_TVRATING_L)
    &&(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 & VCHIP_TVRATING_D)
    &&(!(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 & VCHIP_TVRATING_ALL))
    )
    {
        MApp_UiMenuFunc_SetVChip_TVRating_TV_14_ALL();
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, FALSE);
        if(!(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_ALL))
        {
            MApp_UiMenuFunc_SetVChip_TVRating_TV_MA_ALL();
            MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, FALSE);
        }
    }
    else if((stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_V)
    &&(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_S)
    &&(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_L)
    &&(!(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_ALL)))
    {
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, FALSE);
    }
}

static void MApp_UiMenuFunc_CheckVChip_TVRating_TV_MA(void)
{
    if((stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_V)
    &&(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_S)
    &&(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_L)
    &&(!(stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_ALL))
    )
    {
        MApp_UiMenuFunc_SetVChip_TVRating_TV_MA_ALL();
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, FALSE);
    }
}
#endif
BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_PG_V(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG & VCHIP_TVRATING_V)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~VCHIP_TVRATING_V;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, TRUE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~(VCHIP_TVRATING_V|VCHIP_TVRATING_ALL);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G &= ~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
      #endif
    }
    else
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG |= VCHIP_TVRATING_V;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 |= VCHIP_TVRATING_V;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA |= VCHIP_TVRATING_V;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG, FALSE);
      #if (!ENABLE_VCHIP_ALL_AS_AGEBASED)
        MApp_UiMenuFunc_CheckVChip_TVRating_TV_PG();
      #endif
    }
    MApp_UiMenuFunc_VChip_CompareRating();
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_14_V(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 & VCHIP_TVRATING_V)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= ~VCHIP_TVRATING_V;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~VCHIP_TVRATING_V;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, TRUE);
     #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= ~(VCHIP_TVRATING_V|VCHIP_TVRATING_ALL);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~(VCHIP_TVRATING_ALL|VCHIP_TVRATING_V);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G &= ~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
     #endif
    }
    else
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 |= VCHIP_TVRATING_V;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA |= VCHIP_TVRATING_V;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG, FALSE);
    #if (!ENABLE_VCHIP_ALL_AS_AGEBASED)
        MApp_UiMenuFunc_CheckVChip_TVRating_TV_14();
    #endif
    }
    MApp_UiMenuFunc_VChip_CompareRating();
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_MA_V(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_V)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA &= ~VCHIP_TVRATING_V;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= ~VCHIP_TVRATING_V;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~VCHIP_TVRATING_V;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG, TRUE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA &= ~(VCHIP_TVRATING_V|VCHIP_TVRATING_ALL);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= ~(VCHIP_TVRATING_ALL|VCHIP_TVRATING_V);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~(VCHIP_TVRATING_ALL|VCHIP_TVRATING_V);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G &= ~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
      #endif
    }
    else
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA |= VCHIP_TVRATING_V;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG, FALSE);
    #if (!ENABLE_VCHIP_ALL_AS_AGEBASED)
        MApp_UiMenuFunc_CheckVChip_TVRating_TV_MA();
    #endif
    }
    MApp_UiMenuFunc_VChip_CompareRating();
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_PG_S(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG & VCHIP_TVRATING_S)
    {
    #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~VCHIP_TVRATING_S;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, TRUE);
    #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~(VCHIP_TVRATING_S|VCHIP_TVRATING_ALL);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G &= ~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
    #endif
    }
    else
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG |= VCHIP_TVRATING_S;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 |= VCHIP_TVRATING_S;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA |= VCHIP_TVRATING_S;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG, FALSE);
      #if (!ENABLE_VCHIP_ALL_AS_AGEBASED)
        MApp_UiMenuFunc_CheckVChip_TVRating_TV_PG();
      #endif
    }
    MApp_UiMenuFunc_VChip_CompareRating();
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_14_S(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 & VCHIP_TVRATING_S)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= ~VCHIP_TVRATING_S;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~VCHIP_TVRATING_S;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, TRUE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= ~(VCHIP_TVRATING_S|VCHIP_TVRATING_ALL);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~(VCHIP_TVRATING_ALL|VCHIP_TVRATING_S);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G &= ~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
      #endif
    }
    else
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 |= VCHIP_TVRATING_S;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA |= VCHIP_TVRATING_S;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG, FALSE);
      #if (!ENABLE_VCHIP_ALL_AS_AGEBASED)
        MApp_UiMenuFunc_CheckVChip_TVRating_TV_14();
      #endif
    }
    MApp_UiMenuFunc_VChip_CompareRating();
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_MA_S(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_S)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA &= ~VCHIP_TVRATING_S;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= ~VCHIP_TVRATING_S;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~VCHIP_TVRATING_S;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG, TRUE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA &= ~(VCHIP_TVRATING_S|VCHIP_TVRATING_ALL);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= ~(VCHIP_TVRATING_ALL|VCHIP_TVRATING_S);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~(VCHIP_TVRATING_ALL|VCHIP_TVRATING_S);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G &= ~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
      #endif
    }
    else
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA |= VCHIP_TVRATING_S;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG, FALSE);
      #if (!ENABLE_VCHIP_ALL_AS_AGEBASED)
        MApp_UiMenuFunc_CheckVChip_TVRating_TV_MA();
      #endif
    }
    MApp_UiMenuFunc_VChip_CompareRating();
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_PG_L(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG & VCHIP_TVRATING_L)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~VCHIP_TVRATING_L;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, TRUE);
     #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~(VCHIP_TVRATING_L|VCHIP_TVRATING_ALL);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G &= ~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
    #endif
    }
    else
    {

        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG |= VCHIP_TVRATING_L;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 |= VCHIP_TVRATING_L;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA |= VCHIP_TVRATING_L;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG, FALSE);
      #if (!ENABLE_VCHIP_ALL_AS_AGEBASED)
        MApp_UiMenuFunc_CheckVChip_TVRating_TV_PG();
      #endif
    }
    MApp_UiMenuFunc_VChip_CompareRating();
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_14_L(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 & VCHIP_TVRATING_L)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= ~VCHIP_TVRATING_L;
     stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~VCHIP_TVRATING_L;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, TRUE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= ~(VCHIP_TVRATING_L|VCHIP_TVRATING_ALL);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~(VCHIP_TVRATING_ALL|VCHIP_TVRATING_L);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G &= ~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
      #endif
    }
    else
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 |= VCHIP_TVRATING_L;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA |= VCHIP_TVRATING_L;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG, FALSE);
      #if (!ENABLE_VCHIP_ALL_AS_AGEBASED)
        MApp_UiMenuFunc_CheckVChip_TVRating_TV_14();
      #endif
    }
    MApp_UiMenuFunc_VChip_CompareRating();
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_MA_L(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_L)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA &= ~VCHIP_TVRATING_L;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= ~VCHIP_TVRATING_L;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~VCHIP_TVRATING_L;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG, TRUE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA &= ~(VCHIP_TVRATING_L|VCHIP_TVRATING_ALL);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= ~(VCHIP_TVRATING_ALL|VCHIP_TVRATING_L);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~(VCHIP_TVRATING_ALL|VCHIP_TVRATING_L);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G &= ~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
      #endif
    }
    else
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_MA |= VCHIP_TVRATING_L;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG, FALSE);
      #if (!ENABLE_VCHIP_ALL_AS_AGEBASED)
        MApp_UiMenuFunc_CheckVChip_TVRating_TV_MA();
      #endif
    }

    MApp_UiMenuFunc_VChip_CompareRating();

    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_PG_D(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG & VCHIP_TVRATING_D)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~VCHIP_TVRATING_D;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, TRUE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~(VCHIP_TVRATING_D|VCHIP_TVRATING_ALL);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G &= ~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
      #endif
    }
    else
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG |= VCHIP_TVRATING_D;
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 |= VCHIP_TVRATING_D;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, FALSE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG, FALSE);
    #if (!ENABLE_VCHIP_ALL_AS_AGEBASED)
        MApp_UiMenuFunc_CheckVChip_TVRating_TV_PG();
      #endif
    }
    MApp_UiMenuFunc_VChip_CompareRating();
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_SetVChip_TVRating_TV_14_D(void)
{
    if (stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 & VCHIP_TVRATING_D)
    {
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= ~VCHIP_TVRATING_D;
     stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~VCHIP_TVRATING_D;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, TRUE);
      #else
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 &= ~(VCHIP_TVRATING_D|VCHIP_TVRATING_ALL);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_PG &= ~(VCHIP_TVRATING_ALL|VCHIP_TVRATING_D);
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_G &= ~VCHIP_TVRATING_ALL;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG, TRUE);
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG, TRUE);
      #endif
    }
    else
    {
        stGenSetting.g_VChipSetting.stVChipTVItem.Item_TV_14 |= VCHIP_TVRATING_D;
        MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG, FALSE);
      #if (!ENABLE_VCHIP_ALL_AS_AGEBASED)
        MApp_UiMenuFunc_CheckVChip_TVRating_TV_14();
      #endif
    }
    MApp_UiMenuFunc_VChip_CompareRating();
    return TRUE;
}

#endif
// Get RRT description from SDRAM to xdata
BOOLEAN MApp_UiMenuFunc_GetRRT_OptionDescription(U8 u8DimensionIdx, U8 u8OptionIdx)
{
    if( (u8DimensionIdx>=REGION5_DIMENSION_NUM)||(u8OptionIdx>=REGION5_MAX_RATING_OPTION) ) // error checking
        return FALSE;

    // Load from DB to g_u8CurrentRRT_Descriptor
#if(ENABLE_DB_ATSC_RRT5_API)
    MApp_DB_ATSC_Load_RRT_Descriptor(u8DimensionIdx, u8OptionIdx, (U8*)&g_u8CurrentRRT_Descriptor[0], REGION5_RATING_DES_MAX_LENGTH );
#else
    msAPI_MIU_Copy((U32)GET_RRT_DESCRIPTOR_ADDRESS(u8DimensionIdx, u8OptionIdx),  (U32)&g_u8CurrentRRT_Descriptor[0], REGION5_RATING_DES_MAX_LENGTH, MIU_SDRAM2SDRAM);
#endif

    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_ToggleRRT_DimensionValues(U8 u8ValueIndex)
{
    if( (u8ValueIndex<1)||(u8ValueIndex>REGION5_MAX_RATING_OPTION)||
        (g_u8CurrentRRT_Dimension>=REGION5_DIMENSION_NUM) ) // error checking
        return FALSE;

    stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_Dimension].u32CurrentOption ^= (1<<(u8ValueIndex-1));

    if (stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_Dimension].u16Graduated_Scale)
    {
        if (stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_Dimension].u32CurrentOption & (0x01<<(u8ValueIndex-1)))
        {
            stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_Dimension].u32CurrentOption |= (0xFFFF<<(u8ValueIndex-1));
        }
        else
        {
            stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_Dimension].u32CurrentOption =
            (stGenSettingVchipRegion5.stRegin5Dimension[g_u8CurrentRRT_Dimension].u32CurrentOption>>u8ValueIndex)<<u8ValueIndex;
        }
    }

    if ( (g_stVChipRatingInfo.u8DimVal0 && g_u8CurrentRRT_Dimension == 0) ||
         (g_stVChipRatingInfo.u8DimVal1 && g_u8CurrentRRT_Dimension == 1) ||
         (g_stVChipRatingInfo.u8DimVal2 && g_u8CurrentRRT_Dimension == 2) ||
         (g_stVChipRatingInfo.u8DimVal3 && g_u8CurrentRRT_Dimension == 3) ||
         (g_stVChipRatingInfo.u8DimVal4 && g_u8CurrentRRT_Dimension == 4) ||
         (g_stVChipRatingInfo.u8DimVal5 && g_u8CurrentRRT_Dimension == 5) ||
         (g_stVChipRatingInfo.u8DimVal6 && g_u8CurrentRRT_Dimension == 6) ||
         (g_stVChipRatingInfo.u8DimVal7 && g_u8CurrentRRT_Dimension == 7) ||
         (g_stVChipRatingInfo.u8DimVal8 && g_u8CurrentRRT_Dimension == 8) ||
         (g_stVChipRatingInfo.u8DimVal9 && g_u8CurrentRRT_Dimension == 9)
#if (ENABLE_MAX_RRT_DIMENSION_NUMBER)
      || (g_stVChipRatingInfo.u8DimVal10 && g_u8CurrentRRT_Dimension == 10)  ||
         (g_stVChipRatingInfo.u8DimVal11 && g_u8CurrentRRT_Dimension == 11)  ||
         (g_stVChipRatingInfo.u8DimVal12 && g_u8CurrentRRT_Dimension == 12)  ||
         (g_stVChipRatingInfo.u8DimVal13 && g_u8CurrentRRT_Dimension == 13)  ||
         (g_stVChipRatingInfo.u8DimVal14 && g_u8CurrentRRT_Dimension == 14)  ||
         (g_stVChipRatingInfo.u8DimVal15 && g_u8CurrentRRT_Dimension == 15)  ||
         (g_stVChipRatingInfo.u8DimVal16 && g_u8CurrentRRT_Dimension == 16)  ||
         (g_stVChipRatingInfo.u8DimVal17 && g_u8CurrentRRT_Dimension == 17)  ||
         (g_stVChipRatingInfo.u8DimVal18 && g_u8CurrentRRT_Dimension == 18)  ||
         (g_stVChipRatingInfo.u8DimVal19 && g_u8CurrentRRT_Dimension == 19)     ||
         (g_stVChipRatingInfo.u8DimVal20 && g_u8CurrentRRT_Dimension == 20)    ||
         (g_stVChipRatingInfo.u8DimVal21 && g_u8CurrentRRT_Dimension == 21)    ||
         (g_stVChipRatingInfo.u8DimVal22 && g_u8CurrentRRT_Dimension == 22)    ||
         (g_stVChipRatingInfo.u8DimVal23 && g_u8CurrentRRT_Dimension == 23)    ||
         (g_stVChipRatingInfo.u8DimVal24 && g_u8CurrentRRT_Dimension == 24)    ||
         (g_stVChipRatingInfo.u8DimVal25 && g_u8CurrentRRT_Dimension == 25)    ||
         (g_stVChipRatingInfo.u8DimVal26 && g_u8CurrentRRT_Dimension == 26)    ||
         (g_stVChipRatingInfo.u8DimVal27 && g_u8CurrentRRT_Dimension == 27)    ||
         (g_stVChipRatingInfo.u8DimVal28 && g_u8CurrentRRT_Dimension == 28)    ||
           (g_stVChipRatingInfo.u8DimVal29 && g_u8CurrentRRT_Dimension == 29) ||
         (g_stVChipRatingInfo.u8DimVal30 && g_u8CurrentRRT_Dimension == 30) ||
         (g_stVChipRatingInfo.u8DimVal31 && g_u8CurrentRRT_Dimension == 31) ||
         (g_stVChipRatingInfo.u8DimVal32 && g_u8CurrentRRT_Dimension == 32) ||
         (g_stVChipRatingInfo.u8DimVal33 && g_u8CurrentRRT_Dimension == 33) ||
         (g_stVChipRatingInfo.u8DimVal34 && g_u8CurrentRRT_Dimension == 34) ||
         (g_stVChipRatingInfo.u8DimVal35 && g_u8CurrentRRT_Dimension == 35) ||
         (g_stVChipRatingInfo.u8DimVal36 && g_u8CurrentRRT_Dimension == 36) ||
         (g_stVChipRatingInfo.u8DimVal37 && g_u8CurrentRRT_Dimension == 37) ||
         (g_stVChipRatingInfo.u8DimVal38 && g_u8CurrentRRT_Dimension == 38) ||
         (g_stVChipRatingInfo.u8DimVal39 && g_u8CurrentRRT_Dimension == 39) ||
         (g_stVChipRatingInfo.u8DimVal40 && g_u8CurrentRRT_Dimension == 40)
#endif
      )
    {
        fVChipPassWordEntered = FALSE;
        memset(&g_stVChipRatingInfo, 0, sizeof(g_stVChipRatingInfo));
    }

    return TRUE;
}

//*************************************************************************************************
void MApp_UiMenuFunc_ConvertTempChannelProgramNumber2Str (MS_VIRTUAL_CHANNEL_NUM *pstVirtualChNum, U8 *pu8Str)
{
    U8 u8NoOfDigit;
#if 0//(NEW_VIRTUAL_CHANNEL_STRUCTURE == ENABLE)
    MS_RF_CHANNEL_new pRf_Ch;
#endif

    u8NoOfDigit = MApp_GetNoOfDigit( pstVirtualChNum->major_num );
    MApp_UlongToString( pstVirtualChNum->major_num, pu8Str, u8NoOfDigit );

  #if ONE_PART_CHNO
    if(!pstVirtualChNum->fIsOnePartChNum)
    {
    #if 0//(NEW_VIRTUAL_CHANNEL_STRUCTURE == ENABLE)
        MApp_ChanProc_GetRfChannelPointer(&g_stPreVirtualCh, &pRf_Ch);
        if ( pRf_Ch.stTPSetting.fModulation != DEMOD_ATSC_MODE_NTSC )
    #else
        //if ( g_stPreVirtualCh.stTPSetting.fModulation != DEMOD_ATSC_MODE_NTSC )
        if( !MApp_ChanProc_Is_ChannelAtv(&g_stPreVirtualCh) )
    #endif
        {
            pu8Str[u8NoOfDigit++] = CHAN_NUM_SEPERATOR;//'-';
            MApp_UlongToString( ( U32 ) pstVirtualChNum->minor_num, pu8Str + u8NoOfDigit, MApp_GetNoOfDigit( pstVirtualChNum->minor_num ) );
        }
    }
  #else
    pu8Str[u8NoOfDigit++] = CHAN_NUM_SEPERATOR;//'-';
    MApp_UlongToString( ( U32 ) pstVirtualChNum->minor_num, pu8Str + u8NoOfDigit, MApp_GetNoOfDigit( pstVirtualChNum->minor_num ) );
  #endif
}

BOOLEAN MApp_UiMenuFunc_EventInfoSignalUpdate(void)
{
    if(IS_HIDE_CH_ATSC(MApp_ChanProc_GetCurProgIndex()))
    {
        u8PreSignalSNR = (U8)SIGNAL_NO;
    }
    else
    {
        u8PreSignalSNR = (U8)msAPI_Tuner_CheckSignalSNR();
    }
    return TRUE;
}

BOOLEAN MApp_UiMenuFunc_IsCCEnable(void)
{
     return MApp_CC_CheckExist();
}

void MApp_ReturnResolution(U8 *strBuffer)
{
    U16 h, v;
    U8 vfreq;
    static char locbuf[MSAPI_DMX_SECTION_4K];

    if (MApp_PCMode_GetCurrentState(MAIN_WINDOW) == E_PCMODE_STABLE_UN_SUPPORT_MODE)
    {
        strBuffer[0] = 0;
        return;
    }

    h = v = vfreq = 0;
#if (ENABLE_SCART_VIDEO)
    if(IsAVInUse()||IsSVInUse()||IsScartInUse()||IsATVInUse())
#else
    if(IsAVInUse()||IsSVInUse()||IsATVInUse())
#endif
    {
#if (ENABLE_ATSC)
        if(!(msAPI_AVD_Get_LatchStatus() & VD_HSYNC_LOCKED))
        {
           printf("VD status not VD_HSYNC_LOCKED\n");
           printf("msAPI_AVD_Get_LatchStatus() is %x \n",msAPI_AVD_Get_LatchStatus());
           printf("mvideo_vd_get_videosystem() is %x \n",mvideo_vd_get_videosystem());
           return;
        }

        switch( mvideo_vd_get_videosystem() )
        {
            case SIG_NTSC:
            case SIG_NTSC_443:
                MApp_U16StringToU8String((U16*)MApp_ZUI_API_GetString(en_str_NTSC),strBuffer,(U8)MApp_UiMenu_u16Strlen((U16*)MApp_ZUI_API_GetString(en_str_NTSC)));
                strBuffer += 4;
                break;

            case SIG_PAL:
            case SIG_PAL_M:
            case SIG_PAL_NC:
                MApp_U16StringToU8String((U16*)MApp_ZUI_API_GetString(en_str_PAL),strBuffer,(U8)MApp_UiMenu_u16Strlen((U16*)MApp_ZUI_API_GetString(en_str_PAL)));
                strBuffer += 3;
                break;

            case SIG_SECAM:
                MApp_U16StringToU8String((U16*)MApp_ZUI_API_GetString(en_str_SECAM),strBuffer,(U8)MApp_UiMenu_u16Strlen((U16*)MApp_ZUI_API_GetString(en_str_SECAM)));
                strBuffer += 5;
                break;
            default:
                break;
        }
#endif
    }
    else if(IsYPbPrInUse())
    {
        if( MApi_XC_PCMonitor_SyncLoss(MAIN_WINDOW) )
            return;

        // h = MApp_PCMode_Get_HResolution(MAIN_WINDOW);
        v = MApp_PCMode_Get_VResolution(MAIN_WINDOW,TRUE);
        vfreq = (MApi_XC_PCMonitor_Get_VFreqx10(MAIN_WINDOW) + 5) / 10;

        memset(locbuf, 0, sizeof(locbuf));
        snprintf(locbuf,sizeof(locbuf), "%u%c %uHz",v,
        MApi_XC_PCMonitor_GetSyncStatus(MAIN_WINDOW) & XC_MD_INTERLACE_BIT ? 'i' : 'p',
            vfreq);
        strncpy((char *)strBuffer,locbuf, strlen(locbuf));
        *(strBuffer+strlen(locbuf)) = 0;
    }
    else if(IsVgaInUse())
    {
        if(MApi_XC_PCMonitor_SyncLoss(MAIN_WINDOW))
            return;

        h = MApp_PCMode_Get_HResolution(MAIN_WINDOW,TRUE);
        v = MApp_PCMode_Get_VResolution(MAIN_WINDOW,TRUE);
        vfreq = (MApi_XC_PCMonitor_Get_VFreqx10(MAIN_WINDOW) + 5) / 10;

         if(vfreq > 58 && vfreq < 61)
         {
                vfreq= 60;
          }
         else  if(vfreq > 63 && vfreq < 66)
          {
                vfreq= 65;
          }
          else if(vfreq > 68 && vfreq < 71)
          {
                vfreq= 70;
          }
          else if(vfreq >=71 && vfreq <=73)
          {
                vfreq= 72;
          }
          else if( vfreq > 73 && vfreq < 76)
          {
                vfreq= 75;
          }
        memset(locbuf, 0, sizeof(locbuf));
        snprintf(locbuf,sizeof(locbuf), "%ux%u %uHz", h, v, vfreq);
        strcpy((char *)strBuffer,locbuf);

    }
    else if(IsHDMIInUse())
    {

        if( MApi_XC_PCMonitor_SyncLoss(MAIN_WINDOW) )
            return;

        v = MApp_PCMode_Get_VResolution(MAIN_WINDOW,FALSE);
        h = MApp_PCMode_Get_HResolution(MAIN_WINDOW,FALSE);
        vfreq = (MApi_XC_PCMonitor_Get_VFreqx10(MAIN_WINDOW) + 5) / 10;
        memset(locbuf, 0, sizeof(locbuf));

        if((v==0)||(h==0))
        {
            return ;
        }

        if ((v >= 710 && h <= 1540) && (v >= 470 && v<= 490))
        {
            v = 480;
        }
        else if ((h>=710 && h<=1540)&&(v > 566 && v < 586))
        {
            v = 576;
        }
        // 1280x720
        else if((v > 710 && v < 730) && (h> 1270 && h < 1290))
        {
            v = 720;
        }
        // 1920x1080
        else if((v > 1070 && v < 1090) && (h > 1910 && h < 1930))
        {
            v = 1080;
        }
        else
        {
            if ((h >= 620&& h <= 670) && (v >= 470 && v <= 490))
            {
                v = 480;
                h = 640;
            }
            else if ((h >= 780&& h <= 840) && (v >= 580&& v <= 620))
            {
                v = 600;
                h = 800;
            }
            else if ((h >= 1000&& h <= 1050) && (v >= 740&& v <= 790))
            {
                v = 768;
                h = 1024;
            }
            else if( (h> 1270 && h < 1300)&&(v > 740 && v < 790))
            {
                v = 768;
                h = 1280;
            }
            else if( (h> 1300 && h < 1390)&&(v > 740 && v < 790))
            {
                v = 768;
                h = 1360;
            }
            else if ((h >= 1260&& h <= 1300) && (v >= 1000&& v <= 1250))
            {
                v = 1024;
                h = 1280;
            }
            else if ((h >= 1580&& h <= 1620) && (v >= 1180&& v <= 1220))
            {
                v = 1200;
                h = 1600;
            }
            else
            {
                ;
            }

            if(vfreq > 47 && vfreq < 53)
            {
                vfreq= 50;
            }
            else if(vfreq > 55 && vfreq < 57)
            {
                vfreq= 56;
            }
            else if(vfreq > 58 && vfreq < 62)
            {
                vfreq= 60;
            }
            else if(vfreq > 67 && vfreq < 71)
            {
                vfreq= 70;
            }
            else if(vfreq >= 71 && vfreq < 73)
            {
                vfreq= 72;
            }
            else if( vfreq > 73 && vfreq < 77)
            {
                vfreq= 75;
            }
            else if( vfreq > 80 && vfreq < 85)
            {
                vfreq= 85;
            }
            snprintf(locbuf,sizeof(locbuf), "%ux%u %uHz", h, v, vfreq);
            strcpy((char *)strBuffer,locbuf);
            return;
        }

        if( vfreq > 55 )
        {// (60)
            vfreq = 60;
        }
        else if( vfreq > 45 )
        {// (50)
            vfreq =50;
        }
        else if( vfreq > 27 )
        {// (30)
            vfreq = 30;
        }
        else if( vfreq > 24 )
        {//(25P)
            vfreq = 25;
        }
        else if( vfreq > 23 )
        {//(24P)
            vfreq = 24;
        }
        else if( vfreq > 20 )
        {//(23P)
            vfreq = 23;
        }
        snprintf(locbuf,sizeof(locbuf), "%u%c %uHz", v,
                (MApi_XC_PCMonitor_GetSyncStatus(MAIN_WINDOW) & XC_MD_INTERLACE_BIT) ? 'i' : 'p',
                vfreq);
        strcpy((char *)strBuffer,locbuf);
    }
    //*strBuffer = 0;
}

#if (ENABLE_AUDIO_ONLY_CUSTOMERMODE == 1)

void MApp_UiMenuFunc_EnterAudioOnlyMode( void )
{
    fEnableAudioOnlyFunc = ENABLE;
    MApi_PNL_SetBackLight(DISABLE);
    //printf("MApp_UiMenuFunc_EnterAudioOnlyMode: %x ; g_AudioOnly: %x\n", fEnableAudioOnlyFunc, g_AudioOnly);
}

void MApp_UiMenuFunc_ExitAudioOnlyMode( void )
{
    fEnableAudioOnlyFunc = DISABLE;
    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_AUDIO_ONLY, DISABLE, 0, MAIN_WINDOW);
    if (MApp_ZUI_GetActiveOSD() == E_OSD_MAIN_MENU)
        MApp_ZUI_API_InvalidateWindow(HWND_MENU_SOUND_AUDIO_ONLY);
    MApi_PNL_SetBackLight(ENABLE);
    //printf("MApp_UiMenuFunc_ExitAudioOnlyMode: %x ; g_AudioOnly: %x\n", fEnableAudioOnlyFunc, g_AudioOnly);
}
#endif

//====================================================================
#if EN_INPUT_LABEL_EDIT
//static EN_INPUT_LABEL_PRESENT_TYPE sInputLabelPresentType;
static E_UI_INPUT_SOURCE sUIInputSourceType;
//InputLabelPresentString length must big than DefaultSourceString length,for memcpy() end character
//static U8 InputLabelPresentString[][MAX_INPUTLLABEL_CHAR_NUM+1] = {
//"", "Antenna", "Cable", "Satellite", "DTV", "DVD", "Blu_ray", "HD_DVD",  "XBOX", "Wii", "PS3", "Game", "Computer", "VCR", "DV", " "};

BOOL MApp_UiMenuFunc_InputLabel_SetCustomLabel(U8* str)
{
    memcpy(stGenSetting.g_SysSetting.g_InputLableEdit[sUIInputSourceType], str, MAX_INPUTLLABEL_CHAR_NUM + 1);
    return TRUE;
}
#endif

void MApp_UiMenuFunc_InputLabel_GetCustomLabel(U8* tempStr)
{
    U8 i;
    memset(tempStr,  CHAR_SPACE, MAX_INPUTLLABEL_CHAR_NUM);
    memcpy(tempStr, stGenSetting.g_SysSetting.g_InputLableEdit[sUIInputSourceType], MAX_INPUTLLABEL_CHAR_NUM + 1);
    tempStr[MAX_INPUTLLABEL_CHAR_NUM] = '\0';
    for (i=MAX_INPUTLLABEL_CHAR_NUM-1; i > 0; i--)
    {
        if (tempStr[i] == (U8)CHAR_SPACE)
        {
            tempStr[i] = '\0';
        }
        else
            break;
    }
}


//=============================================================


