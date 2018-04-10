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

#define MAPP_ZUI_ACTCHANNELINFO_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include <string.h>
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "MsOS.h"

// Common Definition
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "msAPI_Video.h"
#include "msAPI_Timer.h"

#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_ZUI_ACTmainpage.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_ACTglobal.h"
#if (ENABLE_CI_PLUS)
#include "MApp_CIMMI.h"
#endif
#include "MApp_ZUI_ACTchannelinfo.h"

#include "OSDcp_String_EnumIndex.h"
#include "ZUI_exefunc.h"
#include "MApp_MVDMode.h"
#include "MApp_SignalMonitor.h"
#include "msAPI_DTVSystem.h"
#include "msAPI_ATVSystem.h"
#include "MApp_ChannelChange.h"
#include "MApp_GlobalFunction.h"
#include "MApp_UiMenuDef.h"
#include "msAPI_Tuning.h"
#include "MApp_PCMode.h"
#include "OSDcp_Bitmap_EnumIndex.h"

// [END]
#include "MApp_VDMode.h"
#include "MApp_AnalogInputs.h"

#if (ENABLE_SUBTITLE)
#include "MApp_Subtitle.h"
#endif

#if (ENABLE_DTV)
#include "mapp_demux.h"
#include "mapp_si.h"
#endif

#include "msAPI_VD.h"
#include "msAPI_audio.h"
#include "apiXC_ModeParse.h"
#include "apiXC_PCMonitor.h"
#include "apiXC_Cus.h"
#include "apiXC_Sys.h"
#include "drvXC_HDMI_if.h"
#include "MApp_Key.h"

#include "MApp_ZUI_GlobalFunction.h"
#if (ENABLE_DTV_EPG)
#include "mapp_eit.h"
#endif
#if (ENABLE_TTX)
#include "mapp_ttx.h"
#endif

#if ENABLE_PVR
#include "MApp_Playback.h"
#include "MApp_Record.h"
#endif

#if ((ATSC_CC == ATV_CC) || ENABLE_ISDB_ATV_VCHIP)
#include "MApp_VChip.h"
#endif

#if(ENABLE_PIP)
#include "MApp_PIP.h"
#endif
/////////////////////////////////////////////////////////////////////

#define ZUI_CHINFO_TUNER_LOCK_TIMER_ID      0
#define ZUI_CHINFO_EVENT_TIME_TIMER_ID      1
#define ZUI_CHINFO_VIDEO_MODE_TIMER_ID      2
#define ZUI_CHINFO_AUDIO_MODE_TIMER_ID      3

#define ZUI_CHINFO_CHECKING_PERIOD          100 //ms

#if ((UI_SKIN_SEL == UI_SKIN_960X540X565)||(UI_SKIN_SEL == UI_SKIN_960X540XI8))
#define BRIEF_EXT_OFFSET                    42
#else
#define BRIEF_EXT_OFFSET                    60
#endif
#define BRIEF_PIP_OFFSET                    32
#define PIP_MAIN_SUB_OFFSET                 683

#define PIP_1_ORIGINAL_POS_TOP              624
#define PIP_1_ORIGINAL_POS_HEIGHT           32

#define PIP_1_PIP_BRIEF_POS_TOP             603
#define PIP_1_PIP_BRIEF_POS_HEIGHT          22

#define PIP_1_PIP_EXT_POS_TOP               543
#define PIP_1_PIP_EXT_POS_HEIGHT            22

#define PIP_2_ORIGINAL_POS_LEFT             691
#define PIP_2_ORIGINAL_POS_TOP              624
#define PIP_2_ORIGINAL_POS_HEIGHT           32

#define PIP_2_PIP_BRIEF_POS_LEFT            8
#define PIP_2_PIP_BRIEF_POS_TOP             741
#define PIP_2_PIP_BRIEF_POS_HEIGHT          22

#define PIP_2_PIP_EXT_POS_LEFT              8
#define PIP_2_PIP_EXT_POS_TOP               741
#define PIP_2_PIP_EXT_POS_HEIGHT            22

#define BTM_PR_BG1_ORIGINAL_POS_TOP         709
#define BTM_PR_BG1_PIP_BRIEF_POS_TOP        677

#define BTM_PR_BG1_GREEN_ORIGINAL_POS_TOP   668
#define BTM_PR_BG1_GREENPIP_BRIEF_POS_TOP   636

#define BTM_PR_BG5_ORIGINAL_POS_LEFT        0

#define BTM_PR_RARROW_ORIGINAL_POS_LEFT     1317
#define BTM_PR_RARROW_ORIGINAL_POS_TOP      608

#define BTM_PR_RARROW_PIP_EXT_POS_LEFT       634
#define BTM_PR_RARROW_PIP_EXT_POS_TOP        668

#define BTM_PR_LARROW_ORIGINAL_POS_TOP       608
#define BTM_PR_LARROW_PIP_EXT_POS_TOP        668

#define BTM_PR_NAME_ORIGINAL_POS_LEFT        371
#define BTM_PR_NAME_ORIGINAL_POS_TOP         608
#define BTM_PR_NAME_ORIGINAL_POS_WIDTH       624

#define BTM_PR_NAME_PIP_EXT_POS_LEFT         247
#define BTM_PR_NAME_PIP_EXT_POS_TOP          668
#define BTM_PR_NAME_PIP_EXT_POS_WIDTH        189

#define BTM_PR_TIME_START_ORIGINAL_POS_TOP   608
#define BTM_PR_TIME_START_ORIGINAL_POS_WIDTH 150

#define BTM_PR_TIME_START_PIP_EXT_POS_TOP    668
#define BTM_PR_TIME_START_PIP_EXT_POS_WIDTH   94

#define BTM_PR_TIME_END_ORIGINAL_POS_LEFT    201
#define BTM_PR_TIME_END_ORIGINAL_POS_TOP     608
#define BTM_PR_TIME_END_ORIGINAL_POS_WIDTH   150

#define BTM_PR_TIME_END_PIP_EXT_POS_LEFT     145
#define BTM_PR_TIME_END_PIP_EXT_POS_TOP      668
#define BTM_PR_TIME_END_PIP_EXT_POS_WIDTH     94

#define BTM_PR_GENRE_END_ORIGINAL_POS_LEFT  1015
#define BTM_PR_GENRE_END_ORIGINAL_POS_TOP    608
#define BTM_PR_GENRE_END_ORIGINAL_POS_WIDTH  169

#define BTM_PR_GENRE_END_PIP_EXT_POS_LEFT    446
#define BTM_PR_GENRE_END_PIP_EXT_POS_TOP     668
#define BTM_PR_GENRE_END_PIP_EXT_POS_WIDTH    94

#define BTM_PR_AGE_END_ORIGINAL_POS_LEFT    1184
#define BTM_PR_AGE_END_ORIGINAL_POS_TOP      608
#define BTM_PR_AGE_END_ORIGINAL_POS_WIDTH    133

#define BTM_PR_AGE_END_PIP_EXT_POS_LEFT      540
#define BTM_PR_AGE_END_PIP_EXT_POS_TOP       668
#define BTM_PR_AGE_END_PIP_EXT_POS_WIDTH      58

#define TOP_CH_COLOR_SYS_ORIGINAL_POS_LEFT   262
#define TOP_CH_COLOR_SYS_ORIGINAL_POS_TOP    649
#define TOP_CH_COLOR_SYS_ORIGINAL_POS_WIDTH  203

#define TOP_CH_COLOR_SYS_PIP_EXT_POS_LEFT    149
#define TOP_CH_COLOR_SYS_PIP_EXT_POS_TOP     712
#define TOP_CH_COLOR_SYS_PIP_EXT_POS_WIDTH    89

#define TOP_CH_SOUND_SYS_ORIGINAL_POS_LEFT   475
#define TOP_CH_SOUND_SYS_ORIGINAL_POS_TOP    649
#define TOP_CH_SOUND_SYS_ORIGINAL_POS_WIDTH  203

#define TOP_CH_SOUND_SYS_PIP_EXT_POS_LEFT    248
#define TOP_CH_SOUND_SYS_PIP_EXT_POS_TOP     712
#define TOP_CH_SOUND_SYS_PIP_EXT_POS_WIDTH    89

#define TOP_CH_INPUT_ORIGINAL_POS_LEFT       688
#define TOP_CH_INPUT_ORIGINAL_POS_TOP        649
#define TOP_CH_INPUT_ORIGINAL_POS_WIDTH      203

#define TOP_CH_INPUT_PIP_EXT_POS_LEFT        347
#define TOP_CH_INPUT_PIP_EXT_POS_TOP         712
#define TOP_CH_INPUT_PIP_EXT_POS_WIDTH        89

#define TOP_CH_SDHD_ORIGINAL_POS_LEFT        901
#define TOP_CH_SDHD_ORIGINAL_POS_TOP         649
#define TOP_CH_SDHD_ORIGINAL_POS_WIDTH       203

#define TOP_CH_SDHD_PIP_EXT_POS_LEFT         446
#define TOP_CH_SDHD_PIP_EXT_POS_TOP          712
#define TOP_CH_SDHD_PIP_EXT_POS_WIDTH         89

#define TOP_CH_MTS_TYPE_ORIGINAL_POS_LEFT   1114
#define TOP_CH_MTS_TYPE_ORIGINAL_POS_TOP     649
#define TOP_CH_MTS_TYPE_ORIGINAL_POS_WIDTH   203

#define TOP_CH_MTS_TYPE_PIP_EXT_POS_LEFT     545
#define TOP_CH_MTS_TYPE_PIP_EXT_POS_TOP      712
#define TOP_CH_MTS_TYPE_PIP_EXT_POS_WIDTH     89

#define TOP_CH_AUDIO_TYPE_ORIGINAL_POS_LEFT   49
#define TOP_CH_AUDIO_TYPE_ORIGINAL_POS_TOP   679
#define TOP_CH_AUDIO_TYPE_ORIGINAL_POS_WIDTH 203

#define TOP_CH_AUDIO_TYPE_PIP_EXT_POS_LEFT    50
#define TOP_CH_AUDIO_TYPE_PIP_EXT_POS_TOP    740
#define TOP_CH_AUDIO_TYPE_PIP_EXT_POS_WIDTH   89

#define BTM_PR_MHEG_ORIGINAL_POS_LEFT        262
#define BTM_PR_MHEG_ORIGINAL_POS_TOP         679
#define BTM_PR_MHEG_ORIGINAL_POS_WIDTH       203

#define BTM_PR_MHEG_PIP_EXT_POS_LEFT         149
#define BTM_PR_MHEG_PIP_EXT_POS_TOP          740
#define BTM_PR_MHEG_PIP_EXT_POS_WIDTH         89

#define BTM_PR_NARRATION_ORIGINAL_POS_LEFT   475
#define BTM_PR_NARRATION_ORIGINAL_POS_TOP    679
#define BTM_PR_NARRATION_ORIGINAL_POS_WIDTH  203

#define BTM_PR_NARRATION_PIP_EXT_POS_LEFT    248
#define BTM_PR_NARRATION_PIP_EXT_POS_TOP     740
#define BTM_PR_NARRATION_PIP_EXT_POS_WIDTH    89

#define BTM_PR_SUBTITLE_ORIGINAL_POS_LEFT    688
#define BTM_PR_SUBTITLE_ORIGINAL_POS_TOP     679
#define BTM_PR_SUBTITLE_ORIGINAL_POS_WIDTH   203

#define BTM_PR_SUBTITLE_PIP_EXT_POS_LEFT     347
#define BTM_PR_SUBTITLE_PIP_EXT_POS_TOP      740
#define BTM_PR_SUBTITLE_PIP_EXT_POS_WIDTH     89

#define BTM_PR_AUDIO_LANG_ORIGINAL_POS_LEFT  901
#define BTM_PR_AUDIO_LANG_ORIGINAL_POS_TOP   679
#define BTM_PR_AUDIO_LANG_ORIGINAL_POS_WIDTH 203

#define BTM_PR_AUDIO_LANG_PIP_EXT_POS_LEFT   446
#define BTM_PR_AUDIO_LANG_PIP_EXT_POS_TOP    740
#define BTM_PR_AUDIO_LANG_PIP_EXT_POS_WIDTH   89


#define BTM_PR_TELETEXT_ORIGINAL_POS_LEFT   1114
#define BTM_PR_TELETEXT_ORIGINAL_POS_TOP     679
#define BTM_PR_TELETEXT_ORIGINAL_POS_WIDTH   203

#define BTM_PR_TELETEXT_PIP_EXT_POS_LEFT     545
#define BTM_PR_TELETEXT_PIP_EXT_POS_TOP      740
#define BTM_PR_TELETEXT_PIP_EXT_POS_WIDTH     89

#define TOP_CH_NUMBER_ORIGINAL_POS_TOP       564

#define TOP_CH_NUMBER_POP_POS_TOP            624

#define TOP_CH_NAME_ORIGINAL_POS_LEFT        218
#define TOP_CH_NAME_ORIGINAL_POS_TOP         564

#define TOP_CH_NAME_POP_POS_LEFT             158
#define TOP_CH_NAME_POP_POS_TOP              624

#define BTM_PR_TIME_ORIGINAL_POS_LEFT        378
#define BTM_PR_TIME_ORIGINAL_POS_TOP         564

#define BTM_PR_TIME_POP_POS_LEFT             268
#define BTM_PR_TIME_POP_POS_TOP              624

#define BTM_PR_DATE_ORIGINAL_POS_LEFT        444
#define BTM_PR_DATE_ORIGINAL_POS_TOP         564

#define BTM_PR_DATE_POP_POS_LEFT             348
#define BTM_PR_DATE_POP_POS_TOP              624

static AUDIOMODE_TYPE   _preCurrentMTSType;
U8                      u8InfoScrollLineCount;
U8                      u8InfoScrollLineCount_Pre;
extern U16              u16NextLineStartInx;
extern bit              bStopScrollDown;
U16                     au16EventTextScrollLineInx[98];
extern AUDIOMODE_TYPE   m_eAudioMode;
U8                      u8IsBriefChInfo;    //identify whether the act is EN_EXE_SHOW_BRIEF_CH_INFO or not

#if (ENABLE_ARABIC_OSD)
extern BOOLEAN ArabicCHStringFlag;
#endif

extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);
//extern void _MApp_ZUI_API_DrawDynamicComponent(DRAWCOMPONENT component, const void * param, const GRAPHIC_DC * pdc, const RECT * rect);
extern U16 MApp_ZUI_GetCurrentInputSourceStringID(E_UI_INPUT_SOURCE src);
extern LPTSTR MApp_ZUI_ACT_GetMenuLanguageStringByIndex(U8 u8Index);

#if (ENABLE_PIP)
static SCALER_WIN _MApp_ZUI_ACT_Channelinfo_PIP_Window_Query(EN_PIP_MODE enpip, HWND hwnd)
{
    if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
    {
        if(enpip == EN_PIP_MODE_PIP)
        {
            //sub window at right side
            if(stGenSetting.g_stPipSetting.enPipPosition == EN_PIP_POSITION_RIGHT_TOP ||
                stGenSetting.g_stPipSetting.enPipPosition == EN_PIP_POSITION_RIGHT_BOTTOM)
            {
                if(hwnd == HWND_CHINFO_POP_LEFT_TV_INFO || hwnd == HWND_CHINFO_POP_LEFT_SRC_INFO)
                {
                    return MAIN_WINDOW;
                }
                else if(hwnd == HWND_CHINFO_POP_RIGHT_TV_INFO || hwnd == HWND_CHINFO_POP_RIGHT_SRC_INFO)
                {
                    return SUB_WINDOW;
                }
            }
            else if(stGenSetting.g_stPipSetting.enPipPosition == EN_PIP_POSITION_LEFT_TOP ||
                stGenSetting.g_stPipSetting.enPipPosition == EN_PIP_POSITION_LEFT_BOTTOM)
            {
                if(hwnd == HWND_CHINFO_POP_LEFT_TV_INFO || hwnd == HWND_CHINFO_POP_LEFT_SRC_INFO)
                {
                    return SUB_WINDOW;
                }
                else if(hwnd == HWND_CHINFO_POP_RIGHT_TV_INFO || hwnd == HWND_CHINFO_POP_RIGHT_SRC_INFO)
                {
                    return MAIN_WINDOW;
                }
            }

        }
        else if(enpip == EN_PIP_MODE_POP || enpip == EN_PIP_MODE_POP_FULL)
        {
            if(hwnd == HWND_CHINFO_POP_LEFT_TV_INFO || hwnd == HWND_CHINFO_POP_LEFT_SRC_INFO)
            {
                return MAIN_WINDOW;
            }
            else if(hwnd == HWND_CHINFO_POP_RIGHT_TV_INFO || hwnd == HWND_CHINFO_POP_RIGHT_SRC_INFO)
            {
                return SUB_WINDOW;
            }
        }
    }
    return MAIN_WINDOW;

}
#endif


