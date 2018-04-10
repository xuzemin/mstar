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

#define MAPP_ZUI_ACTDRAWDYNAWIN_C
#define _ZUI_INTERNAL_INSIDE_ //NOTE: for ZUI internal


//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "MsCommon.h"

#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcommon.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIgdi.h"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_ACTeffect.h"
#include "MApp_ZUI_ACTglobal.h"
#include "OSDcp_String_EnumIndex.h"
#include "ZUI_exefunc.h"
#include "MApp_ZUI_APIcomponent.h"
#include "msAPI_Memory.h"
#include "MApp_ZUI_APIdraw.h"
#include "drvGPIO.h"
#include "MApp_ZUI_ACTcoexistWin.h"
#include "MApp_UiMenuDef.h"
#include "MApp_GlobalSettingSt.h"
#include "msAPI_audio.h"
#include "GPIO.h"
#include "OSDcp_Bitmap_EnumIndex.h"
#include "apiGOP.h"
#include "MApp_TopStateMachine.h"
#if ENABLE_CI
#include "MApp_CIMMI.h"
#endif
#if (ENABLE_TTX)
#include "msAPI_TTX.h"
#include "mapp_ttx.h"
#endif
#include "MApp_Key.h"
#include "MApp_EpgTimer.h"
#if MHEG5_ENABLE
#include "MApp_MHEG5_Main.h"
#endif
#if (ENABLE_SUBTITLE)
#include "MApp_Subtitle.h"
#endif
#if (ENABLE_MFC_6M20)
#include "drvUrsaMFCAPI.h"
#endif
#include "msAPI_Timer.h"
#include "msAPI_CEC.h"
#if(ENABLE_ATSC)
#include "MApp_ZUI_ACTmenufunc.h"
#endif
#include "Utl.h"

#if ENABLE_ATSC_TTS
#include "MApp_Audio.h"
//#include "MApp_TTSControlHandler.h"
#include "MApp_TTS_Cus.h"
#endif
#if ENABLE_KEY_TO_SPEECH
#include "MApp_KeyToSpeech.h"
#endif

/////////////////////////////////////////////////////////////////////
extern BOOLEAN _MApp_ZUI_API_AllocateVarData(void);

extern void _MApp_ZUI_API_ConvertTextComponentToDynamic(U16 u16TextOutIndex, DRAW_TEXT_OUT_DYNAMIC * pComp);
//**************************************************************************
#if(UI_SKIN_SEL ==  UI_SKIN_1366X768X565)
#define MUTE_GWIN_X    20
#define MUTE_GWIN_Y    84
#define MUTE_GWIN_W    168
#define MUTE_GWIN_H    58

#define MUTE_GWIN_PA_X    20//(PA-power amplifier)
#define MUTE_GWIN_PA_Y    84
#define MUTE_GWIN_PA_W   440
#define MUTE_GWIN_PA_H    58

#define MBOX_GWIN_X    515//384
#define MBOX_GWIN_Y    240
#define MBOX_GWIN_W   336//600
#define MBOX_GWIN_H   280//250

#define ARC_GWIN_X    20
#define ARC_GWIN_Y    84
#define ARC_GWIN_W   440
#define ARC_GWIN_H    58

#elif(UI_SKIN_SEL ==  UI_SKIN_1920X1080X565)
#define MUTE_GWIN_X    28
#define MUTE_GWIN_Y    118
#define MUTE_GWIN_W    240
#define MUTE_GWIN_H    81

#define MUTE_GWIN_PA_X    28//(PA-power amplifier)
#define MUTE_GWIN_PA_Y    118
#define MUTE_GWIN_PA_W   614
#define MUTE_GWIN_PA_H    81

#define MBOX_GWIN_X    780
#define MBOX_GWIN_Y    340
#define MBOX_GWIN_W   464
#define MBOX_GWIN_H   389

#define ARC_GWIN_X    28
#define ARC_GWIN_Y    118
#define ARC_GWIN_W   614
#define ARC_GWIN_H    81
#else
#define MUTE_GWIN_X    20
#define MUTE_GWIN_Y    84
#define MUTE_GWIN_W    112
#define MUTE_GWIN_H    40

#define MUTE_GWIN_PA_X    20//(PA-power amplifier)
#define MUTE_GWIN_PA_Y    84
#define MUTE_GWIN_PA_W   440
#define MUTE_GWIN_PA_H    58

#define MBOX_GWIN_X    515//384
#define MBOX_GWIN_Y    240
#define MBOX_GWIN_W   336//600
#define MBOX_GWIN_H   280//250

#define ARC_GWIN_X    20
#define ARC_GWIN_Y    84
#define ARC_GWIN_W   440
#define ARC_GWIN_H    58
#endif

#if 1//ENABLE_TEMPERATURE_DETECT
#define TEMP_DET_GWIN_X   380
#define TEMP_DET_GWIN_Y   190
#define TEMP_DET_GWIN_W   95
#define TEMP_DET_GWIN_H   100
#endif

#define BAT_LOW_GWIN_X   331//240
#define BAT_LOW_GWIN_Y   195//190
#define BAT_LOW_GWIN_W  192//374
#define BAT_LOW_GWIN_H  90//100
extern U8 bPowerLowFlag ; 

#if (ENABLE_EASMONITOR)
#if (UI_SKIN_SEL == UI_SKIN_1920X1080X565)
#define EAS_GWIN_X    0
#define EAS_GWIN_Y    84
#define EAS_GWIN_W    1920
#define EAS_GWIN_H    81
#elif (UI_SKIN_SEL == UI_SKIN_960X540X565)
#define EAS_GWIN_X    0
#define EAS_GWIN_Y    84
#define EAS_GWIN_W    960
#define EAS_GWIN_H    40
#elif (UI_SKIN_SEL == UI_SKIN_960X540XI8)
#define EAS_GWIN_X    0
#define EAS_GWIN_Y    84
#define EAS_GWIN_W    960
#define EAS_GWIN_H    40
#else // UI_SKIN_1366X768X565
#define EAS_GWIN_X    0
#define EAS_GWIN_Y    84
#define EAS_GWIN_W    1360
#define EAS_GWIN_H    58
#endif
#endif

#define CW_DEBUG(x)     //x

typedef struct _OSD_WIN
{
    U8      u8GwinID;
    U8      u8FBID;
    U16     u16GWin_x;
    U16     u16GWin_y;
    U16     u16GWin_w;
    U16     u16GWin_h;
} ZUI_OSD_WIN;

typedef struct
{
    MS_U32 u32NonMirrorFBAdr;
    MS_U16 u16NonMirrorHStr;
    MS_U16 u16NonMirrorHEnd;
    MS_U16 u16NonMirrorVStr;
    MS_U16 u16NonMirrorVEnd;
}ZUI_MUTE_MirrorInfo;

static ZUI_OSD_WIN CoexistWin;
static U8 u8OriGOP;
static U8 u8OriGwin;
static U8 u8MuteFBID =0xFF;  //we havr to keep Mute FB for CAPE

#if (ENABLE_UI_3D_PROCESS)
#define CO_GWIN_WIDTH      1366
#define CO_GWIN_HEIGHT     768
#endif

static U32 ARCDiscTime = 0;

#if (ENABLE_EASMONITOR)
static ZUI_MUTE_MirrorInfo sEASMirInfo;
#endif

extern void _MApp_ZUI_API_DrawStyleList(const GRAPHIC_DC * pdc, const RECT * rect, const DRAWSTYLE * style_list);

////
static void _MApp_MUTE_fpGOP_CB(MS_U32 u32EventID, void* reserved0)
{
    //printf("_MApp_MUTE_fpGOP_CB\n");
    reserved0=reserved0;
    //if(enMainMenuState == STATE_MENU_WAIT)
    {
        if(E_GOP_EVENT_BUF_ARRANGE_BEGIN == u32EventID)
        {

        }
        else if(E_GOP_EVENT_BUF_ARRANGE_END == u32EventID)
        {

        }
    }
}

void MApp_fpGOP_CB(MS_U32 u32EventID, void* reserved0)
{
    //printf("_MApp_fpGOP_CB\n");
    #if MHEG5_ENABLE
    MApp_MHEG5_fpGOP_CB(u32EventID, reserved0);
    #endif
    MApp_MUTE_fpGOP_CB(u32EventID, reserved0);
}

void MApp_MUTE_fpGOP_CB(MS_U32 u32EventID, void* reserved0)
{
    _MApp_MUTE_fpGOP_CB(u32EventID, reserved0);
}

//******************************************************************************
void MApp_ZUI_ACTcoexistWin_SwitchGwin(void)
{
    u8OriGOP = MApi_GOP_GWIN_GetCurrentGOP();
    u8OriGwin = MApi_GOP_GWIN_GetCurrentWinId();
    //printf("u8OriGOP=%u\n", u8OriGOP);
    //printf("u8OriGwin=%u\n", u8OriGwin);

    if (u8OriGOP != OSD_GOP_ID)
    {
        //printf(" => Switch to GOP=%u\n", OSD_GOP_ID);
        MApi_GOP_GWIN_SwitchGOP(OSD_GOP_ID);
    }

    if (u8OriGwin != CoexistWin.u8GwinID)
    {
        //printf("CoexistWin.u8GwinID=%u\n", CoexistWin.u8GwinID);
        if(MApi_GOP_GWIN_IsGwinExist(CoexistWin.u8GwinID))
        {
            //printf(" => Switch to GWin=%u\n", CoexistWin.u8GwinID);
            MApi_GOP_GWIN_Switch2Gwin(CoexistWin.u8GwinID);
        }
    }
}

