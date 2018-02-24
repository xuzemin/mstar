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


#define MAPP_ZUI_ACTATVMANUALTUNING_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "apiXC.h"
#include "apiXC_Adc.h"

#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_APIdraw.h"

#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_ACTglobal.h"
#include "OSDcp_String_EnumIndex.h"
#include "OSDcp_Bitmap_EnumIndex.h"
#include "ZUI_exefunc.h"
#include "MApp_SignalMonitor.h"
#include "MApp_ATV_ManualTuning_Main.h"
#include "MApp_ATV_Scan.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_SaveData.h"
#include "MApp_UiMenuDef.h"
#include "msAPI_Memory.h"
#include "msAPI_FreqTableDTV.h"
#include "msAPI_ChProc.h"
#include "msAPI_ATVSystem.h"
#include "msAPI_audio.h"
#include "msAPI_Tuning.h"
#include "msAPI_VD.h"
#include "MApp_BlockSys.h"
#include "msAPI_FreqTableATV.h"
#include "msAPI_Timer.h"

#if (ENABLE_DTV)
#include "mapp_demux.h"
#include"MApp_BlockSys.h"
#include"MApp_MultiTasks.h"
#endif

#include "MApp_ChannelChange.h"
#include "MApp_ChannelList.h"
#include "MApp_GlobalFunction.h"
#include "MApp_TopStateMachine.h"
#include <stdio.h>
#include <string.h>
#include "msAPI_ATVSystem.h"
#include "msAPI_FreqTableATV.h"
#include "MApp_TopStateMachine.h"
#include "MApp_Menu_Main.h"
#include "MApp_TV.h"
#include "MApp_InputSource.h"
#include "MApp_ZUI_ACTinputsource.h"
#include "MApp_ZUI_ACTmainpage.h"
#include "msAPI_Video.h"

#include "MApp_ParentalRating.h"

#if(CHAKRA3_AUTO_TEST)
#include "MApp_AutoTest.h"
#endif

#include "MApp_Func_AtvManualTuning.h"
#include "MApp_InputSource.h"

/////////////////////////////////////////////////////////////////////


extern EN_ATV_MANUALTUNING_STATE enAtvManualTuningState;
static EN_ATV_MANUALTUNING_STATE _enTargetAtvManualTuningState;
static U8 u8ManualScan_StoreChannel_Value;
static BOOLEAN bManualScan_Skip_IsChange;

//*************************************************************************
//              Defines
//*************************************************************************

typedef enum
{
    ATV_MANUAL_TUNING_COMMAND_INIT,
    ATV_MANUAL_TUNING_COMMAND_UP,
    ATV_MANUAL_TUNING_COMMAND_DOWN,
} EN_ATV_MANUAL_TUNING_COMMAND_TYPE;

typedef struct _MENU_KEY2BTN_STRUCT
{
    VIRTUAL_KEY_CODE key;
    HWND hwnd;
} MENU_KEY2BTN_STRUCT;

#define ATV_MANUAL_SCAN_DELAY 200
/********************************************************************************/
/*                    Macro                                                     */
/********************************************************************************/
#define ATV_MANUAL_TUNING_DBINFO(y)    //y
#define ATV_FREQUENCE_TENTUNING ENABLE

extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);

/********************************************************************************/
/*                      Local                                                   */
/********************************************************************************/
void _MApp_ZUI_ACT_AtvSetUserVideoStandard(BOOLEAN bMap, U16 u16VideoStandard)
{
    BYTE u8ChNum = msAPI_ATV_GetCurrentProgramNumber();
    AVD_VideoStandardType eUserStd;

    if (bMap)    //Should map to AVD_VideoStandardType
    {
        eUserStd = (EN_ATV_VideoStandard_AUTO == u16VideoStandard) ? E_VIDEOSTANDARD_AUTO : (AVD_VideoStandardType)(u16VideoStandard);
        if (E_VIDEOSTANDARD_AUTO == eUserStd)
        {
            msAPI_AVD_StartAutoStandardDetection();
        }
        else
        {
            msAPI_AVD_ForceVideoStandard(eUserStd);
        }
    }
    else
        eUserStd = (AVD_VideoStandardType)u16VideoStandard;

    msAPI_ATV_SetUserVideoStandardOfProgram(u8ChNum, eUserStd);
    //printf(">>>> %s u8ChNum:%u eUserStd:%u videoStd:%u\n", __FUNCTION__, u8ChNum, eUserStd, msAPI_AVD_GetVideoStandard());
}

EN_ATV_VIDEOSTANDARD_TYPE _MApp_ZUI_ACT_AtvGetUserVideoStandard(void)
{
    BYTE u8ChNum = msAPI_ATV_GetCurrentProgramNumber();
    AVD_VideoStandardType eAtvVideoStandardType = msAPI_ATV_GetUserVideoStandardOfProgram(u8ChNum);

    //printf(">>>> %s u8ChNum:%u eUserStd:%u videoStd:%u\n", __FUNCTION__, u8ChNum, eAtvVideoStandardType, msAPI_AVD_GetVideoStandard());
    if (E_VIDEOSTANDARD_AUTO == eAtvVideoStandardType || E_VIDEOSTANDARD_NOTSTANDARD == eAtvVideoStandardType)
    {
        return  EN_ATV_VideoStandard_AUTO;
    }
    else
    {
        return (EN_ATV_VIDEOSTANDARD_TYPE)(eAtvVideoStandardType);
    }
}

static void _MApp_ZUI_ACT_SetAtvManualTuningState(EN_ATV_MANUALTUNING_STATE eState)
{
    _enTargetAtvManualTuningState = eState;
}

static EN_ATV_MANUALTUNING_STATE _MApp_ZUI_ACT_GetAtvManualTuningState(void)
{
   return _enTargetAtvManualTuningState;
}


static void _MApp_ZUI_ACT_SetStoreChannelValue(U8 u8CHVal)
{
    u8ManualScan_StoreChannel_Value = u8CHVal;
}

static U8 _MApp_ZUI_ACT_GetStoreChannelValue(void)
{
   return u8ManualScan_StoreChannel_Value;
}

static void MApp_ZUI_ACT_AtvManualTuningChangeCurrentCH(U16 Value )
{
    dmSetLastWatchedOrdinal();
    MApp_ChannelChange_DisableAV(MAIN_WINDOW);

    //Cancel Freeze
    if(MApp_IsImageFrozen())
    {
        MApp_SetImageFrozen(FALSE);
        MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);
    }
    if(Value <= (msAPI_ATV_GetChannelMax()-1) && Value >= (msAPI_ATV_GetChannelMin()-1))
    {
        _MApp_ZUI_ACT_SetStoreChannelValue((U8)Value);
    }

    msAPI_ATV_SetCurrentProgramNumber(_MApp_ZUI_ACT_GetStoreChannelValue());
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_SIF, E_AUDIOMUTESOURCE_ATV);
    //BY 20090406 msAPI_VD_AdjustVideoFactor(E_ADJUST_VIDEOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_TUNER);
    msAPI_AVD_TurnOffAutoAV();
    msAPI_Tuner_ChangeProgram();
    //msAPI_VD_ClearSyncCheckCounter();
    msAPI_AVD_ClearAspectRatio();
    MApp_CheckBlockProgramme();
    MApp_ZUI_API_InvalidateWindow(HWND_ATUNE_STORAGE_TO_OPTION);
    MApp_ZUI_API_InvalidateWindow(HWND_ATUNE_CURRENT_CH_OPTION);
    MApp_ZUI_API_InvalidateWindow(HWND_ATUNE_FREQUENCY_VALUE_TXT);

    MApp_Set_IdleInputValue(0);
    MApp_Set_IdleDigitCount(0);

}


