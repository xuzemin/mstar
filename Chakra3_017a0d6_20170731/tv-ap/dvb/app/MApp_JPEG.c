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
////////////////////////////////////////////////////////////////////////////////

#define MAPP_JPEG_C

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>

// Global Layer
#include "sysinfo.h"
#include "Panel.h"

// driver layer
#include "SysInit.h"

// API Layer
#include "msAPI_MIU.h"
#include "msAPI_Memory.h"
#include "msAPI_Timer.h"
#include "msAPI_JPEG.h"
//#include "msAPI_FAT.h"
//#include "msAPI_NTFS.h"
#include "msAPI_FCtrl.h"
#include "msAPI_MSDCtrl.h"

#include "apiGOP.h"
// AP Layer
#include "MApp_GlobalVar.h"
#include "MApp_GlobalFunction.h"
#include "MApp_Exit.h"
#include "MApp_JPEG.h"
#include "MApp_ChannelChange.h"

//UI Layer
//ZUI_TODO: #include "MApp_UiMenu.h"

static U8 code _DUMMY;

#if 0//def ENABLE_MEDIAPLAYER
//-------------------------------------------------------------------------------------------------
// Local Defines
//-------------------------------------------------------------------------------------------------
#define     JPEG_SRC_BLOCK_SIZE     2048
// JPEG decode timeout
// [071030 Andy] Longer decode timeout
#define     JPEG_DECODE_TIMEOUT_MS  3000UL
//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------
#define JPEG_DBG(x)

/******************************************************************************/
/*                                 Enum                                       */
/******************************************************************************/
typedef enum
{
    STATE_JPEG_NONE =0,
    STATE_JPEG_INIT,
    STATE_JPEG_OPEN_FILE,
    STATE_JPEG_DECODE,
    STATE_JPEG_WAIT_DONE,
    STATE_JPEG_FEED_HEADER,
} EN_JPEG_STATE;

//-------------------------------------------------------------------------------------------------
// Global Variables
//-------------------------------------------------------------------------------------------------

extern BOOLEAN bEnableThumbnail;
extern U8 g_JpegFSEnvironmentID;
extern U8 u8ExifHandle;

//-------------------------------------------------------------------------------------------------
// Local Variables
//-------------------------------------------------------------------------------------------------
static EN_JPEG_STATE        enJpegState   =  STATE_JPEG_INIT;

static U32  gJpegSrcBlockSize;
static U8   u8JpegFileHandle = FCTRL_INVALID_FILE_HANDLE;

U32 u32JpegFileBytesLeft;
static U32  u32DecodeTime;

U16 seedDataOffset=0;
U16 dataOffsetOfSector=0;
U16 dataFrameSize=0;
static U8 firstContinueRead=0;

U32 u32JpegDecodeTime;

//-------------------------------------------------------------------------------------------------
// Local Function Prototypes
//-------------------------------------------------------------------------------------------------




//-------------------------------------------------------------------------------------------------
// Function Implementation
//-------------------------------------------------------------------------------------------------

BOOLEAN MApp_Jpeg_Initial(JPEG_OUTPUT_FORMAT enFormat)
{
    U8 i;

    for (i = 0; i < 3; i++)
    {
        if (msAPI_JPEG_Init(enFormat, ((MAD_JPEG_OUT_MEMORY_TYPE & MIU1) ? (MAD_JPEG_OUT_ADR | MIU_INTERVAL) : (MAD_JPEG_OUT_ADR))) == TRUE)
            break;
    }

    if (i == 3)
        return FALSE;

    return TRUE;
}



BOOLEAN MApp_Jpeg_OpenFile(FileEntry* pFileEntry, U16 dataOffset, U16 dataSize)
{

    seedDataOffset=dataOffset;
    dataFrameSize=dataSize;
    firstContinueRead=0;



    gJpegSrcBlockSize = JPEG_SRC_BLOCK_SIZE;

    u8JpegFileHandle = msAPI_FCtrl_FileOpen(pFileEntry, OPEN_MODE_BINARY_FOR_READ);


   dataOffsetOfSector=seedDataOffset%512;


    if(u8JpegFileHandle == FCTRL_INVALID_FILE_HANDLE)
    {
        return FALSE;
    }

    if(seedDataOffset/512)
     {

         u32JpegFileBytesLeft = msAPI_FCtrl_FileRead(u8JpegFileHandle, JPEG_FILE_BACKBUFF_ADDR, ((U16) (seedDataOffset/512))*512);
     }

    if(dataOffsetOfSector)
     {

         u32JpegFileBytesLeft = msAPI_FCtrl_FileRead(u8JpegFileHandle, JPEG_FILE_BACKBUFF_ADDR+2048, 512);
         msAPI_MIU_Copy(JPEG_FILE_BACKBUFF_ADDR+2048+dataOffsetOfSector, JPEG_FILE_BACKBUFF_ADDR, 512-dataOffsetOfSector, MIU_SDRAM2SDRAM);
         u32JpegFileBytesLeft = msAPI_FCtrl_FileRead(u8JpegFileHandle, JPEG_FILE_BACKBUFF_ADDR+512-dataOffsetOfSector, 2048);
     }
    else
     {
         u32JpegFileBytesLeft = msAPI_FCtrl_FileRead(u8JpegFileHandle, JPEG_FILE_BACKBUFF_ADDR, 4*512);

      }

      firstContinueRead=1;

    return TRUE;
}

