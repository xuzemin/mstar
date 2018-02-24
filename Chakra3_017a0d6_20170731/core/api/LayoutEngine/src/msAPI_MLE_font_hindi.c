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
#include "msAPI_MLE_font_vector.h"
#include "msAPI_MLE_le.h"

#include "msAPI_MLE_font_hindi_priv.h"
#include "msAPI_MLE_font_devanagari.h"
#include "msAPI_MLE_font_bengali.h"
#include "msAPI_MLE_font_telugu.h"
#include "msAPI_MLE_font_malayalam.h"
#include "msAPI_MLE_font_kannada.h"
#include "msAPI_MLE_font_punjabi.h"
#include "msAPI_MLE_font_myanmar.h"
#include "msAPI_MLE_font_khmer.h"
#include "msAPI_MLE_font_laoo.h"

#define CHAR_DOTTED_CIRCLE 0x25CC

extern const HindiTable_t g_dvngTable;
extern const HindiTable_t g_bengTable;
extern const HindiTable_t g_gujrTable;
extern const HindiTable_t g_tamilTable;
extern const HindiTable_t g_teluTable;
extern const HindiTable_t g_mlymTable;
extern const HindiTable_t g_kndaTable;
extern const HindiTable_t g_punjTable;
extern const HindiTable_t g_mymrTable;
extern const HindiTable_t g_mymrExtATable;
extern const HindiTable_t g_mymrExtBTable;
extern const HindiTable_t g_khmrTable;
extern const HindiTable_t g_khmrDigit1Table;
extern const HindiTable_t g_khmrDigit2Table;
extern const HindiTable_t g_khmrSymbolsTable;
#if(KHMER_SPECIAL_CHARACTER)
extern const HindiTable_t g_SpecialSymbolsTable;
#endif
extern const HindiTable_t g_laooTable;

const HindiTable_t *g_pHindiLangsTbl[] =
{
#ifdef __DVNG_FONT__
    &g_dvngTable,
#endif //__DVNG_FONT__

#ifdef __BENGALI_FONT__
    &g_bengTable,
#endif //__BENGALI_FONT__

#ifdef __TELUGU_FONT__
    &g_teluTable,
#endif //__TELUGU_FONT__

#ifdef __TAMIL_FONT__
    &g_tamilTable,
#endif //__TAMIL_FONT__

#ifdef __GUJR_FONT__
    &g_gujrTable,
#endif //__TAMIL_FONT__

#ifdef __MLYM_FONT__
    &g_mlymTable,
#endif //__MLYM_FONT__

#ifdef __KNDA_FONT__
    &g_kndaTable,
#endif //__KNDA_FONT__

#ifdef __PUNJ_FONT__
    &g_punjTable,
#endif //__PUNJ_FONT__

#ifdef __MYMR_FONT__
    &g_mymrTable,
    &g_mymrExtATable,
    &g_mymrExtBTable,
#endif //__MYMR_FONT__

#ifdef __KHMR_FONT__
    &g_khmrTable,
    &g_khmrDigit1Table,
    &g_khmrDigit2Table,
    &g_khmrSymbolsTable,
#if(KHMER_SPECIAL_CHARACTER)
    &g_SpecialSymbolsTable,
#endif
#endif//__KHMR_FONT__

#ifdef __LAOO_FONT__
    &g_laooTable,
#endif//__LAOO_FONT__

    NULL
};

static U16 msAPI_MLE_FontHindiGetPreCon( HindiScript_e eScript, U16 *pu16Cluster, U16 u16ClusterSize, U16 u16Offset, U16 *pu16PreOffset );

//static U16 _msAPI_MLE_FontHindiGetConsonantCluster( HindiScript_e eScript, const U16 *pu16Txt, U32 u32InLen, U16 u16ConsumedCount, U16 u16Character, U16 *pu16Cluster, U16 u16BufferSize, U16 *pu16ClusterSize, U16 *pu16SeqInCluster, U32 *pu32FeatureTags );
static U16 _msAPI_MLE_FontHindiReorderCluster( HindiScript_e eScript, const U16 *pu16Txt, U32 u32InLen, U16 u16ConsumedCount, U16 *pu16Cluster, U16 u16BufferSize, U16 *pu16ClusterSize, U16 u16CharType, U16 *pu16SeqInCluster, U32 *pu32FeatureTags );
static void _msAPI_MLE_FontHindiSwapRaHalantStr( HindiScript_e eScript, const U16 *pu16Txt, U32 u32InLen, U16 u16ConsumedCount, U16 *pu16Cluster, U16 u16BufferSize, U16 *pu16ClusterSize, U16 *pu16SeqInCluster, U32 *pu32FeatureTags );
static U16 _msAPI_MLE_FontHindiGetIndexInSequence(const U16 *pu16SeqPos, U16 u16SeqSize, U16 u16StrOffset );

static BOOLEAN _msAPI_MLE_FontHindiCharIsRA( HindiScript_e eScript, U16 u16Char );
static BOOLEAN _msAPI_MLE_FontHindiCharIsHalant( HindiScript_e eScript, U16 u16Character );
static BOOLEAN _msAPI_MLE_FontHindiCharIsNukta( HindiScript_e eScript, U16 u16Character );
static BOOLEAN _msAPI_MLE_FontHindiCharIsBindu( HindiScript_e eScript, U16 u16Character );
static BOOLEAN _msAPI_MLE_FontHindiCharWithNukta( HindiScript_e eScript, U16 u16Character );
static BOOLEAN _msAPI_MLE_FontHindiCharIsNoHalfCon( HindiScript_e eScript, U16 u16Character );
static BOOLEAN _msAPI_MLE_FontHindiCharIsFollowingZWJ( HindiScript_e eScript, U16 u16Character );
static U16 _msAPI_MLE_FontHindiGetTwoWordLeftChar( HindiScript_e eScript, U16 u16Character );
static U16 _msAPI_MLE_FontHindiGetTwoWordRightChar( HindiScript_e eScript, U16 u16Character );
static HindiCharacter_e _msAPI_MLE_FontHindiGetCharType( HindiScript_e eScript, U16 u16Character );
static HindiSpecialCharacter_e _msAPI_MLE_FontHindiGetCharSpecialType( HindiScript_e eScript, U16 u16Character );
static HindiOtherCharacterType_e _msAPI_MLE_FontHindiGetCharOtherType( HindiScript_e eScript, U16 u16Character );
static BOOLEAN _msAPI_MLE_FontHindiCharIsPstf( HindiScript_e eScript, U16 u16FirstChar, U16 u16SecondChar );
static BOOLEAN _msAPI_MLE_FontHindiCharIsLigated( HindiScript_e eScript, U16 u16FirstChar, U16 u16SecondChar, BOOLEAN withZWJ );
static BOOLEAN _msAPI_MLE_FontHindiStrWithAkhand( HindiScript_e eScript, U16 *pu16Str, U32 u32StrLen, U16 u16Offset );
static U32 _msAPI_MLE_FontHindiSetFeature( HindiScript_e eScript, U32 u32FeatureTags, HindiFeature_e eFeature );
//static U32 _msAPI_MLE_FontHindiRemoveFeature( HindiScript_e eScript, U32 u32FeatureTags, HindiFeature_e eFeature );

#ifdef __FEATURE_VECTOR_FONT__
static U16 _msAPI_MLE_FontHindiVectorRules( HindiScript_e eScript, LE_LanguageTag_e eLang, U16 *pu16Cluster, U16 u16ClusterSize, U16 u16ClustIndex, U16 *pu16Glyph, U16 *pu16OffsetInConcatenation, U16 *pu16OffsetInComposed, U16 *pu16ConcatenationComposedSize, U32 *pu32Features );
static BOOLEAN _msAPI_MLE_FontHindiCharIsBlwf( HindiScript_e eScript, U16 u16FirstChar, U16 u16SecondChar );
static U16 _msAPI_MLE_FontHindiGetFeatureMap( HindiScript_e eScript, const HindiFeatureRecord_t **ppasFeatureMap );
#endif //__FEATURE_VECTOR_FONT__

/*-------------------------------------------------------------------------------------------
*
*                                         FUNCTION DEFINE
*
-------------------------------------------------------------------------------------------*/

/**
 *@FUNCTION         _msAPI_MLE_FontHindiRules
 *@DESCRIPTION
 *@AUTHOR           anning.deng@mstarsemi.com
 *@DATA             2010-11-01
 *@PARAMETERS
        [IN] pu16Cluster                Pointer of cluster
        [IN] u16ClusterSize         Size of cluster
        [] pu16Glyph
        [] u16ClustIndex
        [] pu16OffsetInConcatenation
        [] pu16OffsetInComposed
        [] pu16ConcatenationComposedSize
        [] pu16ConcatenationElememtSize
*@RETURN
*/
U16 _msAPI_MLE_FontHindiRules( HindiScript_e eScript, LE_LanguageTag_e eLang, U16 *pu16Cluster, U16 u16ClusterSize, U16 u16ClustIndex, U16 *pu16Glyph, U16 *pu16OffsetInConcatenation, U16 *pu16OffsetInComposed, U16 *pu16ConcatenationComposedSize, U32 *pu32Features )
{
#ifdef __FEATURE_VECTOR_FONT__
    if ( msAPI_MLE_FONTBASE_IsVectorFontExist() )
    {
        return _msAPI_MLE_FontHindiVectorRules(eScript, eLang, pu16Cluster, u16ClusterSize, u16ClustIndex, pu16Glyph, pu16OffsetInConcatenation, pu16OffsetInComposed, pu16ConcatenationComposedSize, pu32Features);
    }
    else
    {
        return 0;
    }
#endif //__FEATURE_VECTOR_FONT__
}

static U16 _msAPI_MLE_FontHindiHandleHalant( HindiScript_e eScript, const U16 *pu16Txt, U32 u32InLen, U16 u16ConsumedCount, U16 *pu16Cluster, U16 u16BufferSize, U16 *pu16ClusterSize, U16 *pu16SeqInCluster, U32 *pu32FeatureTags )
{
    U16 u16Character = 0;
    U16 u16PreConChar = 0;
    U16 u16PreConOffset = 0;
    U16 u16ClusterSize = 0;
    HindiSpecialCharacter_e eSpType = HINDI_SP_INVALID;
    U16 u16HalantCount = 0;
    BOOLEAN bCharWithNukta = FALSE;

    u16PreConChar = msAPI_MLE_FontHindiGetPreCon(eScript, pu16Cluster, (*pu16ClusterSize + 1), u16ConsumedCount, &u16PreConOffset);
    u16Character = pu16Txt[u16ConsumedCount];

    while( _msAPI_MLE_FontHindiCharIsHalant(eScript, u16Character) )
    {
        U16 u16TempCurrentOffset;

        _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, *pu16ClusterSize, u16Character, u16ConsumedCount, pu16SeqInCluster );
        u16HalantCount = u16HalantCount + 1;

        if ( u16HalantCount >= 5 || (u32InLen > u16ConsumedCount && pu16Txt[u16ConsumedCount] == FONT_CONTROL_ZWJ) )
        {
            if ( _msAPI_MLE_FontHindiCharIsNoHalfCon(eScript, u16PreConChar) )
            {
                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_CJCT);
            }
            *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_HALF);
            *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_PRES);
            break;
        }

        _HINDI_VERLIFY_LEN( pu16Txt, u16ConsumedCount, u32InLen );

        if ( u16ConsumedCount == 1 )
        {
            break;
        }

        u16TempCurrentOffset = u16ConsumedCount;
        u16Character = pu16Txt[u16ConsumedCount];
        bCharWithNukta = _msAPI_MLE_FontHindiCharWithNukta(eScript, u16Character);
        if( _msAPI_MLE_FontHindiGetCharType(eScript, u16Character) == HINDI_CON )
        {
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, *pu16ClusterSize, u16Character, u16ConsumedCount, pu16SeqInCluster );

            if ( _msAPI_MLE_FontHindiStrWithAkhand(eScript, pu16Cluster, *pu16ClusterSize, u16PreConOffset) )
            {
                /*Cf + H + Cf -> Af*/
                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_AKHN);
            }

            if ( u32InLen > u16ConsumedCount && pu16Txt[u16ConsumedCount] == FONT_CONTROL_ZWJ )
            {
                if ( _msAPI_MLE_FontHindiCharIsNoHalfCon(eScript, u16PreConChar) )
                {
                    *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_CJCT);
                }
                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_HALF);
                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_PRES);
                break;
            }

            if ( u16PreConOffset == 0 && _msAPI_MLE_FontHindiCharIsRA(eScript, u16PreConChar)  && _msAPI_MLE_FontHindiCharIsHalant(eScript, pu16Cluster[1] ) )
            {
                /*Ra + H -> Reph*/
                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_RPHF);

                _msAPI_MLE_FontHindiFeatureWithRphf(eScript, *pu32FeatureTags, &eSpType);
                if ( eSpType == HINDI_SP_LEFT_T_UP_POS || eSpType == HINDI_SP_CENTER_T_UP_POS )
                {
                    /*{Kh} + Kf -> Lf*/
                    *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVS);
                    *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);

                    //These 4 languages RA should add blwm feature
                    switch(eScript)
                    {
    #ifdef __DVNG_FONT__
                    case HINDI_SCRIPT_DEVA:
    #endif
    #ifdef __BENGALI_FONT__
                    case HINDI_SCRIPT_BENG:
    #endif
                    case HINDI_SCRIPT_GUJR:
                    case HINDI_SCRIPT_ORYA:
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWM);
                        break;
                    default:
                        break;
                    }
                }
                else if ( eSpType == HINDI_SP_CENTER_T_DOWN_POS || eSpType == HINDI_SP_RIGHT_T_DOWN_POS )
                {
                    /*{Kh} + Kf -> Lf*/
                    *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWS);
                    *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWM);
                }
            }
            else
            {
                /*Kf + H -> Kh*/
                if ( _msAPI_MLE_FontHindiCharIsNoHalfCon(eScript, u16PreConChar) )
                {
                    *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_CJCT);
                }
                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_HALF);
                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_PRES);
            }


            u16PreConOffset = u16TempCurrentOffset;
            u16PreConChar = u16Character;

            if( _msAPI_MLE_FontHindiCharIsRA(eScript, u16Character) )
            {
                _HINDI_VERLIFY_LEN( pu16Txt, u16ConsumedCount, u32InLen );
                u16TempCurrentOffset = u16ConsumedCount;
                u16Character = pu16Txt[u16ConsumedCount];
                bCharWithNukta = _msAPI_MLE_FontHindiCharWithNukta(eScript, u16Character);

                //Special case
                if( ((u16ClusterSize) % 2) && _msAPI_MLE_FontHindiCharIsRA(eScript, u16PreConChar) )
                {
                    u16TempCurrentOffset = u16ConsumedCount;
                    u16Character = pu16Txt[u16ConsumedCount];
                    eSpType = _msAPI_MLE_FontHindiGetCharSpecialType(eScript, u16Character);
                    if( eSpType != HINDI_SP_LEFT_JOINER && eSpType != HINDI_SP_TWOPART_JOINER && _msAPI_MLE_FontHindiGetCharType(eScript, u16Character) == HINDI_DEPVOW )
                    {
                        _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, *pu16ClusterSize, u16Character, u16ConsumedCount, pu16SeqInCluster );
                    }

                    _HINDI_VERLIFY_LEN( pu16Txt, u16ConsumedCount, u32InLen );
                    u16TempCurrentOffset = u16ConsumedCount;
                    u16Character = pu16Txt[u16ConsumedCount];
                    bCharWithNukta = _msAPI_MLE_FontHindiCharWithNukta(eScript, u16Character);
                    if( _msAPI_MLE_FontHindiGetCharType(eScript, u16Character) == HINDI_SIGN )
                    {
                        _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, *pu16ClusterSize, u16Character, u16ConsumedCount, pu16SeqInCluster );
                    }
                    break;
                }
            }
            else
            {
                _HINDI_VERLIFY_LEN( pu16Txt, u16ConsumedCount, u32InLen );
                u16TempCurrentOffset = u16ConsumedCount;
                u16Character = pu16Txt[u16ConsumedCount];
                bCharWithNukta = _msAPI_MLE_FontHindiCharWithNukta(eScript, u16Character);
            }
        }
        else if( u32InLen >5 && *pu16ClusterSize == 4
            &&  _msAPI_MLE_FontHindiCharIsHalant(eScript, u16Character)
            &&  _msAPI_MLE_FontHindiCharIsRA(eScript, pu16Txt[u16ConsumedCount+1]))
        {
            if(pu16Cluster[0] == 0x09A6 && pu16Cluster[2] == 0x09A6
                &&_msAPI_MLE_FontHindiCharIsHalant(eScript, pu16Cluster[1])
                && _msAPI_MLE_FontHindiCharIsHalant(eScript, pu16Cluster[3]))
            {
                _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, *pu16ClusterSize, u16Character, u16ConsumedCount, pu16SeqInCluster );
                _HINDI_VERLIFY_LEN( pu16Txt, u16ConsumedCount, u32InLen );
                u16Character = pu16Txt[u16ConsumedCount];

                _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, *pu16ClusterSize, u16Character, u16ConsumedCount, pu16SeqInCluster );
                _HINDI_VERLIFY_LEN( pu16Txt, u16ConsumedCount, u32InLen );
                u16Character = pu16Txt[u16ConsumedCount];
            }

        }
        else
        {
            break;
        }



        if ( !bCharWithNukta && _msAPI_MLE_FontHindiCharIsNukta(eScript, u16Character) )
        {
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, *pu16ClusterSize, u16Character, u16ConsumedCount, pu16SeqInCluster );

            /*Cf + Nukta -> Kf-nukta*/
            *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_NUKT);

            _HINDI_VERLIFY_LEN( pu16Txt, u16ConsumedCount, u32InLen );
            u16Character = pu16Txt[u16ConsumedCount];
            bCharWithNukta = _msAPI_MLE_FontHindiCharWithNukta(eScript, u16Character);
        }
    }

    return u16ConsumedCount;
}

/**
 *@FUNCTION                     _msAPI_MLE_FontHindiGetCluster
 *@DESCRIPTION                  get cluster data
 *@AUTHOR                       anning.deng@mstarsemi.com
 *@DATA                         2010-11-01
 *@PARAMETERS
        [IN] pu16InTxt          original text string pointer
        [IN] u32InLen               original text length
        [OUT] pu16Cluster           pointer of cluster
        [IN] u16BufferSize          size of buffer for convert
        [OUT] pu16ConsumedCount consumed count
        [] pu16SeqInCluster
        [IN] bIsDispStr         is display string. #measure:FALSE#display:TRUE
        [OUT] ps8Increase           increase of string. example [09cb]->[09c7 09be] increase = 1
 */
static U16 _msAPI_MLE_FontHindiGetCluster( HindiScript_e eScript, const U16 *pu16Txt, U32 u32InLen, U16 *pu16Cluster, U16 u16BufferSize, U16 *pu16ConsumedCount, U16 *pu16SeqInCluster, BOOLEAN bIsDispStr, U32 *pu32FeatureTags )
{
    U16 u16Character = 0;
    U16 u16ClusterSize = 0;
    HindiCharacter_e eType = HINDI_INVALID;
    HindiSpecialCharacter_e eSpType = HINDI_SP_INVALID;
    BOOLEAN bCharWithNukta = FALSE, bTwoPartsCombine = FALSE;
    U16 i= 0;
    U16 u16Result= 0;
    U16 *pu16BufferBackup = NULL;

    if ( pu16Txt == NULL || u32InLen == 0 || pu16ConsumedCount == NULL || pu32FeatureTags == NULL )
    {
        return 0;
    }

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return 0;
    }

    for ( i = 0; i < HINDI_MAX_SCRIPT_NUM; i++ )
    {
        if ( g_pHindiLangsTbl[i] == NULL )
        {
            break;
        }

        if ( g_pHindiLangsTbl[i]->eScript == eScript )
        {
            if ( g_pHindiLangsTbl[i]->fnGetCluster )
            {
                u16Result = g_pHindiLangsTbl[i]->fnGetCluster( eScript, pu16Txt, u32InLen, pu16Cluster, u16BufferSize, pu16ConsumedCount, pu16SeqInCluster, bIsDispStr, pu32FeatureTags );
                break;
            }
        }
    }

    if ( u16Result > 0)
    {
        return u16Result;
    }

    *pu16ConsumedCount = 0;
    u16Character = pu16Txt[0];

    eType = _msAPI_MLE_FontHindiGetCharType(eScript, u16Character);
    eSpType = _msAPI_MLE_FontHindiGetCharSpecialType(eScript, u16Character);
    bCharWithNukta = _msAPI_MLE_FontHindiCharWithNukta(eScript, u16Character);
    switch( eType )
    {
        case HINDI_CON:
        {
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];

            if ( !bCharWithNukta && _msAPI_MLE_FontHindiCharIsNukta(eScript, u16Character) )
            {
                /*Cf + Nukta -> Kf-nukta*/
                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_NUKT);
                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWM);

                //For customer's Kannada TTF file, need to use abvm feature
                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);

                _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );
                _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
                u16Character = pu16Txt[*pu16ConsumedCount];
                bCharWithNukta = _msAPI_MLE_FontHindiCharWithNukta(eScript, u16Character);
#ifdef __BENGALI_FONT__
                {
                    U16 u16YASize = 0;
                    u16YASize = msAPI_MLE_FontBengaliGetYAPHALAAClusterSize( pu16Txt, u32InLen, *pu16ConsumedCount);
                    while(u16YASize > 0)
                    {
                        u16YASize--;
                        _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );
                        _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
                        u16Character = pu16Txt[*pu16ConsumedCount];
                    }
                }
#endif
            }

            if(u32InLen >2 && _msAPI_MLE_FontHindiCharIsRA(eScript, pu16Cluster[0]) && _msAPI_MLE_FontHindiCharIsHalant(eScript, u16Character)
                && (pu16Txt[2] == 0x098B || pu16Txt[2] == 0x098C)) // for bengali
            {
                _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );
                _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
                u16Character = pu16Txt[*pu16ConsumedCount];

                _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );
                _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
                u16Character = pu16Txt[*pu16ConsumedCount];
            }
            else if( _msAPI_MLE_FontHindiCharIsHalant(eScript, u16Character) )
            {
                *pu16ConsumedCount = _msAPI_MLE_FontHindiHandleHalant(eScript, pu16Txt, u32InLen, *pu16ConsumedCount, pu16Cluster, u16BufferSize, &u16ClusterSize, pu16SeqInCluster, pu32FeatureTags);
                if ( *pu16ConsumedCount > 0 && _msAPI_MLE_FontHindiCharIsHalant(eScript, pu16Txt[(*pu16ConsumedCount) - 1]) )
                {
                    if ( _msAPI_MLE_FontHindiCharIsHalant(eScript, pu16Txt[(*pu16ConsumedCount) - 1]) )
                    {
                        eSpType = _msAPI_MLE_FontHindiGetCharSpecialType(eScript, pu16Txt[(*pu16ConsumedCount) - 1]);
                        if ( eSpType == HINDI_SP_LEFT_T_UP_POS || eSpType == HINDI_SP_CENTER_T_UP_POS )
                        {
                            /*{Kh} + Kf -> Lf*/
                            *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVS);
                            *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);
                        }
                        else if ( eSpType == HINDI_SP_CENTER_T_DOWN_POS || eSpType == HINDI_SP_RIGHT_T_DOWN_POS )
                        {
                            /*{Kh} + Kf -> Lf*/
                            *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWS);
                            *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWM);
                        }

#if (defined(__KNDA_FONT__))
                        if ( eScript == HINDI_SCRIPT_KNDA )
                        {
                            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
                            u16Character = pu16Txt[*pu16ConsumedCount];
                            eSpType = _msAPI_MLE_FontHindiGetCharSpecialType(eScript, u16Character);

                            if ( eSpType == HINDI_SP_LEFT_T_UP_POS || eSpType == HINDI_SP_CENTER_T_UP_POS )
                            {
                                /*{Kh} + Kf -> Lf*/
                                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVS);
                                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);
                            }
                            else if ( eSpType == HINDI_SP_CENTER_T_DOWN_POS || eSpType == HINDI_SP_RIGHT_T_DOWN_POS )
                            {
                                /*{Kh} + Kf -> Lf*/
                                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWS);
                                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWM);
                            }

                            if (_msAPI_MLE_FontHindiCharIsNukta(eScript, u16Character))
                            {
                                _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );
                                _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
                                //u16Character = pu16Txt[*pu16ConsumedCount];
                            }
                            break;
                        }
#endif
#if (defined(__MLYM_FONT__) || defined(__DVNG_FONT___))
                        //FIX ME: Is this suitable for other languages?
                        if ( ( eScript ==  HINDI_SCRIPT_MLYM ) || ( eScript == HINDI_SCRIPT_DEVA ) )
                        {
                            u16Character = pu16Txt[*pu16ConsumedCount];
                            if ( FONT_CONTROL_ZWJ == u16Character )
                            {
                                _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );
                                _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
                                u16Character = pu16Txt[*pu16ConsumedCount];
                                bCharWithNukta = _msAPI_MLE_FontHindiCharWithNukta(eScript, u16Character);
                                eType = _msAPI_MLE_FontHindiGetCharType(eScript, u16Character);

                                if ( eType == HINDI_CON )
                                {
                                    _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );
                                    _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
                                    u16Character = pu16Txt[*pu16ConsumedCount];
                                    bCharWithNukta = _msAPI_MLE_FontHindiCharWithNukta(eScript, u16Character);

                                    if ( _msAPI_MLE_FontHindiCharIsHalant(eScript, u16Character) )
                                    {
                                        _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );
                                        _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
                                        u16Character = pu16Txt[*pu16ConsumedCount];
                                        bCharWithNukta = _msAPI_MLE_FontHindiCharWithNukta(eScript, u16Character);
                                        eType = _msAPI_MLE_FontHindiGetCharType(eScript, u16Character);

                                        if ( eType == HINDI_CON )
                                        {
                                            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );
                                        }
                                    }

                                }
                            }
                        }
                        else
#endif
                        {
                            break;
                        }
                    }
                }

                _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
                u16Character = pu16Txt[*pu16ConsumedCount];
                bCharWithNukta = _msAPI_MLE_FontHindiCharWithNukta(eScript, u16Character);
            }

#if defined(__TELUGU_FONT__)
            if ( ( eScript == HINDI_SCRIPT_TELU ) && ( u16Character == TELUGU_DV_E ) )
            {
                if ( ( *pu16ConsumedCount < u32InLen ) && ( pu16Txt[(*pu16ConsumedCount)+1] == TELUGU_ADV_AI ) )
                {
                    U16 *pu16CombineTxt = (U16 *)pu16Txt;

                    //In Telugu, TELUGU_DV_AI = TELUGU_DV_E + TELUGU_ADV_AI
                    //We combine these two characters into one two-parts character
                    //Before this operation, backup original string first
                    pu16BufferBackup = (U16 *)MALLOC(sizeof(U16) * u32InLen);
                    if ( pu16BufferBackup == NULL )
                        return 0;

                    memcpy((void *)pu16BufferBackup, (void *)pu16Txt, sizeof(U16)*u32InLen);
                    u16Character = TELUGU_DV_AI;
                    pu16CombineTxt[*pu16ConsumedCount] = TELUGU_DV_AI;
                    //Move remain characters forward one position
                    for(i=(*pu16ConsumedCount)+1;i<(u32InLen-1);i++)
                    {
                        pu16CombineTxt[i] = pu16CombineTxt[i+1];
                    }
                    u32InLen--;

                    bTwoPartsCombine = TRUE;
                }
            }
            //add blws feature for two-part 0x0c48
            if ((eScript == HINDI_SCRIPT_TELU) && (u16Character == TELUGU_DV_AI || u16Character == TELUGU_ADV_AI))
            {
                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWS);
            }
#endif
            eType = _msAPI_MLE_FontHindiGetCharType(eScript, u16Character);
            eSpType = _msAPI_MLE_FontHindiGetCharSpecialType(eScript, u16Character);
            if ( eType == HINDI_DEPVOW )
            {
                BOOLEAN bLeftJoinSwap = FALSE;

                if ( eSpType == HINDI_SP_LEFT_JOINER || eSpType == HINDI_SP_TWOPART_JOINER )
                {
                    _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );

                    /*{Kh} + Kf -> Lf*/
                    *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_PRES);
                    //*pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_INIT);

                    if ( eSpType == HINDI_SP_LEFT_JOINER )
                    {
                        bLeftJoinSwap = TRUE;

                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_PRIV_FEATURE_LEFT_JOIN);
                        *pu16ConsumedCount = _msAPI_MLE_FontHindiReorderCluster(eScript, pu16Txt, u32InLen, *pu16ConsumedCount, pu16Cluster, u16BufferSize, &u16ClusterSize, HINDI_ORDER_DVI, pu16SeqInCluster, pu32FeatureTags );
                    }
                    else
                    {
#if (defined(__TELUGU_FONT__) || defined(__KNDA_FONT__))
                        if ( ( eScript == HINDI_SCRIPT_TELU ) || ( eScript == HINDI_SCRIPT_KNDA ) )
                        {
                            *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVS);
                            *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);
                        }