S32 MApp_ZUI_ACT_AtvManualTuningWinProc(HWND hwnd, PMSG msg)
{
    switch(msg->message)
    {
        case MSG_CREATE:
            {

            }
            break;

        case MSG_TIMER:
            {
                MApp_ZUI_API_KillTimer(hwnd, 0);
                switch(hwnd)
                {
                    case HWND_ATUNE_FINE_TUNE_LARROW1:
                    case HWND_ATUNE_FINE_TUNE_RARROW1:
                        MApp_ZUI_API_ShowWindow(hwnd, SW_SHOW);
                    break;

                    case HWND_ATUNE_FINE_TUNE_LARROW2:
                    case HWND_ATUNE_FINE_TUNE_RARROW2:
                        MApp_ZUI_API_ShowWindow(hwnd, SW_HIDE);
                    break;
                }
                MApp_ZUI_API_InvalidateWindow(HWND_ATUNE_FREQUENCY_VALUE_TXT);
            }
            break;
        default:
            break;

    }
    return DEFAULTWINPROC(hwnd, msg);

}

BOOLEAN MApp_ZUI_ACT_ExecuteAtvManualTuningAction(U16 act)
{
    U8 u8TmpValue;
    static BOOLEAN bWaitUpdateSignal = FALSE;
    MS_SCANMENU_SETTING *pstScanMenuSetting = NULL;

    MApp_GetGenSetting(EN_GENSETTING_CLASS_SCANMENU,  (void *)&pstScanMenuSetting);

    //printf("\e[31;1m >> %s(0x%X) \33[m \n", __FUNCTION__, act);

    switch(act)
    {
        case EN_EXE_POWEROFF:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _MApp_ZUI_ACT_SetAtvManualTuningState(STATE_ATV_MANUALTUNING_GOTO_STANDBY);
            return TRUE;

        case EN_EXE_CLOSE_CURRENT_OSD:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _MApp_ZUI_ACT_SetAtvManualTuningState(STATE_ATV_MANUALTUNING_CLEAN_UP);
            return TRUE;

        case EN_EXE_GOTO_MAINMENU:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _MApp_ZUI_ACT_SetAtvManualTuningState( STATE_ATV_MANUALTUNING_GOTO_MAIN_MENU);
            return TRUE;

        case EN_EXE_DEC_STORAGE_TO_OPTION:
        case EN_EXE_INC_STORAGE_TO_OPTION:
            u8TmpValue = _MApp_ZUI_ACT_GetStoreChannelValue();
            u8TmpValue = MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_STORAGE_TO_OPTION,
                    u8TmpValue, msAPI_ATV_GetChannelMin()-1, msAPI_ATV_GetChannelMax()-1, 1);
            MApp_ZUI_API_InvalidateWindow(HWND_ATUNE_STORAGE_TO_OPTION);
            _MApp_ZUI_ACT_SetStoreChannelValue(u8TmpValue);
            return TRUE;

        case EN_EXE_DEC_SYSTEM_OPTION:
        case EN_EXE_INC_SYSTEM_OPTION:
        {
          #if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_ATV_SYSTEM || (TV_SYSTEM == TV_NTSC) )

            pstScanMenuSetting->u8SoundSystem = EN_ATV_SystemType_M;

            if(msAPI_ATV_IsProgramAutoColorSystem(msAPI_ATV_GetCurrentProgramNumber()))
            {
                pstScanMenuSetting->u8VideoSystem_Brazil=E_VIDEOSTANDARD_BRAZIL_AUTO;
            }
            else
            {
                switch(msAPI_ATV_GetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber()))
                {
                    case E_VIDEOSTANDARD_NTSC_M:
                        pstScanMenuSetting->u8VideoSystem_Brazil=E_VIDEOSTANDARD_BRAZIL_NTSC_M;
                        break;
                    case E_VIDEOSTANDARD_PAL_N:
                        pstScanMenuSetting->u8VideoSystem_Brazil=E_VIDEOSTANDARD_BRAZIL_PAL_N;
                        break;
                    case E_VIDEOSTANDARD_PAL_M:
                        pstScanMenuSetting->u8VideoSystem_Brazil=E_VIDEOSTANDARD_BRAZIL_PAL_M;
                        break;
                    default:
                        ASSERT(0);
                        pstScanMenuSetting->u8VideoSystem_Brazil=E_VIDEOSTANDARD_BRAZIL_NTSC_M;
                        break;
                }
            }
            pstScanMenuSetting->u8VideoSystem_Brazil=
               (U8) MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_SYSTEM_OPTION,
                    pstScanMenuSetting->u8VideoSystem_Brazil,
                    E_VIDEOSTANDARD_BRAZIL_NTSC_M,
                    E_VIDEOSTANDARD_BRAZIL_AUTO,
                    1);

            if(pstScanMenuSetting->u8VideoSystem_Brazil==E_VIDEOSTANDARD_BRAZIL_AUTO)
                msAPI_ATV_SetProgramAutoColorSystem(msAPI_ATV_GetCurrentProgramNumber(),TRUE);
            else
                msAPI_ATV_SetProgramAutoColorSystem(msAPI_ATV_GetCurrentProgramNumber(),FALSE);


            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_INTERNAL_4_MUTEON, E_AUDIOMUTESOURCE_ATV);
            msAPI_Timer_Delayms(DELAY_FOR_ENTERING_MUTE);

            switch(pstScanMenuSetting->u8VideoSystem_Brazil)
            {
                case E_VIDEOSTANDARD_BRAZIL_NTSC_M:
                   msAPI_AVD_SetVideoStandard (E_VIDEOSTANDARD_NTSC_M);
                   msAPI_ATV_SetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber(),E_VIDEOSTANDARD_NTSC_M);
                break;

                case E_VIDEOSTANDARD_BRAZIL_PAL_M:
                   msAPI_AVD_SetVideoStandard (E_VIDEOSTANDARD_PAL_M);
                   msAPI_ATV_SetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber(),E_VIDEOSTANDARD_PAL_M);
                break;

                case E_VIDEOSTANDARD_BRAZIL_PAL_N:
                   msAPI_AVD_SetVideoStandard (E_VIDEOSTANDARD_PAL_N);
                   msAPI_ATV_SetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber(),E_VIDEOSTANDARD_PAL_N);
                break;

                default:
                   msAPI_AVD_StartAutoStandardDetection();
                   msAPI_AVD_GetResultOfAutoStandardDetection();
                   msAPI_ATV_SetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber(),msAPI_AVD_GetResultOfAutoStandardDetection());
                break;
            }

            msAPI_Tuner_UpdateMediumAndChannelNumber();
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_INTERNAL_4_MUTEOFF, E_AUDIOMUTESOURCE_ATV);

            pstScanMenuSetting->u8RFChannelNumber = msAPI_Tuner_GetChannelNumber();
            pstScanMenuSetting->u8ATVMediumType = (EN_ATV_BAND_TYPE)msAPI_Tuner_GetMedium();
            pstScanMenuSetting->u8LSystem = FALSE;
            MApp_ZUI_API_InvalidateWindow(HWND_ATUNE_SYSTEM_OPTION);
            return TRUE;
          #else
            AUDIOSTANDARD_TYPE eSoundSystem;

            if(act == EN_EXE_INC_SYSTEM_OPTION)
            {
                switch (pstScanMenuSetting->u8SoundSystem)
                {
                    case EN_ATV_SystemType_BG:
                         pstScanMenuSetting->u8SoundSystem = EN_ATV_SystemType_I;
                        break;

                    case EN_ATV_SystemType_I:
                         pstScanMenuSetting->u8SoundSystem = EN_ATV_SystemType_DK;
                        break;

                  #if ( ENABLE_DTMB_CHINA_APP || ENABLE_DVB_TAIWAN_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP || (TV_SYSTEM == TV_NTSC) )
                    case EN_ATV_SystemType_DK:
                         pstScanMenuSetting->u8SoundSystem = EN_ATV_SystemType_M;
                        break;

                    case EN_ATV_SystemType_M:
                         pstScanMenuSetting->u8SoundSystem = EN_ATV_SystemType_BG;
                        break;
                  #else
                    case EN_ATV_SystemType_DK:
                         pstScanMenuSetting->u8SoundSystem = EN_ATV_SystemType_L;
                        break;

                    case EN_ATV_SystemType_L:
                         pstScanMenuSetting->u8SoundSystem = EN_ATV_SystemType_BG;
                        break;
                  #endif
                }
            }
            else
            {
                switch (pstScanMenuSetting->u8SoundSystem)
                {
                    case EN_ATV_SystemType_I:
                         pstScanMenuSetting->u8SoundSystem = EN_ATV_SystemType_BG;
                        break;

                    case EN_ATV_SystemType_DK:
                         pstScanMenuSetting->u8SoundSystem = EN_ATV_SystemType_I;
                        break;

                  #if ( ENABLE_DTMB_CHINA_APP || ENABLE_DVB_TAIWAN_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP || (TV_SYSTEM == TV_NTSC) )
                    case EN_ATV_SystemType_M:
                         pstScanMenuSetting->u8SoundSystem = EN_ATV_SystemType_DK;
                        break;

                    case EN_ATV_SystemType_BG:
                         pstScanMenuSetting->u8SoundSystem = EN_ATV_SystemType_M;
                        break;

                  #else
                    case EN_ATV_SystemType_L:
                         pstScanMenuSetting->u8SoundSystem = EN_ATV_SystemType_DK;
                        break;

                    case EN_ATV_SystemType_BG:
                         pstScanMenuSetting->u8SoundSystem = EN_ATV_SystemType_L;
                        break;

                  #endif
                }
            }

            switch (pstScanMenuSetting->u8SoundSystem)
            {
                case EN_ATV_SystemType_BG:
                     eSoundSystem = E_AUDIOSTANDARD_BG;
                    break;

                case EN_ATV_SystemType_I:
                     eSoundSystem = E_AUDIOSTANDARD_I;
                    break;

                case EN_ATV_SystemType_DK:
                     eSoundSystem = E_AUDIOSTANDARD_DK;
                    break;

              #if ( ENABLE_DTMB_CHINA_APP || ENABLE_DVB_TAIWAN_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP || (TV_SYSTEM == TV_NTSC) )
                case EN_ATV_SystemType_M:
                     eSoundSystem = E_AUDIOSTANDARD_M;
                    break;
              #else
                case EN_ATV_SystemType_L:
                     eSoundSystem = E_AUDIOSTANDARD_L;
                    break;
              #endif

                default:
                  #if ( ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP )
                     eSoundSystem = E_AUDIOSTANDARD_DK;
                  #else
                     eSoundSystem = E_AUDIOSTANDARD_BG;
                  #endif
                     break;
            }

            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_INTERNAL_4_MUTEON, E_AUDIOMUTESOURCE_ATV);

            msAPI_Timer_Delayms(DELAY_FOR_ENTERING_MUTE);
            msAPI_AUD_ForceAudioStandard((AUDIOSTANDARD_TYPE)eSoundSystem);
            msAPI_Tuner_UpdateMediumAndChannelNumber();
            msAPI_Tuner_SetIF();
            msAPI_SetTunerPLL();

            msAPI_Timer_Delayms(DELAY_FOR_STABLE_SIF);
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_INTERNAL_4_MUTEOFF, E_AUDIOMUTESOURCE_ATV);

            pstScanMenuSetting->u8RFChannelNumber = msAPI_Tuner_GetChannelNumber();
            pstScanMenuSetting->u8ATVMediumType = (EN_ATV_BAND_TYPE)msAPI_Tuner_GetMedium();

        #if ( ENABLE_DTMB_CHINA_APP || ENABLE_DVB_TAIWAN_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP || (TV_SYSTEM == TV_NTSC) )
            ;
        #else
            if (pstScanMenuSetting->u8SoundSystem == EN_ATV_SystemType_L)
            {
                pstScanMenuSetting->u8LSystem = TRUE;
            }
            else
        #endif
            {
                pstScanMenuSetting->u8LSystem = FALSE;
            }

            MApp_ZUI_API_InvalidateWindow(HWND_ATUNE_SYSTEM_OPTION);
          #endif

            return TRUE;
        }


        case EN_EXE_DEC_VIDEO_STANDARD:
        case EN_EXE_INC_VIDEO_STANDARD:
        {
            U16 u16VideoStandard;
            MApp_FuncExec_AtvManualTuningPage(EN_FUNC_ATV_MANUAL_TUNING_GET_USER_VIDEO_STANDARD , (void *)&u16VideoStandard);
            u16VideoStandard = MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_VIDEO_STANDARD,
                    u16VideoStandard,
                    EN_ATV_VideoStandard_PAL_BGHI,
                    EN_ATV_VideoStandard_MAX-1,
                    1);
            MApp_ZUI_API_InvalidateWindow(HWND_ATUNE_VIDEO_STANDARD_OPTION);
            MApp_FuncExec_AtvManualTuningPage(EN_FUNC_ATV_MANUAL_TUNING_SET_USER_VIDEO_STANDARD_BY_MAP, (void *)&u16VideoStandard);
            bWaitUpdateSignal = FALSE;

            return TRUE;
        }


        case EN_EXE_DEC_CURRENT_CH_OPTION:
        case EN_EXE_INC_CURRENT_CH_OPTION:
        {
            bWaitUpdateSignal = FALSE;
            dmSetLastWatchedOrdinal();
            MApp_ChannelChange_DisableAV(MAIN_WINDOW);

            //Cancel Freeze
            if(MApp_IsImageFrozen())
            {
                MApp_SetImageFrozen( FALSE);
                MApi_XC_FreezeImg(TRUE, MAIN_WINDOW);
            }

            u8TmpValue =
            MApp_ZUI_ACT_DecIncValue_Cycle(
                    act==EN_EXE_INC_CURRENT_CH_OPTION,
                    msAPI_ATV_GetCurrentProgramNumber(), msAPI_ATV_GetChannelMin()-1, msAPI_ATV_GetChannelMax()-1, 1);
            MApp_ZUI_API_InvalidateWindow(HWND_ATUNE_CURRENT_CH_OPTION);

            _MApp_ZUI_ACT_SetStoreChannelValue(u8TmpValue);
            msAPI_ATV_SetCurrentProgramNumber(u8TmpValue);
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_SIF, E_AUDIOMUTESOURCE_ATV);
            //BY 20090406 msAPI_VD_AdjustVideoFactor(E_ADJUST_VIDEOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_TUNER);
            msAPI_AVD_TurnOffAutoAV();
            msAPI_Tuner_ChangeProgram();
            msAPI_AVD_ClearAspectRatio();
            MApp_CheckBlockProgramme();
            MApp_ZUI_API_InvalidateWindow(HWND_ATUNE_STORAGE_TO_OPTION);
            MApp_ZUI_API_InvalidateWindow(HWND_ATUNE_CURRENT_CH_OPTION);
            MApp_ZUI_API_InvalidateWindow(HWND_ATUNE_FREQUENCY_VALUE_TXT);
            MApp_ZUI_API_InvalidateWindow(HWND_ATUNE_SYSTEM_OPTION);
            MApp_ZUI_API_InvalidateWindow(HWND_ATUNE_VIDEO_STANDARD_OPTION);

            return TRUE;
        }


        case EN_EXE_GOTO_SCAN_DEC:
        {
            enAtvManualTuningState = STATE_ATV_MANUALTUNING_GOTO_ATV_SCAN;
            MApp_ATV_Scan_State_Init();
          #if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_SCAN )
            msAPI_ATV_SetDirectTuneFlag(FALSE);
          #endif
            pstScanMenuSetting->u8ScanType = SCAN_TYPE_MANUAL;
            pstScanMenuSetting->u8ATVManScanType = ATV_MAN_SCAN_TYPE_ONECH;
            pstScanMenuSetting->u8ATVManScanDir = ATV_MAN_SCAN_DOWN;
            MApp_ZUI_API_ShowWindow(HWND_ATUNE_SEARCH_RARROW1, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_ATUNE_SEARCH_LARROW2, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_ATUNE_FREQUENCY_VALUE_TXT, SW_SHOW);
            MApp_Set_IdleInputValue(0);
            MApp_Set_IdleDigitCount(0);
            MApp_ZUI_API_KillTimer(HWND_ATUNE_BG_PANE, 0);
            return TRUE;
        }


        case EN_EXE_GOTO_SCAN_INC:
        {
            enAtvManualTuningState = STATE_ATV_MANUALTUNING_GOTO_ATV_SCAN;
            MApp_ATV_Scan_State_Init();
          #if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_SCAN )
            msAPI_ATV_SetDirectTuneFlag(FALSE);
          #endif
            pstScanMenuSetting->u8ScanType = SCAN_TYPE_MANUAL;
            pstScanMenuSetting->u8ATVManScanType = ATV_MAN_SCAN_TYPE_ONECH;
            pstScanMenuSetting->u8ATVManScanDir = ATV_MAN_SCAN_UP;
            MApp_ZUI_API_ShowWindow(HWND_ATUNE_SEARCH_LARROW1, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_ATUNE_SEARCH_RARROW2, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_ATUNE_FREQUENCY_VALUE_TXT, SW_SHOW);
            MApp_Set_IdleDigitCount(0);
            MApp_Set_IdleInputValue(0);
            MApp_ZUI_API_KillTimer(HWND_ATUNE_BG_PANE, 0);

            return TRUE;
        }


        case EN_EXE_ATV_MANUAL_SCAN_SHOW_INFO:
        {
            MApp_ZUI_API_InvalidateWindow(HWND_ATUNE_FREQUENCY_VALUE_TXT);

            return TRUE;
        }


        case EN_EXE_ATV_MANUAL_SCAN_END:
        {
            MApp_ZUI_API_ShowWindow(HWND_ATUNE_SEARCH_LARROW1, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_ATUNE_SEARCH_RARROW1, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_ATUNE_SEARCH_LARROW2, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_ATUNE_SEARCH_RARROW2, SW_HIDE);
            MApp_ZUI_API_InvalidateWindow(HWND_ATUNE_SYSTEM_OPTION);
            MApp_ZUI_API_InvalidateWindow(HWND_ATUNE_FREQUENCY_VALUE_TXT);
            MApp_ZUI_API_SetTimer(HWND_ATUNE_BG_PANE, 0, MENU_TIME_OUT_MS);
            msAPI_Scaler_SetBlueScreen( DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
          #if(CHAKRA3_AUTO_TEST)
            MApp_AT_SendEvent(E_AT_EVENT_ATV_MANUAL_SCAN_FINISH, NULL);
          #endif
            bWaitUpdateSignal = TRUE;

            return TRUE;
        }


        case EN_EXE_UPDATE_SIGNAL_INFORMAT:
        {
            if (bWaitUpdateSignal)
            {
//                printf("Update video standard -> %u\n", msAPI_AVD_GetVideoStandard());
                U16 u16VideoStandard;
                MApp_FuncExec_AtvManualTuningPage(EN_FUNC_ATV_MANUAL_TUNING_GET_VIDEO_STANDARD, (void *)&u16VideoStandard);
                MApp_FuncExec_AtvManualTuningPage(EN_FUNC_ATV_MANUAL_TUNING_SET_USER_VIDEO_STANDARD, (void *)&u16VideoStandard);
                MApp_ZUI_API_InvalidateWindow(HWND_ATUNE_VIDEO_STANDARD_OPTION);
            }

            return TRUE;
        }


        case EN_EXE_ATV_MANUAL_SCAN_FINETUNE_UP:
        {
            MApp_ZUI_API_ShowWindow(HWND_ATUNE_FINE_TUNE_LARROW1, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_ATUNE_FINE_TUNE_RARROW2, SW_SHOW);
            if(MApp_IsImageFrozen())
            {
                MApp_SetImageFrozen(FALSE);
                MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);
            }
            msAPI_Tuner_AdjustUnlimitedFineTune(DIRECTION_UP);
            MApp_ZUI_API_SetTimer(HWND_ATUNE_FINE_TUNE_LARROW1, 0, ATV_MANUAL_SCAN_DELAY);
            MApp_ZUI_API_SetTimer(HWND_ATUNE_FINE_TUNE_RARROW2, 0, ATV_MANUAL_SCAN_DELAY);
            MApp_ZUI_API_InvalidateWindow(HWND_ATUNE_FREQUENCY_VALUE_TXT);

            return TRUE;
        }


        case EN_EXE_ATV_MANUAL_SCAN_FINETUNE_DOWN:
        {
            MApp_ZUI_API_ShowWindow(HWND_ATUNE_FINE_TUNE_RARROW1, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_ATUNE_FINE_TUNE_LARROW2, SW_SHOW);
            if(MApp_IsImageFrozen())
            {
                MApp_SetImageFrozen(FALSE);
                MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);
            }
            msAPI_Tuner_AdjustUnlimitedFineTune(DIRECTION_DOWN);
            MApp_ZUI_API_SetTimer(HWND_ATUNE_FINE_TUNE_RARROW1, 0, ATV_MANUAL_SCAN_DELAY);
            MApp_ZUI_API_SetTimer(HWND_ATUNE_FINE_TUNE_LARROW2, 0, ATV_MANUAL_SCAN_DELAY);
            MApp_ZUI_API_InvalidateWindow(HWND_ATUNE_FREQUENCY_VALUE_TXT);

            return TRUE;
        }


        case EN_EXE_CHANGE_CURRENT_CH:
        {
            U16 InputValue;
            if( MApp_Get_IdleDigitCount() != 0 )
            {
                InputValue = MApp_Get_IdleInputValue() ;

                //SHIFT 1 Start channl is 1 not 0,
                if(InputValue != 0)
                    InputValue = InputValue -1;

                MApp_ZUI_ACT_AtvManualTuningChangeCurrentCH(InputValue);

                MApp_Set_IdleDigitCount(0);
            }

            return TRUE;
        }


        case EN_EXE_CHANGE_CURRENT_CH_KEY_0:
        case EN_EXE_CHANGE_CURRENT_CH_KEY_1:
        case EN_EXE_CHANGE_CURRENT_CH_KEY_2:
        case EN_EXE_CHANGE_CURRENT_CH_KEY_3:
        case EN_EXE_CHANGE_CURRENT_CH_KEY_4:
        case EN_EXE_CHANGE_CURRENT_CH_KEY_5:
        case EN_EXE_CHANGE_CURRENT_CH_KEY_6:
        case EN_EXE_CHANGE_CURRENT_CH_KEY_7:
        case EN_EXE_CHANGE_CURRENT_CH_KEY_8:
        case EN_EXE_CHANGE_CURRENT_CH_KEY_9:
        {
            U8 u8TmpIdleDigitCount = MApp_Get_IdleDigitCount();
            U16 u16TmpIdleInputValue = MApp_Get_IdleInputValue();

            if (MApp_ZUI_API_GetFocus() == HWND_ATUNE_CURRENT_CH)
            {
                 if (u8TmpIdleDigitCount == 0)
                     u16TmpIdleInputValue = 0;

                u16TmpIdleInputValue = u16TmpIdleInputValue * 10 + (act - EN_EXE_CHANGE_CURRENT_CH_KEY_0);
                u8TmpIdleDigitCount++;

            #if ENABLE_SBTVD_SCAN
                //CABLE:CH 13~ CH 100 direct change,CH 1 ~ CH 12 Must press Enter to Change
                if((msAPI_ATV_GetCurrentAntenna() == ANT_CATV)&&(msAPI_SRC_IS_SBTVD_InUse()))
                {
                    if (u8TmpIdleDigitCount >= 3 || (u8TmpIdleDigitCount >= 2 && u16TmpIdleInputValue >12))
                    {
                        U16 InputValue;
                        InputValue = u16TmpIdleInputValue ;
                        //SHIFT 1 Start channl is 1 not 0,
                        if(InputValue != 0)
                        {
                            InputValue = InputValue -1;
                        }

                        MApp_ZUI_ACT_AtvManualTuningChangeCurrentCH(InputValue);
                    }
                }
                else
            #endif
                 //CH 11~ CH 100 direct change,CH 1 ~ CH 10 Must press Enter to Change
                {
                    if (u8TmpIdleDigitCount >= 3 || (u8TmpIdleDigitCount >= 2 && u16TmpIdleInputValue >10))
                    {
                        U16 InputValue;
                        InputValue = u16TmpIdleInputValue ;
                        //SHIFT 1 Start channl is 1 not 0,
                        if(InputValue != 0)
                        {
                            InputValue = InputValue -1;
                        }

                        MApp_ZUI_ACT_AtvManualTuningChangeCurrentCH(InputValue);
                    }
                }
                MApp_ZUI_API_InvalidateWindow(HWND_ATUNE_STORAGE_TO_OPTION);
                MApp_ZUI_API_InvalidateWindow(HWND_ATUNE_CURRENT_CH_OPTION);
                MApp_ZUI_API_InvalidateWindow(HWND_ATUNE_FREQUENCY_VALUE_TXT);
            }

        #if ATV_FREQUENCE_TENTUNING
            if(MApp_ZUI_API_GetFocus() == HWND_ATUNE_SEARCH)
            {
                if (u8TmpIdleDigitCount == 0)
                    u16TmpIdleInputValue = 0;

                u16TmpIdleInputValue = u16TmpIdleInputValue * 10 + (act - EN_EXE_CHANGE_CURRENT_CH_KEY_0);
                u8TmpIdleDigitCount++;

                if(u8TmpIdleDigitCount > 3)
                {
                    u16TmpIdleInputValue = u16TmpIdleInputValue%10;
                    u8TmpIdleDigitCount = 1;
                }

                MApp_ZUI_API_InvalidateWindow(HWND_ATUNE_FREQUENCY_VALUE_TXT);
            }
        #endif
            MApp_Set_IdleDigitCount(u8TmpIdleDigitCount);
            MApp_Set_IdleInputValue(u16TmpIdleInputValue);
        }
        return TRUE;


    #if ATV_FREQUENCE_TENTUNING
        case EN_EXE_SET_MANUAL_SCAN:
            if (MApp_Get_IdleDigitCount() > 0 )
            {
                MApp_Set_IdleInputValue(msAPI_Tuner_SetSearchManualTune(MApp_Get_IdleInputValue()));
                MApp_Set_IdleDigitCount(0);
                MApp_ZUI_API_InvalidateWindow(HWND_ATUNE_FREQUENCY_VALUE_TXT);
            }
            break;
    #endif


        case EN_EXE_SAVE_ATV_MANUAL_SCAN:
        {
            BOOLEAN bSkipFlag;
            u8TmpValue = _MApp_ZUI_ACT_GetStoreChannelValue();
            if((BYTE)u8TmpValue != msAPI_ATV_GetCurrentProgramNumber())
            {
                msAPI_ATV_SaveProgram((BYTE) u8TmpValue);
            }
            else
            {
                bSkipFlag = msAPI_ATV_IsProgramSkipped(u8TmpValue);
                msAPI_ATV_SaveProgram(u8TmpValue);

                if(bManualScan_Skip_IsChange == TRUE)
                    msAPI_ATV_SkipProgram(u8TmpValue, bSkipFlag);
                else
                    msAPI_ATV_SkipProgram(u8TmpValue, FALSE);
            }

        #if ENABLE_SKIP_ATV_PROGRAMS_SAME_TO_DTV_LCN
            if(ANT_AIR == msAPI_ATV_GetCurrentAntenna())
            {
                msAPI_CHPROC_CM_InitOridial();
                U16 u16Position;
                U16 u16Number;
                LOGICAL_CHANNEL_NUMBER LCN;
                U8 u8StoreAtvCh = u8TmpValue + 1;
                U16 u16TotalChCount = msAPI_CHPROC_CM_CountProgram(E_SERVICETYPE_ATV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + msAPI_CHPROC_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                for(u16Position = 0; u16Position < u16TotalChCount; u16Position++)
                {
                    u16Number = msAPI_CM_GetLogicalChannelNumber((MEMBER_SERVICETYPE)E_SERVICETYPE_DTV,u16Position);
                    LCN.wLCN = (WORD)u16Number;
                    if (LCN.stLCN.bPhysicalChannel == u8StoreAtvCh)
                    {
                        msAPI_ATV_SkipProgram(u8TmpValue, TRUE);
                        break;
                    }
                }
            }
        #elif ENABLE_SBTVD_CM_APP//fixed channel list show error
            if(msAPI_SRC_IS_SBTVD_InUse())
            {
                if(ANT_AIR == msAPI_ATV_GetCurrentAntenna())
                    msAPI_CHPROC_CM_InitOridial();
            }
        #endif
            bManualScan_Skip_IsChange = FALSE;
            MApp_ZUI_API_InvalidateWindow(HWND_ATUNE_CURRENT_CH_OPTION);

            return TRUE;
        }


        default:
            break;


    }
    return FALSE;
}

