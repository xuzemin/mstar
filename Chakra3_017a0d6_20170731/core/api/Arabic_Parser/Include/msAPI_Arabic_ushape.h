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
//******************************************************************************
//<MStar Software>
//---------------------------------------------------------------------------
// ICU License - ICU 1.8.1 and later
//
// COPYRIGHT AND PERMISSION NOTICE
//
// Copyright (c) 1995-2008 International Business Machines Corporation and others
//
// All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, provided that 
// the above copyright notice(s) and this permission notice appear in all copies of
// the Software and that both the above copyright notice(s) and this permission 
// notice appear in supporting documentation.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
// PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS. IN NO EVENT SHALL 
// THE COPYRIGHT HOLDER OR HOLDERS INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM, 
// OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER 
// RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, 
// NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE 
// OR PERFORMANCE OF THIS SOFTWARE.
//
// Except as contained in this notice, the name of a copyright holder shall not be 
// used in advertising or otherwise to promote the sale, use or other dealings in 
// this Software without prior written authorization of the copyright holder.
//
// All trademarks and registered trademarks mentioned herein are the property of 
// their respective owners. 
//---------------------------------------------------------------------------

#ifndef __USHAPE_H__
#define __USHAPE_H__

#include "msAPI_ParserSys.h"

/**
 * \file
 * \brief C API:  Arabic shaping
 * 
 */

/**
 * Shape Arabic text on a character basis.
 *
 * <p>This function performs basic operations for "shaping" Arabic text. It is most
 * useful for use with legacy data formats and legacy display technology
 * (simple terminals). All operations are performed on Unicode characters.</p>
 *
 * <p>Text-based shaping means that some character code points in the text are
 * replaced by others depending on the context. It transforms one kind of text
 * into another. In comparison, modern displays for Arabic text select
 * appropriate, context-dependent font glyphs for each text element, which means
 * that they transform text into a glyph vector.</p>
 *
 * <p>Text transformations are necessary when modern display technology is not
 * available or when text needs to be transformed to or from legacy formats that
 * use "shaped" characters. Since the Arabic script is cursive, connecting
 * adjacent letters to each other, computers select images for each letter based
 * on the surrounding letters. This usually results in four images per Arabic
 * letter: initial, middle, final, and isolated forms. In Unicode, on the other
 * hand, letters are normally stored abstract, and a display system is expected
 * to select the necessary glyphs. (This makes searching and other text
 * processing easier because the same letter has only one code.) It is possible
 * to mimic this with text transformations because there are characters in
 * Unicode that are rendered as letters with a specific shape
 * (or cursive connectivity). They were included for interoperability with
 * legacy systems and codepages, and for unsophisticated display systems.</p>
 *
 * <p>A second kind of text transformations is supported for Arabic digits:
 * For compatibility with legacy codepages that only include European digits,
 * it is possible to replace one set of digits by another, changing the
 * character code points. These operations can be performed for either
 * Arabic-Indic Digits (U+0660...U+0669) or Eastern (Extended) Arabic-Indic
 * digits (U+06f0...U+06f9).</p>
 *
 * <p>Some replacements may result in more or fewer characters (code points).
 * By default, this means that the destination buffer may receive text with a
 * length different from the source length. Some legacy systems rely on the
 * length of the text to be constant. They expect extra spaces to be added
 * or consumed either next to the affected character or at the end of the
 * text.</p>
 *
 * <p>For details about the available operations, see the description of the
 * <code>U_SHAPE_...</code> options.</p>
 *
 * @param source The input text.
 *
 * @param sourceLength The number of UChars in <code>source</code>.
 *
 * @param dest The destination buffer that will receive the results of the
 *             requested operations. It may be <code>NULL</code> only if
 *             <code>destSize</code> is 0. The source and destination must not
 *             overlap.
 *
 * @param destSize The size (capacity) of the destination buffer in UChars.
 *                 If <code>destSize</code> is 0, then no output is produced,
 *                 but the necessary buffer size is returned ("preflighting").
 *
 * @param options This is a 32-bit set of flags that specify the operations
 *                that are performed on the input text. If no error occurs,
 *                then the result will always be written to the destination
 *                buffer.
 *
 * @param pErrorCode must be a valid pointer to an error code value,
 *        which must not indicate a failure before the function call.
 *
 * @return The number of UChars written to the destination buffer.
 *         If an error occured, then no output was written, or it may be
 *         incomplete. If <code>U_BUFFER_OVERFLOW_ERROR</code> is set, then
 *         the return value indicates the necessary destination buffer size.
 * @stable ICU 2.0
 */ 
//S32  u_shapeArabic(const U16 *source, S32 sourceLength,
//              U16 *dest, S32 destSize,
//            S32 options,
//              S32 *pErrorCode);
extern U16  ArabicParser( U16 *source, U16 sourceLength,
              U16 *dest, U16 destSize,
              U32 options,
              S32 *pErrorCode);

