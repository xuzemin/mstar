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

#define MAPP_ZUI_CTL_PAGESCROLL_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "datatype.h"
#include "msAPI_OSD.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_APIalphatables.h"
#include "MApp_ZUI_APIcomponent.h"
#include "MApp_ZUI_ACTglobal.h"
#include "OSDcp_Bitmap_EnumIndex.h"

/*/////////////////////////////////////////////////////////////
// Page scroll for Philip OSD

   +---+ ("scrollbar_background.bmp" not inclued in this control)
   |   |
   |   |
   |   |
   |   |
   |   |
   |   |
   |   |
   |   |
   |   |
   |   |
   |+-+| ("scrollbar_pointer_top.bmp") 6x4 -> 8x4
   || ||
   || || ("scrollbar_pointer_middle.bmp") 6x1 -> 8x1
   || ||
   |+-+| ("scrollbar_pointer_bottom.bmp") 6x4 -> 8x4
   |   |
   |   |
   |   |
   |   |
   |   |
   |   |
   |   |
   +---+



*/

#define PAGE_SCROLL_IMAGE_HEIGHT1 4
#define PAGE_SCROLL_IMAGE_HEIGHT2 1
#define PAGE_SCROLL_IMAGE_HEIGHT3 4

#define PAGE_SCROLL_BAR_MIN_HEIGHT 60

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_PageScrollWinProc
///  Window Proc for "page scroll" control, which shows visible range of a specific dynamic list
///
///  @param [in]       hwnd HWND     window handle
///  @param [in]       pMsg PMSG     message type
///
///  @return S32 message execute result
///
///  @author MStarSemi @date 2007/1/29
///////////////////////////////////////////////////////////////////////////////
S32 MApp_ZUI_CTL_PageScrollWinProc(HWND hwnd, PMSG pMsg)
{
    //WINDOWDATA * win = &g_GUI_WindowList[hwnd];
    GUI_DATA_PAGESCROLL_VARDATA * windata =
        (GUI_DATA_PAGESCROLL_VARDATA*)MApp_ZUI_API_GetWindowData(hwnd);
    if (!windata)
    {
        //PRINT("MApp_ZUI_API_SpinWinProc(%x): data NULL\n", hwnd);
        //ABORT();
        return DEFAULTWINPROC(hwnd, pMsg);
    }

    switch(pMsg->message)
    {

        case MSG_PAINT:
            if (windata->u16TotalItems > 0 &&
                windata->u16PageBeginItem <= windata->u16PageEndItem &&
                windata->u16PageEndItem <= windata->u16TotalItems)
            {
                PAINT_PARAM * param = (PAINT_PARAM*)pMsg->wParam;
                U16 top = (U32)windata->u16PageBeginItem*param->rect->height/windata->u16TotalItems;
                U16 bottom = (U32)(windata->u16PageEndItem+1)*param->rect->height/windata->u16TotalItems - 1;

                //note: if bar legnth is too small, adjust to PAGE_SCROLL_BAR_MIN_HEIGHT
                if (bottom - top < PAGE_SCROLL_BAR_MIN_HEIGHT)
                {
                    top = (U32)windata->u16PageBeginItem*(param->rect->height-PAGE_SCROLL_BAR_MIN_HEIGHT)/windata->u16TotalItems;
                    bottom = (U32)(windata->u16PageEndItem+1)*(param->rect->height-PAGE_SCROLL_BAR_MIN_HEIGHT)/windata->u16TotalItems + PAGE_SCROLL_BAR_MIN_HEIGHT - 1;
                }

                if (param->bIsDisable)
                {
                    param->dc.u8ConstantAlpha = MApp_ZUI_API_GetDisableAlpha(hwnd);
                }
                else if (param->bIsFocus) //the same focus group
                {
                    param->dc.u8ConstantAlpha = MApp_ZUI_API_GetFocusAlpha(hwnd);
                }
                else
                {
                    param->dc.u8ConstantAlpha = MApp_ZUI_API_GetNormalAlpha(hwnd);
                }


                if (param->rect->height >= PAGE_SCROLL_IMAGE_HEIGHT1+PAGE_SCROLL_IMAGE_HEIGHT3)
                {
                    DRAW_BITMAP draw_bitmap;
                    RECT rcNew;

                    //draw top
                    RECT_SET(rcNew,
                        param->rect->left,
                        param->rect->top+top,
                        param->rect->width,
                        PAGE_SCROLL_IMAGE_HEIGHT1);
                    draw_bitmap.bSrcColorKey = TRUE;
                    draw_bitmap.srcColorKeyEnd = BITMAP_COLOR_KEY_RGB8888;
                    draw_bitmap.srcColorKeyFrom = BITMAP_COLOR_KEY_RGB8888;
                    draw_bitmap.u16BitmapIndex = E_BMP_SCROLLBAR_POINTER_TOP;
                    draw_bitmap.u8Constant_Alpha = 0xFF;

                    //printf("[top]%d,%d\n", rcNew.top, rcNew.height);

                    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP, &draw_bitmap, &param->dc, &rcNew);
                    rcNew.top += PAGE_SCROLL_IMAGE_HEIGHT1;

                    //draw middle
                    rcNew.height = bottom-top-(PAGE_SCROLL_IMAGE_HEIGHT1+PAGE_SCROLL_IMAGE_HEIGHT3);
                    if (rcNew.height > 0)
                    {
                        draw_bitmap.u16BitmapIndex = E_BMP_SCROLLBAR_POINTER_MIDDLE;

                    //printf("[mid]%d,%d\n", rcNew.top, rcNew.height);

                        _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP, &draw_bitmap, &param->dc, &rcNew);
                        rcNew.top += rcNew.height;
                    }

                    //draw bottom
                    rcNew.height = PAGE_SCROLL_IMAGE_HEIGHT3;
                    draw_bitmap.u16BitmapIndex = E_BMP_SCROLLBAR_POINTER_BOTTOM;

                    //printf("[bot]%d,%d\n", rcNew.top, rcNew.height);

                    _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP, &draw_bitmap, &param->dc, &rcNew);

                    return 0;

                }
            }
            return 0;

        default:
            break;
    }

    return DEFAULTWINPROC(hwnd, pMsg);

}

//////////////////////////////////////////////////////////////

void MApp_ZUI_CTL_PageScrollSetRange(HWND hwnd, GUI_DATA_PAGESCROLL_VARDATA * range)
{
    GUI_DATA_PAGESCROLL_VARDATA * windata =
        (GUI_DATA_PAGESCROLL_VARDATA*)MApp_ZUI_API_GetWindowData(hwnd);
    if (!windata)
        return;

    memcpy(windata, range, sizeof(GUI_DATA_PAGESCROLL_VARDATA));
    MApp_ZUI_API_InvalidateWindow(hwnd);
}


#undef MAPP_ZUI_CTL_PAGESCROLL_C
