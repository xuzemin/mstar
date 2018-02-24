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

#define MAPP_ZUI_CTL_ROTATESTATIC_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "stdlib.h"
#include "stdio.h"
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
#include "MApp_ZUI_ACTglobal.h"

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_RotateStaticWinProc
///  Window Proc for "rotate static" control,
///     which draw the original static content with 90 degree rotation
///
///  @param [in]       hWnd HWND     window handle
///  @param [in]       pMsg PMSG     message type
///
///  @return S32 message execute result
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////

S32 MApp_ZUI_CTL_RotateStaticWinProc(HWND hWnd, PMSG pMsg)
{
    switch(pMsg->message)
    {
        case MSG_PAINT:
            {
                //get buffer GC for offline drawing...
                PAINT_PARAM * param = (PAINT_PARAM*)pMsg->wParam;
                U8 u8OrigFbID = param->dc.u8FbID;
                RECT rcTemp;
                RECT * rcOrig;

                //step1: create temp buffer
                MSAPI_OSDRegion CopyFB;
                MSAPI_OSDRegion PasteFB;
                GFX_Buffer_Format gefmt;
                U16 u16AlignWidth;
                U16 u16AlignHeight;
                #if (MPLAYER_BITMAP_FORMAT == MPLAYER_I8)
                gefmt = GE_FMT_I8;
                u16AlignWidth = ((param->rect->width + 0x0F) & ~(0x0F));
                u16AlignHeight = ((param->rect->height + 0x0F) & ~(0x0F));
                #else
                gefmt = GFX_FMT_RGB565;
                u16AlignWidth = ((param->rect->width * 2 + 0x0F) & ~(0x0F))/2;
                u16AlignHeight = ((param->rect->height * 2 + 0x0F) & ~(0x0F))/2;
                #endif
                param->dc.u8FbID = MApi_GOP_GWIN_GetFreeFBID();
                MApi_GOP_GWIN_CreateFB(
                    param->dc.u8FbID, 0, 0,u16AlignHeight, u16AlignWidth, gefmt);

                //step2: bitblt original background to temp buffer (270 degree rotate)
                CopyFB.fbID=u8OrigFbID;
                CopyFB.x=param->rect->left;
                CopyFB.y=param->rect->top;
                CopyFB.width=param->rect->width;
                CopyFB.height=param->rect->height;
                PasteFB.fbID=param->dc.u8FbID;
                PasteFB.x=0;
                PasteFB.y=0;
                PasteFB.width=CopyFB.width;
                PasteFB.height=CopyFB.height;
                MApi_GOP_GWIN_Switch2FB(param->dc.u8FbID);
                //we MUST reset clip window before msAPI_OSD_CopyRegion()
                msAPI_OSD_SetClipWindow(
                    0, 0, u16AlignHeight-1, u16AlignWidth-1);

                MDrv_GE_SetRotate(GEROTATE_270);
                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                MDrv_GE_SetRotate(0);

                //step3: draw to temp buffer (swap width and height, and reset origon point)
                //printf("[]rotate=%bu,%bu\n", u8OrigFbID, param->dc.u8FbID);
                RECT_SET(rcTemp, 0, 0, param->rect->height, param->rect->width);
                rcOrig = param->rect;
                param->rect = &rcTemp;
                DEFAULTWINPROC(hWnd, pMsg);
                param->rect = rcOrig;

                //step4: rotate bitblt to target with 90 degree rotation
                CopyFB.fbID=param->dc.u8FbID;
                CopyFB.x=0;
                CopyFB.y=0;
                CopyFB.width=param->rect->height;
                CopyFB.height=param->rect->width;
                PasteFB.fbID=u8OrigFbID;
                PasteFB.x=param->rect->left;
                PasteFB.y=param->rect->top;
                PasteFB.width=CopyFB.width;
                PasteFB.height=CopyFB.height;
                MApi_GOP_GWIN_Switch2FB(u8OrigFbID);
                //we MUST reset clip window before msAPI_OSD_CopyRegion()
                msAPI_OSD_SetClipWindow(
                    0, 0, PANEL_WIDTH-1, PANEL_HEIGHT-1);/*
                    PasteFB.y, PasteFB.x,
                    PasteFB.y+PasteFB.height, PasteFB.x+PasteFB.width);*/

                MDrv_GE_SetRotate(GEROTATE_90);
                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                MDrv_GE_SetRotate(0);
                MApi_GOP_GWIN_DestroyFB(param->dc.u8FbID);
                param->dc.u8FbID = u8OrigFbID;

            }
            return 0;
    }
    return DEFAULTWINPROC(hWnd, pMsg);
}

#undef MAPP_ZUI_CTL_ROTATESTATIC_C
