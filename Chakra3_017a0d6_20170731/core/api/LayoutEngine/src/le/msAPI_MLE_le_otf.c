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


#ifndef __MSAPI_MLE_LE_OTF_C__
#define __MSAPI_MLE_LE_OTF_C__

#ifdef __FEATURE_VECTOR_FONT__
/******************************/
/*        INCLUDE             */
/******************************/
#include "msAPI_MLE_common_def.h"

#include "msAPI_MLE_le_types.h"
#include "msAPI_MLE_le_otf_common.h"

#include "msAPI_MLE_le_otf_subst.h"
#include "msAPI_MLE_le_otf_pos.h"
#include "msAPI_MLE_le_otf_def.h"

#include "msAPI_MLE_le_otf.h"

//extern const const U8 g_LeGlyphSubstitutionTable[];
//extern const U8 g_LeGlyphClassDefinitionTable[];

typedef struct
{
    LE_ScriptTag_e eTagValue;
    LE_OTF_ScriptTag_e eTag;
} _leScriptMap_t;

static const _leScriptMap_t _g_scriptMap[] =
{
    {LE_SCRIPT_TAG_DEVA, LE_OTF_SCRIPT_DEVA},// 0
    {LE_SCRIPT_TAG_BENG, LE_OTF_SCRIPT_BENG},// 1
    {LE_SCRIPT_TAG_GUJR, LE_OTF_SCRIPT_GUJR},// 2
    {LE_SCRIPT_TAG_ORYA, LE_OTF_SCRIPT_ORYA},// 3
    {LE_SCRIPT_TAG_TAML, LE_OTF_SCRIPT_TAML},// 4
    {LE_SCRIPT_TAG_TELU, LE_OTF_SCRIPT_TELU},// 5
    {LE_SCRIPT_TAG_KNDA, LE_OTF_SCRIPT_KNDA},// 6
    {LE_SCRIPT_TAG_MLYM, LE_OTF_SCRIPT_MLYM},// 7
    {LE_SCRIPT_TAG_GURU, LE_OTF_SCRIPT_GURU},// 8
    {LE_SCRIPT_TAG_SINH, LE_OTF_SCRIPT_SINH},// 9
    {LE_SCRIPT_TAG_MYM2, LE_OTF_SCRIPT_MYMR},// 10
    {LE_SCRIPT_TAG_KHMR, LE_OTF_SCRIPT_KHMR},// 11
    {LE_SCRIPT_TAG_LAOO, LE_OTF_SCRIPT_LAOO},// 12
    {LE_SCRIPT_TAG_MYM2, LE_OTF_SCRIPT_MYMR_EXTA},// 13
    {LE_SCRIPT_TAG_MYM2, LE_OTF_SCRIPT_MYMR_EXTB},// 14
    {LE_SCRIPT_TAG_KHMR, LE_OTF_SCRIPT_KHMR_DIGIT1},// 15
    {LE_SCRIPT_TAG_KHMR, LE_OTF_SCRIPT_KHMR_DIGIT2},// 16
    {LE_SCRIPT_TAG_KHMR, LE_OTF_SCRIPT_KHMR_SYMBOLS},// 17
};

static LE_ScriptTag_e _msAPI_MLE_LeMapScriptTag(LE_OTF_ScriptTag_e eScript)
{
    U8 i;
    LE_ScriptTag_e eScriptTag = LE_SCRIPT_TAG_NULL;

    if ( eScript > LE_OTF_MAX_SCRIPT_NUM )//fix coverity 203937
    {
        return LE_FEATURE_TAG_NULL;
    }

     for ( i = 0; i < LE_OTF_MAX_SCRIPT_NUM; i++ )
     {
        if ( _g_scriptMap[i].eTag == eScript )
        {
            eScriptTag = _g_scriptMap[i].eTagValue;
            break;
        }
     }

     return eScriptTag;
}

