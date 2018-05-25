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
// have read, understood, and agree, To be bound by below terms ("Terms") and to
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
#define MAPP_ZUI_ACTFMRADIO_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal

#include "Board.h"

#if ENABLE_FM_RADIO

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "datatype.h"
#include "MsCommon.h"

// Common Definition
#include "MApp_GlobalSettingSt.h"

#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_ACTmainpage.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_ZUI_ACTepg.h"
#include "MApp_ZUI_ACTinputsource.h"
#include "OSDcp_String_EnumIndex.h"
#include "OSDcp_Bitmap_EnumIndex.h"
#include "ZUI_exefunc.h"
#include "MApp_GlobalFunction.h"
#include "MApp_ZUI_ACTcoexistWin.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_APIcomponent.h"
#include "MApp_ZUI_APIalphatables.h"
#include "MApp_ZUI_APIstyletables.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_TV.h"
#include "MApp_BlockSys.h"
#include "MApp_ZUI_ACTmsgbox.h"
#include "MApp_ChannelChange.h"
#ifndef ATSC_SYSTEM
#include "MApp_EpgTimer.h"
#include "MApp_UiPvr.h"
#endif
#include "drvUART.h"
#include "msAPI_Memory.h"
#include "msAPI_OCP.h"
#include "msAPI_MSDCtrl.h"
#include "msAPI_FCtrl.h"
#include "MApp_MassStorage.h"
#include "apiGOP.h"
#include "MsTypes.h"
#include "MApp_DMP_Main.h"
#include "MApp_ZUI_ACTdmp.h"
#include "MApp_UiMediaPlayer_Define.h"
#include "MApp_UiMenuDef.h"
#include "mapp_videoplayer.h"
#include "MApp_Audio.h"
#include "mapp_music.h"
#if (ENABLE_WMA)
#include "mapp_wma.h"
#endif
#include "msAPI_audio.h"
#include "msAPI_Timer.h"
#include "FSUtil.h"
#include "IOUtil.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "mapp_txt.h"
#include "MApp_CharTable.h"
#include "msAPI_MPEG_Subtitle.h"
#include "Panel.h"
#if ENABLE_DRM
#include "MApp_SaveData.h"
#endif
#include "ZUI_tables_h.inl"
#include "GPIO.h"

#include "mapp_photo.h"

#if ENABLE_PIP
#include "MApp_InputSource.h"
#include "MApp_ChannelChange.h"
#include "drvPQ.h"
#include "apiXC_Hdmi.h"
#include "MApp_PIP.h"
#endif
#include "msAPI_CEC.h"

#include "MApp_IR.h" // jimmy.wang

#if ENABLE_ATSC_TTS
#include "MApp_TTSControlHandler.h"
#include "MApp_TTS_Cus.h"
#endif

#if ENABLE_KEY_TO_SPEECH
#include "MApp_KeyToSpeech.h"
#endif

#include "MApp_ZUI_ACTFMRadio.h"
#include "MApp_Radio.h"
#include "MApp_FMRadio_Main.h"
#include "MApp_FM_Scan.h"
#include "drvPWM.h"

//====================================================================

extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);
extern EN_FM_SCAN_TYPE enFMScanType;

extern EN_FMRADIO_STATE enFMRadioState;
static EN_FMRADIO_STATE _enTargetRadioState;

//====================================================================

#define EditNameArray "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 -:"
#define NumberOfEditNameArray 39
#define DigitsThresholdAfterPoint 10
#define MIN_FREQUENCY 8700
#define MAX_FREQUENCY 10800

//====================================================================

static BOOLEAN bFMBlackLight = TRUE;
static HWND tempHWND = HWND_FMRADIO_LIST_ITEM1;

static U8 _u8FMIdleInputValue = 0;
static U8 _u8FMIdleInputCount = 0;

//static U16 u16InfoPage_CurFreq = 0;

//====================================================================

void u8RollBarModify(U8 u8NameCharNum, BOOL bIncrease)
{
    U8 u8NameIndex;
    U8 u8CurChIdx = MApp_FMRadio_Get_CurChIdx();

    u8NameIndex = stGenSetting.stRadioSetting.astChData[u8CurChIdx].au8ChName[u8NameCharNum-1];

    if(u8NameIndex>=CHAR_0 && u8NameIndex <=CHAR_9)
    {
        u8NameIndex = u8NameIndex - CHAR_0 + 26;
    }
    else if(u8NameIndex>=CHAR_A&& u8NameIndex <= CHAR_Z)
    {
        u8NameIndex = u8NameIndex - CHAR_A;
    }
    else if(u8NameIndex == CHAR_SPACE)//
    {
        u8NameIndex = 36;
    }
    else if(u8NameIndex == CHAR_MINUS)//-
    {
        u8NameIndex = 37;
    }
    else if(u8NameIndex == CHAR_COLON)//:
    {
        u8NameIndex = 38;
    }

    if(bIncrease == TRUE)
    {
        if(u8NameIndex >=  (NumberOfEditNameArray-1) )
        {
            u8NameIndex = 0;
            stGenSetting.stRadioSetting.astChData[u8CurChIdx].au8ChName[u8NameCharNum-1] = EditNameArray[u8NameIndex];
        }
        else
        {
            stGenSetting.stRadioSetting.astChData[u8CurChIdx].au8ChName[u8NameCharNum-1] = EditNameArray[u8NameIndex+1];
        }
    }
    else
    {
        if(u8NameIndex <= 0)
        {
            u8NameIndex = (NumberOfEditNameArray-1);
            stGenSetting.stRadioSetting.astChData[u8CurChIdx].au8ChName[u8NameCharNum-1] = EditNameArray[u8NameIndex];
        }
        else
        {
            stGenSetting.stRadioSetting.astChData[u8CurChIdx].au8ChName[u8NameCharNum-1] = EditNameArray[u8NameIndex-1];
        }
    }
}

