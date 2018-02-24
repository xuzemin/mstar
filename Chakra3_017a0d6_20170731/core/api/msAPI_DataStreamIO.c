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

#define _MSAPI_DATA_STREAM_IO_C_
///////////////////////////////////////////////////////////////////////////////
/// @file   msAPI_DataStreamIO.c
/// @author MStar Semiconductor Inc.
/// @brief  Data stream I/O Module
///////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "MsCommon.h"
#include "MsOS.h"

#include "msAPI_DataStreamIO.h"

#include "msAPI_FCtrl.h"
#include "msAPI_FSCommon.h"

//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Type and Structure Declaration
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------
#define DATA_STREAM_MODE_BASE      4
#define DATA_STREAM_SET_MODE(hdl, mode)    ((hdl) + ((mode) << DATA_STREAM_MODE_BASE))
#define DATA_STREAM_GET_MODE(x)    ((x) >> DATA_STREAM_MODE_BASE)
#define DATA_STREAM_GET_HANDLE(x)  ((x) & ((1 << DATA_STREAM_MODE_BASE)-1))


//-------------------------------------------------------------------------------------------------
// Global Variables
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Local Variables
//-------------------------------------------------------------------------------------------------
static FN_DATA_STRM_IO _gStreamIOFunc[E_DATA_STREAM_MODE_NUM], *_gpStreamIOFunc[E_DATA_STREAM_MODE_NUM] = {NULL};
static E_DATA_STREAM_MODE m_eStreamMode = E_DATA_STREAM_MODE_BASIC;

//-------------------------------------------------------------------------------------------------
// Local Function Prototypes
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Function Implementation
//-------------------------------------------------------------------------------------------------
U32 msAPI_DataStreamIO_Open(void *pPrivate, U8 u8Mode, E_DATA_STREAM_TYPE eType)
{
    U8 u8FileHdl;

    if (eType >= E_DATA_STREAM_TYPE_NUM)
    {
        return INVALID_DATA_STREAM_HDL;
    }

    if (_gpStreamIOFunc[m_eStreamMode] == NULL || _gpStreamIOFunc[m_eStreamMode]->pfnOpen == NULL )
    {
        // default
        u8FileHdl = msAPI_FCtrl_FileOpen((FileEntry *)pPrivate, u8Mode);
    }
    else
    {
        u8FileHdl = DATA_STREAM_SET_MODE(_gpStreamIOFunc[m_eStreamMode]->pfnOpen(pPrivate, u8Mode, eType), m_eStreamMode);
    }

    return u8FileHdl;
}

BOOLEAN msAPI_DataStreamIO_Close(U32 u32Hdl)
{
    U16 u16StreamMode = DATA_STREAM_GET_MODE(u32Hdl);
    BOOLEAN bRet = FALSE;

    if((E_DATA_STREAM_MODE)u16StreamMode >= E_DATA_STREAM_MODE_NUM)
    {
        return FALSE;
    }

    if (_gpStreamIOFunc[u16StreamMode] == NULL || _gpStreamIOFunc[u16StreamMode]->pfnClose == NULL)
    {
        // default
        bRet = msAPI_FCtrl_FileClose((U8)DATA_STREAM_GET_HANDLE(u32Hdl)) == FILE_CLOSE_RESULT_ERROR ? FALSE : TRUE;
    }
    else
    {
        bRet = _gpStreamIOFunc[u16StreamMode]->pfnClose(DATA_STREAM_GET_HANDLE(u32Hdl));
    }

    return bRet ;
}

U32 msAPI_DataStreamIO_Read(U32 u32Hdl, void *pBuffAddr, U32 u32Length)
{
    U16 u16StreamMode = DATA_STREAM_GET_MODE(u32Hdl);
    U32 u32RetLength;

    if((E_DATA_STREAM_MODE)u16StreamMode >= E_DATA_STREAM_MODE_NUM)
    {
        return u32Length;
    }

    if (_gpStreamIOFunc[u16StreamMode] == NULL || _gpStreamIOFunc[u16StreamMode]->pfnRead == NULL)
    {
        // default
        u32RetLength = msAPI_FCtrl_FileRead((U8)DATA_STREAM_GET_HANDLE(u32Hdl), (U32)pBuffAddr, u32Length);
    }
    else
    {
        u32RetLength = _gpStreamIOFunc[u16StreamMode]->pfnRead(DATA_STREAM_GET_HANDLE(u32Hdl), pBuffAddr, u32Length);
    }

    return u32RetLength;
}

