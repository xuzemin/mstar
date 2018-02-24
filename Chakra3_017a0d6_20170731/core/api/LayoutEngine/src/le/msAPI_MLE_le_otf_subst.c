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


#ifndef __MSAPI_MLE_LE_OTF_SUBST_C__
#define __MSAPI_MLE_LE_OTF_SUBST_C__

#ifdef __FEATURE_VECTOR_FONT__
/******************************/
/*        INCLUDE             */
/******************************/
#include "msAPI_MLE_common_def.h"

#include "msAPI_MLE_le_types.h"
#include "msAPI_MLE_le_otf_common.h"
#include "msAPI_MLE_le_otf_subst.h"

static BOOLEAN _msAPI_MLE_LeProcessSubstitutionLookupSubtable( LE_GSUBProcess_t *psProcess, LE_SubstitutionLookupType_e eLookupType, const U8 *pu8Subtable, U16 u16Position, LE_LookupFlag_e eLookupFlags );
static BOOLEAN _msAPI_MLE_LeProcessSubstitutionLookupTable( LE_GSUBProcess_t *psProcess, const U8 *pu8Table, U16 u16Position );

static BOOLEAN _msAPI_MLE_LeProcessSingleSubstitutionFormat1Table( LE_GSUBProcess_t *psProcess, const U8 *pu8Subtable, U16 u16Position, LE_LookupFlag_e eLookupFlags )
{
    const U8 *pFormat1 = pu8Subtable;
    const U8 *pConverage = NULL;
    U16 u16GlyphId = (U16)(-1);
    S32 s32CoverageIndex = -1;
    BOOLEAN bResult = FALSE;

    eLookupFlags = eLookupFlags;

    if ( psProcess == NULL || pu8Subtable == NULL )
    {
        return FALSE;
    }

    if ( u16Position >= psProcess->sHeader.u16OutLen )
    {
        return FALSE;
    }

    u16GlyphId = LE_GET_GLYPH_ID(psProcess->sHeader.pau32OutGlyph[u16Position]);

    pFormat1 = pFormat1 + sizeof(U16);
    pConverage = pu8Subtable + LE_GET_OFFSET(pFormat1);
    s32CoverageIndex = msAPI_MLE_LeGetGlyphCoverage(pConverage, u16GlyphId);

    pFormat1 = pFormat1 + sizeof(LE_Offset);
    if ( s32CoverageIndex >= 0 )
    {
        U16 u16Substitute = u16GlyphId + LE_GET_SHORT(pFormat1);

		//This is a patch to prevent upper layer API run into a dead lock status
		if ( u16GlyphId == u16Substitute )
			return FALSE;
		//Patch End

        //ignore, because some ligature graph are not define in GDEF
        //if ( psProcess->pClassDefTable )
        //{
        //  if ( msAPI_MLE_LeGetGlyphClass(psProcess->pClassDefTable, u16Substitute) >= 0 )
        //  {
        //      bResult = TRUE;
        //  }
        //}
        //else
        //{
            bResult = TRUE;
        //}

        if ( bResult )
        {
            psProcess->sHeader.u16Consumed = 1;
            psProcess->sHeader.u16Produced = 1;
            psProcess->sHeader.pau32OutGlyph[u16Position] = LE_SET_GLYPH_ID(psProcess->sHeader.pau32OutGlyph[u16Position], u16Substitute);
        }
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_LeProcessSingleSubstitutionFormat2Table( LE_GSUBProcess_t *psProcess, const U8 *pu8Subtable, U16 u16Position, LE_LookupFlag_e eLookupFlags )
{
    const U8 *pFormat2 = pu8Subtable;
    const U8 *pConverage = NULL;
    U16 u16GlyphId = (U16)(-1);
    S32 s32CoverageIndex = -1;
    BOOLEAN bResult = FALSE;

    eLookupFlags = eLookupFlags;

    if ( psProcess == NULL || pu8Subtable == NULL )
    {
        return FALSE;
    }

    if ( u16Position >= psProcess->sHeader.u16OutLen )
    {
        return FALSE;
    }

    u16GlyphId = LE_GET_GLYPH_ID(psProcess->sHeader.pau32OutGlyph[u16Position]);

    pFormat2 = pu8Subtable + sizeof(U16);
    pConverage = pu8Subtable + LE_GET_OFFSET(pFormat2);
    s32CoverageIndex = msAPI_MLE_LeGetGlyphCoverage(pConverage, u16GlyphId);

    pFormat2 = pFormat2 + sizeof(LE_Offset);
    if ( s32CoverageIndex >= 0 )
    {
        U16 u16Substitute;

        pFormat2 = pFormat2 + sizeof(U16);
        pFormat2 = pFormat2 + (s32CoverageIndex * sizeof(LE_GlyphId));
        u16Substitute = LE_GET_GLYPHID(pFormat2);

        //ignore, because some ligature graph are not define in GDEF
        //if ( psProcess->pClassDefTable )
        //{
        //  if ( msAPI_MLE_LeGetGlyphClass(psProcess->pClassDefTable, u16Substitute) >= 0 )
        //  {
        //      bResult = TRUE;
        //  }
        //}
        //else
        //{
            bResult = TRUE;
        //}

        if ( bResult )
        {
            psProcess->sHeader.pau32OutGlyph[u16Position] = LE_SET_GLYPH_ID(psProcess->sHeader.pau32OutGlyph[u16Position], u16Substitute);
            psProcess->sHeader.u16Produced = 1;
        }
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_LeProcessSingleSubstitutionTable( LE_GSUBProcess_t *psProcess, const U8 *pu8Subtable, U16 u16Position, LE_LookupFlag_e eLookupFlags )
{
    BOOLEAN bResult = FALSE;

    if ( pu8Subtable == NULL )
    {
        return FALSE;
    }

    switch( LE_GET_SHORT(pu8Subtable) )
    {
        case LE_SINGLE_SUBST_FORMAT_1:
        {
            bResult = _msAPI_MLE_LeProcessSingleSubstitutionFormat1Table(psProcess, pu8Subtable, u16Position, eLookupFlags);
            break;
        }

        case LE_SINGLE_SUBST_FORMAT_2:
        {
            bResult = _msAPI_MLE_LeProcessSingleSubstitutionFormat2Table(psProcess, pu8Subtable, u16Position, eLookupFlags);
            break;
        }

        case LE_SINGLE_SUBST_FORMAT_INVALID:
        default:
            break;
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_LeProcessMultipleSubstitutionTable( LE_GSUBProcess_t *psProcess, const U8 *pu8Subtable, U16 u16Position, LE_LookupFlag_e eLookupFlags )
{
    const U8 *pMultiple = pu8Subtable;
    const U8 *pConverage = NULL;
    U16 u16GlyphId = (U16)(-1);
    S32 s32CoverageIndex = -1;
    U16 u16SeqCount = 0;
    BOOLEAN bResult = FALSE;

    eLookupFlags = eLookupFlags;

    if ( psProcess == NULL || pu8Subtable == NULL )
    {
        return FALSE;
    }

    if ( u16Position >= psProcess->sHeader.u16OutLen )
    {
        return FALSE;
    }

    u16GlyphId = LE_GET_GLYPH_ID(psProcess->sHeader.pau32OutGlyph[u16Position]);
    //if ( psProcess->pClassDefTable && msAPI_MLE_LeGetGlyphClass(psProcess->pClassDefTable, u16GlyphId) < 0 )
    //{
    //    return FALSE;
    //}

    pMultiple = pMultiple + sizeof(U16);
    pConverage = pu8Subtable + LE_GET_OFFSET(pMultiple);
    s32CoverageIndex = msAPI_MLE_LeGetGlyphCoverage(pConverage, u16GlyphId);

    pMultiple = pMultiple + sizeof(LE_Offset);
    u16SeqCount = LE_GET_SHORT(pMultiple);

    if ( s32CoverageIndex >= 0 && s32CoverageIndex < u16SeqCount )
    {
        //S32 s32SeqOffset = (S32)pMultiple + sizeof(U16) + (u16SeqCount * sizeof(LE_Offset));
        //const U8 *pSequenceTable = pu8Subtable + LE_GET_OFFSET(s32SeqOffset);
        const U8 *pSequenceTable = pMultiple + sizeof(U16) + (u16SeqCount * sizeof(LE_Offset));
        U8 u8tempGlyphCount = 0,u8temp;
        for (u8temp = 0; u8temp < s32CoverageIndex; u8temp++)
        {
            u8tempGlyphCount = LE_GET_SHORT(pSequenceTable);
            pSequenceTable = pSequenceTable + sizeof(U16) + (u8tempGlyphCount * sizeof(U16));
        }
        U16 u16GlyphCount = LE_GET_SHORT(pSequenceTable);

        if ( u16GlyphCount > psProcess->sHeader.u16OutBufferSize )
        {
            return FALSE;
        }

        pSequenceTable = pSequenceTable + sizeof(U16);
        if ( u16GlyphCount == 0 )
        {
            psProcess->sHeader.pau32OutGlyph[u16Position] = LE_SET_GLYPH_ID(psProcess->sHeader.pau32OutGlyph[u16Position], u16GlyphId);
            psProcess->sHeader.u16Consumed = 1;
            psProcess->sHeader.u16Produced = 1;
            bResult = TRUE;
        }
        else if ( u16GlyphCount == 1 )
        {
            U16 u16Substitute = LE_GET_GLYPHID(pSequenceTable);

            bResult = TRUE;
            //if ( psProcess->pClassDefTable )
            //{
            //    if ( msAPI_MLE_LeGetGlyphClass(psProcess->pClassDefTable, u16Substitute) < 0 )
            //    {
            //      bResult = FALSE;
            //    }
            //}

            if ( bResult )
            {
                psProcess->sHeader.pau32OutGlyph[u16Position] = LE_SET_GLYPH_ID(psProcess->sHeader.pau32OutGlyph[u16Position], u16Substitute);
                psProcess->sHeader.u16Consumed = 1;
                psProcess->sHeader.u16Produced = 1;
            }
        }
        else
        {
            bResult = TRUE;
            //ignore, because some ligature graph are not define in GDEF
            //if ( psProcess->pClassDefTable )
            //{
            //    U16 i = 0;

            //  for ( i = 0; i < u16GlyphCount; i++ )
            //  {
            //      const U8 *pu8TempSequenceTable = (const U8 *)(pSequenceTable + (i * sizeof(LE_GlyphId)));
            //      U16 u16Substitute = LE_GET_GLYPHID(pu8TempSequenceTable);

            //        if ( msAPI_MLE_LeGetGlyphClass(psProcess->pClassDefTable, u16Substitute) < 0 )
            //      {
            //            bResult = FALSE;
            //        }
            //    }
            //}

            if ( bResult )
            {
                U16 i = 0;

                if ( psProcess->sHeader.u16OutBufferSize < psProcess->sHeader.u16OutLen )
                {
                    return FALSE;
                }

                //shift the rest composed inf at the end of array
                for ( i = psProcess->sHeader.u16OutLen - 1; i >= u16Position + 1; i-- )
                {
                    psProcess->sHeader.pau32OutGlyph[i + u16GlyphCount - 1] = psProcess->sHeader.pau32OutGlyph[i];
                    psProcess->sHeader.pau16ComposedSize[i + u16GlyphCount - 1] = psProcess->sHeader.pau16ComposedSize[i];
                }

                for ( i = 0; i < u16GlyphCount; i++ )
                {
                    const U8 *pu8TempSequenceTable = (const U8 *)(pSequenceTable + (i * sizeof(LE_GlyphId)));
                    psProcess->sHeader.pau32OutGlyph[i + u16Position] = LE_SET_GLYPH_ID(psProcess->sHeader.pau32OutGlyph[i + u16Position], LE_GET_GLYPHID(pu8TempSequenceTable));
                    if ( i > 0 )
                    {
                        psProcess->sHeader.pau16ComposedSize[i + u16Position] = 0;
                    }
                }

                psProcess->sHeader.u16Consumed = 1;
                psProcess->sHeader.u16Produced = u16GlyphCount;
                psProcess->sHeader.u16OutLen = psProcess->sHeader.u16OutLen - psProcess->sHeader.u16Consumed + psProcess->sHeader.u16Produced;

                if ( psProcess->sHeader.u16OffsetInOutput > u16Position )
                {
                    psProcess->sHeader.u16OffsetInOutput = psProcess->sHeader.u16OffsetInOutput - psProcess->sHeader.u16Consumed + u16GlyphCount;
                }
            }
        }
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_LeProcessAlternateSubstitutionTable( LE_GSUBProcess_t *psProcess, const U8 *pu8Subtable, U16 u16Position, LE_LookupFlag_e eLookupFlags )
{
    const U8 *pAlternate = pu8Subtable;
    const U8 *pConverage = NULL;
    U16 u16GlyphId = (U16)(-1);
    S32 s32CoverageIndex = -1;
    BOOLEAN bResult = FALSE;

    eLookupFlags = eLookupFlags;

    if ( psProcess == NULL || pu8Subtable == NULL )
    {
        return FALSE;
    }

    if ( u16Position >= psProcess->sHeader.u16OutLen )
    {
        return FALSE;
    }

    u16GlyphId = LE_GET_GLYPH_ID(psProcess->sHeader.pau32OutGlyph[u16Position]);

    pAlternate = pAlternate + sizeof(U16);
    pConverage = pu8Subtable + LE_GET_OFFSET(pAlternate);
    s32CoverageIndex = msAPI_MLE_LeGetGlyphCoverage(pConverage, u16GlyphId);

    pAlternate = pAlternate + sizeof(LE_Offset);
    if ( s32CoverageIndex >= 0 )
    {
        U16 u16AltSetCount = LE_GET_SHORT(pAlternate);

        pAlternate = pAlternate + sizeof(U16);
        if ( s32CoverageIndex < u16AltSetCount )
        {
            const U8 *pu8AlternateOffset = (const U8 *)(pAlternate + (s32CoverageIndex * sizeof(LE_Offset)));
            const U8 *pAlternateSetTable = pu8Subtable + LE_GET_OFFSET(pu8AlternateOffset);
            U16 u16Alternate;

            pAlternateSetTable = pAlternateSetTable + sizeof(U16);
            u16Alternate = LE_GET_GLYPHID(pAlternateSetTable);

            bResult = TRUE;
            //ignore, because some ligature graph are not define in GDEF
            //if ( psProcess->pClassDefTable )
            //{
            //    if ( msAPI_MLE_LeGetGlyphClass(psProcess->pClassDefTable, u16Alternate) < 0 )
            //    {
            //      bResult = FALSE;
            //    }
            //}

            if ( bResult )
            {
                psProcess->sHeader.u16Consumed = 1;
                psProcess->sHeader.u16Produced = 1;
                psProcess->sHeader.pau32OutGlyph[u16Position] = LE_SET_GLYPH_ID(psProcess->sHeader.pau32OutGlyph[u16Position], u16Alternate);
            }
        }
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_LeProcessLigatureSubstitutionTable( LE_GSUBProcess_t *psProcess, const U8 *pu8Subtable, U16 u16Position, LE_LookupFlag_e eLookupFlags )
{
    const U8 *pLigature = pu8Subtable;
    const U8 *pConverage = NULL;
    U16 u16GlyphId = (U16)(-1);
    S32 s32CoverageIndex = -1;
    BOOLEAN bResult = FALSE;

    if ( psProcess == NULL || pu8Subtable == NULL )
    {
        return FALSE;
    }

    if ( u16Position >= psProcess->sHeader.u16OutLen )
    {
        return FALSE;
    }

    u16GlyphId = LE_GET_GLYPH_ID(psProcess->sHeader.pau32OutGlyph[u16Position]);

    pLigature = pLigature + sizeof(U16);
    pConverage = pu8Subtable + LE_GET_OFFSET(pLigature);
    s32CoverageIndex = msAPI_MLE_LeGetGlyphCoverage(pConverage, u16GlyphId);

    pLigature = pLigature + sizeof(LE_Offset);
    if (s32CoverageIndex >= 0)
    {
        S32 s32LigOffset = (S32)pLigature + sizeof(U16) + (s32CoverageIndex * sizeof(LE_Offset));
        const U8 *pLigSetTable = pu8Subtable + LE_GET_OFFSET(s32LigOffset);
        U16 u16LigCount = LE_GET_SHORT(pLigSetTable);
        U16 i = 0;

        for ( i = 0; i < u16LigCount; i++ )
        {
            S32 s32LigTableOffset = (S32)pLigSetTable + sizeof(U16) + (i * sizeof(LE_Offset));
            const U8 *pLigTable = pLigSetTable + LE_GET_OFFSET(s32LigTableOffset);
            U16 u16CompCount;
            U16 u16LigGlyph;
            U16 j = 0;

            u16LigGlyph = LE_GET_GLYPHID(pLigTable);

            pLigTable = pLigTable + sizeof(LE_GlyphId);
            u16CompCount = LE_GET_SHORT(pLigTable) - 1;

            pLigTable = pLigTable + sizeof(U16);
            for ( j = 0; j < u16CompCount; j++ )
            {
                S32 s32ComponOffset = (S32)pLigTable + (j * sizeof(LE_GlyphId));
                U16 u16CompOffset = u16Position + j + 1;
                U16 u16ComponGlyphId = msAPI_MLE_LeGlyphStrGetNext(psProcess->sHeader.pau32OutGlyph, psProcess->sHeader.u16OutLen, u16Position, (j + 1), NULL, psProcess->pClassDefTable, eLookupFlags, TRUE);

                if ( u16CompOffset >= psProcess->sHeader.u16OutLen )
                {
                    break;
                }

                if ( u16ComponGlyphId != LE_GET_GLYPHID(s32ComponOffset) )
                {
                    break;
                }
            }

            if ( j == u16CompCount )
            {
                u16CompCount = u16CompCount + 1; //include the current position glyph
                bResult = TRUE;

                //check ligature glyph is exist
                //ignore, because some ligature graph are not define in GDEF
                //if ( psProcess->pClassDefTable )
                //{
                //    if ( msAPI_MLE_LeGetGlyphClass(psProcess->pClassDefTable, u16LigGlyph) < 0 )
                //    {
                //        bResult = FALSE;
                //    }
                //}

                if ( bResult )
                {
                    U16 u16TempComposedSize = 0;

                    psProcess->sHeader.pau32OutGlyph[u16Position] = LE_SET_GLYPH_ID(psProcess->sHeader.pau32OutGlyph[u16Position], u16LigGlyph);

                    for ( i = 0; i < u16CompCount; i++ )
                    {
                        psProcess->sHeader.pau32OutGlyph[u16Position] = psProcess->sHeader.pau32OutGlyph[u16Position] | (psProcess->sHeader.pau32OutGlyph[u16Position + i] & LE_GLYPH_FEATURE_MASK);
                        if ( psProcess->sHeader.u16OffsetInOutput == (u16Position + i) )
                        {
                            psProcess->sHeader.u16OffsetInConposed = psProcess->sHeader.u16OffsetInConposed + u16TempComposedSize;
                        }

                        u16TempComposedSize = u16TempComposedSize + psProcess->sHeader.pau16ComposedSize[i + u16Position];
                    }
                    psProcess->sHeader.pau16ComposedSize[u16Position] = u16TempComposedSize;

                    //shift the rest to left
                    for ( i = u16Position + u16CompCount; i < psProcess->sHeader.u16OutLen; i++ )
                    {
                        psProcess->sHeader.pau32OutGlyph[i - u16CompCount + 1] = psProcess->sHeader.pau32OutGlyph[i];
                        psProcess->sHeader.pau16ComposedSize[i - u16CompCount + 1] = psProcess->sHeader.pau16ComposedSize[i];
                    }

                    psProcess->sHeader.u16Consumed = u16CompCount;
                    psProcess->sHeader.u16Produced = 1;
                    psProcess->sHeader.u16OutLen = psProcess->sHeader.u16OutLen - psProcess->sHeader.u16Consumed + psProcess->sHeader.u16Produced;

                    if ( psProcess->sHeader.u16OffsetInOutput > u16Position )
                    {
                        if ( psProcess->sHeader.u16OffsetInOutput >= u16Position + u16CompCount )
                        {
                            psProcess->sHeader.u16OffsetInOutput = psProcess->sHeader.u16OffsetInOutput - u16CompCount + psProcess->sHeader.u16Produced;
                        }
                        else
                        {
                            psProcess->sHeader.u16OffsetInOutput = u16Position;
                        }
                    }
                }
            }

        }
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_LeProcessSubstitutionLookups( LE_GSUBProcess_t *psProcess, const U8 *paLookupRecord, U16 u16LookupRecordCount, U16 u16Position )
{
    const U8 *pLookupList;
    S32 s32LookupListOffset;
    U16 u16LoookupListCount = 0;
    U16 u16TempCusumeSize = 0;
    U16 i;
    BOOLEAN bMatched = FALSE;
    BOOLEAN bResult = FALSE;

    if ( psProcess == NULL || paLookupRecord == NULL || u16LookupRecordCount == 0 )
    {
        return FALSE;
    }

    s32LookupListOffset = (S32)psProcess->pGSUB + sizeof(LE_Version) + sizeof(LE_Offset) + sizeof(LE_Offset);

    pLookupList = psProcess->pGSUB + LE_GET_SHORT(s32LookupListOffset);
    u16LoookupListCount = LE_GET_SHORT(pLookupList);

    for ( i = 0; i < u16LookupRecordCount; i++ )
    {
        const U8 *pLookupRecord = paLookupRecord + (i * LE_LookupRecord_Size);
        U16 u16SequenceIndex;
        U16 u16LookupListIndex;

        u16SequenceIndex = LE_GET_SHORT(pLookupRecord);

        pLookupRecord = pLookupRecord + sizeof(U16);
        u16LookupListIndex = LE_GET_SHORT(pLookupRecord);

        if ( u16LookupListIndex < u16LoookupListCount )
        {
            S32 s32LookupTableOffset = (S32)pLookupList + sizeof(U16) + (u16LookupListIndex * sizeof(LE_Offset));
            const U8 *pLookupTable = pLookupList + LE_GET_OFFSET(s32LookupTableOffset);
            U16 u16TempOffset = u16Position + u16SequenceIndex;

            bMatched = _msAPI_MLE_LeProcessSubstitutionLookupTable(psProcess, pLookupTable, u16TempOffset);
            if ( bMatched )
            {
                u16TempCusumeSize = MAX(u16TempCusumeSize, (u16TempOffset + psProcess->sHeader.u16Consumed - u16Position));
                bResult = TRUE;
                continue;
            }
        }
    }

    if ( bResult )
    {
        psProcess->sHeader.u16Consumed = u16TempCusumeSize;
        psProcess->sHeader.u16Produced = psProcess->sHeader.u16OutLen - u16Position;
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_LeProcessContextSubstitutionTable( LE_GSUBProcess_t *psProcess, const U8 *pu8Subtable, U16 u16Position, LE_LookupFlag_e eLookupFlags )
{
    const U8 *pContext = pu8Subtable;
    const U8 *pasLookupRecord = NULL;
    U16 u16RecordCount = 0;
    BOOLEAN bResult = FALSE;

    if ( psProcess == NULL || pu8Subtable == NULL )
    {
        return FALSE;
    }

    u16RecordCount = msAPI_MLE_LeContextTableGetLookupRecord(pContext, (void *)psProcess, psProcess->sHeader.pau32OutGlyph, psProcess->sHeader.u16OutLen, u16Position, &pasLookupRecord, eLookupFlags, TRUE);
    if ( u16RecordCount > 0 )
    {
        bResult = _msAPI_MLE_LeProcessSubstitutionLookups(psProcess, pasLookupRecord, u16RecordCount, u16Position);
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_LeProcessChainingContextSubstitutionTable( LE_GSUBProcess_t *psProcess, const U8 *pu8Subtable, U16 u16Position, LE_LookupFlag_e eLookupFlags )
{
    const U8 *pChainingContext = pu8Subtable;
    const U8 *pasLookupRecord = NULL;
    U16 u16RecordCount = 0;
    BOOLEAN bResult = FALSE;

    if ( psProcess == NULL || pu8Subtable == NULL )
    {
        return FALSE;
    }

    if ( psProcess->sHeader.u16OutLen == 0 || u16Position >= psProcess->sHeader.u16OutLen )
    {
        return FALSE;
    }

    u16RecordCount = msAPI_MLE_LeChainingContextTableGetLookupRecord(pChainingContext, (void *)psProcess, psProcess->sHeader.pau32OutGlyph, psProcess->sHeader.u16OutLen, u16Position, &pasLookupRecord, eLookupFlags, TRUE);
    if ( u16RecordCount > 0 )
    {
        bResult = _msAPI_MLE_LeProcessSubstitutionLookups(psProcess, pasLookupRecord, u16RecordCount, u16Position);
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_LeProcessExtensionSubstitutionTable( LE_GSUBProcess_t *psProcess, const U8 *pu8Subtable, U16 u16Position, LE_LookupFlag_e eLookupFlags )
{
    const U8 *pExtension = pu8Subtable;
    U16 u16ExtensionLookupType;
    BOOLEAN bResult = FALSE;

    if ( psProcess == NULL || pu8Subtable == NULL )
    {
        return FALSE;
    }

    pExtension = pExtension + sizeof(U16);
    u16ExtensionLookupType = LE_GET_SHORT(pExtension);

    pExtension = pExtension + sizeof(U16);
    if ( u16ExtensionLookupType != LE_SUBST_LOOKUP_EXTENSION )
    {
        const U8 *pSubst = pu8Subtable + LE_GET_LONG_OFFSET(pExtension);

        bResult = _msAPI_MLE_LeProcessSubstitutionLookupSubtable(psProcess, u16ExtensionLookupType, pSubst, u16Position, eLookupFlags);
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_LeProcessSubstitutionLookupTable( LE_GSUBProcess_t *psProcess, const U8 *pu8Table, U16 u16Position )
{
    const U8 *pLookup = pu8Table;
    U16 u16SubtableCount = 0;
    U16 i;
    LE_SubstitutionLookupType_e eLookupType;
    LE_LookupFlag_e eLookupFlags;
    BOOLEAN bResult = FALSE;

    if ( psProcess == NULL || pu8Table == NULL )
    {
        return FALSE;
    }

    eLookupType = (LE_SubstitutionLookupType_e)LE_GET_SHORT(pLookup);

    pLookup = pLookup + sizeof(U16);
    eLookupFlags = (LE_LookupFlag_e)LE_GET_SHORT(pLookup);

    pLookup = pLookup + sizeof(U16);
    u16SubtableCount = LE_GET_SHORT(pLookup);

    for ( i = 0; i < u16SubtableCount; i++ )
    {
        const U8 *pLookupSubtable = (const U8 *)msAPI_MLE_LeLookupTableGetLookupSubtable(pu8Table, i);

        bResult = _msAPI_MLE_LeProcessSubstitutionLookupSubtable(psProcess, eLookupType, pLookupSubtable, u16Position, eLookupFlags);

        if ( bResult )
        {
            break;
        }
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_LeProcessSubstitutionLookupSubtable( LE_GSUBProcess_t *psProcess, LE_SubstitutionLookupType_e eLookupType, const U8 *pu8Subtable, U16 u16Position, LE_LookupFlag_e eLookupFlags )
{
    BOOLEAN bResult = FALSE;

    if ( psProcess == NULL )
    {
        return FALSE;
    }

    switch( eLookupType )
    {
        case LE_SUBST_LOOKUP_SINGLE:
        {
            bResult = _msAPI_MLE_LeProcessSingleSubstitutionTable(psProcess, pu8Subtable, u16Position, eLookupFlags);
            break;
        }

        case LE_SUBST_LOOKUP_MULTIPLE:
        {
            bResult = _msAPI_MLE_LeProcessMultipleSubstitutionTable(psProcess, pu8Subtable, u16Position, eLookupFlags);
            break;
        }

        case LE_SUBST_LOOKUP_ALTERNATE:
        {
            bResult = _msAPI_MLE_LeProcessAlternateSubstitutionTable(psProcess, pu8Subtable, u16Position, eLookupFlags);
            break;
        }

        case LE_SUBST_LOOKUP_LIGATURE:
        {
            bResult = _msAPI_MLE_LeProcessLigatureSubstitutionTable(psProcess, pu8Subtable, u16Position, eLookupFlags);
            break;
        }

        case LE_SUBST_LOOKUP_CONTEXT:
        {
            bResult = _msAPI_MLE_LeProcessContextSubstitutionTable(psProcess, pu8Subtable, u16Position, eLookupFlags);
            break;
        }

        case LE_SUBST_LOOKUP_CHAINING_CONTEXT:
        {
            bResult = _msAPI_MLE_LeProcessChainingContextSubstitutionTable(psProcess, pu8Subtable, u16Position, eLookupFlags);
            break;
        }

        case LE_SUBST_LOOKUP_EXTENSION:
        {
            bResult = _msAPI_MLE_LeProcessExtensionSubstitutionTable(psProcess, pu8Subtable, u16Position, eLookupFlags);
            break;
        }

        case LE_SUBST_LOOKUP_INVALID:
        default:
            break;
    }

    return bResult;
}

BOOLEAN msAPI_MLE_LeProcessSubstLookupTable( LE_GSUBProcess_t *psProcess, const U8 *pLookupTable, U16 u16SubtableIndex, U16 u16Position )
{
    const U8 *pTempLookupTable = pLookupTable;
    LE_SubstitutionLookupType_e eLookupType;
    LE_LookupFlag_e eLookupFlags;
    U16 u16SubtableCount;
    BOOLEAN bResult = FALSE;

    if ( psProcess == NULL || pLookupTable == NULL )
    {
        return FALSE;
    }

    eLookupType = LE_GET_SHORT(pTempLookupTable);

    pTempLookupTable = pTempLookupTable + sizeof(U16);
    eLookupFlags = (LE_SubstitutionLookupType_e)LE_GET_SHORT(pTempLookupTable);

    pTempLookupTable = pTempLookupTable + sizeof(U16);
    u16SubtableCount = (LE_LookupFlag_e)LE_GET_SHORT(pTempLookupTable);

    if ( u16SubtableIndex < u16SubtableCount )
    {
        const U8 *pSubtable = NULL;

        pSubtable = (const U8 *)msAPI_MLE_LeLookupTableGetLookupSubtable(pLookupTable, u16SubtableIndex);
        if ( pSubtable )
        {
            bResult = _msAPI_MLE_LeProcessSubstitutionLookupSubtable((LE_GSUBProcess_t *)psProcess, eLookupType, pSubtable, u16Position, eLookupFlags);
        }
    }

    return bResult;
}

const U8* msAPI_MLE_LeSubstGetScriptListTable( const U8 *pSubstTable )
{
    S32 s32ScriptListOffset = (S32)pSubstTable + sizeof(LE_Version);

    if ( pSubstTable == NULL )
    {
        return NULL;
    }

    return (pSubstTable + LE_GET_OFFSET(s32ScriptListOffset));
}

const U8* msAPI_MLE_LeSubstGetFeatureListTable( const U8 *pSubstTable )
{
    S32 s32FeatureListOffset = (S32)pSubstTable + sizeof(LE_Version) + sizeof(LE_Offset);

    if ( pSubstTable == NULL )
    {
        return NULL;
    }

    return (pSubstTable + LE_GET_OFFSET(s32FeatureListOffset));
}

const U8* msAPI_MLE_LeSubstGetLookupListTable( const U8 *pSubstTable )
{
    S32 s32LookupListOffset = (S32)pSubstTable + sizeof(LE_Version) + sizeof(LE_Offset) + sizeof(LE_Offset);

    if ( pSubstTable == NULL )
    {
        return NULL;
    }

    return (pSubstTable + LE_GET_OFFSET(s32LookupListOffset));
}

#endif //__FEATURE_VECTOR_FONT__

#endif //__MSAPI_MLE_LE_OTF_SUBST_C__