void MApp_ZUI_ACTcoexistWin_RestoreGwin(void)
{
    if (u8OriGOP != OSD_GOP_ID)
    {
        //printf(" => Switch to GOP=%u\n", u8OriGOP);
        MApi_GOP_GWIN_SwitchGOP(u8OriGOP);
    }
    if ((u8OriGwin != CoexistWin.u8GwinID) && (u8OriGwin < MAX_GWIN_SUPPORT))
    {
        //printf(" => Switch to GWin=%u\n", u8OriGwin);
        MApi_GOP_GWIN_Switch2Gwin(u8OriGwin);
    }
}

void MApp_ZUI_ACTcoexistWin_Init(void)
{
    GFX_Buffer_Format gefmt;
    MApp_ZUI_ACTcoexistWin_SwitchGwin();

    CoexistWin.u8FBID = 0xFF;
    CoexistWin.u8GwinID = 0xFF;
    u8CoexistWinType = COWIN_ID_NONE;

#if (MPLAYER_BITMAP_FORMAT == MPLAYER_I8)
    gefmt = GFX_FMT_I8;
#elif (MPLAYER_BITMAP_FORMAT == MPLAYER_RGB555)
    gefmt = GFX_FMT_ARGB1555;
#elif (MPLAYER_BITMAP_FORMAT == MPLAYER_ARGB1555)
        gefmt = GFX_FMT_ARGB1555;
#elif (MPLAYER_BITMAP_FORMAT == MPLAYER_RGB565)
    gefmt = GFX_FMT_RGB565;
#elif (MPLAYER_BITMAP_FORMAT == MPLAYER_ARGB4444)
    gefmt = GFX_FMT_ARGB4444;
#elif (MPLAYER_BITMAP_FORMAT == MPLAYER_ARGB8888)
    gefmt = GFX_FMT_ARGB8888;
#else
    #error "unsupported pixel format!"
#endif

    CoexistWin.u8GwinID = MApi_GOP_GWIN_CreateWin(8,8, gefmt); //create default win
    //printf("CoexistWin.u8GwinID=%u\n", CoexistWin.u8GwinID);

    u8MuteFBID = 0xFF;
    //MApp_UiMenu_MuteWin_Create();
    MApi_GOP_GWIN_SetForceWrite(TRUE);

    if(CoexistWin.u8GwinID == GWIN_NO_AVAILABLE)
    {
        CW_DEBUG(printf("Can't create Coexist win\n");)
    }
    else
    {
        MApi_GOP_GWIN_SwapOverlapWin(OSD_GOP_ID, CoexistWin.u8GwinID); //switch to top layer
    }
    MApi_GOP_RegisterEventNotify(MApp_fpGOP_CB);
}

#if (MPLAYER_BITMAP_FORMAT == MPLAYER_I8)
extern void _MApp_ZUI_API_InitPalette(void);
#endif

BOOLEAN MApp_ZUI_ACTcoexist_Create(U8 win_ID, U16 win_x,U16 win_y,U16 win_w,U16 win_h)
{
    U8 u8FbID;
    BOOLEAN bEnableAlpha;
    U8 u8GopAlpha;
    GFX_Buffer_Format gefmt;

    MApp_ZUI_ACTcoexistWin_SwitchGwin();

#if (ENABLE_UI_3D_PROCESS)
    if(MApp_ZUI_API_Is_UI_3D_Mode_ON())
    {
        if(MApp_ZUI_Query_UI_3D_Mode() == E_UI_3D_OUTPUT_SIDE_BY_SIDE_HALF)
        {
            win_x /= 2;
            win_y = win_y;
            win_w = (CO_GWIN_WIDTH + win_w)/2;
            win_h = win_h;
            //win_w = (win_w + 0x03) & ~(0x03);//align-4
            win_w = (win_w + 0x07) & ~(0x07);//align-8
            if(win_x + win_w > 1360)
            {
                win_w = 1360 - win_x;
                if((win_w + 0x07) > 1360)
                    win_w = 1360;
                else
                    win_w = (win_w + 0x07) & ~(0x07);//align-8
            }
        }
        else
        {
            win_x = win_x;
            win_y /= 2;
            win_w = (win_w + 0x07) & ~(0x07);//align-8
            win_h = (CO_GWIN_HEIGHT + win_h)/2;
        }
        printf(" Co-Exit[%d, %d, %d, %d]", win_x, win_y, win_w, win_h);
    }
    //else
#endif
        //if(win_ID == COWIN_ID_MUTE && u8MuteFBID != 0xFF)
        //{
        //    u8FbID = u8MuteFBID;
        //}
        //else
    {
        u8FbID = MApi_GOP_GWIN_GetFreeFBID();

        if (u8FbID == 0xFF)
        {
            CW_DEBUG(printf("[MUTE]:Create FB failed\n"));
            ABORT();
            return FALSE;
        }

#if (MPLAYER_BITMAP_FORMAT == MPLAYER_I8)
        gefmt = GFX_FMT_I8;
#elif (MPLAYER_BITMAP_FORMAT == MPLAYER_RGB555)
        gefmt = GFX_FMT_ARGB1555;
#elif (MPLAYER_BITMAP_FORMAT == MPLAYER_ARGB1555)
        gefmt = GFX_FMT_ARGB1555;
#elif (MPLAYER_BITMAP_FORMAT == MPLAYER_RGB565)
        gefmt = GFX_FMT_RGB565;
#elif (MPLAYER_BITMAP_FORMAT == MPLAYER_ARGB4444)
        gefmt = GFX_FMT_ARGB4444;
#elif (MPLAYER_BITMAP_FORMAT == MPLAYER_ARGB8888)
        gefmt = GFX_FMT_ARGB8888;
#else
        #error "unsupported pixel format!"
#endif

        MApi_GOP_GWIN_CreateFB(u8FbID, 0, 0, win_w, win_h, gefmt);
    }

        MApi_GOP_GWIN_MapFB2Win(u8FbID, CoexistWin.u8GwinID);
        MApi_GOP_GWIN_Switch2FB(u8FbID);
        MApi_GOP_GWIN_SetWinPosition(CoexistWin.u8GwinID, win_x + (MApi_GOP_GWIN_Get_HSTART()), win_y);
        msAPI_OSD_SetClipWindow(0, 0, win_w, win_h);

#if (MPLAYER_BITMAP_FORMAT == MPLAYER_I8)
        bEnableAlpha = TRUE; //alpha table is depend by 256 color table
        u8GopAlpha = 63;
#elif (MPLAYER_BITMAP_FORMAT == MPLAYER_ARGB4444 || MPLAYER_BITMAP_FORMAT == MPLAYER_ARGB8888 )
        //for ARGB4444, ARGB8888 disable GOP alpha
        bEnableAlpha = TRUE;
        u8GopAlpha = 63;
#else
        bEnableAlpha = FALSE;
        u8GopAlpha = (63*9/10);
#endif

        MApi_GOP_GWIN_SetBlending(CoexistWin.u8GwinID, bEnableAlpha, u8GopAlpha);
        MApi_GFX_SetAlpha(FALSE, COEF_CONST, ABL_FROM_CONST, 0xFF); //=> msAPI_OSD_DisableAlpha();

        /* #1309984 - I8 mode ATV source, enable Mute icon, switch on/off Main menu page raipdly about 2mins, Mute background transparent.*/
    #if 0//(MPLAYER_BITMAP_FORMAT == MPLAYER_I8)
        _MApp_ZUI_API_InitPalette(); //before set palette for GOP
        MApi_GOP_GWIN_SetTransClr(GOPTRANSCLR_FMT1, 0); //NOTE: index color 0 is transparent
        MApi_GOP_GWIN_EnableTransClr(GOPTRANSCLR_FMT1,TRUE);
    #else
        MApi_GOP_GWIN_SetFMT0TransClr(0);
    #endif
        //if(win_ID != COWIN_ID_MUTE)
        {
            clrBtn1.x = 0;
            clrBtn1.y = 0;
            clrBtn1.width = win_w;
            clrBtn1.height = win_h;
            clrBtn1.b_clr = 0x0;
            clrBtn1.u8Gradient = CONSTANT_COLOR;
            clrBtn1.fHighLight = FALSE;
            msAPI_OSD_DrawBlock(&clrBtn1); //clean win
        }
    MApi_GOP_GWIN_SetForceWrite(FALSE);
    /////////////////////////////////////////////////////////
    u8CoexistWinType = win_ID;
    CoexistWin.u8FBID = u8FbID;
    CoexistWin.u16GWin_x = win_x;
    CoexistWin.u16GWin_y = win_y;
    CoexistWin.u16GWin_h = win_h;
    CoexistWin.u16GWin_w = win_w;

    MApp_ZUI_ACTcoexistWin_RestoreGwin();
    return TRUE;
}

//not really delete Gwin, just reset u8CoexistWinType
void MApp_ZUI_ACTcoexist_Delete( void)
{
    U8 u8FBID=0xFF;

    if(u8CoexistWinType != COWIN_ID_NONE)
    {
        MApp_ZUI_ACTcoexistWin_SwitchGwin();
        MApi_GOP_GWIN_Enable(CoexistWin.u8GwinID, FALSE);

        //if(u8CoexistWinType == COWIN_ID_MUTE || u8CoexistWinType == COWIN_ID_PA_MUTE)
        //{//do nothing
        //}
        //else
        //{
        //    MApi_GOP_GWIN_DeleteWin(CoexistWin.u8GwinID);
        //}
        u8FBID=MApi_GOP_GWIN_GetFBfromGWIN(CoexistWin.u8GwinID);
        MApi_GOP_GWIN_DeleteFB(u8FBID);

        CoexistWin.u8FBID = 0xFF;
        u8CoexistWinType = COWIN_ID_NONE;

        //if(msAPI_AUD_IsAudioMutedByUser()) //redraw MUTE icon
            //MApp_UiMenu_MuteWin_Show();

        MApp_ZUI_ACTcoexistWin_RestoreGwin();
    }
}

