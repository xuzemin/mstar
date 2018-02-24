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

#ifdef __THAI_FONT__

#include "msAPI_MLE_common_def.h"
#include "msAPI_MLE_font_thai.h"
#include "msAPI_MLE_font_vector.h"

/* Declarations */
static BOOLEAN msAPI_MLE_FontThaiComposible(U16 nCode1, U16 nCode2);

/* Variables */
static const U8 _nThaiTypeAry[] =
{
    CONS, CONS, CONS, CONS, CONS, CONS, CONS, CONS,
    CONS, CONS, CONS, CONS, CONS, CONS, CONS, CONS,
    CONS, CONS, CONS, CONS, CONS, CONS, CONS, CONS,
    CONS, CONS, CONS, CONS, CONS, CONS, CONS, CONS,
    CONS, CONS, CONS, FV3,  CONS, FV3,  CONS, CONS,
    CONS, CONS, CONS, CONS, CONS, CONS, NON,  FV1,
    AV2,  FV1,  FV1,  AV1,  AV3,  AV2,  AV3,  BV1,
    BV2,  BD,   NON,  NON,  NON,  NON,  NON,  LV,
    LV,   LV,   LV,   LV,   FV2,  NON,  AD2,  TONE,
    TONE, TONE, TONE, AD1,  AD1,  AD3,  NON,  NON,
    NON,  NON,  NON,  NON,  NON,  NON,  NON,  NON,
    NON,  NON,  NON
};

/* Global functions */

// Assume all parameters are valid
U16 _msAPI_MLE_FontThaiGetNextCodes(const U16 *pInTxt, U32 nInLen, U16 *pOutCode, U32 nOutLen, U32 *paConsumed)
{
    U16 i;

    if(!IS_THAI(pInTxt[0]))
        return 0;

    pOutCode[0] = pInTxt[0];
    paConsumed[0] = 1;
    paConsumed[1] = 1;

    if(nInLen == 1)
        return 1;
        
    for(i=1; i<=MAX_THAI_COMBINE_NUM && i<=nInLen && i<=nOutLen; i++)
    {
        if(!msAPI_MLE_FontThaiComposible(pInTxt[i-1], pInTxt[i]))
            break;

        pOutCode[i] = pInTxt[i];
        paConsumed[i + 1] = 1;
    }

    paConsumed[0] = i;
    return i;
}

#ifdef __FEATURE_VECTOR_FONT__
U16 msAPI_MLE_FontThaiVectorGetNextCodes(const U16 *pInTxt, U32 nInLen, U16 *pOutCode, U32 nOutLen, U32 *paConsumed)
{
    U16 u16ReturnLen = 0;

    u16ReturnLen = _msAPI_MLE_FontThaiGetNextCodes(pInTxt, nInLen, pOutCode, nOutLen, paConsumed);

    if ( msAPI_MLE_FONTBASE_IsVectorFontExist() )
    {
        U16 i;
        for ( i = 0; i < u16ReturnLen; i++ )
        {
            if( msAPI_MLE_FontBaseIsControlChar(pOutCode[i]) )
            {
                pOutCode[i] = (U16)(-2); //Control code
            }
            else
            {
                pOutCode[i] = msAPI_MLE_FONTBASE_VectorFontGetGlyphId(pOutCode[i]);
            }
        }
    }
    
    return u16ReturnLen;
}
#endif //__FEATURE_VECTOR_FONT__

/* Static functions */
static BOOLEAN msAPI_MLE_FontThaiComposible(U16 nCode1, U16 nCode2)
{
    U8 nType1, nType2;

    if (!IS_THAI(nCode1) || !IS_THAI(nCode2))
    {
        return FALSE;
    }

    //fix coverity 203941
    if(0x0E01 <= nCode1 && nCode1 <= 0x0E5B)
    {
        nType1 = _nThaiTypeAry[nCode1-0x0E01];
    }
    else
    {
        nType1 = NON;
    }

    if(0x0E01 <= nCode2 && nCode2 <= 0x0E5B)
    {
        nType2 = _nThaiTypeAry[nCode2-0x0E01];
    }
    else
    {
        nType2 = NON;
    }

    //nType1 = _nThaiTypeAry[nCode1-0x0E01];
    //nType2 = _nThaiTypeAry[nCode2-0x0E01];
    //fix coverity 203941-----end

    switch(nType1)
    {
    case CONS:
    {
        if(BV1 == nType2 ||
           BV2 == nType2 ||
           BD == nType2 ||
           TONE == nType2 ||
           AD1 == nType2 ||
           AD2 == nType2 ||
           AD3 == nType2 ||
           AV1 == nType2 ||
           AV2 == nType2 ||
           AV3 == nType2 )
        {
            return TRUE;
        }
    }
        break;

    case BV1:
    case AV1:
    {
        if(TONE == nType2 ||
           AD1 == nType2)
        {
            return TRUE;
        }
    }
        break;

    case BV2:
    case AV2:
    {
        if(TONE == nType2)
        {
            return TRUE;
        }
    }
        break;

    case AV3:
    {
        if(TONE == nType2 ||
           AD2 == nType2)
        {
            return TRUE;
        }
    }
        break;
    }

    return FALSE;
}

BOOLEAN msAPI_MLE_FontThaiGetNextCodeXOffset(U16 *pu16CurrentRefChar, U16 *pu16CurrentCharRefWidth, U16 u16NextChar, U16 u16NextCharWidth, S16 *ps16XOffset)
{
    if (ps16XOffset == NULL)
    {
        return FALSE;
    }

    if (!IS_THAI(*pu16CurrentRefChar) || !IS_THAI(u16NextChar))
    {
        return FALSE;
    }


    if(*pu16CurrentRefChar == 0x0e1b || *pu16CurrentRefChar == 0x0e1d ||*pu16CurrentRefChar == 0x0e1f || *pu16CurrentRefChar == 0x0e2c)
    {
        if(u16NextChar == 0x0e38 || u16NextChar == 0x0e39 || u16NextChar == 0x0e3a) //below base vowels
        {
            *ps16XOffset = *ps16XOffset + (*pu16CurrentCharRefWidth - u16NextCharWidth);
        }
        else
        {
            *ps16XOffset = *ps16XOffset + (*pu16CurrentCharRefWidth - u16NextCharWidth)/2;
        }
    }
    else
    {
        if(u16NextChar == 0x0e4C)
        {
            *ps16XOffset = *ps16XOffset + (*pu16CurrentCharRefWidth - u16NextCharWidth)+(*pu16CurrentCharRefWidth/3);
        }
        else
        {
            *ps16XOffset = *ps16XOffset + (*pu16CurrentCharRefWidth - u16NextCharWidth);
        }
    }
    return TRUE;
}

#endif //__THAI_FONT__
