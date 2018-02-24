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

#define MAPP_ZUI_APIGUIDRAW_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


///////////////////////////////////////////////////////////////////////////////////////////////////
// Description: default drawing style
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include "MsCommon.h"

#include "MApp_ZUI_Main.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIgdi.h"
#include "OSDcp_Bitmap_EnumIndex.h"
#include "OSDcp_String_EnumIndex.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_APIcomponent.h"

#include "msAPI_Font.h"
#include "apiGOP.h"
#include "MApp_GlobalVar.h"
#include "MApp_Font.h"
#include "MsTypes.h"
#include "drvBDMA.h"

extern U16 _MApp_ZUI_API_FindFirstComponentIndex(HWND hWnd, DRAWSTYLE_TYPE type, DRAWCOMPONENT comp);
///////////////////////////////////////////////////////////////////////////////
///  private  _MApp_ZUI_API_DrawComponent
///  draw a single style into GRAPHIC_DC (for drawing built-in components)
///
///  @param [in]  component DRAWCOMPONENT    style(component) type
///  @param [in]  u16Index  U16              style(component) index
///  @param [in]  pdc GRAPHIC_DC *    target GRAPHIC_DC wants to paint for
///  @param [in]  rect RECT *    target region wants to draw
///
///  This function doesn't return a value
///
///  @author MStar @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
void _MApp_ZUI_API_DrawComponent(DRAWCOMPONENT component, U16 u16Index, const GRAPHIC_DC * pdc, const RECT * rect)
{


    switch(component)
    {
        case CP_RECT_BORDER:
            {
                DRAW_RECT_BORDER * paramRectBorder = (DRAW_RECT_BORDER*)&_Zui_RectBorder_List[u16Index];
                _MApp_ZUI_API_DrawDynamicComponent(CP_RECT_BORDER, paramRectBorder, pdc, rect);
            }
            break;

        case CP_FILL_RECT:
            {
                DRAW_FILL_RECT * paramFillRect = (DRAW_FILL_RECT*)&_Zui_FillRect_List[u16Index];
                _MApp_ZUI_API_DrawDynamicComponent(CP_FILL_RECT, paramFillRect, pdc, rect);

            }
            break;

        case CP_TEXT_OUT:
            {
                DRAW_TEXT_OUT * paramTextOut = (DRAW_TEXT_OUT*)&_Zui_TextOut_List[u16Index];
                _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT, paramTextOut, pdc, rect);

            }
            break;

        case CP_BITMAP:
            {
                DRAW_BITMAP * paramBitmap = (DRAW_BITMAP*)&_Zui_Bitmap_List[u16Index];
                _MApp_ZUI_API_DrawDynamicComponent(CP_BITMAP, paramBitmap, pdc, rect);

            }
            break;

        case CP_RECT:
            {

                DRAW_RECT * paramRect = (DRAW_RECT*)&_Zui_Rect_List[u16Index];
                _MApp_ZUI_API_DrawDynamicComponent(CP_RECT, paramRect, pdc, rect);

            }
            break;

        default:
            break;
    }
}


