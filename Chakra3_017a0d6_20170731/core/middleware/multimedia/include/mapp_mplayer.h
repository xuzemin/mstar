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
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
/// @file MApp_MPlayer.h
/// @brief Media player kernel
/// @author MStar Semiconductor Inc.
///
/// Media player kernel provide a simple interface to let users implement
/// media player on MStar chip.
///
////////////////////////////////////////////////////////////////////////////////

#ifndef MAPP_MPLAYER_H
#define MAPP_MPLAYER_H

#include "datatype.h"
#include "apiGOP.h"
#include "MApp_UiMediaPlayer_Define.h"
#include "MApp_Exit.h"
#include "mapp_music.h"
#include "drvUSB.h"
#include "msAPI_FSCommon.h"
#include "apiGFX.h"
#include "MApp_GlobalSettingSt.h"
#include "msAPI_FCtrl.h"
#include "mapp_photo_display.h"

//*****************************************************************************
//              Defines
//*****************************************************************************
#ifndef HIDE_HIDDEN_FILE
    #define HIDE_HIDDEN_FILE                0
#endif

#ifndef ENABLE_MPLAYER_SORT
    #define ENABLE_MPLAYER_SORT             0// 1
    #if ENABLE_MPLAYER_SORT
        #define ENABLE_MPLAYER_SORT_EX      1
    #else
        #define ENABLE_MPLAYER_SORT_EX      0
    #endif
#endif

#if ENABLE_SUBTITLE_DMP
#define ENABLE_SUBTITLE_COPY_AND_DELETE 0
#else
#define ENABLE_SUBTITLE_COPY_AND_DELETE 0
#endif

#define MPLAYER_INVALID_INDEX               0xFFFF


#if OBA2
//os
#define MPlayerFileInfo_SIZE    512
#if (HIGH_SPEED_BROWSER)
#if (ENABLE_MPLAYER_SORT)
#define FILE_INFO_LONG_FILENAME_SIZE    (MPlayerFileInfo_SIZE-312) // Let sizeof(MPlayerFileInfo) to be 512-byte
#else
#define FILE_INFO_LONG_FILENAME_SIZE    (MPlayerFileInfo_SIZE-308) // Let sizeof(MPlayerFileInfo) to be 512-byte
#endif
#else//#if (HIGH_SPEED_BROWSER)
#define FILE_INFO_LONG_FILENAME_SIZE    (MPlayerFileInfo_SIZE-24) // Let sizeof(MPlayerFileInfo) to be 512-byte
#endif//#if (HIGH_SPEED_BROWSER)
#else//#if OBA2
//no os
#if ENABLE_FILE_INFO_LONG_FILENAME_SIZE_INCREASE==1
#define MPlayerFileInfo_SIZE    256
#else
#define MPlayerFileInfo_SIZE    128
#endif
#if (HIGH_SPEED_BROWSER)
#if (ENABLE_MPLAYER_SORT)
#define FILE_INFO_LONG_FILENAME_SIZE    (MPlayerFileInfo_SIZE-68) // Let sizeof(MPlayerFileInfo) to be 128/256-byte
#else
#define FILE_INFO_LONG_FILENAME_SIZE    (MPlayerFileInfo_SIZE-64) // Let sizeof(MPlayerFileInfo) to be 128/256-byte
#endif
#else//#if (HIGH_SPEED_BROWSER)
#define FILE_INFO_LONG_FILENAME_SIZE    (MPlayerFileInfo_SIZE-24) // Let sizeof(MPlayerFileInfo) to be 128/256-byte
#endif//#if (HIGH_SPEED_BROWSER)
#endif//#if OBA2

#define ENABLE_LYRICS3                  0
#define ENABLE_LRC_LYRIC                1
#define ENABLE_MOVIE_PREVIEW            1
#define ENABLE_WMDRMPD                  0
#define ENABLE_WMV                      0
#define ENABLE_DVD                      0

#if (defined(ENABLE_MPLAYER_MUSIC) && (ENABLE_MPLAYER_MUSIC))
    #if ((MEMORY_MAP == MMAP_32MB) && (ENABLE_32M_H264 == ENABLE))
    #define ENABLE_AAC                              0
    #define ENABLE_WMA                              0
    #define ENABLE_FLAC                             0
    #define ENABLE_AC3                              0
    #define ENABLE_WAV                              0
    #define ENABLE_OGG                              0   //all chip in Chakra3 support OGG
    #define ENABLE_NON_PARSING_AUDIO_DATA_INPUT     0
    #define ENABLE_AMR                              0
    #define ENABLE_BMP                              0
    #define ENABLE_PNG                              0
    #define ENABLE_GIF                              0
    #define ENABLE_TIFF                             0
    #else
    #define ENABLE_AAC                              1
    #define ENABLE_WMA                              1
    #define ENABLE_FLAC                             1
    #define ENABLE_AC3                              1
    #define ENABLE_WAV                              1
    #define ENABLE_OGG                              1   //all chip in Chakra3 support OGG
    #define ENABLE_NON_PARSING_AUDIO_DATA_INPUT     0
    #define ENABLE_AMR                              0
    #define ENABLE_BMP                              1
    #define ENABLE_PNG                              1
    #define ENABLE_GIF                              0
    #define ENABLE_TIFF                             0
    #endif
#else
    #define ENABLE_AAC                              0
    #define ENABLE_WMA                              0
    #define ENABLE_WAV                              0
    #define ENABLE_OGG                              0
    #define ENABLE_AMR                              0
    #define ENABLE_FLAC                             0
    #define ENABLE_AC3                              0
    #define ENABLE_BMP                              1
    #define ENABLE_PNG                              1
    #define ENABLE_GIF                              0
    #define ENABLE_TIFF                             0
#endif // #if (defined(ENABLE_MPLAYER_MUSIC) && (ENABLE_MPLAYER_MUSIC))

#ifndef HIGH_SPEED_BROWSER
    #define HIGH_SPEED_BROWSER                      0
#endif

#ifndef ENABLE_MOVIE_PREVIEW_ALL_AND_1ST_FRAME
    #define ENABLE_MOVIE_PREVIEW_ALL_AND_1ST_FRAME  0
#endif

#ifndef ENABLE_MOVIE_PREVIEW_1ST_FRAME
    #define ENABLE_MOVIE_PREVIEW_1ST_FRAME          0
#endif

#ifndef ENABLE_MOVIE_PREVIEW_1ST_FRAME_POS_MS
    #define ENABLE_MOVIE_PREVIEW_1ST_FRAME_POS_MS   2000
#endif

#ifndef ENABLE_USB_DETECT_STEP_BY_STEP
    #define ENABLE_USB_DETECT_STEP_BY_STEP          0
#endif

#if ENABLE_CI_PLUS
#define DWIN_MOVIE_PREVIEW      0
#else
#define DWIN_MOVIE_PREVIEW      0
#endif
#define ENABLE_DIVX_PLUS        0

#define SUPPORT_ONE_FILE_HANDLE_APP_BUT_DEMUX_USE_2_FILE_HANDLE     0
#define ENABLE_PROBE_MOVIE_HEADER   1
#define NOTIFY_ACTIVE_DEVICE_CHANGE_ONLY_WHEN_CURRENT_LUN_REMOVE 0

#if ENABLE_SUBTITLE_DMP
#define ENALBE_RENDER_SUBTITLE_IN_TRICK_MODE 0
#define ENABLE_INTERNAL_AND_EXTERNAL_SUBTITLE 1
#endif

#if (ENABLE_MPLAYER_VIDEO_CAPTURE || ENABLE_MPLAYER_AUDIO_CAPTURE)
#define CAPTURE_MAX_PATH_LEN                255
#define CAPTURE_MAX_FILENAME_BUFFER_SIZE    512
#endif

//*****************************************************************************
//              Macro
//*****************************************************************************

#define MPLAYER_EXIF_CAMERA_MAKER_SIZE  32
#define MPLAYER_EXIF_CAMERA_MODEL_SIZE  128

//*****************************************************************************
//              Enums
//*****************************************************************************
/// Return value for media player API interface.
typedef enum
{
    E_MPLAYER_RET_OK,                   /// Function execution successfully
    E_MPLAYER_RET_FAIL,                 /// Function failed
    E_MPLAYER_RET_USB_FAIL,             /// USB failed
    E_MPLAYER_RET_CREADER_FAIL,         /// Card reader failed
    E_MPLAYER_RET_UNSUPPORT_FILESYSTEM, /// Unsupported file system type
    E_MPLAYER_RET_NOT_FOUND,            /// Item not found
    E_MPLAYER_RET_DISK_FULL,            /// Disk is full
    E_MPLAYER_RET_UNSUPPORT,            /// Unsupported format
    E_MPLAYER_RET_IGNORE,               /// Ignore this call
    E_MPLAYER_RET_GOP_ERROR,            /// GOP error
    E_MPLAYER_RET_DIRECTORY_TOO_DEEP,   /// Do not support this depth of directory
    E_MPLAYER_RET_NUM,
} enumMPlayerRet;

#if (ENABLE_MPLAYER_VIDEO_CAPTURE || ENABLE_MPLAYER_AUDIO_CAPTURE)
typedef enum
{
    E_CAPTURE_RET_OK,                   /// Function execution successfully
    E_CAPTURE_RET_FAIL,                 /// Function failed
    E_CAPTURE_RET_CONTINUE,             /// Function working
    E_CAPTURE_RET_USB_FAIL,             /// USB failed
    E_CAPTURE_RET_CREADER_FAIL,         /// Card reader failed
    E_CAPTURE_RET_UNSUPPORT_FILESYSTEM, /// Unsupported file system type
    E_CAPTURE_RET_NOT_FOUND,            /// Item not found
    E_CAPTURE_RET_DISK_FULL,            /// Disk is full
    E_CAPTURE_RET_UNSUPPORT,            /// Unsupported format
    E_CAPTURE_RET_IGNORE,               /// Ignore this call
    E_CAPTURE_RET_NUM,
} enumCaptureRet;
#endif

/// Specify the connection of H/W device
typedef enum
{
    E_MPLAYER_INVALID = 0,  /// Invalid device
    E_MPLAYER_USB0,         /// USB host 0
    E_MPLAYER_USB1,         /// USB host 1
    E_MPLAYER_USB2,         /// USB host 2
    E_MPLAYER_USB3,         /// USB host 3
    E_MPLAYER_CARDREADER0,  /// Card reader 0 (SD/MMC/MS/MS pro)
    E_MPLAYER_CARDREADER1,  /// Card reader 1 (CF)
} enumMPlayerDeviceType;

/// Specify the file attribute
typedef enum
{
    E_MPLAYER_FILE_RDONLY       = BIT0,    /// Read only file
    E_MPLAYER_FILE_HIDDEN       = BIT1,    /// Read only file
    E_MPLAYER_FILE_SYSTEM       = BIT2,    /// Read only file
    E_MPLAYER_FILE_VOLUME_ID    = BIT3,    /// Read only file
    E_MPLAYER_FILE_DIRECTORY    = BIT4,    /// Specify it is a directory
    E_MPLAYER_FILE_ARCHIVE      = BIT5,    /// Specify it is an archive file
    E_MPLAYER_FILE_SELECT       = BIT6,    /// Specify it is selected file
    E_MPLAYER_FILE_DECODED_FAIL = BIT7,    /// Specify it is a decoded fail file
    E_MPLAYER_FILE_ATTRIBUTE_NUM,           /// Specify the number of file attributes
} enumFileAttribute;
#define Remove_enumFileAttribute(val, attr)  \
   do{(val) = (enumFileAttribute)(((U8)(val))&~(attr));}while(0)

/// Specify the beginning of file index.
typedef enum
{
    E_MPLAYER_INDEX_CURRENT_DIRECTORY,  /// From the beginning of current directory
    E_MPLAYER_INDEX_CURRENT_PAGE,       /// From the beginning of current page
    E_MPLAYER_INDEX_TYPE_NUM,           /// Specify the index type number
} enumMPlayerFileIndexBegin;

/// Specify the repeat mode.
typedef enum
{
    E_MPLAYER_REPEAT_NONE,          /// Disable repeat mode
    E_MPLAYER_REPEAT_1,             /// Repeat to play one media file.
    E_MPLAYER_REPEAT_ALL,           /// Repeat to all selected files
    E_MPLAYER_REPEAT_MODE_NUM,      /// Specify the number of repeat mode
} enumMPlayerRepeatMode;