void MApp_ZUI_ACT_TerminateAtvManualTuning(void)
{
    //printf("[]term:atv manual tuning\n");
   #if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_SCAN || (TV_SYSTEM == TV_NTSC) )
    msAPI_ATV_SaveProgram_Exit_Menu((BYTE) msAPI_ATV_GetCurrentProgramNumber());
   #endif
    enAtvManualTuningState = _MApp_ZUI_ACT_GetAtvManualTuningState();
}

BOOLEAN MApp_ZUI_ACT_HandleAtvManualTuningKey(VIRTUAL_KEY_CODE key)
{
    //reset timer if any key
    MApp_ZUI_API_ResetTimer(HWND_ATUNE_BG_PANE, 0);

    switch(key)
    {
        case VK_EXIT:
            MApp_ZUI_ACT_ExecuteAtvManualTuningAction(EN_EXE_CLOSE_CURRENT_OSD);
            return TRUE;

        case VK_POWER:
            MApp_ZUI_ACT_ExecuteAtvManualTuningAction(EN_EXE_POWEROFF);
            return TRUE;

        case VK_MENU:
            MApp_ZUI_ACT_ExecuteAtvManualTuningAction(EN_EXE_GOTO_MAINMENU);
            _enReturnMenuItem = STATE_RETURN_ATV_MANUAL_TUNING;
            return TRUE;

        case VK_UP:
        case VK_DOWN:
            if( MApp_Get_IdleDigitCount() != 0 )
            {
                MApp_Set_IdleDigitCount(0);
                MApp_Set_IdleInputValue(0);
                MApp_ZUI_API_InvalidateWindow(HWND_ATUNE_FREQUENCY_VALUE_TXT);
            }
            return FALSE;

        default:
            break;

    }
    return FALSE;
}

