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

#define MAPP_ZUI_ACTEXPERTMENU_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "datatype.h"
#include "MApp_ZUI_Main.h"

#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_APItables.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcontrols.h"

#include "MApp_ZUI_ACTeffect.h"
#include "OSDcp_String_EnumIndex.h"
#include "ZUI_exefunc.h"
//#include "MApp_ZUI_ACTmainpage.h"

#include "MApp_ZUI_ACTexpertmenu.h"
#include "MApp_ZUI_ACTfactorymenu.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_UiMenuDef.h"
#include "SysInit.h"
#include "MApp_ChannelChange.h"
#include "MApp_InputSource.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_MVDMode.h"
#include "MApp_SaveData.h"
#include "apiXC.h"
#include "apiXC_Sys.h"
#include "apiXC_Adc.h"
#include "MApp_Scaler.h"
#include "apiXC_Ace.h"
#include "drvPQ.h"
#include "MApp_XC_PQ.h"
#if (ENABLE_DLC)
#include "apiXC_Dlc.h"
#endif
#include "MApp_OSDPage_Main.h"
#include "util_checkversion.h"

/////////////////////////////////////////////////////////////////////
typedef struct _EXPERT_BAR_INFO
{
    HWND pre_item;
    HWND cur_item;
} EXPERT_BAR_INFO;

static EXPERT_BAR_INFO _eExpertBarInfo;
/* Linking part of scaler adjust
#include "mvideo_if.h"
#include "apiXC_Cus.h"
#include "Analog_DataType.h"
*/
/////////////////////////////////////////////////////////////////////

typedef struct _MENU_KEY2BTN_STRUCT
{
    VIRTUAL_KEY_CODE key;
    HWND hwnd;
} MENU_KEY2BTN_STRUCT;

/////////////////////////////////////////////////////////////////////

typedef enum _EXPERT_MENU_PAGE
{
    EN_EXPERT_PAGE_ROOT,
    EN_EXPERT_PAGE_SCALER_PAGE,
    EN_EXPERT_PAGE_LIB,
    EN_EXPERT_PAGE_LIB_DRV,
    EN_EXPERT_PAGE_LIB_MW,
} EXPERT_MENU_PAGE;

static EXPERT_MENU_PAGE _eExpertMenuPage;
static void _MApp_ZUI_ACT_ExpertMenuInitPage(EXPERT_MENU_PAGE page);
static U8 _u8LibNumber;
static U8 _u8LibIndex;


/////////////////////////////////////////////////////////////////////
static EN_OSDPAGE_STATE _enTargetOSDPageState;

extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);
#define EXPERT_MENU_CURRENT_TEXT_DISABLE_COLOR   0xFFFF0000

//////////////////////////////////////////////////////////////////////
BOOLEAN g_bLibVersion = TRUE;


static  HWND _ZUI_TBLSEG _ExpertMenuItemHwndList[]=
{
    HWND_EXPERT_MENU_ITEM0,
    HWND_EXPERT_MENU_ITEM1,
    HWND_EXPERT_MENU_ITEM2,
    HWND_EXPERT_MENU_ITEM3,
    HWND_EXPERT_MENU_ITEM4,
    HWND_EXPERT_MENU_ITEM5,
    HWND_EXPERT_MENU_ITEM6,
    HWND_EXPERT_MENU_ITEM7,
    HWND_EXPERT_MENU_ITEM8,
    HWND_EXPERT_MENU_ITEM9,
    HWND_EXPERT_MENU_ITEM10,
    HWND_EXPERT_MENU_ITEM11,

};

static  HWND _ZUI_TBLSEG _ExpertMenuItemHwndNameList[]=
{
    HWND_EXPERT_MENU_ITEM0_NAME,
    HWND_EXPERT_MENU_ITEM1_NAME,
    HWND_EXPERT_MENU_ITEM2_NAME,
    HWND_EXPERT_MENU_ITEM3_NAME,
    HWND_EXPERT_MENU_ITEM4_NAME,
    HWND_EXPERT_MENU_ITEM5_NAME,
    HWND_EXPERT_MENU_ITEM6_NAME,
    HWND_EXPERT_MENU_ITEM7_NAME,
    HWND_EXPERT_MENU_ITEM8_NAME,
    HWND_EXPERT_MENU_ITEM9_NAME,
    HWND_EXPERT_MENU_ITEM10_NAME,
    HWND_EXPERT_MENU_ITEM11_NAME,

};

static  HWND _ZUI_TBLSEG _ExpertMenuItemHwndValueList[]=
{
    HWND_EXPERT_MENU_ITEM0_VALUE,
    HWND_EXPERT_MENU_ITEM1_VALUE,
    HWND_EXPERT_MENU_ITEM2_VALUE,
    HWND_EXPERT_MENU_ITEM3_VALUE,
    HWND_EXPERT_MENU_ITEM4_VALUE,
    HWND_EXPERT_MENU_ITEM5_VALUE,
    HWND_EXPERT_MENU_ITEM6_VALUE,
    HWND_EXPERT_MENU_ITEM7_VALUE,
    HWND_EXPERT_MENU_ITEM8_VALUE,
    HWND_EXPERT_MENU_ITEM9_VALUE,
    HWND_EXPERT_MENU_ITEM10_VALUE,
    HWND_EXPERT_MENU_ITEM11_VALUE,

};
static U8 _MApp_ZUI_ACT_ExpertMenuWindowMapToIndex(HWND hwnd)
{
    U8 i;
    for (i = 0; i < COUNTOF(_ExpertMenuItemHwndList); i++)
    {
        if (hwnd == _ExpertMenuItemHwndList[i] ||
            MApp_ZUI_API_IsSuccessor(_ExpertMenuItemHwndList[i], hwnd))
        {
            return i;
        }
    }
    return 0;
}

static HWND _MApp_ZUI_ACT_ExpertMenuIndexMapToWindow(U8 u8Index)
{
    if (u8Index >= COUNTOF(_ExpertMenuItemHwndList))
        return HWND_INVALID;
    return _ExpertMenuItemHwndList[u8Index];

}


static void _MApp_ZUI_ACT_LibPrevPage(EXPERT_MENU_PAGE expert_page)
{

    EXPERT_MENU_PAGE _ePrevPage = expert_page;
    U8 u8ShowItem = 0;

    u8ShowItem = _u8LibIndex%(COUNTOF(_ExpertMenuItemHwndList));

    _MApp_ZUI_ACT_ExpertMenuInitPage(_ePrevPage);
    MApp_ZUI_API_SetFocus(_ExpertMenuItemHwndList[u8ShowItem]);
    return;
}

static void _MApp_ZUI_ACT_LibNextPage(EXPERT_MENU_PAGE expert_page)
{

    EXPERT_MENU_PAGE _eNextPage = expert_page;
    U8 u8ShowItem = 0;

    u8ShowItem = _u8LibIndex%(COUNTOF(_ExpertMenuItemHwndList));

    _MApp_ZUI_ACT_ExpertMenuInitPage(_eNextPage);
    MApp_ZUI_API_SetFocus(_ExpertMenuItemHwndList[u8ShowItem]);
    return;
}


////////////////////////////////////////////////////////////////////

