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

///////////////////////////////////////////////////////////////////////////////
/// @file MApp_KTV.c
/// @brief KTV quecy&playback kernel
/// @author MStar Semiconductor Inc.
///
/// KTV quecy & playback kernel provide a simple interface to let users implement
/// KTV function on MStar chip.
///
///////////////////////////////////////////////////////////////////////////////

#define MAPP_KTV_C

#include <stdio.h>
#include <string.h>
#include "Utl.h"
#include "imginfo.h"

#ifdef ENABLE_KTV
#include "SysInit.h"
#include "drvCPU.h"
#include "MApp_Exit.h"
#include "sysinfo.h"
#include "GPIO.h"
#include "msAPI_MailBox.h"
#include "msAPI_Bootloader.h"

//Mass Storage ========================
#include "msAPI_FCtrl.h"
#include "MApp_MassStorage.h"
#include "MApp_FileBrowser.h"

#include "msAPI_Memory.h"
#include "msAPI_MIU.h"
#include "msAPI_Timer.h"
#include "apiGOP.h"
#include "IOUtil.h"
#include "msAPI_Flash.h"
#include "msAPI_DrvInit.h"
#include "apiXC_Sys.h"
#include "msAPI_audio.h"

#include "MApp_GlobalVar.h"
#include "msAPI_JPEG_MM.h"
#include "msAPI_APEngine.h"

#include "MApp_KTV.h"
#include "MApp_KTV_Main.h"
#include "mapp_jpeg_mm.h"
#include "MApp_KTV_Lyric.h"

#include "mapp_videoplayer.h"
#include "mapp_gb2unicode.h"
#include "mapp_big52unicode.h"
#include "MApp_CharTable.h"
#include "MApp_Audio.h"
#include "MApp_Logo.h"
#include "MApp_SaveData.h"
#include "MApp_InputSource.h"
#include "MApp_Ktv_DbSearch.h"
#if DYNAMIC_VECTOR_FONT_ENABLE
#include "MApp_Font_Dynamic_MVF.h"
#endif
#include "MApp_USBDownload.h"

//*****************************************************************************
//              Definitions
//*****************************************************************************
#define KTV_DBG(x)                  x
#define KTV_REC_DBG(x)              //x

#define INI_FILENAME        "KTV.INI"
#define SONG_BIN_FILENAME          "MUSICLIST.BIN"
#define SINGER_BIN_FILENAME        "SINGERLIST.BIN"
#define SONG_PLAYLIST_FILENAME     "SONGLIST.BIN"
#define SW_MERGE_FILENAME     "MERGE.BIN"
#define SW_MERGE_FILENAME2     "MERGE.bin"
#define SOUND_FONT_FILENAME     "2.6M-GS-FreeMan.dat"
#if ENABLE_AUDIO_ENCODE
#define REC_SONG_FILENAME         "REC00.MP3"
#define QUECY_LATEST_REC_SONG   1
#endif

//please use upper case


//*****************************************************************************
//              enums
//*****************************************************************************


//*****************************************************************************
//              Data structure
//*****************************************************************************

typedef struct
{
    enumKTVKnlMovieFlags eKnlMovieFlag;

    U8 u8BrowserHandle;

    U16 u16PlayingIdx;

    U16 u16CurrentDrive;
    FileEntry curPlayingFileEntry;
    U16 u16TotalFileNum;
    U16 u16TotalDirNum;
} KTVPlayingMovieFileInfo;

typedef struct
{
    U32 u32PlayStartTime;
    U32 u32Duration;
} ST_MIC_INFO;

#if ENABLE_AUDIO_ENCODE
typedef struct
{
    //FileEntry curRecordingFileEntry;
    KTVFileInfo curRecFileInfo;
    U8 u8RecFilehandle;
    U32 u32BuffStart;
    U32 u32BuffEnd;
    U32 u32BuffSize;
    U32 u32BuffWrPtr;
    U32 u32BuffRdPtr;
    U32 u32BuffFreeSize;
    BOOLEAN bBuffRewind;
} KTVRecodInfo;
#define REC_BUFF_SIZE     0x8000
#define REC_BUFF_FIRE_THD        (REC_BUFF_SIZE/4)
#endif
//*****************************************************************************
//              Global variables
//*****************************************************************************
U16 *pSongCurrentPlayList;
U16 *pSongHistoryPlayList;
U16 *pSongFavoritePlayList;
EN_KTV_PLAYLIST_INFO eKTVPlayListInfo;

//*****************************************************************************
//              Local variables
//*****************************************************************************
static enumKTVKnlFlags _eKTVKnlFlags=E_KTV_KNL_FLG_NULL;
static EN_KTV_DISK_STATUS _PrevUSBDeviceStatus=E_KTV_USB_NONE;
static U8 _u8TotalDriveNum;
static KTVDeviceStatus *_KTVDeviceStatus;
static U16 _u16DeviceValidStatus;
static U32 _u32DeviceCheckTimer;
static KTVDrive _DriveInfo[NUM_OF_MAX_KTV_DRIVE];

U8 _u8NetWorkState=0;
static U32 _u32NetUpdateCounter=0;
static U32 _u32NetErrorCounter=0;
static U32 _u32NetIPAddress=0;
static U32 _u32NetInfoLen=0;
static U32 _u32NetVersion=0;
static U32 _u32MusicVersion0=0;
static U32 _u32MusicVersion1=0;
static U32 _u32SingerVersion0=0;
static U32 _u32SingerVersion1=0;

static U32 _u32SoundFontFileLen=0;
//static U32 _u32SoundMicFileLen=0;
//static U32 _u32MidiLrcFileLen=0;
BOOLEAN bUpdateLRCFileReady = FALSE;
BOOLEAN bSongNameDisplay = FALSE;

static BOOLEAN bKTVCoProcesserReady = FALSE;

U8 u8UpdateReady=0;

static U32 _u32NetSWVersion=0;
static U32 _u32MergeVersion0=AP_SW_VERSION;
static U32 _u32MergeVersion1=(MAGIC_APP&0x00ffffff);
static U8 MApp_KTV_MailBoxHandler(void);
static void MApp_KTV_AutoUpdate(void);
static void MApp_KTV_CheckCoProcesserReady_Task(void);


static U8 _u8CurDeviceIdx;
static U16 _u16CurDriveIdx;
//static U32 _u32DriveStatus;
static U16 _u16CurDirectory[NUM_OF_MAX_KTV_DIRECTORY_DEPTH+1];
static U16 _u16DirectoryNum[NUM_OF_MAX_KTV_DIRECTORY_DEPTH+1];
//static U16 _u16PathIndex[NUM_OF_MAX_KTV_DIRECTORY_DEPTH+1];
static U16 _u16CurDirectoryDepth;

static U16 _u16BufDirectoryDepth;
static U16 _u16BufDirectory[NUM_OF_MAX_KTV_DIRECTORY_DEPTH+1];
static U16 _u16BufTotalFileNum;
static U16 _u16BufDirectoryNum;
static U16 _u16BufReadLongNameIdx;

static U16 _u16CurFileIdx;
static U8 _u8UserBrowserHandle = INVALID_BROWSER_HANDLE;
static U16 _u16TotalFileNum;

static FileEntry *_pKTVFileEntry;
static U8 _u8FileHandleId;

U8 code _au8KTV_ExtFileName[][3] =
{
    "AVI", "MP4", "MKV", "MIC", "BIN", "TXT", "DAT", "INI", "MP3"
};

static KTVPlayingMovieFileInfo _KTVMovieInfo;
static EN_RET _eMovieMainExit = EXIT_VDPLAYER_NULL;
static enumKTVZoom _eZoom;
static U32 _u32PlayCheckTime;
static U16 _u16PlayingTickTime;

static U32 _u32SongListAddr;
static U32 _u32SongListCheckTimer;
static ST_MIC_INFO st_mic_info;
static Music_Mic_Lyric_Tag curLyricTag;
static U16 u16Duringtime;
static U16 u16preDowncounterLyricPos;
static U16 u16preLine1LyricPos;
static U16 u16preLine2LyricPos;

static KTV_INI_INFO _sKtvIni;
static BOOLEAN bForceHKPrintf;
#if ENABLE_AUDIO_ENCODE
static U32 u32RecBuff[REC_BUFF_SIZE/4];
static BOOLEAN bEncoding = FALSE;
KTVRecodInfo RecInfo;
KTVRecodInfo* pRecInfo = &RecInfo;
U8 u8AudIntCount;
extern XDATA U8 gu8MADEncodeDone;
U32 u32AudOutputSize = 0;
U32 u32AudFileWriteSize = 0;
#endif

//*****************************************************************************
//              Local Functions Prototype
//*****************************************************************************


//*****************************************************************************
//              Local Functions
//*****************************************************************************
static void _MApp_KTV_SendMailboxMsg(U8 _class, U8 _index, MBX_MSG_Type _type, U8 _count,
                                        U8 _p1, U8 _p2, U8 _p3, U8 _p4, U8 _p5, U8 _p6, U8 _p7, U8 _p8, U8 _p9, U8 _p10)
{
    MBX_Msg m5_mbxMsg;
    MBX_Result mbxResult;

    m5_mbxMsg.u8MsgClass            = _class;
    m5_mbxMsg.u8Index               = _index;
    m5_mbxMsg.u8ParameterCount      = _count;
    m5_mbxMsg.eMsgType              = _type;
    m5_mbxMsg.u8Parameters[0]       = _p1;
    m5_mbxMsg.u8Parameters[1]       = _p2;
    m5_mbxMsg.u8Parameters[2]       = _p3;
    m5_mbxMsg.u8Parameters[3]       = _p4;
    m5_mbxMsg.u8Parameters[4]       = _p5;
    m5_mbxMsg.u8Parameters[5]       = _p6;
    m5_mbxMsg.u8Parameters[6]       = _p7;
    m5_mbxMsg.u8Parameters[7]       = _p8;
    m5_mbxMsg.u8Parameters[8]       = _p9;
    m5_mbxMsg.u8Parameters[9]       = _p10;

    do
    {
        mbxResult = MSApi_MBX_SendMsg(&m5_mbxMsg);
        switch(mbxResult)
        {
            case E_MBX_ERR_PEER_CPU_BUSY:
            case E_MBX_ERR_PEER_CPU_NOTREADY:
            case E_MBX_ERR_PEER_CPU_NOT_ALIVE:
                //Error Handling here...
                break;
            case E_MBX_ERR_PEER_CPU_OVERFLOW:
                MsOS_DelayTask(1);
                break;
            default:
                break;
        }
    }while(E_MBX_SUCCESS != mbxResult);
}

static void _ASCII2Unicode(U8 *pu8String)
{
    U8 len=0;
    U8 i=0;
    for(i=0;i<255;i++)
    {
        if(pu8String[i]==0)
        {
            len=i;
            break;
        }
    }
    for(i=0;i<len;i++)
    {
        ((U16*)pu8String)[len-1-i]=pu8String[len-1-i];
    }
    if(len>0)
    {
        ((U16*)pu8String)[len]=0;
    }
}

static BOOLEAN _MApp_IsKTV_File_ByExtName(U8 *pu8ExtName)
{
    U8 i, *pu8MediaTypeName, u8ExtNum, j;

    pu8MediaTypeName = &_au8KTV_ExtFileName[0][0];
    u8ExtNum = sizeof(_au8KTV_ExtFileName)/3;
    for(i=0;i<u8ExtNum;i++)
    {
        for(j=0;j<3;j++)
        {
            if(toupper(pu8ExtName[j]) != pu8MediaTypeName[j])
            {
                break;
            }
        }
        if(j >= 3)
        {
            return TRUE;
        }
        pu8MediaTypeName += 3;
    }
    return FALSE;
}

U16 _MApp_KTV_FilterFileByMediaType(U16 u16DirCnt, U16 u16TotalCnt, BOOLEAN bValid)
{
    U32 u32Addr;
    U16 u16FileIdx;
    KTVFileInfo fileInfo, *pFileInfo;
    #define extName     pFileInfo->u8ExtFileName
    U16 u16MediaFileCnt = 0;

    for(u16FileIdx=0;
        u16FileIdx<(u16TotalCnt-u16DirCnt);
        u16FileIdx++)
    {
        u32Addr = (U32)((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR)) +
                  (U32)(u16FileIdx+NUM_OF_MAX_KTV_FILES_PER_DIRECTORY+u16DirCnt)*sizeof(KTVFileInfo);

        pFileInfo = (KTVFileInfo xdata *)u32Addr;
        //KTV_DBG(printf("u32Addr = %lx\n", u32Addr));
        //KTV_DBG(printf("EXT %p %s\n", extName, extName));

        if(_MApp_IsKTV_File_ByExtName(extName))
        {
            memcpy(&fileInfo, pFileInfo, sizeof(KTVFileInfo));

            u32Addr = (U32)((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR)) +
                      (U32)(u16MediaFileCnt+u16DirCnt)*sizeof(KTVFileInfo);

            pFileInfo = (KTVFileInfo xdata *)u32Addr;

            memcpy(pFileInfo, &fileInfo, sizeof(KTVFileInfo));
            pFileInfo->bLongFileNameValid = bValid;
            u16MediaFileCnt++;
        }

        msAPI_Timer_ResetWDT();
    }
    return u16MediaFileCnt;
}

static void _MApp_KTV_Browser_SaveCurFileInfo(U16 u16FileIdx)
{
    MPlayerFileInfo fileInfo;
    MPlayerFileInfo *pFileInfo;
    DirEntryStruct * pCurrentDirEntry;
    U32 u32Addr;

    pCurrentDirEntry = MApp_FileBrowser_GetCurrentDirEntry();

    // Save file entry for file name.
    MApp_FileBrowser_GetCurrentFileEntry(&fileInfo.fileEntry);

    fileInfo.eAttribute = (enumFileAttribute)pCurrentDirEntry->u8DirEntryAttrib;
    fileInfo.u64FileSize= &MApp_FileBrowser_GetCurrentLength_LongLong();

    fileInfo.u16Year = FAT_GET_YEAR (pCurrentDirEntry->u16DirEntryDate);
    fileInfo.u8Month = FAT_GET_MONTH(pCurrentDirEntry->u16DirEntryDate);
    fileInfo.u8Day   = FAT_GET_DAY  (pCurrentDirEntry->u16DirEntryDate);

    fileInfo.u8Hour   = FAT_GET_HOUR(pCurrentDirEntry->u16DirEntryTime);
    fileInfo.u8Minute = FAT_GET_MIN (pCurrentDirEntry->u16DirEntryTime);
    fileInfo.u8Second = FAT_GET_SEC (pCurrentDirEntry->u16DirEntryTime);

    if(E_KTV_FILE_DIRECTORY & fileInfo.eAttribute)
    {
        memset(fileInfo.u8ExtFileName, ' ', 3);
        fileInfo.u8ExtFileName[3] = '\0';
    }
    else
    {
        memcpy(fileInfo.u8ExtFileName, pCurrentDirEntry->ps8DirEntryExtName, 3);
        fileInfo.u8ExtFileName[3] = 0;
    }

    fileInfo.bLongFileNameValid = FALSE;

    u32Addr = (U32)((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR)) + (U32)u16FileIdx*sizeof(MPlayerFileInfo);

    pFileInfo = (MPlayerFileInfo xdata *)u32Addr;
    memcpy(pFileInfo, &fileInfo, sizeof(MPlayerFileInfo));
}

static void _MApp_KTV_Browser_EnumCurDirectory(void)
{
    DirEntryStruct * pCurrentDirEntry   = NULL;     //global current dir entry

    //U16 u16FileIdx;
    U16 u16DirCnt;
    U16 u16FileCnt, u16MediaFileCnt;
    BOOLEAN bNeedRead = FALSE;


    // 0: Check whether change directory
    if(_u16BufDirectoryDepth != _u16CurDirectoryDepth)
    {
        bNeedRead = TRUE;
    }
    else
    {
        for(u16DirCnt=0;u16DirCnt<_u16CurDirectoryDepth;u16DirCnt++)
        {
            if(_u16BufDirectory[u16DirCnt] != _u16CurDirectory[u16DirCnt])
            {
                bNeedRead = TRUE;
            }
        }
    }

    if(bNeedRead)
    {
        // 1. Read all files & directories.
        _u16BufTotalFileNum = 0;
        u16DirCnt = 0;
        u16FileCnt = 0;
        MApp_FileBrowser_ToFirstEntryInCurrentDirectory();
        pCurrentDirEntry = MApp_FileBrowser_GetCurrentDirEntry();

        while(pCurrentDirEntry && (_u16BufTotalFileNum<NUM_OF_MAX_KTV_FILES_PER_DIRECTORY))
        {
            FileEntry fileEntry;

            MApp_FileBrowser_GetCurrentFileEntry(&fileEntry);
            if(!(fileEntry.EntryAttrib & ENTRY_ATTRIB_HIDDEN) ||
                (fileEntry.EntryType == ENTRY_TYPE_DIR_DOT) ||
                (fileEntry.EntryType == ENTRY_TYPE_DIR_DOTDOT))
            {
                if(pCurrentDirEntry->u8DirEntryAttrib & ENTRY_ATTRIB_DIRECTORY)
                {
                    _MApp_KTV_Browser_SaveCurFileInfo(u16DirCnt+NUM_OF_MAX_KTV_FILES_PER_DIRECTORY);
                    u16DirCnt++;
                }
                else
                {
                    _MApp_KTV_Browser_SaveCurFileInfo(u16FileCnt);
                    u16FileCnt++;
                }
                _u16BufTotalFileNum++;
            }
            msAPI_Timer_ResetWDT();
            pCurrentDirEntry = MApp_FileBrowser_GetNextDirEntry(1);
        }
        _u16DirectoryNum[_u16CurDirectoryDepth] = u16DirCnt;
        _u16BufDirectoryNum = u16DirCnt;

        msAPI_MIU_Copy((U32)((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR)),
                       (U32)((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR))+
                       ((U32)u16DirCnt+(U32)NUM_OF_MAX_KTV_FILES_PER_DIRECTORY)*sizeof(KTVFileInfo),
                       (U32)sizeof(KTVFileInfo)*u16FileCnt,
                       MIU_SDRAM2SDRAM);

        // Copy directories.
        msAPI_MIU_Copy((U32)((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR))+
                       (U32)NUM_OF_MAX_KTV_FILES_PER_DIRECTORY*sizeof(KTVFileInfo),
                       (U32)((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR)),
                       (U32)sizeof(KTVFileInfo)*u16DirCnt,
                       MIU_SDRAM2SDRAM);

        _u16BufDirectoryDepth = _u16CurDirectoryDepth;
        for(u16DirCnt=0;u16DirCnt<_u16CurDirectoryDepth;u16DirCnt++)
        {
            _u16BufDirectory[u16DirCnt] = _u16CurDirectory[u16DirCnt];
        }
        _u16BufDirectory[_u16CurDirectoryDepth] = KTV_INVALID_INDEX;
    }

    // Enumerate files.
    u16MediaFileCnt = _MApp_KTV_FilterFileByMediaType(_u16BufDirectoryNum, _u16BufTotalFileNum, FALSE);
    _u16DirectoryNum[_u16CurDirectoryDepth] = _u16BufDirectoryNum;
    _u16TotalFileNum = u16MediaFileCnt + _u16BufDirectoryNum;
    _u16BufReadLongNameIdx = 0;

    // Set selected files.
    /*
    for(u16FileIdx=_u16BufDirectoryNum;
        u16FileIdx<_u16TotalFileNum;
        u16FileIdx++)
    {
        if(_MApp_MPlayer_Browser_IsInPlayingList(m_eMediaType, u16FileIdx))
        {
            _MApp_MPlayer_Browser_SetSelected(u16FileIdx, TRUE);
        }
        msAPI_Timer_ResetWDT();
    }
    */
    KTV_DBG(printf("_u16TotalFileNum = %x\n", _u16TotalFileNum));
}


