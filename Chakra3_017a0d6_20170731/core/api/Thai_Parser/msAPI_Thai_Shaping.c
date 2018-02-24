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
//---------------------------------------------------------------------------
// ICU License - ICU 1.8.1 and later
//
// COPYRIGHT AND PERMISSION NOTICE
//
// Copyright (c) 1995-2008 International Business Machines Corporation and others
//
// All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, and/or sell copies of the Software,
// and to permit persons to whom the Software is furnished to do so, provided that
// the above copyright notice(s) and this permission notice appear in all copies of
// the Software and that both the above copyright notice(s) and this permission
// notice appear in supporting documentation.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
// PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS. IN NO EVENT SHALL
// THE COPYRIGHT HOLDER OR HOLDERS INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM,
// OR ANY SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER
// RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
// NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE
// OR PERFORMANCE OF THIS SOFTWARE.
//
// Except as contained in this notice, the name of a copyright holder shall not be
// used in advertising or otherwise to promote the sale, use or other dealings in
// this Software without prior written authorization of the copyright holder.
//
// All trademarks and registered trademarks mentioned herein are the property of
// their respective owners.
//---------------------------------------------------------------------------
#ifndef __THAISHAPING_C
#define __THAISHAPING_C

#include "LETypes.h"
#include "msAPI_Thai_Shaping.h"

enum {
    CH_SPACE        = 0x0020,
    CH_YAMAKKAN     = 0x0E4E,
    CH_MAI_HANAKAT  = 0x0E31,
    CH_SARA_AA      = 0x0E32,
    CH_SARA_AM      = 0x0E33,
    CH_SARA_UEE     = 0x0E37,
    CH_MAITAIKHU    = 0x0E47,
    CH_NIKHAHIT     = 0x0E4D,
    CH_SARA_U       = 0x0E38,
    CH_PHINTHU      = 0x0E3A,
    CH_YO_YING      = 0x0E0D,
    CH_THO_THAN     = 0x0E10,
    CH_DOTTED_CIRCLE = 0x25CC
};

extern StateTransition getTransition(le_uint8 state, le_uint8 currClass);

U8 MinusDrawTable[] =
{
    0,  //0x0E01    0
    0,  //0x0E02    1
    0,  //0x0E03    2
    0,  //0x0E04    3
    0,  //0x0E05    4
    0,  //0x0E06    5
    0,  //0x0E07    6
    0,  //0x0E08    7
    0,  //0x0E09    8
    0,  //0x0E0A    9
    0,  //0x0E0B    10
    0,  //0x0E0C    11
    0,  //0x0E0D    12
    0,  //0x0E0E    13
    0,  //0x0E0F    14
    0,  //0x0E10    15
    0,  //0x0E11    16
    0,  //0x0E12    17
    0,  //0x0E13    18
    0,  //0x0E14    19
    0,  //0x0E15    20
    0,  //0x0E16    21
    0,  //0x0E17    22
    0,  //0x0E18    23
    0,  //0x0E19    24
    0,  //0x0E1A    25
    0,  //0x0E1B    26
    0,  //0x0E1C    27
    0,  //0x0E1D    28
    0,  //0x0E1E    29
    0,  //0x0E1F    30
    0,  //0x0E20    31
    0,  //0x0E21    32
    0,  //0x0E22    33
    0,  //0x0E23    34
    0,  //0x0E24    35
    0,  //0x0E25    36
    0,  //0x0E26    37
    0,  //0x0E27    38
    0,  //0x0E28    39
    0,  //0x0E29    40
    0,  //0x0E2A    41
    0,  //0x0E2B    42
    0,  //0x0E2C    43
    0,  //0x0E2D    44
    0,  //0x0E2E    45
    0,  //0x0E2F    46
    0,  //0x0E30    47
    1,  //0x0E31    48
    0,  //0x0E32    49
    0,  //0x0E33    50
    1,  //0x0E34    51
    1,  //0x0E35    52
    1,  //0x0E36    53
    1,  //0x0E37    54
    1,  //0x0E38    55
    1,  //0x0E39    56
    1,  //0x0E3A    57
    0,  //0x0E3B    58
    0,  //0x0E3C    59
    0,  //0x0E3D    60
    0,  //0x0E3E    61
    0,  //0x0E3F    62
    0,  //0x0E40    63
    0,  //0x0E41    64
    0,  //0x0E42    65
    0,  //0x0E43    66
    0,  //0x0E44    67
    0,  //0x0E45    68
    0,  //0x0E46    69
    1,  //0x0E47    70
    1,  //0x0E48    71
    1,  //0x0E49    72
    1,  //0x0E4A    73
    1,  //0x0E4B    74
    1,  //0x0E4C    75
    1,  //0x0E4D    76
    1,  //0x0E4E    77
    0,  //0x0E4F    78
    0,  //0x0E50    79
    0,  //0x0E51    80
    0,  //0x0E52    81
    0,  //0x0E53    82
    0,  //0x0E54    83
    0,  //0x0E55    84
    0,  //0x0E56    85
    0,  //0x0E57    86
    0,  //0x0E58    87
    0,  //0x0E59    88
    0,  //0x0E5A    89
    0   //0x0E5B    90
};