#if RANDOM_PLAY
/// Specify the repeat mode.
typedef enum
{
    E_MPLAYER_RANDOM_NONE,          /// Disable random mode
    E_MPLAYER_RANDOM,               /// Random play media files.
    E_MPLAYER_RANDOM_MODE_NUM,      /// Specify the number of random mode
} enumMPlayerRandomMode;
#endif

#if ENABLE_MPLAYER_SORT_EX
typedef enum
{
    E_MPLAYER_SORT_NONE,            /// Disable sort mode.
    E_MPLAYER_SORT_BY_NAME,         /// Sort by name.
    E_MPLAYER_SORT_BY_TIME,         /// Sort by time.
    E_MPLAYER_SORT_TYPE_NUM,        /// Specify the number of sorting mode.
} enumMPlayerFileSortMode;

typedef enum
{
    E_MPLAYER_SORT_INCREMENT_ORDER,      /// Increment order.
    E_MPLAYER_SORT_DECREASING_ORDER,     /// Decreasing order.
    E_MPLAYER_ORDER_TYPE_NUM,            /// Specify the number of order mode.
} enumMPlayerFileSortSubMode;
#endif //ENABLE_MPLAYER_SORT_EX

/// Specify the play mode.
typedef enum
{
    E_MPLAYER_PLAY_ONE,             /// Play the current file.
    E_MPLAYER_PLAY_SELECTED,        /// Play the files in the selected list.
    E_MPLAYER_PLAY_SELECTED_FROM_CURRENT, /// Play the files in the selected list.
    E_MPLAYER_PLAY_ONE_DIRECTORY,   /// Play all files in the current directory.
    E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT,  /// Play all files in the current directory from the current selection.
    E_MPLAYER_PLAY_MODE_NUM,        /// Specify the number of play mode
} enumMPlayerPlayMode;

/// Specify the media mode
typedef enum
{
#if ENABLE_MPLAYER_PHOTO
    E_MPLAYER_TYPE_PHOTO,           /// Photo mode
#endif
#if ENABLE_MPLAYER_MUSIC
    E_MPLAYER_TYPE_MUSIC,           /// Music mode.
#endif
#if ENABLE_MPLAYER_MOVIE
    E_MPLAYER_TYPE_MOVIE,           /// movie mode
#endif
#if ENABLE_MPLAYER_TEXT
    E_MPLAYER_TYPE_TEXT,            /// text mode
#endif
#if ENABLE_MPLAYER_PLUGIN
    E_MPLAYER_TYPE_PLUGIN,             /// Plug-in APP mode
#endif //#if ENABLE_MPLAYER_PLUGIN
#if ENABLE_MPLAYER_MIXED
    E_MPLAYER_TYPE_MIXED,             /// mixed mode
#endif //#if ENABLE_MPLAYER_MIXED
    E_MPLAYER_TYPE_NUM,             /// Specify the number of media mode
    E_MPLAYER_TYPE_INVALID,         /// invalid mode
} enumMPlayerMediaType;

/// Specify the zoom mode
typedef enum
{
    E_MPLAYER_ZOOM_1_DIV4,          /// 1/4
    E_MPLAYER_ZOOM_1_DIV2,          /// 1/2
    E_MPLAYER_ZOOM_1,               /// normal
    E_MPLAYER_ZOOM_2,               /// 2x
    E_MPLAYER_ZOOM_4,               /// 4x
    E_MPLAYER_ZOOM_8,               /// 8x
    E_MPLAYER_ZOOM_NUM,             /// Specify the number of zoom scale
} enumMPlayerZoom;

/// Specify the movie playback mode
typedef enum
{
    E_MPLAYER_MOVIE_NORMAL,         /// Enter normal play mode
    E_MPLAYER_MOVIE_PAUSE,          /// Pause
    E_MPLAYER_MOVIE_FF_2X,          /// Fast forward 2x
    E_MPLAYER_MOVIE_FF_4X,          /// Fast forward 4x
    E_MPLAYER_MOVIE_FF_8X,          /// Fast forward 8x
    E_MPLAYER_MOVIE_FF_16X,         /// Fast forward 16x
    E_MPLAYER_MOVIE_FF_32X,         /// Fast forward 32x
    E_MPLAYER_MOVIE_FB_2X,          /// Fast backward 2x
    E_MPLAYER_MOVIE_FB_4X,          /// Fast backward 4x
    E_MPLAYER_MOVIE_FB_8X,          /// Fast backward 8x
    E_MPLAYER_MOVIE_FB_16X,         /// Fast backward 16x
    E_MPLAYER_MOVIE_FB_32X,         /// Fast backward 32x
    E_MPLAYER_MOVIE_SF_2X,          /// slow forward 2x
    E_MPLAYER_MOVIE_SF_4X,          /// slow forward 4x
    E_MPLAYER_MOVIE_SF_8X,          /// slow forward 8x
    E_MPLAYER_MOVIE_SF_16X,         /// slow forward 16x
    E_MPLAYER_MOVIE_STEP,           /// STEP to the next video
    E_MPLAYER_MOVIE_STOP,           /// Stop playback
    E_MPLAYER_MOVIE_PLAY_MODE_NUM,  /// Specify the number of movie play mode
} enumMPlayerMoviePlayMode;

/// Specify the movie repeatAB mode
typedef enum
{
    E_MPLAYER_MOVIE_SET_REPEAT_AB_NONE,  //cancel repeatAB
    E_MPLAYER_MOVIE_SET_REPEAT_A,  //set repeat_A
    E_MPLAYER_MOVIE_SET_REPEAT_B,  //set repeat_B
} enumMPlayerMovieRepeatAB;


/// Specify the photo playback mode
typedef enum
{
    E_MPLAYER_PHOTO_NORMAL,         /// Normal mode
    E_MPLAYER_PHOTO_PAUSE,          /// Pause
    E_MPLAYER_PHOTO_PLAY_MODE_NUM,  /// Specify the number of photo play mode
} enumMPlayerPhotoPlayMode;

/// Specify the music playback mode
typedef enum
{
    E_MPLAYER_MUSIC_NORMAL,         /// Enter normal play mode
    E_MPLAYER_MUSIC_PAUSE,          /// Pause
    E_MPLAYER_MUSIC_FF_2X,          /// Fast forward 2X
    E_MPLAYER_MUSIC_FF_4X,          /// Fast forward 4X
    E_MPLAYER_MUSIC_FF_8X,          /// Fast forward 8X
    E_MPLAYER_MUSIC_FF_16X,         /// Fast forward 16X
    E_MPLAYER_MUSIC_FB_2X,          /// Fast backward 2X
    E_MPLAYER_MUSIC_FB_4X,          /// Fast backward 4X
    E_MPLAYER_MUSIC_FB_8X,          /// Fast backward 8X
    E_MPLAYER_MUSIC_FB_16X,         /// Fast backward 16X
    E_MPLAYER_MUSIC_STOP,           /// Stop playback
    E_MPLAYER_MUSIC_PLAY_MODE_NUM,  /// Specify the number of music play mode
} enumMPlayerMusicPlayMode;

//This enum definition is the same with EN_MUSIC_INFO in mapp_music.h
//You must sync these two enum
typedef enum
{
    E_MPLAYER_MUSIC_INFO_BASIC = 0x01,
    E_MPLAYER_MUSIC_INFO_DURATION = 0x02
} enumMPlayerMusicInfo;

/// Specify the photo rotation degree
typedef enum
{
    E_MPLAYER_PHOTO_ROTATE_0,       /// rotate 0 degree
    E_MPLAYER_PHOTO_ROTATE_90,      /// rotate 90 degree
    E_MPLAYER_PHOTO_ROTATE_180,     /// rotate 180 degree
    E_MPLAYER_PHOTO_ROTATE_270,     /// rotate 270 degree
    E_MPLAYER_PHOTO_ROTATE_MODE_NUM,/// Specify the number of photo rotation mode
} enumMPlayerPhotoRotate;

/// Specify the JPEG orient
typedef enum
{
    E_MPLAYER_JPEG_ORIENT_ORIGINAL,     /// Orient original
    E_MPLAYER_JPEG_ORIENT_TOP_LEFT,     /// Orient top left
    E_MPLAYER_JPEG_ORIENT_TOP_RIGHT,    /// Orient top right
    E_MPLAYER_JPEG_ORIENT_BOTTOM_RIGHT, /// Orient bottom right
    E_MPLAYER_JPEG_ORIENT_BOTTOM_LEFT,  /// Orient bottom left
    E_MPLAYER_JPEG_ORIENT_LEFT_TOP,     /// Orient left top
    E_MPLAYER_JPEG_ORIENT_RIGHT_TOP,    /// Orient right top
    E_MPLAYER_JPEG_ORIENT_RIGHT_BOTTOM, /// Orient right bottom
    E_MPLAYER_JPEG_ORIENT_LEFT_BOTTOM,  /// Orient left bottom
    E_MPLAYER_JPEG_ORIENT_NUM,          /// Specify the JPEG orient number
} enumMPlayerJPGOrient;

/// Specify the JPEG attribute flag
typedef enum
{
    E_MPLAYER_JPEG_FLAG_JPEG        = BIT0,    /// A valid JPEG
    E_MPLAYER_JPEG_FLAG_BASELINE    = BIT1,    /// Baseline JPEG
    E_MPLAYER_JPEG_FLAG_PROGRESIVE  = BIT2,    /// Progressive JPEG
    E_MPLAYER_JPEG_FLAG_THUMBNAIL   = BIT4,    /// Has embedded JPEG
} enumMPlayerJPGFlag;

/// Specify the media sub-type
typedef enum
{
#if ENABLE_MPLAYER_PHOTO
    E_MPLAYER_SUBTYPE_JPG,              /// JPEG
#if ENABLE_BMP
    E_MPLAYER_SUBTYPE_BMP,              /// BMP
#endif
#if ENABLE_PNG
    E_MPLAYER_SUBTYPE_PNG,              /// PNG
#endif
#if ENABLE_TIFF
    E_MPLAYER_SUBTYPE_TIFF,             /// TIFF
#endif
#if ENABLE_GIF
    E_MPLAYER_SUBTYPE_GIF,               /// GIF
#endif
#endif  // #if ENABLE_MPLAYER_PHOTO
#if ENABLE_MPLAYER_MOVIE
    E_MPLAYER_SUBTYPE_TS,               /// TS
    E_MPLAYER_SUBTYPE_RM,               /// RM
    E_MPLAYER_SUBTYPE_MPEG,             /// MPEG1 or MPEG2
    E_MPLAYER_SUBTYPE_MPEG4,            /// MPEG4
#if ENABLE_WMV
    E_MPLAYER_SUBTYPE_WMV,              /// WMV
#endif
#if ENABLE_DVD
    E_MPLAYER_SUBTYPE_DVD,              /// DVD
    E_MPLAYER_SUBTYPE_IFO,              /// IFO
#endif
    E_MPLAYER_SUBTYPE_MOVIE,
#endif  // #if ENABLE_MPLAYER_MOVIE
#if ENABLE_MPLAYER_MUSIC
    E_MPLAYER_SUBTYPE_MP3,              /// MP3
#if ENABLE_FLAC
    E_MPLAYER_SUBTYPE_FLAC,             ///FLAC
#endif
#if ENABLE_AC3
    E_MPLAYER_SUBTYPE_AC3,              ///AC3
#endif
#if ENABLE_AAC
    E_MPLAYER_SUBTYPE_AAC,              /// AAC
#endif
#if ENABLE_WAV
    E_MPLAYER_SUBTYPE_WAV,              /// WAV (PCM)
#endif
#if ENABLE_WMA
    E_MPLAYER_SUBTYPE_WMA,              /// WMA
#endif  // #if ENABLE_WMA
#if ENABLE_OGG
    E_MPLAYER_SUBTYPE_OGG,              /// OGG
#endif
#if ENABLE_AMR
    E_MPLAYER_SUBTYPE_AMR,              /// AMR
    E_MPLAYER_SUBTYPE_AWB,              /// AWB
#endif
#if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
    E_MPLAYER_SUBTYPE_LOAS,              /// LOAS
#endif //#if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
#endif  // #if ENABLE_MPLAYER_MUSIC
#if ENABLE_MPLAYER_TEXT
    E_MPLAYER_SUBTYPE_TEXT,             /// TEXT
#endif  // #if ENABLE_MPLAYER_TEXT
#if ENABLE_MPLAYER_PLUGIN
    E_MPLAYER_SUBTYPE_PLG,             /// Plug-in APP
#endif //#if ENABLE_MPLAYER_PLUGIN
    E_MPLAYER_SUBTYPE_NUM,              /// Specify the number of media sub-type
    E_MPLAYER_SUBTYPE_INVALID,          /// invalid mode
} enumMPlayerMediaSubType;

