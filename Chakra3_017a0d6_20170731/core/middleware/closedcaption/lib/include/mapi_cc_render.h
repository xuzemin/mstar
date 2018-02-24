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

#ifndef MAPI_CC_RENDER_H
#define MAPI_CC_RENDER_H

/***************************************************************************************/
/*                 Header Files                                                        */
/***************************************************************************************/
#include "mapi_cc_type.h"

#ifdef __cplusplus
extern "C" {
#endif
/***************************************************************************************/
/* DEFINE                                                                         */
/***************************************************************************************/
#define CONSTANT_COLOR              0x01
#define GRADIENT_X_COLOR            0x02
#define GRADIENT_Y_COLOR            0x04
#define GRADIENT_X_CENTER_COLOR     0x16
#define GRADIENT_Y_CENTER_COLOR     0x32
#define GRADIENT_XY_COLOR           0x64

/// Types for GEFontFmt.flag: Default
#define GEFONT_FLAG_DEFAULT     0x0000
/// Types for GEFontFmt.flag: Italic
#define GEFONT_FLAG_ITALIC        0x0001
/// Types for GEFontFmt.flag: Scale
#define GEFONT_FLAG_SCALE        0x0002
/// Types for GEFontFmt.flag: Compact
#define GEFONT_FLAG_COMPACT     0x0004
/// Types for GEFontFmt.flag: Background
#define GEFONT_FLAG_BACKGROUND  0x0008
/// Types for GEFontFmt.flag: Blink
#define GEFONT_FLAG_BLINK        0x0010
/// Types for GEFontFmt.flag: Variable width
#define GEFONT_FLAG_VARWIDTH    0x0020  // variable width
/// Types for GEFontFmt.flag: Gap
#define GEFONT_FLAG_GAP            0x0040  // gap (specified by font_tab) between fonts
/// Types for GEFontFmt.flag: Bold
#define GEFONT_FLAG_BOLD        0x0080
/// Types for GEFontFmt.flag: Simple
#define GEFONT_FLAG_SIMPLE      0x0100
/// Types for GEFontFmt.flag: Blink foreground
#define GEFONT_FLAG_BLINK_FG    0x0200
/// Types for GEFontFmt.flag: Blink Background
#define GEFONT_FLAG_BLINK_BG    0x0400
/// Types for GEFontFmt.flag: TRANSL Foreground
#define GEFONT_FLAG_TRANSL_FG   0x0800
/// Types for GEFontFmt.flag: TRANSL Background
#define GEFONT_FLAG_TRANSL_BG   0x1000
/// Types for GEFontFmt.flag: Transparent Foreground
#define GEFONT_FLAG_TRANSP_FG   0x2000
/// Types for GEFontFmt.flag: Transparent Background
#define GEFONT_FLAG_TRANSP_BG   0x4000
/// Types for GEFontFmt.flag: Mirror
#define GEFONT_FLAG_MIRROR   0x8000

#define CC_ROLL_UP_DOWN         0
#define CC_ROLL_LEFT_RIGHT      1
#define CC_ROLL_UNKNOWN         2

#define KOREAN_TEXT_CODE      0xFF00
/***************************************************************************************/
/* ENUM                                                                              */
/***************************************************************************************/
typedef enum
{
    CC_FONTINFO_WIDTH           = 0,
    CC_FONTINFO_HEIGHT          = 1,
} EN_CC_FontInfo;

typedef enum
{
    CC_GOP_MODE_I8 = 0x00,
    CC_GOP_MODE_2266,
} EN_CC_GOP_MODE;

typedef enum
{
    BORDER_FILL_OPACITY_SOLID,
    BORDER_FILL_OPACITY_FLASH,
    BORDER_FILL_OPACITY_TRANSLUCENT,
    BORDER_FILL_OPACITY_TRANSPARENT,
} EN_BORDER_EFFECT_OPACITY;

typedef enum
{
    /* both using in setting and getting info */
    ///CC current program information Frame buffer width
    CC_FBINFO_DISPWIDTH         = 0x0000,
    ///CC current program information Frame buffer height
    CC_FBINFO_DISPHEIGHT,
    ///CC current program information Frame buffer active
    CC_FBINFO_ISACTIVEFB,
    ///CC current program information Frame buffer palette
    CC_FBINFO_PPALETTE,

    /* using in setting info */
    ///CC current program information Frame buffer horizontal offset
    CC_HORIZONTAL_OFFSET       = 0x1000,
    ///CC current program information Frame buffer vertical offset
    CC_VERTICAL_OFFSET,
    ///CC current program information CC font handle
    CC_FONT_HANDLER,
    ///CC current program information CC font glyph handle
    CC_FONT_GLYPH_HANDLER,
    ///CC current program information CC choose primary surface
    CC_SET_PRIMARY_SURFACE,
    ///CC current CC font id
    CC_FONT_ID,
    ///CC Window info
    CC_WINDOW_INFO,
    ///CC Window Border
    CC_WINDOW_BORDER,
    ///CC Window Flip
    CC_WONOW_FLIP,
    ///CC translucent value
    CC_TRANSTUCENT_VALUE,
    ///CC Font Indent Gap
    CC_FONT_INDENTGAP,
    ///CC korean wunsung table,
    CC_KOREAN_WUNSUNGTABLE,
    ///CC ATTRIBUTE FLAG,
    CC_ATTRIBUTE_FLAG,
    ///CC BLOCK0 ADDR --- only used in NOS,
    CC_BLOCK0_ADDR,
    ///CC BLOCK1 ADDR --- only used in NOS,
    CC_BLOCK1_ADDR,
    ///CC big window width --- only used in NOS,
    CC_DISWINDOW_WIDTH,
    ///CC big window height --- only used in NOS,
    CC_DISWINDOW_HEIGHT,
    ///CC align value,
    CC_ALIGN_VALUE,
    ///CC window color format ARGB4444 or ARGB8888 or I8 --- only used in OS,
    CC_SET_COLOR_MODE,

    
    /* using in getting info */
    ///CC current program information Frame buffer display window
    CC_FBINFO_WINDOW               = 0x2000,
    ///CC current program information Blink Frame buffer display window
    CC_BLINK_FBINFO_WINDOW,
    ///CC current program information Display buffer display window
    CC_DISPALY_WINDOW,
    ///CC Layer maximum Width
    CC_LAYER_MAXIMUM_WIDHT,
    ///CC Layer maximum Height
    CC_LAYER_MAXIMUM_HEIGHT,
    // CC video display rect
    CC_VIDEO_DISP_RECT,
    // CC video display full width
    CC_VIDEO_DISP_FULL_WIDTH,
    // CC video display full height
    CC_VIDEO_DISP_FULL_HEIGHT,
    ///CC virtual layer width
    CC_VIRTUAL_LAYER_WIDTH,
    ///CC virtual layer height
    CC_VIRTUAL_LAYER_HEIGHT,
    // CC real layer width
    CC_REAL_LAYER_WIDTH,
    // CC real layer height
    CC_REAL_LAYER_HEIGHT,
    // panel rect
    CC_VIDEO_PANEL_RECT,
} EN_CC_RenderInfo;

/// Scrolling direction
typedef enum
{
    CC_SCROLL_NONE = 0, ///< no scrolling
    CC_SCROLL_UP,       ///< scrolling up
    CC_SCROLL_DOWN,     ///< scrolling down
    CC_SCROLL_LEFT,     ///< scrolling left
    CC_SCROLL_RIGHT,    ///< scrolling right
    CC_SCROLL_MAX       ///< scrolling max enum number
} EN_CC_SCROLL_TYPE;

typedef enum
{    
    RStep_CC_Zero = 0x00,         // Not smooth scrolling, set destination offset directly
    RStep_CC_One,
    RStep_CC_Two,
    RStep_CC_Three,
    RStep_CC_Four,
    RStep_CC_Five,
    RStep_CC_Six,
    RStep_CC_Nume = 0xFF,   // No scrolling, set offset directly
} EN_Scrolling_Step;

typedef enum
{
    MSAPI_CC_TYPE_NONE = 0,
    MSAPI_CC_TYPE_NTSC_FIELD1 = 1,
    MSAPI_CC_TYPE_NTSC_FIELD2 = 2,
    MSAPI_CC_TYPE_DTVCC = 3,
    MSAPI_CC_TYPE_NTSC_TWOFIELD = 4,
} EN_MSAPI_CC_TYPE;

typedef enum
{
    WINDOW_FLASH = 0,
    TEXT_BG_FLASH,
    TEXT_FG_FLASH,
    EDGE_FLASH,
} EN_FLASH_MODE;

typedef enum
{
    EDGE_NONE = 0,
    EDGE_RAISED,
    EDGE_DEPRESSED,
    EDGE_UNIFORM,
    EDGE_LEFT_DROP_SHADOW,
    EDGE_RIGHT_DROP_SHADOW,
} EDGE_EFFECT_TYPE;

typedef enum
{
    BORDER_NONE = 0,
    BORDER_RAISED,
    BORDER_DEPRESSED,
    BORDER_UNIFORM,
    BORDER_LEFT_DROP_SHADOW,
    BORDER_RIGHT_DROP_SHADOW,
} EN_BORDER_EFFECT_TYPE;

/***************************************************************************************/
/* Data structure                                                                      */
/***************************************************************************************/
/// GE Font format
typedef struct
{
    CC_U16 flag;                    ///< scale or italic
    CC_U16 width;                  ///< width
    CC_U16 height;                 ///< height
    CC_U8 dis;                     ///< distance
    CC_U8 blinkfg;                 ///< blink foreground
    CC_U8 blinkflashfg;            ///< blink flash on foreground
    CC_U8 blinkbg;                 ///< blink background
    CC_U8 ifont_gap;               ///< inter-font gap, only valid for GEFONT_FLAG_GAP
} CC_GEFontFmt;

typedef struct
{
    CC_U16 TextCode;
    CC_U16 TextHposition;
    CC_U16 TextVposition;
    CC_U8 fHandle;     // Reference to MAX_FONT
    CC_U8 FGColorIndex;
	CC_U8 FGBlinkColorIndex;
    CC_U8 EdgeColorIdx;
	CC_U8 EdgeBlinkColorIdx;
    CC_U8 BGColorIndex;
	CC_U8 BGBlinkColorIndex;
    CC_U8 EdgeType     : 3;
    CC_U8 CharSize     : 2;
    CC_U8 FG_Blink     : 1;
    CC_U8 BG_Blink     : 1;
    CC_U8 Italic       : 1;
    CC_U8 Underline    : 1;
    CC_U8 HeadBlock    : 1;
    CC_U8 TailBlock    : 1;
} BlinkChar_Info;

typedef struct
{
    CC_U32 BlockSrc0Address;
    CC_U32 BlockSrc1Address;
    CC_U16 V0_x;
    CC_U16 V0_y;
    CC_U16 V1_x;
    CC_U16 V1_y;

    CC_U8 Char_Width;
    CC_U8 Char_Height;

    CC_U8 FGColorIndex;
	CC_U8 FGBlinkColorIndex;
    CC_U8 BGColorIndex;
    CC_U8 FG_Blink  :1;
    CC_U8 BG_Blink  :1;
    CC_U8 TOPRSV_Lines   :2;
    CC_U8 BTMRSV_Lines   :2;
    CC_U8 BGFlashMode     :1;     // 1: for transparent color ; 0: for window's color
    CC_U8 fbId;
} BlinkBlock_Info;

/// OSD Button structure
typedef struct
{
    CC_U16 x;                                  ///< x
    CC_U16 y;                                  ///< y
    CC_U16 width;                              ///< width
    CC_U16 height;                             ///< height
    CC_U16 radius;                             ///< radius
    CC_U32 f_clr;                              ///< frame color
    CC_U32 t_clr;                              ///< text_color
    CC_U32 b_clr;                              ///< background color
    CC_U32 g_clr;                              ///< gradient color
    CC_U8 u8Gradient;                          ///< gradient
    CC_BOOL fHighLight;                     ///< hight light or not
    CC_U8 bFrameWidth;                         ///< frame width
    CC_GEFontFmt Fontfmt;                ///< Font format
    CC_U8 fbId;
    
} CC_OSDClrBtn;

typedef struct _CCResizeFbInfo
{
    CC_U32                 w;
    CC_U32                 h;
    CC_U16                 *offsetY;
    CC_U8                  fbId;
    CC_U8                  colorIdx;
    CC_U8                  u8RowHeight;
    CC_BOOL                fFlash;
} stCCResizeFbInfo;

typedef struct 
{
    CC_BOOL bWinIsAcive;
    CC_BOOL bWinHasText;
    CC_BOOL bWinNeedWindow;

    #if 0
    CC_U8  u8Win_IsWriteChar;
    CC_U8  u8Win_BackTextCol;
    CC_U8  u8Win_DispTextCol;
    #endif
}stCCWindowInfo;

typedef struct 
{
    CC_U8 u8WinFBID;
    CC_U16 u16horizontalOffset;
    CC_U16 u16verticalOffset;
}stCCWindowFBinfo;

/// Bounding box (BBox) of a glyph
typedef struct
{
    CC_S32  X0;       ///< Position of the left edge of the bounding box
    CC_S32  width;    ///< Width of the bounding box
    CC_S32  Y0;       ///< Position of the top edge of the bounding box
    CC_S32  height;   ///< Height of the bounding box
}CC_GLYPH_BBOX;

/// Bounding box (BBox) of a glyph
typedef struct
{
    CC_GLYPH_BBOX stFontBbox;
    CC_U8  u8DisplayWidth;
} stCCFontBBOX;

typedef struct
{
    CC_U8 winId;
    CC_U8 dir;
    CC_U8 RStep;
    CC_U8 colorIdx;
    CC_U16 pixLines;
    CC_U16 rolX;
    CC_U16 rolY;
    CC_U16 w;
    CC_U16 h;
    CC_BOOL bIsNotTextMode;
} CC_ScrollLineINFO;

typedef struct
{
    CC_U8 Offset_x;
    CC_U8 Offset_y;
    CC_U32 DisplayWidth;
    CC_U32 DisplayHeight;
    CC_U8 BorderColor;
    CC_U8 BorderOpacity;
    CC_U8 BorderType;
    CC_U8 BorderColorIndex;
} CC_WindowsBorderInfo;

typedef struct 
{
    CC_U8 Window_NO;
    CC_U8 Window_Priority;
} stCCWinPriority;

typedef struct
{
    CC_U8 a;   ///< alpha
    CC_U8 r;   ///< Red
    CC_U8 g;   ///< Green
    CC_U8 b;   ///< Blue
} CC_GERGBColor;

///CC color's information
typedef struct
{
    ///CC program information text foreground color index
    CC_U8 u8Text_FGColorIndex;
    ///CC program information text background color index
    CC_U8 u8Text_BGColorIndex;
    ///CC program information Edge background color index
    CC_U8 u8Edge_ColorIndex;
    ///CC program information block background color index
    CC_U8 u8Block_FGColorIndex;
    ///CC program information block background color index
    CC_U8 u8Block_BGColorIndex;
    ///CC program information caption window is blinking
    CC_BOOL bIsWindowBlink;
    ///CC program information caption block is blinking
    CC_BOOL bIsBlockBlink;
} CC_ColorInfo_t;
    
/// Internal customer functions
/// Render target functions
typedef struct
{
   CC_BOOL (*Open)(void *pDfb, void *pLayer, void *pSur);
   void (*Close)(void);
   void (*Init)(void);
   void (*Reset)(void);
   CC_BOOL (*Create)(CC_U8 fbId, void *pInfo, void *pInfo1);
   void (*Delete)(CC_U8 fbId);
   CC_BOOL (*Clear)(CC_U8 id);
   void (*DrawWindowBorder)(CC_U8 WinID);
   void (*DrawBlock)(BlinkBlock_Info *BlockInfo, CC_BOOL bSwa, CC_BOOL bCaptionWin);
   void (*DrawText)(BlinkBlock_Info *BlockInfo, BlinkChar_Info *CharRow, CC_U8 length, CC_BOOL bIndention, void *pOpt1,void *pOpt2);
   void (*DrawText1)(CC_FONTHANDLE font_handle, CC_U8 *pu8Str, CC_OSDClrBtn *pclrBtn);
   void (*GetFbSize)(CC_U8 fbId, CC_U32 *w, CC_U32 *h);
   void (*GetFontBBoxinfo)(CC_FONTHANDLE handle, CC_U16 u16TextCode, CC_BOOL bItalic, stCCFontBBOX *BBoxinfo);
   void (*InitialPalette)(CC_GERGBColor *pPaletteIndex);
   void (*SetPalette)(CC_U8 fbId);
   void (*SetNewPalette)(CC_U8 newId, CC_U8 oldId, CC_U8 id);
   CC_BOOL (*SetDstWindow)(CC_U8 u8CaptionWinID);
   void (*SetCcInfo)(CC_U8 fbId, EN_CC_RenderInfo select, CC_U32 val);
   void (*GetCcInfo)(CC_U8 fbId, EN_CC_RenderInfo select, CC_U32 *ret);
   void (*GetCcFontInfo)(CC_FONTHANDLE fh, CC_U8 select, CC_U8 *ret);
   void (*SetWinPriority)(void);   
   void (*MoveFb)(CC_U8 fbId, CC_U32 x, CC_U32 y);
   void (*ResizeFb)(stCCResizeFbInfo *pInfo);
   void (*ScrollFb)(CC_ScrollLineINFO *ScrollInfo);
   void (*FlushEngine)(CC_U8 u8Roll, CC_U8 u8FBID);
   void (*SoftBlinkEngine)(void);
   void (*SetSoftBlink)(EN_FLASH_MODE flash_mode, CC_ColorInfo_t *pInfo, CC_U8 id);
   void (*SetPreviewPalette)(CC_BOOL bFgBlink, CC_BOOL bBgBlink, CC_BOOL bWindowBlink, BlinkBlock_Info *pBlk, BlinkChar_Info *pChar);
   void (*Convert_Wunsung2Unicode)(CC_U16 *p16Wunsung, CC_U16 *p16Unicode);
   void (*PassCallbackAddr)(CC_U32 u32EventID, void* reserved0);
   void (*SetScrollDirection)(CC_U8 u8Roll);
   void (*GetPalette) ( CC_U8 colorIndex, CC_GERGBColor *ppalette);
} CC_RenderTarget;

/***************************************************************************************/
/* Variables                                                                           */
/***************************************************************************************/
extern const CC_RenderTarget CC_RenderFuns;
 
/***************************************************************************************/
/* Functions                                                                           */
/***************************************************************************************/

#ifdef __cplusplus
  }
#endif

#endif
///*** please do not remove change list tag ***///
///***$Change: 1504174 $***///
