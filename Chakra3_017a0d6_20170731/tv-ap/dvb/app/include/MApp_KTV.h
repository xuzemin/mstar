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

#ifndef MAPP_KTV_H
#define MAPP_KTV_H

#include "datatype.h"
#include "drvUSB.h"
#include "msAPI_FSCommon.h"

//*****************************************************************************
//              Defines
//*****************************************************************************
#define NUM_OF_SOFTWARE_KEYBOARD_DIGIT_STRING       ((5+1)*2)
#define NUM_OF_SOFTWARE_KEYBOARD_LETTER_STRING      ((4+1)*2)
#define NUM_OF_DIALOG_STRING       (15*2)

#define NUM_OF_SONG_STRING                          30
#define NUM_OF_SINGER_STRING                        20

#define KTV_FILE_INFO_LONG_FILENAME_SIZE    (128-65)

#define NUM_OF_MAX_KTV_DRIVE                    16
#define NUM_OF_MAX_KTV_SELECTED_FILE            10
#define NUM_OF_MAX_KTV_DIRECTORY_DEPTH          30
#define NUM_OF_MAX_KTV_FILES_PER_DIRECTORY      4000
#define KTV_INVALID_INDEX           0xFFFF

#define NUM_OF_KTV_SONGS_PER_PAGE       8
#define NUM_OF_KTV_SINGERS_PER_PAGE       8
#define NUM_OF_KTV_SONGS_FIRSTWORD_PER_PAGE       23

//*****************************************************************************
#define KTV_MUSIC_VOLUME_MAX       200
#define KTV_MUSIC_VOLUME_MIN       0
#define KTV_MUSIC_VOLUME_DEF       10

#define KTV_MIC_VOLUME_MAX       100
#define KTV_MIC_VOLUME_MIN       0
#define KTV_MIC_VOLUME_DEF       30

#define KTV_MELODY_VOLUME_MAX       127
#define KTV_MELODY_VOLUME_MIN       0
#define KTV_MELODY_VOLUME_DEF       64

#define KTV_ECHO_MAX       100
#define KTV_ECHO_MIN       0
#define KTV_ECHO_DEF       30

#define KTV_MUSIC_KEY_MAX       24
#define KTV_MUSIC_KEY_MIN       0
#define KTV_MUSIC_KEY_DEF       12

#define KTV_MUSIC_TEMPO_MAX       400
#define KTV_MUSIC_TEMPO_MIN       10
#define KTV_MUSIC_TEMPO_DEF       100

//*****************************************************************************
#define MIC_URL_DEF             "http://192.168.1.101/iSing99_server/curl.php?ref="
#define DB_URL_DEF              "http://192.168.1.101/iSing99_server/"
#define UPDATE_URL_DEF          "http://192.168.1.101/swupdate/"
#define Reserve_URL1_DEF        "http://"
#define Reserve_URL2_DEF        "http://"
#define Reserve_URL3_DEF        "http://"
#define UART_DEF                0 // 0 don't care // 1 MIPS // 2 HK
#define SKIN_DEF                0 // default skin

#define INI_FILE_SIZE           2048
#define INI_DATA_SIZE           2048
#define INI_URL_SIZE            256

#define ENABLE_AUDIO_ENCODE        1

