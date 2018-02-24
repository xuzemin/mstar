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

#ifdef __INDIC_FONT__

/*------------------------------------------------------------------------------------------
*
*                                                                                     INCLUDE HEAD FILE
*
-------------------------------------------------------------------------------------------*/
#include "msAPI_MLE_common_def.h"
#include "msAPI_MLE_font_hindi_priv.h"
#include "msAPI_MLE_font_base.h"

#ifdef __MYMR_FONT__
#include "msAPI_MLE_font_myanmar.h"

/*------------------------------------------------------------------------------------------
*
*                                                                                     MACRO DEFINE
*
-------------------------------------------------------------------------------------------*/

#if 0
const U8 g_MyanmarCharTypeArray[] =
{
    /*  CONSONANT'S TABLES    */            /* Consonants */
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_KA        =0x1000,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_KHA       =0x1001,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_GA        =0x1002,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_GHA       =0x1003,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_NGA       =0x1004,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_CA        =0x1005,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_CHA       =0x1006,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_JA        =0x1007,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_JHA       =0x1008,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_NYA       =0x1009,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_NNYA      =0x100A,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_TTA       =0x100B,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_TTHA      =0x100C,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_DDA       =0x100D,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_DDHA      =0x100E,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_NNA       =0x100F,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_TA        =0x1010,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_THA       =0x1011,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_DA        =0x1012,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_DHA       =0x1013,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_NA        =0x1014,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_PA        =0x1015,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_PHA       =0x1016,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_BA        =0x1017,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_BHA       =0x1018,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_MA        =0x1019,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_YA        =0x101A,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_RA        =0x101B,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_LA        =0x101C,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_WA        =0x101D,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_SA        =0x101E,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_HA        =0x101F,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_LLA       =0x1020,

    /* Independent vowels */      /* Independent vowels */
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW,  //MYANMAR_IV_A        =0x1021,
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW,  //MYANMAR_IV_SHAN_A   =0x1022,
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW,  //MYANMAR_IV_I        =0x1023,
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW,  //MYANMAR_IV_II       =0x1024,
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW,  //MYANMAR_IV_U        =0x1025,
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW,  //MYANMAR_IV_UU       =0x1026,
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW,  //MYANMAR_IV_E        =0x1027,
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW,  //MYANMAR_IV_MON_E    =0x1028,
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW,  //MYANMAR_IV_O        =0x1029,
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW,  //MYANMAR_IV_AU       =0x102A,

    /* Dependent Vowels  */
    HINDI_VPST | HINDI_SP_RIGHT_JOINER,     //MYANMAR_DV_TALL_AA  =0x102B,
    HINDI_VPST | HINDI_SP_RIGHT_JOINER,     //MYANMAR_DV_AA       =0x102C,
    HINDI_VABV | HINDI_SP_CENTER_T_UP_POS,  //MYANMAR_DV_I        =0x102D,
    HINDI_VABV | HINDI_SP_CENTER_T_UP_POS,  //MYANMAR_DV_II       =0x102E,
    HINDI_VBLW | HINDI_SP_CENTER_T_DOWN_POS,//MYANMAR_DV_U        =0x102F,
    HINDI_VBLW | HINDI_SP_CENTER_T_DOWN_POS,//MYANMAR_DV_UU       =0x1030,
    HINDI_VPRE | HINDI_SP_LEFT_JOINER,          //MYANMAR_DV_E        =0x1031,
    HINDI_A | HINDI_SP_CENTER_T_UP_POS,     //MYANMAR_DV_AI       =0x1032,
    HINDI_VABV | HINDI_SP_CENTER_T_UP_POS,  //MYANMAR_DV_MON_II   =0x1033,
    HINDI_VABV | HINDI_SP_CENTER_T_UP_POS,  //MYANMAR_DV_MON_O    =0x1034,
    HINDI_VABV | HINDI_SP_CENTER_T_UP_POS,  //MYANMAR_DV_E_ABOVE  =0x1035,

    /* Various signs*/
    HINDI_A | HINDI_SP_CENTER_T_UP_POS,     //MYANMAR_S_ANUSVARA  =0x1036,
    HINDI_DB | HINDI_SP_CENTER_T_DOWN_POS,  //MYANMAR_S_DOT_BELOW =0x1037,
    HINDI_V | HINDI_SP_RIGHT_JOINER,                //MYANMAR_S_VISARGA   =0x1038,
    HINDI_HALANT | HINDI_SP_CENTER_T_DOWN_POS, //MYANMAR_S_HALANT    =0x1039,
    HINDI_AS | HINDI_SP_CENTER_T_UP_POS,        //MYANMAR_S_ASAT      =0x103A,

    /* Dependent consonants signs */
    HINDI_MY | HINDI_SP_RIGHT_JOINER,               //MYANMAR_DC_YA       =0x103B,
    HINDI_MR | HINDI_SP_CENTER_T,                       //MYANMAR_DC_RA       =0x103C,
    HINDI_MW | HINDI_SP_CENTER_T_DOWN_POS,  //MYANMAR_DC_WA       =0x103D,
    HINDI_MH | HINDI_SP_CENTER_T_DOWN_POS,  //MYANMAR_DC_HA       =0x103E,

    /* Consonants */
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_GREAT_SA  =0x103F,

    /* Digits */
    HINDI_D0,                                                               //MYANMAR_D_ZERO      =0x1040,
    HINDI_NUM,                                                          //MYANMAR_D_ONE       =0x1041,
    HINDI_NUM,                                                          //MYANMAR_D_TWO       =0x1042,
    HINDI_NUM,                                                          //MYANMAR_D_THREE     =0x1043,
    HINDI_NUM,                                                          //MYANMAR_D_FOUR      =0x1044,
    HINDI_NUM,                                                          //MYANMAR_D_FIVE      =0x1045,
    HINDI_NUM,                                                          //MYANMAR_D_SIX       =0x1046,
    HINDI_NUM,                                                          //MYANMAR_D_SEVEN     =0x1047,
    HINDI_NUM,                                                          //MYANMAR_D_EIGHT     =0x1048,
    HINDI_NUM,                                                          //MYANMAR_D_NINE      =0x1049,

    /* Punctuation */
    HINDI_P,                                                                //MYANMAR_S_LITTLE_SECTION    =0x104A,
    HINDI_P,                                                                //MYANMAR_S_SECTION   =0x104B,

    /* Various signs */
    HINDI_SIGN,                                                         //MYANMAR_S_LOCATIVE  =0x104C,
    HINDI_SIGN,                                                         //MYANMAR_S_COMPLETED =0x104D,
    HINDI_CON | HINDI_SP_NO_T,                          //MYANMAR_S_AFOREMENTIONED    =0x104E,
    HINDI_SIGN,                                                         //MYANMAR_S_GENITIVE  =0x104F,

    /* Pali and Sanskrit extensions */
    HINDI_CON | HINDI_SP_NO_T,                          //MYANMAR_C_SHA       =0x1050,
    HINDI_CON | HINDI_SP_NO_T,                          //MYANMAR_C_SSA       =0x1051,
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW,  //MYANMAR_C_VR        =0x1052,
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW,  //MYANMAR_C_VRR       =0x1053,
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW,  //MYANMAR_C_VL        =0x1054,
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW,  //MYANMAR_C_VLL       =0x1055,
    HINDI_VPST | HINDI_SP_RIGHT_JOINER,     //MYANMAR_C_VS_VR     =0x1056,
    HINDI_VPST | HINDI_SP_RIGHT_JOINER,     //MYANMAR_C_VS_VRR    =0x1057,
    HINDI_VBLW | HINDI_SP_CENTER_T_DOWN_POS,//MYANMAR_C_VS_VL     =0x1058,
    HINDI_VBLW | HINDI_SP_CENTER_T_DOWN_POS,//MYANMAR_C_VS_VLL    =0x1059,

    /* Extensions for Mon */
    HINDI_CON | HINDI_SP_NO_T,                          //MYANMAR_C_MON_NGA   =0x105A,
    HINDI_CON | HINDI_SP_NO_T,                          //MYANMAR_C_MON_JHA   =0x105B,
    HINDI_CON | HINDI_SP_NO_T,                          //MYANMAR_C_MON_BBA   =0x105C,
    HINDI_CON | HINDI_SP_NO_T,                          //MYANMAR_C_MON_BBE   =0x105D,
    HINDI_MY | HINDI_SP_CENTER_T_DOWN_POS,  //MYANMAR_C_CS_MON_NA =0x105E,
    HINDI_MY | HINDI_SP_CENTER_T_DOWN_POS,  //MMYANMAR_C_CS_MON_MA =0x105F,
    HINDI_MH | HINDI_SP_CENTER_T_DOWN_POS,  //MMYANMAR_C_CS_MON_LA =0x1060,

    /* Extensions for S'gaw Karen */
    HINDI_CON | HINDI_SP_NO_T,                          //MYANMAR_C_SGAW_SHA  =0x1061,
    HINDI_VPST | HINDI_SP_RIGHT_JOINER,     //MYANMAR_C_VS_SGAW_EU=0x1062,
    HINDI_PT | HINDI_SP_RIGHT_JOINER,               //MYANMAR_C_SGAW_HATHI=0x1063,
    HINDI_PT | HINDI_SP_RIGHT_JOINER,               //MYANMAR_C_SGAW_KE_PHO   =0x1064,

    /* Extensions for Western Pwo Karen */
    HINDI_CON | HINDI_SP_NO_T,                          //MYANMAR_C_WP_THA    =0x1065,
    HINDI_CON | HINDI_SP_NO_T,                          //MYANMAR_C_WP_PWA    =0x1066,
    HINDI_VPST | HINDI_SP_RIGHT_JOINER,     //MYANMAR_C_VS_WP_EU  =0x1067,
    HINDI_VPST | HINDI_SP_RIGHT_JOINER,     //MYANMAR_C_VS_WP_UE  =0x1068,
    HINDI_PT | HINDI_SP_RIGHT_JOINER,               //MYANMAR_C_VS_WP_T1  =0x1069,
    HINDI_PT | HINDI_SP_RIGHT_JOINER,               //MYANMAR_C_VS_WP_T2  =0x106A,
    HINDI_PT | HINDI_SP_RIGHT_JOINER,               //MYANMAR_C_VS_WP_T3  =0x106B,
    HINDI_PT | HINDI_SP_RIGHT_JOINER,               //MYANMAR_C_VS_WP_T4  =0x106C,
    HINDI_PT | HINDI_SP_RIGHT_JOINER,               //MYANMAR_C_VS_WP_T5  =0x106D,

    /* Extensions for Eastern Pwo Karen */
    HINDI_CON | HINDI_SP_NO_T,                          //MYANMAR_C_EP_NNA    =0x106E,
    HINDI_CON | HINDI_SP_NO_T,                          //MYANMAR_C_EP_YWA    =0x106F,
    HINDI_CON | HINDI_SP_NO_T,                          //MYANMAR_C_EP_GHWA   =0x1070,

    /* Extensions for Geba Karen */
    HINDI_VABV | HINDI_SP_CENTER_T_UP_POS,    //MYANMAR_C_VS_GEBA_I =0x1071,

    /* Extensions for Kayah */
    HINDI_VABV | HINDI_SP_CENTER_T_UP_POS,    //MYANMAR_C_VS_KAYAH_OE   =0x1072,
    HINDI_VABV | HINDI_SP_CENTER_T_UP_POS,    //MYANMAR_C_VS_KAYAH_U    =0x1073,
    HINDI_VABV | HINDI_SP_CENTER_T_UP_POS,    //MYANMAR_C_VS_KAYAH_EE   =0x1074,

    /* Extensions for Shan */
    HINDI_CON | HINDI_SP_NO_T,                          //MYANMAR_C_SHAN_KA   =0x1075,
    HINDI_CON | HINDI_SP_NO_T,                          //MYANMAR_C_SHAN_KHA  =0x1076,
    HINDI_CON | HINDI_SP_NO_T,                          //MYANMAR_C_SHAN_GA   =0x1077,
    HINDI_CON | HINDI_SP_NO_T,                          //MYANMAR_C_SHAN_CA   =0x1078,
    HINDI_CON | HINDI_SP_NO_T,                          //MYANMAR_C_SHAN_ZA   =0x1079,
    HINDI_CON | HINDI_SP_NO_T,                          //MYANMAR_C_SHAN_NYA  =0x107A,
    HINDI_CON | HINDI_SP_NO_T,                          //MYANMAR_C_SHAN_DA   =0x107B,
    HINDI_CON | HINDI_SP_NO_T,                          //MYANMAR_C_SHAN_NA   =0x107C,
    HINDI_CON | HINDI_SP_NO_T,                          //MYANMAR_C_SHAN_PHA  =0x107D,
    HINDI_CON | HINDI_SP_NO_T,                          //MYANMAR_C_SHAN_FA   =0x107E,
    HINDI_CON | HINDI_SP_NO_T,                          //MYANMAR_C_SHAN_BA   =0x107F,
    HINDI_CON | HINDI_SP_NO_T,                          //MYANMAR_C_SHAN_THA  =0x1080,
    HINDI_CON | HINDI_SP_NO_T,                          //MYANMAR_C_SHAN_HA   =0x1081,
    HINDI_MW | HINDI_SP_CENTER_T_DOWN_POS,  //MYANMAR_C_CS_SHAN_WA=0x1082,
    HINDI_VPST | HINDI_SP_RIGHT_JOINER,     //MYANMAR_C_VS_SHAN_AA=0x1083,
    HINDI_VPRE | HINDI_SP_LEFT_JOINER,          //MYANMAR_C_VS_SHAN_E =0x1084,
    HINDI_VABV | HINDI_SP_CENTER_T_UP_POS,  //MYANMAR_C_VS_SHAN_E_ABOVE   =0x1085,
    HINDI_VABV | HINDI_SP_CENTER_T_UP_POS,  //MYANMAR_C_VS_SHAN_FINAL_Y   =0x1086,
    HINDI_V | HINDI_SP_RIGHT_JOINER,                //MYANMAR_C_S_SHAN_T2 =0x1087,
    HINDI_V | HINDI_SP_RIGHT_JOINER,                //MYANMAR_C_S_SHAN_T3 =0x1088,
    HINDI_V | HINDI_SP_RIGHT_JOINER,                //MYANMAR_C_S_SHAN_T5 =0x1089,
    HINDI_V | HINDI_SP_RIGHT_JOINER,                //MYANMAR_C_S_SHAN_T6 =0x108A,
    HINDI_V | HINDI_SP_RIGHT_JOINER,                //MYANMAR_C_S_SHAN_CT2=0x108B,
    HINDI_V | HINDI_SP_RIGHT_JOINER,                //MYANMAR_C_S_SHAN_CT3=0x108C,
    HINDI_V | HINDI_SP_RIGHT_JOINER,                //MYANMAR_C_S_SHAN_CET=0x108D,

    /* Extensions for Rumai Palaung */
    HINDI_CON | HINDI_SP_NO_T,                          //YANMAR_C_RUMAI_FA  =0x108E,
    HINDI_V | HINDI_SP_RIGHT_JOINER,                //MYANMAR_C_S_RUMAI_T5=0x108F,

    /* Shan digits */
    HINDI_NUM,                                                          //MYANMAR_D_SHAN_ZERO =0x1090,
    HINDI_NUM,                                                          //MYANMAR_D_SHAN_ONE  =0x1091,
    HINDI_NUM,                                                          //MYANMAR_D_SHAN_TWO  =0x1092,
    HINDI_NUM,                                                          //MYANMAR_D_SHAN_THREE=0x1093,
    HINDI_NUM,                                                          //MYANMAR_D_SHAN_FOUR =0x1094,
    HINDI_NUM,                                                          //MYANMAR_D_SHAN_FIVE =0x1095,
    HINDI_NUM,                                                          //MYANMAR_D_SHAN_SIX  =0x1096,
    HINDI_NUM,                                                          //MYANMAR_D_SHAN_SEVEN=0x1097,
    HINDI_NUM,                                                          //MYANMAR_D_SHAN_EIGHT=0x1098,
    HINDI_NUM,                                                          //MYANMAR_D_SHAN_NINE =0x1099,

        /* Extensions for Khamti Shan */
    HINDI_V | HINDI_SP_RIGHT_JOINER,                //MYANMAR_C_S_KHAMTI_T1   =0x109A,
    HINDI_V | HINDI_SP_RIGHT_JOINER,                //MYANMAR_C_S_KHAMTI_T3   =0x109B,

    /* Extensions for Aiton and Phake */
    HINDI_V | HINDI_SP_RIGHT_JOINER,                //MYANMAR_C_VS_AITON_A=0x109C,
    HINDI_VABV | HINDI_SP_CENTER_T_UP_POS,  //MYANMAR_C_VS_AITON_AI   =0x109D,

    /* Shan symbols */
    HINDI_SIGN,                                                         //MYANMAR_C_S_SHAN_ONE=0x109E,
    HINDI_SIGN                                                          //MYANMAR_C_S_SHAN_EXCLAMATION    =0x109F,
};

