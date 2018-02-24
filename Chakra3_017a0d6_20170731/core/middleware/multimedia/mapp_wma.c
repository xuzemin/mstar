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
// (“MStar Confidential Information”) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define MAPP_WMA_C

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>

#include "debug.h"
// Global Layer
#include "sysinfo.h"
#include "MsTypes.h"
#include "apiPNL.h"//#include "Panel.h"

#include "SysInit.h"
//#include "drvAUDIO.h"
//
#include "MsTypes.h"
#include "drvBDMA.h"
#include "drvGPIO.h"
//#include "Tv_china.h"
//#include "drvausif.h"
#include "drvSERFLASH.h"

#ifdef MSOS_TYPE_LINUX
#include "MsIRQ.h"
#include "MsOS.h"
#endif

// API Layer
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "msAPI_MIU.h"
#include "msAPI_Memory.h"
#include "msAPI_Timer.h"
#include "msAPI_FCtrl.h"
#include "msAPI_WMA.h"
#include "apiGOP.h"
#include "msAPI_Flash.h"
#include "msAPI_audio.h"
#include "msAPI_Music.h"

// AP Layer
#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalVar.h"
#include "MApp_GlobalFunction.h"
#include "MApp_Exit.h"
#if 0//ndef ZUI
#include "MApp_UiMenuDraw.h"
#include "MApp_UiMenu.h"
#endif
//UI Layer
#include "MApp_UiMediaPlayer_Define.h"

#include "mapp_wma.h"
#include "MApp_Audio.h"
#include "MApp_FileBrowser.h"
#include "MApp_UiMediaPlayer.h"
#include "MApp_SaveData.h"
#include "MApp_IR.h"
#include "MApp_MassStorage.h"
#include "mapp_mplayer.h"
#include "msAPI_DataStreamIO.h"

#if (ENABLE_DMP)
#if ENABLE_WMDRMPD
#include "mapp_wmdrmpd.h"
#endif

//static code U8 u8Dummy;

#if (ENABLE_WMA)

#define ENABLE_WMA_INDEX_TABLE  (1)

#ifdef WMA_INFO_READ_ADR
#ifdef WMA_INFO_READ_LEN
#if WMA_INFO_READ_LEN
#define ENABLE_FILE_BM      (1)
#endif
#endif
#else
#define ENABLE_FILE_BM      (0)
#endif

#if ENABLE_ASF_PARSING
#define WMA_ASF_PACKET_HEADER_SIZE 16 //bytes
static U8 _pu8ASFPayloadHeader[17];  // 0~3 Sync word(4Byte): 7F FD 80 02
                                                         // 4~7 Payload Data Size(4Byte):00 00 0A AB
                                                         // 8~15 dummy (8Byte): 00 00 00 00 00 00 00 00
                                                         // 16 Left Size
static U32 _u32CurrentPacket=0;
static U32 _u32CurrentPayload=0;
static U32 _u32PayloadWriteLeft=0;
//static U32 m_u32BufLeftSize, m_u32BufReadSize;
#if ENABLE_WMA_INDEX_TABLE
static U32 u32WMAPayloadTableAddr = ((M4A_STCO_MEMORY_TYPE & MIU1) ? (M4A_STCO_ADR | MIU_INTERVAL) : (M4A_STCO_ADR));
#define WMA_INDEX_TABLE_MAX_NUM         ((M4A_STCO_LEN >> 3) - 1)
typedef struct
{
    U32 u32WMAPayloadPTime;
    U32 u32WMAPayloadFilePos;
} ST_WMA_INDEX_TABLE;
#endif
#endif

#define msAPI_Steam_Seek(x,y) msAPI_DataStreamIO_Seek(x,y,E_DATA_STREAM_SEEK_SET)

#ifdef HSS_UI
#include <stdlib.h>
#include "MApp_UiMenuComponent.h"
#include "MApp_MassStorage.h"

#define UI_MEDIA_PLAYER_MP3_EQ_BAR_NUM    8
#define UI_MEDIA_PLAYER_MP3_EQ_BAR_X      NEWUI_MEDIA_PLAYER_PREVIEW_BG_START_X  \
                                                                               + (NEWUI_MEDIA_PLAYER_PREVIEW_BG_WIDTH \
                                                                               - UI_MEDIA_PLAYER_MP3_EQ_BAR_W*UI_MEDIA_PLAYER_MP3_EQ_BAR_NUM \
                                                                               -UI_MEDIA_PLAYER_MP3_EQ_BAR_W*(UI_MEDIA_PLAYER_MP3_EQ_BAR_NUM-1)/2)/2
#define UI_MEDIA_PLAYER_MP3_EQ_BAR_Y      NEWUI_MEDIA_PLAYER_PREVIEW_BG_START_Y
#define UI_MEDIA_PLAYER_MP3_EQ_BAR_W      30
#define UI_MEDIA_PLAYER_MP3_EQ_BAR_H      NEWUI_MEDIA_PLAYER_PREVIEW_BG_HEIGHT*2/3
#endif

//-------------------------------------------------------------------------------------------------
// Local Defines
//-------------------------------------------------------------------------------------------------
#define FILE_PROPERTIES_OBJECT_ID                   0x0
#define FILE_PROPERTIES_OBJECT_SIZE                 0x10
#define FILE_PROPERTIES_FILE_ID                     0x18
#define FILE_PROPERTIES_FILE_SIZE                   0x28
#define FILE_PROPERTIES_CREATION_DATE               0x30
#define FILE_PROPERTIES_DATA_PACKETS_COUNT          0x38
#define FILE_PROPERTIES_PLAY_DURATION               0x40
#define FILE_PROPERTIES_SEND_DURATION               0x48
#define FILE_PROPERTIES_PREROLL                     0x50
#define FILE_PROPERTIES_FLAGS                       0x58
#define FILE_PROPERTIES_MINIMUM_DATA_PACKET_SIZE    0x5C
#define FILE_PROPERTIES_MAXIMUM_DATA_PACKET_SIZE    0x60
#define FILE_PROPERTIES_MAXIMUM_BITRATE             0x64

//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------
#define WMA_DBG(x)                     //x
#define WMA_INFO(x)                    //x
#define PRINT_WMA_STATE                 0

#define WMA_SHOW_TIMEOUT                4000
#define WMA_TIME_OUT_THRESHOLD          3000 // ms
#define WMA_FILE_END_TIME_OUT_THRESHOLD 10000 // ms

static U8 u8MusicFFFWMode = 0;
#define WMA_NORMAL_MODE 0
#define WMA_FF_Mode BIT0
#define WMA_FW_Mode BIT1

#define CODEC_FORMAT_WMA_PRO 0x162
#define CODEC_FORMAT_MP3 0x55

#define WMA_HEADER_READ_LEN 0x1000
#define WMA_PROBE_READ_LEN  0x1000

#define WMA_MEASURE 0

#define ENABLE_WMA_DSP_DEBUG 0
#define WMA_MAX_TITLE_LENGTH 128
#define WMA_MAX_AUTHOR_LENGTH 128
#define WMA_MAX_YEAR_LENGTH 32
#define WMA_MAX_ALBUM_LENGTH 128


/******************************************************************************/
/*                                 Enum                                       */
/******************************************************************************/

//-------------------------------------------------------------------------------------------------
// Global Variables
//-------------------------------------------------------------------------------------------------

#if WMA_MEASURE
   BOOLEAN bwmaCollect=FALSE;
   U32 u32TotalRead_1=0;
   U32 u32TotalRead_2=0;
   U32 u32TotalRead_3=0;

   U32 u32TotalPrevReadNum_2 = 0;

   U32 u32TotalLooptime = 0;

   U32 u32TotalReadByte_2 = 0;
   U32 u32TotalReadByte_3 = 0;
#endif

#if ENABLE_WMA_DSP_DEBUG
   U8 u8FileHandle0 = NULL;
#endif


#ifndef U64
    typedef unsigned long long U64;
#endif


//-------------------------------------------------------------------------------------------------
// Local Variables
//-------------------------------------------------------------------------------------------------
typedef struct
{
    U16 u16FormatTag;
    U8 u8Version;
    U16 u16Channels;
    U16 u16BlockAlign;
    U16 u16BitsSample;
    U32 u32ChannelMask;
    U16 u16Encopt;
    U32 u32BitRate;
    U32 u32ByteRate;
    U32 u32SampleRate;
    U32 u32HeaderSize;
    U32 u32PacketSize;             //Packet = Error Correction Data + Payload Parsing Information + Payload Data + Padding
    U16 u16PacketOffset;
    U16 u16PayloadOffset;
    U32 u32TotalPacket;
#if ENABLE_WMA_INDEX_TABLE
    U32 u32SkipPayload;
#else
    U32 u32SkipPacket;
#endif
    U32 u32FileSize;
    U32 u32Duration;
#if ENABLE_WMA_INDEX_TABLE
    U32 u32PreRoll;
#endif
    U32 u32CurrentPlayTime;
    U32 u32PlayTimer;
    U8 u8Title[WMA_MAX_TITLE_LENGTH];
    U16 u16TitleLength;
    U8 u8Author[WMA_MAX_AUTHOR_LENGTH];
    U16 u16AuthorLength;
    U8 u8Year[WMA_MAX_YEAR_LENGTH];
    U16 u16YearLength;
    U8 u8Album[WMA_MAX_ALBUM_LENGTH];
    U16 u16AlbumLength;
#if ENABLE_ASF_PARSING
    //--  WMA DRC Info -- //
    U8 u8DeviceConformanceTemplate[32];
    U32 u32IsVBR;
    U32 u32WMADRCPeakReference;
    U32 u32WMADRCPeakTarget;
    U32 u32WMADRCAverageReference;
    U32 u32WMADRCAverageTarget;
    //------------------//
    //--  Error correction data (Property Flag) --//
    U32 u32ErrorCLength;                  //Error Correction Length
    //------------------------------------//
    //--  Payload parsing information (Length Type Flags) --//
    BOOLEAN bIsMultiPayloads;
    U8 u8SequenceLType;            //Sequence Length Type
    U8 u8PaddingLType;               //Padding Length Type
    U8 u8PacketLType;                //Packet Length Type
    U32 u32SequenceLength;            //Sequence Length
    U32 u32PaddingLength;               //Padding Length
    //----------------------------------------------//
    //--  Payload parsing information (Property Flag) --//
    U8 u8ReplicatedDLType;         //Replicated Data Length Type                  00:0  01:1  10:2  11:3
    U8 u8OffseIMOLType;             //Offset Into Media Object Length Type       0      8     16     32   (bits)
    U8 u8MediaONLType;             //Media Object Number Length Type
    U8 u8StreamNLType;             //Stream Number Length Type
    U32 u32ReplicatedDLength;         //Replicated Data Length
    U32 u32OffseIMOLength;             //Offset Into Media Object Length
    U32 u32MediaONLengthe;            //Media Object Number Length
    U32 u32StreamNLength;             //Stream Number Length
    //-----------------------------------------//
    //--  Payload information  --//
    U8 u8NumPayloads;                  //Number of Payloads
    U8 u8PayloadLType;                  //Payload Length Type
    U32 u32PayloadLength;                  //Payload Length
    U8 u8PresentationTimeDelta;        //Presentation Time Delta
#if ENABLE_WMA_INDEX_TABLE
    U8 u8FirstNumPayloads;               //Number of Payloads in 1st Packet
    U32 u32TotalPayloads;               //Number of Total Payloads in this file
#endif
    //-----------------------//
#endif
    BOOLEAN bCheckFfFb;
    BOOLEAN bHeaderFound;
    BOOLEAN bHeaderExtensionFound;
    BOOLEAN bHE_MetadataObjectFound;
    BOOLEAN bWMADRCFound;
    BOOLEAN bStreamFound;
    BOOLEAN bContentFound;
    BOOLEAN bExContentFound;             // Extended Content Description Object, it is optional
    BOOLEAN bDataObjectFound;
    BOOLEAN bExContentEObjectFound; //Extended Content Encryption Object
    U32 u32ExContentEObjectLocation;
    U32 u32ExContentEObjectSize;
    BOOLEAN bContentEObjectFound; //Content Encryption Object
    U32 u32ContentEObjectLocation;
    U32 u32ContentEObjectSize;
    BOOLEAN bFilePropertiesFound;
    BOOLEAN bAdvancedMutualExclusionObject;
    U8 u8StreamNumber;
    U8 u8CurrentStreamIndex;
    U16 u16StreamID[128];
    U16 u16CurrentStreamId;
} ST_WMA_INFO;

EN_WMA_STATE enWmaState     = STATE_WMA_NONE;
#if (PRINT_WMA_STATE)
EN_WMA_STATE enPreWmaState  = STATE_WMA_NONE;
#endif

static EN_RET       enWmaRetVal;

static FileEntry *m_pWmaFileEntry;

static U32 u32WmaFileHandle = INVALID_DATA_STREAM_HDL;
static WMA_PLAY_STATUS enWmaPlayStatus = WMA_STATUS_STOP;
static BOOLEAN m_bCheckFftoEnd = FALSE;

static U32 u32WmaFileBytesLeft;
static En_DVB_decSystemType enCurrentDecSystem;
static BOOLEAN bReloadDsp;
static EN_WMA_SPEED enWmaPlaySpeed = EN_WMA_SPEED_X1;
static ST_WMA_INFO stWmaInfo;
static U32 u32WmaShowTimer;
static U32 u32WmaTimeOutDefault = WMA_SHOW_TIMEOUT; // ms
static U32 u32FfRewTimer;
static BOOLEAN bProcessFfRew = FALSE;
static U32 u32WmaHeaderByteSent;
static EN_WMA_ERRCODE _enWMA_ErrCode = E_WMA_ERR_NONE;
static BOOLEAN bStop_After_FB_To_Begin_Wma = FALSE;

//-------------------------------------------------------------------------------------------------
// Local Function Prototypes
//-------------------------------------------------------------------------------------------------
static BOOLEAN _MApp_WMA_CheckSupportedAudio(En_DVB_decSystemType enDecSystem);

//-------------------------------------------------------------------------------------------------
// Function Implementation
//-------------------------------------------------------------------------------------------------
extern void MApp_UiMenu_DrawMenuPage(void);

#if ENABLE_FILE_BM

#define MIDFS_SIZE  (WMA_INFO_READ_LEN)

typedef struct
{
    //U8 bInit;
    U8 *pu8MidFSCurrentBuffer;
    U32 u32StartAddr;
    U32 u32EndAddr;
    U32 u32UserSeekAddr;
    U32 u32FileLen;
} ST_MID_FS_INFO;

static ST_MID_FS_INFO stMidFSInfo;

void msAPI_DataStreamIO_MID_FS_RegisterBuffer(U8 *pu8MidFSBuf)
{
    stMidFSInfo.pu8MidFSCurrentBuffer = pu8MidFSBuf;
    stMidFSInfo.u32StartAddr = 0;
    stMidFSInfo.u32EndAddr = 0;
    stMidFSInfo.u32UserSeekAddr = 0;
}

void msAPI_DataStreamIO_MID_FS_SetFileLen(U32 u32FileLen)
{
    stMidFSInfo.u32FileLen = u32FileLen;
}

U32 msAPI_DataStreamIO_MID_FS_Read(U32 u32Hdl, U32 u32Length, U32 *pu32DestAddr)
{
    U32 u32RemainLen = u32Length;
    U32 u32InBufferNum = 0;

#if WMA_MEASURE
    U32 u32IOtime1 = 0;
    U32 u32IOtime2 = 0;

#endif

    if ( (u32Length > MIDFS_SIZE) || (stMidFSInfo.u32UserSeekAddr > stMidFSInfo.u32FileLen) )
    {
        return u32RemainLen;
    }
    if ( ( stMidFSInfo.u32StartAddr <= stMidFSInfo.u32UserSeekAddr ) && ( stMidFSInfo.u32EndAddr >= (stMidFSInfo.u32UserSeekAddr + u32Length) ) )
    {
        //in cache memory, just return pointer
        *pu32DestAddr = (U32)(stMidFSInfo.pu8MidFSCurrentBuffer + stMidFSInfo.u32UserSeekAddr - stMidFSInfo.u32StartAddr);
        u32RemainLen = 0;
        stMidFSInfo.u32UserSeekAddr += u32Length;

#if WMA_MEASURE
        if(bwmaCollect)
        {
            u32TotalRead_1++;
        }
#endif
    }
    else
    {
        if ( (stMidFSInfo.u32UserSeekAddr <= stMidFSInfo.u32EndAddr) && ( stMidFSInfo.u32StartAddr <= stMidFSInfo.u32UserSeekAddr ) && ( stMidFSInfo.u32EndAddr < (stMidFSInfo.u32UserSeekAddr + u32Length) ) )
        {
            //Move the last part to the beginning of the buffer
            U32 i;
            U32 u32PrevReadNum = (stMidFSInfo.u32EndAddr - stMidFSInfo.u32UserSeekAddr);

            U32 u32TrueReadNum = MIDFS_SIZE - u32PrevReadNum;
#if WMA_MEASURE
            if(bwmaCollect)
            {
                u32IOtime1 = msAPI_Timer_GetTime0();
            }
#endif

            for(i=0; i<u32PrevReadNum; i++)
            {
                *(stMidFSInfo.pu8MidFSCurrentBuffer+i) = *(stMidFSInfo.pu8MidFSCurrentBuffer+stMidFSInfo.u32UserSeekAddr-stMidFSInfo.u32StartAddr+i);
            }
#if WMA_MEASURE
            if(bwmaCollect)
            {
                u32IOtime2 = msAPI_Timer_GetTime0();
            }
#endif
            //always try to make buffer as full as possible
            U32 u32TempRemainLen = msAPI_DataStreamIO_Read(u32Hdl, (void *)(_VA2PA((U32)stMidFSInfo.pu8MidFSCurrentBuffer+u32PrevReadNum)), u32TrueReadNum);
            u32InBufferNum = u32TrueReadNum-u32TempRemainLen+u32PrevReadNum;   //total read number

#if WMA_MEASURE
            if(bwmaCollect)
            {
                u32TotalRead_2++;
                u32TotalReadByte_2 = u32TotalReadByte_2 + u32InBufferNum;
                u32TotalPrevReadNum_2 = u32TotalPrevReadNum_2 + u32PrevReadNum;
                printf("for loop time: %lu   count:%lu\n", u32IOtime2- u32IOtime1,u32PrevReadNum);
                u32TotalLooptime = u32TotalLooptime + u32IOtime2- u32IOtime1;
            }
#endif
        }
        else
        {
            //not in cache memory, reload from file
            msAPI_Steam_Seek(u32WmaFileHandle, stMidFSInfo.u32UserSeekAddr);
            //always try to make buffer as full as possible
            U32 u32TempRemainLen = msAPI_DataStreamIO_Read(u32Hdl, (void *)(_VA2PA((U32)stMidFSInfo.pu8MidFSCurrentBuffer)), MIDFS_SIZE);
            u32InBufferNum = MIDFS_SIZE-u32TempRemainLen;

#if WMA_MEASURE
            if(bwmaCollect)
            {
                u32TotalRead_3++;
                u32TotalReadByte_3 = u32TotalReadByte_3 + u32InBufferNum;
            }
#endif
        }

            // user ask for u32Length byte, but we read MIDFS_SIZE bytes actually
            // revise u32RemainLen to the number as if we read only u32Length byte
            // or it may return a value even larger than u32RemainLen
            if(u32InBufferNum>=u32Length)
            {
                u32RemainLen = 0;    //total read>=u32Length, return 0 because we have all what user requested
            }
            else
            {
                u32RemainLen = u32Length - u32InBufferNum;	//u32Length - (total read)
            }

            stMidFSInfo.u32StartAddr = stMidFSInfo.u32UserSeekAddr;
            stMidFSInfo.u32EndAddr = stMidFSInfo.u32UserSeekAddr+u32InBufferNum;
            stMidFSInfo.u32UserSeekAddr = stMidFSInfo.u32StartAddr + u32Length - u32RemainLen;
            *pu32DestAddr = (U32)(stMidFSInfo.pu8MidFSCurrentBuffer);
        }

        return u32RemainLen;
}

void msAPI_DataStreamIO_MID_FS_Seek(U32 u32Index)
{
    stMidFSInfo.u32UserSeekAddr = u32Index;
}

U32 msAPI_DataStreamIO_MID_FS_Tell(void)
{
    return stMidFSInfo.u32UserSeekAddr;
}
#endif

#if ENABLE_ASF_PARSING

#if ENABLE_WMA_INDEX_TABLE
static U32 MApp_WMA_ParsingASFPacketSCR(U32 dwReqAddress,ST_WMA_INFO *pWmaInfo)
{
    U8 *pu8Data = (U8 *)dwReqAddress;
    //U32 *pu32WMAPayloadAddr = (U32 *)(_PA2VA(u32WMAPayloadAddr));
    U32 i=0;
    //U32 u32SCR=0;

    if(pu8Data[i]&0x80)
    {
        U8 u8ErrorCLengthType;

        pWmaInfo->u32ErrorCLength=pu8Data[i]&0x0F;
        //Error Correction Length Type
        u8ErrorCLengthType =  (pu8Data[i]&0x60)>>5;
        //spec:The value of this u32ErrorCLength is valid only if the value of the Error Correction Length Type field is 00.
        //If the Error Correction Length Type field is 00, this field represents the size of the Error Correction
        //Data field, in bytes.  The value of this field should be set to 0010. If the Error Correction Length Type
        //field is different than 00, this field shall be set to 0000.
        //add simple check ,skip some error packets
        if((u8ErrorCLengthType != 0 && pWmaInfo->u32ErrorCLength != 0) ||
                (u8ErrorCLengthType == 0 && pWmaInfo->u32ErrorCLength != 2))
        {
            WMA_DBG(printf("packet error. skip it.\n"));
            return 0;
        }
        i++;  //Jump Error Correction Flags
        i += pWmaInfo->u32ErrorCLength;
    }

    pWmaInfo->bIsMultiPayloads = pu8Data[i]&0x01;
    pWmaInfo->u8SequenceLType = (pu8Data[i]&0x06)>>1;
    pWmaInfo->u8PaddingLType = (pu8Data[i]&0x18)>>3;
    pWmaInfo->u8PacketLType = (pu8Data[i]&0x60)>>5;
    i++;  //Jump Length Type Flags

    pWmaInfo->u8ReplicatedDLType = pu8Data[i]&0x03;
    pWmaInfo->u8OffseIMOLType = (pu8Data[i]&0x0C)>>2;
    pWmaInfo->u8MediaONLType = (pu8Data[i]&0x30)>>4;
    i++;  //Jump Property Flags

    if(pWmaInfo->u8PacketLType)
    {
        i += (1 << (pWmaInfo->u8PacketLType-1));
    }
    if(pWmaInfo->u8SequenceLType)
    {
        i += (1 << (pWmaInfo->u8SequenceLType-1));
    }
    if(pWmaInfo->u8PaddingLType)
    {
        //memcpy(&pWmaInfo->u32PaddingLength, &pu8Data[i], (1 << (pWmaInfo->u8PaddingLType-1)));
        i += (1 << (pWmaInfo->u8PaddingLType-1));
    }
    else
    {
        //pWmaInfo->u32PaddingLength = 0;
    }

    //memcpy(&u32SCR, &pu8Data[i], 4);
    //pu32WMAPayloadAddr[u32IndexNum] = u32SCR;
    i += 4;    //Jump Send Time

    i += 2;    //Jump Duration

    //------Payload data----------//
    if(pWmaInfo->bIsMultiPayloads)
    {
        pWmaInfo->u8NumPayloads = pu8Data[i]&0x3F;
        pWmaInfo->u8PayloadLType = (pu8Data[i]&0xC0)>>6;
        i += 1;    //Jump Payload Flags
        if ( pWmaInfo->u32TotalPayloads == 0 )
            pWmaInfo->u8FirstNumPayloads = pWmaInfo->u8NumPayloads;
        pWmaInfo->u32TotalPayloads += pWmaInfo->u8NumPayloads;
    }
    else
    {
        pWmaInfo->u8NumPayloads = 1;
        pWmaInfo->u8FirstNumPayloads = 1;
        pWmaInfo->u32TotalPayloads ++;
    }

    return i;
}
#endif

static U32 MApp_WMA_ParsingASFPacketHeader(U32 dwReqAddress,ST_WMA_INFO *pWmaInfo)
{
    U8 *pu8Data = (U8 *)dwReqAddress;
    U32 i=0;

    if(pu8Data[i]&0x80)
    {
        U8 u8ErrorCLengthType;

        pWmaInfo->u32ErrorCLength=pu8Data[i]&0x0F;
        //Error Correction Length Type
        u8ErrorCLengthType =  (pu8Data[i]&0x60)>>5;
        //spec:The value of this u32ErrorCLength is valid only if the value of the Error Correction Length Type field is 00.
        //If the Error Correction Length Type field is 00, this field represents the size of the Error Correction
        //Data field, in bytes.  The value of this field should be set to 0010. If the Error Correction Length Type
        //field is different than 00, this field shall be set to 0000.
        //add simple check ,skip some error packets
        if((u8ErrorCLengthType != 0 && pWmaInfo->u32ErrorCLength != 0) ||
            (u8ErrorCLengthType == 0 && pWmaInfo->u32ErrorCLength != 2))
        {
            WMA_DBG(printf("packet error. skip it.\n"));
            return 0;
        }
        i++;  //Jump Error Correction Flags
        i += pWmaInfo->u32ErrorCLength;
    }

    pWmaInfo->bIsMultiPayloads = pu8Data[i]&0x01;
    pWmaInfo->u8SequenceLType = (pu8Data[i]&0x06)>>1;
    pWmaInfo->u8PaddingLType = (pu8Data[i]&0x18)>>3;
    pWmaInfo->u8PacketLType = (pu8Data[i]&0x60)>>5;
    i++;  //Jump Length Type Flags

    pWmaInfo->u8ReplicatedDLType = pu8Data[i]&0x03;
    pWmaInfo->u8OffseIMOLType = (pu8Data[i]&0x0C)>>2;
    pWmaInfo->u8MediaONLType = (pu8Data[i]&0x30)>>4;
    pWmaInfo->u8StreamNLType = (pu8Data[i]&0xC0)>>6;
    i++;  //Jump Property Flags

    if(pWmaInfo->u8PacketLType)
    {
        i += (1 << (pWmaInfo->u8PacketLType-1));
    }
    if(pWmaInfo->u8SequenceLType)
    {
        i += (1 << (pWmaInfo->u8SequenceLType-1));
    }
    if(pWmaInfo->u8PaddingLType)
    {
        i += (1 << (pWmaInfo->u8PaddingLType-1));
    }

    i += 4;    //Jump Send Time
    i += 2;    //Jump Duration

    //------Payload data----------//
    if(pWmaInfo->bIsMultiPayloads)
    {
        pWmaInfo->u8NumPayloads = pu8Data[i]&0x3F;
        pWmaInfo->u8PayloadLType = (pu8Data[i]&0xC0)>>6;
        i += 1;    //Jump Payload Flags
    }
    else
    {
        pWmaInfo->u8NumPayloads = 1;
    }

    return i;
}

