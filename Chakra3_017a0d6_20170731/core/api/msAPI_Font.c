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
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (��MStar Confidential Information��) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
/// @file msAPI_Font.h
/// This file includes MStar application interface for FONT.
/// @brief API for font handling
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////

#define MSAPI_FONT_C

#include <stdio.h>
#include <string.h> //for memcpy()

#include "Board.h"
#include "hwreg.h"
#include "datatype.h"
#include "ms_vectorfont_if.h"

#include "drvSERFLASH.h"
#include "drvCPU.h"
#include "msAPI_MailBox.h"
#include "debug.h"
#include "msAPI_DrvInit.h"

#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"


#include "msAPI_Font.h"
#include "msAPI_MIU.h"
#include "msAPI_OSD_Resource.h"
#include "msAPI_OSD.h"
#include "msAPI_BDMA.h"
#if MHEG5_ENABLE
#include "MApp_Key.h"
#endif
#include "msAPI_Global.h"

#if VECTOR_FONT_ENABLE
#include "msAPI_Timer.h"

#if DYNAMIC_VECTOR_FONT_ENABLE
#include "msAPI_Font_Dynamic_MVF.h"
#endif

#include "drvMBX.h"
#endif

//==========================================================================

#define DEBUG_API_LOAD_FONT(x)  //x

#if VECTOR_FONT_ENABLE

#define APIMVF_DBG(y)   //y
#define APIMVF_DBG_TIME_USAGE 1

#define MVF_MAX_COMMAND_WORDS (1024 / sizeof(U32))

//MVF command memory address in DRAM
static U32 *fontaddr_mailbox;
static U32 mvf_font_word_count;
static U32 fontaddr;
static U32 BMPfontaddr;


#elif DYNAMIC_VECTOR_FONT_ENABLE //=========================================

#include "msAPI_Font_Dynamic_MVF.h"

#define APIMVF_DBG(y) //y
#define APIMVF_DBG_TIME_USAGE 1

#define MVF_MAX_COMMAND_WORDS (2048 / sizeof(U32))

//MVF command memory address in DRAM
static U32 *fontaddr_mailbox = (U32 *)GE_ADDR_ALIGNMENT(((FONT_START_MEMORY_TYPE & MIU1) ? (FONT_START_ADR | MIU_INTERVAL) : (FONT_START_ADR)));
static U32 mvf_font_word_count; //memory usage in MVF_MAX_COMMAND_WORDS
static U32 fontaddr = GE_ADDR_ALIGNMENT(((FONT_START_MEMORY_TYPE & MIU1) ? (FONT_START_ADR | MIU_INTERVAL) : (FONT_START_ADR))) + GE_ADDR_ALIGNMENT(MVF_MAX_COMMAND_WORDS * 4);

#else //===================================================================

  #if (BRAZIL_CC==0)
    static U32 s_u32FontPhyAddr = GE_ADDR_ALIGNMENT(((FONT_START_MEMORY_TYPE & MIU1) ? (FONT_START_ADR | MIU_INTERVAL) : (FONT_START_ADR)));
  #endif

#endif //VECTOR_FONT_ENABLE


OSDSRC_GLYPH_BBOX  g_SRAM_BBox;

void GET_Y_BBOX_FROM_SDRAM_TO_SRAM(U32 sdram_addr, U16 char_index)
{
    U8 *pBBox;

    pBBox = (U8 *)_PA2VA((U32)((sdram_addr) + 2 + ((char_index) << 2)));
    g_SRAM_BBox.u8Y0 = pBBox[0];
    g_SRAM_BBox.u8Height = pBBox[1];
}

/******************************************************************************/
/// API for font header::
/// Read font header on flash
/// @param u16FontBinID \b IN Font ID in the packed binary
/// @param pFontBinHeader \b IN Pointer to returning FONT_BIN_HEADER
/// @param pu32BinBaseAddr \b IN Pointer to returning base address of the specified font ID
/// @return BOOLEAN:
///- TRUE: Success
///- FALSE: Fail
/******************************************************************************/
bool msAPI_Font_ReadBinHeader(U16 u16FontBinID, FONT_BIN_HEADER *pFontBinHeader, U32 *pu32BinBaseAddr)  //20091127EL
{
    BININFO BinInfo;
    BOOLEAN bResult;
    U32 u32LoadBin_Dst;
    U32 u32LoadBin_Dec;
    U32 u32LoadBin_Tmp;


#if (BLOADER && ((CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)))
    u32LoadBin_Dst = MAD_BASE_BUFFER_ADR; // Use Audio
    u32LoadBin_Dec = MAD_BASE_BUFFER_ADR + 0x100000;
    u32LoadBin_Tmp = MAD_BASE_BUFFER_ADR + 0x200000;
#elif( /*(CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA)&&*/(MEMORY_MAP == MMAP_32MB) )
    u32LoadBin_Dst = POOL_BUFFER_ADR;
    u32LoadBin_Dec = MAD_JPEG_INTERBUFF_ADR;
    u32LoadBin_Tmp = MAD_JPEG_INTERBUFF_ADR + 0x200000;
#elif( CHIP_FAMILY_TYPE == CHIP_FAMILY_MELODY )
    if (IsDTVInUse())
    {
        u32LoadBin_Dst = AEON_MM_MEM_ADR;
        u32LoadBin_Dec = AEON_MM_MEM_ADR + 0x100000;
        u32LoadBin_Tmp = AEON_MM_MEM_ADR + 0x200000;
    }
    else
    {
        u32LoadBin_Dst = ((POOL_BUFFER_ADR & MIU1) ? (POOL_BUFFER_ADR | MIU_INTERVAL) : (POOL_BUFFER_ADR));
        u32LoadBin_Dec = (((POOL_BUFFER_ADR+BUF_FOR_DECOMPRESS_OFFSET1) & MIU1) ? ((POOL_BUFFER_ADR+BUF_FOR_DECOMPRESS_OFFSET1) | MIU_INTERVAL) : (POOL_BUFFER_ADR+BUF_FOR_DECOMPRESS_OFFSET1));
        u32LoadBin_Tmp = (((POOL_BUFFER_ADR+BUF_FOR_DECOMPRESS_OFFSET2) & MIU1) ? ((POOL_BUFFER_ADR+BUF_FOR_DECOMPRESS_OFFSET2) | MIU_INTERVAL) : (POOL_BUFFER_ADR+BUF_FOR_DECOMPRESS_OFFSET2));
    }
#else
    u32LoadBin_Dst = ((POOL_BUFFER_ADR & MIU1) ? (POOL_BUFFER_ADR | MIU_INTERVAL) : (POOL_BUFFER_ADR));
    u32LoadBin_Dec = (((POOL_BUFFER_ADR+BUF_FOR_DECOMPRESS_OFFSET1) & MIU1) ? ((POOL_BUFFER_ADR+BUF_FOR_DECOMPRESS_OFFSET1) | MIU_INTERVAL) : (POOL_BUFFER_ADR+BUF_FOR_DECOMPRESS_OFFSET1));
    u32LoadBin_Tmp = (((POOL_BUFFER_ADR+BUF_FOR_DECOMPRESS_OFFSET2) & MIU1) ? ((POOL_BUFFER_ADR+BUF_FOR_DECOMPRESS_OFFSET2) | MIU_INTERVAL) : (POOL_BUFFER_ADR+BUF_FOR_DECOMPRESS_OFFSET2));
#endif


    BinInfo.B_ID = u16FontBinID;
    msAPI_MIU_Get_BinInfo(&BinInfo, &bResult);
    if ( bResult != PASS)
    {
        printf("\nError: Get bin info failed!\n");
        return FALSE;
    }

    if( SUCCESS == MDrv_DMA_LoadBin(&BinInfo, _PA2VA(u32LoadBin_Dst), _PA2VA(u32LoadBin_Dec), _PA2VA(u32LoadBin_Tmp) ) )
    {
        //printf(" CRC10=0x%X\n", msAPI_CRC_Cal( (U8*)_PA2VA(u32LoadBin_Dst), 49518) );

        //*pIsBinComp = TRUE;
        memcpy(pFontBinHeader,(void *)_PA2VA(u32LoadBin_Dst), sizeof(FONT_BIN_HEADER));

        *pu32BinBaseAddr = u32LoadBin_Dst;
    }
    else
    {
        return FALSE;
    }

    return (pFontBinHeader->u32Tag == FONT_HEADER_TAG);
}

/******************************************************************************/
/// API for font header::
/// Get the size of one line in byte
/// @param pFontBinHeader \b IN Pointer to FONT_BIN_HEADER
/// @return U8: Line bytes
/******************************************************************************/
U8 msAPI_Font_GetLineBytes(const FONT_BIN_HEADER *pFontBinHeader)
{
    U8  u8PitchBits = pFontBinHeader->u32Pitch * 8;
    return ((pFontBinHeader->u32Width+u8PitchBits-1)/u8PitchBits) * pFontBinHeader->u32Pitch * pFontBinHeader->u32BPP;
}

/******************************************************************************/
/// API for font header::
/// Get the size of one character glyph in byte including possible bottom paddings for alignment
/// @param pFontBinHeader \b IN Pointer to FONT_BIN_HEADER
/// @return U16: Character glyph bytes
/******************************************************************************/
U16 msAPI_Font_GetCharGlyphBytes(const FONT_BIN_HEADER *pFontBinHeader)
{
    return (U16)pFontBinHeader->u32CharGlyphBytes;
}