void MApp_ZUI_ACT_AppShowChannelInfo(void)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_CHANNEL_INFO;

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
        ZUI_CHANNEL_INFO_XSTART, ZUI_CHANNEL_INFO_YSTART,
        ZUI_CHANNEL_INFO_WIDTH, ZUI_CHANNEL_INFO_HEIGHT);

    if (!MApp_ZUI_API_InitGDI(&rect))
    {
        ZUI_DBG_FAIL(printf("[ZUI]GDIINIT\n"));
        ABORT();
        return;
    }

#if (ENABLE_ARABIC_OSD)
    ArabicCHStringFlag = TRUE;
#endif

    for (wnd = 0; wnd < HWND_MAX; wnd++)
    {
        //printf("create msg: %lu\n", (U32)wnd);
        MApp_ZUI_API_SendMessage(wnd, MSG_CREATE, 0);
    }

    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_CHINFO_TRANSPARENT_BG, SW_SHOW);

    MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_OPEN, E_ZUI_STATE_RUNNING);
}


//////////////////////////////////////////////////////////
// Key Handler

BOOLEAN MApp_ZUI_ACT_HandleChannelInfoKey(VIRTUAL_KEY_CODE key)
{
    //note: don't do anything here! keys will be handled in state machines
    //      moved to MApp_TV_ProcessAudioVolumeKey()
    UNUSED(key);
    ZUI_DBG_FAIL(printf("[ZUI]IDLEKEY\n"));
    //ABORT();
    return FALSE;
}

void MApp_ZUI_ACT_TerminateChannelInfo(void)
{
    ZUI_MSG(printf("Terminate Channel Info\n"));
#if (ENABLE_ARABIC_OSD)
    ArabicCHStringFlag = FALSE;
#endif
}

#if (ENABLE_DTV_EPG)
BOOLEAN MApp_ZUI_ACT_ACTchannelinfo_Scroll(void)
{
    if (u8KeyCode == KEY_DOWN && bStopScrollDown)
        return FALSE;

    if ( u8KeyCode == KEY_DOWN && !bStopScrollDown )
    {
        u8InfoScrollLineCount ++;
    }
    if ( u8KeyCode == KEY_UP && u8InfoScrollLineCount > 0 )
    {
        u8InfoScrollLineCount--;
    }

    if ( u8InfoScrollLineCount == 0 )
    {
        au16EventTextScrollLineInx[0] = 0;
    }
    else
    {
        if ( u8InfoScrollLineCount > u8InfoScrollLineCount_Pre )
        {
            au16EventTextScrollLineInx[u8InfoScrollLineCount] = au16EventTextScrollLineInx[u8InfoScrollLineCount - 1] + u16NextLineStartInx;
            u8InfoScrollLineCount_Pre = u8InfoScrollLineCount;
        }
    }

    if ( bNextEvent )
    {
        MApp_EIT_GetPfString(NEXT,(U8*)CHAR_BUFFER,(au16EventTextScrollLineInx[u8InfoScrollLineCount]*2),1024);
    }
    else
    {
        MApp_EIT_GetPfString(NOW,(U8*)CHAR_BUFFER,(au16EventTextScrollLineInx[u8InfoScrollLineCount]*2),1024);
    }

    MApp_ZUI_API_ShowWindow(HWND_CHINFO_EXT_CONTENT_TEXT, SW_SHOW);

    return TRUE;
}
#endif

///////////////////////////////////////////////////////////////////////////////
///  private  MApp_ZUI_ACT_ExecuteChannelInfoAction
///  [OSD page handler] execute a specific action in CHANNEL INFO application
///
///  @param [in]       act U16      action ID
///
///  @return BOOLEAN     true for accept, false for ignore
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_ZUI_ACT_ExecuteChannelInfoAction(U16 act)
{

AGAIN:
    switch(act)
    {
        case EN_EXE_CLOSE_CURRENT_OSD:
        case EN_EXE_POWEROFF:
            bNextEvent=FALSE;
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            MApp_ZUI_ACT_ShutdownOSD();
          #if ENABLE_TTX
            MApp_TTX_SetChInfoOnOff(FALSE);
          #endif
            return (act != EN_EXE_POWEROFF); // return FALSE for KEY_POWER


        case EN_EXE_RESET_AUTO_CLOSE_TIMER:
            //reset timer if any key
            MApp_ZUI_API_ResetTimer(HWND_CHINFO_ROOT_PANE, 0);
            return FALSE;


        case EN_EXE_HIDE_CH_INFO:                        ///< hide CH INFO
            MApp_ZUI_API_ShowWindow(HWND_CHINFO_ROOT_PANE, SW_HIDE);
            return TRUE;


        case EN_EXE_REPAINT_CH_BANNER:             ///< invalidate/repaint channel banner (top part)
            //to enable timer for checking....
            MApp_ZUI_API_SetTimer(HWND_CHINFO_TRANSPARENT_BG, ZUI_CHINFO_TUNER_LOCK_TIMER_ID, ZUI_CHINFO_CHECKING_PERIOD);
            MApp_ZUI_API_SetTimer(HWND_CHINFO_TRANSPARENT_BG, ZUI_CHINFO_AUDIO_MODE_TIMER_ID, ZUI_CHINFO_CHECKING_PERIOD);
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHINFO_ROOT_PANE);
            return TRUE;


        case EN_EXE_REPAINT_CH_INFO:             ///< invalidate/repaint CH INFO
            if (bNextEvent)
            {
            #if (ENABLE_PIP)
                if(IsPIPSupported() && MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
                {
                    if(MApp_Get_PIPMode() == EN_PIP_MODE_POP
                        || MApp_Get_PIPMode() == EN_PIP_MODE_POP_FULL)
                    {
                        if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
                            || IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
                        {
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_LARROW_ICON, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_RARROW_ICON, SW_HIDE);
                        }
                        if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))
                            || IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
                        {
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_LARROW_ICON, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_RARROW_ICON, SW_HIDE);
                        }
                    }
                }
                else
            #endif
                {
                    MApp_ZUI_API_ShowWindow(HWND_CHINFO_EXT_LARROW_ICON, SW_SHOW);
                    MApp_ZUI_API_ShowWindow(HWND_CHINFO_EXT_RARROW_ICON, SW_HIDE);
                }
            }
            else
            {
            #if (ENABLE_PIP)
                if(IsPIPSupported() && MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
                {
                    if(MApp_Get_PIPMode() == EN_PIP_MODE_POP
                        || MApp_Get_PIPMode() == EN_PIP_MODE_POP_FULL)
                    {
                        if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
                            || IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
                        {
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_LARROW_ICON, SW_HIDE);
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_RARROW_ICON, SW_SHOW);
                        }
                        if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))
                            || IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
                        {
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_LARROW_ICON, SW_HIDE);
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_RARROW_ICON, SW_SHOW);
                        }
                    }
                }
                else
            #endif
                {
                    MApp_ZUI_API_ShowWindow(HWND_CHINFO_EXT_LARROW_ICON, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_CHINFO_EXT_RARROW_ICON, SW_SHOW);
                }
            }

            if (!IsDTVInUse()) //IsATVInUse())
            {
            #if (ENABLE_PIP)
                if(IsPIPSupported() && MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
                {
                    if(MApp_Get_PIPMode() == EN_PIP_MODE_POP
                        || MApp_Get_PIPMode() == EN_PIP_MODE_POP_FULL)
                    {
                        if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
                            || IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
                        {
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_LARROW_ICON, SW_HIDE);
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_RARROW_ICON, SW_HIDE);
                        }
                        if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))
                            || IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
                        {
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_LARROW_ICON, SW_HIDE);
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_RARROW_ICON, SW_HIDE);
                        }
                    }
                }
                else
            #endif
                {
                    MApp_ZUI_API_ShowWindow(HWND_CHINFO_EXT_RARROW_ICON, SW_HIDE);
                    MApp_ZUI_API_ShowWindow(HWND_CHINFO_EXT_LARROW_ICON, SW_HIDE);
                }
            }
            MApp_ZUI_API_SetTimer(HWND_CHINFO_TRANSPARENT_BG, ZUI_CHINFO_VIDEO_MODE_TIMER_ID, ZUI_CHINFO_CHECKING_PERIOD);
            MApp_ZUI_API_SetTimer(HWND_CHINFO_TRANSPARENT_BG, ZUI_CHINFO_EVENT_TIME_TIMER_ID, ZUI_CHINFO_CHECKING_PERIOD);
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHINFO_ROOT_PANE);
            return TRUE;


    #if (ENABLE_DTV_EPG)
        case EN_EXE_REPAINT_CH_INFO_SCROLL:
                return MApp_ZUI_ACT_ACTchannelinfo_Scroll();
    #endif  //#if (ENABLE_DTV_EPG)


        case EN_EXE_SHOW_BRIEF_CH_INFO:                  ///< show brief CH INFO
        {
            //move brief pane: align to bottom of screen.....
            RECT rc_ext;//,rc_top_pane;

        #if (ENABLE_PIP)
            if(IsPIPSupported() && MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
            {
                if(MApp_Get_PIPMode() == EN_PIP_MODE_PIP)//PIP
                {
                    if(MApp_Get_PIPMode() == EN_PIP_POSITION_RIGHT_TOP ||
                      MApp_Get_PIPMode() == EN_PIP_POSITION_RIGHT_BOTTOM)
                    {
                        // 1. Show Main window POP src type
                        if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
                            || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
                        {// Main window src is TV type
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_AREA, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_SRC_INFO, SW_HIDE);
                        }
                        else
                        {// Main window src is OTHER type
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_AREA, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_TV_INFO, SW_HIDE);
                        }
                        // 2. Show Sub window POP src type
                        if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))
                         || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
                        {// Sub window src is TV type
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_AREA, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_SRC_INFO, SW_HIDE);
                        }
                        else
                        {// Sub window src is OTHER type
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_AREA, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_TV_INFO, SW_HIDE);
                        }
                    }
                    else
                    {
                        // 1. Show Main window POP src type
                        if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))
                            || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
                        {// Main window src is TV type
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_AREA, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_SRC_INFO, SW_HIDE);
                        }
                        else
                        {// Main window src is OTHER type
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_AREA, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_TV_INFO, SW_HIDE);
                        }
                        // 2. Show Sub window POP src type
                        if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
                         || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
                        {// Sub window src is TV type
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_AREA, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_SRC_INFO, SW_HIDE);
                        }
                        else
                        {// Sub window src is OTHER type
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_AREA, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_TV_INFO, SW_HIDE);
                        }
                    }

                }
                else if(MApp_Get_PIPMode() == EN_PIP_MODE_POP
                    || MApp_Get_PIPMode() == EN_PIP_MODE_POP_FULL)
                {
                    // 1. Show Main window POP src type
                    if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
                        || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
                    {// Main window src is TV type
                        MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_AREA, SW_SHOW);
                        MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_SRC_INFO, SW_HIDE);
                    }
                    else
                    {// Main window src is OTHER type
                        MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_AREA, SW_SHOW);
                        MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_TV_INFO, SW_HIDE);
                    }
                    // 2. Show Sub window POP src type
                    if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))
                        || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
                    {// Sub window src is TV type
                        MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_AREA, SW_SHOW);
                        MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_SRC_INFO, SW_HIDE);
                    }
                    else
                    {// Sub window src is OTHER type
                        MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_AREA, SW_SHOW);
                        MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_TV_INFO, SW_HIDE);
                    }
                }
            }
            else//normal mode
        #endif
            {
                MApp_ZUI_API_ShowWindow(HWND_CHINFO_EXT_PANE, SW_SHOW);
                MApp_ZUI_API_ShowWindow(HWND_CHINFO_EXT_CONTENT_EXTENSION_BG, SW_HIDE);
                MApp_ZUI_API_GetWindowInitialRect(HWND_CHINFO_EXT_PANE, &rc_ext);
                MApp_ZUI_API_MoveAllSuccessors(HWND_CHINFO_EXT_PANE,
                rc_ext.left, rc_ext.top+BRIEF_EXT_OFFSET);
            }
        }
        act = EN_EXE_REPAINT_CH_INFO;
        u8IsBriefChInfo = TRUE;
        goto AGAIN;


        case EN_EXE_SHOW_EXTENDED_CH_INFO:               ///< show ext CH INFO
        {
        #if (ENABLE_PIP)
            if(IsPIPSupported() && MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
            {
                if(MApp_Get_PIPMode() == EN_PIP_MODE_POP ||
                   MApp_Get_PIPMode() == EN_PIP_MODE_POP_FULL)//POP mode
                {
                    // 1. Show Main window POP src type
                    if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
                        || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
                    {// Main window src is TV type
                        MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_AREA, SW_SHOW);
                        MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_SRC_INFO, SW_HIDE);
                    }
                    else
                    {// Main window src is OTHER type
                        MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_AREA, SW_SHOW);
                        MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_TV_INFO, SW_HIDE);
                    }
                    // 2. Show Sub window POP src type
                    if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))
                        || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
                    {// Sub window src is TV type
                        MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_AREA, SW_SHOW);
                        MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_SRC_INFO, SW_HIDE);
                    }
                    else
                    {// Sub window src is OTHER type
                        MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_AREA, SW_SHOW);
                        MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_TV_INFO, SW_HIDE);
                    }
                }
                else if(MApp_Get_PIPMode() == EN_PIP_MODE_PIP)//PIP mode
                {

                    if(stGenSetting.g_stPipSetting.enPipPosition == EN_PIP_POSITION_RIGHT_TOP ||
                      stGenSetting.g_stPipSetting.enPipPosition == EN_PIP_POSITION_RIGHT_BOTTOM)
                    {
                        // 1. Show Main window POP src type
                        if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
                            || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
                        {// Main window src is TV type
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_AREA, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_SRC_INFO, SW_HIDE);
                        }
                        else
                        {// Main window src is OTHER type
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_AREA, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_TV_INFO, SW_HIDE);
                        }
                        // 2. Show Sub window POP src type
                        if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))
                         || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
                        {// Sub window src is TV type
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_AREA, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_SRC_INFO, SW_HIDE);
                        }
                        else
                        {// Sub window src is OTHER type
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_AREA, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_TV_INFO, SW_HIDE);
                        }
                    }
                    else
                    {
                        // 1. Show Main window POP src type
                        if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))
                            || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
                        {// Main window src is TV type
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_AREA, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_SRC_INFO, SW_HIDE);
                        }
                        else
                        {// Main window src is OTHER type
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_AREA, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_LEFT_TV_INFO, SW_HIDE);
                        }
                        // 2. Show Sub window POP src type
                        if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
                         || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
                        {// Sub window src is TV type
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_AREA, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_SRC_INFO, SW_HIDE);
                        }
                        else
                        {// Sub window src is OTHER type
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_AREA, SW_SHOW);
                            MApp_ZUI_API_ShowWindow(HWND_CHINFO_POP_RIGHT_TV_INFO, SW_HIDE);
                        }
                    }

                }
            }
            else//normal mode
        #endif
            {
                MApp_ZUI_API_ShowWindow(HWND_CHINFO_EXT_PANE, SW_SHOW);
            }
            act = EN_EXE_REPAINT_CH_INFO;
            u8IsBriefChInfo = FALSE;
        }
        goto AGAIN;


        case EN_EXE_HIDE_CH_BANNER:                      ///< hide banner
            MApp_ZUI_API_ShowWindow(HWND_CHINFO_EXT_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_CHINFO_PIP_SRC_INFO_AREA, SW_HIDE);
            return TRUE;


        case EN_EXE_SHOW_TV_BANNER:                     ///< show TV channel banner
            //Not used currently. 5/13 2009.
            return TRUE;


        case EN_EXE_SHOW_SOURCE_BANNER:                     ///< show source banner
        {
            {
                //MApp_ZUI_API_ShowWindow(HWND_CHINFO_PIP_SRC1_INFO_AREA, SW_SHOW); //gchen @ 20180322 //MP333 hide source banner
                //MApp_ZUI_API_ShowWindow(HWND_CHINFO_EXT_PANE, SW_HIDE); //gchen @ 20180322 //MP333 hide source banner
            }
        }
        return TRUE;

        default:
            break;
    }
    return FALSE;
}


