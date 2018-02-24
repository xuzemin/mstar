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

#ifndef MAPI_CC_BRAZIL_DECODE_H
#define MAPI_CC_BRAZIL_DECODE_H
//#include "mapi_cc_brazil_private.h"//bruce.gao@0224
#include "mapi_cc_interface.h"//bruce.gao@0302
//#include "mapi_cc_interface.h"
#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************/
/* Define */

/*****************************************************************/


/*****************************************************************/
/* Structure */

/*****************************************************************/


/*****************************************************************/
/* Variables */

/*****************************************************************/
#if 0
extern CC_U8 int_cc_lang, int_cc_lang_bak, int_cc_lang_korean_bak;

/* Common Variables */
extern CC_U8  int_g_u8CCFontWidth;
extern CC_U8  int_g_u8CCFontHeight;
extern CC_U8  int_g_u8CCRowWidth;
extern CC_U8  int_g_u8CCRowHeight;
extern MAPI_U16 int_g_u16Axis_XPos;
extern MAPI_U16 int_g_u16Axis_YPos;
extern CC_U8  int_g_u8Scale_HorFactor, int_g_u8Scale_VerFactor;

/* CC608 Variables */
extern CC_U8 int_g_u8Row_TopRsvHeight;
extern CC_U8 int_g_u8Row_BtmRsvHeight;
extern CC_U8 int_g_u8Text_RowNo;
extern CC_U8 int_g_u8Text_YPos;
extern CC_U8 int_g_u8Priority;

/* CC708 Variables */
extern CC_U8 int_g_u8WinAnkor_GridWidthMax, int_g_u8WinAnkor_GridHeightMax;
extern CC_U8 int_g_u8WinAnkor_GridWidthSpace, int_g_u8WinAnkor_GridHeightSpace;
extern CC_U8 int_g_u8MaxColNo, int_g_u8MaxColPlus;
extern MAPI_U16 int_g_u16STA_SXLoc, int_g_u16STA_SYLoc;
extern MAPI_U16 int_g_u16STA_Width, int_g_u16STA_Height;
extern CC_U8 int_g_u8CC708_RsvBlk_ColNo;

extern stCCAttrType int_fCCAttrFlag;
extern stCaptionSetting_Type int_stCCOSDSetting;
extern CC_U8 *CC_Service_Buffer;

extern stIntMemoryAddr int_intMemoryAddr;
extern stIntControlVariables int_intControlVariables;

extern BlinkBlock_Info *int_CCBBlockInfo;
extern CC_U8 *int_Service_Buffer;

//
extern CC_U8 int_u8CCType_Option;
extern CC_U8 u8ServiceRemain_Index;
extern CC_U8 u8ServiceDelay_Index;

//
extern CC_U8 int_u8CCPR_Temp1, int_u8CCPR_Temp2, int_u8CCPR_Temp3, int_u8CCPR_Temp4;
extern MAPI_U16 int_u16CCPR_Temp1, int_u16CCPR_Temp2, int_u16CCPR_Temp3;
extern CC_U32 int_u32CCPR_Temp1, int_u32CCPR_Temp2, int_u32CCPR_Temp3;

//
extern CC_U8 g_u8CC608_GWID;
extern CC_U32 g_u32CCProtectionTime;
extern CC_U8 g_u8CCProtection;

extern CC_U8  volatile int_CC_Packet_Buffer[SIZE_OF_PACKET_BUFFER];
extern CC_U32 int_CC_EachPacketBuffer_Size;

extern MAPI_BYTE int_fCC608Using157;

/*****************************************************************/
/* Common Function List */

/*****************************************************************/

// common
//-------------------------------------------------------------------------------------------------
/// API for EIA708 CC Service Parser.
/// @param  fEnableCCFunc           \b IN: Enable parser flag
/// @return None
//-------------------------------------------------------------------------------------------------
extern void mapi_CC708_Service_Parser(MAPI_BOOL fEnableCCFunc);

//-------------------------------------------------------------------------------------------------
/// API for EIA608 CC Service Parser.
/// @param  None
/// @return None
//-------------------------------------------------------------------------------------------------
extern void mapi_CC608_Service_Parser(void);

//-------------------------------------------------------------------------------------------------
/// API for CC608 VCHIP pre-parser.
/// @param  None
/// @return None
//-------------------------------------------------------------------------------------------------
extern void mapi_CC608_VChip_PreParser(void);

// 708
//-------------------------------------------------------------------------------------------------
/// API for clear One line of display buffer for EIA708.
/// @param line                     \b IN: Line Number
/// @param fIsRowFlag               \b IN: 0: Clear column  1: clear row
/// @return None
//-------------------------------------------------------------------------------------------------
extern void mapi_CC708_ClearOneLine(CC_U8 line, MAPI_BOOL fIsRowFlag);