/******************************************************************************/
/// API for font header::
/// Get the size in byte of the uncompressed font table
/// @param pFontBinHeader \b IN Pointer to FONT_BIN_HEADER
/// @return U8: Font table bytes
/******************************************************************************/
U32 msAPI_Font_GetFontGlyphBytes(const FONT_BIN_HEADER *pFontBinHeader)
{
    return msAPI_Font_GetCharGlyphBytes(pFontBinHeader) * pFontBinHeader->u32CharNum;
}

/******************************************************************************/
/// API for MIU Load Font::
/// Decompress font table from flash to SDRAM
/// @param u16FontBinID \b IN Font ID in the packed binary
/// @param u32DstAddr \b IN Destination address on SDRAM.
/// @param pFontBinHeader \b IN Pointer to returning FONT_BIN_HEADER
/// @param pFontSdramReport \b IN Pointer to ST_LOAD_FONT_SDRAM_REPORT to keep SDRAM information
/// @return BOOLEAN:
/// - TRUE: Success
/// - FALSE: Fail
/******************************************************************************/
bool msAPI_Font_LoadFlashFont_Decompress (
    U16 u16FontBinID,
    U32 u32DstAddr,
    FONT_BIN_HEADER *pFontBinHeader,
    ST_LOAD_FONT_SDRAM_REPORT *pFontSdramReport
    )
{
    U32 u32FlashAddr, u32BinBaseAddr;
    U16 u16;
    U16 u16LineBytes, u16CharGlyphBytes;
    int i;
    U8 offset_align;
    U8 u8shift;
    U32 size_bak;

    //U32 t0;

    //t0 = msAPI_Timer_GetTime0();

    //printf("msAPI_Font_LoadFlashFont_Decompress(u32DstAddr=0x%X)\n", u32DstAddr);


    pFontSdramReport->u32StartAddr = u32DstAddr;
    pFontSdramReport->u32SdramLen = 0;

    if ( !msAPI_Font_ReadBinHeader(u16FontBinID, pFontBinHeader, &u32BinBaseAddr) )  //20091127EL
    {
        return FALSE;
    }

    // Load bbox info to SDRAM
    if (pFontBinHeader->u32BBoxOffset != 0)
    {
        U32 u32Len = pFontBinHeader->u32CharNum * 4;
        u32Len = ((u32Len+(MIU_ALIGN_UNIT-1))/MIU_ALIGN_UNIT)*MIU_ALIGN_UNIT;

        memcpy((void*)_PA2VA(u32DstAddr),(void*)_PA2VA(u32BinBaseAddr + pFontBinHeader->u32BBoxOffset), u32Len);

        pFontSdramReport->u32BBoxAddr = u32DstAddr;
        u32DstAddr += u32Len;
        pFontSdramReport->u32SdramLen += u32Len;
    }
    else
    {
        pFontSdramReport->u32BBoxAddr = 0;
    }

    // Load codemap to SDRAM
    if (pFontBinHeader->u32CodemapBlockNum != 0 && pFontBinHeader->u32CodemapOffset != 0)
    {
        U32 u32Len = pFontBinHeader->u32CodemapBlockNum * sizeof(CHAR_CODEMAP_BLOCK);    // each block contains 6 bytes. 2 bytes for start and 2 for end.
        u32Len = ((u32Len+(MIU_ALIGN_UNIT-1))/MIU_ALIGN_UNIT)*MIU_ALIGN_UNIT;

        memcpy((void*)_PA2VA(u32DstAddr),(void*)_PA2VA(u32BinBaseAddr + pFontBinHeader->u32CodemapOffset),u32Len);
        //memcpy((void*)_PA2VA(u32DstAddr),(void*)_PA2VA(u32BinBaseAddr + pFontBinHeader->u32BBoxOffset), u32Len);

        pFontSdramReport->u32CodemapAddr = u32DstAddr;
        u32DstAddr += u32Len;
        pFontSdramReport->u32SdramLen += u32Len;
    }
    else
    {
        pFontBinHeader->u32CodemapBlockNum = 0;
        pFontBinHeader->u32CodemapOffset = 0;

        pFontSdramReport->u32CodemapAddr = 0;
    }

    // Below load glyph data to SDRAM
    u32DstAddr = GE_ADDR_ALIGNMENT(u32DstAddr);
    pFontSdramReport->u32GlyphAddr = u32DstAddr;
    u16LineBytes = msAPI_Font_GetLineBytes(pFontBinHeader);
    u16CharGlyphBytes = msAPI_Font_GetCharGlyphBytes(pFontBinHeader);

    u32FlashAddr = u32BinBaseAddr + (U32)pFontBinHeader->u32FontGlyphOffset;

    switch (pFontBinHeader->u32Compression)
    {
        case FONT_COMPRESSION_NONE:
            memcpy((void*)_PA2VA(u32DstAddr), (void*)_PA2VA(u32FlashAddr), msAPI_Font_GetFontGlyphBytes(pFontBinHeader));
            break;

        case FONT_COMPRESSION_BOUND_RECTANGLE:
            if (pFontSdramReport->u32BBoxAddr == 0)
            {
                return FALSE;
            }

            // Clear entire buffer to 0.
            MDrv_GE_ClearFrameBuffer( u32DstAddr, msAPI_Font_GetFontGlyphBytes(pFontBinHeader), 0);

#if ENABLE_DMP
            //MDrv_Sys_PushXdataWindow1Base();
#endif
            for (u16=0; u16<pFontBinHeader->u32CharNum; u16++)
            {
                GET_Y_BBOX_FROM_SDRAM_TO_SRAM(pFontSdramReport->u32BBoxAddr, u16);

                if (g_SRAM_BBox.u8Height != 0)
                {
                    U16 offset = g_SRAM_BBox.u8Y0 * u16LineBytes;

                    U16 copysize = (g_SRAM_BBox.u8Height) * u16LineBytes;

                    size_bak =copysize;

#if 1
                    if( (u32DstAddr + offset)%MIU_ALIGN_UNIT != 0)
                    {
                         offset_align = 1;
                         u8shift = offset - (offset/MIU_ALIGN_UNIT)*MIU_ALIGN_UNIT;
                         copysize += u8shift;
                         offset = (offset/MIU_ALIGN_UNIT)*MIU_ALIGN_UNIT;
                    }
                    else {
                        u8shift = 0;
                        offset_align = 0;
                    }

#endif

                    //printf("u8Y0 = %02bx, u8Height = %02bx\n", g_SRAM_BBox.u8Y0, g_SRAM_BBox.u8Height);

                     memcpy((void *)_PA2VA(u32DstAddr + offset),(void *)_PA2VA(u32FlashAddr-u8shift),copysize);

                     i = ((copysize+(MIU_ALIGN_UNIT-1))/MIU_ALIGN_UNIT)*MIU_ALIGN_UNIT - copysize;
                    if( i != 0)
                    {
                        while(i)
                        {

                            *(U8 *)(_PA2VA(u32DstAddr + offset + copysize + i - 1)) = 0;
                            i--;
                        }
                    }

#if 1
                    if(offset_align)
                    {
                        i = 0;
                        while(u8shift)
                        {
                            *(U8 *)(_PA2VA(u32DstAddr + offset + i))= 0;
                            i++;
                            u8shift--;
                        }

                    }
#endif
                    copysize = size_bak;
                    u32FlashAddr += copysize;
                }
                u32DstAddr += u16CharGlyphBytes;
            }
#if ENABLE_DMP
            //MDrv_Sys_PopXdataWindow1Base();
#endif
            break;

        default:
//            msWarning(ERR_FONT_WRONG_FORMAT);
            return FALSE;
    }

    // Note that u32FontGlyphBytes may indicate the size of compressed data.
    // So need to update the actual data size here.
    pFontBinHeader->u32FontGlyphBytes = msAPI_Font_GetFontGlyphBytes(pFontBinHeader);
    pFontSdramReport->u32SdramLen += pFontBinHeader->u32FontGlyphBytes;

    //printf("Load font: %ld ms\n", msAPI_Timer_DiffTimeFromNow(t0));
    return TRUE;
}