/// Specify the video type
typedef enum
{
    E_MPLAYER_VIDEO_TYPE_MPEG1,         /// MPEG1
    E_MPLAYER_VIDEO_TYPE_MPEG2,         /// MPEG2
    E_MPLAYER_VIDEO_TYPE_DIVX,          /// DIVX
    E_MPLAYER_VIDEO_TYPE_XVID,          /// XVID
    E_MPLAYER_VIDEO_TYPE_NUM,           /// Specify the number of video type
    E_MPLAYER_VIDEO_TYPE_INVALID,       /// invalid mode
} enumMPlayerMovieVideoType;

/// Specify the audio type
typedef enum
{
    E_MPLAYER_AUDIO_TYPE_MPEG,          /// MPEG (not including MP3)
    E_MPLAYER_AUDIO_TYPE_MP3,           /// MP3
    E_MPLAYER_AUDIO_TYPE_AAC,           /// AAC
    E_MPLAYER_AUDIO_TYPE_AC3,           /// AC3
    E_MPLAYER_AUDIO_TYPE_DTS,           /// DTS
    E_MPLAYER_AUDIO_TYPE_PCM,           /// PCM
    E_MPLAYER_AUDIO_TYPE_NOAUDIO,       /// No audio
    E_MPLAYER_AUDIO_TYPE_NUM,           /// Specify the number of audio type
    E_MPLAYER_AUDIO_TYPE_INVALID,       /// invalid mode
} enumMPlayerMovieAudioType;

/// Specify the notification type.
typedef enum
{
    E_MPLAYER_NOTIFY_DRIVE_CHANGE=0,        /// Drive connection status change
    E_MPLAYER_NOTIFY_HIDE_SUBTITLE,         /// Hide subtitle
    E_MPLAYER_NOTIFY_SHOW_SUBTITLE,         /// Show subtitle
    E_MPLAYER_NOTIFY_SHOW_LYRIC,            /// Show lyric
    E_MPLAYER_NOTIFY_PLAYING_TIME_TICK,     /// playing time changed in 1 second tick
    E_MPLAYER_NOTIFY_SHOW_MUSIC_NFO,            /// show music file info, lit Album,Title...
    E_MPLAYER_NOTIFY_BEFORE_PHOTO_PREVIEW,  /// Begin of photo preview
    E_MPLAYER_NOTIFY_END_OF_PHOTO_PREVIEW,  /// End of photo preview
    E_MPLAYER_NOTIFY_BEFORE_MUSIC_PREVIEW,  /// Begin of music preview
    E_MPLAYER_NOTIFY_END_OF_MUSIC_PREVIEW,  /// End of music preview
    E_MPLAYER_NOTIFY_BEFORE_MOVIE_PREVIEW,
    E_MPLAYER_NOTIFY_END_OF_MOVIE_PREVIEW,  /// End of movie preview
    E_MPLAYER_NOTIFY_END_OF_TEXT_PREVIEW,   /// End of text preview
    E_MPLAYER_NOTIFY_END_OF_ONE_THUMBNAIL,  /// End of one thumbnail
    E_MPLAYER_NOTIFY_END_OF_THUMBNAIL,      /// End of all thumbnails
    E_MPLAYER_NOTIFY_BEFORE_PLAY_ONE_FILE,  /// before play one media file
    E_MPLAYER_NOTIFY_END_OF_PLAY_ONE_FILE,  /// end of one media file playback
    E_MPLAYER_NOTIFY_END_OF_PLAY_ALL_FILE,  /// end of all media files playback
    E_MPLAYER_NOTIFY_ERROR_OF_PLAY_FILE,    /// Error when playing media file
    E_MPLAYER_NOTIFY_USB_DEVICE_STATUS_CHANGE,  /// USB device status changed
    E_MPLAYER_NOTIFY_USB_ACTIVE_DEVICE_STATUS_CHANGE, /// Current USB device had been inserted/removed
    E_MPLAYER_NOTIFY_MEDIA_PREDECODE_OK,        /// Specify the current playing media file is a valid media file.
#ifdef MEDIA_PLAYER_HIGHLIGHT_CHANGE
    E_MPLAYER_NOTIFY_PLAY_NEXT_FILE,            /// play next media file
    E_MPLAYER_NOTIFY_PLAY_PREVIOUS_FILE,        /// play previous media file
#endif
#if ENBALE_PARENTALRATING_MM
    E_MPLAYER_NOTIFY_MOVIE_RATING_CONTROL,     //Start UI for parental contral in MM
#endif
    E_MPLAYER_NOTIFY_TEXT_PREV_PAGE,
    E_MPLAYER_NOTIFY_TEXT_NEXT_PAGE,
    E_MPLAYER_NOTIFY_PHOTO_INFO_OK,
    E_MPLAYER_NOTIFY_SETUP_DISPLAY,
#if ENABLE_DVD
    E_MPLAYER_NOTIFY_DVD_RESUME_NORMAL_PLAY,
#endif
#if ENABLE_DRM
    E_MPLAYER_NOTIFY_DRM_INIT,
#endif
#if ENABLE_LAST_MEMORY==1
    E_MPLAYER_NOTIFY_LAST_MEMORY_RESUME_PLAY,
#endif
#if ENABLE_EMBEDDED_PHOTO_DISPLAY
    E_MPLAYER_NOTIFY_BEFORE_EMBEDDED_PHOTO_DISPLAY,     //Begin of embedded photo display
    E_MPLAYER_NOTIFY_END_OF_EMBEDDED_PHOTO_DISPLAY,     //end of embedded photo display
    E_MPLAYER_NOTIFY_ERROR_OF_EMBEDDED_PHOTO_DISPLAY,   //error when embedded photo display
#endif

    E_MPLAYER_NOTIFY_BEFORE_COPY_ONE_FILE,      /// Before copy/delete one file
    E_MPLAYER_NOTIFY_END_OF_COPY_ONE_FILE,      /// End of copy/delete one file
    E_MPLAYER_NOTIFY_END_OF_COPY_ALL_FILE,      /// End of copy/delete all file
    E_MPLAYER_NOTIFY_ERROR_OF_COPY_FILE,        /// Error when playing media file
    E_MPLAYER_NOTIFY_UNSUPPORT_FS_OF_COPY_FILE,         /// unsupport file system of copy file
    E_MPLAYER_NOTIFY_NO_ENOUGH_SPACE_OF_COPY_FILE,      /// No enough space of copy file
    E_MPLAYER_NOTIFY_COPY_USED_USB_REMOVE,              /// Used USB be removed when copying.
    E_MPLAYER_NOTIFY_UPDATE_COPIED_FILE_SIZE,           /// Notify total copied copy file size


    E_MPLAYER_NOTIFY_BEFORE_DELETE_ONE_FILE,    /// Before copy/delete one file
    E_MPLAYER_NOTIFY_END_OF_DELETE_ONE_FILE,    /// End of copy/delete one file
    E_MPLAYER_NOTIFY_END_OF_DELETE_ALL_FILE,    /// End of copy/delete all file
    E_MPLAYER_NOTIFY_ERROR_OF_DELETE_FILE,      /// Error when playing media file
    E_MPLAYER_NOTIFY_DELETE_USED_USB_REMOVE,    /// Used USB be removed when deleting.


    E_MPLAYER_NOTIFY_BEFORE_FORMAT,         /// Before format partition
    E_MPLAYER_NOTIFY_END_OF_FORMAT,         /// End of format partition
    E_MPLAYER_NOTIFY_UNSUPPORT_FS_OF_FORMAT,         /// unsupport file system of FORMAT

    E_MPLAYER_NOTIFY_NUM,                   /// Specify the notification type number
    E_MPLAYER_NOTIFY_ALL,                   /// All notifications.
} enumMPlayerNotifyType;

/// Specify the direction of move window
typedef enum
{
    E_MPLAYER_DIRECTION_UP = 0,     /// Move up
    E_MPLAYER_DIRECTION_DOWN,       /// Move down
    E_MPLAYER_DIRECTION_LEFT,       /// Move left
    E_MPLAYER_DIRECTION_RIGHT,      /// Move right
    E_MPLAYER_DIRECTION_NUM,
} enumMPlayerMoveDirection;

typedef enum
{
    E_MPLAYER_USB_NO_DEVICE     = NO_DEVICE,
    E_MPLAYER_USB_USB11_DEVICE  = USB11_DEVICE,
    E_MPLAYER_USB_USB20_DEVICE  = USB20_DEVICE,
    E_MPLAYER_USB_BAD_DEVICE    = BAD_DEVICE,
    E_MPLAYER_USB_NONE          = (BAD_DEVICE+20),
} enumMPlayerUSBDeviceStatus;

#if ENABLE_MPLAYER_PHOTO
typedef enum
{
    E_MPLAYER_PHOTO_DECODER_INIT = 0,
    E_MPLAYER_PHOTO_DECODER_OPENFILE,
    E_MPLAYER_PHOTO_DECODER_DECODING,
    E_MPLAYER_PHOTO_DECODER_DECODE_DONE,
    E_MPLAYER_PHOTO_DECODER_INVALID_NUM,
} enumMPlayerPhotoDecoderState;
#endif  // #if ENABLE_MPLAYER_PHOTO

typedef enum
{
    E_PHOTO_PREVIEW_NONE,               // need not to do photo preview.
    E_PHOTO_PREVIEW_TIMER_ENABLE,       // Begin count down.
    E_PHOTO_PREVIEW_RUNNING,            // Initialize preview.
    E_PHOTO_PREVIEW_DONE,               //need to do stop photo preview.
    E_PHOTO_PREVIEW_MODE_NUM,           // Specify the number of photo preview mode.
} enumPhotoPreviewState;

typedef enum
{
    E_MUSIC_PREVIEW_NONE,               // need not to do music preview.
    E_MUSIC_PREVIEW_TIMER_ENABLE,       // Begin count down.
    E_MUSIC_PREVIEW_RUNNING,            // Initialize preview.
    E_MUSIC_PREVIEW_MODE_NUM,           // Specify the number of music preview mode.
} enumMusicPreviewState;

typedef enum
{
    E_MOVIE_PREVIEW_NONE,               // need not to do movie preview.
    E_MOVIE_PREVIEW_TIMER_ENABLE,       // Begin count down.
    E_MOVIE_PREVIEW_RUNNING,            // Initialize preview.
    E_MOVIE_PREVIEW_1ST_FRAME_PREDECODE,// predecode the 1st frame.
    E_MOVIE_PREVIEW_1ST_FRAME_DECODE,   // decode the 1st frame.
    E_MOVIE_PREVIEW_DONE,               //need to do stop movie preview.
    E_MOVIE_PREVIEW_MODE_NUM,           // Specify the number of movie preview mode.
} enumMoviePreviewState;

typedef enum
{
    E_TEXT_PREVIEW_NONE,                // need not to do text preview.
    E_TEXT_PREVIEW_TIMER_ENABLE,        // Begin count down.
    E_TEXT_PREVIEW_RUNNING,             // Initialize preview.
    E_TEXT_PREVIEW_MODE_NUM,            // Specify the number of text preview mode.
} enumTextPreviewState;

#if ENABLE_EMBEDDED_PHOTO_DISPLAY
typedef enum
{
    E_EMBEDDED_PHOTO_WAIT,               // embedded photo wait to display.
    E_EMBEDDED_PHOTO_RUNNING,            // embedded photo display process.
    E_EMBEDDED_PHOTO_DONE,               // embedded photo done.
    E_EMBEDDED_PHOTO_EXIT,               // embedded photo exit.
    E_EMBEDDED_PHOTO_MODE_NUM,           // Specify the number of embedded photo display mode.
}enumEmbeddedPhotoState;
#endif

