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

#ifdef __KHMR_FONT__
#include "msAPI_MLE_font_khmer.h"

/*------------------------------------------------------------------------------------------
*
*                                                                                     MACRO DEFINE
*
-------------------------------------------------------------------------------------------*/

const U8 g_KhmerCharTypeArray[] =
{
    /*  CONSONANT'S TABLES    */            /* Consonants */
    HINDI_CON,                                                            //KHMER_C_KA        =0x1780,
    HINDI_CON,                                                            //KHMER_C_KHA       =0x1781,
    HINDI_CON,                                                            //KHMER_C_KO        =0x1782,
    HINDI_CON,                                                            //KHMER_C_KHO       =0x1783,
    HINDI_CON,                                                            //KHMER_C_NGO       =0x1784,
    HINDI_CON,                                                            //KHMER_C_CA        =0x1785,
    HINDI_CON,                                                            //KHMER_C_CHA       =0x1786,
    HINDI_CON,                                                            //KHMER_C_CO        =0x1787,
    HINDI_CON,                                                            //KHMER_C_CHO       =0x1788,
    HINDI_CON,                                                            //KHMER_C_NYO       =0x1789,
    HINDI_CON,                                                            //KHMER_C_DA        =0x178A,
    HINDI_CON,                                                            //KHMER_C_TTHA      =0x178B,
    HINDI_CON,                                                            //KHMER_C_DO        =0x178C,
    HINDI_CON,                                                            //KHMER_C_TTHO      =0x178D,
    HINDI_CON,                                                            //KHMER_C_NNO       =0x178E,
    HINDI_CON,                                                            //KHMER_C_TA        =0x178F,
    HINDI_CON,                                                            //KHMER_C_THA       =0x1790,
    HINDI_CON,                                                            //KHMER_C_TO        =0x1791,
    HINDI_CON,                                                            //KHMER_C_THO       =0x1792,
    HINDI_CON,                                                            //KHMER_C_NO        =0x1793,
    HINDI_CON,                                                            //KHMER_C_BA        =0x1794,
    HINDI_CON,                                                            //KHMER_C_PHA       =0x1795,
    HINDI_CON,                                                            //KHMER_C_PO        =0x1796,
    HINDI_CON,                                                            //KHMER_C_PHO       =0x1797,
    HINDI_CON,                                                            //KHMER_C_MO        =0x1798,
    HINDI_CON,                                                            //KHMER_C_YO        =0x1799,
    HINDI_CON,                                                            //KHMER_C_RO        =0x179A,
    HINDI_CON,                                                            //KHMER_C_LO        =0x179B,
    HINDI_CON,                                                            //KHMER_C_LO        =0x179C,
    HINDI_CON,                                                            //KHMER_C_SHA       =0x179D,
    HINDI_CON,                                                            //KHMER_C_SSO       =0x179E,
    HINDI_CON,                                                            //KHMER_C_SA        =0x179F,
    HINDI_CON,                                                            //KHMER_C_HA        =0x17A0,
    HINDI_CON,                                                            //KHMER_C_LA        =0x17A1,
    HINDI_CON,                                                            //KHMER_C_QA        =0x17A2,

                                                                                  /* Deprecated independent vowels for transliteration*/
    HINDI_INDVOW,                                                      //KHMER_DIV_QAQ     =0x17A3,
    HINDI_INDVOW,                                                      //KHMER_DIV_QAA     =0x17A4,

                                                                                   /* Independent vowels */
    HINDI_INDVOW,                                                     //KHMER_IV_QI       =0x17A5,
    HINDI_INDVOW,                                                     //KHMER_IV_QII      =0x17A6,
    HINDI_INDVOW,                                                     //KHMER_IV_QU       =0x17A7,
    HINDI_INDVOW,                                                     //KHMER_IV_QUK      =0x17A8,
    HINDI_INDVOW,                                                     //KHMER_IV_QUU      =0x17A9,
    HINDI_INDVOW,                                                     //KHMER_IV_QUUV     =0x17AA,
    HINDI_INDVOW,                                                     //KHMER_IV_RY       =0x17AB,
    HINDI_INDVOW,                                                     //KHMER_IV_RYY      =0x17AC,
    HINDI_INDVOW,                                                     //KHMER_IV_LY       =0x17AD,
    HINDI_INDVOW,                                                     //KHMER_IV_LYY      =0x17AE,
    HINDI_INDVOW,                                                     //KHMER_IV_QE       =0x17AF,
    HINDI_INDVOW,                                                     //KHMER_IV_QAI      =0x17B0,
    HINDI_INDVOW,                                                     //KHMER_IV_QOO_TYPE1        =0x17B1,
    HINDI_INDVOW,                                                     //KHMER_IV_QOO_TYPE2        =0x17B2,
    HINDI_INDVOW,                                                     //KHMER_IV_QAU      =0x17B3,

                                                                                   /* Inherent vowels */
    HINDI_INVALID,                                                     //KHMER_VI_AQ       =0x17B4,
    HINDI_INVALID,                                                     //KHMER_VI_AA       =0x17B5,

                                                                                    /* Dependent vowel signs */
    HINDI_VPST,                                                            //KHMER_DV_AA       =0x17B6,
    HINDI_VABV,                                                            //KHMER_DV_I        =0x17B7,
    HINDI_VABV,                                                            //KHMER_DV_II       =0x17B8,
    HINDI_VABV,                                                            //KHMER_DV_Y        =0x17B9,
    HINDI_VABV,                                                            //KHMER_DV_YY       =0x17BA,
    HINDI_VBLW,                                                            //KHMER_DV_U        =0x17BB,
    HINDI_VBLW,                                                            //KHMER_DV_UU       =0x17BC,
    HINDI_VBLW,                                                            //KHMER_DV_UA       =0x17BD,

                                                                                    /* two-part dependent vowel */
    HINDI_DEPVOW,                                                        //KHMER_DV_OE       =0x17BE,
    HINDI_DEPVOW,                                                        //KHMER_DV_YA       =0x17BF,
    HINDI_DEPVOW,                                                        //KHMER_DV_IE       =0x17C0,

                                                                                    /* Dependent vowel signs */
    HINDI_VPRE,                                                            //KHMER_DV_E        =0x17C1,
    HINDI_VPRE,                                                            //KHMER_DV_AE       =0x17C2,
    HINDI_VPRE,                                                            //KHMER_DV_AI       =0x17C3,

                                                                                    /* two-part dependent vowel */
    HINDI_DEPVOW,                                                        //KHMER_DV_OO       =0x17C4,
    HINDI_DEPVOW,                                                        //KHMER_DV_AU       =0x17C5,

                                                                                    /* Various signs*/
    HINDI_SABV,                                                            //KHMER_S_NIKAHIT   =0x17C6,
    HINDI_SPST,                                                            //KHMER_S_REAHMUK   =0x17C7,
    HINDI_SPST,                                                            //KHMER_S_YUUKALEAPINTU    =0x17C8,

                                                                                    /* Consonant shifters */
    HINDI_REGSHIFT,                                                       //KHMER_S_MUUSIKATOAN      =0x17C9,
    HINDI_REGSHIFT,                                                       //KHMER_S_TRIISA    =0x17CA,

                                                                                    /* Various signs */
    HINDI_SABV,                                                            //KHMER_S_BANTOC    =0x17CB,
    HINDI_SABV,                                                            //KHMER_S_ROBAT     =0x17CC,
    HINDI_SABV,                                                            //KHMER_S_TOANDAKHIAT    =0x17CD,
    HINDI_SABV,                                                            //KHMER_S_KAKABAT   =0x17CE,
    HINDI_SABV,                                                            //KHMER_S_AHSDA     =0x17CF,
    HINDI_SABV,                                                            //KHMER_S_SAMYOK_SANNYA    =0x17D0,
    HINDI_SABV,                                                            //KHMER_S_VIRIAM    =0x17D1,
    HINDI_COENG,                                                         //KHMER_S_COENG     =0x17D2,

                                                                                    /* Lunar date sign */
    HINDI_SABV,                                                            //KHMER_S_BATHAMASAT    =0x17D3,

                                                                                    /* Various signs */
    HINDI_SIGN,                                                            //KHMER_S_KHAN      =0x17D4,
    HINDI_SIGN,                                                            //KHMER_S_BARIYOOSAN    =0x17D5,
    HINDI_SIGN,                                                            //KHMER_S_CAMNUC_PII_KUUH    =0x17D6,
    HINDI_SIGN,                                                            //KHMER_S_LEK_TOO   =0x17D7,
    HINDI_SIGN,                                                            //KHMER_S_BEYYAL    =0x17D8,
    HINDI_SIGN,                                                            //KHMER_S_PHNAEK_MUAN    =0x17D9,
    HINDI_SIGN,                                                            //KHMER_S_KOOMUUT   =0x17DA,

                                                                                    /* Currency symbol */
    HINDI_SIGN,                                                            //KHMER_CS_RIEL   =0x17DB,

                                                                                    /* Various signs */
    HINDI_SIGN,                                                             //KHMER_S_AVAKRAHASANYA   =0x17DC,
    HINDI_SABV,                                                            //KHMER_S_ATTHACAN   =0x17DD,
};