static BOOLEAN _MApp_KTV_DisconnectDrive(void)
{
    U8 i;

    MApp_FileBrowser_DeInit();
    MApp_MassStorage_DriveDisconnect(_u16CurDriveIdx);
    KTV_DBG(printf("_MApp_KTV_DisconnectDrive\n"));
    for(i=0;i<NUM_OF_MAX_KTV_DIRECTORY_DEPTH+1;i++)
    {
        _u16CurDirectory[i] = KTV_INVALID_INDEX;
        _u16BufDirectory[i] = KTV_INVALID_INDEX;
    }

    _u16CurDirectoryDepth = 0;
    _u16BufDirectoryDepth = KTV_INVALID_INDEX;
    _u16BufReadLongNameIdx = KTV_INVALID_INDEX;
    _u16CurFileIdx        = 0;
    _u16TotalFileNum      = 0;
    _u8CurDeviceIdx        = 0;
    memset(_u16DirectoryNum, 0, sizeof(U16)*NUM_OF_MAX_KTV_DIRECTORY_DEPTH);

    return TRUE;
}

/******************************************************************************/
/// Read back the file information by filename(UNICODE) from file buffer.
/// @param  pu16Buf \b IN Specify the filename.
/// @param  pInfo      \b OUT Return the file information.
/// @return enumKTVRet
/******************************************************************************/
static enumKTVRet _MApp_KTV_QueryFileInfo(U16 *pu16Buf, KTVFileInfo *pInfo)
{
    U32 u32Addr;
    KTVFileInfo *pFileInfo;
    U8 i,j;
    U8 u8length_S=0,u8length_D=0;
    U16 *pu16Tmp;
    U16 *pu16String_S = pu16Buf;
    U16 *pu16String_D;
    BOOLEAN bIsFound=FALSE;
    U8 u8Count = 0;

    pu16Tmp = pu16Buf;
    for(i=0;i<255;i++)//get input filename length
    {
        if( *(pu16Tmp++)==0)
            break;
        u8length_S++;
    }


    for(j=0;j<(_u16TotalFileNum-_u16BufDirectoryNum);j++)
    {
        FS_RESET_WDT();
        u8length_D=0;
        u8Count=0;
        pu16String_S = pu16Buf;

        u32Addr = (U32)((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR)) + (U32)(j+_u16BufDirectoryNum)*sizeof(KTVFileInfo);
        pFileInfo = (KTVFileInfo xdata *)(u32Addr);

        if(!pFileInfo->bLongFileNameValid)
        {
            U8 u8Len;

            // Get long file name from file entry.
            u8Len = MApp_FileBrowser_GetLongFileNameByFileEntry(
                        &pFileInfo->fileEntry,
                        XD2PHY(&pInfo->u8LongFileName[0]),
                        (KTV_FILE_INFO_LONG_FILENAME_SIZE/2-1));
            u8Len = (u8Len > (KTV_FILE_INFO_LONG_FILENAME_SIZE/2-1)) ?
                        KTV_FILE_INFO_LONG_FILENAME_SIZE/2-1:
                        u8Len;
            pInfo->u8LongFileName[u8Len*2] = 0;
            pInfo->u8LongFileName[u8Len*2+1] = 0;
            memcpy(&pFileInfo->u8LongFileName[0], &pInfo->u8LongFileName[0], KTV_FILE_INFO_LONG_FILENAME_SIZE);
            pFileInfo->bLongFileNameValid = TRUE;
        }
        //compare longfilename
        pu16String_D=pu16Tmp=(U16*)pFileInfo->u8LongFileName;
        for(i=0;i<255;i++)//get disk filename length
        {
            if( *(pu16Tmp++)==0)
                break;
            u8length_D++;
        }
        //KTV_DBG(printf("\n u8length_S=%bd ; u8length_D=%bd \n",u8length_S,u8length_D));
        if(u8length_S!=u8length_D)
            continue;

        while(u8Count < u8length_S)
        {
            //KTV_DBG(printf("pu16String_S=%x  pu16String_D=%x \n",*pu16String_S,*pu16String_D));
            if( *(pu16String_S++) != *(pu16String_D++))
            {
                break;
            }
            u8Count ++;
        }

        if(u8Count == u8length_S)
        {
            bIsFound = TRUE;
            break;
        }

    }
    if(bIsFound==FALSE)
        return E_KTV_RET_FAIL;

    memcpy(pInfo, pFileInfo, sizeof(KTVFileInfo));

    return E_KTV_RET_OK;
}


static BOOLEAN _MApp_KTV_MoviePlayerInit(void)
{
    U16 u16TotalFileNumber = _u16TotalFileNum;

    _KTVMovieInfo.eKnlMovieFlag &= (enumKTVKnlMovieFlags)~(E_KTV_KNL_MOVIE_FLG_PLAY);

    _KTVMovieInfo.u16PlayingIdx = 0;
    _KTVMovieInfo.u16TotalFileNum = u16TotalFileNumber; // directories are included
    _KTVMovieInfo.u16TotalDirNum = _u16DirectoryNum[_u16CurDirectoryDepth];

    if ((_KTVMovieInfo.u8BrowserHandle == INVALID_BROWSER_HANDLE)
            || (_KTVMovieInfo.u16CurrentDrive != _u16CurDriveIdx))
    {
        if (_KTVMovieInfo.u8BrowserHandle != INVALID_BROWSER_HANDLE)
        {
            MApp_FileBrowser_Destroy(_KTVMovieInfo.u8BrowserHandle);
        }

        _KTVMovieInfo.u16CurrentDrive = _u16CurDriveIdx;
        _KTVMovieInfo.u8BrowserHandle =MApp_FileBrowser_Create(_KTVMovieInfo.u16CurrentDrive);
    }

    return (_KTVMovieInfo.u8BrowserHandle != INVALID_BROWSER_HANDLE ? TRUE : FALSE);
}
void _MApp_KTV_PlayMovie(void)
{
    KTVFileInfo FileInfo;

    U16 u16FlashID;
    U8 u8FlashFileName[15];
    MApp_SearchSongByID(stp_ktv_songbuf, g_total_song,  stp_ktv_singerbuf, st_ktv_list->st_play_song_list[_KTVMovieInfo.u16PlayingIdx].u32Song_ID, st_searchedsong_buf, st_searchedsinger_buf);
    srand(msAPI_Timer_GetTime0());
    if((rand()%5) == 0)
    u16FlashID=stp_ktv_songbuf->wFlashU;
    else if((rand()%5) == 1)
    u16FlashID=stp_ktv_songbuf->wFlashV;
    else if((rand()%5) == 2)
    u16FlashID=stp_ktv_songbuf->wFlashW;
    else if((rand()%5) == 3)
    u16FlashID=stp_ktv_songbuf->wFlashX;
    else if((rand()%5) == 4)
    u16FlashID=stp_ktv_songbuf->wFlashY;
    else
    u16FlashID=0;
    printf("\r\n u16Flash = %x",u16FlashID);
    MApp_ConvertFlashNumberToFileName(u16FlashID,u8FlashFileName);
    _KTVMovieInfo.eKnlMovieFlag =E_KTV_KNL_MOVIE_FLG_FILE_INIT;
    if(MApp_KTV_QueryAsciiFileInfo(&u8FlashFileName[0],&FileInfo)==E_KTV_RET_OK)
    {
        _MApp_KTV_MoviePlayerInit();
        memcpy(&_KTVMovieInfo.curPlayingFileEntry,
                &FileInfo.fileEntry,
                sizeof(FileEntry));
        _KTVMovieInfo.eKnlMovieFlag |=E_KTV_KNL_MOVIE_FLG_PLAY;
        return;
    }
    //No Flash File Find
    u16FlashID = 0x0AA9;//A01_105_01.avi
    MApp_ConvertFlashNumberToFileName(u16FlashID,u8FlashFileName);
    if(MApp_KTV_QueryAsciiFileInfo(&u8FlashFileName[0],&FileInfo)==E_KTV_RET_OK)
    {
        _MApp_KTV_MoviePlayerInit();
        memcpy(&_KTVMovieInfo.curPlayingFileEntry,
                &FileInfo.fileEntry,
                sizeof(FileEntry));
        _KTVMovieInfo.eKnlMovieFlag |=E_KTV_KNL_MOVIE_FLG_PLAY;

    }


}

static BOOLEAN _MApp_KTV_PlayMovieAgain(void)
{
    _eZoom = E_KTV_ZOOM_1;
    _eKTVMoviePlayMode = E_KTV_MOVIE_NORMAL;
    _eKTVMovieActionMode=E_KTV_MOVIE_ACTION_NUL;
    _eMovieMainExit = EXIT_VDPLAYER_NULL;
    _KTVMovieInfo.eKnlMovieFlag |= E_KTV_KNL_MOVIE_FLG_PLAY;
    _KTVMovieInfo.eKnlMovieFlag |= E_KTV_KNL_MOVIE_FLG_FILE_INIT;
    _KTVMovieInfo.eKnlMovieFlag &= (enumKTVKnlMovieFlags)~E_KTV_KNL_MOVIE_FLG_PREDECODE_OK;
    _MApp_KTV_PlayMovie();

    return TRUE;
}
static BOOLEAN _MApp_KTV_PlayMovieNext(void)
{
    _eZoom = E_KTV_ZOOM_1;
    _eKTVMoviePlayMode = E_KTV_MOVIE_NORMAL;
    _eKTVMovieActionMode=E_KTV_MOVIE_ACTION_NUL;
    _eMovieMainExit = EXIT_VDPLAYER_NULL;

    _KTVMovieInfo.u16PlayingIdx++;
    _MApp_KTV_PlayMovie();

    return TRUE;
}
static BOOLEAN _MApp_KTV_PlayMoviePrev(void)
{
    _eZoom = E_KTV_ZOOM_1;
    _eKTVMoviePlayMode = E_KTV_MOVIE_NORMAL;
    _eKTVMovieActionMode=E_KTV_MOVIE_ACTION_NUL;
    _eMovieMainExit = EXIT_VDPLAYER_NULL;
    if(_KTVMovieInfo.u16PlayingIdx)
{
        _KTVMovieInfo.u16PlayingIdx--;
    }

    _MApp_KTV_PlayMovie();
    return TRUE;
}


void _MApp_KTV_Stop_Movie(void)
{
    msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    MApi_XC_GenerateBlackVideo(ENABLE, MAIN_WINDOW);
    MApp_VDPlayer_Stop();
}


static BOOLEAN _MApp_KTV_Check_PlayList(void)
{
    if(st_ktv_list->u8playsongcounter > MAXNUM_OF_PLAY_SONG)
    {
        st_ktv_list->u8playsongcounter=0;
        printf("init u8playsongcounter\n");
    }
    if(st_ktv_list->u8playedsongcounter> MAXNUM_OF_PLAYED_SONG)
    {
        st_ktv_list->u8playedsongcounter=0;
        printf("init u8playedsongcounter\n");
    }
    if(st_ktv_list->u8favorsongcounter> MAXNUM_OF_FAVOR_SONG)
    {
        st_ktv_list->u8favorsongcounter=0;
        printf("init u8favorsongcounter\n");
    }
    if(st_ktv_list->u8CurrentRecSongIndex> MAXNUM_OF_REC_SONG)
    {
        st_ktv_list->u8CurrentRecSongIndex=0;
        printf("init u8CurrentRecSongIndex\n");
    }
    return TRUE;
}

/******************************************************************************/
/// Read back the file information by playlist filenname(ASCII) from file buffer.
/// @param  pu8Buf \b IN Specify the playlist filename.
/// @param  pInfo      \b OUT Return the file information.
/// @return enumKTVRet
/******************************************************************************/
enumKTVRet _MApp_KTV_QueryPlaylistFileInfo(U8 *pu8Buf, KTVFileInfo *pInfo)
{
    U8 u8String[40],i;
    U16 *pu16String;
    enumKTVRet eRet=E_KTV_RET_FAIL;
    U8 u8HandleNo;
    FileEntry fileEntry;

    for(i=0;i<40;i++)
    {
        if(*pu8Buf!=0)
            u8String[i]=*(pu8Buf++);
        else
            u8String[i]=0;
    }
    KTV_DBG(printf(" u8String=%s\n",u8String));

    _ASCII2Unicode(&u8String[0]);
    pu16String = (U16*)(&u8String[0]);
    eRet = _MApp_KTV_QueryFileInfo(pu16String,pInfo);
    if(eRet==E_KTV_RET_FAIL)//file invalid,need create
    {
        u8HandleNo = MApp_FileBrowser_OpenNewFileForWrite(pu16String, UnicodeLen((S8*)u8String));
        if (u8HandleNo ==  INVALID_FILE_HANDLE)
        {
            KTV_DBG(printf("crate file failed\n"));
            return eRet;
        }
        msAPI_FCtrl_EntryGetByHandle(u8HandleNo,&fileEntry);
        msAPI_FCtrl_FileWrite(u8HandleNo,(U32)st_ktv_list,sizeof(ST_KTV_LIST));
        msAPI_FCtrl_FileClose(u8HandleNo);
        pInfo->fileEntry = fileEntry;
        eRet = E_KTV_RET_OK;
    }
    else//FS issue,need fix
    {
        msAPI_FCtrl_FileDelete(&(pInfo->fileEntry));
        u8HandleNo = MApp_FileBrowser_OpenNewFileForWrite(pu16String, UnicodeLen((S8*)u8String));
        if (u8HandleNo ==  INVALID_FILE_HANDLE)
        {
            KTV_DBG(printf("crate file failed\n"));
            return eRet;
        }
        msAPI_FCtrl_EntryGetByHandle(u8HandleNo,&fileEntry);
        msAPI_FCtrl_FileWrite(u8HandleNo,(U32)st_ktv_list,sizeof(ST_KTV_LIST));
        msAPI_FCtrl_FileClose(u8HandleNo);
        pInfo->fileEntry = fileEntry;
        eRet = E_KTV_RET_OK;
    }
    return eRet;
}

#if ENABLE_AUDIO_ENCODE
enumKTVRet _MApp_KTV_QueryRecSongFileInfo(U8 *pu8Buf, KTVFileInfo *pInfo)
{
    U16 u16String[20];
    U8 i;
    U8* u8String = (U8*)u16String;
    U16 *pu16String;
    enumKTVRet eRet=E_KTV_RET_FAIL;
    U8 u8HandleNo;
    FileEntry fileEntry;
    U8 RecSongIndex=st_ktv_list->u8CurrentRecSongIndex;

    if(RecSongIndex >= MAXNUM_OF_REC_SONG)
        RecSongIndex = 0;

    pRecInfo->u8RecFilehandle = 0;
    for(i=0;i<40;i++)
    {
        if(*pu8Buf!=0)
            u8String[i]=*(pu8Buf++);
        else
            u8String[i]=0;
    }
#if (QUECY_LATEST_REC_SONG)
    u8String[3] = RecSongIndex/10+'0';
    u8String[4] = RecSongIndex%10+'0';

    if(RecSongIndex >= MAXNUM_OF_REC_SONG)//set to next REC index
        RecSongIndex = 0;
    else
        RecSongIndex += 1;
    st_ktv_list->u8CurrentRecSongIndex=RecSongIndex;
    MApp_KTV_SetPlayListModifyFlag();
#endif
    KTV_DBG(printf(" u8String=%s\n",u8String));


    _ASCII2Unicode(&u8String[0]);
    pu16String = (U16*)(&u8String[0]);
    eRet = _MApp_KTV_QueryFileInfo(pu16String,pInfo);

    if(eRet==E_KTV_RET_FAIL)//file invalid,need create
    {
        u8HandleNo = MApp_FileBrowser_OpenNewFileForWrite(pu16String, UnicodeLen((S8*)u8String));
        if (u8HandleNo ==  INVALID_FILE_HANDLE)
        {
            KTV_DBG(printf("crate file failed 1\n"));
            return eRet;
        }
        msAPI_FCtrl_EntryGetByHandle(u8HandleNo,&fileEntry);
        msAPI_FCtrl_FileClose(u8HandleNo);
        pInfo->fileEntry = fileEntry;
        eRet = E_KTV_RET_OK;
    }
    else
    {
        msAPI_FCtrl_FileDelete(&(pInfo->fileEntry));
        u8HandleNo = MApp_FileBrowser_OpenNewFileForWrite(pu16String, UnicodeLen((S8*)u8String));
        if (u8HandleNo ==  INVALID_FILE_HANDLE)
        {
            KTV_DBG(printf("crate file failed 2\n"));
            return eRet;
        }
        msAPI_FCtrl_EntryGetByHandle(u8HandleNo,&fileEntry);
        msAPI_FCtrl_FileClose(u8HandleNo);
        pInfo->fileEntry = fileEntry;
        eRet = E_KTV_RET_OK;
    }
    return eRet;
}


