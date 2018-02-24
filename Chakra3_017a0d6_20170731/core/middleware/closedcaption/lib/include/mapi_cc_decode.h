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

#ifndef MAPI_CC_DECODE_H
#define MAPI_CC_DECODE_H

/***************************************************************************************/
/*                 Header Files                                                        */
/***************************************************************************************/
#include "mapi_cc_type.h"
#include "mapi_cc_interface.h"
#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************/
/* Define */
/*****************************************************************/
#define _CC608_REDRAW_BGCOLOR_          0       // for Re-Draw Background Color

/* CC708 RESERVED BLOCK Define */
#define RSVBLK_ROWMAX           64

//CC program information CC 608 row/col number
#if KOREAN_CC_ENABLE
#define CC608_MAX_ROW_NUMBER        15
#define CC608_MAX_COL_NUMBER_EIA608    36//34//46  // 40+6
#define CC608_MAX_COL_NUMBER_KOREAN   46//34//46  // 40+6
#else
/* CC608 Definition */
#define CC_MAX_ROW_NUMBER           15
#define CC_MAX_COL_NUMBER           34
#define CC_MIN_ROW_NUMBER           0
#define CC_MIN_COL_NUMBER           0
#define CC608_ROW_BUFF_SIZE         (CC_MAX_COL_NUMBER+2)

//CC program information CC 608 font start col
#define CC_START_COLLOC             1
//CC program information CC 608 font end col
#define CC_END_COLLOC               32
#endif
/*****************************************************************/
/* Enum */
/*****************************************************************/
typedef enum
{
    KOREAN_CC_ROW_NUMBER = 0,
    KOREAN_CC_COL_NUMBER,
}EN_CC_DECODEINFO;

/*****************************************************************/
/* Structure */
/*****************************************************************/

 /* Structure Definition */
typedef struct
{
    CC_FONTHANDLE fHandle;         ///< Font handle
} CC_FONT;

typedef struct _CC708_ReservedBlock
{
    CC_U8 DoneFlag : 1;
    CC_U8 HeadLoc : 6;
    CC_U8 TailLoc : 6;
    CC_U8 Rsv : 3;
} CC708_ReservedBlock;

typedef struct _CC608_CodeSyntax_CntlAttr
{
    /* Whole System */
    CC_U16 u16SysSettingFlag;        // System Attr

    CC_U8 u8WinText_CurRowNo;
    CC_U8 u8WinText_CurColNo;
    CC_U8 u8WinText_RowTotalNo;
    CC_U8 u8WinText_BakRowNo;
    CC_U8 u8WinText_RowRUxNo;
    CC_U8 u8WinText_LastRowRUxNo;
    CC_U8 u8WinText_WinLocY;

    CC_U8 u8ScrollingNo;            //scroll record
    CC_U8 u8TextStartScroll;        // indicate if the text mode should start the scrolling

    /* Text Part */
    #if KOREAN_CC_ENABLE
    CC_U32 u32TextAttrFlag;        // Text Attr
    #else
    CC_U16 u16TextAttrFlag;        // Text Attr
    #endif
    CC_U8 u8FontTypeFlag;

    /* FB & GOP Control */
    CC_U16 u16WinAttr_ClipHeight;
    CC_U16 u16WinAttr_ClipWidth;
    CC_U16 u16WinAttr_Loc_SX;
    CC_U16 u16WinAttr_Loc_SY;

    /*  */
    #if (_CC608_REDRAW_BGCOLOR_)
    CC_U8 u8TextBakBGColor;
    #endif

} CC608_CodeSyntax_CntlAttr;

#if KOREAN_CC_ENABLE
typedef struct _CC608_Display_Buffer
{
    CC_U8  RollUpBaseRow;
    CC_U32 RollUpTextAttr;
    CC_U32 *RowDisplayBuffer;
    CC_U32 DisplayBuffer0[CC608_MAX_ROW_NUMBER][CC608_MAX_COL_NUMBER_EIA608]; // last word of each row indicate the lastest draw time
    CC_U32 DisplayBuffer1[CC608_MAX_ROW_NUMBER][CC608_MAX_COL_NUMBER_EIA608];
    CC_U8  DisplayedRowNum;
    CC_U8  NonDisplayedRowNum;
    CC_U32 *NonDisplayedBuffer;
    CC_U8  NonDisplayedGwin;
    CC_U32 *DisplayedBuffer;
    CC_U8  DisplayedGwin;
    CC_U8  DisplayedFB;
    CC_U8  WinMode;
} CC608_Display_Buffer;
#else
typedef struct _CC608_Display_Buffer
{
    CC_U8  RollUpBaseRow;
    CC_U16 RollUpTextAttr;
    CC_U16 *RowDisplayBuffer;
    CC_U16 DisplayBuffer0[CC608_ROW_BUFF_SIZE];
    CC_U16 DisplayBuffer1[CC608_ROW_BUFF_SIZE];
    CC_U8  DisplayedRowNum;
    CC_U8  NonDisplayedRowNum;
    CC_U16 *NonDisplayedBuffer;
    CC_U8  NonDisplayedGwin;
    CC_U16 *DisplayedBuffer;
    CC_U8  DisplayedGwin;
    CC_U8  DisplayedFB;
    CC_U8  WinMode;
    CC_U8  DisplayedMappedBufNum;
    CC_U8  NonDisplayedMappedBufNum;
} CC608_Display_Buffer;
#endif

