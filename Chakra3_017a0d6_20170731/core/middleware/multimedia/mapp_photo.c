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

#define _MAPP_PHOTO_C_
///////////////////////////////////////////////////////////////////////////////
/// @file   mapp_photo.c
/// @author MStar Semiconductor Inc.
/// @brief  Photo Module
///////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>

#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"
#include "sysinfo.h"

#include "drvGlobal.h"
#include "drvUART.h"

#include "apiDMX.h"

#include "msAPI_Timer.h"

#include "drvCPU.h"
#include "msAPI_CPU.h"

#include "msAPI_FCtrl.h"
#include "msAPI_FSCommon.h"

#include "msAPI_DataStreamIO.h"

#if (ENABLE_DMP)

#if (defined(ENABLE_PTP) && (ENABLE_PTP))
#include "mapp_ptp.h"
#endif // #if (defined(ENABLE_PTP) && (ENABLE_PTP))

#include "mapp_photo.h"
#include "mapp_stillimage_sharememcfg.h"

#include "InfoBlock.h"
#include "msAPI_DrvInit.h"

#include "msAPI_MailBox.h"

#include "apiGFX.h"

#include "mapp_photo_display.h"

#include "mapp_videoplayer.h"

#if ENABLE_HK_PHOTO
#include "msapi_stillimage.h"
#endif

//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
#define PHOTO_INIT_TIMEOUT      (2000)  // milli-sec
#define PHOTO_START_TIMEOUT     (1000)  // milli-sec
#define PHOTO_STOP_TIMEOUT      (2000)  // milli-sec
#define PHOTO_WDT_TIMEOUT       (1000)  // milli-sec
#define PHOTO_PROGRESS_TIMEOUT  (500)   // milli-sec
#define PHOTO_MBX_MSG_TIMEOUT   (500)   // milli-sec

#define PHOTO_STREAM_INIT_TIMEOUT      (40000)  // milli-sec
#define PHOTO_STREAM_START_TIMEOUT     (40000)  // milli-sec
#define PHOTO_STREAM_STOP_TIMEOUT      (2000)   // milli-sec
#define PHOTO_STREAM_WDT_TIMEOUT       (20000)  // milli-sec
#define PHOTO_STREAM_PROGRESS_TIMEOUT  (500)    // milli-sec

#define PHOTO_STOP_PROGRESSIVE_JPEG_TIMEOUT      (10000)  // milli-sec

#define CP_ALIVE_CHECKING_CNT   (5)     // how many PHOTO_WDT_TIMEOUT can HK say CP is not alive
#define CP_ALIVE_CHECKING_CNT_FOR_PROGRESSIVE_JPEG   (15)

#define PHOTO_NO_SINGLE_PIXEL   1   //dont allow single pixel to show
//-------------------------------------------------------------------------------------------------
// Type and Structure Declaration
//-------------------------------------------------------------------------------------------------
typedef enum
{
    E_PHOTO_STATUS_STOPPED              = 0,
    E_PHOTO_STATUS_INITED,
    E_PHOTO_STATUS_WAITING_START_ACK,
    E_PHOTO_STATUS_WORKING,
} EN_PHOTO_STATUS;

typedef enum
{
    E_PHOTO_ACKFLG_NULL         = 0,
    E_PHOTO_ACKFLG_WAIT_INIT    = BIT0,
    E_PHOTO_ACKFLG_WAIT_START   = BIT1,
    E_PHOTO_ACKFLG_WAIT_STOP    = BIT2,
} EN_PHOTO_ACK_FLAGS;

#define SET_PHOTO_FLAG(t, v, f)   \
    ((v) = (t)((U32)(v) | (U32)(f)))

#define REMOVE_PHOTO_FLAG(t, v, f)   \
    ((v) = (t)((U32)(v) & ~(U32)(f)))

typedef enum
{
    E_PHOTO_TIMER_INIT = 0,
    E_PHOTO_TIMER_START,
    E_PHOTO_TIMER_STOP,
    E_PHOTO_TIMER_DECODE,

    E_PHOTO_TIMER_WDT,      // watch dog timer
    E_PHOTO_TIMER_PROGRESS, // timer used to check progress

    E_PHOTO_TIMER_MBX_MSG,

    E_PHOTO_TIMER_NUM,
} EN_PHOTO_TIMER;

typedef struct
{
    U32 u32InitTime;    // in millisecond
    U32 u32TimeOut;     // in millisecond
    BOOLEAN bEnable;
} ST_PHOTO_TIMER;

typedef enum
{
    E_UART_SWITCH_HK,
    E_UART_SWITCH_CP,
    E_UART_SWITCH_NUM,
} EN_PHOTO_UART_SWITCH;

typedef enum
{
    E_PHOTO_DECODE     = 0,
    E_PHOTO_ENCODE,
} EN_PHOTO_CMD;

//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------
// error/debug/info message
#define PHOTO_MSG_DBG(x)        //(x)
#define PHOTO_MSG_ERR(x)        //(x)
#define PHOTO_MSG_INFO(x)       //(x)
#define PHOTO_MSG_INFO_MUST(x)  //(x)

#define _U32_MAX    (0xffffffff)
#define PHOTO_EXIF_INFO_BUFFER_SIZE   128

#if ENABLE_HK_PHOTO
static BOOLEAN bDecodeFromeMem;
#endif
//-------------------------------------------------------------------------------------------------
// Global Variables
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Local Variables
//-------------------------------------------------------------------------------------------------
static const U32 _u32Photo_ShareMemAddr = PHOTO_SHARE_MEM_BUFFER_ADDR;

static EN_PHOTO_STATUS enPhoto_Status = E_PHOTO_STATUS_STOPPED;

static EN_PHOTO_ACK_FLAGS enPhoto_AckFlags = E_PHOTO_ACKFLG_NULL;
static EN_PHOTO_ERRCODE _enPhoto_ErrCode = E_PHOTO_ERR_NONE;
static U32 _u32Photo_Progress = 0;
static ST_PHOTO_TIMER _stPhoto_Timer[E_PHOTO_TIMER_NUM];

static BOOLEAN _bPhoto_DecodeThumbnail = FALSE;
static U8 _u8Photo_Decode_FileHandle = INVALID_FILE_HANDLE;
static U32 _u32Photo_Decode_FileSize = 0;

// NOTE: _u32PoolMemAddr and _u32ProgressiveJpegMemAddr are now mutual exclusive now
//      but it depends on decoder implementation on CP
static U32 _u32DataBuffAddr = 0, _u32OutputBuffAddr = 0, _u32PoolMemAddr = 0, _u32ProgressiveJpegMemAddr = 0, _u32GifFrameInfoArrayAddr = 0;
static U32 _u32DataBuffSize = 0, _u32OutputBuffSize = 0, _u32PoolMemSize = 0, _u32ProgressiveJpegMemSize = 0, _u32GifFrameInfoArraySize = 0;
static U32 m_u32MinDecodeWidth                = 0, m_u32MinDecodeHeight                = 0;
static U32 m_u32MaxDecodeJpegBaselineWidth    = 0, m_u32MaxDecodeJpegBaselineHeight    = 0;
static U32 m_u32MaxDecodeJpegProgressiveWidth = 0, m_u32MaxDecodeJpegProgressiveHeight = 0;
static U32 m_u32MaxDecodeBmpWidth             = 0, m_u32MaxDecodeBmpHeight             = 0;
static U32 m_u32MaxDecodePngWidth             = 0, m_u32MaxDecodePngHeight             = 0;
static U32 m_u32MaxDecodeTiffWidth            = 0, m_u32MaxDecodeTiffHeight            = 0;
static U32 m_u32MaxDecodeGifWidth             = 0, m_u32MaxDecodeGifHeight             = 0;
static U32 m_u32MaxDecodeMpoBaselineWidth     = 0, m_u32MaxDecodeMpoBaselineHeight     = 0;
static U32 m_u32MaxDecodeMpoProgressiveWidth  = 0, m_u32MaxDecodeMpoProgressiveHeight  = 0;

static EN_PHOTO_CMD _enPhotoCmd = E_PHOTO_DECODE;

static BOOLEAN _gTotalSizeUnknown = FALSE;
static MApp_Photo_DataRequestCallBack _gDataRequestCallBack = NULL;
static U32 _u32ResidualReadSize = 0;
static U32 _u32ReadBuffAddr = NULL;
#if (!ENABLE_HK_PHOTO)
static MBX_Class _eMbxCmdClass;
static MB_STILLIMAGE_DATA_IO _eDataIo;
#endif

static U32  _u32Photo_Init_Timeout      = PHOTO_INIT_TIMEOUT;
static U32  _u32Photo_Start_Timeout     = PHOTO_START_TIMEOUT;
static U32  _u32Photo_Stop_Timeout      = PHOTO_STOP_TIMEOUT;
static U32  _u32Photo_WDT_Timeout       = PHOTO_WDT_TIMEOUT;
static U32  _u32Photo_Progress_Timeout  = PHOTO_PROGRESS_TIMEOUT;

static BOOLEAN _bEnableStreamMode = FALSE;
static U32 _u32PreGifDecodedFrameIndex = _U32_MAX;
static BOOLEAN bDoAlphaBlendForPng = TRUE;
static BOOLEAN m_bForceDisplayPartialError = TRUE;

//-------------------------------------------------------------------------------------------------
// Local Function Prototypes
//-------------------------------------------------------------------------------------------------
static void     _MApp_Photo_Reset(BOOLEAN bForceResetMem);
static void     _MApp_Photo_Stop(void);
static BOOLEAN  _MApp_Photo_Decode_MemoryValidation(EN_PHOTO_CMD enCmd);
static void     _MApp_Photo_SetErrCode(BOOLEAN bFromShareMem, EN_PHOTO_ERRCODE enErrCode);
static void     _MApp_Photo_Decode_ShowImageInfo(void);

static void     _MApp_Photo_Timer_Init(EN_PHOTO_TIMER enTimer, U32 u32TimeOut);
static BOOLEAN  _MApp_Photo_Timer_IsTimeOut(EN_PHOTO_TIMER enTimer);
static void     _MApp_Photo_Timer_Disable(EN_PHOTO_TIMER enTimer);
#if (!ENABLE_HK_PHOTO)
static void _MApp_Photo_ShareMem_SetInfo(EN_STILLIMAGE_SHAREMEMORY enInfo, U32 u32Value);
static U32  _MApp_Photo_ShareMem_GetInfo(EN_STILLIMAGE_SHAREMEMORY enInfo);
static BOOLEAN  _MApp_Photo_CheckCPAlive(void);
static void     _MApp_Photo_UartSwitch(EN_PHOTO_UART_SWITCH enUartSwitch);
static BOOLEAN  _MApp_Photo_SendCmd(MBX_Msg *pmbxMsg);
static void     _MApp_Photo_SendCmd_Init(void);
static void     _MApp_Photo_SendCmd_Start(void);
static void     _MApp_Photo_SendCmd_Stop(void);
static void     _MApp_Photo_SendCmd_AbortDataOperation(void);

static void _MApp_Photo_SendAck_FileOpen(void);
static void _MApp_Photo_SendAck_FileClose(void);
static void _MApp_Photo_SendAck_FileRead(MBX_Class enCmdClass, MB_STILLIMAGE_DATA_IO enIoType, U32 u32UnReadSize);
static void _MApp_Photo_SendAck_FileSeek(MBX_Class enCmdClass, MB_STILLIMAGE_DATA_IO enIoType);
static void _MApp_Photo_SendAck_Memory_TotalSize(MBX_Class enCmdClass, MB_STILLIMAGE_DATA_IO enIoType, U32 u32TotalSize);
static void _MApp_Photo_SendAck_Memory_RequestData(MBX_Class enCmdClass, MB_STILLIMAGE_DATA_IO enIoType, U32 u32UnReadSize, BOOLEAN bMore);

static BOOLEAN  _MApp_Photo_MailBox_Init(void);
static void     _MApp_Photo_MailBox_Clear(void);
static void     _MApp_Photo_MailBox_Handler(void);
static void     _MApp_Photo_FileReadHandler(U32 u32Addr, U32 u32Size);
#else
static BOOLEAN _MApp_Photo_DataIO_Open(U64 *pu64Size, U8 *pu8Hdl);
static BOOLEAN _MApp_Photo_DataIO_Close(U8 u8Hdl);
static U32 _MApp_Photo_DataIO_Read(U8 u8Hdl, U32 u32Addr, U32 u32Size);
static BOOLEAN _MApp_Photo_DataIO_Seek(U8 u8Hdl, U64 u64Offset);
#endif
static BOOLEAN  _MApp_Photo_FileOpen(FileEntry *pFileEntry);
static void     _MApp_Photo_FileClose(void);
static U32      _MApp_Photo_FileRead(U32 u32Addr, U32 u32Size);
static BOOLEAN  _MApp_Photo_FileSeek(U32 u32Offset);
static U32      _MApp_Photo_FileLength(void);
static U32      _MApp_Photo_FileTell(void);

//-------------------------------------------------------------------------------------------------
// Function Implementation
//-------------------------------------------------------------------------------------------------
void MApp_Photo_MemCfg(
        U32 u32DataBufferAddr,      U32 u32DataBufferSize,
        U32 u32OutputBufferAddr,    U32 u32OutputBufferSize,
        U32 u32PoolMemAddr,         U32 u32PoolMemSize,
        U32 u32PoolBufferSize)
{
    _u32DataBuffAddr = u32DataBufferAddr;
    _u32DataBuffSize = u32DataBufferSize;

    _u32OutputBuffAddr = u32OutputBufferAddr;
    _u32OutputBuffSize = u32OutputBufferSize;

    // _u32PoolMemAddr & _u32ProgressiveJpegMemAddr are mutual exclusive now
    _u32PoolMemAddr = u32PoolMemAddr;
    _u32PoolMemSize = u32PoolBufferSize;

    _u32ProgressiveJpegMemAddr = u32PoolMemAddr;
    _u32ProgressiveJpegMemSize = u32PoolMemSize;


}

//******************************************************************************
/// Set photo decode resolution parameters.
/// @param  stPhotoResolution \b IN Specify structure of resolution parameters.
/// @return void.
//******************************************************************************
void MApp_Photo_DecodeResolutionCfg(ST_PHOTO_DECODE_RESOLUTION_DEFINTIONS stPhotoResolution)
{
    m_u32MinDecodeWidth = stPhotoResolution.u32MinDecodeWidth;
    m_u32MinDecodeHeight = stPhotoResolution.u32MinDecodeHeight;

    m_u32MaxDecodeJpegBaselineWidth = stPhotoResolution.u32MaxDecodeJpegBaselineWidth;
    m_u32MaxDecodeJpegBaselineHeight = stPhotoResolution.u32MaxDecodeJpegBaselineHeight;

    m_u32MaxDecodeJpegProgressiveWidth = stPhotoResolution.u32MaxDecodeJpegProgressiveWidth;
    m_u32MaxDecodeJpegProgressiveHeight = stPhotoResolution.u32MaxDecodeJpegProgressiveHeight;

    m_u32MaxDecodeBmpWidth = stPhotoResolution.u32MaxDecodeBmpWidth;
    m_u32MaxDecodeBmpHeight = stPhotoResolution.u32MaxDecodeBmpHeight;

    m_u32MaxDecodePngWidth = stPhotoResolution.u32MaxDecodePngWidth;
    m_u32MaxDecodePngHeight = stPhotoResolution.u32MaxDecodePngHeight;

    m_u32MaxDecodeTiffWidth = stPhotoResolution.u32MaxDecodeTiffWidth;
    m_u32MaxDecodeTiffHeight = stPhotoResolution.u32MaxDecodeTiffHeight;

    m_u32MaxDecodeGifWidth = stPhotoResolution.u32MaxDecodeGifWidth;
    m_u32MaxDecodeGifHeight = stPhotoResolution.u32MaxDecodeGifHeight;

    m_u32MaxDecodeMpoBaselineWidth = stPhotoResolution.u32MaxDecodeMpoBaselineWidth;
    m_u32MaxDecodeMpoBaselineHeight = stPhotoResolution.u32MaxDecodeMpoBaselineHeight;

    m_u32MaxDecodeMpoProgressiveWidth = stPhotoResolution.u32MaxDecodeMpoProgressiveWidth;
    m_u32MaxDecodeMpoProgressiveHeight = stPhotoResolution.u32MaxDecodeMpoProgressiveHeight;
}

void MApp_Photo_EnableStreamMode(BOOLEAN bEnabled)
{
    _bEnableStreamMode = bEnabled;
    if(_bEnableStreamMode)
    {
        _u32Photo_Init_Timeout      = PHOTO_STREAM_INIT_TIMEOUT;
        _u32Photo_Start_Timeout     = PHOTO_STREAM_START_TIMEOUT;
        _u32Photo_Stop_Timeout      = PHOTO_STREAM_STOP_TIMEOUT;
        _u32Photo_WDT_Timeout       = PHOTO_STREAM_WDT_TIMEOUT;
        _u32Photo_Progress_Timeout  = PHOTO_STREAM_PROGRESS_TIMEOUT;
    }
    else
    {
        _u32Photo_Init_Timeout      = PHOTO_INIT_TIMEOUT;
        _u32Photo_Start_Timeout     = PHOTO_START_TIMEOUT;
        _u32Photo_Stop_Timeout      = PHOTO_STOP_TIMEOUT;
        _u32Photo_WDT_Timeout       = PHOTO_WDT_TIMEOUT;
        _u32Photo_Progress_Timeout  = PHOTO_PROGRESS_TIMEOUT;
    }
}

void MApp_Photo_DoAlphaBlendForPng(BOOLEAN bEnabled)
{
    bDoAlphaBlendForPng = bEnabled;
}

//update gif displayed frame index, notify coprocessor this frame is displayed
void MApp_Photo_UpdateDisplayedFrameIndex(U32 u32DisplayedFrameIndex)
{
    PHOTO_MSG_INFO_MUST(printf("update displayed frame index:%d\n",u32DisplayedFrameIndex));
#if (!ENABLE_HK_PHOTO)
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_DISPLAYED_FRAME_INDEX, u32DisplayedFrameIndex);
#else
    msAPI_StillImage_UpdateDisplayedFrameIndex(u32DisplayedFrameIndex);
#endif
}

//every gif frame has a delay time(in minisecond) for animation case
U32 MApp_Photo_GetFrameDelayTime(U32 u32FrameIndex)
{
    U32 DelayTime;

    DelayTime = *(U32*)(_PA2VA((_u32GifFrameInfoArrayAddr + (u32FrameIndex%(_u32GifFrameInfoArraySize/4))*4)));
    return DelayTime;
}

#if (!ENABLE_HK_PHOTO)
BOOLEAN MApp_Photo_DecodeFile_Init(FileEntry *pFileEntry, BOOLEAN bThumbnail)
{
    U32 u32InitTimeOut;
    EN_STILLIMAGE_CONTROL_FLAGS eControlFlags = E_STILLIMAGE_CONTROL_FLAG_ENABLE_NONE;

    // check status
    if (enPhoto_Status != E_PHOTO_STATUS_STOPPED)
    {
        return FALSE;
    }

    u32InitTimeOut = _u32Photo_Init_Timeout;

    // Init mailbox
    if(!_MApp_Photo_MailBox_Init())
    {
        return FALSE;
    }

    // make sure the other side is in expected state
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_ERROR, E_STILLIMAGE_ERR_NONE);
    _MApp_Photo_Stop();

    // initialization
    _MApp_Photo_Reset(FALSE);
    _MApp_Photo_Timer_Disable(E_PHOTO_TIMER_NUM);
    _enPhoto_ErrCode = E_PHOTO_ERR_NONE;
    _u32Photo_Progress = 0;
    _u32Photo_Decode_FileSize = 0;
    _bPhoto_DecodeThumbnail = bThumbnail;

    _gTotalSizeUnknown = FALSE;
    _gDataRequestCallBack = NULL;

    // memory validation
    if (_MApp_Photo_Decode_MemoryValidation(E_PHOTO_DECODE) == FALSE)
    {
        return FALSE;
    }

#if (defined(ENABLE_PTP) && (ENABLE_PTP))
    if (MApp_PTP_DeviceInUse())
    {
        // PTP has its thumbnail put to a special location
        // and it's up to _MApp_Photo_FileRead() to get the data of thumbnail
        bThumbnail = FALSE;
    }
