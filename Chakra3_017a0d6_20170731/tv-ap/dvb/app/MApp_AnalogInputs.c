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

#define _MAPP_ANALOGINPUTS_C

//------------------------------------------------------------------------------
//                            Header Files
//------------------------------------------------------------------------------
#include "Board.h"

#include <string.h>
#include <stdio.h>

#include "MsCommon.h"


#if(ENABLE_TEST_PATTERN)
#include "msAPI_TestPattern.h"
#endif

#include "MApp_Main.h"
#include "MApp_Exit.h"
#include "MApp_GlobalVar.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalFunction.h"
#include "MApp_Key.h"
#include "MApp_IR.h"
#include "MApp_Audio.h"
#include "MApp_MultiTasks.h"
#include "MApp_DataBase.h"
#include "MApp_Scan.h"
#include "MApp_Font.h"
#include "MApp_InputSource.h"
#include "MApp_PCMode.h"
#include "MApp_VDMode.h"
#include "MApp_AnalogInputs.h"
#include "MApp_TV.h"
#include "MApp_ChannelChange.h"
#include "MApp_Bitmap.h"
#include "apiXC_Ace.h"
#include "MApp_Sleep.h"
#include "MApp_Scaler.h"
#include "MApp_UiMenuDef.h"
#include "MApp_ZUI_Main.h"
#include "ZUI_tables_h.inl"
#include "ZUI_exefunc.h"
#include "MApp_BlockSys.h"
#include "MApp_SaveData.h"
#include "MApp_ATVProc.h"
#include "MApp_ChannelList.h"
#include "MApp_Init.h"

#include "msAPI_OSD.h"
#include "apiGOP.h"
#include "msAPI_Timer.h"
#include "msAPI_Mode.h"
#include "apiXC_Sys.h"
#include "apiXC_PCMonitor.h"

#include "msAPI_DTVSystem.h"
#include "msAPI_DrvInit.h"
#include "msAPI_audio.h"
#include "msAPI_Tuning.h"
#include "msAPI_ChProc.h"
#if ENABLE_TTX
#include "msAPI_TTX.h"
#include "mapp_ttx.h"
#endif

#include "MApp_TopStateMachine.h"
#include "GPIO.h"
#include "drvpower_if.h"
#include "msAPI_FreqTableATV.h"

#include "msIR.h"

#if ENABLE_DMP
#include "mapp_mplayer.h"
#include "MApp_UiMediaPlayer.h"
#endif


#if ENABLE_CI
#include "MApp_CIMMI.h"
#include "msAPI_CI.h"
#endif

#if (((BRAZIL_CC))||(ATSC_CC == ATV_CC))
#include "mapp_closedcaption.h"
#endif

#if 0//(NO_SIGNAL_AUTO_SHUTDOWN )
#include "MApp_NoSignal_AutoSleep.h"
#endif

#if ENABLE_DTV_EPG //ENABLE_DTV
    extern void MApp_ZUI_EpgTimerCountDown(void);
    extern BOOLEAN MApp_TV_ProcessEpgCountDownKey(U8 key);
#endif

#if 0//ENABLE_E_POP //move out
extern void MApp_ZUI_ACT_EpopHandler(void);
#endif

//------------------------------------------------------------------------------
//                                Local
//------------------------------------------------------------------------------
#define ANALOGINPUTS_DBINFO(y)   //y

#define TV_MODE_WINDOW_MONITOR_PERIOD 2000 //ms
#define TV_MODE_WINDOW_MONITOR_PERIOD_NOSINGAL 50 //ms

#define DELAY_4SEC  60

//static EN_RET enAnalogInputsRetVal;
//static EN_ANALOGINPUTS_STATE enAnalogInputsState = STATE_ANALOGINPUTS_INIT;
static U32 u32AnalogInputsModeWinTimer[PIP_WINDOWS];
static U8 su8NoSignalDisplayCNT[PIP_WINDOWS] = {DELAY_4SEC, DELAY_4SEC};

#if ENABLE_TTX
//static U_INT8 SubtitlePageIndex;
#endif
extern EN_RET enTVRetVal;
extern EN_TV_STATE enTVState;
BOOLEAN MApp_Analog_NoSignal_ExcludeATV()
{
     return ( ( ( IsVgaInUse() || IsYPbPrInUse() || (IsHDMIInUse()) ) && MApi_XC_PCMonitor_SyncLoss(MAIN_WINDOW) )
               || ((IsAVInUse()||(IsSVInUse())||(IsScartInUse()))&&(!MApp_VD_IsSyncLock())));
}

//------------------------------------------------------------------------------
// Function name:    MApp_AnalogInputs_FunctionNotAvailableCheck
// Passing parameter:    none
// Return parameter:    none
// Description:      If function not available, draw a warning message dialog then return true
//------------------------------------------------------------------------------
BOOLEAN MApp_AnalogInputs_FunctionNotAvailableCheck()
{
    if ( MApp_Analog_NoSignal_ExcludeATV() )
    {
        //ZUI: #if SHOW_NOT_AVAILABLE_WARNING_MESSAGE
        //ZUI: MApp_UiMenu_Show_Warning_Message_Dialog(MENU_FUNCTION_NOT_AVAILABLE_MSG);
        MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_FUNC_NOT_AVAIL_MSGBOX);
        //ZUI: #endif
       return TRUE;
    }
    return FALSE;
}

/********************************************************************************/
/*                   Functions                      */
/********************************************************************************/
//*************************************************************************
//Function name:    MApp_AnalogInputs_DeleteWin
//Passing parameter:    none
//Return parameter:    none
//Description:      Delete idle mode OSD window
//*************************************************************************
void MApp_AnalogInputs_DeleteWin(void)
{
    /*/ZUI:
    if (enCurTVWin != DISP_WIN_NONEOSD &&
        enCurTVWin != DISP_WIN_MUTE) //2007/10/25: fix mute blinking in AV mode
    {
        MApp_UiMenu_HideShortcut();
        MApp_UiMenu2_HideOSDGwin(GWIN_MAIN_MENU);
        enCurTVWin = DISP_WIN_NONEOSD;
    }
    */
}

