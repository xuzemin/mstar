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

#define MAPP_ZUI_STYLETABLE_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


///////////////////////////////////////////////////////////////////////////////////////////////////
// Description: tables for GUI window/control layout and styles
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APItables.h"
#include "MApp_ZUI_APIstyletables.h"
#include "MApp_ZUI_APIcomponent.h"
#include "MApp_ZUI_APIdraw.h"
#include "MApp_ZUI_APIalphatables.h"
#include "MApp_ZUI_ACTglobal.h"

#include "OSDcp_String_EnumIndex.h" //#include "ZUI_strings_enum.h"
#include "MApp_ZUI_APIstrings.h"

#if ENABLE_ATSC_TTS
#include "Utl.h"
#include "MApp_TTSControlHandler.h"
#include "MApp_TTS_Cus.h"
#endif

///////////////////////////////////////////////////////////////////////////////
///  private  _MApp_ZUI_API_FindFirstComponentIndex
///  find first component index in a specific drawing style
///
///  @param [in]  hWnd HWND                 window handle
///  @param [in]  type DRAWSTYLE_TYPE         draw type: normal/disable/focus
///  @param [in]  comp DRAWCOMPONENT        draw component: ex: CP_TEXT_OUT
///
///  @return U16      component index, 0xFFFF for not found...
///
///  @author MStar @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
U16 _MApp_ZUI_API_FindFirstComponentIndex(HWND hWnd, DRAWSTYLE_TYPE type, DRAWCOMPONENT comp)
{
    DRAWSTYLE * style_list = 0;
    if (type == DS_DISABLE)
    {
        style_list = GETDISABLEDRAWSTYLE(hWnd);
    }
    else if (type == DS_FOCUS)
    {
        style_list = GETFOCUSDRAWSTYLE(hWnd);
    }
    else
    {
        style_list = GETNORMALDRAWSTYLE(hWnd);
    }

    if (style_list)
    {
        while(style_list->component != CP_NOON)
        {
            if (style_list->component == comp)
            {
                return style_list->u16Index;
            }
            style_list++;
        }
    }
    return 0xFFFF;
}


///////////////////////////////////////////////////////////////////////////////
///  private  _MApp_ZUI_API_DrawStyleList
///  draw a style array into GRAPHIC_DC (for bank issue, moved to the same as DEFUALT winproc)
///
///  @param [in]  pdc GRAPHIC_DC *    target GRAPHIC_DC wants to paint for
///  @param [in]  rect RECT *    target region wants to draw
///  @param [in]  style_list DRAWSTYLE *    array of style
///
///  This function doesn't return a value
///
///  @author MStar @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
void _MApp_ZUI_API_DrawStyleList(const GRAPHIC_DC * pdc, const RECT * rect, const DRAWSTYLE * style_list)
{
    if (!style_list)
        return;

    while(style_list->component != CP_NOON)
    {
        _MApp_ZUI_API_DrawComponent((DRAWCOMPONENT)style_list->component, style_list->u16Index, pdc, rect);
        style_list++;
    }
}

///////////////////////////////////////////////////////////////////////////////
///  private  _MApp_ZUI_API_DrawStyleListNoText
///  draw a style array into GRAPHIC_DC (for bank issue, moved to the same as DEFUALT winproc)
///
///  @param [in]  pdc GRAPHIC_DC *    target GRAPHIC_DC wants to paint for
///  @param [in]  rect RECT *    target region wants to draw
///  @param [in]  style_list DRAWSTYLE *    array of style
///
///  This function doesn't return a value
///
///  @author MStar @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
void _MApp_ZUI_API_DrawStyleListNoText(const GRAPHIC_DC * pdc, const RECT * rect, const DRAWSTYLE * style_list)
{
    if (!style_list)
        return;

    while(style_list->component != CP_NOON)
    {
        if (style_list->component != CP_TEXT_OUT &&
            style_list->component != CP_TEXT_OUT_DYNAMIC)
        {
            _MApp_ZUI_API_DrawComponent((DRAWCOMPONENT)style_list->component, style_list->u16Index, pdc, rect);
        }
        style_list++;
    }
}

