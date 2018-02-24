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
// Copyright (c) 2006-2008 MStar Semiconductor, Inc.
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

#ifndef _MSAPI_VDPLAYER_BM_H_
#define _MSAPI_VDPLAYER_BM_H_

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus


//-------------------------------------------------------------------------------------------------
// Project include files:
//-------------------------------------------------------------------------------------------------
#include "../../../../include/datatype.h"
//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
#undef INTERFACE
#ifdef  _MSAPI_VDPLAYER_BM_C_
#define INTERFACE
#else
#define INTERFACE       extern
#endif  // #ifdef  _MSAPI_VDPLAYER_DEMUXER_C_

#define BM_DEFAULT_PRELOAD_SIZE     (0x80000UL)        // Preload after the seek operation.

//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Type and Structure Declaration
//-------------------------------------------------------------------------------------------------
// data type signed int, data length 8 byte
typedef long long           S64;    // 8 bytes
// data type unsigned int, data length 8 byte
typedef unsigned long long  U64;    // 8 bytes

typedef enum
{
    E_BM_FILEPOS_SEEK_CUR,      // Seek from current position of file pointer
    E_BM_FILEPOS_SEEK_SET,      // Seek from the beginning of file.
} EN_BM_FILEPOS;

typedef enum
{
    E_BM_RET_FAIL = 0,
    E_BM_RET_OK,
} EN_BM_RET;

typedef enum
{
    E_BM_AV_HANDLER = 0,
    E_BM_MAX_HANDLER,
} EN_BM_FILE_HANDLER;

typedef struct
{
    U64 u64FileSize;
    U64 u64FilePosition;

    U32 u32BitStreamAddr;
    U32 u32BitStreamSize;
    U32 u32ReservedBuffSize;

    U32 u32BuffActiveAddr;
    U32 u32BuffActiveSize;

    U32 u32DemuxRead_Addr;
    U32 u32DemuxWrite_Addr;
    U32 u32DemuxLower_Addr;
    U32 u32DemuxUpper_Addr;
    U32 u32DemuxBase_Ptr;
    U32 u32DemuxCurrent_Ptr;

    U32 u32DemuxBufTell_Ptr;

    U16 u16DemuxRead_Layer;
    U16 u16DemuxWrite_Layer;
    U16 u16DemuxBase_Layer;
    U16 u16DemuxCurrent_Layer;

    U8  u8FileHdl;
    BOOL    bEOFReached;

    U32 *pItem;
} BM_HANDLER, *PBM_HANDLER;

//-------------------------------------------------------------------------------------------------
// Extern Global Variabls
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Extern Functions
///-------------------------------------------------------------------------------------------------
INTERFACE void  msAPI_VDPlayer_BMInit(U8 u8FileHdl, U64 u64FileSize);
INTERFACE U64   msAPI_VDPlayer_BMFileTell(void);
INTERFACE BOOL  msAPI_VDPlayer_BMFileEOF(void);
INTERFACE U32   msAPI_VDPlayer_BMFileRead(U32 u32Addr, U32 u32Size);
INTERFACE U32   msAPI_VDPlayer_BMReadBytes(U8 u8Bytes);
INTERFACE U32   msAPI_VDPlayer_BMShowBytes(U8 u8Bytes);
INTERFACE U32   msAPI_VDPlayer_BMReadBytes_LE(U8 u8Bytes);
INTERFACE U32   msAPI_VDPlayer_BMShowBytes_LE(U8 u8Bytes);
INTERFACE U32   msAPI_VDPlayer_BMFillBuffer_Custom(U32 u32Size);
INTERFACE U32   msAPI_VDPlayer_BMReadBytes_AutoLoad(U8 nBytes);
INTERFACE U32   msAPI_VDPlayer_BMReadBytes_LE_AutoLoad(U8 nBytes);
INTERFACE U32   msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad(void);
INTERFACE void  msAPI_VDPlayer_BMFlushBytes(U32 u32Bytes);
INTERFACE EN_BM_RET msAPI_VDPlayer_BMFileSeek(U64 u64Offset, EN_BM_FILEPOS ePos);
INTERFACE EN_BM_RET msAPI_VDPlayer_BMBuffer_Configuration(U32 u32BitStreamAddr, U32 u32Size);
INTERFACE EN_BM_RET msAPI_VDPlayer_BMBuffer_Reset(void);
INTERFACE U32   msAPI_VDPlayer_BMBuffer_Remainder(void);
INTERFACE EN_BM_RET msAPI_VDPlayer_BM_SetPreloadSize(U32 u32Size);
#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef _MSAPI_VDPLAYER_BM_H_