void MApp_ZUI_ACT_AppShowExpertMenu(void) //HWND sender)
{
    HWND wnd;
    RECT rect;
    E_OSD_ID osd_id = E_OSD_EXPERT_MENU;
    //UNUSED(sender);

    g_GUI_WindowList = GetWindowListOfOsdTable(osd_id);
    g_GUI_WinDrawStyleList = GetWindowStyleOfOsdTable(osd_id);
    g_GUI_WindowPositionList = GetWindowPositionOfOsdTable(osd_id);
#if ZUI_ENABLE_ALPHATABLE
    g_GUI_WinAlphaDataList = GetWindowAlphaDataOfOsdTable(osd_id);
#endif
    HWND_MAX = GetWndMaxOfOsdTable(osd_id);
    OSDPAGE_BLENDING_ENABLE = IsBlendingEnabledOfOsdTable(osd_id);
    OSDPAGE_BLENDING_VALUE = GetBlendingValueOfOsdTable(osd_id);

    //init scaler adjust static value
    XC_SETWIN_INFO stWindowInfo;
    MApp_Scaler_GetWinInfo(&stWindowInfo, MAIN_WINDOW);
    MApp_Scaler_GetOverScan(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), &stWindowInfo);

    if (!_MApp_ZUI_API_AllocateVarData())
    {
        ZUI_DBG_FAIL(printf("[ZUI]ALLOC\n"));
        ABORT();
        return;
    }

    RECT_SET(rect,
        ZUI_EXPERT_MENU_XSTART, ZUI_EXPERT_MENU_YSTART,
        ZUI_EXPERT_MENU_WIDTH, ZUI_EXPERT_MENU_HEIGHT);

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

#ifdef OPEN_VERSION_DBG
#if (OPEN_VERSION_DBG==ENABLE)
    MApp_CountMax();
    MApp_AllVersion_Init();
    MApp_CheckAllVersion();
#endif
#endif
    _u8LibIndex = 0;

    //printf("------- Init _u8IPIndex [%bu] _u8IPNumber [%bu] --------\n", _u8IPIndex, _u8IPNumber);

    MApp_ZUI_API_ShowWindow(HWND_MAINFRAME, SW_SHOW);
    //MApp_ZUI_API_SetFocus(HWND_EXPERT_MENU_ITEM0);
    MApp_ZUI_API_ShowWindow(HWND_EXPERT_MENU_BG_TRANSPARENT, SW_HIDE);
    MApp_ZUI_API_ShowWindow(HWND_EXPERT_MENU_INPUT_INFO, SW_HIDE);

    MApp_ZUI_API_ShowWindow(HWND_EXPERT_MENU_ADJUST_BG, SW_HIDE);
    _MApp_ZUI_ACT_ExpertMenuInitPage(EN_EXPERT_PAGE_ROOT);

    MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_PAGE_SHOWUP, E_ZUI_STATE_RUNNING);

   //must
    MApp_ZUI_API_ShowWindow(HWND_EXPERT_MENU_BSP_ITEM, SW_HIDE);

}


//////////////////////////////////////////////////////////
// Key Handler

BOOLEAN MApp_ZUI_ACT_HandleExpertMenuKey(VIRTUAL_KEY_CODE key)
{
    //note: this function will be called in running state

    //reset timer if any key
    //MApp_ZUI_API_ResetTimer(HWND_AUDLANG_LIST_PANE, 0);

    switch(key)
    {
        case VK_EXIT:
            // TODO: exit here
            MS_DEBUG_MSG(printf("MDrv_PQ_ReStoreToDefault\n"));
            MDrv_PQ_ReStoreToDefault();
            MApp_ZUI_ACT_ExecuteExpertMenuAction(EN_EXE_CLOSE_CURRENT_OSD);
            return TRUE;
        case VK_POWER:
            // TODO: exit here
            MS_DEBUG_MSG(printf("MDrv_PQ_ReStoreToDefault\n"));
            MDrv_PQ_ReStoreToDefault();
            MApp_ZUI_ACT_ExecuteExpertMenuAction(EN_EXE_POWEROFF);
            return TRUE;
        default:
            break;
    }
    if(HWND_EXPERT_MENU_ADJ_NAME == MApp_ZUI_API_GetFocus())
    {
        static  MENU_KEY2BTN_STRUCT _ZUI_TBLSEG _PicAdjkey2btn[] =
        {
            {VK_LEFT, HWND_EXPERT_MENU_ADJ_BOTTOM_HALF_LEFT_BTN},
            {VK_RIGHT, HWND_EXPERT_MENU_ADJ_BOTTOM_HALF_RIGHT_BTN},
        };
        U8 i;

        for (i = 0; i < COUNTOF(_PicAdjkey2btn); i++)
        {
            if (_PicAdjkey2btn[i].key == key)
            {
                MApp_ZUI_API_SetTimer(_PicAdjkey2btn[i].hwnd, 0, BUTTONANICLICK_PERIOD);
                MApp_ZUI_API_InvalidateWindow(_PicAdjkey2btn[i].hwnd);
                break;
            }
        }
    }
    return FALSE;
}

void MApp_ZUI_ACT_TerminateExpertMenu(void)
{
    ZUI_MSG(printf("[]term:facmenu\n");)
    MApp_OSDPage_SetState(_enTargetOSDPageState);
}

////////////////////////////////////////////////////////////


typedef struct _EXPERT_MENU_ITEM
{
    EXPERT_MENU_PAGE eCurPage;
    EXPERT_MENU_PAGE ePrevPage;
    EXPERT_MENU_PAGE eNextPage;
    U8 u8ShowItem;
    U16 u16StringID;
    BOOLEAN bDisable;
} EXPERT_MENU_ITEM;