const U8 g_KhmerDigitICharTypeArray[] =
{
                                                                                        /* Digits */
    HINDI_NUM,                                                              //KHMER_D_ZERO     =0x17E0,
    HINDI_NUM,                                                            //KHMER_D_ONE      =0x17E1,
    HINDI_NUM,                                                            //KHMER_D_TWO      =0x17E2,
    HINDI_NUM,                                                            //KHMER_D_THREE    =0x17E3,
    HINDI_NUM,                                                            //KHMER_D_FOUR     =0x17E4,
    HINDI_NUM,                                                            //KHMER_D_FIVE     =0x17E5,
    HINDI_NUM,                                                            //KHMER_D_SIX      =0x17E6,
    HINDI_NUM,                                                            //KHMER_D_SEVEN    =0x17E7,
    HINDI_NUM,                                                            //KHMER_D_EIGHT    =0x17E8,
    HINDI_NUM,                                                            //KHMER_D_NINE     =0x17E9,
};

const U8 g_KhmerDigitIICharTypeArray[] =
{
    /* Numeric symbols for divination lore */
HINDI_NUM,                                                            //KHMER_S_LA_SON    =0x17F0,
HINDI_NUM,                                                            //KHMER_S_LA_MUOY   =0x17F1,
HINDI_NUM,                                                            //KHMER_S_PII       =0x17F2,
HINDI_NUM,                                                            //KHMER_S_BEI       =0x17F3,
HINDI_NUM,                                                            //KHMER_S_BUON      =0x17F4,
HINDI_NUM,                                                            //KHMER_S_PRAM      =0x17F5,
HINDI_NUM,                                                            //KHMER_S_PRAM_MUOY =0x17F6,
HINDI_NUM,                                                            //KHMER_S_PRAM_PII  =0x17F7,
HINDI_NUM,                                                            //KHMER_S_PRAM_BEI  =0x17F8,
HINDI_NUM,                                                            //KHMER_S_PRAM_BUON =0x17F9,
};