static U16 _MApp_ZUI_ACT_AtvManualTuningGetProgramNumber(void)
{
    return ((U16)msAPI_ATV_GetCurrentProgramNumber());
}

LPTSTR MApp_ZUI_ACT_GetAtvManualTuningDynamicText(HWND hwnd)
{
// Market it by coverity_0514
#if 0//UI2 NoNeed
    U16 u16TempID = Empty;
#endif

    switch(hwnd)
    {
        case HWND_ATUNE_STORAGE_TO_OPTION:
            {
                U16 curStringLen = 0;
                U8 digit, u8TmpVal = _MApp_ZUI_ACT_GetStoreChannelValue();

                MApp_ZUI_API_Strcpy(&CHAR_BUFFER[0], MApp_ZUI_API_GetString(en_str_Storage_To));
                curStringLen = MApp_ZUI_API_Strlen(CHAR_BUFFER);
                CHAR_BUFFER[curStringLen] = CHAR_SPACE;
                curStringLen +=1;
                digit = MApp_GetNoOfDigit(u8TmpVal+1);
                __MApp_UlongToString(u8TmpVal+1, (CHAR_BUFFER+curStringLen), digit);
                curStringLen +=digit;
                CHAR_BUFFER[curStringLen] = 0;
                return (LPTSTR) CHAR_BUFFER;
            }
            break;

        case HWND_ATUNE_CURRENT_CH_OPTION:
            {
                U16 curStringLen = 0;
                U8 digit;

                MApp_ZUI_API_Strcpy(&CHAR_BUFFER[0], MApp_ZUI_API_GetString(en_str_Current_CH));
                curStringLen = MApp_ZUI_API_Strlen(CHAR_BUFFER);
                CHAR_BUFFER[curStringLen] = CHAR_SPACE;
                curStringLen +=1;

                if( IsATVInUse() )
                {
                    if( MApp_Get_IdleDigitCount() == 0 )
                    {
                        digit = MApp_GetNoOfDigit(_MApp_ZUI_ACT_AtvManualTuningGetProgramNumber()+1);
                        __MApp_UlongToString(_MApp_ZUI_ACT_AtvManualTuningGetProgramNumber()+1, (CHAR_BUFFER+curStringLen), digit);
                    }
                    else
                    {
                        digit = MApp_GetNoOfDigit(MApp_Get_IdleInputValue());
                        __MApp_UlongToString(MApp_Get_IdleInputValue(), (CHAR_BUFFER+curStringLen), digit);
                    }
                    curStringLen +=digit;
                    CHAR_BUFFER[curStringLen] = 0;
                    return (LPTSTR) CHAR_BUFFER;
                }
                else
                {
                    __MApp_UlongToString(0, (CHAR_BUFFER+curStringLen), 1);
                    curStringLen += 1;
                    CHAR_BUFFER[curStringLen] = 0;
                    return (LPTSTR) CHAR_BUFFER;
                }
            }
            break;

        case HWND_ATUNE_SYSTEM_OPTION:
        {
         #if ENABLE_SBTVD_SCAN
            if(msAPI_SRC_IS_SBTVD_InUse())
            {
                LPTSTR str = CHAR_BUFFER;
                if(msAPI_ATV_IsProgramAutoColorSystem(msAPI_ATV_GetCurrentProgramNumber()))
                {
                                str[0]= CHAR_A;
                                str[1]= CHAR_U;
                                str[2]= CHAR_T;
                                str[3]= CHAR_O;
                                str[4]= 0;
                }
                else
                {
                    switch(msAPI_ATV_GetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber()))
                    {
                        case E_VIDEOSTANDARD_NTSC_M:
                {
                                str[0]= CHAR_N;
                                str[1]= CHAR_T;
                                str[2]= CHAR_S;
                                str[3]= CHAR_C;
                                str[4]= 0;
                            }
                        break;

                        case E_VIDEOSTANDARD_PAL_M:
                {
                                str[0]= CHAR_P;
                                str[1]= CHAR_A;
                                str[2]= CHAR_L;
                                str[3]= CHAR_SPACE;
                                str[4]= CHAR_M;
                                str[5]= 0;
                }
                break;

                        case E_VIDEOSTANDARD_PAL_N:
                {
                                str[0]= CHAR_P;
                                str[1]= CHAR_A;
                                str[2]= CHAR_L;
                                str[3]= CHAR_SPACE;
                                str[4]= CHAR_N;
                                str[5]= 0;
                }
                break;

                        default:
                         {
                                str[0]= CHAR_A;
                                str[1]= CHAR_U;
                                str[2]= CHAR_T;
                                str[3]= CHAR_O;
                                str[4]= 0;
                      }
                        break;
                    }
                }
                  return CHAR_BUFFER;
            }
            else
        #endif
            {
                U16 u16StrID = Empty;
                U16 curStringLen=0;
                U16 u16StrBuf[32];
                MS_SCANMENU_SETTING *pstScanMenuSetting = NULL;

                MApp_GetGenSetting(EN_GENSETTING_CLASS_SCANMENU,  (void *)&pstScanMenuSetting);
                if(pstScanMenuSetting->u8SoundSystem == EN_ATV_SystemType_BG )
                    u16StrID=en_str_BG;
                else if(pstScanMenuSetting->u8SoundSystem == EN_ATV_SystemType_I )
                    u16StrID=en_str_I;
                else if(pstScanMenuSetting->u8SoundSystem == EN_ATV_SystemType_DK )
                    u16StrID=en_str_DK;
                //----VChip data moving
              #if ( ENABLE_DTMB_CHINA_APP || ENABLE_DVB_TAIWAN_APP || ENABLE_ATV_CHINA_APP || ENABLE_SBTVD_SCAN || ENABLE_DVBC_PLUS_DTMB_CHINA_APP  ||((TV_SYSTEM == TV_NTSC)))
                else if( pstScanMenuSetting->u8SoundSystem == EN_ATV_SystemType_M )
                    u16StrID=en_str_MN;
              #else
                else if(pstScanMenuSetting->u8SoundSystem == EN_ATV_SystemType_L )
                    u16StrID=en_str_L;
              #endif

                MApp_ZUI_API_Strcpy(u16StrBuf, MApp_ZUI_API_GetString(en_str_Sound_Standard));
                curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                u16StrBuf[curStringLen] = CHAR_SPACE;
                curStringLen +=1;
                MApp_ZUI_API_Strcpy(&u16StrBuf[curStringLen], MApp_ZUI_API_GetString(u16StrID));
                MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);
                curStringLen = MApp_ZUI_API_Strlen(CHAR_BUFFER);
                CHAR_BUFFER[curStringLen] = 0;
                return (LPTSTR) CHAR_BUFFER;
            } 
        }
        break;

    #if 0//UI2 NoNeed
        case HWND_ATUNE_SKIP_OPTION:
            if(msAPI_ATV_IsProgramSkipped(msAPI_ATV_GetCurrentProgramNumber()))
                u16TempID = en_str_Yes;
            else
                u16TempID = en_str_No;
            break;
    #endif

     case HWND_ATUNE_VIDEO_STANDARD_OPTION:
        {

            U16 u16StrID = Empty;
            U16 curStringLen=0;
            U16 u16StrBuf[32]={0};
            U16 u16VideoStandard;
            MApp_FuncExec_AtvManualTuningPage(EN_FUNC_ATV_MANUAL_TUNING_GET_USER_VIDEO_STANDARD , (void *)&u16VideoStandard);

            MApp_ZUI_API_Strcpy(u16StrBuf, MApp_ZUI_API_GetString(en_str_Video_Standard));
                   curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
                   u16StrBuf[curStringLen] = CHAR_SPACE;
                   curStringLen +=1;

            //To be fixed after add related UI string
            switch (u16VideoStandard)
            {
            case EN_ATV_VideoStandard_PAL_BGHI:
                        u16StrID = en_str_PAL;
                        MApp_ZUI_API_Strcpy(&u16StrBuf[curStringLen], MApp_ZUI_API_GetString(u16StrID));
                        break;

            case EN_ATV_VideoStandard_PAL_N:
               u16StrBuf[curStringLen]= CHAR_P;
                        u16StrBuf[curStringLen+1]= CHAR_A;
                        u16StrBuf[curStringLen+2]= CHAR_L;
                        u16StrBuf[curStringLen+3]= CHAR_MINUS;
                        u16StrBuf[curStringLen+4]= CHAR_N;
                break;

            case EN_ATV_VideoStandard_PAL_M:
               u16StrBuf[curStringLen]= CHAR_P;
                        u16StrBuf[curStringLen+1]= CHAR_A;
                        u16StrBuf[curStringLen+2]= CHAR_L;
                        u16StrBuf[curStringLen+3]= CHAR_MINUS;
                        u16StrBuf[curStringLen+4]= CHAR_M;
                break;

            case EN_ATV_VideoStandard_SECAM:
                u16StrID = en_str_SECAM;
                        MApp_ZUI_API_Strcpy(&u16StrBuf[curStringLen], MApp_ZUI_API_GetString(u16StrID));
                break;

            case EN_ATV_VideoStandard_PAL_60:
               u16StrBuf[curStringLen]= CHAR_P;
                        u16StrBuf[curStringLen+1]= CHAR_A;
                        u16StrBuf[curStringLen+2]= CHAR_L;
                        u16StrBuf[curStringLen+3]= CHAR_MINUS;
                        u16StrBuf[curStringLen+4]= CHAR_6;
                        u16StrBuf[curStringLen+5]=CHAR_0;
                        break;

                    case EN_ATV_VideoStandard_NTSC_44:
               u16StrBuf[curStringLen]= CHAR_N;
                        u16StrBuf[curStringLen+1]= CHAR_T;
                        u16StrBuf[curStringLen+2]= CHAR_S;
                        u16StrBuf[curStringLen+3]= CHAR_C;
                        u16StrBuf[curStringLen+4]= CHAR_MINUS;
                        u16StrBuf[curStringLen+5]= CHAR_4;
                        u16StrBuf[curStringLen+6]= CHAR_4;
                        break;

                    case EN_ATV_VideoStandard_NTSC_M:
                u16StrID = en_str_NTSC;
                        MApp_ZUI_API_Strcpy(&u16StrBuf[curStringLen], MApp_ZUI_API_GetString(u16StrID));
                break;

            default:
                u16StrID=en_str_Auto;
                        MApp_ZUI_API_Strcpy(&u16StrBuf[curStringLen], MApp_ZUI_API_GetString(u16StrID));
                break;
            }

            curStringLen = MApp_ZUI_API_Strlen(u16StrBuf);
            u16StrBuf[curStringLen] = 0;
            MApp_ZUI_API_Strcpy(CHAR_BUFFER, u16StrBuf);
            return (LPTSTR) CHAR_BUFFER;

         }
        break;

        case HWND_ATUNE_FREQUENCY_VALUE_TXT:
            {
                WORD wTunerPLL,wTunerPLLI,wTunerPLLF;
                LPTSTR str = CHAR_BUFFER;
                U8 u8Index;
                WORD wPLL;
                U8 u8CurrentProgramNumber;
                u8CurrentProgramNumber = msAPI_ATV_GetCurrentProgramNumber();

                wPLL = msAPI_ATV_GetProgramPLLData(u8CurrentProgramNumber);

                MApp_ZUI_API_Strcpy(&str[0], MApp_ZUI_API_GetString(en_str_Frequency));
                u8Index = MApp_ZUI_API_Strlen(str);
                str[u8Index] = CHAR_SPACE;
                u8Index += 1;

                wTunerPLL = msAPI_Tuner_GetCurrentChannelPLL();
                wTunerPLLI = msAPI_CFT_ConvertPLLtoIntegerOfFrequency(wTunerPLL);
                wTunerPLLF = msAPI_CFT_ConvertPLLtoFractionOfFrequency(wTunerPLL);

            #if ATV_FREQUENCE_TENTUNING
                if(MApp_ZUI_API_GetFocus() == HWND_ATUNE_SEARCH && MApp_Get_IdleDigitCount() != 0)
                {
                    __MApp_UlongToString((U32)MApp_Get_IdleInputValue(), (str+(U16)(u8Index)), MApp_Get_IdleDigitCount());
                    u8Index += MApp_Get_IdleDigitCount();

                    str[u8Index++] = '.';
                    str[u8Index++] = '0';
                    str[u8Index++] = '0';
                    str[u8Index++] = CHAR_SPACE;
                    str[u8Index++] = CHAR_M;
                    str[u8Index++] = CHAR_H;
                    str[u8Index++] = CHAR_z;
                }
                else if( MApp_TopStateMachine_GetTopState()!= STATE_TOP_ATV_SCAN  &&
                    wTunerPLL == DEFAULT_PLL ) //DEFAULT_PLL
            #else
                if( MApp_TopStateMachine_GetTopState()!= STATE_TOP_ATV_SCAN  &&
                    wTunerPLL == DEFAULT_PLL ) //DEFAULT_PLL
            #endif
                { /* Unregistered */ // if support multi OSD languages, the string need be add to string file
                    str[u8Index++] = 'U';
                    str[u8Index++] = 'n';
                    str[u8Index++] = 'r';
                    str[u8Index++] = 'e';
                    str[u8Index++] = 'g';
                    str[u8Index++] = 'i';
                    str[u8Index++] = 's';
                    str[u8Index++] = 't';
                    str[u8Index++] = 'e';
                    str[u8Index++] = 'r';
                    str[u8Index++] = 'e';
                    str[u8Index++] = 'd';
                }
                else
                {
                    str[u8Index++] = ((wTunerPLLI/100) == 0) ? ' ' : '0'+(wTunerPLLI/100);
                    str[u8Index++] = '0'+((wTunerPLLI%100)/10);
                    str[u8Index++] = '0'+(wTunerPLLI%10);
                    str[u8Index++] = '.';
                    str[u8Index++] = '0'+(wTunerPLLF/100);
                    str[u8Index++] = '0'+((wTunerPLLF%100)/10);
                    str[u8Index++] = CHAR_SPACE;
                    str[u8Index++] = CHAR_M;
                    str[u8Index++] = CHAR_H;
                    str[u8Index++] = CHAR_z;
                }
                str[u8Index++] = 0;
                return CHAR_BUFFER;
            }
            break;
        default:
            break;
    }

