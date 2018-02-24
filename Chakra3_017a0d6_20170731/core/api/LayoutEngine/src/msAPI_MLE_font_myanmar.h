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


#ifndef __MLE_FONT_MYANMAR_PRIV_H__
#define __MLE_FONT_MYANMAR_PRIV_H__
#ifdef __INDIC_FONT__
#ifdef __MYMR_FONT__

#define MYMR_MASK 0x1000
#define MYMR_EXTA_MASK 0xAA60
#define MYMR_EXTB_MASK 0xA9E0

#define IS_MYMR_ALL_RANGE(_char) ( ((_char >= MYANMAR_C_KA) && (_char <= MYANMAR_C_S_SHAN_EXCLAMATION)) || ((_char >= MYANMAR_C_KHAMTI_GA) && (_char <= MYANMAR_C_SHWE_SHA)) || ((_char >= MYANMAR_C_SHAN_GHA) && (_char <= MYANMAR_C_TAI_BHA)) )
#define IS_MYMR_RANGE(_char) ((_char >= MYANMAR_C_KA) && (_char <= MYANMAR_C_S_SHAN_EXCLAMATION))
#define IS_MYMR_EXTA_RANGE(_char) ((_char >= MYANMAR_C_KHAMTI_GA) && (_char <= MYANMAR_C_SHWE_SHA))
#define IS_MYMR_EXTB_RANGE(_char) ((_char >= MYANMAR_C_SHAN_GHA) && (_char <= MYANMAR_C_TAI_BHA))

#define IS_MYMR_HALANT_CHAR(_char) (_char == MYANMAR_S_HALANT)


