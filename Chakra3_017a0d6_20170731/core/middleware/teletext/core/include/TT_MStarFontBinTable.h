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
#include "TT_Global.h"
#include "TT_MStarFontBinTableStr.h"

PRIVATE
const quirkGlyphRuleInfo TX_ArabicFarsi_G0_Glyph51_RuleInfos[] =
{
    {
        .type = GUIRK_GLYPH_RLUE_FRONT,
        .judgeGlyphIndex = 6,
        .fontTable = ARABIC_EXTENTION,
        .quirkGlyphIndex = 0
    }
};

PRIVATE
const quirkGlyphRuleInfo TX_ArabicFarsi_G0_Glyph52_RuleInfos[] =
{
    {
        .type = GUIRK_GLYPH_RLUE_FRONT,
        .judgeGlyphIndex = 6,
        .fontTable = ARABIC_EXTENTION,
        .quirkGlyphIndex = 1
    }

};

PRIVATE
const quirkGlyphRuleInfo TX_ArabicFarsi_G0_Glyph53_RuleInfos[] =
{
    {
        .type = GUIRK_GLYPH_RLUE_FRONT,
        .judgeGlyphIndex = 6,
        .fontTable = ARABIC_EXTENTION,
        .quirkGlyphIndex = 2
    }

};

PRIVATE
const quirkGlyphRuleInfo TX_ArabicFarsi_G0_Glyph54_RuleInfos[] =
{
    {
        .type = GUIRK_GLYPH_RLUE_FRONT,
        .judgeGlyphIndex = 6,
        .fontTable = ARABIC_EXTENTION,
        .quirkGlyphIndex = 3
    }

};

PRIVATE
const quirkGlyphInfo TTX_ArabicFarsi_G0_QuirkGlyphs_InfoTable[] =
{
    {
        .glyphID = 51,
        .rules =
        {
            .ruleNum = sizeof(TX_ArabicFarsi_G0_Glyph51_RuleInfos)/sizeof(TX_ArabicFarsi_G0_Glyph51_RuleInfos[0]),
            .ruleInfoTable = TX_ArabicFarsi_G0_Glyph51_RuleInfos
        }
    },
    {
        .glyphID = 52,
        .rules =
        {
            .ruleNum = sizeof(TX_ArabicFarsi_G0_Glyph52_RuleInfos)/sizeof(TX_ArabicFarsi_G0_Glyph52_RuleInfos[0]),
            .ruleInfoTable = TX_ArabicFarsi_G0_Glyph52_RuleInfos
        }
    },
    {
        .glyphID = 53,
        .rules =
        {
            .ruleNum = sizeof(TX_ArabicFarsi_G0_Glyph53_RuleInfos)/sizeof(TX_ArabicFarsi_G0_Glyph53_RuleInfos[0]),
            .ruleInfoTable = TX_ArabicFarsi_G0_Glyph53_RuleInfos
        }
    },
    {
        .glyphID = 54,
        .rules =
        {
            .ruleNum = sizeof(TX_ArabicFarsi_G0_Glyph54_RuleInfos)/sizeof(TX_ArabicFarsi_G0_Glyph54_RuleInfos[0]),
            .ruleInfoTable = TX_ArabicFarsi_G0_Glyph54_RuleInfos
        }
    }
};

PRIVATE
const TTX_FontDesc TTX_Font_Arabic_G0 =
{
    .type = TYPE_PRIMITIVE,
    .capacity = 96,
    .glyphNum = 96,
    .description=
    {
        .using ={FONT_DONTCARE,0,0},
        .reference = {0,0}    },
    .quirkGlyphTable =
    {
        .recordNum = sizeof(TTX_ArabicFarsi_G0_QuirkGlyphs_InfoTable)/sizeof(TTX_ArabicFarsi_G0_QuirkGlyphs_InfoTable[0]),
        .table = TTX_ArabicFarsi_G0_QuirkGlyphs_InfoTable
    }
};
///////////////////////////////////////////////////////////////////////
PRIVATE
const TTX_FontDesc TTX_Font_Arabic_G2 =
{
    .type = TYPE_PRIMITIVE,
    .capacity = 96,
    .glyphNum = 96,
    .description=
    {
        .using = {FONT_DONTCARE,0,0},
        .reference = {0,0}
    },
    .quirkGlyphTable =
    {
        .recordNum = 0,
        .table = 0
    }
};

