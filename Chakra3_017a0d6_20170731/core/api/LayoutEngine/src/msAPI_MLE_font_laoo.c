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

#ifdef __LAOO_FONT__
#include "msAPI_MLE_font_laoo.h"

/*------------------------------------------------------------------------------------------
*
*                                                                                     MACRO DEFINE
*
-------------------------------------------------------------------------------------------*/

const U8 g_LaooCharTypeArray[] =
{
    /* Consonants */
    HINDI_CON,                                           //LAOO_C_KO                   = 0x0E81,
    HINDI_CON,                                           //LAOO_C_KHO_SUNG      = 0x0E82,
    HINDI_INVALID,                                     //LAOO_C_RESERVED1     = 0x0E83,
    HINDI_CON,                                           //LAOO_C_KHO_TAM        = 0x0E84,
    HINDI_INVALID,                                     //LAOO_C_RESERVED2     = 0x0E85,
    HINDI_INVALID,                                     //LAOO_C_RESERVED3     = 0x0E86,
    HINDI_CON,                                           //LAOO_C_NGO                = 0x0E87,
    HINDI_CON,                                           //LAOO_C_CO                   = 0x0E88,
    HINDI_INVALID,                                     //LAOO_C_RESERVED4     = 0x0E89,
    HINDI_CON,                                           //LAOO_C_SO_TAM          = 0x0E8A,
    HINDI_INVALID,                                     //LAOO_C_RESERVED5     = 0x0E8B,
    HINDI_INVALID,                                     //LAOO_C_RESERVED6     = 0x0E8C,
    HINDI_CON,                                           //LAOO_C_NYO                 = 0x0E8D,
    HINDI_INVALID,                                     //LAOO_C_RESERVED7     = 0x0E8E,
    HINDI_INVALID,                                     //LAOO_C_RESERVED8     = 0x0E8F,
    HINDI_INVALID,                                     //LAOO_C_RESERVED9     = 0x0E90,
    HINDI_INVALID,                                     //LAOO_C_RESERVED10   = 0x0E91,
    HINDI_INVALID,                                     //LAOO_C_RESERVED11   = 0x0E92,
    HINDI_INVALID,                                     //LAOO_C_RESERVED12   = 0x0E93,
    HINDI_CON,                                           //LAOO_C_DO                   = 0x0E94,
    HINDI_CON,                                           //LAOO_C_TO                   = 0x0E95,
    HINDI_CON,                                           //LAOO_C_THO_SUNG      = 0x0E96,
    HINDI_CON,                                           //LAOO_C_THO_TAM        = 0x0E97,
    HINDI_INVALID,                                     //LAOO_C_RESERVED13   = 0x0E98,
    HINDI_CON,                                           //LAOO_C_NO                   = 0x0E99,
    HINDI_CON,                                           //LAOO_C_BO                   = 0x0E9A,
    HINDI_CON,                                           //LAOO_C_PO                   = 0x0E9B,
    HINDI_CON,                                           //LAOO_C_PHO_SUNG      = 0x0E9C,
    HINDI_CON,                                           //LAOO_C_FO_TAM          = 0x0E9D,
    HINDI_CON,                                           //LAOO_C_PHO_TAM        = 0x0E9E,
    HINDI_CON,                                           //LAOO_C_FO_SUNG        = 0x0E9F,
    HINDI_INVALID,                                     //LAOO_C_RESERVED14   = 0x0EA0,
    HINDI_CON,                                           //LAOO_C_MO                   = 0x0EA1,
    HINDI_CON,                                           //LAOO_C_YO                   = 0x0EA2,
    HINDI_CON,                                           //LAOO_C_LO_LING          = 0x0EA3,
    HINDI_INVALID,                                     //LAOO_C_RESERVED15    = 0x0EA4,
    HINDI_CON,                                           //LAOO_C_LO_LOOT          = 0x0EA5,
    HINDI_INVALID,                                     //LAOO_C_RESERVED16    = 0x0EA6,
    HINDI_CON,                                           //LAOO_C_WO                   = 0x0EA7,
    HINDI_INVALID,                                     //LAOO_C_RESERVED17    = 0x0EA8,
    HINDI_INVALID,                                     //LAOO_C_RESERVED18    = 0x0EA9,
    HINDI_CON,                                           //LAOO_C_SO_SUNG         = 0x0EAA,
    HINDI_CON,                                           //LAOO_C_HO_SUNG         = 0x0EAB,
    HINDI_INVALID,                                     //LAOO_C_RESERVED19    = 0x0EAC,
    HINDI_CON,                                           //LAOO_C_O                      = 0x0EAD,
    HINDI_CON,                                           //LAOO_C_HO_TAM           = 0x0EAE,

    /* Sign */
    HINDI_SIGN,                                           //LAOO_S_ELLIPSIS          = 0x0EAF,

    /* Vowel */
    HINDI_INDVOW,                                      //LAOO_V_A                      = 0x0EB0,
    HINDI_VABV,                                      //LAOO_V_MAI_KAN          = 0x0EB1,
    HINDI_INDVOW,                                      //LAOO_V_AA                    = 0x0EB2,
    HINDI_DEPVOW,                                      //LAOO_V_AM                    = 0x0EB3,//need to refined
    HINDI_VABV,                                      //LAOO_V_I                       = 0x0EB4,
    HINDI_VABV,                                      //LAOO_V_II                      = 0x0EB5,
    HINDI_VABV,                                      //LAOO_V_Y                       = 0x0EB6,
    HINDI_VABV,                                      //LAOO_V_YY                     = 0x0EB7,
    HINDI_VBLW,                                      //LAOO_V_U                       = 0x0EB8,
    HINDI_VBLW,                                      //LAOO_V_UU                     = 0x0EB9,
    HINDI_INVALID,                                       //LAOO_C_RESERVED20     = 0x0EBA,
    HINDI_VABV,                                      //LAOO_V_AMI_KON          = 0x0EBB,

    /* Sign */
    HINDI_SBLW,                                           //LAOO_S_LO                     = 0x0EBC,
    HINDI_SIGN,                                           //LAOO_S_NYO                  = 0x0EBD,

    HINDI_INVALID,                                     //LAOO_C_RESERVED21    = 0x0EBE,
    HINDI_INVALID,                                     //LAOO_C_RESERVED22    = 0x0EBF,

    /* Vowel */
    HINDI_INDVOW,                                      //LAOO_V_E                       = 0x0EC0,
    HINDI_INDVOW,                                      //LAOO_V_EI                      = 0x0EC1,
    HINDI_INDVOW,                                      //LAOO_V_O                       = 0x0EC2,
    HINDI_INDVOW,                                      //LAOO_V_AY                     = 0x0EC3,
    HINDI_INDVOW,                                      //LAOO_V_AI                      = 0x0EC4,

    HINDI_INVALID,                                     //LAOO_C_RESERVED23    = 0x0EC5,

    /* Repetition Mark */
    HINDI_INDVOW,                                           //LAOO_M_KO_LA                = 0x0EC6,

    HINDI_INVALID,                                     //LAOO_C_RESERVED24    = 0x0EC7,

    /* Tone Mark */
    HINDI_SABV,                                           //LAOO_M_MAI_EK              = 0x0EC8,
    HINDI_SABV,                                           //LAOO_M_MAI_THO            = 0x0EC9,
    HINDI_SABV,                                           //LAOO_M_MAI_TI               = 0x0ECA,
    HINDI_SABV,                                           //LAOO_M_MAI_CATAWA     = 0x0ECB,

    /* Sign */
    HINDI_SABV,                                           //LAOO_S_CANCELLATION_MARK    = 0x0ECC,
    HINDI_SABV,                                           //LAOO_S_NIGGAHITA                    = 0x0ECD,

    HINDI_INVALID,                                     //LAOO_C_RESERVED25    = 0x0ECE,
    HINDI_INVALID,                                     //LAOO_C_RESERVED26    = 0x0ECF,

    /* Digits */
    HINDI_NUM,                                            //LAOO_D_ZERO                   = 0x0ED0,
    HINDI_NUM,                                            //LAOO_D_ONE                     = 0x0ED1,
    HINDI_NUM,                                            //LAOO_D_TWO                    = 0x0ED2,
    HINDI_NUM,                                            //LAOO_D_THREE                 = 0x0ED3,
    HINDI_NUM,                                            //LAOO_D_FOUR                   = 0x0ED4,
    HINDI_NUM,                                            //LAOO_D_FIVE                    = 0x0ED5,
    HINDI_NUM,                                            //LAOO_D_SIX                      = 0x0ED6,
    HINDI_NUM,                                            //LAOO_D_SEVEN                 = 0x0ED7,
    HINDI_NUM,                                            //LAOO_D_EIGHT                  = 0x0ED8,
    HINDI_NUM,                                            //LAOO_D_NINE                    = 0x0ED9,

    HINDI_INVALID,                                     //LAOO_C_RESERVED27    = 0x0EDA,
    HINDI_INVALID,                                     //LAOO_C_RESERVED28    = 0x0EDB,

    /* Digraphs */
    HINDI_CON,                                           //LAOO_C_HO_NO                   = 0x0EDC,
    HINDI_CON,                                           //LAOO_C_HO_MO                   = 0x0EDD,

    /* Consonants for Khmu */
    HINDI_CON,                                           //LAOO_C_KHMU_GO              = 0x0EDE,
    HINDI_CON,                                           //LAOO_C_KHMU_NYO            = 0x0EDF,

    HINDI_INVALID
};


