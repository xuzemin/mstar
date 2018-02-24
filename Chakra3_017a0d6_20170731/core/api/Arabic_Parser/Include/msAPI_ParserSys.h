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

#ifndef __PARSERSYS_H__
#define __PARSERSYS_H__


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "datatype.h"

typedef unsigned char  UBool;
//typedef S32 UChar32;

#define     SUPPORT_DIGITS_CONVERT  0

#if SUPPORT_DIGITS_CONVERT

typedef struct UTrie {
    U16 *index;
    U32 *data32; /* NULL if 16b data is used via index */

    /**
     * This function is not used in _FROM_LEAD, _FROM_BMP, and _FROM_OFFSET_TRAIL macros.
     * If convenience macros like _GET16 or _NEXT32 are used, this function must be set.
     *
     * utrie_unserialize() sets a default function which simply returns
     * the lead surrogate's value itself - which is the inverse of the default
     * folding function used by utrie_serialize().
     *
     * @see UTrieGetFoldingOffset
     */
//  UTrieGetFoldingOffset *getFoldingOffset;

    S32 indexLength, dataLength;
    S32 initialValue;
    UBool isLatin1Linear;
} UTrie;

struct UBiDiProps {
//    UDataMemory *mem;
     S32 *indexes;
     S32 *mirrors;
     U8 *jgArray;

    UTrie trie;
//  U8 formatVersion[4];
};
#endif

/*===========================================================================*/
/* S32 */
/*===========================================================================*/

/**
 * Error code to replace exception handling, so that the code is compatible with all C++ compilers,
 * and to use the same mechanism for C and C++.
 *
 * \par
 * ICU functions that take a reference (C++) or a pointer (C) to a S32
 * first test if(U_FAILURE(errorCode)) { return immediately; }
 * so that in a chain of such functions the first one that sets an error code
 * causes the following ones to not perform any operations.
 *
 * \par
 * Error codes should be tested using U_FAILURE() and U_SUCCESS().
 * @stable ICU 2.0
 */
//typedef enum S32 {
    /* The ordering of U_ERROR_INFO_START Vs U_USING_FALLBACK_WARNING looks weird
     * and is that way because VC++ debugger displays first encountered constant,
     * which is not the what the code is used for
     */

#define    U_USING_FALLBACK_WARNING   (-128)   /**< A resource bundle lookup returned a fallback result (not an error) */

#define    U_ERROR_WARNING_START      (-128)   /**< Start of information results (semantically successful) */

#define    U_USING_DEFAULT_WARNING    (-127)   /**< A resource bundle lookup returned a result from the root locale (not an error) */

#define    U_SAFECLONE_ALLOCATED_WARNING  (-126) /**< A SafeClone operation required allocating memory (informational only) */

#define    U_STATE_OLD_WARNING        (-125)   /**< ICU has to use compatibility layer to construct the service. Expect performance/memory usage degradation. Consider upgrading */

#define    U_STRING_NOT_TERMINATED_WARNING  (-124)  /**< An output string could not be NUL-terminated because output length==destCapacity. */

#define    U_SORT_KEY_TOO_SHORT_WARNING  (-123) /**< Number of levels requested in getBound is higher than the number of levels in the sort key */

#define    U_AMBIGUOUS_ALIAS_WARNING  (-122)   /**< This converter alias can go to different converter implementations */

#define    U_DIFFERENT_UCA_VERSION  (-121)     /**< ucol_open encountered a mismatch between UCA version and collator image version, so the collator was constructed from rules. No impact to further function */

#define    U_ERROR_WARNING_LIMIT        (-120)     /**< This must always be the last warning value to indicate the limit for S32 warnings (last warning code +1) */


#define    U_ZERO_ERROR                0     /**< No error, no warning. */