#endif // #if (defined(ENABLE_PTP) && (ENABLE_PTP))

    // remove all queued messages in mail box
    _MApp_Photo_MailBox_Clear();

    // switch UART
    _MApp_Photo_UartSwitch(E_UART_SWITCH_NUM);

    // open file
    if (_MApp_Photo_FileOpen(pFileEntry) == FALSE)
    {
        return FALSE;
    }

    //After open file, check file size. If the photo is 0x0 => Init fail.
    if (_u32Photo_Decode_FileSize == 0)
        return FALSE;

    // set share memory info
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_ERROR,           E_STILLIMAGE_ERR_NONE);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_CMD,             E_STILLIMAGE_DECODE);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_MIN_WIDTH,       m_u32MinDecodeWidth);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_MIN_HEIGHT,      m_u32MinDecodeHeight);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_JPEG_BASELINE_MAX_WIDTH,     m_u32MaxDecodeJpegBaselineWidth);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_JPEG_BASELINE_MAX_HEIGHT,    m_u32MaxDecodeJpegBaselineHeight);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_JPEG_PROGRESSIVE_MAX_WIDTH,  m_u32MaxDecodeJpegProgressiveWidth);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_JPEG_PROGRESSIVE_MAX_HEIGHT, m_u32MaxDecodeJpegProgressiveHeight);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_BMP_MAX_WIDTH,   m_u32MaxDecodeBmpWidth);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_BMP_MAX_HEIGHT,  m_u32MaxDecodeBmpHeight);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_PNG_MAX_WIDTH,   m_u32MaxDecodePngWidth);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_PNG_MAX_HEIGHT,  m_u32MaxDecodePngHeight);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_TIFF_MAX_WIDTH,   m_u32MaxDecodeTiffWidth);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_TIFF_MAX_HEIGHT,  m_u32MaxDecodeTiffHeight);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_GIF_MAX_WIDTH,   m_u32MaxDecodeGifWidth);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_GIF_MAX_HEIGHT,  m_u32MaxDecodeGifHeight);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_MPO_BASELINE_MAX_WIDTH, m_u32MaxDecodeMpoBaselineWidth);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_MPO_BASELINE_MAX_HEIGHT, m_u32MaxDecodeMpoBaselineHeight);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_MPO_PROGRESSIVE_MAX_WIDTH, m_u32MaxDecodeMpoProgressiveWidth);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_MPO_PROGRESSIVE_MAX_HEIGHT, m_u32MaxDecodeMpoProgressiveHeight);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_DECODE_THUMBNAIL,        bThumbnail);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_INPUT_DATA_BUFF_ADDR,    _u32DataBuffAddr);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_INPUT_DATA_BUFF_LEN,     _u32DataBuffSize);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_OUTPUT_DATA_BUFF_ADDR,   _u32OutputBuffAddr);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_OUTPUT_DATA_BUFF_LEN,    _u32OutputBuffSize);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_PROGRESSIVE_BUFF_ADDR,   _u32ProgressiveJpegMemAddr);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_PROGRESSIVE_BUFF_LEN,    _u32ProgressiveJpegMemSize);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_MEM_POOL_BUFF_ADDR,      _u32PoolMemAddr);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_MEM_POOL_BUFF_LEN,       _u32PoolMemSize);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_DATA_ACCESS_METHOD,      E_STILLIMAGE_VIA_MAILBOX);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_IS_STREAM_MODE,              _bEnableStreamMode);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_STREAM_MODE_READ_TIME_OUT,   _U32_MAX);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_FRAME_INFO_ARRAY_ADDR, _u32GifFrameInfoArrayAddr);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_FRAME_INFO_ARRAY_SIZE, _u32GifFrameInfoArraySize);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_DECODED_FRAME_INDEX,     _U32_MAX);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_DISPLAYED_FRAME_INDEX,   _U32_MAX);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_ONLY_DECODE_FIRST_FRAME, FALSE);

    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_ENABLE_JPEG_DECODER);
    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_SUUPPORT_JPEG_CMYK);
    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_SUUPPORT_JPEG_RGB);
    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_STOP_WHEN_RST_ERROR);
#if ENABLE_MAPP_PHOTO_BMP
    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_ENABLE_BMP_DECODER);
#endif
#if ENABLE_MAPP_PHOTO_PNG
    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_ENABLE_PNG_DECODER);
#endif
#if ENABLE_MAPP_PHOTO_GIF
    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_ENABLE_GIF_DECODER);
#endif
#if ENABLE_MAPP_PHOTO_TIFF
    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_ENABLE_TIFF_DECODER);
#endif
    if(bDoAlphaBlendForPng)
    {
        SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_ENABLE_DO_ALPHA_BLEND_PNG);
    }
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_CONTORL_FLAGS,   (U32)eControlFlags);

    // validate share memory info
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_NUM,             STILLIMAGE_SHAREMEM_MAGICKEY);

    // send cmd
    SET_PHOTO_FLAG(EN_PHOTO_ACK_FLAGS, enPhoto_AckFlags, E_PHOTO_ACKFLG_WAIT_INIT);
    _MApp_Photo_SendCmd_Init();

    // start timer
    _MApp_Photo_Timer_Init(E_PHOTO_TIMER_INIT, u32InitTimeOut);
    // check response
    do
    {
        // reset watch dog timer
        msAPI_Timer_ResetWDT();

        // check if request data arrived because of last _MApp_Photo_FileRead wasn't satisfied the last request
        _MApp_Photo_FileReadHandler(_u32ReadBuffAddr, _u32ResidualReadSize);

        // handle CP response by check mail box
        _MApp_Photo_MailBox_Handler();

        // check if timer times out
        if (_MApp_Photo_Timer_IsTimeOut(E_PHOTO_TIMER_INIT) == TRUE)
        {
            break;
        }
    } while (enPhoto_AckFlags & E_PHOTO_ACKFLG_WAIT_INIT);

    // check if time out or failed
    if ((enPhoto_AckFlags & E_PHOTO_ACKFLG_WAIT_INIT)
            || (MApp_Photo_GetErrCode() != E_PHOTO_ERR_NONE))
    {
        // (enPhoto_AckFlags & E_PHOTO_ACKFLG_WAIT_INIT) -- > time out
        // (MApp_Photo_GetErrCode() != E_PHOTO_ERR_NONE) -- > failed
        _MApp_Photo_Stop();
        _MApp_Photo_Reset(TRUE);
        return FALSE;
    }

    // chear output buffer
    switch ((EN_PHOTO_OUTPUT_FORMAT)MApp_Photo_GetInfo(E_PHOTO_INFO_OUTPUT_FORMAT))
    {
        case E_PHOTO_OUTPUT_ARGB8888:
            msAPI_GE_ClearFrameBufferByWord(_u32OutputBuffAddr, _u32OutputBuffSize, 0x00000000);
            MApi_GFX_FlushQueue();
            break;

        case E_PHOTO_OUTPUT_YUV422:
            msAPI_GE_ClearFrameBufferByWord(_u32OutputBuffAddr, _u32OutputBuffSize, 0x80008000);
            MApi_GFX_FlushQueue();
            break;

        default:
            break;
    }
#if PHOTO_NO_SINGLE_PIXEL
    //YUV422 will lose color if only 1 pixel, so we show unupport file
    if( (MApp_Photo_GetInfo(E_PHOTO_INFO_WIDTH)==1) || (MApp_Photo_GetInfo(E_PHOTO_INFO_HEIGHT)==1) )
    {
        PHOTO_MSG_DBG(printf("width or height is 1, dont support"));
        return FALSE;
    }
#endif

    // save cmd
    _enPhotoCmd = E_PHOTO_DECODE;
    PHOTO_MSG_INFO(printf("[PHOTO] Decode File\n"));

    enPhoto_Status = E_PHOTO_STATUS_INITED;
    PHOTO_MSG_INFO(printf("[PHOTO] statue, %d --> %d\n", E_PHOTO_STATUS_STOPPED, E_PHOTO_STATUS_INITED));

    // show detail information
    _MApp_Photo_Decode_ShowImageInfo();

    if(MApp_Photo_GetInfo(E_PHOTO_INFO_IMAGE_TYPE) == E_PHOTO_IMAGE_JPEG_PROGRESSIVE)
    {
        _u32Photo_Stop_Timeout      = PHOTO_STOP_PROGRESSIVE_JPEG_TIMEOUT;
    }
    else  if(_bEnableStreamMode)
    {
        _u32Photo_Stop_Timeout      = PHOTO_STREAM_STOP_TIMEOUT;
    }
    else
    {
        _u32Photo_Stop_Timeout      = PHOTO_STOP_TIMEOUT;
    }

    return TRUE;
}

BOOLEAN MApp_Photo_DecodeMemory_Init(BOOLEAN bThumbnail, MApp_Photo_DataRequestCallBack pfCallBack)
{
    U32 u32InitTimeOut = PHOTO_INIT_TIMEOUT;
    EN_STILLIMAGE_CONTROL_FLAGS eControlFlags = E_STILLIMAGE_CONTROL_FLAG_ENABLE_NONE;

    // check status
    if (enPhoto_Status != E_PHOTO_STATUS_STOPPED)
    {
        return FALSE;
    }

    // Init mailbox
    if(!_MApp_Photo_MailBox_Init())
    {
        return FALSE;
    }

    // make sure the other side is in expected state
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_ERROR, E_STILLIMAGE_ERR_NONE);
    _MApp_Photo_Stop();

    // initialization
    _MApp_Photo_Reset(FALSE);
    _MApp_Photo_Timer_Disable(E_PHOTO_TIMER_NUM);
    _enPhoto_ErrCode = E_PHOTO_ERR_NONE;
    _u32Photo_Progress = 0;
    _u32Photo_Decode_FileSize = 0;
    _bPhoto_DecodeThumbnail = bThumbnail;

    _gTotalSizeUnknown = (pfCallBack == NULL ? FALSE : TRUE);
    _gDataRequestCallBack = pfCallBack;

    // memory validation
    if (_MApp_Photo_Decode_MemoryValidation(E_PHOTO_DECODE) == FALSE)
    {
        return FALSE;
    }

    // remove all queued messages in mail box
    _MApp_Photo_MailBox_Clear();

    // switch UART
    _MApp_Photo_UartSwitch(E_UART_SWITCH_NUM);

    // set share memory info
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_ERROR,           E_STILLIMAGE_ERR_NONE);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_CMD,             E_STILLIMAGE_DECODE);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_MIN_WIDTH,       m_u32MinDecodeWidth);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_MIN_HEIGHT,      m_u32MinDecodeHeight);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_JPEG_BASELINE_MAX_WIDTH,     m_u32MaxDecodeJpegBaselineWidth);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_JPEG_BASELINE_MAX_HEIGHT,    m_u32MaxDecodeJpegBaselineHeight);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_JPEG_PROGRESSIVE_MAX_WIDTH,  m_u32MaxDecodeJpegProgressiveWidth);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_JPEG_PROGRESSIVE_MAX_HEIGHT, m_u32MaxDecodeJpegProgressiveHeight);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_BMP_MAX_WIDTH,   m_u32MaxDecodeBmpWidth);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_BMP_MAX_HEIGHT,  m_u32MaxDecodeBmpHeight);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_PNG_MAX_WIDTH,   m_u32MaxDecodePngWidth);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_PNG_MAX_HEIGHT,  m_u32MaxDecodePngHeight);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_TIFF_MAX_WIDTH,   m_u32MaxDecodeTiffWidth);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_TIFF_MAX_HEIGHT,  m_u32MaxDecodeTiffHeight);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_GIF_MAX_WIDTH,   m_u32MaxDecodeGifWidth);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_GIF_MAX_HEIGHT,  m_u32MaxDecodeGifHeight);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_DECODE_THUMBNAIL,        bThumbnail);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_INPUT_DATA_BUFF_ADDR,    _u32DataBuffAddr);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_INPUT_DATA_BUFF_LEN,     _u32DataBuffSize);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_OUTPUT_DATA_BUFF_ADDR,   _u32OutputBuffAddr);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_OUTPUT_DATA_BUFF_LEN,    _u32OutputBuffSize);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_PROGRESSIVE_BUFF_ADDR,   _u32ProgressiveJpegMemAddr);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_PROGRESSIVE_BUFF_LEN,    _u32ProgressiveJpegMemSize);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_MEM_POOL_BUFF_ADDR,      _u32PoolMemAddr);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_MEM_POOL_BUFF_LEN,       _u32PoolMemSize);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_DATA_ACCESS_METHOD,      E_STILLIMAGE_IN_MEMORY);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_IS_STREAM_MODE,      FALSE);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_FRAME_INFO_ARRAY_ADDR, _u32GifFrameInfoArrayAddr);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_FRAME_INFO_ARRAY_SIZE, _u32GifFrameInfoArraySize);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_DECODED_FRAME_INDEX,     _U32_MAX);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_DISPLAYED_FRAME_INDEX,   _U32_MAX);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_ONLY_DECODE_FIRST_FRAME, FALSE);

    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_ENABLE_JPEG_DECODER);
    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_SUUPPORT_JPEG_CMYK);
    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_SUUPPORT_JPEG_RGB);
    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_STOP_WHEN_RST_ERROR);
#if ENABLE_MAPP_PHOTO_BMP
    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_ENABLE_BMP_DECODER);
#endif
#if ENABLE_MAPP_PHOTO_PNG
    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_ENABLE_PNG_DECODER);
#endif
#if ENABLE_MAPP_PHOTO_GIF
    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_ENABLE_GIF_DECODER);
#endif
#if ENABLE_MAPP_PHOTO_TIFF
    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_ENABLE_TIFF_DECODER);
#endif
    if(bDoAlphaBlendForPng)
    {
        SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_ENABLE_DO_ALPHA_BLEND_PNG);
    }
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_CONTORL_FLAGS,   (U32)eControlFlags);

    // validate share memory info
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_NUM,             STILLIMAGE_SHAREMEM_MAGICKEY);

    // send cmd
    SET_PHOTO_FLAG(EN_PHOTO_ACK_FLAGS, enPhoto_AckFlags, E_PHOTO_ACKFLG_WAIT_INIT);
    _MApp_Photo_SendCmd_Init();

    // start timer
    _MApp_Photo_Timer_Init(E_PHOTO_TIMER_INIT, u32InitTimeOut);
    // check response
    do
    {
        // reset watch dog timer
        msAPI_Timer_ResetWDT();

        // check if request data arrived because of last _MApp_Photo_FileRead wasn't satisfied the last request
        _MApp_Photo_FileReadHandler(_u32ReadBuffAddr, _u32ResidualReadSize);

        // handle CP response by check mail box
        _MApp_Photo_MailBox_Handler();

        // check if timer times out
        if (_MApp_Photo_Timer_IsTimeOut(E_PHOTO_TIMER_INIT) == TRUE)
        {
            break;
        }
    } while (enPhoto_AckFlags & E_PHOTO_ACKFLG_WAIT_INIT);

    // check if time out or failed
    if ((enPhoto_AckFlags & E_PHOTO_ACKFLG_WAIT_INIT)
            || (MApp_Photo_GetErrCode() != E_PHOTO_ERR_NONE))
    {
        // (enPhoto_AckFlags & E_PHOTO_ACKFLG_WAIT_INIT) -- > time out
        // (MApp_Photo_GetErrCode() != E_PHOTO_ERR_NONE) -- > failed
        _MApp_Photo_Stop();
        _MApp_Photo_Reset(TRUE);
        return FALSE;
    }

    // chear output buffer
    switch ((EN_PHOTO_OUTPUT_FORMAT)MApp_Photo_GetInfo(E_PHOTO_INFO_OUTPUT_FORMAT))
    {
        case E_PHOTO_OUTPUT_ARGB8888:
            msAPI_GE_ClearFrameBufferByWord(_u32OutputBuffAddr, _u32OutputBuffSize, 0x00000000);
            MApi_GFX_FlushQueue();
            break;

        case E_PHOTO_OUTPUT_YUV422:
            msAPI_GE_ClearFrameBufferByWord(_u32OutputBuffAddr, _u32OutputBuffSize, 0x80008000);
            MApi_GFX_FlushQueue();
            break;

        default:
            break;
    }

#if PHOTO_NO_SINGLE_PIXEL
    //YUV422 will lose color if only 1 pixel, so we show unupport file
    if( (MApp_Photo_GetInfo(E_PHOTO_INFO_WIDTH)==1) || (MApp_Photo_GetInfo(E_PHOTO_INFO_HEIGHT)==1) )
    {
        PHOTO_MSG_DBG(printf("width or height is 1, dont support"));
        return FALSE;
    }
#endif

    // save cmd
    _enPhotoCmd = E_PHOTO_DECODE;
    PHOTO_MSG_INFO(printf("[PHOTO] Decode Memory\n"));

    enPhoto_Status = E_PHOTO_STATUS_INITED;
    PHOTO_MSG_INFO(printf("[PHOTO] statue, %d --> %d\n", E_PHOTO_STATUS_STOPPED, E_PHOTO_STATUS_INITED));

    // show detail information
    _MApp_Photo_Decode_ShowImageInfo();

    return TRUE;
}

BOOLEAN MApp_Photo_EncodeMemory_Init(U32 u32Width, U32 u32Height, MApp_Photo_DataRequestCallBack pfCallBack)
{
    U32 u32InitTimeOut = PHOTO_INIT_TIMEOUT;
    EN_STILLIMAGE_CONTROL_FLAGS eControlFlags = E_STILLIMAGE_CONTROL_FLAG_ENABLE_NONE;

    // check status
    if (enPhoto_Status != E_PHOTO_STATUS_STOPPED)
    {
        return FALSE;
    }

    // init mailbox
    if(!_MApp_Photo_MailBox_Init())
    {
        return FALSE;
    }

    // make sure the other side is in expected state
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_ERROR, E_STILLIMAGE_ERR_NONE);
    _MApp_Photo_Stop();

    // initialization
    _MApp_Photo_Reset(FALSE);
    _MApp_Photo_Timer_Disable(E_PHOTO_TIMER_NUM);
    _enPhoto_ErrCode = E_PHOTO_ERR_NONE;
    _u32Photo_Progress = 0;

    _gTotalSizeUnknown = (pfCallBack == NULL ? FALSE : TRUE);
    _gDataRequestCallBack = pfCallBack;

    // memory validation
    if (_MApp_Photo_Decode_MemoryValidation(E_PHOTO_ENCODE) == FALSE)
    {
        return FALSE;
    }

    // remove all queued messages in mail box
    _MApp_Photo_MailBox_Clear();

    // switch UART
    _MApp_Photo_UartSwitch(E_UART_SWITCH_NUM);

    // set share memory info
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_ERROR,           E_STILLIMAGE_ERR_NONE);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_CMD,             E_STILLIMAGE_ENCODE);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_JPEG_BASELINE_MAX_WIDTH,     u32Width);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_JPEG_BASELINE_MAX_HEIGHT,    u32Height);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_INPUT_DATA_BUFF_ADDR,    _u32DataBuffAddr);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_INPUT_DATA_BUFF_LEN,     _u32DataBuffSize);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_OUTPUT_DATA_BUFF_ADDR,   _u32OutputBuffAddr);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_OUTPUT_DATA_BUFF_LEN,    _u32OutputBuffSize);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_MEM_POOL_BUFF_ADDR,      _u32PoolMemAddr);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_MEM_POOL_BUFF_LEN,       _u32PoolMemSize);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_DATA_ACCESS_METHOD,      E_STILLIMAGE_IN_MEMORY);

    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_IS_STREAM_MODE,      FALSE);

    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_ENABLE_JPEG_ENCODER);
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_CONTORL_FLAGS,   (U32)eControlFlags);

    // validate share memory info
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_NUM,             STILLIMAGE_SHAREMEM_MAGICKEY);

    // send cmd
    SET_PHOTO_FLAG(EN_PHOTO_ACK_FLAGS, enPhoto_AckFlags, E_PHOTO_ACKFLG_WAIT_INIT);
    _MApp_Photo_SendCmd_Init();

    // start timer
    _MApp_Photo_Timer_Init(E_PHOTO_TIMER_INIT, u32InitTimeOut);
    // check response
    do
    {
        // reset watch dog timer
        msAPI_Timer_ResetWDT();

        // check if request data arrived because of last _MApp_Photo_FileRead wasn't satisfied the last request
        _MApp_Photo_FileReadHandler(_u32ReadBuffAddr, _u32ResidualReadSize);

        // handle CP response by check mail box
        _MApp_Photo_MailBox_Handler();

        // check if timer times out
        if (_MApp_Photo_Timer_IsTimeOut(E_PHOTO_TIMER_INIT) == TRUE)
        {
            break;
        }
    } while (enPhoto_AckFlags & E_PHOTO_ACKFLG_WAIT_INIT);

    // check if time out or failed
    if ((enPhoto_AckFlags & E_PHOTO_ACKFLG_WAIT_INIT)
            || (MApp_Photo_GetErrCode() != E_PHOTO_ERR_NONE))
    {
        // (enPhoto_AckFlags & E_PHOTO_ACKFLG_WAIT_INIT) -- > time out
        // (MApp_Photo_GetErrCode() != E_PHOTO_ERR_NONE) -- > failed
        _MApp_Photo_Stop();
        _MApp_Photo_Reset(TRUE);
        return FALSE;
    }

    // save cmd
    _enPhotoCmd = E_PHOTO_ENCODE;
    PHOTO_MSG_INFO(printf("[PHOTO] Encode Memory\n"));

    enPhoto_Status = E_PHOTO_STATUS_INITED;
    PHOTO_MSG_INFO(printf("[PHOTO] statue, %d --> %d\n", E_PHOTO_STATUS_STOPPED, E_PHOTO_STATUS_INITED));

    return TRUE;
}