#if 1//(ENABLE_UI_3D_PROCESS)
void MApp_ZUI_ACTcoexist_RealDelete( void)
{
    //printf("MApp_ZUI_ACTcoexist_RealDelete()\n");

    if(u8CoexistWinType != COWIN_ID_NONE)
    {
        MApp_ZUI_ACTcoexistWin_SwitchGwin();
        MApi_GOP_GWIN_Enable(CoexistWin.u8GwinID, FALSE);

        MApi_GOP_GWIN_DeleteFB(CoexistWin.u8FBID);

        CoexistWin.u8FBID = 0xFF;
        u8CoexistWinType = COWIN_ID_NONE;

        //if(msAPI_AUD_IsAudioMutedByUser()) //redraw MUTE icon
            //MApp_UiMenu_MuteWin_Show();

        MApp_ZUI_ACTcoexistWin_RestoreGwin();
    }
    u8MuteFBID = 0xFF;
}
#endif

void MApp_ZUI_ACTcoexist_Enable(BOOLEAN bEnable)
{
    //printf("MApp_ZUI_ACTcoexist_Enable(bEnable=%u)\n", bEnable);
    MApp_ZUI_ACTcoexistWin_SwitchGwin();
    MApi_GOP_GWIN_Enable(CoexistWin.u8GwinID, bEnable);
    MApp_ZUI_ACTcoexistWin_RestoreGwin();
}

//============================================================================
//static void MApp_UiMenu_MuteWin_Create(void)  //wht120713_3 remove
 void MApp_UiMenu_MuteWin_Create(void)
{
    GRAPHIC_DC Wdc;
    RECT    Wrect;
    WINDOWPOSDATA *t_GUI_WPT;
#if (MirrorEnable)
    GOP_GwinInfo sGWININfo;
#endif
    BOOLEAN  bCreateOk=FALSE;

    DRAWSTYLE * _Zui_Volume_Mute_Pane_Normal_DrawStyle =  _GUI_WindowsDrawStyleList_Zui_Audio_Volume[HWND_VOLUME_MUTE_PANE].pNormalStyle;
    DRAWSTYLE * _Zui_Volume_Mute_Icon_Normal_DrawStyle =  _GUI_WindowsDrawStyleList_Zui_Audio_Volume[HWND_VOLUME_MUTE_ICON].pNormalStyle;
    DRAWSTYLE * _Zui_Volume_Mute_Text_Normal_DrawStyle =  _GUI_WindowsDrawStyleList_Zui_Audio_Volume[HWND_VOLUME_MUTE_TEXT].pNormalStyle;
    DRAWSTYLE * _Zui_Volume_Mute_BG_Normal_DrawStyle =  _GUI_WindowsDrawStyleList_Zui_Audio_Volume[HWND_VOLUME_MUTE_ICON_BG].pNormalStyle;
    //DRAWSTYLE * _Zui_Volume_Mute_BG_R_Normal_DrawStyle =  _GUI_WindowsDrawStyleList_Zui_Audio_Volume[HWND_VOLUME_MUTE_ICON_BG_R].pNormalStyle;
#if (ATSC_CC == ATV_CC)
    if ((IsATVInUse()||IsAVInUse()||IsSVInUse())&& stGenSetting.g_SysSetting.enATVCaptionType != ATV_CAPTION_TYPE_OFF)
    {
        if ( MApp_CC_GetInfo(CC_SELECTOR_STATUS_CODE) == STATE_CAPTION_PARSER)
        {
             MApp_CC_StopParser();
             MApp_Set_CCState(FALSE);
        }
    }
#endif
  //  MApp_ZUI_ACTcoexistWin_SwitchGwin();
#if (ENABLE_UI_3D_PROCESS)
    if(MApp_ZUI_API_Is_UI_3D_Mode_ON())
    {
        MApp_ZUI_API_Set_CoexistWin_Half(TRUE);
    }
#endif

    MApp_ZUI_ACTcoexist_Delete();
    bCreateOk=MApp_ZUI_ACTcoexist_Create(COWIN_ID_MUTE, MUTE_GWIN_X, MUTE_GWIN_Y, MUTE_GWIN_W, MUTE_GWIN_H);
    if(bCreateOk==FALSE)
    {
        printf(" MuteWin_Create  fail\n");
        return;
    }
#if (ENABLE_UI_3D_PROCESS)
    if(MApp_ZUI_API_Is_UI_3D_Mode_ON())
    {
        Wdc = MApp_ZUI_API_CreateDC(MUTE_GWIN_W, MUTE_GWIN_H);
    }
    else
#endif
    {
    Wdc.u8FbID = CoexistWin.u8FBID;
    }

    u8MuteFBID = CoexistWin.u8FBID;
    Wdc.u8ConstantAlpha = 0xFF;

    t_GUI_WPT = g_GUI_WindowPositionList;
    g_GUI_WindowPositionList = _GUI_WindowPositionList_Zui_Audio_Volume;

    MApp_ZUI_API_GetWindowInitialRect(HWND_VOLUME_MUTE_PANE,&Wrect);
    _MApp_ZUI_API_DrawStyleList(&Wdc, &Wrect, _Zui_Volume_Mute_Pane_Normal_DrawStyle);
    MApp_ZUI_API_GetWindowInitialRect(HWND_VOLUME_MUTE_ICON_BG,&Wrect);
    _MApp_ZUI_API_DrawStyleList(&Wdc, &Wrect, _Zui_Volume_Mute_BG_Normal_DrawStyle);
    //MApp_ZUI_API_GetWindowInitialRect(HWND_VOLUME_MUTE_ICON_BG_R,&Wrect);
    //_MApp_ZUI_API_DrawStyleList(&Wdc, &Wrect, _Zui_Volume_Mute_BG_R_Normal_DrawStyle);
    MApp_ZUI_API_GetWindowInitialRect(HWND_VOLUME_MUTE_ICON,&Wrect);
    _MApp_ZUI_API_DrawStyleList(&Wdc, &Wrect, _Zui_Volume_Mute_Icon_Normal_DrawStyle);
    MApp_ZUI_API_GetWindowInitialRect(HWND_VOLUME_MUTE_TEXT,&Wrect);
    _MApp_ZUI_API_DrawStyleList(&Wdc, &Wrect, _Zui_Volume_Mute_Text_Normal_DrawStyle);

    g_GUI_WindowPositionList = t_GUI_WPT;

#if (ENABLE_UI_3D_PROCESS)
    if(MApp_ZUI_API_ConvertTo3DTwinModeOutput(Wdc.u8FbID, CoexistWin.u8FBID, MUTE_GWIN_W, MUTE_GWIN_H) == TRUE)
    {
        MApp_ZUI_API_DeleteDC(Wdc);
    }
    MApp_ZUI_API_Set_CoexistWin_Half(FALSE);
#endif

#if (MirrorEnable)
    MApi_GOP_GWIN_GetWinInfo(CoexistWin.u8GwinID, &sGWININfo);
    sMuteMirInfo.u32NonMirrorFBAdr = sGWININfo.u32DRAMRBlkStart;
    sMuteMirInfo.u16NonMirrorHEnd = sGWININfo.u16DispHPixelEnd;
    sMuteMirInfo.u16NonMirrorHStr = sGWININfo.u16DispHPixelStart;
    sMuteMirInfo.u16NonMirrorVStr = sGWININfo.u16DispVPixelStart;
    sMuteMirInfo.u16NonMirrorVEnd = sGWININfo.u16DispVPixelEnd;
#endif
    //MApp_ZUI_ACTcoexistWin_RestoreGwin();
}

//============================================================================
#if(ENABLE_CEC)
static void MApp_UiMenu_PAMuteWin_Create(void)
{
    GRAPHIC_DC Wdc = {0, 0, 0};
    RECT    Wrect;
    WINDOWPOSDATA *t_GUI_WPT;
    //DRAWSTYLE * _Zui_Volume_Mute_Pane_Normal_DrawStyle =  _GUI_WindowsDrawStyleList_Zui_Audio_Volume[HWND_VOLUME_MUTE_PANE].pNormalStyle;
    DRAWSTYLE * _Zui_Volume_Mute_Icon_Normal_DrawStyle =  _GUI_WindowsDrawStyleList_Zui_Audio_Volume[HWND_VOLUME_MUTE_ICON].pNormalStyle;
    DRAWSTYLE * _Zui_Volume_Mute_Text_Normal_DrawStyle =  _GUI_WindowsDrawStyleList_Zui_Audio_Volume[HWND_VOLUME_MUTE_TEXT].pNormalStyle;
    DRAWSTYLE * _Zui_Volume_Mute_BG_Normal_DrawStyle =  _GUI_WindowsDrawStyleList_Zui_Audio_Volume[HWND_VOLUME_MUTE_ICON_BG].pNormalStyle;
    DRAWSTYLE * _Zui_Volume_Power_Amplifier_Normal_DrawStyle =  _GUI_WindowsDrawStyleList_Zui_Audio_Volume[HWND_VOLUME_POWER_AMPLIFIER].pNormalStyle;
#if(ENABLE_OSD_SUBTITLE_EXCLUSIVE == ENABLE)
    #if (ENABLE_SUBTITLE)
        if (IsDTVInUse())
        {
            if (( MApp_Subtitle_GetStatus() == STATE_SUBTITLE_DECODING)
#if(ENABLE_TTX)
                ||(MApp_TTX_IsTeletextOn()&&stGenSetting.g_SysSetting.fEnableTTXSubTitle)
#endif
                )
            {
                 MApp_Subtitle_SetShowStatus(FALSE);
            }
        }
    #endif
#endif

    RECT rectPane;
    RECT rectAmp;

    t_GUI_WPT = g_GUI_WindowPositionList;
    g_GUI_WindowPositionList = _GUI_WindowPositionList_Zui_Audio_Volume;

    MApp_ZUI_API_GetWindowInitialRect(HWND_VOLUME_MUTE_PANE, &rectPane);
    MApp_ZUI_API_GetWindowInitialRect(HWND_VOLUME_POWER_AMPLIFIER, &rectAmp);

    rectAmp.left = rectPane.left + rectPane.width;

    rectAmp.width = GE_ALIGNED_VALUE(rectPane.width+rectAmp.width, 8) - rectPane.width;

    //MApp_ZUI_ACTcoexistWin_SwitchGwin();

    MApp_ZUI_ACTcoexist_Delete();

    MApp_ZUI_ACTcoexist_Create(COWIN_ID_PA_MUTE, MUTE_GWIN_PA_X, MUTE_GWIN_PA_Y, rectPane.width+rectAmp.width, rectPane.height);

    Wdc.u8FbID = CoexistWin.u8FBID;
    u8MuteFBID = CoexistWin.u8FBID;
    Wdc.u8ConstantAlpha = 0xFF;

    //MApp_ZUI_API_GetWindowInitialRect(HWND_VOLUME_POWER_AMPLIFIER,&Wrect);
    _MApp_ZUI_API_DrawStyleList(&Wdc, &rectAmp, _Zui_Volume_Power_Amplifier_Normal_DrawStyle);
    // MApp_ZUI_API_GetWindowInitialRect(HWND_VOLUME_MUTE_PANE,&Wrect);
    //_MApp_ZUI_API_DrawStyleList(&Wdc, &Wrect, _Zui_Volume_Mute_Pane_Normal_DrawStyle);
    MApp_ZUI_API_GetWindowInitialRect(HWND_VOLUME_MUTE_ICON_BG,&Wrect);
    _MApp_ZUI_API_DrawStyleList(&Wdc, &Wrect, _Zui_Volume_Mute_BG_Normal_DrawStyle);
    MApp_ZUI_API_GetWindowInitialRect(HWND_VOLUME_MUTE_ICON,&Wrect);
    _MApp_ZUI_API_DrawStyleList(&Wdc, &Wrect, _Zui_Volume_Mute_Icon_Normal_DrawStyle);
    MApp_ZUI_API_GetWindowInitialRect(HWND_VOLUME_MUTE_TEXT,&Wrect);
    _MApp_ZUI_API_DrawStyleList(&Wdc, &Wrect, _Zui_Volume_Mute_Text_Normal_DrawStyle);

    g_GUI_WindowPositionList = t_GUI_WPT;

    //MApp_ZUI_ACTcoexistWin_RestoreGwin();
}
#endif

