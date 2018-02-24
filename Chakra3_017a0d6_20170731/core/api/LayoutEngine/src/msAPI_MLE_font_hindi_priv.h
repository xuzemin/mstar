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


#ifndef __MLE_FONT_HINDI_PRIV_H__
#define __MLE_FONT_HINDI_PRIV_H__
     
#ifdef __INDIC_FONT__

#ifdef __FEATURE_VECTOR_FONT__
#include "msAPI_MLE_le.h"
//#define __INDIC_FONT_RULE_CACHE__
#endif //__FEATURE_VECTOR_FONT__

#define __DVNG_FONT__
#define __BENGALI_FONT__
#define __PUNJ_FONT__
#define __GUJR_FONT__
//#define __ORYA_FONT__
#define __TAMIL_FONT__
#define __TELUGU_FONT__
#define __KNDA_FONT__
#define __MLYM_FONT__
//#define __SINH_FONT__
#define __MYMR_FONT__
#define __KHMR_FONT__
#define __LAOO_FONT__

#define _HINDI_FILL_CLUSTER(_pCluster, _bufferSize, _clusterSize, _char, _consumed, _seq)\
{\
    if ( (_clusterSize) >= _bufferSize ) \
    {\
    break;\
    }\
    _pCluster[_clusterSize] = _char;\
    if ( _seq )\
    {\
    _seq[_clusterSize] = _clusterSize;\
    }\
    (_clusterSize)++;\
    (_consumed)++;\
}

#define _HINDI_VERLIFY_LEN(_pInputStr, _currentLen, _maxLen)\
{\
    if ( _currentLen >= _maxLen || (msAPI_MLE_FontHindiGetCharScript(_pInputStr[_currentLen]) >= HINDI_MAX_SCRIPT_NUM) )\
    {\
    break;\
    }\
}

enum
{
    HINDI_SCRIPT_DEVA,
    HINDI_SCRIPT_BENG,
    HINDI_SCRIPT_GUJR,
    HINDI_SCRIPT_ORYA,
    HINDI_SCRIPT_TAML,
    HINDI_SCRIPT_TELU,
    HINDI_SCRIPT_KNDA,
    HINDI_SCRIPT_MLYM,
    HINDI_SCRIPT_PUNJ,
    HINDI_SCRIPT_SINH,
    HINDI_SCRIPT_MYMR,
    HINDI_SCRIPT_KHMR,
    HINDI_SCRIPT_LAOO,
    HINDI_SCRIPT_MYMR_EXTA,
    HINDI_SCRIPT_MYMR_EXTB,
    HINDI_SCRIPT_KHMR_DIGIT1,
    HINDI_SCRIPT_KHMR_DIGIT2,
    HINDI_SCRIPT_KHMR_SYMBOLS,
    HINDI_MAX_SCRIPT_NUM
};
typedef U8 HindiScript_e;


#define _HindiLoclFeatureMask 0x80000000UL
#define _HindiNuktFeatureMask 0x40000000UL
#define _HindiAkhnFeatureMask 0x20000000UL
#define _HindiRphfFeatureMask 0x10000000UL
#define _HindiRkrfFeatureMask 0x08000000UL
#define _HindiBlwfFeatureMask 0x04000000UL
#define _HindiHalfFeatureMask 0x02000000UL
#define _HindiVatuFeatureMask 0x01000000UL
#define _HindiCjctFeatureMask 0x00800000UL
#define _HindiPresFeatureMask 0x00400000UL
#define _HindiAbvsFeatureMask 0x00200000UL
#define _HindiBlwsFeatureMask 0x00100000UL
#define _HindiPstsFeatureMask 0x00080000UL 
#define _HindiHalnFeatureMask 0x00040000UL
#define _HindiCaltFeatureMask 0x00020000UL
#define _HindiPrefFeatureMask 0x00010000UL
#define _HindiCligFeatureMask 0x00008000UL
#define _HindiAbvmFeatureMask 0x00004000UL
#define _HindiBlwmFeatureMask 0x00002000UL
#define _HindiPstfFeatureMask 0x00001000UL
#define _HindiInitFeatureMask 0x00000800UL
#define _HindiDistFeatureMask 0x00000400UL
#define _HindiMarkFeatureMask 0x00000200UL
#define _HindiMkmkFeatureMask 0x00000100UL
#define _HindiLigaFeatureMask 0x00000040UL
#define _HindiRligFeatureMask 0x00000080UL