#endif
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_PSTS);
                        //Sometimes users use one two parts character, sometimes users use two seperate two parts component characters, (Ex: Left and Right parts, two characters).
                        //This mixed condition will confuse our font cache system and make incorrect outputs, especially in Telugu language
                        //So we added HINDI_PRIV_FEATURE_DONT_CACHED tag to prevent this happens.
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_PRIV_FEATURE_DONT_CACHED);

                        if ( !bTwoPartsCombine )
                        {
                            *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_PRIV_FEATURE_TWOPART_JOIN);
                        }
                        *pu16ConsumedCount = _msAPI_MLE_FontHindiReorderCluster(eScript, pu16Txt, u32InLen, *pu16ConsumedCount, pu16Cluster, u16BufferSize, &u16ClusterSize, HINDI_ORDER_TWOPART_DEPVOW, pu16SeqInCluster, pu32FeatureTags );
                    }

                    _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
                    u16Character = pu16Txt[*pu16ConsumedCount];
                    bCharWithNukta = _msAPI_MLE_FontHindiCharWithNukta(eScript, u16Character);
                    if( _msAPI_MLE_FontHindiCharIsBindu(eScript, u16Character) )
                    {
                        //for customer's TTF font, use BLWM instead of ABVM
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWS);
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWM);
                        //*pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVS);
                        //*pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);

                        _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );

                        _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
                        u16Character = pu16Txt[*pu16ConsumedCount];
                    }
                }
                else
                {
                    _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );

                    if ( eSpType == HINDI_SP_LEFT_T_UP_POS || eSpType == HINDI_SP_CENTER_T_UP_POS )
                    {
                        /*{Kh} + Kf -> Lf*/
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVS);
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);

                        //For some TTF fonts, they need to use BLWM feature
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWS);
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWM);
                    }
                    else if ( eSpType == HINDI_SP_CENTER_T_DOWN_POS || eSpType == HINDI_SP_RIGHT_T_DOWN_POS )
                    {
                        /*{Kh} + Kf -> Lf*/
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWS);
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWM);
                    }
                    else if ( eSpType == HINDI_SP_RIGHT_JOINER )
                    {
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_PSTS);

                        //For some TTF fonts, they need to use ABVS, BLWM feature
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVS);
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWM);
                    }

                    _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
                    u16Character = pu16Txt[*pu16ConsumedCount];
                    bCharWithNukta = _msAPI_MLE_FontHindiCharWithNukta(eScript, u16Character);
                }

                if ( !bCharWithNukta && _msAPI_MLE_FontHindiCharIsNukta(eScript, u16Character) )
                {
                    /*Cf + Nukta -> Kf-nukta*/
                    *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_NUKT);
                    *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWM);

                    _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );

                    //From above if statement, this condition combination should be:
                    //Left join Dep Vowel + Consonant + Nukta
                    //or
                    //Left join Dep Vowel + Consonant + Bindu sign + Nukta
                    if ( ( bLeftJoinSwap ) && ( !_msAPI_MLE_FontHindiCharIsBindu(eScript, pu16Cluster[u16ClusterSize-2]) ) )
                    {
                        //Because bLeftJoinSwap is true, Nukta should follow dependent vowel instead of consonant
                        if ( _msAPI_MLE_FontHindiGetCharSpecialType(eScript, pu16Cluster[u16ClusterSize-3]) == HINDI_SP_LEFT_JOINER )
                        {
                            //swap order
                            u16Character = pu16Cluster[u16ClusterSize-2];
                            pu16Cluster[u16ClusterSize-2] = pu16Cluster[u16ClusterSize-1];
                            pu16Cluster[u16ClusterSize-1] = u16Character;

                            if ( pu16SeqInCluster )
                            {
                                u16Character = pu16SeqInCluster[u16ClusterSize - 2];
                                pu16SeqInCluster[u16ClusterSize - 2] = pu16SeqInCluster[u16ClusterSize - 1];
                                pu16SeqInCluster[u16ClusterSize - 1] = u16Character;
                            }
                        }
                    }

                    _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
                    u16Character = pu16Txt[*pu16ConsumedCount];
                    bCharWithNukta = _msAPI_MLE_FontHindiCharWithNukta(eScript, u16Character);
                }
#if (defined(__TELUGU_FONT__) || defined(__PUNJ_FONT__) || defined(__KNDA_FONT__) || defined(__GUJR_FONT__))
                if ( ( ( eScript ==  HINDI_SCRIPT_TELU ) || ( eScript ==  HINDI_SCRIPT_PUNJ ) || ( eScript ==  HINDI_SCRIPT_KNDA ) || ( eScript == HINDI_SCRIPT_GUJR ) ) && (_msAPI_MLE_FontHindiGetCharType(eScript, u16Character) == HINDI_DEPVOW) )
                {
                    eSpType = _msAPI_MLE_FontHindiGetCharSpecialType(eScript, u16Character);

                    if(eSpType != HINDI_SP_INVALID)
                        _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );

                    switch( eSpType )
                    {
                    case HINDI_SP_LEFT_T_UP_POS:
                    case HINDI_SP_CENTER_T_UP_POS:
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);
                        break;
                    case HINDI_SP_CENTER_T_DOWN_POS:
                    case HINDI_SP_RIGHT_T_DOWN_POS:
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWM);
                        break;
                    case HINDI_SP_RIGHT_POS:
                        //Todo: not sure, need test
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWF);
                        break;
                    case HINDI_SP_TWOPART_JOINER:
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_PSTS);
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_PRIV_FEATURE_TWOPART_JOIN);
                        if(pu16SeqInCluster)//fix coverity 203850
                        {
                            *pu16ConsumedCount = _msAPI_MLE_FontHindiReorderCluster(eScript, pu16Txt, u32InLen, *pu16ConsumedCount, pu16Cluster, u16BufferSize, &u16ClusterSize, HINDI_ORDER_TWOPART_DEPVOW, pu16SeqInCluster, pu32FeatureTags );
                        }
                        break;
#if ( defined(__KNDA_FONT__) )
                    case HINDI_SP_RIGHT_JOINER:
                        if ( eScript ==  HINDI_SCRIPT_KNDA )
                        {
                            *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_PSTS);
                        }
                        break;
#endif
                    default:
                        break;
                    }
                }
#endif
            }

            if ( _msAPI_MLE_FontHindiCharIsNukta(eScript, u16Character) )
            {
                break;
            }

            if ( ( _msAPI_MLE_FontHindiGetCharType(eScript, u16Character) == HINDI_SIGN )
#if (defined(__TAMIL_FONT__) || defined(__BENGALI_FONT__) || defined(__MLYM_FONT__) )
                || ( ( ( eScript ==  HINDI_SCRIPT_TAML ) || ( eScript == HINDI_SCRIPT_BENG ) || ( eScript ==  HINDI_SCRIPT_MLYM ) ) && ( _msAPI_MLE_FontHindiGetCharType(eScript, u16Character) == HINDI_DEPVOW) ) )
#else
                )
#endif
            {
                U16 u16PreChar = u16Character;

                //_HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );

                eSpType = _msAPI_MLE_FontHindiGetCharSpecialType(eScript, u16Character);

                if(eSpType != HINDI_SP_INVALID)
                    _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );

                if ( eSpType == HINDI_SP_LEFT_T_UP_POS || eSpType == HINDI_SP_CENTER_T_UP_POS )
                {
                    if( _msAPI_MLE_FontHindiCharIsBindu(eScript, u16PreChar) )
                    {
                        //for customer's TTF font, use BLWM instead of ABVM
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWM);
                    }
                    else
                    {
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);
                    }
                }
                else if ( eSpType == HINDI_SP_CENTER_T_DOWN_POS || eSpType == HINDI_SP_RIGHT_T_DOWN_POS )
                {
                    *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWM);
                }
            }
#if ( defined(__KNDA_FONT__) )
            else if ( eScript ==  HINDI_SCRIPT_KNDA )
            {
                _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
                u16Character = pu16Txt[*pu16ConsumedCount];
                bCharWithNukta = _msAPI_MLE_FontHindiCharWithNukta(eScript, u16Character);

                if ( _msAPI_MLE_FontHindiGetCharType(eScript, u16Character) == HINDI_DEPVOW )
                {
                    _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );

                    eSpType = _msAPI_MLE_FontHindiGetCharSpecialType(eScript, u16Character);

                    switch( eSpType )
                    {
                    case HINDI_SP_LEFT_T_UP_POS:
                    case HINDI_SP_CENTER_T_UP_POS:
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);
                        break;
                    case HINDI_SP_CENTER_T_DOWN_POS:
                    case HINDI_SP_RIGHT_T_DOWN_POS:
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWM);
                        break;
                    case HINDI_SP_RIGHT_JOINER:
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_PSTS);
                        break;
                    default:
                        break;
                    }
                }
            }
#endif

            break;
        } /* end of if first character is consonant */

        case HINDI_INDVOW:
        {
#ifdef __BENGALI_FONT__
            U16 u16YASize = 0;
            U16 u16PreChar = pu16Txt[*pu16ConsumedCount];
#endif
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            if( (eSpType != HINDI_SP_SINGLE_INDVOW) && ( (_msAPI_MLE_FontHindiGetCharType(eScript, u16Character) == HINDI_SIGN)
#if (defined(__PUNJ_FONT__) || defined(__DVNG_FONT__))
                || ((_msAPI_MLE_FontHindiGetCharType(eScript, u16Character) == HINDI_DEPVOW) && ( (eScript == HINDI_SCRIPT_PUNJ) || (eScript == HINDI_SCRIPT_DEVA) ) )
#endif
                ) )
            {
#ifdef __BENGALI_FONT__
                if( _msAPI_MLE_FontHindiCharIsHalant(eScript, u16Character) )
                {
                    u16YASize = msAPI_MLE_FontBengaliGetYAPHALAAClusterSize( pu16Txt, u32InLen, *pu16ConsumedCount);
                }
                else if(u16YASize == 0)
                {
#endif
                    _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );

#ifdef __PUNJ_FONT__
                    if ( eScript ==  HINDI_SCRIPT_PUNJ )
                    {
                        if ( !bCharWithNukta )
                        {
                            if ( _msAPI_MLE_FontHindiCharIsNukta(eScript, u16Character) )
                            {
                                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_NUKT);
                                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWM);
                            }
                            else
                            {
                                //Now it is HINDI_SIGN
                                switch(_msAPI_MLE_FontHindiGetCharSpecialType(eScript, u16Character))
                                {
                                case HINDI_SP_LEFT_T_UP_POS:
                                case HINDI_SP_CENTER_T_UP_POS:
                                    *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVS);
                                    *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);
                                    break;
                                case HINDI_SP_LEFT_T_DOWN_POS:
                                case HINDI_SP_CENTER_T_DOWN_POS:
                                case HINDI_SP_RIGHT_T_DOWN_POS:
                                    *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWS);
                                    *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWM);
                                    break;
                                default:
                                    break;
                                }
                            }
                        }
                    }
#endif
#ifdef __DVNG_FONT__
                    if (eScript == HINDI_SCRIPT_DEVA)
                    {
                        if (_msAPI_MLE_FontHindiGetCharType(eScript, u16Character) == HINDI_SIGN)
                        {
                            *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVS);
                        }
                    }
#endif
#ifdef __BENGALI_FONT__
                    _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
                    if ( _msAPI_MLE_FontHindiCharIsNukta(eScript,u16Character)
                        && (BENGALI_IV_VR == u16PreChar || BENGALI_IV_VL == u16PreChar))
                    {
                        u16YASize = msAPI_MLE_FontBengaliGetYAPHALAAClusterSize( pu16Txt, u32InLen, *pu16ConsumedCount);
                    }
                    u16Character = pu16Txt[*pu16ConsumedCount];
                }
#endif
            }
#ifdef __BENGALI_FONT__
            else
            {
                u16YASize = msAPI_MLE_FontBengaliGetYAPHALAAClusterSize( pu16Txt, u32InLen, *pu16ConsumedCount);
            }

            while(u16YASize > 0)
            {
                u16YASize--;
                _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );
                _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
                u16Character = pu16Txt[*pu16ConsumedCount];

            }
#endif
            break;
        }

        case HINDI_DEPVOW:
        case HINDI_SIGN:
        default:
        {
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );
            break;
        }
    }

    do // Add Zero Width Joiner to Cluster if the first char is constant and the last char is S_HALANT
    {
        if ( u16ClusterSize > 0 && *pu16ConsumedCount > 0 && *pu16ConsumedCount < u32InLen )
        {
            u16Character = pu16Txt[*pu16ConsumedCount];
            if ( FONT_CONTROL_ZWJ == u16Character )
            {
                _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );

                _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
                u16Character = pu16Txt[*pu16ConsumedCount];
                if( _msAPI_MLE_FontHindiCharIsFollowingZWJ(eScript, u16Character) )
                {
                    _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );

#ifdef __FEATURE_VECTOR_FONT__
                    if ( msAPI_MLE_FONTBASE_IsVectorFontExist() )
                    {
                        *pu16ConsumedCount = _msAPI_MLE_FontHindiReorderCluster(eScript, pu16Txt, u32InLen, *pu16ConsumedCount, pu16Cluster, u16BufferSize, &u16ClusterSize, HINDI_ORDER_ZWJ_SHALANT, pu16SeqInCluster, pu32FeatureTags);

                        eSpType = _msAPI_MLE_FontHindiGetCharSpecialType(eScript, u16Character);
                        if ( eSpType == HINDI_SP_LEFT_T_UP_POS || eSpType == HINDI_SP_CENTER_T_UP_POS )
                        {
                            if ( _msAPI_MLE_FontHindiCharIsLigated(eScript, pu16Txt[*pu16ConsumedCount - 3], pu16Txt[*pu16ConsumedCount - 2], TRUE) )
                            {
                                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVS);
                            }
                            else
                            {
                                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);
                            }
                        }
                        else if ( eSpType == HINDI_SP_CENTER_T_DOWN_POS || eSpType == HINDI_SP_RIGHT_T_DOWN_POS )
                        {
                            if ( _msAPI_MLE_FontHindiCharIsLigated(eScript, pu16Txt[*pu16ConsumedCount - 3], pu16Txt[*pu16ConsumedCount - 2], TRUE) )
                            {
                                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWS);
                            }
                            else
                            {
                                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWM);
                            }
                        }
                    }
#endif //__FEATURE_VECTOR_FONT__

                }
            }
        }
    } while(FALSE);

    _msAPI_MLE_FontHindiSwapRaHalantStr(eScript, pu16Txt, u32InLen, *pu16ConsumedCount, pu16Cluster, HINDI_CONVERT_MAX, &u16ClusterSize, pu16SeqInCluster, pu32FeatureTags);

#ifdef __FEATURE_VECTOR_FONT__
    if ( msAPI_MLE_FONTBASE_IsVectorFontExist() && u16ClusterSize == 1 )
    {
        eType = _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[0]);
        eSpType = _msAPI_MLE_FontHindiGetCharSpecialType(eScript, pu16Cluster[0]);
        if ( eType == HINDI_SIGN || eType == HINDI_DEPVOW )
        {
            U16 u16TempChar = pu16Cluster[0];

            if ( eSpType == HINDI_SP_LEFT_T_UP_POS || eSpType == HINDI_SP_CENTER_T_UP_POS )
            {
                pu16Cluster[0] = CHAR_DOTTED_CIRCLE;
                pu16Cluster[u16ClusterSize] = u16TempChar;
                pu16SeqInCluster[0] = 1;
                pu16SeqInCluster[1] = 0;
                u16ClusterSize = u16ClusterSize + 1;

                /*{Kh} + Kf -> Lf*/
                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVS);
                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);
                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_PRIV_FEATURE_PRE_DOTTED);
            }
            else if ( eSpType == HINDI_SP_CENTER_T_DOWN_POS || eSpType == HINDI_SP_RIGHT_T_DOWN_POS || eSpType == HINDI_SP_LEFT_T_DOWN_POS  )
            {
                pu16Cluster[0] = CHAR_DOTTED_CIRCLE;
                pu16Cluster[u16ClusterSize] = u16TempChar;
                pu16SeqInCluster[0] = 1;
                pu16SeqInCluster[1] = 0;
                u16ClusterSize = u16ClusterSize + 1;

                /*{Kh} + Kf -> Lf*/
                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWS);
                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWM);
                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_PRIV_FEATURE_PRE_DOTTED);
            }
            else if ( eSpType == HINDI_SP_RIGHT_JOINER )
            {
                pu16Cluster[0] = CHAR_DOTTED_CIRCLE;
                pu16Cluster[u16ClusterSize] = u16TempChar;
                pu16SeqInCluster[0] = 1;
                pu16SeqInCluster[1] = 0;
                u16ClusterSize = u16ClusterSize + 1;

                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_PSTS);
                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_PRIV_FEATURE_PRE_DOTTED);
            }
            else if ( eSpType == HINDI_SP_LEFT_JOINER )
            {
                pu16Cluster[u16ClusterSize] = CHAR_DOTTED_CIRCLE;
                if(pu16SeqInCluster)//fix coverity 203850
                {
                    pu16SeqInCluster[1] = 1;
                }
                u16ClusterSize = u16ClusterSize + 1;

                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_PRES);
                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_PRIV_FEATURE_POS_DOTTED);
            }
        }
    }
#endif //__FEATURE_VECTOR_FONT__

    do // Add Zero Width Joiner to Cluster if the first char is constant and the last char is S_HALANT
    {
        if ( u16ClusterSize > 0 && *pu16ConsumedCount > 0 && *pu16ConsumedCount < u32InLen )
        {
            if ( FONT_CONTROL_ZWNJ == u16Character )
            {
                _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, u16Character, *pu16ConsumedCount, pu16SeqInCluster );
            }
        }
    } while(FALSE);

    if ( bTwoPartsCombine )
    {
        (*pu16ConsumedCount)++;
        if ( pu16BufferBackup != NULL )
        {
            U16 *pu16CombineTxt = (U16 *)pu16Txt;

            //restore original input string
            u32InLen++;
            memcpy((void *)pu16CombineTxt, (void *)pu16BufferBackup, sizeof(U16)*u32InLen);
            FREE(pu16BufferBackup);
        }
    }

    return u16ClusterSize;
}/*end of function get_cluster */

/**
 *@FUNCTION                 _FontBengaliGetConsonantCluster
 *@DESCRIPTION              recursive search consonant cluster
 *@AUTHOR                   anning.deng@mstarsemi.com
 *@DATA                     2010-11-01
 *@PARAMETERS
        [IN] pu16Txt                original text string pointer
        [IN] u32InLen               original text length
        [IN] u16ConsumedCount   have been consumed  count
        [] u16Character                 first char ,always is BENGALI_S_HALANT
        [OUT] pu16Cluster           pointer of cluster
        [IN] u16BufferSize          size of buffer for convert
        [OUT] pu16ClusterSize       size of cluster
        [OUT] pu16SeqInCluster
 *@RETURN                   total    consumed count  (u16ConsumedCount + new consumed count)
 */
/*static U16 _msAPI_MLE_FontHindiGetConsonantCluster( HindiScript_e eScript, const U16 *pu16Txt, U32 u32InLen, U16 u16ConsumedCount, U16 u16Character, U16 *pu16Cluster, U16 u16BufferSize, U16 *pu16ClusterSize, U16 *pu16SeqInCluster, U32 *pu32FeatureTags )
{
    if ( pu16Txt == NULL || u32InLen <= u16ConsumedCount || pu16ClusterSize == NULL )
    {
        return 0;
    }

    do
    {
        _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, *pu16ClusterSize, u16Character, u16ConsumedCount, pu16SeqInCluster );
        _HINDI_VERLIFY_LEN( pu16Txt, u16ConsumedCount, u32InLen );
        u16Character = pu16Txt[u16ConsumedCount];
        if( _msAPI_MLE_FontHindiGetCharType(eScript, u16Character) == HINDI_CON )
        {
            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, *pu16ClusterSize, u16Character, u16ConsumedCount, pu16SeqInCluster );

            /Kh + V -> Lh-vattu/
            *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_VATU);

            _HINDI_VERLIFY_LEN( pu16Txt, u16ConsumedCount, u32InLen );
            u16Character = pu16Txt[u16ConsumedCount];
            if( _msAPI_MLE_FontHindiCharIsHalant(eScript, u16Character) )
            {
                u16ConsumedCount = _msAPI_MLE_FontHindiGetConsonantCluster(eScript, pu16Txt, u32InLen, u16ConsumedCount, u16Character, pu16Cluster, u16BufferSize, pu16ClusterSize, pu16SeqInCluster, pu32FeatureTags);
            }
        }
        else if( u32InLen >5 && *pu16ClusterSize == 4
            &&  _msAPI_MLE_FontHindiGetCharType(eScript, u16Character) == HINDI_HALANT
            &&  _msAPI_MLE_FontHindiCharIsRA(eScript, pu16Txt[u16ConsumedCount+1]))
        {
            if(pu16Cluster[0] == 0x09A6 && pu16Cluster[2] == 0x09A6
                &&_msAPI_MLE_FontHindiCharIsHalant(eScript, pu16Cluster[1])
                && _msAPI_MLE_FontHindiCharIsHalant(eScript, pu16Cluster[3]))
            {
                _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, *pu16ClusterSize, u16Character, u16ConsumedCount, pu16SeqInCluster );
                _HINDI_VERLIFY_LEN( pu16Txt, u16ConsumedCount, u32InLen );
                u16Character = pu16Txt[u16ConsumedCount];

                _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, *pu16ClusterSize, u16Character, u16ConsumedCount, pu16SeqInCluster );
                _HINDI_VERLIFY_LEN( pu16Txt, u16ConsumedCount, u32InLen );
                u16Character = pu16Txt[u16ConsumedCount];
            }

        }
    }while(FALSE);

    return u16ConsumedCount;
}*/

/**
 *@FUNCTION             _FontBengaliReorderCluster
 *@DESCRIPTION          reorder cluster
 *@AUTHOR               anning.deng@mstarsemi.com
 *@DATA                 2010-11-01
 *@PARAMETERS
        [IN] pu16Txt                original text string pointer
        [IN] u32InLen               original text length
        [IN] u16ConsumedCount   have been consumed count
        [OUT] pu16Cluster           pointer of cluster
        [IN] u16BufferSize          size of buffer for convert
        [OUT] pu16ClusterSize       size of cluster
        [IN] u16CharType            type of char #BengaliOrderType_e
        [] pu16SeqInCluster
 *@RETURN               total   consumed count  (u16ConsumedCount + new consumed count),this value is u16ConsumedCount here.
 */
