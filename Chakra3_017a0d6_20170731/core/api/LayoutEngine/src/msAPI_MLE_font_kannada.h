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


#ifndef __MLE_FONT_KANNADA_H__
#define __MLE_FONT_KANNADA_H__
#ifdef __INDIC_FONT__
#ifdef __KNDA_FONT__

#define KANNADA_MASK 0x0C80

#define IS_KANNADA_RANGE(_char) (_char >= KANNADA_S_ANUSVARA && _char <= KANNADA_D_NINE)
#define IS_KANNADA_HALANT_CHAR(_char) (_char == KANNADA_S_HALANT)
#define IS_KANNADA_RA_CHAR(_char) (_char == KANNADA_C_RA)
//#define IS_KANNADA_BINDU_CHAR(_char) (_char == KANNADA_S_CHANDRA_BINDU)
#define IS_KANNADA_NUKTA_CHAR(_char) (_char == KANNADA_S_NUKTA)
#define IS_KANNADA_CONSONANT(_char) ((_char  >= KANNADA_C_KA && _char <= KANNADA_C_HA) || _char == KANNADA_C_LLLA )
#define IS_KANNADA_DEPVOW_COMPOSING_CHAR(_char) ((_char >= KANNADA_DV_AA && _char <= KANNADA_DV_AU) || _char == KANNADA_S_HALANT)
#define IS_KANNADA_DEPVOW_RIGHT_POS_CHAR(_char) (_char == KANNADA_S_ANUSVARA || _char == KANNADA_S_VISARGA || _char == KANNADA_S_AVAGRAHA \
                                                || _char == KANNADA_DV_VR || _char == KANNADA_DV_VRR || _char == KANNADA_ADV_EE || _char == KANNADA_ADV_AI)
#define IS_KANNADA_DEPVOW_RIGHT_JOINER_CHAR(_char) (_char == KANNADA_DV_AA || _char == KANNADA_DV_U || _char == KANNADA_DV_UU)