//***************************************************************
//* return: 0 : not show MUTE icon
//*         1 : delete all win and show MUTE icon(due to use same GWIN ID)
//*         2 : show MUTE icon but not delete all GWIN
//***************************************************************
static U8 MApp_UiMenu_NeedShowMuteIcon(void)
{
#if ENABLE_TTX
    if(MApp_TTX_IsTeletextOn()&&MApp_TTX_GetControlMode()==TTX_MODE_NORMAL) //draw nothing in TTX mode
        return 0;
#endif

    if ( (MApp_TopStateMachine_GetTopState()== STATE_TOP_ATV_SCAN)
        #if ENABLE_DVB
        || (MApp_TopStateMachine_GetTopState()== STATE_TOP_DTV_SCAN)
        #endif
        )
        return 0;

    //    if((u8CoexistWinType != COWIN_ID_MUTE)
    //        && (u8CoexistWinType != 0xFF))
    //        return 0;

    if(CoexistWin.u8GwinID == 0xFF)
    {
        MS_DEBUG_MSG(printf("CoexistWin.u8GwinID is not created.\n"));
        return 0;
    }

    if(MApp_ZUI_GetActiveOSD() == E_OSD_AUDIO_VOLUME)
        return 1;
#if (ENABLE_EASMONITOR)
    if(u8CoexistWinType == COWIN_ID_EAS)
        return 3;
#endif
    return 2;
}

//BOOLEAN MApp_UiMenu_ARCDiscWin_Update(void)
//{

//}

void MApp_UiMenu_ARCDeviceStatusWin_Create(BOOLEAN isConnect)
{
    GRAPHIC_DC Wdc = {0, 0, 0};
    RECT       Wrect = {0, 0, 0, 0};
    WINDOWPOSDATA *t_GUI_WPT;
    U16 u16index =0;

    DRAWSTYLE * _Zui_Volume_Power_Amplifier_Normal_DrawStyle =  _GUI_WindowsDrawStyleList_Zui_Audio_Volume[HWND_ARC_DISCONNECT_WINDOW].pNormalStyle;
    DRAWSTYLE * style_list = _Zui_Volume_Power_Amplifier_Normal_DrawStyle;
    if(style_list != NULL)
    {
        while(style_list->component != CP_NOON)
        {
            if(style_list->component == CP_TEXT_OUT)
            {
                u16index = style_list->u16Index;
                break;
            }
            ++style_list;
        }
        printf("\n index :%d   [%s,%s,%d] \n",u16index,__FUNCTION__,__FILE__,__LINE__);
        if(isConnect==TRUE)
        {
            _Zui_TextOut_List[u16index].StringID = en_str_ARC_Device_Connect;
        }
        else
        {
            _Zui_TextOut_List[u16index].StringID = en_str_Disconnect_ARC_Device;
        }
    }

    //MApp_ZUI_ACTcoexistWin_SwitchGwin();

    MApp_ZUI_ACTcoexist_Delete();
    MApp_ZUI_ACTcoexist_Create(COWIN_ID_ARC_DISC_WIN, ARC_GWIN_X, ARC_GWIN_Y, ARC_GWIN_W, ARC_GWIN_H);


    Wdc.u8FbID = CoexistWin.u8FBID;
    u8MuteFBID = CoexistWin.u8FBID;
    Wdc.u8ConstantAlpha = 0xFF;

    t_GUI_WPT = g_GUI_WindowPositionList;
    g_GUI_WindowPositionList = _GUI_WindowPositionList_Zui_Audio_Volume;

    MApp_ZUI_API_GetWindowInitialRect(HWND_ARC_DISCONNECT_WINDOW,&Wrect);
    printf("%d %d %d %d\n",Wrect.left,Wrect.top,Wrect.width,Wrect.height);
    _MApp_ZUI_API_DrawStyleList(&Wdc, &Wrect, _Zui_Volume_Power_Amplifier_Normal_DrawStyle);

    g_GUI_WindowPositionList = t_GUI_WPT;
    //MApp_ZUI_ACTcoexistWin_RestoreGwin();
}

void MApp_UiMenu_ARCDeviceStatusWin_Show(BOOLEAN IsConnect)
{
    if(u8CoexistWinType != COWIN_ID_ARC_DISC_WIN)
    {
        ARCDiscTime = msAPI_Timer_GetTime0();
        MApp_UiMenu_ARCDeviceStatusWin_Create(IsConnect);
        MApp_ZUI_ACTcoexist_Enable(TRUE);
    }
}

void MApp_UiMenu_ARCDeviceStatusWin_Hide(void)
{
    U8 u8FBID=0xFF;

    if(u8CoexistWinType == COWIN_ID_ARC_DISC_WIN)
    {
        MApp_ZUI_ACTcoexist_Enable(FALSE);
        u8FBID=MApi_GOP_GWIN_GetFBfromGWIN(CoexistWin.u8GwinID);
        MApi_GOP_GWIN_DeleteFB(u8FBID);
        CoexistWin.u8FBID = 0xFF;
        u8CoexistWinType = COWIN_ID_NONE;
    }
}

void MApp_UiMenu_ARCDiscWin_State(void)
{
    if(msAPI_Timer_DiffTimeFromNow(ARCDiscTime) > 3000)
    {
        MApp_UiMenu_ARCDeviceStatusWin_Hide();
    }
}

void MApp_UiMenu_MuteWin_Show(void)
{
    //printf("MApp_UiMenu_MuteWin_Show()\n");
    U8 ret = MApp_UiMenu_NeedShowMuteIcon();


    if( ret == 1 )
    {
        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD); //close current window
    }


    //switch(ret)
    {
        //case 1:
            //MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD); //close current window
            //go on show MUTE win
        //case 2:
        //default:
        #if(ENABLE_CEC)
            if( MApp_CEC_ARC_Is_ExtAudioDeviceConnected() )
          /* #if(CEC_VERSION_USING == CEC_NEW_VERSION)
            if(msAPI_CEC_IsAudioSystemKeyValid() == TRUE)
          #else
            if(msAPI_CEC_ARC_Is_Connect() == TRUE)//anvi22
          #endif */
            {
            //    if(u8CoexistWinType != COWIN_ID_PA_MUTE)
                {
                    MApp_UiMenu_PAMuteWin_Create(); //prepare PA MUTE window, maybe can rewrite to reduce boot up time
                }
                MApp_ZUI_ACTcoexist_Enable(TRUE);
            }
            else
        #endif
            {
                //if(u8CoexistWinType != COWIN_ID_MUTE)
                {
                    MApp_UiMenu_MuteWin_Create(); //prepare MUTE window, maybe can rewrite to reduce boot up time
                }
                MApp_ZUI_ACTcoexist_Enable(TRUE);
              #if (ENABLE_MFC_6M20)
                 MDrv_Ursa_SetOsdArea(MUTE_GWIN_X, MUTE_GWIN_Y, MUTE_GWIN_W, MUTE_GWIN_H);
              #endif
            }
            //break;
    }

#if ENABLE_TTX
    if (MApp_TTX_GetControlMode() == TTX_MODE_SUBTITLE)
    {
        MApp_TTX_BackToTTXMode();
    }
#endif

}