typedef enum
{
    E_TEXT_CHARSET_DEFAULT = 0,          // use ascii & gbk as the same as default
    E_TEXT_CHARSET_GBK,                  // use ascii & gbk as the same as default
    E_TEXT_CHARSET_CP874,                // Thai Windows Code Page 874
    E_TEXT_CHARSET_CP1250,               // windows central european
    E_TEXT_CHARSET_CP1251,               // Cyrillic Windows Code Page 1251
    E_TEXT_CHARSET_CP1252,               // windows western european
    E_TEXT_CHARSET_CP1253,               // Greek Windows Code Page 1253
    E_TEXT_CHARSET_CP1254,               // windows turkey
    E_TEXT_CHARSET_CP1255,               // Hebrew Windows Code Page 1255
    E_TEXT_CHARSET_CP1256,               // Arabic Code Page 1256
    E_TEXT_CHARSET_CP1257,               // Latin 4 Code Page 1257
    E_TEXT_CHARSET_CP1258,               // Vietnamese  Code Page 1258
    E_TEXT_CHARSET_ISO_8859_05,         //Cyrillic (ISO)
    E_TEXT_CHARSET_ISO_8859_10,          //
    E_TEXT_CHARSET_CROATIAN_MAC,         // croatian mac
    E_TEXT_CHARSET_KOREAN,               // KOREAN KSC5601
} enumTextCharsetType;

typedef enum
{
    SUBTITLE_CHARSET_DEFAULT = 0,        // use ascii & gbk as the same as default
    SUBTITLE_CHARSET_GBK,                      // use ascii & gbk as the same as default
    SUBTITLE_CHARSET_CP874,                 // Thai Windows Code Page 874
    SUBTITLE_CHARSET_CP1250,                // windows central european
    SUBTITLE_CHARSET_CP1251,                // Cyrillic Windows Code Page 1251
    SUBTITLE_CHARSET_CP1252,                // windows western european
    SUBTITLE_CHARSET_CP1253,                // Greek Windows Code Page 1253
    SUBTITLE_CHARSET_CP1254,                // windows turkey
    SUBTITLE_CHARSET_CP1255,                // Hebrew Windows Code Page 1255
    SUBTITLE_CHARSET_CP1256,                // Arabic Code Page 1256
    SUBTITLE_CHARSET_CP1257,                // Latin 4 Code Page 1257
    SUBTITLE_CHARSET_CP1258,                // Vietnamese  Code Page 1258
    SUBTITLE_CHARSET_CROATIAN_MAC,  // croatian mac
    SUBTITLE_CHARSET_ISO_8859_05,   //Cyrillic(ISO)
    SUBTITLE_CHARSET_ISO_8859_10,  //
    SUBTITLE_CHARSET_KOREAN,                // KOREAN KSC5601
} enumSubtitleCharsetType;


#if ENABLE_DVD
// If this enum is changed, then dvd library need rebuild also.
typedef enum
{
    E_MPLAYER_DVD_CMD_ENTER,
    E_MPLAYER_DVD_CMD_KEYUP,
    E_MPLAYER_DVD_CMD_DOWN,
    E_MPLAYER_DVD_CMD_LEFT,
    E_MPLAYER_DVD_CMD_RIGHT,
    E_MPLAYER_DVD_CMD_NEXT,
    E_MPLAYER_DVD_CMD_PREV,
    E_MPLAYER_DVD_CMD_SUBTITLE,
    E_MPLAYER_DVD_CMD_LANGUAGE,
    E_MPLAYER_DVD_CMD_TITLE,
    E_MPLAYER_DVD_CMD_ROOT,
    E_MPLAYER_DVD_CMD_PLAY_PAUSE,
    E_MPLAYER_DVD_CMD_FF,
    E_MPLAYER_DVD_CMD_FB,
    E_MPLAYER_DVD_CMD_REPEATAB,
} enumMPlayerDVDCmdType;
#endif

typedef enum
{
    E_MPLAYER_LANGUAGE_CZECH,           // 0  CZE/CES
    E_MPLAYER_LANGUAGE_DANISH,          // 1
    E_MPLAYER_LANGUAGE_GERMAN,          // 2  GER/DEU
    E_MPLAYER_LANGUAGE_ENGLISH,         // 3
    E_MPLAYER_LANGUAGE_SPANISH,         // 4
    E_MPLAYER_LANGUAGE_GREEK,           // 5  GRE/ELL//??
    E_MPLAYER_LANGUAGE_FRENCH,          // 6  FRE/FRA
    E_MPLAYER_LANGUAGE_CROATIAN,        // 7  SCR/HRV
    E_MPLAYER_LANGUAGE_ITALIAN,         // 8
    E_MPLAYER_LANGUAGE_HUNGARIAN,       // 9
    E_MPLAYER_LANGUAGE_DUTCH,           //10  DUT/NLD
    E_MPLAYER_LANGUAGE_NORWEGIAN,       //11
    E_MPLAYER_LANGUAGE_POLISH,          //12
    E_MPLAYER_LANGUAGE_PORTUGUESE,      //13
    E_MPLAYER_LANGUAGE_RUSSIAN,         //14
    E_MPLAYER_LANGUAGE_ROMANIAN,        //15  ROM/RON
    E_MPLAYER_LANGUAGE_SLOVENIAN,       //16
    E_MPLAYER_LANGUAGE_SERBIAN,         //17
    E_MPLAYER_LANGUAGE_FINNISH,         //18
    E_MPLAYER_LANGUAGE_SWEDISH,         //19
    E_MPLAYER_LANGUAGE_BULGARIAN,       //20
    E_MPLAYER_LANGUAGE_GAELIC,          //21  GLA
    E_MPLAYER_LANGUAGE_WELSH,           //22 WEL/cym
    E_MPLAYER_LANGUAGE_IRISH,           //23 GLE
    E_MPLAYER_LANGUAGE_ARABIC,          //24
    E_MPLAYER_LANGUAGE_CATALAN,         //25
    E_MPLAYER_LANGUAGE_CHINESE,         //26
    E_MPLAYER_LANGUAGE_KOREAN,          //27
    E_MPLAYER_LANGUAGE_JAPAN,           //28
    E_MPLAYER_LANGUAGE_TURKISH,         //29
    E_MPLAYER_LANGUAGE_HEBREW,          //30
    E_MPLAYER_LANGUAGE_GALLEGAN,        //31
    E_MPLAYER_LANGUAGE_BASQUE,          //32
    E_MPLAYER_LANGUAGE_LUXEMBOURGISH,   //33
    E_MPLAYER_LANGUAGE_ICELANDIC,       //34
    E_MPLAYER_LANGUAGE_LATVIAN,         //35
    E_MPLAYER_LANGUAGE_ESTONIAN,        //36
    E_MPLAYER_LANGUAGE_LITHUANIAN,      //37
    E_MPLAYER_LANGUAGE_UKRAINIAN,       //38
    E_MPLAYER_LANGUAGE_BELARUSIAN,      //39
    E_MPLAYER_LANGUAGE_HINDI,           //40
    E_MPLAYER_LANGUAGE_KIRUNDI,         //41
    E_MPLAYER_LANGUAGE_MAORI,           //42
    E_MPLAYER_LANGUAGE_SLOVAK,          //43
    E_MPLAYER_LANGUAGE_VOLAPUK,         //44
    E_MPLAYER_LANGUAGE_MANDARIN,        //45
    E_MPLAYER_LANGUAGE_CANTONESE,       //46
    E_MPLAYER_LANGUAGE_SAMI,            //47
    E_MPLAYER_LANGUAGE_QAA,             //48
    E_MPLAYER_LANGUAGE_THAI,            //49
    E_MPLAYER_LANGUAGE_INDONESIAN,      //50
    E_MPLAYER_LANGUAGE_MALAY,           //51
    E_MPLAYER_LANGUAGE_VIETNAMESE,      //52
    E_MPLAYER_LANGUAGE_URDU,            //53
    E_MPLAYER_LANGUAGE_AFRIKAANS,       //54
    E_MPLAYER_LANGUAGE_ZULU,            //55
    E_MPLAYER_LANGUAGE_AMHARIC,         //56
    E_MPLAYER_LANGUAGE_YORUBA,          //57
    E_MPLAYER_LANGUAGE_HAUSA,           //58
    E_MPLAYER_LANGUAGE_XHOSA,           //59
    E_MPLAYER_LANGUAGE_SWAHILI,         //60
    E_MPLAYER_LANGUAGE_IGBO,            //61
    E_MPLAYER_LANGUAGE_NUM,
    E_MPLAYER_LANGUAGE_UNDEFINED,
} enumMPlayerLanguage;

typedef enum
{
    E_MPLAYER_FORCE_STOP_INIT,
    E_MPLAYER_FORCE_STOP_PLAY,
} EN_MPLAYER_FORCE_STOP;

typedef enum
{
    E_MPLAYER_CONTINUE_PLAYING,
    E_MPLAYER_USER_EXIT,
    E_MPLAYER_ERROR_EXIT,
} EN_MPLAYER_FORCE_STOP_RESULT;

typedef EN_MPLAYER_FORCE_STOP_RESULT (*PF_FORCE_STOP)(EN_MPLAYER_FORCE_STOP eType);

//*****************************************************************************
//              Data structure
//*****************************************************************************
/// Specify the device information.

#define PROBE_MPLAYER_INFO_LENGTH 128
#define PROBE_MPLAYER_INFO_YEAR_LENGTH 32

typedef struct
{
    U8 u8Title[PROBE_MPLAYER_INFO_LENGTH];
    U8 u8Artist[PROBE_MPLAYER_INFO_LENGTH];
    U8 u8Album[PROBE_MPLAYER_INFO_LENGTH];
    U8 u8Year[PROBE_MPLAYER_INFO_YEAR_LENGTH];
    U16 u16BitRate;
    U32 u32SampleRate;
    U32 u32Duration;
    U32 u32PicOffset;
    U32 u32PicSize;

} ST_MPLAYER_PROBE_INFO;



typedef struct
{
    enumMPlayerDeviceType eDeviceType;  /// Device type: USB host X or card reader X
    U8 u8DeviceAddr;                    /// Useless currently.
    U8 u8Lun;                           /// Specify the lun
} MPlayerDevice;

/// Specify the drive information.
typedef struct
{
    enumMPlayerDeviceType eDeviceType;  /// Device type: USB host X or card reader X
    U8 u8DeviceAddr;                    /// Useless currently.
    U8 u8Lun;                           /// Specify the lun
    U8 u8Partition;                     /// Specify the drive partition index
} MPlayerDrive;

/// Specify the device status information.
typedef struct
{
    enumMPlayerDeviceType eDeviceType;          /// Device type: USB host X or card reader X
    U8 u8DeviceAddr;                            /// Useless currently.
    U16 u16LunValid;                            /// Use 16-bit to specify which lun are valid
    U16 u16PartitionValid[MSD_USB_4_INDEX_END];  /// Use 16-bit to specify which partition is valid
} MPlayerDeviceStatus;


#define USE_DUMMY_ALIGNMENT_FOR_MPLAYFILEINFO 0

#if USE_DUMMY_ALIGNMENT_FOR_MPLAYFILEINFO
#define LONGFILENAME_SIZE_ALIGN (FILE_INFO_LONG_FILENAME_SIZE%4)
#define  LONGFILENAME_SIZE (LONGFILENAME_SIZE_ALIGN==0)? \
                                                   (FILE_INFO_LONG_FILENAME_SIZE): \
                                                   (FILE_INFO_LONG_FILENAME_SIZE+4-LONGFILENAME_SIZE_ALIGN )

#define ENUMFILEATRIBUTE_SIZE sizeof(enumFileAttribute)

#define LONGLONG_SIZE sizeof(LongLong)
#if (HIGH_SPEED_BROWSER)
#define FILEENTRY_SIZE sizeof(FileEntry)
#else
#define FILEENTRY_SIZE 0
#endif

