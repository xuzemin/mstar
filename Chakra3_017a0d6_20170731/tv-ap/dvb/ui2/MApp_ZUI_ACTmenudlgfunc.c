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
// (��MStar Confidential Information��) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define MAPP_ZUI_ACTMENUDLGFUNC_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "GPIO.h"                   //For audio
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "apiXC_Sys.h"
#include "msAPI_audio.h"

#include "MApp_GlobalSettingSt.h"

#include "MApp_Audio.h"

#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_APIcomponent.h"

#include "MApp_ZUI_APIalphatables.h"
#include "MApp_ZUI_ACTmainpage.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_ACTglobal.h"
#include "msAPI_Flash.h"

#include "OSDcp_String_EnumIndex.h"
#include "ZUI_exefunc.h"

#include "MApp_ZUI_ACTmenudlgfunc.h"
#include "MApp_UiMenuDef.h"
#include "MApp_RestoreToDefault.h"
#include "MApp_Scaler.h"
#include "MApp_XC_PQ.h"
#include "MApp_SaveData.h"
#include "MApp_ATVProc.h"
#include "msAPI_Global.h"
#include "MApp_ChannelChange.h"
#include "SysInit.h"
#include <stdio.h>
#include <string.h>
#include "msAPI_Memory.h"
#include "msAPI_MIU.h"
#include "MApp_DataBase.h"
#include "MApp_USBDownload.h"
#include "msAPI_Bootloader.h"
#include "msAPI_OCP.h"
#include "drvGPIO.h"
#include "msAPI_Timer.h"
#if ENABLE_DMP
#include "MApp_DMP_Main.h"
#endif
#include "MApp_InputSource.h"
#include "MApp_TopStateMachine.h"
#include "MApp_CADTV_Proc.h"
#include "MApp_Menu_Main.h"
#include "MApp_ZUI_ACTcoexistWin.h"
#if (ENABLE_CI_PLUS)
#include "MApp_CIMMI.h"
#endif

#include "MApp_MenuFunc.h"

#if ENABLE_ATSC_TTS
#include "MApp_TTS_Cus.h"
#endif

#if ENABLE_DVBC
#include "MApp_Scan.h"
#endif

///////////////////////////////////////////////////
extern EN_MENU_STATE enMainMenuState;
extern COMMON_DLG_MODE _eCommonDlgMode;
extern U16 _MApp_ZUI_API_FindFirstComponentIndex(HWND hWnd, DRAWSTYLE_TYPE type, DRAWCOMPONENT comp);
extern void _MApp_ZUI_API_ConvertTextComponentToDynamic(U16 u16TextOutIndex, DRAW_TEXT_OUT_DYNAMIC * pComp);
extern void _MApp_ZUI_ACT_OpenCommonDialog(COMMON_DLG_MODE dlg);
void _MApp_ZUI_API_ForceUpdateWindows(HWND aUpdateWindows[],U8 WinCount);
void MApp_ZUI_SwUpdate_ProgressBar(U8 percent);
extern void  MApp_ZUI_ACT_SetTargetMenuState(EN_MENU_STATE MenuState);
extern BOOLEAN _MApp_ZUI_API_WindowProcOnIdle(void);

static U8 USB_Upgrade_Percent = 0xFF;
//////////////////////////////////////////
//for factory reset
static BOOLEAN MApp_ZUI_ACT_FactoryReset_VideoReset(void)
{
    MApp_DataBase_RestoreDefaultVideo(DATA_INPUT_SOURCE_TYPE(MAIN_WINDOW));
    //MApp_DataBase_RestoreDefaultWhiteBalance(DATA_INPUT_SOURCE_TYPE(MAIN_WINDOW));
    MApp_DataBase_PictureResetWhiteBalance(DATA_INPUT_SOURCE_TYPE(MAIN_WINDOW));

    MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);  //MApp_PicSetVideo(SYS_INPUT_SOURCE_TYPE, &ST_VIDEO );
    MApp_Scaler_Setting_SetVDScale(ST_VIDEO.eAspectRatio, MAIN_WINDOW);
#if (IR_TYPE_SEL == IR_TYPE_SZ_ALC1)//ALC 20071109
    SET_OSD_MENU_LANGUAGE(LANGUAGE_DEFAULT); // menu language
#endif

    return TRUE;
}

static BOOLEAN MApp_ZUI_ACT_FactoryReset_SoundReset(void)
{
    MApp_DataBase_RestoreDefaultAudio(TRUE);
    return TRUE;
}

static void MApp_ZUI_ACT_FactoryReset(void)
{
    MS_DEBUG_MSG(printf(">>>>>>>MApp_ZUI_ACT_FactoryReset\n"));

    // set Audio Mute
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
    msAPI_Timer_Delayms(10);//DELAY_FOR_ENTERING_MUTE);

    MApp_Audio_Set_AmpMute(AUDIO_AMP_MUTE_ON);

    MApp_Audio_Set_AmpOnOff(AUDIO_AMP_OFF);

    // set Video Mute
    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_UI, ENABLE, 0, MAIN_WINDOW);
    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_UI, ENABLE, 0, SUB_WINDOW);
    MS_DEBUG_MSG(printf(">>>>>>>msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_BY_UI, ENABLE, 0, MAIN_WINDOW);  \n"));

    MApp_DataBase_RestoreFactoryDefault(RESTORE_GENSETTING);
    MS_DEBUG_MSG(printf(">>>>>>> MApp_DataBase_RestoreFactoryDefault(RESTORE_GENSETTING);\n"));

    MApp_DataBase_RestoreFactoryDefault(RESTORE_DATABASE);
    MS_DEBUG_MSG(printf(">>>>>>> MApp_DataBase_RestoreFactoryDefault(RESTORE_DATABASE);\n"));

    MApp_ZUI_ACT_ShutdownOSD();
    MS_DEBUG_MSG(printf(">>>>>>>MApp_ZUI_ACT_ShutdownOSD\n"));
#if (ENABLE_CI_PLUS)
    MApp_CI_ResetOPCacheDB(FALSE);
#endif

    //store to flash immediately
    //MApp_DB_SaveNowGenSetting();
    MApp_DB_GEN_SaveData_RightNow();

    MDrv_Sys_WholeChipReset();
}

static void MApp_ZUI_ACT_UserSettingReset(void)
{
         MS_DEBUG_MSG(printf(">>>>>>>MApp_ZUI_ACT_UserSettingReset\n"));
         //menu default
         MApp_ZUI_ACT_FactoryReset_VideoReset();
         msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);//Mute before reset audio
         MApp_ZUI_ACT_FactoryReset_SoundReset();
         msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);//Mute before reset audio
        MApp_DataBase_RestoreUserSettingDefault(RESTORE_USERSETTING);
        #if 0//ENABLE_T_C_COMBO
       MApp_CATV_RestoreManutuning_settingDefault();
        #endif
       //*************************************************************************
       // Restore default source
       //*************************************************************************

      UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ATV;
      MApp_InputSource_ChangeInputSource(MAIN_WINDOW);
      MApp_ChannelChange_VariableInit();
#if (ENABLE_DTV)
      stGenSetting.stMiscSetting.bRunInstallationGuide =TRUE;
      if( stGenSetting.stMiscSetting.bRunInstallationGuide )
    {
        MApp_TopStateMachine_SetTopState(STATE_TOP_INSTALLGUIDE);
    }
#else
       stGenSetting.stMiscSetting.bRunInstallationGuide =FALSE;
       MApp_TopStateMachine_SetTopState(STATE_TOP_CHANNELCHANGE);
#endif
      enMainMenuState=STATE_MENU_INIT;
      MApp_ZUI_ACT_SetTargetMenuState(STATE_MENU_INIT);

#if ENABLE_CI_PLUS
  //for clear CI key setting informations
       MApp_DataBase_RestoreDefault_CIPlus();
       MApp_SaveCIPlusSetting();
