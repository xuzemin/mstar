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


#ifndef __LETYPES_H
#define __LETYPES_H

#include "msAPI_ParserSys.h"

/**
 * Used to represent 16-bit Unicode code points.
 *
 * @deprecated since ICU 2.4. Use LEUnicode16 instead
 */
typedef U16 LEUnicode;

/**
 * A type used for boolean values.
 *
 * @stable ICU 2.4
 */
typedef S8 le_bool;

/**
 * A type used for unsigned, 8-bit integers.
 *
 * @stable ICU 2.4
 */
typedef U8 le_uint8;

/**
 * A type used for unsigned, 16-bit integers.
 *
 * @stable ICU 2.4
 */
typedef U16 le_uint16;

/**
 * A type used for signed, 16-bit integers.
 *
 * @stable ICU 2.4
 */
typedef S16 le_int16;

/**
 * A type used for signed, 32-bit integers.
 *
 * @stable ICU 2.4
 */
typedef S32 le_int32;
/**
 * A type used for unsigned, 32-bit integers.
 *
 * @stable ICU 2.4
 */
typedef U32 le_uint32;


/**
 * Error codes returned by the LayoutEngine.
 *
 * @stable ICU 2.4
 */
enum LEErrorCode {
    /* informational */
    LE_NO_SUBFONT_WARNING          = U_USING_DEFAULT_WARNING, /**< The font does not contain subfonts. */

    /* success */
    LE_NO_ERROR                     = U_ZERO_ERROR, /**< No error, no warning. */

    /* failures */
    LE_ILLEGAL_ARGUMENT_ERROR       = U_ILLEGAL_ARGUMENT_ERROR,  /**< An illegal argument was detected. */
    LE_MEMORY_ALLOCATION_ERROR      = U_MEMORY_ALLOCATION_ERROR, /**< Memory allocation error. */
    LE_INDEX_OUT_OF_BOUNDS_ERROR    = U_INDEX_OUTOFBOUNDS_ERROR, /**< Trying to access an index that is out of bounds. */
    LE_NO_LAYOUT_ERROR              = U_UNSUPPORTED_ERROR,       /**< You must call layoutChars() first. */
    LE_INTERNAL_ERROR               = U_INTERNAL_PROGRAM_ERROR,  /**< An internal error was encountered. */
    LE_FONT_FILE_NOT_FOUND_ERROR    = U_FILE_ACCESS_ERROR,       /**< The requested font file cannot be opened. */
    LE_MISSING_FONT_TABLE_ERROR     = U_MISSING_RESOURCE_ERROR   /**< The requested font table does not exist. */
};

#endif