static U16 _msAPI_MLE_FontHindiReorderCluster( HindiScript_e eScript, const U16 *pu16Txt, U32 u32InLen, U16 u16ConsumedCount, U16 *pu16Cluster, U16 u16BufferSize, U16 *pu16ClusterSize, U16 u16CharType, U16 *pu16SeqInCluster, U32 *pu32FeatureTags )
{
    U16 u16Character = 0;
    HindiSpecialCharacter_e eSpType = HINDI_SP_INVALID;
    U16 i, j;
    U16 u16Temp = 0;
    U16 u16TempSeq = 0;
    U16 au16Temp[4] = {0};
    U16 au16TempSeq[4] = {0};
    S16 k;

    switch ( u16CharType )
    {
        case HINDI_ORDER_CRA_SHALANT:
            if( ((*pu16ClusterSize) % 2) && _msAPI_MLE_FontHindiCharIsRA(eScript, pu16Cluster[0]) )
            {
                _HINDI_VERLIFY_LEN( pu16Txt, u16ConsumedCount, u32InLen );
                u16Character = pu16Txt[u16ConsumedCount];
                eSpType = _msAPI_MLE_FontHindiGetCharSpecialType(eScript, u16Character);
                if( eSpType != HINDI_SP_LEFT_JOINER && eSpType != HINDI_SP_TWOPART_JOINER && _msAPI_MLE_FontHindiGetCharType(eScript, u16Character) == HINDI_DEPVOW )
                {
                    _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, *pu16ClusterSize, u16Character, u16ConsumedCount, pu16SeqInCluster );
                }

                for( i = 0; i <= 1; i++ )
                {
                    u16Temp = pu16Cluster[0];
                    if ( pu16SeqInCluster )
                    {
                        u16TempSeq = pu16SeqInCluster[0];
                    }

                    for( j = 0; j < (*pu16ClusterSize) - 1; j++ )
                    {
                        pu16Cluster[j] = pu16Cluster[j+1];
                        if ( pu16SeqInCluster )
                        {
                            pu16SeqInCluster[j] = pu16SeqInCluster[j+1];
                        }
                    }

                    pu16Cluster[j] = u16Temp;
                    if ( pu16SeqInCluster )
                    {
                        pu16SeqInCluster[j] = u16TempSeq;
                    }
                }

                _HINDI_VERLIFY_LEN( pu16Txt, u16ConsumedCount, u32InLen );
                u16Character = pu16Txt[u16ConsumedCount];
                if( _msAPI_MLE_FontHindiGetCharType(eScript, u16Character) == HINDI_SIGN )
                {
                    _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, *pu16ClusterSize, u16Character, u16ConsumedCount, pu16SeqInCluster );;
                }
            }
            else if( (*pu16ClusterSize) > 1 && _msAPI_MLE_FontHindiCharIsRA(eScript, pu16Cluster[0]) )
            {
                u16Temp = pu16Cluster[(*pu16ClusterSize) - 1];
                if ( pu16SeqInCluster )
                {
                    u16TempSeq = pu16SeqInCluster[(*pu16ClusterSize) - 1];
                }

                for( i = 0; i <= 1; i++ )
                {
                    au16Temp[0] = pu16Cluster[0];
                    if ( pu16SeqInCluster )
                    {
                        au16TempSeq[0] = pu16SeqInCluster[0];
                    }

                    for( j = 0; j < (*pu16ClusterSize) - 2; j++ )
                    {
                        pu16Cluster[j] = pu16Cluster[j+1];
                        if ( pu16SeqInCluster )
                        {
                            pu16SeqInCluster[j] = pu16SeqInCluster[j+1];
                        }
                    }
                    pu16Cluster[j] = au16Temp[0];
                    if ( pu16SeqInCluster )
                    {
                        pu16SeqInCluster[j] = au16TempSeq[0];
                    }
                }

                pu16Cluster[(*pu16ClusterSize) - 1] = u16Temp;
                if ( pu16SeqInCluster )
                {
                    pu16SeqInCluster[(*pu16ClusterSize) - 1] = u16TempSeq;
                }
            }
            break;

        case HINDI_ORDER_DVI:
            {
                U16 u16BaseConsonant = 0;

    #ifdef __PUNJ_FONT__
                if ( eScript == HINDI_SCRIPT_PUNJ )
                {
                    BOOLEAN bLastCONFound = FALSE;
                    BOOLEAN bFoundBelowBaseForm = FALSE;
                    U16 u16Base = 0;

                    if ( ( IS_PUNJ_RA_CHAR(pu16Cluster[0]) ) && ( _msAPI_MLE_FontHindiCharIsHalant(eScript, pu16Cluster[1]) ) && ((*pu16ClusterSize) > 2) )
                    {
                        u16Base += 2;
                    }

                    for(k=((*pu16ClusterSize)-1); k >= u16Base; k--)
                    {
                        if ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[k]) == HINDI_CON )
                        {
                            bLastCONFound = TRUE;
                            break;
                        }
                    }

                    if ( bLastCONFound )
                    {
                        u16BaseConsonant = k;

                        while( u16BaseConsonant > 0 )
                        {
                            if ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16BaseConsonant]) == HINDI_CON )
                            {
                                if ( ( ( u16BaseConsonant > 0 ) && ( u16BaseConsonant < ((*pu16ClusterSize)-1) ) && ( !_msAPI_MLE_FontHindiCharIsHalant(eScript, pu16Cluster[u16BaseConsonant - 1]) ) ) ||
                                        ( !IS_PUNJ_POST_BELOW_BASE_FORM(pu16Cluster[u16BaseConsonant]) ) )
                                {
                                    break;
                                }
                            }

                            if ( IS_PUNJ_POST_BASE_FORM(pu16Cluster[u16BaseConsonant]) )
                            {
                                if ( bFoundBelowBaseForm )
                                {
                                    break;
                                }
                            }
                            else if ( IS_PUNJ_BELOW_BASE_FORM(pu16Cluster[u16BaseConsonant]) )
                            {
                                bFoundBelowBaseForm = TRUE;
                            }

                            u16BaseConsonant--;
                        }

                    }
                }
    #endif

            u16Temp = pu16Cluster[(*pu16ClusterSize) - 1];
            if ( pu16SeqInCluster )
            {
                u16TempSeq = pu16SeqInCluster[(*pu16ClusterSize) - 1];
            }

                for( k = (*pu16ClusterSize) - 2; k >= u16BaseConsonant; k-- )
            {
                pu16Cluster[k + 1] = pu16Cluster[k];
                if ( pu16SeqInCluster )
                {
                    pu16SeqInCluster[k + 1] = pu16SeqInCluster[k];
                }
                    if ( k == u16BaseConsonant )
                {
                    break;
                }
            }

                pu16Cluster[u16BaseConsonant] = u16Temp;
                if ( pu16SeqInCluster )
                {
                    pu16SeqInCluster[u16BaseConsonant] = u16TempSeq;
                }
            }
            break;

        case HINDI_ORDER_CON_DEPVOW:
            au16Temp[0] = pu16Cluster[2];
            au16Temp[1] = pu16Cluster[3];
            au16Temp[2] = pu16Cluster[0];
            au16Temp[3] = pu16Cluster[1];
            if ( pu16SeqInCluster )
            {
                au16TempSeq[0] = pu16SeqInCluster[2];
                au16TempSeq[1] = pu16SeqInCluster[3];
                au16TempSeq[2] = pu16SeqInCluster[0];
                au16TempSeq[3] = pu16SeqInCluster[1];
            }

            for( j = 0; j <= 3; j++ )
            {
                pu16Cluster[j] = au16Temp[j];
                if ( pu16SeqInCluster )
                {
                    pu16SeqInCluster[j] = au16TempSeq[j];
                }
            }
            break;

        case HINDI_ORDER_CON_SHALANT:
        {
            BOOLEAN bWithZWJ = FALSE;

            if ( pu16Cluster[(*pu16ClusterSize) - 1] == FONT_CONTROL_ZWJ )
            {
                bWithZWJ = TRUE;
            }

            if( !bWithZWJ )
            {
                for( i = 0; i <= 1; i++ )
                {
                    u16Temp = pu16Cluster[0];
                    if ( pu16SeqInCluster )
                    {
                        u16TempSeq = pu16SeqInCluster[0];
                    }

                    for( j = 0; j < (*pu16ClusterSize) - 1; j++ )
                    {
                        pu16Cluster[j] = pu16Cluster[j+1];
                        if ( pu16SeqInCluster )
                        {
                            pu16SeqInCluster[j] = pu16SeqInCluster[j+1];
                        }
                    }

                    pu16Cluster[j] = u16Temp;
                    if ( pu16SeqInCluster )
                    {
                        pu16SeqInCluster[j] = u16TempSeq;
                    }
                }
            }
            else
            {
                u16Temp = pu16Cluster[(*pu16ClusterSize) - 1];
                if ( pu16SeqInCluster )
                {
                    u16TempSeq = pu16SeqInCluster[(*pu16ClusterSize) - 1];
                }

                for( i = 0; i <= 1; i++ )
                {
                    au16Temp[0] = pu16Cluster[0];
                    if ( pu16SeqInCluster )
                    {
                        au16TempSeq[0] = pu16SeqInCluster[0];
                    }

                    for( j = 0; j < (*pu16ClusterSize) - 2; j++ )
                    {
                        pu16Cluster[j] = pu16Cluster[j+1];
                        if ( pu16SeqInCluster )
                        {
                            pu16SeqInCluster[j] = pu16SeqInCluster[j+1];
                        }
                    }

                    pu16Cluster[j] = au16Temp[0];
                    if ( pu16SeqInCluster )
                    {
                        pu16SeqInCluster[j] = au16TempSeq[0];
                    }
                }

                pu16Cluster[(*pu16ClusterSize) - 1] = u16Temp;
                if ( pu16SeqInCluster )
                {
                    pu16SeqInCluster[(*pu16ClusterSize) - 1] = u16TempSeq;
                }
            }
            break;
        }

        case HINDI_ORDER_ZWJ_SHALANT:
            if ( *pu16ClusterSize > 1 )
            {
                if ( eScript ==  HINDI_SCRIPT_DEVA )
                {
                    if ( !IS_DVNG_HALANT_CHAR(pu16Cluster[(*pu16ClusterSize) - 1]) )
                    {
                        break;
                    }
                }

                u16Temp = pu16Cluster[(*pu16ClusterSize) - 2];
                pu16Cluster[(*pu16ClusterSize) - 2] = pu16Cluster[(*pu16ClusterSize) - 1];
                pu16Cluster[(*pu16ClusterSize) - 1] = u16Temp;
                if ( pu16SeqInCluster )
                {
                    u16TempSeq = pu16SeqInCluster[(*pu16ClusterSize) - 2];
                    pu16SeqInCluster[(*pu16ClusterSize) - 2] = pu16SeqInCluster[(*pu16ClusterSize) - 1];
                    pu16SeqInCluster[(*pu16ClusterSize) - 1] = u16TempSeq;
                }
            }
            break;

        case HINDI_ORDER_TWOPART_DEPVOW:
        {
            U16 u16Tail = 0;
            U16 u16MoveCount = 0;
            S16 s16BaseConIndex = 0;

            u16Tail = _msAPI_MLE_FontHindiGetTwoWordRightChar(eScript, pu16Cluster[(*pu16ClusterSize) - 1]);//get right part
            u16Temp = _msAPI_MLE_FontHindiGetTwoWordLeftChar(eScript, pu16Cluster[(*pu16ClusterSize) - 1]);

#if (defined(__TELUGU_FONT__) || defined(__KNDA_FONT__))
            if ( ( ( eScript == HINDI_SCRIPT_TELU ) || ( eScript == HINDI_SCRIPT_KNDA ) ) && ( (*pu16ClusterSize) >= 3 ) )
            {
                BOOLEAN bPostAkhn = FALSE;
                U16 u16Base = 1;

                if ( ( ( pu16Cluster[0] == KANNADA_C_RA ) || ( pu16Cluster[0] == TELUGU_C_RA ) ) && ( _msAPI_MLE_FontHindiCharIsHalant(eScript, pu16Cluster[1]) ) && ((*pu16ClusterSize) > 2) )
                {
                    u16Base += 2;
                }

                for( k = (*pu16ClusterSize) - 2; k >= u16Base; k-- )
                {
                    if ( !_msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[k-1], pu16Cluster[k]) )
                    {
                        if ( (k-2) >= 0 )
                        {
                            if ( !_msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[k-2], pu16Cluster[k-1]) )
                            {
                                break;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                if ( eScript == HINDI_SCRIPT_KNDA )
                {
                    S16 l;

                    if (_msAPI_MLE_FontHindiGetCharSpecialType(eScript, u16Tail) != HINDI_SP_RIGHT_POS)
                    {
                        for (l=(u16Base-1); l< ( *pu16ClusterSize - 2 ); l++)
                        {
                            if ( _msAPI_MLE_FontHindiStrWithAkhand( eScript, pu16Cluster, *pu16ClusterSize, l ) )
                            {
                                bPostAkhn = TRUE;
                                break;
                            }
                        }
                    }

                    if ( bPostAkhn )
                    {
                        if ( ( k >= l ) && ( k <= (l+2) ) )
                        {
                            k = l;
                        }

                        k += 3;
                    }
                }

                //if u16Tail is HINDI_SP_RIGHT_POS, k+3 is the position of u16Tail
                if ( (eScript == HINDI_SCRIPT_KNDA) && (_msAPI_MLE_FontHindiGetCharSpecialType(eScript, u16Tail) == HINDI_SP_RIGHT_POS) && (!bPostAkhn) )
                {
                    for(u16MoveCount = (*pu16ClusterSize) - 2; u16MoveCount >= k; u16MoveCount-- )
                    {
                        pu16Cluster[u16MoveCount + 1 ] = pu16Cluster[u16MoveCount];
                        if ( pu16SeqInCluster )
                        {
                            pu16SeqInCluster[u16MoveCount + 1] = pu16SeqInCluster[u16MoveCount];
                        }
                        if ( u16MoveCount == 0 )
                        {
                            break;
                        }
                    }
                    pu16Cluster[*pu16ClusterSize] = u16Tail;
                    if(pu16SeqInCluster)//fix coverity 203957
                    {
                        pu16SeqInCluster[*pu16ClusterSize] = *pu16ClusterSize;
                    }
                }
                else //k+1 is the position of u16Tail
                {
                    for(u16MoveCount = (*pu16ClusterSize) - 2; u16MoveCount >= k; u16MoveCount-- )
                    {
                        pu16Cluster[u16MoveCount + 2 ] = pu16Cluster[u16MoveCount];
                        if ( pu16SeqInCluster )
                        {
                            pu16SeqInCluster[u16MoveCount + 2] = pu16SeqInCluster[u16MoveCount];
                        }
                        if ( u16MoveCount == 0 )
                        {
                            break;
                        }
                    }
                    pu16Cluster[k+1] = u16Tail;
                    if(pu16SeqInCluster)//fix coverity 203849
                    {
                        pu16SeqInCluster[k+1] = k+1;
                    }
                }

                if ( k > 0 )
                {
                    U16 u16StartPos = k-1;

                    if ( bPostAkhn )
                    {
                        u16StartPos = k-3;
                    }

                    for(s16BaseConIndex = u16StartPos; s16BaseConIndex >= (u16Base-1); s16BaseConIndex-- )
                    {
                        if ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[s16BaseConIndex]) == HINDI_CON )
                            break;
                    }

                    if ( ( u16Base > 1 ) && ( s16BaseConIndex < 2 ) )
                    {
                        //Reph case
                        s16BaseConIndex = 2;
                    }

                    //Now s16BaseConIndex is the position of base consonant
                    //here need to check!
                    if ( ( s16BaseConIndex >= 0 ) && ( (k-2) >= 0 ) )
                    {
                        U16 u16EndPos = s16BaseConIndex+1;

                        if ( bPostAkhn )
                        {
                            u16EndPos = s16BaseConIndex+3;
                        }

                        for(u16MoveCount = (k-2); u16MoveCount >= u16EndPos; u16MoveCount-- )
                        {
                            pu16Cluster[u16MoveCount + 1 ] = pu16Cluster[u16MoveCount];
                            if ( pu16SeqInCluster )
                            {
                                pu16SeqInCluster[u16MoveCount + 1] = pu16SeqInCluster[u16MoveCount];
                            }
                            if ( u16MoveCount == 0 )
                            {
                                break;
                            }
                        }
                    }

                    if (bPostAkhn) //base cosonant is akhn
                    {
                        pu16Cluster[s16BaseConIndex+3] = u16Temp;
                        pu16SeqInCluster[s16BaseConIndex+3] = s16BaseConIndex+3;
                    }
                    else
                    {
                    pu16Cluster[s16BaseConIndex+1] = u16Temp;
                    if(pu16SeqInCluster)//fix coverity 203849
                    {
                        pu16SeqInCluster[s16BaseConIndex+1] = s16BaseConIndex+1;
                    }
                }
            }
            }
            else if ( (( eScript == HINDI_SCRIPT_TELU ) || ( eScript == HINDI_SCRIPT_KNDA )) && ( (*pu16ClusterSize) == 2 ) )
            {
                //Telugu only have one two part vowel case
                //At this condition, arrange after consonant
                if ( ( eScript == HINDI_SCRIPT_KNDA ) && ( _msAPI_MLE_FontHindiGetCharSpecialType(eScript, u16Temp) == HINDI_SP_TWOPART_JOINER ) )
                {
                    U16 u16Tail2, u16Head2;

                    //Split again
                    u16Tail2 = _msAPI_MLE_FontHindiGetTwoWordRightChar(eScript, u16Temp);//get right part
                    u16Head2 = _msAPI_MLE_FontHindiGetTwoWordLeftChar(eScript, u16Temp); //get left part
                    pu16Cluster[(*pu16ClusterSize) - 1] = u16Head2;
                    pu16SeqInCluster[(*pu16ClusterSize) - 1] = (*pu16ClusterSize) - 1;
                    pu16Cluster[(*pu16ClusterSize)] = u16Tail2;
                    pu16SeqInCluster[(*pu16ClusterSize)] = (*pu16ClusterSize);
                    if ( ( (*pu16ClusterSize) + 1 ) < u16BufferSize )
                    {
                        pu16Cluster[(*pu16ClusterSize) + 1] = u16Tail;
                        pu16SeqInCluster[(*pu16ClusterSize) + 1] = (*pu16ClusterSize) + 1;
                    }
                    (*pu16ClusterSize)++;

                    *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_PRIV_FEATURE_THREEPART);
                }
                else
                {
                    pu16Cluster[(*pu16ClusterSize) - 1] = u16Temp;
                    pu16SeqInCluster[(*pu16ClusterSize) - 1] = (*pu16ClusterSize) - 1;
                    pu16Cluster[(*pu16ClusterSize)] = u16Tail;
                    pu16SeqInCluster[(*pu16ClusterSize)] = (*pu16ClusterSize);
                }
            }
            else
#endif
            {
                for( k = (*pu16ClusterSize) - 1; k >= 0; k-- )
                {
                    pu16Cluster[k + 1] = pu16Cluster[k];
                    if ( pu16SeqInCluster )
                    {
                        pu16SeqInCluster[k + 1] = pu16SeqInCluster[k];
                    }
                    if ( k == 0 )
                    {
                        break;
                    }
                }
                pu16Cluster[0] = u16Temp;
                if ( pu16SeqInCluster )
                {
                    pu16SeqInCluster[0] = 0;
                }
                pu16Cluster[(*pu16ClusterSize)] = u16Tail;
            }

            (*pu16ClusterSize)++;
        }
        break;

        default:
            break;

    }

    return u16ConsumedCount;
}

/**
 *@FUNCTION             _FontBengaliGetClusterStartOffset
 *@DESCRIPTION
 *@AUTHOR               anning.deng@mstarsemi.com
 *@DATA                 2010-11-01
 *@PARAMETERS
        [IN] pu16InTxt          original text string pointer
        [IN] u32InLen               original text length
        [IN] u32Offset              code's offset
        [OUT] pu16Cluster           cluster's pointer
        [OUT] pu16CluserSize        cluster's size
        [OUT] pu16DisplayOffset
        [IN] bIsDispStr         is display string. #measure:FALSE#display:TRUE
        [OUT] ps8Increase           increase of string. example [09cb]->[09c7 09be] increase = 1
 *@RETURN
 */
U16 _msAPI_MLE_FontHindiGetClusterStartOffset( HindiScript_e eScript, const U16 *pu16InTxt, U32 u32InLen, U32 u32Offset, U16 *pu16Cluster, U16 *pu16CluserSize, BOOLEAN bIsDispStr, U32 *pu32FeatureTags )
{
    U16 u16ConsumedCount = 0;
    U16 au16ClusterSeq[HINDI_CONVERT_MAX] = {0,};
    U16 nReturnOffset = 0;
    U32 u32CurrentStartOffset = 0;

    if ( pu16Cluster == NULL || pu16CluserSize == NULL || u32Offset >= u32InLen )
    {
        return 0;
    }

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return 0;
    }

    while ( u32CurrentStartOffset <= u32Offset )
    {
        U32 u32FeatureTags = 0;
        ///HindiScript_e eTempScript = msAPI_MLE_FontHindiGetCharScript(pu16InTxt[u32CurrentStartOffset]);

        *pu16CluserSize = _msAPI_MLE_FontHindiGetCluster(eScript, &(pu16InTxt[u32CurrentStartOffset]), u32InLen - u32CurrentStartOffset, pu16Cluster, HINDI_CONVERT_MAX, &u16ConsumedCount, au16ClusterSeq, bIsDispStr, &u32FeatureTags);
#ifdef __BENGALI_FONT__
        *pu16CluserSize = msAPI_MLE_FontBengaliGetLigatedCluster(&(pu16InTxt[u32CurrentStartOffset]), u32InLen - u32CurrentStartOffset, pu16Cluster, HINDI_CONVERT_MAX, *pu16CluserSize, &u16ConsumedCount, au16ClusterSeq);
#endif

        if ( *pu16CluserSize > 0 )
        {
            if ( u32CurrentStartOffset + u16ConsumedCount > u32Offset )
            {
                *pu32FeatureTags = u32FeatureTags;
                nReturnOffset = _msAPI_MLE_FontHindiGetIndexInSequence(au16ClusterSeq, *pu16CluserSize, u32Offset - u32CurrentStartOffset);
                break;
            }
            u32CurrentStartOffset = u32CurrentStartOffset + u16ConsumedCount;
        }
        else
        {
            u32CurrentStartOffset = u32CurrentStartOffset + 1;
            if ( u32CurrentStartOffset > u32Offset )
            {
                break;
            }
        }
    }

    return nReturnOffset;
}

U16 _msAPI_MLE_FontHindiRefineCluster( HindiScript_e eScript, const U16 *pu16InTxt, U32 u32InLen, U32 u32Offset, U16 *pu16Cluster, U16 *pu16CluserSize, U16 u16ClusterOffset, BOOLEAN bIsDispStr, U32 *pu32Features, const U16 *pu16OriginTxt, U32 u32OriginOffset)
{
    U16 i= 0;
    U16 u16Result= u16ClusterOffset;
    for ( i = 0; i < HINDI_MAX_SCRIPT_NUM; i++ )
    {
        if ( g_pHindiLangsTbl[i] == NULL )
        {
            break;
        }

        if ( g_pHindiLangsTbl[i]->eScript == eScript )
        {
            if ( g_pHindiLangsTbl[i]->fnRefineCluster )
            {
                u16Result = g_pHindiLangsTbl[i]->fnRefineCluster(eScript, pu16InTxt, u32InLen, u32Offset, pu16Cluster, pu16CluserSize, u16ClusterOffset, bIsDispStr, pu32Features, pu16OriginTxt, u32OriginOffset);
                break;
            }
        }
    }

    return u16Result;
}
/**
 *@FUNCTION             _FontBengaliGetNextCodes
 *@DESCRIPTION          get translated code number from string
 *@AUTHOR               anning.deng@mstarsemi.com
 *@DATA                 2010-11-01
 *@PARAMETERS
        [IN] pu16InTxt      original text string pointer
        [IN] u32InLen           original text length
        [IN] u32Offset          code's offset
        [IN] u32SubLen      code's length
        [OUT] pu16OutCode   output code's pointer
        [IN] u32OutLen      output code's length
        [OUT] pu32Consumed  size of code that get from original text
        [IN] bIsDispStr     is display string. #measure:FALSE#display:TRUE
 *@RETURN               size of output codes
 *@ATTENTION            if orignal text include code [0x09cb] or [0x09cc] the return length is different from *pu32Consumed(*pu32Consumed always less than return value)
 */
U16 msAPI_MLE_FontHindiGetNextCodes( HindiScript_e eScript, LE_LanguageTag_e eLang, const U16 *pu16InTxt, U32 u32InLen, U32 u32Offset, U32 u32SubLen, U16 *pu16OutCode, U32 u32OutLen, U32 *pau32Consumed, BOOLEAN bIsDispStr, U32 *pu32Features, const U16 *pu16OriginTxt, U32 u32OriginOffset)
{
    U16 au16Cluster[HINDI_CONVERT_MAX] = {0};
    U16 au16OrginalCluster[HINDI_CONVERT_MAX] = {0};
    U16 nReturnLen = 0;
    U16 u16ClusterLen = 0;
    U16 u16OriginalClusterLen = 0;
    U16 u16ClusterOffset = 0;
    U32 u32FeatureTags = 0;

#ifdef __INDIC_FONT_RULE_CACHE__
    U8 *pCacheData = NULL;
    BOOLEAN bUseCache = FALSE;
    BOOLEAN bKeyDuplicate = FALSE;
    BOOLEAN bNoCached = FALSE;
#endif //__INDIC_FONT_RULE_CACHE__

    if ( u32InLen == 0 || pu16InTxt == NULL || pu16OutCode == NULL || pau32Consumed == NULL )
    {
        return 0;
    }

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return 0;
    }

    pau32Consumed[0] = 0;
    pau32Consumed[1] = 0;

    u16ClusterOffset = _msAPI_MLE_FontHindiGetClusterStartOffset(eScript, pu16InTxt, u32InLen, u32Offset, au16Cluster, &u16ClusterLen, bIsDispStr, &u32FeatureTags);

#ifdef __INDIC_FONT_RULE_CACHE__
    if( u32Offset == 0 && u16ClusterLen >=2 && u16ClusterLen<=5)
    {
#ifdef __BENGALI_FONT__
        if(au16Cluster[0] != BENGALI_DV_E) // Not cache Bengali init feature
        {
#endif
            pCacheData = (U8*)msAPI_MLE_FONTBASE_Vector_SearchHindiCache(au16Cluster, u16ClusterLen, u32FeatureTags, &bKeyDuplicate);
            bUseCache = TRUE;

#ifdef __INDIC_FONT_RULE_CACHE__
            if ( _msAPI_MLE_FontHindiFeatureWithNoCache(eScript, u32FeatureTags, &bNoCached ) )
            {
                if ( bNoCached )
                {
                    pCacheData = NULL;
                    bUseCache = FALSE;
                }
            }
#endif

#ifdef __BENGALI_FONT__
        }
#endif
    }

    if(pCacheData != NULL)
    {
        U16 u16OutCodeLen = 0;
        U16 u16Comsume = 0;
        MEMCPY((void*)&u16OutCodeLen, (void*)pCacheData, sizeof(u16OutCodeLen));
        pCacheData += sizeof(u16OutCodeLen);

        MEMCPY((void*)&u16Comsume, (void*)pCacheData, sizeof(u16Comsume));
        pCacheData += sizeof(u16Comsume);

        if(pu32Features)
        {
            MEMCPY((void*)pu32Features, (void*)pCacheData, sizeof(U32));
        }
        pCacheData += sizeof(U32);

        MEMCPY((void *)pau32Consumed, (void *)pCacheData,u16Comsume*sizeof(U32));
        pCacheData += u16Comsume*sizeof(U32);

        MEMCPY((void *)pu16OutCode, (void *)pCacheData, u16OutCodeLen*sizeof(MLE_WChar));
        return u16OutCodeLen;
    }
#endif //__INDIC_FONT_RULE_CACHE__

    if ( u16ClusterLen > 0 )
    {
        U16 au16ConcertStr[HINDI_CONVERT_MAX] = {0};
        U16 pu16ConcatenationComposedSize[HINDI_CONVERT_MAX] = {0};
        U16 u16ConcatenationComposedSizeMinusCount = 0;
        U16 u16OffsetInConcatenation = 0;
        U16 u16OffsetInComposed = 0;
        U16 u16OutLen = 0;
        S16 i = 0;
        BOOLEAN bIsPreDotted = FALSE;
        U16 u16CheckMoreNum = 0;
        U16 u16MaxConsumedSize = u32SubLen;

        memcpy((void *)au16OrginalCluster, au16Cluster, HINDI_CONVERT_MAX*sizeof(U16));
        u16OriginalClusterLen = u16ClusterLen;

        u16ClusterOffset = _msAPI_MLE_FontHindiRefineCluster(eScript, pu16InTxt, u32InLen, u32Offset, au16Cluster, &u16ClusterLen, u16ClusterOffset, bIsDispStr, &u32FeatureTags, pu16OriginTxt, u32OriginOffset);

#if __FEATURE_VECTOR_FONT__
        if ( msAPI_MLE_FONTBASE_IsVectorFontExist() )
        {
            u16OutLen = _msAPI_MLE_FontHindiVectorRules(eScript, eLang, au16Cluster, u16ClusterLen, u16ClusterOffset, au16ConcertStr, &u16OffsetInConcatenation, &u16OffsetInComposed, pu16ConcatenationComposedSize, &u32FeatureTags);
        }
#endif //__FEATURE_VECTOR_FONT__

        if ( u16OutLen > 0 )
        {
            BOOLEAN bIsTwoPart = FALSE, bIsThreePart = FALSE;

            if ( _msAPI_MLE_FontHindiFeatureWithRphf(eScript, u32FeatureTags, NULL) )
            {
                u16OffsetInConcatenation = 0;
                u16MaxConsumedSize = MAX(u16OutLen, u16MaxConsumedSize);
            }

            if ( _msAPI_MLE_FontHindiFeatureWithLJoin(eScript, u32FeatureTags, &bIsTwoPart) )
            {
                u16OffsetInConcatenation = 0;
                u16MaxConsumedSize = MAX(u16OutLen, u16MaxConsumedSize);
                if ( bIsTwoPart )
                {
                    //pu16ConcatenationComposedSize[0] = 0;
                    if (pu16ConcatenationComposedSize[0] > 0)
                        pu16ConcatenationComposedSize[0]--;
                }

                if ( _msAPI_MLE_FontHindiFeatureWithThreePart(eScript, u32FeatureTags, &bIsThreePart) )
                {
                    if ( bIsThreePart )
                    {
                        if (pu16ConcatenationComposedSize[0] > 0)
                        {
                            pu16ConcatenationComposedSize[0]--;
                        }
                        else
                        {
                            u16ConcatenationComposedSizeMinusCount++;
                        }
                    }
                }
            }

            if ( _msAPI_MLE_FontHindiFeatureWithDotted(eScript, u32FeatureTags, &bIsPreDotted) )
            {
                u16OffsetInConcatenation = 0;
                if ( bIsPreDotted )
                {
                    pu16ConcatenationComposedSize[0] = 0;
                }
                else
                {
                    pu16ConcatenationComposedSize[1] = 0;
                    u16CheckMoreNum = 1;
                }
            }

#ifdef __INDIC_FONT_RULE_CACHE__
            if ( _msAPI_MLE_FontHindiFeatureWithNoCache(eScript, u32FeatureTags, &bNoCached ) )
            {
                if ( bNoCached )
                {
                    bUseCache = FALSE;
                }
            }
#endif

            u16OutLen = (U16)MIN(u32OutLen, u16OutLen);
            for ( i = u16OffsetInConcatenation; i < u16OutLen; i++ )
            {
                if ( pau32Consumed[0] < (U32)(u16MaxConsumedSize + u16CheckMoreNum) )
                {
                    nReturnLen++;
                    pau32Consumed[0] = pau32Consumed[0] + pu16ConcatenationComposedSize[i];
                    pau32Consumed[nReturnLen] = pu16ConcatenationComposedSize[i];
                }
                else
                {
                    break;
                }
            }

            if ( pau32Consumed[0] >= u16ConcatenationComposedSizeMinusCount )
                pau32Consumed[0] -= u16ConcatenationComposedSizeMinusCount;

            MEMCPY((void *)pu16OutCode, (void *)(au16ConcertStr + u16OffsetInConcatenation), sizeof(U16) * nReturnLen);
        }
        else
        {
            nReturnLen = 1;
            pau32Consumed[0] = 1;
            pau32Consumed[1] = 1;
            pu16OutCode[0] = au16Cluster[u16ClusterOffset];
        }
#ifdef __INDIC_FONT_RULE_CACHE__
        if( (bUseCache) && (!bKeyDuplicate) )
        {
            msAPI_MLE_FONTBASE_Vector_InsertHindiCache(u32Offset, au16OrginalCluster, u16OriginalClusterLen, pu16OutCode, nReturnLen, pau32Consumed, u32FeatureTags);
        }
#endif //__INDIC_FONT_RULE_CACHE__
    }

    if ( pu32Features )
    {
        *pu32Features = u32FeatureTags;
    }

    return nReturnLen;
}