//*****************************************************************************
//              Enums
//*****************************************************************************
//-----------------------------------------------
// MB_CLASS_KTV
//-----------------------------------------------
typedef enum
{
    MB_KTV_CMD_NONE = 0x00,

    // HK --> Co-processer
    MB_KTV_CMD_CHECK_COPROCESSER_READY      = 0x10,
    MB_KTV_CMD_RESET_IP      = 0x11,
    MB_KTV_CMD_SET_INI_MEM_ADDR     = 0x12,
    MB_KTV_CMD_SET_CMD       = 0x13,
    MB_KTV_CMD_GET_INFO      = 0x14,
    MB_KTV_CMD_SET_SOUND_FONT_MEM_ADDR      = 0x15,
    MB_KTV_CMD_SET_SOUND_MIC_MEM_ADDR      = 0x16,
    MB_KTV_CMD_SET_SOUND_LRC_MEM_ADDR      = 0x17,
    MB_KTV_CMD_OPEN_MIC_FILE_FROM_USB      = 0x18,
    MB_KTV_CMD_PLAY      = 0x19,
    MB_KTV_CMD_STOP      = 0x1A,
    MB_KTV_CMD_PAUSE      = 0x1B,
    MB_KTV_CMD_SET_MUSIC_VOL      = 0x1C,
    MB_KTV_CMD_SET_MUSIC_KEY      = 0x1D,
    MB_KTV_CMD_SET_MUSIC_MELODY      = 0x1E,
    MB_KTV_CMD_SET_MUSIC_TEMPO      = 0x1F,

    // Co-processer --> HK
    MB_KTV_CMD_COPROCESSER_READY      = 0x80,
    MB_KTV_CMD_CLIENT_IP     = 0x81,
    MB_KTV_CMD_HOST_IP        = 0x82,
    MB_KTV_CMD_SET_INFO      = 0x83,
    MB_KTV_CMD_LRC_SIZE      = 0x84,
    MB_KTV_CMD_SERVER_ERROR  = 0x85,
} MB_KTV_CMD;

typedef enum
{
    E_KTV_CURRENT_PLAYLIST=1,
    E_KTV_HISTORY_PLAYLIST,
    E_KTV_FAVORITE_PLAYLIST,
} EN_KTV_PLAYLIST_INFO;

/// Return value for KTV API interface.
typedef enum
{
    E_KTV_RET_OK,                   /// Function execution successfully
    E_KTV_RET_FAIL,                 /// Function failed
    E_KTV_RET_USB_FAIL,             /// USB failed
    E_KTV_RET_CREADER_FAIL,         /// Card reader failed
    E_KTV_RET_UNSUPPORT_FILESYSTEM, /// Unsupported file system type
    E_KTV_RET_NOT_FOUND,            /// Item not found
    E_KTV_RET_DISK_FULL,            /// Disk is full
    E_KTV_RET_UNSUPPORT,            /// Unsupported format
    E_KTV_RET_IGNORE,               /// Ignore this call
    E_KTV_RET_GOP_ERROR,            /// GOP error
    E_KTV_RET_DIRECTORY_TOO_DEEP,   /// Do not support this depth of directory
    E_KTV_RET_NUM,
} enumKTVRet;

typedef enum
{
    E_KTV_USB_NO_DEVICE     = NO_DEVICE,
    E_KTV_USB_USB11_DEVICE  = USB11_DEVICE,
    E_KTV_USB_USB20_DEVICE  = USB20_DEVICE,
    E_KTV_USB_BAD_DEVICE    = BAD_DEVICE,
    E_KTV_USB_NONE          = (BAD_DEVICE+20),
} EN_KTV_DISK_STATUS;

/// Specify the onnection of H/W device
typedef enum
{
    E_KTV_INVALID = 0,  /// Invalid device
    E_KTV_USB0,         /// USB host 0
    E_KTV_USB1,         /// USB host 1
    E_KTV_USB2,         /// USB host 2
    E_KTV_USB3,         /// USB host 3
    E_KTV_CARDREADER0,  /// Card reader 0 (SD/MMC/MS/MS pro)
    E_KTV_CARDREADER1,  /// Card reader 1 (CF)
} enumKTVDeviceType;

/// Specify the file attribute
typedef enum
{
    E_KTV_FILE_RDONLY       = BIT0,    /// Read only file
    E_KTV_FILE_HIDDEN       = BIT1,    /// Read only file
    E_KTV_FILE_SYSTEM       = BIT2,    /// Read only file
    E_KTV_FILE_VOLUME_ID    = BIT3,    /// Read only file
    E_KTV_FILE_DIRECTORY    = BIT4,    /// Specify it is a directory
    E_KTV_FILE_ARCHIVE      = BIT5,    /// Specify it is an archive file
    E_KTV_FILE_SELECT       = BIT6,    /// Specify it is selected file
    E_KTV_FILE_ATTRIBUTE_NUM,           /// Specify the number of file attributes
} enumKTVFileAttribute;

