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

#define MAPP_ZUI_ACTPVRBROWSER_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "Board.h"


#if ENABLE_PVR_BROWSER


#include "datatype.h"
#include "MsCommon.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_ACTmainpage.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_ACTglobal.h"
#include "OSDcp_String_EnumIndex.h"
#include "ZUI_exefunc.h"

#include "MApp_ZUI_ACTpvrBrowser.h"
#include "MApp_OSDPage_Main.h"
#include "MApp_Menu_Main.h"

#include "IOUtil.h"
#include "MApp_GlobalFunction.h"
#include "OSDcp_Bitmap_EnumIndex.h"


/////////////////////////////////////////////////////////////////////

static EN_OSDPAGE_STATE _enTargetState;

#define STRBUFF_LENGTH 10

extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);
extern BOOLEAN _MApp_ZUI_API_WindowProcOnIdle(void);
extern LPTSTR _MApp_ZUI_ACT_GetLocalClockTimeString(LPTSTR str);

static  HWND _ZUI_TBLSEG _PvrBrowserHwndList[PVR_BROWSER_ITEM_PER_PAGE]=
{
    HWND_PVR_BROWSER_ITEM0,
    HWND_PVR_BROWSER_ITEM1,
    HWND_PVR_BROWSER_ITEM2,
    HWND_PVR_BROWSER_ITEM3,
    HWND_PVR_BROWSER_ITEM4,
    HWND_PVR_BROWSER_ITEM5,
    HWND_PVR_BROWSER_ITEM6,
    HWND_PVR_BROWSER_ITEM7,
    HWND_PVR_BROWSER_ITEM8,
    HWND_PVR_BROWSER_ITEM9,
};

static  HWND _ZUI_TBLSEG _PvrBrowserTriIconHwndList[PVR_BROWSER_ITEM_PER_PAGE]=
{
    HWND_PVR_BROWSER_ITEM0_R_ARROW,
    HWND_PVR_BROWSER_ITEM1_R_ARROW,
    HWND_PVR_BROWSER_ITEM2_R_ARROW,
    HWND_PVR_BROWSER_ITEM3_R_ARROW,
    HWND_PVR_BROWSER_ITEM4_R_ARROW,
    HWND_PVR_BROWSER_ITEM5_R_ARROW,
    HWND_PVR_BROWSER_ITEM6_R_ARROW,
    HWND_PVR_BROWSER_ITEM7_R_ARROW,
    HWND_PVR_BROWSER_ITEM8_R_ARROW,
    HWND_PVR_BROWSER_ITEM9_R_ARROW,
};

static U8 _MApp_ZUI_ACT_PvrBrowserListMapToIndex(HWND hwnd)
{
    U8 i;
    for (i = 0; i < PVR_BROWSER_ITEM_PER_PAGE; i++)
    {
        if (hwnd == _PvrBrowserHwndList[i] ||
            MApp_ZUI_API_IsSuccessor(_PvrBrowserHwndList[i], hwnd))
        {
            return i;
        }
    }
    return 0;
}

static HWND _MApp_ZUI_ACT_PvrBrowserIndexMapToWindow(U8 u8Index)
{
    if (u8Index >= PVR_BROWSER_ITEM_PER_PAGE)
        return HWND_INVALID;
    return _PvrBrowserHwndList[u8Index];

}

static void _MApp_ZUI_ACT_PvrBrowser_ShowTriIcon(U32 u8Flag )
{
    U8 i;
    for (i = 0; i < PVR_BROWSER_ITEM_PER_PAGE; i++)
    {
        MApp_ZUI_API_ShowWindow(_PvrBrowserTriIconHwndList[i], u8Flag);
    }
}

void MApp_ZUI_ACT_AppShowPvrBrowser(void)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_PVR_BROWSER;

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
        ZUI_PVR_XSTART, ZUI_PVR_YSTART,
        ZUI_PVR_WIDTH, ZUI_PVR_HEIGHT);

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

#if (ENABLE_UI_3D_PROCESS)
    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);
#else
    MApp_ZUI_API_ShowWindow(HWND_PVR_BROWSER_BG_PANE, SW_SHOW);
    MApp_ZUI_API_ShowWindow(HWND_PVR_BROWSER_LIST_PANE, SW_SHOW);
