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

#ifdef __BENGALI_FONT__
#include "msAPI_MLE_font_bengali.h"

/*------------------------------------------------------------------------------------------
*
*                                                                                     MACRO DEFINE
*
-------------------------------------------------------------------------------------------*/

const U8 g_BengaliCharTypeArray[] =
{
    HINDI_INVALID,

    /* Various signs */
    HINDI_SIGN   | HINDI_SP_CENTER_T_UP_POS, //BENGALI_S_CHANDRA_BINDU=0x981,
    HINDI_SIGN   | HINDI_SP_RIGHT_POS,    //BENGALI_S_ANUSVARA=0x982,
    HINDI_SIGN   | HINDI_SP_RIGHT_POS,    //BENGALI_S_VISARGA=0x983,
    
    HINDI_INVALID,
    
    /* Independent vowels */
    HINDI_INDVOW | HINDI_SP_RIGHT_T,       //BENGALI_IV_A=0x985,
    HINDI_INDVOW | HINDI_SP_DOUBLE_T,      //BENGALI_IV_AA=0x986,
    HINDI_INDVOW | HINDI_SP_NO_T,          //BENGALI_IV_I=0x987,
    HINDI_INDVOW | HINDI_SP_NO_T,          //BENGALI_IV_II=0x988,
    HINDI_INDVOW | HINDI_SP_NO_T,          //BENGALI_IV_U=0x989,
    HINDI_INDVOW | HINDI_SP_NO_T,          //BENGALI_IV_UU=0x98a,
    HINDI_INDVOW | HINDI_SP_DOUBLE_T,      //BENGALI_IV_VR=0x98b,
    HINDI_INDVOW | HINDI_SP_NO_T,          //BENGALI_IV_VL=0x98c,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INDVOW | HINDI_SP_NO_T,          //BENGALI_IV_E=0x98f,
    HINDI_INDVOW | HINDI_SP_NO_T,          //BENGALI_IV_AI=0x990,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INDVOW | HINDI_SP_NO_T,          //BENGALI_IV_O=0x993,
    HINDI_INDVOW | HINDI_SP_NO_T,          //BENGALI_IV_AU=0x994,

    /* Consonants */
    HINDI_CON    | HINDI_SP_CENTER_T,      //BENGALI_C_KA=0x995,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //BENGALI_C_KHA=0x996,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //BENGALI_C_GA=0x997,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //BENGALI_C_GHA=0x998,
    HINDI_CON    | HINDI_SP_CENTER_T,      //BENGALI_C_NGA=0x999,
    HINDI_CON    | HINDI_SP_CENTER_T,      //BENGALI_C_CA=0x99a,
    HINDI_CON    | HINDI_SP_CENTER_T,      //BENGALI_C_CHA=0x99b,
    HINDI_CON    | HINDI_SP_CENTER_T,      //BENGALI_C_JA=0x99c,
    HINDI_CON    | HINDI_SP_CENTER_T,      //BENGALI_C_JHA=0x99d,
    HINDI_CON    | HINDI_SP_CENTER_T,      //BENGALI_C_NYA=0x99e,
    HINDI_CON    | HINDI_SP_CENTER_T,      //BENGALI_C_TTA=0x99f,  
    HINDI_CON    | HINDI_SP_NO_T,          //BENGALI_C_TTHA=0x9a0,
    HINDI_CON    | HINDI_SP_CENTER_T,      //BENGALI_C_DDA=0x9a1,
    HINDI_CON    | HINDI_SP_CENTER_T,      //BENGALI_C_DDHA=0x9a2,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //BENGALI_C_NNA=0x9a3,
    HINDI_CON    | HINDI_SP_CENTER_T,      //BENGALI_C_TA=0x9a4,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //BENGALI_C_THA=0x9a5,
    HINDI_CON    | HINDI_SP_CENTER_T,      //BENGALI_C_DA=0x9a6,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //BENGALI_C_DHA=0x9a7,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //BENGALI_C_NA=0x9a8,
    HINDI_INVALID,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //BENGALI_C_PA=0x9aa,
    HINDI_CON    | HINDI_SP_CENTER_T,      //BENGALI_C_PHA=0x9ab,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //BENGALI_C_BA=0x9ac,
    HINDI_CON    | HINDI_SP_CENTER_T,      //BENGALI_C_BHA=0x9ad,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //BENGALI_C_MA=0x9ae,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //BENGALI_C_YA=0x9af,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //BENGALI_C_RA=0x9b0,
    HINDI_INVALID,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //BENGALI_C_LA=0x9b2,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //BENGALI_C_SHA=0x9b6,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //BENGALI_C_SSA=0x9b7,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //BENGALI_C_SA=0x9b8,
    HINDI_CON    | HINDI_SP_CENTER_T,      //BENGALI_C_HA=0x9b9,
    
    HINDI_INVALID,
    HINDI_INVALID,
    
    /* Various signs */
    HINDI_SIGN   | HINDI_SP_LEFT_T_DOWN_POS,//BENGALI_S_NUKTA=0x9bc,
    HINDI_SIGN   | HINDI_SP_RIGHT_POS,     //BENGALI_S_AVAGRAHA=0x9bd,

    /* Dependent vowel signs */
    HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,  //BENGALI_DV_AA=0x9be,
    HINDI_DEPVOW | HINDI_SP_LEFT_JOINER,   //BENGALI_DV_I   =0x9bf,
    HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,  //BENGALI_DV_II=0x9c0,
    HINDI_DEPVOW | HINDI_SP_CENTER_T_DOWN_POS,//BENGALI_DV_U=0x9c1,
    HINDI_DEPVOW | HINDI_SP_CENTER_T_DOWN_POS,//BENGALI_DV_UU=0x9c2,
    HINDI_DEPVOW | HINDI_SP_CENTER_T_DOWN_POS,//BENGALI_DV_VR=0x9c3,
    HINDI_DEPVOW | HINDI_SP_RIGHT_T_DOWN_POS, //BENGALI_DV_VRR=0x9c4,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_DEPVOW | HINDI_SP_LEFT_JOINER,   //BENGALI_DV_E=0x9c7, modify by anning.deng@mstarsemi.com 2010.11.19
    HINDI_DEPVOW | HINDI_SP_LEFT_JOINER,   //BENGALI_DV_AI=0x9c8,modify by anning.deng@mstarsemi.com 2010.11.19

    HINDI_INVALID,
    HINDI_INVALID,

    /* Two-part dependent vowel signs*/
    HINDI_DEPVOW | HINDI_SP_TWOPART_JOINER,//BENGALI_DV_O=0x9cb,
    HINDI_DEPVOW | HINDI_SP_TWOPART_JOINER,//BENGALI_DV_AU=0x9cc,

    /* Virama */
    HINDI_SIGN | HINDI_SP_RIGHT_T_DOWN_POS,//BENGALI_S_HALANT   =0x9cd,
    
    /* Additional consonant */
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW, //BENGALI_AD_TA=0x9ce,
    
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    
    /* Signs */
    HINDI_DEPVOW | HINDI_SP_RIGHT_JOINER,  //BENGALI_AD_AU=0x9d7,
    
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    HINDI_INVALID,
    
    /* Additional consonant */
    HINDI_CON    | HINDI_SP_CENTER_T,      //BENGALI_C_RRA=0x9dc,
    HINDI_CON    | HINDI_SP_CENTER_T,      //BENGALI_C_RHA=0x9dd,
    HINDI_INVALID,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //BENGALI_C_YYA=0x9df,

    /*Additional vowels for Sanskrit*/
    HINDI_INDVOW | HINDI_SP_DOUBLE_T,      //BENGALI_C_VRR=0x9e0,
    HINDI_INDVOW | HINDI_SP_NO_T,          //BENGALI_C_VLL=0x9e1,
    HINDI_DEPVOW | HINDI_SP_LEFT_T_DOWN_POS,    //BENGALI_S_VRR=0x9e2,
    HINDI_DEPVOW | HINDI_SP_CENTER_T_DOWN_POS,  //BENGALI_S_VLL=0x9e3,
    
    HINDI_INVALID,
    HINDI_INVALID,
    
    /* Digits */
    HINDI_NUM,                             //BENGALI_D_ZERO=0x9e6,
    HINDI_NUM,                             //BENGALI_D_ONE=0x9e7,
    HINDI_NUM,                             //BENGALI_D_TWO=0x9e8,
    HINDI_NUM,                             //BENGALI_D_THREE=0x9e9,
    HINDI_NUM,                             //BENGALI_D_FOUR=0x9ea,
    HINDI_NUM,                             //BENGALI_D_FIVE=0x9eb,
    HINDI_NUM,                             //BENGALI_D_SIX=0x9ec,
    HINDI_NUM,                             //BENGALI_D_SEVEN=0x9ed,
    HINDI_NUM,                             //BENGALI_D_EIGHT=0x9ee,
    HINDI_NUM,                             //BENGALI_D_NINE=0x9ef,

    /*Bengali-spacific additions*/
    HINDI_CON    | HINDI_SP_RIGHT_T,       //BENGALI_C_MRA=0x9f0,
    HINDI_CON    | HINDI_SP_RIGHT_T,       //BENGALI_C_LRA=0x9f1,
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW, //BENGALI_OS_RUPEE=0x9f2,
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW, //BENGALI_C_RUPEE_SIGN=0x9f3,
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW, //BENGALI_C_CURONE=0x9f4,
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW, //BENGALI_C_CURTWO=0x9f5,
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW, //BENGALI_C_CURTHREE=0x9f6,
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW, //BENGALI_C_CURFOUR=0x9f7,
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW, //BENGALI_OS_CURLESSDEN=0x9f8,
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW, //BENGALI_OS_CURDENSIXTEEN=0x9f9,
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW, //BENGALI_OS_ISSHAR= x9fa
    HINDI_INDVOW | HINDI_SP_SINGLE_INDVOW  //BENGALI GANDA MARK=09FB
};          