const U8 g_KhmerSymbolCharTypeArray[] =
{
    /* Khmer Symbols */                     /* Lunar date symbols */
    HINDI_SIGN,                                                            //KHMER_S_PATHAMASAT        =0x19E0
    HINDI_SIGN,                                                            //KHMER_S_MUOY_KOET                  =0x19E1
    HINDI_SIGN,                                                            //KHMER_S_PII_KOET                   =0x19E2
    HINDI_SIGN,                                                            //KHMER_S_BEI_KOET                   =0x19E3
    HINDI_SIGN,                                                            //KHMER_S_BUON_KOET                  =0x19E4
    HINDI_SIGN,                                                            //KHMER_S_PRAM_KOET                  =0x19E5
    HINDI_SIGN,                                                            //KHMER_S_PRAM_MUOY_KOET         =0x19E6
    HINDI_SIGN,                                                            //KHMER_S_PRAM_PII_KOET         =0x19E7
    HINDI_SIGN,                                                            //KHMER_S_PRAM_BEI_KOET         =0x19E8
    HINDI_SIGN,                                                            //KHMER_S_PRAM_BUON_KOET         =0x19E9
    HINDI_SIGN,                                                            //KHMER_S_DAP_KOET                     =0x19EA
    HINDI_SIGN,                                                            //KHMER_S_DAP_MUOY_KOET         =0x19EB
    HINDI_SIGN,                                                            //KHMER_S_DAP_PII_KOET             =0x19EC
    HINDI_SIGN,                                                            //KHMER_S_DAP_BEI_KOET             =0x19ED
    HINDI_SIGN,                                                            //KHMER_S_DAP_BUON_KOET         =0x19EE
    HINDI_SIGN,                                                            //KHMER_S_DAP_PRAM_KOET         =0x19EF
    HINDI_SIGN,                                                            //KHMER_S_TUTEYASAT                 =0x19F0
    HINDI_SIGN,                                                            //KHMER_S_MUOY_ROC                     =0x19F1
    HINDI_SIGN,                                                            //KHMER_S_PII_ROC                        =0x19F2
    HINDI_SIGN,                                                            //KHMER_S_BEI_ROC           =0x19F3
    HINDI_SIGN,                                                            //KHMER_S_BUON_ROC                     =0x19F4
    HINDI_SIGN,                                                            //KHMER_S_PRAM_ROC                     =0x19F5
    HINDI_SIGN,                                                            //KHMER_S_PRAM_MUOY_ROC         =0x19F6
    HINDI_SIGN,                                                            //KHMER_S_PRAM_PII_ROC             =0x19F7
    HINDI_SIGN,                                                            //KHMER_S_PRAM_BEI_ROC             =0x19F8
    HINDI_SIGN,                                                            //KHMER_S_PRAM_BUON_ROC         =0x19F9
    HINDI_SIGN,                                                            //KHMER_S_DAP_ROC                     =0x19FA
    HINDI_SIGN,                                                            //KHMER_S_DAP_MUOY_ROC             =0x19FB
    HINDI_SIGN,                                                            //KHMER_S_DAP_PII_ROC             =0x19FC
    HINDI_SIGN,                                                            //KHMER_S_DAP_BEI_ROC             =0x19FD
    HINDI_SIGN,                                                            //KHMER_S_DAP_BUON_ROC             =0x19FE
    HINDI_SIGN,                                                            //KHMER_S_DAP_PRAM_ROC             =0x19FF

    HINDI_INVALID
};


const HindiFeatureRecord_t _g_sKhmerFeatureMap[] =
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
    /*HINDI_FEATURE_CLIG*/  {HINDI_FEATURE_CLIG, _HindiCligFeatureMask},
    /*HINDI_FEATURE_ABVM*/ {HINDI_FEATURE_ABVM, _HindiAbvmFeatureMask},
    /*HINDI_FEATURE_BLWM*/ {HINDI_FEATURE_BLWM, _HindiBlwmFeatureMask},
    /*HINDI_FEATURE_DIST*/ {HINDI_FEATURE_DIST, _HindiDistFeatureMask},
    /*HINDI_FEATURE_MARK*/ {HINDI_FEATURE_MARK, _HindiMarkFeatureMask},
    /*HINDI_FEATURE_MKMK*/ {HINDI_FEATURE_MKMK, _HindiMkmkFeatureMask},
    /*HINDI_PRIV_FEATURE_TWOPART_JOIN*/ { HINDI_PRIV_FEATURE_TWOPART_JOIN , _HindiPrivTwoPartJoinFeatureMask }
};
const U16 _g_u16KhmerFeatureCount = (sizeof(_g_sKhmerFeatureMap)/sizeof(HindiFeatureRecord_t));

static U16 _msAPI_MLE_FontKhmerGetCluster( HindiScript_e eScript, const U16 *pu16Txt, U32 u32InLen, U16 *pu16Cluster, U16 u16BufferSize, U16 *pu16ConsumedCount, U16 *pu16SeqInCluster, BOOLEAN bIsDispStr, U32 *pu32FeatureTags );
static HindiCharacter_e _msAPI_MLE_FontKhmerGetCharType( U16 u16Character );
static U32 _msAPI_MLE_FontKhmerSetFeature( U32 u32FeatureTags, HindiFeature_e eFeature );
static U16 _msAPI_MLE_FontKhmerGetFeatureMap( const HindiFeatureRecord_t **ppasFeatureMap );
static BOOLEAN _msAPI_MLE_FontKhmerCharIsBlwf( U16 u16FirstChar, U16 u16SecondChar );
static U16 _msAPI_MLE_FontKhmerRefineCluster( HindiScript_e eScript, const U16 *pu16InTxt, U32 u32InLen, U32 u32Offset, U16 *pu16Cluster, U16 *pu16CluserSize, U16 u16ClusterOffset, BOOLEAN bIsDispStr, U32 *pu32Features, const U16 *pu16OriginTxt, U32 u32OriginOffset);