// Market it by coverity_0514
#if 0//UI2 NoNeed
    if (u16TempID != Empty)
        return MApp_ZUI_API_GetString(u16TempID);
#endif

    return 0; //for empty string....
}

void MApp_ZUI_ACT_AppShowAtvManualTuning(void)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_ATV_MANUAL_TUNING;

    g_GUI_WindowList = GetWindowListOfOsdTable(osd_id);
    g_GUI_WinDrawStyleList = GetWindowStyleOfOsdTable(osd_id);
    g_GUI_WindowPositionList = GetWindowPositionOfOsdTable(osd_id);
#if ZUI_ENABLE_ALPHATABLE
    g_GUI_WinAlphaDataList = GetWindowAlphaDataOfOsdTable(osd_id);
#endif
    HWND_MAX = GetWndMaxOfOsdTable(osd_id);
    OSDPAGE_BLENDING_ENABLE = IsBlendingEnabledOfOsdTable(osd_id);
    OSDPAGE_BLENDING_VALUE = GetBlendingValueOfOsdTable(osd_id);

    // clean digital key count and buffer
    MApp_Set_IdleDigitCount(0);
    MApp_Set_IdleInputValue(0);

    if (!_MApp_ZUI_API_AllocateVarData())
    {
        ZUI_DBG_FAIL(printf("[ZUI]ALLOC\n"));
        ABORT();
        return;
    }

    RECT_SET(rect,
        ZUI_ATV_MANUAL_TUNING_XSTART, ZUI_ATV_MANUAL_TUNING_YSTART,
        ZUI_ATV_MANUAL_TUNING_WIDTH, ZUI_ATV_MANUAL_TUNING_HEIGHT);

    if (!MApp_ZUI_API_InitGDI(&rect))
    {
        ZUI_DBG_FAIL(printf("[ZUI]GDIINIT\n"));
        ABORT();
        return;
    }