#if ENABLE_DTV
static U8 _MApp_ZUI_ACT_GetCurrentChannelResolutionType(void)
{
    if(gstVidStatus.u16HorSize >= 1200 && gstVidStatus.u16VerSize >= 700)
        return 1;
    else if(gstVidStatus.u16HorSize>0 && gstVidStatus.u16VerSize>0 && (gstVidStatus.u16VerSize >= 570 && gstVidStatus.u32FrameRate <= 25000 ))
        return 0;
    else if(gstVidStatus.u16HorSize == 0)
        return 3;
    else
        return 2;
}

static BOOLEAN _MApp_ZUI_ACT_IsCurrentSourceAvailable(void)
{
    //from function MApp_UiMenu_CurrentSourceAvailable()
    BOOLEAN StatusCheck = FALSE;

    if ( IsDTVInUse() )
    {
        if (enFrotEndLockStatus != FRONTEND_UNKNOWN)
        {
            if (MApp_GetSignalStatus() == SIGNAL_LOCK)
            {
                StatusCheck=TRUE;
            }
        }
    }
    else if ( IsATVInUse() )
    {
        StatusCheck = IsVDHasSignal();
    }
    else
    {
        StatusCheck= !MApp_Analog_NoSignal_ExcludeATV();
    }

    return StatusCheck;
}
#endif

static LPTSTR _MApp_ZUI_ACT_GetInputSourceResolution(SCALER_WIN eWindow)
{
    //from case CUR_INPUT_SOURCE_VIDEO_RES:
    U16 u16H, u16V, u16F;
    LPTSTR str = CHAR_BUFFER; //iu8Buffer_i = 0;

    if ( IsYPbPrInUse() )
    {
        if(g_PcadcModeSetting[eWindow].u8ModeIndex >= MApi_XC_GetTotalModeCount() )
        {
            return NULL;
        }

        u16V = MApp_PCMode_Get_VResolution( eWindow ,TRUE);

        if( u16V == 0 )//not get resolution yet , so return 0 , to avoid kill timer
            return NULL;

        __MApp_UlongToString( ( U32 )u16V, str, MApp_GetNoOfDigit( u16V ) );
        str += MApp_ZUI_API_Strlen(str); //iu8Buffer_i = __strlen( p_string_buffer );
        if (MApi_XC_PCMonitor_GetSyncStatus(eWindow) & XC_MD_INTERLACE_BIT)
        {
            *str++ = CHAR_i;
        }
        else
        {
            *str++ = CHAR_p;
        }

        u16F = MApi_XC_PCMonitor_Get_VFreqx10( eWindow );
        if(u16F > 560 && u16F < 620)
        {
            u16F= 60;
        }
        else if(u16F > 460 && u16F < 520)
        {
            u16F= 50;
        }
        else if (u16F > 220 && u16F < 245)
        {
            u16F = 24;
        }
        else if(u16F >= 245 && u16F < 260)
        {
            u16F = 25;
        }
        else if(u16F > 280 && u16F < 320)
        {
            u16F = 30;
        }
        else
        {
            u16F= 60;
        }
        *str++ = CHAR_AT;
        __MApp_UlongToString( ( U32 )u16F, str, MApp_GetNoOfDigit( u16F ) );
        str += MApp_ZUI_API_Strlen(str);
        *str++ = CHAR_H;
        *str++ = CHAR_z;
        *str = 0;
        return (MApp_IsSrcHasSignal(eWindow) == FALSE) ? NULL : CHAR_BUFFER;
    }
    else if ( IsVgaInUse() )
    {
        if(MApp_PCMode_GetCurrentState(eWindow) != E_PCMODE_STABLE_SUPPORT_MODE)    //(MApp_PCMode_SyncLossFlag() || g_bUnsupportMode || (g_bInputTimingStable!=TRUE))
        {
            return NULL;
        }
        else
        {
            U16 u16Fx10;

            u16H = MApp_PCMode_Get_HResolution( eWindow , TRUE);
            u16V = MApp_PCMode_Get_VResolution( eWindow , TRUE);
            u16Fx10 = MApi_XC_GetVerticalFrequency(MApp_PCMode_Get_Mode_Idx(eWindow));
            u16F = u16Fx10 / 10;

            if (u16F > 58 && u16F < 61)
            {
                u16F = 60;
            }
            if (u16F > 63 && u16F < 66)
            {
                u16F = 65;
            }
            else if (u16F > 68 && u16F < 71)
            {
                u16F = 70;
            }
            else if (u16F >= 71 && u16F <= 73)
            {
                u16F = 72;
            }
            else if (u16F > 73 && u16F < 77)
            {
                u16F = 75;
            }

            __MApp_UlongToString( ( U32 )u16H, str, MApp_GetNoOfDigit( u16H ) );
            str += MApp_ZUI_API_Strlen(str); //iu8Buffer_i = __strlen( p_string_buffer );
            *str++ = CHAR_x;
            __MApp_UlongToString( ( U32 )u16V, str, MApp_GetNoOfDigit( u16V ) );
            str += MApp_ZUI_API_Strlen(str); //iu8Buffer_i = __strlen( p_string_buffer );
            *str++ = CHAR_AT;
            __MApp_UlongToString( ( U32 )u16F, str, MApp_GetNoOfDigit( u16F ) );
            str += MApp_ZUI_API_Strlen(str); //iu8Buffer_i = __strlen( p_string_buffer );
            *str++ = CHAR_H;
            *str++ = CHAR_z;
            *str = 0;

            return CHAR_BUFFER;
        }
    }
    else if ( IsHDMIInUse() )
    {
        if (MApp_IsSrcHasSignal(eWindow) == FALSE)
            return NULL;

        u16V = MApp_PCMode_Get_VResolution(eWindow, FALSE);
        u16H = MApp_PCMode_Get_HResolution(eWindow, FALSE);

        if((u16V==0)||(u16H==0))
        {
            return NULL;
        }

        if ((u16H >= 710 && u16H <= 1540) && (u16V >= 470 && u16V <= 490))
        {
            u16V = 480;
        }
        else if ((u16H>=710 && u16H<=1540)&&(u16V > 566 && u16V < 586))
        {
            u16V = 576;
        }
        // 1280x720
        else if((u16V > 710 && u16V < 730) && (u16H> 1270 && u16H < 1290))
        {
            u16V = 720;
        }
        // 1920x1080
        else if((u16V > 1070 && u16V < 1090) && (u16H > 1910 && u16H < 1930))
        {
            u16V = 1080;
        }
        else
        {
          #if 0 // no need to adjust
            if ((u16H >= 620&& u16H <= 670) && (u16V >= 470 && u16V <= 490))
            {
                u16V = 480;
                u16H = 640;
            }
            else if ((u16H >= 780&& u16H <= 840) && (u16V >= 580&& u16V <= 620))
            {
                u16V = 600;
                u16H = 800;
            }
            else if ((u16H >= 1000&& u16H <= 1050) && (u16V >= 740&& u16V <= 790))
            {
                u16V = 768;
                u16H = 1024;
            }
            else if( (u16H> 1270 && u16H < 1300)&&(u16V > 740 && u16V < 790))
            {
                u16V = 768;
                u16H = 1280;
            }
            else if( (u16H> 1300 && u16H < 1390)&&(u16V > 740 && u16V < 790))
            {
                u16V = 768;
                u16H = 1360;
            }
            else if ((u16H >= 1260&& u16H <= 1300) && (u16V >= 1000&& u16V <= 1250))
            {
                u16V = 1024;
                u16H = 1280;
            }
            else if ((u16H >= 1580&& u16H <= 1620) && (u16V >= 1180&& u16V <= 1220))
            {
                u16V = 1200;
                u16H = 1600;
            }
            else
            {
                ;
            }
          #endif

            U16 u16Fx10 = MApi_XC_PCMonitor_Get_VFreqx10(eWindow);
            if(u16Fx10 > 470 && u16Fx10 < 530)
            {
                u16F = 50;
            }
            else if(u16Fx10 > 550 && u16Fx10 < 570)
            {
                u16F = 56;
            }
            else if(u16Fx10 > 580 && u16Fx10 < 620)
            {
                u16F = 60;
            }
            else if (u16Fx10 > 670 && u16Fx10 < 710)
            {
                u16F = 70;
            }
            else if(u16Fx10 >= 710 && u16Fx10 < 730)
            {
                u16F = 72;
            }
            else if( u16Fx10 > 730 && u16Fx10 < 770)
            {
                u16F = 75;
            }
            else if( u16Fx10 > 800 && u16Fx10 < 850)
            {
                u16F = 85;
            }
            else
            {
                u16F = (u16Fx10+5)/10;
            }

            __MApp_UlongToString( ( U32 )u16H, str, MApp_GetNoOfDigit( u16H ) );
            str += MApp_ZUI_API_Strlen(str);
            *str++ = CHAR_x;
            __MApp_UlongToString( ( U32 )u16V, str, MApp_GetNoOfDigit( u16V ) );
            str += MApp_ZUI_API_Strlen(str);
            *str++ = CHAR_AT;
            __MApp_UlongToString( ( U32 )u16F, str, MApp_GetNoOfDigit( u16F ) );
            str += MApp_ZUI_API_Strlen(str);
            *str++ = CHAR_H;
            *str++ = CHAR_z;
            *str = 0;
            return CHAR_BUFFER;
        }

        {
            __MApp_UlongToString( ( U32 )u16V, str, MApp_GetNoOfDigit( u16V ) );
            str += MApp_ZUI_API_Strlen(str);
        }

        if (MApi_XC_PCMonitor_GetSyncStatus(eWindow) & XC_MD_INTERLACE_BIT)
        {
            *str++ = CHAR_i;
        }
        else
        {
            *str++ = CHAR_p;
        }

        u16F=MApi_XC_PCMonitor_Get_VFreqx10(eWindow);
        if( u16F > 550 )
        {// (60)
            u16F = 60;
        }
        else if( u16F > 450 )
        {// (50)
            u16F =50;
        }
        else if( u16F > 275 )
        {// (30)
            u16F = 30;
        }
        else if( u16F > 240 )
        {//(25P)
            u16F = 25;
        }
        else if( u16F > 230 )
        {//(24P)
            u16F = 24;
        }
        else if( u16F > 200 )
        {//(23P)
            u16F = 23;
        }
        *str++ = CHAR_AT;
        __MApp_UlongToString( ( U32 )u16F, str, MApp_GetNoOfDigit( u16F ) );
        str += MApp_ZUI_API_Strlen(str);
        *str++ = CHAR_H;
        *str++ = CHAR_z;
        *str = 0;
        return CHAR_BUFFER;
    }
    else if (IsDTVInUse())
    {
        VDEC_DispInfo pinfo;
        BOOLEAN bRet = msAPI_VID_GetVidInfo(&pinfo);

        if( MApp_IsSrcHasSignal(eWindow) && bRet )//if(u16V > 0)
        {
            u16V = pinfo.u16VerSize;

            if (u16V >= 470 && u16V <= 490)
            {
                u16V = 480;
            }
            else if (u16V > 566 && u16V < 586)
            {
                u16V = 576;
            }
            else if(u16V > 710 && u16V < 730)
            {
                u16V = 720;
            }
            else if(u16V > 1070 && u16V < 1090)
            {
                u16V = 1080;
            }

            __MApp_UlongToString( ( U32 )u16V, str, MApp_GetNoOfDigit( u16V ) );
            str += MApp_ZUI_API_Strlen(str); //iu8Buffer_i = __strlen( p_string_buffer );

            //if(pinfo.u8Interlace == 1)
            if( msAPI_VID_Is_SrcOriginalInterlace() )
                *str++ = CHAR_i;
            else
            {
                *str++ = CHAR_p;
                if( pinfo.u8Interlace )
                {
                    printf("Warning: Ori is P, but force to i\n");
                }
            }

            *str = 0;

            return CHAR_BUFFER;
        }
        else
            return NULL;
    }
    else
    {

        if ( MApp_IsSrcHasSignal(eWindow) == FALSE /*||msAPI_AVD_IsVideoFormatChanged()*/ )
              return NULL;
    #if 1

        switch( msAPI_AVD_GetVideoStandard() )
        {
            case E_VIDEOSTANDARD_NTSC_M:
                *str++ = 'N';
                *str++ = 'T';
                *str++ = 'S';
                *str++ = 'C';
                *str = 0;
                break;

            case E_VIDEOSTANDARD_NTSC_44:
                *str++ = 'N';
                *str++ = 'T';
                *str++ = 'S';
                *str++ = 'C';
                *str++ = '4';
                *str++ = '4';
                *str++ = '3';
                *str = 0;
                break;

            case E_VIDEOSTANDARD_PAL_BGHI:
                *str++ = 'P';
                *str++ = 'A';
                *str++ = 'L';
                *str = 0;
                break;

            case E_VIDEOSTANDARD_PAL_M:
                *str++ = 'P';
                *str++ = 'A';
                *str++ = 'L';
                *str++ = '-';
                *str++ = 'M';
                *str = 0;
                break;

            case E_VIDEOSTANDARD_PAL_N:
                *str++ = 'P';
                *str++ = 'A';
                *str++ = 'L';
                *str++ = '-';
                *str++ = 'N';
                *str++ = 'c';
                *str = 0;
                break;

            case E_VIDEOSTANDARD_SECAM:
                *str++ = 'S';
                *str++ = 'E';
                *str++ = 'C';
                *str++ = 'A';
                *str++ = 'M';
                *str = 0;
                break;

            case E_VIDEOSTANDARD_PAL_60:
                *str++ = 'P';
                *str++ = 'A';
                *str++ = 'L';
                *str++ = '-';
                *str++ = '6';
                *str++ = '0';
                *str = 0;
                break;

            default:
                return NULL;
        }
    #else
        switch ( mvideo_vd_get_videosystem() )
        {
            case SIG_NTSC:
            case SIG_NTSC_443:
                //u16TempID = en_str_resolution_480i;
                *str++ = '4';
                *str++ = '8';
                *str++ = '0';
                *str++ = CHAR_i;
                *str = 0;
                break;
            case SIG_PAL:
            case SIG_PAL_M:
            case SIG_PAL_NC:
            case SIG_SECAM:
                //u16TempID = en_str_resolution_576i;
                *str++ = '5';
                *str++ = '7';
                *str++ = '6';
                *str++ = CHAR_i;
                *str = 0;
                break;
            default:
                return NULL;
        }
    #endif
        return CHAR_BUFFER;
    }

    return NULL;
}

