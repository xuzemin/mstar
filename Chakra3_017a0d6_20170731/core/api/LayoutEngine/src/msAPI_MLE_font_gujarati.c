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

#include "msAPI_MLE_common_def.h"
#include "msAPI_MLE_font_base.h"
#include "msAPI_MLE_font_hindi_priv.h"

#ifdef __GUJR_FONT__
#include "msAPI_MLE_font_gujarati.h"

const U8 g_GujrCharTypeArray[] =
{
    HINDI_INVALID,

    /* Various signs*/
    HINDI_SIGN   | HINDI_SP_CENTER_T_UP_POS,//GUJARATI_S_CHANDRA_BINDU=0xA81,
    HINDI_SIGN   | HINDI_SP_CENTER_T_UP_POS,    //GUJARATI_S_ANUSVARA=0xA82,
    HINDI_SIGN   | HINDI_SP_RIGHT_POS,    //GUJARATI_S_VISARGA=0xA83,
    
    HINDI_INVALID,
    
    /* Independent vowels */
    HINDI_INDVOW | HINDI_SP_RIGHT_T,       //GUJARATI_IV_A=0xA85,
    HINDI_INDVOW | HINDI_SP_DOUBLE_T,      //GUJARATI_IV_AA=0xA86,
    HINDI_INDVOW | HINDI_SP_NO_T,          //GUJARATI_IV_I=0xA87,
    HINDI_INDVOW | HINDI_SP_NO_T,          //GUJARATI_IV_II=0xA88,
    HINDI_INDVOW | HINDI_SP_NO_T,          //GUJARATI_IV_U=0xA89,
    HINDI_INDVOW | HINDI_SP_NO_T,          //GUJARATI_IV_UU=0xA8a,
    HINDI_INDVOW | HINDI_SP_DOUBLE_T,      //GUJARATI_IV_VR=0xA8b,
    HINDI_INDVOW | HINDI_SP_NO_T,          //GUJARATI_IV_VL=0xA8c,
    HINDI_INDVOW | HINDI_SP_RIGHT_T,        //GUJARATI_CE=0xA8d,
    HINDI_INVALID,
    HINDI_INDVOW | HINDI_SP_RIGHT_T,       //GUJARATI_IV_E=0xA8f,
    HINDI_INDVOW | HINDI_SP_RIGHT_T,          //GUJARATI_IV_AI=0xA90,
    HINDI_INDVOW | HINDI_SP_DOUBLE_T,       //GUJARATI_IV_CO=0xA91,
    HINDI_INVALID,
    HINDI_INDVOW | HINDI_SP_DOUBLE_T,          //GUJARATI_IV_O=0xA93,
    HINDI_INDVOW | HINDI_SP_DOUBLE_T,          //GUJARATI_IV_AU=0xA94,

    /* Consonants */
    HINDI_CON    | HINDI_SP_NO_T,           //GUJARATI_C_KA=0xA95,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //GUJARATI_C_KHA=0xA96,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //GUJARATI_C_GA=0xA97,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //GUJARATI_C_GHA=0xA98,
    HINDI_CON    | HINDI_SP_NO_T,      //GUJARATI_C_NGA=0xA99,
    HINDI_CON    | HINDI_SP_RIGHT_T,      //GUJARATI_C_CA=0xA9a,
    HINDI_CON    | HINDI_SP_NO_T,      //GUJARATI_C_CHA=0xA9b,
    HINDI_CON    | HINDI_SP_NO_T,      //GUJARATI_C_JA=0xA9c,
    HINDI_CON    | HINDI_SP_NO_T,      //GUJARATI_C_JHA=0xA9d,
    HINDI_CON    | HINDI_SP_RIGHT_T,      //GUJARATI_C_NYA=0xA9e,
    HINDI_CON    | HINDI_SP_NO_T,      //GUJARATI_C_TTA=0xA9f,  
    HINDI_CON    | HINDI_SP_NO_T,          //GUJARATI_C_TTHA=0xAa0,
    HINDI_CON    | HINDI_SP_NO_T,      //GUJARATI_C_DDA=0xAa1,
    HINDI_CON    | HINDI_SP_NO_T,      //GUJARATI_C_DDHA=0xAa2,
    HINDI_CON    | HINDI_SP_NO_T,       //GUJARATI_C_NNA=0xAa3,
    HINDI_CON    | HINDI_SP_RIGHT_T,      //GUJARATI_C_TA=0xAa4,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //GUJARATI_C_THA=0xAa5,
    HINDI_CON    | HINDI_SP_NO_T,      //GUJARATI_C_DA=0xAa6,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //GUJARATI_C_DHA=0xAa7,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //GUJARATI_C_NA=0xAa8,
    HINDI_INVALID,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //GUJARATI_C_PA=0xAaa,
    HINDI_CON    | HINDI_SP_NO_T,      //GUJARATI_C_PHA=0xAab,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //GUJARATI_C_BA=0xAac,
    HINDI_CON    | HINDI_SP_RIGHT_T,      //GUJARATI_C_BHA=0xAad,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //GUJARATI_C_MA=0xAae,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //GUJARATI_C_YA=0xAaf,
    HINDI_CON    | HINDI_SP_NO_T,       //GUJARATI_C_RA=0xAb0,
    HINDI_INVALID,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //GUJARATI_C_LA=0xAb2,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //GUJARATI_C_LLA=0xAb3,
    HINDI_INVALID,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //GUJARATI_C_VA=0xAb5,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //GUJARATI_C_SHA=0xAb6,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //GUJARATI_C_SSA=0xAb7,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //GUJARATI_C_SA=0xAb8,
    HINDI_CON    | HINDI_SP_NO_T,      //GUJARATI_C_HA=0xAb9,
    
    HINDI_INVALID,
    HINDI_INVALID,
    
    /* Various signs */
    HINDI_SIGN   | HINDI_SP_LEFT_T_DOWN_POS,//GUJARATI_S_NUKTA=0xAbc,
    HINDI_SIGN   | HINDI_SP_RIGHT_POS,     //GUJARATI_S_AVAGRAH=0xAbd,

    /* Dependent vowel signs */
    HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,  //GUJARATI_DV_AA=0xAbe,
    HINDI_DEPVOW | HINDI_SP_LEFT_JOINER,   //GUJARATI_DV_I   =0xAbf,
    HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,  //GUJARATI_DV_II=0xAc0,
    HINDI_DEPVOW | HINDI_SP_CENTER_T_DOWN_POS,  //GUJARATI_DV_U=0xAc1,
    HINDI_DEPVOW | HINDI_SP_CENTER_T_DOWN_POS,//GUJARATI_DV_UU=0xAc2,
    HINDI_DEPVOW | HINDI_SP_CENTER_T_DOWN_POS,//GUJARATI_DV_VR=0xAc3,
    HINDI_DEPVOW | HINDI_SP_CENTER_T_DOWN_POS, //GUJARATI_DV_VRR=0xAc4,
    HINDI_DEPVOW | HINDI_SP_CENTER_T_UP_POS,//GUJARATI_DV_CE=0xAc5,
    HINDI_INVALID,
    HINDI_DEPVOW | HINDI_SP_LEFT_T_UP_POS,   //GUJARATI_DV_E=0xAc7
    HINDI_DEPVOW | HINDI_SP_LEFT_T_UP_POS,   //GUJARATI_DV_AI=0xAc8
    HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,   //GUJARATI_DV_CO=0xAc9,
    HINDI_INVALID,
    HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,//GUJARATI_DV_O=0xAcb,
    HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,//GUJARATI_DV_AU=0xAcc,

    /* Virama */
    HINDI_SIGN | HINDI_SP_RIGHT_T_DOWN_POS,//GUJARATI_S_HALANT   =0xAcd,
    
    HINDI_INVALID,
    HINDI_INVALID,
    
    HINDI_INDVOW | HINDI_SP_RIGHT_T,        //GUJARATI_S_OM=0xAd0,
    
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    
    /*Additional vowels for Sanskrit*/
    HINDI_INDVOW | HINDI_SP_CENTER_T,       //GUJARATI_C_VRR=0xAe0,
    HINDI_INDVOW | HINDI_SP_NO_T,          //GUJARATI_C_VLL=0xAe1,
    HINDI_DEPVOW | HINDI_SP_CENTER_T_DOWN_POS,    //GUJARATI_S_VL=0xAe2,
    HINDI_DEPVOW | HINDI_SP_CENTER_T_DOWN_POS,  //GUJARATI_S_VLL=0xAe3,
    
    HINDI_INVALID,
    HINDI_INVALID,
    
    /* Digits */
    HINDI_NUM,                             //GUJARATI_D_ZERO=0xAe6,
    HINDI_NUM,                             //GUJARATI_D_ONE=0xAe7,
    HINDI_NUM,                             //GUJARATI_D_TWO=0xAe8,
    HINDI_NUM,                             //GUJARATI_D_THREE=0xAe9,
    HINDI_NUM,                             //GUJARATI_D_FOUR=0xAea,
    HINDI_NUM,                             //GUJARATI_D_FIVE=0xAeb,
    HINDI_NUM,                             //GUJARATI_D_SIX=0xAec,
    HINDI_NUM,                             //GUJARATI_D_SEVEN=0xAed,
    HINDI_NUM,                             //GUJARATI_D_EIGHT=0xAee,
    HINDI_NUM,                             //GUJARATI_D_NINE=0xAef,

    /* Gujarati-specific additions */
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW,  //GUJARATI_S_ABBR=0xAf0
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW,  //GUJARATI_C_RUPEE_SIGN=0xAf1,
};                  

