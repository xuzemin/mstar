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

#ifdef __MLYM_FONT__
#include "msAPI_MLE_font_malayalam.h"

/*------------------------------------------------------------------------------------------
*
*                                                                                     MACRO DEFINE
*
-------------------------------------------------------------------------------------------*/
    
 const U8 g_MalayalamCharTypeArray[] =
 {
     HINDI_INVALID,
     HINDI_INVALID,

     /*  Various signs    */
     HINDI_SIGN | HINDI_SP_RIGHT_POS,     //MALAYALAM_S_ANUSVARA=0xD02,
     HINDI_SIGN | HINDI_SP_RIGHT_POS,     //MALAYALAM_S_VISARGA=0xD03,

     /*  Independent Vowels    */
     HINDI_INVALID,
     HINDI_INDVOW | HINDI_SP_NO_T,               //MALAYALAM_IV_A=0xD05
     HINDI_INDVOW | HINDI_SP_NO_T,               //MALAYALAM_IV_AA=0xD06
     HINDI_INDVOW | HINDI_SP_NO_T,               //MALAYALAM_IV_I=0xD07
     HINDI_INDVOW | HINDI_SP_NO_T,               //MALAYALAM_IV_II=0xD08
     HINDI_INDVOW | HINDI_SP_NO_T,               //MALAYALAM_IV_U=0xD09
     HINDI_INDVOW | HINDI_SP_NO_T,               //MALAYALAM_IV_UU=0xD0a
     HINDI_INDVOW | HINDI_SP_NO_T,               //MALAYALAM_IV_VR=0xD0b
     HINDI_INDVOW | HINDI_SP_NO_T,               //MALAYALAM_IV_VL=0xD0c
     HINDI_INVALID,
     HINDI_INDVOW | HINDI_SP_NO_T,               //MALAYALAM_IV_E=0xD0e
     HINDI_INDVOW | HINDI_SP_NO_T,               //MALAYALAM_IV_EE=0xD0f
     HINDI_INDVOW | HINDI_SP_NO_T,               //MALAYALAM_IV_AI=0xD10
     HINDI_INVALID,
     HINDI_INDVOW | HINDI_SP_NO_T,               //MALAYALAM_IV_O=0xD12
     HINDI_INDVOW | HINDI_SP_NO_T,               //MALAYALAM_IV_OO=0xD13
     HINDI_INDVOW | HINDI_SP_NO_T,               //MALAYALAM_IV_AU=0xD14
     
     /*  CONSONANT'S TABLES    */    
     HINDI_CON | HINDI_SP_NO_T,                 //MALAYALAM_C_KA=0xD15
     HINDI_CON | HINDI_SP_NO_T,                 //MALAYALAM_C_KHA=0xD16
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_GA=0xD17
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_GHA=0xD18
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_NGA=0xD19
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_CA=0xD1a
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_CHA=0xD1b
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_JA=0xD1c
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_JHA=0xD1d
     HINDI_CON | HINDI_SP_NO_T,              //MALAYALAM_C_NYA=0xD1e
     HINDI_CON | HINDI_SP_NO_T,            //MALAYALAM_C_TTA=0xD1f
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_TTHA=0xD20
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_DDA=0xD21
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_DDHA=0xD22
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_NNA=0xD23
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_TA=0xD24
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_THA=0xD25
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_DA=0xD26
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_DHA=0xD27
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_NA=0xD28
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_NNNA=0xD29
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_PA=0xD2a
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_PHA=0xD2b
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_BA=0xD2c
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_BHA=0xD2d
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_MA=0xD2e
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_YA=0xD2f
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_RA=0xD30
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_RRA=0xD31
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_LA=0xD32
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_LLA=0xD33
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_LLLA=0xD34
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_VA=0xD35
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_SHA=0xD36
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_SSA=0xD37
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_SA=0xD38
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_HA=0xD39
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_TTTA=0xD3a
     HINDI_INVALID,
     HINDI_INVALID,
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_S_AVAGRAHA=0xD3d

     /* Dependent Vowels  */
     HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,      //MALAYALAM_DV_AA=0xD3e
     HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,      //MALAYALAM_DV_I=0xD3f
     HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,   //MALAYALAM_DV_II=0xD40
     HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,  //MALAYALAM_DV_U=0xD41
     HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,  //MALAYALAM_DV_UU=0xD42
     HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,  //MALAYALAM_DV_VR=0xD43
     HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,  //MALAYALAM_DV_VRR=0xD44
     HINDI_INVALID,
     HINDI_DEPVOW | HINDI_SP_LEFT_JOINER,       //MALAYALAM_DV_E=0xD46
     HINDI_DEPVOW | HINDI_SP_LEFT_JOINER,       //MALAYALAM_DV_EE=0xD47
     HINDI_DEPVOW | HINDI_SP_LEFT_JOINER,       //MALAYALAM_DV_AI=0xD48      
     HINDI_INVALID,
     
     /* Two-part dependent vowel signs*/
     HINDI_DEPVOW | HINDI_SP_TWOPART_JOINER,    //MALAYALAM_DV_O=0xD4a
     HINDI_DEPVOW | HINDI_SP_TWOPART_JOINER,    //MALAYALAM_DV_OO=0xD4b
     HINDI_DEPVOW | HINDI_SP_TWOPART_JOINER,    //MALAYALAM_DV_AU=0xD4c
     
     /* SIGNS */
     HINDI_DEPVOW,                                                  //MALAYALAM_S_HALANT=0xD4d
     HINDI_DEPVOW,                                                  //MALAYALAM_S_DR=0xD4e
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
     HINDI_INVALID,
     HINDI_INVALID,
     
     /*Additional vowels for Sanskrit*/
     HINDI_DEPVOW | HINDI_SP_NO_T,                  //MALAYALAM_C_VRR=0xD60
     HINDI_DEPVOW | HINDI_SP_NO_T,                  //MALAYALAM_C_VLL=0xD61

     /* Dependent Vowels  */
     HINDI_DEPVOW | HINDI_SP_CENTER_T_DOWN_POS,      //MALAYALAM_DV_VL=0xD62
     HINDI_DEPVOW | HINDI_SP_CENTER_T_DOWN_POS,      //MALAYALAM_DV_VLL=0xD63
     
     HINDI_INVALID,
     HINDI_INVALID,

     /* Digit TABLE */
     HINDI_NUM,                  //MALAYALAM_D_ZERO=0xD66
     HINDI_NUM,                  //MALAYALAM_D_ONE=0xD67
     HINDI_NUM,                  //MALAYALAM_D_TWO=0xD68
     HINDI_NUM,                  //MALAYALAM_D_THREE=0xD69
     HINDI_NUM,                  //MALAYALAM_D_FOUR=0xD6a
     HINDI_NUM,                  //MALAYALAM_D_FIVE=0xD6b
     HINDI_NUM,                  //MALAYALAM_D_SIX=0xD6c
     HINDI_NUM,                  //MALAYALAM_D_SEVEN=0xD6d
     HINDI_NUM,                  //MALAYALAM_D_EIGHT=0xD6e
     HINDI_NUM,                  //MALAYALAM_D_NINE=0xD6f
     
     /* Malayalam-specific additions */        
     HINDI_NUM,                  //MALAYALAM_N_TEN=0xD70
     HINDI_NUM,                  //MALAYALAM_N_HUNDRED=0xD71
     HINDI_NUM,                  //MALAYALAM_N_THOUSAND=0xD72
     HINDI_NUM,                  //MALAYALAM_F_QUARTER=0xD73
     HINDI_NUM,                  //MALAYALAM_F_HALF=0xD74
     HINDI_NUM,                  //MALAYALAM_F_THREE_QUARTERS=0xD75
     HINDI_INVALID,
     HINDI_INVALID,
     HINDI_INVALID,

     HINDI_NUM,                  //MALAYALAM_S_DM=0xD79

     /* Chillu letters */
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_CHILLU_NN=0xD7a
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_CHILLU_N=0xD7b
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_CHILLU_RR=0xD7c
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_CHILLU_L=0xD7d
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_CHILLU_LL=0xD7e
     HINDI_CON | HINDI_SP_NO_T,               //MALAYALAM_C_CHILLU_K=0xD7f
 };
            