static S16 s16BaseGlyphIndex = -1;
static S16 s16MRIndex = -1;
//static S16 s16ROIndex = -1;
static S16 s16PreBaseVowelIndex = -1;
static U16 u16VPreCount = 0;
static S16 s16AnusvaraIndex = -1;
static U16 u16ACount = 0;
static S16 s16VBlwIndex = -1;
static U16 u16VBlwCount = 0;
static BOOLEAN bKinziFound = FALSE;
static BOOLEAN bConRoFound = FALSE;
static BOOLEAN bRegshiftCaseFound = FALSE;

__SLDPM_FREE__ const HindiTable_t g_khmrTable =
{
    HINDI_SCRIPT_KHMR,
    KHMER_C_KA,
    KHMER_S_ATTHACAN,
    &_msAPI_MLE_FontKhmerGetCluster,
    &_msAPI_MLE_FontKhmerRefineCluster,
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
    &_msAPI_MLE_FontKhmerGetCharType,
    NULL,//&_msAPI_MLE_FontMyanmarGetCharSpecialType,
    NULL,//&_FontBengGetCharOtherType,
    &_msAPI_MLE_FontKhmerCharIsBlwf,
    NULL,//&_msAPI_MLE_FontMyanmarCharIsPstf,
    NULL,//&_FontBengCharIsLigated,
    NULL,//&_msAPI_MLE_FontMyanmarStrWithAkhand,
    &_msAPI_MLE_FontKhmerSetFeature,
    &_msAPI_MLE_FontKhmerGetFeatureMap,
    NULL,//&_FontBengCharIsSign,
    NULL,//&_FontBengCharIsComposed,
    NULL,//&_msAPI_MLE_FontMyanmarFeatureWithRphf,
    NULL,//&_msAPI_MLE_FontMyanmarFeatureWithBlwf
};

__SLDPM_FREE__ const HindiTable_t g_khmrDigit1Table =
{
    HINDI_SCRIPT_KHMR_DIGIT1,
    KHMER_D_ZERO,
    KHMER_D_NINE,
    &_msAPI_MLE_FontKhmerGetCluster,
    &_msAPI_MLE_FontKhmerRefineCluster,
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
    &_msAPI_MLE_FontKhmerGetCharType,
    NULL,//&_msAPI_MLE_FontMyanmarGetCharSpecialType,
    NULL,//&_FontBengGetCharOtherType,
    &_msAPI_MLE_FontKhmerCharIsBlwf,
    NULL,//&_msAPI_MLE_FontMyanmarCharIsPstf,
    NULL,//&_FontBengCharIsLigated,
    NULL,//&_msAPI_MLE_FontMyanmarStrWithAkhand,
    &_msAPI_MLE_FontKhmerSetFeature,
    &_msAPI_MLE_FontKhmerGetFeatureMap,
    NULL,//&_FontBengCharIsSign,
    NULL,//&_FontBengCharIsComposed,
    NULL,//&_msAPI_MLE_FontMyanmarFeatureWithRphf,
    NULL,//&_msAPI_MLE_FontMyanmarFeatureWithBlwf
};

__SLDPM_FREE__ const HindiTable_t g_khmrDigit2Table =
{
    HINDI_SCRIPT_KHMR_DIGIT2,
    KHMER_S_LA_SON,
    KHMER_S_PRAM_BUON,
    &_msAPI_MLE_FontKhmerGetCluster,
    &_msAPI_MLE_FontKhmerRefineCluster,
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
    &_msAPI_MLE_FontKhmerGetCharType,
    NULL,//&_msAPI_MLE_FontMyanmarGetCharSpecialType,
    NULL,//&_FontBengGetCharOtherType,
    &_msAPI_MLE_FontKhmerCharIsBlwf,
    NULL,//&_msAPI_MLE_FontMyanmarCharIsPstf,
    NULL,//&_FontBengCharIsLigated,
    NULL,//&_msAPI_MLE_FontMyanmarStrWithAkhand,
    &_msAPI_MLE_FontKhmerSetFeature,
    &_msAPI_MLE_FontKhmerGetFeatureMap,
    NULL,//&_FontBengCharIsSign,
    NULL,//&_FontBengCharIsComposed,
    NULL,//&_msAPI_MLE_FontMyanmarFeatureWithRphf,
    NULL,//&_msAPI_MLE_FontMyanmarFeatureWithBlwf
};

__SLDPM_FREE__ const HindiTable_t g_khmrSymbolsTable =
{
    HINDI_SCRIPT_KHMR_SYMBOLS,
    KHMER_S_PATHAMASAT,
    KHMER_S_DAP_PRAM_ROC,
    &_msAPI_MLE_FontKhmerGetCluster,
    &_msAPI_MLE_FontKhmerRefineCluster,
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
    &_msAPI_MLE_FontKhmerGetCharType,
    NULL,//&_msAPI_MLE_FontMyanmarGetCharSpecialType,
    NULL,//&_FontBengGetCharOtherType,
    &_msAPI_MLE_FontKhmerCharIsBlwf,
    NULL,//&_msAPI_MLE_FontMyanmarCharIsPstf,
    NULL,//&_FontBengCharIsLigated,
    NULL,//&_msAPI_MLE_FontMyanmarStrWithAkhand,
    &_msAPI_MLE_FontKhmerSetFeature,
    &_msAPI_MLE_FontKhmerGetFeatureMap,
    NULL,//&_FontBengCharIsSign,
    NULL,//&_FontBengCharIsComposed,
    NULL,//&_msAPI_MLE_FontMyanmarFeatureWithRphf,
    NULL,//&_msAPI_MLE_FontMyanmarFeatureWithBlwf
};

