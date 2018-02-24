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

#ifdef __DVNG_FONT__
#include "msAPI_MLE_font_devanagari.h"

const U8 g_DvngCharTypeArray[] =
{
    HINDI_INVALID,

    /* Various signs*/
    HINDI_SIGN   | HINDI_SP_CENTER_T_UP_POS,//S_CHANDRA_BINDU=0x0901,
    HINDI_SIGN   | HINDI_SP_CENTER_T_UP_POS,//S_BINDU=0x902,
    HINDI_SIGN   | HINDI_SP_RIGHT_POS,      //S_VISARGA=0x903,

    /* Independent vowels */
    HINDI_INDVOW | HINDI_SP_RIGHT_T,        //NIV_A=0x904,
    HINDI_INDVOW | HINDI_SP_RIGHT_T,        //IV_A=0x905,
    HINDI_INDVOW | HINDI_SP_DOUBLE_T,       //IV_AA=0x906,
    HINDI_INDVOW | HINDI_SP_RIGHT_T,        //IV_I=0x907,
    HINDI_INDVOW | HINDI_SP_RIGHT_T,        //IV_II=0x908,          
    HINDI_INDVOW | HINDI_SP_RIGHT_T,        //IV_U=0x909,
    HINDI_INDVOW | HINDI_SP_CENTER_T,       //IV_UU=0x90a,
    HINDI_INDVOW | HINDI_SP_CENTER_T,       //IV_R=0x90b,
    HINDI_INDVOW | HINDI_SP_RIGHT_T,        //NIV_L=0x90c,
    HINDI_INDVOW | HINDI_SP_RIGHT_T,        //NIV_CE=0x90d,
    HINDI_INDVOW | HINDI_SP_RIGHT_T,        //NIV_SE=0x90e,
    HINDI_INDVOW | HINDI_SP_RIGHT_T,        //IV_E=0x90f,
    HINDI_INDVOW | HINDI_SP_RIGHT_T,        //IV_AI=0x910,
    HINDI_INDVOW | HINDI_SP_DOUBLE_T,       //NIV_CO=0x911,
    HINDI_INDVOW | HINDI_SP_DOUBLE_T,       //NIV_SO=0x912,
    HINDI_INDVOW | HINDI_SP_DOUBLE_T,       //IV_O=0x913,
    HINDI_INDVOW | HINDI_SP_DOUBLE_T,       //IV_AU=0x914,

    /* Consonants */
    HINDI_CON    | HINDI_SP_CENTER_T,       //C_KA=0x915,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_KHA=0x916,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_GA=0x917,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_GHA=0x918,
    HINDI_CON    | HINDI_SP_CENTER_T,       //C_NGA=0x919,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_CHA=0x91a,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_CHHA=0x91b,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_JA=0x91c,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_JHA=0x91d,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_NYA=0x91e,
    HINDI_CON    | HINDI_SP_CENTER_T,       //C_TTA=0x91f,
    HINDI_CON    | HINDI_SP_CENTER_T,       //C_TTHA=0x920,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_DDA=0x921,
    HINDI_CON    | HINDI_SP_CENTER_T,       //C_DDHA=0x922,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_NNA=0x923,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_TA=0x924,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_THA=0x925,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_DA=0x926,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_DHA=0x927,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_NA=0x928,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_NNNA=0x929,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_PA=0x92a,
    HINDI_CON    | HINDI_SP_CENTER_T,       //C_PHA=0x92b,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_BA=0x92c,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_BHA=0x92d,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_MA=0x92e,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_YA=0x92f,
    HINDI_CON    | HINDI_SP_CENTER_T,       //C_RA=0x930,
    HINDI_CON    | HINDI_SP_CENTER_T,       //C_RRA=0x931,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_LA=0x932,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_LLA=0x933,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_LLLA=0x934,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_VA=0x935,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_SHA=0x936,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_SSA=0x937,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_SA=0x938,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //C_HA=0x939,
    
    HINDI_INVALID,                          //N_BLANK1=0x93a,
    HINDI_INVALID,                          //N_BLANK2=0x93b,

    /* Various signs */
    HINDI_SIGN   | HINDI_SP_LEFT_T_DOWN_POS,//S_NUKTA=0x93c,
    HINDI_SIGN   | HINDI_SP_RIGHT_POS,      //NS_AVAGRAHA=0x93d,

    /* Dependent vowel signs */
    HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,   //DV_AA=0x93e,
    HINDI_DEPVOW | HINDI_SP_LEFT_JOINER,    //DV_I=0x93f,
    HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,   //DV_II=0x940,
    HINDI_DEPVOW | HINDI_SP_CENTER_T_DOWN_POS,//DV_U=0x941,
    HINDI_DEPVOW | HINDI_SP_CENTER_T_DOWN_POS,//DV_UU=0x942,
    HINDI_DEPVOW | HINDI_SP_CENTER_T_DOWN_POS,//DV_R=0x943,
    HINDI_DEPVOW | HINDI_SP_CENTER_T_DOWN_POS,//NDV_RR=0x944,
    HINDI_DEPVOW | HINDI_SP_CENTER_T_UP_POS,//DV_CE=0x945,
    HINDI_DEPVOW | HINDI_SP_LEFT_T_UP_POS,  //NDV_E=0x946,
    HINDI_DEPVOW | HINDI_SP_LEFT_T_UP_POS,      //DV_E=0x947,
    HINDI_DEPVOW | HINDI_SP_LEFT_T_UP_POS,      //DV_AI=0x948,
    HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,   //NDV_CO=0x949,
    HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,   //NDV_O=0x94a,
    HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,   //DV_O=0x94b,
    HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,   //DV_AU=0x94c,

    /* Various signs */
    HINDI_SIGN   | HINDI_SP_RIGHT_T_DOWN_POS,//S_HALANT=0x94d,
    HINDI_INVALID,                          //NS_RESERVED1=0x94e,
    HINDI_INVALID,                          //NS_RESERVED2=0x94f,
    HINDI_INDVOW | HINDI_SP_RIGHT_T,        //S_OM=0x950,
    HINDI_SIGN   | HINDI_SP_CENTER_T_UP_POS,//NS_UDATTA=0x951,
    HINDI_SIGN   | HINDI_SP_CENTER_T_DOWN_POS,//NS_ANUDATTA=0x952,
    HINDI_SIGN   | HINDI_SP_LEFT_T_UP_POS,  //NS_GACCENT=0x953,
    HINDI_SIGN   | HINDI_SP_LEFT_T_UP_POS,  //NS_AACCENT=0x954,
    
    HINDI_INVALID,                          //N_BLANK5=0x955,
    HINDI_INVALID,                          //N_BLANK6=0x956,
    HINDI_INVALID,                          //N_BLANK7=0x957,

    /* Additional consonants */
    HINDI_CON    | HINDI_SP_CENTER_T,       //AC_QA=0x958,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //AC_KHHA=0x959,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //AC_GHHA=0x95a,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //AC_ZA=0x95b,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //AC_DDDHA=0x95c,
    HINDI_CON    | HINDI_SP_CENTER_T,       //AC_RHA=0x95d,
    HINDI_CON    | HINDI_SP_CENTER_T,       //AC_FA=0x95e,
    HINDI_CON    | HINDI_SP_RIGHT_T,        //AC_YYA=0x95f,

    /* Generic additions */
    HINDI_INDVOW | HINDI_SP_CENTER_T,       //NG_RR=0x960,
    HINDI_INDVOW | HINDI_SP_RIGHT_T,        //NG_LL=0x961,
    HINDI_SIGN   | HINDI_SP_CENTER_T_DOWN_POS,//NG_L=0x962,
    HINDI_SIGN   | HINDI_SP_CENTER_T_DOWN_POS,//NG_VLL=0x963,                   
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW,  //NG_D=0x964,
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW,  //NG_DD=0x965,

    /* Digits */
    HINDI_NUM,                              //D_ZERO=0x966,
    HINDI_NUM,                              //D_ONE=0x967,
    HINDI_NUM,                              //D_TWO=0x968,
    HINDI_NUM,                              //D_THREE=0x969,
    HINDI_NUM,                              //D_FOUR=0x96a,
    HINDI_NUM,                              //D_FIVE=0x96b,
    HINDI_NUM,                              //D_SIX=0x96c,
    HINDI_NUM,                              //D_SEVEN=0x96d,
    HINDI_NUM,                              //D_EIGHT=0x96e,
    HINDI_NUM,                              //D_NINE=0x96f, 

    /* Devanagari-specific additions */
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW,  //S_ABBR=0x970
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW   //S_RUPEE=0x971
};                  