BOOLEAN msAPI_Font_LoadSDRAMFont_Decompress(U32 srcAddr, U32 u32DstAddr, FONT_BIN_HEADER *pFontBinHeader, ST_LOAD_FONT_SDRAM_REPORT *pFontSdramReport)
{
    U32 u32SDRAMAddr;
    U16 u16;
    U16 u16LineBytes, u16CharGlyphBytes;
    int i;
    U8 offset_align;
    U8 u8shift;
    U32 size_bak;

    pFontSdramReport->u32StartAddr = u32DstAddr;
    pFontSdramReport->u32SdramLen = 0;

    MApi_BDMA_Copy(srcAddr,XD2PHY(pFontBinHeader),sizeof(FONT_BIN_HEADER),MIU_SDRAM2SDRAM);

    // Load bbox info to SDRAM
    if (pFontBinHeader->u32BBoxOffset != 0)
    {
        U32 u32Len = pFontBinHeader->u32CharNum * 4;
        u32Len = ((u32Len+(MIU_ALIGN_UNIT-1))/MIU_ALIGN_UNIT)*MIU_ALIGN_UNIT;
        MApi_BDMA_Copy(srcAddr+pFontBinHeader->u32BBoxOffset, u32DstAddr, u32Len,MIU_SDRAM2SDRAM);
        pFontSdramReport->u32BBoxAddr = u32DstAddr;
        u32DstAddr += u32Len;
        pFontSdramReport->u32SdramLen += u32Len;
    }
    else
    {
        pFontSdramReport->u32BBoxAddr = 0;
    }

    // Load codemap to SDRAM
    if (pFontBinHeader->u32CodemapBlockNum != 0 && pFontBinHeader->u32CodemapOffset != 0)
    {
        U32 u32Len = pFontBinHeader->u32CodemapBlockNum * sizeof(CHAR_CODEMAP_BLOCK);    // each block contains 6 bytes. 2 bytes for start and 2 for end.
        u32Len = ((u32Len+(MIU_ALIGN_UNIT-1))/MIU_ALIGN_UNIT)*MIU_ALIGN_UNIT;
        MApi_BDMA_Copy(srcAddr+pFontBinHeader->u32CodemapOffset, u32DstAddr, u32Len,MIU_SDRAM2SDRAM);
        pFontSdramReport->u32CodemapAddr = u32DstAddr;
        u32DstAddr += u32Len;
        pFontSdramReport->u32SdramLen += u32Len;
    }
    else
    {
        pFontBinHeader->u32CodemapBlockNum = 0;
        pFontBinHeader->u32CodemapOffset = 0;

        pFontSdramReport->u32CodemapAddr = 0;
    }

    // Below load glyph data to SDRAM
    u32DstAddr = GE_ADDR_ALIGNMENT(u32DstAddr);
    pFontSdramReport->u32GlyphAddr = u32DstAddr;
    u16LineBytes = msAPI_Font_GetLineBytes(pFontBinHeader);
    u16CharGlyphBytes = msAPI_Font_GetCharGlyphBytes(pFontBinHeader);

    u32SDRAMAddr=srcAddr+(U32)pFontBinHeader->u32FontGlyphOffset;


    switch (pFontBinHeader->u32Compression)
    {
        case FONT_COMPRESSION_NONE:

            MApi_BDMA_Copy(u32SDRAMAddr,u32DstAddr, msAPI_Font_GetFontGlyphBytes(pFontBinHeader),MIU_SDRAM2SDRAM);
            break;

        case FONT_COMPRESSION_BOUND_RECTANGLE:
        #if 0
            if (pFontBinHeader->u32BPP == 2 && u8TargetBPP == FONT_TARGET_BPP_I2_VARIANT)
            {
                if (!msAPI_MIU_LoadSDRAMFont_I2_To_3_I1(pFontBinHeader, u32SDRAMAddr, u32DstAddr, pFontSdramReport->u32BBoxAddr))
                {
                    return FALSE;
                }
            }
            else
            {
                if (pFontSdramReport->u32BBoxAddr == 0)
                {
                    return FALSE;
                }
                // Clear entire buffer to 0.
                MDrv_GE_ClearFrameBuffer(u32DstAddr, msAPI_Font_GetFontGlyphBytes(pFontBinHeader), 0);

                for (u16=0; u16<pFontBinHeader->u32CharNum; u16++)
                {
                    GET_Y_BBOX_FROM_SDRAM_TO_SRAM(pFontSdramReport->u32BBoxAddr, u16);

                    if (g_SRAM_BBox.u8Height != 0)
                    {
                        U16 offset = g_SRAM_BBox.u8Y0 * u16LineBytes;
                        U16 copysize = g_SRAM_BBox.u8Height * u16LineBytes;

                        MApi_BDMA_Copy(u32SDRAMAddr, u32DstAddr+ offset, copysize, MIU_SDRAM2SDRAM);

                        u32SDRAMAddr += copysize;
                    }
                    u32DstAddr += u16CharGlyphBytes;
                }
            }
            break;

        #endif

            if (pFontSdramReport->u32BBoxAddr == 0)
            {
                return FALSE;
            }

            // Clear entire buffer to 0.
            MDrv_GE_ClearFrameBuffer( u32DstAddr, msAPI_Font_GetFontGlyphBytes(pFontBinHeader), 0);

            for (u16=0; u16<pFontBinHeader->u32CharNum; u16++)
            {
                GET_Y_BBOX_FROM_SDRAM_TO_SRAM(pFontSdramReport->u32BBoxAddr, u16);

                if (g_SRAM_BBox.u8Height != 0)
                {
                    U16 offset = g_SRAM_BBox.u8Y0 * u16LineBytes;

                    U16 copysize = (g_SRAM_BBox.u8Height) * u16LineBytes;

                    size_bak =copysize;

#if 1
                    if( (u32DstAddr + offset)%MIU_ALIGN_UNIT != 0)
                    {
                         offset_align = 1;
                         u8shift = offset - (offset/MIU_ALIGN_UNIT)*MIU_ALIGN_UNIT;
                         copysize += u8shift;
                         offset = (offset/MIU_ALIGN_UNIT)*MIU_ALIGN_UNIT;
                    }
                    else {
                        u8shift = 0;
                        offset_align = 0;
                    }

#endif

                    //printf("u8Y0 = %02bx, u8Height = %02bx\n", g_SRAM_BBox.u8Y0, g_SRAM_BBox.u8Height);
//                    MDrv_MIU_XCopy(MCPY_LOADFONT, u32SDRAMAddr-u8shift, u32DstAddr + offset, ((copysize +(MIU_ALIGN_UNIT-1))/MIU_ALIGN_UNIT)*MIU_ALIGN_UNIT   );
                    MApi_BDMA_Copy(u32SDRAMAddr-u8shift,  u32DstAddr + offset, ((copysize +(MIU_ALIGN_UNIT-1))/MIU_ALIGN_UNIT)*MIU_ALIGN_UNIT ,MIU_SDRAM2SDRAM);
                     i = ((copysize+(MIU_ALIGN_UNIT-1))/MIU_ALIGN_UNIT)*MIU_ALIGN_UNIT - copysize;
                    if( i != 0)
                    {
                        while(i)
                        {
                            *(U8 *)(u32DstAddr + offset + copysize + i - 1) = 0;
                            i--;
                        }
                    }

#if 1
                    if(offset_align)
                    {
                        i = 0;
                        while(u8shift)
                        {
                            *(U8 *)(u32DstAddr + offset + i) = 0;
                            i++;
                            u8shift--;
                        }

                    }
#endif
                    copysize = size_bak;
                    u32SDRAMAddr += copysize;
                }
                u32DstAddr += u16CharGlyphBytes;
            }
            break;

        default:
//            msWarning(ERR_FONT_WRONG_FORMAT);
            return FALSE;
    }

    // Note that u32FontGlyphBytes may indicate the size of compressed data.
    // So need to update the actual data size here.
    pFontBinHeader->u32FontGlyphBytes = msAPI_Font_GetFontGlyphBytes(pFontBinHeader);
    pFontSdramReport->u32SdramLen += pFontBinHeader->u32FontGlyphBytes;

    //printf("Load font: %ld ms\n", msAPI_Timer_DiffTimeFromNow(t0));
    return TRUE;
}

#if (0)

/******************************************************************************/
/// API for MIU Reload Font::
/// Reload a font table from flash to the same SDRAM space that previously allocated.
/// @param handle \b IN Font handle
/// @param u16FontBinID \b IN Font ID in the packed binary
/******************************************************************************/
void msAPI_Font_ReloadFlashFontToSDRAM(FONTHANDLE handle, U16 u16FontBinID)
{
    FONT_INFO finfo;
    FONT_BIN_HEADER FontBinHeader;
    ST_LOAD_FONT_SDRAM_REPORT FontSdramInfo;

    MDrv_GE_GetFontInfo(handle, &finfo);

    if (!msAPI_Font_LoadFlashFont_Decompress(u16FontBinID, finfo.start_addr, &FontBinHeader, &FontSdramInfo))
    {
        return;
    }
}
#endif

static void (*_pFnLoad)(U8);
void msAPI_Font_RegisterLoadFontFunction(void (*pFnLoadFont)(U8))
{
    _pFnLoad = pFnLoadFont;
}

#if VECTOR_FONT_ENABLE
void msAPI_Font_MVF_PrintInfo(void)
{
    printf("Vector Font info:\n");

    printf(" mvf_font_word_count=%u\n", mvf_font_word_count);

    U8 i;
    printf(" fontaddr_mailbox=0x%X\n", fontaddr_mailbox);

    for( i = 0; i <= (mvf_font_word_count+1); ++ i )
    {
        printf(" fontaddr_mailbox[%u]=0x%X\n", i, fontaddr_mailbox[i]);
    }

    printf(" fontaddr=0x%X\n", fontaddr);
    printf(" BMPfontaddr=0x%X\n", BMPfontaddr);
}

//Load Font:
//   u32MVFStartAddr, u32MVFEndAddr

//Done Font:
//   (no parameter)

//Make Font:
//////////////INPUT///////////
//   u32OutputStartAddr;
//   u32OutputBitmapSize    //loop to zero                       //skip if size=0
//      u32OutputFontID                            ///for GE load font id
//      u32OutputBitmapBPP
//      u32OutputBitmapWidth                      ///< Width in pixels of a font
//      u32OutputBitmapHeight                     ///< Height in pixels of a font
//      u32OutputUnicodeFrom,u32OutputUnicodeTo  //loop to (0, 0)
//////////////OUTPUT///////////
//   u32OutputEndAddr;
//   u32OutputBitmapSize    //loop to zero                       //skip if size=0
//      u32OutputFontID                            ///for GE load font id
//      u32OutputBitmapBPP
//      u32OutputBitmapWidth                      ///< Width in pixels of a font
//      u32OutputBitmapHeight                     ///< Height in pixels of a font
//      u32BBoxAddr                               ///< Offset of BBox information
//      u32CodemapAddr                            ///< Offset of codemap block data. Each codemap block is a tuple of(start code, end code, start index)
//      u32GlyphAddr                              ///< Offset of glyph data
//      u32CharNum                               ///< Character count
//      u32CodemapBlockNum                       ///< Number of codemap block.
//      u32CharGlyphBytes                       ///< Size of one char glyph including possible paddings for alignment