#endif

#if (ENABLE_EWS)
    stGenSetting.stMiscSetting.u8EWSLocationCode[0] =0 ;
    stGenSetting.stMiscSetting.u8EWSLocationCode[1] =0 ;
    stGenSetting.stMiscSetting.u8EWSLocationCode[2] =0 ;
    stGenSetting.stMiscSetting.u8EWSLocationCode[3] =0 ;
    stGenSetting.stMiscSetting.u8EWSLocationCode[4] =0 ;
    MApp_SI_SetLocationCode(stGenSetting.stMiscSetting.u8EWSLocationCode);
#endif


}

BOOLEAN MApp_ZUI_ACT_ExecuteMenuCommonDialogAction(U16 act)
{
    //mapping generic command to specific action...
    if (act == EN_EXE_CLOSE_CURRENT_OSD)
    {
        switch(_eCommonDlgMode)
        {
            case EN_COMMON_DLG_MODE_FACTORY_RESET:
            case EN_COMMON_DLG_MODE_FACTORY_RESET_CONFIRM:
                act = EN_EXE_CLOSE_FACTORY_RESET_CONFIRM_DLG;
                break;
            case EN_COMMON_DLG_MODE_USB_UPDATE_CONFIRM:
                act = EN_EXE_CLOSE_USB_UPGRADE_CONFIRM_DLG;
                break;
            case EN_COMMON_DLG_MODE_DIVX:
                act = EN_EXE_CLOSE_DIVX_CONFIRM_DLG;
                break;
            case EN_COMMON_DLG_MODE_DEACTIVATION:
            case EN_COMMON_DLG_MODE_DEACTIVATION_CONFIRM:
                act = EN_EXE_CLOSE_DEACTIVATION_CONFIRM_DLG;
                break;

            case EN_COMMON_DLG_MODE_MISMATCH_PASSWORD:
                act = EN_EXE_CLOSE_MISMATCH_PASSWORD_DLG;
                break;

            case EN_COMMON_DLG_MODE_WRONG_PASSWORD:
                act = EN_EXE_CLOSE_WRONG_PASSWORD_DLG;
                break;

#if ( ENABLE_FORCE_PRESET_PASSWORD )
            case EN_COMMON_DLG_MODE_FORCE_PRESET_PASSWORD:
#endif  //ENABLE_FORCE_PRESET_PASSWORD
            case EN_COMMON_DLG_MODE_SET_PASSWORD:
                act = EN_EXE_CLOSE_SET_PASSWORD_DLG;
                break;

            case EN_COMMON_DLG_MODE_INPUT_PASSWORD:
            case EN_COMMON_DLG_MODE_SCAN_INPUT_PASSWORD:
            case EN_COMMON_DLG_MODE_DTV_TUNING_INPUT_PASSWORD:
            case EN_COMMON_DLG_MODE_ATV_TUNING_INPUT_PASSWORD:
            case EN_COMMON_DLG_MODE_FACTORY_RESET_INPUT_PASSWORD:
            case EN_COMMON_DLG_MODE_ENTER_MENU_LOCK_PAGE_INPUT_PASSWORD:
                act = EN_EXE_CLOSE_INPUT_PASSWORD_DLG;
                break;
            default:
                break;
        }
    }

    switch(act)
    {
        case EN_EXE_CLOSE_FACTORY_RESET_CONFIRM_DLG:
            //if (_eCommonDlgMode != EN_COMMON_DLG_MODE_FACTORY_RESET_CONFIRM)
            //    return TRUE;

            _eCommonDlgMode = EN_COMMON_DLG_MODE_INVALID;
            MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_COMMON, SW_HIDE);
            MApp_ZUI_ACT_ShowMainMenuBackground(HWND_MENU_BOTTOM_BALL_FOCUS_OPTION);
            MApp_ZUI_API_ShowWindow(HWND_MENU_OPTION_PAGE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_MENU_OPTION_FACTORY_RESET);
            //MApp_ZUI_API_SetFocus(_hwndCommonDlgPrevFocus);
            //MApp_ZUI_API_RestoreFocusCheckpoint();
            return TRUE;

        case EN_EXE_CLOSE_DIVX_CONFIRM_DLG:
        case EN_EXE_CLOSE_DEACTIVATION_CONFIRM_DLG:
            _eCommonDlgMode = EN_COMMON_DLG_MODE_INVALID;
            MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_COMMON, SW_HIDE);
            MApp_ZUI_ACT_ShowMainMenuBackground(HWND_MENU_BOTTOM_BALL_FOCUS_OPTION);
            MApp_ZUI_API_ShowWindow(HWND_MENU_OPTION_PAGE, SW_SHOW);
            //MApp_ZUI_API_SetFocus(HWND_MENU_OPTION_DIVX);
            MApp_ZUI_CTL_DynamicListSetItemFocus(HWND_MENU_OPTION_PAGE_LIST, HWND_MENU_OPTION_DIVX);
            return TRUE;

        case EN_EXE_CLOSE_USB_UPGRADE_CONFIRM_DLG:
            _eCommonDlgMode = EN_COMMON_DLG_MODE_INVALID;
            MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_COMMON, SW_HIDE);
            MApp_ZUI_ACT_ShowMainMenuBackground(HWND_MENU_BOTTOM_BALL_FOCUS_OPTION);
            MApp_ZUI_API_ShowWindow(HWND_MENU_OPTION_PAGE, SW_SHOW);
            //MApp_ZUI_CTL_DynamicListSetItemFocus(HWND_MENU_OPTION_PAGE_LIST, HWND_MENU_OPTION_DIVX);
			MApp_ZUI_API_SetFocus(HWND_MENU_OPTION_UPGRADE);
            MApp_UsbDownload_Exit();
            return TRUE;

        case EN_EXE_FACTORY_RESET:
            if (_eCommonDlgMode != EN_COMMON_DLG_MODE_FACTORY_RESET)
                return TRUE;
            {//Factory default
                MApp_ZUI_ACT_FactoryReset_VideoReset();
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);//Mute before reset audio
                MApp_ZUI_ACT_FactoryReset_SoundReset();
            }
            MApp_ZUI_ACT_FactoryReset();
            _eCommonDlgMode = EN_COMMON_DLG_MODE_INVALID;
            MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_COMMON, SW_HIDE);

            MApp_ZUI_API_RestoreFocusCheckpoint();
            return TRUE;

        case EN_EXE_USER_SETTING_RESET:
            if (_eCommonDlgMode != EN_COMMON_DLG_MODE_FACTORY_RESET)
                return TRUE;
            if(msAPI_AUD_IsAudioMutedByUser())
            {
              MApp_UiMenu_MuteWin_Hide();
            }
            MApp_ZUI_ACT_UserSettingReset();

            _eCommonDlgMode = EN_COMMON_DLG_MODE_INVALID;
            MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_COMMON, SW_HIDE);
            return TRUE;

        case EN_EXE_CLOSE_MISMATCH_PASSWORD_DLG:
            if (_eCommonDlgMode != EN_COMMON_DLG_MODE_MISMATCH_PASSWORD)
                return TRUE;

            _eCommonDlgMode = EN_COMMON_DLG_MODE_INVALID;
            MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_COMMON, SW_HIDE);
            MApp_ZUI_ACT_ShowMainMenuBackground(HWND_MENU_BOTTOM_BALL_FOCUS_LOCK);
            MApp_ZUI_API_ShowWindow(HWND_MENU_LOCK_PAGE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_MENU_LOCK_SET_PASSWORD);
            MApp_ZUI_API_RestoreFocusCheckpoint();
            return TRUE;

        case EN_EXE_CLOSE_WRONG_PASSWORD_DLG:
        {
            HWND hwnd = (HWND)0;//NULL; // Move it by coverity_0530
            if (_eCommonDlgMode != EN_COMMON_DLG_MODE_WRONG_PASSWORD)
                return TRUE;
			
            _eCommonDlgMode = EN_COMMON_DLG_MODE_INVALID;
            MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_COMMON, SW_HIDE);
            hwnd = MApp_ZUI_API_GetFocusCheckpoint();
            if(MApp_ZUI_API_IsSuccessor(HWND_MENU_CHANNEL_PAGE, hwnd))
            {
               MApp_ZUI_ACT_ShowMainMenuBackground(HWND_MENU_BOTTOM_BALL_FOCUS_CHANNEL);
               MApp_ZUI_API_ShowWindow(HWND_MENU_CHANNEL_PAGE, SW_SHOW);
            }
            else if (MApp_ZUI_API_IsSuccessor(HWND_MENU_LOCK_PAGE, hwnd))
            {
               MApp_ZUI_ACT_ShowMainMenuBackground(HWND_MENU_BOTTOM_BALL_FOCUS_LOCK);
               MApp_ZUI_API_ShowWindow(HWND_MENU_LOCK_PAGE, SW_SHOW);
               MApp_MenuFunc_Setup_BlockSysEnterLockPage_Set(0);
               MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_SET_PASSWORD, DISABLE);
               MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_BLOCK_PROGRAM, DISABLE);
               MApp_ZUI_API_EnableWindow(HWND_MENU_LOCK_PARENTAL_GUIDANCE, DISABLE);
               MApp_ZUI_API_InvalidateWindow(HWND_MENU_LOCK_PAGE_LIST);
            }
            else
            {
               MApp_ZUI_ACT_ShowMainMenuBackground(HWND_MENU_BOTTOM_BALL_FOCUS_OPTION);
               MApp_ZUI_API_ShowWindow(HWND_MENU_OPTION_PAGE, SW_SHOW);
            }
            MApp_ZUI_API_RestoreFocusCheckpoint();
        }
            return TRUE;

        case EN_EXE_CLOSE_SET_PASSWORD_DLG:
