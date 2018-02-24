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
// (!¡±MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifdef MSOS_TYPE_LINUX
#include <string.h>
#else
#include "Utl.h"
#endif

#include "TT_API25.h"
#include "TT_GERenderTarget.h"
#include "TT_DriverTime.h"
#include "TT_GEGOPRenderDeviceDB.h"

#include "MsCommon.h"
#include "MsOS.h"

#include "datatype.h"
#include "MsTypes.h"
#include "apiGOP.h"
#include "apiGFX.h"
#include "mw_debug.h"
#include "debug.h"
////////////////////////////////////////////////////////////////////////////////////////////

#define TT_PALETTE_SIZE 256
#define TT_DSP_LAST_COLOR_INDEX TT_PALETTE_SIZE-1
#define TT_MAX_NUM_OF_RENDER_DEVICES 5

////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    GOP_PaletteEntry TTPaletteData[TT_PALETTE_SIZE];
} TTPalette;
typedef TTPalette* TTPaletteHandle;

typedef struct
{
    TT_BOOL   FlashON,
              DriverIsOpen;
    MS_U32    TTXGop;

    TTPaletteHandle        Palette;

    TT_U16 ColorBookInd;
    TT_U16 FlashColorIndex;
    TT_U16 ClutBeginIndex;
}TT_RenderState;

typedef struct
{
    TT_U8 fgColor;
    TT_U8 bgColor;
    TT_U8 flashMode;
} TT_FlashColor;

typedef struct
{
    int inc;
    TT_U16 indexStart;
    TT_U16 indexEnd;
}TT_FlashColorBook;

typedef struct
{
    TT_U16 indexStart;
}TT_ClutColorBook;

////////////////////////////////////////////////////////////////////////////////////////////

PRIVATE TT_RenderState _RenderState;
PRIVATE TTPalette _Palette;
PRIVATE TT_FlashColor _FlashColors[TT_PALETTE_SIZE];
PRIVATE TT_FlashColorBook _FlashColorBooks[2] =
{
     /*255 is not available*/
    {1, TT_DSP_NO_OF_COLORS, TT_DSP_LAST_COLOR_INDEX-TT_DSP_NO_OF_COLORS},
    {-1, TT_DSP_LAST_COLOR_INDEX-TT_DSP_NO_OF_COLORS, TT_DSP_NO_OF_COLORS}
};

PRIVATE TT_ClutColorBook _ClutColorBooks[2] =
{
    {0},
    {TT_DSP_LAST_COLOR_INDEX- TT_DSP_NO_OF_COLORS + 1}
};

PRIVATE GOP_PaletteEntry _PrimitiveColor[TT_DSP_NO_OF_COLORS] =
{
    {{ 0x00, 0x08, 0x08, 0x08 }},  /*0-> TT_COLOR_BLACK */
    {{ 0x00, 0xff, 0x00, 0x00 }},  /*1-> TT_COLOR_RED */
    {{ 0x00, 0x00, 0xff, 0x00 }},  /*2-> TT_COLOR_GREEN */
    {{ 0x00, 0xff, 0xff, 0x00 }},  /*3-> TT_COLOR_YELLOW */
    {{ 0x00, 0x00, 0x00, 0xff }},  /*4-> TT_COLOR_BLUE */
    {{ 0x00, 0xff, 0x00, 0xff }},  /*5-> TT_COLOR_MAGENTA */
    {{ 0x00, 0x00, 0xff, 0xff }},  /*6-> TT_COLOR_CYAN */
    {{ 0x00, 0xff, 0xff, 0xff }},  /*7-> TT_COLOR_WHITE */
    {{ 0x00, 0xff, 0x08, 0xff }},  /*8-> TT_COLOR_TRANSPARENT */
    {{ 0x00, 0x7f, 0x00, 0x00 }},  /*9-> TT_COLOR_TRANSPARENT */
    {{ 0x00, 0x00, 0x7f, 0x00 }},  /*A-> TT_COLOR_HALF_RED */
    {{ 0x00, 0x7f, 0x7f, 0x00 }},  /*B-> TT_COLOR_HALF_GREEN */
    {{ 0x00, 0x00, 0x00, 0x7f }},  /*C-> TT_COLOR_HALF_BLUE */
    {{ 0x00, 0x7f, 0x00, 0x7f }},  /*D-> TT_COLOR_HALF_MAGENTA */
    {{ 0x00, 0x00, 0x7f, 0x7f }},  /*E-> TT_COLOR_HALF_CYAN */
    {{ 0x00, 0x7f, 0x7f, 0x7f }},  /*F-> TT_COLOR_GREY */
};