#define _HindiPrivLeftJoinFeatureMask    0x00000001UL
#define _HindiPrivTwoPartJoinFeatureMask 0x00000002UL
#define _HindiPrivPreDottedFeatureMask   0x00000004UL
#define _HindiPrivPosDottedFeatureMask   0x00000008UL
#define _HindiPrivDontCachedFeatureMask  0x00000010UL
#define _HindiPrivThreePartFeatureMask      0x00000020UL

enum
{
    HINDI_FEATURE_LOCL = 0,
    HINDI_FEATURE_NUKT = 1,
    HINDI_FEATURE_AKHN = 2,
    HINDI_FEATURE_RPHF = 3,
    HINDI_FEATURE_BLWF = 4,
    HINDI_FEATURE_HALF = 5,
    HINDI_FEATURE_VATU = 6,
    HINDI_FEATURE_PRES = 7,
    HINDI_FEATURE_BLWS = 8,
    HINDI_FEATURE_ABVS = 9,
    HINDI_FEATURE_PSTS = 10,
    HINDI_FEATURE_HALN = 11,
    HINDI_FEATURE_BLWM = 12,
    HINDI_FEATURE_ABVM = 13,
    HINDI_FEATURE_RKRF = 14,
    HINDI_FEATURE_CJCT = 15,
    HINDI_FEATURE_CALT = 16,
    HINDI_FEATURE_PSTF = 17,
    HINDI_FEATURE_INIT = 18,
    HINDI_FEATURE_PREF = 19,
    HINDI_FEATURE_DIST = 20,
    HINDI_FEATURE_MARK = 21,
    HINDI_FEATURE_MKMK = 22,
    HINDI_FEATURE_CLIG = 23,
    HINDI_FEATURE_LIGA = 24,
    HINDI_FEATURE_RLIG = 25,
    HINDI_MAX_FEATURE_NUM,
    HINDI_PRIV_FEATURE_LEFT_JOIN,
    HINDI_PRIV_FEATURE_TWOPART_JOIN,
    HINDI_PRIV_FEATURE_PRE_DOTTED,
    HINDI_PRIV_FEATURE_POS_DOTTED,
    HINDI_PRIV_FEATURE_DONT_CACHED,
    HINDI_PRIV_FEATURE_THREEPART
};
typedef U8 HindiFeature_e;

typedef struct
{
    HindiFeature_e eTag;
    U32 u32Mask;
} HindiFeatureRecord_t;

typedef struct
{
    U16 *pu16OutCode;
    U16 u16ReturnLen;
    U32 *pau32Consumed;
    U32 u32FeatureTags;
} HindiCodeCachNode_t;

#define HINDI_OUT_SPLIT_ONE_TO_ONE          0x01
#define HINDI_OUT_SPLIT_ALL_IN_ONE          0x02
#define HINDI_OUT_SPLIT_ONE_TWO             0x03
#define HINDI_OUT_SPLIT_TWO_ONE             0x04
#define HINDI_OUT_SPLIT_ONE_THREE           0x05
#define HINDI_OUT_SPLIT_TWO_TWO             0x06
#define HINDI_OUT_SPLIT_THREE_ONE           0x07
#define HINDI_OUT_SPLIT_ONE_ONE_TWO         0x08
#define HINDI_OUT_SPLIT_TWO_ONE_ONE         0x09
#define HINDI_OUT_SPLIT_TWO_THREE           0x0A
#define HINDI_OUT_SPLIT_THREE_TWO           0x0B
#define HINDI_OUT_SPLIT_ONE_ONE_THREE       0x0C
#define HINDI_OUT_SPLIT_ONE_ONE_TWO_ONE     0x0D
#define HINDI_OUT_SPLIT_ONE_ONE_FOUR        0x0E
#define HINDI_OUT_SPLIT_ONE_ONE_ONE_THREE   0x0F

#define HINDI_CONVERT_MAX 20
     