#if (!COPRO_MVF_ENABLE)
BOOLEAN msAPI_Font_MVF_LoadFlashFontToSDRAM(U16 u16FontBinID)
{
    BININFO   BinInfo;
    U32 u32Len;
    //U16 u16TryCount;
    BOOLEAN bResult;

    DEBUG_LOAD_VF(printf("msAPI_Font_MVF_LoadFlashFontToSDRAM(u16FontBinID=0x%X) at %u\n", u16FontBinID, MsOS_GetSystemTime()););


    BinInfo.B_ID = u16FontBinID;

    msAPI_MIU_Get_BinInfo(&BinInfo, &bResult) ;
    if (bResult != PASS)
    {
        msWarning(ERR_FONT_BIN_NOT_FOUND);
        return FALSE;
    }

    //printf("msAPI_MIU_LoadFlashFont_MVF: addr=%ld, len=%ld\n",
        //BinInfo.B_FAddr, BinInfo.B_Len);

    u32Len = (BinInfo.B_Len+(MIU_ALIGN_UNIT-1UL)) & ~(MIU_ALIGN_UNIT-1UL);

    DEBUG_LOAD_VF( printf("fontaddr=0x%X\n", fontaddr); );

    mvf_font_word_count = 0;
    fontaddr_mailbox[mvf_font_word_count+0] = fontaddr;
    //fontaddr_mailbox[mvf_font_word_count+1] = fontaddr + u32Len;
    //fontaddr_mailbox[mvf_font_word_count+1] = fontaddr + 277032;

//20100106EL
    if (SUCCESS == MDrv_DMA_LoadBin(&BinInfo, fontaddr,
    _PA2VA(((POOL_BUFFER_ADR+BUF_FOR_DECOMPRESS_OFFSET1) & MIU1) ? ((POOL_BUFFER_ADR+BUF_FOR_DECOMPRESS_OFFSET1) | MIU_INTERVAL) : (POOL_BUFFER_ADR+BUF_FOR_DECOMPRESS_OFFSET1)),
    _PA2VA(((POOL_BUFFER_ADR+BUF_FOR_DECOMPRESS_OFFSET2) & MIU1) ? ((POOL_BUFFER_ADR+BUF_FOR_DECOMPRESS_OFFSET2) | MIU_INTERVAL) : (POOL_BUFFER_ADR+BUF_FOR_DECOMPRESS_OFFSET2))))
    {
        switch(BinInfo.B_IsComp)
        {
        case LZSS_COMPRESS:
        case MS_COMPRESS:
        case MS_COMPRESS7:
            //printf("~~1~~  MS_COMPRESS\n");
            //printf("~^~^~  BinInfo.B_Len = %d\n", BinInfo.B_Len);
            fontaddr_mailbox[mvf_font_word_count+1] = fontaddr + GE_ALIGNED_VALUE(BinInfo.B_Len,8);
            break;
        default:
            //printf("~~2~~  NO COMPRESS\n");
            fontaddr_mailbox[mvf_font_word_count+1] = fontaddr + u32Len;
            MApi_BDMA_XCopy(MCPY_LOADFONT, BinInfo.B_FAddr, _VA2PA(fontaddr), u32Len);
            break;
        }

        MsOS_FlushMemory();
    }
    else
    {
        printf("\nError: Load mvf bin failed\n");
        return FALSE;
    }

    DEBUG_LOAD_VF( msAPI_Font_MVF_PrintInfo(); );

    Chakra_MailBox[0].u8Param[0] = ((U32)fontaddr_mailbox&0xFF000000) >> 24;
    Chakra_MailBox[0].u8Param[1] = ((U32)fontaddr_mailbox&0x00FF0000) >> 16;
    Chakra_MailBox[0].u8Param[2] = ((U32)fontaddr_mailbox&0x0000FF00) >> 8;
    Chakra_MailBox[0].u8Param[3] = ((U32)fontaddr_mailbox&0x000000FF) ;

    DEBUG_LOAD_VF(printf("Call ms_MVF_LoadFont() at %u\n", MsOS_GetSystemTime()););

    ms_MVF_LoadFont();

    return TRUE;
}

void msAPI_Font_MVF_AddBitmapSize(
        U16 font_id,
        U8 output_bpp, U8 output_size,
        U8 output_width, U8 output_height,
        U16* unicode_from, U16* unicode_to)
{
    U16 idx;

    DEBUG_LOAD_VF(printf("msAPI_Font_MVF_AddBitmapSize(font_id=%u) at %u\n", font_id, MsOS_GetSystemTime()););

    DEBUG_LOAD_VF(printf("output_bpp=%u\n", output_bpp););
    DEBUG_LOAD_VF(printf("output_size=%u\n", output_size););
    DEBUG_LOAD_VF(printf("output_width=%u, output_height=%u\n", output_width, output_height););

    if ( mvf_font_word_count >=     MVF_MAX_COMMAND_WORDS)
    {
        msWarning(ERR_FONT_OUT_OF_BUFFER);
        return;
    }
    if ( unicode_from == 0 || unicode_to == 0 )
    {
        msWarning(ERR_FONT_WRONG_FORMAT);
        return;
    }

    //send to AEON... parameters...
    if ( mvf_font_word_count == 0 )
    {
        fontaddr_mailbox[mvf_font_word_count++] = fontaddr; //u32OutputStartAddr
    }

    fontaddr_mailbox[mvf_font_word_count++] = output_size; //   u32OutputBitmapSize    //loop to zero                       //skip if size=0
    fontaddr_mailbox[mvf_font_word_count++] = font_id; //      u32OutputFontID                            ///for GE load font id
    fontaddr_mailbox[mvf_font_word_count++] = output_bpp; //      u32OutputBitmapBPP
    fontaddr_mailbox[mvf_font_word_count++] = output_width;//      u32OutputBitmapWidth                      ///< Width in pixels of a font
    fontaddr_mailbox[mvf_font_word_count++] = output_height;

    for (idx = 0; ; idx++)
    {
        fontaddr_mailbox[mvf_font_word_count++] = unicode_from[idx];
        fontaddr_mailbox[mvf_font_word_count++] = unicode_to[idx];
        if (unicode_from[idx] == 0 && unicode_to[idx] == 0)
        {
            break;
        }
        DEBUG_LOAD_VF(printf("unicode_from[%u]=%u, unicode_to[%u]=%u\n", idx, unicode_from[idx], idx, unicode_to[idx]); );
    }

    DEBUG_LOAD_VF( msAPI_Font_MVF_PrintInfo(); );

}
#if 0
void msAPI_Font_MVF_StartGenerateBitmaps(void)
{
    if ( mvf_font_word_count == 0 )
    {
        msWarning(ERR_FONT_GENERIC_ERROR); //no parameter....
        return;
    }
    if ( mvf_font_word_count >=     MVF_MAX_COMMAND_WORDS)
    {
        msWarning(ERR_FONT_OUT_OF_BUFFER);
        return;
    }

    fontaddr_mailbox[mvf_font_word_count++] = 0; //terminal zero

    if (MDrv_CheckMailBoxReady())
    {
        MailBoxPara.u8CmdClass      = MB_CLASS_MVF;
        MailBoxPara.u8CmdIdx        = MB_MVF_CMD_GENERATE_BITMAP;
        MailBoxPara.ParamCnt        = 0x04;
        MailBoxPara.CMDType         = MB_CMD_TYPE_DEFAULT;
        MailBoxPara.u8Param[0]      = (fontaddr_mailbox&0xFF000000) >> 24;
        MailBoxPara.u8Param[1]      = (fontaddr_mailbox&0x00FF0000) >> 16;
        MailBoxPara.u8Param[2]      = (fontaddr_mailbox&0x0000FF00) >> 8;
        MailBoxPara.u8Param[3]      = (fontaddr_mailbox&0x000000FF) ;
        MDrv_SendMailBoxMsg();

        mvf_running = TRUE;
        //printf("===MApp_MediaPlayer_LoadFont: send command done===\n");
    }
    else
    {
        //printf("===MApp_MediaPlayer_LoadFont: send command error===\n");
        msWarning(ERR_FONT_GENERIC_ERROR);
        return;
    }

    //NOTE: non-blocking!!!
    //while( msAPI_ProcessMailBox() != MB_RETURN_MVF_DONE )
    //Drv_Timer_Delayms(3);

}
#else
void msAPI_Font_MVF_StartGenerateBitmaps(void)
{
    DEBUG_LOAD_VF(printf("msAPI_Font_MVF_StartGenerateBitmaps() at %u\n", MsOS_GetSystemTime()););

    if ( mvf_font_word_count == 0 )
    {
        msWarning(ERR_FONT_GENERIC_ERROR); //no parameter....
        return;
    }
    if ( mvf_font_word_count >=     MVF_MAX_COMMAND_WORDS)
    {
        msWarning(ERR_FONT_OUT_OF_BUFFER);
        return;
    }

    fontaddr_mailbox[mvf_font_word_count++] = 0; //terminal zero

    DEBUG_LOAD_VF( msAPI_Font_MVF_PrintInfo(); );


    Chakra_MailBox[0].u8Param[0] = ((U32)fontaddr_mailbox&0xFF000000) >> 24;
    Chakra_MailBox[0].u8Param[1] = ((U32)fontaddr_mailbox&0x00FF0000) >> 16;
    Chakra_MailBox[0].u8Param[2] = ((U32)fontaddr_mailbox&0x0000FF00) >> 8;
    Chakra_MailBox[0].u8Param[3] = ((U32)fontaddr_mailbox&0x000000FF) ;

    DEBUG_LOAD_VF(printf("Call ms_MVF_MakeFont2() at %u\n", MsOS_GetSystemTime()););

    ms_MVF_MakeFont2();
    //printf("===MApp_MediaPlayer_LoadFont: send command done===\n");

}