EN_RET MApp_Photo_Main(void)
{
    EN_RET enRet = EXIT_PHOTO_DECODING;
    EN_PHOTO_STATUS enPhoto_PreStatus = enPhoto_Status;
    static U32 u32StartTime = 0;

    _MApp_Photo_MailBox_Handler();

    // check if request data arrived because of last _MApp_Photo_FileRead wasn't satisfied the last request
    _MApp_Photo_FileReadHandler(_u32ReadBuffAddr, _u32ResidualReadSize);

    // check if CP alive
    if (_MApp_Photo_CheckCPAlive() == FALSE)
    {
        _MApp_Photo_Stop();
        _MApp_Photo_Reset(TRUE);
        enPhoto_Status = E_PHOTO_STATUS_STOPPED;
        return EXIT_PHOTO_DECODE_FAIL;
    }

    switch (enPhoto_Status)
    {
        default:
        case E_PHOTO_STATUS_STOPPED:
            return EXIT_PHOTO_EXIT;

        case E_PHOTO_STATUS_INITED:
            // start timer
            _MApp_Photo_Timer_Init(E_PHOTO_TIMER_PROGRESS, _u32Photo_Progress_Timeout);
            _MApp_Photo_Timer_Init(E_PHOTO_TIMER_WDT, _u32Photo_WDT_Timeout);

            // send cmd
            SET_PHOTO_FLAG(EN_PHOTO_ACK_FLAGS, enPhoto_AckFlags, E_PHOTO_ACKFLG_WAIT_START);
            _MApp_Photo_SendCmd_Start();

            // start timer
            _MApp_Photo_Timer_Init(E_PHOTO_TIMER_START, _u32Photo_Start_Timeout);

            // change status
            enPhoto_Status = E_PHOTO_STATUS_WAITING_START_ACK;

            u32StartTime = msAPI_Timer_GetTime0();
            break;

        case E_PHOTO_STATUS_WAITING_START_ACK:
            // check if times out or error
            if (!(enPhoto_AckFlags & E_PHOTO_ACKFLG_WAIT_START))
            {
                // change status
                enPhoto_Status = E_PHOTO_STATUS_WORKING;
            }
            else if ((_MApp_Photo_Timer_IsTimeOut(E_PHOTO_TIMER_START) == TRUE)
                    || (MApp_Photo_GetErrCode() != E_PHOTO_ERR_NONE))
            {
                // (_MApp_Photo_Timer_IsTimeOut(E_PHOTO_TIMER_START) == TRUE) -- > time out
                // (MApp_Photo_GetErrCode() != E_PHOTO_ERR_NONE) -- > failed
                enRet = EXIT_PHOTO_DECODE_FAIL;
            }
            break;

        case E_PHOTO_STATUS_WORKING:
            if (MApp_Photo_GetErrCode() == E_PHOTO_ERR_NONE)
            {
                EN_STILLIMAGE_ERR_CODE enStillImage_ErrCode;

                // check if job done
                enStillImage_ErrCode = (EN_STILLIMAGE_ERR_CODE)_MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_ERROR);
                if ((enStillImage_ErrCode == E_STILLIMAGE_NORMAL_STOPPED)
                        || (enStillImage_ErrCode == E_STILLIMAGE_USER_STOPPED))
                {
                    enRet = EXIT_PHOTO_DECODE_DONE;
                }

                if(MApp_Photo_GetInfo(E_PHOTO_INFO_FILE_FORMAT) == E_PHOTO_FILE_GIF)
                {
                    if(enRet != EXIT_PHOTO_DECODE_DONE)
                    {
                        U32 u32CurrDecodedFrameIndex =  _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_DECODED_FRAME_INDEX);
                        if(_u32PreGifDecodedFrameIndex != u32CurrDecodedFrameIndex)
                        {
                            _u32PreGifDecodedFrameIndex = u32CurrDecodedFrameIndex;
                            PHOTO_MSG_INFO_MUST(printf("[PHOTO] GIF frame index %lu decode done.\n",_u32PreGifDecodedFrameIndex));
                            enRet = EXIT_PHOTO_DECODE_ONE_FRAME_DONE;
                        }
                    }
                    else
                    {
                        MApp_Photo_GIFDecodeDone(TRUE);
                    }
                }

                if(MApp_Photo_GetInfo(E_PHOTO_INFO_IS_MPO_DISPARITY_TYPE))
                {
                    if(enRet != EXIT_PHOTO_DECODE_DONE)
                    {
                        U32 u32CurrDecodedFrameIndex =  _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_DECODED_FRAME_INDEX);
                        if(_u32PreGifDecodedFrameIndex != u32CurrDecodedFrameIndex)
                        {
                            _u32PreGifDecodedFrameIndex = u32CurrDecodedFrameIndex;
                            PHOTO_MSG_INFO_MUST(printf("[PHOTO] MPO frame index %lu decode done.\n",_u32PreGifDecodedFrameIndex));
                            enRet = EXIT_PHOTO_DECODE_ONE_FRAME_DONE;
                        }
                    }
                }

            }
            else
            {
                enRet = EXIT_PHOTO_DECODE_FAIL;
            }
            break;
    }

    switch (enRet)
    {
        case EXIT_PHOTO_DECODE_DONE:
            if(MApp_Photo_GetInfo(E_PHOTO_INFO_IS_MPO_DISPARITY_TYPE))
            {
                _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_DECODED_FRAME_INDEX, 1);
            }
            // fall through
        case EXIT_PHOTO_DECODE_FAIL:
            _MApp_Photo_Stop();
            _MApp_Photo_Reset(TRUE);
            _MApp_Photo_Timer_Disable(E_PHOTO_TIMER_NUM);

            PHOTO_MSG_INFO_MUST(printf("[PHOTO] total time: %lu, progress: %lu\n",
                    msAPI_Timer_DiffTimeFromNow(u32StartTime),
                    MApp_Photo_GetInfo(E_PHOTO_INFO_PROGRESS)));

            // when encoding image, information is gained after encoding done
            if (_enPhotoCmd == E_PHOTO_ENCODE)
            {
                _MApp_Photo_Decode_ShowImageInfo();
            }
            else if(m_bForceDisplayPartialError
                 && MApp_Photo_GetInfo(E_PHOTO_INFO_PROGRESS) > 0)
            {
                PHOTO_MSG_INFO_MUST(printf("[PHOTO] decode error, but decode part:%d percent.\n", MApp_Photo_GetInfo(E_PHOTO_INFO_PROGRESS)));
                enRet = EXIT_PHOTO_DECODE_DONE;
            }
            enPhoto_Status = E_PHOTO_STATUS_STOPPED;
            break;
        case EXIT_PHOTO_DECODE_ONE_FRAME_DONE:
            break;
        case EXIT_PHOTO_DECODING:
            if (_MApp_Photo_Timer_IsTimeOut(E_PHOTO_TIMER_PROGRESS))
            {
                PHOTO_MSG_INFO(printf("[PHOTO] progress: %04lu\n", MApp_Photo_GetInfo(E_PHOTO_INFO_PROGRESS)));
                _MApp_Photo_Timer_Init(E_PHOTO_TIMER_PROGRESS, _u32Photo_Progress_Timeout);
            }
            // fall through
        default:
            break;
    }

    if (enPhoto_PreStatus != enPhoto_Status)
    {
        PHOTO_MSG_INFO(printf("[PHOTO] statue, %d --> %d\n", enPhoto_PreStatus, enPhoto_Status));
    }

    return enRet;
}


void MApp_Photo_Stop(void)
{
    if (enPhoto_Status == E_PHOTO_STATUS_STOPPED)
    {
        return;
    }

    // disable timers when user stop
    _MApp_Photo_Timer_Disable(E_PHOTO_TIMER_WDT);
    _MApp_Photo_Timer_Disable(E_PHOTO_TIMER_PROGRESS);

    _MApp_Photo_Stop();
    _MApp_Photo_Reset(TRUE);
    enPhoto_Status = E_PHOTO_STATUS_STOPPED;
    bDoAlphaBlendForPng = TRUE;
}

U32 MApp_Photo_GetInfo(EN_PHOTO_INFO enInfo)
{
    U32 u32Info;

    switch (enInfo)
    {
        case E_PHOTO_INFO_INPUT_DATA_FORMAT:
            return _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_INPUT_DATA_FORMAT);

        case E_PHOTO_INFO_FILE_FORMAT:
            u32Info = _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_INPUT_DATA_FORMAT);
            switch (MAJOR_FORMAT(u32Info))
            {
                case E_STILLIMAGE_INPUT_DATA_JPEG:
                    return E_PHOTO_FILE_JPEG;

                case E_STILLIMAGE_INPUT_DATA_BMP:
                    return E_PHOTO_FILE_BMP;

                case E_STILLIMAGE_INPUT_DATA_PNG:
                    return E_PHOTO_FILE_PNG;

                case E_STILLIMAGE_INPUT_DATA_TIFF:
                    return E_PHOTO_FILE_TIFF;

                case E_STILLIMAGE_INPUT_DATA_GIF:
                    return E_PHOTO_FILE_GIF;

                default:
                    break;
            }
            return E_PHOTO_FILE_UNKNOWN;

        case E_PHOTO_INFO_IMAGE_TYPE:
            u32Info = _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_INPUT_DATA_FORMAT);
            switch (MAJOR_FORMAT(u32Info))
            {
                case E_STILLIMAGE_INPUT_DATA_JPEG:
                    switch (u32Info)
                    {
                        default:
                        case E_STILLIMAGE_INPUT_DATA_JPEG_BASELINE:
                            return E_PHOTO_IMAGE_JPEG_BASELINE;

                        case E_STILLIMAGE_INPUT_DATA_JPEG_PROGRESSIVE:
                            return E_PHOTO_IMAGE_JPEG_PROGRESSIVE;
                        case E_STILLIMAGE_INPUT_DATA_MPO_BASELINE_SUBJPEG_BASELINE:
                        case E_STILLIMAGE_INPUT_DATA_MPO_PANORAMA_SUBJPEG_BASELINE:
                        case E_STILLIMAGE_INPUT_DATA_MPO_DISPARITY_SUBJPEG_BASELINE:
                        case E_STILLIMAGE_INPUT_DATA_MPO_MULTI_ANGLE_SUBJPEG_BASELINE:
                            return E_PHOTO_IMAGE_JPEG_BASELINE;

                        case E_STILLIMAGE_INPUT_DATA_MPO_BASELINE_SUBJPEG_PROGRESSIVE:
                        case E_STILLIMAGE_INPUT_DATA_MPO_PANORAMA_SUBJPEG_PROGRESSIVE:
                        case E_STILLIMAGE_INPUT_DATA_MPO_DISPARITY_SUBJPEG_PROGRESSIVE:
                        case E_STILLIMAGE_INPUT_DATA_MPO_MULTI_ANGLE_SUBJPEG_PROGRESSIVE:
                            return E_PHOTO_IMAGE_JPEG_PROGRESSIVE;
                    }
                    break;

                case E_STILLIMAGE_INPUT_DATA_BMP:
                    return E_PHOTO_IMAGE_BMP;

                case E_STILLIMAGE_INPUT_DATA_PNG:
                    switch (u32Info)
                    {
                        default:
                        case E_STILLIMAGE_INPUT_DATA_PNG_NON_INTERLACED:
                            return E_PHOTO_IMAGE_PNG_NON_INTERLACED;

                        case E_STILLIMAGE_INPUT_DATA_PNG_INTERLACED:
                            return E_PHOTO_IMAGE_PNG_INTERLACED;
                    }
                    break;

                case E_STILLIMAGE_INPUT_DATA_TIFF:
                    switch (u32Info)
                    {
                        default:
                        case E_STILLIMAGE_INPUT_DATA_TIFF_16_BITS:
                            return E_PHOTO_IMAGE_TIFF;
                    }
                    break;

                case E_STILLIMAGE_INPUT_DATA_GIF:
                    switch (u32Info)
                    {
                        default:
                        case E_STILLIMAGE_INPUT_DATA_GIF_NOT_ANIMATION:
                            return E_PHOTO_IMAGE_GIF_NON_ANIMATION;

                        case E_STILLIMAGE_INPUT_DATA_GIF_ANIMATION:
                            return E_PHOTO_IMAGE_GIF_ANIMATION;
                    }
                    break;

                default:
                    break;
            }
            return E_PHOTO_IMAGE_UNKNOWN;

        case E_PHOTO_INFO_FILE_SIZE:
            switch (_MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_DATA_ACCESS_METHOD))
            {
                case E_STILLIMAGE_VIA_MAILBOX:
                    return _u32Photo_Decode_FileSize;

                case E_STILLIMAGE_IN_MEMORY:
                    if (_gTotalSizeUnknown)
                    {
                        return _U32_MAX;
                    }

                    return _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_INPUT_DATA_BUFF_LEN);

                default:
                   return 0;
            }
            return 0;

        case E_PHOTO_INFO_IMAGE_WIDTH:
            return _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_IMAGE_WIDTH);

        case E_PHOTO_INFO_IMAGE_HEIGHT:
            return _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_IMAGE_HEIGHT);

        case E_PHOTO_INFO_PITCH:
            return _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_OUTPUT_PITCH);

        case E_PHOTO_INFO_WIDTH:
            return _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_OUTPUT_WIDTH);

        case E_PHOTO_INFO_HEIGHT:
            return _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_OUTPUT_HEIGHT);

        case E_PHOTO_INFO_SIZE:
            return _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_OUTPUT_SIZE);

        case E_PHOTO_INFO_HAS_THUMBNAIL:
            return _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_HAS_THUMBNAIL);

        case E_PHOTO_INFO_OUTPUT_FORMAT:
            switch (_MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_OUTPUT_IMAGE_FORMAT))
            {
                case E_STILLIMAGE_OUTPU_RAW_YUV422:
                    return E_PHOTO_OUTPUT_YUV422;

                case E_STILLIMAGE_OUTPU_RAW_ARGB8888:
                    return E_PHOTO_OUTPUT_ARGB8888;

                case E_STILLIMAGE_OUTPU_ARGB1555:
                    return E_PHOTO_OUTPUT_ARGB1555;

                case E_STILLIMAGE_OUTPU_JPEG:
                    return E_PHOTO_OUTPUT_JPEG;

                default:
                    return E_PHOTO_OUTPUT_FORMAT_UNKNOWN;
            }

        case E_PHOTO_INFO_PROGRESS:
            return _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_PROGRESS) / 10;

        case E_PHOTO_INFO_ERROR_INFO:
            return _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_ERROR);

        /////////////////////////////////////////////////////////////
        case E_PHOTO_INFO_EXIF_WIDTH:
            return _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_OUTPUT_JPEG_EXIF_WIDTH);

        case E_PHOTO_INFO_EXIF_HEIGHT:
            return _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_OUTPUT_JPEG_EXIF_HEIGHT);
        /////////////////////////////////////////////////////////////

        case E_PHOTO_INFO_ORIENTATION:
            switch (_MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_OIRENTATION))
            {
                case E_STILLIMAGE_ORIENT_RESERVED:
                    return E_PHOTO_ORIENT_RESERVED;

                case E_STILLIMAGE_ORIENT_ROTATE_0:
                    return E_PHOTO_ORIENT_ROTATE_0;

                case E_STILLIMAGE_ORIENT_MIRROR_LR:
                    return E_PHOTO_ORIENT_MIRROR_LR;

                case E_STILLIMAGE_ORIENT_ROTATE_180:
                    return E_PHOTO_ORIENT_ROTATE_180;

                case E_STILLIMAGE_ORIENT_MIRROR_TB:
                    return E_PHOTO_ORIENT_MIRROR_TB;

                case E_STILLIMAGE_ORIENT_ROTATE_90_MIRROR_LR:
                    return E_PHOTO_ORIENT_ROTATE_90_MIRROR_LR;

                case E_STILLIMAGE_ORIENT_E_ORIENT_ROTATE_90:
                    return E_PHOTO_ORIENT_E_ORIENT_ROTATE_90;

                case E_STILLIMAGE_ORIENT_ROTATE_90_MIRROR_TB:
                    return E_PHOTO_ORIENT_ROTATE_90_MIRROR_TB;

                case E_STILLIMAGE_ORIENT_ROTATE_270:
                    return E_PHOTO_ORIENT_ROTATE_270;

                case E_STILLIMAGE_ORIENT_NOT_FOUND:
                    return E_PHOTO_ORIENT_NOT_FOUND;

                case E_STILLIMAGE_ORIENT_UNDEFINE:
                default:
                    return E_PHOTO_ORIENT_UNDEFINE;

            }
            break;

        case E_PHOTO_INFO_HAS_DATE_TIME:
            return _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_HAS_DATE_TIME);

        case E_PHOTO_INFO_DATE_TIME_YEAR:
            return _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_DATE_TIME_YEAR);

        case E_PHOTO_INFO_DATE_TIME_MONTH:
            return _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_DATE_TIME_MONTH);

        case E_PHOTO_INFO_DATE_TIME_DAY:
            return _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_DATE_TIME_DAY);

        case E_PHOTO_INFO_DATE_TIME_HOUR:
            return _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_DATE_TIME_HOUR);

        case E_PHOTO_INFO_DATE_TIME_MINUTE:
            return _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_DATE_TIME_MINUTE);

        case E_PHOTO_INFO_DATE_TIME_SECOND:
            return _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_DATE_TIME_SECOND);

        case E_PHOTO_INFO_DECODED_FRAME_INDEX:
            return _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_DECODED_FRAME_INDEX);

        case E_PHOTO_INFO_DISPLAYED_FRAME_INDEX:
            return _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_DISPLAYED_FRAME_INDEX);

        case E_PHOTO_INFO_SLOT_NUM:
            return _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_SLOT_NUM);

        case E_PHOTO_INFO_FRAME_SIZE:
            return _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_FRAME_SIZE);

        case E_PHOTO_INFO_IS_MPO_DISPARITY_TYPE:
            if((_MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_INPUT_DATA_FORMAT) == E_STILLIMAGE_INPUT_DATA_MPO_DISPARITY_SUBJPEG_BASELINE) ||
                (_MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_INPUT_DATA_FORMAT) == E_STILLIMAGE_INPUT_DATA_MPO_DISPARITY_SUBJPEG_PROGRESSIVE))
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }
        case E_PHOTO_INFO_SCALE_DOWN_FACTOR:
            return _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_SCALE_DOWN_FACTOR);

        default:
            break;
    }

    return 0;
}

BOOLEAN MApp_Photo_GetExifInfo(EN_PHOTO_EXIF_INFO enInfo, void *pBufAddr, U16 u16BufSize)
{
    if(pBufAddr == NULL || u16BufSize == 0)
    {
        return FALSE;
    }

    BOOLEAN bRet=TRUE;
    U32 u32InfoAddr;
    U16 u16InfoSize;
    U32 *pu32Addr;

    pu32Addr = ((U32 *)(_u32Photo_ShareMemAddr)) + E_STILLIMAGE_SHAREMEM_OUTPUT_JPEG_EXIF_DATA;

    switch (enInfo)
    {
        case E_PHOTO_EXIF_INFO_CAMERA_MAKER:
            //Get "pointer" of camera maker
            u32InfoAddr = (U32)(&(((ST_STILLIMAGE_JPEG_EXIF *)(_PA2VA((U32)pu32Addr)))->au8CameraMaker));
            u16InfoSize = EXIF_CAMERA_MAKER_SIZE;
            break;

        case E_PHOTO_EXIF_INFO_CAMERA_MODEL:
            //Get "pointer" of camera model
            u32InfoAddr = (U32)(&(((ST_STILLIMAGE_JPEG_EXIF *)(_PA2VA((U32)pu32Addr)))->au8CameraModel));
            u16InfoSize = EXIF_CAMERA_MODEL_SIZE;
            break;

        case E_PHOTO_EXIF_INFO_FLASH_MODE:
            u32InfoAddr = (U32)(&(((ST_STILLIMAGE_JPEG_EXIF *)(_PA2VA((U32)pu32Addr)))->u32FlashMode));
            u16InfoSize = sizeof(U32);
            break;

        case E_PHOTO_EXIF_INFO_ISO_SPEED:
            u32InfoAddr = (U32)(&(((ST_STILLIMAGE_JPEG_EXIF *)(_PA2VA((U32)pu32Addr)))->u32ISOSpeed));
            u16InfoSize = sizeof(U32);
            break;

        case E_PHOTO_EXIF_INFO_EXPOSURE_BIAS:
            //Get "pointer" of RATIONAL structure
            u32InfoAddr = (U32)(&(((ST_STILLIMAGE_JPEG_EXIF *)(_PA2VA((U32)pu32Addr)))->stExposureBias));
            u16InfoSize = sizeof(ST_STILLIMAGE_RATIONAL);
            break;

        case E_PHOTO_EXIF_INFO_EXPOSURE_TIME:
            //Get "pointer" of RATIONAL structure
            u32InfoAddr = (U32)(&(((ST_STILLIMAGE_JPEG_EXIF *)(_PA2VA((U32)pu32Addr)))->stExposureTime));
            u16InfoSize = sizeof(ST_STILLIMAGE_RATIONAL);
            break;

        case E_PHOTO_EXIF_INFO_F_STOP:
            //Get "pointer" of RATIONAL structure
            u32InfoAddr = (U32)(&(((ST_STILLIMAGE_JPEG_EXIF *)(_PA2VA((U32)pu32Addr)))->stF_Stop));
            u16InfoSize = sizeof(ST_STILLIMAGE_RATIONAL);
            break;

        case E_PHOTO_EXIF_INFO_FOCAL_LENGTH:
            //Get "pointer" of RATIONAL structure
            u32InfoAddr = (U32)(&(((ST_STILLIMAGE_JPEG_EXIF *)(_PA2VA((U32)pu32Addr)))->stFocalLength));
            u16InfoSize = sizeof(ST_STILLIMAGE_RATIONAL);
            break;

        case E_PHOTO_EXIF_INFO_SHUTTER_SPEED:
            //Get "pointer" of RATIONAL structure
            u32InfoAddr = (U32)(&(((ST_STILLIMAGE_JPEG_EXIF *)(_PA2VA((U32)pu32Addr)))->stShutterSpeedValue));
            u16InfoSize = sizeof(ST_STILLIMAGE_RATIONAL);
            break;

        case E_PHOTO_EXIF_INFO_APERTURE:
            //Get "pointer" of RATIONAL structure
            u32InfoAddr = (U32)(&(((ST_STILLIMAGE_JPEG_EXIF *)(_PA2VA((U32)pu32Addr)))->stApertureValue));
            u16InfoSize = sizeof(ST_STILLIMAGE_RATIONAL);
            break;

        default:
            bRet = FALSE;
            break;
    }

    if(bRet == TRUE)
    {
        if(u16BufSize >= u16InfoSize && u32InfoAddr != 0)
        {
            memcpy(pBufAddr, (void*)u32InfoAddr, u16InfoSize);
        }
        else
        {
            PHOTO_MSG_ERR(printf("%s LINE %d -- buffer is too small.\n", __FUNCTION__, __LINE__));
            bRet = FALSE;
        }
    }

    return bRet;
}


