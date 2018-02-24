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


#ifndef __MSAPI_MLE_LE_UTIL_C__
#define __MSAPI_MLE_LE_UTIL_C__

#ifdef __FEATURE_VECTOR_FONT__
/******************************/
/*        INCLUDE             */
/******************************/
#include "msAPI_MLE_common_def.h"

#include "msAPI_MLE_font_vector.h"

#include "msAPI_MLE_le_types.h"
#include "msAPI_MLE_le_otf_common.h"
#include "msAPI_MLE_le_otf_def.h"
#include "msAPI_MLE_le_util.h"

S32 msAPI_MLE_LeFontXPixelsToUnits( LE_FontInstanceInf_t *pFontInstanceInf, S32 s32XPixel )
{
    return (s32XPixel * pFontInstanceInf->u16UnitsPerEM) / pFontInstanceInf->u16XPixelsPerEM;
}

S32 msAPI_MLE_LeFontYPixelsToUnits( LE_FontInstanceInf_t *pFontInstanceInf, S32 s32YPixel )
{
    return (s32YPixel * pFontInstanceInf->u16UnitsPerEM) / pFontInstanceInf->u16YPixelsPerEM;
}

S32 msAPI_MLE_LeFontXUnitToPoint( LE_FontInstanceInf_t *pFontInstanceInf, S32 s32XUnit )
{
    return ((s32XUnit * pFontInstanceInf->u16XPixelsPerEM) / pFontInstanceInf->u16UnitsPerEM);
}

S32 msAPI_MLE_LeFontYUnitToPoint( LE_FontInstanceInf_t *pFontInstanceInf, S32 s32YUnit )
{
    return ((s32YUnit * pFontInstanceInf->u16YPixelsPerEM) / pFontInstanceInf->u16UnitsPerEM);
}

void msAPI_MLE_LeFontPixelsToUnits( LE_FontInstanceInf_t *pFontInstanceInf, LE_Points_t *pPixel, LE_Points_t *pUnit )
{
    pUnit->s32X = msAPI_MLE_LeFontXPixelsToUnits(pFontInstanceInf, pPixel->s32X);
    pUnit->s32Y = msAPI_MLE_LeFontYPixelsToUnits(pFontInstanceInf, pPixel->s32Y);
}

void msAPI_MLE_LeFontUnitToPoint( LE_FontInstanceInf_t *pFontInstanceInf, LE_Points_t *pUnit, LE_Points_t *pPixel )
{
    pPixel->s32X = msAPI_MLE_LeFontXUnitToPoint(pFontInstanceInf, pUnit->s32X);
    pPixel->s32Y = msAPI_MLE_LeFontYUnitToPoint(pFontInstanceInf, pUnit->s32Y);
}

void msAPI_MLE_LeFontTransformUnit( LE_FontInstanceInf_t *pFontInstanceInf, S32 s32XUnit, S32 s32YUnit, LE_Points_t *pPixel )
{
    pPixel->s32X = msAPI_MLE_LeFontXUnitToPoint(pFontInstanceInf, s32XUnit) * pFontInstanceInf->s32XScaleFactor;
    pPixel->s32Y = msAPI_MLE_LeFontYUnitToPoint(pFontInstanceInf, s32YUnit) * pFontInstanceInf->s32YScaleFactor;
}

#if 0
BOOLEAN msAPI_MLE_LeFontGetGlyphPoint( U16 u16GlyphId, S32 s32PointNumber, LE_Points_t *pPoint )
{
    BOOLEAN bResult = FALSE;
    TTF_Bitmap *pBmp = NULL;

    s32PointNumber = s32PointNumber;
    
    if ( msAPI_MLE_FONTBASE_VectorFontGetTFGlyphInfAllocate(u16GlyphId, &pBmp) == MLE_RET_SUCCESS )
    {
        pPoint->s32X = pBmp->x/64;
        pPoint->s32Y = pBmp->y/64;
        bResult = TRUE;
    }

    msAPI_MLE_FONTBASE_VectorFontTFBitmapFree(pBmp);
    pBmp = NULL;
    
    return bResult;
}
#endif

BOOLEAN msAPI_MLE_LeFontGetGlyphAdvance( U16 u16GlyphId, LE_Points_t *pAdvance )
{
    TTF_Bitmap *pBmp = NULL;

    pAdvance->s32X = 0;
    pAdvance->s32Y = 0;

    if ( msAPI_MLE_FONTBASE_VectorFontGetTFGlyphInfAllocate(u16GlyphId, &pBmp) == MLE_RET_SUCCESS )
    {
        pAdvance->s32X = pBmp->xadvance;
        pAdvance->s32Y = pBmp->yadvance;
    }

    msAPI_MLE_FONTBASE_VectorFontTFBitmapFree(pBmp);
    pBmp = NULL;

    return TRUE;
}

BOOLEAN msAPI_MLE_LeFontIsGlyphRightToLeft( LE_FontInstanceInf_t *pFontInstanceInf, U16 u16GlyphId )
{
    pFontInstanceInf = pFontInstanceInf;
    u16GlyphId = u16GlyphId;
    
    //TBD
    return FALSE;
}

#endif //__FEATURE_VECTOR_FONT__

#endif //__MSAPI_MLE_LE_UTIL_C__
