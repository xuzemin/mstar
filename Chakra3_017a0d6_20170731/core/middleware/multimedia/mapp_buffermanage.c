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

#define _MSAPI_BUFFER_MANAGE_C_
///////////////////////////////////////////////////////////////////////////////
/// @file   msAPI_BufferManage.c
/// @author MStar Semiconductor Inc.
/// @brief  Buffer management Module
///////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "MsCommon.h"
#include "MsOS.h"

#include "msAPI_DataStreamIO.h"
#include "MApp_FileBrowser.h"
#include "msAPI_Memory.h"


#include "FSUtil.h"
#include "msAPI_FCtrl.h"
#include "msAPI_FSCommon.h"

//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
#define BM_MEMORY_SIZE      0x1000
#define MAX_BM_HANDLER_NUM  4
#define BM_DBG(x)           //x

//-------------------------------------------------------------------------------------------------
// Type and Structure Declaration
//-------------------------------------------------------------------------------------------------
typedef struct   {
    U32 u32FilePosition;
    U32 u32BufferPosition;
    U32 u32BufferSize;
    
    U8 u8Handle;
    
    U8* pu8BufferAddr;
} ST_BM_HANDLER_INFO;

//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Global Variables
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Local Variables
//-------------------------------------------------------------------------------------------------
static ST_BM_HANDLER_INFO m_astBMHandler[MAX_BM_HANDLER_NUM];

//-------------------------------------------------------------------------------------------------
// Local Function Prototypes
//-------------------------------------------------------------------------------------------------
static BOOLEAN  _MApp_BufferManage_Init(void);
static BOOLEAN  _MApp_BufferManage_Finalize(void);
static U32      _MApp_BufferManage_FileOpen(void *pPrivate, U8 u8Mode, E_DATA_STREAM_TYPE eType);
static BOOLEAN  _MApp_BufferManage_FileClose(U32 u32FileHandle);
static U32      _MApp_BufferManage_FileRead(U32 u32FileHandle, void *pBuffAddr, U32 u32ReadByteLength);
static BOOLEAN  _MApp_BufferManage_FileSeek(U32 u32FileHandle, LongLong u64Pos, E_DATA_STREAM_SEEK_OPTION eOption);
static LongLong _MApp_BufferManage_FileTell(U32 u32FileHandle);
static LongLong _MApp_BufferManage_FileLength(U32 u32FileHandle);

//-------------------------------------------------------------------------------------------------
// Function Implementation
//-------------------------------------------------------------------------------------------------

//******************************************************************************
/// Register buffer management file I/O functions to DataStreamIO
/// @param  bEnable  \b IN Specify ST_AUDIO_CAPTURE_SET_INFO
/// @return BOOLEAN
//******************************************************************************
BOOLEAN MApp_BufferManage_Register(BOOLEAN bEnable)
{
    if (bEnable)
    {
        BM_DBG(printf("ENABLE BufferManage\n"));
        FN_DATA_STRM_IO stStreamIOFunc;
        memset(&stStreamIOFunc, 0, sizeof(FN_DATA_STRM_IO));
        
        // To avoid the resource unreleased, it should unregister first.
        msAPI_DataStreamIO_OptionRegistation(NULL,E_DATA_STREAM_MODE_BUFFER_MANAGEMENT);
        
        stStreamIOFunc.pfnInit = _MApp_BufferManage_Init;
        stStreamIOFunc.pfnFinalize = _MApp_BufferManage_Finalize;
        stStreamIOFunc.pfnOpen = _MApp_BufferManage_FileOpen;
        stStreamIOFunc.pfnClose = _MApp_BufferManage_FileClose;
        stStreamIOFunc.pfnRead = _MApp_BufferManage_FileRead;
        stStreamIOFunc.pfnSeek = _MApp_BufferManage_FileSeek;
        stStreamIOFunc.pfnTell = _MApp_BufferManage_FileTell;
        stStreamIOFunc.pfnLength = _MApp_BufferManage_FileLength;
        msAPI_DataStreamIO_OptionRegistation(&stStreamIOFunc,E_DATA_STREAM_MODE_BUFFER_MANAGEMENT);
        
    }
    else
    {
        BM_DBG(printf("DISABLE BufferManage\n"));
        msAPI_DataStreamIO_OptionRegistation(NULL,E_DATA_STREAM_MODE_BUFFER_MANAGEMENT);
    }

    return TRUE;
}