BOOLEAN _MApp_KTV_SetAudIntAck(void)
{
    u8AudIntCount++;
    MApi_AUDIO_MM_SetInput(DVB_Audio_Decoder2, u8AudIntCount);
    return TRUE;
}

BOOLEAN _MApp_KTV_CheckOutputRequest(U32 *pU32WrtAddr, U32 *pU32WrtBytes)
{
    if (gu8MADEncodeDone)
    {
        MApi_AUDIO_MM_CheckInputRequest(DVB_Audio_Decoder2,pU32WrtAddr,pU32WrtBytes); 
        KTV_REC_DBG(printf("Audio Output, Start: 0x%x, Size: 0x%x\n", *pU32WrtAddr, *pU32WrtBytes));
        return TRUE;
    }
    return FALSE;
}

BOOLEAN _MApp_KTV_GetAudCompressData(U32 u32Start, U32 u32Size)
{
    U32 u32Temp;
/*
    if (pRecInfo->bBuffRewind)
    {
        return TRUE;
    }
*/
    if (u32Size > 0)
    {
        KTV_REC_DBG(printf("_MApp_KTV_GetAudCompressData, Src start: 0x%x, Size: 0x%x\n", u32Start, u32Size));
        KTV_REC_DBG(printf("Buffer start: 0x%x, end: 0x%x, Size: 0x%x\n",
            pRecInfo->u32BuffStart, pRecInfo->u32BuffEnd, pRecInfo->u32BuffSize));
        KTV_REC_DBG(printf("Buffer WrPtr: 0x%x, RdPtr: 0x%x, FreeSize: 0x%x, Rewind: 0x%x\n",
            pRecInfo->u32BuffWrPtr, pRecInfo->u32BuffRdPtr, pRecInfo->u32BuffFreeSize, pRecInfo->bBuffRewind));
        if (pRecInfo->u32BuffFreeSize >= u32Size)
        {
            if (pRecInfo->bBuffRewind)
            {
                //pRecInfo->u32BuffWrPtr < pRecInfo->u32BuffRdPtr
                memcpy((U8*)pRecInfo->u32BuffWrPtr, (U8*)u32Start, u32Size);
                pRecInfo->u32BuffWrPtr += u32Size;
                pRecInfo->u32BuffFreeSize -= u32Size;
            }
            else
            {
                if ((pRecInfo->u32BuffEnd - pRecInfo->u32BuffWrPtr) >= u32Size)
                {
                    memcpy((U8*)pRecInfo->u32BuffWrPtr, (U8*)u32Start, u32Size);
                    pRecInfo->u32BuffWrPtr += u32Size;
                    pRecInfo->u32BuffFreeSize -= u32Size;
                    if (pRecInfo->u32BuffWrPtr == pRecInfo->u32BuffEnd)
                    {
                        pRecInfo->u32BuffWrPtr = pRecInfo->u32BuffStart;
                        pRecInfo->bBuffRewind = TRUE;
                    }
                }
                else
                {
                    u32Temp = pRecInfo->u32BuffEnd - pRecInfo->u32BuffWrPtr;
                    memcpy((U8*)pRecInfo->u32BuffWrPtr, (U8*)u32Start, u32Temp);
                    pRecInfo->u32BuffWrPtr += u32Temp;
                    pRecInfo->u32BuffFreeSize -= u32Temp;
                    if (pRecInfo->u32BuffWrPtr == pRecInfo->u32BuffEnd)
                    {
                        pRecInfo->u32BuffWrPtr = pRecInfo->u32BuffStart;
                        pRecInfo->bBuffRewind = TRUE;
                    }
                    memcpy((U8*)pRecInfo->u32BuffWrPtr, (U8*)(u32Start + u32Temp), (u32Size - u32Temp));
                    pRecInfo->u32BuffWrPtr += (u32Size - u32Temp);
                    pRecInfo->u32BuffFreeSize -= (u32Size - u32Temp);
                }
            }
            KTV_REC_DBG(printf("Buffer WrPtr: 0x%x, RdPtr: 0x%x, FreeSize: 0x%x, Rewind: 0x%x\n",
                pRecInfo->u32BuffWrPtr, pRecInfo->u32BuffRdPtr, pRecInfo->u32BuffFreeSize, pRecInfo->bBuffRewind));
        }
        else
        {
            //Audio buffer overwite
            KTV_REC_DBG(printf("Audio Encoding Error!\n"));
            KTV_REC_DBG(printf("Buffer Free size is samll than Audio output!\n"));
            return FALSE;
        }
    }
    return TRUE;
}

BOOLEAN _MApp_KTV_WriteAudCompressdata(BOOLEAN bFlushAll)
{
    U32 u32Temp;

    if (!bFlushAll)
    {

        //Check Buffer write size, if write size > fire threshold, write those data to USB
        if ((pRecInfo->u32BuffSize - pRecInfo->u32BuffFreeSize) > REC_BUFF_FIRE_THD)
        {
            KTV_REC_DBG(printf("_MApp_KTV_WriteAudCompressdata, Flush all: 0x%x\n", bFlushAll));
            KTV_REC_DBG(printf("1. Buff need to write: 0x%x, RdPtr: 0x%x\n",
                (pRecInfo->u32BuffSize - pRecInfo->u32BuffFreeSize), pRecInfo->u32BuffRdPtr));
            //msAPI_FCtrl_FileWrite(pRecInfo->u8RecFilehandle, pRecInfo->u32BuffStart, REC_BUFF_SIZE);
            if (msAPI_FCtrl_FileWrite(pRecInfo->u8RecFilehandle, pRecInfo->u32BuffRdPtr, REC_BUFF_FIRE_THD) != 0)
            {
                KTV_REC_DBG(printf("1. File write fail."));
            }

            u32AudFileWriteSize += REC_BUFF_FIRE_THD;
            pRecInfo->u32BuffRdPtr += REC_BUFF_FIRE_THD;
            pRecInfo->u32BuffFreeSize += REC_BUFF_FIRE_THD;
            if (pRecInfo->u32BuffRdPtr == pRecInfo->u32BuffEnd)
            {
                pRecInfo->u32BuffRdPtr = pRecInfo->u32BuffStart;
                if (pRecInfo->bBuffRewind)
                {
                    pRecInfo->bBuffRewind = FALSE;
                }
            }
            else if (pRecInfo->u32BuffRdPtr > pRecInfo->u32BuffEnd)
            {
                KTV_REC_DBG(printf("Read PTR Error: 0x%x\n", pRecInfo->u32BuffRdPtr));
                return FALSE;
            }
            KTV_REC_DBG(printf("2. Buff need to write: 0x%x, RdPtr: 0x%x\n",
                (pRecInfo->u32BuffSize - pRecInfo->u32BuffFreeSize), pRecInfo->u32BuffRdPtr));
        }

    }
    else
    {
        if ((pRecInfo->u32BuffSize - pRecInfo->u32BuffFreeSize) > 0)
        {
            KTV_REC_DBG(printf("_MApp_KTV_WriteAudCompressdata, Flush all: 0x%x\n", bFlushAll));
            KTV_REC_DBG(printf("3. Buff need to write: 0x%x, RdPtr: 0x%x\n",
                (pRecInfo->u32BuffSize - pRecInfo->u32BuffFreeSize), pRecInfo->u32BuffRdPtr));
            if (pRecInfo->bBuffRewind)
            {
                u32Temp = pRecInfo->u32BuffEnd - pRecInfo->u32BuffRdPtr;
                KTV_REC_DBG(printf("1: Temp: 0x%x\n", u32Temp));
                //msAPI_FCtrl_FileWrite(pRecInfo->u8RecFilehandle, pRecInfo->u32BuffStart, REC_BUFF_SIZE);
                if (msAPI_FCtrl_FileWrite(pRecInfo->u8RecFilehandle, pRecInfo->u32BuffRdPtr, u32Temp) != 0)
                {
                    KTV_REC_DBG(printf("2. File write fail."));
                }
                pRecInfo->u32BuffRdPtr = pRecInfo->u32BuffStart;
                u32AudFileWriteSize += u32Temp;
                pRecInfo->u32BuffFreeSize += u32Temp;
                pRecInfo->bBuffRewind = FALSE;
            }



            u32Temp = pRecInfo->u32BuffWrPtr- pRecInfo->u32BuffRdPtr;
            KTV_REC_DBG(printf("2: Temp: 0x%x\n", u32Temp));
            //msAPI_FCtrl_FileWrite(pRecInfo->u8RecFilehandle, pRecInfo->u32BuffStart, REC_BUFF_SIZE);
            if (msAPI_FCtrl_FileWrite(pRecInfo->u8RecFilehandle, pRecInfo->u32BuffRdPtr, u32Temp) != 0)
            {
                KTV_REC_DBG(printf("3. File write fail."));
            }
            u32AudFileWriteSize += u32Temp;
            pRecInfo->u32BuffRdPtr = pRecInfo->u32BuffWrPtr;
            pRecInfo->u32BuffFreeSize += u32Temp;
            KTV_REC_DBG(printf("4. Buff need to write: 0x%x, RdPtr: 0x%x\n",
                (pRecInfo->u32BuffSize - pRecInfo->u32BuffFreeSize), pRecInfo->u32BuffRdPtr));
        }

    }
    return TRUE;
}

#endif

static void _MApp_KTV_WritePlayListFileToUsb(void)
{
    KTVFileInfo FileInfo;
    U8 u8Playlist[]=SONG_PLAYLIST_FILENAME;

    _MApp_KTV_QueryPlaylistFileInfo(&u8Playlist[0],&FileInfo);
    MApp_KTV_SetFileEntry(&(FileInfo.fileEntry));
    MApp_KTV_FileWrite(_u32SongListAddr,sizeof(ST_KTV_LIST));
}

static U8 _INIType[9][20]=
{
    {"Version"},
    {"Debug"},
    {"Skin"},
    {"MIC"},
    {"DB"},
    {"UPDATE"},
    {"Other1"},
    {"Other2"},
    {"Other3"},
};

static void _SetCustomerIni2Buf(U32 Addr, U32 u32filelength)
{
    U32 u32ParsedPos;
    U16 i;
    U8 *pu8Data = au8Section;
    U8 u8Data, u8Data1, j,tmp;

    for(u32ParsedPos=0; u32ParsedPos<u32filelength;)
    {
        msAPI_MIU_Copy(u32ParsedPos + Addr -INI_FILE_SIZE, XD2PHY(&u8Data), 1,   MIU_SDRAM2SDRAM);
        if(u8Data == '[')
        {
            for(i=0; i<20; i++)
            {
                u32ParsedPos ++;
                msAPI_MIU_Copy(u32ParsedPos + Addr -INI_FILE_SIZE, XD2PHY(&u8Data), 1,   MIU_SDRAM2SDRAM);
                if(u8Data != ']')
                {
                    pu8Data[i] = u8Data;
                }
                else
                {
                    pu8Data[i] = 0;
                    break;
                }
            }
            u32ParsedPos += 2;
            for(j=0; j<9; j++)
            {
                if(strcmp((char *)pu8Data, (char *)_INIType[j]) == 0)
                {
                    while(u8Data != '=')
                    {
                        u32ParsedPos ++;
                        msAPI_MIU_Copy(u32ParsedPos + Addr -INI_FILE_SIZE, XD2PHY(&u8Data), 1,   MIU_SDRAM2SDRAM);
                    }
                    i = 0;
                    //printf("\r\n");
                    do
                    {
                        u32ParsedPos ++;
                        msAPI_MIU_Copy(u32ParsedPos + Addr -INI_FILE_SIZE, XD2PHY(&u8Data), 1,   MIU_SDRAM2SDRAM);
                        msAPI_MIU_Copy(u32ParsedPos + 1 + Addr -INI_FILE_SIZE, XD2PHY(&u8Data1), 1,   MIU_SDRAM2SDRAM);
                        pu8Data[i] = u8Data;
                        //printf("  %c  ", pu8Data[i]);
                        i ++;
                    }while((u8Data != 0x0D) || (u8Data1 != 0x0A));
                    pu8Data[i - 1] = 0;
                    //printf("\r\n i = %d", i);

                    switch(j)
                    {
                        case 0: //Version
                            break;
                        case 1: //Debug
                            pu8Data[0] -= '0';// 7th
                            //printf("\r\n ***** %d ******", pu8Data[0]);
                            msAPI_MIU_Copy((U32)&pu8Data[0], Addr+INI_URL_SIZE*6, 1, MIU_SDRAM2SDRAM);
                            tmp=pu8Data[0];
                            if(tmp&0x02)
                                bForceHKPrintf=TRUE;
                            break;
                        case 2: //Skin
                            pu8Data[0] -= '0';// 8th
                            //printf("\r\n ***** %d ******", pu8Data[0]);
                            msAPI_MIU_Copy((U32)&pu8Data[0], Addr+INI_URL_SIZE*6 + 1, 1, MIU_SDRAM2SDRAM);
                            break;
                        case 3: //MIC
                            msAPI_MIU_Copy((U32)&pu8Data[0],Addr, i, MIU_SDRAM2SDRAM);
                            _sKtvIni.u8MicURLLength = i;
                            break;
                        case 4: //DB
                            msAPI_MIU_Copy((U32)&pu8Data[0],Addr+INI_URL_SIZE, i, MIU_SDRAM2SDRAM);
                            _sKtvIni.u8DBURLLength = i;
                            break;
                        case 5: //Update
                            msAPI_MIU_Copy((U32)&pu8Data[0],Addr+INI_URL_SIZE*2, i, MIU_SDRAM2SDRAM);
                            _sKtvIni.u8UpdateURLLength = i;
                            break;
                        case 6: //Other1
                            msAPI_MIU_Copy((U32)&pu8Data[0],Addr+INI_URL_SIZE*3, i, MIU_SDRAM2SDRAM);
                            _sKtvIni.u8URL1Length = i;
                            break;
                        case 7: //Other2
                            msAPI_MIU_Copy((U32)&pu8Data[0],Addr+INI_URL_SIZE*4, i, MIU_SDRAM2SDRAM);
                            _sKtvIni.u8URL2Length = i;
                            break;
                        case 8: //Other3
                            msAPI_MIU_Copy((U32)&pu8Data[0],Addr+INI_URL_SIZE*5, i, MIU_SDRAM2SDRAM);
                            _sKtvIni.u8URL3Length = i;
                            break;
                         default:
                            break;
                    }
                }
            }
        }
        else
            u32ParsedPos ++;

    }
}

static void _SetDefaultIni2Buf(U32 Addr)
{
    U8 *pu8Data = au8Section;
    snprintf((char*)pu8Data,sizeof(MIC_URL_DEF),"%s",MIC_URL_DEF);// 1st
    msAPI_MIU_Copy((U32)&pu8Data[0],Addr,sizeof(MIC_URL_DEF),MIU_SDRAM2SDRAM);
    _sKtvIni.u8MicURLLength = sizeof(MIC_URL_DEF);

    snprintf((char*)pu8Data,sizeof(DB_URL_DEF),"%s",DB_URL_DEF);// 2nd
    msAPI_MIU_Copy((U32)&pu8Data[0],Addr+INI_URL_SIZE,sizeof(DB_URL_DEF),MIU_SDRAM2SDRAM);
    _sKtvIni.u8DBURLLength = sizeof(DB_URL_DEF);

    snprintf((char*)pu8Data,sizeof(UPDATE_URL_DEF),"%s",UPDATE_URL_DEF);// 3rd
    msAPI_MIU_Copy((U32)&pu8Data[0],Addr+INI_URL_SIZE*2,sizeof(UPDATE_URL_DEF),MIU_SDRAM2SDRAM);
    _sKtvIni.u8UpdateURLLength = sizeof(UPDATE_URL_DEF);

    snprintf((char*)pu8Data,sizeof(Reserve_URL1_DEF),"%s",Reserve_URL1_DEF);// 4th
    msAPI_MIU_Copy((U32)&pu8Data[0],Addr+INI_URL_SIZE*3,sizeof(Reserve_URL1_DEF),MIU_SDRAM2SDRAM);
    _sKtvIni.u8URL1Length = sizeof(Reserve_URL1_DEF);

    snprintf((char*)pu8Data,sizeof(Reserve_URL2_DEF),"%s",Reserve_URL2_DEF);// 5th
    msAPI_MIU_Copy((U32)&pu8Data[0],Addr+INI_URL_SIZE*4,sizeof(Reserve_URL2_DEF),MIU_SDRAM2SDRAM);
    _sKtvIni.u8URL2Length = sizeof(Reserve_URL2_DEF);

    snprintf((char*)pu8Data,sizeof(Reserve_URL3_DEF),"%s",Reserve_URL3_DEF);// 6th
    msAPI_MIU_Copy((U32)&pu8Data[0],Addr+INI_URL_SIZE*5,sizeof(Reserve_URL3_DEF),MIU_SDRAM2SDRAM);
    _sKtvIni.u8URL3Length = sizeof(Reserve_URL3_DEF);

    pu8Data[0]=UART_DEF;// 7th
    pu8Data[1]=SKIN_DEF;// 8th
    msAPI_MIU_Copy((U32)&pu8Data[0],Addr+INI_URL_SIZE*6,2,MIU_SDRAM2SDRAM);

}

/******************************************************************************/
/// It will disconnect all USB and card reader devices.
/// @return enumMPlayerRet
/******************************************************************************/
enumKTVRet MApp_KTV_DisconnectAllDevices(void)
{
    msAPI_MSDCtrl_ResetDevices();
    MApp_FileBrowser_DeInit();
    if(_u16CurDriveIdx != KTV_INVALID_INDEX)
    {
        if(_DriveInfo[_u16CurDriveIdx].eDeviceType == E_KTV_USB0)
        {
            MApp_MassStorage_DriveDisconnect(_u16CurDriveIdx);
        }
    }

    _u8UserBrowserHandle = INVALID_BROWSER_HANDLE;
    _eKTVKnlFlags = E_KTV_KNL_FLG_NULL;
    _KTVMovieInfo.eKnlMovieFlag= E_KTV_KNL_MOVIE_FLG_NULL;

    return E_KTV_RET_OK;
}

