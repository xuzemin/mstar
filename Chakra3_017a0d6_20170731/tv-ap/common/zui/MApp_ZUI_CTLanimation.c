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

#define MAPP_ZUI_CTLANIMATE_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "datatype.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_APIalphatables.h"
#include "MApp_ZUI_APIcomponent.h"
#include "MApp_ZUI_ACTglobal.h"

/////////////////////////////////////////////////////
//NOTE: must be the same bank with table, because of GETWNDDATA()


#define CTL_ANI_DBG(x) //x



#define CTL_GETANIMATESTATE(hwnd)  (((GUI_DATA_ANIMATION *)GETWNDDATA(hwnd))->pVardata->u8State)
#define CTL_GETANIMATEFRAMEPOS(hwnd)  (((GUI_DATA_ANIMATION *)GETWNDDATA(hwnd))->pVardata->s8FramePos)
#define CTL_GETANIMATEFRAMESTEP(hwnd)  (((GUI_DATA_ANIMATION *)GETWNDDATA(hwnd))->pVardata->s8FrameStep)
//#define CTL_GETANIMATEFOCUSANISTATE(hwnd)  (((GUI_DATA_ANIMATION *)GETWNDDATA(hwnd))->pVardata->u8FocusAniState)


extern void _MApp_ZUI_API_ConvertComponentToDynamic(DRAWCOMPONENT comp, U16 u16CompIndex, void * pDraw);
extern U16 _MApp_ZUI_API_FindFirstComponentIndex(HWND hWnd, DRAWSTYLE_TYPE type, DRAWCOMPONENT comp);