#define    U_ILLEGAL_ARGUMENT_ERROR    1     /**< Start of codes indicating failure */
#define    U_MISSING_RESOURCE_ERROR    2     /**< The requested resource cannot be found */
#define    U_INVALID_FORMAT_ERROR      3     /**< Data format is not what is expected */
#define    U_FILE_ACCESS_ERROR         4     /**< The requested file cannot be found */
#define    U_INTERNAL_PROGRAM_ERROR    5     /**< Indicates a bug in the library code */
#define    U_MESSAGE_PARSE_ERROR       6     /**< Unable to parse a message (message format) */
#define    U_MEMORY_ALLOCATION_ERROR   7     /**< Memory allocation error */
#define    U_INDEX_OUTOFBOUNDS_ERROR   8     /**< Trying to access the index that is out of bounds */
#define    U_PARSE_ERROR               9     /**< Equivalent to Java ParseException */
#define    U_INVALID_CHAR_FOUND       10     /**< Character conversion: Unmappable input sequence. In other APIs: Invalid character. */
#define    U_TRUNCATED_CHAR_FOUND     11     /**< Character conversion: Incomplete input sequence. */
#define    U_ILLEGAL_CHAR_FOUND       12     /**< Character conversion: Illegal input sequence/combination of input units. */
#define    U_INVALID_TABLE_FORMAT     13     /**< Conversion table file found but corrupted */
#define    U_INVALID_TABLE_FILE       14     /**< Conversion table file not found */
#define    U_BUFFER_OVERFLOW_ERROR    15     /**< A result would not fit in the supplied buffer */
#define    U_UNSUPPORTED_ERROR        16     /**< Requested operation not supported in current context */
#define    U_RESOURCE_TYPE_MISMATCH   17     /**< an operation is requested over a resource that does not support it */
#define    U_ILLEGAL_ESCAPE_SEQUENCE  18     /**< ISO-2022 illlegal escape sequence */
#define    U_UNSUPPORTED_ESCAPE_SEQUENCE  19 /**< ISO-2022 unsupported escape sequence */
#define    U_NO_SPACE_AVAILABLE       20     /**< No space available for in-buffer expansion for Arabic shaping */
#define    U_CE_NOT_FOUND_ERROR       21     /**< Currently used only while setting variable top but can be used generally */
#define    U_PRIMARY_TOO_LONG_ERROR   22     /**< User tried to set variable top to a primary that is longer than two bytes */
#define    U_STATE_TOO_OLD_ERROR      23     /**< ICU cannot construct a service from this state as it is no longer supported */
#define    U_TOO_MANY_ALIASES_ERROR   24     /**< There are too many aliases in the path to the requested resource.
                                             It is very possible that a circular alias definition has occured */
#define    U_ENUM_OUT_OF_SYNC_ERROR   25     /**< UEnumeration out of sync with underlying collection */
#define    U_INVARIANT_CONVERSION_ERROR  26  /**< Unable to convert a U16* string to char* with the invariant converter. */
#define    U_INVALID_STATE_ERROR      27     /**< Requested operation can not be completed with ICU in its current state */
#define    U_COLLATOR_VERSION_MISMATCH  28   /**< Collator version is not compatible with the base version */
#define    U_USELESS_COLLATOR_ERROR   29     /**< Collator is options only and no base is specified */
#define    U_NO_WRITE_PERMISSION      30     /**< Attempt to modify read-only or constant data. */

#define    U_STANDARD_ERROR_LIMIT           31     /**< This must always be the last value to indicate the limit for standard errors */
    /*
     * the error code range 0x10000 0x10100 are reserved for Transliterator
     */