BOOLEAN msAPI_DataStreamIO_Seek(U32 u32Hdl, U32 u32Pos, E_DATA_STREAM_SEEK_OPTION eOption)
{
    BOOLEAN bRet = FALSE;
    EN_FILE_SEEK_OPTION eFileSeekOpt;
    LongLong u64Pos;
    U16 u16StreamMode = DATA_STREAM_GET_MODE(u32Hdl);

    if((E_DATA_STREAM_MODE)u16StreamMode >= E_DATA_STREAM_MODE_NUM)
    {
        return FALSE;
    }

    switch (eOption)
    {
        case E_DATA_STREAM_SEEK_SET:
        default:
            eFileSeekOpt = FILE_SEEK_SET;
            break;

        case E_DATA_STREAM_SEEK_CUR:
            eFileSeekOpt = FILE_SEEK_CUR;
            break;
    }

    if (_gpStreamIOFunc[u16StreamMode] == NULL || _gpStreamIOFunc[u16StreamMode]->pfnSeek == NULL)
    {
        // default
        bRet = msAPI_FCtrl_FileSeek((U8)DATA_STREAM_GET_HANDLE(u32Hdl), u32Pos, eFileSeekOpt);
    }
    else
    {
        u64Pos.Hi = 0;
        u64Pos.Lo = u32Pos;
        bRet = _gpStreamIOFunc[u16StreamMode]->pfnSeek(DATA_STREAM_GET_HANDLE(u32Hdl), u64Pos, eOption);
    }

    return bRet;
}

BOOLEAN msAPI_DataStreamIO_Seek_LongLong(U32 u32Hdl, LongLong u64Pos, E_DATA_STREAM_SEEK_OPTION eOption)
{
    BOOLEAN bRet = FALSE;
    EN_FILE_SEEK_OPTION eFileSeekOpt;
    U16 u16StreamMode = DATA_STREAM_GET_MODE(u32Hdl);

    if((E_DATA_STREAM_MODE)u16StreamMode >= E_DATA_STREAM_MODE_NUM)
    {
        return FALSE;
    }

    switch (eOption)
    {
        case E_DATA_STREAM_SEEK_SET:
        default:
            eFileSeekOpt = FILE_SEEK_SET;
            break;

        case E_DATA_STREAM_SEEK_CUR:
            eFileSeekOpt = FILE_SEEK_CUR;
            break;
    }

    if (_gpStreamIOFunc[u16StreamMode] == NULL || _gpStreamIOFunc[u16StreamMode]->pfnSeek == NULL)
    {
        // default
        bRet = msAPI_FCtrl_FileSeek_LongLong((U8)DATA_STREAM_GET_HANDLE(u32Hdl), u64Pos, eFileSeekOpt);
    }
    else
    {
        bRet = _gpStreamIOFunc[u16StreamMode]->pfnSeek(DATA_STREAM_GET_HANDLE(u32Hdl), u64Pos, eOption);
    }

    return bRet;
}

U32 msAPI_DataStreamIO_Tell(U32 u32Hdl)
{
    U32 u32Position;
    LongLong u64Pos;
    U16 u16StreamMode = DATA_STREAM_GET_MODE(u32Hdl);

    if((E_DATA_STREAM_MODE)u16StreamMode >= E_DATA_STREAM_MODE_NUM)
    {
        return 0xFFFFFFFF;
    }

    if (_gpStreamIOFunc[u16StreamMode] == NULL || _gpStreamIOFunc[u16StreamMode]->pfnTell == NULL)
    {
        // default
        u32Position = msAPI_FCtrl_FileTell((U8)DATA_STREAM_GET_HANDLE(u32Hdl));
    }
    else
    {
        u64Pos = _gpStreamIOFunc[u16StreamMode]->pfnTell(DATA_STREAM_GET_HANDLE(u32Hdl));
        u32Position = u64Pos.Lo;
    }

    return u32Position;
}