BOOLEAN _msAPI_MLE_FontHindiGetNextCodeXOffset( HindiScript_e eScript, U16 *pu16CurrentRefChar, U16 *pu16CurrentCharRefWidth, U16 u16NextChar, U16 u16NextCharWidth, S16 *ps16XOffset, U16 u16BaseWidth, U16 u16PreChar, BOOLEAN bFirstCharInCluster)
{
    BOOLEAN bReturn = TRUE;
    BOOLEAN bResult = FALSE;
    U16 u16TempBaseWidth = ((u16BaseWidth > 0) ? (u16BaseWidth): *pu16CurrentCharRefWidth);
    U16 u16HalfTempBaseWidth = u16TempBaseWidth/2;
    U16 u16QuarTempBaseWidth = u16TempBaseWidth/4;
    S16 s16OriginalOffset;
    U16 i;

    if( ps16XOffset )//fix coverity 203958
    {
        s16OriginalOffset = *ps16XOffset;
    }
    else
    {
        return FALSE;
    }


    if ( ps16XOffset == NULL || pu16CurrentRefChar == NULL || pu16CurrentCharRefWidth == NULL )
    {
        return FALSE;
    }

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return FALSE;
    }

    for ( i = 0; i < HINDI_MAX_SCRIPT_NUM; i++ )
    {
        if ( g_pHindiLangsTbl[i] == NULL )
        {
            break;
        }

        if ( g_pHindiLangsTbl[i]->eScript == eScript )
        {
            if ( g_pHindiLangsTbl[i]->fnGetNextCodeXOffset )
            {
                bResult = g_pHindiLangsTbl[i]->fnGetNextCodeXOffset(pu16CurrentRefChar, pu16CurrentCharRefWidth, u16NextChar, u16NextCharWidth, ps16XOffset, u16BaseWidth, u16PreChar, bFirstCharInCluster);
            }
            break;
        }
    }

    if ( bResult || bFirstCharInCluster == TRUE)
    {
        return TRUE;
    }

    if ( (u16NextChar != FONT_CONTROL_ZWJ) && (u16NextChar != FONT_CONTROL_ZWNJ) )
    {
        HindiSpecialCharacter_e eNextSpType = _msAPI_MLE_FontHindiGetCharSpecialType(eScript, u16NextChar);
        HindiSpecialCharacter_e eCurrentSpType = _msAPI_MLE_FontHindiGetCharSpecialType(eScript, *pu16CurrentRefChar);
        HindiOtherCharacterType_e eCurrentOtherType = _msAPI_MLE_FontHindiGetCharOtherType(eScript, *pu16CurrentRefChar);

        switch ( _msAPI_MLE_FontHindiGetCharType(eScript, u16NextChar) )
        {
            case HINDI_DEPVOW:
                switch ( eNextSpType )
                {
                    case HINDI_SP_RIGHT_JOINER:
                    {
                        if( eCurrentSpType == HINDI_SP_RIGHT_T || eCurrentSpType == HINDI_SP_DOUBLE_T )
                        {
                            *ps16XOffset = *ps16XOffset + (*pu16CurrentCharRefWidth - (u16NextCharWidth - u16TempBaseWidth));
                        }
                        else if( ( IS_BENGALI_RANGE(*pu16CurrentRefChar) )
                            && ( IS_BENGALI_RANGE(u16NextChar) ))
                        {
                            *ps16XOffset = *ps16XOffset + (*pu16CurrentCharRefWidth - (u16NextCharWidth - u16TempBaseWidth));
                        }
                        else
                        {
                            *ps16XOffset = *ps16XOffset + (*pu16CurrentCharRefWidth - (u16NextCharWidth - u16TempBaseWidth) - u16HalfTempBaseWidth);
                        }

                        *pu16CurrentRefChar = u16NextChar;
                        *pu16CurrentCharRefWidth = u16TempBaseWidth;
                        break;
                    }

                    case HINDI_SP_TWOPART_JOINER:
                    case HINDI_SP_LEFT_JOINER:
                    {
                        *ps16XOffset = *ps16XOffset + *pu16CurrentCharRefWidth;
                        *pu16CurrentCharRefWidth = MAX(*pu16CurrentCharRefWidth, u16NextCharWidth);
                        break;
                    }

                    case HINDI_SP_CENTER_T_UP_POS:
                    {
                        if( eCurrentSpType == HINDI_SP_RIGHT_T )
                        {
                            if ( *pu16CurrentCharRefWidth >= (u16NextCharWidth + u16HalfTempBaseWidth) )
                            {
                                *ps16XOffset = *ps16XOffset + *pu16CurrentCharRefWidth - u16HalfTempBaseWidth - u16NextCharWidth;
                            }
                            else
                            {
                                *ps16XOffset = *ps16XOffset + (*pu16CurrentCharRefWidth - u16NextCharWidth);
                            }
                        }
                        else if ( eCurrentSpType == HINDI_SP_DOUBLE_T )
                        {
                            if ( *pu16CurrentCharRefWidth >= (u16NextCharWidth + u16QuarTempBaseWidth) )
                            {
                                *ps16XOffset = *ps16XOffset + *pu16CurrentCharRefWidth - u16QuarTempBaseWidth - u16NextCharWidth;
                            }
                            else
                            {
                                *ps16XOffset = *ps16XOffset + (*pu16CurrentCharRefWidth - u16NextCharWidth);
                            }
                        }
                        else
                        {
                            if ( u16NextCharWidth <= *pu16CurrentCharRefWidth )
                            {
                                *ps16XOffset = *ps16XOffset + ((*pu16CurrentCharRefWidth + 1 - u16NextCharWidth)/2);
                            }
                            else
                            {
                                *ps16XOffset = *ps16XOffset + (*pu16CurrentCharRefWidth - u16NextCharWidth);
                            }
                        }
                        *pu16CurrentCharRefWidth = MAX(*pu16CurrentCharRefWidth, (*ps16XOffset - s16OriginalOffset) + u16NextCharWidth);
                        break;
                    }

                    case HINDI_SP_CENTER_T_DOWN_POS:
                    {
                        if ( eCurrentOtherType == HINDI_OTYPE_DEPVOW_LONG_DOWN_CHAR )
                        {
                            if ( eCurrentSpType == HINDI_SP_RIGHT_T || eCurrentSpType == HINDI_SP_DOUBLE_T )
                            {
                                eCurrentSpType = HINDI_SP_CENTER_T;
                            }
                            else
                            {
                                eCurrentSpType = HINDI_SP_DOUBLE_T;
                            }
                        }

                        if( eCurrentSpType == HINDI_SP_RIGHT_T )
                        {
                            if ( *pu16CurrentCharRefWidth >= (u16NextCharWidth + u16HalfTempBaseWidth) )
                            {
                                *ps16XOffset = *ps16XOffset + *pu16CurrentCharRefWidth - u16HalfTempBaseWidth - u16NextCharWidth;
                            }
                            else
                            {
                                *ps16XOffset = *ps16XOffset + (*pu16CurrentCharRefWidth - u16NextCharWidth);
                            }
                        }
                        else if ( eCurrentSpType == HINDI_SP_DOUBLE_T )
                        {
                            if ( *pu16CurrentCharRefWidth >= (u16NextCharWidth + u16QuarTempBaseWidth) )
                            {
                                *ps16XOffset = *ps16XOffset + *pu16CurrentCharRefWidth - u16QuarTempBaseWidth - u16NextCharWidth;
                            }
                            else
                            {
                                *ps16XOffset = *ps16XOffset + (*pu16CurrentCharRefWidth - u16NextCharWidth);
                            }
                        }
                        else
                        {
                            if ( u16NextCharWidth <= *pu16CurrentCharRefWidth )
                            {
                                *ps16XOffset = *ps16XOffset + ((*pu16CurrentCharRefWidth + 1 - u16NextCharWidth)/2);
                            }
                            else
                            {
                                *ps16XOffset = *ps16XOffset + (*pu16CurrentCharRefWidth - u16NextCharWidth);
                            }
                        }
                        *pu16CurrentCharRefWidth = MAX(*pu16CurrentCharRefWidth, (*ps16XOffset - s16OriginalOffset) + u16NextCharWidth);
                        break;
                    }

                    case HINDI_SP_LEFT_T_UP_POS:
                    case HINDI_SP_LEFT_T_DOWN_POS:
                    {
                        if( eCurrentSpType == HINDI_SP_RIGHT_T )
                        {
                            if ( *pu16CurrentCharRefWidth >= (u16NextCharWidth + u16HalfTempBaseWidth) )
                            {
                                *ps16XOffset = *ps16XOffset + *pu16CurrentCharRefWidth - + u16HalfTempBaseWidth - u16NextCharWidth;
                            }
                            else
                            {
                                *ps16XOffset = *ps16XOffset + (*pu16CurrentCharRefWidth - u16NextCharWidth);
                            }
                        }
                        else if ( eCurrentSpType == HINDI_SP_DOUBLE_T )
                        {
                            if ( *pu16CurrentCharRefWidth >= (u16NextCharWidth + u16QuarTempBaseWidth) )
                            {
                                *ps16XOffset = *ps16XOffset + *pu16CurrentCharRefWidth - u16QuarTempBaseWidth - u16NextCharWidth;
                            }
                            else
                            {
                                *ps16XOffset = *ps16XOffset + (*pu16CurrentCharRefWidth - u16NextCharWidth);
                            }
                        }
                        else
                        {
                            if ( *ps16XOffset + ((*pu16CurrentCharRefWidth)/2) >= u16NextCharWidth )
                            {
                                *ps16XOffset = *ps16XOffset + ((*pu16CurrentCharRefWidth)/2) - u16NextCharWidth;
                            }
                            else
                            {
                                *ps16XOffset = *ps16XOffset + 0;
                            }
                        }
                        *pu16CurrentCharRefWidth = MAX(*pu16CurrentCharRefWidth, (*ps16XOffset - s16OriginalOffset) + u16NextCharWidth);
                        break;
                    }

                    case HINDI_SP_RIGHT_T_DOWN_POS:
                    {
                        *ps16XOffset = *ps16XOffset + *pu16CurrentCharRefWidth;
                        *pu16CurrentCharRefWidth = *pu16CurrentCharRefWidth + u16NextCharWidth;
                        break;
                    }

                    default:
                    {
                        *ps16XOffset = *ps16XOffset + *pu16CurrentCharRefWidth;
                        *pu16CurrentRefChar = u16NextChar;
                        *pu16CurrentCharRefWidth = u16NextCharWidth;
                        break;
                    }
                }
                break;

            case HINDI_HALANT:
            case HINDI_SIGN:
                switch ( eNextSpType )
                {
                    case HINDI_SP_RIGHT_JOINER:
                    {
                        *ps16XOffset = *ps16XOffset + *pu16CurrentCharRefWidth;
                        *pu16CurrentRefChar = u16NextChar;
                        *pu16CurrentCharRefWidth = u16NextCharWidth;
                        break;
                    }

                    case HINDI_SP_LEFT_T_DOWN_POS:
                    {
                        *pu16CurrentCharRefWidth = MAX(*pu16CurrentCharRefWidth, u16NextCharWidth);
                        break;
                    }

                    case HINDI_SP_LEFT_T_UP_POS:
                    {
                        HindiSpecialCharacter_e ePreSpType = HINDI_SP_INVALID;

                        if ( u16PreChar > 0 && u16PreChar != (*pu16CurrentRefChar) )
                        {
                            ePreSpType = _msAPI_MLE_FontHindiGetCharSpecialType(eScript, u16PreChar);
                        }

                        if ( ePreSpType == HINDI_SP_CENTER_T_UP_POS )
                        {
                            if ( u16NextCharWidth < (*pu16CurrentCharRefWidth)/2 )
                            {
                                *ps16XOffset = *ps16XOffset + ((*pu16CurrentCharRefWidth)/2) - u16NextCharWidth;
                            }
                        }
                        else
                        {
                            if ( *pu16CurrentCharRefWidth >= (u16NextCharWidth + u16HalfTempBaseWidth) )
                            {
                                *ps16XOffset = *ps16XOffset + *pu16CurrentCharRefWidth - u16HalfTempBaseWidth - u16NextCharWidth;
                            }
                            else
                            {
                                *ps16XOffset = *ps16XOffset + (*pu16CurrentCharRefWidth - u16NextCharWidth);
                            }
                        }
                        break;
                    }

                    case HINDI_SP_RIGHT_POS:
                    {
                        *ps16XOffset = *ps16XOffset + *pu16CurrentCharRefWidth;
                        *pu16CurrentRefChar = u16NextChar;
                        *pu16CurrentCharRefWidth = u16NextCharWidth;
                        break;
                    }

                    default:
                    {
                        if( eCurrentSpType == HINDI_SP_RIGHT_T )
                        {
                            if ( *pu16CurrentCharRefWidth >= (u16NextCharWidth + u16HalfTempBaseWidth) )
                            {
                                *ps16XOffset = *ps16XOffset + *pu16CurrentCharRefWidth - u16HalfTempBaseWidth - u16NextCharWidth;
                            }
                            else
                            {
                                *ps16XOffset = *ps16XOffset + (*pu16CurrentCharRefWidth - u16NextCharWidth);
                            }
                        }
                        else if ( eCurrentSpType == HINDI_SP_DOUBLE_T   )
                        {
                            if ( *pu16CurrentCharRefWidth >= (u16NextCharWidth + u16QuarTempBaseWidth) )
                            {
                                *ps16XOffset = *ps16XOffset + *pu16CurrentCharRefWidth - u16QuarTempBaseWidth - u16NextCharWidth;
                            }
                            else
                            {
                                *ps16XOffset = *ps16XOffset + (*pu16CurrentCharRefWidth - u16NextCharWidth);
                            }
                        }
                        else if ( (_msAPI_MLE_FontHindiGetCharType(eScript, *pu16CurrentRefChar) == HINDI_NUM) || eCurrentSpType == HINDI_SP_SINGLE_INDVOW )
                        {
                            *ps16XOffset = *ps16XOffset + *pu16CurrentCharRefWidth;
                        }
                        else
                        {
                            if ( u16NextCharWidth <= *pu16CurrentCharRefWidth )
                            {
                                if ( eCurrentOtherType == HINDI_OTYPE_CON_SMALL_CHAR && eNextSpType == HINDI_SP_CENTER_T_UP_POS )
                                {
                                    *ps16XOffset = *ps16XOffset + ((*pu16CurrentCharRefWidth + 1 - u16NextCharWidth)/2) + u16QuarTempBaseWidth;
                                }
                                else
                                {
                                    *ps16XOffset = *ps16XOffset + ((*pu16CurrentCharRefWidth + 1 - u16NextCharWidth)/2);
                                }
                            }
                            else
                            {
                                *ps16XOffset = *ps16XOffset + (*pu16CurrentCharRefWidth - u16NextCharWidth);
                            }
                        }
                        *pu16CurrentCharRefWidth = MAX(*pu16CurrentCharRefWidth, (*ps16XOffset - s16OriginalOffset) + u16NextCharWidth);
                        break;
                    }
                }
                break;

            default:
                *ps16XOffset = *ps16XOffset + *pu16CurrentCharRefWidth;
                *pu16CurrentRefChar = u16NextChar;
                *pu16CurrentCharRefWidth = u16NextCharWidth;
                break;
        }
    }
    else
    {
        HindiCharacter_e eRefCharType = _msAPI_MLE_FontHindiGetCharType(eScript, *pu16CurrentRefChar);

        if ( eRefCharType != HINDI_INVALID )
        {
            *ps16XOffset = *ps16XOffset + *pu16CurrentCharRefWidth;
        }
        else
        {
            bReturn = FALSE;
        }
    }

    return bReturn;
}

/**
 *@FUNCTION         _FontBengaliGetCodeDrawWidth
 *@DESCRIPTION
 *@AUTHOR           anning.deng@mstarsemi.com
 *@DATA             2010-11-01
 *@PARAMETERS
        [IN] u16Character       current char
        [IN] u16CharWidth   current char's width
        [IN] u16NextChar    next char
        [IN] u16BaseWidth   base char width
 *@RETURN           code's draw width
 */
BOOLEAN _msAPI_MLE_FontHindiGetCodeDrawWidth( HindiScript_e eScript, U32 nLen, U16 u16Character, U16 u16CharWidth, U16 u16NextChar, U16 u16BaseWidth, U16 *pu16Width )
{
    U16 u16ReturnWidth = u16CharWidth;
    HindiSpecialCharacter_e eSpType = HINDI_SP_INVALID;
    HindiSpecialCharacter_e eNextSpType = HINDI_SP_INVALID;

    if ( eScript >= HINDI_MAX_SCRIPT_NUM || pu16Width == NULL )
    {
        return FALSE;
    }

    if(nLen <= 1)
    {
        if( ( IS_BENGALI_RANGE(u16Character) )
            || ( IS_BENGALI_RANGE(u16NextChar) ))
        {
            *pu16Width = u16ReturnWidth;
            return TRUE;
        }
    }

    eSpType = _msAPI_MLE_FontHindiGetCharSpecialType(eScript, u16Character);
    eNextSpType = _msAPI_MLE_FontHindiGetCharSpecialType(eScript, u16NextChar);
    if ( eSpType == HINDI_SP_LEFT_JOINER || eSpType == HINDI_SP_TWOPART_JOINER )
    {
        if ( !_msAPI_MLE_FontHindiCharIsComposed(eScript, u16NextChar)
             && eNextSpType != HINDI_SP_LEFT_JOINER
             && eNextSpType != HINDI_SP_RIGHT_JOINER
             && eNextSpType != HINDI_SP_TWOPART_JOINER
             && u16NextChar != FONT_CONTROL_ZWJ && u16NextChar != FONT_CONTROL_ZWNJ )
        {
            u16ReturnWidth = u16BaseWidth - 1;
        }
    }

    *pu16Width = u16ReturnWidth;
    return TRUE;
}

BOOLEAN _msAPI_MLE_FontHindiReorderStr( HindiScript_e eScript, const U16 *pu16Str, U16 u16StrLen, U16 u16StrIndex, const U16 *pu16Seq, U16 **ppu16OrderSeg, U16 *pu16InOrderOffset, BOOLEAN bIsDispStr )
{
    U16 u16CurrentIndex = 0;
    S32 s326RemainLen = u16StrLen;
    U16 u16ClusterSize = 0;
    U16 u16ConsumedCount = 0;
    U16 au16Cluster[HINDI_CONVERT_MAX] = {0,};
    U16 au16ClusterSeq[HINDI_CONVERT_MAX] = {0,};
    U16 au16TempClusterSeq[HINDI_CONVERT_MAX] = {0,};
    U16 i = 0;
    BOOLEAN bIsOrdered = FALSE;
    U32 u32Len = 0;
    U32 u32InfBufferSize = u16StrLen + MAX_CODE_COUNT;

    if ( pu16Str == NULL || u16StrLen == 0 || pu16Seq == NULL || ppu16OrderSeg == NULL )
    {
        return FALSE;
    }

    *ppu16OrderSeg = (U16 *)MALLOC(sizeof(U16) * u32InfBufferSize);

    if ( *ppu16OrderSeg == NULL )
    {
        return FALSE;
    }
    MEMSET((void *)(*ppu16OrderSeg), 0, u32InfBufferSize * sizeof(U16));

    while ( s326RemainLen > 0 )
    {
        U32 u32FeatureTags = 0;
        HindiScript_e eTempScript = msAPI_MLE_FontHindiGetCharScript(pu16Str[u16CurrentIndex]);

        if ( eScript != eTempScript )
        {
            break;
        }

        u16ClusterSize = _msAPI_MLE_FontHindiGetCluster(eScript, (pu16Str + u16CurrentIndex), s326RemainLen, au16Cluster, HINDI_CONVERT_MAX, &u16ConsumedCount, au16ClusterSeq, bIsDispStr, &u32FeatureTags);

        if ( u16ClusterSize > 0 )
        {
            BOOLEAN bIsTwoPart = FALSE;

            bIsOrdered = TRUE;

            if ( _msAPI_MLE_FontHindiFeatureWithLJoin(eScript, u32FeatureTags, &bIsTwoPart) )
            {
                if ( bIsTwoPart )
                {
                    au16TempClusterSeq[0] = pu16Seq[u16CurrentIndex];
                    for ( i = 1; i < u16ClusterSize; i++ )
                    {
                        au16TempClusterSeq[i] = pu16Seq[u16CurrentIndex + au16ClusterSeq[i]];
                    }
                }
                else
                {
            for ( i = 0; i < u16ClusterSize; i++ )
            {
                au16TempClusterSeq[i] = pu16Seq[u16CurrentIndex + au16ClusterSeq[i]];
            }
                }
            }
            else if ( _msAPI_MLE_FontHindiFeatureWithDotted(eScript, u32FeatureTags, NULL) )
            {
                au16TempClusterSeq[0] = pu16Seq[u16CurrentIndex];
                au16TempClusterSeq[1] = pu16Seq[u16CurrentIndex];
                for ( i = 2; i < u16ClusterSize; i++ )
                {
                    au16TempClusterSeq[i] = pu16Seq[u16CurrentIndex + au16ClusterSeq[i]];
                }
            }
            else
            {
                for ( i = 0; i < u16ClusterSize; i++ )
                {
                    au16TempClusterSeq[i] = pu16Seq[u16CurrentIndex + au16ClusterSeq[i]];
                }
            }
        }
        else
        {
            au16TempClusterSeq[0] = u16CurrentIndex;
            u16ClusterSize = 1;
            u16ConsumedCount = 1;
        }

        if ( pu16InOrderOffset && u16CurrentIndex <= u16StrIndex && (u16CurrentIndex + u16ConsumedCount) > u16StrIndex )
        {
            *pu16InOrderOffset = u32Len + _msAPI_MLE_FontHindiGetIndexInSequence(au16ClusterSeq, u16ClusterSize, u16StrIndex - u16CurrentIndex);
        }

        s326RemainLen = s326RemainLen - u16ConsumedCount;
        u16CurrentIndex = u16CurrentIndex + u16ConsumedCount;
            if ( u32InfBufferSize < (u16ClusterSize + u32Len) )
            {
                U32 u32TempInBufferSize = u32InfBufferSize;

                u32InfBufferSize = u16ClusterSize + u32Len + MAX_CODE_COUNT;
                *ppu16OrderSeg = (U16 *)REALLOC((void *)(*ppu16OrderSeg), u32InfBufferSize * sizeof(U16));
            MEMSET((void *)((*ppu16OrderSeg) + u32TempInBufferSize), 0, (u32InfBufferSize - u32TempInBufferSize) * sizeof(U16));
        }

        MEMCPY(((*ppu16OrderSeg) + u32Len), au16TempClusterSeq, sizeof(U16) * u16ClusterSize);
        u32Len = u32Len + u16ClusterSize;
    }

    return bIsOrdered;
}

BOOLEAN _msAPI_MLE_FontHindiNextComposedChars( HindiScript_e eScript, LE_LanguageTag_e eLang, const U16 *pString, U32 nStrLen, U32 nOffset, U16 *pwComposedStr, U32 *pComposedLen, U32 *paConsumed, BOOLEAN bDispStr, U16 u16OutBufferSize )
{
    U32 nOutStrLen = 0;
    U16 u16OutLen = 0;
    U16 u16ClusterSize = 0;
    U16 u16ClusterOffset = 0;
    U16 au16ClusterStr[HINDI_CONVERT_MAX] = {0,};
    U32 u32FeatureTags = 0;
    BOOLEAN bReturnValue = FALSE;

    if ( pString == NULL || nStrLen == 0 || nOffset >= (nStrLen - 1) || u16OutBufferSize == 0 || paConsumed == NULL )
    {
        return FALSE;
    }

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return FALSE;
    }

    u16ClusterOffset = _msAPI_MLE_FontHindiGetClusterStartOffset(eScript, pString, nStrLen, nOffset, au16ClusterStr, &u16ClusterSize, bDispStr, &u32FeatureTags);

    if ( u16ClusterSize > 1 )
    {
        U16 au16OutputStr[HINDI_CONVERT_MAX] = {0,};
        U16 pu16ConcatenationComposedSize[HINDI_CONVERT_MAX] = {0};
        U32 nTempHindiConsumed[HINDI_CONVERT_MAX] = {0};
        U16 u16TempHindiOutLen = 0;
        U16 u16OffsetInConcatenation = 0;
        U16 u16OffsetInComposed = 0;
        U16 u16OutOffset = 0;
        U16 u16OrderConCharOffset = 0;
        U16 u16FirstOutputStringCharOffset = 0;
        BOOLEAN bOrderConCharMatched = FALSE;
        S16 i = 0;

        u16OutLen = _msAPI_MLE_FontHindiRules( eScript, eLang, au16ClusterStr, u16ClusterSize, u16ClusterOffset, au16OutputStr, &u16OffsetInConcatenation, &u16OffsetInComposed, pu16ConcatenationComposedSize, &u32FeatureTags );
        if ( u16OutLen == 0 )
        {
            return FALSE;
        }

        u16OrderConCharOffset = u16OffsetInConcatenation;
        do
        {
            //If the order con character is in output string, the display sequence is changed
            if ( _msAPI_MLE_FontHindiFeatureWithRphf(eScript, u32FeatureTags, NULL) )
            {
                u16OrderConCharOffset = u16OutLen - 1;
                bOrderConCharMatched = TRUE;
            }

            if ( bOrderConCharMatched )
            {
                //0x0930, 0x094D, 0x09X1, 0x09X2 ==> 0x09X1, 0x09X2, 0x0930, 0x094D
                if ( u16OffsetInConcatenation < u16OrderConCharOffset )
                {
                    //offset is the 0x09X1 in 0x09X1, 0x09X2, 0x0930, 0x094D
                    nOutStrLen = 1;
                    paConsumed[0] = pu16ConcatenationComposedSize[u16OffsetInConcatenation] - u16OffsetInComposed;
                    nTempHindiConsumed[0] = paConsumed[0];

                    //calculate from 0x09X1 to 0x09X2 (not include 0x0930, 0x094D)
                    for ( i = u16OffsetInConcatenation + 1; i < u16OrderConCharOffset; i++ )
                    {
                        if ( nOutStrLen >= u16OutBufferSize )
                        {
                            break;
                        }

                        paConsumed[0] = paConsumed[0] + pu16ConcatenationComposedSize[i];
                        nTempHindiConsumed[nOutStrLen] = pu16ConcatenationComposedSize[i];
                        nOutStrLen++;
                    }

                    u16OutOffset = u16OffsetInConcatenation;
                }
                else
                {
                    //offset is the 0x0930 in 0x09X1, 0x09X2, 0x0930, 0x094D
                    //Find the first character of order_con string (0x09X1)
                    for ( i = u16OrderConCharOffset - 1; i >= 0; i-- )
                    {
                        if ( (i < u16OrderConCharOffset - 1)
                             && (_msAPI_MLE_FontHindiCharIsComposed(eScript, au16OutputStr[i])
                                 || ( i == 0 && _msAPI_MLE_FontHindiFeatureWithLJoin(eScript, u32FeatureTags, NULL))) )
                        {
                            break;
                        }
                        u16FirstOutputStringCharOffset = i;
                    }

                    //calculate the order_con string length
                    nOutStrLen = 0;
                    paConsumed[0] = 0;
                    //The case is 0x0947, 0x0930, 0x094D
                    for ( i = u16FirstOutputStringCharOffset; i < u16OrderConCharOffset; i++ )
                    {
                        if ( nOutStrLen >= u16OutBufferSize )
                        {
                            break;
                        }

                        paConsumed[0] = paConsumed[0] + pu16ConcatenationComposedSize[i];
                        nTempHindiConsumed[nOutStrLen] = pu16ConcatenationComposedSize[i];
                        nOutStrLen++;
                    }

                    if ( nOutStrLen >= u16OutBufferSize )
                    {
                        break;
                    }

                    if ( pu16ConcatenationComposedSize[u16OffsetInConcatenation] > 2 && u16OffsetInComposed <= pu16ConcatenationComposedSize[u16OffsetInConcatenation] - 2 )
                    {
                        paConsumed[0] = paConsumed[0] + pu16ConcatenationComposedSize[u16OffsetInConcatenation] - u16OffsetInComposed + 1;
                        nTempHindiConsumed[nOutStrLen] = pu16ConcatenationComposedSize[u16OffsetInConcatenation] - u16OffsetInComposed + 1;
                    }
                    else
                    {
                        paConsumed[0] = paConsumed[0] + pu16ConcatenationComposedSize[u16OffsetInConcatenation] - u16OffsetInComposed;
                        nTempHindiConsumed[nOutStrLen] = pu16ConcatenationComposedSize[u16OffsetInConcatenation] - u16OffsetInComposed;
                    }
                    nOutStrLen++;

                    u16OutOffset = u16FirstOutputStringCharOffset;
                }
                u16OffsetInConcatenation = u16OrderConCharOffset;
            }
            else
            {
                nOutStrLen = 1;
                paConsumed[0] = pu16ConcatenationComposedSize[u16OffsetInConcatenation] - u16OffsetInComposed;
                nTempHindiConsumed[0] = paConsumed[0];
                u16OutOffset = u16OffsetInConcatenation;
            }

            if ( nOutStrLen >= u16OutBufferSize )
            {
                break;
            }

            u16TempHindiOutLen = nOutStrLen;

            //find the right join character
            if ( u16OffsetInConcatenation > 0 && _msAPI_MLE_FontHindiFeatureWithLJoin(eScript, u32FeatureTags, NULL) )
            {
                nOutStrLen++;
                paConsumed[0] = paConsumed[0] + pu16ConcatenationComposedSize[0];
                paConsumed[1] = pu16ConcatenationComposedSize[0];

                MEMCPY((void *)(paConsumed + 2), (void *)nTempHindiConsumed, sizeof(U32) * u16TempHindiOutLen);
                for ( i = u16OffsetInConcatenation + 1; i < u16OutLen; i++ )
                {
                    if ( nOutStrLen >= u16OutBufferSize )
                    {
                        break;
                    }

                    nOutStrLen++;
                    paConsumed[0] = paConsumed[0] + pu16ConcatenationComposedSize[i];
                    paConsumed[nOutStrLen] = pu16ConcatenationComposedSize[i];
                }
            }
            else
            {
                MEMCPY((void *)(paConsumed + 1), (void *)nTempHindiConsumed, sizeof(U32) * u16TempHindiOutLen);

                for ( i = u16OffsetInConcatenation + 1; i < u16OutLen; i++ )
                {
                    if ( !_msAPI_MLE_FontHindiCharIsComposed(eScript, au16OutputStr[i]) && au16OutputStr[i] != FONT_CONTROL_ZWJ && au16OutputStr[i] != FONT_CONTROL_ZWNJ )
                    {
                        break;
                    }

                    if ( nOutStrLen >= u16OutBufferSize )
                    {
                        break;
                    }

                    nOutStrLen++;
                    paConsumed[0] = paConsumed[0] + pu16ConcatenationComposedSize[i];
                    paConsumed[nOutStrLen] = pu16ConcatenationComposedSize[i];
                }
            }
        }while ( FALSE );

        if ( paConsumed[0] > 1 )
        {
            if ( _msAPI_MLE_FontHindiFeatureWithLJoin(eScript, u32FeatureTags, NULL) && u16OutOffset > 0 )
            {
                pwComposedStr[0] = au16OutputStr[0];
                nOutStrLen--;
                MEMCPY((void *)(pwComposedStr + 1), (void *)(au16OutputStr + u16OutOffset), sizeof(U16) * nOutStrLen);
            }
            else
            {
                MEMCPY((void *)pwComposedStr, (void *)(au16OutputStr + u16OutOffset), sizeof(U16) * nOutStrLen);
            }

            if ( pComposedLen )
            {
                *pComposedLen = nOutStrLen;
            }
            bReturnValue = TRUE;
        }
    }

    return bReturnValue;
}