///////////////////////////////////////////////////////////////////////////////
///  private  _MApp_ZUI_API_DrawDynamicComponent
///  draw a single style into GRAPHIC_DC (for drawing user-defined components)
///
///  @param [in]  component DRAWCOMPONENT         style(component) type
///  @param [in]  param void *                    style(component) parameters
///  @param [in]  pdc GRAPHIC_DC *    target GRAPHIC_DC wants to paint for
///  @param [in]  rect RECT *    target region wants to draw
///
///  This function doesn't return a value
///
///  @author MStar @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
void _MApp_ZUI_API_DrawDynamicComponent(DRAWCOMPONENT component, const void * param, const GRAPHIC_DC * pdc, const RECT * rect)
{
    RECT rectGWin, rectClip;
    memset(&rectGWin,0,sizeof(RECT));
    MApp_ZUI_API_QueryGWinRect(&rectGWin);
    rectClip = *rect;
    if ( (rectGWin.left + rectClip.left + rectClip.width) > g_IPanel.Width() )
    {
        rectClip.width = g_IPanel.Width() - rectClip.left - rectGWin.left;
    }

    msAPI_OSD_SetClipWindow(rectClip.left, rectClip.top, rectClip.left+rectClip.width-1, rectClip.top+rectClip.height-1);
    MApi_GOP_GWIN_Switch2FB(pdc->u8FbID);//SetDstBuffer(pGC, BUFFER_DISPLAY);

    MApi_GFX_SetNearestMode(TRUE); //default setting
    MApi_GFX_SetDither (TRUE);

#if (MPLAYER_BITMAP_FORMAT == MPLAYER_ARGB4444 || MPLAYER_BITMAP_FORMAT == MPLAYER_ARGB8888)
    //for ARGB4444 and ARGB8888, use bitmap original alpha value
    if (pdc->bSrcAlphaReplaceDstAlpha)
        MApi_GFX_SetAlpha(TRUE, COEF_ASRC, ABL_FROM_ASRC, 0);
    else
        MApi_GFX_SetAlpha(TRUE, COEF_ASRC, ABL_FROM_ADST, 0);
#elif (MPLAYER_BITMAP_FORMAT == MPLAYER_ARGB1555)
    if (pdc->bSrcAlphaReplaceDstAlpha)
    {
        MApi_GFX_SetAlpha(TRUE, COEF_CONST, ABL_FROM_ASRC, pdc->u8ConstantAlpha);
    }
    else
    {
        MApi_GFX_SetAlpha(TRUE, COEF_CONST, ABL_FROM_ADST, pdc->u8ConstantAlpha);
    }
#elif (MPLAYER_BITMAP_FORMAT == MPLAYER_I8)
    //for I8 palette mode, alpha disabled
    MApi_GFX_SetAlpha(FALSE, COEF_ASRC, ABL_FROM_CONST, 0xFF);
#else
    if (pdc->u8ConstantAlpha == 0xFF)
    {
        MApi_GFX_SetAlpha(FALSE, COEF_CONST, ABL_FROM_CONST, 0xFF);
    }
    else
    {
        MApi_GFX_SetAlpha(TRUE, COEF_CONST, ABL_FROM_CONST, pdc->u8ConstantAlpha);
    }
#endif

    switch(component)
    {
        case CP_RECT_BORDER:
            {
                DRAW_RECT_BORDER * paramRectBorder = (DRAW_RECT_BORDER*)param;
                U8 i;

                g_ClrLine.u8LineWidth    = 1;

                for(i=0; i<paramRectBorder->thickness; i++)
                {
                    RECT R;
                    RECT_SET(R, rect->left+i, rect->top+i, rect->width-(i<<1), rect->height-(i<<1));

                    g_ClrLine.u32LineColor    = paramRectBorder->colorLeftTop;
                    g_ClrLine.x1 = R.left;
                    g_ClrLine.y1 = R.top;
                    g_ClrLine.x2 = (R.left+R.width);
                    g_ClrLine.y2 = R.top;
                    msAPI_OSD_DrawLine(&g_ClrLine);

                    g_ClrLine.u32LineColor    = paramRectBorder->colorRightDown;
                    g_ClrLine.x1 = (R.left+R.width-1);
                    g_ClrLine.y1 = R.top;
                    g_ClrLine.x2 = (R.left+R.width-1);
                    g_ClrLine.y2 = (R.top+R.height+1);
                    msAPI_OSD_DrawLine(&g_ClrLine);

                    g_ClrLine.u32LineColor    = paramRectBorder->colorLeftTop;
                    g_ClrLine.x1 = R.left;
                    g_ClrLine.y1 = R.top;
                    g_ClrLine.x2 = R.left;
                    g_ClrLine.y2 = (R.top+R.height);
                    msAPI_OSD_DrawLine(&g_ClrLine);

                    g_ClrLine.u32LineColor    = paramRectBorder->colorRightDown;
                    g_ClrLine.x1 = R.left;
                    g_ClrLine.y1 = (R.top+R.height-1);
                    g_ClrLine.x2 = (R.left+R.width+1);
                    g_ClrLine.y2 = (R.top+R.height-1);
                    msAPI_OSD_DrawLine(&g_ClrLine);

                }
            }
            break;

        case CP_FILL_RECT:
            {
                DRAW_FILL_RECT * paramFillRect = (DRAW_FILL_RECT*)param;

                clrBtn1.x = rect->left;
                clrBtn1.y = rect->top;
                clrBtn1.width = rect->width;
                clrBtn1.height = rect->height;
                clrBtn1.u8Gradient = paramFillRect->eGradient;
                clrBtn1.fHighLight = FALSE;
                clrBtn1.g_clr = paramFillRect->toColor;
                clrBtn1.b_clr = paramFillRect->fromColor;

                msAPI_OSD_DrawBlock(&clrBtn1);

            }
            break;

        /*case CP_RECT_BORDER_EX:
            {
                DRAW_RECT_BORDER_EX * param = (DRAW_RECT_BORDER_EX*)style_list->param;
                MApi_Osd_DrawRectangleBorderEx(hdc->pGC,
                                rect,
                                UI_MENU_DRAW_COLOR_FMT,
                                param->colorTopLeft,
                                param->colorTopRight,
                                param->colorRightTop,
                                param->colorRightDown,
                                param->colorDownRight,
                                param->colorDownLeft,
                                param->colorLeftDown,
                                param->colorLeftTop,
                                param->thickness,
                                param->lt,
                                hdc->pAlpha);
            }
            break;

        case CP_RECT_3D:
            {
                DRAW_RECT_3D * param = (DRAW_RECT_3D*)style_list->param;
                MApi_Osd_Draw3DRectangle(hdc->pGC,
                                rect,
                                UI_MENU_DRAW_COLOR_FMT,
                                param->COLOR_3DBORDER_DARK,
                                param->COLOR_3DBORDER_LIGHT,
                                param->borderWidth,
                                param->flag,
                                hdc->pAlpha);
            }
            break;*/

        case CP_TEXT_OUT:
            {
                DRAW_TEXT_OUT * paramTextOut = (DRAW_TEXT_OUT*)param;
                U16 * pString = MApp_ZUI_API_GetString(paramTextOut->StringID);

                clrBtn1.x = rect->left;
                clrBtn1.y = rect->top;
                clrBtn1.width = rect->width;
                clrBtn1.height = rect->height;
                #if (MPLAYER_BITMAP_FORMAT == MPLAYER_I8)
                clrBtn1.t_clr = paramTextOut->TextColor&0xFF;
                #else //ZUI_ENABLE_PALETTE
                clrBtn1.t_clr = paramTextOut->TextColor;
                #endif //ZUI_ENABLE_PALETTE

                clrBtn1.Fontfmt.flag = paramTextOut->flag;
                clrBtn1.Fontfmt.ifont_gap = paramTextOut->u8dis;
                clrBtn1.bStringIndexWidth = CHAR_IDX_2BYTE;

                switch (paramTextOut->eTextAttrib)
                {
                    case eTextAlignLeft:
                        clrBtn1.enTextAlign = EN_ALIGNMENT_LEFT;
                        break;
                    case eTextAlignMiddle:
                    case eTextAlignMiddleWH:
                    case eTextAlignLeft_MiddleH:
                    case eTextAlignRight_MiddleH:
                        clrBtn1.enTextAlign = EN_ALIGNMENT_CENTER;
                        break;
                    case eTextAlignRight:
                        clrBtn1.enTextAlign = EN_ALIGNMENT_RIGHT;
                        break;
                    default:
                        clrBtn1.enTextAlign = EN_ALIGNMENT_DEFAULT;
                        break;
                }

                msAPI_OSD_DrawClippedString(Font[paramTextOut->eSystemFont].fHandle,
                    pString, &clrBtn1, EN_STRING_ENDING_3_DOT);

            }
            break;


        case CP_TEXT_OUT_DYNAMIC:
            {
                DRAW_TEXT_OUT_DYNAMIC * paramTextOut = (DRAW_TEXT_OUT_DYNAMIC*)param;

                clrBtn1.x = rect->left;
                clrBtn1.y = rect->top;
                clrBtn1.width = rect->width;
                clrBtn1.height = rect->height;
                #if (MPLAYER_BITMAP_FORMAT == MPLAYER_I8)
                clrBtn1.t_clr = paramTextOut->TextColor&0xFF;
                #else //ZUI_ENABLE_PALETTE
                clrBtn1.t_clr = paramTextOut->TextColor;
                #endif //ZUI_ENABLE_PALETTE

                clrBtn1.Fontfmt.flag = paramTextOut->flag;
                clrBtn1.Fontfmt.ifont_gap = paramTextOut->u8dis;
                clrBtn1.bStringIndexWidth = CHAR_IDX_2BYTE;

                switch (paramTextOut->eTextAttrib)
                {
                    case eTextAlignLeft:
                        clrBtn1.enTextAlign = EN_ALIGNMENT_LEFT;
                        break;
                    case eTextAlignMiddle:
                    case eTextAlignMiddleWH:
                    case eTextAlignLeft_MiddleH:
                    case eTextAlignRight_MiddleH:
                        clrBtn1.enTextAlign = EN_ALIGNMENT_CENTER;
                        break;
                    case eTextAlignRight:
                        clrBtn1.enTextAlign = EN_ALIGNMENT_RIGHT;
                        break;
                    default:
                        clrBtn1.enTextAlign = EN_ALIGNMENT_DEFAULT;
                        break;
                }

                msAPI_OSD_DrawClippedString(Font[paramTextOut->eSystemFont].fHandle,
                    paramTextOut->pString, &clrBtn1, (EN_STRING_ENDING_TYPE)paramTextOut->u8dots/*EN_STRING_ENDING_3_DOT*/);


            }
            break;


        case CP_PUNCTUATED_DYNAMIC:
            {
                //NOTE: we define CP_PUNCTUATED_DYNAMIC use original height with max row
                //      this component also automatically H-center,
                //      not the same as msAPI_OSD_DrawPunctuatedString() only define the first single height

                DRAW_PUNCTUATED_DYNAMIC * paramTextOut = (DRAW_PUNCTUATED_DYNAMIC*)param;
                U8 u8Row;
                U16 u16Height;
                //U16 * pString = MApp_ZUI_API_GetString(paramTextOut->StringID);

                if (paramTextOut->max_row == 0) break;

                clrBtn1.x = rect->left + 2; //note: reserve 2 pixel for avoiding crop...
                clrBtn1.y = rect->top;
                clrBtn1.width = rect->width - 8; //note: reserve 8 pixel for avoiding crop...
                clrBtn1.height = rect->height / paramTextOut->max_row;
                #if (MPLAYER_BITMAP_FORMAT == MPLAYER_I8)
                clrBtn1.t_clr = paramTextOut->TextColor&0xFF;
                #else //ZUI_ENABLE_PALETTE
                clrBtn1.t_clr = paramTextOut->TextColor;
                #endif //ZUI_ENABLE_PALETTE

                clrBtn1.Fontfmt.flag = paramTextOut->flag;
                clrBtn1.Fontfmt.ifont_gap = paramTextOut->u8dis;
                clrBtn1.bStringIndexWidth = CHAR_IDX_2BYTE;

                switch (paramTextOut->eTextAttrib)
                {
                    case eTextAlignLeft:
                        clrBtn1.enTextAlign = EN_ALIGNMENT_LEFT;
                        break;
                    case eTextAlignMiddle:
                    case eTextAlignMiddleWH:
                    case eTextAlignLeft_MiddleH:
                    case eTextAlignRight_MiddleH:
                        clrBtn1.enTextAlign = EN_ALIGNMENT_CENTER;
                        break;
                    case eTextAlignRight:
                        clrBtn1.enTextAlign = EN_ALIGNMENT_RIGHT;
                        break;
                    default:
                        clrBtn1.enTextAlign = EN_ALIGNMENT_DEFAULT;
                        break;
                }

                msAPI_OSD_GetPunctuatedStringHeight(Font[paramTextOut->eSystemFont].fHandle,
                    paramTextOut->pString, &clrBtn1, paramTextOut->max_row, &u8Row, &u16Height);

                //printf("[]row=%bu,height=%u\n", u8Row, u16Height);

                if (u8Row > 0 && u16Height > 0)
                {
                    if (u16Height < rect->height)
                    {
                        clrBtn1.y += (rect->height-u16Height)/2;
                    }
                    if ( u8Row > paramTextOut->max_row )
                    {
                        u8Row = paramTextOut->max_row;
                    }

                    msAPI_OSD_DrawPunctuatedString(Font[paramTextOut->eSystemFont].fHandle,
                        paramTextOut->pString, &clrBtn1, u8Row);
                }

            }
            break;

        case CP_EPG_PUNCTUATED_DYNAMIC:
            {
                //NOTE: we define CP_PUNCTUATED_DYNAMIC use original height with max row
                //      this component also automatically H-center,
                //      not the same as msAPI_OSD_DrawPunctuatedString() only define the first single height

                DRAW_PUNCTUATED_DYNAMIC * paramTextOut = (DRAW_PUNCTUATED_DYNAMIC*)param;

                if (paramTextOut->max_row == 0) break;

                clrBtn1.x = rect->left + 2; //note: reserve 2 pixel for avoiding crop...
                clrBtn1.y = rect->top;
                clrBtn1.width = rect->width - 8; //note: reserve 8 pixel for avoiding crop...
                clrBtn1.height = rect->height / paramTextOut->max_row;
                #if (MPLAYER_BITMAP_FORMAT == MPLAYER_I8)
                clrBtn1.t_clr = paramTextOut->TextColor&0xFF;
                #else //ZUI_ENABLE_PALETTE
                clrBtn1.t_clr = paramTextOut->TextColor;
                #endif //ZUI_ENABLE_PALETTE

                clrBtn1.Fontfmt.flag = paramTextOut->flag;
                clrBtn1.Fontfmt.ifont_gap = paramTextOut->u8dis;
                clrBtn1.bStringIndexWidth = CHAR_IDX_2BYTE;

                switch (paramTextOut->eTextAttrib)
                {
                    case eTextAlignLeft:
                        clrBtn1.enTextAlign = EN_ALIGNMENT_LEFT;
                        break;
                    case eTextAlignMiddle:
                    case eTextAlignMiddleWH:
                    case eTextAlignLeft_MiddleH:
                    case eTextAlignRight_MiddleH:
                        clrBtn1.enTextAlign = EN_ALIGNMENT_CENTER;
                        break;
                    case eTextAlignRight:
                        clrBtn1.enTextAlign = EN_ALIGNMENT_RIGHT;
                        break;
                    default:
                        clrBtn1.enTextAlign = EN_ALIGNMENT_DEFAULT;
                        break;
                }

                msAPI_OSD_DrawPunctuatedString_S1_NEW(Font[paramTextOut->eSystemFont].fHandle,
                        (U8*)paramTextOut->pString, &clrBtn1, paramTextOut->max_row,FALSE);

            }
            break;

       case  CP_SCROL_PUNCTUATED_DYNAMIC:
           {
               //NOTE: we define CP_PUNCTUATED_DYNAMIC use original height with max row
               //      this component also automatically H-center,
               //      not the same as msAPI_OSD_DrawPunctuatedString() only define the first single height

               DRAW_PUNCTUATED_DYNAMIC * paramTextOut = (DRAW_PUNCTUATED_DYNAMIC*)param;

               if (paramTextOut->max_row == 0) break;

               clrBtn1.x = rect->left + 2; //note: reserve 2 pixel for avoiding crop...
               clrBtn1.y = rect->top;
               clrBtn1.width = rect->width - 8; //note: reserve 8 pixel for avoiding crop...
               clrBtn1.height = rect->height / paramTextOut->max_row;
    #if (MPLAYER_BITMAP_FORMAT == MPLAYER_I8)
               clrBtn1.t_clr = paramTextOut->TextColor&0xFF;
    #else //ZUI_ENABLE_PALETTE
               clrBtn1.t_clr = paramTextOut->TextColor;
    #endif //ZUI_ENABLE_PALETTE

               clrBtn1.Fontfmt.flag = paramTextOut->flag;
               clrBtn1.Fontfmt.ifont_gap = paramTextOut->u8dis;
               clrBtn1.bStringIndexWidth = CHAR_IDX_2BYTE;

               switch (paramTextOut->eTextAttrib)
               {
                   case eTextAlignLeft:
                       clrBtn1.enTextAlign = EN_ALIGNMENT_LEFT;
                       break;
                   case eTextAlignMiddle:
                   case eTextAlignMiddleWH:
                   case eTextAlignLeft_MiddleH:
                   case eTextAlignRight_MiddleH:
                       clrBtn1.enTextAlign = EN_ALIGNMENT_CENTER;
                       break;
                   case eTextAlignRight:
                       clrBtn1.enTextAlign = EN_ALIGNMENT_RIGHT;
                       break;
                   default:
                       clrBtn1.enTextAlign = EN_ALIGNMENT_DEFAULT;
                       break;
               }



               msAPI_OSD_DrawScrolPunctuatedString(Font[paramTextOut->eSystemFont].fHandle,
                   (U8*)paramTextOut->pString, &clrBtn1, paramTextOut->max_row);

           }
           break;


        case CP_BT_TEXT_DYNAMIC:
            {
                //NOTE: we define CP_PUNCTUATED_DYNAMIC use original height with max row
                //      this component also automatically H-center,
                //      not the same as msAPI_OSD_DrawPunctuatedString() only define the first single height

                DRAW_PUNCTUATED_DYNAMIC * paramTextOut = (DRAW_PUNCTUATED_DYNAMIC*)param;

                if (paramTextOut->max_row == 0) break;

                clrBtn1.x = rect->left + 2; //note: reserve 2 pixel for avoiding crop...
                clrBtn1.y = rect->top;
                clrBtn1.width = rect->width - 8; //note: reserve 8 pixel for avoiding crop...
                clrBtn1.height = rect->height / paramTextOut->max_row;
                #if (MPLAYER_BITMAP_FORMAT == MPLAYER_I8)
                clrBtn1.t_clr = paramTextOut->TextColor&0xFF;
                #else //ZUI_ENABLE_PALETTE
                clrBtn1.t_clr = paramTextOut->TextColor;
                #endif //ZUI_ENABLE_PALETTE

                clrBtn1.Fontfmt.flag = paramTextOut->flag;
                clrBtn1.Fontfmt.ifont_gap = paramTextOut->u8dis;
                clrBtn1.bStringIndexWidth = CHAR_IDX_2BYTE;

                switch (paramTextOut->eTextAttrib)
                {
                    case eTextAlignLeft:
                        clrBtn1.enTextAlign = EN_ALIGNMENT_LEFT;
                        break;
                    case eTextAlignMiddle:
                    case eTextAlignMiddleWH:
                    case eTextAlignLeft_MiddleH:
                    case eTextAlignRight_MiddleH:
                        clrBtn1.enTextAlign = EN_ALIGNMENT_CENTER;
                        break;
                    case eTextAlignRight:
                        clrBtn1.enTextAlign = EN_ALIGNMENT_RIGHT;
                        break;
                    default:
                        clrBtn1.enTextAlign = EN_ALIGNMENT_DEFAULT;
                        break;
                }

                msAPI_OSD_DrawPunctuatedString_S2(Font[paramTextOut->eSystemFont].fHandle,
                    (U8*)paramTextOut->pString, &clrBtn1, paramTextOut->max_row);

            }
            break;


        case CP_BITMAP:
            {
                DRAW_BITMAP * paramBitmap = (DRAW_BITMAP*)param;

            #if (MPLAYER_BITMAP_FORMAT != MPLAYER_I8)
                U8 r_clr, g_clr, b_clr;
            #endif

            #if (MPLAYER_BITMAP_FORMAT == MPLAYER_ARGB4444 || MPLAYER_BITMAP_FORMAT == MPLAYER_ARGB8888)
                //for ARGB4444 and ARGB8888, use bitmap original alpha value
                if (pdc->bSrcAlphaReplaceDstAlpha)
                    MApi_GFX_SetAlpha(TRUE, COEF_ASRC, ABL_FROM_ASRC, 0);
                else
                    MApi_GFX_SetAlpha(TRUE, COEF_ASRC, ABL_FROM_ADST, 0);
            #elif (MPLAYER_BITMAP_FORMAT == MPLAYER_ARGB1555)
                U16 a = paramBitmap->u8Constant_Alpha;
                a *= pdc->u8ConstantAlpha;
                if (pdc->bSrcAlphaReplaceDstAlpha)
                    MApi_GFX_SetAlpha(TRUE, COEF_CONST, ABL_FROM_ASRC, a/255);
                else
                    MApi_GFX_SetAlpha(TRUE, COEF_CONST, ABL_FROM_ADST, a/255);
                MApi_GFX_SetAlpha_ARGB1555(0xFF); //for alpha channel of ARGB1555 bitblt
            #elif (MPLAYER_BITMAP_FORMAT == MPLAYER_I8)
                //for I8 palette mode, alpha disabled
                MApi_GFX_SetAlpha(FALSE, COEF_ASRC, ABL_FROM_ASRC, 0xFF);
            #else
                //for RGB565 and RGB555, constant alpha used
                if (pdc->u8ConstantAlpha != 0xFF || paramBitmap->u8Constant_Alpha != 0xFF)
                {
                    U16 a = paramBitmap->u8Constant_Alpha;
                    a *= pdc->u8ConstantAlpha;
                    MApi_GFX_SetAlpha(TRUE, COEF_CONST, ABL_FROM_CONST, a/255);
                }
            #endif

                clrBtn1.x = rect->left;
                clrBtn1.y = rect->top;

                gbmpfmt.width = rect->width;
                gbmpfmt.height = rect->height;

                gbmpfmt.bScale = TRUE;

                if ( paramBitmap->bSrcColorKey )
                {
                    gbmpfmt.bBmpColorKeyEnable = TRUE;

                #if (MPLAYER_BITMAP_FORMAT == MPLAYER_I8)
                    gbmpfmt.clrrange.color_s.a = 0;
                    gbmpfmt.clrrange.color_s.r = 0;
                    gbmpfmt.clrrange.color_s.g = 0;
                    gbmpfmt.clrrange.color_s.b = paramBitmap->srcColorKeyFrom & 0xFF;

                    gbmpfmt.clrrange.color_e.a = 0;
                    gbmpfmt.clrrange.color_e.r = 0;
                    gbmpfmt.clrrange.color_e.g = 0;
                    gbmpfmt.clrrange.color_e.b = paramBitmap->srcColorKeyEnd & 0xFF;

                #else
                    r_clr=((paramBitmap->srcColorKeyFrom&0x00ff0000)>>16)&0xff;
                    g_clr=((paramBitmap->srcColorKeyFrom&0x0000ff00)>>8)&0xff;
                    b_clr=((paramBitmap->srcColorKeyFrom&0x000000ff))&0xff;

                    gbmpfmt.clrrange.color_s.a = 0;
                    gbmpfmt.clrrange.color_s.r = r_clr;
                    gbmpfmt.clrrange.color_s.g = g_clr;
                    gbmpfmt.clrrange.color_s.b = b_clr;

                    r_clr=((paramBitmap->srcColorKeyEnd&0x00ff0000)>>16)&0xff;
                    g_clr=((paramBitmap->srcColorKeyEnd&0x0000ff00)>>8)&0xff;
                    b_clr=((paramBitmap->srcColorKeyEnd&0x000000ff))&0xff;

                    gbmpfmt.clrrange.color_e.a = 0;
                    gbmpfmt.clrrange.color_e.r = r_clr;
                    gbmpfmt.clrrange.color_e.g = g_clr;
                    gbmpfmt.clrrange.color_e.b = b_clr;
                #endif

                #if 0//(MPLAYER_BITMAP_FORMAT == MPLAYER_I8)
                    msAPI_OSD_DrawBitmap_I8(paramBitmap->u16BitmapIndex,
                        clrBtn1.x, clrBtn1.y, gbmpfmt);
                #else
                    msAPI_OSD_DrawColorKeyBitmap(paramBitmap->u16BitmapIndex,
                        clrBtn1.x, clrBtn1.y, gbmpfmt);
                #endif

                }
                else
                {
                    gbmpfmt.bBmpColorKeyEnable = FALSE;


                #if 0//(MPLAYER_BITMAP_FORMAT == MPLAYER_I8)
                    msAPI_OSD_DrawBitmap_I8(paramBitmap->u16BitmapIndex,
                        clrBtn1.x, clrBtn1.y, gbmpfmt);
                #else
                    msAPI_OSD_DrawColorKeyBitmap(paramBitmap->u16BitmapIndex,
                        clrBtn1.x, clrBtn1.y, gbmpfmt);
                #endif

                }

            #if (MPLAYER_BITMAP_FORMAT == MPLAYER_ARGB4444 || MPLAYER_BITMAP_FORMAT == MPLAYER_ARGB8888)
                MApi_GFX_SetAlpha(TRUE, COEF_CONST, ABL_FROM_CONST, 0xFF);
            #endif
            }
            break;

        /*case CP_ROUND_BAR:
            {
                DRAW_ROUND_BAR * param = (DRAW_ROUND_BAR*)style_list->param;
                MApi_Osd_DrawRoundBar(hdc->pGC,
                                rect,
                                UI_MENU_DRAW_COLOR_FMT,
                                param->colorFrom,
                                param->colorTo,
                                param->egradient,
                                param->bshadow,
                                param->eOSD_RoundBar,
                                hdc->pAlpha);
            }
            break;

        case CP_WINDOW:
            {
                DRAW_WINDOW * param = (DRAW_WINDOW*)style_list->param;
                MApi_Osd_DrawWindow(hdc->pGC,
                                UI_MENU_DRAW_COLOR_FMT,
                                rect,
                                param->titleHeight,
                                param->colorTitle,
                                param->colorBkgnd,
                                param->attrib,
                                param->BroderColor,
                                param->sizeBorder,
                                param->bShadow,
                                hdc->pAlpha);
            }
            break;*/

        case CP_RECT:
            {

                DRAW_RECT * paramRect = (DRAW_RECT*)param;

                clrBtn1.x = rect->left;
                clrBtn1.y = rect->top;

                clrBtn1.width = rect->width;
                clrBtn1.height = rect->height;
                clrBtn1.u8Gradient = paramRect->eRectGradient;
                clrBtn1.fHighLight = FALSE;

                clrBtn1.b_clr = paramRect->RcolorFrom;
                clrBtn1.g_clr = paramRect->RcolorTo;

                if (paramRect->attrib == eRectBorderRound &&
                    paramRect->radius > 0)
                {
                    clrBtn1.radius = paramRect->radius;
                    if (clrBtn1.u8Gradient == CONSTANT_COLOR)
                    {
                      #if (MPLAYER_BITMAP_FORMAT == MPLAYER_ARGB1555)
                             MApi_GFX_SetAlphaSrcFrom(ABL_FROM_CONST);
                             MApi_GFX_EnableAlphaBlending(TRUE);
                      #endif
                        msAPI_OSD_DrawRoundBlock(&clrBtn1);
                      #if (MPLAYER_BITMAP_FORMAT == MPLAYER_ARGB1555)
                             MApi_GFX_EnableAlphaBlending(FALSE);
                      #endif
                    }
                    else
                    {
                        //note: msAPI_OSD_DrawGradientRoundBlock() only support gradient_y
                        //      so we ignore radious....
                        #if (MPLAYER_BITMAP_FORMAT != MPLAYER_I8)
                        if ( clrBtn1.u8Gradient == OSD_COLOR_GRADIENT_Y )
                        {
                           #if (MPLAYER_BITMAP_FORMAT == MPLAYER_ARGB1555)
                             MApi_GFX_SetAlphaSrcFrom(ABL_FROM_CONST);
                             MApi_GFX_EnableAlphaBlending(TRUE);
                           #endif
                            msAPI_OSD_DrawGradientRoundBlock(&clrBtn1);
                           #if (MPLAYER_BITMAP_FORMAT == MPLAYER_ARGB1555)
                             MApi_GFX_EnableAlphaBlending(FALSE);
                           #endif
                        }
                        else
                        #endif
                        {
                            msAPI_OSD_DrawBlock(&clrBtn1);
                        }
                    }
                }
                else
                {
                    //clrBtn1.radius = 0;
                    msAPI_OSD_DrawBlock(&clrBtn1);
                }
            }
            break;

        /*case CP_DASH_BAR:
            {
                DRAW_DASH_BAR * param = (DRAW_DASH_BAR*)style_list->param;
                MApi_Osd_DrawDashBar(hdc->pGC,
                                UI_MENU_DRAW_COLOR_FMT,
                                rect,
                                param->colorFrom,
                                param->colorTo,
                                param->bXdirection,
                                param->dash_len,
                                hdc->pAlpha);
            }
            break;*/

        /*/case CP_TRIANGLE:
            {
                paramTriangle = (DRAW_TRIANGLE*)&_NewSkin_Triangle_List[u16Index];
                //PRINT("[CP_TRIANGLE] param=%X, color=%X\n", param, param->color);
                MApi_Osd_DrawTriangle(hdc->pGC,
                                UI_MENU_DRAW_COLOR_FMT,
                                paramTriangle->style,
                                rect,
                                paramTriangle->color,
                                hdc->pAlpha);
            }
            break;*/

        /*case CP_CIRCLE:
            {
                DRAW_CIRCLE * param = (DRAW_CIRCLE*)style_list->param;
                Pos center = { rect->left + rect->width/2, rect->top + rect->height/2 };
                MApi_Osd_DrawCircle(hdc->pGC,
                                &center,
                                MIN(rect->width, rect->height)/2 - 2, //avoiding shadow overlapping
                                UI_MENU_DRAW_COLOR_FMT,
                                param->colorFrom,
                                param->colorTo,
                                hdc->pAlpha,
                                param->bShadow);
            }
            break;

        case CP_ROUND_BORDER:
            {
                DRAW_ROUND_BORDER * param = (DRAW_ROUND_BORDER*)style_list->param;
                MApi_Osd_DrawRoundBorder(hdc->pGC,
                                param->radius,
                                rect,
                                param->u16BorderWidth,
                                UI_MENU_DRAW_COLOR_FMT,
                                param->BorderColor,
                                hdc->pAlpha);
            }
            break;*/
     #if TXTFONT_ZOOM2X
        case CP_ZOOM2X_PUNCTUATED_DYNAMIC:
            {
                //NOTE: we define CP_ZOOM2X_PUNCTUATED_DYNAMIC use original height with max row
                //      this component also automatically H-center,
                //      not the same as msAPI_OSD_DrawPunctuatedString() only define the first single height

                DRAW_PUNCTUATED_DYNAMIC * paramTextOut = (DRAW_PUNCTUATED_DYNAMIC*)param;
                GFX_TextOutInfo text_info;

                if (paramTextOut->max_row == 0) break;

                clrBtn1.x = rect->left + 2; //note: reserve 2 pixel for avoiding crop...
                clrBtn1.y = rect->top;
                clrBtn1.width = rect->width - 8; //note: reserve 8 pixel for avoiding crop...
                clrBtn1.height = rect->height / paramTextOut->max_row;
                #if (MPLAYER_BITMAP_FORMAT == MPLAYER_I8)
                clrBtn1.t_clr = paramTextOut->TextColor&0xFF;
                #else //ZUI_ENABLE_PALETTE
                clrBtn1.t_clr = paramTextOut->TextColor;
                #endif //ZUI_ENABLE_PALETTE
                clrBtn1.Fontfmt.flag = paramTextOut->flag;
                clrBtn1.Fontfmt.ifont_gap = paramTextOut->u8dis;
                clrBtn1.bStringIndexWidth = CHAR_IDX_2BYTE;

                switch (paramTextOut->eTextAttrib)
                {
                    case eTextAlignLeft:
                        clrBtn1.enTextAlign = EN_ALIGNMENT_LEFT;
                        break;
                    case eTextAlignMiddle:
                    case eTextAlignMiddleWH:
                    case eTextAlignLeft_MiddleH:
                    case eTextAlignRight_MiddleH:
                        clrBtn1.enTextAlign = EN_ALIGNMENT_CENTER;
                        break;
                    case eTextAlignRight:
                        clrBtn1.enTextAlign = EN_ALIGNMENT_RIGHT;
                        break;
                    default:
                        clrBtn1.enTextAlign = EN_ALIGNMENT_DEFAULT;
                        break;
                }

                MApi_GFX_SetStrBltSckType(GFX_DONOTHING,&text_info.color);
                msAPI_OSD_DrawPunctuatedString_Zoom2X(Font[paramTextOut->eSystemFont].fHandle,
                    (U8*)paramTextOut->pString, &clrBtn1, paramTextOut->max_row);
                MApi_GFX_SetStrBltSckType(GFX_NEAREST,&text_info.color);
            }
            break;
    #endif

        default:
            break;
    }
    MApi_GFX_SetDither (FALSE);
}

