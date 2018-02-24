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

#ifndef __MSAPI_MLE_LE_OTF_POS_H__
#define __MSAPI_MLE_LE_OTF_POS_H__

#ifdef __FEATURE_VECTOR_FONT__

#include "msAPI_MLE_le_otf_common.h"
#include "msAPI_MLE_font_hindi_priv.h"

typedef enum
{
    LE_POS_LOOKUP_INVALID                     = 0,
    LE_POS_LOOKUP_SINGLE_ADJUSTMENT           = 1,
    LE_POS_LOOKUP_PAIR_ADJUSTMENT             = 2,
    LE_POS_LOOKUP_CURSIVE_ATTACHMENT          = 3,
    LE_POS_LOOKUP_MARKTOBASE_ATTACHMENT       = 4,
    LE_POS_LOOKUP_MARKTOLIGATURE_ATTACHEMENT  = 5,
    LE_POS_LOOKUP_MARKTOMARK_ATTACHEMENT      = 6,
    LE_POS_LOOKUP_CONTEXT                     = 7,
    LE_POS_LOOKUP_CHAINED_CONTEXT             = 8, 
    LE_POS_LOOKUP_EXTENSION                   = 9
} LE_PositionLookupType_e;

typedef struct
{
    LE_Version u32Version;
    LE_Offset ScriptListOffset;
    LE_Offset FeatureListOffset;
    LE_Offset LookupListOffset;
} LE_GPOSTable_t;

/*=============== SINGLE ADJUSTMENT POSITION Begin ==============*/
enum
{
    LE_SINGLE_ADJ_POS_FORMAT_INVALID = 0,
    LE_SINGLE_ADJ_POS_FORMAT_1 = 1,
    LE_SINGLE_ADJ_POS_FORMAT_2 = 2
};
typedef U16 LE_SingleAdjPositionFormat_e;

typedef struct
{
    U16 u16ValueFormat;
    LE_ValueRecord_t sValueRecord;
} LE_SingleAdjPositionFormat1_t;

typedef struct
{
    U16 u16ValueFormat;
    U16 u16ValueCount;
    LE_ValueRecord_t asValueRecord[LE_ARRAY_NUM];
} LE_SingleAdjPositionFormat2_t;

typedef struct
{
    U16 u16PosFormat;
    LE_Offset CoverageOffset;
    union
    {
        LE_SingleAdjPositionFormat1_t sData1;
        LE_SingleAdjPositionFormat2_t sData2;
    } usData;
} LE_SingleAdjPosition_t;
/*=============== SINGLE ADJUSTMENT POSITION End ==============*/

/*=============== PARI ADJUSTMENT POSITION Begin ==============*/
enum
{
    LE_PAIR_ADJ_POS_FORMAT_INVALID = 0,
    LE_PAIR_ADJ_POS_FORMAT_1 = 1,
    LE_PAIR_ADJ_POS_FORMAT_2 = 2
};
typedef U16 LE_PairAdjPositionFormat_e;

typedef struct
{
    LE_GlyphId SecondGlyph;
    LE_ValueRecord_t sValueRecord1;
    /* LE_ValueRecord_t sValueRecord2 -- ignore here */
} LE_PairValueRecord_t;

typedef struct
{
    U16 u16PairValueCount;
    LE_PairValueRecord_t asPairValueRecord[LE_ARRAY_NUM];
} LE_PairSetTable_t;

typedef struct
{
    U16 u16ValueFormat1;
    U16 u16ValueFormat2;
    U16 u16PairSetCount;
    LE_Offset aPairSetTableOffset[LE_ARRAY_NUM];
} LE_PairAdjPositionFormat1_t;

typedef struct
{
    LE_ValueRecord_t sValueRecord1;
    /* LE_ValueRecord_t sValueRecord2 -- ignore here */
} LE_Class2Record;

typedef struct
{
    LE_Class2Record asClass2Record[LE_ARRAY_NUM];
} LE_Class1Record;

typedef struct
{
    U16 u16ValueFormat1;
    U16 u16ValueFormat2;
    LE_Offset ClassDef1Offset;
    LE_Offset ClassDef2Offset;
    U16 u16Class1Count;
    U16 u16Class2Count;
    LE_Class1Record asClass1Record[LE_ARRAY_NUM];
} LE_PairAdjPositionFormat2_t;

typedef struct
{
    U16 u16PosFormat;
    LE_Offset CoverageOffset;
    union
    {
        LE_PairAdjPositionFormat1_t sData1;
        LE_PairAdjPositionFormat2_t sData2;
    } usData;
} LE_PairAdjPosition_t;
/*=============== PAIR ADJUSTMENT POSITION End ==============*/

/*=============== CURSIVE ATTACHMENT POSITION Begin ==============*/
typedef struct
{
    LE_Offset EntryAnchor;
    LE_Offset ExitAnchor;
} LE_EntryExitRecord_t;
#define LE_EntryExitRecord_Size (sizeof(LE_Offset) + sizeof(LE_Offset))

