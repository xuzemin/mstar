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

#define MAPP_NINE_LATTICE_C

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
#include <string.h>
#include "MsCommon.h"
#include "datatype.h"
#include "Panel.h"
#include "MApp_GlobalVar.h"
#include "msAPI_Timer.h"
#include "apiGOP.h"
#include "MApp_Scaler.h"
#include "MApp_NineLattice.h"

//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------
#define DBG(x)      x

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define NL_MAX_LATTICE_NUM      9
#define NL_WIDTH                (g_IPanel.Width())
#define NL_HEIGHT               (g_IPanel.Height())
#define NL_LATTICE_W            (NL_WIDTH/3)
#define NL_LATTICE_H            (NL_HEIGHT/3)

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
static EN_NL_STATE _enNLState = STATE_NL_IDLE;
static MS_S8 _s8LatticeIndex = -1;
static MS_U8 _u8WinId;
static MS_U8 _u8MainFBId, _u8DwinFBId;
static MS_U8 _u8GopId = E_GOP_APP;
static MS_BOOL _bNLInitialized = FALSE;

//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------

#if 0
static void _dumpdata(MS_U32 addr, MS_U32 size, MS_U32 pitch)
{
    MS_U32 i, j;
    MS_U8 *p;

    printf("dump>> Addr=%lx, size=%lx, pitch=%lx\n", addr, size, pitch);
    p = (MS_U8 *)_PA2VA(addr);
    for (j = 0; j < size/pitch; j++)
    {
        for (i = 0; i < pitch; i++)
        {
            printf("%02x", p[j*pitch + i]);
        }
        printf("\n");
    }
    printf("dump>> end\n");
}
#endif
static void _NineLatice_Init(void)
{
    GOP_GwinFBAttr stFBattr;
    E_GOP_API_Result eResult;
    MS_U8 u8GopBank;

    printf("%d, %d, %d\n", E_GOP_APP, E_GOP_OSD, E_GOP_CAP);

    u8GopBank = MApi_GOP_GWIN_GetCurrentGOP();

    eResult = MApi_GOP_GWIN_SwitchGOP(_u8GopId);

    eResult = MApi_GOP_GWIN_OutputLayerSwitch(E_GOP_OSD);

    _u8WinId = MApi_GOP_GWIN_CreateWin(NL_WIDTH, NL_HEIGHT, GFX_FMT_ARGB1555);
    DBG(printf("Main Gwin Id = %d\n", _u8WinId));
    _u8MainFBId = MApi_GOP_GWIN_GetFBfromGWIN(_u8WinId);
    DBG(printf("Main FB Id = %d\n", _u8MainFBId ));
    
    _u8DwinFBId = MApi_GOP_GWIN_GetFreeFBID();
    DBG(printf("Cap FB Id = %d\n", _u8DwinFBId ));
    eResult = MApi_GOP_GWIN_CreateFB(_u8DwinFBId, 0, 0, NL_LATTICE_W, NL_LATTICE_H, GFX_FMT_ARGB8888);

    //_u8OldFBId = MApi_GOP_GWIN_GetFBfromGWIN(_u8WinId);
    eResult = MApi_GOP_GWIN_MapFB2Win(_u8MainFBId, _u8WinId);
    eResult = MApi_GOP_GWIN_Switch2Gwin( _u8WinId );
    eResult = MApi_GOP_DWIN_SetSourceSel(DWIN_SRC_OP);
    eResult = MApi_GOP_GWIN_Enable(_u8WinId, FALSE);
    eResult = MApi_GOP_GWIN_SetBlending(_u8WinId, FALSE, 0x3F);//by-pixel

    eResult = MApi_GOP_GWIN_GetFBInfo(_u8MainFBId, &stFBattr);
    //printf("%x, %x, %x, %x, %x\n",stFBattr.width, stFBattr.height, stFBattr.dispWidth, stFBattr.dispHeight,stFBattr.size);
    MApi_GFX_ClearFrameBufferByWord(stFBattr.addr, stFBattr.size, 0x00000000);

    eResult = MApi_GOP_GWIN_GetFBInfo(_u8DwinFBId, &stFBattr);
    //printf("%x, %x, %x, %x, %x, %x\n",stFBattr.width, stFBattr.height, stFBattr.dispWidth, stFBattr.dispHeight,stFBattr.size,stFBattr.pitch);
    MApi_GFX_ClearFrameBufferByWord(stFBattr.addr, stFBattr.size, 0xffffffff);

    //MApi_GOP_GWIN_SetWinDispPosition(_u8WinId, 0, 10);
    

    eResult = MApi_GOP_GWIN_SwitchGOP(u8GopBank);

    _s8LatticeIndex = -1;
    _bNLInitialized = TRUE;
}

static void _NineLatice_Exit(void)
{
    //MApi_GOP_GWIN_SwitchGOP(_u8GopId);
    MApi_GOP_GWIN_Enable(_u8WinId, FALSE);

    MApi_GOP_GWIN_DeleteFB(_u8DwinFBId);
    MApi_GOP_GWIN_DeleteWin(_u8WinId);

    _bNLInitialized = FALSE;
}