#define    U_BAD_VARIABLE_DEFINITION    0x10000L    /**< Missing '$' or duplicate variable name */
#define    U_PARSE_ERROR_START  0x10000L    /**< Start of Transliterator errors */
#define    U_MALFORMED_RULE         0x10001L    /**< Elements of a rule are misplaced */
#define    U_MALFORMED_SET      0x10002L    /**< A UnicodeSet pattern is invalid*/
#define    U_MALFORMED_SYMBOL_REFERENCE 0x10003L     /**< UNUSED as of ICU 2.4 */
#define    U_MALFORMED_UNICODE_ESCAPE   0x10004L    /**< A Unicode escape pattern is invalid*/
#define    U_MALFORMED_VARIABLE_DEFINITION  0x10005L  /**< A variable definition is invalid */
#define    U_MALFORMED_VARIABLE_REFERENCE   0x10006L    /**< A variable reference is invalid */
#define    U_MISMATCHED_SEGMENT_DELIMITERS  0x10007L    /**< UNUSED as of ICU 2.4 */
#define    U_MISPLACED_ANCHOR_START         0x10008L    /**< A start anchor appears at an illegal position */
#define    U_MISPLACED_CURSOR_OFFSET        0x10009L    /**< A cursor offset occurs at an illegal position */
#define    U_MISPLACED_QUANTIFIER           0x1000AL    /**< A quantifier appears after a segment close delimiter */
#define    U_MISSING_OPERATOR               0x1000BL    /**< A rule contains no operator */
#define    U_MISSING_SEGMENT_CLOSE          0x1000CL    /**< UNUSED as of ICU 2.4 */
#define    U_MULTIPLE_ANTE_CONTEXTS         0x1000DL    /**< More than one ante context */
#define    U_MULTIPLE_CURSORS               0x1000EL    /**< More than one cursor */
#define    U_MULTIPLE_POST_CONTEXTS         0x1000FL    /**< More than one post context */
#define    U_TRAILING_BACKSLASH             0x10010L    /**< A dangling backslash */
#define    U_UNDEFINED_SEGMENT_REFERENCE    0x10011L    /**< A segment reference does not correspond to a defined segment */
#define    U_UNDEFINED_VARIABLE             0x10012L    /**< A variable reference does not correspond to a defined variable */
#define    U_UNQUOTED_SPECIAL               0x10013L    /**< A special character was not quoted or escaped */
#define    U_UNTERMINATED_QUOTE             0x10014L    /**< A closing single quote is missing */
#define    U_RULE_MASK_ERROR                0x10015L    /**< A rule is hidden by an earlier more general rule */
#define    U_MISPLACED_COMPOUND_FILTER      0x10016L    /**< A compound filter is in an invalid location */
#define    U_MULTIPLE_COMPOUND_FILTERS      0x10017L    /**< More than one compound filter */
#define    U_INVALID_RBT_SYNTAX             0x10018L    /**< A "::id" rule was passed to the RuleBasedTransliterator parser */
#define    U_INVALID_PROPERTY_PATTERN       0x10019L    /**< UNUSED as of ICU 2.4 */
#define    U_MALFORMED_PRAGMA               0x1001AL    /**< A 'use' pragma is invlalid */
#define    U_UNCLOSED_SEGMENT               0x1001BL    /**< A closing ')' is missing */
#define    U_ILLEGAL_CHAR_IN_SEGMENT        0x1001CL    /**< UNUSED as of ICU 2.4 */
#define    U_VARIABLE_RANGE_EXHAUSTED       0x1001DL    /**< Too many stand-ins generated for the given variable range */
#define    U_VARIABLE_RANGE_OVERLAP         0x1001EL    /**< The variable range overlaps characters used in rules */
#define    U_ILLEGAL_CHARACTER              0x1001FL    /**< A special character is outside its allowed context */
#define    U_INTERNAL_TRANSLITERATOR_ERROR  0x10020L    /**< Internal transliterator system error */
#define    U_INVALID_ID                     0x10021L    /**< A "::id" rule specifies an unknown transliterator */
#define    U_INVALID_FUNCTION               0x10022L    /**< A "&fn()" rule specifies an unknown transliterator */
#define    U_PARSE_ERROR_LIMIT              0x10023L    /**< The limit for Transliterator errors */

    /*
     * the error code range 0x10100 0x10200 are reserved for formatting API parsing error
     */