#if (KHMER_SPECIAL_CHARACTER)
__SLDPM_FREE__ const HindiTable_t g_SpecialSymbolsTable =
{
    HINDI_SCRIPT_KHMR,
    SPECIAL_CONTROL_UNIT_WS,
    SPECIAL_CONTROL_UNIT_WS,
    &_msAPI_MLE_FontKhmerGetCluster,
    &_msAPI_MLE_FontKhmerRefineCluster,
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
    &_msAPI_MLE_FontKhmerGetCharType,
    NULL,//&_msAPI_MLE_FontMyanmarGetCharSpecialType,
    NULL,//&_FontBengGetCharOtherType,
    &_msAPI_MLE_FontKhmerCharIsBlwf,
    NULL,//&_msAPI_MLE_FontMyanmarCharIsPstf,
    NULL,//&_FontBengCharIsLigated,
    NULL,//&_msAPI_MLE_FontMyanmarStrWithAkhand,
    &_msAPI_MLE_FontKhmerSetFeature,
    &_msAPI_MLE_FontKhmerGetFeatureMap,
    NULL,//&_FontBengCharIsSign,
    NULL,//&_FontBengCharIsComposed,
    NULL,//&_msAPI_MLE_FontMyanmarFeatureWithRphf,
    NULL,//&_msAPI_MLE_FontMyanmarFeatureWithBlwf
};
#endif