#if ( ENABLE_FORCE_PRESET_PASSWORD )
            if (_eCommonDlgMode == EN_COMMON_DLG_MODE_FORCE_PRESET_PASSWORD)
            {
                _eCommonDlgMode = EN_COMMON_DLG_MODE_INVALID;
                MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_COMMON, SW_HIDE);
                MApp_ZUI_ACT_ExecuteMainMenuAction(EN_EXE_GOTO_TUNING_CONFIRM);
            }
            else
#endif  //ENABLE_FORCE_PRESET_PASSWORD
            if(_eCommonDlgMode == EN_COMMON_DLG_MODE_SET_PASSWORD)
            {
                _eCommonDlgMode = EN_COMMON_DLG_MODE_INVALID;
                MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_COMMON, SW_HIDE);
                MApp_ZUI_ACT_ShowMainMenuBackground(HWND_MENU_BOTTOM_BALL_FOCUS_LOCK);
                MApp_ZUI_API_ShowWindow(HWND_MENU_LOCK_PAGE, SW_SHOW);
                MApp_ZUI_API_EnableWindow(HWND_MENU_DLG_PASSWORD_INPUT1_TEXT, ENABLE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_DLG_PASSWORD_INPUT1_1, ENABLE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_DLG_PASSWORD_INPUT1_2, ENABLE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_DLG_PASSWORD_INPUT1_3, ENABLE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_DLG_PASSWORD_INPUT1_4, ENABLE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_DLG_PASSWORD_INPUT2_TEXT, ENABLE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_DLG_PASSWORD_INPUT2_1, ENABLE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_DLG_PASSWORD_INPUT2_2, ENABLE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_DLG_PASSWORD_INPUT2_3, ENABLE);
                MApp_ZUI_API_EnableWindow(HWND_MENU_DLG_PASSWORD_INPUT2_4, ENABLE);
                MApp_ZUI_API_SetFocus(HWND_MENU_LOCK_SET_PASSWORD);
                MApp_ZUI_API_RestoreFocusCheckpoint();
            }
            return TRUE;

        case EN_EXE_CLOSE_INPUT_PASSWORD_DLG:
            if (_eCommonDlgMode != EN_COMMON_DLG_MODE_INPUT_PASSWORD &&
                 _eCommonDlgMode != EN_COMMON_DLG_MODE_SCAN_INPUT_PASSWORD &&
                 _eCommonDlgMode != EN_COMMON_DLG_MODE_DTV_TUNING_INPUT_PASSWORD &&
                 _eCommonDlgMode != EN_COMMON_DLG_MODE_ATV_TUNING_INPUT_PASSWORD &&
                 _eCommonDlgMode != EN_COMMON_DLG_MODE_FACTORY_RESET_INPUT_PASSWORD &&
                 _eCommonDlgMode != EN_COMMON_DLG_MODE_ENTER_MENU_LOCK_PAGE_INPUT_PASSWORD)
                return TRUE;
            else
            {
               switch(_eCommonDlgMode)
               {
                   case EN_COMMON_DLG_MODE_FACTORY_RESET_INPUT_PASSWORD:
                       MApp_ZUI_ACT_ShowMainMenuBackground(HWND_MENU_BOTTOM_BALL_FOCUS_OPTION);
                       MApp_ZUI_API_ShowWindow(HWND_MENU_OPTION_PAGE, SW_SHOW);
                       MApp_ZUI_API_SetFocus(HWND_MENU_OPTION_OSD_LANG);
                       break;
                   case EN_COMMON_DLG_MODE_SCAN_INPUT_PASSWORD:
						MApp_ZUI_ACT_ShowMainMenuBackground(HWND_MENU_BOTTOM_BALL_FOCUS_OPTION);
						MApp_ZUI_API_ShowWindow(HWND_MENU_OPTION_PAGE, SW_SHOW);
						MApp_ZUI_CTL_DynamicListSetItemFocus(HWND_MENU_OPTION_PAGE_LIST, HWND_MENU_OPTION_DIVX);
                       break;
                   case EN_COMMON_DLG_MODE_DTV_TUNING_INPUT_PASSWORD:
						MApp_ZUI_ACT_ShowMainMenuBackground(HWND_MENU_BOTTOM_BALL_FOCUS_OPTION);
						MApp_ZUI_API_ShowWindow(HWND_MENU_OPTION_PAGE, SW_SHOW);
						MApp_ZUI_CTL_DynamicListSetItemFocus(HWND_MENU_OPTION_PAGE_LIST, HWND_MENU_OPTION_DIVX);
                       break;
                   case EN_COMMON_DLG_MODE_ATV_TUNING_INPUT_PASSWORD:
						MApp_ZUI_ACT_ShowMainMenuBackground(HWND_MENU_BOTTOM_BALL_FOCUS_OPTION);
						MApp_ZUI_API_ShowWindow(HWND_MENU_OPTION_PAGE, SW_SHOW);
						MApp_ZUI_CTL_DynamicListSetItemFocus(HWND_MENU_OPTION_PAGE_LIST, HWND_MENU_OPTION_DIVX);
                       break;
                   case EN_COMMON_DLG_MODE_ENTER_MENU_LOCK_PAGE_INPUT_PASSWORD:
                       MApp_ZUI_ACT_ShowMainMenuBackground(HWND_MENU_BOTTOM_BALL_FOCUS_LOCK);
                       MApp_ZUI_API_ShowWindow(HWND_MENU_LOCK_PAGE, SW_SHOW);
                       //MApp_ZUI_API_SetFocus(HWND_MENU_LOCK_TITLE);
                      //stGenSetting.g_BlockSysSetting.u8EnterLockPage = 0;
                      MApp_MenuFunc_Setup_BlockSysEnterLockPage_Set(0);


                    break;
                   default:
                    break;
               }
            }

            _eCommonDlgMode = EN_COMMON_DLG_MODE_INVALID;
            MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_COMMON, SW_HIDE);
            MApp_ZUI_API_RestoreFocusCheckpoint();
            return TRUE;

        case EN_EXE_CLEAR_PASSWORD:
    #if ENABLE_ATSC_TTS
            MApp_TTS_Cus_Add_Str_By_StrId(en_str_Clear);
            MApp_TTSControlSetOn(TRUE);
    #endif
            if(MApp_ZUI_API_IsSuccessor(HWND_MENU_DLG_PASSWORD_PANE0, MApp_ZUI_API_GetFocus()))
            {
                PasswordInput0 = 0;
                MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PRESSED_PANE0, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PANE0, SW_SHOW);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_DLG_PASSWORD_PANE0);
                MApp_ZUI_API_SetFocus(HWND_MENU_DLG_PASSWORD_INPUT0_1);
            }
            else if(MApp_ZUI_API_IsSuccessor(HWND_MENU_DLG_PASSWORD_PANE1, MApp_ZUI_API_GetFocus()))
            {
                PasswordInput0 = 0;
                MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PRESSED_PANE1, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PANE1, SW_SHOW);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_DLG_PASSWORD_PANE1);
                MApp_ZUI_API_SetFocus(HWND_MENU_DLG_PASSWORD_INPUT1_1);

                if (_eCommonDlgMode == EN_COMMON_DLG_MODE_INPUT_PASSWORD ||
                     _eCommonDlgMode == EN_COMMON_DLG_MODE_SCAN_INPUT_PASSWORD ||
                     _eCommonDlgMode == EN_COMMON_DLG_MODE_DTV_TUNING_INPUT_PASSWORD ||
                     _eCommonDlgMode == EN_COMMON_DLG_MODE_ATV_TUNING_INPUT_PASSWORD ||
                     _eCommonDlgMode == EN_COMMON_DLG_MODE_FACTORY_RESET_INPUT_PASSWORD ||
                     _eCommonDlgMode == EN_COMMON_DLG_MODE_WRONG_PASSWORD ||
                   _eCommonDlgMode ==  EN_COMMON_DLG_MODE_ENTER_MENU_LOCK_PAGE_INPUT_PASSWORD)
                {
                    MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_INPUT1_TEXT, SW_HIDE);
                }
                else
                {
                    MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_INPUT1_TEXT, SW_SHOW);
                }
            }
            else
            {
                PasswordInput1 = PasswordInput2 = 0;

                MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PRESSED_PANE1, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PRESSED_PANE2, SW_HIDE);

                MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PANE1, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PANE2, SW_SHOW);

                MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_DLG_PASSWORD_PANE0);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_DLG_PASSWORD_PANE1);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_DLG_PASSWORD_PANE2);
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_MENU_DLG_COMMON_BTN_OK);
                MApp_ZUI_API_SetFocus(HWND_MENU_DLG_PASSWORD_INPUT1_1);
            }
            return FALSE; //don't eat this key event..

        default:
            ZUI_DBG_FAIL(printf("[ZUI]COMDLGACT\n"));
            ABORT();


    }
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////