typedef enum
{
    /* Consonants */
    MYANMAR_C_KA        =0x1000,
    MYANMAR_C_KHA       =0x1001,
    MYANMAR_C_GA        =0x1002,
    MYANMAR_C_GHA       =0x1003,
    MYANMAR_C_NGA       =0x1004,
    MYANMAR_C_CA        =0x1005,
    MYANMAR_C_CHA       =0x1006,
    MYANMAR_C_JA        =0x1007,
    MYANMAR_C_JHA       =0x1008,
    MYANMAR_C_NYA       =0x1009,
    MYANMAR_C_NNYA      =0x100A,
    MYANMAR_C_TTA       =0x100B,
    MYANMAR_C_TTHA      =0x100C,
    MYANMAR_C_DDA       =0x100D,
    MYANMAR_C_DDHA      =0x100E,
    MYANMAR_C_NNA       =0x100F,
    MYANMAR_C_TA        =0x1010,
    MYANMAR_C_THA       =0x1011,
    MYANMAR_C_DA        =0x1012,
    MYANMAR_C_DHA       =0x1013,
    MYANMAR_C_NA        =0x1014,
    MYANMAR_C_PA        =0x1015,
    MYANMAR_C_PHA       =0x1016,
    MYANMAR_C_BA        =0x1017,
    MYANMAR_C_BHA       =0x1018,
    MYANMAR_C_MA        =0x1019,
    MYANMAR_C_YA        =0x101A,
    MYANMAR_C_RA        =0x101B,
    MYANMAR_C_LA        =0x101C,
    MYANMAR_C_WA        =0x101D,
    MYANMAR_C_SA        =0x101E,
    MYANMAR_C_HA        =0x101F,
    MYANMAR_C_LLA       =0x1020,

    /* Independent vowels */
    MYANMAR_IV_A        =0x1021,
    MYANMAR_IV_SHAN_A   =0x1022,
    MYANMAR_IV_I        =0x1023,
    MYANMAR_IV_II       =0x1024,
    MYANMAR_IV_U        =0x1025,        
    MYANMAR_IV_UU       =0x1026,
    MYANMAR_IV_E        =0x1027,
    MYANMAR_IV_MON_E    =0x1028,
    MYANMAR_IV_O        =0x1029,
    MYANMAR_IV_AU       =0x102A,

    /* Dependent vowel signs */
    MYANMAR_DV_TALL_AA  =0x102B,
    MYANMAR_DV_AA       =0x102C,
    MYANMAR_DV_I        =0x102D,
    MYANMAR_DV_II       =0x102E,
    MYANMAR_DV_U        =0x102F,
    MYANMAR_DV_UU       =0x1030,
    MYANMAR_DV_E        =0x1031,
    MYANMAR_DV_AI       =0x1032,
    MYANMAR_DV_MON_II   =0x1033,
    MYANMAR_DV_MON_O    =0x1034,
    MYANMAR_DV_E_ABOVE  =0x1035,
        
    /* Various signs*/
    MYANMAR_S_ANUSVARA  =0x1036,
    MYANMAR_S_DOT_BELOW =0x1037,
    MYANMAR_S_VISARGA   =0x1038,

    /* Virama/Halant */
    MYANMAR_S_HALANT    =0x1039,
    
    /* Various signs */
    MYANMAR_S_ASAT      =0x103A,
    
    /* Dependent consonants signs */
    MYANMAR_DC_YA       =0x103B,
    MYANMAR_DC_RA       =0x103C,
    MYANMAR_DC_WA       =0x103D,
    MYANMAR_DC_HA       =0x103E,
    
    /* Consonants */
    MYANMAR_C_GREAT_SA  =0x103F,
    
    /* Digits */
    MYANMAR_D_ZERO      =0x1040,
    MYANMAR_D_ONE       =0x1041,
    MYANMAR_D_TWO       =0x1042,
    MYANMAR_D_THREE     =0x1043,
    MYANMAR_D_FOUR      =0x1044,
    MYANMAR_D_FIVE      =0x1045,
    MYANMAR_D_SIX       =0x1046,
    MYANMAR_D_SEVEN     =0x1047,
    MYANMAR_D_EIGHT     =0x1048,
    MYANMAR_D_NINE      =0x1049,
    
    /* Punctuation */
    MYANMAR_S_LITTLE_SECTION    =0x104A,
    MYANMAR_S_SECTION   =0x104B,
    
    /* Various signs */
    MYANMAR_S_LOCATIVE  =0x104C,
    MYANMAR_S_COMPLETED =0x104D,
    MYANMAR_S_AFOREMENTIONED    =0x104E,
    MYANMAR_S_GENITIVE  =0x104F,
    
    /* Pali and Sanskrit extensions */
    MYANMAR_C_SHA       =0x1050,
    MYANMAR_C_SSA       =0x1051,
    MYANMAR_C_VR        =0x1052,
    MYANMAR_C_VRR       =0x1053,
    MYANMAR_C_VL        =0x1054,
    MYANMAR_C_VLL       =0x1055,
    MYANMAR_C_VS_VR     =0x1056,
    MYANMAR_C_VS_VRR    =0x1057,
    MYANMAR_C_VS_VL     =0x1058,
    MYANMAR_C_VS_VLL    =0x1059,
    
    /* Extensions for Mon */
    MYANMAR_C_MON_NGA   =0x105A,
    MYANMAR_C_MON_JHA   =0x105B,
    MYANMAR_C_MON_BBA   =0x105C,
    MYANMAR_C_MON_BBE   =0x105D,
    MYANMAR_C_CS_MON_NA =0x105E,
    MYANMAR_C_CS_MON_MA =0x105F,
    MYANMAR_C_CS_MON_LA =0x1060,

    /* Extensions for S'gaw Karen */
    MYANMAR_C_SGAW_SHA  =0x1061,
    MYANMAR_C_VS_SGAW_EU=0x1062,
    MYANMAR_C_SGAW_HATHI=0x1063,
    MYANMAR_C_SGAW_KE_PHO   =0x1064,

    /* Extensions for Western Pwo Karen */
    MYANMAR_C_WP_THA    =0x1065,
    MYANMAR_C_WP_PWA    =0x1066,
    MYANMAR_C_VS_WP_EU  =0x1067,
    MYANMAR_C_VS_WP_UE  =0x1068,
    MYANMAR_C_VS_WP_T1  =0x1069,
    MYANMAR_C_VS_WP_T2  =0x106A,
    MYANMAR_C_VS_WP_T3  =0x106B,
    MYANMAR_C_VS_WP_T4  =0x106C,
    MYANMAR_C_VS_WP_T5  =0x106D,
    
    /* Extensions for Eastern Pwo Karen */
    MYANMAR_C_EP_NNA    =0x106E,
    MYANMAR_C_EP_YWA    =0x106F,
    MYANMAR_C_EP_GHWA   =0x1070,
    
    /* Extensions for Geba Karen */
    MYANMAR_C_VS_GEBA_I =0x1071,

    /* Extensions for Kayah */
    MYANMAR_C_VS_KAYAH_OE   =0x1072,
    MYANMAR_C_VS_KAYAH_U    =0x1073,
    MYANMAR_C_VS_KAYAH_EE   =0x1074,
    
    /* Extensions for Shan */
    MYANMAR_C_SHAN_KA   =0x1075,
    MYANMAR_C_SHAN_KHA  =0x1076,
    MYANMAR_C_SHAN_GA   =0x1077,
    MYANMAR_C_SHAN_CA   =0x1078,
    MYANMAR_C_SHAN_ZA   =0x1079,
    MYANMAR_C_SHAN_NYA  =0x107A,
    MYANMAR_C_SHAN_DA   =0x107B,
    MYANMAR_C_SHAN_NA   =0x107C,
    MYANMAR_C_SHAN_PHA  =0x107D,
    MYANMAR_C_SHAN_FA   =0x107E,
    MYANMAR_C_SHAN_BA   =0x107F,
    MYANMAR_C_SHAN_THA  =0x1080,
    MYANMAR_C_SHAN_HA   =0x1081,
    MYANMAR_C_CS_SHAN_WA=0x1082,
    MYANMAR_C_VS_SHAN_AA=0x1083,
    MYANMAR_C_VS_SHAN_E =0x1084,
    MYANMAR_C_VS_SHAN_E_ABOVE   =0x1085,
    MYANMAR_C_VS_SHAN_FINAL_Y   =0x1086,
    MYANMAR_C_S_SHAN_T2 =0x1087,
    MYANMAR_C_S_SHAN_T3 =0x1088,
    MYANMAR_C_S_SHAN_T5 =0x1089,
    MYANMAR_C_S_SHAN_T6 =0x108A,
    MYANMAR_C_S_SHAN_CT2=0x108B,
    MYANMAR_C_S_SHAN_CT3=0x108C,
    MYANMAR_C_S_SHAN_CET=0x108D,
    
    /* Extensions for Rumai Palaung */
    MYANMAR_C_RUMAI_FA  =0x108E,
    MYANMAR_C_S_RUMAI_T5=0x108F,
    
    /* Shan digits */
    MYANMAR_D_SHAN_ZERO =0x1090,
    MYANMAR_D_SHAN_ONE  =0x1091,
    MYANMAR_D_SHAN_TWO  =0x1092,
    MYANMAR_D_SHAN_THREE=0x1093,
    MYANMAR_D_SHAN_FOUR =0x1094,
    MYANMAR_D_SHAN_FIVE =0x1095,
    MYANMAR_D_SHAN_SIX  =0x1096,
    MYANMAR_D_SHAN_SEVEN=0x1097,
    MYANMAR_D_SHAN_EIGHT=0x1098,
    MYANMAR_D_SHAN_NINE =0x1099,
    
    /* Extensions for Khamti Shan */
    MYANMAR_C_S_KHAMTI_T1   =0x109A,
    MYANMAR_C_S_KHAMTI_T3   =0x109B,

    /* Extensions for Aiton and Phake */
    MYANMAR_C_VS_AITON_A=0x109C,
    MYANMAR_C_VS_AITON_AI   =0x109D,

    /* Shan symbols */
    MYANMAR_C_S_SHAN_ONE=0x109E,
    MYANMAR_C_S_SHAN_EXCLAMATION    =0x109F,
    
    /* Myanmar Extended-A */
                                     
    /* Khamti Shan consonants */
    MYANMAR_C_KHAMTI_GA =0xAA60,
    MYANMAR_C_KHAMTI_CA =0xAA61,
    MYANMAR_C_KHAMTI_CHA=0xAA62,
    MYANMAR_C_KHAMTI_JA =0xAA63,
    MYANMAR_C_KHAMTI_JHA=0xAA64,
    MYANMAR_C_KHAMTI_NYA=0xAA65,
    MYANMAR_C_KHAMTI_TTA=0xAA66,
    MYANMAR_C_KHAMTI_TTHA   =0xAA67,
    MYANMAR_C_KHAMTI_DDA=0xAA68,
    MYANMAR_C_KHAMTI_DDHA   =0xAA69,
    MYANMAR_C_KHAMTI_DHA=0xAA6A,
    MYANMAR_C_KHAMTI_NA =0xAA6B,
    MYANMAR_C_KHAMTI_SA =0xAA6C,
    MYANMAR_C_KHAMTI_HA =0xAA6D,
    MYANMAR_C_KHAMTI_HHA=0xAA6E,
    MYANMAR_C_KHAMTI_FA =0xAA6F,
    MYANMAR_C_KHAMTI_REDUPLICATION  =0xAA70,
    MYANMAR_C_KHAMTI_XA =0xAA71,
    MYANMAR_C_KHAMTI_ZA =0xAA72,
    MYANMAR_C_KHAMTI_RA =0xAA73,
    
    /* Khamti Shan logograms */
    MYANMAR_C_LOGO_KHAMTI_OAY   =0xAA74,
    MYANMAR_C_LOGO_KHAMTI_QN    =0xAA75,
    MYANMAR_C_LOGO_KHAMTI_HM    =0xAA76,
    
    /* Aiton symbols and letters */
    MYANMAR_C_S_AITON_EXCLAMATION   =0xAA77,
    MYANMAR_C_S_AITON_ONE   =0xAA78,
    MYANMAR_C_S_AITON_TWO   =0xAA79,
    MYANMAR_C_AITON_RA  =0xAA7A,

    /* Pa'o Karen tone mark */
    MYANMAR_C_S_PAO_T   =0xAA7B,
    
    /* Tai Laing tone marks */
    MYANMAR_C_S_TAI_T2  =0xAA7C,
    MYANMAR_C_S_TAI_T5  =0xAA7D,
    
    /* Shwe Palaung letters */
    MYANMAR_C_SHWE_CHA  =0xAA7E,
    MYANMAR_C_SHWE_SHA  =0xAA7F,

    /* Myanmar Extended-B */
    
    /* Additions for Shan Pali */
    MYANMAR_C_SHAN_GHA  =0xA9E0,
    MYANMAR_C_SHAN_CHA  =0xA9E1,
    MYANMAR_C_SHAN_JHA  =0xA9E2,
    MYANMAR_C_SHAN_NNA  =0xA9E3,
    MYANMAR_C_SHAN_BHA  =0xA9E4,
    MYANMAR_C_S_SHAN_SAW=0xA9E5,
    
    /* Reduplication mark */
    MYANMAR_C_SHAN_REDUPLICATION =0xA9E6,

    /* Tai Laing consonants */
    MYANMAR_C_TAI_NYA   =0xA9E7,
    MYANMAR_C_TAI_FA    =0xA9E8,
    MYANMAR_C_TAI_GA    =0xA9E9,
    MYANMAR_C_TAI_GHA   =0xA9EA,
    MYANMAR_C_TAI_JA    =0xA9EB,
    MYANMAR_C_TAI_JHA   =0xA9EC,
    MYANMAR_C_TAI_DDA   =0xA9ED,
    MYANMAR_C_TAI_DDHA  =0xA9EE,
    MYANMAR_C_TAI_NNA   =0xA9EF,
    
    /* Tai Laing digits */
    MYANMAR_D_TAI_ZERO  =0xA9F0,
    MYANMAR_D_TAI_ONE   =0xA9F1,
    MYANMAR_D_TAI_TWO   =0xA9F2,
    MYANMAR_D_TAI_THREE =0xA9F3,
    MYANMAR_D_TAI_FOUR  =0xA9F4,
    MYANMAR_D_TAI_FIVE  =0xA9F5,
    MYANMAR_D_TAI_SIX   =0xA9F6,
    MYANMAR_D_TAI_SEVEN =0xA9F7,
    MYANMAR_D_TAI_EIGHT =0xA9F8,
    MYANMAR_D_TAI_NINE  =0xA9F9,
    
    /* Tai Laing consonants */
    MYANMAR_C_TAI_LLA   =0xA9FA,
    MYANMAR_C_TAI_DA    =0xA9FB,
    MYANMAR_C_TAI_DHA   =0xA9FC,
    MYANMAR_C_TAI_BA    =0xA9FD,
    MYANMAR_C_TAI_BHA   =0xA9FE

}MyanmarChar_e;

