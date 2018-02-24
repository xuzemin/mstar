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


#ifndef __MSAPI_MLE_TEXT_UTIL_H__
#define __MSAPI_MLE_TEXT_UTIL_H__
#include "msAPI_MLE_common_def.h"

/*
@brief - to define a ucs2 code of white space character.
*/
#define TEXT_WHITE_SPACE 0x0020
#define TEXT_LINE_FEED   0x000A
#define TEXT_CARRIAGE_RETURN   0x000D
#define SI_NEW_LINE     0x008A
#define SI_CONTROL_CODE_START   0x0080
#define SI_CONTROL_CODE_END     0x009F

#define TEXT_CHINESE_UNICODE_SECTION1_START  0x4E00
#define TEXT_CHINESE_UNICODE_SECTION1_END    0x709D
#define TEXT_CHINESE_UNICODE_SECTION2_START  0x70AB
#define TEXT_CHINESE_UNICODE_SECTION2_END    0x9FA0
#define TEXT_THAI_UNICODE_SECTION_START      0x0E00
#define TEXT_THAI_UNICODE_SECTION_END        0x0F7F

#define TEXT_MAX_COMPOSED_SIZE 10

#define MLETEXTUTIL_IsReturnChar(_Char_) ((U16)_Char_ == 0x000A || (U16)_Char_ == 0x000D)

#define MLETEXUTIL_IsChineseChar(_Char_) ( ((_Char_ >= TEXT_CHINESE_UNICODE_SECTION1_START && _Char_ <= TEXT_CHINESE_UNICODE_SECTION1_END) || \
                                                (_Char_ >= TEXT_CHINESE_UNICODE_SECTION2_START && _Char_ <= TEXT_CHINESE_UNICODE_SECTION2_END)) )

#define MLETEXUTIL_IsChineseThaiChar(_Char_) ( ((_Char_ >= TEXT_CHINESE_UNICODE_SECTION1_START && _Char_ <= TEXT_CHINESE_UNICODE_SECTION1_END) || \
                                                (_Char_ >= TEXT_CHINESE_UNICODE_SECTION2_START && _Char_ <= TEXT_CHINESE_UNICODE_SECTION2_END)) || \
                                               (_Char_ >= TEXT_THAI_UNICODE_SECTION_START && _Char_ <= TEXT_THAI_UNICODE_SECTION_END) )
#ifdef __BIDI_TEXT__
/*
@brief - to check a input language is RTL or LTR display direction. ( ARABIC, HEBREW now )
*/
#define MLETEXTUTIL_BidiIsRTL( _Level_ ) ( (_Level_ % 2) == 1 )
#endif //__BIDI_TEXT__
typedef enum
{
    MLE_TEXTUTIL_BL_FORWARD,
    MLE_TEXTUTIL_BL_BACKWARD
}Mle_TextUtil_BLDirection_e;

typedef struct
{
    MLE_WChar nBLChar;
    BOOLEAN bBackwardBreak;
}Mle_TextUtil_BL_t;

typedef struct
{
    Mle_TextUtil_BL_t *pBLTable;
    U16 nBLTableSize;
}Mle_TextUtil_BLTable_t;

/****************/
/* Text convert */
/****************/

/*
@brief - Convert text to display string. note that only the first paragraph will be convert to display string.
@param - [in]pu16String: a ucs2 string
@param - [in]nStrLen: the length of ucs2 string
@param - [in]bIsRTL: the display direction of the string. (in Arabic language, the bIsRTL should be TRUE)
@param - [in]ppu16DisplayStr: a double pointer of display string, allocate by this function and need to free it by caller.
@return - [out]U32: the length of display string
*/
U32     msAPI_MLE_TEXTUTIL_TextToDisplayString( const MLE_WChar *pString, U32 nStrLen, BOOLEAN bDisplayRTL, MLE_WChar **ppwDisplayStr, BOOLEAN *pIsRTLStr, BOOLEAN bWithoutBidi );

