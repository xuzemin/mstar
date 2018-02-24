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
#endif
#include "datatype.h"
#include "MsTypes.h"
#include "apiGOP.h"
#include "apiGFX.h"
#include "apiPNL.h"
#include "MApp_GlobalVar.h"
#include "Utl.h"
#include "TT_GEGOPRenderDeviceDB.h"
#include "TT_API25.h"
#include "sysinfo.h"

#define TTX_TRAN_COLOR_KEY 0x7C3F
#define TTX_TRAN_COLOR  0xFF08FF
#define TTX_BG_COLOR    0
#define TTX_INVALID_WIN_ID  0xff

#define TTX_ARABIC_CHARACTER_TRANSFORM_DISABLE 0
#define TTX_ARABIC_CHARACTER_TRANSFORM_ENABLE 1

#define TTX_ARABIC_CHARACTER_TRANSFORM TTX_ARABIC_CHARACTER_TRANSFORM_DISABLE

#define TTX_ASSERT(P) {if(!(P)) \
                          {\
                            while(1)\
                            { \
                            printf("assert faile: \"%s\" in %s,%s(),%d\n", #P, __FILE__, __FUNCTION__,__LINE__);\
                            }\
                           }\
                          }

///////////////////////////////////////////////////////////////////////////////

typedef struct
{
  MS_U32 orgGOP;
  MS_U32 orgGWinID;
  MS_U16 orgClipWindowLeftX;
  MS_U16 orgClipWindowLeftY;
  MS_U16 orgClipWindowRightX;
  MS_U16 orgClipWindowRightY;
}TT_OrgDeviceState;

typedef struct
{
  MS_U8  fbID;
  MS_U32 ttxFBAddress;
  MS_U32 bufferWidth;
  MS_U32 bufferHeight;
  GFX_Buffer_Format colorFormat;
}TT_RenderFrameBuffer;

typedef struct
{
  MS_BOOL isOpened;
  MS_U32 ttxGOP;

  TT_U8 ttxWinID;
  TT_RenderFrameBuffer FrameBuffers[2];
  TT_U32 activeFrameBuffer; //The current background drawing buffer

  MS_U32 ttxWidth;
  MS_U32 ttxHeight;
  MS_U32 ttxMarginH;
  MS_U32 ttxMarginV;
  MS_U32 displayX;
  MS_U32 displayY;
  MS_U32 displayWidth;
  MS_U32 displayHeight;
  TT_OrgDeviceState orgDeviceState;

  MS_U32 gwinBufferWidth;
  MS_U32 gwinBufferHeight;
  MS_BOOL doesNeedScaleDown;
  TT_RenderFrameBuffer scaledownFrameBuffer;
}TT_RenderDeviceState;


///////////////////////////////////////////////////////////////////////////////

static void _Switch2TTXGop(void);
static void _CreateTTXGWin(TT_BOOL isTransparent);
static void TT_GEGOPRenderDeviceDB_Close(void);
static void _DelTTXGWin(void);
static void _Switch2OSDGop(void);
static void _FillRectangle (TT_RenderFrameBuffer* pFrameBuffer,
                                TT_U8 ColorIndex,
                                TT_U16 x,
                                TT_U16 y,
                                TT_U16 width,
                                TT_U16 height);
static void _ShowFrameBuffer(void);
static void _FillMargin(TT_RenderFrameBuffer*, TT_U8 colorIndex);
static void TT_GEGOPRenderDeviceDB_ClearScreen(TT_U8 colorIndex);
static void _FrameBufferPositionChanaged(MS_U32 u32EventID, void* reserved0);
static void TT_GEGOPRenderDeviceDB_CompleteRendering(TT_U8 screenColor);
static void _SetGEDest(TT_RenderFrameBuffer* pFrameBuffer);

///////////////////////////////////////////////////////////////////////////////

static TT_RenderDeviceState _deviceState;

///////////////////////////////////////////////////////////////////////////////

extern void  msAPI_TTX_SetWinID(MS_U8 which, MS_U8 u8TTXWinId1);
extern void msAPI_TTX_SetWinFBAddress(MS_U8 WinID, MS_U32 WinAddr);

static
void TT_GEGOPRenderDeviceDB_Create(void)
{
  memset(&_deviceState,
         0,
         sizeof(_deviceState));

  _deviceState.ttxWinID = TTX_INVALID_WIN_ID;

}

TT_U32 TT_GEGOPRenderDevice_GetInternalWindowWidth(TT_U32 ttxMarginH,
                                                          TT_U32 displayWidth)
{
    U32 result;
    U32 ttxWidth =
        TT_EngineObj.DisplayParams.GetColNum()*
        TT_EngineObj.GetRenderSystem()->GetFontCharsMan()->GetFontCharWidth() +
        2*ttxMarginH;

    ttxWidth = ((ttxWidth - 1)/16+1)*16;

    if((ttxWidth > displayWidth))
    {
        result = ((displayWidth - 1)/16+1)*16;
    }
    else
    {
        result = ttxWidth;
    }

    return result;
}