static LE_ScriptTag_e _msAPI_MLE_LeMapScriptTagV2(LE_ScriptTag_e eScriptTag)
{
    LE_ScriptTag_e eV2Tag = LE_SCRIPT_TAG_NULL;

    switch(eScriptTag)
    {
    case LE_SCRIPT_TAG_DEVA:
        eV2Tag = LE_SCRIPT_TAG_DEV2;
        break;
    case LE_SCRIPT_TAG_BENG:
        eV2Tag = LE_SCRIPT_TAG_BNG2;
        break;
    case LE_SCRIPT_TAG_GUJR:
        eV2Tag = LE_SCRIPT_TAG_GJR2;
        break;
    case LE_SCRIPT_TAG_ORYA:
        eV2Tag = LE_SCRIPT_TAG_ORY2;
        break;
    case LE_SCRIPT_TAG_TAML:
        eV2Tag = LE_SCRIPT_TAG_TML2;
        break;
    case LE_SCRIPT_TAG_TELU:
        eV2Tag = LE_SCRIPT_TAG_TEL2;
        break;
    case LE_SCRIPT_TAG_KNDA:
        eV2Tag = LE_SCRIPT_TAG_KND2;
        break;
    case LE_SCRIPT_TAG_MLYM:
        eV2Tag = LE_SCRIPT_TAG_MLM2;
        break;
    case LE_SCRIPT_TAG_GURU:
        eV2Tag = LE_SCRIPT_TAG_GUR2;
        break;
    case LE_SCRIPT_TAG_SINH:        //This language doesn't have v2 version
    case LE_SCRIPT_TAG_MYM2:
    default:
        break;
    }

    return eV2Tag;
}

typedef struct
{
    LE_FeatureTag_e eTagValue;
    LE_OTF_FeatureTag_e eTag;
} _leFeatureMap_t;

static const _leFeatureMap_t _g_freturnMap[] =
{
    {LE_FEATURE_TAG_LOCL, LE_OTF_FEATURE_LOCL},
    {LE_FEATURE_TAG_INIT, LE_OTF_FEATURE_INIT},
    {LE_FEATURE_TAG_NUKT, LE_OTF_FEATURE_NUKT},
    {LE_FEATURE_TAG_AKHN, LE_OTF_FEATURE_AKHN},
    {LE_FEATURE_TAG_RPHF, LE_OTF_FEATURE_RPHF},
    {LE_FEATURE_TAG_BLWF, LE_OTF_FEATURE_BLWF},
    {LE_FEATURE_TAG_HALF, LE_OTF_FEATURE_HALF},
    {LE_FEATURE_TAG_PSTF, LE_OTF_FEATURE_PSTF},
    {LE_FEATURE_TAG_VATU, LE_OTF_FEATURE_VATU},
    {LE_FEATURE_TAG_PRES, LE_OTF_FEATURE_PRES},
    {LE_FEATURE_TAG_BLWS, LE_OTF_FEATURE_BLWS},
    {LE_FEATURE_TAG_ABVS, LE_OTF_FEATURE_ABVS},
    {LE_FEATURE_TAG_PSTS, LE_OTF_FEATURE_PSTS},
    {LE_FEATURE_TAG_HALN, LE_OTF_FEATURE_HALN},
    {LE_FEATURE_TAG_BLWM, LE_OTF_FEATURE_BLWM},
    {LE_FEATURE_TAG_ABVM, LE_OTF_FEATURE_ABVM},
    {LE_FEATURE_TAG_DIST, LE_OTF_FEATURE_DIST},
    {LE_FEATURE_TAG_RKRF, LE_OTF_FEATURE_RKRF},
    {LE_FEATURE_TAG_CJCT, LE_OTF_FEATURE_CJCT},
    {LE_FEATURE_TAG_CALT, LE_OTF_FEATURE_CALT},
    {LE_FEATURE_TAG_KERN, LE_OTF_FEATURE_KERN},
    {LE_FEATURE_TAG_PREF, LE_OTF_FEATURE_PREF},
    {LE_FEATURE_TAG_MARK, LE_OTF_FEATURE_MARK},
    {LE_FEATURE_TAG_MKMK, LE_OTF_FEATURE_MKMK},
    {LE_FEATURE_TAG_CLIG, LE_OTF_FEATURE_CLIG},//fix coverity 203938
    {LE_FEATURE_TAG_RLIG, LE_OTF_FEATURE_RLIG},
    {LE_FEATURE_TAG_LIGA, LE_OTF_FEATURE_LIGA},
};

