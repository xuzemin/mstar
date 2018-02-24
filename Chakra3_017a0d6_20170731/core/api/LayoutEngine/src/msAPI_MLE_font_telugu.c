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

#ifdef __TELUGU_FONT__
#include "msAPI_MLE_font_telugu.h"

/*------------------------------------------------------------------------------------------
*
*                                                                                     MACRO DEFINE
*
-------------------------------------------------------------------------------------------*/

const U8 g_TeluguCharTypeArray[] =
{
    HINDI_INVALID,
        
    /* VARIOUS SIGNS */
    HINDI_SIGN      |   HINDI_SP_RIGHT_POS,        /* TELUGU_S_CHANDRA_BINDU = 0xc01 */
    HINDI_SIGN      |   HINDI_SP_RIGHT_POS,        /* TELUGU_S_ANUSVARA = 0xc02 */
    HINDI_SIGN      |   HINDI_SP_RIGHT_POS,        /* TELUGU_S_VISARGA = 0xc03 */
    HINDI_INVALID,     /* 0xc04 */
    
    /* INDEPENDENT VOWEL */
    HINDI_INDVOW    |   HINDI_SP_NO_T,      /* TELUGU_IV_A = 0xc05 */
    HINDI_INDVOW    |   HINDI_SP_NO_T,      /* TELUGU_IV_AA = 0xc06 */
    HINDI_INDVOW    |   HINDI_SP_NO_T,      /* TELUGU_IV_I = 0xc07 */
    HINDI_INDVOW    |   HINDI_SP_NO_T,      /* TELUGU_IV_II = 0xc08 */
    HINDI_INDVOW    |   HINDI_SP_NO_T,      /* TELUGU_IV_U = 0xc09 */
    HINDI_INDVOW    |   HINDI_SP_NO_T,      /* TELUGU_IV_UU = 0xc0a */
    HINDI_INDVOW    |   HINDI_SP_NO_T,      /* TELUGU_IV_VR = 0xc0b */
    HINDI_INDVOW    |   HINDI_SP_NO_T,      /* TELUGU_IV_VL = 0xc0c */
    HINDI_INVALID,                                       /* 0xc0d */
    HINDI_INDVOW    |   HINDI_SP_NO_T,      /* TELUGU_IV_E = 0xc0e */
    HINDI_INDVOW    |   HINDI_SP_NO_T,      /* TELUGU_IV_EE = 0xc0f */
    HINDI_INDVOW    |   HINDI_SP_NO_T,      /* TELUGU_IV_AI = 0xc10 */
    HINDI_INVALID,                                       /* 0xc11 */
    HINDI_INDVOW    |   HINDI_SP_NO_T,      /* TELUGU_IV_O = 0xc12 */
    HINDI_INDVOW    |   HINDI_SP_NO_T,      /* TELUGU_IV_OO = 0xc13 */
    HINDI_INDVOW    |   HINDI_SP_NO_T,      /* TELUGU_IV_AU = 0xc14 */
    
    /*  CONSONANTS  */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_KA = 0xc15 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_KHA = 0xc16 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_GA = 0xc17 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_GHA = 0xc18 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_NGA = 0xc19 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_CA = 0xc1a */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_CHA = 0xc1b */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_JA = 0xc1c */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_JHA = 0xc1d */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_NYA = 0xc1e */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_TTA = 0xc1f */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_TTHA = 0xc20 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_DDA = 0xc21 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_DDHA = 0xc22 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_NNA = 0xc23 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_TA = 0xc24 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_THA = 0xc25 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_DA = 0xc26 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_DHA = 0xc27 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_NA = 0xc28 */
    HINDI_INVALID,     /* 0xc29 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_PA = 0xc2a */
    HINDI_CON       ,         /* TELUGU_C_PHA = 0xc2b */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_BA = 0xc2c */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_BHA = 0xc2d */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_MA = 0xc2e */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_YA = 0xc2f */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_RA = 0xc30 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_RRA = 0xc31 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_LA = 0xc32 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_LLA = 0xc33 */
    HINDI_INVALID,     /* 0xc34 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_VA = 0xc35 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_SHA = 0xc36 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_SSA = 0xc37 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_SA = 0xc38 */
    HINDI_CON       |   HINDI_SP_CENTER_T,         /* TELUGU_C_HA = 0xc39 */
    
    /*  DEPENDENT VOWELS  */
    HINDI_INVALID,     /* 0xc3a */
    HINDI_INVALID,     /* 0xc3b */
    HINDI_INVALID,     /* 0xc3c */
    HINDI_INVALID,     /* 0xc3d */
    HINDI_DEPVOW    |   HINDI_SP_CENTER_T_UP_POS,      /* TELUGU_DV_AA = 0xc3e */
    HINDI_DEPVOW    |   HINDI_SP_CENTER_T_UP_POS,      /* TELUGU_DV_I = 0xc3f */
    HINDI_DEPVOW    |   HINDI_SP_CENTER_T_UP_POS,      /* TELUGU_DV_II = 0xc40 */
    HINDI_DEPVOW    |   HINDI_SP_RIGHT_JOINER,         /* TELUGU_DV_U = 0xc41 */
    HINDI_DEPVOW    |   HINDI_SP_RIGHT_JOINER,         /* TELUGU_DV_UU = 0xc42 */
    HINDI_DEPVOW    |   HINDI_SP_RIGHT_POS,                /* TELUGU_DV_VR = 0xc43 */
    HINDI_DEPVOW    |   HINDI_SP_RIGHT_POS,                /* TELUGU_DV_VRR = 0xc44 */
    HINDI_INVALID,                                                      /* 0xc45 */
    HINDI_DEPVOW    |   HINDI_SP_CENTER_T_UP_POS,      /* TELUGU_DV_E = 0xc46 */
    HINDI_DEPVOW    |   HINDI_SP_CENTER_T_UP_POS,      /* TELUGU_DV_EE = 0xc47 */
    HINDI_DEPVOW    |   HINDI_SP_TWOPART_JOINER,         /* TELUGU_DV_AI = 0xc48 */
    HINDI_INVALID,     /* 0xc49 */
    HINDI_DEPVOW    |   HINDI_SP_CENTER_T_UP_POS,      /* TELUGU_DV_O = 0xc4a */
    HINDI_DEPVOW    |   HINDI_SP_CENTER_T_UP_POS,      /* TELUGU_DV_OO = 0xc4b */
    HINDI_DEPVOW    |   HINDI_SP_CENTER_T_UP_POS,      /* TELUGU_DV_AU = 0xc4c */
    HINDI_HALANT,                                                        /* TELUGU_S_HALANT = 0xc4d */
    HINDI_INVALID,                                                       /* 0xc4e */
    HINDI_INVALID,                                                       /* 0xc4f */
    HINDI_INVALID,                                                           /* 0xc50 */
    HINDI_INVALID,                                                           /* 0xc51 */
    HINDI_INVALID,                                                           /* 0xc52 */
    HINDI_INVALID,                                                           /* 0xc53 */
    HINDI_INVALID,                                                           /* 0xc54 */
    HINDI_DEPVOW    |   HINDI_SP_CENTER_T_UP_POS,      /* TELUGU_ADV_EE = 0xc55 */
    HINDI_DEPVOW    |   HINDI_SP_CENTER_T_DOWN_POS,      /* TELUGU_ADV_AI = 0xc56 */
    HINDI_INVALID,                                                           /* 0xc57 */
    HINDI_INVALID,                                                           /* 0xc58 */
    HINDI_INVALID,                                                           /* 0xc59 */
    HINDI_INVALID,                                                       /* 0xc5a */
    HINDI_INVALID,                                                           /* 0xc5b */
    HINDI_INVALID,                                                           /* 0xc5c */
    HINDI_INVALID,                                                           /* 0xc5d */
    HINDI_INVALID,                                                           /* 0xc5e */
    HINDI_INVALID,                                                           /* 0xc5f */
    HINDI_INDVOW    |   HINDI_SP_NO_T,                          /* TELUGU_IV_VRR = 0xc60 */
    HINDI_INDVOW    |   HINDI_SP_NO_T,                          /* TELUGU_IV_VLL = 0xc61 */
    HINDI_DEPVOW    |   HINDI_SP_CENTER_T_DOWN_POS,      /* 0xc62 */
    HINDI_DEPVOW    |   HINDI_SP_CENTER_T_DOWN_POS,      /* 0xc63 */
    HINDI_NUM,                                                               /* TELUGU_S_DANDA = 0xc64 */
    HINDI_NUM,                                                               /* TELUGU_S_DDANDA = 0xc65 */
    
    /*  DIGITS  */
    HINDI_NUM,                                                               /* TELUGU_D_ZERO = 0xc66 */
    HINDI_NUM,                                                               /* TELUGU_D_ONE = 0xc67 */
    HINDI_NUM,                                                               /* TELUGU_D_TWO = 0xc68 */
    HINDI_NUM,                                                               /* TELUGU_D_THREE = 0xc69 */
    HINDI_NUM,                                                               /* TELUGU_D_FOUR = 0xc6a */
    HINDI_NUM,                                                               /* TELUGU_D_FIVE = 0xc6b */
    HINDI_NUM,                                                               /* TELUGU_D_SIX = 0xc6c */
    HINDI_NUM,                                                               /* TELUGU_D_SEVEN = 0xc6d */
    HINDI_NUM,                                                               /* TELUGU_D_EIGHT = 0xc6e */
    HINDI_NUM,                                                               /* TELUGU_D_NINE = 0xc6f */
};          