const HindiFeatureRecord_t _g_sBengFeatureMap[] = 
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
/*HINDI_FEATURE_INIT*/  {HINDI_FEATURE_INIT, _HindiInitFeatureMask},
/*HINDI_FEATURE_PRES*/  {HINDI_FEATURE_PRES, _HindiPresFeatureMask},
/*HINDI_FEATURE_ABVS*/  {HINDI_FEATURE_ABVS, _HindiAbvsFeatureMask},
/*HINDI_FEATURE_BLWS*/ {HINDI_FEATURE_BLWS, _HindiBlwsFeatureMask},
/*HINDI_FEATURE_PSTS*/  {HINDI_FEATURE_PSTS, _HindiPstsFeatureMask},
/*HINDI_FEATURE_HALN*/  {HINDI_FEATURE_HALN, _HindiHalnFeatureMask},
/*HINDI_FEATURE_CALT*/  {HINDI_FEATURE_CALT, _HindiCaltFeatureMask},
/*HINDI_FEATURE_ABVM*/ {HINDI_FEATURE_ABVM, _HindiAbvmFeatureMask},
/*HINDI_FEATURE_BLWM*/ {HINDI_FEATURE_BLWM, _HindiBlwmFeatureMask}
};
const U16 _g_u16BengFeatureCount = (sizeof(_g_sBengFeatureMap)/sizeof(HindiFeatureRecord_t));

