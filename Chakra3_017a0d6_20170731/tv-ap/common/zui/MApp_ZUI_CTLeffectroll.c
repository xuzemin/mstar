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

#define MAPP_ZUI_CTL_EFFECTROLL_C
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

static U8 u8RollFbId = 0Xff;

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_EffectRollWinProc
///  Window Proc for "effect roll" control
///
///
///  @param [in]       hWnd HWND     window handle
///  @param [in]       pMsg PMSG     message type
///
///  @return S32 message execute result
///
///  @author MStarSemi @date 2009/2/24
///////////////////////////////////////////////////////////////////////////////
#define LOOP                32
#define DELAY               2  //ms

static void _MApp_ZUI_CTL_Effect_SpreadOut(HWND hWnd, U8 loop, U32 ms)
{
    GRAPHIC_DC *pBuffDC = MApp_ZUI_API_GetBufferDC();
    GRAPHIC_DC *pScrnDC = MApp_ZUI_API_GetScreenDC();
    MSAPI_OSDRegion CopyFB;
    MSAPI_OSDRegion PasteFB;
    GOP_GwinFBAttr fbAttr;

    RECT *subrect = &GETWNDINITRECT(hWnd);
    RECT *orgrect;

    HWND last_succ = GETWNDLASTSUCCESSOR(hWnd);
    HWND child;

    for (child = hWnd; child <= last_succ; child++)
    {
        orgrect = &GETWNDINITRECT(child);
        MApp_ZUI_API_UnionRect(subrect, orgrect);
    }

    MApi_GOP_GWIN_GetFBInfo(pScrnDC->u8FbID, &fbAttr);
    u8RollFbId = MApi_GOP_GWIN_GetFreeFBID();
    MApi_GOP_GWIN_CreateFB(u8RollFbId, 0, 0, subrect->width*3, subrect->height, fbAttr.fbFmt);

    //we MUST reset clip window before msAPI_OSD_CopyRegion()
    msAPI_OSD_SetClipWindow(0, 0, subrect->width*3-1, subrect->height-1);

    PasteFB.fbID=u8RollFbId;
    PasteFB.x=subrect->width;
    PasteFB.y=0;
    PasteFB.width=subrect->width;
    PasteFB.height=subrect->height;

    CopyFB.fbID=pScrnDC->u8FbID;
    CopyFB.x=subrect->left;
    CopyFB.y=subrect->top;
    CopyFB.width=subrect->width;
    CopyFB.height=subrect->height;
    msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

    //we MUST reset clip window before msAPI_OSD_CopyRegion()
    msAPI_OSD_SetClipWindow(0, 0, subrect->width*3-1, subrect->height-1);

    PasteFB.fbID=u8RollFbId;
    PasteFB.x=subrect->width*2;
    PasteFB.y=0;
    PasteFB.width=subrect->width;
    PasteFB.height=subrect->height;

    CopyFB.fbID=pBuffDC->u8FbID;
    CopyFB.x=subrect->left;
    CopyFB.y=subrect->top;
    CopyFB.width=subrect->width;
    CopyFB.height=subrect->height;
    msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

    U8 i;
    for(i=1; i < loop; i++)
    {
        U16 ww = subrect->width;
        U16 hh = subrect->height*i/loop;
        U16 xx = 0;
        U16 yy = 0;

        //we MUST reset clip window before msAPI_OSD_CopyRegion()
        msAPI_OSD_SetClipWindow(0, 0, subrect->width*3-1, subrect->height-1);

        PasteFB.fbID=u8RollFbId;
        PasteFB.x=0;
        PasteFB.y=0;
        PasteFB.width=subrect->width;
        PasteFB.height=subrect->height;

        CopyFB.fbID=u8RollFbId;
        CopyFB.x=subrect->width;
        CopyFB.y=0;
        CopyFB.width=subrect->width;
        CopyFB.height=subrect->height;
        msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

        PasteFB.fbID=u8RollFbId;
        PasteFB.x=xx;
        PasteFB.y=yy;
        PasteFB.width=ww;
        PasteFB.height=hh;

        CopyFB.fbID=u8RollFbId;
        CopyFB.x=subrect->width*2;
        CopyFB.y=0;
        CopyFB.width=subrect->width;
        CopyFB.height=hh;
        msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

        //we MUST reset clip window before msAPI_OSD_CopyRegion()
        msAPI_OSD_SetClipWindow(subrect->left, subrect->top, subrect->left+subrect->width-1, subrect->top+subrect->height-1);

        PasteFB.fbID=pScrnDC->u8FbID;
        PasteFB.x=subrect->left;
        PasteFB.y=subrect->top;
        PasteFB.width=subrect->width;
        PasteFB.height=subrect->height;

        CopyFB.fbID=u8RollFbId;
        CopyFB.x=0;
        CopyFB.y=0;
        CopyFB.width=subrect->width;
        CopyFB.height=subrect->height;
        msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

        msAPI_Timer_Delayms(ms);
    }

    MApi_GOP_GWIN_DestroyFB(u8RollFbId);

}