HWND MApp_ZUI_ACT_GetHWNDViaIndex(U8 u8Index)
{
    U8 u8Listitem;

    u8Listitem = u8Index % 10;

    switch(u8Listitem)
    {
        case 0:
            return HWND_FMRADIO_LIST_ITEM1;
            break;
        case 1:
            return HWND_FMRADIO_LIST_ITEM2;
            break;
        case 2:
            return HWND_FMRADIO_LIST_ITEM3;
            break;
        case 3:
            return HWND_FMRADIO_LIST_ITEM4;
            break;
        case 4:
            return HWND_FMRADIO_LIST_ITEM5;
            break;
        case 5:
            return HWND_FMRADIO_LIST_ITEM6;
            break;
        case 6:
            return HWND_FMRADIO_LIST_ITEM7;
            break;
        case 7:
            return HWND_FMRADIO_LIST_ITEM8;
            break;
        case 8:
            return HWND_FMRADIO_LIST_ITEM9;
            break;
        case 9:
            return HWND_FMRADIO_LIST_ITEM10;
            break;

        default:
            return HWND_FMRADIO_LIST_ITEM1;
            break;
    }

    return HWND_FMRADIO_LIST_ITEM1;
}

void MApp_ZUI_ACT_FMRadio_ResetListItemFocus(U8 u8ChIdx)
{
    HWND eFocusItem = MApp_ZUI_ACT_GetHWNDViaIndex( u8ChIdx );

    MApp_ZUI_API_SetFocus(eFocusItem);
}

void MApp_ZUI_ACT_AppShowFMRadio(void)
{
    HWND wnd;
    E_OSD_ID osd_id = E_OSD_FMRADIO;
    RECT rect;

PRINT_CURRENT_LINE();

    g_GUI_WindowList = GetWindowListOfOsdTable(osd_id);
    g_GUI_WinDrawStyleList = GetWindowStyleOfOsdTable(osd_id);
    g_GUI_WindowPositionList = GetWindowPositionOfOsdTable(osd_id);
#if ZUI_ENABLE_ALPHATABLE
    g_GUI_WinAlphaDataList = GetWindowAlphaDataOfOsdTable(osd_id);
#endif
    HWND_MAX = GetWndMaxOfOsdTable(osd_id);
    OSDPAGE_BLENDING_ENABLE = IsBlendingEnabledOfOsdTable(osd_id);
    OSDPAGE_BLENDING_VALUE = GetBlendingValueOfOsdTable(osd_id);

    if (!_MApp_ZUI_API_AllocateVarData())
    {
        ZUI_DBG_FAIL(printf("[ZUI]ALLOC\n"));
        ABORT();
        return;
    }
    RECT_SET(rect,
        ZUI_FMRADIO_XSTART, ZUI_FMRADIO_YSTART,
        ZUI_FMRADIO_WIDTH, ZUI_FMRADIO_HEIGHT);

    if (!MApp_ZUI_API_InitGDI(&rect))
    {
        ZUI_DBG_FAIL(printf("[ZUI]GDIINIT\n"));
        ABORT();
        return;
    }

    for (wnd = 0; wnd < HWND_MAX; wnd++)
    {
        //printf("create msg: %lu\n", (U32)wnd);
        MApp_ZUI_API_SendMessage(wnd, MSG_CREATE, 0);
    }

    //To show "Loading..." symbol
    printf("OSD IN FMRADIO\n");
    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_FMRADIO_ROOT_TRANSPARENT_BG, SW_SHOW);
    MApp_ZUI_API_ShowWindow(HWND_FMRADIO_TENKEY_CH_NUMBER_PAGE, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_FMRADIO_AUTOTUNE_INFO_PAGE, SW_HIDE);

    MApp_ZUI_ACT_FMRadio_ResetListItemFocus(MApp_FMRadio_Get_CurChIdx());

    //MApp_ZUI_API_SetFocus(HWND_FMRADIO_LIST_ITEM1);
#if 0
    DMP_DBG(printf("show DMP_MSG_TYPE_LOADING\n"););
    if (DMP_STATE_UI != MApp_DMP_GetDMPStat())
    {
       _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_LOADING);
    }
#endif

    //Do not show transition effect to avoid a small block show up before entering MM main page.
    MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_PAGE_EXIT, E_ZUI_STATE_RUNNING);
}

void MApp_ZUI_ACT_TerminateFMRadio(void)
{
    ZUI_MSG(printf("[]term:FMRadio player\n");)

    enFMRadioState= _enTargetRadioState;

//  MApp_FuncExec_InputSourcePage(EN_FUNC_INPUTSOURCE_SAVE_SYS_SETTING, NULL, NULL);
}

