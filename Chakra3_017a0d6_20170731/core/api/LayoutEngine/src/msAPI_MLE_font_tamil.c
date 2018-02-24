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

#ifdef __TAMIL_FONT__
#include "msAPI_MLE_font_tamil.h"

/*------------------------------------------------------------------------------------------
*
*                                                                                     MACRO DEFINE
*
-------------------------------------------------------------------------------------------*/
    
 const U8 g_TamilCharTypeArray[] =
 {
     HINDI_INVALID,
     HINDI_INVALID,
 
     /*  Various signs    */
     HINDI_SIGN | HINDI_SP_RIGHT_POS,           //TAMIL_S_ANUSVARA=0xb82
     HINDI_INDVOW,                              //TAMIL_S_VISARGA=0xb83

     /*  Independent Vowels    */
     HINDI_INVALID,
     HINDI_INDVOW | HINDI_SP_NO_T,               //TAMIL_IV_A=0xb85
     HINDI_INDVOW | HINDI_SP_NO_T,               //TAMIL_IV_AA=0xb86
     HINDI_INDVOW | HINDI_SP_NO_T,               //TAMIL_IV_I=0xb87
     HINDI_INDVOW | HINDI_SP_NO_T,               //TAMIL_IV_II=0xb88
     HINDI_INDVOW | HINDI_SP_NO_T,               //TAMIL_IV_U=0xb89
     HINDI_INDVOW | HINDI_SP_NO_T,               //TAMIL_IV_UU=0xb8a
     HINDI_INVALID,
     HINDI_INVALID,
     HINDI_INVALID,
     HINDI_INDVOW | HINDI_SP_RIGHT_T,            //TAMIL_IV_E=0xb8e
     HINDI_INDVOW | HINDI_SP_RIGHT_T,            //TAMIL_IV_EE=0xb8f
     HINDI_INDVOW | HINDI_SP_NO_T,               //TAMIL_IV_AI=0xb90
     HINDI_INVALID,
     HINDI_INDVOW | HINDI_SP_NO_T,               //TAMIL_IV_AI=0xb92
     HINDI_INDVOW | HINDI_SP_NO_T,               //TAMIL_IV_OO=0xb93
     HINDI_INDVOW | HINDI_SP_NO_T,               //TAMIL_IV_AU=0xb94 
 
     /*  CONSONANT'S TABLES    */
     HINDI_CON | HINDI_SP_NO_T,                  //TAMIL_C_KA=0xb95
     HINDI_INVALID,
     HINDI_INVALID,
     HINDI_INVALID,
     HINDI_CON | HINDI_SP_NO_T,                  //TAMIL_C_NGA=0xb99
     HINDI_CON | HINDI_SP_NO_T,                  //TAMIL_C_CHA=0xb9a
     HINDI_INVALID,
     HINDI_CON | HINDI_SP_NO_T,                  //TAMIL_C_JA=0xb9c
     HINDI_INVALID,
     HINDI_CON | HINDI_SP_RIGHT_T,               //TAMIL_C_NYA=0xb9e
     HINDI_CON | HINDI_SP_NO_T,                  //TAMIL_C_TTA=0xb9f
     HINDI_INVALID,
     HINDI_INVALID,
     HINDI_INVALID,
     HINDI_CON | HINDI_SP_RIGHT_T,               //TAMIL_C_NNA=0xba3
     HINDI_CON | HINDI_SP_RIGHT_T,               //TAMIL_C_TA=0xba4
     HINDI_INVALID,
     HINDI_INVALID,
     HINDI_INVALID,
     HINDI_CON | HINDI_SP_RIGHT_T,               //TAMIL_C_NA=0xba8
     HINDI_CON | HINDI_SP_RIGHT_T,               //TAMIL_C_NNNA=0xba9
     HINDI_CON | HINDI_SP_NO_T,                  //TAMIL_C_PA=0xbaa
     HINDI_INVALID,
     HINDI_INVALID,
     HINDI_INVALID,
     HINDI_CON | HINDI_SP_NO_T,                  //TAMIL_C_MA=0xbae
     HINDI_CON | HINDI_SP_NO_T,                  //TAMIL_C_YA=0xbaf
     HINDI_CON | HINDI_SP_RIGHT_T,               //TAMIL_C_RA=0xbb0
     HINDI_CON | HINDI_SP_NO_T,                  //TAMIL_C_RRA=0xbb1
     HINDI_CON | HINDI_SP_NO_T,                  //TAMIL_C_LA=0xbb2
     HINDI_CON | HINDI_SP_RIGHT_T,               //TAMIL_C_LLA=0xbb3
     HINDI_CON | HINDI_SP_NO_T,                  //TAMIL_C_LLLA=0xbb4
     HINDI_CON | HINDI_SP_NO_T,                  //TAMIL_C_VA=0xbb5
     HINDI_CON | HINDI_SP_NO_T,                  //TAMIL_C_SHA=0xbb6
     HINDI_CON | HINDI_SP_NO_T,                  //TAMIL_C_SSA=0xbb7
     HINDI_CON | HINDI_SP_NO_T,                  //TAMIL_C_SA=0xbb8
     HINDI_CON | HINDI_SP_NO_T,                  //TAMIL_C_HA=0xbb9

     /* Dependent Vowels  */
     HINDI_INVALID,
     HINDI_INVALID,
     HINDI_INVALID,
     HINDI_INVALID,
     HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,      //TAMIL_DV_AA=0xbbe
     HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,      //TAMIL_DV_I=0xbbf
     HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,   //TAMIL_DV_II=0xbc0
     HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,  //TAMIL_DV_U=0xbc1
     HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,  //TAMIL_DV_UU=0xbc2
     HINDI_INVALID,
     HINDI_INVALID,
     HINDI_INVALID,
     HINDI_DEPVOW | HINDI_SP_LEFT_JOINER,       //TAMIL_DV_E=0xbc6
     HINDI_DEPVOW | HINDI_SP_LEFT_JOINER,       //TAMIL_DV_EE=0xbc7
     HINDI_DEPVOW | HINDI_SP_LEFT_JOINER,       //TAMIL_DV_AI=0xbc8      
     HINDI_INVALID,
     /* Two-part dependent vowel signs*/
     HINDI_DEPVOW | HINDI_SP_TWOPART_JOINER,    //TAMIL_DV_O=0xbca
     HINDI_DEPVOW | HINDI_SP_TWOPART_JOINER,    //TAMIL_DV_OO=0xbcb
     HINDI_DEPVOW | HINDI_SP_TWOPART_JOINER,    //TAMIL_DV_AU=0xbcc
     HINDI_DEPVOW,                              //TAMIL_S_HALANT=0xbcd
     HINDI_INVALID,
     HINDI_INVALID,
     HINDI_INVALID,
     HINDI_INVALID,
     HINDI_INVALID,
     HINDI_INVALID,
     HINDI_INVALID,
     HINDI_INVALID,
     HINDI_INVALID,
     HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,      //TAMIL_AD_AU=0xbd7
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
     /* Digit TABLE */
     HINDI_NUM,                  //TAMIL_D_ZERO=0xbe6
     HINDI_NUM,                  //TAMIL_D_ONE=0xbe7
     HINDI_NUM,                  //TAMIL_D_TWO=0xbe8
     HINDI_NUM,                  //TAMIL_D_THREE=0xbe9
     HINDI_NUM,                  //TAMIL_D_FOUR=0xbea
     HINDI_NUM,                  //TAMIL_D_FIVE=0xbeb
     HINDI_NUM,                  //TAMIL_D_SIX=0xbec
     HINDI_NUM,                  //TAMIL_D_SEVEN=0xbed
     HINDI_NUM,                  //TAMIL_D_EIGHT=0xbee
     HINDI_NUM,                  //TAMIL_D_NINE=0xbef
 
     /* Tamil Numerics */            
     HINDI_NUM,                  //TAMIL_D_TEN=0xbf0
     HINDI_NUM,                  //TAMIL_D_HUNDRED=0xbf1
     HINDI_NUM,                  //TAMIL_D_THOUSAND=0xbf2
     HINDI_NUM,                  //TAMIL_OS_DAY=0xbf3
     HINDI_NUM,                  //TAMIL_OS_MONTH=0xbf4
     HINDI_NUM,                  //TAMIL_OS_YEAR=0xbf5
     HINDI_NUM,                  //TAMIL_OS_DEBIT=0xbf6
     HINDI_NUM,                  //TAMIL_OS_CREDIT=0xbf7
     HINDI_NUM,                  //TAMIL_OS_ABOVE=0xbf8
     HINDI_NUM,                  //TAMIL_OS_RUPEE=0xbf9
     HINDI_NUM,                  //TAMIL_OS_NUMERNAL=0xbfa
 };