/*
@brief - invert part of sequence characters in ucs2 string.
@param - [in]pu16String: a ucs2 string
@param - [in]nStrLen: the length of ucs2 string
@param - [in]nOffset: the start position that want to invert in this string
@param - [in]pSubLength: the length that want to invert
@param - [in][out]pSourcePos: Get the original string location position after invert.
                                 if doesn't get the information, assign to NULL
@return - none
*/
void    msAPI_MLE_TEXTUTIL_UCS2Invert( MLE_WChar *pString, U32 nStrLen, U32 nOffset, U32 pSubLength, U16 *pSourcePos );

/*
@brief - remove a chararcter at x index in a ucs2 string.
@param - [in]pu16String: a ucs2 string
@param - [in]nStrLen: the length of ucs2 string after removed a character
@param - [in]nOffset: the position of character that want to remvoed in this string
@return - [out]U32: the remain string length after remove a character
*/
U32     msAPI_MLE_TEXTUTIL_UCS2RemoveCharAt( MLE_WChar *pString, U32 nStrLen, U32 nOffset );

BOOLEAN msAPI_MLE_TEXTUTIL_UCS2IsComposedNextChars( const MLE_WChar *pString, U32 nStrLen, U32 nOffset, MLE_WChar **ppComposedStr, U32 *pComposedLen, U32 *paConsumed, BOOLEAN bDispStr );
BOOLEAN msAPI_MLE_TEXTUTIL_UCS2IsComposedPreChars( const MLE_WChar *pString, U32 nStrLen, U32 nOffset, MLE_WChar **ppComposedStr, U32 *pComposedLen, U32 *paConsumed, BOOLEAN bDispStr );

#ifdef __MMI_BIDI_UI__
BOOLEAN msAPI_MLE_TEXTUTIL_IsRTLDisplayLanguage( void );
BOOLEAN msAPI_MLE_TEXTUTIL_IsRTLLanguage( U8 nLan );
#endif //__MMI_BIDI_UI__

#ifdef __BIDI_TEXT__
/*
@brief - Check a paragraph text's display direction.
@param - [in]pu16String: a ucs2 string.
@param - [in]nStrLen: the length of ucs2 string.
@param - [in]bIsRTL: the display direction of the string. (in Arabic language, the bIsRTL should be TRUE)
@return - [out]BOOLEAN: The paragraph text is display RTL or LTR. TRUE, is RTL.
*/
BOOLEAN msAPI_MLE_TEXTUTIL_ParagraphIsRTL( const MLE_WChar *pString, U32 nStrLen, BOOLEAN bDisplayRTL );

/*
@brief - Check a character is an Arabic character.
@param - [in]u16Char: a ucs2 character
@return - [out]BOOLEAN: Is an Arabic character or not. TRUE, an Arabic character.
*/
U32     msAPI_MLE_TEXTUTIL_MeasureMixedLine( const MLE_WChar *pString, U32 nStrLen, U32 nOffset, U32 nLineStrLen, BOOLEAN bDiffDirChangeLine );


#endif //__BIDI_TEXT__

BOOLEAN msAPI_MLE_TEXTUTIL_MeasureTextToLineBreak( const MLE_WChar *pText, U32 nStrLen, U32 nWidth, U32 nFontSize, U32 nFontType, BOOLEAN bDiffDirChangeLine, U32 *pu32FitLen, Mle_TextUtil_BLTable_t *pBLCodeTable );

#ifdef __BIDI_TEXT__

/**********/
/* Arabic */
/**********/
/*
@brief - conver a ucs2 arabic string to a display string.
@param - [in]pu16String: a ucs2 string
@param - [in]nStrLen: the length of ucs2 string.
@return - [out]U32: the display string length after convert to arabic string.
                   (the string length maybe changed after converting)
*/
U32     msAPI_MLE_TEXTUTIL_ConvertToArabicStr( MLE_WChar *pString, U32 nStrLen, BOOLEAN bDispStr );

BOOLEAN msAPI_MLE_TEXTUTIL_ConvertToArabicFEStr( MLE_WChar *pString, U32 nStrLen, BOOLEAN bDispStr );

U16 msAPI_MLE_TEXTUTIL_ConvertToArabicFEChar( const MLE_WChar *pString, U32 nStrLen, U32 nOffset, BOOLEAN bDispStr, U16 *pNextFEChar );