static  EXPERT_MENU_ITEM _ZUI_TBLSEG _ExpertMenuItem[]=
{
    //==root============================================
    {
        EN_EXPERT_PAGE_ROOT,
        EN_EXPERT_PAGE_ROOT, EN_EXPERT_PAGE_SCALER_PAGE,
        0, en_str_SCALER_ADJUST, FALSE
    },
    {
        EN_EXPERT_PAGE_ROOT,
        EN_EXPERT_PAGE_ROOT, EN_EXPERT_PAGE_ROOT,
        1, en_str_Dynamic_Contrast, FALSE
    },
    {
        EN_EXPERT_PAGE_ROOT,
        EN_EXPERT_PAGE_ROOT, EN_EXPERT_PAGE_ROOT,
        2, en_str_Dynamic_Backlight, FALSE
    },
    {
        EN_EXPERT_PAGE_ROOT,
        EN_EXPERT_PAGE_ROOT, EN_EXPERT_PAGE_ROOT,
        3, en_str_Film_Mode, FALSE
    },
    {
        EN_EXPERT_PAGE_ROOT,
        EN_EXPERT_PAGE_ROOT, EN_EXPERT_PAGE_ROOT,
        4, en_str_DedashBlocking_Function, FALSE
    },
    {
        EN_EXPERT_PAGE_ROOT,
        EN_EXPERT_PAGE_ROOT, EN_EXPERT_PAGE_ROOT,
        5, en_str_DedashMosquito_Function, FALSE
    },
    {
        EN_EXPERT_PAGE_ROOT,
        EN_EXPERT_PAGE_ROOT, EN_EXPERT_PAGE_LIB,
        6, en_str_Library_version, FALSE
    },


    //==SCALER ADJUST======================================
    {
        EN_EXPERT_PAGE_SCALER_PAGE,
        EN_EXPERT_PAGE_ROOT, EN_EXPERT_PAGE_SCALER_PAGE,
        0, en_str_Horizontal_Posdot, FALSE
    },
    {
        EN_EXPERT_PAGE_SCALER_PAGE,
        EN_EXPERT_PAGE_ROOT, EN_EXPERT_PAGE_SCALER_PAGE,
        1, en_str_Vertical_Pos, FALSE
    },
    {
        EN_EXPERT_PAGE_SCALER_PAGE,
        EN_EXPERT_PAGE_ROOT, EN_EXPERT_PAGE_SCALER_PAGE,
        3, en_str_Up_Crop, FALSE
    },
    {
        EN_EXPERT_PAGE_SCALER_PAGE,
        EN_EXPERT_PAGE_ROOT, EN_EXPERT_PAGE_SCALER_PAGE,
        4, en_str_Down_Crop, FALSE
    },
    {
        EN_EXPERT_PAGE_SCALER_PAGE,
        EN_EXPERT_PAGE_ROOT, EN_EXPERT_PAGE_SCALER_PAGE,
        5, en_str_Left_Crop, FALSE
    },
    {
        EN_EXPERT_PAGE_SCALER_PAGE,
        EN_EXPERT_PAGE_ROOT, EN_EXPERT_PAGE_SCALER_PAGE,
        6, en_str_Right_Crop, FALSE
    },


    //==Library version=====================================
    {
        EN_EXPERT_PAGE_LIB,
        EN_EXPERT_PAGE_ROOT, EN_EXPERT_PAGE_LIB_DRV,
        0, en_str_Driver_Library_version, FALSE
    },
    {
        EN_EXPERT_PAGE_LIB,
        EN_EXPERT_PAGE_ROOT, EN_EXPERT_PAGE_LIB_MW,
        1, en_str_MW_Library_version, FALSE
    },
    //==Library Driver=================================
    {
        EN_EXPERT_PAGE_LIB_DRV,
        EN_EXPERT_PAGE_LIB, EN_EXPERT_PAGE_LIB_DRV,
        0, Empty, FALSE
    },
    {
        EN_EXPERT_PAGE_LIB_DRV,
        EN_EXPERT_PAGE_LIB, EN_EXPERT_PAGE_LIB_DRV,
        1, Empty, FALSE
    },
    {
        EN_EXPERT_PAGE_LIB_DRV,
        EN_EXPERT_PAGE_LIB, EN_EXPERT_PAGE_LIB_DRV,
        2, Empty, FALSE
    },
    {
        EN_EXPERT_PAGE_LIB_DRV,
        EN_EXPERT_PAGE_LIB, EN_EXPERT_PAGE_LIB_DRV,
        3, Empty, FALSE
    },
    {
        EN_EXPERT_PAGE_LIB_DRV,
        EN_EXPERT_PAGE_LIB, EN_EXPERT_PAGE_LIB_DRV,
        4, Empty, FALSE
    },
    {
        EN_EXPERT_PAGE_LIB_DRV,
        EN_EXPERT_PAGE_LIB, EN_EXPERT_PAGE_LIB_DRV,
        5, Empty, FALSE
    },
    {
        EN_EXPERT_PAGE_LIB_DRV,
        EN_EXPERT_PAGE_LIB, EN_EXPERT_PAGE_LIB_DRV,
        6, Empty, FALSE
    },
    {
        EN_EXPERT_PAGE_LIB_DRV,
        EN_EXPERT_PAGE_LIB, EN_EXPERT_PAGE_LIB_DRV,
        7, Empty, FALSE
    },
    {
        EN_EXPERT_PAGE_LIB_DRV,
        EN_EXPERT_PAGE_LIB, EN_EXPERT_PAGE_LIB_DRV,
        8, Empty, FALSE
    },
    {
        EN_EXPERT_PAGE_LIB_DRV,
        EN_EXPERT_PAGE_LIB, EN_EXPERT_PAGE_LIB_DRV,
        9, Empty, FALSE
    },
    {
        EN_EXPERT_PAGE_LIB_DRV,
        EN_EXPERT_PAGE_LIB, EN_EXPERT_PAGE_LIB_DRV,
        10, Empty, FALSE
    },
    {
        EN_EXPERT_PAGE_LIB_DRV,
        EN_EXPERT_PAGE_LIB, EN_EXPERT_PAGE_LIB_DRV,
        11, Empty, FALSE
    },

    //==Library Middle ware=================================
    {
        EN_EXPERT_PAGE_LIB_MW,
        EN_EXPERT_PAGE_LIB, EN_EXPERT_PAGE_LIB_MW,
        0, Empty, FALSE
    },
    {
        EN_EXPERT_PAGE_LIB_MW,
        EN_EXPERT_PAGE_LIB, EN_EXPERT_PAGE_LIB_MW,
        1, Empty, FALSE
    },
    {
        EN_EXPERT_PAGE_LIB_MW,
        EN_EXPERT_PAGE_LIB, EN_EXPERT_PAGE_LIB_MW,
        2, Empty, FALSE
    },
    {
        EN_EXPERT_PAGE_LIB_MW,
        EN_EXPERT_PAGE_LIB, EN_EXPERT_PAGE_LIB_MW,
        3, Empty, FALSE
    },
    {
        EN_EXPERT_PAGE_LIB_MW,
        EN_EXPERT_PAGE_LIB, EN_EXPERT_PAGE_LIB_MW,
        4, Empty, FALSE
    },
    {
        EN_EXPERT_PAGE_LIB_MW,
        EN_EXPERT_PAGE_LIB, EN_EXPERT_PAGE_LIB_MW,
        5, Empty, FALSE
    },
    {
        EN_EXPERT_PAGE_LIB_MW,
        EN_EXPERT_PAGE_LIB, EN_EXPERT_PAGE_LIB_MW,
        6, Empty, FALSE
    },
    {
        EN_EXPERT_PAGE_LIB_MW,
        EN_EXPERT_PAGE_LIB, EN_EXPERT_PAGE_LIB_MW,
        7, Empty, FALSE
    },
    {
        EN_EXPERT_PAGE_LIB_MW,
        EN_EXPERT_PAGE_LIB, EN_EXPERT_PAGE_LIB_MW,
        8, Empty, FALSE
    },
    {
        EN_EXPERT_PAGE_LIB_MW,
        EN_EXPERT_PAGE_LIB, EN_EXPERT_PAGE_LIB_MW,
        9, Empty, FALSE
    },
    {
        EN_EXPERT_PAGE_LIB_MW,
        EN_EXPERT_PAGE_LIB, EN_EXPERT_PAGE_LIB_MW,
        10, Empty, FALSE
    },
    {
        EN_EXPERT_PAGE_LIB_MW,
        EN_EXPERT_PAGE_LIB, EN_EXPERT_PAGE_LIB_MW,
        11, Empty, FALSE
    },


};

