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


#ifndef __MLE_FONT_KHMER_PRIV_H__
#define __MLE_FONT_KHMER_PRIV_H__
#ifdef __INDIC_FONT__
#ifdef __KHMR_FONT__

#define KHMER_MASK 0x1780
#define KHMER_DIGIT1_MASK 0x17E0
#define KHMER_DIGIT2_MASK 0x17F0
#define KHMER_SYMBOLS_MASK 0x19E0
#define KHMER_SPECIAL_CHARACTER 0

#define IS_KHMER_ALL_RANGE(_char) ( ((_char >= KHMER_C_KA) && (_char <= KHMER_S_ATTHACAN)) || ((_char >= KHMER_D_ZERO) && (_char <= KHMER_D_NINE)) || ((_char >= KHMER_S_LA_SON) && (_char <= KHMER_S_PRAM_BUON)) || ((_char >= KHMER_S_PATHAMASAT) && (_char <= KHMER_S_DAP_PRAM_ROC)))
#define IS_KHMER_RANGE(_char) ((_char >= KHMER_C_KA) && (_char <= KHMER_S_ATTHACAN))
#define IS_KHMER_DIGIT1_RANGE(_char) ((_char >= KHMER_D_ZERO) && (_char <= KHMER_D_NINE))
#define IS_KHMER_DIGIT2_RANGE(_char) ((_char >= KHMER_S_LA_SON) && (_char <= KHMER_S_PRAM_BUON))
#define IS_KHMER_SYMBOLS_RANGE(_char) ((_char >= KHMER_S_PATHAMASAT) && (_char <= KHMER_S_DAP_PRAM_ROC))
#define IS_KHMER_COENG_CHAR(_char) (_char == KHMER_S_COENG)
#define IS_KHMER_CON_RO_CHAR(_char) (_char == KHMER_C_RO)
#define IS_KHMER_REGSHIFT_CHAR(_char) ((_char == KHMER_S_MUUSIKATOAN) || (_char == KHMER_S_TRIISA))
#define IS_KHMER_CONS_CHAR(_char) ((_char >= KHMER_C_KA) && (_char <= KHMER_C_QA))
#define IS_KHMER_INDV_CHAR(_char) ((_char >= KHMER_DIV_QAQ) && (_char <= KHMER_IV_QAU))
#define IS_KHMER_VABV_CHAR(_char) ((_char >= KHMER_DV_I) && (_char <= KHMER_DV_YY))
#define IS_KHMER_VBLW_CHAR(_char) ((_char >= KHMER_DV_U) && (_char <= KHMER_DV_UA))
#define IS_KHMER_VPRE_CHAR(_char) ((_char >= KHMER_DV_E) && (_char <= KHMER_DV_AI))
#define IS_KHMER_TWOPART_CHAR(_char) ( ((_char >= KHMER_DV_OE) && (_char <= KHMER_DV_IE)) || ((_char >= KHMER_DV_OO) && (_char <= KHMER_DV_AU)))
//#define IS_MYMR_EXTB_RANGE(_char) ((_char >= MYANMAR_C_SHAN_GHA) && (_char <= MYANMAR_C_TAI_BHA))
//#define IS_MYMR_RA_CHAR(_char) (_char == MYANMAR_C_RA)
//#define IS_MYMR_HALANT_CHAR(_char) (_char == MYANMAR_S_HALANT)
//#define IS_MYMR_DEPVOW_COMPOSING_CHAR(_char) ((_char >= MYANMAR_DV_U && _char <= MYANMAR_DV_AI) || _char == MYANMAR_S_HALANT)
//#define IS_MYMR_PREBASE_CHAR(_char) (_char == MYANMAR_C_RA) //|| (_char == MYANMAR_C_RRA), should RRA char be a prebase character? FIX Me!
//#define IS_MYMR_BELOW_BASE_FORM(_char) (_char == MYANMAR_C_LA)
//#define IS_MYMR_POST_BASE_FORM(_char) ((_char == MYANMAR_C_YA) || (_char == MYANMAR_C_VA) || (_char == MYANMAR_C_RA))
//#define IS_MYMR_POST_BELOW_BASE_FORM(_char) ((_char == MYANMAR_C_YA) || (_char == MYANMAR_C_VA) || (_char == MYANMAR_C_LA) || (_char == MYANMAR_C_RA))