static LE_FeatureTag_e _msAPI_MLE_LeMapFeatureTag( LE_OTF_FeatureTag_e eFeature )
{
    U8 i;
    LE_FeatureTag_e eFeatureTag = LE_FEATURE_TAG_NULL;

    if ( eFeature > LE_OTF_MAX_FEATURE_NUM )
    {
        return LE_FEATURE_TAG_NULL;
    }

     for ( i = 0; i < LE_OTF_MAX_FEATURE_NUM; i++ )
     {
        if ( _g_freturnMap[i].eTag == eFeature )
        {
            eFeatureTag = _g_freturnMap[i].eTagValue;
            break;
        }
     }

     return eFeatureTag;
}

static BOOLEAN _msAPI_MLE_LeIsGposFeature( LE_OTF_FeatureTag_e eFeature )
{
    switch( eFeature )
    {
    case LE_OTF_FEATURE_DIST:
    case LE_OTF_FEATURE_BLWM:
    case LE_OTF_FEATURE_ABVM:
    case LE_OTF_FEATURE_KERN:
    case LE_OTF_FEATURE_MARK:
    case LE_OTF_FEATURE_MKMK:
        return TRUE;
        break;
    default:
        return FALSE;
        break;
    }
}

static BOOLEAN _msAPI_MLE_LeIsGsubFeature( LE_OTF_FeatureTag_e eFeature )
{
    if ( eFeature == LE_OTF_FEATURE_LOCL || eFeature == LE_OTF_FEATURE_INIT || eFeature == LE_OTF_FEATURE_NUKT
         || eFeature == LE_OTF_FEATURE_AKHN || eFeature == LE_OTF_FEATURE_RPHF || eFeature == LE_OTF_FEATURE_BLWF
         || eFeature == LE_OTF_FEATURE_HALF || eFeature == LE_OTF_FEATURE_PSTF || eFeature == LE_OTF_FEATURE_VATU
         || eFeature == LE_OTF_FEATURE_PRES || eFeature == LE_OTF_FEATURE_BLWS || eFeature == LE_OTF_FEATURE_ABVS
         || eFeature == LE_OTF_FEATURE_PSTS || eFeature == LE_OTF_FEATURE_HALN || eFeature == LE_OTF_FEATURE_RKRF
         || eFeature == LE_OTF_FEATURE_CJCT || eFeature == LE_OTF_FEATURE_CALT || eFeature == LE_OTF_FEATURE_PREF
         || eFeature == LE_OTF_FEATURE_LIGA || eFeature == LE_OTF_FEATURE_RLIG )
    {
        return TRUE;
    }

    return FALSE;
}

LE_GSUBProcess_t* msAPI_MLE_LeCreateGsubProcess( LE_OTF_ScriptTag_e eScript, LE_LanguageTag_e eLang, const U8 *pGSUB, const U8 *pGDEF )
{
    LE_GSUBProcess_t *pGSUBProcess = NULL;

    if ( pGSUB == NULL )
    {
        return NULL;
    }

    pGSUBProcess = (LE_GSUBProcess_t *)MALLOC(sizeof(LE_GSUBProcess_t));
    if ( pGSUBProcess == NULL )
    {
        return NULL;
    }

    MEMSET(pGSUBProcess, 0, sizeof(LE_GSUBProcess_t));

    pGSUBProcess->sHeader.eType = LE_VECTOR_TYPE_OTF;
    pGSUBProcess->eScript = _msAPI_MLE_LeMapScriptTag(eScript);
    pGSUBProcess->eScriptV2 = _msAPI_MLE_LeMapScriptTagV2(pGSUBProcess->eScript);
    pGSUBProcess->eLang = eLang;
    pGSUBProcess->pGSUB = pGSUB;

    if ( pGDEF )
    {
        pGSUBProcess->pClassDefTable = msAPI_MLE_LeGDEFGetClassDefinitionTable(pGDEF);
        pGSUBProcess->pMarkAttachClassDefTable = msAPI_MLE_LeGDEFGetMarkAttachClassDefinitionTable(pGDEF);
    }
    else
    {
        pGSUBProcess->pClassDefTable = NULL;
        pGSUBProcess->pMarkAttachClassDefTable = NULL;
    }

    return pGSUBProcess;
}