//*****************************************************************************
//              Global Functions
//*****************************************************************************

/******************************************************************************/
/// KTV init
/******************************************************************************/
enumKTVRet MApp_KTV_Init(void)
{
    enumKTVRet eRet=E_KTV_RET_FAIL;
    KTVFileInfo FileInfo;
    U32 u32Addr,u32FileLength=0;
    U8 u8IniFile[]=INI_FILENAME;
    U8 u8SingerBin[]=SINGER_BIN_FILENAME;
    U8 u8SongBin[]=SONG_BIN_FILENAME;
    U8 u8SongList[]=SONG_PLAYLIST_FILENAME;

    g_total_song = 0;
    g_total_singer = 0;
    bContinuePlay = FALSE;
    eplayTheEnd = E_KTV_PLAY_NULL;

    bKTVCoProcesserReady = FALSE;

    _eKTVVolumeSetting.MusicVolume = KTV_MUSIC_VOLUME_DEF;
    _eKTVVolumeSetting.MicVolume = KTV_MIC_VOLUME_DEF;
    _eKTVVolumeSetting.MelodyVolume = KTV_MELODY_VOLUME_DEF;
    _eKTVVolumeSetting.Echo= KTV_ECHO_DEF;
    _eKTVVolumeSetting.MusicKey = KTV_MUSIC_KEY_DEF;
    _eKTVVolumeSetting.MusicTempo = KTV_MUSIC_TEMPO_DEF;
    _eKTVVolumeSetting.MusicMode = 0;

    bForceHKPrintf=FALSE;

  // parser ktv INI file into KTV_INI_BUFFER
    u32Addr = (U32)((KTV_DATABASE_BUFFER_MEMORY_TYPE & MIU1) ? (KTV_DATABASE_BUFFER_ADR | MIU_INTERVAL) : (KTV_DATABASE_BUFFER_ADR));
    eRet = MApp_KTV_QueryAsciiFileInfo(&u8IniFile[0],&FileInfo);
    if(eRet == E_KTV_RET_FAIL)
        _SetDefaultIni2Buf(u32Addr+INI_FILE_SIZE);
    else
    {
        MApp_KTV_SetFileEntry(&(FileInfo.fileEntry));
        u32FileLength = MApp_KTV_FileRead(u32Addr);
        if(u32FileLength > INI_FILE_SIZE)//if ini file exceed 2K,ingore it
        {
            _SetDefaultIni2Buf(u32Addr+INI_FILE_SIZE);
        }
        else
        {
            _SetCustomerIni2Buf(u32Addr+INI_FILE_SIZE, u32FileLength);
        }
    }
    u32FileLength = INI_FILE_SIZE+INI_DATA_SIZE;// 4K bytes ,2K file ,2K paser data
    if(bForceHKPrintf)
        MApp_VDPlayer_UartSwitch(E_UART_SWITCH_TO_HK);

  // load ktv singer database bin file into KTV_DATABASE_BUFFER
    u32Addr = (U32)((KTV_DATABASE_BUFFER_MEMORY_TYPE & MIU1) ? (KTV_DATABASE_BUFFER_ADR | MIU_INTERVAL) : (KTV_DATABASE_BUFFER_ADR))+MemAlign(u32FileLength,MemAlignUnit);
    KTV_DBG(printf("SingerBin Addr=%lx\n",u32Addr));
    eRet = MApp_KTV_QueryAsciiFileInfo(&u8SingerBin[0],&FileInfo);
    if(eRet == E_KTV_RET_FAIL)
        return eRet;
    MApp_KTV_SetFileEntry(&(FileInfo.fileEntry));
    u32FileLength = MApp_KTV_FileRead(u32Addr);
    g_total_singer=*(U32 *)(u32Addr+TOTAL_ITEM_OFFSET);
    _u32SingerVersion0=*(U32 *)(u32Addr+0);
    _u32SingerVersion1=*(U32 *)(u32Addr+12);
    _u32SingerVersion1&=0x00ffffff;
    KTV_DBG(printf("_u32SingerVersion0=%x\n",_u32SingerVersion0););
    KTV_DBG(printf("_u32SingerVersion1=%x\n",_u32SingerVersion1););
    stp_ktv_singerbuf=(const TKtvSinger *)(u32Addr+FILE_HEADER_SIZE);
    KTV_DBG(printf("total singer %d\n",g_total_singer));
    KTV_DBG(printf("ktv first singer id 0x%02x\n",stp_ktv_singerbuf->ID));

  // load ktv song database bin file into KTV_DATABASE_BUFFER
    u32Addr = u32Addr+MemAlign(u32FileLength,MemAlignUnit);
    KTV_DBG(printf("u8SongBin Addr=%lx\n",u32Addr));
    eRet = MApp_KTV_QueryAsciiFileInfo(&u8SongBin[0],&FileInfo);
    if(eRet == E_KTV_RET_FAIL)
        return eRet;
    MApp_KTV_SetFileEntry(&(FileInfo.fileEntry));
    u32FileLength = MApp_KTV_FileRead(u32Addr);
    g_total_song=*(U32 *)(u32Addr+TOTAL_ITEM_OFFSET);
    KTV_DBG(printf("total song %d\n",g_total_song));
    _u32MusicVersion0=*(U32 *)(u32Addr+0);
    _u32MusicVersion1=*(U32 *)(u32Addr+12);
    _u32MusicVersion1&=0x00ffffff;
    KTV_DBG(printf("_u32MusicVersion0=%x\n",_u32MusicVersion0););
    KTV_DBG(printf("_u32MusicVersion1=%x\n",_u32MusicVersion1););
    stp_ktv_songbuf=(const TKtvTable *)(u32Addr+FILE_HEADER_SIZE);
    KTV_DBG(printf("ktv first song id 0x%lx\n",stp_ktv_songbuf->dwSongID));

  // read KTV Play List file into st_ktv_list buffer
    u32Addr = u32Addr+MemAlign(u32FileLength,MemAlignUnit);
    _u32SongListAddr = u32Addr;
    KTV_DBG(printf("_u32SongListAddr=%lx\n",u32Addr));

    st_ktv_list =(ST_KTV_LIST*)_u32SongListAddr;
    eRet = MApp_KTV_QueryAsciiFileInfo(u8SongList,&FileInfo);
    if(eRet == E_KTV_RET_FAIL)
    {
        KTV_DBG(printf("create new file & init play list buffer!!!\n"));
        // create new file in here
        memset((U8*)st_ktv_list,0,sizeof(ST_KTV_LIST));
    }
    else
    {
        MApp_KTV_SetFileEntry(&(FileInfo.fileEntry));
        u32FileLength = MApp_KTV_FileRead((U32)st_ktv_list);
        if(u32FileLength==0)
        {
            KTV_DBG(printf("create new file or file invalid!!!\n"));
        }
        printf("played song counter %d,favor song counter %d\n",st_ktv_list->u8playedsongcounter,st_ktv_list->u8favorsongcounter);
        _MApp_KTV_Check_PlayList();
    }

  // assign  st_searchedsong_buf  address
    u32Addr = u32Addr+MemAlign(sizeof(ST_KTV_LIST),MemAlignUnit);
    st_searchedsong_buf = (ST_SEARCHED_SONGS*)u32Addr;
    KTV_DBG(printf("st_searchedsong_buf=%lx\n", st_searchedsong_buf));

  // assign  st_searchedsinger_buf  address
    u32Addr = u32Addr+MemAlign(sizeof(ST_SEARCHED_SONGS),MemAlignUnit);
    st_searchedsinger_buf = (ST_SEARCHED_SINGERS*)u32Addr;
    KTV_DBG(printf("st_searchedsinger_buf=%lx\n", st_searchedsinger_buf));

  // calculate whether the KTV database end of address overflow
    u32Addr = u32Addr+MemAlign(sizeof(ST_SEARCHED_SINGERS),MemAlignUnit);
    if(KTV_DATABASE_BUFFER_LEN < (u32Addr-((KTV_DATABASE_BUFFER_MEMORY_TYPE & MIU1) ? (KTV_DATABASE_BUFFER_ADR | MIU_INTERVAL) : (KTV_DATABASE_BUFFER_ADR))))
        ASSERT(0);

  // assign  st_KTV_Lyric_buf_adr  address  (KTV_LYRIC_BUFFER_LEN)
    u32Addr = (U32)KTV_LRC_BUFFER_ADR;
    st_KTV_Lyric_buf_adr = u32Addr;
    KTV_DBG(printf("st_KTV_Lyric_buf_adr=%lx\n", st_KTV_Lyric_buf_adr));

  // assign  st_KTV_Lyric_tags_adr  address (KTV_LYRIC_TAG_LEN)
    u32Addr = u32Addr+MemAlign(KTV_LYRIC_BUFFER_LEN, MemAlignUnit);
    st_KTV_Lyric_tags_adr = u32Addr;
    KTV_DBG(printf("st_KTV_Lyric_tags_adr=%lx\n", st_KTV_Lyric_tags_adr));

  // assign  st_KTV_Lyric_words_adr  address  (KTV_LYRIC_WORDS_LEN)
    u32Addr = u32Addr+MemAlign(KTV_LYRIC_TAG_LEN, MemAlignUnit);
    st_KTV_Lyric_words_adr = u32Addr;
    KTV_DBG(printf("st_KTV_Lyric_tags_adr=%lx\n", st_KTV_Lyric_tags_adr));


    // load ktv sound font file into KTV_SOUND_FONT_BUFFER_ADR
    eKTVLoadFileAttribute |= E_KTV_BEGIAN_LOAD;
    if(!(eKTVLoadFileAttribute & E_KTV_SOUNDFONT_LOADED))
    {
        _u32SoundFontFileLen = MApp_KTV_LoadSoundFontFile();
    }
    _u8NetWorkState = E_CHECK_COPROCESSER_READY;
    _eKTVMoviePlayMode=E_KTV_MOVIE_STOP;
    return eRet;
}

void MAPP_KTV_Init2(void)
{
    // load ktv sound font file into KTV_SOUND_FONT_BUFFER_ADR
    MApp_KTV_SetSoundFontMemoryAddr(KTV_SOUND_FONT_BUFFER_ADR, _u32SoundFontFileLen);

    // set ktv Mic Memory addr and size
    MApp_KTV_SetSoundMicMemoryAddr(KTV_MIDI_BUFFER_ADR, KTV_MIDI_BUFFER_LEN);

    // set ktv LRC Memory addr and size
    MApp_KTV_Set_LRC_MemoryAddr(KTV_LRC_BUFFER_ADR, KTV_LRC_BUFFER_LEN);

    // set ktv Music Volume
    MApp_KTV_SendMailBoxCmd(MB_KTV_CMD_SET_MUSIC_VOL, _eKTVVolumeSetting.MusicVolume);

    // set ktv Music Key
    MApp_KTV_SendMailBoxCmd(MB_KTV_CMD_SET_MUSIC_KEY, _eKTVVolumeSetting.MusicKey);

    // set ktv Music Melody
    MApp_KTV_SendMailBoxCmd(MB_KTV_CMD_SET_MUSIC_MELODY, _eKTVVolumeSetting.MelodyVolume);

    // set ktv Music Tempo
    MApp_KTV_SendMailBoxCmd(MB_KTV_CMD_SET_MUSIC_TEMPO, _eKTVVolumeSetting.MusicTempo);

    // parser ktv ini file into KTV_DATABASE_BUFFER_ADR+INI_FILE_SIZE
    MApp_KTV_Set_INI_MemoryAddr(((KTV_DATABASE_BUFFER_MEMORY_TYPE & MIU1) ? (KTV_DATABASE_BUFFER_ADR | MIU_INTERVAL) : (KTV_DATABASE_BUFFER_ADR))+INI_FILE_SIZE);
}

/******************************************************************************/
/// It will initialize the KTV usb devices.
/// @return enumKTVRet
/******************************************************************************/
enumKTVRet MApp_KTV_InitializeUsbDevice(void)
{
    U8 u8DeviceCnt;

    KTV_DBG(printf("MApp_KTV_InitializeUsbDevice\n"));
    u8DeviceCnt = 0;
    _PrevUSBDeviceStatus = E_KTV_USB_NONE;
    memset(_KTVDeviceStatus, 0, sizeof(KTVDeviceStatus));
    _u8TotalDriveNum = 0;

     if((MApp_MassStorage_DeviceConnectionDetect() & MS_USB_CONNECTED) ||
        (MApp_MassStorage_DeviceConnectionDetect() & MS_USB2_CONNECTED))
    {
        MApp_MassStorage_DeviceStatusCheck();
        _u16DeviceValidStatus = MApp_MassStorage_GetValidDevice();

        if(MApp_MassStorage_DeviceConnectionDetect() & MS_USB_CONNECTED)
        {
            _u8CurDeviceIdx = E_KTV_USB0;
        }
        else if(MApp_MassStorage_DeviceConnectionDetect() & MS_USB2_CONNECTED)
        {
            _u8CurDeviceIdx = E_KTV_USB1;
        }
        else
        {
            _u8CurDeviceIdx = E_KTV_INVALID;
        }
        _u16CurDriveIdx = KTV_INVALID_INDEX;
        _eKTVKnlFlags |= E_KTV_KNL_FLG_DEVICE_INITIALIZED;
        _u32DeviceCheckTimer = msAPI_Timer_GetTime0();
        return E_KTV_RET_OK;
    }

    _u16CurDriveIdx = KTV_INVALID_INDEX;
    _eKTVKnlFlags |= E_KTV_KNL_FLG_DEVICE_INITIALIZED;
    _u32DeviceCheckTimer = msAPI_Timer_GetTime0();

    return E_KTV_RET_FAIL;

}

/******************************************************************************/
/// Set the drive to be the current drive and initialize file system for it.
/// @param  u16DriveIdx \b IN Speccify the drive index.
/// @return enumKTVRet
/******************************************************************************/
enumKTVRet MApp_KTV_ConnectDrive(U16 u16DriveIdx)
{
    static U8 u8PreUserBrowserHandle = INVALID_BROWSER_HANDLE;
    BOOLEAN bFound = FALSE;
    U8 i;

    KTV_DBG(printf("MApp_KTV_ConnectDrive %d\n", u16DriveIdx));
    KTV_DBG(printf("MApp_MassStorage_GetTotalDriveNum %bd\n", MApp_MassStorage_GetTotalDriveNum()));
    //Check drive index and assign active drive
    for(i=0; i<MApp_MassStorage_GetTotalDriveNum(); i++)
    {
        KTV_DBG(printf("\n _DriveInfo[i].u8Partition=%bd",_DriveInfo[i].u8Partition));
        if(_DriveInfo[i].u8Partition == u16DriveIdx)
        {
            if(_DriveInfo[i].u8Lun < MSD_USB_INDEX_END)
            {
                _u8CurDeviceIdx = E_KTV_USB0;
                bFound = TRUE;
                break;
            }
            else
            {
                _u8CurDeviceIdx = E_KTV_USB1;
                bFound = TRUE;
                break;
            }
        }
    }
    if(!bFound)
    {
        return E_KTV_RET_FAIL;
    }
    MApp_FileBrowser_Destroy(u8PreUserBrowserHandle);

    _u16TotalFileNum = 0;
    if(!MApp_MassStorage_DriveConnect(u16DriveIdx))
    {
        KTV_DBG(printf("MApp_KTV_ConnectDrive No Device\n"));
        return E_KTV_RET_FAIL;
    }

    _u8UserBrowserHandle = MApp_FileBrowser_Create(u16DriveIdx);
    if(_u8UserBrowserHandle == INVALID_BROWSER_HANDLE)                                     //<--FILE BROWSER SECOND
    {
        KTV_DBG(printf("MApp_KTV_ConnectDrive File browser Failed\n"));
        return E_KTV_RET_FAIL;
    }
    u8PreUserBrowserHandle = _u8UserBrowserHandle;
    MApp_FileBrowser_SetEnvironment(_u8UserBrowserHandle);

    for(i=0;i<NUM_OF_MAX_KTV_DIRECTORY_DEPTH+1;i++)
    {
        _u16CurDirectory[i] = MPLAYER_INVALID_INDEX;
        _u16BufDirectory[i] = MPLAYER_INVALID_INDEX;
    }

    _u16CurDirectoryDepth = 0;
    _u16BufDirectoryDepth = MPLAYER_INVALID_INDEX;
    _u16BufReadLongNameIdx = MPLAYER_INVALID_INDEX;
    memset(_u16DirectoryNum, 0, sizeof(U16)*NUM_OF_MAX_KTV_DIRECTORY_DEPTH);
    _u16CurFileIdx = 0;

    _u16CurDriveIdx = u16DriveIdx;
    _MApp_KTV_Browser_EnumCurDirectory();

    if(_u16TotalFileNum==0)
    {
        return E_KTV_RET_FAIL;
    }
    _u8TotalDriveNum = MApp_MassStorage_GetTotalDriveNum();

    return E_KTV_RET_OK;
}


void MApp_KTV_OpenMicFileToBuffer(void)
{
    enumKTVRet eRet=E_KTV_RET_FAIL;
    KTVFileInfo FileInfo;
    snprintf((char *)&u8LyricFileName, 5, "%d", st_ktv_list->st_play_song_list[0].u32Song_ID);
    memcpy(u8LyricExtFilename, ".mic", sizeof(".mic"));
    strcat((char *)u8LyricFileName, (char *)u8LyricExtFilename);
    eRet = MApp_KTV_QueryAsciiFileInfo(u8LyricFileName, &FileInfo);
    if(eRet == E_KTV_RET_FAIL)
    {
        printf("\r\n  KTV open mic file from USB fail,download from server ");
        MApp_KTV_DownloadMicFile(st_ktv_list->st_play_song_list[0].u32Song_ID);
        return;
    }
    MApp_KTV_SetFileEntry(&(FileInfo.fileEntry));
    u32MicFileLen = MApp_KTV_FileRead((U32)KTV_MIDI_BUFFER_ADR);
    MApp_KTV_SetSoundMicMemoryAddr(KTV_MIDI_BUFFER_ADR, u32MicFileLen);
    MApp_KTV_OpenMicFileFromUsb();
}