PRIVATE TT_IRenderDevice const* _RenderDevice = 0;

TT_U8 TT_GERenderTargetGetColorIndex(TT_U8 color);
static void TT_GERenderTarget_EnterDrawingPhease(void);
static void TT_GERenderTarget_LeaveDrawingPhease(void);
////////////////////////////////////////////////////////////////////////////////////////////
PRIVATE void
_FillClut(void)
{
    TT_U16 i, j;

    for(j = 0; j < sizeof(_ClutColorBooks)/sizeof(_ClutColorBooks[0]); ++j)
    {
        TT_U16 colorIndex = _ClutColorBooks[j].indexStart;

        for ( i=0; i < TT_DSP_NO_OF_COLORS; i++ )
            _RenderState.Palette->TTPaletteData[colorIndex +i] = _PrimitiveColor[i];
    }
}

static GOP_PaletteEntry
_GetFlashColor(
  TT_U8   aColorIndex,
  TT_U8   aColorFlashMode,
  TT_BOOL  aFlashOn,
  TT_BOOL aBackgroundTransparent)
{
#define  FLASH_BG_COLOR_ENTRY( index ) \
    _RenderState.Palette->TTPaletteData[TT_GERenderTargetGetColorIndex(_FlashColors[index].bgColor)]

#define  FLASH_FG_COLOR_ENTRY( index ) \
    _RenderState.Palette->TTPaletteData[TT_GERenderTargetGetColorIndex(_FlashColors[index].fgColor)]

#define  FLASH_FG_COLOR_ENTRY_NEXT_CLUT( index ) \
    _RenderState.Palette->TTPaletteData[TT_GERenderTargetGetColorIndex(_FlashColors[index].fgColor)+8]

      #define GET_RRAN_COLOR() \
        _RenderState.Palette->TTPaletteData[TT_GERenderTargetGetColorIndex(TT_COLOR_TRANSPARENT)]


    switch(aColorFlashMode)
    {
    case 0: /* steady */
        break;
    case 1: /* normal flash to background color */
        if(!aFlashOn)
            {
                if(aBackgroundTransparent)
                    return GET_RRAN_COLOR();
                else
            return FLASH_BG_COLOR_ENTRY( aColorIndex );
            }
        else
            return FLASH_FG_COLOR_ENTRY( aColorIndex );
    case 2: /* invert phase of flash to background color */
        if(!aFlashOn)
            return FLASH_FG_COLOR_ENTRY( aColorIndex );
        else
            {
                if(aBackgroundTransparent)
                    return GET_RRAN_COLOR();
                else
            return FLASH_BG_COLOR_ENTRY( aColorIndex );
            }
    case 3: /* flash to the corresponding color in an adjacent */
        if(!aFlashOn)
            return FLASH_FG_COLOR_ENTRY_NEXT_CLUT( aColorIndex );
        else
            return FLASH_FG_COLOR_ENTRY( aColorIndex );
    }

    return FLASH_FG_COLOR_ENTRY( aColorIndex );
}

void _SubmitPalette(void)
{
    MS_U32 oldGop = MApi_GOP_GWIN_GetCurrentGOP();
    GOP_CAP_PAL_TYPE Pal;
	_RenderState.Palette = &_Palette;
    MS_U8 u8PalGOP = 0;

    MApi_GOP_GetChipCaps(E_GOP_CAP_PALETTE,(MS_U32 *)&Pal,sizeof(GOP_CAP_PAL_TYPE));
    if(Pal.GOP_PalTbl[0] != E_GOP_CAP_PAL_SIZE_NONE)
        u8PalGOP = 0;
    else
        u8PalGOP = 1;

    MApi_GOP_GWIN_SwitchGOP(u8PalGOP);
    MApi_GOP_GWIN_SetForceWrite(TRUE);
    MApi_GOP_GWIN_SetPaletteOpt(_RenderState.Palette->TTPaletteData,
                                0,
                                TT_DSP_LAST_COLOR_INDEX,
                                E_GOP_PAL_ARGB8888);
    if(u8PalGOP != _RenderState.TTXGop)
        MApi_GOP_GWIN_SetPaletteRead (E_GOP1_PAL_GOP_RIU);
    else
        MApi_GOP_GWIN_SetPaletteRead (E_GOP_PAL_GOP_RIU);
    MApi_GOP_GWIN_SetForceWrite(FALSE);
    MApi_GOP_GWIN_SwitchGOP(oldGop);
}