const HindiFeatureRecord_t _g_sLaooFeatureMap[] =
{
    /*HINDI_FEATURE_LOCL*/  { HINDI_FEATURE_LIGA, _HindiLigaFeatureMask},
    /*HINDI_FEATURE_RPHF*/  { HINDI_FEATURE_RLIG, _HindiRligFeatureMask},
};
const U16 _g_u16LaooFeatureCount = (sizeof(_g_sLaooFeatureMap)/sizeof(HindiFeatureRecord_t));

static U16 _msAPI_MLE_FontLaooGetCluster( HindiScript_e eScript, const U16 *pu16Txt, U32 u32InLen, U16 *pu16Cluster, U16 u16BufferSize, U16 *pu16ConsumedCount, U16 *pu16SeqInCluster, BOOLEAN bIsDispStr, U32 *pu32FeatureTags );
static HindiCharacter_e _msAPI_MLE_FontLaooGetCharType( U16 u16Character );
static U32 _msAPI_MLE_FontLaooSetFeature( U32 u32FeatureTags, HindiFeature_e eFeature );
static U16 _msAPI_MLE_FontLaooGetFeatureMap( const HindiFeatureRecord_t **ppasFeatureMap );
static BOOLEAN _msAPI_MLE_FontLaooCharIsBlwf( U16 u16FirstChar, U16 u16SecondChar );
static U16 _msAPI_MLE_FontLaooRefineCluster( HindiScript_e eScript, const U16 *pu16InTxt, U32 u32InLen, U32 u32Offset, U16 *pu16Cluster, U16 *pu16CluserSize, U16 u16ClusterOffset, BOOLEAN bIsDispStr, U32 *pu32Features, const U16 *pu16OriginTxt, U32 u32OriginOffset);