//pString is input order string
BOOLEAN _msAPI_MLE_FontHindiPreComposedChars( HindiScript_e eScript, LE_LanguageTag_e eLang, const U16 *pString, U32 nStrLen, U32 nOffset, U16 *pComposedStr, U32 *pComposedLen, U32 *pConsumed, BOOLEAN bDispStr, U16 u16OutBufferSize )
{
    U32 nOutStrLen = 0;
    U16 u16ClusterSize = 0;
    U16 u16ClusterOffset = 0;
    U16 au16ClusterStr[HINDI_CONVERT_MAX] = {0,};
    U16 u16OutLen = 0;
    U32 nTempHindiConsumed[HINDI_CONVERT_MAX] = {0};
    U16 u16TempHindiOutLen = 0;
    U32 u32FeatureTags = 0;
    BOOLEAN bReturnValue = FALSE;

    if ( pString == NULL || nStrLen == 0 || nOffset >= nStrLen || nOffset == 0 || pConsumed == NULL )
    {
        return FALSE;
    }

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return FALSE;
    }

    u16ClusterOffset = _msAPI_MLE_FontHindiGetClusterStartOffset(eScript, pString, nStrLen, nOffset, au16ClusterStr, &u16ClusterSize, bDispStr, &u32FeatureTags);

    if ( u16ClusterSize > 1 )
    {
        U16 au16OutputStr[HINDI_CONVERT_MAX] = {0,};
        U16 pu16ConcatenationComposedSize[HINDI_CONVERT_MAX] = {0};
        U16 u16OffsetInConcatenation = 0;
        U16 u16OffsetInComposed = 0;
        U16 u16OutOffset = 0;
        U16 u16OrderConCharOffset = 0;
        U16 u16FirstOutputStringCharOffset = 0;
        BOOLEAN bOrderConCharMatched = FALSE;
        S16 i = 0;

        u16OutLen = _msAPI_MLE_FontHindiRules( eScript, eLang, au16ClusterStr, u16ClusterSize, u16ClusterOffset, au16OutputStr, &u16OffsetInConcatenation, &u16OffsetInComposed, pu16ConcatenationComposedSize, &u32FeatureTags );
        if ( u16OutLen == 0 )
        {
            return FALSE;
        }

        u16OrderConCharOffset = u16OffsetInConcatenation;
        do
        {
            //If the order con character is in output string, the display sequence is changed
            if ( _msAPI_MLE_FontHindiFeatureWithRphf(eScript, u32FeatureTags, NULL) )
            {
                u16OrderConCharOffset = u16OutLen - 1;
                bOrderConCharMatched = TRUE;
            }

            if ( bOrderConCharMatched )
            {
                u16FirstOutputStringCharOffset = u16OffsetInConcatenation;

                //0x0930, 0x094D, 0x09XX, 0x09XX ==> 0x09XX, 0x09XX, 0x0930, 0x094D
                if ( u16OffsetInConcatenation < u16OrderConCharOffset )
                {
                    //offset is the 0x09X2 in 0x09X1, 0x09X2, 0x0930, 0x094D
                    //Find the first character that is non sign character
                    u16FirstOutputStringCharOffset = u16OffsetInConcatenation;
                    for ( i = u16OffsetInConcatenation - 1; i >= 0; i-- )
                    {
                        if ( (i < u16OrderConCharOffset - 1)
                             && (_msAPI_MLE_FontHindiCharIsComposed(eScript, au16OutputStr[i])
                                || ( i == 0 && _msAPI_MLE_FontHindiFeatureWithLJoin(eScript, u32FeatureTags, NULL))) )
                        {
                            break;
                        }
                        u16FirstOutputStringCharOffset = i;
                    }

                    //calculate the order_con string length (not include 0x0930, 0x094D)
                    nOutStrLen = 1;
                    pConsumed[0] = u16OffsetInComposed + 1;
                    nTempHindiConsumed[u16OffsetInConcatenation - u16FirstOutputStringCharOffset] = pConsumed[0];
                    for ( i = u16OffsetInConcatenation - 1; i >= u16FirstOutputStringCharOffset; i-- )
                    {
                        if ( nOutStrLen >= u16OutBufferSize )
                        {
                            break;
                        }

                        pConsumed[0] = pConsumed[0] + pu16ConcatenationComposedSize[i];
                        nTempHindiConsumed[i - u16FirstOutputStringCharOffset] = pu16ConcatenationComposedSize[i];
                        nOutStrLen++;
                    }

                    if ( nOutStrLen >= u16OutBufferSize )
                    {
                        break;
                    }

                    //add the 0x0930, 0x094D
                    pConsumed[0] = pConsumed[0] + pu16ConcatenationComposedSize[u16OrderConCharOffset];
                    nTempHindiConsumed[nOutStrLen] = pu16ConcatenationComposedSize[u16OrderConCharOffset];
                    nOutStrLen++;

                    u16OutOffset = u16FirstOutputStringCharOffset;
                }
                else
                {
                    //The case is 0x0947, 0x0930, 0x094D
                    if ( pu16ConcatenationComposedSize[u16OffsetInConcatenation] > 2 && u16OffsetInComposed <= pu16ConcatenationComposedSize[u16OffsetInConcatenation] - 2 )
                    {
                        //Find the first character that is non sign character
                        for ( i = u16OrderConCharOffset - 1; i >= 0; i-- )
                        {
                            if ( (i < u16OrderConCharOffset - 1)
                                 && (_msAPI_MLE_FontHindiCharIsComposed(eScript, au16OutputStr[i])
                                    || ( i == 0 && _msAPI_MLE_FontHindiFeatureWithLJoin(eScript, u32FeatureTags, NULL))) )
                            {
                                break;
                            }
                            u16FirstOutputStringCharOffset = i;
                        }

                        nOutStrLen = 0;
                        pConsumed[0] = 0;
                        for ( i = u16FirstOutputStringCharOffset; i < u16OffsetInConcatenation; i++ )
                        {
                            if ( nOutStrLen >= u16OutBufferSize )
                            {
                                break;
                            }
                            pConsumed[0] = pConsumed[0] + pu16ConcatenationComposedSize[i];
                            nTempHindiConsumed[nOutStrLen] = pu16ConcatenationComposedSize[i];
                            nOutStrLen++;
                        }

                        if ( nOutStrLen >= u16OutBufferSize )
                        {
                            break;
                        }

                        nTempHindiConsumed[nOutStrLen] = u16OffsetInComposed + 1 + 2;
                        pConsumed[0] = pConsumed[0] + nTempHindiConsumed[nOutStrLen]; //include 0x0930, 0x094D
                        nOutStrLen++;

                        u16OutOffset = u16FirstOutputStringCharOffset;
                    }
                    else
                    {
                        //only the 0x0930, 0x094D
                        nOutStrLen = 1;
                        pConsumed[0] = u16OffsetInComposed + 1;
                        nTempHindiConsumed[0] = pConsumed[0];

                        u16OutOffset = u16OffsetInConcatenation;
                    }
                }
                u16OffsetInConcatenation = u16FirstOutputStringCharOffset;
            }
            else
            {
                nOutStrLen = 1;
                u16OutOffset = u16OffsetInConcatenation;
                pConsumed[0] = pConsumed[0] + u16OffsetInComposed;
                nTempHindiConsumed[0] = pConsumed[0];
            }

            if ( nOutStrLen >= u16OutBufferSize )
            {
                break;
            }

            u16TempHindiOutLen = nOutStrLen;

            //find the right join character
            if ( nOffset > 0 && u16OffsetInConcatenation == 0 && _msAPI_MLE_FontHindiFeatureWithLJoin(eScript, u32FeatureTags, NULL) )
            {
                MEMCPY((void *)(pConsumed + 1), (void *)nTempHindiConsumed, sizeof(U32) * u16TempHindiOutLen);
                for ( i = u16OffsetInConcatenation + 1; i < u16OutLen; i++ )
                {
                    if ( nOutStrLen > u16OutBufferSize )
                    {
                        break;
                    }

                    nOutStrLen++;
                    pConsumed[0] = pConsumed[0] + pu16ConcatenationComposedSize[i];
                    pConsumed[nOutStrLen] = pu16ConcatenationComposedSize[i];
                }
            }
            else
            {
                if ( _msAPI_MLE_FontHindiCharIsComposed(eScript, au16OutputStr[u16OffsetInConcatenation]) )
                {
                    U16 u16CircleChar = CHAR_DOTTED_CIRCLE;

#ifdef __FEATURE_VECTOR_FONT__
                    u16CircleChar = msAPI_MLE_FONTBASE_VectorFontGetGlyphId(u16CircleChar);
#endif //__FEATURE_VECTOR_FONT__

                    for ( i = u16OffsetInConcatenation - 1; i >= 0; i-- )
                    {
                        if ( nOutStrLen >= u16OutBufferSize )
                        {
                            break;
                        }

                        if ( !_msAPI_MLE_FontHindiCharIsComposed(eScript, au16OutputStr[i]) )
                        {
                            if ( au16OutputStr[i] != u16CircleChar )
                            {
                                pConsumed[0] = pConsumed[0] + pu16ConcatenationComposedSize[i];
                                nTempHindiConsumed[nOutStrLen] = pu16ConcatenationComposedSize[i];
                                nOutStrLen++;
                            }
                            break;
                        }
                        else
                        {
                            pConsumed[0] = pConsumed[0] + pu16ConcatenationComposedSize[i];
                            nTempHindiConsumed[nOutStrLen] = pu16ConcatenationComposedSize[i];
                            nOutStrLen++;
                        }
                    }

                    for ( i = nOutStrLen - 1; i >= u16TempHindiOutLen; i-- )
                    {
                        pConsumed[nOutStrLen - i] = nTempHindiConsumed[i];
                    }
                    MEMCPY((void *)(pConsumed + (nOutStrLen - u16TempHindiOutLen) + 1), (void *)nTempHindiConsumed, sizeof(U32) * u16TempHindiOutLen);
                }
            }
        } while ( FALSE );

        if ( nOutStrLen > 0 )
        {
            if ( pComposedStr )
            {
                MEMCPY((void *)pComposedStr, (void *)(au16OutputStr + u16OutOffset), sizeof(U16) * nOutStrLen);
            }

            if ( pComposedLen )
            {
                *pComposedLen = nOutStrLen;
            }

            bReturnValue = TRUE;
        }
    }

    return bReturnValue;
}


static void _msAPI_MLE_FontHindiSwapRaHalantStr( HindiScript_e eScript, const U16 *pu16Txt, U32 u32InLen, U16 u16ConsumedCount, U16 *pu16Cluster, U16 u16BufferSize, U16 *pu16ClusterSize, U16 *pu16SeqInCluster, U32 *pu32FeatureTags )
{
    U16 u16TempClusterSize = 0;
    HindiSpecialCharacter_e eSpType = HINDI_SP_INVALID;
    U16 i = 0;

    if ( pu16Txt == NULL || u32InLen == 0 || pu16Cluster == NULL || pu16ClusterSize == NULL || (*pu16ClusterSize) == 0 )
    {
        return;
    }

    if ( *pu16ClusterSize <= 1 )
    {
        return;
    }

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return;
    }

    u16TempClusterSize = *pu16ClusterSize;

    eSpType = _msAPI_MLE_FontHindiGetCharSpecialType(eScript, pu16Cluster[0]);
    if ( eSpType == HINDI_SP_LEFT_JOINER || eSpType == HINDI_SP_TWOPART_JOINER )
    {
        pu16Cluster++;
        u16TempClusterSize--;

        if ( pu16SeqInCluster )
        {
            pu16SeqInCluster++;
        }
    }

    if( ((u16TempClusterSize) > 2) && _msAPI_MLE_FontHindiCharIsRA(eScript, pu16Cluster[0]) && _msAPI_MLE_FontHindiCharIsHalant(eScript, pu16Cluster[1]) )
    {
        if ( (_msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[2]) == HINDI_CON) )
        {
            if ( (u16TempClusterSize > 3) && (_msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[3]) == HINDI_DEPVOW)
#if ( defined(__KNDA_FONT__) )
                && ( eScript != HINDI_SCRIPT_KNDA )
#endif
                )
            {
                if(u16TempClusterSize == 4 && _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[2]) == HINDI_CON
                    && pu16Cluster[0] == 0x09b0 && pu16Cluster[1] == 0x09cd)
                {
                    pu16Cluster[0] = pu16Cluster[2];
                    pu16Cluster[1] = 0x09b0;
                    pu16Cluster[2] = 0x09cd;
                }
                else
                {
                    _msAPI_MLE_FontHindiReorderCluster(eScript, pu16Txt, u32InLen, u16ConsumedCount, pu16Cluster, u16BufferSize, &u16TempClusterSize, HINDI_ORDER_CON_DEPVOW, pu16SeqInCluster, pu32FeatureTags );
                }
            }
            //for bengali reph swap
            else if ((u16TempClusterSize > 2) && eScript == HINDI_SCRIPT_BENG)
            {
                if (u16TempClusterSize > 2 && _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[2]) == HINDI_CON
                    && pu16Cluster[0] == 0x09b0 && pu16Cluster[1] == 0x09cd)
                {
                    pu16Cluster[0] = pu16Cluster[2];
                    pu16Cluster[1] = 0x09b0;
                    pu16Cluster[2] = 0x09cd;
                }
                else
                {
                    _msAPI_MLE_FontHindiReorderCluster(eScript, pu16Txt, u32InLen, u16ConsumedCount, pu16Cluster, u16BufferSize, &u16TempClusterSize, HINDI_ORDER_CON_DEPVOW, pu16SeqInCluster, pu32FeatureTags);
                }
            }
            else
            {
                for ( i = u16TempClusterSize; i > 2; i-- )
                {
                    if ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[i-1]) != HINDI_SIGN )
                    {
                        break;
                    }
                }
                u16TempClusterSize = i;
                _msAPI_MLE_FontHindiReorderCluster(eScript, pu16Txt, u32InLen, u16ConsumedCount, pu16Cluster, u16BufferSize, &u16TempClusterSize, HINDI_ORDER_CON_SHALANT, pu16SeqInCluster, pu32FeatureTags );
            }
        }
    }
}

static U16 _msAPI_MLE_FontHindiGetIndexInSequence( const U16 *pu16SeqPos, U16 u16SeqSize, U16 u16StrOffset )
{
    U16 i = 0;
    U16 u16ReturnOffset = 0;

    if ( pu16SeqPos == NULL || u16StrOffset >= u16SeqSize )
    {
        return u16StrOffset;
    }

    for ( i = 0; i < u16SeqSize; i++ )
    {
        if ( pu16SeqPos[i] == u16StrOffset )
        {
            u16ReturnOffset = i;
            break;
        }
    }

    return u16ReturnOffset;
}

static U16 msAPI_MLE_FontHindiGetPreCon( HindiScript_e eScript, U16 *pu16Cluster, U16 u16ClusterSize, U16 u16Offset, U16 *pu16PreOffset )
{
    S16 i = 0;
    U16 u16ReturnChar = 0;

    if ( pu16PreOffset )
    {
        *pu16PreOffset = u16Offset;
    }

    if ( pu16Cluster == NULL || u16ClusterSize == 0 || u16Offset == 0 || u16Offset >= u16ClusterSize )
    {
        return 0;
    }

    for ( i = (u16Offset - 1); i >= 0; i-- )
    {
        if ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[i]) == HINDI_CON )
        {
            u16ReturnChar = pu16Cluster[i];

            if ( pu16PreOffset )
            {
                *pu16PreOffset = i;
            }
            break;
        }
    }

    return u16ReturnChar;
}

HindiScript_e msAPI_MLE_FontHindiGetCharScript( U16 u16Character )
{
    U16 i;
    HindiScript_e eScript = HINDI_MAX_SCRIPT_NUM;

    for ( i = 0; i < HINDI_MAX_SCRIPT_NUM; i++ )
    {
        if ( g_pHindiLangsTbl[i] == NULL )
        {
            break;
        }

#ifdef __FEATURE_VECTOR_FONT__
        if ( msAPI_MLE_FONTBASE_IsVectorFontExist() )
        {
            if ( (u16Character >= g_pHindiLangsTbl[i]->u16FirstChar && u16Character <= g_pHindiLangsTbl[i]->u16LastChar) )
            {
                eScript = g_pHindiLangsTbl[i]->eScript;
                break;
            }
        }
#endif //__FEATURE_VECTOR_FONT__
    }

    switch(eScript)
    {
    case HINDI_SCRIPT_MLYM:
    case HINDI_SCRIPT_SINH:
        msAPI_MLE_FontBaseSetZeroWidthFilterStatus(FALSE);
        break;
    default:
        msAPI_MLE_FontBaseSetZeroWidthFilterStatus(TRUE);
        break;
    }

    return eScript;
}

BOOLEAN _msAPI_MLE_FontHindiFeatureWithLJoin( HindiScript_e eScript, U32 u32FeatureTags, BOOLEAN *pIsTwoPart )
{
    BOOLEAN bResult = FALSE;

    eScript = eScript;

    if ( u32FeatureTags & _HindiPrivTwoPartJoinFeatureMask )
    {
        bResult = TRUE;

        if ( pIsTwoPart )
        {
            *pIsTwoPart = TRUE;
        }
    }
    else if ( u32FeatureTags & _HindiPrivLeftJoinFeatureMask )
    {
        bResult = TRUE;

        if ( pIsTwoPart )
        {
            *pIsTwoPart = FALSE;
        }
    }
    else
    {
        if ( pIsTwoPart )
        {
            *pIsTwoPart = FALSE;
        }
    }

    return bResult;
}

BOOLEAN _msAPI_MLE_FontHindiFeatureWithDotted( HindiScript_e eScript, U32 u32FeatureTags, BOOLEAN *pIsPreDotted )
{
    BOOLEAN bResult = FALSE;

    eScript = eScript;

    if ( u32FeatureTags & _HindiPrivPreDottedFeatureMask )
    {
        bResult = TRUE;

        if ( pIsPreDotted )
        {
            *pIsPreDotted = TRUE;
        }
    }
    else if ( u32FeatureTags & _HindiPrivPosDottedFeatureMask )
    {
        bResult = TRUE;

        if ( pIsPreDotted )
        {
            *pIsPreDotted = FALSE;
        }
    }

    return bResult;
}

BOOLEAN _msAPI_MLE_FontHindiFeatureWithNoCache( HindiScript_e eScript, U32 u32FeatureTags, BOOLEAN *pIsNoCached )
{
    BOOLEAN bResult = FALSE;

    eScript = eScript;

    if ( u32FeatureTags & _HindiPrivDontCachedFeatureMask )
    {
        bResult = TRUE;

        if ( pIsNoCached )
        {
            *pIsNoCached = TRUE;
        }
    }
    else
    {
        if ( pIsNoCached )
        {
            *pIsNoCached = FALSE;
        }
    }

    return bResult;
}

BOOLEAN _msAPI_MLE_FontHindiFeatureWithThreePart( HindiScript_e eScript, U32 u32FeatureTags, BOOLEAN *pIsThreePart )
{
    BOOLEAN bResult = FALSE;

    eScript = eScript;

    if ( u32FeatureTags & _HindiPrivThreePartFeatureMask )
    {
        bResult = TRUE;

        if ( pIsThreePart )
        {
            *pIsThreePart = TRUE;
        }
    }
    else
    {
        if ( pIsThreePart )
        {
            *pIsThreePart = FALSE;
        }
    }

    return bResult;
}

#ifdef __FEATURE_VECTOR_FONT__
static const U8 _g_fontScriptMap[] =
{
/*HINDI_SCRIPT_DEVA*/   LE_OTF_SCRIPT_DEVA,
/*HINDI_SCRIPT_BENG*/   LE_OTF_SCRIPT_BENG,
/*HINDI_SCRIPT_GUJR*/   LE_OTF_SCRIPT_GUJR,
/*HINDI_SCRIPT_ORYA*/   LE_OTF_SCRIPT_ORYA,
/*HINDI_SCRIPT_TAML*/   LE_OTF_SCRIPT_TAML,
/*HINDI_SCRIPT_TELU*/   LE_OTF_SCRIPT_TELU,
/*HINDI_SCRIPT_KNDA*/   LE_OTF_SCRIPT_KNDA,
/*HINDI_SCRIPT_MLYM*/   LE_OTF_SCRIPT_MLYM,
/*HINDI_SCRIPT_PUNJ*/   LE_OTF_SCRIPT_GURU,
/*HINDI_SCRIPT_SINH*/   LE_OTF_SCRIPT_SINH,
/*HINDI_SCRIPT_MYMR*/   LE_OTF_SCRIPT_MYMR,
/*HINDI_SCRIPT_KHMR*/   LE_OTF_SCRIPT_KHMR,
/*HINDI_SCRIPT_LAOO*/   LE_OTF_SCRIPT_LAOO,
/*HINDI_SCRIPT_MYMR_EXTA*/      LE_OTF_SCRIPT_MYMR_EXTA,
/*HINDI_SCRIPT_MYMR_EXTB*/      LE_OTF_SCRIPT_MYMR_EXTB,
/*HINDI_SCRIPT_KHMR_DIGIT1*/    LE_OTF_SCRIPT_KHMR_DIGIT1,
/*HINDI_SCRIPT_KHMR_DIGIT2*/    LE_OTF_SCRIPT_KHMR_DIGIT2,
/*HINDI_SCRIPT_KHMR_SYMBOLS*/   LE_OTF_SCRIPT_KHMR_SYMBOLS
};

static LE_OTF_ScriptTag_e _msAPI_MLE_FontMapScriptTag(HindiScript_e eScript)
{
    if ( eScript >= HINDI_MAX_SCRIPT_NUM )//'=' -> '>=' Fix coverity 203912
    {
        return LE_OTF_MAX_SCRIPT_NUM;
    }

    return _g_fontScriptMap[eScript];
}

static const LE_OTF_FeatureTag_e _g_fontOtfFeatureMap[] =
{
/*HINDI_FEATURE_LOCL*/  LE_OTF_FEATURE_LOCL,
/*HINDI_FEATURE_NUKT*/  LE_OTF_FEATURE_NUKT,
/*HINDI_FEATURE_AKHN*/  LE_OTF_FEATURE_AKHN,
/*HINDI_FEATURE_RPHF*/  LE_OTF_FEATURE_RPHF,
/*HINDI_FEATURE_BLWF*/  LE_OTF_FEATURE_BLWF,
/*HINDI_FEATURE_HALF*/  LE_OTF_FEATURE_HALF,
/*HINDI_FEATURE_VATU*/  LE_OTF_FEATURE_VATU,
/*HINDI_FEATURE_PRES*/  LE_OTF_FEATURE_PRES,
/*HINDI_FEATURE_BLWS*/  LE_OTF_FEATURE_BLWS,
/*HINDI_FEATURE_ABVS*/  LE_OTF_FEATURE_ABVS,
/*HINDI_FEATURE_PSTS*/  LE_OTF_FEATURE_PSTS,
/*HINDI_FEATURE_HALN*/  LE_OTF_FEATURE_HALN,
/*HINDI_FEATURE_BLWM*/  LE_OTF_FEATURE_BLWM,
/*HINDI_FEATURE_ABVM*/  LE_OTF_FEATURE_ABVM,
/*HINDI_FEATURE_RKRF*/  LE_OTF_FEATURE_RKRF,
/*HINDI_FEATURE_CJCT*/  LE_OTF_FEATURE_CJCT,
/*HINDI_FEATURE_CALT*/  LE_OTF_FEATURE_CALT,
/*HINDI_FEATURE_PSTF*/  LE_OTF_FEATURE_PSTF,
/*HINDI_FEATURE_INIT*/    LE_OTF_FEATURE_INIT,
/*HINDI_FEATURE_PREF*/  LE_OTF_FEATURE_PREF,
/*HINDI_FEATURE_DIST*/  LE_OTF_FEATURE_DIST,
/*HINDI_FEATURE_MARK*/  LE_OTF_FEATURE_MARK,
/*HINDI_FEATURE_MKMK*/  LE_OTF_FEATURE_MKMK,
/*HINDI_FEATURE_CLIG*/  LE_OTF_FEATURE_CLIG,
/*HINDI_FEATURE_LIGA*/  LE_OTF_FEATURE_LIGA,
/*HINDI_FEATURE_RLIG*/  LE_OTF_FEATURE_RLIG,
};

static BOOLEAN _msAPI_MLE_FontMapFeatureTag(const HindiFeatureRecord_t *psFeatureRecords, U16 u16FeatureSize, LE_OTF_FeatureRecord_t *psOtfFeatureRecords)
{
    U8 i, j = 0;

    if ( psFeatureRecords == NULL || psOtfFeatureRecords == NULL || u16FeatureSize == 0 )
    {
        return FALSE;
    }

    for ( i = 0; i < u16FeatureSize; i++ )
    {
        if ( psFeatureRecords[i].eTag < HINDI_MAX_FEATURE_NUM )
        {
             psOtfFeatureRecords[j].eTag = _g_fontOtfFeatureMap[psFeatureRecords[i].eTag];
             psOtfFeatureRecords[j].u32Mask = psFeatureRecords[i].u32Mask;
             j++;
        }
     }

     return TRUE;
}

static U16 _msAPI_MLE_FontGetPreCharIgnoreNukta( HindiScript_e eScript, U16 *pu16Cluster, U16 u16ClusterSize, U16 u16Offset, U16 *pu16PreOffset )
{
    S16 i = 0;
    U16 u16ReturnChar = 0;

    if ( pu16PreOffset )
    {
        *pu16PreOffset = 0;
    }

    if ( pu16Cluster == NULL || u16ClusterSize == 0 || u16Offset == 0 || u16Offset >= u16ClusterSize )
    {
        return 0;
    }

    for ( i = (u16Offset - 1); i >= 0; i-- )
    {
        if ( _msAPI_MLE_FontHindiCharIsNukta(eScript, pu16Cluster[i]) )
        {
            continue;
        }

        u16ReturnChar = pu16Cluster[i];

        if ( pu16PreOffset )
        {
            *pu16PreOffset = i;
        }
        break;
    }

    return u16ReturnChar;
}

static U16 _msAPI_MLE_FontGetNextConChar( HindiScript_e eScript, U16 *pu16Cluster, U16 u16ClusterSize, U16 u16Offset, U16 *pu16NextOffset )
{
    S16 i = 0;
    U16 u16ReturnChar = 0;

    if ( pu16NextOffset )
    {
        *pu16NextOffset = 0;
    }

    if ( pu16Cluster == NULL || u16ClusterSize == 0 || u16Offset >= (u16ClusterSize - 1) )
    {
        return 0;
    }

    for ( i = u16Offset + 1; i < u16ClusterSize; i++ )
    {
        HindiCharacter_e eType = _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[i]);

        if ( eType == HINDI_CON )
        {
            u16ReturnChar = pu16Cluster[i];
            if ( pu16NextOffset )
            {
                *pu16NextOffset = i;
            }
            break;
        }
    }

    return u16ReturnChar;
}

static void _msAPI_MLE_FontVectorReorderCluster( HindiScript_e eScript, U16 *pu16Cluster, U16 *pu16ClusterSize, U16 *pu16ClustIndex, U32 *pu32FeatureTags, U16 *pau16Consumed,  U16 *pau16CharFeatures, U16 *pau16GlyphOrder, U8 *pu8PrebaseSwapDispOrder, S8 *ps8BaseConsonantGlyph )
{
    U16 u16CurrentSize;
    U16 u16RemainLen;
    U16 u16FirstCharOffset;
    BOOLEAN bNeedBlwf = FALSE;
    BOOLEAN bNeedHaln = FALSE;
    BOOLEAN bWithRphf = FALSE;
    BOOLEAN bHalantSwap = FALSE;
    HindiSpecialCharacter_e eSpType = HINDI_SP_INVALID;

    if ( pu16Cluster == NULL || pu16ClusterSize == NULL || *pu16ClusterSize == 0 || pu16ClustIndex == NULL || pu32FeatureTags == NULL || pau16Consumed == NULL )
    {
        return;
    }

    u16CurrentSize = *pu16ClusterSize;
    u16RemainLen = u16CurrentSize;

    bWithRphf = _msAPI_MLE_FontHindiFeatureWithRphf(eScript, *pu32FeatureTags, NULL);

    if ( bWithRphf )
    {
        while ( u16RemainLen > 2 )
        {
            u16FirstCharOffset = u16RemainLen - 2;

            if ( _msAPI_MLE_FontHindiCharIsRA(eScript, pu16Cluster[u16FirstCharOffset])
                 && _msAPI_MLE_FontHindiCharIsHalant(eScript, pu16Cluster[u16FirstCharOffset + 1]) )
            {
                pau16CharFeatures[u16FirstCharOffset] = pau16CharFeatures[u16FirstCharOffset] | LE_CHAR_FEATURE_RPHF;
                //u16RemainLen = u16RemainLen - 2;
                u16RemainLen = u16RemainLen + 2;
                break;
            }
            u16RemainLen = u16RemainLen - 1;
        }
    }

#if ( defined(__MYMR_FONT__) || defined(__KHMR_FONT__))
    if ( eScript == HINDI_SCRIPT_MYMR )
    {
        BOOLEAN bKinziFound = FALSE;

        while( u16RemainLen >= 2 )
        {
            if ( ( bKinziFound == FALSE ) && ( u16RemainLen >= 3 ) )
            {
                u16FirstCharOffset = u16RemainLen - 3;

                switch( pu16Cluster[u16FirstCharOffset] )
                {
                    case MYANMAR_C_NGA:
                    case MYANMAR_C_RA:
                    case MYANMAR_C_MON_NGA:
                        if ( ( pu16Cluster[u16FirstCharOffset+1] == MYANMAR_S_ASAT ) && ( pu16Cluster[u16FirstCharOffset+2] == MYANMAR_S_HALANT ) )
                        {
                            bKinziFound = TRUE;

                            //Kinzi found
                            pau16CharFeatures[u16FirstCharOffset] = pau16CharFeatures[u16FirstCharOffset] | LE_CHAR_FEATURE_RPHF;
                            pau16CharFeatures[u16FirstCharOffset+1] = pau16CharFeatures[u16FirstCharOffset+1] | LE_CHAR_FEATURE_ABVS;
                        }
                        break;
                    default:
                        break;
                }
            }
            

            u16FirstCharOffset = u16RemainLen - 2;
            if (pu16Cluster[u16FirstCharOffset] == 0x101b && pu16Cluster[u16FirstCharOffset+1] == 0x103d && pu16Cluster[u16FirstCharOffset + 2] == 0x103e)
            {
                pau16CharFeatures[u16FirstCharOffset+1] = pau16CharFeatures[u16FirstCharOffset+1] | LE_CHAR_FEATURE_BLWF;
                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWF);
                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWM);
            }
            else if (pu16Cluster[u16FirstCharOffset] == 0x1010 && pu16Cluster[u16FirstCharOffset + 1] == 0x1030 && pu16Cluster[u16FirstCharOffset -1] == 0x1039)
            {
                pau16CharFeatures[u16FirstCharOffset - 1] = pau16CharFeatures[u16FirstCharOffset - 1] | LE_CHAR_FEATURE_BLWF;
                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWF);
                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWM);
                u16RemainLen--;
            }
            else if ( _msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[u16FirstCharOffset], pu16Cluster[u16FirstCharOffset + 1]) )
            {
                    pau16CharFeatures[u16FirstCharOffset] = pau16CharFeatures[u16FirstCharOffset] | LE_CHAR_FEATURE_BLWF;
                    *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWF);
                    *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWM);
                    //*pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_MARK);
                    u16RemainLen--;

            }

            u16RemainLen--;

        }
    }
    else if (eScript == HINDI_SCRIPT_KHMR)
    {
        U16 i;
        while( u16RemainLen >= 2 )
        {
            u16FirstCharOffset = u16RemainLen - 2;
            if( pu16Cluster[u16FirstCharOffset] == KHMER_S_COENG )
            {
                if ( (IS_KHMER_CONS_CHAR( pu16Cluster[u16FirstCharOffset+1])) || (IS_KHMER_INDV_CHAR(pu16Cluster[u16FirstCharOffset + 1])))
                {
                    //COENG + RO
                    if (pu16Cluster[u16FirstCharOffset + 1] == KHMER_C_RO)
                    {
                    }
                    //COENG + CONS
                    else
                    {
                        pau16CharFeatures[u16FirstCharOffset] = pau16CharFeatures[u16FirstCharOffset] | LE_CHAR_FEATURE_BLWF;
                    }
                }
            }
            else if ((pu16Cluster[u16FirstCharOffset] == KHMER_S_MUUSIKATOAN) || (pu16Cluster[u16FirstCharOffset] == KHMER_S_TRIISA))
            {
                if (IS_KHMER_VABV_CHAR(pu16Cluster[u16FirstCharOffset + 1]))
                {
                    pau16CharFeatures[u16FirstCharOffset] = pau16CharFeatures[u16FirstCharOffset] | LE_CHAR_FEATURE_BLWF;
                }
            }
            if (IS_KHMER_TWOPART_CHAR(pu16Cluster[u16FirstCharOffset + 1]))
            {
                if (pu16Cluster[u16FirstCharOffset + 1] == KHMER_DV_OE)
                {
                    if ((IS_KHMER_REGSHIFT_CHAR(pu16Cluster[u16FirstCharOffset])))
                    {
                        pau16CharFeatures[u16FirstCharOffset] = pau16CharFeatures[u16FirstCharOffset] | LE_CHAR_FEATURE_BLWF;
                    }
                    pu16Cluster[u16FirstCharOffset + 1] = KHMER_DV_II;
                }

                for (i = u16CurrentSize; i > 0; i--)
                {
                    pu16Cluster[i] = pu16Cluster[i - 1];
                    pau16CharFeatures[i] = pau16CharFeatures[i - 1];
                }

                pu16Cluster[0] = KHMER_DV_E;
                u16CurrentSize++;
            }
            u16RemainLen--;

        }
    }
    else