const HindiFeatureRecord_t _g_sMalayalamFeatureMap[] =
{
/*HINDI_FEATURE_LOCL*/  {HINDI_FEATURE_LOCL, _HindiLoclFeatureMask},
/*HINDI_FEATURE_NUKT*/  {HINDI_FEATURE_NUKT, _HindiNuktFeatureMask},
/*HINDI_FEATURE_AKHN*/  {HINDI_FEATURE_AKHN, _HindiAkhnFeatureMask},
/*HINDI_FEATURE_RPHF*/  {HINDI_FEATURE_RPHF, _HindiRphfFeatureMask},
/*HINDI_FEATURE_PREF*/  {HINDI_FEATURE_PREF, _HindiPrefFeatureMask},
/*HINDI_FEATURE_BLWF*/  {HINDI_FEATURE_BLWF, _HindiBlwfFeatureMask},
/*HINDI_FEATURE_HALF*/  {HINDI_FEATURE_HALF, _HindiHalfFeatureMask},
/*HINDI_FEATURE_PSTF*/  {HINDI_FEATURE_PSTF, _HindiPstfFeatureMask},
/*HINDI_FEATURE_CJCT*/  {HINDI_FEATURE_CJCT, _HindiCjctFeatureMask},
/*HINDI_FEATURE_PRES*/  {HINDI_FEATURE_PRES, _HindiPresFeatureMask},
/*HINDI_FEATURE_ABVS*/  {HINDI_FEATURE_ABVS, _HindiAbvsFeatureMask},
/*HINDI_FEATURE_BLWS*/   {HINDI_FEATURE_BLWS, _HindiBlwsFeatureMask},
/*HINDI_FEATURE_PSTS*/  {HINDI_FEATURE_PSTS, _HindiPstsFeatureMask},
/*HINDI_FEATURE_HALN*/  {HINDI_FEATURE_HALN, _HindiHalnFeatureMask},
/*HINDI_FEATURE_CALT*/  {HINDI_FEATURE_CALT, _HindiCaltFeatureMask},
/*HINDI_FEATURE_ABVM*/ {HINDI_FEATURE_ABVM, _HindiAbvmFeatureMask},
/*HINDI_FEATURE_BLWM*/ {HINDI_FEATURE_BLWM, _HindiBlwmFeatureMask}
};
const U16 _g_u16MalayalamFeatureCount = (sizeof(_g_sMalayalamFeatureMap)/sizeof(HindiFeatureRecord_t));