/*
@brief - conver a ucs2 Europe number to a Arabic number.
@param - [in]pu16String: a ucs2 string
@param - [in]nStrLen: the length of ucs2 string.
@return - [out]U32: the string length after converting.
*/
U32     msAPI_MLE_TEXTUTIL_NumConvertToArabicNum( MLE_WChar *pString, U32 nStrLen );

/*
@brief - conver a ucs2 Arabic number to a Europe number.
@param - [in]pu16String: a ucs2 string
@param - [in]nStrLen: the length of ucs2 string.
@return - [out]U32: the string length after converting.
*/
U32     msAPI_MLE_TEXTUTIL_ArabicNumConvertToNum( MLE_WChar *pString, U32 nStrLen );

/*
@brief - Check text is include arabic characters in it.
@param - [in]pu16String: a ucs2 string
@param - [in]nStrLen: the length of ucs2 string.
@return - [out]BOOLEAN: Is an arabic text or not. TRUE, an Arabic text.
*/
BOOLEAN msAPI_MLE_TEXTUTIL_IsArabicText( const MLE_WChar *pString, U32 nStrLen );

/*
@brief - Check a character is an Arabic character.
@param - [in]u16Char: a ucs2 character
@return - [out]BOOLEAN: Is an Arabic character or not. TRUE, an Arabic character.
*/
BOOLEAN msAPI_MLE_TEXTUTIL_IsArabicChar( MLE_WChar nChar );

/*
@brief - Check a character is concatenate to pre-character or next-character.
@param - [in][out]pu16Char: a ucs2 character that want to check. the return value the convered character for display
@param - [in]u16PreChar: the character before the checked character. If the checked character
                         is first and assign this value to 0.
@param - [in]u16NextChar: the character after the checked character. If the checked character
                          is last and assign this value to 0.
@param - [in][out]pbInWord: notic the check character is in a word (not the first or last character of a word)
                            if the check character is a first character of a word, assign to FALSE.
                            You maybe should keep the value for check a sequence string by it.
@param - [in][out]pbPreCharIsFirst: notic the pre-character is the first character in a word.
                                    if the check character is a first character of a word, assign to FALSE.
                                    You maybe should keep the value for check a sequence string by it.
@return - [out]BOOLEAN: Is an concatenatin character or not. TRUE, an concatenation character.
*/
BOOLEAN msAPI_MLE_TEXTUTIL_ConcatenationArabicFEChar( MLE_WChar *pChar, MLE_WChar nNextChar );


/******************/
/* Bidi paragraph */
/******************/

/*
@brief - Check a character is an paragraph character.
@param - [in]u16Char: a ucs2 character
@return - [out]BOOLEAN: Is an paragraph character or not. TRUE, an paragraph character.
*/
BOOLEAN msAPI_MLE_TEXTUTIL_BidiIsParagraphChar( MLE_WChar nChar );

__SLDPM_FREE__ BOOLEAN msAPI_MLE_TEXTUTIL_BidiIsRTLChar( MLE_WChar nChar );

#endif //__BIDI_TEXT__

/*
@brief - To get the first paragraph length from a input text.
@param - [in]pu16String: a ucs2 string.
@return - [out]U32: a paragraph string length.
*/
U32     msAPI_MLE_TEXTUTIL_BidiGetParagraphLength( const MLE_WChar *pString, U32 nStrLen );

/*
@brief - To only order the first paragraph of a input text.
@param - [in][out]pu16String: a ucs2 string.
@param - [in][out]pStrLen: input string length and change to paragraph string length after calling.
@param - [in][out]pbDisplayRight2Left: the string display direction.
@param - [out]ppSeqPos: the paragraph logical order of ordering string.
                           Allocate memory in this function, and must free by caller.
@return - [out]BOOLEAN: success or not. TRUE, success.
*/
BOOLEAN msAPI_MLE_TEXTUTIL_BidiOrderParagraph( MLE_WChar *pString, U32 *pStrLen, BOOLEAN bDisplayRight2Left, U16 **ppSeqPos, U8 **ppCharLevel );


/**********************/
/* Bidi order handler */
/**********************/