#if (ENABLE_DTV_EPG)
U16 MApp_GetGenreTypeString(U8 u8NibbleLevel1, U8 u8NibbleLevel2)
{
    BOOLEAN isUKCountry, isAUCountry;

  #if (ENABLE_SBTVD_CM_APP==0)
    if ( IS_DTG_COUNTRY(OSD_COUNTRY_SETTING) && (msAPI_SRC_IS_SBTVD_InUse()) )
    {
        isUKCountry = 1;
    }
    else
  #endif
    {
        isUKCountry = 0;
    }

    if( IS_NOT_MHEG5_COUNTRY(OSD_COUNTRY_SETTING) )
    {
        isAUCountry = 1;
    }
    else
    {
        isAUCountry = 0;
    }

    switch ( u8NibbleLevel1 )
    {
        case 0x1:
		#if(ENABLE_EWS)
            if(u8NibbleLevel2 == 0x6)
            {
                return en_str_romance;
            }
            else
		#endif
            {
                return ( isUKCountry == 1 ?  en_str_Movie :  en_str_MovieslashDrama );
            }
            break;
        case 0x2:
            // Fix Mantis 1375618.  Genre no need to ENABLE EWS
            if(isUKCountry ==1)
                return en_str_News_and_Factual;
            else
            {
                if(u8NibbleLevel2 == 0x3)
                {
                    return en_str_documentary;
                }
                else
                {
                    return en_str_NewsshashCurrent_Affairs;
                }

            }
            break;
        case 0x3:
            if( u8NibbleLevel2 == 0x3)
            {
                return ( isUKCountry == 1 ?  en_str_Entertainment :  en_str_ScienceslashTalkShow );
            }
            else
            {
                return ( isUKCountry == 1 ?  en_str_Entertainment :  en_str_ShowslshGame_Show );
            }
            break;
        case 0x4:
            return (isUKCountry == 1  ?  en_str_Sport :  en_str_Sports);
            break;
        case 0x5:
            return ( isUKCountry == 1 ?  en_str_Childrens :  en_str_Childrens_Youth_Programs );
            break;
        case 0x6:
            return ( isUKCountry == 1 ?  en_str_Entertainment :  en_str_MusicslashBalletslashDance );
            break;
        case 0x7:
            return ( isUKCountry == 1 ?  en_str_News_and_Factual :  en_str_Genre_0x70_Text );
            break;
        case 0x8:
            if( isUKCountry )
            {
                return en_str_News_and_Factual;
            }
            else if( isAUCountry )
            {
                return en_str_Current_affairs;
            }
            else
            {
                return en_str_SocialshashPolitical_IssuesslashEconomics;
            }
            break;
        case 0x9:
            if( isUKCountry )
            {
                return en_str_Education;
            }
            else if( isAUCountry )
            {
                return en_str_Education_information;
            }
            else
            {
                return en_str_EducationshshScienceslashslashFactual_Topics;
            }
            break;
        case 0xa:
            if( isUKCountry )
            {
                return en_str_Lifestyle;
            }
            else if( isAUCountry )
            {
                return en_str_Infotainment;
            }
            else
            {
                return en_str_Leisure_Hobbies;
            }
            break;
        case 0xb:
            if( isUKCountry )
            {
                return en_str_Not_Supported;
            }
            else if( isAUCountry )
            {
                return en_str_Special;
            }
            else
            {
                return en_str_Special_Characteristics;
            }
            break;
        case 0xc:
            if( isUKCountry )
            {
                return en_str_Not_Supported;
            }
            else if( isAUCountry )
            {
                return en_str_Comedy;
            }
            else
            {
                return en_str_Reserved_for_future_use;
            }
            break;
        case 0xd:
            if( isUKCountry )
            {
                return en_str_Not_Supported;
            }
            else if( isAUCountry )
            {
                return en_str_Drama;
            }
            else
            {
                return en_str_Reserved_for_future_use;
            }
            break;
        case 0xe:
            if( isUKCountry )
            {
                return en_str_Not_Supported;
            }
            else if( isAUCountry )
            {
                return en_str_Documentary;
            }
            else
            {
                return en_str_Reserved_for_future_use;
            }
            break;
        case 0xf:
            return ( isUKCountry == 1 ?  en_str_Drama :  en_str_Reserved_for_future_use );
            break;
        default:
            return Empty;
            break;
    }

}
#endif


static U16 _MApp_ZUI_ACT_GetEventInfoGenreStringID(void)
{
#if (ENABLE_DTV_EPG)
    MS_EIT_CUR_EVENT_PF astEventInfo[2];

    if (MApp_EIT_GetCurPFInfo(astEventInfo) == FALSE
  #if(!DVB_T_C_DIFF_DB)
	 ||((DB_PROGRAM_SOURCE_TYPE != UI_INPUT_SOURCE_TYPE) && (UI_INPUT_SOURCE_ATV != UI_INPUT_SOURCE_TYPE))
  #endif
    )
        return Empty;

    return MApp_GetGenreTypeString(astEventInfo[bNextEvent].u8Content_nibble_level1, astEventInfo[bNextEvent].u8Content_nibble_level2);

    //printf("nibble=%x\n",astEventInfo[bNextEvent].u8Content_nibble_level1);
#else
    return Empty;
#endif
}

/*
static U16 _MApp_ZUI_ACT_GetUIInputSourceStringID(E_UI_INPUT_SOURCE src)
{
    U16 u16TempID = Empty;
    //from function SourceTypeText():
    {
        switch(src)
        {
            case UI_INPUT_SOURCE_RGB:
                u16TempID= en_str_PCdashRGB;
                break;
            case UI_INPUT_SOURCE_DTV:
                u16TempID=en_str_DTV;
                break;
            case UI_INPUT_SOURCE_ATV:
                u16TempID=en_str_ATV;
                break;

            #if (INPUT_AV_VIDEO_COUNT == 1)
            case UI_INPUT_SOURCE_AV:
                u16TempID=en_str_AV;
                break;
            #elif (INPUT_AV_VIDEO_COUNT >= 2)
            case UI_INPUT_SOURCE_AV:
                u16TempID=en_str_AV_1;
                break;
            case UI_INPUT_SOURCE_AV2:
                u16TempID=en_str_AV_2;
                break;
            #endif
            #if (INPUT_AV_VIDEO_COUNT >= 3)
            case UI_INPUT_SOURCE_AV3:
                u16TempID=en_str_AV_3;
                break;
            #endif

            #if (INPUT_SV_VIDEO_COUNT == 1)
            case UI_INPUT_SOURCE_SVIDEO:
                u16TempID=en_str_SdashVideo;
                break;
            #endif
            #if ((INPUT_SCART_USE_SV2 == 0) && (INPUT_SV_VIDEO_COUNT >= 2))
            case UI_INPUT_SOURCE_SVIDEO:
                u16TempID=en_str_SdashVideo_1;
                break;
            case UI_INPUT_SOURCE_SVIDEO2:
                u16TempID=en_str_SdashVideo_2;
                break;
            #endif

            #if (INPUT_YPBPR_VIDEO_COUNT >= 1)
            case UI_INPUT_SOURCE_COMPONENT:
                u16TempID=en_str_Component1;
                break;
            #endif
            #if (INPUT_YPBPR_VIDEO_COUNT >= 2)
            case UI_INPUT_SOURCE_COMPONENT2:
                u16TempID=en_str_Component2;
                break;
            #endif
            #if   (INPUT_SCART_VIDEO_COUNT == 1)
            case UI_INPUT_SOURCE_SCART:
                u16TempID=en_str_SCART;
                break;
            #elif (INPUT_SCART_VIDEO_COUNT == 2)
            case UI_INPUT_SOURCE_SCART:
                u16TempID=en_str_SCART_1;
                break;
            case UI_INPUT_SOURCE_SCART2:
                u16TempID=en_str_SCART_2;
                break;
            #endif
        #if (INPUT_HDMI_VIDEO_COUNT == 1)
            case UI_INPUT_SOURCE_HDMI:
                u16TempID=en_str_HDMI;
                break;
        #endif
        #if (INPUT_HDMI_VIDEO_COUNT >= 2)
            case UI_INPUT_SOURCE_HDMI:
                u16TempID=en_str_HDMI1;
                break;

            case UI_INPUT_SOURCE_HDMI2:
                u16TempID=en_str_HDMI2;
                break;
        #endif
        #if (INPUT_HDMI_VIDEO_COUNT >= 3)
            case UI_INPUT_SOURCE_HDMI3:
                u16TempID=en_str_HDMI3;
                break;
        #endif
        #if (INPUT_HDMI_VIDEO_COUNT >= 4)
            case UI_INPUT_SOURCE_HDMI4:
                u16TempID=en_str_HDMI4;
                break;
        #endif

            default:
                u16TempID=en_str_DTV;
                break;
        }
    }
    return u16TempID;
}
*/
extern void _MApp_ZUI_ACT_LoadMonthString(U8 month, LPTSTR str);
extern void _MApp_ZUI_ACT_LoadWeekString(U8 month, LPTSTR str);
extern LPTSTR _MApp_ZUI_ACT_GetLocalClockTimeString(LPTSTR str);
extern LPTSTR _MApp_ZUI_ACT_GetLocalClockTimeSecString(LPTSTR str);
extern U16 _MApp_ZUI_ACT_GetLanguageStringID(EN_LANGUAGE lang, BOOLEAN bDefaultEnglish);

#if(ENABLE_S2)
#include "apiDTVSatTable.h"
extern DTVPROGRAMID_M _astS2ProgramIDTable[MAX_DTV_S2_MUX_NUMBER];

extern U8 UTL_strlen1(const char *pStr);
extern BOOLEAN _GetSatInforByID(MS_U8 u8SATId,MS_SAT_PARAM *pSATParam);

LPTSTR _GetSatelliteNameTxt(void)
{
    MS_U8 u8Str[30];

    MEMBER_SERVICETYPE bServiceType = msAPI_CM_GetCurrentServiceType();
    WORD wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);

    U16 u16CurrentS2IDIdx = msAPI_CM_GetPhysicalidx(bServiceType,wCurrentPosition);

    if( u16CurrentS2IDIdx >= MAX_DTV_S2_MUX_NUMBER )
    { // ID Table index invalid
        return MApp_ZUI_API_GetString(Empty);
    }

    DTVPROGRAMID_M stIDTable = _astS2ProgramIDTable[u16CurrentS2IDIdx];

    MS_SAT_PARAM sat;
    memset(&sat, 0x00, sizeof(MS_SAT_PARAM));
//  printf("\r\nCurrentS2idx=%d [%d]",CurrentS2idx,TP_temp.SatelliteId);
    if( FALSE == _GetSatInforByID(stIDTable.SatelliteId, &sat) )
    { // Get SAT info failed
        return MApp_ZUI_API_GetString(Empty);
    }

    if( stIDTable.SatelliteId == 1 )
    {
        strcpy((char*)u8Str,(char*)"ASTRA 1H,1KR,1L,1M");
        MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,(U8 *)u8Str, UTL_strlen1((char *)u8Str));
    }
    else
    {
        MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8 *)sat.aSatName, UTL_strlen1((char *)(sat.aSatName)));
    }

    return CHAR_BUFFER;
}

LPTSTR _GetChInfoFreqSymbolTxt(void)
{
    WORD CurrentS2idx;
    DTVPROGRAMID_M pCarrierParam;
    MS_U8 u8Str[20];

    MEMBER_SERVICETYPE bServiceType = msAPI_CM_GetCurrentServiceType();
    WORD wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);

    CurrentS2idx=msAPI_CM_GetPhysicalidx(bServiceType,wCurrentPosition);

    if(GetIDTable(CurrentS2idx, (BYTE *)&pCarrierParam, E_DATA_ID_TABLE))
    {
        if(pCarrierParam.u8Polarity)
            sprintf((char*)u8Str,"%d V %d ",pCarrierParam.u32S2Frequency, pCarrierParam.u16SymbolRate);
        else
            sprintf((char*)u8Str,"%d H %d ",pCarrierParam.u32S2Frequency, pCarrierParam.u16SymbolRate);

        MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,(U8 *)u8Str,UTL_strlen1((char*)u8Str));
        return CHAR_BUFFER;
    }
    else
    {
        return MApp_ZUI_API_GetString(Empty);
    }
}

LPTSTR _GetChInfoSignalQualityTxt(void)
{
    MS_U8 u8Str[20];

    sprintf((char*)u8Str,"Quality: %d",msAPI_Tuner_GetSignalQualityPercentage());
    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,(U8 *)u8Str,UTL_strlen1((char*)u8Str));
    return CHAR_BUFFER;
}
#endif