void MApp_KTV_Stop_All(void)
{
    if( enKTVLyricState == STATE_KTV_LYRIC_PLAY )
        MApp_KTV_Stop();
    else
        return;

    if(_eKTVMoviePlayMode != E_KTV_MOVIE_STOP)
    {
        _MApp_KTV_Stop_Movie();
    }
    _eKTVMoviePlayMode = E_KTV_MOVIE_STOP;
    _eKTVMovieActionMode =E_KTV_MOVIE_ACTION_STOP;

    MApp_UiMenu_iSingCloseSubtitle();
    enKTVLyricState = STATE_KTV_LYRIC_INIT;

    bContinuePlay = FALSE;
}


//=============================================================================/
//============================ KTV task ==================================
//=============================================================================/
/******************************************************************************/
/// KTV task
/******************************************************************************/
void MApp_KTV_Task(void)
{
    U8 u8TotalDriveNum;
    U16 u16ValidDevice;
    U32 u32CurTime;
    BOOLEAN bContinue;
    EN_KTV_DISK_STATUS eUSBDeviceStatus;
#if ENABLE_AUDIO_ENCODE
    U32 u32AudWrPtr = 0;
    U32 u32AudWrSize = 0;
#endif

    if( UI_INPUT_SOURCE_TYPE != UI_INPUT_SOURCE_KTV)
        return;

    if((_eKTVKnlFlags & E_KTV_KNL_FLG_DEVICE_INITIALIZED) &&
       (msAPI_Timer_DiffTimeFromNow(_u32DeviceCheckTimer) > 500))
    {
        BOOLEAN bPort1Changed, bPort2Changed;
        BOOL bDriveMapChged;

        if(!MDrv_UsbDeviceConnect()&&!MDrv_UsbDeviceConnect_Port2())
           MApp_KTV_Stop_All();
        else
        {
            if(MApp_MassStorage_DeviceChangeStatusCheck())
                MApp_MassStorage_DeviceStatusCheck();
            u16ValidDevice = MApp_MassStorage_GetValidDevice();
            u8TotalDriveNum = MApp_MassStorage_GetTotalDriveNum();
            bDriveMapChged =  (_u16DeviceValidStatus!=u16ValidDevice || _u8TotalDriveNum!=u8TotalDriveNum);

            bPort1Changed = msAPI_MSDCtrl_IsPortChanged(MSD_PORT_1);
        	bPort2Changed = msAPI_MSDCtrl_IsPortChanged(MSD_PORT_2);
        	if(bPort1Changed || bPort2Changed ||bDriveMapChged)
            {
                _u16DeviceValidStatus = u16ValidDevice;
                _u8TotalDriveNum = u8TotalDriveNum;

                if(_u8CurDeviceIdx == E_KTV_INVALID)
                {
                    _MApp_KTV_DisconnectDrive();
                    if(MApp_KTV_InitializeUsbDevice() == E_KTV_RET_OK)
                    {
                        if(MApp_KTV_ConnectDrive(0) == E_KTV_RET_OK)//only connect C: driver
                        {
                            KTV_DBG(printf("1) connect drive 0 OK ^_^\n"));
                            if(MApp_KTV_Init() == E_KTV_RET_FAIL)
                            {
                                _u8CurDeviceIdx = E_KTV_INVALID;
                                printf("KTV resource file miss,please check USB Disk\n");
                                //show UI
                            }
                        }
                    }
                }
                else if((bPort1Changed && _u8CurDeviceIdx == E_KTV_USB0))
                {
                    if(MApp_KTV_InitializeUsbDevice() == E_KTV_RET_OK)
                    {
                        if(MApp_KTV_ConnectDrive(0) == E_KTV_RET_OK)//only connect C: driver
                        {
                            KTV_DBG(printf("2) connect drive 0 OK ^_^\n"));
                            if(MApp_KTV_Init() == E_KTV_RET_FAIL)
                            {
                                _u8CurDeviceIdx = E_KTV_INVALID;
                                printf("KTV resource file miss,please check USB Disk\n");
                                //show UI
                            }
                        }
                    }
                }
            else if(bPort2Changed)
            {
                if(MApp_KTV_InitializeUsbDevice() == E_KTV_RET_OK)
                {
                    if(MApp_KTV_ConnectDrive(0) == E_KTV_RET_OK)//only connect C: driver
                    {
                        KTV_DBG(printf("connect drive 0 OK ^_^\n"));
                        if(MApp_KTV_Init() == E_KTV_RET_FAIL)
                        {
                            _u8CurDeviceIdx = E_KTV_INVALID;
                            printf("KTV resource file miss,please check USB Disk\n");
                            //show UI
                        }
                    }
                }
            }
                else
                {
                    _u8CurDeviceIdx = E_KTV_INVALID;
                }
            }
            else
            {
                eUSBDeviceStatus = (EN_KTV_DISK_STATUS)msAPI_GetUsbDeviceStatus();
                if(_PrevUSBDeviceStatus != eUSBDeviceStatus)
                {
                    _PrevUSBDeviceStatus = eUSBDeviceStatus;
                }
            }
        }
    _u32DeviceCheckTimer = msAPI_Timer_GetTime0();
    }

    if((_eKTVKnlFlags & E_KTV_KNL_FLG_DEVICE_INITIALIZED)&&(_u8CurDeviceIdx != E_KTV_INVALID))
    {
        MApp_KTV_MailBoxHandler();
        msAPI_APEngine_ProcessMailBox();
        MApp_KTV_AutoUpdate();
        MApp_KTV_CheckCoProcesserReady_Task();
    }
    else
    {
        _u8NetWorkState=0;
        _u32NetUpdateCounter=0;
        _u32NetErrorCounter=0;
        _u32NetIPAddress=0;
        _u32NetInfoLen=0;
        _u32NetVersion=0;
        _u32MusicVersion0=0;
        _u32MusicVersion1=0;
        _u32SingerVersion0=0;
         _u32SingerVersion1=0;
        _u32NetSWVersion=0;
        _u32MergeVersion0=AP_SW_VERSION;
        _u32MergeVersion1=(MAGIC_APP&0x00ffffff);
    }


    if(_KTVMovieInfo.eKnlMovieFlag & E_KTV_KNL_MOVIE_FLG_PLAY)//movie playing task
    {
        static BOOLEAN bInitOk = FALSE;
        bContinue = TRUE;
        if(_KTVMovieInfo.eKnlMovieFlag & E_KTV_KNL_MOVIE_FLG_FILE_INIT)
        {
            _KTVMovieInfo.eKnlMovieFlag &= (enumKTVKnlMovieFlags)~E_KTV_KNL_MOVIE_FLG_FILE_INIT;

            if(MApp_VDPlayer_Init(VIDEO_PLAYER_INPUT_SOURCE_KTV, VIDEO_PLAYER_PLAYING_TYPE_MPEG4, &_KTVMovieInfo.curPlayingFileEntry) == TRUE)
            {
                bInitOk = TRUE;
                MApp_VDPlayer_Play();
                MApp_VDPlayer_EnableVideoOutputFlag(ENABLE);
                _KTVMovieInfo.eKnlMovieFlag |= E_KTV_KNL_MOVIE_FLG_PREDECODE_OK;
            }
            else
            {
                // ERROR Handling :
                // MUST not set media sub-type to E_MPLAYER_SUBTYPE_INVALID, or it will be blocked
                bInitOk = FALSE;
                return; //prevent to skip twice at same time when meets error file.
            }
        }

        if(_eMovieMainExit != EXIT_VDPLAYER_WAIT && _eMovieMainExit != EXIT_VDPLAYER_EXIT)
        {
            _eMovieMainExit = MApp_VDPlayer_Main();
        }
        switch(_eMovieMainExit)
        {
        case EXIT_VDPLAYER_WAIT:
        case EXIT_VDPLAYER_EXIT:
            if(_eMovieMainExit == EXIT_VDPLAYER_EXIT)
            {
                bContinue = FALSE;
            }
            else if(_eMovieMainExit == EXIT_VDPLAYER_WAIT)
            {
                // If fast backward to start of file, still start playing current file.
                if(_eKTVMoviePlayMode >= E_KTV_MOVIE_FB_2X &&
                    _eKTVMoviePlayMode <= E_KTV_MOVIE_FB_16X)
                {
                    bContinue = _MApp_KTV_PlayMovieAgain();
                }
                else
                {
                    bContinue = _MApp_KTV_PlayMovieNext();
                }
            }
            break;
        default:
            break;
        }

        if(bContinue == FALSE)
        {
            _KTVMovieInfo.eKnlMovieFlag &= (enumKTVKnlMovieFlags)~E_KTV_KNL_MOVIE_FLG_PLAY;
        }
        else if(bInitOk)
        {
            if(msAPI_Timer_DiffTimeFromNow(_u32PlayCheckTime)>200)
            {
                u32CurTime = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CUR_TIME);

                u32CurTime /= 1000;
                if (_u16PlayingTickTime != (U16)u32CurTime)
                {
                    _u16PlayingTickTime = (U16)u32CurTime;
                }
                _u32PlayCheckTime = msAPI_Timer_GetTime0();
            }
        }
    }


    //save play list file to disk task if modify playlist
    if((_eKTVKnlFlags & E_KTV_KNL_FLG_PLAYLIST_MODIFIED) &&
       (msAPI_Timer_DiffTimeFromNow(_u32SongListCheckTimer) > 5000))
    {
        printf("\n save play list file to disk\n");
        _MApp_KTV_WritePlayListFileToUsb();
        _eKTVKnlFlags &= (enumKTVKnlFlags)(~E_KTV_KNL_FLG_PLAYLIST_MODIFIED);

        _u32SongListCheckTimer = msAPI_Timer_GetTime0();
    }

    //RobertYang
#if ENABLE_AUDIO_ENCODE
    if (bEncoding)
    {
        //printf("Encoding..\n");
        //Get Audio encoding ISR
        if (gu8MADEncodeDone)
        {
            //Get Audio output compressed data info
            if (_MApp_KTV_CheckOutputRequest(&u32AudWrPtr, &u32AudWrSize))
            {
                //Copy Audio compressed data to buffer
                if (!_MApp_KTV_GetAudCompressData(u32AudWrPtr, u32AudWrSize))
                {
                    KTV_DBG(printf("Get Audio data fail\n"));
                }
            }
            _MApp_KTV_SetAudIntAck();

            gu8MADEncodeDone= 0;
        }

        //write compressed data to file

        if (pRecInfo->u32BuffFreeSize < pRecInfo->u32BuffSize)
        {
            if (!_MApp_KTV_WriteAudCompressdata(FALSE))
            {
                KTV_DBG(printf("write Audio Data Fail\n"));
            }
        }

    }