EN_PHOTO_ERRCODE MApp_Photo_GetErrCode(void)
{
    return _enPhoto_ErrCode;
}
#endif

//-------------------------------------------------------------------------------------------------
// Local funcion -- misc functions
//-------------------------------------------------------------------------------------------------

static void _MApp_Photo_Reset(BOOLEAN bForceResetMem)
{
    if (bForceResetMem)
    {
        _u32DataBuffAddr =   PHOTO_DATA_BUFFER_ADDR;
        _u32DataBuffSize =   PHOTO_DATA_BUFFER_SIZE;

        _u32OutputBuffAddr = PHOTO_OUTPUT_BUFFER_ADDR;
        _u32OutputBuffSize = PHOTO_OUTPUT_BUFFER_SIZE;

        _u32PoolMemAddr =    PHOTO_MEMPOOL_BUFFER_ADDR;
        _u32PoolMemSize =    PHOTO_MEMPOOL_BUFFER_SIZE;

        _u32ProgressiveJpegMemAddr = PHOTO_JPEG_PROGRESSIVE_BUFFER_ADDR;
        _u32ProgressiveJpegMemSize = PHOTO_JPEG_PROGRESSIVE_BUFFER_SIZE;

        _u32GifFrameInfoArrayAddr = PHOTO_GIF_FRAME_INFO_ARRAY_BUFFER_ADDR;
        _u32GifFrameInfoArraySize = PHOTO_GIF_FRAME_INFO_ARRAY_BUFFER_SIZE;

        //reset decode width/height
        m_u32MinDecodeWidth = PHOTO_DECODE_MIN_WIDTH;
        m_u32MinDecodeHeight = PHOTO_DECODE_MIN_HEIGHT;

        m_u32MaxDecodeJpegBaselineWidth = PHOTO_DECODE_JPEG_BASELINE_MAX_WIDTH;
        m_u32MaxDecodeJpegBaselineHeight = PHOTO_DECODE_JPEG_BASELINE_MAX_HEIGHT;

        m_u32MaxDecodeJpegProgressiveWidth = PHOTO_DECODE_JPEG_PROGRESSIVE_MAX_WIDTH;
        m_u32MaxDecodeJpegProgressiveHeight = PHOTO_DECODE_JPEG_PROGRESSIVE_MAX_HEIGHT;

        m_u32MaxDecodeBmpWidth = PHOTO_DECODE_BMP_MAX_WIDTH;
        m_u32MaxDecodeBmpHeight = PHOTO_DECODE_BMP_MAX_HEIGHT;

        m_u32MaxDecodePngWidth = PHOTO_DECODE_PNG_MAX_WIDTH;
        m_u32MaxDecodePngHeight = PHOTO_DECODE_PNG_MAX_HEIGHT;

        m_u32MaxDecodeTiffWidth = PHOTO_DECODE_TIFF_MAX_WIDTH;
        m_u32MaxDecodeTiffHeight = PHOTO_DECODE_TIFF_MAX_HEIGHT;

        m_u32MaxDecodeGifWidth = PHOTO_DECODE_GIF_MAX_WIDTH;
        m_u32MaxDecodeGifHeight = PHOTO_DECODE_GIF_MAX_HEIGHT;

        m_u32MaxDecodeMpoBaselineWidth = PHOTO_DECODE_MPO_BASELINE_MAX_WIDTH;
        m_u32MaxDecodeMpoBaselineHeight = PHOTO_DECODE_MPO_BASELINE_MAX_HEIGHT;

        m_u32MaxDecodeMpoProgressiveWidth = PHOTO_DECODE_MPO_PROGRESSIVE_MAX_WIDTH;
        m_u32MaxDecodeMpoProgressiveHeight = PHOTO_DECODE_MPO_PROGRESSIVE_MAX_HEIGHT;
    }
    else
    {
        if (_u32DataBuffAddr == 0)
        {
            _u32DataBuffAddr =   PHOTO_DATA_BUFFER_ADDR;
            _u32DataBuffSize =   PHOTO_DATA_BUFFER_SIZE;
        }

        if (_u32OutputBuffAddr == 0)
        {
            _u32OutputBuffAddr = PHOTO_OUTPUT_BUFFER_ADDR;
            _u32OutputBuffSize = PHOTO_OUTPUT_BUFFER_SIZE;
        }

        if (_u32PoolMemAddr == 0)
        {
            _u32PoolMemAddr =    PHOTO_MEMPOOL_BUFFER_ADDR;
            _u32PoolMemSize =    PHOTO_MEMPOOL_BUFFER_SIZE;

            // _u32PoolMemAddr & _u32ProgressiveJpegMemAddr are mutual exclusive now
            _u32ProgressiveJpegMemAddr = PHOTO_JPEG_PROGRESSIVE_BUFFER_ADDR;
            _u32ProgressiveJpegMemSize = PHOTO_JPEG_PROGRESSIVE_BUFFER_SIZE;
        }

        if(_u32GifFrameInfoArrayAddr == 0)
        {
             _u32GifFrameInfoArrayAddr = PHOTO_GIF_FRAME_INFO_ARRAY_BUFFER_ADDR;
            _u32GifFrameInfoArraySize = PHOTO_GIF_FRAME_INFO_ARRAY_BUFFER_SIZE;
        }

        //if decode width/height is invalid, set to default value.
        if(m_u32MinDecodeWidth == 0 || m_u32MinDecodeHeight == 0)
        {
            m_u32MinDecodeWidth = PHOTO_DECODE_MIN_WIDTH;
            m_u32MinDecodeHeight = PHOTO_DECODE_MIN_HEIGHT;
        }

        if(m_u32MaxDecodeJpegBaselineWidth == 0 || m_u32MaxDecodeJpegBaselineHeight == 0)
        {
            m_u32MaxDecodeJpegBaselineWidth = PHOTO_DECODE_JPEG_BASELINE_MAX_WIDTH;
            m_u32MaxDecodeJpegBaselineHeight = PHOTO_DECODE_JPEG_BASELINE_MAX_HEIGHT;
        }

        if(m_u32MaxDecodeJpegProgressiveWidth == 0 || m_u32MaxDecodeJpegProgressiveHeight == 0)
        {
            m_u32MaxDecodeJpegProgressiveWidth = PHOTO_DECODE_JPEG_PROGRESSIVE_MAX_WIDTH;
            m_u32MaxDecodeJpegProgressiveHeight = PHOTO_DECODE_JPEG_PROGRESSIVE_MAX_HEIGHT;
        }

        if(m_u32MaxDecodeBmpWidth == 0 || m_u32MaxDecodeBmpHeight == 0)
        {
            m_u32MaxDecodeBmpWidth = PHOTO_DECODE_BMP_MAX_WIDTH;
            m_u32MaxDecodeBmpHeight = PHOTO_DECODE_BMP_MAX_HEIGHT;
        }

        if(m_u32MaxDecodePngWidth == 0 || m_u32MaxDecodePngHeight == 0)
        {
            m_u32MaxDecodePngWidth = PHOTO_DECODE_PNG_MAX_WIDTH;
            m_u32MaxDecodePngHeight = PHOTO_DECODE_PNG_MAX_HEIGHT;
        }

        if(m_u32MaxDecodeTiffWidth == 0 || m_u32MaxDecodeTiffHeight == 0)
        {
            m_u32MaxDecodeTiffWidth = PHOTO_DECODE_TIFF_MAX_WIDTH;
            m_u32MaxDecodeTiffHeight = PHOTO_DECODE_TIFF_MAX_HEIGHT;
        }

        if(m_u32MaxDecodeGifWidth == 0 || m_u32MaxDecodeGifHeight == 0)
        {
            m_u32MaxDecodeGifWidth = PHOTO_DECODE_GIF_MAX_WIDTH;
            m_u32MaxDecodeGifHeight = PHOTO_DECODE_GIF_MAX_HEIGHT;
        }

        if(m_u32MaxDecodeMpoBaselineWidth == 0 || m_u32MaxDecodeMpoBaselineHeight == 0)
        {
            m_u32MaxDecodeMpoBaselineWidth = PHOTO_DECODE_MPO_BASELINE_MAX_WIDTH;
            m_u32MaxDecodeMpoBaselineHeight = PHOTO_DECODE_MPO_BASELINE_MAX_HEIGHT;
        }

        if(m_u32MaxDecodeMpoProgressiveWidth == 0 || m_u32MaxDecodeMpoProgressiveHeight == 0)
        {
            m_u32MaxDecodeMpoProgressiveWidth = PHOTO_DECODE_MPO_PROGRESSIVE_MAX_WIDTH;
            m_u32MaxDecodeMpoProgressiveHeight = PHOTO_DECODE_MPO_PROGRESSIVE_MAX_HEIGHT;
        }
    }

#if (!ENABLE_HK_PHOTO)
    // invalidate share memory info
    _MApp_Photo_ShareMem_SetInfo(E_STILLIMAGE_SHAREMEM_NUM, 0);
#endif

    _MApp_Photo_FileClose();

    _u32ResidualReadSize = 0;
    _u32ReadBuffAddr = NULL;
    _u32PreGifDecodedFrameIndex = _U32_MAX;

    // reset flag
    enPhoto_AckFlags = E_PHOTO_ACKFLG_NULL;
}

static void _MApp_Photo_SetErrCode(BOOLEAN bFromShareMem, EN_PHOTO_ERRCODE enErrCode)
{
    EN_STILLIMAGE_ERR_CODE enStillImage_ErrCode;

    if (bFromShareMem == FALSE)
    {
        _enPhoto_ErrCode = enErrCode;
    }
    else
    {
        enStillImage_ErrCode = (EN_STILLIMAGE_ERR_CODE)MApp_Photo_GetInfo(E_PHOTO_INFO_ERROR_INFO);
        if (enStillImage_ErrCode & STILLIMAGE_ERR_CODE_ST)
        {
            PHOTO_MSG_INFO_MUST(printf("[PHOTO] error code (0x%x)\n", enStillImage_ErrCode));
            switch (enStillImage_ErrCode)
            {
                case E_STILLIMAGE_DATA_FORMAT_NOT_SUPPORTED:
                    _enPhoto_ErrCode = E_PHOTO_ERR_NOT_SUPPORT_FILE_FMT;
                    break;

                case E_STILLIMAGE_IMAGE_FORMAT_NOT_SUPPORTED:
                case E_STILLIMAGE_IMAGE_RESOLUTION_TOO_BIG:
                case E_STILLIMAGE_IMAGE_RESOLUTION_TOO_SAMLL:
                    _enPhoto_ErrCode = E_PHOTO_ERR_NOT_SUPPORT_IMAGE_FMT;
                    break;

                case E_STILLIMAGE_INPUT_BUFF_TOO_SMALL:
                case E_STILLIMAGE_OUTPUT_BUFF_TOO_SMALL:
                case E_STILLIMAGE_INTERNAL_BUFF_TOO_SMALL:
                    _enPhoto_ErrCode = E_PHOTO_ERR_MEMORY_LAYOUT_VIOLATTION;
                    break;

                case E_STILLIMAGE_OPEN_ERR:
                case E_STILLIMAGE_READ_ERR:
                    _enPhoto_ErrCode = E_PHOTO_ERR_DATA_OPERATION_FAILURE;
                    break;

                case E_STILLIMAGE_JPEG_NO_THUMBNAIL:
                case E_STILLIMAGE_BMP_NO_THUMBNAIL:
                case E_STILLIMAGE_PNG_NO_THUMBNAIL:
                case E_STILLIMAGE_TIFF_NO_THUMBNAIL:
                case E_STILLIMAGE_GIF_NO_THUMBNAIL:
                    _enPhoto_ErrCode = E_PHOTO_ERR_NO_THUMBNAIL;
                    break;

                case E_STILLIMAGE_JPE_FREE_MEM_TOO_LOW:
                case E_STILLIMAGE_JPE_INIT_FAILED:
                case E_STILLIMAGE_JPE_WIDTH_NOT_ALIGNED:
                case E_STILLIMAGE_JPE_HEIGHT_NOT_ALIGNED:
                case E_STILLIMAGE_JPE_WRONG_STATE:
                case E_STILLIMAGE_JPE_OUTPUT_BUFFER_TOO_SMALL:
                    _enPhoto_ErrCode = E_PHOTO_ERR_ENCODE_FAILURE;
                    break;

                default:
                    _enPhoto_ErrCode = E_PHOTO_ERR_DECODE_FAILURE;
                    break;
            }
        }
    }
}

static BOOLEAN _MApp_Photo_Decode_MemoryValidation(EN_PHOTO_CMD enCmd)
{
    U32 u32TotalBytes = 0;

#if (!ENABLE_HK_PHOTO)
    // check is share memory is out of number
    STATIC_ASSERT((E_STILLIMAGE_SHAREMEM_NUM * 4) > PHOTO_SHARE_MEM_BUFFER_SIZE);
#endif

    // check co-buffer using POOL_BUFFER
    // 0
    STATIC_ASSERT((PHOTO_SHRINK_BUFFER_0_ADDR + PHOTO_SHRINK_BUFFER_0_SIZE)
            > (PHOTO_POOL_BUFFER_ADDR +  PHOTO_POOL_BUFFER_SIZE));
    // 1
    STATIC_ASSERT((PHOTO_JPEG_PROGRESSIVE_BUFFER_ADDR + PHOTO_JPEG_PROGRESSIVE_BUFFER_SIZE)
            > (PHOTO_POOL_BUFFER_ADDR +  PHOTO_POOL_BUFFER_SIZE));

    // check co-buffer using DISPLAY_BUFFER
    // 1
    STATIC_ASSERT((PHOTO_THUMBNAIL_SHRINK_BUFFER_1_ADDR + PHOTO_THUMBNAIL_SHRINK_BUFFER_1_SIZE)
            > (PHOTO_DISPLAY_BUFFER_ADDR +  PHOTO_DISPLAY_BUFFER_SIZE));

    // check ouptut buffer
    if (enCmd == E_PHOTO_DECODE)
    {
        //The JPD write buffer need to do the alignment corresponding to the JPEG MCU size.
        //Thus the JPEG format would be used to determine the width / height alignment.
        //Currently, the JPD supports YUV400 / YUV420 / YUV411 / YUV422 / YUV444 formats.
        //Thus the corresponding (width alignment, height alignment) = (8, 8) / (16, 16) / (32, 8) / (16, 8) or (8, 16) / (8, 8).
        //And the lowest common multiple would be (32, 16), which means in order to cover all the cases, the width need to be the multiple of 32, and the height need to be the multiple of 16.
        //Thus in order to support the picture size 1920x1080, the size of write buffer need to be 1920(32 alignment)x1088(16 alignment)x2 to support all the format without decoding error.
        // JPEG, YUV422
        u32TotalBytes = (U32)MAX(u32TotalBytes, PHOTO_ALIGNMENT_32(m_u32MaxDecodeJpegBaselineWidth) * PHOTO_ALIGNMENT(m_u32MaxDecodeJpegBaselineHeight) * 2);
        u32TotalBytes = (U32)MAX(u32TotalBytes, PHOTO_ALIGNMENT_32(m_u32MaxDecodeJpegProgressiveWidth) * PHOTO_ALIGNMENT(m_u32MaxDecodeJpegProgressiveHeight) * 2);

        // BMP, ARGB8888
        u32TotalBytes = (U32)MAX(u32TotalBytes, m_u32MaxDecodeBmpWidth * m_u32MaxDecodeBmpHeight * 4);

        if (u32TotalBytes > (U32)PHOTO_OUTPUT_BUFFER_SIZE)
        {
            PHOTO_MSG_ERR(printf("[PHOTO] In-sufficient OUTPUT_BUFFER, total: 0x%lx, needed: 0x%lx\n", (U32)PHOTO_OUTPUT_BUFFER_SIZE, (U32)u32TotalBytes));
            return FALSE;
        }
    }

    return TRUE;
}