static
void TT_GEGOPRenderDeviceDB_Open(TT_U32 ttxGOP,
                                 TT_U32 ttxMarginH,
                                 TT_U32 ttxMarginV,
                                 TT_U32 displayX,
                                 TT_U32 displayY,
                                 TT_U32 displayWidth,
                                 TT_U32 displayHeight,
                                 TT_BOOL isTransparent)
{
    U32 ttxWidth =
        TT_EngineObj.DisplayParams.GetColNum()*
        TT_EngineObj.GetRenderSystem()->GetFontCharsMan()->GetFontCharWidth() +
        2*ttxMarginH;

    U32 ttxHeight =
        TT_EngineObj.DisplayParams.GetRowNum()*
        TT_EngineObj.GetRenderSystem()->GetFontCharsMan()->GetFontCharHeight() +
        2*ttxMarginV;

    ttxWidth = ((ttxWidth - 1)/16+1)*16;

    ttxMarginH = (ttxWidth - TT_EngineObj.DisplayParams.GetColNum()*
                                TT_EngineObj.GetRenderSystem()->GetFontCharsMan()->GetFontCharWidth())/2;

    if(_deviceState.isOpened)
        return;

#ifdef GOP_GWIN_TTX_ADR
//In this case, GOP sticks rendering FB in MIU1
#if(GOP_GWIN_TTX_MEMORY_TYPE&MIU1)
    MApi_GOP_MIUSel(ttxGOP, E_GOP_SEL_MIU1);
#else
    MApi_GOP_MIUSel(ttxGOP, E_GOP_SEL_MIU0);
#endif
#endif

    _deviceState.ttxGOP = ttxGOP;
    _deviceState.ttxWidth = ttxWidth;
    _deviceState.ttxHeight = ttxHeight;
    _deviceState.ttxMarginH = ttxMarginH;
    _deviceState.ttxMarginV = ttxMarginV;
    _deviceState.displayWidth = displayWidth;
    _deviceState.displayHeight = displayHeight;
    _deviceState.displayX = displayX;
    _deviceState.displayY = displayY;
    _deviceState.activeFrameBuffer = 0;

    if((_deviceState.ttxWidth > displayWidth) ||
        (_deviceState.ttxHeight > displayHeight))
    {
        _deviceState.doesNeedScaleDown = TRUE;
        _deviceState.gwinBufferWidth = ((displayWidth - 1)/16+1)*16;

        _deviceState.gwinBufferHeight =
            (_deviceState.ttxHeight > displayHeight) ? displayHeight : _deviceState.ttxHeight;
    }
    else
    {
        _deviceState.doesNeedScaleDown = FALSE;
        _deviceState.gwinBufferWidth = ttxWidth;
        _deviceState.gwinBufferHeight = ttxHeight;
    }


    _CreateTTXGWin(isTransparent);

    _deviceState.isOpened = TRUE;

}

static
void TT_GEGOPRenderDeviceDB_Close(void)
{
  if(_deviceState.isOpened)
  {
    _DelTTXGWin();
    _Switch2OSDGop();
    _deviceState.isOpened = FALSE;
  }
}

static
void _DrawTo(TT_U32 fbAddress,
             TT_U8* buffer,
             TT_U32 pixelX,
             TT_U32 pixelY,
             TT_U32 pixelWidth,
             TT_U32 pixelHeight,
             TT_U32 bufferWidth)
{
  GFX_BufferInfo src_info, dst_info;
  GFX_DrawRect rect;
  TT_U32 GEdrawflag = 0;

  MsOS_FlushMemory();

  pixelX = pixelX + _deviceState.ttxMarginH;
  pixelY = pixelY + _deviceState.ttxMarginV;

#if 0
  if(pixelWidth != bufferWidth)
  {
    pixelX += 8 * TT_FONT_CHAR_WIDTH;
  }
#endif

  src_info.u32Addr = (U32)buffer;
  src_info.u32ColorFmt = GFX_FMT_I8;
  src_info.u32Width = pixelWidth;
  src_info.u32Height = pixelHeight;
  src_info.u32Pitch = bufferWidth;
  MApi_GFX_SetSrcBufferInfo(&src_info, 0);

  dst_info.u32Addr = fbAddress;
  dst_info.u32ColorFmt = GFX_FMT_I8;
  dst_info.u32Width = _deviceState.ttxWidth;
  dst_info.u32Height = pixelHeight;
  dst_info.u32Pitch = _deviceState.ttxWidth;           //unit: byte, I8:1 bytes
  MApi_GFX_SetDstBufferInfo(&dst_info, 0);


  rect.srcblk.x = 0;
  rect.srcblk.y = 0;
  rect.srcblk.width = pixelWidth;
  rect.srcblk.height = pixelHeight;

  rect.dstblk.x = pixelX;
  rect.dstblk.y = pixelY;
  rect.dstblk.width = pixelWidth;
  rect.dstblk.height = pixelHeight;


  MApi_GFX_BitBlt(&rect, GEdrawflag);
  MApi_GFX_FlushQueue();
}

static
void TT_GEGOPRenderDeviceDB_DrawRow( TT_U8* pixels,
                                    TT_U16 screenColor,
                                    TT_BOOL hasSidePanel,
                                    TT_U32 rowNum,
                                    TT_U32 bufferRowWidth,
                                    TT_U32 bufferRowHeight,
                                    TT_BOOL isUpdateImmediately)
{
    static TT_BOOL _latestHasSidePanel = FALSE;
    TT_U32 pixelRowWidth = bufferRowWidth;

    screenColor = screenColor;
    if(!_deviceState.isOpened)
        return;

    if(_latestHasSidePanel && !hasSidePanel)
    {
        TT_GEGOPRenderDeviceDB_ClearScreen(screenColor);
    }
    _latestHasSidePanel = hasSidePanel;

    if (!hasSidePanel)
    {
        pixelRowWidth = bufferRowWidth -
            TT_DSP_NOF_SIDEPANEL_COLUMNS * TT_EngineObj.GetRenderSystem()->GetFontCharsMan()->GetFontCharWidth();
    }


    if(isUpdateImmediately)
    {
        _DrawTo(_deviceState.FrameBuffers[!_deviceState.activeFrameBuffer].ttxFBAddress,
          pixels,
          0,
          rowNum*bufferRowHeight,
          pixelRowWidth,
          bufferRowHeight,
          bufferRowWidth);
    }

    _DrawTo(_deviceState.FrameBuffers[_deviceState.activeFrameBuffer].ttxFBAddress,
            pixels,
            0,
            rowNum*bufferRowHeight,
            pixelRowWidth,
            bufferRowHeight,
            bufferRowWidth);
  }