U8 MinusDrawTablePersentation[] =
{
    0,  //0xF700
    1,  //0xF701
    1,  //0xF702
    1,  //0xF703
    1,  //0xF704
    1,  //0xF705
    1,  //0xF706
    1,  //0xF707
    1,  //0xF708
    1,  //0xF709
    1,  //0xF70A
    1,  //0xF70B
    1,  //0xF70C
    1,  //0xF70D
    1,  //0xF70E
    0,  //0xF70F
    1,  //0xF710
    1,  //0xF711
    1,  //0xF712
    1,  //0xF713
    1,  //0xF714
    1,  //0xF715
    1,  //0xF716
    1,  //0xF717
    1,  //0xF718
    1,  //0xF719
    1   //0xF71A
};

static le_uint8 getCharClass(LEUnicode ch)
{
    le_uint8 charClass = NON;

    if (ch >= 0x0E00 && ch <= 0x0E5B) {
        charClass = classTable[ch - 0x0E00];
    }

    return charClass;
}

static LEUnicode leftAboveVowel(LEUnicode vowel)//, le_uint8 glyphSet)
{
    static code LEUnicode leftAboveVowels[7] = {
//        {0x0E61, 0x0E32, 0x0E33, 0x0E64, 0x0E65, 0x0E66, 0x0E67},
        0xF710, 0x0E32, 0x0E33, 0xF701, 0xF702, 0xF703, 0xF704
//        {0xF884, 0x0E32, 0x0E33, 0xF885, 0xF886, 0xF887, 0xF788},
//        {0x0E31, 0x0E32, 0x0E33, 0x0E34, 0x0E35, 0x0E36, 0x0E37}
    };

    if (vowel >= CH_MAI_HANAKAT && vowel <= CH_SARA_UEE) {
        //return leftAboveVowels[glyphSet][vowel - CH_MAI_HANAKAT];
        return leftAboveVowels[vowel - CH_MAI_HANAKAT];
    }

//    if (vowel == CH_YAMAKKAN && glyphSet == 0) {
//        return 0x0E7E;
//    }

    return vowel;
}

static LEUnicode lowerRightTone(LEUnicode tone)//, le_uint8 glyphSet)
{
    static code LEUnicode lowerRightTones[7] = {
//        {0x0E68, 0x0E69, 0x0E6A, 0x0E6B, 0x0E6C, 0x0E6D, 0x0E6E},
        0x0E47, 0xF70A, 0xF70B, 0xF70C, 0xF70D, 0xF70E, 0x0E4D
//        {0x0E47, 0xF88B, 0xF88E, 0xF891, 0xF894, 0xF897, 0x0E4D},
//        {0x0E47, 0x0E48, 0x0E49, 0x0E4A, 0x0E4B, 0x0E4C, 0x0E4D}
    };

    if (tone >= CH_MAITAIKHU && tone <= CH_NIKHAHIT) {
        //return lowerRightTones[glyphSet][tone - CH_MAITAIKHU];
        return lowerRightTones[tone - CH_MAITAIKHU];
    }

    return tone;
}

static LEUnicode lowerLeftTone(LEUnicode tone)//, le_uint8 glyphSet)
{
    static code LEUnicode lowerLeftTones[7] = {
//        {0x0E76, 0x0E77, 0x0E78, 0x0E79, 0x0E7A, 0x0E7B, 0x0E7C},
        0xF712, 0xF705, 0xF706, 0xF707, 0xF708, 0xF709, 0xF711
//        {0xF889, 0xF88C, 0xF88F, 0xF892, 0xF895, 0xF898, 0xF899},
//        {0x0E47, 0x0E48, 0x0E49, 0x0E4A, 0x0E4B, 0x0E4C, 0x0E4D}
    };

    if (tone >= CH_MAITAIKHU && tone <= CH_NIKHAHIT) {
        //return lowerLeftTones[glyphSet][tone - CH_MAITAIKHU];
        return lowerLeftTones[tone - CH_MAITAIKHU];
    }

    return tone;
}

