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

#define MAPP_ZUI_CTL_MAIN_FRAME_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


///////////////////////////////////////////////////////////////////////////////////////////////////
// Description: Main Frame at the bottom of GUI layout
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "datatype.h"
#include "msAPI_Timer.h"
#include "MsTypes.h"
#include "apiGOP.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_ACTglobal.h"
#if (ENABLE_SUPPORT_MM_PHOTO_4K_2K == 1)
#include "drvISR.h"
#endif
#define CTL_MFRAME_DBG(x) //x

//ZUI_PAINT_ALWAYS_FULL_SCREEN: if possible, always use full screen release
#define ZUI_PAINT_ALWAYS_FULL_SCREEN         0


extern void _MApp_ZUI_API_DefaultOnPaint(HWND hWnd, PAINT_PARAM * param, BOOLEAN bDrawText);

#if 0
BOOLEAN _MApp_ZUI_API_IsInsideScreen (const RECT* psrc)
{
    /*/return true if any part of the rectangle intersect the screen...

    S16 left, top, right, bottom;

    left = MAX(psrc->left, 0); //(psrc1->left > psrc2->left) ? psrc1->left : psrc2->left;
    right = MIN(psrc->left+psrc->width, UI_MENU_BUFF_WIDTH); //(psrc1->right < psrc2->right) ? psrc1->right : psrc2->right;
    if ( left >= right )
        return FALSE;

    top  = MAX(psrc->top, 0); //(psrc1->top > psrc2->top) ? psrc1->top : psrc2->top;
    bottom = MIN(psrc->top+psrc->height, UI_MENU_BUFF_HEIGHT); //(psrc1->bottom < psrc2->bottom)
                   //? psrc1->bottom : psrc2->bottom;
    if( top >= bottom )
        return FALSE;

    return TRUE;
    */

    //for testing: not allow partial and entire out of the screen....
    return psrc->left >= 0 &&
        psrc->left+psrc->width < UI_MENU_BUFF_WIDTH &&
        psrc->top >= 0 &&
        psrc->top+psrc->height < UI_MENU_BUFF_HEIGHT;
}
#endif


///////////////////////////////////////////////////////////////////////////////
///  private  _MApp_ZUI_CTL_MainFramePaint
///  "paint" event handler for main frame control
///  note: this is a special paint handler! not called from event dispatcher!
///        DO NOT MODIFY THIS FUNCTION!
///
///  @param [in]       hwndMainFrame HWND mainframe window handle
///  @param [in]       wParam WPARAM paint parameter
///
///  @return S32 event handler result, 0 = not full screen, 1 = full screen swap
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////

void _MApp_ZUI_CTL_MainFramePaint(HWND hwndMainFrame, WPARAM *pwParam)
{
    //note: it is default painting flow
    HWND hwnd;

    RECT *pstInvdRect;
    U8 u8TempRectIndex;
    BOOLEAN bIsInterSect;

    BOOLEAN bFullScreen;
    PAINT_PARAM paint_param;

#if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN) || \
      (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA))
    U8 u8GWinID = MApp_ZUI_API_QueryGWinID();
#endif

    U8 u8PrevGopID = MApi_GOP_GWIN_GetCurrentGOP();

#if ZUI_EXCEPTION_MULTITASK
    U32 u32Exception_Timer = 0;
