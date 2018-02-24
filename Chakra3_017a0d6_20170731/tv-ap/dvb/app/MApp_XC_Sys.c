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
#define _APP_XC_SYS_C_

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
// Common Definition
#include <string.h>
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "msAPI_Global.h"

// Driver

// API
#include "msAPI_Video.h"
#include "apiXC.h"
#include "apiXC_Adc.h"

#include "apiXC_Sys.h"
#include "apiPNL.h"
#include "apiGOP.h"

// APP
#include "MApp_ChannelChange.h"
#include "MApp_Scaler.h"
#include "MApp_GlobalVar.h"
#include "MApp_MVDMode.h"
#include "MApp_XC_Sys.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalFunction.h"
#include "MApp_XC_PQ.h"
#include "mapp_mplayer.h"
#if MHEG5_ENABLE
#include "MApp_MHEG5_Main.h"
#endif
#if ENABLE_PVR
#include "MApp_PVR.h"
#include "MApp_TimeShift.h"
#endif

#if (ENABLE_PIP)
#include "MApp_PIP.h"
#endif

//-------------------------------------------------------------------------------------------------
//  Driver Compiler Options
//-------------------------------------------------------------------------------------------------

#define NEW_AFD_FORMULA     1
#define KEEP_SCALING_RATIO  0

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------

#define AFD_MSG(x)  //x

//-------------------------------------------------------------------------------------------------
//  Local Structurs
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------

BOOLEAN _msAPI_Picture_Adjust_MVD4x3Setting(U8 u8stAFD, MS_WINDOW_TYPE *pstCropWin, MS_WINDOW_TYPE *pstDstWin)
{

    U16                 u16SrcHeight,
                        u16SrcWidth;
    U16                 u16HCapStart,
                        u16HCapSize;
    U16                 u16VCapStart,
                        u16VCapSize;
    U16                 u16HDispStart,
                        u16HDispSize;
    U16                 u16VDispStart,
                        u16VDispSize;
    BOOLEAN             bPanelAR16x9=FALSE;


    if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
    {
        if ( ((U32)(g_IPanel.Height()) * 16) > ((U32)(g_IPanel.Width()) * 9) )
        {
            if ( (((U32)(g_IPanel.Height()) * 16) - ((U32)(g_IPanel.Width()) * 9)) > ((U32)(g_IPanel.Width()) / 2) )
            {
                bPanelAR16x9 = FALSE;
            }
            else
            {
                bPanelAR16x9 = TRUE;
            }
        }
        else
        {
            bPanelAR16x9 = TRUE;
        }
    }


    {
        u16SrcWidth  = pstCropWin->width;
        u16SrcHeight = pstCropWin->height;
        u16HCapStart = 0;
        u16HCapSize = u16SrcWidth;
        u16VCapStart = 0;
        u16VCapSize = u16SrcHeight;
        u16HDispStart = 0;
        u16HDispSize = pstDstWin->width;
        u16VDispStart = 0;
        u16VDispSize = pstDstWin->height;
    }


    AFD_MSG(printf("u16H_CapStart = %04d, u16H_CapSize = %04d\n", u16HCapStart, u16HCapSize));
    AFD_MSG(printf("u16V_CapStart = %04d, u16V_CapSize = %04d\n", u16VCapStart,u16VCapSize));
    AFD_MSG(printf("u16H_DisStart = %04d, u16H_DisSize = %04d\n", u16HDispStart, u16HDispSize));
    AFD_MSG(printf("u16V_DisStart = %04d, u16V_DisSize = %04d\n\n", u16VDispStart, u16VDispSize));

    #if (NEW_AFD_FORMULA)

    switch ( u8stAFD )
    {
        case E_MVD_AFD_BOX_16X9_TOP:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
            }
            break;
        case E_MVD_AFD_BOX_14X9_TOP:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
            }
            break;
        case E_MVD_AFD_BOX_16X9:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
            }
            break;
        case E_MVD_AFD_FULL_FRAME:
        case E_MVD_AFD_CENTRE_4x3:
            if ( PANEL_ASPECT_RATIO == E_PNL_ASPECT_RATIO_4_3 )
            {
                // 4:3 or full frame video on 4:3 panel, don't clip source and destination rectangle.
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
                // 4:3 or full frame video on 16:9 panel, clip destination rectangle (pillarbox)
                //u16HDispSize = g_IPanel.Width() * 12 / 16;
                u16HDispSize = g_IPanel.Height() * 12 / 9;
                u16HDispSize = ( u16HDispSize >> 1 ) << 1;
                u16HDispStart = ( ( g_IPanel.Width() - u16HDispSize ) >> 2 ) << 1;

            }
            break;
        case E_MVD_AFD_CENTRE_16X9:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
                // Clip source rectangle (vertical)
                u16VCapSize = u16SrcHeight * 9 / 12;
                u16VCapSize = ( u16VCapSize >> 1 ) << 1;
                u16VCapStart = ( ( u16SrcHeight - u16VCapSize ) >> 2 ) << 1;
            }
            break;
        case E_MVD_AFD_CENTRE_14X9:
        case E_MVD_AFD_CENTRE_4X3_14X9:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
                // 14:9 video on 4:3 panel, don't clip source and destination rectangle.
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
                // 14:9 video on 16:9 panel, clip source rectangle (letterbox) and desination rectangle (pillarbox).
                // Clip source rectangle (vertical)
                u16VCapSize = u16SrcHeight * 18 / 21;
                u16VCapSize = ( u16VCapSize >> 1 ) << 1;
                u16VCapStart = ( ( u16SrcHeight - u16VCapSize ) >> 2 ) << 1;
                // Fine tune for DTG AFD test
                //u16VCapStart = ( (u16SrcHeight - u16VCapSize + 0xF) & ~0xF ) >> 1;

                //Clip destination rectangle (horizontal)
                //u16HDispSize = g_IPanel.Width() * 14 / 16;
                u16HDispSize = g_IPanel.Height() * 14 / 9;
                u16HDispSize = ( u16HDispSize >> 1 ) << 1;
                u16HDispStart = ( ( g_IPanel.Width() - u16HDispSize ) >> 2 ) << 1;
            }
            break;
        case E_MVD_AFD_CENTRE_16X9_14X9:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
                // Case 1, don't clip source and destination rectangle.

                // Case 2, keep 14:9 shoot and protect, clip source rectangle
                // Clip source rectangle (vertical & horinontal)
                u16HCapSize = u16SrcWidth * 14 / 16;
                u16HCapSize = ( u16HCapSize >> 1 ) << 1;
                u16HCapStart = ( ( u16SrcWidth - u16HCapSize ) >> 2 ) << 1;
                u16VCapSize = u16SrcHeight * 14 / 16;
                u16VCapSize = ( u16VCapSize >> 1 ) << 1;
                u16VCapStart = ( ( u16SrcHeight - u16VCapSize ) >> 2 ) << 1;
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
                // 16:9 video on 16:9 panel, clip source rectangle (letterbox).
                // Clip source rectangle (vertical)
                u16VCapSize = u16SrcHeight * 12 / 16;
                u16VCapSize = ( u16VCapSize >> 1 ) << 1;
                u16VCapStart = ( ( u16SrcHeight - u16VCapSize ) >> 2 ) << 1;

                if ( bPanelAR16x9 == FALSE )
                {
                    u16HCapSize = (U16)( (U32)u16VCapSize *  g_IPanel.Width() / g_IPanel.Height() );
                    u16HCapSize = ( u16HCapSize >> 1 ) << 1;
                    u16HCapStart = ( ( u16SrcWidth - u16HCapSize ) >> 2 ) << 1;
                }
            }
            break;
        case E_MVD_AFD_CENTRE_16X9_4X3:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
                // Case 1, don't clip source and destination rectangle.

                // Case 2, keep 4:3 shoot and protect, clip source rectangle
                // Clip source rectangle (horizontal & vertical)
                u16VCapSize = u16SrcHeight * 12 / 16;
                u16VCapSize = ( u16VCapSize >> 1 ) << 1;
                u16VCapStart = ( ( u16SrcHeight - u16VCapSize ) >> 2 ) << 1;

                u16HCapSize = u16SrcWidth * 12 / 16;
                u16HCapSize = ( u16HCapSize >> 1 ) << 1;
                u16HCapStart = ( ( u16SrcWidth - u16HCapSize ) >> 2 ) << 1;
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
                // 16:9 video on 16:9 panel, clip source rectangle (letterbox).
                // Clip source rectangle (vertical)
                u16VCapSize = u16SrcHeight * 12 / 16;
                u16VCapSize = ( u16VCapSize >> 1 ) << 1;
                u16VCapStart = ( ( u16SrcHeight - u16VCapSize ) >> 2 ) << 1;

                if ( bPanelAR16x9 == FALSE )
                {
                    u16HCapSize = (U16)( (U32)u16VCapSize *  g_IPanel.Width() / g_IPanel.Height() );
                    u16HCapSize = ( u16HCapSize >> 1 ) << 1;
                    u16HCapStart = ( ( u16SrcWidth - u16HCapSize ) >> 2 ) << 1;
                }
            }
            break;
        default:
            break;
    }

    #else

    switch (u8stAFD)
    {
        case E_MVD_AFD_BOX_16X9_TOP:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
            }
            break;
        case E_MVD_AFD_BOX_14X9_TOP:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
            }
            break;
        case E_MVD_AFD_BOX_16X9:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
            }
            break;
        case E_MVD_AFD_FULL_FRAME:
        case E_MVD_AFD_CENTRE_4x3:
            if ( PANEL_ASPECT_RATIO == E_PNL_ASPECT_RATIO_4_3 )
            {
                // 4:3 or full frame video on 4:3 panel, don't clip source and destination rectangle.
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
                // 4:3 or full frame video on 16:9 panel, clip destination rectangle (pillarbox)
                u16HDispSize = g_IPanel.Width()*12/16;
                u16HDispSize = (u16HDispSize>>1)<<1;
                u16HDispStart = ((g_IPanel.Width() - u16HDispSize)>>2)<<1;
            }
            break;
        case E_MVD_AFD_CENTRE_16X9:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
                // Clip source rectangle (vertical)
                u16VCapSize = u16SrcHeight*9/12;
                u16VCapSize = (u16VCapSize>>1)<<1;
                u16VCapStart = ((u16SrcHeight - u16VCapSize)>>2)<<1;
            }
            break;
        case E_MVD_AFD_CENTRE_14X9:
        case E_MVD_AFD_CENTRE_4X3_14X9:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
                // 14:9 video on 4:3 panel, don't clip source and destination rectangle.
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
                // 14:9 video on 16:9 panel, clip source rectangle (letterbox) and desination rectangle (pillarbox).
                // Clip source rectangle (vertical)
                u16VCapSize = u16SrcHeight*18/21;
                u16VCapSize = (u16VCapSize>>1)<<1;
                u16VCapStart = ((u16SrcHeight - u16VCapSize)>>2)<<1;

                //Clip destination rectangle (horizontal)
                u16HDispSize = g_IPanel.Width()*14/16;
                u16HDispSize = (u16HDispSize>>1)<<1;
                u16HDispStart = ((g_IPanel.Width() - u16HDispSize)>>2)<<1;
            }
            break;
        case E_MVD_AFD_CENTRE_16X9_14X9:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
                // Case 1, don't clip source and destination rectangle.

                // Case 2, keep 14:9 shoot and protect, clip source rectangle
                // Clip source rectangle (vertical & horinontal)
                u16HCapSize = u16SrcWidth*14/16;
                u16HCapSize = (u16HCapSize>>1)<<1;
                u16HCapStart = ((u16SrcWidth - u16HCapSize)>>2)<<1;
                u16VCapSize = u16SrcHeight*14/16;
                u16VCapSize = (u16VCapSize>>1)<<1;
                u16VCapStart = ((u16SrcHeight - u16VCapSize)>>2)<<1;
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
                // 16:9 video on 16:9 panel, clip source rectangle (letterbox).
                // Clip source rectangle (vertical)
                u16VCapSize = u16SrcHeight*12/16;
                u16VCapSize = (u16VCapSize>>1)<<1;
                u16VCapStart = ((u16SrcHeight - u16VCapSize)>>2)<<1;
            }
            break;
        case E_MVD_AFD_CENTRE_16X9_4X3:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
                // Case 1, don't clip source and destination rectangle.

                // Case 2, keep 4:3 shoot and protect, clip source rectangle
                // Clip source rectangle (horizontal & vertical)
                u16VCapSize = u16SrcHeight*12/16;
                u16VCapSize = (u16VCapSize>>1)<<1;
                u16VCapStart = ((u16SrcHeight - u16VCapSize)>>2)<<1;

                u16HCapSize = u16SrcWidth*12/16;
                u16HCapSize = (u16HCapSize>>1)<<1;
                u16HCapStart = ((u16SrcWidth - u16HCapSize)>>2)<<1;
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
                // 16:9 video on 16:9 panel, clip source rectangle (letterbox).
                // Clip source rectangle (vertical)
                u16VCapSize = u16SrcHeight*12/16;
                u16VCapSize = (u16VCapSize>>1)<<1;
                u16VCapStart = ((u16SrcHeight - u16VCapSize)>>2)<<1;
            }
            break;
        default:
            break;
    }

    #endif


    AFD_MSG(printf("u16H_CapStart = %04d, u16H_CapSize = %04d\n", u16HCapStart, u16HCapSize));
    AFD_MSG(printf("u16V_CapStart = %04d, u16V_CapSize = %04d\n", u16VCapStart,u16VCapSize));
    AFD_MSG(printf("u16H_DisStart = %04d, u16H_DisSize = %04d\n", u16HDispStart, u16HDispSize));
    AFD_MSG(printf("u16V_DisStart = %04d, u16V_DisSize = %04d\n", u16VDispStart, u16VDispSize));


    {
        pstCropWin->x += u16HCapStart;
        pstCropWin->y += u16VCapStart;
        pstCropWin->width=u16HCapSize;
        pstCropWin->height=u16VCapSize;

        pstDstWin->x += u16HDispStart;
        pstDstWin->y += u16VDispStart;
        pstDstWin->width =u16HDispSize;
        pstDstWin->height=u16VDispSize;
    }

    return TRUE;
}