///////////////////////////////////////////////////////////////////////
PRIVATE
const TT_U8 FarsiG0_LocalRef[] =
{
    12, 27, 33, 38, 39, 63, 68
};

PRIVATE
const TTX_FontDesc TTX_Font_Farsi_G0 =
{
    .type = TYPE_USING,
    .capacity = 96,
    .glyphNum = sizeof(FarsiG0_LocalRef)/sizeof(FarsiG0_LocalRef[0]),
    .description=
    {
        .using =
        {
            ARABIC_GO,
            sizeof(FarsiG0_LocalRef)/sizeof(FarsiG0_LocalRef[0]),
            FarsiG0_LocalRef
        },
        .reference =
        {
            0, 0
        }
    },
    .quirkGlyphTable =
    {
        .recordNum = sizeof(TTX_ArabicFarsi_G0_QuirkGlyphs_InfoTable)/sizeof(TTX_ArabicFarsi_G0_QuirkGlyphs_InfoTable[0]),
        .table = TTX_ArabicFarsi_G0_QuirkGlyphs_InfoTable
    }
};
///////////////////////////////////////////////////////////////////////
PRIVATE
const TT_U8 FarsiG2_localRef[]=
{
    1,
    2,
    3,
    4,
    6,
    7,
    9,
    16,
    17,
    18,
    19,
    20,
    21,
    22,
    25,
    27,
    29,
    63
};

PRIVATE
const TTX_FontDesc TTX_Font_Farsi_G2 =
{
    .type = TYPE_USING,
    .capacity = 96,
    .glyphNum = sizeof(FarsiG2_localRef)/sizeof(FarsiG2_localRef[0]),
    .description=
    {
        .using =
        {
            ARABIC_G2,
            sizeof(FarsiG2_localRef)/sizeof(FarsiG2_localRef[0]),
            FarsiG2_localRef
        },
        .reference = {0,0}
    },
    .quirkGlyphTable =
    {
        .recordNum = 0,
        .table = 0
    }
};
///////////////////////////////////////////////////////////////////////
PRIVATE
const TT_U8 LatinG0_localRef[]=
{
    3,
    4,
    6,
    7,
    8,
    9,
    12,
    14,
    27,
    28,
    30,
    31,
    32,
    59,
    60,
    61,
    62,
    63,
    64,
    91,
    92,
    93,
    94,
    95
};

PRIVATE
const stRefElem LatinG0_Ref[] =
{
    {0, 2, ARABIC_GO},
    {5, 5, ARABIC_GO},
    {10, 11, ARABIC_GO},
    {13, 26, ARABIC_GO},
    {29, 29, ARABIC_GO},
    {33, 58, ARABIC_G2},
    {65, 90, ARABIC_G2}
};

PRIVATE
const TTX_FontDesc TTX_Font_Latin_G0 =
{
    .type = TYPE_REFERENCE,
    .capacity = 96,
    .glyphNum = sizeof(LatinG0_localRef)/sizeof(LatinG0_localRef[0]),
    .description=
    {
        .using =
        {
            FONT_DONTCARE,
            sizeof(LatinG0_localRef)/sizeof(LatinG0_localRef[0]),
            LatinG0_localRef,
        },
        .reference =
        {
            sizeof(LatinG0_Ref)/sizeof(LatinG0_Ref[0]),
            LatinG0_Ref
        }
    },
    .quirkGlyphTable =
    {
        .recordNum = 0,
        .table = 0
    }
};

///////////////////////////////////////////////////////////////////////
PRIVATE
const TTX_FontDesc TTX_Font_Latin_G2 =
{
    .type = TYPE_PRIMITIVE,
    .capacity = 96,
    .glyphNum = 96,
    .description=
    {
        .using ={FONT_DONTCARE,0,0},
        .reference = {0,0}    },
    .quirkGlyphTable =
    {
        .recordNum = 0,
        .table = 0
    }
};

///////////////////////////////////////////////////////////////////////

PRIVATE
const TT_U8 CyrillicOpt1G0_localRef[]=
{
    32,
    34,
    35,
    36,
    38,
    39,
    40,
    41,
    42,
    43,
    44,
    46,
    48,
    49,
    50,
    51,
    52,
    53,
    54,
    55,
    56,
    57,
    58,
    59,
    60,
    61,
    62,
    63,
    64,
    66,
    67,
    68,
    69,
    70,
    71,
    72,
    73,
    74,
    75,
    76,
    77,
    78,
    79,
    80,
    81,
    82,
    83,
    84,
    85,
    86,
    87,
    88,
    89,
    90,
    91,
    92,
    93,
    94,
    95
};