const HindiFeatureRecord_t _g_sTamilFeatureMap[] = 
{
/*HINDI_FEATURE_LOCL*/  {HINDI_FEATURE_LOCL, _HindiLoclFeatureMask},
/*HINDI_FEATURE_NUKT*/  {HINDI_FEATURE_NUKT, _HindiNuktFeatureMask},
/*HINDI_FEATURE_AKHN*/  {HINDI_FEATURE_AKHN, _HindiAkhnFeatureMask},
/*HINDI_FEATURE_RPHF*/  {HINDI_FEATURE_RPHF, _HindiRphfFeatureMask},
/*HINDI_FEATURE_PREF*/  {HINDI_FEATURE_PREF, _HindiPrefFeatureMask},
/*HINDI_FEATURE_HALF*/  {HINDI_FEATURE_HALF, _HindiHalfFeatureMask},
/*HINDI_FEATURE_PRES*/  {HINDI_FEATURE_PRES, _HindiPresFeatureMask},
/*HINDI_FEATURE_ABVS*/  {HINDI_FEATURE_ABVS, _HindiAbvsFeatureMask},
/*HINDI_FEATURE_BLWS*/   {HINDI_FEATURE_BLWS, _HindiBlwsFeatureMask},
/*HINDI_FEATURE_PSTS*/  {HINDI_FEATURE_PSTS, _HindiPstsFeatureMask},
/*HINDI_FEATURE_HALN*/  {HINDI_FEATURE_HALN, _HindiHalnFeatureMask},
/*HINDI_FEATURE_CALT*/  {HINDI_FEATURE_CALT, _HindiCaltFeatureMask},
/*HINDI_FEATURE_ABVM*/ {HINDI_FEATURE_ABVM, _HindiAbvmFeatureMask},
/*HINDI_FEATURE_BLWM*/ {HINDI_FEATURE_BLWM, _HindiBlwmFeatureMask}
};
const U16 _g_u16TamilFeatureCount = (sizeof(_g_sTamilFeatureMap)/sizeof(HindiFeatureRecord_t));

