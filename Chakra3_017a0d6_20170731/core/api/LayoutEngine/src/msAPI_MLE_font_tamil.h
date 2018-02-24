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


#ifndef __MSAPI_MLE_FONT_TAMIL_H__
#define __MSAPI_MLE_FONT_TAMIL_H__
#ifdef __INDIC_FONT__
#ifdef __TAMIL_FONT__


#define TAMIL_MASK 0x0B80

#define IS_TAMIL_RANGE(_char) (_char >= TAMIL_S_ANUSVARA && _char <= TAMIL_OS_NUMERNAL)
#define IS_TAMIL_HALANT_CHAR(_char) (_char == TAMIL_S_HALANT)
//#define IS_TAMIL_RA_CHAR(_char) (_char == TAMIL_C_RA)
//#define IS_TAMIL_NUKTA_CHAR(_char) (_char == BENGALI_S_NUKTA)
//#define IS_TAMIL_BINDU_CHAR(_char) (_char == BENGALI_S_CHANDRA_BINDU)
//#define IS_TAMIL_POST_BASE_CON(_char) (_char == TAMIL_C_YA)

typedef enum
{
    /* VARIOUS SIGNS + INDEPENDENT VOWEL */
    TAMIL_S_ANUSVARA = 0xb82,
    TAMIL_S_VISARGA = 0xb83,
    TAMIL_IV_A = 0xb85,
    TAMIL_IV_AA = 0xb86,
    TAMIL_IV_I = 0xb87,
    TAMIL_IV_II = 0xb88,
    TAMIL_IV_U = 0xb89,
    TAMIL_IV_UU = 0xb8a,

    TAMIL_IV_E = 0xb8e,
    TAMIL_IV_EE = 0xb8f,
    TAMIL_IV_AI = 0xb90,
    TAMIL_IV_O = 0xb92,
    TAMIL_IV_OO = 0xb93,
    TAMIL_IV_AU = 0xb94,

    /* CONSONANTS */
    TAMIL_C_KA = 0xb95,
    TAMIL_C_NGA = 0xb99,
    TAMIL_C_CHA = 0xb9a,
    TAMIL_C_JA = 0xb9c,
    TAMIL_C_NYA = 0xb9e,
    TAMIL_C_TTA = 0xb9f,
    TAMIL_C_NNA = 0xba3,
    TAMIL_C_TA = 0xba4,
    TAMIL_C_NA = 0xba8,
    TAMIL_C_NNNA = 0xba9,
    TAMIL_C_PA = 0xbaa,
    TAMIL_C_MA = 0xbae,
    TAMIL_C_YA = 0xbaf,
    TAMIL_C_RA = 0xbb0,
    TAMIL_C_RRA = 0xbb1,
    TAMIL_C_LA = 0xbb2,
    TAMIL_C_LLA = 0xbb3,
    TAMIL_C_LLLA = 0xbb4,
    TAMIL_C_VA = 0xbb5,
    TAMIL_C_SHA = 0xbb6,
    TAMIL_C_SSA = 0xbb7,
    TAMIL_C_SA = 0xbb8,
    TAMIL_C_HA = 0xbb9,

    /* DEPENDENT VOWELS */
    TAMIL_DV_AA = 0xbbe,
    TAMIL_DV_I = 0xbbf,
    TAMIL_DV_II = 0xbc0,
    TAMIL_DV_U = 0xbc1,
    TAMIL_DV_UU = 0xbc2,
    TAMIL_DV_E = 0xbc6,
    TAMIL_DV_EE = 0xbc7,
    TAMIL_DV_AI = 0xbc8,
    TAMIL_DV_O = 0xbca,
    TAMIL_DV_OO = 0xbcb,
    TAMIL_DV_AU = 0xbcc,

    /* SIGNS */
    TAMIL_S_HALANT = 0xbcd,

    /* APPEND DEPENDENT VOWEL */
    TAMIL_AD_AU = 0xbd7,

    TAMIL_S_DANDA = 0xbe4,
    TAMIL_S_DDANDA = 0xbe5,
    /* DIGITS */
    TAMIL_D_ZERO = 0xbe6,
    TAMIL_D_ONE = 0xbe7,
    TAMIL_D_TWO = 0xbe8,
    TAMIL_D_THREE = 0xbe9,
    TAMIL_D_FOUR = 0xbea,
    TAMIL_D_FIVE = 0xbeb,
    TAMIL_D_SIX = 0xbec,
    TAMIL_D_SEVEN = 0xbed,
    TAMIL_D_EIGHT = 0xbee,
    TAMIL_D_NINE = 0xbef,

    /* TAMIL NUMERICS */
    TAMIL_D_TEN = 0xbf0,
    TAMIL_D_HUNDRED = 0xbf1,
    TAMIL_D_THOUSAND = 0xbf2,

    /* TAMIL SYMBOLS */
    TAMIL_OS_DAY = 0xbf3,
    TAMIL_OS_MONTH = 0xbf4,
    TAMIL_OS_YEAR = 0xbf5,
    TAMIL_OS_DEBIT = 0xbf6,
    TAMIL_OS_CREDIT = 0xbf7,
    TAMIL_OS_ABOVE = 0xbf8,

    /* CURRENCY SYMBOL */
    TAMIL_OS_RUPEE = 0xbf9,

    /* TAMIL SYMBOLS */
    TAMIL_OS_NUMERNAL = 0xbfa
} tamil_characters_enum;

#endif //__INDIC_FONT__
#endif //__TAMIL_FONT__
#endif /* __MSAPI_MLE_FONT_TAMIL_H__ */
