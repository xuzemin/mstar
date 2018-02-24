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

#ifndef _MAPP_ZUI_APIGDI_H
#define _MAPP_ZUI_APIGDI_H

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#include "msAPI_OSD.h"

#ifdef MAPP_ZUI_APIGDI_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

///////////////////////////////////////////////
// from apiOSD

/**
 * \var RECT
 * \brief integer rectangle data structure - rectangle (16 bits integer)
 *
*/
typedef struct _RECT
{
   S16  left;
   S16  top;
   S16  width;
   S16  height;
} RECT;

/**
 * \def RECT_SET
 * \brief initial rectangle - initial rectangle position and size
 *
*/
#define RECT_SET(r, l, t, w, h) \
        { r.top = t; r.left = l; r.width = w; r.height = h; }

/**
 * \def RECT_SHIFT
 * \brief shift rectangle position - shift rectangle position with x,y offset
 *
*/
#define RECT_SHIFT(r, w, h) \
        { r.left += w; r.top += h; }

/**
 * \def RECT_SCALE
 * \brief adjust rectangle smaller - scale rectangle position to inner side
 *
*/
#define RECT_SCALE(r, w, h)  \
        { r.left += w; r.top += h; r.width -= (w<<1); r.height -= (h<<1); }

/**
 * \def RECT_REALIZE
 * \brief move rectangle position - add rectangle2 position to rectangle1
 *
*/
#define RECT_REALIZE(r1, r2) \
        {r1.left += r2.left; r1.top += r2.top;}

/**
 * \def RECT_MAP
 * \brief move rectangle position - subtract rectangle2 position to rectangle1
 *
*/
#define RECT_MAP(r1, r2) \
        {r1.left -= r2.left; r1.top -= r2.top;}

/**
 * \def ARGB
 * \brief make 32bits color - return 32bits color by RGB and alpha value
 *
*/
#define ARGB(a, r, g, b)  ((a&0xff)<<24 | (r&0xff) << 16 | (g&0xff) <<8 | (b&0xff))


/**
 * \var OSD_COLOR
 * \brief system independent OSD color
 *
*/
typedef U32 OSD_COLOR;

/**
 * \var FONT_ID
 * \brief system dependent font handle
 *
*/
typedef U8 FONT_ID;


/**
 * \var TRIANGLE_STYLE
 * \brief triangle type
 *
*/
typedef enum _TriangleStyle
{

/*
    _
    \|
*/
   eTriangle1,
/*
    |\
     -

*/
   eTriangle2,
/*
    /|
     -

*/

   eTriangle3,
/*
     _
    |/
*/
   eTriangle4,
/*
    <|
*/
   eTriangle5,
/*
    |>
*/

   eTriangle6,

/*
    _
    \/

*/
   eTriangle7,

/*
    /\
     -
*/
   eTriangle8
}TRIANGLE_STYLE;

/**
 * \var TEXT_ATTRIB
 * \brief text alignment type (left, center, right)
 *
*/
typedef enum _TextAttrib
{
   eTextAlignLeft           = 0x1,
   eTextAlignMiddle         = 0x2,
   eTextAlignRight          = 0x4,
   eTextAlignMiddleWH       = 0x8,
   eTextAlignLeft_MiddleH   = 0x10,
   eTextAlignRight_MiddleH  = 0x20,
}TEXT_ATTRIB;

/*
typedef enum
{
    ///horizontal round bar
    OSD_HRoundBar,
    ///Vertical round bar
    OSD_VRoundBar,
} ROUNDBAR_STYLE;
*/

/**
 * \var RECT_ATTRIB
 * \brief rectangle type (round or not)
 *
*/
typedef enum
{
   eRectBorder     ,
   eRectBorderRound  ,
}RECT_ATTRIB;

/**
 * \var OSD_GRADIENT
 * \brief gradient type (none, x, y, x-center, y-center,...)
 *
*/
typedef enum
{
    ///NO GRADIENT
    OSD_GRADIENT_DISABLE = CONSTANT_COLOR,
    ///GRADIENT based on X axis
    OSD_COLOR_GRADIENT_X = GRADIENT_X_COLOR,
    ///GRADIENT based on Y axis
    OSD_COLOR_GRADIENT_Y = GRADIENT_Y_COLOR,
    ///GRADIENT based on X axis (center)
    OSD_COLOR_GRADIENT_X_CENTER = GRADIENT_X_CENTER_COLOR,
    ///GRADIENT based on Y axis (center)
    OSD_COLOR_GRADIENT_Y_CENTER = GRADIENT_Y_CENTER_COLOR,
    ///GRADIENT based on X+Y axis (center)
    OSD_COLOR_GRADIENT_XY = GRADIENT_XY_COLOR,

}OSD_GRADIENT;

/**
 * \var LINE_TYPE
 * \brief line type (solid or dash)
 *
*/
typedef enum _LineType
{
   eSolidLine,
   eDashLine
} LINE_TYPE;

#if (ENABLE_UI_3D_PROCESS)
typedef enum
{
    E_UI_3D_OUTPUT_TOP_BOTTOM,           //0110
    E_UI_3D_OUTPUT_SIDE_BY_SIDE_HALF,    //1000
    E_UI_3D_OUTPUT_MODE_NONE,            //1111
    E_UI_3D_OUTPUT_MODE_MAX,
} E_UI_3D_OUTPUT_MODE;
#endif