BOOLEAN  _msAPI_Picture_Adjust_MVD16x9Setting(U8 u8stAFD, MS_WINDOW_TYPE *pstCropWin, MS_WINDOW_TYPE *pstDstWin)
{
    U16                 u16SrcHeight,
                        u16SrcWidth;
    U16                 u16HCapStart,
                        u16HCapSize;
    U16                 u16VCapStart,
                        u16VCapSize;
    U16                 u16HDispStart,
                        u16HDispSize;
    U16                 u16VDispStart,
                        u16VDispSize;
    BOOLEAN             bPanelAR16x9;

    if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
    {
        if ( ((U32)(g_IPanel.Height()) * 16) > ((U32)(g_IPanel.Width()) * 9) )
        {
            if ( (((U32)(g_IPanel.Height()) * 16) - ((U32)(g_IPanel.Width()) * 9)) > ((U32)(g_IPanel.Width()) / 2) )
            {
                bPanelAR16x9 = FALSE;
            }
            else
            {
                bPanelAR16x9 = TRUE;
            }
        }
        else
        {
            bPanelAR16x9 = TRUE;
        }
    }


    {
        u16SrcWidth  = pstCropWin->width;
        u16SrcHeight = pstCropWin->height;
        u16HCapStart = 0;
        u16HCapSize = u16SrcWidth;
        u16VCapStart = 0;
        u16VCapSize = u16SrcHeight;
        u16HDispStart = 0;
        u16HDispSize = pstDstWin->width;
        u16VDispStart = 0;
        u16VDispSize = pstDstWin->height;
    }




#if (NEW_AFD_FORMULA)

    switch ( u8stAFD )
    {
        case E_MVD_AFD_BOX_16X9_TOP:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
            }
            break;
        case E_MVD_AFD_BOX_14X9_TOP:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
            }
            break;
        case E_MVD_AFD_BOX_16X9:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
            }
            break;
        case E_MVD_AFD_FULL_FRAME:
        case E_MVD_AFD_CENTRE_16X9:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
                if ( bPanelAR16x9 == FALSE )
                {
                    #if KEEP_SCALING_RATIO
                    u16HCapSize = (U16)( (U32)u16HCapSize *  g_IPanel.Width() * 9 / (g_IPanel.Height() * 16) );

                    u16HCapSize = ( u16HCapSize >> 1 ) << 1;
                    u16HCapStart = ( ( u16SrcWidth - u16HCapSize ) >> 2 ) << 1;
                    #endif
                }
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
                //Clip destination rectangle (vertical)
                u16VDispSize = g_IPanel.Height() * 9 / 12;
                u16VDispSize = ( u16VDispSize >> 1 ) << 1;
                u16VDispStart = ( ( g_IPanel.Height() - u16VDispSize ) >> 2 ) << 1;
            }
            break;
        case E_MVD_AFD_CENTRE_4x3:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
                //Clip source rectangle (horizontal).
                u16HCapSize = u16SrcWidth * 12 / 16;
                u16HCapSize = ( u16HCapSize >> 1 ) << 1;
                u16HCapStart = ( ( u16SrcWidth - u16HCapSize ) >> 2 ) << 1;

                //Clip destination rectangle (horizontal).
                //u16HDispSize = g_IPanel.Width() * 12 / 16;
                u16HDispSize = g_IPanel.Height() * 12 / 9;
                u16HDispSize = ( u16HDispSize >> 1 ) << 1;
                u16HDispStart = ( ( g_IPanel.Width() - u16HDispSize ) >> 2 ) << 1;
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
                //Clip source rectangle.
                u16HCapSize = u16SrcWidth * 12 / 16;
                u16HCapSize = ( u16HCapSize >> 1 ) << 1;
                u16HCapStart = ( ( u16SrcWidth - u16HCapSize ) >> 2 ) << 1;
            }
            break;
        case E_MVD_AFD_CENTRE_14X9:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
                if ( bPanelAR16x9 == FALSE )
                {
                    #if KEEP_SCALING_RATIO
                    u16HCapSize = (U16)( (U32)u16HCapSize *  g_IPanel.Width() * 9 / (g_IPanel.Height() * 16) );

                    u16HCapSize = ( u16HCapSize >> 1 ) << 1;
                    u16HCapStart = ( ( u16SrcWidth - u16HCapSize ) >> 2 ) << 1;
                    #endif
                }
            }
            else if ( PANEL_ASPECT_RATIO == E_PNL_ASPECT_RATIO_4_3 )
            {
                // Clip source rectangle (horizontal).
                u16HCapSize = u16SrcWidth * 14 / 16;
                u16HCapSize = ( u16HCapSize >> 1 ) << 1;
                u16HCapStart = ( ( u16SrcWidth - u16HCapSize ) >> 2 ) << 1;

                // Clip destination rectangle (vertical).
                u16VDispSize = g_IPanel.Height() * 18 / 21;
                u16VDispSize = ( u16VDispSize >> 1 ) << 1;
                u16VDispStart = ( ( g_IPanel.Height() - u16VDispSize ) >> 2 ) << 1;
            }
            break;
        case E_MVD_AFD_CENTRE_4X3_14X9:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
                // Clip source rectangle (horizontal & vertical)
                u16HCapSize = u16SrcWidth * 12 / 16;
                u16HCapSize = ( u16HCapSize >> 1 ) << 1;
                u16HCapStart = ( ( u16SrcWidth - u16HCapSize ) >> 2 ) << 1;
                u16VCapSize = u16SrcHeight * 18 / 21;
                u16VCapSize = ( u16VCapSize >> 1 ) << 1;
                u16VCapStart = ( ( u16SrcHeight - u16VCapSize ) >> 2 ) << 1;
                // Fine tune for DTG AFD test
                //u16VCapStart = ( (u16SrcHeight - u16VCapSize + 0xF) & ~0xF ) >> 1;

                //Clip Destination rectangle (horizontal)
                //u16HDispSize = g_IPanel.Width() * 14 / 16;
                u16HDispSize = g_IPanel.Height() * 14 / 9;
                u16HDispSize = ( u16HDispSize >> 1 ) << 1;
                u16HDispStart = ( ( g_IPanel.Width() - u16HDispSize ) >> 2 ) << 1;
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
                // Clip source rectangle (horizontal)
                u16HCapSize = u16SrcWidth * 12 / 16;
                u16HCapSize = ( u16HCapSize >> 1 ) << 1;
                u16HCapStart = ( ( u16SrcWidth - u16HCapSize ) >> 2 ) << 1;
            }
            break;
        case E_MVD_AFD_CENTRE_16X9_14X9:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
                if ( bPanelAR16x9 == FALSE )
                {
                    #if KEEP_SCALING_RATIO
                    u16HCapSize = (U16)( (U32)u16HCapSize *  g_IPanel.Width() * 9 / (g_IPanel.Height() * 16) );

                    u16HCapSize = ( u16HCapSize >> 1 ) << 1;
                    u16HCapStart = ( ( u16SrcWidth - u16HCapSize ) >> 2 ) << 1;
                    #endif
                }
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
                //Clip Source rectangle (horizontal)
                u16HCapSize = u16SrcWidth * 14 / 16;
                u16HCapSize = ( u16HCapSize >> 1 ) << 1;
                u16HCapStart = ( ( u16SrcWidth - u16HCapSize ) >> 2 ) << 1;

                //Clip Destination rectangle (vertical)
                u16VDispSize = g_IPanel.Height() * 18 / 21;
                u16VDispSize = ( u16VDispSize >> 1 ) << 1;
                u16VDispStart = ( ( g_IPanel.Height() - u16VDispSize ) >> 2 ) << 1;
            }
            break;
        case E_MVD_AFD_CENTRE_16X9_4X3:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
                if ( bPanelAR16x9 == FALSE )
                {
                    #if KEEP_SCALING_RATIO
                    u16HCapSize = (U16)( (U32)u16HCapSize *  g_IPanel.Width() * 9 / (g_IPanel.Height() * 16) );

                    u16HCapSize = ( u16HCapSize >> 1 ) << 1;
                    u16HCapStart = ( ( u16SrcWidth - u16HCapSize ) >> 2 ) << 1;
                    #endif
                }
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
                //Clip Destination rectangle
                u16VDispSize = g_IPanel.Height() * 9 / 12;
                u16VDispSize = ( u16VDispSize >> 1 ) << 1;
                u16VDispStart = ( ( g_IPanel.Height() - u16VDispSize ) >> 2 ) << 1;
            }
            break;
        default:
            break;
    }