//*************************************************************************
//Function name:    MApp_AnalogInputs_MonitorWindows
//Passing parameter:    none
//Return parameter:    none
//Description:      Monitor idle mode OSD window
//*************************************************************************
void MApp_AnalogInputs_MonitorWindows(SCALER_WIN eWindow)
{

#if ENABLE_ATSC
    if ((MApp_ZUI_GetActiveOSD() == E_OSD_EMPTY) && g_bInputBlocked)
    {
        MApp_ChannelChange_CheckBlockChannelPW();
        return;
    }
#endif

#if 0//(ENABLE_TEST_PATTERN)
    if(msAPI_TestPattern_Get_Status() ==TRUE)
        return;
#endif

#if 0//(NO_SIGNAL_AUTO_SHUTDOWN)
    MApp_NoSignalAutoSleep_Task();
#endif

#if 0//(ENABLE_POST_INIT)
    if(MApp_Get_PostInit_Status()==FALSE)
    {
        return;
    }
#endif

    // monitor all windows in idle mode
    if (msAPI_Timer_DiffTimeFromNow(u32AnalogInputsModeWinTimer[eWindow]) > TV_MODE_WINDOW_MONITOR_PERIOD_NOSINGAL) //unit = ms
    {
        if(IsSrcTypeAnalog(SYS_INPUT_SOURCE_TYPE(eWindow)) || IsSrcTypeHDMI(SYS_INPUT_SOURCE_TYPE(eWindow)))   //PC & YPBPR
        {
#if (INPUT_HDMI_VIDEO_COUNT > 0)
            if((IsSrcTypeHDMI(SYS_INPUT_SOURCE_TYPE(eWindow)) && (MApp_PCMode_GetCurrentState(eWindow) == E_PCMODE_UNSTABLE)))
            {
                u32AnalogInputsModeWinTimer[eWindow] = msAPI_Timer_GetTime0();
                return;
            }
#endif
            if(MApi_XC_PCMonitor_SyncLoss(eWindow) || (MApp_PCMode_GetCurrentState(eWindow) == E_PCMODE_STABLE_UN_SUPPORT_MODE)
               )
            { // no sync
                if(!su8NoSignalDisplayCNT[eWindow])
                {
                    if(MApp_PCMode_GetCurrentState(eWindow) == E_PCMODE_STABLE_UN_SUPPORT_MODE) //un-support mode
                    {
                        ANALOGINPUTS_DBINFO(printf("IDLE_WIN>> un-support mode \n"));
                        enTVState = STATE_TV_INIT;
                        //enAnalogInputsRetVal = EXIT_GOTO_MENU;
                        SYS_SCREEN_SAVER_TYPE(eWindow) = EN_SCREENSAVER_UNSUPPORT_MODE;
                        //ZUI: MApp_UiMenu_ExecuteKeyEvent(MIA_UNSUPPORTED_MODE_MSG_BOX);
                        //ZUI: enUiMainMenuState = STATE_UIMENU_CLEAN_UP;
                    }
                    else
                    {
                    #if ENABLE_OFFLINE_SIGNAL_DETECTION
                        //printf("no signal  pc/ypbpr");
                        stAISCtrl.bNoSignal=1;
                        if((UI_INPUT_SOURCE_RGB == UI_INPUT_SOURCE_TYPE)
                      #if (INPUT_YPBPR_VIDEO_COUNT>=1)
                        || (UI_INPUT_SOURCE_COMPONENT== UI_INPUT_SOURCE_TYPE)
                      #endif
                        )
                        {
                            if(stGenSetting.g_SysSetting.bAIS!=AIS_OFF)
                            {
                                stAISSrcList[UI_INPUT_SOURCE_TYPE].bHaveSignal=0;
                            }
                        }
                    #endif
                        ANALOGINPUTS_DBINFO(printf("IDLE_WIN>> no sync\n"));
                        enTVState = STATE_TV_INIT;
                        //enAnalogInputsRetVal = EXIT_GOTO_MENU;
                        if(IsSrcTypeAnalog(SYS_INPUT_SOURCE_TYPE(eWindow))||IsSrcTypeHDMI(SYS_INPUT_SOURCE_TYPE(eWindow)))
                        {
                            SYS_SCREEN_SAVER_TYPE(eWindow) = EN_SCREENSAVER_NOSYNC;
                        }
                        //ZUI: MApp_UiMenu_ExecuteKeyEvent(MIA_NO_SYNC_MSG_BOX);
                        //ZUI: enUiMainMenuState = STATE_UIMENU_CLEAN_UP;
                    }

                    if (MApp_ZUI_GetActiveOSD() == E_OSD_SCREEN_SAVER)
                    {
                        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_ALL);
                    }
                    else if (MApp_ZUI_GetActiveOSD() == E_OSD_EMPTY)
                    {
                        MApp_ZUI_ACT_StartupOSD(E_OSD_SCREEN_SAVER);
                    }
                /*
                  #if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD) || \
                        (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7J) || \
                        (CHIP_FAMILY_TYPE == CHIP_FAMILY_M10) || \
                        (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7)  || \
                        (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN)|| \
                        (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA)|| \
                        (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER))
                       //printf("<<<<<<<<<<<<<<<<1 Always set CVBS out\n");  //20100421EL
                  #else
                        //msAPI_Scaler_SetCVBSMute(ENABLE, E_VE_MUTE_GEN,SYS_INPUT_SOURCE_TYPE(eWindow),OUTPUT_CVBS1);
                      #if (INPUT_SCART_VIDEO_COUNT > 1)
                        //msAPI_Scaler_SetCVBSMute(ENABLE, E_VE_MUTE_GEN,SYS_INPUT_SOURCE_TYPE(eWindow),OUTPUT_CVBS2);
                      #endif
                  #endif
                  */

                }
                else
                {
                    if(su8NoSignalDisplayCNT[eWindow]>0)
                    {
                        su8NoSignalDisplayCNT[eWindow]--;
                    }
                }
            }
            else
            {
            #if ENABLE_OFFLINE_SIGNAL_DETECTION
                //printf("Signal in pc/ypbpr");
                stAISCtrl.bNoSignal=0;
            #endif
                su8NoSignalDisplayCNT[eWindow] = DELAY_4SEC;
            }
        }
        else //if(IsDigitalSourceInUse())
        {    //Todo PIP: deal with SUB_WINDOW aspect
        #if (ATSC_CC == ATV_CC)
            if((enTVState == STATE_TV_WAIT)&& (IsSrcTypeAV(SYS_INPUT_SOURCE_TYPE(eWindow)) && DB_CC_SETTING.enATVCaptionType != ATV_CAPTION_TYPE_OFF))
            {
                enTVState = STATE_TV_INIT;
                enTVRetVal = EXIT_GOTO_CLOSEDCAPTION;
            }

            if  ( IsSrcTypeAV(SYS_INPUT_SOURCE_TYPE(eWindow))
               && DB_CC_SETTING.enATVCaptionType != ATV_CAPTION_TYPE_OFF
               && (SYS_SCREEN_SAVER_TYPE(eWindow)==EN_SCREENSAVER_NULL) )
            {
                if (MApp_CC_GetInfo(CC_SELECTOR_STATUS_CODE) != STATE_CAPTION_PARSER)
                {
                    U32 u32Err;
                    u32Err = MApp_CC_CtrlParser(CC_SELECTOR_MODE, CC_MODE_ATV);
                    u32Err = MApp_CC_CtrlParser(CC_SELECTOR_SERVICE, (EN_CLOSEDCAPTION_SERVICE)DB_CC_SETTING.enATVCaptionType);
                    u32Err = MApp_CC_CtrlParser(CC_SELECTOR_RESET_TO_DEFAULT, ENABLE);
                #if 0//def HER_BRAZIL
                    u32Err = MApp_CC_CtrlParser(CC_SELECTOR_AXIS_XPOS, 0xA4);        // horizontal offset
                    u32Err = MApp_CC_CtrlParser(CC_SELECTOR_AXIS_YPOS, 0x74);        // vertical offset
                #endif
                    u32Err = MApp_CC_StartParser();
                }
            }
        #endif // #if (ATSC_CC == ATV_CC)

#if (BRAZIL_CC)
            if(IS_SBTVD_APP)
            {
                if(MApp_VD_IsSyncLock())
                {
                        if ((enTVState == STATE_TV_WAIT)&&(MApp_ZUI_GetActiveOSD() ==E_OSD_EMPTY)&&(IsAVInUse() || IsSVInUse()) && DB_CC_SETTING.enATVCaptionType != ATV_CAPTION_TYPE_OFF)
                        {
                                enTVState = STATE_TV_INIT;
                                enTVRetVal = EXIT_GOTO_CLOSEDCAPTION;
                        }
                        if ((IsAVInUse() || IsSVInUse())
                        && DB_CC_SETTING.enATVCaptionType != ATV_CAPTION_TYPE_OFF
                        && MApp_ZUI_GetActiveOSD() ==E_OSD_EMPTY
                        &&(SYS_SCREEN_SAVER_TYPE(eWindow)==EN_SCREENSAVER_NULL))
                        {
                            if(MApp_CC_GetInfo(CC_SELECTOR_STATUS_CODE) != STATE_CAPTION_PARSER)
                            {
                                U32 u32Err;
                                u32Err = MApp_CC_CtrlParser(CC_SELECTOR_MODE, CC_MODE_ATV);
                                u32Err = MApp_CC_CtrlParser(CC_SELECTOR_SERVICE, (EN_CLOSEDCAPTION_SERVICE)DB_CC_SETTING.enATVCaptionType);
                                u32Err = MApp_CC_CtrlParser(CC_SELECTOR_RESET_TO_DEFAULT, ENABLE);
                                u32Err = MApp_CC_CtrlParser(CC_SELECTOR_608_SCROLL_STEP, ENABLE);
								u32Err = MApp_CC_CtrlParser(CC_SELECTOR_608_TIMEOUT_TEXT, 16000);
                            #if 0//def HER_BRAZIL
                                u32Err = MApp_CC_CtrlParser(CC_SELECTOR_AXIS_XPOS, 0xA4);        // horizontal offset
                                u32Err = MApp_CC_CtrlParser(CC_SELECTOR_AXIS_YPOS, 0x74);        // vertical offset
                            #endif
                                u32Err = MApp_CC_StartParser();
                            }
                        }
                }
                else
                {
                    if (MApp_CC_GetInfo(CC_SELECTOR_STATUS_CODE) == STATE_CAPTION_PARSER)
                    {
                        MApp_CC_StopParser();
                        MApp_Dmx_PES_Stop();
                    }
                }
            }
#endif

            if(!MApp_VD_IsSyncLock())
            {   // no sync
                if(!su8NoSignalDisplayCNT[eWindow])
                {
                #if ENABLE_OFFLINE_SIGNAL_DETECTION
                    //printf("Analog VD no signal");
                    stAISCtrl.bNoSignal=1;
                    if((UI_INPUT_SOURCE_AV== UI_INPUT_SOURCE_TYPE)
                  #if (INPUT_AV_VIDEO_COUNT >= 2)
                    || (UI_INPUT_SOURCE_AV2== UI_INPUT_SOURCE_TYPE)
                  #endif
                    )
                    {
                        if(stGenSetting.g_SysSetting.bAIS!=AIS_OFF)
                        {
                            stAISSrcList[UI_INPUT_SOURCE_TYPE].bHaveSignal=0;
                        }
                    }
                #endif
                    ANALOGINPUTS_DBINFO(printf("IDLE_WIN>> VD no sync\n"));
                    enTVState = STATE_TV_INIT;
                    //enAnalogInputsRetVal = EXIT_GOTO_MENU;
                    if(IsSrcTypeDigitalVD(SYS_INPUT_SOURCE_TYPE(eWindow)))
                    {
                        SYS_SCREEN_SAVER_TYPE(eWindow) = EN_SCREENSAVER_NOSYNC_VD;
                    }
                    if( (SYS_SCREEN_SAVER_TYPE(eWindow) == EN_SCREENSAVER_NOSIGNAL) \
                        || (SYS_SCREEN_SAVER_TYPE(eWindow) == EN_SCREENSAVER_NOSYNC) \
                        || (SYS_SCREEN_SAVER_TYPE(eWindow) == EN_SCREENSAVER_NOSYNC_VD))
                    {
                        //  power saving TO DO : wait for API from ken.chang
                    }
                    //ZUI: MApp_UiMenu_ExecuteKeyEvent(MIA_NO_SYNC_MSG_BOX);
                    //ZUI: enUiMainMenuState = STATE_UIMENU_CLEAN_UP;
                    //Todo PIP: need to know main or sub window is un-locked
                    //  and how to pass this msg to screen saver?
                    if (MApp_ZUI_GetActiveOSD() == E_OSD_SCREEN_SAVER)
                    {
                        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_ALL);
                    }
                    else if (MApp_ZUI_GetActiveOSD() == E_OSD_EMPTY )
                    {
                    	if(IsSrcTypeAV(SYS_INPUT_SOURCE_TYPE(eWindow)))
                		{
                			if(FALSE==MApp_TV_ScreenSaverClear(MAIN_WINDOW))
            				{
						MApp_ZUI_ACT_StartupOSD(E_OSD_SCREEN_SAVER);
            				}
                		}
				else
				{
                               	MApp_ZUI_ACT_StartupOSD(E_OSD_SCREEN_SAVER);
				}
                    }
                }
                else
                {
                    if(su8NoSignalDisplayCNT[eWindow]>0)
                        su8NoSignalDisplayCNT[eWindow]--;
                }
            }
            else
            { // others
              #if ENABLE_OFFLINE_SIGNAL_DETECTION
                //printf("Signal in VD");
                stAISCtrl.bNoSignal=0;
              #endif
                ANALOGINPUTS_DBINFO(printf("IDLE>> other\n"));
                /*/ZUI:
                if(enCurTVWin != DISP_WIN_NONEOSD)
                {
                    MApp_AnalogInputs_DeleteWin();
                }*/
                su8NoSignalDisplayCNT[eWindow] = DELAY_4SEC;
            }
        }
        u32AnalogInputsModeWinTimer[eWindow] = msAPI_Timer_GetTime0();
    }

