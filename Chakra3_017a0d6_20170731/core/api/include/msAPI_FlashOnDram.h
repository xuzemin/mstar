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
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MSAPI_FLASH_ON_DRAM_H_
#define _MSAPI_FLASH_ON_DRAM_H_

#include "Board.h"

#if (ENABLE_FLASH_ON_DRAM)

#define FOD_MAGIC_ID    0x12344321
#define FOD_MAGIC_ID_2  0x43211234

//==================================================================

#ifdef MMAP_FOD_ADR

    #define FOD_DRAM_BASE           MMAP_FOD_ADR

#else

 #if( (MEMORY_MAP == MMAP_64MB) )
    #define FOD_DRAM_BASE           (59*0x100000)
 #elif( (MEMORY_MAP == MMAP_128MB) )
    #define FOD_DRAM_BASE           (120*0x100000)
 #endif

#endif

#define FOD_AP_END_FLASH_ADDR       0x01000000 // Sboot will auto cal

//-------------------------------------------------------------------------
#if( defined(__mips__) )
 #if( (MEMORY_MAP == MMAP_64MB) )
    #define FOD_FLASH_DATA_1_SIZE   0x200000
 #elif( (MEMORY_MAP == MMAP_128MB) )
    #define FOD_FLASH_DATA_1_SIZE   0x300000
 #endif
#endif

#if( defined(__aeon__) ) // Whisky
 #if( (FLASH_SIZE == FLASH_SIZE_8MB) ) // 8M Flash
    #define FOD_FLASH_DATA_1_SIZE   0x300000
 #elif( (FLASH_SIZE == FLASH_SIZE_4MB) ) // 4M Flash
    #define FOD_FLASH_DATA_1_SIZE   0x200000
 #endif
#endif

//==================================================================


#define FOD_FLASH_DATA_2_ADDR       0
#define FOD_FLASH_DATA_2_SIZE       0

typedef struct
{
    U32 u32FODMagicId_1;

    U32 u32DramBaseAddr;

    U32 u32FlashDataAddr_1;
    U32 u32FlashDataSize_1;

    U32 u32FlashDataAddr_2;
    U32 u32FlashDataSize_2;

    U32 u32FODMagicId_2;
} __attribute__ ((packed)) StuFODDataForImgInfo;

void msAPI_FlashOnDram_Init(void);

BOOLEAN msAPI_FlashOnDram_IsDataOnDram(U32 u32FlashAddr, U32 u32Size );

BOOLEAN msAPI_FlashOnDram_CopyDataToDram(U32 u32FlashAddr, U32 u32DramAddr, U32 u32Size );

void msAPI_FlashOnDram_Disable(void);


#endif // #if(ENABLE_FLASH_ON_DRAM)

#endif // _MSAPI_FLASH_ON_DRAM_H_

