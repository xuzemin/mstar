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

#ifdef __PUNJ_FONT__
#include "msAPI_MLE_font_punjabi.h"

const U8 g_PunjabiCharTypeArray[] =
{
    HINDI_INVALID,

    /* Various signs*/
    HINDI_SIGN   | HINDI_SP_CENTER_T_UP_POS,//PUNJ_S_ADAK_BINDI=0x0A01,
    HINDI_SIGN   | HINDI_SP_CENTER_T_UP_POS,//PUNJ_S_BINDI=0xA02,
    HINDI_SIGN   | HINDI_SP_RIGHT_POS,      //PUNJ_S_VISARGA=0xA03,

    /* Independent vowels */
    HINDI_INVALID,
    HINDI_INDVOW | HINDI_SP_RIGHT_T,        //PUNJ_IV_A=0xA05,
    HINDI_INDVOW | HINDI_SP_RIGHT_T,       //PUNJ_IV_AA=0xA06,
    HINDI_INDVOW | HINDI_SP_RIGHT_T,        //PUNJ_IV_I=0xA07,
    HINDI_INDVOW | HINDI_SP_RIGHT_T,        //PUNJ_IV_II=0xA08,          
    HINDI_INDVOW | HINDI_SP_RIGHT_T,        //PUNJ_IV_U=0xA09,
    HINDI_INDVOW | HINDI_SP_NO_T,       //PUNJ_IV_UU=0xA0a,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INDVOW | HINDI_SP_RIGHT_T,        //PUNJ_IV_EE=0xA0f,
    HINDI_INDVOW | HINDI_SP_RIGHT_T,        //PUNJ_IV_AI=0xA10,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INDVOW | HINDI_SP_NO_T,       //PUNJ_IV_OO=0xA13,
    HINDI_INDVOW | HINDI_SP_RIGHT_T,       //PUNJ_IV_AU=0xA14,

    /* Consonants */
    HINDI_CON    | HINDI_SP_NO_T,       //PUNJ_C_KA=0xA15,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_C_KHA=0xA16,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_C_GA=0xA17,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_C_GHA=0xA18,
    HINDI_CON    | HINDI_SP_CENTER_T,       //PUNJ_C_NGA=0xA19,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_C_CA=0xA1a,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_C_CHA=0xA1b,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_C_JA=0xA1c,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_C_JHA=0xA1d,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_C_NYA=0xA1e,
    HINDI_CON    | HINDI_SP_CENTER_T,       //PUNJ_C_TTA=0xA1f,
    HINDI_CON    | HINDI_SP_CENTER_T,       //PUNJ_C_TTHA=0xA20,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_C_DDA=0xA21,
    HINDI_CON    | HINDI_SP_CENTER_T,       //PUNJ_C_DDHA=0xA22,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_C_NNA=0xA23,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_C_TA=0xA24,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_C_THA=0xA25,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_C_DA=0xA26,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_C_DHA=0xA27,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_C_NA=0xA28,
    HINDI_INVALID,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_C_PA=0xA2a,
    HINDI_CON    | HINDI_SP_CENTER_T,       //PUNJ_C_PHA=0xA2b,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_C_BA=0xA2c,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_C_BHA=0xA2d,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_C_MA=0xA2e,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_C_YA=0xA2f,
    HINDI_CON    | HINDI_SP_CENTER_T,       //PUNJ_C_RA=0xA30,
    HINDI_INVALID,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_C_LA=0xA32,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_C_LLA=0xA33,
    HINDI_INVALID,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_C_VA=0xA35,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_C_SHA=0xA36,
    HINDI_INVALID,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_C_SA=0xA38,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_C_HA=0xA39,
    
    HINDI_INVALID,
    HINDI_INVALID,

    /* Various signs */
    HINDI_SIGN   | HINDI_SP_LEFT_T_DOWN_POS,//PUNJ_S_NUKTA=0xA3c,
    HINDI_INVALID,

    /* Dependent vowel signs */
    HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,   //PUNJ_DV_AA=0xA3e,
    HINDI_DEPVOW | HINDI_SP_LEFT_JOINER,    //PUNJ_DV_I=0xA3f,
    HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,   //PUNJ_DV_II=0xA40,
    HINDI_DEPVOW | HINDI_SP_CENTER_T_DOWN_POS,//PUNJ_DV_U=0xA41,
    HINDI_DEPVOW | HINDI_SP_CENTER_T_DOWN_POS,//PUNJ_DV_UU=0xA42,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_DEPVOW | HINDI_SP_LEFT_T_UP_POS,      //PUNJ_DV_EE=0xA47,
    HINDI_DEPVOW | HINDI_SP_LEFT_T_UP_POS,      //PUNJ_DV_AI=0xA48,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_DEPVOW | HINDI_SP_LEFT_T_UP_POS,   //PUNJ_DV_OO=0xA4b,
    HINDI_DEPVOW | HINDI_SP_CENTER_T_UP_POS,   //PUNJ_DV_AU=0xA4c,

    /* Various signs */
    HINDI_SIGN   | HINDI_SP_RIGHT_T_DOWN_POS,//PUNJ_S_HALANT=0xA4d,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_SIGN   | HINDI_SP_CENTER_T_DOWN_POS,//PUNJ_NS_UDAAT=0xA51,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    
    /* Additional consonants */
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_AC_KHHA=0xA59,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_AC_GHHA=0xA5a,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_AC_ZA=0xA5b,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //PUNJ_AC_RRA=0xA5c,
    HINDI_INVALID,
    HINDI_CON    | HINDI_SP_CENTER_T,       //PUNJ_AC_FA=0xA5e,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    
    /* Digits */
    HINDI_NUM,                              //PUNJ_D_ZERO=0xA66,
    HINDI_NUM,                              //PUNJ_D_ONE=0xA67,
    HINDI_NUM,                              //PUNJ_D_TWO=0xA68,
    HINDI_NUM,                              //PUNJ_D_THREE=0xA69,
    HINDI_NUM,                              //PUNJ_D_FOUR=0xA6a,
    HINDI_NUM,                              //PUNJ_D_FIVE=0xA6b,
    HINDI_NUM,                              //PUNJ_D_SIX=0xA6c,
    HINDI_NUM,                              //PUNJ_D_SEVEN=0xA6d,
    HINDI_NUM,                              //PUNJ_D_EIGHT=0xA6e,
    HINDI_NUM,                              //PUNJ_D_NINE=0xA6f, 
    
    /* Gurmukhi-specific additions */
    HINDI_SIGN | HINDI_SP_CENTER_T_UP_POS,  //PUNJ_S_TIPPI=0xA70
    HINDI_SIGN | HINDI_SP_CENTER_T_UP_POS,   //PUNJ_S_ADDAK=0xA71
    HINDI_INDVOW | HINDI_SP_NO_T,                   //PUNJ_S_IRI=0xA72
    HINDI_INDVOW | HINDI_SP_NO_T,                   //PUNJ_S_URA=0xA73
    HINDI_INDVOW | HINDI_SP_NO_T,                   //PUNJ_S_ONKAR=0xA74
    HINDI_SIGN | HINDI_SP_CENTER_T_DOWN_POS //PUNJ_S_YAKASH=0xA75
};                  

