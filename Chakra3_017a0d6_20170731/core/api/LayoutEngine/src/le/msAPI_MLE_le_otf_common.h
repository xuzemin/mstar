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

#ifndef __MSAPI_MSTAR_LE_OTF_COMMON_H__
#define __MSAPI_MSTAR_LE_OTF_COMMON_H__

#ifdef __FEATURE_VECTOR_FONT__

#include "msAPI_MLE_le_types.h"
#include "msAPI_MLE_le_util.h"

typedef struct
{
    LE_GlyphId FirstGlyph;
    LE_GlyphId LastGlyph;
    U16 u16RangeValue;
} LE_GlyphRangeRecord_t;
#define LE_GlyphRangeRecord_SIZE (sizeof(LE_GlyphId) + sizeof(LE_GlyphId) + sizeof(U16))

/*=============== Language & Script List Table Begin ==============*/
typedef struct
{
    LE_Tag Tag;
    LE_Offset Offset;
} LE_LangSysRecord_t;

typedef struct
{
    LE_Offset LookupOrderOffset;
    U16 u16ReqFeatureIndex;
    U16 u16FeatureCount;
    U16 au16FeatureIndex[LE_ARRAY_NUM];
} LE_LangSysTable_t;

typedef struct
{
    LE_Offset DefaultLangSysTableOffset;
    U16 u16LangSysCount;
    LE_LangSysRecord_t asLangSysRecord[LE_ARRAY_NUM];
} LE_ScriptTable_t;

typedef struct
{
    LE_Tag Tag;
    LE_Offset Offset;
} LE_ScriptRecord_t;
#define LE_ScriptRecord_Size (sizeof(LE_Tag) + sizeof(LE_Offset))

typedef struct
{
    U16 u16ScriptCount;
    LE_ScriptRecord_t asScriptRecord[LE_ARRAY_NUM];
} LE_ScriptListTable_t;
/*=============== Language & Script List Table End ==============*/

/*=============== Feature List Table Begin ==============*/
typedef struct
{
    LE_Offset FeatureParamsOffset;
    U16 u16LookupCount;
    U16 au16LookupListIndex[LE_ARRAY_NUM];
} LE_FeatureTable_t;

typedef struct
{
    LE_Tag FeatureTag;
    LE_Offset FeatureTableOffset;
} LE_FeatureRecord_t;
#define LE_FeatureRecord_Size (sizeof(LE_Tag) + sizeof(LE_Offset))

typedef struct
{
    U16 u16FeatureCount;
    LE_FeatureRecord_t asFeatureRecord[LE_ARRAY_NUM];
} LE_FeatureListTable_t;
/*=============== Feature List Table End ==============*/

/*=============== Lookup Table Begin ==============*/
enum
{
    LE_LOOKUP_FLAG_RIGHTTOLEFT          = 0x0001,
    LE_LOOKUP_FLAG_IGNORE_BASEGLYPHS    = 0x0002,
    LE_LOOKUP_FLAG_IGNORE_LIGATURES     = 0x0004,
    LE_LOOKUP_FLAG_IGNORE_MARKS         = 0x0008,
    LE_LOOKUP_FLAG_USE_MARKFILTERINGSET = 0x0010,
    LE_LOOKUP_FLAG_RESERVED             = 0x00E0,
    LE_LOOKUP_FLAG_MARKATTACHMENTTYPE   = 0xFF00,
};
typedef U16 LE_LookupFlag_e;

typedef struct
{
    U16 u16SubtableFormat;
    LE_Offset CoverageTableOffset;
} LE_LookupSubtable_t;

typedef struct
{
    U16 u16LookupType;
    U16 u16LookupFlag;
    U16 u16SubtableCount;
    LE_Offset aSubtableOffset[LE_ARRAY_NUM];
} LE_LookupTable_t;