enum
{ 
    HINDI_INVALID    = 0x00,
    HINDI_CON        = 0x01,
    HINDI_INDVOW     = 0x02,
    HINDI_DEPVOW     = 0x03,
    HINDI_SIGN       = 0x04,
    HINDI_NUM        = 0x05,
    HINDI_HALANT     = 0x06,
    HINDI_VPST       = 0X07,
    HINDI_VABV       = 0x08,
    HINDI_VBLW       = 0x09,
    HINDI_VPRE       = 0x0A,
    HINDI_A          = 0x0B,
    HINDI_DB         = 0x0C,
    HINDI_V          = 0x0D,
    HINDI_AS         = 0x0E,
    HINDI_MY         = 0x0F,
    HINDI_MR         = 0x10,
    HINDI_MW         = 0x11,
    HINDI_MH         = 0x12,
    HINDI_D0         = 0x13,
    HINDI_P          = 0x14,
    HINDI_PT         = 0x15,
    HINDI_WJ         = 0x16,
    HINDI_WS         = 0x17,
    HINDI_VS         = 0x18,
    HINDI_GB         = 0x19,
    HINDI_J          = 0x1A,
    HINDI_R          = 0x1B,
    HINDI_SABV	     = 0x1C,
    HINDI_SPST       = 0x1D,
    HINDI_COENG      = 0x1E,
    HINDI_REGSHIFT   = 0x1F,
    HINDI_SBLW       = 0x20
};
typedef U8 HindiCharacter_e;

     
enum
{ 
    HINDI_SP_INVALID                 = 0x00,
    HINDI_SP_LEFT_JOINER             = 0x10,
    HINDI_SP_RIGHT_JOINER            = 0x20,
    HINDI_SP_TWOPART_JOINER          = 0x30,
    HINDI_SP_CENTER_T                = 0x40,
    HINDI_SP_RIGHT_T                 = 0x50,
    HINDI_SP_DOUBLE_T                = 0x60,
    HINDI_SP_NO_T                    = 0x70,
    HINDI_SP_SINGLE_INDVOW           = 0x80,
    HINDI_SP_CENTER_T_UP_POS         = 0x90,
    HINDI_SP_CENTER_T_DOWN_POS       = 0xA0,
    HINDI_SP_LEFT_T_UP_POS           = 0xB0,
    HINDI_SP_LEFT_T_DOWN_POS         = 0xC0,
    HINDI_SP_RIGHT_T_DOWN_POS        = 0xD0,
    HINDI_SP_RIGHT_POS               = 0xE0,
};
typedef U8 HindiSpecialCharacter_e;

typedef enum
{
    HINDI_OTYPE_INVALID               = 0x00,
    HINDI_OTYPE_DEPVOW_LONG_DOWN_CHAR = 0x01,
    HINDI_OTYPE_CON_SMALL_CHAR        = 0x02
}HindiOtherCharacterType_e;
     
typedef enum
{ 
    HINDI_ORDER_CRA_SHALANT = 0,
    HINDI_ORDER_DVI,
    HINDI_ORDER_CON_DEPVOW,
    HINDI_ORDER_CON_SHALANT,
    HINDI_ORDER_ZWJ_SHALANT,
    HINDI_ORDER_TWOPART_DEPVOW
}HindiOrderType_e;

typedef U16 (*pfnGetCluster)( HindiScript_e eScript, const U16 *pu16Txt, U32 u32InLen, U16 *pu16Cluster, U16 u16BufferSize, U16 *pu16ConsumedCount, U16 *pu16SeqInCluster, BOOLEAN bIsDispStr, U32 *pu32FeatureTags );
typedef U16 (*pfnRefineCluster)( HindiScript_e eScript, const U16 *pu16InTxt, U32 u32InLen, U32 u32Offset, U16 *pu16Cluster, U16 *pu16CluserSize, U16 u16ClusterOffset, BOOLEAN bIsDispStr, U32 *pu32Features, const U16 *pu16OriginTxt, U32 u32OriginOffset);
typedef BOOLEAN (*pfnGetNextCodeXOffset)(U16 *pu16CurrentRefChar, U16 *pu16CurrentCharRefWidth, U16 u16NextChar, U16 u16NextCharWidth, S16 *ps16XOffset, U16 u16BaseWidth, U16 u16PreChar, BOOLEAN bFirstCharInCluster);
typedef BOOLEAN (*pfnCharIsRA)(U16 u16Character);
typedef BOOLEAN (*pfnCharIsHalant)(U16 u16Character);
typedef BOOLEAN (*pfnCharIsNukta)(U16 u16Character);
typedef BOOLEAN (*pfnCharIsBindu)(U16 u16Character);
typedef BOOLEAN (*pfnCharWithNukta)(U16 u16Character);
typedef BOOLEAN (*pfnCharIsNoHalfCon)(U16 u16Character);
typedef BOOLEAN (*pfnCharIsFollowingZWJ)(U16 u16Character);
typedef U16 (*pfnGetTwoWordLeftChar)(U16 u16Character);
typedef U16 (*pfnGetTwoWordRightChar)(U16 u16Character);
typedef HindiCharacter_e (*pfnGetCharType)(U16 u16Character);
typedef HindiSpecialCharacter_e (*pfnGetCharSpecialType)(U16 u16Character);
typedef HindiOtherCharacterType_e (*pfnGetCharOtherType)(U16 u16Character);
typedef BOOLEAN (*pfnCharIsBlwf)(U16 u16FirstChar, U16 u16SecondChar);
typedef BOOLEAN (*pfnCharIsPstf)(U16 u16FirstChar, U16 u16SecondChar);
typedef BOOLEAN (*pfnCharIsLigated)(U16 u16FirstChar, U16 u16SecondChar, BOOLEAN withZWJ);
typedef U32 (*pfnSetFeature)(U32 u32FeatureTags, HindiFeature_e eFeature);
typedef U16 (*pfnGetFeatureMap)(const HindiFeatureRecord_t **ppasFeatureMap);
typedef BOOLEAN (*pfnStrWithAkhand)(U16 *pu16Str, U32 u32StrLen, U16 u16Offset);
typedef BOOLEAN (*pfnCharIsSign)(U16 u16Character);
typedef BOOLEAN (*pfnCharIsComposed)(U16 u16Character);
typedef BOOLEAN (*pfnFeatureWithRphf)( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType );
typedef BOOLEAN (*pfnFeatureWithBlwf)( U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType );

typedef struct
{
    HindiScript_e eScript;
    U16 u16FirstChar;
    U16 u16LastChar;
    pfnGetCluster fnGetCluster;
    pfnRefineCluster fnRefineCluster;
    pfnGetNextCodeXOffset fnGetNextCodeXOffset;
    pfnCharIsRA fnCharIsRA;
    pfnCharIsHalant fnCharIsHalant;
    pfnCharIsNukta fnCharIsNukta;
    pfnCharIsBindu fnCharIsBindu;
    pfnCharWithNukta fnCharWithNukta;
    pfnCharIsNoHalfCon fnCharIsNoHalfCon;
    pfnCharIsFollowingZWJ fnCharIsFollowingZWJ;
    pfnGetTwoWordLeftChar fnGetTwoWordLeftChar;
    pfnGetTwoWordRightChar fnGetTwoWordRightChar;
    pfnGetCharType fnGetCharType;
    pfnGetCharSpecialType fnGetCharSpecialType;
    pfnGetCharOtherType fnGetCharOtherType;
    pfnCharIsBlwf fnCharIsBlwf;
    pfnCharIsPstf fnCharIsPstf;
    pfnCharIsLigated fnCharIsLigated;
    pfnStrWithAkhand fnStrWithAkhand;
    pfnSetFeature fnSetFeature;
    pfnGetFeatureMap fnGetFeatureMap;
    pfnCharIsSign fnCharIsSign;
    pfnCharIsComposed fnCharIsComposed;
    pfnFeatureWithRphf fnStrWithRphf;
    pfnFeatureWithBlwf fnStrWithBlwf;
} HindiTable_t;
     