static void _MApp_ZUI_ACT_ExpertMenuInitPage(EXPERT_MENU_PAGE page)
{
    BOOLEAN bFirst = TRUE;
    U8 i;
    MApp_ZUI_API_InvalidateWindow(HWND_EXPERT_MENU_TITLE);
    MApp_ZUI_API_ShowWindow(HWND_EXPERT_MENU_LIST, SW_HIDE);
    //MApp_ZUI_API_ShowWindow(HWND_EXPERT_MENU_INPUT_INFO, SW_SHOW);
    //must
    MApp_ZUI_API_ShowWindow(HWND_EXPERT_MENU_BSP_ITEM, SW_HIDE);


    if(page == EN_EXPERT_PAGE_LIB_DRV)
    {

    //must : get bsp version

        _u8LibNumber = Drv_Max;
    }
    else if(page == EN_EXPERT_PAGE_LIB_MW)
    {
        _u8LibNumber = MW_Max;
    }

    for (i = 0; i < COUNTOF(_ExpertMenuItem); i++)
    {
        if (_ExpertMenuItem[i].eCurPage == page)
        {
            HWND hwnd = _MApp_ZUI_ACT_ExpertMenuIndexMapToWindow(_ExpertMenuItem[i].u8ShowItem);
            if( !g_bLibVersion && _ExpertMenuItem[i].eNextPage == EN_EXPERT_PAGE_LIB)
            {
                continue;
            }
            MApp_ZUI_API_ShowWindow(hwnd, SW_SHOW);
            if (_ExpertMenuItem[i].bDisable)
            {
                MApp_ZUI_API_EnableWindow(hwnd, FALSE);
            }
            else
            {
                MApp_ZUI_API_EnableWindow(hwnd, TRUE);
                if (bFirst)
                {
                    bFirst = FALSE;
                    MApp_ZUI_API_SetFocus(hwnd);
                }
            }
        }
    }
    if (bFirst)
    {
        MApp_ZUI_API_SetFocus(HWND_INVALID); //no focus...
    }
    _eExpertMenuPage = page;
}

static void _MApp_ZUI_ACT_ExpertMenuNextPage(U8 u8Item)
{
    U8 i;
    for (i = 0; i < COUNTOF(_ExpertMenuItem); i++)
    {
        if (_ExpertMenuItem[i].eCurPage == _eExpertMenuPage &&
            _ExpertMenuItem[i].u8ShowItem == u8Item)
        {
            if (_eExpertMenuPage != _ExpertMenuItem[i].eNextPage)
            {
                _MApp_ZUI_ACT_ExpertMenuInitPage(_ExpertMenuItem[i].eNextPage);
            }
            return;
        }
    }
}

static void _MApp_ZUI_ACT_ExpertMenuPrevPage(U8 u8Item)
{
    U8 i;
    for (i = 0; i < COUNTOF(_ExpertMenuItem); i++)
    {
        if (_ExpertMenuItem[i].eCurPage == _eExpertMenuPage &&
            _ExpertMenuItem[i].u8ShowItem == u8Item)
        {
            if (_eExpertMenuPage != _ExpertMenuItem[i].ePrevPage)
            {
                _MApp_ZUI_ACT_ExpertMenuInitPage(_ExpertMenuItem[i].ePrevPage);
               // _MApp_ZUI_ACT_ExpertMenuPrePageFocusItem(_ExpertMenuItem[i].ePrevPage, _ExpertMenuItem[i].eCurPage);
            }
            return;
        }
    }
}

typedef enum
{
    EN_REDRAW_NONE,
    EN_REDRAW_ITEM,
    EN_REDRAW_LIST,
} REDRAW_TYPE;

