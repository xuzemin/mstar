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

#define MAPP_ZUI_CTL_PHOTODECODER_C

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------


#include "stdlib.h"
#include "stdio.h"
#include "datatype.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "msAPI_OSD.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_ZUI_CTLphotodecoder.h"
#include "msAPI_Memory.h"

#include "MApp_ZUI_ACTmultimedia.h"
#include "MApp_MultiMedia_Photo.h"

#include "OSDcp_Bitmap_EnumIndex.h"

#if (ENABLE_DMP)

static BOOLEAN g_bStartDecode = FALSE;
static HWND g_currentDecodeHwnd = HWND_INVALID;
static GUI_DATA_PHOTODECODER g_photoDecoderData[MAX_DECODE_NUM];
static U8 g_photoDecoderDataIndex = 0;

static void _MApp_ZUI_CTL_PhotoDecoderNext(HWND hWnd)
{
    HWND nextHWND;
    nextHWND = MApp_ZUI_ACT_QueryNextDecodeHwnd(hWnd);
    if(nextHWND != HWND_INVALID && MApp_ZUI_API_IsWindowVisible(nextHWND))
    {
        g_currentDecodeHwnd = nextHWND;
        MApp_ZUI_API_SetTimer(nextHWND, 0, 0);
        g_bStartDecode = FALSE;
    }
}

void MApp_ZUI_CTL_PhotoDecoderRefreshContent(HWND hwnd)
{
    MApp_ZUI_API_PostMessage(hwnd, MSG_DECODE, 0);
    g_photoDecoderDataIndex = 0;
}


void MApp_ZUI_CTL_PhotoDecoderRefreshContent_Stop()
{
    MApp_MultiMedia_Photo_StopDecode();
    MApp_ZUI_API_KillTimer(g_currentDecodeHwnd, 0);
    g_currentDecodeHwnd = HWND_INVALID;
}
///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_CTL_PhotoDecodeWinProc
///  Window Proc for "Photo Decode" control,
///     register a timer when being created.
//      And if timer event notified, then execute EN_EXE_CLOSE_CURRENT_OSD
///
///  @param [in]       hWnd HWND     window handle
///  @param [in]       pMsg PMSG     message type
///
///  @return S32 message execute result
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////