#endif
    MApp_ZUI_API_ShowWindow(HWND_PVR_BROWSER_INFO_PANE, SW_HIDE);

    if(MApp_PvrBrowser_IsAnyFilePlaying() ||
        MApp_PvrBrowser_IsAnyFileRecording())
    {
        MApp_ZUI_API_ShowWindow(HWND_PVR_BROWSER_BOTTOM_DELETE_BTN, SW_HIDE);
    }

    if(g_PvrBrowser_TotalItem >0)
    {
        if(g_PvrBrowser_FocusItem != 0xFF)
            MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_PvrBrowserIndexMapToWindow(g_PvrBrowser_FocusItem%PVR_BROWSER_ITEM_PER_PAGE));
        else
        {
                MApp_ZUI_API_SetFocus(HWND_PVR_BROWSER_ITEM0);
        }
    }
    ZUI_MSG(printf("[Show]PvrBrow\n");)
    MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_PAGE_EXIT, E_ZUI_STATE_RUNNING);
}


//////////////////////////////////////////////////////////
// Key Handler

typedef struct _MENU_KEY2BTN_STRUCT
{
    VIRTUAL_KEY_CODE key;
    HWND hwnd;
} MENU_KEY2BTN_STRUCT;

BOOLEAN MApp_ZUI_ACT_HandlePvrBrowserKey(VIRTUAL_KEY_CODE key)
{
    //note: this function will be called in running state

    //reset timer if any key
    MApp_ZUI_API_ResetTimer(HWND_PVR_BROWSER_BG_PANE, 0);

    //show click animation
/*    {
        static  MENU_KEY2BTN_STRUCT _ZUI_TBLSEG _key2btn[] =
        {
            {VK_SELECT, HWND_PVR_BROWSER_BOTTOM_OK_BTN},
            {VK_RED, HWND_PVR_BROWSER_BOTTOM_DELETE_BTN},
            {VK_INFO, HWND_PVR_BROWSER_BOTTOM_INFO_BTN},
            {VK_INDEX, HWND_PVR_BROWSER_BOTTOM_INDEX_BTN},
            {VK_UP, HWND_PVR_BROWSER_BOTTOM_ARROW_UP},
            {VK_DOWN, HWND_PVR_BROWSER_BOTTOM_ARROW_DOWN},
            {VK_LEFT, HWND_PVR_BROWSER_BOTTOM_ARROW_LEFT},
            {VK_RIGHT, HWND_PVR_BROWSER_BOTTOM_ARROW_RIGHT},
        };
        U8 i;

        for (i = 0; i < COUNTOF(_key2btn); i++)
        {
            if (_key2btn[i].key == key)
            {
                MApp_ZUI_API_SetTimer(_key2btn[i].hwnd, 0, BUTTONANICLICK_PERIOD);
                MApp_ZUI_API_InvalidateWindow(_key2btn[i].hwnd);
                break;
            }
        }
    }
*/
    switch(key)
    {
        case VK_EXIT:
        case VK_MENU:
            MApp_ZUI_ACT_ExecutePvrBrowserAction(EN_EXE_CLOSE_CURRENT_OSD);
            return TRUE;

        case VK_POWER:
            MApp_ZUI_ACT_ExecutePvrBrowserAction(EN_EXE_POWEROFF);
            return TRUE;
        case VK_INDEX:
            MApp_UiPvr_Browser_KeyProcessor(KEY_INDEX);
            if(g_PvrBrowser_FocusItem !=0)
            MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_PvrBrowserIndexMapToWindow(g_PvrBrowser_FocusItem));
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_PVR_BROWSER_TOP_HALF_BANNER_TITLE_TYPE);
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_PVR_BROWSER_LIST_PANE);
            return TRUE;

        case VK_SELECT:
        case VK_PLAY:
            MApp_UiPvr_Browser_KeyProcessor(KEY_PLAY);
            return TRUE;

        case VK_UP:
            if(g_PvrBrowser_TotalItem > 0)
            {
                MApp_UiPvr_Browser_KeyProcessor(KEY_UP);
                MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_PvrBrowserIndexMapToWindow(g_PvrBrowser_FocusItem%PVR_BROWSER_ITEM_PER_PAGE));
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_PVR_BROWSER_LIST_PANE);
            }
            return TRUE;

        case VK_DOWN:
            if(g_PvrBrowser_TotalItem > 0)
            {
                MApp_UiPvr_Browser_KeyProcessor(KEY_DOWN);
                MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_PvrBrowserIndexMapToWindow(g_PvrBrowser_FocusItem%PVR_BROWSER_ITEM_PER_PAGE));
                MApp_ZUI_API_InvalidateAllSuccessors(HWND_PVR_BROWSER_LIST_PANE);
            }
            return TRUE;

        case VK_LEFT:
            MApp_ZUI_ACT_PVR_BROWSER_FileInfo_Close();
            return TRUE;

        case VK_RIGHT:
            if(g_PvrBrowser_TotalItem > 0)
            {
                MApp_ZUI_ACT_PVR_BROWSER_FileInfo_Open();
            }
            return TRUE;

        case VK_INFO:
        case VK_GREEN:
            if(MApp_ZUI_API_IsWindowVisible(HWND_PVR_BROWSER_INFO_PANE))
                MApp_ZUI_ACT_PVR_BROWSER_FileInfo_Close();
            else
			{
				if(g_PvrBrowser_TotalItem > 0)
				{
					MApp_ZUI_ACT_PVR_BROWSER_FileInfo_Open();
				}
			}

            return TRUE;

        case VK_RED:
            MApp_UiPvr_Browser_KeyProcessor(KEY_RED);

            if(g_PvrBrowser_TotalItem>0)
                MApp_ZUI_API_SetFocus(_MApp_ZUI_ACT_PvrBrowserIndexMapToWindow(g_PvrBrowser_FocusItem));
            else
            {
                MApp_ZUI_ACT_PVR_BROWSER_FileInfo_Close();
                MApp_ZUI_API_SetFocus(HWND_PVR_BROWSER_BG_C); //disable focus
            }

            MApp_ZUI_API_InvalidateAllSuccessors(HWND_PVR_BROWSER_LIST_PANE);
            return TRUE;

        default:
            break;
    }
    return FALSE;
}