#else

    switch (u8stAFD)
    {
        case E_MVD_AFD_BOX_16X9_TOP:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
            }
            break;
        case E_MVD_AFD_BOX_14X9_TOP:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
            }
            break;
        case E_MVD_AFD_BOX_16X9:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
            }
            break;
        case E_MVD_AFD_FULL_FRAME:
        case E_MVD_AFD_CENTRE_16X9:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
                //Clip destination rectangle (vertical)
                u16VDispSize = g_IPanel.Height()*9/12;
                u16VDispSize = (u16VDispSize>>1)<<1;
                u16VDispStart = ((g_IPanel.Height() - u16VDispSize)>>2)<<1;
            }
            break;
        case E_MVD_AFD_CENTRE_4x3:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
                //Clip source rectangle (horizontal).
                u16HCapSize = u16SrcWidth*12/16;
                u16HCapSize = (u16HCapSize>>1)<<1;
                u16HCapStart = ((u16SrcWidth - u16HCapSize)>>2)<<1;

                //Clip destination rectangle (horizontal).
                u16HDispSize = g_IPanel.Width()*12/16;
                u16HDispSize = (u16HDispSize>>1)<<1;
                u16HDispStart = ((g_IPanel.Width() - u16HDispSize)>>2)<<1;
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
                //Clip source rectangle.
                u16HCapSize = u16SrcWidth*12/16;
                u16HCapSize = (u16HCapSize>>1)<<1;
                u16HCapStart = ((u16SrcWidth - u16HCapSize)>>2)<<1;
            }
            break;
        case E_MVD_AFD_CENTRE_14X9:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
                // Don't clip source and destination rectangle.
            }
            else if ( PANEL_ASPECT_RATIO == E_PNL_ASPECT_RATIO_4_3 )
            {
                // Clip source rectangle (horizontal).
                u16HCapSize = u16SrcWidth*14/16;
                u16HCapSize = (u16HCapSize>>1)<<1;
                u16HCapStart = ((u16SrcWidth - u16HCapSize)>>2)<<1;

                // Clip destination rectangle (vertical).
                u16VDispSize = g_IPanel.Height()*18/21;
                u16VDispSize = (u16VDispSize>>1)<<1;
                u16VDispStart = ((g_IPanel.Height() - u16VDispSize)>>2)<<1;
            }
            break;
        case E_MVD_AFD_CENTRE_4X3_14X9:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
                // Clip source rectangle (horizontal & vertical)
                u16HCapSize = u16SrcWidth*12/16;
                u16HCapSize = (u16HCapSize>>1)<<1;
                u16HCapStart = ((u16SrcWidth - u16HCapSize)>>2)<<1;
                u16VCapSize = u16SrcHeight*18/21;
                u16VCapSize = (u16VCapSize>>1)<<1;
                u16VCapStart = ((u16SrcHeight - u16VCapSize)>>2)<<1;

                //Clip Destination rectangle (horizontal)
                u16HDispSize = g_IPanel.Width()*14/16;
                u16HDispSize = (u16HDispSize>>1)<<1;
                u16HDispStart = ((g_IPanel.Width() - u16HDispSize)>>2)<<1;
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
                // Clip source rectangle (horizontal)
                u16HCapSize = u16SrcWidth*12/16;
                u16HCapSize = (u16HCapSize>>1)<<1;
                u16HCapStart = ((u16SrcWidth - u16HCapSize)>>2)<<1;
            }
            break;
        case E_MVD_AFD_CENTRE_16X9_14X9:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
                //Clip Source rectangle (horizontal)
                u16HCapSize = u16SrcWidth*14/16;
                u16HCapSize = (u16HCapSize>>1)<<1;
                u16HCapStart = ((u16SrcWidth - u16HCapSize)>>2)<<1;

                //Clip Destination rectangle (vertical)
                u16VDispSize = g_IPanel.Height()*18/21;
                u16VDispSize = (u16VDispSize>>1)<<1;
                u16VDispStart = ((g_IPanel.Height() - u16VDispSize)>>2)<<1;
            }
            break;
        case E_MVD_AFD_CENTRE_16X9_4X3:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
            }
            else if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_4_3 )
            {
                //Clip Destination rectangle
                u16VDispSize = g_IPanel.Height()*9/12;
                u16VDispSize = (u16VDispSize>>1)<<1;
                u16VDispStart = ((g_IPanel.Height() - u16VDispSize)>>2)<<1;
            }
            break;
        default:
            break;
    }

