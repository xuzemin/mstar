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

#ifndef _MAPP_ZUI_APITABLE_H
#define _MAPP_ZUI_APITABLE_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIwindow.h"

#ifdef MAPP_ZUI_APITABLES_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

/**
 * \var DRAWCOMPONENT
 * \brief system independent drawing component - group UI drawing function to simple drawing component, ex: rectangle, fill rectangle, bitmap, string, ...
 *
*/
typedef enum _DRAWCOMPONENT
{
    CP_NOON = 0,
    CP_RECT_BORDER,
    CP_FILL_RECT,
    //CP_RECT_BORDER_EX,
    //CP_RECT_3D,
    CP_TEXT_OUT,
    CP_BITMAP,
    //CP_ROUND_BAR,
    //CP_WINDOW,
    CP_RECT,
    //CP_DASH_BAR,
    //CP_TRIANGLE,
    //CP_CIRCLE,
    //CP_ROUND_BORDER,
    CP_TEXT_OUT_DYNAMIC,
    CP_PUNCTUATED_DYNAMIC,
    CP_EPG_PUNCTUATED_DYNAMIC,
    CP_SCROL_PUNCTUATED_DYNAMIC,
    CP_BT_TEXT_DYNAMIC,
   #if TXTFONT_ZOOM2X
    CP_ZOOM2X_PUNCTUATED_DYNAMIC,
  #endif


} DRAWCOMPONENT;

/////////////////////////////////////////////////////////////

/**
 * \var DRAWSTYLE
 * \brief drawing style structure - list a sequence of DRAWSTYLE, in order to draw UI component one by one. (generated by tool)
 *
*/
typedef struct _DRAWSTYLE
{
    U16 component : 5; //DRAWCOMPONENT component;
    U16 u16Index : 11; //U16     u16Index;
} DRAWSTYLE;

/////////////////////////////////////////////////////////////

#if ZUI_ENABLE_REDUCED_ALPHATABLE
/**
 * \var WINDOWALPHADATA
 * \brief window alpha structure - for reduced table, only store non-opacity window handle  (0xFF is opacity)
 * (generated by tool)
*/
typedef struct _WINDOWALPHADATA
{
    HWND hwnd;
    U8 u8NormalAlpha;
    U8 u8FocusAlpha;
    U8 u8DisableAlpha;

} WINDOWALPHADATA;
#else
/**
 * \var WINDOWALPHADATA
 * \brief window alpha structure - for non-reduced table, store all the alpha values (0xFF is opacity)
 * (generated by tool)
*/
typedef struct _WINDOWALPHADATA
{
    U8 u8NormalAlpha;
    U8 u8FocusAlpha;
    U8 u8DisableAlpha;

} WINDOWALPHADATA;
#endif //ZUI_ENABLE_REDUCED_ALPHATABLE

/**
 * \var WINDOWDRAWSTYLEDATA
 * \brief window style structure - specify normal/focus/disabled styles (generated by tool)
 *
*/
typedef struct _WINDOWDRAWSTYLEDATA
{
    DRAWSTYLE * pNormalStyle;
    DRAWSTYLE * pFocusStyle;
    DRAWSTYLE * pDisableStyle;

} WINDOWDRAWSTYLEDATA;
typedef WINDOWDRAWSTYLEDATA* OSDPAGEWNDDRAWSTYLETABLE;

/**
 * \var KEYEVENT
 * \brief window key binding table - specify action for a specific key
 *
*/
typedef struct _KEYEVENT
{
    U16 u16VirKey : 6; //VIRTUAL_KEY_CODE  u16VirKey;
    U16  u16ExeActID : 12;

} KEYEVENT;

/**
 * \var WINDOWDATA
 * \brief window general table - store window type, priviate data, and initial value
 * (generated by tool)
*/
// this struct is an internal struct
typedef struct _WINDOWDATA
{
    /* moved to WINDOWPOSDATA
    HWND    parent;
    HWND    hwndLastSuccessor;   //2007/12/4: for speed up IsSuccessor() checking
    RECT    rect;
    */
    U8      u8WinProcID; //note: use more than 32 winproc in this project: WNDPROC WindowProc;
    void *  pWindowData;
    U8      u8InitState;

    HWND *  aFocusNavigation; //up, down, left, right;

    KEYEVENT *Keyevent;            /// keymap

}WINDOWDATA;

/**
 * \var WINDOWPOSDATA
 * \brief window position table - store window parent/child relation and position
 * (generated by tool)
*/
typedef struct _WINDOWPOSDATA
{
    HWND    parent;
    HWND    hwndLastSuccessor;   //2007/12/4: for speed up IsSuccessor() checking
    RECT    rect;

}WINDOWPOSDATA;
typedef WINDOWPOSDATA* OSDPAGEWNDPOSTABLE;

/**
 * \var KEYWNDNAV
 * \brief window navigation order
 *
*/
typedef enum
{
    NAV_UP,
    NAV_DOWN,
    NAV_LEFT,
    NAV_RIGHT,

} KEYWNDNAV;

/**
 * \var DRAWSTYLE_TYPE
 * \brief window style (for dynamic lists)
 *
*/
typedef enum
{
    DS_NORMAL,
    DS_FOCUS,
    DS_DISABLE,

} DRAWSTYLE_TYPE;