BOOLEAN MApp_ZUI_ACT_HandleTenKey(VIRTUAL_KEY_CODE key)
{
    if(MApp_ZUI_API_GetFocus() !=HWND_FMRADIO_TENKEY_CH_NUMBER_PAGE)
    {
        MApp_ZUI_API_ShowWindow(HWND_FMRADIO_TENKEY_CH_NUMBER_PAGE, SW_SHOW);
        tempHWND = MApp_ZUI_API_GetFocus();
        MApp_ZUI_API_SetFocus(HWND_FMRADIO_TENKEY_CH_NUMBER_PAGE);
        _u8FMIdleInputCount = 0;
        _u8FMIdleInputValue = 0;
    }

    U8 u8tempValue = 0;
    u8tempValue = key - VK_NUM_0;

    _u8FMIdleInputValue = (_u8FMIdleInputValue *10)+u8tempValue;

    if(_u8FMIdleInputValue !=0)
        _u8FMIdleInputCount++;


    if((_u8FMIdleInputValue<=30) &&(_u8FMIdleInputCount <=2) )
    {
        MApp_ZUI_ACT_GetFMRadioDynamicText(HWND_FMRADIO_TENKEY_CH_NUMBER_PAGE);
        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_ALL);
        return TRUE;
    }
    else
    {
        MApp_ZUI_API_SetFocus(tempHWND);
        MApp_ZUI_API_ShowWindow(HWND_FMRADIO_TENKEY_CH_NUMBER_PAGE, SW_HIDE);
        _u8FMIdleInputCount = 0;
        _u8FMIdleInputValue = 0;
        return TRUE;
    }

}

