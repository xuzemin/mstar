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

#ifdef __KNDA_FONT__
#include "msAPI_MLE_font_kannada.h"

/*------------------------------------------------------------------------------------------
*
*                                                                                     MACRO DEFINE
*
-------------------------------------------------------------------------------------------*/

const U8 g_KannadaCharTypeArray[] =
{
    HINDI_INVALID,
        
    /* VARIOUS SIGNS */
    HINDI_INVALID,      /* 0xc81 */
    HINDI_SIGN      |   HINDI_SP_RIGHT_POS,        /* KANNADA_S_ANUSVARA = 0xc82 */
    HINDI_SIGN      |   HINDI_SP_RIGHT_POS,        /* KANNADA_S_VISARGA = 0xc83 */
    HINDI_INVALID,     /* 0xc84 */
    
    /* INDEPENDENT VOWEL */
    HINDI_INDVOW    |   HINDI_SP_NO_T,      /* KANNADA_IV_A = 0xc85 */
    HINDI_INDVOW    |   HINDI_SP_NO_T,      /* KANNADA_IV_AA = 0xc86 */
    HINDI_INDVOW    |   HINDI_SP_NO_T,      /* KANNADA_IV_I = 0xc87 */
    HINDI_INDVOW    |   HINDI_SP_NO_T,      /* KANNADA_IV_II = 0xc88 */
    HINDI_INDVOW    |   HINDI_SP_NO_T,      /* KANNADA_IV_U = 0xc89 */
    HINDI_INDVOW    |   HINDI_SP_NO_T,      /* KANNADA_IV_UU = 0xc8a */
    HINDI_INDVOW    |   HINDI_SP_NO_T,      /* KANNADA_IV_VR = 0xc8b */
    HINDI_INDVOW    |   HINDI_SP_NO_T,      /* KANNADA_IV_VL = 0xc8c */
    HINDI_INVALID,                                          /* 0xc8d */
    HINDI_INDVOW    |   HINDI_SP_NO_T,      /* KANNADA_IV_E = 0xc8e */
    HINDI_INDVOW    |   HINDI_SP_NO_T,      /* KANNADA_IV_EE = 0xc8f */
    HINDI_INDVOW    |   HINDI_SP_NO_T,      /* KANNADA_IV_AI = 0xc90 */
    HINDI_INVALID,                                          /* 0xc91 */
    HINDI_INDVOW    |   HINDI_SP_NO_T,      /* KANNADA_IV_O = 0xc92 */
    HINDI_INDVOW    |   HINDI_SP_NO_T,      /* KANNADA_IV_OO = 0xc93 */
    HINDI_INDVOW    |   HINDI_SP_NO_T,      /* KANNADA_IV_AU = 0xc94 */
    
    /*  CONSONANTS  */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_KA = 0xc95 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_KHA = 0xc96 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_GA = 0xc97 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_GHA = 0xc98 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_NGA = 0xc99 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_CA = 0xc9a */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_CHA = 0xc9b */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_JA = 0xc9c */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_JHA = 0xc9d */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_NYA = 0xc9e */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_TTA = 0xc9f */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_TTHA = 0xca0 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_DDA = 0xca1 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_DDHA = 0xca2 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_NNA = 0xca3 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_TA = 0xca4 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_THA = 0xca5 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_DA = 0xca6 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_DHA = 0xca7 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_NA = 0xca8 */
    HINDI_INVALID,                                                 /* 0xca9 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_PA = 0xcaa */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_PHA = 0xcab */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_BA = 0xcac */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_BHA = 0xcad */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_MA = 0xcae */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_YA = 0xcaf */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_RA = 0xcb0 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_RRA = 0xcb1 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_LA = 0xcb2 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_LLA = 0xcb3 */
    HINDI_INVALID,                                                 /* 0xcb4 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_VA = 0xcb5 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_SHA = 0xcb6 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_SSA = 0xcb7 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_SA = 0xcb8 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* KANNADA_C_HA = 0xcb9 */
    
    /* VARIOUS SIGNS */
    HINDI_INVALID,     /* 0xcba */
    HINDI_INVALID,     /* 0xcbb */
    HINDI_SIGN      |   HINDI_SP_CENTER_T_DOWN_POS,     /* KANNADA_S_NUKTA = 0xcbc */    
    HINDI_SIGN      |   HINDI_SP_RIGHT_POS,            /* KANNADA_S_AVAGRAHA = 0xcbd*/
    
    /*  DEPENDENT VOWELS  */
    HINDI_DEPVOW    |   HINDI_SP_RIGHT_JOINER,         /* KANNADA_DV_AA = 0xcbe */
    HINDI_DEPVOW    |   HINDI_SP_CENTER_T_UP_POS,      /* KANNADA_DV_I = 0xcbf */
    HINDI_DEPVOW    |   HINDI_SP_TWOPART_JOINER,       /* KANNADA_DV_II = 0xcc0 */
    HINDI_DEPVOW    |   HINDI_SP_RIGHT_JOINER,         /* KANNADA_DV_U = 0xcc1 */
    HINDI_DEPVOW    |   HINDI_SP_RIGHT_JOINER,         /* KANNADA_DV_UU = 0xcc2 */
    HINDI_DEPVOW    |   HINDI_SP_RIGHT_JOINER,         /* KANNADA_DV_VR = 0xcc3 */
    HINDI_DEPVOW    |   HINDI_SP_RIGHT_JOINER,         /* KANNADA_DV_VRR = 0xcc4 */
    HINDI_INVALID,                                                      /* 0xcc5 */
    HINDI_DEPVOW    |   HINDI_SP_CENTER_T_UP_POS,      /* KANNADA_DV_E = 0xcc6 */
    HINDI_DEPVOW    |   HINDI_SP_TWOPART_JOINER,       /* KANNADA_DV_EE = 0xcc7 */
    HINDI_DEPVOW    |   HINDI_SP_TWOPART_JOINER,       /* KANNADA_DV_AI = 0xcc8 */
    HINDI_INVALID,     /* 0xcc9 */
    HINDI_DEPVOW    |   HINDI_SP_TWOPART_JOINER,       /* KANNADA_DV_O = 0xcca */
    HINDI_DEPVOW    |   HINDI_SP_TWOPART_JOINER,       /* KANNADA_DV_OO = 0xccb */
    HINDI_DEPVOW    |   HINDI_SP_CENTER_T_UP_POS,      /* KANNADA_DV_AU = 0xccc */
    HINDI_HALANT    |   HINDI_SP_CENTER_T_UP_POS,      /* KANNADA_S_HALANT = 0xccd */
    HINDI_INVALID,                                     /* 0xcce */
    HINDI_INVALID,                                     /* 0xccf */
    HINDI_INVALID,                                     /* 0xcd0 */
    HINDI_INVALID,                                     /* 0xcd1 */
    HINDI_INVALID,                                     /* 0xcd2 */
    HINDI_INVALID,                                     /* 0xcd3 */
    HINDI_INVALID,                                     /* 0xcd4 */
    
    /* VARIOUS SIGNS */
    HINDI_DEPVOW    |   HINDI_SP_RIGHT_POS,            /* KANNADA_ADV_EE = 0xcd5 */
    HINDI_DEPVOW    |   HINDI_SP_RIGHT_POS,            /* KANNADA_ADV_AI = 0xcd6 */

    /* ADDITIONAL CONSONANTS */
    HINDI_INVALID,                                                           /* 0xcd7 */
    HINDI_INVALID,                                                           /* 0xcd8 */
    HINDI_INVALID,                                                           /* 0xcd9 */
    HINDI_INVALID,                                                           /* 0xcda */
    HINDI_INVALID,                                                           /* 0xcdb */
    HINDI_INVALID,                                                           /* 0xcdc */
    HINDI_INVALID,                                                           /* 0xcdd */
    HINDI_CON       |   HINDI_SP_CENTER_T,             /* KANNADA LETTER LLLA = 0xcde */
    HINDI_INVALID,                                                           /* 0xcdf */

    /* ADDITIONAL VOWELS FOR SANSKRIT */
    HINDI_INDVOW    |   HINDI_SP_NO_T,                   /* KANNADA_IV_VRR = 0xce0 */
    HINDI_INDVOW    |   HINDI_SP_NO_T,                   /* KANNADA_IV_VLL = 0xce1 */

    /* DEPENDENT VOWELS */
    HINDI_DEPVOW    |   HINDI_SP_CENTER_T_DOWN_POS,              /* KANNADA VOWEL SIGN VOCALIC L = 0xce2 */
    HINDI_DEPVOW    |   HINDI_SP_CENTER_T_DOWN_POS,              /* KANNADA VOWEL SIGN VOCALIC LL = 0xce3 */

    /* RESERVED */
    HINDI_NUM,                                                               /* KANNADA_S_DANDA = 0xce4 */
    HINDI_NUM,                                                               /* KANNADA_S_DDANDA = 0xce5 */
    
    /*  DIGITS  */
    HINDI_NUM,                                                               /* KANNADA_D_ZERO = 0xce6 */
    HINDI_NUM,                                                               /* KANNADA_D_ONE = 0xce7 */
    HINDI_NUM,                                                               /* KANNADA_D_TWO = 0xce8 */
    HINDI_NUM,                                                               /* KANNADA_D_THREE = 0xce9 */
    HINDI_NUM,                                                               /* KANNADA_D_FOUR = 0xcea */
    HINDI_NUM,                                                               /* KANNADA_D_FIVE = 0xceb */
    HINDI_NUM,                                                               /* KANNADA_D_SIX = 0xcec */
    HINDI_NUM,                                                               /* KANNADA_D_SEVEN = 0xced */
    HINDI_NUM,                                                               /* KANNADA_D_EIGHT = 0xcee */
    HINDI_NUM,                                                               /* KANNADA_D_NINE = 0xcef */

    /* SIGNS USED IN SANSKRIT */
    HINDI_INVALID,                                                           /* 0xcf0 */
    HINDI_SIGN,                                                              /* KANNADA_S_JIH = 0xcf1 */
    HINDI_SIGN,                                                              /* KANNADA_S_UPA = 0xcf2 */

};          