typedef enum
{
    E_KTV_SOUNDFONT_LOADED      = BIT0,
    E_KTV_SOUNDFONTADDRESS_SEND = BIT1,    // Send sound font address, mic address and LRC address to coprocessor
    E_KTV_MICADDRESS_SEND       = BIT2,    // Send sound font address, mic address and LRC address to coprocessor
    E_KTV_LRCADDRESS_SEND       = BIT3,    // Send sound font address, mic address and LRC address to coprocessor
    E_KTV_INIADDRESS_SEND       = BIT4,    // Send INI address to coprocessor
    E_KTV_SONG_LOADED       = BIT5,
    E_KTV_BEGIAN_LOAD       = BIT6,
    E_KTV_LOADFILE_ATTRIBUTE_NUM,           /// Specify the number of file attributes
} enumKTVLoadFileAttribute;

typedef enum
{
    E_KTV_KNL_FLG_NULL                  = 0,        //
    E_KTV_KNL_FLG_FILE_OP_DIFF_DRIVE    = BIT1,    // The drive is different when process file operations.
    E_KTV_KNL_FLG_INITIALIZED           = BIT2,   // Initialized KTV.
    E_KTV_KNL_FLG_DEVICE_INITIALIZED    = BIT3,   // Initialized device.
    E_KTV_KNL_FLG_PLAYLIST_MODIFIED     = BIT4,   // modify playlist.
} enumKTVKnlFlags;

typedef enum
{
    E_KTV_KNL_MOVIE_FLG_NULL                = 0,        //
    E_KTV_KNL_MOVIE_FLG_FILE_INIT           = BIT0,   // Need to do some initialization for media file.
    E_KTV_KNL_MOVIE_FLG_PLAY                = BIT1,    // Movie is playing.
    E_KTV_KNL_MOVIE_FLG_PREDECODE_OK        = BIT2,   // Specify it is a valid movie.
} enumKTVKnlMovieFlags;

/// Specify the zoom mode
typedef enum
{
    E_KTV_ZOOM_1_DIV4,          /// 1/4
    E_KTV_ZOOM_1_DIV2,          /// 1/2
    E_KTV_ZOOM_1,               /// normal
    E_KTV_ZOOM_2,               /// 2x
    E_KTV_ZOOM_4,               /// 4x
    E_KTV_ZOOM_8,               /// 8x
    E_KTV_ZOOM_NUM,             /// Specify the number of zoom scale
} enumKTVZoom;

typedef enum
{
    E_KTV_PLAY_NULL,
    E_KTV_PLAY_NEXT,
    E_KTV_PLAY_ALL_END,
} enumKTVPLAYSTATES;

