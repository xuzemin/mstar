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

#ifndef MAPI_CC_INTERFACE_H
#define MAPI_CC_INTERFACE_H

#include "mapi_cc_type.h"

#ifdef __cplusplus
extern "C" {
#endif


    /***************************************************************************************/
    /* Define                                                                              */
    /***************************************************************************************/
    #define NULL_TAG     0x00
    #define ERROR_TAG    0x01
    #define MONITOR_TAG  0x02
    #define RENDER_TAG   0x04
    #define DECODE_TAG   0x08
    #define B_DECODE_TAG 0x10
    #define K_DECODE_TAG 0x20

    #define CC_DEBUG_MSG(tag, fmt, arg...)   \
      if(g_bDumpDbgMsg){   \
        char str[100] = "\n";   \
        if(tag & MONITOR_TAG)   strcat(str, "[CC:Mon]");  \
        if(tag & RENDER_TAG)    strcat(str, "[CC:Ren]");  \
        if(tag & DECODE_TAG)    strcat(str, "[CC:Dec]");  \
        if(tag & B_DECODE_TAG)  strcat(str, "[CC:B_Dec]");  \
        if(tag & K_DECODE_TAG)  strcat(str, "[CC:K_Dec]");  \
        if(tag & ERROR_TAG)     strcat(str, "[CC:ERROR]");  \
        strcat(str,fmt);                                        \
        printf(str,##arg);                                  \
      }


    /***************************************************************************************/
    /* Data structure                                                                      */
    /***************************************************************************************/
    /* Enum Setting */
    ///CC progrem information CC decode 708/608
    typedef enum
    {
        SYSINFO_MODE_708 = 0,
        SYSINFO_MODE_608,

        SYSINFO_MODE_DTV = SYSINFO_MODE_708,
        SYSINFO_MODE_ATV = SYSINFO_MODE_608,

    }EN_CC_SYSINFO;

    ///V-chip program information V_chip data status
    typedef enum
    {
        VCHIP_DATA_NONE,
        VCHIP_DATA_NO_CHANGE,
        VCHIP_DATA_CHANGE
    } EN_VCHIP_DATA_STATUS;

    typedef enum
    {
        CAPTION_ASP_4TO3,
        CAPTION_ASP_16TO9,
        CAPTION_ASP_INVALID = 0xFF,
    }EN_CAPTION_ASPECT_RATIO;

    typedef enum
    {
        CC_PREVIEW_DEFAULT,
        CC_PREVIEW_AUTO,
        CC_PREVIEW_DEBUG_DUMP, // CC_PREVIEW_AUTO + packet dump
    }EN_CAPTION_PREVIEW_MODE;

    typedef enum
    {
        CC_USING_608,
        CC_USING_157,
    }EN_CAPTION_608OR157;

    /* This Enum should be followed by Menu Setting Enum */
    ///CC current program information service mode
    typedef enum
    {
        CS_OFF,
        CS_CC1,
        CS_CC2,
        CS_CC3,
        CS_CC4,
        CS_TEXT1,
        CS_TEXT2,
        CS_TEXT3,
        CS_TEXT4,
        CS_SERVICE1,
        CS_SERVICE2,
        CS_SERVICE3,
        CS_SERVICE4,
        CS_SERVICE5,
        CS_SERVICE6,
        CS_SERVICE64 = CS_SERVICE1 + 63,
        CS_XDS,
    } EN_CAPTION_SERVICE;

    /// For OSD UI Setting
    typedef enum
    {
        ///CC current program information set by  stream
        CAPTION_OPTIONMODE_SETBYSTREAM,
        ///CC current program information set by  custom (OSD)
        CAPTION_OPTIONMODE_CUSTOM,
        /// counts of this enum
        CAPTION_OPTIONMODE_NUM
    } EN_CAPTION_CSOPTION_STYLE;

    ///CC program information palette color index (64 color)
    typedef enum
    {
        CAPTION_INNER_DEP64COLOR_BLACK = 0,
        CAPTION_INNER_DEP64COLOR_RED = 48,
        CAPTION_INNER_DEP64COLOR_GREEN = 12,
        CAPTION_INNER_DEP64COLOR_YELLOW = 60,
        CAPTION_INNER_DEP64COLOR_BLUE = 3,
        CAPTION_INNER_DEP64COLOR_MAGENTA = 51,
        CAPTION_INNER_DEP64COLOR_CYAN = 15,
        CAPTION_INNER_DEP64COLOR_WHITE = 63,
    } EN_CAPTION_INNER_DEP64COLOR_PLATE;

    ///CC program information palette color index
    typedef enum
    {
        CAPTION_INNER_MIN8COLOR_BLACK,
        CAPTION_INNER_MIN8COLOR_RED,
        CAPTION_INNER_MIN8COLOR_GREEN,
        CAPTION_INNER_MIN8COLOR_YELLOW,
        CAPTION_INNER_MIN8COLOR_BLUE,
        CAPTION_INNER_MIN8COLOR_MAGENTA,
        CAPTION_INNER_MIN8COLOR_CYAN,
        CAPTION_INNER_MIN8COLOR_WHITE,
    } EN_CAPTION_INNER_MIN8COLOR_PLATE;

    ///CC current program information Font size
    typedef enum
    {
        CAPTION_FONTSIZE_NORMAL,
        CAPTION_FONTSIZE_SMALL,
        CAPTION_FONTSIZE_LARGE,
        CAPTION_FONTSIZE_DEFAULT = 0xFF,
    } EN_CAPTION_FONT;

    typedef enum
    {
        ///CC program information none edge style
        CAPTION_EDGESTYLE_NONE,
        ///CC program information raise edge style
        CAPTION_EDGESTYLE_RAISE,
        ///CC program information depressed edge style
        CAPTION_EDGESTYLE_DEPRESSED,
        ///CC program information uniform edge style
        CAPTION_EDGESTYLE_UNIFORM,
        ///CC program information lightdropshadow edge style
        CAPTION_EDGESTYLE_LIGHTDROPSHADOW,
        ///CC program information lightdropshadow edge style
        CAPTION_EDGESTYLE_RIGHTDROPSHADOW,
        CAPTION_EDGESTYLE_DEFAULT = 0xFF,
    } EN_CAPTION_EDGE_STYLE;

    ///CC program information edge color
    typedef enum
    {
        CAPTION_EDGECOLOR_BLACK,
        CAPTION_EDGECOLOR_RED,
        CAPTION_EDGECOLOR_GREEN,
        CAPTION_EDGECOLOR_YELLOW,
        CAPTION_EDGECOLOR_BLUE,
        CAPTION_EDGECOLOR_MAGENTA,
        CAPTION_EDGECOLOR_CYAN,
        CAPTION_EDGECOLOR_WHITE,
        CAPTION_EDGECOLOR_DEFAULT = 0xFF,
    } EN_CAPTION_EDGE_COLOR;

    ///CC program information foreground color
    typedef enum
    {
        CAPTION_FG_BLACK,
        CAPTION_FG_RED,
        CAPTION_FG_GREEN,
        CAPTION_FG_YELLOW,
        CAPTION_FG_BLUE,
        CAPTION_FG_MAGENTA,
        CAPTION_FG_CYAN,
        CAPTION_FG_WHITE,
        CAPTION_FGCOLOR_DEFAULT = 0xFF,
    } EN_CAPTION_FG_COLOR;

    ///CC program information background color
    typedef enum
    {
        CAPTION_BG_BLACK,
        CAPTION_BG_RED,
        CAPTION_BG_GREEN,
        CAPTION_BG_YELLOW,
        CAPTION_BG_BLUE,
        CAPTION_BG_MAGENTA,
        CAPTION_BG_CYAN,
        CAPTION_BG_WHITE,
        CAPTION_BGCOLOR_DEFAULT = 0xFF,
    } EN_CAPTION_BG_COLOR;

    typedef enum
    {
        CAPTION_WINDOW_BLACK,
        CAPTION_WINDOW_RED,
        CAPTION_WINDOW_GREEN,
        CAPTION_WINDOW_YELLOW,
        CAPTION_WINDOW_BLUE,
        CAPTION_WINDOW_MAGENTA,
        CAPTION_WINDOW_CYAN,
        CAPTION_WINDOW_WHITE,
        CAPTION_WINDOWCOLOR_DEFAULT = 0xFF,
    } EN_CAPTION_WINDOW_COLOR;

    ///CC program information foreground opacity
    typedef enum
    {
        CAPTION_FG_SOLID,
        CAPTION_FG_FLASHING,
        CAPTION_FG_TRANSLUCENT,
        CAPTION_FG_TRANSPARENT,
        CAPTION_FGOPACITY_DEFAULT = 0xFF,
    } EN_CAPTION_FG_OPACITY;

    ///CC current program information background opacity
    typedef enum
    {
        CAPTION_BG_SOLID,
        CAPTION_BG_FLASHING,
        CAPTION_BG_TRANSLUCENT,
        CAPTION_BG_TRANSPARENT,
        CAPTION_BGOPACITY_DEFAULT = 0xFF,
    } EN_CAPTION_BG_OPACITY;

    typedef enum
    {
        CAPTION_WINDOW_SOLID,
        CAPTION_WINDOW_FLASHING,
        CAPTION_WINDOW_TRANSLUCENT,
        CAPTION_WINDOW_TRANSPARENT,
        CAPTION_WINDOWOPACITY_DEFAULT = 0xFF,
    } EN_CAPTION_WINDOW_OPACITY;

    ///CC program information CC font style
    typedef enum
    {
        CAPTION_FONTSTYLE_0,
        CAPTION_FONTSTYLE_1,
        CAPTION_FONTSTYLE_2,
        CAPTION_FONTSTYLE_3,
        CAPTION_FONTSTYLE_4,
        CAPTION_FONTSTYLE_5,
        CAPTION_FONTSTYLE_6,
        CAPTION_FONTSTYLE_7,
        CAPTION_FONTSTYLE_DEFAULT = 0xFF,
    } EN_CAPTION_FONTSTYLE;
    /* For OSD UI Setting */

    /* For Inner CC708 MinColorPlate */
    ///CC program information default opacity
    typedef enum
    {
        DEFAULT_OPACITY_SOLID,
        DEFAULT_OPACITY_FLASHING,
        DEFAULT_OPACITY_TRANSLUCENT,
        DEFAULT_OPACITY_TRANSPARENT,
    } EN_DEFAULT_OPACITY;

    ///CC program information CC Italics Attr
    typedef enum
    {
        CAPTION_ITALICS_NONE,
        CAPTION_ITALICS_ENABLE,
        CAPTION_ITALICS_DEFAULT,
    } EN_CAPTION_ITALICS;

    ///CC program information CC Underline Attr
    typedef enum
    {
        CAPTION_UNDERLINE_NONE,
        CAPTION_UNDERLINE_ENABLE,
        CAPTION_UNDERLINE_DEFAULT,
    } EN_CAPTION_UNDERLINE;
    /*****************************************************************/
    /* Structure Definition */
    ///CC current program information of setting
     ///  the struct of queue element
    typedef struct _PTSQueueElement
    {
        /// the pointer of the queue element buffer
        CC_U8 *pu8Buf;
        /// the queue length, the maximum PES length is 64k
        CC_U16 u16Len;
        /// the queue PTS
        CC_U32 u32PTS;
    } QueueElement;

    typedef enum
    {
        E_DTV_CAPTION,
        E_RVU_CAPTION,
    } EN_DIGITAL_CAPTION_TYPE;

    /* For caption window position setting */
    typedef enum
    {
        CAPTION_WIN_NONE,
        CAPTION_WIN_TOP,
        CAPTION_WIN_MIDDLE,
        CAPTION_WIN_BOTTOM,
    }EN_CAPTION_WIN_POSITION;

    typedef enum
    {
        CAPTION_WIN_GRID_NONE,
        CAPTION_WIN_GRID_0,    //Left Top
        CAPTION_WIN_GRID_1,    //Middle Top
        CAPTION_WIN_GRID_2,    //Right Top
        CAPTION_WIN_GRID_3,    //Left Middle
        CAPTION_WIN_GRID_4,    //Middle Middle
        CAPTION_WIN_GRID_5,    //Right Middle
        CAPTION_WIN_GRID_6,    //Left Bottom
        CAPTION_WIN_GRID_7,    //Middle Bottom
        CAPTION_WIN_GRID_8,    //Right Bottom
    }EN_CAPTION_WIN_GRID;

    /// Define RVU trick mode type.
    typedef enum
    {
        /// RVU trick mode is normal.
        E_RVU_TRICKMODE_NORMAL = 0,
        /// RVU trick mode is pause.
        E_RVU_TRICKMODE_PAUSE,
        /// RVU trick mode is forward slow motion.
        E_RVU_TRICKMODE_SLOW_FORWARD,
        /// RVU trick mode is fast forward.
        E_RVU_TRICKMODE_FAST_FORWARD,
        /// RVU trick mode is fast backward.
        E_RVU_TRICKMODE_FAST_BACKWARD,
        /// RVU trick mode is step by step (not support now).
        E_RVU_TRICKMODE_STEP,
        /// RVU trick mode is none.
        E_RVU_TRICKMODE_NOT_SUPPORT
    } EN_RVU_TRICKMODE;


    typedef struct _CaptionSettingOption_Type
    {
        ///CC current program information foreground color
        CC_U8 u8CSOptionFGColor;
        ///CC current program information background color
        CC_U8 u8CSOptionBGColor;
        ///CC current program information window color
        CC_U8 u8CSOptionWindowColor;
        ///CC current program information foreground opacity
        CC_U8 u8CSOptionFGOpacity;
        ///CC current program information background opacity
        CC_U8 u8CSOptionBGOpacity;
        ///CC current program information window opacity
        CC_U8 u8CSOptionWindowOpacity;
        ///CC current program information font size
        CC_U8 u8CSFontSize;
        ///CC current program information font style
        CC_U8 u8CSFontStyle;
        ///CC current program information edge style
        CC_U8 u8CSOptionEdgeStyle;
        ///CC current program information edge color
        CC_U8 u8CSOptionEdgeColor;
        ///CC current program information italics attr
        CC_U8 u8CSOptionItalicsAttr;
        ///CC current program information underline attr
        CC_U8 u8CSOptionUnderlineAttr;
    } stCaptionSettingOption_Type;

    ///CC current program information mode option for UI
    typedef struct _CaptionSetting_Type
    {
        CC_U16 CaptionSettingCS;// check sum <<checksum should be put at top of the struct, do not move it to other place>>
        ///CC current program information DTV service mode
        CC_U8 u8CaptionServiceModeDTV; // CC Mode for UI
        ///CC current program information ATV service mode
        CC_U8 u8CaptionServiceModeATV; // CC Mode for UI
        ///CC current program information service mode
        CC_U8 u8CaptionServiceMode;  // CC Service Mode for CC Lib
        ///CC current program information set by menu
        stCaptionSettingOption_Type astCaptionOptionMenu;    // For CC UI
        ///CC current program information set by custom
        stCaptionSettingOption_Type astCaptionOptionCustom;  // For CC Lib
        ///CC current program information CC function is OFF or On
        CC_U8 u8CCMode;
        ///CC current program information CS Option Mode: by stream or by custom setting
        CC_U8 u8CSOptionMode;
        ///CC current preview mode;
        EN_CAPTION_PREVIEW_MODE enCCPreviewMode;
        ///CS Window Position: TOP/MIDDLE/BOTTOM
        CC_U8 u8CSWinPosition;
        ///CS Window Grid: Left Top/Middle Top/Right Top/Left Middle/Middle Middle/Right Middle/Left Bottom/Middle Bottom/Right Bottom
        CC_U8 u8CSWinGrid;
    } stCaptionSetting_Type;

    ///CC current program information of variables
    typedef struct _CaptionSettingOptionVariables
    {
        ///CC current program information ATV CC window left top corner x pos
        CC_U32 u32ATV_Axis_xpos;
        ///CC current program information ATV CC window left top corner y pos
        CC_U32 u32ATV_Axis_ypos;
        ///CC current program information DTV CC window left top corner x pos
        CC_U32 u32DTV_Axis_xpos;
        ///CC current program information DTV CC window left top corner y pos
        CC_U32 u32DTV_Axis_ypos;
        ///CC current program information CC 608 row number (Text mode)
        CC_U32 u32Text_608_rowno;
        ///CC current program information CC 608 Text window y pos (Text mode)
        CC_U32 u32Text_608_ypos;
         ///CC current program information CC 608 caption time out time
        CC_U32 u32Timeout_608_capiton;
         ///CC current program information CC 608 Text time out time
        CC_U32 u32Timeout_608_text;
         ///CC current program information CC 708 caption time out time
        CC_U32 u32Timeout_708_caption;
          ///CC current program information brazil caption time out time
        CC_U32 u32Timeout_DTV_caption;//for Brazil CC Timeout
        ///CC current program information Vchip time out time
        CC_U32 u32Timeout_Vchip;
        ///CC current program information CC font
        CC_U32 u32Cc_lang;
        ///CC current program information CC 608 Font top space
        CC_U32 u32Row_608_toprsvheight;
        ///CC current program information CC 608 Font bottom space
        CC_U32 u32Row_608_btmrsvheight;
        ///CC current program information CC 708 Font top space
        CC_U32 u32Row_708_toprsvheight;
        ///CC current program information CC 708 Font bottom space
        CC_U32 u32Row_708_btmrsvheight;
        ///CC set roll up smoothly
        CC_U32 u32CC_608_ScrollStep;
        ///CC current program information brazil CC font top height
        CC_U8 u8Row_brazil_toprsvheight;
        ///CC current program information brazil CC font bottom height
        CC_U8 u8Row_brazil_btmrsvheight;
        ///CC current program information brazil CC window left top corner x pos
        CC_S32 s32XPos_offset;
        ///CC current program information brazil CC window left top corner y pos
        CC_S32 s32YPos_offset;
        ///CC current program information brazil CC enable SVS
        CC_U8  u8CCEnableSVS;
        ///CC current program information brazil CC enable SHS
        CC_U8  u8CCEnableSHS;
        CC_U8  u8Reserved[3];
    } stCaptionSettingVariables;

    ///CC program information of preview
    typedef struct _CaptionSettingPreviewType
    {
        ///CC program information preview surface
        //IDirectFBSurface *pSur;
        void *pSur;
        ///CC program information preview surface for blink
        void *pSurBlink;
        ///CC program information preview option type
        stCaptionSettingOption_Type CCOpt;
        ///CC program information preview Text
        CC_U8 *pCCText;
        ///CC program information preview Text lengh
        CC_U8 CCTextLen;
        ///CC program information preview window x pos
        CC_U16 u16PosX;
        ///CC program information preview window y pos
        CC_U16 u16PosY;
    } stCaptionSettingPreviewType;

    ///CC window's information
    typedef struct
    {
        ///CC window x pos
        CC_U32 x;
        ///CC window y pos
        CC_U32 y;
        ///CC window width
        CC_U32 w;
        ///CC window height
        CC_U32 h;

    } CC_WindowsInfo;

    typedef struct _IntCustomerVariables
    {
        CC_U16 u16Axis_XPos;
        CC_U16 u16Axis_YPos;
        CC_U16 u16STA_Width;
        CC_U16 u16STA_Height;
        CC_U16 u16STA_SXLoc;
        CC_U16 u16STA_SYLoc;

        CC_U8 u8CCRowWidth;
        CC_U8 u8CCRowHeight;

        CC_U8 u8CCFontWidth;
        CC_U8 u8CCFontHeight;

        CC_U8 u8Row_TopRsvHeight;
        CC_U8 u8Row_BtmRsvHeight;

        CC_U8 u8Text_RowNo;
        CC_U8 u8Text_YPos;

        CC_U8 u8WinAnkor_GridWidthMax;
        CC_U8 u8WinAnkor_GridHeightMax;
        CC_U8 u8WinAnkor_GridWidthSpace;
        CC_U8 u8WinAnkor_GridHeightSpace;
        CC_U8 u8MaxColNo;
        CC_U8 u8MaxColPlus;

        CC_U8 cc_lang;
        CC_U8 cc_lang_bak;
        CC_U8 cc_lang_korean_bak;
        CC_U8 u8CCType_Option;

        CC_U8 u8CCEnableSVS;
        CC_U8 u8CCEnableSHS;
        CC_U8 u8Reserved[3];
    } stIntCustomerVariables;

    typedef struct _IntMemoryAddr
    {
        CC_U32 u32CCCacheAddr;
        CC_U32 u32CCCacheSize;
        CC_U32 u32CC608CacheAddr;
        CC_U32 u32CC608CacheSize;

        CC_U8  *pstCC608_Cntl;
        CC_U8  *Service_Buffer;
        CC_U8  *CCBBlockInfo;
        CC_U8  *cc608DispBuff;
#if KOREAN_CC_ENABLE
        CC_U8  *cc608DispBuffa;
#endif
        CC_U8  *pstCC708_Cntl;
        CC_U8  *pstCC708_Trp;
        CC_U8  *CCTextBuf;

        CC_U8 u8Reserved[4];
    } stIntMemoryAddr;

    // Add CC ATTR Default Option in the Menu, Flag ==1 --> From TRP
    typedef struct _CCAttrType
    {
        CC_U8 fCCAttr_WinColorTransparent_WhenFlash_Flag : 1;
        CC_U8 fCCAttrEnable24Fonts : 1;
        CC_U8 fCCAttrEnableGopZoom : 1;
        CC_U8 fCCAttrEnableAutoSTAbyVideoFmt :  1;
        CC_U8 fCCAttr_EnableFontEdge : 1;
        CC_U8 fCCAttr_EnableRrvBlK : 1;
        CC_U8 fCCAttr_EnableWindowOptionSetting: 1;
        CC_U8 fCCAttr_FGColor_FromTRP_Flag : 1;  //total 1byte

        CC_U8 fCCAttr_BGColor_FromTRP_Flag : 1;
        CC_U8 fCCAttr_WindowColor_FromTRP_Flag: 1;
        CC_U8 fCCAttr_FGOpacity_FromTRP_Flag : 1;
        CC_U8 fCCAttr_BGOpacity_FromTRP_Flag : 1;
        CC_U8 fCCAttr_WindowOpacity_FromTRP_Flag: 1;
        CC_U8 fCCAttr_FontStyle_FromTRP_Flag : 1;
        CC_U8 fCCAttr_FontSize_FromTRP_Flag : 1;
        CC_U8 fCCAttr_EdgeStyle_FromTRP_Flag : 1;  //total 1byte

        CC_U8 fCCAttr_EdgeColor_FromTRP_Flag : 1;
        CC_U8 fCCAttr_EdgeOpacity_NoTransparent_Flag : 1;
        CC_U8 fCCAttr_Parity_Error_Solid_Block_Flag:   1;
        CC_U8 fCCAttr_Packet_Dump_Flag: 1;
        CC_U8 fCCAttr_Suport_Korean_Flag:   1;
        CC_U8 fCCAttr_Wansung_Code_Flag:   1;
        CC_U8 fCCAttr_EnableSemiTransparentOnTextMode_Flag : 1;
        CC_U8 fCCAttr_Map_UIoption_Flag : 1;  //total 1byte

        CC_U8 fCCAttr_Font_Indention_Flag : 1;
        CC_U8 fCCAttr_GOP_Use_FBPool2 : 1;
        CC_U8 fCCAttr_Wait_GFX_Flush_Queue: 1;
        CC_U8 fCCAttr_Support_Border_Opacity: 1;
        CC_U8 fCCAttr_DLW_Call_GEngine: 1;
        CC_U8 fCCAttr_Show_Window_Has_Text: 1;
        CC_U8 fCCAttr_Enable_Roll_Smoothly: 1;
        CC_U8 fCCAttr_Support_Deep_Color: 1;  //total 1byte

        CC_U8 fCCAttr_Italics_FromTRP_Flag : 1;
        CC_U8 fCCAttr_Underline_FromTRP_Flag : 1;
        CC_U8 fCCAttr_Check_Command_Length: 1;
        CC_U8 fCCAttr_NotStandard_Stream_Adaptation: 1;
        CC_U8 fCCAttr_WinBGColor_Effectby_BGColor_Flag : 1;
        CC_U8 fCCAttr_WinBGOpacity_Effectby_BGOpacity_Flag : 1;
        CC_U8 fCCAttr_Support_ATVAttrSet_Flag : 1;
        CC_U8 fCCAttr_Support_EdgeAttrSet_Flag : 1;  //total 1byte

        CC_U8 fCCAttr_Support_WindowBorder_Flag :1;
        CC_U8 fCCAttr_Support_OtherLanguage_Flag :1;
        CC_U8 fCCAttr_Expletive_Show_Flag :1;
        CC_U8 fCCAttr_Support_WordWrap_Flag: 1;
        CC_U8 fCCAttrRSV: 4;  //total 1byte
    } stCCAttrType;

    ///  the struct of cc misc info
    typedef struct
    {
        /// the callback for notifying that CC has updated
        void (*NotifyDFBUpdate)(void);
    } ClosedCaption_Misc;

    /// the dfb color mode
    typedef enum
    {
        CAPTION_COLORMODE_I8,
        CAPTION_COLORMODE_ARGB4444,
        CAPTION_COLORMODE_ARGB8888,
    }EN_CAPTION_COLORMODE;
    /***************************************************************************************/
    /* Variables                                                                           */
    /***************************************************************************************/
    extern CC_BOOL g_bDumpDbgMsg;
    extern EN_CAPTION_COLORMODE g_enColorMode;


    /***************************************************************************************/
    /* Functions                                                                           */
    /***************************************************************************************/


#ifdef __cplusplus
}
#endif

#endif
///*** please do not remove change list tag ***///
///***$Change: 1504452 $***///
