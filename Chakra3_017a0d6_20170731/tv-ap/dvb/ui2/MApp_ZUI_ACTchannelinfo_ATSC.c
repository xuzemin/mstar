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
// (MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define MAPP_ZUI_ACTCHANNELINFO_ATSC_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "string.h"
#include "stdio.h"
#include "MsCommon.h"
#include "Utl.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_ACTglobal.h"

#include "MApp_ZUI_ACTchannelinfo_ATSC.h"
#include "MApp_GlobalSettingSt.h"
#if EN_INPUT_LABEL_EDIT
#include "MApp_ZUI_ACTinputsource.h"
#endif

#include "MApp_ZUI_ACTmainpage.h"
//#include "msAPI_Subtitle.h"
#include "msAPI_VD.h"
#include "apiXC_ModeParse.h"
#include "apiXC_PCMonitor.h"

#include "MApp_GlobalVar.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_MVDMode.h"
#include "MApp_SignalMonitor.h"
#include "MApp_ChannelChange.h"
#include "MApp_TV.h"
#include "MApp_AnalogInputs.h"
#include "MApp_GlobalFunction.h"
#include "MApp_PCMode.h"
#include "MApp_VDMode.h"
#include "MApp_AnalogInputs.h"
#include "MApp_EpgDB_ATSC.h"
#include "MApp_DataBase_ATSC.h"
#include "MApp_ChannelProc_ATSC.h"

#include "MApp_UiMenuStr_ATSC.h"
#include "MApp_UiMenuFunc_ATSC.h"
#include "drvXC_HDMI_if.h"
#include "ZUI_exefunc.h"

#include "OSDcp_String_EnumIndex.h"
#include "MApp_Psip.h"
#if (EEPROM_DB_STORAGE == EEPROM_SAVE_ALL)
#include "MApp_SaveData.h"
#endif
#include "apiGOP.h"

#if ENABLE_ATSC_TTS
#include "MApp_TTSControlHandler.h"
#include "MApp_TTS_Cus.h"
#include "MApp_TTS_Cus_Say.h"
#endif
/////////////////////////////////////////////////////////////////////

#define ZUI_CHINFO_TUNER_LOCK_TIMER_ID      0
#define ZUI_CHINFO_EVENT_TIME_TIMER_ID      1
#define ZUI_CHINFO_VIDEO_MODE_TIMER_ID      2
#define ZUI_CHINFO_AUDIO_MODE_TIMER_ID      3

#define ZUI_CHINFO_CHECKING_PERIOD              100 //ms
#define MAX_MANUALSCAN_MENU_PROGRAMNAME_LEN     26

#if ENABLE_ATSC_TTS
#define PROG_NUMBER_LEN 30
#endif

//static AUDIOMODE_TYPE _preCurrentMTSType;
extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);
//extern void _MApp_ZUI_API_DrawDynamicComponent(DRAWCOMPONENT component, const void * param, const GRAPHIC_DC * pdc, const RECT * rect);
#if EN_INPUT_LABEL_EDIT
extern U16 PresentStrTab[];
extern U16 InputLabelDefaultTable[];
#endif  //EN_INPUT_LABEL_EDIT

#if SUPPORT_LONG_ETT
LPTSTR MApp_EpgZUI_GetExtendText(
  #if ( ENABLE_ATSC_EPG_DB_2016 )
    const MS_EPG_EVENT_New *pEventNew
  #else
    MS_EPG_EVENT *pEvent
  #endif
);
#endif

static void MApp_ZUI_ACT_Indicate_Signal_Status(void)
{
    if(IsDTVInUse())
    {
        MApp_UiMenuFunc_EventInfoSignalUpdate();

        switch((u8PreSignalSNR))
        {
            case SIGNAL_NO:
                MApp_ZUI_API_EnableWindow(HWND_CHINFO_CONTENT_3RD_ROW_SIGNAL_BAR_RED,FALSE);
                MApp_ZUI_API_EnableWindow(HWND_CHINFO_CONTENT_3RD_ROW_SIGNAL_BAR_YELLOW,FALSE);
                MApp_ZUI_API_EnableWindow(HWND_CHINFO_CONTENT_3RD_ROW_SIGNAL_BAR_GREEN,FALSE);
                MApp_ZUI_API_EnableWindow(HWND_CHINFO_CONTENT_3RD_ROW_SIGNAL_BAR_BLUE,FALSE);
                break;
            case SIGNAL_WEAK:
                MApp_ZUI_API_EnableWindow(HWND_CHINFO_CONTENT_3RD_ROW_SIGNAL_BAR_RED,TRUE);
                MApp_ZUI_API_EnableWindow(HWND_CHINFO_CONTENT_3RD_ROW_SIGNAL_BAR_YELLOW,FALSE);
                MApp_ZUI_API_EnableWindow(HWND_CHINFO_CONTENT_3RD_ROW_SIGNAL_BAR_GREEN,FALSE);
                MApp_ZUI_API_EnableWindow(HWND_CHINFO_CONTENT_3RD_ROW_SIGNAL_BAR_BLUE,FALSE);
                break;
            case SIGNAL_MODERATE:
                MApp_ZUI_API_EnableWindow(HWND_CHINFO_CONTENT_3RD_ROW_SIGNAL_BAR_RED,TRUE);
                MApp_ZUI_API_EnableWindow(HWND_CHINFO_CONTENT_3RD_ROW_SIGNAL_BAR_YELLOW,TRUE);
                MApp_ZUI_API_EnableWindow(HWND_CHINFO_CONTENT_3RD_ROW_SIGNAL_BAR_GREEN,FALSE);
                MApp_ZUI_API_EnableWindow(HWND_CHINFO_CONTENT_3RD_ROW_SIGNAL_BAR_BLUE,FALSE);
                break;
            case SIGNAL_STRONG:
                MApp_ZUI_API_EnableWindow(HWND_CHINFO_CONTENT_3RD_ROW_SIGNAL_BAR_RED,TRUE);
                MApp_ZUI_API_EnableWindow(HWND_CHINFO_CONTENT_3RD_ROW_SIGNAL_BAR_YELLOW,TRUE);
                MApp_ZUI_API_EnableWindow(HWND_CHINFO_CONTENT_3RD_ROW_SIGNAL_BAR_GREEN,TRUE);
                MApp_ZUI_API_EnableWindow(HWND_CHINFO_CONTENT_3RD_ROW_SIGNAL_BAR_BLUE,FALSE);
                break;
            case SIGNAL_VERY_STRONG:
                MApp_ZUI_API_EnableWindow(HWND_CHINFO_CONTENT_3RD_ROW_SIGNAL_BAR_RED,TRUE);
                MApp_ZUI_API_EnableWindow(HWND_CHINFO_CONTENT_3RD_ROW_SIGNAL_BAR_YELLOW,TRUE);
                MApp_ZUI_API_EnableWindow(HWND_CHINFO_CONTENT_3RD_ROW_SIGNAL_BAR_GREEN,TRUE);
                MApp_ZUI_API_EnableWindow(HWND_CHINFO_CONTENT_3RD_ROW_SIGNAL_BAR_BLUE,TRUE);
                break;
            default:
                MApp_ZUI_API_EnableWindow(HWND_CHINFO_CONTENT_3RD_ROW_SIGNAL_BAR_RED,FALSE);
                MApp_ZUI_API_EnableWindow(HWND_CHINFO_CONTENT_3RD_ROW_SIGNAL_BAR_YELLOW,FALSE);
                MApp_ZUI_API_EnableWindow(HWND_CHINFO_CONTENT_3RD_ROW_SIGNAL_BAR_GREEN,FALSE);
                MApp_ZUI_API_EnableWindow(HWND_CHINFO_CONTENT_3RD_ROW_SIGNAL_BAR_BLUE,FALSE);
                break;
        }
    }
    else
    {
        MApp_ZUI_API_EnableWindow(HWND_CHINFO_CONTENT_3RD_ROW_SIGNAL_BAR,FALSE);
    }
}

BOOLEAN MApp_ZUI_ACT_IsChInfoMode(EN_CHANNEL_INFO_PAGE_TYPE CHINFO_TYPE)
{
    if (!MApp_ZUI_GetActive_ChannelInfo_OSD())
        return FALSE;

    if (enChannelInfoPageType == CHINFO_TYPE)
        return TRUE;
    else
        return FALSE;
}

void MApp_ZUI_ACT_AppShowChannelInfo_ATSC(void) //HWND sender)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_CHANNEL_INFO_ATSC;

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
        ZUI_CHANNEL_INFO_ATSC_XSTART, ZUI_CHANNEL_INFO_ATSC_YSTART,
        ZUI_CHANNEL_INFO_ATSC_WIDTH, ZUI_CHANNEL_INFO_ATSC_HEIGHT);

    if (!MApp_ZUI_API_InitGDI(&rect))
    {
        ZUI_DBG_FAIL(printf("[ZUI]GDIINIT\n"));
        ABORT();
        return;
    }

    //note: set the first invalid rect equal to gwin size
    MApp_ZUI_API_InvalidateRect(&rect);
    for (wnd = 1; wnd < HWND_MAX; wnd++)
    {
        MApp_ZUI_API_SendMessage(wnd, MSG_CREATE, 0);
    }