/**
 * Memory option: allow the result to have a different length than the source.
 * @stable ICU 2.0
 */
#define U_SHAPE_LENGTH_GROW_SHRINK              0

/**
 * Memory option: the result must have the same length as the source.
 * If more room is necessary, then try to consume spaces next to modified characters.
 * @stable ICU 2.0
 */
#define U_SHAPE_LENGTH_FIXED_SPACES_NEAR        1

/**
 * Memory option: the result must have the same length as the source.
 * If more room is necessary, then try to consume spaces at the end of the text.
 * @stable ICU 2.0
 */
#define U_SHAPE_LENGTH_FIXED_SPACES_AT_END      2

/**
 * Memory option: the result must have the same length as the source.
 * If more room is necessary, then try to consume spaces at the beginning of the text.
 * @stable ICU 2.0
 */
#define U_SHAPE_LENGTH_FIXED_SPACES_AT_BEGINNING 3

/** Bit mask for memory options. @stable ICU 2.0 */
#define U_SHAPE_LENGTH_MASK                     3


/** Direction indicator: the source is in logical (keyboard) order. @stable ICU 2.0 */
#define U_SHAPE_TEXT_DIRECTION_LOGICAL          0

/**
 * Direction indicator:
 * the source is in visual LTR order,
 * the leftmost displayed character stored first.
 * @stable ICU 2.0
 */
#define U_SHAPE_TEXT_DIRECTION_VISUAL_LTR       4

/** Bit mask for direction indicators. @stable ICU 2.0 */
#define U_SHAPE_TEXT_DIRECTION_MASK             4


/** Letter shaping option: do not perform letter shaping. @stable ICU 2.0 */
#define U_SHAPE_LETTERS_NOOP                    0

/** Letter shaping option: replace abstract letter characters by "shaped" ones. @stable ICU 2.0 */
#define U_SHAPE_LETTERS_SHAPE                   8

/** Letter shaping option: replace "shaped" letter characters by abstract ones. @stable ICU 2.0 */
#define U_SHAPE_LETTERS_UNSHAPE                 0x10

/**
 * Letter shaping option: replace abstract letter characters by "shaped" ones.
 * The only difference with U_SHAPE_LETTERS_SHAPE is that Tashkeel letters
 * are always "shaped" into the isolated form instead of the medial form
 * (selecting code points from the Arabic Presentation Forms-B block).
 * @stable ICU 2.0
 */
#define U_SHAPE_LETTERS_SHAPE_TASHKEEL_ISOLATED 0x18

/** Bit mask for letter shaping options. @stable ICU 2.0 */
#define U_SHAPE_LETTERS_MASK                    0x18


/** Digit shaping option: do not perform digit shaping. @stable ICU 2.0 */
#define U_SHAPE_DIGITS_NOOP                     0

/**
 * Digit shaping option:
 * Replace European digits (U+0030...) by Arabic-Indic digits.
 * @stable ICU 2.0
 */
#define U_SHAPE_DIGITS_EN2AN                    0x20

/**
 * Digit shaping option:
 * Replace Arabic-Indic digits by European digits (U+0030...).
 * @stable ICU 2.0
 */
#define U_SHAPE_DIGITS_AN2EN                    0x40

/**
 * Digit shaping option:
 * Replace European digits (U+0030...) by Arabic-Indic digits if the most recent
 * strongly directional character is an Arabic letter
 * (<code>u_charDirection()</code> result <code>U_RIGHT_TO_LEFT_ARABIC</code> [AL]).<br>
 * The direction of "preceding" depends on the direction indicator option.
 * For the first characters, the preceding strongly directional character
 * (initial state) is assumed to be not an Arabic letter
 * (it is <code>U_LEFT_TO_RIGHT</code> [L] or <code>U_RIGHT_TO_LEFT</code> [R]).
 * @stable ICU 2.0
 */
#define U_SHAPE_DIGITS_ALEN2AN_INIT_LR          0x60

/**
 * Digit shaping option:
 * Replace European digits (U+0030...) by Arabic-Indic digits if the most recent
 * strongly directional character is an Arabic letter
 * (<code>u_charDirection()</code> result <code>U_RIGHT_TO_LEFT_ARABIC</code> [AL]).<br>
 * The direction of "preceding" depends on the direction indicator option.
 * For the first characters, the preceding strongly directional character
 * (initial state) is assumed to be an Arabic letter.
 * @stable ICU 2.0
 */
#define U_SHAPE_DIGITS_ALEN2AN_INIT_AL          0x80

/** Not a valid option value. May be replaced by a new option. @stable ICU 2.0 */
#define U_SHAPE_DIGITS_RESERVED                 0xa0

