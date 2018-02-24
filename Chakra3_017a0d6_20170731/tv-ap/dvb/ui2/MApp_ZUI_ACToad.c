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

#define MAPP_ZUI_ACTOAD_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "datatype.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_APIcomponent.h"
#include "MApp_ZUI_ACTeffect.h"
#include "OSDcp_String_EnumIndex.h"
#include "ZUI_exefunc.h"

#include "MApp_ZUI_ACToad.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_UiMenuDef.h"
#include "MApp_Sleep.h"

#include <string.h>
#include "msAPI_Memory.h"
#include "MApp_ZUI_APIalphatables.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_BlockSys.h"
#include "MApp_GlobalFunction.h"
#include "msAPI_OCP.h"
#include "MApp_ChannelChange.h"

#if (ENABLE_OAD)
#include "MApp_OAD.h"
#include "msAPI_Timer.h"
static U8 U8_OAD_Upgrade_Percent = 0xFF;

/////////////////////////////////////////////////////////////////////
extern void _MApp_ZUI_ACT_LoadMonthString(U8 month, LPTSTR str);
extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);
void _MApp_ZUI_API_ForceUpdateWindows(HWND aUpdateWindows[],U8 WinCount);

void MApp_ZUI_OADSwUpdate_ProgressBar(U8 percent)
{
    U8 u8tmp = 0;
    if(MApp_OAD_GetAppState() == EN_OAD_APP_STATE_UPGRADING)
    {
        static const HWND aUpdateWindows[] =
        {
            HWND_OAD_BG,
            HWND_OAD_BG_TOP,
            HWND_OAD_BG_L,
            HWND_OAD_BG_C,
            HWND_OAD_BG_R,
            HWND_OAD_TEXT1,
            HWND_OAD_TEXT2,
        };

        U8_OAD_Upgrade_Percent = percent;
        u8tmp = sizeof(aUpdateWindows)/sizeof(HWND);
        _MApp_ZUI_API_ForceUpdateWindows((HWND*)aUpdateWindows,u8tmp);
    }
    return;
}



