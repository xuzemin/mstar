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
// Copyright (c) 2006-2007 MStar Semiconductor, Inc.
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

#ifndef _MSAPI_STILLIMAGE_DLMALLOC_H_
#define _MSAPI_STILLIMAGE_DLMALLOC_H_

///////////////////////////////////////////////////////////////////////////////
/// @file   msapi_stillimage_dlmalloc.h
/// This file contains the interface for dynamic memory allocation module for still image
/// @author MStar Semiconductor Inc.
/// @brief  Dynamic Memory Allocation Module
///////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

//------------------------------------------------------------------------------
// Include Files
//------------------------------------------------------------------------------
#include "datatype.h"
//#include "mm_types.h"

//------------------------------------------------------------------------------
// Defines & Macros
//------------------------------------------------------------------------------
#ifdef _MSAPI_STILLIMAGE_DLMALLOC_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif

//------------------------------------------------------------------------------
// Type and Structure Declaration
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Extern Global Variabls
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Extern Functions
//------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/// This API is the initialization function for this simple dynamic memory allocation sub-module. This
/// function should be the 1st fucntion called before any other functions in this sub-module called.
/// Also, this function should be called once before upper layer wants to (re-)initialize dynamic memory
/// pool (again). All pointers previously granted by using the allocation function become invalid after
/// this function is called.
/// @param: pAddr: The address of the buffer assigned for dynamic memory pool
/// @param: u32Size: The size of the buffer assigned for dynamic memory pool
/// @return: TRUE if dynamic memory pool is initialized successfully. FALSE if pAddr is NULL or u32Size is too small.
//-------------------------------------------------------------------------------------------------
INTERFACE BOOL msAPI_StillImage_Dlmalloc_InitMemPool(void *pAddr, U32 u32Size);

//-------------------------------------------------------------------------------------------------
/// This API is called for requesting a memory from dynamic memory pool. The caller should check
/// the return value of this function against NULL. If the check stands, no buffer with asked size is
/// allocated for caller. Otherwise, the address of allocated buffer is returned and the caller is free
/// to use the memory. The caller should return the buffer back to dynamic memory pool once the
/// buffer isn't useful any more or memory lackage happens.
/// @param: u32Size: The size of the buffer requested
/// @return: NULL if no buffer with requested size is allocated. Otherwise, the address of the buffer allocated is returned.
//-------------------------------------------------------------------------------------------------
INTERFACE void *msAPI_StillImage_Dlmalloc_Malloc(U32 u32Size);

//-------------------------------------------------------------------------------------------------
/// This API is used to return previously allocated buffer back to dynamic memory pool when isn't
/// used anymore. Return the buffer that isn't allocated by allocation function or return the previously
/// allocated buffer twice could cause problem of the mechanism in this sub-module.
/// @param: pMem: The address of previously allocated buffer.
//-------------------------------------------------------------------------------------------------
INTERFACE void msAPI_StillImage_Dlmalloc_Free(void *pMem);

#undef INTERFACE

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef _MSAPI_STILLIMAGE_DLMALLOC_H_


///*** please do not remove change list tag ***///
///***$Change: 428882 $***///
