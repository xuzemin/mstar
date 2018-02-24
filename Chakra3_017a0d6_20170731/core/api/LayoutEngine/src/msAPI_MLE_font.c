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


#define __MLE_FONT_C__

/******************************/
/*        INCLUDE             */
/******************************/
#include "msAPI_MLE_common_def.h"
#include "msAPI_MLE_font_base.h"

/******************************/
/*        DEFINITION          */
/******************************/
#if 0
static u32 _FontAddRef(IFontExt *pIfont);
static u32 _FontRelease(IFontExt *pIfont);
static MAE_Ret _FontQueryInterface(IFontExt *pIfont, MAE_IId nIId, void **ppObj, IBase *pOwner);
static u32 _FontDrawText(IFontExt *pIFont,u32 nFontCate, u32 nFontSize, IBitmap *pDst, s32 x,
                         s32 y, const u16 *pText, u32 nChars, RGBColor_t nForeGround,
                         RGBColor_t nBackGround, const Rect_t *pRect, u32 nFlags);
static MAE_Ret _FontMeasureText(IFontExt *pIFont,u32 nFontCate,  u32 nFontSize, const u16 *pText, u32 nChars,
                                u32 nMaxWidth, u32 *pFits, u32 *pPixels, u32 nType, u32 nSkip, boolean bDispStr);
#endif
#if 0
MLE_Ret msAPI_MLE_FontMeasurePartialText( U32 nFontSize,
                                          const U16 *pText,
                                          U32 nChars,
                                          U32 u32Offset,
                                          U32 u32SubLen,
                                          U32 nMaxWidth,
                                          U32 *pFits,
                                          U32 *pPixels,
                                          U32 nType,
                                          U32 nSkip,
                                          BOOLEAN bDispStr );
#endif
#if 0
static MAE_Ret _FontGetInfo(IFontExt *pIFont,u32 nFontCate,  u32 nFontSize, u32 nType, FontInfo *pInfo);
static MAE_Ret _FontSetFontBase(IFontExt *pIFont, FontBase_t *pFontBase);
static FontBase_t* _FontGetFontBase(IFontExt *pIFont);


/******************************/
/*         VARIABLES          */
/******************************/
/*
    Table of function pointers for IFontExt
*/
static const FUNCTBL(IFontExt) aIFontExtFuncs = { _FontAddRef,
                                                  _FontRelease,
                                                  _FontQueryInterface,
                                                  _FontDrawText,
                                                  _FontMeasureText,
                                                  _FontMeasurePartialText,
                                                  _FontGetInfo,
                                                  _FontSetFontBase,
                                                  _FontGetFontBase};



/******************************/
/*     LOCAL FUNCTIONS        */
/******************************/
/*
    Add reference count to given IFont
*/
static u32 _FontAddRef(IFontExt *pIfont)
{
    _Font_t *pThis = (_Font_t*)pIfont;
    LOG_TRACE(MAE_LEVEL_GRAPHIC, "_FontAddRef\n");

    if(NULL == pThis)
        return 0;

    pThis->nRefCnt++;

    return pThis->nRefCnt;
}

/*
    Release instance of IFontExt
*/
static MAE_Ret _FontRelease(IFontExt *pIfont)
{
    _Font_t *pThis = (_Font_t*)pIfont;
    LOG_TRACE(MAE_LEVEL_GRAPHIC, "_FontRelease\n");

    if(NULL == pThis)
        return 0;

    // one font instance has been released
    FONTBASE_Release(pThis->pIFontBase);

    if(--pThis->nRefCnt == 0)
    {
        MAE_FreeObject(pThis);

        LOG_TRACE(MAE_LEVEL_GRAPHIC, "IFont Freed\n");

        return 0;
    }
    return pThis->nRefCnt;
}

/*
    _FontQueryInterface
*/
static MAE_Ret _FontQueryInterface(IFontExt *pIfont, MAE_IId nIId, void **ppObj, IBase *pOwner)
{
    if (!pIfont || !ppObj || !pOwner)
        return MAE_RET_BAD_PARAM;

    if (nIId != IID_FONT)
        return MAE_RET_NOT_SUPPORTED;

    *ppObj = (void*)pIfont;
    ADDREF(pIfont, pOwner);
    return MAE_RET_SUCCESS;
}

/*
static u16 _FontGetCombineCode(const u16 **ppTxt, u32 *pSize, u32 *pConsumed)
{
    u16 Code;
    //TBD:

    Code = **ppTxt;
    *ppTxt += 1;
    *pConsumed = 1;
    *pSize -= 1;

    return Code;
}
*/