void MApp_UiMenu_MuteWin_Hide(void)
{
    //printf("MApp_UiMenu_MuteWin_Hide()\n");

#if(ENABLE_CEC)
    if( MApp_CEC_ARC_Is_ExtAudioDeviceConnected() )
/*#if(CEC_VERSION_USING == CEC_NEW_VERSION)
    if(msAPI_CEC_IsAudioSystemKeyValid() == TRUE)
#else
    if(msAPI_CEC_ARC_Is_Connect() == TRUE)
#endif*/
    {
        if(u8CoexistWinType == COWIN_ID_PA_MUTE)
        {
            MApp_ZUI_ACTcoexist_Enable(FALSE);
        }
    }
    else
#endif
    {
        if(u8CoexistWinType == COWIN_ID_MUTE)
        {
            //MApp_ZUI_ACTcoexist_Enable(FALSE);
            MApp_ZUI_ACTcoexist_RealDelete();
          #if (ENABLE_MFC_6M20)
            MDrv_Ursa_DisableOsdArea(FALSE);
          #endif

            u8CoexistWinType = COWIN_ID_NONE;
        }
    }
}

#if DTG_FREEVIEW_STANDBY
extern BOOLEAN MApp_FreeView_Is_Standby(void);
#endif

#if(ENABLE_CEC)
void MApp_ARC_KeyProc_Mute(void)
{
    u8KeyCode = KEY_NULL;

#if DTG_FREEVIEW_STANDBY
    if(MApp_FreeView_Is_Standby())
        return;
#endif

    if (msAPI_CEC_ARC_GetAmpMute() == FALSE)
    {
        MApp_UiMenu_MuteWin_Show();
        msAPI_CEC_ARC_SetAmpMute(TRUE);
    }
    else
    {
    #if ENABLE_TTX
        if (MApp_TTX_GetControlMode() == TTX_MODE_SUBTITLE)
        {
            MApp_TTX_BackToOSDMode();
        }
    #endif

        MApp_UiMenu_MuteWin_Hide();
        msAPI_CEC_ARC_SetAmpMute(FALSE);

    #if ENABLE_TTX
        if (MApp_TTX_GetControlMode() == TTX_MODE_SUBTITLE)
        {
            MApp_TTX_BackToTTXMode();
        }
    #endif
    }
}
#endif

void MApp_KeyProc_Mute(void)
{
    BOOLEAN bIsAudioMuted;

    printf("MApp_KeyProc_Mute()\n");

    bIsAudioMuted = msAPI_AUD_IsAudioMutedByUser();
    u8KeyCode = KEY_NULL;

#if DTG_FREEVIEW_STANDBY
    if(MApp_FreeView_Is_Standby())
        return;
#endif

    if (bIsAudioMuted == FALSE) // Currently is unmute
    {   // unmute ==> mute

    #if(ENABLE_ATSC_TTS)
        // Speak "mute"...
        MApp_TTS_Cus_AddU16StrAndWaitSayFinish( MApp_ZUI_API_GetString(en_str_MUTE), TRUE, 3000); // Max wait 3000ms
    #endif
#if ENABLE_KEY_TO_SPEECH
        MApp_KTS_Say(EN_KTS_MUTE_ON);
        while(!MApp_KTS_IsAudioFinished());
#endif

        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);

      #if ENABLE_CI
        if(!bActiveMMI) // MediaSet
      #endif
        {
        	printf("MApp_KeyProc_Mute()MUTE_On 111111\n");
            MUTE_On();
            MApp_UiMenu_MuteWin_Show();
        }

    }
    else // Currently is mute
    {   // Mute ==> unmute

    #if ENABLE_TTX
        if(MApp_TTX_GetControlMode()==TTX_MODE_SUBTITLE)
        {
            MApp_TTX_BackToOSDMode();
        }
    #endif

        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
#if ENABLE_KEY_TO_SPEECH
        MApp_KTS_Say(EN_KTS_MUTE_OFF);
#endif

    #if ENABLE_CI
        if(!bActiveMMI) // MediaSet
    #endif
        {
        	printf("MApp_KeyProc_Mute()MUTE_Off 222222\n");
            MUTE_Off();
            MApp_UiMenu_MuteWin_Hide();
        }

    #if ENABLE_TTX
        if(MApp_TTX_GetControlMode()==TTX_MODE_SUBTITLE)
        {
            MApp_TTX_BackToTTXMode();
        }
    #endif

    #if ENABLE_ATSC_TTS
        if (msAPI_AUD_IsAudioMutedByUser() == FALSE)
        {
            //U16 u16Len = 0;
            //u16Len = MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(en_str_MUTE));
            //MApp_TTSControlSetTextAndSay(MApp_ZUI_API_GetString(en_str_MUTE), u16Len);

            // Speak "mute"...
            MApp_TTS_Cus_AddU16StrAndWaitSayFinish( MApp_ZUI_API_GetString(en_str_MUTE), TRUE, 3000); // Max wait 3000ms
        }
    #endif
    }

#if ENABLE_ATSC
    if (MApp_ZUI_GetActiveOSD() != E_OSD_DMP)
    {
    #if (PARSING_CC_WHENMUTE)
        MApp_UiMenuFunc_CCGetUserCmd();
    #endif
    }
#endif
}

#if 1
static void MApp_UiMenu_TempDetWin_Create(void)
{
    printf("MApp_UiMenu_BatLowWin_Create \n"); 
    GRAPHIC_DC Wdc;
    RECT    Wrect;
    WINDOWPOSDATA *t_GUI_WPT;

    BOOLEAN  bCreateOk=FALSE;

    DRAWSTYLE * _Zui_Temp_Det_Warning_Window_Normal_DrawStyle =  _GUI_WindowsDrawStyleList_Zui_Temp_Det[HWND_TEMP_DET_WARNING_WINDOW].pNormalStyle;
    DRAWSTYLE * _Zui_Temp_Det_Hint_Text_Normal_DrawStyle =  _GUI_WindowsDrawStyleList_Zui_Temp_Det[HWND_TEMP_DET_HINT1_TEXT].pNormalStyle;
    DRAWSTYLE * _Zui_Temp_Det_Charge_Text_Normal_DrawStyle =  _GUI_WindowsDrawStyleList_Zui_Temp_Det[HWND_TEMP_DET_HINT2_TEXT].pNormalStyle;

	
    printf(" MApp_ZUI_ACTcoexist_Delete 1 \n");
    MApp_ZUI_ACTcoexist_Delete(); 
    //bCreateOk=MApp_ZUI_ACTcoexist_Create(COWIN_ID_BAT_LOW, MUTE_GWIN_X, MUTE_GWIN_Y, MUTE_GWIN_W, MUTE_GWIN_H);
    bCreateOk=MApp_ZUI_ACTcoexist_Create(COWIN_ID_TEMP_DET, TEMP_DET_GWIN_X, TEMP_DET_GWIN_Y, TEMP_DET_GWIN_W, TEMP_DET_GWIN_H);
    if(bCreateOk==FALSE)
    {
        printf(" BatLowWarning_Create  fail\n"); 
        return;
    }
	
    
    Wdc.u8FbID = CoexistWin.u8FBID;
     
    u8MuteFBID = CoexistWin.u8FBID;
    Wdc.u8ConstantAlpha = 0xFF;

    t_GUI_WPT = g_GUI_WindowPositionList;
    g_GUI_WindowPositionList = _GUI_WindowPositionList_Zui_Temp_Det;

    MApp_ZUI_API_GetWindowInitialRect(HWND_TEMP_DET_WARNING_WINDOW,&Wrect);
 
    _MApp_ZUI_API_DrawStyleList(&Wdc, &Wrect, _Zui_Temp_Det_Warning_Window_Normal_DrawStyle);
    MApp_ZUI_API_GetWindowInitialRect(HWND_TEMP_DET_HINT1_TEXT,&Wrect);

    _MApp_ZUI_API_DrawStyleList(&Wdc, &Wrect, _Zui_Temp_Det_Hint_Text_Normal_DrawStyle);
    MApp_ZUI_API_GetWindowInitialRect(HWND_TEMP_DET_HINT2_TEXT,&Wrect);

    _MApp_ZUI_API_DrawStyleList(&Wdc, &Wrect, _Zui_Temp_Det_Charge_Text_Normal_DrawStyle);

    g_GUI_WindowPositionList = t_GUI_WPT;
	u8CoexistWinType = COWIN_ID_TEMP_DET;
    //MApp_ZUI_ACTcoexistWin_RestoreGwin();
}
void MApp_UiMenu_TempDetWin_Show(void)
{
		if(//(MApp_ZUI_GetActiveOSD() == E_OSD_BAT_PERCENTAGE)||
	   	(MApp_ZUI_GetActiveOSD() == E_OSD_SCREEN_SAVER))
	   	   MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
		   
        if(u8CoexistWinType != COWIN_ID_TEMP_DET)
        {
            printf("u8CoexistWinType != COWIN_ID_BAT_LOW \n"); //change by gchen @ 20110714
            MApp_UiMenu_TempDetWin_Create(); 
			MApp_ZUI_ACTcoexist_Enable(TRUE);
			//bTempHighFlag = 1;
        }
		else
		{

		}      
	
}

void MApp_UiMenu_TempDetWin_Hide(void)
{
     U8 u8FBID=0XFF;

    if(u8CoexistWinType == COWIN_ID_TEMP_DET)
    {
        MApp_ZUI_ACTcoexist_Enable(FALSE);
        u8FBID=MApi_GOP_GWIN_GetFBfromGWIN(CoexistWin.u8GwinID);
        MApi_GOP_GWIN_DeleteFB(u8FBID);
        CoexistWin.u8FBID = 0xFF;
        u8CoexistWinType = COWIN_ID_NONE;
		//bTempHighFlag = 0;
    }
}
#endif

