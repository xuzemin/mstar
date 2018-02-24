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
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// @file
// @brief
// @author MStarSemi Inc.
//
//-
//-
//
////////////////////////////////////////////////////////////////////////////////

#ifndef MSAPI_FS_SYSINFO_H
#define MSAPI_FS_SYSINFO_H

#include "Board.h"
#include "datatype.h"

#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include <stdio.h>
#include <string.h>
#include "sysinfo.h"

#include "hwreg.h"


#ifndef FILE_SYSTEM_SMALL
#define FILE_SYSTEM_SMALL 0
#endif


#ifndef FAT_READ_ONLY
#define FAT_READ_ONLY 1
#endif

#ifndef FILE_SYSTEM_WRITE_ENABLE
    #if ENABLE_DMP
#define FILE_SYSTEM_WRITE_ENABLE 1
    #else
    #if ENABLE_SZ_FACTORY_USB_SAVE_DATABASE_FUNCTION
        #define FILE_SYSTEM_WRITE_ENABLE 1
    #else
        #define FILE_SYSTEM_WRITE_ENABLE 1//0
    #endif
#endif
#endif

#ifndef ENABLE_N51FS
    #if ENABLE_DMP
#define ENABLE_N51FS 1
    #else
#define ENABLE_N51FS 1//0
    #endif
#endif

#ifndef FAT_CACHE_PREV_ENABLE
#define FAT_CACHE_PREV_ENABLE 0
#endif

#if 0//ndef ENABLE_DREC
#define ENABLE_DREC 0
#endif

#if ENABLE_PVR
#define FILE_SYSTEM_FOLDER_CREATE_ENABLE    1
#define ENABLE_BULK_FILE_SYSTEM             1
#else
#define FILE_SYSTEM_FOLDER_CREATE_ENABLE    1
#define ENABLE_BULK_FILE_SYSTEM             0
#endif

//#ifndef MPLAYER_USE_FILEENTRY
//  #ifndef FILE_SYSTEM_GET_FILENAME_BY_FILEENTRY_ENABLE
//    #define FILE_SYSTEM_GET_FILENAME_BY_FILEENTRY_ENABLE 0
//  #endif
//#else
    #define FILE_SYSTEM_GET_FILENAME_BY_FILEENTRY_ENABLE 1
//#endif


#if !FILE_SYSTEM_GET_FILENAME_BY_FILEENTRY_ENABLE
  #ifndef FILE_SYSTEM_SEARCH_BY_SHORT_NAME_ENABLE
    #define FILE_SYSTEM_SEARCH_BY_SHORT_NAME_ENABLE 0
  #elif FILE_SYSTEM_SEARCH_BY_SHORT_NAME_ENABLE
    #error "Conflict N51FS Compile Setting!!"
  #endif
#endif


#define FS_KEEP_UNUSED 0

#define GET_DRAM_ADDR(x) (U32)(x)

#ifdef MSAPI_FS_SYSINFO_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

INTERFACE void msAPI_FS_Init(void);

INTERFACE void FS_MEM_Dump(void *ptr,U8 *str);
INTERFACE void *msAPI_FS_Memory_Allocate(U16 u16Number_of_bytes);
INTERFACE void msAPI_FS_Memory_Free(void * pMem);
INTERFACE void msAPI_FS_MIU_Copy(U32 srcaddr, U32 dstaddr, U32 len);
INTERFACE void msAPI_FS_MIU_Copy_I(U32 srcaddr, U32 dstaddr, U32 len);
INTERFACE void FS_RESET_WDT(void);

#if 0
INTERFACE U32 GET_DRAM_ADDR(void *x);
#endif

#undef INTERFACE
#endif
