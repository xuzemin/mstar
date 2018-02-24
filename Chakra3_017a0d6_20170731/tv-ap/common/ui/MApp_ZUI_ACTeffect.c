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

#define MAPP_ZUI_ACTEFFECT_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_ACTmainpage.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_APIdraw.h"
#include "msAPI_Timer.h"
#include "apiGOP.h"
#include "MApp_UiMenuDef.h"
#include "OSDcp_Bitmap_EnumIndex.h"
#include "MApp_ZUI_APIalphatables.h"
#include "ZUI_exefunc.h"


    #if ENABLE_PVR
        #include "MApp_PVR.h"
    #endif

/////////////////////////////////////////////////////
//NOTE: must be the same bank with position table, because of GETWNDINITRECT()


#define ZUI_EFFECT_DBG_TIME_DIFF 0

static ZUI_TRANSEFFMODE _eTransEffectMode;
static ZUI_STATE _eAppTargetStateMenu;
static U32 _u32TransEffectTimer;
static U32 _u32TransEffectMonitorTimer;


//////////////////////////////////////////////////////////
// for effect: EN_EFFMODE_PAGE_SHOWUP
extern BOOLEAN _MApp_ZUI_API_WindowProcOnIdle(void);
extern ZUI_STATE _eZUIState;

U8 _u8TransitionStep;
#if ZUI_EFFECT_DBG_TIME_DIFF
static U32 _u32MainMenuPrevTime;
#endif //ZUI_EFFECT_DBG_TIME_DIFF

static U8 u8FbIdTmp = 0Xff;

#define MAIN_BG_ROTATE_MAX_STEP 8
#define MAIN_MENU_SHOW_UP_STEP (20+8) //16
#define MAIN_MENU_FADE_OUT_STEP 8
#define MAIN_MENU_FADE_IN_STEP 32
#define MAIN_MENU_CUBE_STEP 32

#define MAIN_MENU_STYLE6_ROW 30 //size should be ROW+CEIL(COl)
#define MAIN_MENU_STYLE6_COL 21 //odd integer is better

#define LIST_SHOW_UP_STEP (LIST_SHOW_UP_RIGHT+LIST_SHOW_UP_DOWN)
#define LIST_SHOW_UP_RIGHT 10
#define LIST_SHOW_UP_DOWN   20
#define LIST_SHOW_UP_BANNER_HEIGHT (45+46)
#define LIST_SHOW_UP_DOWN_RATE 3

#define MSGBOX_SHOW_UP_STEP 10
#define MSGBOX_SHOW_UP_LR_RATE 3

#define MSGBOX_ZOOM_IN_STEP 32
#define MSGBOX_ZOOM_OUT_STEP 16

#define MSGBOX_SPREAD_OUT_STEP 32
#define MSGBOX_ROLL_UP_STEP 16

#define MSGBOX_MOSAIC_STEP 32

#define MSGBOX_EXIT_UP_STEP  32
#define MSGBOX_EXIT_DOWN_STEP  32
#define MSGBOX_EXIT_LEFT_STEP  32
#define MSGBOX_EXIT_RIGHT_STEP  32

#define MSGBOX_ENTER_UP_STEP  32
#define MSGBOX_ENTER_DOWN_STEP  32
#define MSGBOX_ENTER_LEFT_STEP  32
#define MSGBOX_ENTER_RIGHT_STEP  32

typedef enum
{
    ALT_LL2LR,
    ALT_LR2RR,
    ALT_RR2LL,
    ALT_RR2LR,
    ALT_LL2RR,
    ALT_LR2LL,
    ALT_Invalid,
} AudioLangTrans;

AudioLangTrans ALTpara = ALT_Invalid;

typedef struct _MENU_FOCUS2ICON1_STRUCT
{
    HWND hwndsrc;
    HWND hwnddest;
} MENU_FOCUS2ICON1_STRUCT;

//Reminder: CUBE effect is only for testing. We also do not use in Chakra2 UI2 project.
//          Because below array struct is written in specific HWND and cannot port to
//          ATSC project, we use ATSC_SYSTEM define to seperate codes.
#ifndef ATSC_SYSTEM
static  MENU_FOCUS2ICON1_STRUCT _ZUI_TBLSEG _focus2icon1[] =
{
    {HWND_AUDLANG_LIST_ITEM0, HWND_AUDLANG_ITEM0_L_SOUND_ICON},
    {HWND_AUDLANG_LIST_ITEM1, HWND_AUDLANG_ITEM1_L_SOUND_ICON},
    {HWND_AUDLANG_LIST_ITEM2, HWND_AUDLANG_ITEM2_L_SOUND_ICON},
    {HWND_AUDLANG_LIST_ITEM3, HWND_AUDLANG_ITEM3_L_SOUND_ICON},
    {HWND_AUDLANG_LIST_ITEM4, HWND_AUDLANG_ITEM4_L_SOUND_ICON},
};

static  MENU_FOCUS2ICON1_STRUCT _ZUI_TBLSEG _focus2icon2[] =
{
    {HWND_AUDLANG_LIST_ITEM0, HWND_AUDLANG_ITEM0_R_SOUND_ICON},
    {HWND_AUDLANG_LIST_ITEM1, HWND_AUDLANG_ITEM1_R_SOUND_ICON},
    {HWND_AUDLANG_LIST_ITEM2, HWND_AUDLANG_ITEM2_R_SOUND_ICON},
    {HWND_AUDLANG_LIST_ITEM3, HWND_AUDLANG_ITEM3_R_SOUND_ICON},
    {HWND_AUDLANG_LIST_ITEM4, HWND_AUDLANG_ITEM4_R_SOUND_ICON},
};
#endif

extern void _MApp_ZUI_API_DefaultOnPaint(HWND hWnd, PAINT_PARAM * param, BOOLEAN bDrawText);

//extern U16 TopIconAlpha[2][2];
#if 0 //performanc is not good...
///////////////////////////////////////////////////////////////////////////////
///  private  _MApp_ZUI_ACT_CopyRegionScaleV
///    copy framebuffer region with V scaling: assume width is the same!!
///
///  @param [in] src   MSAPI_OSDRegion *     source framebuffer
///  @param [in] dst   MSAPI_OSDRegion *     destenation framebuffer
///
///  @return no return value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
static void _MApp_ZUI_ACT_CopyRegionScaleV(MSAPI_OSDRegion *src, MSAPI_OSDRegion *dst)
{
    S16 src_h = src->height, dst_h = dst->height;
    S16 src_y = src->y, dst_y = dst->y;
    S16 dst_i;
    src->height = dst->height = 1; //one scanline copy
    for (dst_i = dst_h; --dst_i >= 0; )
    {
        S16 src_i = (S32)dst_i*(src_h-1)/(dst_h-1);

        src->y = src_y+src_i;
        dst->y = dst_y+dst_i;

        //we MUST reset clip window before msAPI_OSD_CopyRegion()
        msAPI_OSD_SetClipWindow(
            dst->x, dst->y,
            dst->x+dst->width, dst->y+dst->height);

        msAPI_OSD_CopyRegion(src, dst);

    }
    src->height = src_h;
    src->y = src_y;
    dst->height = dst_h;
    dst->y = dst_y;
}

///////////////////////////////////////////////////////////////////////////////
///  private  _MApp_ZUI_ACT_CopyRegionScaleH
///    copy framebuffer region with H scaling: assume height is the same!!
///
///  @param [in] src   MSAPI_OSDRegion *     source framebuffer
///  @param [in] dst   MSAPI_OSDRegion *     destenation framebuffer
///
///  @return no return value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
static void _MApp_ZUI_ACT_CopyRegionScaleH(MSAPI_OSDRegion *src, MSAPI_OSDRegion *dst)
{
    S16 src_w = src->width, dst_w = dst->width;
    S16 src_x = src->x, dst_x = dst->x;
    S16 dst_i;
    src->width = dst->width = 1; //one scanline copy
    for (dst_i = dst_w; --dst_i >= 0; )
    {
        S16 src_i = (S32)dst_i*(src_w-1)/(dst_w-1);

        src->x = src_x+src_i;
        dst->x = dst_x+dst_i;

        //we MUST reset clip window before msAPI_OSD_CopyRegion()
        msAPI_OSD_SetClipWindow(
            dst->x, dst->y,
            dst->x+1/*dst->width*/, dst->y+dst->height);

        msAPI_OSD_CopyRegion(src, dst);

    }
    src->width = src_w;
    src->x = src_x;
    dst->width = dst_w;
    dst->x = dst_x;
}
#endif

///////////////////////////////////////////////////////////////////////////////
///  private  _MApp_ZUI_ACT_TransitionPrepareBufferDC
///  prepare background framebuffer for transition effect
///
///  @return no return value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////
#ifndef ATSC_SYSTEM
static HWND _MApp_ZUI_ACT_Focus2Icon1(HWND hwndsrc)
{
    U8 i;
        for (i = 0; i < COUNTOF(_focus2icon1); i++)
        {
            if (_focus2icon1[i].hwndsrc == hwndsrc)
            {
                return _focus2icon1[i].hwnddest;
            }
        }

    return MApp_ZUI_API_GetFocus();
}

static HWND _MApp_ZUI_ACT_Focus2Icon2(HWND hwndsrc)
{
    U8 i;
        for (i = 0; i < COUNTOF(_focus2icon2); i++)
        {
            if (_focus2icon2[i].hwndsrc == hwndsrc)
            {
                return _focus2icon2[i].hwnddest;
            }
        }

    return MApp_ZUI_API_GetFocus();
}

static HWND _MApp_ZUI_ACT_Focus2Index1(HWND hwndsrc)
{
    U8 i;
        for (i = 0; i < COUNTOF(_focus2icon1); i++)
        {
            if (_focus2icon1[i].hwndsrc == hwndsrc)
            {
                return i;
            }
        }

    return 0xff;
}

static HWND _MApp_ZUI_ACT_Focus2Index2(HWND hwndsrc)
{
    U8 i;
        for (i = 0; i < COUNTOF(_focus2icon2); i++)
        {
            if (_focus2icon2[i].hwndsrc == hwndsrc)
            {
                return i;
            }
        }

    return 0xff;
}
#endif

static ZUI_TRANSEFFMODE _TransitionEffectOpenMapping(U32 effect_id)
{
    switch (effect_id)
    {
        case E_TRANSEFF_IN_SPREAD_OUT:
            return EN_EFFMODE_PAGE_SPREAD_OUT;
        case E_TRANSEFF_IN_FADE_IN:
            return EN_EFFMODE_PAGE_FADE_IN;
        case E_TRANSEFF_IN_ENTER_UP:
            return EN_EFFMODE_PAGE_ENTER_UP;
        case E_TRANSEFF_IN_ENTER_DOWN:
            return EN_EFFMODE_PAGE_ENTER_DOWN;
        case E_TRANSEFF_IN_ENTER_LEFT:
            return EN_EFFMODE_PAGE_ENTER_LEFT;
        case E_TRANSEFF_IN_ENTER_RIGHT:
            return EN_EFFMODE_PAGE_ENTER_RIGHT;

        default:
            break;
    }

    return EN_EFFMODE_NONE;
}