///////////////////////////////////////////////////////////////////////////////
///  private  _MApp_ZUI_API_ConvertTextComponentToDynamic
///  convert static "DRAW_TEXT_OUT" component to "DRAW_TEXT_OUT_DYNAMIC" component
///
///  @param [in]  u16TextOutIndex U16         built-in DRAW_TEXT_OUT component index
///  @param [out]  pComp DRAW_TEXT_OUT_DYNAMIC   user-defined DRAW_TEXT_OUT_DYNAMIC parameters
///
///  This function doesn't return a value
///
///  @author MStar @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
void _MApp_ZUI_API_ConvertTextComponentToDynamic(U16 u16TextOutIndex, DRAW_TEXT_OUT_DYNAMIC * pComp)
{
    DRAW_TEXT_OUT * paramTextOut = (DRAW_TEXT_OUT*)&_Zui_TextOut_List[u16TextOutIndex];
    //pComp->bShadow = paramTextOut->bShadow;
    pComp->eSystemFont = paramTextOut->eSystemFont;
    pComp->eTextAttrib = paramTextOut->eTextAttrib;
    pComp->flag = paramTextOut->flag;
    pComp->TextColor = paramTextOut->TextColor;
    pComp->u8dis = paramTextOut->u8dis;
    pComp->u8dots = EN_STRING_ENDING_3_DOT;
}

