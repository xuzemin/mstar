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


#include "msAPI_MLE_text_util.h"
#include "msAPI_MLE_font_base.h"
#include "msAPI_MLE_font_latine.h"
#include "msAPI_MLE_font_thai.h"
#include "msAPI_MLE_font_hindi_priv.h"
#include "msAPI_MLE_font_bengali.h"
#include "msAPI_MLE_font_vector.h"
#include "msAPI_OSD.h"

static BOOLEAN _msAPI_MLE_TextUtil_ExistsCharAt( const MLE_WChar *pText, U32 nLen, U32 *pAt, U16 *pMatchIdx, Mle_TextUtil_BLDirection_e eDir, Mle_TextUtil_BLTable_t *pBLTable );

/******************************/
/*         VARIABLES          */
/******************************/

U32 msAPI_MLE_TEXTUTIL_TextToDisplayString( const MLE_WChar *pString, U32 nStrLen, BOOLEAN bDisplayRTL, MLE_WChar **ppwDisplayStr, BOOLEAN *pIsRTLStr, BOOLEAN bWithoutBidi )
{
#ifdef __BIDI_TEXT__
    U16 *pOrderString = NULL;
    void *pBidHandler = NULL;
#endif //__BIDI_TEXT__
    U32 nDisplayLen = 0;

    if ( pString == NULL || nStrLen == 0 || ppwDisplayStr == NULL )
    {
        return 0;
    }

    *ppwDisplayStr = NULL;
#ifdef __BIDI_TEXT__
    if ( !bWithoutBidi )
    {
        pBidHandler = msAPI_MLE_TEXTUTIL_BidiCreateHandler();

        if ( msAPI_MLE_TEXTUTIL_BidiOrderText( pBidHandler, pString, nStrLen, bDisplayRTL ) )
        {
            pOrderString = msAPI_MLE_TEXTUTIL_BidiGetOrderStr( pBidHandler, &nDisplayLen );

            if ( pOrderString )
            {
                *ppwDisplayStr = (U16 *)MALLOC( sizeof(U16) * nDisplayLen );
                if ( *ppwDisplayStr )
                {
                    MEMCPY( (void *)(*ppwDisplayStr), (void *)pOrderString, sizeof(U16) * nDisplayLen );
                }

                if ( pIsRTLStr )
                {
                    msAPI_MLE_TEXTUTIL_BidiGetLineInf(pBidHandler, 0, NULL, NULL, pIsRTLStr, NULL, NULL, NULL);
                }
            }
        }
        msAPI_MLE_TEXTUTIL_BidiFreeHandler( pBidHandler );
    }
    else
#endif //__BIDI_TEXT__
    {
        if ( pIsRTLStr )
        {
            *pIsRTLStr = FALSE;
        }
    }

    if ( *ppwDisplayStr == NULL )
    {
        nDisplayLen = nStrLen;
        *ppwDisplayStr = (U16 *)MALLOC( sizeof(U16) * nDisplayLen );
        if ( *ppwDisplayStr )
        {
            MEMCPY( (void *)(*ppwDisplayStr), (void *)pString, sizeof(U16) * nDisplayLen );
        }
    }

    return nDisplayLen;
}

void msAPI_MLE_TEXTUTIL_UCS2Invert( MLE_WChar *pString, U32 nStrLen, U32 nOffset, U32 nSubLength, U16 *pSourcePos )
{
    U32 nInvertLen = 0;
    U32 nInvertIndex;
    U32 nTemp = 0;
    U32 i;

    if ( pString == NULL || nStrLen == 0 || nStrLen <= nOffset )
    {
        return;
    }

    nInvertLen = (nOffset + nSubLength > nStrLen) ? (nStrLen - nOffset) : nSubLength;

    for ( i = nOffset; i < nOffset + ((nInvertLen + 1)/2); i++ )
    {
        if ( i >= nStrLen )
        {
            return;
        }

        nInvertIndex = nOffset + (nInvertLen - (i - nOffset) - 1);

        nTemp = pString[i];
        pString[i] = pString[nInvertIndex];
        pString[nInvertIndex] = nTemp ;

        if ( pSourcePos )
        {
            nTemp = pSourcePos[i];
            pSourcePos[i] = pSourcePos[nInvertIndex];
            pSourcePos[nInvertIndex] = nTemp;
        }
    }
}

