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


#ifndef __MLE_FONT_BENGALI_H__
#define __MLE_FONT_BENGALI_H__
#ifdef __INDIC_FONT__
#ifdef __BENGALI_FONT__

#define __BENGALI_NON_LIGATED__

#define BENGALI_MASK 0x0980

#define IS_BENGALI_RANGE(_char) (_char >= BENGALI_S_CHANDRA_BINDU && _char <= BENGALI_OS_ISSHAR)
#define IS_BENGALI_HALANT_CHAR(_char) (_char == BENGALI_S_HALANT)
#define IS_BENGALI_RA_CHAR(_char) (_char == BENGALI_C_RA)
#define IS_BENGALI_NUKTA_CHAR(_char) (_char == BENGALI_S_NUKTA)
#define IS_BENGALI_BINDU_CHAR(_char) (_char == BENGALI_S_CHANDRA_BINDU)
#define IS_BENGALI_WITH_NUKTA_CHAR(_char) (_char == BENGALI_C_RRA || _char == BENGALI_C_RHA || _char == BENGALI_C_YYA)
#define IS_BENGALI_NO_HALF_CHAR(_char) (_char == BENGALI_C_GHA || _char == BENGALI_C_CHA || _char == BENGALI_C_NYA || _char == BENGALI_C_YA || _char == BENGALI_C_SSA)
#define IS_BENGALI_POST_BASE_CON(_char) (_char == BENGALI_C_YA)
#define IS_BENGALI_DEPVOW_COMPOSING_CHAR(_char) ((_char >= BENGALI_DV_U && _char <= BENGALI_DV_VRR) || (_char >= BENGALI_S_VRR && _char <= BENGALI_S_VLL))
#define IS_BENGALI_DV_AA_CHAR(_char) (_char == BENGALI_DV_AA)

#define IS_BENGALI_CONST_NEED_DV_RIGHT_CHAR(_char) ( _char == 0x099B || _char == 0x09B9 || _char == 0x09DC || _char == 0x09DD)

