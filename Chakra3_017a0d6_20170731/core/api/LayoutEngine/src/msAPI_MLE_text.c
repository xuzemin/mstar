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


#define __MLE_TEXT_C__

/******************************/
/*        INCLUDE             */
/******************************/
#include "msAPI_MLE_common_def.h"
#include "msAPI_MLE_text_priv.h"
#include "msAPI_MLE_text_types.h"
#include "msAPI_MLE_text_util.h"
#include "msAPI_MLE_font_vector.h"

/******************************/
/*        DEFINITION          */
/******************************/

static void _msAPI_MLE_TextTableClean( Mle_TextTable_t *pITextTable );
static U32 _msAPI_MLE_TextGetStrLineLength( const MLE_WChar *pString, U32 nStrLen, Text_MeasureInf_t *pMeasureInf );
static BOOLEAN _msAPI_MLE_TextTableGetStrWidth( Mle_TextTable_t *pThis, MLE_WChar *pOrderStr, U32 nStrLen, BOOLEAN bRTL, U32 *pStrWidth, BOOLEAN bSkipSpaceAtLast );

/******************************/
/*         VARIABLES          */
/******************************/

/******************************/
/*     Text Table             */
/******************************/

static MLE_Ret _msAPI_MLE_TextTable_New( void **ppITextTable, Text_MeasureInf_t *pMeasureInf)
{
    Mle_TextTable_t *pThis = NULL;
    MLE_Ret nRet = MLE_RET_SUCCESS;

    if (ppITextTable == 0)
        return MLE_RET_BAD_PARAM;

    do
    {
        TTF_TRACE(printf("%d %s malloc %d bytes\n", __LINE__, __FUNCTION__, sizeof(Mle_TextTable_t) ));
        if ( (pThis = (Mle_TextTable_t *)MALLOC(sizeof(Mle_TextTable_t))) == NULL )
        {
            *ppITextTable = NULL;
            nRet = MLE_RET_OUT_OF_MEMORY;
            msAPI_MLE_SetMemoryNotEnoughFlag(TRUE);
            break;
        }

        pThis->pBidiHandler = NULL;

        if ( pMeasureInf )
        {
            pThis->tMeasureInf.nWidth = pMeasureInf->nWidth;
            pThis->tMeasureInf.bDiffDirChangeLine = pMeasureInf->bDiffDirChangeLine;
            pThis->tMeasureInf.pfnMeasureLine = pMeasureInf->pfnMeasureLine;
            pThis->tMeasureInf.nFunctionData = pMeasureInf->nFunctionData;
            //pThis->tMeasureInf.tFontData.nFontCate = pMeasureInf->tFontData.nFontCate;
            pThis->tMeasureInf.tFontData.nFontSize = pMeasureInf->tFontData.nFontSize;
            pThis->tMeasureInf.tFontData.nFontType = pMeasureInf->tFontData.nFontType;
        }
        else
        {
            pThis->tMeasureInf.nWidth = (U32)(-1);
            pThis->tMeasureInf.bDiffDirChangeLine = FALSE;
            pThis->tMeasureInf.pfnMeasureLine = NULL;
            pThis->tMeasureInf.nFunctionData = 0;
            //pThis->tMeasureInf.tFontData.nFontCate = FONT_CAT_NORMAL;   
            pThis->tMeasureInf.tFontData.nFontSize = 0;   
            pThis->tMeasureInf.tFontData.nFontType = FONT_TYPE_NORMAL;
        }

        *ppITextTable = (void *)pThis;

        return MLE_RET_SUCCESS;
    }while(0);

    return nRet;
}

/*
Release instance of IFontExt
*/
void msAPI_MLE_TextTableRelease( Mle_TextTable_t *pITextTable )
{
    Mle_TextTable_t *pThis = (Mle_TextTable_t *)pITextTable;

    if( NULL == pThis )
        return;

    _msAPI_MLE_TextTableClean( pITextTable );
    FREE(pThis);
    
    return;
}