/* VARIOUS SIGNS TABLES */

/*    CONSONANT'S TABLES   */

const HindiFeatureRecord_t _g_sGujrFeatureMap[] = 
{
/*HINDI_FEATURE_LOCL*/  {HINDI_FEATURE_LOCL, _HindiLoclFeatureMask},
/*HINDI_FEATURE_NUKT*/  {HINDI_FEATURE_NUKT, _HindiNuktFeatureMask},
/*HINDI_FEATURE_AKHN*/  {HINDI_FEATURE_AKHN, _HindiAkhnFeatureMask},
/*HINDI_FEATURE_RPHF*/  {HINDI_FEATURE_RPHF, _HindiRphfFeatureMask},
/*HINDI_FEATURE_RPHF*/  {HINDI_FEATURE_RKRF, _HindiRkrfFeatureMask},
/*HINDI_FEATURE_BLWF*/  {HINDI_FEATURE_BLWF, _HindiBlwfFeatureMask},
/*HINDI_FEATURE_HALF*/  {HINDI_FEATURE_HALF, _HindiHalfFeatureMask},
/*HINDI_FEATURE_VATU*/  {HINDI_FEATURE_VATU, _HindiVatuFeatureMask},
/*HINDI_FEATURE_CJCT*/  {HINDI_FEATURE_CJCT, _HindiCjctFeatureMask},
/*HINDI_FEATURE_PRES*/  {HINDI_FEATURE_PRES, _HindiPresFeatureMask},
/*HINDI_FEATURE_ABVS*/  {HINDI_FEATURE_ABVS, _HindiAbvsFeatureMask},
/*HINDI_FEATURE_BLWS*/ {HINDI_FEATURE_BLWS, _HindiBlwsFeatureMask},
/*HINDI_FEATURE_PSTS*/  {HINDI_FEATURE_PSTS, _HindiPstsFeatureMask},
/*HINDI_FEATURE_HALN*/  {HINDI_FEATURE_HALN, _HindiHalnFeatureMask},
/*HINDI_FEATURE_CALT*/  {HINDI_FEATURE_CALT, _HindiCaltFeatureMask},
/*HINDI_FEATURE_ABVM*/ {HINDI_FEATURE_ABVM, _HindiAbvmFeatureMask},
/*HINDI_FEATURE_BLWM*/ {HINDI_FEATURE_BLWM, _HindiBlwmFeatureMask}
};
const U16 _g_u16GujrFeatureCount = (sizeof(_g_sGujrFeatureMap)/sizeof(HindiFeatureRecord_t));