static void MApp_UiMenu_BatLowWin_Create(void)
{
    printf("MApp_UiMenu_BatLowWin_Create \n"); 
    GRAPHIC_DC Wdc;
    RECT    Wrect;
    WINDOWPOSDATA *t_GUI_WPT;

    BOOLEAN  bCreateOk=FALSE;

    #if 0
    DRAWSTYLE * _Zui_Volume_Bat_Low_Alert_Win_Normal_DrawStyle = _GUI_WindowsDrawStyleList_Zui_Message_Box[HWND_MSG_ALERT_WINDOW].pNormalStyle;
    DRAWSTYLE * _Zui_Volume_Bat_Low_Alert_Icon_Normal_DrawStyle = _GUI_WindowsDrawStyleList_Zui_Message_Box[HWND_MSG_ALERT_ICON].pNormalStyle;
    DRAWSTYLE * _Zui_Volume_Bat_Low_Alert_Text_Normal_DrawStyle = _GUI_WindowsDrawStyleList_Zui_Message_Box[HWND_MSG_ALERT_STRING].pNormalStyle;
    #elif 0
    DRAWSTYLE * _Zui_Volume_Mute_Pane_Normal_DrawStyle =  _GUI_WindowsDrawStyleList_Zui_Audio_Volume[HWND_VOLUME_MUTE_PANE].pNormalStyle;
    DRAWSTYLE * _Zui_Volume_Mute_Icon_Normal_DrawStyle =  _GUI_WindowsDrawStyleList_Zui_Audio_Volume[HWND_VOLUME_MUTE_ICON].pNormalStyle;
    DRAWSTYLE * _Zui_Volume_Mute_Text_Normal_DrawStyle =  _GUI_WindowsDrawStyleList_Zui_Audio_Volume[HWND_VOLUME_MUTE_TEXT].pNormalStyle;
    #else
    DRAWSTYLE * _Zui_Bat_Low_Warning_Window_Normal_DrawStyle =  _GUI_WindowsDrawStyleList_Zui_Bat_Low[HWND_BAT_LOW_WARNING_WINDOW].pNormalStyle;
    DRAWSTYLE * _Zui_Bat_Low_Hint_Text_Normal_DrawStyle =  _GUI_WindowsDrawStyleList_Zui_Bat_Low[HWND_BAT_LOW_HINT_TEXT].pNormalStyle;
    DRAWSTYLE * _Zui_Bat_Low_Charge_Text_Normal_DrawStyle =  _GUI_WindowsDrawStyleList_Zui_Bat_Low[HWND_BAT_LOW_CHARGE_TEXT].pNormalStyle;
    #endif
  //  MApp_ZUI_ACTcoexistWin_SwitchGwin();
    printf(" MApp_ZUI_ACTcoexist_Delete 1 \n"); //test by gchen @ 20110714
    MApp_ZUI_ACTcoexist_Delete(); //change by gchen @ 20110714
    //bCreateOk=MApp_ZUI_ACTcoexist_Create(COWIN_ID_BAT_LOW, MUTE_GWIN_X, MUTE_GWIN_Y, MUTE_GWIN_W, MUTE_GWIN_H);

    bCreateOk=MApp_ZUI_ACTcoexist_Create(COWIN_ID_BAT_LOW, BAT_LOW_GWIN_X, BAT_LOW_GWIN_Y, BAT_LOW_GWIN_W, BAT_LOW_GWIN_H);
    if(bCreateOk==FALSE)
    {
        printf(" BatLowWarning_Create  fail\n"); 
        return;
    }
	
    
    Wdc.u8FbID = CoexistWin.u8FBID;
     
    u8MuteFBID = CoexistWin.u8FBID;
    Wdc.u8ConstantAlpha = 0xFF;

    t_GUI_WPT = g_GUI_WindowPositionList;
    g_GUI_WindowPositionList = _GUI_WindowPositionList_Zui_Bat_Low;
    #if 0
    MApp_ZUI_API_GetWindowInitialRect(HWND_MSG_ALERT_WINDOW,&Wrect);
    printf("\r\n HWND_MSG_ALERT_WINDOW Wrect x = %d, y = %d, w = %d, h = %d", Wrect.left, Wrect.top, Wrect.width, Wrect.height); //test by gchen @ 20110719
    _MApp_ZUI_API_DrawStyleList(&Wdc, &Wrect, _Zui_Volume_Bat_Low_Alert_Win_Normal_DrawStyle);
    MApp_ZUI_API_GetWindowInitialRect(HWND_MSG_ALERT_ICON,&Wrect);
    printf("\r\n HWND_MSG_ALERT_ICON Wrect x = %d, y = %d, w = %d, h = %d", Wrect.left, Wrect.top, Wrect.width, Wrect.height); //test by gchen @ 20110719
    _MApp_ZUI_API_DrawStyleList(&Wdc, &Wrect, _Zui_Volume_Bat_Low_Alert_Icon_Normal_DrawStyle);
    MApp_ZUI_API_GetWindowInitialRect(HWND_MSG_ALERT_STRING,&Wrect);
    printf("\r\n HWND_MSG_ALERT_STRING Wrect x = %d, y = %d, w = %d, h = %d", Wrect.left, Wrect.top, Wrect.width, Wrect.height); //test by gchen @ 20110719
    _MApp_ZUI_API_DrawStyleList(&Wdc, &Wrect, _Zui_Volume_Bat_Low_Alert_Text_Normal_DrawStyle);
    #else
    MApp_ZUI_API_GetWindowInitialRect(HWND_BAT_LOW_WARNING_WINDOW,&Wrect);
    printf("\r\n HWND_BAT_LOW_WARNING_WINDOW Wrect x = %d, y = %d, w = %d, h = %d", Wrect.left, Wrect.top, Wrect.width, Wrect.height); //test by gchen @ 20110719
    _MApp_ZUI_API_DrawStyleList(&Wdc, &Wrect, _Zui_Bat_Low_Warning_Window_Normal_DrawStyle);
    MApp_ZUI_API_GetWindowInitialRect(HWND_BAT_LOW_HINT_TEXT,&Wrect);
    printf("\r\n HWND_BAT_LOW_HINT_TEXT Wrect x = %d, y = %d, w = %d, h = %d", Wrect.left, Wrect.top, Wrect.width, Wrect.height); //test by gchen @ 20110719
    _MApp_ZUI_API_DrawStyleList(&Wdc, &Wrect, _Zui_Bat_Low_Hint_Text_Normal_DrawStyle);
    MApp_ZUI_API_GetWindowInitialRect(HWND_BAT_LOW_CHARGE_TEXT,&Wrect);
    printf("\r\n HWND_BAT_LOW_CHARGE_TEXT Wrect x = %d, y = %d, w = %d, h = %d", Wrect.left, Wrect.top, Wrect.width, Wrect.height); //test by gchen @ 20110719
    _MApp_ZUI_API_DrawStyleList(&Wdc, &Wrect, _Zui_Bat_Low_Charge_Text_Normal_DrawStyle);
    #endif
    g_GUI_WindowPositionList = t_GUI_WPT;

    //MApp_ZUI_ACTcoexistWin_RestoreGwin();
}

void MApp_UiMenu_BatLowWin_Show(void)
{
		printf("MApp_UiMenu_BatLowWin_Show \n"); 
	   if(//(MApp_ZUI_GetActiveOSD() == E_OSD_BAT_PERCENTAGE)||
	   	(MApp_ZUI_GetActiveOSD() == E_OSD_SCREEN_SAVER))
	   	   MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
	   	
        if(u8CoexistWinType != COWIN_ID_BAT_LOW)
        {
            printf("u8CoexistWinType != COWIN_ID_BAT_LOW \n"); 
            MApp_UiMenu_BatLowWin_Create(); 
        }

        MApp_ZUI_ACTcoexist_Enable(TRUE);
		bPowerLowFlag = TRUE;
}

void MApp_UiMenu_BatLowWin_Hide(void)
{
     U8 u8FBID=0XFF;

    if(u8CoexistWinType == COWIN_ID_BAT_LOW)
    {
        MApp_ZUI_ACTcoexist_Enable(FALSE);
        u8FBID=MApi_GOP_GWIN_GetFBfromGWIN(CoexistWin.u8GwinID);
        MApi_GOP_GWIN_DeleteFB(u8FBID);
        CoexistWin.u8FBID = 0xFF;
        u8CoexistWinType = COWIN_ID_NONE;
		bPowerLowFlag = FALSE;
    }
}

//============================================================================
// create countdown box
//============================================================================
//extern WINDOWPOSDATA _MP_TBLSEG _GUI_WindowPositionList_Zui_Message_Box[];
//extern WINDOWDRAWSTYLEDATA _MP_TBLSEG _GUI_WindowsDrawStyleList_Zui_Message_Box[];
/*
extern DRAWSTYLE _MP_TBLSEG _Zui_Msgbox_Bg_Pane_Normal_DrawStyle[];
extern DRAWSTYLE _MP_TBLSEG _Zui_Msgbox_Bg_Icon_Normal_DrawStyle[];
extern DRAWSTYLE _MP_TBLSEG _Zui_Msgbox_Text1_Normal_DrawStyle[];
*/
#define _Zui_Msgbox_Text2_Normal_DrawStyle _Zui_Msgbox_Text1_Normal_DrawStyle