static S16 s16BaseGlyphIndex = -1;
static S16 s16MRIndex = -1;
static S16 s16PreBaseVowelIndex = -1;
static U16 u16VPreCount = 0;
static S16 s16AnusvaraIndex = -1;
static U16 u16ACount = 0;
static S16 s16VBlwIndex = -1;
static U16 u16VBlwCount = 0;
static BOOLEAN bKinziFound = FALSE;

__SLDPM_FREE__ const HindiTable_t g_laooTable =
{
    HINDI_SCRIPT_LAOO,
    LAOO_C_KO,
    LAOO_C_KHMU_NYO,
    &_msAPI_MLE_FontLaooGetCluster,
    &_msAPI_MLE_FontLaooRefineCluster,
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
    &_msAPI_MLE_FontLaooGetCharType,
    NULL,//&_msAPI_MLE_FontMyanmarGetCharSpecialType,
    NULL,//&_FontBengGetCharOtherType,
    &_msAPI_MLE_FontLaooCharIsBlwf,
    NULL,//&_msAPI_MLE_FontMyanmarCharIsPstf,
    NULL,//&_FontBengCharIsLigated,
    NULL,//&_msAPI_MLE_FontMyanmarStrWithAkhand,
    &_msAPI_MLE_FontLaooSetFeature,
    &_msAPI_MLE_FontLaooGetFeatureMap,
    NULL,//&_FontBengCharIsSign,
    NULL,//&_FontBengCharIsComposed,
    NULL,//&_msAPI_MLE_FontMyanmarFeatureWithRphf,
    NULL,//&_msAPI_MLE_FontMyanmarFeatureWithBlwf
};