///////////////////////////////////////////////////////////////////////////////
///  private  MApp_ZUI_ACT_GetChannelInfoDynamicText
///  [OSD page handler] dynamic text content provider in MENU application
///
///  @param [in]       hwnd HWND     window handle we are processing
///
///  @return LPCTSTR     string content
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
LPTSTR MApp_ZUI_ACT_GetChannelInfoDynamicText(HWND hwnd)
{
    U16 u16TempID = Empty;

    //printf("\n\e[31;1m >> %s(%d) \33[m \n", __FUNCTION__, hwnd);

    switch(hwnd)
    {
    /*
        case HWND_CHINFO_BTM_PR_NOW_NEXT:
            if (bNextEvent)
                u16TempID = en_str_Now;
            else
                u16TempID = en_str_Next;
            break;
    */
        case HWND_CHINFO_EXT_CH_INPUT_TEXT:
        //#if (ENABLE_PIP)
        case HWND_CHINFO_POP_LEFT_CH_INPUT_TEXT:
        case HWND_CHINFO_POP_RIGHT_CH_INPUT_TEXT:
        //#endif
        {
            //from CURPROGRAMCHANNELTYPETEXT
        #if ENABLE_DTV
            if ( IsDTVInUse() )
            {
            #if MHEG5_ENABLE // <-<<<
                if (g_eCurrentUserServiceType == E_SERVICETYPE_DTV)
                {
                    u16TempID = en_str_DTV;
                }
                else if (g_eCurrentUserServiceType == E_SERVICETYPE_RADIO)
                {
                    u16TempID = en_str_Radio;
                }
              #if NORDIG_FUNC //for Nordig spec v2.0
                else if (g_eCurrentUserServiceType == E_SERVICETYPE_DATA)
                {
                    u16TempID = en_str_Data;
                }
              #endif

            #else
                if (msAPI_CM_GetCurrentServiceType() == E_SERVICETYPE_DTV)
                {
                #if ENABLE_SBTVD_CM_APP
                    if(msAPI_SRC_IS_SBTVD_InUse())
                    {
                        u16TempID = en_str_Air_DTV;
                    }
                    else
                #endif
                    {
                        u16TempID = en_str_DTV;
                    }
                }
                else if (msAPI_CM_GetCurrentServiceType() == E_SERVICETYPE_RADIO)
                {
                #if ENABLE_SBTVD_CM_APP
                    if(msAPI_SRC_IS_SBTVD_InUse())
                    {
                        u16TempID = en_str_Air_RADIO;
                    }
                    else
                #endif
                    {
                        u16TempID = en_str_Radio;
                    }
                }
              #if NORDIG_FUNC //for Nordig spec v2.0
                else if (msAPI_CM_GetCurrentServiceType() == E_SERVICETYPE_DATA)
                {
                    u16TempID = en_str_Data;
                }
              #endif
            #endif
            }
            else
        #endif
            if ( IsATVInUse() )
            {
            #if ENABLE_SBTVD_CM_APP
                if(msAPI_SRC_IS_SBTVD_InUse())
                {
                    if(msAPI_ATV_GetCurrentAntenna() == ANT_CATV)
                        u16TempID=en_str_CATV;
                    else
                        u16TempID=en_str_Air_TV;
                }
                else
            #endif
                {
                    u16TempID=en_str_TV;
                }
            }
            else
            {
                break; //return strNUll;
            }
        }
            break;


        case HWND_CHINFO_EXT_CH_NAME_TEXT:
        //#if (ENABLE_PIP)
        case HWND_CHINFO_POP_LEFT_CH_NAME_TEXT:
        case HWND_CHINFO_POP_RIGHT_CH_NAME_TEXT:
        //#endif

          #if ENABLE_SBTVD_CM_APP
            if(msAPI_SRC_IS_SBTVD_InUse())
            {
                if (IsATVInUse())
                {
                    u16TempID = Empty;
                }
                else
                {
                    return MApp_ZUI_GetCurrentChName(MAIN_WINDOW);
                }
            }
            else
          #endif
            {
                return MApp_ZUI_GetCurrentChName(
                  #if (ENABLE_PIP)
                    _MApp_ZUI_ACT_Channelinfo_PIP_Window_Query(MApp_Get_PIPMode(),MApp_ZUI_API_GetParent(hwnd))
                  #else
                    MAIN_WINDOW
                  #endif
                    );
            }

        break;
        case HWND_CHINFO_EXT_CH_SDHD_TEXT:
        //#if (ENABLE_PIP)
        case HWND_CHINFO_POP_LEFT_CH_SDHD_TEXT:
        case HWND_CHINFO_POP_RIGHT_CH_SDHD_TEXT:
        //#endif
        {
        #if ENABLE_DTV
            if (IsDTVInUse())
            {
                if (enFrotEndLockStatus!=FRONTEND_UNKNOWN
              #if(!DVB_T_C_DIFF_DB)
	          && (DB_PROGRAM_SOURCE_TYPE == UI_INPUT_SOURCE_TYPE)
              #endif
                )
                {
                    //from MApp_UiMenu_DrawDTV_BannerInfo()
                    //if (MApp_GetSignalStatus() == SIGNAL_LOCK)
                    {
                        /*
                        MEMBER_SERVICETYPE bServiceType;
                        AUD_INFO stAudioStreamInfo;
                        BYTE bSelectedAudStream;
                        WORD wPosition;
                        BYTE bSelected;

                        bServiceType = msAPI_CM_GetCurrentServiceType();
                        wPosition = msAPI_CM_GetCurrentPosition(bServiceType);
                        bSelectedAudStream = msAPI_CM_GetSelectedAudioStream(bServiceType, msAPI_CM_GetCurrentPosition(bServiceType));
                        msAPI_CM_GetAudioStreamInfo(bServiceType, msAPI_CM_GetCurrentPosition(bServiceType), &stAudioStreamInfo, bSelectedAudStream);
                        bSelected = msAPI_CM_GetSelectedAudioStream(bServiceType, wPosition);
                        */

                        if (E_SERVICETYPE_RADIO != msAPI_CM_GetCurrentServiceType())
                        {
                            U8 result=_MApp_ZUI_ACT_GetCurrentChannelResolutionType();
                            if (result == 1)
                            {
                                u16TempID = en_str_HD; //MApp_UiMenu_DrawMenuString0_3(EN_IDLESTRING0_ICON_HD, EN_CPSTATE_SELECT);
                            }
                            else if(result == 3)
                            {
                                break;
                            }
                            else
                            {
                                u16TempID = en_str_SD; //MApp_UiMenu_DrawMenuString0_3(EN_IDLESTRING0_ICON_SD, EN_CPSTATE_SELECT);
                            }
                        }
                    }
                }
                else
                {
                    //printf("[]lcok_fail\n");
                }
            }
        #endif
            /*
            else if (IsATVInUse())
            {
                if (enFrotEndLockStatus != FRONTEND_UNKNOWN)
                {
                    //from MApp_UiMenu_DrawATV_BannerState();
                    //printf("[]lcok_ok_a\n");
                }
                //printf("[]lcok_a\n");
            }
            else
            {
                //if (g_showChannelStatus == TRUE)
                {
                    //from MApp_UiMenu_DrawNonTV_BannerState();
                }
                //printf("[]av\n");
            }
            */
        }
        break;


        case HWND_CHINFO_EXT_CH_AUDIO_TEXT:
        //#if (ENABLE_PIP)
        case HWND_CHINFO_POP_LEFT_CH_AUDIO_TEXT:
        case HWND_CHINFO_POP_RIGHT_CH_AUDIO_TEXT:
        //#endif
        {
        #if ENABLE_DTV
            if (IsDTVInUse())
            {
                if (enFrotEndLockStatus != FRONTEND_UNKNOWN
              #if(!DVB_T_C_DIFF_DB)
	          && (DB_PROGRAM_SOURCE_TYPE == UI_INPUT_SOURCE_TYPE)
              #endif
                )
                {
                    //from MApp_UiMenu_DrawDTV_BannerInfo()
                    if (MApp_GetSignalStatus() == SIGNAL_LOCK)
                    {
                        MEMBER_SERVICETYPE bServiceType;
                        AUD_INFO stAudioStreamInfo;
                        //BYTE bSelectedAudStream;
                        WORD wPosition;
                        //BYTE bSelected;

                        bServiceType = msAPI_CM_GetCurrentServiceType();
                        wPosition = msAPI_CM_GetCurrentPosition(bServiceType);
                        //bSelectedAudStream = msAPI_CM_GetSelectedAudioStream(bServiceType, msAPI_CM_GetCurrentPosition(bServiceType));
                        msAPI_CM_GetAudioStreamInfo(bServiceType, msAPI_CM_GetCurrentPosition(bServiceType), &stAudioStreamInfo, g_u8AudLangSelected);
                        //bSelected = msAPI_CM_GetSelectedAudioStream(bServiceType, wPosition);

                        AUDIOSTREAM_TYPE eAudStreamType = msAPI_CM_Get_AudStreamType_By_AudInfo(&stAudioStreamInfo);


                        //if (bdrawAudioflag)
                        {
                            if (E_AUDIOSTREAM_MPEG == eAudStreamType)
                            {
                                u16TempID = en_str_MPEG; //MApp_UiMenu_DrawMenuString0_3(EN_IDLESTRING0_ICON_DIGITAL_AUDIO, EN_CPSTATE_SELECT);
                            }
                            else if (E_AUDIOSTREAM_AC3 == eAudStreamType)
                            {
                                u16TempID = en_str_DOLBY; //MApp_UiMenu_DrawMenuString0_3(EN_IDLESTRING0_ICON_DOLBY_DIGITAL, EN_CPSTATE_SELECT);
                            }
                            else if (E_AUDIOSTREAM_INVALID != eAudStreamType)
                            {
                                LPTSTR str = CHAR_BUFFER;

                                switch (eAudStreamType)
                                {
                                    case E_AUDIOSTREAM_MPEG_AD:
                                    {
                                        str[0]= CHAR_M;
                                        str[1]= CHAR_P;
                                        str[2]= CHAR_E;
                                        str[3]= CHAR_G;
                                        str[4]= CHAR_SPACE;
                                        str[5]= CHAR_A;
                                        str[6]= CHAR_D;
                                        str[7]= 0;
                                    }
                                    break;

                                    case E_AUDIOSTREAM_MPEG4:
                                    {
                                        str[0]= CHAR_M;
                                        str[1]= CHAR_P;
                                        str[2]= CHAR_E;
                                        str[3]= CHAR_G;
                                        str[4]= CHAR_4;
                                        str[5]= 0;
                                    }
                                    break;

                                    case E_AUDIOSTREAM_AAC:
                                    {
                                        str[0]= CHAR_A;
                                        str[1]= CHAR_A;
                                        str[2]= CHAR_C;
                                        str[3]= 0;
                                    }
                                    break;

                                    case E_AUDIOSTREAM_AC3P:
                                    {
                                        str[0]= CHAR_D;
                                        str[1]= CHAR_O;
                                        str[2]= CHAR_L;
                                        str[3]= CHAR_B;
                                        str[4]= CHAR_Y;
                                        str[5]= CHAR_PLUS;
                                        str[6]= 0;
                                    }
                                    break;

                                    case E_AUDIOSTREAM_AC3_AD:
                                    {
                                        str[0]= CHAR_D;
                                        str[1]= CHAR_O;
                                        str[2]= CHAR_L;
                                        str[3]= CHAR_B;
                                        str[4]= CHAR_Y;
                                        str[5]= CHAR_SPACE;
                                        str[6]= CHAR_A;
                                        str[7]= CHAR_D;
                                        str[8]= 0;
                                    }
                                    break;

                                    case E_AUDIOSTREAM_AC3P_AD:
                                    {
                                        str[0]= CHAR_D;
                                        str[1]= CHAR_O;
                                        str[2]= CHAR_L;
                                        str[3]= CHAR_B;
                                        str[4]= CHAR_Y;
                                        str[5]= CHAR_PLUS;
                                        str[6]= CHAR_SPACE;
                                        str[7]= CHAR_A;
                                        str[8]= CHAR_D;
                                        str[9]= 0;
                                    }
                                    break;

                                    case E_AUDIOSTREAM_AACP_AD:
                                    {
                                        str[0]= CHAR_A;
                                        str[1]= CHAR_A;
                                        str[2]= CHAR_C;
                                        str[3]= CHAR_PLUS;
                                        str[4]= CHAR_SPACE;
                                        str[5]= CHAR_A;
                                        str[6]= CHAR_D;
                                        str[7]= 0;
                                    }
                                    break;

                                    case E_AUDIOSTREAM_DRA:
                                    {
                                        str[0]= CHAR_D;
                                        str[1]= CHAR_R;
                                        str[2]= CHAR_A;
                                        str[3]= 0;
                                    }
                                    break;

                                    default:
                                        return 0; //for empty string....
                                        break;
                                }

                                return CHAR_BUFFER;
                            }
                        }
                    }
                }
            }
        #endif
        }
        break;


        case HWND_CHINFO_EXT_CH_COLOR_SYS_TEXT:
      #if (ENABLE_PIP)
        case HWND_CHINFO_POP_LEFT_CH_COLOR_SYS_TEXT:
        case HWND_CHINFO_POP_RIGHT_CH_COLOR_SYS_TEXT:
      #endif

            if(IsDigitalSourceInUse() && MApp_IsSrcHasSignal(
                #if (ENABLE_PIP)
                _MApp_ZUI_ACT_Channelinfo_PIP_Window_Query(MApp_Get_PIPMode(), MApp_ZUI_API_GetParent(hwnd))
                #else
                MAIN_WINDOW
                #endif
                ))
            {
                AVD_VideoStandardType eVideoStandard;

                //printf("msAPI_ATV_GetCurrentProgramNumber()=%u\n", msAPI_ATV_GetCurrentProgramNumber());

                if(IsATVInUse())
                {
                    eVideoStandard= msAPI_ATV_GetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber());
                }
                else
                {
                    eVideoStandard = msAPI_AVD_GetVideoStandard();
                    if (eVideoStandard!=msAPI_AVD_GetStandardDetection())
                    {
                        msAPI_AVD_DetectVideoStandard(OPERATIONMETHOD_MANUALLY);
                        eVideoStandard = msAPI_AVD_GetVideoStandard();
                    }
                }

                switch( eVideoStandard )
                {
                    case E_VIDEOSTANDARD_PAL_BGHI:
                    case E_VIDEOSTANDARD_PAL_M:
                    case E_VIDEOSTANDARD_PAL_N:
                        if(!IsATVInUse())
                        {
                            u16TempID=en_str_PAL;
                        }
                        break;

                    case E_VIDEOSTANDARD_PAL_60:
                    case E_VIDEOSTANDARD_NTSC_M:
                    case E_VIDEOSTANDARD_NTSC_44:
                        if(!IsATVInUse())
                        {
                            u16TempID=en_str_NTSC;
                        }
                        break;

                    case E_VIDEOSTANDARD_SECAM:
                        if(!IsATVInUse())
                        {
                            u16TempID=en_str_SECAM;
                        }
                        break;

                    default:
                        if(!IsATVInUse())
                        {
                            u16TempID=en_str_Auto;
                        }
                        break;
                }
            }
            else
            {
                break; //return strNUll;
            }
            break;


        case HWND_CHINFO_EXT_CH_SOUND_SYS_TEXT:
      #if (ENABLE_PIP)
        case HWND_CHINFO_POP_LEFT_CH_SOUND_SYS_TEXT:
        case HWND_CHINFO_POP_RIGHT_CH_SOUND_SYS_TEXT:
      #endif
            //from case INFO_ATV_SOUNDSYSTEXT:
            if ( IsATVInUse()
               &&(!msAPI_AVD_IsVideoFormatChanged())
               &&(MApp_IsSrcHasSignal(
                      #if (ENABLE_PIP)
                        _MApp_ZUI_ACT_Channelinfo_PIP_Window_Query(MApp_Get_PIPMode(),MApp_ZUI_API_GetParent(hwnd))
                      #else
                        MAIN_WINDOW
                      #endif
                  ))
                )//Has signal
            {
                AUDIOSTANDARD_TYPE eAudioStandard;
                eAudioStandard = msAPI_AUD_GetAudioStandard();
                switch(eAudioStandard)
                {
                        case E_AUDIOSTANDARD_BG:
                        case E_AUDIOSTANDARD_BG_A2:
                        case E_AUDIOSTANDARD_BG_NICAM:
                            u16TempID=en_str_BG;
                            break;

                        case E_AUDIOSTANDARD_I:
                            u16TempID=en_str_I;
                            break;

                        case E_AUDIOSTANDARD_DK:
                        case E_AUDIOSTANDARD_DK1_A2:
                        case E_AUDIOSTANDARD_DK2_A2:
                        case E_AUDIOSTANDARD_DK3_A2:
                        case E_AUDIOSTANDARD_DK_NICAM:
                            u16TempID=en_str_DK;
                            break;

                    #if ( ENABLE_ATV_CHINA_APP|ENABLE_DTMB_CHINA_APP || ENABLE_DVB_TAIWAN_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP || (TV_SYSTEM == TV_NTSC) )
                        case E_AUDIOSTANDARD_M:
                        case E_AUDIOSTANDARD_M_BTSC:
                            u16TempID=en_str_MN;
                            break;
                    #else
                      #if(ENABLE_SBTVD_CM_APP)
                        if(msAPI_SRC_IS_SBTVD_InUse())
                        {
                            case E_AUDIOSTANDARD_M:
                            case E_AUDIOSTANDARD_M_BTSC:
                                u16TempID=en_str_MN;
                                break;
                        }
                        else
                      #endif
                        {
                            case E_AUDIOSTANDARD_L:
                                u16TempID=en_str_L;
                                break;
                        }
                    #endif


                        default:
                          #if ( ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP )
                            u16TempID=en_str_DK;
                          #else
                            u16TempID=en_str_BG;
                          #endif
                            break;
                }
            }

            break;


        case HWND_CHINFO_EXT_CH_MTS_TYPE_TEXT:
        //#if (ENABLE_PIP)
        case HWND_CHINFO_POP_LEFT_CH_MTS_TYPE_TEXT:
        case HWND_CHINFO_POP_RIGHT_CH_MTS_TYPE_TEXT:
        //#endif
            //from case INFO_ATV_MTSTEXT:
            if (IsATVInUse()&&!msAPI_AVD_IsVideoFormatChanged()&&(MApp_IsSrcHasSignal(
                #if (ENABLE_PIP)
                _MApp_ZUI_ACT_Channelinfo_PIP_Window_Query(MApp_Get_PIPMode(),MApp_ZUI_API_GetParent(hwnd))
                #else
                MAIN_WINDOW
                #endif
                )))//has signal
            {
                _preCurrentMTSType = m_eAudioMode;
                switch(m_eAudioMode)
                {
                    case E_AUDIOMODE_INVALID:
                        break; //return strNUll;

                    case E_AUDIOMODE_MONO:
                        u16TempID=en_str_Mono;
                        break;

                    case E_AUDIOMODE_FORCED_MONO:
                        u16TempID=en_str_Mono;
                        break;

                    case E_AUDIOMODE_G_STEREO:
                        u16TempID=en_str_Stereo;
                        break;

                    case E_AUDIOMODE_K_STEREO:
                        u16TempID=en_str_Stereo;
                        break;

                    case E_AUDIOMODE_MONO_SAP:
                    case E_AUDIOMODE_STEREO_SAP:
                        u16TempID=en_str_SAP;
                        break;

                    case E_AUDIOMODE_DUAL_A:
                        u16TempID=en_str_DUAL_I;
                        break;

                    case E_AUDIOMODE_DUAL_B:
                        u16TempID=en_str_DUAL_II;
                        break;

                    case E_AUDIOMODE_DUAL_AB:
                        u16TempID=en_str_DUAL_IplusII;
                        break;

                    case E_AUDIOMODE_NICAM_MONO:
                        u16TempID=en_str_NICAM_MONO;
                        break;

                    case E_AUDIOMODE_NICAM_STEREO:
                        u16TempID=en_str_NICAM_STEREO;
                        break;
                    break;

                    case E_AUDIOMODE_NICAM_DUAL_A:
                        u16TempID=en_str_NICAM_DUAL_I;
                        break;

                    case E_AUDIOMODE_NICAM_DUAL_B:
                        u16TempID=en_str_NICAM_DUAL_II;
                        break;

                    case E_AUDIOMODE_NICAM_DUAL_AB:
                        u16TempID=en_str_NICAM_DUAL_IplusII;
                        break;

                    case E_AUDIOMODE_HIDEV_MONO:
                        u16TempID=en_str_HIDEV_MONO;
                        break;

                    case E_AUDIOMODE_LEFT_LEFT:
                        u16TempID=en_str_L_plus_L;
                        break;

                    case E_AUDIOMODE_RIGHT_RIGHT:
                        u16TempID=en_str_R_plus_R;
                        break;

                    case E_AUDIOMODE_LEFT_RIGHT:
                        u16TempID=en_str_L_plus_R;
                        break;
                }
            }
            break;


        case HWND_CHINFO_EXT_CH_NUMBER_TEXT:
        //#if (ENABLE_PIP)
        case HWND_CHINFO_POP_LEFT_CH_NUMBER_TEXT:
        case HWND_CHINFO_POP_RIGHT_CH_NUMBER_TEXT:
        //#endif
            return MApp_ZUI_GetCurrentChNumber();

    #if (ENABLE_DTV_EPG)
        case HWND_CHINFO_EXT_NAME_TEXT:
        //#if (ENABLE_PIP)
        case HWND_CHINFO_POP_LEFT_NAME_TEXT:
        case HWND_CHINFO_POP_RIGHT_NAME_TEXT:
        //#endif
            return MApp_ZUI_GetCurrentEventName();


        case HWND_CHINFO_EXT_TOP_DATE_TEXT:
        {
            //from case INFO_EVENTSTARTDAYTEXT:
        #if ENABLE_DTV
            U32 u32LocalTime;
            U8 u8dayofweek;

            LPTSTR str = CHAR_BUFFER; //u8_idx = 0;
          #if 0//ENABLE_NZ_EIT_TIME_DISPLAY
            MS_EIT_CUR_EVENT_PF astEventInfo[2];
          #endif
            str[0]= 0;

            if ( IsDTVInUse()
              #if 0//ENABLE_NZ_EIT_TIME_DISPLAY
               && (MApp_EIT_GetCurPFInfo(astEventInfo))
               && (MApp_Dmx_EIT_Get_CurPfVer()!=INVALID_VERSION_NUM)
              #endif
               )
            {
              #if 0//ENABLE_NZ_EIT_TIME_DISPLAY
                if ( (IS_DTG_COUNTRY(OSD_COUNTRY_SETTING)==FALSE)
                   ||(astEventInfo[bNextEvent].start_time[0] != 0
                   || astEventInfo[bNextEvent].start_time[1] != 0
                   || astEventInfo[bNextEvent].start_time[2] != 0
                   || astEventInfo[bNextEvent].start_time[3] != 0
                   || astEventInfo[bNextEvent].start_time[4] != 0)
                   )
              #endif
                {
                  #if 0//ENABLE_NZ_EIT_TIME_DISPLAY
                    BOOLEAN bDayLightTime,bGotTOT;
                    if(IS_DTG_COUNTRY(OSD_COUNTRY_SETTING))
                        u32LocalTime = MApp_MJDUTC2Seconds(astEventInfo[bNextEvent].start_time)+ MApp_SI_Get_OffsetTime(MApp_MJDUTC2Seconds(astEventInfo[bNextEvent].start_time),&bDayLightTime,&bGotTOT,TRUE);
                    else
                        u32LocalTime = MApp_GetLocalSystemTime();

                    printf(">>bDayLightTime  %bu\n",bDayLightTime);
                  #else
                    u32LocalTime = MApp_GetLocalSystemTime();
                  #endif

                    MApp_ConvertSeconds2StTime((U32)u32LocalTime, &_stDate);

                    u8dayofweek = MApp_GetDayOfWeek(_stDate.u16Year, _stDate.u8Month, _stDate.u8Day);
                    _MApp_ZUI_ACT_LoadWeekString(u8dayofweek, str);
                    str += MApp_ZUI_API_Strlen(str);
                    *str++ = CHAR_SPACE;

                    _MApp_ZUI_ACT_LoadMonthString(_stDate.u8Month-1, str);
                    str += MApp_ZUI_API_Strlen(str);
                    *str++ = CHAR_SPACE;

                    __MApp_UlongToString((U32)_stDate.u8Day, str, 2);
                    str += 2;
                    *str++ = CHAR_SPACE;

                    __MApp_UlongToString((U32)_stDate.u16Year, str, 4);
                    str += 4;
                    *str = 0;

                  #if 0
                    printf("\e[31;1m u8dayofweek : %d \33[m \n", u8dayofweek);
                    printf("\e[31;1m u32LocalTime: %d \33[m \n", u32LocalTime);
                    printf("\e[31;1m YY/MM/DD    : %4d/%2d/%2d \33[m \n", _stDate.u16Year, _stDate.u8Month, _stDate.u8Day);
                    printf("\e[31;1m Hour/Min/Sec: %2d:%2d:%2d \33[m \n", _stDate.u8Hour, _stDate.u8Min, _stDate.u8Sec);
                  #endif
                }
            }
        #endif // #if ENABLE_DTV

            return CHAR_BUFFER;
        }
        break;

        case HWND_CHINFO_EXT_TIME_START_TEXT:
        //#if (ENABLE_PIP)
        case HWND_CHINFO_POP_LEFT_TIME_START_TEXT:
        case HWND_CHINFO_POP_RIGHT_TIME_START_TEXT:
        //#endif
            //from case INFO_EVENTSTARTTEXT:
        {
        #if ENABLE_DTV
            U32 u32StartTime;
            LPTSTR str = CHAR_BUFFER; //u8_idx = 0;
            MS_EIT_CUR_EVENT_PF astEventInfo[2];
            str[0] = 0; //p_string_buffer[0]= 0;

            //if(MApp_EpgDB_GetCurEvent(&g_stCurEvent)&&IsDTVInUse())
            if (  (MApp_EIT_GetCurPFInfo(astEventInfo))
               && (MApp_Dmx_EIT_Get_CurPfVer()!=INVALID_VERSION_NUM)
               && IsDTVInUse()
             #if(!DVB_T_C_DIFF_DB)
	        && (DB_PROGRAM_SOURCE_TYPE == UI_INPUT_SOURCE_TYPE)
             #endif
               )
            {
                if (astEventInfo[bNextEvent].start_time[0] != 0 || astEventInfo[bNextEvent].start_time[1] != 0 ||
                    astEventInfo[bNextEvent].start_time[2] != 0 || astEventInfo[bNextEvent].start_time[3] != 0 ||
                    astEventInfo[bNextEvent].start_time[4] != 0 )
                {
                  #if ENABLE_NZ_EIT_TIME_DISPLAY
                    BOOLEAN bDayLightTime,bGotTOT;
                    if ((IS_DTG_COUNTRY(OSD_COUNTRY_SETTING))||(OSD_COUNTRY_SETTING==OSD_COUNTRY_NETHERLANDS))
                        u32StartTime = MApp_MJDUTC2Seconds(astEventInfo[bNextEvent].start_time)+ MApp_SI_Get_OffsetTime(MApp_MJDUTC2Seconds(astEventInfo[bNextEvent].start_time),&bDayLightTime,&bGotTOT,TRUE);
                    else
                        u32StartTime = MApp_MJDUTC2Seconds(&(astEventInfo[bNextEvent].start_time[0]))+ msAPI_Timer_GetOffsetTime();
                  #else
                    u32StartTime = MApp_MJDUTC2Seconds(&(astEventInfo[bNextEvent].start_time[0]))+ msAPI_Timer_GetOffsetTime();
                  #endif

                    MApp_ConvertSeconds2StTime((U32)u32StartTime, &_stDate);

                  #if 0
                    printf("\e[31;1m u32StartTime: %d \33[m \n", u32StartTime);
                    printf("\e[31;1m YY/MM/DD    : %4d/%2d/%2d \33[m \n", _stDate.u16Year, _stDate.u8Month, _stDate.u8Day);
                    printf("\e[31;1m Hour/Min/Sec: %2d:%2d:%2d \33[m \n", _stDate.u8Hour, _stDate.u8Min, _stDate.u8Sec);
                  #endif

                    __MApp_UlongToString((U32)_stDate.u8Hour, str, 2);
                    str += 2;
                    *str++ = CHAR_COLON;
                    __MApp_UlongToString((U32)_stDate.u8Min, str, 2);
                    str += 2;
                    *str++ = CHAR_COLON;
					__MApp_UlongToString((U32)_stDate.u8Sec, str, 2);
					str += 2;
                    *str++ = CHAR_SPACE;
                    *str++ = CHAR_MINUS;
                    *str = 0;

                    //ZUI_TODO: m_u8EventStarMinute = stDate.u8Min;
                    //ZUI_TODO: m_u8EventStarHour =stDate.u8Hour;
               }
            }
        #endif // #if ENABLE_DTV

            return CHAR_BUFFER; //p_string_buffer;
        }
        break;


        case HWND_CHINFO_EXT_TIME_END_TEXT:
        //#if (ENABLE_PIP)
        case HWND_CHINFO_POP_LEFT_TIME_END_TEXT:
        case HWND_CHINFO_POP_RIGHT_TIME_END_TEXT:
        //#endif
            //from case INFO_EVENTENDTIMETEXT:
        {
        #if ENABLE_DTV

            U32 u32StartTime;
            U32 u32EndTime;
            LPTSTR str = CHAR_BUFFER; //u8_idx = 0;
            MS_EIT_CUR_EVENT_PF astEventInfo[2];
            str[0] = 0; //p_string_buffer[0]= 0;

            //if(MApp_EpgDB_GetCurEvent(&g_stCurEvent)&&IsDTVInUse())
            if (  (MApp_EIT_GetCurPFInfo(astEventInfo))
               && (MApp_Dmx_EIT_Get_CurPfVer()!=INVALID_VERSION_NUM)
               && IsDTVInUse()
             #if(!DVB_T_C_DIFF_DB)
	        && (DB_PROGRAM_SOURCE_TYPE == UI_INPUT_SOURCE_TYPE)
             #endif
               )
            {
                if (astEventInfo[bNextEvent].start_time[0] != 0 || astEventInfo[bNextEvent].start_time[1] != 0 ||
                    astEventInfo[bNextEvent].start_time[2] != 0 || astEventInfo[bNextEvent].start_time[3] != 0 ||
                    astEventInfo[bNextEvent].start_time[4] != 0 )
                {
                  #if ENABLE_NZ_EIT_TIME_DISPLAY
                    BOOLEAN bDayLightTimeStart,bDayLightTimeEnd,bGotTOT;
                    if ((IS_DTG_COUNTRY(OSD_COUNTRY_SETTING))||(OSD_COUNTRY_SETTING==OSD_COUNTRY_NETHERLANDS))
                    {
                        u32StartTime = MApp_MJDUTC2Seconds(astEventInfo[bNextEvent].start_time);
                        u32StartTime += MApp_SI_Get_OffsetTime(u32StartTime,&bDayLightTimeStart,&bGotTOT,TRUE);
                        u32EndTime = MApp_MJDUTC2Seconds(astEventInfo[bNextEvent].start_time) + MApp_UTC2Seconds(astEventInfo[bNextEvent].duration);
                        u32EndTime += MApp_SI_Get_OffsetTime(u32EndTime,&bDayLightTimeEnd,&bGotTOT,FALSE);
                    }
                    else
                    {
                        u32StartTime = MApp_MJDUTC2Seconds(&(astEventInfo[bNextEvent].start_time[0]))+ msAPI_Timer_GetOffsetTime();
                        u32EndTime = u32StartTime + MApp_UTC2Seconds(astEventInfo[bNextEvent].duration);
                    }
                  #else
                    u32StartTime = MApp_MJDUTC2Seconds(&(astEventInfo[bNextEvent].start_time[0]))+ msAPI_Timer_GetOffsetTime();
                    u32EndTime = u32StartTime + MApp_UTC2Seconds(astEventInfo[bNextEvent].duration);
                  #endif

                    MApp_ConvertSeconds2StTime((U32)u32EndTime, &_stDate);

                  #if 0
                    printf("\e[31;1m u32EndTime  : %d \33[m \n", u32EndTime);
                    printf("\e[31;1m YY/MM/DD    : %4d/%2d/%2d \33[m \n", _stDate.u16Year, _stDate.u8Month, _stDate.u8Day);
                    printf("\e[31;1m Hour/Min/Sec: %2d:%2d:%2d \33[m \n", _stDate.u8Hour, _stDate.u8Min, _stDate.u8Sec);
                  #endif

                    __MApp_UlongToString((U32)_stDate.u8Hour, str, 2);
                    str += 2;
                    *str++ = CHAR_COLON;
                    __MApp_UlongToString((U32)_stDate.u8Min, str, 2);
                    str += 2;
                    *str++ = CHAR_COLON;
					__MApp_UlongToString((U32)_stDate.u8Sec, str, 2);
                    str += 2;
                    *str = 0;

                    //ZUI_TODO: m_u32EventTimeDuration = MApp_UTC2Seconds(astEventInfo[bNextEvent].duration);
                }
            }

        #endif
            return CHAR_BUFFER; //p_string_buffer;
        }
        break;

    #endif  //#if (ENABLE_DTV_EPG)


        case HWND_CHINFO_EXT_TOP_TIME_TEXT:
        //#if (ENABLE_PIP)
        case HWND_CHINFO_POP_LEFT_TIME_TEXT:
        case HWND_CHINFO_POP_RIGHT_TIME_TEXT:
        //#endif
        {
            LPTSTR str = CHAR_BUFFER;
            str = _MApp_ZUI_ACT_GetLocalClockTimeString(str);
            str = _MApp_ZUI_ACT_GetLocalClockTimeSecString(str);
            *str = 0;
            return CHAR_BUFFER;
        }


    #if (ENABLE_DTV_EPG)
        case HWND_CHINFO_EXT_CONTENT_TEXT:
                //from case INFO_EVENTEXTENDEDTEXT:
        {
        #if MHEG5_ENABLE // <-<<<
            if(  g_eCurrentUserServiceType != g_eCurrentRealServiceType
                || (g_eCurrentRealServiceType == E_SERVICETYPE_DTV && g_wCurrentTVUserServicePosition != g_wCurrentTVRealServicePosition)
                || (g_eCurrentRealServiceType == E_SERVICETYPE_RADIO && g_wCurrentRadioUserServicePosition != g_wCurrentRadioRealServicePosition)
              #if NORDIG_FUNC //for Nordig spec v2.0
                || (g_eCurrentRealServiceType == E_SERVICETYPE_DATA && g_wCurrentDataUserServicePosition != g_wCurrentDataRealServicePosition)
              #endif
                )
            {
                u16TempID = en_str_No_Program_Information;
                break;
            }
        #endif

            if ( (MApp_EIT_IsCurPFInfoExist())
               &&(IsDTVInUse() && MApp_Dmx_EIT_Get_CurPfVer() != INVALID_VERSION_NUM)
             #if(!DVB_T_C_DIFF_DB)
	        && (DB_PROGRAM_SOURCE_TYPE == UI_INPUT_SOURCE_TYPE)
             #endif
               )
            {
                if ( u8InfoScrollLineCount == 0 )
                {
                    au16EventTextScrollLineInx[0] = 0;
                }
                else
                {
                    if ( u8InfoScrollLineCount > u8InfoScrollLineCount_Pre )
                    {
                        au16EventTextScrollLineInx[u8InfoScrollLineCount] = au16EventTextScrollLineInx[u8InfoScrollLineCount - 1] + u16NextLineStartInx;
                        //printf("r -u16NextLineStartInx = %u \n", u16NextLineStartInx);
                        u8InfoScrollLineCount_Pre = u8InfoScrollLineCount;
                    }
                }

               if ( bNextEvent )
                {
                    MApp_EIT_GetPfString(NEXT,(U8*)CHAR_BUFFER,(au16EventTextScrollLineInx[u8InfoScrollLineCount]*2),1024);
                }
                else
                {
                    MApp_EIT_GetPfString(NOW,(U8*)CHAR_BUFFER,(au16EventTextScrollLineInx[u8InfoScrollLineCount]*2),1024);
                }

                if ( CHAR_BUFFER[0] != 0 )
                {
                    MApp_EIT_Reset_Cur_PF_Change();
                    return CHAR_BUFFER;
                }
            }

            // for DVB-T2 guidance descriptor
            if (IsDTVInUse()
          #if(!DVB_T_C_DIFF_DB)
	         && (DB_PROGRAM_SOURCE_TYPE == UI_INPUT_SOURCE_TYPE)
          #endif
                )
            {
                MEMBER_SERVICETYPE enServiceType = msAPI_CM_GetCurrentServiceType();
                WORD wPos = msAPI_CM_GetCurrentPosition(enServiceType);
                WORD wONID = msAPI_CM_GetON_ID(enServiceType, wPos);
                WORD wTSID = msAPI_CM_GetTS_ID(enServiceType, wPos);
                WORD wSID = msAPI_CM_GetService_ID(enServiceType, wPos);
                U16 u16Len;
                if (MApp_SI_GetServiceGuidanceInfoTextWithIDs(wONID, wTSID, wSID, (U16 *)CHAR_BUFFER, &u16Len, 1024))
                {
                    if (u16Len>0)
                    {
                        return CHAR_BUFFER;
                    }
                }
            }
            u16TempID=en_str_No_Program_Information;
        }
        break;
    #endif  //#if (ENABLE_DTV_EPG)


        case HWND_CHINFO_EXT_VIDEO_TYPE_TEXT:
        #if ENABLE_DTV
            if (IsDTVInUse() && E_SERVICETYPE_RADIO != msAPI_CM_GetCurrentServiceType()
          #if(!DVB_T_C_DIFF_DB)
	        && (DB_PROGRAM_SOURCE_TYPE == UI_INPUT_SOURCE_TYPE)
          #endif
                )
        #endif
            {
                if (msAPI_VID_GetCodecType() == E_VDEC_CODEC_TYPE_H264)
                {
                    LPTSTR str = CHAR_BUFFER; //u8_idx = 0;
                    str[0]= CHAR_H;
                    str[1]= CHAR_2;
                    str[2]= CHAR_6;
                    str[3]= CHAR_4;
                    str[4]= 0;

                    return CHAR_BUFFER;
                }
            #if( CHIP_SUPPORT_HEVC )//IMPLEMENT_DTV_H265
                else if (msAPI_VID_GetCodecType() == E_VDEC_CODEC_TYPE_HEVC)
                {
                    LPTSTR str = CHAR_BUFFER; //u8_idx = 0;
                    str[0]= CHAR_H;
                    str[1]= CHAR_2;
                    str[2]= CHAR_6;
                    str[3]= CHAR_5;
                    str[4]= 0;

                    return CHAR_BUFFER;
                }
            #endif
                else if (msAPI_VID_GetCodecType() == E_VDEC_CODEC_TYPE_AVS)
                {
                    LPTSTR str = CHAR_BUFFER; //u8_idx = 0;
                    str[0]= CHAR_A;
                    str[1]= CHAR_V;
                    str[2]= CHAR_S;
                    str[3]= 0;

                    return CHAR_BUFFER;
                }
                else if (msAPI_VID_GetCodecType() == E_VDEC_CODEC_TYPE_MPEG2)
                {
                    u16TempID = en_str_MPEG;
                }
            }
            break;

        case HWND_CHINFO_EXT_VIDEO_RES_TEXT:
        #if ENABLE_DTV
            if (E_SERVICETYPE_RADIO != msAPI_CM_GetCurrentServiceType()
          #if(!DVB_T_C_DIFF_DB)
	        && (DB_PROGRAM_SOURCE_TYPE == UI_INPUT_SOURCE_TYPE)
          #endif
               )
        #endif
            {
                return _MApp_ZUI_ACT_GetInputSourceResolution(MAIN_WINDOW);
            }

            break;


    #if (ENABLE_DTV_EPG)
        case HWND_CHINFO_EXT_AGE_TEXT:
        //#if (ENABLE_PIP)
        case HWND_CHINFO_POP_LEFT_AGE_TEXT:
        case HWND_CHINFO_POP_RIGHT_AGE_TEXT:
            {
#if ENABLE_PVR
            if (E_PVR_STATE_PLAYBACK == MApp_PVR_StateMachineGet() &&  E_PLAYBACK_STATE_PLAYBACKING== MApp_Playback_StateMachineGet())
            {
                    if(MApp_Playback_GetParentRating() > PARENTAL_RATE_SHIFT)
                    {
                            if (MApp_Playback_GetParentRating() < (0x10 + PARENTAL_RATE_SHIFT) && MApp_Playback_GetParentRating() > (0x00 + PARENTAL_RATE_SHIFT))
                            {
                                LPTSTR str = CHAR_BUFFER;
                                MApp_ZUI_API_LoadString(en_str_Age, str);
                                str += MApp_ZUI_API_Strlen(str);
                                *str++ = CHAR_SPACE;
                                __MApp_UlongToString(MApp_Playback_GetParentRating(), str, 2);
                                return CHAR_BUFFER;
                            }
                    }
            }
            else
#endif
            {
                MS_EIT_CUR_EVENT_PF astEventInfo[2];
            //#endif
                //from function MApp_UiMenu_DrawDTV_ParentalRating()
                if(MApp_EIT_GetCurPFInfo(astEventInfo)
              #if(!DVB_T_C_DIFF_DB)
	          && (DB_PROGRAM_SOURCE_TYPE == UI_INPUT_SOURCE_TYPE)
              #endif
                   )
                {
                    if(astEventInfo[bNextEvent].u8Parental_Control > PARENTAL_RATE_SHIFT)
                    {
                        //from case EN_DNUM_PARENTAL_RATING_NUMBER:
                        if(!IsATVInUse())
                        {
                            if (astEventInfo[bNextEvent].u8Parental_Control < (0x10 + PARENTAL_RATE_SHIFT) && astEventInfo[bNextEvent].u8Parental_Control > (0x00 + PARENTAL_RATE_SHIFT))
                            {
                                //return astEventInfo[bNextEvent].u8Parental_Control;
                                LPTSTR str = CHAR_BUFFER;
                                MApp_ZUI_API_LoadString(en_str_Age, str);
                                str += MApp_ZUI_API_Strlen(str);
                                *str++ = CHAR_SPACE;
                                __MApp_UlongToString(astEventInfo[bNextEvent].u8Parental_Control, str, 2);
                                return CHAR_BUFFER;
                            }
                            //else
                            //    return 0;
                        }

                    }
                  #if  ENABLE_SBTVD_CM_APP
                    else if(astEventInfo[bNextEvent].u8Parental_Control == 0x01)
                    {
                        if(IsATVInUse())
                        {
                            //return 0;
                        }
                        else
                        {
                            //TODO , maybe it need to display free for ISDB spec
                        }
                    }
                  #endif
                    }
                }
            }
        break;
    #endif  //#if (ENABLE_DTV_EPG)


        case HWND_CHINFO_EXT_GENRE_TEXT:
        //#if (ENABLE_PIP)
        case HWND_CHINFO_POP_LEFT_GENRE_TEXT:
        case HWND_CHINFO_POP_RIGHT_GENRE_TEXT:
        //#endif
        #if ((ATSC_CC == ATV_CC) || ENABLE_ISDB_ATV_VCHIP)
            #if ENABLE_SBTVD_ATV_SYSTEM
            if(IS_SBTVD_APP && IsATVInUse())
            #else
            if(IsATVInUse())
            #endif
            {
                U8 buf[64];
                U16 u16Len = 0;

                if (g_stVChipRatingInfo.RatingType >= VCHIP_RATING_TYPE_TV && g_stVChipRatingInfo.RatingType <= VCHIP_RATING_TYPE_CANADA_FRE)
                {
                    u16Len = UiMenuStr_GetVChip1RatingString(buf);
    				MApp_U8StringToU16String(buf, CHAR_BUFFER, u16Len);
                }
                CHAR_BUFFER[u16Len] = NULL;
                return CHAR_BUFFER;
            }
            else
        #endif
        #if (ENABLE_CI_PLUS)
            if(MApp_CI_IsOpMode()==TRUE)
            {
               U8 u8ContentByte;
               MS_EIT_CUR_EVENT_PF astEventInfo[2];
               MApp_EIT_GetCurPFInfo(astEventInfo);
               u8ContentByte = ((astEventInfo[bNextEvent].u8Content_nibble_level1 << 4)|astEventInfo[bNextEvent].u8Content_nibble_level2);
               if(TRUE==MApp_CI_CompareCIContentByte(u8ContentByte,CHAR_BUFFER,STRING_BUFFER_LENGTH))
               {
                  return CHAR_BUFFER;
               }
               else
               {
                  u16TempID = _MApp_ZUI_ACT_GetEventInfoGenreStringID();
               }
            }
            else
        #endif
            {
                u16TempID = _MApp_ZUI_ACT_GetEventInfoGenreStringID();
            }
            break;


    #if ENABLE_SUBTITLE
        case HWND_CHINFO_EXT_SUBTITLE_TEXT:
        //#if (ENABLE_PIP)
        case HWND_CHINFO_POP_LEFT_SUBTITLE_TEXT:
        case HWND_CHINFO_POP_RIGHT_SUBTITLE_TEXT:
        //#endif
            //from function MApp_UiMenu_DrawProgramBriefInfo()
        #if ENABLE_DTV
            if ( IsDTVInUse() && _MApp_ZUI_ACT_IsCurrentSourceAvailable()
          #if(!DVB_T_C_DIFF_DB)
	        && (DB_PROGRAM_SOURCE_TYPE == UI_INPUT_SOURCE_TYPE)
          #endif
            )
            {
                /*Subtitle*/
                if (u8SubtitleMenuNum > 0)
                {
                    u16TempID = en_str_Subtitle;
                }
            }
        #endif
        break;
    #endif // #if ENABLE_SUBTITLE


    #if ENABLE_TTX
        case HWND_CHINFO_EXT_TELETEXT_TEXT:
        //#if (ENABLE_PIP)
        case HWND_CHINFO_POP_LEFT_TELETEXT_TEXT:
        case HWND_CHINFO_POP_RIGHT_TELETEXT_TEXT:
        //#endif
            //from function MApp_UiMenu_DrawProgramBriefInfo()
        #if ENABLE_DTV
            if ( IsDTVInUse() && _MApp_ZUI_ACT_IsCurrentSourceAvailable()
          #if(!DVB_T_C_DIFF_DB)
	        && (DB_PROGRAM_SOURCE_TYPE == UI_INPUT_SOURCE_TYPE)
          #endif
            )
            {
                //Teletext
                if (MApp_TTX_GetDefaultTTX_PID() != MSAPI_DMX_INVALID_PID && msAPI_TTX_CheckTTXSignal())
                {
                    u16TempID = en_str_Teletext;
                }

            }
        #endif // #if ENABLE_DTV
        break;
    #endif // #if ENABLE_TTX


    #if (ENABLE_S2)
        case HWND_CHINFO_EXT_S2_SATLITENAME_TEXT:
            if(IsS2InUse())
                return _GetSatelliteNameTxt();
            break;

        case HWND_CHINFO_EXT_S2_PREQ_TEXT:
            if(IsS2InUse())
                return _GetChInfoFreqSymbolTxt();
            break;

        case HWND_CHINFO_EXT_S2_SYMBOL_TEXT:
            break;

        case HWND_CHINFO_EXT_S2_SIGNAL_STRENGTH_TEXT:
            if(IsS2InUse())
                return _GetChInfoSignalQualityTxt();
            break;
    #endif


    #if MHEG5_ENABLE
        case HWND_CHINFO_EXT_MHEG_TEXT:
        //#if (ENABLE_PIP)
        case HWND_CHINFO_POP_LEFT_MHEG_TEXT:
        case HWND_CHINFO_POP_RIGHT_MHEG_TEXT:
        //#endif
            //from function MApp_UiMenu_DrawProgramBriefInfo()
            if ( IsDTVInUse() && _MApp_ZUI_ACT_IsCurrentSourceAvailable()
          #if(!DVB_T_C_DIFF_DB)
	        && (DB_PROGRAM_SOURCE_TYPE == UI_INPUT_SOURCE_TYPE)
          #endif
            )
            {
                /*MHEG*/
                if ((MApp_SI_CheckMHEG5Status() == SI_MHEG5_WITH_VIDEO) ||
                     (MApp_SI_CheckMHEG5Status() == SI_MHEG5_DATA_ONLY))
                {
                    u16TempID = en_str_MHEG5;
                }

            }
        break;
    #endif // #if MHEG5_ENABLE


        case HWND_CHINFO_EXT_AUDIO_LANG_TEXT:
        //#if (ENABLE_PIP)
        case HWND_CHINFO_POP_LEFT_AUDIO_LANG_TEXT:
        case HWND_CHINFO_POP_RIGHT_AUDIO_LANG_TEXT:
        //#endif
         #if ENABLE_DTV
            //from function MApp_UiMenu_DrawProgramBriefInfo()
            if ( IsDTVInUse() && _MApp_ZUI_ACT_IsCurrentSourceAvailable()
          #if(!DVB_T_C_DIFF_DB)
	         && (DB_PROGRAM_SOURCE_TYPE == UI_INPUT_SOURCE_TYPE)
          #endif
            )
            {
                return MApp_ZUI_ACT_GetMenuLanguageStringByIndex((EN_LANGUAGE)stGenSetting.g_SoundSetting.enSoundAudioLan1);
            }
         #endif
        break;


        case HWND_CHINFO_EXT_NARRATION_TEXT:
        //#if (ENABLE_PIP)
        case HWND_CHINFO_POP_LEFT_NARRATION_TEXT:
        case HWND_CHINFO_POP_RIGHT_NARRATION_TEXT:
        //#endif
         #if ENABLE_DTV
            //from function MApp_UiMenu_DrawProgramBriefInfo()
            if ( IsDTVInUse() && _MApp_ZUI_ACT_IsCurrentSourceAvailable()
          #if(!DVB_T_C_DIFF_DB)
	         && (DB_PROGRAM_SOURCE_TYPE== UI_INPUT_SOURCE_TYPE)
          #endif
            )
            {
                AUD_INFO stAudInfo;
                if( TRUE == msAPI_CM_GetAudioStreamInfo(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()), &stAudInfo, g_u8AudLangSelected) )
                {
                    //Narration
                    if ( (stAudInfo.aISOLangInfo[0].bAudType == SI_AUDTYPE_HEARING)
                       ||(stAudInfo.aISOLangInfo[0].bAudType == SI_AUDTYPE_VISUAL)
                       ||(stAudInfo.aISOLangInfo[0].bBroadcastMixedAD) )
                    {
                        u16TempID = en_str_Narration;
                    }
                }

            }
         #endif
            break;


        case HWND_CHINFO_PIP_SRC1_SOURCE_TYPE_TEXT:
			u16TempID = en_str_HDMI1;
			break;
        case HWND_CHINFO_POP_LEFT_SOURCE_TYPE_TEXT:
            return MApp_ZUI_GetCurrentChName(
                #if (ENABLE_PIP)
                _MApp_ZUI_ACT_Channelinfo_PIP_Window_Query(MApp_Get_PIPMode(),MApp_ZUI_API_GetParent(hwnd))
                #else
                MAIN_WINDOW
                #endif
                );
            break;


        case HWND_CHINFO_PIP_SRC1_VIDEO_RES_TEXT:
        case HWND_CHINFO_POP_LEFT_VIDEO_RES_TEXT:
        case HWND_CHINFO_POP_LEFT_TV_VIDEO_RES_TEXT:
          #if ENABLE_DTV
            if (E_SERVICETYPE_RADIO != msAPI_CM_GetCurrentServiceType())
          #endif
            {
                return _MApp_ZUI_ACT_GetInputSourceResolution(
                    #if (ENABLE_PIP)
                _MApp_ZUI_ACT_Channelinfo_PIP_Window_Query(MApp_Get_PIPMode(),MApp_ZUI_API_GetParent(hwnd))
                #else
                MAIN_WINDOW
                #endif
                    );
            }
            break;


    #if (ENABLE_PIP)
        case HWND_CHINFO_PIP_SRC2_SOURCE_TYPE_TEXT:
        case HWND_CHINFO_POP_RIGHT_SOURCE_TYPE_TEXT:
            if(IsPIPSupported())
            {
                return MApp_ZUI_GetCurrentChName(
                #if (ENABLE_PIP)
                _MApp_ZUI_ACT_Channelinfo_PIP_Window_Query(MApp_Get_PIPMode(),MApp_ZUI_API_GetParent(hwnd))
                #else
                MAIN_WINDOW
                #endif
                    );
            }
        break;

        case HWND_CHINFO_PIP_SRC2_VIDEO_RES_TEXT:
        case HWND_CHINFO_POP_RIGHT_TV_VIDEO_RES_TEXT:
        case HWND_CHINFO_POP_RIGHT_VIDEO_RES_TEXT:
            if(IsPIPSupported())
            {
              #if ENABLE_DTV
                if (E_SERVICETYPE_RADIO != msAPI_CM_GetCurrentServiceType())
              #endif
                {
                    return _MApp_ZUI_ACT_GetInputSourceResolution(
                        #if (ENABLE_PIP)
                        _MApp_ZUI_ACT_Channelinfo_PIP_Window_Query(MApp_Get_PIPMode(),MApp_ZUI_API_GetParent(hwnd))
                        #else
                        MAIN_WINDOW
                        #endif
                        );
                }
            }
        break;
    #endif // #if (ENABLE_PIP)

    }

    if (u16TempID != Empty)
        return MApp_ZUI_API_GetString(u16TempID);

    return 0; //for empty string....
}

