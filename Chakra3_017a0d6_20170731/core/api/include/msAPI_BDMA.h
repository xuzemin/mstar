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
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
/// @file  drvBDMA.h
/// @brief DMA interface header file
/// @author MStar Semiconductor Inc.
///
////////////////////////////////////////////////////////////////////////////////
#ifndef _APIBDMA_
#define _APIBDMA_

////////////////////////////////////////////////////////////////////////////////
// Compiler Directive
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Include List
////////////////////////////////////////////////////////////////////////////////
#include "datatype.h"
#include "MsTypes.h"
#include "drvBDMA.h"
#include "retcode.h"
#include "BinInfo.h"
#include "retcode.h"

////////////////////////////////////////////////////////////////////////////////
// Constant & Macro Definition
////////////////////////////////////////////////////////////////////////////////
#define LZSS_COMPRESS	1
#define SLZ_COMPRESS 	2
#define MS_COMPRESS 	4
#define MS_COMPRESS7	8

#define BUF_FOR_DECOMPRESS_OFFSET1       (0x300000UL)
#define BUF_FOR_DECOMPRESS_OFFSET2       (0x600000UL)


#if defined(__mips__)
	#define NON_CACHEABLE_TO_CACHEABLE_MASK (0xDFFFFFFF)
#else
	#define NON_CACHEABLE_TO_CACHEABLE_MASK (0x7FFFFFFF)
#endif

//20100106EL
//#define BUF_OFFSET_FOR_BITMAP_DECOMPRESS_SRC (0xD00000UL)  // 13MB
//#define BUF_OFFSET_FOR_BITMAP_DECOMPRESS_DST (0x100000UL)  // 1MB
//#define BUF_OFFSET_FOR_BITMAP_DECOMPRESS_TMP (0x1000000UL)  // 16MB

#define BUF_FOR_VDEC_DECOMPRESS_OFFSET1         (0x100000UL)
#if (MEMORY_MAP <= MMAP_32MB)
#define BUF_FOR_VDEC_DECOMPRESS_OFFSET2         (0x200000UL)
#else
#define BUF_FOR_VDEC_DECOMPRESS_OFFSET2         (0x1800000UL)
#endif // #if (MEMORY_MAP <= MMAP_32MB)

////////////////////////////////////////////////////////////////////////////////
// Type & Structure Declaration
////////////////////////////////////////////////////////////////////////////////
typedef enum MEMTYPE_t
{
    MIU_FLASH = 0x00,   ///<    0: Flash
    MIU_SRAM  = 0x01,   ///<    1: SRAM
    MIU_SDRAM = 0x02,   ///<    2: SDRAM
    MIU_FILE  = 0x09,   ///<    9: FILE
} MEMTYPE;

typedef enum
{
    MCPY_LOADMVDFW,
    MCPY_LOADVDMCUFW,
    MCPY_LOADFONT,
    MCPY_LOADBITMAP,
    MCPY_LOADLOGO,
    MCPY_CCS,
} MCPY_TYPE;

// Memory copy type enumerate
typedef enum MEMCOPYTYPE_t
{
    MIU_FLASH2SDRAM = 0x02,   ///< 0x02:Flash to SDRAM
    MIU_SRAM2SDRAM  = 0x12,   ///< 0x12:SRAM to SDRAM
    MIU_SDRAM2SRAM  = 0x21,   ///< 0x21:SDRAM to SRAM
    MIU_SDRAM2SDRAM = 0x22,   ///< 0x22:SDRAM to SDRAM
    MIU_SDRAM02SDRAM1 = 0x34, ///< 0x34:SDRAM0 to SDRAM1
    MIU_SDRAM12SDRAM0 = 0x43, ///< 0x43:SDRAM1 to SDRAM0
    MIU_SDRAM02SDRAM0 = 0x33, ///< 0x33:SDRAM0 to SDRAM0
    MIU_SDRAM12SDRAM1 = 0x44, ///< 0x44:SDRAM1 to SDRAM1
    MIU_SDRAM2SDRAM_I = 0x55, ///< 0x55:SDRAM to SDRAM Inverse BitBlt
    MIU_FLASH2VDMCU=0x60,     ///< 0x60:Flash to VD MCU
    MIU_FLASH2DRAM_AEON=0x70, ///< 0x70:Flash to DRAM Aeon
} MEMCOPYTYPE;

////////////////////////////////////////////////////////////////////////////////
// External Variable Declaration
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Function Prototype Declaration
////////////////////////////////////////////////////////////////////////////////
BDMA_Result MApi_BDMA_Copy(U32 u32Srcaddr, U32 u32Dstaddr, U32 u32Len, MEMCOPYTYPE eType);
BDMA_Result MApi_BDMA_XCopy(MCPY_TYPE eType, U32 u32Srcaddr, U32 u32Dstaddr, U32 u32Len);
eRETCODE MDrv_DMA_LoadBin(BININFO *pBinInfo, U32 u32DstVA, U32 u32DecVA, U32 u32TmpVA);
//eRETCODE MDrv_DMA_Copy(U32 u32Srcaddr, U32 u32Dstaddr, U32 u32Len, MEMCOPYTYPE eType);
eRETCODE MApi_BDMA_CopyFromResource(U32 offset,U32 destVA,U32 len);

#if(ENABLE_BIN_FILE_CRC)
BOOL MApi_BDMA_CheckBinCRC(U16 u16BinId, U32 u32BinLen, U32 u32BinBuf_VA);
#endif

#endif  //_DRV_DMA_IF_H