typedef struct
{
    U16 u16LookupCount;
    LE_Offset aLookupTableOffset[LE_ARRAY_NUM];
} LE_LookupListTable_t;
/*=============== Lookup Table End ==============*/

/*=============== Value Record Begin ==============*/
enum
{
    LE_VALUE_X_PLACEMENT_INDEX        = 0x0000,
    LE_VALUE_Y_PLACEMENT_INDEX        = 0x0001,
    LE_VALUE_X_ADVANCE_INDEX          = 0x0002,
    LE_VALUE_Y_ADVANCE_INDEX          = 0x0003,
    LE_VALUE_X_PLACEMENT_DEVICE_INDEX = 0x0004,
    LE_VALUE_Y_PLACEMENT_DEVICE_INDEX = 0x0005,
    LE_VALUE_X_ADVANCE_DEVICE_INDEX   = 0x0006,
    LE_VALUE_Y_ADVANCE_DEVICE_INDEX   = 0x0007
};
typedef U16 LE_ValueFormatIndex_e;

enum
{
    LE_VALUE_X_PLACEMENT        = 0x0001,
    LE_VALUE_Y_PLACEMENT        = 0x0002,
    LE_VALUE_X_ADVANCE          = 0x0004,
    LE_VALUE_Y_ADVANCE          = 0x0008,
    LE_VALUE_X_PLACEMENT_DEVICE = 0x0010,
    LE_VALUE_Y_PLACEMENT_DEVICE = 0x0020,
    LE_VALUE_X_ADVANCE_DEVICE   = 0x0040,
    LE_VALUE_Y_ADVANCE_DEVICE   = 0x0080,
    LE_VALUE_RESERVED           = 0xFF00,
    LE_VALUE_ANY_DEVICE         = LE_VALUE_X_PLACEMENT_DEVICE + LE_VALUE_Y_PLACEMENT_DEVICE + LE_VALUE_X_ADVANCE_DEVICE + LE_VALUE_Y_ADVANCE_DEVICE
};
typedef U16 LE_ValueFormat_e;

typedef struct
{
    S16 as16Value[LE_ARRAY_NUM];
} LE_ValueRecord_t; 
/*=============== Value Record End ==============*/

/*=============== Device Table Begin ==============*/
typedef struct
{
    U16 u16StartSize;
    U16 u16EndSize;
    U16 u16DeltaFormat;
    U16 u16DeltaValues[LE_ARRAY_NUM];
} LE_DeviceTable_t;
/*=============== Device Table End ==============*/

/*=============== COVERAGE Table Begin ==============*/
enum
{
    LE_COVERAGE_TABLE_FORMAT_INVALID = 0,
    LE_COVERAGE_TABLE_FORMAT_1 = 1,
    LE_COVERAGE_TABLE_FORMAT_2 = 2
};
typedef U16 LE_CoverageTableFormat_e;

typedef struct
{
    U16 u16GlyphCount;
    U16 au16Glyph[LE_ARRAY_NUM];
} LE_CoverageTableFormat1_t;

typedef struct
{
    U16 u16RangeCount;
    LE_GlyphRangeRecord_t asRangeRecord[LE_ARRAY_NUM];
} LE_CoverageTableFormat2_t;

typedef struct
{
    U16 u16CoverageFormat;
    union
    {
        LE_CoverageTableFormat1_t sData1;
        LE_CoverageTableFormat2_t sData2;
    } usData;
} LE_CoverageTable_t;
/*=============== COVERAGE Table End ==============*/

/*=============== CLASS DEFINITION Table Begin ==============*/
enum
{
    LE_CLASS_DEFINITION_FORMAT_INVALID = 0,
    LE_CLASS_DEFINITION_FORMAT_1 = 1,
    LE_CLASS_DEFINITION_FORMAT_2 = 2
};
typedef U16 LE_ClassDefinitionFormat_e;

typedef struct
{
    U16 u16StartGlyph;
    U16 u16GlyphCount;
    U16 au16ClassValue[LE_ARRAY_NUM];
} LE_ClassDefinitionFormat1_t;