U32 msAPI_MLE_TEXTUTIL_UCS2RemoveCharAt( MLE_WChar *pString, U32 nStrLen, U32 nOffset )
{
    U32 nReturnValue = 0;

    if ( pString == NULL || nStrLen == 0 || nStrLen <= nOffset )
    {
        return 0;
    }

    nReturnValue = nStrLen;

    // remove last char
    if ( nReturnValue == (nOffset + 1) )
    {
        pString[nOffset] = 0;
    }
    else
    {
        MEMCPY( (void *)(pString + nOffset), (void *)(pString + nOffset + 1), (nReturnValue - (nOffset + 1)) * 2 );
    }

    return (nReturnValue - 1);
}

#ifdef __MMI_BIDI_UI__  
BOOLEAN msAPI_MLE_TEXTUTIL_IsRTLDisplayLanguage( void )
{
    BOOLEAN bIsRTLLang = FALSE;

#if 0
    U8 nLang = 0;
    MLE_Ret eRet;

    eRet = msAPI_MLE_GetLanguage( &nLang );
    if ( eRet == MLE_RET_SUCCESS )
    {
        bIsRTLLang = msAPI_MLE_TEXTUTIL_IsRTLLanguage( nLang );
    }
#else
    bIsRTLLang = msAPI_OSD_IsRTLLanguage(msAPI_OSD_GetOSDLanguage());
#endif

    return bIsRTLLang;
}
#endif

#ifdef __BIDI_TEXT__
BOOLEAN msAPI_MLE_TEXTUTIL_ParagraphIsRTL( const MLE_WChar *pString, U32 nStrLen, BOOLEAN bDisplayRTL )
{
    BOOLEAN pIsRTLStr = FALSE;

    if ( pString == NULL || nStrLen == 0 )
    {
        return FALSE;
    }

    if ( bDisplayRTL )
    {
        pIsRTLStr = TRUE;
    }
    else
    {
        // check first character is RTL char
        if ( msAPI_MLE_TEXTUTIL_BidiIsRTLChar(pString[0]) )
        {
            pIsRTLStr = TRUE;
        }
    }

    return pIsRTLStr;
}

U32 msAPI_MLE_TEXTUTIL_MeasureMixedLine( const MLE_WChar *pString, U32 nStrLen, U32 nOffset, U32 u32LineStrLen, BOOLEAN bDiffDirChangeLine )
{
    BOOLEAN bInRTL = FALSE;
    U32 nLastMixedIndex = 0;
    U32 i;
    U32 nEndOfLine = 0;
    U32 nReturnLen = 0;
    U32 nParagraphLen = 0;

    if ( pString == NULL || nStrLen == 0 || u32LineStrLen == 0 )
    {
        return 0;
    }

    nReturnLen = u32LineStrLen;
    nEndOfLine = nOffset + u32LineStrLen;

    nParagraphLen = msAPI_MLE_TEXTUTIL_BidiGetParagraphLength( pString + nOffset, u32LineStrLen );

    for ( i = nOffset; i < nEndOfLine; i++ )
    {
        if ( msAPI_MLE_TEXTUTIL_BidiIsParagraphChar(pString[i]) )
        {
            nLastMixedIndex = 0;
            nReturnLen = nParagraphLen;
            break;
        }
        else if ( bDiffDirChangeLine )
        {
            if ( pString[i] != TEXT_WHITE_SPACE )
            {
                if ( bInRTL )
                {
                    if ( !msAPI_MLE_TEXTUTIL_BidiIsRTLChar(pString[i]) )
                    {
                        nLastMixedIndex = i;
                        bInRTL = FALSE;
                    }
                }
                else
                {
                    if ( msAPI_MLE_TEXTUTIL_BidiIsRTLChar(pString[i]) )
                    {
                        // First character is arabic
                        if ( i > nOffset )
                        {
                            nLastMixedIndex = i;
                        }
                        bInRTL = TRUE;
                    }
                }
            }
            else
            {
                nLastMixedIndex = 0;
            }
        }
    }

    // not include last character in the line
    if ( nLastMixedIndex > 0 && nEndOfLine < nStrLen )
    {
        if ( pString[nEndOfLine] != TEXT_WHITE_SPACE )
        {
            if ( (bInRTL && msAPI_MLE_TEXTUTIL_BidiIsRTLChar(pString[nEndOfLine])) ||
                    (!bInRTL && !msAPI_MLE_TEXTUTIL_BidiIsRTLChar(pString[nEndOfLine])) )
            {
                nReturnLen = nLastMixedIndex - nOffset;
            }
        }
    }

    return nReturnLen;
}
#endif