BOOLEAN MApp_Jpeg_ReadFile()
{
    msAPI_MIU_Copy(JPEG_FILE_BACKBUFF_ADDR, ((MAD_ES_BUFFER_MEMORY_TYPE & MIU1) ? (MAD_ES_BUFFER_ADR | MIU_INTERVAL) : (MAD_ES_BUFFER_ADR)), JPEG_SRC_BLOCK_SIZE, MIU_SDRAM2SDRAM);
    return TRUE;
}

BOOLEAN MApp_Jpeg_ReadFileToBackBuff()
{
    if (u32JpegFileBytesLeft == 0 && u8JpegFileHandle != FCTRL_INVALID_FILE_HANDLE)
    {
        // [071024 Andy] Just refine code style
        // not EOF
        if(dataOffsetOfSector)
        {
            if(firstContinueRead)
            {
                msAPI_MIU_Copy(JPEG_FILE_BACKBUFF_ADDR+2048, JPEG_FILE_BACKBUFF_ADDR, 512-dataOffsetOfSector, MIU_SDRAM2SDRAM);
            }
            else
            {
                msAPI_MIU_Copy(JPEG_FILE_BACKBUFF_ADDR+2048, JPEG_FILE_BACKBUFF_ADDR, 512-dataOffsetOfSector, MIU_SDRAM2SDRAM);
                firstContinueRead=0;
            }
            u32JpegFileBytesLeft = msAPI_FCtrl_FileRead(u8JpegFileHandle, JPEG_FILE_BACKBUFF_ADDR+512-dataOffsetOfSector, 4*512);
        }
        else
        {
           u32JpegFileBytesLeft = msAPI_FCtrl_FileRead(u8JpegFileHandle, JPEG_FILE_BACKBUFF_ADDR, 2048);
        }
    }
    return TRUE;
}

JPEG_DECODE_STATUS MApp_Jpeg_DecodeFragment()
{
    JPEG_DECODE_STATUS u8DecodeStatus;
    U32 ioStart;

    u8DecodeStatus = JPEG_DECODE_RUNNING;

    switch (msAPI_JPEG_GetDecoderState())
    {
        case JPEG_DECODER_STATE_INPUT:
        case JPEG_DECODER_STATE_INITIAL:
            ioStart = msAPI_Timer_GetTime0();
            MApp_Jpeg_ReadFile();
            msAPI_JPEG_StartDecode(((MAD_ES_BUFFER_MEMORY_TYPE & MIU1) ? (MAD_ES_BUFFER_ADR | MIU_INTERVAL) : (MAD_ES_BUFFER_ADR)), JPEG_SRC_BLOCK_SIZE);
            MApp_Jpeg_ReadFileToBackBuff();
            u32JpegDecodeTime = msAPI_Timer_GetTime0();
            break;
        case JPEG_DECODER_STATE_DECODE:
            if (msAPI_Timer_DiffTimeFromNow(u32JpegDecodeTime) >= JPEG_DECODE_TIMEOUT_MS)
            {
                // timeout
                msAPI_JPEG_StopDecoding();
                return JPEG_DECODE_ERROR1;
            }
            u8DecodeStatus = msAPI_JPEG_GetDecodeStatus();
            break;
        case JPEG_DECODER_STATE_STATUS:
            u8DecodeStatus = msAPI_JPEG_GetDecodeStatus();
            break;
    }

    return u8DecodeStatus;
}