U16 _msAPI_MLE_FontHindiRules( HindiScript_e eScript, LE_LanguageTag_e eLang, U16 *pu16Cluster, U16 u16ClusterSize, U16 u16ClustIndex, U16 *pu16Glyph, U16 *pu16OffsetInConcatenation, U16 *pu16OffsetInComposed, U16 *pu16ConcatenationComposedSize, U32 *pu32Features );
U16 _msAPI_MLE_FontHindiGetClusterStartOffset(HindiScript_e eScript, const U16 *pu16InTxt, U32 u32InLen, U32 u32Offset, U16 *pu16Cluster, U16 *pu16CluserSize, BOOLEAN bIsDispStr, U32 *pu32FeatureTags );
U16 _msAPI_MLE_FontHindiRefineCluster( HindiScript_e eScript, const U16 *pu16InTxt, U32 u32InLen, U32 u32Offset, U16 *pu16Cluster, U16 *pu16CluserSize, U16 u16ClusterOffset, BOOLEAN bIsDispStr, U32 *pu32Features, const U16 *pu16OriginTxt, U32 u32OriginOffset);
U16 msAPI_MLE_FontHindiGetNextCodes( HindiScript_e eScript, LE_LanguageTag_e eLang, const U16 *pu16InTxt, U32 u32InLen, U32 u32Offset, U32 u32SubLen, U16 *pu16OutCode, U32 u32OutLen, U32 *pu32Consumed, BOOLEAN bIsDispStr, U32 *pu32Features, const U16 *pu16OriginTxt, U32 u32OriginOffset);
BOOLEAN _msAPI_MLE_FontHindiGetNextCodeXOffset( HindiScript_e eScript, U16 *pu16CurrentRefChar, U16 *pu16CurrentCharRefWidth, U16 u16NextChar, U16 u16NextCharWidth, S16 *ps16XOffset, U16 u16BaseWidth, U16 u16PreChar, BOOLEAN bFirstCharInCluster);
BOOLEAN _msAPI_MLE_FontHindiGetCodeDrawWidth( HindiScript_e eScript, U32 nLen, U16 u16Character, U16 u16CharWidth, U16 u16NextChar, U16 u16BaseWidth, U16 *pu16Width );
BOOLEAN _msAPI_MLE_FontHindiReorderStr( HindiScript_e eScript, const U16 *pu16Str, U16 u16StrLen, U16 u16StrIndex, const U16 *pu16Seq, U16 **ppu16OrderSeg, U16 *pu16InOrderOffset, BOOLEAN bIsDispStr );
BOOLEAN _msAPI_MLE_FontHindiNextComposedChars( HindiScript_e eScript, LE_LanguageTag_e eLang, const U16 *pString, U32 nStrLen, U32 nOffset, U16 *pwComposedStr, U32 *pComposedLen, U32 *paConsumed, BOOLEAN bDispStr, U16 u16OutBufferSize );
BOOLEAN _msAPI_MLE_FontHindiPreComposedChars( HindiScript_e eScript, LE_LanguageTag_e eLang, const U16 *pString, U32 nStrLen, U32 nOffset, U16 *pwComposedStr, U32 *pComposedLen, U32 *paConsumed, BOOLEAN bDispStr, U16 u16OutBufferSize );
BOOLEAN _msAPI_MLE_FontHindiStrWithUpRA( HindiScript_e eScript, U16 *pu16Str, U32 nStrLen );
HindiScript_e msAPI_MLE_FontHindiGetCharScript( U16 u16Character );
BOOLEAN _msAPI_MLE_FontHindiFeatureWithLJoin( HindiScript_e eScript, U32 u32FeatureTags, BOOLEAN *pIsTwoPart );
BOOLEAN _msAPI_MLE_FontHindiFeatureWithDotted( HindiScript_e eScript, U32 u32FeatureTags, BOOLEAN *pIsPreDotted );
BOOLEAN _msAPI_MLE_FontHindiFeatureWithNoCache( HindiScript_e eScript, U32 u32FeatureTags, BOOLEAN *pIsNoCached );
BOOLEAN _msAPI_MLE_FontHindiFeatureWithThreePart( HindiScript_e eScript, U32 u32FeatureTags, BOOLEAN *pIsThreePart );

#ifdef __FEATURE_VECTOR_FONT__
BOOLEAN msAPI_MLE_FontHindiVectorGetNextOffset( HindiScript_e eScript, LE_LanguageTag_e eLang, U16 *pu16InGlyphs, U16 u16GlyphLen, U16 u16NextOffset, U16 *pu16BaseOffset, S16 *ps16XOffset, S16 *ps16YOffset,  S16 *ps16NextXOffset, S16 *ps16NextYOffset, U32 u32FeatureTags );
#endif //__FEATURE_VECTOR_FONT__

/*=======================================================*/
/*================Common porting functions======================*/
/*=======================================================*/
BOOLEAN _msAPI_MLE_FontHindiCharIsSign( HindiScript_e eScript, U16 u16Character );
BOOLEAN _msAPI_MLE_FontHindiCharIsComposed( HindiScript_e eScript, U16 u16Character );
BOOLEAN _msAPI_MLE_FontHindiVectorCharIsComposed( HindiScript_e eScript, U16 u16Character );
BOOLEAN _msAPI_MLE_FontHindiFeatureWithRphf( HindiScript_e eScript, U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType );
BOOLEAN _msAPI_MLE_FontHindiFeatureWithBlwf( HindiScript_e eScript, U32 u32FeatureTags, HindiSpecialCharacter_e *peSpType );

#endif //__INDIC_FONT__
#endif /* __MLE_FONT_HINDI_PRIV_H__ */
