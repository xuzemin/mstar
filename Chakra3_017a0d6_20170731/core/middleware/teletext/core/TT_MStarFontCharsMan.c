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

#include <stdio.h>
#include <string.h>
#include "datatype.h"
#include "sysinfo.h"
#include "TT_Global.h"
#include "TT_MStarFontCharsMan.h"
#include "TT_API25.h"
#include "TT_DriverIntRam.h"
#include "msAPI_Font.h"
#include "InfoBlock.h"
#include "msAPI_OSD_Resource.h"
#include "msAPI_MIU.h"
#include "SysInit.h"
#if defined(TTX_USING_MSTAR_FONT_BIN)

#include "TT_MStarFontBinTable.h"

///////////////////////////////////////////////////////////////////
typedef struct
{
    TT_U32  size;
    TT_U16* entity;
}fontIndexTable;
///////////////////////////////////////////////////////////////////

#if (BIN_ID_FONT_TTX == BIN_ID_TTFONT_24_20)
#define WORKING_FONT_BUFFER_SIZE    (150*1024)
#elif (BIN_ID_FONT_TTX == BIN_ID_TTFONT_34_30)
#define WORKING_FONT_BUFFER_SIZE    (200*1024)
#else
#define WORKING_FONT_BUFFER_SIZE    (200*1024)
#endif

//#define TTX_FONT_BUF_PHY_ADDR GE_ADDR_ALIGNMENT(((TTX_FONT_START_MEMORY_TYPE & MIU1) ? (TTX_FONT_START_ADR | MIU_INTERVAL) : (TTX_FONT_START_ADR)))
#define MASKTABLE_SIZE(X)   ((X)*12)

PRIVATE TT_U8* _fontG1BlockMosaik;
PRIVATE TT_U8* _fontG1SeparatedBlockMosaik;
PRIVATE TT_U8* _fontG3Smooth;
PRIVATE TT_U8* _fontDRCS;
PRIVATE OSD_RESOURCE_FONT_INFO _fontInfo;
PRIVATE TT_U32 _indexTableAddr;
PRIVATE TT_U8* _maskTable;
PRIVATE TT_U32 _bufferBeginningAddr;
PRIVATE FONT_BIN_HEADER _fontBinHeader;

PRIVATE
fontIndexTable _fontIndexTables[NUM_OF_FONTS];

PRIVATE
void _CreateBlockGlyphsFont(void);

///////////////////////////////////////////////////////////////////

PRIVATE
TT_U32 _GetGlyphWidth(void)
{
    return _fontInfo.width;
}

PRIVATE
TT_U32 _GetGlyphHeight(void)
{
    return _fontInfo.height;
}

PRIVATE
TT_U32 _GetBPP(void)
{
    return _fontInfo.bpp;
}

PRIVATE
TT_U32 _GetOneGlyphSize(void)
{
    return _fontInfo.char_glyph_bytes;
}

PRIVATE
TT_U32 _GetPitch(void)
{
    return _fontInfo.pitch * _fontInfo.hw_pitch;
}



PRIVATE
void _CreateBlockGlyphsFontTable(TT_U8* pFontDest,
                                     TT_U32 destGlyphBPP,
                                     TT_U32 destBytesOneGlyph,
                                     TT_U32 destSizeOfOneLine,
                                     const TT_U8* pFontSrc,
                                     TT_U32 srcGlyphBPP,
                                     TT_U32 srcGlyphWidth,
                                     TT_U32 srcGlyphHeight,
                                     TT_U32 srcBytesOneGlyph,
                                     TT_U32 glyphNum,
                                     TT_U32 multipleInWidth,
                                     TT_U32 multipleInHeight)
{
  TT_U32 i, tmp1;
  TT_U32 bitCounter;
  TT_U32 line, char_x, h, w, value;
  TT_U32 shift_mask1 = 7 / srcGlyphBPP;
  TT_U32 mask1 = ((1<<srcGlyphBPP)-1) << shift_mask1;
  TT_U32 srcBitsOneLine, dstBitsOneLine;

  srcBitsOneLine = srcGlyphWidth * srcGlyphBPP;
  dstBitsOneLine = destSizeOfOneLine*8;

  memset(pFontDest, 0, destBytesOneGlyph*glyphNum);
  for(i = 0; i < glyphNum; ++i)
  {
    bitCounter = 0;
    for(line = 0; line < srcGlyphHeight; ++line)
    {
        bitCounter = dstBitsOneLine * line * multipleInHeight;
        for(h = 0; h < multipleInHeight; ++h)
        {
            TT_U32 bitCounter1 = bitCounter + dstBitsOneLine * h;
            TT_U32 pixelCount = 0;

            for(char_x = 0; char_x < srcGlyphWidth; ++char_x)
            {
                tmp1 = (line * srcBitsOneLine) + (char_x * srcGlyphBPP);

                value = (pFontSrc[tmp1/8]) & (mask1 >> (tmp1 & shift_mask1));
                value = value >> (7-(tmp1 & shift_mask1));

                for(w = 0; w < multipleInWidth; ++w,++pixelCount)
                {
                    if(_maskTable[pixelCount] == 1)
                    {
                        pFontDest[bitCounter1/8] =
                            (TT_U8)((pFontDest[bitCounter1/8] << destGlyphBPP) | value);
                        bitCounter1 += destGlyphBPP;
                    }
                }
            }

            //pack the tail byte
            pFontDest[bitCounter1/8] =
                pFontDest[bitCounter1/8] << (8-((bitCounter1-bitCounter)&7));
        }
    }

    pFontSrc = pFontSrc + srcBytesOneGlyph ;
    pFontDest = pFontDest + destBytesOneGlyph;
  }
}