#endif
extern FONT Font[];
void msAPI_Font_MVF_EndGenerateBitmaps(void)
{
    U16 idx;

    DEBUG_LOAD_VF(printf("msAPI_Font_MVF_EndGenerateBitmaps() at %u\n", MsOS_GetSystemTime()););

    mvf_font_word_count = 0;

    //printf("get font command from Aeon\n");
    fontaddr = fontaddr_mailbox[mvf_font_word_count++]; //next start....
    fontaddr = GE_ADDR_ALIGNMENT(fontaddr);

    // Update BMPfontaddr
    // fontaddr is a Virtual addr, need to convert to PA first
    BMPfontaddr = GE_ADDR_ALIGNMENT( MsOS_VA2PA(fontaddr + 0x20) );

    DEBUG_LOAD_VF( msAPI_Font_MVF_PrintInfo(); );


    for (idx = 0; ; idx++)
    {
        U16 font_id;
        U8 output_bpp;
        U8 output_size;
        U8 output_width;
        U8 output_height;
        U32 u32BBoxAddr;
        U32 u32CodemapAddr;
        U32 u32GlyphAddr;
        U16 u32CharNum;
        U16 u32CodemapBlockNum;
        U16 u32CharGlyphBytes;

        output_size  = fontaddr_mailbox[mvf_font_word_count++];
        font_id      = fontaddr_mailbox[mvf_font_word_count++];
        output_bpp   = fontaddr_mailbox[mvf_font_word_count++];
        output_width = fontaddr_mailbox[mvf_font_word_count++];

        APIMVF_DBG(printf("--------------------------------------\n"));
        APIMVF_DBG(printf("==>output_size = %x\n",output_size));
        APIMVF_DBG(printf("==>font_id = %x\n",font_id));
        APIMVF_DBG(printf("==>output_bpp = %x\n",output_bpp));
        APIMVF_DBG(printf("==>output_width = %x\n",output_width));

        if (output_size == 0)
            break;

        if ( mvf_font_word_count >=     MVF_MAX_COMMAND_WORDS)
        {
            msWarning(ERR_FONT_OUT_OF_BUFFER); //something wrong...
            return;
        }

        output_height  = fontaddr_mailbox[mvf_font_word_count++];
        u32BBoxAddr    = fontaddr_mailbox[mvf_font_word_count++];
        u32CodemapAddr = fontaddr_mailbox[mvf_font_word_count++];
        u32GlyphAddr   = fontaddr_mailbox[mvf_font_word_count++];

        APIMVF_DBG(printf("==>output_height = %x\n",output_height));
        APIMVF_DBG(printf("==>u32BBoxAddr = %x\n",u32BBoxAddr));
        APIMVF_DBG(printf("==>u32CodemapAddr = %x\n",u32CodemapAddr));
        APIMVF_DBG(printf("==>u32GlyphAddr = %x\n",u32GlyphAddr));

        u32CharNum          = fontaddr_mailbox[mvf_font_word_count++];
        u32CodemapBlockNum  = fontaddr_mailbox[mvf_font_word_count++];
        u32CharGlyphBytes   = fontaddr_mailbox[mvf_font_word_count++];

        APIMVF_DBG(printf("==>u32CharNum = %x\n",u32CharNum));
        APIMVF_DBG(printf("==>u32CodemapBlockNum = %x\n",u32CodemapBlockNum));
        APIMVF_DBG(printf("==>u32CharGlyphBytes = %x\n",u32CharGlyphBytes));

        Font[font_id].fHandle = msAPI_OSD_RESOURCE_LoadFont(
                _VA2PA(u32GlyphAddr),
                _VA2PA(u32GlyphAddr),
                _VA2PA(u32BBoxAddr),
                _VA2PA(u32CodemapAddr),
                u32CharNum,
                u32CodemapBlockNum,
                output_width,
                output_height,
                output_bpp,
                u32CharGlyphBytes,
                1,
                MIU_SDRAM
                );
        //mvf_font_cmd.u8OutputBitmapSize[idx] = 0; //release it
    }


    /*maight be load it again: if (MDrv_CheckMailBoxReady())
    {
        MailBoxPara.u8CmdClass      = MB_CLASS_MVF;
        MailBoxPara.u8CmdIdx        = MB_MVF_CMD_DONE_FACE;
        MailBoxPara.ParamCnt        = 0;
        MailBoxPara.CMDType         = MB_CMD_TYPE_DEFAULT;
        MDrv_SendMailBoxMsg();
        //printf("===MApp_MediaPlayer_LoadFont: send command done===\n");
    }*/

    mvf_font_word_count = 0; //reset for next loading
}


/******************************************************************************/
/// API for loading vector font::
/// @param u8StepID \b IN step id
/******************************************************************************/
void msAPI_Font_MVF_LoadFont(LOADFONT_STRUCT* font_info, U8 u8Begin, U8 u8End)
{
    U8 i;

    DEBUG_LOAD_VF(printf("msAPI_Font_MVF_LoadFont(u8Begin=%u, u8End=%u) at %u\n", u8Begin, u8End, MsOS_GetSystemTime()););

    if( FALSE == msAPI_Font_MVF_LoadFlashFontToSDRAM(FONT_MSTAR_UNICODE_MVF) )
    {
        printf("\nError: msAPI_Font_MVF_LoadFlashFontToSDRAM() failed!\n");
        return;
    }



    for(i=u8Begin; i<=u8End; i++)
    {
        msAPI_Font_MVF_AddBitmapSize(
            font_info[i].FontID, font_info[i].output_bpp,
            font_info[i].output_size, font_info[i].output_width,
            font_info[i].output_height, font_info[i].unicode_from,
            font_info[i].unicode_to);
    }

    msAPI_Font_MVF_StartGenerateBitmaps(); //NOTE: non-blocking function!

    msAPI_Font_MVF_EndGenerateBitmaps();
}

//----VChip data moving
#if ( (ENABLE_ARABIC_OSD) || (ENABLE_THAI_OSD) || (BLOADER)|| (ATSC_CC == DTV_CC) || (ATSC_CC == ATV_CC) )
/******************************************************************************/
/// MIU Load Font
/// Copy font table from flash to SDRAM, and config GE Font information
/// @param u16FontBinID \b IN Font ID in the packed binary
/// @return font handle
/******************************************************************************/
FONTHANDLE msAPI_Font_LoadFlashFontToSDRAM(U16 u16FontBinID)
{
    DEBUG_API_LOAD_FONT(printf("msAPI_Font_LoadFlashFontToSDRAM(u16FontBinID=0x%X)\n",u16FontBinID););

    FONTHANDLE handle = INVALID_FONTHANDLE;
    FONT_BIN_HEADER         FontBinHeader;
    ST_LOAD_FONT_SDRAM_REPORT FontSdramInfo;


    DEBUG_API_LOAD_FONT(printf("BMPfontaddr=0x%X\n",BMPfontaddr););

    if (!msAPI_Font_LoadFlashFont_Decompress(u16FontBinID, BMPfontaddr, &FontBinHeader, &FontSdramInfo))
    {
        return INVALID_FONTHANDLE;
    }

    if ( (BMPfontaddr + FontSdramInfo.u32SdramLen) <= (FONT_START_ADR + FONT_START_LEN) )
    {
        handle = msAPI_OSD_RESOURCE_LoadFont( FontSdramInfo.u32StartAddr,
                                   FontSdramInfo.u32GlyphAddr,
                                   FontSdramInfo.u32BBoxAddr,
                                   FontSdramInfo.u32CodemapAddr,
                                   FontBinHeader.u32CharNum,
                                   FontBinHeader.u32CodemapBlockNum,
                                   FontBinHeader.u32Width,
                                   FontBinHeader.u32Height,
                                   FontBinHeader.u32BPP,
                                   FontBinHeader.u32CharGlyphBytes,
                                   FontBinHeader.u32Pitch,
                                   MIU_SDRAM
                                   );

        APIMVF_DBG(printf("FontS:%LX\n", BMPfontaddr));
        // calc for next font table starting address
        BMPfontaddr = GE_ADDR_ALIGNMENT(BMPfontaddr + FontSdramInfo.u32SdramLen);
        DEBUG_API_LOAD_FONT(printf(" => BMPfontaddr=0x%X\n",BMPfontaddr););

        APIMVF_DBG(printf("FontE:%LX %LX\n", BMPfontaddr, FontSdramInfo.u32SdramLen));
    }
    else
    {
        printf("\nError: Font mem over flow! (BMPfontaddr=0x%X, 0x%X)\n", (U32)(BMPfontaddr + FontSdramInfo.u32SdramLen), (U32)(FontSdramInfo.u32SdramLen) );
    }

    return handle;
}
#endif

