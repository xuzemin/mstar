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


#ifndef __MSAPI_MLE_BIDI_PRIV_H__
#define __MSAPI_MLE_BIDI_PRIV_H__

#include "msAPI_MLE_common_def.h"

typedef enum
{
    // input types
    BIDI_ON = 0,  // Other Neutral
    BIDI_L,       // Left Letter
    BIDI_R,       // Right Letter
    BIDI_AN,      // Arabic Number
    BIDI_EN,      // European Number
    BIDI_AL,      // Arabic Letter (Right-to-left)
    BIDI_NSM,     // Non-spacing Mark
    BIDI_CS,      // Common Separator
    BIDI_ES,      // European Separator
    BIDI_ET,      // European Terminator (post/prefix e.g. $ and %)

    // resolved types
    BIDI_BN,      // Boundary neutral (type of RLE etc after explicit levels)

    // input types
    BIDI_S,       // Segment Separator (TAB)  // used only in L1
    BIDI_WS,      // White space              // used only in L1
    BIDI_B,       // Paragraph Separator (aka as PS)

    // types for explicit controls
    BIDI_RLO,     // these are used only in X1-X9
    BIDI_RLE,
    BIDI_LRO,
    BIDI_LRE,
    BIDI_PDF,

    // resolved types, also resolved directions
    BIDI_N = BIDI_ON  // alias, where ON, WS and S are treated the same
} Bidi_CharType_e;

//Possible states
typedef enum
{
    BIDI_WEAK_XA,  //  arabic letter
    BIDI_WEAK_XR,  //  right letter
    BIDI_WEAK_XL,  //  left letter

    BIDI_WEAK_AO,  //  arabic letter followed by ON
    BIDI_WEAK_RO,  //  right letter followed by ON
    BIDI_WEAK_LO,  //  left letter followed by ON

    BIDI_WEAK_RT,  //  ET following R
    BIDI_WEAK_LT,  //  ET following L

    BIDI_WEAK_CN,  //  EN, AN following AL
    BIDI_WEAK_RA,  //  arabic number followed R
    BIDI_WEAK_RE,  //  european number followed R
    BIDI_WEAK_LA,  //  arabic number followed L
    BIDI_WEAK_LE,  //  european number followed L

    BIDI_WEAK_AC,  //  CS following cn
    BIDI_WEAK_RC,  //  CS following ra (right arabic (NxA))
    BIDI_WEAK_RS,  //  CS,ES following re
    BIDI_WEAK_LC,  //  CS following la (left arabic (AxN))
    BIDI_WEAK_LS,  //  CS,ES following le

    BIDI_WEAK_RET, //  ET following re
    BIDI_WEAK_LET  //  ET following le
} Bidi_WeakState_e;

// state values
typedef enum
{
    // new temporary class
    BIDI_NEUTRAL_R,  // R and characters resolved to R
    BIDI_NEUTRAL_L,  // L and characters resolved to L
    BIDI_NEUTRAL_RN, // N preceded by right
    BIDI_NEUTRAL_LN, // N preceded by left
    BIDI_NEUTRAL_A,  // AN preceded by left (the abbrev 'la' is used up above)
    BIDI_NEUTRAL_NA  // N preceeded by a
} Bidi_NeutralState_e;

#define BIDI_LEVEL_MAX_SIZE      61

// possible actions

// primitives
#define BIDI_WEAK_ACT_IX 0x100   // increment
#define BIDI_WEAK_ACT_XX 0xF     // no-op

// actions
#define BIDI_WEAK_ACT_XXX  ((BIDI_WEAK_ACT_XX << 4) + BIDI_WEAK_ACT_XX) // no-op
#define BIDI_WEAK_ACT_XIX  ((BIDI_WEAK_ACT_IX) + BIDI_WEAK_ACT_XXX)     // increment run
#define BIDI_WEAK_ACT_XXN  ((BIDI_WEAK_ACT_XX << 4) + BIDI_ON)          // set current to N
#define BIDI_WEAK_ACT_XXE  ((BIDI_WEAK_ACT_XX << 4) + BIDI_EN)          // set current to EN
#define BIDI_WEAK_ACT_XXA  ((BIDI_WEAK_ACT_XX << 4) + BIDI_AN)          // set current to AN
#define BIDI_WEAK_ACT_XXR  ((BIDI_WEAK_ACT_XX << 4) + BIDI_R)           // set current to R
#define BIDI_WEAK_ACT_XXL  ((BIDI_WEAK_ACT_XX << 4) + BIDI_L)           // set current to L
#define BIDI_WEAK_ACT_NXX  ((BIDI_ON << 4) + 0xF)                       // set run to neutral
#define BIDI_WEAK_ACT_AXX  ((BIDI_AN << 4) + 0xF)                       // set run to AN
#define BIDI_WEAK_ACT_EXE  ((BIDI_EN << 4) + BIDI_EN)                   // set run to EN, set current to EN
#define BIDI_WEAK_ACT_NIX  ((BIDI_ON << 4) + 0xF + BIDI_WEAK_ACT_IX)    // set run to N, increment
#define BIDI_WEAK_ACT_NXN  ((BIDI_ON << 4) + BIDI_ON)                   // set run to N, set current to N
#define BIDI_WEAK_ACT_NXR  ((BIDI_ON << 4) + BIDI_R)                    // set run to N, set current to R
#define BIDI_WEAK_ACT_NXE  ((BIDI_ON << 4) + BIDI_EN)                   // set run to N, set current to EN