void MApp_UiMenu_CountDownWin_Draw(void)
{
    GRAPHIC_DC Wdc = {0, 0, 0};
    RECT       Wrect = {0, 0, 0, 0};
    U8 u8DbFbId;
    GFX_Buffer_Format gefmt;
    MSAPI_OSDRegion CopyFB;
    MSAPI_OSDRegion PasteFB;
    WINDOWPOSDATA *t_GUI_WPT;

    DRAWSTYLE * _Zui_Msgbox_Bg_Top_Normal_DrawStyle =  _GUI_WindowsDrawStyleList_Zui_Message_Box[HWND_MSGBOX_COMMON_BG_TOP].pNormalStyle;
    DRAWSTYLE * _Zui_Msgbox_New_Bg_L_Normal_DrawStyle =  _GUI_WindowsDrawStyleList_Zui_Message_Box[HWND_MSGBOX_COMMON_NEW_BG_L].pNormalStyle;
    DRAWSTYLE * _Zui_Msgbox_New_Bg_C_Normal_DrawStyle =  _GUI_WindowsDrawStyleList_Zui_Message_Box[HWND_MSGBOX_COMMON_NEW_BG_C].pNormalStyle;
    DRAWSTYLE * _Zui_Msgbox_New_Bg_R_Normal_DrawStyle =  _GUI_WindowsDrawStyleList_Zui_Message_Box[HWND_MSGBOX_COMMON_NEW_BG_R].pNormalStyle;
    DRAWSTYLE * _Zui_Msgbox_Text1_Normal_DrawStyle =  _GUI_WindowsDrawStyleList_Zui_Message_Box[HWND_MSGBOX_COMMON_TEXT1].pNormalStyle;

    MApp_ZUI_ACTcoexistWin_SwitchGwin();

    u8DbFbId = MApi_GOP_GWIN_GetFreeFBID();
    if (u8DbFbId == 0xFF)
    {
        CW_DEBUG(printf("[MUTE]:Create u8DbFbId failed\n"));
        ABORT();
        return ;
    }

#if (MPLAYER_BITMAP_FORMAT == MPLAYER_I8)
    gefmt = GFX_FMT_I8;
#elif (MPLAYER_BITMAP_FORMAT == MPLAYER_RGB555)
    gefmt = GFX_FMT_ARGB1555;
#elif (MPLAYER_BITMAP_FORMAT == MPLAYER_ARGB1555)
        gefmt = GFX_FMT_ARGB1555;
#elif (MPLAYER_BITMAP_FORMAT == MPLAYER_RGB565)
    gefmt = GFX_FMT_RGB565;
#elif (MPLAYER_BITMAP_FORMAT == MPLAYER_ARGB4444)
    gefmt = GFX_FMT_ARGB4444;
#elif (MPLAYER_BITMAP_FORMAT == MPLAYER_ARGB8888)
    gefmt = GFX_FMT_ARGB8888;
#else
    #error "unsupported pixel format!"
#endif

    MApi_GOP_GWIN_CreateFB(u8DbFbId, 0, 0, MBOX_GWIN_W, MBOX_GWIN_H, gefmt);
    Wdc.u8FbID = u8DbFbId;//CoexistWin.u8FBID;
    Wdc.u8ConstantAlpha = 0xFF;

    t_GUI_WPT = g_GUI_WindowPositionList;
    g_GUI_WindowPositionList = _GUI_WindowPositionList_Zui_Message_Box;

    MApp_ZUI_API_GetWindowInitialRect(HWND_MSGBOX_COMMON_BG_TOP,&Wrect);
#if (UI_SKIN_SEL ==  UI_SKIN_1366X768X565)
    Wrect.top = 0;
    Wrect.left = 0;
#endif
    _MApp_ZUI_API_DrawStyleList(&Wdc, &Wrect, _Zui_Msgbox_Bg_Top_Normal_DrawStyle);
    MApp_ZUI_API_GetWindowInitialRect(HWND_MSGBOX_COMMON_NEW_BG_L,&Wrect);
#if (UI_SKIN_SEL ==  UI_SKIN_1366X768X565)
    Wrect.top = 49;
    Wrect.left = 0;
#endif
    _MApp_ZUI_API_DrawStyleList(&Wdc, &Wrect, _Zui_Msgbox_New_Bg_L_Normal_DrawStyle);
    MApp_ZUI_API_GetWindowInitialRect(HWND_MSGBOX_COMMON_NEW_BG_C,&Wrect);
#if (UI_SKIN_SEL ==  UI_SKIN_1366X768X565)
    Wrect.top = 49;
    Wrect.left = 6;
#endif
    _MApp_ZUI_API_DrawStyleList(&Wdc, &Wrect, _Zui_Msgbox_New_Bg_C_Normal_DrawStyle);
    MApp_ZUI_API_GetWindowInitialRect(HWND_MSGBOX_COMMON_NEW_BG_R,&Wrect);
#if (UI_SKIN_SEL ==  UI_SKIN_1366X768X565)
    Wrect.top = 49;
    Wrect.left = 330;
#endif
    _MApp_ZUI_API_DrawStyleList(&Wdc, &Wrect, _Zui_Msgbox_New_Bg_R_Normal_DrawStyle);
    //MApp_ZUI_API_GetWindowInitialRect(HWND_MSGBOX_BG_ICON,&Wrect);
    //_MApp_ZUI_API_DrawStyleList(&Wdc, &Wrect, _Zui_Msgbox_Bg_Icon_Normal_DrawStyle);
    MApp_ZUI_API_GetWindowInitialRect(HWND_MSGBOX_COMMON_TEXT1,&Wrect);
#if (UI_SKIN_SEL ==  UI_SKIN_1366X768X565)
    Wrect.top = 88;
    Wrect.left = 3;
#endif
    {
        DRAW_TEXT_OUT_DYNAMIC * dyna;
        U16 u16TextIndex = _Zui_Msgbox_Text1_Normal_DrawStyle[0].u16Index;
        if (u16TextIndex != 0xFFFF)
        {
            dyna = (DRAW_TEXT_OUT_DYNAMIC*)_ZUI_MALLOC(sizeof(DRAW_TEXT_OUT_DYNAMIC));
            if (dyna)
            {
                LPTSTR str = CHAR_BUFFER;
                _MApp_ZUI_API_ConvertTextComponentToDynamic(u16TextIndex, dyna);

                MApp_ZUI_API_GetU16String((U16)MApp_Sleep_DisplayCountDownTimer());

                str += MApp_ZUI_API_Strlen(str);
                *str = CHAR_SPACE;
                str++;
                MApp_ZUI_API_LoadString(en_str_SECOND_TO_POWER_OFF, str);

                dyna->pString = CHAR_BUFFER;

                _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, dyna, &Wdc, &Wrect);
                _ZUI_FREE(dyna);
            }
            else
            {
                __ASSERT(0);
            }
        }
    }

    MApp_ZUI_API_GetWindowInitialRect(HWND_MSGBOX_COMMON_TEXT2,&Wrect);
#if (UI_SKIN_SEL ==  UI_SKIN_1366X768X565)
    Wrect.top = 119;
    Wrect.left = 3;
#endif
    {
        DRAW_TEXT_OUT_DYNAMIC * dyna;
        U16 u16TextIndex = _Zui_Msgbox_Text2_Normal_DrawStyle[0].u16Index;
        if (u16TextIndex != 0xFFFF)
        {
           dyna = (DRAW_TEXT_OUT_DYNAMIC*)_ZUI_MALLOC(sizeof(DRAW_TEXT_OUT_DYNAMIC));
            if (dyna)
            {
                _MApp_ZUI_API_ConvertTextComponentToDynamic(u16TextIndex, dyna);
                MApp_ZUI_API_LoadString(en_str_Please_press_any_key_to_cancel, CHAR_BUFFER);
                dyna->pString = CHAR_BUFFER;
                _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, dyna, &Wdc, &Wrect);
                _ZUI_FREE(dyna);
            }
            else
            {
                __ASSERT(0);
            }
        }
    }

#if (ENABLE_UI_3D_PROCESS)
    if(MApp_ZUI_API_ConvertTo3DTwinModeOutput(Wdc.u8FbID, CoexistWin.u8FBID, MBOX_GWIN_W, MBOX_GWIN_H) == FALSE)
#endif
    {
        PasteFB.fbID = CoexistWin.u8FBID;
        PasteFB.x = 0;
        PasteFB.y = 0;
        PasteFB.width = MBOX_GWIN_W;
        PasteFB.height = MBOX_GWIN_H;

        CopyFB.fbID = u8DbFbId;
        CopyFB.x = 0;
        CopyFB.y = 0;
        CopyFB.width = MBOX_GWIN_W;
        CopyFB.height = MBOX_GWIN_H;
        msAPI_OSD_SetClipWindow(0, 0,MBOX_GWIN_W, MBOX_GWIN_H);
        msAPI_OSD_CopyRegion(&CopyFB, &PasteFB);
    }

    MApi_GOP_GWIN_DeleteFB(u8DbFbId);

    g_GUI_WindowPositionList = t_GUI_WPT;
    MApp_ZUI_ACTcoexistWin_RestoreGwin();
}

#if(ENABLE_OSD_SUBTITLE_EXCLUSIVE == ENABLE)
BOOLEAN MApp_UiMenu_GetCoexistWin_State(void)
{
    if((u8CoexistWinType == COWIN_ID_COUNT_DOWN_WIN) \
        ||(u8CoexistWinType == COWIN_ID_MUTE))
   {
      return FALSE;
   }
    else
   {
      return TRUE;
   }
}
#endif
void MApp_UiMenu_CountDownWin_Create(void)
{
#if(ENABLE_OSD_SUBTITLE_EXCLUSIVE == ENABLE)
    #if (ENABLE_SUBTITLE)
        if (IsDTVInUse())
        {
            if (( MApp_Subtitle_GetStatus() == STATE_SUBTITLE_DECODING)
            #if(ENABLE_TTX)
                ||(MApp_TTX_IsTeletextOn()&&stGenSetting.g_SysSetting.fEnableTTXSubTitle)
            #endif
                )
            {
                 MApp_Subtitle_SetShowStatus(FALSE);
            }
        }
    #endif
#endif
    MApp_ZUI_ACTcoexistWin_SwitchGwin();

    MApp_ZUI_ACTcoexist_Delete();
    MApp_ZUI_ACTcoexist_Create(COWIN_ID_COUNT_DOWN_WIN, MBOX_GWIN_X, MBOX_GWIN_Y, MBOX_GWIN_W, MBOX_GWIN_H);

    MApp_UiMenu_CountDownWin_Draw();

    MApp_ZUI_ACTcoexist_Enable(TRUE);

    MApp_ZUI_ACTcoexistWin_RestoreGwin();
}

