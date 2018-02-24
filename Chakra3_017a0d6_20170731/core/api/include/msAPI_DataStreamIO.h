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
///////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2010 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _MSAPI_DATA_STREAM_IO_H_
#define _MSAPI_DATA_STREAM_IO_H_

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

///////////////////////////////////////////////////////////////////////////////
/// @file   msAPI_DataStreamIO.h
/// This file contains the interface of data stream I/O
/// @author MStar Semiconductor Inc.
/// @brief  APIs for data stream I/O
///////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// Include Files
//------------------------------------------------------------------------------
#include "MsCommon.h"

#include "msAPI_FSCommon.h" // for LongLong

//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
#undef INTERFACE
#ifdef _MSAPI_DATA_STREAM_IO_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif // #ifdef _MSAPI_DATA_STREAM_IO_C_

//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Type and Structure Declaration
//------------------------------------------------------------------------------
#define INVALID_DATA_STREAM_HDL (0xffffffff)

typedef enum
{
    E_DATA_STREAM_SEEK_SET    = 0,
    E_DATA_STREAM_SEEK_CUR    = 1,
} E_DATA_STREAM_SEEK_OPTION;

typedef enum
{
    E_DATA_STREAM_TYPE_IGNORE     = 0,

    E_DATA_STREAM_TYPE_PHOTO,

    E_DATA_STREAM_TYPE_MUSIC,
    E_DATA_STREAM_TYPE_MUSIC2,
    E_DATA_STREAM_TYPE_LYRIC,

    E_DATA_STREAM_TYPE_VIDEO,
    E_DATA_STREAM_TYPE_AUDIO,
    E_DATA_STREAM_TYPE_IN_SUB,
    E_DATA_STREAM_TYPE_EX_SUB0,
    E_DATA_STREAM_TYPE_EX_SUB1,
    E_DATA_STREAM_TYPE_ATTACHMENT,

    E_DATA_STREAM_TYPE_NUM,
} E_DATA_STREAM_TYPE;

typedef enum
{
    E_DATA_STREAM_MODE_BASIC    = 0,
    E_DATA_STREAM_MODE_SEAMLESS,
    E_DATA_STREAM_MODE_BUFFER_MANAGEMENT,
#if ENABLE_POWERON_VIDEO
    E_DATA_STREAM_MODE_POWER_ON_VIDEO,
#endif
    E_DATA_STREAM_MODE_NUM,
} E_DATA_STREAM_MODE;

typedef struct
{
    BOOLEAN     (*pfnInit)  (void);
    BOOLEAN     (*pfnFinalize)  (void);
    U32         (*pfnOpen)  (void *pPrivate, U8 u8Mode, E_DATA_STREAM_TYPE eType);
    BOOLEAN     (*pfnClose) (U32 u32Hdl);
    U32         (*pfnRead)  (U32 u32Hdl, void *pBuffAddr, U32 u32Length);
    BOOLEAN     (*pfnSeek)  (U32 u32Hdl, LongLong u64Pos, E_DATA_STREAM_SEEK_OPTION eOption);
    LongLong    (*pfnTell)  (U32 u32Hdl);
    LongLong    (*pfnLength)    (U32 u32Hdl);
} FN_DATA_STRM_IO;

//------------------------------------------------------------------------------
// Extern Global Variabls
//------------------------------------------------------------------------------
INTERFACE U32       msAPI_DataStreamIO_Open(void *pPrivate, U8 u8Mode, E_DATA_STREAM_TYPE eType);
INTERFACE BOOLEAN   msAPI_DataStreamIO_Close(U32 u32Hdl);
INTERFACE U32       msAPI_DataStreamIO_Read(U32 u32Hdl, void *pBuffAddr, U32 u32Length);
INTERFACE BOOLEAN   msAPI_DataStreamIO_Seek(U32 u32Hdl, U32 u32Pos, E_DATA_STREAM_SEEK_OPTION eOption);
INTERFACE BOOLEAN   msAPI_DataStreamIO_Seek_LongLong(U32 u32Hdl, LongLong u64Pos, E_DATA_STREAM_SEEK_OPTION option);
INTERFACE U32       msAPI_DataStreamIO_Tell(U32 u32Hdl);
INTERFACE LongLong  msAPI_DataStreamIO_Tell_LongLong(U32 u32Hdl);
INTERFACE U32       msAPI_DataStreamIO_Length(U32 u32Hdl);
INTERFACE LongLong  msAPI_DataStreamIO_Length_LongLong(U32 u32Hdl);

INTERFACE BOOLEAN   msAPI_DataStreamIO_OptionRegistation(FN_DATA_STRM_IO *pfnIO, E_DATA_STREAM_MODE eMode);
INTERFACE BOOLEAN   msAPI_DataStreamIO_SetStreamMode(E_DATA_STREAM_MODE eMode);
INTERFACE E_DATA_STREAM_MODE msAPI_DataStreamIO_GetStreamMode(void);

//------------------------------------------------------------------------------
// Extern Functions
//------------------------------------------------------------------------------

#undef INTERFACE

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef _MSAPI_DATA_STREAM_IO_H_