//-------------------------------------------------------------------------------------------------
// Local funcion -- misc functions
//-------------------------------------------------------------------------------------------------

//******************************************************************************
/// Initialize all static variables for buffer management
/// @param  None
/// @return BOOLEAN
//******************************************************************************
static BOOLEAN _MApp_BufferManage_Init(void)
{
    U8 u8i;
    for(u8i = 0; u8i < MAX_BM_HANDLER_NUM; u8i++)
    {
        m_astBMHandler[u8i].u32FilePosition = 0;
        m_astBMHandler[u8i].u32BufferPosition = 0;
        m_astBMHandler[u8i].u32BufferSize = 0;
        m_astBMHandler[u8i].pu8BufferAddr = NULL;
        m_astBMHandler[u8i].u8Handle = INVALID_FILE_HANDLE;
    }
    return TRUE;
}

//******************************************************************************
/// Set all static variables to initial values for buffer management and free allocated memory.
/// @param  None
/// @return BOOLEAN
//******************************************************************************
static BOOLEAN _MApp_BufferManage_Finalize(void)
{
    U8 u8Idx = 0;
    
    for(u8Idx = 0; u8Idx < MAX_BM_HANDLER_NUM; u8Idx++)
    {
        if(m_astBMHandler[u8Idx].u8Handle != INVALID_FILE_HANDLE)
        {
            //seek
            msAPI_FCtrl_FileSeek(m_astBMHandler[u8Idx].u8Handle,m_astBMHandler[u8Idx].u32FilePosition,FILE_SEEK_SET);
            //free
            msAPI_Memory_Free(m_astBMHandler[u8Idx].pu8BufferAddr,BUF_ID_FILEBROWER);
            m_astBMHandler[u8Idx].u32FilePosition = 0;
            m_astBMHandler[u8Idx].u32BufferPosition = 0;
            m_astBMHandler[u8Idx].u32BufferSize = 0;
            m_astBMHandler[u8Idx].pu8BufferAddr = NULL;
            m_astBMHandler[u8Idx].u8Handle = INVALID_FILE_HANDLE;
        }
    }
    return TRUE;
}

//******************************************************************************
/// A wrapper function which opens file and creates file handle for buffer management
/// @param  pPrivate  \b IN Specify the file entry
/// @param  u8Mode    \b IN Specify the file open mode
/// @param  eType     \b IN Specify the data stream type
/// @return U32
//******************************************************************************
static U32 _MApp_BufferManage_FileOpen(void *pPrivate, U8 u8Mode, E_DATA_STREAM_TYPE eType)
{
    U8 u8Hdl = INVALID_FILE_HANDLE;
    U8 u8Idx = 0;
    U8* pu8BuffAddr;

    eType = eType;
    u8Hdl = msAPI_FCtrl_FileOpen((FileEntry *)pPrivate, u8Mode);

    for(u8Idx = 0; u8Idx < MAX_BM_HANDLER_NUM; u8Idx++)
    {
        BM_DBG(printf("#%d Handle:%d\n",u8Idx,m_astBMHandler[u8Idx].u8Handle));
        if(m_astBMHandler[u8Idx].u8Handle== INVALID_FILE_HANDLE)
        {
            break;
        }
    }

    if(u8Idx == MAX_BM_HANDLER_NUM)
    {
        BM_DBG(printf("[BM] Open fail, the file handle space is full\n"));
        goto _MApp_BM_FileOpen_Other;
    }
    
    pu8BuffAddr = (U8*)msAPI_Memory_Allocate(BM_MEMORY_SIZE,BUF_ID_FILEBROWER);
    if(pu8BuffAddr == NULL)
    {
        BM_DBG(printf("[BM] Can not allocate Memory"));
        goto _MApp_BM_FileOpen_Other;
    }

    m_astBMHandler[u8Idx].u32FilePosition = 0;
    m_astBMHandler[u8Idx].u32BufferPosition = 0;
    m_astBMHandler[u8Idx].u32BufferSize = 0;
    m_astBMHandler[u8Idx].pu8BufferAddr = pu8BuffAddr;
    m_astBMHandler[u8Idx].u8Handle = u8Hdl;
        
_MApp_BM_FileOpen_Other:
    return u8Hdl;
}