static void _NineLattice_CaptureOneFrame(void)
{
    GOP_DwinProperty stProperty;
    GOP_GwinFBAttr stFBattr;
    E_GOP_API_Result eResult;
    U8 u8GopBank;
    
    u8GopBank = MApi_GOP_GWIN_GetCurrentGOP();

    eResult = MApi_GOP_DWIN_Init();
    eResult = MApi_GOP_GWIN_SwitchGOP(E_GOP_CAP);
    
    eResult = MApi_GOP_SetClkForCapture();
    eResult = MApi_GOP_DWIN_SelectSourceScanType(DWIN_SCAN_MODE_PROGRESSIVE);
    eResult = MApi_GOP_DWIN_SetDataFmt(DWIN_DATA_FMT_ARGB8888);
    eResult = MApi_GOP_DWIN_SetSourceSel(DWIN_SRC_OP);
    
    eResult = MApi_GOP_GWIN_GetFBInfo(_u8DwinFBId, &stFBattr);
    
    stProperty.u16x         = 0;
    stProperty.u16y         = 0;
    stProperty.u16w         = stFBattr.width;
    stProperty.u16h         = stFBattr.height;
    stProperty.u16fbw       = stFBattr.width;
    stProperty.u32fbaddr0   = stFBattr.addr;
    stProperty.u32fbaddr1   = stFBattr.addr + stFBattr.size;
    eResult = MApi_GOP_DWIN_SetWinProperty(&stProperty);
    eResult = MApi_GOP_DWIN_Enable(ENABLE);
    
    //capture one frame
    MApi_GOP_DWIN_SetAlphaValue(0x0f);
    msAPI_Timer_Delayms(10);
    eResult = MApi_GOP_DWIN_CaptureOneFrame();
    msAPI_Timer_Delayms(50);

    eResult = MApi_GOP_DWIN_Enable(FALSE);

    eResult = MApi_GOP_GWIN_SwitchGOP(u8GopBank);
}

static void _NineLattice_CopyOneLattice(void)
{
    GOP_GwinFBAttr stFBattr;
    E_GOP_API_Result eResult;
    
    //[blt]: set src buffer info
    GFX_BufferInfo gfxSrcBuf, gfxDstBuf;
    eResult = MApi_GOP_GWIN_GetFBInfo(_u8DwinFBId, &stFBattr);
    gfxSrcBuf.u32ColorFmt   = stFBattr.fbFmt&0xff;
    gfxSrcBuf.u32Addr       = stFBattr.addr;
    gfxSrcBuf.u32Pitch      = stFBattr.pitch;
    eResult = MApi_GFX_SetSrcBufferInfo(&gfxSrcBuf, 0);

    //[blt]: set dst buffer info
    eResult = MApi_GOP_GWIN_GetFBInfo(_u8MainFBId, &stFBattr);
    gfxDstBuf.u32ColorFmt   = stFBattr.fbFmt&0xff;
    gfxDstBuf.u32Addr       = stFBattr.addr;
    gfxDstBuf.u32Pitch      = stFBattr.pitch;
    eResult = MApi_GFX_SetDstBufferInfo(&gfxDstBuf, 0);

    //[blt]: set clip window
    GFX_Point v0,v1;
    v0.x = (_s8LatticeIndex%3)*NL_LATTICE_W;
    v0.y = (_s8LatticeIndex/3)*NL_LATTICE_H;
    v1.x = v0.x + NL_WIDTH;
    v1.y = v0.y + NL_HEIGHT;
    MApi_GFX_SetClip(&v0, &v1);

    //[blt]: do blt
    GFX_DrawRect gfxDrawRect;
    gfxDrawRect.srcblk.x        = 0;
    gfxDrawRect.srcblk.y        = 0;
    gfxDrawRect.srcblk.width    = NL_LATTICE_W;
    gfxDrawRect.srcblk.height   = NL_LATTICE_H;

    gfxDrawRect.dstblk.x        = (_s8LatticeIndex%3)*NL_LATTICE_W;
    gfxDrawRect.dstblk.y        = (_s8LatticeIndex/3)*NL_LATTICE_H;
    gfxDrawRect.dstblk.width    = NL_LATTICE_W;
    gfxDrawRect.dstblk.height   = NL_LATTICE_H;
    eResult = MApi_GFX_BitBlt(&gfxDrawRect, GFXDRAW_FLAG_DEFAULT);
}