#endif
    //2007/12/26: consider gop switching
    if (u8PrevGopID != OSD_GOP_ID)
        MApi_GOP_GWIN_SwitchGOP(OSD_GOP_ID);

    pstInvdRect = &(((INVALIDATE_CLIP *)pwParam)->stRect[0]);

    bFullScreen = MApp_ZUI_API_IsAllowFullScreenRelease();

    paint_param.dc = *MApp_ZUI_API_GetBufferDC();
    paint_param.dc.u8ConstantAlpha = 0xFF; //disable alpha blending

    { //draw main frame...
        /*
        _MApp_ZUI_API_DrawStyleList(&param.dc,
            &GETWNDINITRECT(hwndMainFrame),
            GETNORMALDRAWSTYLE(hwndMainFrame));
        */
        RECT stRect_mainframe;
        MApp_ZUI_API_GetWindowInitialRect(hwndMainFrame, &(stRect_mainframe));
        paint_param.rect = &stRect_mainframe;
        paint_param.rect_invalidate = pstInvdRect;
        paint_param.bIsDisable = paint_param.bIsFocus = FALSE;
        paint_param.bIsVisible = TRUE;
        _MApp_ZUI_API_DefaultOnPaint(hwndMainFrame, &paint_param, TRUE);
    }

    //draw others....
    for (hwnd = HWND_MAINFRAME+1; hwnd < HWND_MAX; hwnd++)
    {
        //PRINT("\n[Note] loop hwnd = %d, state = %ld, u32State&WS_VISIBLE = %d", hwnd, u16State, (U16)u16State&WS_VISIBLE);

        paint_param.bIsVisible = MApp_ZUI_API_IsWindowVisible(hwnd);
        if (paint_param.bIsVisible)/* &&
            _MApp_ZUI_API_IsInsideScreen(&GETWNDRECT(hwnd)) )*/
        {
            RECT rect;
            MApp_ZUI_API_GetWindowRect(hwnd, &rect);
            paint_param.rect = &rect;

#if ZUI_PAINT_ALWAYS_FULL_SCREEN
            //note: if bFullScreen, then draw everything in once
            //      if not bFullScreen, then draw necessary windows..
            if ( bFullScreen ||
                MApp_ZUI_API_DoesIntersect(pstInvdRect, paint_param.rect) )
#else
            for(u8TempRectIndex = 0, bIsInterSect = FALSE ; u8TempRectIndex < ((INVALIDATE_CLIP *)pwParam)->u8RectIndex ; u8TempRectIndex++)
            {
            #if (ENABLE_UI_3D_PROCESS)
                if(MApp_ZUI_API_Is_UI_3D_Mode_ON())
                {
                    //20100430, Must repaint all visible HWND when invalid one!!
                    bIsInterSect = TRUE;
                    break;
                }
                else
            #endif
                if (MApp_ZUI_API_DoesIntersect((pstInvdRect+u8TempRectIndex), paint_param.rect))
                {
                    bIsInterSect = TRUE;
                    break;
                }
            }

            if( bIsInterSect )
#endif //ZUI_PAINT_ALWAYS_FULL_SCREEN
            {
                paint_param.bIsDisable = !MApp_ZUI_API_IsWindowEnabled(hwnd);

                //note: we assume if one window get focus, the child will be painted as focus style..
                paint_param.bIsFocus = (MApp_ZUI_API_GetFocus()==hwnd || MApp_ZUI_API_IsParentFocused(hwnd));
                paint_param.dc.bSrcAlphaReplaceDstAlpha = ((GETWNDINITSTATE(hwnd)&WS_SRCALPHAREPLACEDSTALPHA) != 0);
                //printf("\n[Note] send paint msg to win %d (%d)\n", hwnd, paint_param.dc.bSrcAlphaReplaceDstAlpha);
                MApp_ZUI_API_SendMessage(hwnd, MSG_PAINT, (WPARAM)&paint_param);

                #if ZUI_EXCEPTION_MULTITASK
                //note: avoid painting loop waste too much time
                //please be attention here, if you want input some special function
                {
                    if(u32Exception_Timer == 0)
                    {
                        u32Exception_Timer = msAPI_Timer_GetTime0();
                    }
                    else if(msAPI_Timer_DiffTimeFromNow(u32Exception_Timer) > ZUI_EXCEPTION_MULITASK_TIMER )
                    {
                        MApp_ZUI_ACT_Exception_MultiTask();
                        u32Exception_Timer = msAPI_Timer_GetTime0();
                    }
                }
                #endif
            }
            else
            {
                bFullScreen = FALSE; //something need not to paint (partally paint)
            }
        }
    }

    //printf("[]gop=%bu\n", MApi_GOP_GWIN_GetCurrentGOP());
    //printf("[]gwin=%bu\n", MApi_GOP_GWIN_GetCurrentWinId());
    //printf("[]enable=%bu\n", MApi_GOP_GWIN_IsGWINEnabled(MApi_GOP_GWIN_GetCurrentWinId()));

    //PRINT("Repaint buffer complete, cost=%d)\n", MsOS_GetSystemTime()-start_time);
    if (bFullScreen)
    {
        MApp_ZUI_API_ReleaseFullScreenDC();
    }
    else
    {
        for(u8TempRectIndex = 0 ; u8TempRectIndex < ((INVALIDATE_CLIP *)pwParam)->u8RectIndex ; u8TempRectIndex++)
        {
            if((pstInvdRect+u8TempRectIndex)->width != 0)
                MApp_ZUI_API_ReleaseDC(pstInvdRect+u8TempRectIndex);
        }
    }
    //PRINT("Repaint end (%d,%d,%d,%d), cost=%d\n",
    //  rect_inv->left, rect_inv->top, rect_inv->width, rect_inv->height,
    //  MsOS_GetSystemTime()-start_time);