void msAPI_MLE_LeFreeGsubProcess( U8 *psProcess )
{
    LE_GSUBProcess_t *psTempProcess = (LE_GSUBProcess_t *)((void *)psProcess);

    if ( psProcess == NULL )
    {
        return;
    }

    FREEIF(psTempProcess);
}

U16 msAPI_MLE_LeGsubProcessGlyphs( LE_GSUBProcess_t *psProcess, LE_LanguageTag_e eLang, const LE_OTF_FeatureRecord_t *pasFeatureMap, U16 u16FeatureMapSize, U32 u32FeatureTags )
{
    const U8 *pFeatureList = NULL;
    const U8 *pLookupList = NULL;
    const U8 *pu8ScriptTable = NULL;
    U16 i;

    if ( psProcess == NULL || psProcess->pGSUB == NULL || pasFeatureMap == NULL || u16FeatureMapSize == 0  )
    {
        return 0;
    }

    pu8ScriptTable = msAPI_MLE_LeFindScript(msAPI_MLE_LeSubstGetScriptListTable(psProcess->pGSUB), psProcess->eScript, psProcess->eScriptV2);
    if ( pu8ScriptTable == NULL )
    {
        return 0;
    }

    if ( msAPI_MLE_LeFindLangSysTable( pu8ScriptTable, eLang, &psProcess->u16FeatureCount, psProcess->aFeatureIndices ) == FALSE )
    {
        return 0;
    }

    pFeatureList = msAPI_MLE_LeSubstGetFeatureListTable(psProcess->pGSUB);
    if ( pFeatureList == NULL )
    {
        return 0;
    }

    pLookupList = msAPI_MLE_LeSubstGetLookupListTable(psProcess->pGSUB);
    if ( pLookupList == NULL )
    {
        return 0;
    }

    for ( i = 0; i < u16FeatureMapSize; i++ )
    {
        const LE_OTF_FeatureRecord_t *pTempFeatureRecord = &pasFeatureMap[i];

        if ( (u32FeatureTags & pTempFeatureRecord->u32Mask) && _msAPI_MLE_LeIsGsubFeature(pTempFeatureRecord->eTag) )
        {
            const U8 *pFeature = NULL;
            U16 *pau16LookupIndex = NULL;
            U16 u16LookupCount = 0;

            pFeature = msAPI_MLE_LeGetFeatureTable( psProcess->u16FeatureCount, psProcess->aFeatureIndices, pFeatureList, _msAPI_MLE_LeMapFeatureTag(pTempFeatureRecord->eTag), &u16LookupCount);
            if ( pFeature == NULL || u16LookupCount == 0 )
            {
                continue;
            }

            pau16LookupIndex = (U16 *)MALLOC(u16LookupCount * sizeof(U16));
            if ( msAPI_MLE_LeFeatureTableGetLookupIndexs(pFeature, pau16LookupIndex, u16LookupCount) )
            {
                U16 j;

                for ( j = 0; j < u16LookupCount; j++ )
                {
                    U16 k;
                    U16 u16SubtableCount = 0;
                    const U8 *pLookup = msAPI_MLE_LeLookupListTableGetLookupTable(pLookupList, pau16LookupIndex[j], &u16SubtableCount);

                    for ( k = 0; k < u16SubtableCount; k++ )
                    {
                        U16 u16OutGlyphLen = psProcess->sHeader.u16OutLen;
                        U16 u16RemainSize = u16OutGlyphLen;
                        U16 u16Index = 0;
                        U16 u16OutOffset = 0;

                        while( u16RemainSize )
                        {
                            U16 u16ProduceSize = 0;
                            BOOLEAN bMatched = FALSE;
                            LE_CharFeatures_e eCharFeatures;

                            eCharFeatures = LE_GET_GLYPH_FEATURE(psProcess->sHeader.pau32OutGlyph[u16Index]);

                            if ( (pTempFeatureRecord->eTag != LE_OTF_FEATURE_RPHF && pTempFeatureRecord->eTag != LE_OTF_FEATURE_BLWF && pTempFeatureRecord->eTag != LE_OTF_FEATURE_HALN && pTempFeatureRecord->eTag != LE_OTF_FEATURE_HALF && pTempFeatureRecord->eTag != LE_OTF_FEATURE_CJCT)
                                 || (pTempFeatureRecord->eTag == LE_OTF_FEATURE_RPHF && (eCharFeatures & LE_CHAR_FEATURE_RPHF))
                                 || (pTempFeatureRecord->eTag == LE_OTF_FEATURE_BLWF && (eCharFeatures & LE_CHAR_FEATURE_BLWF))
                                 || (pTempFeatureRecord->eTag == LE_OTF_FEATURE_HALN && (eCharFeatures & LE_CHAR_FEATURE_HALN))
                                 || (pTempFeatureRecord->eTag == LE_OTF_FEATURE_ABVS && (eCharFeatures & LE_CHAR_FEATURE_ABVS))
                                 || ((pTempFeatureRecord->eTag == LE_OTF_FEATURE_HALF) && !(eCharFeatures & LE_CHAR_FEATURE_HALN) && !(eCharFeatures & LE_CHAR_FEATURE_NO_HALF))       //LE_CHAR_FEATURE_NO_HALF is a invert logic
                                 || ((pTempFeatureRecord->eTag == LE_OTF_FEATURE_CJCT) && !(eCharFeatures & LE_CHAR_FEATURE_HALN)) )
                            {
                                if ( (pTempFeatureRecord->eTag != LE_OTF_FEATURE_INIT) || (u16Index == 0) )
                                {
                                    bMatched = msAPI_MLE_LeProcessSubstLookupTable(psProcess, pLookup, k, u16Index);
                                }
                            }

                            if ( bMatched )
                            {
                                u16OutGlyphLen = psProcess->sHeader.u16OutLen;
                                if ( u16OutGlyphLen > 0 )
                                {
                                    u16ProduceSize = psProcess->sHeader.u16Produced;
                                }
                                else
                                {
                                    u16ProduceSize = 1;
                                }

                                u16RemainSize = u16OutGlyphLen - u16OutOffset;
                            }
                            else
                            {
                                u16ProduceSize = 1;
                                u16Index = u16Index + u16ProduceSize;
                                u16OutOffset = u16OutOffset + u16ProduceSize;
                                u16RemainSize = u16OutGlyphLen - u16OutOffset;
                            }
                        }
                    }
                }
            }
            FREEIF(pau16LookupIndex);
        }
    }

    return psProcess->sHeader.u16OutLen;
}