BOOLEAN MApp_ZUI_ACT_HandleFMRadioKey(VIRTUAL_KEY_CODE key)
{
    BOOLEAN bRtnResult = FALSE;

    //recover backlight
    //if(MApp_ZUI_API_GetFocus() == HWND_FMRADIO_LIST_PAGE_KEY_INFO_REDKEY)
    if(!bFMBlackLight)
    {
        INV_CTL_On();
        MApi_PNL_SetBackLight(ENABLE);
        bFMBlackLight = TRUE;;
        return TRUE;
    }

    switch(key)
    {
        case VK_NUM_0:
        case VK_NUM_1:
        case VK_NUM_2:
        case VK_NUM_3:
        case VK_NUM_4:
        case VK_NUM_5:
        case VK_NUM_6:
        case VK_NUM_7:
        case VK_NUM_8:
        case VK_NUM_9:
            {
                return MApp_ZUI_ACT_HandleTenKey(key);
            }
            break;

        case VK_CHANNEL_MINUS:
        case VK_CHANNEL_PLUS:// movie program test
            break;

        case VK_VOLUME_PLUS:
            if ( stGenSetting.g_SoundSetting.Volume < MAX_NUM_OF_VOL_LEVEL )
            {
                stGenSetting.g_SoundSetting.Volume+= VOLUME_STEP;
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, stGenSetting.g_SoundSetting.Volume, 0);
#if ENABLE_KEY_TO_SPEECH
                if(!MApp_KeyIsReapeatStatus())
                {
                    MApp_KTS_Say(EN_KTS_VOLUME_UP);
                }
#endif
            }
            printf("stGenSetting.g_SoundSetting.Volume=%u\n", stGenSetting.g_SoundSetting.Volume);
            //msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            bRtnResult = TRUE;
            break;

        case VK_VOLUME_MINUS:
            if ( stGenSetting.g_SoundSetting.Volume > 0 )
            {
                stGenSetting.g_SoundSetting.Volume-= VOLUME_STEP;
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, stGenSetting.g_SoundSetting.Volume, 0);
#if ENABLE_KEY_TO_SPEECH
                if(!MApp_KeyIsReapeatStatus())
                {
                    MApp_KTS_Say(EN_KTS_VOLUME_DOWN);
                }
#endif
            }
            printf("stGenSetting.g_SoundSetting.Volume=%u\n", stGenSetting.g_SoundSetting.Volume);
            //msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            bRtnResult = TRUE;
            break;
			
		case VK_KEYSTONE_PLUS:      //xzm @ 20171227
				stGenSetting.g_SysSetting.KeyStoneValue++;
		      if(stGenSetting.g_SysSetting.KeyStoneValue >= 38)
			  	stGenSetting.g_SysSetting.KeyStoneValue=38;
			  printf("ks2=%d",stGenSetting.g_SysSetting.KeyStoneValue);
			  keystone_correction(stGenSetting.g_SysSetting.KeyStoneValue);
			break;
			
		case VK_KEYSTONE_MINUS:
			 stGenSetting.g_SysSetting.KeyStoneValue--;
			  if(stGenSetting.g_SysSetting.KeyStoneValue <=-38)
			  	stGenSetting.g_SysSetting.KeyStoneValue=-38;

			  printf("ks1=%d",stGenSetting.g_SysSetting.KeyStoneValue);
			  keystone_correction(stGenSetting.g_SysSetting.KeyStoneValue);
			break;
			
        case VK_INPUT_SOURCE:
            MApp_ZUI_ACT_ExecuteFMRadioAction(EN_EXE_SHOW_SOURCE_BANNER);
            return TRUE;
                break;

        case VK_MUTE:
            break;

        case VK_MENU:
            MApp_ZUI_ACT_ExecuteFMRadioAction(EN_EXE_GOTO_MAINMENU);
            return TRUE;

        case VK_EXIT:
            if(bFMStopScan)
            {
                //stop scan from user interrupt, dont change input source
                bFMStopScan = 0;
                return TRUE;
            }
            if(bFMEditName)
            {
                //stop edit ch name from interrupt, dont change input source
                bFMEditName = 0;
                MApp_ZUI_API_SetFocus(HWND_FMRADIO_INFOMATION_EDIT_NAME);
                return TRUE;
            }
            MApp_ZUI_ACT_ExecuteFMRadioAction(EN_EXE_CLOSE_CURRENT_OSD);
            enFMRadioState = FMRADIO_STATE_GOTO_TVSOURCE;
            return TRUE;

        case VK_POWER:
            MApp_ZUI_ACT_ExecuteFMRadioAction(EN_EXE_POWEROFF);
            return TRUE;
        /*
        case VK_BLUE:
            _MApp_ACTdmp_ShowAlertWin(DMP_MSG_TYPE_INVALID_OPERATION);
            return TRUE;
        */
        case VK_RED:
            enFMScanType = FM_SCAN_TYPE_ALL;
            MApp_ZUI_API_ShowWindow(HWND_FMRADIO_AUTOTUNE_INFO_PAGE, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_FMRADIO_AUTOTUNE_INFO_PROGRESS_BAR);
            MApp_FM_Scan_Init();
            bRtnResult = TRUE;
            break;

        case VK_GREEN:
            MApi_PNL_SetBackLight(DISABLE);
            INV_CTL_Off();
            bFMBlackLight = FALSE;
            bRtnResult = TRUE;
            break;

        case VK_BLUE:
            INV_CTL_On();
            MApi_PNL_SetBackLight(ENABLE);
            bRtnResult = TRUE;
            break;

        case VK_LEFT:
            break;
        case VK_RIGHT:
            break;
        case VK_SELECT:
            {
                bRtnResult = TRUE;

                switch(MApp_ZUI_API_GetFocus())
                {
                    case HWND_FMRADIO_LIST_ITEM1:
                    case HWND_FMRADIO_LIST_ITEM2:
                    case HWND_FMRADIO_LIST_ITEM3:
                    case HWND_FMRADIO_LIST_ITEM4:
                    case HWND_FMRADIO_LIST_ITEM5:
                    case HWND_FMRADIO_LIST_ITEM6:
                    case HWND_FMRADIO_LIST_ITEM7:
                    case HWND_FMRADIO_LIST_ITEM8:
                    case HWND_FMRADIO_LIST_ITEM9:
                    case HWND_FMRADIO_LIST_ITEM10:
                        MApp_FMRadio_ChgCurCh( MApp_FMRadio_Get_CurChIdx() );
                        break;

                    //----tenkey-----
                    case HWND_FMRADIO_TENKEY_CH_NUMBER_PAGE:
                        MApp_FMRadio_Set_CurChIdx( _u8FMIdleInputValue );

                        MApp_ZUI_API_SetFocus(MApp_ZUI_ACT_GetHWNDViaIndex(_u8FMIdleInputValue));
                        MApp_ZUI_API_ShowWindow(HWND_FMRADIO_TENKEY_CH_NUMBER_PAGE, SW_HIDE);
                        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_ALL);

                        MApp_FMRadio_ChgCurCh( MApp_FMRadio_Get_CurChIdx() );
                        break;

                    default:
                        bRtnResult = FALSE;
                        break;

                }
            }
            break;

        case VK_UP:
            {
                bRtnResult = TRUE;
                switch(MApp_ZUI_API_GetFocus())
                {
                    case HWND_FMRADIO_INFOMATION_EDIT_NAME_VALUE1:
                        u8RollBarModify(1,TRUE);
                        break;
                    case HWND_FMRADIO_INFOMATION_EDIT_NAME_VALUE2:
                        u8RollBarModify(2,TRUE);
                        break;
                    case HWND_FMRADIO_INFOMATION_EDIT_NAME_VALUE3:
                        u8RollBarModify(3,TRUE);
                        break;
                    case HWND_FMRADIO_INFOMATION_EDIT_NAME_VALUE4:
                        u8RollBarModify(4,TRUE);
                        break;
                    case HWND_FMRADIO_INFOMATION_EDIT_NAME_VALUE5:
                        u8RollBarModify(5,TRUE);
                        break;
                    case HWND_FMRADIO_INFOMATION_EDIT_NAME_VALUE6:
                        u8RollBarModify(6,TRUE);
                        break;

                    //////////////////////////////////////////////////////
                    case HWND_FMRADIO_INFOMATION_FREQUENCY_VALUE:
                        enFMScanType = FM_SCAN_TYPE_ONECH;
                        MApp_FM_Scan_Init();
                        break;

                    default:
                        bRtnResult = FALSE;
                        break;

                }
            }

            if( bRtnResult )
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_ALL);

            break;

        case VK_DOWN:
            {
                bRtnResult = TRUE;
                //printf("MApp_ZUI_API_GetFocus()=%u\n", MApp_ZUI_API_GetFocus());
                switch(MApp_ZUI_API_GetFocus())
                {
                    case HWND_FMRADIO_INFOMATION_EDIT_NAME_VALUE1:
                        u8RollBarModify(1,FALSE);
                        break;
                    case HWND_FMRADIO_INFOMATION_EDIT_NAME_VALUE2:
                        u8RollBarModify(2,FALSE);
                        break;
                    case HWND_FMRADIO_INFOMATION_EDIT_NAME_VALUE3:
                        u8RollBarModify(3,FALSE);
                        break;
                    case HWND_FMRADIO_INFOMATION_EDIT_NAME_VALUE4:
                        u8RollBarModify(4,FALSE);
                        break;
                    case HWND_FMRADIO_INFOMATION_EDIT_NAME_VALUE5:
                        u8RollBarModify(5,FALSE);
                        break;
                    case HWND_FMRADIO_INFOMATION_EDIT_NAME_VALUE6:
                        u8RollBarModify(6,FALSE);
                        break;

                    default:
                        bRtnResult = FALSE;
                        break;

                }
            }

            if( bRtnResult )
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_ALL);
            break;

        default:
            return FALSE;
            break;
    }

    return bRtnResult;
}