static U16 _msAPI_MLE_FontKhmerGetCluster( HindiScript_e eScript, const U16 *pu16Txt, U32 u32InLen, U16 *pu16Cluster, U16 u16BufferSize, U16 *pu16ConsumedCount, U16 *pu16SeqInCluster, BOOLEAN bIsDispStr, U32 *pu32FeatureTags )
{
    U16 u16Character = 0;
    KhmerParserState_e eClusterState = CLUSTER_INIT;
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
    bConRoFound = FALSE;
    bRegshiftCaseFound = FALSE;

    while( (u16Index < u32InLen) && ( bExit == FALSE ) && ( bErrExit == FALSE ) && ( *pu16ConsumedCount <= u32InLen ) )
    {
        u16Character = pu16Txt[u16Index];
        eType = _msAPI_MLE_FontKhmerGetCharType(u16Character);
        switch(eType)
        {
        case HINDI_CON:
            if ( eClusterState == CLUSTER_INIT)
            {
                eClusterState = CLUSTER_BASE;
                //Todo: Fix me, should we separate consonant case and other case?
                s16BaseGlyphIndex = u16Index;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontKhmerGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_COENG) && ( eTypeNext != HINDI_VPRE) &&
                         ( eTypeNext != HINDI_VBLW) && ( eTypeNext != HINDI_REGSHIFT) &&
                         ( eTypeNext != HINDI_VABV) && ( eTypeNext != HINDI_SABV) &&
                         ( eTypeNext != HINDI_VPST) && ( eTypeNext != HINDI_SPST) &&
                         (eTypeNext != HINDI_DEPVOW) )
                    {
                        bExit = TRUE;
                    }
                }
            }
            else if( eClusterState == CLUSTER_COENG )
            {
                eClusterState = CLUSTER_COENG_S;
                //Todo: Fix me, should we separate consonant case and other case?
                //s16BaseGlyphIndex = u16Index;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontKhmerGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_COENG) && ( eTypeNext != HINDI_VPRE) &&
                         ( eTypeNext != HINDI_VBLW) && ( eTypeNext != HINDI_REGSHIFT) &&
                         ( eTypeNext != HINDI_VABV) && ( eTypeNext != HINDI_SABV) &&
                         ( eTypeNext != HINDI_VPST) && ( eTypeNext != HINDI_SPST) &&
                         (eTypeNext != HINDI_DEPVOW) )
                    {
                        bExit = TRUE;
                    }
                }

                if (pu16Txt[u16Index] == KHMER_C_RO)
                {
                    bConRoFound = TRUE;
                    *pu32FeatureTags = _msAPI_MLE_FontKhmerSetFeature(*pu32FeatureTags, HINDI_FEATURE_PREF);
                    *pu32FeatureTags = _msAPI_MLE_FontKhmerSetFeature(*pu32FeatureTags, HINDI_FEATURE_PRES);
                }
                else
                {
                    *pu32FeatureTags = _msAPI_MLE_FontKhmerSetFeature(*pu32FeatureTags, HINDI_FEATURE_BLWF);
                    *pu32FeatureTags = _msAPI_MLE_FontKhmerSetFeature(*pu32FeatureTags, HINDI_FEATURE_PSTF);
                }

            }

            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        case HINDI_COENG:
            if ( (eClusterState == CLUSTER_BASE ) ||(eClusterState == CLUSTER_COENG_S ) )
            {
                eClusterState = CLUSTER_COENG;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontKhmerGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_CON) && ( eTypeNext != HINDI_INDVOW) )
                    {
                        bExit = TRUE;
                    }
                }
            }

            //*pu32FeatureTags = _msAPI_MLE_FontKhmerSetFeature(*pu32FeatureTags, HINDI_FEATURE_BLWF);
            //*pu32FeatureTags = _msAPI_MLE_FontKhmerSetFeature(*pu32FeatureTags, HINDI_FEATURE_PSTF);

            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        case HINDI_INDVOW:
            if (eClusterState == CLUSTER_INIT)
            {
                eClusterState = CLUSTER_BASE;
                //Todo: Fix me, should we separate consonant case and other case?
                s16BaseGlyphIndex = u16Index;

                if ((U16)(u16Index + 1) < u32InLen)
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontKhmerGetCharType(pu16Txt[u16Index + 1]);
                    if ((eTypeNext != HINDI_COENG) && (eTypeNext != HINDI_VPRE) &&
                        (eTypeNext != HINDI_VBLW) && (eTypeNext != HINDI_REGSHIFT) &&
                        (eTypeNext != HINDI_VABV) && (eTypeNext != HINDI_SABV) &&
                        (eTypeNext != HINDI_VPST) && (eTypeNext != HINDI_SPST) &&
                        (eTypeNext != HINDI_DEPVOW))
                    {
                        bExit = TRUE;
                    }
                }
            }
            else if( eClusterState == CLUSTER_COENG)
            {
                eClusterState = CLUSTER_COENG_S;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontKhmerGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_COENG) && ( eTypeNext != HINDI_VPRE) &&
                         ( eTypeNext != HINDI_VBLW) && ( eTypeNext != HINDI_REGSHIFT) &&
                         ( eTypeNext != HINDI_VABV) && ( eTypeNext != HINDI_SABV) &&
                         ( eTypeNext != HINDI_VPST) && ( eTypeNext != HINDI_SPST) &&
                         (eTypeNext != HINDI_DEPVOW) )
                    {
                        bExit = TRUE;
                    }

                    *pu32FeatureTags = _msAPI_MLE_FontKhmerSetFeature(*pu32FeatureTags, HINDI_FEATURE_BLWF);
                    *pu32FeatureTags = _msAPI_MLE_FontKhmerSetFeature(*pu32FeatureTags, HINDI_FEATURE_PSTF);

                }
            }

            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        case HINDI_VPRE:
            if ( ( eClusterState == CLUSTER_BASE) || ( eClusterState == CLUSTER_COENG_S) )
            {
                eClusterState = CLUSTER_SYLLABLE_S1;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontKhmerGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_REGSHIFT) && ( eTypeNext != HINDI_VABV) &&
                         ( eTypeNext != HINDI_SABV) && ( eTypeNext != HINDI_VPST) &&
                         ( eTypeNext != HINDI_SPST) && (eTypeNext != HINDI_DEPVOW))
                    {
                        bExit = TRUE;
                    }
                }
            }
            else
            {
                bExit = TRUE;
            }

            if ( u16VPreCount == 0 )
            {
                s16PreBaseVowelIndex = u16Index;
            }
            u16VPreCount++;

            *pu32FeatureTags = _msAPI_MLE_FontKhmerSetFeature(*pu32FeatureTags, HINDI_FEATURE_PREF);
            *pu32FeatureTags = _msAPI_MLE_FontKhmerSetFeature(*pu32FeatureTags, HINDI_FEATURE_PRES);
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        case HINDI_VBLW:
            if ( ( eClusterState == CLUSTER_BASE ) || ( eClusterState == CLUSTER_COENG_S ) )
            {
                eClusterState = CLUSTER_SYLLABLE_S1;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontKhmerGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_REGSHIFT) && ( eTypeNext != HINDI_VABV) &&
                         ( eTypeNext != HINDI_SABV) && ( eTypeNext != HINDI_VPST) &&
                         ( eTypeNext != HINDI_SPST) && (eTypeNext != HINDI_DEPVOW))
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

            *pu32FeatureTags = _msAPI_MLE_FontKhmerSetFeature(*pu32FeatureTags, HINDI_FEATURE_BLWF);
            *pu32FeatureTags = _msAPI_MLE_FontKhmerSetFeature(*pu32FeatureTags, HINDI_FEATURE_BLWS);
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        case HINDI_REGSHIFT:
            if ( ( eClusterState == CLUSTER_BASE ) || ( eClusterState == CLUSTER_COENG_S ) ||
                 ( eClusterState == CLUSTER_SYLLABLE_S1 ) )
            {
                eClusterState = CLUSTER_SYLLABLE_S2;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontKhmerGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_VABV ) && ( eTypeNext != HINDI_SABV ) &&
                         ( eTypeNext != HINDI_VPST ) && ( eTypeNext != HINDI_SPST) &&
                         (eTypeNext != HINDI_DEPVOW))
                    {
                        bExit = TRUE;
                    }
                }
            }

            //*pu32FeatureTags = _msAPI_MLE_FontKhmerSetFeature(*pu32FeatureTags, HINDI_FEATURE_ABVS);
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        case HINDI_VABV:
            if ( ( eClusterState == CLUSTER_BASE ) || ( eClusterState == CLUSTER_COENG_S ) ||
                 ( eClusterState == CLUSTER_SYLLABLE_S1 ) || ( eClusterState == CLUSTER_SYLLABLE_S2 ) )
            {
                bRegshiftCaseFound = FALSE;

                if (eClusterState == CLUSTER_SYLLABLE_S2)
                {
                    bRegshiftCaseFound = TRUE;
                }
                eClusterState = CLUSTER_SYLLABLE_S3;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontKhmerGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_SABV ) && ( eTypeNext != HINDI_VPST ) && ( eTypeNext != HINDI_SPST) )
                    {
                        bExit = TRUE;
                    }
                }
            }

            if (bRegshiftCaseFound)
            {
                *pu32FeatureTags = _msAPI_MLE_FontKhmerSetFeature(*pu32FeatureTags, HINDI_FEATURE_BLWF);
            }
            else
            {
                *pu32FeatureTags = _msAPI_MLE_FontKhmerSetFeature(*pu32FeatureTags, HINDI_FEATURE_ABVS);
            }

            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        case HINDI_SABV:
            if ( ( eClusterState == CLUSTER_BASE ) || ( eClusterState == CLUSTER_COENG_S ) ||
                 ( eClusterState == CLUSTER_SYLLABLE_S1 ) || ( eClusterState == CLUSTER_SYLLABLE_S2 ) ||
                 ( eClusterState == CLUSTER_SYLLABLE_S3 ) || ( eClusterState == CLUSTER_SYLLABLE_S4 ) )
            {
                eClusterState = CLUSTER_SYLLABLE_S4;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontKhmerGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_SABV ) && ( eTypeNext != HINDI_VPST ) && ( eTypeNext != HINDI_SPST) && (eTypeNext != HINDI_DEPVOW))
                    {
                        bExit = TRUE;
                    }
                }
            }

            *pu32FeatureTags = _msAPI_MLE_FontKhmerSetFeature(*pu32FeatureTags, HINDI_FEATURE_ABVS);
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        case HINDI_VPST:
            if ( ( eClusterState == CLUSTER_BASE ) || ( eClusterState == CLUSTER_COENG_S ) ||
                 ( eClusterState == CLUSTER_SYLLABLE_S1 ) || ( eClusterState == CLUSTER_SYLLABLE_S2 ) ||
                 ( eClusterState == CLUSTER_SYLLABLE_S3 ) || ( eClusterState == CLUSTER_SYLLABLE_S4 ) )
            {
                eClusterState = CLUSTER_SYLLABLE_S5;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontKhmerGetCharType(pu16Txt[u16Index+1]);
                    if (  eTypeNext != HINDI_SPST )
                    {
                        bExit = TRUE;
                    }
                }
            }
            *pu32FeatureTags = _msAPI_MLE_FontKhmerSetFeature(*pu32FeatureTags, HINDI_FEATURE_PSTF);
            *pu32FeatureTags = _msAPI_MLE_FontKhmerSetFeature(*pu32FeatureTags, HINDI_FEATURE_PSTS);
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        case HINDI_SPST:
            if ( ( eClusterState == CLUSTER_BASE ) || ( eClusterState == CLUSTER_COENG_S ) ||
                 ( eClusterState == CLUSTER_SYLLABLE_S1 ) || ( eClusterState == CLUSTER_SYLLABLE_S2 ) ||
                 ( eClusterState == CLUSTER_SYLLABLE_S3 ) || ( eClusterState == CLUSTER_SYLLABLE_S4 ) ||
                 ( eClusterState == CLUSTER_SYLLABLE_S5 ))
            {
                eClusterState = CLUSTER_SYLLABLE_S6;
                bExit = TRUE;
            }

            *pu32FeatureTags = _msAPI_MLE_FontKhmerSetFeature(*pu32FeatureTags, HINDI_FEATURE_PSTF);
            *pu32FeatureTags = _msAPI_MLE_FontKhmerSetFeature(*pu32FeatureTags, HINDI_FEATURE_PSTS);
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        case HINDI_DEPVOW:
            if (u16Character == KHMER_DV_OE)
            {
                if ((eClusterState == CLUSTER_BASE) || (eClusterState == CLUSTER_COENG_S) ||
                    (eClusterState == CLUSTER_SYLLABLE_S1) || (eClusterState == CLUSTER_SYLLABLE_S2))
                {
                    bRegshiftCaseFound = FALSE;

                    if (eClusterState == CLUSTER_SYLLABLE_S2)
                    {
                        bRegshiftCaseFound = TRUE;
                    }
                    eClusterState = CLUSTER_SYLLABLE_S3;

                    if ((U16)(u16Index + 1) < u32InLen)
                    {
                        HindiCharacter_e eTypeNext = HINDI_INVALID;

                        eTypeNext = _msAPI_MLE_FontKhmerGetCharType(pu16Txt[u16Index + 1]);
                        if ((eTypeNext != HINDI_SABV) && (eTypeNext != HINDI_VPST) && (eTypeNext != HINDI_SPST))
                        {
                            bExit = TRUE;
                        }
                    }
                }
                else
                {
                    bExit = TRUE;
                    break;
                }
                *pu32FeatureTags = _msAPI_MLE_FontKhmerSetFeature(*pu32FeatureTags, HINDI_PRIV_FEATURE_TWOPART_JOIN);

                if (bRegshiftCaseFound)
                {
                    *pu32FeatureTags = _msAPI_MLE_FontKhmerSetFeature(*pu32FeatureTags, HINDI_FEATURE_BLWF);
                }
                else
                {
                    *pu32FeatureTags = _msAPI_MLE_FontKhmerSetFeature(*pu32FeatureTags, HINDI_FEATURE_ABVS);
                }
            }
            else
            {
                if ((eClusterState == CLUSTER_BASE) || (eClusterState == CLUSTER_COENG_S) ||
                    (eClusterState == CLUSTER_SYLLABLE_S1) || (eClusterState == CLUSTER_SYLLABLE_S2) ||
                    (eClusterState == CLUSTER_SYLLABLE_S3) || (eClusterState == CLUSTER_SYLLABLE_S4))
                {
                    eClusterState = CLUSTER_SYLLABLE_S5;

                    if ((U16)(u16Index + 1) < u32InLen)
                    {
                        HindiCharacter_e eTypeNext = HINDI_INVALID;

                        eTypeNext = _msAPI_MLE_FontKhmerGetCharType(pu16Txt[u16Index + 1]);
                        if (eTypeNext != HINDI_SPST)
                        {
                            bExit = TRUE;
                        }
                    }
                }
                else
                {
                    bExit = TRUE;
                    break;
                }

                *pu32FeatureTags = _msAPI_MLE_FontKhmerSetFeature(*pu32FeatureTags, HINDI_PRIV_FEATURE_TWOPART_JOIN);
                *pu32FeatureTags = _msAPI_MLE_FontKhmerSetFeature(*pu32FeatureTags, HINDI_FEATURE_PSTF);
                *pu32FeatureTags = _msAPI_MLE_FontKhmerSetFeature(*pu32FeatureTags, HINDI_FEATURE_PSTS);
            }

            //bTwoPartCaseFound = TRUE;

            *pu32FeatureTags = _msAPI_MLE_FontKhmerSetFeature(*pu32FeatureTags, HINDI_FEATURE_PREF);
            //*pu32FeatureTags = _msAPI_MLE_FontKhmerSetFeature(*pu32FeatureTags, HINDI_FEATURE_PSTS);
            _HINDI_FILL_CLUSTER(pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster);
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        case HINDI_NUM:
        case HINDI_SIGN:
            //bExit = TRUE;

            _HINDI_FILL_CLUSTER(pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster);
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;
#if(KHMER_SPECIAL_CHARACTER)        
        case HINDI_WS:
            if (eClusterState != CLUSTER_INIT)
            {
                bErrExit = TRUE;
                break;
            }

            eClusterState = CLUSTER_INIT;
            {
                //Found cluster with only one character
                u16ClusterSize = 0;

                bExit = TRUE;

                _HINDI_FILL_CLUSTER(pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster);//lc@@
                _HINDI_VERLIFY_LEN(pu16Txt, *pu16ConsumedCount, u32InLen);
            }
            break;