#endif


    AFD_MSG(printf("u16H_CapStart = %04d, u16H_CapSize = %04d\n", u16HCapStart, u16HCapSize));
    AFD_MSG(printf("u16V_CapStart = %04d, u16V_CapSize = %04d\n", u16VCapStart,u16VCapSize));
    AFD_MSG(printf("u16H_DisStart = %04d, u16H_DisSize = %04d\n", u16HDispStart, u16HDispSize));
    AFD_MSG(printf("u16V_DisStart = %04d, u16V_DisSize = %04d\n\n", u16VDispStart, u16VDispSize));


    {
        pstCropWin->x += u16HCapStart;
        pstCropWin->y += u16VCapStart;
        pstCropWin->width=u16HCapSize;
        pstCropWin->height=u16VCapSize;

        pstDstWin->x += u16HDispStart;
        pstDstWin->y += u16VDispStart;
        pstDstWin->width =u16HDispSize;
        pstDstWin->height=u16VDispSize;
    }

    return TRUE;
}

static U16 _H264_ASPECT_RATIO[17][2]   =      {{1,1},
                                               {1,1},
                                               {12,11},
                                               {10,11},
                                               {16,11},
                                               {40,33},
                                               {24,11},
                                               {20,11},
                                               {32,11},
                                               {80,33},
                                               {18,11},
                                               {15,11},
                                               {64,33},
                                               {160,99},
                                               {4,3},
                                               {3,2},
                                               {2,1}};