PRIVATE
const stRefElem CyrillicOpt1G0_Ref[] =
{
    {0, 3, LATIN_G0},
    {4, 4, LATIN_G2},
    {5, 31, LATIN_G0},
    {33, 33, LATIN_G0},
    {37, 37, LATIN_G0},
    {45, 45, LATIN_G0},
    {47, 47, LATIN_G0},
    {65, 65, LATIN_G0}
};

PRIVATE
const TTX_FontDesc TTX_Font_CyrillicOpt1G0 =
{
    .type = TYPE_REFERENCE,
    .capacity = 96,
    .glyphNum = sizeof(CyrillicOpt1G0_localRef)/sizeof(CyrillicOpt1G0_localRef[0]),
    .description=
    {
        .using =
        {
            FONT_DONTCARE,
            sizeof(CyrillicOpt1G0_localRef)/sizeof(CyrillicOpt1G0_localRef[0]),
            CyrillicOpt1G0_localRef
        },
        .reference =
        {
            sizeof(CyrillicOpt1G0_Ref)/sizeof(CyrillicOpt1G0_Ref[0]),
            CyrillicOpt1G0_Ref
        }    },
    .quirkGlyphTable =
    {
        .recordNum = 0,
        .table = 0
    }
};

///////////////////////////////////////////////////////////////////////
PRIVATE
const TT_U8 CyrillicOpt2G0_localRef[]=
{
    6,
    32,
    42,
    48,
    49,
    50,
    51,
    52,
    53,
    54,
    55,
    56,
    57,
    58,
    59,
    60,
    61,
    62,
    63,
    64,
    74,
    80,
    81,
    86,
    87,
    88,
    89,
    90,
    91,
    92,
    93,
    94
};

PRIVATE
const stRefElem CyrillicOpt2G0_Ref[] =
{
    {0, 3, LATIN_G0},
    {4, 4, LATIN_G2},
    {5, 5, LATIN_G0},
    {7, 31, CYRILLIC_G0_OPT1},
    {33, 41, CYRILLIC_G0_OPT1},
    {43, 47, CYRILLIC_G0_OPT1},
    {50, 53, CYRILLIC_G0_OPT1},
    {65, 73, CYRILLIC_G0_OPT1},
    {75, 79, CYRILLIC_G0_OPT1},
    {82, 85, CYRILLIC_G0_OPT1},
    {95, 95, CYRILLIC_G0_OPT1}
};

PRIVATE
const TTX_FontDesc TTX_Font_CyrillicOpt2G0 =
{
    .type = TYPE_REFERENCE,
    .capacity = 96,
    .glyphNum = sizeof(CyrillicOpt2G0_localRef)/sizeof(CyrillicOpt2G0_localRef[0]),
    .description=
    {
        .using =
        {
            FONT_DONTCARE,
            sizeof(CyrillicOpt2G0_localRef)/sizeof(CyrillicOpt2G0_localRef[0]),
            CyrillicOpt2G0_localRef
        },
        .reference =
        {
            sizeof(CyrillicOpt2G0_Ref)/sizeof(CyrillicOpt2G0_Ref[0]),
            CyrillicOpt2G0_Ref
        }    },
    .quirkGlyphTable =
    {
        .recordNum = 0,
        .table = 0
    }
};

///////////////////////////////////////////////////////////////////////
PRIVATE
const TT_U8 CyrillicOpt3G0_localRef[]=
{
    6,
    57,
    60,
    63,
    89,
    92
};

PRIVATE
const stRefElem CyrillicOpt3G0_Ref[] =
{
    {0, 5, CYRILLIC_G0_OPT1},
    {7, 31, CYRILLIC_G0_OPT1},
    {32, 56, CYRILLIC_G0_OPT2},
    {58, 59, CYRILLIC_G0_OPT2},
    {61, 62, CYRILLIC_G0_OPT2},
    {64, 88, CYRILLIC_G0_OPT2},
    {90, 91, CYRILLIC_G0_OPT2},
    {93, 95, CYRILLIC_G0_OPT2}
};