LPTSTR MApp_ZUI_ACT_GetMenuCommonDynamicText(HWND hwnd)
{
    U16 u16TempID = Empty;

#if ENABLE_ATSC_TTS
    BOOLEAN bNeedCallTts = TRUE;
#endif

    switch(hwnd)
    {
        case HWND_MENU_DLG_COMMON_TEXT1:
            switch(_eCommonDlgMode)
            {
            #if (ENABLE_ATSC)
                case EN_COMMON_DLG_MODE_RESETRRT_CONFIRM:
            #endif
                case EN_COMMON_DLG_MODE_FACTORY_RESET_CONFIRM:
                case EN_COMMON_DLG_MODE_USB_UPDATE_CONFIRM:
                    u16TempID = en_str_Are_you_sure;
                    break;

                case EN_COMMON_DLG_MODE_DIVX:
                case EN_COMMON_DLG_MODE_DEACTIVATION:
                case EN_COMMON_DLG_MODE_DEACTIVATION_CONFIRM:
                    u16TempID = Empty;
                    break;

                case EN_COMMON_DLG_MODE_FACTORY_RESET:
                    //u16TempID = en_str_Reseting3dot;
                    break;

                case EN_COMMON_DLG_MODE_WRONG_PASSWORD:
                    //u16TempID = en_str_Wrong_password;
                    break;

                case EN_COMMON_DLG_MODE_MISMATCH_PASSWORD:
                    //u16TempID = en_str_Password_doesnot_match;
                    break;

#if ( ENABLE_FORCE_PRESET_PASSWORD )
                case EN_COMMON_DLG_MODE_FORCE_PRESET_PASSWORD:
#endif  //ENABLE_FORCE_PRESET_PASSWORD
                case EN_COMMON_DLG_MODE_SET_PASSWORD:
                case EN_COMMON_DLG_MODE_INPUT_PASSWORD:
                case EN_COMMON_DLG_MODE_SCAN_INPUT_PASSWORD:
                case EN_COMMON_DLG_MODE_DTV_TUNING_INPUT_PASSWORD:
                case EN_COMMON_DLG_MODE_ATV_TUNING_INPUT_PASSWORD:
                case EN_COMMON_DLG_MODE_FACTORY_RESET_INPUT_PASSWORD:
                case EN_COMMON_DLG_MODE_ENTER_MENU_LOCK_PAGE_INPUT_PASSWORD:
                    //u16TempID = en_str_Please_enter_password;
                    break;

                case EN_COMMON_DLG_MODE_USB_NOT_DETECTED:
                    u16TempID = en_str_Cannot_Detect_USB;
                    break;

                case EN_COMMON_DLG_MODE_CI_NO_MODULE:
                    u16TempID = en_str_Please_insert_CI_Module;
                    break;

                case EN_COMMON_DLG_MODE_SW_FILE_NOT_DETECTED:
                    u16TempID = en_str_Cannot_Detect_software_file;
                    break;

            #if ((MEMORY_MAP <= MMAP_32MB)&&(CHIP_FAMILY_TYPE ==CHIP_FAMILY_WHISKY))
                case EN_COMMON_DLG_MODE_USB_UPGRADING:
                    u16TempID = en_str_Software_UpdatebracketsUSB;
                    break;
            #endif

                default:
                    ZUI_DBG_FAIL(printf("[ZUI]COMDLGMODE\n"));
                    ABORT();

            }
            break;

        case HWND_MENU_DLG_COMMON_TEXT2:
            if ( (_eCommonDlgMode == EN_COMMON_DLG_MODE_USB_UPGRADING)
               &&(USB_Upgrade_Percent != 0xFF) )
            {
                if (USB_Upgrade_Percent <= 100)
                {
                    MApp_ZUI_API_GetU16String((U16)USB_Upgrade_Percent);
                    if(USB_Upgrade_Percent < 10 )
                    {
                        CHAR_BUFFER[1] = CHAR_SPACE;
                        CHAR_BUFFER[2] = CHAR_SPACE;
                    }
                    else if(USB_Upgrade_Percent < 100)
                    {
                        CHAR_BUFFER[2] = CHAR_SPACE;
                    }
                    CHAR_BUFFER[3] = CHAR_PERCENT;
                    CHAR_BUFFER[4] = '\0';

                #if ENABLE_ATSC_TTS
                    bNeedCallTts = FALSE;
                #endif
                }
                else if(USB_Upgrade_Percent == 0xFE)
                {
                    U8 str[] = {"CRC Error"};
                    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,str, strlen((const char *)str));
                }
                else if(USB_Upgrade_Percent == 0xFD)
                {
                    U8 str[] = {"Fail to Burn AP Code"};
                    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, str, strlen((const char *)str));
                }
                else if(USB_Upgrade_Percent == 0xFC)
                {
                    U8 str[] = {"Unknown image type"};
                    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, str, strlen((const char *)str));
                }
                else if(USB_Upgrade_Percent == 0xFB)
                {
                    U8 str[] = {"Reboot fail"};
                    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, str, strlen((const char *)str));
                }
                else if(USB_Upgrade_Percent == 0xFA)
                {
                    U8 str[] = {"Failed to update software"};
                    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, str, strlen((const char *)str));
                }
                else
                {
                    return 0;
                }
                return CHAR_BUFFER;
            }
            else
            {
               return 0;
            }

        case HWND_MENU_DLG_COMMON_TEXT3:
            switch(_eCommonDlgMode)
            {
                case EN_COMMON_DLG_MODE_INPUT_PASSWORD:
                case EN_COMMON_DLG_MODE_SCAN_INPUT_PASSWORD:
                case EN_COMMON_DLG_MODE_DTV_TUNING_INPUT_PASSWORD:
                case EN_COMMON_DLG_MODE_ATV_TUNING_INPUT_PASSWORD:
                case EN_COMMON_DLG_MODE_FACTORY_RESET_INPUT_PASSWORD:
                case EN_COMMON_DLG_MODE_ENTER_MENU_LOCK_PAGE_INPUT_PASSWORD:
                    u16TempID = en_str_Please_enter_password;
                    break;

                case EN_COMMON_DLG_MODE_WRONG_PASSWORD:
                    u16TempID = en_str_Wrong_password;
                    break;
                default:
                    return 0;
            }
            break;