#if ENABLE_MPLAYER_SORT
#define PHYINDEX_SIZE 2
#else
#define PHYINDEX_SIZE 0
#endif

#define BEFORE_DUMMY_PENDING_SIZE (LONGFILENAME_SIZE+ \
                                                                  4+ \
                                                                  ENUMFILEATRIBUTE_SIZE + \
                                                                  LONGLONG_SIZE+ \
                                                                  2+1+1+ \
                                                                  1+1+1+1 + \
                                                                  FILEENTRY_SIZE + \
                                                                  PHYINDEX_SIZE)


#define MPLAYERFILEINFO_ALIGNMENT_SIZE \
                   (BEFORE_DUMMY_PENDING_SIZE <=256)?(256-BEFORE_DUMMY_PENDING_SIZE): \
                   (BEFORE_DUMMY_PENDING_SIZE <=512)?(512-BEFORE_DUMMY_PENDING_SIZE): \
                   (BEFORE_DUMMY_PENDING_SIZE<=1024)?(1024-BEFORE_DUMMY_PENDING_SIZE): \
                   (BEFORE_DUMMY_PENDING_SIZE<=2048)?(2048-BEFORE_DUMMY_PENDING_SIZE): \
                   (BEFORE_DUMMY_PENDING_SIZE<=4096)?(4096-BEFORE_DUMMY_PENDING_SIZE): \
                   0
#endif

/// Specify the file information.
typedef struct
{
    enumFileAttribute eAttribute;                       /// File attributes
    LongLong u64FileSize;                               /// File size
    U16 u16Year;                                        /// Year
    U8 u8Month;                                         /// Month
    U8 u8Day;                                           /// Day
    U8 u8Hour;                                          /// Hour
    U8 u8Minute;                                        /// Minute
    U8 u8Second;                                        /// Second
    BOOLEAN bLongFileNameValid;                         /// Specify whether the file name is valid.
#if (HIGH_SPEED_BROWSER)
    FileEntry fileEntry;                                /// Specify the file entry.
#if (ENABLE_MPLAYER_SORT)
    U16 u16PhyIndex;                                    /// Keep physical order from file system view.
#endif
#endif
    U8 u8ExtFileName[3+1];                              /// Short extension file name
    U8 u8LongFileName[FILE_INFO_LONG_FILENAME_SIZE];    /// Long file name
#if USE_DUMMY_ALIGNMENT_FOR_MPLAYFILEINFO
    U8 u8dummy[MPLAYERFILEINFO_ALIGNMENT_SIZE];
#endif
} MPlayerFileInfo;

/// Specify the JPEG information
typedef struct
{
    U16 u16Width;                   /// JPEG width
    U16 u16Height;                  /// JPEG height
    U32 u32FileSize;                /// JPEG file size
    enumMPlayerJPGFlag eFlags;      /// JPEG attribute

    //Exif information
    enumMPlayerJPGOrient eOrientation;   /// JPEG orient
    BOOLEAN bHasDateTime;           /// Is there a date time with this photo file
    U32 u32Year;                    /// Date time, year
    U32 u32Month;                   /// Date time, month
    U32 u32Day;                     /// Date time, day
    U32 u32Hour;                    /// Date time, hour
    U32 u32Minute;                  /// Date time, minute
    U32 u32Second;                  /// Date time, second
    U32 u32ExifWidth;               /// Exif Width
    U32 u32ExifHeight;              /// Exif Height
    U8 au8CameraMaker[MPLAYER_EXIF_CAMERA_MAKER_SIZE];  /// Camera maker
    U8 au8CameraModel[MPLAYER_EXIF_CAMERA_MODEL_SIZE];  /// Camera model
    U32 u32FlashMode;                   /// Flash mode
    U32 u32ISOSpeed;                    /// ISO speed
    RATIONAL stExposureBias; /// Exposure bias
    RATIONAL stExposureTime; /// Exposure time
    RATIONAL stF_Stop;       /// F-Stop
} MPlayerPhotoInfo;

/// Specify the status when end a thumbnail.
typedef struct
{
    U16 u16FileIdx;                 /// Indicate the file index from the current page.
    BOOLEAN bOK;                    /// Specify if the thumbnail is shown correctly.
} MPlayerNotifyOneThumbnail;

#if (ENABLE_MPLAYER_VIDEO_CAPTURE)
typedef struct
{
    BOOLEAN bThumbnail;            /// TRUE to enable thumbnail
    BOOLEAN bHMirror;              /// TRUE to mirror the thumbnail in horizontal line
    BOOLEAN bVMirror;              /// TRUE to mirror the thumbnail in vertical line
    U32 u32BufferBaseAddr;         /// destination buffer base in bytes
    U16 u16Pitch ;                 /// destination pitch in bytes
    U16 u16Coordinate_X;           /// start x
    U16 u16Coordinate_Y;           /// start y
    U16 u16Width;                  /// destination width
    U16 u16Height;                 /// destination height
    MS_ColorFormat  format;        /// color format
} ST_VIDEO_CAPTURE_THUMB_BITBLT_INFO;

typedef struct
{
    ST_VIDEO_CAPTURE_THUMB_BITBLT_INFO ThumbBitBltInfo;    /// Video capture thumbnail info
    U16* pu16FileName;                                     /// file name in unicode
    U16* pu16CapturePath;                                  /// capture path in unicode, the last charater must be '\\' or '\0'
    U16 u16FileNameLen;                                    /// file name string length
    U16 u16CapturePathLen;                                 /// capture path string length

    U8 u8ConnectPort;                                      /// USB port
    U8 u8ConnectDrive;                                     /// USB connect target drive
    BOOLEAN bScreenFreeze;                                 /// screen freeze state

    BOOLEAN bLoadCoprocessor;                              /// TRUE for Load coprocessor before encoding and disable after encoding

    /// Callback function for path update
    /// pu16Path \b IN Specify the input path and output path.
    /// u16MaxPathLen \b Specify the max file name length (CAPTURE_MAX_FILENAME_BUFFER_SIZE/2)
    BOOLEAN (*pfnIsPathUpdate) (U16 *pu16Path, U16 u16MaxPathLen);

    /// Callback function for renaming file name if the file is existed
    /// pu16FileName \b IN Specify the input file name and output file name.
    /// u16MaxNameBufferLen \b Specify the max file name length (CAPTURE_MAX_FILENAME_BUFFER_SIZE/2)
    BOOLEAN (*pfnRenameFileIfFileExisted) (U16 *pu16FileName, U16 u16MaxNameBufferLen);

} ST_VIDEO_CAPTURE_SET_INFO;

typedef struct
{
    U8 u8Progress;                                         /// Encoding progress in percent (not implement yet)
} ST_VIDEO_CAPTURE_GET_INFO;
#endif

#if (ENABLE_MPLAYER_AUDIO_CAPTURE)
typedef struct
{
    U16* pu16FileName;                                     /// file name in unicode
    U16* pu16CapturePath;                                  /// capture path in unicode, the last charater must be '\\' or '\0'
    U16 u16FileNameLen;                                    /// file name string length
    U16 u16CapturePathLen;                                 /// capture path string length

    U8 u8ConnectPort;                                      /// USB port
    U8 u8ConnectDrive;                                     /// USB connect target drive

    /// Callback function for path update
    /// pu16Path \b IN Specify the input path and output path.
    /// u16MaxPathLen \b Specify the max file name length (CAPTURE_MAX_FILENAME_BUFFER_SIZE/2)
    BOOLEAN (*pfnIsPathUpdate) (U16 *pu16Path, U16 u16MaxPathLen);

    /// Callback function for renaming file name if the file is existed
    /// pu16FileName \b IN Specify the input file name and output file name.
    /// u16MaxNameBufferLen \b Specify the max file name length (CAPTURE_MAX_FILENAME_BUFFER_SIZE/2)
    BOOLEAN (*pfnRenameFileIfFileExisted) (U16 *pu16FileName, U16 u16MaxNameBufferLen);

} ST_AUDIO_CAPTURE_SET_INFO;

typedef struct
{
    U32 u32Duration;                                       /// in seconds
} ST_AUDIO_CAPTURE_GET_INFO;
#endif

#if ENABLE_LAST_MEMORY==1
#define ENABLE_LAST_MEMORY_DEBUG    0
//#define ENABLE_LAST_MEMORY_STORAGE_SAVE    1 // save to flash or eeprom for suddently power off
#define ENABLE_LAST_MEMORY_ENABLE_MUSIC    0

//#define LAST_MEMORY_FILENUMBER    1// 8// number of LastMemory file to be recorded
#define ENABLE_LAST_MEMORY_PLAYTIME_UPDATE    0//start timer to keep update current play time, if "STORAGE_SAVE==1", data will continue to save to storage
#define LAST_MEMORY_UPDATE_INTERVAL    2500 // ms
//#define LAST_MEMORY_MAX_FULL_NAME_LEN   32*7*2 // byte
#define LAST_MEMORY_ORDER_NONE  0xFFFF// 0
#define LAST_MEMORY_ORDER_MINIMUM  1
#define LAST_MEMORY_ORDER_MAXIMUM  LAST_MEMORY_FILENUMBER

#define ENABLE_LAST_MEMORY_PLAYLIST_PATH_POOL_STATIC    0
#if ENABLE_LAST_MEMORY_PLAYLIST_PATH_POOL_STATIC==1
#define LAST_MEMORY_PLAYLIST_PATH_LEN_TBL_LEN   256 //byte
#define LAST_MEMORY_PLAYLIST_PATH_POOL_LEN   8*1024 //byte
#else//use "MAPP_FILEBROWSER_CURRENT_DIR_NAME_CACHE_ADR"
#define LAST_MEMORY_PLAYLIST_PATH_LEN_TBL_LEN   256 //byte
#if ENABLE_LAST_MEMORY_ENABLE_MUSIC
#define LAST_MEMORY_PLAYLIST_PATH_POOL_LEN   ((MAPP_FILEBROWSER_CURRENT_DIR_NAME_CACHE_LEN-2*LAST_MEMORY_PLAYLIST_PATH_LEN_TBL_LEN)>>1)
#else
#define LAST_MEMORY_PLAYLIST_PATH_POOL_LEN   (MAPP_FILEBROWSER_CURRENT_DIR_NAME_CACHE_LEN-LAST_MEMORY_PLAYLIST_PATH_LEN_TBL_LEN)
#endif
#endif
#endif//#if ENABLE_LAST_MEMORY==1

#ifdef MAPP_MPLAYER_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

//*****************************************************************************
//              Global variables
//*****************************************************************************
INTERFACE BOOLEAN g_bPlayPrev;
//*****************************************************************************
//              Function prototypes
//*****************************************************************************
// Command Interface
INTERFACE enumMPlayerRet MApp_MPlayer_InitializeKernel(void);
INTERFACE enumMPlayerRet MApp_MPlayer_InitializeAllDevices(void);
INTERFACE enumMPlayerRet MApp_MPlayer_ExitMediaPlayer(void);
INTERFACE enumMPlayerRet MApp_MPlayer_DisconnectAllDevices(void);
//INTERFACE enumMPlayerRet MApp_MPlayer_DisconnectOneDevice(MPlayerDevice *pDeviceInfo);
INTERFACE enumMPlayerRet MApp_MPlayer_ConnectDrive(U16 u16DriveIdx);
#ifdef ENABLE_PTP
INTERFACE enumMPlayerRet MApp_MPlayer_PTP_ConnectDrive();
#endif
INTERFACE enumMPlayerRet MApp_MPlayer_SetFileSelected(enumMPlayerFileIndexBegin eBegin, U16 u16FileIdx);
INTERFACE enumMPlayerRet MApp_MPlayer_SetFileUnselected(enumMPlayerFileIndexBegin eBegin, U16 u16FileIdx);
INTERFACE enumMPlayerRet MApp_MPlayer_SetCurrentFile(enumMPlayerFileIndexBegin eBegin, U16 u16FileIdx);
INTERFACE enumMPlayerRet MApp_MPlayer_SetCopyFile(enumMPlayerFileIndexBegin eBegin, U16 u16FileIdx);
INTERFACE enumMPlayerRet MApp_MPlayer_BeginPasteFile(U8 *pFileName);
INTERFACE enumMPlayerRet MApp_MPlayer_DeleteFile(enumMPlayerFileIndexBegin eBegin, U16 u16FileIdx);
INTERFACE enumMPlayerRet MApp_MPlayer_BeginDeleteSelectedFiles(void);
INTERFACE BOOLEAN MApp_MPlayer_StopDelete(void);
INTERFACE enumMPlayerRet MApp_MPlayer_RenameFile(enumMPlayerFileIndexBegin eBegin, U16 u16FileIdx, U8 *pFileName);
INTERFACE enumMPlayerRet MApp_MPlayer_EnterDirectory(enumMPlayerFileIndexBegin eBegin, U16 u16Idx);
INTERFACE enumMPlayerRet MApp_MPlayer_NextPage(void);
INTERFACE enumMPlayerRet MApp_MPlayer_PrevPage(void);
INTERFACE enumMPlayerRet MApp_MPlayer_SetCurrentPageIndex(U16 u16PageIdx);
INTERFACE enumMPlayerRet MApp_MPlayer_PhotoBeginPreview(void);
INTERFACE enumMPlayerRet MApp_MPlayer_MusicStopPreview(void);
INTERFACE enumMPlayerRet MApp_MPlayer_MovieBeginPreview(void);
INTERFACE enumMPlayerRet MApp_MPlayer_TextBeginPreview(void);
INTERFACE enumMPlayerRet MApp_MPlayer_BeginPreview(void);
INTERFACE enumMPlayerRet MApp_MPlayer_PhotoStopPreview(void);
INTERFACE enumMPlayerRet MApp_MPlayer_MovieStopPreview(void);
INTERFACE enumMPlayerRet MApp_MPlayer_TextStopPreview(void);
INTERFACE void MApp_MPlayer_ResetPreviewTimer(void);