static void _NineLattice_ActivateLattice(void)
{
    GOP_GwinFBAttr stFBattr;
    E_GOP_API_Result eResult;
    U8 u8GopBank;
    
    u8GopBank = MApi_GOP_GWIN_GetCurrentGOP();
    MApi_GOP_GWIN_SwitchGOP(_u8GopId);

    //[active lattice]: show video in active lattice
    GFX_BufferInfo gfxDstBuf;
    eResult = MApi_GOP_GWIN_GetFBInfo(_u8MainFBId, &stFBattr);
    gfxDstBuf.u32ColorFmt   = stFBattr.fbFmt&0xff;
    gfxDstBuf.u32Addr       = stFBattr.addr;
    gfxDstBuf.u32Pitch      = stFBattr.pitch;
    eResult = MApi_GFX_SetDstBufferInfo(&gfxDstBuf, 0);

    GFX_RectFillInfo gfxFillBlock;
    gfxFillBlock.fmt = stFBattr.fbFmt&0xff;
    gfxFillBlock.dstBlock.x = (_s8LatticeIndex%3)*NL_LATTICE_W;
    gfxFillBlock.dstBlock.y = (_s8LatticeIndex/3)*NL_LATTICE_H;
    gfxFillBlock.dstBlock.width = NL_LATTICE_W;
    gfxFillBlock.dstBlock.height= NL_LATTICE_H;
    gfxFillBlock.colorRange.color_s.a = 0;
    gfxFillBlock.colorRange.color_s.r = 0;
    gfxFillBlock.colorRange.color_s.g = 0;
    gfxFillBlock.colorRange.color_s.b = 0;
    gfxFillBlock.colorRange.color_e.a = 0;
    gfxFillBlock.colorRange.color_e.r = 0;
    gfxFillBlock.colorRange.color_e.g = 0;
    gfxFillBlock.colorRange.color_e.b = 0;
    gfxFillBlock.flag = GFXRECT_FLAG_COLOR_CONSTANT;
    MApi_GFX_RectFill(&gfxFillBlock);
    //
    eResult = MApi_GOP_GWIN_Set_STRETCHWIN(_u8GopId,E_GOP_DST_OP0, 0, 0, NL_WIDTH, NL_HEIGHT);
    eResult = MApi_GOP_GWIN_Set_HSCALE(FALSE, 1, 1);
    eResult = MApi_GOP_GWIN_Set_VSCALE(FALSE, 1, 1);
    
    eResult = MApi_GOP_GWIN_Enable(_u8WinId, TRUE);
    MApi_GOP_GWIN_SwitchGOP(u8GopBank);
}

MS_BOOL MApp_NineLattice_IsEnabled(void)
{
    return _bNLInitialized;
}

void MApp_NineLattice_Set(EN_NL_STATE eState)
{
    _enNLState = eState;
}

void MApp_NineLattice(void)
{
    E_GOP_API_Result eResult;
    U8 u8GopBank;
    
    switch(_enNLState)
    {
        case STATE_NL_INIT:
            DBG(printf("STATE_NINE_LATTICE_INIT\n"));
            _NineLatice_Init();
            _enNLState = STATE_NL_IDLE;
            break;

        case STATE_NL_SWITCH:
        {            
            DBG(printf("STATE_NINE_LATTICE_DISPLAY_OSD\n"));

            if (_s8LatticeIndex == -1)
            {
                _enNLState = STATE_NL_SCALER_SETWINDOW;
                break;
            }
            
            _NineLattice_CaptureOneFrame();
            _NineLattice_CopyOneLattice();

            u8GopBank = MApi_GOP_GWIN_GetCurrentGOP();
            MApi_GOP_GWIN_SwitchGOP(_u8GopId);
            eResult = MApi_GOP_GWIN_Set_STRETCHWIN(_u8GopId,E_GOP_DST_OP0, 0, 0, NL_WIDTH, NL_HEIGHT);
            eResult = MApi_GOP_GWIN_Set_HSCALE(FALSE, 1, 1);
            eResult = MApi_GOP_GWIN_Set_VSCALE(FALSE, 1, 1);
            
            eResult = MApi_GOP_GWIN_Enable(_u8WinId, TRUE);
            MApi_GOP_GWIN_SwitchGOP(u8GopBank);
            _enNLState = STATE_NL_SCALER_SETWINDOW;

        }break;

        case STATE_NL_SCALER_SETWINDOW:
        {
            MS_WINDOW_TYPE stWinDst;

            DBG(printf("STATE_NL_SCALER_SETWINDOW\n"));

            _s8LatticeIndex = (_s8LatticeIndex + 1)%NL_MAX_LATTICE_NUM;

            stWinDst.x      = (_s8LatticeIndex%3)*NL_LATTICE_W;
            stWinDst.y      = (_s8LatticeIndex/3)*NL_LATTICE_H;
            stWinDst.width  = NL_LATTICE_W;
            stWinDst.height = NL_LATTICE_H;
            msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
            MApp_Scaler_SetWindow(NULL, NULL, &stWinDst, stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
            msAPI_Scaler_SetBlueScreen(DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);

            _NineLattice_ActivateLattice();

            _enNLState = STATE_NL_IDLE;
        }break;

        case STATE_NL_EXIT:
            DBG(printf("STATE_NL_EXIT\n"));
            if (_bNLInitialized)
            {
                msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
                MApp_Scaler_SetWindow(NULL, NULL, NULL, stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
                msAPI_Scaler_SetBlueScreen(DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
                _NineLatice_Exit();
            }
            _enNLState = STATE_NL_IDLE;
            break;
        
        case STATE_NL_IDLE:
            //DBG(printf("STATE_NINE_LATTICE_IDLE\n"));
            break;
    }
}