#if ((MEMORY_MAP > MMAP_32MB)||(CHIP_FAMILY_TYPE !=CHIP_FAMILY_WHISKY))
        case HWND_MENU_DLG_COMMON_TEXT4:
            switch(_eCommonDlgMode)
            {
                case EN_COMMON_DLG_MODE_WRONG_PASSWORD:
                    u16TempID = en_str_Reenter_password;
                    break;
                case EN_COMMON_DLG_MODE_USB_UPGRADING:
                    u16TempID = en_str_Software_UpdatebracketsUSB;
                    break;
                default:
                    return 0;
            }
            break;
#endif
        case HWND_MENU_DLG_COMMON_TEXT5:
            switch(_eCommonDlgMode)
            {
#if ( ENABLE_FORCE_PRESET_PASSWORD )
                case EN_COMMON_DLG_MODE_FORCE_PRESET_PASSWORD:
#endif  //ENABLE_FORCE_PRESET_PASSWORD
                case EN_COMMON_DLG_MODE_MISMATCH_PASSWORD:
                    u16TempID = en_str_Password_doesnot_match;
                    break;
                case EN_COMMON_DLG_MODE_SET_PASSWORD:
                    u16TempID = en_str_Wrong_password;
                    break;
                default:
                    return 0;
            }
            break;

        case HWND_MENU_DLG_COMMON_TEXT6:
            switch(_eCommonDlgMode)
            {
                case EN_COMMON_DLG_MODE_FACTORY_RESET:
                    u16TempID = en_str_Reseting3dot;
                    break;
                default:
                    return 0;
            }
            break;
#if ENABLE_DRM
        case HWND_MENU_DLG_COMMON_TEXT7:
        {
            U8 u8Str[64];
            switch(_eCommonDlgMode)
            {
                case EN_COMMON_DLG_MODE_DIVX:
                case EN_COMMON_DLG_MODE_DEACTIVATION_CONFIRM:
                case EN_COMMON_DLG_MODE_DEACTIVATION:
                    snprintf((char*)u8Str, 25, "DivX(R) Video on Demand");
                    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8Str, strlen((const char *)u8Str));
                    return CHAR_BUFFER;
                default:
                    return 0;
            }
            break;
        }
        case HWND_MENU_DLG_COMMON_TEXT8:
            switch(_eCommonDlgMode)
            {
                U8 u8Str[32];
                case EN_COMMON_DLG_MODE_DIVX:
                    snprintf((char*)u8Str, 26, "You registration code is:");
                    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8Str, strlen((const char *)u8Str));
                    return CHAR_BUFFER;
                case EN_COMMON_DLG_MODE_DEACTIVATION_CONFIRM:
                    break;
                case EN_COMMON_DLG_MODE_DEACTIVATION:
                    snprintf((char*)u8Str, 30, "This device is deactivated");
                    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8Str, strlen((const char *)u8Str));
                    return CHAR_BUFFER;
                    break;

                    break;
                default:
                    return 0;
            }
            break;

        case HWND_MENU_DLG_COMMON_TEXT9:
            switch(_eCommonDlgMode)
            {
                U8 u8Str[32];
                case EN_COMMON_DLG_MODE_DIVX:
                    #if ENABLE_DRM
                    {
                        U8 i;
                        for(i = 0; i < DIVX_REG_CODE_LEN; i++)
                        {
                            u8Str[i] = stGenSetting.g_VDplayerDRMInfo.u8RegistrationCode[i];
                        }
                        u8Str[DIVX_REG_CODE_LEN] = 0;
                        MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8Str, strlen((const char *)u8Str));
                        return CHAR_BUFFER;
                    }
                    #else
                        return 0;
                    #endif
                    break;
                case EN_COMMON_DLG_MODE_DEACTIVATION_CONFIRM:
                    snprintf((char*)u8Str, 25, "Do you want to deactivate");
                    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8Str, strlen((const char *)u8Str));
                    return CHAR_BUFFER;
                case EN_COMMON_DLG_MODE_DEACTIVATION:
                    #if ENABLE_DRM
                    {
                        snprintf((char*)u8Str, 30, "Your deactivation code is:");
                        MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8Str, strlen((const char *)u8Str));
                        return CHAR_BUFFER;
                    }
                    #else
                        return 0;
                    #endif
                    break;
                default:
                    return 0;
            }
            break;

        case HWND_MENU_DLG_COMMON_TEXT10:
            switch(_eCommonDlgMode)
            {
                U8 u8Str[32];
                U8 i;
                case EN_COMMON_DLG_MODE_DEACTIVATION_CONFIRM:
                    snprintf((char*)u8Str, 12, "your device?");
                    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8Str, strlen((const char *)u8Str));
                    return CHAR_BUFFER;
                case EN_COMMON_DLG_MODE_DEACTIVATION:
                    for(i = 0; i < DIVX_DEACT_CODE_LEN; i++)
                    {
                        u8Str[i] = stGenSetting.g_VDplayerDRMInfo.u8DeActivationCode[i];
                    }
                    u8Str[DIVX_DEACT_CODE_LEN] = 0;
                    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8Str, strlen((const char *)u8Str));
                    return CHAR_BUFFER;
                default:
                    return 0;
            }
            break;

       case HWND_MENU_DLG_COMMON_TEXT11:
            switch(_eCommonDlgMode)
            {
                U8 u8Str[32];
                case EN_COMMON_DLG_MODE_DIVX:
                case EN_COMMON_DLG_MODE_DEACTIVATION:
                    snprintf((char*)u8Str, 20, "To learn more visit");
                    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8Str, strlen((const char *)u8Str));
                    return CHAR_BUFFER;
                default:
                    return 0;
            }
            break;

       case HWND_MENU_DLG_COMMON_TEXT12:
            switch(_eCommonDlgMode)
            {
                U8 u8Str[32];
                case EN_COMMON_DLG_MODE_DIVX:
                case EN_COMMON_DLG_MODE_DEACTIVATION:
                    snprintf((char*)u8Str, 17, "www.divx.com/vod");
                    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8Str, strlen((const char *)u8Str));
                    return CHAR_BUFFER;
                    break;
                default:
                    return 0;
            }
            break;
