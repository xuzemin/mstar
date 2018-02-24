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
#include "mapi_cc_type.h"
#include "mapi_cc_decode.h"
#include "mapi_cc_render.h"

#ifndef MSAPI_CC_PARSER_H
#define MSAPI_CC_PARSER_H

#ifdef MSAPI_CC_PARSER_C
#define INTERFACE
#else
#define INTERFACE extern
#endif


// Version string
#define MSIF_CC_TAG                 {'M','S','I','F'}                   //Version ID header
#define MSIF_CC_CLASS               {'1','0'}                           //info Class code
#define MSIF_CC_CUS                 0x6666                              //Customer ID
#define MSIF_CC_MOD                 0x6666                              //Module ID
#define MSIF_CC_CHIP                0xFFFF                              //CHIP ID
#define MSIF_CC_CPU                 '1'                                 //CPU
#define MSIF_CC_LIB_CODE            {'C','C','_','E'}                   //Lib code
#define MSIF_CC_LIBVER              {'0','0'}                           //LIB version
#define MSIF_CC_BUILDNUM            {'0','1'}                           //Build Number
#define MSIF_CC_CHANGELIST          {'0','0','1','8','0','2','7','6'}   //P4 ChangeList Number
#define MSIF_CC_OS                  '0'                                 //OS

#define MW_CC_VER                   /* Character String for DRV/API version             */  \
    MSIF_CC_TAG,                    /* 'MSIF'                                           */  \
    MSIF_CC_CLASS,                  /* '00'                                             */  \
    MSIF_CC_CUS,                    /* 0x0000                                           */  \
    MSIF_CC_MOD,                    /* 0x0000                                           */  \
    MSIF_CC_CHIP,                                                                          \
    MSIF_CC_CPU,                                                                           \
    MSIF_CC_LIB_CODE,               /* IP__                                             */  \
    MSIF_CC_LIBVER,                 /* 0.0 ~ Z.Z                                        */  \
    MSIF_CC_BUILDNUM,               /* 00 ~ 99                                          */  \
    MSIF_CC_CHANGELIST,             /* CL#                                              */  \
    MSIF_CC_OS
#if 0
/************************************************************************/
/* Control Area                                                         */
/************************************************************************/
/* CC Self testing */
#define CC_USE_TEST_PATTERN             0    // 0: None, 1,3: test pattern (3: from flash), 2: self-test

#define CC_608_USE_ENHANCE_MODE          1
#define CC_NEW_FLUSH_MECHANISM          1
#define TEXT_FLUSH_PERIOD_TIME              33
#define TEXT_CONTINUOUS_FLUSH_TIME	10

#define CC_MEASURE_SYSTEM_TIME          0    // 0: None, 1: all

/* If using one GWIN, how many times to be flushed. */
#define _CC_FLUSH_PERIOD_COLUMNS        3

/* CC608 Define */
#ifdef CC_MULTI_LANGUAGE
#define CC_TYPE_EIA608                  0
#define CC_TYPE_KOREAN                  1
#define _CC708_Korean_Justify_
#define _KoreanP16Usage_
/* Font's Korean type */
#define CC_LANG_KOREAN_TYPE             3//24
#endif

#define _CC608_REDRAW_BGCOLOR_          0       // for Re-Draw Background Color

/* CC708 FONT Define */
#define _CC708_NON_DYNAMIC_RELOADFONT_  0       // Do not dynamic relaod different Font table
#define _CC708_RELOADFONT_STYLE_        1       // Relaod different Font table in the same SDRAM, for saving SDRAM
#define _CC708_8FONT_TABLE_             2       // All 8 FONT table in SDRAM, for speed up
#define _CC708_FONT_STYLE_MODE_         _CC708_RELOADFONT_STYLE_

/* CC708 RESERVED BLOCK Define */
#define RSVBLK_ROWMAX       16

/* CC Debug Define */
#define _CC_DEBUG_LEVEL2_       0        // For more detail,
#define _CC_DEBUG_EXHANDLE_     0        // For Exception Handle
#define _CC_DEBUG_TEMP_         0    // For Temp Debug
#define _CC_DEBUG_CMD_           0    // For Temp Debug
#define _CC_DEBUG_CMD608_       0    // For Temp Debug

// Ata Temp Debug label
#define _CC_DEBUG_708Step_      0   // For 708 Servive Step Debug
#define _CC_DEBUG_CtrlBuf_      0   // For Control Buffer
#define _CC_DEBUG_CCColor_      0   // For CC color
#define _CC_DEBUG_FieldTry1_    0   // For Field Try use, solve CC.trp bug
#define _CC_DEBUG_FieldTry2_    0   // For Field Try use, solve 5.trp bug
#define _CC_DEBUG_GENGINE_    0

// Self-Test item
#define _CC_DEBUG_CCPKT_        0   // For Specific CC708 Packet test
#define _CC_DEBUG_GETONE_708_   0   // For getting one ringbuffer data of 708.

// Dump item
#define _CC_PACKET_DUMP_        0   // For Dump DTVCC 708 Packet data
#define _CC_SERVICE_DUMP_       0   // For Dump DTVCC 708 Service data
#define _CC_708_CMD_DUMP_       0   // For 708 CMD Debug
#define _CC_DTV_608_PACKET_DUMP_  0 // For Dump DTVCC 608 Packet data

// Additional function

#if (_CC_DEBUG_LEVEL2_)
#define CC_DBINFO_L2(y)            y
#else
#define CC_DBINFO_L2(y)
#endif