static void _msAPI_MLE_TextTableClean( Mle_TextTable_t *pITextTable )
{
    Mle_TextTable_t *pThis = (Mle_TextTable_t *)pITextTable;

    if ( pITextTable == NULL )
    {
        return;
    }

    if ( pThis->pBidiHandler )
    {
        msAPI_MLE_TEXTUTIL_BidiFreeHandler( pThis->pBidiHandler );
    }
    pThis->pBidiHandler = NULL;
}

static MLERet_t _msAPI_MLE_TextTableAddLine( Mle_TextTable_t *pITextTable, Text_LineData_t tLineData )
{
    Mle_TextTable_t *pThis = (Mle_TextTable_t *)pITextTable;

    if ( pThis == NULL )
    {
        return MLE_RET_BAD_PARAM;
    }

    if ( pThis->pBidiHandler == NULL )
    {
        pThis->pBidiHandler = msAPI_MLE_TEXTUTIL_BidiCreateHandler();
    }

    if ( msAPI_MLE_TEXTUTIL_BidiAddLine(pThis->pBidiHandler, tLineData.nOffset, tLineData.nLength, tLineData.bRTL) )
    {
        return MLE_RET_SUCCESS;
    }

    return MLE_RET_FAILED;
}

MLERet_t msAPI_MLE_TextTableGetLine( Mle_TextTable_t *pITextTable, U32 nIndex, Text_LineData_t *pLineData )
{
    Mle_TextTable_t *pThis = (Mle_TextTable_t *)pITextTable;

    if ( pLineData )
    {
        MEMSET( (void *)pLineData, 0, sizeof(Text_LineData_t) );
    }

    if ( pThis == NULL || pThis->pBidiHandler == NULL )
    {
        return MLE_RET_BAD_PARAM;
    }

    if ( pLineData )
    {
        if ( msAPI_MLE_TEXTUTIL_BidiGetLineInf(pThis->pBidiHandler,
            nIndex,
            &(pLineData->nOffset),
            &(pLineData->nLength),
            &(pLineData->bRTL),
            NULL,
            NULL,
            NULL) )
        {
            return MLE_RET_SUCCESS;
        }
    }
    else
    {
        if ( msAPI_MLE_TEXTUTIL_BidiGetLineInf(pThis->pBidiHandler,
            nIndex,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL,
            NULL) )
        {
            return MLE_RET_SUCCESS;
        }
    }

    return MLE_RET_FAILED;
}

static MLERet_t _msAPI_MLE_TextTableOrderText( Mle_TextTable_t *pITextTable, const MLE_WChar *pStr, U32 nStrLen, BOOLEAN bIsLangRTL )
{
#ifdef __BIDI_TEXT__
    Mle_TextTable_t *pThis = (Mle_TextTable_t *)pITextTable;

    if ( pThis == NULL || pStr == NULL || nStrLen == 0 )
    {
        return MLE_RET_BAD_PARAM;
    }

    if ( msAPI_MLE_TEXTUTIL_BidiOrderText(pThis->pBidiHandler, pStr, nStrLen, bIsLangRTL) )
    {
        return MLE_RET_SUCCESS;
    }
    return MLE_RET_FAILED;
#else
    return MLE_RET_SUCCESS;
#endif //__BIDI_TEXT__

}

static MLERet_t _msAPI_MLE_TextTableInsertText( Mle_TextTable_t *pITextTable, const MLE_WChar *pStr, U32 nStrLen, BOOLEAN bIsLangRTL )
{
    Mle_TextTable_t *pThis = (Mle_TextTable_t *)pITextTable;

    if ( pThis == NULL || pStr == NULL || nStrLen == 0 )
    {
        return MLE_RET_BAD_PARAM;
    }

    if ( msAPI_MLE_TEXTUTIL_BidiInsertText(pThis->pBidiHandler, pStr, nStrLen, bIsLangRTL) )
    {
        return MLE_RET_SUCCESS;
    }

    return MLE_RET_FAILED;
}