#endif

    switch(enKTVLyricState)
    {
        case STATE_KTV_LYRIC_INIT:
            MApp_MIC_LyricInit();
            if((st_ktv_list->u8playsongcounter > 0) && bContinuePlay)
            {
                eplayTheEnd = E_KTV_PLAY_NEXT;
                enKTVLyricState = STATE_KTV_LYRIC_PLAY_NEXT;
            }
            else if(bContinuePlay)
            {
                eplayTheEnd = E_KTV_PLAY_ALL_END;
                bContinuePlay = FALSE;
                enKTVLyricState = STATE_KTV_LYRIC_WAIT;
            }
            else
            {
                enKTVLyricState = STATE_KTV_LYRIC_WAIT;
            }
            break;

        case STATE_KTV_LYRIC_WAIT:
            break;

        case STATE_KTV_LYRIC_PLAY_NEXT:
        {
            MApp_KTV_OpenMicFileToBuffer();
            eKTVLoadFileAttribute |= E_KTV_BEGIAN_LOAD;
            enKTVLyricState = STATE_KTV_LYRIC_GET_LRC_SIZE;
        }
        break;

        case STATE_KTV_LYRIC_GET_LRC_SIZE:
            #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
            #endif
            MApp_KTV_MailBoxHandler();
            if(!bServerError)
            {
                if( bUpdateLRCFileReady )
                {
                    bUpdateLRCFileReady = FALSE;
                if(_eKTVMovieActionMode != E_KTV_MOVIE_ACTION_PLAY)
                {
                    _eKTVMovieActionMode =E_KTV_MOVIE_ACTION_PLAY;
                }
                    enKTVLyricState = STATE_KTV_LYRIC_PARSER;
                }
            }
            else
            {
                bServerError = FALSE;
                bShowErrorInfo = TRUE;
                MApp_PlayedSong(0,  st_ktv_list);
                u8KeyCode = KEY_GREEN;
                enKTVLyricState = STATE_KTV_LYRIC_INIT;
            }

            break;

        case STATE_KTV_LYRIC_PARSER:
        #if 0  // for test
            {
                KTVFileInfo FileInfo;
                U8 u8Playlist[]="LYRIC.TXT";

                _MApp_KTV_QueryPlaylistFileInfo(&u8Playlist[0],&FileInfo);
                MApp_KTV_SetFileEntry(&(FileInfo.fileEntry));
                MApp_KTV_FileWrite(st_KTV_Lyric_buf_adr, u32LyricFileLen);
            }
        #endif
            if(MApp_MIC_Lyrics_Parser(u32LyricFileLen))
            {
                U8 i, u8SingerNameLen, u8SongNameLen;
                U16 u16Data = 0;
                U16 u16SongName[30];
                U16 u16SingerName[12];
                //printf(" [STATE_KTV_LYRIC_PARSER  OK]\n");
                u16preDowncounterLyricPos = 0;
                u16preLine1LyricPos = 0;
                u16preLine2LyricPos = 0;
            #if DYNAMIC_VECTOR_FONT_ENABLE
                for(i=0; i<st_ktv_list->st_play_song_list[0].u16SongSting[0]; i++)
                {
                    u16SongName[i] = st_ktv_list->st_play_song_list[0].u16SongSting[i+1];
                    u16SongName[i+1] = 0;
                msAPI_MIU_Copy(XD2PHY(&(st_ktv_list->st_play_song_list[0].u16SongSting[i+1])),  st_KTV_Lyric_words_adr + u16LyricWordsCount * 2,  2, MIU_SDRAM2SDRAM);
                msAPI_MIU_Copy(XD2PHY(&u16Data),  st_KTV_Lyric_words_adr + (u16LyricWordsCount + 1)*2,  2, MIU_SDRAM2SDRAM);
                    u16LyricWordsCount ++;
                }
                u8SongNameLen = i - 1;
                for(i=0; i<st_ktv_list->st_play_song_list[0].u16SingerSting[0]; i++)
                {
                    u16SingerName[i] = st_ktv_list->st_play_song_list[0].u16SingerSting[i+1];
                    u16SingerName[i+1] = 0;
                msAPI_MIU_Copy(XD2PHY(&(st_ktv_list->st_play_song_list[0].u16SingerSting[i+1])),  st_KTV_Lyric_words_adr + u16LyricWordsCount * 2,  2, MIU_SDRAM2SDRAM);
                msAPI_MIU_Copy(XD2PHY(&u16Data),  st_KTV_Lyric_words_adr + (u16LyricWordsCount + 1)*2,  2, MIU_SDRAM2SDRAM);
                    u16LyricWordsCount ++;
                }
                u8SingerNameLen = i - 1;
                Dyx_MVF_LoadFont((U16 *)st_KTV_Lyric_words_adr);
            #endif
                MApp_UiMenu_iSingOpenSubtitle();
                wcscpy((U16 *)au8LineSection, u16SongName);
                u16SongNameDisplayOffset = (KTV_LYRIC_GW_HSIZE - u8SongNameLen * MS_DYNAMIC_FONTOUTPUTSIZE)/2;
                MApp_UiMenu_iSingDisplaySubtitle(1);
                wcscpy((U16 *)au8LineSection, u16SingerName);
                u16SingerNameDisplayOffset = (KTV_LYRIC_GW_HSIZE - u8SingerNameLen * MS_DYNAMIC_FONTOUTPUTSIZE)/2 - KTV_LYRIC_SECONDLINE_OFFSET/2;
                MApp_UiMenu_iSingDisplaySubtitle(2);
                u16SingerNameDisplayOffset = 0;
                u16SongNameDisplayOffset = 0;
                bSongNameDisplay = TRUE;
                MApp_KTV_Play();
                st_mic_info.u32PlayStartTime = msAPI_Timer_GetTime0();
                st_mic_info.u32Duration = 0;
                bCheckTime = FALSE;
                enKTVLyricState = STATE_KTV_LYRIC_PLAY;
                eKTVLoadFileAttribute |= E_KTV_SONG_LOADED;
                u8CountNum = 10;
            }
            else
            {
                enKTVLyricState = STATE_KTV_LYRIC_INIT;
            }
            break;

        case STATE_KTV_LYRIC_PLAY:
            {
                U32 u32LyricTime;

                if(*(U32 *)(KTV_LRC_BUFFER_ADR + KTV_LRC_BUFFER_LEN - 4) > LYRIC_TIME_OFFSET)
                {
                u32LyricTime = *(U32 *)(KTV_LRC_BUFFER_ADR + KTV_LRC_BUFFER_LEN - 4) - LYRIC_TIME_OFFSET ;
                }
                else
                {
                    u32LyricTime = 0;
                }
                st_mic_info.u32Duration = msAPI_Timer_GetTime0()  - st_mic_info.u32PlayStartTime;
                //printf("\r\n time = %lx  ms  %lx  ms ", u32LyricTime, st_mic_info.u32Duration);
                if(!bCheckTime)
                {
                    U32 u32offset;
                    if(u32LyricTime > st_mic_info.u32Duration)
                    {
                        u32offset = u32LyricTime - st_mic_info.u32Duration;
                        if(u32offset > 100)
                        {
                            st_mic_info.u32PlayStartTime -= u32offset;
                            st_mic_info.u32Duration += u32offset;
                            bCheckTime = TRUE;
                        }
                    }
                    else
                    {
                        u32offset = st_mic_info.u32Duration - u32LyricTime;
                        if(u32offset > 100)
                        {
                            st_mic_info.u32PlayStartTime += u32offset;
                            st_mic_info.u32Duration -= u32offset;
                            bCheckTime = TRUE;
                        }
                    }
                }
                if(MApp_KTV_GetDownCounterLyricTag(st_mic_info.u32Duration, &curLyricTag))
                {
                    if(u16preDowncounterLyricPos != curLyricTag.u16LyricPos)
                    {
                        u16preDowncounterLyricPos = curLyricTag.u16LyricPos;
                        _MApp_KTV_GetLyric( curLyricTag.u16LyricPos, au8LineSection);
                        //printf("\r\n au8LineSection[0-1] = %bx  %bx", au8LineSection[0], au8LineSection[1]);
                        //printf("\r\n au8LineSection[2-3] = %bx  %bx", au8LineSection[2], au8LineSection[3]);
                        //printf("\r\n st_mic_info.u32Duration = %d  ", st_mic_info.u32Duration);
                        //printf("\r\n curLyricTag.u16LyricPos = %x   u8DisplayPos = %d", curLyricTag.u16LyricPos, curLyricTag.u8DisplayPos);
                        //printf("\r\n curLyricTag.u8BlushColor = %d   u16Duringtime = %d", curLyricTag.u8BlushColor, u16Duringtime);
                        if(au8LineSection[0] == '0' && curLyricTag.u8DisplayPos == 3)
                        {
                            au8LineSection[0] = 0;
                        }
                        MApp_UiMenu_iSingDisplaySubtitle(0);
                    }
                }
                if(MApp_KTV_GetLine1LyricTag(st_mic_info.u32Duration, &curLyricTag, &u16Duringtime))
                {
                    if(u16preLine1LyricPos != curLyricTag.u16LyricPos)
                    {
                        u16preLine1LyricPos = curLyricTag.u16LyricPos;
                        u8CharNum = _MApp_KTV_GetLyric( curLyricTag.u16LyricPos, au8LineSection);
                        //printf("\r\n ***1***u8CharNum = %d ", u8CharNum);
                        if(curLyricTag.u8BlushColor)
                        {
                            MApp_UiMenu_iSingDrawSubtitleChar(1, u16Duringtime);
                        }
                        else
                        {
                            MApp_UiMenu_iSingDisplaySubtitle(1);
                            if(bSongNameDisplay)
                            {
                                bSongNameDisplay = FALSE;
                                au8LineSection[0] = 0;
                                au8LineSection[1] = 0;
                                MApp_UiMenu_iSingDisplaySubtitle(2);
                            }
                        }
                    }
                }
               if(MApp_KTV_GetLine2LyricTag(st_mic_info.u32Duration, &curLyricTag, &u16Duringtime))
                {
                    if(u16preLine2LyricPos != curLyricTag.u16LyricPos)
                    {
                        u16preLine2LyricPos = curLyricTag.u16LyricPos;
                        u8CharNum = _MApp_KTV_GetLyric( curLyricTag.u16LyricPos, au8LineSection);
                        //printf("\r\n ***2***u8CharNum = %d ", u8CharNum);
                        if(curLyricTag.u8BlushColor)
                        {
                            MApp_UiMenu_iSingDrawSubtitleChar(2, u16Duringtime);
                        }
                        else
                        {
                            MApp_UiMenu_iSingDisplaySubtitle(2);
                        }
                    }
                }
               if(st_mic_info.u32Duration >= u32LyricTotalTime)
                {
                    MApp_PlayedSong(0,  st_ktv_list);
                    MApp_KTV_Stop();
                    if(_eKTVMoviePlayMode != E_KTV_MOVIE_STOP)
                    {
                        _MApp_KTV_Stop_Movie();
                    }
                    enKTVLyricState = STATE_KTV_LYRIC_STOP;
                    _eKTVMoviePlayMode = E_KTV_MOVIE_STOP;
                    _eKTVMovieActionMode=E_KTV_MOVIE_ACTION_NUL;
                }
            }
            break;

        case STATE_KTV_LYRIC_PAUSE:
                st_mic_info.u32PlayStartTime = msAPI_Timer_GetTime0() - st_mic_info.u32Duration;
                bCheckTime = FALSE;
            break;
        case STATE_KTV_LYRIC_STOP:
            printf("\r\n STATE_KTV_LYRIC_STOP");
            MApp_UiMenu_iSingCloseSubtitle();
            enKTVLyricState = STATE_KTV_LYRIC_INIT;
            break;

        default:
            break;
    }
    switch(_eKTVMovieActionMode)
    {

        case E_KTV_MOVIE_ACTION_PLAY:
        {

            if(_eKTVMoviePlayMode == E_KTV_MOVIE_PAUSE)
            {
                MApp_VDPlayer_Resume();
                MApp_VDPlayer_Main();   // Necessary: Process Resume command
                //                    msAPI_Timer_Delayms(500);
                MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);
                MApp_VDPlayer_SetTrickMode(MODE_NORMAL_PLAY, PLAY_SPEEDx1);
            }
            #if 0
            else if(_eKTVMoviePlayMode >=E_KTV_MOVIE_FB_2X &&_eKTVMoviePlayMode <=E_KTV_MOVIE_FB_16X)
            {
                MApp_VDPlayer_SetTrickMode(MODE_FAST_BACKWARD, PLAY_SPEEDx1);
            }
            else if(_eKTVMoviePlayMode >=E_KTV_MOVIE_FF_2X &&_eKTVMoviePlayMode <=E_KTV_MOVIE_FF_16X)
            {
                MApp_VDPlayer_SetTrickMode(MODE_FAST_FORWARD, PLAY_SPEEDx1);
            }
            #endif
            else if(_eKTVMoviePlayMode ==E_KTV_MOVIE_STOP)
            {
                _MApp_KTV_PlayMovie();
            }
            _eKTVMoviePlayMode = E_KTV_MOVIE_NORMAL;
            _eKTVMovieActionMode=E_KTV_MOVIE_ACTION_NUL;
        }
        break;
        case E_KTV_MOVIE_ACTION_PAUSE:
        {
            _eKTVMoviePlayMode = E_KTV_MOVIE_PAUSE;
            _eKTVMovieActionMode=E_KTV_MOVIE_ACTION_NUL;
            MApp_VDPlayer_Pause();
        }
        break;
        case E_KTV_MOVIE_ACTION_STOP:
        {
            if(_eKTVMoviePlayMode != E_KTV_MOVIE_STOP)
            {
                _MApp_KTV_Stop_Movie();
            }
            _eKTVMoviePlayMode = E_KTV_MOVIE_STOP;
            _eKTVMovieActionMode=E_KTV_MOVIE_ACTION_NUL;

        }
        break;
        case E_KTV_MOVIE_ACTION_PREV:
            {

                _eKTVMovieActionMode=E_KTV_MOVIE_ACTION_NUL;
                _MApp_KTV_PlayMoviePrev();
                break;
            }

        #if 0
        case E_KTV_MOVIE_ACTION_FB:
            {

                if(_eKTVMoviePlayMode == E_KTV_MOVIE_NORMAL)
                {
                    _eKTVMoviePlayMode = E_KTV_MOVIE_FB_2X;
                    MApp_VDPlayer_SetTrickMode(MODE_FAST_BACKWARD, PLAY_SPEEDx2);
                }
                else if(_eKTVMoviePlayMode == E_KTV_MOVIE_FB_2X)
                {
                    _eKTVMoviePlayMode = E_KTV_MOVIE_FB_4X;
                    MApp_VDPlayer_SetTrickMode(MODE_FAST_BACKWARD, PLAY_SPEEDx4);
                }
                else if(_eKTVMoviePlayMode == E_KTV_MOVIE_FB_4X)
                {
                    _eKTVMoviePlayMode = E_KTV_MOVIE_FB_8X;
                    MApp_VDPlayer_SetTrickMode(MODE_FAST_BACKWARD, PLAY_SPEEDx8);
                }

                else if(_eKTVMoviePlayMode == E_KTV_MOVIE_FB_8X)
                {
                    _eKTVMoviePlayMode = E_KTV_MOVIE_FB_16X;
                    MApp_VDPlayer_SetTrickMode(MODE_FAST_BACKWARD, PLAY_SPEEDx16);
                }
                else if(_eKTVMoviePlayMode == E_KTV_MOVIE_FB_16X)
                {
                    _eKTVMoviePlayMode = E_KTV_MOVIE_NORMAL;
                    MApp_VDPlayer_SetTrickMode(MODE_FAST_BACKWARD, PLAY_SPEEDx1);
                }
                _eKTVMovieActionMode=E_KTV_MOVIE_ACTION_NUL;
                break;
            }

        case E_KTV_MOVIE_ACTION_FF:
            {
                if(_eKTVMoviePlayMode == E_KTV_MOVIE_NORMAL)
                {
                    _eKTVMoviePlayMode = E_KTV_MOVIE_FF_2X;
                    MApp_VDPlayer_SetTrickMode(MODE_FAST_FORWARD, PLAY_SPEEDx2);
                }
                else if(_eKTVMoviePlayMode == E_KTV_MOVIE_FF_2X)
                {
                    _eKTVMoviePlayMode = E_KTV_MOVIE_FF_4X;
                    MApp_VDPlayer_SetTrickMode(MODE_FAST_FORWARD, PLAY_SPEEDx4);
                }
                else if(_eKTVMoviePlayMode == E_KTV_MOVIE_FF_4X)
                {
                    _eKTVMoviePlayMode = E_KTV_MOVIE_FF_8X;
                    MApp_VDPlayer_SetTrickMode(MODE_FAST_FORWARD, PLAY_SPEEDx8);
                }

                else if(_eKTVMoviePlayMode == E_KTV_MOVIE_FF_8X)
                {
                    _eKTVMoviePlayMode = E_KTV_MOVIE_FF_16X;
                    MApp_VDPlayer_SetTrickMode(MODE_FAST_FORWARD, PLAY_SPEEDx16);
                }
                else if(_eKTVMoviePlayMode == E_KTV_MOVIE_FF_16X)
                {
                    _eKTVMoviePlayMode = E_KTV_MOVIE_NORMAL;
                    MApp_VDPlayer_SetTrickMode(MODE_FAST_FORWARD, PLAY_SPEEDx1);
                }
                _eKTVMovieActionMode=E_KTV_MOVIE_ACTION_NUL;
                break;
            }
#endif
        case E_KTV_MOVIE_ACTION_NEXT:
        {
            _MApp_KTV_PlayMovieNext();
            _eKTVMovieActionMode=E_KTV_MOVIE_ACTION_NUL;
            break;
        }
        default:
            break;

    }

    // Lyric display
    MApp_UiMenu_iSingDrawSubtitleMonitor();

}

/******************************************************************************/
/// It will exit KTV kernel, free all resources.
/// @return enumKTVRet
/******************************************************************************/
enumKTVRet MApp_KTV_ExitKTV(void)
{
    _u8TotalDriveNum = 0;
    eKTVLoadFileAttribute = (enumKTVLoadFileAttribute)0;
    //_MApp_KTV_Stop_Movie();
    enKTVLyricState = STATE_KTV_LYRIC_STOP;
    bContinuePlay = FALSE;
    MApp_KTV_Stop();
    MApp_UiMenu_iSingCloseSubtitle();
    msAPI_FS_Init(); //for switch source and USB abnormal
    MApp_KTV_DisconnectAllDevices();
    return E_KTV_RET_OK;
}

/******************************************************************************/
/// Read back the file information by song id from file buffer.
/// @param  u16SongIdx \b IN Specify the Song index.
/// @param  pInfo      \b OUT Return the file information.
/// @return enumKTVRet
/******************************************************************************/
enumKTVRet MApp_KTV_QueryMicFileInfo(U16 u16SongIdx, KTVFileInfo *pInfo)
{
    U8 u8String[40],i;
    U8 u8length_S=0;
    U16 *pu16String;
    U16 u16Tmp=u16SongIdx;

    for(i=0;i<40;i++)
        u8String[i]=0;

    for(i=0;i<255;i++)//get search filename length
    {
        u8length_S++;
        u16Tmp=u16Tmp/10;
        if(u16Tmp==0)
            break;
    }
    u8length_S+=4;//add .mic

    snprintf((char*)(&u8String[0]), u8length_S, "%d.mic", u16SongIdx);
    KTV_DBG(printf(" u8String=%s\n",u8String));
    _ASCII2Unicode(&u8String[0]);
    pu16String = (U16*)(&u8String[0]);
    return _MApp_KTV_QueryFileInfo(pu16String,pInfo);

}

/******************************************************************************/
/// Read back the file information by filenname(ASCII) from file buffer.
/// @param  pu8Buf \b IN Specify the filename(ASCII).
/// @param  pInfo      \b OUT Return the file information.
/// @return enumKTVRet
/******************************************************************************/
enumKTVRet MApp_KTV_QueryAsciiFileInfo(U8 *pu8Buf, KTVFileInfo *pInfo)
{
    U8 u8String[40],i;
    U16 *pu16String;

    for(i=0;i<40;i++)
    {
        if(*pu8Buf!=0)
            u8String[i]=*(pu8Buf++);
        else
            u8String[i]=0;
    }
    KTV_DBG(printf(" u8String=%s\n",u8String));

    _ASCII2Unicode(&u8String[0]);
    pu16String = (U16*)(&u8String[0]);
    return _MApp_KTV_QueryFileInfo(pu16String,pInfo);

}

BOOLEAN MApp_KTV_SetFileEntry(FileEntry *pEntry)
{
    _pKTVFileEntry = pEntry;
    return TRUE;
}

/******************************************************************************/
/// Read back the file data into DRAM.
/// @param  pu8Buf \b IN Specify the read buffer address.
/// @return file length
/******************************************************************************/
U32 MApp_KTV_FileRead(U32 pBuff)
{
    BOOLEAN bRet = FALSE;
    U32 u32FileLength = 0;
    U32 u32Temp = 0;

    if ((_u8FileHandleId = msAPI_FCtrl_FileOpen(_pKTVFileEntry, OPEN_MODE_FOR_READ)) == FCTRL_INVALID_FILE_HANDLE)
    {
        KTV_DBG(printf("KTV file open failed\n"));
        return 0;
    }

    //KTV_DBG(printf("KTV file handle 0x%bx\n", _u8FileHandleId));
    u32FileLength = msAPI_FCtrl_FileLength(_u8FileHandleId);
    msAPI_FCtrl_FileSeek(_u8FileHandleId,0,FILE_SEEK_SET);

    //KTV_DBG(printf("msAPI_FCtrl_FileLength 0x%lx\n", u32FileLength));
    //KTV_DBG(printf("Read buffer address 0x%lx\n", pBuff));
    //if (u32FileLength < 0x100)
    //{
    //    KTV_DBG(printf("overflow length 0x%lx\n", u32FileLength));
    //    return FALSE;
    //}

    u32Temp = msAPI_FCtrl_FileRead(_u8FileHandleId, pBuff, u32FileLength);
    if (u32Temp == 0)
    {
        bRet = TRUE;
    }
    else
    {
        KTV_DBG(printf("Read fail, return 0x%lx.\n",u32Temp));
    }

    if (msAPI_FCtrl_FileClose(_u8FileHandleId))
    {
        _u8FileHandleId = FCTRL_INVALID_FILE_HANDLE;
        bRet = TRUE;
    }
    else
    {
        KTV_DBG(printf("Close file fail %bx.\n",_u8FileHandleId ));
    }

    if(bRet)
        return u32FileLength;
    else
        return 0;
}

/******************************************************************************/
/// Capture the current video and save it as a JPEG file.
/// @param  pFileName \b IN Specify the file name.
/// @param  u8pTmpBuffAddr \b IN Specify the tmp buffer addr.
/// @param  u8pTmpBuffAddr \b IN Specify the tmp buffer size.
/// @return enumMPlayerRet
/******************************************************************************/
BOOLEAN MApp_KTV_FileWrite(U32 pBuff, U32 BuffLen)
{
    BOOLEAN bRet = FALSE;

    if ((_u8FileHandleId = msAPI_FCtrl_FileOpen(_pKTVFileEntry, OPEN_MODE_BINARY_FOR_READ_WRITE)) == FCTRL_INVALID_FILE_HANDLE)
    {
        KTV_DBG(printf("KTV file open failed\n"));
        return bRet;
    }

    msAPI_FCtrl_FileWrite(_u8FileHandleId, pBuff, BuffLen);

    if (msAPI_FCtrl_FileClose(_u8FileHandleId))
    {
        _u8FileHandleId = FCTRL_INVALID_FILE_HANDLE;
        bRet = TRUE;
    }
    else
    {
        KTV_DBG(printf("Close file fail %bx.\n",_u8FileHandleId ));
    }

    return bRet;
}

void MApp_KTV_SetPlayListModifyFlag(void)
{
    _eKTVKnlFlags |= E_KTV_KNL_FLG_PLAYLIST_MODIFIED;
    _u32SongListCheckTimer = msAPI_Timer_GetTime0();
}