#if ENABLE_WMA_INDEX_TABLE
static U32 MApp_WMA_ParsingASFPayloadPTime(U32 dwReqAddress,ST_WMA_INFO *pWmaInfo, U32 u32IndexNum, U32 u32PayloadPosInFile)
{
    U8 *pu8Data = (U8 *)dwReqAddress;
    ST_WMA_INDEX_TABLE *pstWMAIndexTable = (ST_WMA_INDEX_TABLE *)(_PA2VA(u32WMAPayloadTableAddr));
    U32 i=0;

    if ( u32IndexNum > WMA_INDEX_TABLE_MAX_NUM )
        u32IndexNum = WMA_INDEX_TABLE_MAX_NUM;

    stWmaInfo.u16CurrentStreamId = pu8Data[i] & 0x7F;
    i += 1;    //Jump Stream Number

    if(pWmaInfo->u8MediaONLType)
    {
        i += (1 << (pWmaInfo->u8MediaONLType-1));
    }

    if(pWmaInfo->u8OffseIMOLType)
    {
        i += (1 << (pWmaInfo->u8OffseIMOLType-1));
    }

    if(pWmaInfo->u8ReplicatedDLType)
    {
        pWmaInfo->u32ReplicatedDLength = 0;
        memcpy(&pWmaInfo->u32ReplicatedDLength,&pu8Data[i],(1 << (pWmaInfo->u8ReplicatedDLType-1)));
        i += (1 << (pWmaInfo->u8ReplicatedDLType-1));
    }

    if(pWmaInfo->u32ReplicatedDLength == 0x1)  //Compressed payload data
    {
        U32 u32PresentationTime;

        if(pWmaInfo->u8ReplicatedDLType)
            i -= (1 << (pWmaInfo->u8ReplicatedDLType-1));
        if(pWmaInfo->u8OffseIMOLType)           //pWmaInfo->u8OffseIMOLType must not be set to 0x00 in this case
            i -= (1 << (pWmaInfo->u8OffseIMOLType-1));

        memcpy(&u32PresentationTime, &pu8Data[i], (1 << (pWmaInfo->u8OffseIMOLType-1)));

        if(u32PresentationTime <=  pWmaInfo->u32PreRoll)
        {
        if(u32IndexNum > 0 )
        {
            //set to previous payload time so the whole table will be in ascending order
            WMA_DBG(printf("set payload %lu to previous payload time: %lu\n",u32IndexNum,pstWMAIndexTable[u32IndexNum-1].u32WMAPayloadPTime));
            pstWMAIndexTable[u32IndexNum].u32WMAPayloadPTime =	pstWMAIndexTable[u32IndexNum-1].u32WMAPayloadPTime;
        }
        else
        {
            pstWMAIndexTable[u32IndexNum].u32WMAPayloadPTime = 0;
        }

        }
        else
        {
            pstWMAIndexTable[u32IndexNum].u32WMAPayloadPTime = u32PresentationTime - pWmaInfo->u32PreRoll;

            if( u32IndexNum > 0)
            {
                if(pstWMAIndexTable[u32IndexNum].u32WMAPayloadPTime < pstWMAIndexTable[u32IndexNum-1].u32WMAPayloadPTime)
                {
                    WMA_DBG(printf("set payload %lu to previous payload time: %lu\n",u32IndexNum,pstWMAIndexTable[u32IndexNum-1].u32WMAPayloadPTime));
                    pstWMAIndexTable[u32IndexNum].u32WMAPayloadPTime =  pstWMAIndexTable[u32IndexNum-1].u32WMAPayloadPTime;
                }
            }
        }

        pstWMAIndexTable[u32IndexNum].u32WMAPayloadFilePos = u32PayloadPosInFile;

        if(pWmaInfo->u8OffseIMOLType)
            i += (1 << (pWmaInfo->u8OffseIMOLType-1));

        if(pWmaInfo->u8ReplicatedDLType)
            i += (1 << (pWmaInfo->u8ReplicatedDLType-1));

        //memcpy(&pWmaInfo->u8PresentationTimeDelta,&pu8Data[i],1);
        //This value was ignored if there is only one sub-payload
        i++;  //Jump Presentation Time Delta

        //Sub-Payload Data
        memcpy(&pWmaInfo->u32PayloadLength,&pu8Data[i],1);
        i++; //Jump Sub-Payload Data Length
        //for single payload, compressed payload data case, how about multiple payloads case? It seems the same with single payload case
        //Another calculation formula is below formula
        //pWmaInfo->u32PayloadLength = pWmaInfo->u32PacketSize - pWmaInfo->u16PacketOffset - i - pWmaInfo->u32PaddingLength;
    }
    else  //non-compressed payload data
    {
        U32 u32PresentationTime;

        memcpy(&pWmaInfo->u32PayloadLength,&pu8Data[i],4);
        memcpy(&u32PresentationTime, &pu8Data[i+4], 4);

        if(u32PresentationTime <=  pWmaInfo->u32PreRoll)
        {
            if(u32IndexNum > 0 )
            {
                //set to previos payload time so the whole table will be in ascending order
                WMA_DBG(printf("set payload %lu to previous payload time: %lu\n",u32IndexNum,pstWMAIndexTable[u32IndexNum-1].u32WMAPayloadPTime));
                pstWMAIndexTable[u32IndexNum].u32WMAPayloadPTime =  pstWMAIndexTable[u32IndexNum-1].u32WMAPayloadPTime;
            }
            else
            {
                pstWMAIndexTable[u32IndexNum].u32WMAPayloadPTime = 0;
            }
        }
        else
        {
            pstWMAIndexTable[u32IndexNum].u32WMAPayloadPTime = u32PresentationTime - pWmaInfo->u32PreRoll;

            if( u32IndexNum > 0)
            {
                if(pstWMAIndexTable[u32IndexNum].u32WMAPayloadPTime < pstWMAIndexTable[u32IndexNum-1].u32WMAPayloadPTime)
                {
                    WMA_DBG(printf("set payload %lu to previous payload time: %lu\n",u32IndexNum,pstWMAIndexTable[u32IndexNum-1].u32WMAPayloadPTime));
                    pstWMAIndexTable[u32IndexNum].u32WMAPayloadPTime =  pstWMAIndexTable[u32IndexNum-1].u32WMAPayloadPTime;
                }
            }
        }

        pstWMAIndexTable[u32IndexNum].u32WMAPayloadFilePos = u32PayloadPosInFile;

        i += pWmaInfo->u32ReplicatedDLength;

        if(pWmaInfo->bIsMultiPayloads)
        {
            if(pWmaInfo->u8PayloadLType)
            {
                memcpy(&pWmaInfo->u32PayloadLength,&pu8Data[i],(1 << (pWmaInfo->u8PayloadLType-1)));
                i += (1 << (pWmaInfo->u8PayloadLType-1));  //Jump Payload Length
            }
        }
    }

    if(pWmaInfo->u32PayloadLength > pWmaInfo->u32PacketSize)
    {
        WMA_INFO(printf("pWmaInfo->u32PayloadLength: %ld is abnormal. pWmaInfo->u32PacketSize:%lu \n", pWmaInfo->u32PayloadLength,pWmaInfo->u32PacketSize));
        return 0xFFFFFFFF;
    }

    return i;
}
#endif

static U32 MApp_WMA_ParsingASFPayloadHeader(U32 dwReqAddress,ST_WMA_INFO *pWmaInfo)
{
    U8 *pu8Data = (U8 *)dwReqAddress;
    U32 i=0;

    stWmaInfo.u16CurrentStreamId = pu8Data[i] & 0x7F;
    i += 1;    //Jump Stream Number

    if(pWmaInfo->u8MediaONLType)
    {
        i += (1 << (pWmaInfo->u8MediaONLType-1));
    }
    if(pWmaInfo->u8OffseIMOLType)
    {
        i += (1 << (pWmaInfo->u8OffseIMOLType-1));
    }
    if(pWmaInfo->u8ReplicatedDLType)
    {
        pWmaInfo->u32ReplicatedDLength = 0;
        memcpy(&pWmaInfo->u32ReplicatedDLength,&pu8Data[i],(1 << (pWmaInfo->u8ReplicatedDLType-1)));
        i += (1 << (pWmaInfo->u8ReplicatedDLType-1));
    }

    if(pWmaInfo->u32ReplicatedDLength == 0x1)  //Compressed payload data
    {
        memcpy(&pWmaInfo->u8PresentationTimeDelta,&pu8Data[i],1);
        i++;  //Jump Presentation Time Delta

        //Sub-Payload Data
        memcpy(&pWmaInfo->u32PayloadLength,&pu8Data[i],1);
        i++; //Jump Sub-Payload Data Length
    }
    else  //non-compressed payload data
    {
        memcpy(&pWmaInfo->u32PayloadLength,&pu8Data[i],4);
        i += pWmaInfo->u32ReplicatedDLength;

        if(pWmaInfo->bIsMultiPayloads)
        {
            if(pWmaInfo->u8PayloadLType)
            {
                memcpy(&pWmaInfo->u32PayloadLength,&pu8Data[i],(1 << (pWmaInfo->u8PayloadLType-1)));
                i += (1 << (pWmaInfo->u8PayloadLType-1));  //Jump Payload Length
            }
        }
    }

    if(pWmaInfo->u32PayloadLength > pWmaInfo->u32PacketSize)
    {
        WMA_INFO(printf("pWmaInfo->u32PayloadLength: %ld is abnormal.\n", pWmaInfo->u32PayloadLength));
        return 0xFFFFFFFF;
    }

    return i;
}