static
void TT_GEGOPRenderDeviceDB_DrawRow2(TT_DRIVER_PARAMS* pParams,
                                     TT_U16 screenColor,
                                     TT_BOOL hasSidePanel,
                                     TT_BOOL isUpdateImmediately)
{
    static TT_BOOL _latestHasSidePanel = FALSE;
    TT_RenderFrameBuffer* pFrameBuffer;
    TT_U32 startColumn, endColumn, i, y, tmp, offsetX;
    GFX_BufferInfo src_info, dst_info;
    GFX_DrawRect rect;
    TT_U32 GEdrawflag = GFXDRAW_FLAG_SCALE;
    GFX_Point clipv0, clipv1;
    TT_U32  BPP,
            glyphWidth,
            glyphHeight,
            glyphPitch;
    TT_Charset_Font    fontIDTmp = TT_Charset_Font_G0_Latin;
    TT_U8    glyphIndexTmp = 0;

    const TT_IBitmapFontCharsMan* fontman=
        (const TT_IBitmapFontCharsMan*)
        TT_EngineObj.GetRenderSystem()->GetFontCharsMan();

    if(!_deviceState.isOpened)
        return;

    BPP = fontman->GetGlyphBPP();
    glyphWidth = fontman->GetFontCharWidth();
    glyphHeight = fontman->GetFontCharHeight();
    glyphPitch = fontman->GetPitch();

    MsOS_FlushMemory();

    clipv0.x = 0;
    clipv0.y = 0;
    clipv1.x = _deviceState.ttxWidth;
    clipv1.y = _deviceState.ttxHeight;

    MApi_GFX_SetClip(&clipv0, &clipv1);

    if(BPP == 1)
        BPP = GFX_FMT_I1;
    else if(BPP == 2)
        BPP = GFX_FMT_I2;
    else
        BPP = GFX_FMT_I4;

    y = pParams[0].Row * glyphHeight;

    if(_deviceState.doesNeedScaleDown)
    {
        pFrameBuffer = &_deviceState.scaledownFrameBuffer;
    }
    else
    {
        if(isUpdateImmediately)
            pFrameBuffer = &_deviceState.FrameBuffers[!_deviceState.activeFrameBuffer];
        else
            pFrameBuffer = &_deviceState.FrameBuffers[_deviceState.activeFrameBuffer];
    }

    if(_latestHasSidePanel && !hasSidePanel)
    {
        TT_GEGOPRenderDeviceDB_ClearScreen(screenColor);

    }
    _latestHasSidePanel = hasSidePanel;

    if(hasSidePanel)
    {
        startColumn = 0;
        endColumn = TT_DSP_NOF_COLUMNS;

        offsetX = 0;
    }
    else
    {
        startColumn = 0;
        endColumn = TT_DSP_NOF_L1_COLUMNS;

        if(TT_EngineObj.Status.DoesSupportSidePanel())
            offsetX = TT_DSP_NOF_SIDEPANEL_COLUMNS/2 * glyphWidth;
        else
            offsetX = 0;
    }

    for(i = startColumn; i < endColumn; ++i)
    {
        if(pParams[i].ignore)
            continue;

#if (TTX_ARABIC_CHARACTER_TRANSFORM == TTX_ARABIC_CHARACTER_TRANSFORM_ENABLE)
        if (pParams[i].refDisplayInfo & 0x000C)
        {
            switch ((pParams[i].refDisplayInfo >> 2) & 0x0003)
            {
                case 1:
                    if ((pParams[i].fontID == TT_Charset_Font_G0_Arabic) || (pParams[i].fontID == TT_Charset_Font_G2_Arabic))
                        fontIDTmp = TT_Charset_Font_G0_Arabic;
                    else
                        fontIDTmp = TT_Charset_Font_G0_Farsi;
                    break;
                case 2:
                    if ((pParams[i].fontID == TT_Charset_Font_G0_Arabic) || (pParams[i].fontID == TT_Charset_Font_G2_Arabic))
                        fontIDTmp = TT_Charset_Font_G2_Arabic;
                    else
                        fontIDTmp = TT_Charset_Font_G2_Farsi;
                    break;
                case 3:
                    fontIDTmp = TT_Charset_Font_Arabic_Extention;
                    break;
            }
            glyphIndexTmp = 0xE000 | ((pParams[i].refDisplayInfo >> 4) & 0x0FFF);
        }
        else
#endif // (TTX_ARABIC_CHARACTER_TRANSFORM == TTX_ARABIC_CHARACTER_TRANSFORM_ENABLE)
        {
            fontIDTmp = pParams[i].fontID;
            glyphIndexTmp = pParams[i].glyphIndex;
        }

        src_info.u32Addr = (U32)fontman->GetGlyph(fontIDTmp,
                                                  glyphIndexTmp,
                                                  i==0 || pParams[i].fontID!=pParams[i-1].fontID? -1 : pParams[i-1].glyphIndex,
                                                  i==endColumn-1 || pParams[i].fontID!=pParams[i+1].fontID ? -1 : pParams[i+1].glyphIndex);

        src_info.u32ColorFmt = (GFX_Buffer_Format)BPP;
        src_info.u32Width = glyphWidth;
        src_info.u32Height = glyphHeight;
        src_info.u32Pitch = glyphPitch;
        MApi_GFX_SetSrcBufferInfo(&src_info, 0);

        dst_info.u32Addr = pFrameBuffer->ttxFBAddress;
        dst_info.u32ColorFmt = pFrameBuffer->colorFormat;
        dst_info.u32Width = pFrameBuffer->bufferWidth;
        dst_info.u32Height = pFrameBuffer->bufferHeight;
        dst_info.u32Pitch = pFrameBuffer->bufferWidth;           //unit: byte, I8:1 bytes
        MApi_GFX_SetDstBufferInfo(&dst_info, 0);

        //foreground
        tmp = pParams[i].FgColour;
        MApi_GFX_SetIntensity(1,
                              GFX_FMT_I8,
                              &tmp);
        //background
        tmp = pParams[i].BgColour;
        MApi_GFX_SetIntensity(0,
                              GFX_FMT_I8,
                              &tmp);

        rect.srcblk.x = 0;
        rect.srcblk.y = 0;
        rect.srcblk.width = glyphWidth;
        rect.srcblk.height = glyphHeight;

        rect.dstblk.x = _deviceState.ttxMarginH + glyphWidth*i + offsetX;
        rect.dstblk.y = _deviceState.ttxMarginV + y;
        rect.dstblk.width = pParams[i].desWidth;
        rect.dstblk.height = pParams[i].desHeight;

        MApi_GFX_BitBlt(&rect, GEdrawflag);
    }
    if(isUpdateImmediately && _deviceState.doesNeedScaleDown)
        TT_GEGOPRenderDeviceDB_CompleteRendering(screenColor);

    MApi_GFX_FlushQueue();
}


