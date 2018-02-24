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

#define MAPP_ZUI_CTL_EFFECTSLIDEITEM_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "msAPI_Timer.h"
#include "MsTypes.h"
#include "apiGOP.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_APIstyletables.h"
#include "MApp_ZUI_APIalphatables.h"
#include "MApp_ZUI_CTLdynalist.h"
///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_EffectSlideItemWinProc
///  Window Proc for "effect slide" control
///
///
///  @param [in]       hWnd HWND     window handle
///  @param [in]       pMsg PMSG     message type
///
///  @return S32 message execute result
///
///  @author MStarSemi @date 2009/3/19
///////////////////////////////////////////////////////////////////////////////
#define LOOP                8
#define DELAY               0  //ms

static void _MApp_ZUI_CTL_Effect_DrawSlideBufferDC(HWND taghWnd, HWND srchWnd, S8 step, S8 loop)
{
    //note: it is ALMOST default painting flow, but not update to screen!
    HWND hwnd;
    RECT * rect_inv;
    //BOOLEAN bFullScreen; //always full screen!
    PAINT_PARAM param;

    //redraw all controls
    rect_inv = &GETWNDINITRECT(HWND_MAINFRAME);
    ZUI_MSG(printf("[MainFrame]Repaint rect(%lu,%lu,%lu,%lu)\n",(U32)rect_inv->left, (U32)rect_inv->top,(U32)rect_inv->width, (U32)rect_inv->height);)
    //bFullScreen = TRUE;

    param.dc = *MApp_ZUI_API_GetBufferDC();
    param.dc.u8ConstantAlpha = 0xFF; //disable alpha blending

    //draw main frame...
    //_MApp_ZUI_API_DrawStyleList(&param.dc, rect_inv, GETNORMALDRAWSTYLE(HWND_MAINFRAME));
    param.rect = rect_inv;
    param.rect_invalidate = rect_inv;
    param.bIsDisable = param.bIsFocus = FALSE;
    param.bIsVisible = TRUE;
    _MApp_ZUI_API_DefaultOnPaint(HWND_MAINFRAME, &param, TRUE);

    //draw others....
    for (hwnd = HWND_MAINFRAME+1; hwnd < HWND_MAX; hwnd++)
    {
        //PRINT("\n[Note] loop hwnd = %d, state = %ld, u32State&WS_VISIBLE = %d", hwnd, u16State, (U16)u16State&WS_VISIBLE);

        param.bIsVisible = MApp_ZUI_API_IsWindowVisible(hwnd);
        if (param.bIsVisible)/* &&
            _MApp_ZUI_API_IsInsideScreen(&GETWNDRECT(hwnd)) )*/
        {
            RECT rect;
            MApp_ZUI_API_GetWindowRect(hwnd, &rect);
            param.rect = &rect;
            //if ( MApp_ZUI_API_DoesIntersect(rect_inv, param.rect) ) //always full screen!
            {
                param.bIsDisable = !MApp_ZUI_API_IsWindowEnabled(hwnd);
                param.bIsFocus = FALSE;
                param.dc.bSrcAlphaReplaceDstAlpha = ((GETWNDINITSTATE(hwnd)&WS_SRCALPHAREPLACEDSTALPHA) != 0);

                //printf("\n[Note] send paint msg to win %d", hwnd);
                MApp_ZUI_API_SendMessage(hwnd, MSG_PAINT, (WPARAM)&param);
            }
            //else
            //{
            //    bFullScreen = FALSE; //something need not to paint (partally paint)
            //}
        }
    }

    //draw focus....
    PAINT_PARAM focusparam = param;
    RECT rect_src;
    RECT rect_tag;
    MApp_ZUI_API_GetWindowRect(srchWnd, &rect_src);
    MApp_ZUI_API_GetWindowRect(taghWnd, &rect_tag);

    focusparam.rect->left = rect_src.left + (rect_tag.left - rect_src.left)*step/loop;
    focusparam.rect->top = rect_src.top + (rect_tag.top - rect_src.top)*step/loop;
    focusparam.rect->width = rect_tag.width;
    focusparam.rect->height = rect_tag.height;
    _MApp_ZUI_API_DrawStyleListNoText(&focusparam.dc, focusparam.rect, GETFOCUSDRAWSTYLE(taghWnd));

    //draw text....
    HWND starthwnd = MIN(srchWnd, taghWnd);
    HWND endhwnd = MAX(srchWnd, taghWnd);

    for (hwnd = starthwnd; hwnd <= endhwnd; hwnd++)
    {
        //PRINT("\n[Note] loop hwnd = %d, state = %ld, u32State&WS_VISIBLE = %d", hwnd, u16State, (U16)u16State&WS_VISIBLE);

        param.bIsVisible = MApp_ZUI_API_IsWindowVisible(hwnd);
        if (param.bIsVisible)/* &&
            _MApp_ZUI_API_IsInsideScreen(&GETWNDRECT(hwnd)) )*/
        {
            RECT rect;
            MApp_ZUI_API_GetWindowRect(hwnd, &rect);
            param.rect = &rect;
            //if ( MApp_ZUI_API_DoesIntersect(rect_inv, param.rect) ) //always full screen!
            {
                param.bIsDisable = !MApp_ZUI_API_IsWindowEnabled(hwnd);
                param.bIsFocus = FALSE;
                param.dc.bSrcAlphaReplaceDstAlpha = ((GETWNDINITSTATE(hwnd)&WS_SRCALPHAREPLACEDSTALPHA) != 0);

                //printf("\n[Note] send paint msg to win %d", hwnd);
                MApp_ZUI_API_SendMessage(hwnd, MSG_PAINT, (WPARAM)&param);
            }
            //else
            //{
            //    bFullScreen = FALSE; //something need not to paint (partally paint)
            //}
        }
        if (hwnd == 0xFFFF) // check end of hwnd
            break;
    }

    MApp_ZUI_API_ReleaseWithoutUpdateDC(); //note: don't update!!

    //PRINT("Repaint buffer complete, cost=%d)\n", MsOS_GetSystemTime()-start_time);
    /*
    if (bFullScreen)
        MApp_ZUI_API_ReleaseFullScreenDC();
    else
        MApp_ZUI_API_ReleaseDC(rect_inv);
    */

    //printf("==end\n");
}