static LEUnicode upperLeftTone(LEUnicode tone)//, le_uint8 glyphSet)
{
    static code LEUnicode upperLeftTones[7] = {
//        {0x0E6F, 0x0E70, 0x0E71, 0x0E72, 0x0E73, 0x0E74, 0x0E75},
        0xF712, 0xF713, 0xF714, 0xF715, 0xF716, 0xF717, 0xF711
//        {0xF889, 0xF88A, 0xF88D, 0xF890, 0xF893, 0xF896, 0xF899},
//        {0x0E47, 0x0E48, 0x0E49, 0x0E4A, 0x0E4B, 0x0E4C, 0x0E4D}
    };

    if (tone >= CH_MAITAIKHU && tone <= CH_NIKHAHIT) {
        //return upperLeftTones[glyphSet][tone - CH_MAITAIKHU];
        return upperLeftTones[tone - CH_MAITAIKHU];
    }

    return tone;
}

static LEUnicode lowerBelowVowel(LEUnicode vowel)//, le_uint8 glyphSet)
{
    static code LEUnicode lowerBelowVowels[3] = {
//        {0x0E3C, 0x0E3D, 0x0E3E},
        0xF718, 0xF719, 0xF71A
//        {0x0E38, 0x0E39, 0x0E3A},
//        {0x0E38, 0x0E39, 0x0E3A}

    };

    if (vowel >= CH_SARA_U && vowel <= CH_PHINTHU) {
        //return lowerBelowVowels[glyphSet][vowel - CH_SARA_U];
        return lowerBelowVowels[vowel - CH_SARA_U];
    }

    return vowel;
}

static LEUnicode noDescenderCOD(LEUnicode cod)//, le_uint8 glyphSet)
{
    static code LEUnicode noDescenderCODs[4] = {
//        {0x0E60, 0x0E0E, 0x0E0F, 0x0E63},
        0xF70F, 0x0E0E, 0x0E0F, 0xF700
//        {0x0E0D, 0x0E0E, 0x0E0F, 0x0E10},
//        {0x0E0D, 0x0E0E, 0x0E0F, 0x0E10}

    };

    if (cod >= CH_YO_YING && cod <= CH_THO_THAN) {
        //return noDescenderCODs[glyphSet][cod - CH_YO_YING];
        return noDescenderCODs[cod - CH_YO_YING];
    }

    return cod;
}

//le_uint8 doTransition (StateTransition transition, LEUnicode currChar, le_int32 inputIndex, /*le_uint8 glyphSet,*/
//        LEUnicode *errorChar, LEUnicode *outputBuffer, /*LEGlyphStorage &glyphStorage,*/ le_int32 *outputIndex)
static le_uint8 doTransition (StateTransition transition, LEUnicode currChar,
        LEUnicode *errorChar, LEUnicode *outputBuffer, le_uint16 *outputIndex)
{
//  LEErrorCode success = LE_NO_ERROR;

    switch (transition.action) {
    case tA:
//        glyphStorage.setCharIndex(outputIndex, inputIndex, success);
        outputBuffer[*outputIndex] = currChar;
        (*outputIndex)++;
        break;

    case tC:
//      glyphStorage.setCharIndex(outputIndex, inputIndex, success);
        outputBuffer[*outputIndex] = currChar;
        (*outputIndex)++;
        break;

    case tD:
//      glyphStorage.setCharIndex(outputIndex, inputIndex, success);
//        outputBuffer[*outputIndex] = leftAboveVowel(currChar, glyphSet);
        outputBuffer[*outputIndex] = leftAboveVowel(currChar);
        (*outputIndex)++;
        break;

    case tE:
//      glyphStorage.setCharIndex(outputIndex, inputIndex, success);
//        outputBuffer[*outputIndex] = lowerRightTone(currChar, glyphSet);
        outputBuffer[*outputIndex] = lowerRightTone(currChar);
        (*outputIndex)++;
        break;

    case tF:
//      glyphStorage.setCharIndex(outputIndex, inputIndex, success);
//        outputBuffer[*outputIndex] = lowerLeftTone(currChar, glyphSet);
        outputBuffer[*outputIndex] = lowerLeftTone(currChar);
        (*outputIndex)++;
        break;

    case tG:
//      glyphStorage.setCharIndex(outputIndex, inputIndex, success);
//        outputBuffer[*outputIndex] = upperLeftTone(currChar, glyphSet);
        outputBuffer[*outputIndex] = upperLeftTone(currChar);
        (*outputIndex)++;
        break;

    case tH:
    {
        LEUnicode cod = outputBuffer[*outputIndex - 1];
        LEUnicode coa = noDescenderCOD(cod);//, glyphSet);

        if (cod != coa) {
            outputBuffer[*outputIndex - 1] = coa;

//              glyphStorage.setCharIndex(outputIndex, inputIndex, success);
            outputBuffer[*outputIndex] = currChar;
            (*outputIndex)++;
            break;
        }

//      glyphStorage.setCharIndex(outputIndex, inputIndex, success);
//        outputBuffer[*outputIndex] = lowerBelowVowel(currChar, glyphSet);
        outputBuffer[*outputIndex] = lowerBelowVowel(currChar);
        (*outputIndex)++;
        break;
    }

    case tR:
//      glyphStorage.setCharIndex(outputIndex, inputIndex, success);
        outputBuffer[*outputIndex] = *errorChar;
        (*outputIndex)++;

//      glyphStorage.setCharIndex(outputIndex, inputIndex, success);
        outputBuffer[*outputIndex] = currChar;
        (*outputIndex)++;
        break;

    case tS:
        if (currChar == CH_SARA_AM) {
//          glyphStorage.setCharIndex(outputIndex, inputIndex, success);
            outputBuffer[*outputIndex] = *errorChar;
            (*outputIndex)++;
        }

//      glyphStorage.setCharIndex(outputIndex, inputIndex, success);
        outputBuffer[*outputIndex] = currChar;
        (*outputIndex)++;
        break;

    default:
        // FIXME: if we get here, there's an error
        // in the state table!
//      glyphStorage.setCharIndex(outputIndex, inputIndex, success);
        outputBuffer[*outputIndex] = currChar;
        (*outputIndex)++;
        break;
     }

     return transition.nextState;
}