////////////////////////////////////////////////////////////////////////////////////////////

static TT_BOOL
TT_GERenderTargetCreate( MS_U32 param )
{
    _RenderDevice = &TT_GEGOPRenderDeviceDB;

    _RenderDevice->Create();

    memset(&_RenderState, 0, sizeof(_RenderState));
    _RenderState.TTXGop = param;

    return true;
}

static void
TT_GERenderTargetOpen(void)
{
    if ( _RenderState.DriverIsOpen )
        return;

    _RenderState.Palette = &_Palette;

    _RenderState.ColorBookInd = 0;
    _RenderState.FlashColorIndex = _FlashColorBooks[_RenderState.ColorBookInd].indexStart;
    _RenderState.ClutBeginIndex = _ClutColorBooks[_RenderState.ColorBookInd].indexStart;

    _FillClut();
    _RenderDevice->EnterDrawingPhease();
    _SubmitPalette();
    _RenderDevice->LeaveDrawingPhease();

    /* initialize the fashcolors */
    memset(_FlashColors,
           0,
           sizeof(_FlashColors));

    _RenderState.DriverIsOpen = TRUE;
}

static void
TT_GERenderTargetClose(void)
{
    _RenderState.DriverIsOpen = FALSE;

}


TT_U8
TT_GERenderTargetGetColorIndex(TT_U8 color)
{
    return _RenderState.ClutBeginIndex + color;
}

static void
TT_GERenderTargetClearFullScreen(TT_BOOL bTransparent)
{
    TT_U8 colorIndex;

    if(FALSE == _RenderState.DriverIsOpen)
        return;

    colorIndex = TT_COLOR_BLACK;
    if (bTransparent)
        colorIndex = TT_COLOR_TRANSPARENT;

    _RenderDevice->ClearScreen(TT_GERenderTargetGetColorIndex(colorIndex));

}

/***********************************************************************
 * FUNCTION: TT_GERenderTargetDrawRow
 *
 * DESCRIPTION:
 *   Draw one row using the bitmap based display.
 *
 * PARAMETERS:
 *   pParams - Pointer to the driver parameters.
 *
 * RETURN:
 ***********************************************************************/
static void
TT_GERenderTargetDrawRow(TT_U8* dataBuffer,
                         TT_BOOL hasSidePanel,
                         TT_U16 rowNum,
                         TT_U16 screenColor,
                         TT_U16 rowColor,
                         TT_U16 bufferRowWidth,
                         TT_U16 bufferRowHeight,
                         TT_BOOL isUpdateImmediately)
{
    if (!_RenderState.DriverIsOpen)
        return;

    rowColor = rowColor;

    _RenderDevice->DrawRow( (TT_U8*)_VA2PA((TT_U32)dataBuffer),
                            TT_GERenderTargetGetColorIndex(screenColor),
                            hasSidePanel,
                            rowNum,
                            bufferRowWidth,                                              bufferRowHeight,
                            isUpdateImmediately);
}

static void
TT_GERenderTarget_CompleteRendering(TT_U32 screenColor)
{
    if (!_RenderState.DriverIsOpen)
        return;

    _RenderDevice->CompleteRendering(
        TT_GERenderTargetGetColorIndex(screenColor));
}

static TT_U8
TT_GERenderTargetSelectFlashColor(
  TT_U8   aFgColor,
  TT_U8   aBgColor,
  TT_U8   aFlashMode )
{
    // put your code here
    TT_U16 i, j;
    TT_U16 start = _FlashColorBooks[_RenderState.ColorBookInd].indexStart;
    TT_U16 end = _FlashColorBooks[_RenderState.ColorBookInd].indexEnd;
    int inc = _FlashColorBooks[_RenderState.ColorBookInd].inc;

    // search for the flash color in current flash array
    for (i=start; i != _RenderState.FlashColorIndex; i = i + inc)
    {
        if ((aFgColor == _FlashColors[i].fgColor) &&
            (aBgColor == _FlashColors[i].bgColor) &&
            (aFlashMode == _FlashColors[i].flashMode))
        {
            return (TT_U8)i;
        }
    }

    // if the color is not in the array, add it do the array
    {
        TT_U8 retValue;

        j = _RenderState.FlashColorIndex;
        _FlashColors[j].fgColor = aFgColor;
        _FlashColors[j].bgColor = aBgColor;
        _FlashColors[j].flashMode = aFlashMode;

        retValue = (TT_U8)(_RenderState.FlashColorIndex);

        //if no more entry left, sacrifice the last one
        if (_RenderState.FlashColorIndex != end)
            _RenderState.FlashColorIndex += inc;

        return retValue;
    }
}