static
void _CopyFrameBuffer(TT_RenderFrameBuffer* pToFrameBuffer,
                         TT_RenderFrameBuffer* pFromFrameBuffer)
{
    GFX_BufferInfo src_info, dst_info;
    GFX_DrawRect rect;
    TT_U32 GEdrawflag = GFXDRAW_FLAG_SCALE;

    MsOS_FlushMemory();

    src_info.u32Addr = pFromFrameBuffer->ttxFBAddress;
    src_info.u32ColorFmt = pFromFrameBuffer->colorFormat;
    src_info.u32Width = pFromFrameBuffer->bufferWidth;
    src_info.u32Height = pFromFrameBuffer->bufferHeight;
    src_info.u32Pitch = pFromFrameBuffer->bufferWidth;
    MApi_GFX_SetSrcBufferInfo(&src_info, 0);

    dst_info.u32Addr = pToFrameBuffer->ttxFBAddress;
    dst_info.u32ColorFmt = pToFrameBuffer->colorFormat;
    dst_info.u32Width = pToFrameBuffer->bufferWidth;
    dst_info.u32Height = pToFrameBuffer->bufferHeight;
    dst_info.u32Pitch = pToFrameBuffer->bufferWidth;           //unit: byte, I8:1 bytes
    MApi_GFX_SetDstBufferInfo(&dst_info, 0);


    rect.srcblk.x = 0;
    rect.srcblk.y = 0;
    rect.srcblk.width = pFromFrameBuffer->bufferWidth;
    rect.srcblk.height = pFromFrameBuffer->bufferHeight;

    rect.dstblk.x = 0;
    rect.dstblk.y = 0;
    rect.dstblk.width = pToFrameBuffer->bufferWidth;
    rect.dstblk.height = pToFrameBuffer->bufferHeight;

    MApi_GFX_BitBlt(&rect, GEdrawflag);
    MApi_GFX_FlushQueue();

}

static
void TT_GEGOPRenderDeviceDB_CompleteRendering(TT_U8 screenColor)
{
    if(!_deviceState.isOpened)
      return;

    //Freeze
    MApi_GOP_GWIN_UpdateRegOnce(TRUE);

    if(!_deviceState.doesNeedScaleDown)
    {
        _FillMargin(&_deviceState.FrameBuffers[_deviceState.activeFrameBuffer],
                      screenColor);
        _ShowFrameBuffer();
        _CopyFrameBuffer(&_deviceState.FrameBuffers[_deviceState.activeFrameBuffer],
                           &_deviceState.FrameBuffers[!_deviceState.activeFrameBuffer]);
    }
    else
    {
        _FillMargin(&_deviceState.scaledownFrameBuffer,
                      screenColor);

        _CopyFrameBuffer(&_deviceState.FrameBuffers[_deviceState.activeFrameBuffer],
                           &_deviceState.scaledownFrameBuffer);

        _ShowFrameBuffer();
    }

    //throw
    MApi_GOP_GWIN_UpdateRegOnce(FALSE);

    MApi_GOP_GWIN_Enable(_deviceState.ttxWinID,
                         TRUE);
}