#if ENABLE_EMBEDDED_PHOTO_DISPLAY
INTERFACE enumMPlayerRet MApp_MPlayer_ClearEmbeddedPhoto(void);
INTERFACE enumMPlayerRet MApp_MPlayer_StopEmbeddedPhoto(void);
INTERFACE enumMPlayerRet MApp_MPlayer_StopEmbeddedPhotoDecode(void);
INTERFACE enumMPlayerRet MApp_MPlayer_ResumeEmbeddedPhoto(void);
#endif

INTERFACE enumMPlayerRet MApp_MPlayer_StopPreview(void);
INTERFACE enumMPlayerRet MApp_MPlayer_EnterThumbnailMode(GOP_GwinFBAttr *pFBAttr);
INTERFACE enumMPlayerRet MApp_MPlayer_LeaveThumbnailMode(void);
INTERFACE enumMPlayerRet MApp_MPlayer_BeginThumbnail(void);
INTERFACE enumMPlayerRet MApp_MPlayer_StopThumbnail(void);
INTERFACE enumMPlayerRet MApp_MPlayer_EnableSubtitle(void);
INTERFACE enumMPlayerRet MApp_MPlayer_DisableSubtitle(void);
INTERFACE enumMPlayerRet MApp_MPlayer_ShowSubtitle(BOOLEAN bShow);
INTERFACE enumMPlayerRet MApp_MPlayer_EnableLRCLyric(void);
INTERFACE enumMPlayerRet MApp_MPlayer_DisableLRCLyric(void);
INTERFACE enumMPlayerRet MApp_MPlayer_InitRepeatMode(enumMPlayerRepeatMode eMode);
INTERFACE enumMPlayerRet MApp_MPlayer_SetRepeatMode(enumMPlayerRepeatMode eMode);
INTERFACE enumMPlayerRet MApp_MPlayer_SetRepeatModeByMPlayerType(enumMPlayerMediaType eType, enumMPlayerRepeatMode eMode);
#if RANDOM_PLAY
INTERFACE enumMPlayerRet MApp_MPlayer_InitRandomMode(enumMPlayerRandomMode eMode);
INTERFACE enumMPlayerRet MApp_MPlayer_SetRandomMode(enumMPlayerRandomMode eMode);
INTERFACE enumMPlayerRet MApp_MPlayer_SetRandomModeByMPlayerType(enumMPlayerMediaType eType, enumMPlayerRandomMode eMode);
#endif
INTERFACE enumMPlayerRet MApp_MPlayer_SetPlayMode(enumMPlayerPlayMode ePlayMode);
INTERFACE enumMPlayerRet MApp_MPlayer_SetCurrentMediaType(enumMPlayerMediaType eType, BOOLEAN bReset);
INTERFACE enumMPlayerRet MApp_MPlayer_EnableNotify(enumMPlayerNotifyType eNotify, BOOLEAN bEnable);

#if (ENABLE_MPLAYER_VIDEO_CAPTURE)
INTERFACE enumCaptureRet MApp_MPlayer_CaptureVideoBegin(ST_VIDEO_CAPTURE_SET_INFO *pCaptureVideoinfo);
INTERFACE enumCaptureRet MApp_MPlayer_CaptureVideoTask(void);
INTERFACE enumCaptureRet MApp_MPlayer_CaptureVideoStop(void);
INTERFACE BOOLEAN MApp_MPlayer_IsCapturingVideo(void);
INTERFACE BOOLEAN MApp_MPlayer_GetVideoCaptureInfo(ST_VIDEO_CAPTURE_GET_INFO* pVideoCaptureInfo);
#endif
#if (ENABLE_MPLAYER_AUDIO_CAPTURE)
INTERFACE enumCaptureRet MApp_MPlayer_CaptureAudioBegin(ST_AUDIO_CAPTURE_SET_INFO *pCaptureAudioinfo);
INTERFACE enumCaptureRet MApp_MPlayer_CaptureAudioTask(void);
INTERFACE enumCaptureRet MApp_MPlayer_CaptureAudioRead(void);
INTERFACE enumCaptureRet MApp_MPlayer_CaptureAudioStop(void);
INTERFACE BOOLEAN MApp_MPlayer_IsCapturingAudio(void);
INTERFACE BOOLEAN MApp_MPlayer_GetAudioCaptureInfo(ST_AUDIO_CAPTURE_GET_INFO* pAudioCaptureInfo);
#endif

#if 0
INTERFACE enumMPlayerRet MApp_MPlayer_CaptureVideo(U8 *pFileName, GOP_GwinFBAttr *pFBAttr);
#endif
INTERFACE enumMPlayerRet MApp_MPlayer_GenCaptureFileName(U8 *pFileName, U16 u16FileNameLen);
INTERFACE enumMPlayerRet MApp_MPlayer_SetPhotoSlideShowDelayTime(U16 u16DelayTime);
INTERFACE enumMPlayerRet MApp_MPlayer_SetPlayerErrorDelayTime(enumMPlayerMediaType eType, U16 u16DelayTime);
INTERFACE enumMPlayerRet MApp_MPlayer_ResetSlideStartTime(void);
INTERFACE enumMPlayerRet MApp_MPlayer_StopPlayerErrorMsgPending(void);
INTERFACE enumMPlayerRet MApp_MPlayer_Play(void);
INTERFACE void MApp_MPlayer_SetMoviePreviewWindow(U16 u16X, U16 u16Y, U16 u16Width, U16 u16Height,EN_ASPECT_RATIO_TYPE eAspectRatioType);
INTERFACE enumMPlayerRet MApp_MPlayer_PlayMusic(void);
INTERFACE enumMPlayerRet MApp_MPlayer_ResumeMusic(void);
INTERFACE enumMPlayerRet MApp_MPlayer_PlayNextFile(void);
INTERFACE enumMPlayerRet MApp_MPlayer_PlayPrevFile(void);
INTERFACE enumMPlayerRet MApp_MPlayer_PlayOneMediaFile(U8 *pFullPathName);
INTERFACE enumMPlayerRet MApp_MPlayer_Stop(void);
INTERFACE enumMPlayerRet MApp_MPlayer_StopMusic(void);
INTERFACE enumMPlayerRet MApp_MPlayer_PhotoZoom(enumMPlayerZoom eZoom);
INTERFACE enumMPlayerRet MApp_MPlayer_MovieZoom(enumMPlayerZoom eZoom);
INTERFACE enumMPlayerRet MApp_MPlayer_Zoom(enumMPlayerZoom eZoom);
INTERFACE enumMPlayerRet MApp_MPlayer_PhotoMove(enumMPlayerMoveDirection eDirection, U16 u16Offset);
INTERFACE enumMPlayerRet MApp_MPlayer_MovieMove(enumMPlayerMoveDirection eDirection, U16 u16Offset);
INTERFACE enumMPlayerRet MApp_MPlayer_Move(enumMPlayerMoveDirection eDirection, U16 u16Offset);
INTERFACE enumMPlayerRet MApp_MPlayer_MovieChangePlayMode(enumMPlayerMoviePlayMode ePlayMode);
INTERFACE enumMPlayerRet MApp_MPlayer_MovieSetRepeatAB(enumMPlayerMovieRepeatAB enAction, U32 u32RepeatTime);
INTERFACE enumMPlayerRet MApp_MPlayer_MovieChangeNextProgram(BOOLEAN bPlus);
INTERFACE enumMPlayerRet MApp_MPlayer_MovieChangeNextAudio(void);
INTERFACE enumMPlayerRet MApp_MPlayer_MovieChangeProgram(U8 u8ProgramIdx);
INTERFACE enumMPlayerRet MApp_MPlayer_MovieChangeAudioTrack(U8 u8TrackId);
INTERFACE enumMPlayerRet MApp_MPlayer_MovieChangeSubtitleTrack(U8 u8TrackId);
#if (ENABLE_DIVX_PLUS == 1)
INTERFACE enumMPlayerRet MApp_MPlayer_MovieChangeTitle(U8 u8TitleId);
INTERFACE enumMPlayerRet MApp_MPlayer_MovieChangeEdition(U8 u8EditionId);
INTERFACE enumMPlayerRet MApp_MPlayer_MovieChangeChapter(U8 u8ChapterId);
INTERFACE enumMPlayerRet MApp_MPlayer_MovieChangeAutoGenChapter(U8 u8ChapterId);
#endif
INTERFACE enumMPlayerRet MApp_MPlayer_PhotoChangePlayMode(enumMPlayerPhotoPlayMode ePlayMode);
INTERFACE enumMPlayerRet MApp_MPlayer_PhotoRotate(enumMPlayerPhotoRotate eRotate);
INTERFACE enumMPlayerRet MApp_MPlayer_MusicChangePlayMode(enumMPlayerMusicPlayMode ePlayMode);
INTERFACE enumMPlayerRet MApp_MPlayer_TextNextPage(void);
INTERFACE enumMPlayerRet MApp_MPlayer_TextPrevPage(void);
INTERFACE enumMPlayerRet MApp_MPlayer_TextStop(void);
INTERFACE enumMPlayerRet MApp_MPlayer_CaptureLogo(void);
INTERFACE enumMPlayerRet MApp_MPlayer_CaptureLogoByAddr(U32 u32SrcAddr, U32 u32Pitch, U32 u32Width, U32 u32Height, GFX_Buffer_Format SrcFormat);
INTERFACE enumMPlayerRet MApp_MPlayer_StartCaptureBootUpMusic(void);
INTERFACE enumMPlayerRet MApp_MPlayer_EndCaptureBootUpMusic(void);
INTERFACE enumMPlayerRet MApp_MPlayer_GotoMenuState(void);
INTERFACE enumMPlayerRet MApp_MPlayer_ScaleVideo(void);
INTERFACE enumMPlayerRet MApp_MPlayer_SetPlayPosition(U32 u32TimeInMS);
INTERFACE enumMPlayerRet MApp_MPlayer_SetFileDecodedFail(U16 u16FileIdx, U8 bFailed, enumMPlayerMediaType MediaType, enumMPlayerPlayMode PlayMode);
INTERFACE BOOLEAN MApp_MPlayer_GetFileDecodedFail(U16 u16FileIdx, enumMPlayerMediaType MediaType, enumMPlayerPlayMode PlayMode);