///////////////////////////////////////////////////////////////////////////////
///  global static  _MApp_ZUI_CTL_AnimationGetState
///  check current status (invisible/disabled/focus/normal)
///
///  @param [in]       hwnd HWND     window handle
///
///  @return U8 {0,1,2,3} = (invisible/disabled/focus/normal)
///
///  @author MStarSemi @date 2007/1/29
///////////////////////////////////////////////////////////////////////////////
static U8 _MApp_ZUI_CTL_AnimationGetState(HWND hwnd)
{
    //WINDOWDATA * win = &g_GUI_WindowList[hwnd];

    if (MApp_ZUI_API_IsWindowVisible(hwnd)) //GETWNDSTATE(hwnd) & WS_VISIBLE)
    {
        if (!MApp_ZUI_API_IsWindowEnabled(hwnd)) //GETWNDSTATE(hwnd) & WS_DISABLED)
            return 1;
        else if (hwnd == MApp_ZUI_API_GetFocus() ||     MApp_ZUI_API_IsParentFocused(hwnd))
            return 2;
        else
            return 3;
    }
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
///  global  _MApp_ZUI_CTL_AnimationOnTimer
///  timer event handler for "Normal/Disabled/Focus Animation" control, which override focus state to draw a array of BITMAP frames
///
///  @param [in]       hwnd HWND     window handle
///  @param [in]       pMsg PMSG     message type
///
///  @return no return value
///
///  @author MStarSemi @date 2007/1/29
///////////////////////////////////////////////////////////////////////////////

static void _MApp_ZUI_CTL_AnimationOnTimer(HWND hwnd, PMSG pMsg)
{
    //WINDOWDATA * win;
    GUI_DATA_ANIMATION *windata;
    S8 s8FrameCount;
    S8 s8PrevFrame;
    U8 u8State;

    //win = &g_GUI_WindowList[hwnd];
    windata = (GUI_DATA_ANIMATION*)GETWNDDATA(hwnd);

    //PRINT("\n[AnimationOnTimer] wparam = %ld", pMsg->wParam);
    if (pMsg->wParam == 0)
    {
        s8PrevFrame = CTL_GETANIMATEFRAMEPOS(hwnd);
        u8State = _MApp_ZUI_CTL_AnimationGetState(hwnd);
        //PRINT("\n[AnimationOnTimer] u8State = %d", (U16)u8State);
        switch (u8State)
        {
            case 1:
                s8FrameCount = windata->s8DisabledFrameCount;
                break;
            case 2:
                s8FrameCount = windata->s8FocusFrameCount;
                break;
            case 3:
                s8FrameCount = windata->s8NormalFrameCount;
                break;
            default:
            case 0:
                //s8FrameCount = 0;
                s8FrameCount = windata->s8NormalFrameCount;
                break;
        }
        //PRINT("\n[AnimationOnTimer] s8FrameCount = %d", (U8)s8FrameCount);
        //for playback...
        CTL_GETANIMATEFRAMEPOS(hwnd) += CTL_GETANIMATEFRAMESTEP(hwnd);
        //PRINT("\n[AnimateionOnTimer] windata->s8FramePos = %d", windata->s8FramePos);
        if (CTL_GETANIMATEFRAMEPOS(hwnd) >= s8FrameCount)
        {
            if (windata->u8Flags&FA_FLAG_LOOP_BACK)
            {
                CTL_GETANIMATEFRAMEPOS(hwnd) = s8FrameCount-1;
                CTL_GETANIMATEFRAMESTEP(hwnd) = -1;
            }
            else if (windata->u8Flags&FA_FLAG_REPEAT_ONCE)
            {
                CTL_GETANIMATEFRAMEPOS(hwnd) = 0;
                CTL_GETANIMATEFRAMESTEP(hwnd) = 1;
                MApp_ZUI_API_KillTimer(hwnd, 0);
            }
            else
            {
                CTL_GETANIMATEFRAMEPOS(hwnd) = 0;
                CTL_GETANIMATEFRAMESTEP(hwnd) = 1;
                MApp_ZUI_API_KillTimer(hwnd, 0);
                MApp_ZUI_API_SetTimer(hwnd, 1, windata->u16RepeatSleepTime);
            }
        }
        if (CTL_GETANIMATEFRAMEPOS(hwnd) < 0)
        {
            CTL_GETANIMATEFRAMEPOS(hwnd) = 0;
            CTL_GETANIMATEFRAMESTEP(hwnd) = 1;
            if (windata->u8Flags&FA_FLAG_REPEAT_ONCE)
                MApp_ZUI_API_KillTimer(hwnd, 0);
            else
            {
                MApp_ZUI_API_KillTimer(hwnd, 0);
                MApp_ZUI_API_SetTimer(hwnd, 1, windata->u16RepeatSleepTime);
            }
        }
        //PRINT("\n[AnimationOnTimer] windata->s8FramePos = %d, s8PrevFrame = %d", windata->s8FramePos, s8PrevFrame);
        if (CTL_GETANIMATEFRAMEPOS(hwnd) != s8PrevFrame)
        {
            //PRINT("\n[AnimationOnTimer] InvalidateRECT");
            MApp_ZUI_API_InvalidateWindow(hwnd);
        }
    }
    /*
    else if (pMsg->wParam == 2)
    {
        //PRINT("\n[AnimationOnTimer] InvalidateRECT");
        MApp_ZUI_API_InvalidateWindow(hwnd);
    }*/
    else
    {
        //for sleep...
        MApp_ZUI_API_KillTimer(hwnd, 1);
        MApp_ZUI_API_SetTimer(hwnd, 0, windata->u16FrameSleepTime);
    }
}

//#define _MAPP_ZUI_CTL_ANIMATION_FOCUS_FRAME_SLEEP 30 //note: hard code frame sleep time for focus animation...

///////////////////////////////////////////////////////////////////////////////
///  global  _MApp_ZUI_CTL_AnimationOnPaint
///  paint event handler for "Normal/Disabled/Focus Animation" control, which override focus state to draw a array of BITMAP frames
///
///  @param [in]       hwnd HWND     window handle
///  @param [in]       pMsg PMSG     message type
///
///  @return no return value
///
///  @author MStarSemi @date 2007/1/29
///////////////////////////////////////////////////////////////////////////////
extern void *memset(void * s, int c, size_t count);
void _MApp_ZUI_CTL_AnimationOnPaint(HWND hwnd, PMSG pMsg)
{
    //WINDOWDATA * win = &g_GUI_WindowList[hwnd];
    U16 * pFrame;
    GUI_DATA_ANIMATION * windata = (GUI_DATA_ANIMATION*)GETWNDDATA(hwnd);
    //RECT rect;
    //S16 ww = 0, hh = 0;
    PAINT_PARAM * param = (PAINT_PARAM*)pMsg->wParam;

    S8 s8FrameCount;
    U8 u8State; // = _MApp_ZUI_CTL_AnimationGetState(param);
    DRAWSTYLE_TYPE ds_type = DS_NORMAL;

    if (param->bIsVisible) //GETWNDSTATE(hwnd) & WS_VISIBLE)
    {
        if (param->bIsDisable) //GETWNDSTATE(hwnd) & WS_DISABLED)
        {
            u8State = 1;
            s8FrameCount = windata->s8DisabledFrameCount;
            pFrame = windata->pDisabledFrame;

            param->dc.u8ConstantAlpha = MApp_ZUI_API_GetDisableAlpha(hwnd);
            ds_type = DS_DISABLE;

        }
        else if (param->bIsFocus)
        {
            u8State = 2;
            s8FrameCount = windata->s8FocusFrameCount;
            pFrame = windata->pFocusFrame;

            param->dc.u8ConstantAlpha = MApp_ZUI_API_GetFocusAlpha(hwnd);
            ds_type = DS_FOCUS;

        }
        else
        {
            u8State = 3;
            s8FrameCount = windata->s8NormalFrameCount;
            pFrame = windata->pNormalFrame;

            param->dc.u8ConstantAlpha = MApp_ZUI_API_GetNormalAlpha(hwnd);

        }
    }
    else
    {
        u8State = 0;
        //s8FrameCount = 0;
        s8FrameCount = windata->s8NormalFrameCount;
        //pFrame = NULL;
        pFrame = windata->pNormalFrame;
        return;
    }


    //PRINT("[AnimationOnPaint] u8State = %d", (U8)u8State);

    /*switch (u8State)
    {
        case 1:
            s8FrameCount = windata->s8DisabledFrameCount;
            pFrame = windata->pDisabledFrame;
            break;
        case 2:
            s8FrameCount = windata->s8FocusFrameCount;
            pFrame = windata->pFocusFrame;
            break;
        case 3:
            s8FrameCount = windata->s8NormalFrameCount;
            pFrame = windata->pNormalFrame;
            break;
        default:
        case 0:
            //s8FrameCount = 0;
            s8FrameCount = windata->s8NormalFrameCount;
            //pFrame = NULL;
            pFrame = windata->pNormalFrame;
            break;
    }*/

    //PRINT("[AnimationOnPaint] s8FrameCount = %d", (U8)s8FrameCount);

    /*
    if (CTL_GETANIMATEFOCUSANISTATE(hwnd) > 0)
    {
        //resize animation....
        if (CTL_GETANIMATESTATE(hwnd) != u8State) //state changed...
        {
            CTL_GETANIMATEFRAMEPOS(hwnd) = 0; //reset frame...
            CTL_GETANIMATEFRAMESTEP(hwnd) = 1;

            if (CTL_GETANIMATESTATE(hwnd) == 2 && (u8State == 1 || u8State == 3) && windata->u16KillFocusResizeDuration > 0)
                CTL_GETANIMATEFOCUSANISTATE(hwnd) = 2; //lost focus...
            else if (u8State == 2 && (CTL_GETANIMATESTATE(hwnd) == 1 || CTL_GETANIMATESTATE(hwnd) == 3) && windata->u16SetFocusResizeDuration > 0)
                CTL_GETANIMATEFOCUSANISTATE(hwnd) = 1; //set focus...
            else
                CTL_GETANIMATEFOCUSANISTATE(hwnd) = 0; //no animation...

            CTL_GETANIMATESTATE(hwnd) = u8State;

            MApp_ZUI_API_KillTimer(hwnd, 0);
            MApp_ZUI_API_KillTimer(hwnd, 1);
            MApp_ZUI_API_KillTimer(hwnd, 2);
            if (CTL_GETANIMATEFOCUSANISTATE(hwnd) > 0)
                MApp_ZUI_API_SetTimer(hwnd, 2, _MAPP_ZUI_CTL_ANIMATION_FOCUS_FRAME_SLEEP);
            else
                MApp_ZUI_API_SetTimer(hwnd, 0, windata->u16FrameSleepTime);
        }
    }
    else*/
    {
        //non resize animation...
        if (CTL_GETANIMATEFRAMEPOS(hwnd) >= s8FrameCount || //out of range...
            CTL_GETANIMATESTATE(hwnd) != u8State) //state changed...
        {
            CTL_GETANIMATEFRAMEPOS(hwnd) = 0; //reset frame...
            CTL_GETANIMATEFRAMESTEP(hwnd) = 1;

            /*
            if (CTL_GETANIMATESTATE(hwnd) == 2 && (u8State == 1 || u8State == 3) && windata->u16KillFocusResizeDuration > 0)
                CTL_GETANIMATEFOCUSANISTATE(hwnd) = 2; //lost focus...
            else if (u8State == 2 && (CTL_GETANIMATESTATE(hwnd) == 1 || CTL_GETANIMATESTATE(hwnd) == 3) && windata->u16SetFocusResizeDuration > 0)
                CTL_GETANIMATEFOCUSANISTATE(hwnd) = 1; //set focus...
            else
                CTL_GETANIMATEFOCUSANISTATE(hwnd) = 0; //no animation...
            */

            CTL_GETANIMATESTATE(hwnd) = u8State;

            MApp_ZUI_API_KillTimer(hwnd, 0);
            MApp_ZUI_API_KillTimer(hwnd, 1);
            //MApp_ZUI_API_KillTimer(hwnd, 2);
            /*
            if (CTL_GETANIMATEFOCUSANISTATE(hwnd) > 0)
                MApp_ZUI_API_SetTimer(hwnd, 2, _MAPP_ZUI_CTL_ANIMATION_FOCUS_FRAME_SLEEP);
            else*/
                MApp_ZUI_API_SetTimer(hwnd, 0, windata->u16FrameSleepTime);
        }

    }

    /*
    rect = *param->rect;

    if (CTL_GETANIMATEFOCUSANISTATE(hwnd) > 0)
    {
        //resize animation....
        if (pFrame && s8FrameCount > 0)
        {
            S16 total = 0;
            if (CTL_GETANIMATEFOCUSANISTATE(hwnd) == 1)
                total = windata->u16SetFocusResizeDuration / _MAPP_ZUI_CTL_ANIMATION_FOCUS_FRAME_SLEEP;
            else
                total = windata->u16KillFocusResizeDuration / _MAPP_ZUI_CTL_ANIMATION_FOCUS_FRAME_SLEEP;
            if (CTL_GETANIMATEFRAMEPOS(hwnd) < total)
            {
                CTL_GETANIMATEFRAMEPOS(hwnd)++;
                ww = hh = 0;
                if (CTL_GETANIMATEFOCUSANISTATE(hwnd) == 1)
                {
                    ww = windata->u16NonFocusBorderWidth*(total-CTL_GETANIMATEFRAMEPOS(hwnd))/total;
                    hh = windata->u16NonFocusBorderHeight*(total-CTL_GETANIMATEFRAMEPOS(hwnd))/total;
                }
                else
                {
                    ww = windata->u16NonFocusBorderWidth*(CTL_GETANIMATEFRAMEPOS(hwnd))/total;
                    hh = windata->u16NonFocusBorderHeight*(CTL_GETANIMATEFRAMEPOS(hwnd))/total;
                }
                RECT_SCALE(rect, ww, hh);
                _MApp_ZUI_API_DrawComponent(CP_BITMAP, *pFrame, &param->dc, &rect);

            }
            else
            {
                CTL_GETANIMATEFOCUSANISTATE(hwnd) = 0;
                CTL_GETANIMATEFRAMEPOS(hwnd) = 0;
                MApp_ZUI_API_KillTimer(hwnd, 1);
                MApp_ZUI_API_KillTimer(hwnd, 2);
                MApp_ZUI_API_SetTimer(hwnd, 0, windata->u16FrameSleepTime);

                goto NO_RESIZE_PAINT_START;
            }
        }

    }
    else*/
    {
        U16 component_id = _MApp_ZUI_API_FindFirstComponentIndex(hwnd, ds_type, CP_BITMAP);
//NO_RESIZE_PAINT_START:
        //resize animation....
        if (pFrame && s8FrameCount > 0 &&
            CTL_GETANIMATEFRAMEPOS(hwnd) < s8FrameCount &&
            component_id != 0xFFFF)
        {
            DRAW_BITMAP draw_bitmap;
            RECT rect_hwnd;
            HWND Cur_Hwnd = windata->FirstItem;
            S8 Cur_Pos = CTL_GETANIMATEFRAMEPOS(hwnd);
            memset(&rect_hwnd,0,sizeof(RECT));

            if (CTL_GETANIMATEFRAMEPOS(hwnd) == 0)
            {
                MApp_ZUI_API_GetWindowInitialRect(windata->FirstItem, &rect_hwnd);
            }
            else
            {
                S8 ani;
                for (ani = 1; ani <= Cur_Pos; ani++)
                {
                    Cur_Hwnd++;
                }
                MApp_ZUI_API_GetWindowInitialRect(Cur_Hwnd, &rect_hwnd);
            }

            _MApp_ZUI_API_ConvertComponentToDynamic(CP_BITMAP, component_id, &draw_bitmap);
            /*
            if (u8State != 2)
                RECT_SCALE(rect, windata->u16NonFocusBorderWidth, windata->u16NonFocusBorderHeight);
            */

            //draw an bitmap frame...
            pFrame += CTL_GETANIMATEFRAMEPOS(hwnd);
            /*
            OSD_ALPHA_BLENDING alpha =
            {
                TRUE, COEF_CONST, ABL_FROM_CONST, pFrame->u8Constant_Alpha
            };

            //for Page Transition: consider global alpha...
            if ( hdc->pAlpha->bEnable_Blend && hdc->pAlpha->eBLEND_COEF == COEF_CONST )
            {
                U16 a = pFrame->u8Constant_Alpha;
                a *= hdc->pAlpha->u8Constant_Alpha;
                alpha.u8Constant_Alpha = a/255;
            }

            BMPHANDLE bmp = MApi_Osd_LoadBitmap(
                pFrame->bmpAddress, pFrame->bmpTotalBytes,
                pFrame->bmpWidth, pFrame->bmpHeight,
                pFrame->bmpColorFmt);
            MApi_Osd_DrawBitmap(hdc->pGC,
                            bmp,
                            &rect,
                            pFrame->bSrcColorKey,
                            pFrame->srcColorKeyFrom,
                            pFrame->srcColorKeyEnd,
                            &alpha);
            MDrv_GE_PE_FreeBitmap(bmp); //note: no free bitmap function
            */

            draw_bitmap.u16BitmapIndex = *pFrame;

            _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP, &draw_bitmap, &param->dc, &rect_hwnd);
            //_MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP, &draw_bitmap, &param->dc, param->rect);


        }
    }

}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_AnimationWinProc
///  Window Proc for "Normal/Disabled/Focus Animation" control,
///     which override focus state to draw a array of BITMAP frames
///
///  @param [in]       hwnd HWND     window handle
///  @param [in]       pMsg PMSG     message type
///
///  @return S32 message execute result
///
///  @author MStarSemi @date 2007/1/29
///////////////////////////////////////////////////////////////////////////////
S32 MApp_ZUI_CTL_AnimationWinProc(HWND hwnd, PMSG pMsg)
{
    //WINDOWDATA * win = &g_GUI_WindowList[hwnd];
    GUI_DATA_ANIMATION * windata;
    windata = (GUI_DATA_ANIMATION*)GETWNDDATA(hwnd);
    if (!windata)
    {
        CTL_ANI_DBG(printf("MApp_ZUI_CTL_AnimationWinProc(%x): data NULL\n", hwnd));
        ABORT();
        return DEFAULTWINPROC(hwnd, pMsg);
    }

    switch(pMsg->message)
    {
        case MSG_CREATE:
            {
                CTL_GETANIMATEFRAMEPOS(hwnd) = 0;
                CTL_GETANIMATEFRAMESTEP(hwnd) = 1;
                CTL_GETANIMATESTATE(hwnd) = 0;
                //CTL_GETANIMATEFOCUSANISTATE(hwnd) = 0;
                MApp_ZUI_API_SetTimer(hwnd, 0, windata->u16FrameSleepTime);
            }
            break;

        case MSG_DESTROY:
            {
                /* //for performance, skip them
                CTL_GETANIMATEFRAMEPOS(hwnd) = 0;
                CTL_GETANIMATEFRAMESTEP(hwnd)  = 1;
                CTL_GETANIMATESTATE(hwnd) = 0;
                CTL_GETANIMATEFOCUSANISTATE(hwnd) = 0;
                MApp_ZUI_API_KillTimer(hwnd, 0);
                MApp_ZUI_API_KillTimer(hwnd, 1);
                MApp_ZUI_API_KillTimer(hwnd, 2);
                */
            }
            break;

        case MSG_NOTIFY_HIDE: //needs to be added to PostMesageFilter()
            //if (pMsg->wParam == MN_HIDE)
            {
                CTL_GETANIMATEFRAMEPOS(hwnd) = 0;
                CTL_GETANIMATEFRAMESTEP(hwnd)  = 1;
                CTL_GETANIMATESTATE(hwnd) = 0;
                //CTL_GETANIMATEFOCUSANISTATE(hwnd) = 0;
            }
            break;

        case MSG_TIMER:
            //PRINT("\n[AnimationWinProc] Got timer, window id = %d", hwnd);
            if (MApp_ZUI_API_IsWindowVisible(hwnd))
            {
                _MApp_ZUI_CTL_AnimationOnTimer(hwnd, pMsg);
            }
            break;

        case MSG_PAINT:
            //should be visible: if (win->dwState & WS_VISIBLE)
            _MApp_ZUI_CTL_AnimationOnPaint(hwnd, pMsg);
            //draw default at the top...
            //return DEFAULTWINPROC(hwnd, pMsg);
            return 0;

        default:
            break;
    }

    return DEFAULTWINPROC(hwnd, pMsg);

}

#undef MAPP_ZUI_CTLANIMATE_C