static void _MApp_ZUI_CTL_Effect_SlideItem(HWND taghWnd, HWND srchWnd, S8 loop, U32 ms)
{
    S8 step;

    GRAPHIC_DC *pBuffDC = MApp_ZUI_API_GetBufferDC();
    GRAPHIC_DC *pScrnDC = MApp_ZUI_API_GetScreenDC();
    MSAPI_OSDRegion CopyFB;
    MSAPI_OSDRegion PasteFB;

    HWND parent = MApp_ZUI_API_GetParent(taghWnd);
    HWND last_succ = GETWNDLASTSUCCESSOR(parent);
    RECT *rect = &GETWNDINITRECT(parent);

    HWND child;
    RECT *subrect;

    for (child = parent; child <= last_succ; child++)
    {
        subrect = &GETWNDINITRECT(child);
        MApp_ZUI_API_UnionRect(rect, subrect);

        if (child == 0xFFFF) // check end of hwnd
            break;
    }

    for(step=1; step <= loop; step++)
    {
        _MApp_ZUI_CTL_Effect_DrawSlideBufferDC(taghWnd, srchWnd, step, loop);

        //we MUST reset clip window before msAPI_OSD_CopyRegion()
        msAPI_OSD_SetClipWindow(rect->left, rect->top, rect->left+rect->width-1, rect->top+rect->height-1);

        PasteFB.fbID=pScrnDC->u8FbID;
        PasteFB.x=rect->left;
        PasteFB.y=rect->top;
        PasteFB.width=rect->width;
        PasteFB.height=rect->height;

        CopyFB.fbID=pBuffDC->u8FbID;
        CopyFB.x=rect->left;
        CopyFB.y=rect->top;
        CopyFB.width=rect->width;
        CopyFB.height=rect->height;
        msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

        msAPI_Timer_Delayms(ms);
    }
}

S32 MApp_ZUI_CTL_EffectSlideItemWinProc(HWND hWnd, PMSG pMsg)
{
    switch(pMsg->message)
    {
        case MSG_EFFECT_SLIDEITEM:
        {
            HWND taghWnd = MApp_ZUI_API_GetFocus();
            HWND srchWnd = pMsg->wParam;

            GUI_DATA_DYNAMIC_LIST * windata = (GUI_DATA_DYNAMIC_LIST*)GETWNDDATA(GETWNDPARENT(taghWnd));

            if (windata == 0
                || windata->pVarData == 0
                || (windata->pVarData->hwndFirstShown <= srchWnd && srchWnd <= windata->pVarData->hwndLastShown)
                )

            {
                _MApp_ZUI_CTL_Effect_SlideItem(taghWnd, srchWnd, LOOP, DELAY);
            }
            return 0;
}
        default:
            break;
    }
    return DEFAULTWINPROC(hWnd, pMsg);
}

#undef MAPP_ZUI_CTL_EFFECTSLIDEITEM_C