LE_GPOSProcess_t* msAPI_MLE_LeCreateGposProcess( LE_OTF_ScriptTag_e eScript, LE_LanguageTag_e eLang, const U8 *pGPOS, const U8 *pGDEF, LE_FontInstanceInf_t *psFontInf )
{
    LE_GPOSProcess_t *pGPOSProcess = NULL;

    if ( pGPOS == NULL || psFontInf == NULL )
    {
        return NULL;
    }

    pGPOSProcess = (LE_GPOSProcess_t *)MALLOC(sizeof(LE_GPOSProcess_t));
    if ( pGPOSProcess == NULL )
    {
        return NULL;
    }

    MEMSET(pGPOSProcess, 0, sizeof(LE_GPOSProcess_t));

    pGPOSProcess->sHeader.eType = LE_VECTOR_TYPE_OTF;
    pGPOSProcess->eScript = _msAPI_MLE_LeMapScriptTag(eScript);
    pGPOSProcess->eScriptV2 = _msAPI_MLE_LeMapScriptTagV2(pGPOSProcess->eScript);
    pGPOSProcess->eLang =  eLang;
    pGPOSProcess->pGPOS = pGPOS;

    pGPOSProcess->sFontInstanceInf = (*psFontInf);

    if ( pGDEF )
    {
        pGPOSProcess->pClassDefTable = msAPI_MLE_LeGDEFGetClassDefinitionTable(pGDEF);
        pGPOSProcess->pMarkAttachClassDefTable = msAPI_MLE_LeGDEFGetMarkAttachClassDefinitionTable(pGDEF);
    }
    else
    {
        pGPOSProcess->pClassDefTable = NULL;
        pGPOSProcess->pMarkAttachClassDefTable = NULL;
    }

    return pGPOSProcess;
}