const U8 g_MyanmarExtACharTypeArray[] =
{
    /* Khamti Shan consonants */
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_KHAMTI_GA =0xAA60,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_KHAMTI_CA =0xAA61,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_KHAMTI_CHA=0xAA62,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_KHAMTI_JA =0xAA63,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_KHAMTI_JHA=0xAA64,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_KHAMTI_NYA=0xAA65,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_KHAMTI_TTA=0xAA66,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_KHAMTI_TTHA   =0xAA67,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_KHAMTI_DDA=0xAA68,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_KHAMTI_DDHA   =0xAA69,
    HINDI_CON | HINDI_SP_NO_T,              //      MYANMAR_C_KHAMTI_DHA=0xAA6A,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_KHAMTI_NA =0xAA6B,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_KHAMTI_SA =0xAA6C,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_KHAMTI_HA =0xAA6D,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_KHAMTI_HHA=0xAA6E,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_KHAMTI_FA =0xAA6F,
    HINDI_SIGN,                                                         //MYANMAR_C_KHAMTI_REDUPLICATION  =0xAA70,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_KHAMTI_XA =0xAA71,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_KHAMTI_ZA =0xAA72,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_KHAMTI_RA =0xAA73,

    /* Khamti Shan logograms */
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_LOGO_KHAMTI_OAY   =0xAA74,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_LOGO_KHAMTI_QN    =0xAA75,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_LOGO_KHAMTI_HM    =0xAA76,

    /* Aiton symbols and letters */
    HINDI_SIGN,                                                         //MYANMAR_C_S_AITON_EXCLAMATION   =0xAA77,
    HINDI_SIGN,                                                         //MYANMAR_C_S_AITON_ONE   =0xAA78,
    HINDI_SIGN,                                                         //MYANMAR_C_S_AITON_TWO   =0xAA79,
    HINDI_CON | HINDI_SP_NO_T,              //YANMAR_C_AITON_RA  =0xAA7A,

    /* Pa'o Karen tone mark */
    HINDI_PT | HINDI_SP_RIGHT_JOINER,               //MYANMAR_C_S_PAO_T   =0xAA7B,

    /* Tai Laing tone marks */
    HINDI_PT | HINDI_SP_CENTER_T_UP_POS,        //MYANMAR_C_S_TAI_T2  =0xAA7C,
    HINDI_PT | HINDI_SP_RIGHT_JOINER,               //MYANMAR_C_S_TAI_T5  =0xAA7D,

    /* Shwe Palaung letters */
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_SHWE_CHA  =0xAA7E,
    HINDI_CON | HINDI_SP_NO_T               //MYANMAR_C_SHWE_SHA  =0xAA7F,
};