void _MApp_Photo_Decode_ShowImageInfo(void)
{
    U32 u32Width, u32Height, u32Size;
    U32 u32OutputWidth, u32OutputPitch, u32OutputHeight;
    BOOLEAN bHasThumbnail;
    EN_PHOTO_FILE enFile;
    EN_PHOTO_IMAGE enImage;
    U8 au8TempBuf[PHOTO_EXIF_INFO_BUFFER_SIZE];
    U32 u32TempExifValue;
    RATIONAL stTempExifRational;

    if (_enPhotoCmd == E_PHOTO_DECODE)
    {
        enFile = (EN_PHOTO_FILE)MApp_Photo_GetInfo(E_PHOTO_INFO_FILE_FORMAT);
        enImage = (EN_PHOTO_IMAGE)MApp_Photo_GetInfo(E_PHOTO_INFO_IMAGE_TYPE);

        u32Width = MApp_Photo_GetInfo(E_PHOTO_INFO_IMAGE_WIDTH);
        u32Height = MApp_Photo_GetInfo(E_PHOTO_INFO_IMAGE_HEIGHT);
        u32Size = MApp_Photo_GetInfo(E_PHOTO_INFO_FILE_SIZE);
        bHasThumbnail = MApp_Photo_GetInfo(E_PHOTO_INFO_HAS_THUMBNAIL);

        u32OutputWidth = MApp_Photo_GetInfo(E_PHOTO_INFO_WIDTH);
        u32OutputPitch = MApp_Photo_GetInfo(E_PHOTO_INFO_PITCH);
        u32OutputHeight = MApp_Photo_GetInfo(E_PHOTO_INFO_HEIGHT);

        PHOTO_MSG_INFO_MUST(printf("[PHOTO] "));

        // file type
        switch (enFile)
        {
            case E_PHOTO_FILE_JPEG:
                PHOTO_MSG_INFO_MUST(printf("JPEG, "));
                // image type
                switch (enImage)
                {
                    default:
                    case E_PHOTO_IMAGE_JPEG_BASELINE:
                        PHOTO_MSG_INFO_MUST(printf("Baseline, "));
                        break;

                    case E_PHOTO_IMAGE_JPEG_PROGRESSIVE:
                        PHOTO_MSG_INFO_MUST(printf("Progressive, "));
                        break;
                }
                break;

            case E_PHOTO_FILE_BMP:
                PHOTO_MSG_INFO_MUST(printf("BMP, %lx, ", MApp_Photo_GetInfo(E_PHOTO_INFO_INPUT_DATA_FORMAT)));
                break;

            case E_PHOTO_FILE_PNG:
                PHOTO_MSG_INFO_MUST(printf("PNG, "));
                // image type
                switch (enImage)
                {
                    default:
                    case E_PHOTO_IMAGE_PNG_NON_INTERLACED:
                        PHOTO_MSG_INFO_MUST(printf("non-interlaced, "));
                        break;

                    case E_PHOTO_IMAGE_PNG_INTERLACED:
                        PHOTO_MSG_INFO_MUST(printf("interlaced, "));
                        break;
                }
                break;

            case E_PHOTO_FILE_TIFF:
                PHOTO_MSG_INFO_MUST(printf("TIFF, %lx, ", MApp_Photo_GetInfo(E_PHOTO_INFO_INPUT_DATA_FORMAT)));
                break;

            case E_PHOTO_FILE_GIF:
                PHOTO_MSG_INFO_MUST(printf("GIF, %lx, ", MApp_Photo_GetInfo(E_PHOTO_INFO_INPUT_DATA_FORMAT)));
                break;

            default:
                PHOTO_MSG_INFO_MUST(printf("?? Unknown "));
                break;
        }

        // resolution
        PHOTO_MSG_INFO_MUST(printf("(%lux%lu, %lu(%lu)x%lu), ", u32Width, u32Height, u32OutputWidth, u32OutputPitch, u32OutputHeight));

        // size & thumbnail
        PHOTO_MSG_INFO_MUST(printf("size: %lu, thumbnail: %u", u32Size, (U16)bHasThumbnail));

        // new line
        PHOTO_MSG_INFO_MUST(printf("\n[PHOTO] "));

        PHOTO_MSG_INFO_MUST(printf("Exif width: %lu, Exif height: %lu ", MApp_Photo_GetInfo(E_PHOTO_INFO_EXIF_WIDTH),
                                                                         MApp_Photo_GetInfo(E_PHOTO_INFO_EXIF_HEIGHT)));
        // orientation & date (it there is one)
        PHOTO_MSG_INFO_MUST(printf("Orient: %lu, ", MApp_Photo_GetInfo(E_PHOTO_INFO_ORIENTATION)));
        PHOTO_MSG_INFO_MUST(printf("Date Time: "));
        if ((BOOLEAN)MApp_Photo_GetInfo(E_PHOTO_INFO_HAS_DATE_TIME) == FALSE)
        {
            PHOTO_MSG_INFO_MUST(printf("NO\n"));
        }
        else
        {
            PHOTO_MSG_INFO_MUST(printf("%04lu:%02lu:%02lu %02lu:%02lu:%02lu\n",
                    MApp_Photo_GetInfo(E_PHOTO_INFO_DATE_TIME_YEAR),
                    MApp_Photo_GetInfo(E_PHOTO_INFO_DATE_TIME_MONTH),
                    MApp_Photo_GetInfo(E_PHOTO_INFO_DATE_TIME_DAY),
                    MApp_Photo_GetInfo(E_PHOTO_INFO_DATE_TIME_HOUR),
                    MApp_Photo_GetInfo(E_PHOTO_INFO_DATE_TIME_MINUTE),
                    MApp_Photo_GetInfo(E_PHOTO_INFO_DATE_TIME_SECOND)));
        }

        if(TRUE == MApp_Photo_GetExifInfo(E_PHOTO_EXIF_INFO_CAMERA_MAKER, au8TempBuf, PHOTO_EXIF_INFO_BUFFER_SIZE))
        {
            PHOTO_MSG_INFO_MUST(printf("Camera maker: %s, ", au8TempBuf));
        }

        if(TRUE == MApp_Photo_GetExifInfo(E_PHOTO_EXIF_INFO_CAMERA_MODEL, au8TempBuf, PHOTO_EXIF_INFO_BUFFER_SIZE))
        {
            PHOTO_MSG_INFO_MUST(printf("Camera model: %s\n", au8TempBuf));
        }

        if(TRUE == MApp_Photo_GetExifInfo(E_PHOTO_EXIF_INFO_FLASH_MODE, &u32TempExifValue, 4))
        {
            PHOTO_MSG_INFO_MUST(printf("Flash mode: 0x%lx, ", u32TempExifValue));
        }

        if(TRUE == MApp_Photo_GetExifInfo(E_PHOTO_EXIF_INFO_ISO_SPEED, &u32TempExifValue, 4))
        {
            PHOTO_MSG_INFO_MUST(printf("ISO Speed: %lu, ", u32TempExifValue));
        }

        if(TRUE == MApp_Photo_GetExifInfo(E_PHOTO_EXIF_INFO_EXPOSURE_BIAS, &stTempExifRational, sizeof(RATIONAL)))
        {
            PHOTO_MSG_INFO_MUST(printf("Exposure bias: %lu/%lu, ", stTempExifRational.u32Numerator, stTempExifRational.u32Denominator));
        }

        if(TRUE == MApp_Photo_GetExifInfo(E_PHOTO_EXIF_INFO_EXPOSURE_TIME, &stTempExifRational, sizeof(RATIONAL)))
        {
            PHOTO_MSG_INFO_MUST(printf("Exposure time: %lu/%lu, ", stTempExifRational.u32Numerator, stTempExifRational.u32Denominator));
        }

        if(TRUE == MApp_Photo_GetExifInfo(E_PHOTO_EXIF_INFO_F_STOP, &stTempExifRational, sizeof(RATIONAL)))
        {
            PHOTO_MSG_INFO_MUST(printf("F-Stop: %lu/%lu\n", stTempExifRational.u32Numerator, stTempExifRational.u32Denominator));
        }

        if(TRUE == MApp_Photo_GetExifInfo(E_PHOTO_EXIF_INFO_FOCAL_LENGTH, &stTempExifRational, sizeof(RATIONAL)))
        {
            PHOTO_MSG_INFO_MUST(printf("FocalLength: %lu/%lu\n", stTempExifRational.u32Numerator, stTempExifRational.u32Denominator));
        }

        if(TRUE == MApp_Photo_GetExifInfo(E_PHOTO_EXIF_INFO_SHUTTER_SPEED, &stTempExifRational, sizeof(RATIONAL)))
        {
            PHOTO_MSG_INFO_MUST(printf("ShutterSpeed: %lu/%lu\n", stTempExifRational.u32Numerator, stTempExifRational.u32Denominator));
        }

        if(TRUE == MApp_Photo_GetExifInfo(E_PHOTO_EXIF_INFO_APERTURE, &stTempExifRational, sizeof(RATIONAL)))
        {
            PHOTO_MSG_INFO_MUST(printf("ApertureValue: %lu/%lu\n", stTempExifRational.u32Numerator, stTempExifRational.u32Denominator));
        }
    }
    else if (_enPhotoCmd == E_PHOTO_ENCODE)
    {
        u32Size = MApp_Photo_GetInfo(E_PHOTO_INFO_SIZE);

        u32OutputWidth = MApp_Photo_GetInfo(E_PHOTO_INFO_WIDTH);
        u32OutputHeight = MApp_Photo_GetInfo(E_PHOTO_INFO_HEIGHT);

        PHOTO_MSG_INFO_MUST(printf("[PHOTO] JPEG, (%lux%lu), size: %lu", u32OutputWidth, u32OutputHeight, u32Size));
    }

    // new line
    PHOTO_MSG_INFO_MUST(printf("\n"));
}



//-------------------------------------------------------------------------------------------------
// Local funcion -- timer functions
//-------------------------------------------------------------------------------------------------
static void _MApp_Photo_Timer_Init(EN_PHOTO_TIMER enTimer, U32 u32TimeOut)
{
    _stPhoto_Timer[enTimer].u32InitTime = msAPI_Timer_GetTime0();
    _stPhoto_Timer[enTimer].u32TimeOut  = u32TimeOut;
    _stPhoto_Timer[enTimer].bEnable     = TRUE;
}

static BOOLEAN _MApp_Photo_Timer_IsTimeOut(EN_PHOTO_TIMER enTimer)
{
    BOOLEAN bTimeOut = (msAPI_Timer_DiffTimeFromNow(_stPhoto_Timer[enTimer].u32InitTime) > _stPhoto_Timer[enTimer].u32TimeOut);

    bTimeOut = bTimeOut && _stPhoto_Timer[enTimer].bEnable;
    if ((bTimeOut)
            && (enTimer != E_PHOTO_TIMER_WDT)
            && (enTimer != E_PHOTO_TIMER_PROGRESS))
    {
        PHOTO_MSG_INFO_MUST(printf("[PHOTO] Timer (%u) times out (%lu ms)\n", (U16)enTimer, _stPhoto_Timer[enTimer].u32TimeOut));
    }

    return bTimeOut;
}

static void _MApp_Photo_Timer_Disable(EN_PHOTO_TIMER enTimer)
{
    if (enTimer == E_PHOTO_TIMER_NUM)
    {
        EN_PHOTO_TIMER eTimerIdx;

        for (eTimerIdx = (EN_PHOTO_TIMER)0; eTimerIdx < enTimer; eTimerIdx++)
        {
            _stPhoto_Timer[eTimerIdx].bEnable = FALSE;
        }
    }
    else
    {
        _stPhoto_Timer[enTimer].bEnable = FALSE;
    }
}
#if (!ENABLE_HK_PHOTO)
//-------------------------------------------------------------------------------------------------
// Local funcion -- share memory accessing functions
//-------------------------------------------------------------------------------------------------
static void _MApp_Photo_ShareMem_SetInfo(EN_STILLIMAGE_SHAREMEMORY enInfo, U32 u32Value)
{
    U32 *pu32Addr;

    pu32Addr = (U32 *)_u32Photo_ShareMemAddr + enInfo;
    *(U32 *)_PA2VA((U32)pu32Addr) = u32Value;

//    MsOS_Sync();
    MsOS_FlushMemory();
}

static U32 _MApp_Photo_ShareMem_GetInfo(EN_STILLIMAGE_SHAREMEMORY enInfo)
{
    U32 *pu32Addr, u32Value;

    pu32Addr = (U32 *)_u32Photo_ShareMemAddr + enInfo;
    u32Value = *(U32 *)_PA2VA((U32)pu32Addr);
    return u32Value;
}

static BOOLEAN _MApp_Photo_CheckCPAlive(void)
{
    static U32 u32LoopCnt;
    static U8 u8CheckCnt = 0;
    BOOLEAN bAlive = TRUE;
    U8 u8CheckLiveCountMax;

    if (_MApp_Photo_Timer_IsTimeOut(E_PHOTO_TIMER_WDT))
    {
        if(MApp_Photo_GetInfo(E_PHOTO_INFO_IMAGE_TYPE) == E_PHOTO_IMAGE_JPEG_PROGRESSIVE)
        {
            u8CheckLiveCountMax = CP_ALIVE_CHECKING_CNT_FOR_PROGRESSIVE_JPEG;
        }
        else
        {
            u8CheckLiveCountMax = CP_ALIVE_CHECKING_CNT;
        }

        if (u32LoopCnt == _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_WDT_LOOP))
        {
            if (u8CheckCnt < u8CheckLiveCountMax)
            {
                u8CheckCnt++;
            }

            if (u8CheckCnt == u8CheckLiveCountMax)
            {
                bAlive = FALSE;
                PHOTO_MSG_ERR(printf("[PHOTO] CP isn't alive for at least %ldms.\n", u8CheckCnt * _u32Photo_WDT_Timeout));
            }
        }
        else
        {
            u8CheckCnt = 0;
            u32LoopCnt = _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_WDT_LOOP);
        }

        // reset timer
        _MApp_Photo_Timer_Init(E_PHOTO_TIMER_WDT, _u32Photo_WDT_Timeout);
    }

    return bAlive;
}

static void _MApp_Photo_FileReadHandler(U32 u32Addr, U32 u32Size)
{
    U32 u32RemnantSize;

    if (u32Size == 0)
    {
        return;
    }

    u32RemnantSize = _MApp_Photo_FileRead(u32Addr, u32Size);
    PHOTO_MSG_DBG(printf("[PHOTO] Continue block read, uread size: %lx\n", u32RemnantSize));

    // send ack when 1 of 3 conditions is satisfied
    // 1. all data is ready
    // 2. file position greater than file size as an error handling
    // 3. if file length is unknown
    if ((u32RemnantSize == 0)
            || (_MApp_Photo_FileTell() >= _u32Photo_Decode_FileSize)
            || (_u32Photo_Decode_FileSize == 0xFFFFFFFF))
    {
        // send ack
        _MApp_Photo_SendAck_FileRead(
                _eMbxCmdClass,
                _eDataIo,
                u32RemnantSize);
        _u32ResidualReadSize = 0;
        PHOTO_MSG_DBG(printf("[PHOTO] Finish block read\n"));
    }
    else   //need continue read in next loop
    {
        _u32ReadBuffAddr = u32Addr + u32Size - u32RemnantSize;
        _u32ResidualReadSize = u32RemnantSize;
    }
}

