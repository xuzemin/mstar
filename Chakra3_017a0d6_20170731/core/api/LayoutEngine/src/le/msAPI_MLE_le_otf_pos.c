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

#include "msAPI_MLE_le_util.h"
#include "msAPI_MLE_le_otf_pos.h"

static BOOLEAN _msAPI_MLE_LeProcessPositionLookupTable( LE_GPOSProcess_t *psProcess, const U8 *pu8Table, U16 u16Position );

static BOOLEAN _msAPI_MLE_LeAdjustPosition( const U8 *pValueRecord, LE_ValueFormat_e eValueFormat, const U8 *psData, LE_FontInstanceInf_t *pFontInstanceInf, LE_PosInf_t *pPositionInf )
{
    S32 s32XPlacementAdjustment = 0;
    S32 s32YPlacementAdjustment = 0;
    S32 s32XAdvanceAdjustment = 0;
    S32 s32YAdvanceAdjustment = 0;

    if ( pValueRecord == NULL || psData == NULL || pFontInstanceInf == NULL || pPositionInf == NULL )
    {
        return FALSE;
    }

    if ( (eValueFormat & LE_VALUE_X_PLACEMENT) != 0 ) 
    {
        S16 s16Value = msAPI_MLE_LeValueGetFieldValue(pValueRecord, eValueFormat, LE_VALUE_X_PLACEMENT_INDEX);
        LE_Points_t sPoint = {0, 0};

        msAPI_MLE_LeFontTransformUnit(pFontInstanceInf, s16Value, 0, &sPoint);

        s32XPlacementAdjustment = s32XPlacementAdjustment + msAPI_MLE_LeFontXPixelsToUnits(pFontInstanceInf, sPoint.s32X);
        s32YPlacementAdjustment = s32YPlacementAdjustment + msAPI_MLE_LeFontYPixelsToUnits(pFontInstanceInf, sPoint.s32Y);
    }

    if ( (eValueFormat & LE_VALUE_Y_PLACEMENT) != 0 )
    {
        S16 s16Value = msAPI_MLE_LeValueGetFieldValue(pValueRecord, eValueFormat, LE_VALUE_Y_PLACEMENT_INDEX);
        LE_Points_t sPoint = {0, 0};

        msAPI_MLE_LeFontTransformUnit(pFontInstanceInf, 0, s16Value, &sPoint);

        s32XPlacementAdjustment = s32XPlacementAdjustment + msAPI_MLE_LeFontXPixelsToUnits(pFontInstanceInf, sPoint.s32X);
        s32YPlacementAdjustment = s32YPlacementAdjustment + msAPI_MLE_LeFontYPixelsToUnits(pFontInstanceInf, sPoint.s32Y);
    }

    if ( (eValueFormat & LE_VALUE_X_ADVANCE) != 0 )
    {
        S16 s16Value = msAPI_MLE_LeValueGetFieldValue(pValueRecord, eValueFormat, LE_VALUE_X_ADVANCE_INDEX);
        LE_Points_t sPoint = {0, 0};

        msAPI_MLE_LeFontTransformUnit(pFontInstanceInf, s16Value, 0, &sPoint);

        s32XAdvanceAdjustment = s32XAdvanceAdjustment + msAPI_MLE_LeFontXPixelsToUnits(pFontInstanceInf, sPoint.s32X);
        s32YAdvanceAdjustment = s32YAdvanceAdjustment + msAPI_MLE_LeFontYPixelsToUnits(pFontInstanceInf, sPoint.s32Y);
    }

    if ( (eValueFormat & LE_VALUE_Y_ADVANCE) != 0 )
    {
        S16 s16Value = msAPI_MLE_LeValueGetFieldValue(pValueRecord, eValueFormat, LE_VALUE_Y_ADVANCE_INDEX);
        LE_Points_t sPoint = {0, 0};

        msAPI_MLE_LeFontTransformUnit(pFontInstanceInf, 0, s16Value, &sPoint);

        s32XAdvanceAdjustment = s32XAdvanceAdjustment + msAPI_MLE_LeFontXPixelsToUnits(pFontInstanceInf, sPoint.s32X);
        s32YAdvanceAdjustment = s32YAdvanceAdjustment + msAPI_MLE_LeFontYPixelsToUnits(pFontInstanceInf, sPoint.s32Y);
    }

    if ( (eValueFormat & LE_VALUE_ANY_DEVICE) != 0 )
    {
        if ( (eValueFormat & LE_VALUE_X_PLACEMENT_DEVICE) != 0 )
        {   
            S32 s32Offset = msAPI_MLE_LeValueGetFieldValue(pValueRecord, eValueFormat, LE_VALUE_X_PLACEMENT_DEVICE_INDEX);

            if ( s32Offset != 0 )
            {
                const U8 *pDeviceTable = (const U8 *)(psData + s32Offset);
                S16 s16XAdj = msAPI_MLE_LeDeviceTableGetAdjustment(pDeviceTable, pFontInstanceInf->u16XPixelsPerEM);

                s32XPlacementAdjustment = s32XPlacementAdjustment + msAPI_MLE_LeFontXPixelsToUnits(pFontInstanceInf, s16XAdj);
            }
        }

        if ( (eValueFormat & LE_VALUE_Y_PLACEMENT_DEVICE) != 0 )
        {
            S32 s32Offset = msAPI_MLE_LeValueGetFieldValue(pValueRecord, eValueFormat, LE_VALUE_Y_PLACEMENT_DEVICE_INDEX);

            if ( s32Offset != 0 )
            {
                const U8 *pDeviceTable = (const U8 *)(psData + s32Offset);
                S16 s16YAdj = msAPI_MLE_LeDeviceTableGetAdjustment(pDeviceTable, pFontInstanceInf->u16YPixelsPerEM);

                s32YPlacementAdjustment = s32YPlacementAdjustment + msAPI_MLE_LeFontXPixelsToUnits(pFontInstanceInf, s16YAdj);
            }
        }

        if ( (eValueFormat & LE_VALUE_X_ADVANCE_DEVICE) != 0 )
        {
            S32 s32Offset = msAPI_MLE_LeValueGetFieldValue(pValueRecord, eValueFormat, LE_VALUE_X_ADVANCE_DEVICE_INDEX);

            if ( s32Offset != 0 )
            {
                const U8 *pDeviceTable = (const U8 *)(psData + s32Offset);
                S16 s16XAdj = msAPI_MLE_LeDeviceTableGetAdjustment(pDeviceTable, pFontInstanceInf->u16XPixelsPerEM);

                s32XAdvanceAdjustment = s32XAdvanceAdjustment + msAPI_MLE_LeFontXPixelsToUnits(pFontInstanceInf, s16XAdj);
            }
        }

        if ((eValueFormat & LE_VALUE_Y_ADVANCE_DEVICE) != 0)
        {
            S32 s32Offset = msAPI_MLE_LeValueGetFieldValue(pValueRecord, eValueFormat, LE_VALUE_Y_ADVANCE_DEVICE_INDEX);

            if ( s32Offset != 0 )
            {
                const U8 *pDeviceTable = (const U8 *)(psData + s32Offset);
                S16 s16YAdj = msAPI_MLE_LeDeviceTableGetAdjustment(pDeviceTable, pFontInstanceInf->u16YPixelsPerEM);

                s32YAdvanceAdjustment = s32YAdvanceAdjustment + msAPI_MLE_LeFontXPixelsToUnits(pFontInstanceInf, s16YAdj);
            }
        }
    }

    pPositionInf->s32XPlacementAdjustment = s32XPlacementAdjustment;
    pPositionInf->s32YPlacementAdjustment = s32YPlacementAdjustment;
    pPositionInf->s32XAdvanceAdjustment = s32XAdvanceAdjustment;
    pPositionInf->s32YAdvanceAdjustment = s32YAdvanceAdjustment;

    return TRUE;
}