/// Specify the movie playback mode
typedef enum
{
    E_KTV_MOVIE_NORMAL,         /// Enter normal play mode
    E_KTV_MOVIE_PAUSE,          /// Pause
    E_KTV_MOVIE_FF_2X,          /// Fast forward 2x
    E_KTV_MOVIE_FF_4X,          /// Fast forward 4x
    E_KTV_MOVIE_FF_8X,          /// Fast forward 8x
    E_KTV_MOVIE_FF_16X,         /// Fast forward 16x
    E_KTV_MOVIE_FB_2X,          /// Fast backward 2x
    E_KTV_MOVIE_FB_4X,          /// Fast backward 4x
    E_KTV_MOVIE_FB_8X,          /// Fast backward 8x
    E_KTV_MOVIE_FB_16X,         /// Fast backward 16x
    E_KTV_MOVIE_STEP,           /// STEP to the next video
    E_KTV_MOVIE_SLOW,           /// Slow motion mode
    E_KTV_MOVIE_STOP,           /// Stop playback
    E_KTV_MOVIE_PLAY_MODE_NUM,  /// Specify the number of movie play mode
} enumKTVMoviePlayMode;
/// Specify the Control Type
typedef enum
{
    E_KTV_MOVIE_ACTION_NUL,           /// NUL
    E_KTV_MOVIE_ACTION_PLAY,           /// Enter normal play mode
    E_KTV_MOVIE_ACTION_PAUSE,          /// Pause
    E_KTV_MOVIE_ACTION_STOP,           /// Stop playback
    E_KTV_MOVIE_ACTION_PREV,           /// Pre
    #if 0
    E_KTV_MOVIE_ACTION_FB,             /// Fast backward
    E_KTV_MOVIE_ACTION_FF,             /// Fast forward
    #endif
    E_KTV_MOVIE_ACTION_NEXT,           /// Next
    E_KTV_MOVIE_ACTION_NUM,       /// Specify the number of movie Action mode
} enumKTVMovieActionMode;



//*****************************************************************************
//              Data structure
//*****************************************************************************
typedef struct
{
    U8      u8Input_Offset;
    U8      u8Sting[NUM_OF_SOFTWARE_KEYBOARD_DIGIT_STRING];// 5 digit song id
} KTV_DIGIT_INFO;

typedef struct
{
    U8      u8Input_Offset;
    U8      u8Sting[NUM_OF_SOFTWARE_KEYBOARD_LETTER_STRING];// 4 letter pingyin
} KTV_LETTER_INFO;

typedef struct
{
    U8      u8Line1Sting[NUM_OF_DIALOG_STRING];
    U8      u8Line2Sting[NUM_OF_DIALOG_STRING];
} KTV_DIALOG_INFO;

typedef struct
{
    U8      u8Line1Sting[NUM_OF_DIALOG_STRING+10];
    U8      u8Line2Sting[NUM_OF_DIALOG_STRING];
} KTV_TONE_OF_SONGS_INFO;

typedef struct
{
    enumKTVDeviceType eDeviceType;          /// Device type: USB host X or card reader X
    U8 u8DeviceAddr;                            /// Useless currently.
    U16 u16LunValid;                            /// Use 16-bit to specify which lun are valid
    U16 u16PartitionValid[MSD_USB_2_INDEX_END];  /// Use 16-bit to specify which partition is valid
} KTVDeviceStatus;

typedef struct
{
    enumKTVDeviceType eDeviceType;  /// Device type: USB host X or card reader X
    U8 u8DeviceAddr;                    /// Useless currently.
    U8 u8Lun;                           /// Specify the lun
    U8 u8Partition;                     /// Specify the drive partition index
} KTVDrive;

/// Specify the file information.
typedef struct
{
    U8 u8LongFileName[KTV_FILE_INFO_LONG_FILENAME_SIZE];    /// Long file name
    U8 u8ExtFileName[3+1];                              /// Short extension file name
    enumKTVFileAttribute eAttribute;                       /// File attributes
    U32 u32FileSize;                                    /// File size
    U16 u16Year;                                        /// Year
    U8 u8Month;                                         /// Month
    U8 u8Day;                                           /// Day
    U8 u8Hour;                                          /// Hour
    U8 u8Minute;                                        /// Minute
    U8 u8Second;                                        /// Second
    BOOLEAN bLongFileNameValid;                         /// Specify whether the file name is valid.
    FileEntry fileEntry;                                /// Specify the file entry.
} KTVFileInfo;

typedef enum
{
        E_NONE=0,
        E_CHECK_COPROCESSER_READY,
        E_GET_IP,
        E_CHECK_IP,
        E_GET_VERSION,
        E_CHECK_VERSION,
        E_GET_SINGERLIST,
        E_CHECK_SINGERLIST,
        E_GET_MUSICLIST,
        E_CHECK_MUSICLIST,
        E_GET_SW_VERSION,
        E_CHECK_SW_VERSION,
        E_GET_MERGE_BIN,
        E_CHECK_MERGE_BIN,
        E_UPDATE_MERGE_BIN,
} enumUpdateStates;