static void _MApp_Photo_Stop(void)
{
    // set flag
    SET_PHOTO_FLAG(EN_PHOTO_ACK_FLAGS, enPhoto_AckFlags, E_PHOTO_ACKFLG_WAIT_STOP);

    // send cmd to abort pending data operation
    if (_u32ResidualReadSize != 0)
    {
        _MApp_Photo_SendCmd_AbortDataOperation();
        _u32ResidualReadSize = 0;
    }

    _MApp_Photo_SendCmd_Stop();

    // start timer
    _MApp_Photo_Timer_Init(E_PHOTO_TIMER_STOP, _u32Photo_Stop_Timeout);

    // check response
    do
    {
        // send cmd till we get response
        //_MApp_Photo_SendCmd_Stop();
        MApp_Music_InputBackGroundMusicData();  //for bgm, incase while loop takes too long

        // reset watch dog timer
        msAPI_Timer_ResetWDT();

        // wait
        msAPI_Timer_Delayms(30);

        // handle CP response by check mail box
        _MApp_Photo_MailBox_Handler();

        // check response
        if (!(enPhoto_AckFlags & E_PHOTO_ACKFLG_WAIT_STOP))
        {
            break;
        }

        // check if timer times out
        if (_MApp_Photo_Timer_IsTimeOut(E_PHOTO_TIMER_STOP) == TRUE)
        {
            break;
        }
    } while (1);

    // switch UART back to HK
    _MApp_Photo_UartSwitch(E_UART_SWITCH_NUM);

    // check if time out
    if (enPhoto_AckFlags & E_PHOTO_ACKFLG_WAIT_STOP)
    {
        // TBD: stop cmd times out, what should be done?
        printf("[PHOTO] !!!!!!!!!!!!!!!! Warning !!!!!!!!!!!!!!\n");
        printf("[PHOTO] Stop cmd times out, CP dead?? ReInit CP\n");
        printf("[PHOTO] !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    #if( VD_PLAYER_IS_IN_CROP_CPU )
        MApp_VDPlayer_LoadBinToCrop();
        //Note:
        //In co-processor side , it will do MApi_DMX_Init()/MApi_DMX_Exit() in each movie.
        //XDemux will do MApi_DMX_Init() in xdemux init state , and do MApi_DMX_Exit() in xdemux stop state.
        //In MApi_DMX_Init() , it will re-load TSP Firmware. In MApi_DMX_Exit() it will disable TSP.
        //If Co-processor abnormal , we have to reload co-processor Firmware
        //When reload co-processor Fireware during playing movie, co-processor will not do MApi_DMX_Exit()
        //If co-processor not do MApi_DMX_Exit() then UI enter DTV mode , TSP will NOT re-load FW.
        //This means TSP FW is still same which loaded by XDemux.
        //This is a big problem , if DTV vs XDemux TSP Firmware is different.
        //That is the reason , why we have to do MApi_DMX_ForceExit().
        MApi_DMX_ForceExit();
    #endif
    }
}


void _MApp_Photo_UartSwitch(EN_PHOTO_UART_SWITCH enUartSwitch)
{
#if (defined(MIPS_CHAKRA) || defined(__AEONR2__) || defined(ARM_CHAKRA))
    switch (enUartSwitch)
    {
        case E_UART_SWITCH_CP:
            PHOTO_MSG_INFO_MUST(printf("[PHOTO] Uart from CP\n"));
    #if 0//(CHIP_FAMILY_TYPE == CHIP_FAMILY_S8) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5)
            mdrv_uart_connect(E_UART_PORT0, E_UART_AEON_R2);
    #else
            mdrv_uart_connect(E_UART_PORT0, E_UART_AEON);
    #endif
            break;

        case E_UART_SWITCH_HK:
            PHOTO_MSG_INFO_MUST(printf("[PHOTO] Uart from HK\n"));

    #if( defined(__AEONR2__) )
            mdrv_uart_connect(E_UART_PORT0, E_UART_AEON_R2);
    #else
            mdrv_uart_connect(E_UART_PORT0, E_UART_PIU_UART0);
    #endif
            break;

        default:
            break;
    }
#else

    switch (enUartSwitch)
    {
        case E_UART_SWITCH_CP:
            PHOTO_MSG_INFO_MUST(printf("[PHOTO] Uart from CP\n"));
            MDrv_WriteByte(0x1EAA, 0x14);
            break;

        case E_UART_SWITCH_HK:
            MDrv_WriteByte(0x1EAA, 0x0C);
            PHOTO_MSG_INFO_MUST(printf("[PHOTO] Uart from HK\n"));
            break;

        default:
            break;
    }
#endif // #if (defined(MIPS_CHAKRA) || defined(__AEONR2__) || defined(ARM_CHAKRA))
}

//-------------------------------------------------------------------------------------------------
// Local funcion -- mail box functions
//-------------------------------------------------------------------------------------------------
static BOOLEAN _MApp_Photo_SendCmd(MBX_Msg *pmbxMsg)
{
    MBX_Result mbxResult;
    U32 u32TimeOut = PHOTO_MBX_MSG_TIMEOUT, u32Cnt = 0;

    // start timer
    _MApp_Photo_Timer_Init(E_PHOTO_TIMER_MBX_MSG, u32TimeOut);

    while (!_MApp_Photo_Timer_IsTimeOut(E_PHOTO_TIMER_MBX_MSG))
    {
        if ((mbxResult = MSApi_MBX_SendMsg(pmbxMsg)) == E_MBX_SUCCESS)
        {
            // msg sent
            return TRUE;
        }

        PHOTO_MSG_INFO_MUST(printf("[PHOTO] %luth send msg (class: %u, idx: %u) failed (%u)!\n",
                u32Cnt, pmbxMsg->u8MsgClass, pmbxMsg->u8Index, (U16)mbxResult));
        MsOS_DelayTask(5);
        u32Cnt++; // for debug purpose
    }

    // time out
    return FALSE;
}

static void _MApp_Photo_SendCmd_Init(void)
{
    MBX_Msg mbxMsg;

    mbxMsg.eMsgType = E_MBX_MSG_TYPE_NORMAL;
    mbxMsg.u8MsgClass = E_MBX_CLASS_STILLIMAGE_CMD_IO;
    mbxMsg.u8Index = MB_STILLIMAGE_INIT_CMD;
    mbxMsg.u8ParameterCount = 4;
    mbxMsg.u8Parameters[0] = (U8)(_u32Photo_ShareMemAddr >> 24);
    mbxMsg.u8Parameters[1] = (U8)(_u32Photo_ShareMemAddr >> 16);
    mbxMsg.u8Parameters[2] = (U8)(_u32Photo_ShareMemAddr >> 8);
    mbxMsg.u8Parameters[3] = (U8)(_u32Photo_ShareMemAddr & 0x000000FF);

    _MApp_Photo_SendCmd(&mbxMsg);
}

static void _MApp_Photo_SendCmd_Start(void)
{
    MBX_Msg mbxMsg;

    mbxMsg.eMsgType = E_MBX_MSG_TYPE_NORMAL;
    mbxMsg.u8MsgClass = E_MBX_CLASS_STILLIMAGE_CMD_IO;
    mbxMsg.u8Index = MB_STILLIMAGE_START_CMD;
    mbxMsg.u8ParameterCount = 0;

    _MApp_Photo_SendCmd(&mbxMsg);
}

static void _MApp_Photo_SendCmd_Stop(void)
{
    MBX_Msg mbxMsg;

    mbxMsg.eMsgType = E_MBX_MSG_TYPE_NORMAL;
    mbxMsg.u8MsgClass = E_MBX_CLASS_STILLIMAGE_CMD_IO;
    mbxMsg.u8Index = MB_STILLIMAGE_STOP_CMD;
    mbxMsg.u8ParameterCount = 0;

    _MApp_Photo_SendCmd(&mbxMsg);
}

static void _MApp_Photo_SendCmd_AbortDataOperation(void)
{
    MBX_Msg mbxMsg;

    mbxMsg.eMsgType = E_MBX_MSG_TYPE_NORMAL;
    mbxMsg.u8MsgClass = E_MBX_CLASS_STILLIMAGE_DATA_IO_FAST;
    mbxMsg.u8Index = MB_STILLIMAGE_STOP_DATA_OPERATION;
    mbxMsg.u8ParameterCount = 0;

    _MApp_Photo_SendCmd(&mbxMsg);
}

static void _MApp_Photo_SendAck_FileOpen(void)
{
    MBX_Msg mbxMsg;

    mbxMsg.eMsgType = E_MBX_MSG_TYPE_NORMAL;
    mbxMsg.u8MsgClass = E_MBX_CLASS_STILLIMAGE_DATA_IO_FAST;
    mbxMsg.u8Index = MB_STILLIMAGE_DATA_REQ_ACK;
    mbxMsg.u8ParameterCount = 10;
    mbxMsg.u8Parameters[0] = MB_STILLIMAGE_DATA_IO_FILE_OPEN;
    mbxMsg.u8Parameters[1] = 0;
    mbxMsg.u8Parameters[2] = 0;
    mbxMsg.u8Parameters[3] = 0;
    mbxMsg.u8Parameters[4] = 0;
    mbxMsg.u8Parameters[5] = (U8)((_u32Photo_Decode_FileSize >> 24) & 0x000000FF);
    mbxMsg.u8Parameters[6] = (U8)((_u32Photo_Decode_FileSize >> 16) & 0x000000FF);
    mbxMsg.u8Parameters[7] = (U8)((_u32Photo_Decode_FileSize >> 8) & 0x000000FF);
    mbxMsg.u8Parameters[8] = (U8)(_u32Photo_Decode_FileSize & 0x000000FF);
    mbxMsg.u8Parameters[9] = _u8Photo_Decode_FileHandle;

    _MApp_Photo_SendCmd(&mbxMsg);
}

static void _MApp_Photo_SendAck_FileClose(void)
{
    MBX_Msg mbxMsg;

    mbxMsg.eMsgType = E_MBX_MSG_TYPE_NORMAL;
    mbxMsg.u8MsgClass = E_MBX_CLASS_STILLIMAGE_DATA_IO_FAST;
    mbxMsg.u8Index = MB_STILLIMAGE_DATA_REQ_ACK;
    mbxMsg.u8ParameterCount = 2;
    mbxMsg.u8Parameters[0] = MB_STILLIMAGE_DATA_IO_FILE_CLOSE;
    mbxMsg.u8Parameters[1] = _u8Photo_Decode_FileHandle;

    _MApp_Photo_SendCmd(&mbxMsg);
}

static void _MApp_Photo_SendAck_FileRead(MBX_Class enCmdClass, MB_STILLIMAGE_DATA_IO enIoType, U32 u32UnReadSize)
{
    MBX_Msg mbxMsg;

    mbxMsg.eMsgType = E_MBX_MSG_TYPE_NORMAL;
    mbxMsg.u8MsgClass = enCmdClass;
    mbxMsg.u8Index = MB_STILLIMAGE_DATA_REQ_ACK;
    mbxMsg.u8ParameterCount = 6;
    mbxMsg.u8Parameters[0] = enIoType;
    mbxMsg.u8Parameters[1] = (U8)((u32UnReadSize >> 24) & 0x000000FF);
    mbxMsg.u8Parameters[2] = (U8)((u32UnReadSize >> 16) & 0x000000FF);
    mbxMsg.u8Parameters[3] = (U8)((u32UnReadSize >> 8) & 0x000000FF);
    mbxMsg.u8Parameters[4] = (U8)(u32UnReadSize & 0x000000FF);
    mbxMsg.u8Parameters[5] = _u8Photo_Decode_FileHandle;

    _MApp_Photo_SendCmd(&mbxMsg);
}

static void _MApp_Photo_SendAck_FileSeek(MBX_Class enCmdClass, MB_STILLIMAGE_DATA_IO enIoType)
{
    MBX_Msg mbxMsg;

    mbxMsg.eMsgType = E_MBX_MSG_TYPE_NORMAL;
    mbxMsg.u8MsgClass = enCmdClass;
    mbxMsg.u8Index = MB_STILLIMAGE_DATA_REQ_ACK;
    mbxMsg.u8ParameterCount = 2;
    mbxMsg.u8Parameters[0] = enIoType;
    mbxMsg.u8Parameters[1] = _u8Photo_Decode_FileHandle;

    _MApp_Photo_SendCmd(&mbxMsg);
}

static void _MApp_Photo_SendAck_Memory_TotalSize(MBX_Class enCmdClass, MB_STILLIMAGE_DATA_IO enIoType, U32 u32TotalSize)
{
    MBX_Msg mbxMsg;

    mbxMsg.eMsgType = E_MBX_MSG_TYPE_NORMAL;
    mbxMsg.u8MsgClass = enCmdClass;
    mbxMsg.u8Index = MB_STILLIMAGE_DATA_REQ_ACK;
    mbxMsg.u8ParameterCount = 9;
    mbxMsg.u8Parameters[0] = enIoType;
    mbxMsg.u8Parameters[1] = 0;
    mbxMsg.u8Parameters[2] = 0;
    mbxMsg.u8Parameters[3] = 0;
    mbxMsg.u8Parameters[4] = 0;
    mbxMsg.u8Parameters[5] = (U8)((u32TotalSize >> 24) & 0x000000FF);
    mbxMsg.u8Parameters[6] = (U8)((u32TotalSize >> 16) & 0x000000FF);
    mbxMsg.u8Parameters[7] = (U8)((u32TotalSize >> 8) & 0x000000FF);
    mbxMsg.u8Parameters[8] = (U8)(u32TotalSize & 0x000000FF);

    _MApp_Photo_SendCmd(&mbxMsg);
}

static void _MApp_Photo_SendAck_Memory_RequestData(MBX_Class enCmdClass, MB_STILLIMAGE_DATA_IO enIoType, U32 u32UnReadSize, BOOLEAN bMore)
{
    MBX_Msg mbxMsg;

    mbxMsg.eMsgType = E_MBX_MSG_TYPE_NORMAL;
    mbxMsg.u8MsgClass = enCmdClass;
    mbxMsg.u8Index = MB_STILLIMAGE_DATA_REQ_ACK;
    mbxMsg.u8ParameterCount = 6;
    mbxMsg.u8Parameters[0] = enIoType;
    mbxMsg.u8Parameters[1] = (U8)((u32UnReadSize >> 24) & 0x000000FF);
    mbxMsg.u8Parameters[2] = (U8)((u32UnReadSize >> 16) & 0x000000FF);
    mbxMsg.u8Parameters[3] = (U8)((u32UnReadSize >> 8) & 0x000000FF);
    mbxMsg.u8Parameters[4] = (U8)(u32UnReadSize & 0x000000FF);
    mbxMsg.u8Parameters[5] = bMore;

    _MApp_Photo_SendCmd(&mbxMsg);
}

static BOOLEAN  _MApp_Photo_MailBox_Init(void)
{
    if(E_MBX_SUCCESS != MSApi_MBX_RegisterMSG(E_MBX_CLASS_STILLIMAGE_CMD_IO, MM_COMMON_MBX_QUEUESIZE))
    {
        if(E_MBX_SUCCESS != MSApi_MBX_UnRegisterMSG(E_MBX_CLASS_STILLIMAGE_CMD_IO))
        {
            PHOTO_MSG_INFO(printf("[PHOTO] E_MBX_CLASS_STILLIMAGE_CMD_IO unregister failed\n"));
            return FALSE;
        }
        else
        {
            if(E_MBX_SUCCESS != MSApi_MBX_RegisterMSG(E_MBX_CLASS_STILLIMAGE_CMD_IO, MM_COMMON_MBX_QUEUESIZE))
            {
                PHOTO_MSG_INFO(printf("[PHOTO] E_MBX_CLASS_STILLIMAGE_CMD_IO register failed\n"));
                return FALSE;
            }
        }
    }

    if(E_MBX_SUCCESS != MSApi_MBX_RegisterMSG(E_MBX_CLASS_STILLIMAGE_DATA_IO_FAST, MM_COMMON_MBX_QUEUESIZE))
    {
        if(E_MBX_SUCCESS != MSApi_MBX_UnRegisterMSG(E_MBX_CLASS_STILLIMAGE_DATA_IO_FAST))
        {
            PHOTO_MSG_INFO(printf("[PHOTO] E_MBX_CLASS_STILLIMAGE_DATA_IO_FAST unregister failed\n"));
            return FALSE;
        }
        else
        {
            if(E_MBX_SUCCESS != MSApi_MBX_RegisterMSG(E_MBX_CLASS_STILLIMAGE_DATA_IO_FAST, MM_COMMON_MBX_QUEUESIZE))
            {
                PHOTO_MSG_INFO(printf("[PHOTO] E_MBX_CLASS_STILLIMAGE_DATA_IO_FAST register failed\n"));
                return FALSE;
            }
        }
    }

    if(E_MBX_SUCCESS != MSApi_MBX_RegisterMSG(E_MBX_CLASS_STILLIMAGE_DATA_IO, MM_COMMON_MBX_QUEUESIZE))
    {
        if(E_MBX_SUCCESS != MSApi_MBX_UnRegisterMSG(E_MBX_CLASS_STILLIMAGE_DATA_IO))
        {
            PHOTO_MSG_INFO(printf("[PHOTO] E_MBX_CLASS_STILLIMAGE_DATA_IO unregister failed\n"));
            return FALSE;
        }
        else
        {
            if(E_MBX_SUCCESS != MSApi_MBX_RegisterMSG(E_MBX_CLASS_STILLIMAGE_DATA_IO, MM_COMMON_MBX_QUEUESIZE))
            {
                PHOTO_MSG_INFO(printf("[PHOTO] E_MBX_CLASS_STILLIMAGE_DATA_IO register failed\n"));
                return FALSE;
            }
        }
    }

    return TRUE;
}

static void _MApp_Photo_MailBox_Clear(void)
{
    //MailBox MB_Msg;
    MBX_MSGQ_Status Mstatus;
    U8 u8Cnt, u8i;
    MBX_Msg MB_Message;

    memset(&Mstatus,0,sizeof(MBX_MSGQ_Status));

    // clear E_MBX_CLASS_STILLIMAGE_CMD_IO mail box
    MSApi_MBX_GetMsgQueueStatus(E_MBX_CLASS_STILLIMAGE_CMD_IO, &Mstatus);
    u8Cnt = (U8)Mstatus.u32NormalMsgCount;
    // u8Cnt = msAPI_MailBox_GetMsgCount(Q_MM);
    for (u8i = 0; u8i < u8Cnt; u8i++)
    {
        MSApi_MBX_RecvMsg(E_MBX_CLASS_STILLIMAGE_CMD_IO, &MB_Message, 0,MBX_CHECK_NORMAL_MSG);
        // remove msg only, don't care the result
    }

    // clear E_MBX_CLASS_STILLIMAGE_DATA_IO_FAST mail box
    MSApi_MBX_GetMsgQueueStatus(E_MBX_CLASS_STILLIMAGE_DATA_IO_FAST, &Mstatus);
    u8Cnt = (U8)Mstatus.u32NormalMsgCount;
    for (u8i = 0; u8i < u8Cnt; u8i++)
    {
        MSApi_MBX_RecvMsg(E_MBX_CLASS_STILLIMAGE_DATA_IO_FAST, &MB_Message, 0,MBX_CHECK_NORMAL_MSG);
        // remove msg only, don't care the result
    }

    // clear E_MBX_CLASS_STILLIMAGE_DATA_IO mail box
    MSApi_MBX_GetMsgQueueStatus(E_MBX_CLASS_STILLIMAGE_DATA_IO, &Mstatus);
    u8Cnt = (U8)Mstatus.u32NormalMsgCount;
    for (u8i = 0; u8i < u8Cnt; u8i++)
    {
        MSApi_MBX_RecvMsg(E_MBX_CLASS_STILLIMAGE_DATA_IO, &MB_Message, 0,MBX_CHECK_NORMAL_MSG);
        // remove msg only, don't care the result
    }
}

static void _MApp_Photo_MailBox_Handler(void)
{
    //MailBox MB_Msg;
    U8 u8Cnt, u8i, u8j;
    U32 u32Addr, u32Size, u32Offset;
    BOOLEAN bMoreData;
    MBX_MSGQ_Status Mstatus;
    MBX_Msg MB_Message;

    memset(&Mstatus,0,sizeof(MBX_MSGQ_Status));//initial value
    memset(&MB_Message,0,sizeof(MBX_Msg));//initial value

    MSApi_MBX_GetMsgQueueStatus(E_MBX_CLASS_STILLIMAGE_CMD_IO, &Mstatus);
    if ((U8)Mstatus.u32NormalMsgCount == 0)
    {
        MSApi_MBX_GetMsgQueueStatus(E_MBX_CLASS_STILLIMAGE_DATA_IO_FAST, &Mstatus);
    }
    if ((U8)Mstatus.u32NormalMsgCount == 0)
    {
        MSApi_MBX_GetMsgQueueStatus(E_MBX_CLASS_STILLIMAGE_DATA_IO, &Mstatus);
    }
    u8Cnt = (U8)Mstatus.u32NormalMsgCount;

    //u8Cnt = msAPI_MailBox_GetMsgCount(Q_MM);
    for (u8i = 0; u8i < u8Cnt; u8i++)
    {
        //if (msAPI_MailBox_GetMsg(Q_MM, (U8 *)&MB_Msg) == MB_GET_MSG_OK)
        if ((MSApi_MBX_RecvMsg(E_MBX_CLASS_STILLIMAGE_CMD_IO, &MB_Message, 0,MBX_CHECK_NORMAL_MSG) == E_MBX_SUCCESS )
                ||(MSApi_MBX_RecvMsg(E_MBX_CLASS_STILLIMAGE_DATA_IO, &MB_Message, 0,MBX_CHECK_NORMAL_MSG) == E_MBX_SUCCESS )
                ||(MSApi_MBX_RecvMsg(E_MBX_CLASS_STILLIMAGE_DATA_IO_FAST, &MB_Message, 0,MBX_CHECK_NORMAL_MSG) == E_MBX_SUCCESS))
        {
            switch ((MBX_Class)MB_Message.u8MsgClass)
            {
                case E_MBX_CLASS_STILLIMAGE_CMD_IO:
                    switch ((MB_STILLIMAGE_CMD_IO)MB_Message.u8Index)
                    {
                        case MB_STILLIMAGE_INIT_ACK:
                            if (enPhoto_AckFlags & E_PHOTO_ACKFLG_WAIT_INIT)
                            {
                                _MApp_Photo_SetErrCode(TRUE, E_PHOTO_ERR_NONE);
                            }
                            REMOVE_PHOTO_FLAG(EN_PHOTO_ACK_FLAGS, enPhoto_AckFlags, E_PHOTO_ACKFLG_WAIT_INIT);
                            break;

                        case MB_STILLIMAGE_START_ACK:
                            if (enPhoto_AckFlags & E_PHOTO_ACKFLG_WAIT_START)
                            {
                                _MApp_Photo_SetErrCode(TRUE, E_PHOTO_ERR_NONE);
                            }
                            REMOVE_PHOTO_FLAG(EN_PHOTO_ACK_FLAGS, enPhoto_AckFlags, E_PHOTO_ACKFLG_WAIT_START);
                            break;

                        case MB_STILLIMAGE_STOP_ACK:
                            if (enPhoto_AckFlags & E_PHOTO_ACKFLG_WAIT_STOP)
                            {
                                // CP stopped as request, don't care the error code of CP
                            }
                            else
                            {
                                _MApp_Photo_SetErrCode(TRUE, E_PHOTO_ERR_NONE);
                            }
                            REMOVE_PHOTO_FLAG(EN_PHOTO_ACK_FLAGS, enPhoto_AckFlags, E_PHOTO_ACKFLG_WAIT_STOP);
                            break;

                        default:
                            break;
                    }
                    break;

                case E_MBX_CLASS_STILLIMAGE_DATA_IO_FAST:
                case E_MBX_CLASS_STILLIMAGE_DATA_IO:
                    switch ((MB_STILLIMAGE_DATA_IO)MB_Message.u8Index)
                    {
                        case MB_STILLIMAGE_DATA_REQ:
                            switch ((MB_STILLIMAGE_DATA_IO)MB_Message.u8Parameters[0])
                            {
                                case MB_STILLIMAGE_DATA_IO_FILE_OPEN:
                                    // already opened when been inited, do nothing for open

                                    // send ack
                                    _MApp_Photo_SendAck_FileOpen();
                                    break;

                                case MB_STILLIMAGE_DATA_IO_FILE_CLOSE:
                                    if (_u8Photo_Decode_FileHandle != MB_Message.u8Parameters[1])
                                    {
                                        PHOTO_MSG_INFO(printf("[PHOTO] FClose: file handle is incorrect\n"));
                                        break;
                                    }

                                    // close file
                                    _MApp_Photo_FileClose();

                                    // send ack
                                    _MApp_Photo_SendAck_FileClose();
                                    break;

                                case MB_STILLIMAGE_DATA_IO_FILE_READ:
                                case MB_STILLIMAGE_DATA_IO_FILE_NONBLOCKING_READ:
                                    if (_u8Photo_Decode_FileHandle != MB_Message.u8Parameters[9])
                                    {
                                        PHOTO_MSG_INFO(printf("[PHOTO] FRead (%d): file handle is incorrect\n", MB_Message.u8Parameters[0]));
                                        break;
                                    }

                                    // get addr
                                    u32Addr = 0;
                                    for (u8j = 1; u8j < 5; u8j++)
                                    {
                                        u32Addr = (u32Addr << 8) | MB_Message.u8Parameters[u8j];
                                    }

                                    // get size
                                    u32Size = 0;
                                    for (u8j = 5; u8j < 9; u8j++)
                                    {
                                        u32Size = (u32Size << 8) | MB_Message.u8Parameters[u8j];
                                    }

                                    // read file
                                    _eMbxCmdClass = (MBX_Class)MB_Message.u8MsgClass;
                                    _eDataIo = (MB_STILLIMAGE_DATA_IO)MB_Message.u8Parameters[0];
                                    _MApp_Photo_FileReadHandler(u32Addr, u32Size);
                                    break;

                                case MB_STILLIMAGE_DATA_IO_FILE_SEEK:
                                case MB_STILLIMAGE_DATA_IO_FILE_NONBLOCKING_SEEK:
                                    if (_u8Photo_Decode_FileHandle != MB_Message.u8Parameters[9])
                                    {
                                        PHOTO_MSG_INFO(printf("[PHOTO] FSeek (%d): file handle is incorrect\n", MB_Message.u8Parameters[0]));
                                    }

                                    // get offset
                                    u32Offset = 0;
                                    for (u8j = 5; u8j < 9; u8j++)
                                    {
                                        u32Offset = (u32Offset << 8) | MB_Message.u8Parameters[u8j];
                                    }

                                    // seek file
                                    _MApp_Photo_FileSeek(u32Offset);

                                    // send ack
                                    _MApp_Photo_SendAck_FileSeek(
                                            (MBX_Class)MB_Message.u8MsgClass,
                                            (MB_STILLIMAGE_DATA_IO)MB_Message.u8Parameters[0]);
                                    break;

                                case MB_STILLIMAGE_DATA_IO_MEMORY_GET_TOTAL_SIZE:
                                    // decide total size
                                    if (_gTotalSizeUnknown == TRUE)
                                    {
                                        u32Size = _U32_MAX;
                                    }
                                    else
                                    {
                                        // all data in memory
                                        u32Size = _MApp_Photo_ShareMem_GetInfo(E_STILLIMAGE_SHAREMEM_INPUT_DATA_BUFF_LEN);
                                    }

                                    // send ack
                                    _MApp_Photo_SendAck_Memory_TotalSize(
                                            (MBX_Class)MB_Message.u8MsgClass,
                                            (MB_STILLIMAGE_DATA_IO)MB_Message.u8Parameters[0],
                                            u32Size);
                                    break;

                                case MB_STILLIMAGE_DATA_IO_MEMORY_REQUIRE_DATA:
                                case MB_STILLIMAGE_DATA_IO_MEMORY_REQUIRE_DATA_NONBLOCKING:
                                    // get addr
                                    u32Addr = 0;
                                    for (u8j = 1; u8j < 5; u8j++)
                                    {
                                        u32Addr = (u32Addr << 8) | MB_Message.u8Parameters[u8j];
                                    }

                                    // get size
                                    u32Size = 0;
                                    for (u8j = 5; u8j < 9; u8j++)
                                    {
                                        u32Size = (u32Size << 8) | MB_Message.u8Parameters[u8j];
                                    }

                                    // read file
                                    bMoreData = FALSE;
                                    if (_gTotalSizeUnknown == TRUE)
                                    {
                                        if (_gDataRequestCallBack != NULL)
                                        {
                                            S32 s32ReadSize;

                                            s32ReadSize = (*_gDataRequestCallBack)((U8 *)_PA2VA(u32Addr), u32Size);
                                            if (s32ReadSize >= 0)
                                            {
                                                bMoreData = TRUE;
                                                u32Size -= s32ReadSize;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        // un-read size is 0 because it's in memory
                                        u32Size = 0;
                                    }

                                    // send ack
                                    _MApp_Photo_SendAck_Memory_RequestData(
                                            (MBX_Class)MB_Message.u8MsgClass,
                                            (MB_STILLIMAGE_DATA_IO)MB_Message.u8Parameters[0],
                                            u32Size,
                                            bMoreData);
                                    break;

                                default:
                                    break;
                            }
                            break;

                        case MB_STILLIMAGE_DATA_REQ_ACK:
                            // ??, do nothing
                        default:
                            break;
                    }
                    break;

                default:
                    break;
            }
        }
    }
}
#endif
//-------------------------------------------------------------------------------------------------
// Local funcion -- file operation functions
//-------------------------------------------------------------------------------------------------
static BOOLEAN _MApp_Photo_FileOpen(FileEntry *pFileEntry)
{
#if (defined(ENABLE_PTP) && (ENABLE_PTP))
    if (MApp_PTP_DeviceInUse())
    {
        _u8Photo_Decode_FileHandle = msAPI_PTP_FileOpen(pFileEntry, OPEN_MODE_FOR_READ);
    }
    else
#endif // #if (defined(ENABLE_PTP) && (ENABLE_PTP))
    {
        _u8Photo_Decode_FileHandle = msAPI_DataStreamIO_Open(pFileEntry, OPEN_MODE_FOR_READ, E_DATA_STREAM_TYPE_PHOTO);
    }

    if (_u8Photo_Decode_FileHandle == INVALID_FILE_HANDLE)
    {
        PHOTO_MSG_ERR(printf("[PHOTO] File open failed\n"));
        return FALSE;
    }

    _u32Photo_Decode_FileSize = _MApp_Photo_FileLength();
    return TRUE;
}

static void _MApp_Photo_FileClose(void)
{
    if (_u8Photo_Decode_FileHandle == INVALID_FILE_HANDLE)
    {
        PHOTO_MSG_DBG(printf("[PHOTO] File wasn't opened for close\n"));
        return;
    }

#if (defined(ENABLE_PTP) && (ENABLE_PTP))
    if (MApp_PTP_DeviceInUse())
    {
        msAPI_PTP_FileClose(_u8Photo_Decode_FileHandle);
    }
    else
#endif // #if (defined(ENABLE_PTP) && (ENABLE_PTP))
    {
        msAPI_DataStreamIO_Close(_u8Photo_Decode_FileHandle);
    }

    _u8Photo_Decode_FileHandle = INVALID_FILE_HANDLE;
    //_u32Photo_Decode_FileSize = 0;
}

static U32 _MApp_Photo_FileRead(U32 u32Addr, U32 u32Size)
{
    if (_u8Photo_Decode_FileHandle == INVALID_FILE_HANDLE)
    {
        PHOTO_MSG_INFO_MUST(printf("[PHOTO] File wasn't opened for read\n"));
        return 0;
    }

    if (_MApp_Photo_FileTell() == _u32Photo_Decode_FileSize)
    {
        return u32Size;
    }

#if (defined(ENABLE_PTP) && (ENABLE_PTP))
    if (MApp_PTP_DeviceInUse())
    {
        U32 u32UnReadSize;

        if (_bPhoto_DecodeThumbnail == TRUE)
        {
            msAPI_PTP_SetFileReadMode(EN_PTP_FILEREAD_THUMB);
        }

        // TBD: does the u32Addr has to be transferred by _PA2VA() as it is in msAPI_FCtrl_FileRead()
        u32UnReadSize = msAPI_PTP_FileRead(_u8Photo_Decode_FileHandle, u32Addr, u32Size);

        if (_bPhoto_DecodeThumbnail == TRUE)
        {
            msAPI_PTP_SetFileReadMode(EN_PTP_FILEREAD_ALL);
        }

        return u32UnReadSize;    }
    else
#endif // #if (defined(ENABLE_PTP) && (ENABLE_PTP))
    {
        return msAPI_DataStreamIO_Read(_u8Photo_Decode_FileHandle, (void *)u32Addr, u32Size);
    }
}

static BOOLEAN _MApp_Photo_FileSeek(U32 u32Offset)
{
    // TBD: do I really need this function?
    if (_u8Photo_Decode_FileHandle == INVALID_FILE_HANDLE)
    {
        PHOTO_MSG_INFO_MUST(printf("[PHOTO] File wasn't opened for seek\n"));
        return FALSE;
    }

    if (_MApp_Photo_FileLength() < u32Offset)
    {
        u32Offset = _MApp_Photo_FileLength();
    }

#if (defined(ENABLE_PTP) && (ENABLE_PTP))
    if (MApp_PTP_DeviceInUse())
    {
        PHOTO_MSG_INFO_MUST(printf("[PHOTO] No seek function for PTP\n"));
        return FALSE;
    }
    else
#endif // #if (defined(ENABLE_PTP) && (ENABLE_PTP))
    {
        return msAPI_DataStreamIO_Seek(_u8Photo_Decode_FileHandle, u32Offset, E_DATA_STREAM_SEEK_SET);
    }
}

static U32 _MApp_Photo_FileLength(void)
{
    if (_u8Photo_Decode_FileHandle == INVALID_FILE_HANDLE)
    {
        PHOTO_MSG_INFO_MUST(printf("[PHOTO] File wasn't opened for length\n"));
        return 0;
    }

#if (defined(ENABLE_PTP) && (ENABLE_PTP))
    if (MApp_PTP_DeviceInUse())
    {
        return msAPI_PTP_FileLength(_u8Photo_Decode_FileHandle);
    }
    else
#endif // #if (defined(ENABLE_PTP) && (ENABLE_PTP))
    {
        return msAPI_DataStreamIO_Length(_u8Photo_Decode_FileHandle);
    }
}

static U32 _MApp_Photo_FileTell(void)
{
    if (_u8Photo_Decode_FileHandle == INVALID_FILE_HANDLE)
    {
        PHOTO_MSG_INFO_MUST(printf("[PHOTO] File wasn't opened for tell\n"));
        return _U32_MAX;
    }

#if (defined(ENABLE_PTP) && (ENABLE_PTP))
    if (MApp_PTP_DeviceInUse())
    {
        return msAPI_PTP_FileTell(_u8Photo_Decode_FileHandle);
    }
    else
#endif // #if (defined(ENABLE_PTP) && (ENABLE_PTP))
    {
        return msAPI_DataStreamIO_Tell(_u8Photo_Decode_FileHandle);
    }
}
#if ENABLE_HK_PHOTO
//------------------------------------------------------------------------------
// Global Function Implementation
//------------------------------------------------------------------------------

BOOLEAN MApp_Photo_DecodeFile_Init(FileEntry *pFileEntry, BOOLEAN bThumbnail)
{
    EN_STILLIMAGE_CONTROL_FLAGS eControlFlags = E_STILLIMAGE_CONTROL_FLAG_ENABLE_NONE;

    // check status
    if (enPhoto_Status != E_PHOTO_STATUS_STOPPED)
    {
        return FALSE;
    }

    // make sure the other side is in expected state
    _MApp_Photo_Stop();

    // initialization
    _MApp_Photo_Reset(FALSE);
    _MApp_Photo_Timer_Disable(E_PHOTO_TIMER_NUM);
    _enPhoto_ErrCode = E_PHOTO_ERR_NONE;
    _u32Photo_Progress = 0;
    _u32Photo_Decode_FileSize = 0;
    _bPhoto_DecodeThumbnail = bThumbnail;

    _gTotalSizeUnknown = FALSE;
    _gDataRequestCallBack = NULL;
    bDecodeFromeMem = FALSE;

    // memory validation
    if (_MApp_Photo_Decode_MemoryValidation(E_PHOTO_DECODE) == FALSE)
    {
        return FALSE;
    }

#if (defined(ENABLE_PTP) && (ENABLE_PTP))
    if (MApp_PTP_DeviceInUse())
    {
        // PTP has its thumbnail put to a special location
        // and it's up to _MApp_Photo_FileRead() to get the data of thumbnail
        bThumbnail = FALSE;
    }
#endif // #if (defined(ENABLE_PTP) && (ENABLE_PTP))

    // open file
    if (_MApp_Photo_FileOpen(pFileEntry) == FALSE)
    {
        return FALSE;
    }

    //After open file, check file size. If the photo is 0x0 => Init fail.
    if (_u32Photo_Decode_FileSize == 0)
        return FALSE;

    ST_STILLIMAGE_CFG_PARAMS stInputCfgParams;
    memset(&stInputCfgParams, 0, sizeof(ST_STILLIMAGE_CFG_PARAMS));

    stInputCfgParams.enCmdType           = E_STILLIMAGE_DECODE;

    stInputCfgParams.u32MinWidth         = m_u32MinDecodeWidth;
    stInputCfgParams.u32MinHeight        = m_u32MinDecodeHeight;

    stInputCfgParams.u32JpegBaseLineMaxWidth     = m_u32MaxDecodeJpegBaselineWidth;
    stInputCfgParams.u32JpegBaseLineMaxHeight    = m_u32MaxDecodeJpegBaselineHeight;

    stInputCfgParams.u32JpegProgressiveMaxWidth  = m_u32MaxDecodeJpegProgressiveWidth;
    stInputCfgParams.u32JpegProgressiveMaxHeight = m_u32MaxDecodeJpegProgressiveHeight;

    stInputCfgParams.u32BmpMaxWidth  = m_u32MaxDecodeBmpWidth;
    stInputCfgParams.u32BmpMaxHeight = m_u32MaxDecodeBmpHeight;

    stInputCfgParams.u32PngMaxWidth  = m_u32MaxDecodePngWidth;
    stInputCfgParams.u32PngMaxHeight = m_u32MaxDecodePngHeight;

    stInputCfgParams.u32TiffMaxWidth  = m_u32MaxDecodeTiffWidth;
    stInputCfgParams.u32TiffMaxHeight = m_u32MaxDecodeTiffHeight;

    stInputCfgParams.u32GifMaxWidth  = m_u32MaxDecodeGifWidth;
    stInputCfgParams.u32GifMaxHeight = m_u32MaxDecodeGifHeight;

    stInputCfgParams.u32MPOBaseLineMaxWidth     = m_u32MaxDecodeMpoBaselineWidth;
    stInputCfgParams.u32MPOBaseLineMaxHeight    = m_u32MaxDecodeMpoBaselineHeight;

    stInputCfgParams.u32MPOProgressiveMaxWidth  = m_u32MaxDecodeMpoProgressiveWidth;
    stInputCfgParams.u32MPOProgressiveMaxHeight = m_u32MaxDecodeMpoProgressiveHeight;

    stInputCfgParams.bDecodeThumbnail    = bThumbnail;
    stInputCfgParams.enDataAccessMethod  = E_STILLIMAGE_VIA_MAILBOX;

    stInputCfgParams.u32InputBuffAddr    = _u32DataBuffAddr;
    stInputCfgParams.u32InputBuffLen     = _u32DataBuffSize;

    stInputCfgParams.u32OutputBuffAddr   = _u32OutputBuffAddr;
    stInputCfgParams.u32OutputBuffLen    = _u32OutputBuffSize;

    stInputCfgParams.u32ProgressiveJpegBuffAddr  = _u32ProgressiveJpegMemAddr;
    stInputCfgParams.u32ProgressiveJpegBuffLen   = _u32ProgressiveJpegMemSize;

    stInputCfgParams.u32MemPoolBuffAddr  = _u32PoolMemAddr;
    stInputCfgParams.u32MemPoolBuffLen   = _u32PoolMemSize;

    stInputCfgParams.bIsStreamMode               = _bEnableStreamMode;
    stInputCfgParams.u32StreamMode_ReadTimeOut   = _U32_MAX;

    stInputCfgParams.u32FrameInfoArrayAddr = _u32GifFrameInfoArrayAddr;
    stInputCfgParams.u32FrameInfoArraySize = _u32GifFrameInfoArraySize;
    stInputCfgParams.bOnlyDecodeFirstFrame = FALSE;
    stInputCfgParams.bOnlyPlayFirstLoopForLoopAnimation = TRUE;

    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_ENABLE_JPEG_DECODER);
    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_SUUPPORT_JPEG_CMYK);
    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_SUUPPORT_JPEG_RGB);
    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_STOP_WHEN_RST_ERROR);