static BOOLEAN _msAPI_MLE_FontGujrCharIsRA( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontGujrCharIsHalant( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontGujrCharIsNukta( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontGujrCharIsBindu( U16 u16Character );
//static BOOLEAN _msAPI_MLE_FontGujrCharWithNukta( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontGujrCharIsNoHalfCon( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontGujrCharIsFollowingZWJ( U16 u16Character );
static HindiCharacter_e _msAPI_MLE_FontGujrGetCharType( U16 u16Character );
static HindiSpecialCharacter_e _msAPI_MLE_FontGujrGetCharSpecialType( U16 u16Character );
static HindiOtherCharacterType_e _msAPI_MLE_FontGujrGetCharOtherType( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontGujrCharIsBlwf( U16 u16FirstChar, U16 u16SecondChar );
//static const HindiMainTable_t* _msAPI_MLE_FontGujrGetCharRuleTable( U16 u16Character );
//static BOOLEAN _msAPI_MLE_FontGujrReplaceOutputChar( U16 *pu16Cluster, U16 u16ClusterSize, U16 u16ClustIndex, U16 *pu16Index, U16 u16MatchedLen, U16 *pu16RemainSize, U16 *pu16OutGlyph, U16 *pu16OutGlyphLen, U16 u16OffsetInConcatenation, U16 *pu16OffsetInConcatenation, U16 *pu16OffsetInComposed, U16 *pu16ConcatenationComposedSize );
static U32 _msAPI_MLE_FontGujrSetFeature( U32 u32FeatureTags, HindiFeature_e eFeature );
static U16 _msAPI_MLE_FontGujrGetFeatureMap( const HindiFeatureRecord_t **ppasFeatureMap );
static BOOLEAN _msAPI_MLE_FontGujrStrWithAkhand( U16 *pu16Str, U32 u32StrLen, U16 u16Offset );

static BOOLEAN _msAPI_MLE_FontGujrCharIsSign( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontGujrCharIsComposed( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontGujrFeatureWithRphf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType );
static BOOLEAN _msAPI_MLE_FontGujrFeatureWithBlwf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType );

__SLDPM_FREE__ const HindiTable_t g_gujrTable =
{
    HINDI_SCRIPT_GUJR,
    GUJARATI_S_CHANDRA_BINDU,
    GUJARATI_C_RUPEE_SIGN,
    NULL, //fnGetCluster
    NULL, //fnRefineCluster
    NULL, //fnGetNextCodeXOffset
    &_msAPI_MLE_FontGujrCharIsRA,
    &_msAPI_MLE_FontGujrCharIsHalant,
    &_msAPI_MLE_FontGujrCharIsNukta,
    &_msAPI_MLE_FontGujrCharIsBindu,
    NULL, //&_msAPI_MLE_FontGujrCharWithNukta,
    &_msAPI_MLE_FontGujrCharIsNoHalfCon,
    &_msAPI_MLE_FontGujrCharIsFollowingZWJ,
    NULL,
    NULL,
    &_msAPI_MLE_FontGujrGetCharType,
    &_msAPI_MLE_FontGujrGetCharSpecialType,
    &_msAPI_MLE_FontGujrGetCharOtherType,
    &_msAPI_MLE_FontGujrCharIsBlwf,
    NULL,
    NULL,
    &_msAPI_MLE_FontGujrStrWithAkhand,
    &_msAPI_MLE_FontGujrSetFeature,
    &_msAPI_MLE_FontGujrGetFeatureMap,
    &_msAPI_MLE_FontGujrCharIsSign,
    &_msAPI_MLE_FontGujrCharIsComposed,
    &_msAPI_MLE_FontGujrFeatureWithRphf,
    &_msAPI_MLE_FontGujrFeatureWithBlwf
};

static BOOLEAN _msAPI_MLE_FontGujrCharIsRA( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_GUJR_RANGE(u16Character) )
    {
        if ( IS_GUJR_RA_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
 
    return bResult;
}

static BOOLEAN _msAPI_MLE_FontGujrCharIsHalant( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( !bResult )
    {
        if ( IS_GUJR_RANGE(u16Character) )
        {
            if ( IS_GUJR_HALANT_CHAR(u16Character) )
            {
                bResult = TRUE;
            }
        }
    }
 
    return bResult;
}
     
static BOOLEAN _msAPI_MLE_FontGujrCharIsNukta( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( !bResult )
    {
        if ( IS_GUJR_RANGE(u16Character) )
        {
            if ( IS_GUJR_NUKTA_CHAR(u16Character) )
            {
                bResult = TRUE;
            }
        }
    }
 
    return bResult;
}
     
static BOOLEAN _msAPI_MLE_FontGujrCharIsBindu( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_GUJR_RANGE(u16Character) )
    {
        if ( IS_GUJR_BINDU_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
 
    return bResult;
}

#if 0
static BOOLEAN _msAPI_MLE_FontGujrCharWithNukta( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_GUJR_RANGE(u16Character) )
    {
        if ( IS_GUJR_WITH_NUKTA_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
 
    return bResult;
}
#endif

static BOOLEAN _msAPI_MLE_FontGujrCharIsNoHalfCon( U16 u16Character )
{
    BOOLEAN bResult = FALSE;
    
    if ( IS_GUJR_RANGE(u16Character) )
    {
        if ( IS_GUJR_NO_HALF_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
         
    return bResult;
}

static BOOLEAN _msAPI_MLE_FontGujrCharIsFollowingZWJ( U16 u16Character )
{
    BOOLEAN bResult = FALSE;
    
    if ( IS_GUJR_RANGE(u16Character) )
    {
        if ( IS_GUJR_HALANT_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
         
    return bResult;
}
  
static HindiCharacter_e _msAPI_MLE_FontGujrGetCharType( U16 u16Character )
{
    HindiCharacter_e eType = HINDI_INVALID;

    if ( IS_GUJR_RANGE(u16Character) )
    {
        eType = (HindiCharacter_e)((g_GujrCharTypeArray[u16Character - GUJR_MASK]) & 0x0F);
    }
     
    return eType;
}
 
static HindiSpecialCharacter_e _msAPI_MLE_FontGujrGetCharSpecialType( U16 u16Character )
{
    HindiSpecialCharacter_e eType = HINDI_SP_INVALID;

    if ( IS_GUJR_RANGE(u16Character) )
    {
        eType = (HindiSpecialCharacter_e)((g_GujrCharTypeArray[u16Character - GUJR_MASK]) & 0xF0);
    }
     
    return eType;
}

static HindiOtherCharacterType_e _msAPI_MLE_FontGujrGetCharOtherType( U16 u16Character )
{
    HindiOtherCharacterType_e eType = HINDI_OTYPE_INVALID;

    if ( IS_GUJR_RANGE(u16Character) )
    {
        if ( IS_GUJR_DEPVOW_LONG_DOWN_CHAR(u16Character) )
        {
            eType = HINDI_OTYPE_DEPVOW_LONG_DOWN_CHAR;
        }
        else if ( IS_GUJR_DEPVOW_SMALL_CHAR(u16Character) )
        {
            eType = HINDI_OTYPE_CON_SMALL_CHAR;
        }
    }
 
    return eType;
}

static BOOLEAN _msAPI_MLE_FontGujrCharIsBlwf( U16 u16FirstChar, U16 u16SecondChar )
{
    BOOLEAN bResult = FALSE;

    if ( IS_GUJR_RANGE(u16FirstChar) && IS_GUJR_RANGE(u16SecondChar) )
    {
        if ( IS_GUJR_HALANT_CHAR(u16FirstChar) && IS_GUJR_RA_CHAR(u16SecondChar) )
        {
            bResult = TRUE;
        }
    }
 
    return bResult;
}
 
#if 0
static const HindiMainTable_t* _msAPI_MLE_FontGujrGetCharRuleTable( U16 u16Character )
{
    const HindiMainTable_t *psMainTable = NULL;

    if ( IS_GUJR_RANGE(u16Character) )
    {
        psMainTable = &g_GujrRuleTbl[u16Character - GUJR_MASK - 1];
    }
     
    return psMainTable;
}

static BOOLEAN _msAPI_MLE_FontGujrReplaceOutputChar( U16 *pu16Cluster, U16 u16ClusterSize, U16 u16ClustIndex, U16 *pu16Index, U16 u16MatchedLen, U16 *pu16RemainSize, U16 *pu16OutGlyph, U16 *pu16OutGlyphLen, U16 u16OffsetInConcatenation, U16 *pu16OffsetInConcatenation, U16 *pu16OffsetInComposed, U16 *pu16ConcatenationComposedSize )
{
    BOOLEAN bReplaced = FALSE;

    pu16OffsetInConcatenation = pu16OffsetInConcatenation;
    
    if ( pu16Cluster == NULL || u16ClusterSize ==0 || pu16Index == NULL || (pu16ConcatenationComposedSize != NULL && pu16OffsetInComposed == NULL) )
    {
        return FALSE;
    }

    if ( IS_GUJR_RANGE(pu16Cluster[(*pu16Index)]) )
    {
        if( u16MatchedLen > 1 && (*pu16Index) < (u16ClusterSize - 1) 
            && IS_GUJR_PRIV_CONJUNCT_CHAR(pu16OutGlyph[(*pu16OutGlyphLen) - 1])
            && IS_GUJR_PRIV_CONJUNCT_CHAR(pu16Cluster[(*pu16Index)])
            && (_msAPI_MLE_FontGujrGetCharType(pu16Cluster[(*pu16Index) + 1]) == HINDI_CON || pu16Cluster[(*pu16Index) + 1] == FONT_CONTROL_ZWJ) )
        {
            U16 u16Conjunct = pu16OutGlyph[(*pu16OutGlyphLen) - 1];
             
            switch( u16Conjunct )
            {
                case DVNG_L_KSHA:
                    pu16OutGlyph[(*pu16OutGlyphLen) - 1] = DVNG_H_KHSA;
                    break;
                case DVNG_L_GYA:
                    pu16OutGlyph[(*pu16OutGlyphLen) - 1] = DVNG_H_GYAA;
                    break;
                case DVNG_L_TRA:
                    pu16OutGlyph[(*pu16OutGlyphLen) - 1] = DVNG_H_TRA;
                    break;
                case DVNG_L_SHRA:
                    pu16OutGlyph[(*pu16OutGlyphLen) - 1] = DVNG_H_SHRA;
                    break;
                case DVNG_L_TTTA:
                    pu16OutGlyph[(*pu16OutGlyphLen) - 1] = DVNG_H_TTA;
                    break;
                default:
                    break;
            }
     
            if ( *pu16ConcatenationComposedSize )
            {        
                pu16ConcatenationComposedSize[u16OffsetInConcatenation] = pu16ConcatenationComposedSize[u16OffsetInConcatenation] + 1;
                if ( ((*pu16Index) == u16ClustIndex) )
                {
                    *pu16OffsetInComposed = pu16ConcatenationComposedSize[u16OffsetInConcatenation] - 1;
                }
            }
                             
            (*pu16RemainSize) = (*pu16RemainSize) - 1;
            (*pu16Index) = (*pu16Index) + 1;
            bReplaced = TRUE;
        }
    }

    if ( !bReplaced && (*pu16Index) > 1 && (IS_GUJR_RANGE(pu16Cluster[(*pu16Index) - 1]) || IS_GUJR_PRIV_RANGE(pu16Cluster[(*pu16Index) - 1])) )
    {
        if ( (*pu16OutGlyphLen) > 1 && pu16OutGlyph[0] == DVNG_DV_I )
        {
            if ( _msAPI_MLE_FontGujrGetCharSpecialType(pu16OutGlyph[1]) == HINDI_SP_CENTER_T || ((*pu16OutGlyphLen) > 2 && pu16OutGlyph[2] == DVNG_SUP_RA))
            {
                pu16OutGlyph[0] = DVNG_L_DV_I_C;
                bReplaced = TRUE;
            }
        }
    }
     
    return bReplaced;
}
#endif

static BOOLEAN _msAPI_MLE_FontGujrStrWithAkhand( U16 *pu16Str, U32 u32StrLen, U16 u16Offset )
{
    BOOLEAN bResult = FALSE;

    if ( IS_GUJR_RANGE(pu16Str[u16Offset]) )
    {
        if ( (u32StrLen - u16Offset) > 2 )
        {
            if ( pu16Str[u16Offset] == GUJARATI_C_KA && pu16Str[u16Offset+1] == GUJARATI_S_HALANT && pu16Str[u16Offset+2] == GUJARATI_C_SSA )
            {
                bResult = TRUE;
            }
            else if ( pu16Str[u16Offset] == GUJARATI_C_JA && pu16Str[u16Offset+1] == GUJARATI_S_HALANT && pu16Str[u16Offset+2] == GUJARATI_C_NYA )
            {
                bResult = TRUE;
            }
        }
    }
     
    return bResult;
}

static U32 _msAPI_MLE_FontGujrSetFeature( U32 u32FeatureTags, HindiFeature_e eFeature )
{
    U16 i;
    for ( i = 0; i < _g_u16GujrFeatureCount; i++ )
    {
        if ( _g_sGujrFeatureMap[i].eTag == eFeature )
        {
            u32FeatureTags = u32FeatureTags | _g_sGujrFeatureMap[i].u32Mask;
            break;
        }
    }
    return u32FeatureTags;
}

static U16 _msAPI_MLE_FontGujrGetFeatureMap( const HindiFeatureRecord_t **ppasFeatureMap )
{
    *ppasFeatureMap = _g_sGujrFeatureMap;
    return (U16)_g_u16GujrFeatureCount;
}

static BOOLEAN _msAPI_MLE_FontGujrCharIsSign( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_GUJR_RANGE(u16Character) )
    {
        if ( _msAPI_MLE_FontGujrGetCharType(u16Character) == HINDI_SIGN )
        {
            bResult = TRUE;
        }
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_FontGujrCharIsComposed( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_GUJR_RANGE(u16Character) )
    {
        if ( _msAPI_MLE_FontGujrGetCharType(u16Character) == HINDI_SIGN && _msAPI_MLE_FontGujrGetCharSpecialType(u16Character) != HINDI_SP_RIGHT_JOINER )
        {
            bResult = TRUE;
        }
        else if ( IS_GUJR_DEPVOW_COMPOSING_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
 
    return bResult;
}

static BOOLEAN _msAPI_MLE_FontGujrFeatureWithRphf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType )
{
    BOOLEAN bResult = FALSE;
    
    if ( u32FeatureTags & _HindiRphfFeatureMask )
    {
        bResult = TRUE;
    }

    if ( peSpType )
    {
        *peSpType = HINDI_SP_CENTER_T_UP_POS;
    }
    
    return bResult;
}

static BOOLEAN _msAPI_MLE_FontGujrFeatureWithBlwf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType )
{
    BOOLEAN bResult = FALSE;
    
    if ( u32FeatureTags & _HindiBlwfFeatureMask )
    {
        bResult = TRUE;
    }

    if ( peSpType )
    {
        *peSpType = HINDI_SP_CENTER_T_DOWN_POS;
    }
    
    return bResult;
}

#endif //__GUJR_FONT__
#endif //__INDIC_FONT__