PRIVATE
TT_BOOL _LoadFont(void)
{
    TT_U32  u32BinBaseAddr,
            pitch_bits;
    TT_U32  tmpAddr1,
            tmpAddr2;

    BININFO   BinInfo;
    BOOLEAN   bResult;
    eRETCODE  _tmpret = FAILURE;

    BinInfo.B_ID = BIN_ID_FONT_TTX;

    msAPI_MIU_Get_BinInfo(&BinInfo, &bResult);

    if ( bResult != PASS)
    {
        return FALSE;
    }
    u32BinBaseAddr =
        _PA2VA((_bufferBeginningAddr & MIU1) ? (_bufferBeginningAddr | MIU_INTERVAL) : (_bufferBeginningAddr));

    tmpAddr1 = u32BinBaseAddr + WORKING_FONT_BUFFER_SIZE;//_PA2VA(((POOL_BUFFER_ADR) & MIU1) ? ((POOL_BUFFER_ADR) | MIU_INTERVAL) : (POOL_BUFFER_ADR));
    tmpAddr2 = tmpAddr1 + WORKING_FONT_BUFFER_SIZE; //u32BinBaseAddr + 0x32000;//POOL_BUFFER_ADR+0x32000;

    _tmpret = MDrv_DMA_LoadBin(&BinInfo,
                                   u32BinBaseAddr,
                                   tmpAddr1,
                                   tmpAddr2);

    memcpy(&_fontBinHeader,
            (void*)u32BinBaseAddr,
            sizeof(_fontBinHeader));

    _fontInfo.glyph_addr= _bufferBeginningAddr + _fontBinHeader.u32FontGlyphOffset;
    _fontInfo.bpp = _fontBinHeader.u32BPP;
    _fontInfo.char_num = _fontBinHeader.u32CharNum;
    _fontInfo.width = _fontBinHeader.u32Width;
    _fontInfo.height = _fontBinHeader.u32Height;
    _fontInfo.hw_pitch = _fontBinHeader.u32Pitch;

    pitch_bits = _fontInfo.hw_pitch*8;
    if(_fontInfo.bpp == 3)
        _fontInfo.pitch = (_fontInfo.width + (pitch_bits-1)) / pitch_bits;
    else
        _fontInfo.pitch = (_fontInfo.width + (pitch_bits-1)) / pitch_bits * _fontInfo.bpp;

    _fontInfo.char_glyph_bytes = _fontBinHeader.u32CharGlyphBytes;


    {

        TT_U32 tmp;
        TT_U32 multiple_width;

        tmp = (TT_U32)_fontInfo.glyph_addr + _GetOneGlyphSize()*(_fontInfo.char_num+1);
        _fontG1BlockMosaik = (TT_U8*)GE_ADDR_ALIGNMENT(tmp);

        tmp = (TT_U32)_fontG1BlockMosaik + _GetOneGlyphSize()*96;
        _fontG1SeparatedBlockMosaik = (TT_U8*)GE_ADDR_ALIGNMENT(tmp);

        tmp = (TT_U32)_fontG1SeparatedBlockMosaik + _GetOneGlyphSize()*96;
        _fontG3Smooth = (TT_U8*)GE_ADDR_ALIGNMENT(tmp);

        tmp = (TT_U32)_fontG3Smooth + _GetOneGlyphSize()*96;
        _fontDRCS = (TT_U8*)GE_ADDR_ALIGNMENT(tmp);

        multiple_width = (_GetGlyphWidth()+12-1) / 12;

        _maskTable =(TT_U8*)(((unsigned)_fontDRCS) + _GetOneGlyphSize()*TT_DISPLAY_MAX_DRCS);

        _indexTableAddr = (TT_U32)_maskTable + MASKTABLE_SIZE(multiple_width);

        _indexTableAddr = GE_ALIGNED_VALUE(_indexTableAddr, 4);

        _maskTable = (TT_U8*)_PA2VA((TT_U32)_maskTable);

        _CreateBlockGlyphsFont();
    }

    TT_DriverIntRamMemset ((void *)(tmpAddr1 & NON_CACHEABLE_TO_CACHEABLE_MASK), 0, WORKING_FONT_BUFFER_SIZE);
    TT_DriverIntRamMemset ((void *)(tmpAddr2 & NON_CACHEABLE_TO_CACHEABLE_MASK), 0, WORKING_FONT_BUFFER_SIZE);

    return TRUE;
}