PRIVATE
const TTX_FontDesc TTX_Font_CyrillicOpt3G0 =
{
    .type = TYPE_REFERENCE,
    .capacity = 96,
    .glyphNum = sizeof(CyrillicOpt3G0_localRef)/sizeof(CyrillicOpt3G0_localRef[0]),
    .description=
    {
        .using =
        {
            FONT_DONTCARE,
            sizeof(CyrillicOpt3G0_localRef)/sizeof(CyrillicOpt3G0_localRef[0]),
            CyrillicOpt3G0_localRef
        },
        .reference =
        {
            sizeof(CyrillicOpt3G0_Ref)/sizeof(CyrillicOpt3G0_Ref[0]),
            CyrillicOpt3G0_Ref
        }    },
    .quirkGlyphTable =
    {
        .recordNum = 0,
        .table = 0
    }
};

///////////////////////////////////////////////////////////////////////

PRIVATE
const TT_U8 TTX_Font_Cyrillic_G2_LocalRef[] =
{
    6,  8, 25, 57, 58, 59, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77,
    78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95
};

PRIVATE
const TTX_FontDesc TTX_Font_Cyrillic_G2 =
{
    .type = TYPE_USING,
    .capacity = 96,
    .glyphNum = sizeof(TTX_Font_Cyrillic_G2_LocalRef)/sizeof(TTX_Font_Cyrillic_G2_LocalRef[0]),
    .description=
    {
        .using =
        {
            LATIN_G2,
            sizeof(TTX_Font_Cyrillic_G2_LocalRef)/sizeof(TTX_Font_Cyrillic_G2_LocalRef[0]),
            TTX_Font_Cyrillic_G2_LocalRef
        },
        .reference =
        {
            0, 0
        }
    },
    .quirkGlyphTable =
    {
        .recordNum = 0,
        .table = 0
    }
};


///////////////////////////////////////////////////////////////////////
PRIVATE
const TT_U8 GreekG0_localRef[] =
{
    32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
    61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
    81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95
};

PRIVATE
const TTX_FontDesc TTX_Font_Greek_G0 =
{
    .type = TYPE_USING,
    .capacity = 96,
    .glyphNum = sizeof(GreekG0_localRef)/sizeof(GreekG0_localRef[0]),
    .description=
    {
        .using =
        {
            CYRILLIC_G0_OPT1,
            sizeof(GreekG0_localRef)/sizeof(GreekG0_localRef[0]),
            GreekG0_localRef
        },
        .reference =
        {
            0, 0
        }    },
    .quirkGlyphTable =
    {
        .recordNum = 0,
        .table = 0
    }
};

///////////////////////////////////////////////////////////////////////

PRIVATE
const TT_U8 GreekG2_localRef[] =
{
    1, 2, 4, 5, 6, 8, 9, 10, 11, 21, 22, 23, 24, 26, 27, 31, 47, 48, 57, 58,
    59, 64, 65, 66, 67, 68, 69,
    70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89,
    90, 91, 92, 93, 94, 95

};

PRIVATE
const stRefElem Greek_G2_Ref[] =
{
    {0, 0, CYRILLIC_G0_OPT2},
    {3, 3, CYRILLIC_G0_OPT2},
    {7, 7, CYRILLIC_G0_OPT2},
    {12, 20, CYRILLIC_G0_OPT2},
    {25, 25, CYRILLIC_G0_OPT2},
    {28, 30, CYRILLIC_G0_OPT2},
    {32, 46, CYRILLIC_G0_OPT2},
    {49, 56, CYRILLIC_G0_OPT2},
    {60, 63, CYRILLIC_G0_OPT2}
};

PRIVATE
const TTX_FontDesc TTX_Font_Greek_G2 =
{
    .type = TYPE_REFERENCE,
    .capacity = 96,
    .glyphNum = sizeof(GreekG2_localRef)/sizeof(GreekG2_localRef[0]),
    .description=
    {
        .using =
        {
            FONT_DONTCARE,
            sizeof(GreekG2_localRef)/sizeof(GreekG2_localRef[0]),
            GreekG2_localRef
        },
        .reference =
        {
            sizeof(Greek_G2_Ref)/sizeof(Greek_G2_Ref[0]),
            Greek_G2_Ref
        }    },
    .quirkGlyphTable =
    {
        .recordNum = 0,
        .table = 0
    }
};