///////////////////////////////////////////////////////////////////////////////
///  private  MApp_ZUI_ACT_GetChannelInfoDynamicValue
///  [OSD page handler] dynamic integer value provider in MENU application
///
///  @param [in]       hwnd HWND     window handle we are processing
///
///  @return S16 integer value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
S16 MApp_ZUI_ACT_GetChannelInfoDynamicValue(HWND hwnd)
{

    switch(hwnd)
    {
    #if (ENABLE_DTV_EPG)
        /*
        case HWND_CHINFO_BTM_PR_TIME_BAR:
        //from function MApp_UiMenu_Monitor_UpdateEventTime()
        if((astEventInfo[bNextEvent].start_time[0] != 0 || astEventInfo[bNextEvent].start_time[1] != 0 ||
            astEventInfo[bNextEvent].start_time[2] != 0 || astEventInfo[bNextEvent].start_time[3] != 0 ||
            astEventInfo[bNextEvent].start_time[4] != 0 ) && IsDTVInUse())
        {
            if (MApp_UTC2Seconds(astEventInfo[bNextEvent].duration) != 0)
            {
                //from function: U16 MApp_Info_Get_DurationBar_Percentage( void )
                U32 u32StartTime =0;
                U32 u32EndTime =0;
                U32 u32CurrentTime =0;
                S32 s32EventPassedTime =0; //   = (stTime.u32System - stTime.u32EventStart);
                U32 u32EventDurationTime =0; // = (stTime.u32EventEnd - stTime.u32EventStart);

                u32CurrentTime = MApp_GetLocalSystemTime();

                if( (astEventInfo) && (MApp_Dmx_EIT_Get_CurPfVer()!=INVALID_VERSION_NUM) && IsDTVInUse())
                {
                       u32StartTime = MApp_MJDUTC2Seconds(&(astEventInfo[bNextEvent].start_time[0]))+ msAPI_Timer_GetOffsetTime();
                       u32EventDurationTime=MApp_UTC2Seconds(astEventInfo[bNextEvent].duration);
                }
                s32EventPassedTime = u32CurrentTime-u32StartTime;
                u32EndTime = u32StartTime + u32EventDurationTime;

                // Draw Progress Bar
                if ( u32CurrentTime < u32StartTime )
                {
                    return 0;
                }
                else if ( (u32CurrentTime>u32EndTime) && (u32EventDurationTime>0) )
                {
                    return 100;
                }
                else if ( (s32EventPassedTime>0) && (u32EventDurationTime>0) )
                {
                    return (U16)( (s32EventPassedTime*100) / u32EventDurationTime );
                }
            }
        }

        break;
        */
    #endif


        default:
            break;

    }
    return 0; //for empty  data
}