typedef struct _CC708_Grph_CntlAttr
{
    // System Control Part
    //CC_U8 u8CreateWinID_Flag;    // for create Window
    CC_U8 u8GWinIDVisible;    // for TGW , DLW
    //CC_U8 u8WID_AvailData_Flag;        // o-> No Data; 1-> have Data
  //  CC_U8 u8GWinID;        // for GOP GWIN ID [0 -3]
    CC_U8 u8CaptionWinID;        // for Caption Window NO [0 - 7]         u8FrameID
    CC_U8 u8Priority;

    /* Frame Buffer */
    CC_U8 u8WinText_Row;
    CC_U8 u8WinText_Pivot;
    CC_U8 u8WinText_Column;
    CC_U8 u8WinText_RowMax;
    CC_U8 u8WinText_ColumnMax;
    CC_U8 u8WinText_DispRowMax;
    //CC_U8 u8WinText_RowOffset;

    CC_U16 u16ClipWindow_Width;
    CC_U16 u16ClipWindow_Height;

    /* GOP Part */
    CC_U16 u16WinAttr_GWIN_Loc_SX;
    CC_U16 u16WinAttr_GWIN_Loc_SY;
    CC_U16 u16WinAttr_GWIN_Loc_EX;
    CC_U16 u16WinAttr_GWIN_Loc_EY;

    /**/
    CC_U8 u8WinAttr_RowMax;
    CC_U8 u8WinAttr_ColumnMax;

    CC_U16 u16WinAttr_GOPRow;
    CC_U16 u16WinAttr_GOPColumn;

    /* Frame Buffer & GOP Part */
    CC_U16 u16ScrollingTimes;

    // Window Attr part
    //CC_U8 u8WinAttr_WID;    // This version doesn't support !
    CC_U8 u8WinAttr_AnchorPoint;
    CC_U8 u8WinAttr_AnchorV;
    CC_U8 u8WinAttr_AnchorH;
    CC_U8 u8WinAttr_RowLock;
    CC_U8 u8WinAttr_ColumnLock;
    //CC_U8 u8WinAttr_WindowStyleID;    // This version doesn't support !
    //CC_U8 u8WinAttr_PenStyleID;        // This version doesn't support !
    CC_U8 u8WinAttr_TextJustifyType;        //Supporting Left, Right, Center (3 Types)
    CC_U8 u8WinAttr_TextPrintDirection;
    CC_U8 u8WinAttr_ScrollDirection;
    CC_U8 u8WinAttr_DispEffect;
    CC_U8 u8WinAttr_EffectDirection;
    CC_U8 u8WinAttr_EffectSpeed;
    CC_U8 u8WinAttr_WinFillColorIdx;
    CC_U8 u8WinAttr_WinOpacity;
    CC_U8 u8WinAttr_WinBorderType;
    CC_U8 u8WinAttr_WinBorderColor;

    // Pen Attr Part
    CC_U8 u8PenAttr_PenSize;
    CC_U8 u8PenAttr_FontStyle;
    CC_U8 u8PenAttr_TextTag;
    //CC_U8 u8PenAttr_SubScript;        // This version doesn't support !    // Only Normal
    CC_U8 u8PenAttr_Italics;
    CC_U8 u8PenAttr_Underline;
    CC_U8 u8PenAttr_EdgeStyle;

    CC_U8 u8PenAttr_TextFGColorIndex;
    CC_U8 u8PenAttr_TextFGOpacity;
    CC_U8 u8PenAttr_TextBGColorIndex;
    CC_U8 u8PenAttr_TextBGOpacity;
    CC_U8 u8PenAttr_TextEdgeColorIndex;

    // For GOP scrolling windos
    CC_U16 rolX;
    CC_U16 rolY;

    CC_U8 u8P16CharExisted;
    CC_U8 u8P16CommandExisted;

    // Reserved Block
    CC708_ReservedBlock RSVBLK[RSVBLK_ROWMAX];

    // Invisible draw flag
    //CC_U8 u8NeedDraw;
    // CC Font handle
    CC_U8 u8FontHandle;
    CC_U8 u8WinAttr_WordWrapping : 1;
    CC_U8 u8RSV: 7;
}CC708_Grph_CntlAttr;

