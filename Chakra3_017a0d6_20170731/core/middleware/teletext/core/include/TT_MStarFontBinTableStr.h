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
//******************************************************************************
//<MStar Software>
#ifndef _TTX_MSTAR_FONTBIN_TABLE_STR_
#define _TTX_MSTAR_FONTBIN_TABLE_STR_

#define TTX_FONTBIN_INDEX_TABLE_ESCAPE_PLACE_HOLDER ((TT_U8)-1)

typedef enum
{
    TYPE_PRIMITIVE,
    TYPE_USING,
    TYPE_REFERENCE
}TTX_FontTableType;

typedef enum
{
    ARABIC_GO,
    ARABIC_G2,
    FARSI_G0,
    FARSI_G2,
    LATIN_G0,
    LATIN_G2,
    CYRILLIC_G0_OPT1,
    CYRILLIC_G0_OPT2,
    CYRILLIC_G0_OPT3,
    CYRILLIC_G2,
    GREEK_G0,
    GREEK_G2,
    HEBREW_G0,
    INTERNATIONAL1,
    INTERNATIONAL2,
    INTERNATIONAL3,
    SYMBOL,
    ARABIC_EXTENTION,
    NUM_OF_FONTS,
    FONT_DONTCARE = 0,
}TTX_FontID;

typedef struct
{
    TTX_FontID usingFontID;
    TT_U32 number;
    TT_U8 const* elem;
}stLocalRef;

typedef struct
{
    TT_U8 start;
    TT_U8 end;
    TTX_FontID refFont;
}stRefElem;

typedef struct
{
    TT_U32 number;
    stRefElem const* refElems;
}stRefs;

enum GuirkGlyphRuleType
{
    GUIRK_GLYPH_RLUE_FRONT = 1 << 0,
    GUIRK_GLYPH_RLUE_AFTER = 1 << 1   
};

typedef struct
{
    unsigned type : 8;
    unsigned judgeGlyphIndex : 8;
    unsigned fontTable : 8;    
    unsigned quirkGlyphIndex : 8;
}quirkGlyphRuleInfo;

typedef struct
{
    TT_U8 glyphID;
    struct
    {
        TT_U8 ruleNum;
        const quirkGlyphRuleInfo* ruleInfoTable;
    }rules;
}quirkGlyphInfo;


typedef struct
{
    TTX_FontTableType type;
    TT_U32 capacity;
    TT_U32 glyphNum;
    struct
    {
        stLocalRef using;
        stRefs  reference;
    }description;
    struct
    {
        TT_U8 recordNum;
        const quirkGlyphInfo* table;    
    }quirkGlyphTable;
}TTX_FontDesc;

#endif