#if ENABLE_MAPP_PHOTO_BMP
    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_ENABLE_BMP_DECODER);
#endif
#if ENABLE_MAPP_PHOTO_PNG
    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_ENABLE_PNG_DECODER);
#endif
#if ENABLE_MAPP_PHOTO_GIF
    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_ENABLE_GIF_DECODER);
#endif
#if ENABLE_MAPP_PHOTO_TIFF
    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_ENABLE_TIFF_DECODER);
#endif
    if(bDoAlphaBlendForPng)
    {
        SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_ENABLE_DO_ALPHA_BLEND_PNG);
    }
    stInputCfgParams.u32ControlFlags     = eControlFlags;

    stInputCfgParams.stDataIoFuncs.pfStillImage_DataIO_Open     = _MApp_Photo_DataIO_Open;
    stInputCfgParams.stDataIoFuncs.pfStillImage_DataIO_Close    = _MApp_Photo_DataIO_Close;
    stInputCfgParams.stDataIoFuncs.pfStillImage_DataIO_Read     = _MApp_Photo_DataIO_Read;
    stInputCfgParams.stDataIoFuncs.pfStillImage_DataIO_Seek     = _MApp_Photo_DataIO_Seek;

    if (msAPI_StillImage_Init(&stInputCfgParams) != E_STILLIMAGE_RET_OK)
    {
        if (msAPI_StillImage_GetErrorCode() == E_STILLIMAGE_ERR_NONE)
        {
            _MApp_Photo_SetErrCode(FALSE, E_PHOTO_ERR_NOT_SUPPORT_IMAGE_FMT);
        }
        else
        {
            _MApp_Photo_SetErrCode(TRUE, E_PHOTO_ERR_NONE);
        }
        _MApp_Photo_Stop();
        _MApp_Photo_Reset(TRUE);
        PHOTO_MSG_INFO(printf("[PHOTO] Decode photo init fail\n"));
        return FALSE;
    }

    // clear output buffer
    switch ((EN_PHOTO_OUTPUT_FORMAT)MApp_Photo_GetInfo(E_PHOTO_INFO_OUTPUT_FORMAT))
    {
        case E_PHOTO_OUTPUT_ARGB8888:
            msAPI_GE_ClearFrameBufferByWord(_u32OutputBuffAddr, _u32OutputBuffSize, 0x00000000);
            MApi_GFX_FlushQueue();
            break;

        case E_PHOTO_OUTPUT_YUV422:
            msAPI_GE_ClearFrameBufferByWord(_u32OutputBuffAddr, _u32OutputBuffSize, 0x80008000);
            MApi_GFX_FlushQueue();
            break;

        default:
            break;
    }

#if PHOTO_NO_SINGLE_PIXEL
    //YUV422 will lose color if only 1 pixel, so we show unupport file
    if( (MApp_Photo_GetInfo(E_PHOTO_INFO_WIDTH)==1) || (MApp_Photo_GetInfo(E_PHOTO_INFO_HEIGHT)==1) )
    {
        PHOTO_MSG_DBG(printf("width or height is 1, dont support"));
        return FALSE;
    }
#endif

    // save cmd
    _enPhotoCmd = E_PHOTO_DECODE;
    PHOTO_MSG_INFO(printf("[PHOTO] Decode File\n"));

    enPhoto_Status = E_PHOTO_STATUS_INITED;
    PHOTO_MSG_INFO(printf("[PHOTO] statue, %d --> %d\n", E_PHOTO_STATUS_STOPPED, E_PHOTO_STATUS_INITED));

    // show detail information
    _MApp_Photo_Decode_ShowImageInfo();

    return TRUE;
}


BOOLEAN MApp_Photo_DecodeMemory_Init(BOOLEAN bThumbnail, MApp_Photo_DataRequestCallBack pfCallBack)
{
    EN_STILLIMAGE_CONTROL_FLAGS eControlFlags = E_STILLIMAGE_CONTROL_FLAG_ENABLE_NONE;

    // check status
    if (enPhoto_Status != E_PHOTO_STATUS_STOPPED)
    {
        return FALSE;
    }

    // make sure the other side is in expected state
    _MApp_Photo_Stop();

    // initialization
    _MApp_Photo_Reset(FALSE);
    _MApp_Photo_Timer_Disable(E_PHOTO_TIMER_NUM);
    _enPhoto_ErrCode = E_PHOTO_ERR_NONE;
    _u32Photo_Progress = 0;
    _u32Photo_Decode_FileSize = 0;
    _bPhoto_DecodeThumbnail = bThumbnail;

    _gTotalSizeUnknown = (pfCallBack == NULL ? FALSE : TRUE);
    _gDataRequestCallBack = pfCallBack;
    bDecodeFromeMem = TRUE;

    // memory validation
    if (_MApp_Photo_Decode_MemoryValidation(E_PHOTO_DECODE) == FALSE)
    {
        return FALSE;
    }

    ST_STILLIMAGE_CFG_PARAMS stInputCfgParams;
    memset(&stInputCfgParams, 0, sizeof(ST_STILLIMAGE_CFG_PARAMS));

    stInputCfgParams.enCmdType           = E_STILLIMAGE_DECODE;

    stInputCfgParams.u32MinWidth         = m_u32MinDecodeWidth;
    stInputCfgParams.u32MinHeight        = m_u32MinDecodeHeight;

    stInputCfgParams.u32JpegBaseLineMaxWidth     = m_u32MaxDecodeJpegBaselineWidth;
    stInputCfgParams.u32JpegBaseLineMaxHeight    = m_u32MaxDecodeJpegBaselineHeight;

    stInputCfgParams.u32JpegProgressiveMaxWidth  = m_u32MaxDecodeJpegProgressiveWidth;
    stInputCfgParams.u32JpegProgressiveMaxHeight = m_u32MaxDecodeJpegProgressiveHeight;

    stInputCfgParams.u32BmpMaxWidth  = m_u32MaxDecodeBmpWidth;
    stInputCfgParams.u32BmpMaxHeight = m_u32MaxDecodeBmpHeight;

    stInputCfgParams.u32PngMaxWidth  = m_u32MaxDecodePngWidth;
    stInputCfgParams.u32PngMaxHeight = m_u32MaxDecodePngHeight;

    stInputCfgParams.u32TiffMaxWidth  = m_u32MaxDecodeTiffWidth;
    stInputCfgParams.u32TiffMaxHeight = m_u32MaxDecodeTiffHeight;

    stInputCfgParams.u32GifMaxWidth  = m_u32MaxDecodeGifWidth;
    stInputCfgParams.u32GifMaxHeight = m_u32MaxDecodeGifHeight;

    stInputCfgParams.u32MPOBaseLineMaxWidth     = m_u32MaxDecodeMpoBaselineWidth;
    stInputCfgParams.u32MPOBaseLineMaxHeight    = m_u32MaxDecodeMpoBaselineHeight;

    stInputCfgParams.u32MPOProgressiveMaxWidth  = m_u32MaxDecodeMpoProgressiveWidth;
    stInputCfgParams.u32MPOProgressiveMaxHeight = m_u32MaxDecodeMpoProgressiveHeight;

    stInputCfgParams.bDecodeThumbnail    = bThumbnail;
    stInputCfgParams.enDataAccessMethod  = E_STILLIMAGE_IN_MEMORY;

    stInputCfgParams.u32InputBuffAddr    = _u32DataBuffAddr;
    stInputCfgParams.u32InputBuffLen     = _u32DataBuffSize;

    stInputCfgParams.u32OutputBuffAddr   = _u32OutputBuffAddr;
    stInputCfgParams.u32OutputBuffLen    = _u32OutputBuffSize;

    stInputCfgParams.u32ProgressiveJpegBuffAddr  = _u32ProgressiveJpegMemAddr;
    stInputCfgParams.u32ProgressiveJpegBuffLen   = _u32ProgressiveJpegMemSize;

    stInputCfgParams.u32MemPoolBuffAddr  = _u32PoolMemAddr;
    stInputCfgParams.u32MemPoolBuffLen   = _u32PoolMemSize;

    stInputCfgParams.bIsStreamMode               = _bEnableStreamMode;
    stInputCfgParams.u32StreamMode_ReadTimeOut   = _U32_MAX;

    stInputCfgParams.u32FrameInfoArrayAddr = _u32GifFrameInfoArrayAddr;
    stInputCfgParams.u32FrameInfoArraySize = _u32GifFrameInfoArraySize;
    stInputCfgParams.bOnlyDecodeFirstFrame = FALSE;
    stInputCfgParams.bOnlyPlayFirstLoopForLoopAnimation = TRUE;

    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_ENABLE_JPEG_DECODER);
    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_SUUPPORT_JPEG_CMYK);
    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_SUUPPORT_JPEG_RGB);
    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_STOP_WHEN_RST_ERROR);
#if ENABLE_MAPP_PHOTO_BMP
    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_ENABLE_BMP_DECODER);
#endif
#if ENABLE_MAPP_PHOTO_PNG
    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_ENABLE_PNG_DECODER);
#endif
#if ENABLE_MAPP_PHOTO_GIF
    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_ENABLE_GIF_DECODER);
#endif
#if ENABLE_MAPP_PHOTO_TIFF
    SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_ENABLE_TIFF_DECODER);
#endif
    if(bDoAlphaBlendForPng)
    {
        SET_PHOTO_FLAG(EN_STILLIMAGE_CONTROL_FLAGS, eControlFlags, E_STILLIMAGE_CONTROL_FLAG_ENABLE_DO_ALPHA_BLEND_PNG);
    }
    stInputCfgParams.u32ControlFlags     = eControlFlags;

    stInputCfgParams.stDataIoFuncs.pfStillImage_DataIO_Open     = _MApp_Photo_DataIO_Open;
    stInputCfgParams.stDataIoFuncs.pfStillImage_DataIO_Close    = _MApp_Photo_DataIO_Close;
    stInputCfgParams.stDataIoFuncs.pfStillImage_DataIO_Read     = _MApp_Photo_DataIO_Read;
    stInputCfgParams.stDataIoFuncs.pfStillImage_DataIO_Seek     = _MApp_Photo_DataIO_Seek;

    if (msAPI_StillImage_Init(&stInputCfgParams) != E_STILLIMAGE_RET_OK)
    {
        if (msAPI_StillImage_GetErrorCode() == E_STILLIMAGE_ERR_NONE)
        {
            _MApp_Photo_SetErrCode(FALSE, E_PHOTO_ERR_NOT_SUPPORT_IMAGE_FMT);
        }
        else
        {
            _MApp_Photo_SetErrCode(TRUE, E_PHOTO_ERR_NONE);
        }
        _MApp_Photo_Stop();
        _MApp_Photo_Reset(TRUE);
        PHOTO_MSG_INFO(printf("[PHOTO] Decode photo init fail\n"));
        return FALSE;
    }

    // clear output buffer
    switch ((EN_PHOTO_OUTPUT_FORMAT)MApp_Photo_GetInfo(E_PHOTO_INFO_OUTPUT_FORMAT))
    {
        case E_PHOTO_OUTPUT_ARGB8888:
            msAPI_GE_ClearFrameBufferByWord(_u32OutputBuffAddr, _u32OutputBuffSize, 0x00000000);
            MApi_GFX_FlushQueue();
            break;

        case E_PHOTO_OUTPUT_YUV422:
            msAPI_GE_ClearFrameBufferByWord(_u32OutputBuffAddr, _u32OutputBuffSize, 0x80008000);
            MApi_GFX_FlushQueue();
            break;

        default:
            break;
    }