const U8 g_MyanmarExtBCharTypeArray[] =
{
    /* Additions for Shan Pali */
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_SHAN_GHA  =0xA9E0,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_SHAN_CHA  =0xA9E1,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_SHAN_JHA  =0xA9E2,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_SHAN_NNA  =0xA9E3,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_SHAN_BHA  =0xA9E4,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_S_SHAN_SAW=0xA9E5,

    /* Reduplication mark */
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_SHAN_REDUPLICATION =0xA9E6,

    /* Tai Laing consonants */
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_TAI_NYA   =0xA9E7,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_TAI_FA    =0xA9E8,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_TAI_GA    =0xA9E9,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_TAI_GHA   =0xA9EA,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_TAI_JA    =0xA9EB,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_TAI_JHA   =0xA9EC,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_TAI_DDA   =0xA9ED,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_TAI_DDHA  =0xA9EE,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_TAI_NNA   =0xA9EF,

    /* Tai Laing digits */
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_D_TAI_ZERO  =0xA9F0,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_D_TAI_ONE   =0xA9F1,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_D_TAI_TWO   =0xA9F2,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_D_TAI_THREE =0xA9F3,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_D_TAI_FOUR  =0xA9F4,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_D_TAI_FIVE  =0xA9F5,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_D_TAI_SIX   =0xA9F6,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_D_TAI_SEVEN =0xA9F7,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_D_TAI_EIGHT =0xA9F8,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_D_TAI_NINE  =0xA9F9,

    /* Tai Laing consonants */
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_TAI_LLA   =0xA9FA,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_TAI_DA    =0xA9FB,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_TAI_DHA   =0xA9FC,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_TAI_BA    =0xA9FD,
    HINDI_CON | HINDI_SP_NO_T,              //MYANMAR_C_TAI_BHA   =0xA9FE,

    HINDI_INVALID
};
#else
const U8 g_MyanmarCharTypeArray[] =
{
    /*  CONSONANT'S TABLES    */            /* Consonants */
    HINDI_CON,              //MYANMAR_C_KA        =0x1000,
    HINDI_CON,              //MYANMAR_C_KHA       =0x1001,
    HINDI_CON,              //MYANMAR_C_GA        =0x1002,
    HINDI_CON,              //MYANMAR_C_GHA       =0x1003,
    HINDI_CON,              //MYANMAR_C_NGA       =0x1004,
    HINDI_CON,              //MYANMAR_C_CA        =0x1005,
    HINDI_CON,              //MYANMAR_C_CHA       =0x1006,
    HINDI_CON,              //MYANMAR_C_JA        =0x1007,
    HINDI_CON,              //MYANMAR_C_JHA       =0x1008,
    HINDI_CON,              //MYANMAR_C_NYA       =0x1009,
    HINDI_CON,              //MYANMAR_C_NNYA      =0x100A,
    HINDI_CON,              //MYANMAR_C_TTA       =0x100B,
    HINDI_CON,              //MYANMAR_C_TTHA      =0x100C,
    HINDI_CON,              //MYANMAR_C_DDA       =0x100D,
    HINDI_CON,              //MYANMAR_C_DDHA      =0x100E,
    HINDI_CON,              //MYANMAR_C_NNA       =0x100F,
    HINDI_CON,              //MYANMAR_C_TA        =0x1010,
    HINDI_CON,              //MYANMAR_C_THA       =0x1011,
    HINDI_CON,              //MYANMAR_C_DA        =0x1012,
    HINDI_CON,              //MYANMAR_C_DHA       =0x1013,
    HINDI_CON,              //MYANMAR_C_NA        =0x1014,
    HINDI_CON,              //MYANMAR_C_PA        =0x1015,
    HINDI_CON,              //MYANMAR_C_PHA       =0x1016,
    HINDI_CON,              //MYANMAR_C_BA        =0x1017,
    HINDI_CON,              //MYANMAR_C_BHA       =0x1018,
    HINDI_CON,              //MYANMAR_C_MA        =0x1019,
    HINDI_CON,              //MYANMAR_C_YA        =0x101A,
    HINDI_CON,              //MYANMAR_C_RA        =0x101B,
    HINDI_CON,              //MYANMAR_C_LA        =0x101C,
    HINDI_CON,              //MYANMAR_C_WA        =0x101D,
    HINDI_CON,              //MYANMAR_C_SA        =0x101E,
    HINDI_CON,              //MYANMAR_C_HA        =0x101F,
    HINDI_CON,              //MYANMAR_C_LLA       =0x1020,

    /* Independent vowels */      /* Independent vowels */
    HINDI_INDVOW,           //MYANMAR_IV_A        =0x1021,
    HINDI_INDVOW,           //MYANMAR_IV_SHAN_A   =0x1022,
    HINDI_INDVOW,           //MYANMAR_IV_I        =0x1023,
    HINDI_INDVOW,           //MYANMAR_IV_II       =0x1024,
    HINDI_INDVOW,           //MYANMAR_IV_U        =0x1025,
    HINDI_INDVOW,           //MYANMAR_IV_UU       =0x1026,
    HINDI_INDVOW,           //MYANMAR_IV_E        =0x1027,
    HINDI_INDVOW,           //MYANMAR_IV_MON_E    =0x1028,
    HINDI_INDVOW,           //MYANMAR_IV_O        =0x1029,
    HINDI_INDVOW,           //MYANMAR_IV_AU       =0x102A,

    /* Dependent Vowels  */
    HINDI_VPST,             //MYANMAR_DV_TALL_AA  =0x102B,
    HINDI_VPST,             //MYANMAR_DV_AA       =0x102C,
    HINDI_VABV,             //MYANMAR_DV_I        =0x102D,
    HINDI_VABV,             //MYANMAR_DV_II       =0x102E,
    HINDI_VBLW,             //MYANMAR_DV_U        =0x102F,
    HINDI_VBLW,             //MYANMAR_DV_UU       =0x1030,
    HINDI_VPRE,             //MYANMAR_DV_E        =0x1031,
    HINDI_A,                //MYANMAR_DV_AI       =0x1032,
    HINDI_VABV,             //MYANMAR_DV_MON_II   =0x1033,
    HINDI_VABV,             //MYANMAR_DV_MON_O    =0x1034,
    HINDI_VABV,             //MYANMAR_DV_E_ABOVE  =0x1035,

    /* Various signs*/
    HINDI_A,                //MYANMAR_S_ANUSVARA  =0x1036,
    HINDI_DB,               //MYANMAR_S_DOT_BELOW =0x1037,
    HINDI_V,                //MYANMAR_S_VISARGA   =0x1038,
    HINDI_HALANT,           //MYANMAR_S_HALANT    =0x1039,
    HINDI_AS,               //MYANMAR_S_ASAT      =0x103A,

    /* Dependent consonants signs */
    HINDI_MY,               //MYANMAR_DC_YA       =0x103B,
    HINDI_MR,               //MYANMAR_DC_RA       =0x103C,
    HINDI_MW,               //MYANMAR_DC_WA       =0x103D,
    HINDI_MH,               //MYANMAR_DC_HA       =0x103E,

    /* Consonants */
    HINDI_CON,              //MYANMAR_C_GREAT_SA  =0x103F,

    /* Digits */
    HINDI_D0,               //MYANMAR_D_ZERO      =0x1040,
    HINDI_NUM,              //MYANMAR_D_ONE       =0x1041,
    HINDI_NUM,              //MYANMAR_D_TWO       =0x1042,
    HINDI_NUM,              //MYANMAR_D_THREE     =0x1043,
    HINDI_NUM,              //MYANMAR_D_FOUR      =0x1044,
    HINDI_NUM,              //MYANMAR_D_FIVE      =0x1045,
    HINDI_NUM,              //MYANMAR_D_SIX       =0x1046,
    HINDI_NUM,              //MYANMAR_D_SEVEN     =0x1047,
    HINDI_NUM,              //MYANMAR_D_EIGHT     =0x1048,
    HINDI_NUM,              //MYANMAR_D_NINE      =0x1049,

    /* Punctuation */
    HINDI_P,                //MYANMAR_S_LITTLE_SECTION    =0x104A,
    HINDI_P,                //MYANMAR_S_SECTION   =0x104B,

    /* Various signs */
    HINDI_SIGN,             //MYANMAR_S_LOCATIVE  =0x104C,
    HINDI_SIGN,             //MYANMAR_S_COMPLETED =0x104D,
    HINDI_CON,              //MYANMAR_S_AFOREMENTIONED    =0x104E,
    HINDI_SIGN,             //MYANMAR_S_GENITIVE  =0x104F,

    /* Pali and Sanskrit extensions */
    HINDI_CON,              //MYANMAR_C_SHA       =0x1050,
    HINDI_CON,              //MYANMAR_C_SSA       =0x1051,
    HINDI_INDVOW,           //MYANMAR_C_VR        =0x1052,
    HINDI_INDVOW,           //MYANMAR_C_VRR       =0x1053,
    HINDI_INDVOW,           //MYANMAR_C_VL        =0x1054,
    HINDI_INDVOW,           //MYANMAR_C_VLL       =0x1055,
    HINDI_VPST,             //MYANMAR_C_VS_VR     =0x1056,
    HINDI_VPST,             //MYANMAR_C_VS_VRR    =0x1057,
    HINDI_VBLW,             //MYANMAR_C_VS_VL     =0x1058,
    HINDI_VBLW,             //MYANMAR_C_VS_VLL    =0x1059,

    /* Extensions for Mon */
    HINDI_CON,              //MYANMAR_C_MON_NGA   =0x105A,
    HINDI_CON,              //MYANMAR_C_MON_JHA   =0x105B,
    HINDI_CON,              //MYANMAR_C_MON_BBA   =0x105C,
    HINDI_CON,              //MYANMAR_C_MON_BBE   =0x105D,
    HINDI_MY,               //MYANMAR_C_CS_MON_NA =0x105E,
    HINDI_MY,               //MMYANMAR_C_CS_MON_MA =0x105F,
    HINDI_MH,               //MMYANMAR_C_CS_MON_LA =0x1060,

    /* Extensions for S'gaw Karen */
    HINDI_CON,              //MYANMAR_C_SGAW_SHA  =0x1061,
    HINDI_VPST,             //MYANMAR_C_VS_SGAW_EU=0x1062,
    HINDI_PT,               //MYANMAR_C_SGAW_HATHI=0x1063,
    HINDI_PT,               //MYANMAR_C_SGAW_KE_PHO   =0x1064,

    /* Extensions for Western Pwo Karen */
    HINDI_CON,              //MYANMAR_C_WP_THA    =0x1065,
    HINDI_CON,              //MYANMAR_C_WP_PWA    =0x1066,
    HINDI_VPST,             //MYANMAR_C_VS_WP_EU  =0x1067,
    HINDI_VPST,             //MYANMAR_C_VS_WP_UE  =0x1068,
    HINDI_PT,               //MYANMAR_C_VS_WP_T1  =0x1069,
    HINDI_PT,               //MYANMAR_C_VS_WP_T2  =0x106A,
    HINDI_PT,               //MYANMAR_C_VS_WP_T3  =0x106B,
    HINDI_PT,               //MYANMAR_C_VS_WP_T4  =0x106C,
    HINDI_PT,               //MYANMAR_C_VS_WP_T5  =0x106D,

    /* Extensions for Eastern Pwo Karen */
    HINDI_CON,              //MYANMAR_C_EP_NNA    =0x106E,
    HINDI_CON,              //MYANMAR_C_EP_YWA    =0x106F,
    HINDI_CON,              //MYANMAR_C_EP_GHWA   =0x1070,

    /* Extensions for Geba Karen */
    HINDI_VABV,             //MYANMAR_C_VS_GEBA_I =0x1071,

    /* Extensions for Kayah */
    HINDI_VABV,             //MYANMAR_C_VS_KAYAH_OE   =0x1072,
    HINDI_VABV,             //MYANMAR_C_VS_KAYAH_U    =0x1073,
    HINDI_VABV,             //MYANMAR_C_VS_KAYAH_EE   =0x1074,

    /* Extensions for Shan */
    HINDI_CON,              //MYANMAR_C_SHAN_KA   =0x1075,
    HINDI_CON,              //MYANMAR_C_SHAN_KHA  =0x1076,
    HINDI_CON,              //MYANMAR_C_SHAN_GA   =0x1077,
    HINDI_CON,              //MYANMAR_C_SHAN_CA   =0x1078,
    HINDI_CON,              //MYANMAR_C_SHAN_ZA   =0x1079,
    HINDI_CON,              //MYANMAR_C_SHAN_NYA  =0x107A,
    HINDI_CON,              //MYANMAR_C_SHAN_DA   =0x107B,
    HINDI_CON,              //MYANMAR_C_SHAN_NA   =0x107C,
    HINDI_CON,              //MYANMAR_C_SHAN_PHA  =0x107D,
    HINDI_CON,              //MYANMAR_C_SHAN_FA   =0x107E,
    HINDI_CON,              //MYANMAR_C_SHAN_BA   =0x107F,
    HINDI_CON,              //MYANMAR_C_SHAN_THA  =0x1080,
    HINDI_CON,              //MYANMAR_C_SHAN_HA   =0x1081,
    HINDI_MW,               //MYANMAR_C_CS_SHAN_WA=0x1082,
    HINDI_VPST,             //MYANMAR_C_VS_SHAN_AA=0x1083,
    HINDI_VPRE,             //MYANMAR_C_VS_SHAN_E =0x1084,
    HINDI_VABV,             //MYANMAR_C_VS_SHAN_E_ABOVE   =0x1085,
    HINDI_VABV,             //MYANMAR_C_VS_SHAN_FINAL_Y   =0x1086,
    HINDI_V,                //MYANMAR_C_S_SHAN_T2 =0x1087,
    HINDI_V,                //MYANMAR_C_S_SHAN_T3 =0x1088,
    HINDI_V,                //MYANMAR_C_S_SHAN_T5 =0x1089,
    HINDI_V,                //MYANMAR_C_S_SHAN_T6 =0x108A,
    HINDI_V,                //MYANMAR_C_S_SHAN_CT2=0x108B,
    HINDI_V,                //MYANMAR_C_S_SHAN_CT3=0x108C,
    HINDI_V,                //MYANMAR_C_S_SHAN_CET=0x108D,

    /* Extensions for Rumai Palaung */
    HINDI_CON,              //YANMAR_C_RUMAI_FA  =0x108E,
    HINDI_V,                //MYANMAR_C_S_RUMAI_T5=0x108F,

    /* Shan digits */
    HINDI_NUM,              //MYANMAR_D_SHAN_ZERO =0x1090,
    HINDI_NUM,              //MYANMAR_D_SHAN_ONE  =0x1091,
    HINDI_NUM,              //MYANMAR_D_SHAN_TWO  =0x1092,
    HINDI_NUM,              //MYANMAR_D_SHAN_THREE=0x1093,
    HINDI_NUM,              //MYANMAR_D_SHAN_FOUR =0x1094,
    HINDI_NUM,              //MYANMAR_D_SHAN_FIVE =0x1095,
    HINDI_NUM,              //MYANMAR_D_SHAN_SIX  =0x1096,
    HINDI_NUM,              //MYANMAR_D_SHAN_SEVEN=0x1097,
    HINDI_NUM,              //MYANMAR_D_SHAN_EIGHT=0x1098,
    HINDI_NUM,              //MYANMAR_D_SHAN_NINE =0x1099,

    /* Extensions for Khamti Shan */
    HINDI_V,                //MYANMAR_C_S_KHAMTI_T1   =0x109A,
    HINDI_V,                //MYANMAR_C_S_KHAMTI_T3   =0x109B,

    /* Extensions for Aiton and Phake */
    HINDI_V,                //MYANMAR_C_VS_AITON_A=0x109C,
    HINDI_VABV,             //MYANMAR_C_VS_AITON_AI   =0x109D,

    /* Shan symbols */
    HINDI_SIGN,             //MYANMAR_C_S_SHAN_ONE=0x109E,
    HINDI_SIGN              //MYANMAR_C_S_SHAN_EXCLAMATION    =0x109F,
};

const U8 g_MyanmarExtACharTypeArray[] =
{
    /* Khamti Shan consonants */
    HINDI_CON,              //MYANMAR_C_KHAMTI_GA =0xAA60,
    HINDI_CON,              //MYANMAR_C_KHAMTI_CA =0xAA61,
    HINDI_CON,              //MYANMAR_C_KHAMTI_CHA=0xAA62,
    HINDI_CON,              //MYANMAR_C_KHAMTI_JA =0xAA63,
    HINDI_CON,              //MYANMAR_C_KHAMTI_JHA=0xAA64,
    HINDI_CON,              //MYANMAR_C_KHAMTI_NYA=0xAA65,
    HINDI_CON,              //MYANMAR_C_KHAMTI_TTA=0xAA66,
    HINDI_CON,              //MYANMAR_C_KHAMTI_TTHA   =0xAA67,
    HINDI_CON,              //MYANMAR_C_KHAMTI_DDA=0xAA68,
    HINDI_CON,              //MYANMAR_C_KHAMTI_DDHA   =0xAA69,
    HINDI_CON,              //MYANMAR_C_KHAMTI_DHA=0xAA6A,
    HINDI_CON,              //MYANMAR_C_KHAMTI_NA =0xAA6B,
    HINDI_CON,              //MYANMAR_C_KHAMTI_SA =0xAA6C,
    HINDI_CON,              //MYANMAR_C_KHAMTI_HA =0xAA6D,
    HINDI_CON,              //MYANMAR_C_KHAMTI_HHA=0xAA6E,
    HINDI_CON,              //MYANMAR_C_KHAMTI_FA =0xAA6F,
    HINDI_SIGN,             //MYANMAR_C_KHAMTI_REDUPLICATION  =0xAA70,
    HINDI_CON,              //MYANMAR_C_KHAMTI_XA =0xAA71,
    HINDI_CON,              //MYANMAR_C_KHAMTI_ZA =0xAA72,
    HINDI_CON,              //MYANMAR_C_KHAMTI_RA =0xAA73,

    /* Khamti Shan logograms */
    HINDI_CON,              //MYANMAR_C_LOGO_KHAMTI_OAY   =0xAA74,
    HINDI_CON,              //MYANMAR_C_LOGO_KHAMTI_QN    =0xAA75,
    HINDI_CON,              //MYANMAR_C_LOGO_KHAMTI_HM    =0xAA76,

    /* Aiton symbols and letters */
    HINDI_SIGN,             //MYANMAR_C_S_AITON_EXCLAMATION   =0xAA77,
    HINDI_SIGN,             //MYANMAR_C_S_AITON_ONE   =0xAA78,
    HINDI_SIGN,             //MYANMAR_C_S_AITON_TWO   =0xAA79,
    HINDI_CON,              //YANMAR_C_AITON_RA  =0xAA7A,

    /* Pa'o Karen tone mark */
    HINDI_PT,               //MYANMAR_C_S_PAO_T   =0xAA7B,

    /* Tai Laing tone marks */
    HINDI_PT,               //MYANMAR_C_S_TAI_T2  =0xAA7C,
    HINDI_PT,               //MYANMAR_C_S_TAI_T5  =0xAA7D,

    /* Shwe Palaung letters */
    HINDI_CON,              //MYANMAR_C_SHWE_CHA  =0xAA7E,
    HINDI_CON               //MYANMAR_C_SHWE_SHA  =0xAA7F,
};