const HindiFeatureRecord_t _g_sKannadaFeatureMap[] = 
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
/*HINDI_FEATURE_BLWS*/  {HINDI_FEATURE_BLWS, _HindiBlwsFeatureMask},
/*HINDI_FEATURE_PSTS*/  {HINDI_FEATURE_PSTS, _HindiPstsFeatureMask},
/*HINDI_FEATURE_HALN*/  {HINDI_FEATURE_HALN, _HindiHalnFeatureMask},
/*HINDI_FEATURE_CALT*/  {HINDI_FEATURE_CALT, _HindiCaltFeatureMask},
/*HINDI_FEATURE_ABVM*/ {HINDI_FEATURE_ABVM, _HindiAbvmFeatureMask},
/*HINDI_FEATURE_BLWM*/ {HINDI_FEATURE_BLWM, _HindiBlwmFeatureMask}
};
const U16 _g_u16KannadaFeatureCount = (sizeof(_g_sKannadaFeatureMap)/sizeof(HindiFeatureRecord_t));

//static U16 _msAPI_MLE_FontKannadaGetCluster( HindiScript_e eScript, const U16 *pu16Txt, U32 u32InLen, U16 *pu16Cluster, U16 u16BufferSize, U16 *pu16ConsumedCount, U16 *pu16SeqInCluster, BOOLEAN bIsDispStr, U32 *pu32FeatureTags );
static BOOLEAN _msAPI_MLE_FontKannadaGetNextCodeXOffset( U16 *pu16CurrentRefChar, U16 *pu16CurrentCharRefWidth, U16 u16NextChar, U16 u16NextCharWidth, S16 *ps16XOffset, U16 u16BaseWidth, U16 u16PreChar, BOOLEAN bFirstCharInCluster );
static BOOLEAN _msAPI_MLE_FontKannadaCharIsRA( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontKannadaCharIsHalant( U16 u16Character );
//static BOOLEAN _msAPI_MLE_FontKannadaCharIsBindu( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontKannadaCharIsNukta( U16 u16Character );
static U16 _msAPI_MLE_FontKannadaGetTwoWordLeftChar( U16 u16Character );
static U16 _msAPI_MLE_FontKannadaGetTwoWordRightChar( U16 u16Character );
static HindiCharacter_e _msAPI_MLE_FontKannadaGetCharType( U16 u16Character );
static HindiSpecialCharacter_e _msAPI_MLE_FontKannadaGetCharSpecialType( U16 u16Character );
//static const HindiMainTable_t* _msAPI_MLE_FontKannadaGetCharRuleTable( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontKannadaCharIsBlwf( U16 u16FirstChar, U16 u16SecondChar );
static BOOLEAN _msAPI_MLE_FontKannadaCharIsPstf( U16 u16FirstChar, U16 u16SecondChar );
static BOOLEAN _msAPI_MLE_FontKannadaCharIsComposed( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontKannadaStrWithAkhand( U16 *pu16Str, U32 u32StrLen, U16 u16Offset );
static U32 _msAPI_MLE_FontKannadaSetFeature( U32 u32FeatureTags, HindiFeature_e eFeature );
static U16 _msAPI_MLE_FontKannadaGetFeatureMap( const HindiFeatureRecord_t **ppasFeatureMap );
static BOOLEAN _msAPI_MLE_FontKannadaFeatureWithRphf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType );
static BOOLEAN _msAPI_MLE_FontKannadaFeatureWithBlwf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType );

__SLDPM_FREE__ const HindiTable_t g_kndaTable =
{
    HINDI_SCRIPT_KNDA,
    KANNADA_S_ANUSVARA,
    KANNADA_S_UPA,
    NULL, //&_msAPI_MLE_FontKannadaGetCluster,
    NULL, //fnRefineCluster
    &_msAPI_MLE_FontKannadaGetNextCodeXOffset,
    &_msAPI_MLE_FontKannadaCharIsRA,
    &_msAPI_MLE_FontKannadaCharIsHalant,
    &_msAPI_MLE_FontKannadaCharIsNukta,
    NULL,//&_FontBengCharIsBindu,
    NULL,//&_FontBengCharWithNukta,
    NULL,//&_FontBengCharIsNoHalfCon,
    NULL,//&_FontBengCharIsFollowingZWJ,
    &_msAPI_MLE_FontKannadaGetTwoWordLeftChar,
    &_msAPI_MLE_FontKannadaGetTwoWordRightChar,
    &_msAPI_MLE_FontKannadaGetCharType,
    &_msAPI_MLE_FontKannadaGetCharSpecialType,
    NULL,//&_FontBengGetCharOtherType,
    &_msAPI_MLE_FontKannadaCharIsBlwf,
    &_msAPI_MLE_FontKannadaCharIsPstf,
    NULL,//&_FontBengCharIsLigated,
    &_msAPI_MLE_FontKannadaStrWithAkhand,
    &_msAPI_MLE_FontKannadaSetFeature,
    &_msAPI_MLE_FontKannadaGetFeatureMap,
    NULL,//&_FontBengCharIsSign,
    &_msAPI_MLE_FontKannadaCharIsComposed,
    &_msAPI_MLE_FontKannadaFeatureWithRphf,
    &_msAPI_MLE_FontKannadaFeatureWithBlwf
};
/*
static U16 _msAPI_MLE_FontKannadaGetCluster( HindiScript_e eScript, const U16 *pu16Txt, U32 u32InLen, U16 *pu16Cluster, U16 u16BufferSize, U16 *pu16ConsumedCount, U16 *pu16SeqInCluster, BOOLEAN bIsDispStr, U32 *pu32FeatureTags )
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
            if( _msAPI_MLE_FontKannadaGetCharType(u16Character) == HINDI_CON )
            {
                u16Index++;
                u16Character = pu16Txt[u16Index];
                if( _msAPI_MLE_FontKannadaCharIsHalant(u16Character) )
                {
                    u16Index++;
                    u16Character = pu16Txt[u16Index];
                    if( _msAPI_MLE_FontKannadaGetCharType(u16Character) == HINDI_CON )
                    {
                        HindiCharacter_e eType = HINDI_INVALID;
                        HindiSpecialCharacter_e eSpType = HINDI_SP_INVALID;
                        u16Index++;
                        u16Character = pu16Txt[u16Index];
                        eType = _msAPI_MLE_FontKannadaGetCharType(u16Character);
                        eSpType = _msAPI_MLE_FontKannadaGetCharSpecialType(u16Character);
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
*/