static REDRAW_TYPE _MApp_ZUI_ACT_ExpertMenuDecIncValue(U8 u8Item, BOOLEAN bInc)
{
    switch(_eExpertMenuPage)
    {
        case EN_EXPERT_PAGE_ROOT:
            switch(u8Item)
            {
                case 1: //from case Dynamic contrast:
                {
                    stGenSetting.g_SysSetting.fDynamicContrast = !stGenSetting.g_SysSetting.fDynamicContrast;
                #if (ENABLE_DLC)
                    g_bEnableDLC = stGenSetting.g_SysSetting.fDynamicContrast;
                    MApi_XC_DLC_SetOnOff(g_bEnableDLC, MAIN_WINDOW);
                    if( g_bEnableDLC)
                    {
                        MDrv_PQ_LoadDynamicContrastTable(PQ_MAIN_WINDOW,PQ_DynContr_ON);
                    }
                    else
                    {
                        MDrv_PQ_LoadDynamicContrastTable(PQ_MAIN_WINDOW,PQ_DynContr_OFF);
                    }
                #endif
                }
                break;


                case 2: //from case Dynamic blacklight:
                {
                    stGenSetting.g_SysSetting.fDynamicBacklight = !stGenSetting.g_SysSetting.fDynamicBacklight;
                }
                break;


                case 3: //from case film mode:
                {
                    stGenSetting.g_SysSetting.fFilmMode = !stGenSetting.g_SysSetting.fFilmMode;
                    MS_DEBUG_MSG(printf("MDrv_PQ_FilmMode_AnyCandence_Enable(%d)\n", stGenSetting.g_SysSetting.fFilmMode));
                    MDrv_PQ_FilmMode_AnyCandence_Enable(stGenSetting.g_SysSetting.fFilmMode);
                }
                break;


                case 4: //from case de-blocking function:
                {
                    ST_VIDEO.eNRMode.eNR =
                        (EN_MS_NR)MApp_ZUI_ACT_DecIncValue_Cycle(
                            bInc,ST_VIDEO.eNRMode.eNR,MS_NR_OFF, MS_NR_HIGH, 1);
                    switch(ST_VIDEO.eNRMode.eNR )
                    {
                        case MS_NR_OFF:
                            MS_DEBUG_MSG(printf("MS_NR_OFF\n"));
                            MDrv_PQ_DBK_Control(FALSE, Level_Low);
                            break;
                        case MS_NR_LOW:
                            MS_DEBUG_MSG(printf("MS_NR_LOW\n"));
                            MDrv_PQ_DBK_Control(TRUE, Level_Low);
                            break;
                        case MS_NR_MIDDLE:
                            MS_DEBUG_MSG(printf("MS_NR_MIDDLE\n"));
                            MDrv_PQ_DBK_Control(TRUE, Level_MID);
                            break;
                        case MS_NR_HIGH:
                            MS_DEBUG_MSG(printf("MS_NR_HIGH\n"));
                            MDrv_PQ_DBK_Control(TRUE, Level_High);
                            break;
                        default:
                            break;
                    }

                }
                break;


                case 5: //from case de-mosquito function:
                {
                    ST_VIDEO.eNRMode.eNR =
                        (EN_MS_NR)MApp_ZUI_ACT_DecIncValue_Cycle(
                            bInc,ST_VIDEO.eNRMode.eNR,MS_NR_OFF, MS_NR_HIGH, 1);
                    switch(ST_VIDEO.eNRMode.eNR )
                    {
                        case MS_NR_OFF:
                            MS_DEBUG_MSG(printf("MS_NR_OFF\n"));
                            MDrv_PQ_DMS_Control(FALSE, Level_Low);
                            break;
                        case MS_NR_LOW:
                            MS_DEBUG_MSG(printf("MS_NR_LOW\n"));
                            MDrv_PQ_DMS_Control(TRUE, Level_Low);
                            break;
                        case MS_NR_MIDDLE:
                            MS_DEBUG_MSG(printf("MS_NR_MIDDLE\n"));
                            MDrv_PQ_DMS_Control(TRUE, Level_MID);
                            break;
                        case MS_NR_HIGH:
                            MS_DEBUG_MSG(printf("MS_NR_HIGH\n"));
                            MDrv_PQ_DMS_Control(TRUE, Level_High);
                            break;
                        default:
                            break;
                    }
                }
                break;
            }
            break;


        case EN_EXPERT_PAGE_LIB:
        case EN_EXPERT_PAGE_LIB_DRV:
        case EN_EXPERT_PAGE_LIB_MW:
            switch(u8Item)
            {

            }
            break;


        case EN_EXPERT_PAGE_SCALER_PAGE:
        {
            switch(u8Item)
            {
                case 0: //H position
                {
                    MS_VIDEO_Window_Info_EXT stWinInfo;
                    MApp_Scaler_GetVidWinInfo(&stWinInfo, MAIN_WINDOW);
                    stWinInfo.stCapWin.x = MApp_ZUI_ACT_DecIncValue_Cycle(
                        bInc,stWinInfo.stCapWin.x,0, PANEL_WIDTH-1, 1);
                    MApp_Scaler_SetVidWinInfo(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),&stWinInfo, MAIN_WINDOW);
                    MApp_Scaler_SetWindow(&(stWinInfo.stCapWin), NULL,NULL,
                            stSystemInfo[MAIN_WINDOW].enAspectRatio,
                            SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);

                    return EN_REDRAW_ITEM;
                }
                break;

                case 1: //V position
                {
                    MS_VIDEO_Window_Info_EXT stWinInfo;
                    MApp_Scaler_GetVidWinInfo(&stWinInfo, MAIN_WINDOW);
                    stWinInfo.stCapWin.y = MApp_ZUI_ACT_DecIncValue_Cycle(
                        bInc,stWinInfo.stCapWin.y,0, PANEL_HEIGHT-1, 1);
                    MApp_Scaler_SetVidWinInfo(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),&stWinInfo, MAIN_WINDOW);
                    MApp_Scaler_SetWindow(&(stWinInfo.stCapWin), NULL,NULL,
                        stSystemInfo[MAIN_WINDOW].enAspectRatio,SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),MAIN_WINDOW);

                    return EN_REDRAW_ITEM;
                }
                break;


                case 3: //Up crop
                {
                    if ( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
                       ||(IsSrcTypeStorage(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) && !IsSrcTypeJpeg(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))) // storage type except JPEG
                    {
                        MS_VIDEO_Window_Info_EXT stWinInfo;
                        MApp_Scaler_GetVidWinInfo(&stWinInfo, MAIN_WINDOW);
                        stWinInfo.u8V_OverScanRatio = MApp_ZUI_ACT_DecIncValue_Cycle(
                            bInc,(U16)stWinInfo.u8V_OverScanRatio,0, OVERSCAN_RATIO, 1);
                        MApp_Scaler_SetVidWinInfo(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),&stWinInfo, MAIN_WINDOW);
                        MApp_Scaler_SetWindow(&(stWinInfo.stCapWin), NULL,NULL,
                            stSystemInfo[MAIN_WINDOW].enAspectRatio,SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),MAIN_WINDOW);
                    }
                    else
                    {
                        MS_VIDEO_Window_Info_EXT stWinInfo;
                        MApp_Scaler_GetVidWinInfo(&stWinInfo, MAIN_WINDOW);
                        stWinInfo.u8VCrop_Up = MApp_ZUI_ACT_DecIncValue_Cycle(
                            bInc,(U16)stWinInfo.u8VCrop_Up,0, OVERSCAN_RATIO, 1);
                        MApp_Scaler_SetVidWinInfo(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),&stWinInfo, MAIN_WINDOW);
                        MApp_Scaler_SetWindow(&(stWinInfo.stCapWin), NULL,NULL,
                            stSystemInfo[MAIN_WINDOW].enAspectRatio,SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),MAIN_WINDOW);
                    }
                    return EN_REDRAW_ITEM;
                 }
                 break;


                case 4: //Down crop
                {
                    MS_VIDEO_Window_Info_EXT stWinInfo;
                    MApp_Scaler_GetVidWinInfo(&stWinInfo, MAIN_WINDOW);
                    stWinInfo.u8VCrop_Down = MApp_ZUI_ACT_DecIncValue_Cycle(
                        bInc,(U16)stWinInfo.u8VCrop_Down,0, OVERSCAN_RATIO, 1);
                    MApp_Scaler_SetVidWinInfo(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),&stWinInfo, MAIN_WINDOW);
                    MApp_Scaler_SetWindow(&(stWinInfo.stCapWin), NULL,NULL,
                        stSystemInfo[MAIN_WINDOW].enAspectRatio,SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),MAIN_WINDOW);
                    return EN_REDRAW_ITEM;
                }
                break;


                case 5: //Left crop
                {
                    if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) ||
                        (IsSrcTypeStorage(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) && !IsSrcTypeJpeg(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))) // storage type except JPEG
                    {
                        MS_VIDEO_Window_Info_EXT stWinInfo;
                        MApp_Scaler_GetVidWinInfo(&stWinInfo, MAIN_WINDOW);
                        stWinInfo.u8H_OverScanRatio = MApp_ZUI_ACT_DecIncValue_Cycle(
                            bInc,(U16)stWinInfo.u8H_OverScanRatio,0, OVERSCAN_RATIO, 1);
                        MApp_Scaler_SetVidWinInfo(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),&stWinInfo, MAIN_WINDOW);
                        MApp_Scaler_SetWindow(&(stWinInfo.stCapWin), NULL,NULL,
                            stSystemInfo[MAIN_WINDOW].enAspectRatio,SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),MAIN_WINDOW);
                    }
                    else
                    {
                        MS_VIDEO_Window_Info_EXT stWinInfo;
                        MApp_Scaler_GetVidWinInfo(&stWinInfo, MAIN_WINDOW);
                        stWinInfo.u8HCrop_Left = MApp_ZUI_ACT_DecIncValue_Cycle(
                            bInc,(U16)stWinInfo.u8HCrop_Left,0, OVERSCAN_RATIO, 1);
                        MApp_Scaler_SetVidWinInfo(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),&stWinInfo, MAIN_WINDOW);
                        MApp_Scaler_SetWindow(&(stWinInfo.stCapWin), NULL,NULL,
                            stSystemInfo[MAIN_WINDOW].enAspectRatio,SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),MAIN_WINDOW);
                        return EN_REDRAW_ITEM;
                    }
                 }
                 break;

                 case 6: //Right crop
                {
                    MS_VIDEO_Window_Info_EXT stWinInfo;
                    MApp_Scaler_GetVidWinInfo(&stWinInfo, MAIN_WINDOW);
                    stWinInfo.u8HCrop_Right = MApp_ZUI_ACT_DecIncValue_Cycle(
                        bInc,(U16)stWinInfo.u8HCrop_Right,0, OVERSCAN_RATIO, 1);
                    MApp_Scaler_SetVidWinInfo(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),&stWinInfo, MAIN_WINDOW);
                    MApp_Scaler_SetWindow(&(stWinInfo.stCapWin), NULL,NULL,
                        stSystemInfo[MAIN_WINDOW].enAspectRatio,SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),MAIN_WINDOW);
                    return EN_REDRAW_ITEM;
                }
                break;

            }
        }
        break;


        default:
            break;
    }

    return EN_REDRAW_NONE;
}