#endif

        default:
            {
                _HINDI_FILL_CLUSTER(pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster);
                u16Index++;
                _HINDI_VERLIFY_LEN(pu16Txt, *pu16ConsumedCount, u32InLen);
                u16Character = pu16Txt[*pu16ConsumedCount];
                break;
            }

        }
    }

    return *pu16ConsumedCount;
}

static HindiCharacter_e _msAPI_MLE_FontKhmerGetCharType( U16 u16Character )
{
    HindiCharacter_e eType = HINDI_INVALID;

    if ( IS_KHMER_RANGE(u16Character) )
    {
        eType = (g_KhmerCharTypeArray[u16Character - KHMER_MASK]);
    }
    else if ( IS_KHMER_DIGIT1_RANGE(u16Character) )
    {
        eType = (g_KhmerDigitICharTypeArray[u16Character - KHMER_DIGIT1_MASK]);
    }
    else if ( IS_KHMER_DIGIT2_RANGE(u16Character) )
    {
        eType = (g_KhmerDigitIICharTypeArray[u16Character - KHMER_DIGIT2_MASK]);
    }
    else if ( IS_KHMER_SYMBOLS_RANGE(u16Character) )
    {
        eType = (g_KhmerSymbolCharTypeArray[u16Character - KHMER_SYMBOLS_MASK]);
    }
    else
    {
        switch (u16Character)
        {
        case 0x200B:    //ZWSP, Zero Width Space
            eType = HINDI_WS;
            break;
        case 0x200C:
        case 0x200D:
            eType = HINDI_J;  //Joiners
            break;
        default:
            break;
        }
    }

    return eType;
}

