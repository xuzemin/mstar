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
// Copyright (c) 2006-2012 MStar Semiconductor, Inc.
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
#define _MSAPI_VDPLAYER_BM_C_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "msAPI_DataStreamIO.h"
#include "mapp_vdplayer_bm.h"

#define VDPLAYER_DBG(format, args...)        printf(format, ##args)
#define VDPLAYER_IFO(format, args...)        printf(format, ##args)
#define VDPLAYER_ERR(format, args...)        printf(format, ##args)

typedef union
{
    U64 u64;
    struct {
        U32 u32_0;
        U32 u32_1;
    };
    struct {
        U16 u16_0;
        U16 u16_1;
        U16 u16_2;
        U16 u16_3;
    };
    struct {
        U8 u8_0;
        U8 u8_1;
        U8 u8_2;
        U8 u8_3;
        U8 u8_4;
        U8 u8_5;
        U8 u8_6;
        U8 u8_7;
    };
} UU64;

#define RESERVED_ES_BUF_SIZE    (0x80000)
#define u32u64_0(u)             (((UU64*)&(u))->u32_0)
#define u32u64_1(u)             (((UU64*)&(u))->u32_1)
#define U32_MAX                 (0xFFFFFFFFUL)
#define CPU_IS_LITTLE_ENDIAN    1

static BM_HANDLER m_BM_Handler[E_BM_MAX_HANDLER];
static U32 _u32PreLoadSize;
PBM_HANDLER m_pBM_Handler;
//------------------------------------------------------------------------------
//          local function
//------------------------------------------------------------------------------
static __attribute__((noinline)) U32 _msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad(void);
//------------------------------------------------------------------------------
inline U8 msAPI_VDPlayer_BMGetBitstreamBuf(U32 u32Idx)
{
    return *((U8*)(m_pBM_Handler->u32BitStreamAddr + u32Idx));
}

