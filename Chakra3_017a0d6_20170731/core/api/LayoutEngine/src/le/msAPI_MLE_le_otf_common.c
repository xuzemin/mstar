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
#include "msAPI_MLE_le_util.h"
#include "msAPI_MLE_le_otf_common.h"
#include "msAPI_MLE_le_otf_subst.h"
#include "msAPI_MLE_le_otf_pos.h"
#include "msAPI_MLE_font_hindi_priv.h"

static const U16 g_au16BeforeMask[] = 
{
    0x0000,
    0x0001,
    0x0003,
    0x0007,
    0x000F,
    0x001F,
    0x003F,
    0x007F,
    0x00FF,
    0x01FF,
    0x03FF,
    0x07FF,
    0x0FFF,
    0x1FFF,
    0x3FFF,
    0x7FFF,
    0xFFFF
};

static const S16 g_as16BitsInNibble[] =
{
    0 + 0 + 0 + 0,
    0 + 0 + 0 + 1,
    0 + 0 + 1 + 0,
    0 + 0 + 1 + 1,
    0 + 1 + 0 + 0,
    0 + 1 + 0 + 1,
    0 + 1 + 1 + 0,
    0 + 1 + 1 + 1,
    1 + 0 + 0 + 0,
    1 + 0 + 0 + 1,
    1 + 0 + 1 + 0,
    1 + 0 + 1 + 1,
    1 + 1 + 0 + 0,
    1 + 1 + 0 + 1,
    1 + 1 + 1 + 0,
    1 + 1 + 1 + 1
};

static const U16 g_au16FieldMasks[]    = {0x0003, 0x000F, 0x00FF};
static const U16 g_au16FieldSignBits[] = {0x0002, 0x0008, 0x0080};
static const U16 g_au16FieldBits[]     = {     2,      4,      8};

#define DEVICE_TABLE_FORMAT_COUNT (sizeof(g_au16FieldBits)/sizeof(U16))

#define LE_VALUE_NIBBLE(_value, _nibble) ((_value >> (_nibble * 4)) & 0xF)
#define LE_VALUE_NIBBLE_BITS(_value, _nibble) (g_as16BitsInNibble[LE_VALUE_NIBBLE(_value, _nibble)])


static S32 _msAPI_MLE_LegetGlyphRangeIndex( const U8 *pu8Records, U16 u16GlyphId, U16 u16RecordSize )
{
    const U8 *pu8TempRecords = pu8Records;
    S32 s32Low = 0;
    S32 s32High;
    S32 s32Return = -1;
    
    if ( pu8Records == NULL || u16RecordSize == 0 )
    {
        return -1;
    }
    
    //binary search
    s32High = u16RecordSize - 1;

    while ( s32Low <= s32High )
    {
        S32 s32Mid = (s32Low + s32High)/2;
        U16 u16First;
        U16 u16Last;

        pu8TempRecords = pu8Records + (s32Mid * LE_GlyphRangeRecord_SIZE);
        
        u16First = LE_GET_GLYPHID(pu8TempRecords);

        pu8TempRecords = pu8TempRecords + sizeof(LE_GlyphId);
        u16Last = LE_GET_GLYPHID(pu8TempRecords);
        
        if ( u16GlyphId <= u16First )
        {
            if ( u16GlyphId == u16First )
            {
                s32Return = s32Mid;
                break;
            }

            s32High = s32Mid - 1;    
        }
        else
        {
            if ( u16GlyphId <= u16Last )
            {
                s32Return = s32Mid;
                break;
            }
        
            s32Low = s32Mid + 1;
        }
    }

    return s32Return;
}

static S32 _msAPI_MLE_LeGetGlyphFormat1Coverage( const U8 *pu8Format1, U16 u16GlyphId )
{
    const U8 *pu8TempFormat1 = pu8Format1;
    U16 u16GlyphCount;
    S32 s32Low = 0;
    S32 s32High;
    S32 s32Return = -1;
    
    if ( pu8Format1 == NULL )
    {
        return -1;
    }

    //binary search
    u16GlyphCount = LE_GET_SHORT(pu8TempFormat1);
    s32High = u16GlyphCount - 1;

    pu8TempFormat1 = pu8TempFormat1 + sizeof(U16);
    while ( s32Low <= s32High )
    {
        S32 s32Mid = (s32Low + s32High)/2;
        U16 u16Glyph;
        S32 s32GlyphOffset = (S32)pu8TempFormat1 + (s32Mid * sizeof(U16));

        u16Glyph = LE_GET_SHORT(s32GlyphOffset);
            
        if ( u16GlyphId <= u16Glyph )
        {
            if ( u16GlyphId == u16Glyph )
            {
                s32Return = s32Mid;
                break;
            }
            s32High = s32Mid - 1;    
        }
        else
        {
            s32Low = s32Mid + 1;
        }
    }

    return s32Return;
}

static S32 _msAPI_MLE_LeGetGlyphFormat2Coverage( const U8 *pu8Format2, U16 u16GlyphId )
{
    const U8 *pu8TempFormat2 = pu8Format2;
    U16 u16RangeCount;
    S32 s32RangeIndex = -1;
    S32 s32RangeOffset;
    U16 u16StartGlyph;
    U16 u16StartConverIndex;

    if ( pu8Format2 == NULL )
    {
        return (U16)(-1);
    }

    u16RangeCount = LE_GET_SHORT(pu8TempFormat2);
    pu8TempFormat2 = pu8TempFormat2 + sizeof(U16);
    s32RangeIndex = _msAPI_MLE_LegetGlyphRangeIndex(pu8TempFormat2, u16GlyphId, u16RangeCount);
    if ( s32RangeIndex < 0)
    {
        return -1;
    }

    s32RangeOffset = (S32)pu8TempFormat2 + (s32RangeIndex * LE_GlyphRangeRecord_SIZE);

    u16StartGlyph = LE_GET_SHORT(s32RangeOffset);

    s32RangeOffset = s32RangeOffset + sizeof(U16) + sizeof(U16);
    u16StartConverIndex = LE_GET_SHORT(s32RangeOffset);

    return (S32)(u16StartConverIndex + (u16GlyphId - u16StartGlyph));
}

static S32 _msAPI_MLE_LeGetGlyphFormat1Class( const U8 *pu8Format1, U16 u16GlyphId )
{
    const U8 *pu8TempFormat1 = pu8Format1;
    S32 s32Result = -1;
    U16 u16Start = (U16)(-1);
        
    if ( pu8Format1 == NULL )
    {
        return -1;
    }

    u16Start = LE_GET_SHORT(pu8Format1);
    pu8TempFormat1 = pu8TempFormat1 + sizeof(U16);
    
    if ( u16GlyphId >= u16Start && u16GlyphId < (u16Start + LE_GET_SHORT(pu8TempFormat1)) )
    {
        pu8TempFormat1 = pu8TempFormat1 + sizeof(U16);
        pu8TempFormat1 = pu8TempFormat1 + ((u16GlyphId - u16Start) * sizeof(U16));
        s32Result = LE_GET_SHORT(pu8TempFormat1);
    }

    return s32Result;
}

static S32 _msAPI_MLE_LeGetGlyphFormat2Class( const U8 *pu8Format2, U16 u16GlyphId )
{
    const U8 *pu8TempFormat2 = pu8Format2;
    U16 u16ClassRangeCount;
    S32 s32Return = -1;
    S32 s32RangeIndex = -1;

    if ( pu8Format2 == NULL )
    {
        return -1;
    }

    u16ClassRangeCount =  LE_GET_SHORT(pu8TempFormat2);
    pu8TempFormat2 = pu8TempFormat2 + sizeof(U16);

    s32RangeIndex = _msAPI_MLE_LegetGlyphRangeIndex(pu8TempFormat2, u16GlyphId, u16ClassRangeCount);
    if ( s32RangeIndex < 0)
    {
        return -1;
    }

    pu8TempFormat2 = pu8TempFormat2 + (s32RangeIndex * LE_GlyphRangeRecord_SIZE);
    pu8TempFormat2 = pu8TempFormat2 + sizeof(U16) + sizeof(U16);

    s32Return = LE_GET_SHORT(pu8TempFormat2);

    return s32Return;
}