void MApp_ZUI_ACT_TerminatePvrBrowser(void)
{
    ZUI_MSG(printf("[]term:pvrBrow\n");)
    g_PvrMenuPageType = MENU_PVR_NONE;
    MApp_OSDPage_SetState(_enTargetState);
}

BOOLEAN MApp_ZUI_ACT_ExecutePvrBrowserAction(U16 act)
{
    switch(act)
    {
        case EN_EXE_CLOSE_CURRENT_OSD:
            _enTargetState = STATE_OSDPAGE_CLEAN_UP;
            #if (ENABLE_UI_3D_PROCESS)
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_CLOSE, E_ZUI_STATE_TERMINATE);
            #else
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_PAGE_FADE_OUT, E_ZUI_STATE_TERMINATE);
            #endif
            return TRUE;

        case EN_EXE_POWEROFF:
            _enTargetState = STATE_OSDPAGE_GOTO_STANDBY;
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_PAGE_FADE_OUT, E_ZUI_STATE_TERMINATE);
            return TRUE;

    }
    return FALSE;
}

S16 MApp_ZUI_ACT_GetPvrBrowserDynamicValue(HWND hwnd)
{
    switch(hwnd)
    {
        case HWND_PVR_FORMAT_DISK_PROGRESSBAR:
        {
            if(g_PVRCheckFSStatus == EN_PVR_CHKSTS_FORMAT_PROGRESS)
            {
                return (U16)MApp_PVR_DiskFormatGetPercentage();
            }
        #if (ENABLE_BULK_FILE_SYSTEM)
            else if(g_PVRCheckFSStatus == EN_PVR_CHKSTS_CREATE_FILE_SYSTEM_PROGRESS)
            {
                return (U16)MApp_PVR_DiskFormatGetCreateFilePercentage();
            }
        #endif
            else
            {
                return 0;
            }
        }
         default:
            break;
    }
    return 0; //for empty  data
}