// Query Interface
INTERFACE enumMPlayerRet MApp_MPlayer_QueryFileInfo(enumMPlayerFileIndexBegin eBegin, U16 u16FileIdx, MPlayerFileInfo *pInfo);
INTERFACE enumMPlayerRet MApp_MPlayer_QueryDeviceConnectionStatus(MPlayerDeviceStatus **pStatus);
INTERFACE enumMPlayerRet MApp_MPlayer_QueryDriveConnectionStatus(U32 *pu32DriveStatus);
#ifdef MEDIA_PLAYER_HIGHLIGHT_CHANGE
INTERFACE void MApp_MPlayer_SetNextPlayListFileIndex(void);
INTERFACE void MApp_MPlayer_SetPrevPlayListFileIndex(void);
INTERFACE U16 MApp_MPlayer_QueryCurrentPlayingFileIndex(void);
INTERFACE U8 MApp_MPlayer_QueryCurrentPlayingDriveIndex(void);
INTERFACE void MApp_MPlayer_SetCurrentPlayingFileIndex(U16 u16FileIndex);
INTERFACE U16 MApp_MPlayer_QueryCurrentPlayingListFileSequence(void);
INTERFACE U16 MApp_MPlayer_QueryCurrentPlayingListFileIndex(void);
INTERFACE U16  MApp_MPlayer_QueryCurrentPlayingList(void);
INTERFACE U16  MApp_MPlayer_QueryBGMPlayingList(void);
INTERFACE void MApp_MPlayer_SetCurrentPlayingList(U16 u16PLIndex);
INTERFACE BOOLEAN MApp_MPlayer_IsPathDifferent(U16 u16PLIndex);
INTERFACE BOOLEAN MApp_MPlayer_Change2TargetPath(U16 u16PLIndex);
INTERFACE BOOLEAN MApp_MPlayer_Change2TargetDirectory(U16 u16DriveIdx, U16 *dir, U16 depth);
#endif  // MEDIA_PLAYER_HIGHLIGHT_CHANGE
INTERFACE U16 MApp_MPlayer_QueryCurrentPageIndex(void);
EN_FILE_SYSTEM_TYPE MApp_MPlayer_QueryCurrentFileSystemType(void);
INTERFACE EN_FILE_SYSTEM_FORMAT MApp_MPlayer_QueryFileSystemFormatByDriveIndex(U8 u8DriveIndex);
INTERFACE U16 MApp_MPlayer_QueryCurrentFileIndex(enumMPlayerFileIndexBegin eBegin);
INTERFACE U16 MApp_MPlayer_QueryTotalPages(void);
INTERFACE enumMPlayerRet MApp_MPlayer_IsCurrentExternalSubtitleAvailable(void);
INTERFACE enumMPlayerRet MApp_MPlayer_IsCurrentLRCLyricAvailable(void);
INTERFACE enumMPlayerMediaType MApp_MPlayer_QueryCurrentMediaType(void);
INTERFACE enumMPlayerPlayMode MApp_MPlayer_QueryPlayMode(void);
INTERFACE enumMPlayerRet MApp_MPlayer_QueryPhotoInfo(MPlayerPhotoInfo *pInfo);
INTERFACE enumMPlayerMediaSubType MApp_MPlayer_QueryCurrentFileMediaSubType(void);
INTERFACE enumMPlayerMediaSubType MApp_MPlayer_QueryCurrentMediaSubType(void);
INTERFACE enumMPlayerMovieVideoType MApp_MPlayer_QueryCurrentMovieVideoType(void);
INTERFACE enumMPlayerMovieAudioType MApp_MPlayer_QueryCurrentMovieAudioType(void);
INTERFACE U16 MApp_MPlayer_QueryPasteFileStatus(void);
INTERFACE U16 MApp_MPlayer_QueryDeleteFileStatus(void);
INTERFACE enumMPlayerMoviePlayMode MApp_MPlayer_QueryMoviePlayMode(void);
#if ENABLE_DIVX_PLUS
INTERFACE void MApp_MPlayer_SetMoviePlayMode(enumMPlayerMoviePlayMode eMoviePlayMode);
#endif
INTERFACE enumMPlayerPhotoPlayMode MApp_MPlayer_QueryPhotoPlayMode(void);
INTERFACE enumMPlayerMusicPlayMode MApp_MPlayer_QueryMusicPlayMode(void);
INTERFACE U16 MApp_MPlayer_QueryMovieProgramNum(void);
INTERFACE U16 MApp_MPlayer_QueryMovieAudioChannelNum(void);
#if (ENABLE_DIVX_PLUS == 1)
INTERFACE U16 MApp_MPlayer_QueryMovieTitleNum(void);
INTERFACE U16 MApp_MPlayer_QueryMovieEditionNum(void);
INTERFACE U16 MApp_MPlayer_QueryMovieChapterNum(void);
#endif
INTERFACE U16 MApp_MPlayer_QueryMovieSubtitleNum(void);
INTERFACE U16 MApp_MPlayer_QueryMovieCurProgramIdx(void);
INTERFACE U16 MApp_MPlayer_QueryMovieCurAudioTrackIdx(void);
INTERFACE U16 MApp_MPlayer_QueryMovieCurSubtitleTrackIdx(void);
INTERFACE enumMPlayerRet MApp_MPlayer_QueryCurrentDrive(MPlayerDrive *pDriveInfo);
INTERFACE U16 MApp_MPlayer_QueryCurrentDriveIndex(void);
INTERFACE U16 MApp_MPlayer_QueryTotalDeviceNum(void);
INTERFACE enumMPlayerRet MApp_MPlayer_QueryDeviceInfo(U16 u16DeviceIdx, MPlayerDevice *pDeviceInfo);
INTERFACE U16 MApp_MPlayer_QueryTotalDriveNum(void);
INTERFACE U16 MApp_MPlayer_QueryTotalFileNum(void);
#if PLAYLIST_BGM
INTERFACE U16 MApp_MPlayer_QueryTotalMusicFileNum(void);
#endif
INTERFACE enumMPlayerRet MApp_MPlayer_QueryDriveInfo(U16 u16DriveIdx, MPlayerDrive *pDriveInfo);
INTERFACE U8 MApp_MPlayer_QueryPartitionIdxInDrive(U16 u16PartitionIdx, MPlayerDrive *pDriveInfo);
INTERFACE enumMPlayerZoom MApp_MPlayer_QueryZoomScale(void);
INTERFACE enumMPlayerPhotoRotate MApp_MPlayer_QueryPhotoRotateMode(void);
INTERFACE enumMPlayerRepeatMode MApp_MPlayer_QueryRepeatMode(void);
INTERFACE enumMPlayerRepeatMode MApp_MPlayer_QueryRepeatModeByMPlayerType(enumMPlayerMediaType eType);
#if RANDOM_PLAY
INTERFACE enumMPlayerRandomMode MApp_MPlayer_QueryRandomMode(void);
INTERFACE enumMPlayerRandomMode MApp_MPlayer_QueryRandomModeByMPlayerType(enumMPlayerMediaType eType);
#endif
INTERFACE U8 *MApp_MPlayer_QueryMusicInfo(EN_MP3_INFO eInfo,U8 *u8Length);
INTERFACE U16 MApp_MPlayer_QuerySelectedFileNum(enumMPlayerMediaType eType);
INTERFACE BOOLEAN MApp_MPlayer_IsMusicRecording(void);
INTERFACE BOOLEAN MApp_MPlayer_IsMediaFileInPlaying(void);
INTERFACE BOOLEAN MApp_MPlayer_IsPlugInAppPlaying(void);
INTERFACE BOOLEAN MApp_MPlayer_IsMusicPlaying(void);
INTERFACE void MApp_MPlayer_BGM_Bitstream_Handle(void);
INTERFACE BOOLEAN MApp_MPlayer_IsOnlyMusicPlaying(void);
INTERFACE U16 MApp_MPlayer_QueryDirectoryDepth(void);
INTERFACE U16 MApp_MPlayer_QueryDirectoryNumber(void);
#if PLAYLIST_BGM
INTERFACE U16 MApp_MPlayer_QueryMusicDirectoryNumber(void);
#endif
#if (ENABLE_MPLAYER_MUSIC)
INTERFACE U32 MApp_MPlayer_QueryMusicFilePlayTime(void);
INTERFACE U32 MApp_MPlayer_QueryMusicFileCurrentTime(void);
INTERFACE void MApp_MPlayer_QueryCurrentLyric(U8 *pu8Lyric);
#endif
#if (ENABLE_MPLAYER_PHOTO)
INTERFACE BOOLEAN MApp_MPlayer_IsThumbnailMode(void);
INTERFACE enumMPlayerPhotoDecoderState MApp_MPlayer_QueryPhotoDecoderState(void);
INTERFACE BOOLEAN MApp_MPlayer_IsPhotoPlaying(void);
#endif  // #if (ENABLE_MPLAYER_PHOTO)

INTERFACE void MApp_MPlayer_SetSubtitleCharsetType(enumSubtitleCharsetType enType);
INTERFACE enumSubtitleCharsetType MApp_MPlayer_GetSubtitleCharsetType(void);

INTERFACE void MApp_MPlayer_SetTextCharsetType(enumTextCharsetType enType);
INTERFACE enumTextCharsetType MApp_MPlayer_GetTextCharsetType(void);

#if 0//ndef ZUI
INTERFACE EN_RET MApp_MPlayer_Main(void);
#endif
INTERFACE void MApp_MPlayer_Task(void);
INTERFACE enumMPlayerRet MApp_MPlayer_GetFullPath(U16 *pu16Buffer, U16 u16Length);

#if ENABLE_MPLAYER_MOVIE
INTERFACE BOOLEAN MApp_MPlayer_IsMovieIndexTableExist(void);
INTERFACE BOOLEAN MApp_MPlayer_IsMoviePlaying(void);
INTERFACE void MApp_MPlayer_PlayMovieOnDemand(void);
INTERFACE void MApp_MPlayer_QueryCurrentSubtitle(U8 *pu8Subtitle, U32 u32BufSize);
#endif  // #if ENABLE_MPLAYER_MOVIE
INTERFACE void MApp_MPlayer_Standby(void);
INTERFACE BOOLEAN MApp_MPlayer_IsFilenameExistInCurrentDirectory(U16* pString,U8 charLen);
INTERFACE BOOLEAN MApp_MPlayer_IsCopyFileExist(void);
INTERFACE BOOLEAN MApp_MPlayer_IsCopying(void);
INTERFACE BOOLEAN MApp_MPlayer_IsDeleting(void);
INTERFACE U32 MApp_MPlayer_QueryUsbDiskTotalSizeInKB(U8 u8DriveIndex);
INTERFACE U32 MApp_MPlayer_QueryUsbDiskUnusedSizeInKB(U8 u8DriveIndex);
INTERFACE U8 MApp_MPlayer_QueryPreviewState(enumMPlayerMediaType eType);
INTERFACE void MApp_MPlayer_GotoRootDirEntry(void);
INTERFACE void MApp_MPlayer_GotoCurrentDirEntry(void);
INTERFACE enumMPlayerDeviceType MApp_MPlayer_QueryCurrentDeviceIndex(void);
INTERFACE BOOLEAN MApp_MPlayer_QueryCurrentDeviceIsConnected(void);
INTERFACE U16 MApp_MPlayer_QueryPlayListFileNum(enumMPlayerMediaType eType);
INTERFACE enumMPlayerRet MApp_MPlayer_RemoveFileFromPlayList(enumMPlayerMediaType eType, U16 u16Index, BOOLEAN bDeleteFile);
INTERFACE enumMPlayerRet MApp_MPlayer_QueryFileNameInPlayList(enumMPlayerMediaType eType, U16 u16Index, U8 *pu8FileName, U16 u16BufLen);
INTERFACE enumMPlayerRet MApp_MPlayer_QueryCurrentPlayingFileName(U8 *pu8LongFilename);
INTERFACE BOOLEAN MApp_MPlayer_QueryLongFilenameByPlayingIdx(U16 u16PlayingIdx, U8 *pFilename, U8 u8Len);
INTERFACE BOOLEAN MApp_MPlayer_IsPlayListChanged(void);
INTERFACE void MApp_MPlayer_PlayListIsSet(void);
#if ENABLE_MPLAYER_MUSIC
INTERFACE BOOLEAN MApp_MPlayer_MusicPlayList_PlayByIdx(U16 u16Idx);
#endif
INTERFACE U16 MApp_MPlayer_QueryFileIdxByPlayingIdx(U16 u16PlayingIdx);
#if PLAYLIST_BGM
INTERFACE BOOLEAN MApp_MPlayer_BGM_Playlist_Init(void);
INTERFACE BOOLEAN MApp_MPlayer_BGM_Playlist_DeInit(void);
#endif
#if 1//def ZUI
INTERFACE enumMPlayerRet MApp_MPlayer_DrawThumbnailByIdx(U8 u8Idx);
#endif