static
void _FillMargin(TT_RenderFrameBuffer* pFrameBuffer, TT_U8 colorIndex)
{
    if(_deviceState.ttxMarginH == 0 &&
      _deviceState.ttxMarginV == 0)
        return;

    if(!_deviceState.isOpened)
       return;

  //top
    _FillRectangle(pFrameBuffer,
                     colorIndex,
                 0,
                 0,
                     pFrameBuffer->bufferWidth,
                 _deviceState.ttxMarginV);

  //bottom
    _FillRectangle(pFrameBuffer,
                    colorIndex,
                 0,
                    pFrameBuffer->bufferHeight - _deviceState.ttxMarginV,
                    pFrameBuffer->bufferWidth,
                 _deviceState.ttxMarginV);

  //left
    _FillRectangle(pFrameBuffer,
                     colorIndex,
                 0,
                 0,
                 _deviceState.ttxMarginH,
                     pFrameBuffer->bufferHeight);

  //right
    _FillRectangle(pFrameBuffer,
                     colorIndex,
                     pFrameBuffer->bufferWidth - _deviceState.ttxMarginH,
                 0,
                 _deviceState.ttxMarginH,
                     pFrameBuffer->bufferHeight);

}


static
void TT_GEGOPRenderDeviceDB_ClearScreen(TT_U8 colorIndex)
{
    if(!_deviceState.isOpened)
        return;

    if(!_deviceState.doesNeedScaleDown)
    {
        _FillRectangle (&_deviceState.FrameBuffers[!_deviceState.activeFrameBuffer],
                          colorIndex,
                  0,
                  0,
                          _deviceState.FrameBuffers[!_deviceState.activeFrameBuffer].bufferWidth,
                          _deviceState.FrameBuffers[!_deviceState.activeFrameBuffer].bufferHeight);
    }
    else
    {
        _FillRectangle (&_deviceState.scaledownFrameBuffer,
                          colorIndex,
                          0,
                          0,
                          _deviceState.scaledownFrameBuffer.bufferWidth,
                          _deviceState.scaledownFrameBuffer.bufferHeight);
    }


    _FillRectangle (&_deviceState.FrameBuffers[ _deviceState.activeFrameBuffer],
                      colorIndex,
                      0,
                      0,
                      _deviceState.FrameBuffers[ _deviceState.activeFrameBuffer].bufferWidth,
                      _deviceState.FrameBuffers[ _deviceState.activeFrameBuffer].bufferHeight);
}

static
void TT_GEGOPRenderDeviceDB_EnterDrawingPhease(void)
{
  if(!_deviceState.isOpened)
    return;

  _Switch2TTXGop();
}

static
void TT_GEGOPRenderDeviceDB_LeaveDrawingPhease(void)
{
  if(!_deviceState.isOpened)
    return;

  _Switch2OSDGop();
}

const TT_IRenderDevice TT_GEGOPRenderDeviceDB =
{
  .Create = TT_GEGOPRenderDeviceDB_Create,
  .Open = TT_GEGOPRenderDeviceDB_Open,
  .Close = TT_GEGOPRenderDeviceDB_Close,
  .DrawRow = TT_GEGOPRenderDeviceDB_DrawRow,
  .DrawRow2 = TT_GEGOPRenderDeviceDB_DrawRow2,
  .CompleteRendering = TT_GEGOPRenderDeviceDB_CompleteRendering,
  .ClearScreen = TT_GEGOPRenderDeviceDB_ClearScreen,
  .EnterDrawingPhease = TT_GEGOPRenderDeviceDB_EnterDrawingPhease,
  .LeaveDrawingPhease = TT_GEGOPRenderDeviceDB_LeaveDrawingPhease
};

///////////////////////////////////////////////////////////////////////////////

static
void _Switch2TTXGop(void)
{
  //memorize the original(OSD) state
  _deviceState.orgDeviceState.orgGOP = MApi_GOP_GWIN_GetCurrentGOP();
  _deviceState.orgDeviceState.orgGWinID = MApi_GOP_GWIN_GetCurrentWinId();
  msAPI_OSD_GetClipWindow(&_deviceState.orgDeviceState.orgClipWindowLeftX,
                          &_deviceState.orgDeviceState.orgClipWindowLeftY,
                          &_deviceState.orgDeviceState.orgClipWindowRightX,
                          &_deviceState.orgDeviceState.orgClipWindowRightY);

  MApi_GOP_GWIN_UpdateRegOnce(TRUE);

  MApi_GOP_GWIN_SwitchGOP(_deviceState.ttxGOP );

  if(TTX_INVALID_WIN_ID != _deviceState.ttxWinID)
  {
	if(MApi_GOP_GWIN_IsGwinExist(_deviceState.orgDeviceState.orgGWinID))
	{
	    MApi_GOP_GWIN_Switch2Gwin(_deviceState.ttxWinID);
	}
    msAPI_OSD_SetClipWindow(0,
                            0,
                            _deviceState.ttxWidth,
                            _deviceState.ttxHeight);

    msAPI_GE_SetNearestMode(TRUE);

    MApi_GFX_EnableAlphaBlending(FALSE);
  }
  MApi_GOP_GWIN_UpdateRegOnce(FALSE);
}

static
void _Switch2OSDGop(void)
{
  MApi_GOP_GWIN_UpdateRegOnce(TRUE);
  MApi_GOP_GWIN_SwitchGOP(_deviceState.orgDeviceState.orgGOP);
  if(MApi_GOP_GWIN_IsGwinExist(_deviceState.orgDeviceState.orgGWinID))
  {
	  MApi_GOP_GWIN_Switch2Gwin(_deviceState.orgDeviceState.orgGWinID);
  }
  msAPI_OSD_SetClipWindow(_deviceState.orgDeviceState.orgClipWindowLeftX,
                          _deviceState.orgDeviceState.orgClipWindowLeftY,
                          _deviceState.orgDeviceState.orgClipWindowRightX,
                          _deviceState.orgDeviceState.orgClipWindowRightY);
  MApi_GOP_GWIN_UpdateRegOnce(FALSE);
}