LongLong msAPI_DataStreamIO_Tell_LongLong(U32 u32Hdl)
{
    LongLong u64Pos;
    U16 u16StreamMode = DATA_STREAM_GET_MODE(u32Hdl);

    if((E_DATA_STREAM_MODE)u16StreamMode >= E_DATA_STREAM_MODE_NUM)
    {
        u64Pos.Hi = 0xFFFFFFFF;
        u64Pos.Lo = 0xFFFFFFFF;
        return u64Pos;
    }

    if (_gpStreamIOFunc[u16StreamMode] == NULL || _gpStreamIOFunc[u16StreamMode]->pfnTell == NULL)
    {
        // default
        u64Pos = msAPI_FCtrl_FileTell_LongLong((U8)DATA_STREAM_GET_HANDLE(u32Hdl));
    }
    else
    {
        u64Pos = _gpStreamIOFunc[u16StreamMode]->pfnTell(DATA_STREAM_GET_HANDLE(u32Hdl));
    }

    return u64Pos;
}

U32 msAPI_DataStreamIO_Length(U32 u32Hdl)
{
    U32 u32Length;
    LongLong u64Pos;
    U16 u16StreamMode = DATA_STREAM_GET_MODE(u32Hdl);

    if((E_DATA_STREAM_MODE)u16StreamMode >= E_DATA_STREAM_MODE_NUM)
    {
        return 0;
    }

    if (_gpStreamIOFunc[u16StreamMode] == NULL || _gpStreamIOFunc[u16StreamMode]->pfnLength == NULL)
    {
        // default
        u32Length = msAPI_FCtrl_FileLength((U8)DATA_STREAM_GET_HANDLE(u32Hdl));
    }
    else
    {
        u64Pos = _gpStreamIOFunc[u16StreamMode]->pfnLength(DATA_STREAM_GET_HANDLE(u32Hdl));
        u32Length = u64Pos.Lo;
    }

    return u32Length;
}

LongLong msAPI_DataStreamIO_Length_LongLong(U32 u32Hdl)
{
    LongLong u64Size;
    U16 u16StreamMode = DATA_STREAM_GET_MODE(u32Hdl);

    if((E_DATA_STREAM_MODE)u16StreamMode >= E_DATA_STREAM_MODE_NUM)
    {
        u64Size.Hi = 0;
        u64Size.Lo = 0;
        return u64Size;
    }

    if (_gpStreamIOFunc[u16StreamMode] == NULL || _gpStreamIOFunc[u16StreamMode]->pfnLength == NULL)
    {
        // default
        u64Size = msAPI_FCtrl_FileLength_LongLong((U8)DATA_STREAM_GET_HANDLE(u32Hdl));
    }
    else
    {
        u64Size = _gpStreamIOFunc[u16StreamMode]->pfnLength(DATA_STREAM_GET_HANDLE(u32Hdl));
    }

    return u64Size;
}

BOOLEAN msAPI_DataStreamIO_OptionRegistation(FN_DATA_STRM_IO *pfnIO, E_DATA_STREAM_MODE eMode)
{
    if(eMode >= E_DATA_STREAM_MODE_NUM)
    {
        return FALSE;
    }

    if (pfnIO == NULL)
    {
        if (_gpStreamIOFunc[eMode] != NULL && _gpStreamIOFunc[eMode]->pfnFinalize != NULL)
        {
            _gpStreamIOFunc[eMode]->pfnFinalize();
        }
        _gpStreamIOFunc[eMode] = NULL;
    }
    else
    {
        _gStreamIOFunc[eMode] = *pfnIO;
        _gpStreamIOFunc[eMode] = &_gStreamIOFunc[eMode];
        if (_gpStreamIOFunc[eMode] != NULL && _gpStreamIOFunc[eMode]->pfnInit != NULL)
        {
            _gpStreamIOFunc[eMode]->pfnInit();
        }
    }

    return TRUE;
}

BOOLEAN msAPI_DataStreamIO_SetStreamMode(E_DATA_STREAM_MODE eMode)
{
    if(eMode >= E_DATA_STREAM_MODE_NUM)
    {
        return FALSE;
    }

    m_eStreamMode = eMode;

    return TRUE;
}

E_DATA_STREAM_MODE msAPI_DataStreamIO_GetStreamMode(void)
{
    return m_eStreamMode;
}


//-------------------------------------------------------------------------------------------------
// Local funcion -- misc functions
//-------------------------------------------------------------------------------------------------

#undef _MSAPI_DATA_STREAM_IO_C_