typedef struct
{
    U16 u16PosFormat;
    LE_Offset CoverageOffset;
    U16 u16EntryExitCount;
    LE_EntryExitRecord_t asEntryExitRecords[LE_ARRAY_NUM];
} LE_CursiveAttPosition_t;
/*=============== CURSIVE ATTACHMENT  POSITION End ==============*/

typedef struct
{
    LE_Offset BaseCoverageTableOffset;
    U16 u16ClassCount;
    LE_Offset MarkArrayOffset;
    LE_Offset BaseArrayOffset;
} LE_AttachmentPositionTable_t;

/*=============== MARKTOBASE ATTACHMENT POSITION Begin ==============*/
typedef struct
{
    LE_Offset aBaseAnchorTableOffset[LE_ARRAY_NUM];
} LE_BaseRecord_t;

typedef struct
{
    S16 s16BaseRecordCount;
    LE_BaseRecord_t asBaseRecord[LE_ARRAY_NUM];
} LE_BaseArray_t;

typedef struct
{
    U16 u16PosFormat;
    LE_Offset MarkCoverageOffset;
    LE_Offset BaseCoverageOffset;
    U16 u16ClassCount;
    LE_Offset MarkArrayOffset;
    LE_Offset BaseArrayOffset;
} LE_MarkToBaseAttPositionTable_t;
/*=============== MARKTOBASE ATTACHMENT  POSITION End ==============*/

/*=============== MARKTOLIGATURE ATTACHMENT POSITION Begin ==============*/
typedef struct
{
    LE_Offset as32LigatureAnchorTableOffset[LE_ARRAY_NUM];
} LE_ComponentRecord_t;

typedef struct
{
    U16 u16ComponentCount;
    LE_ComponentRecord_t asComponentRecord[LE_ARRAY_NUM];
} LE_LigatureAttachTable_t;

typedef struct
{
    U16 u16LigatureCount;
    LE_Offset aLigatureAttachTableOffset[LE_ARRAY_NUM];
} LE_LigatureArray_t;

typedef struct
{
    U16 u16PosFormat;
    LE_Offset MarkCoverageOffset;
    LE_Offset LigatureCoverageOffset;
    U16 u16ClassCount;
    LE_Offset MarkArrayOffset;
    LE_Offset LigatureArrayOffset;
} LE_MarkToLigatureAttPositionTable_t;
/*=============== MARKTOLIGATURE ATTACHMENT  POSITION End ==============*/

/*=============== MARKTOMARK ATTACHMENT POSITION Begin ==============*/
typedef struct
{
    LE_Offset aMark2AnchorTableOffset[LE_ARRAY_NUM];
} LE_Mark2Record_t;

typedef struct
{
    U16 u16Mark2RecordCount;
    LE_Mark2Record_t asMark2Record[LE_ARRAY_NUM];
} LE_Mark2Array_t;

typedef struct
{
    U16 u16PosFormat;
    LE_Offset Mark1CoverageOffset;
    LE_Offset Mark2CoverageOffset;
    U16 u16ClassCount;
    LE_Offset Mark1ArrayOffset;
    LE_Offset Mark2ArrayOffset;
} LE_MarkToMarkAttPositionTable_t;
/*=============== MARKTOMARK ATTACHMENT  POSITION End ==============*/

typedef struct
{
    S32 s32XPlacementAdjustment;
    S32 s32YPlacementAdjustment;
    S32 s32XAdvanceAdjustment;
    S32 s32YAdvanceAdjustment;
    LE_Points_t sEntryAnchor;
    LE_Points_t sExitAnchor;
} LE_PosInf_t;

typedef struct
{
    LE_ProcessPosHeader_t sHeader;
    LE_ScriptTag_e eScript;
    LE_ScriptTag_e eScriptV2;
    LE_LanguageTag_e eLang;
    U16 u16FeatureCount;
    U16 aFeatureIndices[HINDI_MAX_FEATURE_NUM];
    const U8 *pGPOS;
    const U8 *pClassDefTable;
    const U8 *pMarkAttachClassDefTable;
    LE_FontInstanceInf_t sFontInstanceInf;
    LE_PosInf_t sPosInf;
    LE_PosInf_t sNextPosInf;
} LE_GPOSProcess_t;

BOOLEAN msAPI_MLE_LeProcessPosLookupTable( LE_GPOSProcess_t *psProcess, const U8 *pLookupTable, U16 u16SubtableIndex, U16 u16Position );
const U8* msAPI_MLE_LePosGetScriptListTable( const U8 *pPosTable );
const U8* msAPI_MLE_LePosGetFeatureListTable( const U8 *pPosTable );
const U8* msAPI_MLE_LePosGetLookupListTable( const U8 *pPosTable );

#endif //__FEATURE_VECTOR_FONT__
#endif //__MSAPI_MLE_LE_OTF_POS_H__