static BOOLEAN _msAPI_MLE_LeProcessSingleAdjPositionFormat1Table( LE_GPOSProcess_t *psProcess, const U8 *pu8Subtable, U16 u16Position )
{
    const U8 *pFormat1 = pu8Subtable;
    const U8 *pConverage = NULL;
    U16 u16GlyphId = (U16)(-1);
    S32 s32CoverageIndex = -1;
    BOOLEAN bResult = FALSE;

    if ( psProcess == NULL || pu8Subtable == NULL )
    {
        return FALSE;
    }

    if ( u16Position >= psProcess->sHeader.u16InLen )
    {
        return FALSE;
    }
    
    u16GlyphId = LE_GET_GLYPH_ID(psProcess->sHeader.pau32InGlyph[u16Position]);

    pFormat1 = pFormat1 + sizeof(U16);
    pConverage = (const U8 *)(pu8Subtable + LE_GET_OFFSET(pFormat1));
    s32CoverageIndex = msAPI_MLE_LeGetGlyphCoverage(pConverage, u16GlyphId);

    pFormat1 = pFormat1 + sizeof(LE_Offset);
    if ( s32CoverageIndex >= 0 ) 
    {
        bResult = _msAPI_MLE_LeAdjustPosition((pFormat1 + sizeof(U16)), LE_GET_SHORT(pFormat1), pu8Subtable, &psProcess->sFontInstanceInf, &(psProcess->sPosInf));
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_LeProcessSingleAdjPositionFormat2Table( LE_GPOSProcess_t *psProcess, const U8 *pu8Subtable, U16 u16Position )
{
    const U8 *pFormat2 = pu8Subtable;
    const U8 *pConverage = NULL;
    U16 u16GlyphId = (U16)(-1);
    S32 s32CoverageIndex = -1;
    BOOLEAN bResult = FALSE;

    if ( psProcess == NULL || pu8Subtable == NULL )
    {
        return FALSE;
    }

    if ( u16Position >= psProcess->sHeader.u16InLen )
    {
        return FALSE;
    }

    u16GlyphId = LE_GET_GLYPH_ID(psProcess->sHeader.pau32InGlyph[u16Position]);

    pFormat2 = pFormat2 + sizeof(U16);
    pConverage = (const U8 *)(pu8Subtable + LE_GET_OFFSET(pFormat2));
    s32CoverageIndex = msAPI_MLE_LeGetGlyphCoverage(pConverage, u16GlyphId);

    pFormat2 = pFormat2 + sizeof(LE_Offset);
    if ( s32CoverageIndex >= 0 )
    {
        S32 s32ValueRecordOffset = (S32)pFormat2 + sizeof(U16) + sizeof(U16);
        
        bResult = _msAPI_MLE_LeAdjustPosition( (const U8 *)s32ValueRecordOffset, LE_GET_SHORT(pFormat2), pu8Subtable, &psProcess->sFontInstanceInf, &(psProcess->sPosInf));
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_LeProcessSingleAdjPositionTable( LE_GPOSProcess_t *psProcess, const U8 *pu8Subtable, U16 u16Position )
{
    BOOLEAN bResult = FALSE;

    if ( psProcess == NULL || pu8Subtable == NULL )
    {
        return FALSE;
    }

    switch( LE_GET_SHORT(pu8Subtable) )
    {
        case LE_SINGLE_ADJ_POS_FORMAT_1:
        {
             bResult = _msAPI_MLE_LeProcessSingleAdjPositionFormat1Table(psProcess, pu8Subtable, u16Position);
             break;
        }

        case LE_SINGLE_ADJ_POS_FORMAT_2:
        {
             bResult = _msAPI_MLE_LeProcessSingleAdjPositionFormat2Table(psProcess, pu8Subtable, u16Position);
             break;
        }

        case LE_SINGLE_ADJ_POS_FORMAT_INVALID:
        default:
            break;
    }

    return bResult;
}

const U8* _msAPI_MLE_LeFindPairValueRecord(U16 u16GlyphId, const U8 *pRecords, U16 u16RecordCount, U16 u16RecordSize )
{
    const U8 *pRecord = NULL;
    U32 i = 0;

    if ( pRecords == NULL || u16RecordCount == 0 )
    {
        return NULL;
    }

    for( i = 0; i < u16RecordCount; i++ ) 
    {
        pRecord = pRecords + (u16RecordSize * i);
        if ( LE_GET_SHORT(pRecord) == u16GlyphId )
        {
            return pRecord;
        }
    }

    return NULL;
}

static BOOLEAN _msAPI_MLE_LeProcessPairAdjPositionFormat1Table( LE_GPOSProcess_t *psProcess, const U8 *pu8Subtable, U16 u16Position )
{
    const U8 *pFormat1 = pu8Subtable;
    const U8 *pConverage = NULL;
    U16 u16GlyphId = (U16)(-1);
    S32 s32CoverageIndex = -1;
    BOOLEAN bResult = FALSE;

    if ( psProcess == NULL || pu8Subtable == NULL )
    {
        return FALSE;
    }

    //at leaset need two glyphs
    if ( u16Position >= (psProcess->sHeader.u16InLen - 1) )
    {
        return FALSE;
    }

    u16GlyphId = LE_GET_GLYPH_ID(psProcess->sHeader.pau32InGlyph[u16Position]);

    pFormat1 = pFormat1 + sizeof(U16);
    pConverage = pu8Subtable + LE_GET_OFFSET(pFormat1);
    s32CoverageIndex = msAPI_MLE_LeGetGlyphCoverage(pConverage, u16GlyphId);

    pFormat1 = pFormat1 + sizeof(LE_Offset);
    if ( s32CoverageIndex >= 0 )
    {
        S32 s32PairSetTableOffset = (S32)pFormat1 + sizeof(U16) + sizeof(U16) + sizeof(U16) + (s32CoverageIndex * sizeof(LE_Offset));
        const U8 *pPairSetTable = pu8Subtable + LE_GET_OFFSET(s32PairSetTableOffset);
        U16 u16PairValueCount = LE_GET_SHORT(pPairSetTable);
        U16 u16SecondGlyph = LE_GET_GLYPH_ID(psProcess->sHeader.pau32InGlyph[u16Position + 1]);
        const U8 *pPairValueRecord = NULL;
        S16 s16ValueRecord1Size;
        S16 s16ValueRecord2Size;
        S16 s16RecordSize;

        s16ValueRecord1Size = msAPI_MLE_LeValueGetSize(LE_GET_SHORT(pFormat1));

        pFormat1 = pFormat1 + sizeof(U16);
        s16ValueRecord2Size = msAPI_MLE_LeValueGetSize(LE_GET_SHORT(pFormat1));
        s16RecordSize = sizeof(U16) + s16ValueRecord1Size + s16ValueRecord2Size;

        if ( u16PairValueCount != 0 ) 
        {
            pPairValueRecord = _msAPI_MLE_LeFindPairValueRecord(u16SecondGlyph, (pPairSetTable + sizeof(U16)), u16PairValueCount, s16RecordSize);
        }

        pFormat1 = pu8Subtable + sizeof(U16) + sizeof(LE_Offset);
        if ( pPairValueRecord != NULL)
        {
            if ( LE_GET_SHORT(pFormat1) != 0 )
            {
                bResult = _msAPI_MLE_LeAdjustPosition( (pPairValueRecord + sizeof(U16)), LE_GET_SHORT(pFormat1), pu8Subtable, &psProcess->sFontInstanceInf, &(psProcess->sPosInf));
            }

            pFormat1 = pFormat1 + sizeof(U16);
            if ( LE_GET_SHORT(pFormat1) != 0 )
            {           
                const U8 *pValueRecord2 = pPairValueRecord + sizeof(U16) + s16ValueRecord1Size;
                
                bResult = (bResult | _msAPI_MLE_LeAdjustPosition( pValueRecord2, LE_GET_SHORT(pFormat1), pu8Subtable, &psProcess->sFontInstanceInf, &(psProcess->sNextPosInf)));
            }
        }
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_LeProcessPairAdjPositionFormat2Table( LE_GPOSProcess_t *psProcess, const U8 *pu8Subtable, U16 u16Position )
{
    const U8 *pFormat2 = pu8Subtable;
    const U8 *pConverage = NULL;
    U16 u16GlyphId = (U16)(-1);
    S32 s32CoverageIndex = -1;
    BOOLEAN bResult = FALSE;

    if ( psProcess == NULL || pu8Subtable == NULL )
    {
        return FALSE;
    }

    //at leaset need two glyphs
    if ( u16Position >= (psProcess->sHeader.u16InLen - 1) )
    {
        return FALSE;
    }

    u16GlyphId = LE_GET_GLYPH_ID(psProcess->sHeader.pau32InGlyph[u16Position]);

    pFormat2 = pFormat2 + sizeof(U16);
    pConverage = (const U8 *)(pu8Subtable + LE_GET_OFFSET(pFormat2));
    s32CoverageIndex = msAPI_MLE_LeGetGlyphCoverage(pConverage, u16GlyphId);

    pFormat2 = pFormat2 + sizeof(LE_Offset);
    if ( s32CoverageIndex ) 
    {
        U16 u16SecondGlyph = LE_GET_GLYPH_ID(psProcess->sHeader.pau32InGlyph[u16Position + 1]);
        S32 s32ClassDef1Offset = (S32)pFormat2 + sizeof(U16) + sizeof(U16);
        const U8 *pClassDef1 = (const U8 *) (((const LE_PairAdjPosition_t *)((void *)(pu8Subtable))) + LE_GET_OFFSET(s32ClassDef1Offset));
        S32 s32ClassDef2Offset = (S32)pFormat2 + sizeof(U16) + sizeof(U16) + sizeof(LE_Offset);
        const U8 *pClassDef2 = (const U8 *) (((const LE_PairAdjPosition_t *)((void *)(pu8Subtable))) + LE_GET_OFFSET(s32ClassDef2Offset));
        S32 s32Class1 = msAPI_MLE_LeGetGlyphClass(pClassDef1, u16GlyphId);
        S32 s32Class2 = msAPI_MLE_LeGetGlyphClass(pClassDef2, u16SecondGlyph);
        S16 s16ValueRecord1Size;
        S16 s16ValueRecord2Size;
        U16 u16Class2Count;
        S16 s16Class2RecordSize;
        S16 s16Class1RecordSize;
        const U8 *pClass1Record;
        const U8 *pClass2Record;

        if ( s32Class1 < 0 )
        {
            s32Class1 = 0;
        }

        if ( s32Class2 < 0 )
        {
            s32Class2 = 0;
        }

        s16ValueRecord1Size = msAPI_MLE_LeValueGetSize(LE_GET_SHORT(pFormat2));

        pFormat2 = pFormat2 + sizeof(U16);
        s16ValueRecord2Size = msAPI_MLE_LeValueGetSize(LE_GET_SHORT(pFormat2));
        
        s16Class2RecordSize = s16ValueRecord1Size + s16ValueRecord2Size;

        pFormat2 = pFormat2 + sizeof(U16) + sizeof(LE_Offset) + sizeof(LE_Offset);

        pFormat2 = pFormat2 + sizeof(U16);
        u16Class2Count = LE_GET_SHORT(pFormat2);
        
        s16Class1RecordSize = s16Class2RecordSize * u16Class2Count;

        pFormat2 = pFormat2 + sizeof(U16);
        pClass1Record = pFormat2 + (s16Class1RecordSize * s32Class1);
        pClass2Record = pClass1Record + (s16Class2RecordSize * s32Class2);

        pFormat2 = pu8Subtable + sizeof(U16) + sizeof(LE_Offset);
        if ( LE_GET_SHORT(pFormat2) != 0 )
        {
            bResult = _msAPI_MLE_LeAdjustPosition( pClass2Record, LE_GET_SHORT(pFormat2), pu8Subtable, &psProcess->sFontInstanceInf, &(psProcess->sPosInf));
        }

        pFormat2 = pFormat2 + sizeof(U16);
        if ( LE_GET_SHORT(pFormat2) != 0 )
        {
            const U8 *pValueRecord2 = pClass2Record + s16ValueRecord1Size;
            
            bResult = (bResult | _msAPI_MLE_LeAdjustPosition( pValueRecord2, LE_GET_SHORT(pFormat2), pu8Subtable, &psProcess->sFontInstanceInf, &(psProcess->sNextPosInf)));
        }
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_LeProcessPairAdjPositionTable( LE_GPOSProcess_t *psProcess, const U8 *pu8Subtable, U16 u16Position )
{
    BOOLEAN bResult = FALSE;

    if ( psProcess == NULL || pu8Subtable == NULL )
    {
        return FALSE;
    }

    switch(LE_GET_SHORT(pu8Subtable))
    {
        case LE_PAIR_ADJ_POS_FORMAT_1:
        {
            bResult = _msAPI_MLE_LeProcessPairAdjPositionFormat1Table(psProcess, pu8Subtable, u16Position);
            break;
        }

        case LE_PAIR_ADJ_POS_FORMAT_2:
        {
            bResult = _msAPI_MLE_LeProcessPairAdjPositionFormat2Table(psProcess, pu8Subtable, u16Position);
            break;
        }

        case LE_PAIR_ADJ_POS_FORMAT_INVALID:
        default:
            break;
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_LeProcessCursiveAttPositionTable( LE_GPOSProcess_t *psProcess, const U8 *pu8Subtable, U16 u16Position )
{
    const U8 *pCursive = pu8Subtable;
    const U8 *pConverage = NULL;
    U16 u16GlyphId = (U16)(-1);
    S32 s32CoverageIndex = -1;
    LE_Points_t sEntryAnchor, sExitAnchor;
    BOOLEAN bResult = FALSE;
    
    if ( psProcess == NULL || pu8Subtable == NULL )
    {
        return FALSE;
    }

    if ( u16Position >= psProcess->sHeader.u16InLen )
    {
        return FALSE;
    }

    u16GlyphId = LE_GET_GLYPH_ID(psProcess->sHeader.pau32InGlyph[u16Position]);

    pCursive = pCursive + sizeof(U16);
    pConverage = (const U8 *)(pu8Subtable + LE_GET_OFFSET(pCursive));
    s32CoverageIndex = msAPI_MLE_LeGetGlyphCoverage(pConverage, u16GlyphId);

    pCursive = pCursive + sizeof(LE_Offset);
    if ( s32CoverageIndex >= 0 && s32CoverageIndex <= LE_GET_SHORT(pCursive) )
    {
        S32 s32EntryOffset = (S32)pCursive + sizeof(U16) + (s32CoverageIndex * LE_EntryExitRecord_Size);
        S32 s32ExitOffset = s32EntryOffset + sizeof(LE_Offset);

        if ( s32EntryOffset != 0 ) 
        {
            const U8 *pEntryAnchorTable = pu8Subtable + LE_GET_OFFSET(s32EntryOffset);

            bResult = msAPI_MLE_LeGetAnchor(pEntryAnchorTable, u16GlyphId, &sEntryAnchor, &psProcess->sFontInstanceInf);
        }

        if ( bResult )
        {
            psProcess->sPosInf.sEntryAnchor = sEntryAnchor;
        }
        else
        {
            memset((void *)&(psProcess->sPosInf.sEntryAnchor), 0, sizeof(LE_Points_t));
        }

        if ( s32ExitOffset != 0 )
        {
            const U8 *pExitAnchorTable = pu8Subtable + LE_GET_OFFSET(s32ExitOffset);

            bResult = msAPI_MLE_LeGetAnchor(pExitAnchorTable, u16GlyphId, &sExitAnchor, &psProcess->sFontInstanceInf);
        }
        
        if ( bResult )
        {
            psProcess->sPosInf.sExitAnchor = sExitAnchor;
        }
        else
        {
            memset((void *)&(psProcess->sPosInf.sExitAnchor), 0, sizeof(LE_Points_t));
        }
    }
    else
    {
        memset((void *)&(psProcess->sPosInf.sEntryAnchor), 0, sizeof(LE_Points_t));
        memset((void *)&(psProcess->sPosInf.sExitAnchor), 0, sizeof(LE_Points_t));
    }

    return TRUE;
}

static BOOLEAN _msAPI_MLE_LeProcessMarkToBaseAttPositionTable( LE_GPOSProcess_t *psProcess, const U8 *pu8Subtable, U16 u16Position )
{
    const U8 *pMarkToBase = pu8Subtable;
    const U8 *pConverage = NULL;
    U16 u16MarkGlyph = (U16)(-1);
    S32 s32MarkCoverageIndex = -1;
    BOOLEAN bResult = FALSE;

    if ( psProcess == NULL || pu8Subtable == NULL )
    {
        return FALSE;
    }

    if ( u16Position >= psProcess->sHeader.u16InLen )
    {
        return FALSE;
    }

    u16MarkGlyph = LE_GET_GLYPH_ID(psProcess->sHeader.pau32InGlyph[u16Position]);

    pMarkToBase = pMarkToBase + sizeof(U16);
    pConverage = (const U8 *)(pu8Subtable + LE_GET_OFFSET(pMarkToBase));
    s32MarkCoverageIndex = msAPI_MLE_LeGetGlyphCoverage(pConverage, u16MarkGlyph);

    pMarkToBase = pMarkToBase + sizeof(LE_Offset);
    if ( s32MarkCoverageIndex >= 0 )
    {
        LE_Points_t sMarkAnchor = {0, 0};
        S32 s32MarkArrayOffset = (S32)pMarkToBase + sizeof(LE_Offset) + sizeof(U16);
        const U8 *pMarkArray = (const U8 *)(pu8Subtable + LE_GET_OFFSET(s32MarkArrayOffset));
        S32 s32MarkClass = msAPI_MLE_LeMarkArrayGetMarkClass(pMarkArray, u16MarkGlyph, s32MarkCoverageIndex, &sMarkAnchor, &psProcess->sFontInstanceInf);
        S32 s32ClassCountOffset = (S32)pMarkToBase + sizeof(LE_Offset);
        U16 u16MarkCount = LE_GET_SHORT(s32ClassCountOffset);
        U16 u16BasePosition = 0;

        if ( s32MarkClass >= 0 && s32MarkClass < u16MarkCount )
        {
            U16 u16BaseGlyph = msAPI_MLE_LeGlyphStrGetNextBaseGlyph(psProcess->sHeader.pau32InGlyph, psProcess->sHeader.u16InLen, u16Position, 1, &u16BasePosition, psProcess->pClassDefTable, LE_LOOKUP_FLAG_RIGHTTOLEFT, TRUE);
            S32 s32BaseCoverage = msAPI_MLE_LeGetGlyphCoverage((pu8Subtable + LE_GET_OFFSET(pMarkToBase)), u16BaseGlyph);
            S32 s32BaseArrayOffset = (S32)pMarkToBase + sizeof(LE_Offset) + sizeof(U16) + sizeof(LE_Offset);
            const U8 *pBaseArray = pu8Subtable + LE_GET_OFFSET(s32BaseArrayOffset);
            U16 u16BaseCount = LE_GET_SHORT(pBaseArray);

            if ( s32BaseCoverage >= 0 && s32BaseCoverage < u16BaseCount )
            {
                const U8 *pBaseRecord = pBaseArray + sizeof(S16) + ((s32BaseCoverage * u16MarkCount) * sizeof(LE_Offset));
                S32 s32AnchorTableOffset = (S32)pBaseRecord + (s32MarkClass * sizeof(LE_Offset));
                const U8 *pAnchorTable = pBaseArray + LE_GET_OFFSET(s32AnchorTableOffset);
                LE_Points_t sBaseAnchor, sMarkAdvance, sPixels;

                if ( LE_GET_OFFSET(s32AnchorTableOffset) == 0 )
                {
                    psProcess->sHeader.u16BaseOffset = u16Position;
                }
                else
                {
                    S32 s32AnchorDiffX = 0;
                    S32 s32AnchorDiffY = 0;
                    
                    msAPI_MLE_LeGetAnchor(pAnchorTable, u16BaseGlyph, &sBaseAnchor, &psProcess->sFontInstanceInf);

                    msAPI_MLE_LeFontGetGlyphAdvance(u16MarkGlyph, &sPixels);
                    msAPI_MLE_LeFontPixelsToUnits(&psProcess->sFontInstanceInf, &sPixels, &sMarkAdvance);

                    s32AnchorDiffX = sBaseAnchor.s32X - sMarkAnchor.s32X;
                    s32AnchorDiffY = sBaseAnchor.s32Y - sMarkAnchor.s32Y;

                    if ( msAPI_MLE_LeFontIsGlyphRightToLeft(&psProcess->sFontInstanceInf, LE_GET_GLYPH_ID(psProcess->sHeader.pau32InGlyph[u16Position])) )
                    {               
                        psProcess->sPosInf.s32XPlacementAdjustment = s32AnchorDiffX;
                        psProcess->sPosInf.s32YPlacementAdjustment = s32AnchorDiffY;
                        psProcess->sPosInf.s32XAdvanceAdjustment = (-sMarkAdvance.s32X);
                        psProcess->sPosInf.s32YAdvanceAdjustment = (-sMarkAdvance.s32Y);
                    } 
                    else
                    {
                        LE_Points_t sBaseAdvance;
                        U16 u16SearchOffset = u16Position;

                        msAPI_MLE_LeFontGetGlyphAdvance(u16BaseGlyph, &sPixels);

                        u16SearchOffset = u16BasePosition + 1;
                        psProcess->sHeader.u16BaseOffset = u16BasePosition;
                        while ( u16SearchOffset < u16Position )
                        {
                            U16 u16OtherMarkGlyphId = LE_GET_GLYPH_ID(psProcess->sHeader.pau32InGlyph[u16SearchOffset]);
                            LE_Points_t sTempPixel;
                            
                            msAPI_MLE_LeFontGetGlyphAdvance(u16OtherMarkGlyphId, &sTempPixel);
                            sPixels.s32X += sTempPixel.s32X;
                            sPixels.s32Y += sTempPixel.s32Y;
                            u16SearchOffset = u16SearchOffset + 1;
                        }
   
                        msAPI_MLE_LeFontPixelsToUnits(&psProcess->sFontInstanceInf, &sPixels, &sBaseAdvance);

                        psProcess->sPosInf.s32XPlacementAdjustment = s32AnchorDiffX - sBaseAdvance.s32X;
                        psProcess->sPosInf.s32YPlacementAdjustment = s32AnchorDiffY - sBaseAdvance.s32Y;
                        psProcess->sPosInf.s32XAdvanceAdjustment = (-sMarkAdvance.s32X);
                        psProcess->sPosInf.s32YAdvanceAdjustment = (-sMarkAdvance.s32Y);
                    }
                }

                bResult = TRUE;
            }
        }
    }
    
    return bResult;
}

static BOOLEAN _msAPI_MLE_LeProcessMarkToLigatureAttPositionTable( LE_GPOSProcess_t *psProcess, const U8 *pu8Subtable, U16 u16Position )
{
    const U8 *pMarkToLigature = pu8Subtable;
    const U8 *pConverage = NULL;
    U16 u16MarkGlyph = (U16)(-1);
    S32 s32MarkCoverageIndex = -1;
    BOOLEAN bResult = FALSE;

    if ( psProcess == NULL || pu8Subtable == NULL )
    {
        return FALSE;
    }

    if ( u16Position >= psProcess->sHeader.u16InLen )
    {
        return FALSE;
    }

    u16MarkGlyph = LE_GET_GLYPH_ID(psProcess->sHeader.pau32InGlyph[u16Position]);

    pMarkToLigature = pMarkToLigature + sizeof(U16);
    pConverage = (const U8 *)(pu8Subtable + LE_GET_OFFSET(pMarkToLigature));
    s32MarkCoverageIndex = msAPI_MLE_LeGetGlyphCoverage(pConverage, u16MarkGlyph);

    pMarkToLigature = pMarkToLigature + sizeof(LE_Offset);
    if ( s32MarkCoverageIndex >= 0 )
    {
        LE_Points_t sMarkAnchor = {0, 0};
        S32 s32MarkArrayOffset = (S32)pMarkToLigature + sizeof(LE_Offset) + sizeof(U16);
        const U8 *pMarkArray = (const U8 *)(pu8Subtable + LE_GET_OFFSET(s32MarkArrayOffset));
        S32 s32MarkClass = msAPI_MLE_LeMarkArrayGetMarkClass(pMarkArray, u16MarkGlyph, s32MarkCoverageIndex, &sMarkAnchor, &psProcess->sFontInstanceInf);
        S32 s32ClassCountOffset = (S32)pMarkToLigature + sizeof(LE_Offset);
        U16 u16MarkCount = LE_GET_SHORT(s32ClassCountOffset);

        if ( s32MarkClass >= 0 && s32MarkClass < u16MarkCount )
        {
            U16 u16LigaturePosition = u16Position;
            U16 u16LigatureGlyph = msAPI_MLE_LeGlyphStrGetNext(psProcess->sHeader.pau32InGlyph, psProcess->sHeader.u16InLen, u16Position, 1, &u16LigaturePosition, psProcess->pClassDefTable, (LE_LOOKUP_FLAG_IGNORE_MARKS | LE_LOOKUP_FLAG_RIGHTTOLEFT), TRUE);
            S32 s32LigatureCoverage = msAPI_MLE_LeGetGlyphCoverage((const U8 *)(pu8Subtable + LE_GET_OFFSET(pMarkToLigature)), u16LigatureGlyph);
            S32 s32LigatureArrayOffset = (S32)pMarkToLigature + sizeof(LE_Offset) + sizeof(U16) + sizeof(LE_Offset);
            const U8 *pLigatureArray = pu8Subtable + LE_GET_OFFSET(s32LigatureArrayOffset);
            U16 u16LigatureCount = LE_GET_SHORT(pLigatureArray);

            //there has a ligature glyph in front of current mark position
            if ( s32LigatureCoverage >= 0 && s32LigatureCoverage < u16LigatureCount )
            {
                S32 s32LigatureAttachTableOffset = (S32)pLigatureArray + sizeof(U16) + (s32LigatureCoverage * sizeof(LE_Offset));
                const U8 *pLigatureAttachTable = pLigatureArray + LE_GET_OFFSET(s32LigatureAttachTableOffset);
                U16 u16ComponentCount = LE_GET_SHORT(pLigatureAttachTable);
                const U8 *pComponentRecord = NULL;
                S32 s32AnchorTableOffset;
                const U8 *pAnchorTable = NULL;
                LE_Points_t sLigatureAnchor, sMarkAdvance, sPixels;
                S32 s32AnchorDiffX = 0;
                S32 s32AnchorDiffY = 0;
                
                if ( u16LigaturePosition >= u16ComponentCount ) 
                {
                    u16LigaturePosition = u16ComponentCount - 1;
                }
    
                pComponentRecord = pLigatureAttachTable + sizeof(U16) + ((u16LigaturePosition * u16MarkCount) * sizeof(LE_Offset));

                s32AnchorTableOffset = (S32)pComponentRecord + (s32MarkClass * sizeof(LE_Offset));
                pAnchorTable = pLigatureAttachTable + LE_GET_OFFSET(s32AnchorTableOffset);

                msAPI_MLE_LeGetAnchor(pAnchorTable, u16LigatureGlyph, &sLigatureAnchor, &psProcess->sFontInstanceInf);

                msAPI_MLE_LeFontGetGlyphAdvance(u16MarkGlyph, &sPixels);
                msAPI_MLE_LeFontPixelsToUnits(&psProcess->sFontInstanceInf, &sPixels, &sMarkAdvance);

                s32AnchorDiffX = sLigatureAnchor.s32X - sMarkAnchor.s32X;
                s32AnchorDiffY = sLigatureAnchor.s32Y - sMarkAnchor.s32Y;

                psProcess->sHeader.u16BaseOffset = u16LigaturePosition;

                if ( msAPI_MLE_LeFontIsGlyphRightToLeft(&psProcess->sFontInstanceInf, LE_GET_GLYPH_ID(psProcess->sHeader.pau32InGlyph[u16Position])) )
                {
                    psProcess->sPosInf.s32XPlacementAdjustment = s32AnchorDiffX;
                    psProcess->sPosInf.s32YPlacementAdjustment = s32AnchorDiffY;
                    psProcess->sPosInf.s32XAdvanceAdjustment = (-sMarkAdvance.s32X);
                    psProcess->sPosInf.s32YAdvanceAdjustment = (-sMarkAdvance.s32Y);
                }
                else
                {
                    LE_Points_t sLigatureAdvance;

                    msAPI_MLE_LeFontGetGlyphAdvance(u16LigatureGlyph, &sPixels);
                    msAPI_MLE_LeFontPixelsToUnits(&psProcess->sFontInstanceInf, &sPixels, &sLigatureAdvance);
                        
                    psProcess->sPosInf.s32XPlacementAdjustment = s32AnchorDiffX - sLigatureAdvance.s32X;
                    psProcess->sPosInf.s32YPlacementAdjustment = s32AnchorDiffY - sLigatureAdvance.s32Y;
                    psProcess->sPosInf.s32XAdvanceAdjustment = (-sMarkAdvance.s32X);
                    psProcess->sPosInf.s32YAdvanceAdjustment = (-sMarkAdvance.s32Y);
                }
            }
            
            bResult = TRUE;
        }
    }
    
    return bResult;
}

static BOOLEAN _msAPI_MLE_LeProcessMarkToMarkAttPositionTable( LE_GPOSProcess_t *psProcess, const U8 *pu8Subtable, U16 u16Position )
{
    const U8 *pMarkToMark = pu8Subtable;
    const U8 *pConverage = NULL;
    U16 u16MarkGlyph = (U16)(-1);
    S32 s32MarkCoverageIndex = -1;
    BOOLEAN bResult = FALSE;

    if ( psProcess == NULL || pu8Subtable == NULL )
    {
        return FALSE;
    }

    if ( u16Position >= psProcess->sHeader.u16InLen )
    {
        return FALSE;
    }

    u16MarkGlyph = LE_GET_GLYPH_ID(psProcess->sHeader.pau32InGlyph[u16Position]);

    pMarkToMark = pMarkToMark + sizeof(U16);
    pConverage = (const U8 *)(pu8Subtable + LE_GET_OFFSET(pMarkToMark));
    s32MarkCoverageIndex = msAPI_MLE_LeGetGlyphCoverage(pConverage, u16MarkGlyph);

    pMarkToMark = pMarkToMark + sizeof(LE_Offset);
    if ( s32MarkCoverageIndex >= 0 )
    {
        LE_Points_t sMarkAnchor = {0, 0};
        S32 s32MarkArrayOffset = (S32)pMarkToMark + sizeof(LE_Offset) + sizeof(U16);
        const U8 *pMarkArray = (const U8 *)(pu8Subtable + LE_GET_OFFSET(s32MarkArrayOffset));
        S32 s32MarkClass = msAPI_MLE_LeMarkArrayGetMarkClass(pMarkArray, u16MarkGlyph, s32MarkCoverageIndex, &sMarkAnchor, &psProcess->sFontInstanceInf);
        S32 s32ClassCountOffset = (S32)pMarkToMark + sizeof(LE_Offset);
        U16 u16MarkCount = LE_GET_SHORT(s32ClassCountOffset);

        if ( s32MarkClass >= 0 && s32MarkClass < u16MarkCount )
        {
            U16 u16BasePosition = 0;
            U16 u16BaseGlyph = msAPI_MLE_LeGlyphStrGetNextBaseGlyph(psProcess->sHeader.pau32InGlyph, psProcess->sHeader.u16InLen, u16Position, 1, &u16BasePosition, psProcess->pClassDefTable, (LE_LOOKUP_FLAG_IGNORE_LIGATURES | LE_LOOKUP_FLAG_RIGHTTOLEFT), TRUE);
            S32 s32BaseCoverage = msAPI_MLE_LeGetGlyphCoverage((const U8 *)(pu8Subtable + LE_GET_OFFSET(pMarkToMark)), u16BaseGlyph);
            S32 s32Mark2ArrayOffset = (S32)pMarkToMark + sizeof(LE_Offset) + sizeof(U16) + sizeof(LE_Offset);
            const U8 *pMark2Array = pu8Subtable + LE_GET_OFFSET(s32Mark2ArrayOffset);
            U16 u16Mark2Count = LE_GET_SHORT(pMark2Array);

            //there has a ligature glyph in front of current mark position
            if ( s32BaseCoverage >= 0 && s32BaseCoverage < u16Mark2Count )
            {
                const U8 *pMark2Record = pMark2Array + sizeof(U16) + ((s32BaseCoverage * u16MarkCount) * sizeof(LE_Offset));
                S32 s32AnchorTableOffset = (S32)pMark2Record + (s32MarkClass * sizeof(LE_Offset));
                const U8 *pAnchorTable = (const U8 *) (pMark2Array + LE_GET_OFFSET(s32AnchorTableOffset));
                LE_Points_t sBaseAnchor, sMarkAdvance, sPixels;
        
                if ( s32AnchorTableOffset != 0 )
                {
                    S32 s32AnchorDiffX = 0;
                    S32 s32AnchorDiffY = 0;
                                        
                    msAPI_MLE_LeGetAnchor(pAnchorTable, u16BaseGlyph, &sBaseAnchor, &psProcess->sFontInstanceInf);
                    
                    msAPI_MLE_LeFontGetGlyphAdvance(u16MarkGlyph, &sPixels);
                    msAPI_MLE_LeFontPixelsToUnits(&psProcess->sFontInstanceInf, &sPixels, &sMarkAdvance);
                    
                    s32AnchorDiffX = sBaseAnchor.s32X - sMarkAnchor.s32X;
                    s32AnchorDiffY = sBaseAnchor.s32Y - sMarkAnchor.s32Y;
                    
                    psProcess->sHeader.u16BaseOffset = u16BasePosition;

                    if ( msAPI_MLE_LeFontIsGlyphRightToLeft(&psProcess->sFontInstanceInf, LE_GET_GLYPH_ID(psProcess->sHeader.pau32InGlyph[u16Position])) )
                    {               
                        psProcess->sPosInf.s32XPlacementAdjustment = s32AnchorDiffX;
                        psProcess->sPosInf.s32YPlacementAdjustment = s32AnchorDiffY;
                        psProcess->sPosInf.s32XAdvanceAdjustment = (-sMarkAdvance.s32X);
                        psProcess->sPosInf.s32YAdvanceAdjustment = (-sMarkAdvance.s32Y);
                    } 
                    else
                    {
                        LE_Points_t sBaseAdvance;
                        U16 u16SearchOffset = u16Position;

                        msAPI_MLE_LeFontGetGlyphAdvance(u16BaseGlyph, &sPixels);

                        u16SearchOffset = u16BasePosition + 1;
                        while ( u16SearchOffset < u16Position )
                        {
                            U16 u16OtherMarkGlyphId = LE_GET_GLYPH_ID(psProcess->sHeader.pau32InGlyph[u16SearchOffset]);
                            LE_Points_t sTempPixel;
                            
                            msAPI_MLE_LeFontGetGlyphAdvance(u16OtherMarkGlyphId, &sTempPixel);
                            sPixels.s32X += sTempPixel.s32X;
                            sPixels.s32Y += sTempPixel.s32Y;
                            u16SearchOffset = u16SearchOffset + 1;
                        }
   
                        msAPI_MLE_LeFontPixelsToUnits(&psProcess->sFontInstanceInf, &sPixels, &sBaseAdvance);

                        psProcess->sPosInf.s32XPlacementAdjustment = s32AnchorDiffX - sBaseAdvance.s32X;
                        psProcess->sPosInf.s32YPlacementAdjustment = s32AnchorDiffY - sBaseAdvance.s32Y;
                        psProcess->sPosInf.s32XAdvanceAdjustment = (-sMarkAdvance.s32X);
                        psProcess->sPosInf.s32YAdvanceAdjustment = (-sMarkAdvance.s32Y);
                    }

                    bResult = TRUE;
                }
            }
        }
    }
    return bResult;
}

static BOOLEAN _msAPI_MLE_LeProcessPositionLookups( LE_GPOSProcess_t *psProcess, const U8 *paLookupRecord, U16 u16LookupRecordCount, U16 u16Position )
{
    const U8 *pLookupList = NULL;
    S32 s32LookupListOffset;
    U16 u16LoookupListCount = 0;
    U16 i;

    if ( psProcess == NULL || paLookupRecord == NULL || u16LookupRecordCount == 0 )
    {
        return FALSE;
    }

    s32LookupListOffset = (S32)psProcess->pGPOS + sizeof(LE_Version) + sizeof(LE_Offset) + sizeof(LE_Offset);

    pLookupList = psProcess->pGPOS + LE_GET_SHORT(s32LookupListOffset);
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
            
            _msAPI_MLE_LeProcessPositionLookupTable(psProcess, pLookupTable, u16TempOffset);
        }
    }

    return TRUE;
}

static BOOLEAN _msAPI_MLE_LeProcessContextPositionTable( LE_GPOSProcess_t *psProcess, const U8 *pu8Subtable, U16 u16Position, LE_LookupFlag_e eLookupFlags )
{
    const U8 *pasLookupRecord = NULL;
    U16 u16RecordCount = 0;
    BOOLEAN bResult = FALSE;

    if ( psProcess == NULL || pu8Subtable == NULL )
    {
        return FALSE;
    }

    u16RecordCount = msAPI_MLE_LeContextTableGetLookupRecord(pu8Subtable, (void *)psProcess, psProcess->sHeader.pau32InGlyph, psProcess->sHeader.u16InLen, u16Position, &pasLookupRecord, eLookupFlags, FALSE);
    if ( u16RecordCount > 0 )
    {
        bResult = _msAPI_MLE_LeProcessPositionLookups(psProcess, pasLookupRecord, u16RecordCount, u16Position);
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_LeProcessChainingContextPositionTable( LE_GPOSProcess_t *psProcess, const U8 *pu8Subtable, U16 u16Position, LE_LookupFlag_e eLookupFlags )
{
    const U8 *pasLookupRecord = NULL;
    U16 u16RecordCount = 0;
    BOOLEAN bResult = FALSE;

    if ( psProcess == NULL || pu8Subtable == NULL )
    {
        return FALSE;
    }

    u16RecordCount = msAPI_MLE_LeChainingContextTableGetLookupRecord(pu8Subtable, (void *)psProcess, psProcess->sHeader.pau32InGlyph, psProcess->sHeader.u16InLen, u16Position, &pasLookupRecord, eLookupFlags, FALSE);
    if ( u16RecordCount > 0 )
    {
        bResult = _msAPI_MLE_LeProcessPositionLookups(psProcess, pasLookupRecord, u16RecordCount, u16Position);
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_LeProcessExtensionPositionTable( LE_GPOSProcess_t *psProcess, const U8 *pu8Subtable, U16 u16Position )
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
    if ( u16ExtensionLookupType != LE_POS_LOOKUP_EXTENSION ) 
    {
        const U8 *pExtTable = pu8Subtable + LE_GET_OFFSET(pExtension);
        
        bResult = _msAPI_MLE_LeProcessPositionLookupTable(psProcess, pExtTable, u16Position);
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_LeProcessPositionLookupSubtable( LE_GPOSProcess_t *psProcess, LE_PositionLookupType_e eLookupType, const U8 *pu8Subtable, U16 u16Position, LE_LookupFlag_e eLookupFlags )
{
    BOOLEAN bResult = FALSE;

    if ( psProcess == NULL || pu8Subtable == NULL )
    {
        return FALSE;
    }

    switch( eLookupType )
    {
        case LE_POS_LOOKUP_SINGLE_ADJUSTMENT:
        {
            bResult = _msAPI_MLE_LeProcessSingleAdjPositionTable(psProcess, pu8Subtable, u16Position);
            break;
        }

        case LE_POS_LOOKUP_PAIR_ADJUSTMENT:
        {
            bResult = _msAPI_MLE_LeProcessPairAdjPositionTable(psProcess, pu8Subtable, u16Position);
            break;
        }

        case LE_POS_LOOKUP_CURSIVE_ATTACHMENT:
        {
            bResult = _msAPI_MLE_LeProcessCursiveAttPositionTable(psProcess, pu8Subtable, u16Position);
            break;
        }

        case LE_POS_LOOKUP_MARKTOBASE_ATTACHMENT:
        {
            bResult = _msAPI_MLE_LeProcessMarkToBaseAttPositionTable(psProcess, pu8Subtable, u16Position);
            break;
        }

        case LE_POS_LOOKUP_MARKTOLIGATURE_ATTACHEMENT:
        {
            bResult = _msAPI_MLE_LeProcessMarkToLigatureAttPositionTable(psProcess, pu8Subtable, u16Position);
            break;
        }

        case LE_POS_LOOKUP_MARKTOMARK_ATTACHEMENT:
        {
            bResult = _msAPI_MLE_LeProcessMarkToMarkAttPositionTable(psProcess, pu8Subtable, u16Position);
            break;
        }

        case LE_POS_LOOKUP_CONTEXT:
        {
            bResult = _msAPI_MLE_LeProcessContextPositionTable(psProcess, pu8Subtable, u16Position, eLookupFlags);
            break;
        }

        case LE_POS_LOOKUP_CHAINED_CONTEXT:
        {
            bResult = _msAPI_MLE_LeProcessChainingContextPositionTable(psProcess, pu8Subtable, u16Position, eLookupFlags);
            break;
        }

        case LE_POS_LOOKUP_EXTENSION:
        {
            bResult = _msAPI_MLE_LeProcessExtensionPositionTable(psProcess, pu8Subtable, u16Position);
            break;
        }

        case LE_POS_LOOKUP_INVALID:
        default:
            break;
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_LeProcessPositionLookupTable( LE_GPOSProcess_t *psProcess, const U8 *pu8Table, U16 u16Position )
{
    const U8 *pLookup = pu8Table;
    U16 u16SubtableCount = 0;
    U16 i;
    LE_PositionLookupType_e eLookupType;
    LE_LookupFlag_e eLookupFlags;
    BOOLEAN bResult = FALSE;

    if ( psProcess == NULL || pu8Table == NULL )
    {
        return FALSE;
    }
    
    eLookupType = (LE_PositionLookupType_e)LE_GET_SHORT(pLookup);

    pLookup = pLookup + sizeof(U16);
    eLookupFlags = (LE_LookupFlag_e)LE_GET_SHORT(pLookup);
    
    pLookup = pLookup + sizeof(U16) + sizeof(U16);
    u16SubtableCount = LE_GET_SHORT(pLookup);
    
    for ( i = 0; i < u16SubtableCount; i++ ) 
    {   
        const U8 *pLookupSubtable = (const U8 *)msAPI_MLE_LeLookupTableGetLookupSubtable(pu8Table, i);

        bResult = _msAPI_MLE_LeProcessPositionLookupSubtable(psProcess, eLookupType, pLookupSubtable, u16Position, eLookupFlags);

        if ( bResult )
        {
            break;
        }
    }

    return bResult;
}

BOOLEAN msAPI_MLE_LeProcessPosLookupTable( LE_GPOSProcess_t *psProcess, const U8 *pLookupTable, U16 u16SubtableIndex, U16 u16Position )
{
    const U8 *pTempLookupTable = pLookupTable;
    LE_PositionLookupType_e eLookupType;
    LE_LookupFlag_e eLookupFlags;
    U16 u16SubtableCount = 0;
    BOOLEAN bResult = FALSE;

    if ( psProcess == NULL || pLookupTable == NULL )
    {
        return FALSE;
    }

    eLookupType = (LE_PositionLookupType_e)LE_GET_SHORT(pTempLookupTable);

    pTempLookupTable = pTempLookupTable + sizeof(U16);
    eLookupFlags = (LE_LookupFlag_e)LE_GET_SHORT(pTempLookupTable);
    
    pTempLookupTable = pTempLookupTable + sizeof(U16);
    u16SubtableCount = LE_GET_SHORT(pTempLookupTable);

    if ( u16SubtableIndex < u16SubtableCount )
    {
        const U8 *pSubtable = msAPI_MLE_LeLookupTableGetLookupSubtable(pLookupTable, u16SubtableIndex);

        bResult = _msAPI_MLE_LeProcessPositionLookupSubtable(psProcess, eLookupType, pSubtable, u16Position, eLookupFlags);
    }

    return bResult;
}

const U8* msAPI_MLE_LePosGetScriptListTable( const U8 *pPosTable )
{
    S32 s32ScriptListOffset = (S32)pPosTable + sizeof(LE_Version);

    if ( pPosTable == NULL )
    {
        return NULL;
    }

    return (pPosTable + LE_GET_OFFSET(s32ScriptListOffset));        
}

const U8* msAPI_MLE_LePosGetFeatureListTable( const U8 *pPosTable )
{
    S32 s32FeatureListOffset = (S32)pPosTable + sizeof(LE_Version) + sizeof(LE_Offset);

    if ( pPosTable == NULL )
    {
        return NULL;
    }

    return (pPosTable + LE_GET_OFFSET(s32FeatureListOffset));       
}

const U8* msAPI_MLE_LePosGetLookupListTable( const U8 *pPosTable )
{
    S32 s32LookupListOffset = (S32)pPosTable + sizeof(LE_Version) + sizeof(LE_Offset) + sizeof(LE_Offset);

    if ( pPosTable == NULL )
    {
        return NULL;
    }

    return (pPosTable + LE_GET_OFFSET(s32LookupListOffset));        
}

#endif //__FEATURE_VECTOR_FONT__

#endif //__MSAPI_MLE_LE_OTF_SUBST_C__