#if PHOTO_NO_SINGLE_PIXEL
    //YUV422 will lose color if only 1 pixel, so we show unupport file
    if( (MApp_Photo_GetInfo(E_PHOTO_INFO_WIDTH)==1) || (MApp_Photo_GetInfo(E_PHOTO_INFO_HEIGHT)==1) )
    {
        PHOTO_MSG_DBG(printf("width or height is 1, dont support"));
        return FALSE;
    }
#endif

    // save cmd
    _enPhotoCmd = E_PHOTO_DECODE;
    PHOTO_MSG_INFO(printf("[PHOTO] Decode Memory\n"));

    enPhoto_Status = E_PHOTO_STATUS_INITED;
    PHOTO_MSG_INFO(printf("[PHOTO] statue, %d --> %d\n", E_PHOTO_STATUS_STOPPED, E_PHOTO_STATUS_INITED));

    // show detail information
    _MApp_Photo_Decode_ShowImageInfo();

    return TRUE;
}

BOOLEAN MApp_Photo_EncodeMemory_Init(U32 u32Width, U32 u32Height, MApp_Photo_DataRequestCallBack pfCallBack)
{
    UNUSED(u32Width);
    UNUSED(u32Height);
    UNUSED(pfCallBack);
        return FALSE;
}
EN_RET MApp_Photo_Main(void)
{
    EN_RET enRet = EXIT_PHOTO_DECODING;
    EN_PHOTO_STATUS enPhoto_PreStatus = enPhoto_Status;
    static U32 u32StartTime = 0;

    switch (enPhoto_Status)
    {
        default:
        case E_PHOTO_STATUS_STOPPED:
            return EXIT_PHOTO_EXIT;

        case E_PHOTO_STATUS_INITED:
            // start timer
            _MApp_Photo_Timer_Init(E_PHOTO_TIMER_PROGRESS, _u32Photo_Progress_Timeout);
            _MApp_Photo_Timer_Init(E_PHOTO_TIMER_WDT, _u32Photo_WDT_Timeout);

            u32StartTime = msAPI_Timer_GetTime0();
            enPhoto_Status = E_PHOTO_STATUS_WORKING;
            break;

        case E_PHOTO_STATUS_WORKING:
            {
                EN_STILLIMAGE_RET enDecodeRet;

                enDecodeRet = msAPI_StillImage_Task();
                switch(enDecodeRet)
                {
                    case E_STILLIMAGE_RET_FAIL:
                    {
                        enRet = EXIT_PHOTO_DECODE_FAIL;
                        break;
                    }
                    case E_STILLIMAGE_RET_DONE:
                    {
                        enRet = EXIT_PHOTO_DECODE_DONE;
                        break;
                    }
                    case E_STILLIMAGE_RET_DECODE_ONE_FRAME_DONE:
                    {
                        enRet = EXIT_PHOTO_DECODE_ONE_FRAME_DONE;
                        break;
                    }
                    default:
                    break;
                }
            }
            break;
    }

    switch (enRet)
    {
        case EXIT_PHOTO_DECODE_DONE:
            if(MApp_Photo_GetInfo(E_PHOTO_INFO_FILE_FORMAT) == E_PHOTO_FILE_GIF)
            {
                MApp_Photo_GIFDecodeDone(TRUE);
            }
            // fall through
        case EXIT_PHOTO_DECODE_FAIL:

            _MApp_Photo_Stop();
            _MApp_Photo_Reset(TRUE);
            _MApp_Photo_Timer_Disable(E_PHOTO_TIMER_NUM);

            PHOTO_MSG_INFO_MUST(printf("[PHOTO] total time: %lu, progress: %lu\n",
                    msAPI_Timer_DiffTimeFromNow(u32StartTime),
                    MApp_Photo_GetInfo(E_PHOTO_INFO_PROGRESS)));

            // when encoding image, information is gained after encoding done
            if (_enPhotoCmd == E_PHOTO_ENCODE)
            {
                _MApp_Photo_Decode_ShowImageInfo();
            }
            else if(m_bForceDisplayPartialError
                 && MApp_Photo_GetInfo(E_PHOTO_INFO_PROGRESS) > 0)
            {
                PHOTO_MSG_INFO_MUST(printf("[PHOTO] decode error, but decode part:%d percent.\n", MApp_Photo_GetInfo(E_PHOTO_INFO_PROGRESS)));
                enRet = EXIT_PHOTO_DECODE_DONE;
            }
            enPhoto_Status = E_PHOTO_STATUS_STOPPED;
            break;
        case EXIT_PHOTO_DECODE_ONE_FRAME_DONE:
            PHOTO_MSG_INFO_MUST(printf("[PHOTO] decode one frame done.\n"));
            break;
        case EXIT_PHOTO_DECODING:
            if (_MApp_Photo_Timer_IsTimeOut(E_PHOTO_TIMER_PROGRESS))
            {
                PHOTO_MSG_INFO(printf("[PHOTO] progress: %04lu\n", MApp_Photo_GetInfo(E_PHOTO_INFO_PROGRESS)));
                _MApp_Photo_Timer_Init(E_PHOTO_TIMER_PROGRESS, _u32Photo_Progress_Timeout);
            }
            // fall through
        default:
            break;
    }

    if (enPhoto_PreStatus != enPhoto_Status)
    {
        PHOTO_MSG_INFO(printf("[PHOTO] statue, %d --> %d\n", enPhoto_PreStatus, enPhoto_Status));
    }

    return enRet;
}

void MApp_Photo_Stop(void)
{
    if (enPhoto_Status == E_PHOTO_STATUS_STOPPED)
    {
        return;
    }

    // disable timers when user stop
    _MApp_Photo_Timer_Disable(E_PHOTO_TIMER_WDT);
    _MApp_Photo_Timer_Disable(E_PHOTO_TIMER_PROGRESS);

    _MApp_Photo_Stop();
    _MApp_Photo_Reset(TRUE);
    enPhoto_Status = E_PHOTO_STATUS_STOPPED;
    bDoAlphaBlendForPng = TRUE;
}

U32 MApp_Photo_GetInfo(EN_PHOTO_INFO enInfo)
{
    U32 u32Info;

    switch (enInfo)
    {
        case E_PHOTO_INFO_INPUT_DATA_FORMAT:
            return msAPI_StillImage_GetInputDataFormat();

        case E_PHOTO_INFO_FILE_FORMAT:
            u32Info = msAPI_StillImage_GetInputDataFormat();
            switch (MAJOR_FORMAT(u32Info))
            {
                case E_STILLIMAGE_INPUT_DATA_JPEG:
                    return E_PHOTO_FILE_JPEG;

                case E_STILLIMAGE_INPUT_DATA_BMP:
                    return E_PHOTO_FILE_BMP;

                case E_STILLIMAGE_INPUT_DATA_PNG:
                    return E_PHOTO_FILE_PNG;

                case E_STILLIMAGE_INPUT_DATA_TIFF:
                    return E_PHOTO_FILE_TIFF;

                case E_STILLIMAGE_INPUT_DATA_GIF:
                    return E_PHOTO_FILE_GIF;

                default:
                    break;
            }
            return E_PHOTO_FILE_UNKNOWN;

        case E_PHOTO_INFO_IMAGE_TYPE:
            u32Info = msAPI_StillImage_GetInputDataFormat();
            switch (MAJOR_FORMAT(u32Info))
            {
                case E_STILLIMAGE_INPUT_DATA_JPEG:
                    switch (u32Info)
                    {
                        default:
                        case E_STILLIMAGE_INPUT_DATA_JPEG_BASELINE:
                            return E_PHOTO_IMAGE_JPEG_BASELINE;

                        case E_STILLIMAGE_INPUT_DATA_JPEG_PROGRESSIVE:
                            return E_PHOTO_IMAGE_JPEG_PROGRESSIVE;
                    }
                    break;

                case E_STILLIMAGE_INPUT_DATA_BMP:
                    return E_PHOTO_IMAGE_BMP;

                case E_STILLIMAGE_INPUT_DATA_PNG:
                    switch (u32Info)
                    {
                        default:
                        case E_STILLIMAGE_INPUT_DATA_PNG_NON_INTERLACED:
                            return E_PHOTO_IMAGE_PNG_NON_INTERLACED;

                        case E_STILLIMAGE_INPUT_DATA_PNG_INTERLACED:
                            return E_PHOTO_IMAGE_PNG_INTERLACED;
                    }
                    break;

                case E_STILLIMAGE_INPUT_DATA_TIFF:
                    switch (u32Info)
                    {
                        default:
                        case E_STILLIMAGE_INPUT_DATA_TIFF_16_BITS:
                            return E_PHOTO_IMAGE_TIFF;
                    }
                    break;

                case E_STILLIMAGE_INPUT_DATA_GIF:
                    switch (u32Info)
                    {
                        default:
                        case E_STILLIMAGE_INPUT_DATA_GIF_NOT_ANIMATION:
                            return E_PHOTO_IMAGE_GIF_NON_ANIMATION;

                        case E_STILLIMAGE_INPUT_DATA_GIF_ANIMATION:
                            return E_PHOTO_IMAGE_GIF_ANIMATION;
                    }
                    break;

                default:
                    break;
            }
            return E_PHOTO_IMAGE_UNKNOWN;

        case E_PHOTO_INFO_FILE_SIZE:
            switch (msAPI_StillImage_GetDataAccessMethod())
            {
                case E_STILLIMAGE_VIA_MAILBOX:
                    return _u32Photo_Decode_FileSize;

                case E_STILLIMAGE_IN_MEMORY:
                    if (_gTotalSizeUnknown)
                    {
                        return _U32_MAX;
                    }

                    return msAPI_StillImage_GetInputBuffLen();

                default:
                   return 0;
            }
            return 0;

        case E_PHOTO_INFO_IMAGE_WIDTH:
            return msAPI_StillImage_GetImageWidth();

        case E_PHOTO_INFO_IMAGE_HEIGHT:
            return msAPI_StillImage_GetImageHeight();

        case E_PHOTO_INFO_PITCH:
            return msAPI_StillImage_GetOutputPitch();

        case E_PHOTO_INFO_WIDTH:
            return msAPI_StillImage_GetOutputWidth();

        case E_PHOTO_INFO_HEIGHT:
            return msAPI_StillImage_GetOutputHeight();

        case E_PHOTO_INFO_SIZE:
            return msAPI_StillImage_GetOutputSize();

        case E_PHOTO_INFO_HAS_THUMBNAIL:
            return msAPI_StillImage_HasThumbnail();

        case E_PHOTO_INFO_OUTPUT_FORMAT:
            switch (msAPI_StillImage_GetOutputDataFormat())
            {
                case E_STILLIMAGE_OUTPU_RAW_YUV422:
                    return E_PHOTO_OUTPUT_YUV422;

                case E_STILLIMAGE_OUTPU_RAW_ARGB8888:
                    return E_PHOTO_OUTPUT_ARGB8888;

                case E_STILLIMAGE_OUTPU_ARGB1555:
                    return E_PHOTO_OUTPUT_ARGB1555;

                case E_STILLIMAGE_OUTPU_JPEG:
                    return E_PHOTO_OUTPUT_JPEG;

                default:
                    return E_PHOTO_OUTPUT_FORMAT_UNKNOWN;
            }

        case E_PHOTO_INFO_PROGRESS:
            return msAPI_StillImage_GetProgress() / 10;

        case E_PHOTO_INFO_ERROR_INFO:
            return msAPI_StillImage_GetErrorCode();

        case E_PHOTO_INFO_EXIF_WIDTH:
            return msAPI_StillImage_GetExifWidth();

        case E_PHOTO_INFO_EXIF_HEIGHT:
            return msAPI_StillImage_GetExifHeight();

        case E_PHOTO_INFO_ORIENTATION:
            switch (msAPI_StillImage_Orientation())
            {
                case E_STILLIMAGE_ORIENT_RESERVED:
                    return E_PHOTO_ORIENT_RESERVED;

                case E_STILLIMAGE_ORIENT_ROTATE_0:
                    return E_PHOTO_ORIENT_ROTATE_0;

                case E_STILLIMAGE_ORIENT_MIRROR_LR:
                    return E_PHOTO_ORIENT_MIRROR_LR;

                case E_STILLIMAGE_ORIENT_ROTATE_180:
                    return E_PHOTO_ORIENT_ROTATE_180;

                case E_STILLIMAGE_ORIENT_MIRROR_TB:
                    return E_PHOTO_ORIENT_MIRROR_TB;

                case E_STILLIMAGE_ORIENT_ROTATE_90_MIRROR_LR:
                    return E_PHOTO_ORIENT_ROTATE_90_MIRROR_LR;

                case E_STILLIMAGE_ORIENT_E_ORIENT_ROTATE_90:
                    return E_PHOTO_ORIENT_E_ORIENT_ROTATE_90;

                case E_STILLIMAGE_ORIENT_ROTATE_90_MIRROR_TB:
                    return E_PHOTO_ORIENT_ROTATE_90_MIRROR_TB;

                case E_STILLIMAGE_ORIENT_ROTATE_270:
                    return E_PHOTO_ORIENT_ROTATE_270;

                case E_STILLIMAGE_ORIENT_NOT_FOUND:
                    return E_PHOTO_ORIENT_NOT_FOUND;

                case E_STILLIMAGE_ORIENT_UNDEFINE:
                default:
                    return E_PHOTO_ORIENT_UNDEFINE;

            }
            break;

        case E_PHOTO_INFO_HAS_DATE_TIME:
            return msAPI_StillImage_HasDateTime();

        case E_PHOTO_INFO_DATE_TIME_YEAR:
            return msAPI_StillImage_DateTimeYear();

        case E_PHOTO_INFO_DATE_TIME_MONTH:
            return msAPI_StillImage_DateTimeMonth();

        case E_PHOTO_INFO_DATE_TIME_DAY:
            return msAPI_StillImage_DateTimeDay();

        case E_PHOTO_INFO_DATE_TIME_HOUR:
            return msAPI_StillImage_DateTimeHour();

        case E_PHOTO_INFO_DATE_TIME_MINUTE:
            return msAPI_StillImage_DateTimeMinute();

        case E_PHOTO_INFO_DATE_TIME_SECOND:
            return msAPI_StillImage_DateTimeSecond();

        case E_PHOTO_INFO_DECODED_FRAME_INDEX:
            return msAPI_StillImage_GetDecodedFrameIndex();

        case E_PHOTO_INFO_DISPLAYED_FRAME_INDEX:
            return msAPI_StillImage_GetDisplayedFrameIndex();

        case E_PHOTO_INFO_SLOT_NUM:
            return msAPI_StillImage_GetGifSlotTotalNum();

        case E_PHOTO_INFO_FRAME_SIZE:
            return msAPI_StillImage_GetGifOutputFrameSize();

        case E_PHOTO_INFO_IS_MPO_DISPARITY_TYPE:
            return msAPI_StillImage_GetMPODisparityType();

        case E_PHOTO_INFO_SCALE_DOWN_FACTOR:
            return msAPI_StillImage_DownScaleFactor();

        default:
            break;
    }

    return 0;
}

BOOLEAN MApp_Photo_GetExifInfo(EN_PHOTO_EXIF_INFO enInfo, void *pBufAddr, U16 u16BufSize)
{
    if(pBufAddr == NULL || u16BufSize == 0)
    {
        return FALSE;
    }

    BOOLEAN bRet=TRUE;
    U32 u32InfoAddr, u32Info;
    U16 u16InfoSize;

    switch (enInfo)
    {
        case E_PHOTO_EXIF_INFO_CAMERA_MAKER:
            //Get "pointer" of camera maker
            u32InfoAddr = msAPI_StillImage_GetEXIFManufacturer();
            u16InfoSize = EXIF_CAMERA_MAKER_SIZE;
            break;

        case E_PHOTO_EXIF_INFO_CAMERA_MODEL:
            //Get "pointer" of camera model
            u32InfoAddr = msAPI_StillImage_GetEXIFModel();
            u16InfoSize = EXIF_CAMERA_MODEL_SIZE;
            break;

        case E_PHOTO_EXIF_INFO_FLASH_MODE:
            u32Info = msAPI_StillImage_GetEXIFFlash();
            u32InfoAddr = (U32)&u32Info;
            u16InfoSize = (u16BufSize<4)?u16BufSize:4;
            break;

        case E_PHOTO_EXIF_INFO_ISO_SPEED:
            u32Info = msAPI_StillImage_GetEXIFISOSpeedRatings();
            u32InfoAddr = (U32)&u32Info;
            u16InfoSize = (u16BufSize<4)?u16BufSize:4;
            break;

        case E_PHOTO_EXIF_INFO_EXPOSURE_BIAS:
            //Get "pointer" of RATIONAL structure
            u32InfoAddr = msAPI_StillImage_GetEXIFExposureBiasValue();
            u16InfoSize = sizeof(ST_STILLIMAGE_RATIONAL);
            break;

        case E_PHOTO_EXIF_INFO_EXPOSURE_TIME:
            //Get "pointer" of RATIONAL structure
            u32InfoAddr = msAPI_StillImage_GetEXIFExposureTime();
            u16InfoSize = sizeof(ST_STILLIMAGE_RATIONAL);
            break;

        case E_PHOTO_EXIF_INFO_F_STOP:
            //Get "pointer" of RATIONAL structure
            u32InfoAddr = msAPI_StillImage_GetEXIFFNumber();
            u16InfoSize = sizeof(ST_STILLIMAGE_RATIONAL);
            break;

        case E_PHOTO_EXIF_INFO_FOCAL_LENGTH:
            //Get "pointer" of RATIONAL structure
            u32InfoAddr = msAPI_StillImage_GetEXIFFocalLength();
            u16InfoSize = sizeof(ST_STILLIMAGE_RATIONAL);
            break;

        case E_PHOTO_EXIF_INFO_SHUTTER_SPEED:
            //Get "pointer" of RATIONAL structure
            u32InfoAddr = msAPI_StillImage_GetEXIFShutterSpeedValue();
            u16InfoSize = sizeof(ST_STILLIMAGE_RATIONAL);
            break;
        case E_PHOTO_EXIF_INFO_APERTURE:
            //Get "pointer" of RATIONAL structure
            u32InfoAddr = msAPI_StillImage_GetEXIFApertureValue();
            u16InfoSize = sizeof(ST_STILLIMAGE_RATIONAL);
            break;

        default:
            bRet = FALSE;
            break;
    }

    if(bRet == TRUE)
    {
        if(u16BufSize >= u16InfoSize && u32InfoAddr != 0)
        {
            memcpy(pBufAddr, (void*)u32InfoAddr, u16InfoSize);
        }
        else
        {
            PHOTO_MSG_ERR(printf("%s LINE %d -- buffer is too small.\n", __FUNCTION__, __LINE__));
            bRet = FALSE;
        }
    }

    return bRet;
}

EN_PHOTO_ERRCODE MApp_Photo_GetErrCode(void)
{
    return _enPhoto_ErrCode;
}
#endif

#if ENABLE_HK_PHOTO
static void _MApp_Photo_Stop(void)
{
    msAPI_StillImage_Stop();
}

static BOOLEAN _MApp_Photo_DataIO_Open(U64 *pu64Size, U8 *pu8Hdl)
{
    if(bDecodeFromeMem)
    {
        *pu8Hdl = 0;
        if (_gTotalSizeUnknown == TRUE)
        {
            *pu64Size = (U64)_U32_MAX;
        }
        else
        {
            // all data in memory
            *pu64Size = (U64)msAPI_StillImage_GetInputBuffLen();
        }
    }
    else
    {
        if (_u8Photo_Decode_FileHandle == INVALID_FILE_HANDLE)
        {
            return FALSE;
        }

        *pu8Hdl = _u8Photo_Decode_FileHandle;
        *pu64Size = (U64)_u32Photo_Decode_FileSize;
    }
    return TRUE;
}

static BOOLEAN _MApp_Photo_DataIO_Close(U8 u8Hdl)
{
    UNUSED(u8Hdl);
    return TRUE;
}

static U32 _MApp_Photo_DataIO_Read(U8 u8Hdl, U32 u32Addr, U32 u32Size)
{
    UNUSED(u8Hdl);
    if(bDecodeFromeMem)
    {
        if (_gTotalSizeUnknown == TRUE)
        {
            if (_gDataRequestCallBack != NULL)
            {
                S32 s32ReadSize = (*_gDataRequestCallBack)((U8 *)_PA2VA(u32Addr), u32Size);

                if (s32ReadSize >= 0)
                {
                    u32Size -= s32ReadSize;
                }
            }
        }
        else
        {
            // un-read size is 0 because it's in memory
            u32Size = 0;
        }
        return u32Size;
    }
    else
    {
        return _MApp_Photo_FileRead(u32Addr, u32Size);
    }
}

static BOOLEAN _MApp_Photo_DataIO_Seek(U8 u8Hdl, U64 u64Offset)
{
    UNUSED(u8Hdl);
    if(bDecodeFromeMem)
    {
        return TRUE;
    }
    else
    {
        return _MApp_Photo_FileSeek((U32)u64Offset);
    }
}
#endif

BOOLEAN MApp_Photo_SetForceDisplayPhotoPartialError(BOOLEAN bForceDisPlay)
{
    m_bForceDisplayPartialError = bForceDisPlay;

    return TRUE;
}

#endif // #if (ENABLE_DMP)

#undef _MAPP_PHOTO_C_