U32 msAPI_MLE_TextTableGetLineDispStr( Mle_TextTable_t *pITextTable, U32 nIndex, MLE_WChar **ppwDispStr, U32 *pWidth, BOOLEAN *pRTL, BOOLEAN bSkipSpaceAtLast )
{
    Mle_TextTable_t *pThis = (Mle_TextTable_t *)pITextTable;
    U16 *pOrderStr = NULL;
    U32 nStrLen = 0;
    BOOLEAN bIsRTL = FALSE;

    if ( pThis == NULL || pThis->pBidiHandler == NULL )
    {
        return 0;
    }

    msAPI_MLE_TEXTUTIL_BidiGetLineInf( pThis->pBidiHandler,
        nIndex,
        NULL,
        &nStrLen,
        &bIsRTL,
        &pOrderStr,
        NULL,
        NULL );

    if ( pWidth )
    {
        _msAPI_MLE_TextTableGetStrWidth( pThis, pOrderStr, nStrLen, bIsRTL, pWidth, bSkipSpaceAtLast );
    }

    if ( pRTL )
    {
        *pRTL = bIsRTL;
    }

    if ( ppwDispStr )
    {
        *ppwDispStr = pOrderStr;
    }
    else
    {
        FREEIF( pOrderStr );
    }

    return nStrLen;
}

U32 msAPI_MLE_TextTableGetSize( Mle_TextTable_t *pITextTable )
{
    Mle_TextTable_t *pThis = (Mle_TextTable_t *)pITextTable;

    if ( pThis == NULL || pThis->pBidiHandler == NULL )
    {
        return 0;
    }

    return msAPI_MLE_TEXTUTIL_BidiGetTableSize(pThis->pBidiHandler);
}

//pString is input string
Mle_TextTable_t* msAPI_MLE_TextCreateLineTable( const MLE_WChar *pString, U32 nStrLen, BOOLEAN bUseBidiRule, BOOLEAN bWithoutBidi, Text_MeasureInf_t *pMeasureInf)
{
    Mle_TextTable_t *pTable = NULL;
    Mle_TextTable_t *pReturnTable = NULL;
    Text_LineData_t tLineData;
    // MLE_Ret nRet;
    BOOLEAN bIsRTLLang = FALSE;

    U32 nOffset = 0;
    U32 nLineLength = 0;

    do
    {
        //nRet = TextTable_New( &pTable, pMeasureInf, (IBase *)pThis );
        _msAPI_MLE_TextTable_New( (void **) &pTable, pMeasureInf);
        // BREAK_IF_FAIL( nRet  , "" );
#ifdef __BIDI_TEXT__
        if(TRUE == bUseBidiRule)
        {
            bIsRTLLang = msAPI_MLE_TEXTUTIL_IsRTLDisplayLanguage();
            bIsRTLLang = msAPI_MLE_TEXTUTIL_ParagraphIsRTL( pString, nStrLen, bIsRTLLang );
        }
#endif //__BIDI_TEXT__
        if ( pMeasureInf != NULL )
        {
            if ( pMeasureInf->nWidth == (U32)(-1) ) //one line
            {
                tLineData.nOffset = 0;
                tLineData.nLength = nStrLen;
                tLineData.bRTL = bIsRTLLang;

                _msAPI_MLE_TextTableAddLine( pTable, tLineData );
            }
            else
            {
                while( nOffset < nStrLen )
                {
                    //get a line that fit the width
                    nLineLength = _msAPI_MLE_TextGetStrLineLength( (pString + nOffset),
                        nStrLen - nOffset,
                        pMeasureInf );
                    tLineData.nOffset = nOffset;
                    tLineData.nLength = nLineLength;
                    tLineData.bRTL = bIsRTLLang;

                    _msAPI_MLE_TextTableAddLine( pTable, tLineData );

                    if(0==nLineLength)
                    {
                        //LOG_INFO(MAE_LEVEL_UTIL, "_TextCreateLineTable: Current Text=%d, Width=%d", *(pwString+u32Offset) , psMeasureInf->u32Width);
                        break;
                    }

                    nOffset = nOffset + nLineLength;
                }
            }
        }
#ifdef __BIDI_TEXT__
        if ( bWithoutBidi )
        {
            _msAPI_MLE_TextTableInsertText( pTable, pString, nStrLen, bIsRTLLang );
        }
        else
        {
            _msAPI_MLE_TextTableOrderText( pTable, pString, nStrLen, bIsRTLLang );
        }
#else
        _msAPI_MLE_TextTableInsertText( pTable, pString, nStrLen, bIsRTLLang );
#endif //__BIDI_TEXT__
    }while (0);

    pReturnTable = pTable;

    return (Mle_TextTable_t *)pReturnTable;
}

