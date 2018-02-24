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


#ifndef __MLE_FONT_MALAYALAM_PRIV_H__
#define __MLE_FONT_MALAYALAM_PRIV_H__
#ifdef __INDIC_FONT__
#ifdef __MLYM_FONT__

#define MLYM_MASK 0x0D00

#define IS_MLYM_RANGE(_char) (_char >= MALAYALAM_S_ANUSVARA && _char <= MALAYALAM_C_CHILLU_K)
//#define IS_MLYM_RA_CHAR(_char) (_char == MALAYALAM_C_RA)
#define IS_MLYM_HALANT_CHAR(_char) (_char == MALAYALAM_S_HALANT)
//#define IS_MLYM_NUKTA_CHAR(_char) (_char == MALAYALAM_S_NUKTA)
//#define IS_MLYM_BINDU_CHAR(_char) (_char == MALAYALAM_S_CHANDRA_BINDU)
#define IS_MLYM_WITH_NUKTA_CHAR(_char) (_char == MALAYALAM_C_RRA)
//#define IS_MLYM_NO_HALF_CHAR(_char) (_char == MALAYALAM_IV_CE)
#define IS_MLYM_DEPVOW_COMPOSING_CHAR(_char) ((_char >= MALAYALAM_DV_U && _char <= MALAYALAM_DV_AI) || _char == MALAYALAM_S_HALANT)
//#define IS_MLYM_DEPVOW_LONG_DOWN_CHAR(_char) (_char == MALAYALAM_C_HA)
//#define IS_MLYM_DEPVOW_SMALL_CHAR(_char) (_char == MALAYALAM_C_RA)
#define IS_MLYM_PREBASE_CHAR(_char) (_char == MALAYALAM_C_RA) //|| (_char == MALAYALAM_C_RRA), should RRA char be a prebase character? FIX Me!
#define IS_MLYM_BELOW_BASE_FORM(_char) (_char == MALAYALAM_C_LA)
#define IS_MLYM_POST_BASE_FORM(_char) ((_char == MALAYALAM_C_YA) || (_char == MALAYALAM_C_VA) || (_char == MALAYALAM_C_RA))
#define IS_MLYM_POST_BELOW_BASE_FORM(_char) ((_char == MALAYALAM_C_YA) || (_char == MALAYALAM_C_VA) || (_char == MALAYALAM_C_LA) || (_char == MALAYALAM_C_RA))