void MApp_ZUI_ACT_AppShowOAD(void)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_OAD;

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
        ZUI_OAD_XSTART, ZUI_OAD_YSTART,
        ZUI_OAD_WIDTH, ZUI_OAD_HEIGHT);

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

    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_HIDE);
    if(bShowOadScanPage == FALSE)
    {
        if(MApp_OAD_GetMonitorState() == EN_OAD_MONITOR_STATE_DSI_SIGNAL)
        {
            if (OSD_COUNTRY_SETTING == OSD_COUNTRY_NEWZEALAND)
            {
                MApp_ZUI_API_ShowWindow(HWND_OAD_VERSION_PANE,SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_NZ_OAD_VERSION_PANE,SW_SHOW);
            }
			else if(OSD_COUNTRY_SETTING == E_NETHERLANDS)
			{
				MApp_ZUI_API_ShowWindow(HWND_NZ_OAD_VERSION_PANE,SW_HIDE);
				MApp_ZUI_API_ShowWindow(HWND_OAD_VERSION_PANE,SW_HIDE);
			}
            else
            {
                MApp_ZUI_API_ShowWindow(HWND_NZ_OAD_VERSION_PANE,SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_OAD_VERSION_PANE,SW_SHOW);
            }
            MApp_ZUI_API_ShowWindow(HWND_OAD_TEXT1,SW_SHOW);

        }
        else if(MApp_OAD_GetMonitorState() == EN_OAD_MONITOR_STATE_UNT_SIGNAL ||
            MApp_OAD_GetMonitorState() == EN_OAD_MONITOR_STATE_NIT_SIGNAL)
        {
            MApp_ZUI_API_ShowWindow(HWND_OAD_TEXT1,SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_OAD_TEXT2,SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_OAD_TEXT3,SW_SHOW);

            if (OSD_COUNTRY_SETTING == OSD_COUNTRY_NEWZEALAND)
            {
                MApp_ZUI_API_ShowWindow(HWND_OAD_VERSION_PANE,SW_HIDE);
            }
            else
            {
                MApp_ZUI_API_ShowWindow(HWND_NZ_OAD_VERSION_PANE,SW_HIDE);
            }
        }
        else if(MApp_OAD_GetMonitorState() == EN_OAD_MONITOR_STATE_NIT_DSI_SIGNAL)
        {
            MApp_ZUI_API_ShowWindow(HWND_OAD_TEXT1,SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_OAD_TEXT2,SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_OAD_BTN_NO,SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_OAD_BTN_YES,SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_OAD_VERSION_PANE,SW_HIDE);
        }
        else if(MApp_OAD_GetMonitorState() == EN_OAD_MONITOR_STATE_UNT_WAIT_SCHEDULE)
        {
            MApp_ZUI_API_ShowWindow(HWND_OAD_TEXT1,SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_OAD_TEXT2,SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_OAD_TEXT3,SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_OAD_VERSION_PANE,SW_HIDE);
        }
        else
        {
            if (OSD_COUNTRY_SETTING == OSD_COUNTRY_NEWZEALAND)
            {
                MApp_ZUI_API_ShowWindow(HWND_OAD_VERSION_PANE,SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_NZ_OAD_VERSION_PANE,SW_SHOW);
            }
            else
            {
                MApp_ZUI_API_ShowWindow(HWND_NZ_OAD_VERSION_PANE,SW_HIDE);
                MApp_ZUI_API_ShowWindow(HWND_OAD_VERSION_PANE,SW_SHOW);
            }
        }
        if(MApp_OAD_GetMonitorState()==EN_OAD_MONITOR_STATE_NIT_DSI_SIGNAL)
        {
            MApp_ZUI_API_ShowWindow(HWND_OAD_BTN_EXIT,SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_OAD_BTN_EXIT);
        }
        else
        {
            MApp_ZUI_API_ShowWindow(HWND_OAD_BTN_PANE,SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_OAD_BTN_EXIT,SW_HIDE);
            MApp_ZUI_API_SetFocus(HWND_OAD_BTN_PANE);
        }
        MApp_ZUI_API_ShowWindow(HWND_OAD_BG,SW_SHOW);
        MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_OPEN, E_ZUI_STATE_RUNNING);
    }
    else
    {
    #if 0 // wait to do
        MApp_ZUI_API_ShowWindow(HWND_OAD_TUNE_BG_PANE,SW_SHOW);
        MApp_ZUI_API_ShowWindow(HWND_OAD_TUNE_SCAN_PROGRESS_PANE,SW_SHOW);
    #endif
        //bShowOadScanPage = FALSE;
    }
}

//////////////////////////////////////////////////////////
// Key Handler

BOOLEAN MApp_ZUI_ACT_HandleOADKey(VIRTUAL_KEY_CODE key)
{

    switch(key)
    {
        case VK_EXIT:
            if((MApp_OAD_IsScheduleOnCheck() || MApp_OAD_GetSignalForStandby()) && MApp_OAD_IsDownloading())
            {
                return TRUE;
            }
            MApp_ZUI_ACT_ExecuteOADAction(EN_EXE_OAD_EXIT);
            return TRUE;

        /* Exclude Exit/Power key, OAD downloading process cannot response any other IRkey. */
        /* Otherwise, will cause OAD download CRC32 fail or trigger MBX to unmute video.     */
        /* Test case ** [DTG_Freeview NZ_OAD]NZ_OAD-0016 [TC16083000045] **             */
        default:
            break;
    }
    return FALSE;
}

void MApp_ZUI_ACT_TerminateOAD(void)
{
    ZUI_MSG(printf("[]term:OAD\n");)
}

