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


#ifndef __MLE_FONT_LAOO_PRIV_H__
#define __MLE_FONT_LAOO_PRIV_H__
#ifdef __INDIC_FONT__
#ifdef __LAOO_FONT__

#define LAOO_MASK 0x0E81
//#define LAOO_DIGIT1_MASK 0x17E0
//#define LAOO_DIGIT2_MASK 0x17F0
//#define LAOO_SYMBOLS_MASK 0x19E0

#define IS_LAOO_ALL_RANGE(_char) ( (_char >= LAOO_C_KO) && (_char <= LAOO_C_KHMU_NYO) )
#define IS_LAOO_ABOVE1_CHAR(_char) ( ( _char == LAOO_V_MAI_KAN ) || ((_char >= LAOO_V_I) && (_char <= LAOO_V_YY)) || ( _char == LAOO_V_AMI_KON ) || ( _char == LAOO_S_NIGGAHITA ))
#define IS_LAOO_ABOVE2_CHAR(_char) ((_char >= LAOO_M_MAI_EK) && (_char <= LAOO_S_CANCELLATION_MARK))
#define IS_LAOO_BELOW1_CHAR(_char) (_char == LAOO_S_LO)
#define IS_LAOO_BELOW2_CHAR(_char) ((_char == LAOO_V_U) || (_char == LAOO_V_UU))