///////////////////////////////////////////////////////////////////////////////
///  private  _MApp_ZUI_API_ConvertTextComponentToPunctuated
///  convert static "DRAW_TEXT_OUT" component to "DRAW_PUNCTUATED_DYNAMIC" component
///
///  @param [in]  u16TextOutIndex U16         built-in DRAW_TEXT_OUT component index
///  @param [out]  pComp DRAW_TEXT_OUT_DYNAMIC   user-defined DRAW_PUNCTUATED_DYNAMIC parameters
///
///  This function doesn't return a value
///
///  @author MStar @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
void _MApp_ZUI_API_ConvertTextComponentToPunctuated(U16 u16TextOutIndex, DRAW_PUNCTUATED_DYNAMIC * pComp)
{
    DRAW_TEXT_OUT * paramTextOut = (DRAW_TEXT_OUT*)&_Zui_TextOut_List[u16TextOutIndex];
    //pComp->bShadow = paramTextOut->bShadow;
    pComp->eSystemFont = paramTextOut->eSystemFont;
    pComp->eTextAttrib = paramTextOut->eTextAttrib;
    pComp->flag = paramTextOut->flag;
    pComp->TextColor = paramTextOut->TextColor;
    pComp->u8dis = paramTextOut->u8dis;
}

/*
///////////////////////////////////////////////////////////////////////////////
///  private  _MApp_ZUI_API_ConvertBitmapComponentToDynamic
///  convert static "DRAW_BITMAP" component to dynamic component
///
///  @param [in]  u16CompIndex U16         built-in DRAW_BITMAP component index
///  @param [out]  pComp DRAW_BITMAP   user-defined DRAW_BITMAP parameters
///
///  This function doesn't return a value
///
///  @author MStar @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
void _MApp_ZUI_API_ConvertBitmapComponentToDynamic(U16 u16CompIndex , DRAW_BITMAP * pComp)
{
    DRAW_BITMAP * paramBitmap = (DRAW_BITMAP*)&_Zui_Bitmap_List[u16CompIndex];
    memcpy(pComp, paramBitmap, sizeof(DRAW_BITMAP));
}
*/