typedef enum
{       
    /* Various signs*/
    MALAYALAM_S_ANUSVARA      =0xD02,
    MALAYALAM_S_VISARGA          =0xD03,

    /* Independent vowels */
    MALAYALAM_IV_A           =0xD05,
    MALAYALAM_IV_AA         =0xD06,
    MALAYALAM_IV_I           =0xD07,
    MALAYALAM_IV_II           =0xD08,
    MALAYALAM_IV_U           =0xD09,        
    MALAYALAM_IV_UU      =0xD0a,
    MALAYALAM_IV_VR          =0xD0b,
    MALAYALAM_IV_VL          =0xD0c,
    MALAYALAM_IV_E           =0xD0e,
    MALAYALAM_IV_EE          =0xD0f,
    MALAYALAM_IV_AI          =0xD10,
    MALAYALAM_IV_O           =0xD12,
    MALAYALAM_IV_OO          =0xD13,
    MALAYALAM_IV_AU          =0xD14,
    
    /* Consonants */   
    MALAYALAM_C_KA           =0xD15,
    MALAYALAM_C_KHA      =0xD16,
    MALAYALAM_C_GA           =0xD17,
    MALAYALAM_C_GHA      =0xD18,
    MALAYALAM_C_NGA      =0xD19,
    MALAYALAM_C_CA           =0xD1a,
    MALAYALAM_C_CHA      =0xD1b,
    MALAYALAM_C_JA           =0xD1c,
    MALAYALAM_C_JHA      =0xD1d,
    MALAYALAM_C_NYA      =0xD1e,
    MALAYALAM_C_TTA      =0xD1f,
    MALAYALAM_C_TTHA     =0xD20,
    MALAYALAM_C_DDA      =0xD21,
    MALAYALAM_C_DDHA =0xD22,
    MALAYALAM_C_NNA      =0xD23,
    MALAYALAM_C_TA           =0xD24,
    MALAYALAM_C_THA      =0xD25,
    MALAYALAM_C_DA           =0xD26,
    MALAYALAM_C_DHA      =0xD27,
    MALAYALAM_C_NA           =0xD28,
    MALAYALAM_C_NNNA        =0xD29,
    MALAYALAM_C_PA           =0xD2a,
    MALAYALAM_C_PHA      =0xD2b,
    MALAYALAM_C_BA           =0xD2c,
    MALAYALAM_C_BHA      =0xD2d,
    MALAYALAM_C_MA       =0xD2e,
    MALAYALAM_C_YA           =0xD2f,
    MALAYALAM_C_RA           =0xD30,
    MALAYALAM_C_RRA          =0xD31,
    MALAYALAM_C_LA           =0xD32,
    MALAYALAM_C_LLA      =0xD33,
    MALAYALAM_C_LLLA      =0xD34,
    MALAYALAM_C_VA           =0xD35,
    MALAYALAM_C_SHA      =0xD36,
    MALAYALAM_C_SSA      =0xD37,
    MALAYALAM_C_SA           =0xD38,
    MALAYALAM_C_HA           =0xD39,
    MALAYALAM_C_TTTA         =0xD3a,
    
    /* Various signs */
    MALAYALAM_S_AVAGRAHA  =0xD3d,
    
    /* Dependent vowel signs */
    MALAYALAM_DV_AA          =0xD3e,
    MALAYALAM_DV_I               =0xD3f,
    MALAYALAM_DV_II             =0xD40,
    MALAYALAM_DV_U               =0xD41,
    MALAYALAM_DV_UU          =0xD42,
    MALAYALAM_DV_VR          =0xD43,
    MALAYALAM_DV_VRR         =0xD44,
    MALAYALAM_DV_E               =0xD46,
    MALAYALAM_DV_EE              =0xD47,
    MALAYALAM_DV_AI          =0xD48,
    
    MALAYALAM_DV_O           =0xD4a,
    MALAYALAM_DV_OO              =0xD4b,
    MALAYALAM_DV_AU          =0xD4c,
    
    /* Virama */
    MALAYALAM_S_HALANT       =0xD4d,
    
    MALAYALAM_S_DR           =0xD4e,

    MALAYALAM_AD_AU           =0xD57,
    
    /*Additional vowels for Sanskrit*/
    MALAYALAM_C_VRR          =0xD60,
    MALAYALAM_C_VLL          =0xD61,
    
    MALAYALAM_DV_VL               =0xD62,
    MALAYALAM_DV_VLL                 =0xD63,
    
    /* Digits */
    MALAYALAM_D_ZERO             =0xD66,
    MALAYALAM_D_ONE              =0xD67,
    MALAYALAM_D_TWO              =0xD68,
    MALAYALAM_D_THREE            =0xD69,
    MALAYALAM_D_FOUR             =0xD6a,
    MALAYALAM_D_FIVE             =0xD6b,
    MALAYALAM_D_SIX              =0xD6c,
    MALAYALAM_D_SEVEN            =0xD6d,
    MALAYALAM_D_EIGHT            =0xD6e,
    MALAYALAM_D_NINE             =0xD6f,
    
    /* Malayalam-specific additions */
    MALAYALAM_N_TEN             =0xD70,
    MALAYALAM_N_HUNDRED            =0xD71,
    MALAYALAM_N_THOUSAND           =0xD72,
    
    MALAYALAM_F_QUARTER           =0xD73,
    MALAYALAM_F_HALF                   =0xD74,
    MALAYALAM_F_THREE_QUARTERS  =0xD75,
    
    MALAYALAM_S_DM                  =0xD79,
    
    /* Chillu letters */
    MALAYALAM_C_CHILLU_NN       =0xD7a,
    MALAYALAM_C_CHILLU_N            =0xD7b,
    MALAYALAM_C_CHILLU_RR       =0xD7c,
    MALAYALAM_C_CHILLU_L            =0xD7d,
    MALAYALAM_C_CHILLU_LL           =0xD7e,
    MALAYALAM_C_CHILLU_K            =0xD7f
    
}MalayalamChar_e;

#endif //__MLYM_FONT__
#endif //__INDIC_FONT__
#endif /* __MLE_FONT_MALAYALAM_PRIV_H__ */