static U16 _msAPI_MLE_FontLaooGetCluster( HindiScript_e eScript, const U16 *pu16Txt, U32 u32InLen, U16 *pu16Cluster, U16 u16BufferSize, U16 *pu16ConsumedCount, U16 *pu16SeqInCluster, BOOLEAN bIsDispStr, U32 *pu32FeatureTags )
{
    U16 u16Character = 0;
    LaooParserState_e eClusterState = CLUSTER_LAOO_INIT;
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

    while( (u16Index < u32InLen) && ( bExit == FALSE ) && ( bErrExit == FALSE ) && ( *pu16ConsumedCount <= u32InLen ) )
    {
        u16Character = pu16Txt[u16Index];
        eType = _msAPI_MLE_FontLaooGetCharType(u16Character);
        switch(eType)
        {
        case HINDI_CON:
        case HINDI_INDVOW:
        case HINDI_NUM:
        case HINDI_SIGN:
            if ( eClusterState == CLUSTER_LAOO_INIT)
            {
                eClusterState = CLUSTER_LAOO_BASE;

                s16BaseGlyphIndex = u16Index;

                if ( (U16)(u16Index+1) < u32InLen )
                {
                    HindiCharacter_e eTypeNext = HINDI_INVALID;

                    eTypeNext = _msAPI_MLE_FontLaooGetCharType(pu16Txt[u16Index+1]);
                    if ( ( eTypeNext != HINDI_VABV) && ( eTypeNext != HINDI_SBLW) && ( eTypeNext != HINDI_SABV) && ( eTypeNext != HINDI_VBLW) && (eTypeNext != HINDI_DEPVOW))
                    {
                        bExit = TRUE;
                    }
                }
            }

            _HINDI_FILL_CLUSTER( pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster );
            u16Index++;
            _HINDI_VERLIFY_LEN( pu16Txt, *pu16ConsumedCount, u32InLen );
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        case HINDI_VABV:
        case HINDI_VBLW:
        case HINDI_SABV:
        case HINDI_SBLW:
        case HINDI_DEPVOW:
            if ((U16)(u16Index + 1) < u32InLen)
            {
                HindiCharacter_e eTypeNext = HINDI_INVALID;

                eTypeNext = _msAPI_MLE_FontLaooGetCharType(pu16Txt[u16Index + 1]);
                if (eTypeNext == HINDI_CON)
                {
                    bExit = TRUE;
                }
            }

            _HINDI_FILL_CLUSTER(pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster);
            u16Index++;
            _HINDI_VERLIFY_LEN(pu16Txt, *pu16ConsumedCount, u32InLen);
            u16Character = pu16Txt[*pu16ConsumedCount];
            break;

        //special case:customer need get the character when this character not define in the ttf, but still need to receive it.
        //here will not to get into cluster with others.
        case HINDI_INVALID:
            if (eClusterState != CLUSTER_LAOO_INIT)
            {
                bErrExit = TRUE;
            }

            bExit = TRUE;

            _HINDI_FILL_CLUSTER(pu16Cluster, u16BufferSize, u16ClusterSize, pu16Txt[*pu16ConsumedCount], *pu16ConsumedCount, pu16SeqInCluster);
            _HINDI_VERLIFY_LEN(pu16Txt, *pu16ConsumedCount, u32InLen);
            break;
        }

    }

    if ( *pu16ConsumedCount > 0 )
    {
        *pu32FeatureTags = _msAPI_MLE_FontLaooSetFeature(*pu32FeatureTags, HINDI_FEATURE_LIGA);
        *pu32FeatureTags = _msAPI_MLE_FontLaooSetFeature(*pu32FeatureTags, HINDI_FEATURE_RLIG);
    }

    return *pu16ConsumedCount;
}