INTERFACE void MApp_MPlayer_StopCopy(void);

#if ENABLE_MPLAYER_PLUGIN
INTERFACE BOOLEAN MApp_MPlayer_SearchPlugInBinFileEntry(U8 *pFilename);
INTERFACE FileEntry * MApp_MPlayer_GetPlugInBinFileEntry(void);
#endif //#if ENABLE_MPLAYER_PLUGIN

INTERFACE void MApp_MPlayer_PlayList_CleanUp(void);
INTERFACE void MApp_MPlayer_SetFileNum(U16 bufnum, U16 num);
INTERFACE void MApp_MPlayer_ReSetSelected(U16 DCnt, U16 FTCnt);
INTERFACE void MApp_MPlayer_ReSetCurIdx(void);

INTERFACE void MApp_MPlayer_ReSetThumbnailFileIdx(void);
INTERFACE enumMPlayerRet _MApp_MPlayer_GetMusicFileInfo(U16 u16Idx, MPlayerFileInfo *pInfo);  //chaos
INTERFACE U16 MAPP_MPlayer_GetMusicTotalFileNum(void);
INTERFACE void _MApp_MPlayer_StoreMusicFileInCurDirectory(void);
INTERFACE void MApp_MPlayer_CoProcessorMsg(BOOL bEnable);

#if ENABLE_DVD
INTERFACE void MApp_MPlayer_DVD_StartPlay(void);
INTERFACE U8 MApp_MPlayer_DVD_Command(enumMPlayerDVDCmdType cmd);
#endif
INTERFACE void MApp_MPlayer_SetZUIFbAttr(GOP_GwinFBAttr FbAttr);
#if ENABLE_DRM
INTERFACE void MApp_MPlayer_PlayDRMFile(BOOLEAN bPlayDRM);
#endif

INTERFACE BOOLEAN MApp_MPlayer_GetPlayListFileInfo(U16 u16PlayingIdx, MPlayerFileInfo *pInfo);
#if (EN_DMP_SEARCH_ALL || EN_DMP_SEARCH_FAV)
INTERFACE BOOLEAN MApp_MPlayer_LoadPlayList2FileBuffer(enumMPlayerMediaType eMediaType, BOOLEAN bIsNeedDot);
#endif
#if EN_DMP_SEARCH_FAV
BOOLEAN MApp_MPlayer_SavePlayListToDisk(enumMPlayerMediaType eMediaType);
BOOLEAN MApp_MPlayer_LoadPlayListFromDisk(enumMPlayerMediaType eMediaType);
#endif
#if EN_DMP_SEARCH_ALL
INTERFACE void MApp_MPlayer_GetAllFilesInCurDrive(void);
INTERFACE void MApp_MPlayer_SetSearchAllModeTotalFiles(void);
#endif
#if ENABLE_MPLAYER_MIXED
INTERFACE void MApp_MPlayer_SetMediaTypeByFileExtName(MPlayerFileInfo *pFileInfo);
INTERFACE enumMPlayerMediaType MApp_MPlayer_QueryMediaTypeByFileExtName(MPlayerFileInfo *pFileInfo);
INTERFACE U32 MApp_MPlayer_QueryFileListIndex(enumMPlayerMediaType eType,U16 u16PlayingIdx);
INTERFACE U32 MApp_MPlayer_QueryPlayListIndex(enumMPlayerMediaType eType, U32 u32FileListIndex);
#endif
#if ENABLE_LAST_MEMORY==1
extern U32 m_u32LastMemoryCurIdx;
extern U8 m_u8LastMemoryCheck;
extern U8 m_u8LastMemorySearchHit;

INTERFACE U8 MApp_MPlayer_LastMemory_Info_Get(U16 index, stLastMemoryInfo** ppLastMemInfo);
INTERFACE U8 MApp_MPlayer_LastMemory_Info_Save(U16 index, stLastMemoryInfo* pLastMemInfo);
INTERFACE U8 MApp_MPlayer_LastMemory_Info_Update(U16 InfoIndex, U8 enable, stLastMemoryAttribute stLastMemAttr);
INTERFACE U8 MApp_MPlayer_LastMemory_FileMatch_Entry(LastMemoryFileEntry* pFileEntry_db, FileEntry* pFileEntry_cur);
INTERFACE U8 MApp_MPlayer_LastMemory_OrderTbl_Get(U16** buf);
INTERFACE U8 MApp_MPlayer_LastMemory_OrderTbl_Save(U16* buf);
INTERFACE U8 MApp_MPlayer_LastMemory_OrderTbl_Rearrange(U8 del_add, U16 IndexToModify, U16* buf);
INTERFACE U8 MApp_MPlayer_LastMemory_OrderTbl_Update(U8 mode, U16 Index_Del_Touch, U16* Index_Add);
INTERFACE U8 MApp_MPlayer_LastMemory_Search(FileEntry* pFileEntry);
INTERFACE U8 MApp_MPlayer_LastMemory_SetResumePlayAttribute(U8 clear);
INTERFACE U8 MApp_MPlayer_LastMemory_GetResumePos(U32* pTimeMs, U32* pPosL, U32* pPosH);
INTERFACE BOOLEAN MApp_MPlayer_LastMemory_GetResumePlayInfo(stLastMemoryInfo* pstLastMemoryInfo);
#if(ENABLE_LAST_MEMORY_STORAGE_SAVE==1)
U8 MApp_MPlayer_LastMemory_Storage_Read(void);
U8 MApp_MPlayer_LastMemory_Storage_Write(void);
#endif
INTERFACE void MApp_MPlayer_LastMemory_GetCurPlayFileFullpath(U16 *fullpathbuf, U16 fullpathbuflen);
INTERFACE U16 * MApp_StrCpy_16(U16 *pTarBuf, U16 *pSrcBuf, U16 TarLen);
INTERFACE U16 * MApp_StrCat_16(U16 *pTarBuf, U16 *pSrcBuf, U16 TarLen);
INTERFACE void MApp_Printf_n_16(U16 *str, U16 n);
INTERFACE void MApp_Printf_16(U16 *str);
#endif//#if ENABLE_LAST_MEMORY==1
#if FILE_SYSTEM_GET_VOLUME_LABEL_ENABLE
INTERFACE U8 MApp_MPlayer_GetVolumName(U8 u8DriveID,U8* pVolumStrBuf, U8 VolumStrLen);
#endif

#if SUPPORT_ONE_FILE_HANDLE_APP_BUT_DEMUX_USE_2_FILE_HANDLE
INTERFACE BOOL MApp_MPlayer_SetStreamMode(BOOL bStreamMode);
#endif

#if ENABLE_MPLAYER_SORT_EX
INTERFACE void MApp_MPlayer_ReSortFileBrowser(enumMPlayerFileSortMode eSortMode, enumMPlayerFileSortSubMode eOrderMode);
INTERFACE enumMPlayerFileSortMode MApp_MPlayer_QueryCurrentFileSortingMode(void);
INTERFACE enumMPlayerFileSortSubMode MApp_MPlayer_QueryCurrentFileSortingOrderMode(void);
#endif //ENABLE_MPLAYER_SORT_EX

#if ENABLE_PROBE_MOVIE_HEADER
INTERFACE BOOLEAN MApp_MPlayer_ProbeMovieHeaderOnly(enumMPlayerFileIndexBegin eBegin, U16 u16FileIdx);
#endif

INTERFACE BOOLEAN MApp_MPlayer_QueryDirectoryNode(U16 *ptr , U16 DirDepth);
INTERFACE U32 MApp_MPlayer_QueryPlayerErrorDelayTime(enumMPlayerMediaType eType);
INTERFACE BOOLEAN MApp_MPlayer_SetVideoSyncDelayMsTime(U32 u32VideoSyncDelayMsTime);
INTERFACE U32 MApp_MPlayer_GetVideoSyncDelayMsTime(void);

INTERFACE BOOLEAN MApp_MPlayer_FormatPartitionByDriveIndex(EN_FORMAT_MODE formatMode,U8 u8DriveIndex);
INTERFACE BOOLEAN MApp_MPlayer_BeginCopySelectedFiles(U16 u16DstDriveNo, U16* pu16DstPath);
INTERFACE BOOLEAN MApp_MPlayer_BeginCopySelectedFiles_New(U16 u16DstDriveNo, U16* pu16DstPath, BOOLEAN bAfterCopyDoneStayInSrcFolder);
INTERFACE U16 MApp_MPlayer_QueryCurrentSelectedCopyingFileIndex(void);
INTERFACE U16 MApp_MPlayer_QueryCurrentSelectedDeletingFileIndex(void);
INTERFACE enumMPlayerLanguage MApp_MPlayer_QueryCurMovieAudioLanguage(void);
INTERFACE enumMPlayerLanguage MApp_MPlayer_QueryCurMovieSubtitleLanguage(void);
INTERFACE BOOLEAN MApp_MPlayer_GetMovieAudioCodecSupported(void);
INTERFACE enumMPlayerLanguage MApp_MPlayer_QueryMovieAudioLanguageByTrackIndex(U16 u16AudioTrack);
INTERFACE enumMPlayerLanguage MApp_MPlayer_QueryMovieSubtitleLanguageByTrackIndex(U16 u16SubtitleTrack);
INTERFACE BOOLEAN MApp_MPlayer_IsCurSubtitleText(void);

INTERFACE void MApp_MPlayer_SetSubtitleTimeShift(S32 u32TimeShift);
INTERFACE S32 MApp_MPlayer_GetSubtitleTimeShift(void);
INTERFACE BOOLEAN MApp_MPlayer_IsCurSubtitleExternal(void);

#if ENABLE_SUBTITLE_COPY_AND_DELETE
U32 MApp_MPlayer_GetExternalSubtitleFileSizeByPlaylistIndex(U16 u16FileIdx, enumMPlayerMediaType eMediaType);
#endif
INTERFACE BOOLEAN MApp_MPlayer_GetFileSizeByPlaylistIndex(U16 u16FileIdx, enumMPlayerMediaType eMediaType, LongLong *pfileSize);
INTERFACE BOOLEAN MApp_MPlayer_GetFileEntryByPlaylistIndex(U16 u16FileIdx, enumMPlayerMediaType eMediaType, FileEntry *pFileEntry);

#if PHOTO_SLIDE_SHOW_EFFECT
INTERFACE void MApp_MPlayer_SetSlideShowEffect(EN_PHOTO_SLIDE_SHOW_EFFECT eSlideShowEffect);
#endif

INTERFACE BOOLEAN MApp_MPlayer_SetForceStopCallBackFunction(enumMPlayerMediaType eMediaType, PF_FORCE_STOP pfForceStopCallBack);
INTERFACE BOOLEAN MApp_MPlayer_SetForceDisplayPhotoPartialError(BOOLEAN bForceDisPlay);

INTERFACE BOOLEAN MApp_MPlayer_EnterCopyMode(void);
INTERFACE BOOLEAN MApp_MPlayer_ExitCopyMode(void);
INTERFACE BOOLEAN MApp_MPlayer_QueryIsCopyMode(void);

INTERFACE BOOLEAN MApp_MPlayer_MusicMetaData_Probe_ByDirectoryIndex(enumMPlayerFileIndexBegin eBegin,U16 u16Index,ST_MPLAYER_PROBE_INFO *pstTempMplayerProbeInfo,EN_MUSIC_INFO eMusicInfoType);
INTERFACE BOOLEAN MApp_MPlayer_MusicMetaData_Probe_ByPlayListIndex(U16 u16Index,ST_MPLAYER_PROBE_INFO *pstTempMplayerProbeInfo,EN_MUSIC_INFO eMusicInfoType);

INTERFACE BOOLEAN MApp_MPlayer_QueryPlayListFileAvailable(enumMPlayerMediaType MediaType, U16 u16PlayingIdx);

#undef INTERFACE

#endif


