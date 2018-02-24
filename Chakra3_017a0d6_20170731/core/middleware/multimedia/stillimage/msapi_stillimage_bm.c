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

#define _MSAPI_STILLIMAGE_BM_C_

//------------------------------------------------------------------------------
// Include Files
//------------------------------------------------------------------------------
//#include "mm_common.h"           // Every source code should include this in the first line
#include <string.h>
#include "MsOS.h"

#include "msapi_stillimage_defines.h"

#include "msapi_stillimage_bm.h"

//------------------------------------------------------------------------------
// Type and Structure Declaration
//------------------------------------------------------------------------------
#define BM_RESERVED_ES_BUF_SIZE     (0x0)

#define UN_WRAP_LOOP    (1) // unwarp for loop to improve performance

typedef enum
{
    E_BM_NON_BLOCKING_READ_DONE       = BIT0,
    E_BM_NON_BLOCKING_READ_CANCELED   = BIT1,
    E_BM_NON_BLOCKING_SEEK_DONE       = BIT2,
} EN_BM_FLAGS;

#define IS_NONBLOCKING_READ_DONE(eBmFlag) \
    ((eBmFlag & E_BM_NON_BLOCKING_READ_DONE) == E_BM_NON_BLOCKING_READ_DONE ? TRUE : FALSE)
#define IS_NONBLOCKING_READ_CANCELED(eBmFlag) \
    ((eBmFlag & E_BM_NON_BLOCKING_READ_CANCELED) == E_BM_NON_BLOCKING_READ_CANCELED ? TRUE : FALSE)
#define IS_NONBLOCKING_SEEK_DONE(eBmFlag) \
    ((eBmFlag & E_BM_NON_BLOCKING_SEEK_DONE) == E_BM_NON_BLOCKING_SEEK_DONE ? TRUE : FALSE)

typedef struct
{
    U8 u8FileHdl;
    U64 u64FileSize;
    U64 u64FilePosition;

    U32 u32Buff_Addr;
    U32 u32Buff_Size;

    U32 u32BuffReserved_Size;

    U32 u32BuffActive_Addr;
    U32 u32BuffActive_Size;

    U32 u32BuffRead_Addr;
    U32 u32BuffWrite_Addr;
    U32 u32BuffLower_Addr;
    U32 u32BuffUpper_Addr;
    U32 u32BuffCurrent_Ptr;

    U16 u16BuffRead_Layer;
    U16 u16BuffWrite_Layer;
    U16 u16BuffCurrent_Layer;
#if (ENABLE_BM_READ_4KALIGNMENT)
    U16 u16RedundantSize;
#endif // #if (ENABLE_BM_READ_4KALIGNMENT)

    BOOL    bEOFReached;

    U32     enFlags;
    U32     u32NonBlockingOpStartTime;
    U32     u32RequestSize;

    ST_STILLIMAGE_DATA_IO_FUNC stDataIoFuncs;
} ST_BM_HANDLER, *PST_BM_HANDLER;

//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------
#ifndef MIN
#define MIN(a, b)   ((a) < (b) ? (a) : (b))
#endif // #ifndef MIN

#define SI_BM_DBG(x)        //x
#define SI_BM_INFO(x)       x
#define SI_BM_INFO_MUST(x)  x
#define SI_BM_ERR(x)        x

//------------------------------------------------------------------------------
// Global Variables
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Local Variables
//------------------------------------------------------------------------------
static ST_BM_HANDLER stBM_Handler;
static PST_BM_HANDLER pstBM_Handler = &stBM_Handler;

static U32 u32PreLoadSize;
//------------------------------------------------------------------------------
// Local Function Prototype
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local Function Implementation
//------------------------------------------------------------------------------
static inline U8 _msAPI_StillImage_BM_GetData(U32 u32Idx)
{
    return *((U8*)(pstBM_Handler->u32Buff_Addr + u32Idx));
}

static inline void _msAPI_StillImage_BMBuff_UpdateCurrentPtr(U32 u32Cnt)
{
    pstBM_Handler->u32BuffCurrent_Ptr += u32Cnt;
    while (pstBM_Handler->u32BuffCurrent_Ptr >= pstBM_Handler->u32BuffUpper_Addr)
    {
        pstBM_Handler->u32BuffCurrent_Ptr -= pstBM_Handler->u32BuffActive_Size;
        pstBM_Handler->u16BuffCurrent_Layer++;
    }
}

static inline void _msAPI_StillImage_BMBuff_UpdateWriteAddr(U32 u32Cnt)
{
    pstBM_Handler->u32BuffWrite_Addr += u32Cnt;
    while (pstBM_Handler->u32BuffWrite_Addr >= pstBM_Handler->u32BuffUpper_Addr)
    {
        pstBM_Handler->u32BuffWrite_Addr -= pstBM_Handler->u32BuffActive_Size;
        pstBM_Handler->u16BuffWrite_Layer++;
    }
}