static void _MApp_ZUI_CTL_Effect_RollUp(HWND hWnd, U8 loop, U32 ms)
{
    GRAPHIC_DC *pBuffDC = MApp_ZUI_API_GetBufferDC();
    GRAPHIC_DC *pScrnDC = MApp_ZUI_API_GetScreenDC();
    MSAPI_OSDRegion CopyFB;
    MSAPI_OSDRegion PasteFB;
    GOP_GwinFBAttr fbAttr;

    RECT *subrect = &GETWNDINITRECT(hWnd);
    RECT *orgrect;

    HWND last_succ = GETWNDLASTSUCCESSOR(hWnd);
    HWND child;

    for (child = hWnd; child <= last_succ; child++)
    {
        orgrect = &GETWNDINITRECT(child);
        MApp_ZUI_API_UnionRect(subrect, orgrect);
    }

    MApi_GOP_GWIN_GetFBInfo(pScrnDC->u8FbID, &fbAttr);
    u8RollFbId = MApi_GOP_GWIN_GetFreeFBID();
    MApi_GOP_GWIN_CreateFB(u8RollFbId, 0, 0, subrect->width*3, subrect->height, fbAttr.fbFmt);

    //we MUST reset clip window before msAPI_OSD_CopyRegion()
    msAPI_OSD_SetClipWindow(0, 0, subrect->width*3-1, subrect->height-1);

    PasteFB.fbID=u8RollFbId;
    PasteFB.x=subrect->width;
    PasteFB.y=0;
    PasteFB.width=subrect->width;
    PasteFB.height=subrect->height;

    CopyFB.fbID=pBuffDC->u8FbID;
    CopyFB.x=subrect->left;
    CopyFB.y=subrect->top;
    CopyFB.width=subrect->width;
    CopyFB.height=subrect->height;
    msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

    //we MUST reset clip window before msAPI_OSD_CopyRegion()
    msAPI_OSD_SetClipWindow(0, 0, subrect->width*3-1, subrect->height-1);

    PasteFB.fbID=u8RollFbId;
    PasteFB.x=subrect->width*2;
    PasteFB.y=0;
    PasteFB.width=subrect->width;
    PasteFB.height=subrect->height;

    CopyFB.fbID=pScrnDC->u8FbID;
    CopyFB.x=subrect->left;
    CopyFB.y=subrect->top;
    CopyFB.width=subrect->width;
    CopyFB.height=subrect->height;
    msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

    U8 i;
    for(i=loop; i > 1; i--)
    {
        U16 ww = subrect->width;
        U16 hh = subrect->height*i/loop;
        U16 xx = 0;
        U16 yy = 0;

        //we MUST reset clip window before msAPI_OSD_CopyRegion()
        msAPI_OSD_SetClipWindow(0, 0, subrect->width*3-1, subrect->height-1);

        PasteFB.fbID=u8RollFbId;
        PasteFB.x=0;
        PasteFB.y=0;
        PasteFB.width=subrect->width;
        PasteFB.height=subrect->height;

        CopyFB.fbID=u8RollFbId;
        CopyFB.x=subrect->width;
        CopyFB.y=0;
        CopyFB.width=subrect->width;
        CopyFB.height=subrect->height;
        msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

        PasteFB.fbID=u8RollFbId;
        PasteFB.x=xx;
        PasteFB.y=yy;
        PasteFB.width=ww;
        PasteFB.height=hh;

        CopyFB.fbID=u8RollFbId;
        CopyFB.x=subrect->width*2;
        CopyFB.y=0;
        CopyFB.width=subrect->width;
        CopyFB.height=hh;
        msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

        //we MUST reset clip window before msAPI_OSD_CopyRegion()
        msAPI_OSD_SetClipWindow(subrect->left, subrect->top, subrect->left+subrect->width-1, subrect->top+subrect->height-1);

        PasteFB.fbID=pScrnDC->u8FbID;
        PasteFB.x=subrect->left;
        PasteFB.y=subrect->top;
        PasteFB.width=subrect->width;
        PasteFB.height=subrect->height;

        CopyFB.fbID=u8RollFbId;
        CopyFB.x=0;
        CopyFB.y=0;
        CopyFB.width=subrect->width;
        CopyFB.height=subrect->height;
        msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

        msAPI_Timer_Delayms(ms);
    }

    MApi_GOP_GWIN_DestroyFB(u8RollFbId);

}


S32 MApp_ZUI_CTL_EffectRollWinProc(HWND hWnd, PMSG pMsg)
{
    switch(pMsg->message)
    {
        case MSG_EFFECT_SPREADOUT:
            MApp_ZUI_API_PrepareBufferDC(MApp_ZUI_API_GetBufferDC());
            _MApp_ZUI_CTL_Effect_SpreadOut(hWnd, LOOP, DELAY);
            return 0;

        case MSG_EFFECT_ROLLUP:
            MApp_ZUI_API_PrepareBufferDC(MApp_ZUI_API_GetBufferDC());
            _MApp_ZUI_CTL_Effect_RollUp(hWnd, LOOP, DELAY);
            return 0;

        default:
            break;
    }
    return DEFAULTWINPROC(hWnd, pMsg);
}

#undef MAPP_ZUI_CTL_EFFECTROLL_C