#else // #if (!COPRO_MVF_ENABLE)

BOOLEAN msAPI_Font_MVF_LoadFlashFontToSDRAM(U16 u16FontBinID)
{
    BININFO   BinInfo;
    U32 u32Len;
    U16 u16TryCount;
    MBX_Msg mbox;
    BOOLEAN bResult;
    MBX_Result stResult;

    BinInfo.B_ID = u16FontBinID;

    msAPI_MIU_Get_BinInfo(&BinInfo, &bResult) ;
    if (bResult != PASS)
    {
        msWarning(ERR_FONT_BIN_NOT_FOUND);
        return FALSE;
    }

    //printf("msAPI_MIU_LoadFlashFont_MVF: addr=%ld, len=%ld\n",
    //    BinInfo.B_FAddr, BinInfo.B_Len);

    u32Len = (BinInfo.B_Len+(MIU_ALIGN_UNIT-1UL)) & ~(MIU_ALIGN_UNIT-1UL);

    mvf_font_word_count = 0;
    fontaddr_mailbox[mvf_font_word_count+0] = fontaddr;
    fontaddr_mailbox[mvf_font_word_count+1] = fontaddr + u32Len;

    MApi_BDMA_XCopy(MCPY_LOADFONT, BinInfo.B_FAddr, _VA2PA(fontaddr), u32Len);

    mbox.u8MsgClass           = E_MBX_CLASS_MVF;
    mbox.u8Index              = MB_MVF_CMD_LOAD_FACE;
    mbox.u8ParameterCount     = 0x04;
    mbox.eMsgType             = E_MBX_MSG_TYPE_NORMAL;
    mbox.u8Parameters[0]      = ((U32)fontaddr_mailbox&0xFF000000) >> 24;
    mbox.u8Parameters[1]      = ((U32)fontaddr_mailbox&0x00FF0000) >> 16;
    mbox.u8Parameters[2]      = ((U32)fontaddr_mailbox&0x0000FF00) >> 8;
    mbox.u8Parameters[3]      = ((U32)fontaddr_mailbox&0x000000FF) ;

    stResult = MSApi_MBX_SendMsg(&mbox);
    if(stResult != E_MBX_SUCCESS)
    {
        printf("stResult = %x\n", (U16)stResult);
    }

    //wait for ok...
    u16TryCount = 0;
    //note: AEON_MVF might be no echo,
    // so we give it a timeout: 2500*2 = 5000ms, and send the mailbox msg again
    while( (msAPI_ProcessMailBox() != MB_MVF_RETURN_DONE) && (u16TryCount < 2500) )
    {
        msAPI_Timer_Delayms(2);
        u16TryCount++;
    }

    printf("LoadCount : %d\n", u16TryCount);

    return TRUE;
}

void msAPI_Font_MVF_AddBitmapSize(
        U16 font_id,
        U8 output_bpp, U8 output_size,
        U8 output_width, U8 output_height,
        U16* unicode_from, U16* unicode_to)
{
    U16 idx;

    if ( mvf_font_word_count >=     MVF_MAX_COMMAND_WORDS)
    {
        msWarning(ERR_FONT_OUT_OF_BUFFER);
        return;
    }
    if ( unicode_from == 0 || unicode_to == 0 )
    {
        msWarning(ERR_FONT_WRONG_FORMAT);
        return;
    }

    //send to AEON... parameters...
    if ( mvf_font_word_count == 0 )
    {
        fontaddr_mailbox[mvf_font_word_count++] = fontaddr; //u32OutputStartAddr
    }

    fontaddr_mailbox[mvf_font_word_count++] = output_size; //   u32OutputBitmapSize    //loop to zero                       //skip if size=0
    fontaddr_mailbox[mvf_font_word_count++] = font_id; //      u32OutputFontID                            ///for GE load font id
    fontaddr_mailbox[mvf_font_word_count++] = output_bpp; //      u32OutputBitmapBPP
    fontaddr_mailbox[mvf_font_word_count++] = output_width;//      u32OutputBitmapWidth                      ///< Width in pixels of a font
    fontaddr_mailbox[mvf_font_word_count++] = output_height;

    for (idx = 0; ; idx++)
    {
        fontaddr_mailbox[mvf_font_word_count++] = unicode_from[idx];
        fontaddr_mailbox[mvf_font_word_count++] = unicode_to[idx];
        if (unicode_from[idx] == 0 && unicode_to[idx] == 0)
        {
            break;
        }
    }
}

void msAPI_Font_MVF_StartGenerateBitmaps(void)
{
    MBX_Msg mbox;
    MBX_Result stResult;

    if ( mvf_font_word_count == 0 )
    {
        msWarning(ERR_FONT_GENERIC_ERROR); //no parameter....
        return;
    }
    if ( mvf_font_word_count >=     MVF_MAX_COMMAND_WORDS)
    {
        msWarning(ERR_FONT_OUT_OF_BUFFER);
        return;
    }

    fontaddr_mailbox[mvf_font_word_count++] = 0; //terminal zero

    mbox.u8MsgClass             = E_MBX_CLASS_MVF;
    mbox.u8Index                = MB_MVF_CMD_GENERATE_BITMAP;
    mbox.u8ParameterCount       = 0x04;
    mbox.eMsgType               = E_MBX_MSG_TYPE_NORMAL;
    mbox.u8Parameters[0]        = ((U32)(fontaddr_mailbox)&0xFF000000) >> 24;
    mbox.u8Parameters[1]        = ((U32)(fontaddr_mailbox)&0x00FF0000) >> 16;
    mbox.u8Parameters[2]        = ((U32)(fontaddr_mailbox)&0x0000FF00) >> 8;
    mbox.u8Parameters[3]        = ((U32)(fontaddr_mailbox)&0x000000FF) ;

    stResult = MSApi_MBX_SendMsg(&mbox);
    if(stResult != E_MBX_SUCCESS)
    {
        printf("stResult = %x\n", (U16)stResult);
    }
}

void msAPI_Font_MVF_WaitForGenerateBitmaps(void)
{
    U16 u16TryCount = 0;
    //wait for ok...
    //note: AEON_MVF might be no echo,
    // so we give it a timeout: 2500*2 = 5000ms, and send the mailbox msg again
    while( (msAPI_ProcessMailBox() != MB_MVF_RETURN_DONE) && u16TryCount < 2500 )
    {
        msAPI_Timer_Delayms(2);
        u16TryCount++;
    }
    printf("WaitForGenBitmaps : %d\n", u16TryCount);
}

extern FONT Font[];
void msAPI_Font_MVF_EndGenerateBitmaps(void)
{
    U16 idx;

    mvf_font_word_count = 0;

    //printf("get font command from Aeon\n");
    fontaddr = fontaddr_mailbox[mvf_font_word_count++]; //next start....
    fontaddr = GE_ADDR_ALIGNMENT(fontaddr);

    // Update BMPfontaddr
    // fontaddr is a Virtual addr, need to convert to PA first
    BMPfontaddr = GE_ADDR_ALIGNMENT( MsOS_VA2PA(fontaddr + 0x20) );

    for (idx = 0; ; idx++)
    {
        U16 font_id;
        U8 output_bpp;
        U8 output_size;
        U8 output_width;
        U8 output_height;
        U32 u32BBoxAddr;
        U32 u32CodemapAddr;
        U32 u32GlyphAddr;
        U16 u32CharNum;
        U16 u32CodemapBlockNum;
        U16 u32CharGlyphBytes;

        output_size  = fontaddr_mailbox[mvf_font_word_count++];
        font_id      = fontaddr_mailbox[mvf_font_word_count++];
        output_bpp   = fontaddr_mailbox[mvf_font_word_count++];
        output_width = fontaddr_mailbox[mvf_font_word_count++];

        APIMVF_DBG(printf("==>output_size = %x\n",output_size));
        APIMVF_DBG(printf("==>font_id = %x\n",font_id));
        APIMVF_DBG(printf("==>output_bpp = %x\n",output_bpp));
        APIMVF_DBG(printf("==>output_width = %x\n",output_width));

        if (output_size == 0)
            break;
        if ( mvf_font_word_count >=     MVF_MAX_COMMAND_WORDS)
        {
            msWarning(ERR_FONT_OUT_OF_BUFFER); //something wrong...
            return;
        }

        output_height  = fontaddr_mailbox[mvf_font_word_count++];
        u32BBoxAddr    = fontaddr_mailbox[mvf_font_word_count++];
        u32CodemapAddr = fontaddr_mailbox[mvf_font_word_count++];
        u32GlyphAddr   = fontaddr_mailbox[mvf_font_word_count++];

        APIMVF_DBG(printf("==>output_height = %x\n",output_height));
        APIMVF_DBG(printf("==>u32BBoxAddr = %x\n",u32BBoxAddr));
        APIMVF_DBG(printf("==>u32CodemapAddr = %x\n",u32CodemapAddr));
        APIMVF_DBG(printf("==>u32GlyphAddr = %x\n",u32GlyphAddr));

        u32CharNum          = fontaddr_mailbox[mvf_font_word_count++];
        u32CodemapBlockNum  = fontaddr_mailbox[mvf_font_word_count++];
        u32CharGlyphBytes   = fontaddr_mailbox[mvf_font_word_count++];

        APIMVF_DBG(printf("==>u32CharNum = %x\n",u32CharNum));
        APIMVF_DBG(printf("==>u32CodemapBlockNum = %x\n",u32CodemapBlockNum));
        APIMVF_DBG(printf("==>u32CharGlyphBytes = %x\n",u32CharGlyphBytes));

        Font[font_id].fHandle = msAPI_OSD_RESOURCE_LoadFont(
                _VA2PA(u32GlyphAddr),
                _VA2PA(u32GlyphAddr),
                _VA2PA(u32BBoxAddr),
                _VA2PA(u32CodemapAddr),
                u32CharNum,
                u32CodemapBlockNum,
                output_width,
                output_height,
                output_bpp,
                u32CharGlyphBytes,
                1,
                MIU_SDRAM
                );
        //mvf_font_cmd.u8OutputBitmapSize[idx] = 0; //release it
    }
    mvf_font_word_count = 0; //reset for next loading
}