U16 MApp_ZUI_ACT_GetPvrBrowserDynamicBitmap(HWND hwnd, DRAWSTYLE_TYPE ds_type)
{
    ds_type=ds_type;
    switch(hwnd)
    {
        case HWND_PVR_BROWSER_ITEM0_ICON:
        case HWND_PVR_BROWSER_ITEM1_ICON:
        case HWND_PVR_BROWSER_ITEM2_ICON:
        case HWND_PVR_BROWSER_ITEM3_ICON:
        case HWND_PVR_BROWSER_ITEM4_ICON:
        case HWND_PVR_BROWSER_ITEM5_ICON:
        case HWND_PVR_BROWSER_ITEM6_ICON:
        case HWND_PVR_BROWSER_ITEM7_ICON:
        case HWND_PVR_BROWSER_ITEM8_ICON:
        case HWND_PVR_BROWSER_ITEM9_ICON:
        {
            U16 u16DrawItemIdex = g_PvrBrowser_PageStartItem + _MApp_ZUI_ACT_PvrBrowserListMapToIndex(hwnd);
            BOOLEAN FileStatus;
            if(u16DrawItemIdex < g_PvrBrowser_TotalItem)
            {

                if(MApp_PvrBrowser_GetFileAttribute(E_PVR_ATTR_IS_PLAYING, g_PVRBrowerSort,
                    u16DrawItemIdex, &FileStatus, sizeof(BOOLEAN)) == E_PVR_RET_OK)
                {
                    if(FileStatus == TRUE)
                    {
                        if(ds_type == DS_FOCUS)
                            return E_BMP_ICON_PLAY_F;
                        else
                            return E_BMP_ICON_PLAY_N;
                    }
                }

                if(MApp_PvrBrowser_GetFileAttribute(E_PVR_ATTR_IS_RECORDING, g_PVRBrowerSort,
                    u16DrawItemIdex, &FileStatus, sizeof(BOOLEAN)) == E_PVR_RET_OK)
                {
                    if(FileStatus == TRUE)
                    {
                        if(ds_type == DS_FOCUS)
                            return E_BMP_ICON_RECORD_F;
                        else
                            return E_BMP_ICON_RECORD_N;
                    }
                }
            }
            return 0xFFFF; //for empty bitmap....
        }
            break;
        default:
            break;


    }

    return 0xFFFF; //for empty bitmap....
}