/////////////////////////////////////////////////////////
// Customize Window Procedures

S32 MApp_ZUI_ACT_ChannelInfoRootWinProc(HWND hwnd, PMSG msg)
{
    switch(msg->message)
    {
        case MSG_PAINT:
            //printf("[Ch Info] MSG_PAINT\n");
            MApp_ZUI_API_ResetTimer(HWND_CHINFO_ROOT_PANE, 0);
            break;

        case MSG_CREATE:
        {
            MApp_ZUI_API_SetTimer(hwnd, ZUI_CHINFO_TUNER_LOCK_TIMER_ID, ZUI_CHINFO_CHECKING_PERIOD);
            MApp_ZUI_API_SetTimer(hwnd, ZUI_CHINFO_EVENT_TIME_TIMER_ID, ZUI_CHINFO_CHECKING_PERIOD);
            MApp_ZUI_API_SetTimer(hwnd, ZUI_CHINFO_VIDEO_MODE_TIMER_ID, ZUI_CHINFO_CHECKING_PERIOD);
            MApp_ZUI_API_SetTimer(hwnd, ZUI_CHINFO_AUDIO_MODE_TIMER_ID, ZUI_CHINFO_CHECKING_PERIOD);
        }
            break;

        case MSG_TIMER:
        {
            switch(msg->wParam)
            {
                case  ZUI_CHINFO_TUNER_LOCK_TIMER_ID:
                    //from MApp_UiMenu_Monitor_UpdateBannerInfo()
                  #if ENABLE_DVB
                    if( IsDVBInUse()/*IsDTVInUse()*/ )
                    {
                        if (enFrotEndLockStatus!=FRONTEND_UNKNOWN)
                        {
                            BOOL bGotVideo=TRUE;

                            if(enFrotEndLockStatus == FRONTEND_UNLOCK)
                            {
                                MApp_ZUI_API_KillTimer(hwnd, ZUI_CHINFO_TUNER_LOCK_TIMER_ID);
                                MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHINFO_ROOT_PANE);
                                break;
                            }

                            if (*MApp_Dmx_GetFid(EN_VIDEO_FID)  != MSAPI_DMX_INVALID_FLT_ID)// && msAPI_DMX_GetFilterState(*MApp_Dmx_GetFid(EN_VIDEO_FID) ) != MSAPI_DMX_FILTER_STATE_STOP)
                            {
                                BOOL bEnable=FALSE;
                                MApi_DMX_IsStart(*MApp_Dmx_GetFid(EN_VIDEO_FID),&bEnable);
                                if (bEnable)
                                {
                                    if (  (_MApp_ZUI_ACT_GetCurrentChannelResolutionType() == 3)
                                       && (MApp_SI_CheckCurProgScramble()!= TRUE) )
                                       bGotVideo=FALSE;
                                }
                            }
                            if(bGotVideo)
                            {
                                MApp_ZUI_API_KillTimer(hwnd, ZUI_CHINFO_TUNER_LOCK_TIMER_ID);
                            }
                            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHINFO_ROOT_PANE);
                        }
                    }
                    else
                  #endif
                    if (IsATVInUse())
                    {
                        if (enFrotEndLockStatus != FRONTEND_UNKNOWN)
                        {
                            MApp_ZUI_API_KillTimer(hwnd, ZUI_CHINFO_TUNER_LOCK_TIMER_ID);
                            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHINFO_ROOT_PANE);
                        }
                    }
                    else
                    {
                        MApp_ZUI_API_KillTimer(hwnd, ZUI_CHINFO_TUNER_LOCK_TIMER_ID);
                    }
                    break;

            #if (ENABLE_DTV_EPG)
                case ZUI_CHINFO_EVENT_TIME_TIMER_ID:
                //from function MApp_UiMenu_Monitor_UpdateEventTime()
                {
                    MS_EIT_CUR_EVENT_PF astEventInfo[2];

                    if ( (MApp_EIT_GetCurPFInfo(astEventInfo))
                       &&(MApp_Dmx_EIT_Get_CurPfVer() != INVALID_VERSION_NUM)
                       &&(IsDTVInUse()) )
                    {
                        if (astEventInfo[bNextEvent].start_time[0] != 0 || astEventInfo[bNextEvent].start_time[1] != 0 ||
                            astEventInfo[bNextEvent].start_time[2] != 0 || astEventInfo[bNextEvent].start_time[3] != 0 ||
                            astEventInfo[bNextEvent].start_time[4] != 0 )
                        {
                            MApp_ZUI_API_KillTimer(hwnd, ZUI_CHINFO_EVENT_TIME_TIMER_ID);
                            MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHINFO_ROOT_PANE);
                        }
                    }

                    break;
                }
            #endif  //#if (ENABLE_DTV_EPG)

                case ZUI_CHINFO_VIDEO_MODE_TIMER_ID:
                {
                    //wait until video signal ok...
                    if (_MApp_ZUI_ACT_GetInputSourceResolution(MAIN_WINDOW) != NULL)
                    {
                        MApp_ZUI_API_KillTimer(hwnd, ZUI_CHINFO_VIDEO_MODE_TIMER_ID);
                        MApp_ZUI_API_InvalidateWindow(HWND_CHINFO_EXT_VIDEO_RES_TEXT);
                        MApp_ZUI_API_InvalidateWindow(HWND_CHINFO_PIP_SRC1_VIDEO_RES_TEXT);
                        MApp_ZUI_API_InvalidateWindow(HWND_CHINFO_PIP_SRC2_VIDEO_RES_TEXT);
                    }
                    break;
                }

                case ZUI_CHINFO_AUDIO_MODE_TIMER_ID:
                {
                    //wait when audio mode changed...don't kill this timer

                    //from function MApp_UiMenu_Monitor_Update_CHANNEL_BANNER()
                    if(IsATVInUse()&&(MApp_IsSrcHasSignal(MAIN_WINDOW)))//has signal
                    {
                        if (_preCurrentMTSType != m_eAudioMode)
                        {
                            MApp_ZUI_API_InvalidateWindow(HWND_CHINFO_EXT_CH_MTS_TYPE_TEXT);
                        }
                    }
                    break;
                }

                default:
                    break;

            }
            break;
        }


        default:
            break;
    }

    return DEFAULTWINPROC(hwnd, msg);
}

