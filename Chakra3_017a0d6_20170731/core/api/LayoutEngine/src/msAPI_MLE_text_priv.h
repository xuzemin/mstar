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


#ifndef __MLE_TEXT_PRIV_H__
#define __MLE_TEXT_PRIV_H__

/******************************/
/*        INCLUDE             */
/******************************/
#include "msAPI_MLE_common_def.h"
#include "msAPI_MLE_text_forward.h"
#include "msAPI_MLE_text_types.h"

/******************************/
/*        DEFINITION          */
/******************************/
typedef struct
{
    ///DECLARE_FUNCTBL(ITextTable);
    ///U32   nRefCnt;
    ///IFONT *pIFont;
    void  *pBidiHandler;
    Text_MeasureInf_t tMeasureInf;
} Mle_TextTable_t;

Mle_TextTable_t* msAPI_MLE_TextCreateLineTable( const MLE_WChar *pString, U32 nStrLen, BOOLEAN bUseBidiRule, BOOLEAN bWithoutBidi, Text_MeasureInf_t *pMeasureInf);
U32 msAPI_MLE_TextTableGetSize( Mle_TextTable_t *pITextTable );
MLERet_t msAPI_MLE_TextTableGetLine( Mle_TextTable_t *pITextTable, U32 nIndex, Text_LineData_t *pLineData );
U32 msAPI_MLE_TextTableGetLineDispStr( Mle_TextTable_t *pITextTable, U32 nIndex, MLE_WChar **ppwDispStr, U32 *pWidth, BOOLEAN *pRTL, BOOLEAN bSkipSpaceAtLast );
void msAPI_MLE_TextTableRelease( Mle_TextTable_t *pITextTable );

#if 0
static void _TextTableFreeItem( void *pData, IBase *pOwner );

typedef struct
{
    DECLARE_FUNCTBL(IText);
    u32    nRefCnt;
    IFONT *pIFont;
} Mae_Text_t;

static u32 _TextTableAddRef( ITextTable *pITextTable );
static u32 _TextTableRelease( ITextTable *pITextTable );
static MAE_Ret _TextTableQueryInterface( ITextTable *pITextTable, MAE_IId nIId, void **ppObj, IBase *pOwner );
static void _TextTableClean( ITextTable *pITextTable );
static MAERet_t _TextTableAddLine( ITextTable *pITextTable, Text_LineData_t tLineData );
static MAERet_t _TextTableGetLine( ITextTable *pITextTable, u32 nIndex, Text_LineData_t *pLineData );
static MAERet_t _TextTableOrderText( ITextTable *pITextTable, const MAE_WChar *pStr, u32 nStrLen, boolean bIsLangRTL );
static MAERet_t _TextTableInsertText( ITextTable *pITextTable, const MAE_WChar *pStr, u32 nStrLen, boolean bIsLangRTL );
static u32 _TextTableGetLineDispStr( ITextTable *pITextTable, u32 nIndex, MAE_WChar **ppDispStr, u32 *pWidth, boolean *pRTL, boolean bSkipSpaceAtLast );
static u32 _TextTableGetSize( ITextTable *pITextTable );
static s32 _TextTableGetLineCharPos( ITextTable *pITextTable, u32 nLine, u32 nLineRealOffset, boolean bIsCharBeginPos, boolean bIsPosOnChar );
static u32 _TextTableGetLineStrOffsetByXPos( ITextTable *pITextTable, u32 nLine, s32 nXPos );
static u32 _TextTableGetLineStrWidth( ITextTable *pITextTable, u32 nLine, u32 nLineRealOffset, u32 nSubStrLen );

static u32 _TextAddRef( IText *pIText );
static u32 _TextRelease( IText *pIText );
static MAE_Ret _TextQueryInterface( IText *pIText, MAE_IId nIId, void **ppObj, IBase *pOwner );
static ITextTable* _TextCreateLineTable( IText *pIText, const MAE_WChar *pString, u32 nStrLen, boolean bUseBidiRule,boolean bWithoutBidi, Text_MeasureInf_t *pMeasureInf, IBase *pOwner );
static u32 _TextGetStrLineLength( IText *pIText, const MAE_WChar *pString, u32 nStrLen, Text_MeasureInf_t *pMeasureInf );
static u32 _TextGetLineStrOffsetByXPos( IText *pIText, const MAE_WChar *pString, u32 nStrLen, boolean bStrRTL, s32 nXPos, Text_MeasureInf_t tMeasureInf );
static s32 _TextGetLineCharPos( IText *pIText, const MAE_WChar *pString, u32 nStrLen, boolean bStrRTL, u32 nOffset, Text_MeasureInf_t tMeasureInf );
static u32 _TextGetLineStrWidth( IText *pIText, const MAE_WChar *pString, u32 nStrLen, boolean bStrRTL, u32 nOffset, u32 nSubStrLen, Text_MeasureInf_t tMeasureInf );
static MAERet_t _TextTableReorderLine( ITextTable *pITextTable, u32 nOffset, const MAE_WChar *pStr, u32 nStrLen );
static MAERet_t _TextTableCharIsRTL( ITextTable *pITextTable, u32 u32LineIndex, u32 u32CharOffsetInLine, boolean *pbIsRTL );
static MAERet_t _TextTableGetFontInf( ITextTable *pITextTable, u32 u32FontCate, u32 u32FontSize, u32 u32FontType, FontInfo *pFontInf );
static MAERet_t _TextTableGetLineOrderStrInputOffset(ITextTable *pITextTable, 
    boolean bIsRTLDisplayLang, 
    u32 nIndex, 
    u32 nInputStartOffset,
    u32 nInputEndOffset,
    u32 *pSelectionStart,
    u32 *pSelectionEnd,
    boolean *pIsStartCharBeginPos,
    boolean *pIsEndCharBeginPos);

/********************/
/* Private functions*/
/********************/
static boolean _TextTableReplaceLine( Mae_TextTable_t *pThis, u32 nLine, Text_LineData_t tLineData );
static u32 _TextTableGetLineOrderStr( Mae_TextTable_t *pThis, u32 nIndex, MAE_WChar **ppOrderStr, u16 **ppu16OrderSeq, boolean *pRTL );
static u32 _TextTableGetLineCharLevel( Mae_TextTable_t *pThis, u32 nIndex, u8 **ppCharLevel );
static boolean _TextTableGetStrWidth( Mae_TextTable_t *pThis, MAE_WChar *pOrderStr, u32 nStrLen, boolean bRTL, u32 *pStrWidth, boolean bSkipSpaceAtLast );
static s32 _TextOffsetToPos(  IFONT *pIFont, const MAE_WChar *pOrderStr, u32 nStrLen, u32 nStrWidth, const u16 *pSeqPos, const u8 *pCharLevel, u32 nStrOffset, Text_MeasureInf_t tMeasureInf, boolean bIsCharBeginPos, boolean bIsPosOnChar );
static u32 _TextXPosToOffset( IFONT *pIFont, const MAE_WChar *pOrderStr, u32 nStrLen, u32 nStrWidth, const u16 *pSeqPos, const u8 *pCharLevel, s32 nXPos, Text_MeasureInf_t tMeasureInf );
static u32 _TextStrWidth( IFONT *pIFont, const MAE_WChar *pOrderStr, u32 nStrLen, const u16 *pSeqPos, const u8 *pCharLevel, u32 nOffset, u32 nSubStrLen, Text_MeasureInf_t tMeasureInf );
#endif

#endif //__MLE_TEXT_PRIV_H__