#if (_CC_DEBUG_EXHANDLE_)
#define CC_DBINFO_EX(y)            y
#else
#define CC_DBINFO_EX(y)
#endif

#if (_CC_DEBUG_TEMP_)
#define CC_DBINFO_TEMP(y)        y
#else
#define CC_DBINFO_TEMP(y)
#endif

#if (_CC_DEBUG_CtrlBuf_)
#define CC_DBINFO_CtrlBuf(y)        y
#else
#define CC_DBINFO_CtrlBuf(y)
#endif

#if (_CC_DEBUG_CCColor_)
#define CC_DBINFO_Color(y)        y
#else
#define CC_DBINFO_Color(y)
#endif

#if (_CC_DEBUG_708Step_)
#define CC_DBINFO_STEP(y)        y
#else
#define CC_DBINFO_STEP(y)
#endif

#if (_CC_DEBUG_FieldTry1_)
#define CC_DBINFO_FIELDTRY1(y)        y
#else
#define CC_DBINFO_FIELDTRY1(y)
#endif

#if (_CC_DEBUG_FieldTry2_)
#define CC_DBINFO_FIELDTRY2(y)        y
#else
#define CC_DBINFO_FIELDTRY2(y)
#endif

#if (_CC_DEBUG_CMD_)
#define CC_DBINFO_CMD(y)        y
#else
#define CC_DBINFO_CMD(y)
#endif

#if (_CC_DEBUG_CMD608_)
#define CC_DBINFO_CMD608(y)        y
#else
#define CC_DBINFO_CMD608(y)
#endif

#if (_CC_DEBUG_GENGINE_)
#define CC_DBINFO_GENGINE(y)        y
#else
#define CC_DBINFO_GENGINE(y)
#endif

#endif
/***************************************************************************************/
/*                                                                                     */
/* COMMON                                                                              */
/*                                                                                     */
/***************************************************************************************/
typedef enum
{
    CC_SIGNAL_ANALOG,
    CC_SIGNAL_DIGITAL,
} EN_CC_SIGNAL;

typedef enum
{
    CC_INPUT_CAPTIONTYPE = 0,
    CC_INPUT_USING157,
    CC_INPUT_PERIODTIME,
} EN_PARSER_INPUT;
/***************************************************************************************/

INTERFACE CC708_Grph_CntlAttr   * pstCC708_Cntl;
INTERFACE CC708_CodeSyntax_TRPAttr *pstCC708_Trp;
INTERFACE BlinkChar_Info * CCTextBuf;
INTERFACE BlinkBlock_Info * CCBBlockInfo;
INTERFACE CC608_Display_Buffer *cc608DispBuff;
#if KOREAN_CC_ENABLE
INTERFACE CC608_Display_Buffer *cc608DispBuffa;
#endif
INTERFACE CC608_CodeSyntax_CntlAttr *pstCC608_Cntl;
INTERFACE U8 * CC_Service_Buffer;
INTERFACE BOOLEAN fCCDynamicMemAllocFlag;
INTERFACE U8 u8CCType_Option;
/*Check CC Exist */
// the period of checking digital availability
#define CC_CHECK_PERIOD_TIME                 1000   // in ms

INTERFACE BOOLEAN fDCCExistFlag;
INTERFACE BOOLEAN fACCExistFlag;
INTERFACE U32 u32CC_Check_Period;
INTERFACE U32 u32CC608_Last, u32CC708_Last, u32CC157_Last;

#define SET_708CCISEXIST(col)                 (fDCCExistFlag = col)
#define SET_608CCISEXIST(col)                 (fACCExistFlag = col)
#define CHECKCCEXIST(col)                        ((col == TRUE)?TRUE:FALSE)

/* Common Function List */
INTERFACE void msAPI_CC_Reset(void);
INTERFACE void msAPI_CC_InitialData(U8 u8CCType, BOOLEAN DTVInUse);
INTERFACE void msAPI_CC_AllocateMemory(U8 u8CCType);
INTERFACE void msAPI_CC_DeleteMemory(void);
INTERFACE void msAPI_CC_ClearBuffer(void);
INTERFACE void msAPI_CC_SetDrvVar(void);    
INTERFACE BOOL msAPI_CC_GetLibVer(const MSIF_Version **ppVersion);
INTERFACE BOOLEAN msAPI_CC_AnalogCC608_Available(void);
INTERFACE BOOLEAN msAPI_CC_DigitalCC608_Available(void);
INTERFACE BOOLEAN msAPI_CC_DigitalCC708_Available(void);
INTERFACE void msAPI_CC_ResetExistInfo(void);
INTERFACE void msAPI_CC_SetPeriodTime(U32 u32PeriodTime);
INTERFACE void msAPI_CC_SetInputData(EN_PARSER_INPUT enInputType, U32 u32Val);
INTERFACE void msAPI_CC_WakeUp(void);
INTERFACE void msAPI_CC_VchipRateReset(void);



//INTERFACE7 void msAPI_CC_DigitalCC_Parser(void);
INTERFACE U8 msAPI_CC_DigitalCC708_AvailableType(void);
INTERFACE U8 msAPI_CC_CC608_AvailableType(void);
INTERFACE void msAPI_CC_DigitalCC_Parser(BOOLEAN fEnableCCFunc);
INTERFACE void msAPI_CC_AnalogCC_Parser(void);
//INTERFACE7 void msAPI_CC_Parser(U8 u8CCType);
INTERFACE void msAPI_CC_Parser(U8 u8CCType, BOOLEAN fEnableCCFunc);
INTERFACE U8 msAPI_CC_GetEnableDispGwin(void);

#undef INTERFACE
#endif