#if 0//ENABLE_E_POP  //move out
    MApp_ZUI_ACT_EpopHandler();
#endif
}

//*************************************************************************
//Function name:    MApp_AnalogInputs_Init
//Passing parameter:    none
//Return parameter:    none
//Description:      Initialize all state before entering idle mode
//*************************************************************************
void MApp_AnalogInputs_Init(SCALER_WIN eWindow)
{
    //ZUI: enMenuFlowState = FS_WAIT_MENU;
    //ZUI: enMenuMode = ANALOGINPUTS_MODE;

    u32AnalogInputsModeWinTimer[eWindow] = msAPI_Timer_GetTime0();
    u16IdleInputValue = 0;
    //ZUI: refine: u8IdleDigitCount = 0;
}

void MApp_AnalogInputs_Force2MonitorWindows(SCALER_WIN eWindow)
{
    u32AnalogInputsModeWinTimer[eWindow] -= TV_MODE_WINDOW_MONITOR_PERIOD;
}
#if 0 // useless after merge STATE_TOP_ANALOGINPUTS and STATE_TOP_DIGITALINPUTS
/*****************************************************************************/
// TELETEXT key handler
#if ENABLE_TTX

extern U32 g_u32MonitorTTXClockTimer;

static void MApp_AnalogInputs_TTX_ProcessUserInput(void)
{
    if((MApp_TTX_GetControlMode()!=TTX_MODE_NORMAL))
    {
        if (u8KeyCode == KEY_CLOCK && MApp_TTX_GetControlMode()==TTX_MODE_CLOCK)
            u8KeyCode = KEY_NULL;

        if(u8KeyCode != KEY_NULL)
        {
            if(MApp_TTX_GetControlMode()==TTX_MODE_SUBTITLE)
            {
                switch(u8KeyCode)
                {
                    case KEY_VOLUME_PLUS:
                    case KEY_VOLUME_MINUS:
                    {
                        /*//ZUI_TODO:
                        MApp_UiMenu2_SwitchToGwin(GWIN_DYNAMICMSG );
                        if ( MApp_TTX_GetOSDState() != STATE_TTX_OSD_VOLUMN)
                        {
                            MApp_UiMenu_ExecuteKeyEvent( MIA_VOLUME );
                        }
                        if ( u8KeyCode == KEY_VOLUME_PLUS )
                        {
                            MApp_UiMenu_ExecuteKeyEvent( MIA_INCVALUE );
                        }
                        else
                        {
                            MApp_UiMenu_ExecuteKeyEvent( MIA_DECVALUE );
                        }
                        */
                        MApp_ZUI_ACT_StartupOSD(E_OSD_AUDIO_VOLUME);
                        MApp_TV_ProcessAudioVolumeKey(u8KeyCode);
                        //ZUI_TODO: MApp_TTX_SetOSDState(STATE_TTX_OSD_VOLUMN);
                        u8KeyCode = KEY_NULL;
                        break;
                    }
                    case KEY_SUBTITLE:
                    {
                        if ( SubtitlePageIndex == (MApp_TTX_GetSubtitlesAvailable()-1) ) //reset SubtitlePageIndex and exit Subtitle Mode
                        {
                            SubtitlePageIndex = 0;
                        }
                        else
                        {
                            U16 magPage, subPage;

                            SubtitlePageIndex++;
                            msAPI_TTX_GetSubtitlePage( SubtitlePageIndex, &magPage, &subPage);
                            MApp_TTX_SetSubtitlePage(magPage, subPage);
                            MApp_TTX_TeletextCommand(TTX_SUBTITLE_TTX_ON);  //open the next subtitle
                        }

                        u8KeyCode = KEY_NULL;
                        break;
                    }
                    case KEY_RED:
                    case KEY_GREEN:
                    case KEY_YELLOW:
                    case KEY_BLUE:
                    case KEY_EXIT:
                    case KEY_BACK:
                    case KEY_UP:
                    case KEY_DOWN:
                    case KEY_LEFT:
                    case KEY_RIGHT:
                    case KEY_UPDATE:
                    case DSC_KEY_MULTI_PIP:
                    case KEY_TIME:
                    case KEY_HOLD:
                    case KEY_REVEAL:
                    case KEY_SIZE:
                    case KEY_TTX_MODE:
                    {
                        u8KeyCode = KEY_NULL;
                        break;
                    }
                    default:
                    {
                        // Before exit, check state. If there's any OSD state
                        /*/ZUI_TODO:
                        if(MApp_TTX_GetOSDState()==STATE_TTX_OSD_VOLUMN)
                        {
                            MApp_UiMenu_ExecuteKeyEvent( MIA_EXIT );
                            MApp_TTX_SetOSDState(STATE_TTX_OSD_NONE);
                        }
                        */
                        MApp_TTX_TeletextCommand(TTX_TV);
                        break;
                    }

                }
            }
            else
            {
                MApp_TTX_TeletextCommand(TTX_TV);//leave TTX to TV
                u8KeyCode = KEY_NULL;
            }
        }
    }
    else
    {
        switch ( u8KeyCode )
        {
        case KEY_POWER:
            MApp_TTX_TeletextCommand(TTX_TV);
            enTVState = STATE_TV_INIT;
            enAnalogInputsRetVal = EXIT_GOTO_STANDBY;
            u8KeyCode = KEY_NULL;
            break;
        case KEY_1:
        case KEY_2:
        case KEY_3:
        case KEY_4:
        case KEY_5:
        case KEY_6:
        case KEY_7:
        case KEY_8:
        case KEY_9:
        case KEY_0:
            MApp_TTX_TeletextCommand((TELETEXT_COMMAND)(u8KeyCode - KEY_0));
            break;

        case KEY_VOLUME_PLUS:
            if ( stGenSetting.g_SoundSetting.Volume < MAX_NUM_OF_VOL_LEVEL )
            {
                stGenSetting.g_SoundSetting.Volume+= VOLUME_STEP;
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, stGenSetting.g_SoundSetting.Volume, 0);
            }
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            break;

        case KEY_VOLUME_MINUS:
            if ( stGenSetting.g_SoundSetting.Volume > 0 )
            {
                stGenSetting.g_SoundSetting.Volume-= VOLUME_STEP;
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, stGenSetting.g_SoundSetting.Volume, 0);
            }
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            break;

        case KEY_EXIT:
        case KEY_TTX:
            MApp_TTX_TeletextCommand(TTX_TV);
            //ZUI_TODO: g_u8MenuPageIndex = MENU_ROOT;
            break;

#if ENABLE_TTX_ACI
        case KEY_UP:    // when multi-package, users can use key-up, key-down, and key-ok, to select what they want
            MApp_TTX_TeletextCommand(TTX_UP);
            break;

        case KEY_DOWN:  // when multi-package, users can use key-up, key-down, and key-ok, to select what they want
            MApp_TTX_TeletextCommand(TTX_DOWN);
            break;

        case KEY_SELECT:    // when multi-package, users can use key-up, key-down, and key-ok, to select what they want
            MApp_TTX_TeletextCommand(TTX_OK);
            break;
#endif
        case KEY_CHANNEL_PLUS:
            MApp_TTX_TeletextCommand(TTX_PAGE_UP);
            break;

        case KEY_CHANNEL_MINUS:
            MApp_TTX_TeletextCommand(TTX_PAGE_DOWN);
            break;

        case KEY_LEFT:
            MApp_TTX_TeletextCommand(TTX_PAGE_LEFT);
            break;

        case KEY_RIGHT:
            MApp_TTX_TeletextCommand(TTX_PAGE_RIGHT);
            break;

        case KEY_RED:
            MApp_TTX_TeletextCommand(TTX_RED);
            break;

        case KEY_GREEN:
            MApp_TTX_TeletextCommand(TTX_GREEN);
            break;

        case KEY_YELLOW:
            MApp_TTX_TeletextCommand(TTX_YELLOW);
            break;

        case KEY_BLUE:
            MApp_TTX_TeletextCommand(TTX_CYAN);
            break;

        case KEY_SIZE:
            MApp_TTX_TeletextCommand(TTX_SIZE);
            break;

        case KEY_MIX:
            MApp_TTX_TeletextCommand(TTX_MIX);
            break;

        case KEY_INDEX:
            MApp_TTX_TeletextCommand(TTX_INDEX);
            break;

        case KEY_HOLD:
            MApp_TTX_TeletextCommand(TTX_HOLD);
            break;
        case KEY_UPDATE:        // add update key
            MApp_TTX_TeletextCommand(TTX_UPDATE);
            break;
        case KEY_REVEAL:
            MApp_TTX_TeletextCommand(TTX_REVEAL);
            break;

        case KEY_CHANNEL_LIST:  // list
            MApp_TTX_TeletextCommand(TTX_LIST);
            break;

        case KEY_SUBTITLE:
            MApp_TTX_TeletextCommand(TTX_SUBPAGE);
            break;

        default:
            break;
        }

        u8KeyCode = KEY_NULL;
    }
}
#endif  // #if ENABLE_TTX
#endif
//*************************************************************************
//Function name:        MApp_AnalogInputs_ProcessUserInput
//Passing parameter:    none
//Return parameter:     none
//Description:          Handle IR/FP key
//*************************************************************************
#if (BRAZIL_CC == 1) && (CC_ATV_TEST == 1)
static U8 u8TestCC=0;
#endif
#if 0 // useless after merge STATE_TOP_ANALOGINPUTS and STATE_TOP_DIGITALINPUTS
void MApp_AnalogInputs_ProcessUserInput(void)
{
    //2007/12/14: in some osd, we don't switch to other state, but we direct key event to ZUI
    //2008/3/27: handle keys here! don't handle these keys in MApp_ZUI_ACTxxx.c
    switch ( MApp_ZUI_GetActiveOSD()  )
    {
        case E_OSD_HOTKEY_OPTION:
            if (MApp_TV_ProcessHotkeyOptionKey(u8KeyCode))
                u8KeyCode = KEY_NULL;
            break;
        case E_OSD_AUDIO_VOLUME:
            if (MApp_TV_ProcessAudioVolumeKey(u8KeyCode))
                u8KeyCode = KEY_NULL;
            break;
        case E_OSD_MESSAGE_BOX:
            if (MApp_TV_ProcessMessageBoxKey(u8KeyCode))
                u8KeyCode = KEY_NULL;
            break;
        case E_OSD_CHANNEL_INFO:
            if (MApp_TV_ProcessChannelInfoKey(u8KeyCode))
                u8KeyCode = KEY_NULL;
            break;
#if ENABLE_DTV_EPG //ENABLE_DTV
        case E_OSD_EPG:
            if (MApp_TV_ProcessEpgCountDownKey(u8KeyCode))
                u8KeyCode = KEY_NULL;
            break;
#endif
        default:
            break;

    }

    switch ( u8KeyCode )
    {
        case KEY_POWER:
        case DSC_KEY_PWROFF:
            MApp_ZUI_ACT_ShutdownOSD(); /*/ZUI: if(enCurTVWin != DISP_WIN_NONEOSD)
                MApp_AnalogInputs_DeleteWin();*/

            enTVState = STATE_TV_INIT;
            enTVRetVal = EXIT_GOTO_STANDBY;
            u8KeyCode = KEY_NULL;
            break;

        case KEY_EXIT:
             u8KeyCode = KEY_NULL;
            break;

        case KEY_MENU:
            enTVState = STATE_TV_INIT;
            enTVRetVal = EXIT_GOTO_MENU;
            u8KeyCode = KEY_NULL;
            break;
        case KEY_COUNTDOWN_EXIT_TT_SUBTITLE:
            if (MApp_ZUI_GetActiveOSD() != E_OSD_MESSAGE_BOX ||
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_QUERY_IS_POWER_OFF_COUNTDOWN_MSG_BOX) == FALSE)
            {
                MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_POWER_OFF_COUNTDOWN_MSG_BOX);
            }
            u8KeyCode = KEY_NULL;
            break;