///////////////////////////////////////////////////////////////////////////////
///  private  _MApp_ZUI_API_DefaultOnPaint
///  a default window procedure for MSG_PAINT,
///
///  @param [in]       hWnd HWND     window handle we are processing
///  @param [in]       param PAINT_PARAM *     MSG_PAINT drawing parameters
///  @param [in]       bDrawText BOOLEAN            draw background only (no CP_TEXT_OUT and CP_TEXT_OUT_DYNAMIC)
///
///  This function doesn't return a value
///
///  @author MStar @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
void _MApp_ZUI_API_DefaultOnPaint(HWND hWnd, PAINT_PARAM * param, BOOLEAN bDrawText)
{
    //get buffer GC for offline drawing...
    //const PAINT_PARAM * param = (const PAINT_PARAM*)pMsg->wParam;

    if (bDrawText)
    {
        if (param->bIsDisable)
        {
            param->dc.u8ConstantAlpha = MApp_ZUI_API_GetDisableAlpha(hWnd);
            _MApp_ZUI_API_DrawStyleList(&param->dc, param->rect, GETDISABLEDRAWSTYLE(hWnd));
        }
        else if (param->bIsFocus) //the same focus group
        {
            param->dc.u8ConstantAlpha = MApp_ZUI_API_GetFocusAlpha(hWnd);
            _MApp_ZUI_API_DrawStyleList(&param->dc, param->rect, GETFOCUSDRAWSTYLE(hWnd));
#if ENABLE_ATSC_TTS
            BOOLEAN bHasText = FALSE;
            DRAWSTYLE * style_list = 0;
            HWND focused = MApp_ZUI_API_GetFocus();
            if ((focused == MApp_ZUI_API_GetParent(hWnd)) || (focused == hWnd))
            {
                style_list = GETFOCUSDRAWSTYLE(hWnd);
                if (style_list)
                {
                    while(style_list->component != CP_NOON)
                    {
                        if ((style_list->component == CP_TEXT_OUT) || (style_list->component ==  CP_TEXT_OUT_DYNAMIC))
                        {
                            bHasText = TRUE;
                            break;
                        }
                        style_list++;
                    }
                }
            #if ENABLE_TTSTEST_FROM_USB
                if((MApp_ZUI_GetActiveOSD() == E_OSD_MAIN_MENU)&&(MApp_ZUI_API_IsSuccessor(HWND_MENU_TEST_TTS_PAGE, hWnd)))
                {
                    return;
                }
            #endif
                if(bHasText)
                {
                    DRAW_TEXT_OUT * paramTextOut = (DRAW_TEXT_OUT*)&_Zui_TextOut_List[style_list->u16Index];
                    MApp_TTS_Cus_Add_Str_By_StrId(paramTextOut->StringID);
                    MApp_TTSControlSetOn(TRUE);
                }
                if((MApp_ZUI_GetActiveOSD() == E_OSD_MAIN_MENU)&&(MApp_ZUI_API_IsSuccessor(HWND_MENU_LOCK_TVRATINGSUBPAGE, hWnd)))
                {
                    switch(hWnd)
                    {
                        case HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV_NONE_ALL_BG:
                            MApp_TTS_Cus_Add_Str_By_StrId(en_str_TVdashNone);
                            MApp_TTS_Cus_Add_Str_By_StrId(en_str_ALL_UNLOCK);
                            MApp_TTSControlSetOn(TRUE);
                            break;
                        case HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY_ALL_BG:
                            MApp_TTS_Cus_Add_Str_By_StrId(en_str_TVdashY);
                            MApp_TTS_Cus_Add_Str_By_StrId(en_str_ALL_UNLOCK);
                            MApp_TTSControlSetOn(TRUE);
                            break;
                        case HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_ALL_BG:
                            MApp_TTS_Cus_Add_Str_By_StrId(en_str_TVdashY7);
                            MApp_TTS_Cus_Add_Str_By_StrId(en_str_ALL_UNLOCK);
                            MApp_TTSControlSetOn(TRUE);
                            break;
                        case HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVG_ALL_BG:
                            MApp_TTS_Cus_Add_Str_By_StrId(en_str_TVdashG);
                            MApp_TTS_Cus_Add_Str_By_StrId(en_str_ALL_UNLOCK);
                            MApp_TTSControlSetOn(TRUE);
                            break;
                        case HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_ALL_BG:
                            MApp_TTS_Cus_Add_Str_By_StrId(en_str_TVdashPG);
                            MApp_TTS_Cus_Add_Str_By_StrId(en_str_ALL_UNLOCK);
                            MApp_TTSControlSetOn(TRUE);
                            break;
                        case HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_ALL_BG:
                            MApp_TTS_Cus_Add_Str_By_StrId(en_str_TVdash14);
                            MApp_TTS_Cus_Add_Str_By_StrId(en_str_ALL_UNLOCK);
                            MApp_TTSControlSetOn(TRUE);
                            break;
                        case HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_ALL_BG:
                            MApp_TTS_Cus_Add_UniStr_Format(MApp_ZUI_API_GetString(en_str_TVdashMA),EN_TTS_SPEAK_CHARACTERS);
                            MApp_TTS_Cus_Add_Str_By_StrId(en_str_ALL_UNLOCK);
                            MApp_TTSControlSetOn(TRUE);
                            break;
                        case HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVY7_FV_BG:
                            MApp_TTS_Cus_Add_Str_By_StrId(en_str_FV);
                            MApp_TTS_Cus_Add_Str_By_StrId(en_str_UNLOCK);
                            MApp_TTSControlSetOn(TRUE);
                            break;
                        case HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_V_BG:
                        case HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_V_BG:
                        case HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_V_BG:
                            MApp_TTS_Cus_Add_Str_By_StrId(en_str_V);
                            MApp_TTS_Cus_Add_Str_By_StrId(en_str_UNLOCK);
                            MApp_TTSControlSetOn(TRUE);
                            break;
                        case HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_S_BG:
                        case HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_S_BG:
                        case HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_S_BG:
                            MApp_TTS_Cus_Add_Str_By_StrId(en_str_S);
                            MApp_TTS_Cus_Add_Str_By_StrId(en_str_UNLOCK);
                            MApp_TTSControlSetOn(TRUE);
                            break;
                        case HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_L_BG:
                        case HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_L_BG:
                        case HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVMA_L_BG:
                            MApp_TTS_Cus_Add_Str_By_StrId(en_str_L);
                            MApp_TTS_Cus_Add_Str_By_StrId(en_str_UNLOCK);
                            MApp_TTSControlSetOn(TRUE);
                            break;
                        case HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TVPG_D_BG:
                        case HWND_MENU_LOCK_TVRATINGSUBPAGE_ITEM_TV14_D_BG:
                            MApp_TTS_Cus_Add_Str_By_StrId(en_str_D);
                            MApp_TTS_Cus_Add_Str_By_StrId(en_str_UNLOCK);
                            MApp_TTSControlSetOn(TRUE);
                            break;
                        default:
                            break;

                    }
                }
            }
#endif
        }
        else
        {
            param->dc.u8ConstantAlpha = MApp_ZUI_API_GetNormalAlpha(hWnd);
            _MApp_ZUI_API_DrawStyleList(&param->dc, param->rect, GETNORMALDRAWSTYLE(hWnd));
        }
    }
    else
    {
        if (param->bIsDisable)
        {
            param->dc.u8ConstantAlpha = MApp_ZUI_API_GetDisableAlpha(hWnd);
            _MApp_ZUI_API_DrawStyleListNoText(&param->dc, param->rect, GETDISABLEDRAWSTYLE(hWnd));
        }
        else if (param->bIsFocus) //the same focus group
        {
            param->dc.u8ConstantAlpha = MApp_ZUI_API_GetFocusAlpha(hWnd);
            _MApp_ZUI_API_DrawStyleListNoText(&param->dc, param->rect, GETFOCUSDRAWSTYLE(hWnd));
        }
        else
        {
            param->dc.u8ConstantAlpha = MApp_ZUI_API_GetNormalAlpha(hWnd);
            _MApp_ZUI_API_DrawStyleListNoText(&param->dc, param->rect, GETNORMALDRAWSTYLE(hWnd));
        }
    }

}

void _MApp_ZUI_API_ForceUpdateWindows(HWND aUpdateWindows[],U8 WinCount)
{
    U32 i;
    PAINT_PARAM paint_param;

    paint_param.dc = *MApp_ZUI_API_GetScreenDC();
    paint_param.dc.u8ConstantAlpha = 0xFF; //disable alpha blending
    //draw necessary windows
    for (i = 0; i < WinCount; i++)
    {

        RECT rect;
        MApp_ZUI_API_GetWindowRect(aUpdateWindows[i], &rect);
        paint_param.rect = &rect;

        paint_param.bIsVisible = TRUE;
        paint_param.bIsDisable = FALSE;
        paint_param.bIsFocus = FALSE;
        MApp_ZUI_API_SendMessage(aUpdateWindows[i], MSG_PAINT, (WPARAM)&paint_param);
    }
}

#undef MAPP_ZUI_STYLETABLE_C