const HindiFeatureRecord_t _g_sPunjabiFeatureMap[] = 
{
/*HINDI_FEATURE_LOCL*/  {HINDI_FEATURE_LOCL, _HindiLoclFeatureMask},
/*HINDI_FEATURE_NUKT*/  {HINDI_FEATURE_NUKT, _HindiNuktFeatureMask},
/*HINDI_FEATURE_AKHN*/  {HINDI_FEATURE_AKHN, _HindiAkhnFeatureMask},
/*HINDI_FEATURE_RPHF*/  {HINDI_FEATURE_RPHF, _HindiRphfFeatureMask},
/*HINDI_FEATURE_BLWF*/  {HINDI_FEATURE_BLWF, _HindiBlwfFeatureMask},
/*HINDI_FEATURE_HALF*/  {HINDI_FEATURE_HALF, _HindiHalfFeatureMask},
/*HINDI_FEATURE_PSTF*/  {HINDI_FEATURE_PSTF, _HindiPstfFeatureMask},
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
const U16 _g_u16PunjabiFeatureCount = (sizeof(_g_sPunjabiFeatureMap)/sizeof(HindiFeatureRecord_t));

static BOOLEAN _msAPI_MLE_FontPunjabiCharIsRA( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontPunjabiCharIsHalant( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontPunjabiCharIsNukta( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontPunjabiCharIsBindu( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontPunjabiCharWithNukta( U16 u16Character );
//static BOOLEAN _msAPI_MLE_FontPunjabiCharIsNoHalfCon( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontPunjabiCharIsFollowingZWJ( U16 u16Character );
static HindiCharacter_e _msAPI_MLE_FontPunjabiGetCharType( U16 u16Character );
static HindiSpecialCharacter_e _msAPI_MLE_FontPunjabiGetCharSpecialType( U16 u16Character );
static HindiOtherCharacterType_e _msAPI_MLE_FontPunjabiGetCharOtherType( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontPunjabiCharIsBlwf( U16 u16FirstChar, U16 u16SecondChar );
static U32 _msAPI_MLE_FontPunjabiSetFeature( U32 u32FeatureTags, HindiFeature_e eFeature );
static U16 _msAPI_MLE_FontPunjabiGetFeatureMap( const HindiFeatureRecord_t **ppasFeatureMap );
static BOOLEAN _msAPI_MLE_FontPunjabiCharIsPstf( U16 u16FirstChar, U16 u16SecondChar );
//static BOOLEAN _msAPI_MLE_FontPunjabiStrWithAkhand( U16 *pu16Str, U32 u32StrLen, U16 u16Offset );

static BOOLEAN _msAPI_MLE_FontPunjabiCharIsSign( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontPunjabiCharIsComposed( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontPunjabiFeatureWithRphf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType );
static BOOLEAN _msAPI_MLE_FontPunjabiFeatureWithBlwf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType );

__SLDPM_FREE__ const HindiTable_t g_punjTable =
{
    HINDI_SCRIPT_PUNJ,
    PUNJ_S_ADAK_BINDI,
    PUNJ_S_YAKASH,
    NULL, //fnGetCluster
    NULL, //fnRefineCluster
    NULL, //fnGetNextCodeXOffset
    &_msAPI_MLE_FontPunjabiCharIsRA,
    &_msAPI_MLE_FontPunjabiCharIsHalant,
    &_msAPI_MLE_FontPunjabiCharIsNukta,
    &_msAPI_MLE_FontPunjabiCharIsBindu,
    &_msAPI_MLE_FontPunjabiCharWithNukta,
    NULL, //&_msAPI_MLE_FontPunjabiCharIsNoHalfCon,
    &_msAPI_MLE_FontPunjabiCharIsFollowingZWJ,
    NULL,
    NULL,
    &_msAPI_MLE_FontPunjabiGetCharType,
    &_msAPI_MLE_FontPunjabiGetCharSpecialType,
    &_msAPI_MLE_FontPunjabiGetCharOtherType,
    &_msAPI_MLE_FontPunjabiCharIsBlwf,
    &_msAPI_MLE_FontPunjabiCharIsPstf,
    NULL,
    NULL, //&_msAPI_MLE_FontPunjabiStrWithAkhand,
    &_msAPI_MLE_FontPunjabiSetFeature,
    &_msAPI_MLE_FontPunjabiGetFeatureMap,
    &_msAPI_MLE_FontPunjabiCharIsSign,
    &_msAPI_MLE_FontPunjabiCharIsComposed,
    &_msAPI_MLE_FontPunjabiFeatureWithRphf,
    &_msAPI_MLE_FontPunjabiFeatureWithBlwf
};
 
static BOOLEAN _msAPI_MLE_FontPunjabiCharIsRA( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_PUNJ_RANGE(u16Character) )
    {
        if ( IS_PUNJ_RA_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
 
    return bResult;
}

static BOOLEAN _msAPI_MLE_FontPunjabiCharIsHalant( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( !bResult )
    {
        if ( IS_PUNJ_RANGE(u16Character) )
        {
            if ( IS_PUNJ_HALANT_CHAR(u16Character) )
            {
                bResult = TRUE;
            }
        }
    }
 
    return bResult;
}
     
static BOOLEAN _msAPI_MLE_FontPunjabiCharIsNukta( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( !bResult )
    {
        if ( IS_PUNJ_RANGE(u16Character) )
        {
            if ( IS_PUNJ_NUKTA_CHAR(u16Character) )
            {
                bResult = TRUE;
            }
        }
    }
 
    return bResult;
}
     
static BOOLEAN _msAPI_MLE_FontPunjabiCharIsBindu( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_PUNJ_RANGE(u16Character) )
    {
        if ( IS_PUNJ_BINDU_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
 
    return bResult;
}

static BOOLEAN _msAPI_MLE_FontPunjabiCharWithNukta( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_PUNJ_RANGE(u16Character) )
    {
        if ( IS_PUNJ_WITH_NUKTA_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
 
    return bResult;
}

/*
static BOOLEAN _msAPI_MLE_FontPunjabiCharIsNoHalfCon( U16 u16Character )
{
    BOOLEAN bResult = FALSE;
    
    if ( IS_PUNJ_RANGE(u16Character) )
    {
        if ( IS_PUNJ_NO_HALF_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
         
    return bResult;
}
*/

static BOOLEAN _msAPI_MLE_FontPunjabiCharIsFollowingZWJ( U16 u16Character )
{
    BOOLEAN bResult = FALSE;
    
    if ( IS_PUNJ_RANGE(u16Character) )
    {
        if ( IS_PUNJ_HALANT_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
         
    return bResult;
}
  
static HindiCharacter_e _msAPI_MLE_FontPunjabiGetCharType( U16 u16Character )
{
    HindiCharacter_e eType = HINDI_INVALID;

    if ( IS_PUNJ_RANGE(u16Character) )
    {
        eType = (HindiCharacter_e)((g_PunjabiCharTypeArray[u16Character - PUNJ_MASK]) & 0x0F);
    }
     
    return eType;
}
 
static HindiSpecialCharacter_e _msAPI_MLE_FontPunjabiGetCharSpecialType( U16 u16Character )
{
    HindiSpecialCharacter_e eType = HINDI_SP_INVALID;

    if ( IS_PUNJ_RANGE(u16Character) )
    {
        eType = (HindiSpecialCharacter_e)((g_PunjabiCharTypeArray[u16Character - PUNJ_MASK]) & 0xF0);
    }
     
    return eType;
}

static HindiOtherCharacterType_e _msAPI_MLE_FontPunjabiGetCharOtherType( U16 u16Character )
{
    HindiOtherCharacterType_e eType = HINDI_OTYPE_INVALID;

    if ( IS_PUNJ_RANGE(u16Character) )
    {
        if ( IS_PUNJ_DEPVOW_LONG_DOWN_CHAR(u16Character) )
        {
            eType = HINDI_OTYPE_DEPVOW_LONG_DOWN_CHAR;
        }
        else if ( IS_PUNJ_DEPVOW_SMALL_CHAR(u16Character) )
        {
            eType = HINDI_OTYPE_CON_SMALL_CHAR;
        }
    }
 
    return eType;
}

static BOOLEAN _msAPI_MLE_FontPunjabiCharIsBlwf( U16 u16FirstChar, U16 u16SecondChar )
{
    BOOLEAN bResult = FALSE;

    if ( IS_PUNJ_RANGE(u16FirstChar) && IS_PUNJ_RANGE(u16SecondChar) )
    {
        if ( IS_PUNJ_HALANT_CHAR(u16FirstChar) )
        {
            switch(u16SecondChar)
            {
            case PUNJ_C_RA:
            case PUNJ_C_HA:
            case PUNJ_C_VA:         
                bResult = TRUE;
                break;
            default:
                break;
            }
        }
    }
 
    return bResult;
}

static BOOLEAN _msAPI_MLE_FontPunjabiCharIsPstf( U16 u16FirstChar, U16 u16SecondChar )
{
    BOOLEAN bResult = FALSE;

    if ( IS_PUNJ_RANGE(u16FirstChar) && IS_PUNJ_RANGE(u16SecondChar) )
    {
        if ( IS_PUNJ_HALANT_CHAR(u16FirstChar) && IS_PUNJ_PSTF_CHAR(u16SecondChar ) )
        {
            bResult = TRUE;
        }
    }

    return bResult;
}

/*
static BOOLEAN _msAPI_MLE_FontPunjabiStrWithAkhand( U16 *pu16Str, U32 u32StrLen, U16 u16Offset )
{
    BOOLEAN bResult = FALSE;

    if ( IS_PUNJ_RANGE(pu16Str[u16Offset]) )
    {
        if ( (u32StrLen - u16Offset) > 2 )
        {
            if ( pu16Str[u16Offset] == PUNJ_C_KA && pu16Str[u16Offset+1] == PUNJ_S_HALANT && pu16Str[u16Offset+2] == PUNJ_C_SSA )
            {
                bResult = TRUE;
            }
            else if ( pu16Str[u16Offset] == PUNJ_C_JA && pu16Str[u16Offset+1] == PUNJ_S_HALANT && pu16Str[u16Offset+2] == PUNJ_C_NYA )
            {
                bResult = TRUE;
            }
        }
    }
     
    return bResult;
}
*/

static U32 _msAPI_MLE_FontPunjabiSetFeature( U32 u32FeatureTags, HindiFeature_e eFeature )
{
    U16 i;
    for ( i = 0; i < _g_u16PunjabiFeatureCount; i++ )
    {
        if ( _g_sPunjabiFeatureMap[i].eTag == eFeature )
        {
            u32FeatureTags = u32FeatureTags | _g_sPunjabiFeatureMap[i].u32Mask;
            break;
        }
    }
    return u32FeatureTags;
}

static U16 _msAPI_MLE_FontPunjabiGetFeatureMap( const HindiFeatureRecord_t **ppasFeatureMap )
{
    *ppasFeatureMap = _g_sPunjabiFeatureMap;
    return (U16)_g_u16PunjabiFeatureCount;
}

static BOOLEAN _msAPI_MLE_FontPunjabiCharIsSign( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_PUNJ_RANGE(u16Character) )
    {
        if ( _msAPI_MLE_FontPunjabiGetCharType(u16Character) == HINDI_SIGN )
        {
            bResult = TRUE;
        }
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_FontPunjabiCharIsComposed( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_PUNJ_RANGE(u16Character) )
    {
        if ( _msAPI_MLE_FontPunjabiGetCharType(u16Character) == HINDI_SIGN && _msAPI_MLE_FontPunjabiGetCharSpecialType(u16Character) != HINDI_SP_RIGHT_JOINER )
        {
            bResult = TRUE;
        }
        else if ( IS_PUNJ_DEPVOW_COMPOSING_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
 
    return bResult;
}

static BOOLEAN _msAPI_MLE_FontPunjabiFeatureWithRphf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType )
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

static BOOLEAN _msAPI_MLE_FontPunjabiFeatureWithBlwf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType )
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

#endif //__PUNJ_FONT__
#endif //__INDIC_FONT__
