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


#ifndef __MLE_FONT_DEVANAGARI_PRIV_H__
#define __MLE_FONT_DEVANAGARI_PRIV_H__
#ifdef __INDIC_FONT__
#ifdef __DVNG_FONT__

#define DVNG_MASK 0x0900

#define IS_DVNG_RANGE(_char) (_char >= DVNG_S_CHANDRA_BINDU && _char <= DVNG_S_RUPEE)
#define IS_DVNG_RA_CHAR(_char) (_char == DVNG_C_RA)
#define IS_DVNG_HALANT_CHAR(_char) (_char == DVNG_S_HALANT)
#define IS_DVNG_NUKTA_CHAR(_char) (_char == DVNG_S_NUKTA)
#define IS_DVNG_BINDU_CHAR(_char) (_char == DVNG_S_CHANDRA_BINDU || _char == DVNG_S_BINDU)
#define IS_DVNG_WITH_NUKTA_CHAR(_char) (_char == DVNG_C_NNNA || _char == DVNG_C_RRA || _char == DVNG_C_LLLA || (_char >= DVNG_AC_QA && _char <= DVNG_AC_YYA))
#define IS_DVNG_NO_HALF_CHAR(_char) (_char == DVNG_NIV_CE)
#define IS_DVNG_DEPVOW_COMPOSING_CHAR(_char) ((_char >= DVNG_DV_U && _char <= DVNG_DV_AI) || _char == DVNG_S_HALANT)

#define IS_DVNG_DEPVOW_LONG_DOWN_CHAR(_char) (_char == DVNG_C_HA)
#define IS_DVNG_DEPVOW_SMALL_CHAR(_char) (_char == DVNG_C_RA)

typedef enum
{       
    /* Various signs*/
    DVNG_S_CHANDRA_BINDU=0x0901,
    DVNG_S_BINDU        =0x902,
    DVNG_S_VISARGA      =0x903,

    /* Independent vowels */
    DVNG_NIV_A          =0x904,
    DVNG_IV_A           =0x905,
    DVNG_IV_AA          =0x906,
    DVNG_IV_I           =0x907,
    DVNG_IV_II          =0x908,         
    DVNG_IV_U           =0x909,
    DVNG_IV_UU          =0x90a,
    DVNG_IV_R           =0x90b,
    DVNG_NIV_L          =0x90c,
    DVNG_NIV_CE         =0x90d,
    DVNG_NIV_SE         =0x90e,
    DVNG_IV_E           =0x90f,
    DVNG_IV_AI          =0x910,
    DVNG_NIV_CO         =0x911,
    DVNG_NIV_SO         =0x912,
    DVNG_IV_O           =0x913,
    DVNG_IV_AU          =0x914,
    
    /* Consonants */        
    DVNG_C_KA           =0x915,
    DVNG_C_KHA          =0x916,
    DVNG_C_GA           =0x917,
    DVNG_C_GHA          =0x918,
    DVNG_C_NGA          =0x919,
    DVNG_C_CHA          =0x91a,
    DVNG_C_CHHA         =0x91b,
    DVNG_C_JA           =0x91c,
    DVNG_C_JHA          =0x91d,
    DVNG_C_NYA          =0x91e,
    DVNG_C_TTA          =0x91f,
    DVNG_C_TTHA         =0x920,
    DVNG_C_DDA          =0x921,
    DVNG_C_DDHA         =0x922,
    DVNG_C_NNA          =0x923,
    DVNG_C_TA           =0x924,
    DVNG_C_THA          =0x925,
    DVNG_C_DA           =0x926,
    DVNG_C_DHA          =0x927,
    DVNG_C_NA           =0x928,
    DVNG_C_NNNA         =0x929,
    DVNG_C_PA           =0x92a,
    DVNG_C_PHA          =0x92b,
    DVNG_C_BA           =0x92c,
    DVNG_C_BHA          =0x92d,
    DVNG_C_MA           =0x92e,
    DVNG_C_YA           =0x92f,
    DVNG_C_RA           =0x930,
    DVNG_C_RRA          =0x931,
    DVNG_C_LA           =0x932,
    DVNG_C_LLA          =0x933,
    DVNG_C_LLLA         =0x934,
    DVNG_C_VA           =0x935,
    DVNG_C_SHA          =0x936,
    DVNG_C_SSA          =0x937,
    DVNG_C_SA           =0x938,
    DVNG_C_HA           =0x939,
    
    /* Various signs */
    DVNG_S_NUKTA        =0x93c,
    DVNG_NS_AVAGRAHA    =0x93d,
    
    /* Dependent vowel signs */
    DVNG_DV_AA          =0x93e,
    DVNG_DV_I           =0x93f,
    DVNG_DV_II          =0x940,
    DVNG_DV_U           =0x941,
    DVNG_DV_UU          =0x942,
    DVNG_DV_R           =0x943,
    DVNG_NDV_RR         =0x944,
    DVNG_DV_CE          =0x945,
    DVNG_NDV_E          =0x946,
    DVNG_DV_E           =0x947,
    DVNG_DV_AI          =0x948,
    DVNG_NDV_CO         =0x949,
    DVNG_NDV_O          =0x94a,
    DVNG_DV_O           =0x94b,
    DVNG_DV_AU          =0x94c,
    
    /* Various signs */
    DVNG_S_HALANT       =0x94d,
    DVNG_NS_RESERVED1   =0x94e,
    DVNG_NS_RESERVED2   =0x94f,
    DVNG_S_OM           =0x950,
    DVNG_NS_UDATTA      =0x951,
    DVNG_NS_ANUDATTA    =0x952,
    DVNG_NS_GACCENT     =0x953,
    DVNG_NS_AACCENT     =0x954,
    
    /* Additional consonants */
    DVNG_AC_QA          =0x958,
    DVNG_AC_KHHA        =0x959,
    DVNG_AC_GHHA        =0x95a,
    DVNG_AC_ZA          =0x95b,
    DVNG_AC_DDDHA       =0x95c,
    DVNG_AC_RHA         =0x95d,
    DVNG_AC_FA          =0x95e,
    DVNG_AC_YYA         =0x95f,
    
    /* Generic additions */
    DVNG_NG_RR          =0x960,
    DVNG_NG_LL          =0x961,
    DVNG_NG_L           =0x962,
    DVNG_NG_VLL         =0x963,
    DVNG_NG_D           =0x964,
    DVNG_NG_DD          =0x965,
    
    /* Digits */
    DVNG_D_ZERO         =0x966,
    DVNG_D_ONE          =0x967,
    DVNG_D_TWO          =0x968,
    DVNG_D_THREE        =0x969,
    DVNG_D_FOUR         =0x96a,
    DVNG_D_FIVE         =0x96b,
    DVNG_D_SIX          =0x96c,
    DVNG_D_SEVEN        =0x96d,
    DVNG_D_EIGHT        =0x96e,
    DVNG_D_NINE         =0x96f,
    
    /* Devanagari-specific additions */
    DVNG_S_ABBR         =0x970,
    DVNG_S_RUPEE        =0x971
}DevanagariChar_e;

#endif //__DVNG_FONT__
#endif //__INDIC_FONT__
#endif /* __MLE_FONT_HINDI_PRIV_H__ */