#if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN) || \
     (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA))
#if (ENABLE_SUPPORT_MM_PHOTO_4K_2K == 1)
	if (MDrv_Photo_Display_Get4K2KMode()== FALSE)
#endif
	MApi_GOP_GWIN_Enable(u8GWinID, TRUE);
#endif


    if (u8PrevGopID != OSD_GOP_ID)
        MApi_GOP_GWIN_SwitchGOP(u8PrevGopID);
}


///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_API_MainFrameWinProc
///  Window Proc for Main Frame (the most bottom window)
///
///  @param [in]       hwndMainFrame HWND     window handle
///  @param [in]       pMsg PMSG     message type
///
///  @return S32 message execute result
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
//extern DRAWSTYLE _MENU_TBLSEG _Skin_BlueTwo_MAINFRAME_DrawStyle2[];

S32 MApp_ZUI_CTL_MainFrameWinProc(HWND hwndMainFrame, PMSG pMsg)
{
    /*DRAW_WINDOW my_DesktopWindow0 =
    {
        20, {.u32AllColorValue = 0xFFFF0000}, {.u32AllColorValue = 0xFF707070}, eRECTBorderRound, {.u32AllColorValue = 0xFF00FF00}, 2, TRUE
    };*/

    //WINDOWDATA * win;
    //HWND hwnd;
    //GRAPHIC_DC * pdc;
    //RECT * rect_inv;
    //BOOLEAN bFullScreen;

    //PRINT("\n[Note] enter mainframe winproc\n");

    //win = &g_GUI_WindowList[HWND_MAINFRAME];

    switch(pMsg->message)
    {
        case MSG_CREATE:
            //printf("Desktop Created\n");
            break;

        case MSG_DESTROY:
            //printf("Desktop Destroy\n");
            //KillTimer(hwnd, 0);
            break;

        /* //note: move key events to MApp_ZUI_API_DispatchMessage....
        case MSG_KEYDOWN:
            {
                //forward key message if has focus....
                HWND focus = MApp_ZUI_API_GetFocus();
                if (HWND_INVALID != focus && hwnd != focus)
                    return MApp_ZUI_API_SendMessage(focus, msg, wparam, lparam);
            }
            break;*/

        //case MSG_PAINT:
        //    {
                //NOTE: to avoid recusrive call, move OnPaint() to another function...
                // MApp_ZUI_API_UpdateWindow() and _MApp_ZUI_API_WindowProcOnIdle()
                //    will directly call _MApp_ZUI_API_MainFramePaint()
        //    }
        //    return 0; //don't call default MSG_PAINT

        default:
            break;
    }

    return DEFAULTWINPROC(hwndMainFrame, pMsg);
}


#undef MAPP_ZUI_CTL_MAIN_FRAME_C