///////////////////////////////////////////////////////////////////////

PRIVATE
const TT_U8 Hebrew_G0_localRef[] =
{
    59, 60,
    61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80,
    81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95
};

PRIVATE
const stRefElem Hebrew_G0_Ref[] =
{
    {0, 2, LATIN_G0},
    {3, 3, LATIN_G2},
    {4, 4, CYRILLIC_G0_OPT1},
    {5, 31, LATIN_G0},
    {32, 58, LATIN_G0}
};

PRIVATE
const TTX_FontDesc TTX_Font_Hebrew_G0 =
{
    .type = TYPE_REFERENCE,
    .capacity = 96,
    .glyphNum = sizeof(Hebrew_G0_localRef)/sizeof(Hebrew_G0_localRef[0]),
    .description=
    {
        .using =
        {
            FONT_DONTCARE,
            sizeof(Hebrew_G0_localRef)/sizeof(Hebrew_G0_localRef[0]),
            Hebrew_G0_localRef
        },
        .reference =
        {
            sizeof(Hebrew_G0_Ref)/sizeof(Hebrew_G0_Ref[0]),
            Hebrew_G0_Ref
        }    },
    .quirkGlyphTable =
    {
        .recordNum = 0,
        .table = 0
    }
};

///////////////////////////////////////////////////////////////////////

PRIVATE
const TTX_FontDesc TTX_Font_International1 =
{
    .type = TYPE_PRIMITIVE,
    .capacity = 96,
    .glyphNum = 96,
    .description=
    {
        .using ={FONT_DONTCARE,0,0},
        .reference = {0,0}    },
    .quirkGlyphTable =
    {
        .recordNum = 0,
        .table = 0
    }
};

///////////////////////////////////////////////////////////////////////
PRIVATE
const TTX_FontDesc TTX_Font_International2 =
{
    .type = TYPE_PRIMITIVE,
    .capacity = 96,
    .glyphNum = 96,
    .description=
    {
        .using ={FONT_DONTCARE,0,0},
        .reference = {0,0}    },
    .quirkGlyphTable =
    {
        .recordNum = 0,
        .table = 0
    }
};

///////////////////////////////////////////////////////////////////////
PRIVATE
const TTX_FontDesc TTX_Font_International3 =
{
    .type = TYPE_PRIMITIVE,
    .capacity = 35,
    .glyphNum = 35,
    .description=
    {
        .using ={FONT_DONTCARE,0,0},
        .reference = {0,0}    },
    .quirkGlyphTable =
    {
        .recordNum = 0,
        .table = 0
    }
};

///////////////////////////////////////////////////////////////////////
PRIVATE
const TTX_FontDesc TTX_Font_Symbol =
{
    .type = TYPE_PRIMITIVE,
    .capacity = 14,
    .glyphNum = 14,
    .description=
    {
        .using ={FONT_DONTCARE,0,0},
        .reference = {0,0}    },
    .quirkGlyphTable =
    {
        .recordNum = 0,
        .table = 0
    }
};

PRIVATE
const TTX_FontDesc TTX_Font_ARABIC_EXTENTION =
{
    .type = TYPE_PRIMITIVE,
    .capacity = 53,
    .glyphNum = 53,
    .description=
    {
        .using ={FONT_DONTCARE,0,0},
        .reference = {0,0}
    },
    .quirkGlyphTable =
    {
        .recordNum = 0,
        .table = 0
    }
};

PRIVATE
const TTX_FontDesc* TTX_FontDescs[] =
{
    &TTX_Font_Arabic_G0,
    &TTX_Font_Arabic_G2,
    &TTX_Font_Farsi_G0,
    &TTX_Font_Farsi_G2,
    &TTX_Font_Latin_G0,
    &TTX_Font_Latin_G2,
    &TTX_Font_CyrillicOpt1G0,
    &TTX_Font_CyrillicOpt2G0,
    &TTX_Font_CyrillicOpt3G0,
    &TTX_Font_Cyrillic_G2,
    &TTX_Font_Greek_G0,
    &TTX_Font_Greek_G2,
    &TTX_Font_Hebrew_G0,
    &TTX_Font_International1,
    &TTX_Font_International2,
    &TTX_Font_International3,
    &TTX_Font_Symbol,
    &TTX_Font_ARABIC_EXTENTION
};

