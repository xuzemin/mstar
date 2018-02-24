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
// (MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef MSAPI_FLASH_H
#define MSAPI_FLASH_H


#include "Board.h"


#ifdef MSAPI_FLASH_C
    #define INTERFACE
#else
    #define INTERFACE extern
#endif

//================================================================

#ifndef FLASH_ALWAYS_NOT_PROTECT_DB_GEN
    #define FLASH_ALWAYS_NOT_PROTECT_DB_GEN     1
#endif

#define FLASH_BLOCK_ERASE_MAX_TIME (2000)

////////////////////////////////////////////////////////////////////////////////

typedef enum
{
    E_FLASH_CHIP_SELECT_0 = 0,
    E_FLASH_CHIP_SELECT_1 = 1,
    E_FLASH_CHIP_SELECT_2 = 2,
    E_FLASH_CHIP_SELECT_3 = 3,
}FLASH_CHIP_SELECT;


/////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////

void msAPI_Flash_Init(void);
BOOL msAPI_Flash_Check_WriteAddressValid(U32 u32StartAddr, U32 u32Size );

INTERFACE BOOLEAN msAPI_Flash_ChipSelect(FLASH_CHIP_SELECT eFlashChipSel);

U16 msAPI_Flash_Get_StatusRegister(void);


//INTERFACE BOOLEAN msAPI_Flash_WriteProtect(BOOL bEnable);
BOOLEAN msAPI_Flash_Set_WriteProtect(BOOL bEnable);

INTERFACE BOOLEAN msAPI_Flash_AddressErase(U32 u32StartAddr,U32 u32EraseSize,BOOL bWait);
//INTERFACE BOOLEAN msAPI_Flash_BlockErase(U32 u32StartBlock, U32 u32EndBlock, BOOL bWait);
INTERFACE BOOLEAN msAPI_Flash_Write(U32 u32StartAddr, U32 u32WriteSize, U8 * user_buffer);
INTERFACE BOOLEAN msAPI_Flash_Read(U32 u32StartAddr, U32 u32ReadSize, U8 * user_buffer);
INTERFACE BOOLEAN msAPI_Flash_DetectType(void);
INTERFACE BOOLEAN msAPI_Flash_AddressToBlock(U32 u32FlashAddr, U32 * pu32BlockIndex);
INTERFACE BOOLEAN msAPI_Flash_BlockToAddress(U32 u32BlockIndex, U32 *pu32FlashAddr);

INTERFACE BOOLEAN msAPI_Flash_CheckWriteDone(void);
BOOL msAPI_Flash_WaitWriteDone(U32 u32Timeout);

#if(ENABLE_FLASH_WRITE_PROTECT_METHOD_M12)
INTERFACE void msAPI_Flash_WriteProtect_SetBPStatus(void);
INTERFACE BOOLEAN msAPI_Flash_WriteProtect_GetBPStatus(void);
#endif

void msAPI_Flash_Init_WriteProtect(void);

void msAPI_Flash_Set_WP_DB_CH(BOOL bEnable );
void msAPI_Flash_Set_WP_DB_GEN(BOOL bEnable );

BOOL msAPI_Flash_StoreDramData2Flash(U32 u32FlashAddr, U32 u32srcaddr, U32 u32Size, BOOL bControlWP);    // SRAM2Flash

//INTERFACE void MApp_Printf_Flash_Variable(void);

INTERFACE U16  msAPI_Flash_GetVersion(void);

//=========================================================
U16 msAPI_Flash_Get_StatusRegU16(void);
void msAPI_Flash_Set_StatusRegU16(U16 u16Mask, U16 u16Value);

BOOL msAPI_Flash_Set_WriteProtect_Disable_Range(U32 u32DisableLowerBound, U32 u32DisableSize);


#if (MAYA_PATCH_04)
    #define FLASH_ONLY_FULL_RANGE_WP    1
#else
    #ifndef FLASH_ONLY_FULL_RANGE_WP
    #define FLASH_ONLY_FULL_RANGE_WP    0
    #endif
#endif

//=========================================================

void msAPI_Flash_PrintData(U32 u32FlashAddr, U32 u32Size);

void msAPI_Flash_Test_WriteData(void);

void msAPI_Flash_Test_WriteBank(U8 u8Bank);


//******************************************************************************

#undef INTERFACE

//******************************************************************************

#endif // #define MSAPI_FLASH_H