#endif
    {
        BOOLEAN bPstfSwap = FALSE;
        while ( u16RemainLen && (u16CurrentSize > 0) )
        {
            BOOLEAN bMatched = FALSE;

    #if (defined(__TELUGU_FONT__) || defined(__KNDA_FONT__))

            //Todo: Telugu reorder parts need to refine and optimize again, now it is Ugly and Redundancy
            if ( ( eScript == HINDI_SCRIPT_TELU ) || ( eScript == HINDI_SCRIPT_KNDA ) )
            {
                if ( u16RemainLen >= 8 )
                {
                    U16 au16Temp[8];
                    U16 i, j;

                    u16FirstCharOffset = u16RemainLen - 8;

                    if ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset + 6]) == HINDI_CON
                            && _msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[u16FirstCharOffset + 5], pu16Cluster[u16FirstCharOffset + 6])
                            && _msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[u16FirstCharOffset + 3], pu16Cluster[u16FirstCharOffset + 4])
                            && _msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[u16FirstCharOffset + 1], pu16Cluster[u16FirstCharOffset + 2])
                            && _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset]) == HINDI_CON
                            && _msAPI_MLE_FontHindiVectorCharIsComposed( eScript, pu16Cluster[u16FirstCharOffset + 7])
                            && !_msAPI_MLE_FontHindiCharIsRA(eScript, pu16Cluster[u16FirstCharOffset]) )
                    {
                        //This feature is applied only on the base glyph if the syllable ends with a halant.
                        if ( _msAPI_MLE_FontHindiCharIsHalant( eScript, pu16Cluster[u16FirstCharOffset + 7]) )
                        {
                            pau16CharFeatures[u16FirstCharOffset] = pau16CharFeatures[u16FirstCharOffset] | LE_CHAR_FEATURE_HALN;
                            bNeedHaln = TRUE;
                        }

                        if ( *pu32FeatureTags & _HindiAkhnFeatureMask )
                        {
                            // only 5 possible conditions: 012, 123, 234, 345, 456
                            for(i=0; i<5; i++)
                            {
                                if ( _msAPI_MLE_FontHindiStrWithAkhand(eScript, pu16Cluster, 8, u16FirstCharOffset+i) )
                                    break;
                            }
                            //now the last char halant should be put on position (i+3), skip akhand pattern length
                            au16Temp[0] = pu16Cluster[u16FirstCharOffset];
                            for(j=1;j<(i+3);j+=2)
                            {
                                au16Temp[j] = pu16Cluster[u16FirstCharOffset + j + 1];
                                au16Temp[j+1] = pu16Cluster[u16FirstCharOffset + j];

                                pau16CharFeatures[u16FirstCharOffset + j] = pau16CharFeatures[u16FirstCharOffset + j] | LE_CHAR_FEATURE_BLWF;
                            }
                            au16Temp[i+3] = pu16Cluster[u16FirstCharOffset + 7];
                            for(j=i+4;j<8;j+=2)
                            {
                                au16Temp[j] = pu16Cluster[u16FirstCharOffset + j ];
                                if((j+1)<8)//fix coverity 203935
                                {
                                    au16Temp[j+1] = pu16Cluster[u16FirstCharOffset + j - 1];
                                }

                                pau16CharFeatures[u16FirstCharOffset + j] = pau16CharFeatures[u16FirstCharOffset + j] | LE_CHAR_FEATURE_BLWF;
                            }
                        }
                        else
                        {
                            au16Temp[0] = pu16Cluster[u16FirstCharOffset];
                            au16Temp[1] = pu16Cluster[u16FirstCharOffset + 7];
                            for(j=2;j<8;j+=2)
                            {
                                au16Temp[j] = pu16Cluster[u16FirstCharOffset + j ];
                                au16Temp[j+1] = pu16Cluster[u16FirstCharOffset + j - 1];

                                pau16CharFeatures[u16FirstCharOffset + j] = pau16CharFeatures[u16FirstCharOffset + j] | LE_CHAR_FEATURE_BLWF;
                            }
                        }

                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVS);
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);

                        for( i = 0; i < 8; i++ )
                        {
                            pu16Cluster[u16FirstCharOffset + i] = au16Temp[i];
                        }

                        bMatched = TRUE;
                        bNeedBlwf = TRUE;
                        bHalantSwap = TRUE;

                        u16RemainLen = u16RemainLen - 8;
                    }
                }

                if ( u16RemainLen >= 7 )
                {
                    U16 au16Temp[8];
                    U16 i;

                    u16FirstCharOffset = u16RemainLen - 7;

                    if ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset + 6]) == HINDI_CON
                            && _msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[u16FirstCharOffset + 5], pu16Cluster[u16FirstCharOffset + 6])
                            && _msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[u16FirstCharOffset + 3], pu16Cluster[u16FirstCharOffset + 4])
                            && _msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[u16FirstCharOffset + 1], pu16Cluster[u16FirstCharOffset + 2])
                            && _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset]) == HINDI_CON
                            && !_msAPI_MLE_FontHindiCharIsRA(eScript, pu16Cluster[u16FirstCharOffset]) )
                    {
                        au16Temp[0] = pu16Cluster[u16FirstCharOffset];
                        au16Temp[1] = pu16Cluster[u16FirstCharOffset + 2];
                        au16Temp[2] = pu16Cluster[u16FirstCharOffset + 1];
                        au16Temp[3] = pu16Cluster[u16FirstCharOffset + 4];
                        au16Temp[4] = pu16Cluster[u16FirstCharOffset + 3];
                        au16Temp[5] = pu16Cluster[u16FirstCharOffset + 6];
                        au16Temp[6] = pu16Cluster[u16FirstCharOffset + 5];

                        pau16CharFeatures[u16FirstCharOffset + 5] = pau16CharFeatures[u16FirstCharOffset + 5] | LE_CHAR_FEATURE_BLWF;
                        pau16CharFeatures[u16FirstCharOffset + 3] = pau16CharFeatures[u16FirstCharOffset + 3] | LE_CHAR_FEATURE_BLWF;
                        pau16CharFeatures[u16FirstCharOffset + 1] = pau16CharFeatures[u16FirstCharOffset + 1] | LE_CHAR_FEATURE_BLWF;

                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVS);
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);

                        for( i = 0; i < 7; i++ )
                        {
                            pu16Cluster[u16FirstCharOffset + i] = au16Temp[i];
                        }

                        bMatched = TRUE;
                        bNeedBlwf = TRUE;
                        bHalantSwap = TRUE;

                        u16RemainLen = u16RemainLen - 7;
                    }
                    else if ( _msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[u16FirstCharOffset + 5], pu16Cluster[u16FirstCharOffset + 6])
                            && _msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[u16FirstCharOffset + 3], pu16Cluster[u16FirstCharOffset + 4])
                            && ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset + 2]) == HINDI_DEPVOW )
                            && ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset + 1]) == HINDI_DEPVOW )
                            && _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset]) == HINDI_CON
                            && !_msAPI_MLE_FontHindiCharIsRA(eScript, pu16Cluster[u16FirstCharOffset]) )
                    {
                        au16Temp[0] = pu16Cluster[u16FirstCharOffset];
                        au16Temp[1] = pu16Cluster[u16FirstCharOffset + 1];
                        au16Temp[2] = pu16Cluster[u16FirstCharOffset + 2];
                        au16Temp[3] = pu16Cluster[u16FirstCharOffset + 4];
                        au16Temp[4] = pu16Cluster[u16FirstCharOffset + 3];
                        au16Temp[5] = pu16Cluster[u16FirstCharOffset + 6];
                        au16Temp[6] = pu16Cluster[u16FirstCharOffset + 5];

                        pau16CharFeatures[u16FirstCharOffset + 5] = pau16CharFeatures[u16FirstCharOffset + 5] | LE_CHAR_FEATURE_BLWF;
                        pau16CharFeatures[u16FirstCharOffset + 3] = pau16CharFeatures[u16FirstCharOffset + 3] | LE_CHAR_FEATURE_BLWF;

                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVS);
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);

                        for( i = 0; i < 7; i++ )
                        {
                            pu16Cluster[u16FirstCharOffset + i] = au16Temp[i];
                        }

                        bMatched = TRUE;
                        bNeedBlwf = TRUE;
                        bHalantSwap = TRUE;

                        u16RemainLen = u16RemainLen - 7;
                    }
    #ifdef __KNDA_FONT__
                    else if ( eScript == HINDI_SCRIPT_KNDA )
                    {
                        if ( ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset+6]) == HINDI_DEPVOW ) &&
                            ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset+5]) == HINDI_DEPVOW ) &&
                            ( _msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[u16FirstCharOffset + 3], pu16Cluster[u16FirstCharOffset + 4]) ) &&
                            ( _msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[u16FirstCharOffset + 1], pu16Cluster[u16FirstCharOffset + 2]) ) &&
                            ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset]) == HINDI_CON ) &&
                            ( !_msAPI_MLE_FontHindiCharIsRA(eScript, pu16Cluster[u16FirstCharOffset]) ) )
                        {
                            U8 u8Path = 1;

                            if ( u16CurrentSize >= 8 )
                            {
                                switch ( pu16Cluster[u16FirstCharOffset+7] )
                                {
                                case KANNADA_DV_AA:
                                case KANNADA_DV_U:
                                case KANNADA_DV_UU:
                                    if ( *pu32FeatureTags & _HindiAkhnFeatureMask )
                                        u8Path = 2;
                                    else
                                        u8Path = 3;
                                    break;
                                default:
                                    if ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset+7]) == HINDI_DEPVOW )
                                        if ( !( *pu32FeatureTags & _HindiAkhnFeatureMask ) )
                                            u8Path = 4;
                                    break;
                                }
                            }

                            switch( u8Path )
                            {
                            default:
                            case 1:
                            case 2:
                                au16Temp[0] = pu16Cluster[u16FirstCharOffset];
                                au16Temp[1] = pu16Cluster[u16FirstCharOffset + 2];
                                au16Temp[2] = pu16Cluster[u16FirstCharOffset + 1];
                                au16Temp[3] = pu16Cluster[u16FirstCharOffset + 5];
                                au16Temp[4] = pu16Cluster[u16FirstCharOffset + 6];

                                pau16CharFeatures[u16FirstCharOffset + 1] = pau16CharFeatures[u16FirstCharOffset + 1] | LE_CHAR_FEATURE_BLWF;

                                if ( u8Path == 2 )
                                {
                                    au16Temp[5] = pu16Cluster[u16FirstCharOffset + 7];
                                    au16Temp[6] = pu16Cluster[u16FirstCharOffset + 4];
                                    au16Temp[7] = pu16Cluster[u16FirstCharOffset + 3];

                                    pau16CharFeatures[u16FirstCharOffset + 6] = pau16CharFeatures[u16FirstCharOffset + 6] | LE_CHAR_FEATURE_BLWF;
                                }
                                else
                                {
                                    au16Temp[5] = pu16Cluster[u16FirstCharOffset + 4];
                                    au16Temp[6] = pu16Cluster[u16FirstCharOffset + 3];

                                    pau16CharFeatures[u16FirstCharOffset + 5] = pau16CharFeatures[u16FirstCharOffset + 5] | LE_CHAR_FEATURE_BLWF;
                                }
                                break;

                            case 3:
                                au16Temp[0] = pu16Cluster[u16FirstCharOffset];
                                au16Temp[1] = pu16Cluster[u16FirstCharOffset + 5];
                                au16Temp[2] = pu16Cluster[u16FirstCharOffset + 6];
                                au16Temp[3] = pu16Cluster[u16FirstCharOffset + 7];
                                au16Temp[4] = pu16Cluster[u16FirstCharOffset + 2];
                                au16Temp[5] = pu16Cluster[u16FirstCharOffset + 1];
                                au16Temp[6] = pu16Cluster[u16FirstCharOffset + 4];
                                au16Temp[7] = pu16Cluster[u16FirstCharOffset + 3];

                                pau16CharFeatures[u16FirstCharOffset + 4] = pau16CharFeatures[u16FirstCharOffset + 4] | LE_CHAR_FEATURE_BLWF;
                                pau16CharFeatures[u16FirstCharOffset + 6] = pau16CharFeatures[u16FirstCharOffset + 6] | LE_CHAR_FEATURE_BLWF;
                                break;

                            case 4:
                                au16Temp[0] = pu16Cluster[u16FirstCharOffset];
                                au16Temp[1] = pu16Cluster[u16FirstCharOffset + 5];
                                au16Temp[2] = pu16Cluster[u16FirstCharOffset + 6];
                                au16Temp[3] = pu16Cluster[u16FirstCharOffset + 2];
                                au16Temp[4] = pu16Cluster[u16FirstCharOffset + 1];
                                au16Temp[5] = pu16Cluster[u16FirstCharOffset + 4];
                                au16Temp[6] = pu16Cluster[u16FirstCharOffset + 3];
                                au16Temp[7] = pu16Cluster[u16FirstCharOffset + 7];

                                pau16CharFeatures[u16FirstCharOffset + 3] = pau16CharFeatures[u16FirstCharOffset + 3] | LE_CHAR_FEATURE_BLWF;
                                pau16CharFeatures[u16FirstCharOffset + 5] = pau16CharFeatures[u16FirstCharOffset + 5] | LE_CHAR_FEATURE_BLWF;
                                break;
                            }

                            *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVS);
                            *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);

                            for( i = 0; i < ((u8Path > 1) ? 8 : 7); i++ )
                            {
                                pu16Cluster[u16FirstCharOffset + i] = au16Temp[i];
                            }

                            bMatched = TRUE;
                            bNeedBlwf = TRUE;
                            bHalantSwap = TRUE;

                            u16RemainLen = u16RemainLen - 7;
                        }
                        else if ( ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset+6]) == HINDI_DEPVOW ) &&
                            ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset+5]) == HINDI_DEPVOW ) &&
                            ( _msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[u16FirstCharOffset + 3], pu16Cluster[u16FirstCharOffset + 4]) ) &&
                            ( _msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[u16FirstCharOffset + 1], pu16Cluster[u16FirstCharOffset + 2]) ) &&
                            ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset]) == HINDI_DEPVOW ) )
                        {
                            au16Temp[0] = pu16Cluster[u16FirstCharOffset + 5];
                            au16Temp[1] = pu16Cluster[u16FirstCharOffset + 0];
                            au16Temp[2] = pu16Cluster[u16FirstCharOffset + 2];
                            au16Temp[3] = pu16Cluster[u16FirstCharOffset + 1];
                            au16Temp[4] = pu16Cluster[u16FirstCharOffset + 4];
                            au16Temp[5] = pu16Cluster[u16FirstCharOffset + 3];
                            au16Temp[6] = pu16Cluster[u16FirstCharOffset + 6];

                            pau16CharFeatures[u16FirstCharOffset + 2] = pau16CharFeatures[u16FirstCharOffset + 2] | LE_CHAR_FEATURE_BLWF;
                            pau16CharFeatures[u16FirstCharOffset + 4] = pau16CharFeatures[u16FirstCharOffset + 4] | LE_CHAR_FEATURE_BLWF;

                            *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVS);
                            *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);

                            for( i = 0; i < 7; i++ )
                            {
                                pu16Cluster[u16FirstCharOffset + i] = au16Temp[i];
                            }

                            bMatched = TRUE;
                            bNeedBlwf = TRUE;
                            bHalantSwap = TRUE;

                            u16RemainLen = u16RemainLen - 7;
                        }
                        else if ( ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset+6]) == HINDI_DEPVOW ) &&
                            ( _msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[u16FirstCharOffset + 4], pu16Cluster[u16FirstCharOffset + 5]) ) &&
                            ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset + 3]) == HINDI_DEPVOW ) &&
                            ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset + 2]) == HINDI_DEPVOW ) &&
                            ( _msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[u16FirstCharOffset], pu16Cluster[u16FirstCharOffset + 1]) ) )
                        {
                            au16Temp[0] = pu16Cluster[u16FirstCharOffset + 1];
                            au16Temp[1] = pu16Cluster[u16FirstCharOffset + 0];
                            au16Temp[2] = pu16Cluster[u16FirstCharOffset + 6];
                            au16Temp[3] = pu16Cluster[u16FirstCharOffset + 2];
                            au16Temp[4] = pu16Cluster[u16FirstCharOffset + 5];
                            au16Temp[5] = pu16Cluster[u16FirstCharOffset + 4];
                            au16Temp[6] = pu16Cluster[u16FirstCharOffset + 3];

                            pau16CharFeatures[u16FirstCharOffset + 0] = pau16CharFeatures[u16FirstCharOffset + 0] | LE_CHAR_FEATURE_BLWF;
                            pau16CharFeatures[u16FirstCharOffset + 4] = pau16CharFeatures[u16FirstCharOffset + 4] | LE_CHAR_FEATURE_BLWF;

                            *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVS);
                            *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);

                            for( i = 0; i < 7; i++ )
                            {
                                pu16Cluster[u16FirstCharOffset + i] = au16Temp[i];
                            }

                            bMatched = TRUE;
                            bNeedBlwf = TRUE;
                            bHalantSwap = TRUE;

                            u16RemainLen = u16RemainLen - 7;
                        }
                    }
    #endif
                }

                if ( u16RemainLen >= 6 )
                {
                    U16 au16Temp[7];
                    U16 i, j;

                    u16FirstCharOffset = u16RemainLen - 6;

                    if ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset + 4]) == HINDI_CON
                         && _msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[u16FirstCharOffset + 3], pu16Cluster[u16FirstCharOffset + 4])
                         && _msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[u16FirstCharOffset + 1], pu16Cluster[u16FirstCharOffset + 2])
                         && _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset]) == HINDI_CON
                         && _msAPI_MLE_FontHindiVectorCharIsComposed( eScript, pu16Cluster[u16FirstCharOffset + 5])
                         && !_msAPI_MLE_FontHindiCharIsRA(eScript, pu16Cluster[u16FirstCharOffset]) )
                    {
                        //This feature is applied only on the base glyph if the syllable ends with a halant.
                        if ( _msAPI_MLE_FontHindiCharIsHalant( eScript, pu16Cluster[u16FirstCharOffset + 5]) )
                        {
                            pau16CharFeatures[u16FirstCharOffset] = pau16CharFeatures[u16FirstCharOffset] | LE_CHAR_FEATURE_HALN;
                            bNeedHaln = TRUE;
                        }

                        if ( *pu32FeatureTags & _HindiAkhnFeatureMask )
                        {
                            // only 3 possible conditions: 012, 123, 234
                            for(i=0; i<3; i++)
                            {
                                if ( _msAPI_MLE_FontHindiStrWithAkhand(eScript, pu16Cluster, 6, u16FirstCharOffset+i) )
                                    break;
                            }
                            //now the last char halant should be put on position (i+3), skip akhand pattern length
                            au16Temp[0] = pu16Cluster[u16FirstCharOffset];
                            for(j=1;j<(i+3);j+=2)
                            {
                                au16Temp[j] = pu16Cluster[u16FirstCharOffset + j + 1];
                                au16Temp[j+1] = pu16Cluster[u16FirstCharOffset + j];

                                pau16CharFeatures[u16FirstCharOffset + j] = pau16CharFeatures[u16FirstCharOffset + j] | LE_CHAR_FEATURE_BLWF;
                            }
                            au16Temp[i+3] = pu16Cluster[u16FirstCharOffset + 5];
                            for(j=i+4;j<6;j+=2)
                            {
                                au16Temp[j] = pu16Cluster[u16FirstCharOffset + j ];
                                au16Temp[j+1] = pu16Cluster[u16FirstCharOffset + j - 1];

                                pau16CharFeatures[u16FirstCharOffset + j] = pau16CharFeatures[u16FirstCharOffset + j] | LE_CHAR_FEATURE_BLWF;
                            }
                        }
                        else
                        {
                            au16Temp[0] = pu16Cluster[u16FirstCharOffset];
                            au16Temp[1] = pu16Cluster[u16FirstCharOffset + 5];
                            for(j=2;j<6;j+=2)
                            {
                                au16Temp[j] = pu16Cluster[u16FirstCharOffset + j ];
                                au16Temp[j+1] = pu16Cluster[u16FirstCharOffset + j - 1];

                                pau16CharFeatures[u16FirstCharOffset + j] = pau16CharFeatures[u16FirstCharOffset + j] | LE_CHAR_FEATURE_BLWF;
                            }
                        }

                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVS);
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);

                        for( i = 0; i < 6; i++ )
                        {
                            pu16Cluster[u16FirstCharOffset + i] = au16Temp[i];
                        }

                        bMatched = TRUE;
                        bNeedBlwf = TRUE;
                        bHalantSwap = TRUE;

                        u16RemainLen = u16RemainLen - 6;
                    }
    #ifdef __KNDA_FONT__
                    //blwf + two-part
                    else if ( eScript == HINDI_SCRIPT_KNDA )
                    {
                        if ( ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset+5]) == HINDI_DEPVOW ) &&
                            ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset+4]) == HINDI_DEPVOW ) &&
                            ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset+3]) == HINDI_DEPVOW ) &&
                            ( _msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[u16FirstCharOffset + 1], pu16Cluster[u16FirstCharOffset + 2]) ) &&
                            ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset]) == HINDI_CON ) &&
                            ( !_msAPI_MLE_FontHindiCharIsRA(eScript, pu16Cluster[u16FirstCharOffset]) ) )
                        {
                            if ( *pu32FeatureTags & _HindiAkhnFeatureMask )
                            {
                                switch ( pu16Cluster[u16FirstCharOffset+4] )
                                {
                                case KANNADA_DV_UU:
                                case KANNADA_ADV_EE:
                                case KANNADA_ADV_AI:
                                    au16Temp[0] = pu16Cluster[u16FirstCharOffset];
                                    au16Temp[1] = pu16Cluster[u16FirstCharOffset + 2];
                                    au16Temp[2] = pu16Cluster[u16FirstCharOffset + 1];
                                    au16Temp[3] = pu16Cluster[u16FirstCharOffset + 5];
                                    au16Temp[4] = pu16Cluster[u16FirstCharOffset + 3];
                                    au16Temp[5] = pu16Cluster[u16FirstCharOffset + 4];

                                    pau16CharFeatures[u16FirstCharOffset + 1] = pau16CharFeatures[u16FirstCharOffset + 1] | LE_CHAR_FEATURE_BLWF;

                                    *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVS);
                                    *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);

                                    for( i = 0; i < 6; i++ )
                                    {
                                        pu16Cluster[u16FirstCharOffset + i] = au16Temp[i];
                                    }

                                    bMatched = TRUE;
                                    bNeedBlwf = TRUE;
                                    bHalantSwap = TRUE;

                                    u16RemainLen = u16RemainLen - 6;
                                    break;
                                default:
                                    break;
                                }
                            }
                            else
                            {
                                switch ( pu16Cluster[u16FirstCharOffset+5] )
                                {
                                case KANNADA_DV_UU:
                                case KANNADA_ADV_EE:
                                case KANNADA_ADV_AI:
                                    if ( ( u16FirstCharOffset > 0 ) && ( _msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[u16FirstCharOffset - 1], pu16Cluster[u16FirstCharOffset + 0]) ) )
                                    {
                                        S16 k;

                                        if ( pu16Cluster[u16FirstCharOffset+5] == KANNADA_DV_UU )
                                        {
                                            au16Temp[0] = pu16Cluster[u16FirstCharOffset + 3];
                                            au16Temp[1] = pu16Cluster[u16FirstCharOffset + 4];
                                            au16Temp[2] = pu16Cluster[u16FirstCharOffset + 5];
                                            au16Temp[3] = pu16Cluster[u16FirstCharOffset + 0];
                                            au16Temp[4] = pu16Cluster[u16FirstCharOffset - 1];
                                            au16Temp[5] = pu16Cluster[u16FirstCharOffset + 2];
                                            au16Temp[6] = pu16Cluster[u16FirstCharOffset + 1];

                                            pau16CharFeatures[u16FirstCharOffset + 2] = pau16CharFeatures[u16FirstCharOffset + 2] | LE_CHAR_FEATURE_BLWF;
                                            pau16CharFeatures[u16FirstCharOffset + 4] = pau16CharFeatures[u16FirstCharOffset + 4] | LE_CHAR_FEATURE_BLWF;
                                        }
                                        else
                                        {
                                            au16Temp[0] = pu16Cluster[u16FirstCharOffset + 3];
                                            au16Temp[1] = pu16Cluster[u16FirstCharOffset + 4];
                                            au16Temp[2] = pu16Cluster[u16FirstCharOffset + 0];
                                            au16Temp[3] = pu16Cluster[u16FirstCharOffset - 1];
                                            au16Temp[4] = pu16Cluster[u16FirstCharOffset + 2];
                                            au16Temp[5] = pu16Cluster[u16FirstCharOffset + 1];
                                            au16Temp[6] = pu16Cluster[u16FirstCharOffset + 5];

                                            pau16CharFeatures[u16FirstCharOffset + 1] = pau16CharFeatures[u16FirstCharOffset + 1] | LE_CHAR_FEATURE_BLWF;
                                            pau16CharFeatures[u16FirstCharOffset + 3] = pau16CharFeatures[u16FirstCharOffset + 3] | LE_CHAR_FEATURE_BLWF;
                                        }

                                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVS);
                                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);

                                        for( k = -1; k < 6; k++ )
                                        {
                                            pu16Cluster[u16FirstCharOffset + k] = au16Temp[k+1];
                                        }

                                        bMatched = TRUE;
                                        bNeedBlwf = TRUE;
                                        bHalantSwap = TRUE;

                                        u16RemainLen = u16RemainLen - 7;
                                    }
                                    break;
                                default:
                                    break;
                                }
                            }
                        }
                        else if ( ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset+5]) == HINDI_DEPVOW ) &&
                                ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset+4]) == HINDI_DEPVOW ) &&
                                ( _msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[u16FirstCharOffset + 2], pu16Cluster[u16FirstCharOffset + 3]) ) &&
                                ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset+1]) == HINDI_DEPVOW ) &&
                                ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset]) == HINDI_CON ) &&
                                ( !_msAPI_MLE_FontHindiCharIsRA(eScript, pu16Cluster[u16FirstCharOffset]) ) )
                        {
                            au16Temp[0] = pu16Cluster[u16FirstCharOffset];
                            au16Temp[1] = pu16Cluster[u16FirstCharOffset + 4];
                            au16Temp[2] = pu16Cluster[u16FirstCharOffset + 1];
                            au16Temp[3] = pu16Cluster[u16FirstCharOffset + 3];
                            au16Temp[4] = pu16Cluster[u16FirstCharOffset + 2];
                            au16Temp[5] = pu16Cluster[u16FirstCharOffset + 5];

                            pau16CharFeatures[u16FirstCharOffset + 3] = pau16CharFeatures[u16FirstCharOffset + 3] | LE_CHAR_FEATURE_BLWF;

                            *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVS);
                            *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);

                            for( i = 0; i < 6; i++ )
                            {
                                pu16Cluster[u16FirstCharOffset + i] = au16Temp[i];
                            }

                            bMatched = TRUE;
                            bNeedBlwf = TRUE;
                            bHalantSwap = TRUE;

                            u16RemainLen = u16RemainLen - 6;
                        }
                    }
    #endif
                }

                if ( u16RemainLen >= 5 )
                {
                    U16 au16Temp[5];
                    U16 i;

                    u16FirstCharOffset = u16RemainLen - 5;

                    if ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset + 4]) == HINDI_CON
                            && _msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[u16FirstCharOffset + 3], pu16Cluster[u16FirstCharOffset + 4])
                            && _msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[u16FirstCharOffset + 1], pu16Cluster[u16FirstCharOffset + 2])
                            && _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset]) == HINDI_CON
                            && !_msAPI_MLE_FontHindiCharIsRA(eScript, pu16Cluster[u16FirstCharOffset]) )
                    {
                        au16Temp[0] = pu16Cluster[u16FirstCharOffset];
                        au16Temp[1] = pu16Cluster[u16FirstCharOffset + 2];
                        au16Temp[2] = pu16Cluster[u16FirstCharOffset + 1];
                        au16Temp[3] = pu16Cluster[u16FirstCharOffset + 4];
                        au16Temp[4] = pu16Cluster[u16FirstCharOffset + 3];

                        pau16CharFeatures[u16FirstCharOffset + 3] = pau16CharFeatures[u16FirstCharOffset + 3] | LE_CHAR_FEATURE_BLWF;
                        pau16CharFeatures[u16FirstCharOffset + 1] = pau16CharFeatures[u16FirstCharOffset + 1] | LE_CHAR_FEATURE_BLWF;

                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVS);
                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);

                        for( i = 0; i < 5; i++ )
                        {
                            pu16Cluster[u16FirstCharOffset + i] = au16Temp[i];
                        }

                        bMatched = TRUE;
                        bNeedBlwf = TRUE;
                        bHalantSwap = TRUE;

                        u16RemainLen = u16RemainLen - 5;
                    }
    #ifdef __KNDA_FONT__
                    //blwf + two-part
                    else if ( eScript == HINDI_SCRIPT_KNDA )
                    {
                        if ( _msAPI_MLE_FontHindiGetCharSpecialType(eScript, pu16Cluster[u16FirstCharOffset + 4]) == HINDI_SP_RIGHT_POS
                            && _msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[u16FirstCharOffset + 2], pu16Cluster[u16FirstCharOffset + 3])
                            && (_msAPI_MLE_FontHindiGetCharSpecialType(eScript, pu16Cluster[u16FirstCharOffset + 1]) == HINDI_SP_CENTER_T_UP_POS
                            || _msAPI_MLE_FontHindiGetCharSpecialType(eScript, pu16Cluster[u16FirstCharOffset + 1]) == HINDI_SP_TWOPART_JOINER)
                            && _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset]) == HINDI_CON
                            && !_msAPI_MLE_FontHindiCharIsRA(eScript, pu16Cluster[u16FirstCharOffset]) )
                        {
                            au16Temp[0] = pu16Cluster[u16FirstCharOffset];
                            au16Temp[1] = pu16Cluster[u16FirstCharOffset + 1];
                            au16Temp[2] = pu16Cluster[u16FirstCharOffset + 3];
                            au16Temp[3] = pu16Cluster[u16FirstCharOffset + 2];
                            au16Temp[4] = pu16Cluster[u16FirstCharOffset + 4];

                            pau16CharFeatures[u16FirstCharOffset + 2] = pau16CharFeatures[u16FirstCharOffset + 2] | LE_CHAR_FEATURE_BLWF;

                            *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVS);
                            *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);

                            for( i = 0; i < 5; i++ )
                            {
                                pu16Cluster[u16FirstCharOffset + i] = au16Temp[i];
                            }

                            bMatched = TRUE;
                            bNeedBlwf = TRUE;
                            bHalantSwap = TRUE;

                            u16RemainLen = u16RemainLen - 5;
                        }
            //blwf + two-part
                        else if ( ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset+4]) == HINDI_DEPVOW ) &&
                            ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset+3]) == HINDI_DEPVOW ) &&
                            ( _msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[u16FirstCharOffset + 1], pu16Cluster[u16FirstCharOffset + 2]) ) &&
                            ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset]) == HINDI_CON ) &&
                            ( !_msAPI_MLE_FontHindiCharIsRA(eScript, pu16Cluster[u16FirstCharOffset]) ) )
                        {
                            if (msAPI_MLE_FontKannadaCharIsBeforeSubscript(pu16Cluster[u16FirstCharOffset + 3]) &&
                                msAPI_MLE_FontKannadaCharIsBeforeSubscript(pu16Cluster[u16FirstCharOffset + 4]))
                            {
                                //reordering Classes for Kannada 0xcc6/0xcc2
                                au16Temp[0] = pu16Cluster[u16FirstCharOffset];
                                au16Temp[1] = pu16Cluster[u16FirstCharOffset + 3];
                                au16Temp[2] = pu16Cluster[u16FirstCharOffset + 4];
                                au16Temp[3] = pu16Cluster[u16FirstCharOffset + 2];
                                au16Temp[4] = pu16Cluster[u16FirstCharOffset + 1];

                                pau16CharFeatures[u16FirstCharOffset + 3] = pau16CharFeatures[u16FirstCharOffset + 3] | LE_CHAR_FEATURE_BLWF;

                                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWF);
                            }
                            else
                            {
                                au16Temp[0] = pu16Cluster[u16FirstCharOffset];
                                au16Temp[1] = pu16Cluster[u16FirstCharOffset + 2];
                                au16Temp[2] = pu16Cluster[u16FirstCharOffset + 1];
                                au16Temp[3] = pu16Cluster[u16FirstCharOffset + 3];
                                au16Temp[4] = pu16Cluster[u16FirstCharOffset + 4];

                                pau16CharFeatures[u16FirstCharOffset + 1] = pau16CharFeatures[u16FirstCharOffset + 1] | LE_CHAR_FEATURE_BLWF;

                                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVS);
                                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);
                            }


                            

                            for( i = 0; i < 5; i++ )
                            {
                                pu16Cluster[u16FirstCharOffset + i] = au16Temp[i];
                            }

                            bMatched = TRUE;
                            bNeedBlwf = TRUE;
                            bHalantSwap = TRUE;

                            u16RemainLen = u16RemainLen - 5;
                        }
                    }
    #endif //#ifdef __KNDA_FONT__
                }
            }

    #endif

            if ( u16RemainLen >= 5 )
            {
                U16 au16Temp[5];
                U16 i;

                u16FirstCharOffset = u16RemainLen - 5;

                if ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset + 4]) == HINDI_CON
                        && _msAPI_MLE_FontHindiCharIsHalant(eScript, pu16Cluster[u16FirstCharOffset + 3])
                        && _msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[u16FirstCharOffset + 1], pu16Cluster[u16FirstCharOffset + 2])
                        && _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset]) == HINDI_CON
                        && !_msAPI_MLE_FontHindiCharIsRA(eScript, pu16Cluster[u16FirstCharOffset]) )
                    {
                    au16Temp[0] = pu16Cluster[u16FirstCharOffset];
    #ifdef __MLYM_FONT__
                    if ( eScript == HINDI_SCRIPT_MLYM )
                    {
                        au16Temp[1] = pu16Cluster[u16FirstCharOffset + 2];
                        au16Temp[2] = pu16Cluster[u16FirstCharOffset + 1];
                        au16Temp[3] = pu16Cluster[u16FirstCharOffset + 4];
                        au16Temp[4] = pu16Cluster[u16FirstCharOffset + 3];

                        pau16CharFeatures[u16FirstCharOffset + 1] = pau16CharFeatures[u16FirstCharOffset + 1] | LE_CHAR_FEATURE_BLWF;
                    }
                    else
    #endif
                    {
                        au16Temp[1] = pu16Cluster[u16FirstCharOffset + 3];
                        au16Temp[2] = pu16Cluster[u16FirstCharOffset + 2];
                        au16Temp[3] = pu16Cluster[u16FirstCharOffset + 1];
                        au16Temp[4] = pu16Cluster[u16FirstCharOffset + 4];

                        pau16CharFeatures[u16FirstCharOffset + 2] = pau16CharFeatures[u16FirstCharOffset + 2] | LE_CHAR_FEATURE_BLWF;
                    }

                    for( i = 0; i < 5; i++ )
                    {
                        pu16Cluster[u16FirstCharOffset + i] = au16Temp[i];
                    }


                    bMatched = TRUE;
                    bNeedBlwf = TRUE;
                    bHalantSwap = TRUE;
                    u16RemainLen = u16RemainLen - 5;
                }
            }

            if ( !bMatched && u16RemainLen >= 5 && u16RemainLen <= (u16CurrentSize - (bWithRphf ? 2 : 0)) )
            {
                U16 i;

                u16FirstCharOffset = u16RemainLen - 5;

                if ( u16FirstCharOffset == 0
                     && _msAPI_MLE_FontHindiCharIsRA(eScript, pu16Cluster[u16FirstCharOffset])
                     && _msAPI_MLE_FontHindiCharIsHalant(eScript, pu16Cluster[u16FirstCharOffset + 1])
                     && _msAPI_MLE_FontHindiCharIsRA(eScript, pu16Cluster[u16FirstCharOffset + 2])
                     && _msAPI_MLE_FontHindiCharIsHalant(eScript, pu16Cluster[u16FirstCharOffset + 3])
                     && _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset + 4]) == HINDI_CON )
                {
                    if ( pau16Consumed )
                    {
                        pau16Consumed[u16FirstCharOffset + 2] = pau16Consumed[u16FirstCharOffset + 2] + 1;
                    }

                    if ( *pu16ClustIndex >= u16FirstCharOffset + 2 )
                    {
                        *pu16ClustIndex = *pu16ClustIndex - 1;
                    }

                    //removed a RA and shift one character to left
                    for ( i = u16FirstCharOffset + 2; i < (u16CurrentSize - 1); i++ )
                    {
                        pu16Cluster[i] = pu16Cluster[i + 1];
                        pau16CharFeatures[i] = pau16CharFeatures[i + 1];
                    }

                    u16CurrentSize = u16CurrentSize - 1;
                    bMatched = TRUE;
                    bHalantSwap = TRUE;
                    u16RemainLen = u16RemainLen - 5;
                }
            }

            if ( !bMatched && u16RemainLen >= 4 && u16RemainLen < (u16CurrentSize - (bWithRphf ? 2 : 0)) )
            {
                U16 i;

                u16FirstCharOffset = u16RemainLen - 4;

                if ( u16FirstCharOffset == 0
                    && _msAPI_MLE_FontHindiCharIsRA(eScript, pu16Cluster[u16FirstCharOffset])
                    && _msAPI_MLE_FontHindiCharIsHalant(eScript, pu16Cluster[u16FirstCharOffset + 1])
                    && _msAPI_MLE_FontHindiCharIsRA(eScript, pu16Cluster[u16FirstCharOffset + 2])
                    && _msAPI_MLE_FontHindiCharIsHalant(eScript, pu16Cluster[u16FirstCharOffset + 3]) )
                {
                    if ( pau16Consumed )
                    {
                        pau16Consumed[u16FirstCharOffset + 2] = pau16Consumed[u16FirstCharOffset + 2] + 1;
                    }

                    if ( *pu16ClustIndex >= u16FirstCharOffset + 2 )
                    {
                        *pu16ClustIndex = *pu16ClustIndex - 1;
                    }

                    //removed a RA and shift one character to left
                    for ( i = u16FirstCharOffset + 2; i < (u16CurrentSize - 1); i++ )
                    {
                        pu16Cluster[i] = pu16Cluster[i + 1];
                        pau16CharFeatures[i] = pau16CharFeatures[i + 1];
                    }

                    u16CurrentSize = u16CurrentSize - 1;
                    bMatched = TRUE;
                    bHalantSwap = TRUE;
                    u16RemainLen = u16RemainLen - 4;
                }
            }

    #if (defined(__TELUGU_FONT__) || defined(__KNDA_FONT__))

            if ( ( ( eScript == HINDI_SCRIPT_TELU ) || ( eScript == HINDI_SCRIPT_KNDA ) ) && ( u16RemainLen >= 4 ) )
            {
                U16 au16Temp[4];
                U16 i;

                u16FirstCharOffset = u16RemainLen - 4;

                if ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16FirstCharOffset]) == HINDI_CON
                        && _msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[u16FirstCharOffset + 1], pu16Cluster[u16FirstCharOffset + 2])
                        && _msAPI_MLE_FontHindiVectorCharIsComposed( eScript, pu16Cluster[u16FirstCharOffset + 3])
                        && !_msAPI_MLE_FontHindiCharIsRA(eScript, pu16Cluster[u16FirstCharOffset]) )
                {
                    //This feature is applied only on the base glyph if the syllable ends with a halant.
                    if ( _msAPI_MLE_FontHindiCharIsHalant( eScript, pu16Cluster[u16FirstCharOffset + 3]) )
                    {
                        pau16CharFeatures[u16FirstCharOffset] = pau16CharFeatures[u16FirstCharOffset] | LE_CHAR_FEATURE_HALN;

                        bNeedHaln = TRUE;
                    }

                        if ( ( *pu32FeatureTags & _HindiAkhnFeatureMask ) ||
                            ( ( eScript == HINDI_SCRIPT_KNDA ) &&
                            (!(_msAPI_MLE_FontHindiCharIsHalant(eScript, pu16Cluster[u16FirstCharOffset + 1]) &&
                            _msAPI_MLE_FontHindiCharIsHalant(eScript, pu16Cluster[u16FirstCharOffset + 3]))) &&
                            (!msAPI_MLE_FontKannadaCharIsBeforeSubscript(pu16Cluster[u16FirstCharOffset + 3])) ) )
                        {
                            au16Temp[0] = pu16Cluster[u16FirstCharOffset];
                            au16Temp[1] = pu16Cluster[u16FirstCharOffset + 2];
                            au16Temp[2] = pu16Cluster[u16FirstCharOffset + 1];
                            au16Temp[3] = pu16Cluster[u16FirstCharOffset + 3];

                            pau16CharFeatures[u16FirstCharOffset + 1] = pau16CharFeatures[u16FirstCharOffset + 1] | LE_CHAR_FEATURE_BLWF;
                        }
                        else
                        {
                            au16Temp[0] = pu16Cluster[u16FirstCharOffset];
                            au16Temp[1] = pu16Cluster[u16FirstCharOffset + 3];
                            au16Temp[2] = pu16Cluster[u16FirstCharOffset + 2];
                            au16Temp[3] = pu16Cluster[u16FirstCharOffset + 1];

                            pau16CharFeatures[u16FirstCharOffset + 2] = pau16CharFeatures[u16FirstCharOffset + 2] | LE_CHAR_FEATURE_BLWF;
                        }

                    *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVS);
                    *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);

                    for( i = 0; i < 4; i++ )
                    {
                        pu16Cluster[u16FirstCharOffset + i] = au16Temp[i];
                    }

                    bMatched = TRUE;
                    bNeedBlwf = TRUE;
                    bHalantSwap = TRUE;

                    u16RemainLen = u16RemainLen - 4;
                }
            }

    #endif

            if ( !bMatched && u16RemainLen > 2 )
            {
                //BOOLEAN bPstfSwap = FALSE;

                u16FirstCharOffset = u16RemainLen - 2;

                if ( _msAPI_MLE_FontHindiCharIsBlwf(eScript, pu16Cluster[u16FirstCharOffset], pu16Cluster[u16FirstCharOffset + 1]) )
                {
                    U16 u16TempGlyphId = pu16Cluster[u16FirstCharOffset];
                    U16 u16PreChar = 0;
                    U16 u16PreCharOffset = 0;
                    BOOLEAN bSwapDecision = FALSE;

                    u16PreChar = _msAPI_MLE_FontGetPreCharIgnoreNukta(eScript, pu16Cluster, u16FirstCharOffset + 1, u16FirstCharOffset, &u16PreCharOffset);

    #if (defined(__TELUGU_FONT__) || defined(__KNDA_FONT__))
                    if ( ( eScript == HINDI_SCRIPT_TELU ) || ( eScript == HINDI_SCRIPT_KNDA ) )
                    {
                        if ( u16PreChar > 0 )
                        {
                            if ( ( _msAPI_MLE_FontHindiGetCharType(eScript, u16PreChar) == HINDI_CON ) || ( u16PreChar == TELUGU_DV_E) || ( u16PreChar == TELUGU_ADV_AI) || ( u16PreChar == KANNADA_DV_I) || ( u16PreChar == KANNADA_DV_E) || ( u16PreChar == KANNADA_DV_UU) )
                                bSwapDecision = TRUE;
                        }
                    }
                    else
    #endif
                    if ( u16PreChar > 0 && _msAPI_MLE_FontHindiGetCharType(eScript, u16PreChar) == HINDI_CON )
                    {
    #if (defined(__MLYM_FONT__))
                        if ( eScript == HINDI_SCRIPT_MLYM )
                        {
                            if ( (u16FirstCharOffset > 0) && ( _msAPI_MLE_FontHindiCharWithNukta(eScript, pu16Cluster[u16FirstCharOffset-1]) ) )  //For Malayalam, add consonant with nukta exception case
                                bSwapDecision = FALSE;
                            else
                                bSwapDecision = TRUE;
                        }
                        else
    #endif
                            bSwapDecision = TRUE;
                    }

                    if ( bSwapDecision )
                    {
                        if ( (u16FirstCharOffset + 2 >= u16CurrentSize) || (pu16Cluster[u16FirstCharOffset + 2] != FONT_CONTROL_ZWJ && !_msAPI_MLE_FontHindiCharIsNukta(eScript, pu16Cluster[u16FirstCharOffset + 2])) )
                        {
                            pu16Cluster[u16FirstCharOffset] = pu16Cluster[u16FirstCharOffset + 1];
                            pu16Cluster[u16FirstCharOffset + 1] = u16TempGlyphId;

                            pau16CharFeatures[u16FirstCharOffset] = pau16CharFeatures[u16FirstCharOffset] | LE_CHAR_FEATURE_BLWF;

                            bMatched = TRUE;
                            bNeedBlwf = TRUE;
                            bHalantSwap = TRUE;
                            u16RemainLen = u16PreCharOffset;
    #if (defined(__TELUGU_FONT__) || defined(__KNDA_FONT__))
                            if ( ( eScript == HINDI_SCRIPT_TELU ) || ( eScript == HINDI_SCRIPT_KNDA ) )
                            {
                                if ( *pu32FeatureTags & _HindiPrivTwoPartJoinFeatureMask )
                                    u16RemainLen++;
                            }
    #endif
                        }
                    }
                }
                else if ( u16FirstCharOffset + 2 <= u16CurrentSize )
                {
                    if ( _msAPI_MLE_FontHindiCharIsPstf(eScript, pu16Cluster[u16FirstCharOffset], pu16Cluster[u16FirstCharOffset + 1]) )
                    {
                        U16 u16TempGlyphId = pu16Cluster[u16FirstCharOffset];
                        U16 u16PreChar = 0;
                        U16 u16PreCharOffset = 0;

                        //u16PreChar = _msAPI_MLE_FontGetPreCharIgnoreNukta(eScript, pu16Cluster, u16FirstCharOffset + 1, u16FirstCharOffset, &u16PreCharOffset);
                        u16PreChar = _msAPI_MLE_FontGetPreCharIgnoreNukta(eScript, pu16Cluster, u16FirstCharOffset + 2, u16FirstCharOffset + 1, &u16PreCharOffset);

                        if ( u16PreChar > 0 && _msAPI_MLE_FontHindiGetCharType(eScript, u16PreChar) == HINDI_CON )
                        {
                            if ( (u16FirstCharOffset + 2 >= u16CurrentSize) || (pu16Cluster[u16FirstCharOffset + 2] != FONT_CONTROL_ZWJ && !_msAPI_MLE_FontHindiCharIsNukta(eScript, pu16Cluster[u16FirstCharOffset + 2])) )
                            {
                                pu16Cluster[u16FirstCharOffset] = pu16Cluster[u16FirstCharOffset + 1];
                                pu16Cluster[u16FirstCharOffset + 1] = u16TempGlyphId;

                                pau16CharFeatures[u16FirstCharOffset] = pau16CharFeatures[u16FirstCharOffset] | LE_CHAR_FEATURE_PSTF;

                                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_PSTF);

                                bPstfSwap = TRUE;
                                bMatched = TRUE;
                                bHalantSwap = TRUE;
                                u16RemainLen = u16PreCharOffset;
                                *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_RKRF);
                            }
                        }
                    }

    #ifdef __BENGALI_FONT__
                    //Feature Tag: "pstf"
                    //Applying this feature substitutes post-base forms, such as the 'Bengali Ya'.
                    //The post-base form of the Ya is substituted, when it is the last consonant in a syllable:
                    if ( eScript == HINDI_SCRIPT_BENG )
                    {
                        S16 i;
                        BOOLEAN bLastCONFound = FALSE;

                        for(i=(u16CurrentSize-1); i >= 0; i--)
                        {
                            if ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[i]) == HINDI_CON )
                            {
                                bLastCONFound = TRUE;
                                break;
                            }
                        }

                        if ( bLastCONFound )
                        {
                            S16 k = 0;

                            if ( bPstfSwap )
                            {
                                //already pstf swap
                                if ( ( i >= 0 ) && ( i < (u16CurrentSize-1) ) )
                                {
                                    if ( IS_BENGALI_POST_BASE_CON(pu16Cluster[i]) && IS_BENGALI_HALANT_CHAR(pu16Cluster[i+1]) )
                                    {
                                        //Invert logic for half flag
                                        pau16CharFeatures[i] = pau16CharFeatures[i] | LE_CHAR_FEATURE_NO_HALF;
                                    }

                                    if ( (i-1) >= 0 )
                                    {
                                        //for <rphf> and <half>, features are applied to Consonant + Halant combinations
                                        if ( ( i-1 ) == 0 )
                                        {
                                            //only one character, it can't have Consonant + Halant combinations, remove Half feature
                                        }
                                        else
                                        {
                                            //search Half condition
                                            for(k=(i-1); k>0; k--)
                                            {
                                                if ( ( IS_BENGALI_HALANT_CHAR(pu16Cluster[k]) )
                                                && ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[k-1]) == HINDI_CON ) )
                                                {
                                                    //Half condition found, keep Half feature
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            else
                            {
                                if ( (i-1) >= 0 )
                                {
                                    if ( IS_BENGALI_POST_BASE_CON(pu16Cluster[i]) && IS_BENGALI_HALANT_CHAR(pu16Cluster[i-1]) )
                                    {
                                        U16 u16TempGlyphId = pu16Cluster[i-1];

                                        pu16Cluster[i-1] = pu16Cluster[i];
                                        pu16Cluster[i] = u16TempGlyphId;

                                        pau16CharFeatures[i-1] = pau16CharFeatures[i-1] | LE_CHAR_FEATURE_PSTF;
                                        //Invert logic for half flag
                                        pau16CharFeatures[i-1] = pau16CharFeatures[i-1] | LE_CHAR_FEATURE_NO_HALF;

                                        bMatched = TRUE;
                                        bHalantSwap = TRUE;
                                        bPstfSwap = TRUE;
                                        u16RemainLen = i-1;

                                        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_PSTF);

                                        if ( (i-2) >= 0 )
                                        {
                                            //for <rphf> and <half>, features are applied to Consonant + Halant combinations
                                            if ( ( i-2 ) == 0 )
                                            {
                                                //only one character, it can't have Consonant + Halant combinations, remove Half feature
                                            }
                                            else
                                            {
                                                //search Half condition
                                                for(k=(i-2); k>0; k--)
                                                {
                                                    if ( ( IS_BENGALI_HALANT_CHAR(pu16Cluster[k]) )
                                                    && ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[k-1]) == HINDI_CON ) )
                                                    {
                                                        //Half condition found, keep Half feature
                                                        break;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {
                                        //if ( (i-1) >= 0 )
                                        {
                                            //for <rphf> and <half>, features are applied to Consonant + Halant combinations
                                            if ( ( i-1 ) == 0 )
                                            {
                                                //only one character, it can't have Consonant + Halant combinations, remove Half feature
                                            }
                                            else
                                            {
                                                //search Half condition
                                                for(k=(i-1); k>0; k--)
                                                {
                                                    if ( ( IS_BENGALI_HALANT_CHAR(pu16Cluster[k]) )
                                                    && ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[k-1]) == HINDI_CON ) )
                                                    {
                                                        //Half condition found, keep Half feature
                                                        break;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            if ( k == 0 )
                            {
                                //Half condition not found, remove Half feature
                                *pu32FeatureTags &= (~_HindiHalfFeatureMask);
                            }
                        }
                    }
    #endif
                }
            }

            if ( !bMatched && u16RemainLen > 1 )
            {
                U16 u16PreChar = 0;
                U16 u16PreCharOffset = 0;

                u16FirstCharOffset = u16RemainLen - 2;

                if ( _msAPI_MLE_FontHindiCharIsHalant(eScript, pu16Cluster[u16FirstCharOffset + 1]) )
                {
                    u16PreChar = _msAPI_MLE_FontGetPreCharIgnoreNukta(eScript, pu16Cluster, u16FirstCharOffset + 2, u16FirstCharOffset + 1, &u16PreCharOffset);

                    if ( u16PreChar > 0 && _msAPI_MLE_FontHindiGetCharType(eScript, u16PreChar) == HINDI_CON )
                    {
                        if ( u16FirstCharOffset + 2 == u16CurrentSize )
                        {
                            pau16CharFeatures[u16PreCharOffset] = pau16CharFeatures[u16PreCharOffset] | LE_CHAR_FEATURE_HALN;

                            bMatched = TRUE;
                            bNeedHaln = TRUE;
                            u16RemainLen = u16RemainLen - 1;
                        }
                        else
                        {
                            if ( pu16Cluster[u16FirstCharOffset + 2] != FONT_CONTROL_ZWJ && !_msAPI_MLE_FontHindiCharIsHalant(eScript, pu16Cluster[u16FirstCharOffset + 2]) && _msAPI_MLE_FontGetNextConChar(eScript, pu16Cluster, u16CurrentSize, u16FirstCharOffset + 1, NULL) == 0 )
                            {
                                pau16CharFeatures[u16PreCharOffset] = pau16CharFeatures[u16PreCharOffset] | LE_CHAR_FEATURE_HALN;
                                bMatched = TRUE;
                                bNeedHaln = TRUE;
                                u16RemainLen = u16RemainLen - 1;
                            }
    #if (defined(__KNDA_FONT__))
                            else if ( eScript == HINDI_SCRIPT_KNDA )
                            {
                                //rphf: RA consonant will be reordered to after base position, so don't check _msAPI_MLE_FontGetNextConChar()
                                if ( bWithRphf && pu16Cluster[u16FirstCharOffset + 2] != FONT_CONTROL_ZWJ && !_msAPI_MLE_FontHindiCharIsHalant(eScript, pu16Cluster[u16FirstCharOffset + 2]) )
                                {
                                    pau16CharFeatures[u16PreCharOffset] = pau16CharFeatures[u16PreCharOffset] | LE_CHAR_FEATURE_HALN;
                                    bMatched = TRUE;
                                    bNeedHaln = TRUE;
                                    u16RemainLen = u16RemainLen - 1;
                                }
                            }
    #endif
                        }
                    }
                }
                else    if ( *pu32FeatureTags & _HindiAbvsFeatureMask )
                {
                    //Todo, need to consider more cases
                    pau16CharFeatures[1] = pau16CharFeatures[1] | LE_CHAR_FEATURE_ABVS;
                }
            }

            if ( !bMatched )
            {
                u16RemainLen = u16RemainLen - 1;
            }
        }
    }
#if (defined(__TAMIL_FONT__) || defined(__MLYM_FONT__))
    if (( eScript == HINDI_SCRIPT_TAML ) || ( eScript == HINDI_SCRIPT_MLYM ) )
    {
        U16 u16BaseConsonant = 0;
        S16 i;
        BOOLEAN bLastCONFound = FALSE;
        BOOLEAN bFoundBelowBaseForm = FALSE;
        U16 u16Temp = pau16GlyphOrder[0];
        S8 s8PatternCompareDirection = 1;

        for(i=(u16CurrentSize-1); i >= 0; i--)
        {
            if ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[i]) == HINDI_CON )
            {
                bLastCONFound = TRUE;
                break;
            }
        }

        if ( bHalantSwap )
            s8PatternCompareDirection = 1;
        else
            s8PatternCompareDirection = -1;

        if ( bLastCONFound )
        {
            u16BaseConsonant = i;

            while( u16BaseConsonant > 0 )
            {
                 if ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[u16BaseConsonant]) == HINDI_CON )
                 {
                     if ( ( ( u16BaseConsonant > 0 ) &&
                             ( u16BaseConsonant < (u16CurrentSize-1) ) &&
                             ( !_msAPI_MLE_FontHindiCharIsHalant(eScript, pu16Cluster[u16BaseConsonant + s8PatternCompareDirection]) ) ) ||
                         ( !IS_MLYM_POST_BELOW_BASE_FORM(pu16Cluster[u16BaseConsonant]) ) )
                     {
                         break;
                     }

                     if ( !bHalantSwap )
                     {
                         if ( (u16BaseConsonant > 1) && ( _msAPI_MLE_FontHindiCharWithNukta(eScript, pu16Cluster[u16BaseConsonant-2]) ) && ( _msAPI_MLE_FontHindiCharIsHalant(eScript, pu16Cluster[u16BaseConsonant-1]) ) ) //For Malayalam, add consonant with nukta case
                            break;
                     }
                 }

                if ( IS_MLYM_POST_BASE_FORM(pu16Cluster[u16BaseConsonant]) )
                {
                    if ( bFoundBelowBaseForm )
                    {
                        break;
                    }
                }
                else if ( IS_MLYM_BELOW_BASE_FORM(pu16Cluster[u16BaseConsonant]) )
                {
                    bFoundBelowBaseForm = TRUE;
                }

                u16BaseConsonant--;
            }

            *ps8BaseConsonantGlyph = (S8)u16BaseConsonant;

            //search pstf pattern
            for ( i=u16BaseConsonant+1; i<(u16CurrentSize-1); i++ )
            {
                BOOLEAN bPSTFMatched  = FALSE;

                if ( bHalantSwap )
                {
                    //swap pattern detect order
                    if ( _msAPI_MLE_FontHindiCharIsPstf(eScript, pu16Cluster[i+1], pu16Cluster[i]) )
                    {
                        //At this position, u16PreChar is a consonant, and consonant + halant characters already be swapped
                        bPSTFMatched = TRUE;
                    }
                }
                else
                {
                    if ( _msAPI_MLE_FontHindiCharIsPstf(eScript, pu16Cluster[i], pu16Cluster[i+1]) )
                    {
                        U16 u16TempGlyphId = pu16Cluster[i];

                        pu16Cluster[i] = pu16Cluster[i + 1];
                        pu16Cluster[i + 1] = u16TempGlyphId;

                        bPSTFMatched = TRUE;
                    }
                }

                if ( bPSTFMatched )
                {
                    pau16CharFeatures[i] = pau16CharFeatures[i] | LE_CHAR_FEATURE_PSTF;
                    //Invert logic for half flag
                    pau16CharFeatures[i] = pau16CharFeatures[i] | LE_CHAR_FEATURE_NO_HALF;

                    *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_PSTF);
                    *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_PSTS);

                    bPSTFMatched = FALSE;

                    if ( IS_MLYM_PREBASE_CHAR(pu16Cluster[i]) )
                    {
                        U16 u16TempOrder = pau16GlyphOrder[i-1];

                        //In this case, Ra is the last consonant in this syllable, halant will be invisible
                        //Swap Display Order
                        pau16GlyphOrder[i-1] = pau16GlyphOrder[i];
                        pau16GlyphOrder[i] = u16TempOrder;

                        pu8PrebaseSwapDispOrder[i-1] = FALSE;
                    }
                }
            }

            if ( u16BaseConsonant > 1 )
            {
                if ( ( _msAPI_MLE_FontHindiGetCharType(eScript, pu16Cluster[0]) == HINDI_DEPVOW ) &&
                        ( _msAPI_MLE_FontHindiGetCharSpecialType(eScript, pu16Cluster[0]) == HINDI_SP_LEFT_JOINER ) )
                {
                    //Swap Display Order, put prebase depend vowel glyph to just before base consonant position
                    for(i=1;i<u16BaseConsonant;i++)
                    {
                        pau16GlyphOrder[i-1] = pau16GlyphOrder[i];
                    }
                    pau16GlyphOrder[u16BaseConsonant-1] = u16Temp;

                    pu8PrebaseSwapDispOrder[u16BaseConsonant-2] = TRUE;
                }
            }
        }
    }