void msAPI_MLE_LeFreeGposProcess( U8 *psProcess )
{
    LE_GPOSProcess_t *psTempProcess = (LE_GPOSProcess_t *)((void *)psProcess);

    if ( psProcess == NULL )
    {
        return;
    }

    FREEIF(psTempProcess);
}

BOOLEAN msAPI_MLE_LeGposProcessGlyphs( LE_GPOSProcess_t *psProcess, LE_LanguageTag_e eLang, const LE_OTF_FeatureRecord_t *pasFeatureMap, U16 u16FeatureMapSize, U32 u32FeatureTags )
{
    const U8 *pFeatureList = NULL;
    const U8 *pLookupList = NULL;
    const U8 *pu8ScriptTable = NULL;
    U16 i;
    BOOLEAN bResult = FALSE;
    BOOLEAN bMatched = FALSE;

    if ( psProcess == NULL || psProcess->pGPOS == NULL  )
    {
        return FALSE;
    }

    pu8ScriptTable = msAPI_MLE_LeFindScript(msAPI_MLE_LePosGetScriptListTable(psProcess->pGPOS), psProcess->eScript, psProcess->eScriptV2);
    if ( pu8ScriptTable == NULL )
    {
        return FALSE;
    }

    if ( msAPI_MLE_LeFindLangSysTable( pu8ScriptTable, eLang, &psProcess->u16FeatureCount, psProcess->aFeatureIndices ) == FALSE )
    {
        return FALSE;
    }

    pFeatureList = msAPI_MLE_LePosGetFeatureListTable(psProcess->pGPOS);
    if ( pFeatureList == NULL )
    {
        return FALSE;
    }

    pLookupList = msAPI_MLE_LePosGetLookupListTable(psProcess->pGPOS);
    if ( pLookupList == NULL )
    {
        return FALSE;
    }

    for ( i = 0; i < u16FeatureMapSize; i++ )
    {
        const LE_OTF_FeatureRecord_t *pTempFeatureRecord = &pasFeatureMap[i];

        if ( (u32FeatureTags & pTempFeatureRecord->u32Mask) && _msAPI_MLE_LeIsGposFeature(pTempFeatureRecord->eTag) )
        {
            const U8 *pFeature = NULL;
            U16 *pau16LookupIndex = NULL;
            U16 u16LookupCount = 0;

            pFeature = msAPI_MLE_LeGetFeatureTable( psProcess->u16FeatureCount, psProcess->aFeatureIndices, pFeatureList, _msAPI_MLE_LeMapFeatureTag(pTempFeatureRecord->eTag), &u16LookupCount);
            if ( pFeature == NULL || u16LookupCount == 0 )
            {
                continue;
            }

            pau16LookupIndex = (U16 *)MALLOC(u16LookupCount * sizeof(U16));
            if ( msAPI_MLE_LeFeatureTableGetLookupIndexs(pFeature, pau16LookupIndex, u16LookupCount) )
            {
                U16 j;

                for ( j = 0; j < u16LookupCount; j++ )
                {
                    U16 k;
                    U16 u16SubtableCount = 0;
                    const U8 *pLookup = msAPI_MLE_LeLookupListTableGetLookupTable(pLookupList, pau16LookupIndex[j], &u16SubtableCount);

                    for ( k = 0; k < u16SubtableCount; k++ )
                    {
                        bResult = msAPI_MLE_LeProcessPosLookupTable(psProcess, pLookup, k, psProcess->sHeader.u16NextOffset);
                        if ( bResult )
                        {
                            bMatched = TRUE;
                            break;
                        }
                    }

                    if ( bMatched )
                    {
                        break;
                    }
                }
            }
            FREEIF(pau16LookupIndex);

            if ( bMatched )
            {
                break;
            }
        }
    }

    return bMatched;
}

#endif //__FEATURE_VECTOR_FONT__

#endif //__MSAPI_MLE_LE_OTF_C__