/**
 * \var OSDPAGETABLE
 * \brief global osd page table
 *
*/
typedef struct _OSDPageTable
{
    HWND                WndMaxNum;
    WINDOWDATA          *WindowList;
    //WINDOWDRAWSTYLEDATA *WindowDrawStyleList;
    WINDOWALPHADATA     *WindowAlphaDataList;
    KEYEVENT            *Keyevent;                    /// keymap

    U16                 u16Gwin;
    U32                 u32GwinXPos;
    U32                 u32GwinYPos;
    U32                 u32GwinWidth;
    U32                 u32GwinHeight;

    U8                  bEnableAlpha;
    U8                  u8AlphaValue;

    U8                  bEnableClrKey;
    U8                  u8ClrKeyRedStart;
    U8                  u8ClrKeyGreenStart;
    U8                  u8ClrKeyBlueStart;
    U8                  u8ClrKeyRedEnd;
    U8                  u8ClrKeyGreenEnd;
    U8                  u8ClrKeyBlueEnd;

    HWND                hwndDefaultFocus;

} OSDPAGETABLE;

/**
 * \var OSDPAGETABLE
 * \brief global osd page table
 *
*/
typedef struct _OSDPageTransEffTable
{
    U32 EffectID_Open;
    U32 EffectID_Close;

} OSDPAGE_TRANSEFF_TABLE;


#ifdef _ZUI_INTERNAL_INSIDE_

#define GETWNDINFO(hwnd) (&g_GUI_WindowList[hwnd])
#define GETWNDINITRECT(hwnd) (g_GUI_WindowPositionList[hwnd].rect)
//#define SETWNDRECT(hwnd, rect) (g_GUI_WinVarDataList[hwnd].rect = rect)
#define GETWNDINITSTATE(hwnd) (g_GUI_WindowList[hwnd].u8InitState)
#define GETWNDDATA(hwnd) (g_GUI_WindowList[hwnd].pWindowData)
#define GETNORMALDRAWSTYLE(hwnd) (g_GUI_WinDrawStyleList[hwnd].pNormalStyle)
#define GETFOCUSDRAWSTYLE(hwnd) (g_GUI_WinDrawStyleList[hwnd].pFocusStyle)
#define GETDISABLEDRAWSTYLE(hwnd) (g_GUI_WinDrawStyleList[hwnd].pDisableStyle)
#define GETWNDPARENT(hwnd) (g_GUI_WindowPositionList[hwnd].parent)
#define GETWNDLASTSUCCESSOR(hwnd) (g_GUI_WindowPositionList[hwnd].hwndLastSuccessor)
//#define GETTRANSEFFIN(hwnd) (g_GUI_WindowList[hwnd].u8InTransEff)
//#define GETTRANSEFFOUT(hwnd) (g_GUI_WindowList[hwnd].u8OutTransEff)
//#define GETWNDPROC(hwnd) (g_GUI_WindowList[hwnd].WindowProc)
#define GETWNDPROCID(hwnd) (g_GUI_WindowList[hwnd].u8WinProcID)
#define GETWNDNAVI(hwnd) (g_GUI_WindowList[hwnd].aFocusNavigation)
//#define GETWNDACTIONEXEC(hwnd) (g_GUI_WindowList[hwnd].OnAction)
//#define GETWNDFOCUSGROUP(hwnd) (g_GUI_WindowList[hwnd].focusGroup)
#define GETWNDNORMALALPHA(hwnd) (g_GUI_WinAlphaDataList[hwnd].u8NormalAlpha)
#define GETWNDFOCUSALPHA(hwnd) (g_GUI_WinAlphaDataList[hwnd].u8FocusAlpha)
#define GETWNDDISABLEALPHA(hwnd) (g_GUI_WinAlphaDataList[hwnd].u8DisableAlpha)
#define GETWNDKEYEVENT(hwnd) (g_GUI_WindowList[hwnd].Keyevent)

INTERFACE HWND HWND_MAX;
INTERFACE WINDOWDATA _ZUI_TBLSEG * g_GUI_WindowList; //point to window list of current skin
INTERFACE WINDOWPOSDATA _ZUI_TBLSEG * g_GUI_WindowPositionList; //point to window list of current skin
INTERFACE WINDOWDRAWSTYLEDATA _ZUI_TBLSEG * g_GUI_WinDrawStyleList;
INTERFACE BOOLEAN OSDPAGE_BLENDING_ENABLE;
INTERFACE U8 OSDPAGE_BLENDING_VALUE;

#if ZUI_ENABLE_ALPHATABLE
INTERFACE WINDOWALPHADATA _ZUI_TBLSEG * g_GUI_WinAlphaDataList;
#endif

//for page control
INTERFACE HWND GetWndMaxOfOsdTable(U32 id);
INTERFACE WINDOWDATA* GetWindowListOfOsdTable(U32 id);
INTERFACE WINDOWDRAWSTYLEDATA* GetWindowStyleOfOsdTable(U32 id);
INTERFACE WINDOWPOSDATA* GetWindowPositionOfOsdTable(U32 id);
INTERFACE WINDOWALPHADATA* GetWindowAlphaDataOfOsdTable(U32 id);
INTERFACE BOOLEAN IsBlendingEnabledOfOsdTable(U32 id);
INTERFACE U8 GetBlendingValueOfOsdTable(U32 id);
INTERFACE U32 GetOsdTableTransEffIn(U32 id);
INTERFACE U32 GetOsdTableTransEffOut(U32 id);

#endif //#ifdef _ZUI_INTERNAL_INSIDE_

INTERFACE void SetOsdPageBlendingValue(BOOLEAN bEnable, U8 u8Value);

#undef INTERFACE


#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _MAPP_ZUI_APITABLE_H */