LPTSTR MApp_ZUI_ACT_GetPvrBrowserDynamicText(HWND hwnd)
{
    switch(hwnd)
    {
        case HWND_PVR_BROWSER_ITEM0_TEXT:
        case HWND_PVR_BROWSER_ITEM1_TEXT:
        case HWND_PVR_BROWSER_ITEM2_TEXT:
        case HWND_PVR_BROWSER_ITEM3_TEXT:
        case HWND_PVR_BROWSER_ITEM4_TEXT:
        case HWND_PVR_BROWSER_ITEM5_TEXT:
        case HWND_PVR_BROWSER_ITEM6_TEXT:
        case HWND_PVR_BROWSER_ITEM7_TEXT:
        case HWND_PVR_BROWSER_ITEM8_TEXT:
        case HWND_PVR_BROWSER_ITEM9_TEXT:
        {
            U16 u16DrawItemIdex = g_PvrBrowser_PageStartItem + _MApp_ZUI_ACT_PvrBrowserListMapToIndex(hwnd);
            if(u16DrawItemIdex < g_PvrBrowser_TotalItem)
            {
                if(E_PVR_RET_OK == MApp_PvrBrowser_GetFileAttribute(E_PVR_ATTR_PROGRAM_NAME, g_PVRBrowerSort
                    , u16DrawItemIdex, (BYTE*)CHAR_BUFFER, PVR_BROWSER_MAX_FILE_NAME_LEN*2))
                {
                    U8 len;
                    len = MApp_ZUI_API_Strlen(CHAR_BUFFER);
                    if (len ==0)
                    {
                        MApp_ZUI_API_GetString(en_str_No_Information);

                        len = MApp_ZUI_API_Strlen(CHAR_BUFFER);
                        CHAR_BUFFER[len] = CHAR_STAR;
                        CHAR_BUFFER[len+1] = 0;
                    }
                    else
                    {
                        if (len > (PVR_BROWSER_SIZE_OF_FILE_NAME - 4))
                        {
                            CHAR_BUFFER[PVR_BROWSER_SIZE_OF_FILE_NAME-4] = CHAR_DOT;
                            CHAR_BUFFER[PVR_BROWSER_SIZE_OF_FILE_NAME -3] = CHAR_DOT;
                            CHAR_BUFFER[PVR_BROWSER_SIZE_OF_FILE_NAME -2] = CHAR_DOT;
                            CHAR_BUFFER[PVR_BROWSER_SIZE_OF_FILE_NAME -1] = 0;
                        }
                        else
                        {
                            CHAR_BUFFER[len] = 0;
                        }
                    }

                    return CHAR_BUFFER;
                }
                else
                {
                    __ASSERT(0);
                    return 0;
                }
            }
            break;
        }

        case HWND_PVR_BROWSER_TOP_HALF_BANNER_TITLE_TYPE:
        {
            U8 len;
            len = 0;
            CHAR_BUFFER[len++] = CHAR_SPACE;
            CHAR_BUFFER[len++] = CHAR_MINUS;
            CHAR_BUFFER[len++] = CHAR_SPACE;
            CHAR_BUFFER[len++] = 0;
            switch(g_PVRBrowerSort)
            {
                default:
                case SORT_NONE:
                    MApp_ZUI_API_Strcpy(CHAR_BUFFER, MApp_ZUI_API_GetString( en_str_No_Sort));
                    break;
                case SORT_PROG_NAME:
                    MApp_ZUI_API_Strcpy(CHAR_BUFFER, MApp_ZUI_API_GetString( en_str_Programme));
                    break;
                case SORT_CHANNEL_NAME:
                    MApp_ZUI_API_Strcpy(CHAR_BUFFER, MApp_ZUI_API_GetString(en_str_Channel));
                    break;
                case SORT_FILE_NAME:
                    MApp_ZUI_API_Strcpy(CHAR_BUFFER, MApp_ZUI_API_GetString( en_str_FileName));
                    break;
                case SORT_FILE_LENGTH:
                    MApp_ZUI_API_Strcpy(CHAR_BUFFER, MApp_ZUI_API_GetString( en_str_FileLength));
                    break;
                case SORT_PROG_TIME:
                    MApp_ZUI_API_Strcpy(CHAR_BUFFER, MApp_ZUI_API_GetString(en_str_Time));
                    break;
            }

            len = MApp_ZUI_API_Strlen(CHAR_BUFFER);
            CHAR_BUFFER[len++] = CHAR_SPACE;
            CHAR_BUFFER[len++] = CHAR_DOWN_ARROW;
            CHAR_BUFFER[len] = 0;
            return (LPTSTR) CHAR_BUFFER;
        }
        break;
        case HWND_PVR_BROWSER_INFO_DATE:
        {
            U8 len = 0;
            U32 u32Time = 0;

            //memset(CHAR_BUFFER, 0, sizeof(CHAR_BUFFER));
            ZUI_CLEAR_STRING_BUFFER(); //Fix coverity 182848

            CHAR_BUFFER[len++] = CHAR_LEFT_BRACKET;
            CHAR_BUFFER[len++] = CHAR_D;
            CHAR_BUFFER[len++] = CHAR_A;
            CHAR_BUFFER[len++] = CHAR_T;
            CHAR_BUFFER[len++] = CHAR_E;
            CHAR_BUFFER[len++] = CHAR_RIGHT_BRACKET;
            CHAR_BUFFER[len++] = CHAR_SPACE;
            CHAR_BUFFER[len++] = 0;

            if(MApp_PvrBrowser_GetFileAttribute(E_PVR_ATTR_PROGRAM_START_TIME, g_PVRBrowerSort,
                (g_PvrBrowser_PageStartItem + g_PvrBrowser_FocusItem),
                (BYTE *)&u32Time, sizeof(U32))== E_PVR_RET_OK)
            {
                ST_TIME stTime;
                U16 strDate[11];

                MApp_ConvertSeconds2StTime(u32Time, &stTime);
                memset(strDate,0,sizeof(strDate));
                MApp_UlongToU16String(stTime.u16Year, &strDate[0], 4);
                strDate[4] = CHAR_SLASH;
                MApp_UlongToU16String(stTime.u8Month, &strDate[5], 2);
                strDate[7] = CHAR_SLASH;
                MApp_UlongToU16String(stTime.u8Day, &strDate[8], 2);
                strDate[10] = '\0';

                 MApp_ZUI_API_Strcat(CHAR_BUFFER,strDate);
            }
            return (LPTSTR) CHAR_BUFFER;
        }

        case HWND_PVR_BROWSER_INFO_TIME:
        {
            U8 len = 0;
            U32 u32Time = 0;

            CHAR_BUFFER[len++] = CHAR_LEFT_BRACKET;
            CHAR_BUFFER[len++] = CHAR_T;
            CHAR_BUFFER[len++] = CHAR_I;
            CHAR_BUFFER[len++] = CHAR_M;
            CHAR_BUFFER[len++] = CHAR_E;
            CHAR_BUFFER[len++] = CHAR_RIGHT_BRACKET;
            CHAR_BUFFER[len++] = CHAR_SPACE;
            CHAR_BUFFER[len++] = 0;

            if(MApp_PvrBrowser_GetFileAttribute(E_PVR_ATTR_PROGRAM_START_TIME, g_PVRBrowerSort,
                (g_PvrBrowser_PageStartItem + g_PvrBrowser_FocusItem),
                (BYTE*)&u32Time, sizeof(U32))== E_PVR_RET_OK)
            {
                ST_TIME stTime;
                U16 strTime[9];

                MApp_ConvertSeconds2StTime(u32Time, &stTime);
                memset(strTime,0,sizeof(strTime));
                MApp_UlongToU16String(stTime.u8Hour, &strTime[0], 2 );
                strTime[2] = ':';
                MApp_UlongToU16String(stTime.u8Min, &strTime[3], 2 );
                strTime[5] = ':';
                MApp_UlongToU16String(stTime.u8Sec, &strTime[6], 2 );
                strTime[8] = '\0';

                MApp_ZUI_API_Strcat(CHAR_BUFFER,strTime);

            }
            return CHAR_BUFFER;
        }

        case HWND_PVR_BROWSER_INFO_DURATION:
        {
            U8 len = 0;
            U32 u32Time = 0;
            BOOLEAN IsRecording = 0;

            CHAR_BUFFER[len++] = CHAR_LEFT_BRACKET;
            CHAR_BUFFER[len++] = CHAR_D;
            CHAR_BUFFER[len++] = CHAR_U;
            CHAR_BUFFER[len++] = CHAR_R;
            CHAR_BUFFER[len++] = CHAR_A;
            CHAR_BUFFER[len++] = CHAR_T;
            CHAR_BUFFER[len++] = CHAR_I;
            CHAR_BUFFER[len++] = CHAR_O;
            CHAR_BUFFER[len++] = CHAR_N;
            CHAR_BUFFER[len++] = CHAR_RIGHT_BRACKET;
            CHAR_BUFFER[len++] = CHAR_SPACE;
            CHAR_BUFFER[len++] = 0;

            MApp_PvrBrowser_GetFileAttribute(E_PVR_ATTR_IS_RECORDING, g_PVRBrowerSort,
                (g_PvrBrowser_PageStartItem + g_PvrBrowser_FocusItem),
                (BYTE*)&IsRecording, sizeof(BOOLEAN));

            if(IsRecording)
            {//show dynamic number during recording
                u32Time = (MApp_Record_GetEndTimeSec(RECORD_PATH_DEFAULT) - MApp_Record_GetStartTimeSec(RECORD_PATH_DEFAULT));
            }
            else if(MApp_PvrBrowser_GetFileAttribute(E_PVR_ATTR_PROGRAM_DURATION, g_PVRBrowerSort,
                    (g_PvrBrowser_PageStartItem + g_PvrBrowser_FocusItem),
                    (BYTE*)&u32Time, sizeof(U32))== E_PVR_RET_OK)
            { //goet number from BKFS
            }
            else
            {//exception
                return CHAR_BUFFER;
            }

            {
                U16 strTime[11];
                memset(strTime,0,sizeof(strTime));
                MApp_UlongToU16String(u32Time/SECONDS_PER_HOUR, &strTime[0], 4 );
                strTime[4] = ':';
                MApp_UlongToU16String((u32Time%SECONDS_PER_HOUR)/SECONDS_PER_MIN, &strTime[5], 2 );
                strTime[7] = ':';
                MApp_UlongToU16String(u32Time%SECONDS_PER_MIN, &strTime[8], 2 );
                strTime[10] = '\0';

                MApp_ZUI_API_Strcat(CHAR_BUFFER,strTime);
            }
            return CHAR_BUFFER;
        }

        case HWND_PVR_BROWSER_INFO_CHANNEL:
        {
            U8 len = 0;

            CHAR_BUFFER[len++] = CHAR_LEFT_BRACKET;
            CHAR_BUFFER[len++] = CHAR_C;
            CHAR_BUFFER[len++] = CHAR_H;
            CHAR_BUFFER[len++] = CHAR_A;
            CHAR_BUFFER[len++] = CHAR_N;
            CHAR_BUFFER[len++] = CHAR_N;
            CHAR_BUFFER[len++] = CHAR_E;
            CHAR_BUFFER[len++] = CHAR_L;
            CHAR_BUFFER[len++] = CHAR_SPACE;
            CHAR_BUFFER[len++] = CHAR_N;
            CHAR_BUFFER[len++] = CHAR_A;
            CHAR_BUFFER[len++] = CHAR_M;
            CHAR_BUFFER[len++] = CHAR_E;
            CHAR_BUFFER[len++] = CHAR_RIGHT_BRACKET;
            CHAR_BUFFER[len++] = CHAR_SPACE;

             MApp_PvrBrowser_GetFileAttribute(E_PVR_ATTR_CHANNEL_NAME, g_PVRBrowerSort,
                (g_PvrBrowser_PageStartItem + g_PvrBrowser_FocusItem),
                (BYTE*)&CHAR_BUFFER[len], PVR_BROWSER_MAX_CHANNEL_NAME_LEN*2);

            return (LPTSTR) CHAR_BUFFER;
        }

        case HWND_PVR_BROWSER_INFO_PROGRAM:
        {
            U8 len = 0;
            CHAR_BUFFER[len++] = CHAR_LEFT_BRACKET;
            CHAR_BUFFER[len++] = CHAR_P;
            CHAR_BUFFER[len++] = CHAR_R;
            CHAR_BUFFER[len++] = CHAR_O;
            CHAR_BUFFER[len++] = CHAR_G;
            CHAR_BUFFER[len++] = CHAR_R;
            CHAR_BUFFER[len++] = CHAR_A;
            CHAR_BUFFER[len++] = CHAR_M;
            CHAR_BUFFER[len++] = CHAR_SPACE;
            CHAR_BUFFER[len++] = CHAR_N;
            CHAR_BUFFER[len++] = CHAR_A;
            CHAR_BUFFER[len++] = CHAR_M;
            CHAR_BUFFER[len++] = CHAR_E;
            CHAR_BUFFER[len++] = CHAR_RIGHT_BRACKET;
            CHAR_BUFFER[len++] = CHAR_SPACE;

             MApp_PvrBrowser_GetFileAttribute(E_PVR_ATTR_PROGRAM_NAME, g_PVRBrowerSort,
                (g_PvrBrowser_PageStartItem + g_PvrBrowser_FocusItem),
                (BYTE*)&CHAR_BUFFER[len], PVR_BROWSER_MAX_PROGRAM_NAME_LEN*2);

            return (LPTSTR) CHAR_BUFFER;
        }
            break;
        case HWND_PVR_BROWSER_INFO_DESCRIPTION:
        {
            U8 len = 0;
            CHAR_BUFFER[len++] = CHAR_LEFT_BRACKET;
            CHAR_BUFFER[len++] = CHAR_P;
            CHAR_BUFFER[len++] = CHAR_R;
            CHAR_BUFFER[len++] = CHAR_O;
            CHAR_BUFFER[len++] = CHAR_G;
            CHAR_BUFFER[len++] = CHAR_R;
            CHAR_BUFFER[len++] = CHAR_A;
            CHAR_BUFFER[len++] = CHAR_M;
            CHAR_BUFFER[len++] = CHAR_SPACE;
            CHAR_BUFFER[len++] = CHAR_D;
            CHAR_BUFFER[len++] = CHAR_E;
            CHAR_BUFFER[len++] = CHAR_S;
            CHAR_BUFFER[len++] = CHAR_C;
            CHAR_BUFFER[len++] = CHAR_R;
            CHAR_BUFFER[len++] = CHAR_I;
            CHAR_BUFFER[len++] = CHAR_P;
            CHAR_BUFFER[len++] = CHAR_T;
            CHAR_BUFFER[len++] = CHAR_I;
            CHAR_BUFFER[len++] = CHAR_O;
            CHAR_BUFFER[len++] = CHAR_N;
            CHAR_BUFFER[len++] = CHAR_RIGHT_BRACKET;
            CHAR_BUFFER[len++] = CHAR_SPACE;

            MApp_PvrBrowser_GetFileAttribute(E_PVR_ATTR_PROGRAM_DESC, g_PVRBrowerSort,
                (g_PvrBrowser_PageStartItem + g_PvrBrowser_FocusItem),
                (BYTE*)&CHAR_BUFFER[len], PVR_BROWSER_MAX_PROGRAM_DESC_LEN*2);

            return (LPTSTR) CHAR_BUFFER;

        }
            break;


    }

    return 0; //for empty string....
}