BOOLEAN _msAPI_Picture_AdjustWidth_CutByHeight(SRC_RATIO_INFO *pstSrcRatioInfo, MS_WINDOW_TYPE *pstSrcWin,  MS_WINDOW_TYPE *pstDstWin)
{
    U32 u16Temp;
    U32 WR=pstSrcRatioInfo->u32SarWidth,HR=pstSrcRatioInfo->u32SarHeight;
    U8 u8DivideRatio=1;


    //printf("[VidSta] H/V: %u, %u\n", pstSrcRatioInfo->u16VideoWidth, pstSrcRatioInfo->u16VideoHeight);
    //printf("[SrcWin] H/V: %u, %u\n", pstSrcWin->width, pstSrcWin->height);
    //printf("[DstWin] H/V: %u, %u\n", pstDstWin->width, pstDstWin->height);

    //printf("_msAPI_Picture_AdjustWidth_CutByHeight:%u* %u > %u*%u\n",pstDstWin->height,WR  , pstDstWin->width,HR);
    //if(((U32)WR*pstDstWin->height) > ((U32)HR*pstDstWin->width))
    if(MDrv_MVOP_GetIsHDuplicate())
        u8DivideRatio=2;
    if(((U32)pstSrcWin->width*WR*pstDstWin->height/u8DivideRatio) > ((U32)pstSrcWin->height*HR*pstDstWin->width))
    {
        AFD_MSG(printf("AdjustWidth:%u,%u\n",pstSrcWin->x,pstSrcWin->width));
        u16Temp = pstSrcWin->width;
        //pstSrcWin->width = (((U32)HR * pstSrcWin->width * pstDstWin->width) /  ((U32)WR * pstDstWin->height) );
        pstSrcWin->width = (((U32)pstSrcWin->height*HR*pstDstWin->width) /  ((U32)(WR*pstDstWin->height)/u8DivideRatio) );

        pstSrcWin->x += (u16Temp - pstSrcWin->width)/2;
//        printf("pstSrcWinx:%u,width:%u\n",pstSrcWin->x,pstSrcWin->width);
//        printf("==============================\n");
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}
BOOLEAN _msAPI_Picture_AdjustHeight_CutByWidth(SRC_RATIO_INFO *pstSrcRatioInfo, MS_WINDOW_TYPE *pstSrcWin,  MS_WINDOW_TYPE *pstDstWin)
{
    U16 u16Temp;
    U32 WR=pstSrcRatioInfo->u32SarWidth,HR=pstSrcRatioInfo->u32SarHeight;
    U8 u8DivideRatio=1;

    if(MDrv_MVOP_GetIsHDuplicate())
        u8DivideRatio=2;

    //printf("_msAPI_Picture_AdjustHeight_CutByWidth:%u*%u > %u,%u\n",HR,pstDstWin->width , pstDstWin->height,WR);
    //if( HR/WR > pstDstWin->height/pstDstWin->width )
    //if( ((U32)HR*pstDstWin->width) > ((U32)WR*pstDstWin->height) )
    if( ((U32)pstSrcWin->height*HR*pstDstWin->width) > (((U32)pstSrcWin->width*WR*pstDstWin->height)/u8DivideRatio) )
    {
        //printf("AdjustHeight :%u,height:%u:\n",pstSrcWin->y,pstSrcWin->height);
        u16Temp = pstSrcWin->height;
        //pstSrcWin->height = (((U32)WR*pstSrcWin->height*pstDstWin->height) / ((U32)HR*pstDstWin->width));
        pstSrcWin->height = ((((U32)pstSrcWin->width*WR*pstDstWin->height)/u8DivideRatio) / ((U32)HR*pstDstWin->width));
        pstSrcWin->y += (u16Temp - pstSrcWin->height)/2;
//        printf("pstSrcWiny:%u,height:%u\n",pstSrcWin->y,pstSrcWin->height);
//        printf("==============================\n");

        return TRUE;
    }
    else
    {
        return FALSE;
    }

}

BOOLEAN  _msAPI_Picture_Adjust_AFDSourceWindow(SRC_RATIO_INFO *pstSrcRatioInfo,
                                               MS_WINDOW_TYPE *pstCropWin,
                                               MS_WINDOW_TYPE *pstDstWin)
{
    U16     u16SrcHeight,u16SrcWidth;
    U16     u16HCapStart,u16HCapSize;
    U16     u16VCapStart,u16VCapSize;
    BOOLEAN ret = FALSE;
    MS_WINDOW_TYPE tDstWin;

    U8 u8AspectRate     = pstSrcRatioInfo->u8AspectRate;
    U8 u8stAFD          = pstSrcRatioInfo->u8AFD;

    u16SrcWidth  = pstCropWin->width;
    u16SrcHeight = pstCropWin->height;
    u16HCapStart = 0;
    u16HCapSize = u16SrcWidth;
    u16VCapStart = 0;
    u16VCapSize = u16SrcHeight;


    //printf("_msAPI_Picture_Adjust_AFDSourceWindow:%bx,%bx\n",u8AspectRate,u8stAFD);
    switch ( u8stAFD )
    {
        case E_MVD_AFD_FULL_FRAME:

            if(u8AspectRate == MVD_ASP_4TO3)
            {
            }
            else if(u8AspectRate == MVD_ASP_16TO9)
            {
            }
            ret = _msAPI_Picture_AdjustWidth_CutByHeight(pstSrcRatioInfo,pstCropWin,pstDstWin);

            break;

        case E_MVD_AFD_CENTRE_4x3:
            if(u8AspectRate == MVD_ASP_4TO3)
            {

            }
            else if(u8AspectRate == MVD_ASP_16TO9)
            {
#if ENABLE_AFD_FOR_SGP_MDA
                tDstWin.width = 4;
                tDstWin.height = 3;
                ret = _msAPI_Picture_AdjustWidth_CutByHeight(pstSrcRatioInfo,pstCropWin,&tDstWin);
#endif
            }

#if (PANEL_16_10 == DISABLE)
            ret = _msAPI_Picture_AdjustWidth_CutByHeight(pstSrcRatioInfo,pstCropWin,pstDstWin);
#endif

            break;
        case E_MVD_AFD_CENTRE_16X9:
            if(u8AspectRate == MVD_ASP_4TO3)
            {
                tDstWin.width = 16;
                tDstWin.height = 9;
                //source clip to 16x9 first
                _msAPI_Picture_AdjustHeight_CutByWidth(pstSrcRatioInfo,pstCropWin,&tDstWin);
            }
            else if(u8AspectRate == MVD_ASP_16TO9)
            {
                //Don't Clip source
            }
            ret = _msAPI_Picture_AdjustWidth_CutByHeight(pstSrcRatioInfo,pstCropWin,pstDstWin);
            break;

        case E_MVD_AFD_CENTRE_14X9:

            tDstWin.width = 14;
            tDstWin.height = 9;

            if(u8AspectRate == MVD_ASP_4TO3)
            {
                ret = _msAPI_Picture_AdjustHeight_CutByWidth(pstSrcRatioInfo,pstCropWin,&tDstWin);
            }
            else if(u8AspectRate == MVD_ASP_16TO9)
            {
                //ret = _msAPI_Picture_AdjustWidth_CutByHeight(pstSrcRatioInfo,pstCropWin,&tDstWin);
            }

            ret = _msAPI_Picture_AdjustWidth_CutByHeight(pstSrcRatioInfo,pstCropWin,pstDstWin);

            break;
        case E_MVD_AFD_CENTRE_4X3_14X9:
            if(u8AspectRate == MVD_ASP_4TO3)
            {
            //    ret = _msAPI_Picture_AdjustHeight_CutByWidth(pstSrcRatioInfo,pstCropWin,pstDstWin);
            }
            else
            if(u8AspectRate == MVD_ASP_16TO9)
            {
                //MS_WINDOW_TYPE tDstWin;
                tDstWin.width = 4;
                tDstWin.height = 3;
                //source clip to 4x3 first
                _msAPI_Picture_AdjustWidth_CutByHeight(pstSrcRatioInfo,pstCropWin,&tDstWin);

            }
            ret = _msAPI_Picture_AdjustHeight_CutByWidth(pstSrcRatioInfo,pstCropWin,pstDstWin);

            break;

        case E_MVD_AFD_CENTRE_16X9_14X9:
            if(u8AspectRate == MVD_ASP_4TO3)
            {
                tDstWin.width = 16;
                tDstWin.height = 9;
                //source clip to 16x9 first
                _msAPI_Picture_AdjustHeight_CutByWidth(pstSrcRatioInfo,pstCropWin,&tDstWin);

                //ret = _msAPI_Picture_AdjustWidth_CutByHeight(pstSrcRatioInfo,pstCropWin,pstDstWin);
            }
            else if(u8AspectRate == MVD_ASP_16TO9)
            {
            }
            ret = _msAPI_Picture_AdjustWidth_CutByHeight(pstSrcRatioInfo,pstCropWin,pstDstWin);

            break;
        case E_MVD_AFD_CENTRE_16X9_4X3:
            if(u8AspectRate == MVD_ASP_4TO3)
            {
                tDstWin.width = 16;
                tDstWin.height = 9;
                //source clip to 16x9 first
                _msAPI_Picture_AdjustHeight_CutByWidth(pstSrcRatioInfo,pstCropWin,&tDstWin);

            }
            else if(u8AspectRate == MVD_ASP_16TO9)
            {

            }

            ret = _msAPI_Picture_AdjustWidth_CutByHeight(pstSrcRatioInfo,pstCropWin,pstDstWin);


            break;
        default:
            break;
    }
    return ret;
}

void  _msAPI_Picture_Adjust_AFDDisplayWindow(SRC_RATIO_INFO *pstSrcRatioInfo, MS_WINDOW_TYPE *pstDstWin)
{
    U16                 u16HDispStart,
                        u16HDispSize;
    U16                 u16VDispStart,
                        u16VDispSize;
//    BOOLEAN             bPanelAR16x9;
    U8 u8AspectRate     = pstSrcRatioInfo->u8AspectRate;
    U8 u8stAFD          = pstSrcRatioInfo->u8AFD;

    {
        u16HDispStart = 0;
        u16HDispSize = pstDstWin->width;
        u16VDispStart = 0;
        u16VDispSize = pstDstWin->height;
    }

    AFD_MSG(printf("_msAPI_Picture_Adjust_AFDDisplayWindow\n"));
/*
    if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
    {
        if ( ((U32)(g_IPanel.Height()) * 16) > ((U32)(g_IPanel.Width()) * 9) )
        {
            if ( (((U32)(g_IPanel.Height()) * 16) - ((U32)(g_IPanel.Width()) * 9)) > ((U32)(g_IPanel.Width()) / 2) )
            {
                bPanelAR16x9 = FALSE;
            }
            else
            {
                bPanelAR16x9 = TRUE;
            }
        }
        else
        {
            bPanelAR16x9 = TRUE;
        }
    }
*/
    switch ( u8stAFD )
    {
        case E_MVD_AFD_UNKNOWN:
        case E_MVD_AFD_FULL_FRAME:


            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE &&
                (u8AspectRate ==MVD_ASP_4TO3) )
            {
                u16HDispSize = pstDstWin->height* 12 / 9;
                u16HDispSize = ( u16HDispSize >> 1 ) << 1;
                u16HDispStart = ( ( pstDstWin->width - u16HDispSize ) >> 2 ) << 1;
            }
#if (PANEL_16_10 == ENABLE)
            else if(u8AspectRate ==MVD_ASP_16TO9)
            {
                u16VDispSize = pstDstWin->height* 9 / 10;
                u16VDispSize = ( u16VDispSize >> 1 ) << 1;
                u16VDispStart = ( ( pstDstWin->height - u16VDispSize ) >> 2 ) << 1;
            }
#endif
            break;
        case E_MVD_AFD_CENTRE_4x3:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE)
            {
#if !ENABLE_AFD_FOR_SGP_MDA
                if (u8AspectRate ==MVD_ASP_4TO3)
#endif
                {
                    u16HDispSize = pstDstWin->height* 12 / 9;
                    u16HDispSize = ( u16HDispSize >> 1 ) << 1;
                    u16HDispStart = ( ( pstDstWin->width - u16HDispSize ) >> 2 ) << 1;
                }
            }
#if (PANEL_16_10 == ENABLE)
            break;
#endif
        case E_MVD_AFD_CENTRE_16X9:
#if (PANEL_16_10 == ENABLE)
            {
                u16VDispSize = pstDstWin->height* 9 / 10;
                u16VDispSize = ( u16VDispSize >> 1 ) << 1;
                u16VDispStart = ( ( pstDstWin->height - u16VDispSize ) >> 2 ) << 1;
            }
#endif
            break;

        case E_MVD_AFD_CENTRE_14X9:
            if(u8AspectRate ==MVD_ASP_4TO3)
            {
                if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
                {
                    u16HDispSize = pstDstWin->height * 14 / 9;
                    u16HDispSize = ( u16HDispSize >> 1 ) << 1;
                    u16HDispStart = ( ( pstDstWin->width - u16HDispSize ) >> 2 ) << 1;
                }
            }
            else if(u8AspectRate == MVD_ASP_16TO9)
            {

            }
            break;
        case E_MVD_AFD_CENTRE_4X3_14X9:
            if(u8AspectRate == MVD_ASP_4TO3)
            {
                if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
                {
                    u16HDispSize = pstDstWin->height * 14 / 9;
                    u16HDispSize = ( u16HDispSize >> 1 ) << 1;
                    u16HDispStart = ( ( pstDstWin->width - u16HDispSize ) >> 2 ) << 1;
                }
            }

            else if(u8AspectRate == MVD_ASP_16TO9)
            {
                if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
                {
                    u16HDispSize = pstDstWin->height * 14 / 9;
                    u16HDispSize = ( u16HDispSize >> 1 ) << 1;
                    u16HDispStart = ( ( pstDstWin->width - u16HDispSize ) >> 2 ) << 1;
                }
            }


            break;
        case E_MVD_AFD_CENTRE_16X9_14X9:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
                /*
                if ( bPanelAR16x9 == FALSE )
                {
                    u16HCapSize = (U16)( (U32)u16VCapSize *  g_IPanel.Width() / g_IPanel.Height() );
                    u16HCapSize = ( u16HCapSize >> 1 ) << 1;
                    u16HCapStart = ( ( u16SrcWidth - u16HCapSize ) >> 2 ) << 1;
                }*/
            }
            break;

        case E_MVD_AFD_CENTRE_16X9_4X3:
            if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
            {
                /*
                if ( bPanelAR16x9 == FALSE )
                {
                    u16HCapSize = (U16)( (U32)u16VCapSize *  g_IPanel.Width() / g_IPanel.Height() );
                    u16HCapSize = ( u16HCapSize >> 1 ) << 1;
                    u16HCapStart = ( ( u16SrcWidth - u16HCapSize ) >> 2 ) << 1;
                }
                */
            }
            break;