//******************************************************************************
/// Close file for buffer management
/// @param  pPrivate  \b IN Specify the file entry
/// @param  u8Mode    \b IN Specify the file open mode
/// @param  eType     \b IN Specify the data stream type
/// @return BOOLEAN
//******************************************************************************
static BOOLEAN _MApp_BufferManage_FileClose(U32 u32FileHandle)
{
    U8 u8Idx = 0;;

    if(u32FileHandle == INVALID_FILE_HANDLE)
    {
        return FALSE;
    }
    
    for(u8Idx = 0; u8Idx < MAX_BM_HANDLER_NUM; u8Idx++)
    {
        BM_DBG(printf("#%d Handle:%d\n",u8Idx,m_astBMHandler[u8Idx].u8Handle));
        if(m_astBMHandler[u8Idx].u8Handle == u32FileHandle)
        {
            break;
        }
    }

    if(u8Idx == MAX_BM_HANDLER_NUM)
    {
        BM_DBG(printf("[BM] Close. file handle: %d is not belong to BM\n",u32FileHandle));
        return msAPI_FCtrl_FileClose((U8)u32FileHandle) == FILE_CLOSE_RESULT_ERROR ? FALSE : TRUE;
    }

    if(msAPI_FCtrl_FileClose(m_astBMHandler[u8Idx].u8Handle) == FILE_CLOSE_RESULT_ERROR)
    {
        m_astBMHandler[u8Idx].u8Handle= INVALID_FILE_HANDLE;
        BM_DBG(printf("[BM] file close fail\n"));
        return FALSE;
    }
    else
    {
        BM_DBG(printf("[BM] File Handle %d close ok\n",u32FileHandle));
        msAPI_Memory_Free(m_astBMHandler[u8Idx].pu8BufferAddr,BUF_ID_FILEBROWER);
        m_astBMHandler[u8Idx].u8Handle = INVALID_FILE_HANDLE;
        m_astBMHandler[u8Idx].u32BufferPosition = 0;
        m_astBMHandler[u8Idx].u32BufferSize = 0;
        m_astBMHandler[u8Idx].u32FilePosition = 0;
        return TRUE;
    }
}