const HindiFeatureRecord_t _g_sTeluguFeatureMap[] = 
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
const U16 _g_u16TeluguFeatureCount = (sizeof(_g_sTeluguFeatureMap)/sizeof(HindiFeatureRecord_t));

static BOOLEAN _msAPI_MLE_FontTeluguGetNextCodeXOffset( U16 *pu16CurrentRefChar, U16 *pu16CurrentCharRefWidth, U16 u16NextChar, U16 u16NextCharWidth, S16 *ps16XOffset, U16 u16BaseWidth, U16 u16PreChar, BOOLEAN bFirstCharInCluster );
#if 0
static BOOLEAN _msAPI_MLE_FontTeluguCharIsRA( U16 u16Character );
#endif
static BOOLEAN _msAPI_MLE_FontTeluguCharIsHalant( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontTeluguCharIsBindu( U16 u16Character );
static U16 _msAPI_MLE_FontTeluguGetTwoWordLeftChar( U16 u16Character );
static U16 _msAPI_MLE_FontTeluguGetTwoWordRightChar( U16 u16Character );
static HindiCharacter_e _msAPI_MLE_FontTeluguGetCharType( U16 u16Character );
static HindiSpecialCharacter_e _msAPI_MLE_FontTeluguGetCharSpecialType( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontTeluguCharIsBlwf( U16 u16FirstChar, U16 u16SecondChar );
static BOOLEAN _msAPI_MLE_FontTeluguCharIsPstf( U16 u16FirstChar, U16 u16SecondChar );
static BOOLEAN _msAPI_MLE_FontTeluguCharIsComposed( U16 u16Character );
static BOOLEAN _msAPI_MLE_FontTeluguStrWithAkhand( U16 *pu16Str, U32 u32StrLen, U16 u16Offset );
static U32 _msAPI_MLE_FontTeluguSetFeature( U32 u32FeatureTags, HindiFeature_e eFeature );
static U16 _msAPI_MLE_FontTeluguGetFeatureMap( const HindiFeatureRecord_t **ppasFeatureMap );
static BOOLEAN _msAPI_MLE_FontTeluguFeatureWithRphf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType );
static BOOLEAN _msAPI_MLE_FontTeluguFeatureWithBlwf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType );

__SLDPM_FREE__ const HindiTable_t g_teluTable =
{
    HINDI_SCRIPT_TELU,
    TELUGU_S_CHANDRA_BINDU,
    TELUGU_D_NINE,
    NULL, //fnGetCluster
    NULL, //fnRefineCluster
    &_msAPI_MLE_FontTeluguGetNextCodeXOffset,
    NULL, //&_msAPI_MLE_FontTeluguCharIsRA,
    &_msAPI_MLE_FontTeluguCharIsHalant,
    NULL,//&_FontBengCharIsNukta,
    &_msAPI_MLE_FontTeluguCharIsBindu,
    NULL,//&_FontBengCharWithNukta,
    NULL,//&_FontBengCharIsNoHalfCon,
    NULL,//&_FontBengCharIsFollowingZWJ,
    &_msAPI_MLE_FontTeluguGetTwoWordLeftChar,
    &_msAPI_MLE_FontTeluguGetTwoWordRightChar,
    &_msAPI_MLE_FontTeluguGetCharType,
    &_msAPI_MLE_FontTeluguGetCharSpecialType,
    NULL,//&_FontBengGetCharOtherType,
    &_msAPI_MLE_FontTeluguCharIsBlwf,
    &_msAPI_MLE_FontTeluguCharIsPstf,
    NULL,//&_FontBengCharIsLigated,
    &_msAPI_MLE_FontTeluguStrWithAkhand,
    &_msAPI_MLE_FontTeluguSetFeature,
    &_msAPI_MLE_FontTeluguGetFeatureMap,
    NULL,//&_FontBengCharIsSign,
    &_msAPI_MLE_FontTeluguCharIsComposed,
    &_msAPI_MLE_FontTeluguFeatureWithRphf,
    &_msAPI_MLE_FontTeluguFeatureWithBlwf
};