static BOOLEAN _msAPI_MLE_FontMalayalamGetNextCodeXOffset( U16 *pu16CurrentRefChar, U16 *pu16CurrentCharRefWidth, U16 u16NextChar, U16 u16NextCharWidth, S16 *ps16XOffset, U16 u16BaseWidth, U16 u16PreChar, BOOLEAN bFirstCharInCluster );
//static BOOLEAN _msAPI_MLE_FontMalayalamCharIsRA( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontMalayalamCharIsHalant( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontMalayalamCharWithNukta( U16 u16Character );
static HindiCharacter_e _msAPI_MLE_FontMalayalamGetCharType( U16 u16Character );
static HindiSpecialCharacter_e _msAPI_MLE_FontMalayalamGetCharSpecialType( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontMalayalamCharIsBlwf( U16 u16FirstChar, U16 u16SecondChar );
static BOOLEAN _msAPI_MLE_FontMalayalamCharIsPstf( U16 u16FirstChar, U16 u16SecondChar );
static BOOLEAN _msAPI_MLE_FontMalayalamStrWithAkhand( U16 *pu16Str, U32 u32StrLen, U16 u16Offset );
static U32 _msAPI_MLE_FontMalayalamSetFeature( U32 u32FeatureTags, HindiFeature_e eFeature );
static U16 _msAPI_MLE_FontMalayalamGetFeatureMap( const HindiFeatureRecord_t **ppasFeatureMap );
static U16 _msAPI_MLE_FontMalayalamGetTwoWordLeftChar( U16 u16Character );
static U16 _msAPI_MLE_FontMalayalamGetTwoWordRightChar( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontMalayalamFeatureWithRphf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType );
static BOOLEAN _msAPI_MLE_FontMalayalamFeatureWithBlwf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType );

__SLDPM_FREE__ const HindiTable_t g_mlymTable =
{
    HINDI_SCRIPT_MLYM,
    MALAYALAM_S_ANUSVARA,
    MALAYALAM_C_CHILLU_K,
    NULL,//&_msAPI_MLE_FontMalayalamGetCluster,
    NULL, //fnRefineCluster
    &_msAPI_MLE_FontMalayalamGetNextCodeXOffset,
    NULL,//&_msAPI_MLE_FontMalayalamCharIsRA,
    &_msAPI_MLE_FontMalayalamCharIsHalant,
    NULL,//&_FontBengCharIsNukta,
    NULL,//&_FontTeluguCharIsBindu,
    &_msAPI_MLE_FontMalayalamCharWithNukta,
    NULL,//&_FontBengCharIsNoHalfCon,
    NULL,//&_FontBengCharIsFollowingZWJ,
    &_msAPI_MLE_FontMalayalamGetTwoWordLeftChar,
    &_msAPI_MLE_FontMalayalamGetTwoWordRightChar,
    &_msAPI_MLE_FontMalayalamGetCharType,
    &_msAPI_MLE_FontMalayalamGetCharSpecialType,
    NULL,//&_FontBengGetCharOtherType,
    &_msAPI_MLE_FontMalayalamCharIsBlwf,
    &_msAPI_MLE_FontMalayalamCharIsPstf,
    NULL,//&_FontBengCharIsLigated,
    &_msAPI_MLE_FontMalayalamStrWithAkhand,
    &_msAPI_MLE_FontMalayalamSetFeature,
    &_msAPI_MLE_FontMalayalamGetFeatureMap,
    NULL,//&_FontBengCharIsSign,
    NULL,//&_FontBengCharIsComposed,
    &_msAPI_MLE_FontMalayalamFeatureWithRphf,
    &_msAPI_MLE_FontMalayalamFeatureWithBlwf
};

static BOOLEAN _msAPI_MLE_FontMalayalamGetNextCodeXOffset( U16 *pu16CurrentRefChar, U16 *pu16CurrentCharRefWidth, U16 u16NextChar, U16 u16NextCharWidth, S16 *ps16XOffset, U16 u16BaseWidth, U16 u16PreChar, BOOLEAN bFirstCharInCluster )
{
    BOOLEAN bReturn = TRUE;

    u16BaseWidth = u16BaseWidth;
    u16PreChar = u16PreChar;
    bFirstCharInCluster = bFirstCharInCluster;
    
    if ( ps16XOffset == NULL || pu16CurrentRefChar == NULL || pu16CurrentCharRefWidth == NULL )
    {
        return FALSE;
    }

    if( ( IS_MLYM_RANGE(*pu16CurrentRefChar) ) 
        && ( IS_MLYM_RANGE(u16NextChar)))
    {
        switch ( _msAPI_MLE_FontMalayalamGetCharType(u16NextChar) )
        {
        case HINDI_DEPVOW:
            if(MALAYALAM_DV_AA == u16NextChar)
            {
                *ps16XOffset = *ps16XOffset+*pu16CurrentCharRefWidth;
            }
            else
            {
                HindiSpecialCharacter_e eSpType = _msAPI_MLE_FontMalayalamGetCharSpecialType(u16NextChar);
                if ( eSpType == HINDI_SP_RIGHT_JOINER)
                {
                    *ps16XOffset = *ps16XOffset+*pu16CurrentCharRefWidth;
                }
                else
                {
                    *ps16XOffset = *ps16XOffset + (*pu16CurrentCharRefWidth - u16NextCharWidth)/2;
                }
            }
            return TRUE;
        case HINDI_HALANT:
            *ps16XOffset = *ps16XOffset + (*pu16CurrentCharRefWidth - u16NextCharWidth)/2;
            return TRUE;

        default:
            bReturn = FALSE; // not handled 
            break;
        }
    }
    else
    {
        bReturn = FALSE; // not handled
    }

    return bReturn;
}