static BOOLEAN _msAPI_MLE_LeHasGlyphFormat1Class( const U8 *pu8Format1, S32 s32GlyphClass )
{
    const U8 *pu8TempFormat1 = pu8Format1;
    U16 u16GlyphClassCount = 0;
    BOOLEAN bResult = FALSE;
    U16 i;
        
    if ( pu8Format1 == NULL )
    {
        return FALSE;
    }

    pu8TempFormat1 = pu8TempFormat1 + sizeof(U16);
    u16GlyphClassCount = LE_GET_SHORT(pu8TempFormat1);

    pu8TempFormat1 = pu8TempFormat1 + sizeof(U16);
    for ( i = 0; i < u16GlyphClassCount; i++ )
    {
        S32 s32GlyphClassOffset = (S32)pu8TempFormat1 + (i * sizeof(U16));
        
        if ( s32GlyphClass == LE_GET_SHORT(s32GlyphClassOffset) )
        {
            bResult = TRUE;
            break;
        }
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_LeHasGlyphFormat2Class( const U8 *pu8Format2, S32 s32GlyphClass )
{
    const U8 *pu8TempFormat2 = pu8Format2;
    U16 u16ClassRangeCount = 0;
    BOOLEAN bResult = FALSE;
    U16 i;
        
    if ( pu8Format2 == NULL )
    {
        return FALSE;
    }

    u16ClassRangeCount = LE_GET_SHORT(pu8TempFormat2);
    pu8TempFormat2 = pu8TempFormat2 + sizeof(U16);

    for ( i = 0; i < u16ClassRangeCount; i++ )
    {
        S32 s32GlyphClassOffset = (S32)pu8TempFormat2 + (i * LE_GlyphRangeRecord_SIZE) + sizeof(U16) + sizeof(U16);
        if ( s32GlyphClass == LE_GET_SHORT(s32GlyphClassOffset) )
        {
            bResult = TRUE;
            break;
        }
    }

    return bResult;

}

S32 msAPI_MLE_LeGetGlyphCoverage( const U8 *pu8Cover, U16 u16GlyphId )
{
    S32 s32Result = -1;
        
    if ( pu8Cover == NULL )
    {
        return -1;
    }

    switch( LE_GET_SHORT(pu8Cover) )
    {
        case LE_COVERAGE_TABLE_FORMAT_1:
        {
            s32Result = _msAPI_MLE_LeGetGlyphFormat1Coverage((pu8Cover + sizeof(U16)), u16GlyphId);
            break;
        }

        case LE_COVERAGE_TABLE_FORMAT_2:
        {
            s32Result = _msAPI_MLE_LeGetGlyphFormat2Coverage((pu8Cover + sizeof(U16)), u16GlyphId);
            break;
        }

        case LE_COVERAGE_TABLE_FORMAT_INVALID:
        default:
            break;
    }

    return s32Result;
}

S32 msAPI_MLE_LeGetGlyphClass( const U8 *pDefTable, U16 u16GlyphId )
{
    S32 s32Result = -1;
        
    if ( pDefTable == NULL )
    {
        return -1;
    }

    switch( LE_GET_SHORT(pDefTable) ) 
    {
        case LE_CLASS_DEFINITION_FORMAT_1:
        {
            s32Result = _msAPI_MLE_LeGetGlyphFormat1Class((pDefTable + sizeof(U16)), u16GlyphId);
            break;
        }

        case LE_CLASS_DEFINITION_FORMAT_2:
        {
            s32Result = _msAPI_MLE_LeGetGlyphFormat2Class((pDefTable + sizeof(U16)), u16GlyphId);
            break;
        }

        case LE_CLASS_DEFINITION_FORMAT_INVALID:
        default:
            break;
    }

    return s32Result;
}

BOOLEAN msAPI_MLE_LeHasGlyphClass( const U8 *pDefTable, S32 s32GlyphClass )
{
    BOOLEAN bResult = FALSE;
        
    if ( pDefTable == NULL )
    {
        return FALSE;
    }

    switch( LE_GET_SHORT(pDefTable) )
    {
        case LE_CLASS_DEFINITION_FORMAT_1:
        {
            bResult = _msAPI_MLE_LeHasGlyphFormat1Class((pDefTable + sizeof(U16)), s32GlyphClass);
            break;
        }

        case LE_CLASS_DEFINITION_FORMAT_2:
        {
            bResult = _msAPI_MLE_LeHasGlyphFormat2Class((pDefTable + sizeof(U16)), s32GlyphClass);
            break;
        }

        case LE_CLASS_DEFINITION_FORMAT_INVALID:
        default:
            break;
    }

    return bResult;
}

S16 msAPI_MLE_LeValueGetFieldCount( LE_ValueFormat_e eValueFormat )
{
    LE_ValueFormat_e eValue = (eValueFormat & (~LE_VALUE_RESERVED));

    return (LE_VALUE_NIBBLE_BITS(eValue, 0) + LE_VALUE_NIBBLE_BITS(eValue, 1) + LE_VALUE_NIBBLE_BITS(eValue, 2) + LE_VALUE_NIBBLE_BITS(eValue, 3));
}

S16 msAPI_MLE_LeValueGetSize( LE_ValueFormat_e eValueFormat )
{
    return msAPI_MLE_LeValueGetFieldCount(eValueFormat) * sizeof(S16);
}

S16 msAPI_MLE_LeValueGetFieldIndex( LE_ValueFormat_e eValueFormat, S16 s16Field )
{
    return msAPI_MLE_LeValueGetFieldCount((eValueFormat & g_au16BeforeMask[s16Field]));
}

U16 msAPI_MLE_LeValueGetFieldValue( const U8 *pValueRecord, LE_ValueFormat_e eValueFormat, S16 s16Field )
{
    S16 s16ValueIndex = msAPI_MLE_LeValueGetFieldIndex(eValueFormat, s16Field);
    S32 s32ValueOffset = (S32)pValueRecord + (s16ValueIndex * sizeof(U16));
    S16 value = LE_GET_SHORT(s32ValueOffset);

    return value;
}

S16 msAPI_MLE_LeDeviceTableGetAdjustment( const U8 *pDeviceTable, U16 u16PixelsPerEM )
{  
    const U8 *pDevice = pDeviceTable;
    U16 u16Start;
    U16 u16End;
    U16 u16Format;
    S16 s16Result = 0;

    if ( pDeviceTable == NULL )
    {
        return 0;
    }

    u16Start = LE_GET_SHORT(pDevice);

    pDevice = pDevice + sizeof(U16);
    u16End = LE_GET_SHORT(pDevice);

    pDevice = pDevice + sizeof(U16);
    u16Format = LE_GET_SHORT(pDevice) - 1;
    
    if ( u16PixelsPerEM >= u16Start && u16PixelsPerEM <= u16End && u16Format < DEVICE_TABLE_FORMAT_COUNT )
    {
        U16 u16SizeIndex = u16PixelsPerEM - u16Start;
        U16 u16Bits = g_au16FieldBits[u16Format];
        U16 u16Count = 16 / u16Bits;
        S32 s32DeltaValueOffset = (S32)pDevice + sizeof(U16) + ((u16SizeIndex/u16Count) * sizeof(U16));
        U16 u16Word = LE_GET_SHORT(s32DeltaValueOffset);
        U16 u16FieldIndex = u16SizeIndex % u16Count;
        U16 u16Shift = 16 - (u16Bits * (u16FieldIndex + 1));
        U16 u16Field = (u16Word >> u16Shift) & g_au16FieldMasks[u16Format];

        s16Result = u16Field;

        if ( (u16Field & g_au16FieldSignBits[u16Format]) != 0 )
        {
            s16Result = (s16Result | (~g_au16FieldMasks[u16Format]));
        }
    }

    return s16Result;
}

static BOOLEAN _msAPI_MLE_LeGetFormat1Anchor( const U8 *pAnchorTable, LE_Points_t *pAnchor, LE_FontInstanceInf_t *pFontInstanceInf )
{
    const U8 *pFormat1 = pAnchorTable;
    S16 s16X = 0, s16Y = 0;
    LE_Points_t sPixels = {0, 0};

    if ( pAnchorTable == NULL || pAnchor == NULL || pFontInstanceInf == NULL )
    {
        return FALSE;
    }

    pFormat1 = pFormat1 + sizeof(U16);
    s16X = LE_GET_SHORT(pFormat1);

    pFormat1 = pFormat1 + sizeof(S16);
	s16Y = LE_GET_SHORT(pFormat1);

    msAPI_MLE_LeFontTransformUnit(pFontInstanceInf, s16X, s16Y, &sPixels);
    msAPI_MLE_LeFontPixelsToUnits(pFontInstanceInf, &sPixels, pAnchor);

    return TRUE;
}

static BOOLEAN _msAPI_MLE_LeGetFormat2Anchor( const U8 *pAnchorTable, U16 u16GlyphId, LE_Points_t *pAnchor, LE_FontInstanceInf_t *pFontInstanceInf )
{
    const U8 *pFormat2 = pAnchorTable;
    S32 s32AnchorPointOffset;
    LE_Points_t sPoints = {0, 0};

    if ( pAnchorTable == NULL || pAnchor == NULL || pFontInstanceInf == NULL )
    {
        return FALSE;
    }

    u16GlyphId = u16GlyphId;
    
    pFormat2 = pFormat2 + sizeof(U16);
    s32AnchorPointOffset = (S32)pFormat2 + sizeof(S16) + sizeof(S16);
    //if ( !msAPI_MLE_LeFontGetGlyphPoint(u16GlyphId, LE_GET_SHORT(s32AnchorPointOffset), &sPoints) )
    {
        S16 s16X;
        S16 s16Y;

        s16X = LE_GET_SHORT(pFormat2);

        pFormat2 = pFormat2 + sizeof(S16);
        s16Y = LE_GET_SHORT(pFormat2);

        msAPI_MLE_LeFontTransformUnit(pFontInstanceInf, s16X, s16Y, &sPoints);
    }

    msAPI_MLE_LeFontPixelsToUnits(pFontInstanceInf, &sPoints, pAnchor);

    return TRUE;
}

static BOOLEAN _msAPI_MLE_LeGetFormat3Anchor( const U8 *pAnchorTable, LE_Points_t *pAnchor, LE_FontInstanceInf_t *pFontInstanceInf )
{
    const U8 *pFormat3 = pAnchorTable;
    S16 s16X = 0;
    S16 s16Y = 0;
    S32 s32XDeviceTableOffset = 0;
    S32 s32YDeviceTableOffset = 0;
    LE_Points_t sPixels = {0, 0};

    if ( pAnchorTable == NULL || pAnchor == NULL || pFontInstanceInf == NULL )
    {
        return FALSE;
    }

    pFormat3 = pFormat3 + sizeof(U16);
    s16X = LE_GET_SHORT(pFormat3);

    pFormat3 = pFormat3 + sizeof(S16);
    s16Y = LE_GET_SHORT(pFormat3);

    pFormat3 = pFormat3 + sizeof(S16);
    s32XDeviceTableOffset = LE_GET_OFFSET(pFormat3);

    pFormat3 = pFormat3 + sizeof(LE_Offset);
    s32YDeviceTableOffset = LE_GET_OFFSET(pFormat3);

    msAPI_MLE_LeFontTransformUnit(pFontInstanceInf, s16X, s16Y, &sPixels);

    if ( s32XDeviceTableOffset != 0 )
    {
        const U8 *pDeviceTableX = pAnchorTable + s32XDeviceTableOffset;
        S16 s16Adjx = msAPI_MLE_LeDeviceTableGetAdjustment(pDeviceTableX, pFontInstanceInf->u16XPixelsPerEM);

        sPixels.s32X = sPixels.s32X + s16Adjx;
    }

    if ( s32YDeviceTableOffset != 0 )
    {
        const U8 *pDeviceTableY = pAnchorTable + s32YDeviceTableOffset;
        S16 s16Adjy = msAPI_MLE_LeDeviceTableGetAdjustment(pDeviceTableY, pFontInstanceInf->u16YPixelsPerEM);

        sPixels.s32Y = sPixels.s32Y + s16Adjy;
    }

    msAPI_MLE_LeFontPixelsToUnits(pFontInstanceInf, &sPixels, pAnchor);
    return TRUE;
}

BOOLEAN msAPI_MLE_LeGetAnchor( const U8 *pAnchorTable, U16 u16GlyphId, LE_Points_t *pAnchor, LE_FontInstanceInf_t *pFontInstanceInf )
{
    BOOLEAN bResult = FALSE;
        
    if ( pAnchorTable == NULL || pAnchor == NULL || pFontInstanceInf == NULL )
    {
        return FALSE;
    }

    switch( LE_GET_SHORT(pAnchorTable) )
    {
        case LE_ANCHOR_TABLE_FORMAT_2:
        {
            bResult = _msAPI_MLE_LeGetFormat2Anchor(pAnchorTable, u16GlyphId, pAnchor, pFontInstanceInf);
            break;
        }

        case LE_ANCHOR_TABLE_FORMAT_3:
        {
            bResult = _msAPI_MLE_LeGetFormat3Anchor(pAnchorTable, pAnchor, pFontInstanceInf);
            break;
        }

        case LE_ANCHOR_TABLE_FORMAT_1:
        case LE_ANCHOR_TABLE_FORMAT_INVALID:
        default:
            bResult = _msAPI_MLE_LeGetFormat1Anchor(pAnchorTable, pAnchor, pFontInstanceInf);
            break;
    }

    return bResult;
}

S32 msAPI_MLE_LeMarkArrayGetMarkClass(const U8 *pMarks, U16 u16GlyphId, S32 s32CoverageIndex, LE_Points_t *pAnchor, LE_FontInstanceInf_t *pFontInstance)
{
    const U8 *pTempMarks = pMarks;
    S32 s32MarkClass = -1;

    if ( pAnchor == NULL || pFontInstance == NULL )
    {
        return -1;
    }

    if ( s32CoverageIndex >= 0 )
    {
        if ( s32CoverageIndex < LE_GET_SHORT(pTempMarks) )
        {
            const U8 *pMarkRecord = pMarks + sizeof(U16) + (s32CoverageIndex * LE_MarkRecord_Size);
            S32 s32MarkAnchorTableOffset = (S32)pMarkRecord + sizeof(U16);
            const U8 *pAnchorTable = pMarks + LE_GET_OFFSET(s32MarkAnchorTableOffset);

            msAPI_MLE_LeGetAnchor(pAnchorTable, u16GlyphId, pAnchor, pFontInstance);
            s32MarkClass = LE_GET_SHORT(pMarkRecord);
        }
    }

    return s32MarkClass;
}

static BOOLEAN _msAPI_MLE_LeMatchGlyphId( const U32 *paGlyphId, U16 u16GlyphLen, U16 u16Position, const U8 *pCompareGlyph, U16 u16CompareCount, BOOLEAN bBackTrack )
{
    S32 s32Direction = 1;
    U16 u16CurrentMatched = 0;
    U16 u16CurrentOffset;
    U16 u16TempCompareCount = u16CompareCount;
    BOOLEAN bResult = TRUE;

    if ( paGlyphId == NULL || pCompareGlyph == NULL || u16GlyphLen == 0 || u16CompareCount == 0 )
    {
        return FALSE;
    }

    if ( bBackTrack ) 
    {
        if ( u16Position < u16CompareCount )
        {
            return FALSE;
        }
    
        u16CurrentMatched = u16CompareCount - 1;
        s32Direction = -1;
    }
    else
    {
        if ( u16Position + u16CompareCount >= u16GlyphLen )
        {
            return FALSE;
        }
    }

    u16CurrentOffset = u16Position + s32Direction;

    while ( u16TempCompareCount > 0 ) 
    {
        S32 s32CompareOffset = (S32)pCompareGlyph + (u16CurrentMatched * sizeof(LE_GlyphId));
        if ( LE_GET_GLYPH_ID(paGlyphId[u16CurrentOffset]) != LE_GET_GLYPHID(s32CompareOffset) ) 
        {
            bResult = FALSE;
            break;
        }

        u16CompareCount--;
        u16CurrentOffset = u16CurrentOffset + s32Direction;
        u16CurrentMatched = u16CurrentMatched + s32Direction;
    }

    return bResult;
}

static U16 _msAPI_MLE_LeContextFormat1TableGetLookupRecord( const U8* psContext, const U32 *paGlyphId, U16 u16GlyphLen, U16 u16Position, const U8 **ppasRecords )
{
    const U8 *psFormat1 = psContext;
    const U8 *pConverage = NULL;
    U16 u16GlyphId = (U16)(-1);
    S32 s32CoverageIndex = -1;
    U16 u16RecordCount = 0;

    if ( psContext == NULL || paGlyphId == NULL || u16GlyphLen == 0 || ppasRecords == NULL )
    {
        return 0;
    }

    if ( u16Position >= u16GlyphLen )
    {
        return 0;
    }

    u16GlyphId = LE_GET_GLYPH_ID(paGlyphId[u16Position]);

    psFormat1 = psFormat1 + sizeof(U16);
    pConverage = psContext + LE_GET_OFFSET(psFormat1);
    s32CoverageIndex = msAPI_MLE_LeGetGlyphCoverage(pConverage, u16GlyphId);

    psFormat1 = psFormat1 + sizeof(LE_Offset);
    if ( s32CoverageIndex >= 0 ) 
    {
        U16 u16SubstRuleSetCount = LE_GET_SHORT(psFormat1);

        psFormat1 = psFormat1 + sizeof(U16);
        if ( s32CoverageIndex < u16SubstRuleSetCount )
        {   
            S32 s32RuleSetTableOffset = (S32)psFormat1 + (s32CoverageIndex * sizeof(LE_Offset));
            const U8 *pSubstRuleSetTable = psContext + LE_GET_OFFSET(s32RuleSetTableOffset);
            U16 u16SubRuleCount = LE_GET_SHORT(pSubstRuleSetTable);
            U16 i;

            for ( i = 0; i < u16SubRuleCount; i++ ) 
            {
                S32 s32SubRuleTableOffset = (S32)pSubstRuleSetTable + sizeof(U16) + (i * sizeof(LE_Offset));
                const U8 *pSubRuleTable = pSubstRuleSetTable + LE_GET_OFFSET(s32SubRuleTableOffset);
                U16 u16GlyphCount = LE_GET_SHORT(pSubRuleTable) - 1;

                pSubRuleTable = pSubRuleTable + sizeof(U16);
                if ( _msAPI_MLE_LeMatchGlyphId(paGlyphId, u16GlyphLen, u16Position, (pSubRuleTable + sizeof(U16)), u16GlyphCount, FALSE) )
                {
                    u16RecordCount = LE_GET_SHORT(pSubRuleTable);
                    *ppasRecords = pSubRuleTable + sizeof(U16) + (u16GlyphCount * sizeof(U16));
                    break;
                }
            }
        }
    }
    
    return u16RecordCount;
}

static BOOLEAN _msAPI_MLE_LeMatchGlyphClass( const U8 *psClassDefinitionTable, void *psProcess, const U32 *paGlyphId, U16 u16GlyphLen, U16 u16Position, const U8 *pauClass, U16 u16ClassCount, LE_LookupFlag_e eLookupFlags, BOOLEAN bBackTrack, BOOLEAN bLookAhead, BOOLEAN bGSUB )
{
    S32 s32Direction = 1;
    S32 s32CurrentMatched = 0;
    U16 u16CurrentOffset;
    U16 u16CompareCount = u16ClassCount;
    BOOLEAN bResult = TRUE;

    if ( paGlyphId == NULL || pauClass == NULL || psClassDefinitionTable == NULL || u16GlyphLen == 0 || u16ClassCount == 0 )
    {
        return FALSE;
    }

    if ( bBackTrack ) 
    {
        if ( u16Position < u16ClassCount )
        {
            return FALSE;
        }
    
        s32CurrentMatched = u16ClassCount - 1;
        s32Direction = -1;
    }
    else
    {
        if ( u16Position + u16ClassCount >= u16GlyphLen )
        {
            return FALSE;
        }
    }

    u16CurrentOffset = u16Position + s32Direction;

    while ( u16CompareCount > 0 )
    {
        S32 s32GlyphClass = 0, s32MarkAttachmentClass = 0;
        S32 s32ClassOffset = 0, s32MatchedClass = 0;
        U16 u16CurrentOffset1 = u16CurrentOffset;
        
        if ( bLookAhead )
        {
            while(1)
            {
                if ( bGSUB )
                {
                    s32MarkAttachmentClass = msAPI_MLE_LeGetGlyphClass(((LE_GSUBProcess_t *)psProcess)->pMarkAttachClassDefTable, LE_GET_GLYPH_ID(paGlyphId[u16CurrentOffset1]));
                }
                else
                {
                    s32MarkAttachmentClass = msAPI_MLE_LeGetGlyphClass(((LE_GPOSProcess_t *)psProcess)->pMarkAttachClassDefTable, LE_GET_GLYPH_ID(paGlyphId[u16CurrentOffset1]));
                }
                //s32GlyphClass = msAPI_MLE_LeGetGlyphClass(psClassDefinitionTable, LE_GET_GLYPH_ID(paGlyphId[u16CurrentOffset]));
                
                //MarkAttachmentType: 0xFF00
                if ( ((eLookupFlags & 0xFF00) >> 8 ) == s32MarkAttachmentClass )
                {
                    u16CurrentOffset = u16CurrentOffset1;
                    break;
                }
                else
                {
                    u16CurrentOffset1++;
                    if ( u16CurrentOffset1 >= u16GlyphLen )
                    {
                        break;
                    }
                }
            }
        }
        else if (bBackTrack)
        {
            while (1)
            {
                if (bGSUB)
                {
                    s32MarkAttachmentClass = msAPI_MLE_LeGetGlyphClass(((LE_GSUBProcess_t *)psProcess)->pMarkAttachClassDefTable, LE_GET_GLYPH_ID(paGlyphId[u16CurrentOffset1]));
                }
                else
                {
                    s32MarkAttachmentClass = msAPI_MLE_LeGetGlyphClass(((LE_GPOSProcess_t *)psProcess)->pMarkAttachClassDefTable, LE_GET_GLYPH_ID(paGlyphId[u16CurrentOffset1]));
                }
                //s32GlyphClass = msAPI_MLE_LeGetGlyphClass(psClassDefinitionTable, LE_GET_GLYPH_ID(paGlyphId[u16CurrentOffset]));

                //MarkAttachmentType: 0xFF00
                if (((eLookupFlags & 0xFF00) >> 8) == s32MarkAttachmentClass)
                {
                    u16CurrentOffset = u16CurrentOffset1;
                    break;
                }
                else
                {
                    u16CurrentOffset1--;
                    if (u16CurrentOffset1 == 0xffff)
                    {
                        break;
                    }
                }
            }
        }
        else
        {
            if ( u16Position < u16GlyphLen )
            {
                while (1)
                {
                    if (bGSUB)
                    {
                        s32MarkAttachmentClass = msAPI_MLE_LeGetGlyphClass(((LE_GSUBProcess_t *)psProcess)->pMarkAttachClassDefTable, LE_GET_GLYPH_ID(paGlyphId[u16CurrentOffset1]));
                    }
                    else
                    {
                        s32MarkAttachmentClass = msAPI_MLE_LeGetGlyphClass(((LE_GPOSProcess_t *)psProcess)->pMarkAttachClassDefTable, LE_GET_GLYPH_ID(paGlyphId[u16CurrentOffset1]));
                    }
                    //s32GlyphClass = msAPI_MLE_LeGetGlyphClass(psClassDefinitionTable, LE_GET_GLYPH_ID(paGlyphId[u16CurrentOffset]));

                    //MarkAttachmentType: 0xFF00
                    if (((eLookupFlags & 0xFF00) >> 8) == s32MarkAttachmentClass)
                    {
                        u16CurrentOffset = u16CurrentOffset1;
                        break;
                    }
                    else
                    {
                        u16CurrentOffset1++;
                        if (u16CurrentOffset1 >= u16GlyphLen)
                        {
                            break;
                        }
                    }
                }
            }           
        }

        s32GlyphClass = msAPI_MLE_LeGetGlyphClass(psClassDefinitionTable, LE_GET_GLYPH_ID(paGlyphId[u16CurrentOffset]));
        
        s32ClassOffset = (S32)pauClass + (s32CurrentMatched * sizeof(U16));
        s32MatchedClass = LE_GET_SHORT(s32ClassOffset);

		//if glyph is not define in class definition table, use the default value 0
        if ( s32GlyphClass < 0 )
        {
            s32GlyphClass = 0;
        }

        if ( s32GlyphClass != s32MatchedClass )
        {
            bResult = FALSE;
            break;
        }

        u16CompareCount--;
        u16CurrentOffset = u16CurrentOffset + s32Direction;
        s32CurrentMatched = s32CurrentMatched + s32Direction;
    }

    return bResult;
}

static U16 _msAPI_MLE_LeContextFormat2TableGetLookupRecord( const U8* psContext, void *psProcess, const U32 *paGlyphId, U16 u16GlyphLen, U16 u16Position, const U8 **ppasRecords, LE_LookupFlag_e eLookupFlags, BOOLEAN bGSUB )
{
    const U8 *psFormat2 = psContext;
    const U8 *pConverage = NULL;
    U16 u16GlyphId = (U16)(-1);
    S32 s32CoverageIndex = -1;
    U16 u16RecordCount = 0;

    if ( psContext == NULL || paGlyphId == NULL || u16GlyphLen == 0 || ppasRecords == NULL )
    {
        return 0;
    }

    if ( u16Position >= u16GlyphLen )
    {
        return 0;
    }

    u16GlyphId = LE_GET_GLYPH_ID(paGlyphId[u16Position]);

    psFormat2 = psFormat2 + sizeof(U16);
    pConverage = psContext + LE_GET_OFFSET(psFormat2);
    s32CoverageIndex = msAPI_MLE_LeGetGlyphCoverage(pConverage, u16GlyphId);

    psFormat2 = psFormat2 + sizeof(LE_Offset);
    if ( s32CoverageIndex >= 0 ) 
    {
        const U8 *pClassDefinitionTable = psContext + LE_GET_OFFSET(psFormat2);
        S32 s32SubstSetClass = msAPI_MLE_LeGetGlyphClass(pClassDefinitionTable, u16GlyphId);
        U16 u16SubstClassSetCount;
        S32 s32ClassSetTableOffset;

        //if glyph is not define in class definition table and use the default value 0
        if ( s32SubstSetClass < 0 )
        {
            s32SubstSetClass = 0;
        }

        psFormat2 = psFormat2 + sizeof(LE_Offset);
        u16SubstClassSetCount = LE_GET_SHORT(psFormat2);

        psFormat2 = psFormat2 + sizeof(U16);

        s32ClassSetTableOffset = (S32)psFormat2 + (s32SubstSetClass * sizeof(LE_Offset));
        if ( s32SubstSetClass < u16SubstClassSetCount && s32ClassSetTableOffset != 0 ) 
        {
            const U8 *pSubstClassSetTable = psContext + LE_GET_OFFSET(s32ClassSetTableOffset);
            U16 u16SubstClassRuleCount = LE_GET_SHORT(pSubstClassSetTable);
            U16 i;

            for ( i = 0; i < u16SubstClassRuleCount; i++ )
            {
                S32 s32SubstClassRuleTableOffset = (S32)pSubstClassSetTable + sizeof(U16) + (i * sizeof(LE_Offset));
                const U8 *pSubstClassRuleTable = pSubstClassSetTable + LE_GET_OFFSET(s32SubstClassRuleTableOffset);
                U16 u16GlyphCount = LE_GET_SHORT(pSubstClassRuleTable) - 1;

                pSubstClassRuleTable = pSubstClassRuleTable + sizeof(U16);
                if ( _msAPI_MLE_LeMatchGlyphClass(pClassDefinitionTable, psProcess, paGlyphId, u16GlyphLen, u16Position, (pSubstClassRuleTable + sizeof(U16)), u16GlyphCount, eLookupFlags, FALSE, FALSE, bGSUB ) ) 
                {
                    u16RecordCount = LE_GET_SHORT(pSubstClassRuleTable);
                    *ppasRecords = pSubstClassRuleTable + sizeof(U16) + (u16GlyphCount * sizeof(U16));
                    break;
                }
            }
        }
    }
    
    return u16RecordCount;
}

static BOOLEAN _msAPI_MLE_LeMatchGlyphCoverage( const U8* psContext, const U32 *paGlyphId, U16 u16GlyphLen, U16 u16Position, const U8 *pasCoverageOffset, U16 u16CoverageCount, BOOLEAN bBackTrack )
{
    S32 s32Direction = 1;
    S32 s32CurrentMatched = 0;
    S32 s32CurrentOffset;
    U16 u16CompareCount = u16CoverageCount;
    BOOLEAN bResult = TRUE;

    if ( psContext == NULL || paGlyphId == NULL || pasCoverageOffset == NULL || u16GlyphLen == 0 || u16CoverageCount == 0 )
    {
        return FALSE;
    }

    if ( bBackTrack ) 
    {
        if ( u16Position < u16CoverageCount )
        {
            return FALSE;
        }
    
//Fix GSUB bug
        //s32CurrentMatched = u16CoverageCount - 1;
        s32Direction = -1;
    }
    else
    {
        if ( u16Position + u16CoverageCount >= u16GlyphLen )
        {
            return FALSE;
        }
    }

    s32CurrentOffset = u16Position + s32Direction;


    while ( u16CompareCount > 0 ) 
    {   
        S32 s32CoverageTableOffset = (S32)pasCoverageOffset + (s32CurrentMatched * sizeof(LE_Offset));
        const U8 *pCoverageTable = psContext + LE_GET_OFFSET(s32CoverageTableOffset);

        if ( msAPI_MLE_LeGetGlyphCoverage(pCoverageTable, LE_GET_GLYPH_ID(paGlyphId[s32CurrentOffset])) < 0 )
        {
            bResult = FALSE;
            break;
        }

        u16CompareCount--;
        s32CurrentOffset = s32CurrentOffset + s32Direction;
//Fix GSUB bug, wait verify
        if ( bBackTrack )
        {
            s32CurrentMatched = s32CurrentMatched - s32Direction;
        }
        else
        {
        s32CurrentMatched = s32CurrentMatched + s32Direction;
        }
    }

    return bResult;
}

static U16 _msAPI_MLE_LeContextFormat3TableGetLookupRecord( const U8* psContext, const U32 *strGlyphId, U16 u16GlyphLen, U16 u16Position, const U8 **ppasRecords )
{
    const U8 *psFormat3 = psContext;
    U16 u16GlyphCount = 0;
    U16 u16RecordCount = 0;

    if ( psFormat3 == NULL || strGlyphId == NULL || u16GlyphLen == 0 || ppasRecords == NULL )
    {
        return FALSE;
    }

    if ( u16Position >= u16GlyphLen )
    {
        return FALSE;
    }
    
    u16GlyphCount = LE_GET_SHORT(psFormat3);

    psFormat3 = psFormat3 + sizeof(U16);
    if ( _msAPI_MLE_LeMatchGlyphCoverage(psContext, strGlyphId, u16GlyphLen, u16Position, (psFormat3 + sizeof(U16)), u16GlyphCount, FALSE) ) 
    {
        u16RecordCount = LE_GET_SHORT(psFormat3);

        *ppasRecords = psFormat3 + sizeof(U16) + (u16GlyphCount * sizeof(U16));
    }

    return u16RecordCount;
}

U16 msAPI_MLE_LeContextTableGetLookupRecord( const U8 *psContext, void *psProcess, const U32 *paGlyphId, U16 u16GlyphLen, U16 u16Position, const U8 **ppasRecords, LE_LookupFlag_e eLookupFlags, BOOLEAN bGSUB )
{
    U16 u16RecordCount = 0;

    if ( paGlyphId == NULL || psContext == NULL || ppasRecords == NULL )
    {
        return 0;
    }

    switch( LE_GET_SHORT(psContext) )
    {
        case LE_CONTEXT_FORMAT_1:
        {
            u16RecordCount = _msAPI_MLE_LeContextFormat1TableGetLookupRecord(psContext, paGlyphId, u16GlyphLen, u16Position, ppasRecords);
            break;
        }

        case LE_CONTEXT_FORMAT_2:
        {       
            u16RecordCount = _msAPI_MLE_LeContextFormat2TableGetLookupRecord(psContext, psProcess, paGlyphId, u16GlyphLen, u16Position, ppasRecords, eLookupFlags, bGSUB);
            break;
        }

        case LE_CONTEXT_FORMAT_3:
        {
            u16RecordCount = _msAPI_MLE_LeContextFormat3TableGetLookupRecord(psContext, paGlyphId, u16GlyphLen, u16Position, ppasRecords);
            break;
        }

        case LE_CONTEXT_FORMAT_INVALID:
        default:
            break;
    }

    return u16RecordCount;
}

static U16 _msAPI_MLE_LeChainingContextFormat1TableGetLookupRecord( const U8 *psChainingContext, const U32 *paGlyphId, U16 u16GlyphLen, U16 u16Position, const U8 **ppasRecords )
{
    const U8 *psFormat1 = psChainingContext;
    const U8 *pConverage = NULL;
    U16 u16GlyphId = (U16)(-1);
    S32 s32CoverageIndex = -1;
    U16 u16RecordCount = 0;

    if ( psFormat1 == NULL || paGlyphId == NULL || ppasRecords == NULL || u16GlyphLen == 0 )
    {
        return 0;
    }

    if ( u16Position >= u16GlyphLen )
    {
        return 0;
    }
    
    u16GlyphId = LE_GET_GLYPH_ID(paGlyphId[u16Position]);

    psFormat1 = psFormat1 + sizeof(U16);
    pConverage = psChainingContext + LE_GET_OFFSET(psFormat1);
    s32CoverageIndex = msAPI_MLE_LeGetGlyphCoverage(pConverage, u16GlyphId);

    psFormat1 = psFormat1 + sizeof(LE_Offset);
    if ( s32CoverageIndex >= 0 ) 
    {
        U16 u16ChainSubRuleSetCount = LE_GET_SHORT(psFormat1);

        if ( s32CoverageIndex < u16ChainSubRuleSetCount )
        {   
            S32 s32ChainRuleSetTableOffset = (S32)psChainingContext + sizeof(U16) + (s32CoverageIndex * sizeof(LE_Offset));
            const U8 *pChainSubstRuleSetTable = psChainingContext + LE_GET_OFFSET(s32ChainRuleSetTableOffset);
            U16 u16ChainSubstRuleCount = LE_GET_SHORT(pChainSubstRuleSetTable);
            U16 i;

            for ( i = 0; i < u16ChainSubstRuleCount; i++ ) 
            {
                S32 s32ChainRuleTableOffset = (S32)pChainSubstRuleSetTable + sizeof(U16) + (i * sizeof(LE_Offset));
                const U8 *pChainSubstRuleTable = pChainSubstRuleSetTable + LE_GET_OFFSET(s32ChainRuleTableOffset);
                U16 u16BacktrackGlyphCount = LE_GET_SHORT(pChainSubstRuleTable) - 1;
                S32 s32BacktrackGlyphOffset = (S32)pChainSubstRuleTable + sizeof(U16) + (u16BacktrackGlyphCount * sizeof(U16));
                U16 u16InputGlyphCount = LE_GET_SHORT(s32BacktrackGlyphOffset) - 1;
                const U8 *pInputGlyphArray = (const U8 *)(s32BacktrackGlyphOffset + sizeof(U16));
                S32 s32InputOffset = (S32)pInputGlyphArray + (u16InputGlyphCount * sizeof(U16));
                U16 u16LookaheadGlyphCount = LE_GET_SHORT(s32InputOffset);
                const U8 *pLookaheadGlyphArray = pInputGlyphArray + ((u16InputGlyphCount + 1) * sizeof(U16));
                S32 s32LookupRecordOffset;

                if ( u16BacktrackGlyphCount == 0 )
                {
                    continue;
                }

                if ( !_msAPI_MLE_LeMatchGlyphId(paGlyphId, u16GlyphLen, u16Position, (pChainSubstRuleTable + sizeof(U16)), u16BacktrackGlyphCount, TRUE) )
                {
                    continue;
                }

                if ( u16LookaheadGlyphCount > 0 )
                {
                    if ( !_msAPI_MLE_LeMatchGlyphId(paGlyphId, u16GlyphLen, u16Position, pLookaheadGlyphArray, u16LookaheadGlyphCount, FALSE) )
                    {
                        continue;
                    }
                }

                if ( u16InputGlyphCount > 0 )
                {
                    if ( !_msAPI_MLE_LeMatchGlyphId(paGlyphId, u16GlyphLen, u16Position, pInputGlyphArray, u16InputGlyphCount, FALSE) )
                    {
                        continue;
                    }
                }
                
                s32LookupRecordOffset = (S32)pLookaheadGlyphArray + (u16LookaheadGlyphCount * sizeof(U16));
                    
                u16RecordCount = LE_GET_SHORT(s32LookupRecordOffset);
                *ppasRecords = (const U8 *)(s32LookupRecordOffset + sizeof(U16));
                break;
            }
        }
    }
    
    return u16RecordCount;
}

static U16 _msAPI_MLE_LeChainingContextFormat2TableGetLookupRecord( const U8 *psChainingContext, void *psProcess, const U32 *paGlyphId, U16 u16GlyphLen, U16 u16Position, const U8 **ppasRecords, LE_LookupFlag_e eLookupFlags, BOOLEAN bGSUB )
{
    const U8 *psFormat2 = psChainingContext;
    const U8 *pConverage = NULL;
    U16 u16GlyphId = (U16)(-1);
    S32 s32CoverageIndex = -1;
    U16 u16RecordCount = 0;

    if ( psFormat2 == NULL || paGlyphId == NULL || ppasRecords == NULL || u16GlyphLen == 0 )
    {
        return 0;
    }

    if ( u16Position >= u16GlyphLen )
    {
        return 0;
    }

    u16GlyphId = LE_GET_GLYPH_ID(paGlyphId[u16Position]);
    psFormat2 = psFormat2 + sizeof(U16);
    pConverage = psChainingContext + LE_GET_OFFSET(psFormat2);
    s32CoverageIndex = msAPI_MLE_LeGetGlyphCoverage(pConverage, u16GlyphId);

    psFormat2 = psFormat2 + sizeof(LE_Offset);
    if ( s32CoverageIndex >= 0 ) 
    {
        const U8 *pBacktrackClassDefinitionTable = psChainingContext + LE_GET_OFFSET(psFormat2);
        const U8 *pInputClassDefinitionTable;
        const U8 *pLookaheadClassDefinitionTable;
        U16 u16ChainSubstClassSetCount;
        S32 s32ChainSubstSetClass;
        S32 s32ChainClassSetTableOffset;

        psFormat2 = psFormat2 + sizeof(LE_Offset);
        pInputClassDefinitionTable = psChainingContext + LE_GET_OFFSET(psFormat2);

        s32ChainSubstSetClass = msAPI_MLE_LeGetGlyphClass(pInputClassDefinitionTable, u16GlyphId);

        //if glyph is not define in class definition table and use the default value 0
        if ( s32ChainSubstSetClass < 0 )
        {
            s32ChainSubstSetClass = 0;
        }

        psFormat2 = psFormat2 + sizeof(LE_Offset);
        pLookaheadClassDefinitionTable = psChainingContext + LE_GET_OFFSET(psFormat2);

        psFormat2 = psFormat2 + sizeof(LE_Offset);
        u16ChainSubstClassSetCount = LE_GET_SHORT(psFormat2);

        psFormat2 = psFormat2 + sizeof(U16);
        s32ChainClassSetTableOffset = (S32)psFormat2 + (s32ChainSubstSetClass * sizeof(LE_Offset));
        if ( s32ChainSubstSetClass < u16ChainSubstClassSetCount && s32ChainClassSetTableOffset != 0 ) 
        {
            const U8 *pChainSubstClassSetTable = psChainingContext + LE_GET_OFFSET(s32ChainClassSetTableOffset);
            U16 u16ChainSubstClassRuleCount = LE_GET_SHORT(pChainSubstClassSetTable);
            U16 i;

            for ( i = 0; i < u16ChainSubstClassRuleCount; i++ )
            {
                S32 s32ChainClassRuleTableOffset = (S32)pChainSubstClassSetTable + sizeof(U16) + (i * sizeof(LE_Offset));
                const U8 *pChainSubstClassRuleTable = pChainSubstClassSetTable + LE_GET_OFFSET(s32ChainClassRuleTableOffset);               
                U16 u16BacktrackGlyphCount = LE_GET_SHORT(pChainSubstClassRuleTable);
                S32 s32BacktrackClassOffset = (S32)pChainSubstClassRuleTable + sizeof(U16) + (u16BacktrackGlyphCount * sizeof(U16));
                U16 u16InputGlyphCount = LE_GET_SHORT(s32BacktrackClassOffset) - 1; //start with second glyph
                const U8 *pInputClassArray = (const U8 *)(s32BacktrackClassOffset + sizeof(U16));
                S32 s32LookaheadGlyphOffset = (S32)pInputClassArray + (u16InputGlyphCount * sizeof(U16));
                U16 u16LookaheadGlyphCount = LE_GET_SHORT(s32LookaheadGlyphOffset);
                const U8 *pLookaheadClassArray = (const U8 *)(s32LookaheadGlyphOffset + sizeof(U16));
                S32 s32LookupRecordOffset;

                if ( u16BacktrackGlyphCount > 0 )
                {
                    if ( !_msAPI_MLE_LeMatchGlyphClass(pBacktrackClassDefinitionTable, psProcess, paGlyphId, u16GlyphLen, u16Position, (pChainSubstClassRuleTable + sizeof(U16)), u16BacktrackGlyphCount, eLookupFlags, TRUE, FALSE, bGSUB) )
                    {
                        continue;
                    }
                }

                if ( u16LookaheadGlyphCount > 0 )
                {
                    if ( !_msAPI_MLE_LeMatchGlyphClass(pLookaheadClassDefinitionTable, psProcess, paGlyphId, u16GlyphLen, u16Position, pLookaheadClassArray, u16LookaheadGlyphCount, eLookupFlags, FALSE, TRUE, bGSUB) )
                    {
                        continue;
                    }
                }

                if ( u16InputGlyphCount > 0 )
                {
                    if ( !_msAPI_MLE_LeMatchGlyphClass(pInputClassDefinitionTable, psProcess, paGlyphId, u16GlyphLen, u16Position, pInputClassArray, u16InputGlyphCount, eLookupFlags, FALSE, FALSE, bGSUB) ) 
                    {
                        continue;
                    }
                }
                s32LookupRecordOffset = (S32)pLookaheadClassArray + (u16LookaheadGlyphCount * sizeof(U16));
                
                u16RecordCount =  LE_GET_SHORT(s32LookupRecordOffset);
                *ppasRecords = (const U8*)(s32LookupRecordOffset + sizeof(U16));
                break;
            }
        }
    }
    
    return u16RecordCount;
}

static U16 _msAPI_MLE_LeChainingContextFormat3TableGetLookupRecord( const U8 *psChainingContext, const U32 *paGlyphId, U16 u16GlyphLen, U16 u16Position, const U8 **ppasRecords )
{
    const U8 *psFormat3 = psChainingContext;
    U16 u16BacktrackGlyphCount;
    U16 u16InputGlyphCount;
    S32 s32InputCoverageTableOffset;
    const U8 *pInputCoverageTableOffsetArray = NULL;
    S32 s32LookaheadCoverageTableOffset;
    U16 u16LookaheadGlyphCount;
    const U8 *pLookaheadCoverageTableOffsetArray = NULL;
    U16 u16RecordCount = 0;

    if ( psFormat3 == NULL || paGlyphId == NULL || ppasRecords == NULL || u16GlyphLen == 0 )
    {
        return 0;
    }

    if ( u16Position >= u16GlyphLen )
    {
        return 0;
    }

    //strange bug
    //psFormat3 = psFormat3 + sizeof(U16) + sizeof(LE_Offset);
    psFormat3 = psFormat3 + sizeof(U16);

    u16BacktrackGlyphCount = LE_GET_SHORT(psFormat3);

    s32InputCoverageTableOffset = (S32)psFormat3 + sizeof(U16) + (u16BacktrackGlyphCount * sizeof(LE_Offset));
    u16InputGlyphCount = LE_GET_SHORT(s32InputCoverageTableOffset);
    pInputCoverageTableOffsetArray = (const U8 *)(s32InputCoverageTableOffset + sizeof(U16));
    s32LookaheadCoverageTableOffset = (S32)pInputCoverageTableOffsetArray + (u16InputGlyphCount * sizeof(LE_Offset));
    u16LookaheadGlyphCount = LE_GET_SHORT(s32LookaheadCoverageTableOffset);
    pLookaheadCoverageTableOffsetArray = (const U8 *)(s32LookaheadCoverageTableOffset + sizeof(U16));

    do
    {
        S32 s32LookupRecordOffset;

        //Don't check this, some TTF files this count is zero!
        //if ( u16BacktrackGlyphCount == 0 )
        //{
            //break;
        //}
            
        //if ( !_msAPI_MLE_LeMatchGlyphCoverage(psChainingContext, paGlyphId, u16GlyphLen, u16Position, (psFormat3 + sizeof(U16)), u16BacktrackGlyphCount, TRUE) )
        //{
            //break;
        //}
		
        if ( u16BacktrackGlyphCount > 0 )
        {   
            if ( !_msAPI_MLE_LeMatchGlyphCoverage(psChainingContext, paGlyphId, u16GlyphLen, u16Position, (psFormat3 + sizeof(U16)), u16BacktrackGlyphCount, TRUE) )
            {
                break;
            }
        }

        if ( u16LookaheadGlyphCount > 0 )
        {
            if ( !_msAPI_MLE_LeMatchGlyphCoverage(psChainingContext, paGlyphId, u16GlyphLen, u16Position, pLookaheadCoverageTableOffsetArray, u16LookaheadGlyphCount, FALSE) )
            {
                break;
            }
        }

        if ( u16InputGlyphCount > 0 )
        {
            if ( _msAPI_MLE_LeMatchGlyphCoverage(psChainingContext, paGlyphId, u16GlyphLen, u16Position,pInputCoverageTableOffsetArray, u16InputGlyphCount, FALSE) ) 
            {
                s32LookupRecordOffset = (S32)pLookaheadCoverageTableOffsetArray + (u16LookaheadGlyphCount * sizeof(U16));
                    
                u16RecordCount = LE_GET_SHORT(s32LookupRecordOffset);
                *ppasRecords = (const U8 *)(s32LookupRecordOffset + sizeof(U16));
                break;
            }
        }
    
        s32LookupRecordOffset = (S32)pLookaheadCoverageTableOffsetArray + (u16LookaheadGlyphCount * sizeof(U16));
                    
        u16RecordCount = LE_GET_SHORT(s32LookupRecordOffset);
        *ppasRecords = (const U8 *)(s32LookupRecordOffset + sizeof(U16));
    }while(FALSE);

    return u16RecordCount;
}

U16 msAPI_MLE_LeChainingContextTableGetLookupRecord( const U8 *psChainingContext, void *psProcess, const U32 *paGlyphId, U16 u16GlyphLen, U16 u16Position, const U8 **ppasRecords, LE_LookupFlag_e eLookupFlags, BOOLEAN bGSUB )
{
    U16 u16RecordCount = 0;

    if ( psChainingContext == NULL || paGlyphId == NULL || ppasRecords == NULL || u16GlyphLen == 0 )
    {
        return 0;
    }

    switch( LE_GET_SHORT(psChainingContext) )
    {
        case LE_CHAININGCONTEXT_FORMAT_1:
        {           
            u16RecordCount = _msAPI_MLE_LeChainingContextFormat1TableGetLookupRecord(psChainingContext, paGlyphId, u16GlyphLen, u16Position, ppasRecords);
            break;
        }

        case LE_CHAININGCONTEXT_FORMAT_2:
        {       
            u16RecordCount = _msAPI_MLE_LeChainingContextFormat2TableGetLookupRecord(psChainingContext, psProcess, paGlyphId, u16GlyphLen, u16Position, ppasRecords, eLookupFlags, bGSUB);
            break;
        }

        case LE_CHAININGCONTEXT_FORMAT_3:
        {
            u16RecordCount = _msAPI_MLE_LeChainingContextFormat3TableGetLookupRecord(psChainingContext, paGlyphId, u16GlyphLen, u16Position, ppasRecords);
            break;
        }

        case LE_CHAININGCONTEXT_FORMAT_INVALID:
        default:
            break;
    }

    return u16RecordCount;
}

const U8* msAPI_MLE_LeGetFeatureTable( const U16 u16FeatureCount, const U16 *pu16FeatureIndices, const U8 *pFeatureList, LE_FeatureTag_e u32FeatureTag, U16 *pu16LookupCount )
{
    const U8 *pTempFeatureList = pFeatureList;
    U16 u16FeatureNum;
    const U8 *pFeatureTable = NULL;

    if ( pFeatureList == NULL )
    {
        return NULL;
    }

    pTempFeatureList = pTempFeatureList + sizeof(U16);
    for(u16FeatureNum=0;u16FeatureNum<u16FeatureCount;u16FeatureNum++)
    {
        S32 s32FeatureRecordOffset = (S32)pTempFeatureList + (pu16FeatureIndices[u16FeatureNum] * LE_FeatureRecord_Size);
        if ( LE_GET_TAG(s32FeatureRecordOffset) == u32FeatureTag ) 
        {
            s32FeatureRecordOffset = s32FeatureRecordOffset + sizeof(LE_Tag);
            pFeatureTable = pFeatureList + LE_GET_OFFSET(s32FeatureRecordOffset);

            if ( pu16LookupCount )
            {
                S32 s32LookupCountOffset = (S32)pFeatureTable + sizeof(LE_Offset);
                
                *pu16LookupCount = LE_GET_OFFSET(s32LookupCountOffset);
            }
            break;
        }
    }

    return pFeatureTable;
}

BOOLEAN msAPI_MLE_LeFeatureTableGetLookupIndexs( const U8 *pFeature, U16 *pau16Index, U16 u16ArraySize )
{
    const U8 *pTempFeature = pFeature;
    U16 u16LookupCount = 0;
    U16 i;

    if ( pFeature == NULL || pau16Index == NULL || u16ArraySize == 0 )
    {
        return FALSE;
    }

    pTempFeature = pTempFeature + sizeof(LE_Offset);
    u16LookupCount = LE_GET_SHORT(pTempFeature);

    if ( u16ArraySize < u16LookupCount )
    {
        return FALSE;
    }

    pTempFeature = pTempFeature + sizeof(U16);
    for ( i = 0; i < u16LookupCount; i++ )
    {
        S32 s32LookupListOffset = (S32)pTempFeature + (i * sizeof(U16));
        
        pau16Index[i] = LE_GET_SHORT(s32LookupListOffset);
    }

    return TRUE;
}

const U8* msAPI_MLE_LeLookupListTableGetLookupTable( const U8 *pLookupList, U16 u16Index, U16 *pu16SubtableCount )
{
    const U8 *pTempLookupList = pLookupList;
    S32 s32LookupTableOffset;
    const U8 *pLookupTable = NULL;
    U16 u16LookupCount = 0;

    if ( pLookupList == NULL )
    {
        return NULL;
    }

    u16LookupCount = LE_GET_SHORT(pTempLookupList);

    if ( u16Index >= u16LookupCount )
    {
        return NULL;
    }

    s32LookupTableOffset = (S32)pTempLookupList + sizeof(U16) + (u16Index * sizeof(LE_Offset));
    pLookupTable = pLookupList + LE_GET_OFFSET(s32LookupTableOffset);
    if ( pu16SubtableCount )
    {
        S32 s32SubtableCountOffset = (S32)pLookupTable + sizeof(U16) + sizeof(U16);
        *pu16SubtableCount = LE_GET_SHORT(s32SubtableCountOffset);
    }

    return pLookupTable;
}

const U8* msAPI_MLE_LeLookupTableGetLookupSubtable( const U8 *pLookup, U16 u16Index )
{
    const U8 *pTempLookup = pLookup;
    S32 s32SubtableOffset;
    const U8 *pLookupSubtable = NULL;
    U16 u16LookupSubtableCount = 0;

    if ( pLookup == NULL )
    {
        return NULL;
    }

    pTempLookup = pTempLookup + sizeof(U16) + sizeof(U16);
    u16LookupSubtableCount = LE_GET_SHORT(pTempLookup);

    if ( u16Index >= u16LookupSubtableCount )
    {
        return NULL;
    }

    s32SubtableOffset = (S32)pTempLookup + sizeof(U16) + (u16Index * sizeof(LE_Offset));
    pLookupSubtable = pLookup + LE_GET_OFFSET(s32SubtableOffset);

    return pLookupSubtable;
}

static S32 _msAPI_MLE_LeSearchScriptName(LE_ScriptTag_e eScriptTag, U16 u16SearchCount, S32 s32ScriptListAddr)
{
    S32 s32ScriptTableOffset = 0;
    U16 i;
    
    for( i = 0; i < u16SearchCount; i++ )
    {
        S32 s32ScriptRecordOffset = s32ScriptListAddr + (i * LE_ScriptRecord_Size);
        if ( LE_GET_TAG(s32ScriptRecordOffset) == eScriptTag )
        {
            s32ScriptRecordOffset = s32ScriptRecordOffset + sizeof(LE_Tag);
            s32ScriptTableOffset = LE_GET_SHORT(s32ScriptRecordOffset);
            break;
        }
    }
    
    return s32ScriptTableOffset;
}

const U8* msAPI_MLE_LeFindScript( const U8 *pu8ScriptList, LE_ScriptTag_e eScriptTag, LE_ScriptTag_e eScriptTagV2 )
{
    const U8 *pu8TempScriptList = pu8ScriptList;
    const U8 *pu8Script = NULL; 
    U16 u16ScriptCount;
    const U8 *pFirstScriptRecord;
    S32 s32FirstScriptRecordOffset;
    U16 u16Limit;
    S32 s32ScriptTableOffset = 0;
    U16 u16TempNum;

    if ( pu8ScriptList == NULL || eScriptTag == LE_SCRIPT_TAG_NULL )
    {
        return NULL;
    }

    u16ScriptCount = LE_GET_SHORT(pu8TempScriptList);
    pu8TempScriptList = pu8TempScriptList + sizeof(U16);

    pFirstScriptRecord = pu8TempScriptList + sizeof(LE_Tag);
    s32FirstScriptRecordOffset = LE_GET_SHORT(pFirstScriptRecord);
    u16Limit = ((s32FirstScriptRecordOffset - sizeof(U16))/LE_ScriptRecord_Size);

    u16TempNum = MIN(u16Limit, u16ScriptCount);
    if ( 0 ) //if ( eScriptTagV2 != LE_SCRIPT_TAG_NULL ) //Don't use v2 now
    {
        s32ScriptTableOffset = _msAPI_MLE_LeSearchScriptName(eScriptTagV2, u16TempNum, (S32)pu8TempScriptList);
        if ( s32ScriptTableOffset == 0 )
        {
            //V2 name not found, search V1 name instead
            s32ScriptTableOffset = _msAPI_MLE_LeSearchScriptName(eScriptTag, u16TempNum, (S32)pu8TempScriptList);
        }
    }
    else
    {
        //V2 name not exist, direct search V1 name
        s32ScriptTableOffset = _msAPI_MLE_LeSearchScriptName(eScriptTag, u16TempNum, (S32)pu8TempScriptList);
    }

    if ( s32ScriptTableOffset != 0 )
    {
        pu8Script = ((U8 *)pu8ScriptList + s32ScriptTableOffset);
    }

    return pu8Script;
}

BOOLEAN msAPI_MLE_LeFindLangSysTable( const U8 *pu8ScriptTable, LE_LanguageTag_e eLang, U16 *pu16FeatureCount, U16 *pu16FeatureIndices)
{
    const U8 *pu8TempScriptTable = pu8ScriptTable;
    U16 u16LangSysCount, u16DefLangSys, u16FeatureCount;
    const U8 *pu8LangSysTable;
    U16 u16TempNum;
    U16 i;

    if ( pu8ScriptTable == NULL )
    {
        return FALSE;
    }

    u16DefLangSys = LE_GET_SHORT(pu8TempScriptTable);
    pu8TempScriptTable += sizeof(LE_Offset);
    
    u16LangSysCount = LE_GET_SHORT(pu8TempScriptTable);
    pu8TempScriptTable = pu8TempScriptTable + sizeof(U16);

    if ( ( u16LangSysCount > 0 ) && ( eLang != LE_LANGUAGE_TAG_NULL ) )
    {
        //Not only default language, but now we have other languages
        for(i=0;i<u16LangSysCount;i++)
        {
            if ( LE_GET_TAG(pu8TempScriptTable) == eLang )
            {
                break;
            }
            pu8TempScriptTable += (sizeof(LE_Tag) + sizeof(LE_Offset));
        }
        
        if ( i == u16LangSysCount )
        {
            //eLang Not Found, use default language instead     
        }
        else
        {
            u16DefLangSys = LE_GET_SHORT(pu8TempScriptTable + sizeof(LE_Tag));
        }
    }
    
    pu8LangSysTable = pu8ScriptTable + u16DefLangSys;
    
    pu8LangSysTable += ( sizeof(U16) + sizeof(U16) );   //skip Lookup Order and ReqFeatureIndex
    
    u16FeatureCount = LE_GET_SHORT(pu8LangSysTable);
    pu8LangSysTable += sizeof(U16);     //skip Feature Count
    
    u16TempNum = MIN(HINDI_MAX_FEATURE_NUM, u16FeatureCount);
    
    *pu16FeatureCount = u16TempNum;
    for(i=0;i<u16TempNum;i++)
    {
        pu16FeatureIndices[i] = LE_GET_SHORT(pu8LangSysTable);
        pu8LangSysTable += sizeof(U16);
    }
    
    return TRUE;
}

U16 msAPI_MLE_LeGlyphStrGetNext( const U32 *paGlyphId, U16 u16GlyphLen, U16 u16Position, U16 u16NextCount, U16 *pu16NextPosition, const U8 *pDefTable, LE_LookupFlag_e eLookupFlags, BOOLEAN bIgnoreFFFE )
{
    U16 u16Result = (U16)-1;
    S16 s16Direction = 1;

    if ( paGlyphId == NULL || u16GlyphLen == 0 )
    {
        return (U16)-1;
    }

    if ( eLookupFlags & LE_LOOKUP_FLAG_RIGHTTOLEFT )
    {
        s16Direction = -1;
    }

    if ( (S16)(u16Position + (u16NextCount * s16Direction)) >= u16GlyphLen || (S16)(u16Position + (u16NextCount * s16Direction)) < 0 )
    {
        return (U16)-1;
    }

    if ( pDefTable == NULL || eLookupFlags == 0 || u16NextCount == 0 )
    {
        u16Result = LE_GET_GLYPH_ID(paGlyphId[u16Position + (s16Direction * u16NextCount)]);
        if ( pu16NextPosition )
        {
            *pu16NextPosition = u16Position + (s16Direction * u16NextCount);
        }
    }
    else
    {
        S32 s32GlyphClass = LE_CLASS_DEF_NO;
        U16 u16GlyphId = (U16)(-1);
        U16 u16CurrentOffset = u16Position;

        while ( u16NextCount > 0 ) 
        {               
            BOOLEAN bMatched = TRUE;
            
            if ( ((S16)(u16CurrentOffset) >= u16GlyphLen) || (S16)(u16CurrentOffset) < 0 )
            {
                bMatched = FALSE;
                break;
            }

            u16CurrentOffset = u16CurrentOffset + s16Direction;
            u16GlyphId = LE_GET_GLYPH_ID(paGlyphId[u16CurrentOffset]);

            if ( u16GlyphId == 0xFFFE ) 
            {
                if ( bIgnoreFFFE )
                {
                    continue;
                }
                else
                {
                    break;
                }
            }
            else if ( u16GlyphId > 0xFFFE )
            {
                break;
            }
            
            s32GlyphClass = msAPI_MLE_LeGetGlyphClass(pDefTable, u16GlyphId);

            //if glyph is not define in class definition table and use the default value 0
            if ( s32GlyphClass < 0 )
            {
                s32GlyphClass = 0;
            }

            switch ( s32GlyphClass ) 
            {
                case LE_CLASS_DEF_SIMPLE:
                case LE_CLASS_DEF_COMPONENT:    
                    if ( eLookupFlags & LE_LOOKUP_FLAG_IGNORE_BASEGLYPHS )
                    {
                        bMatched = FALSE;
                    }
                    break;

                case LE_CLASS_DEF_LIGATURE:
                    if ( eLookupFlags & LE_LOOKUP_FLAG_IGNORE_LIGATURES )
                    {
                        bMatched = FALSE;
                    }
                    break;

                case LE_CLASS_DEF_MARK:
                    if ( eLookupFlags & LE_LOOKUP_FLAG_IGNORE_MARKS )
                    {
                        bMatched = FALSE;
                    }
                    break;

                case LE_CLASS_DEF_NO:
                default:
                    break;
            }
            
            if ( bMatched )
            {
                u16NextCount = u16NextCount - 1;
            }
        }

        if ( u16NextCount == 0 )
        {
            u16Result = u16GlyphId;
            if ( pu16NextPosition )
            {
                *pu16NextPosition = u16CurrentOffset;
            }
        }
    }

    return u16Result;
}

U16 msAPI_MLE_LeGlyphStrGetNextBaseGlyph( const U32 *paGlyphId, U16 u16GlyphLen, U16 u16Position, U16 u16NextCount, U16 *pu16NextPosition, const U8 *pDefTable, LE_LookupFlag_e eLookupFlags, BOOLEAN bIgnoreFFFE )
{
    U16 u16Result = (U16)-1;
    S16 s16Direction = 1;

    if ( paGlyphId == NULL || u16GlyphLen == 0 )
    {
        return (U16)-1;
    }

    if ( eLookupFlags & LE_LOOKUP_FLAG_RIGHTTOLEFT )
    {
        s16Direction = -1;
    }

    if ( (S16)(u16Position + (u16NextCount * s16Direction)) >= u16GlyphLen || (S16)(u16Position + (u16NextCount * s16Direction)) < 0 )
    {
        return (U16)-1;
    }

    if ( pDefTable == NULL || eLookupFlags == 0 || u16NextCount == 0 )
    {
        u16Result = LE_GET_GLYPH_ID(paGlyphId[u16Position + (s16Direction * u16NextCount)]);
        if ( pu16NextPosition )
        {
            *pu16NextPosition = u16Position + (s16Direction * u16NextCount);
        }
    }
    else
    {
        S32 s32GlyphClass = LE_CLASS_DEF_NO;
        U16 u16GlyphId = (U16)(-1);
        U16 u16CurrentOffset = u16Position;

        while ( u16NextCount > 0 ) 
        {               
            BOOLEAN bMatched = TRUE;
            
            if ( ((S16)(u16CurrentOffset) >= u16GlyphLen) || (S16)(u16CurrentOffset) < 0 )
            {
                bMatched = FALSE;
                break;
            }

            u16CurrentOffset = u16CurrentOffset + s16Direction;
            u16GlyphId = LE_GET_GLYPH_ID(paGlyphId[u16CurrentOffset]);

            if ( u16GlyphId == 0xFFFE ) 
            {
                if ( bIgnoreFFFE )
                {
                    continue;
                }
                else
                {
                    break;
                }
            }
            else if ( u16GlyphId > 0xFFFE )
            {
                break;
            }
            
            s32GlyphClass = msAPI_MLE_LeGetGlyphClass(pDefTable, u16GlyphId);

            //if glyph is not define in class definition table and use the default value 0
            if ( s32GlyphClass < 0 )
            {
                s32GlyphClass = 0;
            }

            switch ( s32GlyphClass ) 
            {
                case LE_CLASS_DEF_SIMPLE:
                case LE_CLASS_DEF_COMPONENT:    
                    if ( eLookupFlags & LE_LOOKUP_FLAG_IGNORE_BASEGLYPHS )
                    {
                        bMatched = FALSE;
                    }
                    break;

                case LE_CLASS_DEF_LIGATURE:
                    if ( eLookupFlags & LE_LOOKUP_FLAG_IGNORE_LIGATURES )
                    {
                        bMatched = FALSE;
                    }
                    break;

                case LE_CLASS_DEF_MARK:
                    if ( eLookupFlags & LE_LOOKUP_FLAG_IGNORE_MARKS )
                    {
                        bMatched = FALSE;
                    }
                    break;

                case LE_CLASS_DEF_NO:
                default:
                    break;
            }
            
            if ( bMatched )
            {
                u16NextCount = u16NextCount - 1;
                if ( ( u16NextCount == 0 ) && ( u16CurrentOffset > 0 ) && ( u16CurrentOffset < u16GlyphLen ) )
                {
                    if ( ( s32GlyphClass != LE_CLASS_DEF_SIMPLE ) && ( s32GlyphClass != LE_CLASS_DEF_COMPONENT ) )
                    {
                        u16NextCount = 1;
                    }
                }
            }
        }

        if ( u16NextCount == 0 )
        {
            u16Result = u16GlyphId;
            if ( pu16NextPosition )
            {
                *pu16NextPosition = u16CurrentOffset;
            }
        }
    }

    return u16Result;
}

#endif //__FEATURE_VECTOR_FONT__

#endif //__MSAPI_MLE_LE_OTF_C__