typedef struct _CC708_CodeSyntax_TRPAttr
{
    /* SPA CMD */
    CC_U8    u8SPAPenSize :2;
    CC_U8    u8SPAFontStyle :3;
    CC_U8    u8SPATextTag :4;
    CC_U8    u8SPAOffset :2;
    CC_U8    u8SPAItalics :1;
    CC_U8    u8SPAUnderLine :1;
    CC_U8    u8SPAEdgeType :3;

    /* SPC CMD */
    CC_U8    u8SPCFGColor :6;
    CC_U8    u8SPCFGOpacity :2;
    CC_U8    u8SPCBGColor :6;
    CC_U8    u8SPCBGOpacity :2;
    CC_U8    u8SPCEdgeColor :6;

    /* SPL CMD */
    CC_U8    u8SPLRow;
    CC_U8    u8SPLColumn;

    /* SWA CMD */
    CC_U8    u8SWAJustifyType :2;
    CC_U8    u8SWAPrintDirection :2;
    CC_U8    u8SWAScrollDirection :2;
    CC_U8    u8SWAWordWrap :1;
    CC_U8    u8SWADisplayEffect :2;
    CC_U8    u8SWAEffectDirection :2;
    CC_U8    u8SWAEffectSpeed :4;
    CC_U8    u8SWAFillColor :6;
    CC_U8    u8SWAFillOpacity :2;
    CC_U8    u8SWABorderType :3;
    CC_U8    u8SWABorderColor :6;

    /* DFW CMD */
    CC_U8    u8DFWWID;
    CC_U8    u8DFWPriority;
    CC_U8    u8DFWAnchorPoint;
    CC_U8    u8DFWRelativePositioning;
    CC_U8    u8DFWAnchorVertical;
    CC_U8    u8DFWAnchorHorizontal;
    CC_U8    u8DFWRowCount;
    CC_U8    u8DFWColumnCount;
    CC_U8    u8DFWRowLock;
    CC_U8    u8DFWColumnLock;
    CC_U8    u8DFWVisible;
    CC_U8    u8DFWWindowStyleID;
    CC_U8    u8DFWPenStyleID;

} CC708_CodeSyntax_TRPAttr;

/***************************************************************************************/
/* Data structure                                                                      */
/***************************************************************************************/
typedef unsigned char (*MIGetDataFromVBIFifoPacket)(unsigned char *pFifo);
/// Internal customer functions
typedef struct
{
   void (*Open)(void);
   void (*Close)(void);
   void (*Initial)(void);
   void (*InitVar)(stIntMemoryAddr *pMem, stIntCustomerVariables *pVar, stCCAttrType *pAttr, stCaptionSetting_Type *pType);
   void (*Reset708LocationVar)(stIntCustomerVariables *pVar);
   void (*GetDecodeInfo)(EN_CC_DECODEINFO enInfo, CC_U32 *u32value);
   void (*SetFontHandle)(CC_FONT * stFont);
   void (*CC608ParserInit)(void);
   void (*Decode608)(void);
   void (*Decode708)(CC_BOOL fEnableCCFunc);
   void (*DecodeVChip)(void);
   void (*DecodeRemData)(CC_BOOL fEnableCCFunc);
   CC_BOOL (*Check608TimeOut)(void);
   CC_BOOL (*Check708TimeOut)(void);
   void (*GetInputData)(CC_U8 *pData, CC_U16 len);
   void (*SetPalette)(CC_U8 id, CC_BOOL bDeepColor);
   CC_U8 (*Check708Type)(void);
   void (*Reset708CtrlData)(void);
   void (*Store708Database)(CC_U8 *srcaddr, CC_U8 u8WinNth);
   void (*AnalogCC_Parser)(void);
   void (*Timeout_Threshold)(CC_U32 u32Caption, CC_U32 u32Text);
   void (*Timeout_Threshold608)(CC_U32 u32Caption, CC_U32 u32Text);
   void (*Timeout_Threshold708)(CC_U32 u32Caption);
   void (*KoreanCCEnv)(CC_U8 val);
   CC_U8 (*CC608TypeGet)(void);
   void (*SetCC608ScrollStep)(CC_U8 u8CC608ScrollStep);
   void (*PassCallbackAddr)(MIGetDataFromVBIFifoPacket pfEventCallback);
} CC_DecoderService;


/***************************************************************************************/
/* Variables                                                                           */
/***************************************************************************************/
extern const CC_DecoderService CC_DecoderFuns;

/***************************************************************************************/
/* Functions                                                                           */
/***************************************************************************************/

#ifdef __cplusplus
  }
#endif

#endif
///*** please do not remove change list tag ***///
///***$Change: 1435801 $***///