#define    U_UNEXPECTED_TOKEN                               0x10100L  /**< Syntax error in format pattern */
#define    U_FMT_PARSE_ERROR_START                  0x10100L  /**< Start of format library errors */
#define    U_MULTIPLE_DECIMAL_SEPARATORS    0x10101L    /**< More than one decimal separator in number pattern */
#define    U_MULTIPLE_DECIMAL_SEPERATORS  U_MULTIPLE_DECIMAL_SEPARATORS /**< Typo: kept for backward compatibility. Use U_MULTIPLE_DECIMAL_SEPARATORS */
#define    U_MULTIPLE_EXPONENTIAL_SYMBOLS   0x10102L    /**< More than one exponent symbol in number pattern */
#define    U_MALFORMED_EXPONENTIAL_PATTERN  0x10103L    /**< Grouping symbol in exponent pattern */
#define    U_MULTIPLE_PERCENT_SYMBOLS       0x10104L    /**< More than one percent symbol in number pattern */
#define    U_MULTIPLE_PERMILL_SYMBOLS       0x10105L    /**< More than one permill symbol in number pattern */
#define    U_MULTIPLE_PAD_SPECIFIERS        0x10106L    /**< More than one pad symbol in number pattern */
#define    U_PATTERN_SYNTAX_ERROR           0x10107L    /**< Syntax error in format pattern */
#define    U_ILLEGAL_PAD_POSITION           0x10108L    /**< Pad symbol misplaced in number pattern */
#define    U_UNMATCHED_BRACES               0x10109L    /**< Braces do not match in message pattern */
#define    U_UNSUPPORTED_PROPERTY           0x1010AL    /**< UNUSED as of ICU 2.4 */
#define    U_UNSUPPORTED_ATTRIBUTE          0x1010BL    /**< UNUSED as of ICU 2.4 */
#define    U_ARGUMENT_TYPE_MISMATCH         0x1010CL    /**< Argument name and argument index mismatch in MessageFormat functions */
#define    U_DUPLICATE_KEYWORD              0x1010DL    /**< Duplicate keyword in PluralFormat */
#define    U_UNDEFINED_KEYWORD              0x1010EL    /**< Undefined Pluarl keyword */
#define    U_DEFAULT_KEYWORD_MISSING        0x1010FL    /**< Missing DEFAULT rule in plural rules */
#define    U_FMT_PARSE_ERROR_LIMIT          0x10110L    /**< The limit for format library errors */

    /*
     * the error code range 0x10200 0x102ff are reserved for Break Iterator related error
     */
#define    U_BRK_INTERNAL_ERROR                         0x10200L  /**< An internal error (bug) was detected.             */
#define    U_BRK_ERROR_START                                0x10200L  /**< Start of codes indicating Break Iterator failures */
#define    U_BRK_HEX_DIGITS_EXPECTED        0x10201L  /**< Hex digits expected as part of a escaped char in a rule. */
#define    U_BRK_SEMICOLON_EXPECTED         0x10202L  /**< Missing ';' at the end of a RBBI rule.            */
#define    U_BRK_RULE_SYNTAX                0x10203L  /**< Syntax error in RBBI rule.                        */
#define    U_BRK_UNCLOSED_SET               0x10204L  /**< UnicodeSet witing an RBBI rule missing a closing ']'.  */
#define    U_BRK_ASSIGN_ERROR               0x10205L  /**< Syntax error in RBBI rule assignment statement.   */
#define    U_BRK_VARIABLE_REDFINITION       0x10206L  /**< RBBI rule $Variable redefined.                    */
#define    U_BRK_MISMATCHED_PAREN           0x10207L  /**< Mis-matched parentheses in an RBBI rule.          */
#define    U_BRK_NEW_LINE_IN_QUOTED_STRING  0x10208L  /**< Missing closing quote in an RBBI rule.            */
#define    U_BRK_UNDEFINED_VARIABLE         0x10209L  /**< Use of an undefined $Variable in an RBBI rule.    */
#define    U_BRK_INIT_ERROR                 0x1020AL  /**< Initialization failure.  Probable missing ICU Data. */
#define    U_BRK_RULE_EMPTY_SET             0x1020BL  /**< Rule contains an empty Unicode Set.               */
#define    U_BRK_UNRECOGNIZED_OPTION        0x1020CL  /**< !!option in RBBI rules not recognized.            */
#define    U_BRK_MALFORMED_RULE_TAG         0x1020DL  /**< The {nnn} tag on a rule is mal formed             */
#define    U_BRK_ERROR_LIMIT                0x1020EL  /**< This must always be the last value to indicate the limit for Break Iterator failures */
    /*
     * The error codes in the range 0x10300-0x103ff are reserved for regular expression related errrs
     */