//////////////////////////////////////////
BOOLEAN MApp_ZUI_ACT_ExecuteOADAction(U16 act)
{
    switch(act)
    {
        case EN_EXE_OAD_BTN_YES:
            MApp_OAD_SetAppState(EN_OAD_APP_STATE_YES);
            return TRUE;

        case EN_EXE_OAD_GOTOUPGRADE:
            /*if(!_bOCPFromMem)
            {
                msAPI_OCP_LoadAllStringToMem();
            } */
            MApp_ZUI_API_ShowWindow(HWND_OAD_BTN_EXIT,SW_HIDE);
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_OAD_TEXT_PANE);
            return TRUE;
        case EN_EXE_OAD_PAINTPROGRESS:
            if (MApp_OAD_GetAppState() == EN_OAD_APP_STATE_DOWNLOADING )
            {
                MApp_ZUI_API_InvalidateWindow(HWND_OAD_TEXT1);
                MApp_ZUI_API_InvalidateWindow(HWND_OAD_TEXT2);
            }
            return TRUE;
        case EN_EXE_OAD_EXIT:
            {
                BOOLEAN bDownloading = MApp_OAD_IsDownloading();

                if(bDownloading)
                {
                    MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
                    MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
                }
            }
            break;
        case EN_EXE_OAD_BTN_NO:
            {
                MApp_OAD_SetAppState(EN_OAD_APP_STATE_NO);
            }
            return TRUE;
    }
    return FALSE;
}