//******************************************************************************
/// Read file for buffer management
/// Use 4K alignment to load file. 
/// 1. First check that the read position is located in current memory or not. If not, reload the BM memory.
/// 2. In while loop, copy BM memory to dst buffer and reload the next 4k size of file to BM memory.
/// @param  u32FileHandle     \b IN Specify the file handle
/// @param  pBuffAddr         \b IN Specify the read dst buffer
/// @param  u32ReadByteLength \b IN Specify the read length
/// @return U32 \b IN Specify the unread length
//******************************************************************************
U32 _MApp_BufferManage_FileRead(U32 u32FileHandle, void *pBuffAddr, U32 u32ReadByteLength)
{
    printf("Q");
    U32 u32OriginalReadByte = u32ReadByteLength;
    U8 u8Idx = 0;

    if(u32FileHandle == INVALID_FILE_HANDLE)
    {
        return u32OriginalReadByte;
    }
    
    for(u8Idx = 0; u8Idx < MAX_BM_HANDLER_NUM; u8Idx++)
    {
        if(m_astBMHandler[u8Idx].u8Handle == u32FileHandle)
        {
            break;
        }
    }

    if(u8Idx == MAX_BM_HANDLER_NUM)
    {
        BM_DBG(printf("[BM] Read. file handle: %d is not belong to BM\n",u32FileHandle));
        return msAPI_FCtrl_FileRead((U8)u32FileHandle, (U32)pBuffAddr, u32OriginalReadByte);
    }

    U32 u32FilePosition = m_astBMHandler[u8Idx].u32FilePosition;
    U32 u32BufferPosition = m_astBMHandler[u8Idx].u32BufferPosition;
    U32 u32BufferSize = m_astBMHandler[u8Idx].u32BufferSize;
    U8* u8BufferAddr = m_astBMHandler[u8Idx].pu8BufferAddr;
    BM_DBG(printf("R    %lu %lu %lu len=%lu ",u32FilePosition, u32BufferSize , u32BufferPosition, u32ReadByteLength));
    
    U32 u32ProcessByteLength = 0;
    U32 u32ReadByteCnt = m_astBMHandler[u8Idx].u32FilePosition % BM_MEMORY_SIZE;
    U32 u32FileTotalSize = msAPI_FCtrl_FileLength((U8)u32FileHandle);
    
    U32 u32FailReadSize = 0;

    if(u32FilePosition > u32FileTotalSize)
    {
        return u32OriginalReadByte;
    }

    //If not hit
    if(!((u32BufferPosition <= u32FilePosition) && ((u32BufferPosition + u32BufferSize) > u32FilePosition)))
    {
        if(u32FilePosition > 0)
        {
            u32BufferPosition = (u32FilePosition/BM_MEMORY_SIZE)*BM_MEMORY_SIZE;
        }
        else
        {
            u32BufferPosition = 0;
        }
        msAPI_FCtrl_FileSeek((U8)u32FileHandle, u32BufferPosition, FILE_SEEK_SET);
        u32BufferSize = 0;
        BM_DBG(printf("    XXX\n"));
        //BM_DBG(printf("    No hit seek to %lu, File Pos: %lu\n",u32BufferPosition,u32FilePosition));
    }
    else
    {
        BM_DBG(printf("    OOO\n"));
        //BM_DBG(printf("    Hit, Cur Pos %lu, File Pos: %lu\n",u32BufferPosition,u32FilePosition));
    }
    
    //If read size over file size 
    if(u32ReadByteLength + u32FilePosition > u32FileTotalSize)
    {
        u32ReadByteLength = u32FileTotalSize - u32FilePosition;
    }  
 
    while(u32ProcessByteLength < u32ReadByteLength)
    {
        //read next
        if(u32BufferSize == 0 || 
           (u32FilePosition % BM_MEMORY_SIZE == 0 && u32FilePosition < u32FileTotalSize && u32FilePosition != 0)
          )
        {
            u32FailReadSize = msAPI_FCtrl_FileRead((U8)u32FileHandle, _VA2PA((U32)u8BufferAddr), BM_MEMORY_SIZE);
            //printf("# Cur File Pos: %lu\n",msAPI_FCtrl_FileTell((U8)u32FileHandle));
            u32BufferSize = BM_MEMORY_SIZE - u32FailReadSize;
            //BM_DBG(printf("# UnRead Length:%lu, buff size : %lu \n", u32FailReadSize, u32BufferSize));

            MsOS_Dcache_Flush((U32)u8BufferAddr, BM_MEMORY_SIZE);
            MsOS_FlushMemory();
            
            if(u32FailReadSize == BM_MEMORY_SIZE)
            {
                goto _MApp_BM_FileRead_End;
            }
        }
    
        //compute read size for current BM memory
        u32ReadByteCnt = u32BufferSize - u32ReadByteCnt;
        if(u32ReadByteCnt > (u32ReadByteLength - u32ProcessByteLength))
        {
            u32ReadByteCnt = u32ReadByteLength - u32ProcessByteLength;
        }

        //MsOS_Dcache_Flush((U32)u8BufferAddr, BM_MEMORY_SIZE);
        //MsOS_FlushMemory();

        //copy to dest buffer
        memcpy((U8*)_PA2VA((U32)pBuffAddr) + u32ProcessByteLength, &u8BufferAddr[0] + u32FilePosition % BM_MEMORY_SIZE, u32ReadByteCnt);
        
        //BM_DBG(printf("# Copy to %lu from %lu , Length:%lu\n",u32ProcessByteLength, (u32FilePosition % BM_MEMORY_SIZE),u32ReadByteCnt));
        u32ProcessByteLength += u32ReadByteCnt;
        u32FilePosition += u32ReadByteCnt;          
        u32ReadByteCnt = 0;
    }
    
_MApp_BM_FileRead_End:

    //_MApp_BM_FileRead(U32 u32FileHandle, void *pBuffAddr, U32 u32ReadByteLength)

    // Read : address =?  request = ? real = ?, tell = ?\n   ==> file
    // Data => file \n

    m_astBMHandler[u8Idx].u32FilePosition += u32ProcessByteLength;
    if( m_astBMHandler[u8Idx].u32FilePosition > 0)
    {
        m_astBMHandler[u8Idx].u32BufferPosition = ((m_astBMHandler[u8Idx].u32FilePosition-1)/BM_MEMORY_SIZE)*BM_MEMORY_SIZE;
    }
    else
    {
        m_astBMHandler[u8Idx].u32BufferPosition = 0;
    }

    m_astBMHandler[u8Idx].u32BufferSize = u32BufferSize;
    
    //BM_DBG(printf("    Read Done, Cur Pos %lu, File Pos: %lu\n",m_astBMHandler[u8Idx].u32BufferPosition, m_astBMHandler[u8Idx].u32FilePosition));
    //BM_DBG(printf("    Length = %lu UnRead = %lu\n",u32ProcessByteLength,(u32OriginalReadByte - u32ProcessByteLength)));
    return (u32OriginalReadByte - u32ProcessByteLength);
}