typedef struct
{
    U16 u16ClassRangeCount;
    LE_GlyphRangeRecord_t asClassRangeRecord[LE_ARRAY_NUM];
} LE_ClassDefinitionFormat2_t;

typedef struct
{
    U16 u16ClassFormat;
    union
    {
        LE_ClassDefinitionFormat1_t sData1;
        LE_ClassDefinitionFormat2_t sData2;
    } usData;
} LE_ClassDefinition_t;
/*=============== CLASS DEFINITION Table End ==============*/

/*=============== Anchor Table Begin ==============*/
enum
{
    LE_ANCHOR_TABLE_FORMAT_INVALID = 0,
    LE_ANCHOR_TABLE_FORMAT_1 = 1,
    LE_ANCHOR_TABLE_FORMAT_2 = 2,
    LE_ANCHOR_TABLE_FORMAT_3 = 3
};
typedef U16 LE_AnchorTableFormat_e;

typedef struct
{
    S16 s16XCoordinate;
    S16 s16YCoordinate;
} LE_AnchorTableFormat1_t;

typedef struct
{
    S16 s16XCoordinate;
    S16 s16YCoordinate;
    U16 u16AnchorPoint;
} LE_AnchorTableFormat2_t;

typedef struct
{
    S16 s16XCoordinate;
    S16 s16YCoordinate;
    LE_Offset XDeviceTableOffset;
    LE_Offset YDeviceTableOffset;
} LE_AnchorTableFormat3_t;

typedef struct
{
    U16 u16AnchorFormat;
    union
    {
        LE_AnchorTableFormat1_t sData1;
        LE_AnchorTableFormat2_t sData2;
        LE_AnchorTableFormat3_t sData3;
    } usData;
} LE_AnchorTable_t;
/*=============== Anchor Table End ==============*/

/*=============== Mark Array Begin ==============*/
typedef struct
{
    U16 u16MarkClass;
    LE_Offset MarkAnchorTableOffset;
} LE_MarkRecord_t;
#define LE_MarkRecord_Size (sizeof(U16) + sizeof(LE_Offset))

typedef struct
{
    U16 u16MarkCount;
    LE_MarkRecord_t asMarkRecord[LE_ARRAY_NUM];
} LE_MarkArray_t;
/*=============== Mark Array End ==============*/

/*=============== CONTEXT Begin ==============*/
enum
{
    LE_CONTEXT_FORMAT_INVALID = 0,
    LE_CONTEXT_FORMAT_1 = 1,
    LE_CONTEXT_FORMAT_2 = 2,
    LE_CONTEXT_FORMAT_3 = 3
};
typedef U16 LE_ContextFormat_e;

typedef struct
{
    U16 u16SeqIndex;
    U16 u16LookupListIndex;
} LE_LookupRecord_t;
#define LE_LookupRecord_Size (sizeof(U16) + sizeof(U16))

typedef struct
{
    U16 u16GlyphCount;
    U16 u16Count;
    LE_GlyphId aInputGlyph[LE_ARRAY_NUM/*u16Count - 1*/];
    /*LE_LookupRecord_t SubstLookupRecord[u16Count];*/
} LE_RuleTable_t;

typedef struct
{
    U16 u16RuleCount;
    LE_Offset aRuleTableOffset[LE_ARRAY_NUM];
} LE_RuleSetTable_t;

typedef struct
{
    U16 u16RuleSetCount;
    LE_Offset aRuleSetTableOffset[LE_ARRAY_NUM];
} LE_ContextFormat1_t;

typedef struct
{
    U16 u16GlyphCount;
    U16 u16Count;
    U16 au16Class[LE_ARRAY_NUM];
} LE_ClassRuleTable_t;

typedef struct
{
    U16 u16ClassRuleCount;
    LE_Offset aClassRuleTableOffset[LE_ARRAY_NUM];
} LE_ClassSetTable_t;