static void
TT_GERenderTargetFlushClut( TT_BOOL aBackgroundTransparent )
{
    GOP_PaletteEntry *color;
    TT_U8 colorFlashMode, colorFlashPhase;
    TT_U16 flashIndexStart, flashIndexEnd;
    TT_U16 colorIndex;
    int flashIndexInc;

    if (!_RenderState.DriverIsOpen)
        return;

    //no flash characters found in the display page
    if(_RenderState.FlashColorIndex == _FlashColorBooks[_RenderState.ColorBookInd].indexStart)
    {
        return;
    }

    /* set global CLUT */
    color = _RenderState.Palette->TTPaletteData;
    /* increase color to flash colors */

    flashIndexStart = _FlashColorBooks[_RenderState.ColorBookInd].indexStart;
    flashIndexEnd = _RenderState.FlashColorIndex;
    flashIndexInc = _FlashColorBooks[_RenderState.ColorBookInd].inc;

    for ( colorIndex = flashIndexStart;
          colorIndex != flashIndexEnd;
          colorIndex+=flashIndexInc)
    {
        colorFlashMode = (TT_U8)(_FlashColors[colorIndex].flashMode & 0x03);
        colorFlashPhase = (TT_U8)((_FlashColors[colorIndex].flashMode >> 2) & 0x03);

        switch(colorFlashPhase)
        {
          case 0: // slow rate (1Hz)
            if(_RenderState.FlashON < 3)
          color[colorIndex] = _GetFlashColor(colorIndex, colorFlashMode, TRUE, aBackgroundTransparent);
            else if(_RenderState.FlashON > 3)
          color[colorIndex] = _GetFlashColor(colorIndex, colorFlashMode, FALSE, aBackgroundTransparent);
            break;

          case 1: // fast rate (2Hz), phase 1
            if((_RenderState.FlashON == 0) || (_RenderState.FlashON == 3))
          color[colorIndex] = _GetFlashColor(colorIndex, colorFlashMode, TRUE, aBackgroundTransparent);
            else
          color[colorIndex] = _GetFlashColor(colorIndex, colorFlashMode, FALSE, aBackgroundTransparent);
            break;
          case 2: // fast rate (2Hz), phase 2
            if((_RenderState.FlashON == 1) || (_RenderState.FlashON == 4))
          color[colorIndex] = _GetFlashColor(colorIndex, colorFlashMode, TRUE, aBackgroundTransparent);
            else
          color[colorIndex] = _GetFlashColor(colorIndex, colorFlashMode, FALSE, aBackgroundTransparent);
            break;
          case 3: // fast rate (2Hz), phase 3
            if((_RenderState.FlashON == 2) || (_RenderState.FlashON == 5))
          color[colorIndex] = _GetFlashColor(colorIndex, colorFlashMode, TRUE, aBackgroundTransparent);
            else
          color[colorIndex] = _GetFlashColor(colorIndex, colorFlashMode, FALSE, aBackgroundTransparent);
            break;
        }
    }

    _SubmitPalette();

    _RenderState.FlashON = (TT_BOOL)((_RenderState.FlashON + 1) % 6);

}

static void
TT_GERenderTargetAfterPageProcessed( void )
{
    if (!_RenderState.DriverIsOpen)
        return;

    _RenderState.ColorBookInd = !_RenderState.ColorBookInd;
    _RenderState.FlashColorIndex = _FlashColorBooks[_RenderState.ColorBookInd].indexStart;
    _RenderState.ClutBeginIndex = _ClutColorBooks[_RenderState.ColorBookInd].indexStart;

    _FillClut();

}

static void
TT_GERenderSetPaletteColor(
  TT_U8   aIndex,
  TT_U8   aRed,
  TT_U8   aGreen,
  TT_U8   aBlue )
{
    if (!_RenderState.DriverIsOpen)
        return;

    _RenderState.Palette->TTPaletteData[TT_GERenderTargetGetColorIndex(aIndex)].RGB.u8R = aRed;
    _RenderState.Palette->TTPaletteData[TT_GERenderTargetGetColorIndex(aIndex)].RGB.u8G = aGreen;
    _RenderState.Palette->TTPaletteData[TT_GERenderTargetGetColorIndex(aIndex)].RGB.u8B = aBlue;

    /* update palette if all colors are set */
    if ( aIndex == 31 )
    {
        _SubmitPalette();
    }
}