#if ENABLE_DTV_EPG //ENABLE_DTV
        case KEY_EPGTIMER_COUNTDOWN:
            MApp_ZUI_EpgTimerCountDown();
            u8KeyCode = KEY_NULL;
            break;
#endif
        case KEY_MUTE:
        case KEY_VOLUME_PLUS:
        case KEY_VOLUME_MINUS:
            MApp_ZUI_ACT_StartupOSD(E_OSD_AUDIO_VOLUME);
            MApp_TV_ProcessAudioVolumeKey(u8KeyCode);
             MApp_AnalogInputs_ResetTimer();
            u8KeyCode = KEY_NULL;
            break;

        case KEY_1:
        case KEY_2:
        case KEY_3:
        case KEY_4:
        case KEY_5:
        case KEY_6:
        case KEY_7:
        case KEY_8:
        case KEY_9:
        case KEY_0:
            MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_FUNC_NOT_AVAIL_MSGBOX);

            u8KeyCode = KEY_NULL;
            break;
        case KEY_INPUT_SOURCE:
            enTVState = STATE_TV_INIT;
            enTVRetVal = EXIT_GOTO_INPUTSOURCE; //ZUI: EXIT_GOTO_MENU;
            u8KeyCode = KEY_NULL;
            break;

             // source switching hotkey
            case KEY_DTV:
            #if (ENABLE_DTV)
                if(UI_INPUT_SOURCE_TYPE != UI_INPUT_SOURCE_DTV)
                {
                    //ZUI: MApp_UiMenu_ExecuteKeyEvent(MIA_EXIT);
                    UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DTV;
                    MApp_InputSource_ChangeInputSource(); //ZUI: MApp_UiMenuFunc_ChangeInputSource();
                    MApp_ChannelChange_VariableInit();
                    MApp_TopStateMachine_SetTopState(STATE_TOP_CHANNELCHANGE);
                }
                else
            #endif
                {
                  //ZUI: MApp_UiMenu_DisplayShortCut(DISP_WIN_CHANNEL_BANNER, TRUE);
                    MApp_ZUI_ACT_StartupOSD(E_OSD_CHANNEL_INFO);
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_BRIEF_CH_INFO);
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_SOURCE_BANNER);
                }
                u8KeyCode = KEY_NULL;
                break;
            case KEY_TV:
                if(UI_INPUT_SOURCE_TYPE != UI_INPUT_SOURCE_ATV)
                {

                    //ZUI: MApp_UiMenu_ExecuteKeyEvent(MIA_EXIT);
                    UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ATV;
                    MApp_InputSource_ChangeInputSource(); //ZUI: MApp_UiMenuFunc_ChangeInputSource();
                    MApp_ChannelChange_VariableInit();
                    MApp_TopStateMachine_SetTopState(STATE_TOP_CHANNELCHANGE);

                }
                else
                {
                    //ZUI: MApp_UiMenu_DisplayShortCut(DISP_WIN_CHANNEL_BANNER, TRUE);
                    MApp_ZUI_ACT_StartupOSD(E_OSD_CHANNEL_INFO);
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_BRIEF_CH_INFO);
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_SOURCE_BANNER);
                }

                u8KeyCode = KEY_NULL;
                break;
            case KEY_PC:
                if(UI_INPUT_SOURCE_TYPE != UI_INPUT_SOURCE_RGB)
                {

                    //ZUI: MApp_UiMenu_ExecuteKeyEvent(MIA_EXIT);
                    UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_RGB;
                    MApp_InputSource_ChangeInputSource(); //ZUI: MApp_UiMenuFunc_ChangeInputSource();
                    MApp_ChannelChange_VariableInit();
                    MApp_TopStateMachine_SetTopState(STATE_TOP_ANALOG_SHOW_BANNER);

                }
                else
                {
                  //ZUI: MApp_UiMenu_DisplayShortCut(DISP_WIN_CHANNEL_BANNER, TRUE);
                    MApp_ZUI_ACT_StartupOSD(E_OSD_CHANNEL_INFO);
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_BRIEF_CH_INFO);
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_SOURCE_BANNER);
                }
                u8KeyCode = KEY_NULL;
                break;
        #if (INPUT_YPBPR_VIDEO_COUNT > 0)
            case KEY_COMPONENT:
                if(UI_INPUT_SOURCE_TYPE != UI_INPUT_SOURCE_COMPONENT)
                {

                    //ZUI: MApp_UiMenu_ExecuteKeyEvent(MIA_EXIT);
                    UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_COMPONENT;
                    MApp_InputSource_ChangeInputSource(); //ZUI: MApp_UiMenuFunc_ChangeInputSource();
                    MApp_ChannelChange_VariableInit();
                    MApp_TopStateMachine_SetTopState(STATE_TOP_ANALOG_SHOW_BANNER);

                }
                else
                {
                    //ZUI: MApp_UiMenu_DisplayShortCut(DISP_WIN_CHANNEL_BANNER, TRUE);
                    MApp_ZUI_ACT_StartupOSD(E_OSD_CHANNEL_INFO);
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_BRIEF_CH_INFO);
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_SOURCE_BANNER);
                }
                u8KeyCode = KEY_NULL;
                break;
        #endif
        #if (INPUT_HDMI_VIDEO_COUNT > 0)
             case KEY_HDMI:
                if(UI_INPUT_SOURCE_TYPE != UI_INPUT_SOURCE_HDMI)
                {
                    //ZUI: MApp_UiMenu_ExecuteKeyEvent(MIA_EXIT);
                    UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_HDMI;
                    MApp_InputSource_ChangeInputSource(); //ZUI: MApp_UiMenuFunc_ChangeInputSource();
                    MApp_ChannelChange_VariableInit();
                    MApp_TopStateMachine_SetTopState(STATE_TOP_ANALOG_SHOW_BANNER);
                }
                else
            #if (INPUT_HDMI_VIDEO_COUNT >= 2)
                {
                    //ZUI: MApp_UiMenu_ExecuteKeyEvent(MIA_EXIT);
                    UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_HDMI2;
                    MApp_InputSource_ChangeInputSource(); //ZUI: MApp_UiMenuFunc_ChangeInputSource();
                    MApp_ChannelChange_VariableInit();
                    MApp_TopStateMachine_SetTopState(STATE_TOP_ANALOG_SHOW_BANNER);
                }
            #else
                {
                   //ZUI: MApp_UiMenu_DisplayShortCut(DISP_WIN_CHANNEL_BANNER, TRUE);
                    MApp_ZUI_ACT_StartupOSD(E_OSD_CHANNEL_INFO);
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_BRIEF_CH_INFO);
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_SOURCE_BANNER);
                }
            #endif
                u8KeyCode = KEY_NULL;
                break;
        #endif
        #if (INPUT_SCART_VIDEO_COUNT > 0)
             case KEY_SCART:
                if(UI_INPUT_SOURCE_TYPE != UI_INPUT_SOURCE_SCART)
                {
                  //ZUI: MApp_UiMenu_ExecuteKeyEvent(MIA_EXIT);
                  UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_SCART;
                  MApp_InputSource_ChangeInputSource(); //ZUI: MApp_UiMenuFunc_ChangeInputSource();
                  MApp_ChannelChange_VariableInit();
                  MApp_TopStateMachine_SetTopState(STATE_TOP_ANALOG_SHOW_BANNER);

                }
                else
                {
                  //ZUI: MApp_UiMenu_DisplayShortCut(DISP_WIN_CHANNEL_BANNER, TRUE);
                    MApp_ZUI_ACT_StartupOSD(E_OSD_CHANNEL_INFO);
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_BRIEF_CH_INFO);
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_SOURCE_BANNER);
                }
                u8KeyCode = KEY_NULL;
                break;


        #endif
        #if (INPUT_AV_VIDEO_COUNT > 0)
             case KEY_AV:
                if(UI_INPUT_SOURCE_TYPE != UI_INPUT_SOURCE_AV)
                {

                    //ZUI: MApp_UiMenu_ExecuteKeyEvent(MIA_EXIT);
                    UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_AV;
                    MApp_InputSource_ChangeInputSource(); //ZUI: MApp_UiMenuFunc_ChangeInputSource();
                    MApp_ChannelChange_VariableInit();
                    MApp_TopStateMachine_SetTopState(STATE_TOP_ANALOG_SHOW_BANNER);

                }
                else
                {
                    //ZUI: MApp_UiMenu_DisplayShortCut(DISP_WIN_CHANNEL_BANNER, TRUE);
                    MApp_ZUI_ACT_StartupOSD(E_OSD_CHANNEL_INFO);
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_BRIEF_CH_INFO);
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_SOURCE_BANNER);
                }
                u8KeyCode = KEY_NULL;
                break;
         #endif
         #if (INPUT_SV_VIDEO_COUNT > 0)

             case KEY_SV:
                if(UI_INPUT_SOURCE_TYPE != UI_INPUT_SOURCE_SVIDEO)
                {

                    //ZUI: MApp_UiMenu_ExecuteKeyEvent(MIA_EXIT);
                    UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_SVIDEO;
                    MApp_InputSource_ChangeInputSource(); //ZUI: MApp_UiMenuFunc_ChangeInputSource();
                    MApp_ChannelChange_VariableInit();
                    MApp_TopStateMachine_SetTopState(STATE_TOP_ANALOG_SHOW_BANNER);

                }
                else
                {
                  //ZUI: MApp_UiMenu_DisplayShortCut(DISP_WIN_CHANNEL_BANNER, TRUE);
                    MApp_ZUI_ACT_StartupOSD(E_OSD_CHANNEL_INFO);
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_BRIEF_CH_INFO);
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_SOURCE_BANNER);
                }
                u8KeyCode = KEY_NULL;
                break;
        #endif
        // Use Green key as TV hotkey tempory for testing
        // Will change to XX TV key when key map ready
         case KEY_TV_INPUT:
         //case KEY_GREEN: //MStar Tempory for TV KEY
             /*/ZUI_TODO: if(enCurTVWin != DISP_WIN_NONEOSD)
                MApp_AnalogInputs_DeleteWin();*/

            enTVState = STATE_TV_INIT;
            enTVRetVal = EXIT_GOTO_MENU;
            //ZUI_TODO: enUiMainMenuState = STATE_UIMENU_WAIT;
            //ZUI: enMenuFlowState = FS_WAIT_MENU;

            break;

      //For Sleep Timer
        case KEY_SLEEP:
            if(MApp_ZUI_GetActiveOSD()!=E_OSD_HOTKEY_OPTION) //ZUI: enCurTVWin != DISP_WIN_HKEY_SLEEP) // only display current setting to Hotkey window
            {
                MApp_AnalogInputs_DeleteWin();
                MApp_ZUI_ACT_StartupOSD(E_OSD_HOTKEY_OPTION);
            }
            else
            {
                MApp_TV_ProcessHotkeyOptionKey(u8KeyCode);
            }
            MApp_AnalogInputs_ResetTimer();
            u8KeyCode = KEY_NULL;
            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_SLEEP_HOTKEY);
            break;

        case KEY_NULL:
            MApp_AnalogInputs_MonitorWindows();

            /*/2008/3/10: refine CI/MMI flow to independent MMI state...
#if ENABLE_CI
            if ( u8KeyCode == KEY_MMI )
            {
                ANALOGINPUTS_DBINFO(printf("Key MMI\n"));
                enAnalogInputsState = STATE_ANALOGINPUTS_INIT;
                enAnalogInputsRetVal =EXIT_GOTO_MMI;
                u8KeyCode = KEY_NULL;
            }
#endif
            */

            break;



        case KEY_PICTURE:
//            if((!MApp_AnalogInputs_FunctionNotAvailableCheck())&&MApp_AnalogInputs_IsHotkeyWinAvailable())
            {
                if(MApp_ZUI_GetActiveOSD()!=E_OSD_HOTKEY_OPTION) //ZUI: enCurTVWin != DISP_WIN_HKEY_PICTURE) // only display current setting to Hotkey window
                {
                    MApp_AnalogInputs_DeleteWin();
                    //ZUI: enCurTVWin = DISP_WIN_HKEY_PICTURE;
                    //ZUI: enAnalogInputsState = STATE_ANALOGINPUTS_INIT;
                    //ZUI: enAnalogInputsRetVal = EXIT_GOTO_MENU;
                    MApp_ZUI_ACT_StartupOSD(E_OSD_HOTKEY_OPTION);
                    //ZUI: enUiMainMenuState = STATE_UIMENU_WAIT;
                    //ZUI: MApp_UiMenu_ExecuteKeyEvent(MIA_PICTURE_MODE);
                }

                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_PICTURE_HOTKEY);
                MApp_TV_ProcessHotkeyOptionKey(u8KeyCode);

                MApp_AnalogInputs_ResetTimer();
            }
            u32AnalogInputsModeWinTimer = msAPI_Timer_GetTime0();
            u8KeyCode = KEY_NULL;
            break;

        case KEY_AUDIO:
//            if ((!MApp_AnalogInputs_FunctionNotAvailableCheck()) && MApp_AnalogInputs_IsHotkeyWinAvailable())
            {
                if (MApp_ZUI_GetActiveOSD()!=E_OSD_HOTKEY_OPTION) //ZUI: enCurTVWin != DISP_WIN_HKEY_AUDIO) // only display current setting to Hotkey window
                {
                    MApp_AnalogInputs_DeleteWin();
                    //ZUI: enCurTVWin = DISP_WIN_HKEY_AUDIO;
                    //ZUI: enAnalogInputsState = STATE_ANALOGINPUTS_INIT;
                    //ZUI: enAnalogInputsRetVal = EXIT_GOTO_MENU;
                    MApp_ZUI_ACT_StartupOSD(E_OSD_HOTKEY_OPTION);
                    //ZUI: enUiMainMenuState = STATE_UIMENU_WAIT;
                    //ZUI: MApp_UiMenu_ExecuteKeyEvent(MIA_AUDIO_MODE);

                }
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_AUDIO_HOTKEY);
                MApp_TV_ProcessHotkeyOptionKey(u8KeyCode);

                MApp_AnalogInputs_ResetTimer();
            }

            u8KeyCode = KEY_NULL;
            break;

        case KEY_FREEZE:
//            if ((!MApp_AnalogInputs_FunctionNotAvailableCheck()) && MApp_AnalogInputs_IsHotkeyWinAvailable())
            {
                if (MApp_ZUI_GetActiveOSD()!=E_OSD_HOTKEY_OPTION) //ZUI: if (enCurTVWin != DISP_WIN_HKEY_FREEZE) // only display current setting to Hotkey window
                {
                    MApp_AnalogInputs_DeleteWin();
                    //ZUI: enCurTVWin = DISP_WIN_HKEY_FREEZE;
                    //ZUI: enAnalogInputsState = STATE_ANALOGINPUTS_INIT;
                    //ZUI: enAnalogInputsRetVal = EXIT_GOTO_MENU;
                    MApp_ZUI_ACT_StartupOSD(E_OSD_HOTKEY_OPTION);
                    //ZUI: enUiMainMenuState = STATE_UIMENU_WAIT;
                    //ZUI: MApp_UiMenu_ExecuteKeyEvent(MIA_FREEZE);

                }
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_FREEZE_HOTKEY);
                MApp_TV_ProcessHotkeyOptionKey(u8KeyCode);

                MApp_AnalogInputs_ResetTimer();
            }

            u8KeyCode = KEY_NULL;
            break;

        case KEY_ZOOM:
        case DSC_KEY_ARC4X3://add DiscreteIR
        case DSC_KEY_ARC16X9:
        case DSC_KEY_ARCZOOM:
            //temporarily force system to display ZOOM window
            //if(MApp_AnalogInputs_IsHotkeyWinAvailable())
            if(1)
            {
                if(MApp_ZUI_GetActiveOSD()!=E_OSD_HOTKEY_OPTION) //ZUI: enCurTVWin != DISP_WIN_HKEY_ZOOM) // only display current setting to Hotkey window
                {
                    MApp_AnalogInputs_DeleteWin();
                    //ZUI: enCurTVWin = DISP_WIN_HKEY_ZOOM;
                    //ZUI: enAnalogInputsState = STATE_ANALOGINPUTS_INIT;
                    //ZUI: enAnalogInputsRetVal = EXIT_GOTO_MENU;
                    MApp_ZUI_ACT_StartupOSD(E_OSD_HOTKEY_OPTION);
                    //ZUI: enUiMainMenuState = STATE_UIMENU_WAIT;
                    //ZUI: MApp_UiMenu_ExecuteKeyEvent(MApp_GetAspectMenuAction(u8KeyCode));

                }
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_SCALE_HOTKEY);
                MApp_TV_ProcessHotkeyOptionKey(u8KeyCode);

                MApp_AnalogInputs_ResetTimer();
            }

            u8KeyCode = KEY_NULL;
            break;

        case KEY_INFO:
        case KEY_SELECT:
            //ZUI: if (MApp_ZUI_GetActiveOSD()==E_OSD_CHANNEL_INFO) //ZUI:  enCurTVWin == DISP_WIN_CHANNEL_BANNER )
            //ZUI: {
            //ZUI:     MApp_UiMenu_ExecuteKeyEvent(MIA_EXIT);
            //ZUI: }
            //ZUI: else
            {
                MApp_AnalogInputs_DeleteWin();

                //ZUI: enAnalogInputsState = STATE_ANALOGINPUTS_INIT;
                //ZUI: enAnalogInputsRetVal = EXIT_GOTO_MENU;
                //ZUI: enUiMainMenuState = STATE_UIMENU_WAIT;
                //ZUI: MApp_UiMenu_ExecuteKeyEvent(MIA_PROGRAM_BRIEF_INFO);
                MApp_ZUI_ACT_StartupOSD(E_OSD_CHANNEL_INFO);
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_BRIEF_CH_INFO);
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_SOURCE_BANNER);

                MApp_AnalogInputs_ResetTimer();
            }

            u8KeyCode = KEY_NULL;
            break;

        /*/ZUI_TODO:
        case KEY_BRIGHTNESS_PLUS:
        case KEY_BRIGHTNESS_MINUS:
            if(MApp_ZUI_GetActiveOSD()!=E_OSD_HOTKEY_OPTION) //ZUI: enCurTVWin != DISP_WIN_HKEY_BRIGHTNESS)
            {
                MApp_AnalogInputs_DeleteWin();
                enAnalogInputsState = STATE_ANALOGINPUTS_INIT;
                enAnalogInputsRetVal = EXIT_GOTO_MENU;
                //ZUI_TODO: enUiMainMenuState = STATE_UIMENU_WAIT;
                //enMenuFlowState = FS_MAIN_MENU;
                //ZUI: enCurTVWin = DISP_WIN_HKEY_BRIGHTNESS;
                //ZUI_TODO: MApp_UiMenu_ExecuteKeyEvent(MIA_BRIGHTNESS);
            }
            else
            {
                if(u8KeyCode==KEY_BRIGHTNESS_PLUS)
                {
                    //ZUI_TODO: MApp_UiMenu_ExecuteKeyEvent(MIA_INCVALUE);
                    //ZUI_TODO: MApp_UiMenu_ExecuteKeyEvent(MIA_NEXTITEM);
                }
                else
                {
                    //ZUI_TODO: MApp_UiMenu_ExecuteKeyEvent(MIA_DECVALUE);
                    //ZUI_TODO: MApp_UiMenu_ExecuteKeyEvent(MIA_PREVITEM);
                }
            }
            MApp_AnalogInputs_ResetTimer();
            u8KeyCode = KEY_NULL;
            break;*/

        case KEY_MTS:
        case KEY_EPG:
        case KEY_CHANNEL_FAV_LIST:
        case KEY_CHANNEL_RETURN:
            //ZUI: #if SHOW_NOT_AVAILABLE_WARNING_MESSAGE
            //ZUI: MApp_UiMenu_Show_Warning_Message_Dialog(MENU_FUNCTION_NOT_AVAILABLE_MSG);
            MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_FUNC_NOT_AVAIL_MSGBOX);
            //ZUI: #endif
            u8KeyCode = KEY_NULL;
            break;
        case KEY_CHANNEL_PLUS:
        case KEY_CHANNEL_MINUS:
            /*/ZUI: if ( enCurTVWin != DISP_WIN_NONEOSD )
                MApp_AnalogInputs_DeleteWin();*/

            UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ATV;
            MApp_InputSource_ChangeInputSource(); //ZUI: MApp_UiMenuFunc_ChangeInputSource();

            enTVState = STATE_TV_INIT;
            enTVRetVal = EXIT_GOTO_CHANNELCHANGE;
            //ZUI: enMenuFlowState = FS_WAIT_MENU;

            //u8KeyCode = KEY_NULL;
            break;