static inline void _msAPI_StillImage_BMBuff_UpdateReadAddr(U32 u32Cnt)
{
    pstBM_Handler->u32BuffRead_Addr += u32Cnt;
    while (pstBM_Handler->u32BuffRead_Addr >= pstBM_Handler->u32BuffUpper_Addr)
    {
        pstBM_Handler->u32BuffRead_Addr -= pstBM_Handler->u32BuffActive_Size;
        pstBM_Handler->u16BuffRead_Layer++;
    }
}

//------------------------------------------------------------------------------
// Global Function Implementation
//------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/// The API is used as a chance to BM variables.
/// @param: None
/// @return: None
///
//-------------------------------------------------------------------------------------------------
void msAPI_StillImage_BM_Init(void)
{
    memset(&stBM_Handler, 0x0, sizeof(stBM_Handler));

#if (ENABLE_BM_READ_4KALIGNMENT)
    stBM_Handler.u16RedundantSize = 0;
#endif // #if (ENABLE_BM_READ_4KALIGNMENT)

    u32PreLoadSize = BM_DEFAULT_PRELOAD_SIZE;
    pstBM_Handler = &stBM_Handler;
}

//-------------------------------------------------------------------------------------------------
/// The API is used set desired IO functio to BM.
/// @param: None
/// @return: TRUE/FALSE
///
//-------------------------------------------------------------------------------------------------
EN_BM_RET msAPI_StillImage_BM_SetIO(PST_STILLIMAGE_DATA_IO_FUNC pstDataIoFuncs)
{
    if(pstDataIoFuncs->pfStillImage_DataIO_Open == NULL
    || pstDataIoFuncs->pfStillImage_DataIO_Close == NULL
    || pstDataIoFuncs->pfStillImage_DataIO_Read == NULL
    || pstDataIoFuncs->pfStillImage_DataIO_Seek == NULL)
    {
        return E_BM_RET_FAIL;
    }
    
    pstBM_Handler->stDataIoFuncs = *pstDataIoFuncs;
    return E_BM_RET_OK;
}

//-------------------------------------------------------------------------------------------------
/// Set the size for automatic preload action.
/// @param: u32Size, Wanted preload size.
/// @return:  E_BM_RET_OK or E_BM_RET_FAIL
///
//-------------------------------------------------------------------------------------------------
EN_BM_RET msAPI_StillImage_BM_SetPreloadSize(U32 u32Size)
{
    u32PreLoadSize = u32Size;
    return E_BM_RET_OK;
}

//-------------------------------------------------------------------------------------------------
/// Get the size for automatic preload action.
/// @param: None
/// @return:  u32Size, Current preload size
///
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_BM_GetPreloadSize(void)
{
    return u32PreLoadSize;
}

//-------------------------------------------------------------------------------------------------
/// The API provides to open the data input stream.
/// @param: None
/// @return:  E_BM_RET_OK or E_BM_RET_FAIL
///
//-------------------------------------------------------------------------------------------------
EN_BM_RET msAPI_StillImage_BMFile_Open(void)
{
    pstBM_Handler->stDataIoFuncs.pfStillImage_DataIO_Open(&pstBM_Handler->u64FileSize, &pstBM_Handler->u8FileHdl);
    pstBM_Handler->u64FilePosition = 0;
    pstBM_Handler->bEOFReached = FALSE;

    if (pstBM_Handler->u8FileHdl == INVALID_HDL)
    {
        return E_BM_RET_FAIL;
    }

    return E_BM_RET_OK;
}

//-------------------------------------------------------------------------------------------------
/// The API provides to close data input stream.
/// @param: None
/// @return:  E_BM_RET_OK or E_BM_RET_FAIL
///
//-------------------------------------------------------------------------------------------------
EN_BM_RET msAPI_StillImage_BMFile_Close(void)
{
    pstBM_Handler->stDataIoFuncs.pfStillImage_DataIO_Close(pstBM_Handler->u8FileHdl);

    pstBM_Handler->bEOFReached = TRUE;
    pstBM_Handler->u64FilePosition = U64_MAX;

    return E_BM_RET_OK;
}

//-------------------------------------------------------------------------------------------------
/// The API provides to get the total size of input stream.
/// @param: None
/// @return: the size in byte of input stream
///
//-------------------------------------------------------------------------------------------------
U64 msAPI_StillImage_BMFile_Size(void)
{
    return pstBM_Handler->u64FileSize;
}

//-------------------------------------------------------------------------------------------------
/// The API provides to set the total size of input stream.
/// @param: the size in byte of input stream
/// @return: None
///
//-------------------------------------------------------------------------------------------------
void msAPI_StillImage_BMFile_SetSize(U64 u64Size)
{
    pstBM_Handler->u64FileSize = u64Size;
}

//-------------------------------------------------------------------------------------------------
/// The API provides to get the current position of the file.
/// @param: None
/// @return:  The current file position
///
//-------------------------------------------------------------------------------------------------
U64 msAPI_StillImage_BMFile_Tell(void)
{
    return (pstBM_Handler->u64FilePosition - msAPI_StillImage_BMBuffer_Remainder());
}