static BOOLEAN _msAPI_MLE_FontKannadaGetNextCodeXOffset( U16 *pu16CurrentRefChar, U16 *pu16CurrentCharRefWidth, U16 u16NextChar, U16 u16NextCharWidth, S16 *ps16XOffset, U16 u16BaseWidth, U16 u16PreChar, BOOLEAN bFirstCharInCluster )
{
    BOOLEAN bReturn = TRUE;

    u16BaseWidth = u16BaseWidth;
    u16PreChar = u16PreChar;
    bFirstCharInCluster = bFirstCharInCluster;
    
    if ( ps16XOffset == NULL || pu16CurrentRefChar == NULL || pu16CurrentCharRefWidth == NULL )
    {
        return FALSE;
    }

    if( ( IS_KANNADA_RANGE(*pu16CurrentRefChar)) && ( IS_KANNADA_RANGE(u16NextChar)) )
    {
        switch ( _msAPI_MLE_FontKannadaGetCharType(u16NextChar) )
        {
            case HINDI_DEPVOW:
            case HINDI_HALANT:
                if(IS_KANNADA_DEPVOW_RIGHT_JOINER_CHAR(u16NextChar))
                {
                    *ps16XOffset = *ps16XOffset + *pu16CurrentCharRefWidth - (u16NextCharWidth/4);
                    return TRUE;
                }
                else if(IS_KANNADA_DEPVOW_RIGHT_POS_CHAR(u16NextChar))
                {
                    *ps16XOffset = *ps16XOffset + *pu16CurrentCharRefWidth;
                    return TRUE;
                }
                else
                {
                    *ps16XOffset = *ps16XOffset + (*pu16CurrentCharRefWidth - u16NextCharWidth)/2;
                    
                    return TRUE;
                }
            break;
            case HINDI_SIGN:
                    *ps16XOffset = *ps16XOffset + *pu16CurrentCharRefWidth;
                    return TRUE;
            break;
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

static BOOLEAN _msAPI_MLE_FontKannadaCharIsRA( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_KANNADA_RANGE(u16Character) )
    {
        if ( IS_KANNADA_RA_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
    
    return bResult;
}

static BOOLEAN _msAPI_MLE_FontKannadaCharIsHalant( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_KANNADA_RANGE(u16Character) )
    {
        if ( IS_KANNADA_HALANT_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
     
    return bResult;
}

static BOOLEAN _msAPI_MLE_FontKannadaCharIsNukta( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_KANNADA_RANGE(u16Character) )
    {
        if ( IS_KANNADA_NUKTA_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
     
    return bResult;
}

/*
static BOOLEAN _msAPI_MLE_FontKannadaCharIsBindu( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_KANNADA_RANGE(u16Character) )
    {
    
        if ( IS_KANNADA_BINDU_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
        
    }
     
    return bResult;
}
*/

static U16 _msAPI_MLE_FontKannadaGetTwoWordLeftChar( U16 u16Character )
{
    U16 u16ReturnChar = 0;

    if ( IS_KANNADA_RANGE(u16Character) && _msAPI_MLE_FontKannadaGetCharSpecialType(u16Character) == HINDI_SP_TWOPART_JOINER )
    {
        if ( u16Character == KANNADA_DV_AI )
        {
            u16ReturnChar = KANNADA_DV_E;
        }
        else if ( u16Character == KANNADA_DV_EE )
        {
            u16ReturnChar = KANNADA_DV_E;
        }
        else if ( u16Character == KANNADA_DV_II )
        {
            u16ReturnChar = KANNADA_DV_I;
        }
        else if ( u16Character == KANNADA_DV_O )
        {
            u16ReturnChar = KANNADA_DV_E;
        }
        else if ( u16Character == KANNADA_DV_OO )
        {
            u16ReturnChar = KANNADA_DV_O;
        }        
    }
    
    return u16ReturnChar;
}

static U16 _msAPI_MLE_FontKannadaGetTwoWordRightChar( U16 u16Character )
{
    U16 u16ReturnChar = 0;

    if ( IS_KANNADA_RANGE(u16Character) && _msAPI_MLE_FontKannadaGetCharSpecialType(u16Character) == HINDI_SP_TWOPART_JOINER )
    {
        if ( u16Character == KANNADA_DV_AI )
        {
            u16ReturnChar = KANNADA_ADV_AI;
        }
        else if ( u16Character == KANNADA_DV_EE )
        {
            u16ReturnChar = KANNADA_ADV_EE;
        }
        else if ( u16Character == KANNADA_DV_II )
        {
            u16ReturnChar = KANNADA_ADV_EE;
        }
        else if ( u16Character == KANNADA_DV_O )
        {
            u16ReturnChar = KANNADA_DV_UU;
        }
        else if ( u16Character == KANNADA_DV_OO )
        {
            u16ReturnChar = KANNADA_ADV_EE;
        }        
    }
    
    return u16ReturnChar;
}

static HindiCharacter_e _msAPI_MLE_FontKannadaGetCharType( U16 u16Character )
{
    HindiCharacter_e eType = HINDI_INVALID;
    
    if ( IS_KANNADA_RANGE(u16Character) )
    {
        eType = (g_KannadaCharTypeArray[u16Character - KANNADA_MASK]) & 0x0F;
    }
         
    return eType;
}

static HindiSpecialCharacter_e _msAPI_MLE_FontKannadaGetCharSpecialType( U16 u16Character )
{
    HindiSpecialCharacter_e eType = HINDI_SP_INVALID;

    if ( IS_KANNADA_RANGE(u16Character) )
    {
        eType = (g_KannadaCharTypeArray[u16Character - KANNADA_MASK]) & 0xF0;
    }

    return eType;
}
     
static BOOLEAN _msAPI_MLE_FontKannadaCharIsComposed( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_KANNADA_RANGE(u16Character) )
    {
        if ( IS_KANNADA_DEPVOW_COMPOSING_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
 
    return bResult;
}

static BOOLEAN _msAPI_MLE_FontKannadaCharIsBlwf( U16 u16FirstChar, U16 u16SecondChar )
{
    BOOLEAN bResult = FALSE;

    if ( IS_KANNADA_RANGE(u16FirstChar) && IS_KANNADA_RANGE(u16SecondChar) )
    {
        if ( IS_KANNADA_HALANT_CHAR(u16FirstChar) )
        {
#if 0
            switch( u16SecondChar )
            {
            case KANNADA_C_KHA:
            case KANNADA_C_GA:
            case KANNADA_C_GHA:
            case KANNADA_C_NGA:
            case KANNADA_C_JA:
            case KANNADA_C_JHA:
            case KANNADA_C_NYA:
            case KANNADA_C_TTA:
            case KANNADA_C_TTHA:
            case KANNADA_C_DDA:
            case KANNADA_C_DDHA:
            case KANNADA_C_NNA:
            case KANNADA_C_TA:
            case KANNADA_C_THA:
            case KANNADA_C_DA:
            case KANNADA_C_DHA:
            case KANNADA_C_RA:
            case KANNADA_C_RRA:
            case KANNADA_C_LA:
            case KANNADA_C_SSA:
            case KANNADA_C_HA:
                
            case KANNADA_C_KA:
            case KANNADA_C_CA:
            case KANNADA_C_CHA:
            case KANNADA_C_NA:
            case KANNADA_C_PA:
            case KANNADA_C_PHA:
            case KANNADA_C_BA:
            case KANNADA_C_BHA:
            case KANNADA_C_MA:
            case KANNADA_C_YA:
            case KANNADA_C_LLA:
            case KANNADA_C_VA:
            case KANNADA_C_SHA:
            case KANNADA_C_SA:
                bResult = TRUE;
                break;
            default:
                break;
            }
#else
            if ( IS_KANNADA_CONSONANT(u16SecondChar) )
            {
                bResult = TRUE;
            }
#endif
        }
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_FontKannadaCharIsPstf( U16 u16FirstChar, U16 u16SecondChar )
{
    BOOLEAN bResult = FALSE;

    if ( IS_KANNADA_RANGE(u16FirstChar) && IS_KANNADA_RANGE(u16SecondChar) )
    {
        if ( IS_KANNADA_HALANT_CHAR(u16FirstChar) )
        {
            switch( u16SecondChar )
            {

//                bResult = TRUE;
//                break;
            default:
                break;
            }
        }
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_FontKannadaStrWithAkhand( U16 *pu16Str, U32 u32StrLen, U16 u16Offset )
{
    BOOLEAN bResult = FALSE;

    if ( IS_KANNADA_RANGE(pu16Str[u16Offset]) )
    {
        if ( (u32StrLen - u16Offset) > 2 )
        {
            if ( pu16Str[u16Offset] == KANNADA_C_KA && pu16Str[u16Offset+1] == KANNADA_S_HALANT && pu16Str[u16Offset+2] == KANNADA_C_SSA )
            {
                bResult = TRUE;
            }
            else if ( pu16Str[u16Offset] == KANNADA_C_JA && pu16Str[u16Offset+1] == KANNADA_S_HALANT && pu16Str[u16Offset+2] == KANNADA_C_NYA )
            {
                bResult = TRUE;
            }
        }
    }
    
    return bResult;
}

static U32 _msAPI_MLE_FontKannadaSetFeature( U32 u32FeatureTags, HindiFeature_e eFeature )
{
    U16 i;
    for ( i = 0; i < _g_u16KannadaFeatureCount; i++ )
    {
        if ( _g_sKannadaFeatureMap[i].eTag == eFeature )
        {
            u32FeatureTags = u32FeatureTags | _g_sKannadaFeatureMap[i].u32Mask;
            break;
        }
    }
    return u32FeatureTags;
}

static U16 _msAPI_MLE_FontKannadaGetFeatureMap( const HindiFeatureRecord_t **ppasFeatureMap )
{
    *ppasFeatureMap = _g_sKannadaFeatureMap;
    return (U16)_g_u16KannadaFeatureCount;
}

static BOOLEAN _msAPI_MLE_FontKannadaFeatureWithRphf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType )
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

static BOOLEAN _msAPI_MLE_FontKannadaFeatureWithBlwf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType )
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

BOOLEAN msAPI_MLE_FontKannadaCharIsBeforeSubscript( U16 u16Character )
{
    BOOLEAN bRet = FALSE;

    switch(u16Character)
    {
    case KANNADA_DV_I:
    case KANNADA_DV_E:
    case KANNADA_DV_AU:
    case KANNADA_DV_AA:
    case KANNADA_DV_VL:
    case KANNADA_DV_VLL:
    case KANNADA_DV_U:
    case KANNADA_DV_UU:
        bRet = TRUE;
        break;
    default:
        break;
    }

    return bRet;
}

#endif //__KANNADA_FONT__
#endif //__INDIC_FONT__