typedef enum
{ 
    CLUSTER_SIMPLE   = 0x00,
    CLUSTER_HALANT   = 0x01,
    CLUSTER_COMPLEX  = 0x02,
    CLUSTER_HALANT_EXT_S1 = 0x03,
    CLUSTER_HALANT_EXT_S2 = 0x04,
    CLUSTER_HALANT_EXT_S3 = 0x05,
    CLUSTER_HALANT_EXT_S4 = 0x06,
    CLUSTER_HALANT_BASE = 0x07,
    CLUSTER_HALANT_VS1 = 0x08,
    CLUSTER_COMPLEX_S1 = 0x09,
    CLUSTER_COMPLEX_S2 = 0x0A,
    CLUSTER_COMPLEX_S3 = 0x0B,
    CLUSTER_COMPLEX_S4 = 0x0C,
    CLUSTER_COMPLEX_S5 = 0x0D,
    CLUSTER_COMPLEX_S6 = 0x0E,
    CLUSTER_COMPLEX_S7 = 0x0F,
    CLUSTER_COMPLEX_S8 = 0x10,
    CLUSTER_COMPLEX_S9 = 0x11,
    CLUSTER_COMPLEX_S10 = 0x12,
    CLUSTER_COMPLEX_S11 = 0x13,
    CLUSTER_COMPLEX_S12 = 0x14,
    CLUSTER_COMPLEX_S13 = 0x15,
    CLUSTER_COMPLEX_S14 = 0x16,
    CLUSTER_COMPLEX_S15 = 0x17,
    CLUSTER_COMPLEX_S16 = 0x18,
    CLUSTER_COMPLEX_S17 = 0x19,
    CLUSTER_COMPLEX_S18 = 0x1A,
    CLUSTER_COMPLEX_S19 = 0x1B,
    CLUSTER_COMPLEX_S20 = 0x1C,
    CLUSTER_COMPLEX_S21 = 0x1D,
    CLUSTER_COMPLEX_S22 = 0x1E,
    CLUSTER_COMPLEX_S23 = 0x1F,
    CLUSTER_COMPLEX_S24 = 0x20,
    CLUSTER_COMPLEX_S25 = 0x21,
    CLUSTER_COMPLEX_S26 = 0x22
}MyanmarParserState_e;

#endif //__MYMR_FONT__
#endif //__INDIC_FONT__
#endif /* __MLE_FONT_MYANMAR_PRIV_H__ */