static
void _ShowFrameBuffer(void)
{
	MApi_GOP_GWIN_MapFB2Win(_deviceState.FrameBuffers[_deviceState.activeFrameBuffer].fbID,
	                      _deviceState.ttxWinID);
	if(MApi_GOP_GWIN_IsGwinExist(_deviceState.ttxWinID))
	{
		MApi_GOP_GWIN_Switch2Gwin(_deviceState.ttxWinID);
	}
	if(!_deviceState.doesNeedScaleDown)
	{
		_deviceState.activeFrameBuffer = !_deviceState.activeFrameBuffer;
		MApi_GOP_GWIN_Switch2FB(_deviceState.FrameBuffers[_deviceState.activeFrameBuffer].fbID);
	}
}

static
void _InitFrameBuffer(TT_RenderFrameBuffer* pFrameBuffer,
                      TT_BOOL isTransparent)
{
  GFX_BufferInfo srcbuf_bak, dstbuf_bak, dstbuf;

  MApi_GOP_GWIN_Switch2FB(pFrameBuffer->fbID);

  clrBtn1.x = 0;
  clrBtn1.y = 0;
  clrBtn1.width =  pFrameBuffer->bufferWidth;
  clrBtn1.height =  pFrameBuffer->bufferHeight;
  if(isTransparent)
    clrBtn1.b_clr = TTX_TRAN_COLOR;
  else
    clrBtn1.b_clr = TTX_BG_COLOR;

  clrBtn1.u8Gradient = CONSTANT_COLOR;
  clrBtn1.fHighLight = FALSE;

  MApi_GFX_GetBufferInfo(&srcbuf_bak, &dstbuf_bak);
  memcpy(&dstbuf, &dstbuf_bak, sizeof(GFX_BufferInfo));
  dstbuf.u32ColorFmt = GFX_FMT_ARGB1555;
  // for resolve legacy 1555 => ARGB_DST problem.
  MApi_GFX_SetDstBufferInfo(&dstbuf, 0);

  msAPI_OSD_DrawBlock(&clrBtn1);

  MApi_GFX_SetDstBufferInfo(&dstbuf_bak,
                            0);
}