static LPTSTR _MApp_ZUI_ACT_GetExpertMenuValueText(U8 u8Item)
{
    U16 u16TempID = Empty;

    switch (_eExpertMenuPage)
    {
        case EN_EXPERT_PAGE_ROOT:
            switch(u8Item)
            {
                case 1: //from case Dynamic contrast:
                {
                    if(!stGenSetting.g_SysSetting.fDynamicContrast)
                        u16TempID=en_str_Off;
                    else
                        u16TempID=en_str_On;

                    break;
                }


                case 2: //from case Dynamic blacklight:
                {
                    if(!stGenSetting.g_SysSetting.fDynamicBacklight)
                        u16TempID=en_str_Off;
                    else
                    u16TempID=en_str_On;

                    break;
                }


                case 3: //from case film mode:
                {
                    if(!stGenSetting.g_SysSetting.fFilmMode)
                        u16TempID=en_str_Off;
                    else
                        u16TempID=en_str_On;

                    break;
                }


                case 4: //from case de-blocking function:
                {
                    switch(ST_VIDEO.eNRMode.eNR)
                    {
                        default:
                        case MS_NR_OFF:
                            u16TempID=en_str_Off;
                        break;
                        case MS_NR_LOW:
                            u16TempID=en_str_Low;
                        break;
                        case MS_NR_HIGH:
                            u16TempID=en_str_High;
                        break;
                        case MS_NR_MIDDLE:
                            u16TempID=en_str_Middle;
                        break;
                    }

                    break;
                }


                case 5: //from case de-mosquito function:
                {
                    switch(ST_VIDEO.eNRMode.eNR)
                    {
                        default:
                        case MS_NR_OFF:
                            u16TempID=en_str_Off;
                        break;
                        case MS_NR_LOW:
                            u16TempID=en_str_Low;
                        break;
                        case MS_NR_HIGH:
                            u16TempID=en_str_High;
                        break;
                        case MS_NR_MIDDLE:
                            u16TempID=en_str_Middle;
                        break;
                    }

                    break;
                }
            }
            break;


        case EN_EXPERT_PAGE_SCALER_PAGE:
        {
            switch(u8Item)
            {
                case 0: //H position
                {
                    MS_VIDEO_Window_Info_EXT stWinInfo;
                    MApp_Scaler_GetVidWinInfo(&stWinInfo, MAIN_WINDOW);
                    return MApp_ZUI_API_GetU16String(stWinInfo.stCapWin.x);
                }
                break;

                case 1: //V position
                {
                    MS_VIDEO_Window_Info_EXT stWinInfo;
                    MApp_Scaler_GetVidWinInfo(&stWinInfo, MAIN_WINDOW);
                    return MApp_ZUI_API_GetU16String(stWinInfo.stCapWin.y);
                }
                break;

                case 3: //Up crop
                {
                    MS_VIDEO_Window_Info_EXT stWinInfo;
                    MApp_Scaler_GetVidWinInfo(&stWinInfo, MAIN_WINDOW);

                    if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) ||
                        (IsSrcTypeStorage(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) && !IsSrcTypeJpeg(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))) // storage type except JPEG
                    {
                        return MApp_ZUI_API_GetU16String((U16)stWinInfo.u8V_OverScanRatio);
                    }
                    else
                    {
                        return MApp_ZUI_API_GetU16String((U16)stWinInfo.u8VCrop_Up);
                    }
                }
                break;

                case 4: //Down crop
                {
                    if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) ||
                        (IsSrcTypeStorage(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) && !IsSrcTypeJpeg(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))) // storage type except JPEG
                    {

                    }
                    else
                    {
                        MS_VIDEO_Window_Info_EXT stWinInfo;
                        MApp_Scaler_GetVidWinInfo(&stWinInfo, MAIN_WINDOW);
                        return MApp_ZUI_API_GetU16String((U16)stWinInfo.u8VCrop_Down);
                    }
                }
                break;

                case 5: //Left crop
                {

                    MS_VIDEO_Window_Info_EXT stWinInfo;
                    MApp_Scaler_GetVidWinInfo(&stWinInfo, MAIN_WINDOW);

                    if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) ||
                        (IsSrcTypeStorage(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) && !IsSrcTypeJpeg(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))) // storage type except JPEG
                    {
                        return MApp_ZUI_API_GetU16String((U16)stWinInfo.u8H_OverScanRatio);
                    }
                    else
                    {

                        return MApp_ZUI_API_GetU16String((U16)stWinInfo.u8HCrop_Left);
                    }
                }
                break;

                case 6: //Right crop
                {   // wait to link
                    if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) ||
                        (IsSrcTypeStorage(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) && !IsSrcTypeJpeg(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))) // storage type except JPEG
                    {
                    }
                    else
                    {
                        MS_VIDEO_Window_Info_EXT stWinInfo;
                        MApp_Scaler_GetVidWinInfo(&stWinInfo, MAIN_WINDOW);
                        return MApp_ZUI_API_GetU16String((U16)stWinInfo.u8HCrop_Right);
                    }
                }
                break;
            }
            break;
        }


        case EN_EXPERT_PAGE_LIB_DRV:
        {
            U8 u8LibIdx, u8LibNum;
            //U16 u16str[STRING_BUFFER_LENGTH];

            u8LibIdx = ((_u8LibIndex)/(COUNTOF(_ExpertMenuItemHwndList)))*(COUNTOF(_ExpertMenuItemHwndList))+u8Item;
            u8LibNum = _u8LibNumber;

            if(u8LibIdx < u8LibNum)
            {
            #if 1
                MApp_ZUI_API_Strcpy(CHAR_BUFFER, drv_LibVersion[u8LibIdx]);
                MApp_ZUI_API_Strcat(CHAR_BUFFER, drv_BuildNumber[u8LibIdx]);
                MApp_ZUI_API_Strcat(CHAR_BUFFER, drv_ChangeList[u8LibIdx]);
            #else
                MApp_ZUI_API_Strcpy(u16str,drv_LibVersion[u8LibIdx]);
                MApp_ZUI_API_Strcat(u16str,drv_BuildNumber[u8LibIdx]);
                MApp_ZUI_API_Strcat(u16str,drv_ChangeList[u8LibIdx]);
                MApp_ZUI_API_Strcpy(CHAR_BUFFER,u16str);
            #endif
                return CHAR_BUFFER;
            }

            break;
        }


        case EN_EXPERT_PAGE_LIB_MW:
        {
            U8 u8LibIdx, u8LibNum;
            //U16 u16str[STRING_BUFFER_LENGTH];

            u8LibIdx = ((_u8LibIndex)/(COUNTOF(_ExpertMenuItemHwndList)))*(COUNTOF(_ExpertMenuItemHwndList))+u8Item;
            u8LibNum = _u8LibNumber;

            if(u8LibIdx < u8LibNum)
            {
            #if(1)
                MApp_ZUI_API_Strcpy(CHAR_BUFFER, MW_LibVersion[u8LibIdx]);
                MApp_ZUI_API_Strcat(CHAR_BUFFER, MW_BuildNumber[u8LibIdx]);
                MApp_ZUI_API_Strcat(CHAR_BUFFER, MW_ChangeList[u8LibIdx]);
            #else
                MApp_ZUI_API_Strcpy(u16str,MW_LibVersion[u8LibIdx]);
                MApp_ZUI_API_Strcat(u16str,MW_BuildNumber[u8LibIdx]);
                MApp_ZUI_API_Strcat(u16str,MW_ChangeList[u8LibIdx]);
                MApp_ZUI_API_Strcpy(CHAR_BUFFER,u16str);
            #endif
                return CHAR_BUFFER;
            }

            break;
        }


        case EN_EXPERT_PAGE_LIB:
        {
            break;
        }

    } // switch (_eExpertMenuPage)

    if (u16TempID != Empty)
    {
        return MApp_ZUI_API_GetString(u16TempID);
    }

    return NULL; //for empty string
}