const U8 g_MyanmarExtBCharTypeArray[] =
{
    /* Additions for Shan Pali */
    HINDI_CON,              //MYANMAR_C_SHAN_GHA  =0xA9E0,
    HINDI_CON,              //MYANMAR_C_SHAN_CHA  =0xA9E1,
    HINDI_CON,              //MYANMAR_C_SHAN_JHA  =0xA9E2,
    HINDI_CON,              //MYANMAR_C_SHAN_NNA  =0xA9E3,
    HINDI_CON,              //MYANMAR_C_SHAN_BHA  =0xA9E4,
    HINDI_CON,              //MYANMAR_C_S_SHAN_SAW=0xA9E5,

    /* Reduplication mark */
    HINDI_CON,              //MYANMAR_C_SHAN_REDUPLICATION =0xA9E6,

    /* Tai Laing consonants */
    HINDI_CON,              //MYANMAR_C_TAI_NYA   =0xA9E7,
    HINDI_CON,              //MYANMAR_C_TAI_FA    =0xA9E8,
    HINDI_CON,              //MYANMAR_C_TAI_GA    =0xA9E9,
    HINDI_CON,              //MYANMAR_C_TAI_GHA   =0xA9EA,
    HINDI_CON,              //MYANMAR_C_TAI_JA    =0xA9EB,
    HINDI_CON,              //MYANMAR_C_TAI_JHA   =0xA9EC,
    HINDI_CON,              //MYANMAR_C_TAI_DDA   =0xA9ED,
    HINDI_CON,              //MYANMAR_C_TAI_DDHA  =0xA9EE,
    HINDI_CON,              //MYANMAR_C_TAI_NNA   =0xA9EF,

    /* Tai Laing digits */
    HINDI_CON,              //MYANMAR_D_TAI_ZERO  =0xA9F0,
    HINDI_CON,              //MYANMAR_D_TAI_ONE   =0xA9F1,
    HINDI_CON,              //MYANMAR_D_TAI_TWO   =0xA9F2,
    HINDI_CON,              //MYANMAR_D_TAI_THREE =0xA9F3,
    HINDI_CON,              //MYANMAR_D_TAI_FOUR  =0xA9F4,
    HINDI_CON,              //MYANMAR_D_TAI_FIVE  =0xA9F5,
    HINDI_CON,              //MYANMAR_D_TAI_SIX   =0xA9F6,
    HINDI_CON,              //MYANMAR_D_TAI_SEVEN =0xA9F7,
    HINDI_CON,              //MYANMAR_D_TAI_EIGHT =0xA9F8,
    HINDI_CON,              //MYANMAR_D_TAI_NINE  =0xA9F9,

    /* Tai Laing consonants */
    HINDI_CON,              //MYANMAR_C_TAI_LLA   =0xA9FA,
    HINDI_CON,              //MYANMAR_C_TAI_DA    =0xA9FB,
    HINDI_CON,              //MYANMAR_C_TAI_DHA   =0xA9FC,
    HINDI_CON,              //MYANMAR_C_TAI_BA    =0xA9FD,
    HINDI_CON,              //MYANMAR_C_TAI_BHA   =0xA9FE,

    HINDI_INVALID
};
#endif

const HindiFeatureRecord_t _g_sMyanmarFeatureMap[] =
{
    /*HINDI_FEATURE_LOCL*/  {HINDI_FEATURE_LOCL, _HindiLoclFeatureMask},
    /*HINDI_FEATURE_RPHF*/  {HINDI_FEATURE_RPHF, _HindiRphfFeatureMask},
    /*HINDI_FEATURE_PREF*/  {HINDI_FEATURE_PREF, _HindiPrefFeatureMask},
    /*HINDI_FEATURE_BLWF*/  {HINDI_FEATURE_BLWF, _HindiBlwfFeatureMask},
    /*HINDI_FEATURE_PSTF*/  {HINDI_FEATURE_PSTF, _HindiPstfFeatureMask},
    /*HINDI_FEATURE_PRES*/  {HINDI_FEATURE_PRES, _HindiPresFeatureMask},
    /*HINDI_FEATURE_ABVS*/  {HINDI_FEATURE_ABVS, _HindiAbvsFeatureMask},
    /*HINDI_FEATURE_BLWS*/  {HINDI_FEATURE_BLWS, _HindiBlwsFeatureMask},
    /*HINDI_FEATURE_PSTS*/  {HINDI_FEATURE_PSTS, _HindiPstsFeatureMask},
    /*HINDI_FEATURE_ABVM*/ {HINDI_FEATURE_ABVM, _HindiAbvmFeatureMask},
    /*HINDI_FEATURE_BLWM*/ {HINDI_FEATURE_BLWM, _HindiBlwmFeatureMask},
    /*HINDI_FEATURE_DIST*/ {HINDI_FEATURE_DIST, _HindiDistFeatureMask},
    /*HINDI_FEATURE_MARK*/ {HINDI_FEATURE_MARK, _HindiMarkFeatureMask},
    /*HINDI_FEATURE_MKMK*/ {HINDI_FEATURE_MKMK, _HindiMkmkFeatureMask}
};
const U16 _g_u16MyanmarFeatureCount = (sizeof(_g_sMyanmarFeatureMap)/sizeof(HindiFeatureRecord_t));

static U16 _msAPI_MLE_FontMyanmarGetCluster( HindiScript_e eScript, const U16 *pu16Txt, U32 u32InLen, U16 *pu16Cluster, U16 u16BufferSize, U16 *pu16ConsumedCount, U16 *pu16SeqInCluster, BOOLEAN bIsDispStr, U32 *pu32FeatureTags );
static HindiCharacter_e _msAPI_MLE_FontMyanmarGetCharType( U16 u16Character );
static U32 _msAPI_MLE_FontMyanmarSetFeature( U32 u32FeatureTags, HindiFeature_e eFeature );
static U16 _msAPI_MLE_FontMyanmarGetFeatureMap( const HindiFeatureRecord_t **ppasFeatureMap );
static BOOLEAN _msAPI_MLE_FontMyanmarCharIsBlwf( U16 u16FirstChar, U16 u16SecondChar );
static U16 _msAPI_MLE_FontMyanmarRefineCluster( HindiScript_e eScript, const U16 *pu16InTxt, U32 u32InLen, U32 u32Offset, U16 *pu16Cluster, U16 *pu16CluserSize, U16 u16ClusterOffset, BOOLEAN bIsDispStr, U32 *pu32Features, const U16 *pu16OriginTxt, U32 u32OriginOffset);

static S16 s16BaseGlyphIndex = -1;
static S16 s16MRIndex = -1;
static S16 s16PreBaseVowelIndex = -1;
static U16 u16VPreCount = 0;
static S16 s16AnusvaraIndex = -1;
static U16 u16ACount = 0;
static S16 s16VBlwIndex = -1;
static U16 u16VBlwCount = 0;
static BOOLEAN bKinziFound = FALSE;

__SLDPM_FREE__ const HindiTable_t g_mymrTable =
{
    HINDI_SCRIPT_MYMR,
    MYANMAR_C_KA,
    MYANMAR_C_S_SHAN_EXCLAMATION,
    &_msAPI_MLE_FontMyanmarGetCluster,
    &_msAPI_MLE_FontMyanmarRefineCluster,
    NULL,//&_msAPI_MLE_FontMyanmarGetNextCodeXOffset,
    NULL,//&_msAPI_MLE_FontMyanmarCharIsRA,
    NULL,//&_msAPI_MLE_FontMyanmarCharIsHalant,
    NULL,//&_FontBengCharIsNukta,
    NULL,//&_FontTeluguCharIsBindu,
    NULL,//&_msAPI_MLE_FontMyanmarCharWithNukta,
    NULL,//&_FontBengCharIsNoHalfCon,
    NULL,//&_FontBengCharIsFollowingZWJ,
    NULL,//&_msAPI_MLE_FontMyanmarGetTwoWordLeftChar,
    NULL,//&_msAPI_MLE_FontMyanmarGetTwoWordRightChar,
    &_msAPI_MLE_FontMyanmarGetCharType,
    NULL,//&_msAPI_MLE_FontMyanmarGetCharSpecialType,
    NULL,//&_FontBengGetCharOtherType,
    &_msAPI_MLE_FontMyanmarCharIsBlwf,
    NULL,//&_msAPI_MLE_FontMyanmarCharIsPstf,
    NULL,//&_FontBengCharIsLigated,
    NULL,//&_msAPI_MLE_FontMyanmarStrWithAkhand,
    &_msAPI_MLE_FontMyanmarSetFeature,
    &_msAPI_MLE_FontMyanmarGetFeatureMap,
    NULL,//&_FontBengCharIsSign,
    NULL,//&_FontBengCharIsComposed,
    NULL,//&_msAPI_MLE_FontMyanmarFeatureWithRphf,
    NULL,//&_msAPI_MLE_FontMyanmarFeatureWithBlwf
};

__SLDPM_FREE__ const HindiTable_t g_mymrExtATable =
{
    HINDI_SCRIPT_MYMR,
    MYANMAR_C_KHAMTI_GA,
    MYANMAR_C_SHWE_SHA,
    &_msAPI_MLE_FontMyanmarGetCluster,
    &_msAPI_MLE_FontMyanmarRefineCluster,
    NULL,//&_msAPI_MLE_FontMyanmarGetNextCodeXOffset,
    NULL,//&_msAPI_MLE_FontMyanmarCharIsRA,
    NULL,//&_msAPI_MLE_FontMyanmarCharIsHalant,
    NULL,//&_FontBengCharIsNukta,
    NULL,//&_FontTeluguCharIsBindu,
    NULL,//&_msAPI_MLE_FontMyanmarCharWithNukta,
    NULL,//&_FontBengCharIsNoHalfCon,
    NULL,//&_FontBengCharIsFollowingZWJ,
    NULL,//&_msAPI_MLE_FontMyanmarGetTwoWordLeftChar,
    NULL,//&_msAPI_MLE_FontMyanmarGetTwoWordRightChar,
    &_msAPI_MLE_FontMyanmarGetCharType,
    NULL,//&_msAPI_MLE_FontMyanmarGetCharSpecialType,
    NULL,//&_FontBengGetCharOtherType,
    &_msAPI_MLE_FontMyanmarCharIsBlwf,
    NULL,//&_msAPI_MLE_FontMyanmarCharIsPstf,
    NULL,//&_FontBengCharIsLigated,
    NULL,//&_msAPI_MLE_FontMyanmarStrWithAkhand,
    &_msAPI_MLE_FontMyanmarSetFeature,
    &_msAPI_MLE_FontMyanmarGetFeatureMap,
    NULL,//&_FontBengCharIsSign,
    NULL,//&_FontBengCharIsComposed,
    NULL,//&_msAPI_MLE_FontMyanmarFeatureWithRphf,
    NULL,//&_msAPI_MLE_FontMyanmarFeatureWithBlwf
};

__SLDPM_FREE__ const HindiTable_t g_mymrExtBTable =
{
    HINDI_SCRIPT_MYMR,
    MYANMAR_C_SHAN_GHA,
    MYANMAR_C_TAI_BHA,
    &_msAPI_MLE_FontMyanmarGetCluster,
    &_msAPI_MLE_FontMyanmarRefineCluster,
    NULL,//&_msAPI_MLE_FontMyanmarGetNextCodeXOffset,
    NULL,//&_msAPI_MLE_FontMyanmarCharIsRA,
    NULL,//&_msAPI_MLE_FontMyanmarCharIsHalant,
    NULL,//&_FontBengCharIsNukta,
    NULL,//&_FontTeluguCharIsBindu,
    NULL,//&_msAPI_MLE_FontMyanmarCharWithNukta,
    NULL,//&_FontBengCharIsNoHalfCon,
    NULL,//&_FontBengCharIsFollowingZWJ,
    NULL,//&_msAPI_MLE_FontMyanmarGetTwoWordLeftChar,
    NULL,//&_msAPI_MLE_FontMyanmarGetTwoWordRightChar,
    &_msAPI_MLE_FontMyanmarGetCharType,
    NULL,//&_msAPI_MLE_FontMyanmarGetCharSpecialType,
    NULL,//&_FontBengGetCharOtherType,
    &_msAPI_MLE_FontMyanmarCharIsBlwf,
    NULL,//&_msAPI_MLE_FontMyanmarCharIsPstf,
    NULL,//&_FontBengCharIsLigated,
    NULL,//&_msAPI_MLE_FontMyanmarStrWithAkhand,
    &_msAPI_MLE_FontMyanmarSetFeature,
    &_msAPI_MLE_FontMyanmarGetFeatureMap,
    NULL,//&_FontBengCharIsSign,
    NULL,//&_FontBengCharIsComposed,
    NULL,//&_msAPI_MLE_FontMyanmarFeatureWithRphf,
    NULL,//&_msAPI_MLE_FontMyanmarFeatureWithBlwf
};

