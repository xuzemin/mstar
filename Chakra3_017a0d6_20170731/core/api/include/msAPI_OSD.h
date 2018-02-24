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

#ifndef MSAPI_OSD_H
#define MSAPI_OSD_H
#include "datatype.h"
#include "MsTypes.h"
#include "Board.h"
#include "msAPI_Font.h"
#include "msAPI_OSD_Resource.h"
#include "apiGFX.h"
#include "MApp_GlobalSettingSt.h"

//#include "adpGE.h"

#if ( ENABLE_TTF_FONT )
	#include "msAPI_MLE_le_types.h"
#endif

#define GE_DRIVER_TEST        0
/********************************************************************************/
/*                                 Macro                                        */
/********************************************************************************/
#define BTN_TEXT_GAP            3//2

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
#define GEFONT_FLAG_ARABIC      0x0100
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

///////////////////////////////////////////////////////////////
// color format
///////////////////////////////////////////////////////////////
#define COLOR_TRANSPARENT                               0X000000
#define COLOR_WHITE                                     0xffffff
#define COLOR_BLACK                                     0x0f0f0f
#define COLOR_RED                                       0xe00000
#define COLOR_GREEN                                     0x00FF00
#define COLOR_YELLOW                                    0xffdf00
#define COLOR_LTBLUE                                    0x0080ff
#define COLOR_BLUE                                      0x0000ff
#define COLOR_DKGRAY                                    0x808080
#define COLOR_ASHEN                                         0xffC800
#define COLOR_MAGENTA                                    0xff00ff
#define COLOR_CYAN                                        0x00FFFF
#define COLOR_DKRED                                     0xbf5164
#define COLOR_DKGREEN                                   0x00bf20
#define COLOR_DKBLUE                                    0x0060c0//0x576288
#define COLOR_LTGRAY                                    0xdfdfdf
#define COLOR_GRAY                                      0xa0a0a0
#define COLOR_BRBLUE                                    0x00ffff
#define COLOR_PINK                                      0xffAFAF
#define COLOR_PURPLE                                    0x919EBA
#define COLOR_ORANGE                                    0xff9f00
#define COLOR_BROWN                                     0xa55e02//0xa05f00
#define COLOR_MIDBLUE                                   0x82d7ff
#define COLOR_PURPLERED                                 0x9E103A

//FOR S1 TRUNK
#define COLOR_MIDBLUE           0x82d7ff
#define COLOR_OPTION_LTBLUE     0x99ccff
#define COLOR_BOTTON_DKBLUE     0x3366cc
#define COLOR_BOTTONFRAME_BLUE  0x00ccff
#define COLOR_MENU_LTOLIVEGREEN    0xD5F565
//#define COLOR_MENU_BBB        0x0060C0
#define COLOR_MENU_BLUE            0x0080FF
#define COLOR_MENU_LTBLUE        0xC0DFE0
#define COLOR_MENU_DKGREEN        0x00BF20
#define COLOR_MENU_LTGREEN        0x00FF00
#define COLOR_MENU_PINK            0xF847F4
//#define COLOR_MENU_HHH        0xFF9F00
#define COLOR_MENU_DKGRAY        0x808080
#define COLOR_MENU_GRAY            0xA0A0A0
#define COLOR_MENU_LTGRAY        0xDFDFDF
//#define COLOR_MENU_LLL        0xA05F00
#define COLOR_MENU_LTYELLOW        0xFFFF80
#define COLOR_MENU_GRID         COLOR_LTBLUE
#define BACKGROUND_COLOR        COLOR_TRANSPARENT


///////////////////////////////////////////////////////////////
// blcok gradient attribute
///////////////////////////////////////////////////////////////
#define CONSTANT_COLOR              0x01
#define GRADIENT_X_COLOR            0x02
#define GRADIENT_Y_COLOR            0x04
#define GRADIENT_X_CENTER_COLOR     0x16
#define GRADIENT_Y_CENTER_COLOR     0x32
#define GRADIENT_XY_COLOR           0x64

//Bitblt Type Flag
#define GEBitbltType_Normal                  0x01
#define GEBitbltType_Bitmap                  0x02
#define GEBitbltType_Font                      0x04
#define GEBitbltType_Has_ScaleInfo     0x08

#define ZUI_ETT_LINE                10
#define MAX_LINE_ADDDR_NUM          30