#if (ENABLE_DTV)
    if(TRUE == MApp_Get_ParentalBlock_state())
    {
        MApp_ParentalControl_SetBlockStatus(FALSE);
        MApp_Set_ParentalBlock_state(DISABLE);
    }
#endif
#if ENABLE_SBTVD_SCAN
    if(msAPI_SRC_IS_SBTVD_InUse())
    {
        if ( UI_INPUT_SOURCE_TYPE != UI_INPUT_SOURCE_ATV)
        {
            if(IsAnyTVSourceInUse())
            {
                MApp_ChannelChange_DisableChannel(TRUE, MAIN_WINDOW);
            }
            else
            {
                MApp_ChannelChange_DisableAV(MAIN_WINDOW);
            }
#if 0
            //if(UI_INPUT_SOURCE_TYPE <= UI_INPUT_SOURCE_DTMB && msAPI_VID_GetPlayMode()== MSAPI_VID_PLAY)
            if (  (MApp_InputSrc_Is_CurUiInputSrcTypeDtv())
               && (msAPI_VID_GetPlayMode()== MSAPI_VID_PLAY) )
            {
                 msAPI_VID_Command(MSAPI_VID_STOP);
            }
#endif
           // msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            if(msAPI_ATV_GetCurrentAntenna()==ANT_CATV)
            {
                msAPI_ATV_SetCurrentAntenna(ANT_AIR);
            }
            //UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ATV;
            MApp_InputSrc_Set_UiInputSrcType(UI_INPUT_SOURCE_ATV);
            MApp_InputSource_SwitchSource(UI_INPUT_SOURCE_ATV, MAIN_WINDOW);
            //msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);

           MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
        }
    }
    else