static U16 _msAPI_MLE_FontTamilGetCluster( HindiScript_e eScript, const U16 *pu16Txt, U32 u32InLen, U16 *pu16Cluster, U16 u16BufferSize, U16 *pu16ConsumedCount, U16 *pu16SeqInCluster, BOOLEAN bIsDispStr, U32 *pu32FeatureTags );
static BOOLEAN _msAPI_MLE_FontTamilGetNextCodeXOffset( U16 *pu16CurrentRefChar, U16 *pu16CurrentCharRefWidth, U16 u16NextChar, U16 u16NextCharWidth, S16 *ps16XOffset, U16 u16BaseWidth, U16 u16PreChar, BOOLEAN bFirstCharInCluster );
static BOOLEAN _msAPI_MLE_FontTamilCharIsHalant( U16 u16Character );
static HindiCharacter_e _msAPI_MLE_FontTamilGetCharType( U16 u16Character );
static HindiSpecialCharacter_e _msAPI_MLE_FontTamilGetCharSpecialType( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontTamilStrWithAkhand( U16 *pu16Str, U32 u32StrLen, U16 u16Offset );
static U32 _msAPI_MLE_FontTamilSetFeature( U32 u32FeatureTags, HindiFeature_e eFeature );
static U16 _msAPI_MLE_FontTamilGetFeatureMap( const HindiFeatureRecord_t **ppasFeatureMap );
static U16 _msAPI_MLE_FontTamilGetTwoWordLeftChar( U16 u16Character );
static U16 _msAPI_MLE_FontTamilGetTwoWordRightChar( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontTamilFeatureWithRphf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType );
static BOOLEAN _msAPI_MLE_FontTamilFeatureWithBlwf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType );

__SLDPM_FREE__ const HindiTable_t g_tamilTable =
{
    HINDI_SCRIPT_TAML,
    TAMIL_S_ANUSVARA,
    TAMIL_OS_NUMERNAL,
    &_msAPI_MLE_FontTamilGetCluster,
    NULL, //fnRefineCluster
    &_msAPI_MLE_FontTamilGetNextCodeXOffset,
    NULL,//&_msAPI_MLE_FontTamilCharIsRA,
    &_msAPI_MLE_FontTamilCharIsHalant,
    NULL,//&_FontBengCharIsNukta,
    NULL,//&_FontTeluguCharIsBindu,
    NULL,//&_FontBengCharWithNukta,
    NULL,//&_FontBengCharIsNoHalfCon,
    NULL,//&_FontBengCharIsFollowingZWJ,
    &_msAPI_MLE_FontTamilGetTwoWordLeftChar,
    &_msAPI_MLE_FontTamilGetTwoWordRightChar,
    &_msAPI_MLE_FontTamilGetCharType,
    &_msAPI_MLE_FontTamilGetCharSpecialType,
    NULL,//&_FontBengGetCharOtherType,
    NULL,//&_FontBengCharIsBlwf,
    NULL,//&_FontBengCharIsPstf,
    NULL,//&_FontBengCharIsLigated,
    &_msAPI_MLE_FontTamilStrWithAkhand,
    &_msAPI_MLE_FontTamilSetFeature,
    &_msAPI_MLE_FontTamilGetFeatureMap,
    NULL,//&_FontBengCharIsSign,
    NULL,//&_FontBengCharIsComposed,
    &_msAPI_MLE_FontTamilFeatureWithRphf,
    &_msAPI_MLE_FontTamilFeatureWithBlwf
};

static U16 _msAPI_MLE_FontTamilGetCluster( HindiScript_e eScript, const U16 *pu16Txt, U32 u32InLen, U16 *pu16Cluster, U16 u16BufferSize, U16 *pu16ConsumedCount, U16 *pu16SeqInCluster, BOOLEAN bIsDispStr, U32 *pu32FeatureTags )
{
    eScript = eScript;
    bIsDispStr = bIsDispStr;
    pu32FeatureTags = pu32FeatureTags;
    
    *pu16ConsumedCount = 0;
    do 
    {
        if(u32InLen >=4)
        {
            U16 u16Character = 0;
            U16 u16Index = 0;

            u16Character = pu16Txt[u16Index];
            if( _msAPI_MLE_FontTamilGetCharType(u16Character) == HINDI_CON )
            {
                u16Index++;
                u16Character = pu16Txt[u16Index];
                if( _msAPI_MLE_FontTamilCharIsHalant(u16Character) )
                {
                    u16Index++;
                    u16Character = pu16Txt[u16Index];
                    if( _msAPI_MLE_FontTamilGetCharType(u16Character) == HINDI_CON )
                    {
                        HindiCharacter_e eType = HINDI_INVALID;
                        HindiSpecialCharacter_e eSpType = HINDI_SP_INVALID;
                        u16Index++;
                        u16Character = pu16Txt[u16Index];
                        eType = _msAPI_MLE_FontTamilGetCharType(u16Character);
                        eSpType = _msAPI_MLE_FontTamilGetCharSpecialType(u16Character);
                        if ( eType == HINDI_DEPVOW )
                        {
                            if ( eSpType == HINDI_SP_LEFT_JOINER || eSpType == HINDI_SP_TWOPART_JOINER )
                            {
                                U16 u16ClusterSize = 0;
                                _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
                                _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
                                _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
                                _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
                            }
                        }
                    }
                }
            }
        }
    } while (FALSE);
    
    return *pu16ConsumedCount;
}

