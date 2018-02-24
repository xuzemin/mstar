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


#ifndef __MLE_FONT_TELUGU_H__
#define __MLE_FONT_TELUGU_H__
#ifdef __INDIC_FONT__
#ifdef __TELUGU_FONT__

#define TELUGU_MASK 0x0C00

#define IS_TELUGU_RANGE(_char) (_char >= TELUGU_S_CHANDRA_BINDU && _char <= TELUGU_D_NINE)
#define IS_TELUGU_HALANT_CHAR(_char) (_char == TELUGU_S_HALANT)
#define IS_TELUGU_RA_CHAR(_char) (_char == TELUGU_C_RA)
#define IS_TELUGU_BINDU_CHAR(_char) (_char == TELUGU_S_CHANDRA_BINDU)
#define IS_TELUGU_CONSONANT(_char) (_char  >= TELUGU_C_KA && _char <= TELUGU_C_HA )
#define IS_TELUGU_DEPVOW_COMPOSING_CHAR(_char) ((_char >= TELUGU_DV_AA && _char <= TELUGU_DV_AU) || _char == TELUGU_S_HALANT)
#define IS_TELUGU_DEPVOW_RIGHT_POS_CHAR(_char) (_char == TELUGU_DV_VR || _char == TELUGU_DV_VRR)
#define IS_TELUGU_DEPVOW_RIGHT_JOINER_CHAR(_char) (_char == TELUGU_DV_AA || _char == TELUGU_DV_U || _char == TELUGU_DV_UU)

typedef enum
{
    /* VARIOUS SIGNS */
    TELUGU_S_CHANDRA_BINDU        = 0xc01,
    TELUGU_S_ANUSVARA             = 0xc02,
    TELUGU_S_VISARGA              = 0xc03,

    /* INDEPENDENT VOWEL */
    TELUGU_IV_A                   = 0xc05,
    TELUGU_IV_AA                  = 0xc06,
    TELUGU_IV_I                   = 0xc07,
    TELUGU_IV_II                  = 0xc08,
    TELUGU_IV_U                   = 0xc09,
    TELUGU_IV_UU                  = 0xc0a,
    TELUGU_IV_VR                  = 0xc0b,
    TELUGU_IV_VL                  = 0xc0c,
    TELUGU_IV_E                   = 0xc0e,
    TELUGU_IV_EE                  = 0xc0f,
    TELUGU_IV_AI                  = 0xc10,
    TELUGU_IV_O                   = 0xc12,
    TELUGU_IV_OO                  = 0xc13,
    TELUGU_IV_AU                  = 0xc14,

    /*  CONSONANTS  */
    TELUGU_C_KA                   = 0xc15,
    TELUGU_C_KHA                  = 0xc16,
    TELUGU_C_GA                   = 0xc17,
    TELUGU_C_GHA                  = 0xc18,
    TELUGU_C_NGA                  = 0xc19,
    TELUGU_C_CA                   = 0xc1a,
    TELUGU_C_CHA                  = 0xc1b,
    TELUGU_C_JA                   = 0xc1c,
    TELUGU_C_JHA                  = 0xc1d,
    TELUGU_C_NYA                  = 0xc1e,
    TELUGU_C_TTA                  = 0xc1f,
    TELUGU_C_TTHA                 = 0xc20,
    TELUGU_C_DDA                  = 0xc21,
    TELUGU_C_DDHA                 = 0xc22,
    TELUGU_C_NNA                  = 0xc23,
    TELUGU_C_TA                   = 0xc24,
    TELUGU_C_THA                  = 0xc25,
    TELUGU_C_DA                   = 0xc26,
    TELUGU_C_DHA                  = 0xc27,
    TELUGU_C_NA                   = 0xc28,
    TELUGU_C_PA                   = 0xc2a,
    TELUGU_C_PHA                  = 0xc2b,
    TELUGU_C_BA                   = 0xc2c,
    TELUGU_C_BHA                  = 0xc2d,
    TELUGU_C_MA                   = 0xc2e,
    TELUGU_C_YA                   = 0xc2f,
    TELUGU_C_RA                   = 0xc30,
    TELUGU_C_RRA                  = 0xc31,
    TELUGU_C_LA                   = 0xc32,
    TELUGU_C_LLA                  = 0xc33,
    TELUGU_C_VA                   = 0xc35,
    TELUGU_C_SHA                  = 0xc36,
    TELUGU_C_SSA                  = 0xc37,
    TELUGU_C_SA                   = 0xc38,
    TELUGU_C_HA                   = 0xc39,

    /*  DEPENDENT VOWELS  */
    TELUGU_DV_AA                  = 0xc3e,
    TELUGU_DV_I                   = 0xc3f,
    TELUGU_DV_II                  = 0xc40,
    TELUGU_DV_U                   = 0xc41,
    TELUGU_DV_UU                  = 0xc42,
    TELUGU_DV_VR                  = 0xc43,
    TELUGU_DV_VRR                 = 0xc44,
    TELUGU_DV_E                   = 0xc46,
    TELUGU_DV_EE                  = 0xc47,
    TELUGU_DV_AI                  = 0xc48,
    TELUGU_DV_O                   = 0xc4a,
    TELUGU_DV_OO                  = 0xc4b,
    TELUGU_DV_AU                  = 0xc4c,
    TELUGU_S_HALANT               = 0xc4d,
    TELUGU_ADV_EE                 = 0xc55,
    TELUGU_ADV_AI                 = 0xc56,
    
    TELUGU_IV_VRR                 = 0xc60,
    TELUGU_IV_VLL                 = 0xc61,

    TELUGU_S_DANDA                = 0xc64,
    TELUGU_S_DDANDA               = 0xc65,
    
    /*  DIGITS  */
    TELUGU_D_ZERO                 = 0xc66,
    TELUGU_D_ONE                  = 0xc67,
    TELUGU_D_TWO                  = 0xc68,
    TELUGU_D_THREE                = 0xc69,
    TELUGU_D_FOUR                 = 0xc6a,
    TELUGU_D_FIVE                 = 0xc6b,
    TELUGU_D_SIX                  = 0xc6c,
    TELUGU_D_SEVEN                = 0xc6d,
    TELUGU_D_EIGHT                = 0xc6e,
    TELUGU_D_NINE                 = 0xc6f
}TeluguChar_e;

#endif //__TELUGU_FONT__
#endif //__INDIC_FONT__
#endif /* __MLE_FONT_TELUGU_H__ */