#define    U_REGEX_INTERNAL_ERROR                       0x10300L    /**< An internal error (bug) was detected.              */
#define    U_REGEX_ERROR_START                          0x10300L    /**< Start of codes indicating Regexp failures          */
#define    U_REGEX_RULE_SYNTAX              0x10301L    /**< Syntax error in regexp pattern.                    */
#define    U_REGEX_INVALID_STATE            0x10302L    /**< RegexMatcher in invalid state for requested operation */
#define    U_REGEX_BAD_ESCAPE_SEQUENCE      0x10303L    /**< Unrecognized backslash escape sequence in pattern  */
#define    U_REGEX_PROPERTY_SYNTAX          0x10304L    /**< Incorrect Unicode property                         */
#define    U_REGEX_UNIMPLEMENTED            0x10305L    /**< Use of regexp feature that is not yet implemented. */
#define    U_REGEX_MISMATCHED_PAREN         0x10306L    /**< Incorrectly nested parentheses in regexp pattern.  */
#define    U_REGEX_NUMBER_TOO_BIG           0x10307L    /**< Decimal number is too large.                       */
#define    U_REGEX_BAD_INTERVAL             0x10308L    /**< Error in {min,max} interval                        */
#define    U_REGEX_MAX_LT_MIN               0x10309L    /**< In {min,max}, max is less than min.                */
#define    U_REGEX_INVALID_BACK_REF         0x1030AL    /**< Back-reference to a non-existent capture group.    */
#define    U_REGEX_INVALID_FLAG             0x1030BL    /**< Invalid value for match mode flags.                */
#define    U_REGEX_LOOK_BEHIND_LIMIT        0x1030CL    /**< Look-Behind pattern matches must have a bounded maximum length.    */
#define    U_REGEX_SET_CONTAINS_STRING      0x1030DL    /**< Regexps cannot have UnicodeSets containing strings.*/
#define    U_REGEX_OCTAL_TOO_BIG            0x1030EL    /**< Octal character constants must be < 0377.         */
#define    U_REGEX_MISSING_CLOSE_BRACKET    0x1030FL    /**< Missing closing bracket on a bracket expression.   */
#define    U_REGEX_INVALID_RANGE            0x10310L    /**< In a character range [x-y], x is greater than y.   */
#define    U_REGEX_STACK_OVERFLOW           0x10311L    /**< Regular expression backtrack stack overflow.       */
#define    U_REGEX_TIME_OUT                 0x10312L    /**< Maximum allowed match time exceeded                */
#define    U_REGEX_STOPPED_BY_CALLER        0x10313L    /**< Matching operation aborted by user callback fn.    */
#define    U_REGEX_ERROR_LIMIT              0x10314L    /**< This must always be the last value to indicate the limit for regexp errors */
    /*
     * The error code in the range 0x10400-0x104ff are reserved for IDNA related error codes
     */
#define    U_IDNA_PROHIBITED_ERROR                  0x10400L
#define    U_IDNA_ERROR_START                               0x10400L
#define    U_IDNA_UNASSIGNED_ERROR                  0x10401L
#define    U_IDNA_CHECK_BIDI_ERROR                  0x10402L
#define    U_IDNA_STD3_ASCII_RULES_ERROR        0x10403L
#define    U_IDNA_ACE_PREFIX_ERROR                  0x10404L
#define    U_IDNA_VERIFICATION_ERROR                0x10405L
#define    U_IDNA_LABEL_TOO_LONG_ERROR          0x10406L
#define    U_IDNA_ZERO_LENGTH_LABEL_ERROR       0x10407L
#define    U_IDNA_DOMAIN_NAME_TOO_LONG_ERROR    0x10408L
#define    U_IDNA_ERROR_LIMIT                               0x10409L
    /*
     * Aliases for StringPrep
     */