#endif
    }

    if (u16TempID != Empty)
    {
    #if ENABLE_ATSC_TTS
        if( bNeedCallTts )
        {
            MApp_TTSControlSetInputText(MApp_ZUI_API_GetString(u16TempID), MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(u16TempID)));
            MApp_TTSControlSetOn(TRUE);
        }
    #endif

        return MApp_ZUI_API_GetString(u16TempID);
    }
    return 0; //for empty string....
}


/////////////////////////////////////////////////////////
// Customize Window Procedures
S32 MApp_ZUI_ACT_MenuCommonDialogRootWinProc(HWND hwnd, PMSG msg)
{
    switch(msg->message)
    {
        case MSG_NOTIFY_SHOW:
            {
                //for factory reset dialog, execute reset procedure after one second...
                if (_eCommonDlgMode == EN_COMMON_DLG_MODE_FACTORY_RESET)
                {
                    MApp_ZUI_API_SetTimer(hwnd, 0, 1000);
                }
                else if(_eCommonDlgMode == EN_COMMON_DLG_MODE_WRONG_PASSWORD)
                {
                    MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PANE1, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_INPUT1_TEXT, SW_HIDE);
                    MApp_ZUI_API_SetFocus(HWND_MENU_DLG_PASSWORD_INPUT1_1);
                }
                else if(_eCommonDlgMode == EN_COMMON_DLG_MODE_MISMATCH_PASSWORD)
                {
                    MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PANE1, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_INPUT1_TEXT, SW_SHOW);
                    MApp_ZUI_API_SetFocus(HWND_MENU_DLG_PASSWORD_INPUT1_1);
                }
            }
            return 0;

        case MSG_TIMER:
            {
                //for factory reset dialog, execute reset procedure after one second...
                if (_eCommonDlgMode == EN_COMMON_DLG_MODE_FACTORY_RESET)
                {
                    MApp_ZUI_API_KillTimer(hwnd, 0);
                  #if DAILEO_RESET_MANU_CONFIG
                    MApp_ZUI_ACT_ExecuteMenuCommonDialogAction(EN_EXE_FACTORY_RESET/*EN_EXE_USER_SETTING_RESET*/);
                  #else
                    MApp_ZUI_ACT_ExecuteMenuCommonDialogAction(EN_EXE_FACTORY_RESET);
                  #endif
                }
                else if(_eCommonDlgMode == EN_COMMON_DLG_MODE_USB_NOT_DETECTED
                    || _eCommonDlgMode == EN_COMMON_DLG_MODE_SW_FILE_NOT_DETECTED)
                {
                    MApp_ZUI_API_KillTimer(hwnd, 0);
                    MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_COMMON, SW_HIDE);
					MApp_ZUI_ACT_ShowMainMenuBackground(HWND_MENU_BOTTOM_BALL_FOCUS_OPTION);
					MApp_ZUI_API_ShowWindow(HWND_MENU_OPTION_PAGE, SW_SHOW);
					//MApp_ZUI_CTL_DynamicListSetItemFocus(HWND_MENU_OPTION_PAGE_LIST, HWND_MENU_OPTION_DIVX);
					MApp_ZUI_API_SetFocus(HWND_MENU_OPTION_UPGRADE);
                }
                else if(_eCommonDlgMode == EN_COMMON_DLG_MODE_DIVX
                    || _eCommonDlgMode == EN_COMMON_DLG_MODE_DEACTIVATION
                    || _eCommonDlgMode == EN_COMMON_DLG_MODE_DEACTIVATION_CONFIRM)
                {
                  #if 1 //Don't let these dlgs disappear unless Exit/Select key
                    if(MApp_ZUI_API_IsExistTimer(HWND_MENU_MASK_BACKGROUND,0))
                    {
                        MApp_ZUI_API_ResetTimer(HWND_MENU_MASK_BACKGROUND, 0);
                        MApp_ZUI_API_ResetTimer(hwnd, 0);
                    }
                  #else
                    MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_COMMON, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_MENU_OPTION_PAGE, SW_SHOW);
                    MApp_ZUI_ACT_ShowMainMenuBackground(HWND_MENU_BOTTOM_BALL_FOCUS_OPTION);
                    MApp_ZUI_CTL_DynamicListSetItemFocus(HWND_MENU_OPTION_PAGE_LIST, HWND_MENU_OPTION_DEACTIVATION);
                  #endif
                }
                else if(_eCommonDlgMode == EN_COMMON_DLG_MODE_USB_UPGRADING)
                {
                    MApp_ZUI_API_KillTimer(hwnd, 0);
                    USB_Upgrade_Percent = 0;

                    // Enable Blue&black screen
                    msAPI_Scaler_SetBlueScreen( ENABLE, E_XC_FREE_RUN_COLOR_BLACK, 0, MAIN_WINDOW);

                    if ( IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
                       ||IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) )
                    {
                        MApp_ChannelChange_DisableChannel(TRUE, MAIN_WINDOW);
                    }

                #if ENABLE_DMP
                    // for dmp
                    if( UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_DMP)
                    {
                        //MApp_DMP_SetDMPStat(DMP_STATE_GOTO_PREV_SRC);
                        MApp_DMP_Exit();
                    }
                #endif // #if ENABLE_DMP

                #if ( ENABLE_SW_UPGRADE && ENABLE_FILESYSTEM )
                    //20091124EL
                    /*if(!_bOCPFromMem)
                    {
                        msAPI_OCP_LoadAllStringToMem();
                    } */


                    if (MW_UsbDownload_Start())
                    {
                        msAPI_BLoader_Reboot();
                    }
                    else
                    {
                        //Screen will Blue & Red flash
                    }
                #endif
                }
            }
            break;

        case MSG_NOTIFY_HIDE:
            {
                //note: restore pane1 position...
                MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PRESSED_PANE1, SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PANE1, SW_HIDE);

                MApp_ZUI_API_RestoreWindowRect(HWND_MENU_DLG_PASSWORD_PANE1);
                MApp_ZUI_API_RestoreWindowRect(HWND_MENU_DLG_PASSWORD_INPUT1_TEXT);
                MApp_ZUI_API_RestoreWindowRect(HWND_MENU_DLG_PASSWORD_INPUT1_1);
                MApp_ZUI_API_RestoreWindowRect(HWND_MENU_DLG_PASSWORD_INPUT1_2);
                MApp_ZUI_API_RestoreWindowRect(HWND_MENU_DLG_PASSWORD_INPUT1_3);
                MApp_ZUI_API_RestoreWindowRect(HWND_MENU_DLG_PASSWORD_INPUT1_4);
            }
            return 0;

        default:
            break;

    }

    return DEFAULTWINPROC(hwnd, msg);
}

//////////////////////////////////////////////////////
U16 _MApp_ZUI_ACT_PasswordConvertToSystemFormat(U16 password)
{
    U16 ret = 0;
    ret += (password>>12)&PASSWORD_INPUT_MASK;
    ret *= 10;
    ret += (password>>8)&PASSWORD_INPUT_MASK;
    ret *= 10;
    ret += (password>>4)&PASSWORD_INPUT_MASK;
    ret *= 10;
    ret += (password)&PASSWORD_INPUT_MASK;
    return ret;
}

typedef struct
{
    HWND hwnd;
    HWND hwndNext;
    HWND hwndPressed;
    U16 * pVar;
    U8 u8ShiftBits;
}PASSWORD_INPUT_DATA_STRUCT;