void msAPI_Font_MVF_LoadFont(LOADFONT_STRUCT* font_info, U8 u8Begin, U8 u8End)
{

    U8 i;
    if (msAPI_Font_MVF_LoadFlashFontToSDRAM(FONT_MSTAR_UNICODE_MVF))
    {
        for(i=u8Begin; i<=u8End; i++)
        {
            msAPI_Font_MVF_AddBitmapSize(
                font_info[i].FontID, font_info[i].output_bpp,
                font_info[i].output_size, font_info[i].output_width,
                font_info[i].output_height, font_info[i].unicode_from,
                font_info[i].unicode_to);
        }
        msAPI_Font_MVF_StartGenerateBitmaps(); //NOTE: non-blocking function!

    }
    //msAPI_Font_MVF_EndGenerateBitmaps();
}
#endif // #if (!COPRO_MVF_ENABLE)

#else // #if VECTOR_FONT_ENABLE

FONTHANDLE msAPI_Font_LoadFlashFontToSDRAM(U16 u16FontBinID)
{
    FONTHANDLE handle = INVALID_FONTHANDLE;
    FONT_BIN_HEADER         FontBinHeader;
    ST_LOAD_FONT_SDRAM_REPORT FontSdramInfo;

    memset(&FontBinHeader,0,sizeof(FONT_BIN_HEADER));

    if (!msAPI_Font_LoadFlashFont_Decompress(u16FontBinID, s_u32FontPhyAddr, &FontBinHeader, &FontSdramInfo))
    {
        return INVALID_FONTHANDLE;
    }

    //printf("\n fontaddr = %lx, _VA2PA_fontaddr = %lx, FontSdramInfo.u32SdramLen = %lx", fontaddr,  _VA2PA(fontaddr), FontSdramInfo.u32SdramLen );

    if ((s_u32FontPhyAddr + FontSdramInfo.u32SdramLen) <= ((FONT_START_MEMORY_TYPE & MIU1) ? (FONT_START_ADR | MIU_INTERVAL) : (FONT_START_ADR)) + FONT_START_LEN)
    {
        handle = msAPI_OSD_RESOURCE_LoadFont(
                FontSdramInfo.u32StartAddr,
                FontSdramInfo.u32GlyphAddr,
                FontSdramInfo.u32BBoxAddr,
                FontSdramInfo.u32CodemapAddr,
                FontBinHeader.u32CharNum,
                FontBinHeader.u32CodemapBlockNum,
                FontBinHeader.u32Width,
                FontBinHeader.u32Height,
                FontBinHeader.u32BPP,
                FontBinHeader.u32CharGlyphBytes,
                FontBinHeader.u32Pitch,
                MIU_SDRAM
                );
        // calc for next font table starting address
        s_u32FontPhyAddr = GE_ADDR_ALIGNMENT(s_u32FontPhyAddr + FontSdramInfo.u32SdramLen);
    }
    else
    {
        msWarning(ERR_FONT_OUT_OF_BUFFER);
    }

    return handle;
}
#endif //VECTOR_FONT_ENABLE


#if (BRAZIL_CC == 1)

/******************************************************************************/
/// MIU Load Font
/// Copy font table from flash to SDRAM, and config GE Font information
/// @param u16FontBinID \b IN Font ID in the packed binary
/// @return font handle
/******************************************************************************/
FONTHANDLE msAPI_Font_LoadFlashFontToSDRAM(U16 u16FontBinID)
{
    FONTHANDLE handle = INVALID_FONTHANDLE;
    FONT_BIN_HEADER         FontBinHeader;
    ST_LOAD_FONT_SDRAM_REPORT FontSdramInfo;

    FontBinHeader.u32BPP = 0;
    FontBinHeader.u32BPP = 0;
    FontBinHeader.u32Height = 0;
    FontBinHeader.u32Pitch = 0;
    FontBinHeader.u32Width = 0;
    FontBinHeader.u32CharNum = 0;

    if (!msAPI_Font_LoadFlashFont_Decompress(u16FontBinID, _VA2PA(fontaddr), &FontBinHeader, &FontSdramInfo))
    {
        return INVALID_FONTHANDLE;
    }

    //printf("\n fontaddr = %lx, _VA2PA_fontaddr = %lx, FontSdramInfo.u32SdramLen = %lx", fontaddr,  _VA2PA(fontaddr), FontSdramInfo.u32SdramLen );

    if ((_VA2PA( fontaddr) + FontSdramInfo.u32SdramLen) <= (((FONT_START_MEMORY_TYPE & MIU1) ? (FONT_START_ADR | MIU_INTERVAL) : (FONT_START_ADR)) + FONT_START_LEN))
    {

        handle = msAPI_OSD_RESOURCE_LoadFont(
                FontSdramInfo.u32StartAddr,
                FontSdramInfo.u32GlyphAddr,
                FontSdramInfo.u32BBoxAddr,
                FontSdramInfo.u32CodemapAddr,
                FontBinHeader.u32CharNum,
                FontBinHeader.u32CodemapBlockNum,
                FontBinHeader.u32Width,
                FontBinHeader.u32Height,
                FontBinHeader.u32BPP,
                FontBinHeader.u32CharGlyphBytes,
                FontBinHeader.u32Pitch,
                MIU_SDRAM
                );
        // calc for next font table starting address
        fontaddr=_PA2VA (GE_ADDR_ALIGNMENT(_VA2PA( fontaddr) + FontSdramInfo.u32SdramLen));
    }
    else
    {
//        msWarning(ERR_FONT_OUT_OF_BUFFER);
    }

    return handle;
}

#endif

FONTHANDLE msAPI_Font_LoadTTF(void)
{
    FONTHANDLE handle = INVALID_FONTHANDLE;

    handle = msAPI_OSD_RESOURCE_LoadTTF();

    return handle;
}

#if (VECTOR_FONT_ENABLE&&COPRO_MVF_ENABLE)
MB_MVF_RETURN_STATE msAPI_ProcessMailBox(void)
{
    //U8 u8AeonMailBox[12];
    MBX_Msg MB_Message;
    memset(&MB_Message,0,sizeof(MBX_Msg));
    U8 bResult;

    bResult = MSApi_MBX_RecvMsg(E_MBX_CLASS_MVF, &MB_Message, 0,MBX_CHECK_NORMAL_MSG);
    //printf("msAPI_ProcessMailBox : %x\n", bResult);
    if(bResult == E_MBX_SUCCESS)
    {
        if ( MB_Message.u8Parameters[0] ) //u8Param[0]
            return MB_MVF_RETURN_FAILED;

        if ( MB_Message.u8Index == MB_MVF_CMD_GENERATE_DONE ) //command index: MB_MVF_CMD_GENERATE_DONE
        {
            //PRINT_CURRENT_LINE();
            msAPI_Font_MVF_EndGenerateBitmaps();
            return MB_MVF_RETURN_DONE;
        }
        else if ( MB_Message.u8Index == MB_MVF_CMD_LOAD_DONE )
        {
            //PRINT_CURRENT_LINE();
            return MB_MVF_RETURN_DONE;
        }
    }
    else if( bResult == E_MBX_ERR_NO_MORE_MSG )
    {
    }
    else
    {
        PRINT_CURRENT_LINE();
        printf("\nError: Receive Msg resrult=%u\n", bResult);
        //msAPI_Timer_Delayms(1000);
    }

    /*if(MSApi_MBX_RecvMsg(E_MBX_CLASS_LZSS, &MB_Message, 0,MBX_CHECK_NORMAL_MSG) == E_MBX_SUCCESS)
    {
        if( MB_Message.u8Parameters[0] )
            return MB_RETURN_LZSS_COMPRESS_FAILED;
        return MB_RETURN_LZSS_COMPRESS_DONE;
    }*/

    return MB_MVF_RETURN_NONE;
}
#endif

#if DYNAMIC_VECTOR_FONT_ENABLE

BOOLEAN msAPI_Dynamic_MVF_Generator(U16 *tblUnicode, U32 tableSize)
{
    U32 u32Len;

    if ((u32Len=msAPI_LoadUsbFontLib2MVF(tblUnicode, tableSize)) == 0)
    {
        printf("ERR_FONT_FILE_NOT_FOUND.\n");
        msWarning(ERR_FONT_BIN_NOT_FOUND);
        return FALSE;
    }

    u32Len = (u32Len+(MIU_ALIGN_UNIT-1UL)) & ~(MIU_ALIGN_UNIT-1UL);

    mvf_font_word_count = 0;
    fontaddr_mailbox[mvf_font_word_count+0] = DYNAXIC_MVF_FONT_BUFFER_ADR;
    fontaddr_mailbox[mvf_font_word_count+1] = DYNAXIC_MVF_FONT_BUFFER_ADR + u32Len;


    Chakra_MailBox[0].u8Param[0] = ((U32)fontaddr_mailbox&0xFF000000) >> 24;
    Chakra_MailBox[0].u8Param[1] = ((U32)fontaddr_mailbox&0x00FF0000) >> 16;
    Chakra_MailBox[0].u8Param[2] = ((U32)fontaddr_mailbox&0x0000FF00) >> 8;
    Chakra_MailBox[0].u8Param[3] = ((U32)fontaddr_mailbox&0x000000FF) ;

    ms_MVF_LoadFont();

    return TRUE;
}