const HindiFeatureRecord_t _g_sDvngFeatureMap[] = 
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
const U16 _g_u16DvngFeatureCount = (sizeof(_g_sDvngFeatureMap)/sizeof(HindiFeatureRecord_t));

static BOOLEAN _msAPI_MLE_FontDvngCharIsRA( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontDvngCharIsHalant( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontDvngCharIsNukta( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontDvngCharIsBindu( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontDvngCharWithNukta( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontDvngCharIsNoHalfCon( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontDvngCharIsFollowingZWJ( U16 u16Character );
static HindiCharacter_e _msAPI_MLE_FontDvngGetCharType( U16 u16Character );
static HindiSpecialCharacter_e _msAPI_MLE_FontDvngGetCharSpecialType( U16 u16Character );
static HindiOtherCharacterType_e _msAPI_MLE_FontDvngGetCharOtherType( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontDvngCharIsBlwf( U16 u16FirstChar, U16 u16SecondChar );
static U32 _msAPI_MLE_FontDvngSetFeature( U32 u32FeatureTags, HindiFeature_e eFeature );
static U16 _msAPI_MLE_FontDvngGetFeatureMap( const HindiFeatureRecord_t **ppasFeatureMap );
static BOOLEAN _msAPI_MLE_FontDvngStrWithAkhand( U16 *pu16Str, U32 u32StrLen, U16 u16Offset );

static BOOLEAN _msAPI_MLE_FontDvngCharIsSign( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontDvngCharIsComposed( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontDvngFeatureWithRphf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType );
static BOOLEAN _msAPI_MLE_FontDvngFeatureWithBlwf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType );

__SLDPM_FREE__ const HindiTable_t g_dvngTable =
{
    HINDI_SCRIPT_DEVA,
    DVNG_S_CHANDRA_BINDU,
    DVNG_S_RUPEE,
    NULL, //fnGetCluster
    NULL, //fnRefineCluster
    NULL, //fnGetNextCodeXOffset
    &_msAPI_MLE_FontDvngCharIsRA,
    &_msAPI_MLE_FontDvngCharIsHalant,
    &_msAPI_MLE_FontDvngCharIsNukta,
    &_msAPI_MLE_FontDvngCharIsBindu,
    &_msAPI_MLE_FontDvngCharWithNukta,
    &_msAPI_MLE_FontDvngCharIsNoHalfCon,
    &_msAPI_MLE_FontDvngCharIsFollowingZWJ,
    NULL,
    NULL,
    &_msAPI_MLE_FontDvngGetCharType,
    &_msAPI_MLE_FontDvngGetCharSpecialType,
    &_msAPI_MLE_FontDvngGetCharOtherType,
    &_msAPI_MLE_FontDvngCharIsBlwf,
    NULL,
    NULL,
    &_msAPI_MLE_FontDvngStrWithAkhand,
    &_msAPI_MLE_FontDvngSetFeature,
    &_msAPI_MLE_FontDvngGetFeatureMap,
    &_msAPI_MLE_FontDvngCharIsSign,
    &_msAPI_MLE_FontDvngCharIsComposed,
    &_msAPI_MLE_FontDvngFeatureWithRphf,
    &_msAPI_MLE_FontDvngFeatureWithBlwf
};
 
static BOOLEAN _msAPI_MLE_FontDvngCharIsRA( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_DVNG_RANGE(u16Character) )
    {
        if ( IS_DVNG_RA_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
 
    return bResult;
}

static BOOLEAN _msAPI_MLE_FontDvngCharIsHalant( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( !bResult )
    {
        if ( IS_DVNG_RANGE(u16Character) )
        {
            if ( IS_DVNG_HALANT_CHAR(u16Character) )
            {
                bResult = TRUE;
            }
        }
    }
 
    return bResult;
}
     
static BOOLEAN _msAPI_MLE_FontDvngCharIsNukta( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( !bResult )
    {
        if ( IS_DVNG_RANGE(u16Character) )
        {
            if ( IS_DVNG_NUKTA_CHAR(u16Character) )
            {
                bResult = TRUE;
            }
        }
    }
 
    return bResult;
}
     
static BOOLEAN _msAPI_MLE_FontDvngCharIsBindu( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_DVNG_RANGE(u16Character) )
    {
        if ( IS_DVNG_BINDU_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
 
    return bResult;
}

static BOOLEAN _msAPI_MLE_FontDvngCharWithNukta( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_DVNG_RANGE(u16Character) )
    {
        if ( IS_DVNG_WITH_NUKTA_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
 
    return bResult;
}

static BOOLEAN _msAPI_MLE_FontDvngCharIsNoHalfCon( U16 u16Character )
{
    BOOLEAN bResult = FALSE;
    
    if ( IS_DVNG_RANGE(u16Character) )
    {
        if ( IS_DVNG_NO_HALF_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
         
    return bResult;
}

static BOOLEAN _msAPI_MLE_FontDvngCharIsFollowingZWJ( U16 u16Character )
{
    BOOLEAN bResult = FALSE;
    //HindiCharacter_e eType = HINDI_INVALID;
    
    if ( IS_DVNG_RANGE(u16Character) )
    {
        //eType = _msAPI_MLE_FontDvngGetCharType(u16Character);
        //if ( IS_DVNG_HALANT_CHAR(u16Character) || ( eType == HINDI_CON ) || ( eType == HINDI_DEPVOW ) )
        if ( IS_DVNG_HALANT_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
         
    return bResult;
}
  
static HindiCharacter_e _msAPI_MLE_FontDvngGetCharType( U16 u16Character )
{
    HindiCharacter_e eType = HINDI_INVALID;

    if ( IS_DVNG_RANGE(u16Character) )
    {
        eType = (HindiCharacter_e)((g_DvngCharTypeArray[u16Character - DVNG_MASK]) & 0x0F);
    }
     
    return eType;
}
 
static HindiSpecialCharacter_e _msAPI_MLE_FontDvngGetCharSpecialType( U16 u16Character )
{
    HindiSpecialCharacter_e eType = HINDI_SP_INVALID;
 
    if ( IS_DVNG_RANGE(u16Character) )
    {
        eType = (HindiSpecialCharacter_e)((g_DvngCharTypeArray[u16Character - DVNG_MASK]) & 0xF0);
    }
     
    return eType;
}

static HindiOtherCharacterType_e _msAPI_MLE_FontDvngGetCharOtherType( U16 u16Character )
{
    HindiOtherCharacterType_e eType = HINDI_OTYPE_INVALID;

    if ( IS_DVNG_RANGE(u16Character) )
    {
        if ( IS_DVNG_DEPVOW_LONG_DOWN_CHAR(u16Character) )
        {
            eType = HINDI_OTYPE_DEPVOW_LONG_DOWN_CHAR;
        }
        else if ( IS_DVNG_DEPVOW_SMALL_CHAR(u16Character) )
        {
            eType = HINDI_OTYPE_CON_SMALL_CHAR;
        }
    }
 
    return eType;
}

static BOOLEAN _msAPI_MLE_FontDvngCharIsBlwf( U16 u16FirstChar, U16 u16SecondChar )
{
    BOOLEAN bResult = FALSE;

    if ( IS_DVNG_RANGE(u16FirstChar) && IS_DVNG_RANGE(u16SecondChar) )
    {
        if ( IS_DVNG_HALANT_CHAR(u16FirstChar) && IS_DVNG_RA_CHAR(u16SecondChar) )
        {
            bResult = TRUE;
        }
    }
 
    return bResult;
}

static BOOLEAN _msAPI_MLE_FontDvngStrWithAkhand( U16 *pu16Str, U32 u32StrLen, U16 u16Offset )
{
    BOOLEAN bResult = FALSE;

    if ( IS_DVNG_RANGE(pu16Str[u16Offset]) )
    {
        if ( (u32StrLen - u16Offset) > 2 )
        {
            if ( pu16Str[u16Offset] == DVNG_C_KA && pu16Str[u16Offset+1] == DVNG_S_HALANT && pu16Str[u16Offset+2] == DVNG_C_SSA )
            {
                bResult = TRUE;
            }
            else if ( pu16Str[u16Offset] == DVNG_C_JA && pu16Str[u16Offset+1] == DVNG_S_HALANT && pu16Str[u16Offset+2] == DVNG_C_NYA )
            {
                bResult = TRUE;
            }
        }
    }
     
    return bResult;
}

static U32 _msAPI_MLE_FontDvngSetFeature( U32 u32FeatureTags, HindiFeature_e eFeature )
{
    U16 i;
    for ( i = 0; i < _g_u16DvngFeatureCount; i++ )
    {
        if ( _g_sDvngFeatureMap[i].eTag == eFeature )
        {
            u32FeatureTags = u32FeatureTags | _g_sDvngFeatureMap[i].u32Mask;
            break;
        }
    }
    return u32FeatureTags;
}

static U16 _msAPI_MLE_FontDvngGetFeatureMap( const HindiFeatureRecord_t **ppasFeatureMap )
{
    *ppasFeatureMap = _g_sDvngFeatureMap;
    return (U16)_g_u16DvngFeatureCount;
}

static BOOLEAN _msAPI_MLE_FontDvngCharIsSign( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_DVNG_RANGE(u16Character) )
    {
        if ( _msAPI_MLE_FontDvngGetCharType(u16Character) == HINDI_SIGN )
        {
            bResult = TRUE;
        }
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_FontDvngCharIsComposed( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_DVNG_RANGE(u16Character) )
    {
        if ( _msAPI_MLE_FontDvngGetCharType(u16Character) == HINDI_SIGN && _msAPI_MLE_FontDvngGetCharSpecialType(u16Character) != HINDI_SP_RIGHT_JOINER )
        {
            bResult = TRUE;
        }
        else if ( IS_DVNG_DEPVOW_COMPOSING_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
 
    return bResult;
}

static BOOLEAN _msAPI_MLE_FontDvngFeatureWithRphf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType )
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

static BOOLEAN _msAPI_MLE_FontDvngFeatureWithBlwf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType )
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

#endif //__DVNG_FONT__
#endif //__INDIC_FONT__