//le_uint8 getNextState(LEUnicode ch, le_uint8 prevState, le_int32 inputIndex, /*le_uint8 glyphSet,*/ LEUnicode *errorChar,
//                              le_uint8 *charClass, LEUnicode *output, /*LEGlyphStorage &glyphStorage,*/ le_int32 *outputIndex)
static le_uint8 getNextState(LEUnicode ch, le_uint8 prevState, LEUnicode *errorChar,
                              le_uint8 *charClass, LEUnicode *output, le_uint16 *outputIndex)
{
    StateTransition transition;

    *charClass = getCharClass(ch);
    transition = getTransition(prevState, *charClass);

    return doTransition(transition, ch, /*inputIndex, glyphSet,*/ errorChar, output, /*glyphStorage,*/ outputIndex);
}

static le_bool isLegalHere(LEUnicode ch, le_uint8 prevState)
{
    le_uint8 charClass;
    StateTransition transition;

    charClass = getCharClass(ch);
    transition = getTransition(prevState, charClass);

    switch (transition.action) {
    case tA:
    case tC:
    case tD:
    case tE:
    case tF:
    case tG:
    case tH:
        return TRUE;

    case tR:
    case tS:
        return FALSE;

    default:
        // FIXME: if we get here, there's an error
        // in the state table!
        return FALSE;
    }
}

//le_int32 compose(const LEUnicode *input, le_int32 offset, le_int32 charCount, /*le_uint8 glyphSet,*/
//                          LEUnicode *errorChar, LEUnicode *output/*, LEGlyphStorage &glyphStorage*/)
LEUnicode Thai_compose(LEUnicode *input, le_uint16 offset, le_uint16 charCount, le_uint16 max, LEUnicode *output)
{
    LEUnicode errorChar = THAIERRORCHAR;
    le_uint8 state = 0;
//    le_int32 inputIndex;
//    le_int32 outputIndex = 0;
    le_uint8 conState = 0;
//    le_int32 conInput = -1;
//    le_int32 conOutput = -1;
    le_uint16 inputIndex;
    le_uint16 outputIndex = 0;
    le_int32 conInput = -1;
    le_int32 conOutput = -1;
    int j;

    if (input == NULL || offset >= max || (offset + charCount) > max) {
        //*success = LE_ILLEGAL_ARGUMENT_ERROR;
        return 0;
    }

    for (inputIndex = 0; inputIndex < charCount; inputIndex += 1) {
        LEUnicode ch = input[inputIndex + offset];
        le_uint8 charClass;

        // Decompose SARA AM into NIKHAHIT + SARA AA
        if (ch == CH_SARA_AM && isLegalHere(ch, state)) {
            outputIndex = conOutput;
            state = getNextState(CH_NIKHAHIT, conState, /*inputIndex, glyphSet,*/ &errorChar, &charClass,
                output, /*glyphStorage,*/ &outputIndex);

            for (j = conInput + 1; j < inputIndex; j += 1) {
                ch = input[j + offset];
                state = getNextState(ch, state, /*j, glyphSet,*/ &errorChar, &charClass,
                    output, /*glyphStorage,*/ &outputIndex);
            }

            ch = CH_SARA_AA;
        }

        state = getNextState(ch, state, /*inputIndex, glyphSet,*/ &errorChar, &charClass,
            output, /*glyphStorage,*/ &outputIndex);

        if (charClass >= CON && charClass <= COD) {
            conState = state;
            conInput = inputIndex;
            conOutput = outputIndex;
        }
    }

    return outputIndex;
}

#endif