static MAE_Ret _FontDrawText(IFontExt *pIFont,
                             u32 nFontCate,              // category
                             u32 nFontSize,              // Size
                             IBitmap *pDst,             // Destination IBitmap
                             s32 xStart,                // start x
                             s32 yStart,                // start y
                             const u16 *pText,          // text buffer pointer
                             u32 nChars,                 // number of text character
                             RGBColor_t nClrFG,          // foreground color
                             RGBColor_t nClrOL,          // background color
                             const Rect_t *pRect,       // Client area
                             u32 nType)                  // nType
{
    _Font_t *pThis = (_Font_t*)pIFont;
    _Bitmap_t *pBmpDst = (_Bitmap_t *)pDst;

    if(NULL == pThis || NULL == pDst || NULL == pText || 0 == nChars)
        return MAE_RET_BAD_PARAM;

    return FONTBASE_DrawText(pThis->pIFontBase, nFontCate, nFontSize, pBmpDst->pBitmapBase, xStart, yStart, pText, nChars, nClrFG, nClrOL, pRect, nType, NULL, 0);
}

static MAE_Ret _FontMeasureText(IFontExt *pIFont,
                                u32 nFontCate,              // category
                                u32 nFontSize,
                                const u16 *pText,
                                u32 nChars,
                                u32 nMaxWidth,
                                u32 *pFits,
                                u32 *pPixels,
                                u32 nType,
                                u32 nSkip,
                                boolean bDispStr)
{
    _Font_t *pThis = (_Font_t*)pIFont;

    if(NULL == pThis || NULL == pText)
        return MAE_RET_BAD_PARAM;

    if ( bDispStr )
    {
        return FONTBASE_MeasureTextBidi(pThis->pIFontBase, nFontCate, nFontSize, pText, nChars, 0, nChars, nMaxWidth, pFits, pPixels, nType, nSkip, bDispStr);
    }
    else
    {
    return FONTBASE_MeasureText(pThis->pIFontBase, nFontCate, nFontSize, pText, nChars, nMaxWidth, pFits, pPixels, nType, nSkip);
}
}
#endif
#if 0
MLE_Ret msAPI_MLE_FontMeasurePartialText( U32 nFontSize,
                                          const U16 *pText,
                                          U32 nChars,
                                          U32 u32Offset,
                                          U32 u32SubLen,
                                          U32 nMaxWidth,
                                          U32 *pFits,
                                          U32 *pPixels,
                                          U32 nType,
                                          U32 nSkip,
                                          BOOLEAN bDispStr )
{
    if(NULL == pText)
        return MAE_RET_BAD_PARAM;

    if ( (u32Offset + u32SubLen) > nChars )
    {
        return MAE_RET_BAD_PARAM;
    }

    if ( bDispStr )
    {
        //Original, FONTBASE_MeasureTextBidi
        return msAPI_MLE_FONTBASE_Vector_MeasureText(nFontSize, pText, nChars, u32Offset, u32SubLen, nMaxWidth, pFits, pPixels, nType, nSkip, bDispStr);
    }
    else
    {
        return msAPI_MLE_FONTBASE_Vector_MeasureText(nFontSize, (pText + u32Offset), u32SubLen, 0, u32SubLen, nMaxWidth, pFits, pPixels, nType, nSkip, FALSE);
    }
}
#endif
#if 0
static MAE_Ret _FontGetInfo(IFontExt *pIFont,
                            u32 nFontCate,
                            u32 nFontSize,           // Font Size to query
                            u32 nType,
                            FontInfo *pInfo)
{
    _Font_t *pThis = (_Font_t*)pIFont;

    if(NULL == pThis || NULL == pInfo)
        return MAE_RET_BAD_PARAM;

    return FONTBASE_GetInfo(pThis->pIFontBase,nFontCate, nFontSize, nType, pInfo);
}

static MAE_Ret _FontSetFontBase(IFontExt *pIFont, FontBase_t *pFontBase)
{
    _Font_t *pThis = (_Font_t*)pIFont;

    pThis->pIFontBase = pFontBase;
    return MAE_RET_SUCCESS;
}


static FontBase_t* _FontGetFontBase(IFontExt *pIFont)
{
    _Font_t *pThis = (_Font_t*)pIFont;

    return pThis->pIFontBase;
}



/******************************/
/*     GLOBAL FUNCTIONS       */
/******************************/
MAE_Ret Font_New(MAE_ClsId nIId, void **ppIFont)
{
    _Font_t *pFont;
    u32 nRet = MAE_RET_SUCCESS;

    LOG_TRACE(MAE_LEVEL_GRAPHIC, "IFont_CreateInstance\n");

    if (ppIFont == 0) return MAE_RET_BAD_PARAM;

    do
    {
        if ((pFont = (_Font_t*)MAE_AllocObjectEx(sizeof(_Font_t), (IBase_Vtbl*)&aIFontExtFuncs)) == 0)
        {
            *ppIFont = 0;
            nRet = MAE_RET_OUT_OF_MEMORY;
            break;
        }

        if (MAE_RET_SUCCESS != FONTBASE_New(nIId, &pFont->pIFontBase))
            break;

        *ppIFont = (void*)pFont;
        pFont = NULL;

    }while(0);

    if(pFont)
        _FontRelease((IFontExt*)pFont);

    return nRet;
}
#endif