#endif

    if ( bNeedBlwf )
    {
        /* kf + H --> Ks*/
        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_RKRF);
        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWF);
        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_VATU);

        _msAPI_MLE_FontHindiFeatureWithBlwf(eScript, *pu32FeatureTags, &eSpType);
        if ( eSpType == HINDI_SP_LEFT_T_UP_POS || eSpType == HINDI_SP_CENTER_T_UP_POS )
        {
            /*{Kh} + Kf -> Lf*/
            *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVS);
            *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_ABVM);
        }
        else if ( eSpType == HINDI_SP_CENTER_T_DOWN_POS || eSpType == HINDI_SP_RIGHT_T_DOWN_POS )
        {
            /*{Kh} + Kf -> Lf*/
            *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWS);
            *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWM);
        }
    }

    if ( bNeedHaln )
    {
        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_HALN);
        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWS);
        *pu32FeatureTags = _msAPI_MLE_FontHindiSetFeature(eScript, *pu32FeatureTags, HINDI_FEATURE_BLWM);
    }

    *pu16ClusterSize = u16CurrentSize;
}

static U16 _msAPI_MLE_FontHindiVectorRules( HindiScript_e eScript, LE_LanguageTag_e eLang, U16 *pu16Cluster, U16 u16ClusterSize, U16 u16ClustIndex, U16 *pu16Glyph, U16 *pu16OffsetInConcatenation, U16 *pu16OffsetInComposed, U16 *pu16ConcatenationComposedSize, U32 *pu32Features )
{
    const HindiFeatureRecord_t *pasFeatureMap = NULL;
    U8 *pSubstProcess = NULL;
    U16 u16FeatureMapSize = 0;
    LE_OTF_ScriptTag_e eLeScript;
    LE_OTF_FeatureRecord_t asOtfFeatuureTable[LE_OTF_MAX_FEATURE_NUM] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
    U16 u16OutLen = 0, i, j;
    U16 au16Consumed[HINDI_CONVERT_MAX] = {0};
    U16 au16CharFeatures[HINDI_CONVERT_MAX] = {0};
    U16 au16GlyphOrder[HINDI_CONVERT_MAX] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    U16 au16TempGlyph[HINDI_CONVERT_MAX+1] = {0};
    U8 au8PrebaseSwapDispOrder[HINDI_CONVERT_MAX] = {0};
    S8 s8BaseConsonantGlyph = -1;

    if ( pu32Features == NULL )
    {
        return 0;
    }

    u16FeatureMapSize = _msAPI_MLE_FontHindiGetFeatureMap(eScript, &pasFeatureMap);
    eLeScript = _msAPI_MLE_FontMapScriptTag(eScript);

    _msAPI_MLE_FontVectorReorderCluster(eLeScript, pu16Cluster, &u16ClusterSize, &u16ClustIndex, pu32Features, au16Consumed, au16CharFeatures, au16GlyphOrder, au8PrebaseSwapDispOrder, &s8BaseConsonantGlyph);

    pSubstProcess = msAPI_MLE_Le_CreateSubstProcess(eLeScript, eLang, pu16Cluster, u16ClusterSize, u16ClustIndex, au16Consumed, au16CharFeatures);
    if ( pSubstProcess == NULL )
    {
        return 0;
    }

    if ( _msAPI_MLE_FontMapFeatureTag(pasFeatureMap, u16FeatureMapSize, asOtfFeatuureTable) )
    {
        u16OutLen = msAPI_MLE_Le_SubstProcessGlyphs(pSubstProcess, eLang, (const LE_OTF_FeatureRecord_t *)asOtfFeatuureTable, u16FeatureMapSize, *pu32Features, pu16Glyph, pu16OffsetInConcatenation, pu16OffsetInComposed, pu16ConcatenationComposedSize);
    }

    au16TempGlyph[0] = 0;

    for(j=0;j<u16OutLen;j++)
    {
        au16TempGlyph[j+1] = au16TempGlyph[j] + pu16ConcatenationComposedSize[j];
    }

    //find position of target 0
    for(i=0;i<(u16ClusterSize-1);i++)
    {
        if ( au16GlyphOrder[i] > au16GlyphOrder[i+1] )
        {
            U16 u16Temp;
            S16 s16LeftJoinGlyph = -1;
            S8 s8SwapBaseA = -1, s8SwapBaseB = -1;

            if ( au8PrebaseSwapDispOrder[i] )
            {
                //Find Base Consonant Glyph first, in this case, there should one base consonant glyph at i+2 position
                for(j=0;j<u16OutLen;j++)
                {
                    if ( ( s8BaseConsonantGlyph >= au16TempGlyph[j] ) && ( s8BaseConsonantGlyph < au16TempGlyph[j+1] ) )
                    {
                        s8SwapBaseA = (S8)j;
                        break;
                    }
                }

                s16LeftJoinGlyph = au16GlyphOrder[i+1];
                for(j=0;j<u16OutLen;j++)
                {
                    if ( ( s16LeftJoinGlyph >= au16TempGlyph[j] ) && ( s16LeftJoinGlyph < au16TempGlyph[j+1] ) )
                    {
                        s8SwapBaseB = (S8)j;
                        break;
                    }
                }

                if ( s8SwapBaseA == (s8SwapBaseB+1) )
                {
                    //The base consonant glyph was combined with its previous glyphs and became the first glyph.
                    //Left join glyph should be at the previous position of base glyph, so it is no need to swap position
                }
                else
                {
                    //Move B before A
                    u16Temp = pu16Glyph[s8SwapBaseB];
                    for(j=0;j<(s8SwapBaseA-1);j++)
                    {
                        pu16Glyph[j] = pu16Glyph[j+1];
                    }
                    pu16Glyph[j] = u16Temp;
                }
            }
            else
            {
                //Do Swap A and B

                for(j=0;j<u16OutLen;j++)
                {
                    if ( ( au16GlyphOrder[i] >= au16TempGlyph[j] ) && ( au16GlyphOrder[i] < au16TempGlyph[j+1] ) )
                    {
                        s8SwapBaseA = (S8)j;
                        break;
                    }
                }

                for(j=0;j<u16OutLen;j++)
                {
                    if ( ( au16GlyphOrder[i+1] >= au16TempGlyph[j] ) && ( au16GlyphOrder[i+1] < au16TempGlyph[j+1] ) )
                    {
                        s8SwapBaseB = (S8)j;
                        break;
                    }
                }

                u16Temp = pu16Glyph[s8SwapBaseA];
                pu16Glyph[s8SwapBaseA] = pu16Glyph[s8SwapBaseB];
                pu16Glyph[s8SwapBaseB] = u16Temp;
            }
        }
    }

    msAPI_MLE_Le_FreeSubstProcess(pSubstProcess);

    return u16OutLen;
}

