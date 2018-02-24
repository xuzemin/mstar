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

#ifndef _MAPP_ZUI_CTL_LIST_BOX_H
#define _MAPP_ZUI_CTL_LIST_BOX_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

//////List Box////////////////////////////////////////////////////
typedef struct //List Box Item data
{
    DRAWSTYLE * pDrawItemNormal;
    DRAWSTYLE * pDrawItemFocus;
    U16 u16Param;

} GUI_DATA_LIST_BOX_ITEM;


typedef struct  //List Box collection data
{
    GUI_DATA_LIST_BOX_ITEM * pItems; //internal thumbnail list array, NULL for empty set
    U16 u16Count;       //internal thumbnail count
    U16 u16Size;        //array size... grater or equal to count....
    U16 u16FocusIndex;       //internal thumbnail focus index, NOTE: assume single selection
    U16 u16StartItem;       //first item in this scroll view (include)
    U16 u16EndItem;     //last item in this scroll view  (exclude)

}GUI_DATA_LIST_BOX_INTERNAL;

#define LB_FLAG_SCROLL_PAGE         BIT0
#define LB_FLAG_DOWN_AS_SELECT      BIT1
#define LB_FLAG_RIGHT_AS_SELECT     BIT2

typedef enum
{
    LB_FOCUS_AUTO,
    LB_FOCUS_ALWAYS_HIDE,
    LB_FOCUS_ALWAYS_SHOW,
} GUI_DATA_LIST_BOX_FOCUS_ENUM;

typedef struct
{
    // Thumbnail Data
    GUI_DATA_LIST_BOX_INTERNAL list; //internal data
    //fpIndexString DisplayString;
    //fpIndexBitmap DisplayBitmap;

} GUI_VARDATA_LIST_BOX;

typedef struct //List Box control data
{
    GUI_VARDATA_LIST_BOX *pVardata;
    U16 u16ListBorderWidth; //reserved for outer border space
    U16 u16ListBorderHeight;    //reserved for outer border space
    U16 u16ItemBorderWidth; //reserved for item border space
    U16 u16ItemBorderHeight;    //reserved for item border space
    U16 u16ItemGapX;        //reserved between item and item
    U16 u16ItemGapY;        //reserved between item and item

    U16 u16ThumbRowCount;       //internal thumbnail display row grid count, should be > 0
    U16 u16ThumbColumnCount;    //internal thumbnail display column grid count, should be > 0
    //U16 u16ThumbItemSelBorder; //border for displaying selected items
    U16 u16ThumbFormatFlag;         //thumbnail list display flags
                            // LB_FLAG_SCROLL_PAGE: scroll a page <-> scroll a line

    GUI_DATA_LIST_BOX_FOCUS_ENUM enFocusType;

    //Background drawing style
    //DRAWSTYLE * pDrawBackground; //NULL for empty background

    //Non-Selected Item drawing style
    DRAWSTYLE * DrawItemBGNormal; //NULL for empty style

    //Selected Item drawing style
    DRAWSTYLE * DrawItemBGFocus; //NULL for empty style

    HWND hWndScrollBar;         //HWND_INVALID for no scrollbar binding

    //fpOwnerDrawThumbItem OwnerDrawItem;//NULL for static BMP case, Not-NULL for using owner draw

    // Event
    //CALLBACK_SEL_CHANGED OnSelectionChanged;


} GUI_DATA_LIST_BOX;
extern S32 MApp_ZUI_CTL_ListBoxWinProc(HWND, PMSG);

#define LISTBOXWINPROC MApp_ZUI_CTL_ListBoxWinProc

extern BOOLEAN MApp_ZUI_CTL_ListBoxSetSelectIndex(HWND hwnd, U16 select_idx);
extern U16 MApp_ZUI_CTL_ListBoxGetSelectIndex(HWND hwnd);

extern BOOLEAN MApp_ZUI_CTL_ListBoxSetItems(HWND hwnd, GUI_DATA_LIST_BOX_ITEM * pItems, U16 u16Count);
//extern BOOLEAN MApp_ZUI_CTL_ListBoxSetItemsCallback(HWND hwnd, fpIndexString fp_str, fpIndexBitmap fp_bmp, U16 u16Count);
extern void MApp_ZUI_CTL_ListBoxClearItems(HWND hwnd);


////////////////////////////////////////////////////////////////////////////////////
// MACRO
//
#define CTL_GETLISTBOXLIST(hwnd)  (((GUI_DATA_LIST_BOX *)g_GUI_WindowList[hwnd].pWindowData)->pVardata->list)
//#define CTL_GETLISTBOXSTRCALLBACK(hwnd)  (((GUI_DATA_LIST_BOX *)g_GUI_WindowList[hwnd].pWindowData)->pVardata->DisplayString)
//#define CTL_GETLISTBOXBMPCALLBACK(hwnd)  (((GUI_DATA_LIST_BOX *)g_GUI_WindowList[hwnd].pWindowData)->pVardata->DisplayBitmap)

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _MAPP_ZUI_CTL_LIST_BOX_H */

