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


#include "msAPI_MLE_helper.h"
#include "msAPI_MLE_font_base.h"
#include "msAPI_MLE_text_util.h"
#include "msAPI_MLE_graphic_types.h"
#include "msAPI_MLE_graphic_forward.h"
#include "msAPI_MLE_graphic.h"
#include "msAPI_MLE_font_vector.h"
#include "msAPI_MLE_display_priv.h"

/******************************/
/*        DEFINITION          */
/******************************/

/******************************/
/*         VAIABLES           */
/******************************/

/******************************/
/*     LOCAL FUNCTIONS        */
/******************************/

U32 msAPI_MLE_Display_DrawTextToBitmap(
                                    U32 nFontSize,
                                    const U16 *pText,
                                    S32 Chars,
                                    S32 x,
                                    S32 y,
                                    const Rect_t *pRect,
                                    U32 Types,
                                    OSDClrBtn *pclrBtn)
{
#ifdef __BIDI_TEXT__
    void *pBidHandler = NULL;
#endif //__BIDI_TEXT__
    BOOLEAN bIsRTL = FALSE;
    BOOLEAN bFontMirror = FALSE;
    U16 *pu16DisplayStr = NULL;
    U32 u32DisplayStrLen = 0;
    U32 u32DisplayStrWidth = 0;
    U32 u32OutLen = 0;
    U32 u32OutWidth = 0;
    U32 u32DisplayWidth = 0;
    MLERet_t eRet;

    if ( pRect==NULL )//fix coverity 203959
    {
        return 0;
    }
    Rect_t tRect = *pRect;
    
    if ( pRect )
    {
        u32DisplayWidth = pRect->w - BTN_TEXT_GAP;
    }
    TTF_TRACE(printf("%d %s %s, x=%d, y=%d\n", __LINE__, __FUNCTION__, __FILE__, x, y));
#ifdef __BIDI_TEXT__
    // Conver to display string
    bIsRTL = msAPI_MLE_TEXTUTIL_IsRTLDisplayLanguage();
    TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
    pBidHandler = msAPI_MLE_TEXTUTIL_BidiCreateHandler();    
    if ( msAPI_MLE_TEXTUTIL_BidiOrderText(pBidHandler, (U16 *)pText, (U32)Chars, bIsRTL) )
    {
        TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
        // get the bidi line table and copy to user line table
        //If code executes to this line, pBidHandler must not be NULL
        pu16DisplayStr = msAPI_MLE_TEXTUTIL_BidiGetOrderStr( pBidHandler, &u32DisplayStrLen );
    }
    else
#endif //__BIDI_TEXT__
    {
        TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
        pu16DisplayStr = (U16 *)pText;
        u32DisplayStrLen = (U32)Chars;
    }

    if ( msAPI_MLE_FONTBASE_Vector_MeasureText(nFontSize, pu16DisplayStr, u32DisplayStrLen, 0, u32DisplayStrLen, 0,  &u32DisplayStrLen, &u32DisplayStrWidth, Types, FALSE, FALSE) == MLE_RET_OUT_OF_MEMORY )
        return MLE_RET_OUT_OF_MEMORY;
    TTF_TRACE(printf("%d u32DisplayStrLen = %d, u32DisplayStrWidth = %d\n", __LINE__, u32DisplayStrLen, u32DisplayStrWidth));

    bFontMirror = ( bIsRTL ) && ( !msAPI_OSD_GetDivxSubtitleMode() );
    
    // Calculate display x position
    switch(pclrBtn->enTextAlign)
    {
        default:
        case EN_ALIGNMENT_DEFAULT: //without BTN_TEXT_GAP
            break;
    
        case EN_ALIGNMENT_LEFT:
            if (u32DisplayStrWidth <= u32DisplayWidth)
            {
                x = x + BTN_TEXT_GAP;
            }
            else
            {
                if ( ( u32DisplayStrWidth - u32DisplayWidth ) <= BTN_TEXT_GAP )
                {
                    x = x + BTN_TEXT_GAP - ( u32DisplayStrWidth - u32DisplayWidth );
                }
                else
                {
                    //do nothing, keep original x
                }
            }
            break;
    
        case EN_ALIGNMENT_RIGHT:
            if ( bIsRTL && (!bFontMirror) && u32DisplayWidth > 0 )
            {
                TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
            
                if ( msAPI_MLE_FONTBASE_Vector_MeasureText(nFontSize, pu16DisplayStr, u32DisplayStrLen, 0, u32DisplayStrLen, 0,  &u32DisplayStrLen, &u32DisplayStrWidth, Types, FALSE, FALSE) == MLE_RET_OUT_OF_MEMORY )
                    return MLE_RET_OUT_OF_MEMORY;
            
                if ( x < 0 )
                {
                    x = 0;
                }
                TTF_TRACE(printf("%d %s %s, u32DisplayStrLen=%d, u32DisplayStrWidth=%d\n", __LINE__, __FUNCTION__, __FILE__, u32DisplayStrLen, u32DisplayStrWidth));
                if ( u32DisplayStrWidth > (U32)(u32DisplayWidth) )
                {
                    TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
                    if ( msAPI_MLE_FONTBASE_Vector_MeasureText(nFontSize, pu16DisplayStr, u32DisplayStrLen, 0, u32DisplayStrLen, u32DisplayStrWidth - u32DisplayWidth, &u32OutLen, &u32OutWidth, Types, FALSE, FALSE) == MLE_RET_OUT_OF_MEMORY )
                        return MLE_RET_OUT_OF_MEMORY;
            
                    if ( msAPI_MLE_FONTBASE_Vector_MeasureText(nFontSize, (pu16DisplayStr + u32OutLen), u32DisplayStrLen - u32OutLen, 0, u32DisplayStrLen - u32OutLen, u32DisplayWidth,  &u32DisplayStrLen, &u32DisplayStrWidth, Types, FALSE, FALSE) == MLE_RET_OUT_OF_MEMORY )
                        return MLE_RET_OUT_OF_MEMORY;
                }
            
                ///if ( u32DisplayStrWidth < (U32)(u32DisplayWidth) )
                if ( u32DisplayStrWidth <= (U32)(u32DisplayWidth) )
                {           
                    x = x + u32DisplayWidth - u32DisplayStrWidth;
                    TTF_TRACE(printf("%d %s %s, u32DisplayWidth=%d, u32DisplayStrWidth=%d, x=%d\n", __LINE__, __FUNCTION__, __FILE__, u32DisplayWidth, u32DisplayStrWidth, x));
                }
            }
            else
            {
                if (u32DisplayStrWidth <= u32DisplayWidth)
                {
                    x = x + u32DisplayWidth - u32DisplayStrWidth;
                }
            }
            break;
    
        case EN_ALIGNMENT_CENTER:
            if (u32DisplayStrWidth <= (u32DisplayWidth+BTN_TEXT_GAP) )
            {
                x = x + (u32DisplayWidth+BTN_TEXT_GAP - u32DisplayStrWidth) / 2;
            }
            break;
    }

    TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
    
    if ( bFontMirror )
        msAPI_GE_SetMirror(1, 0);    //patch GE driver
        
    eRet = msAPI_MLE_FONTBASE_Vector_DrawText(
                             nFontSize,
                             x,                            // nStart x
                             y,                            // nStart y
                             pu16DisplayStr,                        // text buffer pointer
                             u32DisplayStrLen,                        // number of text character
                             &tRect,                       // Client area
                             Types,                        // text type
                             pclrBtn,
                             bFontMirror );
    
    if ( bFontMirror )
        msAPI_GE_SetMirror(0, 0);    //patch GE driver
    
#ifdef __BIDI_TEXT__
    msAPI_MLE_TEXTUTIL_BidiFreeHandler( pBidHandler );
#endif //__BIDI_TEXT__
    return eRet;
}