BOOLEAN MApp_ZUI_ACT_ExecuteFMRadioAction(U16 act)
{
    switch(act)
    {
        case EN_EXE_CLOSE_CURRENT_OSD:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetRadioState = FMRADIO_STATE_CLEAN_UP;
            return TRUE;
            break;

        case EN_EXE_GOTO_RADIO_INFO_PAGE:

            // Change ch to current index
            //if( g_Radio_u8CurChIdx != )
            {
                MApp_FMRadio_ChgCurCh(g_Radio_u8CurChIdx);
            }

            tempHWND = MApp_ZUI_API_GetFocus();
            MApp_ZUI_API_SetFocus(HWND_FMRADIO_INFOMATION_FREQUENCY);
            return TRUE;
            break;

        case EN_EXE_EXIT_RADIO_INFO_PAGE:
            MApp_ZUI_API_SetFocus(tempHWND);
            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_ALL);
            return TRUE;
            break;

        case EN_EXE_INC_RADIO_LIST_CHANNEL_NUMBER:
            g_Radio_u8CurChIdx = (g_Radio_u8CurChIdx+1) % RADIO_CH_NUM;

            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_ALL);
            return TRUE;
            break;

        case EN_EXE_DEC_RADIO_LIST_CHANNEL_NUMBER:

            if( g_Radio_u8CurChIdx == 0 )
                g_Radio_u8CurChIdx = RADIO_CH_NUM - 1;
            else
                g_Radio_u8CurChIdx = g_Radio_u8CurChIdx - 1;

            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_ALL);
            return TRUE;
            break;

        case EN_EXE_GOTO_RADIO_FREQUENCY_SET:
            MApp_ZUI_API_SetFocus(HWND_FMRADIO_INFOMATION_FREQUENCY_VALUE);
            return TRUE;
            break;

        case EN_EXE_EXIT_RADIO_FREQUENCY_SET:

            // Copy cur data to DB
            g_Radio_stCurChData.u16Freq_x10K = g_CurFMFreq;

            MApp_FMRadio_SaveCh(g_Radio_u8CurChIdx, &g_Radio_stCurChData);

            MApp_ZUI_API_SetFocus(HWND_FMRADIO_INFOMATION_FREQUENCY);
            return TRUE;
            break;

        case EN_EXE_INC_RADIO_FREQUENCY:
            {
                U16 u16CurFreq_x10K = g_Radio_stCurChData.u16Freq_x10K;

                u16CurFreq_x10K += 5;

                if( u16CurFreq_x10K > MAX_FREQUENCY )
                {
                    u16CurFreq_x10K = MAX_FREQUENCY;
                }

                g_Radio_stCurChData.u16Freq_x10K = u16CurFreq_x10K;

                MApp_FMRadio_SetFMFreq(u16CurFreq_x10K);

                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_ALL);
            }
            break;

        case EN_EXE_DEC_RADIO_FREQUENCY:
            {
                U16 u16CurFreq_x10K = g_Radio_stCurChData.u16Freq_x10K;

                u16CurFreq_x10K -= 5;

                if( u16CurFreq_x10K < MIN_FREQUENCY )
                {
                    u16CurFreq_x10K = MIN_FREQUENCY;
                }

                g_Radio_stCurChData.u16Freq_x10K = u16CurFreq_x10K;

                MApp_FMRadio_SetFMFreq(u16CurFreq_x10K);

                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_ALL);
            }
            break;

        case EN_EXE_GOTO_RADIO_EDITNAME_SET:
            bFMEditName = 1;
            MApp_ZUI_API_SetFocus(HWND_FMRADIO_INFOMATION_EDIT_NAME_VALUE1);
            return TRUE;
            break;

        case EN_EXE_EXIT_RADIO_EDITNAME_SET:
            // Copy cur ch data to DB
            MApp_FMRadio_SaveCh(g_Radio_u8CurChIdx, &g_Radio_stCurChData);

            MApp_ZUI_API_SetFocus(HWND_FMRADIO_INFOMATION_EDIT_NAME);
            return TRUE;
            break;

        case EN_EXE_SHOW_SOURCE_BANNER:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetRadioState = FMRADIO_STATE_GOTO_INPUTSOURCE;
            return TRUE;

        case EN_EXE_POWEROFF:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetRadioState = FMRADIO_STATE_GOTO_STANDBY;
            return TRUE;

        case EN_EXE_GOTO_MAINMENU:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            _enTargetRadioState = FMRADIO_STATE_GOTO_MENU;
            return TRUE;

        default:
            break;
    }

    return FALSE;
}