typedef enum
{       
    /* Various signs */
    BENGALI_S_CHANDRA_BINDU = 0x981,
    BENGALI_S_ANUSVARA      = 0x982,
    BENGALI_S_VISARGA       = 0x983,

    /*Independent vowels*/
    BENGALI_IV_A            = 0x985,
    BENGALI_IV_AA           = 0x986,
    BENGALI_IV_I            = 0x987,
    BENGALI_IV_II           = 0x988,
    BENGALI_IV_U            = 0x989,
    BENGALI_IV_UU           = 0x98a,
    BENGALI_IV_VR           = 0x98b,
    BENGALI_IV_VL           = 0x98c,
    
    BENGALI_IV_E            = 0x98f,
    BENGALI_IV_AI           = 0x990,
    BENGALI_IV_O            = 0x993,
    BENGALI_IV_AU           = 0x994,

    /* Consonants */
    BENGALI_C_KA            = 0x995,
    BENGALI_C_KHA           = 0x996,
    BENGALI_C_GA            = 0x997,
    BENGALI_C_GHA           = 0x998,
    BENGALI_C_NGA           = 0x999,
    BENGALI_C_CA            = 0x99a,
    BENGALI_C_CHA           = 0x99b,
    BENGALI_C_JA            = 0x99c,
    BENGALI_C_JHA           = 0x99d,
    BENGALI_C_NYA           = 0x99e,
    BENGALI_C_TTA           = 0x99f,  
    BENGALI_C_TTHA          = 0x9a0,
    BENGALI_C_DDA           = 0x9a1,
    BENGALI_C_DDHA          = 0x9a2,
    BENGALI_C_NNA           = 0x9a3,
    BENGALI_C_TA            = 0x9a4,
    BENGALI_C_THA           = 0x9a5,
    BENGALI_C_DA            = 0x9a6,
    BENGALI_C_DHA           = 0x9a7,
    BENGALI_C_NA            = 0x9a8,

    BENGALI_C_PA            = 0x9aa,
    BENGALI_C_PHA           = 0x9ab,
    BENGALI_C_BA            = 0x9ac,
    BENGALI_C_BHA           = 0x9ad,
    BENGALI_C_MA            = 0x9ae,
    BENGALI_C_YA            = 0x9af,
    BENGALI_C_RA            = 0x9b0,

    BENGALI_C_LA            = 0x9b2,
    
    BENGALI_C_SHA           = 0x9b6,
    BENGALI_C_SSA           = 0x9b7,
    BENGALI_C_SA            = 0x9b8,
    BENGALI_C_HA            = 0x9b9,

    /* Various signs */
    BENGALI_S_NUKTA         = 0x9bc,
    BENGALI_S_AVAGRAHA      = 0x9bd,

    /* Dependent vowel signs*/
    BENGALI_DV_AA           = 0x9be,
    BENGALI_DV_I            = 0x9bf,
    BENGALI_DV_II           = 0x9c0,
    BENGALI_DV_U            = 0x9c1,
    BENGALI_DV_UU           = 0x9c2,
    BENGALI_DV_VR           = 0x9c3,
    BENGALI_DV_VRR          = 0x9c4,
    
    BENGALI_DV_E            = 0x9c7,
    BENGALI_DV_AI           = 0x9c8,

    /* Two-part dependent vowel signs*/
    BENGALI_DV_O            = 0x9cb,
    BENGALI_DV_AU           = 0x9cc,

    /* Virama */
    BENGALI_S_HALANT        = 0x9cd,
    
    /* Additional consonant */
    BENGALI_AD_TA           = 0x9ce,

    /*Signs*/
    BENGALI_AD_AU           = 0x9d7,

    /*Additional consonant*/
    BENGALI_C_RRA           = 0x9dc,
    BENGALI_C_RHA           = 0x9dd,
    BENGALI_C_YYA           = 0x9df,

    /*Additional vowels for Sanskrit*/
    BENGALI_C_VRR           = 0x9e0,
    BENGALI_C_VLL           = 0x9e1,
    BENGALI_S_VRR           = 0x9e2,
    BENGALI_S_VLL           = 0x9e3,
       
    /* Digits */
    BENGALI_D_ZERO          = 0x9e6,
    BENGALI_D_ONE           = 0x9e7,
    BENGALI_D_TWO           = 0x9e8,
    BENGALI_D_THREE         = 0x9e9,
    BENGALI_D_FOUR          = 0x9ea,
    BENGALI_D_FIVE          = 0x9eb,
    BENGALI_D_SIX           = 0x9ec,
    BENGALI_D_SEVEN         = 0x9ed,
    BENGALI_D_EIGHT         = 0x9ee,
    BENGALI_D_NINE          = 0x9ef,

    /*Bengali-spacific additions*/
    BENGALI_C_MRA           = 0x9f0,
    BENGALI_C_LRA           = 0x9f1,
    BENGALI_OS_RUPEE        = 0x9f2,
    BENGALI_C_RUPEE_SIGN    = 0x9f3,
    BENGALI_C_CURONE        = 0x9f4,
    BENGALI_C_CURTWO        = 0x9f5,
    BENGALI_C_CURTHREE      = 0x9f6,
    BENGALI_C_CURFOUR       = 0x9f7,
    BENGALI_OS_CURLESSDEN   = 0x9f8,
    BENGALI_OS_CURDENSIXTEEN= 0x9f9,
    BENGALI_OS_ISSHAR       = 0x9fa
}BengaliChar_e;

U16 msAPI_MLE_FontBengaliGetLigatedCluster( const U16 *pU16Txt, U32 U32InLen, U16 *pU16Cluster, U16 U16BufferSize, U16 U16ClusterSize, U16 *pU16ConsumedCount, U16 *pU16SeqInCluster);

U16 msAPI_MLE_FontBengaliGetYAPHALAAClusterSize( const U16 *pU16Txt, U32 U32InLen, U16 U16ConsumedCount);
#endif //__INDIC_FONT__
#endif //__BENGALI_FONT__
#endif /* __MLE_FONT_BENGALI_H__ */
