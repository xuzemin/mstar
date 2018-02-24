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


#ifndef __MLE_FONT_GUJARATI_PRIV_H__
#define __MLE_FONT_GUJARATI_PRIV_H__
#ifdef __INDIC_FONT__
#ifdef __GUJR_FONT__

#define GUJR_MASK 0x0A80

#define IS_GUJR_RANGE(_char) (_char >= GUJARATI_S_CHANDRA_BINDU && _char <= GUJARATI_C_RUPEE_SIGN)
#define IS_GUJR_RA_CHAR(_char) (_char == GUJARATI_C_RA)
#define IS_GUJR_HALANT_CHAR(_char) (_char == GUJARATI_S_HALANT)
#define IS_GUJR_NUKTA_CHAR(_char) (_char == GUJARATI_S_NUKTA)
#define IS_GUJR_BINDU_CHAR(_char) (_char == GUJARATI_S_CHANDRA_BINDU)
//Todo
//#define IS_GUJR_WITH_NUKTA_CHAR(_char) (_char >= GUJARATI_AC_QA && _char <= GUJARATI_AC_YYA)
#define IS_GUJR_NO_HALF_CHAR(_char) (_char == GUJARATI_IV_CE)
#define IS_GUJR_DEPVOW_COMPOSING_CHAR(_char) ((_char >= GUJARATI_DV_U && _char <= GUJARATI_DV_AI) || _char == GUJARATI_S_HALANT)

#define IS_GUJR_DEPVOW_LONG_DOWN_CHAR(_char) (_char == GUJARATI_C_HA)
#define IS_GUJR_DEPVOW_SMALL_CHAR(_char) (_char == GUJARATI_C_RA)

typedef enum
{       
    /* Various signs*/
    GUJARATI_S_CHANDRA_BINDU    =0xA81,
    GUJARATI_S_ANUSVARA      =0xA82,
    GUJARATI_S_VISARGA          =0xA83,

    /* Independent vowels */
    GUJARATI_IV_A           =0xA85,
    GUJARATI_IV_AA         =0xA86,
    GUJARATI_IV_I           =0xA87,
    GUJARATI_IV_II           =0xA88,
    GUJARATI_IV_U           =0xA89,        
    GUJARATI_IV_UU      =0xA8a,
    GUJARATI_IV_VR          =0xA8b,
    GUJARATI_IV_VL          =0xA8c,
    GUJARATI_IV_CE          =0xA8d,
    GUJARATI_IV_E           =0xA8f,
    GUJARATI_IV_AI          =0xA90,
    GUJARATI_IV_CO      =0xA91,
    GUJARATI_IV_O           =0xA93,
    GUJARATI_IV_AU          =0xA94,
    
    /* Consonants */   
    GUJARATI_C_KA           =0xA95,
    GUJARATI_C_KHA      =0xA96,
    GUJARATI_C_GA           =0xA97,
    GUJARATI_C_GHA      =0xA98,
    GUJARATI_C_NGA      =0xA99,
    GUJARATI_C_CA           =0xA9a,
    GUJARATI_C_CHA      =0xA9b,
    GUJARATI_C_JA           =0xA9c,
    GUJARATI_C_JHA      =0xA9d,
    GUJARATI_C_NYA      =0xA9e,
    GUJARATI_C_TTA      =0xA9f,
    GUJARATI_C_TTHA     =0xAa0,
    GUJARATI_C_DDA      =0xAa1,
    GUJARATI_C_DDHA =0xAa2,
    GUJARATI_C_NNA      =0xAa3,
    GUJARATI_C_TA           =0xAa4,
    GUJARATI_C_THA      =0xAa5,
    GUJARATI_C_DA           =0xAa6,
    GUJARATI_C_DHA      =0xAa7,
    GUJARATI_C_NA           =0xAa8,
    GUJARATI_C_PA           =0xAaa,
    GUJARATI_C_PHA      =0xAab,
    GUJARATI_C_BA           =0xAac,
    GUJARATI_C_BHA      =0xAad,
    GUJARATI_C_MA       =0xAae,
    GUJARATI_C_YA           =0xAaf,
    GUJARATI_C_RA           =0xAb0,
    GUJARATI_C_LA           =0xAb2,
    GUJARATI_C_LLA      =0xAb3,
    GUJARATI_C_VA           =0xAb5,
    GUJARATI_C_SHA      =0xAb6,
    GUJARATI_C_SSA      =0xAb7,
    GUJARATI_C_SA           =0xAb8,
    GUJARATI_C_HA           =0xAb9,
    
    /* Various signs */
    GUJARATI_S_NUKTA        =0xAbc,
    GUJARATI_S_AVAGRAHA  =0xAbd,
    
    /* Dependent vowel signs */
    GUJARATI_DV_AA          =0xAbe,
    GUJARATI_DV_I               =0xAbf,
    GUJARATI_DV_II             =0xAc0,
    GUJARATI_DV_U               =0xAc1,
    GUJARATI_DV_UU          =0xAc2,
    GUJARATI_DV_VR          =0xAc3,
    GUJARATI_DV_VRR         =0xAc4,
    GUJARATI_DV_CE          =0xAc5,
    GUJARATI_DV_E               =0xAc7,
    GUJARATI_DV_AI          =0xAc8,
    GUJARATI_DV_CO          =0xAc9,
    GUJARATI_DV_O               =0xAcb,
    GUJARATI_DV_AU          =0xAcc,
    
    /* Virama */
    GUJARATI_S_HALANT       =0xAcd,
    
    GUJARATI_S_OM           =0xAd0,
    
    /*Additional vowels for Sanskrit*/
    GUJARATI_C_VRR          =0xAe0,
    GUJARATI_C_VLL          =0xAe1,
    GUJARATI_S_VL               =0xAe2,
    GUJARATI_S_VLL                  =0xAe3,
    
    /* Digits */
    GUJARATI_D_ZERO             =0xAe6,
    GUJARATI_D_ONE              =0xAe7,
    GUJARATI_D_TWO              =0xAe8,
    GUJARATI_D_THREE            =0xAe9,
    GUJARATI_D_FOUR             =0xAea,
    GUJARATI_D_FIVE             =0xAeb,
    GUJARATI_D_SIX              =0xAec,
    GUJARATI_D_SEVEN            =0xAed,
    GUJARATI_D_EIGHT            =0xAee,
    GUJARATI_D_NINE             =0xAef,
    
    /* Gujarati-specific additions */
    GUJARATI_S_ABBR             =0xAf0,
    GUJARATI_C_RUPEE_SIGN   =0xAf1
    
}GujaratiChar_e;

#endif //__GUJR_FONT__
#endif //__INDIC_FONT__
#endif /* __MLE_FONT_GUJR_PRIV_H__ */