#define    U_STRINGPREP_PROHIBITED_ERROR  U_IDNA_PROHIBITED_ERROR
#define    U_STRINGPREP_UNASSIGNED_ERROR  U_IDNA_UNASSIGNED_ERROR
#define    U_STRINGPREP_CHECK_BIDI_ERROR  U_IDNA_CHECK_BIDI_ERROR


#define    U_ERROR_LIMIT    U_IDNA_ERROR_LIMIT      /**< This must always be the last value to indicate the limit for S32 (last error code +1) */
//} S32;

/**
 * This specifies the language directional property of a character set.
 * @stable ICU 2.0
 */
typedef enum UCharDirection {
    /** See note !!.  Comments of the form "EN" are read by genpname. */

    /** L @stable ICU 2.0 */
    U_LEFT_TO_RIGHT               = 0,
    /** R @stable ICU 2.0 */
    U_RIGHT_TO_LEFT               = 1,
    /** EN @stable ICU 2.0 */
    U_EUROPEAN_NUMBER             = 2,
    /** ES @stable ICU 2.0 */
    U_EUROPEAN_NUMBER_SEPARATOR   = 3,
    /** ET @stable ICU 2.0 */
    U_EUROPEAN_NUMBER_TERMINATOR  = 4,
    /** AN @stable ICU 2.0 */
    U_ARABIC_NUMBER               = 5,
    /** CS @stable ICU 2.0 */
    U_COMMON_NUMBER_SEPARATOR     = 6,
    /** B @stable ICU 2.0 */
    U_BLOCK_SEPARATOR             = 7,
    /** S @stable ICU 2.0 */
    U_SEGMENT_SEPARATOR           = 8,
    /** WS @stable ICU 2.0 */
    U_WHITE_SPACE_NEUTRAL         = 9,
    /** ON @stable ICU 2.0 */
    U_OTHER_NEUTRAL               = 10,
    /** LRE @stable ICU 2.0 */
    U_LEFT_TO_RIGHT_EMBEDDING     = 11,
    /** LRO @stable ICU 2.0 */
    U_LEFT_TO_RIGHT_OVERRIDE      = 12,
    /** AL @stable ICU 2.0 */
    U_RIGHT_TO_LEFT_ARABIC        = 13,
    /** RLE @stable ICU 2.0 */
    U_RIGHT_TO_LEFT_EMBEDDING     = 14,
    /** RLO @stable ICU 2.0 */
    U_RIGHT_TO_LEFT_OVERRIDE      = 15,
    /** PDF @stable ICU 2.0 */
    U_POP_DIRECTIONAL_FORMAT      = 16,
    /** NSM @stable ICU 2.0 */
    U_DIR_NON_SPACING_MARK        = 17,
    /** BN @stable ICU 2.0 */
    U_BOUNDARY_NEUTRAL            = 18,
    /** @stable ICU 2.0 */
    U_CHAR_DIRECTION_COUNT
} UCharDirection;


/**
 * \file
 *
 * This is a common implementation of a "folded" trie.
 * It is a kind of compressed, serializable table of 16- or 32-bit values associated with
 * Unicode code points (0..0x10ffff).
 *
 * This implementation is optimized for getting values while walking forward
 * through a UTF-16 string.
 * Therefore, the simplest and fastest access macros are the
 * _FROM_LEAD() and _FROM_OFFSET_TRAIL() macros.
 *
 * The _FROM_BMP() macros are a little more complicated; they get values
 * even for lead surrogate code _points_, while the _FROM_LEAD() macros
 * get special "folded" values for lead surrogate code _units_ if
 * there is relevant data associated with them.
 * From such a folded value, an offset needs to be extracted to supply
 * to the _FROM_OFFSET_TRAIL() macros.
 *
 * Most of the more complex (and more convenient) functions/macros call a callback function
 * to get that offset from the folded value for a lead surrogate unit.
 */