////////////////////////////////////////////////////////

BOOLEAN MApp_ZUI_ACT_ExecuteExpertMenuAction(U16 act)
{
    LPTSTR tmp = NULL;

    switch(act)
    {
        case EN_EXE_EXPERT_MENU_GOTO_BAR_ADJUST:
            //add element to skip into bar;
            tmp = _MApp_ZUI_ACT_GetExpertMenuValueText(_MApp_ZUI_ACT_ExpertMenuWindowMapToIndex(MApp_ZUI_API_GetFocus()));
            if(tmp == NULL)
                return TRUE;

            if(_eExpertMenuPage ==EN_EXPERT_PAGE_LIB_DRV || _eExpertMenuPage == EN_EXPERT_PAGE_LIB_MW )
            {
                return TRUE;
            }

            _eExpertBarInfo.pre_item = MApp_ZUI_API_GetFocus();
            _eExpertBarInfo.cur_item = HWND_EXPERT_MENU_ADJ_TEXT;

            MApp_ZUI_API_ShowWindow(HWND_EXPERT_MENU_BG_TRANSPARENT, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EXPERT_MENU_BG_PANE, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EXPERT_MENU_INPUT_INFO, SW_HIDE);
            MApp_ZUI_API_ShowWindow(HWND_EXPERT_MENU_LIST, SW_HIDE);

            MApp_ZUI_API_ShowWindow(HWND_EXPERT_MENU_ADJUST_BG, SW_SHOW);
            MApp_ZUI_API_SetFocus(HWND_EXPERT_MENU_ADJ_NAME);
            //must
            MApp_ZUI_API_ShowWindow(HWND_EXPERT_MENU_BSP_ITEM, SW_HIDE);
            return TRUE;


        case EN_EXE_EXPERT_MENU_EXIT_BAR_ADJUST:
            MApp_ZUI_API_ShowWindow(HWND_EXPERT_MENU_BG_PANE, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_EXPERT_MENU_LIST, SW_SHOW);
            MApp_ZUI_API_ShowWindow(HWND_EXPERT_MENU_ADJUST_BG, SW_HIDE);
            _MApp_ZUI_ACT_ExpertMenuInitPage(_eExpertMenuPage);
            MApp_ZUI_API_SetFocus(_eExpertBarInfo.pre_item);
            //must
            MApp_ZUI_API_ShowWindow(HWND_EXPERT_MENU_BSP_ITEM, SW_HIDE);
            return TRUE;


        case EN_EXE_CLOSE_CURRENT_OSD:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_PAGE_FADE_OUT, E_ZUI_STATE_TERMINATE);
            _enTargetOSDPageState = STATE_OSDPAGE_CLEAN_UP;
            return TRUE;


        case EN_EXE_POWEROFF:
            MApp_ZUI_ACT_TransitionEffectBegin(EN_EFFMODE_PAGE_FADE_OUT, E_ZUI_STATE_TERMINATE);
            _enTargetOSDPageState = STATE_OSDPAGE_GOTO_STANDBY;
            return TRUE;


        case EN_EXE_EXPERT_MENU_PREV_PAGE:
            if(_eExpertMenuPage ==  EN_EXPERT_PAGE_LIB_DRV || EN_EXPERT_PAGE_LIB_MW)
            {
                _u8LibIndex = 0;
                _u8LibNumber = 0;
            }
            _MApp_ZUI_ACT_ExpertMenuPrevPage(
                _MApp_ZUI_ACT_ExpertMenuWindowMapToIndex(MApp_ZUI_API_GetFocus()));
            return TRUE;


        case EN_EXE_EXPERT_MENU_NEXT_PAGE:
            // need to check
            _MApp_ZUI_ACT_ExpertMenuNextPage(
                _MApp_ZUI_ACT_ExpertMenuWindowMapToIndex(MApp_ZUI_API_GetFocus()));
            return TRUE;


        case EN_EXE_EXPERT_MENU_ADJ_DEC:
        case EN_EXE_EXPERT_MENU_ADJ_INC:
        {
            REDRAW_TYPE eRedraw = _MApp_ZUI_ACT_ExpertMenuDecIncValue(
                _MApp_ZUI_ACT_ExpertMenuWindowMapToIndex(
                    _eExpertBarInfo.pre_item),
                    act==EN_EXE_EXPERT_MENU_ADJ_INC);

            eRedraw = EN_REDRAW_ITEM;
            MApp_ZUI_API_InvalidateAllSuccessors(HWND_EXPERT_MENU_ADJ_NAME);

            return TRUE;
        }


        case EN_EXE_EXPERT_PREV_PAGE:
            if(_eExpertMenuPage == EN_EXPERT_PAGE_LIB_DRV || _eExpertMenuPage == EN_EXPERT_PAGE_LIB_MW )
            {
                BOOLEAN _bChangePage;
                _bChangePage = FALSE;

                if(_u8LibIndex == 0)
                {
                    _u8LibIndex = _u8LibNumber-1;
                    _bChangePage = TRUE;
                }
                else
                {
                    if((_u8LibIndex != 0) && (((_u8LibIndex)%(COUNTOF(_ExpertMenuItemHwndList))) == 0))
                    {
                        _bChangePage = TRUE;
                    }
                    _u8LibIndex--;
                }
                if(_bChangePage)
                {
                    _MApp_ZUI_ACT_LibPrevPage(_eExpertMenuPage);
                    return TRUE;
                }
            }
            return FALSE;


        case EN_EXE_EXPERT_NEXT_PAGE:
            if( _eExpertMenuPage == EN_EXPERT_PAGE_LIB_DRV || _eExpertMenuPage == EN_EXPERT_PAGE_LIB_MW )
            {
                BOOLEAN _bChangePage;
                _bChangePage = FALSE;

                if(_u8LibIndex == (_u8LibNumber-1))
                {
                    _u8LibIndex = 0;
                    _bChangePage = TRUE;
                }
                else
                {
                    if((_u8LibIndex != 0) && (((_u8LibIndex+1)%(COUNTOF(_ExpertMenuItemHwndList))) == 0))
                    {
                        _bChangePage = TRUE;
                    }
                    _u8LibIndex++;
                }

                if(_bChangePage)
                {
                    _MApp_ZUI_ACT_LibNextPage(_eExpertMenuPage);
                    return TRUE;
                }
            }
            return FALSE;
    }

    return FALSE;
}