/********************************************************************************/
/*                                 Enum                                         */
/********************************************************************************/
typedef enum
{
    CHAR_IDX_1BYTE,
    CHAR_IDX_2BYTE
} EN_CHAR_IDX_LENGTH;

typedef enum
{
    EN_ALIGNMENT_DEFAULT,           ///< Alignment default
    EN_ALIGNMENT_LEFT,              ///< Alignment left
    EN_ALIGNMENT_RIGHT,             ///< Alignment right
    EN_ALIGNMENT_CENTER             ///< Alignment center
} EN_ALIGNMENT_TYPE;

typedef enum
{
    EN_STRING_ENDING_NONE,
    EN_STRING_ENDING_1_DOT,
    EN_STRING_ENDING_2_DOT,
    EN_STRING_ENDING_3_DOT,
} EN_STRING_ENDING_TYPE;

#if 1
typedef enum _EN_OSDAPI_LANGUAGE
{
    LANGUAGE_OSD_CZECH,
    LANGUAGE_OSD_DANISH,
    LANGUAGE_OSD_GERMAN,
    LANGUAGE_OSD_ENGLISH,
    LANGUAGE_OSD_SPANISH,
    LANGUAGE_OSD_GREEK,
    LANGUAGE_OSD_FRENCH,
    LANGUAGE_OSD_CROATIAN,
    LANGUAGE_OSD_ITALIAN,
    LANGUAGE_OSD_HUNGARIAN,
    LANGUAGE_OSD_DUTCH,
    LANGUAGE_OSD_NORWEGIAN,
    LANGUAGE_OSD_POLISH,
    LANGUAGE_OSD_PORTUGUESE,
    LANGUAGE_OSD_RUSSIAN,
    LANGUAGE_OSD_ROMANIAN,
    LANGUAGE_OSD_SLOVENIAN,
    LANGUAGE_OSD_SERBIAN,
    LANGUAGE_OSD_FINNISH,
    LANGUAGE_OSD_SWEDISH,
    LANGUAGE_OSD_BULGARIAN,
    LANGUAGE_OSD_SLOVAK,
    LANGUAGE_OSD_THAI,
#if(ENABLE_COUNTRY_ICELANDIC)
    LANGUAGE_OSD_ICELAND,
    LANGUAGE_OSD_SAMI,
#endif
#if ( ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP || CHINESE_SIMP_FONT_ENABLE || ENABLE_DVB_TAIWAN_APP || CHINESE_BIG5_FONT_ENABLE )
    LANGUAGE_OSD_CHINESE,
#endif
    LANGUAGE_OSD_HINDI,
#if(ENABLE_SOUTHEAST_ASIA_CERTIFICATION)
    LANGUAGE_OSD_INDONESIA,
    LANGUAGE_OSD_MALAYSIA,
    LANGUAGE_OSD_ARABIC,
#endif
    LANGUAGE_OSD_URDU,
    LANGUAGE_OSD_TELUGU,
    LANGUAGE_OSD_TAMIL,
    LANGUAGE_OSD_MARATHI,
    LANGUAGE_OSD_BENGALI,
    LANGUAGE_OSD_ASSAMESE,
    LANGUAGE_OSD_GUJARATI,
    LANGUAGE_OSD_KANNADA,
    LANGUAGE_OSD_MALAYALAM,
    LANGUAGE_OSD_PUNJABI,
    LANGUAGE_OSD_UYGHUR,
    LANGUAGE_OSD_KHMER,
    LANGUAGE_OSD_LAO,
    LANGUAGE_OSD_MYANMAR,
#if (ENABLE_TTF_FONT)
    LANGUAGE_OSD_MENU_MAX = LANGUAGE_OSD_MYANMAR,        // OSD Menu Language Maximum
#else
    LANGUAGE_OSD_MENU_MAX = LANGUAGE_OSD_PUNJABI,        // OSD Menu Language Maximum
#endif
    LANGUAGE_OSD_GAELIC,
    LANGUAGE_OSD_WELSH,
    LANGUAGE_OSD_IRISH,
    LANGUAGE_OSD_KOREAN,
    LANGUAGE_OSD_JAPAN,
    LANGUAGE_OSD_MAORI,
    LANGUAGE_OSD_MANDARIN,
    LANGUAGE_OSD_CANTONESE,
    LANGUAGE_OSD_AUDIO_SUBTITLE_LANGUAGE_MAX_NUM = LANGUAGE_OSD_CANTONESE,      // Audio Language New Zealannd Maximum
    LANGUAGE_OSD_TURKISH,
    LANGUAGE_OSD_NETHERLANDS,
#if (!ENABLE_SOUTHEAST_ASIA_CERTIFICATION)
    LANGUAGE_OSD_ARABIC,
#endif
    LANGUAGE_OSD_HEBREW,
    LANGUAGE_OSD_KURDISH,
    LANGUAGE_OSD_PARSI,
    LANGUAGE_OSD_QAA,
    LANGUAGE_OSD_UND, //**-- Italy CI Certificate --**//
    LANGUAGE_OSD_UNKNOWN,       //move to hear to avoid haveing same value as spanish.

    LANGUAGE_OSD_AUDIO1,
    LANGUAGE_OSD_AUDIO2,
    LANGUAGE_OSD_AUDIO3,
    LANGUAGE_OSD_AUDIO4,
    LANGUAGE_OSD_AUDIO5,
    LANGUAGE_OSD_AUDIO6,
    LANGUAGE_OSD_ENGX2,// = MENU_LANGUAGE_FONT_ENGX2,
    LANGUAGE_OSD_DEFAULT = LANGUAGE_OSD_ENGLISH,
    LANGUAGE_OSD_NONE = 0xFF,
} EN_OSDAPI_LANGUAGE;
#endif