static ZUI_TRANSEFFMODE _TransitionEffectCloseMapping(U32 effect_id)
{
    switch (effect_id)
    {
        case E_TRANSEFF_OUT_ROLL_UP:
            return EN_EFFMODE_PAGE_ROLL_UP;
        case E_TRANSEFF_OUT_FADE_OUT:
            return EN_EFFMODE_PAGE_FADE_OUT;
        case E_TRANSEFF_OUT_EXIT_UP:
            return EN_EFFMODE_PAGE_EXIT_UP;
        case E_TRANSEFF_OUT_EXIT_DOWN:
            return EN_EFFMODE_PAGE_EXIT_DOWN;
        case E_TRANSEFF_OUT_EXIT_LEFT:
            return EN_EFFMODE_PAGE_EXIT_LEFT;
        case E_TRANSEFF_OUT_EXIT_RIGHT:
            return EN_EFFMODE_PAGE_EXIT_RIGHT;

        default:
            break;
    }

    return EN_EFFMODE_NONE;
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_ACT_TransitionEffectBegin
///  transition begin state handler, provide different kinds of transition initialization
///
///  @param [in]       mode ZUI_TRANSEFFMODE     transition mode
///  @param [in]       target ZUI_STATE          target ZUI state
///
///  @return no return value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////

void MApp_ZUI_ACT_TransitionEffectBegin(ZUI_TRANSEFFMODE mode, ZUI_STATE target)
{
    //note: called from MApp_Menu_MainTask(),
    //      you can customize the transition effect by your self...
    //      you CANNOT do anything send message!

#if (ENABLE_UI_3D_PROCESS)
    if(MApp_ZUI_API_Is_UI_3D_Mode_ON())
    {
        if(mode == EN_EFFMODE_CLOSE)
            mode = EN_EFFMODE_PAGE_EXIT;
        else
            return;
    }
#endif

    //printf("EffBegin\n");
    //printf("target=%bx\n",target);
    //printf("_eTransEffectMode=%bx\n",_eTransEffectMode);
    _eAppTargetStateMenu = target;
  #ifdef ATSC_SYSTEM
  #if TRUNK_UI2
    if(mode == EN_EFFMODE_MAIN_BG_ROTATE)
  #else
    if(mode != EN_EFFMODE_MAIN_BG_ROTATE)
  #endif
  #else
#if (ENABLE_MAINPAGE_EFFECT)
    if (stGenSetting.g_SysSetting.fEnableOsdAnimation == EN_OSD_EFFECT_ROTATION_ONLY)
#endif
  #endif
    {
        MApp_ZUI_ACT_TransitionEffectEnd();
        return;
    }

    _u32TransEffectMonitorTimer = msAPI_Timer_GetTime0();

    _eTransEffectMode = mode;
    _eZUIState = E_ZUI_STATE_TRANSEFF_DOING;

    #if ZUI_EFFECT_DBG_TIME_DIFF
    _u32MainMenuPrevTime = msAPI_Timer_GetTime0();
    #endif

    switch( _eTransEffectMode )
    {
        case EN_EFFMODE_PAGE_SHOWUP:
            _u8TransitionStep = MAIN_MENU_SHOW_UP_STEP;
            break;

        case EN_EFFMODE_MAIN_BG_ROTATE:
            _u8TransitionStep = MAIN_BG_ROTATE_MAX_STEP;
            _u32TransEffectTimer = msAPI_Timer_GetTime0();
            break;

        case EN_EFFMODE_PAGE_FADE_OUT:
            _u8TransitionStep = MAIN_MENU_FADE_OUT_STEP;
            break;

        case EN_EFFMODE_LIST_SHOWUP:
            _u8TransitionStep = LIST_SHOW_UP_STEP;
            _u32TransEffectTimer = msAPI_Timer_GetTime0();
            break;

        case EN_EFFMODE_MSGBOX_SHOWUP:
            _u8TransitionStep = MSGBOX_SHOW_UP_STEP;
            break;

        case EN_EFFMODE_PAGE_FADE_IN:
            _u8TransitionStep = MAIN_MENU_FADE_IN_STEP;
            _u32TransEffectTimer = msAPI_Timer_GetTime0();
            break;

        case EN_EFFMODE_CUBE:
            {
              #ifdef ATSC_SYSTEM
              #if(TRUNK_UI2)
                _u8TransitionStep = MAIN_MENU_CUBE_STEP;
                _u32TransEffectTimer = msAPI_Timer_GetTime0();
              #endif
              #else
                _u8TransitionStep = MAIN_MENU_CUBE_STEP;
                _u32TransEffectTimer = msAPI_Timer_GetTime0();
              #endif
            }
            break;

        case EN_EFFMODE_PAGE_ZOOM_IN:
            _u8TransitionStep = MSGBOX_ZOOM_IN_STEP;
            _u32TransEffectTimer = msAPI_Timer_GetTime0();
            break;

        case EN_EFFMODE_PAGE_ZOOM_OUT:
            _u8TransitionStep = MSGBOX_ZOOM_OUT_STEP;
            break;

        case EN_EFFMODE_PAGE_SPREAD_OUT:
            _u8TransitionStep = MSGBOX_SPREAD_OUT_STEP;
            _u32TransEffectTimer = msAPI_Timer_GetTime0();
            break;

        case EN_EFFMODE_PAGE_ROLL_UP:
            _u8TransitionStep = MSGBOX_ROLL_UP_STEP;
            break;

        case EN_EFFMODE_PAGE_MOSAIC:
            _u8TransitionStep = MSGBOX_MOSAIC_STEP;
            _u32TransEffectTimer = msAPI_Timer_GetTime0();
            break;

        case EN_EFFMODE_PAGE_EXIT_UP:
            _u8TransitionStep = MSGBOX_EXIT_UP_STEP;
            _u32TransEffectTimer = msAPI_Timer_GetTime0();
            _eTransEffectMode = EN_EFFMODE_PAGE_EXIT_UP;
            break;

        case EN_EFFMODE_PAGE_EXIT_DOWN:
            _u8TransitionStep = MSGBOX_EXIT_DOWN_STEP;
            _u32TransEffectTimer = msAPI_Timer_GetTime0();
            _eTransEffectMode = EN_EFFMODE_PAGE_EXIT_DOWN;
            break;

        case EN_EFFMODE_PAGE_EXIT_LEFT:
            _u8TransitionStep = MSGBOX_EXIT_LEFT_STEP;
            _u32TransEffectTimer = msAPI_Timer_GetTime0();
            _eTransEffectMode = EN_EFFMODE_PAGE_EXIT_LEFT;
            break;

        case EN_EFFMODE_PAGE_EXIT_RIGHT:
            _u8TransitionStep = MSGBOX_EXIT_RIGHT_STEP;
            _u32TransEffectTimer = msAPI_Timer_GetTime0();
            _eTransEffectMode = EN_EFFMODE_PAGE_EXIT_RIGHT;
            break;

        case EN_EFFMODE_PAGE_ENTER_UP:
            _u8TransitionStep = MSGBOX_ENTER_UP_STEP;
            _u32TransEffectTimer = msAPI_Timer_GetTime0();
            _eTransEffectMode = EN_EFFMODE_PAGE_ENTER_UP;
            break;

        case EN_EFFMODE_PAGE_ENTER_DOWN:
            _u8TransitionStep = MSGBOX_ENTER_DOWN_STEP;
            _u32TransEffectTimer = msAPI_Timer_GetTime0();
            _eTransEffectMode = EN_EFFMODE_PAGE_ENTER_DOWN;
            break;

        case EN_EFFMODE_PAGE_ENTER_LEFT:
            _u8TransitionStep = MSGBOX_ENTER_LEFT_STEP;
            _u32TransEffectTimer = msAPI_Timer_GetTime0();
            _eTransEffectMode = EN_EFFMODE_PAGE_ENTER_LEFT;
            break;

        case EN_EFFMODE_PAGE_ENTER_RIGHT:
            _u8TransitionStep = MSGBOX_ENTER_RIGHT_STEP;
            _u32TransEffectTimer = msAPI_Timer_GetTime0();
            _eTransEffectMode = EN_EFFMODE_PAGE_ENTER_RIGHT;
            break;

        case EN_EFFMODE_OPEN:
            {
                U32 osd_id = MApp_ZUI_GetActiveOSD();
                U32 effect_id = GetOsdTableTransEffIn(osd_id);

            #if ENABLE_PVR//@@-- When it is Recording or playbacking state, disable the effect mode
                if((MApp_PVR_IsRecording()||MApp_PVR_IsPlaybacking()))
                    {
                        effect_id=effect_id;
                        _eTransEffectMode=EN_EFFMODE_NONE;
                    }
                else
            #endif

                    {
                _eTransEffectMode = _TransitionEffectOpenMapping(effect_id);
                     }
                _u32TransEffectTimer = msAPI_Timer_GetTime0();

                switch (_eTransEffectMode)
                {
                    case EN_EFFMODE_PAGE_SPREAD_OUT:
                        _u8TransitionStep = MSGBOX_SPREAD_OUT_STEP;
                        break;

                    case EN_EFFMODE_PAGE_FADE_IN:
                        //Delay some time for zui msg dispatch.
                        msAPI_Timer_Delayms(5);
                        _u8TransitionStep = MAIN_MENU_FADE_IN_STEP;
                        break;

                    case EN_EFFMODE_PAGE_MOSAIC:
                        _u8TransitionStep = MSGBOX_MOSAIC_STEP;
                        break;

                    case EN_EFFMODE_PAGE_ZOOM_IN:
                        _u8TransitionStep = MSGBOX_ZOOM_IN_STEP;
                        break;

                    case EN_EFFMODE_PAGE_ENTER_UP:
                        _u8TransitionStep = MSGBOX_ENTER_UP_STEP;
                        break;

                    case EN_EFFMODE_PAGE_ENTER_DOWN:
                        _u8TransitionStep = MSGBOX_ENTER_DOWN_STEP;
                        break;

                    case EN_EFFMODE_PAGE_ENTER_LEFT:
                        _u8TransitionStep = MSGBOX_ENTER_LEFT_STEP;
                        break;

                    case EN_EFFMODE_PAGE_ENTER_RIGHT:
                        _u8TransitionStep = MSGBOX_ENTER_RIGHT_STEP;
                        break;

                    default:
                        _eTransEffectMode = EN_EFFMODE_NONE;
                        break;
                }
            }
            break;

        case EN_EFFMODE_CLOSE:
            {
                U32 osd_id = MApp_ZUI_GetActiveOSD();
                U32 effect_id = GetOsdTableTransEffOut(osd_id);


            #if ENABLE_PVR
                if((MApp_PVR_IsRecording()||MApp_PVR_IsPlaybacking()))
                    {
                        effect_id=effect_id;
                        _eTransEffectMode=EN_EFFMODE_NONE;
                    }
                else
            #endif

                    {
                _eTransEffectMode = _TransitionEffectCloseMapping(effect_id);
                     }
                _u32TransEffectTimer = msAPI_Timer_GetTime0();

                switch (_eTransEffectMode)
                {
                    case EN_EFFMODE_PAGE_ROLL_UP:
                        _u8TransitionStep = MSGBOX_ROLL_UP_STEP;
                        break;

                    case EN_EFFMODE_PAGE_FADE_OUT:
                        _u8TransitionStep = MAIN_MENU_FADE_OUT_STEP;
                        break;

                    case EN_EFFMODE_PAGE_ZOOM_OUT:
                        _u8TransitionStep = MSGBOX_ZOOM_OUT_STEP;
                        break;

                    case EN_EFFMODE_PAGE_EXIT_UP:
                        _u8TransitionStep = MSGBOX_EXIT_UP_STEP;
                        break;

                    case EN_EFFMODE_PAGE_EXIT_DOWN:
                        _u8TransitionStep = MSGBOX_EXIT_DOWN_STEP;
                        break;

                    case EN_EFFMODE_PAGE_EXIT_LEFT:
                        _u8TransitionStep = MSGBOX_EXIT_LEFT_STEP;
                        break;

                    case EN_EFFMODE_PAGE_EXIT_RIGHT:
                        _u8TransitionStep = MSGBOX_EXIT_RIGHT_STEP;
                        break;

                    default:
                        _eTransEffectMode = EN_EFFMODE_NONE;
                        break;
                }
            }
            break;

        case EN_EFFMODE_PAGE_EXIT:
            //do nothing, go on next
        default:
            //printf("_eTransEffectMode=%x\n",_eTransEffectMode);
            MApp_ZUI_ACT_TransitionEffectEnd();
            return;
    }
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_ACT_TransitionEffectDoing
///  transition doing handler, provide differenct kind of transition effect algorithms
///
///  @return no return value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////

void MApp_ZUI_ACT_TransitionEffectDoing(void)
{
    //note: called from MApp_Menu_MainTask(),
    //      you can customize the transition effect by your self...

    //2007/12/26: consider gop switching
    U8 u8PrevGopID = MApi_GOP_GWIN_GetCurrentGOP();
    GOP_GwinFBAttr fbAttr;
    GRAPHIC_DC *pBuffDC = NULL;
    GRAPHIC_DC *pScrnDC = NULL;
    ZUI_MSG(printf("AEON busy! timer=%ld %d\n",msAPI_Timer_DiffTimeFromNow(_u32TransEffectMonitorTimer),_u8TransitionStep));
    if (msAPI_Timer_DiffTimeFromNow(_u32TransEffectMonitorTimer) > 220
    && (_eTransEffectMode == EN_EFFMODE_PAGE_FADE_IN)
    )
    {
        _u8TransitionStep = 1;
    }
    if (msAPI_Timer_DiffTimeFromNow(_u32TransEffectMonitorTimer) > 110
        && (_eTransEffectMode != EN_EFFMODE_MAIN_BG_ROTATE)
        && (_eTransEffectMode != EN_EFFMODE_PAGE_FADE_IN)
        /*&& (_eTransEffectMode != EN_EFFMODE_PAGE_FADE_OUT)*/
        && (_eTransEffectMode != EN_EFFMODE_PAGE_ZOOM_IN)
        && (_eTransEffectMode != EN_EFFMODE_PAGE_ZOOM_OUT)
        /*&& (_eTransEffectMode != EN_EFFMODE_PAGE_SPREAD_OUT)*/
        /*&& (_eTransEffectMode != EN_EFFMODE_PAGE_ROLL_UP)*/
        && (_eTransEffectMode != EN_EFFMODE_PAGE_EXIT_UP)
        && (_eTransEffectMode != EN_EFFMODE_PAGE_EXIT_DOWN)
        && (_eTransEffectMode != EN_EFFMODE_PAGE_EXIT_LEFT)
        /*&& (_eTransEffectMode != EN_EFFMODE_PAGE_EXIT_RIGHT)*/
        && (_eTransEffectMode != EN_EFFMODE_PAGE_ENTER_UP)
        && (_eTransEffectMode != EN_EFFMODE_PAGE_ENTER_DOWN)
        && (_eTransEffectMode != EN_EFFMODE_PAGE_ENTER_LEFT)
        /*&& (_eTransEffectMode != EN_EFFMODE_PAGE_ENTER_RIGHT)*/
        && (_eTransEffectMode != EN_EFFMODE_PAGE_MOSAIC))
    {//if spend too much time in other task, disable
        //ZUI_MSG(printf("AEON busy! timer=%ld\n",msAPI_Timer_DiffTimeFromNow(_u32TransEffectMonitorTimer)));
        //MApp_ZUI_ACT_TransitionEffectEnd();
        _u8TransitionStep = 1;
        //return;
    }

    _u32TransEffectMonitorTimer = msAPI_Timer_GetTime0();

    if (u8PrevGopID != OSD_GOP_ID)
        MApi_GOP_GWIN_SwitchGOP(OSD_GOP_ID);

    switch( _eTransEffectMode )
    {

        case EN_EFFMODE_PAGE_SHOWUP:
        {
            #if ZUI_EFFECT_DBG_TIME_DIFF
            //printf("time_diff=%lu\n", msAPI_Timer_GetTime0()-_u32MainMenuPrevTime);
            _u32MainMenuPrevTime = msAPI_Timer_GetTime0();
            #endif //ZUI_EFFECT_DBG_TIME_DIFF
            if (_u8TransitionStep == MAIN_MENU_SHOW_UP_STEP)
            {
                MApp_ZUI_API_PrepareBufferDC(MApp_ZUI_API_GetBufferDC());
            }
            _u8TransitionStep--;
            /*{ //style 1: show block 4x4
                U8 yy = _u8TransitionStep/4;
                U8 xx = _u8TransitionStep%4;
                const RECT *rect = &GETWNDINITRECT(HWND_MAINFRAME);
                U16 ww = rect->width/4;
                U16 hh = rect->height/4;
                pBuffDC = MApp_ZUI_API_GetBufferDC();
                pScrnDC = MApp_ZUI_API_GetScreenDC();
                MSAPI_OSDRegion CopyFB;
                MSAPI_OSDRegion PasteFB;

                //printf("[]ww=%u,hh=%u\n", ww, hh);

                //we MUST reset clip window before msAPI_OSD_CopyRegion()
                msAPI_OSD_SetClipWindow(
                    ww*xx, hh*yy,
                    ww*(xx+1), hh*(yy+1) );

                PasteFB.fbID=pScrnDC->u8FbID;
                PasteFB.x=ww*xx;
                PasteFB.y=hh*yy;
                PasteFB.width=ww;
                PasteFB.height=hh;

                CopyFB.fbID=pBuffDC->u8FbID;
                CopyFB.x=ww*xx;
                CopyFB.y=hh*yy;
                CopyFB.width=ww;
                CopyFB.height=hh;
                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                MApp_ZUI_API_ReleaseWithoutUpdateDC();
            }*/
            /*{ //style 2: show 16 rows
                U8 i;
                const RECT *rect = &GETWNDINITRECT(HWND_MAINFRAME);
                U16 hh = rect->height/MAIN_MENU_SHOW_UP_STEP;
                U16 hshow = hh*(MAIN_MENU_SHOW_UP_STEP-_u8TransitionStep)/MAIN_MENU_SHOW_UP_STEP ;
                pBuffDC = MApp_ZUI_API_GetBufferDC();
                pScrnDC = MApp_ZUI_API_GetScreenDC();
                MSAPI_OSDRegion CopyFB;
                MSAPI_OSDRegion PasteFB;

                //printf("hshow=%u\n", hshow);

                for (i = 0; i < MAIN_MENU_SHOW_UP_STEP; i++)
                {
                    //we MUST reset clip window before msAPI_OSD_CopyRegion()
                    msAPI_OSD_SetClipWindow(
                        0, hh*i,
                        rect->width, hh*i+hshow);

                    PasteFB.fbID=pScrnDC->u8FbID;
                    PasteFB.x=0;
                    PasteFB.y=hh*i;
                    PasteFB.width=rect->width;
                    PasteFB.height=hshow;

                    CopyFB.fbID=pBuffDC->u8FbID;
                    CopyFB.x=0;
                    CopyFB.y=hh*i;
                    CopyFB.width=rect->width;
                    CopyFB.height=hshow;
                    msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                }
                MApp_ZUI_API_ReleaseWithoutUpdateDC();
            }*/
            /*{ //style 3: slide down
                const RECT *rect = &GETWNDINITRECT(HWND_MAINFRAME);
                U16 hh = rect->height*(MAIN_MENU_SHOW_UP_STEP-_u8TransitionStep)/MAIN_MENU_SHOW_UP_STEP ;
                pBuffDC = MApp_ZUI_API_GetBufferDC();
                pScrnDC = MApp_ZUI_API_GetScreenDC();
                MSAPI_OSDRegion CopyFB;
                MSAPI_OSDRegion PasteFB;

                //printf("hh=%u\n", hh);

                //we MUST reset clip window before msAPI_OSD_CopyRegion()
                msAPI_OSD_SetClipWindow(
                    0, 0,
                    rect->width, hh );

                PasteFB.fbID=pScrnDC->u8FbID;
                PasteFB.x=0;
                PasteFB.y=0;
                PasteFB.width=rect->width;
                PasteFB.height=hh;

                CopyFB.fbID=pBuffDC->u8FbID;
                CopyFB.x=0;
                CopyFB.y=rect->height-hh;
                CopyFB.width=rect->width;
                CopyFB.height=hh;
                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                MApp_ZUI_API_ReleaseWithoutUpdateDC();
            }*/
            /*{ //style 4: zoom in:  OSD API NOT ALLOW ZOOM BITBLT
                const RECT *rect = &GETWNDINITRECT(HWND_MAINFRAME);
                U16 ww = rect->width*(MAIN_MENU_SHOW_UP_STEP-_u8TransitionStep)/MAIN_MENU_SHOW_UP_STEP ;
                U16 hh = rect->height*(MAIN_MENU_SHOW_UP_STEP-_u8TransitionStep)/MAIN_MENU_SHOW_UP_STEP ;
                U16 xx = (rect->width-ww)/2;
                U16 yy = (rect->height-hh)/2;
                pBuffDC = MApp_ZUI_API_GetBufferDC();
                pScrnDC = MApp_ZUI_API_GetScreenDC();
                MSAPI_OSDRegion CopyFB;
                MSAPI_OSDRegion PasteFB;

                //printf("[]ww=%u,hh=%u\n", ww, hh);

                //we MUST reset clip window before msAPI_OSD_CopyRegion()
                msAPI_OSD_SetClipWindow(
                    xx, yy, xx+ww, yy+hh );

                PasteFB.fbID=pScrnDC->u8FbID;
                PasteFB.x=xx;
                PasteFB.y=yy;
                PasteFB.width=ww;
                PasteFB.height=hh;

                CopyFB.fbID=pBuffDC->u8FbID;
                CopyFB.x=0;
                CopyFB.y=0;
                CopyFB.width=rect->width;
                CopyFB.height=rect->height;
                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                MApp_ZUI_API_ReleaseWithoutUpdateDC();
            }*/
            /*{ //style 5: mosic: OSD API NOT ALLOW ZOOM BITBLT
                const RECT *rect = &GETWNDINITRECT(HWND_MAINFRAME);
                U16 sp = MAIN_MENU_SHOW_UP_STEP-_u8TransitionStep;
                U16 uw = rect->width/sp;
                U16 uh = rect->height/sp;
                U16 xx, yy;
                pBuffDC = MApp_ZUI_API_GetBufferDC();
                pScrnDC = MApp_ZUI_API_GetScreenDC();
                MSAPI_OSDRegion CopyFB;
                MSAPI_OSDRegion PasteFB;

                for (xx = 0; xx < sp; xx++)
                {
                    for (yy = 0; yy < sp; yy++)
                    {
                        PasteFB.fbID=pScrnDC->u8FbID;
                        PasteFB.x=uw*xx;
                        PasteFB.y=uh*yy;
                        PasteFB.width=uw;
                        PasteFB.height=uh;

                        //we MUST reset clip window before msAPI_OSD_CopyRegion()
                        msAPI_OSD_SetClipWindow(
                            PasteFB.x, PasteFB.y, PasteFB.x+PasteFB.width, PasteFB.y+PasteFB.height );

                        CopyFB.fbID=pBuffDC->u8FbID;
                        CopyFB.x=uw*xx;
                        CopyFB.y=uw*yy;
                        CopyFB.width=4; //for GE limitation: scale bitmap need to be divied by 4!
                        CopyFB.height=4;
                        msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                    }
                }
                MApp_ZUI_API_ReleaseWithoutUpdateDC();
            }*/
            { //style 6: show NxM v waterfal
                U8 i, j;
                const RECT *rect = &GETWNDINITRECT(HWND_MAINFRAME);
                U16 h = rect->height/MAIN_MENU_STYLE6_ROW;
                U16 w = rect->width/MAIN_MENU_STYLE6_COL;
                //S8 hindex = MAIN_MENU_SHOW_UP_STEP-_u8TransitionStep;
                //U16 hshow = hh*(MAIN_MENU_SHOW_UP_STEP-_u8TransitionStep)/MAIN_MENU_SHOW_UP_STEP ;
                pBuffDC = MApp_ZUI_API_GetBufferDC();
                pScrnDC = MApp_ZUI_API_GetScreenDC();
                MSAPI_OSDRegion CopyFB;
                MSAPI_OSDRegion PasteFB;

                //printf("hshow=%u\n", hshow);

                for (i = 0; i < MAIN_MENU_STYLE6_ROW; i++)
                {
                    for (j = 0; j < MAIN_MENU_STYLE6_COL; j++)
                    {
                        U16 hh = h, ww = w;
                        S8 idx = MAIN_MENU_STYLE6_COL/2;
                        idx -= j;
                        if (idx < 0) idx = -idx;
                        idx += i;
                        if ( idx != (MAIN_MENU_SHOW_UP_STEP-1-_u8TransitionStep))
                            continue;
                        if (j == MAIN_MENU_STYLE6_COL-1)
                            ww += (rect->width%MAIN_MENU_STYLE6_COL);
                        if (i == MAIN_MENU_STYLE6_ROW-1)
                            hh += (rect->height%MAIN_MENU_STYLE6_ROW);

                        //we MUST reset clip window before msAPI_OSD_CopyRegion()
                        msAPI_OSD_SetClipWindow(
                            w*j, h*i,
                            w*j+ww-1, h*i+hh-1);

                        PasteFB.fbID=pScrnDC->u8FbID;
                        PasteFB.x=w*j;
                        PasteFB.y=h*i;
                        PasteFB.width=ww;
                        PasteFB.height=hh;

                        CopyFB.fbID=pBuffDC->u8FbID;
                        CopyFB.x=PasteFB.x;
                        CopyFB.y=PasteFB.y;
                        CopyFB.width=ww;
                        CopyFB.height=hh;
                        msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                    }
                }
                MApp_ZUI_API_ReleaseWithoutUpdateDC();
            }
            if ( _u8TransitionStep == 0)
            {
                _eZUIState = E_ZUI_STATE_TRANSEFF_END;
            }
        }
        break;

        case EN_EFFMODE_MAIN_BG_ROTATE:
        #ifdef ATSC_SYSTEM
        #if(!TRUNK_UI2)
        {
            //note: here assume init position of HWND_TOP_ICON_CHANNEL is the focus position
            //      and current focus hwnd is the window we want to move it to focus position
            //      and HWND_TOP_ICON_CHANNEL to HWND_TOP_ICON_LOCK continuously placed...
            #if ZUI_EFFECT_DBG_TIME_DIFF
            printf("time_diff=%lu\n", msAPI_Timer_DiffTimeFromNow(_u32MainMenuPrevTime));
            _u32MainMenuPrevTime = msAPI_Timer_GetTime0();
            #endif //ZUI_EFFECT_DBG_TIME_DIFF

            //speed control....
            if(MApp_ZUI_API_IsExistRemainingMessage(MSG_KEYDOWN))
            {
                if (msAPI_Timer_DiffTimeFromNow(_u32TransEffectTimer)<30)
                {
                    break;
                }
            }
            else
            {
                if (msAPI_Timer_DiffTimeFromNow(_u32TransEffectTimer)<(U32)((_u8TransitionStep)*10))
                {
                    break;
                }

            }
            _u32TransEffectTimer = msAPI_Timer_GetTime0();
            _u8TransitionStep--;
            {
                U8 i;
                HWND move = MApp_ZUI_API_GetFocus();
                HWND target = HWND_MENU_TOP_ICON_PICTURE;
                const RECT * target_rect;
                RECT move_new_rect;
                RECT rect;
                if (move < HWND_MENU_TOP_ICON_PICTURE || move > HWND_MENU_TOP_ICON_CHANNEL)
                {
                    ZUI_DBG_FAIL(printf("[ZUI]EFFFOCUS\n"));
                    ABORT();
                }
                for (i = 7; i >1; i--)
                {
                    target_rect = &GETWNDINITRECT(target);
                    MApp_ZUI_API_GetWindowRect(move, &rect);
                    move_new_rect.left = target_rect->left + (rect.left-target_rect->left)*_u8TransitionStep/MAIN_BG_ROTATE_MAX_STEP;
                    move_new_rect.top = target_rect->top + (rect.top-target_rect->top)*_u8TransitionStep/MAIN_BG_ROTATE_MAX_STEP;
                    move_new_rect.width = target_rect->width + (rect.width-target_rect->width)*_u8TransitionStep/MAIN_BG_ROTATE_MAX_STEP;
                    move_new_rect.height = target_rect->height + (rect.height-target_rect->height)*_u8TransitionStep/MAIN_BG_ROTATE_MAX_STEP;
                    MApp_ZUI_API_MoveWindow(move, &move_new_rect);

                    target++; //will not over HWND_MENU_TOP_ICON_LOCK
                    if (move == HWND_MENU_TOP_ICON_CHANNEL)
                        move = HWND_MENU_TOP_ICON_PICTURE;
                    else
                        move++;
                }
                _MApp_ZUI_API_WindowProcOnIdle(); //force paint to scren...
            }
            if ( _u8TransitionStep == 0)
            {
                _eZUIState = E_ZUI_STATE_TRANSEFF_END;
            }
        }
        #endif
        #endif
        break;
        //case EN_EFFMODE_MAIN_BG_ROTATE_RIGHT:
        //    break;

        case EN_EFFMODE_PAGE_FADE_OUT:
        {
            #if ZUI_EFFECT_DBG_TIME_DIFF
            printf("time_diff=%lu\n", msAPI_Timer_DiffTimeFromNow(_u32MainMenuPrevTime));
            _u32MainMenuPrevTime = msAPI_Timer_GetTime0();
            #endif //ZUI_EFFECT_DBG_TIME_DIFF
            _u8TransitionStep--;
            {
                #if (MPLAYER_BITMAP_FORMAT == MPLAYER_I8)
                //quality is not good in palette mode...
                //extern void _MApp_ZUI_API_FadePaletteAlpha(U8 u8Alpha);
                //_MApp_ZUI_API_FadePaletteAlpha(
                //    255*(U16)_u8TransitionStep/MAIN_MENU_FADE_OUT_STEP);
                #else
                MApi_GOP_GWIN_SetBlending(
                    MApp_ZUI_API_QueryGWinID(),
                    FALSE,
                    OSDPAGE_BLENDING_VALUE*(U16)_u8TransitionStep/MAIN_MENU_FADE_OUT_STEP);
                #endif
            }
            if ( _u8TransitionStep == 0)
            {
                _eZUIState = E_ZUI_STATE_TRANSEFF_END;
            }
        }
        break;

        case EN_EFFMODE_LIST_SHOWUP:
        {
            //speed control....
            if (msAPI_Timer_DiffTimeFromNow(_u32TransEffectTimer)<20)
            {
                break;
            }
            _u32TransEffectTimer = msAPI_Timer_GetTime0();

            if (_u8TransitionStep == LIST_SHOW_UP_STEP)
            {
                MApp_ZUI_API_PrepareBufferDC(MApp_ZUI_API_GetBufferDC());
            }
            _u8TransitionStep--;
            //we assume list osd pages: CHANNEL_LIST, INPUT_SOURCE, AUDIO_LANGUAGE
            //   are the same bitmap on the top
            //   display to the right and drop down..
            if (_u8TransitionStep >= LIST_SHOW_UP_DOWN)
            {
                U8 step = (LIST_SHOW_UP_STEP-1)-_u8TransitionStep;
                U16 wtotal = GETWNDINITRECT(HWND_MAINFRAME).width;
                U16 htotal = LIST_SHOW_UP_BANNER_HEIGHT;
                U16 w = wtotal/LIST_SHOW_UP_RIGHT;
                U16 ww = w;
                pBuffDC = MApp_ZUI_API_GetBufferDC();
                pScrnDC = MApp_ZUI_API_GetScreenDC();
                MSAPI_OSDRegion CopyFB;
                MSAPI_OSDRegion PasteFB;

                if (step == LIST_SHOW_UP_RIGHT-1)
                    ww += wtotal%LIST_SHOW_UP_RIGHT;

                //we MUST reset clip window before msAPI_OSD_CopyRegion()
                msAPI_OSD_SetClipWindow(
                    step*w, 0,
                    step*w+ww-1, htotal-1);

                PasteFB.fbID=pScrnDC->u8FbID;
                PasteFB.x=step*w;
                PasteFB.y=0;
                PasteFB.width=ww;
                PasteFB.height=htotal;

                CopyFB.fbID=pBuffDC->u8FbID;
                CopyFB.x=PasteFB.x;
                CopyFB.y=0;
                CopyFB.width=ww;
                CopyFB.height=htotal;
                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                MApp_ZUI_API_ReleaseWithoutUpdateDC();
            }
            else
            {
                U8 step = (LIST_SHOW_UP_DOWN-1)-_u8TransitionStep;
                U16 htotal = GETWNDINITRECT(HWND_MAINFRAME).height-LIST_SHOW_UP_BANNER_HEIGHT;
                U16 wtotal = GETWNDINITRECT(HWND_MAINFRAME).width;
                U16 h = htotal, i;
                U16 ystart = 0;
                //U16 h = 0, i;
                pBuffDC = MApp_ZUI_API_GetBufferDC();
                pScrnDC = MApp_ZUI_API_GetScreenDC();
                MSAPI_OSDRegion CopyFB;
                MSAPI_OSDRegion PasteFB;


                for (i = 0; i < step; i++)
                {
                    ystart += h/LIST_SHOW_UP_DOWN_RATE;
                    h -= h/LIST_SHOW_UP_DOWN_RATE;
                }

                //we MUST reset clip window before msAPI_OSD_CopyRegion()
                msAPI_OSD_SetClipWindow(
                    0, LIST_SHOW_UP_BANNER_HEIGHT+ystart,
                    wtotal-1,
                    LIST_SHOW_UP_BANNER_HEIGHT+ystart+h/LIST_SHOW_UP_DOWN_RATE -1);

                PasteFB.fbID=pScrnDC->u8FbID;
                PasteFB.x=0;
                PasteFB.y=LIST_SHOW_UP_BANNER_HEIGHT+ystart;
                PasteFB.width=wtotal;
                PasteFB.height=h/LIST_SHOW_UP_DOWN_RATE;

                CopyFB.fbID=pBuffDC->u8FbID;
                CopyFB.x=0;
                CopyFB.y=PasteFB.y;
                CopyFB.width=wtotal;
                CopyFB.height=PasteFB.height;
                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

                /*
                for (i = 0; i <= step; i++)
                {
                    h += (htotal-h) / LIST_SHOW_UP_DOWN_RATE;
                }

                PasteFB.fbID=pScrnDC->u8FbID;
                PasteFB.x=0;
                PasteFB.y=LIST_SHOW_UP_BANNER_HEIGHT;
                PasteFB.width=wtotal;
                PasteFB.height=h;

                CopyFB.fbID=pBuffDC->u8FbID;
                CopyFB.x=0;
                CopyFB.y=LIST_SHOW_UP_BANNER_HEIGHT;
                CopyFB.width=wtotal;
                CopyFB.height=htotal;
                _MApp_ZUI_ACT_CopyRegionScaleV(&CopyFB, &PasteFB);
                */
                MApp_ZUI_API_ReleaseWithoutUpdateDC();
            }
            if ( _u8TransitionStep == 0)
            {
                _eZUIState = E_ZUI_STATE_TRANSEFF_END;
            }
        }
        break;

        case EN_EFFMODE_MSGBOX_SHOWUP:
        {
            //speed control....
            //if (msAPI_Timer_DiffTimeFromNow(_u32TransEffectTimer)<20)
            //{
            //    break;
            //}
            //_u32TransEffectTimer = msAPI_Timer_GetTime0();

            if (_u8TransitionStep == MSGBOX_SHOW_UP_STEP)
            {
                MApp_ZUI_API_PrepareBufferDC(MApp_ZUI_API_GetBufferDC());
            }
            _u8TransitionStep--;
            {
                U8 step = (MSGBOX_SHOW_UP_STEP-1)-_u8TransitionStep;
                U16 htotal = GETWNDINITRECT(HWND_MAINFRAME).height;
                U16 wtotal = GETWNDINITRECT(HWND_MAINFRAME).width;
                U16 w = 0, i;
                pBuffDC = MApp_ZUI_API_GetBufferDC();
                pScrnDC = MApp_ZUI_API_GetScreenDC();
                MSAPI_OSDRegion CopyFB;
                MSAPI_OSDRegion PasteFB;

                for (i = 0; i <= step; i++)
                {
                    w += (wtotal-w) / MSGBOX_SHOW_UP_LR_RATE;
                }

                /*
                PasteFB.fbID=pScrnDC->u8FbID;
                PasteFB.x=(wtotal-w)/2;
                PasteFB.y=0;
                PasteFB.width=w;
                PasteFB.height=htotal;

                CopyFB.fbID=pBuffDC->u8FbID;
                CopyFB.x=0;
                CopyFB.y=0;
                CopyFB.width=wtotal;
                CopyFB.height=htotal;
                _MApp_ZUI_ACT_CopyRegionScaleH(&CopyFB, &PasteFB);
                */

                PasteFB.fbID=pScrnDC->u8FbID;
                PasteFB.x=(wtotal-w)/2;
                PasteFB.y=0;
                PasteFB.width=w;
                PasteFB.height=htotal;

                CopyFB.fbID=pBuffDC->u8FbID;
                CopyFB.x=PasteFB.x;
                CopyFB.y=0;
                CopyFB.width=w;
                CopyFB.height=htotal;

                //we MUST reset clip window before msAPI_OSD_CopyRegion()
                msAPI_OSD_SetClipWindow(
                    PasteFB.x, 0,
                    w-1, htotal-1);
                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

                MApp_ZUI_API_ReleaseWithoutUpdateDC();
            }
            if ( _u8TransitionStep == 0)
            {
                _eZUIState = E_ZUI_STATE_TRANSEFF_END;
            }
        }
        break;

        case EN_EFFMODE_PAGE_FADE_IN:
        {
            #if ZUI_EFFECT_DBG_TIME_DIFF
            printf("time_diff=%lu\n", msAPI_Timer_DiffTimeFromNow(_u32MainMenuPrevTime));
            _u32MainMenuPrevTime = msAPI_Timer_GetTime0();
            #endif //ZUI_EFFECT_DBG_TIME_DIFF

            //speed control....
            if (msAPI_Timer_DiffTimeFromNow(_u32TransEffectTimer)<20)
            {
                break;
            }
            _u32TransEffectTimer = msAPI_Timer_GetTime0();

            _u8TransitionStep--;
            {
#if (MPLAYER_BITMAP_FORMAT == MPLAYER_I8)
                //quality is not good in palette mode...
                //extern void _MApp_ZUI_API_FadePaletteAlpha(U8 u8Alpha);
                //_MApp_ZUI_API_FadePaletteAlpha(
                //    255*(U16)(MAIN_MENU_FADE_IN_STEP-_u8TransitionStep)/MAIN_MENU_FADE_IN_STEP);
#else
                BOOLEAN bPixelAlpha = FALSE;
                if ( _u8TransitionStep == 0 )
                {
                    bPixelAlpha = TRUE;
                }
                MApi_GOP_GWIN_SetBlending(
                    MApp_ZUI_API_QueryGWinID(),
                    bPixelAlpha,
                    OSDPAGE_BLENDING_VALUE*(U16)(MAIN_MENU_FADE_IN_STEP-_u8TransitionStep)/MAIN_MENU_FADE_IN_STEP);
#endif

                if(MAIN_MENU_FADE_IN_STEP == _u8TransitionStep+1)
                {
                    MApp_ZUI_API_InvalidateWindow(HWND_MAINFRAME);
                    _MApp_ZUI_API_WindowProcOnIdle(); //force paint to scren...
                }

            }
            if ( _u8TransitionStep == 0)
            {
                _eZUIState = E_ZUI_STATE_TRANSEFF_END;
            }
        }
        break;

        case EN_EFFMODE_CUBE:
        {
#ifndef ATSC_SYSTEM
            // Marked by coverity_0449
            //printf("CUBE doing: %bu\n", _eTransEffectMode);

            //speed control....
            if (msAPI_Timer_DiffTimeFromNow(_u32TransEffectTimer)<20)
            {
                break;
            }
            _u32TransEffectTimer = msAPI_Timer_GetTime0();

            _u8TransitionStep --;

            if(_MApp_ZUI_ACT_Focus2Icon1(MApp_ZUI_API_GetFocus()) != MApp_ZUI_API_GetFocus())
            {
                RECT rect1 = GETWNDINITRECT(_MApp_ZUI_ACT_Focus2Icon1(MApp_ZUI_API_GetFocus()));
                if(_MApp_ZUI_ACT_Focus2Index1(MApp_ZUI_API_GetFocus()) >= _MApp_ZUI_ACT_Focus2Index1(HWND_AUDLANG_LIST_ITEM0)
                    && _MApp_ZUI_ACT_Focus2Index1(MApp_ZUI_API_GetFocus()) <= _MApp_ZUI_ACT_Focus2Index1(HWND_AUDLANG_LIST_ITEM4))
                {
                    if(ALTpara==ALT_LR2RR || ALTpara==ALT_RR2LL || ALTpara==ALT_RR2LR || ALTpara==ALT_LL2RR)
                    {
                        rect1.width=rect1.width*(MAIN_MENU_CUBE_STEP-_u8TransitionStep)/MAIN_MENU_CUBE_STEP;
                        MS_DEBUG_MSG(printf("L===%u, %u, %u, %u===\n", rect1.left, rect1.top, rect1.width, rect1.height));
                        MApp_ZUI_API_InvalidateRect (&rect1);
                    }
                }
                else
                {
                    rect1.width=rect1.width*(MAIN_MENU_CUBE_STEP-_u8TransitionStep)/MAIN_MENU_CUBE_STEP;
                    MApp_ZUI_API_InvalidateRect (&rect1);
                }
            }
            if(_MApp_ZUI_ACT_Focus2Icon2(MApp_ZUI_API_GetFocus()) != MApp_ZUI_API_GetFocus())
            {
                RECT rect2 = GETWNDINITRECT(_MApp_ZUI_ACT_Focus2Icon2(MApp_ZUI_API_GetFocus()));
                if(_MApp_ZUI_ACT_Focus2Index2(MApp_ZUI_API_GetFocus()) >= _MApp_ZUI_ACT_Focus2Index2(HWND_AUDLANG_LIST_ITEM0)
                    && _MApp_ZUI_ACT_Focus2Index2(MApp_ZUI_API_GetFocus()) <= _MApp_ZUI_ACT_Focus2Index2(HWND_AUDLANG_LIST_ITEM4))
                {
                    if(ALTpara==ALT_LL2LR || ALTpara==ALT_RR2LL || ALTpara==ALT_LL2RR || ALTpara==ALT_LR2LL)
                    {
                        rect2.width=rect2.width*(MAIN_MENU_CUBE_STEP-_u8TransitionStep)/MAIN_MENU_CUBE_STEP;
                        MS_DEBUG_MSG(printf("R===%u, %u, %u, %u===\n", rect2.left, rect2.top, rect2.width, rect2.height));
                        MApp_ZUI_API_InvalidateRect (&rect2);
                    }
                }
                else
                {
                    rect2.width=rect2.width*(MAIN_MENU_CUBE_STEP-_u8TransitionStep)/MAIN_MENU_CUBE_STEP;
                    MApp_ZUI_API_InvalidateRect (&rect2);
                }
            }
            _MApp_ZUI_API_WindowProcOnIdle(); //force paint to scren...

            if ( _u8TransitionStep == 0)
            {
                _eZUIState = E_ZUI_STATE_TRANSEFF_END;
                MApp_ZUI_API_InvalidateWindow(MApp_ZUI_API_GetFocus());
                MApp_ZUI_API_ResetTimer(HWND_AUDLANG_LIST_PANE, 0);
            }
#else
                printf("[ATSC] Do not support CUBE effect\n");
#endif
        }
        break;

        case EN_EFFMODE_PAGE_ZOOM_IN:
        {
            #if ZUI_EFFECT_DBG_TIME_DIFF
            //printf("time_diff=%lu\n", msAPI_Timer_GetTime0()-_u32MainMenuPrevTime);
            _u32MainMenuPrevTime = msAPI_Timer_GetTime0();
            #endif //ZUI_EFFECT_DBG_TIME_DIFF
            if (_u8TransitionStep == MSGBOX_ZOOM_IN_STEP)
            {
                MApp_ZUI_API_PrepareBufferDC(MApp_ZUI_API_GetBufferDC());
            }
            _u8TransitionStep--;
            {
                const RECT *rect = &GETWNDINITRECT(HWND_MAINFRAME);
                U16 ww = rect->width*(MSGBOX_ZOOM_IN_STEP-_u8TransitionStep)/MSGBOX_ZOOM_IN_STEP;
                U16 hh = rect->height*(MSGBOX_ZOOM_IN_STEP-_u8TransitionStep)/MSGBOX_ZOOM_IN_STEP;
                U16 xx = (rect->width-ww)/2;
                U16 yy = (rect->height-hh)/2;

                pBuffDC = MApp_ZUI_API_GetBufferDC();
                pScrnDC = MApp_ZUI_API_GetScreenDC();
                MSAPI_OSDRegion CopyFB;
                MSAPI_OSDRegion PasteFB;

                if (_u8TransitionStep == (MSGBOX_ZOOM_IN_STEP-1))
                {
                    MApi_GOP_GWIN_GetFBInfo(pBuffDC->u8FbID, &fbAttr);
                    u8FbIdTmp = MApi_GOP_GWIN_GetFreeFBID();
                    MApi_GOP_GWIN_CreateFB(u8FbIdTmp, 0, 0, fbAttr.width, fbAttr.height, fbAttr.fbFmt);

                    //we MUST reset clip window before msAPI_OSD_CopyRegion()
                    msAPI_OSD_SetClipWindow(0, 0, rect->width-1, rect->height-1);

                    PasteFB.fbID=u8FbIdTmp;
                    PasteFB.x=0;
                    PasteFB.y=0;
                    PasteFB.width=rect->width*1/2+4;
                    PasteFB.height=rect->height*1/2+4;

                    CopyFB.fbID=pBuffDC->u8FbID;
                    CopyFB.x=0;
                    CopyFB.y=0;
                    CopyFB.width=rect->width;
                    CopyFB.height=rect->height;
                    msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

                    PasteFB.fbID=u8FbIdTmp;
                    PasteFB.x=rect->width*1/2+4;
                    PasteFB.y=0;
                    PasteFB.width=rect->width*1/4+4;
                    PasteFB.height=rect->height*1/4+4;

                    CopyFB.fbID=u8FbIdTmp;
                    CopyFB.x=0;
                    CopyFB.y=0;
                    CopyFB.width=rect->width*1/2+4;
                    CopyFB.height=rect->width*1/2+4;
                    msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

                    PasteFB.fbID=u8FbIdTmp;
                    PasteFB.x=rect->width*1/2+4+rect->width*1/4+4;
                    PasteFB.y=0;
                    PasteFB.width=rect->width*1/8+4;
                    PasteFB.height=rect->height*1/8+4;

                    CopyFB.fbID=u8FbIdTmp;
                    CopyFB.x=rect->width*1/2+4;
                    CopyFB.y=0;
                    CopyFB.width=rect->width*1/4+4;
                    CopyFB.height=rect->width*1/4+4;
                    msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
               }

                //we MUST reset clip window before msAPI_OSD_CopyRegion()
                msAPI_OSD_SetClipWindow(xx, yy, xx+ww-1, yy+hh-1 );

                if(ww > rect->width/2 && hh > rect->height/2)
                {
                    PasteFB.fbID=pScrnDC->u8FbID;
                    PasteFB.x=xx;
                    PasteFB.y=yy;
                    PasteFB.width=ww;
                    PasteFB.height=hh;

                    CopyFB.fbID=pBuffDC->u8FbID;
                    CopyFB.x=0;
                    CopyFB.y=0;
                    CopyFB.width=rect->width;
                    CopyFB.height=rect->height;
                    msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                }
                else if (ww > rect->width/4 && hh > rect->height/4)
                {
                    PasteFB.fbID=pScrnDC->u8FbID;
                    PasteFB.x=xx;
                    PasteFB.y=yy;
                    PasteFB.width=ww;
                    PasteFB.height=hh;

                    CopyFB.fbID=u8FbIdTmp;
                    CopyFB.x=0;
                    CopyFB.y=0;
                    CopyFB.width=rect->width*1/2+4;
                    CopyFB.height=rect->height*1/2+4;
                    msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                }
                else if (ww > rect->width/8 && hh > rect->height/8)
                {
                    PasteFB.fbID=pScrnDC->u8FbID;
                    PasteFB.x=xx;
                    PasteFB.y=yy;
                    PasteFB.width=ww;
                    PasteFB.height=hh;

                    CopyFB.fbID=u8FbIdTmp;
                    CopyFB.x=rect->width*1/2+4;
                    CopyFB.y=0;
                    CopyFB.width=rect->width*1/4+4;
                    CopyFB.height=rect->height*1/4+4;
                    msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                }
                else if (ww > rect->width/16 && hh > rect->height/16)
                {
                    PasteFB.fbID=pScrnDC->u8FbID;
                    PasteFB.x=xx;
                    PasteFB.y=yy;
                    PasteFB.width=ww;
                    PasteFB.height=hh;

                    CopyFB.fbID=u8FbIdTmp;
                    CopyFB.x=rect->width*1/2+4+rect->width*1/4+4;
                    CopyFB.y=0;
                    CopyFB.width=rect->width*1/8+4;
                    CopyFB.height=rect->height*1/8+4;
                    msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                }

                MApp_ZUI_API_ReleaseWithoutUpdateDC();
            }
            if ( _u8TransitionStep == 0)
            {
                MApi_GOP_GWIN_DestroyFB(u8FbIdTmp);
                _eZUIState = E_ZUI_STATE_TRANSEFF_END;
            }
        }
        break;

        case EN_EFFMODE_PAGE_ZOOM_OUT:
        {
            #if ZUI_EFFECT_DBG_TIME_DIFF
            //printf("time_diff=%lu\n", msAPI_Timer_DiffTimeFromNow(_u32MainMenuPrevTime));
            _u32MainMenuPrevTime = msAPI_Timer_GetTime0();
            #endif //ZUI_EFFECT_DBG_TIME_DIFF
            _u8TransitionStep--;

            pBuffDC = MApp_ZUI_API_GetBufferDC();
            pScrnDC = MApp_ZUI_API_GetScreenDC();
            MSAPI_OSDRegion CopyFB;
            MSAPI_OSDRegion PasteFB;

            if ( _u8TransitionStep == 0)
            {
                _eZUIState = E_ZUI_STATE_TRANSEFF_END;
            }
            else
            {
                const RECT *rect = &GETWNDINITRECT(HWND_MAINFRAME);

                U16 w0 = rect->width*(_u8TransitionStep+1)/MSGBOX_ZOOM_OUT_STEP;
                U16 h0 = rect->height*(_u8TransitionStep+1)/MSGBOX_ZOOM_OUT_STEP;
                U16 x0 = (rect->width-w0)/2;
                U16 U16y0 = (rect->height-h0)/2;

                U16 w1 = rect->width*(_u8TransitionStep)/MSGBOX_ZOOM_OUT_STEP;
                U16 h1 = rect->height*(_u8TransitionStep)/MSGBOX_ZOOM_OUT_STEP;
                U16 x1 = (rect->width-w1)/2;
                U16 U16y1 = (rect->height-h1)/2;

                MApi_GOP_GWIN_GetFBInfo(pBuffDC->u8FbID, &fbAttr);
                MApi_GFX_ClearFrameBuffer(fbAttr.addr, fbAttr.size, 0); // fill frame buffer with 0, black

                //we MUST reset clip window before msAPI_OSD_CopyRegion()
                msAPI_OSD_SetClipWindow(0, 0, 0+rect->width-1, 0+rect->height-1);

                PasteFB.fbID=pBuffDC->u8FbID;
                PasteFB.x=x1;
                PasteFB.y=U16y1;
                PasteFB.width=w1;
                PasteFB.height=h1;

                CopyFB.fbID=pScrnDC->u8FbID;
                CopyFB.x=x0;
                CopyFB.y=U16y0;
                CopyFB.width=w0;
                CopyFB.height=h0;
                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

                PasteFB.fbID=pScrnDC->u8FbID;
                PasteFB.x=0;
                PasteFB.y=0;
                PasteFB.width=rect->width;
                PasteFB.height=rect->height;

                CopyFB.fbID=pBuffDC->u8FbID;
                CopyFB.x=0;
                CopyFB.y=0;
                CopyFB.width=rect->width;
                CopyFB.height=rect->height;
                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
            }
        }
        break;

        case EN_EFFMODE_PAGE_SPREAD_OUT:
        {
            #if ZUI_EFFECT_DBG_TIME_DIFF
            //printf("time_diff=%lu\n", msAPI_Timer_GetTime0()-_u32MainMenuPrevTime);
            _u32MainMenuPrevTime = msAPI_Timer_GetTime0();
            #endif //ZUI_EFFECT_DBG_TIME_DIFF
            if (_u8TransitionStep == MSGBOX_SPREAD_OUT_STEP)
            {
                MApp_ZUI_API_PrepareBufferDC(MApp_ZUI_API_GetBufferDC());
            }
            _u8TransitionStep--;
            {
                const RECT *rect = &GETWNDINITRECT(HWND_MAINFRAME);
                ZUI_MSG(printf("rect (%d, %d, %d, %d)\n",
                    rect->left, rect->top, rect->width, rect->height));

                U16 w_effect = rect->left + rect->width;
                U16 h_effect = rect->height;
                U16 x_effect = rect->left;
                U16 y_effect = rect->top;

                U16 h_top = 63;//parameter
                U16 h_bottom = 53;//parameter

                if ( h_effect < h_top || h_effect < (h_top+h_bottom+10) )
                {
                    _u8TransitionStep = 0;
                    _eZUIState = E_ZUI_STATE_TRANSEFF_END;
                    break;
                }

                U16 h_middle = (rect->height - h_top - h_bottom) * (MSGBOX_SPREAD_OUT_STEP - _u8TransitionStep) / MSGBOX_SPREAD_OUT_STEP;

                U16 y_middle = y_effect + h_top;
                U16 y_bottom = y_middle + h_middle;
                U16 y_bottom_org = y_effect + h_effect - h_bottom;

                pBuffDC = MApp_ZUI_API_GetBufferDC();
                pScrnDC = MApp_ZUI_API_GetScreenDC();
                MSAPI_OSDRegion CopyFB;
                MSAPI_OSDRegion PasteFB;

                msAPI_OSD_BackupClipWindow();
                msAPI_OSD_SetClipWindow(x_effect, y_effect, x_effect+w_effect-1, y_effect+h_effect-1);

                // copy from back buffer to screen buffer
                PasteFB.fbID=pScrnDC->u8FbID;
                CopyFB.fbID=pBuffDC->u8FbID;

                // copy top
                PasteFB.x=x_effect;
                PasteFB.y=y_effect;
                PasteFB.width=w_effect;
                PasteFB.height=h_top;

                CopyFB.x=x_effect;
                CopyFB.y=y_effect;
                CopyFB.width=w_effect;
                CopyFB.height=h_top;
                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                ZUI_MSG(printf("copy (%d, %d, %d, %d) to (%d %d %d %d)\n",
                    CopyFB.x, CopyFB.y, CopyFB.width, CopyFB.height,
                    PasteFB.x, PasteFB.y, PasteFB.width, PasteFB.height));

                // copy middle
                PasteFB.x=x_effect;
                PasteFB.y=y_middle;
                PasteFB.width=w_effect;
                PasteFB.height=h_middle;

                CopyFB.x=x_effect;
                CopyFB.y=y_middle;
                CopyFB.width=w_effect;
                CopyFB.height=h_middle;
                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                ZUI_MSG(printf("copy (%d, %d, %d, %d) to (%d %d %d %d)\n",
                    CopyFB.x, CopyFB.y, CopyFB.width, CopyFB.height,
                    PasteFB.x, PasteFB.y, PasteFB.width, PasteFB.height));

                // copy bottom
                PasteFB.x=x_effect;
                PasteFB.y=y_bottom;
                PasteFB.width=w_effect;
                PasteFB.height=h_bottom;

                CopyFB.x=x_effect;
                CopyFB.y=y_bottom_org;
                CopyFB.width=w_effect;
                CopyFB.height=h_bottom;
                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                ZUI_MSG(printf("copy (%d, %d, %d, %d) to (%d %d %d %d)\n",
                    CopyFB.x, CopyFB.y, CopyFB.width, CopyFB.height,
                    PasteFB.x, PasteFB.y, PasteFB.width, PasteFB.height));

                msAPI_OSD_RestoreBackupClipWindow();
            }
            if ( _u8TransitionStep == 0)
            {
                MApi_GOP_GWIN_DestroyFB(u8FbIdTmp);
                _eZUIState = E_ZUI_STATE_TRANSEFF_END;
            }
        }
        break;

        case EN_EFFMODE_PAGE_ROLL_UP:
        {
            #if ZUI_EFFECT_DBG_TIME_DIFF
            //printf("time_diff=%lu\n", msAPI_Timer_GetTime0()-_u32MainMenuPrevTime);
            _u32MainMenuPrevTime = msAPI_Timer_GetTime0();
            #endif //ZUI_EFFECT_DBG_TIME_DIFF
            _u8TransitionStep--;
            {
                const RECT *rect = &GETWNDINITRECT(HWND_MAINFRAME);
                ZUI_MSG(printf("rect (%d, %d, %d, %d)\n",
                    rect->left, rect->top, rect->width, rect->height));

                U16 w_effect = rect->left + rect->width;
                U16 h_effect = rect->height;
                U16 x_effect = rect->left;
                U16 y_effect = rect->top;

                U16 h_top = 63;//parameter
                U16 h_bottom = 53;//parameter

                if ( h_effect < h_top || h_effect < (h_top+h_bottom+10) )
                {
                    _u8TransitionStep = 0;
                    _eZUIState = E_ZUI_STATE_TRANSEFF_END;
                    break;
                }

                U16 h_middle_pre = (rect->height - h_top - h_bottom) * (_u8TransitionStep+1) / MSGBOX_ROLL_UP_STEP;
                U16 h_middle = (rect->height - h_top - h_bottom) * _u8TransitionStep / MSGBOX_ROLL_UP_STEP;

                U16 y_middle = y_effect + h_top;
                U16 y_bottom_pre = y_middle + h_middle_pre;
                U16 y_bottom = y_middle + h_middle;

                pBuffDC = MApp_ZUI_API_GetBufferDC();
                pScrnDC = MApp_ZUI_API_GetScreenDC();
                MSAPI_OSDRegion CopyFB;
                MSAPI_OSDRegion PasteFB;

                MApi_GOP_GWIN_GetFBInfo(pBuffDC->u8FbID, &fbAttr);
                MApi_GFX_ClearFrameBuffer(fbAttr.addr, fbAttr.size, 0); // fill frame buffer with 0, black

                msAPI_OSD_BackupClipWindow();
                msAPI_OSD_SetClipWindow(x_effect, y_effect, x_effect+w_effect-1, y_effect+h_effect-1);

                // copy from screen buffer to back buffer
                PasteFB.fbID=pBuffDC->u8FbID;
                CopyFB.fbID=pScrnDC->u8FbID;

                // copy top
                PasteFB.x=x_effect;
                PasteFB.y=y_effect;
                PasteFB.width=w_effect;
                PasteFB.height=h_top;

                CopyFB.x=x_effect;
                CopyFB.y=y_effect;
                CopyFB.width=w_effect;
                CopyFB.height=h_top;
                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                ZUI_MSG(printf("copy (%d, %d, %d, %d) to (%d %d %d %d)\n",
                    CopyFB.x, CopyFB.y, CopyFB.width, CopyFB.height,
                    PasteFB.x, PasteFB.y, PasteFB.width, PasteFB.height));

                // copy middle
                PasteFB.x=x_effect;
                PasteFB.y=y_middle;
                PasteFB.width=w_effect;
                PasteFB.height=h_middle;

                CopyFB.x=x_effect;
                CopyFB.y=y_middle;
                CopyFB.width=w_effect;
                CopyFB.height=h_middle;
                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                ZUI_MSG(printf("copy (%d, %d, %d, %d) to (%d %d %d %d)\n",
                    CopyFB.x, CopyFB.y, CopyFB.width, CopyFB.height,
                    PasteFB.x, PasteFB.y, PasteFB.width, PasteFB.height));

                // copy bottom
                PasteFB.x=x_effect;
                PasteFB.y=y_bottom;
                PasteFB.width=w_effect;
                PasteFB.height=h_bottom;

                CopyFB.x=x_effect;
                CopyFB.y=y_bottom_pre;
                CopyFB.width=w_effect;
                CopyFB.height=h_bottom;
                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                ZUI_MSG(printf("copy (%d, %d, %d, %d) to (%d %d %d %d)\n",
                    CopyFB.x, CopyFB.y, CopyFB.width, CopyFB.height,
                    PasteFB.x, PasteFB.y, PasteFB.width, PasteFB.height));

                // copy from screen buffer to back buffer
                PasteFB.fbID=pScrnDC->u8FbID;
                CopyFB.fbID=pBuffDC->u8FbID;

                PasteFB.x=x_effect;
                PasteFB.y=y_effect;
                PasteFB.width=w_effect;
                PasteFB.height=h_effect;

                CopyFB.x=x_effect;
                CopyFB.y=y_effect;
                CopyFB.width=w_effect;
                CopyFB.height=h_effect;
                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                ZUI_MSG(printf("copy (%d, %d, %d, %d) to (%d %d %d %d)\n",
                    CopyFB.x, CopyFB.y, CopyFB.width, CopyFB.height,
                    PasteFB.x, PasteFB.y, PasteFB.width, PasteFB.height));

                msAPI_OSD_RestoreBackupClipWindow();
            }
            if ( _u8TransitionStep == 0)
            {
                _eZUIState = E_ZUI_STATE_TRANSEFF_END;
            }
        }
        break;

        case EN_EFFMODE_PAGE_MOSAIC:
        {
            #if ZUI_EFFECT_DBG_TIME_DIFF
            //printf("time_diff=%lu\n", msAPI_Timer_GetTime0()-_u32MainMenuPrevTime);
            _u32MainMenuPrevTime = msAPI_Timer_GetTime0();
            #endif //ZUI_EFFECT_DBG_TIME_DIFF
            if (_u8TransitionStep == MSGBOX_MOSAIC_STEP)
            {
                MApp_ZUI_API_PrepareBufferDC(MApp_ZUI_API_GetBufferDC());
            }
            _u8TransitionStep--;
            {
                const RECT *rect = &GETWNDINITRECT(HWND_MAINFRAME);
                U16 sp = MSGBOX_MOSAIC_STEP-_u8TransitionStep;
                U16 uw = (rect->width + rect->left)/sp;
                U16 uh = (rect->height + rect->top)/sp;
                U16 xx, yy;
                pBuffDC = MApp_ZUI_API_GetBufferDC();
                pScrnDC = MApp_ZUI_API_GetScreenDC();
                MSAPI_OSDRegion CopyFB;
                MSAPI_OSDRegion PasteFB;

                for (xx = 0; xx < sp; xx++)
                {
                    for (yy = 0; yy < sp; yy++)
                    {
                        PasteFB.fbID=pScrnDC->u8FbID;
                        PasteFB.x=uw*xx;
                        PasteFB.y=uh*yy;
                        PasteFB.width=uw;
                        PasteFB.height=uh;

                        //we MUST reset clip window before msAPI_OSD_CopyRegion()
                        msAPI_OSD_SetClipWindow(PasteFB.x, PasteFB.y,
                        PasteFB.x+PasteFB.width-1, PasteFB.y+PasteFB.height -1);

                        CopyFB.fbID=pBuffDC->u8FbID;

                        CopyFB.width=uw*(MSGBOX_MOSAIC_STEP+sp)/(2*MSGBOX_MOSAIC_STEP); //for GE limitation: scale bitmap need to be divied by 4!
                        CopyFB.height=uh*(MSGBOX_MOSAIC_STEP+sp)/(2*MSGBOX_MOSAIC_STEP);

                        CopyFB.x=uw*xx+(uw-CopyFB.width)/2;
                        CopyFB.y=uh*yy+(uh-CopyFB.height)/2;
                        msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                    }
                }
                MApp_ZUI_API_ReleaseWithoutUpdateDC();
            }
            if ( _u8TransitionStep == 0)
            {
                _eZUIState = E_ZUI_STATE_TRANSEFF_END;
            }
        }
        break;

        case EN_EFFMODE_PAGE_EXIT_UP:
        {
            #if ZUI_EFFECT_DBG_TIME_DIFF
            //printf("time_diff=%lu\n", msAPI_Timer_GetTime0()-_u32MainMenuPrevTime);
            _u32MainMenuPrevTime = msAPI_Timer_GetTime0();
            #endif //ZUI_EFFECT_DBG_TIME_DIFF

            //speed control....
            if (msAPI_Timer_DiffTimeFromNow(_u32TransEffectTimer)<20)
            {
                break;
            }
            _u32TransEffectTimer = msAPI_Timer_GetTime0();


            _u8TransitionStep--;
            {
                const RECT *rect = &GETWNDINITRECT(HWND_MAINFRAME);

                U16 wt = rect->width + rect->left;
                U16 ht = rect->height + rect->top;
                U16 xt = rect->left;
                U16 yt = rect->top;

                pBuffDC = MApp_ZUI_API_GetBufferDC();
                pScrnDC = MApp_ZUI_API_GetScreenDC();
                MSAPI_OSDRegion CopyFB;
                MSAPI_OSDRegion PasteFB;

                MApi_GOP_GWIN_GetFBInfo(pBuffDC->u8FbID, &fbAttr);
                MApi_GFX_ClearFrameBuffer(fbAttr.addr, fbAttr.size, 0); // fill frame buffer with 0, black

                //we MUST reset clip window before msAPI_OSD_CopyRegion()
                msAPI_OSD_SetClipWindow(xt, yt, xt+wt-1, yt+ht-1 );
                PasteFB.fbID=pBuffDC->u8FbID;
                PasteFB.x=xt;
                PasteFB.y=yt;
                PasteFB.width=wt;
                PasteFB.height=ht -(rect->height)*(MSGBOX_EXIT_UP_STEP-_u8TransitionStep)/MSGBOX_EXIT_UP_STEP;

                CopyFB.fbID=pScrnDC->u8FbID;
                CopyFB.x=xt;
                CopyFB.y=yt + (rect->height)*(MSGBOX_EXIT_UP_STEP-_u8TransitionStep)/MSGBOX_EXIT_UP_STEP;
                CopyFB.width=wt;
                CopyFB.height=ht - (rect->height)*(MSGBOX_EXIT_UP_STEP-_u8TransitionStep)/MSGBOX_EXIT_UP_STEP;
                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

                //we MUST reset clip window before msAPI_OSD_CopyRegion()
                msAPI_OSD_SetClipWindow(xt, yt, xt+wt-1, yt+ht-1 );

                PasteFB.fbID=pScrnDC->u8FbID;
                PasteFB.x=xt;
                PasteFB.y=yt;
                PasteFB.width=wt;
                PasteFB.height=ht;

                CopyFB.fbID=pBuffDC->u8FbID;
                CopyFB.x=xt;
                CopyFB.y=yt;
                CopyFB.width=wt;
                CopyFB.height=ht;

                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                ZUI_MSG(printf("copy (%d, %d, %d, %d) to (%d %d %d %d)\n",
                    CopyFB.x, CopyFB.y, CopyFB.width, CopyFB.height,
                    PasteFB.x, PasteFB.y, PasteFB.width, PasteFB.height));

            }
            if ( _u8TransitionStep == 0)
            {
                _eZUIState = E_ZUI_STATE_TRANSEFF_END;
            }
        }
        break;

        case EN_EFFMODE_PAGE_EXIT_DOWN:
        {
            #if ZUI_EFFECT_DBG_TIME_DIFF
            //printf("time_diff=%lu\n", msAPI_Timer_GetTime0()-_u32MainMenuPrevTime);
            _u32MainMenuPrevTime = msAPI_Timer_GetTime0();
            #endif //ZUI_EFFECT_DBG_TIME_DIFF

            //speed control....
            if (msAPI_Timer_DiffTimeFromNow(_u32TransEffectTimer)<20)
            {
                break;
            }
            _u32TransEffectTimer = msAPI_Timer_GetTime0();


            _u8TransitionStep--;
            {
                const RECT *rect = &GETWNDINITRECT(HWND_MAINFRAME);
                U16 wt = rect->width + rect->left;
                U16 ht = rect->height + rect->top;
                U16 xt = rect->left;
                U16 yt = rect->top;

                pBuffDC = MApp_ZUI_API_GetBufferDC();
                pScrnDC = MApp_ZUI_API_GetScreenDC();
                MSAPI_OSDRegion CopyFB;
                MSAPI_OSDRegion PasteFB;

                MApi_GOP_GWIN_GetFBInfo(pBuffDC->u8FbID, &fbAttr);
                MApi_GFX_ClearFrameBuffer(fbAttr.addr, fbAttr.size, 0); // fill frame buffer with 0, black

                //we MUST reset clip window before msAPI_OSD_CopyRegion()
                msAPI_OSD_SetClipWindow(xt, yt, xt+wt-1, yt+ht-1 );
                PasteFB.fbID=pBuffDC->u8FbID;
                PasteFB.x=xt;
                PasteFB.y=yt + (rect->height)*(MSGBOX_EXIT_DOWN_STEP-_u8TransitionStep)/MSGBOX_EXIT_DOWN_STEP;
                PasteFB.width=wt;
                PasteFB.height=ht -(rect->height)*(MSGBOX_EXIT_DOWN_STEP-_u8TransitionStep)/MSGBOX_EXIT_DOWN_STEP;

                CopyFB.fbID=pScrnDC->u8FbID;
                CopyFB.x=xt;
                CopyFB.y=yt;
                CopyFB.width=wt;
                CopyFB.height=ht - (rect->height)*(MSGBOX_EXIT_DOWN_STEP-_u8TransitionStep)/MSGBOX_EXIT_DOWN_STEP;
                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

                //we MUST reset clip window before msAPI_OSD_CopyRegion()
                msAPI_OSD_SetClipWindow(xt, yt, xt+wt-1, yt+ht-1 );

                PasteFB.fbID=pScrnDC->u8FbID;
                PasteFB.x=xt;
                PasteFB.y=yt;
                PasteFB.width=wt;
                PasteFB.height=ht;

                CopyFB.fbID=pBuffDC->u8FbID;
                CopyFB.x=xt;
                CopyFB.y=yt;
                CopyFB.width=wt;
                CopyFB.height=ht;

                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                ZUI_MSG(printf("copy (%d, %d, %d, %d) to (%d %d %d %d)\n",
                    CopyFB.x, CopyFB.y, CopyFB.width, CopyFB.height,
                    PasteFB.x, PasteFB.y, PasteFB.width, PasteFB.height));

            }
            if ( _u8TransitionStep == 0)
            {
                _eZUIState = E_ZUI_STATE_TRANSEFF_END;
            }
        }
        break;

        case EN_EFFMODE_PAGE_EXIT_LEFT:
        {
            #if ZUI_EFFECT_DBG_TIME_DIFF
            //printf("time_diff=%lu\n", msAPI_Timer_GetTime0()-_u32MainMenuPrevTime);
            _u32MainMenuPrevTime = msAPI_Timer_GetTime0();
            #endif //ZUI_EFFECT_DBG_TIME_DIFF

            //speed control....
            if (msAPI_Timer_DiffTimeFromNow(_u32TransEffectTimer)<20)
            {
                break;
            }
            _u32TransEffectTimer = msAPI_Timer_GetTime0();

            _u8TransitionStep--;
            {
                const RECT *rect = &GETWNDINITRECT(HWND_MAINFRAME);

                U16 wt = rect->width + rect->left;
                U16 ht = rect->height + rect->top;
                U16 xt = rect->left;
                U16 yt = rect->top;

                pBuffDC = MApp_ZUI_API_GetBufferDC();
                pScrnDC = MApp_ZUI_API_GetScreenDC();
                MSAPI_OSDRegion CopyFB;
                MSAPI_OSDRegion PasteFB;

                MApi_GOP_GWIN_GetFBInfo(pBuffDC->u8FbID, &fbAttr);
                MApi_GFX_ClearFrameBuffer(fbAttr.addr, fbAttr.size, 0); // fill frame buffer with 0, black

                //we MUST reset clip window before msAPI_OSD_CopyRegion()
                msAPI_OSD_SetClipWindow(xt, yt, xt+wt-1, yt+ht-1 );
                PasteFB.fbID=pBuffDC->u8FbID;
                PasteFB.x=xt;
                PasteFB.y=yt;
                PasteFB.width=wt - (rect->width)*(MSGBOX_EXIT_LEFT_STEP-_u8TransitionStep)/MSGBOX_EXIT_LEFT_STEP;
                PasteFB.height=ht;

                CopyFB.fbID=pScrnDC->u8FbID;
                CopyFB.x=xt + (rect->width)*(MSGBOX_EXIT_LEFT_STEP-_u8TransitionStep)/MSGBOX_EXIT_LEFT_STEP;
                CopyFB.y=yt;
                CopyFB.width=wt - (rect->width)*(MSGBOX_EXIT_LEFT_STEP-_u8TransitionStep)/MSGBOX_EXIT_LEFT_STEP;
                CopyFB.height=ht;
                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

                //we MUST reset clip window before msAPI_OSD_CopyRegion()
                msAPI_OSD_SetClipWindow(xt, yt, xt+wt-1, yt+ht-1 );

                PasteFB.fbID=pScrnDC->u8FbID;
                PasteFB.x=xt;
                PasteFB.y=yt;
                PasteFB.width=wt;
                PasteFB.height=ht;

                CopyFB.fbID=pBuffDC->u8FbID;
                CopyFB.x=xt;
                CopyFB.y=yt;
                CopyFB.width=wt;
                CopyFB.height=ht;

                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                ZUI_MSG(printf("copy (%d, %d, %d, %d) to (%d %d %d %d)\n",
                    CopyFB.x, CopyFB.y, CopyFB.width, CopyFB.height,
                    PasteFB.x, PasteFB.y, PasteFB.width, PasteFB.height));

            }
            if ( _u8TransitionStep == 0)
            {
                _eZUIState = E_ZUI_STATE_TRANSEFF_END;
            }
        }
        break;

        case EN_EFFMODE_PAGE_EXIT_RIGHT:
        {
            #if ZUI_EFFECT_DBG_TIME_DIFF
            //printf("time_diff=%lu\n", msAPI_Timer_GetTime0()-_u32MainMenuPrevTime);
            _u32MainMenuPrevTime = msAPI_Timer_GetTime0();
            #endif //ZUI_EFFECT_DBG_TIME_DIFF

            //speed control....
            if (msAPI_Timer_DiffTimeFromNow(_u32TransEffectTimer)<20)
            {
                break;
            }
            _u32TransEffectTimer = msAPI_Timer_GetTime0();

            _u8TransitionStep--;
            {
                const RECT *rect = &GETWNDINITRECT(HWND_MAINFRAME);

                U16 wt = rect->width + rect->left;
                U16 ht = rect->height + rect->top;
                U16 xt = rect->left;
                U16 yt = rect->top;

                pBuffDC = MApp_ZUI_API_GetBufferDC();
                pScrnDC = MApp_ZUI_API_GetScreenDC();
                MSAPI_OSDRegion CopyFB;
                MSAPI_OSDRegion PasteFB;

                MApi_GOP_GWIN_GetFBInfo(pBuffDC->u8FbID, &fbAttr);
                MApi_GFX_ClearFrameBuffer(fbAttr.addr, fbAttr.size, 0); // fill frame buffer with 0, black

                //we MUST reset clip window before msAPI_OSD_CopyRegion()
                msAPI_OSD_SetClipWindow(xt, yt, xt+wt-1, yt+ht-1 );
                PasteFB.fbID=pBuffDC->u8FbID;
                PasteFB.x=xt + (rect->width)*(MSGBOX_EXIT_RIGHT_STEP-_u8TransitionStep)/MSGBOX_EXIT_RIGHT_STEP;
                PasteFB.y=yt;
                PasteFB.width=wt - (rect->width)*(MSGBOX_EXIT_RIGHT_STEP-_u8TransitionStep)/MSGBOX_EXIT_RIGHT_STEP;
                PasteFB.height=ht;

                CopyFB.fbID=pScrnDC->u8FbID;
                CopyFB.x=xt;
                CopyFB.y=yt;
                CopyFB.width=wt - (rect->width)*(MSGBOX_EXIT_RIGHT_STEP-_u8TransitionStep)/MSGBOX_EXIT_RIGHT_STEP;
                CopyFB.height=ht;
                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

                //we MUST reset clip window before msAPI_OSD_CopyRegion()
                msAPI_OSD_SetClipWindow(xt, yt, xt+wt-1, yt+ht-1 );

                PasteFB.fbID=pScrnDC->u8FbID;
                PasteFB.x=xt;
                PasteFB.y=yt;
                PasteFB.width=wt;
                PasteFB.height=ht;

                CopyFB.fbID=pBuffDC->u8FbID;
                CopyFB.x=xt;
                CopyFB.y=yt;
                CopyFB.width=wt;
                CopyFB.height=ht;

                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                ZUI_MSG(printf("copy (%d, %d, %d, %d) to (%d %d %d %d)\n",
                    CopyFB.x, CopyFB.y, CopyFB.width, CopyFB.height,
                    PasteFB.x, PasteFB.y, PasteFB.width, PasteFB.height));

            }
            if ( _u8TransitionStep == 0)
            {
                _eZUIState = E_ZUI_STATE_TRANSEFF_END;
            }
        }
        break;

        case EN_EFFMODE_PAGE_ENTER_UP:
        {
            #if ZUI_EFFECT_DBG_TIME_DIFF
            //printf("time_diff=%lu\n", msAPI_Timer_GetTime0()-_u32MainMenuPrevTime);
            _u32MainMenuPrevTime = msAPI_Timer_GetTime0();
            #endif //ZUI_EFFECT_DBG_TIME_DIFF

            //speed control....
            if (msAPI_Timer_DiffTimeFromNow(_u32TransEffectTimer)<20)
            {
                break;
            }
            _u32TransEffectTimer = msAPI_Timer_GetTime0();


            if (_u8TransitionStep == MSGBOX_ENTER_UP_STEP)
            {
                MApp_ZUI_API_PrepareBufferDC(MApp_ZUI_API_GetBufferDC());
            }
            _u8TransitionStep--;
            {
                const RECT *rect = &GETWNDINITRECT(HWND_MAINFRAME);

                U16 wt = rect->width + rect->left;
                U16 ht = rect->height + rect->top;
                U16 xt = rect->left;
                U16 yt = rect->top;

                pBuffDC = MApp_ZUI_API_GetBufferDC();
                pScrnDC = MApp_ZUI_API_GetScreenDC();
                MSAPI_OSDRegion CopyFB;
                MSAPI_OSDRegion PasteFB;

                //we MUST reset clip window before msAPI_OSD_CopyRegion()
                msAPI_OSD_SetClipWindow(xt, yt, xt+wt-1, yt+ht-1 );

                PasteFB.fbID=pScrnDC->u8FbID;
                PasteFB.x=xt;
                PasteFB.y=yt;
                PasteFB.width=wt;
                PasteFB.height=ht -(rect->height)*_u8TransitionStep/MSGBOX_ENTER_UP_STEP;

                CopyFB.fbID=pBuffDC->u8FbID;
                CopyFB.x=xt;
                CopyFB.y=yt + (rect->height)*_u8TransitionStep/MSGBOX_ENTER_UP_STEP;
                CopyFB.width=wt;
                CopyFB.height=ht - (rect->height)*_u8TransitionStep/MSGBOX_ENTER_UP_STEP;

                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                ZUI_MSG(printf("copy (%d, %d, %d, %d) to (%d %d %d %d)\n",
                    CopyFB.x, CopyFB.y, CopyFB.width, CopyFB.height,
                    PasteFB.x, PasteFB.y, PasteFB.width, PasteFB.height));

            }
            if ( _u8TransitionStep == 0)
            {
                _eZUIState = E_ZUI_STATE_TRANSEFF_END;
            }
        }
        break;

        case EN_EFFMODE_PAGE_ENTER_LEFT:
        {
            #if ZUI_EFFECT_DBG_TIME_DIFF
            //printf("time_diff=%lu\n", msAPI_Timer_GetTime0()-_u32MainMenuPrevTime);
            _u32MainMenuPrevTime = msAPI_Timer_GetTime0();
            #endif //ZUI_EFFECT_DBG_TIME_DIFF

            //speed control....
            if (msAPI_Timer_DiffTimeFromNow(_u32TransEffectTimer)<20)
            {
                break;
            }
            _u32TransEffectTimer = msAPI_Timer_GetTime0();


            if (_u8TransitionStep == MSGBOX_ENTER_LEFT_STEP)
            {
                MApp_ZUI_API_PrepareBufferDC(MApp_ZUI_API_GetBufferDC());
            }
            _u8TransitionStep--;
            {
                const RECT *rect = &GETWNDINITRECT(HWND_MAINFRAME);

                U16 wt = rect->width + rect->left;
                U16 ht = rect->height + rect->top;
                U16 xt = rect->left;
                U16 yt = rect->top;

                pBuffDC = MApp_ZUI_API_GetBufferDC();
                pScrnDC = MApp_ZUI_API_GetScreenDC();
                MSAPI_OSDRegion CopyFB;
                MSAPI_OSDRegion PasteFB;

                //we MUST reset clip window before msAPI_OSD_CopyRegion()
                msAPI_OSD_SetClipWindow(xt, yt, xt+wt-1, yt+ht-1 );

                PasteFB.fbID=pScrnDC->u8FbID;
                PasteFB.x=xt;
                PasteFB.y=yt;
                PasteFB.width=wt -(rect->width)*_u8TransitionStep/MSGBOX_ENTER_LEFT_STEP;
                PasteFB.height=ht;

                CopyFB.fbID=pBuffDC->u8FbID;
                CopyFB.x=xt + (rect->width)*_u8TransitionStep/MSGBOX_ENTER_LEFT_STEP;
                CopyFB.y=yt;
                CopyFB.width=wt - (rect->width)*_u8TransitionStep/MSGBOX_ENTER_LEFT_STEP;
                CopyFB.height=ht;

                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);

                MApp_ZUI_API_ReleaseWithoutUpdateDC();
                ZUI_MSG(printf("copy (%d, %d, %d, %d) to (%d %d %d %d)\n",
                    CopyFB.x, CopyFB.y, CopyFB.width, CopyFB.height,
                    PasteFB.x, PasteFB.y, PasteFB.width, PasteFB.height));

            }
            if ( _u8TransitionStep == 0)
            {
                _eZUIState = E_ZUI_STATE_TRANSEFF_END;
            }
        }
        break;

        case EN_EFFMODE_PAGE_ENTER_DOWN:
        {
            #if ZUI_EFFECT_DBG_TIME_DIFF
            //printf("time_diff=%lu\n", msAPI_Timer_GetTime0()-_u32MainMenuPrevTime);
            _u32MainMenuPrevTime = msAPI_Timer_GetTime0();
            #endif //ZUI_EFFECT_DBG_TIME_DIFF

            //speed control....
            if (msAPI_Timer_DiffTimeFromNow(_u32TransEffectTimer)<20)
            {
                break;
            }
            _u32TransEffectTimer = msAPI_Timer_GetTime0();


            if (_u8TransitionStep == MSGBOX_ENTER_DOWN_STEP)
            {
                MApp_ZUI_API_PrepareBufferDC(MApp_ZUI_API_GetBufferDC());
            }
            _u8TransitionStep--;
            {
                const RECT *rect = &GETWNDINITRECT(HWND_MAINFRAME);

                U16 wt = rect->width + rect->left;
                U16 ht = rect->height + rect->top;
                U16 xt = rect->left;
                U16 yt = rect->top;

                pBuffDC = MApp_ZUI_API_GetBufferDC();
                pScrnDC = MApp_ZUI_API_GetScreenDC();
                MSAPI_OSDRegion CopyFB;
                MSAPI_OSDRegion PasteFB;

                //we MUST reset clip window before msAPI_OSD_CopyRegion()
                msAPI_OSD_SetClipWindow(xt, yt, xt+wt-1, yt+ht-1 );

                PasteFB.fbID=pScrnDC->u8FbID;
                PasteFB.x=xt;
                PasteFB.y=yt + (rect->height)*_u8TransitionStep/MSGBOX_ENTER_DOWN_STEP;
                PasteFB.width=wt;
                PasteFB.height=ht -(rect->height)*_u8TransitionStep/MSGBOX_ENTER_DOWN_STEP;

                CopyFB.fbID=pBuffDC->u8FbID;
                CopyFB.x=xt;
                CopyFB.y=yt;
                CopyFB.width=wt;
                CopyFB.height=ht - (rect->height)*_u8TransitionStep/MSGBOX_ENTER_DOWN_STEP;

                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                ZUI_MSG(printf("copy (%d, %d, %d, %d) to (%d %d %d %d)\n",
                    CopyFB.x, CopyFB.y, CopyFB.width, CopyFB.height,
                    PasteFB.x, PasteFB.y, PasteFB.width, PasteFB.height));

            }
            if ( _u8TransitionStep == 0)
            {
                _eZUIState = E_ZUI_STATE_TRANSEFF_END;
            }
        }
        break;

        case EN_EFFMODE_PAGE_ENTER_RIGHT:
        {
            #if ZUI_EFFECT_DBG_TIME_DIFF
            //printf("time_diff=%lu\n", msAPI_Timer_GetTime0()-_u32MainMenuPrevTime);
            _u32MainMenuPrevTime = msAPI_Timer_GetTime0();
            #endif //ZUI_EFFECT_DBG_TIME_DIFF

            //speed control....
            if (msAPI_Timer_DiffTimeFromNow(_u32TransEffectTimer)<20)
            {
                break;
            }
            _u32TransEffectTimer = msAPI_Timer_GetTime0();


            if (_u8TransitionStep == MSGBOX_ENTER_RIGHT_STEP)
            {
                MApp_ZUI_API_PrepareBufferDC(MApp_ZUI_API_GetBufferDC());
            }
            _u8TransitionStep--;
            {
                const RECT *rect = &GETWNDINITRECT(HWND_MAINFRAME);

                U16 wt = rect->width + rect->left;
                U16 ht = rect->height + rect->top;
                U16 xt = rect->left;
                U16 yt = rect->top;

                pBuffDC = MApp_ZUI_API_GetBufferDC();
                pScrnDC = MApp_ZUI_API_GetScreenDC();
                MSAPI_OSDRegion CopyFB;
                MSAPI_OSDRegion PasteFB;

                //we MUST reset clip window before msAPI_OSD_CopyRegion()
                msAPI_OSD_SetClipWindow(xt, yt, xt+wt-1, yt+ht-1 );

                PasteFB.fbID=pScrnDC->u8FbID;
                PasteFB.x=xt + (rect->width)*_u8TransitionStep/MSGBOX_ENTER_RIGHT_STEP;
                PasteFB.y=yt;
                PasteFB.width=wt -(rect->width)*_u8TransitionStep/MSGBOX_ENTER_RIGHT_STEP;
                PasteFB.height=ht;

                CopyFB.fbID=pBuffDC->u8FbID;
                CopyFB.x=xt;
                CopyFB.y=yt;
                CopyFB.width=wt - (rect->width)*_u8TransitionStep/MSGBOX_ENTER_RIGHT_STEP;
                CopyFB.height=ht;

                msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
                ZUI_MSG(printf("copy (%d, %d, %d, %d) to (%d %d %d %d)\n",
                    CopyFB.x, CopyFB.y, CopyFB.width, CopyFB.height,
                    PasteFB.x, PasteFB.y, PasteFB.width, PasteFB.height));

            }
            if ( _u8TransitionStep == 0)
            {
                _eZUIState = E_ZUI_STATE_TRANSEFF_END;
            }
        }
        break;

        default:
        {
            _eZUIState = E_ZUI_STATE_TRANSEFF_END;
        }
            break;

    }

    //_eZUIState = E_ZUI_STATE_TRANSEFF_END;

    if (u8PrevGopID != OSD_GOP_ID)
        MApi_GOP_GWIN_SwitchGOP(u8PrevGopID);
}

///////////////////////////////////////////////////////////////////////////////
///  global  MApp_ZUI_ACT_TransitionEffectEnd
///  transition end handler, provide different kind of transition de-initialization
///
///  @return no return value
///
///  @author MStarSemi @date 2007/1/25
///////////////////////////////////////////////////////////////////////////////



void MApp_ZUI_ACT_TransitionEffectEnd(void)
{
    //note: called from MApp_Menu_MainTask(),
    //      you can customize the transition effect by your self...
    //      normally, just switch to target state

    ZUI_MSG(printf("EffEnd\n"));
    _eTransEffectMode = EN_EFFMODE_NONE;
    _eZUIState = _eAppTargetStateMenu;
}

#undef MAPP_ZUI_ACTEFFECT_C