//******************************************************************************
/// Only update the file postition.
/// @param  pPrivate  \b IN Specify the file handle
/// @param  u64Pos    \b IN Specify the target file position
/// @param  eType     \b IN Specify the E_DATA_STREAM_SEEK_OPTION
/// @return BOOLEAN
//******************************************************************************
BOOLEAN _MApp_BufferManage_FileSeek(U32 u32FileHandle, LongLong u64Pos, E_DATA_STREAM_SEEK_OPTION eOption)
{
    U32 u32TargetPos;
    U32 u32FileTotalSize;
    U8 u8Idx = 0;
    EN_FILE_SEEK_OPTION eFileSeekOpt;

    if(u32FileHandle == INVALID_FILE_HANDLE)
    {
        return FALSE;
    }
    
    u32FileTotalSize = msAPI_FCtrl_FileLength((U8)u32FileHandle);
    switch (eOption)
    {
        case E_DATA_STREAM_SEEK_SET:
        default:
            u32TargetPos = u64Pos.Lo;
            eFileSeekOpt = FILE_SEEK_SET;
            break;

        case E_DATA_STREAM_SEEK_CUR:
            u32TargetPos = m_astBMHandler[u8Idx].u32FilePosition + u64Pos.Lo;
            eFileSeekOpt = FILE_SEEK_CUR;
            break;
    }

    for(u8Idx = 0; u8Idx < MAX_BM_HANDLER_NUM; u8Idx++)
    {
        if(m_astBMHandler[u8Idx].u8Handle == u32FileHandle)
        {
            break;
        }
    }

    if(u8Idx == MAX_BM_HANDLER_NUM)
    {
        BM_DBG(printf("[BM] Seek. file handle: %d is not belong to BM\n",u32FileHandle));
        return msAPI_FCtrl_FileSeek((U8)u32FileHandle, u64Pos.Lo, eFileSeekOpt);
    }
    
    m_astBMHandler[u8Idx].u32FilePosition= ((u32TargetPos> u32FileTotalSize) ? u32FileTotalSize : u32TargetPos);
    BM_DBG(printf("Seek to %lu\n",m_astBMHandler[u8Idx].u32FilePosition));
    return TRUE;
}

//******************************************************************************
/// Get the current file postition.
/// @param  pPrivate  \b IN Specify the file handle
/// @return LongLong
//******************************************************************************
LongLong _MApp_BufferManage_FileTell(U32 u32FileHandle)
{
    U8 u8Idx = 0;
    LongLong u64Pos;

    if(u32FileHandle == INVALID_FILE_HANDLE)
    {
        memset(&u64Pos, 1, sizeof(LongLong)); //0xFFFFFFFF
        return u64Pos;
    }
    
    for(u8Idx = 0; u8Idx < MAX_BM_HANDLER_NUM; u8Idx++)
    {
        if(m_astBMHandler[u8Idx].u8Handle == u32FileHandle)
        {
            break;
        }
    }

    if(u8Idx == MAX_BM_HANDLER_NUM)
    {
        BM_DBG(printf("[BM] Tell. file handle: %d is not belong to BM\n",u32FileHandle));
        memset(&u64Pos, 0, sizeof(LongLong));
        u64Pos.Lo = msAPI_FCtrl_FileTell((U8)u32FileHandle);
    }
    else
    {
        memset(&u64Pos, 0, sizeof(LongLong));
        u64Pos.Lo = m_astBMHandler[u8Idx].u32FilePosition;
    }
    return u64Pos;
}

//******************************************************************************
/// Get the current file length.
/// @param  pPrivate  \b IN Specify the file handle
/// @return LongLong
//******************************************************************************
LongLong _MApp_BufferManage_FileLength(U32 u32FileHandle)
{
    LongLong u64Length;
    memset(&u64Length, 0, sizeof(LongLong));
    u64Length = msAPI_FCtrl_FileLength_LongLong((U8)u32FileHandle);

    return u64Length;
}

#undef _MSAPI_BUFFER_MANAGE_C_