S32 MApp_ZUI_ACT_PvrBrowserWinProc(HWND hwnd, PMSG msg)
{
    switch(msg->message)
    {
        case MSG_NOTIFY_SETFOCUS:
            switch(hwnd)
            {
                case HWND_PVR_BROWSER_ITEM0:
                case HWND_PVR_BROWSER_ITEM1:
                case HWND_PVR_BROWSER_ITEM2:
                case HWND_PVR_BROWSER_ITEM3:
                case HWND_PVR_BROWSER_ITEM4:
                case HWND_PVR_BROWSER_ITEM5:
                case HWND_PVR_BROWSER_ITEM6:
                case HWND_PVR_BROWSER_ITEM7:
                case HWND_PVR_BROWSER_ITEM8:
                case HWND_PVR_BROWSER_ITEM9:
                {
                    BOOLEAN ret;
                    RECT move_new_rect;
                    RECT target_rect;
                    HWND target = MApp_ZUI_API_GetFocus();
                    HWND move = HWND_PVR_BROWSER_INFO_PANE;

                    memset(&move_new_rect, 0, sizeof(RECT));
                    memset(&target_rect, 0, sizeof(RECT));

                    MApp_ZUI_API_GetWindowInitialRect(move,&move_new_rect);
                    MApp_ZUI_API_GetWindowInitialRect(target,&target_rect);

                    move_new_rect.top = target_rect.top;

                    ret = MApp_ZUI_API_MoveAllSuccessors(move, move_new_rect.left,move_new_rect.top);

                    break;
                }
            }
        default:
            break;
    }
    return DEFAULTWINPROC(hwnd, msg);
}