// [071029 Andy] Get JPEG buffer by streaming input
JPEG_RETURN_STATUS MApp_JPEG_GetExifInfo(FileEntry* pFileEntry, JPEG_EXIF_INFO *pExifInfo)
{
    U16 u16Marker, u16Len;

    memset(pExifInfo, 0, sizeof(JPEG_EXIF_INFO));

    u8ExifHandle = msAPI_FCtrl_FileOpen(pFileEntry, OPEN_MODE_BINARY_FOR_READ);
    if (u8ExifHandle == FCTRL_INVALID_FILE_HANDLE)
    {
        return JPEG_RETURN_ERR_FILE;
    }

    msAPI_JPEG_DecodeExifInfo_Init();

    // search SOI first
    u16Marker = (U16)msAPI_JPEG_GetBytes(2);
    if (u16Marker != JPEG_MARKER_SOI)
    {
        return JPEG_RETURN_ERR_NOT_JPEG;      // not a JPEG
    }

    pExifInfo->u8Flags |= JPEG_INFO_FLAG_JPEG;

    do
    {
        u16Marker = (U16)msAPI_JPEG_GetBytes(2);
        u16Len = (U16)msAPI_JPEG_GetBytes(2);

        // [071031 Andy] To support progressive
        if ((u16Marker == JPEG_MARKER_SOF0) || (u16Marker == JPEG_MARKER_SOF2))
        {
            msAPI_JPEG_Sof0Parser(pExifInfo, u16Len-2);
            pExifInfo->u8Flags |= JPEG_INFO_FLAG_BASELINE;

        }
        else if (u16Marker == JPEG_MARKER_APP1)
        {
            msAPI_JPEG_DecodeExifInfo(pExifInfo, u16Len-2);
        }
        else if (u16Marker == JPEG_MARKER_SOS)
        {
            break;
        }
        else
        {
            msAPI_JPEG_SkipByteCnt(u16Len-2);
        }
    } while (!msAPI_JPEG_DecodeExif_EndOfFile());

    pExifInfo->u32FileSize = msAPI_FCtrl_FileLength(u8ExifHandle);
    msAPI_FCtrl_FileClose(u8ExifHandle);

    if (pExifInfo->u8Flags & JPEG_INFO_FLAG_BASELINE)
    {
        return JPEG_RETURN_SUCCESS;
    }
    else
    {
        return JPEG_RETURN_ERR_NOT_JPEG;
    }
}

JPEG_DECODE_STATUS MApp_Jpeg_Decode (FileEntry* pFileEntry, U16 dataOffset,U16 dataSize,JPEG_PLAY_COMMAND enCommand)
{
    JPEG_DECODE_STATUS u8DecodeStatus;
    JPEG_RETURN_STATUS enJpegRetVal;
    U16 u16Width, u16Height;


    if (enCommand == JPEG_CMD_STOP)
    {
        // [071024 Andy] Stop JPEG decoding here
        if (enJpegState != STATE_JPEG_INIT)
        {
            if ( u8JpegFileHandle != FCTRL_INVALID_FILE_HANDLE )
            {
                msAPI_FCtrl_FileClose(u8JpegFileHandle);
                u8JpegFileHandle = FCTRL_INVALID_FILE_HANDLE;
            }
            enJpegState = STATE_JPEG_INIT;
            msAPI_JPEG_StopDecoding();
            return JPEG_RETURN_SUCCESS;
        }
        return JPEG_RETURN_SUCCESS;
    }

    enJpegRetVal = JPEG_RETURN_DECODING;

    switch(enJpegState)
    {
        case STATE_JPEG_INIT:
            u32DecodeTime = msAPI_Timer_GetTime0();
            if (enCommand == JPEG_CMD_DECODE_SD)
            {
                MApp_Jpeg_Initial(JPEG_OUTPUT_FORMAT_SD);
            }
            else
            {
                MApp_Jpeg_Initial(JPEG_OUTPUT_FORMAT_HD);
            }
            enJpegState = STATE_JPEG_OPEN_FILE;
            break;

        case STATE_JPEG_OPEN_FILE:
            if ( u8JpegFileHandle != FCTRL_INVALID_FILE_HANDLE )
            {
                msAPI_FCtrl_FileClose(u8JpegFileHandle);
                u8JpegFileHandle = FCTRL_INVALID_FILE_HANDLE;
            }
            if (MApp_Jpeg_OpenFile(pFileEntry, dataOffset,dataSize) == FALSE)
            {
                enJpegState = STATE_JPEG_INIT;
                enJpegRetVal = JPEG_RETURN_ERR_FILE;
                break;
            }
            enJpegState = STATE_JPEG_DECODE;

        case STATE_JPEG_DECODE:
            u8DecodeStatus = MApp_Jpeg_DecodeFragment();
            if (u8DecodeStatus == JPEG_DECODE_RUNNING)
                break;

            if (u8JpegFileHandle != FCTRL_INVALID_FILE_HANDLE)
            {
                msAPI_FCtrl_FileClose(u8JpegFileHandle);
                u8JpegFileHandle = FCTRL_INVALID_FILE_HANDLE;
            }

            printf("\nJPEG Decode Time = %lu\n", msAPI_Timer_DiffTimeFromNow(u32DecodeTime));

            if ((u8DecodeStatus == JPEG_DECODE_DONE) && (msAPI_JPEG_GetImageInfo(&u16Width, &u16Height)))
            {
                enJpegRetVal = JPEG_RETURN_SUCCESS;
            }
            else    // error return
            {
                if ((bEnableThumbnail) && (!(msAPI_JPEG_GetExifInfo() & JPEG_EXIF_THUMBNAIL_EXIST)))
                {
                    enJpegRetVal = JPEG_RETURN_ERR_NO_THUMBNAIL;
                }
                else
                {
                    enJpegRetVal = JPEG_RETURN_ERR_DECODE;
                }
            }
            enJpegState = STATE_JPEG_INIT;
            break;

    }

    return enJpegRetVal;
}

#endif

#undef MAPP_JPEG_C