/********************************************************************************/
/*                             Structure type                                   */
/********************************************************************************/
/// GE RGB Color
typedef struct
{
#ifdef WORDS_BIGENDIAN
    U8 a;               ///< Alpha
    U8 r;               ///< Red
    U8 g;               ///< Green
    U8 b;               ///< Blue
#else
    U8 b;
    U8 g;
    U8 r;
    U8 a;
#endif
}MSAPI_GERGBColor;

/// GE Font format
typedef struct
{
    U16 flag;                    ///< scale or italic
    U16 width;                  ///< width
    U16 height;                 ///< height
    U8 dis;                     ///< distance
    MSAPI_GERGBColor clr;       ///< GE RGB Color
    U8 blinkfg;                 ///< blink foreground
    U8 blinkbg;                 ///< blink background
    U8 ifont_gap;               ///< inter-font gap, only valid for GEFONT_FLAG_GAP
} MSAPI_GEFontFmt;

/// OSD Button structure
typedef struct
{
    U16 x;                                  ///< x
    U16 y;                                  ///< y
    U16 width;                              ///< width
    U16 height;                             ///< height
    U16 radius;                             ///< radius
    U32 f_clr;                              ///< frame color
    U32 t_clr;                              ///< text_color
    U32 b_clr;                              ///< background color
    U32 g_clr;                              ///< gradient color
    U8 u8Gradient;                          ///< gradient
    EN_CHAR_IDX_LENGTH bStringIndexWidth;   ///< string index width
    EN_ALIGNMENT_TYPE enTextAlign;          ///< text align
    BOOLEAN fHighLight;                     ///< hight light or not
    U8 bFrameWidth;                         ///< frame width
    MSAPI_GEFontFmt Fontfmt;                ///< Font format
} OSDClrBtn;



typedef struct

{

    U16               sb_pit;       ///< source pitch in bytes

    U16               db_pit;       ///< destination pitch in bytes

    U32               sb_base;      ///< source buffer base in bytes

    U32               db_base;      ///< destination buffer base in bytes

}GEPitBaseInfo;

/// GE Color information
#if 1
typedef struct

{

#ifdef WORDS_BIGENDIAN

    U8 a;   ///< alpha

    U8 r;   ///< Red

    U8 g;   ///< Green

    U8 b;   ///< Blue

#else

    U8 b;   ///< Blue

    U8 g;   ///< Green

    U8 r;   ///< Red

    U8 a;   ///< alpha

#endif

} GERGBColor;
#endif

/// GE Color Range
typedef struct
{
    GERGBColor color_s;     ///< start color
    GERGBColor color_e;     ///< end color
} GEColorRange;

/// GE Bitmap format
typedef struct
{
    BOOLEAN bBmpColorKeyEnable; ///< colorkey enable
    GEColorRange clrrange;  ///< color range
    BOOLEAN bScale; ///< scaling enable
    U16 width; ///< bitmap width
    U16 height; ///< bitmap height
} GEBitmapFmt;


/// GE pointer coordinate
typedef struct
{
    U16 x; ///< x coordinate of point
    U16 y; ///< y coordinate of point
} GEPoint;