S32 MApp_ZUI_CTL_PhotoDecodeWinProc(HWND hWnd, PMSG pMsg)
{
    U16  u16PreviewLeft;
    U16  u16PreviewTop;
    RECT rect;
    U8 i;

    switch(pMsg->message)
    {
        case MSG_TIMER:
            if(g_bStartDecode == FALSE)
            {
                if(MApp_MultiMedia_Photo_StartDecode(MApp_ZUI_ACT_QueryMultiMediaFileIndex(hWnd), MApp_ZUI_ACT_GetCurrentMediaType()))
                {
                    MApp_ZUI_API_SetTimer(hWnd, 0, 0);
                    g_bStartDecode = TRUE;
                }
                else
                {
                    g_currentDecodeHwnd = HWND_INVALID;
                    MApp_ZUI_API_KillTimer(hWnd, 0);
                    MApp_ZUI_API_InvalidateAllSuccessors(hWnd);
                    //decode next photo
                    _MApp_ZUI_CTL_PhotoDecoderNext(hWnd);
                }
            }
            else
            {
                switch(MApp_MultiMedia_Photo_Decode(FALSE))
                {
                    case EXIT_PHOTO_DECODE_DONE:
                        //capture photo to dwin buffer
                        if(g_photoDecoderDataIndex < MAX_DECODE_NUM)
                        {
                            BOOLEAN bDisplayPath = MApp_ZUI_API_GetWindowData(hWnd);
                            MApp_ZUI_API_GetWindowInitialRect(hWnd, &rect);
                            if (bDisplayPath)
                            {
                                MApp_MultiMedia_Photo_SetDisplay(rect.left,rect.top, (U16 *)&rect.width, (U16 *)&rect.height, bDisplayPath);
                            }
                            else
                            {
                                if(G_FACTORY_SETTING.g_u8FactoryImageRotate)
                                    MApp_MultiMedia_Photo_SetDisplay(PANEL_WIDTH-(rect.left+rect.width)-ZUI_EXTERNAL_STORAGE_XSTART, PANEL_HEIGHT-(rect.top+rect.height)-ZUI_EXTERNAL_STORAGE_YSTART, (U16 *)&rect.width, (U16 *)&rect.height, bDisplayPath);
                                else
                                    MApp_MultiMedia_Photo_SetDisplay(rect.left+ZUI_EXTERNAL_STORAGE_XSTART, rect.top+ZUI_EXTERNAL_STORAGE_YSTART, (U16 *)&rect.width, (U16 *)&rect.height, bDisplayPath);
                            }
                            g_photoDecoderData[g_photoDecoderDataIndex].hwnd = hWnd;
                            g_photoDecoderData[g_photoDecoderDataIndex].u16Width = rect.width;
                            g_photoDecoderData[g_photoDecoderDataIndex].u16Height = rect.height;
                            g_photoDecoderDataIndex++;
                        }
                        g_currentDecodeHwnd = HWND_INVALID;
                        MApp_ZUI_API_KillTimer(hWnd, 0);
                        MApp_ZUI_API_InvalidateAllSuccessors(hWnd);

                        //decode next photo
                        _MApp_ZUI_CTL_PhotoDecoderNext(hWnd);

                        break;
                    case EXIT_PHOTO_DECODE_FAIL:
                        g_currentDecodeHwnd = HWND_INVALID;
                        MApp_ZUI_API_KillTimer(hWnd, 0);
                        break;
                    default:
                        break;
                }
            }
            break;
        case MSG_PAINT:
            {
                BOOLEAN bDisplayPath = MApp_ZUI_API_GetWindowData(hWnd);
                const PAINT_PARAM * param = (const PAINT_PARAM*)pMsg->wParam;
                for(i = 0; i < g_photoDecoderDataIndex; i++)
                {
                    if(g_photoDecoderData[i].hwnd == hWnd)
                    {
                        break;
                    }
                }
                if(i < g_photoDecoderDataIndex)
                {
                    //draw hwnd using default winproc
                    DEFAULTWINPROC(hWnd, pMsg);

                    //bitblt from dwin buffer to gwin buffer
                    MApp_ZUI_API_GetWindowInitialRect(hWnd, &rect);
                    if (bDisplayPath)
                    {
                        u16PreviewLeft = rect.left + (rect.width - g_photoDecoderData[i].u16Width) / 2;
                        u16PreviewTop= rect.top + (rect.height - g_photoDecoderData[i].u16Height) / 2;
                        MApp_MultiMedia_Photo_GOP_Bitblt( param->dc.u8FbID, rect.left, rect.top, g_photoDecoderData[i].u16Width, g_photoDecoderData[i].u16Height, u16PreviewLeft, u16PreviewTop);
                    }
                    else
                    {
                        RECT rcDraw;
                        DRAW_FILL_RECT draw_rect;
                        rcDraw.left =  rect.left + (rect.width - g_photoDecoderData[i].u16Width)/2 + 1;
                        rcDraw.top = rect.top + (rect.height - g_photoDecoderData[i].u16Height)/2 + 1;
                        rcDraw.width = g_photoDecoderData[i].u16Width-2;
                        rcDraw.height = g_photoDecoderData[i].u16Height-2;
                        draw_rect.fromColor = ZUI_COLOR_TRANSPARENT_RGB8888;
                        draw_rect.toColor = ZUI_COLOR_TRANSPARENT_RGB8888;
                        draw_rect.eGradient = OSD_GRADIENT_DISABLE;
                        _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, &draw_rect, &param->dc, &rcDraw);
                    }
                    return 0;
                }
                break;
            }
         case MSG_DECODE:
            MApp_ZUI_CTL_PhotoDecoderRefreshContent_Stop();
            MApp_MultiMedia_Photo_CloseDisplay();
            MApp_ZUI_API_SetTimer(hWnd, 0, 500);
            g_currentDecodeHwnd = hWnd;
            g_bStartDecode = FALSE;
            return 0;
    }
    return DEFAULTWINPROC(hWnd, pMsg);
}

#endif

#undef MAPP_ZUI_CTL_PHOTODECODER_C