#if 0
static U32 MApp_WMA_AddASFPacketForDSP(U32 dwReqAddress,U32 u32ReqBytes)
{
    U32 u32OriReqBytes = u32ReqBytes;
    U32 u32SeekOffset = 0, u32HeaderOffset=0;
    U32 u32readLeft = 0;
    U32 u32WriteSize = 0;
    U8 u8HeaderLeftSize;
    U8 u8RetryCount = 0;

    while(u32ReqBytes>0)
    {
        if(stWmaInfo.u16FormatTag != CODEC_FORMAT_MP3)
        {
            u8HeaderLeftSize = _pu8ASFPayloadHeader[WMA_ASF_PACKET_HEADER_SIZE];
            if(u8HeaderLeftSize > 0)
            {
                //msAPI_FS_MIU_Copy((U32)&_pu8ASFPayloadHeader[WMA_ASF_PACKET_HEADER_SIZE-u8HeaderLeftSize], dwReqAddress, u8HeaderLeftSize);
                memcpy((U8 *)_PA2VA(dwReqAddress), &_pu8ASFPayloadHeader[WMA_ASF_PACKET_HEADER_SIZE-u8HeaderLeftSize], u8HeaderLeftSize);
                dwReqAddress += u8HeaderLeftSize;
                u32ReqBytes -= u8HeaderLeftSize;
                _pu8ASFPayloadHeader[WMA_ASF_PACKET_HEADER_SIZE]=0;
            }
        }

        if(m_u32BufLeftSize > 0)
        {
            u32SeekOffset = (U32)msAPI_FCtrl_FileTell(u32WmaFileHandle);
            if(m_u32BufLeftSize <= u32ReqBytes)
            {
                u32WriteSize = m_u32BufLeftSize;
            }
            else
            {
                u32WriteSize = u32ReqBytes;
            }
            memcpy((void*)_PA2VA(dwReqAddress) ,(void*)_PA2VA(((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (WMA_INFO_READ_ADR | MIU_INTERVAL) : (WMA_INFO_READ_ADR))+m_u32BufReadSize-m_u32BufLeftSize) ,u32WriteSize);
            _u32PayloadWriteLeft -= u32WriteSize;
            u32ReqBytes -= u32WriteSize;
            dwReqAddress += u32WriteSize;
            m_u32BufLeftSize -= u32WriteSize;
        }

        if(_u32PayloadWriteLeft!=0)
        {
            if(_u32PayloadWriteLeft>u32ReqBytes)
            {
                u32WriteSize = u32ReqBytes;
            }
            else
            {
                u32WriteSize = _u32PayloadWriteLeft;
            }


    #if ENABLE_WMDRMPD
            if(stWmaInfo.bContentEObjectFound)  //DRM Content
            {
                //msAPI_FS_MIU_Copy(((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (WMA_INFO_READ_ADR | MIU_INTERVAL) : (WMA_INFO_READ_ADR))+(stWmaInfo.u32PayloadLength-_u32PayloadWriteLeft),dwReqAddress, u32WriteSize);
                memcpy((U8 *)_PA2VA((void *)dwReqAddress), (U8 *)_PA2VA((void *)(((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (WMA_INFO_READ_ADR | MIU_INTERVAL) : (WMA_INFO_READ_ADR))+(stWmaInfo.u32PayloadLength-_u32PayloadWriteLeft))), u32WriteSize);

                u32readLeft = 0;
            }
            else
    #endif
            {
                u32readLeft = msAPI_DataStreamIO_Read(u32WmaFileHandle, (void*)dwReqAddress, u32WriteSize);
            }

            //Re-read for networking
            u8RetryCount = 0;
            while((u32readLeft != 0)  && (u8RetryCount<3))
            {
                u8RetryCount++;

                u32WriteSize -= u32readLeft;
                _u32PayloadWriteLeft -= u32WriteSize;
                u32ReqBytes -= u32WriteSize;
                dwReqAddress += u32WriteSize;

                u32WriteSize = u32readLeft;
                u32readLeft = msAPI_DataStreamIO_Read(u32WmaFileHandle, (void*)dwReqAddress, u32WriteSize);
            }

            if(u32readLeft!=0)
            {
                WMA_DBG(printf("u32readLeft!=0\n"));
                __ASSERT(0);
            }
            _u32PayloadWriteLeft -= u32WriteSize;
            u32ReqBytes -= u32WriteSize;
            dwReqAddress += u32WriteSize;
        }
        else
        {
            do
            {
                u32HeaderOffset = m_u32BufReadSize = 0;
                if(_u32CurrentPayload%stWmaInfo.u8NumPayloads == 0) //Handle packet
                {
                    U32 u32SkipErrorPacketTimes = 0;

                    do
                    {
                        WMA_DBG(printf("_u32CurrentPacket:%lu ",_u32CurrentPacket));

                        u32SeekOffset = stWmaInfo.u32HeaderSize+(_u32CurrentPacket*stWmaInfo.u32PacketSize);
                        msAPI_Steam_Seek(u32WmaFileHandle, u32SeekOffset);
                        m_u32BufReadSize = 0;

                        //re-calculate packet header
                        if(0x100 == msAPI_DataStreamIO_Read(u32WmaFileHandle, (void*)((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (WMA_INFO_READ_ADR | MIU_INTERVAL) : (WMA_INFO_READ_ADR)), 0x100))
                        {
                            WMA_DBG(printf("No data to read.\n"));
                            return u32OriReqBytes;;
                        }
                        m_u32BufReadSize += 0x100;
                        stWmaInfo.u16PacketOffset = MApp_WMA_ParsingASFPacketHeader(_PA2VA(((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (WMA_INFO_READ_ADR | MIU_INTERVAL) : (WMA_INFO_READ_ADR))),&stWmaInfo);
                        WMA_DBG(printf("u16PacketOffset:0x%x\n",stWmaInfo.u16PacketOffset));
                        _u32CurrentPacket++;
                        if(stWmaInfo.u16PacketOffset == 0)
                        {
                            u32SkipErrorPacketTimes++;
                            if(u32SkipErrorPacketTimes >= 3)
                            {
                                WMA_DBG(printf("Too much error , exit play.\n"));
                                return u32OriReqBytes;;
                            }
                        }
                    }while(stWmaInfo.u16PacketOffset == 0); //skip error packet
                    u32HeaderOffset += stWmaInfo.u16PacketOffset;
                    _u32CurrentPayload=0;
                }

                WMA_DBG(printf("_u32CurrentPayload:%lu u16PayloadOffset:0x%x u8NumPayloads:%bu\n\n",_u32CurrentPayload,stWmaInfo.u16PayloadOffset,stWmaInfo.u8NumPayloads));
                WMA_INFO(printf("u16PacketOffset=0x%x u16PayloadOffset:0x%x\n",stWmaInfo.u16PacketOffset,stWmaInfo.u16PayloadOffset));
                WMA_INFO(printf("u32PacketSize=0x%lx u32PayloadLength:0x%lx \n",stWmaInfo.u32PacketSize,stWmaInfo.u32PayloadLength));
                WMA_INFO(printf("u32TotalPacket:0x%lx u8NumPayloads=0x%bx \n",stWmaInfo.u32TotalPacket,stWmaInfo.u8NumPayloads));

                //re-calculate payload header , payload size.
                msAPI_DataStreamIO_Read(u32WmaFileHandle, (void*)(((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (WMA_INFO_READ_ADR | MIU_INTERVAL) : (WMA_INFO_READ_ADR))+m_u32BufReadSize), 0x100);
                m_u32BufReadSize += 0x100;
                stWmaInfo.u16PayloadOffset = MApp_WMA_ParsingASFPayloadHeader(_PA2VA(((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (WMA_INFO_READ_ADR | MIU_INTERVAL) : (WMA_INFO_READ_ADR))+u32HeaderOffset),&stWmaInfo);
                if(stWmaInfo.u16PayloadOffset == (U16)0xFFFFFFFF)
                {
                    WMA_INFO(printf("payload error! exit play.\n"));
                    return u32OriReqBytes;
                }
                u32HeaderOffset += stWmaInfo.u16PayloadOffset;
                if(stWmaInfo.u16CurrentStreamId != stWmaInfo.u16StreamID[stWmaInfo.u8CurrentStreamIndex])
                {
                    WMA_INFO(printf("skip stream %d payload\n", stWmaInfo.u16CurrentStreamId));

                    u32SeekOffset = msAPI_DataStreamIO_Tell(u32WmaFileHandle);
                    u32SeekOffset += stWmaInfo.u32PayloadLength-(m_u32BufReadSize-u32HeaderOffset);
                    msAPI_Steam_Seek(u32WmaFileHandle, u32SeekOffset);
                }

                _u32CurrentPayload++;

                if(_u32CurrentPacket>= stWmaInfo.u32TotalPacket && _u32CurrentPayload>=stWmaInfo.u8NumPayloads)
                {
                    MS_DEBUG_MSG(printf("Packet-payload end\n"));
                    return u32OriReqBytes;
                }
            }while(stWmaInfo.u16CurrentStreamId != stWmaInfo.u16StreamID[stWmaInfo.u8CurrentStreamIndex]);

            _u32PayloadWriteLeft = stWmaInfo.u32PayloadLength;
            m_u32BufLeftSize = m_u32BufReadSize - u32HeaderOffset;

    #if ENABLE_WMDRMPD
            if(stWmaInfo.bContentEObjectFound)  //DRM Content
            {
                msAPI_DataStreamIO_Read(u32WmaFileHandle, (void*)((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (WMA_INFO_READ_ADR | MIU_INTERVAL) : (WMA_INFO_READ_ADR)), _u32PayloadWriteLeft);
                MApp_WMDRMPD_Decrypt((void *)((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (WMA_INFO_READ_ADR | MIU_INTERVAL) : (WMA_INFO_READ_ADR)),(int)_u32PayloadWriteLeft);
            }

        #if 0  //For Debug
            if(_u32CurrentPacket==1 & _u32CurrentPayload==1)
            {
                U32 j;
                U8 *pu8Data;
                pu8Data = (U8 *)((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (WMA_INFO_READ_ADR | MIU_INTERVAL) : (WMA_INFO_READ_ADR));
                printf("Payload[0] Data:\n");
                for(j=0;j<_u32PayloadWriteLeft;j++)
                {
                    if((j%0x10) == 0)
                    {
                        printf("\n");
                    }
                    printf("%02bX ",pu8Data[j]);
                }
            }
        #endif
    #endif

            if(stWmaInfo.u16FormatTag != CODEC_FORMAT_MP3)
            {
                //----Payload header for DSP----//
                _pu8ASFPayloadHeader[0]=0x02;
                _pu8ASFPayloadHeader[1]=0x80;
                _pu8ASFPayloadHeader[2]=0xFD;
                _pu8ASFPayloadHeader[3]=0x7F;
                memcpy(&_pu8ASFPayloadHeader[4],&stWmaInfo.u32PayloadLength,4);
                memset(&_pu8ASFPayloadHeader[8],0,8);
                _pu8ASFPayloadHeader[16]=0;   //Left size
                //---------------------------//

                if(u32ReqBytes >= WMA_ASF_PACKET_HEADER_SIZE)
                {
                    //msAPI_FS_MIU_Copy((U32)&_pu8ASFPayloadHeader, dwReqAddress, WMA_ASF_PACKET_HEADER_SIZE);
                    memcpy((U8 *)_PA2VA(dwReqAddress), _pu8ASFPayloadHeader, WMA_ASF_PACKET_HEADER_SIZE);

                    _pu8ASFPayloadHeader[WMA_ASF_PACKET_HEADER_SIZE]=0;
                    dwReqAddress += WMA_ASF_PACKET_HEADER_SIZE;
                    u32ReqBytes -= WMA_ASF_PACKET_HEADER_SIZE;
                }
                else //u32ReqBytes < WMA_ASF_PACKET_HEADER_SIZE
                {
                    //msAPI_FS_MIU_Copy((U32)&_pu8ASFPayloadHeader, dwReqAddress, u32ReqBytes);
                    memcpy((U8 *)_PA2VA(dwReqAddress), _pu8ASFPayloadHeader, u32ReqBytes);

                    _pu8ASFPayloadHeader[WMA_ASF_PACKET_HEADER_SIZE]=WMA_ASF_PACKET_HEADER_SIZE-u32ReqBytes;
                    dwReqAddress += u32ReqBytes;
                    u32ReqBytes = 0;
                }
            }
        }

    }
    return u32readLeft;
}
#else
static U32 MApp_WMA_AddASFPacketForDSP(U32 dwReqAddress,U32 u32ReqBytes)
{
    U32 u32OriReqBytes = u32ReqBytes;
    U32 u32SeekOffset = 0;
    U32 u32readLeft = 0;
    U32 u32WriteSize = 0;
    U8 u8HeaderLeftSize;
    U8 u8RetryCount = 0;

    while(u32ReqBytes>0)
    {
        if(stWmaInfo.u16FormatTag != CODEC_FORMAT_MP3)
        {
            u8HeaderLeftSize = _pu8ASFPayloadHeader[WMA_ASF_PACKET_HEADER_SIZE];
            if(u8HeaderLeftSize > 0)
            {
                //msAPI_FS_MIU_Copy((U32)&_pu8ASFPayloadHeader[WMA_ASF_PACKET_HEADER_SIZE-u8HeaderLeftSize], dwReqAddress, u8HeaderLeftSize);
                memcpy((U8 *)_PA2VA(dwReqAddress), &_pu8ASFPayloadHeader[WMA_ASF_PACKET_HEADER_SIZE-u8HeaderLeftSize], u8HeaderLeftSize);
#if ENABLE_WMA_DSP_DEBUG
                msAPI_FCtrl_FileWrite(u8FileHandle0, (U32)&_pu8ASFPayloadHeader[WMA_ASF_PACKET_HEADER_SIZE-u8HeaderLeftSize], u8HeaderLeftSize);
#endif
                dwReqAddress += u8HeaderLeftSize;
                u32ReqBytes -= u8HeaderLeftSize;
                _pu8ASFPayloadHeader[WMA_ASF_PACKET_HEADER_SIZE]=0;
            }
        }

        if(_u32PayloadWriteLeft!=0)
        {
            if(_u32PayloadWriteLeft>u32ReqBytes)
            {
                u32WriteSize = u32ReqBytes;
            }
            else
            {
                u32WriteSize = _u32PayloadWriteLeft;
            }


    #if ENABLE_WMDRMPD
            if(stWmaInfo.bContentEObjectFound)  //DRM Content
            {
                //msAPI_FS_MIU_Copy(((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (WMA_INFO_READ_ADR | MIU_INTERVAL) : (WMA_INFO_READ_ADR))+(stWmaInfo.u32PayloadLength-_u32PayloadWriteLeft),dwReqAddress, u32WriteSize);
                memcpy((U8 *)_PA2VA((void *)dwReqAddress), (U8 *)_PA2VA((void *)(((WMA_INFO_READ_MEMORY_TYPE & MIU1) ? (WMA_INFO_READ_ADR | MIU_INTERVAL) : (WMA_INFO_READ_ADR))+(stWmaInfo.u32PayloadLength-_u32PayloadWriteLeft))), u32WriteSize);
#if ENABLE_WMA_DSP_DEBUG
                msAPI_FCtrl_FileWrite(u8FileHandle0, _PA2VA((void *)(((WMA_INFO_READ_MEMORY_TYPE & MIU1) ? (WMA_INFO_READ_ADR | MIU_INTERVAL) : (WMA_INFO_READ_ADR))+(stWmaInfo.u32PayloadLength-_u32PayloadWriteLeft))), u32WriteSize);
#endif


                u32readLeft = 0;
            }
            else
    #endif
            {
#if ENABLE_FILE_BM
                U32 u32DestAddr = 0, u32TempAddr = dwReqAddress;
                U32 u32SrcSize = u32WriteSize, u32TempSize = u32WriteSize;

                while(u32SrcSize > 0)
                {
                    if ( u32SrcSize > MIDFS_SIZE )
                        u32TempSize = MIDFS_SIZE;
                    else
                        u32TempSize = u32SrcSize;

                    u32readLeft = msAPI_DataStreamIO_MID_FS_Read(u32WmaFileHandle, u32TempSize, &u32DestAddr);
                    memcpy((U8 *)_PA2VA(u32TempAddr), (U8 *)u32DestAddr, u32TempSize);
#if ENABLE_WMA_DSP_DEBUG
                    msAPI_FCtrl_FileWrite(u8FileHandle0, u32DestAddr, u32TempSize);
#endif

                    u32SrcSize -= u32TempSize;
                    u32TempAddr += u32TempSize;
                }
#else
                u32readLeft = msAPI_DataStreamIO_Read(u32WmaFileHandle, (void*)dwReqAddress, u32WriteSize);
#if ENABLE_WMA_DSP_DEBUG
                msAPI_FCtrl_FileWrite(u8FileHandle0, dwReqAddress, u32WriteSize);
#endif
#endif
            }

            //Re-read for networking
            u8RetryCount = 0;
            while((u32readLeft != 0)  && (u8RetryCount<3))
            {
                u8RetryCount++;

                u32WriteSize -= u32readLeft;
                _u32PayloadWriteLeft -= u32WriteSize;
                u32ReqBytes -= u32WriteSize;
                dwReqAddress += u32WriteSize;

                u32WriteSize = u32readLeft;

#if ENABLE_FILE_BM
                U32 u32DestAddr = 0, u32TempAddr = dwReqAddress;
                U32 u32SrcSize = u32WriteSize, u32TempSize = u32WriteSize;

                while(u32SrcSize > 0)
                {
                    if ( u32SrcSize > MIDFS_SIZE )
                        u32TempSize = MIDFS_SIZE;
                    else
                        u32TempSize = u32SrcSize;

                    u32readLeft = msAPI_DataStreamIO_MID_FS_Read(u32WmaFileHandle, u32TempSize, &u32DestAddr);
                    memcpy((U8 *)_PA2VA(u32TempAddr), (U8 *)u32DestAddr, u32TempSize);
#if ENABLE_WMA_DSP_DEBUG
                    msAPI_FCtrl_FileWrite(u8FileHandle0, u32DestAddr, u32TempSize);
#endif

                    u32SrcSize -= u32TempSize;
                    u32TempAddr += u32TempSize;
                }
#else
                u32readLeft = msAPI_DataStreamIO_Read(u32WmaFileHandle, (void*)dwReqAddress, u32WriteSize);
#if ENABLE_WMA_DSP_DEBUG
                msAPI_FCtrl_FileWrite(u8FileHandle0, dwReqAddress, u32WriteSize);
#endif
#endif
            }

            if(u32readLeft!=0)
            {
                WMA_DBG(printf("u32readLeft!=0\n"));
                __ASSERT(0);
            }
            _u32PayloadWriteLeft -= u32WriteSize;
            u32ReqBytes -= u32WriteSize;
            dwReqAddress += u32WriteSize;
        }
        else
        {
#if ENABLE_FILE_BM
            U8 *pu8Data = NULL;
            U32 u32DestAddr = 0;
#endif
            do
            {
                if(_u32CurrentPayload%stWmaInfo.u8NumPayloads == 0) //Handle packet
                {
                    U32 u32SkipErrorPacketTimes = 0;

                    do
                    {
                        WMA_DBG(printf("_u32CurrentPacket:%lu ",_u32CurrentPacket));

                        u32SeekOffset = stWmaInfo.u32HeaderSize+(_u32CurrentPacket*stWmaInfo.u32PacketSize);
#if ENABLE_FILE_BM
                        msAPI_DataStreamIO_MID_FS_Seek(u32SeekOffset);

                        if ( 0x100 == msAPI_DataStreamIO_MID_FS_Read(u32WmaFileHandle, 0x100, &u32DestAddr) )
                        {
                            //packet header maximum size: 0x100 byte
                            WMA_DBG(printf("No data to read.\n"));
                            return u32OriReqBytes;
                        }

                        pu8Data = (U8 *)u32DestAddr;

                        stWmaInfo.u16PacketOffset = MApp_WMA_ParsingASFPacketHeader((U32)pu8Data, &stWmaInfo);
#else
                        msAPI_Steam_Seek(u32WmaFileHandle, u32SeekOffset);

                        //re-calculate packet header
                        if(0x100 == msAPI_DataStreamIO_Read(u32WmaFileHandle, (void*)((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (MP3_INFO_READ_ADR | MIU_INTERVAL) : (MP3_INFO_READ_ADR)), 0x100))
                        {
                            //packet header maximum size: 0x100 byte
                            WMA_DBG(printf("No data to read.\n"));
                            return u32OriReqBytes;;
                        }
                        stWmaInfo.u16PacketOffset = MApp_WMA_ParsingASFPacketHeader(_PA2VA(((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (MP3_INFO_READ_ADR | MIU_INTERVAL) : (MP3_INFO_READ_ADR))),&stWmaInfo);
#endif

                        WMA_DBG(printf("u16PacketOffset:0x%x\n",stWmaInfo.u16PacketOffset));
                        _u32CurrentPacket++;
                        if(stWmaInfo.u16PacketOffset == 0)
                        {
                            u32SkipErrorPacketTimes++;
                            if(u32SkipErrorPacketTimes >= 3)
                            {
                                WMA_DBG(printf("Too much error , exit play.\n"));
                                return u32OriReqBytes;
                            }
                        }
                    }while(stWmaInfo.u16PacketOffset == 0); //skip error packet
                    u32SeekOffset += stWmaInfo.u16PacketOffset;
#if ENABLE_FILE_BM
                    msAPI_DataStreamIO_MID_FS_Seek(u32SeekOffset);
#else
                    WMA_DBG(printf("%d %s Seek: %d\n", __LINE__, __FUNCTION__, u32SeekOffset));
                    msAPI_Steam_Seek(u32WmaFileHandle, u32SeekOffset);
#endif
                    _u32CurrentPayload=0;
                }

                WMA_DBG(printf("_u32CurrentPayload:%lu u16PayloadOffset:0x%x u8NumPayloads:%bu\n\n",_u32CurrentPayload,stWmaInfo.u16PayloadOffset,stWmaInfo.u8NumPayloads));
                WMA_INFO(printf("u16PacketOffset=0x%x u16PayloadOffset:0x%x\n",stWmaInfo.u16PacketOffset,stWmaInfo.u16PayloadOffset));
                WMA_INFO(printf("u32PacketSize=0x%lx u32PayloadLength:0x%lx \n",stWmaInfo.u32PacketSize,stWmaInfo.u32PayloadLength));
                WMA_INFO(printf("u32TotalPacket:0x%lx u8NumPayloads=0x%bx \n",stWmaInfo.u32TotalPacket,stWmaInfo.u8NumPayloads));

#if ENABLE_FILE_BM
                u32SeekOffset = msAPI_DataStreamIO_MID_FS_Tell();
                msAPI_DataStreamIO_MID_FS_Read(u32WmaFileHandle, 0x100, &u32DestAddr);  //payload header maximum size: 0x100
                pu8Data = (U8 *)u32DestAddr;
                stWmaInfo.u16PayloadOffset = MApp_WMA_ParsingASFPayloadHeader((U32)pu8Data, &stWmaInfo);
#else
                u32SeekOffset = msAPI_DataStreamIO_Tell(u32WmaFileHandle);
                //re-calculate payload header , payload size.
                msAPI_DataStreamIO_Read(u32WmaFileHandle, (void*)((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (MP3_INFO_READ_ADR | MIU_INTERVAL) : (MP3_INFO_READ_ADR)), 0x100);  //payload header maximum size: 0x100
                stWmaInfo.u16PayloadOffset = MApp_WMA_ParsingASFPayloadHeader(_PA2VA(((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (MP3_INFO_READ_ADR | MIU_INTERVAL) : (MP3_INFO_READ_ADR))),&stWmaInfo);
#endif
                if(stWmaInfo.u16PayloadOffset == (U16)0xFFFFFFFF)
                {
                    WMA_INFO(printf("payload error! exit play.\n"));
                    return u32OriReqBytes;
                }
                u32SeekOffset += stWmaInfo.u16PayloadOffset;
                if(stWmaInfo.u16CurrentStreamId != stWmaInfo.u16StreamID[stWmaInfo.u8CurrentStreamIndex])
                {
                    WMA_INFO(printf("skip stream %d payload\n", stWmaInfo.u16CurrentStreamId));
                    u32SeekOffset += stWmaInfo.u32PayloadLength;
                }

#if ENABLE_FILE_BM
                msAPI_DataStreamIO_MID_FS_Seek(u32SeekOffset);
#else
                msAPI_Steam_Seek(u32WmaFileHandle, u32SeekOffset);
#endif

                _u32CurrentPayload++;

                if(_u32CurrentPacket>= stWmaInfo.u32TotalPacket && _u32CurrentPayload>=stWmaInfo.u8NumPayloads)
                {
                    MS_DEBUG_MSG(printf("Packet-payload end\n"));
                    return u32OriReqBytes;
                }
            }while(stWmaInfo.u16CurrentStreamId != stWmaInfo.u16StreamID[stWmaInfo.u8CurrentStreamIndex]);


            _u32PayloadWriteLeft = stWmaInfo.u32PayloadLength;

    #if ENABLE_WMDRMPD
            if(stWmaInfo.bContentEObjectFound)  //DRM Content
            {
                msAPI_DataStreamIO_Read(u32WmaFileHandle, (void*)((WMA_INFO_READ_MEMORY_TYPE & MIU1) ? (WMA_INFO_READ_ADR | MIU_INTERVAL) : (WMA_INFO_READ_ADR)), _u32PayloadWriteLeft);
                MApp_WMDRMPD_Decrypt((void *)((WMA_INFO_READ_MEMORY_TYPE & MIU1) ? (WMA_INFO_READ_ADR | MIU_INTERVAL) : (WMA_INFO_READ_ADR)),(int)_u32PayloadWriteLeft);
            }

        #if 0  //For Debug
            if(_u32CurrentPacket==1 & _u32CurrentPayload==1)
            {
                U32 j;
                U8 *pu8Data;
                pu8Data = (U8 *)((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (WMA_INFO_READ_ADR | MIU_INTERVAL) : (WMA_INFO_READ_ADR));
                printf("Payload[0] Data:\n");
                for(j=0;j<_u32PayloadWriteLeft;j++)
                {
                    if((j%0x10) == 0)
                    {
                        printf("\n");
                    }
                    printf("%02bX ",pu8Data[j]);
                }
            }
        #endif
    #endif

            if(stWmaInfo.u16FormatTag != CODEC_FORMAT_MP3)
            {
                //----Payload header for DSP----//
                _pu8ASFPayloadHeader[0]=0x02;
                _pu8ASFPayloadHeader[1]=0x80;
                _pu8ASFPayloadHeader[2]=0xFD;
                _pu8ASFPayloadHeader[3]=0x7F;
                memcpy(&_pu8ASFPayloadHeader[4],&stWmaInfo.u32PayloadLength,4);
                memset(&_pu8ASFPayloadHeader[8],0,8);
                _pu8ASFPayloadHeader[16]=0;   //Left size
                //---------------------------//

                if(u32ReqBytes >= WMA_ASF_PACKET_HEADER_SIZE)
                {
                    //msAPI_FS_MIU_Copy((U32)&_pu8ASFPayloadHeader, dwReqAddress, WMA_ASF_PACKET_HEADER_SIZE);
                    memcpy((U8 *)_PA2VA(dwReqAddress), _pu8ASFPayloadHeader, WMA_ASF_PACKET_HEADER_SIZE);
#if ENABLE_WMA_DSP_DEBUG
                    msAPI_FCtrl_FileWrite(u8FileHandle0, (U32)_pu8ASFPayloadHeader, WMA_ASF_PACKET_HEADER_SIZE);
#endif

                    _pu8ASFPayloadHeader[WMA_ASF_PACKET_HEADER_SIZE]=0;
                    dwReqAddress += WMA_ASF_PACKET_HEADER_SIZE;
                    u32ReqBytes -= WMA_ASF_PACKET_HEADER_SIZE;
                }
                else //u32ReqBytes < WMA_ASF_PACKET_HEADER_SIZE
                {
                    //msAPI_FS_MIU_Copy((U32)&_pu8ASFPayloadHeader, dwReqAddress, u32ReqBytes);
                    memcpy((U8 *)_PA2VA(dwReqAddress), _pu8ASFPayloadHeader, u32ReqBytes);
#if ENABLE_WMA_DSP_DEBUG
                    msAPI_FCtrl_FileWrite(u8FileHandle0, (U32)_pu8ASFPayloadHeader, u32ReqBytes);
#endif

                    _pu8ASFPayloadHeader[WMA_ASF_PACKET_HEADER_SIZE]=WMA_ASF_PACKET_HEADER_SIZE-u32ReqBytes;
                    dwReqAddress += u32ReqBytes;
                    u32ReqBytes = 0;
                }
            }
        }

    }
    return u32readLeft;
}
#endif
#endif

#if ENABLE_WMDRMPD
static BOOLEAN MApp_WMA_WMDRMPD_GetLicense(void)
{
    U32 u32Addr = (U32)((WMA_INFO_READ_MEMORY_TYPE & MIU1) ? (WMA_INFO_READ_ADR | MIU_INTERVAL) : (WMA_INFO_READ_ADR));
    U32 u32Size = 0;
    U8 retry = 0;
    U8 *pu8Data = (U8 *)_PA2VA((void*)u32Addr);
    BOOLEAN bRet = FALSE;

    u32WmaFileHandle = msAPI_DataStreamIO_Open(m_pWmaFileEntry, OPEN_MODE_FOR_READ,E_DATA_STREAM_TYPE_MUSIC);
    if(u32WmaFileHandle == INVALID_DATA_STREAM_HDL)
    {
        WMA_DBG(printf("MApp_WMA_CollectInfo: Open file failed\n"));
        return FALSE;
    }

    msAPI_Steam_Seek(u32WmaFileHandle, stWmaInfo.u32ExContentEObjectLocation);
    msAPI_DataStreamIO_Read(u32WmaFileHandle, (void*)((WMA_INFO_READ_MEMORY_TYPE & MIU1) ? (WMA_INFO_READ_ADR | MIU_INTERVAL) : (WMA_INFO_READ_ADR)), WMA_INFO_READ_LEN);

    if(pu8Data[0]==0xFF && pu8Data[1]==0xFE)  //Check Unicode
    {
        u32Addr += 2;
        u32Size = (stWmaInfo.u32ExContentEObjectSize - 2);
    }

    if(MApp_WMDRMPD_Initialize(E_WMDRMPD_MEDIA_TYPE_WMA))
    {
        switch(MApp_WMDRMPD_GetLicense((void *)u32Addr, (int)u32Size))
        {
            case E_WMDRMPD_LICENSE_OK:
                bRet = TRUE;
                break;
            case E_WMDRMPD_LICENSE_RETRY:
                retry = 1;
                break;
            case E_WMDRMPD_LICENSE_INVALID:
                bRet = FALSE;
                break;
        }
    }
    else
    {
        bRet = FALSE;
    }

    if (retry)
    {
        int sizeXML, sizeUrl;
        char url[128];
        void *pXML = NULL;
        void *pUrl = (void *)&url[0];
        //U32 u32DrmTimout = 0;

        // Send LicenseChallengeReq to network module
        MApp_WMDRMPD_QueryLicenseChallenge(&sizeXML, &sizeUrl);
        MApp_WMDRMPD_GetLicenseChallenge(pXML, pUrl, sizeXML, sizeUrl);

#if 0
        if (MDrv_WaitMailBoxReady())
        {
            MailBoxPara.u8CmdClass      = MB_CLASS_VDPLAYER_FS;
            MailBoxPara.u8CmdIdx        = MB_VDPLAYER_CHECK_DRM_AUTHORIZATION;
            MailBoxPara.ParamCnt        = 0;
            MailBoxPara.CMDType         = MB_CMD_TYPE_DEFAULT;
            MDrv_SendMailBoxMsg();
        }

        // Waiting for Ack from network module
        u32DrmTimout = msAPI_Timer_GetTime0();
        bDrmAuthorization = FALSE;

        do
        {
            MApp_VDPlayer_MailBoxHandler();
        } while ((m_eVDPlayerAckFlags & E_ACKFLG_WAIT_CHECK_DRM_AUTHORIZATION) &&
                    (msAPI_Timer_DiffTimeFromNow(u32DrmTimout) < VDPLAYER_COPROCESSOR_CHECK_TIMEOUT));
#endif

        MApp_WMDRMPD_SetLicenseResponse(pXML, sizeXML);
        switch (MApp_WMDRMPD_GetLicense((void *)pXML, sizeXML))
        {
            case E_WMDRMPD_LICENSE_OK:
                bRet = TRUE;
                break;
            case E_WMDRMPD_LICENSE_RETRY:
                bRet = FALSE;
                break;
            case E_WMDRMPD_LICENSE_INVALID:
                bRet = FALSE;
                break;
        }
    }

    msAPI_DataStreamIO_Close(u32WmaFileHandle);
    u32WmaFileHandle = INVALID_DATA_STREAM_HDL;

    return bRet;
}

#endif

static BOOLEAN MApp_WMA_TimeOutCheck(void)
{
    static EN_WMA_STATE _enWmaPrevState = STATE_WMA_NONE;
    static U32 u32PreFilePosition = -1; // set to -1 is ok because all we need is a value that is not quite possible
    static U32 u32TimeMarker = 0;
    static U16 u16PreDspCounter = 0;

    U32 u32FilePosition, u32TimeOut = WMA_TIME_OUT_THRESHOLD;
    BOOLEAN bCheck = FALSE;

    u32FilePosition = msAPI_DataStreamIO_Tell(u32WmaFileHandle);

    if ((_enWmaPrevState != enWmaState) || (enWmaPlayStatus == WMA_STATUS_PAUSE)||(enWmaPlayStatus == WMA_STATUS_SCAN))
    {
        // at least state has changed
        u32TimeMarker = msAPI_Timer_GetTime0();
        _enWmaPrevState = enWmaState;
        u32PreFilePosition = -1;
    }
    else
    {
        if (enWmaState != STATE_WMA_WAIT) // it's ok to be in idle state and waiting for key event
        {
            if((enWmaState == STATE_WMA_WAIT_DECODE_DONE)
            && (msAPI_WMA_GetEsMEMCnt() != u16PreDspCounter))
            {
                //when last audio data push to DSP we need wait audio dsp play finish
                //we check DSP counter is continues decrease or not
                u16PreDspCounter = msAPI_WMA_GetEsMEMCnt();
                u32TimeMarker = msAPI_Timer_GetTime0();
            }
            else if (u32FilePosition != u32PreFilePosition) // here, check if file position still the same for many times
            {
                u32PreFilePosition = u32FilePosition;
                u32TimeMarker = msAPI_Timer_GetTime0();
            }
            else if (msAPI_Music_GetPCMBufferSize2(stWmaInfo.u32BitRate,stWmaInfo.u32SampleRate) != 0)
            {
                //For low bitrate WMA file. DSP is decoding.
                u32TimeMarker = msAPI_Timer_GetTime0();
            }
            else
            {
                bCheck = TRUE;
            }
        }
    }

    if (bCheck == TRUE)
    {
        if (u32FilePosition == msAPI_DataStreamIO_Length(u32WmaFileHandle))
        {
            u32TimeOut = WMA_FILE_END_TIME_OUT_THRESHOLD;
        }

        if (msAPI_Timer_GetTime0() - u32TimeMarker > u32TimeOut)
        {
            //printf("hit, s: %bu, ps: %bu, t: %lu, pt: %lu, fp: %lu, pfp: %lu\n", enMp3State, _enMp3PrevState, msAPI_Timer_GetTime0(), u32TimeMarker, msAPI_DataStreamIO_Tell(u8Mp3FileHandle), u32PreFilePosition);
            return TRUE;
        }
    }

    return FALSE;
}

void MApp_WMA_SetFileEntry(FileEntry *pEntry)
{
    m_pWmaFileEntry = pEntry;
}

static BOOLEAN MApp_WMA_CollectInfo(ST_WMA_INFO *pWmaInfo)
{
    U32 u32Index = 0;
    U32 i,j;

#if WMA_MEASURE
    bwmaCollect=TRUE;
    U32 u32collStart = 0;
    u32collStart = msAPI_Timer_GetTime0();
#endif

#if ENABLE_WMA_DSP_DEBUG
    u8FileHandle0=NULL;
    U16 u16FileName0[13] = {'d', 's', 'p', 'd', 'e', 'b', 'u', 'g', '.', 'w', 'm', 'a',0};

    u8FileHandle0 = MApp_FileBrowser_OpenNewFileForWrite(u16FileName0, 14);
#endif

#if ENABLE_FILE_BM
    U8 *pu8Data = (U8 *)_PA2VA(((WMA_INFO_READ_MEMORY_TYPE & MIU1) ? (WMA_INFO_READ_ADR | MIU_INTERVAL) : (WMA_INFO_READ_ADR)));
#else
    U8 *pu8Data = (U8 *)_PA2VA(((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (MP3_INFO_READ_ADR | MIU_INTERVAL) : (MP3_INFO_READ_ADR)));
#endif

#if ENABLE_FILE_BM
    U8 *pu8MidFSBuf = NULL;
    U32 u32DestAddr;
#endif

    // Parsing Title, Author information
    memset(pWmaInfo,0,sizeof(ST_WMA_INFO));

    u32WmaFileHandle = msAPI_DataStreamIO_Open(m_pWmaFileEntry, OPEN_MODE_FOR_READ,E_DATA_STREAM_TYPE_MUSIC2);
    if(u32WmaFileHandle == INVALID_DATA_STREAM_HDL)
    {
        WMA_DBG(printf("MApp_WMA_CollectInfo: Open file failed\n"));
        _enWMA_ErrCode = E_WMA_ERR_DATA_OPERATION_FAILURE;
        return FALSE;
    }

    pWmaInfo->u32FileSize = msAPI_DataStreamIO_Length(u32WmaFileHandle);
    stWmaInfo.u8StreamNumber = 1;

#if ENABLE_FILE_BM
    pu8MidFSBuf = pu8Data;
    msAPI_DataStreamIO_MID_FS_RegisterBuffer(pu8MidFSBuf);
    msAPI_DataStreamIO_MID_FS_SetFileLen(pWmaInfo->u32FileSize);

    msAPI_DataStreamIO_MID_FS_Seek(0);
    msAPI_DataStreamIO_MID_FS_Read(u32WmaFileHandle, WMA_HEADER_READ_LEN, &u32DestAddr);
    pu8Data = (U8 *)u32DestAddr;
#else
    msAPI_DataStreamIO_Read(u32WmaFileHandle, (void*)((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (MP3_INFO_READ_ADR | MIU_INTERVAL) : (MP3_INFO_READ_ADR)), MP3_INFO_READ_LEN);
#endif

    for(i=0;i<4080;i++)    //4096-16
    {
        if((pu8Data[i]==0x30)&&(pu8Data[i+1]==0x26)&&(pu8Data[i+2]==0xB2)&&(pu8Data[i+3]==0x75)&&
            (pu8Data[i+4]==0x8E)&&(pu8Data[i+5]==0x66)&&(pu8Data[i+6]==0xCF)&&(pu8Data[i+7]==0x11)&&
            (pu8Data[i+8]==0xA6)&&(pu8Data[i+9]==0xD9)&&(pu8Data[i+10]==0x00)&&(pu8Data[i+11]==0xAA)&&
            (pu8Data[i+12]==0x00)&&(pu8Data[i+13]==0x62)&&(pu8Data[i+14]==0xCE)&&(pu8Data[i+15]==0x6C)
        )
        {
            pWmaInfo->bHeaderFound = TRUE;
            memcpy(&pWmaInfo->u32HeaderSize,&pu8Data[i+16],4);
            break;
        }
    }
    WMA_INFO(printf("pWmaInfo->u32HeaderSize = 0x%lx\n",pWmaInfo->u32HeaderSize));

    if(pWmaInfo->bHeaderFound)
    {
        i=0;
        for(u32Index=0;u32Index<(pWmaInfo->u32HeaderSize+0x100);u32Index++,i++)     //u32HeaderSize + 0x100 to parsing Data Object
        {
            if((i+0x100) > (WMA_HEADER_READ_LEN-1))
            {
            #if ENABLE_FILE_BM
                msAPI_DataStreamIO_MID_FS_Seek(u32Index);
                msAPI_DataStreamIO_MID_FS_Read(u32WmaFileHandle, WMA_HEADER_READ_LEN, &u32DestAddr);
                pu8Data = (U8 *)u32DestAddr;
            #else
                msAPI_Steam_Seek(u32WmaFileHandle, u32Index);
                msAPI_DataStreamIO_Read(u32WmaFileHandle, (void*)((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (MP3_INFO_READ_ADR | MIU_INTERVAL) : (MP3_INFO_READ_ADR)), MP3_INFO_READ_LEN);
            #endif
                i = 0;
            }


            //Check all Stream Properties Object

            //ASF_Stream_Properties_Object guid:B7DC0791-A9B7-11CF-8EE6-00C00C205365
            //ASF_Audio_Media guid:F8699E40-5B4D-11CF-A8FD-00805F5C442B
            //ASF_Video_Media guid:BC19EFC0-5B4D-11CF-A8FD-00805F5C442B
            if((pu8Data[i]==0x91)&&(pu8Data[i+1]==0x07)&&(pu8Data[i+2]==0xDC)&&(pu8Data[i+3]==0xB7)&&
                (pu8Data[i+4]==0xB7)&&(pu8Data[i+5]==0xA9)&&(pu8Data[i+6]==0xCF)&&(pu8Data[i+7]==0x11)&&
                (pu8Data[i+8]==0x8E)&&(pu8Data[i+9]==0xE6)&&(pu8Data[i+10]==0x00)&&(pu8Data[i+11]==0xC0)&&
                (pu8Data[i+12]==0x0C)&&(pu8Data[i+13]==0x20)&&(pu8Data[i+14]==0x53)&&(pu8Data[i+15]==0x65))
            {

                if((pu8Data[i+24] == 0xC0) && (pu8Data[i+25] == 0xEF) && (pu8Data[i+26] == 0x19) && (pu8Data[i +27] == 0xBC) &&
                (pu8Data[i+28] == 0x4D) && (pu8Data[i+29] == 0x5B) && (pu8Data[i+30] == 0xCF) && (pu8Data[i+31] == 0x11) &&
                (pu8Data[i+32] == 0xA8) && (pu8Data[i+33] == 0xFD) && (pu8Data[i+34] == 0x00) && (pu8Data[i+35] == 0x80) &&
                (pu8Data[i+36] == 0x5F) && (pu8Data[i+37] == 0x5C) && (pu8Data[i+38] == 0x44) && (pu8Data[i+39] == 0x2B))
                {
                    WMA_DBG(printf("Contain Video Stream, don't play this file\n"));
                    return FALSE;
                }
                else if((pu8Data[i+24] == 0x40) && (pu8Data[i+25] == 0x9E) && (pu8Data[i+26] == 0x69) && (pu8Data[i +27] == 0xF8) &&
                (pu8Data[i+28] == 0x4D) && (pu8Data[i+29] == 0x5B) && (pu8Data[i+30] == 0xCF) && (pu8Data[i+31] == 0x11) &&
                (pu8Data[i+32] == 0xA8) && (pu8Data[i+33] == 0xFD) && (pu8Data[i+34] == 0x00) && (pu8Data[i+35] == 0x80) &&
                (pu8Data[i+36] == 0x5F) && (pu8Data[i+37] == 0x5C) && (pu8Data[i+38] == 0x44) && (pu8Data[i+39] == 0x2B))
                {


                    pWmaInfo->bStreamFound = TRUE;
                    memcpy(&pWmaInfo->u16FormatTag,&pu8Data[i+0x4E],2);               //Check "WMA" or "WMA Pro"
                    memcpy(&pWmaInfo->u16Channels,&pu8Data[i+0x50],2);
                    memcpy(&pWmaInfo->u32SampleRate,&pu8Data[i+0x52],4);
                    memcpy(&pWmaInfo->u32ByteRate,&pu8Data[i+0x56],4);
                    pWmaInfo->u32BitRate = pWmaInfo->u32ByteRate*8; //ByteRate

                    memcpy(&pWmaInfo->u16BlockAlign,&pu8Data[i+0x5A],2);
                    memcpy(&pWmaInfo->u16BitsSample,&pu8Data[i+0x5C],2);
                    memcpy(&pWmaInfo->u16StreamID[0], &pu8Data[i+0x48], 2);
                    pWmaInfo->u8CurrentStreamIndex = 0;

                    if(pWmaInfo->u16FormatTag == 0x160)
                    {
                        pWmaInfo->u8Version = 1;
                        memcpy(&pWmaInfo->u16Encopt,&pu8Data[i+0x5C+6],2);
                    }
                    else if(pWmaInfo->u16FormatTag == 0x161)
                    {
                        pWmaInfo->u8Version = 2;
                        memcpy(&pWmaInfo->u16Encopt,&pu8Data[i+0x5C+8],2);
                    }
                    else if(pWmaInfo->u16FormatTag == CODEC_FORMAT_WMA_PRO || pWmaInfo->u16FormatTag == CODEC_FORMAT_MP3)
                    {
                        pWmaInfo->u8Version = 3;
                        memcpy(&pWmaInfo->u32ChannelMask,&pu8Data[i+0x5C+6],4);
                        memcpy(&pWmaInfo->u16Encopt,&pu8Data[i+0x5C+18],2);
                    }
                    else
                    {
                        //support WMA Standard v1 (0x160), WMA Standard v2 (0x161), WMA Pro (0x162),
                        //not support WMA Lossless (0x163), WMA Voice (0xA).
                        _enWMA_ErrCode = E_WMA_ERR_NOT_SUPPORT_CODECID;
                        return FALSE;
                    }

                    if(pWmaInfo->u16Channels > 6)
                    {
                        //Don't support >6 channels .
                        _enWMA_ErrCode = E_WMA_ERR_NOT_SUPPORT_CHANNEL_NUM;
                        return FALSE;
                    }

                    WMA_INFO(printf("pWmaInfo->u16FormatTag = 0x%x\n",pWmaInfo->u16FormatTag));
                    WMA_INFO(printf("pWmaInfo->u16Channels = %u\n",pWmaInfo->u16Channels));
                    WMA_INFO(printf("pWmaInfo->u32SampleRate = 0x%lx\n",pWmaInfo->u32SampleRate));
                    WMA_INFO(printf("pWmaInfo->u32ByteRate = 0x%lx\n",pWmaInfo->u32ByteRate));
                    WMA_INFO(printf("pWmaInfo->u32BitRate = 0x%lx\n",pWmaInfo->u32BitRate));
                    WMA_INFO(printf("pWmaInfo->u16BlockAlign = 0x%x\n",pWmaInfo->u16BlockAlign));
                    WMA_INFO(printf("pWmaInfo->u16BitsSample = 0x%x\n",pWmaInfo->u16BitsSample));
                    WMA_INFO(printf("pWmaInfo->u8Version = %bu\n",pWmaInfo->u8Version));
                    WMA_INFO(printf("pWmaInfo->u32ChannelMask = 0x%lx\n",pWmaInfo->u32ChannelMask));
                    WMA_INFO(printf("pWmaInfo->u16Encopt = 0x%x\n",pWmaInfo->u16Encopt));
                }
            }


            if(!pWmaInfo->bContentFound)
            {
                if((pu8Data[i]==0x33)&&(pu8Data[i+1]==0x26)&&(pu8Data[i+2]==0xB2)&&(pu8Data[i+3]==0x75)&&
                    (pu8Data[i+4]==0x8E)&&(pu8Data[i+5]==0x66)&&(pu8Data[i+6]==0xCF)&&(pu8Data[i+7]==0x11)&&
                    (pu8Data[i+8]==0xA6)&&(pu8Data[i+9]==0xD9)&&(pu8Data[i+10]==0x00)&&(pu8Data[i+11]==0xAA)&&
                    (pu8Data[i+12]==0x00)&&(pu8Data[i+13]==0x62)&&(pu8Data[i+14]==0xCE)&&(pu8Data[i+15]==0x6C)
                )
                {
                    pWmaInfo->bContentFound = TRUE;
                    memcpy(&pWmaInfo->u16TitleLength,&pu8Data[i+0x18],2);
                    //Must reserve 4 bytes for "\0\0"
                    if(pWmaInfo->u16TitleLength > WMA_MAX_TITLE_LENGTH - 4)
                    {
                        pWmaInfo->u16TitleLength = WMA_MAX_TITLE_LENGTH - 4;
                    }
                    memcpy(&pWmaInfo->u16AuthorLength,&pu8Data[i+0x1a],2);
                    //Must reserve 4 bytes for "\0\0"
                    if(pWmaInfo->u16AuthorLength > WMA_MAX_AUTHOR_LENGTH - 4)
                    {
                        pWmaInfo->u16AuthorLength = WMA_MAX_AUTHOR_LENGTH - 4;
                    }
                    WMA_INFO(printf("u16TitleLength = %u\n",pWmaInfo->u16TitleLength));
                    WMA_INFO(printf("u16AuthorLength = %u\n",pWmaInfo->u16AuthorLength));
                    if((i+pWmaInfo->u16TitleLength+pWmaInfo->u16AuthorLength+0x23) > (WMA_HEADER_READ_LEN-1))
                    {
                    #if ENABLE_FILE_BM
                        msAPI_DataStreamIO_MID_FS_Seek(u32Index);
                        msAPI_DataStreamIO_MID_FS_Read(u32WmaFileHandle, WMA_HEADER_READ_LEN, &u32DestAddr);
                        pu8Data = (U8 *)u32DestAddr;
                    #else
                        msAPI_Steam_Seek(u32WmaFileHandle, u32Index);
                        msAPI_DataStreamIO_Read(u32WmaFileHandle, (void*)((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (MP3_INFO_READ_ADR | MIU_INTERVAL) : (MP3_INFO_READ_ADR)), MP3_INFO_READ_LEN);
                    #endif
                        i = 0;
                    }
                    pWmaInfo->u8Title[0] = 0x01;   //ZUI use this bit to check unicode or not.
                    for(j=0;j<pWmaInfo->u16TitleLength;j=j+2)
                    {
                        pWmaInfo->u8Title[j+1] = pu8Data[i+j+0x22];
                        pWmaInfo->u8Title[j+2] = pu8Data[i+j+0x23];
                    }

                    pWmaInfo->u8Author[0] = 0x01; //ZUI use this bit to check unicode or not.
                    for(j=0;j<pWmaInfo->u16AuthorLength;j=j+2)
                    {
                        pWmaInfo->u8Author[j+1] = pu8Data[i+j+0x22+pWmaInfo->u16TitleLength];
                        pWmaInfo->u8Author[j+2] = pu8Data[i+j+0x23+pWmaInfo->u16TitleLength];
                    }
                    //printf("pWmaInfo->u8Title = %s\n",pWmaInfo->u8Title);
                }
            }

            if(!pWmaInfo->bExContentFound) // it is optional
            {

                if((pu8Data[i]==0x40)&&(pu8Data[i+1]==0xA4)&&(pu8Data[i+2]==0xD0)&&(pu8Data[i+3]==0xD2)&&
                    (pu8Data[i+4]==0x07)&&(pu8Data[i+5]==0xE3)&&(pu8Data[i+6]==0xD2)&&(pu8Data[i+7]==0x11)&&
                    (pu8Data[i+8]==0x97)&&(pu8Data[i+9]==0xF0)&&(pu8Data[i+10]==0x00)&&(pu8Data[i+11]==0xA0)&&
                    (pu8Data[i+12]==0xC9)&&(pu8Data[i+13]==0x5E)&&(pu8Data[i+14]==0xA8)&&(pu8Data[i+15]==0x50)
                )
                {
                    //Extended Content Description Object
                    //--------------------------------------
                    //GUID: 16 byte
                    //Object size: 8 byte
                    //Content discriptor count: 2 byte
                    //--------------------------------------

                    U16 u16ContentCount;
                    U16 u16Index;
                    U32 u32DataOffset = 0;

                    U8 *pu8DataTmp;

                    WMA_INFO(printf("found Extended Content Description Object\n"));

                    memcpy(&u16ContentCount, &pu8Data[i+0x18],2);  //0x18 = 24 = GUID+Object size

                    pWmaInfo->bExContentFound = TRUE;

                    if(u16ContentCount == 0)
                    {
                        continue;
                    }

                    u32Index =  u32Index+26;  //GUID+Object size+Content discriptor count=26
#if ENABLE_FILE_BM
                    msAPI_DataStreamIO_MID_FS_Seek(u32Index);
                    msAPI_DataStreamIO_MID_FS_Read(u32WmaFileHandle, WMA_HEADER_READ_LEN, &u32DestAddr);
                    pu8Data = (U8 *)u32DestAddr;
#else
                    msAPI_Steam_Seek(u32WmaFileHandle, u32Index);
                    msAPI_DataStreamIO_Read(u32WmaFileHandle, (void*)((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (MP3_INFO_READ_ADR | MIU_INTERVAL) : (MP3_INFO_READ_ADR)), MP3_INFO_READ_LEN);
#endif
                    u32DataOffset = 0;

                    for(u16Index = 0; u16Index < u16ContentCount; ++u16Index)
                    {

                        //Descriptor Structure
                        //-------------------------------------
                        //Descriptor name length: 2 byte
                        //Descriptor name: varies
                        //Descriptor value data type: 2 byte
                        //Descriptor value length: 2 byte
                        //Descriptor value: varies
                        //--------------------------------------

                        U16 u16DesNameLen;
                        U16 u16DataType;
                        U16 u16DataLen;

                        U32 u32tmp;

                        const U8 u8WmaYear[16] = {0x57,0x00,0x4D,0x00,0x2F,0x00,0x59,0x00,0x65,0x00,0x61,0x00,0x72,0x00,0x00,0x00};  //extended content discription name: WM/Year
                        const U8 u8AlbumTitle[28] = {'W',0x00,'M',0x00,'/',0x00,'A',0x00,'l',0x00,'b',0x00,'u',0x00,'m',0x00,'T',0x00,'i',0x00,'t',0x00,'l',0x00,'e',0x00,0x00,0x00}; //extended content description name: WM/AlbumTitle

                        if((u32DataOffset+0x100) > (WMA_HEADER_READ_LEN-1))    //256 byte buffer space for safety
                        {
                            u32Index = u32Index + u32DataOffset;
#if ENABLE_FILE_BM
                            msAPI_DataStreamIO_MID_FS_Seek(u32Index);
                            msAPI_DataStreamIO_MID_FS_Read(u32WmaFileHandle, WMA_HEADER_READ_LEN, &u32DestAddr);
                            pu8Data = (U8 *)u32DestAddr;
#else
                            msAPI_Steam_Seek(u32WmaFileHandle, u32Index);
                            msAPI_DataStreamIO_Read(u32WmaFileHandle, (void*)((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (MP3_INFO_READ_ADR | MIU_INTERVAL) : (MP3_INFO_READ_ADR)), MP3_INFO_READ_LEN);

#endif
                            u32DataOffset = 0;
                        }


                        memcpy(&u16DesNameLen, &pu8Data[u32DataOffset],2);



                        if((u32DataOffset+2+u16DesNameLen+0x100) > (WMA_HEADER_READ_LEN-1))  //256 byte buffer space for safety
                        {
                            u32Index = u32Index + u32DataOffset+2+u16DesNameLen;
#if ENABLE_FILE_BM
                            msAPI_DataStreamIO_MID_FS_Seek(u32Index);
                            msAPI_DataStreamIO_MID_FS_Read(u32WmaFileHandle, WMA_HEADER_READ_LEN, &u32DestAddr);

                            pu8Data = (U8 *)u32DestAddr;
#else
                            msAPI_Steam_Seek(u32WmaFileHandle, u32Index);
                            msAPI_DataStreamIO_Read(u32WmaFileHandle, (void*)((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (MP3_INFO_READ_ADR | MIU_INTERVAL) : (MP3_INFO_READ_ADR)), MP3_INFO_READ_LEN);
#endif
                            u32DataOffset = 0;


                            memcpy(&u16DataType, &pu8Data[0],2);
                            memcpy(&u16DataLen, &pu8Data[2],2);

                            u32tmp = 0;

                        }

                        else
                        {
                            memcpy(&u16DataType, &pu8Data[u32DataOffset+2+u16DesNameLen],2);
                            memcpy(&u16DataLen, &pu8Data[u32DataOffset+4+u16DesNameLen],2);

                            u32tmp = u32DataOffset + u16DesNameLen;
                        }


                        WMA_INFO(printf("u16DesNameLen = %d, u16DataType=%d, u16DataLen=%d\n", u16DesNameLen, u16DataType, u16DataLen));



                        if( (u16DesNameLen == 16) && (u16DataType == 0) )// unicode
                        {
                            //because u16DesNameLen is 16  so   (u32DataOffset + u16DesNameLen) < (WMA_INFO_READ_LEN-1)


                            pu8DataTmp = (pu8Data + u32DataOffset + 2);

                            //"WM/Year"
                            if(memcmp(pu8DataTmp,u8WmaYear,sizeof(u8WmaYear))==0)
                            {
                                pWmaInfo->u8Year[0] = 0x01;

                                for(j=0;j<u16DataLen;j=j+2)
                                {
                                    pWmaInfo->u8Year[j+1] = pu8Data[u32tmp+j+6];     //6= 2(DesNameLen) + 2(DataType) + 2(DataLen)
                                    pWmaInfo->u8Year[j+2] = pu8Data[u32tmp+j+7];
                                }
                                pWmaInfo->u16YearLength = u16DataLen;
                                //Must reserve 4 bytes for "\0\0"
                                if(pWmaInfo->u16YearLength > WMA_MAX_YEAR_LENGTH - 4)
                                {
                                    pWmaInfo->u16YearLength = WMA_MAX_YEAR_LENGTH - 4;
                                }
                                //break;
                            }
                        }
                        else if( (u16DesNameLen == 28) && (u16DataType == 0) )// unicode
                        {
                            //because u16DesNameLen is 28  so   (u32DataOffset + u16DesNameLen) < (WMA_INFO_READ_LEN-1)

                            pu8DataTmp = (pu8Data + u32DataOffset + 2);

                            //"WM/AlbumTitle"
                            if(memcmp(pu8DataTmp,u8AlbumTitle,sizeof(u8AlbumTitle))==0)
                            {
                                pWmaInfo->u8Album[0] = 0x01;

                                WMA_INFO(printf("Album is:"));

                                for(j=0;j<u16DataLen;j=j+2)
                                {
                                    pWmaInfo->u8Album[j+1] = pu8Data[u32tmp+j+6];    //6= 2(DesNameLen) + 2(DataType) + 2(DataLen)
                                    WMA_INFO(printf("%c", pWmaInfo->u8Album[j+1]));
                                    pWmaInfo->u8Album[j+2] = pu8Data[u32tmp+j+7];
                                }
                                WMA_INFO(printf("\n"));
                                pWmaInfo->u16AlbumLength = u16DataLen;
                                //Must reserve 4 bytes for "\0\0"
                                if(pWmaInfo->u16AlbumLength > WMA_MAX_ALBUM_LENGTH - 4)
                                {
                                    pWmaInfo->u16AlbumLength = WMA_MAX_ALBUM_LENGTH - 4;
                                }
                                //break;
                            }
                        }
                        // get to next description
                        u32DataOffset += 6+u16DesNameLen+u16DataLen;
                    }

                    if(u32DataOffset > 0)
                    {
                        i = (u32DataOffset - 1);
                        u32Index += (u32DataOffset - 1);
                    }
                }
            }

            if(!pWmaInfo->bFilePropertiesFound)
            {
                if((pu8Data[i]==0xA1)&&(pu8Data[i+1]==0xDC)&&(pu8Data[i+2]==0xAB)&&(pu8Data[i+3]==0x8C)&&
                    (pu8Data[i+4]==0x47)&&(pu8Data[i+5]==0xA9)&&(pu8Data[i+6]==0xCF)&&(pu8Data[i+7]==0x11)&&
                    (pu8Data[i+8]==0x8E)&&(pu8Data[i+9]==0xE4)&&(pu8Data[i+10]==0x00)&&(pu8Data[i+11]==0xC0)&&
                    (pu8Data[i+12]==0x0C)&&(pu8Data[i+13]==0x20)&&(pu8Data[i+14]==0x53)&&(pu8Data[i+15]==0x65)
                )
                {
                    pWmaInfo->bFilePropertiesFound = TRUE;
                    memcpy(&pWmaInfo->u32Duration,&pu8Data[i+0x4a],4);
                    //Specifies the time needed to send the file in 100-nanosecond units.
                    pWmaInfo->u32Duration = (pWmaInfo->u32Duration*0.0065536);     //*(2^16 * 0.0000001)
#if ENABLE_WMA_INDEX_TABLE
                    //Specifies the amount of time to buffer data before starting to play the file, in millisecond units.
                    memcpy(&pWmaInfo->u32PreRoll,&pu8Data[i+0x50],4);   //in millisecond
#endif
                    //if send duration incorrect, use play duration subtract  preroll.
                    if(pWmaInfo->u32Duration == 0)
                    {
#if ENABLE_WMA_INDEX_TABLE
                        U32 u32PlayDuration;
                        //Specifies the time needed to play the file in 100-nanosecond units.
                        memcpy(&u32PlayDuration,&pu8Data[i+0x42],4);
                        if(u32PlayDuration*0.0065536 > pWmaInfo->u32PreRoll*0.001)
                        {
                            pWmaInfo->u32Duration = (u32PlayDuration*0.0065536 - pWmaInfo->u32PreRoll*0.001);
                        }
#else
                        U32 u32PlayDuration, u32PreRoll;
                        //Specifies the time needed to play the file in 100-nanosecond units.
                        memcpy(&u32PlayDuration,&pu8Data[i+0x42],4);
                        //Specifies the amount of time to buffer data before starting to play the file, in millisecond units.
                        memcpy(&u32PreRoll,&pu8Data[i+0x50],4);   //in millisecond
                        if(u32PlayDuration*0.0065536 > u32PreRoll*0.001)
                        {
                            pWmaInfo->u32Duration = (u32PlayDuration*0.0065536 - u32PreRoll*0.001);
                        }
#endif
                    }
                    if(pWmaInfo->u32Duration == 0)
                    {
                        pWmaInfo->u32Duration = 0xFFFFFFFF;
                    }
                    memcpy(&pWmaInfo->u32PacketSize,&pu8Data[i+0x5c],4);
                    memcpy(&pWmaInfo->u32TotalPacket,&pu8Data[i+0x38],4);
                    WMA_INFO(printf("pWmaInfo->u32PacketSize = 0x%lx\n",pWmaInfo->u32PacketSize));
                    WMA_INFO(printf("pWmaInfo->u32TotalPacket = 0x%lx\n",pWmaInfo->u32TotalPacket));

                    U32 u32Flags;
                    memcpy(&u32Flags,&pu8Data[i+FILE_PROPERTIES_FLAGS],4);

                    //Specifies, if set, that a file is in the process of being created,
                    //and thus that various values stored in the header objects are invalid.
                    BOOLEAN bBroadcast = u32Flags & 0x1;//(bit 0)

                    if(bBroadcast)
                    {
                        pWmaInfo->bCheckFfFb = FALSE;
                    }
                    else
                    {
                        pWmaInfo->bCheckFfFb = TRUE;
                    }
                }
            }

            if(!pWmaInfo->bHeaderExtensionFound)
            {
                if((pu8Data[i]==0xB5)&&(pu8Data[i+1]==0x03)&&(pu8Data[i+2]==0xBF)&&(pu8Data[i+3]==0x5F)&&
                    (pu8Data[i+4]==0x2E)&&(pu8Data[i+5]==0xA9)&&(pu8Data[i+6]==0xCF)&&(pu8Data[i+7]==0x11)&&
                    (pu8Data[i+8]==0x8E)&&(pu8Data[i+9]==0xE3)&&(pu8Data[i+10]==0x00)&&(pu8Data[i+11]==0xC0)&&
                    (pu8Data[i+12]==0x0C)&&(pu8Data[i+13]==0x20)&&(pu8Data[i+14]==0x53)&&(pu8Data[i+15]==0x65)
                )
                {
                    U32 u32Skip=0;
                    U32 u32HeaderSize;

                    pWmaInfo->bHeaderExtensionFound = TRUE;
                    memcpy(&u32HeaderSize,&pu8Data[i+0x10],4);

                    for(u32Skip=0x10;u32Skip<u32HeaderSize;u32Skip++)
                    {
                        if((i+u32Skip+0x100) > (WMA_HEADER_READ_LEN-1))
                        {
                            u32Index += u32Skip;

                        #if ENABLE_FILE_BM
                            msAPI_DataStreamIO_MID_FS_Seek(u32Index);
                            msAPI_DataStreamIO_MID_FS_Read(u32WmaFileHandle, WMA_HEADER_READ_LEN, &u32DestAddr);
                            pu8Data = (U8 *)u32DestAddr;
                        #else
                            msAPI_Steam_Seek(u32WmaFileHandle, u32Index);
                            msAPI_DataStreamIO_Read(u32WmaFileHandle, (void*)((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (MP3_INFO_READ_ADR | MIU_INTERVAL) : (MP3_INFO_READ_ADR)), MP3_INFO_READ_LEN);
                        #endif
                            u32HeaderSize -= u32Skip;
                            i = 0;
                            u32Skip = 0;
                        }
                        if(!pWmaInfo->bHE_MetadataObjectFound)
                        {
                            if((pu8Data[i+u32Skip]==0xEA)&&(pu8Data[i+u32Skip+1]==0xCB)&&(pu8Data[i+u32Skip+2]==0xF8)&&(pu8Data[i+u32Skip+3]==0xC5)&&
                                (pu8Data[i+u32Skip+4]==0xAF)&&(pu8Data[i+u32Skip+5]==0x5B)&&(pu8Data[i+u32Skip+6]==0x77)&&(pu8Data[i+u32Skip+7]==0x48)&&
                                (pu8Data[i+u32Skip+8]==0x84)&&(pu8Data[i+u32Skip+9]==0x67)&&(pu8Data[i+u32Skip+10]==0xAA)&&(pu8Data[i+u32Skip+11]==0x8C)&&
                                (pu8Data[i+u32Skip+12]==0x44)&&(pu8Data[i+u32Skip+13]==0xFA)&&(pu8Data[i+u32Skip+14]==0x4C)&&(pu8Data[i+u32Skip+15]==0xCA)
                            )
                            {
                                U16 u16Attribute;
                                U16 u16ObjectSize;
                                U16 u16NameLength;
                                U32 u32DataLength;
                                U32 u32AttrIndex;
                                U8 u8Name[64];
                                U8 u8Data[32];
                                const U8 au8IsVBR[28] = {'I',0x00,'s',0x00,'V',0x00,'B',0x00,'R',0x00,0x00,0x00};
                                const U8 au8DeviceConformanceTemplate[64] = {'D',0x00,'e',0x00,'v',0x00,'i',0x00,'c',0x00,'e',0x00,
                                                                            'C',0x00,'o',0x00,'n',0x00,'f',0x00,'o',0x00,'r',0x00,
                                                                            'm',0x00,'a',0x00,'n',0x00,'c',0x00,'e',0x00,'T',0x00,
                                                                            'e',0x00,'m',0x00,'p',0x00,'l',0x00,'a',0x00,'t',0x00,
                                                                            'e',0x00,0x00,0x00};
                                const U8 au8PeakReference[64] = {'W',0x00,'M',0x00,'/',0x00,'W',0x00,'M',0x00,'A',0x00,
                                                                'D',0x00,'R',0x00,'C',0x00,'P',0x00,'e',0x00,'a',0x00,
                                                                'k',0x00,'R',0x00,'e',0x00,'f',0x00,'e',0x00,'r',0x00,
                                                                'e',0x00,'n',0x00,'c',0x00,'e',0x00,0x00,0x00};
                                const U8 au8PeakTarget[64] = {'W',0x00,'M',0x00,'/',0x00,'W',0x00,'M',0x00,'A',0x00,
                                                             'D',0x00,'R',0x00,'C',0x00,'P',0x00,'e',0x00,'a',0x00,
                                                             'k',0x00,'T',0x00,'a',0x00,'r',0x00,'g',0x00,'e',0x00,
                                                             't',0x00,0x00,0x00};
                                const U8 au8AverageReference[64] = {'W',0x00,'M',0x00,'/',0x00,'W',0x00,'M',0x00,'A',0x00,
                                                                   'D',0x00,'R',0x00,'C',0x00,'A',0x00,'v',0x00,'e',0x00,
                                                                   'r',0x00,'a',0x00,'g',0x00,'e',0x00,'R',0x00,'e',0x00,
                                                                   'f',0x00,'e',0x00,'r',0x00,'e',0x00,'n',0x00,'c',0x00,
                                                                   'e',0x00,0x00,0x00};
                                const U8 au8AverageTarget[64] = {'W',0x00,'M',0x00,'/',0x00,'W',0x00,'M',0x00,'A',0x00,
                                                                'D',0x00,'R',0x00,'C',0x00,'A',0x00,'v',0x00,'e',0x00,
                                                                'r',0x00,'a',0x00,'g',0x00,'e',0x00,'T',0x00,'a',0x00,
                                                                'r',0x00,'g',0x00,'e',0x00,'t',0x00,0x00,0x00};
                                pWmaInfo->bHE_MetadataObjectFound = TRUE;
                                memcpy(&u16ObjectSize,&pu8Data[i+u32Skip+16],8);
                                memcpy(&u16Attribute,&pu8Data[i+u32Skip+24],2);

                                if(u16Attribute==6)
                                {
                                    pWmaInfo->bWMADRCFound = TRUE;
                                    u32Skip += 0x1A; //To attribute data
                                    for(u32AttrIndex = 0 ; u32AttrIndex < u16Attribute ; u32AttrIndex++ )
                                    {
                                        memcpy(&u16NameLength,&pu8Data[i+u32Skip+0x4],2);
                                        memcpy(&u32DataLength,&pu8Data[i+u32Skip+0x8],4);
                                        u32Skip += 0xC;

                                        memcpy(&u8Name[0],&pu8Data[i+u32Skip],u16NameLength);
                                        u32Skip += u16NameLength;

                                        memcpy(&u8Data[0],&pu8Data[i+u32Skip],u32DataLength);
                                        u32Skip += u32DataLength;

                                        if(memcmp(u8Name,au8IsVBR,u16NameLength)==0)
                                        {
                                            memcpy(&pWmaInfo->u32IsVBR,&u8Data[0],u32DataLength);
                                            WMA_INFO(printf("pWmaInfo->u32IsVBR:0x%lx\n",pWmaInfo->u32IsVBR));
                                        }
                                        else if(memcmp(u8Name,au8DeviceConformanceTemplate,u16NameLength)==0)
                                        {
                                            memcpy(&pWmaInfo->u8DeviceConformanceTemplate[0],&u8Data[0],u32DataLength);
                                            if(pWmaInfo->u8DeviceConformanceTemplate[0] == 0x4D)
                                            {
                                                if(pWmaInfo->u8DeviceConformanceTemplate[2] == 0x30)
                                                {
                                                    WMA_INFO(printf("WMA pro M0\n"));
                                                }
                                                else if(pWmaInfo->u8DeviceConformanceTemplate[2] == 0x31)
                                                {
                                                    WMA_INFO(printf("WMA pro M1\n"));
                                                }
                                                else if(pWmaInfo->u8DeviceConformanceTemplate[2] == 0x32)
                                                {
                                                    WMA_INFO(printf("WMA pro M2\n"));
                                                }
                                                else
                                                {
                                                    WMA_INFO(printf("Unknown Format!!\n"));
                                                }
                                            }
                                            else
                                            {
                                                WMA_INFO(printf("Unknown Format!!\n"));
                                            }
                                        }
                                        else if(memcmp(u8Name,au8PeakReference,u16NameLength)==0)
                                        {
                                            memcpy(&pWmaInfo->u32WMADRCPeakReference,&u8Data[0],u32DataLength);
                                            WMA_INFO(printf("pWmaInfo->u32WMADRCPeakReference:0x%lx\n",pWmaInfo->u32WMADRCPeakReference));
                                        }
                                        else if(memcmp(u8Name,au8PeakTarget,u16NameLength)==0)
                                        {
                                            memcpy(&pWmaInfo->u32WMADRCPeakTarget,&u8Data[0],u32DataLength);
                                            WMA_INFO(printf("pWmaInfo->u32WMADRCPeakTarget:0x%lx\n",pWmaInfo->u32WMADRCPeakTarget));
                                        }
                                        else if(memcmp(u8Name,au8AverageReference,u16NameLength)==0)
                                        {
                                            memcpy(&pWmaInfo->u32WMADRCAverageReference,&u8Data[0],u32DataLength);
                                            WMA_INFO(printf("pWmaInfo->u32WMADRCAverageReference:0x%lx\n",pWmaInfo->u32WMADRCAverageReference));
                                        }
                                        else if(memcmp(u8Name,au8AverageTarget,u16NameLength)==0)
                                        {
                                            memcpy(&pWmaInfo->u32WMADRCAverageTarget,&u8Data[0],u32DataLength);
                                            WMA_INFO(printf("pWmaInfo->u32WMADRCAverageTarget:0x%lx\n",pWmaInfo->u32WMADRCAverageTarget));
                                        }

                                    }
                                }
                            }
                        }
                        //advanced Mutual Exclusion Object
                        if(!pWmaInfo->bAdvancedMutualExclusionObject)
                        {
                            if((pu8Data[i+u32Skip]==0xCF)&&(pu8Data[i+u32Skip+1]==0x49)&&(pu8Data[i+u32Skip+2]==0x86)&&(pu8Data[i+u32Skip+3]==0xA0)&&
                                (pu8Data[i+u32Skip+4]==0x75)&&(pu8Data[i+u32Skip+5]==0x47)&&(pu8Data[i+u32Skip+6]==0x70)&&(pu8Data[i+u32Skip+7]==0x46)&&
                                (pu8Data[i+u32Skip+8]==0x8A)&&(pu8Data[i+u32Skip+9]==0x16)&&(pu8Data[i+u32Skip+10]==0x6E)&&(pu8Data[i+u32Skip+11]==0x35)&&
                                (pu8Data[i+u32Skip+12]==0x35)&&(pu8Data[i+u32Skip+13]==0x75)&&(pu8Data[i+u32Skip+14]==0x66)&&(pu8Data[i+u32Skip+15]==0xCD)
                            )
                            {
                                U16 u16Next;
                                U16 u16StreamNumber;

                                pWmaInfo->bAdvancedMutualExclusionObject = TRUE;
                                memcpy(&u16StreamNumber,&pu8Data[i+u32Skip+40],2);

                                if(u16StreamNumber < 2 || u16StreamNumber > 127)
                                {
                                    pWmaInfo->bAdvancedMutualExclusionObject = FALSE;
                                    WMA_INFO(printf("wrong advanced Mutual Exclusion Object\n"));
                                }
                                else
                                {
                                    pWmaInfo->u8StreamNumber = (U8)u16StreamNumber;
                                    u32Skip+=42;
                                    for(u16Next = 0; u16Next < u16StreamNumber; u16Next++)
                                    {
                                        memcpy(&pWmaInfo->u16StreamID[u16Next], &pu8Data[i+u32Skip+u16Next*2], 2);
                                        WMA_INFO(printf("pWmaInfo->u16StreamID[0x%lx]:0x%lx\n", u16Next, pWmaInfo->u16StreamID[u16Next]));
                                    }
                                    pWmaInfo->u8CurrentStreamIndex = 1;
                                    u32Skip+=(u16StreamNumber*2);
                                }

                                WMA_INFO(printf("pWmaInfo->u8StreamNumber:0x%lx\n",pWmaInfo->u8StreamNumber));
                            }
                        }
                    }

                    if(u32Skip > 0)
                    {
                        u32Index += (u32Skip - 1);
                        i += (u32Skip - 1);
                    }
                }
            }

            if(!pWmaInfo->bExContentEObjectFound)
            {
                if((pu8Data[i]==0x14)&&(pu8Data[i+1]==0xE6)&&(pu8Data[i+2]==0x8A)&&(pu8Data[i+3]==0x29)&&
                    (pu8Data[i+4]==0x22)&&(pu8Data[i+5]==0x26)&&(pu8Data[i+6]==0x17)&&(pu8Data[i+7]==0x4C)&&
                    (pu8Data[i+8]==0xB9)&&(pu8Data[i+9]==0x35)&&(pu8Data[i+10]==0xDA)&&(pu8Data[i+11]==0xE0)&&
                    (pu8Data[i+12]==0x7E)&&(pu8Data[i+13]==0xE9)&&(pu8Data[i+14]==0x28)&&(pu8Data[i+15]==0x9C)
                )
                {
                    pWmaInfo->bExContentEObjectFound = TRUE;
                    j = i+0x10; //Jump Object ID
                    memcpy(&pWmaInfo->u32ExContentEObjectSize,&pu8Data[j+0x8],4);
                    j += 0xC; //Jump Header Info
                    pWmaInfo->u32ExContentEObjectLocation = j;
                    WMA_INFO(printf("DRM ExContentEObject Szie:0x%lx Location:0x%lx\n",pWmaInfo->u32ExContentEObjectSize,pWmaInfo->u32ExContentEObjectLocation));
                }
            }

            if(!pWmaInfo->bContentEObjectFound)
            {
                if((pu8Data[i]==0xFB)&&(pu8Data[i+1]==0xB3)&&(pu8Data[i+2]==0x11)&&(pu8Data[i+3]==0x22)&&
                    (pu8Data[i+4]==0x23)&&(pu8Data[i+5]==0xBD)&&(pu8Data[i+6]==0xD2)&&(pu8Data[i+7]==0x11)&&
                    (pu8Data[i+8]==0xB4)&&(pu8Data[i+9]==0xB7)&&(pu8Data[i+10]==0x00)&&(pu8Data[i+11]==0xA0)&&
                    (pu8Data[i+12]==0xC9)&&(pu8Data[i+13]==0x55)&&(pu8Data[i+14]==0xFC)&&(pu8Data[i+15]==0x6E)
                )
                {
                    pWmaInfo->bContentEObjectFound = TRUE;
                    j = i+0x10; //Jump Object ID
                    memcpy(&pWmaInfo->u32ContentEObjectSize,&pu8Data[j+0x8],4);
                    j += 0xC; //Jump Header Info
                    pWmaInfo->u32ContentEObjectLocation = j;
                    WMA_INFO(printf("DRM ContentEObject Szie:0x%lx Location:0x%lx\n",pWmaInfo->u32ContentEObjectSize,pWmaInfo->u32ContentEObjectLocation));
                }
            }

            if(!pWmaInfo->bDataObjectFound)
            {
                if((pu8Data[i]==0x36)&&(pu8Data[i+1]==0x26)&&(pu8Data[i+2]==0xB2)&&(pu8Data[i+3]==0x75)&&
                    (pu8Data[i+4]==0x8E)&&(pu8Data[i+5]==0x66)&&(pu8Data[i+6]==0xCF)&&(pu8Data[i+7]==0x11)&&
                    (pu8Data[i+8]==0xA6)&&(pu8Data[i+9]==0xD9)&&(pu8Data[i+10]==0x00)&&(pu8Data[i+11]==0xAA)&&
                    (pu8Data[i+12]==0x00)&&(pu8Data[i+13]==0x62)&&(pu8Data[i+14]==0xCE)&&(pu8Data[i+15]==0x6C)
                )
                {
                    pWmaInfo->bDataObjectFound = TRUE;
    #if ENABLE_ASF_PARSING
                    //--------------------------Init--------------------------------//
                    memset(_pu8ASFPayloadHeader,0,WMA_ASF_PACKET_HEADER_SIZE+1);
                    pWmaInfo->u8NumPayloads = 1;
                    _u32CurrentPacket = 0;
                    _u32CurrentPayload = 0;
                    _u32PayloadWriteLeft = 0;
                    //m_u32BufLeftSize = m_u32BufReadSize = 0;
                    //-------------------------------------------------------------//
    #endif
                }
            }

    #if (!ENABLE_WMDRMPD)
            if(pWmaInfo->bContentEObjectFound)
            {
                //Do not support DRM file!
                _enWMA_ErrCode = E_WMA_ERR_NOT_SUPPORT_DRM;
                return FALSE;
            }
    #endif

        }

        pWmaInfo->u32HeaderSize += 0x32;  //Jump Data Object Header(0x32)
        // 16:Object ID, 8:Object Size, 16:File ID, 8:Total Data packets, 2:Reserved
    }

#if ENABLE_WMA_INDEX_TABLE
////////////////////////////////////////////////////////
    U32 u32SeekOffset = 0;
    U32 u32SkipErrorPacketTimes = 0;
    U32 u32PayloadCounter = 0;

    //Initial total payload numbers
    pWmaInfo->u32TotalPayloads = 0;

#if WMA_MEASURE
    U32 u32Time1 = 0;
    U32 u32Time2 = 0;
    U32 u32Time3 = 0;
    U32 u32Time4 = 0;
    U32 u32Counter;

    u32Time1 = msAPI_Timer_GetTime0();

    printf("u32Time1 start\n");
#endif
    //parse each packet
    for(_u32CurrentPacket=0;_u32CurrentPacket< stWmaInfo.u32TotalPacket;_u32CurrentPacket++)
    {
        u32SeekOffset = stWmaInfo.u32HeaderSize+(_u32CurrentPacket*stWmaInfo.u32PacketSize);

#if ENABLE_FILE_BM
        msAPI_DataStreamIO_MID_FS_Seek(u32SeekOffset);

        if ( 0 != msAPI_DataStreamIO_MID_FS_Read(u32WmaFileHandle, 0x100, &u32DestAddr) )
        {
            //Packet header maximum size: 0x100 byte
            WMA_DBG(printf("No data to read.\n"));
            goto CreateIndexErr;
        }
        pu8Data = (U8 *)u32DestAddr;

        stWmaInfo.u16PacketOffset = MApp_WMA_ParsingASFPacketSCR((U32)pu8Data, &stWmaInfo);
#else
        msAPI_Steam_Seek(u32WmaFileHandle, u32SeekOffset);

        //re-calculate packet header
        if(0 != msAPI_DataStreamIO_Read(u32WmaFileHandle, (void*)((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (MP3_INFO_READ_ADR | MIU_INTERVAL) : (MP3_INFO_READ_ADR)), 0x100))
        {
                //Packet header maximum size: 0x100 byte
        WMA_DBG(printf("No data to read.\n"));
        goto CreateIndexErr;
        }

        stWmaInfo.u16PacketOffset = MApp_WMA_ParsingASFPacketSCR(_PA2VA(((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (MP3_INFO_READ_ADR | MIU_INTERVAL) : (MP3_INFO_READ_ADR))),&stWmaInfo);
#endif

        if(stWmaInfo.u16PacketOffset == 0)
        {
            u32SkipErrorPacketTimes++;
            if(u32SkipErrorPacketTimes >= 3)
            {
                WMA_DBG(printf("Too much error , exit play.\n"));
                goto CreateIndexErr;
            }
        }
        u32SeekOffset += stWmaInfo.u16PacketOffset;

        //parse payloads for each packet to create wma index table
        for(_u32CurrentPayload=0; _u32CurrentPayload < stWmaInfo.u8NumPayloads; _u32CurrentPayload++)
        {
#if ENABLE_FILE_BM
            msAPI_DataStreamIO_MID_FS_Seek(u32SeekOffset);
            msAPI_DataStreamIO_MID_FS_Read(u32WmaFileHandle, 0x100, &u32DestAddr);   //payload header maximum size is 0x100
            pu8Data = (U8 *)u32DestAddr;
            stWmaInfo.u16PayloadOffset = MApp_WMA_ParsingASFPayloadPTime((U32)pu8Data,&stWmaInfo, pWmaInfo->u32TotalPayloads-pWmaInfo->u8NumPayloads+_u32CurrentPayload, u32SeekOffset);
#else
            msAPI_Steam_Seek(u32WmaFileHandle, u32SeekOffset);
            msAPI_DataStreamIO_Read(u32WmaFileHandle, (void*)((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (MP3_INFO_READ_ADR | MIU_INTERVAL) : (MP3_INFO_READ_ADR)), 0x100);   //payload header maximum size is 0x100
            stWmaInfo.u16PayloadOffset = MApp_WMA_ParsingASFPayloadPTime(_PA2VA(((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (MP3_INFO_READ_ADR | MIU_INTERVAL) : (MP3_INFO_READ_ADR))),&stWmaInfo, pWmaInfo->u32TotalPayloads-pWmaInfo->u8NumPayloads+_u32CurrentPayload, u32SeekOffset);
#endif
            if(stWmaInfo.u16PayloadOffset == (U16)0xFFFFFFFF)
            {
                WMA_INFO(printf("payload error! exit play.\n"));
                goto CreateIndexErr;
            }
            u32SeekOffset += stWmaInfo.u16PayloadOffset;
            if(stWmaInfo.u16CurrentStreamId != stWmaInfo.u16StreamID[stWmaInfo.u8CurrentStreamIndex])
            {
                //payload can be empty  ex: 張學友越吻越傷心.wma has three empty payloads 54,55,56

                WMA_INFO(printf("skip stream %d payload, packet: %lu , payload: %lu\n", stWmaInfo.u16CurrentStreamId,_u32CurrentPacket,u32PayloadCounter));

            }

            WMA_DBG(printf("packet: %lu   payload: %lu\n",_u32CurrentPacket,u32PayloadCounter));
            u32SeekOffset += stWmaInfo.u32PayloadLength;
            u32PayloadCounter++;

        }

    }

    WMA_DBG(printf("Packet-payload end\n"));

#if WMA_MEASURE
        printf("Packet-payload end\n");

#endif


////////////////////////////////////////////////////

CreateIndexErr:
    _u32CurrentPacket = 0;
    _u32CurrentPayload= 0;

#endif

#if WMA_MEASURE
    u32Time2 = msAPI_Timer_GetTime0();

    bwmaCollect = FALSE;

    msAPI_Steam_Seek(u32WmaFileHandle, 0);




    u32Time3 = msAPI_Timer_GetTime0();

    for(u32Counter=0;u32Counter<=stWmaInfo.u32FileSize;)
    {

        msAPI_DataStreamIO_Read(u32WmaFileHandle, (void*)((WMA_INFO_READ_MEMORY_TYPE & MIU1) ? (WMA_INFO_READ_ADR | MIU_INTERVAL) : (WMA_INFO_READ_ADR)), MIDFS_SIZE);
        u32Counter = u32Counter + MIDFS_SIZE;

    }
    if(u32Counter!=stWmaInfo.u32FileSize)
    {
        msAPI_DataStreamIO_Read(u32WmaFileHandle, (void*)((WMA_INFO_READ_MEMORY_TYPE & MIU1) ? (WMA_INFO_READ_ADR | MIU_INTERVAL) : (WMA_INFO_READ_ADR)), stWmaInfo.u32FileSize - u32Counter);
    }


    u32Time4 = msAPI_Timer_GetTime0();


    printf("Filesize: %lu read by MIDFS_SIZE: %lu needs: %lu ms\n",stWmaInfo.u32FileSize,MIDFS_SIZE,u32Time4 -u32Time3 );


    printf("create table total time: %lu ms\n",u32Time2-u32Time1);

    printf("wma_collect total time: %lu ms\n",u32Time2-u32collStart);


    printf("read path1 count: %lu\n",u32TotalRead_1);


    printf("read path2 count: %lu, bytes: %lu   total loop:%lu   total loop time: %lu\n",u32TotalRead_2,u32TotalReadByte_2,u32TotalPrevReadNum_2,u32TotalLooptime);

    printf("read path3 count: %lu, bytes: %lu\n",u32TotalRead_3,u32TotalReadByte_3);

    printf("total read bytes: %lu\n", u32TotalReadByte_2 + u32TotalReadByte_3);

    u32TotalRead_1 = 0;
    u32TotalRead_2 = 0;
    u32TotalRead_3 = 0;

    u32TotalReadByte_2 = 0;
    u32TotalReadByte_3 = 0;


#endif
    msAPI_DataStreamIO_Close(u32WmaFileHandle);

    u32WmaFileHandle = INVALID_DATA_STREAM_HDL;

    if(pWmaInfo->bHeaderFound&pWmaInfo->bDataObjectFound)
    {
        return TRUE;
    }
    else
    {
        _enWMA_ErrCode = E_WMA_ERR_DECODE_HEADER_FAILURE;
        return FALSE;
    }
}

static void MApp_WMA_UpdatePlayTime(void)
{
    U32 u32FilePosition;

   if (u32WmaFileHandle == INVALID_DATA_STREAM_HDL)
   {
        stWmaInfo.u32PlayTimer = msAPI_Timer_GetTime0();
        stWmaInfo.u32CurrentPlayTime = 0;
        return;
    }

#if ENABLE_FILE_BM
    u32FilePosition = msAPI_DataStreamIO_MID_FS_Tell();
#else
    u32FilePosition = msAPI_DataStreamIO_Tell(u32WmaFileHandle);
#endif

    if ((u32FilePosition == 0) // no data read
        &&(bProcessFfRew!=TRUE)) // If need to process FF/Rew, It is possible the file position is 0
    {
        // reset timer
        stWmaInfo.u32PlayTimer = msAPI_Timer_GetTime0();
        stWmaInfo.u32CurrentPlayTime = 0;
        return;
    }

    if ((enWmaPlayStatus == WMA_STATUS_PAUSE)||(enWmaPlayStatus == WMA_STATUS_SCAN))
    {
        // reset timer
        stWmaInfo.u32PlayTimer = msAPI_Timer_GetTime0();
        return;
    }

    if (stWmaInfo.u32CurrentPlayTime == 0)
    {

    }

    stWmaInfo.u32CurrentPlayTime += msAPI_Timer_DiffTimeFromNow(stWmaInfo.u32PlayTimer);
    stWmaInfo.u32PlayTimer = msAPI_Timer_GetTime0();
    if (stWmaInfo.u32CurrentPlayTime >= ((U32)stWmaInfo.u32Duration * 1000))
    {
        // prevent out of range
        stWmaInfo.u32CurrentPlayTime = (U32)stWmaInfo.u32Duration * 1000;
    }
}


U32 MApp_WMA_GetTotalTime(void)
{
#if 0
    if (u32WmaFileHandle == INVALID_DATA_STREAM_HDL)
    {
        memset(&stWmaInfo, 0, sizeof(stWmaInfo));

        if (MApp_WMA_CollectInfo(&stWmaInfo) == FALSE)
        {
            return 0;
        }
    }
#endif
    return stWmaInfo.u32Duration;
}

U16 MApp_WMA_GetCurrentTime(void)
{
    U32 u32CurrentTime;

    if (!((enWmaState == STATE_WMA_INPUT)
            || (enWmaState == STATE_WMA_WAIT_DECODE_DONE)
            || (enWmaState == STATE_WMA_WAIT)))
    {
        return 0;
    }
    MApp_WMA_UpdatePlayTime();
    u32CurrentTime = stWmaInfo.u32CurrentPlayTime;
    u32CurrentTime /= 1000;

    return (u32CurrentTime  < stWmaInfo.u32Duration ? u32CurrentTime : stWmaInfo.u32Duration);
}

U32 MApp_WMA_GetCurrentTimeMs(void)
{
    U32 u32CurrentTime;

    if (!((enWmaState == STATE_WMA_INPUT)
            || (enWmaState == STATE_WMA_WAIT_DECODE_DONE)
            || (enWmaState == STATE_WMA_WAIT)))
    {
        return 0;
    }
    MApp_WMA_UpdatePlayTime();
    u32CurrentTime = stWmaInfo.u32CurrentPlayTime;

    return ((u32CurrentTime/1000) < stWmaInfo.u32Duration ? u32CurrentTime : (stWmaInfo.u32Duration * 1000));
}

BOOLEAN MApp_WMA_Initial(void)
{
    memset(&stWmaInfo, 0, sizeof(stWmaInfo));
    _enWMA_ErrCode = E_WMA_ERR_NONE;

    msAPI_WMA_FileEndDataHandle(0);
    if (MApp_WMA_CollectInfo(&stWmaInfo) == FALSE)
    {
        return FALSE;
    }

#if 0
    if ( MApp_MPlayer_QueryCurrentFileMediaSubType() == E_MPLAYER_SUBTYPE_WMA) //WMA
    {
        g_u16GroupXPos = 0;
        g_u16GroupYPos = 0;
        MApp_UiMenu_DrawComponents(DrawMp3InfoBG);
        MApp_UiMenu_DrawComponents(DrawWmaInfoText);
        g_u16GroupXPos = UI_MEDIA_PLAYER_INFO_X;
        g_u16GroupYPos = UI_MEDIA_PLAYER_INFO_Y;
        MApp_UiMenu_DrawComponents(DrawMp3InfoItem);
    }
#endif

    if(stWmaInfo.u16FormatTag == CODEC_FORMAT_WMA_PRO)
    {
        enCurrentDecSystem = MSAPI_AUD_DVB_WMA_PRO;
    }
    else if(stWmaInfo.u16FormatTag == CODEC_FORMAT_MP3)
    {
        enCurrentDecSystem = MSAPI_AUD_DVB_MP3;
    }
    else
    {
        enCurrentDecSystem = MSAPI_AUD_DVB_WMA;
    }

    if(_MApp_WMA_CheckSupportedAudio(enCurrentDecSystem)==FALSE)
    {
        printf("DSP not supported Codec[enCurrentDecSystem:0x%x]\n",enCurrentDecSystem);
        return FALSE;
    }

    msAPI_WMA_Init(enCurrentDecSystem);

#if ENABLE_ASF_PARSING
    msAPI_WMA_SetASFParm(WMA_PARAMTYPE_PARSINGBYAPP, 1);
    msAPI_WMA_SetASFParm(WMA_PARAMTYPE_VERSION, stWmaInfo.u8Version);
    msAPI_WMA_SetASFParm(WMA_PARAMTYPE_CHANNELS, stWmaInfo.u16Channels);
    msAPI_WMA_SetASFParm(WMA_PARAMTYPE_SAMPLERATE, stWmaInfo.u32SampleRate);
    msAPI_WMA_SetASFParm(WMA_PARAMTYPE_BYTERATE, stWmaInfo.u32ByteRate);
    msAPI_WMA_SetASFParm(WMA_PARAMTYPE_BLOCKALIGN, stWmaInfo.u16BlockAlign);
    msAPI_WMA_SetASFParm(WMA_PARAMTYPE_ENCOPT, stWmaInfo.u16Encopt);
    msAPI_WMA_SetASFParm(WMA_PARAMTYPE_MAX_PACKET_SIZE, 0);

    if(stWmaInfo.u16FormatTag == CODEC_FORMAT_WMA_PRO)
    {
        msAPI_WMA_SetASFParm(WMA_PARAMTYPE_BITS_PER_SAMPLE, stWmaInfo.u16BitsSample);
        msAPI_WMA_SetASFParm(WMA_PARAMTYPE_CHANNELMASK, stWmaInfo.u32ChannelMask);
        msAPI_WMA_SetASFParm(WMA_PARAMTYPE_DRC_PARAM_EXIST, stWmaInfo.bWMADRCFound);
        if(stWmaInfo.bWMADRCFound == TRUE)
        {
            msAPI_WMA_SetASFParm(WMA_PARAMTYPE_DRC_RMS_AMP_REF, stWmaInfo.u32WMADRCAverageReference);
            msAPI_WMA_SetASFParm(WMA_PARAMTYPE_DRC_RMS_AMP_TARGET, stWmaInfo.u32WMADRCAverageTarget);
            msAPI_WMA_SetASFParm(WMA_PARAMTYPE_DRC_PEAK_AMP_REF, stWmaInfo.u32WMADRCPeakReference);
            msAPI_WMA_SetASFParm(WMA_PARAMTYPE_DRC_PEAK_AMP_TARGET, stWmaInfo.u32WMADRCPeakTarget);
        }
    }
#endif

#if ENABLE_WMDRMPD
    if(stWmaInfo.bContentEObjectFound == TRUE)
    {
        if(!MApp_WMA_WMDRMPD_GetLicense())
        {
            printf("MApp_WMA_WMDRMPD_GetLicense Fail....\n");
            _enWMA_ErrCode = E_WMA_ERR_GET_LICENSE_FAILURE;
            return FALSE;
        }
    }
#endif

    if(msAPI_AUD_IsAudioMutedByUser())
    {
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
    }
    else
    {
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
    }

    bReloadDsp = FALSE;

    enWmaPlayStatus = WMA_STATUS_PLAYING;

    MApp_WMA_UpdatePlayTime();

    return TRUE;
}


void MApp_WMA_CloseFile(void)
{
    if (u32WmaFileHandle == INVALID_DATA_STREAM_HDL)
        return;

    msAPI_DataStreamIO_Close(u32WmaFileHandle);
    u32WmaFileHandle = INVALID_DATA_STREAM_HDL;

    //close E_DATA_STREAM_TYPE_MUSIC2 in case sometimes ap open it and chakra does not close.
    if(INVALID_DATA_STREAM_HDL != (u32WmaFileHandle = msAPI_DataStreamIO_Open(m_pWmaFileEntry, OPEN_MODE_FOR_READ,E_DATA_STREAM_TYPE_MUSIC2)))
    {
        msAPI_DataStreamIO_Close(u32WmaFileHandle);
        u32WmaFileHandle = INVALID_DATA_STREAM_HDL;
    }
}

void MApp_WMA_Stop(void)
{
#if (ENABLE_LAST_MEMORY==1)&&ENABLE_LAST_MEMORY_ENABLE_MUSIC
    if (m_u8LastMemoryCheck==TRUE)
    {
        MApp_MPlayer_LastMemory_SetResumePlayAttribute(0);
        m_u8LastMemoryCheck=FALSE;
    }
#endif
    msAPI_WMA_StopDecode();
    MApp_WMA_CloseFile();

#if ENABLE_WMDRMPD
    if(stWmaInfo.bContentEObjectFound)  //DRM Content
    {
        MApp_WMDRMPD_Finalize();
    }
#endif

#if ENABLE_WMA_DSP_DEBUG
msAPI_FCtrl_FileClose(u8FileHandle0);
#endif

    u8MusicFFFWMode = WMA_NORMAL_MODE;
    enWmaPlayStatus = WMA_STATUS_STOP;
    enWmaState = STATE_WMA_STANDBY;
}

BOOLEAN MApp_WMA_OpenFile(void)
{
    WMA_DBG(printf("\nOpen File \n"));

    if (u32WmaFileHandle != INVALID_DATA_STREAM_HDL)
    {
        MApp_WMA_CloseFile();
    }

    u32WmaFileHandle = msAPI_DataStreamIO_Open(m_pWmaFileEntry, OPEN_MODE_FOR_READ,E_DATA_STREAM_TYPE_MUSIC);
    if(u32WmaFileHandle == INVALID_DATA_STREAM_HDL)
    {
        WMA_DBG(printf("\nopen file failed"););
        _enWMA_ErrCode = E_WMA_ERR_DATA_OPERATION_FAILURE;
        return FALSE;
    }

    return TRUE;
}

void MApp_WMA_Input(void)
{
    U32 u32ReqAddr, u32ReqBytes;
    static U32 u32Len, u32TimeMarker;

    if ((enWmaPlayStatus == WMA_STATUS_PAUSE) ||
        (enWmaPlayStatus == WMA_STATUS_SCAN) ||
        (msAPI_WMA_CheckInputRequest(&u32ReqAddr, &u32ReqBytes) == FALSE))
        return;

    if (u32ReqBytes == 0)
        return;

#if ENABLE_FILE_BM
    if ((msAPI_DataStreamIO_MID_FS_Tell() + u32ReqBytes) > msAPI_DataStreamIO_Length(u32WmaFileHandle))
#else
    if ((msAPI_DataStreamIO_Tell(u32WmaFileHandle) + u32ReqBytes) > msAPI_DataStreamIO_Length(u32WmaFileHandle))
#endif
    {
        // if we don't have enough data asked by DSP, we have to clear the buffer first or garbage will be left
        msAPI_WMA_CleanFileEndData((U32)u32ReqAddr, u32ReqBytes, 0x0UL);
    }

#if ENABLE_ASF_PARSING
    {
        u32WmaFileBytesLeft = MApp_WMA_AddASFPacketForDSP(u32ReqAddr,u32ReqBytes);
    }
#else
    if(bProcessFfRew)
    {
        if(u32WmaHeaderByteSent == 0 )
        {
            msAPI_Steam_Seek(u32WmaFileHandle, 0);
        }

        if((stWmaInfo.u32HeaderSize-u32WmaHeaderByteSent)>u32ReqBytes)
        {
            u32WmaFileBytesLeft = msAPI_DataStreamIO_Read(u32WmaFileHandle, (void*)u32ReqAddr, u32ReqBytes);
            u32WmaHeaderByteSent = u32WmaHeaderByteSent + u32ReqBytes;
        }
        else if ((stWmaInfo.u32HeaderSize-u32WmaHeaderByteSent)==u32ReqBytes)
        {
            u32WmaFileBytesLeft = msAPI_DataStreamIO_Read(u32WmaFileHandle, (void*)u32ReqAddr, u32ReqBytes);
            u32WmaHeaderByteSent = u32WmaHeaderByteSent + u32ReqBytes;
            msAPI_Steam_Seek(u32WmaFileHandle, stWmaInfo.u32HeaderSize+stWmaInfo.u32SkipPacket *stWmaInfo.u32PacketSize);
            bProcessFfRew = FALSE;
        }
        else
        {
            u32WmaFileBytesLeft = msAPI_DataStreamIO_Read(u32WmaFileHandle, (void*)u32ReqAddr, u32ReqBytes);
            msAPI_Steam_Seek(u32WmaFileHandle, stWmaInfo.u32HeaderSize+stWmaInfo.u32SkipPacket *stWmaInfo.u32PacketSize);
            u32WmaFileBytesLeft += msAPI_DataStreamIO_Read(u32WmaFileHandle, (void*)(u32ReqAddr+(stWmaInfo.u32HeaderSize-u32WmaHeaderByteSent)), u32ReqBytes-(stWmaInfo.u32HeaderSize-u32WmaHeaderByteSent));
            bProcessFfRew = FALSE;
        }
    }
    else
    {
        u32WmaFileBytesLeft = msAPI_DataStreamIO_Read(u32WmaFileHandle, (void*)u32ReqAddr, u32ReqBytes);
    }
#endif
    WMA_DBG(printf("msAPI_DataStreamIO_Read  addr=%lx,len=%lx\n",u32ReqAddr,u32ReqBytes);)

    u32Len = 0;
    u32TimeMarker = msAPI_Timer_GetTime0();

    if (u32WmaFileBytesLeft == u32ReqBytes)
    {
        // end of file
        MS_DEBUG_MSG(printf("End of file\n"));
        enWmaState = STATE_WMA_WAIT_DECODE_DONE;
        return;
    }
    else if (u32WmaFileBytesLeft!=0)
    {
        //infor DSP residual bytes
        msAPI_WMA_FileEndDataHandle(u32WmaFileBytesLeft);
    }


    msAPI_WMA_SetInput();

}

BOOLEAN MApp_WMA_LoadDspCodec(En_DVB_decSystemType enDecSystem)
{
    // stop codec
    msAPI_WMA_StopDecode();

    if (bReloadDsp == TRUE)
    {
        // reload dsp codec before
        return FALSE;
    }

    enCurrentDecSystem = enDecSystem;
    msAPI_WMA_Init(enCurrentDecSystem);
    bReloadDsp = TRUE;

    return TRUE;
}

void MApp_WMA_Play(void)
{
    msAPI_WMA_StopDecode();
    msAPI_DataStreamIO_Close(u32WmaFileHandle);
    if(enWmaPlayStatus == WMA_STATUS_PLAYING ||
       enWmaPlayStatus == WMA_STATUS_PAUSE ||
       enWmaPlayStatus == WMA_STATUS_SCAN)
    {
        enWmaState = STATE_WMA_WAIT;
        enWmaPlayStatus = WMA_STATUS_STOP;
    }
    else
    {
        enWmaState = STATE_WMA_INIT;
        enWmaPlayStatus = WMA_STATUS_PLAYING;
    }
}

#if 0
void MApp_WMA_DrawStatus(void)
{
    g_u16GroupXPos=0;
    g_u16GroupYPos=0;

    switch (enWmaPlayStatus)
    {
        case WMA_STATUS_PLAYING:
            MApp_UiMenu_DrawComponents(DrawA3_MediaPlayer_Music_Play);
            break;

        case WMA_STATUS_PAUSE:
            {
                MApp_UiMenu_DrawComponents(DrawA3_MediaPlayer_Music_Pause);
            }
            break;

        case WMA_STATUS_SCAN:
            if (u8MusicFFFWMode == WMA_FF_Mode)
            {
                MApp_UiMenu_DrawComponents(DrawA3_MediaPlayer_Music_Ff);
            }
            else if (u8MusicFFFWMode == WMA_FW_Mode)
            {
                MApp_UiMenu_DrawComponents(DrawA3_MediaPlayer_Music_Rew);
            }
            break;

        case WMA_STATUS_STOP:
            MApp_UiMenu_DrawComponents(DrawA3_MediaPlayer_Music_Stop);
            break;
    }
}
#endif

#if 0//def HSS_UI
void MApp_WMA_DrawEQ(void)
{
    U8 i, j;
    U8 u8Threshold;
    U8 u8PrevGwinID;
    U16 u16Height;
    static U8 u8Cntr=0;

    u8Cntr++;
    if(u8Cntr%5)
        return;

    if(enWmaPlayStatus != WMA_STATUS_PLAYING)
        return;

    u8PrevGwinID = MApi_GOP_GWIN_GetCurrentWinId();
    MApi_GOP_GWIN_Switch2Gwin(u8MainOSDWinId);

    MApp_UiMenu_DrawMusicEQ_DblBufOn();
    MApp_UiMenu_DrawMusicEQ(UI_MEDIA_PLAYER_MP3_EQ_BAR_X,
                            UI_MEDIA_PLAYER_MP3_EQ_BAR_Y,
                            ((UI_MEDIA_PLAYER_MP3_EQ_BAR_W+10)*UI_MEDIA_PLAYER_MP3_EQ_BAR_NUM),
                            UI_MEDIA_PLAYER_MP3_EQ_BAR_H*3/2, EN_COLOR_BLACK);

    for(i=0;i<UI_MEDIA_PLAYER_MP3_EQ_BAR_NUM;i++)
    {
        if(i<UI_MEDIA_PLAYER_MP3_EQ_BAR_NUM/3)
        {
            u8Threshold = 40 + i*10;
        }
        else if(i > UI_MEDIA_PLAYER_MP3_EQ_BAR_NUM*2/3)
        {
            u8Threshold = 30+(UI_MEDIA_PLAYER_MP3_EQ_BAR_NUM-i)*10;
        }
        else
        {
            u8Threshold = 120;
        }

        srand(msAPI_Timer_GetTime0());
        u16Height = (U16)((U16)rand() % u8Threshold);

        if((i<(UI_MEDIA_PLAYER_MP3_EQ_BAR_NUM/3)) || (i>(UI_MEDIA_PLAYER_MP3_EQ_BAR_NUM*2/3)))
        {
            u16Height = (U16)UI_MEDIA_PLAYER_MP3_EQ_BAR_H*3/4 - u16Height - 45;
        }
        else
        {
            u16Height = (U16)UI_MEDIA_PLAYER_MP3_EQ_BAR_H*3/4 - u16Height + 30;
        }

        u16Height = u16Height/15;

        for(j=0;j<u16Height;j++)
        {
            MApp_UiMenu_DrawMusicEQ(UI_MEDIA_PLAYER_MP3_EQ_BAR_X+i*(UI_MEDIA_PLAYER_MP3_EQ_BAR_W+10),
                UI_MEDIA_PLAYER_MP3_EQ_BAR_Y+UI_MEDIA_PLAYER_MP3_EQ_BAR_H-j*15,
                UI_MEDIA_PLAYER_MP3_EQ_BAR_W, 10, EN_COLOR_RED);
        }
    }
    MApp_UiMenu_DblBufOff();
    MApi_GOP_GWIN_Switch2Gwin(u8PrevGwinID);

}
#endif

EN_WMA_SPEED MApp_WMA_GetFfRewSpeed(void)
{
    if (u8MusicFFFWMode == WMA_NORMAL_MODE)
        return EN_WMA_SPEED_X1;

    return enWmaPlaySpeed;
}

#if ENABLE_WMA_INDEX_TABLE

//******************************************************************************
/// get the payload information from payload index table.
/// @param  u32CurrentPayload \b current payload
/// @param  u32GotoTimeMs \b request goto time
/// @param  stWMAIndexTableReturn \b payload information closest to request goto time
/// @return u32CurrentPayload \b payload number closest to request goto time
//******************************************************************************

U32 MApp_WMA_GetPayloadIndexFromIndexTable(U32 u32CurrentPayload, U32 u32GotoTimeMs,ST_WMA_INDEX_TABLE *pstWMAIndexTableReturn)
{

    ST_WMA_INDEX_TABLE *pstWMAIndexTable = (ST_WMA_INDEX_TABLE *)(_PA2VA(u32WMAPayloadTableAddr));

    U32 u32OriginalPayload = u32CurrentPayload;

    if(pstWMAIndexTableReturn==NULL)
    {
        return u32CurrentPayload;
    }

    //memset(pstWMAIndexTableReturn, 0, sizeof(pstWMAIndexTableReturn));
    memset(pstWMAIndexTableReturn, 0, sizeof(ST_WMA_INDEX_TABLE));  // coverity@84327



    while(1)
    {
        if ( pstWMAIndexTable[u32CurrentPayload].u32WMAPayloadPTime <= u32GotoTimeMs )
        {
            if ( (u32CurrentPayload < stWmaInfo.u32TotalPayloads) && ( u32CurrentPayload < WMA_INDEX_TABLE_MAX_NUM ) && ( pstWMAIndexTable[u32CurrentPayload+1].u32WMAPayloadPTime > u32GotoTimeMs ) )
            {
                //This is what we want
                //u32Ret = u32CurrentPayload;
                pstWMAIndexTableReturn->u32WMAPayloadPTime = pstWMAIndexTable[u32CurrentPayload].u32WMAPayloadPTime;
                break;
            }
            else
            {
                if ( ( u32CurrentPayload + 1 ) < stWmaInfo.u32TotalPayloads )
                {
                    u32CurrentPayload++;
                    if ( u32CurrentPayload > WMA_INDEX_TABLE_MAX_NUM )
                    {
                        u32CurrentPayload = u32OriginalPayload;
                        pstWMAIndexTableReturn->u32WMAPayloadPTime = 0;
                        pstWMAIndexTableReturn->u32WMAPayloadFilePos = 0xFFFFFFFF;
                        break;
                    }
                }
                else
                    break;
            }
        }
        else
        {
            if ( u32CurrentPayload >= 1 )
                u32CurrentPayload--;
            else
                break;
        }
    }


    if ( pstWMAIndexTableReturn->u32WMAPayloadFilePos != 0xFFFFFFFF )
        pstWMAIndexTableReturn->u32WMAPayloadFilePos = pstWMAIndexTable[u32CurrentPayload].u32WMAPayloadFilePos;

    return u32CurrentPayload;
}

void MApp_WMA_ProcessFfRew(void){

    U8 u8FakeKey;
    U32 u32CurrentPacket, u32CurrentPayload, u32SeekPoint = 0;
    U32 u32NewPlayTime = 0;
    ST_WMA_INDEX_TABLE stWMAIndexTableReturn;

    memset(&stWMAIndexTableReturn, 0, sizeof(stWMAIndexTableReturn));

    if (u8MusicFFFWMode == WMA_NORMAL_MODE)
    {
        return;
    }

    if (u8MusicFFFWMode == WMA_FF_Mode)
    {
        u8FakeKey = KEY_FF;
        msAPI_WMA_StopDecode();
    }

    else if (u8MusicFFFWMode == WMA_FW_Mode)
    {
        u8FakeKey = KEY_REWIND;
        msAPI_WMA_StopDecode();
    }
    else
    {
        return;
    }

    if(bProcessFfRew == FALSE)
    {
        u32WmaHeaderByteSent = 0;
        bProcessFfRew = TRUE;
    }

    WMA_DBG(printf("start u32CurrentPlayTime: %lu\n",stWmaInfo.u32CurrentPlayTime));

    if (u8FakeKey == KEY_FF)
    {
        if((stWmaInfo.u32CurrentPlayTime+2000)>(stWmaInfo.u32Duration*1000))
        {
            u32CurrentPayload = stWmaInfo.u32TotalPayloads;
            m_bCheckFftoEnd = TRUE;
        }
        else
        {
            LongLong u64Temp;
            u64Temp = LL_multU32((stWmaInfo.u32CurrentPlayTime+2000), stWmaInfo.u32TotalPayloads);
            u32CurrentPayload = LL_LongDivU32(&u64Temp, (stWmaInfo.u32Duration)).Lo/1000;
            u32CurrentPayload = MApp_WMA_GetPayloadIndexFromIndexTable(u32CurrentPayload, stWmaInfo.u32CurrentPlayTime+2000, &stWMAIndexTableReturn);
            u32SeekPoint = stWMAIndexTableReturn.u32WMAPayloadFilePos;
            u32NewPlayTime = stWMAIndexTableReturn.u32WMAPayloadPTime;

            WMA_DBG(printf("u32CurrentPayload: %lu \n",u32CurrentPayload));
        }
    }
    else // FB
    {
        if(stWmaInfo.u32CurrentPlayTime<2000)
        {
            //u32CurrentPacket=0;
            u32CurrentPayload = 0;
            u8MusicFFFWMode = WMA_NORMAL_MODE;
            if(bStop_After_FB_To_Begin_Wma)
            {
                enWmaState = STATE_WMA_WAIT;
            }
            else
            {
                MApp_WMA_Resume();
            }
        }
        else
        {
            LongLong u64Temp;
            u64Temp = LL_multU32((stWmaInfo.u32CurrentPlayTime-2000), stWmaInfo.u32TotalPayloads);
            u32CurrentPayload = LL_LongDivU32(&u64Temp, (stWmaInfo.u32Duration)).Lo/1000;
            u32CurrentPayload = MApp_WMA_GetPayloadIndexFromIndexTable(u32CurrentPayload, stWmaInfo.u32CurrentPlayTime-2000, &stWMAIndexTableReturn);
            u32SeekPoint = stWMAIndexTableReturn.u32WMAPayloadFilePos;
            u32NewPlayTime = stWMAIndexTableReturn.u32WMAPayloadPTime;
        }
    }

    stWmaInfo.u32SkipPayload = u32CurrentPayload;


#if ENABLE_ASF_PARSING
    if ( u32SeekPoint == 0xFFFFFFFF )
    {
        //not in payload table
        if (u8FakeKey == KEY_FF)
        {
            u32CurrentPacket =_u32CurrentPacket = (stWmaInfo.u32CurrentPlayTime+2000)*(stWmaInfo.u32TotalPacket)/(stWmaInfo.u32Duration*1000);
        }
        else
        {
            u32CurrentPacket = _u32CurrentPacket = (stWmaInfo.u32CurrentPlayTime-2000)*(stWmaInfo.u32TotalPacket)/(stWmaInfo.u32Duration*1000);
        }
        _u32CurrentPayload = 0;
        u32SeekPoint = stWmaInfo.u32HeaderSize+_u32CurrentPacket*stWmaInfo.u32PacketSize;
        WMA_DBG(printf("u32SeekPoint is 0xFFFFFFFF\n"));
    }
    else
    {
        //in payload table
        u32CurrentPacket = _u32CurrentPacket = u32CurrentPayload / stWmaInfo.u8FirstNumPayloads;
        _u32CurrentPayload = u32CurrentPayload % stWmaInfo.u8FirstNumPayloads;
        if ( _u32CurrentPayload != 0 )
        {
            _u32CurrentPacket++;
            u32CurrentPacket++;
        }
        WMA_DBG(printf("u32SeekPoint is not 0xFFFFFFFF\n"));
    }

    WMA_DBG(printf("u32CurrentPacket: %lu     u32CurrentPayload: %lu \n",u32CurrentPacket,u32CurrentPayload));


#else

    u32CurrentPacket = _u32CurrentPacket = (u32GotoTimeMs)*(stWmaInfo.u32TotalPacket)/(stWmaInfo.u32Duration*1000);
    u32CurrentPayload = _u32CurrentPayload = 0;
    u32SeekPoint = stWmaInfo.u32HeaderSize+_u32CurrentPacket*stWmaInfo.u32PacketSize;

#endif


    // re-calculate timer
    if (u32CurrentPacket == 0)
    {
        //because u32CurrentPacket=0 so stWmaInfo.u32CurrentPlayTime is 0

        stWmaInfo.u32CurrentPlayTime = 0;
        WMA_DBG(printf("because u32CurrentPacket=0 so stWmaInfo.u32CurrentPlayTime is 0"));
    }
    else if(u32NewPlayTime==0)
    {
        //not in payload table, use packet to calculate instead of payload to avoid VBR wma to go backward instead
        //ex: test1_WMA_v9_1pVBR-Quality_Q25_44kHz_2_NC.wma , press FF will go FB instead because
        //stWmaInfo.u32CurrentPlayTime is even smaller than we first entering this function, causing it to go FB instead.

        LongLong u64Temp;
        u64Temp = LL_multU32(stWmaInfo.u32Duration, 1000 * u32CurrentPacket);
        stWmaInfo.u32CurrentPlayTime = LL_LongDivU32(&u64Temp, stWmaInfo.u32TotalPacket).Lo;
        WMA_DBG(printf("after long div u32CurrentPlayTime: %lu\n",stWmaInfo.u32CurrentPlayTime));
    }
    else
    {
        //in payload, just use the time from table.

        stWmaInfo.u32CurrentPlayTime = u32NewPlayTime;
        WMA_DBG(printf("stWmaInfo.u32CurrentPlayTime from payload\n"));
    }
    WMA_DBG(printf("end u32CurrentPlayTime: %lu\n",stWmaInfo.u32CurrentPlayTime));
    stWmaInfo.u32PlayTimer = msAPI_Timer_GetTime0();


#if ENABLE_FILE_BM
    msAPI_DataStreamIO_MID_FS_Seek(u32SeekPoint);
#else
    msAPI_Steam_Seek(u32WmaFileHandle, u32SeekPoint);
#endif


    WMA_DBG(printf("u32SeekPoint: %lu\n\n", u32SeekPoint));
    _pu8ASFPayloadHeader[WMA_ASF_PACKET_HEADER_SIZE] = 0;
    _u32PayloadWriteLeft = 0;

}

#else   //disable WMA_INDEX_TABLE
void MApp_WMA_ProcessFfRew(void)
{
    U8 u8FakeKey;
    U32 u32CurrentPacket;

    if (u8MusicFFFWMode == WMA_NORMAL_MODE)
        return;

    if (u8MusicFFFWMode == WMA_FF_Mode)
    {
        u8FakeKey = KEY_FF;
        msAPI_WMA_StopDecode();
    }
    else if (u8MusicFFFWMode == WMA_FW_Mode)
    {
        u8FakeKey = KEY_REWIND;
        msAPI_WMA_StopDecode();
    }
    else
    {
        return;
    }

    if(bProcessFfRew == FALSE)
    {
        u32WmaHeaderByteSent = 0;
        bProcessFfRew = TRUE;
    }

    if (u8FakeKey == KEY_FF)
    {
        if((stWmaInfo.u32CurrentPlayTime+2000)>(stWmaInfo.u32Duration*1000))
        {
            u32CurrentPacket=stWmaInfo.u32TotalPacket;
            m_bCheckFftoEnd = TRUE;
        }
        else
        {
            LongLong u64Temp;
            u64Temp = LL_multU32((stWmaInfo.u32CurrentPlayTime+2000), stWmaInfo.u32TotalPacket);
            u32CurrentPacket = LL_LongDivU32(&u64Temp, (stWmaInfo.u32Duration)).Lo/1000;
        }
    }
    else // FB
    {
        if(stWmaInfo.u32CurrentPlayTime<2000)
        {
            u32CurrentPacket=0;
            u8MusicFFFWMode = WMA_NORMAL_MODE;
            if(bStop_After_FB_To_Begin_Wma)
            {
                enWmaState = STATE_WMA_WAIT;
            }
            else
            {
                MApp_WMA_Resume();
            }
        }
        else
        {
            LongLong u64Temp;
            u64Temp = LL_multU32((stWmaInfo.u32CurrentPlayTime-2000), stWmaInfo.u32TotalPacket);
            u32CurrentPacket = LL_LongDivU32(&u64Temp, (stWmaInfo.u32Duration)).Lo/1000;
        }
    }

    stWmaInfo.u32SkipPacket = u32CurrentPacket;
#if ENABLE_ASF_PARSING
    _u32CurrentPacket = u32CurrentPacket;
    _u32CurrentPayload = 0;
#endif

    // re-calculate timer
    if (u32CurrentPacket == 0)
    {
        stWmaInfo.u32CurrentPlayTime = 0;
    }
    else
    {
        LongLong u64Temp;
        u64Temp = LL_multU32(stWmaInfo.u32Duration, 1000*u32CurrentPacket);
        stWmaInfo.u32CurrentPlayTime = LL_LongDivU32(&u64Temp, stWmaInfo.u32TotalPacket).Lo;
    }
    stWmaInfo.u32PlayTimer = msAPI_Timer_GetTime0();
    msAPI_Steam_Seek(u32WmaFileHandle, stWmaInfo.u32HeaderSize+stWmaInfo.u32SkipPacket *stWmaInfo.u32PacketSize);

    //printf("stWmaInfo.u32SkipPacket=%lx %lx\n",stWmaInfo.u32SkipPacket,stWmaInfo.u32TotalPacket );

}
#endif

#if 0
BOOLEAN MApp_WMA_ProcessKey (void)
{
    BOOLEAN ret = FALSE;

    switch (u8KeyCode)
    {
        case KEY_EXIT:
            msAPI_WMA_StopDecode();
            u8MusicFFFWMode = WMA_NORMAL_MODE;
            enWmaState = STATE_WMA_EXIT;
            ret = TRUE;
            break;

        case KEY_POWER:
            MApp_WMA_CloseFile();
            u8MusicFFFWMode = WMA_NORMAL_MODE;
            enWmaState = STATE_WMA_INIT;
            enWmaRetVal = EXIT_WMA_TRAN_STANDBY;
            break;

        case KEY_VOLUME_MINUS:
        case KEY_VOLUME_PLUS:
            MApp_MEDIA_VolumeMenu();
            break;

        case KEY_PAUSE:
            if ((enWmaPlayStatus == WMA_STATUS_PLAYING)||(enWmaPlayStatus == WMA_STATUS_SCAN))
            {
                msAPI_WMA_PauseDecode();
                enWmaPlayStatus = WMA_STATUS_PAUSE;
                ret = TRUE;
            }
            u8MusicFFFWMode = WMA_NORMAL_MODE;
            break;

        case KEY_PLAY:
            if ((enWmaPlayStatus == WMA_STATUS_PAUSE)||(enWmaPlayStatus == WMA_STATUS_SCAN))
            {
                if(enWmaPlayStatus == WMA_STATUS_SCAN)
                {
                    msAPI_DataStreamIO_Seek(u32WmaFileHandle, 0);
                    u32WmaHeaderByteSent = 0;
                    u8MusicFFFWMode = WMA_NORMAL_MODE;
                    enWmaPlaySpeed = EN_WMA_SPEED_X1;
                }
                msAPI_WMA_StartDecode();
                if(eMPlayerStatus&MPLAYER_MUSIC_MUTE)
                {
                    MApp_Aud_EnableMute(TRUE);
                }
                else
                {
                    MApp_Aud_EnableMute(FALSE);
                }
                enWmaPlayStatus = WMA_STATUS_PLAYING;
                ret = TRUE;
            }
            u8MusicFFFWMode = WMA_NORMAL_MODE;
            break;

        case KEY_PREVIOUS:
            u8MusicFFFWMode = WMA_NORMAL_MODE;
            enWmaState = STATE_WMA_SKIP_PLAY_PREV;
            ret = TRUE;
            break;

        case KEY_NEXT:
            u8MusicFFFWMode = WMA_NORMAL_MODE;
            enWmaState = STATE_WMA_SKIP_PLAY_NEXT;
            ret = TRUE;
            break;

        case KEY_FF:
        case KEY_REWIND:
            if (enWmaState != STATE_WMA_INPUT)
                break;

            ret = TRUE;
            if (((u8MusicFFFWMode == WMA_FF_Mode) && (u8KeyCode == KEY_FF))
                    || ((u8MusicFFFWMode == WMA_FW_Mode) && (u8KeyCode == KEY_REWIND)))
            {
                if (enWmaPlaySpeed < EN_WMA_SPEED_MAX)
                {
                    enWmaPlaySpeed++;
                }
                else
                {
                    msAPI_DataStreamIO_Seek(u32WmaFileHandle, 0);
                    u32WmaHeaderByteSent = 0;
                    msAPI_WMA_StartDecode();
                    u8MusicFFFWMode = WMA_NORMAL_MODE;
                    enWmaPlaySpeed = EN_WMA_SPEED_X1;
                    enWmaPlayStatus = WMA_STATUS_PLAYING;
                }
                break;
            }

            enWmaPlayStatus = WMA_STATUS_SCAN;
            if (u8KeyCode == KEY_FF)
            {
                u8MusicFFFWMode = WMA_FF_Mode;
            }
            else
            {
                u8MusicFFFWMode = WMA_FW_Mode;
            }
            enWmaPlaySpeed = EN_WMA_SPEED_X2;
            bProcessFfRew = TRUE;
            break;

#if (ENABLE_MUSIC_PREVIEW)
        case KEY_UP:
        case KEY_DOWN:
#endif
        case KEY_STOP:
            msAPI_WMA_StopDecode();
            u8MusicFFFWMode = WMA_NORMAL_MODE;
            enWmaState = STATE_WMA_EXIT;
            enWmaPlayStatus = WMA_STATUS_STOP;
            ret = TRUE;
            g_u8MenuPageIndex = MENU_MEDIA_PLAYER_LIST;
            MApp_UiMenu_DrawMenuPage();
            break;

        default:
            break;

    }

    MApp_WMA_DrawStatus();
    u8KeyCode = KEY_NULL;
    return ret;
}
#endif

BOOLEAN MApp_WMA_Pause(void)
{
    u8MusicFFFWMode = WMA_NORMAL_MODE;

    if ((enWmaPlayStatus == WMA_STATUS_PLAYING)||(enWmaPlayStatus == WMA_STATUS_SCAN))
    {
        msAPI_WMA_PauseDecode();
        enWmaPlayStatus = WMA_STATUS_PAUSE;
        return TRUE;
    }
//    MApp_WMA_DrawStatus();

    return FALSE;
}

void MApp_WMA_Resume(void)
{
    if ((enWmaPlayStatus == WMA_STATUS_PAUSE)||(enWmaPlayStatus == WMA_STATUS_SCAN))
    {
        msAPI_WMA_StartDecode();
        enWmaPlayStatus = WMA_STATUS_PLAYING;
//        MApp_WMA_DrawStatus();

        if(msAPI_AUD_IsAudioMutedByUser())
        {
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
        }
        else
        {
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
        }
    }
}

static U8 u8String[6]; //remove klocwork warning message
U8 *MApp_WMA_GetInfoString(EN_WMA_INFO enWmaInfo, U8* pu8Length)
{
    U16 u16Tmp;
    U8* u8Ptr = NULL;

    switch(enWmaInfo)
    {
        case WMA_INFO_BITRATE:
            if(pu8Length != NULL)
            {
                *pu8Length = 0;
            }
            u16Tmp = (U16)(stWmaInfo.u32BitRate/1000);
            snprintf((char*)u8String, 5, "%dK", u16Tmp);
            u8Ptr = (U8*)u8String;
            break;

        case WMA_INFO_SAMPLINGRATE:
            if(pu8Length != NULL)
            {
                *pu8Length = 0;
            }
            u16Tmp = (U16)(stWmaInfo.u32SampleRate/1000);
            snprintf((char*)u8String, 5, "%dK", u16Tmp);
            u8Ptr = (U8*)u8String;
            break;

        case WMA_INFO_ALBUM:
            if(pu8Length != NULL)
            {
                if(stWmaInfo.u16AlbumLength < sizeof(stWmaInfo.u8Album))
                {
                    *pu8Length = stWmaInfo.u16AlbumLength;
                }
                else
                {
                    *pu8Length = sizeof(stWmaInfo.u8Album);
                }
            }
            u8Ptr = (U8*)stWmaInfo.u8Album;
            break;

        case WMA_INFO_TITLE:
            if(pu8Length != NULL)
            {
                if(stWmaInfo.u16TitleLength < sizeof(stWmaInfo.u8Title))
                {
                    *pu8Length = stWmaInfo.u16TitleLength;
                }
                else
                {
                    *pu8Length = sizeof(stWmaInfo.u8Title);
                }
            }
            u8Ptr = (U8*)stWmaInfo.u8Title;
            break;

        case WMA_INFO_ARTIST:
            if(pu8Length != NULL)
            {
                if(stWmaInfo.u16AuthorLength < sizeof(stWmaInfo.u8Author))
                {
                    *pu8Length = stWmaInfo.u16AuthorLength;
                }
                else
                {
                    *pu8Length = sizeof(stWmaInfo.u8Author);
                }
            }
            u8Ptr = (U8*)stWmaInfo.u8Author;
            break;

        case WMA_INFO_YEAR:
            if(pu8Length != NULL)
            {
                if(stWmaInfo.u16YearLength < sizeof(stWmaInfo.u8Year))
                {
                    *pu8Length = stWmaInfo.u16YearLength;
                }
                else
                {
                    *pu8Length = sizeof(stWmaInfo.u8Year);
                }
            }
            u8Ptr = stWmaInfo.u8Year;
            break;

        case WMA_INFO_CHECK_FF_FB:
            if(pu8Length != NULL)
            {
                *pu8Length = 0;
            }
            u8Ptr =  (U8*)&stWmaInfo.bCheckFfFb;
            break;

        default:
            if(pu8Length != NULL)
            {
                *pu8Length = 0;
            }
            break;
    }

    return u8Ptr;
}

EN_RET MApp_WMA_Main(void)
{
    enWmaRetVal = EXIT_WMA_DECODING;

#if (PRINT_WMA_STATE)
    if (enPreWmaState != enWmaState)
    {
        (printf("Wma state: %bu\n", enWmaState));
        enPreWmaState = enWmaState;
    }
#endif

    switch(enWmaState)
    {
        case STATE_WMA_STANDBY:
            enWmaPlayStatus = WMA_STATUS_STOP;
            enWmaRetVal = EXIT_WMA_TRAN_STANDBY;
            break;

        case STATE_WMA_INIT:
            WMA_DBG(printf("WMA_INIT\n"));
            enWmaPlayStatus = WMA_STATUS_PLAYING;
//            MApp_WMA_DrawStatus();

            if (MApp_WMA_Initial() == FALSE)
            {
                enWmaState = STATE_WMA_EXIT;
                break;
            }
            enWmaState = STATE_WMA_OPEN_FILE;
            u8MusicFFFWMode = WMA_NORMAL_MODE;
            enWmaPlaySpeed = EN_WMA_SPEED_X1;
            enWmaRetVal = EXIT_WMA_INIT;
            if(stGenSetting.g_SysSetting.fSPDIFMODE == 0)
                MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_PCM);
            else if(stGenSetting.g_SysSetting.fSPDIFMODE == 1)
                MApi_AUDIO_SPDIF_SetMode(MSAPI_AUD_SPDIF_NONPCM);
            break;

        case STATE_WMA_OPEN_FILE:
            WMA_DBG(printf("STATE_WMA_OPEN_FILE\n"););
            if (MApp_WMA_OpenFile() == FALSE)
            {
                enWmaState = STATE_WMA_EXIT;
                break;
            }
            msAPI_WMA_StartDecode();
            enWmaState = STATE_WMA_INPUT;
            enWmaRetVal = EXIT_WMA_INPUT;
#if ENABLE_FILE_BM

            U8 *pu8MidFSBuf = (U8 *)_PA2VA(((WMA_INFO_READ_MEMORY_TYPE & MIU1) ? (WMA_INFO_READ_ADR | MIU_INTERVAL) : (WMA_INFO_READ_ADR)));

            msAPI_DataStreamIO_MID_FS_RegisterBuffer(pu8MidFSBuf);
#endif
            u32FfRewTimer = msAPI_Timer_GetTime0();
#if 0//(ENABLE_LAST_MEMORY==1)&&ENABLE_LAST_MEMORY_ENABLE_MUSIC
            if ((m_u8LastMemoryCheck==TRUE) && (m_u8LastMemorySearchHit==TRUE))
            {
                U32 u32ResumeTimeMs;
                MApp_MPlayer_LastMemory_GetResumePos(&u32ResumeTimeMs, NULL, NULL);
                MApp_Music_ProcessTimeOffset(u32ResumeTimeMs);
                WMA_DBG(printf("MApp_WMA_Main, LastMemory, idx=%d, time=%dms\n", m_u32LastMemoryCurIdx, u32ResumeTimeMs););
            }
#endif
            break;

        case STATE_WMA_INPUT:
            //WMA_DBG(printf("STATE_WMA_INPUT\n"););
            if (stWmaInfo.bCheckFfFb && (msAPI_Timer_DiffTimeFromNow(u32FfRewTimer) > (U32)(900 / (1 << (enWmaPlaySpeed - EN_WMA_SPEED_X2))))
                    && ((u8MusicFFFWMode == WMA_FF_Mode)
                        || (u8MusicFFFWMode == WMA_FW_Mode)))
            {
                MApp_WMA_ProcessFfRew();
                u32FfRewTimer = msAPI_Timer_GetTime0();
                if(u8MusicFFFWMode == WMA_FF_Mode && m_bCheckFftoEnd == TRUE)
                {
                    m_bCheckFftoEnd = FALSE;
                    msAPI_Music_StopDecode();
                    enWmaState = STATE_WMA_WAIT;
                    u8MusicFFFWMode = WMA_NORMAL_MODE;
                }
            }
            else
            {
                if(msAPI_Music_AudioIsSupported() != 0)
                {
                    enWmaState = STATE_WMA_EXIT;
                    break;
                }
                MApp_WMA_Input();
            }
            MApp_WMA_UpdatePlayTime();
            break;

        case STATE_WMA_WAIT_DECODE_DONE:
            WMA_DBG(printf("STATE_WMA_WAIT_DECODE_DONE\n");)
            if (msAPI_WMA_CheckPlayDone() && (msAPI_Music_GetPCMBufferSize2(stWmaInfo.u32BitRate,stWmaInfo.u32SampleRate) == 0))
            {
                enWmaState = STATE_WMA_WAIT;
                u32WmaShowTimer = msAPI_Timer_GetTime0();
            }
            break;

        case STATE_WMA_WAIT:
            WMA_DBG(printf("STATE_WMA_WAIT\n");)
            if (enWmaPlayStatus != WMA_STATUS_PAUSE
            &&  msAPI_Timer_DiffTimeFromNow(u32WmaShowTimer) > u32WmaTimeOutDefault)
            {
                MApp_WMA_CloseFile();
                enWmaState = STATE_WMA_STANDBY;
                enWmaRetVal = EXIT_WMA_WAIT;
            }
            break;

        case STATE_WMA_SKIP_PLAY_NEXT:
            msAPI_WMA_StopDecode();
            MApp_WMA_CloseFile();
//            MApp_WMA_DrawStatus();
            enWmaPlayStatus = WMA_STATUS_STOP;
            enWmaState = STATE_WMA_INIT;
            enWmaRetVal = EXIT_WMA_WAIT;
            break;

        case STATE_WMA_SKIP_PLAY_PREV:
            msAPI_WMA_StopDecode();
            MApp_WMA_CloseFile();
//            MApp_WMA_DrawStatus();
            enWmaPlayStatus = WMA_STATUS_STOP;
            enWmaState = STATE_WMA_INIT;
            enWmaRetVal = EXIT_WMA_WAIT_PLAY_PREV;
            break;

        case STATE_WMA_EXIT:
            u8KeyCode = KEY_NULL;
            enWmaPlayStatus = WMA_STATUS_STOP;
            enWmaState = STATE_WMA_STANDBY;
            enWmaRetVal = EXIT_WMA_EXIT;
            MApp_WMA_CloseFile();
//            MApp_WMA_DrawStatus();
            break;

        default:
            u8KeyCode = KEY_NULL;
            enWmaState = STATE_WMA_STANDBY;
            enWmaRetVal = EXIT_WMA_EXIT;
//            MApp_WMA_DrawStatus();
            break;
    }

    if (MApp_WMA_TimeOutCheck() == TRUE && enWmaState!= STATE_WMA_STANDBY)
    {
        //ported from Kingwok to fix music playback abnormal after played "bad file"
        if(enWmaState == STATE_WMA_INPUT)
        {
            msAPI_WMA_StopDecode();
            msAPI_AUD_SW_Reset();
        }
        enWmaState = STATE_WMA_EXIT;
        WMA_DBG(printf("WMA: Abnormal\n"));
        _enWMA_ErrCode = E_WMA_ERR_DECODE_FAILURE;
    }

    return enWmaRetVal;
}

#if ENABLE_WMA_INDEX_TABLE

static BOOLEAN _MApp_WMA_TimeOffset(U32 u32GotoTimeMs)
{
    U32 u32SeekPoint = 0;

    ST_WMA_INDEX_TABLE stWMAIndexTableReturn;
    memset(&stWMAIndexTableReturn, 0, sizeof(stWMAIndexTableReturn));

    MS_DEBUG_MSG(printf("WMA goto time!!\n"));

    if(bProcessFfRew == FALSE)
    {
        u32WmaHeaderByteSent = 0;
        bProcessFfRew = TRUE;
    }

    stWmaInfo.u32SkipPayload = (u32GotoTimeMs)*(stWmaInfo.u32TotalPayloads)/(stWmaInfo.u32Duration*1000);

#if ENABLE_ASF_PARSING

    stWmaInfo.u32SkipPayload = MApp_WMA_GetPayloadIndexFromIndexTable(stWmaInfo.u32SkipPayload, u32GotoTimeMs, &stWMAIndexTableReturn);
    u32SeekPoint = stWMAIndexTableReturn.u32WMAPayloadFilePos;

    if ( u32SeekPoint == 0xFFFFFFFF )
    {
        _u32CurrentPacket = (u32GotoTimeMs)*(stWmaInfo.u32TotalPacket)/(stWmaInfo.u32Duration*1000);

        _u32CurrentPayload = 0;

        u32SeekPoint = stWmaInfo.u32HeaderSize+_u32CurrentPacket*stWmaInfo.u32PacketSize;
    }
    else
    {
        //u32CurrentPacket = _u32CurrentPacket = stWmaInfo.u32SkipPayload / stWmaInfo.u8FirstNumPayloads;
        //u32CurrentPayload = _u32CurrentPayload = stWmaInfo.u32SkipPayload % stWmaInfo.u8FirstNumPayloads;
        _u32CurrentPacket = stWmaInfo.u32SkipPayload / stWmaInfo.u8FirstNumPayloads;
        _u32CurrentPayload = stWmaInfo.u32SkipPayload % stWmaInfo.u8FirstNumPayloads;

        if ( _u32CurrentPayload != 0 )
        {
            _u32CurrentPacket++;
        }
    }
#else
    _u32CurrentPacket = (u32GotoTimeMs)*(stWmaInfo.u32TotalPacket)/(stWmaInfo.u32Duration*1000);

    _u32CurrentPayload = 0;

    u32SeekPoint = stWmaInfo.u32HeaderSize+_u32CurrentPacket*stWmaInfo.u32PacketSize;
#endif

#if ENABLE_FILE_BM
    msAPI_DataStreamIO_MID_FS_Seek(u32SeekPoint);
#else
    msAPI_Steam_Seek(u32WmaFileHandle, u32SeekPoint);
#endif

    _pu8ASFPayloadHeader[WMA_ASF_PACKET_HEADER_SIZE] = 0;
    _u32PayloadWriteLeft = 0;

    return TRUE;
}

#else
static BOOLEAN _MApp_WMA_TimeOffset(U32 u32GotoTimeMs)
{
    MS_DEBUG_MSG(printf("WMA goto time!!\n"));

    if(bProcessFfRew == FALSE)
    {
        u32WmaHeaderByteSent = 0;
        bProcessFfRew = TRUE;
    }

    stWmaInfo.u32SkipPacket = (u32GotoTimeMs)*(stWmaInfo.u32TotalPacket)/(stWmaInfo.u32Duration*1000);

#if ENABLE_ASF_PARSING
    _u32CurrentPacket = stWmaInfo.u32SkipPacket;
    _u32CurrentPayload = 0;
#endif
    msAPI_Steam_Seek(u32WmaFileHandle, stWmaInfo.u32HeaderSize+stWmaInfo.u32SkipPacket*stWmaInfo.u32PacketSize);

    return TRUE;
}
#endif

BOOLEAN MApp_WMA_ProcessTimeOffset(U32 u32GotoTimeMs)
{
    BOOLEAN bRet = FALSE;

    if(enWmaState == STATE_WMA_WAIT_DECODE_DONE)
    {
        enWmaState = STATE_WMA_INPUT;
    }
    else if(enWmaState != STATE_WMA_INPUT)
    {
        return FALSE;
    }

    if(stWmaInfo.u32Duration == 0 || (u32GotoTimeMs > stWmaInfo.u32Duration*1000))
    {
        return FALSE;
    }

    //printf("Total Time:%lu , Go to time:%lu\n",stWmaInfo.u32Duration,u32GotoTimeMs);

    msAPI_WMA_StopDecode();
    msAPI_Timer_Delayms(50); // this delay is critical, can't be too small

    bRet = _MApp_WMA_TimeOffset(u32GotoTimeMs);

    if(bRet)
    {
        stWmaInfo.u32CurrentPlayTime = u32GotoTimeMs;
        stWmaInfo.u32PlayTimer = msAPI_Timer_GetTime0();
    }

    msAPI_WMA_StartDecode();

    return bRet;
}

BOOLEAN MApp_WMA_FastForwardBackward(BOOLEAN bForward, EN_WMA_SPEED eSpeed)
{
    if(enWmaState == STATE_WMA_WAIT_DECODE_DONE)
    {
        enWmaState = STATE_WMA_INPUT;
    }
    else if(enWmaState != STATE_WMA_INPUT)
    {
        return FALSE;
    }

    if(bForward && eSpeed == EN_WMA_SPEED_X1)
    {
        msAPI_WMA_StartDecode();
        u8MusicFFFWMode = WMA_NORMAL_MODE;
        enWmaPlaySpeed = EN_WMA_SPEED_X1;
        enWmaPlayStatus = WMA_STATUS_PLAYING;
        return TRUE;
    }

    if (((u8MusicFFFWMode == WMA_FF_Mode) && (bForward))
            || ((u8MusicFFFWMode == WMA_FW_Mode) && (!bForward)))
    {
        if (enWmaPlaySpeed < EN_WMA_SPEED_MAX)
        {
            enWmaPlaySpeed++;
        }
        else
        {
            return FALSE;
        }
        return TRUE;
    }

    //enWmaPlayStatus = WMA_STATUS_SCAN;
    if (enWmaPlayStatus == WMA_STATUS_PLAYING)
    {
        msAPI_WMA_PauseDecode();
    }

    enWmaPlayStatus = WMA_STATUS_SCAN;

    if (bForward)
    {
        u8MusicFFFWMode = WMA_FF_Mode;
    }
    else
    {
        u8MusicFFFWMode = WMA_FW_Mode;
    }
    enWmaPlaySpeed = EN_WMA_SPEED_X2;

    return TRUE;
}

EN_WMA_ERRCODE MApp_Wma_GetErrCode(void)
{
    return _enWMA_ErrCode;
}

void MApp_Wma_StopAfterFBBegin(BOOLEAN bEnabled)
{
   bStop_After_FB_To_Begin_Wma = bEnabled;
}

//******************************************************************************
/// This function will set state of wma music to init state for initializing.
/// @param  N/A
/// @return N/A
//******************************************************************************
void MApp_Wma_Init(void)
{
    msAPI_WMA_StopDecode();
    MApp_WMA_CloseFile();
    enWmaState= STATE_WMA_INIT;
}


BOOLEAN MApp_WMA_Probe(U32 u32Hdl, ST_WMA_PROBE_INFO *pstWmaProbeInfo, U32 u32InfoAttr)
{
    if(pstWmaProbeInfo == NULL)
    {
        WMA_DBG(printf(" ---> MApp_WMA_Probe() Error  !!!  ( pstWmaProbeInfo == NULL ) \n"));
        return FALSE;
    }
    if(u32Hdl == INVALID_DATA_STREAM_HDL)
    {
        WMA_DBG(printf("u32Hdl is INVALID\n"));
        return FALSE;
    }
    U32 u32FileHandle = u32Hdl;
    ST_WMA_INFO stWmaInfoLocal;
    U8 *pu8Data,*pu8DataTmp;
    U32 u32bufferIndex=0,u32Index=0;
    BOOLEAN bRet = FALSE;

    memset(pstWmaProbeInfo, 0, sizeof(ST_WMA_PROBE_INFO));
    memset(&stWmaInfoLocal, 0, sizeof(ST_WMA_INFO));

    stWmaInfoLocal.u32FileSize = msAPI_DataStreamIO_Length(u32FileHandle);

    //Use memory allocate instead of WMA_INFO_READ because wma normal play BM is also using it.
    pu8Data = (U8*)msAPI_Memory_Allocate(MAX(WMA_PROBE_READ_LEN,WMA_HEADER_READ_LEN),BUF_ID_FILEBROWER);
    if(pu8Data==NULL)
    {
        WMA_INFO(printf("memory allocate fail at wma probe\n"));
        return FALSE;
    }

    U32 u32pu8DataPhyAddr = _VA2PA((U32)&pu8Data[0]);


    #define WMA_OBJECT_GUID_LENGTH 16
    const U8 u8headerObjectGUID[WMA_OBJECT_GUID_LENGTH] = {0x30,0x26,0xB2,0x75,0x8E,0x66,0xCF,0x11,0xA6,0xD9,0x00,0xAA,0x00,0x62,0xCE,0x6C};
    const U8 u8StreamObjectGUID[WMA_OBJECT_GUID_LENGTH] = {0x91,0x07,0xDC,0xB7,0xB7,0xA9,0xCF,0x11,0x8E,0xE6,0x00,0xCA,0x0C,0x20,0x53,0x65};
    const U8 u8AudioStreamGUID[WMA_OBJECT_GUID_LENGTH]  = {0x40,0x9E,0x69,0xF8,0x4D,0x5B,0xCF,0x11,0xA8,0xFD,0x00,0x80,0x5F,0x5C,0x44,0x2B};
    const U8 u8FileObjectGUID[WMA_OBJECT_GUID_LENGTH]   = {0xA1,0xDC,0xAB,0x8C,0x47,0xA9,0xCF,0x11,0x8E,0xE4,0x00,0xC0,0x0C,0x20,0x53,0x65};
    const U8 u8ExContentObjectGUID[WMA_OBJECT_GUID_LENGTH]={0x40,0xA4,0xD0,0xD2,0x07,0xE3,0xD2,0x11,0x97,0xF0,0x00,0xA0,0xC9,0x5E,0xA8,0x50};

    msAPI_Steam_Seek(u32FileHandle,0);
    msAPI_DataStreamIO_Read(u32FileHandle,(void *)u32pu8DataPhyAddr,WMA_HEADER_READ_LEN);

    for(u32bufferIndex=0;u32bufferIndex < (WMA_HEADER_READ_LEN - WMA_OBJECT_GUID_LENGTH); u32bufferIndex++)
    {
        pu8DataTmp = pu8Data + u32bufferIndex;

        if(memcmp(pu8DataTmp,u8headerObjectGUID,sizeof(u8headerObjectGUID))==0)
        {
            stWmaInfoLocal.bHeaderFound = TRUE;
            memcpy(&stWmaInfoLocal.u32HeaderSize,&pu8Data[u32bufferIndex+WMA_OBJECT_GUID_LENGTH],4);
            break;
        }

    }
    WMA_INFO(printf("stWmaInfoLocal.u32HeaderSize = 0x%lx\n",stWmaInfoLocal.u32HeaderSize));

    U32 u32ExContentOffset=0;
    U64 u64ExContentObjectSize = 0;
    U16 u16ContentDescriptionCount=0;

    #define EX_CONTENT_OBJECT_SIZE_LENGTH 8
    #define EX_CONTENT_OBJECT_DISCRIPTOR_COUNT_LENGTH 2
    #define STREAM_OBJECT_SIZE_LENGTH 8

    u32Index = 0;
    u32bufferIndex = u32bufferIndex + WMA_OBJECT_GUID_LENGTH;

    if(stWmaInfoLocal.bHeaderFound)
    {
        while( u32Index < stWmaInfoLocal.u32HeaderSize )
        {
            if((u32bufferIndex+0x100) > (WMA_PROBE_READ_LEN-1))
            {
                u32Index = u32Index + u32bufferIndex;
                msAPI_Steam_Seek(u32FileHandle, u32Index);
                msAPI_DataStreamIO_Read(u32FileHandle,(void *)u32pu8DataPhyAddr,WMA_PROBE_READ_LEN);
                u32bufferIndex = 0;
            }

            if((stWmaInfoLocal.bStreamFound==FALSE))
            {
                //Stream Properties Object
                //|-------------------------------------------------------------------------------------------------------------------------|
                //| GUID     | Object size | Stream Type | ........ | Type Specific Data Length | ......... | Type Specific Data | ........ |
                //|(16 byte) | (8 byte)    | (16 byte)   | (24 byte)| (4 byte)                  | (10 byte) |   (N byte)         | (N byte) |
                //|-------------------------------------------------------------------------------------------------------------------------|
                //ASF_Stream_Properties_Object guid:B7DC0791-A9B7-11CF-8EE6-00C00C205365

                //Type Specific Data for ASF Audio Media
                //|------------------------------------------------|
                //| ........  | Sample Rate | Byte Rate | ........ |
                //|(4 byte)   | (4 byte)    | (4 byte)  | (N byte) |
                //|------------------------------------------------|
                //ASF_Audio_Media guid:F8699E40-5B4D-11CF-A8FD-00805F5C442B

                pu8DataTmp = pu8Data + u32bufferIndex;
                U8 *pu8DataTmp2 = pu8Data+u32bufferIndex+ WMA_OBJECT_GUID_LENGTH + STREAM_OBJECT_SIZE_LENGTH;

                if((memcmp(pu8DataTmp,u8StreamObjectGUID,sizeof(u8StreamObjectGUID))==0)  && (memcmp(pu8DataTmp2,u8AudioStreamGUID,sizeof(u8AudioStreamGUID))==0))
                {
                    stWmaInfoLocal.bStreamFound = TRUE;
                    memcpy(&stWmaInfoLocal.u32SampleRate,&pu8Data[u32bufferIndex+0x52],4);
                    memcpy(&stWmaInfoLocal.u32ByteRate,&pu8Data[u32bufferIndex+0x56],4);
                    stWmaInfoLocal.u32BitRate = stWmaInfoLocal.u32ByteRate*8; //ByteRate

                    U64 u64StreamObjectSize = 0;
                    memcpy(&u64StreamObjectSize,&pu8Data[u32bufferIndex+WMA_OBJECT_GUID_LENGTH],8);
                    u32bufferIndex = u32bufferIndex+ WMA_OBJECT_GUID_LENGTH + EX_CONTENT_OBJECT_SIZE_LENGTH + (U32)u64StreamObjectSize;
                }
            }

            if(stWmaInfoLocal.bExContentFound==FALSE) // it is optional
            {
                //Extended Content Description Object
                //|-----------------------------------------------------------------|
                //| GUID     | Object size | Content Descriptor number | Descriptors|
                //|(16 byte) | (8 byte)    | (2 byte)                  | (N byte)   |
                //|-----------------------------------------------------------------|

                pu8DataTmp = pu8Data + u32bufferIndex;
                if(memcmp(pu8DataTmp,u8ExContentObjectGUID,sizeof(u8ExContentObjectGUID))==0)
                {
                    WMA_INFO(printf("found Extended Content Description Object\n"));
                    u32ExContentOffset = u32Index + u32bufferIndex;  //save ExContent Object offset for later use
                    WMA_INFO(printf("u32ExContentOffset: 0x%x u32Index:0x%x  u32bufferIndex:0x%x\n",u32ExContentOffset,u32Index,u32bufferIndex));
                    memcpy(&u64ExContentObjectSize, &pu8Data[u32bufferIndex+WMA_OBJECT_GUID_LENGTH],EX_CONTENT_OBJECT_SIZE_LENGTH);
                    memcpy(&u16ContentDescriptionCount, &pu8Data[u32bufferIndex+WMA_OBJECT_GUID_LENGTH+EX_CONTENT_OBJECT_SIZE_LENGTH],EX_CONTENT_OBJECT_DISCRIPTOR_COUNT_LENGTH);
                    WMA_INFO(printf("u32ExContentOffset: 0x%x  u64ExContentObjectSize:0x%x\n",u32ExContentOffset,(U32)u64ExContentObjectSize));
                    stWmaInfoLocal.bExContentFound= TRUE;
                    u32bufferIndex = u32bufferIndex + WMA_OBJECT_GUID_LENGTH + EX_CONTENT_OBJECT_SIZE_LENGTH + (U32)u64ExContentObjectSize;
                }
            }

            if((stWmaInfoLocal.bFilePropertiesFound==FALSE) && (u32InfoAttr==E_MUSIC_INFO_DURATION))
            {
                //File Properties Object
                //|-------------------------------------------------------------------------------------------------|
                //| GUID     | Object size | ........  | Play Duration       |  Send Duration | Preroll  | ........ |
                //|(16 byte) | (8 byte)    | (40 byte) |(8 byte 100 nanosec) | (8 byte)       | (8 byte) | (8 byte) |
                //|-------------------------------------------------------------------------------------------------|

                pu8DataTmp = pu8Data + u32bufferIndex;
                if(memcmp(pu8DataTmp,u8FileObjectGUID,sizeof(u8FileObjectGUID))==0)
                {
                    stWmaInfoLocal.bFilePropertiesFound = TRUE;
                    U64 u64Duration = 0;
                    memcpy(&u64Duration,&pu8Data[u32bufferIndex+72],8);
                    WMA_INFO(printf("u64Duration: 0x%x  pu8Data:0x%02x 0x%02x 0x%02x 0x%02x\n",(U32)u64Duration,pu8Data[u32bufferIndex+72],pu8Data[u32bufferIndex+72+1],pu8Data[u32bufferIndex+72+2],pu8Data[u32bufferIndex+72+3]));
                    u64Duration = u64Duration / 10000000;  //100 nanosecond to second
                    stWmaInfoLocal.u32Duration = (U32)u64Duration;

                    //if send duration incorrect, use play duration subtract  preroll.
                    if(stWmaInfoLocal.u32Duration == 0)
                    {
                        U64 u64PlayDuration, u64PreRoll;
                        //Specifies the time needed to play the file in 100-nanosecond units.
                        memcpy(&u64PlayDuration,&pu8Data[u32bufferIndex+64],8);
                        u64PlayDuration = u64PlayDuration / 10000000; //100 nanosecond to second
                        //Specifies the amount of time to buffer data before starting to play the file, in millisecond units.
                        memcpy(&u64PreRoll,&pu8Data[u32bufferIndex+80],8);   //in millisecond
                        u64PreRoll = u64PreRoll / 1000;  //from millisecond to second
                        if(u64PlayDuration > u64PreRoll)
                        {
                            stWmaInfoLocal.u32Duration = (U32)(u64PlayDuration - u64PreRoll);
                        }
                    }

                    if(stWmaInfoLocal.u32Duration == 0)
                    {
                        stWmaInfoLocal.u32Duration = 0xFFFFFFFF;
                    }
                    WMA_INFO(printf("stWmaInfoLocal.u32Duration:%lu\n",stWmaInfoLocal.u32Duration));

                    U64 u64FileObjectSize = 0;
                    memcpy(&u64FileObjectSize,&pu8Data[u32bufferIndex+WMA_OBJECT_GUID_LENGTH],8);
                    u32bufferIndex = u32bufferIndex + WMA_OBJECT_GUID_LENGTH + EX_CONTENT_OBJECT_SIZE_LENGTH + (U32)u64FileObjectSize;
                }
            }

            if(stWmaInfoLocal.bStreamFound && stWmaInfoLocal.bExContentFound &&(u32InfoAttr!=E_MUSIC_INFO_DURATION))
            {
                break;
            }
            else if(stWmaInfoLocal.bFilePropertiesFound &&stWmaInfoLocal.bStreamFound &&stWmaInfoLocal.bExContentFound)
            {
                break;
            }

            u32bufferIndex++;

        }//end of while loop


        //Extended Content Description Object
        //|-----------------------------------------------------------------|
        //| GUID     | Object size | Content Descriptor number | Descriptors|
        //|(16 byte) | (8 byte)    | (2 byte)                  | (N byte)   |
        //|-----------------------------------------------------------------|
        //parse ExContent
        if(stWmaInfoLocal.bExContentFound== TRUE  && u16ContentDescriptionCount!=0)
        {
            u32Index = u32ExContentOffset + WMA_OBJECT_GUID_LENGTH + EX_CONTENT_OBJECT_SIZE_LENGTH + EX_CONTENT_OBJECT_DISCRIPTOR_COUNT_LENGTH; //point to descriptor head
            msAPI_Steam_Seek(u32FileHandle, u32Index);
            msAPI_DataStreamIO_Read(u32FileHandle,(void *)u32pu8DataPhyAddr,WMA_PROBE_READ_LEN);
            u32bufferIndex = 0;
            U16 u16DescriptorIndex = 0;
            U16 u16DesNameLen = 0;
            U16 u16DataLen = 0;
            U32 u32PictureSize = 0;

            const U8 u8AlbumPicture[22] = {'W',0x00,'M',0x00,'/',0x00,'P',0x00,'i',0x00,'c',0x00,'t',0x00,'u',0x00,'r',0x00,'e',0x00,0x00,0x00}; //extended content description name: WM/Picture

            #define DESCRIPTOR_NAME_LENGTH 2
            #define WMPICTURE_VALUE_DATA_TYPE_LENGTH 2
            #define WMPICTURE_VALUE_LENGTH 2
            #define WMPICTURE_TYPE_LENGTH 1
            #define WMPICTURE_DATA_LENGTH 4

            for(u16DescriptorIndex = 0; u16DescriptorIndex< u16ContentDescriptionCount; u16DescriptorIndex++)
            {
                //Descriptor Structure
                //|-----------------------------------------------------------------|
                //| Name len |  Name    | data type | data length | data value      |
                //| (2 byte) | (n byte) | (2 byte)  | (2 byte)    | (N byte)        |
                //|-----------------------------------------------------------------|

                if((u32bufferIndex+0x100) > (WMA_PROBE_READ_LEN-1))    //256 byte buffer space for safety
                {
                    u32Index = u32Index + u32bufferIndex;
                    msAPI_Steam_Seek(u32FileHandle, u32Index);
                    msAPI_DataStreamIO_Read(u32FileHandle,(void *)u32pu8DataPhyAddr,WMA_PROBE_READ_LEN);
                    u32bufferIndex = 0;
                }

                //Get Descriptor Name Length,
                memcpy(&u16DesNameLen, &pu8Data[u32bufferIndex],DESCRIPTOR_NAME_LENGTH);

                //Check if WM/Picture
                if( u16DesNameLen == 22 )
                {
                    pu8DataTmp = (pu8Data + u32bufferIndex + DESCRIPTOR_NAME_LENGTH);
                    if(memcmp(pu8DataTmp,u8AlbumPicture,sizeof(u8AlbumPicture))==0)
                    {

                        //WMPicture Descriptor Structure
                        //|-------------------------------------------------------------------------------------------------------------------------|
                        //| Name len |  Name    | data type | data length |                                data value                               |
                        //| (2 byte) |(22 byte) | (2 byte)  | (2 byte)    |                                 (N byte)                                |
                        //|-----------------------------------------------|-------------------------------------------------------------------------|
                        //                                                |  Picture Type | Picture Length | MIME TYPE | Description | Picture Data |
                        //                                                |  (1 byte)     | (4 byte)       | (N byte)  | (N byte)    | (N byte)     |
                        //                                                |-------------------------------------------------------------------------|

                        pu8DataTmp = (pu8Data+u32bufferIndex + DESCRIPTOR_NAME_LENGTH + u16DesNameLen + WMPICTURE_VALUE_DATA_TYPE_LENGTH + WMPICTURE_VALUE_LENGTH + WMPICTURE_TYPE_LENGTH );
                        memcpy(&u32PictureSize,pu8DataTmp,WMPICTURE_DATA_LENGTH);
                        WMA_INFO(printf("pu8DataTmp: 0x%02x  0x%02x  0x%02x  0x%02x\n",pu8DataTmp[0],pu8DataTmp[1],pu8DataTmp[2],pu8DataTmp[3]));
                        pstWmaProbeInfo->u32PicSize = u32PictureSize;
                        memcpy(&u16DataLen, &pu8Data[u32bufferIndex+DESCRIPTOR_NAME_LENGTH+u16DesNameLen + WMPICTURE_VALUE_DATA_TYPE_LENGTH],WMPICTURE_VALUE_LENGTH);
                        U32 u32DataLen = (U32)u16DataLen;
                        pstWmaProbeInfo->u32PicOffset = u32Index + u32bufferIndex + DESCRIPTOR_NAME_LENGTH + u16DesNameLen + WMPICTURE_VALUE_DATA_TYPE_LENGTH + WMPICTURE_VALUE_LENGTH + WMPICTURE_TYPE_LENGTH + (u32DataLen-u32PictureSize);
                        WMA_INFO(printf("u32PicOffset:0x%0x, u32PicSize:0x%0x\n",pstWmaProbeInfo->u32PicOffset,pstWmaProbeInfo->u32PicSize));
                        WMA_INFO(printf("u32Index:0x%x  u32bufferIndex:0x%x  u32DataLen:0x%x  u32PictureSize:0x%x\n",u32Index,u32bufferIndex,u32DataLen,u32PictureSize));
                        WMA_INFO(printf("break at u16DescriptorIndex:%d\n",u16DescriptorIndex));
                        break;
                    }

                }//end of WM/Picture

                //Move to next descriptor
                if((u32bufferIndex + DESCRIPTOR_NAME_LENGTH + u16DesNameLen+ 0x100) > (WMA_PROBE_READ_LEN-1))  //256 byte buffer space for safety
                {
                    u32Index = u32Index + u32bufferIndex + DESCRIPTOR_NAME_LENGTH + u16DesNameLen;
                    msAPI_Steam_Seek(u32FileHandle, u32Index);
                    msAPI_DataStreamIO_Read(u32FileHandle,(void *)u32pu8DataPhyAddr,WMA_PROBE_READ_LEN);
                    memcpy(&u16DataLen, &pu8Data[2],WMPICTURE_VALUE_LENGTH);
                    u32bufferIndex = 0 + WMPICTURE_VALUE_DATA_TYPE_LENGTH + WMPICTURE_VALUE_LENGTH + (U32)u16DataLen;

                }
                else
                {
                    memcpy(&u16DataLen, &pu8Data[u32bufferIndex+DESCRIPTOR_NAME_LENGTH+u16DesNameLen + WMPICTURE_VALUE_DATA_TYPE_LENGTH],WMPICTURE_VALUE_LENGTH);
                    u32bufferIndex = u32bufferIndex + DESCRIPTOR_NAME_LENGTH + u16DesNameLen + WMPICTURE_VALUE_DATA_TYPE_LENGTH + WMPICTURE_VALUE_LENGTH + (U32)u16DataLen;
                }
                WMA_INFO(printf("u16DesNameLen = %d, u16DataLen=%d\n", u16DesNameLen, u16DataLen));
            }
        } //end of parse ExContent

        pstWmaProbeInfo->u16BitRate = (U16)stWmaInfoLocal.u32BitRate;
        pstWmaProbeInfo->u32SampleRate = stWmaInfoLocal.u32SampleRate;

        if(u32InfoAttr==E_MUSIC_INFO_DURATION)
        {
            pstWmaProbeInfo->u32Duration = stWmaInfoLocal.u32Duration;
        }
        //end of Header Object
        bRet = TRUE;
    }
    //no Header Object
    if(pu8Data!=NULL)
    {
        msAPI_Memory_Free(pu8Data ,BUF_ID_FILEBROWER);
        WMA_INFO(printf("free pu8Data\n"));
        pu8Data=NULL;
    }
    return bRet;
}

//******************************************************************************
/// Check Supported Audio, Return value if DSP supported or not
/// @param DecodeSystem
/// @return  BOOLEAN    //True:Supporte, False:NotSupported
//******************************************************************************
static BOOLEAN _MApp_WMA_CheckSupportedAudio(En_DVB_decSystemType enDecSystem)
{
    BOOLEAN bRet=FALSE;
    U64 u64SupportAudio = 0;
    u64SupportAudio=MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_ADEC1_capability);
    switch(enDecSystem)
    {
        case MSAPI_AUD_DVB_MP3:
            if (u64SupportAudio & Audio_DEC_MP3)
            {
                bRet = TRUE;
            }
            break;
        case MSAPI_AUD_DVB_MPEG:
            if (u64SupportAudio & Audio_DEC_MPEG)
            {
                bRet = TRUE;
            }
            break;
        case MSAPI_AUD_DVB_AAC:
            if ((u64SupportAudio & Audio_DEC_AAC_LC)||(u64SupportAudio & Audio_DEC_HEAAC_V1)||(u64SupportAudio & Audio_DEC_HEAAC_V2)||(u64SupportAudio & Audio_DEC_DOLBYPULSE))
            {
                bRet = TRUE;
            }
            break;
        case MSAPI_AUD_DVB_FLAC:
            if (u64SupportAudio & Audio_DEC_FLAC)
            {
                bRet = TRUE;
            }
            break;
        case MSAPI_AUD_DVB_AC3P:
            if (u64SupportAudio & Audio_DEC_AC3P)
            {
                bRet = TRUE;
            }
            break;
        case MSAPI_AUD_DVB_AC3:
            if (u64SupportAudio & Audio_DEC_AC3)
            {
                bRet = TRUE;
            }
            break;
        case MSAPI_AUD_DVB_DRA:
            if (u64SupportAudio & Audio_DEC_DRA)
            {
                bRet = TRUE;
            }
            break;
        case MSAPI_AUD_DVB_DTSLBR:
        case MSAPI_AUD_DVB_DTS:
            if (u64SupportAudio & Audio_DEC_DTS)
            {
                bRet = TRUE;
            }
            break;
        case MSAPI_AUD_DVB_XPCM:
            if ((u64SupportAudio & Audio_DEC_PCM)||(u64SupportAudio&Audio_DEC_XPCM))
            {
                bRet = TRUE;
            }
            break;
        case MSAPI_AUD_DVB_VORBIS:
            if (u64SupportAudio & Audio_DEC_VORBIS)
            {
                bRet = TRUE;
            }
            break;
        case MSAPI_AUD_DVB_WMA:
            if (u64SupportAudio & Audio_DEC_WMA)
            {
                bRet = TRUE;
            }
            break;
        case MSAPI_AUD_DVB_WMA_PRO:
            if (u64SupportAudio & Audio_DEC_WMAPRO)
            {
                bRet = TRUE;
            }
            break;
        case MSAPI_AUD_DVB_RA8LBR:
            if (u64SupportAudio & Audio_DEC_RA8)
            {
                bRet = TRUE;
            }
            break;
        case MSAPI_AUD_DVB_AMR_NB:
            if (u64SupportAudio & Audio_DEC_AMR_NB)
            {
                bRet = TRUE;
            }
            break;
        case MSAPI_AUD_DVB_AMR_WB:
            if (u64SupportAudio & Audio_DEC_AMR_WB)
            {
                bRet = TRUE;
            }
            break;
        default:
            break;
    }
    return bRet;
}

#endif  // #if (ENABLE_WMA)
#endif // #if (ENABLE_DMP)

#undef MAPP_WMA_C