static U16 _msAPI_MLE_FontBengaliRefineCluster( HindiScript_e eScript, const U16 *pu16InTxt, U32 u32InLen, U32 u32Offset, U16 *pu16Cluster, U16 *pu16CluserSize, U16 u16ClusterOffset, BOOLEAN bIsDispStr, U32 *pu32Features, const U16 *pu16OriginTxt, U32 u32OriginOffset);
static BOOLEAN _msAPI_MLE_FontBengaliGetNextCodeXOffset( U16 *pu16CurrentRefChar, U16 *pu16CurrentCharRefWidth, U16 u16NextChar, U16 u16NextCharWidth, S16 *ps16XOffset, U16 u16BaseWidth, U16 u16PreChar, BOOLEAN bFirstCharInCluster);
static BOOLEAN _msAPI_MLE_FontBengCharIsRA( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontBengCharIsHalant( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontBengCharIsNukta( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontBengCharIsBindu( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontBengCharWithNukta( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontBengCharIsNoHalfCon( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontBengCharIsFollowingZWJ( U16 u16Character );
static U16 _msAPI_MLE_FontBengGetTwoWordLeftChar( U16 u16Character );
static U16 _msAPI_MLE_FontBengGetTwoWordRightChar( U16 u16Character );
static HindiCharacter_e _msAPI_MLE_FontBengGetCharType( U16 u16Character );
static HindiSpecialCharacter_e _msAPI_MLE_FontBengGetCharSpecialType( U16 u16Character );
static HindiOtherCharacterType_e _msAPI_MLE_FontBengGetCharOtherType( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontBengCharIsBlwf( U16 u16FirstChar, U16 u16SecondChar );
static BOOLEAN _msAPI_MLE_FontBengCharIsPstf( U16 u16FirstChar, U16 u16SecondChar );
static BOOLEAN _msAPI_MLE_FontBengCharIsLigated( U16 u16FirstChar, U16 u16SecondChar, BOOLEAN withZWJ );
static BOOLEAN _msAPI_MLE_FontBengStrWithAkhand( U16 *pu16Str, U32 u32StrLen, U16 u16Offset );
static U32 _msAPI_MLE_FontBengSetFeature( U32 u32FeatureTags, HindiFeature_e eAddFeature );
static U16 _msAPI_MLE_FontBengGetFeatureMap( const HindiFeatureRecord_t **ppasFeatureMap );

static BOOLEAN _msAPI_MLE_FontBengCharIsSign( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontBengCharIsComposed( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontBengFeatureWithRphf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType );
static BOOLEAN _msAPI_MLE_FontBengFeatureWithBlwf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType );

__SLDPM_FREE__ const HindiTable_t g_bengTable =
{
    HINDI_SCRIPT_BENG,
    BENGALI_S_CHANDRA_BINDU,
    BENGALI_OS_ISSHAR,
    NULL,//fnGetCluster
    &_msAPI_MLE_FontBengaliRefineCluster,
    &_msAPI_MLE_FontBengaliGetNextCodeXOffset,
    &_msAPI_MLE_FontBengCharIsRA,
    &_msAPI_MLE_FontBengCharIsHalant,
    &_msAPI_MLE_FontBengCharIsNukta,
    &_msAPI_MLE_FontBengCharIsBindu,
    &_msAPI_MLE_FontBengCharWithNukta,
    &_msAPI_MLE_FontBengCharIsNoHalfCon,
    &_msAPI_MLE_FontBengCharIsFollowingZWJ,
    &_msAPI_MLE_FontBengGetTwoWordLeftChar,
    &_msAPI_MLE_FontBengGetTwoWordRightChar,
    &_msAPI_MLE_FontBengGetCharType,
    &_msAPI_MLE_FontBengGetCharSpecialType,
    &_msAPI_MLE_FontBengGetCharOtherType,
    &_msAPI_MLE_FontBengCharIsBlwf,
    &_msAPI_MLE_FontBengCharIsPstf,
    &_msAPI_MLE_FontBengCharIsLigated,
    &_msAPI_MLE_FontBengStrWithAkhand,
    &_msAPI_MLE_FontBengSetFeature,
    &_msAPI_MLE_FontBengGetFeatureMap,
    &_msAPI_MLE_FontBengCharIsSign,
    &_msAPI_MLE_FontBengCharIsComposed,
    &_msAPI_MLE_FontBengFeatureWithRphf,
    &_msAPI_MLE_FontBengFeatureWithBlwf
};

static U16 _msAPI_MLE_FontBengaliRefineCluster( HindiScript_e eScript, const U16 *pu16InTxt, U32 u32InLen, U32 u32Offset, U16 *pu16Cluster, U16 *pu16CluserSize, U16 u16ClusterOffset, BOOLEAN bIsDispStr, U32 *pu32Features, const U16 *pu16OriginTxt, U32 u32OriginOffset)
{
//Below is XP spec, in Win7, it seems that Microsoft modified reorder rule of Bengali, so we don't need to reorder here
#if 0
    U16 u16Character = 0;
    U16 i = 0;
    U16 u16Index = 0;
#endif
    U16 u16CluserSize = *pu16CluserSize;
    BOOLEAN bIsInit = FALSE;

    eScript = eScript;
    pu16InTxt = pu16InTxt;
    u32InLen = u32InLen;
    u32Offset = u32Offset;
    bIsDispStr = bIsDispStr;
    
    if(u16CluserSize>1 && _msAPI_MLE_FontBengGetCharType(pu16Cluster[1]) == HINDI_CON
        && (pu16Cluster[0] == BENGALI_DV_E || pu16Cluster[0] == BENGALI_DV_AI) )
    {
        if(u32OriginOffset == 0)
        {
            bIsInit = TRUE;
        }
        else if(pu16OriginTxt[u32OriginOffset-1] == 0)
        {
            bIsInit = TRUE;
        }
        else if(IS_BENGALI_RANGE(pu16OriginTxt[u32OriginOffset-1]) == FALSE)
        {
            bIsInit = TRUE;
        }
    }

    if(bIsInit)
    {
#if __FEATURE_VECTOR_FONT__
        if ( msAPI_MLE_FONTBASE_IsVectorFontExist() )
        {
            *pu32Features = _msAPI_MLE_FontBengSetFeature(*pu32Features, HINDI_FEATURE_INIT); 
        }
#endif //__FEATURE_VECTOR_FONT__            
    }

//Below is XP spec, in Win7, it seems that Microsoft modified reorder rule of Bengali, so we don't need to reorder here
#if 0
    for ( i = 0; i < u16CluserSize; i++ )
    {
        if((u16CluserSize - i) >=3)
        {
            u16Index = i;
            u16Character = pu16Cluster[u16Index];

            if( _msAPI_MLE_FontBengGetCharType(u16Character) == HINDI_CON )
            {
                u16Index++;
                u16Character = pu16Cluster[u16Index];
                if( _msAPI_MLE_FontBengGetCharType(u16Character) == HINDI_DEPVOW 
                    && _msAPI_MLE_FontBengGetCharSpecialType(u16Character) == HINDI_SP_RIGHT_JOINER )
                {
                    u16Index++;
                    u16Character = pu16Cluster[u16Index];
                    if( _msAPI_MLE_FontBengGetCharType(u16Character) == HINDI_SIGN 
                        && _msAPI_MLE_FontBengGetCharSpecialType(u16Character) == HINDI_SP_CENTER_T_UP_POS )
                    {
                        U16 tmpCode = pu16Cluster[u16Index];
                        pu16Cluster[u16Index] = pu16Cluster[u16Index-1];
                        pu16Cluster[u16Index-1] = tmpCode;
                        i = u16Index;
                    }
                }
            }
        }
    }
#endif
    
    return u16ClusterOffset;
}

static BOOLEAN _msAPI_MLE_FontBengaliGetNextCodeXOffset( U16 *pu16CurrentRefChar, U16 *pu16CurrentCharRefWidth, U16 u16NextChar, U16 u16NextCharWidth, S16 *ps16XOffset, U16 u16BaseWidth, U16 u16PreChar, BOOLEAN bFirstCharInCluster)
{
    BOOLEAN bReturn = FALSE;
 
    bReturn = bReturn;
    u16NextChar = u16NextChar;
    u16NextCharWidth = u16NextCharWidth;
    u16BaseWidth  = u16BaseWidth;
    u16PreChar = u16PreChar;
    bFirstCharInCluster = bFirstCharInCluster;
                    
    if ( ps16XOffset == NULL || pu16CurrentRefChar == NULL || pu16CurrentCharRefWidth == NULL )
    {
        return FALSE;
    }

    if( ( IS_BENGALI_RANGE(*pu16CurrentRefChar) )
        && ( IS_BENGALI_RANGE(u16NextChar) ) )
    {
        U16 u16TempBaseWidth = ((u16BaseWidth > 0) ? (u16BaseWidth): *pu16CurrentCharRefWidth);
        U16 u16HalfTempBaseWidth = u16TempBaseWidth/2;

        HindiSpecialCharacter_e eNextSpType = _msAPI_MLE_FontBengGetCharSpecialType(u16NextChar);
        HindiSpecialCharacter_e eCurrentSpType = _msAPI_MLE_FontBengGetCharSpecialType(*pu16CurrentRefChar);
        
        if(bFirstCharInCluster == TRUE)
        {
            if(u16PreChar == 0x09C2)
            {
                *ps16XOffset = *ps16XOffset-4;
            }

            return TRUE;
        }
        else if( _msAPI_MLE_FontBengGetCharType(u16NextChar) == HINDI_CON )
        {
            U16 nOffset = 0;

            if(BENGALI_C_DDA == *pu16CurrentRefChar)
            {
                if(BENGALI_C_GA == u16NextChar)
                {
                    nOffset = 2; // 09A1+09CD+0997
                }
            }
            else if(BENGALI_C_RRA == *pu16CurrentRefChar)
            {
                if(BENGALI_C_GA == u16NextChar)
                {
                    nOffset = 2; // 09DC+09CD+0997
                }
            }


            if(nOffset > 0)
            {
                *ps16XOffset = *ps16XOffset + *pu16CurrentCharRefWidth-nOffset;
                *pu16CurrentRefChar = u16NextChar;
                *pu16CurrentCharRefWidth = u16NextCharWidth;
                return TRUE;
            }
        }

        switch ( _msAPI_MLE_FontBengGetCharType(u16NextChar) )
        {            
            case HINDI_DEPVOW:
                if(u16NextChar >= BENGALI_DV_U && u16NextChar<= BENGALI_DV_VRR)
                {
                    U16 u16XOffset = 0;

                    if( IS_BENGALI_CONST_NEED_DV_RIGHT_CHAR(*pu16CurrentRefChar) )
                    {
                        u16XOffset = (*pu16CurrentCharRefWidth/2);
                    }
                    else if( eCurrentSpType == HINDI_SP_RIGHT_T 
                        || BENGALI_C_DA == *pu16CurrentRefChar 
                        || BENGALI_C_JA== *pu16CurrentRefChar )
                    {
                        if(BENGALI_DV_U == u16NextChar)
                        {
                            if(*pu16CurrentCharRefWidth >= u16NextCharWidth)
                            {
                                u16XOffset = *pu16CurrentCharRefWidth - u16NextCharWidth;
                            }
                        }
                        else if(BENGALI_DV_UU == u16NextChar)
                        {
                            if(*pu16CurrentCharRefWidth >= u16TempBaseWidth)
                            {
                                u16XOffset = *pu16CurrentCharRefWidth - u16TempBaseWidth;
                            }
                        }
                        else
                        {
                            if(*pu16CurrentCharRefWidth >= (u16NextCharWidth+u16HalfTempBaseWidth))
                            {
                                u16XOffset = *pu16CurrentCharRefWidth - (u16NextCharWidth+u16HalfTempBaseWidth);
                            }
                        }
                        
                    }
                    else if(BENGALI_DV_U != u16NextChar)
                    {
                        if(BENGALI_C_KA== *pu16CurrentRefChar)
                        {
                            u16XOffset = (*pu16CurrentCharRefWidth/2);
                            if(BENGALI_DV_UU == u16NextChar)
                            {
                                if(u16XOffset >= 1)
                                {
                                    u16XOffset--;
                                }
                            }
                            else if(BENGALI_DV_VR == u16NextChar)
                            {
                                if(u16XOffset >= u16NextCharWidth)
                                {
                                    u16XOffset = u16XOffset - u16NextCharWidth;
                                }
                            }
                        }
                        else
                        {
                            u16XOffset = (*pu16CurrentCharRefWidth/2);
                        }
                    }
                 
                    *ps16XOffset = *ps16XOffset + u16XOffset;
                    bReturn = TRUE;
                    break;
                }

                switch ( eNextSpType )
                {
                    case HINDI_SP_LEFT_T_DOWN_POS:
                    case HINDI_SP_CENTER_T_DOWN_POS:
                    {
                        bReturn = TRUE; //handled, *ps16XOffset = *ps16XOffset + 0;
                        break; 
                    }

                    case HINDI_SP_CENTER_T_UP_POS:
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }

    return bReturn;
} 
 
static BOOLEAN _msAPI_MLE_FontBengCharIsRA( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_BENGALI_RANGE(u16Character) )
    {
        if ( IS_BENGALI_RA_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
     
    return bResult;
}
 
static BOOLEAN _msAPI_MLE_FontBengCharIsHalant( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_BENGALI_RANGE(u16Character) )
    {
        if ( IS_BENGALI_HALANT_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
     
    return bResult;
}
     
static BOOLEAN _msAPI_MLE_FontBengCharIsNukta( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_BENGALI_RANGE(u16Character) )
    {
        if ( IS_BENGALI_NUKTA_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
     
    return bResult;
}
     
static BOOLEAN _msAPI_MLE_FontBengCharIsBindu( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_BENGALI_RANGE(u16Character) )
    {
        if ( IS_BENGALI_BINDU_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
     
    return bResult;
}

static BOOLEAN _msAPI_MLE_FontBengCharWithNukta( U16 u16Character )
{
    BOOLEAN bResult = FALSE;
    
    if ( IS_BENGALI_RANGE(u16Character) )
    {
        if ( IS_BENGALI_WITH_NUKTA_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
         
    return bResult;
}

static BOOLEAN _msAPI_MLE_FontBengCharIsNoHalfCon( U16 u16Character )
{
    BOOLEAN bResult = FALSE;
    
    if ( IS_BENGALI_RANGE(u16Character) )
    {
        if ( IS_BENGALI_NO_HALF_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
         
    return bResult;
}

static BOOLEAN _msAPI_MLE_FontBengCharIsFollowingZWJ( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_BENGALI_RANGE(u16Character) )
    {
        if ( IS_BENGALI_HALANT_CHAR(u16Character) || u16Character == BENGALI_DV_U || u16Character == BENGALI_DV_UU || u16Character == BENGALI_DV_VR)
        {
            bResult = TRUE;
        }
    }
     
    return bResult;
}
       
static U16 _msAPI_MLE_FontBengGetTwoWordLeftChar( U16 u16Character )
{
    U16 u16ReturnChar = 0;

    if ( IS_BENGALI_RANGE(u16Character) && _msAPI_MLE_FontBengGetCharSpecialType(u16Character) == HINDI_SP_TWOPART_JOINER )
    {
        if ( u16Character == BENGALI_DV_O || u16Character == BENGALI_DV_AU )
        {
            u16ReturnChar = BENGALI_DV_E;
        }
    }
     
    return u16ReturnChar;
}

static U16 _msAPI_MLE_FontBengGetTwoWordRightChar( U16 u16Character )
{
    U16 u16ReturnChar = 0;

    if ( IS_BENGALI_RANGE(u16Character) && _msAPI_MLE_FontBengGetCharSpecialType(u16Character) == HINDI_SP_TWOPART_JOINER )
    {
        if ( u16Character == BENGALI_DV_O )
        {
            u16ReturnChar = BENGALI_DV_AA;
        }
        else if ( u16Character == BENGALI_DV_AU )
        {
            u16ReturnChar = BENGALI_AD_AU;
        }
    }
     
    return u16ReturnChar;
}

static HindiCharacter_e _msAPI_MLE_FontBengGetCharType( U16 u16Character )
{
    HindiCharacter_e eType = HINDI_INVALID;

    if ( IS_BENGALI_RANGE(u16Character) )
    {
        eType = (g_BengaliCharTypeArray[u16Character - BENGALI_MASK]) & 0x0F;
    }
         
    return eType;
}
 
static HindiSpecialCharacter_e _msAPI_MLE_FontBengGetCharSpecialType( U16 u16Character )
{
    HindiSpecialCharacter_e eType = HINDI_SP_INVALID;

    if ( IS_BENGALI_RANGE(u16Character) )
    {
        eType = (g_BengaliCharTypeArray[u16Character - BENGALI_MASK]) & 0xF0;
    }
     
    return eType;
}

static HindiOtherCharacterType_e _msAPI_MLE_FontBengGetCharOtherType( U16 u16Character )
{
    u16Character = u16Character;
    
    return HINDI_OTYPE_INVALID;
}

static BOOLEAN _msAPI_MLE_FontBengCharIsBlwf( U16 u16FirstChar, U16 u16SecondChar )
{
    BOOLEAN bResult = FALSE;

    if ( IS_BENGALI_RANGE(u16FirstChar) && IS_BENGALI_RANGE(u16SecondChar) )
    {
        if ( IS_BENGALI_HALANT_CHAR(u16FirstChar) 
             && (IS_BENGALI_RA_CHAR(u16SecondChar) || u16SecondChar == BENGALI_C_BA) )
        {
            bResult = TRUE;
        }
    }
     
    return bResult;
}

static BOOLEAN _msAPI_MLE_FontBengCharIsPstf( U16 u16FirstChar, U16 u16SecondChar )
{
    BOOLEAN bResult = FALSE;

    if ( IS_BENGALI_RANGE(u16FirstChar) && IS_BENGALI_RANGE(u16SecondChar) )
    {
        if ( IS_BENGALI_HALANT_CHAR(u16FirstChar) && IS_BENGALI_POST_BASE_CON(u16SecondChar) )
        {
            bResult = TRUE;
        }
    }
     
    return bResult;
}

static BOOLEAN _msAPI_MLE_FontBengCharIsLigated( U16 u16FirstChar, U16 u16SecondChar, BOOLEAN withZWJ )
{
    BOOLEAN bResult = FALSE;

    if ( IS_BENGALI_RANGE(u16FirstChar) && IS_BENGALI_RANGE(u16SecondChar) )
    {
         if ( (u16FirstChar == BENGALI_C_GA && u16SecondChar == BENGALI_DV_U)
              || (u16FirstChar == BENGALI_C_RA && u16SecondChar == BENGALI_DV_U) 
              || (u16FirstChar == BENGALI_C_RA && u16SecondChar == BENGALI_DV_UU)
              || (u16FirstChar == BENGALI_C_SHA && u16SecondChar == BENGALI_DV_U)
              || (u16FirstChar == BENGALI_C_HA && u16SecondChar == BENGALI_DV_U)
              || (u16FirstChar == BENGALI_C_HA && u16SecondChar == BENGALI_DV_UU) 
              || (u16FirstChar == BENGALI_C_HA && u16SecondChar == BENGALI_DV_VR) )
        {
            if ( withZWJ )
            {
#ifdef __BENGALI_NON_LIGATED__      
                bResult = TRUE; 
#else
                bResult = FALSE;
#endif //__BENGALI_NON_LIGATED__                
            }
            else
            {
#ifdef __BENGALI_NON_LIGATED__      
                bResult = FALSE; 
#else
                bResult = TRUE;
#endif //__BENGALI_NON_LIGATED__                
            }
         }
    }
     
    return bResult;
}

static BOOLEAN _msAPI_MLE_FontBengStrWithAkhand( U16 *pu16Str, U32 u32StrLen, U16 u16Offset )
{
    BOOLEAN bResult = FALSE;

    if ( IS_BENGALI_RANGE(pu16Str[u16Offset]) )
    {
        if ( (u32StrLen - u16Offset) > 2 )
        {
            if ( pu16Str[u16Offset] == BENGALI_C_KA && pu16Str[u16Offset+1] == BENGALI_S_HALANT && pu16Str[u16Offset+2] == BENGALI_C_SSA )
            {
                bResult = TRUE;
            }
            else if ( pu16Str[u16Offset] == BENGALI_C_JA && pu16Str[u16Offset+1] == BENGALI_S_HALANT && pu16Str[u16Offset+2] == BENGALI_C_NYA )
            {
                bResult = TRUE;
            }
        }
    }
     
    return bResult;
}

static U32 _msAPI_MLE_FontBengSetFeature( U32 u32FeatureTags, HindiFeature_e eFeature )
{
    U16 i;
    for ( i = 0; i < _g_u16BengFeatureCount; i++ )
    {
        if ( _g_sBengFeatureMap[i].eTag == eFeature )
        {
            u32FeatureTags = u32FeatureTags | _g_sBengFeatureMap[i].u32Mask;
            break;
        }
    }
    return u32FeatureTags;
}

static U16 _msAPI_MLE_FontBengGetFeatureMap( const HindiFeatureRecord_t **ppasFeatureMap )
{
    *ppasFeatureMap = _g_sBengFeatureMap;
    return (U16)_g_u16BengFeatureCount;
}

static BOOLEAN _msAPI_MLE_FontBengCharIsSign( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_BENGALI_RANGE(u16Character) )
    {
        if ( _msAPI_MLE_FontBengGetCharType(u16Character) == HINDI_SIGN )
        {
            bResult = TRUE;
        }
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_FontBengCharIsComposed( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_BENGALI_RANGE(u16Character) )
    {
        if ( _msAPI_MLE_FontBengGetCharType(u16Character) == HINDI_SIGN && _msAPI_MLE_FontBengGetCharSpecialType(u16Character) != HINDI_SP_RIGHT_JOINER )
        {
            bResult = TRUE;
        }
        else if ( IS_BENGALI_DEPVOW_COMPOSING_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
     
    return bResult;
}

static BOOLEAN _msAPI_MLE_FontBengFeatureWithRphf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType )
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

static BOOLEAN _msAPI_MLE_FontBengFeatureWithBlwf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType )
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
 
U16 msAPI_MLE_FontBengaliGetYAPHALAAClusterSize( const U16 *pu16Txt, U32 u32InLen, U16 u16ConsumedCount)
{
    U16 u16Size = 0;

    if(u32InLen < u16ConsumedCount)
        return u16Size;

    if ( _msAPI_MLE_FontBengCharIsNukta(pu16Txt[u16ConsumedCount]) 
        && ((u32InLen - u16ConsumedCount) >= 3))
    {
        if ( _msAPI_MLE_FontBengCharIsHalant(pu16Txt[u16ConsumedCount+1]) )
        {
            if ( IS_BENGALI_POST_BASE_CON(pu16Txt[u16ConsumedCount+2]) )
            {
                u16Size = 3;
            }
        }
    }
    else if ( _msAPI_MLE_FontBengCharIsHalant(pu16Txt[u16ConsumedCount])
        && ((u32InLen - u16ConsumedCount) >= 2))
    {
        if ( IS_BENGALI_POST_BASE_CON(pu16Txt[u16ConsumedCount+1]) )
        {
            if ( IS_BENGALI_DV_AA_CHAR(pu16Txt[u16ConsumedCount+2]) )
                u16Size = 3;
            else
                u16Size = 2;
        }
    }
    return u16Size;
}

U16 msAPI_MLE_FontBengaliGetLigatedCluster( const U16 *pu16Txt, U32 u32InLen, U16 *pu16Cluster, U16 u16BufferSize, U16 u16ClusterSize, U16 *pu16ConsumedCount, U16 *pu16SeqInCluster)
{
    U16 u16Character = 0;

    if ( pu16Txt == NULL || u16ClusterSize!=2 || u32InLen < u16ClusterSize || pu16ConsumedCount == NULL )
    {
        return u16ClusterSize;
    }

    do 
    {
        if( IS_BENGALI_RANGE(*pu16Txt) )
        {
            u16Character = pu16Txt[1];
            if(FONT_CONTROL_ZWJ == u16Character)
            {
                u16Character = pu16Txt[0];
                if(BENGALI_C_GA == u16Character)
                {
                    u16Character = pu16Txt[2];
                    if(BENGALI_DV_U == u16Character)
                    {
                        _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );
                    }
                }
                else if(BENGALI_C_RA == u16Character)
                {
                    u16Character = pu16Txt[2];
                    if(BENGALI_DV_U == u16Character || BENGALI_DV_UU == u16Character)
                    {
                        _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );
                    }
                }
                else if(BENGALI_C_SHA == u16Character)
                {
                    u16Character = pu16Txt[2];
                    if(BENGALI_DV_U == u16Character)
                    {
                        _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );
                    }
                }
                else if(BENGALI_C_HA == u16Character)
                {
                    u16Character = pu16Txt[2];
                    if(BENGALI_DV_U == u16Character || BENGALI_DV_UU == u16Character || BENGALI_DV_VR == u16Character)
                    {
                        _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );
                    }
                }
            }
        }
    } while(FALSE);

    return u16ClusterSize;
}

#endif //__INDIC_FONT__
#endif //__BENGALI_FONT__