/**
 * Trie constants, defining shift widths, index array lengths, etc.
 */
enum {
    /** Shift size for shifting right the input index. 1..9 */
    UTRIE_SHIFT=5,

    /** Number of data values in a stage 2 (data array) block. 2, 4, 8, .., 0x200 */
    UTRIE_DATA_BLOCK_LENGTH=1<<UTRIE_SHIFT,

    /** Mask for getting the lower bits from the input index. */
    UTRIE_MASK=UTRIE_DATA_BLOCK_LENGTH-1,

    /**
     * Lead surrogate code points' index displacement in the index array.
     * 0x10000-0xd800=0x2800
     */
    UTRIE_LEAD_INDEX_DISP=0x2800>>UTRIE_SHIFT,

    /**
     * Shift size for shifting left the index array values.
     * Increases possible data size with 16-bit index values at the cost
     * of compactability.
     * This requires blocks of stage 2 data to be aligned by UTRIE_DATA_GRANULARITY.
     * 0..UTRIE_SHIFT
     */
    UTRIE_INDEX_SHIFT=2,

    /** The alignment size of a stage 2 data block. Also the granularity for compaction. */
    UTRIE_DATA_GRANULARITY=1<<UTRIE_INDEX_SHIFT,

    /** Number of bits of a trail surrogate that are used in index table lookups. */
    UTRIE_SURROGATE_BLOCK_BITS=10-UTRIE_SHIFT,

    /**
     * Number of index (stage 1) entries per lead surrogate.
     * Same as number of index entries for 1024 trail surrogates,
     * ==0x400>>UTRIE_SHIFT
     */
    UTRIE_SURROGATE_BLOCK_COUNT=(1<<UTRIE_SURROGATE_BLOCK_BITS),

    /** Length of the BMP portion of the index (stage 1) array. */
    UTRIE_BMP_INDEX_LENGTH=0x10000>>UTRIE_SHIFT
};

/**
 * Length of the index (stage 1) array before folding.
 * Maximum number of Unicode code points (0x110000) shifted right by UTRIE_SHIFT.
 */
#define UTRIE_MAX_INDEX_LENGTH (0x110000>>UTRIE_SHIFT)

/**
 * Maximum length of the runtime data (stage 2) array.
 * Limited by 16-bit index values that are left-shifted by UTRIE_INDEX_SHIFT.
 */
#define UTRIE_MAX_DATA_LENGTH (0x10000<<UTRIE_INDEX_SHIFT)

/**
 * Maximum length of the build-time data (stage 2) array.
 * The maximum length is 0x110000+UTRIE_DATA_BLOCK_LENGTH+0x400.
 * (Number of Unicode code points + one all-initial-value block +
 *  possible duplicate entries for 1024 lead surrogates.)
 */
#define UTRIE_MAX_BUILD_TIME_DATA_LENGTH (0x110000+UTRIE_DATA_BLOCK_LENGTH+0x400)

/**
 * Number of bytes for a dummy trie.
 * A dummy trie is an empty runtime trie, used when a real data trie cannot
 * be loaded.
 * The number of bytes works for Latin-1-linear tries with 32-bit data
 * (worst case).
 *
 * Calculation:
 *   BMP index + 1 index block for lead surrogate code points +
 *   Latin-1-linear array + 1 data block for lead surrogate code points
 *
 * Latin-1: if(UTRIE_SHIFT<=8) { 256 } else { included in first data block }
 *
 * @see utrie_unserializeDummy
 */
#define UTRIE_DUMMY_SIZE ((UTRIE_BMP_INDEX_LENGTH+UTRIE_SURROGATE_BLOCK_COUNT)*2+(UTRIE_SHIFT<=8?256:UTRIE_DATA_BLOCK_LENGTH)*4+UTRIE_DATA_BLOCK_LENGTH*4)
    
#endif