static U16 _msAPI_MLE_FontMyanmarGetCluster( HindiScript_e eScript, const U16 *pu16Txt, U32 u32InLen, U16 *pu16Cluster, U16 u16BufferSize, U16 *pu16ConsumedCount, U16 *pu16SeqInCluster, BOOLEAN bIsDispStr, U32 *pu32FeatureTags )
{
    U16 u16Character = 0;
    MyanmarParserState_e eClusterState = CLUSTER_SIMPLE;
    HindiCharacter_e eType = HINDI_INVALID;
    U16 u16Index = 0;
    U16 u16ClusterSize = 0;
    U8 bExit = FALSE, bErrExit = FALSE;

    eScript = eScript;
    bIsDispStr = bIsDispStr;

    *pu16ConsumedCount = 0;

    s16BaseGlyphIndex = -1;
    s16MRIndex = -1;
    s16PreBaseVowelIndex = -1;
    u16VPreCount = 0;
    s16AnusvaraIndex = -1;
    u16ACount = 0;
    s16VBlwIndex = -1;
    u16VBlwCount = 0;
    bKinziFound = FALSE;

    while( (u16Index < u32InLen) && ( bExit == FALSE ) && ( bErrExit == FALSE ) && ( *pu16ConsumedCount <= u32InLen ) )
    {
        u16Character = pu16Txt[u16Index];
        eType = _msAPI_MLE_FontMyanmarGetCharType(u16Character);
        switch(eType)
        {
        case HINDI_P:
        case HINDI_SIGN:
        case HINDI_R:   //Reserved characters
        case HINDI_WJ:    //Word Joiner
        case HINDI_WS:    //White Space
        //case HINDI_O:   //Script Common characters
        case HINDI_INVALID:
        case HINDI_D0:
            if ( eClusterState != CLUSTER_SIMPLE )
            {
                bErrExit = TRUE;
                break;
            }

            eClusterState = CLUSTER_SIMPLE;
            {
                //Found cluster with only one character
                u16ClusterSize = 0;

                bExit = TRUE;

                _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
                _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            }
            break;

        case HINDI_CON:
            if ( ( eClusterState == CLUSTER_SIMPLE ) && ( (u32InLen - u16Index) >= 3 ) )
            {
                switch( u16Character )
                {
                case MYANMAR_C_NGA:
                case MYANMAR_C_RA:
                case MYANMAR_C_MON_NGA:
                    if ( ( pu16Txt[u16Index+1] == MYANMAR_S_ASAT ) && ( pu16Txt[u16Index+2] == MYANMAR_S_HALANT ) )
                    {
                        //Kinzi found
                        eClusterState = CLUSTER_HALANT;

                        bKinziFound = TRUE;

                        *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_RPHF);
                        *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_ABVS);      //for some fonts

                        _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
                        u16Index++;
                        _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );

                        _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
                        u16Index++;
                        _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );

                        _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
                        u16Index++;
                        _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );

                        u16Character = pu16Txt[*pu16ConsumedCount];
                    }
                    else
                    {
                        eClusterState = CLUSTER_HALANT_BASE;
                        //Todo: Fix me, should we separate consonant case and other case?
                        s16BaseGlyphIndex = u16Index;

                        if ( (U16)(u16Index+1) < u32InLen )
                        {
                            HindiCharacter_e eTypeNext = HINDI_INVALID;

                            eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
							if ((eTypeNext == HINDI_CON) || (eTypeNext == HINDI_INDVOW) || (eTypeNext == HINDI_NUM) || (eTypeNext == HINDI_GB))
                            {
                                bExit = TRUE;
                            }
                        }

                        _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
                        u16Index++;
                        _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );

                        u16Character = pu16Txt[*pu16ConsumedCount];
                    }
                    break;

                default:
                    eClusterState = CLUSTER_HALANT_BASE;
                    //Todo: Fix me, should we separate consonant case and other case?
                    s16BaseGlyphIndex = u16Index;

                    if ( (U16)(u16Index+1) < u32InLen )
                    {
                        HindiCharacter_e eTypeNext = HINDI_INVALID;

                        eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                        if ( ( eTypeNext == HINDI_CON ) || ( eTypeNext == HINDI_INDVOW) || (eTypeNext == HINDI_NUM) || (eTypeNext == HINDI_GB))
                        {
                            bExit = TRUE;
                        }
                    }

                    _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
                    u16Index++;
                    _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
                    u16Character = pu16Txt[*pu16ConsumedCount];
                    break;
                }
            }
            else
            {
                if ( ( eClusterState == CLUSTER_SIMPLE ) || ( eClusterState == CLUSTER_HALANT ) )
                {
                    eClusterState = CLUSTER_HALANT_BASE;
                    //Todo: Fix me, should we separate consonant case and other case?
                    s16BaseGlyphIndex = u16Index;

                    if ( (U16)(u16Index+1) < u32InLen )
                    {
                        HindiCharacter_e eTypeNext = HINDI_INVALID;

                        eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                        if ( ( eTypeNext != HINDI_VS ) && ( eTypeNext != HINDI_HALANT ) && ( eTypeNext != HINDI_AS ) && ( eTypeNext != HINDI_MY ) && ( eTypeNext != HINDI_MR ) && ( eTypeNext != HINDI_MW ) && ( eTypeNext != HINDI_MH ) && ( eTypeNext != HINDI_VPRE ) && ( eTypeNext != HINDI_VABV ) && ( eTypeNext != HINDI_VBLW ) && ( eTypeNext != HINDI_A ) && ( eTypeNext != HINDI_DB ) && ( eTypeNext != HINDI_VPST ) && ( eTypeNext != HINDI_PT ) && ( eTypeNext != HINDI_V ) && ( eTypeNext != HINDI_J ) )
                        {
                            bExit = TRUE;
                        }
                    }
                }
                else if ( eClusterState == CLUSTER_HALANT_EXT_S1 )
                {
                    eClusterState = CLUSTER_HALANT_EXT_S2;

                    if ( (U16)(u16Index+1) < u32InLen )
                    {
                        HindiCharacter_e eTypeNext = HINDI_INVALID;

                        eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                        if ( ( eTypeNext != HINDI_VS ) && ( eTypeNext != HINDI_HALANT ) && ( eTypeNext != HINDI_AS ) && ( eTypeNext != HINDI_MY ) && ( eTypeNext != HINDI_MR ) && ( eTypeNext != HINDI_MW ) && ( eTypeNext != HINDI_MH ) && ( eTypeNext != HINDI_VPRE ) && ( eTypeNext != HINDI_VABV ) && ( eTypeNext != HINDI_VBLW ) && ( eTypeNext != HINDI_A ) && ( eTypeNext != HINDI_DB ) && ( eTypeNext != HINDI_VPST ) && ( eTypeNext != HINDI_PT ) && ( eTypeNext != HINDI_V ) && ( eTypeNext != HINDI_J ) )
                        {
                            bExit = TRUE;
                        }
                    }
                }

                _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
                u16Index++;
                _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
                u16Character = pu16Txt[*pu16ConsumedCount];
            }
            break;

        case HINDI_INDVOW:
        case HINDI_NUM:
        case HINDI_GB:
            if ( ( eType == HINDI_INDVOW ) && ( eClusterState == CLUSTER_HALANT_EXT_S1 ) )
            {
                    eClusterState = CLUSTER_HALANT_EXT_S2;

                    if ( (U16)(u16Index+1) < u32InLen )
                    {
                        HindiCharacter_e eTypeNext = HINDI_INVALID;

                        eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                        if ( ( eTypeNext != HINDI_VS ) && ( eTypeNext != HINDI_HALANT ) && ( eTypeNext != HINDI_AS ) && ( eTypeNext != HINDI_MY ) && ( eTypeNext != HINDI_MR ) && ( eTypeNext != HINDI_MW ) && ( eTypeNext != HINDI_MH ) && ( eTypeNext != HINDI_VPRE ) && ( eTypeNext != HINDI_VABV ) && ( eTypeNext != HINDI_VBLW ) && ( eTypeNext != HINDI_A ) && ( eTypeNext != HINDI_DB ) && ( eTypeNext != HINDI_VPST ) && ( eTypeNext != HINDI_PT ) && ( eTypeNext != HINDI_V ) && ( eTypeNext != HINDI_J ) )
                        {
                            bExit = TRUE;
                        }
                    }
            }
            else if ( ( eClusterState == CLUSTER_SIMPLE ) || ( eClusterState == CLUSTER_HALANT ) )
            {
                eClusterState = CLUSTER_HALANT_BASE;
                //Todo: Fix me, should we separate consonant case and other case?
                s16BaseGlyphIndex = u16Index;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ((eTypeNext == HINDI_CON) || (eTypeNext == HINDI_INDVOW) || (eTypeNext == HINDI_NUM) || (eTypeNext == HINDI_GB))
                    {
                        bExit = TRUE;
                    }
                }
            }
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        case HINDI_VS:
            if ( eClusterState == CLUSTER_HALANT_BASE )
            {
                eClusterState = CLUSTER_HALANT_VS1;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ( eTypeNext != HINDI_HALANT )
                    {
                        bExit = TRUE;
                    }
                }
            }
            else if ( eClusterState == CLUSTER_HALANT_EXT_S2 )
            {
                eClusterState = CLUSTER_HALANT_EXT_S3;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_HALANT ) && ( eTypeNext != HINDI_AS ) && ( eTypeNext != HINDI_MY ) && ( eTypeNext != HINDI_MR ) && ( eTypeNext != HINDI_MW ) && ( eTypeNext != HINDI_MH ) && ( eTypeNext != HINDI_VPRE ) && ( eTypeNext != HINDI_VABV ) && ( eTypeNext != HINDI_VBLW ) && ( eTypeNext != HINDI_A ) && ( eTypeNext != HINDI_DB ) && ( eTypeNext != HINDI_VPST ) && ( eTypeNext != HINDI_PT ) && ( eTypeNext != HINDI_V ) && ( eTypeNext != HINDI_J ) )
                    {
                        bExit = TRUE;
                    }
                }
            }
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        case HINDI_HALANT:
            if ( ( eClusterState == CLUSTER_HALANT_BASE ) || ( eClusterState == CLUSTER_HALANT_VS1 ) )
            {
                eClusterState = CLUSTER_HALANT_EXT_S1;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_CON ) && ( eTypeNext != HINDI_INDVOW ) )
                    {
                        bExit = TRUE;
                    }
                }
            }
            else if ( ( eClusterState == CLUSTER_HALANT_EXT_S2 ) || ( eClusterState == CLUSTER_HALANT_EXT_S3 ) )
            {
                eClusterState = CLUSTER_HALANT_EXT_S4;

                bExit = TRUE;

                if ( (U16)(u16Index+1) < u32InLen )
                    {
                        HindiCharacter_e eTypeNext = HINDI_INVALID;

                        eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                        if ( ( eTypeNext == HINDI_CON ) || ( eTypeNext == HINDI_INDVOW ) )
                        {
                            eClusterState = CLUSTER_HALANT_EXT_S1;
                            bExit = FALSE;
                        }
                    }
            }
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        case HINDI_AS:
            if ( ( eClusterState == CLUSTER_COMPLEX_S5 ) || ( eClusterState == CLUSTER_COMPLEX_S7 ) || ( eClusterState == CLUSTER_COMPLEX_S13 ) || ( eClusterState == CLUSTER_COMPLEX_S20 ) || ( eClusterState == CLUSTER_COMPLEX_S24 ) )
            {
                bErrExit = TRUE;
                break;
            }
            else if ( ( eClusterState == CLUSTER_HALANT_BASE ) || ( eClusterState == CLUSTER_HALANT_VS1 ) || ( eClusterState == CLUSTER_HALANT_EXT_S2 ) || ( eClusterState == CLUSTER_HALANT_EXT_S3 ) )
            {
                eClusterState = CLUSTER_COMPLEX_S1;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_AS ) && ( eTypeNext != HINDI_MY ) && ( eTypeNext != HINDI_MR ) && ( eTypeNext != HINDI_MW ) && ( eTypeNext != HINDI_MH ) && ( eTypeNext != HINDI_VPRE ) && ( eTypeNext != HINDI_VABV ) && ( eTypeNext != HINDI_VBLW ) && ( eTypeNext != HINDI_A ) && ( eTypeNext != HINDI_DB ) && ( eTypeNext != HINDI_VPST ) && ( eTypeNext != HINDI_PT ) && ( eTypeNext != HINDI_V ) && ( eTypeNext != HINDI_J ) )
                    {
                        bExit = TRUE;
                    }
                }
            }
            else if ( eClusterState == CLUSTER_COMPLEX_S4  )
            {
                eClusterState = CLUSTER_COMPLEX_S5;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_VPRE ) && ( eTypeNext != HINDI_VABV ) && ( eTypeNext != HINDI_VBLW ) && ( eTypeNext != HINDI_A ) && ( eTypeNext != HINDI_DB ) && ( eTypeNext != HINDI_VPST ) && ( eTypeNext != HINDI_PT ) && ( eTypeNext != HINDI_V ) && ( eTypeNext != HINDI_J ) )
                    {
                        bExit = TRUE;
                    }
                }
            }
            else if ( eClusterState == CLUSTER_COMPLEX_S6 )
            {
                eClusterState = CLUSTER_COMPLEX_S7;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_VPRE ) && ( eTypeNext != HINDI_VABV ) && ( eTypeNext != HINDI_VBLW ) && ( eTypeNext != HINDI_A ) && ( eTypeNext != HINDI_DB ) && ( eTypeNext != HINDI_VPST ) && ( eTypeNext != HINDI_PT ) && ( eTypeNext != HINDI_V ) && ( eTypeNext != HINDI_J ) )
                    {
                        bExit = TRUE;
                    }
                }
            }
            else if ( eClusterState == CLUSTER_COMPLEX_S12 )
            {
                eClusterState = CLUSTER_COMPLEX_S13;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_VPST ) && ( eTypeNext != HINDI_PT ) && ( eTypeNext != HINDI_V ) && ( eTypeNext != HINDI_J ) )
                    {
                        bExit = TRUE;
                    }
                }
            }
            else if ( ( eClusterState == CLUSTER_COMPLEX_S14 ) || ( eClusterState == CLUSTER_COMPLEX_S15 ) )
            {
                eClusterState = CLUSTER_COMPLEX_S16;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_VABV ) && ( eTypeNext != HINDI_A ) && ( eTypeNext != HINDI_DB ) && ( eTypeNext != HINDI_VPST ) && ( eTypeNext != HINDI_PT ) && ( eTypeNext != HINDI_V ) && ( eTypeNext != HINDI_J ) )
                    {
                        bExit = TRUE;
                    }
                }
            }
            else if ( eClusterState == CLUSTER_COMPLEX_S19 )
            {
                eClusterState = CLUSTER_COMPLEX_S20;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_VPST ) && ( eTypeNext != HINDI_PT ) && ( eTypeNext != HINDI_V ) && ( eTypeNext != HINDI_J ) )
                    {
                        bExit = TRUE;
                    }
                }
            }
            else if ( eClusterState == CLUSTER_COMPLEX_S23 )
            {
                eClusterState = CLUSTER_COMPLEX_S24;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_PT ) && ( eTypeNext != HINDI_V ) && ( eTypeNext != HINDI_J ) )
                    {
                        bExit = TRUE;
                    }
                }
            }
            *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_ABVS);
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        case HINDI_MY:
            if ( eClusterState == CLUSTER_COMPLEX_S2 )
            {
                bErrExit = TRUE;
                break;
            }
            else if ( ( eClusterState == CLUSTER_HALANT_BASE ) || ( eClusterState == CLUSTER_HALANT_VS1 ) || ( eClusterState == CLUSTER_HALANT_EXT_S2 ) || ( eClusterState == CLUSTER_HALANT_EXT_S3 ) ||  ( eClusterState == CLUSTER_COMPLEX_S1 ) )
            {
                eClusterState = CLUSTER_COMPLEX_S2;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_MR ) && ( eTypeNext != HINDI_MW ) && ( eTypeNext != HINDI_MH ) && ( eTypeNext != HINDI_VPRE ) && ( eTypeNext != HINDI_VABV ) && ( eTypeNext != HINDI_VBLW ) && ( eTypeNext != HINDI_A ) && ( eTypeNext != HINDI_DB ) && ( eTypeNext != HINDI_VPST ) && ( eTypeNext != HINDI_PT ) && ( eTypeNext != HINDI_V ) && ( eTypeNext != HINDI_J ) )
                    {
                        bExit = TRUE;
                    }
                }
            }
            *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_BLWF);
            *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_BLWS);
            *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_PSTF);
            *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_PSTS);
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        case HINDI_MR:
            if ( eClusterState == CLUSTER_COMPLEX_S3 )
            {
                bErrExit = TRUE;
                break;
            }
            else if ( ( eClusterState == CLUSTER_HALANT_BASE ) || ( eClusterState == CLUSTER_HALANT_VS1 ) || ( eClusterState == CLUSTER_HALANT_EXT_S2 ) || ( eClusterState == CLUSTER_HALANT_EXT_S3 ) ||  ( eClusterState == CLUSTER_COMPLEX_S1 ) || ( eClusterState == CLUSTER_COMPLEX_S2 ) )
            {
                eClusterState = CLUSTER_COMPLEX_S3;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_MW ) && ( eTypeNext != HINDI_MH ) && ( eTypeNext != HINDI_VPRE ) && ( eTypeNext != HINDI_VABV ) && ( eTypeNext != HINDI_VBLW ) && ( eTypeNext != HINDI_A ) && ( eTypeNext != HINDI_DB ) && ( eTypeNext != HINDI_VPST ) && ( eTypeNext != HINDI_PT ) && ( eTypeNext != HINDI_V ) && ( eTypeNext != HINDI_J ) )
                    {
                        bExit = TRUE;
                    }
                }
            }
            s16MRIndex = u16Index;
            //Todo: fix me, what's the features for 0x103C?
            *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_PREF);
            *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_PRES);
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        case HINDI_MW:
            if ( eClusterState == CLUSTER_COMPLEX_S4 )
            {
                bErrExit = TRUE;
                break;
            }
            else if ( ( eClusterState == CLUSTER_HALANT_BASE ) || ( eClusterState == CLUSTER_HALANT_VS1 ) || ( eClusterState == CLUSTER_HALANT_EXT_S2 ) || ( eClusterState == CLUSTER_HALANT_EXT_S3 ) ||  ( eClusterState == CLUSTER_COMPLEX_S1 ) || ( eClusterState == CLUSTER_COMPLEX_S2 ) ||  ( eClusterState == CLUSTER_COMPLEX_S3 ) )
            {
                eClusterState = CLUSTER_COMPLEX_S4;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_AS ) && ( eTypeNext != HINDI_MH ) && ( eTypeNext != HINDI_VPRE ) && ( eTypeNext != HINDI_VABV ) && ( eTypeNext != HINDI_VBLW ) && ( eTypeNext != HINDI_A ) && ( eTypeNext != HINDI_DB ) && ( eTypeNext != HINDI_VPST ) && ( eTypeNext != HINDI_PT ) && ( eTypeNext != HINDI_V ) && ( eTypeNext != HINDI_J ) )
                    {
                        bExit = TRUE;
                    }
                }
            }
            *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_BLWF);
            *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_BLWS);
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        case HINDI_MH:
            if ( eClusterState == CLUSTER_COMPLEX_S6 )
            {
                bErrExit = TRUE;
                break;
            }
            else if ( ( eClusterState == CLUSTER_HALANT_BASE ) || ( eClusterState == CLUSTER_HALANT_VS1 ) || ( eClusterState == CLUSTER_HALANT_EXT_S2 ) || ( eClusterState == CLUSTER_HALANT_EXT_S3 ) ||  ( eClusterState == CLUSTER_COMPLEX_S1 ) || ( eClusterState == CLUSTER_COMPLEX_S2 ) ||  ( eClusterState == CLUSTER_COMPLEX_S3 ) ||  ( eClusterState == CLUSTER_COMPLEX_S4 ) )
            {
                eClusterState = CLUSTER_COMPLEX_S6;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_AS ) && ( eTypeNext != HINDI_VPRE ) && ( eTypeNext != HINDI_VABV ) && ( eTypeNext != HINDI_VBLW ) && ( eTypeNext != HINDI_A ) && ( eTypeNext != HINDI_DB ) && ( eTypeNext != HINDI_VPST ) && ( eTypeNext != HINDI_PT ) && ( eTypeNext != HINDI_V ) && ( eTypeNext != HINDI_J ) )
                    {
                        bExit = TRUE;
                    }
                }
            }
            else if ( eClusterState == CLUSTER_COMPLEX_S14 )
            {
                eClusterState = CLUSTER_COMPLEX_S15;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_AS ) && ( eTypeNext != HINDI_VABV ) && ( eTypeNext != HINDI_A ) && ( eTypeNext != HINDI_DB ) && ( eTypeNext != HINDI_VPST ) && ( eTypeNext != HINDI_PT ) && ( eTypeNext != HINDI_V ) && ( eTypeNext != HINDI_J ) )
                    {
                        bExit = TRUE;
                    }
                }
            }
            *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_BLWF);
            *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_BLWS);
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        case HINDI_VPRE:
            if ( ( eClusterState == CLUSTER_HALANT_BASE ) || ( eClusterState == CLUSTER_HALANT_VS1 ) || ( eClusterState == CLUSTER_HALANT_EXT_S2 ) || ( eClusterState == CLUSTER_HALANT_EXT_S3 ) ||  ( eClusterState == CLUSTER_COMPLEX_S1 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S2 ) ||  ( eClusterState == CLUSTER_COMPLEX_S3 ) ||  ( eClusterState == CLUSTER_COMPLEX_S4 ) ||  ( eClusterState == CLUSTER_COMPLEX_S5 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S6 ) || ( eClusterState == CLUSTER_COMPLEX_S7 ) )
            {
                eClusterState = CLUSTER_COMPLEX_S8;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_VPRE ) && ( eTypeNext != HINDI_VABV ) && ( eTypeNext != HINDI_VBLW ) && ( eTypeNext != HINDI_A ) && ( eTypeNext != HINDI_DB ) && ( eTypeNext != HINDI_VPST ) && ( eTypeNext != HINDI_PT ) && ( eTypeNext != HINDI_V ) && ( eTypeNext != HINDI_J ) )
                    {
                        bExit = TRUE;
                    }
                }
            }

            if ( u16VPreCount == 0 )
            {
                s16PreBaseVowelIndex = u16Index;
            }
            u16VPreCount++;

            *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_PREF);
            *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_PRES);
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        case HINDI_VABV:
            if ( ( eClusterState == CLUSTER_HALANT_BASE ) || ( eClusterState == CLUSTER_HALANT_VS1 ) || ( eClusterState == CLUSTER_HALANT_EXT_S2 ) || ( eClusterState == CLUSTER_HALANT_EXT_S3 ) ||  ( eClusterState == CLUSTER_COMPLEX_S1 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S2 ) ||  ( eClusterState == CLUSTER_COMPLEX_S3 ) ||  ( eClusterState == CLUSTER_COMPLEX_S4 ) ||  ( eClusterState == CLUSTER_COMPLEX_S5 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S6 ) || ( eClusterState == CLUSTER_COMPLEX_S7 ) || ( eClusterState == CLUSTER_COMPLEX_S8 ) )
            {
                eClusterState = CLUSTER_COMPLEX_S9;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_VABV ) && ( eTypeNext != HINDI_VBLW ) && ( eTypeNext != HINDI_A ) && ( eTypeNext != HINDI_DB ) && ( eTypeNext != HINDI_VPST ) && ( eTypeNext != HINDI_PT ) && ( eTypeNext != HINDI_V ) && ( eTypeNext != HINDI_J ) )
                    {
                        bExit = TRUE;
                    }
                }
            }
            else if ( ( eClusterState == CLUSTER_COMPLEX_S14 ) ||  ( eClusterState == CLUSTER_COMPLEX_S15 ) ||  ( eClusterState == CLUSTER_COMPLEX_S16 ) )
            {
                eClusterState = CLUSTER_COMPLEX_S17;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_A ) && ( eTypeNext != HINDI_DB ) && ( eTypeNext != HINDI_VPST ) && ( eTypeNext != HINDI_PT ) && ( eTypeNext != HINDI_V ) && ( eTypeNext != HINDI_J ) )
                    {
                        bExit = TRUE;
                    }
                }
            }
            *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_ABVS);
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        case HINDI_VBLW:
            if ( ( eClusterState == CLUSTER_HALANT_BASE ) || ( eClusterState == CLUSTER_HALANT_VS1 ) || ( eClusterState == CLUSTER_HALANT_EXT_S2 ) || ( eClusterState == CLUSTER_HALANT_EXT_S3 ) ||  ( eClusterState == CLUSTER_COMPLEX_S1 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S2 ) ||  ( eClusterState == CLUSTER_COMPLEX_S3 ) ||  ( eClusterState == CLUSTER_COMPLEX_S4 ) ||  ( eClusterState == CLUSTER_COMPLEX_S5 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S6 ) || ( eClusterState == CLUSTER_COMPLEX_S7 ) || ( eClusterState == CLUSTER_COMPLEX_S8 ) || ( eClusterState == CLUSTER_COMPLEX_S9 ) )
            {
                eClusterState = CLUSTER_COMPLEX_S10;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_VBLW ) && ( eTypeNext != HINDI_A ) && ( eTypeNext != HINDI_DB ) && ( eTypeNext != HINDI_VPST ) && ( eTypeNext != HINDI_PT ) && ( eTypeNext != HINDI_V ) && ( eTypeNext != HINDI_J ) )
                    {
                        bExit = TRUE;
                    }
                }
            }

            if ( u16VBlwCount == 0 )
            {
                s16VBlwIndex = u16Index;
            }
            u16VBlwCount++;

            *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_BLWF);
            *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_BLWS);
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        case HINDI_A:
            if ( ( eClusterState == CLUSTER_HALANT_BASE ) || ( eClusterState == CLUSTER_HALANT_VS1 ) || ( eClusterState == CLUSTER_HALANT_EXT_S2 ) || ( eClusterState == CLUSTER_HALANT_EXT_S3 ) ||  ( eClusterState == CLUSTER_COMPLEX_S1 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S2 ) ||  ( eClusterState == CLUSTER_COMPLEX_S3 ) ||  ( eClusterState == CLUSTER_COMPLEX_S4 ) ||  ( eClusterState == CLUSTER_COMPLEX_S5 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S6 ) || ( eClusterState == CLUSTER_COMPLEX_S7 ) || ( eClusterState == CLUSTER_COMPLEX_S8 ) || ( eClusterState == CLUSTER_COMPLEX_S9 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S10 ) )
            {
                eClusterState = CLUSTER_COMPLEX_S11;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_A ) && ( eTypeNext != HINDI_DB ) && ( eTypeNext != HINDI_VPST ) && ( eTypeNext != HINDI_PT ) && ( eTypeNext != HINDI_V ) && ( eTypeNext != HINDI_J ) )
                    {
                        bExit = TRUE;
                    }
                }
            }
            else if ( ( eClusterState == CLUSTER_COMPLEX_S14 ) ||  ( eClusterState == CLUSTER_COMPLEX_S15 ) ||  ( eClusterState == CLUSTER_COMPLEX_S16 ) ||  ( eClusterState == CLUSTER_COMPLEX_S17 ) )
            {
                eClusterState = CLUSTER_COMPLEX_S18;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_DB) && ( eTypeNext != HINDI_VPST ) && ( eTypeNext != HINDI_PT ) && ( eTypeNext != HINDI_V ) && ( eTypeNext != HINDI_J ) )
                    {
                        bExit = TRUE;
                    }
                }
            }
            else if ( eClusterState == CLUSTER_COMPLEX_S21 )
            {
                eClusterState = CLUSTER_COMPLEX_S22;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_DB ) && ( eTypeNext != HINDI_PT ) && ( eTypeNext != HINDI_V ) && ( eTypeNext != HINDI_J ) )
                    {
                        bExit = TRUE;
                    }
                }
            }
            if ( u16ACount == 0 )
            {
                s16AnusvaraIndex = u16Index;
            }
            u16ACount++;

            *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_ABVS);
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        case HINDI_DB:
            if ( ( eClusterState == CLUSTER_COMPLEX_S12 ) || ( eClusterState == CLUSTER_COMPLEX_S19 ) || ( eClusterState == CLUSTER_COMPLEX_S23 ) )
            {
                bErrExit = TRUE;
                break;
            }
            else if ( ( eClusterState == CLUSTER_HALANT_BASE ) || ( eClusterState == CLUSTER_HALANT_VS1 ) || ( eClusterState == CLUSTER_HALANT_EXT_S2 ) || ( eClusterState == CLUSTER_HALANT_EXT_S3 ) ||  ( eClusterState == CLUSTER_COMPLEX_S1 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S2 ) ||  ( eClusterState == CLUSTER_COMPLEX_S3 ) ||  ( eClusterState == CLUSTER_COMPLEX_S4 ) ||  ( eClusterState == CLUSTER_COMPLEX_S5 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S6 ) || ( eClusterState == CLUSTER_COMPLEX_S7 ) || ( eClusterState == CLUSTER_COMPLEX_S8 ) || ( eClusterState == CLUSTER_COMPLEX_S9 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S10 ) || ( eClusterState == CLUSTER_COMPLEX_S11 ) )
            {
                eClusterState = CLUSTER_COMPLEX_S12;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_AS ) && ( eTypeNext != HINDI_VPST ) && ( eTypeNext != HINDI_PT ) && ( eTypeNext != HINDI_V ) && ( eTypeNext != HINDI_J ) )
                    {
                        bExit = TRUE;
                    }
                }
            }
            else if ( ( eClusterState == CLUSTER_COMPLEX_S14 ) || ( eClusterState == CLUSTER_COMPLEX_S15 ) || ( eClusterState == CLUSTER_COMPLEX_S16 ) || ( eClusterState == CLUSTER_COMPLEX_S17 ) ||
                ( eClusterState == CLUSTER_COMPLEX_S18 ) )
            {
                eClusterState = CLUSTER_COMPLEX_S19;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_AS) && ( eTypeNext != HINDI_VPST ) && ( eTypeNext != HINDI_PT ) && ( eTypeNext != HINDI_V ) && ( eTypeNext != HINDI_J ) )
                    {
                        bExit = TRUE;
                    }
                }
            }
            else if ( ( eClusterState == CLUSTER_COMPLEX_S21 ) || ( eClusterState == CLUSTER_COMPLEX_S22 ) )
            {
                eClusterState = CLUSTER_COMPLEX_S23;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_AS ) && ( eTypeNext != HINDI_PT ) && ( eTypeNext != HINDI_V ) && ( eTypeNext != HINDI_J ) )
                    {
                        bExit = TRUE;
                    }
                }
            }
            *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_BLWF);
            *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_BLWS);
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        case HINDI_VPST:
            if (  ( eClusterState == CLUSTER_HALANT_BASE ) || ( eClusterState == CLUSTER_HALANT_VS1 ) ||  ( eClusterState == CLUSTER_HALANT_EXT_S2 ) || ( eClusterState == CLUSTER_HALANT_EXT_S3 ) ||  ( eClusterState == CLUSTER_COMPLEX_S1 ) ||
                      ( eClusterState == CLUSTER_COMPLEX_S2 ) ||  ( eClusterState == CLUSTER_COMPLEX_S3 ) ||  ( eClusterState == CLUSTER_COMPLEX_S4 ) ||  ( eClusterState == CLUSTER_COMPLEX_S5 ) ||
                      ( eClusterState == CLUSTER_COMPLEX_S6 ) || ( eClusterState == CLUSTER_COMPLEX_S7 ) || ( eClusterState == CLUSTER_COMPLEX_S8 ) || ( eClusterState == CLUSTER_COMPLEX_S9 ) ||
                      ( eClusterState == CLUSTER_COMPLEX_S10 ) || ( eClusterState == CLUSTER_COMPLEX_S11 ) || ( eClusterState == CLUSTER_COMPLEX_S12 ) || ( eClusterState == CLUSTER_COMPLEX_S13 ) ||
                      ( eClusterState == CLUSTER_COMPLEX_S15 ) || ( eClusterState == CLUSTER_COMPLEX_S16 ) || ( eClusterState == CLUSTER_COMPLEX_S17 ) || ( eClusterState == CLUSTER_COMPLEX_S18 ) ||
                      ( eClusterState == CLUSTER_COMPLEX_S19 ) || ( eClusterState == CLUSTER_COMPLEX_S20 ) )
            {
                eClusterState = CLUSTER_COMPLEX_S14;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_MH ) && ( eTypeNext != HINDI_AS ) && ( eTypeNext != HINDI_VABV ) && ( eTypeNext != HINDI_A ) && ( eTypeNext != HINDI_DB ) && ( eTypeNext != HINDI_VPST ) && ( eTypeNext != HINDI_PT ) && ( eTypeNext != HINDI_V ) && ( eTypeNext != HINDI_J ) )
                    {
                        bExit = TRUE;
                    }
                }
            }
            *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_PSTF);
            *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_PSTS);
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        case HINDI_PT:
            if (  ( eClusterState == CLUSTER_HALANT_BASE ) || ( eClusterState == CLUSTER_HALANT_VS1 ) ||  ( eClusterState == CLUSTER_HALANT_EXT_S2 ) || ( eClusterState == CLUSTER_HALANT_EXT_S3 ) ||  ( eClusterState == CLUSTER_COMPLEX_S1 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S2 ) ||  ( eClusterState == CLUSTER_COMPLEX_S3 ) ||  ( eClusterState == CLUSTER_COMPLEX_S4 ) ||  ( eClusterState == CLUSTER_COMPLEX_S5 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S6 ) || ( eClusterState == CLUSTER_COMPLEX_S7 ) || ( eClusterState == CLUSTER_COMPLEX_S8 ) || ( eClusterState == CLUSTER_COMPLEX_S9 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S10 ) || ( eClusterState == CLUSTER_COMPLEX_S11 ) || ( eClusterState == CLUSTER_COMPLEX_S12 ) || ( eClusterState == CLUSTER_COMPLEX_S13 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S14 ) || ( eClusterState == CLUSTER_COMPLEX_S15 ) || ( eClusterState == CLUSTER_COMPLEX_S16 ) || ( eClusterState == CLUSTER_COMPLEX_S17 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S18 ) || ( eClusterState == CLUSTER_COMPLEX_S19 ) || ( eClusterState == CLUSTER_COMPLEX_S20 ) || ( eClusterState == CLUSTER_COMPLEX_S22 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S23 ) || ( eClusterState == CLUSTER_COMPLEX_S24 ) )
            {
                eClusterState = CLUSTER_COMPLEX_S21;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_A ) && ( eTypeNext != HINDI_DB ) && ( eTypeNext != HINDI_PT ) && ( eTypeNext != HINDI_V ) && ( eTypeNext != HINDI_J ) )
                    {
                        bExit = TRUE;
                    }
                }
            }
            *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_PSTF);
            *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_PSTS);
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        case HINDI_V:
            if (  ( eClusterState == CLUSTER_HALANT_BASE ) || ( eClusterState == CLUSTER_HALANT_VS1 ) ||  ( eClusterState == CLUSTER_HALANT_EXT_S2 ) || ( eClusterState == CLUSTER_HALANT_EXT_S3 ) ||  ( eClusterState == CLUSTER_COMPLEX_S1 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S2 ) ||  ( eClusterState == CLUSTER_COMPLEX_S3 ) ||  ( eClusterState == CLUSTER_COMPLEX_S4 ) ||  ( eClusterState == CLUSTER_COMPLEX_S5 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S6 ) || ( eClusterState == CLUSTER_COMPLEX_S7 ) || ( eClusterState == CLUSTER_COMPLEX_S8 ) || ( eClusterState == CLUSTER_COMPLEX_S9 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S10 ) || ( eClusterState == CLUSTER_COMPLEX_S11 ) || ( eClusterState == CLUSTER_COMPLEX_S12 ) || ( eClusterState == CLUSTER_COMPLEX_S13 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S14 ) || ( eClusterState == CLUSTER_COMPLEX_S15 ) || ( eClusterState == CLUSTER_COMPLEX_S16 ) || ( eClusterState == CLUSTER_COMPLEX_S17 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S18 ) || ( eClusterState == CLUSTER_COMPLEX_S19 ) || ( eClusterState == CLUSTER_COMPLEX_S20 ) || ( eClusterState == CLUSTER_COMPLEX_S21 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S22 ) || ( eClusterState == CLUSTER_COMPLEX_S23 ) || ( eClusterState == CLUSTER_COMPLEX_S24 ) )
            {
                eClusterState = CLUSTER_COMPLEX_S25;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontMyanmarGetCharType(pu16Txt[u16Index+1]);
                    if ( eTypeNext != HINDI_J )
                    {
                        bExit = TRUE;
                    }
                }
            }
            //Should we add blwf/blws for 0x108D ?
            *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_PSTF);
            *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_PSTS);
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        case HINDI_J:
            if ( eClusterState == CLUSTER_COMPLEX_S26 )
            {
                bErrExit = TRUE;
                break;
            }
            else if (  ( eClusterState == CLUSTER_HALANT_BASE ) || ( eClusterState == CLUSTER_HALANT_VS1 ) ||  ( eClusterState == CLUSTER_HALANT_EXT_S2 ) || ( eClusterState == CLUSTER_HALANT_EXT_S3 ) ||  ( eClusterState == CLUSTER_COMPLEX_S1 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S2 ) ||  ( eClusterState == CLUSTER_COMPLEX_S3 ) ||  ( eClusterState == CLUSTER_COMPLEX_S4 ) ||  ( eClusterState == CLUSTER_COMPLEX_S5 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S6 ) || ( eClusterState == CLUSTER_COMPLEX_S7 ) || ( eClusterState == CLUSTER_COMPLEX_S8 ) || ( eClusterState == CLUSTER_COMPLEX_S9 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S10 ) || ( eClusterState == CLUSTER_COMPLEX_S11 ) || ( eClusterState == CLUSTER_COMPLEX_S12 ) || ( eClusterState == CLUSTER_COMPLEX_S13 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S14 ) || ( eClusterState == CLUSTER_COMPLEX_S15 ) || ( eClusterState == CLUSTER_COMPLEX_S16 ) || ( eClusterState == CLUSTER_COMPLEX_S17 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S18 ) || ( eClusterState == CLUSTER_COMPLEX_S19 ) || ( eClusterState == CLUSTER_COMPLEX_S20 ) || ( eClusterState == CLUSTER_COMPLEX_S21 ) ||
                    ( eClusterState == CLUSTER_COMPLEX_S22 ) || ( eClusterState == CLUSTER_COMPLEX_S23 ) || ( eClusterState == CLUSTER_COMPLEX_S24 ) || ( eClusterState == CLUSTER_COMPLEX_S25 ) )
            {
                eClusterState = CLUSTER_COMPLEX_S26;
                bExit = TRUE;
            }
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;
        }
    }

    if ( *pu16ConsumedCount > 0 )
    {
        *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_DIST);
        *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_MARK);
        *pu32FeatureTags = _msAPI_MLE_FontMyanmarSetFeature(*pu32FeatureTags, HINDI_FEATURE_MKMK);
    }

    return *pu16ConsumedCount;
}