void MApp_ZUI_ACT_PVR_BROWSER_FileInfo_Open(void)
{
    if(MApp_ZUI_GetActiveOSD() == E_OSD_PVR_BROWSER)
    {
        if(!MApp_ZUI_API_IsWindowVisible(HWND_PVR_BROWSER_INFO_PANE))
        {
            MApp_ZUI_API_ShowWindow(HWND_PVR_BROWSER_INFO_PANE, SW_SHOW);
            _MApp_ZUI_ACT_PvrBrowser_ShowTriIcon(SW_HIDE);
        }
        else
        {
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_PVR_BROWSER_INFO_PANE);
        }
    }
}

void MApp_ZUI_ACT_PVR_BROWSER_FileInfo_Close(void)
{
    if(MApp_ZUI_GetActiveOSD() == E_OSD_PVR_BROWSER)
    {
        if(MApp_ZUI_API_IsWindowVisible(HWND_PVR_BROWSER_INFO_PANE))
        {
            MApp_ZUI_API_ShowWindow(HWND_PVR_BROWSER_INFO_PANE, SW_HIDE);
            _MApp_ZUI_ACT_PvrBrowser_ShowTriIcon(SW_SHOW);
        }
    }
}

void MApp_ZUI_ACT_PVR_BROWSER_UI_Close(void)
{
   if(MApp_ZUI_GetActiveOSD() == E_OSD_PVR_BROWSER)
   {
        MApp_ZUI_ACT_ExecutePvrBrowserAction(EN_EXE_CLOSE_CURRENT_OSD);
   }
}

void MApp_ZUI_ACT_PVR_Browser_RedrawPage(void)
{
    if(MApp_ZUI_GetActiveOSD() == E_OSD_PVR_BROWSER)
    {
        MApp_ZUI_API_InvalidateAllSuccessors(HWND_MAINFRAME);
    }
}

/*
void MApp_ZUI_ACT_PvrBrowser_PopUp_Msg(EN_PVR_POP_UP_WARNING popUpWarning)
{
    g_PVR_PopUpWarning = popUpWarning;

    if(MApp_ZUI_GetActiveOSD() != E_OSD_PVR_BROWSER)
    {
        MApp_ZUI_ACT_StartupOSD(E_OSD_PVR_BROWSER);
        MApp_ZUI_API_SetTimer(HWND_PVR_WARNING_MESSAGE_PANE, 0, 3000); //aoto close the warning message
    }

    MApp_ZUI_API_ShowWindow(HWND_PVR_WARNING_MESSAGE_PANE, SW_SHOW);
    _MApp_ZUI_API_WindowProcOnIdle(); //force paint to scren...
}
*/
#endif //#if(ENABLE_PVR ==1)
#undef MAPP_ZUI_ACTPVRBROWSER_C