/*
        case E_MVD_AFD_UNKNOWN:
            //printf("\n AFD unKnown");
            if(u8AspectRate == MVD_ASP_4TO3) //tommy
            {
                if ( g_IPanel.AspectRatio() == E_PNL_ASPECT_RATIO_WIDE )
                {
                    u16HDispSize = pstDstWin->height* 12 / 9;
                    u16HDispSize = ( u16HDispSize >> 1 ) << 1;
                    u16HDispStart = ( ( pstDstWin->width - u16HDispSize ) >> 2 ) << 1;
                }
            }
*/
        default:
            break;
    }
    pstDstWin->x += u16HDispStart;
    pstDstWin->y += u16VDispStart;
    pstDstWin->width =u16HDispSize;
    pstDstWin->height=u16VDispSize;
}

BOOLEAN _msAPI_Picture_CalculateSAR(SRC_RATIO_INFO *pstSrcRatioInfo,VDEC_CodecType codecType)
{
    U32 WR=0,HR=0;
    U16 u16SrcWidth = 0;

    if(codecType == E_VDEC_CODEC_TYPE_MPEG2)
    {
        if(pstSrcRatioInfo->u8AspectRate == MVD_ASP_4TO3)
        {
            WR = 4;
            HR = 3;
        }
        else if(pstSrcRatioInfo->u8AspectRate == MVD_ASP_16TO9)
        {
            WR = 16;
            HR = 9;
        }

        if(((U32)pstSrcRatioInfo->u16VideoWidth*9) == ((U32)pstSrcRatioInfo->u16VideoHeight*16)) //1920x1080
        {
            WR*=9;
            HR*=16;
        }
        else if(((U32)pstSrcRatioInfo->u16VideoWidth*4) == ((U32)pstSrcRatioInfo->u16VideoHeight*5))//720x576
        {
            WR*=4;
            HR*=5;
        }
        else
        {
            WR*=(pstSrcRatioInfo->u16VideoHeight>>4);
            HR*=(pstSrcRatioInfo->u16VideoWidth>>4);
        }
    }
    else if( (codecType == E_VDEC_CODEC_TYPE_H264)
        #if (CHIP_SUPPORT_HEVC)//IMPLEMENT_DTV_H265
           ||(codecType == E_VDEC_CODEC_TYPE_HEVC)
        #endif
           )
    {
        if(pstSrcRatioInfo->u8AspectRate == 0xff)
        {
            WR = pstSrcRatioInfo->u32SarWidth;
            HR = pstSrcRatioInfo->u32SarHeight;
        }
        else if(pstSrcRatioInfo->u8AspectRate >0 && pstSrcRatioInfo->u8AspectRate<17)
        {
            WR = _H264_ASPECT_RATIO[pstSrcRatioInfo->u8AspectRate][0];
            HR = _H264_ASPECT_RATIO[pstSrcRatioInfo->u8AspectRate][1];
        }

        if(MDrv_MVOP_GetIsHDuplicate())
        {
            u16SrcWidth = pstSrcRatioInfo->u16VideoWidth/2;
        }
        else
        {
           u16SrcWidth = pstSrcRatioInfo->u16VideoWidth;
        }
        if(u16SrcWidth * WR * 2 > pstSrcRatioInfo->u16VideoHeight * HR * 3)
            pstSrcRatioInfo->u8AspectRate = MVD_ASP_16TO9;
        else
            pstSrcRatioInfo->u8AspectRate = MVD_ASP_4TO3;
    }

    pstSrcRatioInfo->u32SarWidth  = WR;
    pstSrcRatioInfo->u32SarHeight = HR;

    if(pstSrcRatioInfo->u32SarWidth == 0 || pstSrcRatioInfo->u32SarHeight == 0)
        return FALSE;
    else
        return TRUE;
}

void msAPI_Picture_CalculateAFDWindow(XC_SETWIN_INFO *pstXC_SetWin_Info,
                                                EN_ASPECT_RATIO_TYPE enVideoScreen,
                                              MS_WINDOW_TYPE *pstCropWin,
                                              MS_WINDOW_TYPE *pstDstWin,
                                              SRC_RATIO_INFO *pstSrcRatioInfo)
{
    MS_WINDOW_TYPE tCropWin,tDstWin;

    memcpy(&tCropWin,pstCropWin,sizeof(MS_WINDOW_TYPE));
    memcpy(&tDstWin,pstDstWin,sizeof(MS_WINDOW_TYPE));

    AFD_MSG(printf("AFDWindow.crop1: x,y,w,h=%u,%u,%u,%u\n", tCropWin.x, tCropWin.y, tCropWin.width, tCropWin.height));

    MApp_Scaler_CalculateAspectRatio(pstXC_SetWin_Info, enVideoScreen,&tCropWin,&tDstWin);

    AFD_MSG(printf("AFDWindow.crop2: x,y,w,h=%u,%u,%u,%u\n", tCropWin.x, tCropWin.y, tCropWin.width, tCropWin.height));

    if(_msAPI_Picture_CalculateSAR(pstSrcRatioInfo,msAPI_VID_GetCodecType()))
    {

        _msAPI_Picture_Adjust_AFDDisplayWindow(pstSrcRatioInfo,pstDstWin);

#if (PANEL_16_10 == DISABLE)
#if (ENABLE_USERARC_WITH_AFD == DISABLE)
        //AFD display > default , use default display window.
        if(tDstWin.width < pstDstWin->width)
        {
            memcpy(pstDstWin,&tDstWin,sizeof(MS_WINDOW_TYPE));
        }
#endif
#endif
        //printf("u8AspectRate:%bx\n",stVidStatus.u8AspectRate);

        //In this function, it will adjust cropping window according to display window size.

        _msAPI_Picture_Adjust_AFDSourceWindow(pstSrcRatioInfo, pstCropWin, pstDstWin);
    }
    AFD_MSG(printf("AFD:%x , ASP:%x\n",pstSrcRatioInfo->u8AFD,pstSrcRatioInfo->u8AspectRate));
    AFD_MSG(printf("SAR:%d , %d\n",pstSrcRatioInfo->u32SarWidth,pstSrcRatioInfo->u32SarHeight));
    AFD_MSG(printf("AFDWindow.crop: x,y,w,h=%d,%d,%d,%d\n", pstCropWin->x, pstCropWin->y, pstCropWin->width, pstCropWin->height));
    AFD_MSG(printf("AFDWindow.Disp: x,y,w,h=%d,%d,%d,%d\n", pstDstWin->x, pstDstWin->y, pstDstWin->width, pstDstWin->height));

}