/// OSD line structure
typedef struct
{
    U16 x1;                     ///< start x
    U16 y1;                     ///< start y
    U16 x2;                     ///< end x
    U16 y2;                     ///< end y
    U32 u32LineColor;        ///< Line color
    U8     u8LineWidth;            ///< line width
} OSDClrLine;

typedef struct
{
    U16 width;
    U16 height;
    U8 rowdata[1];//row data
} BMPHDR;


typedef struct
{
    MSAPI_GERGBColor color_s;
    MSAPI_GERGBColor color_e;
} MSAPI_GEColorRange;

typedef struct
{
    BOOLEAN bBmpColorKeyEnable;
    MSAPI_GEColorRange clrrange;
    BOOLEAN bScale;
      U16 width;
    U16 height;
} MSAPI_GEBitmapFmt;

/// OSD Region
typedef struct
{
    U16 x;          ///< x
    U16 y;          ///< y
    U16 width;      ///< width
    U16 height;     ///< height
    U8  fbID;       ///< frame buffer ID
} MSAPI_OSDRegion;

typedef struct
{
    U16 x0;
    U16 y0;
    U16 x1;
    U16 y1;
} MSAPI_ClipWindow;

typedef struct
{
    U16  v0_x;  //destination x
    U16  v0_y; //destination y
    U16  width;    // same when drawing line (destination width)
    U16  height;  // same when drawing line (destination height)
    //U16  v1_x;
    //U16  v1_y;
    U16  v2_x;  //source x
    U16  v2_y;  //source y
    U8    direction; // direction[0] = x direction, direction[1] = y direction
}GECoordinate;

//==============================================================================
// Scaling factor info
//==============================================================================
/// Define the scaling facter for X & Y direction.
typedef struct
{
    U32 u32DeltaX;
    U32 u32DeltaY;
    U32 u32InitDelatX;
    U32 u32InitDelatY;
}GE_SCALE_INFO;


///@internal GE Bitmap information, For future use
typedef struct
{
    U8                 BitBltTypeFlag;      ///< bitblt type
    U8                 BmpFlag;             ///< Option for drawing effect(italic, mirror, rotate...etc)
    U8                 dst_fm;              ///< destination format
    U8                 src_fm;              ///< source format
    BMPHANDLE          bmphandle;           ///< handle for bitmap
    U16                src_width;           ///< source width (pixel)
    U16                src_height;          ///< source height (pixel)
    GECoordinate BitbltCoordinate;
    GE_SCALE_INFO ScaleInfo;
} GEBitBltInfo;

#ifdef MSAPI_OSD_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

// Variable
INTERFACE MSAPI_ClipWindow ClipWindow;
INTERFACE MSAPI_ClipWindow ClipWindowBackup;

#if ENABLE_ATSC
INTERFACE U8 g_u8EpgEttPos;
INTERFACE U8 g_u8EpgEttRows;
INTERFACE U16 g_u16LineAddrs[MAX_LINE_ADDDR_NUM];
#endif


INTERFACE void msAPI_OSD_Free_resource(void);
INTERFACE void msAPI_OSD_GET_resource(void);

INTERFACE U16 msAPI_OSD_u16Strlen(U16 *pu16Str);
#if 1//(KEEP_UNUSED_FUNC == 1 || defined(ZUI))
INTERFACE void msAPI_OSD_u16Strcpy(U16 *pu16Dest, U16 *pu16Src);
INTERFACE void msAPI_OSD_u16Strcat(U16 *pu16Dest, U16 *pu16Src);
#endif
INTERFACE int msAPI_OSD_u16Strcmp(U16 *u16strA,U16 *u16strB);
INTERFACE BOOLEAN msAPI_OSD_IsRTLLanguage( EN_OSDAPI_LANGUAGE enLang );
INTERFACE U16 msAPI_OSD_GetStrLength(U8 *pu8Str, EN_CHAR_IDX_LENGTH u8NoOfBytesPerChar);
INTERFACE U16 msAPI_OSD_GetStrWidth(FONTHANDLE font_handle, U8 *pu8Str, OSDClrBtn *pclrBtn);
INTERFACE U8 msAPI_OSD_GetFontHeight(FONTHANDLE font_handle);
#if 1
INTERFACE void msAPI_OSD_DrawLine(OSDClrLine *p_clr_line);
#else
INTERFACE void msAPI_OSD_DrawLine(OSDClrBtn *pclrBtn);
#endif
INTERFACE void msAPI_OSD_DrawText(FONTHANDLE font_handle, U8 *pu8Str, OSDClrBtn *pclrBtn);
INTERFACE void msAPI_OSD_DrawText_I2(FONTHANDLE font_handle, U8 *pu8Str, OSDClrBtn *pclrBtn);
INTERFACE void msAPI_OSD_DrawPunctuatedString(FONTHANDLE font_handle, U16 *pu16Str, OSDClrBtn *pclrBtn, U8 max_row_num);
INTERFACE void msAPI_OSD_DrawPunctuatedString_S1(FONTHANDLE font_handle, U8 *pu8Str, OSDClrBtn *pclrBtn, U8 max_row_num);
INTERFACE void msAPI_OSD_DrawPunctuatedString_S1_NEW(FONTHANDLE font_handle, U8 *pu8Str, OSDClrBtn *pclrBtn, U8 max_row_num, BOOL enable_3dot);
INTERFACE void msAPI_OSD_DrawPunctuatedString_S2(FONTHANDLE font_handle, U8 *pu8Str, OSDClrBtn *pclrBtn, U8 max_row_num);
INTERFACE void msAPI_OSD_DrawClippedString(FONTHANDLE font_handle, U16 *pu16Str, OSDClrBtn *pclrBtn, EN_STRING_ENDING_TYPE enEndingType);

