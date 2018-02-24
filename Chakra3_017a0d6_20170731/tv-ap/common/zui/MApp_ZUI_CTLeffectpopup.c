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

#define MAPP_ZUI_CTL_EFFECTPOPUP_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "string.h"
#include "msAPI_Timer.h"
#include "MsTypes.h"
#include "apiGOP.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_APIstyletables.h"

extern BOOLEAN _MApp_ZUI_API_WindowProcOnIdle(void);

static U8 u8PopupFbId = 0Xff;
///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_EffectPopupWinProc
///  Window Proc for "effect popup" control
///
///
///  @param [in]       hWnd HWND     window handle
///  @param [in]       pMsg PMSG     message type
///
///  @return S32 message execute result
///
///  @author MStarSemi @date 2009/2/11
///////////////////////////////////////////////////////////////////////////////
#define XFACTOR             2   //decimal
#define YFACTOR             4   //decimal
#define LOOP                10
#define DELAY               20  //ms

static void _MApp_ZUI_CTL_Effect_Popup(HWND hWnd, U8 xfac, U8 yfac, S8 loop, U32 ms)
{
    GRAPHIC_DC *pScrnDC = MApp_ZUI_API_GetScreenDC();
    MSAPI_OSDRegion CopyFB;
    MSAPI_OSDRegion PasteFB;
    const RECT *winrect = &GETWNDINITRECT(HWND_MAINFRAME);
    RECT rect;
    memset(&rect,0,sizeof(RECT));
    GOP_GwinFBAttr fbAttr;

    MApp_ZUI_API_GetWindowRect(hWnd, &rect);

    MApi_GOP_GWIN_GetFBInfo(pScrnDC->u8FbID, &fbAttr);

    u8PopupFbId = MApi_GOP_GWIN_GetFreeFBID();
    MApi_GOP_GWIN_CreateFB(u8PopupFbId, 0, 0, winrect->width, winrect->height, fbAttr.fbFmt);

    RECT fg;
    RECT bg;

    RECT_SET(fg, rect.left, rect.top, rect.width, rect.height);
    RECT_SET(bg, rect.left-((rect.width*xfac/10)/2), rect.top-((rect.height*yfac/10)/2), rect.width+(rect.width*xfac/10), rect.height+(rect.height*yfac/10));

    msAPI_OSD_SetClipWindow(0, 0, 0+fg.width-1, 0+fg.height-1);
    CopyFB.fbID=pScrnDC->u8FbID;
    CopyFB.x=fg.left;
    CopyFB.y=fg.top;
    CopyFB.width=fg.width;
    CopyFB.height=fg.height;

    PasteFB.fbID=u8PopupFbId;
    PasteFB.x=0;
    PasteFB.y=0;
    PasteFB.width=CopyFB.width;
    PasteFB.height=CopyFB.height;
    msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

    msAPI_OSD_SetClipWindow(0, fg.height, bg.width-1, fg.height+bg.height-1);
    CopyFB.fbID=pScrnDC->u8FbID;
    CopyFB.x=bg.left;
    CopyFB.y=bg.top;
    CopyFB.width=bg.width;
    CopyFB.height=bg.height;

    PasteFB.fbID=u8PopupFbId;
    PasteFB.x=0;
    PasteFB.y=fg.height;
    PasteFB.width=CopyFB.width;
    PasteFB.height=CopyFB.height;
    msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

    S8 i;
    for(i=loop; i >= 0; i--)
    {
        msAPI_OSD_SetClipWindow(0, (fg.height)+(bg.height), bg.width-1, (fg.height)+(bg.height)+bg.height-1);
        CopyFB.fbID=u8PopupFbId;
        CopyFB.x=0;
        CopyFB.y=fg.height;
        CopyFB.width=bg.width;
        CopyFB.height=bg.height;

        PasteFB.fbID=u8PopupFbId;
        PasteFB.x=0;
        PasteFB.y=(fg.height)+(bg.height);
        PasteFB.width=CopyFB.width;
        PasteFB.height=CopyFB.height;
        msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);


        RECT item;
        RECT_SET(item, ((rect.width*xfac/10)*(loop-i)/loop)/2, ((rect.height*yfac/10)*(loop-i)/loop)/2, rect.width+((rect.width*xfac/10)*i/loop), rect.height+((rect.height*yfac/10)*i/loop));

        msAPI_OSD_SetClipWindow(0+(item.left), (fg.height)+(bg.height)+(item.top), 
        0+(item.left)+item.width-1, (fg.height)+(bg.height)+(item.top)+item.height-1);
        CopyFB.fbID=u8PopupFbId;
        CopyFB.x=0;
        CopyFB.y=0;
        CopyFB.width=fg.width;
        CopyFB.height=fg.height;

        PasteFB.fbID=u8PopupFbId;
        PasteFB.x=0+(item.left);
        PasteFB.y=(fg.height)+(bg.height)+(item.top);
        PasteFB.width=item.width;
        PasteFB.height=item.height;
        msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

        msAPI_OSD_SetClipWindow(bg.left, bg.top, bg.left+bg.width-1, bg.top+bg.height-1);
        CopyFB.fbID=u8PopupFbId;
        CopyFB.x=0;
        CopyFB.y=(fg.height)+(bg.height);
        CopyFB.width=bg.width;
        CopyFB.height=bg.height;

        PasteFB.fbID=pScrnDC->u8FbID;
        PasteFB.x=bg.left;
        PasteFB.y=bg.top;
        PasteFB.width=CopyFB.width;
        PasteFB.height=CopyFB.height;
        msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

        msAPI_Timer_Delayms(ms);
    }

    MApi_GOP_GWIN_DestroyFB(u8PopupFbId);

}

S32 MApp_ZUI_CTL_EffectPopupWinProc(HWND hWnd, PMSG pMsg)
{
    switch(pMsg->message)
    {
        case MSG_EFFECT_POPUP:
            _MApp_ZUI_API_WindowProcOnIdle();
            _MApp_ZUI_CTL_Effect_Popup(MApp_ZUI_API_GetFocus(), XFACTOR, YFACTOR, LOOP, DELAY);
            return 0;

        default:
            break;
    }
    return DEFAULTWINPROC(hWnd, pMsg);
}

#undef MAPP_ZUI_CTL_EFFECTPOPUP_C