BOOLEAN msAPI_MLE_FontHindiVectorGetNextOffset( HindiScript_e eScript, LE_LanguageTag_e eLang, U16 *pu16InGlyphs, U16 u16GlyphLen, U16 u16NextOffset, U16 *pu16BaseOffset, S16 *ps16XOffset, S16 *ps16YOffset,  S16 *ps16NextXOffset, S16 *ps16NextYOffset, U32 u32FeatureTags )
{
    const HindiFeatureRecord_t *pasFeatureMap = NULL;
    U8 *pPosProcess = NULL;
    U16 u16FeatureMapSize = 0;
    LE_OTF_ScriptTag_e eLeScript;
    LE_OTF_FeatureRecord_t asOtfFeatuureTable[LE_OTF_MAX_FEATURE_NUM] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};
    BOOLEAN bResult = FALSE;

    if ( !msAPI_MLE_FONTBASE_IsVectorFontExist() )
    {
        return FALSE;
    }

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return FALSE;
    }

    u16FeatureMapSize = _msAPI_MLE_FontHindiGetFeatureMap(eScript, &pasFeatureMap);
    eLeScript = _msAPI_MLE_FontMapScriptTag(eScript);

    pPosProcess = msAPI_MLE_Le_CreatePosProcess(eLeScript, eLang, pu16InGlyphs, u16GlyphLen, *pu16BaseOffset, u16NextOffset);
    if ( pPosProcess == NULL )
    {
        return FALSE;
    }

    if ( _msAPI_MLE_FontMapFeatureTag(pasFeatureMap, u16FeatureMapSize, asOtfFeatuureTable) )
    {
        bResult = msAPI_MLE_Le_PosProcessGlyphs(pPosProcess, eLang, (const LE_OTF_FeatureRecord_t *)asOtfFeatuureTable, u16FeatureMapSize, u32FeatureTags, pu16BaseOffset, ps16XOffset, ps16YOffset, ps16NextXOffset, ps16NextYOffset);
    }

    msAPI_MLE_Le_FreePosProcess(pPosProcess);
    return bResult;
}

static BOOLEAN _msAPI_MLE_FontHindiCharIsBlwf( HindiScript_e eScript, U16 u16FirstChar, U16 u16SecondChar )
{
    U16 i;
    BOOLEAN bResult = FALSE;

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return FALSE;
    }

    for ( i = 0; i < HINDI_MAX_SCRIPT_NUM; i++ )
    {
        if ( g_pHindiLangsTbl[i] == NULL )
        {
            break;
        }

        if ( g_pHindiLangsTbl[i]->eScript == eScript )
        {
            if ( g_pHindiLangsTbl[i]->fnCharIsBlwf )
            {
                bResult = g_pHindiLangsTbl[i]->fnCharIsBlwf(u16FirstChar, u16SecondChar);
            }
            break;
        }
    }

    return bResult;
}

static U16 _msAPI_MLE_FontHindiGetFeatureMap( HindiScript_e eScript, const HindiFeatureRecord_t **ppasFeatureMap )
{
    U16 i;
    U16 u16Result = 0;

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return FALSE;
    }

    for ( i = 0; i < HINDI_MAX_SCRIPT_NUM; i++ )
    {
        if ( g_pHindiLangsTbl[i] == NULL )
        {
            break;
        }

        if ( g_pHindiLangsTbl[i]->eScript == eScript )
        {
            if ( g_pHindiLangsTbl[i]->fnGetFeatureMap )
            {
                u16Result = g_pHindiLangsTbl[i]->fnGetFeatureMap(ppasFeatureMap);
            }
            break;
        }
    }

    return u16Result;
}

#endif // __FEATURE_VECTOR_FONT__

/*=======================================================*/
/*================Common porting functions======================*/
/*=======================================================*/
static BOOLEAN _msAPI_MLE_FontHindiCharIsRA( HindiScript_e eScript, U16 u16Character )
{
    U16 i;
    BOOLEAN bResult = FALSE;

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return FALSE;
    }

    for ( i = 0; i < HINDI_MAX_SCRIPT_NUM; i++ )
    {
        if ( g_pHindiLangsTbl[i] == NULL )
        {
            break;
        }

        if ( g_pHindiLangsTbl[i]->eScript == eScript )
        {
            if ( g_pHindiLangsTbl[i]->fnCharIsRA )
            {
                bResult = g_pHindiLangsTbl[i]->fnCharIsRA(u16Character);
            }
            break;
        }
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_FontHindiCharIsHalant( HindiScript_e eScript, U16 u16Character )
{
    U16 i;
    BOOLEAN bResult = FALSE;

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return FALSE;
    }

    for ( i = 0; i < HINDI_MAX_SCRIPT_NUM; i++ )
    {
        if ( g_pHindiLangsTbl[i] == NULL )
        {
            break;
        }

        if ( g_pHindiLangsTbl[i]->eScript == eScript )
        {
            if ( g_pHindiLangsTbl[i]->fnCharIsHalant )
            {
                bResult = g_pHindiLangsTbl[i]->fnCharIsHalant(u16Character);
            }
            break;
        }
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_FontHindiCharIsNukta( HindiScript_e eScript, U16 u16Character )
{
    U16 i;
    BOOLEAN bResult = FALSE;

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return FALSE;
    }

    for ( i = 0; i < HINDI_MAX_SCRIPT_NUM; i++ )
    {
        if ( g_pHindiLangsTbl[i] == NULL )
        {
            break;
        }

        if ( g_pHindiLangsTbl[i]->eScript == eScript )
        {
            if ( g_pHindiLangsTbl[i]->fnCharIsNukta )
            {
                bResult = g_pHindiLangsTbl[i]->fnCharIsNukta(u16Character);
            }
            break;
        }
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_FontHindiCharIsBindu( HindiScript_e eScript, U16 u16Character )
{
    U16 i;
    BOOLEAN bResult = FALSE;

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return FALSE;
    }

    for ( i = 0; i < HINDI_MAX_SCRIPT_NUM; i++ )
    {
        if ( g_pHindiLangsTbl[i] == NULL )
        {
            break;
        }

        if ( g_pHindiLangsTbl[i]->eScript == eScript )
        {
            if ( g_pHindiLangsTbl[i]->fnCharIsBindu )
            {
                bResult = g_pHindiLangsTbl[i]->fnCharIsBindu(u16Character);
            }
            break;
        }
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_FontHindiCharWithNukta( HindiScript_e eScript, U16 u16Character )
{
    U16 i;
    BOOLEAN bResult = FALSE;

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return FALSE;
    }

    for ( i = 0; i < HINDI_MAX_SCRIPT_NUM; i++ )
    {
        if ( g_pHindiLangsTbl[i] == NULL )
        {
            break;
        }

        if ( g_pHindiLangsTbl[i]->eScript == eScript )
        {
            if ( g_pHindiLangsTbl[i]->fnCharWithNukta )
            {
                bResult = g_pHindiLangsTbl[i]->fnCharWithNukta(u16Character);
            }
            break;
        }
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_FontHindiCharIsNoHalfCon( HindiScript_e eScript, U16 u16Character )
{
    U16 i;
    BOOLEAN bResult = FALSE;

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return FALSE;
    }

    for ( i = 0; i < HINDI_MAX_SCRIPT_NUM; i++ )
    {
        if ( g_pHindiLangsTbl[i] == NULL )
        {
            break;
        }

        if ( g_pHindiLangsTbl[i]->eScript == eScript )
        {
            if ( g_pHindiLangsTbl[i]->fnCharIsNoHalfCon )
            {
                bResult = g_pHindiLangsTbl[i]->fnCharIsNoHalfCon(u16Character);
            }
            break;
        }
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_FontHindiCharIsFollowingZWJ( HindiScript_e eScript, U16 u16Character )
{
    U16 i;
    BOOLEAN bResult = FALSE;

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return FALSE;
    }

    for ( i = 0; i < HINDI_MAX_SCRIPT_NUM; i++ )
    {
        if ( g_pHindiLangsTbl[i] == NULL )
        {
            break;
        }

        if ( g_pHindiLangsTbl[i]->eScript == eScript )
        {
            if ( g_pHindiLangsTbl[i]->fnCharIsFollowingZWJ )
            {
                bResult = g_pHindiLangsTbl[i]->fnCharIsFollowingZWJ(u16Character);
            }
            break;
        }
    }

    return bResult;
}

static U16 _msAPI_MLE_FontHindiGetTwoWordLeftChar( HindiScript_e eScript, U16 u16Character )
{
    U16 i;
    U16 u16Result = 0;

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return FALSE;
    }

    for ( i = 0; i < HINDI_MAX_SCRIPT_NUM; i++ )
    {
        if ( g_pHindiLangsTbl[i] == NULL )
        {
            break;
        }

        if ( g_pHindiLangsTbl[i]->eScript == eScript )
        {
            if ( g_pHindiLangsTbl[i]->fnGetTwoWordLeftChar)
            {
                u16Result = g_pHindiLangsTbl[i]->fnGetTwoWordLeftChar(u16Character);
            }
            break;
        }
    }

    return u16Result;
}

static U16 _msAPI_MLE_FontHindiGetTwoWordRightChar( HindiScript_e eScript, U16 u16Character )
{
    U16 i;
    U16 u16Result = 0;

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return FALSE;
    }

    for ( i = 0; i < HINDI_MAX_SCRIPT_NUM; i++ )
    {
        if ( g_pHindiLangsTbl[i] == NULL )
        {
            break;
        }

        if ( g_pHindiLangsTbl[i]->eScript == eScript )
        {
            if ( g_pHindiLangsTbl[i]->fnGetTwoWordRightChar)
            {
                u16Result = g_pHindiLangsTbl[i]->fnGetTwoWordRightChar(u16Character);
            }
            break;
        }
    }

    return u16Result;
}

static HindiCharacter_e _msAPI_MLE_FontHindiGetCharType( HindiScript_e eScript, U16 u16Character )
{
    U16 i;
    HindiCharacter_e eType = HINDI_INVALID;

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return HINDI_INVALID;
    }

    for ( i = 0; i < HINDI_MAX_SCRIPT_NUM; i++ )
    {
        if ( g_pHindiLangsTbl[i] == NULL )
        {
            break;
        }

        if ( g_pHindiLangsTbl[i]->eScript == eScript )
        {
            if ( g_pHindiLangsTbl[i]->fnGetCharType )
            {
                eType = g_pHindiLangsTbl[i]->fnGetCharType(u16Character);
            }
            break;
        }
    }

    return eType;
}

static HindiSpecialCharacter_e _msAPI_MLE_FontHindiGetCharSpecialType( HindiScript_e eScript, U16 u16Character )
{
    U16 i;
    HindiSpecialCharacter_e eType = HINDI_SP_INVALID;

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return HINDI_SP_INVALID;
    }

    for ( i = 0; i < HINDI_MAX_SCRIPT_NUM; i++ )
    {
        if ( g_pHindiLangsTbl[i] == NULL )
        {
            break;
        }

        if ( g_pHindiLangsTbl[i]->eScript == eScript )
        {
            if ( g_pHindiLangsTbl[i]->fnGetCharSpecialType )
            {
                eType = g_pHindiLangsTbl[i]->fnGetCharSpecialType(u16Character);
            }
            break;
        }
    }

    return eType;
}

static HindiOtherCharacterType_e _msAPI_MLE_FontHindiGetCharOtherType( HindiScript_e eScript, U16 u16Character )
{
    U16 i;
    HindiOtherCharacterType_e eType = HINDI_OTYPE_INVALID;

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return HINDI_OTYPE_INVALID;
    }

    for ( i = 0; i < HINDI_MAX_SCRIPT_NUM; i++ )
    {
        if ( g_pHindiLangsTbl[i] == NULL )
        {
            break;
        }

        if ( g_pHindiLangsTbl[i]->eScript == eScript )
        {
            if ( g_pHindiLangsTbl[i]->fnGetCharOtherType )
            {
                eType = g_pHindiLangsTbl[i]->fnGetCharOtherType(u16Character);
            }
            break;
        }
    }

    return eType;
}

static BOOLEAN _msAPI_MLE_FontHindiCharIsPstf( HindiScript_e eScript, U16 u16FirstChar, U16 u16SecondChar )
{
    U16 i;
    BOOLEAN bResult = FALSE;

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return FALSE;
    }

    for ( i = 0; i < HINDI_MAX_SCRIPT_NUM; i++ )
    {
        if ( g_pHindiLangsTbl[i] == NULL )
        {
            break;
        }

        if ( g_pHindiLangsTbl[i]->eScript == eScript )
        {
            if ( g_pHindiLangsTbl[i]->fnCharIsPstf )
            {
                bResult = g_pHindiLangsTbl[i]->fnCharIsPstf(u16FirstChar, u16SecondChar);
            }
            break;
        }
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_FontHindiCharIsLigated( HindiScript_e eScript, U16 u16FirstChar, U16 u16SecondChar, BOOLEAN withZWJ )
{
    U16 i;
    BOOLEAN bResult = FALSE;

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return FALSE;
    }

    for ( i = 0; i < HINDI_MAX_SCRIPT_NUM; i++ )
    {
        if ( g_pHindiLangsTbl[i] == NULL )
        {
            break;
        }

        if ( g_pHindiLangsTbl[i]->eScript == eScript )
        {
            if ( g_pHindiLangsTbl[i]->fnCharIsLigated )
            {
                bResult = g_pHindiLangsTbl[i]->fnCharIsLigated(u16FirstChar, u16SecondChar, withZWJ);
            }
            break;
        }
    }

    return bResult;
}

static BOOLEAN _msAPI_MLE_FontHindiStrWithAkhand( HindiScript_e eScript, U16 *pu16Str, U32 u32StrLen, U16 u16Offset )
{
    U16 i;
    BOOLEAN bResult = FALSE;

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return FALSE;
    }

    for ( i = 0; i < HINDI_MAX_SCRIPT_NUM; i++ )
    {
        if ( g_pHindiLangsTbl[i] == NULL )
        {
            break;
        }

        if ( g_pHindiLangsTbl[i]->eScript == eScript )
        {
            if ( g_pHindiLangsTbl[i]->fnStrWithAkhand )
            {
                bResult = g_pHindiLangsTbl[i]->fnStrWithAkhand(pu16Str, u32StrLen, u16Offset);
            }
            break;
        }
    }

    return bResult;
}

static U32 _msAPI_MLE_FontHindiSetFeature( HindiScript_e eScript, U32 u32FeatureTags, HindiFeature_e eFeature )
{
    U16 i;
    U32 u32Result = u32FeatureTags;

    if ( eScript >= HINDI_MAX_SCRIPT_NUM || eFeature == HINDI_MAX_FEATURE_NUM )
    {
        return u32FeatureTags;
    }

    //Hindi Priv features
    if ( eFeature > HINDI_MAX_FEATURE_NUM )
    {
        switch ( eFeature )
        {
        case HINDI_PRIV_FEATURE_LEFT_JOIN:
            u32Result = (u32FeatureTags | _HindiPrivLeftJoinFeatureMask);
            break;
        case HINDI_PRIV_FEATURE_TWOPART_JOIN:
            u32Result = (u32FeatureTags | _HindiPrivTwoPartJoinFeatureMask );
            break;
        case HINDI_PRIV_FEATURE_PRE_DOTTED:
            u32Result = (u32FeatureTags | _HindiPrivPreDottedFeatureMask);
            break;
        case HINDI_PRIV_FEATURE_POS_DOTTED:
            u32Result = (u32FeatureTags | _HindiPrivPosDottedFeatureMask);
            break;
        case HINDI_PRIV_FEATURE_DONT_CACHED:
            u32Result = (u32FeatureTags | _HindiPrivDontCachedFeatureMask);
            break;
        case HINDI_PRIV_FEATURE_THREEPART:
            u32Result = (u32FeatureTags | _HindiPrivThreePartFeatureMask );
            break;
        default:
            break;
        }
    }
    else
    {
        for ( i = 0; i < HINDI_MAX_SCRIPT_NUM; i++ )
        {
            if ( g_pHindiLangsTbl[i] == NULL )
            {
                break;
            }

            if ( g_pHindiLangsTbl[i]->eScript == eScript )
            {
                if ( g_pHindiLangsTbl[i]->fnSetFeature )
                {
                    u32Result = g_pHindiLangsTbl[i]->fnSetFeature(u32FeatureTags, eFeature);
                }
                break;
            }
        }
    }

    return u32Result;
}

BOOLEAN _msAPI_MLE_FontHindiCharIsSign( HindiScript_e eScript, U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return FALSE;
    }

#ifdef __FEATURE_VECTOR_FONT__
    if ( msAPI_MLE_FONTBASE_IsVectorFontExist() )
    {
        LE_ClassDefinitionType_e eType = msAPI_MLE_Le_GetGlyphClass(u16Character);

        if ( eType == LE_CLASS_DEF_MARK )
        {
            bResult = TRUE;
        }
    }
#endif //__FEATURE_VECTOR_FONT__

    return bResult;
}


BOOLEAN _msAPI_MLE_FontHindiCharIsComposed( HindiScript_e eScript, U16 u16Character )
{
    BOOLEAN bResult = FALSE;

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return FALSE;
    }

#ifdef __FEATURE_VECTOR_FONT__
    if ( msAPI_MLE_FONTBASE_IsVectorFontExist() )
    {
        LE_ClassDefinitionType_e eType = msAPI_MLE_Le_GetGlyphClass(u16Character);

        if ( eType == LE_CLASS_DEF_MARK || eType == LE_CLASS_DEF_COMPONENT )
        {
            bResult = TRUE;
        }
    }
#endif //__FEATURE_VECTOR_FONT__

    return bResult;
}

BOOLEAN _msAPI_MLE_FontHindiVectorCharIsComposed( HindiScript_e eScript, U16 u16Character )
{
    U16 i;
    BOOLEAN bResult = FALSE;

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return FALSE;
    }

    for ( i = 0; i < HINDI_MAX_SCRIPT_NUM; i++ )
    {
        if ( g_pHindiLangsTbl[i] == NULL )
        {
            break;
        }

        if ( g_pHindiLangsTbl[i]->eScript == eScript )
        {
            if ( g_pHindiLangsTbl[i]->fnCharIsComposed )
            {
                bResult = g_pHindiLangsTbl[i]->fnCharIsComposed(u16Character);
            }
            break;
        }
    }

    if ( bResult )
    {
        if ( _msAPI_MLE_FontHindiGetCharType(eScript, u16Character) == HINDI_NUM || _msAPI_MLE_FontHindiGetCharSpecialType(eScript, u16Character) == HINDI_SP_SINGLE_INDVOW )
        {
            bResult = FALSE;
        }
    }

    return bResult;
}

BOOLEAN _msAPI_MLE_FontHindiFeatureWithRphf( HindiScript_e eScript, U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType )
{
    U16 i;
    BOOLEAN bResult = FALSE;

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return FALSE;
    }

    for ( i = 0; i < HINDI_MAX_SCRIPT_NUM; i++ )
    {
        if ( g_pHindiLangsTbl[i] == NULL )
        {
            break;
        }

        if ( g_pHindiLangsTbl[i]->eScript == eScript )
        {
            if ( g_pHindiLangsTbl[i]->fnStrWithRphf )
            {
                bResult = g_pHindiLangsTbl[i]->fnStrWithRphf(u32FeatureTags, peSpType);
            }
            break;
        }
    }

    return bResult;
}

BOOLEAN _msAPI_MLE_FontHindiFeatureWithBlwf( HindiScript_e eScript, U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType )
{
    U16 i;
    BOOLEAN bResult = FALSE;

    if ( eScript >= HINDI_MAX_SCRIPT_NUM )
    {
        return FALSE;
    }

    for ( i = 0; i < HINDI_MAX_SCRIPT_NUM; i++ )
    {
        if ( g_pHindiLangsTbl[i] == NULL )
        {
            break;
        }

        if ( g_pHindiLangsTbl[i]->eScript == eScript )
        {
            if ( g_pHindiLangsTbl[i]->fnStrWithBlwf )
            {
                bResult = g_pHindiLangsTbl[i]->fnStrWithBlwf(u32FeatureTags, peSpType);
            }
            break;
        }
    }

    return bResult;
}

#endif //__INDIC_FONT__