static BOOLEAN _msAPI_MLE_FontTeluguGetNextCodeXOffset( U16 *pu16CurrentRefChar, U16 *pu16CurrentCharRefWidth, U16 u16NextChar, U16 u16NextCharWidth, S16 *ps16XOffset, U16 u16BaseWidth, U16 u16PreChar, BOOLEAN bFirstCharInCluster )
{
    BOOLEAN bReturn = TRUE;

    u16BaseWidth = u16BaseWidth;
    u16PreChar = u16PreChar;
    bFirstCharInCluster = bFirstCharInCluster;
    
    if ( ps16XOffset == NULL || pu16CurrentRefChar == NULL || pu16CurrentCharRefWidth == NULL )
    {
        return FALSE;
    }

    if( ( IS_TELUGU_RANGE(*pu16CurrentRefChar) ) 
        && ( IS_TELUGU_RANGE(u16NextChar) ))
    {
        switch ( _msAPI_MLE_FontTeluguGetCharType(u16NextChar) )
        {
            case HINDI_DEPVOW:
            case HINDI_HALANT:
                if(IS_TELUGU_DEPVOW_RIGHT_JOINER_CHAR(u16NextChar))
                {
                    *ps16XOffset = *ps16XOffset + *pu16CurrentCharRefWidth - (u16NextCharWidth/4);
                    return TRUE;
                }
                else if(IS_TELUGU_DEPVOW_RIGHT_POS_CHAR(u16NextChar))
                {
                    *ps16XOffset = *ps16XOffset + *pu16CurrentCharRefWidth;
                    return TRUE;
                }
                else
                {
                    *ps16XOffset = *ps16XOffset + (*pu16CurrentCharRefWidth - u16NextCharWidth)/2;
                    
                    return TRUE;
                }

            case HINDI_SIGN:
                    *ps16XOffset = *ps16XOffset + *pu16CurrentCharRefWidth;
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
static BOOLEAN _msAPI_MLE_FontTeluguCharIsRA( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_TELUGU_RANGE(u16Character) )
    {
        if ( IS_TELUGU_RA_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
    
    return bResult;
}
#endif
static BOOLEAN _msAPI_MLE_FontTeluguCharIsHalant( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_TELUGU_RANGE(u16Character) )
    {
        if ( IS_TELUGU_HALANT_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
     
    return bResult;
}

static BOOLEAN _msAPI_MLE_FontTeluguCharIsBindu( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_TELUGU_RANGE(u16Character) )
    {
        if ( IS_TELUGU_BINDU_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
     
    return bResult;
}

static U16 _msAPI_MLE_FontTeluguGetTwoWordLeftChar( U16 u16Character )
{
    U16 u16ReturnChar = 0;

    if ( IS_TELUGU_RANGE(u16Character) && _msAPI_MLE_FontTeluguGetCharSpecialType(u16Character) == HINDI_SP_TWOPART_JOINER )
    {
        if ( u16Character == TELUGU_DV_AI )
        {
            u16ReturnChar = TELUGU_DV_E;
        }
    }
    
    return u16ReturnChar;
}

static U16 _msAPI_MLE_FontTeluguGetTwoWordRightChar( U16 u16Character )
{
    U16 u16ReturnChar = 0;

    if ( IS_TELUGU_RANGE(u16Character) && _msAPI_MLE_FontTeluguGetCharSpecialType(u16Character) == HINDI_SP_TWOPART_JOINER )
    {
        if ( u16Character == TELUGU_DV_AI )
        {
            u16ReturnChar = TELUGU_ADV_AI;
        }
    }
    
    return u16ReturnChar;
}

static HindiCharacter_e _msAPI_MLE_FontTeluguGetCharType( U16 u16Character )
{
    HindiCharacter_e eType = HINDI_INVALID;

    if ( IS_TELUGU_RANGE(u16Character) )
    {
        eType = (g_TeluguCharTypeArray[u16Character - TELUGU_MASK]) & 0x0F;
    }
         
    return eType;
}

static HindiSpecialCharacter_e _msAPI_MLE_FontTeluguGetCharSpecialType( U16 u16Character )
{
    HindiSpecialCharacter_e eType = HINDI_SP_INVALID;

    if ( IS_TELUGU_RANGE(u16Character) )
    {
        eType = (g_TeluguCharTypeArray[u16Character - TELUGU_MASK]) & 0xF0;
    }

    return eType;
}

static BOOLEAN _msAPI_MLE_FontTeluguCharIsComposed( U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( IS_TELUGU_RANGE(u16Character) )
    {
        if ( IS_TELUGU_DEPVOW_COMPOSING_CHAR(u16Character) )
        {
            bResult = TRUE;
        }
    }
 
    return bResult;
}

static BOOLEAN _msAPI_MLE_FontTeluguCharIsBlwf( U16 u16FirstChar, U16 u16SecondChar )
{
    BOOLEAN bResult = FALSE;

    if ( IS_TELUGU_RANGE(u16FirstChar) && IS_TELUGU_RANGE(u16SecondChar) )
    {
        if ( IS_TELUGU_HALANT_CHAR(u16FirstChar) )
        {
#if 0
            switch( u16SecondChar )
            {
            case TELUGU_C_KHA:
            case TELUGU_C_GA:
            case TELUGU_C_GHA:
            case TELUGU_C_NGA:
            case TELUGU_C_JA:
            case TELUGU_C_JHA:
            case TELUGU_C_NYA:
            case TELUGU_C_TTA:
            case TELUGU_C_TTHA:
            case TELUGU_C_DDA:
            case TELUGU_C_DDHA:
            case TELUGU_C_NNA:
            case TELUGU_C_TA:
            case TELUGU_C_THA:
            case TELUGU_C_DA:
            case TELUGU_C_DHA:
            case TELUGU_C_RA:
            case TELUGU_C_RRA:
            case TELUGU_C_LA:
            case TELUGU_C_SSA:
            case TELUGU_C_HA:
                
            case TELUGU_C_KA:
            case TELUGU_C_CA:
            case TELUGU_C_CHA:
            case TELUGU_C_NA:
            case TELUGU_C_PA:
            case TELUGU_C_PHA:
            case TELUGU_C_BA:
            case TELUGU_C_BHA:
            case TELUGU_C_MA:
            case TELUGU_C_YA:
            case TELUGU_C_LLA:
            case TELUGU_C_VA:
            case TELUGU_C_SHA:
            case TELUGU_C_SA:
                bResult = TRUE;
                break;
            default:
                break;
            }
#else
            if ( IS_TELUGU_CONSONANT(u16SecondChar) )
            {
                bResult = TRUE;
            }
#endif
        }
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_FontTeluguCharIsPstf( U16 u16FirstChar, U16 u16SecondChar )
{
    BOOLEAN bResult = FALSE;

    if ( IS_TELUGU_RANGE(u16FirstChar) && IS_TELUGU_RANGE(u16SecondChar) )
    {
        if ( IS_TELUGU_HALANT_CHAR(u16FirstChar) )
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

static BOOLEAN _msAPI_MLE_FontTeluguStrWithAkhand( U16 *pu16Str, U32 u32StrLen, U16 u16Offset )
{
    BOOLEAN bResult = FALSE;

    if ( IS_TELUGU_RANGE(pu16Str[u16Offset]) )
    {
        if ( (u32StrLen - u16Offset) > 2 )
        {
            if ( pu16Str[u16Offset] == TELUGU_C_KA && pu16Str[u16Offset+1] == TELUGU_S_HALANT && pu16Str[u16Offset+2] == TELUGU_C_SSA )
            {
                bResult = TRUE;
            }
            else if ( pu16Str[u16Offset] == TELUGU_C_SSA && pu16Str[u16Offset+1] == TELUGU_S_HALANT && pu16Str[u16Offset+2] == TELUGU_C_JA )
            {
                bResult = TRUE;
            }
        }
    }
    
    return bResult;
}

static U32 _msAPI_MLE_FontTeluguSetFeature( U32 u32FeatureTags, HindiFeature_e eFeature )
{
    U16 i;
    for ( i = 0; i < _g_u16TeluguFeatureCount; i++ )
    {
        if ( _g_sTeluguFeatureMap[i].eTag == eFeature )
        {
            u32FeatureTags = u32FeatureTags | _g_sTeluguFeatureMap[i].u32Mask;
            break;
        }
    }
    return u32FeatureTags;
}

static U16 _msAPI_MLE_FontTeluguGetFeatureMap( const HindiFeatureRecord_t **ppasFeatureMap )
{
    *ppasFeatureMap = _g_sTeluguFeatureMap;
    return (U16)_g_u16TeluguFeatureCount;
}

static BOOLEAN _msAPI_MLE_FontTeluguFeatureWithRphf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType )
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

static BOOLEAN _msAPI_MLE_FontTeluguFeatureWithBlwf( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType )
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

#endif //__TELUGU_FONT__
#endif //__INDIC_FONT__