static
void _CreateTTXGWin(TT_BOOL isTransparent)
{
  GFX_Buffer_Format gwin_fmt = GFX_FMT_I8;

  _Switch2TTXGop();

  msAPI_GE_SetNearestMode(TRUE);
  MApi_GOP_GWIN_OutputLayerSwitch(E_GOP_OSD);
  MApi_GOP_GWIN_SetTransClr(GOPTRANSCLR_FMT0,
                            TTX_TRAN_COLOR_KEY);
  MApi_GOP_GWIN_EnableTransClr(GOPTRANSCLR_FMT0,
                               TRUE);

  // initialize GE alpha value to non-zero
  MApi_GFX_SetAlpha(true,
                    COEF_ONE,
                    ABL_FROM_CONST,
                    0xff);
  MApi_GFX_SetAlpha(false,
                    COEF_ONE,
                    ABL_FROM_CONST,
                    0xff);

  MApi_GFX_EnableAlphaBlending(FALSE);

  MApi_GOP_GWIN_SetGOPDst(_deviceState.ttxGOP,
                          E_GOP_DST_OP0);

  //stretch
  MApi_GOP_GWIN_Set_STRETCHWIN(_deviceState.ttxGOP,
                                    E_GOP_DST_OP0,
                                    _deviceState.displayX & 0xFFFC,
                                    _deviceState.displayY,
                                    _deviceState.gwinBufferWidth,
                                    _deviceState.gwinBufferHeight);


  MApi_GOP_GWIN_Set_HSCALE(TRUE,
                              _deviceState.gwinBufferWidth,
				           _deviceState.displayWidth) ;

#if 1

  MApi_GOP_GWIN_Set_VSCALE(TRUE,
                              _deviceState.gwinBufferHeight,
                           _deviceState.displayHeight) ;

#endif

  MApi_GOP_GWIN_Set_HStretchMode(E_GOP_HSTRCH_DUPLICATE);
  MApi_GOP_GWIN_Set_VStretchMode(E_GOP_VSTRCH_DUPLICATE);



  if(TTX_INVALID_WIN_ID == _deviceState.ttxWinID)
  {
    //create GWin
    _deviceState.ttxWinID = MApi_GOP_GWIN_GetFreeWinID();

    _deviceState.FrameBuffers[0].fbID = MApi_GOP_GWIN_GetFreeFBID();
    _deviceState.FrameBuffers[0].bufferWidth = _deviceState.gwinBufferWidth;
    _deviceState.FrameBuffers[0].bufferHeight = _deviceState.gwinBufferHeight;
    _deviceState.FrameBuffers[0].colorFormat = gwin_fmt;
#ifdef GOP_GWIN_TTX_ADR
    _deviceState.FrameBuffers[0].ttxFBAddress = GOP_GWIN_TTX_ADR | MIU_INTERVAL;
    MApi_GOP_GWIN_CreateFBbyStaticAddr(_deviceState.FrameBuffers[0].fbID,
                                       0,
                                       0,
                                       _deviceState.FrameBuffers[0].bufferWidth,
                                       _deviceState.FrameBuffers[0].bufferHeight,
                                       _deviceState.FrameBuffers[0].colorFormat,
                                       _deviceState.FrameBuffers[0].ttxFBAddress);
#else
    MApi_GOP_GWIN_CreateFB(_deviceState.FrameBuffers[0].fbID,
                           0,
                           0,
                           _deviceState.FrameBuffers[0].bufferWidth,
                           _deviceState.FrameBuffers[0].bufferHeight,
                           _deviceState.FrameBuffers[0].colorFormat);

    MApi_GOP_GWIN_GetFBAddr(_deviceState.FrameBuffers[0].fbID,
                            &_deviceState.FrameBuffers[0].ttxFBAddress);
#endif
    _InitFrameBuffer(&_deviceState.FrameBuffers[0],
                       isTransparent);

    if(!_deviceState.doesNeedScaleDown)
    {
       _deviceState.FrameBuffers[1].fbID = MApi_GOP_GWIN_GetFreeFBID();
       _deviceState.FrameBuffers[1].bufferWidth = _deviceState.gwinBufferWidth;
       _deviceState.FrameBuffers[1].bufferHeight = _deviceState.gwinBufferHeight;
       _deviceState.FrameBuffers[1].colorFormat = gwin_fmt;
#ifdef GOP_GWIN_TTX_ADR

    _deviceState.FrameBuffers[1].ttxFBAddress =
        (GOP_GWIN_TTX_ADR + GOP_GWIN_TTX_LEN/2) | MIU_INTERVAL;


    MApi_GOP_GWIN_CreateFBbyStaticAddr(_deviceState.FrameBuffers[1].fbID,
                                       0,
                                       0,
                                       _deviceState.ttxWidth,
                                       _deviceState.ttxHeight,
                                       gwin_fmt,
                                       _deviceState.FrameBuffers[1].ttxFBAddress);
#else
    MApi_GOP_GWIN_CreateFB(_deviceState.FrameBuffers[1].fbID,
                           0,
                           0,
                               _deviceState.FrameBuffers[1].bufferWidth,
                               _deviceState.FrameBuffers[1].bufferHeight,
                               _deviceState.FrameBuffers[1].colorFormat);
    MApi_GOP_GWIN_GetFBAddr(_deviceState.FrameBuffers[1].fbID,
                            &_deviceState.FrameBuffers[1].ttxFBAddress);
#endif
    _InitFrameBuffer(&_deviceState.FrameBuffers[1],
                           isTransparent);
  }
    else
    {
        _deviceState.scaledownFrameBuffer.fbID = MApi_GOP_GWIN_GetFreeFBID();
        _deviceState.scaledownFrameBuffer.bufferWidth = _deviceState.ttxWidth;
        _deviceState.scaledownFrameBuffer.bufferHeight = _deviceState.ttxHeight;
        _deviceState.scaledownFrameBuffer.colorFormat = gwin_fmt;
#ifdef GOP_GWIN_TTX_ADR
        _deviceState.scaledownFrameBuffer.ttxFBAddress =
        (GOP_GWIN_TTX_ADR + GOP_GWIN_TTX_LEN/2) | MIU_INTERVAL;


    MApi_GOP_GWIN_CreateFBbyStaticAddr(_deviceState.scaledownFrameBuffer.fbID,
                                       0,
                                       0,
                                       _deviceState.scaledownFrameBuffer.bufferWidth,
                                       _deviceState.scaledownFrameBuffer.bufferHeight,
                                       _deviceState.scaledownFrameBuffer.colorFormat,
                                       _deviceState.scaledownFrameBuffer.ttxFBAddress);
#else
        MApi_GOP_GWIN_CreateFB(_deviceState.scaledownFrameBuffer.fbID,
                               0,
                               0,
                               _deviceState.scaledownFrameBuffer.bufferWidth,
                               _deviceState.scaledownFrameBuffer.bufferHeight,
                               _deviceState.scaledownFrameBuffer.colorFormat);
        MApi_GOP_GWIN_GetFBAddr(_deviceState.scaledownFrameBuffer.fbID,
                                &_deviceState.scaledownFrameBuffer.ttxFBAddress);
#endif
        _InitFrameBuffer(&_deviceState.scaledownFrameBuffer,
                           isTransparent);
    }
  }

  MApi_GOP_GWIN_UpdateRegOnce(TRUE);
  if(MApi_GOP_GWIN_IsGwinExist(_deviceState.ttxWinID))
  {
	  MApi_GOP_GWIN_SetWinPosition( _deviceState.ttxWinID,
	                                _deviceState.displayX & 0xFFFC,
	                                _deviceState.displayY );
  }
  //cancel alpha blending
  MApi_GOP_GWIN_SetBlending(_deviceState.ttxWinID,
                            FALSE,
                            63);
  if(MApi_GOP_GWIN_IsGwinExist(_deviceState.ttxWinID))
  {
	  MApi_GOP_GWIN_Switch2Gwin(_deviceState.ttxWinID);
  }

  msAPI_OSD_SetClipWindow(0,
                          0,
                          _deviceState.ttxWidth,
                          _deviceState.ttxHeight);


  MApi_GOP_GWIN_Switch2FB(_deviceState.FrameBuffers[_deviceState.activeFrameBuffer].fbID);
  MApi_GOP_GWIN_MapFB2Win(_deviceState.FrameBuffers[_deviceState.activeFrameBuffer].fbID,
                          _deviceState.ttxWinID);
  MApi_GOP_GWIN_UpdateRegOnce(FALSE);

  _Switch2OSDGop();

  MApi_GOP_RegisterEventNotify(_FrameBufferPositionChanaged);
}