static U32 _msAPI_MLE_FontKhmerSetFeature( U32 u32FeatureTags, HindiFeature_e eFeature )
{
    U16 i;
    for ( i = 0; i < _g_u16KhmerFeatureCount; i++ )
    {
        if ( _g_sKhmerFeatureMap[i].eTag == eFeature )
        {
            u32FeatureTags = u32FeatureTags | _g_sKhmerFeatureMap[i].u32Mask;
            break;
        }
    }
    return u32FeatureTags;
}

static U16 _msAPI_MLE_FontKhmerGetFeatureMap( const HindiFeatureRecord_t **ppasFeatureMap )
{
    *ppasFeatureMap = _g_sKhmerFeatureMap;
    return (U16)_g_u16KhmerFeatureCount;
}

static BOOLEAN _msAPI_MLE_FontKhmerCharIsBlwf( U16 u16FirstChar, U16 u16SecondChar )
{
    BOOLEAN bResult = FALSE;
//    HindiCharacter_e heFirstChar =_msAPI_MLE_FontKhmerGetCharType(u16FirstChar);
    HindiCharacter_e heSecondChar = _msAPI_MLE_FontKhmerGetCharType(u16SecondChar);

    if ( IS_KHMER_ALL_RANGE(u16FirstChar) && IS_KHMER_ALL_RANGE(u16SecondChar) )
    {
        if ( IS_KHMER_COENG_CHAR(u16FirstChar) )
        {
            switch( heSecondChar )
            {
                case HINDI_CON:
                    bResult = TRUE;
                    break;
                case HINDI_INDVOW:
                    bResult = TRUE;
                    break;
            }
        }
        else if(IS_KHMER_REGSHIFT_CHAR(u16FirstChar))
        {
            if( heSecondChar == HINDI_VABV)
            {
                bResult = TRUE;
            }
        }
    }

    return bResult;
}

static U16 _msAPI_MLE_FontKhmerRefineCluster( HindiScript_e eScript, const U16 *pu16InTxt, U32 u32InLen, U32 u32Offset, U16 *pu16Cluster, U16 *pu16CluserSize, U16 u16ClusterOffset, BOOLEAN bIsDispStr, U32 *pu32Features, const U16 *pu16OriginTxt, U32 u32OriginOffset)
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
    if ( bConRoFound )
    {
        U16 u16Temp;

        u16Temp = pu16Cluster[s16BaseGlyphIndex];

        for(i=0;i<2;i++)
        {
            pu16Cluster[s16BaseGlyphIndex+i] = pu16Cluster[s16BaseGlyphIndex+i+1];
        }
        pu16Cluster[s16BaseGlyphIndex+2] = u16Temp;
        //s16BaseGlyphIndex = 0;
    }

    if (u16VPreCount)
    {
        U16 u16Temp;
        u16Temp = pu16Cluster[s16PreBaseVowelIndex];

        for (i = s16PreBaseVowelIndex; i>0; i--)
        {
            pu16Cluster[i] = pu16Cluster[i-1];
        }
        pu16Cluster[0] = u16Temp;
    }

    //The medial ra (MR) is reordered before the base consonant
    /*if ( ( s16MRIndex > 0 ) && ( s16BaseGlyphIndex < s16MRIndex ) )
    {
        //Todo: Fix me, should we limit this base glyph to must be consonant glyph?
        if ( HINDI_CON == _msAPI_MLE_FontKhmerGetCharType(pu16Cluster[s16BaseGlyphIndex]) )
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
    }*/

    return u16ClusterOffset;
}

#endif //__MYMR_FONT__
#endif //__INDIC_FONT__