///////////////////////////////////////////////

/**
 * \def GRAPHIC_DC
 * \brief system independent structure for low level drawing - we can pass framebuffer ID and alpha value to low level function
 *
*/
typedef struct _GRAPHIC_DC
{
    U8  u8FbID;
    U8  u8ConstantAlpha; //0xFF for disable alpha...
    U8  bSrcAlphaReplaceDstAlpha;

    //U32 u32MemAddr;
    //BOOLEAN bRoughMode;
} GRAPHIC_DC;

/**
 * \def DOUBLE_BUFFER
 * \brief system independent double buffer structure - store two buffer and one GWIN for double buffer drawing flow
 *
*/
typedef struct _DOUBLE_BUFFER
{
    U8     bInit : 1;
    U8     bUsed : 1;
    U8     bLoadPalette : 1;
    U8     bAllowFullScreenRelease : 1;

    //dcMain for display, dcBuff for background temp drawing...
    GRAPHIC_DC  dcMain;
    GRAPHIC_DC  dcBuff;
#if (ENABLE_UI_3D_PROCESS)
    GRAPHIC_DC  dc3DBuff;
#endif

    //the following properties should be the same between dcMain and dcBuff...
    U8          u8GWinID;
    RECT        rcGWin;
#if (ENABLE_UI_3D_PROCESS)
    RECT        rcGWin3D;
#endif
    //U16         u16Pitch;
    //U16         u16FbFmt;
} DOUBLE_BUFFER;

/**
 * \def PAINT_PARAM
 * \brief paint message structure - information from the painting handler (main frame), ex: invalide region and window current state
 *
*/
typedef struct _PAINT_PARAM
{
    GRAPHIC_DC dc;
    RECT * rect; //rectangle of current drawing UI control
    RECT * rect_invalidate; //rectangle of invalid region of current redrawing
    //U8  u8ConstantAlpha; //0xFF for disable alpha...
    BOOLEAN bIsFocus;
    BOOLEAN bIsDisable;
    BOOLEAN bIsVisible; //MSG_PAINT on invisible state??
} PAINT_PARAM;

INTERFACE void MApp_ZUI_API_InitGDIVariables(void);
INTERFACE BOOLEAN MApp_ZUI_API_InitGDI (const RECT * rect_gwin);
INTERFACE void MApp_ZUI_API_TerminateGDI( void );
INTERFACE GRAPHIC_DC* MApp_ZUI_API_GetBufferDC(void);
INTERFACE GRAPHIC_DC* MApp_ZUI_API_GetScreenDC(void);
INTERFACE void MApp_ZUI_API_ReleaseDC(const RECT * rect_invalidate);
INTERFACE void MApp_ZUI_API_ReleaseFullScreenDC(void);
INTERFACE void MApp_ZUI_API_ReleaseWithoutUpdateDC(void);
INTERFACE U8 MApp_ZUI_API_QueryGWinID(void);
INTERFACE void MApp_ZUI_API_QueryGWinRect(RECT* rect);
INTERFACE void MApp_ZUI_API_SetGWinPosition(U16 x, U16 y);
INTERFACE void MApp_ZUI_API_GetGWinPosition(U16* x, U16* y);
INTERFACE void MApp_ZUI_API_EnableFullScreenRelease(BOOLEAN bEnable);
INTERFACE BOOLEAN MApp_ZUI_API_IsAllowFullScreenRelease(void);

INTERFACE BOOLEAN MApp_ZUI_API_DoesIntersect (const RECT* psrc1, const RECT* psrc2);
INTERFACE void MApp_ZUI_API_UnionRect(RECT* pdrc, const RECT* psrc1);
INTERFACE void MApp_ZUI_API_IntersectRect(RECT* pdrc, const RECT* psrc1);
INTERFACE BOOLEAN MApp_ZUI_API_DoesContain (const RECT* pBig, const RECT* pInside);

INTERFACE GRAPHIC_DC MApp_ZUI_API_CreateDC(U16 w, U16 h);
INTERFACE void MApp_ZUI_API_ClearDC(GRAPHIC_DC *pDC, U32 u32Color);
INTERFACE void MApp_ZUI_API_DeleteDC(GRAPHIC_DC dc);

INTERFACE U8 MApp_ZUI_API_ZuiFormatToGeFormat(U8 u8ZuiFormat);
INTERFACE U8 MApp_ZUI_API_ZuiFormatToGopFormat(U8 u8ZuiFormat);
INTERFACE U8 MApp_ZUI_API_GetBPP(U8 u8ZuiFormat);
INTERFACE void MApp_ZUI_API_PrepareBufferDC(GRAPHIC_DC *pDC);

#if (ENABLE_UI_3D_PROCESS)
INTERFACE BOOL MApp_ZUI_API_ConvertTo3DTwinModeOutput(U8 u8SrcFbID, U8 u8DstFbID, U16 src_width, U16 src_height);
INTERFACE BOOL MApp_ZUI_API_Is_UI_3D_Mode_ON(void);
INTERFACE void MApp_ZUI_Set_UI_3D_Mode(E_UI_3D_OUTPUT_MODE TwinDirect);
INTERFACE E_UI_3D_OUTPUT_MODE MApp_ZUI_Query_UI_3D_Mode(void);
#endif

#undef INTERFACE

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _MAPP_ZUI_APIGDI_H */