//-------------------------------------------------------------------------------------------------
/// The API is used as a chance to BM variables.
/// @param: None
/// @return: None
///
//-------------------------------------------------------------------------------------------------
void msAPI_VDPlayer_BMInit(U8 u8FileHdl, U64 u64FileSize)
{
    U8 u8Idx;

    for (u8Idx = 0; u8Idx < E_BM_MAX_HANDLER; u8Idx++)
    {
        memset(&m_BM_Handler[u8Idx], 0x0, sizeof(BM_HANDLER));
    }

    _u32PreLoadSize = BM_DEFAULT_PRELOAD_SIZE;
    m_pBM_Handler = &(m_BM_Handler[0]);
    m_pBM_Handler->u8FileHdl = u8FileHdl;
    m_pBM_Handler->u64FileSize = u64FileSize;
    msAPI_VDPlayer_BMFileSeek(0, E_BM_FILEPOS_SEEK_SET);
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
U32 MApp_VDPlayer_GetStrmHandleByIdx(U8 u8HdlIdx);

void msAPI_VDPlayer_FileSeek(U8 u8StrmHdlIdx, U64 u64FileOffset)
{
    U32 u32StrmHdl = MApp_VDPlayer_GetStrmHandleByIdx(u8StrmHdlIdx);
    LongLong llOffset;
    llOffset.Hi = u32u64_1(u64FileOffset);
    llOffset.Lo = u32u64_0(u64FileOffset);
    msAPI_DataStreamIO_Seek_LongLong(u32StrmHdl, llOffset, E_DATA_STREAM_SEEK_SET);
}

EN_BM_RET msAPI_VDPlayer_BMFileSeek(U64 u64Offset, EN_BM_FILEPOS ePos)
{
    if(E_BM_FILEPOS_SEEK_CUR == ePos)
    {
        u64Offset = msAPI_VDPlayer_BMFileTell() + u64Offset;
    }

    if (u64Offset >= m_pBM_Handler->u64FileSize)
    {
        u64Offset = m_pBM_Handler->u64FileSize;
    }

    msAPI_VDPlayer_BMBuffer_Reset();

    if (u64Offset < m_pBM_Handler->u64FileSize)
    {
        m_pBM_Handler->bEOFReached = FALSE;
    }
    else
    {
        m_pBM_Handler->bEOFReached = TRUE;
    }

    msAPI_VDPlayer_FileSeek(m_pBM_Handler->u8FileHdl, u64Offset);

    m_pBM_Handler->u64FilePosition = u64Offset;

    return E_BM_RET_OK;
}

//-------------------------------------------------------------------------------------------------
/// The API provides to get the current position of the file.
/// @param: None
/// @return:  The current file position
///
//-------------------------------------------------------------------------------------------------
U64 msAPI_VDPlayer_BMFileTell(void)
{
    U64 val;

    if(m_pBM_Handler->u32DemuxCurrent_Ptr > m_pBM_Handler->u32DemuxBufTell_Ptr)
    {
        val = m_pBM_Handler->u64FilePosition - ((m_pBM_Handler->u32DemuxBufTell_Ptr - m_pBM_Handler->u32ReservedBuffSize)
            + m_pBM_Handler->u32BitStreamSize - m_pBM_Handler->u32DemuxCurrent_Ptr);
    }
    else
    {
        val = m_pBM_Handler->u64FilePosition - (m_pBM_Handler->u32DemuxBufTell_Ptr - m_pBM_Handler->u32DemuxCurrent_Ptr);
    }

    return val;
}

//-------------------------------------------------------------------------------------------------
/// The API provides to test for end-of-file on a stream.
/// @param: None
/// @return:  TRUE or FALSE
///
//-------------------------------------------------------------------------------------------------
BOOL msAPI_VDPlayer_BMFileEOF(void)
{
    if(m_pBM_Handler->bEOFReached == TRUE && m_pBM_Handler->u32DemuxCurrent_Ptr== m_pBM_Handler->u32DemuxWrite_Addr)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

//-------------------------------------------------------------------------------------------------
/// The API provides to fill data from bitstream into Demux buffer immediately.
/// It will return the number of actually read,
/// which may be less than count if an error occurs or if the end of the file is encountered before reaching count.
/// The operation will abort any non-blocking read and will do the block read till the ack of file system.
/// It must be care to use at the playing. In order avoiding to trap into the API, it will design with time-out control.
/// @param: u32Size: Fill u32Size bytes bitstream into Demux buffer immediately
/// @return:  The number of actually read
///
//-------------------------------------------------------------------------------------------------
U32 msAPI_VDPlayer_BMFileRead(U32 u32Addr, U32 u32Size)
{
    U32 read_size = 0;

    if (u32Size == 0)
    {
        return 0;
    }

    U32 u32StrmHdl = MApp_VDPlayer_GetStrmHandleByIdx(m_pBM_Handler->u8FileHdl);
    read_size = msAPI_DataStreamIO_Read(u32StrmHdl, (void*)(_VA2PA(u32Addr)), u32Size);
    
    MsOS_Dcache_Flush(u32Addr, u32Size);
    MsOS_FlushMemory();
    
    read_size = (u32Size - read_size);

    m_pBM_Handler->u64FilePosition += read_size;

    return read_size;
}

//-------------------------------------------------------------------------------------------------
/// It will get N bytes data from demux buffer, and flush N bytes automatically.
/// If the demux buffer is empty, it will auto re-fill the size of "BM_DEFAULT_PRELOAD_SIZE"
/// @param: U8Bytes: Read N(0~4) bytes by big endian from demux buffer.
/// @return: The data of demux buffer. (0x01 0x02 0x03 0x04 ' 0x01 0x02 0x03 0x04)
///
//-------------------------------------------------------------------------------------------------
U32 msAPI_VDPlayer_BMReadBytes(U8 u8Bytes)
{
    U32 u32Val = 0x00;
    U8 idx;

    for(idx = 0; idx < u8Bytes; idx++)
    {
        u32Val = (u32Val << 8) | msAPI_VDPlayer_BMGetBitstreamBuf(m_pBM_Handler->u32DemuxCurrent_Ptr++);
    }

    return u32Val;
 }

//-------------------------------------------------------------------------------------------------
/// It just shows N bytes data from demux buffer, and doesn't flush it.
/// If the demux buffer is empty, it will auto re-fill the size of "BM_DEFAULT_PRELOAD_SIZE".
/// @param: U8Bytes: Read N(0~4) bytes by big endian from demux buffer.
/// @return: The data of demux buffer
///
//-------------------------------------------------------------------------------------------------
U32 msAPI_VDPlayer_BMShowBytes(U8 u8Bytes)
{
    U32 u32Val = 0x00;
    U8 idx;

    for(idx = 0; idx < u8Bytes; idx++)
    {
        u32Val = (u32Val << 8) | msAPI_VDPlayer_BMGetBitstreamBuf(m_pBM_Handler->u32DemuxCurrent_Ptr+ idx);
    }

    return u32Val;
 }

//-------------------------------------------------------------------------------------------------
/// It will get N bytes data from demux buffer, and flush N bytes automatically.
/// If the demux buffer is empty, it will auto re-fill the size of "BM_DEFAULT_PRELOAD_SIZE".
/// @param: U8Bytes: Read N(0~4) bytes by little endian from demux buffer.
/// @return: The data of demux buffer
///
//-------------------------------------------------------------------------------------------------
U32 msAPI_VDPlayer_BMReadBytes_LE(U8 u8Bytes)
{
    U32 u32Val = 0x00;
    U8 idx;

    for(idx = 0; idx < u8Bytes; idx++)
    {
        u32Val = u32Val | (msAPI_VDPlayer_BMGetBitstreamBuf(m_pBM_Handler->u32DemuxCurrent_Ptr++)<<(idx*8));
    }

    return u32Val;
}


//-------------------------------------------------------------------------------------------------
/// It just shows N bytes data from demux buffer, and doesn't flush it.
/// If the demux buffer is empty, it will auto re-fill the size of "BM_DEFAULT_PRELOAD_SIZE".
/// @param: U8Bytes: Read N(0~4) bytes by little endian from demux buffer.
/// @return: The data of demux buffer
///
//-------------------------------------------------------------------------------------------------
U32 msAPI_VDPlayer_BMShowBytes_LE(U8 u8Bytes)
{
    U32 u32Val = 0x00;
    U8 idx;

    for(idx = 0; idx < u8Bytes; idx++)
    {
        u32Val = u32Val | (msAPI_VDPlayer_BMGetBitstreamBuf(m_pBM_Handler->u32DemuxCurrent_Ptr + idx)<< (idx*8));
    }

    return u32Val;
}

//-------------------------------------------------------------------------------------------------
///
///
/// @param:
/// @return:
///
//-------------------------------------------------------------------------------------------------
U32 msAPI_VDPlayer_BMFillBuffer_Custom(U32 u32Size)
{
    U64 val = 0;
    U32 u32FillSize;
    S32 s32Space;

    if (m_pBM_Handler->bEOFReached == TRUE)
    {
        return 0;
    }

    m_pBM_Handler->u32DemuxRead_Addr = m_pBM_Handler->u32DemuxCurrent_Ptr;
    m_pBM_Handler->u16DemuxRead_Layer = m_pBM_Handler->u16DemuxCurrent_Layer;

    s32Space = m_pBM_Handler->u32DemuxRead_Addr - m_pBM_Handler->u32DemuxWrite_Addr;

    if (s32Space <= 0)
    {
        s32Space += m_pBM_Handler->u32BuffActiveSize;
    }

    if (s32Space <= 1)
    {
        return 0;
    }

    // Modified u32Size based on remaining buffer size information
    u32Size = MIN(u32Size, (U32)(s32Space - 512)) & ~(0x3);

    // Modified u32Size based on remaining file data information
    val = m_pBM_Handler->u64FileSize - m_pBM_Handler->u64FilePosition;

    if ((u32u64_1(val)==0) && (u32Size > u32u64_0(val)))
    {
        u32Size = u32u64_0(val);
    }

    if (u32Size == 0)
    {
        return 0;
    }

    // Fill u32Size data to Demux Buffer
    if (m_pBM_Handler->u32DemuxWrite_Addr < m_pBM_Handler->u32DemuxRead_Addr)
    {
        u32FillSize = msAPI_VDPlayer_BMFileRead(m_pBM_Handler->u32BitStreamAddr + m_pBM_Handler->u32DemuxWrite_Addr, u32Size);
        m_pBM_Handler->u32DemuxWrite_Addr = m_pBM_Handler->u32DemuxWrite_Addr + u32FillSize;
    }
    else
    {
        U32 u32ToEnd;

        u32ToEnd = (m_pBM_Handler->u32DemuxUpper_Addr-m_pBM_Handler->u32DemuxWrite_Addr);
        if (u32Size < u32ToEnd)
        {
            u32FillSize = msAPI_VDPlayer_BMFileRead(m_pBM_Handler->u32BitStreamAddr + m_pBM_Handler->u32DemuxWrite_Addr, u32Size);
            m_pBM_Handler->u32DemuxWrite_Addr = m_pBM_Handler->u32DemuxWrite_Addr + u32FillSize;
        }
        else if (u32Size > u32ToEnd)
        {
            u32FillSize = msAPI_VDPlayer_BMFileRead(m_pBM_Handler->u32BitStreamAddr + m_pBM_Handler->u32DemuxWrite_Addr, u32ToEnd);
            if (u32FillSize < u32ToEnd)
            {
                m_pBM_Handler->u32DemuxWrite_Addr += u32FillSize;
            }
            else
            {
                u32FillSize += msAPI_VDPlayer_BMFileRead(m_pBM_Handler->u32BuffActiveAddr, u32Size - u32ToEnd);
                m_pBM_Handler->u32DemuxWrite_Addr += u32FillSize - m_pBM_Handler->u32BuffActiveSize;
                m_pBM_Handler->u16DemuxWrite_Layer++;
            }
        }
        else
        {
            u32FillSize = msAPI_VDPlayer_BMFileRead(m_pBM_Handler->u32BitStreamAddr + m_pBM_Handler->u32DemuxWrite_Addr, u32Size);
            m_pBM_Handler->u32DemuxWrite_Addr = m_pBM_Handler->u32DemuxLower_Addr;
            m_pBM_Handler->u16DemuxWrite_Layer++;
        }
    }

    if (m_pBM_Handler->u64FilePosition >= m_pBM_Handler->u64FileSize)
    {
        m_pBM_Handler->bEOFReached = TRUE;
    }

    m_pBM_Handler->u32DemuxBufTell_Ptr = m_pBM_Handler->u32DemuxWrite_Addr;

    MsOS_ReadMemory();
    return u32FillSize;
}

//-------------------------------------------------------------------------------------------------
///
///
/// @param:
/// @return:
///
//-------------------------------------------------------------------------------------------------
U32 msAPI_VDPlayer_BMReadBytes_AutoLoad(U8 nBytes)
{
    S32 s32Remainder;
    U32 u32ToEnd;
    U8  idx;
    U8  u8Byte[4];

    if (0 == nBytes || 4 < nBytes)
        return 0;

    for (idx = 0; idx < 4; idx++)
        u8Byte[idx] = 0;

    s32Remainder = m_pBM_Handler->u32DemuxWrite_Addr - m_pBM_Handler->u32DemuxCurrent_Ptr;
    if (s32Remainder < 0)
    {
        s32Remainder += m_pBM_Handler->u32BuffActiveSize;
    }

    if (nBytes > s32Remainder)
    {
        if (msAPI_VDPlayer_BMFillBuffer_Custom(_u32PreLoadSize) < (U32)(nBytes - s32Remainder))
        {
            VDPLAYER_ERR("No more bits!!\n");
            return U32_MAX;
        }
    }

    u32ToEnd = m_pBM_Handler->u32DemuxUpper_Addr - m_pBM_Handler->u32DemuxCurrent_Ptr;

    if (u32ToEnd > nBytes)
    {
        for (idx = 0; idx < nBytes; idx++)
            u8Byte[idx] =  msAPI_VDPlayer_BMGetBitstreamBuf(m_pBM_Handler->u32DemuxCurrent_Ptr++);
    }
    else
    {
        for (idx = 0; idx < u32ToEnd; idx++)
            u8Byte[idx] =  msAPI_VDPlayer_BMGetBitstreamBuf(m_pBM_Handler->u32DemuxCurrent_Ptr++);

        m_pBM_Handler->u32DemuxCurrent_Ptr -= m_pBM_Handler->u32BuffActiveSize;
        m_pBM_Handler->u16DemuxCurrent_Layer ++;

        for (; idx < nBytes; idx++)
            u8Byte[idx] =  msAPI_VDPlayer_BMGetBitstreamBuf(m_pBM_Handler->u32DemuxCurrent_Ptr++);
    }

    if (nBytes == 4)
        return (U32)u8Byte[3] | ((U32)u8Byte[2] << 8) | ((U32)u8Byte[1] << 16) | ((U32)u8Byte[0] << 24);

    if (nBytes == 3)
        return (U32)u8Byte[2] | ((U32)u8Byte[1] << 8)| ((U32)u8Byte[0] << 16);

    if (nBytes == 2)
        return (U32)u8Byte[1] | ((U32)u8Byte[0] << 8);

    return (U32)u8Byte[0];
}

//-------------------------------------------------------------------------------------------------
///
///
/// @param:
/// @return:
///
//-------------------------------------------------------------------------------------------------
U32 msAPI_VDPlayer_BMReadBytes_LE_AutoLoad(U8 nBytes)
{
    S32 s32Remainder;
    U32 u32ToEnd;
    U8  idx;
    U8  u8Byte[4];

    if (0 == nBytes || 4 < nBytes)
        return 0;

    for (idx = 0; idx < 4; idx++)
        u8Byte[idx] = 0;

    s32Remainder = m_pBM_Handler->u32DemuxWrite_Addr - m_pBM_Handler->u32DemuxCurrent_Ptr;
    if (s32Remainder < 0)
    {
        s32Remainder += m_pBM_Handler->u32BuffActiveSize;
    }

    if (nBytes > s32Remainder)
    {
        if (msAPI_VDPlayer_BMFillBuffer_Custom(_u32PreLoadSize) < (U32)(nBytes - s32Remainder))
        {
            VDPLAYER_ERR("No more bits!!\n");
            return U32_MAX;
        }
    }

    u32ToEnd = m_pBM_Handler->u32DemuxUpper_Addr - m_pBM_Handler->u32DemuxCurrent_Ptr;

    if (u32ToEnd > nBytes)
    {
        for(idx = 0; idx < nBytes; idx++)
            u8Byte[idx] =  msAPI_VDPlayer_BMGetBitstreamBuf(m_pBM_Handler->u32DemuxCurrent_Ptr++);
    }
    else
    {
        for(idx = 0; idx < u32ToEnd; idx++)
            u8Byte[idx] =  msAPI_VDPlayer_BMGetBitstreamBuf(m_pBM_Handler->u32DemuxCurrent_Ptr++);

        m_pBM_Handler->u32DemuxCurrent_Ptr -= m_pBM_Handler->u32BuffActiveSize;
        m_pBM_Handler->u16DemuxCurrent_Layer ++;

        for (; idx < nBytes; idx++)
            u8Byte[idx] =  msAPI_VDPlayer_BMGetBitstreamBuf(m_pBM_Handler->u32DemuxCurrent_Ptr++);
    }

    return (U32)u8Byte[0] | ((U32)u8Byte[1] << 8) | ((U32)u8Byte[2] << 16) | ((U32)u8Byte[3] << 24);
}

U32 msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad(void)
{
    S32 s32Remainder;
    U32 u32ToEnd;
    U32 u32Val;
    U32 u32CurrentAddr;

    s32Remainder = m_pBM_Handler->u32DemuxWrite_Addr - m_pBM_Handler->u32DemuxCurrent_Ptr;
    if (s32Remainder < 0)
    {
        s32Remainder += m_pBM_Handler->u32BuffActiveSize;
    }

    if (4 <= s32Remainder)
    {
        u32ToEnd = m_pBM_Handler->u32DemuxUpper_Addr - m_pBM_Handler->u32DemuxCurrent_Ptr;

        if (u32ToEnd > 4)
        {
            u32CurrentAddr = m_pBM_Handler->u32BitStreamAddr + m_pBM_Handler->u32DemuxCurrent_Ptr;
        
        #if (CPU_IS_LITTLE_ENDIAN)
            if((u32CurrentAddr & 0x3) == 0)
            {
                u32Val = *((U32*)u32CurrentAddr);
            }
            else
        #endif       
            {
                u32Val = *(U8*)(u32CurrentAddr)               |
                        (*(U8*)(u32CurrentAddr + 1) <<  8)    |
                        (*(U8*)(u32CurrentAddr + 2) << 16)    |
                        (*(U8*)(u32CurrentAddr + 3) << 24);
            }

            m_pBM_Handler->u32DemuxCurrent_Ptr += 4;

            return u32Val;
        }
    }

    return _msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();
}

static __attribute__((noinline)) U32 _msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad(void)
{
    S32 s32Remainder;
    U32 u32ToEnd;
    U8  u8Idx;
    U32 u32Val=0;
    U32 u32CurrentPtr;

    s32Remainder = m_pBM_Handler->u32DemuxWrite_Addr - m_pBM_Handler->u32DemuxCurrent_Ptr;
    if (s32Remainder < 0)
    {
        s32Remainder += m_pBM_Handler->u32BuffActiveSize;
    }

    if (4 > s32Remainder)
    {
        if (msAPI_VDPlayer_BMFillBuffer_Custom(_u32PreLoadSize) < (U32)(4 - s32Remainder))
        {
            VDPLAYER_ERR("No more bits!!\n");
            return U32_MAX;
        }
    }

    u32ToEnd = m_pBM_Handler->u32DemuxUpper_Addr - m_pBM_Handler->u32DemuxCurrent_Ptr;

    if (u32ToEnd > 4)
    {
        u32CurrentPtr = m_pBM_Handler->u32BitStreamAddr + m_pBM_Handler->u32DemuxCurrent_Ptr;
    
    #if (CPU_IS_LITTLE_ENDIAN)
        if((u32CurrentPtr & 0x3) == 0)
        {
            u32Val = *((U32*)u32CurrentPtr);
        }
        else
    #endif       
        {
            u32Val = *(U8*)(u32CurrentPtr)               |
                    (*(U8*)(u32CurrentPtr + 1) << 8)     |
                    (*(U8*)(u32CurrentPtr + 2) << 16)    |
                    (*(U8*)(u32CurrentPtr + 3) << 24);
        }

        m_pBM_Handler->u32DemuxCurrent_Ptr += 4;
    }
    else
    {
        for(u8Idx = 0; u8Idx < u32ToEnd; u8Idx++)
        {
            u32Val = u32Val | (msAPI_VDPlayer_BMGetBitstreamBuf(m_pBM_Handler->u32DemuxCurrent_Ptr++) << (u8Idx*8));
        }

        m_pBM_Handler->u32DemuxCurrent_Ptr -= m_pBM_Handler->u32BuffActiveSize;
        m_pBM_Handler->u16DemuxCurrent_Layer ++;

        for(; u8Idx < 4; u8Idx++)
        {
            u32Val = u32Val | (msAPI_VDPlayer_BMGetBitstreamBuf(m_pBM_Handler->u32DemuxCurrent_Ptr++) << (u8Idx*8));
        }
    }

    return u32Val;
}

BOOLEAN msAPI_VDPlayer_BMRead16Bytes_LE_AutoLoad(U32 *u32Ptr0, U32 *u32Ptr1, U32 *u32Ptr2, U32 *u32Ptr3)
{
    S32 s32Remainder;
    U32 u32ToEnd;
    U32 u32CurrentAddr;

    s32Remainder = m_pBM_Handler->u32DemuxWrite_Addr - m_pBM_Handler->u32DemuxCurrent_Ptr;
    if (s32Remainder < 0)
    {
        s32Remainder += m_pBM_Handler->u32BuffActiveSize;
    }

    if (16 > s32Remainder)
    {
        if (msAPI_VDPlayer_BMFillBuffer_Custom(_u32PreLoadSize) < (U32)(16 - s32Remainder))
        {
            VDPLAYER_ERR("No more bits!!\n");
            return FALSE;
        }
    }

    u32ToEnd = m_pBM_Handler->u32DemuxUpper_Addr - m_pBM_Handler->u32DemuxCurrent_Ptr;

    if (u32ToEnd > 16)
    {
        u32CurrentAddr = m_pBM_Handler->u32BitStreamAddr + m_pBM_Handler->u32DemuxCurrent_Ptr;

#if (CPU_IS_LITTLE_ENDIAN)
        if ( (u32CurrentAddr & 0x3) == 0 ) {
            U32 *src = (U32 *)u32CurrentAddr;
            *u32Ptr0 = src[0];
            *u32Ptr1 = src[1];
            *u32Ptr2 = src[2];
            *u32Ptr3 = src[3];
        }
        else
#endif
        {
            U8 *src = (U8 *)u32CurrentAddr;
            *u32Ptr0 = (src[0] << 0)  |
                       (src[1] << 8)  |
                       (src[2] << 16) |
                       (src[3] << 24);
            *u32Ptr1 = (src[4] << 0)  |
                       (src[5] << 8)  |
                       (src[6] << 16) |
                       (src[7] << 24);
            *u32Ptr2 = (src[8] << 0)  |
                       (src[9] << 8)  |
                       (src[10] << 16) |
                       (src[11] << 24);
            *u32Ptr3 = (src[12] << 0)  |
                       (src[13] << 8)  |
                       (src[14] << 16) |
                       (src[15] << 24);
        }

        m_pBM_Handler->u32DemuxCurrent_Ptr += 16;
    }
    else
    {
        *u32Ptr0 = msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();
        *u32Ptr1 = msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();
        *u32Ptr2 = msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();
        *u32Ptr3 = msAPI_VDPlayer_BMRead4Bytes_LE_AutoLoad();
    }

    return TRUE;
}


//-------------------------------------------------------------------------------------------------
/// It will flush data from current position.
/// If the residual buffer space isn't enough, it will re-fill again.
/// @param: u32Bytes: Flush bytes from current position.
/// @return: None
///
//-------------------------------------------------------------------------------------------------
void    msAPI_VDPlayer_BMFlushBytes(U32 u32Bytes)
{
    S32 s32Remainder;
    U32 u32ToEnd;

    s32Remainder = m_pBM_Handler->u32DemuxWrite_Addr - m_pBM_Handler->u32DemuxCurrent_Ptr;

    if (s32Remainder < 0)
    {
        s32Remainder += m_pBM_Handler->u32BuffActiveSize;
    }

    if (u32Bytes > (U32)s32Remainder)
    {
        do {
            u32ToEnd = m_pBM_Handler->u32DemuxUpper_Addr - m_pBM_Handler->u32DemuxCurrent_Ptr;

            if ((U32)s32Remainder < u32ToEnd)
            {
                m_pBM_Handler->u32DemuxCurrent_Ptr += s32Remainder;
            }
            else
            {
                m_pBM_Handler->u32DemuxCurrent_Ptr += s32Remainder - m_pBM_Handler->u32BuffActiveSize;
                m_pBM_Handler->u16DemuxCurrent_Layer++;
            }

            u32Bytes -= s32Remainder;
            if ((s32Remainder = msAPI_VDPlayer_BMFillBuffer_Custom(_u32PreLoadSize)) == 0)
            {
                VDPLAYER_ERR("No more Bits!!\n");
                return;
            }
        } while(u32Bytes > (U32)s32Remainder);
    }

    u32ToEnd = m_pBM_Handler->u32DemuxUpper_Addr - m_pBM_Handler->u32DemuxCurrent_Ptr;

    if (u32Bytes < u32ToEnd)
    {
        m_pBM_Handler->u32DemuxCurrent_Ptr += u32Bytes;
    }
    else
    {
        m_pBM_Handler->u32DemuxCurrent_Ptr += u32Bytes - m_pBM_Handler->u32BuffActiveSize;
        m_pBM_Handler->u16DemuxCurrent_Layer++;
    }
}

//-------------------------------------------------------------------------------------------------
/// The API is used to configure the Buffer location and its range.
/// After configuration, all relative information will be reset to default.
/// @param: u32Lower:The Lower boundary of buffer(eStreamType)
/// @param: u32Upper:The Upper boundary of buffer(eStreamType).
/// @param: eStreamType:Indicates which buffer will be configured. Now just design for Demux Buffer only.
/// @return: E_BM_RET_OK or E_BM_RET_FAIL
///
//-------------------------------------------------------------------------------------------------
EN_BM_RET msAPI_VDPlayer_BMBuffer_Configuration(U32 u32BitStreamAddr, U32 u32Size)
{
    // configure buffer for A/V stream
    m_BM_Handler[E_BM_AV_HANDLER].u32BitStreamAddr = u32BitStreamAddr;
    m_BM_Handler[E_BM_AV_HANDLER].u32BitStreamSize = u32Size;
    m_BM_Handler[E_BM_AV_HANDLER].u32ReservedBuffSize = RESERVED_ES_BUF_SIZE;
    m_BM_Handler[E_BM_AV_HANDLER].u32BuffActiveAddr = u32BitStreamAddr + RESERVED_ES_BUF_SIZE;
    m_BM_Handler[E_BM_AV_HANDLER].u32BuffActiveSize = u32Size - RESERVED_ES_BUF_SIZE;

    msAPI_VDPlayer_BMBuffer_Reset();

    return E_BM_RET_OK;
}

//-------------------------------------------------------------------------------------------------
/// The API provides to reset the Buffer.
/// If the Demux Buffer reset, All Queues will be reset at the same time.
/// Reset Video Buffer ' Flush SLQ & Reset Video Queue
/// Reset Audio Buffer ' ?? & Reset all Audio Queues
/// @param: eStreamType: Indicates which stream buffer.
/// @return:  E_BM_RET_OK or E_BM_RET_FAIL
///
//-------------------------------------------------------------------------------------------------
EN_BM_RET msAPI_VDPlayer_BMBuffer_Reset(void)
{
    m_pBM_Handler->u32DemuxCurrent_Ptr = m_pBM_Handler->u32ReservedBuffSize;
    m_pBM_Handler->u32DemuxWrite_Addr = m_pBM_Handler->u32ReservedBuffSize;
    m_pBM_Handler->u32DemuxRead_Addr = m_pBM_Handler->u32ReservedBuffSize;
    m_pBM_Handler->u32DemuxBase_Ptr = m_pBM_Handler->u32ReservedBuffSize;
    m_pBM_Handler->u32DemuxLower_Addr = m_pBM_Handler->u32ReservedBuffSize;
    m_pBM_Handler->u32DemuxUpper_Addr = m_pBM_Handler->u32ReservedBuffSize + m_pBM_Handler->u32BuffActiveSize;
    m_pBM_Handler->u32DemuxBufTell_Ptr = m_pBM_Handler->u32DemuxWrite_Addr;
    m_pBM_Handler->u16DemuxRead_Layer = 0;
    m_pBM_Handler->u16DemuxWrite_Layer = 0;
    m_pBM_Handler->u16DemuxBase_Layer = 0;
    m_pBM_Handler->u16DemuxCurrent_Layer = 0;
    return E_BM_RET_OK;
}

U32 msAPI_VDPlayer_BMBuffer_Remainder(void)
{
    if(m_pBM_Handler->u32DemuxWrite_Addr >= m_pBM_Handler->u32DemuxCurrent_Ptr)
        return (m_pBM_Handler->u32DemuxWrite_Addr - m_pBM_Handler->u32DemuxCurrent_Ptr);
    else
        return (m_pBM_Handler->u32BuffActiveSize - (m_pBM_Handler->u32DemuxCurrent_Ptr - m_pBM_Handler->u32DemuxWrite_Addr));
}

EN_BM_RET msAPI_VDPlayer_BM_SetPreloadSize(U32 u32Size)
{
    _u32PreLoadSize = u32Size;

    return E_BM_RET_OK;
}

#undef  _MSAPI_VDPLAYER_BM_C_