///////////////////////////////////////////////////////////////////////////////
///  private  _MApp_ZUI_API_ConvertComponentToDynamic
///  convert static component to dynamic component
///
///  @param [in]  comp DRAWCOMPONENT       built-in component type
///  @param [in]  u16CompIndex U16         built-in component index
///  @param [out]  pDraw void *            user-defined drawing structure
///
///  This function doesn't return a value
///
///  @author MStar @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
void _MApp_ZUI_API_ConvertComponentToDynamic(DRAWCOMPONENT comp, U16 u16CompIndex, void * pDraw)
{
    switch(comp)
    {
        case CP_BITMAP:
            memcpy(pDraw, &_Zui_Bitmap_List[u16CompIndex], sizeof(DRAW_BITMAP));
            break;
        case CP_RECT:
            memcpy(pDraw, &_Zui_Rect_List[u16CompIndex], sizeof(DRAW_RECT));
            break;
        case CP_FILL_RECT:
            memcpy(pDraw, &_Zui_FillRect_List[u16CompIndex], sizeof(DRAW_FILL_RECT));
            break;
        case CP_RECT_BORDER:
            memcpy(pDraw, &_Zui_RectBorder_List[u16CompIndex], sizeof(DRAW_RECT_BORDER));
            break;
        case CP_TEXT_OUT:
            memcpy(pDraw, &_Zui_TextOut_List[u16CompIndex], sizeof(DRAW_TEXT_OUT));
            break;
        default:
            break;
    }

}