static HindiCharacter_e _msAPI_MLE_FontLaooGetCharType( U16 u16Character )
{
    HindiCharacter_e eType = HINDI_INVALID;

    if ( IS_LAOO_ALL_RANGE(u16Character) )
    {
        eType = (g_LaooCharTypeArray[u16Character - LAOO_MASK]);
    }

    return eType;
}

static U32 _msAPI_MLE_FontLaooSetFeature( U32 u32FeatureTags, HindiFeature_e eFeature )
{
    U16 i;
    for ( i = 0; i < _g_u16LaooFeatureCount; i++ )
    {
        if ( _g_sLaooFeatureMap[i].eTag == eFeature )
        {
            u32FeatureTags = u32FeatureTags | _g_sLaooFeatureMap[i].u32Mask;
            break;
        }
    }
    return u32FeatureTags;
}

static U16 _msAPI_MLE_FontLaooGetFeatureMap( const HindiFeatureRecord_t **ppasFeatureMap )
{
    *ppasFeatureMap = _g_sLaooFeatureMap;
    return (U16)_g_u16LaooFeatureCount;
}

static BOOLEAN _msAPI_MLE_FontLaooCharIsBlwf( U16 u16FirstChar, U16 u16SecondChar )
{
    BOOLEAN bResult = FALSE;
    u16FirstChar = u16FirstChar;
    u16SecondChar= u16SecondChar;

    return bResult;
}

static U16 _msAPI_MLE_FontLaooRefineCluster( HindiScript_e eScript, const U16 *pu16InTxt, U32 u32InLen, U32 u32Offset, U16 *pu16Cluster, U16 *pu16CluserSize, U16 u16ClusterOffset, BOOLEAN bIsDispStr, U32 *pu32Features, const U16 *pu16OriginTxt, U32 u32OriginOffset)
{
//Below is XP spec, in Win7, it seems that Microsoft modified reorder rule of Bengali, so we don't need to reorder here



    eScript = eScript;
    pu16InTxt = pu16InTxt;
    u32InLen = u32InLen;
    u32Offset = u32Offset;
    bIsDispStr = bIsDispStr;
    pu16Cluster= pu16Cluster;
    pu16CluserSize = pu16CluserSize;
    pu32Features = pu32Features;
    pu16OriginTxt = pu16OriginTxt;
    u32OriginOffset = u32OriginOffset;

    if ( s16BaseGlyphIndex < 0 )
        return u16ClusterOffset;

    //TO-DO//

    //TO-DO//

    return u16ClusterOffset;
}

#endif //__LAOO_FONT__
#endif //__INDIC_FONT__