typedef struct
{
    LE_Offset ClassDefTableOffset;
    U16 u16ClassSetCount;
    LE_Offset aClassSetTableOffset[LE_ARRAY_NUM];
} LE_ContextFormat2_t;

typedef struct
{
    U16 u16GlyphCount;
    U16 u16Count;
    LE_Offset aCoverageTableOffset[LE_ARRAY_NUM];
} LE_ContextFormat3_t;

typedef union
{
    U16 u16Format;
    LE_Offset CoverageOffset;
    union
    {
        LE_ContextFormat1_t sData1;
        LE_ContextFormat2_t sData2;
        LE_ContextFormat3_t sData3;
    } usData;
} LE_Context_t;
/*=============== CONTEXT End ==============*/

/*=============== CHAINING CONTEXT Begin ==============*/
enum
{
    LE_CHAININGCONTEXT_FORMAT_INVALID = 0,
    LE_CHAININGCONTEXT_FORMAT_1 = 1,
    LE_CHAININGCONTEXT_FORMAT_2 = 2,
    LE_CHAININGCONTEXT_FORMAT_3 = 3
};
typedef U16 LE_ChainingContextFormat_e;

typedef struct
{
    U16 u16BacktrackGlyphCount;
    LE_GlyphId aBacktrackGlyph[LE_ARRAY_NUM/*u16BacktrackGlyphCount*/];
    /*U16 InputGlyphCount;*/
    /*LE_GlyphId    Input[InputGlyphCount - 1];*/
    /* U16 LookaheadGlyphCount;*/
    /*LE_GlyphId    LookAhead[LookaheadGlyphCount];*/
    /* U16 SubstCount;*/
    /*LE_LookupRecord_t SubstLookupRecord[SubstCount];*/
} LE_ChainRuleTable_t;

typedef struct
{
    U16 u16ChainRuleCount;
    U16 au16ChainRuleTableOffset[LE_ARRAY_NUM];
} LE_ChainRuleSetTable_t;

typedef struct
{
    U16 u16ChainRuleSetCount;
    LE_Offset aChainRuleSetTableOffset[LE_ARRAY_NUM];
} LE_ChainingContextFormat1_t;

typedef struct
{
    U16 u16BacktrackGlyphCount;
    U16 au16BacktrackClass[LE_ARRAY_NUM];
} LE_ChainClassRuleTable_t;

typedef struct
{
    U16 u16ChainClassRuleCount;
    LE_Offset aChainClassRuleTableOffset[LE_ARRAY_NUM];
} LE_ChainClassSetTable_t;

typedef struct
{
    LE_Offset BacktrackClassDefTableOffset;
    LE_Offset InputClassDefTableOffset;
    LE_Offset LookaheadClassDefTableOffset;
    U16 u16ChainClassSetCount;
    LE_Offset aChainClassSetTableOffset[LE_ARRAY_NUM];
} LE_ChainingContextFormat2_t;

typedef struct
{
    U16 u16BacktrackGlyphCount;
    LE_Offset aBacktrackCoverageTableOffset[LE_ARRAY_NUM];
} LE_ChainingContextFormat3_t;

typedef union
{
    U16 u16SubstFormat;
    LE_Offset CoverageOffset;
    union
    {
        LE_ChainingContextFormat1_t sData1;
        LE_ChainingContextFormat1_t sData2;
        LE_ChainingContextFormat1_t sData3;
    } usData;
} LE_ChainingContext_t;
/*=============== CHAINING CONTEXT End ==============*/

/*=============== EXTENSION Begin ==============*/
typedef struct
{
    U16 u16SubstFormat;
    U16 u16ExtensionLookupType;
    LE_Offset ExtensionOffset;
} LE_Extension_t;
/*=============== EXTENSION End ==============*/