typedef enum
{
    /* Consonants */
    KHMER_C_KA          =0x1780,
    KHMER_C_KHA        =0x1781,
    KHMER_C_KO          =0x1782,
    KHMER_C_KHO        =0x1783,
    KHMER_C_NGO        =0x1784,
    KHMER_C_CA          =0x1785,
    KHMER_C_CHA        =0x1786,
    KHMER_C_CO          =0x1787,
    KHMER_C_CHO        =0x1788,
    KHMER_C_NYO        =0x1789,
    KHMER_C_DA          =0x178A,
    KHMER_C_TTHA      =0x178B,
    KHMER_C_DO          =0x178C,
    KHMER_C_TTHO      =0x178D,
    KHMER_C_NNO        =0x178E,
    KHMER_C_TA          =0x178F,
    KHMER_C_THA        =0x1790,
    KHMER_C_TO          =0x1791,
    KHMER_C_THO        =0x1792,
    KHMER_C_NO          =0x1793,
    KHMER_C_BA          =0x1794,
    KHMER_C_PHA        =0x1795,
    KHMER_C_PO          =0x1796,
    KHMER_C_PHO       =0x1797,
    KHMER_C_MO         =0x1798,
    KHMER_C_YO         =0x1799,
    KHMER_C_RO         =0x179A,
    KHMER_C_LO         =0x179B,
    KHMER_C_VO         =0x179C,
    KHMER_C_SHA       =0x179D,
    KHMER_C_SSO       =0x179E,
    KHMER_C_SA         =0x179F,
    KHMER_C_HA         =0x17A0,
    KHMER_C_LA         =0x17A1,
    KHMER_C_QA         =0x17A2,

    /* Deprecated independent vowels for transliteration*/
    KHMER_DIV_QAQ     =0x17A3,
    KHMER_DIV_QAA     =0x17A4,

    /* Independent vowels */
    KHMER_IV_QI       =0x17A5,
    KHMER_IV_QII      =0x17A6,
    KHMER_IV_QU       =0x17A7,
    KHMER_IV_QUK      =0x17A8,
    KHMER_IV_QUU      =0x17A9,
    KHMER_IV_QUUV     =0x17AA,
    KHMER_IV_RY       =0x17AB,
    KHMER_IV_RYY      =0x17AC,
    KHMER_IV_LY       =0x17AD,
    KHMER_IV_LYY      =0x17AE,
    KHMER_IV_QE       =0x17AF,
    KHMER_IV_QAI      =0x17B0,
    KHMER_IV_QOO_TYPE1        =0x17B1,
    KHMER_IV_QOO_TYPE2        =0x17B2,
    KHMER_IV_QAU      =0x17B3,

    /* Inherent vowels */
    KHMER_VI_AQ       =0x17B4,
    KHMER_VI_AA       =0x17B5,

    /* Dependent vowel signs */
    KHMER_DV_AA       =0x17B6,
    KHMER_DV_I        =0x17B7,
    KHMER_DV_II       =0x17B8,
    KHMER_DV_Y        =0x17B9,
    KHMER_DV_YY       =0x17BA,
    KHMER_DV_U        =0x17BB,
    KHMER_DV_UU       =0x17BC,
    KHMER_DV_UA       =0x17BD,

    /* two-part dependent vowel */
    KHMER_DV_OE       =0x17BE,
    KHMER_DV_YA       =0x17BF,
    KHMER_DV_IE       =0x17C0,

    /* Dependent vowel signs */
    KHMER_DV_E        =0x17C1,
    KHMER_DV_AE       =0x17C2,
    KHMER_DV_AI       =0x17C3,

    /* two-part dependent vowel */
    KHMER_DV_OO       =0x17C4,
    KHMER_DV_AU       =0x17C5,

    /* Various signs*/
    KHMER_S_NIKAHIT                 =0x17C6,
    KHMER_S_REAHMUK               =0x17C7,
    KHMER_S_YUUKALEAPINTU    =0x17C8,

    /* Consonant shifters */
    KHMER_S_MUUSIKATOAN      =0x17C9,
    KHMER_S_TRIISA                  =0x17CA,

    /* Various signs */
    KHMER_S_BANTOC                  =0x17CB,
    KHMER_S_ROBAT                    =0x17CC,
    KHMER_S_TOANDAKHIAT       =0x17CD,
    KHMER_S_KAKABAT                =0x17CE,
    KHMER_S_AHSDA                    =0x17CF,
    KHMER_S_SAMYOK_SANNYA    =0x17D0,
    KHMER_S_VIRIAM                   =0x17D1,
    KHMER_S_COENG                     =0x17D2,

    /* Lunar date sign */
    KHMER_S_BATHAMASAT    =0x17D3,

    /* Various signs */
    KHMER_S_KHAN      =0x17D4,
    KHMER_S_BARIYOOSAN    =0x17D5,
    KHMER_S_CAMNUC_PII_KUUH    =0x17D6,
    KHMER_S_LEK_TOO   =0x17D7,
    KHMER_S_BEYYAL    =0x17D8,
    KHMER_S_PHNAEK_MUAN    =0x17D9,
    KHMER_S_KOOMUUT   =0x17DA,

    /* Currency symbol */
    KHMER_CS_RIEL   =0x17DB,

    /* Various signs */
    KHMER_S_AVAKRAHASANYA   =0x17DC,
    KHMER_S_ATTHACAN   =0x17DD,

    /* Khmer number for calculation*/

    /* Digits */
    KHMER_D_ZERO     =0x17E0,
    KHMER_D_ONE      =0x17E1,
    KHMER_D_TWO      =0x17E2,
    KHMER_D_THREE    =0x17E3,
    KHMER_D_FOUR     =0x17E4,
    KHMER_D_FIVE     =0x17E5,
    KHMER_D_SIX      =0x17E6,
    KHMER_D_SEVEN    =0x17E7,
    KHMER_D_EIGHT    =0x17E8,
    KHMER_D_NINE     =0x17E9,

    /* Khmer number not for calculation*/

    /* Numeric symbols for divination lore */
    KHMER_S_LA_SON    =0x17F0,
    KHMER_S_LA_MUOY   =0x17F1,
    KHMER_S_PII       =0x17F2,
    KHMER_S_BEI       =0x17F3,
    KHMER_S_BUON      =0x17F4,
    KHMER_S_PRAM      =0x17F5,
    KHMER_S_PRAM_MUOY =0x17F6,
    KHMER_S_PRAM_PII  =0x17F7,
    KHMER_S_PRAM_BEI  =0x17F8,
    KHMER_S_PRAM_BUON =0x17F9,


    /* Khmer Symbols */

    /* Lunar date symbols */
    KHMER_S_PATHAMASAT              =0x19E0,
    KHMER_S_MUOY_KOET  			=0x19E1,
    KHMER_S_PII_KOET   			=0x19E2,
    KHMER_S_BEI_KOET   			=0x19E3,
    KHMER_S_BUON_KOET  			=0x19E4,
    KHMER_S_PRAM_KOET  			=0x19E5,
    KHMER_S_PRAM_MUOY_KOET 		=0x19E6,
    KHMER_S_PRAM_PII_KOET 		=0x19E7,
    KHMER_S_PRAM_BEI_KOET 		=0x19E8,
    KHMER_S_PRAM_BUON_KOET 		=0x19E9,
    KHMER_S_DAP_KOET 			=0x19EA,
    KHMER_S_DAP_MUOY_KOET 		=0x19EB,
    KHMER_S_DAP_PII_KOET 		=0x19EC,
    KHMER_S_DAP_BEI_KOET 		=0x19ED,
    KHMER_S_DAP_BUON_KOET 		=0x19EE,
    KHMER_S_DAP_PRAM_KOET 		=0x19EF,
    KHMER_S_TUTEYASAT 			=0x19F0,
    KHMER_S_MUOY_ROC 			=0x19F1,
    KHMER_S_PII_ROC				=0x19F2,
    KHMER_S_BEI_ROC                       =0x19F3,
    KHMER_S_BUON_ROC 			=0x19F4,
    KHMER_S_PRAM_ROC 			=0x19F5,
    KHMER_S_PRAM_MUOY_ROC 		=0x19F6,
    KHMER_S_PRAM_PII_ROC 		=0x19F7,
    KHMER_S_PRAM_BEI_ROC 		=0x19F8,
    KHMER_S_PRAM_BUON_ROC 		=0x19F9,
    KHMER_S_DAP_ROC 				=0x19FA,
    KHMER_S_DAP_MUOY_ROC 		=0x19FB,
    KHMER_S_DAP_PII_ROC 			=0x19FC,
    KHMER_S_DAP_BEI_ROC 			=0x19FD,
    KHMER_S_DAP_BUON_ROC 		=0x19FE,
    KHMER_S_DAP_PRAM_ROC 		=0x19FF,

    SPECIAL_CONTROL_UNIT_WS     =0x200B
}KhmerChar_e;

typedef enum
{
    CLUSTER_INIT          = 0x00,
    CLUSTER_BASE          = 0x01,
    CLUSTER_COENG         = 0x02,
    CLUSTER_COENG_S       = 0x03,
    CLUSTER_SYLLABLE_S1   = 0x04,
    CLUSTER_SYLLABLE_S2   = 0x05,
    CLUSTER_SYLLABLE_S3   = 0x06,
    CLUSTER_SYLLABLE_S4   = 0x07,
    CLUSTER_SYLLABLE_S5   = 0x08,
    CLUSTER_SYLLABLE_S6   = 0x09,
}KhmerParserState_e;

#endif //__KHMR_FONT__
#endif //__INDIC_FONT__
#endif /* __MLE_FONT_KHMER_PRIV_H__ */