static BOOLEAN _msAPI_MLE_FontTamilGetNextCodeXOffset( U16 *pu16CurrentRefChar, U16 *pu16CurrentCharRefWidth, U16 u16NextChar, U16 u16NextCharWidth, S16 *ps16XOffset, U16 u16BaseWidth, U16 u16PreChar, BOOLEAN bFirstCharInCluster )
{
    BOOLEAN bReturn = TRUE;

    u16BaseWidth = u16BaseWidth;
    u16PreChar = u16PreChar;
    bFirstCharInCluster = bFirstCharInCluster;
    
    if ( ps16XOffset == NULL || pu16CurrentRefChar == NULL || pu16CurrentCharRefWidth == NULL )
    {
        return FALSE;
    }

    if( ( IS_TAMIL_RANGE(*pu16CurrentRefChar) ) 
        && ( IS_TAMIL_RANGE(u16NextChar) ))
    {
        switch ( _msAPI_MLE_FontTamilGetCharType(u16NextChar) )
        {
        case HINDI_DEPVOW:
            if(TAMIL_DV_AA == u16NextChar)
            {
                *ps16XOffset = *ps16XOffset+*pu16CurrentCharRefWidth;
            }
            else
            {
                HindiSpecialCharacter_e eSpType = _msAPI_MLE_FontTamilGetCharSpecialType(u16NextChar);
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

static BOOLEAN _msAPI_MLE_FontTamilCharIsHalant( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_TAMIL_RANGE(u16Character) )
    {
        if ( IS_TAMIL_HALANT_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }

    return bResult;
}

static HindiCharacter_e _msAPI_MLE_FontTamilGetCharType( U16 u16Character )
{
    HindiCharacter_e eType = HINDI_INVALID;

    if ( IS_TAMIL_RANGE(u16Character) )
    {
        eType = (g_TamilCharTypeArray[u16Character - TAMIL_MASK]) & 0x0F;
    }

    return eType;
}

static HindiSpecialCharacter_e _msAPI_MLE_FontTamilGetCharSpecialType( U16 u16Character )
{
    HindiSpecialCharacter_e eType = HINDI_SP_INVALID;

    if ( IS_TAMIL_RANGE(u16Character) )
    {
        eType = (g_TamilCharTypeArray[u16Character - TAMIL_MASK]) & 0xF0;
    }

    return eType;
}

static BOOLEAN _msAPI_MLE_FontTamilStrWithAkhand( U16 *pu16Str, U32 u32StrLen, U16 u16Offset )
{
    BOOLEAN bResult = FALSE;

    if ( IS_TAMIL_RANGE(pu16Str[u16Offset]) )
    {
        if ( (u32StrLen - u16Offset) > 2 )
        {
            if ( pu16Str[u16Offset] == TAMIL_C_KA && pu16Str[u16Offset+1] == TAMIL_S_HALANT && pu16Str[u16Offset+2] == TAMIL_C_SSA )
            {
                bResult = TRUE;
            }
        }
    }
     
    return bResult;
}


static U32 _msAPI_MLE_FontTamilSetFeature( U32 u32FeatureTags, HindiFeature_e eFeature )
{
    U16 i;
    for ( i = 0; i < _g_u16TamilFeatureCount; i++ )
    {
        if ( _g_sTamilFeatureMap[i].eTag == eFeature )
        {
            u32FeatureTags = u32FeatureTags | _g_sTamilFeatureMap[i].u32Mask;
            break;
        }
    }
    return u32FeatureTags;
}

static U16 _msAPI_MLE_FontTamilGetFeatureMap( const HindiFeatureRecord_t **ppasFeatureMap )
{
    *ppasFeatureMap = _g_sTamilFeatureMap;
    return (U16)_g_u16TamilFeatureCount;
}


static U16 _msAPI_MLE_FontTamilGetTwoWordLeftChar( U16 u16Character )
{
    U16 u16ReturnChar = 0;

    if ( IS_TAMIL_RANGE(u16Character) && _msAPI_MLE_FontTamilGetCharSpecialType(u16Character) == HINDI_SP_TWOPART_JOINER )
    {
        if ( u16Character == TAMIL_DV_O || u16Character == TAMIL_DV_AU )
        {
            u16ReturnChar = TAMIL_DV_E;
        }
        else if ( u16Character == TAMIL_DV_OO )
        {
            u16ReturnChar = TAMIL_DV_EE;
        }
    }

    return u16ReturnChar;
}

static U16 _msAPI_MLE_FontTamilGetTwoWordRightChar( U16 u16Character )
{
    U16 u16ReturnChar = 0;

    if ( IS_TAMIL_RANGE(u16Character) && _msAPI_MLE_FontTamilGetCharSpecialType(u16Character) == HINDI_SP_TWOPART_JOINER )
    {
        if ( u16Character == TAMIL_DV_O || u16Character == TAMIL_DV_OO)
        {
            u16ReturnChar = TAMIL_DV_AA;
        }
        else if ( u16Character == TAMIL_DV_AU )
        {
            u16ReturnChar = TAMIL_AD_AU;
        }
    }

    return u16ReturnChar;
}

static BOOLEAN _msAPI_MLE_FontTamilFeatureWithRphf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType )
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

static BOOLEAN _msAPI_MLE_FontTamilFeatureWithBlwf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType )
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

#endif //__TAMIL_FONT__
#endif //__INDIC_FONT__