void MApp_UiMenu_ShowCountDownWin(void)
{
    U8 u8TmpCurGOP;

    u8TmpCurGOP = MApi_GOP_GWIN_GetCurrentGOP();
    if (u8TmpCurGOP != OSD_GOP_ID) //GOP of OSD
    {
        MApi_GOP_GWIN_SwitchGOP(OSD_GOP_ID);
    }

    if(u8CoexistWinType != COWIN_ID_COUNT_DOWN_WIN)
    {
        MApp_UiMenu_CountDownWin_Create(); //prepare MUTE window, maybe can rewrite to reduce boot up time
        MApp_ZUI_ACTcoexist_Enable(TRUE);
    }
    else
    {
    }

    if (u8TmpCurGOP != OSD_GOP_ID) //GOP of OSD
    {
            MApi_GOP_GWIN_SwitchGOP(u8TmpCurGOP);
    }
#if ENABLE_TTX
    if(MApp_TTX_GetControlMode()==TTX_MODE_SUBTITLE)
    {
            MApp_TTX_BackToTTXMode();
    }
#endif
}

#if (ENABLE_CEC)
BOOLEAN MApp_UiMenu_IsCountDownWinShow(void)
{
    return (u8CoexistWinType == COWIN_ID_COUNT_DOWN_WIN);
}
#endif

#if (ENABLE_EASMONITOR)
U8 EAS_Display_Buffer[MAX_LENGTH_OF_ALERT_TEXT];
U16 DisplayLengthPonit  ;
static U32 u32MonitorEasDisplayTimer;
static void MApp_UiMenu_EASWin_Create(void)
{
    GRAPHIC_DC Wdc;
    RECT    Wrect;
    WINDOWPOSDATA *t_GUI_WPT;
    DRAWSTYLE * _Zui_Volume_Eas_Pane_Normal_DrawStyle =  _GUI_WindowsDrawStyleList_Zui_Audio_Volume[HWND_VOLUME_EAS_PANE].pNormalStyle;
    DRAWSTYLE * _Zui_Volume_Eas_Text_Normal_DrawStyle =  _GUI_WindowsDrawStyleList_Zui_Audio_Volume[HWND_VOLUME_EAS_TEXT].pNormalStyle;
    GOP_GwinInfo sGWININfo;

    memset(&Wdc, 0, sizeof(GRAPHIC_DC));
    DisplayLengthPonit = 0;
    MApp_ZUI_ACTcoexist_Delete();
    MApp_ZUI_ACTcoexist_Create(COWIN_ID_EAS, EAS_GWIN_X, EAS_GWIN_Y, EAS_GWIN_W, EAS_GWIN_H);

    Wdc.u8FbID = CoexistWin.u8FBID;
    u8MuteFBID = CoexistWin.u8FBID;
    Wdc.u8ConstantAlpha = 0xFF;

    t_GUI_WPT = g_GUI_WindowPositionList;
    g_GUI_WindowPositionList = _GUI_WindowPositionList_Zui_Audio_Volume;
    MApp_ZUI_API_GetWindowInitialRect(HWND_VOLUME_EAS_PANE,&Wrect);
    _MApp_ZUI_API_DrawStyleList(&Wdc, &Wrect, _Zui_Volume_Eas_Pane_Normal_DrawStyle);
    MApp_ZUI_API_GetWindowInitialRect(HWND_VOLUME_EAS_TEXT,&Wrect);
    _MApp_ZUI_API_DrawStyleList(&Wdc, &Wrect, _Zui_Volume_Eas_Text_Normal_DrawStyle);
    g_GUI_WindowPositionList = t_GUI_WPT;

    MApi_GOP_GWIN_GetWinInfo(CoexistWin.u8GwinID, &sGWININfo);
    sEASMirInfo.u32NonMirrorFBAdr = sGWININfo.u32DRAMRBlkStart;
    sEASMirInfo.u16NonMirrorHEnd = sGWININfo.u16DispHPixelEnd;
    sEASMirInfo.u16NonMirrorHStr = sGWININfo.u16DispHPixelStart;
    sEASMirInfo.u16NonMirrorVStr = sGWININfo.u16DispVPixelStart;
    sEASMirInfo.u16NonMirrorVEnd = sGWININfo.u16DispVPixelEnd;


}

void MApp_UiMenu_EASWin_Show(U8 *u8StrLang)
{
    GOP_GwinInfo sGWININfo;
    MApp_UiMenu_MuteWin_Hide();

     if(u8CoexistWinType != COWIN_ID_EAS)
     {
        MApp_UiMenu_EASWin_Create();

        MApi_GOP_GWIN_GetWinInfo(CoexistWin.u8GwinID, &sGWININfo);
        sGWININfo.u32DRAMRBlkStart = sEASMirInfo.u32NonMirrorFBAdr;
        sGWININfo.u16DispHPixelStart = sEASMirInfo.u16NonMirrorHStr;
        sGWININfo.u16DispHPixelEnd = sEASMirInfo.u16NonMirrorHEnd;
        sGWININfo.u16DispVPixelStart = sEASMirInfo.u16NonMirrorVStr;
        sGWININfo.u16DispVPixelEnd = sEASMirInfo.u16NonMirrorVEnd;
        MApi_GOP_GWIN_SetWinInfo(CoexistWin.u8GwinID, &sGWININfo);

        MApp_ZUI_ACTcoexist_Enable(TRUE);
        strcpy((char *)EAS_Display_Buffer,(char *)u8StrLang);
     }
}

void MApp_UiMenu_EASWin_Hide(void)
{
    U8 u8FBID=0xFF;

    if(u8CoexistWinType == COWIN_ID_EAS)
    {
        MApp_ZUI_ACTcoexist_Enable(FALSE);
        u8FBID=MApi_GOP_GWIN_GetFBfromGWIN(CoexistWin.u8GwinID);
        MApi_GOP_GWIN_DeleteFB(u8FBID);

        CoexistWin.u8FBID = 0xFF;
        u8CoexistWinType = COWIN_ID_NONE;
    }
}
#define EAS_DISPLAY_LENGTH  70
U8 MApp_UiMenu_EASWin_Update(void)
{
    GRAPHIC_DC Wdc;
    RECT    Wrect;
    U16 u16StrLang[EAS_DISPLAY_LENGTH+1]={0},u16StrLength,i=0;
    WINDOWPOSDATA *t_GUI_WPT;
    DRAW_TEXT_OUT_DYNAMIC dyna;
    DRAWSTYLE * _Zui_Volume_Eas_Pane_Normal_DrawStyle =  _GUI_WindowsDrawStyleList_Zui_Audio_Volume[HWND_VOLUME_EAS_PANE].pNormalStyle;

      memset(&Wdc, 0, sizeof(GRAPHIC_DC));
     if(u8CoexistWinType != COWIN_ID_EAS)
         return 0;
    if(msAPI_Timer_DiffTimeFromNow(u32MonitorEasDisplayTimer) < (U32)100)
        return 0;
    u32MonitorEasDisplayTimer = msAPI_Timer_GetTime0();
    Wdc.u8FbID = CoexistWin.u8FBID;
    u8MuteFBID = CoexistWin.u8FBID;
    Wdc.u8ConstantAlpha = 0xFF;

    t_GUI_WPT = g_GUI_WindowPositionList;
    if(1260 > 18*DisplayLengthPonit)
    {
        _GUI_WindowPositionList_Zui_Audio_Volume[HWND_VOLUME_EAS_TEXT].rect.left = 1310-18*DisplayLengthPonit;
        _GUI_WindowPositionList_Zui_Audio_Volume[HWND_VOLUME_EAS_TEXT].rect.width =50+18*DisplayLengthPonit;
    }
    g_GUI_WindowPositionList = _GUI_WindowPositionList_Zui_Audio_Volume;
    MApp_ZUI_API_GetWindowInitialRect(HWND_VOLUME_EAS_PANE,&Wrect);
    _MApp_ZUI_API_DrawStyleList(&Wdc, &Wrect, _Zui_Volume_Eas_Pane_Normal_DrawStyle);
    MApp_ZUI_API_GetWindowInitialRect(HWND_VOLUME_EAS_TEXT,&Wrect);
    g_GUI_WindowPositionList = t_GUI_WPT;

    u16StrLength=strlen((char *)EAS_Display_Buffer);
    if(++DisplayLengthPonit > EAS_DISPLAY_LENGTH+u16StrLength)
    {
        MApp_UiMenu_EASWin_Hide();
        DisplayLengthPonit = 0;
        return 0;
    }

    for(i=0;i<EAS_DISPLAY_LENGTH; i++)
    {
        u16StrLang[ i ] = EAS_Display_Buffer[i];
        if(DisplayLengthPonit < EAS_DISPLAY_LENGTH)
        {
            if(i>=DisplayLengthPonit)
                break;
            if(i>=u16StrLength )
                break;
            else
                u16StrLang[ i ] = EAS_Display_Buffer[i];
        }
        else
        {
            if((DisplayLengthPonit - EAS_DISPLAY_LENGTH + i ) >=  u16StrLength)
            {
                break;
            }
            else
                u16StrLang[ i ] = EAS_Display_Buffer[DisplayLengthPonit - EAS_DISPLAY_LENGTH + i];
        }
    }
    u16StrLang[ i ] =0;
    _MApp_ZUI_API_ConvertTextComponentToDynamic(_GUI_WindowsDrawStyleList_Zui_Audio_Volume[HWND_VOLUME_EAS_TEXT].pNormalStyle->u16Index, &dyna);
    dyna.pString = u16StrLang;
    dyna.eSystemFont = FONT_BIG;
        dyna.eTextAttrib = eTextAlignLeft;
    _MApp_ZUI_API_DrawDynamicComponent(CP_TEXT_OUT_DYNAMIC, &dyna, &Wdc, &Wrect);
    return 0;
}
#endif
#undef MAPP_ZUI_ACTAUDIOVOLUME_C