//-------------------------------------------------------------------------------------------------
/// The API provides to test for end-of-file on a stream.
/// @param: None
/// @return:  TRUE or FALSE
///
//-------------------------------------------------------------------------------------------------
BOOL msAPI_StillImage_BMFile_EOF(void)
{
    if ((pstBM_Handler->bEOFReached == TRUE)
            && ((pstBM_Handler->u32BuffCurrent_Ptr == pstBM_Handler->u32BuffWrite_Addr)
                    && (pstBM_Handler->u16BuffCurrent_Layer == pstBM_Handler->u16BuffWrite_Layer)))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

//-------------------------------------------------------------------------------------------------
/// The API provides to fill data into input buffer immediately.
/// It will return the number of actually read,
/// which may be less than count if an error occurs or if the end of the file is encountered before reaching count.
/// The operation will abort any non-blocking read and will do the block read till the ack of input mechanism.
/// It must be care to use. In order avoiding to trap into the API, it will design with time-out control.
/// @param: u32Size: Fill u32Size bytes of data into input buffer immediately
/// @return:  The number of actually read
///
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_BMFile_Read(U32 u32Addr, U32 u32Size)
{
    U32 read_size = 0;

    if (u32Size == 0)
    {
        return 0;
    }

    read_size = pstBM_Handler->stDataIoFuncs.pfStillImage_DataIO_Read(pstBM_Handler->u8FileHdl, MsOS_VA2PA(u32Addr), u32Size);
    read_size = u32Size - read_size;
    pstBM_Handler->u64FilePosition += read_size;
    return read_size;
}

//-------------------------------------------------------------------------------------------------
/// The API provides to read data into input buffer in a non-blocking way. After data has been filled
/// msAPI_StillImage_BMFile_NonBlockingReadDone() to be called as an indication that the last
/// non-blocking read is done.
/// @param: u32Address: The start address for this non-blocking read operation.
/// @param: u32Size: Number of bytes to read.
/// @return: None
///
//-------------------------------------------------------------------------------------------------
void msAPI_StillImage_BMFile_NonBlockingRead(U32 u32Address, U32 u32Size)
{
    UNUSED(u32Address);
    UNUSED(u32Size);
}

//-------------------------------------------------------------------------------------------------
/// The API provides to update all information after received the NonBlocking file read ACK which
/// issued by File system.
/// Note that this function can not be called in software interrupt
/// @param: u8FileHdl: The file handle sent with non-blocking read.
/// @param: u32LeftUnRead: The difference in byte between requested size and the real read size.
/// @return: None
///
//-------------------------------------------------------------------------------------------------
void msAPI_StillImage_BMFile_NonBlockingReadDone(U8 u8FileHdl, U32 u32LeftUnRead)
{
    UNUSED(u8FileHdl);
    UNUSED(u32LeftUnRead);
}

//-------------------------------------------------------------------------------------------------
/// The API provides to do seek operation at the file range.
/// If it is out of file range, the position will move to the end of file.
/// After seeking, the API will preload some data (BM_DEFAULT_PRELOAD_SIZE) into Demux buffer.
/// @param: U64Offset: Number of bytes from ePos
/// @param: ePos: Initial position
/// @return:  E_BM_RET_OK or E_BM_RET_FAIL
///
//-------------------------------------------------------------------------------------------------
EN_BM_RET msAPI_StillImage_BMFile_Seek(U64 u64Offset, EN_BM_FILEPOS ePos)
{
    S32 s32Remainder;

    if (E_BM_FILEPOS_SEEK_CUR == ePos)
    {
        u64Offset = msAPI_StillImage_BMFile_Tell() + u64Offset;
    }

    if (u64Offset >= pstBM_Handler->u64FileSize)
    {
        u64Offset = pstBM_Handler->u64FileSize;
    }

    // check if data already in buffer
    s32Remainder = pstBM_Handler->u32BuffActive_Size - msAPI_StillImage_BMBuffer_SpaceLeft();

    if ((u64Offset  >= (pstBM_Handler->u64FilePosition - s32Remainder))
            && (u64Offset < pstBM_Handler->u64FilePosition))
    {
        s32Remainder -= (S32)(pstBM_Handler->u64FilePosition - u64Offset);

        _msAPI_StillImage_BMBuff_UpdateReadAddr(s32Remainder);

        pstBM_Handler->u32BuffCurrent_Ptr = pstBM_Handler->u32BuffRead_Addr;
        pstBM_Handler->u16BuffCurrent_Layer = pstBM_Handler->u16BuffRead_Layer;
        return E_BM_RET_OK;
    }

    msAPI_StillImage_BMBuffer_Reset();

#if (ENABLE_BM_READ_4KALIGNMENT)
    pstBM_Handler->u16RedundantSize = (U16)(u64Offset - (u64Offset & ~0xFFF));
    u64Offset = u64Offset & ~0xFFF;
#endif // #if (ENABLE_BM_READ_4KALIGNMENT)

    pstBM_Handler->stDataIoFuncs.pfStillImage_DataIO_Seek(pstBM_Handler->u8FileHdl, u64Offset);

    if (u64Offset < pstBM_Handler->u64FileSize)
    {
        pstBM_Handler->bEOFReached = FALSE;
    }
    else
    {
        pstBM_Handler->bEOFReached = TRUE;
    }

    pstBM_Handler->u64FilePosition = u64Offset;

    return E_BM_RET_OK;
}

//-------------------------------------------------------------------------------------------------
/// The API provides to update all information after received the NonBlocking file seek ACK which
/// issued by File system.
/// Note that this function can not be called in software interrupt
/// @param: u8FileHdl: The file handle sent with non-blocking read.
/// @return: None
///
//-------------------------------------------------------------------------------------------------
void msAPI_StillImage_BMFile_NonBlockingSeekDone(U8 u8FileHdl)
{
    UNUSED(u8FileHdl);
}

//-------------------------------------------------------------------------------------------------
/// BUFFER MANAGEMENT APIs for data I/O.
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
/// The API is used to configure the Buffer location and its range.
/// After configuration, all relative information will be reset to default.
/// @param: u32Lower, The Lower boundary of buffer
/// @param: u32Upper, The Upper boundary of buffer
/// @return: E_BM_RET_OK or E_BM_RET_FAIL
///
//-------------------------------------------------------------------------------------------------
EN_BM_RET msAPI_StillImage_BMBuffer_Configuration(U32 u32Lower, U32 u32Upper)
{
    if ((u32Lower >= u32Upper)
        || (u32Upper - u32Lower < 4))
    {
        return E_BM_RET_FAIL;
    }

    pstBM_Handler->u32Buff_Addr = u32Lower;
    pstBM_Handler->u32Buff_Size = u32Upper - u32Lower;
    pstBM_Handler->u32BuffReserved_Size = BM_RESERVED_ES_BUF_SIZE;
    pstBM_Handler->u32BuffActive_Addr = u32Lower + BM_RESERVED_ES_BUF_SIZE;
    pstBM_Handler->u32BuffActive_Size = (u32Upper - u32Lower) - BM_RESERVED_ES_BUF_SIZE;

    return E_BM_RET_OK;
}

//-------------------------------------------------------------------------------------------------
/// Get real active buffer size used for input data.
/// @param: None
/// @return: size of active buffer
///
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_BMBuffer_ActiveBuffSize(void)
{
    return (pstBM_Handler->u32Buff_Size - pstBM_Handler->u32BuffReserved_Size);
}

//-------------------------------------------------------------------------------------------------
/// It just shows N bytes of data from input buffer but doesn't flush it.
/// If in-sufficient data is available, no auto load happens.
/// @param: u8NBytes: Read N(0~4) bytes by big endian from input buffer.
/// @return: The value of the data in input buffer
///
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_BMBuffer_ShowBytes(U8 u8NBytes)
{
    U32 u32Val, u32ToEnd, u32BuffCurrent_Ptr;
    U8 idx, u8Byte[4] = {0, 0, 0, 0};

    if ((0 == u8NBytes) || (4 < u8NBytes))
    {
        return 0;
    }

    u32ToEnd = pstBM_Handler->u32BuffUpper_Addr - pstBM_Handler->u32BuffCurrent_Ptr;
    u32BuffCurrent_Ptr = pstBM_Handler->u32BuffCurrent_Ptr;

    if (u32ToEnd > u8NBytes)
    {
#if UN_WRAP_LOOP
        switch (u8NBytes)
        {
            default:
            case 4:
                u8Byte[3] = *((U8*)(pstBM_Handler->u32Buff_Addr + u32BuffCurrent_Ptr + 3));
                u8Byte[2] = *((U8*)(pstBM_Handler->u32Buff_Addr + u32BuffCurrent_Ptr + 2));
                u8Byte[1] = *((U8*)(pstBM_Handler->u32Buff_Addr + u32BuffCurrent_Ptr + 1));
                u8Byte[0] = *((U8*)(pstBM_Handler->u32Buff_Addr + u32BuffCurrent_Ptr + 0));
                return (U32)u8Byte[3] | ((U32)u8Byte[2] << 8) | ((U32)u8Byte[1] << 16) | ((U32)u8Byte[0] << 24);

            case 3:
                u8Byte[2] = *((U8*)(pstBM_Handler->u32Buff_Addr + u32BuffCurrent_Ptr + 2));
                u8Byte[1] = *((U8*)(pstBM_Handler->u32Buff_Addr + u32BuffCurrent_Ptr + 1));
                u8Byte[0] = *((U8*)(pstBM_Handler->u32Buff_Addr + u32BuffCurrent_Ptr + 0));
                return (U32)u8Byte[2] | ((U32)u8Byte[1] << 8) | ((U32)u8Byte[0] << 16);

            case 2:
                u8Byte[1] = *((U8*)(pstBM_Handler->u32Buff_Addr + u32BuffCurrent_Ptr + 1));
                u8Byte[0] = *((U8*)(pstBM_Handler->u32Buff_Addr + u32BuffCurrent_Ptr + 0));
                return (U32)u8Byte[1] | ((U32)u8Byte[0] << 8);

            case 1:
                u8Byte[0] = *((U8*)(pstBM_Handler->u32Buff_Addr + u32BuffCurrent_Ptr + 0));
                return (U32)u8Byte[0];
        }
#else // #if UN_WRAP_LOOP

        for (idx = 0; idx < u8NBytes; idx++)
        {
            u8Byte[idx] = _msAPI_StillImage_BM_GetData(u32BuffCurrent_Ptr++);
        }
#endif // #if UN_WRAP_LOOP
    }
    else
    {
        for (idx = 0; idx < u32ToEnd; idx++)
        {
            u8Byte[idx] = _msAPI_StillImage_BM_GetData(u32BuffCurrent_Ptr++);
        }

        u32BuffCurrent_Ptr -= pstBM_Handler->u32BuffActive_Size;

        for ( ; idx < u8NBytes; idx++)
        {
            u8Byte[idx] = _msAPI_StillImage_BM_GetData(u32BuffCurrent_Ptr++);
        }
    }

    for (u32Val = 0, idx = 0; idx < u8NBytes; idx++)
    {
        u32Val = (u32Val << 8) + u8Byte[idx];
    }

    return u32Val;
 }

//-------------------------------------------------------------------------------------------------
/// It will get N bytes of data from input buffer, and flush N bytes automatically.
/// If in-sufficient data is available, no auto load happens.
/// @param: u8NBytes: Read N(0~4) bytes by big endian from input buffer
/// @return: The value of the data in input buffer
///
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_BMBuffer_ReadBytes(U8 u8NBytes)
{
    U32 u32Val;

    if ((0 == u8NBytes) || (4 < u8NBytes))
    {
        return 0;
    }

    u32Val = msAPI_StillImage_BMBuffer_ShowBytes(u8NBytes);
    _msAPI_StillImage_BMBuff_UpdateCurrentPtr(u8NBytes);

    return u32Val;
 }

//-------------------------------------------------------------------------------------------------
/// It just shows N bytes of data from input buffer, and doesn't flush it.
/// If in-sufficient data is available, no auto load happens.
/// @param: u8NBytes: Read N(0~4) bytes by little endian from input buffer.
/// @return: The value of the data in input buffer
///
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_BMBuffer_ShowBytes_LE(U8 u8NBytes)
{
    U32 u32ToEnd, u32BuffCurrent_Ptr;
    U8 idx, u8Byte[4] = {0, 0, 0, 0};

    if ((0 == u8NBytes) || (4 < u8NBytes))
    {
        return 0;
    }

    u32ToEnd = pstBM_Handler->u32BuffUpper_Addr - pstBM_Handler->u32BuffCurrent_Ptr;
    u32BuffCurrent_Ptr = pstBM_Handler->u32BuffCurrent_Ptr;

    if (u32ToEnd > u8NBytes)
    {
#if UN_WRAP_LOOP
        switch (u8NBytes)
        {
            default:
            case 4:
                u8Byte[3] = *((U8*)(pstBM_Handler->u32Buff_Addr + u32BuffCurrent_Ptr + 3));
                // fall through

            case 3:
                u8Byte[2] = *((U8*)(pstBM_Handler->u32Buff_Addr + u32BuffCurrent_Ptr + 2));
                // fall through

            case 2:
                u8Byte[1] = *((U8*)(pstBM_Handler->u32Buff_Addr + u32BuffCurrent_Ptr + 1));
                // fall through

            case 1:
                u8Byte[0] = *((U8*)(pstBM_Handler->u32Buff_Addr + u32BuffCurrent_Ptr + 0));
                break;
        }

        return (U32)u8Byte[0] | ((U32)u8Byte[1] << 8) | ((U32)u8Byte[2] << 16) | ((U32)u8Byte[3] << 24);
#else // #if UN_WRAP_LOOP

        for (idx = 0; idx < u8NBytes; idx++)
        {
            u8Byte[idx] = _msAPI_StillImage_BM_GetData(u32BuffCurrent_Ptr++);
        }
#endif // #if UN_WRAP_LOOP
    }
    else
    {
        for (idx = 0; idx < u32ToEnd; idx++)
        {
            u8Byte[idx] = _msAPI_StillImage_BM_GetData(u32BuffCurrent_Ptr++);
        }

        u32BuffCurrent_Ptr -= pstBM_Handler->u32BuffActive_Size;

        for ( ; idx < u8NBytes; idx++)
        {
            u8Byte[idx] = _msAPI_StillImage_BM_GetData(u32BuffCurrent_Ptr++);
        }
    }

    return (U32)u8Byte[0] | ((U32)u8Byte[1] << 8) | ((U32)u8Byte[2] << 16) | ((U32)u8Byte[3] << 24);
}

//-------------------------------------------------------------------------------------------------
/// It will get N bytes of data from input buffer, and flush N bytes automatically.
/// If in-sufficient data is available, no auto load happens.
/// @param: u8NBytes: Read N(0~4) bytes by little endian from input buffer.
/// @return: The value of the data in input buffer
///
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_BMBuffer_ReadBytes_LE(U8 u8NBytes)
{
    U32 u32Val;

    if ((0 == u8NBytes) || (4 < u8NBytes))
    {
        return 0;
    }

    u32Val = msAPI_StillImage_BMBuffer_ShowBytes_LE(u8NBytes);
    _msAPI_StillImage_BMBuff_UpdateCurrentPtr(u8NBytes);

    return u32Val;
}

//-------------------------------------------------------------------------------------------------
/// This function fill at least the amount of data requested or the space left in buffer, depending
/// on which one is smaller.
/// @param: u32Size: The bytes of data requested by caller.
/// @return: the amount of data really filled.
///
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_BMBuffer_CustomFill(U32 u32Size)
{
    U64 val = 0;
    U32 u32FillSize;
    S32 s32Space;

    if (pstBM_Handler->bEOFReached == TRUE)
    {
        return 0;
    }

    pstBM_Handler->u32BuffRead_Addr = pstBM_Handler->u32BuffCurrent_Ptr;
    pstBM_Handler->u16BuffRead_Layer = pstBM_Handler->u16BuffCurrent_Layer;

    s32Space = msAPI_StillImage_BMBuffer_SpaceLeft();
    if (s32Space <= 4)
    {
        return 0;
    }

    // Modified u32Size based on remaining buffer size information
    u32Size = MIN(u32Size, (U32)(s32Space));

    // Modified u32Size based on remaining file data information
    val = pstBM_Handler->u64FileSize - pstBM_Handler->u64FilePosition;

    if ((u32u64_1(val) == 0) && (u32Size > u32u64_0(val)))
    {
        u32Size = u32u64_0(val);
        pstBM_Handler->bEOFReached = TRUE;
    }

    if(u32Size == 0)
    {
        return 0;
    }

    // Fill u32Size data to Buffer
    u32FillSize = 0;
    if(pstBM_Handler->u32BuffWrite_Addr < pstBM_Handler->u32BuffRead_Addr)
    {
        u32FillSize += msAPI_StillImage_BMFile_Read(pstBM_Handler->u32Buff_Addr + pstBM_Handler->u32BuffWrite_Addr, u32Size);
    }
    else
    {
        U32 u32ToEnd = 0;

        u32ToEnd = (pstBM_Handler->u32BuffUpper_Addr - pstBM_Handler->u32BuffWrite_Addr);
        if (u32Size <= u32ToEnd)
        {
            u32FillSize += msAPI_StillImage_BMFile_Read(pstBM_Handler->u32Buff_Addr + pstBM_Handler->u32BuffWrite_Addr, u32Size);
        }
        else if (u32Size > u32ToEnd)
        {
            u32FillSize += msAPI_StillImage_BMFile_Read(pstBM_Handler->u32Buff_Addr + pstBM_Handler->u32BuffWrite_Addr, u32ToEnd);
            u32FillSize += msAPI_StillImage_BMFile_Read(pstBM_Handler->u32BuffActive_Addr, u32Size - u32ToEnd);
        }
    }

    _msAPI_StillImage_BMBuff_UpdateWriteAddr(u32FillSize);

#if (ENABLE_BM_READ_4KALIGNMENT)
    if (pstBM_Handler->u16RedundantSize != 0)
    {
        U32 u32FlushSize;

        if (pstBM_Handler->u16RedundantSize >= u32FillSize)
        {
            u32FlushSize = u32FillSize;
        }
        else
        {
            u32FlushSize = pstBM_Handler->u16RedundantSize;
        }

        pstBM_Handler->u16RedundantSize -= u32FlushSize;
        u32FillSize -= u32FlushSize;
        _msAPI_StillImage_BMBuff_UpdateCurrentPtr(u32FlushSize);
    }
#endif // #if (ENABLE_BM_READ_4KALIGNMENT)

    return u32FillSize;
}

//-------------------------------------------------------------------------------------------------
/// It just shows N bytes of data from input buffer, and doesn't flush it.
/// If in-sufficient data is available, auto load happens.
/// @param: u8NBytes: Read N(0~4) bytes by big endian from input buffer.
/// @return: The value of the data in input buffer
///
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_BMBuffer_ReadBytes_AutoLoad(U8 u8NBytes)
{
    U32 u32Remainder;

    if ((0 == u8NBytes) || (4 < u8NBytes))
    {
        return 0;
    }

    u32Remainder = msAPI_StillImage_BMBuffer_Remainder();
    if (u8NBytes > u32Remainder)
    {
        if (msAPI_StillImage_BMBuffer_CustomFill(u32PreLoadSize) < (U32)(u8NBytes - u32Remainder))
        {
            SI_BM_ERR(printf("No more bits!!\n"));
            return U32_MAX;
        }
    }

    return msAPI_StillImage_BMBuffer_ReadBytes(u8NBytes);
}

//-------------------------------------------------------------------------------------------------
/// It just shows N bytes of data from input buffer, and doesn't flush it.
/// If in-sufficient data is available, auto load happens.
/// @param: u8NBytes: Read N(0~4) bytes by little endian from input buffer.
/// @return: The value of the data in input buffer
///
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_BMBuffer_ReadBytes_LE_AutoLoad(U8 u8NBytes)
{
    U32 u32Remainder;

    if ((0 == u8NBytes) || (4 < u8NBytes))
    {
        return 0;
    }

    u32Remainder = msAPI_StillImage_BMBuffer_Remainder();
    if (u8NBytes > u32Remainder)
    {
        if (msAPI_StillImage_BMBuffer_CustomFill(u32PreLoadSize) < (U32)(u8NBytes - u32Remainder))
        {
            SI_BM_ERR(printf("No more bits!!\n"));
            return U32_MAX;
        }
    }

    return msAPI_StillImage_BMBuffer_ReadBytes_LE(u8NBytes);
}

//-------------------------------------------------------------------------------------------------
/// It just shows u32Nth data from current position, and doesn't flush it.
/// NOTE: the caller has to make sure the peeked byte is in buffer
///     and this can be checked via calling of msAPI_StillImage_BMBuffer_Remainder()
/// @param: u32Nth: Show u32Nth byte from current position.
/// @return: The value of u32Nth data from current position.
///
//-------------------------------------------------------------------------------------------------
U8 msAPI_StillImage_BMBuffer_PeekNthByte (U32 u32Nth)
{
    U32 u32Pos;

    u32Pos = pstBM_Handler->u32BuffCurrent_Ptr + u32Nth;
    if (u32Pos >= pstBM_Handler->u32BuffUpper_Addr)
    {
        u32Pos -= pstBM_Handler->u32BuffActive_Size;
    }

    return _msAPI_StillImage_BM_GetData(u32Pos);
}

//-------------------------------------------------------------------------------------------------
/// It copies N bytes of data to pointed buffer and removes all of it.
/// @param: pu8Buffer: The buffer to where the data will put.
/// @param: u32Nth: How many bytes of data to copy.
/// @return: How many bytes of data copied.
///
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_BMBuffer_CopyNByte (U8 *pu8Buffer, U32 u32N)
{
    U32 u32Remainder;
    U32 u32ToEnd;

    if ((pu8Buffer == NULL) || (u32N == 0))
    {
        return 0;
    }

    u32Remainder = msAPI_StillImage_BMBuffer_Remainder();
    u32Remainder = u32Remainder < u32N ? u32Remainder : u32N;

    u32ToEnd = pstBM_Handler->u32BuffUpper_Addr - pstBM_Handler->u32BuffCurrent_Ptr;

    if (u32ToEnd >= u32Remainder)
    {
        memcpy(pu8Buffer, (void *)(pstBM_Handler->u32Buff_Addr + pstBM_Handler->u32BuffCurrent_Ptr), u32Remainder);
    }
    else
    {
        memcpy(pu8Buffer, (void *)(pstBM_Handler->u32Buff_Addr + pstBM_Handler->u32BuffCurrent_Ptr), u32ToEnd);
        memcpy(pu8Buffer + u32ToEnd, (void *)(pstBM_Handler->u32BuffActive_Addr), u32Remainder - u32ToEnd);
    }

    _msAPI_StillImage_BMBuff_UpdateCurrentPtr(u32Remainder);
    return u32Remainder;
}

//-------------------------------------------------------------------------------------------------
/// It will flush data from current position.
/// If the residual buffer space isn't enough, it will re-fill automatically.
/// @param: u32Bytes: Flush bytes from current position.
/// @return: None
///
//-------------------------------------------------------------------------------------------------
void msAPI_StillImage_BMBuffer_FlushBytes(U32 u32Bytes)
{
    S32 s32Remainder;

    s32Remainder = msAPI_StillImage_BMBuffer_Remainder();

    if (u32Bytes > (U32)s32Remainder)
    {
        do
        {
            _msAPI_StillImage_BMBuff_UpdateCurrentPtr(s32Remainder);

            u32Bytes -= s32Remainder;
            if ((s32Remainder = msAPI_StillImage_BMBuffer_CustomFill(u32PreLoadSize)) == 0)
            {
                SI_BM_ERR(printf("No more Bits!!\n"));
                return;
            }
        } while(u32Bytes > (U32)s32Remainder);
    }

    _msAPI_StillImage_BMBuff_UpdateCurrentPtr(u32Bytes);
}

//-------------------------------------------------------------------------------------------------
/// The variable, u32BuffCurrent_Ptr, will be reset to u32BuffRead_Addr.
/// It provides a method to re-read the input data.
/// @param: None
/// @return: The new u32BuffCurrent_Ptr address.
///
//-------------------------------------------------------------------------------------------------
void msAPI_StillImage_BMBuffer_ResetRead(void)
{
    pstBM_Handler->u32BuffCurrent_Ptr = pstBM_Handler->u32BuffRead_Addr;
    pstBM_Handler->u16BuffCurrent_Layer = pstBM_Handler->u16BuffRead_Layer;
}

//-------------------------------------------------------------------------------------------------
/// The variable, u32BuffRead_Addr, will be move to u32BuffCurrent_Ptr.
/// @param: None
/// @return: The new u32BuffRead_Addr address.
///
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_BMBuffer_UpdateBase(void)
{
    pstBM_Handler->u32BuffRead_Addr = pstBM_Handler->u32BuffCurrent_Ptr;
    pstBM_Handler->u16BuffRead_Layer = pstBM_Handler->u16BuffCurrent_Layer;

    return pstBM_Handler->u32BuffRead_Addr;
}

//-------------------------------------------------------------------------------------------------
/// The API provides to show the buffer remainder.
/// @param: None
/// @return: bytes of data remainds in buffer
///
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_BMBuffer_Remainder(void)
{
    S32 s32Remainder;

    s32Remainder = (S32)(pstBM_Handler->u32BuffWrite_Addr - pstBM_Handler->u32BuffCurrent_Ptr);
    if ((s32Remainder < 0)
            || ((s32Remainder == 0) && (pstBM_Handler->u16BuffWrite_Layer > pstBM_Handler->u16BuffCurrent_Layer)))
    {
        s32Remainder += pstBM_Handler->u32BuffActive_Size;
    }

    return s32Remainder;
}

//-------------------------------------------------------------------------------------------------
/// The API provides to show the space remainder.
/// @param: None
/// @return: bytes of data remainds in buffer
///
//-------------------------------------------------------------------------------------------------
U32 msAPI_StillImage_BMBuffer_SpaceLeft(void)
{
    S32 s32Remainder;

    s32Remainder = (S32)(pstBM_Handler->u32BuffWrite_Addr - pstBM_Handler->u32BuffRead_Addr);
    if ((s32Remainder < 0)
            || ((s32Remainder == 0) && (pstBM_Handler->u16BuffWrite_Layer > pstBM_Handler->u16BuffRead_Layer)))
    {
        s32Remainder += pstBM_Handler->u32BuffActive_Size;
    }

    return (pstBM_Handler->u32BuffActive_Size - s32Remainder);
}

//-------------------------------------------------------------------------------------------------
/// The API provides to reset the Buffer.
/// @param: None
/// @return:  E_BM_RET_OK or E_BM_RET_FAIL
///
//-------------------------------------------------------------------------------------------------
EN_BM_RET msAPI_StillImage_BMBuffer_Reset(void)
{
    pstBM_Handler->u32BuffCurrent_Ptr = pstBM_Handler->u32BuffReserved_Size;
    pstBM_Handler->u32BuffWrite_Addr = pstBM_Handler->u32BuffReserved_Size;
    pstBM_Handler->u32BuffRead_Addr = pstBM_Handler->u32BuffReserved_Size;
    pstBM_Handler->u32BuffLower_Addr = pstBM_Handler->u32BuffReserved_Size;
    pstBM_Handler->u32BuffUpper_Addr = pstBM_Handler->u32BuffReserved_Size + pstBM_Handler->u32BuffActive_Size;
    pstBM_Handler->u16BuffRead_Layer = 0;
    pstBM_Handler->u16BuffWrite_Layer = 0;
    pstBM_Handler->u16BuffCurrent_Layer = 0;

    return E_BM_RET_OK;
}

//-------------------------------------------------------------------------------------------------
/// The API provides to query the status of buffer. Is it full or not?
/// @param: None
/// @return:  TRUE or FALSE
///
//-------------------------------------------------------------------------------------------------
BOOL msAPI_StillImage_BMBuffer_IsFull(void)
{
    return (msAPI_StillImage_BMBuffer_SpaceLeft() <= 4);
}

//-------------------------------------------------------------------------------------------------
/// The API provides to query the status of buffer. Is it empty or not?
/// @param: None
/// @return:  TRUE or FALSE
///
//-------------------------------------------------------------------------------------------------
BOOL msAPI_StillImage_BMBuffer_IsEmpty(void)
{
    return (msAPI_StillImage_BMBuffer_Remainder() == 0);
}

#undef  _MSAPI_STILLIMAGE_BM_C_

///*** please do not remove change list tag ***///
///***$Change: 428882 $***///