//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------

BOOLEAN msAPI_Picture_isCurrentAFDVaild(U8 tmpAFD)
{
    if(tmpAFD!=0 && tmpAFD!=0xFF)
        return TRUE;
    else
        return FALSE;
}

BOOLEAN msAPI_Picture_isAFDEnable(EN_ASPECT_RATIO_TYPE enVideoScreen)
{
    BOOLEAN ret = TRUE;

    #if MHEG5_ENABLE
    if(  msAPI_MHEG5_IsRunning())
    {
    if(!msAPI_MHEG5_VID_AFD_Status())
        ret = FALSE;
    }
    #endif

    if(enVideoScreen != VIDEOSCREEN_PROGRAM
       && enVideoScreen != VIDEOSCREEN_PROGRAM_4X3
       && enVideoScreen != VIDEOSCREEN_PROGRAM_16X9
      )
    {
#if(ENABLE_USERARC_WITH_AFD == DISABLE)
        ret = FALSE;
#endif
    }

    #if 0//(ENABLE_DTV_EPG) ATSC_FIX_C
    if ( STATE_TOP_EPG == MApp_TopStateMachine_GetTopState() )
    {
         ret = FALSE;
    }
    #endif

    return ret;
}

void MApp_Picture_AFDMonitor(void)
{
    BOOLEAN bMonMAIN_WINDOW = FALSE;

    if( FALSE == msAPI_VID_GetVidInfo(&gstVidStatus) )
    {
        gstPreVidStatus.u8AFD = 0xff;
        return;
    }

    if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) )
    {
        bMonMAIN_WINDOW = TRUE;
        if(!msAPI_Picture_isAFDEnable(stSystemInfo[MAIN_WINDOW].enAspectRatio))
        {
            gstPreVidStatus.u8AFD = 0xff;
            bMonMAIN_WINDOW = FALSE;
        }

        #if MHEG5_ENABLE
        if( msAPI_MHEG5_IsRunning() &&
            !(msAPI_MHEG5_VID_IsFullScreen(&g_MHEG5Video.stMHEG5VideoAction)))
        {
            gstPreVidStatus.u8AFD = 0xff;
            bMonMAIN_WINDOW = FALSE;
        }
        #endif
    }

    gstVidStatus.u8AFD = MApi_VDEC_GetActiveFormat();

    if(bMonMAIN_WINDOW)
    {
        if ( //bFullScreen &&
             (gstVidStatus.u8AFD != gstPreVidStatus.u8AFD) &&
             //(gstVidStatus.u8AFD != 0) &&
             (gstVidStatus.u8AFD != 0xFF) )
        {

            //if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) )
            {
                //if ( msAPI_Picture_isAFDEnable(stSystemInfo[MAIN_WINDOW].enAspectRatio) )
                {
                    AFD_MSG(printf("AFD = 0x%02bx\n", gstVidStatus.u8AFD));

                    stSystemInfo[MAIN_WINDOW].enAspectRatio = MApp_Scaler_GetAspectRatio(MAIN_WINDOW,ST_VIDEO.eAspectRatio);

                #if MHEG5_ENABLE
                    if(msAPI_MHEG5_IsRunning())
                    {

                        //if(msAPI_MHEG5_VID_IsFullScreen(&g_MHEG5Video.stMHEG5VideoAction))
                        {
                            MApp_MHEG5_SetGraphARCInfo(SENDARC_AFD_FOR_GE,stSystemInfo[MAIN_WINDOW].enAspectRatio);
                            MApp_MHEG5_SetGraphARCInfo(SENDARC_AFD,stSystemInfo[MAIN_WINDOW].enAspectRatio);
                        }
                        //printf("After Adj ASP:(%u,%u,%u,%u),(%u,%u,%u,%u)\n",tCropWin.x,tCropWin.y,tCropWin.width,tCropWin.height,tDstWin.x,tDstWin.y,tDstWin.width,tDstWin.height);
                    }
                #endif
                #if ENABLE_PVR
                    enPVRState       PVRState       = MApp_PVR_StateMachineGet();
                    enTimeShiftState TimeShiftState = MApp_TimeShift_StateMachineGet();
                    if((PVRState != E_PVR_STATE_RECORDnPLAYBACK && PVRState != E_PVR_STATE_PLAYBACK)
                    &&(TimeShiftState != E_TIMESHIFT_STATE_RECORDINGnPLAYBACKING && TimeShiftState != E_TIMESHIFT_STATE_PLAYBACKING))
                    {
                        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, 300, MAIN_WINDOW);
                    }
                #endif
                    MApi_XC_SkipOPWriteOffInSetWindow(TRUE, MAIN_WINDOW);
                #if (ENABLE_PIP)
                    if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
                    {
                        MS_WINDOW_TYPE stWinRect;
                        if(MApp_InputSource_PIP_GetMainWinRect(&stWinRect))
                        {
                            MApp_Scaler_SetWindow(NULL, NULL, &stWinRect,
                            stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
                        }
                        else
                        {
                            MApp_Scaler_SetWindow(NULL, NULL, NULL,
                                               stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
                        }
                    }
                    else
                #endif
                    {
                        MApp_Scaler_SetWindow(NULL, NULL, NULL,
                                               stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
                    }
                    MApi_XC_SkipOPWriteOffInSetWindow(FALSE, MAIN_WINDOW);
                    gstPreVidStatus.u8AFD = gstVidStatus.u8AFD;
                }
            }
        }
      #if (ENABLE_PIP)
        if(IsPIPSupported())
        {
            if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) )
            {
                if ( msAPI_Picture_isAFDEnable(stSystemInfo[SUB_WINDOW].enAspectRatio) )
                {
                    AFD_MSG(printf("AFD = 0x%02bx\n", gstVidStatus.u8AFD));

                    stSystemInfo[SUB_WINDOW].enAspectRatio = MApp_Scaler_GetAspectRatio(SUB_WINDOW,ST_VIDEO.eAspectRatio);

                    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, 300, SUB_WINDOW);

                    MApi_XC_SkipOPWriteOffInSetWindow(TRUE, SUB_WINDOW);

                    MApp_Scaler_SetWindow(NULL, NULL, NULL,
                                                   stSystemInfo[SUB_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(SUB_WINDOW), SUB_WINDOW);
                    MApi_XC_SkipOPWriteOffInSetWindow(FALSE, SUB_WINDOW);

                    gstPreVidStatus.u8AFD = gstVidStatus.u8AFD;
                }
            }
        }
      #endif

#if(ENABLE_VE)
        msAPI_Scaler_SetAFDToVEWSS(ENABLE, gstVidStatus.u8AFD,  gstVidStatus.u8AspectRate); // 071204
#endif
    }
}

void msAPI_XC_EnableMirrorMode(BOOL bEnableMirror)
{
#if ENABLE_PANEL_H_MIRROR
    if(bEnableMirror)
    {
        MApi_XC_EnableMirrorMode2(MIRROR_V_ONLY);
    }
    else
    {
        MApi_XC_EnableMirrorMode2(MIRROR_H_ONLY);
    }
#else
    MApi_XC_EnableMirrorMode(bEnableMirror);
#endif
}