/** Bit mask for digit shaping options. @stable ICU 2.0 */
#define U_SHAPE_DIGITS_MASK                     0xe0


/** Digit type option: Use Arabic-Indic digits (U+0660...U+0669). @stable ICU 2.0 */
#define U_SHAPE_DIGIT_TYPE_AN                   0

/** Digit type option: Use Eastern (Extended) Arabic-Indic digits (U+06f0...U+06f9). @stable ICU 2.0 */
#define U_SHAPE_DIGIT_TYPE_AN_EXTENDED          0x100

/** Not a valid option value. May be replaced by a new option. @stable ICU 2.0 */
#define U_SHAPE_DIGIT_TYPE_RESERVED             0x200

/** Bit mask for digit type options. @stable ICU 2.0 */
#define U_SHAPE_DIGIT_TYPE_MASK                 0x3f00

/** 
 * Tashkeel aggregation option:
 * Replaces any combination of U+0651 with one of
 * U+064C, U+064D, U+064E, U+064F, U+0650 with
 * U+FC5E, U+FC5F, U+FC60, U+FC61, U+FC62 consecutively.
 * @stable ICU 3.6
 */
#define U_SHAPE_AGGREGATE_TASHKEEL              0x4000
/** Tashkeel aggregation option: do not aggregate tashkeels. @stable ICU 3.6 */
#define U_SHAPE_AGGREGATE_TASHKEEL_NOOP         0
/** Bit mask for tashkeel aggregation. @stable ICU 3.6 */
#define U_SHAPE_AGGREGATE_TASHKEEL_MASK         0x4000

/** 
 * Presentation form option:
 * Don't replace Arabic Presentation Forms-A and Arabic Presentation Forms-B
 * characters with 0+06xx characters, before shaping.
 * @stable ICU 3.6
 */
#define U_SHAPE_PRESERVE_PRESENTATION           0x8000
/** Presentation form option: 
 * Replace Arabic Presentation Forms-A and Arabic Presentationo Forms-B with 
 * their unshaped correspondants in range 0+06xx, before shaping.
 * @stable ICU 3.6 
 */
#define U_SHAPE_PRESERVE_PRESENTATION_NOOP      0
/** Bit mask for preserve presentation form. @stable ICU 3.6 */
#define U_SHAPE_PRESERVE_PRESENTATION_MASK      0x8000

#endif

//---------------------------------------------------------------------------
/*
UNICODE, INC. LICENSE AGREEMENT - DATA FILES AND SOFTWARE

    Unicode Data Files include all data files under the directories
http://www.unicode.org/Public/, http://www.unicode.org/reports/, and
http://www.unicode.org/cldr/data/ . Unicode Software includes any source code
published in the Unicode Standard or under the directories
http://www.unicode.org/Public/, http://www.unicode.org/reports/, and
http://www.unicode.org/cldr/data/.

    NOTICE TO USER: Carefully read the following legal agreement. BY
DOWNLOADING, INSTALLING, COPYING OR OTHERWISE USING UNICODE INC.'S DATA FILES
("DATA FILES"), AND/OR SOFTWARE ("SOFTWARE"), YOU UNEQUIVOCALLY ACCEPT, AND
AGREE TO BE BOUND BY, ALL OF THE TERMS AND CONDITIONS OF THIS AGREEMENT. IF YOU
DO NOT AGREE, DO NOT DOWNLOAD, INSTALL, COPY, DISTRIBUTE OR USE THE DATA FILES
OR SOFTWARE.

    COPYRIGHT AND PERMISSION NOTICE

    Copyright c 1991-2007 Unicode, Inc. All rights reserved. Distributed under
the Terms of Use in http://www.unicode.org/copyright.html.

    Permission is hereby granted, free of charge, to any person obtaining a copy
of the Unicode data files and any associated documentation (the "Data Files") or
Unicode software and any associated documentation (the "Software") to deal in
the Data Files or Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, and/or sell copies of
the Data Files or Software, and to permit persons to whom the Data Files or
Software are furnished to do so, provided that (a) the above copyright notice(s)
and this permission notice appear with all copies of the Data Files or Software,
(b) both the above copyright notice(s) and this permission notice appear in
associated documentation, and (c) there is clear notice in each modified Data
File or in the Software as well as in the documentation associated with the Data
File(s) or Software that the data or software has been modified.

    THE DATA FILES AND SOFTWARE ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY
KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD
PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR HOLDERS INCLUDED IN THIS
NOTICE BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL
DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING
OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THE DATA FILES OR
SOFTWARE.

    Except as contained in this notice, the name of a copyright holder shall not
be used in advertising or otherwise to promote the sale, use or other dealings
in these Data Files or Software without prior written authorization of the
copyright holder.
*/