#if 0
    if(ZUI_ENABLE_TRANSPARENCY_SYSSETTING)
    {
        SetOsdPageBlendingValue(FALSE, (stGenSetting.g_SysSetting.Transparency*7)/100);
        MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD);
        MApi_GOP_GWIN_SetBlending(u8SlaveOSDWinId,FALSE,(stGenSetting.g_SysSetting.Transparency*7)/100);
        MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD);
        MApi_GOP_GWIN_SetBlending(MApp_ZUI_API_QueryGWinID(),FALSE,(stGenSetting.g_SysSetting.Transparency*7)/100);
    }
#endif
    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_CHINFO_TRANSPARENT, SW_SHOW);
    if(enChannelInfoPageType == TYPE_CHANNEL_INFO)
    {
        MApp_ZUI_ACT_Indicate_Signal_Status();
        MApp_ZUI_API_ShowWindow(HWND_CHINFO_BTM_EXT_PANE,SW_SHOW);

        MApp_ZUI_API_ShowWindow(HWND_CHINFO_PROG_NAME_TEXT,IsAnyTVSourceInUse());
        if(fSignalLockStatus == FE_NOT_LOCK)
        {
            MApp_ZUI_API_ShowWindow(HWND_CHINFO_CONTENT_2ND_ROW_VID_RES_ICON,SW_HIDE);
        }

        if(MApp_IsSrcHasSignal(MAIN_WINDOW))
        {
            MApp_ZUI_API_EnableWindow(HWND_CHINFO_CONTENT_1ST_ROW_CC_ICON,MApp_UiMenuFunc_IsCCEnable());
        //MApp_ZUI_API_ShowWindow(HWND_CHINFO_CONTENT_1ST_ROW_CC_INFO,MApp_UiMenuFunc_IsCCEnable());
        //MApp_ZUI_API_ShowWindow(HWND_CHINFO_CONTENT_1ST_ROW_EVENT_INFO,IsDTVInUse());
        }
        else
        {
            MApp_ZUI_API_EnableWindow(HWND_CHINFO_CONTENT_1ST_ROW_CC_ICON,FALSE);
        }

        if(IsVgaInUse() ||IsYPbPrInUse()||IsHDMIInUse())
        {
            MApp_ZUI_API_ShowWindow(HWND_CHINFO_CONTENT_1ST_ROW_CC_ICON,SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_CHINFO_CONTENT_1ST_ROW_CC_INFO,SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_CHINFO_CONTENT_1ST_ROW_EVENT_INFO,SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_CHINFO_CONTENT_3RD_ROW_TIME_TEXT,SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_CHINFO_BANNER,SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_CHINFO_CONTENT_2ND_ROW_RESOLUTION,SW_SHOW);
            if (IsHDMIInUse() && (g_HdmiPollingStatus.bIsHDMIMode != TRUE))
            {
                MApp_ZUI_API_ShowWindow(HWND_CHINFO_CONTENT_2ND_ROW_VID_RES_ICON, SW_SHOW);
            }
            else
            {
                MApp_ZUI_API_ShowWindow(HWND_CHINFO_CONTENT_2ND_ROW_VID_RES_ICON, SW_HIDE);
            }
        }
        else if(IsAVInUse())
        {
            MApp_ZUI_API_ShowWindow(HWND_CHINFO_CONTENT_1ST_ROW_EVENT_INFO,SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_CHINFO_CONTENT_3RD_ROW_TIME_TEXT,SW_HIDE);
        }
    }
    else if(enChannelInfoPageType == TYPE_CHANNEL_BANNER)
    {
         MApp_ZUI_API_ShowWindow(HWND_CHINFO_BANNER,SW_SHOW);

         MApp_ZUI_API_ShowWindow(HWND_CHINFO_BANNER_PROG_NAME,IsAnyTVSourceInUse());
         MApp_ZUI_API_ShowWindow(HWND_CHINFO_BANNER_PROG_SCRAMBLE_INFO,IsAnyTVSourceInUse());
    }
    else if(enChannelInfoPageType == TYPE_CHANNEL_DIRECT_TUNE)
    {
        MApp_ZUI_API_ShowWindow(HWND_CHINFO_DIRECT_TUNE_PANEL,SW_SHOW);
    }
}

//////////////////////////////////////////////////////////
// Key Handler

BOOLEAN MApp_ZUI_ACT_HandleChannelInfoKey_ATSC(VIRTUAL_KEY_CODE key)
{
//     MApp_ZUI_API_ResetTimer(HWND_CHINFO_BG, 0);
     MApp_ZUI_API_ResetTimer(HWND_CHINFO_TRANSPARENT, 0);

    switch(key)
    {
        case VK_EXIT:
#if ENABLE_ATSC_TTS
            MApp_TTS_Cus_Say_exit();
#endif
            MApp_ZUI_ACT_ShutdownOSD();
            return TRUE;
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
        case VK_DASH:
            MApp_ZUI_API_InvalidateWindow(HWND_CHINFO_DIRECT_TUNE_PANEL);
            return TRUE;
        case VK_SELECT:
            if(MApp_ZUI_API_IsWindowVisible(HWND_CHINFO_DIRECT_TUNE_PANEL))
            {
                MApp_ZUI_ACT_ExecuteChannelInfoAction_ATSC(EN_EXE_CLOSE_CURRENT_OSD);
                MApp_ZUI_API_KillTimer(HWND_CHINFO_TRANSPARENT, 0);
            }
            return TRUE;
        default:
            //
            break;
    }

    //UNUSED(key);
    //ZUI_DBG_FAIL(printf("[ZUI]IDLEKEY\n"));
    //ABORT();
    return FALSE;
}

void MApp_ZUI_ACT_TerminateChannelInfo_ATSC(void)
{
    ZUI_MSG(printf("Terminate ATSC Channel Info\n"));

    enChannelInfoPageType = TYPE_CHANNEL_BANNER;
#if (ATSC_READY)
  #if (ENABLE_EEPROM)
    MApp_SaveGenSetting();
  #endif
#endif

#ifdef PATCH_FOR_CHECKSUM_TEMP
  #if ENABLE_QUICK_DATABASE
    //MApp_DB_SaveGenSetting();
    MApp_DB_GEN_Set_DataChanged(TRUE);
  #endif
#endif
}


///////////////////////////////////////////////////////////////////////////////
///  private  MApp_ZUI_ACT_ExecuteChannelInfoAction_ATSC
///  [OSD page handler] execute a specific action in CHANNEL INFO application
///
///  @param [in]       act U16      action ID
///
///  @return BOOLEAN     true for accept, false for ignore
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_ZUI_ACT_ExecuteChannelInfoAction_ATSC(U16 act)
{
    switch(act)
    {
        case EN_EXE_CLOSE_CURRENT_OSD:
            if(MApp_ZUI_API_IsWindowVisible(HWND_CHINFO_DIRECT_TUNE_PANEL))
            {
            #if(ATSC_READY)
                if(IsAnyTVSourceInUse())
                    MApp_TV_ChannelChangeProc(&stVirtualChNum, (EN_ANT_TYPE)ANT_TYPE);
                else
                    MApp_AnalogInputs_ChannelChangeProc(&stVirtualChNum, (EN_ANT_TYPE)ANT_TYPE);
            #endif
                MApp_ZUI_API_ShowWindow(HWND_CHINFO_DIRECT_TUNE_PANEL,SW_HIDE);
            }

            MApp_ZUI_ACT_ShutdownOSD();
            return TRUE;
            break;

        case EN_EXE_CHINFO_DIRECT_TUNE_SHOW:
            MApp_ZUI_API_ShowWindow(HWND_CHINFO_ETT_BG, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_CHINFO_BTM_EXT_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_CHINFO_BANNER, SW_HIDE);
            MApp_ZUI_API_ShowWindow (HWND_CHINFO_DIRECT_TUNE_PANEL,SW_SHOW);
            break;

        case EN_EXE_CHINFO_ETT_INFO_SHOW:
            MApp_ZUI_API_ShowWindow(HWND_CHINFO_ETT_BG,SW_SHOW);
            break;

        case EN_EXE_CHINFO_BANNER_RESET:
            //MApp_ZUI_API_InvalidateWindow(HWND_CHINFO_BANNER);
            MApp_ZUI_API_ShowWindow(HWND_CHINFO_BANNER,SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_CHINFO_BANNER_PROG_NAME,IsAnyTVSourceInUse());
            MApp_ZUI_API_ShowWindow(HWND_CHINFO_BANNER_PROG_SCRAMBLE_INFO,IsAnyTVSourceInUse());
            MApp_ZUI_API_ResetTimer(HWND_CHINFO_TRANSPARENT, 0);
            break;

    #if (ENABLE_MESSAGE_BOX_DISPLAY_TIMING)
        case EN_EXE_CHINFO_BANNER_PROG_TIMIMG_RESET:
            MApp_ZUI_API_InvalidateWindow(HWND_CHINFO_BANNER_PROG_TIMING);
            break;
    #endif

        default:
            //
            break;
    }

 return FALSE;
}