static HindiCharacter_e _msAPI_MLE_FontMyanmarGetCharType( U16 u16Character )
{
    HindiCharacter_e eType = HINDI_INVALID;

    if ( IS_MYMR_RANGE(u16Character) )
    {
        eType = (g_MyanmarCharTypeArray[u16Character - MYMR_MASK]);
    }
    else if ( IS_MYMR_EXTA_RANGE(u16Character) )
    {
        eType = (g_MyanmarExtACharTypeArray[u16Character - MYMR_EXTA_MASK]);
    }
    else if ( IS_MYMR_EXTB_RANGE(u16Character) )
    {
        eType = (g_MyanmarExtBCharTypeArray[u16Character - MYMR_EXTB_MASK]);
    }
    else
    {
        switch( u16Character )
        {
        case 0x2060:    //Word joiner
            eType = HINDI_WJ;
            break;
        case 0x0020:    //Space character
        case 0x200B:    //ZWSP, Zero Width Space
            eType = HINDI_WS;
            break;
        case 0xFE00:
        case 0xFE01:
        case 0xFE02:
        case 0xFE03:
        case 0xFE04:
        case 0xFE05:
        case 0xFE06:
        case 0xFE07:
        case 0xFE08:
        case 0xFE09:
        case 0xFE0A:
        case 0xFE0B:
        case 0xFE0C:
        case 0xFE0D:
        case 0xFE0E:
        case 0xFE0F:
            //Variation selectors
            eType = HINDI_VS;
            break;
        case 0x00A0:
        case 0x00D7:
        case 0x2012:
        case 0x2013:
        case 0x2014:
        case 0x2015:
        case 0x2022:
        case 0x25CC:
        case 0x25FB:
        case 0x25FC:
        case 0x25FD:
        case 0x25FE:
            //Generic base characters
            eType = HINDI_GB;
            break;
        case 0x200C:
        case 0x200D:
            //Joiners
            eType = HINDI_J;
            break;
        case 0xAA7C:
        case 0xAA7D:
        case 0xAA7E:
        case 0xAA7F:
            eType = HINDI_R;
            break;
        default:
            break;
        }
    }

    return eType;
}