/******************************************************************************/
static U8 MApp_KTV_MailBoxHandler(void)
{
    U8 u8Idx;
    MBX_Msg mbxMsg;
    MBX_MSGQ_Status mbxMsgQStatus;
    U32 u32tmpvar = 0;

    MSApi_MBX_GetMsgQueueStatus(MB_CLASS_KTV, &mbxMsgQStatus);
    for (u8Idx = 0; u8Idx < mbxMsgQStatus.u32NormalMsgCount; u8Idx++)
    {
        if(MSApi_MBX_RecvMsg(E_MBX_CLASS_KTV,  &mbxMsg, 0, MBX_CHECK_NORMAL_MSG) == E_MBX_SUCCESS)
        {
            switch(mbxMsg.u8Index)
            {
                case MB_KTV_CMD_COPROCESSER_READY:
                    KTV_DBG(printf("MB_KTV_CMD_COPROCESSER_READY\n"););
                    break;
                case MB_KTV_CMD_CLIENT_IP:
                    u32tmpvar= (((mbxMsg.u8Parameters[0]) << 24)&0xFF000000)|
                        (((mbxMsg.u8Parameters[1]) << 16)&0x00FF0000)|
                        (((mbxMsg.u8Parameters[2]) << 8 )&0x0000FF00)|
                        (((mbxMsg.u8Parameters[3])      )&0x000000FF);
                    _u32NetIPAddress = u32tmpvar;
                    KTV_DBG(printf("Client IP=%d.%d.%d.%d\n",mbxMsg.u8Parameters[3], mbxMsg.u8Parameters[2], mbxMsg.u8Parameters[1], mbxMsg.u8Parameters[0]););
                    break;
                case MB_KTV_CMD_HOST_IP:
                    u32tmpvar= (((mbxMsg.u8Parameters[0]) << 24)&0xFF000000)|
                        (((mbxMsg.u8Parameters[1]) << 16)&0x00FF0000)|
                        (((mbxMsg.u8Parameters[2]) << 8 )&0x0000FF00)|
                        (((mbxMsg.u8Parameters[3])      )&0x000000FF);
                    KTV_DBG(printf("Host IP=%d.%d.%d.%d\n", mbxMsg.u8Parameters[3], mbxMsg.u8Parameters[2], mbxMsg.u8Parameters[1], mbxMsg.u8Parameters[0]););
                    break;
                case MB_KTV_CMD_SET_INFO:
                    u32tmpvar= (((mbxMsg.u8Parameters[0]) << 24)&0xFF000000)|
                        (((mbxMsg.u8Parameters[1]) << 16)&0x00FF0000)|
                        (((mbxMsg.u8Parameters[2]) << 8 )&0x0000FF00)|
                        (((mbxMsg.u8Parameters[3])      )&0x000000FF);
                    _u32NetInfoLen=u32tmpvar;
                    KTV_DBG(printf("FileLen=%x\n",u32tmpvar););
                    break;
                case MB_KTV_CMD_LRC_SIZE:
                    u32tmpvar= (((mbxMsg.u8Parameters[0]) << 24)&0xFF000000)|
                        (((mbxMsg.u8Parameters[1]) << 16)&0x00FF0000)|
                        (((mbxMsg.u8Parameters[2]) << 8 )&0x0000FF00)|
                        (((mbxMsg.u8Parameters[3])      )&0x000000FF);
                    u32LyricFileLen=u32tmpvar;
                    bUpdateLRCFileReady = TRUE;
                    KTV_DBG(printf("LRC FileLen=%x\n",u32tmpvar););
                    break;
                case MB_KTV_CMD_SERVER_ERROR:
                    KTV_DBG(printf("KTV server error\n"););
                    //show error window
                    bServerError = TRUE;
                    break;
            }
        }
    }
    return mbxMsg.u8Index;
}

