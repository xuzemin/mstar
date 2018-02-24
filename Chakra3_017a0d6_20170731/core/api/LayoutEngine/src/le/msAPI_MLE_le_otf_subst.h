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

#ifndef __MSAPI_MLE_LE_OTF_SUBST_H__
#define __MSAPI_MLE_LE_OTF_SUBST_H__

#ifdef __FEATURE_VECTOR_FONT__

#include "msAPI_MLE_le_util.h"
#include "msAPI_MLE_le_otf_types.h"
#include "msAPI_MLE_font_hindi_priv.h"

typedef struct
{
    LE_Version u32Version;
    LE_Offset ScriptListOffset;
    LE_Offset FeatureListOffset;
    LE_Offset LookupListOffset;
} LE_GSUBTable_t;

enum
{
    LE_SUBST_LOOKUP_INVALID = 0,
    LE_SUBST_LOOKUP_SINGLE = 1,
    LE_SUBST_LOOKUP_MULTIPLE = 2,
    LE_SUBST_LOOKUP_ALTERNATE = 3,
    LE_SUBST_LOOKUP_LIGATURE = 4,
    LE_SUBST_LOOKUP_CONTEXT = 5,
    LE_SUBST_LOOKUP_CHAINING_CONTEXT = 6,
    LE_SUBST_LOOKUP_EXTENSION = 7
};
typedef U16 LE_SubstitutionLookupType_e;

/*=============== SINGLE SUBSTITUTION Begin ==============*/
enum
{
    LE_SINGLE_SUBST_FORMAT_INVALID = 0,
    LE_SINGLE_SUBST_FORMAT_1 = 1,
    LE_SINGLE_SUBST_FORMAT_2 = 2
};
typedef U16 LE_SingleSubstitutionFormat_e;

typedef struct
{
    S16 s16DeltaGlyphID;
} LE_SingleSubstitutionFormat1_t;

typedef struct
{
    U16 u16GlyphCount;
    LE_GlyphId asubst[LE_ARRAY_NUM/*u16GlyphCount*/];
} LE_SingleSubstitutionFormat2_t;

typedef struct
{
    U16 u16SubstFormat;
    LE_Offset CoverageOffset;
    union
    {
        LE_SingleSubstitutionFormat1_t sData1;
        LE_SingleSubstitutionFormat2_t sData2;
    } usData;
} LE_SingleSubstitution_t;
/*=============== SINGLE SUBSTITUTION End ==============*/

/*=============== MULTIPLE SUBSTITUTION Begin ==============*/
typedef struct
{
    U16 u16GlyphCount;
    LE_GlyphId aSubst[LE_ARRAY_NUM/*u16GlyphCount*/];
} LE_SequenceTable_t;

typedef struct
{
    U16 u16SubstFormat;
    LE_Offset CoverageOffset;
    U16 u16SeqCount;
    LE_Offset aSeqTableOffset[LE_ARRAY_NUM/*u16SeqCount*/];
} LE_MultipleSubstitution_t;
/*=============== MULTIPLE SUBSTITUTION End ==============*/

/*=============== ALTERNATE SUBSTITUTION Begin ==============*/
typedef struct
{
    U16 u16GlyphCount;
    LE_GlyphId aAlternate[LE_ARRAY_NUM/*u16GlyphCount*/];
} LE_AlternateSetTable_t;

typedef struct
{
    U16 u16SubstFormat;
    LE_Offset CoverageOffset;
    U16 u16AltSetCount;
    LE_Offset aAltSetTableOffset[LE_ARRAY_NUM/*u16AltSetCount*/];
} LE_AlternateSubstitution_t;
/*=============== ALTERNATE SUBSTITUTION End ==============*/

/*=============== LIGATURE SUBSTITUTION Begin ==============*/
typedef struct
{
    LE_GlyphId LigGlyph;
    U16 u16CompCount;
    LE_GlyphId aComponent[LE_ARRAY_NUM/*u16CompCount*/];
} LE_LigatureTable_t;

typedef struct
{
    U16 u16LigCount;
    LE_Offset aLigTableOffset[LE_ARRAY_NUM/*u16LigCount*/];
} LE_LigatureSetTable_t;

typedef struct
{
    U16 u16SubstFormat;
    LE_Offset CoverageOffset;
    U16 u16LigSetCount;
    LE_Offset aLigSetTableOffset[LE_ARRAY_NUM];
} LE_LigatureSubstitution_t;
/*=============== LIGATURE SUBSTITUTION End ==============*/

typedef struct
{
    LE_ProcessSubstHeader_t sHeader;
    LE_ScriptTag_e eScript;
    LE_ScriptTag_e eScriptV2;
    LE_LanguageTag_e eLang;
    U16 u16FeatureCount;
    U16 aFeatureIndices[HINDI_MAX_FEATURE_NUM];
    const U8 *pGSUB;
    const U8 *pClassDefTable;
    const U8 *pMarkAttachClassDefTable;
} LE_GSUBProcess_t;

BOOLEAN msAPI_MLE_LeProcessSubstLookupTable( LE_GSUBProcess_t *psProcess, const U8 *pLookupTable, U16 u16SubtableIndex, U16 u16Position );
const U8* msAPI_MLE_LeSubstGetScriptListTable( const U8 *pSubstTable );
const U8* msAPI_MLE_LeSubstGetFeatureListTable( const U8 *pSubstTable );
const U8* msAPI_MLE_LeSubstGetLookupListTable( const U8 *pSubstTable );

#endif //__FEATURE_VECTOR_FONT__
#endif //__MSAPI_MLE_LE_OTF_SUBST_H__   