LPTSTR MApp_ZUI_ACT_GetExpertMenuDynamicText(HWND hwnd)
{
    U16 u16TempID = Empty;

    U8 u8Item;
    U8 i;

    //step1: special cases: title
    if (hwnd == HWND_EXPERT_MENU_TITLE)
    {
        switch(_eExpertMenuPage)
        {
            case EN_EXPERT_PAGE_ROOT:
                u16TempID = en_str_Expert_setting;
                break;

            case EN_EXPERT_PAGE_SCALER_PAGE:
                u16TempID = en_str_SCALER_ADJUST;
                break;
            case EN_EXPERT_PAGE_LIB:
                u16TempID = en_str_Library_version;
                break;
            case EN_EXPERT_PAGE_LIB_DRV:
                u16TempID = en_str_Driver_Library_version;
                break;
            case EN_EXPERT_PAGE_LIB_MW:
                u16TempID = en_str_MW_Library_version;
                break;

        }
        goto END;

    }

#if(CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD)
   if(hwnd == HWND_EXPERT_MENU_BSP_VERSION)
   {
        //get bsp version
        //temp
        U16 u16str[32];
        MApp_ZUI_API_Strcpy(u16str,drv_Name[0]);
        u16str[4] = '\0';
        MApp_ZUI_API_Strcpy(CHAR_BUFFER,u16str);
        return CHAR_BUFFER;
   }
#endif


    u8Item = _MApp_ZUI_ACT_ExpertMenuWindowMapToIndex(hwnd);

    //special case: board type in item name...
    if (_eExpertMenuPage == EN_EXPERT_PAGE_ROOT && u8Item == 8)
    {
        if (hwnd == HWND_EXPERT_MENU_ITEM8_NAME)
            return _MApp_ZUI_ACT_GetExpertMenuValueText(u8Item);
        return NULL;
    }

    //step2: value windows
    if(hwnd == HWND_EXPERT_MENU_ADJ_VALUE)
    {
        u8Item = _MApp_ZUI_ACT_ExpertMenuWindowMapToIndex(_eExpertBarInfo.pre_item);
        return _MApp_ZUI_ACT_GetExpertMenuValueText(u8Item);
    }
    if (_ExpertMenuItemHwndValueList[u8Item] == hwnd) //is value window...
    {
        return _MApp_ZUI_ACT_GetExpertMenuValueText(u8Item);
    }
    if (hwnd == HWND_EXPERT_MENU_INPUT_TYPE)
    {
        //printf("MApp_ZUI_ACTexpertmenu.c Line %d : %s\n", __LINE__, MDrv_PQ_GetSrcTypeName(MAIN_WINDOW));
        return MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, (U8*)MDrv_PQ_GetSrcTypeName(PQ_MAIN_WINDOW), 255);
    }
    //step3: item name
    if(hwnd == HWND_EXPERT_MENU_ADJ_TEXT)
    {
        u8Item = _MApp_ZUI_ACT_ExpertMenuWindowMapToIndex(_eExpertBarInfo.pre_item);
        return MApp_ZUI_ACT_GetExpertMenuDynamicText(_ExpertMenuItemHwndNameList[u8Item]);
    }
    else if( _eExpertMenuPage == EN_EXPERT_PAGE_LIB_DRV || _eExpertMenuPage == EN_EXPERT_PAGE_LIB_MW)
    {
        U8 u8LibIdx, u8LibNum;
        U16 u16str[32];
        u8LibIdx = ((_u8LibIndex/(COUNTOF(_ExpertMenuItemHwndList)))*(COUNTOF(_ExpertMenuItemHwndList)))+u8Item;
        u8LibNum = _u8LibNumber;

        if(u8LibIdx < u8LibNum)
        {
            if(_eExpertMenuPage == EN_EXPERT_PAGE_LIB_DRV)
            {
            #if(CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD)
                MApp_ZUI_API_ShowWindow(HWND_EXPERT_MENU_BSP_ITEM, SW_SHOW);
            #endif

                MApp_ZUI_API_Strcpy(u16str,drv_Name[u8LibIdx]);
                u16str[4] = '\0';
                MApp_ZUI_API_Strcpy(CHAR_BUFFER,u16str);
                return CHAR_BUFFER;
            }
            else if( _eExpertMenuPage == EN_EXPERT_PAGE_LIB_MW)
            {
                MApp_ZUI_API_Strcpy(u16str,MW_Name[u8LibIdx]);
                u16str[4] = '\0';
                MApp_ZUI_API_Strcpy(CHAR_BUFFER,u16str);
                return CHAR_BUFFER;
            }
        }
    }
    else
    {
        for (i = 0; i < COUNTOF(_ExpertMenuItem); i++)
        {
            if (_ExpertMenuItem[i].eCurPage == _eExpertMenuPage &&
                _ExpertMenuItem[i].u8ShowItem == u8Item)
            {
                u16TempID = _ExpertMenuItem[i].u16StringID;
                break;
            }
        }
    }

END:
    if (u16TempID != Empty)
        return MApp_ZUI_API_GetString(u16TempID);
    return NULL; //for empty string
}

OSD_COLOR MApp_ZUI_ACT_GetExpertmenuDynamicColor(HWND hwnd, DRAWSTYLE_TYPE type, OSD_COLOR colorOriginal)
{
    UNUSED(type);

    U16 u16PageCurIndex;
    U8 u8LibIdx;

    if(_eExpertMenuPage == EN_EXPERT_PAGE_LIB_DRV)
    {
        u16PageCurIndex = (U16)_MApp_ZUI_ACT_ExpertMenuWindowMapToIndex(hwnd);
        u8LibIdx = ((_u8LibIndex/(COUNTOF(_ExpertMenuItemHwndList)))*(COUNTOF(_ExpertMenuItemHwndList)))+u16PageCurIndex;

        if(drv_Match[u8LibIdx])
        {
            return colorOriginal;
        }
        else
        {
            return EXPERT_MENU_CURRENT_TEXT_DISABLE_COLOR;
        }
    }
    else if(_eExpertMenuPage == EN_EXPERT_PAGE_LIB_MW)
    {
        u16PageCurIndex = (U16)_MApp_ZUI_ACT_ExpertMenuWindowMapToIndex(hwnd);
        u8LibIdx = ((_u8LibIndex/(COUNTOF(_ExpertMenuItemHwndList)))*(COUNTOF(_ExpertMenuItemHwndList)))+u16PageCurIndex;

        if(MW_Match[u8LibIdx])
        {
            return colorOriginal;
        }
        else
        {
            return EXPERT_MENU_CURRENT_TEXT_DISABLE_COLOR;
        }
    }
    return colorOriginal;
}



/////////////////////////////////////////////////////////
// Customize Window Procedures




//
//******************************************************************************
//
#undef MAPP_ZUI_ACTEXPERTMENU_C