BOOLEAN MApp_KTV_CheckCoProcesserReady(void)
{
    BOOLEAN bRet = FALSE;

    KTV_DBG(printf("MApp_KTV_CheckCoProcesserReady  --> \n"););
    U32 u32DrmTimout = 0;

    //==> Send mail.
    _MApp_KTV_SendMailboxMsg(E_MBX_CLASS_KTV
    /*Index*/           ,MB_KTV_CMD_CHECK_COPROCESSER_READY
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    // Waiting for Aeon Video Player Ack
    u32DrmTimout = msAPI_Timer_GetTime0();
    do
    {
        #if( WATCH_DOG == ENABLE )
        msAPI_Timer_ResetWDT();
        #endif
        if(MApp_KTV_MailBoxHandler())
        {
            bRet = TRUE;
            break;
        }
    }
    while(msAPI_Timer_DiffTimeFromNow(u32DrmTimout)<50);

    return bRet;
}

void MApp_KTV_RestIP(void)
{
    KTV_DBG(printf("MApp_KTV_RestIP\n"););
    U32 u32DrmTimout = 0;

    //==> Send mail.
    _MApp_KTV_SendMailboxMsg(E_MBX_CLASS_KTV
    /*Index*/           ,MB_KTV_CMD_RESET_IP
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    // Waiting for Aeon Video Player Ack
    u32DrmTimout = msAPI_Timer_GetTime0();
    do
    {
        #if( WATCH_DOG == ENABLE )
        msAPI_Timer_ResetWDT();
        #endif
        if(MApp_KTV_MailBoxHandler())
            break;
    }
    while(msAPI_Timer_DiffTimeFromNow(u32DrmTimout)<200);
}

void MApp_KTV_GetInfo(unsigned char *command,U32 id,U32 buf)
{
    KTV_DBG(printf("MApp_KTV_GetInfo\n"););
    U32 u32DrmTimout = 0;
    U8 i ;

    if(_u32NetInfoLen!=0)
        return;

    if(id==0)
    {
        //==> Send mail.
        _MApp_KTV_SendMailboxMsg(E_MBX_CLASS_KTV
        /*Index*/           ,MB_KTV_CMD_SET_CMD
        /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
        /*ParameterCount*/  ,8
        /*p1*/              ,*command++
        /*p2*/              ,*command++
        /*p3*/              ,*command++
        /*p4*/              ,*command++
        /*p5*/              ,*command++
        /*p6*/              ,*command++
        /*p7*/              ,*command++
        /*p8*/              ,*command++
        /*p9*/              ,0
        /*p10*/             ,0);
    }

    //==> Send mail.
    _MApp_KTV_SendMailboxMsg(E_MBX_CLASS_KTV
    /*Index*/           ,MB_KTV_CMD_GET_INFO
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,8
    /*p1*/              ,(U8)(id>>24)
    /*p2*/              ,(U8)(id>>16)
    /*p3*/              ,(U8)(id>>8)
    /*p4*/              ,(U8)(id)
    /*p5*/              ,(U8)(buf>>24)
    /*p6*/              ,(U8)(buf>>16)
    /*p7*/              ,(U8)(buf>>8)
    /*p8*/              ,(U8)(buf)
    /*p9*/              ,0
    /*p10*/             ,0);

    // Waiting for Aeon Video Player Ack
    u32DrmTimout = msAPI_Timer_GetTime0();
    do
    {
        #if( WATCH_DOG == ENABLE )
        msAPI_Timer_ResetWDT();
        #endif
        if(MApp_KTV_MailBoxHandler())
            break;
    }
    while(msAPI_Timer_DiffTimeFromNow(u32DrmTimout)<1000);
}

void MApp_KTV_SetSoundFontMemoryAddr(U32 u32MemAddr, U32 u32MemSize)
{
    KTV_DBG(printf("MApp_KTV_SetSoundFontMemoryAddr\n"););

   if(!(eKTVLoadFileAttribute & E_KTV_SOUNDFONTADDRESS_SEND))
    {
        //==> Send mail.
        _MApp_KTV_SendMailboxMsg(E_MBX_CLASS_KTV
        /*Index*/           ,MB_KTV_CMD_SET_SOUND_FONT_MEM_ADDR
        /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
        /*ParameterCount*/  ,8
        /*p1*/              ,(U8)(u32MemAddr>>24)
        /*p2*/              ,(U8)(u32MemAddr>>16)
        /*p3*/              ,(U8)(u32MemAddr>>8)
        /*p4*/              ,(U8)(u32MemAddr)
        /*p5*/              ,(U8)(u32MemSize>>24)
        /*p6*/              ,(U8)(u32MemSize>>16)
        /*p7*/              ,(U8)(u32MemSize>>8)
        /*p8*/              ,(U8)(u32MemSize)
        /*p9*/              ,0
        /*p10*/             ,0);
        eKTVLoadFileAttribute |= E_KTV_SOUNDFONTADDRESS_SEND;
    }
}

void MApp_KTV_SetSoundMicMemoryAddr(U32 u32MemAddr, U32 u32MemSize)
{
    KTV_DBG(printf("MApp_KTV_SetSoundMicMemoryAddr\n"););

    //==> Send mail.
    _MApp_KTV_SendMailboxMsg(E_MBX_CLASS_KTV
    /*Index*/           ,MB_KTV_CMD_SET_SOUND_MIC_MEM_ADDR
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,8
    /*p1*/              ,(U8)(u32MemAddr>>24)
    /*p2*/              ,(U8)(u32MemAddr>>16)
    /*p3*/              ,(U8)(u32MemAddr>>8)
    /*p4*/              ,(U8)(u32MemAddr)
    /*p5*/              ,(U8)(u32MemSize>>24)
    /*p6*/              ,(U8)(u32MemSize>>16)
    /*p7*/              ,(U8)(u32MemSize>>8)
    /*p8*/              ,(U8)(u32MemSize)
    /*p9*/              ,0
    /*p10*/             ,0);

     eKTVLoadFileAttribute |= E_KTV_MICADDRESS_SEND;
}

void MApp_KTV_Set_LRC_MemoryAddr(U32 u32MemAddr, U32 u32MemSize)
{
    KTV_DBG(printf("MApp_KTV_Set_LRC_MemoryAddr\n"););

    //==> Send mail.
    _MApp_KTV_SendMailboxMsg(E_MBX_CLASS_KTV
    /*Index*/           ,MB_KTV_CMD_SET_SOUND_LRC_MEM_ADDR
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,8
    /*p1*/              ,(U8)(u32MemAddr>>24)
    /*p2*/              ,(U8)(u32MemAddr>>16)
    /*p3*/              ,(U8)(u32MemAddr>>8)
    /*p4*/              ,(U8)(u32MemAddr)
    /*p5*/              ,(U8)(u32MemSize>>24)
    /*p6*/              ,(U8)(u32MemSize>>16)
    /*p7*/              ,(U8)(u32MemSize>>8)
    /*p8*/              ,(U8)(u32MemSize)
    /*p9*/              ,0
    /*p10*/             ,0);

    eKTVLoadFileAttribute |= E_KTV_LRCADDRESS_SEND;
}

void MApp_KTV_Set_INI_MemoryAddr(U32 u32MemAddr)
{
    KTV_DBG(printf("MApp_KTV_Set_INI_MemoryAddr\n"););

    //==> Send mail.
    _MApp_KTV_SendMailboxMsg(E_MBX_CLASS_KTV
    /*Index*/           ,MB_KTV_CMD_SET_INI_MEM_ADDR
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,10
    /*p1*/              ,(U8)(u32MemAddr>>24)
    /*p2*/              ,(U8)(u32MemAddr>>16)
    /*p3*/              ,(U8)(u32MemAddr>>8)
    /*p4*/              ,(U8)(u32MemAddr)
    /*p5*/              ,(U8)(_sKtvIni.u8MicURLLength)
    /*p6*/              ,(U8)(_sKtvIni.u8DBURLLength)
    /*p7*/              ,(U8)(_sKtvIni.u8UpdateURLLength)
    /*p8*/              ,(U8)(_sKtvIni.u8URL1Length)
    /*p9*/              ,(U8)(_sKtvIni.u8URL2Length)
    /*p10*/             ,(U8)(_sKtvIni.u8URL3Length));

    eKTVLoadFileAttribute |= E_KTV_INIADDRESS_SEND;
}

void MApp_KTV_SendMailBoxCmd(MB_KTV_CMD u8KTVCmd, U32 u32Parameter)
{
    KTV_DBG(printf("MApp_KTV_SendMailBox: [%x] \n", u8KTVCmd););

    //==> Send mail.
    _MApp_KTV_SendMailboxMsg(E_MBX_CLASS_KTV
    /*Index*/           ,u8KTVCmd
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,4
    /*p1*/              ,(U8)(u32Parameter>>24)
    /*p2*/              ,(U8)(u32Parameter>>16)
    /*p3*/              ,(U8)(u32Parameter>>8)
    /*p4*/              ,(U8)(u32Parameter)
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
}

void MApp_KTV_Play(void)
{
    //==> Send mail.
    _MApp_KTV_SendMailboxMsg(E_MBX_CLASS_KTV
    /*Index*/           ,MB_KTV_CMD_PLAY
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
}

void MApp_KTV_Pause(void)
{
    //==> Send mail.
    _MApp_KTV_SendMailboxMsg(E_MBX_CLASS_KTV
    /*Index*/           ,MB_KTV_CMD_PAUSE
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
}

void MApp_KTV_Stop(void)
{
    MApp_KTV_RecordStop();

    //==> Send mail.
    _MApp_KTV_SendMailboxMsg(E_MBX_CLASS_KTV
    /*Index*/           ,MB_KTV_CMD_STOP
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);
}
#if ENABLE_AUDIO_ENCODE
void MApp_KTV_RecordStart(void)
{
    U8 u8Playlist[] = REC_SONG_FILENAME;

    if (!bEncoding)
    {
        // Open file for encoding audio
        u8AudIntCount = 0;
        gu8MADEncodeDone = 0;

        memset((U8*)pRecInfo, 0, sizeof(KTVRecodInfo));
        memset((U8*)u32RecBuff, 0, REC_BUFF_SIZE);
        pRecInfo->u32BuffStart = (U32)u32RecBuff;
        pRecInfo->u32BuffSize = REC_BUFF_SIZE;
        pRecInfo->u32BuffEnd = pRecInfo->u32BuffStart + pRecInfo->u32BuffSize;
        pRecInfo->u32BuffRdPtr = pRecInfo->u32BuffStart;
        pRecInfo->u32BuffWrPtr = pRecInfo->u32BuffStart;
        pRecInfo->bBuffRewind = FALSE;
        pRecInfo->u32BuffFreeSize = REC_BUFF_SIZE;
        pRecInfo->u8RecFilehandle = FCTRL_INVALID_FILE_HANDLE;
        u32AudOutputSize = 0;
        u32AudFileWriteSize = 0;

        if (_MApp_KTV_QueryRecSongFileInfo(&u8Playlist[0],&pRecInfo->curRecFileInfo) == E_KTV_RET_OK)
        {

            if ((pRecInfo->u8RecFilehandle =
                 msAPI_FCtrl_FileOpen(&pRecInfo->curRecFileInfo.fileEntry, OPEN_MODE_BINARY_EMPTY_FOR_WRITE)) == FCTRL_INVALID_FILE_HANDLE)
            {
                KTV_DBG(printf("KTV open Record file failed\n"));
                return;
            }

            KTV_DBG(printf("KTV open record file Done\n"));

            //Start Audio encoding
            MApi_AUDIO_SetCommand(MSAPI_AUD_DVB2_DECCMD_STOP);    //MDrv_MAD2_SetDecCmd(0);

            msAPI_Timer_Delayms(100);
            MApi_AUDIO_SetCommand(MSAPI_AUD_DVB2_DECCMD_PLAY);//MDrv_MAD2_SetDecCmd(1);

            bEncoding = TRUE;
        }
    }
}

void MApp_KTV_RecordStop(void)
{
    U32 u32AudWrPtr;
    U32 u32AudWrSize;
    if (bEncoding)
    {
        //Get last audio output
        if (gu8MADEncodeDone)
        {
            //Get Audio output compressed data info
            if (_MApp_KTV_CheckOutputRequest(&u32AudWrPtr, &u32AudWrSize))
            {
                //Copy Audio compressed data to buffer
                if (!_MApp_KTV_GetAudCompressData(u32AudWrPtr, u32AudWrSize))
                {
                    KTV_DBG(printf("Get Audio data fail\n"));
                }
            }
            _MApp_KTV_SetAudIntAck();
            gu8MADEncodeDone = FALSE;
        }

        //Stop Audio encoding
        MApi_AUDIO_SetCommand(MSAPI_AUD_DVB2_DECCMD_STOP); //MDrv_MAD2_SetDecCmd(0);

        //Flush all audio data to USB
        if (!_MApp_KTV_WriteAudCompressdata(TRUE))
        {
            KTV_DBG(printf("Write Audio data fail\n"));
        }

        if (pRecInfo->u8RecFilehandle != FCTRL_INVALID_FILE_HANDLE)
        {
            if (msAPI_FCtrl_FileClose(pRecInfo->u8RecFilehandle))
            {
                KTV_DBG(printf("KTV close record file Done\n"));
                pRecInfo->u8RecFilehandle = FCTRL_INVALID_FILE_HANDLE;
            }
            else
            {
                KTV_DBG(printf("KTV close record file failed\n"));
            }
        }
        KTV_DBG(printf("Total Audio output: 0x%x\n", u32AudOutputSize));
        KTV_DBG(printf("Total Audio File Write: 0x%x\n", u32AudFileWriteSize));

        bEncoding = FALSE;
    }
}
#endif

void MApp_KTV_OpenMicFileFromUsb(void)
{
    KTV_DBG(printf("MApp_KTV_OpenMicFileFromUsb\n"););

    //==> Send mail.
    _MApp_KTV_SendMailboxMsg(E_MBX_CLASS_KTV
    /*Index*/           ,MB_KTV_CMD_OPEN_MIC_FILE_FROM_USB
    /*MsgType*/         ,E_MBX_MSG_TYPE_NORMAL
    /*ParameterCount*/  ,0
    /*p1*/              ,0
    /*p2*/              ,0
    /*p3*/              ,0
    /*p4*/              ,0
    /*p5*/              ,0
    /*p6*/              ,0
    /*p7*/              ,0
    /*p8*/              ,0
    /*p9*/              ,0
    /*p10*/             ,0);

    bUpdateLRCFileReady = FALSE;
}

void MApp_KTV_DownloadMicFile(U32 u32MicId)
{
    KTV_DBG(printf("MApp_KTV_DownloadMicFile\n"););

    MApp_KTV_GetInfo((unsigned char *)0,u32MicId,KTV_MIDI_BUFFER_ADR);
    eKTVLoadFileAttribute |= E_KTV_MICADDRESS_SEND;
    bUpdateLRCFileReady = FALSE;

}

U32 MApp_KTV_LoadSoundFontFile(void)
{
    U32 u32FileSize = 0;

    enumKTVRet eRet=E_KTV_RET_FAIL;
    KTVFileInfo FileInfo;
    U8 u8SoundFontName[]=SOUND_FONT_FILENAME;

    eRet = MApp_KTV_QueryAsciiFileInfo(&u8SoundFontName[0],&FileInfo);
    if(eRet == E_KTV_RET_FAIL)
        return 0;

    MApp_KTV_SetFileEntry(&(FileInfo.fileEntry));

    u32FileSize = MApp_KTV_FileRead(KTV_SOUND_FONT_BUFFER_ADR);

    if(u32FileSize > KTV_SOUND_FONT_BUFFER_LEN)
    {
        KTV_DBG( printf("Fail: File size[%ld]  Buffer Size[%ld]\n", u32FileSize, KTV_SOUND_FONT_BUFFER_LEN) );
        return 0;
    }

    KTV_DBG(printf("Addr [0x%lx]  DAT File size[%ld]\n", KTV_SOUND_FONT_BUFFER_ADR, u32FileSize));

    eKTVLoadFileAttribute |= E_KTV_SOUNDFONT_LOADED;
    return u32FileSize;
}


static void MApp_KTV_CheckCoProcesserReady_Task(void)
{
    if(++_u32NetErrorCounter<10000)
        return;
    _u32NetErrorCounter = 0;

    if(bKTVCoProcesserReady == FALSE)
    {
        if(MApp_KTV_CheckCoProcesserReady())
        {
            MAPP_KTV_Init2();
            bKTVCoProcesserReady =TRUE;
        }
    }
}

static void MApp_KTV_AutoUpdate(void)
{
    if(++_u32NetUpdateCounter<20000)
        return;
    _u32NetUpdateCounter = 0;

    switch(_u8NetWorkState)
    {
        case E_NONE:
            break;
        case E_CHECK_COPROCESSER_READY:
            if(bKTVCoProcesserReady)
            {
                _u8NetWorkState = E_NONE;// Normally disable auto upgrade function,enable =E_GET_IP
                _u32NetErrorCounter = 0;
            }
            break;
        case E_GET_IP:
            if(++_u32NetErrorCounter>100)
            {
                KTV_DBG(printf("E_GET_IP\n"););
                _u32NetErrorCounter = 0;
                _u32NetIPAddress = 0;
                MApp_KTV_RestIP();
                _u8NetWorkState = E_CHECK_IP;
            }
            break;
        case E_CHECK_IP:
            KTV_DBG(printf("E_CHECK_IP\n"););
            if(_u32NetIPAddress)
            {
                _u32NetInfoLen = 0;
                _u8NetWorkState = E_GET_VERSION;
            }
            else
                _u8NetWorkState = E_GET_IP;
            break;
        case E_GET_VERSION:
            KTV_DBG(printf("E_GET_VERSION\n"););
            if(_u32NetInfoLen==0)
            {
                unsigned char temp[8];
                temp[0]=0xff;
                temp[1]=(unsigned char)_u32MusicVersion1;
                temp[2]=(unsigned char)(_u32MusicVersion1>>8);
                temp[3]=(unsigned char)(_u32MusicVersion1>>16);
                temp[4]=1;
                temp[5]=0;

                memset((char *)((DOWNLOAD_BUFFER_MEMORY_TYPE & MIU1) ? (DOWNLOAD_BUFFER_ADR | MIU_INTERVAL) : (DOWNLOAD_BUFFER_ADR)),0,32);
                MApp_KTV_GetInfo(temp,0,((DOWNLOAD_BUFFER_MEMORY_TYPE & MIU1) ? (DOWNLOAD_BUFFER_ADR | MIU_INTERVAL) : (DOWNLOAD_BUFFER_ADR)));
                _u8NetWorkState = E_CHECK_VERSION;
                 _u32NetErrorCounter = 0;
            }
            break;
        case E_CHECK_VERSION:
            KTV_DBG(printf("E_CHECK_VERSION\n"););
            if(_u32NetInfoLen)
            {
                _u32NetVersion=*(U32 *)((DOWNLOAD_BUFFER_MEMORY_TYPE & MIU1) ? (DOWNLOAD_BUFFER_ADR | MIU_INTERVAL) : (DOWNLOAD_BUFFER_ADR));
                 KTV_DBG(printf("_u32NetVersion=%x\n",_u32NetVersion););
                _u8NetWorkState = E_GET_SINGERLIST;
            }
            else
            {
                if(++_u32NetErrorCounter>200)
                {
                    _u32NetErrorCounter = 0;
                    _u8NetWorkState = E_GET_VERSION;
                }
            }
            break;
        case E_GET_SINGERLIST:
            KTV_DBG(printf("E_GET_SINGERLIST\n"););
            KTV_DBG(printf("_u32SingerVersion0=%x\n",_u32SingerVersion0););
            if(_u32NetVersion>_u32SingerVersion0)
            {
                unsigned char temp[8];
                temp[0]=0xff;
                temp[1]=(unsigned char)_u32MusicVersion1;
                temp[2]=(unsigned char)(_u32MusicVersion1>>8);
                temp[3]=(unsigned char)(_u32MusicVersion1>>16);
                temp[4]=3;
                temp[5]=0;

                _u32NetInfoLen = 0;
                MApp_KTV_GetInfo(temp,0,((DOWNLOAD_BUFFER_MEMORY_TYPE & MIU1) ? (DOWNLOAD_BUFFER_ADR | MIU_INTERVAL) : (DOWNLOAD_BUFFER_ADR)));
                _u8NetWorkState = E_CHECK_SINGERLIST;
                 _u32NetErrorCounter = 0;
            }
            else
            {
                KTV_DBG(printf("Not need update\n"););
                _u32NetInfoLen = 0;
                _u8NetWorkState = E_GET_SW_VERSION;
            }
            break;
        case E_CHECK_SINGERLIST:
            KTV_DBG(printf("E_CHECK_SINGERLIST\n"););
            KTV_DBG(printf("Get_u32NetInfoLen=%x\n",*(U32 *)(((DOWNLOAD_BUFFER_MEMORY_TYPE & MIU1) ? (DOWNLOAD_BUFFER_ADR | MIU_INTERVAL) : (DOWNLOAD_BUFFER_ADR))+4)););
            if((_u32NetInfoLen-16)==*(U32 *)(((DOWNLOAD_BUFFER_MEMORY_TYPE & MIU1) ? (DOWNLOAD_BUFFER_ADR | MIU_INTERVAL) : (DOWNLOAD_BUFFER_ADR))+4))
            {
                KTVFileInfo FileInfo;
                U8 u8HandleNo;
                U8 u8FileName[80]=SINGER_BIN_FILENAME;
                U16 au16FileName[40];

                ASCIItoUnicode2((S8*)u8FileName,strlen((char *)u8FileName));
                memset(au16FileName,0,sizeof(au16FileName));
                memcpy(au16FileName,u8FileName,sizeof(au16FileName));

                if(E_KTV_RET_FAIL!=_MApp_KTV_QueryFileInfo(au16FileName,&FileInfo))
                {
                    msAPI_FCtrl_FileDelete(&(FileInfo.fileEntry));
                    KTV_DBG(printf("msAPI_FCtrl_FileDelete\n"));
                }
                u8HandleNo = MApp_FileBrowser_OpenNewFileForWrite(au16FileName,UnicodeLen((S8*)au16FileName));
                if (u8HandleNo ==  INVALID_FILE_HANDLE)
                {
                    KTV_DBG(printf("crate file failed\n"));
                }
                msAPI_FCtrl_FileWrite(u8HandleNo, ((DOWNLOAD_BUFFER_MEMORY_TYPE & MIU1) ? (DOWNLOAD_BUFFER_ADR | MIU_INTERVAL) : (DOWNLOAD_BUFFER_ADR)), _u32NetInfoLen);
                msAPI_FCtrl_FileClose(u8HandleNo);
                KTV_DBG(printf("Write singerlist.bin finished\n"));
                _u8NetWorkState = E_GET_MUSICLIST;
            }
            else
            {
                if(++_u32NetErrorCounter>200)
                {
                    _u32NetErrorCounter = 0;
                    _u8NetWorkState = E_GET_SINGERLIST;
                }
            }
            break;
        case E_GET_MUSICLIST:
            KTV_DBG(printf("E_GET_MUSICLIST\n"););
            KTV_DBG(printf("_u32MusicVersion0=%x\n",_u32MusicVersion0););
            if(_u32NetVersion>_u32MusicVersion0)
            {
                unsigned char temp[8];
                temp[0]=0xff;
                temp[1]=(unsigned char)_u32MusicVersion1;
                temp[2]=(unsigned char)(_u32MusicVersion1>>8);
                temp[3]=(unsigned char)(_u32MusicVersion1>>16);
                temp[4]=2;
                temp[5]=0;

                _u32NetInfoLen = 0;
                MApp_KTV_GetInfo(temp,0,((DOWNLOAD_BUFFER_MEMORY_TYPE & MIU1) ? (DOWNLOAD_BUFFER_ADR | MIU_INTERVAL) : (DOWNLOAD_BUFFER_ADR)));
                _u8NetWorkState = E_CHECK_MUSICLIST;
                 _u32NetErrorCounter = 0;
            }
            else
            {
                KTV_DBG(printf("Not need update\n"););
                _u32NetInfoLen = 0;
                _u8NetWorkState = E_GET_SW_VERSION;
            }
            break;
        case E_CHECK_MUSICLIST:
            KTV_DBG(printf("E_CHECK_MUSICLIST\n"););
            KTV_DBG(printf("Get_u32NetInfoLen=%x\n",*(U32 *)(((DOWNLOAD_BUFFER_MEMORY_TYPE & MIU1) ? (DOWNLOAD_BUFFER_ADR | MIU_INTERVAL) : (DOWNLOAD_BUFFER_ADR))+4)););
            if((_u32NetInfoLen-16)==*(U32 *)(((DOWNLOAD_BUFFER_MEMORY_TYPE & MIU1) ? (DOWNLOAD_BUFFER_ADR | MIU_INTERVAL) : (DOWNLOAD_BUFFER_ADR))+4))
            {
                KTVFileInfo FileInfo;
                U8 u8HandleNo;
                U8 u8FileName[80]=SONG_BIN_FILENAME;
                U16 au16FileName[40];

                ASCIItoUnicode2((S8*)u8FileName,strlen((char *)u8FileName));
                memset(au16FileName,0,sizeof(au16FileName));
                memcpy(au16FileName,u8FileName,sizeof(au16FileName));

                if(E_KTV_RET_FAIL!=_MApp_KTV_QueryFileInfo(au16FileName,&FileInfo))
                {
                    msAPI_FCtrl_FileDelete(&(FileInfo.fileEntry));
                    KTV_DBG(printf("msAPI_FCtrl_FileDelete\n"));
                }
                u8HandleNo = MApp_FileBrowser_OpenNewFileForWrite(au16FileName,UnicodeLen((S8*)au16FileName));
                if (u8HandleNo ==  INVALID_FILE_HANDLE)
                {
                    KTV_DBG(printf("crate file failed\n"));
                }
                msAPI_FCtrl_FileWrite(u8HandleNo, ((DOWNLOAD_BUFFER_MEMORY_TYPE & MIU1) ? (DOWNLOAD_BUFFER_ADR | MIU_INTERVAL) : (DOWNLOAD_BUFFER_ADR)), _u32NetInfoLen);
                msAPI_FCtrl_FileClose(u8HandleNo);
                KTV_DBG(printf("Write musiclist.bin finished\n"));

                _u32NetInfoLen = 0;
                _u8NetWorkState = E_GET_SW_VERSION;
            }
            else
            {
                if(++_u32NetErrorCounter>200)
                {
                    _u32NetErrorCounter = 0;
                    _u8NetWorkState = E_GET_MUSICLIST;
                }
            }
            break;
///////////////////////////////////////////////////////////////////////
        case E_GET_SW_VERSION:
            KTV_DBG(printf("E_GET_SW_VERSION\n"););
            if(_u32NetInfoLen==0)
            {
                unsigned char temp[8];
                temp[0]=0xff;
                temp[1]=(unsigned char)_u32MergeVersion1;
                temp[2]=(unsigned char)(_u32MergeVersion1>>8);
                temp[3]=(unsigned char)(_u32MergeVersion1>>16);
                temp[4]=1;
                temp[5]=0;

                memset((char *)((DOWNLOAD_BUFFER_MEMORY_TYPE & MIU1) ? (DOWNLOAD_BUFFER_ADR | MIU_INTERVAL) : (DOWNLOAD_BUFFER_ADR)),0,32);
                MApp_KTV_GetInfo(temp,0,((DOWNLOAD_BUFFER_MEMORY_TYPE & MIU1) ? (DOWNLOAD_BUFFER_ADR | MIU_INTERVAL) : (DOWNLOAD_BUFFER_ADR)));
                _u8NetWorkState = E_CHECK_SW_VERSION;
                 _u32NetErrorCounter = 0;
            }
            break;
        case E_CHECK_SW_VERSION:
            KTV_DBG(printf("E_CHECK_SW_VERSION\n"););
            if(_u32NetInfoLen)
            {
                _u32NetSWVersion=*(U32 *)((DOWNLOAD_BUFFER_MEMORY_TYPE & MIU1) ? (DOWNLOAD_BUFFER_ADR | MIU_INTERVAL) : (DOWNLOAD_BUFFER_ADR));
                 KTV_DBG(printf("_u32NetSWVersion=%x\n",_u32NetSWVersion););
                _u8NetWorkState = E_GET_MERGE_BIN;
            }
            else
            {
                if(++_u32NetErrorCounter>200)
                {
                    _u32NetErrorCounter = 0;
                    _u8NetWorkState = E_GET_SW_VERSION;
                }
            }
            break;
        case E_GET_MERGE_BIN:
            KTV_DBG(printf("E_GET_MERGE_BIN\n"););
            KTV_DBG(printf("_u32SWVersion0=%x\n",_u32MergeVersion0););
            if(_u32NetSWVersion>_u32MergeVersion0)
            {
                unsigned char temp[8];
                temp[0]=0xfe;
                temp[1]=(unsigned char)_u32MergeVersion1;
                temp[2]=(unsigned char)(_u32MergeVersion1>>8);
                temp[3]=(unsigned char)(_u32MergeVersion1>>16);
                temp[4]=4;
                temp[5]=0;

                _u32NetInfoLen = 0;
                MApp_KTV_GetInfo(temp,0,((DOWNLOAD_BUFFER_MEMORY_TYPE & MIU1) ? (DOWNLOAD_BUFFER_ADR | MIU_INTERVAL) : (DOWNLOAD_BUFFER_ADR)));
                _u8NetWorkState = E_CHECK_MERGE_BIN;
                 _u32NetErrorCounter = 0;
            }
            else
            {
                KTV_DBG(printf("Not SW need update\n"););
                _u8NetWorkState = E_NONE;
            }
            break;
        case E_CHECK_MERGE_BIN:
            KTV_DBG(printf("E_CHECK_MERGE_BIN\n"););
            KTV_DBG(printf("Get_u32NetInfoLen=%x\n",_u32NetInfoLen););
            {
                if (_u32NetInfoLen)
                {
                    KTVFileInfo FileInfo;
                    U8 u8HandleNo;
                    U8 u8FileName[80]=SW_MERGE_FILENAME;
                    U8 u8FileName2[80]=SW_MERGE_FILENAME2;
                    U16 au16FileName[40];

                   ASCIItoUnicode2((S8*)u8FileName2,strlen((char *)u8FileName2));
                    memset(au16FileName,0,sizeof(au16FileName));
                    memcpy(au16FileName,u8FileName2,sizeof(au16FileName));

                    if(E_KTV_RET_FAIL!=_MApp_KTV_QueryFileInfo(au16FileName,&FileInfo))
                    {
                        msAPI_FCtrl_FileDelete(&(FileInfo.fileEntry));
                        KTV_DBG(printf("msAPI_FCtrl_FileDelete\n"));
                    }

                   ASCIItoUnicode2((S8*)u8FileName,strlen((char *)u8FileName));
                    memset(au16FileName,0,sizeof(au16FileName));
                    memcpy(au16FileName,u8FileName,sizeof(au16FileName));

                    if(E_KTV_RET_FAIL!=_MApp_KTV_QueryFileInfo(au16FileName,&FileInfo))
                    {
                        msAPI_FCtrl_FileDelete(&(FileInfo.fileEntry));
                        KTV_DBG(printf("msAPI_FCtrl_FileDelete\n"));
                    }
                    u8HandleNo = MApp_FileBrowser_OpenNewFileForWrite(au16FileName,UnicodeLen((S8*)au16FileName));
                    if (u8HandleNo ==  INVALID_FILE_HANDLE)
                    {
                        KTV_DBG(printf("crate file failed\n"));
                    }
                    msAPI_FCtrl_FileWrite(u8HandleNo, ((DOWNLOAD_BUFFER_MEMORY_TYPE & MIU1) ? (DOWNLOAD_BUFFER_ADR | MIU_INTERVAL) : (DOWNLOAD_BUFFER_ADR)), _u32NetInfoLen);
                    msAPI_FCtrl_FileClose(u8HandleNo);
                    KTV_DBG(printf("Write merge.bin finished\n"));
                    u8KeyCode = KEY_RED;
                    u8UpdateReady=1;
                    _u8NetWorkState = E_UPDATE_MERGE_BIN;
                }
                else
                {
                    if(++_u32NetErrorCounter>1000)
                    {
                        _u32NetErrorCounter = 0;
                        _u8NetWorkState = E_GET_MERGE_BIN;
                    }
                }
            }
            break;
            case E_UPDATE_MERGE_BIN:
            KTV_DBG(printf("E_UPDATE_MERGE_BIN....\n"););
            {
                extern void MApp_ZUI_SwUpdate_ProgressBar(U8 percent);
                if(u8UpdateReady==2)
                {
                    printf("System is upgrade software!\n");
                    {
                        typedef void (* pZUIDrawCB)(U8);
                        extern void MApp_UsbDownload_Init(U8 u8USBPortNo, pZUIDrawCB ZUIDrawPercentage);
                        extern BOOLEAN MW_UsbDownload_Search(void);
                        extern BOOLEAN MW_UsbDownload_Start(void);
                        extern U8 MDrv_USBGetPortEnableStatus(void);
                        extern void msAPI_BLoader_Reboot(void);
                        U8 u8PortEnStatus = 0;

                        printf("USB SW Update!\n");
                        u8PortEnStatus = MDrv_USBGetPortEnableStatus();
                        if((u8PortEnStatus & BIT0) == BIT0)
                        {
                            MApp_UsbDownload_Init(BIT0, MApp_ZUI_SwUpdate_ProgressBar);
                        }
                        else if((u8PortEnStatus & BIT1) == BIT1)
                        {
                            MApp_UsbDownload_Init(BIT1, MApp_ZUI_SwUpdate_ProgressBar);
                        }
                        else
                        {
                            printf("Error> Unknown USB port\n");
                            return;
                        }

                        if(!MW_UsbDownload_Search())
                        {
                            break;
                        }

                        if (MW_UsbDownload_Start())
                        {
                            msAPI_BLoader_Reboot();
                        }
                    }
                    u8UpdateReady=0;
                }
                else if(u8UpdateReady==0)
                {
                    _u8NetWorkState = E_NONE;
                }
                else
                {
                }
            }
            break;
        default:
            _u8NetWorkState = E_NONE;
    }
}

/******************************************************************************/

#endif


#undef MAPP_KTV_C