INTERFACE void msAPI_OSD_DrawFrame(OSDClrBtn *clrBtn);
INTERFACE void msAPI_OSD_DrawBlock(OSDClrBtn *pclrBtn);
INTERFACE void msAPI_OSD_DrawMMIBlock(OSDClrBtn *pclrBtn);
INTERFACE void msAPI_OSD_DrawButton(FONTHANDLE font_handle, U8 *pu8Str, OSDClrBtn *pclrBtn);

INTERFACE void msAPI_OSD_DrawRoundFrame (OSDClrBtn *pclrBtn);
INTERFACE void msAPI_OSD_DrawRoundBlock (OSDClrBtn *pclrBtn);
INTERFACE void msAPI_OSD_DrawRoundButton(FONTHANDLE font_handle, U8 *pu8Str, OSDClrBtn *pclrBtn);

INTERFACE void msAPI_OSD_DrawBitmap(BMPHANDLE Handle, U16 u16StartX, U16 u16StartY, GEBitmapFmt bmpfmt);
INTERFACE void msAPI_OSD_DrawBitmap_Subtitle(BMPHANDLE Handle, U16 u16StartX, U16 u16StartY, GEBitmapFmt bmpfmt);
INTERFACE void msAPI_OSD_SetClipWindow(U16 U16x0, U16 U16y0, U16 U16x1, U16 U16y1);
INTERFACE void msAPI_OSD_RestoreBackupClipWindow(void);
INTERFACE void msAPI_OSD_GetClipWindow(U16 *pX0, U16 *pY0, U16 *pX1, U16 *pY1);
INTERFACE void msAPI_OSD_BackupClipWindow(void);
INTERFACE void msAPI_OSD_SetDither(BOOLEAN bEnable);
INTERFACE void msAPI_OSD_SetRotation(U8 locrotate,U8 glorotate);

INTERFACE void msAPI_OSD_SetOSDLanguage(EN_OSDAPI_LANGUAGE eLanguage);
INTERFACE EN_OSDAPI_LANGUAGE msAPI_OSD_APILanguage2OSDLanguage(EN_LANGUAGE enLangIndex);

INTERFACE EN_OSDAPI_LANGUAGE msAPI_OSD_GetOSDLanguage(void);
#if ( ENABLE_TTF_FONT )
INTERFACE LE_LanguageTag_e msAPI_OSD_GetOSDLanguageTag(void);
#endif

INTERFACE void msAPI_OSD_EnterDivxSubtitleMode(BOOLEAN bDivxSubtitle);
INTERFACE BOOLEAN msAPI_OSD_GetDivxSubtitleMode(void);
//INTERFACE void msAPI_OSD_DisplayDivxSubtitleText(BOOLEAN bTextMode);
INTERFACE void msAPI_OSD_SetHebrewLangMixedMode(BOOLEAN bHebrewMixed);


#if ENABLE_CI
INTERFACE unsigned short msAPI_OSD_Get_TextString_Width(FONTHANDLE font_handle, U8 *pu8Str, OSDClrBtn *pclrBtn);
#endif

#undef INTERFACE

// Optional special drawing function

#define MSAPI_OSD_AQUA