#define BIDI_WEAK_ACT_AXA  ((BIDI_AN << 4) + BIDI_AN)                   // set run to AN, set current to AN
#define BIDI_WEAK_ACT_NXL  ((BIDI_ON << 4) + BIDI_L)                    // set run to N, set current to L
#define BIDI_WEAK_ACT_LXL  ((BIDI_L << 4) + BIDI_L)                     // set run to L, set current to L

// action to resolve previous input
#define BIDI_NEUTRAL_ACT_NL  (BIDI_L)                 // resolve EN to L
#define BIDI_NEUTRAL_ACT_EN  (3 << 4)                 // resolve neutrals run to embedding level direction
#define BIDI_NEUTRAL_ACT_RN  (BIDI_R << 4)            // resolve neutrals run to strong right
#define BIDI_NEUTRAL_ACT_LN  (BIDI_L << 4)            // resolved neutrals run to strong left
#define BIDI_NEUTRAL_ACT_IN  (1 << 8)                 // increment count of deferred neutrals
#define BIDI_NEUTRAL_ACT_LNL ((BIDI_L << 4) + BIDI_L) // set run and EN to L

typedef struct
{
    BOOLEAN bRight2Left;
    U32 nOffset;
    U32 nLength;
} Bidi_LineData_t;

typedef struct
{
    U32 nMaxLines;
    U32 nLines;
} Bidi_TableData_t;

typedef struct
{
    Bidi_TableData_t tTableInf;
    Bidi_LineData_t *pLines;
 } Bidi_LineTable_t;

typedef struct
{
    MLE_WChar *pOrderStr;
    U16 *pLogicalPosInLine;
    U8 *pCharLevel;
    U32 nStrLen;
    BOOLEAN bUserTable;
    BOOLEAN bIsDisplayRTL;
    Bidi_LineTable_t *pLineTable;
} Bidi_Handler_t;

#define BIDI_GET_LINE( _pTable_,_i_ ) (((Bidi_LineData_t *)&((_pTable_)->pLines)) + _i_)

#ifdef __BIDI_TEXT__
static void _msAPI_MLE_BidiConvertCharType( MLE_WChar *pString, U16 *pCharTypes, U32 *pStrLen, BOOLEAN bReportWsType );
static void _msAPI_MLE_BidiResolveExplicit( U8 nBaseLevel, U16 *pCharTypes, U8 *pCharLevels, U32 nStrLen );
static void _msAPI_MLE_BidiResolveWeak( U8 u8Baselevel, U16 *pCharTypes, U8 *pCharLevels, U32 nStrLen );
static void _msAPI_MLE_BidiResolveNeutrals( U8 u8Baselevel, U16 *pCharTypes, U8 *pCharLevels, U32 nStrLen );
static void _msAPI_MLE_BidiResolveImplicit( U16 *pCharTypes, U8 *pCharLevels, U32 nStrLen );
static void _msAPI_MLE_BidiOrderLine( MLE_WChar *pString, U16 *pCharTypes, U8 *pCharLevels, U16 *pu16LogicPos, U32 nStrLen, U8 nBaseLevel );
static void _msAPI_MLE_BidiResolveWhitespace( U8 nBaseLevel, U16 *pCharTypes, U8 *pCharLevels, U32 nStrLen );
static void _msAPI_MLE_BidiMirrorStr( MLE_WChar *pString, U8 *pCharLevels, U32 nStrLen );
static BOOLEAN _msAPI_MLE_BidiDoMirror( MLE_WChar *pChar, S32 nStartIndex, S32 nEndIndex );
static U32 _msAPI_MLE_BidiReorderLevel( U8 nLevel, MLE_WChar *pText, U8 *pCharlevels, U32 nStrLen, U32 nOffset, U32 nSubLen, BOOLEAN bReverse, U16 *pRealPos );
static void _msAPI_MLE_BidiOrderCharLevel( U16 *pPosInLine, U32 u32Len, U8 *pCharLevels );
static Bidi_CharType_e _msAPI_MLE_BidiGetCharType( MLE_WChar wChar, BOOLEAN bReportWsType );
#endif //__BIDI_TEXT__

static BOOLEAN _msAPI_MLE_BidiOrderString( MLE_WChar *pString, U16 *pPosInLine, U32 nOffset, U32 nSubStrLen, BOOLEAN bRight2Left, Bidi_LineTable_t *pTable, U32 *pStartIndex, U32 *pStartOffset, U8 **ppCharLevel );
static void _msAPI_MLE_BidiInitLogicalPos( U16 *pStrPos, U32 nStrLen );
__SLDPM_FREE__ static Bidi_LineTable_t* _msAPI_MLE_BidiTableAlloc( U32 nLineSize );
static void _msAPI_MLE_BidiTableFree( Bidi_LineTable_t *pLineTable );
static BOOLEAN _msAPI_MLE_BidiTableAddLine( Bidi_LineTable_t **ppLineTable, U32 nOffset, U32 nSubLen, BOOLEAN bRight2Left );
static BOOLEAN _msAPI_MLE_BidiTableDefaultMeasureLines( Bidi_LineTable_t **ppTable, MLE_WChar *pString, U32 u16StrLen, BOOLEAN bRight2Left );
__SLDPM_FREE__ static U32 _msAPI_MLE_BidiResolveParagraph( const MLE_WChar *pString, U32 nStrLen, U32 nOffset );

#endif //__MSAPI_MLE_BIDI_PRIV_H__
