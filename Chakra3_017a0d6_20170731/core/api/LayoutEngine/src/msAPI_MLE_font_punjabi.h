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
//    supplied together with third party`s software and the use of MStarPUNJ_AC_RRA
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


#ifndef __MLE_FONT_PUNJABI_PRIV_H__
#define __MLE_FONT_PUNJABI_PRIV_H__
#ifdef __INDIC_FONT__
#ifdef __PUNJ_FONT__

#define PUNJ_MASK 0x0A00

#define IS_PUNJ_RANGE(_char) (_char >= PUNJ_S_ADAK_BINDI && _char <= PUNJ_S_YAKASH)
#define IS_PUNJ_RA_CHAR(_char) (_char == PUNJ_C_RA)
#define IS_PUNJ_HALANT_CHAR(_char) (_char == PUNJ_S_HALANT)
#define IS_PUNJ_NUKTA_CHAR(_char) (_char == PUNJ_S_NUKTA)
#define IS_PUNJ_PSTF_CHAR(_char) (_char == PUNJ_C_YA)
#define IS_PUNJ_BINDU_CHAR(_char) (_char == PUNJ_S_ADAK_BINDI || _char == PUNJ_S_BINDI)
#define IS_PUNJ_WITH_NUKTA_CHAR(_char)  (_char >= PUNJ_AC_KHHA && _char <= PUNJ_AC_FA)
#define IS_PUNJ_DEPVOW_COMPOSING_CHAR(_char) ((_char >= PUNJ_DV_U && _char <= PUNJ_DV_AU) || _char == PUNJ_S_HALANT)

#define IS_PUNJ_DEPVOW_LONG_DOWN_CHAR(_char) (_char == PUNJ_C_HA)
#define IS_PUNJ_DEPVOW_SMALL_CHAR(_char) (_char == PUNJ_C_RA)

#define IS_PUNJ_BELOW_BASE_FORM(_char) ( (_char == PUNJ_C_RA) || (_char == PUNJ_C_HA) || (_char == PUNJ_C_VA) )
#define IS_PUNJ_POST_BASE_FORM(_char) (_char == PUNJ_C_YA)
#define IS_PUNJ_POST_BELOW_BASE_FORM(_char) ((_char == PUNJ_C_YA) || (_char == PUNJ_C_VA) || (_char == PUNJ_C_HA) || (_char == PUNJ_C_RA))

typedef enum
{       
    /* Various signs*/
    PUNJ_S_ADAK_BINDI=0x0A01,
    PUNJ_S_BINDI        =0xA02,
    PUNJ_S_VISARGA      =0xA03,

    /* Independent vowels */
    PUNJ_IV_A           =0xA05,
    PUNJ_IV_AA          =0xA06,
    PUNJ_IV_I           =0xA07,
    PUNJ_IV_II          =0xA08,         
    PUNJ_IV_U           =0xA09,
    PUNJ_IV_UU          =0xA0a,
    PUNJ_IV_EE           =0xA0f,
    PUNJ_IV_AI          =0xA10,
    PUNJ_IV_OO         =0xA13,
    PUNJ_IV_AU          =0xA14,
    
    /* Consonants */        
    PUNJ_C_KA           =0xA15,
    PUNJ_C_KHA          =0xA16,
    PUNJ_C_GA           =0xA17,
    PUNJ_C_GHA          =0xA18,
    PUNJ_C_NGA          =0xA19,
    PUNJ_C_CA            =0xA1a,
    PUNJ_C_CHA          =0xA1b,
    PUNJ_C_JA           =0xA1c,
    PUNJ_C_JHA          =0xA1d,
    PUNJ_C_NYA          =0xA1e,
    PUNJ_C_TTA          =0xA1f,
    PUNJ_C_TTHA         =0xA20,
    PUNJ_C_DDA          =0xA21,
    PUNJ_C_DDHA         =0xA22,
    PUNJ_C_NNA          =0xA23,
    PUNJ_C_TA           =0xA24,
    PUNJ_C_THA          =0xA25,
    PUNJ_C_DA           =0xA26,
    PUNJ_C_DHA          =0xA27,
    PUNJ_C_NA           =0xA28,
    PUNJ_C_PA           =0xA2a,
    PUNJ_C_PHA          =0xA2b,
    PUNJ_C_BA           =0xA2c,
    PUNJ_C_BHA          =0xA2d,
    PUNJ_C_MA           =0xA2e,
    PUNJ_C_YA           =0xA2f,
    PUNJ_C_RA           =0xA30,
    PUNJ_C_LA           =0xA32,
    PUNJ_C_LLA          =0xA33,
    PUNJ_C_VA           =0xA35,
    PUNJ_C_SHA          =0xA36,
    PUNJ_C_SA           =0xA38,
    PUNJ_C_HA           =0xA39,
    
    /* Various signs */
    PUNJ_S_NUKTA        =0xA3c,
    
    /* Dependent vowel signs */
    PUNJ_DV_AA          =0xA3e,
    PUNJ_DV_I           =0xA3f,
    PUNJ_DV_II          =0xA40,
    PUNJ_DV_U           =0xA41,
    PUNJ_DV_UU          =0xA42,
    PUNJ_DV_EE           =0xA47,
    PUNJ_DV_AI          =0xA48,
    PUNJ_DV_OO          =0xA4b,
    PUNJ_DV_AU          =0xA4c,
    
    /* Various signs */
    PUNJ_S_HALANT       =0xA4d,
    PUNJ_NS_UDAAT       =0xA51,
    
    /* Additional consonants */
    PUNJ_AC_KHHA        =0xA59,
    PUNJ_AC_GHHA        =0xA5a,
    PUNJ_AC_ZA           =0xA5b,
    PUNJ_AC_RRA         =0xA5c,
    PUNJ_AC_FA          =0xA5e,
        
    /* Digits */
    PUNJ_D_ZERO         =0xA66,
    PUNJ_D_ONE          =0xA67,
    PUNJ_D_TWO          =0xA68,
    PUNJ_D_THREE        =0xA69,
    PUNJ_D_FOUR         =0xA6a,
    PUNJ_D_FIVE         =0xA6b,
    PUNJ_D_SIX          =0xA6c,
    PUNJ_D_SEVEN        =0xA6d,
    PUNJ_D_EIGHT        =0xA6e,
    PUNJ_D_NINE         =0xA6f,
    
    /* Gurmukhi-specific additions */
    PUNJ_S_TIPPI         =0xA70,
    PUNJ_S_ADDAK        =0xA71,
    PUNJ_S_IRI               =0xA72,
    PUNJ_S_URA             =0xA73,
    PUNJ_S_ONKAR         =0xA74,
    PUNJ_S_YAKASH        =0xA75
}PunjabiChar_e;

#endif //__PUNJ_FONT__
#endif //__INDIC_FONT__
#endif /* __MLE_FONT_PUNJABI_PRIV_H__ */