static U32 _msAPI_MLE_FontMyanmarSetFeature( U32 u32FeatureTags, HindiFeature_e eFeature )
{
    U16 i;
    for ( i = 0; i < _g_u16MyanmarFeatureCount; i++ )
    {
        if ( _g_sMyanmarFeatureMap[i].eTag == eFeature )
        {
            u32FeatureTags = u32FeatureTags | _g_sMyanmarFeatureMap[i].u32Mask;
            break;
        }
    }
    return u32FeatureTags;
}

static U16 _msAPI_MLE_FontMyanmarGetFeatureMap( const HindiFeatureRecord_t **ppasFeatureMap )
{
    *ppasFeatureMap = _g_sMyanmarFeatureMap;
    return (U16)_g_u16MyanmarFeatureCount;
}

static BOOLEAN _msAPI_MLE_FontMyanmarCharIsBlwf( U16 u16FirstChar, U16 u16SecondChar )
{
    BOOLEAN bResult = FALSE;
    HindiCharacter_e heFirstChar =_msAPI_MLE_FontMyanmarGetCharType(u16FirstChar);
    HindiCharacter_e heSecondChar = _msAPI_MLE_FontMyanmarGetCharType(u16SecondChar);

    if ( IS_MYMR_ALL_RANGE(u16FirstChar) && IS_MYMR_ALL_RANGE(u16SecondChar) )
    {
        if ( IS_MYMR_HALANT_CHAR(u16FirstChar) )
        {
            if ( ( HINDI_CON == heSecondChar ) || ( HINDI_INDVOW == heSecondChar ) )
            {
                bResult = TRUE;
            }
        }
        else
        {
            switch( heSecondChar )
            {
                case HINDI_MY:
                    {
                        switch( heFirstChar )
                        {
                            case HINDI_CON:
                            case HINDI_INDVOW:
                            case HINDI_GB:
                            case HINDI_NUM:
                            case HINDI_VS:
                            case HINDI_AS:
                                {
                                    bResult = TRUE;
                                }
                                break;
                            default:
                                break;
                        }
                    }
                    break;
                case HINDI_MW:
                    {
                        switch( heFirstChar )
                        {
                            case HINDI_CON:
                            case HINDI_INDVOW:
                            case HINDI_GB:
                            case HINDI_NUM:
                            case HINDI_VS:
                            case HINDI_AS:
                            case HINDI_MY:
                                {
                                    bResult = TRUE;
                                }
                                break;
                            default:
                                break;
                        }
                    }
                    break;
                case HINDI_MH:
                    {
                        switch( heFirstChar )
                        {
                            case HINDI_CON:
                            case HINDI_INDVOW:
                            case HINDI_GB:
                            case HINDI_NUM:
                            case HINDI_VS:
                            case HINDI_AS:
                            case HINDI_MY:
                            case HINDI_MR:
                            case HINDI_VPST:
                                {
                                    bResult = TRUE;
                                }
                                break;
                            default:
                                break;
                        }
                    }
                    break;
                case HINDI_VBLW:
                    {
                        switch( heFirstChar )
                        {
                            case HINDI_CON:
                            case HINDI_INDVOW:
                            case HINDI_GB:
                            case HINDI_NUM:
                            case HINDI_VS:
                            case HINDI_AS:
                            case HINDI_MY:
                            case HINDI_MR:
                            case HINDI_MW:
                            case HINDI_MH:
                            case HINDI_VPRE:
                            case HINDI_VABV:
                            case HINDI_VBLW:
                                {
                                    bResult = TRUE;
                                }
                                break;
                            default:
                                break;
                        }
                    }
                    break;
                case HINDI_DB:
                    {
                        switch( heFirstChar )
                        {
                            case HINDI_CON:
                            case HINDI_INDVOW:
                            case HINDI_GB:
                            case HINDI_NUM:
                            case HINDI_VS:
                            case HINDI_AS:
                            case HINDI_MY:
                            case HINDI_MR:
                            case HINDI_MW:
                            case HINDI_MH:
                            case HINDI_VPRE:
                            case HINDI_VABV:
                            case HINDI_VBLW:
                            case HINDI_A:
                            case HINDI_VPST:
                            case HINDI_PT:
                                {
                                    bResult = TRUE;
                                }
                                break;
                            default:
                                break;
                        }
                    }
                    break;
            }
        }
    }

    return bResult;
}