static void MApp_ZUI_ACT_ChInfo_String_Processing(HWND hwnd, U8* SrcStr, U16* DstStr, BOOLEAN bStrIsUTF16)
{
    U16 i,length;

    if( DstStr == NULL )
    {
        return;
    }

    if( SrcStr == NULL )
    {
        DstStr[0] = 0;
        return;
    }

    switch(hwnd)
    {
        case HWND_CHINFO_CONTENT_1ST_ROW_EVENT_INFO:
        case HWND_CHINFO_ETT_TEXT:
        {
            /*
            if( MApp_EpgDB_GetCurEvent(&stEpgEventInfo) == FALSE )
            {
                return;
            }*/

        /*
            if( ((hwnd == HWND_CHINFO_CONTENT_1ST_ROW_EVENT_INFO) && stEpgEventInfo.fIsEitUTF16)
               ||((hwnd == HWND_CHINFO_ETT_TEXT) && stEpgEventInfo.fIsEttUTF16) )
               */
            if( ((hwnd == HWND_CHINFO_CONTENT_1ST_ROW_EVENT_INFO) && bStrIsUTF16)
               ||((hwnd == HWND_CHINFO_ETT_TEXT) && bStrIsUTF16) )
            {
                //The length is equal CHAR_BUFFER length
                length = STRBUFF_LENGTH_ATSC/sizeof(U16);
                for(i=0; i<length; i++)
                {
                #if ENABLE_LANGUAGE_KOREA
                    // Ray, 03302012
                    if( SrcStr[2*i] =='\0' && SrcStr[2*i+1] =='\0')
                        break;

                #else
                    if( SrcStr[2*i+1] =='\0' )
                        break;
                #endif
                    DstStr[i] = ((U16)SrcStr[2*i] << 8 | (U16)SrcStr[2*i+1]);
                }
                DstStr[i] ='\0';

            #if ENABLE_ATSC_TTS
                if (i > 0)
                {
                    MApp_TTSControlSetInputText(DstStr, i);
                    if ( stGenSetting.g_SysSetting.bTTSOn )
                        MApp_TTSControlSetOn(TRUE);
                }
            #endif
            }
            else
            {
                MApp_ZUI_API_StringBuffU8toU16(DstStr, SrcStr, strlen((char *)SrcStr));

              #if ENABLE_ATSC_TTS
                MApp_TTSControlSetInputText(DstStr, strlen((char *)SrcStr));
                if ( stGenSetting.g_SysSetting.bTTSOn )
                    MApp_TTSControlSetOn(TRUE);
              #endif
            }
        }
        break;

        default:
            MApp_ZUI_API_StringBuffU8toU16(DstStr, SrcStr, strlen((char *)SrcStr));
            break;
    }
}

LPTSTR MApp_ZUI_ACT_GetChannelInfoDynamicText_ATSC(HWND hwnd)
{
    U16 u16TempID = Empty;
    U8 *u8TempString = NULL;
    BOOLEAN bStrIsUTF16 = FALSE;


    switch(hwnd)
    {
        case HWND_CHINFO_CONTENT_3RD_ROW_SIGNAL_BAR_TEXT:
            switch((u8PreSignalSNR))
            {
                case SIGNAL_NO:
                case SIGNAL_WEAK:
                    u16TempID = en_str_Bad;
                    break;
                case SIGNAL_MODERATE:
                    u16TempID = en_str_Normal;
                    break;
                case SIGNAL_STRONG:
                case SIGNAL_VERY_STRONG:
                    u16TempID = en_str_Good;
                    break;
                default:
                    u16TempID = en_str_Bad;
                    break;
            }
            break;

        case HWND_CHINFO_PROG_NUM_TEXT:
            if (IsDTVInUse() || IsATVInUse())
            {
                u8TempString = CurProgramNumberText();
            #if ENABLE_ATSC_TTS
                if (u8TempString != NULL)
                {
                    MApp_TTSControlSetInputText(MApp_ZUI_API_GetString(en_str_Channel), MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(en_str_Channel)));

                    U8* pChnStr = malloc(PROG_NUMBER_LEN), *pSrcStr = u8TempString, idx = 0;
                    if (pChnStr != NULL)
                    {
                        memset(pChnStr, 0x0, PROG_NUMBER_LEN);
                        do
                        {
                            if ((*pSrcStr) != '.')
                            {
                                pChnStr[idx++] = *pSrcStr;
                            }
                            else
                            {
                                pChnStr[idx++] = 'P';
                                pChnStr[idx++] = 'O';
                                pChnStr[idx++] = 'I';
                                pChnStr[idx++] = 'N';
                                pChnStr[idx++] = 'T';
                            }
                            pSrcStr++;
                        }while(pSrcStr && *pSrcStr != '\0');

                        LPTSTR pStrtemp = malloc(PROG_NUMBER_LEN);
                        if (pStrtemp != NULL)
                        {
                            memset(pStrtemp, 0x0, PROG_NUMBER_LEN);
                            MApp_ZUI_API_StringBuffU8toU16(pStrtemp, pChnStr, PROG_NUMBER_LEN);
                            MApp_TTSControlSetInputText(pStrtemp, PROG_NUMBER_LEN);
                            free(pStrtemp);
                        }

                        free(pChnStr);
                    }

                    MApp_TTSControlSetInputText(CurProgramNameText(), MApp_UiMenu_u16Strlen(CurProgramNameText()));
                    if ( stGenSetting.g_SysSetting.bTTSOn )
                        MApp_TTSControlSetOn(TRUE);
                }
            #endif // #if ENABLE_ATSC_TTS
            }
            else
            {
            #if EN_INPUT_LABEL_EDIT
              #if (ATSC_READY)
                MApp_UiMenuFunc_InputLabel_SetInputSource();
              #endif
                U8 CustomLabel[MAX_INPUTLLABEL_CHAR_NUM+1];
                MApp_UiMenuFunc_InputLabel_GetCustomLabel(CustomLabel);
                return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, CustomLabel, MAX_INPUTLLABEL_CHAR_NUM+1);
            #else   // !EN_INPUT_LABEL_EDIT
                u16TempID = GetSourceTypeTextID();
            #endif
            }
            break;

        case HWND_CHINFO_PROG_NAME_TEXT:
           return CurProgramNameText();

        case HWND_CHINFO_CONTENT_1ST_ROW_CC_INFO:
            u16TempID = CCInfoTextID();
            u8TempString=(U8 *)"";
            break;

        case HWND_CHINFO_CONTENT_2ND_ROW_RESOLUTION:
            u8TempString = EventInfoLine2Left();
            break;

         case HWND_CHINFO_CONTENT_2ND_ROW_VID_RES_ICON:
            u16TempID = VidResIconTextId();
            break;

        case HWND_CHINFO_CONTENT_3RD_ROW_TIME_TEXT:
            u8TempString = EventInfoLine3Left();
            break;

        case HWND_CHINFO_CONTENT_1ST_ROW_EVENT_INFO:
            if((fSearchEventTitlefromEIT)&&(IsDTVInUse()))
            {
                u8TempString = (U8 *)&(au8EpgUiBuf[0]);
              #if ENABLE_ATSC_TTS
                U16 u16strLen = 0;
                for (u16strLen = 0; u16strLen < EPG_ETT_MAX_STR_LEN; u16strLen++)
                {
                    if (au8EpgUiBuf[u16strLen] == '\0')
                    {
                        u16strLen++;
                        break;
                    }
                }
              #endif

                bStrIsUTF16 = stEpgEventInfo.fIsEitUTF16;
                if(stEpgEventInfo.fIsEitUTF16)
                {
                    U16 length = 0, i = 0, iRet = 0;
                    char tmpNULL[] = "Null";
                    printf("(%d)(%s)\n",__LINE__, __func__);
                    length = strlen(tmpNULL);
                    do
                    {
                        iRet = ((U16)u8TempString[2*i] << 8 | (U16)u8TempString[2*i+1]) - (U16)tmpNULL[i];
                        i++;
                    }while(i<length && iRet == 0);// compare util the end char of tmoNULL

                    if (iRet == 0)
                    {
                        u8TempString = NULL;
                        u16TempID = en_str_No_Event_Information;
                    }
                }
                else if (strncmp((char *)(u8TempString), "Null", strlen((char *)(u8TempString))-1) == 0)
                {
                    u8TempString = NULL;
                    u16TempID = en_str_No_Event_Information;
                }
            }
            else
            {
                u8TempString = CC_SourceFuns.GetXDSInfo(XDS_INFO_PROGRAMTITLE);
                if(u8TempString == NULL)
                {
                    u16TempID = en_str_No_Event_Information;
                }
                else
                {
                    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8TempString, strlen((char *)u8TempString));
                    return CHAR_BUFFER;
                }
            }
            break;

        case HWND_CHINFO_CONTENT_2ND_ROW_SCRAMBLE_STATUS:
            u8TempString = EventInfoLine2Right();
            break;

        case HWND_CHINFO_BANNER_PROG_NUM:
            if(IsDTVInUse() || IsATVInUse())
            {
               u8TempString = CurProgramNumberText();

            #if ENABLE_ATSC_TTS
                if( MApp_TTS_Cus_Get_UserSetting_TTSOn()
                  &&(u8TempString != NULL)
                  )
                {
                    MApp_TTSControlSetInputText(MApp_ZUI_API_GetString(en_str_Channel), MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(en_str_Channel)));

                    U8* pChnStr = malloc(PROG_NUMBER_LEN), *pSrcStr = u8TempString, idx = 0;

                    if (pChnStr != NULL)
                    {
                        memset(pChnStr, 0x0, PROG_NUMBER_LEN);
                        do
                        {
                            if ((*pSrcStr) != '.')
                                pChnStr[idx++] = *pSrcStr;
                            else
                            {
                                pChnStr[idx++] = 'P';
                               pChnStr[idx++] = 'O';
                               pChnStr[idx++] = 'I';
                               pChnStr[idx++] = 'N';
                               pChnStr[idx++] = 'T';
                            }
                            pSrcStr++;
                        }while(pSrcStr && *pSrcStr != '\0');

                        LPTSTR pStrtemp = malloc(PROG_NUMBER_LEN);
                        if (pStrtemp != NULL)
                        {
                            memset(pStrtemp, 0x0, PROG_NUMBER_LEN);
                            MApp_ZUI_API_StringBuffU8toU16(pStrtemp, pChnStr, PROG_NUMBER_LEN);
                            MApp_TTSControlSetInputText(pStrtemp, PROG_NUMBER_LEN);
                            free(pStrtemp);
                        }

                        free(pChnStr);
                    }

                    MApp_TTSControlSetInputText(CurProgramNameText(), MApp_UiMenu_u16Strlen(CurProgramNameText()));
                    //if ( stGenSetting.g_SysSetting.bTTSOn )
                    MApp_TTSControlSetOn(TRUE);
                }
            #endif // #if ENABLE_ATSC_TTS
            }
            else
            {
            #if EN_INPUT_LABEL_EDIT
             #if (ATSC_READY)
                MApp_UiMenuFunc_InputLabel_SetInputSource();
              #endif
                U8 CustomLabel[MAX_INPUTLLABEL_CHAR_NUM+1];
                MApp_UiMenuFunc_InputLabel_GetCustomLabel(CustomLabel);
                return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, CustomLabel, MAX_INPUTLLABEL_CHAR_NUM+1);
            #else   // !EN_INPUT_LABEL_EDIT
                u16TempID = GetSourceTypeTextID();
            #endif
            }
            break;

        case HWND_CHINFO_BANNER_PROG_NAME:
            return CurProgramNameText();

        case HWND_CHINFO_BANNER_PROG_SCRAMBLE_INFO:
                u16TempID = CurProgramScrambleStatusTextID();
            break;

        case HWND_CHINFO_DIRECT_TUNE_PANEL_TEXT:
            if(enVirChType2bVerified == MAJOR_CH_NUM)
            {
               MApp_UlongToString((U32)stVirtualChNum.major_num,au8Section,u8IdleDigitCount);
            }
            else if(enVirChType2bVerified == MINOR_CH_NUM)
            {
                MApp_UlongToString((U32)stVirtualChNum.major_num,au8Section,u8MajorNumDigitCount);
                au8Section[u8MajorNumDigitCount] = '-';

            #if ONE_PART_CHNO
                if(stVirtualChNum.minor_num == INVALID_MINOR_NUMBER)
                {
                    MApp_UlongToString((U32)0,&au8Section[u8MajorNumDigitCount+1],u8IdleDigitCount);
                }
                else
            #endif
                {
                MApp_UlongToString((U32)stVirtualChNum.minor_num,&au8Section[u8MajorNumDigitCount+1],u8IdleDigitCount);
                }
            }

            u8TempString =  au8Section;
            break;
        case HWND_CHINFO_ETT_TEXT:
          #if SUPPORT_LONG_ETT
            if( MApp_EpgDB_GetCurEvent(&stEpgEventInfo) == FALSE )
                u16TempID = en_str_No_Event_Information;
            else
            {
                LPTSTR strEttText = NULL;
                strEttText = MApp_EpgZUI_GetExtendText(&stEpgEventInfo);
                if(strEttText)
                    return strEttText;
                else
                    u16TempID = en_str_No_Event_Information;
            }
          #else
            if (IsAtscInUse())
            {
                if ((stEpgDBInfo.fIsEttRxOk) && (strlen((char *)au8ETT) != 0))
                {
                    u8TempString = (U8 *)&au8ETT;
                }
                else
                {
                    u16TempID = en_str_No_Title;
                }
            }
            else
            {
                u8TempString = CC_SourceFuns.GetXDSInfo(XDS_INFO_NETWORKNAME);
                if(u8TempString == NULL)
                {
                    u16TempID = en_str_No_Title;
                }
                else
                {
                    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8TempString, strlen((char *)u8TempString));
                    return CHAR_BUFFER;
                }
            }
          #endif
            break;


        default:
            //
            break;
    }

    if(u16TempID != Empty)
    {
        return MApp_ZUI_API_GetString(u16TempID);
    }
    else
    {
        if( u8TempString == NULL )
        {
            CHAR_BUFFER[0] = 0;
        }
        else
        {
            MApp_ZUI_ACT_ChInfo_String_Processing(hwnd, u8TempString, CHAR_BUFFER, bStrIsUTF16 );
        }

        return CHAR_BUFFER;
    }
}