#if 0
U32 msAPI_MLE_Display_DrawClippedTextToBitmap(
    U32 nFontSize,
    const U16 *pText,
    S32 Chars,
    S32 x,
    S32 y,
    const Rect_t *pRect,
    U32 Types,
    OSDClrBtn *pclrBtn)
{
#ifdef __BIDI_TEXT__
    void *pBidHandler = NULL;
#endif //__BIDI_TEXT__
    BOOLEAN bIsRTL = FALSE;
    U16 *pu16DisplayStr = NULL;
    U32 u32DisplayStrLen = 0;
    U32 u32DisplayStrWidth = 0;
    U32 u32OutLen = 0;
    U32 u32OutWidth = 0;
    U32 u32DisplayWidth = 0;
    MLERet_t eRet;
    Rect_t tRect = *pRect;
    
    if ( pRect )
    {
        u32DisplayWidth = pRect->w;
    }
    TTF_TRACE(printf("%d %s %s, x=%d, y=%d\n", __LINE__, __FUNCTION__, __FILE__, x, y));
#ifdef __BIDI_TEXT__
    // Conver to display string
    bIsRTL = msAPI_MLE_TEXTUTIL_IsRTLDisplayLanguage();
    TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
    pBidHandler = msAPI_MLE_TEXTUTIL_BidiCreateHandler();    
    if ( msAPI_MLE_TEXTUTIL_BidiOrderText(pBidHandler, (U16 *)pText, (U32)Chars, bIsRTL) )
    {
        TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
        // get the bidi line table and copy to user line table
        //If code executes to this line, pBidHandler must not be NULL
        pu16DisplayStr = msAPI_MLE_TEXTUTIL_BidiGetOrderStr( pBidHandler, &u32DisplayStrLen );
    }
    else
#endif //__BIDI_TEXT__
    {
        TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
        pu16DisplayStr = (U16 *)pText;
        u32DisplayStrLen = (U32)Chars;
    }

    if ( msAPI_MLE_FONTBASE_Vector_MeasureClippedText(nFontSize, pu16DisplayStr, u32DisplayStrLen, 0, u32DisplayStrLen, u32DisplayWidth,  &u32DisplayStrLen, &u32DisplayStrWidth, Types, FALSE, FALSE) == MLE_RET_OUT_OF_MEMORY )
        return MLE_RET_OUT_OF_MEMORY;
    //printf("%d u32DisplayStrLen = %d, u32DisplayStrWidth = %d\n", __LINE__, u32DisplayStrLen, u32DisplayStrWidth);

    // Calculate display x position
    if ( bIsRTL && u32DisplayWidth > 0 )
    {
        TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));

        if ( msAPI_MLE_FONTBASE_Vector_MeasureText(nFontSize, pu16DisplayStr, u32DisplayStrLen, 0, u32DisplayStrLen, 0,  &u32DisplayStrLen, &u32DisplayStrWidth, Types, FALSE, FALSE) == MLE_RET_OUT_OF_MEMORY )
            return MLE_RET_OUT_OF_MEMORY;

        if ( x < 0 )
        {
            x = 0;
        }
        TTF_TRACE(printf("%d %s %s, u32DisplayStrLen=%d, u32DisplayStrWidth=%d\n", __LINE__, __FUNCTION__, __FILE__, u32DisplayStrLen, u32DisplayStrWidth));
        if ( u32DisplayStrWidth > (U32)(u32DisplayWidth) )
        {
            TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
            if ( msAPI_MLE_FONTBASE_Vector_MeasureText(nFontSize, pu16DisplayStr, u32DisplayStrLen, 0, u32DisplayStrLen, u32DisplayStrWidth - u32DisplayWidth, &u32OutLen, &u32OutWidth, Types, FALSE, FALSE) == MLE_RET_OUT_OF_MEMORY )
                return MLE_RET_OUT_OF_MEMORY;

            if ( msAPI_MLE_FONTBASE_Vector_MeasureText(nFontSize, (pu16DisplayStr + u32OutLen), u32DisplayStrLen - u32OutLen, 0, u32DisplayStrLen - u32OutLen, u32DisplayWidth,  &u32DisplayStrLen, &u32DisplayStrWidth, Types, FALSE, FALSE) == MLE_RET_OUT_OF_MEMORY )
                return MLE_RET_OUT_OF_MEMORY;
        }

        ///if ( u32DisplayStrWidth < (U32)(u32DisplayWidth) )
        if ( u32DisplayStrWidth <= (U32)(u32DisplayWidth) )
        {           
            x = x + u32DisplayWidth - u32DisplayStrWidth;
            TTF_TRACE(printf("%d %s %s, u32DisplayWidth=%d, u32DisplayStrWidth=%d, x=%d\n", __LINE__, __FUNCTION__, __FILE__, u32DisplayWidth, u32DisplayStrWidth, x));
        }
    }
    TTF_TRACE(printf("%d %s %s\n", __LINE__, __FUNCTION__, __FILE__));
    
    eRet = msAPI_MLE_FONTBASE_Vector_DrawText(
               nFontSize,
               x,                            // nStart x
               y,                            // nStart y
               pu16DisplayStr,                        // text buffer pointer
               u32DisplayStrLen,                        // number of text character
               &tRect,                       // Client area
               Types,                        // text type
               pclrBtn,
               bIsRTL);
    
#ifdef __BIDI_TEXT__
    msAPI_MLE_TEXTUTIL_BidiFreeHandler( pBidHandler );
#endif //__BIDI_TEXT__
    return eRet;
}
#endif
/******************************/
/*     GLOBAL FUNCTIONS       */
/******************************/