#if 0
static BOOLEAN _msAPI_MLE_FontMalayalamCharIsRA( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_MLYM_RANGE(u16Character) )
    {
        if ( IS_MLYM_RA_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
    
    return bResult;
}
#endif

static BOOLEAN _msAPI_MLE_FontMalayalamCharIsHalant( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_MLYM_RANGE(u16Character) )
    {
        if ( IS_MLYM_HALANT_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }

    return bResult;
}

static HindiCharacter_e _msAPI_MLE_FontMalayalamGetCharType( U16 u16Character )
{
    HindiCharacter_e eType = HINDI_INVALID;

    if ( IS_MLYM_RANGE(u16Character) )
    {
        eType = (g_MalayalamCharTypeArray[u16Character - MLYM_MASK]) & 0x0F;
    }

    return eType;
}

static HindiSpecialCharacter_e _msAPI_MLE_FontMalayalamGetCharSpecialType( U16 u16Character )
{
    HindiSpecialCharacter_e eType = HINDI_SP_INVALID;

    if ( IS_MLYM_RANGE(u16Character) )
    {
        eType = (g_MalayalamCharTypeArray[u16Character - MLYM_MASK]) & 0xF0;
    }

    return eType;
}

static BOOLEAN _msAPI_MLE_FontMalayalamCharIsBlwf( U16 u16FirstChar, U16 u16SecondChar )
{
    BOOLEAN bResult = FALSE;

    if ( IS_MLYM_RANGE(u16FirstChar) && IS_MLYM_RANGE(u16SecondChar) )
    {
        if ( IS_MLYM_HALANT_CHAR(u16FirstChar) )
        {
            if ( IS_MLYM_BELOW_BASE_FORM(u16SecondChar) )
            {
                bResult = TRUE;
            }
        }
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_FontMalayalamCharIsPstf( U16 u16FirstChar, U16 u16SecondChar )
{
    BOOLEAN bResult = FALSE;

    if ( IS_MLYM_RANGE(u16FirstChar) && IS_MLYM_RANGE(u16SecondChar) )
    {
        if ( IS_MLYM_HALANT_CHAR(u16FirstChar) )
        {
            switch( u16SecondChar )
            {
            case MALAYALAM_C_YA:
            case MALAYALAM_C_RA:
            case MALAYALAM_C_VA:
                bResult = TRUE;
                break;
            default:
                break;
            }
        }
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_FontMalayalamStrWithAkhand( U16 *pu16Str, U32 u32StrLen, U16 u16Offset )
{
    BOOLEAN bResult = FALSE;

    if ( IS_MLYM_RANGE(pu16Str[u16Offset]) )
    {
        if ( (u32StrLen - u16Offset) > 2 )
        {
            //This is from Microsoft documents
            /*
            if ( pu16Str[u16Offset] == MALAYALAM_C_KA && pu16Str[u16Offset+1] == MALAYALAM_S_HALANT && pu16Str[u16Offset+2] == MALAYALAM_C_KA )
            {
                bResult = TRUE;
            }
            else if ( pu16Str[u16Offset] == MALAYALAM_C_DA && pu16Str[u16Offset+1] == MALAYALAM_S_HALANT && pu16Str[u16Offset+2] == MALAYALAM_C_DHA )
            {
                bResult = TRUE;
            }
            */
            //bResult = TRUE;
            
            //This is from customer's TTF file, so much different, right?
            if ( pu16Str[u16Offset] == MALAYALAM_C_KA && pu16Str[u16Offset+1] == MALAYALAM_S_HALANT && pu16Str[u16Offset+2] == MALAYALAM_C_LA )
            {
                bResult = TRUE;
            }
            else if ( pu16Str[u16Offset] == MALAYALAM_C_KA && pu16Str[u16Offset+1] == MALAYALAM_S_HALANT && pu16Str[u16Offset+2] == MALAYALAM_C_SSA )
            {
                bResult = TRUE;
            }
            else if ( pu16Str[u16Offset] == MALAYALAM_C_JA && pu16Str[u16Offset+1] == MALAYALAM_S_HALANT && pu16Str[u16Offset+2] == MALAYALAM_C_NYA )
            {
                bResult = TRUE;
            }
            else if ( pu16Str[u16Offset] == MALAYALAM_C_RRA && pu16Str[u16Offset+1] == MALAYALAM_S_HALANT && pu16Str[u16Offset+2] == MALAYALAM_C_RRA )
            {
                bResult = TRUE;
            }
        }
    }
     
    return bResult;
}

static U32 _msAPI_MLE_FontMalayalamSetFeature( U32 u32FeatureTags, HindiFeature_e eFeature )
{
    U16 i;
    for ( i = 0; i < _g_u16MalayalamFeatureCount; i++ )
    {
        if ( _g_sMalayalamFeatureMap[i].eTag == eFeature )
        {
            u32FeatureTags = u32FeatureTags | _g_sMalayalamFeatureMap[i].u32Mask;
            break;
        }
    }
    return u32FeatureTags;
}

static U16 _msAPI_MLE_FontMalayalamGetFeatureMap( const HindiFeatureRecord_t **ppasFeatureMap )
{
    *ppasFeatureMap = _g_sMalayalamFeatureMap;
    return (U16)_g_u16MalayalamFeatureCount;
}

static BOOLEAN _msAPI_MLE_FontMalayalamCharWithNukta( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_MLYM_RANGE(u16Character) )
    {
        if ( IS_MLYM_WITH_NUKTA_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
    
    return bResult;
}

static U16 _msAPI_MLE_FontMalayalamGetTwoWordLeftChar( U16 u16Character )
{
    U16 u16ReturnChar = 0;

    if ( IS_MLYM_RANGE(u16Character) && _msAPI_MLE_FontMalayalamGetCharSpecialType(u16Character) == HINDI_SP_TWOPART_JOINER )
    {
        if ( u16Character == MALAYALAM_DV_O || u16Character == MALAYALAM_DV_AU )
        {
            u16ReturnChar = MALAYALAM_DV_E;
        }
        else if ( u16Character == MALAYALAM_DV_OO )
        {
            u16ReturnChar = MALAYALAM_DV_EE;
        }
    }

    return u16ReturnChar;
}

static U16 _msAPI_MLE_FontMalayalamGetTwoWordRightChar( U16 u16Character )
{
    U16 u16ReturnChar = 0;

    if ( IS_MLYM_RANGE(u16Character) && _msAPI_MLE_FontMalayalamGetCharSpecialType(u16Character) == HINDI_SP_TWOPART_JOINER )
    {
        if ( u16Character == MALAYALAM_DV_O || u16Character == MALAYALAM_DV_OO)
        {
            u16ReturnChar = MALAYALAM_DV_AA;
        }
        else if ( u16Character == MALAYALAM_DV_AU )
        {
            u16ReturnChar = MALAYALAM_AD_AU;
        }
    }

    return u16ReturnChar;
}

static BOOLEAN _msAPI_MLE_FontMalayalamFeatureWithRphf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType )
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

static BOOLEAN _msAPI_MLE_FontMalayalamFeatureWithBlwf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType )
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

#endif //__MLYM_FONT__
#endif //__INDIC_FONT__