#if ENABLE_TTX
        case KEY_CLOCK:
            if (msAPI_TTX_CheckTTXSignal()==TRUE && msAPI_TTX_CheckTTXClockSignal())
            {
                MApp_TTX_TeletextCommand(TTX_CLOCK);
                u8KeyCode = KEY_NULL;
                g_u32MonitorTTXClockTimer = msAPI_Timer_GetTime0();
            }
            if (u8KeyCode != KEY_NULL)
                u8KeyCode = KEY_NULL;

            break;
#endif

        case KEY_TTX:
            if (IsVgaInUse() || IsHDMIInUse())
            {
                //ZUI: #if SHOW_NOT_AVAILABLE_WARNING_MESSAGE
                //ZUI:MApp_UiMenu_Show_Warning_Message_Dialog(MENU_FUNCTION_NOT_AVAILABLE_MSG);
                MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_FUNC_NOT_AVAIL_MSGBOX);
                //ZUI: #endif
            }
            else
            {
#if ENABLE_TTX
                if ( TRUE == msAPI_TTX_CheckTTXSignal() )
                {
                    MApp_TTX_TeletextCommand(TTX_TEXT);
                }
                else
#endif
                {

                    MApp_AnalogInputs_DeleteWin();
                    //ZUI: enAnalogInputsState = STATE_ANALOGINPUTS_INIT;
                    //ZUI: enAnalogInputsRetVal = EXIT_GOTO_MENU;
                    //ZUI: enUiMainMenuState = STATE_UIMENU_WAIT;

                    //ZUI: enMenuFlowState=FS_WAIT_MENU;
                    //ZUI: enCurTVWin=DISP_WIN_HKEY_PICTURE;
                    //ZUI: g_u8MenuPageIndex = MENU_NO_TTX_MSG;
                    //ZUI: g_u8MenuMainItemIndex = 0;
                    //ZUI: g_u8MsgPageIndex= g_u8MenuPageIndex;
                    //ZUI: MApp_UiMenu_ShowHotkeyMenu();
                    MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_NO_TELETEXT_MSGBOX);
                }
            }
            u8KeyCode = KEY_NULL;
            break;


        case KEY_SUBTITLE:
#if ENABLE_TTX
            if(MApp_TTX_GetSubtitlesAvailable())
            {
                //The initial state enter subtitle page mode
                U16 magPage, subPage;

                SubtitlePageIndex = 0;
                msAPI_TTX_GetSubtitlePage( SubtitlePageIndex, &magPage, &subPage);
                MApp_TTX_SetSubtitlePage(magPage, subPage);
                MApp_TTX_TeletextCommand(TTX_SUBTITLE_TTX_ON);
            }
            else
            {
                MApp_AnalogInputs_DeleteWin();
                /*/ZUI:
                enAnalogInputsState = STATE_ANALOGINPUTS_INIT;
                enAnalogInputsRetVal = EXIT_ANALOGINPUTS_TRAN_MENU;
                enUiMainMenuState = STATE_UIMENU_WAIT;

                enMenuFlowState=FS_WAIT_MENU;
                enCurTVWin=DISP_WIN_HKEY_PICTURE;
                g_u8MenuPageIndex = MENU_NO_TTX_SUBTITLE_MSG;
                g_u8MenuMainItemIndex = 0;
                g_u8MsgPageIndex= g_u8MenuPageIndex;
                MApp_UiMenu_ShowHotkeyMenu();
                */
                MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_NO_TTX_SUBTITLE_MSGBOX);
            }
#endif
            u8KeyCode = KEY_NULL;
            break;

            /*/2008/3/10: refine CI/MMI flow to independent MMI state...
    #if ENABLE_CI
        case KEY_MMI:

            enAnalogInputsState = STATE_ANALOGINPUTS_INIT;
            enAnalogInputsRetVal =EXIT_GOTO_MMI;
            u8KeyCode = KEY_NULL;
            ANALOGINPUTS_DBINFO(printf("RETURN A IDLE GOTO MMI\n"));
            break;
    #endif
            */

#if ENABLE_DMP
        case KEY_RECORD:
        {
            U8 u8Filename[FILE_INFO_LONG_FILENAME_SIZE];

            if(MApp_MPlayer_GenCaptureFileName(u8Filename, FILE_INFO_LONG_FILENAME_SIZE) ==
               E_MPLAYER_RET_OK)
            {
                //MApp_MPlayer_CaptureVideo(u8Filename);
            }
            u8KeyCode = KEY_NULL;
            break;
        }
#endif

#if (BRAZIL_CC == 1) && (CC_ATV_TEST == 1)
        case KEY_YELLOW:
            printf("received yellow key....\n");
            u8KeyCode = KEY_NULL;
            u8TestCC = 1;
            break;

        case KEY_BLUE:
            printf("received blue key....\n");
            u8TestCC = 2;
            u8KeyCode = KEY_NULL;
            break;
#endif

           default:
            u8KeyCode = KEY_NULL;
            break;
    }

    // SH@ CC test
#if (BRAZIL_CC == 1) && (CC_ATV_TEST == 1)
    if(u8TestCC == 1)
    {
        enTVRetVal = EXIT_GOTO_CLOSEDCAPTION;
    }
    else if(u8TestCC == 2)
    {
        u8TestCC = 0;
        MApp_CC_StopParser();
        enTVRetVal = EXIT_GOTO_MENU;
        u8KeyCode = KEY_NULL;
    }
#endif

}

//*************************************************************************
//Function name:    MApp_AnalogInputs
//Passing parameter:    none
//Return parameter:
//Description:      Analog idle mode exit and go to menu state
//*************************************************************************
/* unused
void MApp_AnalogInputs_ExitAndGotoMenuState(void)
{
    enAnalogInputsState = STATE_ANALOGINPUTS_INIT;
    //ZUI_TODO: enUiMainMenuState = STATE_UIMENU_WAIT;
    enMenuFlowState = FS_WAIT_MENU;
}*/

//*************************************************************************
//Function name:    MApp_AnalogInputs
//Passing parameter:    none
//Return parameter:
//Description:      Analog idle mode state machine
//*************************************************************************
EN_RET MApp_AnalogInputs(void)
{
    enAnalogInputsRetVal = EXIT_NULL;
    switch(enAnalogInputsState)
    {
        case STATE_ANALOGINPUTS_INIT:
            MApp_AnalogInputs_Init();
            break;

        case STATE_ANALOGINPUTS_WAIT:
#if ENABLE_TTX
            if(MApp_TTX_IsTeletextOn()==TRUE)
            {
                MApp_AnalogInputs_TTX_ProcessUserInput();
            }
            else
#endif
            {

                if ( u8KeyCode == KEY_NULL )
                {
#if ENABLE_CI
                    if (msAPI_CI_MMICheckEvent())
                    {
                        enAnalogInputsState = STATE_ANALOGINPUTS_INIT;
                        enAnalogInputsRetVal = EXIT_GOTO_MMI;
                        break;
                    }
#endif
                }

#if ENABLE_DMP
                if(IsStorageInUse())
                {
                    enAnalogInputsRetVal = EXIT_ANALOGINPUTS_TRAN_MEDIAPLAYER;
                    u8KeyCode = KEY_NULL;

                    break;
                }
#endif

                MApp_AnalogInputs_ProcessUserInput();
            }
            break;

        default:
            break;
    }

    return enAnalogInputsRetVal;
}
#endif
void MApp_AnalogInputs_ResetTimer(SCALER_WIN eWindow)
{
    u32AnalogInputsModeWinTimer[eWindow] = msAPI_Timer_GetTime0();
}

void MApp_Analog_NoSignal_ResetCount(SCALER_WIN eWindow)
{
   su8NoSignalDisplayCNT[eWindow] = DELAY_4SEC;
}


#undef _MAPP_ANALOGINPUTS_C