/*
@brief - To create a bidi handler.
@return - [out]void*: a pointer of bidi handler.
*/
__SLDPM_FREE__ void*   msAPI_MLE_TEXTUTIL_BidiCreateHandler( void );

/*
@brief - To free a bidi handler.
@param - [in]pHandler: a pointer of bidi handler.
@return - none.
*/
void    msAPI_MLE_TEXTUTIL_BidiFreeHandler( void *pHandler );

#ifdef __BIDI_TEXT__
/*
@brief - To order the input text. (support multi-paragraph)
         ordering result is record in bidi handler. you can access information by bidi handler.
@param - [in]pHandler: a pointer of bidi handler.
@param - [in]pu16String: a ucs2 string.
@param - [in]nStrLen: input string length.
@param - [in]bDisplayRight2Left: the string display direction.
@return - [out]BOOLEAN: success or not. TRUE, success.
*/
__SLDPM_FREE__ BOOLEAN msAPI_MLE_TEXTUTIL_BidiOrderText( void *pHandler, const MLE_WChar *pString, U32 nStrLen, BOOLEAN bDisplayRight2Left );
#endif //__BIDI_TEXT__
BOOLEAN msAPI_MLE_TEXTUTIL_BidiInsertText( void *pHandler, const MLE_WChar *pString, U32 nStrLen, BOOLEAN bDisplayRight2Left );
BOOLEAN msAPI_MLE_TEXTUTIL_BidiReorderText( void *pHandler, U32 nOffset, const MLE_WChar *pString, U32 nStrLen );

/*
@brief - To re-init the bidi hanlder's line table.
@param - [in]pHandler: a pointer of bidi handler.
@return - none.
*/
void    msAPI_MLE_TEXTUTIL_BidiInitTable( void *pHandler );

/*
@brief - To add a new line information to bidi handler's line table.
         It will make the bidi order input string depend on your line information.
@param - [in]pHandler: a pointer of bidi handler.
@param - [in]nOffset: the line begin offset in a text.
@param - [in]nStrLen: the line string length.
@param - [in]bRTL: the line display direction. (depend on current display language)
@return - [out]BOOLEAN: success or not. TRUE, success.
*/
__SLDPM_FREE__ BOOLEAN msAPI_MLE_TEXTUTIL_BidiAddLine( void *pHandler, U32 nOffset, U32 nStrLen, BOOLEAN bRTL );

BOOLEAN msAPI_MLE_TEXTUTIL_BidiModifyLineInfo( void *pHandler, U32 u32Line, U32 nOffset, U32 nStrLen, BOOLEAN bRTL );

/*
@brief - To get the bidi handler's line table size.
@param - [in]pHandler: a pointer of bidi handler.
@return - [out]U32: the table size.
*/
U32     msAPI_MLE_TEXTUTIL_BidiGetTableSize( void *pHandler );

BOOLEAN msAPI_MLE_TEXTUTIL_BidiSetTableSize( void *pHandler, U32 u32Size );

/*
@brief - To get a order line's information (after ordering a string by bidi).
@param - [in]pHandler: a pointer of bidi handler.
@param - [in]u32Index: the index of line in handler's line table.
@param - [out]pOffset: the line string begin offset in a input text.
@param - [out]pLineStrLen: the line string length.
@param - [out]pbRTL: the line string display direction.
@param - [out]ppLineString: the line ordering string.
                               Allocate memory in this function, and must free by caller.
@param - [out]ppSeqInLine: the line logical order of ordering string.
                              Allocate memory in this function, and must free by caller.
@return - [out]BOOLEAN: success or not. TRUE, success.
*/
BOOLEAN msAPI_MLE_TEXTUTIL_BidiGetLineInf( void *pHandler, U32 u32Index, U32 *pOffset, U32 *pLineStrLen, BOOLEAN *pbRTL, U16 **ppLineString, U16 **ppSeqInLine, U8 **pCharLevel );

U16* msAPI_MLE_TEXTUTIL_BidiGetOrderStr( void *pHandler, U32 *pStrLen );

#endif /* __MSAPI_MLE_TEXT_UTIL_H__ */