BOOLEAN msAPI_MLE_TEXTUTIL_MeasureTextToLineBreak( const MLE_WChar *pText, U32 nStrLen, U32 nWidth, U32 nFontSize, U32 nFontType, BOOLEAN bDiffDirChangeLine, U32 *pFitLen, Mle_TextUtil_BLTable_t *pBLCodeTable )
{
    U32 nFitChar = 0, nPixels = 0;
    U32 nAt = 0; // 0 based
    Mle_TextUtil_BLTable_t tDefaultBLTable;
    Mle_TextUtil_BL_t tDefaultBL[] = {{TEXT_LINE_FEED, 1}, {TEXT_CARRIAGE_RETURN, 1}, {SI_NEW_LINE, 1}};

    if ( pText == NULL || nStrLen == 0 || pFitLen == NULL )
    {
        return FALSE;
    }

    //msAPI_MLE_FontMeasurePartialText(nFontSize, pText, nStrLen, 0, nStrLen, nWidth, &nFitChar, &nPixels, nFontType, FALSE, FALSE);
    //After optimize become below line
    msAPI_MLE_FONTBASE_Vector_MeasureText(nFontSize, (pText + 0), nStrLen, 0, nStrLen, nWidth, &nFitChar, &nPixels, nFontType, FALSE, FALSE);

    if( nFitChar > 0 )
    {
        U16 nMatchedIdx = 0;
#ifdef __BIDI_TEXT__
        U32 nStrMaxLenForMixedLine = 0;
#endif //__BIDI_TEXT__
        tDefaultBLTable.pBLTable = tDefaultBL;
        tDefaultBLTable.nBLTableSize = 3;

        //find LINEFEED from string's beginning
        if( _msAPI_MLE_TextUtil_ExistsCharAt(pText, nFitChar, &nAt, &nMatchedIdx, MLE_TEXTUTIL_BL_FORWARD, &tDefaultBLTable) )
        {
            if ( (nAt + 1) < nFitChar )
            {
                if ( (tDefaultBLTable.pBLTable[nMatchedIdx]).nBLChar == TEXT_LINE_FEED && pText[nAt + 1] == TEXT_CARRIAGE_RETURN )
                {
                    nAt++;
                    nMatchedIdx = 1;
                }
                else if ( (tDefaultBLTable.pBLTable[nMatchedIdx]).nBLChar == TEXT_CARRIAGE_RETURN && pText[nAt + 1] == TEXT_LINE_FEED )
                {
                    nAt++;
                    nMatchedIdx = 0;
                }
                else if ( (tDefaultBLTable.pBLTable[nMatchedIdx]).nBLChar == SI_NEW_LINE )
                {
                    nMatchedIdx = 2;
                }
            }
            nFitChar = (U32)(nAt + (tDefaultBLTable.pBLTable[nMatchedIdx]).bBackwardBreak);
        }
        //find SPACE from string's ending
        else if( nStrLen > nFitChar )
        {
            U32 i = 0;
            S32 nBackwardBreakLineFitChar = -1;
            S32 nChineseThaiFitChar = -1;

            if ( _msAPI_MLE_TextUtil_ExistsCharAt((pText + nFitChar), 1, &nAt, &nMatchedIdx, MLE_TEXTUTIL_BL_FORWARD, pBLCodeTable) == FALSE )
            {
                if( _msAPI_MLE_TextUtil_ExistsCharAt(pText, nFitChar, &nAt, &nMatchedIdx, MLE_TEXTUTIL_BL_BACKWARD, pBLCodeTable) )
                {
                    nBackwardBreakLineFitChar = (S32)(nAt + (pBLCodeTable->pBLTable[nMatchedIdx]).bBackwardBreak);
                }

                for( i = (nFitChar - 1); i > 0; i-- )
                {
                    //if the char next to the space is a Chinese/Thai character, don't break,
                    if( MLETEXUTIL_IsChineseThaiChar(pText[i]) )
                    {
                        nChineseThaiFitChar = (S32)(i + 1);
                        break;
                    }
                }

                if( (nBackwardBreakLineFitChar > 0) || (nChineseThaiFitChar > 0) )
                {
                    nFitChar = MAX(nBackwardBreakLineFitChar, nChineseThaiFitChar);
                }
#ifdef __BIDI_TEXT__
                nStrMaxLenForMixedLine = msAPI_MLE_TEXTUTIL_MeasureMixedLine( pText, nStrLen, 0, nFitChar, bDiffDirChangeLine);

                if ( nStrMaxLenForMixedLine < nFitChar )
                {
                    nFitChar = nStrMaxLenForMixedLine;
                }
#endif //__BIDI_TEXT__
            }
        }

        *pFitLen = nFitChar;
    }
    else
    {
        *pFitLen = 0;
    }

    return TRUE;
}