PRIVATE
TT_BOOL _Init(void)
{
    TT_BOOL result = TRUE;

    _bufferBeginningAddr = (TT_U32)TT_DriverIntRamAlloc(WORKING_FONT_BUFFER_SIZE+8);
    _bufferBeginningAddr = _VA2PA(_bufferBeginningAddr);
    _bufferBeginningAddr = GE_ALIGNED_VALUE(_bufferBeginningAddr,8);


    result = _LoadFont();


    return result;
}

PRIVATE
void _CreateDRCS(TT_U8* drcsMap, TT_U32 number)
{
  if(number == 0)
    return;

  _CreateBlockGlyphsFontTable((TT_U8*)_PA2VA((MS_U32)_fontDRCS),
                              _GetBPP(),
                              _GetOneGlyphSize(),
                              _GetOneGlyphSize()/_GetGlyphHeight(),
                              drcsMap,
                              1,
                              12,
                              10,
                              16,
                              number,
                              _GetGlyphWidth() / 12,
                              _GetGlyphHeight() / 10);
}

PRIVATE
TT_U32 _BuildGlyphIndexTable(TT_U32 startingAddr)
{
    TT_U32 i, j;
    TT_U32 count = 0;
    TT_U16* glyphIndexAddr =
        (TT_U16*)startingAddr;

    for(i = 0; i < NUM_OF_FONTS; ++i)
    {
        _fontIndexTables[i].size = TTX_FontDescs[i]->capacity;

        _fontIndexTables[i].entity = glyphIndexAddr;

        memset( _fontIndexTables[i].entity,
                0,
                TTX_FontDescs[i]->capacity*sizeof(*_fontIndexTables[TTX_FontDescs[i]->description.using.usingFontID].entity));

        if(TTX_FontDescs[i]->type == TYPE_PRIMITIVE)
        {
            for(j = 0; j < _fontIndexTables[i].size; ++j)
                *(glyphIndexAddr+j) = count + j;
        }
        else if(TTX_FontDescs[i]->type == TYPE_USING)
        {
            memcpy(_fontIndexTables[i].entity,
                   _fontIndexTables[TTX_FontDescs[i]->description.using.usingFontID].entity,
                   _fontIndexTables[TTX_FontDescs[i]->description.using.usingFontID].size*sizeof(*_fontIndexTables[TTX_FontDescs[i]->description.using.usingFontID].entity));

            for(j =0; j < TTX_FontDescs[i]->description.using.number; ++j)
            {
                if(TTX_FontDescs[i]->description.using.elem[j] != TTX_FONTBIN_INDEX_TABLE_ESCAPE_PLACE_HOLDER)
                    _fontIndexTables[i].entity[TTX_FontDescs[i]->description.using.elem[j]] =
                        count + j;
            }
        }
        else if(TTX_FontDescs[i]->type == TYPE_REFERENCE)
        {
            TT_U32 k;

            for(j = 0; j < TTX_FontDescs[i]->description.reference.number; j++)
            {
                for(k = TTX_FontDescs[i]->description.reference.refElems[j].start;
                    k <= TTX_FontDescs[i]->description.reference.refElems[j].end;
                    ++k)
                {
                    _fontIndexTables[i].entity[k] =
                        _fontIndexTables[TTX_FontDescs[i]->description.reference.refElems[j].refFont].entity[k];
                }
            }

            for(j =0; j < TTX_FontDescs[i]->description.using.number; ++j)
            {
                _fontIndexTables[i].entity[TTX_FontDescs[i]->description.using.elem[j]] =
                    count + j;
            }

        }

        count += TTX_FontDescs[i]->glyphNum;
        glyphIndexAddr = glyphIndexAddr + TTX_FontDescs[i]->capacity/**sizeof(*_fontIndexTables[0].entity)*/;
    }

    return (TT_U32)glyphIndexAddr - startingAddr;
}