S32 msAPI_MLE_LeGetGlyphCoverage( const U8 *psCover, U16 u16GlyphId );
S32 msAPI_MLE_LeGetGlyphClass( const U8 *pDefTable, U16 u16GlyphId );
BOOLEAN msAPI_MLE_LeHasGlyphClass( const U8 *pDefTable, S32 s32GlyphClass );
S16 msAPI_MLE_LeValueGetFieldCount( LE_ValueFormat_e eValueFormat );
S16 msAPI_MLE_LeValueGetSize( LE_ValueFormat_e eValueFormat );
S16 msAPI_MLE_LeValueGetFieldIndex( LE_ValueFormat_e eValueFormat, S16 s16Field );
U16 msAPI_MLE_LeValueGetFieldValue( const U8 *pValueRecord,LE_ValueFormat_e eValueFormat, S16 s16Field );
S16 msAPI_MLE_LeDeviceTableGetAdjustment( const U8 *pDeviceTable, U16 u16PixelsPerEM );
BOOLEAN msAPI_MLE_LeGetAnchor( const U8 *pAnchorTable, U16 u16GlyphId, LE_Points_t *pAnchor, LE_FontInstanceInf_t *pFontInstanceInf );
S32 msAPI_MLE_LeMarkArrayGetMarkClass(const U8 *pMarks, U16 u16GlyphId, S32 s32CoverageIndex, LE_Points_t *pAnchor, LE_FontInstanceInf_t *pFontInstance);
U16 msAPI_MLE_LeContextTableGetLookupRecord( const U8 *psContext, void *psProcess, const U32 *paGlyphId, U16 u16GlyphLen, U16 u16Position, const U8 **ppasRecords, LE_LookupFlag_e eLookupFlags, BOOLEAN bGSUB );
U16 msAPI_MLE_LeChainingContextTableGetLookupRecord( const U8 *psChainingContext, void *psProcess, const U32 *paGlyphId, U16 u16GlyphLen, U16 u16Position, const U8 **ppasRecords, LE_LookupFlag_e eLookupFlags, BOOLEAN bGSUB );
const U8* msAPI_MLE_LeGetFeatureTable( const U16 u16FeatureCount, const U16 *pu16FeatureIndices, const U8 *pFeatureList, LE_FeatureTag_e u32FeatureTag, U16 *pu16LookupCount );
BOOLEAN msAPI_MLE_LeFeatureTableGetLookupIndexs( const U8 *pFeature, U16 *pau16Index, U16 u16ArraySize );
const U8* msAPI_MLE_LeLookupListTableGetLookupTable( const U8 *pLookupList, U16 u16Index, U16 *pu16SubtableCount );
const U8* msAPI_MLE_LeLookupTableGetLookupSubtable( const U8 *pLookup, U16 u16Index );
const U8* msAPI_MLE_LeFindScript( const U8 *pScriptList, LE_ScriptTag_e eScriptTag, LE_ScriptTag_e eScriptTagV2 );
BOOLEAN msAPI_MLE_LeFindLangSysTable( const U8 *pu8ScriptTable, LE_LanguageTag_e eLang, U16 *pu16FeatureCount, U16 *pu16FeatureIndices);

U16 msAPI_MLE_LeGlyphStrGetNext( const U32 *paGlyphId, U16 u16GlyphLen, U16 u16Position, U16 u16NextCount, U16 *pu16NextPosition, const U8 *pDefTable, LE_LookupFlag_e eLookupFlags, BOOLEAN bIgnoreFFFE );
U16 msAPI_MLE_LeGlyphStrGetNextBaseGlyph( const U32 *paGlyphId, U16 u16GlyphLen, U16 u16Position, U16 u16NextCount, U16 *pu16NextPosition, const U8 *pDefTable, LE_LookupFlag_e eLookupFlags, BOOLEAN bIgnoreFFFE );

#endif //__FEATURE_VECTOR_FONT__

#endif //__MSAPI_MSTAR_LE_OTF_COMMON_H__