//////////////////////////////////////////////////////////////////////////////////////


#if 0

static U8 _MApp_ZUI_ACT_GetCurrentChannelResolutionType()
{
    if(gstVidStatus.u16HorSize >= 1200 && gstVidStatus.u16VerSize >= 700)
        return 1;
    else if(gstVidStatus.u16HorSize>0 && gstVidStatus.u16VerSize>0 && (gstVidStatus.u16VerSize >= 570 && gstVidStatus.u16FrameRate <= 25000 ))
        return 0;
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
        StatusCheck = MApp_VD_IsSyncLock();
    }
    else
    {
        StatusCheck= !MApp_Analog_NoSignal_ExcludeATV();
    }

    return StatusCheck;
}


static BOOLEAN _MApp_ZUI_ACT_GetServiceNameToUCS2(MEMBER_SERVICETYPE bServiceType, WORD wPosition, WORD * bChannelName, U8 ControlCodes)
{
    U8 tempBuffer[MAX_SERVICE_NAME];
    U8 *tempBuf2;
    tempBuf2=(U8*)bChannelName;
    if(msAPI_CM_GetServiceName(bServiceType, wPosition, tempBuf2)==E_RESULT_SUCCESS)
    {
        MApp_Dmx_GetString(tempBuffer, MAX_SERVICE_NAME, tempBuf2, MAX_SERVICE_NAME, ControlCodes);
        MApp_CharTable_MappingDVBTextToUCS2(tempBuffer, bChannelName, MAX_SERVICE_NAME, MAX_SERVICE_NAME, REMOVE_00AD_SOFT_HYPHEN);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static LPTSTR _MApp_ZUI_ACT_GetInputSourceResolution(void)
{
    //from case CUR_INPUT_SOURCE_VIDEO_RES:
    U16 u16H, u16V, u16F;
    LPTSTR str = CHAR_BUFFER; //iu8Buffer_i = 0;
    if ( IsYPbPrInUse() )
    {
        u16V = msAPI_Mode_GetStdModeResV( g_PcadcModeSetting.u8ModeIndex );
        __MApp_UlongToString( ( U32 )u16V, str, MApp_GetNoOfDigit( u16V ) );
        str += MApp_ZUI_API_Strlen(str); //iu8Buffer_i = __strlen( p_string_buffer );
        if ( MApi_XC_PCMonitor_GetSyncStatus(MAIN_WINDOW) & MD_INTERLACE_BIT )
        {
            *str++ = CHAR_i;
        }
        else
        {
            *str++ = CHAR_p;
        }
        *str = 0;

        return CHAR_BUFFER;
    }
    else if ( IsVgaInUse() )
    {
        if(MApp_PCMode_GetCurrentState(MAIN_WINDOW) != E_PCMODE_STABLE_SUPPORT_MODE)    //(MApp_PCMode_SyncLossFlag() || g_bUnsupportMode || (g_bInputTimingStable!=TRUE))
        {
            return NULL;
        }
        else
        {
            u16H = MApp_PCMode_Get_HResolution( eWindow );
            u16V = MApp_PCMode_Get_VResolution( eWindow );
            u16F = MApi_XC_PCMonitor_Get_VFreqx10( eWindow ) / 10;
            if(u16F > 56 && u16F < 62)
            {
                u16F= 60;
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
        u16V = msAPI_Scaler_GetVerticalDE();
        u16H = msAPI_Scaler_GetHorizontalDE();
        if ((u16H >= 710 && u16H <= 1540) && (u16V >= 470 && u16V <= 490))
        {
            u16V = 480;
        }
        else if (u16V > 566 && u16V < 586)
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
#if(MS_BOARD_TYPE_SEL == BD_MSD109CL_MTC)
            if((u16H >= 630 && u16H <= 650) && (u16V >= 470 && u16V <= 490))
            {
                __MApp_UlongToString( ( U32 )u16H, str, MApp_GetNoOfDigit( u16H ) );
                str += MApp_ZUI_API_Strlen(str); //iu8Buffer_i = __strlen( p_string_buffer );
                *str++ = CHAR_x;
                __MApp_UlongToString( ( U32 )u16V, str, MApp_GetNoOfDigit( u16V ) );
                str += MApp_ZUI_API_Strlen(str); //iu8Buffer_i = __strlen( p_string_buffer );
            }
            else
#endif
                return NULL;
        }

#if(MS_BOARD_TYPE_SEL == BD_MSD109CL_MTC)
        if((u16H >= 630 && u16H <= 650) && (u16V >= 470 && u16V <= 490))
        {
            ;
        }
            else
#endif
        {
            __MApp_UlongToString( ( U32 )u16V, str, MApp_GetNoOfDigit( u16V ) );
            str += MApp_ZUI_API_Strlen(str); //iu8Buffer_i = __strlen( p_string_buffer );
        }

        if ( MApi_XC_PCMonitor_GetSyncStatus(MAIN_WINDOW) & MD_INTERLACE_BIT )
        {
            *str++ = CHAR_i;
        }
        else
        {
            *str++ = CHAR_p;
        }
        *str = 0;

        return CHAR_BUFFER;
    }
    else if ( IsHDMIInUse()&& (!g_HdmiPollingStatus.bIsHDMIMode))//DVI IN USE
    {
        u16V = msAPI_Scaler_GetVerticalDE();
        u16H = msAPI_Scaler_GetHorizontalDE();
        u16F = MApi_XC_PCMonitor_Get_VFreqx10( eWindow ) / 10;

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

        else if((u16V > 740 && u16V < 7900) && (u16H> 1270 && u16H < 1390))
        {
            u16V = 768;
            u16H = 1366;
        }

        else
        {
            ;
        }

        if(u16F > 56 && u16F < 62)
        {
            u16F= 60;
        }
        else if(u16F > 67 && u16F < 72)
        {
            u16F= 70;
        }
        else if( u16F > 72 && u16F < 77)
        {
            u16F= 75;
        }
        else if( u16F > 80 && u16F < 85)
        {
            u16F= 85;
        }
        else
        {
             ;
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
    else if(IsDTVInUse())
    {
        MVD_FRAMEINFO pinfo;
        MDrv_Mvd_GetFrameInfo(&pinfo);

        u16V = pinfo.u16VerSize;
        if(u16V > 0)
        {
            __MApp_UlongToString( ( U32 )u16V, str, MApp_GetNoOfDigit( u16V ) );
            str += MApp_ZUI_API_Strlen(str); //iu8Buffer_i = __strlen( p_string_buffer );

            if (((pinfo.u16FrameRate&0x000F) / (pinfo.u8AspectRatio&0x000F))<2 )
                *str++ = CHAR_i;
            else
                *str++ = CHAR_p;

            *str = 0;

            return CHAR_BUFFER;
        }
        else
            return NULL;
    }
    else
    {
        switch ( g_VdInfo.ucVideoSystem )
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
    }

    return NULL;
}

static U16 _MApp_ZUI_ACT_GetEventInfoGenreStringID(void)
{
    //from         case INFO_GENRE_TEXT:
    BOOLEAN isUKCountry;

    if (pastEventInfo == NULL)
        return Empty;

    if ( OSD_COUNTRY_SETTING == OSD_COUNTRY_UK )
    {
        isUKCountry = 1;
    }
    else
    {
        isUKCountry = 0;
    }

    switch ( pastEventInfo[bNextEvent].u8Content_nibble_level1 )
    {
        case 0x1:
            return ( isUKCountry == 1 ?  en_str_Movie :  en_str_MovieslashDrama );
            break;
        case 0x2:
            return ( isUKCountry == 1 ?  en_str_News_and_Factual :  en_str_NewsshashCurrent_Affairs );
            break;
        case 0x3:
            return  ( isUKCountry == 1 ?  en_str_Entertainment :  en_str_ShowslshGame_Show );
            break;
        case 0x4:
            return   en_str_Sports;
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
            return ( isUKCountry == 1 ?  en_str_News_and_Factual :  en_str_SocialshashPolitical_IssuesslashEconomics );
            break;
        case 0x9:
            return ( isUKCountry == 1 ?  en_str_Education :  en_str_EducationshshScienceslashslashFactual_Topics );
            break;
        case 0xa:
            return ( isUKCountry == 1 ?  en_str_Lifestyle :  en_str_Leisure_Hobbies );
            break;
        case 0xb:
            return ( isUKCountry == 1 ?  en_str_Not_Supported :  en_str_Special_Characteristics );
            break;
        case 0xc:
            return ( isUKCountry == 1 ?  en_str_Not_Supported :  en_str_Reserved_for_future_use );
            break;
        case 0xd:
            return ( isUKCountry == 1 ?  en_str_Not_Supported :  en_str_Reserved_for_future_use );
            break;
        case 0xe:
            return ( isUKCountry == 1 ?  en_str_Not_Supported :  en_str_Reserved_for_future_use );
            break;
        case 0xf:
            return ( isUKCountry == 1 ?  en_str_Drama :  en_str_Reserved_for_future_use );
            break;
        default:
            return Empty;
            break;
    }

}


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
            case UI_INPUT_SOURCE_TV:
                u16TempID=en_str_TV;
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

static const OSDCP_EN_STRING_INDEX _ZUI_TBLSEG _WeekString[7]=
{
    en_str_Sun,
    en_str_Mon,
    en_str_Tue,
    en_str_Wed,
    en_str_Thurs,
    en_str_Fri,
    en_str_Sat,
};

void _MApp_ZUI_ACT_LoadWeekString(U8 month, LPTSTR str)
{
    MApp_ZUI_API_LoadString(_WeekString[month], str);
}

extern void _MApp_ZUI_ACT_LoadMonthString(U8 month, LPTSTR str);
extern LPTSTR _MApp_ZUI_ACT_GetLocalClockTimeString(LPTSTR str);
extern U16 _MApp_ZUI_ACT_GetLanguageStringID(EN_LANGUAGE lang, BOOLEAN bDefaultEnglish);

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
    switch(hwnd)
    {
        case HWND_CHINFO_BTM_PR_NOW_NEXT:
            if (bNextEvent)
                u16TempID = en_str_Next;
            else
                u16TempID = en_str_Now;
            break;

        case HWND_CHINFO_TOP_CH_INPUT:
        {
            //from CURPROGRAMCHANNELTYPETEXT
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
#else

                if (msAPI_CM_GetCurrentServiceType() == E_SERVICETYPE_DTV)
                {
                    u16TempID = en_str_DTV;
                }
                else if (msAPI_CM_GetCurrentServiceType() == E_SERVICETYPE_RADIO)
                {
                    u16TempID = en_str_Radio;
                }
#endif
            }
            else if ( IsATVInUse() )
            {
                u16TempID=en_str_TV;
            }
            else
            {
                break; //return strNUll;
            }
        }
            break;

        case HWND_CHINFO_TOP_CH_NAME:
        {
            //from CURPROGRAMNAMETEXT
            LPTSTR str = CHAR_BUFFER;
            str[0] = 0;
            //iu8Buffer_i = 0;

            if (IsDTVInUse())
            {
                U16 u16Count, u16Pos;
                MEMBER_SERVICETYPE bServiceType;
#if MHEG5_ENABLE // <-<<<
               bServiceType=g_eCurrentUserServiceType;
               u16Count = msAPI_CM_CountProgram(bServiceType, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                if(bServiceType == E_SERVICETYPE_RADIO)
                    u16Pos=g_wCurrentRadioUserServicePosition;
                else
                    u16Pos=g_wCurrentTVUserServicePosition;
#else
                bServiceType = msAPI_CM_GetCurrentServiceType();
                u16Count = msAPI_CM_CountProgram(bServiceType, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                u16Pos = msAPI_CM_GetCurrentPosition(bServiceType);
#endif
                if (u16Count > 0)
                {
                    _MApp_ZUI_ACT_GetServiceNameToUCS2(bServiceType, u16Pos/*msAPI_CM_GetCurrentPosition(bServiceType)*/, str, KEEP_CONTROL_CODE_NONE);
                    //if (__strlen(str) > MAX_MANUALSCAN_MENU_PROGRAMNAME_LEN)
                    {
                        str[MAX_MANUALSCAN_MENU_PROGRAMNAME_LEN] = 0;
                    }
                    return str;
                }
                else
                {
                    break; //return strNUll;
                }
            }
            else if (IsATVInUse())
            {
                U8 u8Temp[MAX_STATION_NAME+1];

                //msAPI_Tuner_GetCurrentStationName(u8Temp);
                msAPI_ATV_GetStationName(msAPI_ATV_GetCurrentProgramNumber(), u8Temp);

                MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8Temp, MAX_STATION_NAME);

                //if (__strlen(str) > MAX_MANUALSCAN_MENU_PROGRAMNAME_LEN)
                {
                    CHAR_BUFFER[MAX_MANUALSCAN_MENU_PROGRAMNAME_LEN] = 0;
                }

                return CHAR_BUFFER;
            }
            else
            {
                u16TempID = _MApp_ZUI_ACT_GetUIInputSourceStringID(UI_INPUT_SOURCE_TYPE);
            }

            break; //return strNUll;
        }
        break;

        case HWND_CHINFO_TOP_CH_SDHD:
        {
            if (IsDTVInUse())
            {
                if (enFrotEndLockStatus!=FRONTEND_UNKNOWN)
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

                        //if (bdrawHDSDflag)
                        {
                            if (_MApp_ZUI_ACT_GetCurrentChannelResolutionType() == 1)
                            {
                                u16TempID = en_str_HD; //MApp_UiMenu_DrawMenuString0_3(EN_IDLESTRING0_ICON_HD, EN_CPSTATE_SELECT);
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

        case HWND_CHINFO_TOP_CH_AUDIO:
        {
            if (IsDTVInUse())
            {
                if (enFrotEndLockStatus!=FRONTEND_UNKNOWN)
                {
                    //from MApp_UiMenu_DrawDTV_BannerInfo()
                    if (MApp_GetSignalStatus() == SIGNAL_LOCK)
                    {
                        MEMBER_SERVICETYPE bServiceType;
                        AUD_INFO stAudioStreamInfo;
                        BYTE bSelectedAudStream;
                        WORD wPosition;
                        //BYTE bSelected;

                        bServiceType = msAPI_CM_GetCurrentServiceType();
                        wPosition = msAPI_CM_GetCurrentPosition(bServiceType);
                        bSelectedAudStream = msAPI_CM_GetSelectedAudioStream(bServiceType, msAPI_CM_GetCurrentPosition(bServiceType));
                        msAPI_CM_GetAudioStreamInfo(bServiceType, msAPI_CM_GetCurrentPosition(bServiceType), &stAudioStreamInfo, bSelectedAudStream);
                        //bSelected = msAPI_CM_GetSelectedAudioStream(bServiceType, wPosition);

                        //if (bdrawAudioflag)
                        {
                            if (E_AUDIOSTREAM_MPEG == stAudioStreamInfo.wAudType)
                            {
                                u16TempID = en_str_MPEG; //MApp_UiMenu_DrawMenuString0_3(EN_IDLESTRING0_ICON_DIGITAL_AUDIO, EN_CPSTATE_SELECT);
                            }
                            else if (E_AUDIOSTREAM_AC3 == stAudioStreamInfo.wAudType)
                            {
                                u16TempID = en_str_DOLBY; //MApp_UiMenu_DrawMenuString0_3(EN_IDLESTRING0_ICON_DOLBY_DIGITAL, EN_CPSTATE_SELECT);
                            }
                        }
                        //channelInfoDrawed = TRUE;
                    }
                }
            }
            /*
            else if (IsATVInUse())
            {
                if (enFrotEndLockStatus != FRONTEND_UNKNOWN)
                {
                    //from MApp_UiMenu_DrawATV_BannerState();
                }
            }
            else
            {
                //if (g_showChannelStatus == TRUE)
                {
                    //from MApp_UiMenu_DrawNonTV_BannerState();
                }
            }
            */
        }
        break;


        case HWND_CHINFO_TOP_CH_COLOR_SYS:
            //from case INFO_ATV_COLORSYSTEXT:
            if(/*/ZUI:ATV or DTV?? IsDigitalSourceInUse()&&*/(MApp_IsSrcHasSignal()))//Has signal
            {
                VIDEOSTANDARD_TYPE eVideoStandard;

                eVideoStandard = msAPI_AVD_GetVideoStandard();
                switch( eVideoStandard )
                {
                    case E_VIDEOSTANDARD_PAL_BGHI:
                    case E_VIDEOSTANDARD_PAL_M:
                    case E_VIDEOSTANDARD_PAL_N:
                    case E_VIDEOSTANDARD_PAL_60:
                        u16TempID=en_str_PAL;
                        break;
                    case E_VIDEOSTANDARD_NTSC_M:
                    case E_VIDEOSTANDARD_NTSC_44:
                        u16TempID=en_str_NTSC;
                        break;
                    case E_VIDEOSTANDARD_SECAM:
                        u16TempID=en_str_SECAM;
                        break;
                    default:
                        u16TempID=en_str_Auto;
                        break;
                }
            }
            else
            {
                break; //return strNUll;
            }
        break;

        case HWND_CHINFO_TOP_CH_SOUND_SYS:
            //from case INFO_ATV_SOUNDSYSTEXT:
            if(IsATVInUse()&&(MApp_IsSrcHasSignal()))//Has signal
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
                    #if ( ENABLE_DTMB_CHINA_APP || ENABLE_DVB_TAIWAN_APP )
                        case E_AUDIOSTANDARD_M:
                            u16TempID=en_str_MN;
                            break;
                    #else
                        case E_AUDIOSTANDARD_L:
                            u16TempID=en_str_L;
                            break;
                    #endif
                        default:
                            u16TempID=en_str_BG;
                            break;

                    }
            }
            else
            {
                break; //return strNUll;
            }
            break;

        case HWND_CHINFO_TOP_CH_MTS_TYPE:
            //from case INFO_ATV_MTSTEXT:
            if(IsATVInUse()&&(MApp_IsSrcHasSignal()))//has signal
            {
                AUDIOMODE_TYPE eCurrentMTSType;
                eCurrentMTSType = MApi_AUDIO_SIF_GetSelectedAudioMode();
                _preCurrentMTSType = eCurrentMTSType;
                switch(eCurrentMTSType)
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
            else
            {
                break; //return strNUll;
            }
            break;


        case HWND_CHINFO_TOP_CH_NUMBER:
        {
            //from CURPROGRAMNUMBERTEXT
            if (IsDTVInUse())
            {
                U16 u16Count, u16Pos, u16LCN;
                MEMBER_SERVICETYPE bServiceType;
#if MHEG5_ENABLE // <-<<<
                bServiceType=g_eCurrentUserServiceType;
                u16Count = msAPI_CM_CountProgram(bServiceType, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                if(bServiceType == E_SERVICETYPE_RADIO)
                    u16Pos=g_wCurrentRadioUserServicePosition;
                else
                    u16Pos=g_wCurrentTVUserServicePosition;
#else
                bServiceType = msAPI_CM_GetCurrentServiceType();
                u16Count = msAPI_CM_CountProgram(bServiceType, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                u16Pos = msAPI_CM_GetCurrentPosition(bServiceType);
#endif
                u16LCN = msAPI_CM_GetLogicalChannelNumber(bServiceType, u16Pos);
                if ((u16Count > 0) && (u16LCN != INVALID_LOGICAL_CHANNEL_NUMBER))
                {
                    //__MApp_UiMenuFunc_ConvertProgramNumber2Str(u16LCN, p_string_buffer);
                    //return p_string_buffer;
                    return MApp_ZUI_API_GetU16String(u16LCN);
                }
                else
                {
                    break; //return strNUll;
                }
            }
            else if (IsATVInUse())
            {
                U8 u8Temp;

                u8Temp = msAPI_ATV_GetCurrentProgramNumber();
                u8Temp++;  //ATV channel number start from 1
                //u8NoOfDigit = MApp_GetNoOfDigit(u8Temp);
                //MApp_UlongToU16String(u8Temp, p_string_buffer, u8NoOfDigit);
                //return p_string_buffer;
                return MApp_ZUI_API_GetU16String(u8Temp);
            }
            else
            {
                break; //return strNUll;
            }
        }
        break;


        case HWND_CHINFO_BTM_PR_NAME:
            //from         case INFO_EVENTTITLETEXT:
        {
            if ( (pastEventInfo) && (g_u8EitCurPfVersionNum!=INVALID_VERSION_NUM) && IsDTVInUse())
            {
#if MHEG5_ENABLE // <-<<<
                if(g_eCurrentUserServiceType != g_eCurrentRealServiceType || (g_eCurrentRealServiceType == E_SERVICETYPE_DTV && g_wCurrentTVUserServicePosition != g_wCurrentTVRealServicePosition)
                    || (g_eCurrentRealServiceType == E_SERVICETYPE_RADIO && g_wCurrentRadioUserServicePosition != g_wCurrentRadioRealServicePosition))
                {
                    u16TempID=en_str_No_Information;
                    break;
                }
#endif
                MApp_EpgDB_EventName_LoadFromSED(CHAR_BUFFER, MAX_SHORT_EVENT_DESCRIPTOR_LEN, pastEventInfo[bNextEvent].short_event_descriptor);
                if (CHAR_BUFFER[0] != 0)
                {
                    return CHAR_BUFFER;
                }
            }

            u16TempID=en_str_No_Information;
        }
        break;

        case HWND_CHINFO_BTM_PR_DATE:
            //from case INFO_EVENTSTARTDAYTEXT:
        {
            U32 u32StartTime;
            U8 u8dayofweek;

            LPTSTR str = CHAR_BUFFER; //u8_idx = 0;
            str[0]= 0;

            if( (pastEventInfo) && (g_u8EitCurPfVersionNum!=INVALID_VERSION_NUM) && IsDTVInUse())
            {
                if (pastEventInfo[bNextEvent].start_time[0] != 0 || pastEventInfo[bNextEvent].start_time[1] != 0 ||
                    pastEventInfo[bNextEvent].start_time[2] != 0 || pastEventInfo[bNextEvent].start_time[3] != 0 ||
                    pastEventInfo[bNextEvent].start_time[4] != 0 )
                {
                    u32StartTime = MApp_GetLocalSystemTime();
                    MApp_ConvertSeconds2StTime((U32)u32StartTime, &stDate);

                    u8dayofweek = MApp_GetDayOfWeek(stDate.u16Year, stDate.u8Month, stDate.u8Day);
                    _MApp_ZUI_ACT_LoadWeekString(u8dayofweek, str);
                    str += MApp_ZUI_API_Strlen(str);
                    *str++ = CHAR_SPACE;

                    _MApp_ZUI_ACT_LoadMonthString(stDate.u8Month-1, str);
                    str += MApp_ZUI_API_Strlen(str);
                    *str++ = CHAR_SPACE;

                    __MApp_UlongToString((U32)stDate.u8Day, str, 2);
                    str += 2;
                    *str++ = CHAR_SPACE;

                    __MApp_UlongToString((U32)stDate.u16Year, str, 4);
                    str += 4;
                    *str = 0;
                }
            }

            return CHAR_BUFFER;
        }
        break;

        case HWND_CHINFO_BTM_PR_TIME_START:
            //from case INFO_EVENTSTARTTEXT:
        {
            U32 u32StartTime;

            LPTSTR str = CHAR_BUFFER; //u8_idx = 0;
            str[0] = 0; //p_string_buffer[0]= 0;

            //if(MApp_EpgDB_GetCurEvent(&g_stCurEvent)&&IsDTVInUse())
            if( (pastEventInfo) && (g_u8EitCurPfVersionNum!=INVALID_VERSION_NUM) && IsDTVInUse())
            {
                if (pastEventInfo[bNextEvent].start_time[0] != 0 || pastEventInfo[bNextEvent].start_time[1] != 0 ||
                    pastEventInfo[bNextEvent].start_time[2] != 0 || pastEventInfo[bNextEvent].start_time[3] != 0 ||
                    pastEventInfo[bNextEvent].start_time[4] != 0 )
                {
                    u32StartTime = MApp_MJDUTC2Seconds(pastEventInfo[bNextEvent].start_time)+ msAPI_Timer_GetOffsetTime();
                    MApp_ConvertSeconds2StTime((U32)u32StartTime, &stDate);

                    __MApp_UlongToString((U32)stDate.u8Hour, str, 2);
                    str += 2;
                    *str++ = CHAR_COLON;
                    __MApp_UlongToString((U32)stDate.u8Min, str, 2);
                    str += 2;
                    *str = 0;

                    //ZUI_TODO: m_u8EventStarMinute = stDate.u8Min;
                    //ZUI_TODO: m_u8EventStarHour =stDate.u8Hour;
               }
            }

            //p_string_buffer[u8_idx] = 0;
            return CHAR_BUFFER; //p_string_buffer;
        }
        break;

        case HWND_CHINFO_BTM_PR_TIME_END:
            //from case INFO_EVENTENDTIMETEXT:
        {
            U32 u32StartTime;
            U32 u32EndTime;

            LPTSTR str = CHAR_BUFFER; //u8_idx = 0;
            str[0] = 0; //p_string_buffer[0]= 0;

            //if(MApp_EpgDB_GetCurEvent(&g_stCurEvent)&&IsDTVInUse())
            if( (pastEventInfo) && (g_u8EitCurPfVersionNum!=INVALID_VERSION_NUM) && IsDTVInUse())
            {
                if (pastEventInfo[bNextEvent].start_time[0] != 0 || pastEventInfo[bNextEvent].start_time[1] != 0 ||
                    pastEventInfo[bNextEvent].start_time[2] != 0 || pastEventInfo[bNextEvent].start_time[3] != 0 ||
                    pastEventInfo[bNextEvent].start_time[4] != 0 )
                {
                    u32StartTime = MApp_MJDUTC2Seconds(pastEventInfo[bNextEvent].start_time)+ msAPI_Timer_GetOffsetTime();
                    u32EndTime = u32StartTime + MApp_UTC2Seconds(pastEventInfo[bNextEvent].duration);
                    MApp_ConvertSeconds2StTime((U32)u32EndTime, &stDate);

                    __MApp_UlongToString((U32)stDate.u8Hour, str, 2);
                    str += 2;
                    *str++ = CHAR_COLON;
                    __MApp_UlongToString((U32)stDate.u8Min, str, 2);
                    str += 2;
                    *str = 0;

                    //ZUI_TODO: m_u32EventTimeDuration = MApp_UTC2Seconds(pastEventInfo[bNextEvent].duration);
                }
            }

            //p_string_buffer[u8_idx] = 0;
            return CHAR_BUFFER; //p_string_buffer;
        }
        break;

        case HWND_CHINFO_BTM_PR_TIME:
        {
            LPTSTR str = CHAR_BUFFER;
            str = _MApp_ZUI_ACT_GetLocalClockTimeString(str);
            *str = 0;
            return CHAR_BUFFER;
        }

        case HWND_CHINFO_BTM_PR_TITLE:
                //from case INFO_EVENTTITLETEXT:
        {
            if ( (pastEventInfo) && (g_u8EitCurPfVersionNum!=INVALID_VERSION_NUM) && IsDTVInUse())
            {
#if MHEG5_ENABLE // <-<<<
                if(g_eCurrentUserServiceType != g_eCurrentRealServiceType || (g_eCurrentRealServiceType == E_SERVICETYPE_DTV && g_wCurrentTVUserServicePosition != g_wCurrentTVRealServicePosition)
                    || (g_eCurrentRealServiceType == E_SERVICETYPE_RADIO && g_wCurrentRadioUserServicePosition != g_wCurrentRadioRealServicePosition))
                {
                    u16TempID=en_str_No_Information;
                    break;
                }
#endif
                MApp_EpgDB_EventName_LoadFromSED(CHAR_BUFFER, MAX_SHORT_EVENT_DESCRIPTOR_LEN, pastEventInfo[bNextEvent].short_event_descriptor);
                if (CHAR_BUFFER[0] != 0)
                {
                    return CHAR_BUFFER;
                }
            }

            u16TempID = en_str_No_Information;
        }
        break;

        case HWND_CHINFO_BTM_PR_CONTENT:
                //from case INFO_EVENTEXTENDEDTEXT:
        {
#if MHEG5_ENABLE // <-<<<
            if(g_eCurrentUserServiceType != g_eCurrentRealServiceType || (g_eCurrentRealServiceType == E_SERVICETYPE_DTV && g_wCurrentTVUserServicePosition != g_wCurrentTVRealServicePosition)
                || (g_eCurrentRealServiceType == E_SERVICETYPE_RADIO && g_wCurrentRadioUserServicePosition != g_wCurrentRadioRealServicePosition))
            {
                u16TempID=en_str_No_Program_Information;
                break;
            }
#endif

            if ( ( pastEventInfo ) && ( g_u8EitCurPfVersionNum != INVALID_VERSION_NUM ) && IsDTVInUse() )
            {
                    /*/ZUI_TODO: not support scroll:
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
                    }*/


                    if ( bNextEvent )
                    {
                        // printf("F_au16EventTextScrollLineInx[u8InfoScrollLineCount]*2 = %u \n", au16EventTextScrollLineInx[u8InfoScrollLineCount]*2);
                        msAPI_MIU_Copy( EIT_CUR_FOL_SECTION_START_ADR /*+ ( au16EventTextScrollLineInx[u8InfoScrollLineCount] * 2 )*/, ( U16 )CHAR_BUFFER - DATABASE_START_ADR, 1024, MIU_SDRAM2SDRAM );
                    }
                    else
                    {
                        //printf("P_au16EventTextScrollLineInx[u8InfoScrollLineCount]*2 = %u \n", au16EventTextScrollLineInx[u8InfoScrollLineCount]*2);
                        msAPI_MIU_Copy( EIT_CUR_PRE_SECTION_START_ADR /*+ ( au16EventTextScrollLineInx[u8InfoScrollLineCount] * 2 )*/, ( U16 )CHAR_BUFFER - DATABASE_START_ADR, 1024, MIU_SDRAM2SDRAM );
                    }

                    //msAPI_MIU_Copy(EIT_CUR_FOL_SECTION_START_ADR, (U16)p_string_buffer-DATABASE_START_ADR, 1024, MIU_SDRAM2SDRAM );
                    //for (i=0;i<512;i++)
                    //printf("%u=[%x] ",i, p_string_buffer[i]);
                    if ( CHAR_BUFFER[0] != 0 )
                    {
                        g_versionNumberChange = false;
                        return CHAR_BUFFER;
                    }
                }

            u16TempID=en_str_No_Program_Information;

        }
        break;

        case HWND_CHINFO_BTM_PR_VIDEO_RES:
            return _MApp_ZUI_ACT_GetInputSourceResolution();

        case HWND_CHINFO_BTM_PR_AGE:
            //from function MApp_UiMenu_DrawDTV_ParentalRating()
            if(pastEventInfo!=NULL &&
                pastEventInfo[bNextEvent].u8Parental_Control > PARENTAL_RATE_SHIFT)
            {
                //from case EN_DNUM_PARENTAL_RATING_NUMBER:
                if(IsATVInUse())
                {
                    //return 0;
                }
                else
                {
                    if (pastEventInfo[bNextEvent].u8Parental_Control < (0x10 + PARENTAL_RATE_SHIFT) && pastEventInfo[bNextEvent].u8Parental_Control > (0x00 + PARENTAL_RATE_SHIFT))
                    {
                        //return pastEventInfo[bNextEvent].u8Parental_Control;
                        LPTSTR str = CHAR_BUFFER;
                        MApp_ZUI_API_LoadString(en_str_Age, str);
                        str += MApp_ZUI_API_Strlen(str);
                        *str++ = CHAR_SPACE;
                        __MApp_UlongToString(pastEventInfo[bNextEvent].u8Parental_Control, str, 2);
                        return CHAR_BUFFER;
                    }
                    //else
                    //    return 0;
                }

            }
        break;

        case HWND_CHINFO_BTM_PR_GENRE:
            u16TempID = _MApp_ZUI_ACT_GetEventInfoGenreStringID();
        break;

        case HWND_CHINFO_BTM_PR_SUBTITLE:
            //from function MApp_UiMenu_DrawProgramBriefInfo()
            if ( IsDTVInUse() && _MApp_ZUI_ACT_IsCurrentSourceAvailable() )
            {
                /*Subtitle*/
                if (u8SubtitleServiceNum > 0)
                {
                    u16TempID = en_str_Subtitle;
                }
            }
        break;

        case HWND_CHINFO_BTM_PR_TELETEXT:
            //from function MApp_UiMenu_DrawProgramBriefInfo()
            if ( IsDTVInUse() && _MApp_ZUI_ACT_IsCurrentSourceAvailable() )
            {
                //Teletext
                if (g_stSIInfo.stPmtMonInfo.stTtx.u16TTX_Pid != MSAPI_DMX_INVALID_PID)
                {
                    // If country option is UK, don't draw TTX icon in INFO window
                    if(OSD_COUNTRY_SETTING != OSD_COUNTRY_UK)
                    {
                        u16TempID = en_str_Teletext;
                    }
                }

            }
        break;

        case HWND_CHINFO_BTM_PR_MHEG:
            //from function MApp_UiMenu_DrawProgramBriefInfo()
            if ( IsDTVInUse() && _MApp_ZUI_ACT_IsCurrentSourceAvailable() )
            {
                /*MHEG*/
                if ((MApp_SI_CheckMHEG5Status() == SI_MHEG5_WITH_VIDEO) ||
                     (MApp_SI_CheckMHEG5Status() == SI_MHEG5_DATA_ONLY))
                {
                    u16TempID = en_str_MHEG5;
                }

            }
        break;

        case HWND_CHINFO_BTM_PR_AUDIO_LANG:
            //from function MApp_UiMenu_DrawProgramBriefInfo()
            if ( IsDTVInUse() && _MApp_ZUI_ACT_IsCurrentSourceAvailable() )
            {
                u16TempID = _MApp_ZUI_ACT_GetLanguageStringID(
                    stGenSetting.g_SoundSetting.enSoundAudioLan1, FALSE);
            }
        break;

        case HWND_CHINFO_BTM_PR_NARRATION:
            //from function MApp_UiMenu_DrawProgramBriefInfo()
            if ( IsDTVInUse() && _MApp_ZUI_ACT_IsCurrentSourceAvailable() )
            {
                AUD_INFO stAudInfo;
                if( E_RESULT_SUCCESS == msAPI_CM_GetAudioStreamInfo(msAPI_CM_GetCurrentServiceType(), msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()), &stAudInfo, g_u8AudLangSelected) )
                {
                    //Narration
                    if((stAudInfo.aISOLangInfo[0].bAudType == SI_AUDTYPE_HEARING) ||(stAudInfo.aISOLangInfo[0].bAudType == SI_AUDTYPE_VISUAL))
                    {
                        u16TempID = en_str_Narration;
                    }
                }

            }
        break;

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
        case HWND_CHINFO_BTM_PR_TIME_BAR:
        //from function MApp_UiMenu_Monitor_UpdateEventTime()
        if((pastEventInfo[bNextEvent].start_time[0] != 0 || pastEventInfo[bNextEvent].start_time[1] != 0 ||
            pastEventInfo[bNextEvent].start_time[2] != 0 || pastEventInfo[bNextEvent].start_time[3] != 0 ||
            pastEventInfo[bNextEvent].start_time[4] != 0 ) && IsDTVInUse())
        {
            if (MApp_UTC2Seconds(pastEventInfo[bNextEvent].duration) != 0)
            {
                //from function: U16 MApp_Info_Get_DurationBar_Percentage( void )
                S32 u32StartTime,u32EndTime;
                S32 s32CurrentTime ;
                S32 s32EventPassedTime; //   = (stTime.u32System - stTime.u32EventStart);
                S32 s32EventDurationTime; // = (stTime.u32EventEnd - stTime.u32EventStart);
                s32CurrentTime = MApp_GetLocalSystemTime();
                if( (pastEventInfo) && (g_u8EitCurPfVersionNum!=INVALID_VERSION_NUM) && IsDTVInUse())
                {
                       u32StartTime = MApp_MJDUTC2Seconds(pastEventInfo[bNextEvent].start_time)+ msAPI_Timer_GetOffsetTime();
                       s32EventDurationTime=MApp_UTC2Seconds(pastEventInfo[bNextEvent].duration);
                }
                s32EventPassedTime = s32CurrentTime-u32StartTime;
                u32EndTime = u32StartTime + s32EventDurationTime;

                // Draw Progress Bar
                if ( s32CurrentTime < u32StartTime )
                {
                    return 0;
                }
                else if ( (s32CurrentTime>u32EndTime) && (s32EventDurationTime>0) )
                {
                    return 100;
                }
                else if ( (s32EventPassedTime>0) && (s32EventDurationTime>0) )
                {
                    return (U16)( (s32EventPassedTime*100) / s32EventDurationTime );
                }
            }
        }

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
                        if (IsDTVInUse())
                        {
                            if (enFrotEndLockStatus!=FRONTEND_UNKNOWN)
                            {
                                MApp_ZUI_API_KillTimer(hwnd, ZUI_CHINFO_TUNER_LOCK_TIMER_ID);
                                MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHINFO_TOP_PANE);
                            }
                        }
                        else if (IsATVInUse())
                        {
                            if (enFrotEndLockStatus != FRONTEND_UNKNOWN)
                            {
                                MApp_ZUI_API_KillTimer(hwnd, ZUI_CHINFO_TUNER_LOCK_TIMER_ID);
                                MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHINFO_TOP_PANE);
                            }
                        }
                        else
                        {
                            MApp_ZUI_API_KillTimer(hwnd, ZUI_CHINFO_TUNER_LOCK_TIMER_ID);
                        }
                        break;

                    case ZUI_CHINFO_EVENT_TIME_TIMER_ID:
                        //from function MApp_UiMenu_Monitor_UpdateEventTime()
                        if( (pastEventInfo) && (g_u8EitCurPfVersionNum!=INVALID_VERSION_NUM) && IsDTVInUse())
                        {
                            if (pastEventInfo[bNextEvent].start_time[0] != 0 || pastEventInfo[bNextEvent].start_time[1] != 0 ||
                                pastEventInfo[bNextEvent].start_time[2] != 0 || pastEventInfo[bNextEvent].start_time[3] != 0 ||
                                pastEventInfo[bNextEvent].start_time[4] != 0 )
                            {
                                MApp_ZUI_API_KillTimer(hwnd, ZUI_CHINFO_EVENT_TIME_TIMER_ID);
                                MApp_ZUI_API_InvalidateAllSuccessors(HWND_CHINFO_BTM_BRIEF_PANE);
                            }
                        }
                        break;

                    case ZUI_CHINFO_VIDEO_MODE_TIMER_ID:
                        {
                            //wait until video signal ok...
                            if (_MApp_ZUI_ACT_GetInputSourceResolution() != NULL)
                            {
                                MApp_ZUI_API_KillTimer(hwnd, ZUI_CHINFO_VIDEO_MODE_TIMER_ID);
                                MApp_ZUI_API_InvalidateWindow(HWND_CHINFO_BTM_PR_VIDEO_RES);
                            }
                        }
                        break;

                    case ZUI_CHINFO_AUDIO_MODE_TIMER_ID:
                        {
                            //wait when audio mode changed...don't kill this timer

                            //from function MApp_UiMenu_Monitor_Update_CHANNEL_BANNER()
                            if(IsATVInUse()&&(MApp_IsSrcHasSignal()))//has signal
                            {
                                AUDIOMODE_TYPE eCurrentMTSType;
                                eCurrentMTSType = MApi_AUDIO_SIF_GetSelectedAudioMode();
                                if (_preCurrentMTSType != eCurrentMTSType)
                                {
                                    MApp_ZUI_API_InvalidateWindow(HWND_CHINFO_TOP_CH_MTS_TYPE);
                                }
                            }
                        }
                        break;
                }
            }
            break;
    }

    return DEFAULTWINPROC(hwnd, msg);
}
#endif


#undef MAPP_ZUI_ACTCHANNELINFO_ATSC_C