PRIVATE
void _BuildMaskTable(void)
{
    TT_U32 i;
    TT_U32 multiple_width = (_GetGlyphWidth()+12-1) / 12;
    TT_U32 slotsNeed2MaskOff = MASKTABLE_SIZE(multiple_width) - _GetGlyphWidth();
    TT_U32 windowSize = MASKTABLE_SIZE(multiple_width);
    TT_U8* pWindow = _maskTable;

    memset(_maskTable,
           1,
           MASKTABLE_SIZE(multiple_width));

    for(i = 0; i < slotsNeed2MaskOff; i+=2)
    {
        pWindow[0] = 0;
        if(i > slotsNeed2MaskOff)
            break;

        pWindow[windowSize-1] = 0;
        //shrink the window
        windowSize -= multiple_width * 2;
        pWindow = pWindow + multiple_width;
    }

}

PRIVATE
void _CreateBlockGlyphsFont(void)
{
    TT_U32 multiple_width,
           multiple_height,
           sizeOfOneLine;

    multiple_width = (_GetGlyphWidth()+12-1) / 12;
    multiple_height = _GetGlyphHeight() / 10;
    sizeOfOneLine = _GetOneGlyphSize()/_GetGlyphHeight();

    _BuildMaskTable();

    _CreateBlockGlyphsFontTable((TT_U8*)_PA2VA((MS_U32)_fontG1BlockMosaik),
                                _GetBPP(),
                                _GetOneGlyphSize(),
                                sizeOfOneLine,
                                TT_EngineObj.GetStockFont(TT_STOCK_FONT_G1_MOSAIK),
                                1,
                                12,
                                10,
                                16,
                                96,
                                multiple_width,
                                multiple_height);

    _CreateBlockGlyphsFontTable((TT_U8*)_PA2VA((MS_U32)_fontG1SeparatedBlockMosaik),
                                _GetBPP(),
                                _GetOneGlyphSize(),
                                sizeOfOneLine,
                                TT_EngineObj.GetStockFont(TT_STOCK_FONT_G1_SEPARATED_MOSAIK),
                                1,
                                12,
                                10,
                                16,
                                96,
                                multiple_width,
                                multiple_height);

    _CreateBlockGlyphsFontTable((TT_U8*)_PA2VA((MS_U32)_fontG3Smooth),
                                _GetBPP(),
                                _GetOneGlyphSize(),
                                sizeOfOneLine,
                                TT_EngineObj.GetStockFont(TT_STOCK_FONT_G3_SMOOTH_MOSAIK),
                                1,
                                12,
                                10,
                                16,
                                96,
                                multiple_width,
                                multiple_height);

    multiple_width = _BuildGlyphIndexTable(_PA2VA(_indexTableAddr));

    if(WORKING_FONT_BUFFER_SIZE < ((unsigned) (_indexTableAddr+multiple_width)-_bufferBeginningAddr))
    {
        U8 u8Index=0;
        for(u8Index=0;u8Index<5;u8Index++)
        {
            printf("WORKING_FONT_BUFFER_SIZE is too small(%x,%x).....\n",
                   WORKING_FONT_BUFFER_SIZE,
                   (unsigned)((_indexTableAddr+multiple_width)-_bufferBeginningAddr));
        }
        MDrv_Sys_StopCpu(1);
    }

    //_LoadFont();
}