LPTSTR MApp_ZUI_ACT_GetFMRadioDynamicText(HWND hwnd)
{
    memset((void*)CHAR_BUFFER, '\0', 128);
    U16 u16TempID = Empty;
    U8 u8ChannelNumberTens = 0;
    U8 u8NoOfDigit;
    U8 u8StrArr[256];
    U8 *u8TempStr=&u8StrArr[0];

    U16 u16tempFreBeforePoint, u16tempFreAfterPoint;
    LPTSTR str=NULL;

    //get channel page level
    u8ChannelNumberTens = (g_Radio_u8CurChIdx / 10) * 10;

//printf("hwnd=%u\n", hwnd);
//printf("u8ChannelNumberTens=%u\n", u8ChannelNumberTens);

    switch(hwnd)
    {
        //list item
        case HWND_FMRADIO_LIST_ITEM1_CHANNEL_NUMBER:
        case HWND_FMRADIO_LIST_ITEM2_CHANNEL_NUMBER:
        case HWND_FMRADIO_LIST_ITEM3_CHANNEL_NUMBER:
        case HWND_FMRADIO_LIST_ITEM4_CHANNEL_NUMBER:
        case HWND_FMRADIO_LIST_ITEM5_CHANNEL_NUMBER:
        case HWND_FMRADIO_LIST_ITEM6_CHANNEL_NUMBER:
        case HWND_FMRADIO_LIST_ITEM7_CHANNEL_NUMBER:
        case HWND_FMRADIO_LIST_ITEM8_CHANNEL_NUMBER:
        case HWND_FMRADIO_LIST_ITEM9_CHANNEL_NUMBER:
        case HWND_FMRADIO_LIST_ITEM10_CHANNEL_NUMBER:
            switch(hwnd)
            {
                case HWND_FMRADIO_LIST_ITEM1_CHANNEL_NUMBER:
                    u8ChannelNumberTens += 1;
                    break;
                case HWND_FMRADIO_LIST_ITEM2_CHANNEL_NUMBER:
                    u8ChannelNumberTens += 2;
                    break;
                case HWND_FMRADIO_LIST_ITEM3_CHANNEL_NUMBER:
                    u8ChannelNumberTens += 3;
                    break;
                case HWND_FMRADIO_LIST_ITEM4_CHANNEL_NUMBER:
                    u8ChannelNumberTens += 4;
                    break;
                case HWND_FMRADIO_LIST_ITEM5_CHANNEL_NUMBER:
                    u8ChannelNumberTens += 5;
                    break;
                case HWND_FMRADIO_LIST_ITEM6_CHANNEL_NUMBER:
                    u8ChannelNumberTens += 6;
                    break;
                case HWND_FMRADIO_LIST_ITEM7_CHANNEL_NUMBER:
                    u8ChannelNumberTens += 7;
                    break;
                case HWND_FMRADIO_LIST_ITEM8_CHANNEL_NUMBER:
                    u8ChannelNumberTens += 8;
                    break;
                case HWND_FMRADIO_LIST_ITEM9_CHANNEL_NUMBER:
                    u8ChannelNumberTens += 9;
                    break;
                case HWND_FMRADIO_LIST_ITEM10_CHANNEL_NUMBER:
                    u8ChannelNumberTens += 10;
                    break;
            }
            u8NoOfDigit = MApp_GetNoOfDigit(u8ChannelNumberTens);
            MApp_UlongToU8String( u8ChannelNumberTens, u8TempStr, u8NoOfDigit );
            MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8TempStr, strlen((char *)u8TempStr));
            return CHAR_BUFFER;
            break;

        case HWND_FMRADIO_LIST_ITEM1_EDIT_NAME:
        case HWND_FMRADIO_LIST_ITEM2_EDIT_NAME:
        case HWND_FMRADIO_LIST_ITEM3_EDIT_NAME:
        case HWND_FMRADIO_LIST_ITEM4_EDIT_NAME:
        case HWND_FMRADIO_LIST_ITEM5_EDIT_NAME:
        case HWND_FMRADIO_LIST_ITEM6_EDIT_NAME:
        case HWND_FMRADIO_LIST_ITEM7_EDIT_NAME:
        case HWND_FMRADIO_LIST_ITEM8_EDIT_NAME:
        case HWND_FMRADIO_LIST_ITEM9_EDIT_NAME:
        case HWND_FMRADIO_LIST_ITEM10_EDIT_NAME:
            switch(hwnd)
            {
                case HWND_FMRADIO_LIST_ITEM1_EDIT_NAME:
                    break;
                case HWND_FMRADIO_LIST_ITEM2_EDIT_NAME:
                    u8ChannelNumberTens += 1;
                    break;
                case HWND_FMRADIO_LIST_ITEM3_EDIT_NAME:
                    u8ChannelNumberTens += 2;
                    break;
                case HWND_FMRADIO_LIST_ITEM4_EDIT_NAME:
                    u8ChannelNumberTens += 3;
                    break;
                case HWND_FMRADIO_LIST_ITEM5_EDIT_NAME:
                    u8ChannelNumberTens += 4;
                    break;
                case HWND_FMRADIO_LIST_ITEM6_EDIT_NAME:
                    u8ChannelNumberTens += 5;
                    break;
                case HWND_FMRADIO_LIST_ITEM7_EDIT_NAME:
                    u8ChannelNumberTens += 6;
                    break;
                case HWND_FMRADIO_LIST_ITEM8_EDIT_NAME:
                    u8ChannelNumberTens += 7;
                    break;
                case HWND_FMRADIO_LIST_ITEM9_EDIT_NAME:
                    u8ChannelNumberTens += 8;
                    break;
                case HWND_FMRADIO_LIST_ITEM10_EDIT_NAME:
                    u8ChannelNumberTens += 9;
                    break;
            }
            u8TempStr = stGenSetting.stRadioSetting.astChData[u8ChannelNumberTens].au8ChName;
            MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8TempStr, RADIO_CH_NAME_LEN-1);
            return CHAR_BUFFER;
            break;

        case HWND_FMRADIO_LIST_ITEM1_FREQUENCY:
        case HWND_FMRADIO_LIST_ITEM2_FREQUENCY:
        case HWND_FMRADIO_LIST_ITEM3_FREQUENCY:
        case HWND_FMRADIO_LIST_ITEM4_FREQUENCY:
        case HWND_FMRADIO_LIST_ITEM5_FREQUENCY:
        case HWND_FMRADIO_LIST_ITEM6_FREQUENCY:
        case HWND_FMRADIO_LIST_ITEM7_FREQUENCY:
        case HWND_FMRADIO_LIST_ITEM8_FREQUENCY:
        case HWND_FMRADIO_LIST_ITEM9_FREQUENCY:
        case HWND_FMRADIO_LIST_ITEM10_FREQUENCY:
            switch(hwnd)
            {
                case HWND_FMRADIO_LIST_ITEM1_FREQUENCY:
                    break;
                case HWND_FMRADIO_LIST_ITEM2_FREQUENCY:
                    u8ChannelNumberTens += 1;
                    break;
                case HWND_FMRADIO_LIST_ITEM3_FREQUENCY:
                    u8ChannelNumberTens += 2;
                    break;
                case HWND_FMRADIO_LIST_ITEM4_FREQUENCY:
                    u8ChannelNumberTens += 3;
                    break;
                case HWND_FMRADIO_LIST_ITEM5_FREQUENCY:
                    u8ChannelNumberTens += 4;
                    break;
                case HWND_FMRADIO_LIST_ITEM6_FREQUENCY:
                    u8ChannelNumberTens += 5;
                    break;
                case HWND_FMRADIO_LIST_ITEM7_FREQUENCY:
                    u8ChannelNumberTens += 6;
                    break;
                case HWND_FMRADIO_LIST_ITEM8_FREQUENCY:
                    u8ChannelNumberTens += 7;
                    break;
                case HWND_FMRADIO_LIST_ITEM9_FREQUENCY:
                    u8ChannelNumberTens += 8;
                    break;
                case HWND_FMRADIO_LIST_ITEM10_FREQUENCY:
                    u8ChannelNumberTens += 9;
                    break;
            }
            CHAR_BUFFER[0] = 0;
            str = CHAR_BUFFER;

            {
                U16 u16Freq_x10K = stGenSetting.stRadioSetting.astChData[u8ChannelNumberTens].u16Freq_x10K;

                u16tempFreBeforePoint = u16Freq_x10K / 100;
                u16tempFreAfterPoint = u16Freq_x10K % 100;
            }

            //before point bit
            u8NoOfDigit = MApp_GetNoOfDigit( u16tempFreBeforePoint );
            MApp_UlongToU8String( u16tempFreBeforePoint , u8TempStr, u8NoOfDigit );
            MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8TempStr, strlen((char *)u8TempStr));
            //add point
            str += MApp_ZUI_API_Strlen(str);
            *str++ = CHAR_DOT;
            if(u16tempFreAfterPoint<DigitsThresholdAfterPoint)
            {
                *str++ = CHAR_0;
            }
            //after point bit
            u8NoOfDigit = MApp_GetNoOfDigit( u16tempFreAfterPoint );
            MApp_UlongToU8String( u16tempFreAfterPoint , u8TempStr, u8NoOfDigit );
            MApp_ZUI_API_StringBuffU8toU16(str, u8TempStr, strlen((char *)u8TempStr)+1);
            str[strlen((char *)u8TempStr)] = 0;
            return CHAR_BUFFER;
            break;

        case HWND_FMRADIO_INFOMATION_CHANNEL_NUMBER_VALUE:
            u8NoOfDigit = MApp_GetNoOfDigit( MApp_FMRadio_Get_CurChIdx()+1 );
            MApp_UlongToU8String( MApp_FMRadio_Get_CurChIdx()+1, u8TempStr, u8NoOfDigit );
            //MApp_UlongToU8String( MApp_FMRadio_Get_CurChIdx()+1, u8TempStr, 2 );
            MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8TempStr, strlen((char *)u8TempStr));
            return CHAR_BUFFER;
            break;

        case HWND_FMRADIO_INFOMATION_FREQUENCY_VALUE:
            {
                CHAR_BUFFER[0] = 0;
                //U16 u16tempFreBeforePoint, u16tempFreAfterPoint;
                str = CHAR_BUFFER;

                U16 u16Freq_x10K;

                if( MApp_ZUI_API_GetFocus() == HWND_FMRADIO_INFOMATION_FREQUENCY_VALUE ) // Focus on info window
                {
                    u16Freq_x10K = g_CurFMFreq;
                }
                else
                {
                    u16Freq_x10K = stGenSetting.stRadioSetting.astChData[MApp_FMRadio_Get_CurChIdx()].u16Freq_x10K;
                }

                u16tempFreBeforePoint = u16Freq_x10K / 100;
                u16tempFreAfterPoint = u16Freq_x10K % 100;

                //before point bit
                u8NoOfDigit = MApp_GetNoOfDigit( u16tempFreBeforePoint );
                MApp_UlongToU8String( u16tempFreBeforePoint , u8TempStr, u8NoOfDigit );
                MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8TempStr, strlen((char *)u8TempStr));
                //add point
                str += MApp_ZUI_API_Strlen(str);
                *str++ = CHAR_DOT;
                if(u16tempFreAfterPoint<10)
                {
                    *str++ = CHAR_0;
                }
                //after point bit
                u8NoOfDigit = MApp_GetNoOfDigit( u16tempFreAfterPoint );
                MApp_UlongToU8String( u16tempFreAfterPoint , u8TempStr, u8NoOfDigit );
                MApp_ZUI_API_StringBuffU8toU16(str, u8TempStr, strlen((char *)u8TempStr)+1);
                str[strlen((char *)u8TempStr)] = 0;

                return CHAR_BUFFER;
            }
            break;

        case HWND_FMRADIO_INFOMATION_EDIT_NAME_VALUE1:
            MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, g_Radio_stCurChData.au8ChName, 0);
            return CHAR_BUFFER;
            break;

        case HWND_FMRADIO_INFOMATION_EDIT_NAME_VALUE2:
            MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, g_Radio_stCurChData.au8ChName+1, 0);
            return CHAR_BUFFER;
            break;

       case HWND_FMRADIO_INFOMATION_EDIT_NAME_VALUE3:
            MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, g_Radio_stCurChData.au8ChName+2, 0);
            return CHAR_BUFFER;
            break;

        case HWND_FMRADIO_INFOMATION_EDIT_NAME_VALUE4:
            MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, g_Radio_stCurChData.au8ChName+3, 0);
            return CHAR_BUFFER;
            break;

        case HWND_FMRADIO_INFOMATION_EDIT_NAME_VALUE5:
            MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, g_Radio_stCurChData.au8ChName+4, 0);
            return CHAR_BUFFER;
            break;

        case HWND_FMRADIO_INFOMATION_EDIT_NAME_VALUE6:
            MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, g_Radio_stCurChData.au8ChName+5, 0);
            return CHAR_BUFFER;
            break;

        ///////////////////////////////////////////////////////////////////////////////////////
        case HWND_FMRADIO_LIST_PAGE_KEY_INFO_REDKEY_TEXT:
            return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8*)"All Tune", STRING_BUFFER_LENGTH);
            break;

        case HWND_FMRADIO_LIST_PAGE_KEY_INFO_GREENKEY_TEXT:
            return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8*)"Backlight", STRING_BUFFER_LENGTH);
            break;

        case HWND_FMRADIO_LIST_PAGE_KEY_INFO_SELECTKEY_TEXT:
            return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8*)"Choose CH", STRING_BUFFER_LENGTH);
            break;

        //-----------------tenkey-----------------------------------
        case HWND_FMRADIO_TENKEY_CH_NUMBER_PAGE:
            u8NoOfDigit = MApp_GetNoOfDigit( _u8FMIdleInputValue );
            MApp_UlongToU8String( _u8FMIdleInputValue , u8TempStr, u8NoOfDigit );
            MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8TempStr,  strlen((char *)u8TempStr));
            return CHAR_BUFFER;
            break;

        //-----------------autotune---------------------------------
        case HWND_FMRADIO_AUTOTUNE_INFO_PERCENTAGE_TEXT:
            return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8*)"%...", STRING_BUFFER_LENGTH);
            break;

        case HWND_FMRADIO_AUTOTUNE_INFO_FREQUENCY_TEXT:
            return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8*)"MHz", STRING_BUFFER_LENGTH);
            break;

        case HWND_FMRADIO_AUTOTUNE_INFO_PERCENTAGE_VALUE:
            u8NoOfDigit = MApp_GetNoOfDigit( u8SFMScanPercentageNum );
            MApp_UlongToU8String( u8SFMScanPercentageNum , u8TempStr, u8NoOfDigit );
            MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8TempStr,  strlen((char *)u8TempStr));
            return CHAR_BUFFER;
            break;

        case HWND_FMRADIO_AUTOTUNE_INFO_FREQUENCY_VALUE:
            CHAR_BUFFER[0] = 0;
            //U16 u16tempFreBeforePoint, u16tempFreAfterPoint;
            str = CHAR_BUFFER;
            printf("2 u16SFMScanFreqNum:0x%x\n",u16SFMScanFreqNum);

            u16tempFreBeforePoint = u16SFMScanFreqNum / 100;
            u16tempFreAfterPoint = u16SFMScanFreqNum % 100;

            //before point bit
            u8NoOfDigit = MApp_GetNoOfDigit( u16tempFreBeforePoint );
            MApp_UlongToU8String( u16tempFreBeforePoint , u8TempStr, u8NoOfDigit );
            MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8TempStr, strlen((char *)u8TempStr));
            //add point
            str += MApp_ZUI_API_Strlen(str);
            *str++ = CHAR_DOT;
            if(u16tempFreAfterPoint<10)
            {
                *str++ = CHAR_0;
            }
            //after point bit
            u8NoOfDigit = MApp_GetNoOfDigit( u16tempFreAfterPoint );
            MApp_UlongToU8String( u16tempFreAfterPoint , u8TempStr, u8NoOfDigit );
            MApp_ZUI_API_StringBuffU8toU16(str, u8TempStr, strlen((char *)u8TempStr)+1);
            str[strlen((char *)u8TempStr)] = 0;

            return CHAR_BUFFER;
            break;

        default:
            break;
    }
    if (u16TempID != Empty)
        return MApp_ZUI_API_GetString(u16TempID);
    return 0; //for empty string....

}

U16 MApp_ZUI_ACT_GetFMRadioDynamicBitmap(HWND hwnd, DRAWSTYLE_TYPE ds_type)
{
    UNUSED(ds_type);
    U16 u16BtimapIdx=0xFFFF;
    switch(hwnd)
    {
        default:
            break;
    }
    return u16BtimapIdx;
}

S16 MApp_ZUI_ACT_GetFMRadioDynamicValue(HWND hwnd)
{
    switch(hwnd)
    {
        case HWND_FMRADIO_AUTOTUNE_INFO_PROGRESS_BAR:
            printf("u8SFMScanPercentageNum : 0x%x\n",u8SFMScanPercentageNum);
            return (U16)u8SFMScanPercentageNum;
            break;

        default:
            break;
    }

    return 0; //for empty  data
}
GUI_ENUM_DYNAMIC_LIST_STATE MApp_ZUI_ACT_QueryFMRadioStatus(HWND hwnd)
{
    switch(hwnd)
    {
        default:
            return EN_DL_STATE_NORMAL;
    }
}

#endif
#undef MAPP_ZUI_ACTFMRADIO_C