//-------------------------------------------------------------------------------------------------
/// API for Rolling one Line for EIA708.
/// @param winId                     \b IN: GWIN ID
/// @param dir                       \b IN: Roll direction
/// @param column                    \b IN: Roll column
/// @return None
//-------------------------------------------------------------------------------------------------
extern void mapi_CC708_RollOneLine(CC_U8 winId, EN_CC_SCROLL_TYPE dir, CC_U8 column);

//-------------------------------------------------------------------------------------------------
/// API for clear display buffer for EIA708.
/// @param  fEraseTextFlag           \b IN: Not used
/// @return None
//-------------------------------------------------------------------------------------------------
extern void mapi_CC708_ClearWindow(MAPI_BOOL fEraseTextFlag);

//-------------------------------------------------------------------------------------------------
/// API for Creating EIA708 Multi Window.
/// @param  None
/// @return None
//-------------------------------------------------------------------------------------------------
extern MAPI_BOOL mapi_CC708_AddDisplayWindow(void);

//-------------------------------------------------------------------------------------------------
/// API for Updating EIA708 Multi Window.
/// @param  None
/// @return None
//-------------------------------------------------------------------------------------------------
extern void mapi_CC708_UpdateDisplayWindow(void);

//-------------------------------------------------------------------------------------------------
/// API to recode enable display Gwin.
/// @param  u8win                     \b IN: GWIN ID
/// @param  bEnable                   \b IN: enable flag
/// @return None
//-------------------------------------------------------------------------------------------------
extern void mapi_CC_EnableDispGwin(CC_U8 u8win, MAPI_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// API to set CC 708 Font Handle.
/// @param  None
/// @return None
//-------------------------------------------------------------------------------------------------
extern void mapi_CC708_SetFontHandle(void);

//-------------------------------------------------------------------------------------------------
/// API for clear display buffer for EIA708.
/// @param fEraseTextFlag              \b IN  true/false(Draw window color only/Draw whole window)
/// @return None
//-------------------------------------------------------------------------------------------------
extern void mapi_CC708_ClearWindow_Swa(MAPI_BOOL fEraseTextFlag, CC_U8);

//-------------------------------------------------------------------------------------------------
/// API for Resetting Controlling variables.
/// @param  None
/// @return None
//-------------------------------------------------------------------------------------------------
extern void mapi_CC708_Reset_CTRL_Data(void);

//-------------------------------------------------------------------------------------------------
/// API for Loading data from EIA708 CC Database.
/// @Param dstaddr                     \b IN  Destination Address
/// @Param u8WinNth                    \b IN  CC window Selection
/// @return None
//-------------------------------------------------------------------------------------------------
extern void mapi_CC708_DataBase_Load(CC_U8 * dstaddr, CC_U8 u8WinNth);

//-------------------------------------------------------------------------------------------------
/// API for Storing data to EIA708 CC Database.
/// @Param dstaddr                     \b IN  CC DataBase Address
/// @Param u8WinNth                    \b IN  CC window Selection
/// @return None
//-------------------------------------------------------------------------------------------------
extern void mapi_CC708_DataBase_Store(CC_U8 *srcaddr, CC_U8 u8WinNth);

//-------------------------------------------------------------------------------------------------
/// API for Storing data to EIA708 CC Database.
/// @Param  stSort                      \b IN  Window priority
/// @Param  Mode                        \b IN  CC Window Visible Mode
/// @return None
//-------------------------------------------------------------------------------------------------
extern void mapi_CC708_GetGWIDPriority(CC708_WID_PRIORITY * stSort, CC_U8 Mode);

//-------------------------------------------------------------------------------------------------
/// API for Getting EIA708 Byte One Number.
/// @Param  u8Byte                      \b IN   One Bye
/// @return Number of MAPI_BYTE value is equal to one
//-------------------------------------------------------------------------------------------------
extern CC_U8 mapi_CC708_GetBitOneNo(CC_U8 u8Byte);

//-------------------------------------------------------------------------------------------------
/// API for CC708 Timeout check.
/// @Param  None
/// @return None
//-------------------------------------------------------------------------------------------------
extern MAPI_BOOL mapi_CC708_Check_TimeOut(void);

// 608
//-------------------------------------------------------------------------------------------------
/// API for Drawing a rectangle block.
/// @Param  pclrBtn                      \b IN   Point of block information
/// @return None
//-------------------------------------------------------------------------------------------------
extern void mapi_CC608_DrawBlock(CC_OSDClrBtn *pclrBtn);

//-------------------------------------------------------------------------------------------------
/// API for Drawing EIA608 One Text in Caption Mode.
/// @param  font_handle                  \b IN: Font Handle
/// @param  GwinID                       \b IN: GWIN ID
/// @param  u16ShowData                  \b OUT: One Text.
/// @return None
//-------------------------------------------------------------------------------------------------
extern void mapi_CC608_CM_DrawText(FONTHANDLE font_handle, CC_U8 GwinID, MAPI_U16 u16ShowData);

//-------------------------------------------------------------------------------------------------
/// API to calculate the number of displayable rows of the RollUp caption.
/// @Param  None
/// @return None
//-------------------------------------------------------------------------------------------------
extern CC_U8 mapi_CC608_Number_Of_Viewable_Row(void);

//-------------------------------------------------------------------------------------------------
/// API to check if the data is displayable.
/// @param  col                         \b IN: the column of position
/// @return TRUE : Success.
/// @return FALSE: Failure.
//-------------------------------------------------------------------------------------------------
extern CC_U8 mapi_CC608_Check_Data_Displayable(CC_U8 col);

//-------------------------------------------------------------------------------------------------
/// API to draw to displayed buffer to GWIN.
/// @Param  gwinId                      \b IN: Gwin ID
/// @return None
//-------------------------------------------------------------------------------------------------
extern void mapi_CC608_Display_Buffer_Draw(CC_U8 gwinId);

//-------------------------------------------------------------------------------------------------
/// API to recode enable display Gwin.
/// @param  u8win                     \b IN: GWIN ID
/// @param  bEnable                   \b IN: enable flag
/// @return None
//-------------------------------------------------------------------------------------------------
extern void mapi_CC_EnableDispGwin(CC_U8 u8win, MAPI_BOOL bEnable);

//-------------------------------------------------------------------------------------------------
/// API for CC708 Timeout check.
/// @Param  None
/// @return None
//-------------------------------------------------------------------------------------------------
extern MAPI_BOOL mapi_CC608_Check_TimeOut(void);

//-------------------------------------------------------------------------------------------------
/// API for setting current line color for EIA708.
/// @param winId                        \b IN: Gwin ID
/// @param line                         \b IN: Line Number
/// @param u8ColorIdx                   \b IN: color index
/// @return None
//-------------------------------------------------------------------------------------------------
extern void mapi_CC608_SetCurrentLineColor(CC_U8 winId, CC_U8 u8Line, CC_U8 u8ColorIdx);

//-------------------------------------------------------------------------------------------------
/// API for Rolling one Line for EIA608.
/// @param winId                     \b IN: GWIN ID
/// @param dir                       \b IN: Roll direction
/// @param u8ColorIdx                \b IN: Roll color index
/// @return None
//-------------------------------------------------------------------------------------------------
extern void mapi_CC608_RollOneLine(CC_U8 winId, EN_CC_SCROLL_TYPE dir, CC_U8 u8ColorIdx);

//-------------------------------------------------------------------------------------------------
/// API for Drawing EIA608 One Text in Text Mode.
/// @param  font_handle                  \b IN: Font Handle
/// @param  GwinID                       \b IN: GWIN ID
/// @param  u16ShowData                  \b In: One Text.
/// @return None
//-------------------------------------------------------------------------------------------------
extern void mapi_CC608_TM_DrawText(FONTHANDLE font_handle, CC_U8 GwinID, MAPI_U16 u16ShowData);

//-------------------------------------------------------------------------------------------------
/// API for clear display buffer for EIA608.
/// @param  u8GWID                       \b IN: Gwin ID
/// @param  u8colorIndex                 \b IN: Color Index
/// @return None
//-------------------------------------------------------------------------------------------------
extern void mapi_CC608_ClearDispWindow(CC_U8 u8GWID, CC_U8 u8colorIndex);

//-------------------------------------------------------------------------------------------------
/// API for Drawing EIA608 One Space.
/// @param  GwinID                       \b IN: Gwin ID
/// @param  u8ColorIdx                   \b IN: Color Index
/// @param  u8Pos                        \b IN: positon
/// @return None
//-------------------------------------------------------------------------------------------------
extern void mapi_CC608_CM_DrawColorSpace(CC_U8 GwinID, CC_U8 u8ColorIdx ,CC_U8 u8Pos);

//-------------------------------------------------------------------------------------------------
/// API for Fill Display buffer with BG Color.
/// @param  GwinID                       \b IN: Gwin ID
/// @return None
//-------------------------------------------------------------------------------------------------
extern void mapi_CC608_FillDispWindowBGColor(CC_U8 u8GWID);

//-------------------------------------------------------------------------------------------------
/// API for Delete to End CMD.
/// Erase those showed text from current cursor to end of line
/// @param  None
/// @return None
//-------------------------------------------------------------------------------------------------
extern void mapi_CC608_DER(void);

//-------------------------------------------------------------------------------------------------
/// API for Backspace CMD.
/// @param  u8GWID                       \b IN: Gwin ID
/// @return None
//-------------------------------------------------------------------------------------------------
extern void mapi_CC608_BackSpace(CC_U8 u8GWID);

//-------------------------------------------------------------------------------------------------
/// API for Initializing the CC Window Property.
/// @param  u8Mode                      \b IN: Selected CC608 Caption Mode
/// @param  u8Rows                      \b IN: Row_Max
/// @return None
//-------------------------------------------------------------------------------------------------
extern void mapi_CC608_Window_Init(CC_U8 u8Mode, CC_U8 u8Rows);

//-------------------------------------------------------------------------------------------------
/// API for Creating EIA608 Multi Window.
/// @param  None
/// @return None
//-------------------------------------------------------------------------------------------------
extern MAPI_BOOL mapi_CC608_Create_Window(void);

//-------------------------------------------------------------------------------------------------
/// API for Analog Closed Caption Protocol Parser.
/// @param  pData                       \b IN: Point of data
/// @param  len                         \b IN: decode data lengh
/// @return None
//-------------------------------------------------------------------------------------------------
extern void mapi_CC608_AnalogCC_Parser(CC_U8 *pData, CC_U32 len);
#endif
/* Structure Definition */
/*typedef struct
{
    FONTHANDLE fHandle;         ///< Font handle
} FONT;

extern FONT* CCFont;//BRUCE.GAO ADD
extern FONT Font_CC[24];*/
#define CC_BRAZIL_WIN  0//bruce.gao@0224
#define CC_TESTING_SOURCE       0   // 0: normal, 1: fixed PID by demux, 2: from file

typedef enum
{
    CC_ERRCODE_SUCCESS = 0,
    CC_ERRCODE_XDATA_ALLOCATE_FAIL,
    CC_ERRCODE_QUEUE_EMPTY

} EN_CC_ERROR_CODE;

//////////////bruce.gao@0225
 /*   typedef struct _QueueElement
    {
        CC_U8 *pu8Buf;
        MAPI_U16 u16Len;      // The maximum PES length is 64k
        CC_U32 u32PTS;
    } QueueElement;*/
///////////////
typedef struct
{
   EN_CC_ERROR_CODE (*RunCaption)(QueueElement *qe);
   CC_U32 (*GetPES)(CC_U8 *fp_In);
   void (*Init)(void);
   void (*SetPalette)(void);
   CC_BOOL (*PeekN)(QueueElement *pQue, CC_U8 u8N);
   CC_BOOL (*Pop)(QueueElement* pQue);
   CC_BOOL (*Push)(CC_U32 u32Addr, CC_U16 u16Len, CC_U32 u32PTS);
   CC_BOOL (*IsFreeRun)(CC_U32 u32STC, CC_U32 u32PTS);
   CC_U32 (*AllocateQue)(CC_U16 size);
   CC_U32 (*SetPTS)(CC_U8 *pu8bff);
   void (*InitBrazilVar)(stIntCustomerVariables *pVar);
   void (*EnableDumpRawData)(CC_BOOL bDumpRawData);
   CC_BOOL (*CheckTimeOut)(void);
   void (*SetTimeoutThreshold)(CC_U32 u32BrazilCCTimeout);
} CC_BrazilDecoder;

extern const CC_BrazilDecoder CC_BrazilDecoderFuns;//bruce.gao mark@0104

void mapi_CC_Brazil_SetPalette(void);
void mapi_CC_Brazil_Init(void);
void mapi_CC_Brazil_Close(void);
CC_U32 mapi_CC_Brazil_GetPES(CC_U8 *fp_In);
EN_CC_ERROR_CODE mapi_CC_Brazil_RunCaption(QueueElement *qe);
CC_BOOL mapi_CC_Check_Is_FreeRun(CC_U32 u32STC, CC_U32 u32PTS);
CC_BOOL mapi_CC_Brazil_Queue_Push(CC_U32 u32Addr, CC_U16 u16Len, CC_U32 u32PTS);
CC_BOOL mapi_CC_Brazil_Queue_PeekN(QueueElement *pQue, CC_U8 u8N);
CC_BOOL mapi_CC_Brazil_Queue_Pop(QueueElement* pQue);
CC_U32 mapi_CC_Brazil_AllocateQue(CC_U16 size);
CC_U32 mapi_CC_Brazil_SetPTS(CC_U8 *pu8bff);
void mapi_CC_Brazil_InitVar(stIntCustomerVariables *pVar);
void mapi_CC_Brazil_EnableDumpRawData(CC_BOOL bDumpRawData);
CC_BOOL mapi_CC_Brazil_CheckTimeOut(void);
void mapi_CC_Brazil_SetTimeoutThreshold(CC_U32 u32BrazilCCTimeout);



#ifdef __cplusplus
  }
#endif

#endif