void MApp_ZUI_ACT_ResetInfoTimer(void)
{
    MApp_ZUI_API_ResetTimer(HWND_CHINFO_ROOT_PANE, 0);
}

U16 MApp_ZUI_ACT_GetChannelInfoDynamicBitmap(HWND hwnd, DRAWSTYLE_TYPE ds_type)
{
    UNUSED(ds_type);
    switch(hwnd)
    {
        case HWND_CHINFO_EXT_FIRST_SRC_ICON:
          #if (ENABLE_PIP)
            if(MApp_Get_PIPMode() == EN_PIP_MODE_OFF)
            {//Case 1. Only TV banner will be shown, do not show src icon.
                break;
            }
            else
            {//Case 2. Show src icon on TV banner.
                if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
                    || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
                {
                    return E_BMP_IDLE_IMG_ICON_1;
                }
                return E_BMP_IDLE_IMG_ICON_2;
            }
          #endif
            break;

        case HWND_CHINFO_POP_FIRST_SRC_ICON:
          #if (ENABLE_PIP)
            if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
            {
                if(MApp_Get_PIPMode() == EN_PIP_MODE_PIP)
                {
                    if(stGenSetting.g_stPipSetting.enPipPosition == EN_PIP_POSITION_RIGHT_TOP ||
                          stGenSetting.g_stPipSetting.enPipPosition == EN_PIP_POSITION_RIGHT_BOTTOM)
                    {
                        return E_BMP_IDLE_IMG_ICON_1;
                    }
                    else
                    {
                        return E_BMP_IDLE_IMG_ICON_2;
                    }
                }
                return E_BMP_IDLE_IMG_ICON_1;
            }
            else
          #endif
            {
                return E_BMP_IDLE_IMG_ICON_1;
            }
            break;

        case HWND_CHINFO_POP_SECOND_SRC_ICON:
          #if (ENABLE_PIP)
            if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
            {
                if(MApp_Get_PIPMode() == EN_PIP_MODE_PIP)
                {
                    if(stGenSetting.g_stPipSetting.enPipPosition == EN_PIP_POSITION_RIGHT_TOP ||
                          stGenSetting.g_stPipSetting.enPipPosition == EN_PIP_POSITION_RIGHT_BOTTOM)
                    {
                        return E_BMP_IDLE_IMG_ICON_2;
                    }
                    else
                    {
                        return E_BMP_IDLE_IMG_ICON_1;
                    }
                }
                return E_BMP_IDLE_IMG_ICON_2;
            }
            else
          #endif
            {
                return E_BMP_IDLE_IMG_ICON_2;
            }
            break;

#if ( ENABLE_COUNTRY_SINGAPORE )
    #if ( ENABLE_SUBTITLE )
        case HWND_CHINFO_EXT_SUBTITLE_ICON:
        #if ( ENABLE_DTV )
            if( IsDTVInUse() && _MApp_ZUI_ACT_IsCurrentSourceAvailable() )
            {
                /*Subtitle*/
                if( ( u8SubtitleMenuNum > 0 )
                 && ( SubtitleMenu[u8SubtitleItemSelIdx-1].u8SubtitleType == SUBTITLING_TYPE_TELETEXT_HOH) )
                {
                    return E_BMP_IDLE_IMG_ICON_HOH;
                }
            }
        #endif  // ENABLE_DTV
            break;
    #endif  // ENABLE_SUBTITLE
#endif  // ENABLE_COUNTRY_SINGAPORE

        default:
            break;
    }
    return 0xFFFF; //for empty bitmap
}


#undef MAPP_ZUI_ACTCHANNELINFO_C