#endif
    {
        if ( UI_INPUT_SOURCE_TYPE != UI_INPUT_SOURCE_ATV )
        {
        #if( ENABLE_DTV )
            //if(UI_INPUT_SOURCE_TYPE <= UI_INPUT_SOURCE_DTMB && msAPI_VID_GetPlayMode()== MSAPI_VID_PLAY)
            if (  (MApp_InputSrc_Is_CurUiInputSrcTypeDtv())
               && (msAPI_VID_GetPlayMode()== MSAPI_VID_PLAY) )
            {
                 msAPI_VID_Command(MSAPI_VID_STOP);
            }
        #endif

            MApp_ZUI_ACT_InputSourceSwitch( UI_INPUT_SOURCE_ATV );
        }
    }

    _MApp_ZUI_ACT_SetStoreChannelValue(_MApp_ZUI_ACT_AtvManualTuningGetProgramNumber());

    for (wnd = 0; wnd < HWND_MAX; wnd++)
    {
        MApp_ZUI_API_SendMessage(wnd, MSG_CREATE, 0);
    }

    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);
    MApp_ZUI_API_ShowWindow(HWND_ATUNE_PAGE_LIST,SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_ATUNE_SEARCH_LARROW2, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_ATUNE_SEARCH_RARROW2, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_ATUNE_FINE_TUNE_LARROW2, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_ATUNE_FINE_TUNE_RARROW2, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_ATUNE_PAGE_LIST,SW_SHOW);
    MApp_ZUI_API_SetFocus(HWND_ATUNE_STORAGE_TO);

    //MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_PAGE_SHOWUP, E_ZUI_STATE_RUNNING);
}
GUI_ENUM_DYNAMIC_LIST_STATE MApp_ZUI_ACT_QueryAtvManualTuningStatus(HWND hwnd)
{
    switch(hwnd)
    {
        case HWND_ATUNE_STORAGE_TO:
        case HWND_ATUNE_SYSTEM:
        case HWND_ATUNE_CURRENT_CH:
        case HWND_ATUNE_FINE_TUNE:
            return EN_DL_STATE_NORMAL;
            break;
        case HWND_ATUNE_SEARCH:
#if(ENABLE_SBTVD_SCAN)
            if(msAPI_SRC_IS_SBTVD_InUse())
            {
                return EN_DL_STATE_HIDDEN;
            }
            else            
#endif
            {
                return EN_DL_STATE_NORMAL;
            }

        break;
        default:
            return EN_DL_STATE_NORMAL;
    }
}


#undef MAPP_ZUI_ACTATVMANUALTUNING_C