S32 MApp_ZUI_ACT_MenuPasswordInputWinProc(HWND hwnd, PMSG msg)
{
    static BOOLEAN _bPasswordBlinkBlack = FALSE;

    static  PASSWORD_INPUT_DATA_STRUCT _ZUI_TBLSEG _PasswordData[] =
    {
        {
            HWND_MENU_DLG_PASSWORD_INPUT0_1,
            HWND_MENU_DLG_PASSWORD_INPUT0_2,
            HWND_MENU_DLG_PASSWORD_PRESSED_PANE0_1,
            &PasswordInput0,
            0
        },
        {
            HWND_MENU_DLG_PASSWORD_INPUT0_2,
            HWND_MENU_DLG_PASSWORD_INPUT0_3,
            HWND_MENU_DLG_PASSWORD_PRESSED_PANE0_2,
            &PasswordInput0,
            4
        },
        {
            HWND_MENU_DLG_PASSWORD_INPUT0_3,
            HWND_MENU_DLG_PASSWORD_INPUT0_4,
            HWND_MENU_DLG_PASSWORD_PRESSED_PANE0_3,
            &PasswordInput0,
            8
        },
        {
            HWND_MENU_DLG_PASSWORD_INPUT0_4,
            HWND_MENU_DLG_PASSWORD_INPUT1_1,
            HWND_MENU_DLG_PASSWORD_PRESSED_PANE0_4,
            &PasswordInput0,
            12
        },
        {
            HWND_MENU_DLG_PASSWORD_INPUT1_1,
            HWND_MENU_DLG_PASSWORD_INPUT1_2,
            HWND_MENU_DLG_PASSWORD_PRESSED_PANE1_1,
            &PasswordInput1,
            0
        },
        {
            HWND_MENU_DLG_PASSWORD_INPUT1_2,
            HWND_MENU_DLG_PASSWORD_INPUT1_3,
            HWND_MENU_DLG_PASSWORD_PRESSED_PANE1_2,
            &PasswordInput1,
            4
        },
        {
            HWND_MENU_DLG_PASSWORD_INPUT1_3,
            HWND_MENU_DLG_PASSWORD_INPUT1_4,
            HWND_MENU_DLG_PASSWORD_PRESSED_PANE1_3,
            &PasswordInput1,
            8
        },
        {
            HWND_MENU_DLG_PASSWORD_INPUT1_4,
            HWND_MENU_DLG_PASSWORD_INPUT2_1,
            HWND_MENU_DLG_PASSWORD_PRESSED_PANE1_4,
            &PasswordInput1,
            12
        },
        {
            HWND_MENU_DLG_PASSWORD_INPUT2_1,
            HWND_MENU_DLG_PASSWORD_INPUT2_2,
            HWND_MENU_DLG_PASSWORD_PRESSED_PANE2_1,
            &PasswordInput2,
            0
        },
        {
            HWND_MENU_DLG_PASSWORD_INPUT2_2,
            HWND_MENU_DLG_PASSWORD_INPUT2_3,
            HWND_MENU_DLG_PASSWORD_PRESSED_PANE2_2,
            &PasswordInput2,
            4
        },
        {
            HWND_MENU_DLG_PASSWORD_INPUT2_3,
            HWND_MENU_DLG_PASSWORD_INPUT2_4,
            HWND_MENU_DLG_PASSWORD_PRESSED_PANE2_3,
            &PasswordInput2,
            8
        },
        {
            HWND_MENU_DLG_PASSWORD_INPUT2_4,
            HWND_MENU_DLG_PASSWORD_INPUT2_4,
            HWND_MENU_DLG_PASSWORD_PRESSED_PANE2_4,
            &PasswordInput2,
            12
        },

    };

    U8 i;
    for (i = 0; i < COUNTOF(_PasswordData); i++)
    {
        if (hwnd == _PasswordData[i].hwnd)
            break;
    }
    if (i == COUNTOF(_PasswordData)) //if not in the data list, we do nothing...
        return DEFAULTWINPROC(hwnd, msg);

    switch(msg->message)
    {
        case MSG_NOTIFY_SETFOCUS:
            {
                //enable blinking
                MApp_ZUI_API_SetTimer(hwnd, 0, 500);
                MApp_ZUI_API_InvalidateWindow(hwnd);
            }
            return 0;

        case MSG_TIMER:
            {
                //blinking
                _bPasswordBlinkBlack = !_bPasswordBlinkBlack;
                MApp_ZUI_API_InvalidateWindow(hwnd);
            }
            break;

        case MSG_NOTIFY_KILLFOCUS:
        case MSG_NOTIFY_HIDE:
            {
                //disable blinking
                MApp_ZUI_API_KillTimer(hwnd, 0);
            }
            return 0;

        case MSG_KEYDOWN:
            {
                if (VK_NUM_0 <= msg->wParam && msg->wParam <= VK_NUM_9)
                {
                #if ENABLE_ATSC_TTS
                     U8 au8InputNumber[2];
                     au8InputNumber[0] = 0x30 + (msg->wParam - VK_NUM_0);
                     au8InputNumber[1] = 0;
                     MApp_TTS_Cus_AddU8String(au8InputNumber);
                     MApp_TTSControlSetOn(TRUE);
                #endif
                    *(_PasswordData[i].pVar) &= ~(PASSWORD_INPUT_MASK<<_PasswordData[i].u8ShiftBits);
                    *(_PasswordData[i].pVar) |= ((msg->wParam-VK_NUM_0)<<_PasswordData[i].u8ShiftBits);
                    if ( _eCommonDlgMode == EN_COMMON_DLG_MODE_INPUT_PASSWORD)
                    {
                        if (i == 7) //last one
                        {
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwnd, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwndPressed, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_COMMON, SW_HIDE);
                            MApp_ZUI_ACT_ExecuteMainMenuAction(EN_EXE_CHECK_INPUT_PASSWORD);
                        }
                        else
                        {
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwnd, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwndPressed, SW_SHOW);
                            MApp_ZUI_API_SetFocus(_PasswordData[i].hwndNext);
                        }
                    }
                    if (_eCommonDlgMode ==  EN_COMMON_DLG_MODE_SCAN_INPUT_PASSWORD)
                    {
                        if (i == 7) //last one
                        {
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwnd, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwndPressed, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_COMMON, SW_HIDE);
                            MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PANE1, SW_HIDE);
                      #if (ENABLE_ATV_CHINA_APP||ENABLE_SBTVD_SCAN)//china will not use country adjust option
                            if(msAPI_SRC_IS_SBTVD_InUse())
                            {
                                MApp_ZUI_ACT_ExecuteMainMenuAction(EN_EXE_GOTO_AUTO_TUNING);
                            }
                            else
                      #endif
                            {
                                #if 0//(ENABLE_T_C_COMBO)
    				                MApp_ZUI_ACT_ExecuteMainMenuAction(EN_EXE_GOTO_DVB_SELECT);
                                #else
                                    #if ENABLE_T_C_COMBO
                                        if(MApp_DVBType_GetCurrentType() == EN_DVB_C_TYPE)
                                            MApp_ZUI_ACT_ExecuteMainMenuAction(EN_EXE_GOTO_DVBC_SCAN_PAGE);
                                        else
                                    #endif  //ENABLE_T_C_COMBO
                                        MApp_ZUI_ACT_ExecuteMainMenuAction(EN_EXE_GOTO_TUNING_CONFIRM);
                                #endif    //0
                            }
                        }
                        else
                        {
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwnd, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwndPressed, SW_SHOW);
                            MApp_ZUI_API_SetFocus(_PasswordData[i].hwndNext);
                        }
                    }
                    if(_eCommonDlgMode ==  EN_COMMON_DLG_MODE_DTV_TUNING_INPUT_PASSWORD)
                    {
                         if (i == 7) //last one
                        {
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwnd, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwndPressed, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_COMMON, SW_HIDE);
                            MApp_ZUI_ACT_ExecuteMainMenuAction(EN_EXE_GOTO_DTV_TUNING);
                        }
                        else
                        {
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwnd, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwndPressed, SW_SHOW);
                            MApp_ZUI_API_SetFocus(_PasswordData[i].hwndNext);
                        }
                    }
                    if(_eCommonDlgMode == EN_COMMON_DLG_MODE_ATV_TUNING_INPUT_PASSWORD)
                    {
                        if (i == 7) //last one
                        {
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwnd, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwndPressed, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_COMMON, SW_HIDE);
                            MApp_ZUI_ACT_ExecuteMainMenuAction(EN_EXE_GOTO_ATV_TUNING);
                        }
                        else
                        {
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwnd, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwndPressed, SW_SHOW);
                            MApp_ZUI_API_SetFocus(_PasswordData[i].hwndNext);
                        }
                    }
                    if(_eCommonDlgMode == EN_COMMON_DLG_MODE_FACTORY_RESET_INPUT_PASSWORD)
                    {
                         if (i == 7) //last one
                        {
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwnd, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwndPressed, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_COMMON, SW_HIDE);
                            MApp_ZUI_ACT_ExecuteMainMenuAction(EN_EXE_GOTO_FACTORY_RESET_CONFIRM_DLG);
                        }
                        else
                        {
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwnd, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwndPressed, SW_SHOW);
                            MApp_ZUI_API_SetFocus(_PasswordData[i].hwndNext);
                        }
                    }
                    if(_eCommonDlgMode == EN_COMMON_DLG_MODE_WRONG_PASSWORD)
                    {
                        if (i == 7) //last one
                        {
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwnd, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwndPressed, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_COMMON, SW_HIDE);
                            MApp_ZUI_ACT_ExecuteMainMenuAction(EN_EXE_PASS_PASSWORD);
                        }
                        else
                        {
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwnd, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwndPressed, SW_SHOW);
                            MApp_ZUI_API_SetFocus(_PasswordData[i].hwndNext);
                        }
                    }
                    if (_eCommonDlgMode ==  EN_COMMON_DLG_MODE_ENTER_MENU_LOCK_PAGE_INPUT_PASSWORD)
                    {
                        if (i == 7) //last one
                        {
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwnd, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwndPressed, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_COMMON, SW_HIDE);
                            MApp_ZUI_API_ShowWindow(HWND_MENU_DLG_PASSWORD_PANE1, SW_HIDE);
                            MApp_ZUI_ACT_ExecuteMainMenuAction(EN_EXE_GOTO_MENU_LOCK_PAGE);
                        }
                        else
                        {
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwnd, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwndPressed, SW_SHOW);
                            MApp_ZUI_API_SetFocus(_PasswordData[i].hwndNext);
                        }
                    }
                    else //set password dialog
                    {
                        if (i == 3)
                        {
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwnd, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwndPressed, SW_SHOW);
                            MApp_ZUI_ACT_ExecuteMainMenuAction(EN_EXE_CHECK_SET_PASSWORD_CHECKOLDPW);
                        }
                        else if (i== 11) //last one
                        {
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwndPressed, SW_SHOW);
                            _MApp_ZUI_API_WindowProcOnIdle();
                            MApp_ZUI_ACT_ExecuteMainMenuAction(EN_EXE_CHECK_SET_PASSWORD);
                        }
                        else
                        {
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwnd, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(_PasswordData[i].hwndPressed, SW_SHOW);
                            MApp_ZUI_API_SetFocus(_PasswordData[i].hwndNext);

#if (ENABLE_ATSC_TTS)
                            if((MApp_ZUI_API_IsWindowVisible(HWND_MENU_DLG_PASSWORD_PANE2))&& (i == 7))
                            {
                                MApp_TTS_Cus_Add_Str_By_StrId(en_str_Confirm_new_password);
                                MApp_TTSControlSetOn(TRUE);
                            }
#endif
                        }
                    }
                    return 0; //don't process default behavior....
                }
            }
            break;

        case MSG_PAINT:
            {
                static  DRAW_RECT _ZUI_TBLSEG _DrawPasswordBlinkBgFocus =
                {
                    0x707070,
                    0x080808,
                    OSD_COLOR_GRADIENT_Y, //OSD_GRADIENT eRectGradient;
                    0, //OSD_COLOR BroderColor;
                    eRectBorder, //RECT_ATTRIB attrib;
                    0, //U8 sizeBorder;
                    0, //radius
                };
                //get buffer GC for offline drawing...
                PAINT_PARAM * param = (PAINT_PARAM*)msg->wParam;
                if (param->bIsFocus && _bPasswordBlinkBlack)
                {

                    //2007/12/22: for bank issue, we prepare it in XDATA
                    DRAW_RECT * pDraw = (DRAW_RECT*)_ZUI_MALLOC(sizeof(DRAW_RECT));
                    if (pDraw)
                    {
                        param->dc.u8ConstantAlpha = MApp_ZUI_API_GetFocusAlpha(hwnd);
                        memcpy(pDraw, &_DrawPasswordBlinkBgFocus, sizeof(DRAW_RECT));
                        _MApp_ZUI_API_DrawDynamicComponent(CP_RECT, pDraw, &param->dc, param->rect);
                        _ZUI_FREE(pDraw);
                    }
                    else
                    {
                        __ASSERT(0);
                    }
                    return DEFAULTWINPROC(hwnd, msg);
                }
                else if (param->bIsFocus)
                {
                    return DEFAULTWINPROC(hwnd, msg);
                }
                else
                {
                    return DEFAULTWINPROC(hwnd, msg);

                    // Market it by coverity_0543
                    /*
                    //if focus is after this, show it as '*'
                    {
                        U8 j;
                        for (j = 0; j < COUNTOF(_PasswordData); j++)
                        {
                            if (MApp_ZUI_API_GetFocus()== _PasswordData[j].hwnd)
                                break;
                        }
                        if (j == COUNTOF(_PasswordData)) //if not in the password input, we do nothing...
                            return DEFAULTWINPROC(hwnd, msg);
                        if (i >= j) //if current password input is after focus (not yet input)
                            return DEFAULTWINPROC(hwnd, msg);
                    }
                    {
                        DRAW_TEXT_OUT_DYNAMIC * dyna;
                        U16 u16TextIndex = _MApp_ZUI_API_FindFirstComponentIndex(hwnd, DS_NORMAL, CP_TEXT_OUT);
                        if (u16TextIndex != 0xFFFF)
                        {
                            param->dc.u8ConstantAlpha = MApp_ZUI_API_GetNormalAlpha(hwnd);

                            dyna = (DRAW_TEXT_OUT_DYNAMIC*)_ZUI_MALLOC(sizeof(DRAW_TEXT_OUT_DYNAMIC));
                            if (dyna)
                            {
                                LPTSTR str = CHAR_BUFFER;
                                _MApp_ZUI_API_ConvertTextComponentToDynamic(u16TextIndex, dyna);
                                str[0] = '*';
                                str[1] = 0;
                                dyna->pString = str;
                                _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, dyna, &param->dc, param->rect);
                                _ZUI_FREE(dyna);
                            }
                        }
                    }
                    */
                }

            }
            return 0;
        default:
            break;


    }

    return DEFAULTWINPROC(hwnd, msg);
}

void MApp_ZUI_SwUpdate_ProgressBar(U8 percent)
{
    U8 u8tmp = 0;
    if(_eCommonDlgMode == EN_COMMON_DLG_MODE_USB_UPGRADING)
    {
        static const HWND aUpdateWindows[] =
        {
            HWND_MENU_DLG_COMMON_NEW_BG_C,
            HWND_MENU_DLG_COMMON_ICON,
            HWND_MENU_DLG_COMMON_TEXT2,
        #if ( (MEMORY_MAP > MMAP_32MB) || (CHIP_FAMILY_TYPE != CHIP_FAMILY_WHISKY))
            HWND_MENU_DLG_COMMON_TEXT4
        #endif
        };

        USB_Upgrade_Percent = percent;
        u8tmp = sizeof(aUpdateWindows)/sizeof(HWND);
        _MApp_ZUI_API_ForceUpdateWindows((HWND*)aUpdateWindows,u8tmp);
    }
    return;
}
#undef MAPP_ZUI_ACTMENUDLGFUNC_C