#if ENABLE_ATSC
U16 MApp_ZUI_API_GetPuncStringLineAddrs(HWND hwnd, LPTSTR pstr, U8 u8RowNum)
{
    U16 u16rows;
    //DRAW_TEXT_OUT draw;
    OSDClrBtn clrBtn;
    DRAW_PUNCTUATED_DYNAMIC dyna;
    RECT rc = {0,0,0,0}; // Coverity CID 170290

    memset(&clrBtn, 0, sizeof(OSDClrBtn));

    MApp_ZUI_API_GetWindowRect(hwnd, &rc);

    U16 u16TxtComponentIndex = _MApp_ZUI_API_FindFirstComponentIndex(hwnd, DS_NORMAL, CP_TEXT_OUT);

//    _MApp_ZUI_API_ConvertComponentToDynamic(CP_TEXT_OUT, hwnd, &draw);
    _MApp_ZUI_API_ConvertTextComponentToPunctuated(u16TxtComponentIndex, &dyna);

    clrBtn.y = rc.top;
    clrBtn.width = rc.width - 8;
    clrBtn.height = rc.height / u8RowNum;
    clrBtn.t_clr = dyna.TextColor;
    clrBtn.enTextAlign = EN_ALIGNMENT_LEFT;

    clrBtn.bStringIndexWidth = CHAR_IDX_2BYTE;
    clrBtn.Fontfmt.flag = dyna.flag;
    clrBtn.Fontfmt.ifont_gap = dyna.u8dis;
//printf("clrBtn.Fontfmt.ifont_gap=%d\n", clrBtn.Fontfmt.ifont_gap);

    msAPI_OSD_GetPunctuatedStringRowsLine(Font[dyna.eSystemFont].fHandle, (U8*)pstr, &clrBtn, MAX_LINE_ADDDR_NUM, &u16rows);

    return u16rows;
}
#endif

#undef MAPP_ZUI_APIGUIDRAW_C