#ifdef MSAPI_OSD2_C
#define INTERFACE
#else
#define INTERFACE extern
#endif
INTERFACE U8 msAPI_OSD_CopyRegion(MSAPI_OSDRegion *src, MSAPI_OSDRegion *dst);

#ifdef MSAPI_OSD_AQUA
INTERFACE void msAPI_OSD_DrawGradientRoundBlock(OSDClrBtn *pclrBtn);

#endif

INTERFACE void msAPI_OSD_DrawColorKeyBitmap(BMPHANDLE Handle, U16 u16StartX, U16 u16StartY, MSAPI_GEBitmapFmt bmpfmt);

#if 1//def ZUI
INTERFACE void msAPI_OSD_GetPunctuatedStringHeight(FONTHANDLE font_handle, U16 *pu16Str, OSDClrBtn *pclrBtn, U8 max_row_num,
    U8 * pu8rows, U16 * pu16height);
#endif

#define msAPI_GE_BitBlt(_BitbltInfo, _PitBaseInfo) MDrv_GE_BitBlt(_BitbltInfo, _PitBaseInfo)
#define MDrv_GE_SetDC_CSC_FMT(mode, yuv_out_range, uv_in_range, srcfmt, dstfmt) \
        MApi_GFX_SetDC_CSC_FMT(mode, yuv_out_range, uv_in_range, srcfmt, dstfmt)

#define msAPI_GE_SetDC_CSC_FMT(mode, yuv_out_range, uv_in_range, srcfmt, dstfmt) \
        MApi_GFX_SetDC_CSC_FMT(mode, yuv_out_range, uv_in_range, srcfmt, dstfmt)
#define msAPI_GE_SetNearestMode(enable) MApi_GFX_SetNearestMode(enable)
#define msAPI_GE_SetPatchMode(repeat) MApi_GFX_SetPatchMode(repeat)

INTERFACE void msAPI_OSD_DrawScrolPunctuatedString(FONTHANDLE font_handle, U8 *pu8Str, OSDClrBtn *pclrBtn, U8 max_row_num);
#if ENABLE_ATSC
INTERFACE void msAPI_OSD_GetPunctuatedStringRowsLine(FONTHANDLE font_handle, U8 *pu8Str, OSDClrBtn *pclrBtn, U8 max_row_num, U16 *pu16rows);
#endif
// Wrapper
INTERFACE BMPHANDLE MDrv_GE_LoadBitmap(MS_U32 addr, MS_U32 u32len, MS_U16 u16width, MS_U16 u16height, MS_U8 dstloc);
INTERFACE void MDrv_GE_DrawBitmap(BMPHANDLE handle, GEPoint *ppoint, GEBitmapFmt *pbmpfmt);
INTERFACE void MDrv_GE_BitBlt(GEBitBltInfo *BitbltInfo, GEPitBaseInfo *PitBaseInfo);
#if (ENABLE_UI_3D_PROCESS)
INTERFACE void MDrv_GE_ColorKeyBitBlt(GEBitBltInfo *BitbltInfo, GEPitBaseInfo *PitBaseInfo, MS_U32 clrKeyFrom, MS_U32 clrKeyTo);
INTERFACE void MDrv_GE_StretchBitBltPixelAlpha(GEBitBltInfo *BitbltInfo, GEPitBaseInfo *PitBaseInfo);
#endif
#define msAPI_GE_SetMirror(MirrorX, MirrorY) MApi_GFX_SetMirror(MirrorX, MirrorY)
#define msAPI_GE_SetRotate(Rotate) MApi_GFX_SetRotate(Rotate)
#if TXTFONT_ZOOM2X
INTERFACE void msAPI_OSD_DrawPunctuatedString_Zoom2X(FONTHANDLE font_handle, U8 *pu8Str, OSDClrBtn *pclrBtn, U8 max_row_num);
#endif
#define MDrv_GE_ClearFrameBuffer(a,b,c)  MApi_GFX_ClearFrameBuffer(a,b,c)
#define MDrv_GE_ClearFrameBufferByWord(a,b,c)  MApi_GFX_ClearFrameBufferByWord(a,b,c)

INTERFACE void msAPI_GOP_GWIN_SetHMirror(BOOL bHMirror);
INTERFACE void msAPI_GOP_GWIN_SetVMirror(BOOL bVMirror);

#undef INTERFACE

// end Optional special drawing function

#endif /* MSAPI_OSD_H */