BOOLEAN msAPI_Dynamic_MVF_LoadFont(U16 font_id, U16 output_size, U8 output_width, U8 output_height, U16* unicode_tbl, U16 tblSize)
{
    U16 idx;

    if (msAPI_Dynamic_MVF_Generator( unicode_tbl, tblSize) == FALSE)
    {
        printf("Load MVF Fail!\n");
        return FALSE;
    }

    if ( unicode_tbl == 0 || tblSize == 0 )
    {
        msWarning(ERR_FONT_WRONG_FORMAT);
        return FALSE;
    }

    mvf_font_word_count = 0;  //reset for loading

    //send to AEON... parameters...
    if ( mvf_font_word_count == 0 )
    {
        fontaddr_mailbox[mvf_font_word_count++] = DYNAXIC_MVF_FONT_BUFFER_ADR|0x80000000; //u32OutputStartAddr
    }

    fontaddr_mailbox[mvf_font_word_count++] = output_size; //   u32OutputBitmapSize    //loop to zero                       //skip if size=0
    fontaddr_mailbox[mvf_font_word_count++] = font_id; //      u32OutputFontID                            ///for GE load font id
    fontaddr_mailbox[mvf_font_word_count++] = 2; //      u32OutputBitmapBPP
    fontaddr_mailbox[mvf_font_word_count++] = output_width;//      u32OutputBitmapWidth                      ///< Width in pixels of a font
    fontaddr_mailbox[mvf_font_word_count++] = output_height;

    for (idx = 0; ; idx++)
    {
        fontaddr_mailbox[mvf_font_word_count++] = unicode_tbl[idx];
        fontaddr_mailbox[mvf_font_word_count++] = unicode_tbl[idx];
        if (unicode_tbl[idx] == 0 )
        {
            break;
        }
    }

    return TRUE;
}

void msAPI_Font_Dynamic_MVF_StartGenerateBitmaps(void)
{
    if ( mvf_font_word_count == 0 )
    {
        msWarning(ERR_FONT_GENERIC_ERROR); //no parameter....
        return;
    }
    if ( mvf_font_word_count >=     MVF_MAX_COMMAND_WORDS)
    {
        msWarning(ERR_FONT_OUT_OF_BUFFER);
        return;
    }

    fontaddr_mailbox[mvf_font_word_count++] = 0; //terminal zero

    Chakra_MailBox[0].u8Param[0] = ((U32)fontaddr_mailbox&0xFF000000) >> 24;
    Chakra_MailBox[0].u8Param[1] = ((U32)fontaddr_mailbox&0x00FF0000) >> 16;
    Chakra_MailBox[0].u8Param[2] = ((U32)fontaddr_mailbox&0x0000FF00) >> 8;
    Chakra_MailBox[0].u8Param[3] = ((U32)fontaddr_mailbox&0x000000FF) ;

    ms_MVF_MakeFont2();
    //printf("===MApp_MediaPlayer_LoadFont: send command done===\n");

}


extern FONT Font[];
void msAPI_Font_Dynamic_MVF_EndGenerateBitmaps(void)
{
    U16 idx;

    mvf_font_word_count = 0;

    //printf("get font command from Aeon\n");
    fontaddr = fontaddr_mailbox[mvf_font_word_count++]; //next start....
    fontaddr = GE_ADDR_ALIGNMENT(fontaddr);

    for (idx = 0; ; idx++)
    {
        U16 font_id;
        U8 output_bpp;
        U8 output_size;
        U8 output_width;
        U8 output_height;
        U32 u32BBoxAddr;
        U32 u32CodemapAddr;
        U32 u32GlyphAddr;
        U16 u32CharNum;
        U16 u32CodemapBlockNum;
        U16 u32CharGlyphBytes;

        output_size  = fontaddr_mailbox[mvf_font_word_count++];
        font_id      = fontaddr_mailbox[mvf_font_word_count++];
        output_bpp   = fontaddr_mailbox[mvf_font_word_count++];
        output_width = fontaddr_mailbox[mvf_font_word_count++];

        APIMVF_DBG(printf("==>output_size = %x\n",output_size));
        APIMVF_DBG(printf("==>font_id = %x\n",font_id));
        APIMVF_DBG(printf("==>output_bpp = %x\n",output_bpp));
        APIMVF_DBG(printf("==>output_width = %x\n",output_width));

        if (output_size == 0)
            break;
        if ( mvf_font_word_count >=     MVF_MAX_COMMAND_WORDS)
        {
            msWarning(ERR_FONT_OUT_OF_BUFFER); //something wrong...
            return;
        }

        output_height  = fontaddr_mailbox[mvf_font_word_count++];
        u32BBoxAddr    = fontaddr_mailbox[mvf_font_word_count++];
        u32CodemapAddr = fontaddr_mailbox[mvf_font_word_count++];
        u32GlyphAddr   = fontaddr_mailbox[mvf_font_word_count++];

        APIMVF_DBG(printf("==>output_height = %x\n",output_height));
        APIMVF_DBG(printf("==>u32BBoxAddr = %x\n",u32BBoxAddr));
        APIMVF_DBG(printf("==>u32CodemapAddr = %x\n",u32CodemapAddr));
        APIMVF_DBG(printf("==>u32GlyphAddr = %x\n",u32GlyphAddr));

        u32CharNum          = fontaddr_mailbox[mvf_font_word_count++];
        u32CodemapBlockNum  = fontaddr_mailbox[mvf_font_word_count++];
        u32CharGlyphBytes   = fontaddr_mailbox[mvf_font_word_count++];

        (printf("==>u32CharNum = %x\n",u32CharNum));
        (printf("==>u32CodemapBlockNum = %x\n",u32CodemapBlockNum));
        (printf("==>u32CharGlyphBytes = %x\n",u32CharGlyphBytes));

        Font[font_id].fHandle = MDrv_GE_LoadFont(
                u32CodemapAddr,
                u32GlyphAddr,
                u32BBoxAddr,
                u32CodemapAddr,
                u32CharNum,
                u32CodemapBlockNum,
                output_width,
                output_height,
                output_bpp,
                u32CharGlyphBytes,
                1, //mvf_font_cmd.u32OutputBitmapAddrAlign,
                MIU_SDRAM
            );

        //mvf_font_cmd.u8OutputBitmapSize[idx] = 0; //release it
    }


    /*maight be load it again: if (MDrv_CheckMailBoxReady())
    {
        MailBoxPara.u8CmdClass      = MB_CLASS_MVF;
        MailBoxPara.u8CmdIdx        = MB_MVF_CMD_DONE_FACE;
        MailBoxPara.ParamCnt        = 0;
        MailBoxPara.CMDType         = MB_CMD_TYPE_DEFAULT;
        MDrv_SendMailBoxMsg();
        //printf("===MApp_MediaPlayer_LoadFont: send command done===\n");
    }*/

    mvf_font_word_count = 0; //reset for next loading
}

#endif

void msAPI_Font_VariableInit(void)
{
#if VECTOR_FONT_ENABLE
    DEBUG_LOAD_VF( printf("msAPI_Font_VariableInit()\n"); );

    fontaddr_mailbox = (U32 *)_PA2VA(GE_ADDR_ALIGNMENT(((FONT_START_MEMORY_TYPE & MIU1) ? (FONT_START_ADR | MIU_INTERVAL) : (FONT_START_ADR))));
    fontaddr = _PA2VA((GE_ADDR_ALIGNMENT(((FONT_START_MEMORY_TYPE & MIU1) ? (FONT_START_ADR | MIU_INTERVAL) : (FONT_START_ADR))) + GE_ADDR_ALIGNMENT(MVF_MAX_COMMAND_WORDS * 4)));

  #if ( ( BLOADER ) && ( ENABLE_BL_UI ) )
    BMPfontaddr = GE_ADDR_ALIGNMENT(((FONT_START_MEMORY_TYPE & MIU1) ? (FONT_START_ADR | MIU_INTERVAL) : (FONT_START_ADR))) + GE_ADDR_ALIGNMENT(MVF_MAX_COMMAND_WORDS * 4);
  #else
    BMPfontaddr = GE_ADDR_ALIGNMENT(((FONT_START_MEMORY_TYPE & MIU1) ? (FONT_START_ADR | MIU_INTERVAL) : (FONT_START_ADR))) + GE_ADDR_ALIGNMENT(MVF_MAX_COMMAND_WORDS * 4) + 0x9E000;
  #endif

    DEBUG_LOAD_VF( printf("FONT_START_ADR=0x%X\n", FONT_START_ADR); );
    DEBUG_LOAD_VF( printf("fontaddr_mailbox=0x%X\n", fontaddr_mailbox); );
    DEBUG_LOAD_VF( printf("fontaddr=0x%X\n", fontaddr); );
    DEBUG_LOAD_VF( printf("BMPfontaddr=0x%X\n", BMPfontaddr); );
#endif
}

#undef MSAPI_FONT_C