LPTSTR MApp_ZUI_ACT_GetOADDynamicText(HWND hwnd)
{
    U16 u16TempID = Empty;
    switch(hwnd)
    {
        case HWND_OAD_TEXT1:
        {
            if (MApp_OAD_GetAppState() == EN_OAD_APP_STATE_WAIT_USER && (
                MApp_OAD_GetMonitorState() == EN_OAD_MONITOR_STATE_DSI_SIGNAL ||
                MApp_OAD_GetMonitorState() == EN_OAD_MONITOR_STATE_UNT_SIGNAL ||
                MApp_OAD_GetMonitorState() == EN_OAD_MONITOR_STATE_NIT_SIGNAL ||
                MApp_OAD_GetMonitorState() == EN_OAD_MONITOR_STATE_UNT_WAIT_SCHEDULE))
            {
                if (OSD_COUNTRY_SETTING == OSD_COUNTRY_NEWZEALAND)
                {
                    U8 str[] = {"A software upgrade is available. Please select YES to upgrade now-thiswill take X minute- or leave in standby( off button on remote) when finished viewing to upgrade late. Thank you."};
                    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, str, strlen((const char *)str));
                    return CHAR_BUFFER;
                }
                else
                {
                    u16TempID = en_str_New_FW_is_available_for_upgrading;
                }
            }
            else if (MApp_OAD_GetAppState() == EN_OAD_APP_STATE_YES ||MApp_OAD_GetAppState() == EN_OAD_APP_STATE_DOWNLOADING)
            {
                if (OSD_COUNTRY_SETTING == OSD_COUNTRY_NEWZEALAND)
                {
                    U8 str[] = {"Your receiver is currently downloading an essential software upgrade. This will only take a few minutes. Please DO NOT adjust your receiver or switch OFF during this time. Thank You."};
                    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, str, strlen((const char *)str));
                    return CHAR_BUFFER;
                }
                else
                {
                    u16TempID = en_str_Download;
                }
            }
            else if (MApp_OAD_GetAppState() == EN_OAD_APP_STATE_UPGRADING)
            {
                if (OSD_COUNTRY_SETTING == OSD_COUNTRY_NEWZEALAND)
                {
                    U8 str[] = {"Your receiver is currently downloading an essential software upgrade. This will only take a few minutes. Please DO NOT adjust your receiver or switch OFF during this time. Thank You."};
                    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, str, strlen((const char *)str));
                    return CHAR_BUFFER;
                }
                else
                {
                    u16TempID = en_str_Software_UpdatebracketsOAD;
                }
            }
        }
        break;
        case HWND_OAD_TEXT2:
        {
            U8 u8persentage = MApp_OAD_GetProgress();
            if (MApp_OAD_GetAppState() == EN_OAD_APP_STATE_DOWNLOADING )
            {
                if (u8persentage > 100)
                    u8persentage = 100;

                MApp_ZUI_API_GetU16String((U16)u8persentage);
                U8 u8tmp = MApp_GetNoOfDigit(u8persentage);
                CHAR_BUFFER[u8tmp++] = CHAR_SPACE;
                CHAR_BUFFER[u8tmp++] = CHAR_PERCENT;
                CHAR_BUFFER[u8tmp++] = '\0';

                return CHAR_BUFFER;

            }
            else if (MApp_OAD_GetAppState() == EN_OAD_APP_STATE_UPGRADING)
            {
                if (U8_OAD_Upgrade_Percent <= 100)
                {
                    MApp_ZUI_API_GetU16String((U16)U8_OAD_Upgrade_Percent);
                    U8 u8tmp = MApp_GetNoOfDigit(U8_OAD_Upgrade_Percent);
                    CHAR_BUFFER[u8tmp++] = CHAR_SPACE;
                    CHAR_BUFFER[u8tmp++] = CHAR_PERCENT;
                    CHAR_BUFFER[u8tmp++] = '\0';
                }
                else if(U8_OAD_Upgrade_Percent == 0xFE)
                {
                    U8 str[] = {"CRC Error"};
                    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER,str, strlen((const char *)str));
                }
                else if(U8_OAD_Upgrade_Percent == 0xFD)
                {
                    U8 str[] = {"Fail to Burn AP Code"};
                    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, str, strlen((const char *)str));
                }
                else if(U8_OAD_Upgrade_Percent == 0xFC)
                {
                    U8 str[] = {"Unknown image type"};
                    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, str, strlen((const char *)str));
                }
                else if(U8_OAD_Upgrade_Percent == 0xFB)
                {
                    U8 str[] = {"Reboot fail"};
                    MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, str, strlen((const char *)str));
                }
                else if(U8_OAD_Upgrade_Percent == 0xFA)
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
            else if(MApp_OAD_GetMonitorState() == EN_OAD_MONITOR_STATE_UNT_SIGNAL)
            {
                u16TempID = en_str_OAD_Schedule_time;
            }
            else if(MApp_OAD_GetMonitorState() == EN_OAD_MONITOR_STATE_NIT_SIGNAL)
            {
                u16TempID = en_str_OAD_Service_CH;
            }
            else if(MApp_OAD_GetMonitorState() == EN_OAD_MONITOR_STATE_UNT_WAIT_SCHEDULE)
            {
                u16TempID = en_str_OAD_Schedule_time;
            }
        }
        break;

        case HWND_OAD_TEXT3:
        {
            if(MApp_OAD_GetMonitorState() == EN_OAD_MONITOR_STATE_UNT_WAIT_SCHEDULE)
            {
                ST_TIME _scheduleTime;
                LPTSTR str = CHAR_BUFFER;
                U32 u32Seconds = 0;

                u32Seconds = MApp_OAD_GetScheduleStart()/*+msAPI_Timer_GetOffsetTime()*/;
                MApp_ConvertSeconds2StTime(u32Seconds, &_scheduleTime);

                // day
                __MApp_UlongToString( _scheduleTime.u8Day, str, 2 );
                str += 2;
                *str++ = CHAR_SPACE;

                // month
                _MApp_ZUI_ACT_LoadMonthString(_scheduleTime.u8Month-1, str);
                str += MApp_ZUI_API_Strlen(str);
                *str++ = CHAR_SPACE;

                // year
                __MApp_UlongToString(_scheduleTime.u16Year, str, 4);
                str += MApp_ZUI_API_Strlen(str);
                *str++ = CHAR_SPACE;

                // HH:MM
                __MApp_UlongToString( _scheduleTime.u8Hour, str, 2 );
                str += 2;
                *str++=CHAR_COLON;
                __MApp_UlongToString( _scheduleTime.u8Min, str, 2 );
                str += 2;
                *str++='-';

                u32Seconds = MApp_OAD_GetScheduleEnd()/*+msAPI_Timer_GetOffsetTime()*/;
                MApp_ConvertSeconds2StTime(u32Seconds, &_scheduleTime);
                // HH:MM
                __MApp_UlongToString( _scheduleTime.u8Hour, str, 2 );
                str += 2;
                *str++=CHAR_COLON;
                __MApp_UlongToString( _scheduleTime.u8Min, str, 2 );
                str += 2;

                *str=0;
                return CHAR_BUFFER;
            }
            else if(MApp_OAD_GetMonitorState() == EN_OAD_MONITOR_STATE_NIT_SIGNAL)
            {
                U16 u16lcn = MApp_OAD_GetServiceLcn();
                MApp_UlongToU16String(u16lcn, CHAR_BUFFER, (S8)MApp_GetNoOfDigit(u16lcn));
                return CHAR_BUFFER;
            }
        }
        break;
    #if 0 // TODO
        case HWND_OAD_TEXT4:
        {
            if (MApp_OAD_GetAppState() == EN_OAD_APP_STATE_WAIT_USER && (
                MApp_OAD_GetMonitorState() == EN_OAD_MONITOR_STATE_DSI_SIGNAL ||
                MApp_OAD_GetMonitorState() == EN_OAD_MONITOR_STATE_UNT_SIGNAL ||
                MApp_OAD_GetMonitorState() == EN_OAD_MONITOR_STATE_NIT_SIGNAL))
            {
                u16TempID = en_str_OAD_Software_download;
            }
        }
    #endif
        case HWND_OAD_TV_VERSION:
        case HWND_NZ_OAD_TV_VERSION:
        {

            if(MApp_OAD_GetMonitorState() == EN_OAD_MONITOR_STATE_DSI_SIGNAL)
            {
                U16 curStringLen = 0;
                //U8 digit;
                U32 u32tv = 0;
                U32 u32ts = 0;
                char cStrVer[6];

                //cStrVer[6]=0;
                MApp_OAD_GetVersion(&u32tv,&u32ts);
                MApp_ZUI_API_Strcpy(&CHAR_BUFFER[0], MApp_ZUI_API_GetString(en_str_TV_Version));
                curStringLen = MApp_ZUI_API_Strlen(CHAR_BUFFER);
                CHAR_BUFFER[curStringLen] = CHAR_SPACE;
                curStringLen +=1;
                snprintf(cStrVer, 6, "v%bx.%02bx",(u32tv>>8&0xFF),(u32tv&0xFF));
                MApp_ZUI_API_StringBuffU8toU16(&CHAR_BUFFER[curStringLen],(U8 *)cStrVer,6);
                curStringLen +=6;
                CHAR_BUFFER[curStringLen] = 0;
                return CHAR_BUFFER;
            }
        }
        break;

        case HWND_OAD_TS_VERSION:
        case HWND_NZ_OAD_TS_VERSION:
        {

            if(MApp_OAD_GetMonitorState() == EN_OAD_MONITOR_STATE_DSI_SIGNAL)
            {
                U16 curStringLen = 0;
                //U8 digit;
                U32 u32tv = 0;
                U32 u32ts = 0;
                char cStrVer[6];

                //cStrVer[6]=0;
                MApp_OAD_GetVersion(&u32tv,&u32ts);
                MApp_ZUI_API_Strcpy(&CHAR_BUFFER[0], MApp_ZUI_API_GetString(en_str_Stream_Version));
                curStringLen = MApp_ZUI_API_Strlen(CHAR_BUFFER);
                CHAR_BUFFER[curStringLen] = CHAR_SPACE;
                curStringLen +=1;
                snprintf(cStrVer, 6, "v%bx.%02bx",(u32ts>>8&0xFF),(u32ts&0xFF));
                MApp_ZUI_API_StringBuffU8toU16(&CHAR_BUFFER[curStringLen],(U8 *)cStrVer,6);
                curStringLen +=6;
                CHAR_BUFFER[curStringLen] = 0;
                return CHAR_BUFFER;
            }
        }
        break;

    }

    if (u16TempID != Empty)
    {
        return MApp_ZUI_API_GetString(u16TempID);
    }
    return 0; //for empty string....
}

void MApp_ZUI_ACT_ShowDownloadUI(void)
{
    MApp_ZUI_API_ShowWindow(HWND_OAD_TV_VERSION,SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_NZ_OAD_TV_VERSION,SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_OAD_TS_VERSION,SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_NZ_OAD_TS_VERSION,SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_OAD_YES_TO_UPGRADE,SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_OAD_IGNORE_UPGRADE,SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_OAD_TEXT2,SW_SHOW);
    MApp_ZUI_API_InvalidateAllSuccessors(HWND_OAD_TEXT_PANE);
}
#endif //ENABLE_OAD
#undef MAPP_ZUI_ACTOAD_C