static BOOLEAN _msAPI_MLE_TextUtil_ExistsCharAt( const MLE_WChar *pText, U32 nLen, U32 *pAt, U16 *pMatchIdx, Mle_TextUtil_BLDirection_e eDir, Mle_TextUtil_BLTable_t *pBLTable )
{
    BOOLEAN bRetVal = FALSE;
    U32 nIdx = 0;
    const MLE_WChar *pChar = NULL;
    U32 i = 0;

    if ( pText == NULL || nLen == 0 || pBLTable == NULL || pMatchIdx == NULL || pAt == NULL )
    {
        return FALSE;
    }

    if ( pBLTable->pBLTable == NULL || pBLTable->nBLTableSize == 0 )
    {
        return FALSE;
    }

    if( MLE_TEXTUTIL_BL_BACKWARD == eDir )
    {
        for( nIdx = nLen; nIdx > 0; --nIdx )
        {
            pChar  = pText + nIdx;

            for( i = 0; i < pBLTable->nBLTableSize; i++ )
            {
                if( (pBLTable->pBLTable[i]).nBLChar == *pChar )
                {
                    bRetVal = TRUE;
                    *pMatchIdx = i;
                    *pAt = nIdx;
                    break;
                }
            }
            if( TRUE == bRetVal )
                break;
        }
    }
    else
    {
        for( nIdx = 0; nIdx < nLen; nIdx++ )
        {
            pChar  = pText + nIdx;

            for( i = 0; i < pBLTable->nBLTableSize; i++ )
            {
                if( (pBLTable->pBLTable[i]).nBLChar == *pChar )
                {
                    bRetVal = TRUE;
                    *pMatchIdx = i;
                    *pAt = nIdx;
                    break;
                }
            }
            if( TRUE == bRetVal )
                break;
        }
    }
    return bRetVal;
}