static
void _DelTTXGWin(void)
{
  MApi_GOP_GWIN_Enable(_deviceState.ttxWinID,
                       FALSE);

  MApi_GOP_GWIN_DeleteWin(_deviceState.ttxWinID);
  _deviceState.ttxWinID = TTX_INVALID_WIN_ID;

  MApi_GOP_GWIN_DeleteFB(_deviceState.FrameBuffers[0].fbID);

  if(!_deviceState.doesNeedScaleDown)
  MApi_GOP_GWIN_DeleteFB(_deviceState.FrameBuffers[1].fbID);
  else
        MApi_GOP_GWIN_DeleteFB(_deviceState.scaledownFrameBuffer.fbID);

  MApi_GOP_GWIN_SwitchGOP(_deviceState.ttxGOP);
  MApi_GOP_GWIN_Set_HSCALE(FALSE,
                           _deviceState.ttxWidth,
                           _deviceState.ttxWidth) ;
  MApi_GOP_GWIN_Set_VSCALE(FALSE,
                           _deviceState.ttxHeight,
                           _deviceState.ttxHeight) ;
  MApi_GOP_Initialize_StretchWindow(_deviceState.ttxGOP);

  // Recover OSD transparent color
  MApi_GOP_GWIN_SetFMT0TransClr( COLOR_TRANSPARENT );

    // Restore GOP setting for Main-UI
#if (CHIP_FAMILY_TYPE==CHIP_FAMILY_MELODY)
    //if(MEMORY_MAP == MMAP_64MB)
  #if( UI_SKIN_SEL == UI_SKIN_1366X768X565 )
    {
        MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_OSD, E_GOP_DST_OP0,0, 0, ZUI_ALIGNED_VALUE(1366,8), 768);
        MApi_GOP_GWIN_Set_HSCALE(TRUE,ZUI_ALIGNED_VALUE(1366,8), PANEL_WIDTH);
        MApi_GOP_GWIN_Set_VSCALE(TRUE, 768, PANEL_HEIGHT);
        MApi_GOP_GWIN_Set_HStretchMode(E_GOP_HSTRCH_6TAPE_LINEAR);
        MApi_GOP_GWIN_Set_VStretchMode(E_GOP_VSTRCH_LINEAR);
    }
  #elif(( UI_SKIN_SEL == UI_SKIN_960X540XI8 )||( UI_SKIN_SEL == UI_SKIN_960X540X565))
    {
        MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_OSD, E_GOP_DST_OP0, 0, 0, 960, 540);
        MApi_GOP_GWIN_Set_HSCALE(TRUE,960, PANEL_WIDTH);
        MApi_GOP_GWIN_Set_VSCALE(TRUE, 540, PANEL_HEIGHT);
        MApi_GOP_GWIN_Set_HStretchMode(E_GOP_HSTRCH_6TAPE_LINEAR);
        MApi_GOP_GWIN_Set_VStretchMode(E_GOP_VSTRCH_LINEAR);
    }

  #else
    #error "Unknown UI resolution"

  #endif
#endif
}

static
void _SetGEDest(TT_RenderFrameBuffer* pFrameBuffer)
{
    GFX_BufferInfo bufferInfo;

    bufferInfo.u32Addr = pFrameBuffer->ttxFBAddress;
    bufferInfo.u32ColorFmt = pFrameBuffer->colorFormat;
    bufferInfo.u32Height = pFrameBuffer->bufferHeight;
    bufferInfo.u32Width = pFrameBuffer->bufferWidth;
    bufferInfo.u32Pitch = pFrameBuffer->bufferWidth;

    MApi_GFX_SetDstBufferInfo(&bufferInfo, 0);
}

static
void _FillRectangle ( TT_RenderFrameBuffer* pFrameBuffer,
                         TT_U8 ColorIndex,
                     TT_U16 x,
                     TT_U16 y,
                     TT_U16 width,
                     TT_U16 height)
{
  GFX_RectFillInfo fillBlock;

    _SetGEDest(pFrameBuffer);

  fillBlock.colorRange.color_s.b = ColorIndex;
  fillBlock.colorRange.color_e.b = ColorIndex;
  fillBlock.flag = GFXRECT_FLAG_COLOR_GRADIENT_X;
  fillBlock.fmt = GFX_FMT_I8;

  fillBlock.dstBlock.x     = x;
  fillBlock.dstBlock.y     = y;
  fillBlock.dstBlock.width = width;
  fillBlock.dstBlock.height= height;

  MApi_GFX_RectFill(&fillBlock);
}

static void _FrameBufferPositionChanaged(MS_U32 u32EventID, void* reserved0)
{
    GOP_GwinFBAttr fbAttr;

    reserved0 = reserved0;
    if(E_GOP_EVENT_BUF_ARRANGE_BEGIN == u32EventID)
    {
        MApi_GFX_BeginDraw();
    }
    else if(E_GOP_EVENT_BUF_ARRANGE_END == u32EventID)
    {
        MApi_GOP_GWIN_GetFBInfo(_deviceState.FrameBuffers[0].fbID,
                                &fbAttr);
        _deviceState.FrameBuffers[0].ttxFBAddress = fbAttr.addr;

        if(!_deviceState.doesNeedScaleDown)
        {
        MApi_GOP_GWIN_GetFBInfo(_deviceState.FrameBuffers[1].fbID,
                                &fbAttr);
        _deviceState.FrameBuffers[1].ttxFBAddress = fbAttr.addr;
        }
        else
        {
            MApi_GOP_GWIN_GetFBInfo(_deviceState.scaledownFrameBuffer.fbID,
                                        &fbAttr);
            _deviceState.scaledownFrameBuffer.ttxFBAddress = fbAttr.addr;
        }

        MApi_GFX_EndDraw();
    }
}