void MApp_Image_SetMirror(void)
{
  #if MirrorEnable
   if(stGenSetting.g_SysSetting.g_MirrorEnable)
    {
        // Video
        msAPI_XC_EnableMirrorMode(TRUE);
        // GOP
        msAPI_GOP_GWIN_SetHMirror(TRUE);
        msAPI_GOP_GWIN_SetVMirror(TRUE);
        //MApi_XC_DisableInputSource(FALSE, MAIN_WINDOW);
    }
    else
  #endif
    {
        // Video
        msAPI_XC_EnableMirrorMode(FALSE);
        // GOP
        msAPI_GOP_GWIN_SetHMirror(FALSE);
        msAPI_GOP_GWIN_SetVMirror(FALSE);
       // MApi_XC_DisableInputSource(FALSE, MAIN_WINDOW);
    }

}

BOOLEAN MApp_Image_GetMirror(void)
{
#if (MirrorEnable)
    return  stGenSetting.g_SysSetting.g_MirrorEnable;
#else
    return FALSE;
#endif
}
#if 0  //same as MApp_SetDesignImageMirror

BOOLEAN MApp_SetFactoryImageMirror(void)
{
#if (MirrorEnable == ENABLE)
    if (!MApi_XC_IsInputSourceDisabled(MAIN_WINDOW))
        MApi_XC_DisableInputSource(TRUE, MAIN_WINDOW);
    if(stGenSetting.g_SysSetting.g_MirrorEnable)
    {
        // Video Mirror
        if(IsDTVInUse()||IsStorageInUse())
        {
            msAPI_XC_EnableMirrorMode(FALSE);
            MDrv_MVOP_SetVOPMirrorMode(ENABLE, E_VOPMIRROR_HORIZONTALL);
            MDrv_MVOP_SetVOPMirrorMode(ENABLE, E_VOPMIRROR_VERTICAL);
        }
        else
        {
            msAPI_XC_EnableMirrorMode(TRUE);
        }
        // GOP Mirror
        msAPI_GOP_GWIN_SetHMirror(TRUE);
        msAPI_GOP_GWIN_SetVMirror(TRUE);
    }
    else
    {
        // Video Mirror
        if(IsDTVInUse()||IsStorageInUse())
        {
            msAPI_XC_EnableMirrorMode(FALSE);
            MDrv_MVOP_SetVOPMirrorMode(DISABLE, E_VOPMIRROR_HORIZONTALL);
            MDrv_MVOP_SetVOPMirrorMode(DISABLE, E_VOPMIRROR_VERTICAL);
        }
        else
        {
            msAPI_XC_EnableMirrorMode(FALSE);
        }

        // GOP Mirror
        msAPI_GOP_GWIN_SetHMirror(FALSE);
        msAPI_GOP_GWIN_SetVMirror(FALSE);
    }

    if (MApp_IsSrcHasSignal(MAIN_WINDOW))
    {
        MApp_Scaler_SetWindow(NULL, NULL, NULL,stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
        MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
        MApp_Scaler_SetTiming(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);

    #if ENABLE_DMP
        if ((IsSrcTypeStorage(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))&&(!MApp_MPlayer_IsMoviePlaying()))
        {
             ; // do nothing
        }
        else
    #endif
        {
            if(MApi_XC_IsCurrentFrameBufferLessMode() || MApi_XC_IsCurrentRequest_FrameBufferLessMode())
            {
                 MApi_XC_WaitFPLLDone();
            }
            // wait 16 input vsync before turn on scalar for worst case
            MApi_XC_WaitInputVSync(16, 200, MAIN_WINDOW);
            MApi_XC_DisableInputSource(FALSE, MAIN_WINDOW);
        }
    }
    else if (IsATVInUse())//for ATV no signal
    {
        // wait 16 input vsync before turn on scalar for worst case
        MApi_XC_WaitInputVSync(16, 200, MAIN_WINDOW);
        MApi_XC_DisableInputSource(FALSE, MAIN_WINDOW);
    }
#endif
    return TRUE;
}
#endif

BOOLEAN MApp_SetDesignImageMirror(void)
{
#if (MirrorEnable == ENABLE)
    if (!MApi_XC_IsInputSourceDisabled(MAIN_WINDOW))
        MApi_XC_DisableInputSource(TRUE, MAIN_WINDOW);

    if(IsDTVInUse())
    {
        MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
    }

    if( IsHDMIInUse() )
    {
        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, 400, MAIN_WINDOW);
    }

    if(stGenSetting.g_SysSetting.g_MirrorEnable)
    {
        // Video Mirror
        if(IsDTVInUse()||IsStorageInUse())
        {
            msAPI_XC_EnableMirrorMode(FALSE);
            MDrv_MVOP_SetVOPMirrorMode(ENABLE, E_VOPMIRROR_HORIZONTALL);
            MDrv_MVOP_SetVOPMirrorMode(ENABLE, E_VOPMIRROR_VERTICAL);
#if(ENABLE_VE)
            MDrv_VE_EnableMirrorMode(MS_VE_MIRROR_HV);  //need enable VE mirror when use MVOP mirror
#endif
        }
        else
        {
            msAPI_XC_EnableMirrorMode(TRUE);
        }
        // GOP Mirror
        msAPI_GOP_GWIN_SetHMirror(TRUE);
        msAPI_GOP_GWIN_SetVMirror(TRUE);
    }
    else
    {
        // Video Mirror
        if(IsDTVInUse()||IsStorageInUse())
        {
            msAPI_XC_EnableMirrorMode(FALSE);
            MDrv_MVOP_SetVOPMirrorMode(DISABLE, E_VOPMIRROR_HORIZONTALL);
            MDrv_MVOP_SetVOPMirrorMode(DISABLE, E_VOPMIRROR_VERTICAL);
#if(ENABLE_VE)
            MDrv_VE_EnableMirrorMode(MS_VE_MIRROR_NORMAL);
#endif
        }
        else
        {
            msAPI_XC_EnableMirrorMode(FALSE);
        }

        // GOP Mirror
        msAPI_GOP_GWIN_SetHMirror(FALSE);
        msAPI_GOP_GWIN_SetVMirror(FALSE);
    }

    if(IsDTVInUse())
    {
        MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
    }

    if( IsHDMIInUse() )
    {
        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, DISABLE, 400, MAIN_WINDOW);
    }

    if (MApp_IsSrcHasSignal(MAIN_WINDOW))
    {
        XC_SETWIN_INFO tWinInfo;

        MApp_Scaler_GetWinInfo(&tWinInfo, MAIN_WINDOW);
        //MApp_Scaler_SetWindow(NULL, NULL, NULL,stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);

        if(IsHDMIInUse())
        {
            MApp_Scaler_SetWindow(NULL, NULL, NULL,stSystemInfo[MAIN_WINDOW].enAspectRatio, tWinInfo.enInputSourceType, MAIN_WINDOW);
        }
        else
        {
            MApp_Scaler_SetWindow(NULL, &tWinInfo.stCropWin, &tWinInfo.stDispWin,stSystemInfo[MAIN_WINDOW].enAspectRatio, tWinInfo.enInputSourceType, MAIN_WINDOW);
        }

        MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
        MApp_Scaler_SetTiming(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
        //>>>>>>>>>>> patch for mantis[0549872]
        if (IsStorageInUse()
    #if ENABLE_MPLAYER_PHOTO
            && !MApp_MPlayer_IsPhotoPlaying()
    #endif
    #if ENABLE_MPLAYER_MOVIE
            &&(!MApp_MPlayer_IsMoviePlaying())
    #endif
        )
        {
            //do nothing
        }
        else
        {
            if(MApi_XC_IsCurrentFrameBufferLessMode() || MApi_XC_IsCurrentRequest_FrameBufferLessMode())
            {
                MApi_XC_WaitFPLLDone();
            }
            // wait 16 input vsync before turn on scalar for worst case
            MApi_XC_WaitInputVSync(16, 200, MAIN_WINDOW);
            MApi_XC_DisableInputSource(FALSE, MAIN_WINDOW);
        }
    }
    else if (IsATVInUse())//for ATV no signal
    {
        // wait 16 input vsync before turn on scalar for worst case
        MApi_XC_WaitInputVSync(16, 200, MAIN_WINDOW);
        MApi_XC_DisableInputSource(FALSE, MAIN_WINDOW);
    }
#endif
    return TRUE;
}

#undef _APP_XC_SYS_C_