PRIVATE
void _TransformByQuirkGlyphRules(TTX_FontID* whichTable,
                                   TT_U32* glyphIndex,
                                   int frontGlyphIndex,
                                   int afterGlyphIndex)
{
    int i;
    int tableIndex = *whichTable;

    afterGlyphIndex = afterGlyphIndex;
    for(i = 0; i < TTX_FontDescs[tableIndex]->quirkGlyphTable.recordNum; ++i)
    {
        const quirkGlyphInfo* quirkGlyphRuleInfos =
            &TTX_FontDescs[tableIndex]->quirkGlyphTable.table[i];

        if(quirkGlyphRuleInfos->glyphID == *glyphIndex)
        {
            int j;

            for(j = 0; j < quirkGlyphRuleInfos->rules.ruleNum; ++j)
            {

                const quirkGlyphRuleInfo* ruleInfo =
                    &quirkGlyphRuleInfos->rules.ruleInfoTable[j];

                if( (ruleInfo->type & GUIRK_GLYPH_RLUE_FRONT) &&
                    (frontGlyphIndex == ruleInfo->judgeGlyphIndex))
                {
                    *whichTable = (TTX_FontID)ruleInfo->fontTable;
                    *glyphIndex = ruleInfo->quirkGlyphIndex;
                    return;
                }
            }
            break;
        }
    }
}

PRIVATE
TT_U32 _GetGlyph(TT_Charset_Font whichfont, TT_U32 glyphIndex, int frontGlyphIndex, int afterGlyphIndex)
{
    TTX_FontID whichTable;

    if(whichfont == TT_Charset_Font_G1_block_mosaic)
        return (TT_U32)(_fontG1BlockMosaik + glyphIndex*_GetOneGlyphSize());
    else if(whichfont == TT_Charset_Font_G1_block_mosaic_separated)
        return (TT_U32)(_fontG1SeparatedBlockMosaik + glyphIndex*_GetOneGlyphSize());
    else if(whichfont == TT_Charset_Font_G3_smooth_mosaic_separated ||
            whichfont == TT_Charset_Font_G3_smooth_mosaic)
        return (TT_U32)(_fontG3Smooth + glyphIndex*_GetOneGlyphSize());
    else if(whichfont == TT_Charset_Font_DRCS)
        return (TT_U32)(_fontDRCS + glyphIndex*_GetOneGlyphSize());
    else
    {
        switch(whichfont)
        {
        case TT_Charset_Font_G0_Latin:
            whichTable = LATIN_G0;
            break;
        case TT_Charset_Font_G2_Latin:
            whichTable = LATIN_G2;
            break;
        case TT_Charset_Font_International1:
            whichTable = INTERNATIONAL1;
            break;
        case TT_Charset_Font_International2:
            whichTable = INTERNATIONAL2;
            break;
        case TT_Charset_Font_International3:
            whichTable = INTERNATIONAL3;
            break;
        case TT_Charset_Font_Symbol:
            whichTable = SYMBOL;
            break;
        case TT_Charset_Font_G0_Greek:
            whichTable = GREEK_G0;
            break;
        case TT_Charset_Font_G2_Greek:
            whichTable = GREEK_G2;
            break;
        case TT_Charset_Font_G0_Arabic:
            whichTable = ARABIC_GO;
            break;
        case TT_Charset_Font_G2_Arabic:
            whichTable = ARABIC_G2;
            break;
        case TT_Charset_Font_G0_Hebrew:
            whichTable = HEBREW_G0;
            break;

        case TT_Charset_Font_G0_Farsi:
            whichTable = FARSI_G0;
            break;

        case TT_Charset_Font_G2_Farsi:
            whichTable = FARSI_G2;
            break;

        case TT_Charset_Font_G0_Cyrillic1:
            whichTable = CYRILLIC_G0_OPT1;
            break;

        case TT_Charset_Font_G0_Cyrillic2:
            whichTable = CYRILLIC_G0_OPT2;
            break;

        case TT_Charset_Font_G0_Cyrillic3:
            whichTable = CYRILLIC_G0_OPT3;
            break;

        case TT_Charset_Font_G2_Cyrillic:
            whichTable = CYRILLIC_G2;
            break;

        case TT_Charset_Font_Arabic_Extention:
            whichTable = ARABIC_EXTENTION;
            break;

        default:
            whichTable = LATIN_G0;
            break;
        }

        _TransformByQuirkGlyphRules(&whichTable,
                                    &glyphIndex,
                                    frontGlyphIndex,
                                    afterGlyphIndex);

        return _fontInfo.glyph_addr +
               _fontIndexTables[whichTable].entity[glyphIndex]*_GetOneGlyphSize();

    }

    return 0;
}


const TT_IBitmapFontCharsMan TT_MStarFontCharsMan_ =
{
    _Init,
    _GetGlyphWidth,
    _GetGlyphHeight,
    _CreateDRCS,
    _GetBPP,
    _GetPitch,
    _GetGlyph
};

#endif