//pString is input string
static U32 _msAPI_MLE_TextGetStrLineLength( const MLE_WChar *pString, U32 nStrLen, Text_MeasureInf_t *pMeasureInf )
{
    U32 nLinePixels = 0;
    U32 nLineLength = 0;
    U32 nReturnValue = 0;

    if ( pString == NULL || nStrLen == 0 )
    {
        return 0;
    }

    // if has measure information, measure line with it.
    // else return the paragraph length
    if ( pMeasureInf != NULL )
    {
        //get a line that fit the width
        if ( pMeasureInf->pfnMeasureLine )
        {
            pMeasureInf->pfnMeasureLine( pString,
                nStrLen,
                pMeasureInf->nWidth,
                pMeasureInf->tFontData.nFontSize,
                pMeasureInf->tFontData.nFontType,
                pMeasureInf->bDiffDirChangeLine,
                &nReturnValue);
        }
        else
        {
            //After optimzie, it become below
            msAPI_MLE_FONTBASE_Vector_MeasureText( pMeasureInf->tFontData.nFontSize,
                pString,
                nStrLen,
                0,
                nStrLen,
                pMeasureInf->nWidth,
                &nLineLength,
                &nLinePixels,
                pMeasureInf->tFontData.nFontType,
                FALSE,
                FALSE );
            
            nReturnValue = nLineLength;
#ifdef __BIDI_TEXT__
            //check the line if need to be cut
            if ( nLinePixels > pMeasureInf->nWidth )
            {
                nReturnValue = msAPI_MLE_TEXTUTIL_MeasureMixedLine(pString, nStrLen, 0, nLineLength, pMeasureInf->bDiffDirChangeLine);
            }
#endif //__BIDI_TEXT__
        }
    }
    else
    {
        nReturnValue = msAPI_MLE_TEXTUTIL_BidiGetParagraphLength(pString, nStrLen);
    }

    return nReturnValue;
}

static BOOLEAN _msAPI_MLE_TextTableGetStrWidth( Mle_TextTable_t *pThis, MLE_WChar *pOrderStr, U32 nStrLen, BOOLEAN bRTL, U32 *pStrWidth, BOOLEAN bSkipSpaceAtLast )
{
    MLE_WChar *pwTempStr = pOrderStr;
    U32 nTempLength = nStrLen;

    if ( pStrWidth == NULL )
    {
        return FALSE;
    }

    *pStrWidth = 0;

    if ( pThis == NULL || pOrderStr == NULL || nStrLen == 0 )
    {
        return FALSE;
    }

    if ( bSkipSpaceAtLast )
    {
        if ( bRTL )
        {
            // ignore white space at first
            while ( nTempLength > 1 && ((*pwTempStr == TEXT_WHITE_SPACE) ||
                MLETEXTUTIL_IsReturnChar(*pwTempStr)) )
            {
                pwTempStr = (U16 *)(pwTempStr + 1);
                nTempLength = nTempLength - 1;
            }
        }
        else
        {
            // ignore white space at last
            while ( nTempLength > 1 && (*(pwTempStr + nTempLength - 1) == TEXT_WHITE_SPACE ||
                MLETEXTUTIL_IsReturnChar(*(pwTempStr + nTempLength - 1))) )
            {
                nTempLength = nTempLength - 1;
            }
        }
    }

    msAPI_MLE_FONTBASE_Vector_MeasureText( pThis->tMeasureInf.tFontData.nFontSize,
        pwTempStr,
        nTempLength,
        0, //max width
        nTempLength,
        0,
        &nTempLength,
        pStrWidth,
        pThis->tMeasureInf.tFontData.nFontType,
        FALSE,
        TRUE );

    return TRUE;
}
