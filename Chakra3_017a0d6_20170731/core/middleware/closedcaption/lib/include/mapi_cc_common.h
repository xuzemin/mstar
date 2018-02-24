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

#ifndef MAPI_CC_COMMON_H
#define MAPI_CC_COMMON_H

///////////////////////////////////////////////////////////////////////////////
//
//  File name: mapi_cc_common.h
//
//  Company: MStarSemi Inc.
//
//  Description: Put some same #define or data structure in Brazil and ATSC CC
//
///////////////////////////////////////////////////////////////////////////////

/******************************************************************************/
/*                 Header Files                                               */
/* ****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************************/
/* Define                                                                              */
/***************************************************************************************/
#define SUPPORT_INSERT_CC_TO_VE        0   // Fix it later~

#define NA          0xFF
#define NA_PREVIEW          0xFE

// Debug wrapper
#define CC_DBINFO_L2(y)
#define CC_DBINFO_EX(y)
#define CC_DBINFO_TEMP(y)
#define CC_DBINFO_CtrlBuf(y)
#define CC_DBINFO_Color(y)
#define CC_DBINFO_STEP(y)
#define CC_DBINFO_FIELDTRY1(y)
#define CC_DBINFO_FIELDTRY2(y)
#define CC_DBINFO_CMD(y)        // y
#define CC_DBINFO_CMD608(y)
#define CC_DBFLUSH_MEMORY_CMD(y)  // y

// Self-Test item
#define _CC_DEBUG_TEST_PATTERN_   0   // 0: None, 1,3: test pattern (3: from flash), 2: self-test
#define _CC_DEBUG_CCPKT_              0   // For Specific CC708 Packet test
#define _CC_DEBUG_GETONE_708_   0   // For getting one ringbuffer data of 708.
#define _CC_DEBUG_FLUSHENGINE_ 0

// Dump item
#define _CC_PACKET_DUMP_        0   // For Dump DTVCC 708 Packet data
#define _CC_SERVICE_DUMP_       0   // For Dump DTVCC 708 Service data
#define _CC_708_CMD_DUMP_       0   // For 708 CMD Debug

// Special font index
#define CC_FONT_IDX_UNDERLINE       0x9A
#define CC_FONT_IDX_TRANSPARENT     0xA0
#define CC_ALIGNED_VALUE(value, align)  ( ((value) + ((align)-1)) & ~((align)-1) )

//Data MASK
#define VBIDATAMASK                 0x7F

// GWIN alignment, the unit is pixel
#define GWIN_ALIGND_VALUE               16
#define GWIN_ALIGNMENT_MASK             0xFFF0

#define CC_FLUSH_AllWIN     10
#define MAX_CS_WINDOW_NO           8
 
//CC program information transparent/translucent color index
//#if (defined(CC708_PALETTE_64Color))
//#define CC_GOP_PALLETTE_TRANS_IDX           255
//#define CC_COLOR_IDX_TRANSLUCENT           64                            //I8 used
//#else
//#define CC_GOP_PALLETTE_TRANS_IDX           255
//#define CC_COLOR_IDX_TRANSLUCENT           8                            //I8 used  only used in window color ID, need change in Chakra2 tip code
//#endif

#define CC_COLOR_IDX_TRANSPARENT            255
#define CC_COLOR_IDX_TRANSLUCENT           64  

#define PALETTE_ENTRY_NUM           256
#define PALETTE_TABLE_NUM           CC_COLOR_IDX_TRANSLUCENT

/* CC608 GOP ID ASSIGNMENT */
//CC program information CC 608 framebuffer
#define GWID_CC608_WIN0             0
#define GWID_CC608_WIN1             1
#define GWID_CC608_ROLLUP           2

/* CC708 Definition */
//CC program information CC 708 row/col number
#define CC708_MAX_ROW_NUMBER           15
#define CC708_MAX_COL_NUMBER           44

//CC program information CC 708 sold/translucent number
#define CC_SOLID_VALUE                  0xFF
#define CC_TRANSLUCENT_VALUE           0xA0

//CC program information CC 708 special define(avoid some side effect)
#define _CC708_PRIORITY_CHECK_          0       // Do the Priority check
#define _CC708_DELGWIN_WHENADDWINDOW_           0
#define _CC708_DELGWIN_WHENUPDATEWINDOW_        0
#define _CC708_BORDER 2

//CC program information CC 708 roll up step
#define FontSizeMapRStep1 11
#define FontSizeMapRStep2 22
#define FontSizeMapRStep3 33
#define FontSizeMapRStep4 44
#define FontSizeMapRStep5 55
#define FontSizeMapRStep6 66

#define GOP_FRAME_FORMAT            GFX_FMT_I8
#define PALETTE_ENTRY_608_NUM       64


#define SIZE_OF_PACKET_BUFFER        128
#define SIZE_OF_SERVICE_BUFFER       256//128

/***************************************************************************************/
/* Data structure                                                                      */
/***************************************************************************************/


/***************************************************************************************/
/* Variables                                                                           */
/***************************************************************************************/


/***************************************************************************************/
/* Functions                                                                           */
/***************************************************************************************/

/*
 * Common functions
 */

#ifdef __cplusplus
  }
#endif

#endif
///*** please do not remove change list tag ***///
///***$Change: 1432294 $***///