typedef enum
{
    /* Consonants */
    LAOO_C_KO                   = 0x0E81,
    LAOO_C_KHO_SUNG      = 0x0E82,
    LAOO_RESERVED1     = 0x0E83,
    LAOO_C_KHO_TAM        = 0x0E84,
    LAOO_RESERVED2     = 0x0E85,
    LAOO_RESERVED3     = 0x0E86,
    LAOO_C_NGO                = 0x0E87,
    LAOO_C_CO                   = 0x0E88,
    LAOO_RESERVED4     = 0x0E89,
    LAOO_C_SO_TAM          = 0x0E8A,
    LAOO_RESERVED5     = 0x0E8B,
    LAOO_RESERVED6     = 0x0E8C,
    LAOO_C_NYO                 = 0x0E8D,
    LAOO_RESERVED7     = 0x0E8E,
    LAOO_RESERVED8     = 0x0E8F,
    LAOO_RESERVED9     = 0x0E90,
    LAOO_RESERVED10   = 0x0E91,
    LAOO_RESERVED11   = 0x0E92,
    LAOO_RESERVED12   = 0x0E93,
    LAOO_C_DO                   = 0x0E94,
    LAOO_C_TO                   = 0x0E95,
    LAOO_C_THO_SUNG      = 0x0E96,
    LAOO_C_THO_TAM        = 0x0E97,
    LAOO_RESERVED13   = 0x0E98,
    LAOO_C_NO                   = 0x0E99,
    LAOO_C_BO                   = 0x0E9A,
    LAOO_C_PO                   = 0x0E9B,
    LAOO_C_PHO_SUNG      = 0x0E9C,
    LAOO_C_FO_TAM          = 0x0E9D,
    LAOO_C_PHO_TAM        = 0x0E9E,
    LAOO_C_FO_SUNG        = 0x0E9F,
    LAOO_RESERVED14   = 0x0EA0,
    LAOO_C_MO                   = 0x0EA1,
    LAOO_C_YO                   = 0x0EA2,
    LAOO_C_LO_LING          = 0x0EA3,
    LAOO_RESERVED15    = 0x0EA4,
    LAOO_C_LO_LOOT          = 0x0EA5,
    LAOO_RESERVED16    = 0x0EA6,
    LAOO_C_WO                   = 0x0EA7,
    LAOO_RESERVED17    = 0x0EA8,
    LAOO_RESERVED18    = 0x0EA9,
    LAOO_C_SO_SUNG         = 0x0EAA,
    LAOO_C_HO_SUNG         = 0x0EAB,
    LAOO_RESERVED19    = 0x0EAC,
    LAOO_C_O                      = 0x0EAD,
    LAOO_C_HO_TAM           = 0x0EAE,

    /* Sign */
    LAOO_S_ELLIPSIS          = 0x0EAF,

    /* Vowel */
    LAOO_V_A                      = 0x0EB0,
    LAOO_V_MAI_KAN          = 0x0EB1,
    LAOO_V_AA                    = 0x0EB2,
    LAOO_V_AM                    = 0x0EB3,
    LAOO_V_I                       = 0x0EB4,
    LAOO_V_II                      = 0x0EB5,
    LAOO_V_Y                       = 0x0EB6,
    LAOO_V_YY                     = 0x0EB7,
    LAOO_V_U                       = 0x0EB8,
    LAOO_V_UU                     = 0x0EB9,
    LAOO_RESERVED20     = 0x0EBA,
    LAOO_V_AMI_KON          = 0x0EBB,

    /* Sign */
    LAOO_S_LO                     = 0x0EBC,
    LAOO_S_NYO                  = 0x0EBD,

    LAOO_RESERVED21     = 0x0EBE,
    LAOO_RESERVED22     = 0x0EBF,

    /* Vowel */
    LAOO_V_E                       = 0x0EC0,
    LAOO_V_EI                      = 0x0EC1,
    LAOO_V_O                       = 0x0EC2,
    LAOO_V_AY                     = 0x0EC3,
    LAOO_V_AI                      = 0x0EC4,

    LAOO_RESERVED23     = 0x0EC5,

    /* Repetition Mark */
    LAOO_M_KO_LA                = 0x0EC6,

    LAOO_RESERVED24     = 0x0EC7,

    /* Tone Mark */
    LAOO_M_MAI_EK              = 0x0EC8,
    LAOO_M_MAI_THO            = 0x0EC9,
    LAOO_M_MAI_TI               = 0x0ECA,
    LAOO_M_MAI_CATAWA     = 0x0ECB,

    /* Sign */
    LAOO_S_CANCELLATION_MARK    = 0x0ECC,
    LAOO_S_NIGGAHITA                    = 0x0ECD,

    LAOO_RESERVED25     = 0x0ECE,
    LAOO_RESERVED26     = 0x0ECF,

    /* Digits */
    LAOO_D_ZERO                   = 0x0ED0,
    LAOO_D_ONE                     = 0x0ED1,
    LAOO_D_TWO                    = 0x0ED2,
    LAOO_D_THREE                 = 0x0ED3,
    LAOO_D_FOUR                   = 0x0ED4,
    LAOO_D_FIVE                    = 0x0ED5,
    LAOO_D_SIX                      = 0x0ED6,
    LAOO_D_SEVEN                 = 0x0ED7,
    LAOO_D_EIGHT                  = 0x0ED8,
    LAOO_D_NINE                    = 0x0ED9,

    LAOO_RESERVED27     = 0x0EDA,
    LAOO_RESERVED28     = 0x0EDB,

    /* Digraphs */
    LAOO_C_HO_NO                   = 0x0EDC,
    LAOO_C_HO_MO                   = 0x0EDD,

    /* Consonants for Khmu */
    LAOO_C_KHMU_GO              = 0x0EDE,
    LAOO_C_KHMU_NYO            = 0x0EDF,
}LaooChar_e;

typedef enum
{
    CLUSTER_LAOO_INIT     	     	         = 0x00,
    CLUSTER_LAOO_BASE                        = 0x01,
    CLUSTER_LAOO_MARK_S1                     = 0x02,
    CLUSTER_LAOO_MARK_S2                     = 0x03,
    CLUSTER_LAOO_MARK_S3                     = 0x04,
    CLUSTER_LAOO_MARK_S4                     = 0x05,
}LaooParserState_e;

typedef enum
{
    MARK_LEVEL_NONE = 0x00,
    MARK_LEVEL_ABOVE1 = 0x01,
    MARK_LEVEL_ABOVE2 = 0x02,
    MARK_LEVEL_BELOW1 = 0x03,
    MARK_LEVEL_BELOW2 = 0x04,
}LaooMarkLevel_e;

#endif //__LAOO_FONT__
#endif //__INDIC_FONT__
#endif /* __MLE_FONT_LAOO_PRIV_H__ */