static
void TT_GERenderTarget_EnterDrawingPhease(void)
{
    if(_RenderState.DriverIsOpen && _RenderState.FlashColorIndex == _FlashColorBooks[_RenderState.ColorBookInd].indexStart)
    {
        _SubmitPalette();
    }
    _RenderDevice->EnterDrawingPhease();
}

static
void TT_GERenderTarget_LeaveDrawingPhease(void)
{
    _RenderDevice->LeaveDrawingPhease();
}

static
TT_BOOL TT_GERenderTarget_DoesNeedFlushClut(void)
{
    //for auto-test
    {
#define AUTOTEST_OUT_MSG_PERIOD 3000
        static TT_U32 lastTime = 0;
        if(lastTime == 0) lastTime = TT_DriverTimeGetms();

        if(TT_DriverTimeGetms() - lastTime > AUTOTEST_OUT_MSG_PERIOD)
        {
            lastTime = TT_DriverTimeGetms();
            MS_DEBUG_MSG(MWprintf(MWDBG_TELETEXT, MWDBGLVL_TEST, printf("121_TTX_Alive\n")));
        }
    }


    if(_RenderState.FlashColorIndex ==
       _FlashColorBooks[_RenderState.ColorBookInd].indexStart)
    {
        return FALSE;
    }

    return TRUE;
}


void TT_GERenderTarget_Attach(TT_U32 ttxMarginH,
                              TT_U32 ttxMarginV,
                              TT_U32 displayX,
                              TT_U32 displayY,
                              TT_U32 displayWidth,
                              TT_U32 displayHeight,
                              TT_BOOL isTransparent)
{
    if(_RenderDevice!=0)
        _RenderDevice->Open(_RenderState.TTXGop,
                            ttxMarginH,
                            ttxMarginV,
                            displayX,
                            displayY,
                            displayWidth,
                            displayHeight,
                            isTransparent);

}

void TT_GERenderTarget_GetInternalWindowSize(TT_U32* width,
                                                   TT_U32* height,
                                                   TT_U32 ttxMarginH,
                                                    TT_U32 ttxMarginV,
                                                    TT_U32 displayWidth,
                                                    TT_U32 displayHeight)
{
    height = height;

    if(width != 0)
    {
        ttxMarginV = ttxMarginV;
        displayHeight = displayHeight;
        *width = TT_GEGOPRenderDevice_GetInternalWindowWidth(ttxMarginH,
                                                                    displayWidth);
    }
}

void TT_GERenderTarget_Detach(void)
{
    if(_RenderDevice != 0)
        _RenderDevice->Close();
}

void TT_GERenderTarget_DrawRow2(TT_DRIVER_PARAMS* pParams,
                                TT_U16  screenColor,
                                TT_BOOL hasSidePanel,
                                TT_BOOL isUpdateImmediately)
{
    if(_RenderDevice!=0)
    {
       /// patch for mantis 1372731
       _RenderDevice->DrawRow2(pParams,
                               screenColor,
                               hasSidePanel,
                               isUpdateImmediately);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
const TT_IRenderTarget TT_GERenderTarget =
{
  .Create = TT_GERenderTargetCreate,
  .Open = TT_GERenderTargetOpen,
  .Close = TT_GERenderTargetClose,
  .ClearFullScreen = TT_GERenderTargetClearFullScreen,
  .DrawRow = TT_GERenderTargetDrawRow,
  .DrawRow2 = TT_GERenderTarget_DrawRow2,
  .CompleteRendering = TT_GERenderTarget_CompleteRendering,
  .SelectFlashColor = TT_GERenderTargetSelectFlashColor,
  .FlushClut = TT_GERenderTargetFlushClut,
  .AfterPageProcessed = TT_GERenderTargetAfterPageProcessed,
  .SetPaletteColor = TT_GERenderSetPaletteColor,
  .GetColorIndex = TT_GERenderTargetGetColorIndex,
  .EnterTTXDrawingPhase = TT_GERenderTarget_EnterDrawingPhease,
  .LeaveTTXDrawingPhase = TT_GERenderTarget_LeaveDrawingPhease,
  .DoesNeedFlushClut = TT_GERenderTarget_DoesNeedFlushClut,
};