static U16 _msAPI_MLE_FontMyanmarRefineCluster( HindiScript_e eScript, const U16 *pu16InTxt, U32 u32InLen, U32 u32Offset, U16 *pu16Cluster, U16 *pu16CluserSize, U16 u16ClusterOffset, BOOLEAN bIsDispStr, U32 *pu32Features, const U16 *pu16OriginTxt, U32 u32OriginOffset)
{
//Below is XP spec, in Win7, it seems that Microsoft modified reorder rule of Bengali, so we don't need to reorder here
    //U16 u16Character = 0;
    U16 i = 0;
    //U16 u16Index = 0;

    //U16 u16CluserSize = *pu16CluserSize;
    //BOOLEAN bIsInit = FALSE;

    eScript = eScript;
    pu16InTxt = pu16InTxt;
    u32InLen = u32InLen;
    u32Offset = u32Offset;
    bIsDispStr = bIsDispStr;
    pu32Features = pu32Features;
    pu16OriginTxt = pu16OriginTxt;
    u32OriginOffset = u32OriginOffset;
    pu16CluserSize = pu16CluserSize;

    if ( s16BaseGlyphIndex < 0 )
        return u16ClusterOffset;

    //Kinzi sequences (K) are reordered directly after the cluster base
    if ( bKinziFound )
    {
        U16 u16Temp;

        u16Temp = pu16Cluster[s16BaseGlyphIndex];

        for(i=0;i<3;i++)
        {
            pu16Cluster[s16BaseGlyphIndex-i] = pu16Cluster[s16BaseGlyphIndex-i-1];
        }
        pu16Cluster[0] = u16Temp;
        s16BaseGlyphIndex = 0;
    }

    //The medial ra (MR) is reordered before the base consonant
    if ( ( s16MRIndex > 0 ) && ( s16BaseGlyphIndex < s16MRIndex ) )
    {
        //Todo: Fix me, should we limit this base glyph to must be consonant glyph?
        if ( HINDI_CON == _msAPI_MLE_FontMyanmarGetCharType(pu16Cluster[s16BaseGlyphIndex]) )
        {
            //MR found
            U16 u16Temp;

            u16Temp = pu16Cluster[s16MRIndex];

            for(i = s16MRIndex; i > s16BaseGlyphIndex; i--)
            {
                pu16Cluster[i] = pu16Cluster[i-1];
            }
            pu16Cluster[s16BaseGlyphIndex] = u16Temp;
            s16BaseGlyphIndex++;
        }
    }

    //Pre-base vowels (VPre) are reordered to the start of the syllable cluster. A sequence of multiple prebase vowels is permitted. Such sequences are moved as a block to the beginning of the cluster
    if ( s16PreBaseVowelIndex > 0 )
    {
        U16 au16temp[HINDI_CONVERT_MAX] = {0};
        S16 s16VPREMoveCount = 0;

        //VPre found
        for(i=0;i<u16VPreCount;i++)
        {
            au16temp[i] = pu16Cluster[s16PreBaseVowelIndex+i];
        }

        for(s16VPREMoveCount = (s16PreBaseVowelIndex-1); s16VPREMoveCount >= 0; s16VPREMoveCount--)
        {
            pu16Cluster[s16VPREMoveCount+u16VPreCount] = pu16Cluster[s16VPREMoveCount];
        }

        for(i=0;i<u16VPreCount;i++)
        {
            pu16Cluster[i] = au16temp[i];
        }

        s16BaseGlyphIndex += u16VPreCount;
    }

    //Anusvara (A) coming immediately after one or more below-base vowels (VBlw) will reorder immediately before them
    if ( ( s16AnusvaraIndex > 0 ) && ( s16VBlwIndex > 0 ) )
    {
        //both Anusvara and VBlw found
        //Todo: Fix me, should we move all Anusvara characters? Or just need to move the first Anusvara character?
        if ( s16AnusvaraIndex == ( s16VBlwIndex + u16VBlwCount ) )
        {
            U16 u16Temp;

            u16Temp = pu16Cluster[s16AnusvaraIndex];

            for(i = s16AnusvaraIndex; i > s16VBlwIndex; i--)
            {
                pu16Cluster[i] = pu16Cluster[i-1];
            }
            pu16Cluster[s16VBlwIndex] = u16Temp;
        }
    }

    return u16ClusterOffset;
}

#endif //__MYMR_FONT__
#endif //__INDIC_FONT__