typedef struct
{
    U16 MusicVolume;
    U16 MicVolume;
    U16 MelodyVolume;
    U16 Echo;
    U16 MusicKey;
    U16 MusicTempo;
    U8 MusicMode;

    U16 KTVSettingCS;
} MS_KTV_SETTING;

typedef struct
{
    U8      u8MicURLLength;
    U8      u8DBURLLength;
    U8      u8UpdateURLLength;
    U8      u8URL1Length;
    U8      u8URL2Length;
    U8      u8URL3Length;
} KTV_INI_INFO;

#ifdef MAPP_KTV_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

//*****************************************************************************
//              Global variables
//*****************************************************************************
INTERFACE BOOLEAN bServerError;
INTERFACE BOOLEAN bShowErrorInfo;
INTERFACE U8 u8CountNum;
INTERFACE enumKTVPLAYSTATES eplayTheEnd;
INTERFACE enumKTVLoadFileAttribute eKTVLoadFileAttribute;
//*****************************************************************************
//              Function prototypes
//*****************************************************************************
INTERFACE enumKTVRet MApp_KTV_Init(void);
INTERFACE enumKTVRet MApp_KTV_InitializeUsbDevice(void);
INTERFACE enumKTVRet MApp_KTV_ConnectDrive(U16 u16DriveIdx);
INTERFACE enumKTVRet MApp_KTV_ExitKTV(void);
INTERFACE void MApp_KTV_Task(void);
INTERFACE enumKTVRet MApp_KTV_DisconnectAllDevices(void);
INTERFACE enumKTVRet MApp_KTV_QueryMicFileInfo(U16 u16SongIdx, KTVFileInfo *pInfo);
INTERFACE enumKTVRet MApp_KTV_QueryAsciiFileInfo(U8 *pu8Buf, KTVFileInfo *pInfo);
INTERFACE U32 MApp_KTV_FileRead(U32 pBuff);
INTERFACE BOOLEAN MApp_KTV_FileWrite(U32 pBuff, U32 BuffLen);
INTERFACE BOOLEAN MApp_KTV_SetFileEntry(FileEntry *pEntry);
INTERFACE void MApp_KTV_SetPlayListModifyFlag(void);
INTERFACE enumKTVMoviePlayMode _eKTVMoviePlayMode;
INTERFACE enumKTVMovieActionMode _eKTVMovieActionMode;
INTERFACE MS_KTV_SETTING _eKTVVolumeSetting;

INTERFACE U32 MApp_KTV_LoadSoundFontFile(void);
INTERFACE void MApp_KTV_SetSoundFontMemoryAddr(U32 u32MemAddr, U32 u32MemSize);
INTERFACE void MApp_KTV_SetSoundMicMemoryAddr(U32 u32MemAddr, U32 u32MemSize);
INTERFACE void MApp_KTV_Set_LRC_MemoryAddr(U32 u32MemAddr, U32 u32MemSize);
INTERFACE void MApp_KTV_Set_INI_MemoryAddr(U32 u32MemAddr);
INTERFACE void MApp_KTV_SendMailBoxCmd(MB_KTV_CMD u8KTVCmd, U32 u32Parameter);
INTERFACE void MApp_KTV_Play(void);
INTERFACE void MApp_KTV_Pause(void);
INTERFACE void MApp_KTV_Stop(void);
//RobertYang
#if ENABLE_AUDIO_ENCODE
INTERFACE void MApp_KTV_RecordStart(void);
INTERFACE void MApp_KTV_RecordStop(void);
#endif
INTERFACE void MApp_KTV_OpenMicFileFromUsb(void);
INTERFACE void MApp_KTV_DownloadMicFile(U32 u32MicId);
INTERFACE void MApp_KTV_OpenMicFileToBuffer(void);

#undef INTERFACE

#endif