typedef enum
{
    /* VARIOUS SIGNS */
    KANNADA_S_ANUSVARA             = 0xc82,
    KANNADA_S_VISARGA              = 0xc83,

    /* INDEPENDENT VOWEL */
    KANNADA_IV_A                   = 0xc85,
    KANNADA_IV_AA                  = 0xc86,
    KANNADA_IV_I                   = 0xc87,
    KANNADA_IV_II                  = 0xc88,
    KANNADA_IV_U                   = 0xc89,
    KANNADA_IV_UU                  = 0xc8a,
    KANNADA_IV_VR                  = 0xc8b,
    KANNADA_IV_VL                  = 0xc8c,
    KANNADA_IV_E                   = 0xc8e,
    KANNADA_IV_EE                  = 0xc8f,
    KANNADA_IV_AI                  = 0xc90,
    KANNADA_IV_O                   = 0xc92,
    KANNADA_IV_OO                  = 0xc93,
    KANNADA_IV_AU                  = 0xc94,

    /*  CONSONANTS  */
    KANNADA_C_KA                   = 0xc95,
    KANNADA_C_KHA                  = 0xc96,
    KANNADA_C_GA                   = 0xc97,
    KANNADA_C_GHA                  = 0xc98,
    KANNADA_C_NGA                  = 0xc99,
    KANNADA_C_CA                   = 0xc9a,
    KANNADA_C_CHA                  = 0xc9b,
    KANNADA_C_JA                   = 0xc9c,
    KANNADA_C_JHA                  = 0xc9d,
    KANNADA_C_NYA                  = 0xc9e,
    KANNADA_C_TTA                  = 0xc9f,
    KANNADA_C_TTHA                 = 0xca0,
    KANNADA_C_DDA                  = 0xca1,
    KANNADA_C_DDHA                 = 0xca2,
    KANNADA_C_NNA                  = 0xca3,
    KANNADA_C_TA                   = 0xca4,
    KANNADA_C_THA                  = 0xca5,
    KANNADA_C_DA                   = 0xca6,
    KANNADA_C_DHA                  = 0xca7,
    KANNADA_C_NA                   = 0xca8,
    KANNADA_C_PA                   = 0xcaa,
    KANNADA_C_PHA                  = 0xcab,
    KANNADA_C_BA                   = 0xcac,
    KANNADA_C_BHA                  = 0xcad,
    KANNADA_C_MA                   = 0xcae,
    KANNADA_C_YA                   = 0xcaf,
    KANNADA_C_RA                   = 0xcb0,
    KANNADA_C_RRA                  = 0xcb1,
    KANNADA_C_LA                   = 0xcb2,
    KANNADA_C_LLA                  = 0xcb3,
    KANNADA_C_VA                   = 0xcb5,
    KANNADA_C_SHA                  = 0xcb6,
    KANNADA_C_SSA                  = 0xcb7,
    KANNADA_C_SA                   = 0xcb8,
    KANNADA_C_HA                   = 0xcb9,

    /* VARIOUS SIGNS */
    KANNADA_S_NUKTA                = 0xcbc,    
    KANNADA_S_AVAGRAHA             = 0xcbd,

    /*  DEPENDENT VOWELS  */
    KANNADA_DV_AA                  = 0xcbe,
    KANNADA_DV_I                   = 0xcbf,
    KANNADA_DV_II                  = 0xcc0,
    KANNADA_DV_U                   = 0xcc1,
    KANNADA_DV_UU                  = 0xcc2,
    KANNADA_DV_VR                  = 0xcc3,
    KANNADA_DV_VRR                 = 0xcc4,
    KANNADA_DV_E                   = 0xcc6,
    KANNADA_DV_EE                  = 0xcc7,
    KANNADA_DV_AI                  = 0xcc8,
    KANNADA_DV_O                   = 0xcca,
    KANNADA_DV_OO                  = 0xccb,
    KANNADA_DV_AU                  = 0xccc,

    /* VIRAMA */
    KANNADA_S_HALANT               = 0xccd,
    
    KANNADA_ADV_EE                 = 0xcd5, /* KANNADA LENGTH MARK */
    KANNADA_ADV_AI                 = 0xcd6, /* KANNADA AI LENGTH MARK */

    /* ADDITIONAL CONSONANTS */
    KANNADA_C_LLLA                 = 0xcde, /* KANNADA LETTER LLLA */

    /* ADDITIONAL VOWELS FOR SANSKRIT */
    KANNADA_IV_VRR                 = 0xce0,
    KANNADA_IV_VLL                 = 0xce1,

    /* DEPENDENT VOWELS */
    KANNADA_DV_VL                  = 0xce2, /* KANNADA VOWEL SIGN VOCALIC L */
    KANNADA_DV_VLL                 = 0xce3, /* KANNADA VOWEL SIGN VOCALIC LL */

    /* RESERVED */
    KANNADA_S_DANDA                = 0xce4,
    KANNADA_S_DDANDA               = 0xce5,
    
    /*  DIGITS  */
    KANNADA_D_ZERO                 = 0xce6,
    KANNADA_D_ONE                  = 0xce7,
    KANNADA_D_TWO                  = 0xce8,
    KANNADA_D_THREE                = 0xce9,
    KANNADA_D_FOUR                 = 0xcea,
    KANNADA_D_FIVE                 = 0xceb,
    KANNADA_D_SIX                  = 0xcec,
    KANNADA_D_SEVEN                = 0xced,
    KANNADA_D_EIGHT                = 0xcee,
    KANNADA_D_NINE                 = 0xcef,

    /* SIGNS USED IN SANSKRIT */
    KANNADA_S_JIH                  = 0xcf1,
    KANNADA_S_UPA                  = 0xcf2
    
}KannadaChar_e;

BOOLEAN msAPI_MLE_FontKannadaCharIsBeforeSubscript( U16 u16Character );

#endif //__KANNADA_FONT__
#endif //__INDIC_FONT__
#endif /* __MLE_FONT_KANNADA_H__ */
