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
#define MSAPI_NPLAYER_C

///////////////////////////////////////////////////////////////////////////////
/// @file   msAPI_Nplayer.c
/// @author MStar Semiconductor Inc.
/// @brief  mapi - nplayer interface
///////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------------
// Include Files
//------------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include<pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/ipc.h>

#include "Board.h"
#include "sysinfo.h"
#include "MsCommon.h"

#if ((OBA2 == 1) && (ENABLE_BABAO_PLAYER == ENABLE))
#include "BinInfo.h"
#if (CHIP_FAMILY_TYPE != CHIP_FAMILY_S7 )
#include "drvTSP.h"
#endif
#include "drvUART.h"
#include "drvGlobal.h"
#include "drvCPU.h"
#include "drvMMIO.h"

#include "madp.h"
#include "apiDMX.h"
#include "msAPI_CI.h"
#include "msAPI_CPU.h"
#include "msAPI_Timer.h"
#include "msAPI_Memory.h"
#include "msAPI_MIU.h"
#include "msAPI_BDMA.h"
#include "msAPI_MailBox.h"
#include "msAPI_Global.h"
#include "msAPI_Nplayer.h"
#include "msAPI_DataStreamIO.h"
#include "msAPI_OCP.h"
#include "msAPI_APEngine.h"

#include "apiXC_Sys.h"
#include "MApp_APEngine.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalFunction.h"
#include "MApp_InputSource.h"
#include "MApp_Scaler.h"
#include "MApp_XC_PQ.h"
#include "MApp_IR.h"
#include "MApp_GlobalVar.h"
#include "mapp_videoplayer.h"
#include "mapp_music.h"
#include "mapp_wma.h"
#include "mapp_photo.h"
#include "mapp_photo_display.h"
#include "ctype.h"
#include "FSUtil.h"

#ifndef U64
typedef unsigned long long                  U64;
#endif

//------------------------------------------------------------------------------
// Local Defines
//------------------------------------------------------------------------------
#define IPC_VERSION                 "2.0.1.1"
#define IPC_PATH                    "/opt/"
#define IPC_HANDLE                  0

//------------------------------------------------------------------------------
static U8 * m_pMsgAddr;
#define MSG_SEND_HANDLE                     0
#define MSG_RETURN_HANDLE                   1
#define MSG_BUFFER_ADDR                     m_pMsgAddr
#define MSG_BUFFER_SIZE                     0x200
#define MSGI_BUFFER_HEAD                    MSG_BUFFER_ADDR
#define MSGO_BUFFER_HEAD                    (MSGI_BUFFER_HEAD+MSG_BUFFER_SIZE+4)
#define MSG_BUFFER_TOTAL_SIZE               ((MSG_BUFFER_SIZE+4)*2)

static U8 * m_pShmAddr;
#define SHARE_MEM_TOTAL_SIZE                0x800
#define SHARE_MEM_VIDEO_INFO_SIZE           0x100
typedef enum
{
    MPLAYER_SHM_VIDEO_INFO = 0,
    MPLAYER_SHM_MUSIC_INFO = MPLAYER_SHM_VIDEO_INFO+SHARE_MEM_VIDEO_INFO_SIZE,
    MPLAYER_SHM_END = SHARE_MEM_TOTAL_SIZE,
}EN_MPLAYER_SHM_MAP;

//------------------------------------------------------------------------------
#define MsgiBufferIndex8(handle, x)         MSGI_BUFFER_HEAD[(handle*MSG_BUFFER_SIZE)+(x)]
#define MsgoBufferIndex8(handle, x)         MSGO_BUFFER_HEAD[(handle*MSG_BUFFER_SIZE)+(x)]
#define MsgiBufferAddress8(handle, x)       (&MSGI_BUFFER_HEAD[(handle*MSG_BUFFER_SIZE)+(x)])
#define MsgoBufferAddress8(handle, x)       (&MSGO_BUFFER_HEAD[(handle*MSG_BUFFER_SIZE)+(x)])

static U32 m_u32RingBufferHead;
static U32 m_u32RingBufferLength;
static U32 m_u32RingBufferSize;

#define RING_BUFFER_HEAD                    m_u32RingBufferHead
#define RING_BUFFER_LENGTH                  m_u32RingBufferLength
#define RING_BUFFER_SIZE                    m_u32RingBufferSize
#define RING_BUFFER_HEAD_SIZE               0x1000
#define RING_BUFFER_START(x)                (RING_BUFFER_HEAD+(x*RING_BUFFER_SIZE)+RING_BUFFER_HEAD_SIZE)
#define RING_BUFFER_END(x)                  (RING_BUFFER_HEAD+(x*RING_BUFFER_SIZE)+RING_BUFFER_SIZE)
#define RING_BUFFER_VERYFI_CODE             21614

#define INDEX_SHAR_MEM_SIZE                 0
#define INDEX_SHAR_MEM_HEAD_SIZE            8
#define INDEX_RING_BUFFER_START             16
#define INDEX_RING_BUFFER_END               24
#define INDEX_STREAM_READ_POS               32
#define INDEX_STREAM_WRITE_POS              40
#define INDEX_STREAM_READ_PAGES             48
#define INDEX_STREAM_WRITE_PAGES            56
#define INDEX_STREAM_LENGTH                 64
#define INDEX_STREAM_SEEK_POS               72
#define INDEX_STREAM_FLAG                   80
#define INDEX_STREAM_BITRATE                88

//INDEX_STREAM_FLAG
#define STREAM_FLAG_FULL                            0x01
#define STREAM_FLAG_EOF                             0x02

#define COMMAND_TO_MPLAYER                          0x08

#define MPLAYER_COMMAND_INT                         0x01
#define MPLAYER_COMMAND_FINT                        0x02
#define MPLAYER_COMMAND_GET_VERSION                 0x03
#define MPLAYER_COMMAND_CREAT_STREAM                0x04
#define MPLAYER_COMMAND_PLAY_PRE                    0x05

#define MPLAYER_COMMAND_SET_DISP_WINDOW             0x11
#define MPLAYER_COMMAND_SEND_FILE_NAME              0x12
#define MPLAYER_COMMAND_PLAY_FILE                   0x13
#define MPLAYER_COMMAND_PAUSE                       0x14
#define MPLAYER_COMMAND_RESUME                      0x15
#define MPLAYER_COMMAND_FF                          0x16
#define MPLAYER_COMMAND_RW                          0x17
#define MPLAYER_COMMAND_SEEK                        0x18
#define MPLAYER_COMMAND_STOP                        0x19

#define MPLAYER_COMMAND_GET_OPTION                  0x21
#define MPLAYER_COMMAND_SET_OPTION                  0x22
#define MPLAYER_COMMAND_SET_DISP_RTSP               0x23
#define MPLAYER_COMMAND_FREEZE_DISP_RTSP            0x24
#define MPLAYER_COMMAND_SEND_SUBTITLE_FILE          0x31

#define MPLAYER_COMMAND_SEND_SUBTITLE_SUBFILE       0x32
#define MPLAYER_COMMAND_SEND_MUSIC_LYRIC_FILE       0x33
#define MPLAYER_COMMAND_CAPTURE                     0x34

#define COMMAND_TO_NETAP                            0x10
#define NETAP_COMMAND_FILE_OPEN                     0x01
#define NETAP_COMMAND_FILE_CLOSE                    0x02
#define NETAP_COMMAND_FILE_SEEK                     0x03
#define NETAP_COMMAND_RTSP_NOTIFY                   0x12
#define NETAP_COMMAND_CALL_BACK                     0x11
#define NETAP_COMMAND_SUBTITLE                      0x21
#define NETAP_COMMAND_MUSIC_LYRIC                   0x22
#define NETAP_COMMAND_MPLAYER_STATE                 0x31

#define RingBufferIndex32(handle, x)        (*(U32 *)_PA2VA((RING_BUFFER_HEAD+(handle*RING_BUFFER_SIZE)+(x))))
#define RingBufferIndex64(handle, x)        (*(U64 *)_PA2VA((RING_BUFFER_HEAD+(handle*RING_BUFFER_SIZE)+(x))))

#define DIR_NAME_SIZE               1024
#define FILE_NAME_SIZE              256
#define FULLPATH_NAME_SIZE          (((DIR_NAME_SIZE+FILE_NAME_SIZE)/2)*3+1)  //utf-8

#define PARAM_SIZE                  (MSG_BUFFER_SIZE-5)

#define MAX_RING_BUFFER_HANDLE      6

//music related
#define MUSIC_SHARE_MEM_SIZE                    1024
#define INDEX_MUSIC_SHAR_CURRENT_TIME           0
#define INDEX_MUSIC_SHAR_TOTAL_TIME             4
#define INDEX_MUSIC_SHAR_STRING_INFO_TYPE       8
#define INDEX_MUSIC_SHAR_STRING_INFO_LEN        12
#define INDEX_MUSIC_SHAR_STRING_INFO            16

#define LYRIC_MAX_SIZE                          76

//photo related
/// \brief PHOTO_TOTAL_SLOT can't < 1 and if PHOTO_TOTAL_SLOT == 1, no pre-decode
#define PHOTO_TOTAL_SLOT (2)
/// \brief Default photo slide show time out value in secons
#define PHOTO_SLIDESHOW_TIME_OUT (20)

#define PHOTO_NEXT_SLOT(idx)    ((idx + 1) % PHOTO_TOTAL_SLOT)

//------------------------------------------------------------------------------
typedef enum
{
    MPLAYER_STREAM_VIDEO = 0,
    MPLAYER_STREAM_IN_SUB = 1,
    MPLAYER_STREAM_AUDIO = 2,
    MPLAYER_STREAM_MUSIC = 3,
    MPLAYER_STREAM_MUSIC2 = 4,
    MPLAYER_STREAM_PHOTO = 5,

    MPLAYER_STREAM_EX_SUB0 = MAX_RING_BUFFER_HANDLE,
    MPLAYER_STREAM_EX_SUB1,
    MPLAYER_STREAM_LYRIC,
    MPLAYER_STREAM_MAX_HANDLE,
} EN_MPLAYER_STREAM_HANDLE;

typedef enum
{
    MPLAYER_SUBTYPE_UNKNOWN = 0,

    MPLAYER_SUBTYPE_MOVIE,

    MPLAYER_SUBTYPE_JPEG,
    MPLAYER_SUBTYPE_PNG,
    MPLAYER_SUBTYPE_GIF,
    MPLAYER_SUBTYPE_TIFF,
    MPLAYER_SUBTYPE_BMP,

    MPLAYER_SUBTYPE_MP3,
    MPLAYER_SUBTYPE_AAC,
    MPLAYER_SUBTYPE_PCM,
    MPLAYER_SUBTYPE_WAV,
    MPLAYER_SUBTYPE_WMA,

    MPLAYER_SUBTYPE_TEXT,
} EN_MPLAYER_SUB_TYPE;

typedef enum
{
    MPLAYER_BUFFER_NORMAL,
    MPLAYER_BUFFER_INSUFFICIENT,
} EN_MPLAYER_BUFFER_TYPE;

typedef enum
{
    MPLAYER_SUBTITLE_SRT,
    MPLAYER_SUBTITLE_SSA,
    MPLAYER_SUBTITLE_ASS,
    MPLAYER_SUBTITLE_SMI,
    MPLAYER_SUBTITLE_IDX,
    MPLAYER_SUBTITLE_NUM,
    MPLAYER_SUBTITLE_INVALID = 0xFF,
} EN_MPLAYER_SUBTITLE_TYPE;

typedef enum
{
    MPLAYER_FILE_MODE,      //for local file
    MPLAYER_RTSP_MODE,  //for rtsp stream
    MPLAYER_SEEKABLE_STREAM_MODE,   //for seekable stream
    MPLAYER_UNSEEKABLE_STREAM_MODE, //for unseekable stream
} EN_MPLAYER_FILE_MODE;

typedef enum
{
    MPLAYER_EXIT_OK = 0, //playback ok, and exit to ap
    MPLAYER_EXIT_FORCE,  //custom stop playback, and exit to ap
    MPLAYER_EXIT_ERROR_FILE, //playback error, and exit to ap

    MPLAYER_SUFFICIENT_DATA, //when playing, data enough to continue play, and codec wil resume
    MPLAYER_INSUFFICIENT_DATA, //when playing, run short of data, and codec wil pause
    MPLAYER_START_PLAY, //player init ok, and start playing

    MPLAYER_PHOTO_DECODE_DONE,     /*!< \brief The photo decode process has finished successfully. */
    MPLAYER_PHOTO_DECODE_FAILED,    /*!< \brief The photo decode process is failed. */
    MPLAYER_PHOTO_DECODING_NEXT,    /*!< \brief Next file is decoding and no decoded photo is ready for display. */
    MPLAYER_PHOTO_DISPLAYED,    /*!< \brief One decoded photo is now displayed. */

    MPLAYER_MOVIE_THUMBNAIL_DECODE_DONE,
    MPLAYER_MOVIE_THUMBNAIL_DECODE_FAIL,

    MPLAYER_NOTIFY_NULL = 0xFF, //playback notify null
} EN_MPLAYER_NOTIFY_TYPE;

typedef enum
{
    MPLAYER_COMMAND_NOTIFY, //chakra will notify AP EN_MPLAYER_NOTIFY_TYPE, when something happen in movie playing
    MPLAYER_COMMAND_SUBTITLE, //chakra will notify AP to draw/hide subtitle
    MPLAYER_COMMAND_MUSIC_LYRIC, //chakra will notify AP to draw music lyric
    MPLAYER_COMMAND_INVALID,
} EN_MPLAYER_COMMAND_TYPE;

typedef enum
{
    E_TRANSMIT_KEY_NULL = 0,
    E_TRANSMIT_KEY_EXIT = 0x01,
    E_TRANSMIT_KEY_VOLUME_PLUS = 0x02,
    E_TRANSMIT_KEY_VOLUME_MINUS = 0x04,
    E_TRANSMIT_KEY_MUTE = 0x08,
} EN_TRANSMIT_KEY_TYPE;

typedef enum
{
    MPLAYER_OPTION_WRITE_LIMIT = 0x0,    //max bytes to be fed per loop [ 0:total ring buffer size || others:specifc size]
    MPLAYER_OPTION_UP_BOUNDARY,     //ring buffer check range -> up boundary //unit: s default: 30
    MPLAYER_OPTION_DOWN_BOUNDARY,     //ring buffer check range -> down boundary //unit: s default: 10
    MPLAYER_OPTION_RING_BUFFER_HANDLE,    //the number of ring buffer stream handle //default: 1

    MPLAYER_OPTION_ENABLE_SUBTITLE,
    MPLAYER_OPTION_CHANGE_EXTERNAL_SUBTITLE,
    MPLAYER_OPTION_CHANGE_INTERNAL_SUBTITLE,
    MPLAYER_OPTION_CHANGE_PROGRAM,
    MPLAYER_OPTION_CHANGE_AUDIO,

    MPLAYER_OPTION_MOVIE_INFO,  //EN_MPLAYER_INFO
    MPLAYER_OPTION_TRICK_MODE,  //EN_MPLAYER_TRICK_MODE
    MPLAYER_OPTION_ASPECT_RATIO,    //EN_MPLAYER_ASPECT_RATIO_TYPE
    MPLAYER_OPTION_PICTURE_MODE,    //EN_MPLAYER_PICTURE_MODE
    MPLAYER_OPTION_DISPLAY_WINDOW,  //set display in playing

    MPLAYER_OPTION_READ_TIME_OUT,       //vdplayer read stram time out in ms; default:500
    MPLAYER_OPTION_INIT_TIME_OUT,       //vdplayer init time out in ms
    MPLAYER_OPTION_INIT_DATA_SIZE,       //data size before vdplayer init //default: 0x20000
    MPLAYER_OPTION_SET_DBG_LEVEL,       //Set debug level:EN_MPLAYER_DBG_LEVEL
    MPLAYER_OPTION_SET_STC_THRESHOLD,       //set rtsp stc & pts diffrence threshold
    MPLAYER_OPTION_GET_BUFFER_INFO,  //Get valid memory buffer in rtsp
    MPLAYER_OPTION_SET_KTV_MODE,    // KTV mode, moive(whitout audio) and music can play at same time
    MPLAYER_OPTION_SET_SEAMLESS_MODE,    // seamless mode, series of moive can player in seamless way
    MPLAYER_OPTION_PLAY_TIME_OUT,       //vdplayer MApp_VDPlayer_Play() time out in ms; default:5000
    MPLAYER_OPTION_LESS_DATA_MODE,       //if set true, only read "INIT_DATA_SIZE" data before MApp_VDPlayer_Play() //default: false

    MPLAYER_OPTION_SET_MUSIC_TYPE = 0x30,
    MPLAYER_OPTION_GET_MUSIC_TYPE,
    MPLAYER_OPTION_ENABLE_MUSIC_LYRIC,
    MPLAYER_OPTION_DISABLE_MUSIC_LYRIC,
    MPLAYER_OPTION_IS_CURRENT_LYRIC_AVAIL,
    MPLAYER_OPTION_MUSIC_SHARE_MEM_ADDR,
    MPLAYER_OPTION_MUSIC_SHARE_MEM_SIZE,
    MPLAYER_OPTION_MUSIC_INFO,  //EN_MPLAYER_INFO
    MPLAYER_OPTION_MUSIC_SET_PCM_PARAM,

    MPLAYER_OPTION_ZOOM = 0x40,
    MPLAYER_OPTION_ROTATION,
    MPLAYER_OPTION_MOVE_VIEW,

    MPLAYER_OPTION_STOP_PHOTO_DISPLAY =0x50,
    MPLAYER_OPTION_ENABLE_SLIDE_SHOW,
    MPLAYER_OPTION_DISABLE_SLIDE_SHOW,
    MPLAYER_OPTION_SET_SLIDE_SHOW_TIMEOUT,
    MPLAYER_OPTION_GET_PHOTO_FREE_SLOT,
    MPLAYER_OPTION_GET_PHOTO_INFO,
    MPLAYER_OPTION_PHOTO_ONLY_DECODE,

    MPLAYER_OPTION_CAPTURE_LOGO = 0x60,
    MPLAYER_OPTION_CAPTURE_LOGO_BYADDR,
    MPLAYER_OPTION_UART_SWITCH, //EN_MPLAYER_UART_SWITCH
    MPLAYER_OPTION_REPEATAB,
    MPLAYER_OPTION_VOLUME,
    MPLAYER_OPTION_MUTE,

    MPLAYER_OPTION_RTSP_TRACE = 0x70,    //Trace rtsp default: TRUE
    MPLAYER_OPTION_RTSP_FREEZE_MODE,    //Freeze before switch to next channel, default:TRUE
    MPLAYER_OPTION_RTSP_BUFFER_TIME,    //Buffered ms berfore play, unit:ms default:2500
    MPLAYER_OPTION_SET_DRM_KEY,
    MPLAYER_OPTION_SET_SUBTITLE_DELAY,                                       // set subtitle show delay steps, in unit 100ms
    MPLAYER_OPTION_SET_SUBTITLE_ADVANCE,                                  // set subtitle show advanced steps, in unit 100ms
    MPLAYER_OPTION_CANCEL_SUBTITLE_DELAY_ADVANCE,                // cancel subtitle delay/advanced steps, in unit 100ms

    MPLAYER_OPTION_BACKLIGHT_ON_OFF = 0x80,     //on/off back light
    MPLAYER_OPTION_MEMC_ON_OFF,     //on/off memc
    MPLAYER_OPTION_TRANSMIT_KEY,     //EN_TRANSMIT_KEY_TYPE
    MPLAYER_OPTION_GET_MOVIE_THUMBNAIL_INFO,

    MPLAYER_OPTIOND_INVALID,
} EN_MPLAYER_OPTION_TYPE;

//suboption for video/music/photo info
typedef enum
{
    MPLAYER_INFO_TOTAL_TIME = 0x0,
    MPLAYER_INFO_TOTAL_TIME_ISVALID,
    MPLAYER_INFO_CUR_TIME,
    MPLAYER_INFO_FRM_PER_SEC,
    MPLAYER_INFO_H_SIZE,
    MPLAYER_INFO_V_SIZE,
    MPLAYER_INFO_NB_AUDIO_TRACK,
    MPLAYER_INFO_AUDIO_TRACK_ID,
    MPLAYER_INFO_NB_SUBTITLE_TRACK, //Internal subtitle
    MPLAYER_INFO_SUBTITLE_TRACK_ID, //Internal subtitle
    MPLAYER_INFO_NB_PROGRAM,
    MPLAYER_INFO_PROGRAM_ID,
    MPLAYER_INFO_VIDEO_CODEC,   //EN_MPLAYER_VIDEO_CODEC_TYPE
    MPLAYER_INFO_AUDIO_CODEC,   //EN_MPLAYER_AUDIO_CODEC_TYPE
    MPLAYER_INFO_DURATION_PERCENT,
    MPLAYER_INFO_MOVIE_ERROR_CODE,  //EN_VDP_ERRORCODE
    MPLAYER_INFO_INDEX_FRAME_EXIST,

    MPLAYER_INFO_MUSIC_LAYER_LEN = 0x20,                       /*!music info,for wma, Layer,COMMENT and GENRE info are not supported. */
    MPLAYER_INFO_MUSIC_BITRATE_LEN,
    MPLAYER_INFO_MUSIC_SAMPLINGRATE_LEN,
    MPLAYER_INFO_MUSIC_ALBUM_LEN,
    MPLAYER_INFO_MUSIC_TITLE_LEN,
    MPLAYER_INFO_MUSIC_ARTIST_LEN,
    MPLAYER_INFO_MUSIC_YEAR_LEN,
    MPLAYER_INFO_MUSIC_GENRE_LEN,
    MPLAYER_INFO_MUSIC_COMMENT_LEN,
    MPLAYER_INFO_MUSIC_CHECK_FF_FB_LEN,

    MPLAYER_INFO_MUSIC_LAYER,                       /*!music info,for wma, Layer,COMMENT and GENRE info are not supported. */
    MPLAYER_INFO_MUSIC_BITRATE,
    MPLAYER_INFO_MUSIC_SAMPLINGRATE,
    MPLAYER_INFO_MUSIC_ALBUM,
    MPLAYER_INFO_MUSIC_TITLE,
    MPLAYER_INFO_MUSIC_ARTIST,
    MPLAYER_INFO_MUSIC_YEAR,
    MPLAYER_INFO_MUSIC_GENRE,
    MPLAYER_INFO_MUSIC_COMMENT,
    MPLAYER_INFO_MUSIC_CHECK_FF_FB,
    MPLAYER_INFO_MUSIC_ERROR_CODE,

    MPLAYER_INFO_PHOTO_DISPLAYING_WIDTH = 0x40,
    MPLAYER_INFO_PHOTO_DISPLAYING_HEIGHT,
    MPLAYER_INFO_PHOTO_DISPLAYING_SIZE,
    MPLAYER_INFO_PHOTO_DECODED_WIDTH,
    MPLAYER_INFO_PHOTO_DECODED_HEIGHT,
    MPLAYER_INFO_PHOTO_DECODED_PITCH,
    MPLAYER_INFO_PHOTO_DECODE_PROGRESS,
    MPLAYER_INFO_PHOTO_DECODE_OUTBUF_ADDR,
    MPLAYER_INFO_PHOTO_ERROR_CODE,
    MPLAYER_INFO_PHOTO_CODEC_TYPE,
    MPLAYER_INFO_PHOTO_IMAGE_ORIGINAL_WIDTH,
    MPLAYER_INFO_PHOTO_IMAGE_ORIGINAL_HEIGHT,

    MPLAYER_INFO_MOVIE_THUMBNAIL_WIDTH = 0x60,
    MPLAYER_INFO_MOVIE_THUMBNAIL_HEIGHT,
    MPLAYER_INFO_MOVIE_THUMBNAIL_PITCH,
    MPLAYER_INFO_MOVIE_THUMBNAIL_OUTBUF_ADDR,
}EN_MPLAYER_INFO;

typedef enum
{
    MPLAYER_TRICK_NORMAL,         /// Enter normal play mode
    MPLAYER_TRICK_PAUSE,          /// Pause
    MPLAYER_TRICK_FF_2X,          /// Fast forward 2x
    MPLAYER_TRICK_FF_4X,          /// Fast forward 4x
    MPLAYER_TRICK_FF_8X,          /// Fast forward 8x
    MPLAYER_TRICK_FF_16X,         /// Fast forward 16x
    MPLAYER_TRICK_FB_2X,          /// Fast backward 2x
    MPLAYER_TRICK_FB_4X,          /// Fast backward 4x
    MPLAYER_TRICK_FB_8X,          /// Fast backward 8x
    MPLAYER_TRICK_FB_16X,         /// Fast backward 16x
    MPLAYER_TRICK_SLOW,           /// Slow motion mode
    MPLAYER_TRICK_MODE_NUM,  /// Specify the number of movie play mode
    MPLAYER_TRICK_MODE_INVALID = MPLAYER_TRICK_MODE_NUM,
} EN_MPLAYER_TRICK_MODE;

typedef enum
{
    MPLAYER_STATE_STANDBY = 0,
    MPLAYER_STATE_PRE_INIT,
    MPLAYER_STATE_INIT,
    MPLAYER_STATE_PLAYING,
} EN_MPLAYER_STATE;

typedef enum
{
    MPLAYER_SUBTITLE_ENCODE_ANSI,
    MPLAYER_SUBTITLE_ENCODE_UNIS,
    MPLAYER_SUBTITLE_ENCODE_UNIB,
    MPLAYER_SUBTITLE_ENCODE_UTF8,
    MPLAYER_SUBTITLE_ENCODE_INVALID,
} EN_MPLAYER_SUBTITLE_ENCODE;

typedef enum
{
    MPLAYER_LYRIC_ENCODE_ANSI,
    MPLAYER_LYRIC_ENCODE_UNIS,
    MPLAYER_LYRIC_ENCODE_UNIB,
    MPLAYER_LYRIC_ENCODE_UTF8,
    MPLAYER_LYRIC_ENCODE_INVALID,
} EN_MPLAYER_LYRIC_ENCODE;

typedef enum
{
    MPLAYER_DBG_LEVEL_NONE = 0,    // disable all uart message.
    MPLAYER_DBG_LEVEL_ERR,    // Only output error message
    MPLAYER_DBG_LEVEL_INFO,    // output general message, and above.
    MPLAYER_DBG_LEVEL_DBG,    // output debug message, and above.
    MPLAYER_DBG_LEVEL_TRACE,    // output function tracing message, and above.
    MPLAYER_DBG_LEVEL_FW,    // output FW message.
} EN_MPLAYER_DBG_LEVEL;

typedef enum
{
    MPLAYER_UART_SWITCH_TO_HK,
    MPLAYER_UART_SWITCH_TO_COPROCESSOR,
} EN_MPLAYER_UART_SWITCH;

typedef enum
{
    MPLAYER_RTSP_OPEN,
    MPLAYER_RTSP_INIT,
    MPLAYER_RTSP_PLAY,
    MPLAYER_RTSP_PAUSE,
    MPLAYER_RTSP_RESUME,
    MPLAYER_RTSP_EXIT,
} EN_MPLAYER_RTSP;

//------------------------------------------------------------------------------
// vdplayer sharemem
//------------------------------------------------------------------------------
typedef enum
{
    MPLAYER_VIDEO_INFO_TOTAL_TIME,
    MPLAYER_VIDEO_INFO_TOTAL_TIME_ISVALID,
    MPLAYER_VIDEO_INFO_CURRENT_TIME,
    MPLAYER_VIDEO_INFO_FRAME_RATE,
    MPLAYER_VIDEO_INFO_WIDTH,
    MPLAYER_VIDEO_INFO_HEIGHT,
    MPLAYER_VIDEO_INFO_VIDEO_CROP_LEFT,
    MPLAYER_VIDEO_INFO_VIDEO_CROP_RIGHT,
    MPLAYER_VIDEO_INFO_VIDEO_CROP_TOP,
    MPLAYER_VIDEO_INFO_VIDEO_CROP_BOTTOM,
    MPLAYER_VIDEO_INFO_TOTAL_ADUIO_TRACK,
    MPLAYER_VIDEO_INFO_CURRENT_AUDIO_TRACK_ID,
    MPLAYER_VIDEO_INFO_TOTAL_SUBTITLE,
    MPLAYER_VIDEO_INFO_CURRENT_SUBTITLE_TRACK_ID,
    MPLAYER_VIDEO_INFO_TS_PROGRAM_NUM,
    MPLAYER_VIDEO_INFO_TS_CUR_PROGRAM_IDX,
    MPLAYER_VIDEO_INFO_VIDEO_CODEC_ID,
    MPLAYER_VIDEO_INFO_AUDIO_CODEC_ID,
    MPLAYER_VIDEO_INFO_ERROR_INFO,
    MPLAYER_VIDEO_INFO_DURATION_PERCENT,
    MPLAYER_VIDEO_INFO_INDEX_FRAME_EXIST,
    MPLAYER_VIDEO_INFO_BUFFER_PERCENT,
    MPLAYER_VIDEO_INFO_NUM,
}EN_MPLAYER_VIDEO_INFO_INDEX;

static U16 m_u16VideoShareMemIndex[MPLAYER_VIDEO_INFO_NUM] =
{
    E_SHAREMEM_TOTAL_TIME,
    E_SHAREMEM_TOTAL_TIME_ISVALID,
    E_SHAREMEM_CURRENT_TIME,
    E_SHAREMEM_FRAME_RATE,
    E_SHAREMEM_WIDTH,
    E_SHAREMEM_HEIGHT,
    E_SHAREMEM_VIDEO_CROP_LEFT,
    E_SHAREMEM_VIDEO_CROP_RIGHT,
    E_SHAREMEM_VIDEO_CROP_TOP,
    E_SHAREMEM_VIDEO_CROP_BOTTOM,
    E_SHAREMEM_TOTAL_ADUIO_TRACK,
    E_SHAREMEM_CURRENT_AUDIO_TRACK_ID,
    E_SHAREMEM_TOTAL_SUBTITLE,
    E_SHAREMEM_CURRENT_SUBTITLE_TRACK_ID,
    E_SHAREMEM_TS_PROGRAM_NUM,
    E_SHAREMEM_TS_CUR_PROGRAM_IDX,
    E_SHAREMEM_VIDEO_CODEC_ID,
    E_SHAREMEM_AUDIO_CODEC_ID,
    E_SHAREMEM_ERROR_INFO,
    E_SHAREMEM_BUFFER_INFO+E_BUFFER_INFO_DURATION,
    E_SHAREMEM_MAX_FAST_BACKWARD_SPEED,
    E_SHAREMEM_BUFFER_INFO+E_SHAREMEM_BUFFER_INFO_SIZE-1,
};

typedef enum
{
    E_MPLAYER_MUSIC_FLG_NULL = 0,
    E_MPLAYER_MUSIC_FLG_LYRIC_VALID,
    E_MPLAYER_MUSIC_FLG_LYRIC_ENABLE,
} EN_MPLAYER_MUSIC_FLAG;

//photo related
typedef enum
{
    E_PHOTO_SLOT_STATE_FREE = 0,
    E_PHOTO_SLOT_STATE_DECODING,
    E_PHOTO_SLOT_STATE_DECODED,
    E_PHOTO_SLOT_STATE_DISPLAYING,
} E_PHOTO_SLOT_STATE;

typedef enum
{
    E_PHOTO_SLIDE_SHOW_FREE_RUN = 0,
    E_PHOTO_SLIDE_SHOW_PAUSED,
    E_PHOTO_SLIDE_SHOW_PAUSE_RELEASED,
} E_PHOTO_PAUSE_STATE;

/*! \brief Rotation angle. Apply to \e E_STRM_TYPE_PHOTO. */
typedef enum
{
    E_ROTATION_0,
    E_ROTATION_90,
    E_ROTATION_180,
    E_ROTATION_270,

    E_ROTATION_MAX,
} E_ROTATION;

/*! \brief Zooming factor. Apply to \e E_STRM_TYPE_MOVIE and \e E_STRM_TYPE_PHOTO. */
typedef enum
{
    E_ZOOM_1_DIV_8,  /*!< Zoom in, X(1/8). */
    E_ZOOM_1_DIV_4,  /*!< Zoom in, X(1/4). */
    E_ZOOM_1_DIV_2,  /*!< Zoom in, X(1/2). */
    E_ZOOM_1,        /*!< Normal, X1. */
    E_ZOOM_2,        /*!< Zoom out, X2. */
    E_ZOOM_4,        /*!< Zoom out, X4. */
    E_ZOOM_8,        /*!< Zoom out, X8. */

    E_ZOOM_MAX,
} E_ZOOM;

/*! \brief Moving direction. Apply to \e E_STRM_TYPE_MOVIE and \e E_STRM_TYPE_PHOTO. */
typedef enum
{
    E_DIRECTION_UP,
    E_DIRECTION_DOWN,
    E_DIRECTION_LEFT,
    E_DIRECTION_RIGHT,

    E_DIRECTION_MAX,
} E_DIRECTION;

typedef struct
{
    S16 s16ShiftX, s16ShiftY;
    E_ROTATION  eRotation;
    E_ZOOM   eZoom;
}MPLAYER_VIEW_INFO;

typedef enum
{
    E_PCM_FORMAT_PCM, //PCM
    E_PCM_FORMAT_M_ADPCM, //M ADPCM
    E_PCM_FORMAT_IMA_ADPCM, //8-bit ITU-T G.711 £g-law
    E_PCM_FORMAT_NUM,
} EN_PCM_FORMAT;

typedef enum
{
    E_FMT_RGB565,
    E_FMT_ARGB8888,
    E_FMT_YUV422,
    E_FMT_NUM,
} EN_CAPTURE_SRC_FORMAT;

typedef enum
{
    REPEATAB_MODE_NONE,
    REPEATAB_MODE_A,
    REPEATAB_MODE_AB,
    REPEATAB_MODE_MAX,
}EN_REPEATAB_STATUS;


//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------
#define MAKEU16(ptr, x) (U16)((ptr)[(x)] + ((ptr)[(x)+1] << 8))
#define MAKEU32(ptr, x) (U32)((ptr)[(x)] + ((ptr)[(x)+1] << 8) + ((ptr)[(x)+2] << 16) + ((ptr)[(x)+3] << 24))
#define SETU16(ptr, x, data) \
                        (ptr)[(x)] = (data) & 0xFF; \
                        (ptr)[(x)+1] = ((data) >> 8) & 0xFF;
#define SETU32(ptr, x, data) \
                        (ptr)[(x)] = (data) & 0xFF; \
                        (ptr)[(x)+1] = ((data) >> 8) & 0xFF; \
                        (ptr)[(x)+2] = ((data) >> 16) & 0xFF; \
                        (ptr)[(x)+3] = ((data) >> 24) & 0xFF;

#define MPLAYER_MSG_MUST(format, args...)   do{if(1) printf(format, ##args);}while(0)
#define MPLAYER_MSG_ERR(format, args...)    do{if(m_eDebugLevle >= MPLAYER_DBG_LEVEL_ERR) printf(format, ##args);}while(0)
#define MPLAYER_MSG_INFO(format, args...)   do{if(m_eDebugLevle >= MPLAYER_DBG_LEVEL_INFO) printf(format, ##args);}while(0)
#define MPLAYER_MSG_DBG(format, args...)    do{if(m_eDebugLevle >= MPLAYER_DBG_LEVEL_DBG) printf(format, ##args);}while(0)
#define MPLAYER_MSG_TRACE(format, args...)  do{if(m_eDebugLevle >= MPLAYER_DBG_LEVEL_TRACE) printf(format, ##args);}while(0)
#define MPLAYER_MSG_FW(format, args...)  do{if(m_eDebugLevle >= MPLAYER_DBG_LEVEL_FW) printf(format, ##args);}while(0)

//------------------------------------------------------------------------------
// Local Variables
//------------------------------------------------------------------------------
static char ver[] = IPC_VERSION;

static char * m_pName;
static char m_FullPathName[FULLPATH_NAME_SIZE];
static int m_Stmfd[MPLAYER_STREAM_MAX_HANDLE];
static U32 m_StmHdl[E_DATA_STREAM_TYPE_NUM];
static EN_MPLAYER_MEDIA_TYPE m_StrmMediaType[MPLAYER_STREAM_MAX_HANDLE];
static FN_DATA_STRM_IO m_StreamIOFunc;
static U32 m_u32NplayerCnt;
static U32 m_u32PID[E_MPLAYER_MEDIA_NUM];

static char m_SubtitleFile[FULLPATH_NAME_SIZE];
static char m_SubtitleSubFile[FULLPATH_NAME_SIZE];
static char m_LyricFile[FULLPATH_NAME_SIZE];
static enumMPlayerSubtitleType m_eExternalSubtitleType = E_MPLAYER_SUBTITLE_INVALID;
static EN_MPLAYER_SUBTITLE_ENCODE m_eSubtitleEncode = MPLAYER_SUBTITLE_ENCODE_INVALID;
static EN_MPLAYER_LYRIC_ENCODE m_eMusicLyricEncode = MPLAYER_LYRIC_ENCODE_INVALID;

static BOOLEAN m_bCheckScreen;
static BOOLEAN m_bNplayerRun;
static BOOLEAN m_bNplayerPlay[E_MPLAYER_MEDIA_NUM];
static U32 m_u32RingBufferNum[E_MPLAYER_MEDIA_NUM];

static BOOLEAN m_bBacklightOnOff;
static BOOLEAN m_bMemcOnOff;
static BOOLEAN m_u8TransmitKey;

static EN_MPLAYER_DBG_LEVEL m_eDebugLevle;
static EN_MPLAYER_FILE_MODE m_eStreamMode[E_MPLAYER_MEDIA_NUM];
static EN_MPLAYER_TRICK_MODE m_eTrickMode[E_MPLAYER_MEDIA_NUM];
static EN_MPLAYER_BUFFER_TYPE m_eBufferType[E_MPLAYER_MEDIA_NUM];
static EN_MPLAYER_STATE m_eMplayerState[E_MPLAYER_MEDIA_NUM] =
{
    MPLAYER_STATE_STANDBY,
    MPLAYER_STATE_STANDBY,
    MPLAYER_STATE_STANDBY
};
static MPLAYER_VIEW_INFO m_ViewInfo[E_MPLAYER_MEDIA_NUM];
static VDPLAYER_ZOOM_FACT m_eZoom;

static U32  m_u32CodecTimeOut[E_SHAREMEM_ESBUF_CTRL_TIMEOUT-E_SHAREMEM_BLOCK_FILEIO_TIMEOUT+1];
static U32 m_u32StartGotoTime;
static U32 m_u32StartPlayTimer;
static U32 m_u32VdplayerInitStartTimer;
static U32 m_u32VdplayerInitTimerOut;
static U32 m_u32VdplayerReadTimerOut;
static S32 m_s32MinBufferSize;
static S32 m_s32MaxBufferSize;
static S32 m_s32MinBufferSec;
static S32 m_s32MaxBufferSec;
static U32 m_u32InitDataSize;
static U32 m_u32ReadTotalSize;
static S32 m_s32DiffBitrate;
static BOOL m_bLessDataSize;
static BOOL m_bKTVMode;
static BOOL m_bRtspFreeze;
static BOOL m_bNotSupportStreamLen;
static BOOL m_bMovieThumbnail = FALSE;

static U32 m_u32MuteTimer;
static BOOL m_bCheckMute;
static U8 m_u8ForceStop;

static U8 m_u8BakReg0640;
static U8 m_u8BakReg0642;

// music specific variables
static EN_MPLAYER_SUB_TYPE _geMPLAYER_MusicType = MPLAYER_SUBTYPE_UNKNOWN;
static EN_MUSIC_TYPE _genMusicType = EN_MUSIC_MP3;
static U32 m_u32PlayCheckTime;
static U32 m_u32LyricSubtitleCurTime;
static U16 m_u16CurLyricPos;
static BOOLEAN m_bIsLyricUnicode = FALSE;
static EN_MPLAYER_MUSIC_FLAG m_eMusicFlag = E_MPLAYER_MUSIC_FLG_NULL;
static U32 m_u32PlayTime = 0;
static U32 m_u32MusicShareMemAddr;
static U32 m_u32MusicShareMemLength;

//photo specific variables
static BOOLEAN m_bThumbnail;
static BOOLEAN m_bFullScreen;
static U8 _gu8Photo_DecodeIdx;
static U8 _gu8Photo_DisplayIdx;
static E_PHOTO_SLOT_STATE _gePhoto_State[PHOTO_TOTAL_SLOT];
static U16 _gu16Photo_SlideShowTimeOutInSec;
static E_PHOTO_PAUSE_STATE _gePhoto_SlideShowPauseState;

static U16 _gu16Photo_Wdith[PHOTO_TOTAL_SLOT];
static U16 _gu16Photo_Height[PHOTO_TOTAL_SLOT];
static U32 _gu32Photo_Size[PHOTO_TOTAL_SLOT];
static U32 m_u32PhotoPlayTime = 0;
static BOOLEAN _gbPhotoOnlyDecode = FALSE;

static U32 u32LoopTimer[2];
static U32 u32TaskLoopCnt;
static U32 u32TaskLoopMax[3];

static U32 u32AudioMonitTimer;

//repeat AB variables
static U32 m_u32MovieRepeatTime[2];
static EN_REPEATAB_STATUS m_enRpeatABMode;
static BOOLEAN m_bNewRepeatABLoop = FALSE;

//IPC variables
static BOOLEAN m_bInSend = FALSE;
static BOOLEAN m_bInit = FALSE;
static ST_PHOTO_CAPTURE_RECT m_sCaptureRect;

union semun
{
    S32 val;
    struct semid_ds *buf;
    U16 *array;
} arg;
S32 shmid;
S32 semid;

static U8 m_u8IPCErrPool[0x1000];
static U32 m_u32IPCErrCnt;

//-------------------------------------------------------------------------------------------------
//Global Variables
//-------------------------------------------------------------------------------------------------
extern VDEC_DispInfo gstVidStatus, gstPreVidStatus;

//-------------------------------------------------------------------------------------------------
// extern Function
//-------------------------------------------------------------------------------------------------
#if (ENABLE_MPLAYER_VIDEO_CAPTURE)
extern BOOLEAN _MApp_MPlayer_CaptureVideo2JPGFile(U8 *pFileName, U32 u32TmpBuffAddr, U32 u32TmpBuffSize);
#endif
extern U16 MApp_Transfer2Unicode(U16 u16Code);

//------------------------------------------------------------------------------
static void msAPI_NPlayer_Stop(EN_MPLAYER_MEDIA_TYPE eType, EN_MPLAYER_NOTIFY_TYPE eNotifyCode);
static void msAPI_NPlayer_Polling(void);
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Local Function Prototypes
//------------------------------------------------------------------------------
static void block_p(S32 sem_id, S32 sem_num)
{
    struct sembuf sops={sem_num,+1,0};
    while((semop(sem_id,&sops,1) == -1) && (errno == EINTR));
}

static void block_v(S32 sem_id,  S32 sem_num)
{
    struct sembuf sops={sem_num,-1,0};
    while((semop(sem_id,&sops,1) == -1) && (errno == EINTR));
}

static void wait_v(void)
{
    U32 i = 0;
    while (MsgoBufferIndex8(MSG_SEND_HANDLE,0) && (i < 5000))
    {
        if (((++i)%1000) == 0)
        {
            MPLAYER_MSG_ERR("hwait_v[%d]\n", i);
        }

        if (i < 5000)
        {
            usleep(1000);
        }
        else
        {
            if (m_u32IPCErrCnt < (sizeof(m_u8IPCErrPool)/8))
            {
                memcpy(m_u8IPCErrPool+m_u32IPCErrCnt*8, MsgoBufferAddress8(MSG_SEND_HANDLE,0), 8);
                m_u32IPCErrCnt++;
            }
        }
    }
}

static BOOLEAN msAPI_NPlayer_Signal(U32 u32PID, U32 uDataSize, U8* param)
{
    if (u32PID != 0xFFFFFFFF)
    {
        wait_v();
        MsgoBufferIndex8(MSG_SEND_HANDLE,1) = u32PID&0xFF;
        MsgoBufferIndex8(MSG_SEND_HANDLE,2) = (u32PID>>8)&0xFF;
        MsgoBufferIndex8(MSG_SEND_HANDLE,3) = (u32PID>>16)&0xFF;
        MsgoBufferIndex8(MSG_SEND_HANDLE,4) = (u32PID>>24)&0xFF;
        memcpy(MsgoBufferAddress8(MSG_SEND_HANDLE,5), param, (uDataSize < PARAM_SIZE ? uDataSize : PARAM_SIZE));
        MsgoBufferIndex8(MSG_SEND_HANDLE,0) = 1;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static U32 msAPI_NPlayer_Query(U32 u32PID, U32 uDataSize, U8* param)
{
    U32 u32RetData = 0;

    if (u32PID != 0xFFFFFFFF)
    {
        wait_v();
        MsgoBufferIndex8(MSG_SEND_HANDLE,1) = u32PID&0xFF;
        MsgoBufferIndex8(MSG_SEND_HANDLE,2) = (u32PID>>8)&0xFF;
        MsgoBufferIndex8(MSG_SEND_HANDLE,3) = (u32PID>>16)&0xFF;
        MsgoBufferIndex8(MSG_SEND_HANDLE,4) = (u32PID>>24)&0xFF;
        memcpy(MsgoBufferAddress8(MSG_SEND_HANDLE,5), param, (uDataSize < PARAM_SIZE ? uDataSize : PARAM_SIZE));
        MsgoBufferIndex8(MSG_SEND_HANDLE,0) = 2;

        wait_v();
        u32RetData = MsgoBufferIndex8(MSG_RETURN_HANDLE,3);
        u32RetData = u32RetData << 8;
        u32RetData += MsgoBufferIndex8(MSG_RETURN_HANDLE,2);
        u32RetData = u32RetData << 8;
        u32RetData += MsgoBufferIndex8(MSG_RETURN_HANDLE,1);
        u32RetData = u32RetData << 8;
        u32RetData += MsgoBufferIndex8(MSG_RETURN_HANDLE,0);
        MPLAYER_MSG_FW("msAPI_NPlayer_Query Got Reply(0x%x, 0x%x)\n", u32PID, u32RetData);
    }
    return u32RetData;
}

//-----------------------------------------------------------------------------
static BOOLEAN msAPI_NPlayer_SendCmd(EN_MPLAYER_MEDIA_TYPE eType, EN_MPLAYER_COMMAND_TYPE eCmd, U32 u32Param)
{
    U8 param[16];

    MPLAYER_MSG_INFO("SendCmd[%d][%d]\n", eCmd, u32Param);
    param[0] = COMMAND_TO_NETAP;
    param[1] = NETAP_COMMAND_CALL_BACK;
    param[2] = eCmd;
    param[3] = eType;
    SETU32(param, 4, u32Param);
    msAPI_NPlayer_Signal(m_u32PID[eType], 8, param);

    return TRUE;
}

//------------------------------------------------------------------------------
static U32 msAPI_NPlayer_StreamOpen(void *pPrivate, U8 u8OpenMode, E_DATA_STREAM_TYPE eType)
{
    char * pName;
    U32 i, u32StrmHdl;
    EN_MPLAYER_MEDIA_TYPE eMediaType;
    BOOLEAN bIsAudioStream = FALSE;

    UNUSED(pPrivate);
    UNUSED(u8OpenMode);
    MPLAYER_MSG_INFO("msAPI_NPlayer_StreamOpen_before(%d, %d, %d)\n", (U32)pPrivate, u8OpenMode, eType);

    //for music stream mode, it does not support opening two handles at one time. So change into one handle. but it will cause  AAC M4A
    //can not play correctly. need refine AAC M4A later.
    if(eType == E_DATA_STREAM_TYPE_MUSIC2 && m_eStreamMode[E_MPLAYER_MEDIA_MUSIC] != MPLAYER_FILE_MODE)
    {
        eType = E_DATA_STREAM_TYPE_MUSIC;
        MPLAYER_MSG_INFO("[music]: change into msAPI_NPlayer_StreamOpen_before(%d, %d, %d)\n", (U32)pPrivate, u8OpenMode, eType);
    }

    if (m_StmHdl[eType] != INVALID_DATA_STREAM_HDL)
    {
        MPLAYER_MSG_INFO("msAPI_NPlayer_StreamOpen_end0(%d)\n", m_StmHdl[eType]);
        return m_StmHdl[eType];
    }

    if ((eType == E_DATA_STREAM_TYPE_VIDEO) ||
        (eType == E_DATA_STREAM_TYPE_IN_SUB) ||
        (eType == E_DATA_STREAM_TYPE_AUDIO) ||
        (eType == E_DATA_STREAM_TYPE_MUSIC) ||
        (eType == E_DATA_STREAM_TYPE_MUSIC2) ||
        (eType == E_DATA_STREAM_TYPE_PHOTO))
    {
        pName = m_pName;
        for (i = 0; i < MAX_RING_BUFFER_HANDLE; i++)
        {
            if (m_Stmfd[i] == -1)
            {
                break;
            }
        }
        if (i < MAX_RING_BUFFER_HANDLE)
            u32StrmHdl = i;
        else
            return INVALID_DATA_STREAM_HDL;

        switch(eType)
        {
            case E_DATA_STREAM_TYPE_MUSIC:
            case E_DATA_STREAM_TYPE_MUSIC2:
                m_StrmMediaType[u32StrmHdl] = E_MPLAYER_MEDIA_MUSIC;
                break;

            case E_DATA_STREAM_TYPE_PHOTO:
                m_StrmMediaType[u32StrmHdl] = E_MPLAYER_MEDIA_PHOTO;
                break;

            case E_DATA_STREAM_TYPE_VIDEO:
            case E_DATA_STREAM_TYPE_IN_SUB:
                m_StrmMediaType[u32StrmHdl] = E_MPLAYER_MEDIA_MOVIE;
                break;

            case E_DATA_STREAM_TYPE_AUDIO:   //it is a seperated stream,need process specially
                bIsAudioStream = TRUE;
                m_StrmMediaType[u32StrmHdl] = E_MPLAYER_MEDIA_MOVIE;
                break;

            default:
                break;
        }
    }
    else if (eType == E_DATA_STREAM_TYPE_EX_SUB0)
    {
        pName = m_SubtitleFile;
        u32StrmHdl = MPLAYER_STREAM_EX_SUB0;
        m_StrmMediaType[u32StrmHdl] = E_MPLAYER_MEDIA_MOVIE;
    }
    else if (eType == E_DATA_STREAM_TYPE_EX_SUB1)
    {
        pName = m_SubtitleSubFile;
        u32StrmHdl = MPLAYER_STREAM_EX_SUB1;
        m_StrmMediaType[u32StrmHdl] = E_MPLAYER_MEDIA_MOVIE;
    }
    else if (eType == E_DATA_STREAM_TYPE_LYRIC)
    {
        pName = m_LyricFile;
        u32StrmHdl = MPLAYER_STREAM_LYRIC;
        m_StrmMediaType[u32StrmHdl] = E_MPLAYER_MEDIA_MUSIC;
    }
    else
    {
        return INVALID_DATA_STREAM_HDL;
    }

    if ((m_Stmfd[u32StrmHdl] != -1) || ((eMediaType = m_StrmMediaType[u32StrmHdl]) >= E_MPLAYER_MEDIA_INVALID))
    {
        return INVALID_DATA_STREAM_HDL;
    }

    if ((m_eStreamMode[eMediaType] == MPLAYER_FILE_MODE) || (u32StrmHdl >= MPLAYER_STREAM_EX_SUB0))
    {
        MPLAYER_MSG_DBG("MPLAYER_FILE_MODE(%s)\n", pName);
        int fd = open(pName, O_RDONLY);
        if (fd != -1)
        {
            m_Stmfd[u32StrmHdl] = fd;
        }
        else
        {
            m_StrmMediaType[u32StrmHdl] = E_MPLAYER_MEDIA_INVALID;
            return INVALID_DATA_STREAM_HDL;
        }
    }
    else
    {
        U8 param[16];

        RingBufferIndex32(u32StrmHdl, INDEX_STREAM_READ_POS) = RingBufferIndex32(u32StrmHdl, INDEX_RING_BUFFER_START);    //read pos
        RingBufferIndex32(u32StrmHdl, INDEX_STREAM_WRITE_POS) = RingBufferIndex32(u32StrmHdl, INDEX_RING_BUFFER_START);  //write pos
        RingBufferIndex32(u32StrmHdl, INDEX_STREAM_READ_PAGES) = 0;
        RingBufferIndex32(u32StrmHdl, INDEX_STREAM_WRITE_PAGES) = 0;
        RingBufferIndex32(u32StrmHdl, INDEX_STREAM_FLAG) = 0;
        RingBufferIndex64(u32StrmHdl, INDEX_STREAM_SEEK_POS) = 0;

        param[0] = COMMAND_TO_NETAP;
        param[1] = NETAP_COMMAND_FILE_OPEN;
        param[2] = u32StrmHdl;
        param[3] = eMediaType;
        param[4] = bIsAudioStream;
        param[5] = m_eStreamMode[eMediaType];
        if (msAPI_NPlayer_Query(m_u32PID[m_StrmMediaType[u32StrmHdl]], 6, param))
        {
            m_Stmfd[u32StrmHdl] = u32StrmHdl;
        }
        else
        {
            m_StrmMediaType[u32StrmHdl] = E_MPLAYER_MEDIA_INVALID;
            return INVALID_DATA_STREAM_HDL;
        }
    }
    m_StmHdl[eType] = u32StrmHdl;

    MPLAYER_MSG_INFO("msAPI_NPlayer_StreamOpen_end1(%d)\n", u32StrmHdl);
    return u32StrmHdl;
}

static BOOLEAN msAPI_NPlayer_StreamClose(U32 u32Hdl)
{
    U8 i = 0;
    EN_MPLAYER_MEDIA_TYPE eMediaType;

    MPLAYER_MSG_INFO("msAPI_NPlayer_StreamClose_before(%d)\n", u32Hdl);

    if ((u32Hdl >= MPLAYER_STREAM_MAX_HANDLE) || (m_Stmfd[u32Hdl] == -1) || ((eMediaType = m_StrmMediaType[u32Hdl]) >= E_MPLAYER_MEDIA_INVALID))
    {
        MPLAYER_MSG_INFO("msAPI_NPlayer_StreamClose_end0\n");
        return FALSE;
    }

    if ((m_eStreamMode[eMediaType] == MPLAYER_FILE_MODE) || (u32Hdl >= MPLAYER_STREAM_EX_SUB0))
    {
        close(m_Stmfd[u32Hdl]);
    }
    else
    {
        U8 param[16];

        param[0] = COMMAND_TO_NETAP;
        param[1] = NETAP_COMMAND_FILE_CLOSE;
        param[2] = u32Hdl;
        msAPI_NPlayer_Query(m_u32PID[m_StrmMediaType[u32Hdl]], 3, param);
    }
    while (i < E_DATA_STREAM_TYPE_NUM)
    {
        if (m_StmHdl[i] == u32Hdl)
        {
            m_StmHdl[i] = INVALID_DATA_STREAM_HDL;
            break;
        }
        i++;
    }
    m_Stmfd[u32Hdl] = -1;
    m_StrmMediaType[u32Hdl] = E_MPLAYER_MEDIA_INVALID;

    MPLAYER_MSG_INFO("msAPI_NPlayer_StreamClose_end1\n");
    return TRUE;
}

static BOOLEAN msAPI_NPlayer_StreamSeek(U32 u32Hdl, LongLong u64SeekPos, E_DATA_STREAM_SEEK_OPTION option)
{
    EN_MPLAYER_MEDIA_TYPE eMediaType;

    MPLAYER_MSG_DBG("msAPI_NPlayer_StreamSeek_before(%d, 0x%x, 0x%x, %d)[%d]\n", u32Hdl, u64SeekPos.Hi, u64SeekPos.Lo, option, g_bNonBlockingSeek);
    if ((u32Hdl >= MPLAYER_STREAM_MAX_HANDLE) || ((eMediaType = m_StrmMediaType[u32Hdl]) >= E_MPLAYER_MEDIA_INVALID))
        return FALSE;

    if ((m_eStreamMode[eMediaType] == MPLAYER_FILE_MODE) || (u32Hdl >= MPLAYER_STREAM_EX_SUB0))
    {
        int seekOff;
        off_t offset;

        if (sizeof(off_t) > 4)
            offset = ((off_t)u64SeekPos.Hi << 32) + u64SeekPos.Lo;
        else
            offset = u64SeekPos.Lo;

        switch(option)
        {
            case E_DATA_STREAM_SEEK_SET:
                seekOff =  lseek(m_Stmfd[u32Hdl], offset, SEEK_SET);
                break;
            case E_DATA_STREAM_SEEK_CUR:
                seekOff =  lseek(m_Stmfd[u32Hdl], offset, SEEK_CUR);
                break;
            default:
                return FALSE;
        }
        MPLAYER_MSG_DBG("msAPI_NPlayer_StreamSeek_end0(0x%x)\n", seekOff);
        return (seekOff >= 0) ? TRUE : FALSE;
    }
    else
    {
        U8 param[16];
        U32 u32ReadPos;
        U32 u32WritePos;
        U32 u32ReadPages;
        U32 u32WritePages;
        U32 u32BufferSize;
        U32 u32AbailableData0, u32AbailableData1;
        U64 u64ReadPos;
        U64 u64GotoPos = ((U64)u64SeekPos.Hi << 32) + (U64)(u64SeekPos.Lo);

        block_v(semid, 0);
        u32ReadPos = RingBufferIndex32(u32Hdl, INDEX_STREAM_READ_POS);
        u32WritePos = RingBufferIndex32(u32Hdl, INDEX_STREAM_WRITE_POS);
        u32ReadPages = RingBufferIndex32(u32Hdl, INDEX_STREAM_READ_PAGES);
        u32WritePages = RingBufferIndex32(u32Hdl, INDEX_STREAM_WRITE_PAGES);
        u32BufferSize = RingBufferIndex32(u32Hdl, INDEX_RING_BUFFER_END) - RingBufferIndex32(u32Hdl, INDEX_RING_BUFFER_START);
        if (u32WritePos > u32ReadPos)
        {
            u32AbailableData0 = u32WritePos - u32ReadPos;
            if (u32WritePages > 0)
                u32AbailableData1 = u32BufferSize - u32AbailableData0;
            else
                u32AbailableData1 = u32ReadPos - RingBufferIndex32(u32Hdl, INDEX_RING_BUFFER_START);
        }
        else if (u32WritePos < u32ReadPos)
        {
            u32AbailableData0 = u32BufferSize + u32WritePos - u32ReadPos;
            u32AbailableData1 = u32ReadPos - u32WritePos;
        }
        else
        {
            if ((RingBufferIndex32(u32Hdl, INDEX_STREAM_FLAG) & STREAM_FLAG_FULL) == 0)
            {
                u32AbailableData0 = 0;
                if (u32WritePages > 0)
                    u32AbailableData1 = u32BufferSize;
                else
                    u32AbailableData1 = u32ReadPos - RingBufferIndex32(u32Hdl, INDEX_RING_BUFFER_START);
            }
            else
            {
                u32AbailableData0 = u32BufferSize;
                u32AbailableData1 = 0;
            }
        }
        u64ReadPos = RingBufferIndex64(u32Hdl, INDEX_STREAM_SEEK_POS) + u32ReadPages * u32BufferSize;
        u64ReadPos = u64ReadPos + (u32ReadPos - RingBufferIndex32(u32Hdl, INDEX_RING_BUFFER_START));

        MPLAYER_MSG_TRACE("POS[0x%x][0x%x][0x%x][0x%x][0x%x]\n", u32ReadPos, u32WritePos, u32ReadPages, u32WritePages, u32BufferSize);
        MPLAYER_MSG_TRACE("AVD[0x%x][0x%x]\n", u32AbailableData1, u32AbailableData0);
        MPLAYER_MSG_TRACE("GOT[0x%x][0x%x][0x%x][0x%x]\n", (U32)(u64GotoPos>>32), (U32)(u64GotoPos), (U32)(u64ReadPos>>32), (U32)(u64ReadPos));

        if ((u64GotoPos > u64ReadPos) && (u64GotoPos <= (u64ReadPos + u32AbailableData0)))
        {
            u32ReadPos = u32ReadPos + (u64GotoPos - u64ReadPos);
            if (u32ReadPos >= RingBufferIndex32(u32Hdl, INDEX_RING_BUFFER_END))
            {
                u32ReadPos = (u32ReadPos - RingBufferIndex32(u32Hdl, INDEX_RING_BUFFER_END)) + RingBufferIndex32(u32Hdl, INDEX_RING_BUFFER_START);
                RingBufferIndex32(u32Hdl, INDEX_STREAM_READ_PAGES) = RingBufferIndex32(u32Hdl, INDEX_STREAM_READ_PAGES) + 1;
            }
            RingBufferIndex32(u32Hdl, INDEX_STREAM_READ_POS) = u32ReadPos;
            RingBufferIndex32(u32Hdl, INDEX_STREAM_FLAG) &= (~STREAM_FLAG_FULL);
        }
        else if ((u64GotoPos < u64ReadPos) && (u64GotoPos >= (u64ReadPos - u32AbailableData1)))
        {
            u32ReadPos = u32ReadPos - (u64ReadPos - u64GotoPos);
            if (u32ReadPos < RingBufferIndex32(u32Hdl, INDEX_RING_BUFFER_START))
            {
                u32ReadPos = RingBufferIndex32(u32Hdl, INDEX_RING_BUFFER_END) - (RingBufferIndex32(u32Hdl, INDEX_RING_BUFFER_START) - u32ReadPos);
                RingBufferIndex32(u32Hdl, INDEX_STREAM_READ_PAGES) = RingBufferIndex32(u32Hdl, INDEX_STREAM_READ_PAGES) - 1;
            }
            RingBufferIndex32(u32Hdl, INDEX_STREAM_READ_POS) = u32ReadPos;
            if (u32ReadPos == RingBufferIndex32(u32Hdl, INDEX_STREAM_WRITE_POS))
                RingBufferIndex32(u32Hdl, INDEX_STREAM_FLAG) |= STREAM_FLAG_FULL;
        }
        else if (u64GotoPos != u64ReadPos)
        {
            RingBufferIndex32(u32Hdl, INDEX_STREAM_READ_POS) = RingBufferIndex32(u32Hdl, INDEX_RING_BUFFER_START);    //read pos
            RingBufferIndex32(u32Hdl, INDEX_STREAM_WRITE_POS) = RingBufferIndex32(u32Hdl, INDEX_RING_BUFFER_START);    //write pos
            RingBufferIndex32(u32Hdl, INDEX_STREAM_READ_PAGES) = 0;
            RingBufferIndex32(u32Hdl, INDEX_STREAM_WRITE_PAGES) = 0;
            RingBufferIndex64(u32Hdl, INDEX_STREAM_SEEK_POS) = u64GotoPos;
            RingBufferIndex32(u32Hdl, INDEX_STREAM_FLAG) &= (~STREAM_FLAG_FULL);

            param[0] = COMMAND_TO_NETAP;
            param[1] = NETAP_COMMAND_FILE_SEEK;
            param[2] = u32Hdl;
            param[3] = option;
            msAPI_NPlayer_Query(m_u32PID[m_StrmMediaType[u32Hdl]], 4, param);
        }

        if (u64GotoPos < RingBufferIndex64(u32Hdl, INDEX_STREAM_LENGTH))
        {
            RingBufferIndex32(u32Hdl, INDEX_STREAM_FLAG) &= (~STREAM_FLAG_EOF);
        }

        block_p(semid, 0);

        MPLAYER_MSG_DBG("msAPI_NPlayer_StreamSeek_end1\n");
        return TRUE;
    }
}

static LongLong msAPI_NPlayer_StreamTell(U32 u32Hdl)
{
    U32 u32ReadPos, u32Pages;
    U64 u64SeekPos;
    LongLong u64Tell;
    EN_MPLAYER_MEDIA_TYPE eMediaType;

    if ((u32Hdl >= MPLAYER_STREAM_MAX_HANDLE) || ((eMediaType = m_StrmMediaType[u32Hdl]) >= E_MPLAYER_MEDIA_INVALID))
    {
        u64Tell.Hi = 0xFFFFFFFF;
        u64Tell.Lo = 0xFFFFFFFF;
    }
    else if ((m_eStreamMode[eMediaType] == MPLAYER_FILE_MODE) || (u32Hdl >= MPLAYER_STREAM_EX_SUB0))
    {
        off_t offset =  lseek(m_Stmfd[u32Hdl], 0, SEEK_CUR);
        u64Tell.Hi = (offset >> 32);
        u64Tell.Lo = (offset & 0xFFFFFFFF);
    }
    else
    {
        u32ReadPos = RingBufferIndex32(u32Hdl, INDEX_STREAM_READ_POS);
        u32Pages = RingBufferIndex32(u32Hdl, INDEX_STREAM_READ_PAGES);
        u64SeekPos = RingBufferIndex64(u32Hdl, INDEX_STREAM_SEEK_POS);
        u64SeekPos = u64SeekPos + u32Pages * (RingBufferIndex32(u32Hdl, INDEX_RING_BUFFER_END) - RingBufferIndex32(u32Hdl, INDEX_RING_BUFFER_START));
        u64SeekPos = u64SeekPos + (u32ReadPos - RingBufferIndex32(u32Hdl, INDEX_RING_BUFFER_START));

        u64Tell.Hi = (u64SeekPos >> 32);
        u64Tell.Lo = (u64SeekPos & 0xFFFFFFFF);
    }

    return u64Tell;
}

static LongLong msAPI_NPlayer_StreamLength(U32 u32Hdl)
{
    LongLong u64Length;
    EN_MPLAYER_MEDIA_TYPE eMediaType;

    if ((u32Hdl >= MPLAYER_STREAM_MAX_HANDLE) || ((eMediaType = m_StrmMediaType[u32Hdl]) >= E_MPLAYER_MEDIA_INVALID))
    {
        u64Length.Hi = 0;
        u64Length.Lo = 0;
    }
    else if ((m_eStreamMode[eMediaType] == MPLAYER_FILE_MODE) || (u32Hdl >= MPLAYER_STREAM_EX_SUB0))
    {
        struct stat statbuf;
        if (fstat(m_Stmfd[u32Hdl], &statbuf) < 0)
        {
            u64Length.Hi = 0;
            u64Length.Lo = 0;
        }
        else
        {
            u64Length.Hi = (U32)(statbuf.st_size >> 32);
            u64Length.Lo = (U32)(statbuf.st_size & 0xFFFFFFFF);
        }
    }
    else
    {
        u64Length.Hi = (U32)(RingBufferIndex64(u32Hdl, INDEX_STREAM_LENGTH) >> 32);
        u64Length.Lo = (U32)(RingBufferIndex64(u32Hdl, INDEX_STREAM_LENGTH) & 0xFFFFFFFF);
    }

    MPLAYER_MSG_TRACE("msAPI_NPlayer_StreamLength(%d, 0x%x, 0x%x)\n", u32Hdl, u64Length.Hi, u64Length.Lo);
    return u64Length;
}

static U32 msAPI_NPlayer_StreamRead(U32 u32Hdl, void *pBuffAddr, U32 u32Length)
{
    U32 u32Buffer = (U32)pBuffAddr;
    EN_MPLAYER_MEDIA_TYPE eMediaType;

    if ((m_eDebugLevle >= MPLAYER_DBG_LEVEL_TRACE) || (m_eMplayerState[E_MPLAYER_MEDIA_MOVIE] == MPLAYER_STATE_INIT))
    {
        MPLAYER_MSG_DBG("msAPI_NPlayer_StreamRead_before(%d, 0x%x, 0x%x)[%d]\n", u32Hdl, u32Buffer, u32Length, g_bNonBlockingRead);
    }

    if ((u32Hdl >= MPLAYER_STREAM_MAX_HANDLE) || ((eMediaType = m_StrmMediaType[u32Hdl]) >= E_MPLAYER_MEDIA_INVALID))
    {
        return u32Length;
    }

    if ((m_eStreamMode[eMediaType] == MPLAYER_FILE_MODE) || (u32Hdl >= MPLAYER_STREAM_EX_SUB0))
    {
        int rdCnt = read(m_Stmfd[u32Hdl], (void*)_PA2VA(u32Buffer), u32Length);
        if ((m_eDebugLevle >= MPLAYER_DBG_LEVEL_TRACE) || (m_eMplayerState[E_MPLAYER_MEDIA_MOVIE] == MPLAYER_STATE_INIT))
        {
            MPLAYER_MSG_DBG("msAPI_NPlayer_StreamRead_end0(0x%x, 0x%x)\n", rdCnt, u32Length - rdCnt);
        }
        if (rdCnt < 0)
        {
            return u32Length;
        }
        else
        {
            return u32Length - rdCnt;
        }
    }
    else
    {
        BOOLEAN bExitRead = FALSE;
        U32 u32ReadSize = 0;
        U32 u32ReadTotal = 0;
        U32 u32ReadPos = 0;
        U32 u32WritePos = 0;
        U32 u32ReadTimerOut;
        U32 u32ReadTimer = MsOS_GetSystemTime();
        if (m_eMplayerState[eMediaType] == MPLAYER_STATE_INIT)
            u32ReadTimerOut = m_u32VdplayerReadTimerOut;
        else
            u32ReadTimerOut = 200;

        if (m_bLessDataSize)
        {
            if ((MApp_VDPlayer_Get_Buffer_Info((EN_BUFFER_INFO_INDEX) 3) == 0) &&
                ((msAPI_Timer_GetTime0()-m_u32StartPlayTimer) < 4500) &&
                (m_StrmMediaType[u32Hdl] == E_MPLAYER_MEDIA_MOVIE) &&
                (m_eMplayerState[E_MPLAYER_MEDIA_MOVIE] < MPLAYER_STATE_PLAYING) &&
                (m_u32ReadTotalSize >= m_u32InitDataSize))
            {
                return u32Length;
            }
        }

        while ((u32ReadTotal < u32Length) && (bExitRead == FALSE) && (((U32)MsOS_GetSystemTime()-u32ReadTimer) < u32ReadTimerOut) && (m_Stmfd[u32Hdl] != -1))
        {
            u32ReadSize = 0;
            u32ReadPos = RingBufferIndex32(u32Hdl, INDEX_STREAM_READ_POS);
            u32WritePos = RingBufferIndex32(u32Hdl, INDEX_STREAM_WRITE_POS);

            if (u32ReadPos < u32WritePos)
            {
                u32ReadSize = u32WritePos - u32ReadPos;
            }
            else if (u32ReadPos > u32WritePos)
            {
                u32ReadSize = RingBufferIndex32(u32Hdl, INDEX_RING_BUFFER_END) - u32ReadPos;
            }
            else if ((RingBufferIndex32(u32Hdl, INDEX_STREAM_FLAG) & STREAM_FLAG_FULL) == STREAM_FLAG_FULL)
            {
                u32ReadSize = RingBufferIndex32(u32Hdl, INDEX_RING_BUFFER_END) - u32ReadPos;
            }
            else   //ring buffer empty
            {
                LongLong lSzie;
                U64 u64SeekPos, u64FileLength;

                u64FileLength = RingBufferIndex64(u32Hdl, INDEX_STREAM_LENGTH);
                lSzie = msAPI_NPlayer_StreamTell(u32Hdl);
                u64SeekPos = ((U64)lSzie.Hi << 32) + lSzie.Lo;

                if (u64SeekPos >= u64FileLength)
                {
                    MPLAYER_MSG_MUST("Reach file end!\n");
                    bExitRead = TRUE;
                }
            }

            if (u32ReadSize > 0)
            {
                if ((u32ReadTotal + u32ReadSize) > u32Length)
                {
                    u32ReadSize = u32Length - u32ReadTotal;
                }
                memcpy((void*)_PA2VA(u32Buffer), (void*)_PA2VA(u32ReadPos), u32ReadSize);
                MPLAYER_MSG_TRACE("memcpy(0x%x)(0x%x)(0x%x)\n", u32Buffer, u32ReadPos, u32ReadSize);
                u32Buffer += u32ReadSize;
                u32ReadPos += u32ReadSize;
                if (u32ReadPos >= RingBufferIndex32(u32Hdl, INDEX_RING_BUFFER_END))
                {
                    u32ReadPos = u32ReadPos - RingBufferIndex32(u32Hdl, INDEX_RING_BUFFER_END) + RingBufferIndex32(u32Hdl, INDEX_RING_BUFFER_START);
                    RingBufferIndex32(u32Hdl, INDEX_STREAM_READ_PAGES) = RingBufferIndex32(u32Hdl, INDEX_STREAM_READ_PAGES) + 1;
                }
                block_v(semid, 0);
                RingBufferIndex32(u32Hdl, INDEX_STREAM_READ_POS) = u32ReadPos;
                RingBufferIndex32(u32Hdl, INDEX_STREAM_FLAG) &= (~STREAM_FLAG_FULL);
                block_p(semid, 0);
                u32ReadTotal += u32ReadSize;
            }
            usleep(1000);
        }

        m_u32ReadTotalSize += u32ReadTotal;
        if ((m_eDebugLevle >= MPLAYER_DBG_LEVEL_TRACE) || (m_eMplayerState[E_MPLAYER_MEDIA_MOVIE] == MPLAYER_STATE_INIT))
        {
            MPLAYER_MSG_DBG("msAPI_NPlayer_StreamRead_end1(0x%x)(0x%x)[%d]\n", (u32Length - u32ReadTotal), m_u32ReadTotalSize, MApp_VDPlayer_Get_Buffer_Info((EN_BUFFER_INFO_INDEX) 3));
        }
        return (u32Length - u32ReadTotal);  //return left unread
    }
}

//-----------------------------------------------------------------------------
static void _msAPI_NPlayer_SetMusicShareMem(U8 u8Index, U8* ptr, U32 u32size)
{
    if(ptr!= NULL && u32size > 0)
    {
        memcpy((U8 *)_PA2VA(m_u32MusicShareMemAddr+u8Index), ptr, u32size);
    }
}

static void* _msAPI_NPlayer_GetMusicShareMem(U8 u8Index)
{
    return (void *)_PA2VA(m_u32MusicShareMemAddr+u8Index);
}


static BOOLEAN _msAPI_NPlayer_Music_Lyric_Parser(void)
{
    U8 *pu8Data;
    U32 u32FileSize,u32ReadSize;
    U32 u32StreamHandleIdx_LRC;

    MApp_Music_LyricInit();

    if(INVALID_DATA_STREAM_HDL == (u32StreamHandleIdx_LRC = msAPI_DataStreamIO_Open(NULL, OPEN_MODE_FOR_READ, E_DATA_STREAM_TYPE_LYRIC)))
    {
        goto _msAPI_NPlayer_Music_Lyric_Parser_END;
    }
    u32FileSize = msAPI_DataStreamIO_Length(u32StreamHandleIdx_LRC);
    if(u32FileSize == 0)
    {
        goto _msAPI_NPlayer_Music_Lyric_Parser_END;
    }

    // Read file.
    msAPI_DataStreamIO_Seek(u32StreamHandleIdx_LRC,0,E_DATA_STREAM_SEEK_SET);
    u32ReadSize = MIN(u32FileSize+512, MUSIC_LYRIC_BUFFER_LEN);
    if(u32ReadSize == msAPI_DataStreamIO_Read(u32StreamHandleIdx_LRC, (void*)((MUSIC_LYRIC_BUFFER_MEMORY_TYPE & MIU1) ? (MUSIC_LYRIC_BUFFER_ADR | MIU_INTERVAL) : (MUSIC_LYRIC_BUFFER_ADR)),u32ReadSize))
    {
        goto _msAPI_NPlayer_Music_Lyric_Parser_END;
    }

    pu8Data = (U8*)_PA2VA(((MUSIC_LYRIC_BUFFER_MEMORY_TYPE & MIU1) ? (MUSIC_LYRIC_BUFFER_ADR | MIU_INTERVAL) : (MUSIC_LYRIC_BUFFER_ADR)));
    if(pu8Data[0]==0xFF && pu8Data[1]==0xFE)
    {
        m_bIsLyricUnicode = TRUE;   //EN_TEXT_UNIS
    }
    else
    {
        m_bIsLyricUnicode = FALSE;
    }

    //now _msAPI_NPlayer_GetLyric will help to convert to unicode, so temparally set into unicode
    m_eMusicLyricEncode = MPLAYER_LYRIC_ENCODE_UNIS;

    if(MApp_Music_LRC_Lyrics_Parser(u32FileSize))
    {
        msAPI_DataStreamIO_Close(u32StreamHandleIdx_LRC);
        return TRUE;
    }

_msAPI_NPlayer_Music_Lyric_Parser_END:
    if(INVALID_DATA_STREAM_HDL != u32StreamHandleIdx_LRC)
    {
        msAPI_DataStreamIO_Close(u32StreamHandleIdx_LRC);
    }

    return FALSE;
}

static void _msAPI_NPlayer_GetLyric(U16 u16LyricPos, U8 *pu8Dst)
{
    U16 u16Src, u16Dst;
    U16 u16Data;
    U8 *pu8Src;

    pu8Src = (U8*)_PA2VA((((MUSIC_LYRIC_BUFFER_MEMORY_TYPE & MIU1) ? (MUSIC_LYRIC_BUFFER_ADR | MIU_INTERVAL) : (MUSIC_LYRIC_BUFFER_ADR))+u16LyricPos));
    for(u16Dst=0,u16Src=0;u16Dst<LYRIC_MAX_SIZE-2;)
    {
        if(m_bIsLyricUnicode)
        {
            memcpy(&u16Data,&pu8Src[u16Src],2);

            if(u16Data == '\r' || u16Data == '\n')
            {
                pu8Dst[u16Dst] = '\0';
                pu8Dst[u16Dst+1] = '\0';
                break;
            }
            else
            {
                memcpy(&pu8Dst[u16Dst], &u16Data, 2);
            }
            u16Dst+=2;
            u16Src+=2;
        }
        else
        {
            if(isprint(pu8Src[u16Src]))
            {
                pu8Dst[u16Dst] = pu8Src[u16Src];
                pu8Dst[u16Dst+1] = '\0';
                u16Dst+=2;
            }
            else if(pu8Src[u16Src] == '\0')
            {
                pu8Dst[u16Dst] = '\0';
                pu8Dst[u16Dst+1] = '\0';
                break;
            }
            else if(pu8Src[u16Src] == '\r' || pu8Src[u16Src] == '\n')
            {
                pu8Dst[u16Dst] = '\0';
                pu8Dst[u16Dst+1] = '\0';
                break;
            }
            else
            {   // It is GB code.
                u16Data = ((pu8Src[u16Src+1]) | ((pu8Src[u16Src])<<8));
                u16Data = MApp_Transfer2Unicode(u16Data);
                memcpy(&pu8Dst[u16Dst], &u16Data, 2);
                u16Dst+=2;
                u16Src++;
            }
            u16Src++;
        }
    }

    pu8Dst[LYRIC_MAX_SIZE-1] = '\0';
    pu8Dst[LYRIC_MAX_SIZE-2] = '\0';

}

//-----------------------------------------------------------------------------
static void _msAPI_NPlayer_NotifyMusicLyric(BOOLEAN bShowLyric, U32 u32TextDataAddress, U16 u16Len)
{
    U8 param[16];
    UNUSED(u16Len);

    MPLAYER_MSG_INFO("NotifyLyric[%d][%d][%x]\n", bShowLyric, m_eMusicLyricEncode, u32TextDataAddress);
    if (bShowLyric == FALSE)
    {
        u32TextDataAddress = 0;
    }
    param[0] = COMMAND_TO_NETAP;
    param[1] = NETAP_COMMAND_MUSIC_LYRIC;
    param[2] = m_eMusicLyricEncode;
    param[3] = u32TextDataAddress&0xFF;
    param[4] = (u32TextDataAddress>>8)&0xFF;
    param[5] = (u32TextDataAddress>>16)&0xFF;
    param[6] = (u32TextDataAddress>>24)&0xFF;
    msAPI_NPlayer_Signal(m_u32PID[E_MPLAYER_MEDIA_MUSIC], 7, param);
}

static EN_MPLAYER_SUB_TYPE _msAPI_NPlayer_VerifyMusicType(FileEntry *pEntry,EN_MPLAYER_SUB_TYPE enMusicType)
{
    U8 *pFileBufPtr;
    U32 u32FileHandle,u16Mp3HeaderOffset,u32Delta,u32Offset = 0,i,u32TagSize = 0,u32FileSize;;
    U32 u32FileBuffAddr = ((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (MP3_INFO_READ_ADR | MIU_INTERVAL) : (MP3_INFO_READ_ADR));


    if(enMusicType == MPLAYER_SUBTYPE_PCM)
    {
        MPLAYER_MSG_MUST("It is PCM file\n");
        return enMusicType;
    }

    u32FileHandle = msAPI_DataStreamIO_Open(pEntry, OPEN_MODE_FOR_READ,E_DATA_STREAM_TYPE_MUSIC);
    if(u32FileHandle == INVALID_DATA_STREAM_HDL)
    {
        MPLAYER_MSG_ERR("Open file failed\n");
        return enMusicType;
    }
    u32FileSize = msAPI_DataStreamIO_Length(u32FileHandle);
    msAPI_DataStreamIO_Seek(u32FileHandle, 0,E_DATA_STREAM_SEEK_SET);
    msAPI_DataStreamIO_Read(u32FileHandle, (void*)u32FileBuffAddr, FAT_SECTOR_SIZE_512BYTE * 8); // 4k is xdata window size


    pFileBufPtr = (U8 *)_PA2VA(u32FileBuffAddr);

    // if has ID3 v2,skip it.
    if ((pFileBufPtr[0] == 'I') && (pFileBufPtr[1] == 'D') && (pFileBufPtr[2] == '3'))
    {
        MPLAYER_MSG_INFO("\nskip ID3 tag\n");
        u32TagSize = (U32) (pFileBufPtr[6] & 0x7F);
        u32TagSize <<= 7;
        u32TagSize |= (U32) (pFileBufPtr[7] & 0x7F);
        u32TagSize <<= 7;
        u32TagSize |= (U32) (pFileBufPtr[8] & 0x7F);
        u32TagSize <<= 7;
        u32TagSize |= (U32) (pFileBufPtr[9] & 0x7F);
        u32Offset = u32TagSize + 10;
        if(u32Offset != 0) //Fix double ID3 tag
        {
            msAPI_DataStreamIO_Seek(u32FileHandle, u32Offset,E_DATA_STREAM_SEEK_SET);
            msAPI_DataStreamIO_Read(u32FileHandle, (void*)u32FileBuffAddr, FAT_SECTOR_SIZE_512BYTE * 8); // 4k is xdata window size

            pFileBufPtr = (U8 *)_PA2VA(u32FileBuffAddr);
            if ((pFileBufPtr[0] == 'I') && (pFileBufPtr[1] == 'D') && (pFileBufPtr[2] == '3'))
            {
                MPLAYER_MSG_INFO("two ID3 tag\n");
                u32TagSize = (U32) (pFileBufPtr[6] & 0x7F);
                u32TagSize <<= 7;
                u32TagSize |= (U32) (pFileBufPtr[7] & 0x7F);
                u32TagSize <<= 7;
                u32TagSize |= (U32) (pFileBufPtr[8] & 0x7F);
                u32TagSize <<= 7;
                u32TagSize |= (U32) (pFileBufPtr[9] & 0x7F);
                u32Offset += (u32TagSize + 10);
            }
        }
    }

    msAPI_DataStreamIO_Seek(u32FileHandle, u32Offset & (~(FAT_SECTOR_SIZE_512BYTE - 1)),E_DATA_STREAM_SEEK_SET);
    u32Delta = u32Offset & (FAT_SECTOR_SIZE_512BYTE - 1);
    msAPI_DataStreamIO_Read(u32FileHandle, (void*)u32FileBuffAddr, FAT_SECTOR_SIZE_512BYTE * 8);

    pFileBufPtr = (U8*)_PA2VA(u32FileBuffAddr+u32Delta);

    //check whether it is  WAV file
    if((pFileBufPtr[0] == 'R') && (pFileBufPtr[1] == 'I') &&  (pFileBufPtr[2] == 'F') && (pFileBufPtr[3] == 'F'))
    {
        if((pFileBufPtr[8] == 'W') && (pFileBufPtr[9] == 'A') &&
            (pFileBufPtr[10] == 'V') && (pFileBufPtr[11] == 'E'))
        {
            MPLAYER_MSG_MUST("It is WAV file\n");
            enMusicType = MPLAYER_SUBTYPE_WAV;   // it is WAV file
            goto _msAPI_NPlayer_VerifyMusicType_end;
        }
    }

    //check whether it is  WMA file
    if(u32FileSize >= 4096)
    {
        for(i=0;i<4080;i++)    //4096-16
        {
            if((pFileBufPtr[i]==0x30)&&(pFileBufPtr[i+1]==0x26)&&(pFileBufPtr[i+2]==0xB2)&&(pFileBufPtr[i+3]==0x75)&&
                (pFileBufPtr[i+4]==0x8E)&&(pFileBufPtr[i+5]==0x66)&&(pFileBufPtr[i+6]==0xCF)&&(pFileBufPtr[i+7]==0x11)&&
                (pFileBufPtr[i+8]==0xA6)&&(pFileBufPtr[i+9]==0xD9)&&(pFileBufPtr[i+10]==0x00)&&(pFileBufPtr[i+11]==0xAA)&&
                (pFileBufPtr[i+12]==0x00)&&(pFileBufPtr[i+13]==0x62)&&(pFileBufPtr[i+14]==0xCE)&&(pFileBufPtr[i+15]==0x6C)
            )
            {
                MPLAYER_MSG_MUST("It is WMA file\n");
                enMusicType = MPLAYER_SUBTYPE_WMA;   // it is WMA file
                goto _msAPI_NPlayer_VerifyMusicType_end;
            }
        }
    }

     //check whether it is AAC file
    if((pFileBufPtr[4] == 'f') && (pFileBufPtr[5] == 't') && (pFileBufPtr[6] == 'y') && (pFileBufPtr[7] == 'p'))
    {
        //AAC M4A file
        MPLAYER_MSG_MUST("It is AAC M4A file\n");
        enMusicType = MPLAYER_SUBTYPE_AAC;
        goto _msAPI_NPlayer_VerifyMusicType_end;
    }
    else if((pFileBufPtr[0] == 'A') && (pFileBufPtr[1] == 'D') && (pFileBufPtr[2] == 'I') && (pFileBufPtr[3] == 'F'))
    {
        //ADIF file
        MPLAYER_MSG_MUST("It is AAC ADIF file\n");
        enMusicType = MPLAYER_SUBTYPE_AAC;
        goto _msAPI_NPlayer_VerifyMusicType_end;
    }
    else if((pFileBufPtr[0] == 0xFF)&&((pFileBufPtr[1] & 0xF6) == 0xF0))
    {
        //ADTS file
        MPLAYER_MSG_MUST("It is AAC ADTS file\n");
        enMusicType = MPLAYER_SUBTYPE_AAC;
        goto _msAPI_NPlayer_VerifyMusicType_end;
    }

    //check whether it is mp3
    if(u32FileSize >= (4096 + u32TagSize))
    {
        // Seek the file to find the MP3 header, max seek 4096 bytes
        u16Mp3HeaderOffset = 0;

        while((!(pFileBufPtr[u16Mp3HeaderOffset] == 0xff &&
                (pFileBufPtr[u16Mp3HeaderOffset+1] & 0xe0) == 0xe0))
            &&((u16Mp3HeaderOffset+u32Delta)<0xFFE))
        {
            u16Mp3HeaderOffset++;
        }

        if (pFileBufPtr[u16Mp3HeaderOffset] == 0xff && (pFileBufPtr[u16Mp3HeaderOffset+1] & 0xe0) == 0xe0)
        {
            MPLAYER_MSG_MUST("It is mp3 file\n");
            enMusicType = MPLAYER_SUBTYPE_MP3;   // it is MP3 file
            goto _msAPI_NPlayer_VerifyMusicType_end;
        }
    }

    MPLAYER_MSG_MUST("can not find match type, return type according file ext\n");

_msAPI_NPlayer_VerifyMusicType_end:
    msAPI_DataStreamIO_Close(u32FileHandle);
    return enMusicType;
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Check how many slots left for next photo decode.
    Photo decode is possible only when the return value of this function greater
    than 0.

    \param None

    \return
        Photo slot left for next decode procedure. */
///////////////////////////////////////////////////////////////////////////////
static U32 _msAPI_NPlayer_Photo_GetFreeSlot(void)
{
    U32 u32Idx, u32Cnt;

    for (u32Idx = 0, u32Cnt = 0; u32Idx < PHOTO_TOTAL_SLOT; u32Idx++)
    {
        MPLAYER_MSG_DBG("Get _gePhoto_State[%d]:%d\n",u32Idx,_gePhoto_State[u32Idx]);
        if (_gePhoto_State[u32Idx] == E_PHOTO_SLOT_STATE_FREE)
        {
            u32Cnt++;
        }
    }

    return u32Cnt;
}

static EN_PHOTO_ZOOMING _msAPI_NPlayer_Photo_TransformZoomFactor(E_ZOOM eDmZoom)
{
    // transform zoom factor
    switch (eDmZoom)
    {
        case E_ZOOM_1_DIV_8:
            return EN_PHOTO_ZOOM_1_8;

        case E_ZOOM_1_DIV_4:
            return EN_PHOTO_ZOOM_1_4;

        case E_ZOOM_1_DIV_2:
            return EN_PHOTO_ZOOM_1_2;

        case E_ZOOM_1:
            return EN_PHOTO_ZOOM_1;

        case E_ZOOM_2:
            return EN_PHOTO_ZOOM_2;

        case E_ZOOM_4:
            return EN_PHOTO_ZOOM_4;

        case E_ZOOM_8:
            return EN_PHOTO_ZOOM_8;

        default:
            break;
    }

    return EN_PHOTO_ZOOM_NOT_SUPPORT;
}

static EN_PHOTO_DIRECTION _msAPI_NPlayer_Photo_TransformDirection(E_DIRECTION eDirection)
{
    // transform move direction
    switch (eDirection)
    {
        case E_DIRECTION_UP:
            return EN_PHOTO_MOVE_UP;

        case E_DIRECTION_DOWN:
            return EN_PHOTO_MOVE_DOWN;

        case E_DIRECTION_LEFT:
            return EN_PHOTO_MOVE_LEFT;

        case E_DIRECTION_RIGHT:
            return EN_PHOTO_MOVE_RIGHT;

        default:
            break;
    }

    return EN_PHOTO_MOVE_NOT_SUPPORT;
}

static EN_PHOTO_ROTATION _msAPI_NPlayer_Photo_TransformRotation(E_ROTATION eRotation)
{
    // transform rotation
    switch (eRotation)
    {
        case E_ROTATION_0:
            return EN_PHOTO_ROTATE_0;

        case E_ROTATION_90:
            return EN_PHOTO_ROTATE_90;

        case E_ROTATION_180:
            return EN_PHOTO_ROTATE_180;

        case E_ROTATION_270:
            return EN_PHOTO_ROTATE_270;

        default:
            break;
    }

    return EN_PHOTO_ROTATE_NOT_SUPPORT;
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Disable photo displaying.

    \param None

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
static BOOLEAN _msAPI_NPlayer_Photo_StopDisplay(void)
{
    U8 u8Idx;

    msAPI_Scaler_SetBlueScreen(TRUE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    MApi_XC_GenerateBlackVideo(ENABLE, MAIN_WINDOW);
    MDrv_MVOP_Enable(FALSE);
#if(ENABLE_MIU_1 == ENABLE)
    MDrv_MVOP_MiuSwitch(1);
#endif
    MApp_Photo_SlideShow(TRUE);

    for (u8Idx = 0; u8Idx < PHOTO_TOTAL_SLOT; u8Idx++)
    {
        _gePhoto_State[u8Idx] = E_PHOTO_SLOT_STATE_FREE;

        _gu16Photo_Wdith[u8Idx]     = 0;
        _gu16Photo_Height[u8Idx]    = 0;
        _gu32Photo_Size[u8Idx]      = 0;
    }
    _gu8Photo_DecodeIdx = 0;
    _gu8Photo_DisplayIdx = 0;

    return TRUE;
}

static BOOLEAN _msAPI_NPlayer_GB2Unicode(U8 *pu8SrcString, U8 *pu8DstString, U16 u16StringMax)
{
    U16 u16SrcIdx, u16DstIdx;
    U16 pu16StrSrcTemp, pu16StrDstTemp;

    u16SrcIdx = 0;
    u16DstIdx = 0;
    while(u16SrcIdx < u16StringMax)
    {
        if(isprint(pu8SrcString[u16SrcIdx]))
        {
            pu8DstString[u16DstIdx] = pu8SrcString[u16SrcIdx];
            pu8DstString[u16DstIdx+1] = '\0';
            u16SrcIdx++;
            u16DstIdx+=2;
        }
        else if(pu8SrcString[u16SrcIdx] == '\0')
        {
            pu8DstString[u16DstIdx] = '\0';
            pu8DstString[u16DstIdx+1] = '\0';
            u16SrcIdx++;
            u16DstIdx+=2;
            break;
        }
        else
        {
            memcpy(&pu16StrSrcTemp,&pu8SrcString[u16SrcIdx],2);
            pu16StrSrcTemp=Swap16(pu16StrSrcTemp);
            pu16StrDstTemp = MApp_Transfer2Unicode(pu16StrSrcTemp);
            memcpy(&pu8DstString[u16DstIdx],&pu16StrDstTemp,2);
            u16SrcIdx+=2;
            u16DstIdx+=2;
        }
    }
    return TRUE;
}

static void _msAPI_NPlayer_ConvertMusicString2Unicode(U8 *pu8SrcString, U16 *pu16DstString, U16 u32StrLen)
{
    if (pu8SrcString != NULL && pu16DstString != NULL)
    {
        memset((U8*)pu16DstString,0,u32StrLen*2);

        if(pu8SrcString[0]==0x00)
        {
            // TODO: fix me!!
            _msAPI_NPlayer_GB2Unicode(pu8SrcString+1, (U8*)pu16DstString, u32StrLen-2); // [u8Length-2] = 0 , [u8Length-1]=0  String end
        }
        else if(pu8SrcString[0]==0x03)
        {
            msAPI_OCP_MappinUTF8ToUCS2((U8*)(pu8SrcString+1), pu16DstString, (U16)(u32StrLen-1), (U16)(u32StrLen-1));
        }
        else //if(pu8Data[0]==0x01)
        {
            memcpy((U8*)pu16DstString, pu8SrcString+1, u32StrLen-2);  // [u8Length-2] = 0 , [u8Length-1]=0  String end
        }

        #if 0
        U32 i;

        for(i=0;i<u32StrLen;i++)
        {
            MPLAYER_MSG_TRACE("%x-->%x\n",pu8SrcString[i],pu16DstString[i]);
        }
        #endif
    }
}

static void _msAPI_NPlayer_MovieCancelRepeatAB(void)
{
    m_enRpeatABMode = REPEATAB_MODE_NONE;
    m_u32MovieRepeatTime[0]= 0xFFFFFFFF;
    m_u32MovieRepeatTime[1] = 0xFFFFFFFF;
    MApp_VDPlayer_SetRepeatAB(SET_REPEAT_AB_NONE);
}

static void _msAPI_NPlayer_ReinitRepeatABSubtitle(void)
{
    MApp_VDPlayer_TextSubtitleInit();
    m_bNewRepeatABLoop = FALSE;
}

static BOOLEAN _msAPI_NPlayer_GenCaptureFileName(U8 *pFileName, U16 u16FileNameLen)
{
    U16 u16CaptureIdx = 1;
    U16 i = strlen(m_pName);
    char PathName[FULLPATH_NAME_SIZE];

    // find first '/'
    while(m_pName[--i] != '/');
    memset(PathName, 0, FULLPATH_NAME_SIZE);
    memcpy(PathName, m_pName, i);

    if (pFileName == NULL)
    {
        __ASSERT(0);
        return FALSE;
    }
    memset(pFileName, 0, u16FileNameLen);

    do
    {
        if (u16CaptureIdx == 65000)
        { // maximum captured number
            snprintf((char*)pFileName, u16FileNameLen, "/CAP%06d.JPG", u16CaptureIdx);
            return FALSE;
        }

        snprintf((char*)pFileName, u16FileNameLen, "%s/CAP%06d.JPG", PathName, u16CaptureIdx++);

    } while (access((char*)pFileName, 0) == 0);

    return TRUE;
}

//-----------------------------------------------------------------------------
static BOOLEAN msAPI_NPlayer_ForceStop(EN_VDPLAYER_FORCE_STOP eType)
{
    U32 u32TimerOut;

    msAPI_NPlayer_Polling();
    if (m_eMplayerState[E_MPLAYER_MEDIA_MOVIE] == MPLAYER_STATE_STANDBY)
    {
        m_u8ForceStop = 1;
        return TRUE;
    }

    MAdp_IR_MStarFantasy_Polling();
    MApp_ProcessUserInput();
    if ((u8KeyCode == KEY_STOP) || (u8KeyCode == KEY_EXIT))
    {
        MPLAYER_MSG_INFO("ForceStop(%d)\n", u8KeyCode);
        u8KeyCode = KEY_NULL;
        m_u8ForceStop = 2;
        return TRUE;
    }

    if (eType == E_FORCE_STOP_INIT)
    {
        if ((m_eStreamMode[E_MPLAYER_MEDIA_MOVIE] == MPLAYER_UNSEEKABLE_STREAM_MODE) || (m_eStreamMode[E_MPLAYER_MEDIA_MOVIE] == MPLAYER_SEEKABLE_STREAM_MODE))
            u32TimerOut = m_u32VdplayerInitTimerOut * 4;
        else
            u32TimerOut = m_u32VdplayerInitTimerOut;

        if (msAPI_Timer_DiffTimeFromNow(m_u32VdplayerInitStartTimer) >= u32TimerOut)
        {
            MPLAYER_MSG_INFO("StopInit(%d)\n", msAPI_Timer_DiffTimeFromNow(m_u32VdplayerInitStartTimer));
            return TRUE;
        }
    }

    usleep(2*1000);
    return FALSE;
}

static void msAPI_NPlayer_Init(void)
{
    U8 i, *ptr;
    U32 u32Aligned, u32MIU;

    MPLAYER_MSG_MUST("msAPI_NPlayer_Init(%s)(%d)\n", IPC_VERSION, m_u32NplayerCnt);
    MPLAYER_MSG_MUST("Date[%s/", __DATE__);
    MPLAYER_MSG_MUST("%s]\n", __TIME__);

    //-------------------------------------------------------------------------
    if (m_u32NplayerCnt == 0)
    {
        m_u32IPCErrCnt = 0;
        m_bNplayerRun = TRUE;
        m_bKTVMode = FALSE;
        m_bRtspFreeze = FALSE;
        m_u32VdplayerInitTimerOut = 15000;
        m_u32VdplayerReadTimerOut = 500;
        m_s32MaxBufferSec = 30;
        m_s32MinBufferSec = 10;
        m_u32InitDataSize = 0x20000;
        m_bLessDataSize = FALSE;
        m_eExternalSubtitleType = E_MPLAYER_SUBTITLE_INVALID;
        m_bNotSupportStreamLen = FALSE;
        m_u8TransmitKey = E_TRANSMIT_KEY_NULL;
        for (i = E_MPLAYER_MEDIA_MIN; i < E_MPLAYER_MEDIA_NUM; i++)
        {
            m_bNplayerPlay[i] = FALSE;
            m_eMplayerState[i] = MPLAYER_STATE_STANDBY;
            m_eStreamMode[i] = MPLAYER_FILE_MODE;
            m_u32RingBufferNum[i] = 0;
        }
        for( i = 0; i < MPLAYER_STREAM_MAX_HANDLE; i++)
        {
            m_StrmMediaType[i] = E_MPLAYER_MEDIA_INVALID;
            m_Stmfd[i] = -1;
        }
        for (i = 0; i < E_DATA_STREAM_TYPE_NUM; i++)
        {
            m_StmHdl[i] = INVALID_DATA_STREAM_HDL;
        }

        u32LoopTimer[0] = u32LoopTimer[1] = 0;
        u32TaskLoopCnt = 0;
        u32TaskLoopMax[0] = u32TaskLoopMax[1] = u32TaskLoopMax[2] = 0;

        memset(&gstVidStatus, 0, sizeof(VDEC_DispInfo));
        memset(&gstPreVidStatus, 0, sizeof(VDEC_DispInfo));
        stSystemInfo[MAIN_WINDOW].enAspectRatio = MApp_Scaler_GetAspectRatio(MAIN_WINDOW,ST_VIDEO.eAspectRatio);
        MPLAYER_MSG_INFO("ASPECT_RATIO[%d][%d]\n", ST_VIDEO.eAspectRatio, stSystemInfo[MAIN_WINDOW].enAspectRatio);

        m_StreamIOFunc.pfnOpen = msAPI_NPlayer_StreamOpen;
        m_StreamIOFunc.pfnClose = msAPI_NPlayer_StreamClose;
        m_StreamIOFunc.pfnRead = msAPI_NPlayer_StreamRead;
        m_StreamIOFunc.pfnSeek = msAPI_NPlayer_StreamSeek;
        m_StreamIOFunc.pfnTell = msAPI_NPlayer_StreamTell;
        m_StreamIOFunc.pfnLength = msAPI_NPlayer_StreamLength;
        msAPI_DataStreamIO_OptionRegistation(&m_StreamIOFunc);

        MAdp_SYS_GetMemoryInfo("EPGEXTDB_SDRAM", (MS_U32*)&m_u32RingBufferHead, (MS_U32*)&m_u32RingBufferLength, (MS_U32*)&u32Aligned, (MS_U32*)&u32MIU);
        MPLAYER_MSG_INFO("RING_BUFFER:[%x][%x][%x][%x]\n", m_u32RingBufferHead, m_u32RingBufferLength, u32Aligned, u32MIU);
        MAdp_SYS_GetMemoryInfo("MPLAYER_MOVIE_PLAYLIST", (MS_U32*)&m_u32MusicShareMemAddr, (MS_U32*)&m_u32MusicShareMemLength, (MS_U32*)&u32Aligned, (MS_U32*)&u32MIU);
        MPLAYER_MSG_INFO("MUSIC_SHM:[%x][%x][%x][%x]\n", m_u32MusicShareMemAddr, m_u32MusicShareMemLength, u32Aligned, u32MIU);

        ptr = m_pShmAddr+MPLAYER_SHM_VIDEO_INFO;
        SETU32(ptr, 0, VDPLAYER_SHAREMEM_ADDR);
        for (i = 0; i < MPLAYER_VIDEO_INFO_NUM; i++)
        {
            SETU16(ptr, 2*i+4, m_u16VideoShareMemIndex[i]);
        }

        //MDrv_AUDIO_Close();

        //for zmplayer bw issue
        m_u8BakReg0640 = MDrv_ReadByte(0x100640);
        m_u8BakReg0642 = MDrv_ReadByte(0x100642);
        MDrv_WriteByte(0x100640, m_u8BakReg0640|0x04);
        MDrv_WriteByte(0x100642, m_u8BakReg0642|0x02);

        //Patch Mvop lead ap osd to disapear
        U8 temp = MDrv_ReadByte(0x100661) | 0x80;
        MDrv_WriteByte(0x100661, temp);

        //-------------------------------------------------------------------------
        //patch for chakra OSD shift left in AP
        //-------------------------------------------------------------------------
        MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD);
	MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_OSD, E_GOP_DST_OP0, 0, 0, 1366, 768);

        //-------------------------------------------------------------------------
        //patch for zmplayer movie no sound
        //-------------------------------------------------------------------------
        MApi_AUDIO_SetCommand(MSAPI_AUD_DVB2_DECCMD_STOP);
        MApi_AUDIO_SetSystem(MSAPI_AUD_DVB2_NONE);
        MApi_AUDIO_SetSystem(MSAPI_AUD_DVB2_MP3);

        //-------------------------------------------------------------------------
        //copy code from _MApp_DMP_Switch2Dmp()
        //-------------------------------------------------------------------------
        MApi_AUDIO_AbsoluteBass(0);  // set the bass to 0 to avoid voice broken

        // reset photo specific vairables
        _gu8Photo_DecodeIdx     = 0;
        _gu8Photo_DisplayIdx    = 0;
        m_bFullScreen = TRUE;

        _gu16Photo_SlideShowTimeOutInSec    = PHOTO_SLIDESHOW_TIME_OUT;
        _gePhoto_SlideShowPauseState        = E_PHOTO_SLIDE_SHOW_FREE_RUN;
        for (i = 0; i < PHOTO_TOTAL_SLOT; i++)
        {
            _gePhoto_State[i] = E_PHOTO_SLOT_STATE_FREE;

            _gu16Photo_Wdith[i]  = 0;
            _gu16Photo_Height[i] = 0;
            _gu32Photo_Size[i]   = 0;
        }

        m_enRpeatABMode = REPEATAB_MODE_NONE;
        m_u32MovieRepeatTime[0]= 0xFFFFFFFF;
        m_u32MovieRepeatTime[1] = 0xFFFFFFFF;
        _msAPI_NPlayer_ReinitRepeatABSubtitle();
    #if SEAMLESS_PLAYING_ENABLE
        MApp_VDPlayer_EnableSeamless(FALSE);
    #endif
    }
    m_u32NplayerCnt++;
}

//-----------------------------------------------------------------------------
static void msAPI_NPlayer_Finit(void)
{
    EN_MPLAYER_MEDIA_TYPE eType;

    MPLAYER_MSG_MUST("msAPI_NPlayer_Finit(%d)\n", m_u32NplayerCnt);
    if (m_u32NplayerCnt == 1)
    {
        MPLAYER_MSG_INFO("m_u32IPCErrCnt[%d]\n", m_u32IPCErrCnt);
        if (m_eDebugLevle >= MPLAYER_DBG_LEVEL_DBG)
        {
            U32 i;
            for (i = 0; i < m_u32IPCErrCnt; i++)
            {
                MPLAYER_MSG_MUST("IPCErrPool[%04d][%08X][%08X]\n", i, MAKEU32(m_u8IPCErrPool, i*8), MAKEU32(m_u8IPCErrPool, i*8+4));
            }
        }

        m_bNplayerRun = FALSE;
        m_eDebugLevle = MPLAYER_DBG_LEVEL_INFO;
        for (eType = E_MPLAYER_MEDIA_MIN; eType < E_MPLAYER_MEDIA_NUM; eType++)
        {
            msAPI_NPlayer_Stop(eType, MPLAYER_NOTIFY_NULL);
        }
        msAPI_DataStreamIO_OptionRegistation(NULL);
    #if SEAMLESS_PLAYING_ENABLE
        MApp_VDPlayer_EnableSeamless(FALSE);
    #endif

        //for zmplayer bw issue
        MDrv_WriteByte(0x100640, m_u8BakReg0640);
        MDrv_WriteByte(0x100642, m_u8BakReg0642);

        //-------------------------------------------------------------------------
        //copy code from MApp_DMP_Exit()
        //-------------------------------------------------------------------------
        //MsOS_EnableInterrupt(E_INT_IRQ_TSP2HK);
    }

    if (m_u32NplayerCnt > 0)
    {
        m_u32NplayerCnt--;
    }
}

//-----------------------------------------------------------------------------
static void msAPI_NPlayer_Start(EN_MPLAYER_MEDIA_TYPE eType)
{
    MPLAYER_MSG_MUST("msAPI_NPlayer_Start(%x)\n",eType);

    m_bNplayerPlay[eType] = TRUE;
#if SEAMLESS_PLAYING_ENABLE
    if ((eType != E_MPLAYER_MEDIA_MOVIE) || !MApp_VDPlayer_GetSeamlessMode())
#endif
    {
        m_eTrickMode[eType] = MPLAYER_TRICK_NORMAL;
    }
    m_eBufferType[eType] = MPLAYER_BUFFER_NORMAL;
    m_eMplayerState[eType] = MPLAYER_STATE_PRE_INIT;
    m_u32ReadTotalSize = 0;

    u32LoopTimer[0] = u32LoopTimer[1] = 0;
    u32TaskLoopCnt = 0;
    u32TaskLoopMax[0] = u32TaskLoopMax[1] = u32TaskLoopMax[2] = 0;

    switch(eType)
    {
        case E_MPLAYER_MEDIA_MOVIE:
            m_s32MinBufferSize = m_s32MinBufferSec*0x20000;
            m_s32MaxBufferSize = m_s32MaxBufferSec*0x20000;
            m_s32DiffBitrate = 0;
            m_bCheckScreen = TRUE;
            m_u8ForceStop = 0;
            m_bNotSupportStreamLen = FALSE;
            m_eZoom = VDPLAYER_ZOOM_FACT_NORMAL;

            if (m_eStreamMode[eType] != MPLAYER_RTSP_MODE)
            {
                if (m_eStreamMode[eType] == MPLAYER_UNSEEKABLE_STREAM_MODE)
                    MApp_VDPlayer_SetCfg(E_VDPLAYER_CFG_BM_STREAM_MODE, E_BM_STREAM_MODE_NETWORK_UNSEEKABLE);
                else
                    MApp_VDPlayer_SetCfg(E_VDPLAYER_CFG_BM_STREAM_MODE, E_BM_STREAM_MODE_NORMAL);

                if (m_eStreamMode[eType] == MPLAYER_FILE_MODE)
                {
                    //Set default timeout
                    m_u32CodecTimeOut[0] = 0;    //E_SHAREMEM_BLOCK_FILEIO_TIMEOUT
                    m_u32CodecTimeOut[1] = 0;  //E_SHAREMEM_NBLOCK_READ_TIMEOUT
                    m_u32CodecTimeOut[2] = 0;  //E_SHAREMEM_NBLOCK_SEEK_TIMEOUT
                    m_u32CodecTimeOut[3] = 0;  //E_SHAREMEM_DECOCE_CTRL_TIMEOUT
                    m_u32CodecTimeOut[4] = 0;  //E_SHAREMEM_ESBUF_CTRL_TIMEOUT
                }
                else
                {
                    m_u32CodecTimeOut[0] = 0xFFFFFFFF;    //E_SHAREMEM_BLOCK_FILEIO_TIMEOUT
                    m_u32CodecTimeOut[1] = 0xFFFFFFFF;  //E_SHAREMEM_NBLOCK_READ_TIMEOUT
                    m_u32CodecTimeOut[2] = 0xFFFFFFFF;  //E_SHAREMEM_NBLOCK_SEEK_TIMEOUT
                    m_u32CodecTimeOut[3] = 0xFFFFFFFF;  //E_SHAREMEM_DECOCE_CTRL_TIMEOUT
                    m_u32CodecTimeOut[4] = 0xFFFFFFFF;  //E_SHAREMEM_ESBUF_CTRL_TIMEOUT
                }
                MApp_VDPlayer_SetCodecTimeout(m_u32CodecTimeOut);

                if (((m_eStreamMode[eType] == MPLAYER_UNSEEKABLE_STREAM_MODE) ||
                    (m_eStreamMode[eType] == MPLAYER_SEEKABLE_STREAM_MODE)) &&
                    (m_u32RingBufferNum[E_MPLAYER_MEDIA_MOVIE] <= 1))
                    MApp_VDPlayer_SetCfg(E_VDPLAYER_CFG_ENABLE_INTERNAL_SUBTITLE, FALSE);
                else
                    MApp_VDPlayer_SetCfg(E_VDPLAYER_CFG_ENABLE_INTERNAL_SUBTITLE, TRUE);

                MApp_VDPlayer_SetCfg(E_VDPLAYER_CFG_FORCE_STOP_CALLBACK, (U32)msAPI_NPlayer_ForceStop);
                MApp_VDPlayer_EnableVideoOnly(m_bKTVMode);
                //Patch for unseekable rmvb stream error after played local mpeg4 moive
                {
                    VDEC_InitParam initParam;
                    memset(&initParam, 0, sizeof(VDEC_InitParam));
                    initParam.eCodecType = E_VDEC_CODEC_TYPE_H264;
                    initParam.VideoInfo.eSrcMode = E_VDEC_SRC_MODE_FILE;
                #if (ENABLE_MIU_1 == ENABLE)
                    initParam.SysConfig.u32CodeBufAddr = ((VDEC_AEON_MEMORY_TYPE & MIU1) ? (VDEC_AEON_ADR | MIU_INTERVAL) : (VDEC_AEON_ADR));
                    initParam.SysConfig.u32CodeBufSize = VDEC_AEON_LEN;
                    initParam.SysConfig.u32FrameBufAddr = ((VDEC_AEON_MEMORY_TYPE & MIU1) ? (VDEC_FRAMEBUFFER_ADR | MIU_INTERVAL) : (VDEC_FRAMEBUFFER_ADR));
                    initParam.SysConfig.u32FrameBufSize = VDEC_FRAMEBUFFER_LEN;
                    initParam.SysConfig.u32BitstreamBufAddr = ((VDEC_AEON_MEMORY_TYPE & MIU1) ? (VDEC_BITSTREAM_ADR | MIU_INTERVAL) : (VDEC_BITSTREAM_ADR));
                    initParam.SysConfig.u32BitstreamBufSize = VDEC_BITSTREAM_LEN;
                    initParam.SysConfig.u32DrvProcBufAddr = (VDEC_BITSTREAM_MEMORY_TYPE & MIU1) ? (VDEC_BITSTREAM_ADR | MIU_INTERVAL) : VDEC_BITSTREAM_ADR;
                    initParam.SysConfig.u32DrvProcBufSize = 0xA000;
                #else
                    initParam.SysConfig.u32CodeBufAddr = VDEC_AEON_ADR;
                    initParam.SysConfig.u32CodeBufSize = VDEC_AEON_LEN;
                    initParam.SysConfig.u32FrameBufAddr = VDEC_FRAMEBUFFER_ADR;
                    initParam.SysConfig.u32FrameBufSize = VDEC_FRAMEBUFFER_LEN;
                    initParam.SysConfig.u32BitstreamBufAddr = VDEC_BITSTREAM_ADR;
                    initParam.SysConfig.u32BitstreamBufSize = VDEC_BITSTREAM_LEN;
                #endif
                    initParam.SysConfig.eDbgMsgLevel = E_VDEC_DBG_LEVEL_NONE;
                    MApi_VDEC_Init(&initParam);
                    MApi_VDEC_Exit();
                }
            }
            break;

        case E_MPLAYER_MEDIA_MUSIC:
            break;

        case E_MPLAYER_MEDIA_PHOTO:
            // check if there is free slot for photo decode
            if (_msAPI_NPlayer_Photo_GetFreeSlot() > 0)
            {
                m_eMplayerState[E_MPLAYER_MEDIA_PHOTO] = MPLAYER_STATE_PRE_INIT;
                msAPI_COPRO_Init(BIN_ID_CODE_VDPLAYER,((AEON_MEM_MEMORY_TYPE & MIU1) ? (AEON_MM_MEM_ADR | MIU_INTERVAL) : (AEON_MM_MEM_ADR)),AEON_MM_MEM_LEN);
                msAPI_Timer_Delayms(50);
            }
            break;

        default:
            break;
    }
}

//-----------------------------------------------------------------------------
static void msAPI_NPlayer_Stop(EN_MPLAYER_MEDIA_TYPE eType, EN_MPLAYER_NOTIFY_TYPE eNotifyCode)
{
    U32 handle;

    for (handle = 0; handle < MPLAYER_STREAM_MAX_HANDLE; handle++)
    {
        if (m_StrmMediaType[handle] == eType)
        {
            msAPI_NPlayer_StreamClose(handle);
            m_StrmMediaType[handle] = E_MPLAYER_MEDIA_INVALID;
        }
    }

    switch(eType)
    {
        case E_MPLAYER_MEDIA_MOVIE:
            if (msAPI_NPlayer_IsPlaying(eType))
            {
                MPLAYER_MSG_MUST("msAPI_NPlayer_Stop(%d)[0x%x]\n", eNotifyCode, MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_ERROR_INFO));

                if (m_eStreamMode[eType] == MPLAYER_RTSP_MODE)
                {
                    U8 param[16];

                    if (!m_bRtspFreeze)
                    {
                        memset(&gstVidStatus, 0, sizeof(VDEC_DispInfo));
                        memset(&gstPreVidStatus, 0, sizeof(VDEC_DispInfo));
                        msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
                        MApi_XC_GenerateBlackVideo(ENABLE, MAIN_WINDOW);
                    }
                    m_bRtspFreeze = FALSE;

                    if (eNotifyCode != MPLAYER_NOTIFY_NULL)
                    {
                        param[0] = COMMAND_TO_NETAP;
                        param[1] = NETAP_COMMAND_RTSP_NOTIFY;
                        param[2] = MPLAYER_RTSP_EXIT;
                        msAPI_NPlayer_Signal(m_u32PID[E_MPLAYER_MEDIA_MOVIE], 3, param);
                    }
                }
                else
                {
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    MsOS_DelayTask(30);
                    if (m_bKTVMode == FALSE)
                    {
                        MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_STOP);
                    }
                #if SEAMLESS_PLAYING_ENABLE
                    if (!MApp_VDPlayer_GetSeamlessMode() || (eNotifyCode != MPLAYER_EXIT_OK))
                #endif
                    {
                        msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
                        MApi_XC_GenerateBlackVideo(ENABLE, MAIN_WINDOW);
                        m_eTrickMode[eType] = MPLAYER_TRICK_NORMAL;
                    }
                    MApp_MPlayer_Subtitle_Dinit();
                    MApp_VDPlayer_Stop();
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);

                    MApp_VDPlayer_SetCfg(E_VDPLAYER_CFG_BM_STREAM_MODE, E_BM_STREAM_MODE_NORMAL);
                    MApp_VDPlayer_SetCfg(E_VDPLAYER_CFG_ENABLE_INTERNAL_SUBTITLE, TRUE);
                    MApp_VDPlayer_SetCfg(E_VDPLAYER_CFG_FORCE_STOP_CALLBACK, (U32)NULL);
                    MApp_VDPlayer_EnableVideoOnly(FALSE);
                }
            }

            m_bCheckMute = FALSE;
            m_bMovieThumbnail = FALSE;
            m_eExternalSubtitleType = E_MPLAYER_SUBTITLE_INVALID;
            memset(m_SubtitleFile, 0, FULLPATH_NAME_SIZE);
            memset(m_SubtitleSubFile, 0, FULLPATH_NAME_SIZE);
            break;

        case E_MPLAYER_MEDIA_MUSIC:
            if (msAPI_NPlayer_IsPlaying(eType))
            {
                if(_geMPLAYER_MusicType == MPLAYER_SUBTYPE_WMA)
                {
                    MApp_Wma_StopAfterFBBegin(FALSE);
                    MApp_WMA_Stop();
                }
                else
                {
                    MApp_Music_StopAfterFBBegin(FALSE);
                    MApp_Music_Stop();
                }
                _geMPLAYER_MusicType = MPLAYER_SUBTYPE_UNKNOWN;
            }
            break;

        case E_MPLAYER_MEDIA_PHOTO:
            {
                U8 i;

                MApp_Photo_Stop();
                MApp_Photo_EnableStreamMode(FALSE);
                // reset photo specific vairables
                _gu8Photo_DecodeIdx     = 0;
                _gu8Photo_DisplayIdx    = 0;

                _gu16Photo_SlideShowTimeOutInSec    = PHOTO_SLIDESHOW_TIME_OUT;
                _gePhoto_SlideShowPauseState        = E_PHOTO_SLIDE_SHOW_FREE_RUN;
                _gbPhotoOnlyDecode = FALSE;
                for (i = 0; i < PHOTO_TOTAL_SLOT; i++)
                {
                    _gePhoto_State[i] = E_PHOTO_SLOT_STATE_FREE;

                    _gu16Photo_Wdith[i]  = 0;
                    _gu16Photo_Height[i] = 0;
                    _gu32Photo_Size[i]   = 0;
                }
            }
            break;

        default:
            break;
    }

    m_bNplayerPlay[eType] = FALSE;
    m_eStreamMode[eType] = MPLAYER_FILE_MODE;
    m_eMplayerState[eType] = MPLAYER_STATE_STANDBY;

    if (eNotifyCode != MPLAYER_NOTIFY_NULL)
    {
        msAPI_NPlayer_SendCmd(eType, MPLAYER_COMMAND_NOTIFY, eNotifyCode);
    }
}

//-----------------------------------------------------------------------------
void msAPI_NPlayer_DrawSubtitle(BOOLEAN bShowSubtitile, U32 u32TextDataAddress, U16 u16Len)
{
    U8 param[16];
    EN_MPLAYER_SUBTITLE_ENCODE eSubtitleEncode;

    UNUSED(u16Len);

    if (m_eExternalSubtitleType != E_MPLAYER_SUBTITLE_INVALID)
    {
        eSubtitleEncode = m_eSubtitleEncode;
    }
    else
    {
        switch (MApp_VDPlayer_GetSubtitleInfo(E_SUBTITLE_INFO_TYPE))
        {
            case E_VDP_CODEC_ID_SUBTITLE_TEXT_SRT:
            case E_VDP_CODEC_ID_SUBTITLE_TEXT_UTF8:
            case E_VDP_CODEC_ID_SUBTITLE_TEXT_ASS:
            case E_VDP_CODEC_ID_SUBTITLE_TEXT_SSA:
            case E_VDP_CODEC_ID_SUBTITLE_TEXT_3GPP:
            case E_VDP_CODEC_ID_SUBTITLE_TEXT_USF:
                eSubtitleEncode = MPLAYER_SUBTITLE_ENCODE_UTF8;
                break;

            default:
                return;
        }
    }
    MPLAYER_MSG_INFO("DrawSubtitle[%d][%d][%x]\n", bShowSubtitile, eSubtitleEncode, u32TextDataAddress);
    if (bShowSubtitile == FALSE)
    {
        u32TextDataAddress = 0;
    }
    param[0] = COMMAND_TO_NETAP;
    param[1] = NETAP_COMMAND_SUBTITLE;
    param[2] = eSubtitleEncode;
    param[3] = u32TextDataAddress&0xFF;
    param[4] = (u32TextDataAddress>>8)&0xFF;
    param[5] = (u32TextDataAddress>>16)&0xFF;
    param[6] = (u32TextDataAddress>>24)&0xFF;
    msAPI_NPlayer_Signal(m_u32PID[E_MPLAYER_MEDIA_MOVIE], 7, param);
}

static BOOL msAPI_NPlayer_ParseSubtitleFile(void)
{
    m_eSubtitleEncode = MPLAYER_SUBTITLE_ENCODE_INVALID;
    if ((m_eExternalSubtitleType != E_MPLAYER_SUBTITLE_INVALID)
        && MApp_MPlayer_ExternalSubtitle_Parser(m_SubtitleFile, m_SubtitleSubFile))
    {
        U8 * pu8Data = (U8*) _PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)));
        if(pu8Data[0]==0xFF && pu8Data[1]==0xFE)
            m_eSubtitleEncode = MPLAYER_SUBTITLE_ENCODE_UNIS;
        else if(pu8Data[0]==0xFE && pu8Data[1]==0xFF)
            m_eSubtitleEncode = MPLAYER_SUBTITLE_ENCODE_UNIB;
        else if(pu8Data[0] == 0xEF && pu8Data[1] == 0xBB && pu8Data[2] == 0xBF)
            m_eSubtitleEncode = MPLAYER_SUBTITLE_ENCODE_UTF8;
        else
            m_eSubtitleEncode = MPLAYER_SUBTITLE_ENCODE_ANSI;
        MPLAYER_MSG_INFO("m_eSubtitleEncode[%d]\n", m_eSubtitleEncode);
        return TRUE;
    }
    return FALSE;
}

static BOOLEAN msAPI_NPlayer_SetTrickMode(EN_MPLAYER_MEDIA_TYPE eType, EN_MPLAYER_TRICK_MODE eTrickMode)
{
    BOOLEAN bRet = FALSE;;

    MPLAYER_MSG_INFO("msAPI_NPlayer_SetTrickMode(%d)\n", eTrickMode);

    if ((eTrickMode >= MPLAYER_TRICK_MODE_NUM) || (m_eMplayerState[eType] != MPLAYER_STATE_PLAYING))
        return FALSE;

    switch(eType)
    {
        case E_MPLAYER_MEDIA_MOVIE:
            {
                if (eTrickMode != MPLAYER_TRICK_NORMAL)
                {
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                }

                switch (eTrickMode)
                {
                    case MPLAYER_TRICK_NORMAL:
                        if (MApp_VDPlayer_SetTrickMode(MODE_NORMAL_PLAY, PLAY_SPEEDx1))
                        {
                            bRet = TRUE;
                            m_bCheckMute = TRUE;
                            m_u32MuteTimer = (U32)MsOS_GetSystemTime() + 500;
                        }

                        if(m_eTrickMode[eType] >= E_MPLAYER_MOVIE_FF_2X  &&
                           m_eTrickMode[eType] <= E_MPLAYER_MOVIE_FB_16X)
                        {
                            if(MApp_VDPlayer_IsTextSubtitle())
                            {
                                MApp_VDPlayer_TextSubtitleInit();
                            }

                            MApp_VDPlayer_SetSubtitleShow(E_SUBTITLE_STATE_COMMAND_SHOW);
                            msAPI_Timer_Delayms(50); //vdplayer time stamp be stable
                        }
                        break;

                    case MPLAYER_TRICK_PAUSE:
                        if (MApp_VDPlayer_Pause())
                        {
                            bRet = TRUE;
                        }
                        break;

                    case MPLAYER_TRICK_FF_2X:
                    case MPLAYER_TRICK_FF_4X:
                    case MPLAYER_TRICK_FF_8X:
                    case MPLAYER_TRICK_FF_16X:
                        MApp_VDPlayer_SetSubtitleShow(E_SUBTITLE_STATE_COMMAND_NOT_SHOW);
                        msAPI_NPlayer_DrawSubtitle(FALSE, 0, 0);//  hide subtitle
                        if (MApp_VDPlayer_SetTrickMode(MODE_FAST_FORWARD, PLAY_SPEEDx2+(EN_PLAY_SPEED)(eTrickMode-MPLAYER_TRICK_FF_2X)))
                        {
                            bRet = TRUE;
                        }
                        break;

                    case MPLAYER_TRICK_FB_2X:
                    case MPLAYER_TRICK_FB_4X:
                    case MPLAYER_TRICK_FB_8X:
                    case MPLAYER_TRICK_FB_16X:
                        MApp_VDPlayer_SetSubtitleShow(E_SUBTITLE_STATE_COMMAND_NOT_SHOW);
                        msAPI_NPlayer_DrawSubtitle(FALSE, 0, 0);//  hide subtitle
                        if (MApp_VDPlayer_SetTrickMode(MODE_FAST_BACKWARD, PLAY_SPEEDx2+(EN_PLAY_SPEED)(eTrickMode-MPLAYER_TRICK_FB_2X)))
                        {
                            bRet = TRUE;
                        }
                        break;

                    case MPLAYER_TRICK_SLOW:
                        if (MApp_VDPlayer_SetTrickMode(MODE_SLOW_FORWARD, PLAY_SPEEDx1))
                        {
                            bRet = TRUE;
                        }
                        break;

                    default:
                        break;
                }

                if (bRet == TRUE)
                {
                    m_eTrickMode[eType] = eTrickMode;
                }
            }
            break;

        case E_MPLAYER_MEDIA_MUSIC:
            {
                switch (eTrickMode)
                {
                    case MPLAYER_TRICK_NORMAL:
                        if(m_eTrickMode[eType] == MPLAYER_TRICK_PAUSE)
                        {
                            if(_geMPLAYER_MusicType == MPLAYER_SUBTYPE_WMA)
                            {
                                MApp_WMA_Resume();
                            }
                            else
                            {
                                MApp_Music_Resume();
                            }

                            // reset play mode & speed
                            m_eTrickMode[eType] = MPLAYER_TRICK_NORMAL;
                            return TRUE;
                        }
                        else
                        {
                            if(_geMPLAYER_MusicType == MPLAYER_SUBTYPE_WMA)
                            {
                                MApp_WMA_FastForwardBackward(TRUE,EN_WMA_SPEED_X1);
                            }
                            else
                            {
                                MApp_Music_FastForwardBackward(TRUE,EN_MP3_SPEED_X1);
                            }
                            bRet = TRUE;

                        }
                        break;

                    case MPLAYER_TRICK_PAUSE:
                        if(_geMPLAYER_MusicType == MPLAYER_SUBTYPE_WMA)
                        {
                            MApp_WMA_Pause();
                        }
                        else
                        {
                            MApp_Music_Pause();
                        }

                        bRet = TRUE;
                        break;

                    case MPLAYER_TRICK_FF_2X:
                    case MPLAYER_TRICK_FF_4X:
                    case MPLAYER_TRICK_FF_8X:
                    case MPLAYER_TRICK_FF_16X:
                        if(_geMPLAYER_MusicType == MPLAYER_SUBTYPE_WMA)
                        {
                            MApp_WMA_FastForwardBackward(TRUE,EN_WMA_SPEED_X2 + (EN_WMA_SPEED)(eTrickMode-MPLAYER_TRICK_FF_2X));
                        }
                        else
                        {
                            MApp_Music_FastForwardBackward(TRUE,EN_MP3_SPEED_X2+ (EN_MP3_SPEED)(eTrickMode-MPLAYER_TRICK_FF_2X));
                        }
                        bRet = TRUE;
                        break;

                    case MPLAYER_TRICK_FB_2X:
                    case MPLAYER_TRICK_FB_4X:
                    case MPLAYER_TRICK_FB_8X:
                    case MPLAYER_TRICK_FB_16X:
                        if(_geMPLAYER_MusicType == MPLAYER_SUBTYPE_WMA)
                        {
                            MApp_WMA_FastForwardBackward(FALSE,EN_WMA_SPEED_X2 + (EN_WMA_SPEED)(eTrickMode-MPLAYER_TRICK_FB_2X));
                        }
                        else
                        {
                            MApp_Music_FastForwardBackward(FALSE,EN_MP3_SPEED_X2+ (EN_MP3_SPEED)(eTrickMode-MPLAYER_TRICK_FB_2X));
                        }
                        bRet = TRUE;
                        break;

                    case MPLAYER_TRICK_SLOW:
                         bRet = FALSE;
                        break;

                    default:
                        break;
                }

                if(bRet)
                {
                    m_eTrickMode[eType] = eTrickMode;
                }
            }
            break;

        case E_MPLAYER_MEDIA_PHOTO:
            {
                switch (eTrickMode)
                {
                    case MPLAYER_TRICK_NORMAL:
                        if (m_eTrickMode[eType]  == MPLAYER_TRICK_PAUSE)
                        {
                            _gePhoto_SlideShowPauseState = E_PHOTO_SLIDE_SHOW_PAUSE_RELEASED;
                            bRet = TRUE;
                        }
                        break;

                    case MPLAYER_TRICK_PAUSE:
                        // for photo, pause display, not decode
                        _gePhoto_SlideShowPauseState = E_PHOTO_SLIDE_SHOW_PAUSED;
                        bRet = TRUE;
                        break;

                    default:
                        break;
                }

                if (bRet == TRUE)
                    m_eTrickMode[eType] = eTrickMode;
            }
            break;
        default:
            break;
    }

    return bRet;
}

//-----------------------------------------------------------------------------
static U32 msAPI_NPlayer_Callback(U8 * pu8Data)
{
    S32 nLen;
    U32 i, u32PID, u32Data = 0;
    EN_MPLAYER_MEDIA_TYPE eType;

    MPLAYER_MSG_INFO("msAPI_NPlayer_Callback(%08X)\n", (pu8Data[3] + (pu8Data[2] << 8) + (pu8Data[1] << 16) + (pu8Data[0] << 24)));
    if (pu8Data[0] != COMMAND_TO_MPLAYER)
        return 0;

    switch (pu8Data[1])
    {
        case MPLAYER_COMMAND_INT:
            {
                u32PID = MAKEU32(pu8Data, 2);
                for (i = 0; i < E_MPLAYER_MEDIA_NUM; i++)
                {
                    if ((m_eMplayerState[i] == MPLAYER_STATE_STANDBY) || (m_u32PID[i] == 0xFFFFFFFF))
                    {
                        m_u32PID[i] = u32PID;
                    }
                }
                msAPI_NPlayer_Init();
            }
            break;

        case MPLAYER_COMMAND_FINT:
            {
                u32PID = MAKEU32(pu8Data, 2);
                for (i = 0; i < E_MPLAYER_MEDIA_NUM; i++)
                {
                    if (m_u32PID[i] == u32PID)
                    {
                        m_u32PID[i] = 0xFFFFFFFF;
                    }
                }
                msAPI_NPlayer_Finit();
            }
            break;

        case MPLAYER_COMMAND_GET_VERSION:
            u32Data = (ver[0]-'0')*100+(ver[2]-'0')*10+(ver[4]-'0');
            break;

        case MPLAYER_COMMAND_CREAT_STREAM:
            {
                U8 maxandle = 0;

                u32Data = RING_BUFFER_HEAD;
                RING_BUFFER_SIZE = 0;
                RingBufferIndex32(0, INDEX_SHAR_MEM_SIZE) = RING_BUFFER_SIZE;
                RingBufferIndex32(0, INDEX_SHAR_MEM_HEAD_SIZE) = 1; //Error1
                if ((eType = (EN_MPLAYER_MEDIA_TYPE)pu8Data[2]) >= E_MPLAYER_MEDIA_INVALID)
                {
                    MPLAYER_MSG_ERR("Wrong media type setting for creat stream cmd:%x!!!\n", eType);
                    return u32Data;
                }

                RingBufferIndex32(0, INDEX_SHAR_MEM_HEAD_SIZE) = 2; //Error2
                switch (eType)
                {
                    case E_MPLAYER_MEDIA_MOVIE:
                        if (m_bKTVMode)
                            maxandle = m_u32RingBufferNum[E_MPLAYER_MEDIA_MOVIE] + m_u32RingBufferNum[E_MPLAYER_MEDIA_MUSIC] + m_u32RingBufferNum[E_MPLAYER_MEDIA_PHOTO];
                        else
                            maxandle = m_u32RingBufferNum[E_MPLAYER_MEDIA_MOVIE];
                        break;

                    case E_MPLAYER_MEDIA_MUSIC:
                        if (m_bKTVMode)
                            maxandle = m_u32RingBufferNum[E_MPLAYER_MEDIA_MOVIE] + m_u32RingBufferNum[E_MPLAYER_MEDIA_MUSIC] + m_u32RingBufferNum[E_MPLAYER_MEDIA_PHOTO];
                        else
                            maxandle = m_u32RingBufferNum[E_MPLAYER_MEDIA_MUSIC] + m_u32RingBufferNum[E_MPLAYER_MEDIA_PHOTO];
                        break;

                    case E_MPLAYER_MEDIA_PHOTO:
                        if (m_bKTVMode)
                            maxandle = m_u32RingBufferNum[E_MPLAYER_MEDIA_MOVIE] + m_u32RingBufferNum[E_MPLAYER_MEDIA_MUSIC] + m_u32RingBufferNum[E_MPLAYER_MEDIA_PHOTO];
                        else
                            maxandle = m_u32RingBufferNum[E_MPLAYER_MEDIA_MUSIC] + m_u32RingBufferNum[E_MPLAYER_MEDIA_PHOTO];
                        break;

                    default:
                        return u32Data;
                }

                if ((maxandle > 0) && (maxandle <= MAX_RING_BUFFER_HANDLE))
                {
                    RING_BUFFER_SIZE = ((RING_BUFFER_LENGTH/maxandle)&0xFFFFFE00);
                    for (i = 0; i < maxandle; i++)
                    {
                        RingBufferIndex32(i, INDEX_SHAR_MEM_SIZE) = RING_BUFFER_SIZE;
                        RingBufferIndex32(i, INDEX_SHAR_MEM_HEAD_SIZE) = RING_BUFFER_HEAD_SIZE;
                        RingBufferIndex32(i, INDEX_RING_BUFFER_START) = RING_BUFFER_START(i);
                        RingBufferIndex32(i, INDEX_RING_BUFFER_END) = RING_BUFFER_END(i);
                    }
                }
                else
                {
                    RingBufferIndex32(0, INDEX_SHAR_MEM_HEAD_SIZE) = 3; //Error3
                }
            }
            break;

        case MPLAYER_COMMAND_SET_DISP_WINDOW:
            g_sDispWindow.x = MAKEU16(pu8Data, 2);
            g_sDispWindow.y = MAKEU16(pu8Data, 6);
            g_sDispWindow.width = MAKEU16(pu8Data, 10);
            g_sDispWindow.height = MAKEU16(pu8Data, 14);

            if (g_sDispWindow.x == 0 && g_sDispWindow.y == 0 && g_sDispWindow.width == 0 && g_sDispWindow.height == 0)
            {
                m_bFullScreen = TRUE;
            }
            else
            {
                m_bFullScreen = FALSE;
            }
            break;

        case MPLAYER_COMMAND_SEND_FILE_NAME:
            if (pu8Data[2] == 1)
            {
                memset(m_FullPathName, 0, FULLPATH_NAME_SIZE);
                m_pName = m_FullPathName+FULLPATH_NAME_SIZE-1;
            }
            else if (pu8Data[2] == 2)
            {
                char * pName = (char *)(pu8Data+3);
                nLen = strlen(pName);
                if (m_pName - m_FullPathName >= nLen)
                {
                    m_pName -= nLen;
                    memcpy(m_pName, pName, nLen);
                }
            }
            else if (pu8Data[2] == 3)
            {
                if (m_pName == (m_FullPathName+FULLPATH_NAME_SIZE-1))
                {
                    m_pName = NULL;
                }
            }
            else
            {
                memset(m_FullPathName, 0, FULLPATH_NAME_SIZE);
                m_pName = NULL;
            }
            break;

        case MPLAYER_COMMAND_PLAY_PRE:
            m_u32VdplayerInitStartTimer = msAPI_Timer_GetTime0();
            m_u32StartPlayTimer= msAPI_Timer_GetTime0();
            eType = (EN_MPLAYER_MEDIA_TYPE)pu8Data[3];
            if(eType >= E_MPLAYER_MEDIA_INVALID)
            {
                MPLAYER_MSG_ERR("Wrong media type setting for playfile cmd:%x!!!\n", eType);
                return 0;
            }
            u32PID = MAKEU32(pu8Data, 4);

            switch(eType)
            {
                case E_MPLAYER_MEDIA_MOVIE:
                    if ((m_bKTVMode == FALSE) && (m_eMplayerState[E_MPLAYER_MEDIA_MUSIC] != MPLAYER_STATE_STANDBY))
                        break;
                    if (m_eMplayerState[E_MPLAYER_MEDIA_PHOTO] != MPLAYER_STATE_STANDBY)
                        break;
                    if ((m_eMplayerState[E_MPLAYER_MEDIA_MOVIE] != MPLAYER_STATE_STANDBY) && (m_u32PID[E_MPLAYER_MEDIA_MOVIE] != u32PID))
                        break;
                    u32Data = TRUE;
                    break;

                case E_MPLAYER_MEDIA_MUSIC:
                    if ((m_bKTVMode == FALSE) && (m_eMplayerState[E_MPLAYER_MEDIA_MOVIE] != MPLAYER_STATE_STANDBY))
                        break;
                    if ((m_eMplayerState[E_MPLAYER_MEDIA_MUSIC] != MPLAYER_STATE_STANDBY) && (m_u32PID[E_MPLAYER_MEDIA_MUSIC] != u32PID))
                        break;
                    u32Data = TRUE;
                    break;

                case E_MPLAYER_MEDIA_PHOTO:
                    if (m_eMplayerState[E_MPLAYER_MEDIA_MOVIE] != MPLAYER_STATE_STANDBY)
                        break;
                    if ((m_eMplayerState[E_MPLAYER_MEDIA_PHOTO] != MPLAYER_STATE_STANDBY) && (m_u32PID[E_MPLAYER_MEDIA_PHOTO] != u32PID))
                        break;
                    u32Data = TRUE;
                    break;

                default:
                    break;
            }
            break;

        case MPLAYER_COMMAND_PLAY_FILE:
            eType = (EN_MPLAYER_MEDIA_TYPE)pu8Data[3];
            if(eType >= E_MPLAYER_MEDIA_INVALID)
            {
                MPLAYER_MSG_ERR("Wrong media type setting for playfile cmd:%x!!!\n", eType);
                return MPLAYER_TRICK_MODE_INVALID;
            }
            u32Data = MPLAYER_TRICK_MODE_INVALID;

            m_eStreamMode[eType] = (EN_MPLAYER_FILE_MODE)pu8Data[2];
            m_u32PID[eType] = MAKEU32(pu8Data, 4);
            switch(eType)
            {
                case E_MPLAYER_MEDIA_MOVIE:
                    {
                        if (m_eStreamMode[eType] == MPLAYER_RTSP_MODE)
                        {
                            msAPI_NPlayer_Start(eType);
                            u32Data = m_eTrickMode[eType];
                        }
                        else
                        {
                            if (m_pName != NULL)
                            {
                                m_u32StartGotoTime = MAKEU32(pu8Data, 8) / 1000;
                                MPLAYER_MSG_INFO("FileName:%s\n", m_pName);
                                MPLAYER_MSG_INFO("Stream[%d], Goto", m_eStreamMode[eType]);
                                MPLAYER_MSG_INFO("[%02d:", m_u32StartGotoTime/3600);
                                m_u32StartGotoTime %= 3600;
                                MPLAYER_MSG_INFO("%02d:", m_u32StartGotoTime/60);
                                m_u32StartGotoTime %= 60;
                                MPLAYER_MSG_INFO("%02d]\n", m_u32StartGotoTime);
                                m_u32StartGotoTime = MAKEU32(pu8Data, 8);
                                m_bMovieThumbnail  = pu8Data[12];
                                MPLAYER_MSG_INFO("m_bMovieThumbnail=%d\n", m_bMovieThumbnail);

                                if ((m_eStreamMode[eType] != MPLAYER_FILE_MODE) || (strlen(m_pName) < FULLPATH_NAME_SIZE))
                                {
                                    MApp_MPlayer_SetExternalSubtitleType(m_eExternalSubtitleType);
                                    MApp_MPlayer_Register_Notify(E_SUBTITLE_NOTIFY_AP_RAWDATA, msAPI_NPlayer_DrawSubtitle);
                                    msAPI_NPlayer_Start(eType);
                                    u32Data = m_eTrickMode[eType];
                                }
                            }

                            if (u32Data == MPLAYER_TRICK_MODE_INVALID)
                            {
                                msAPI_NPlayer_Stop(eType,MPLAYER_EXIT_ERROR_FILE);
                            }
                        }
                    }
                    break;

                case E_MPLAYER_MEDIA_MUSIC:
                    msAPI_NPlayer_Start(eType);
                    u32Data = m_eTrickMode[eType];
                    break;

                case E_MPLAYER_MEDIA_PHOTO:
                    m_bThumbnail = pu8Data[8];
                    msAPI_NPlayer_Start(eType);
                    u32Data = m_eTrickMode[eType];
                    break;

                default:
                    break;
            }
            break;

        case MPLAYER_COMMAND_SET_DISP_RTSP:
            {
                MVOP_VidStat stMvopVidSt;

                memcpy(&gstVidStatus, pu8Data+2, sizeof(VDEC_DispInfo));
                if ((gstPreVidStatus.u16HorSize != gstVidStatus.u16HorSize)
                    || (gstPreVidStatus.u16VerSize != gstVidStatus.u16VerSize)
                    || (gstPreVidStatus.u32FrameRate != gstVidStatus.u32FrameRate)
                    || (gstPreVidStatus.u8Interlace != gstVidStatus.u8Interlace))
                {
                    MDrv_MVOP_Init();
                    memset(&stMvopVidSt, 0, sizeof(MVOP_VidStat));
                    stMvopVidSt.u16HorSize  = gstVidStatus.u16HorSize;
                    stMvopVidSt.u16VerSize  = gstVidStatus.u16VerSize;
                    stMvopVidSt.u16FrameRate = gstVidStatus.u32FrameRate;
                    stMvopVidSt.u8AspectRate = gstVidStatus.u8AspectRate;
                    stMvopVidSt.u8Interlace = gstVidStatus.u8Interlace;
                    stMvopVidSt.u16HorOffset = 0;
                    stMvopVidSt.u16VerOffset = 0;
                    MPLAYER_MSG_INFO("stMvopVidSt[%d][%d][%d]\n", stMvopVidSt.u16HorSize, stMvopVidSt.u16VerSize, stMvopVidSt.u16FrameRate);
                    MDrv_MVOP_SetOutputCfg(&stMvopVidSt, FALSE);
                    MDrv_MVOP_Enable(FALSE);
                    MDrv_MVOP_SetInputCfg(MVOP_INPUT_H264, NULL);
                    MDrv_MVOP_Enable(TRUE);

                    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, DISABLE, 0, MAIN_WINDOW);
                    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, 500, MAIN_WINDOW);
                    msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
                    MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);
                    MApp_Scaler_EnableOverScan(FALSE);
                    if ((g_sDispWindow.width != 0) && (g_sDispWindow.height != 0))
                        MApp_Scaler_SetWindow(NULL, NULL, &g_sDispWindow, stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
                    else
                        MApp_Scaler_SetWindow(NULL, NULL, NULL, stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
                    MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
                    msAPI_Scaler_SetBlueScreen(DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
                }
                gstPreVidStatus = gstVidStatus;
                m_eMplayerState[E_MPLAYER_MEDIA_MOVIE] = MPLAYER_STATE_PLAYING;
                u32AudioMonitTimer = MsOS_GetSystemTime();
            }
            break;

        case MPLAYER_COMMAND_FREEZE_DISP_RTSP:
            m_bRtspFreeze = TRUE;
            MApi_XC_FreezeImg(TRUE, MAIN_WINDOW);
            break;

        case MPLAYER_COMMAND_SEND_SUBTITLE_FILE:
            if (m_pName != NULL)
            {
                strcpy(m_SubtitleFile, m_pName);
                MPLAYER_MSG_INFO("SubtitleFile:%s\n", m_SubtitleFile);
                switch (pu8Data[2])
                {
                    case MPLAYER_SUBTITLE_SRT:
                        m_eExternalSubtitleType = E_MPLAYER_SUBTITLE_SRT;
                        break;

                    case MPLAYER_SUBTITLE_SSA:
                        m_eExternalSubtitleType = E_MPLAYER_SUBTITLE_SSA;
                        break;

                    case MPLAYER_SUBTITLE_ASS:
                        m_eExternalSubtitleType = E_MPLAYER_SUBTITLE_ASS;
                        break;

                    case MPLAYER_SUBTITLE_SMI:
                        m_eExternalSubtitleType = E_MPLAYER_SUBTITLE_SMI;
                        break;

                    case MPLAYER_SUBTITLE_IDX:
                        m_eExternalSubtitleType = E_MPLAYER_SUBTITLE_SUBIDX;
                        break;

                    default:
                        m_eExternalSubtitleType = E_MPLAYER_SUBTITLE_INVALID;
                        break;
                }
                MPLAYER_MSG_INFO("SubtitleType: %d\n", m_eExternalSubtitleType);
            }
            break;

        case MPLAYER_COMMAND_SEND_SUBTITLE_SUBFILE:
            if ((m_pName != NULL) && (m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SUBIDX))
            {
                strcpy(m_SubtitleSubFile, m_pName);
                MPLAYER_MSG_INFO("SubtitleSubFile:%s\n", m_SubtitleSubFile);
            }
            break;

        case MPLAYER_COMMAND_SEND_MUSIC_LYRIC_FILE:
            if (m_pName != NULL)
            {
                strcpy(m_LyricFile, m_pName);
                MPLAYER_MSG_INFO("LyricFile:%s\n", m_LyricFile);
            }
            break;

        case MPLAYER_COMMAND_SET_OPTION:
            {
                eType = (EN_MPLAYER_MEDIA_TYPE)pu8Data[2];
                u32Data = (U32)TRUE;

                if (eType >= E_MPLAYER_MEDIA_INVALID)
                {
                    MPLAYER_MSG_ERR("Wrong media type setting for set option:%x!!!\n", eType);
                    return 0;
                }

                EN_MPLAYER_OPTION_TYPE eOption = (EN_MPLAYER_OPTION_TYPE)pu8Data[3];
                U32 u32Param = MAKEU32(pu8Data, 4);
                switch (eOption)
                {
                    case MPLAYER_OPTION_UP_BOUNDARY:
                        m_s32MaxBufferSec = u32Param;
                        break;

                    case MPLAYER_OPTION_DOWN_BOUNDARY:
                        m_s32MinBufferSec = u32Param;
                        break;

                    case MPLAYER_OPTION_RING_BUFFER_HANDLE:
                        m_u32RingBufferNum[eType] = u32Param;
                        break;

                    case MPLAYER_OPTION_SET_KTV_MODE:
                        m_bKTVMode = (BOOL)u32Param;
                        break;

                    case MPLAYER_OPTION_SET_SEAMLESS_MODE:
                    #if SEAMLESS_PLAYING_ENABLE
                        MApp_VDPlayer_EnableSeamless((BOOL)u32Param);
                    #endif
                        break;

                    case MPLAYER_OPTION_INIT_TIME_OUT:
                        m_u32VdplayerInitTimerOut = u32Param;
                        break;

                    case MPLAYER_OPTION_READ_TIME_OUT:
                        m_u32VdplayerReadTimerOut = u32Param;
                        break;

                    case MPLAYER_OPTION_PLAY_TIME_OUT:
                        MApp_VDPlayer_SetPlayTimeOut(u32Param);
                        break;

                    case MPLAYER_OPTION_INIT_DATA_SIZE:
                        m_u32InitDataSize = u32Param;
                        break;

                    case MPLAYER_OPTION_LESS_DATA_MODE:
                        m_bLessDataSize = u32Param;
                        break;

                    case MPLAYER_OPTION_SET_DBG_LEVEL:
                        m_eDebugLevle = (EN_MPLAYER_DBG_LEVEL)u32Param;
                        break;

                    case MPLAYER_OPTION_VOLUME:
                        if (u32Param <= 100)
                        {
                            stGenSetting.g_SoundSetting.Volume = u32Param;
                            msAPI_AUD_AdjustAudioFactor(E_ADJUST_VOLUME, stGenSetting.g_SoundSetting.Volume, 0);
                        }
                        break;

                    case MPLAYER_OPTION_MUTE:
                        if (u32Param)
                            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                        else
                            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                        break;

                    case MPLAYER_OPTION_UART_SWITCH:
                        if (u32Param == MPLAYER_UART_SWITCH_TO_COPROCESSOR)
                        {
                            MPLAYER_MSG_INFO("Uart switch to Co-Processor\n");
#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)
                            mdrv_uart_connect(E_UART_PORT0, E_UART_AEON_R2);
#else
                            mdrv_uart_connect(E_UART_PORT0, E_UART_AEON);
#endif
                        }
                        else
                        {
                        #if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_M10) || \
						    (CHIP_FAMILY_TYPE==CHIP_FAMILY_EDEN)   || \
						    (CHIP_FAMILY_TYPE==CHIP_FAMILY_NASA)   || \
						    (CHIP_FAMILY_TYPE==CHIP_FAMILY_EULER)  || \
						    (CHIP_FAMILY_TYPE==CHIP_FAMILY_MAYA))
                            mdrv_uart_connect(E_UART_PORT0, E_UART_AEON_R2);
                        #else
                            mdrv_uart_connect(E_UART_PORT0, E_UART_PIU_UART0);
                        #endif
                            MPLAYER_MSG_INFO("Uart switch to HK\n");
                        }
                        break;

                    case MPLAYER_OPTION_ENABLE_SUBTITLE:
                        if (m_eMplayerState[E_MPLAYER_MEDIA_MOVIE] == MPLAYER_STATE_PLAYING)
                        {
                            if (u32Param)
                                MApp_MPlayer_EnableMovieSubtitle();
                            else
                                MApp_MPlayer_DisableMovieSubtitle();
                        }
                        break;

                    case MPLAYER_OPTION_CHANGE_EXTERNAL_SUBTITLE:
                        if ((m_eMplayerState[E_MPLAYER_MEDIA_MOVIE] == MPLAYER_STATE_PLAYING) && (m_eStreamMode[E_MPLAYER_MEDIA_MOVIE] != MPLAYER_RTSP_MODE))
                        {
                            MPLAYER_MSG_INFO("Change external subtitle!\n");
                            MApp_MPlayer_Subtitle_Dinit();
                            MApp_MPlayer_SetExternalSubtitleType(m_eExternalSubtitleType);
                            MApp_MPlayer_Register_Notify(E_SUBTITLE_NOTIFY_AP_RAWDATA, msAPI_NPlayer_DrawSubtitle);
                            msAPI_NPlayer_ParseSubtitleFile();
                        }
                        break;

                    case MPLAYER_OPTION_CHANGE_INTERNAL_SUBTITLE:
                        if ((m_eMplayerState[E_MPLAYER_MEDIA_MOVIE] == MPLAYER_STATE_PLAYING) && (m_eStreamMode[E_MPLAYER_MEDIA_MOVIE] != MPLAYER_RTSP_MODE))
                        {
                            MPLAYER_MSG_INFO("Change internal subtitle(%d)!\n", u32Param);
                            U32 u32TotalTrack = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_NB_SUBTITLE_TRACK);
                            if ((u32TotalTrack > 1) && (u32Param < u32TotalTrack))
                            {
                                MApp_MPlayer_ChangeSubtitleTrack(u32Param);
                            }
                        }
                        break;

                    case MPLAYER_OPTION_CHANGE_PROGRAM:
                        if ((m_eMplayerState[E_MPLAYER_MEDIA_MOVIE] == MPLAYER_STATE_PLAYING) && (m_eStreamMode[E_MPLAYER_MEDIA_MOVIE] != MPLAYER_RTSP_MODE))
                        {
                            U32 u32TotalTrack = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_NB_PROGRAM);
                            if ((u32TotalTrack > 1) && (u32Param < u32TotalTrack))
                            {
                                MApp_VDPlayer_ChangeProgam(u32Param);
                            }
                        }
                        break;

                    case MPLAYER_OPTION_CHANGE_AUDIO:
                        if ((m_eMplayerState[E_MPLAYER_MEDIA_MOVIE] == MPLAYER_STATE_PLAYING) && (m_eStreamMode[E_MPLAYER_MEDIA_MOVIE] != MPLAYER_RTSP_MODE))
                        {
                            U32 u32TotalTrack = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_NB_AUDIO_TRACK);
                            if ((u32TotalTrack > 1) && (u32Param < u32TotalTrack))
                            {
                                MApp_VDPlayer_SetAudioTrackID(u32Param);
                            }
                        }
                        break;

                    case MPLAYER_OPTION_ASPECT_RATIO:
                        {
                            ST_VIDEO.eAspectRatio = (EN_MENU_AspectRatio)(u32Param%EN_AspectRatio_Num);
                            stSystemInfo[MAIN_WINDOW].enAspectRatio = MApp_Scaler_GetAspectRatio(MAIN_WINDOW,ST_VIDEO.eAspectRatio);
                            MPLAYER_MSG_INFO("ASPECT_RATIO[%d][%d]\n", ST_VIDEO.eAspectRatio, stSystemInfo[MAIN_WINDOW].enAspectRatio);

                            if (ST_VIDEO.eAspectRatio == EN_AspectRatio_JustScan)
                                MApp_Scaler_EnableOverScan(DISABLE);
                            else
                                MApp_Scaler_EnableOverScan(ENABLE);

                            if (m_eMplayerState[E_MPLAYER_MEDIA_MOVIE] == MPLAYER_STATE_PLAYING)
                            {
                                if (ST_VIDEO.eAspectRatio == EN_AspectRatio_Original || ST_VIDEO.eAspectRatio == EN_AspectRatio_14X9)
                                {
                                    if (MApp_IsSrcHasSignal(MAIN_WINDOW))
                                    {
                                        MVOP_Timing stMVOPTiming;
                                        MS_WINDOW_TYPE stDstWin;

                                        MDrv_MVOP_GetOutputTiming(&stMVOPTiming);
                                        if (ST_VIDEO.eAspectRatio == EN_AspectRatio_Original )
                                        {
                                            if ((g_IPanel.Width() >= stMVOPTiming.u16Width) && (g_IPanel.Height() >= stMVOPTiming.u16Height))
                                            {
                                                stDstWin.x = (g_IPanel.Width()-stMVOPTiming.u16Width)/2;
                                                stDstWin.y = (g_IPanel.Height()-stMVOPTiming.u16Height)/2;
                                                stDstWin.width = stMVOPTiming.u16Width;
                                                stDstWin.height = stMVOPTiming.u16Height;
                                            }
                                            else
                                            {
                                                stDstWin.x = 0;
                                                stDstWin.y = 0;
                                                stDstWin.width = g_IPanel.Width();
                                                stDstWin.height = g_IPanel.Height();
                                            }
                                        }
                                        else if (ST_VIDEO.eAspectRatio == EN_AspectRatio_14X9 )
                                        {
                                            U32 u32ParWidth = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_PAR_H_SIZE);
                                            U32 u32ParHeight = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_PAR_V_SIZE);
                                            if(u32ParWidth == 0||u32ParHeight == 0)
                                            {
                                                u32ParWidth = g_IPanel.Width();
                                                u32ParHeight = g_IPanel.Height();
                                            }
                                            while(u32ParWidth>0xffff||u32ParHeight>0xffff)
                                            {
                                                u32ParWidth = u32ParWidth >> 1;
                                                u32ParHeight = u32ParHeight >> 1;
                                            }

                                            if ((g_IPanel.Width()*(U16)u32ParHeight) > (g_IPanel.Height()*(U16)u32ParWidth))
                                            {
                                                stDstWin.width = (g_IPanel.Height()*(U16)u32ParWidth/(U16)u32ParHeight);
                                                stDstWin.height = g_IPanel.Height();
                                                stDstWin.x = (g_IPanel.Width()-stDstWin.width)/2;
                                                stDstWin.y = 0;
                                            }
                                            else
                                            {
                                                stDstWin.width = g_IPanel.Width();
                                                stDstWin.height = (g_IPanel.Width()*(U16)u32ParHeight/(U16)u32ParWidth);
                                                stDstWin.x = 0;
                                                stDstWin.y = (g_IPanel.Height()-stDstWin.height)/2;
                                            }
                                        }
                                        MPLAYER_MSG_INFO("EN_AspectRatio_Original[%d][%d][%d][%d]\n", stDstWin.x, stDstWin.y, stDstWin.width, stDstWin.height);

                                        msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
                                        MApp_Scaler_SetWindow(NULL, NULL, &stDstWin, VIDEOSCREEN_FULL, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
                                        MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
                                        MApp_Scaler_SetTiming(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
                                        msAPI_Scaler_SetBlueScreen(DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
                                    }
                                }
                                else
                                {
                                    MApp_VDPlayer_ScaleVideo(m_eZoom);
                                }
                            }
                        }
                        break;

                    case MPLAYER_OPTION_DISPLAY_WINDOW:
                        g_sDispWindow.x = MAKEU32(pu8Data, 4);
                        g_sDispWindow.y = MAKEU32(pu8Data, 8);
                        g_sDispWindow.width = MAKEU32(pu8Data, 12);
                        g_sDispWindow.height = MAKEU32(pu8Data, 16);
                        MPLAYER_MSG_INFO("DISP_WINDOW[%d][%d][%d][%d]\n", g_sDispWindow.x, g_sDispWindow.y, g_sDispWindow.width, g_sDispWindow.height);
                        if (m_eMplayerState[E_MPLAYER_MEDIA_MOVIE] == MPLAYER_STATE_PLAYING)
                        {
                            if ((g_sDispWindow.x < g_IPanel.Width()) && (g_sDispWindow.y < g_IPanel.Height()) &&
                                (g_sDispWindow.width > 0) && (g_sDispWindow.width+g_sDispWindow.x <= g_IPanel.Width()) &&
                                (g_sDispWindow.height > 0) && (g_sDispWindow.height+g_sDispWindow.y <= g_IPanel.Height()))
                            {
                                msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
                                MApp_Scaler_SetWindow(NULL,  NULL, &g_sDispWindow, stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
                                msAPI_Scaler_SetBlueScreen(DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
                            }
                        }
                        break;

                    case MPLAYER_OPTION_PICTURE_MODE:
                        ST_VIDEO.ePicture = (EN_MS_PICTURE)(u32Param%(PICTURE_USER+1));
                        MApp_SetPictureMode(MAIN_WINDOW, TRUE);
                        break;

                    case MPLAYER_OPTION_SET_MUSIC_TYPE:
                        if((EN_MPLAYER_SUB_TYPE)u32Param < MPLAYER_SUBTYPE_TEXT)
                        {
                            _geMPLAYER_MusicType = (EN_MPLAYER_SUB_TYPE)u32Param;
                        }
                        break;

                    case MPLAYER_OPTION_ENABLE_MUSIC_LYRIC:
                        m_eMusicFlag |= E_MPLAYER_MUSIC_FLG_LYRIC_ENABLE;
                        break;

                    case MPLAYER_OPTION_DISABLE_MUSIC_LYRIC:
                        m_eMusicFlag &= (EN_MPLAYER_MUSIC_FLAG)~E_MPLAYER_MUSIC_FLG_LYRIC_ENABLE;
                        break;

                    case MPLAYER_OPTION_MUSIC_SET_PCM_PARAM:
                        {
                            BOOLEAN bRet = TRUE;
                            EN_PCM_FORMAT eFormatTag;
                            U16 u16FormatTag, u16Channels, u32SamplesPerSec, u16BitsPerSample;
                            BOOLEAN bBigEndian;

                            eFormatTag = (EN_PCM_FORMAT)pu8Data[4];
                            switch(eFormatTag)
                            {
                                case E_PCM_FORMAT_PCM:
                                    u16FormatTag = (U16)WAVE_FORMAT_PCM;
                                    break;

                                case E_PCM_FORMAT_M_ADPCM:
                                    u16FormatTag = (U16)WAVE_FORMAT_M_ADPCM;
                                    break;

                                case E_PCM_FORMAT_IMA_ADPCM:
                                    u16FormatTag = (U16)WAVE_FORMAT_IMA_ADPCM;
                                    break;

                                default:
                                    bRet = FALSE;
                                    break;
                            }
                            u16Channels = MAKEU16(pu8Data, 5);
                            u16BitsPerSample = MAKEU16(pu8Data, 7);
                            u32SamplesPerSec = MAKEU32(pu8Data, 9);
                            bBigEndian = pu8Data[13];

                            if(bRet)
                            {
                                bRet = MApp_Music_PCM_SetInfo(u16FormatTag,u16Channels, u32SamplesPerSec, u16BitsPerSample,bBigEndian);
                            }
                            u32Data = (U32) bRet;
                        }
                        break;

                    case MPLAYER_OPTION_ZOOM:
                        if (m_eMplayerState[eType] == MPLAYER_STATE_PLAYING)
                        {
                            if (eType == E_MPLAYER_MEDIA_MOVIE)
                            {
                                m_eZoom = (VDPLAYER_ZOOM_FACT)u32Param;
                                MApp_VDPlayer_ScaleVideo(m_eZoom);
                            }
                            else if ((eType == E_MPLAYER_MEDIA_PHOTO) && (_gePhoto_State[_gu8Photo_DisplayIdx] == E_PHOTO_SLOT_STATE_DISPLAYING))
                            {
                                EN_PHOTO_ZOOMING ePhotoZoom;
                                E_ZOOM eZoom;
                                BOOLEAN bRet = FALSE;

                                // transform zoom factor
                                eZoom = (E_ZOOM)u32Param;
                                ePhotoZoom = _msAPI_NPlayer_Photo_TransformZoomFactor(eZoom);
                                if (ePhotoZoom == EN_PHOTO_ZOOM_NOT_SUPPORT)
                                {
                                    bRet = FALSE;
                                }
                                else
                                {
                                    // send cmd
                                    bRet = MApp_Photo_Zooming(ePhotoZoom);
                                }

                                // save setting
                                if (bRet == TRUE)
                                {
                                    m_ViewInfo[eType].s16ShiftX = 0;
                                    m_ViewInfo[eType].s16ShiftY = 0;
                                    m_ViewInfo[eType].eZoom = eZoom;

                                    // auto pause for photo siide show
                                    if (eType == E_MPLAYER_MEDIA_PHOTO)
                                    {
                                        _gePhoto_SlideShowPauseState = E_PHOTO_SLIDE_SHOW_PAUSED;
                                        m_eTrickMode[eType] = MPLAYER_TRICK_PAUSE;
                                    }
                                }
                                u32Data = (U32) bRet;
                            }
                        }
                        break;

                    case MPLAYER_OPTION_ROTATION:
                        {
                            EN_PHOTO_ROTATION ePhotoRotation;
                            E_ROTATION eRotation;
                            BOOLEAN bRet = FALSE;

                            eRotation = (E_ROTATION)u32Param;
                            // state checking
                            // allowed when media IS playing
                            if (!msAPI_NPlayer_IsPlaying(eType))
                            {
                                // exception for photo
                                if ((eType == E_MPLAYER_MEDIA_PHOTO)
                                        && (_gePhoto_State[_gu8Photo_DisplayIdx] == E_PHOTO_SLOT_STATE_DISPLAYING))
                                {
                                    // allow when there is photo displaying
                                }
                                else
                                {
                                    return  (U32)FALSE;
                                }
                            }

                            if(eType == E_MPLAYER_MEDIA_PHOTO)
                            {
                                // transform zoom factor
                                ePhotoRotation = _msAPI_NPlayer_Photo_TransformRotation(eRotation);
                                if (ePhotoRotation == EN_PHOTO_ROTATE_NOT_SUPPORT)
                                {
                                    bRet = FALSE;
                                }
                                else
                                {
                                    // send cmd
                                    bRet = MApp_Photo_Rotate(ePhotoRotation);
                                }
                            }
                            else
                            {
                                //not support for video and music now
                                bRet = FALSE;
                            }
                                // save setting
                            if (bRet == TRUE)
                            {
                                m_ViewInfo[eType].eRotation = eRotation;

                                // auto pause for photo siide show
                                if (eType == E_MPLAYER_MEDIA_PHOTO)
                                {
                                    _gePhoto_SlideShowPauseState = E_PHOTO_SLIDE_SHOW_PAUSED;

                                    m_eTrickMode[eType] = MPLAYER_TRICK_PAUSE;
                                }
                            }
                            u32Data = (U32) bRet;
                        }

                        break;

                    case MPLAYER_OPTION_MOVE_VIEW:
                        {
                            EN_PHOTO_DIRECTION ePhotoMoveDirection;
                            E_DIRECTION eDirection;
                            BOOLEAN bRet = FALSE;
                            S16 s16X,s16Y;
                            U16 u16Offset;

                            eDirection = (E_DIRECTION)pu8Data[4];
                            u16Offset = MAKEU16(pu8Data, 5);

                            // state checking
                            // allowed when media IS playing
                            if (!msAPI_NPlayer_IsPlaying(eType))
                            {
                                // exception for photo
                                if ((eType == E_MPLAYER_MEDIA_PHOTO)
                                        && (_gePhoto_State[_gu8Photo_DisplayIdx] == E_PHOTO_SLOT_STATE_DISPLAYING))
                                {
                                    // allow when there is photo displaying
                                }
                                else
                                {
                                    return  (U32)FALSE;
                                }
                            }

                                // calculate shift quantity
                            s16X = m_ViewInfo[eType].s16ShiftX;
                            s16Y = m_ViewInfo[eType].s16ShiftY;
                            switch(eDirection)
                            {
                                case E_DIRECTION_UP:
                                    s16Y -= u16Offset;
                                    break;

                                case E_DIRECTION_DOWN:
                                    s16Y += u16Offset;
                                    break;

                                case E_DIRECTION_LEFT:
                                    s16X -= u16Offset;
                                    break;

                                case E_DIRECTION_RIGHT:
                                    s16X += u16Offset;
                                    break;

                                default:
                                    return FALSE;
                            }

                            if(eType == E_MPLAYER_MEDIA_PHOTO)
                            {
                                // transform zoom factor
                                ePhotoMoveDirection = _msAPI_NPlayer_Photo_TransformDirection(eDirection);
                                if (ePhotoMoveDirection == EN_PHOTO_MOVE_NOT_SUPPORT)
                                {
                                    bRet = FALSE;
                                }
                                else
                                {
                                    // send cmd
                                    bRet = MApp_Photo_MoveViewWindow(ePhotoMoveDirection,u16Offset);
                                }
                            }
                            else
                            {
                                //not support for video and music now
                                bRet = FALSE;
                            }
                            // save setting
                            if (bRet == TRUE)
                            {
                                m_ViewInfo[eType].s16ShiftX = s16X;
                                m_ViewInfo[eType].s16ShiftY = s16Y;

                                // auto pause for photo siide show
                                if (eType == E_MPLAYER_MEDIA_PHOTO)
                                {
                                    _gePhoto_SlideShowPauseState = E_PHOTO_SLIDE_SHOW_PAUSED;

                                    m_eTrickMode[eType] = MPLAYER_TRICK_PAUSE;
                                }
                            }
                            u32Data = (U32) bRet;
                        }
                        break;

                    case MPLAYER_OPTION_STOP_PHOTO_DISPLAY:
                        _msAPI_NPlayer_Photo_StopDisplay();
                        break;

                    case MPLAYER_OPTION_ENABLE_SLIDE_SHOW:
                        MApp_Photo_SlideShow(TRUE);
                        break;

                    case MPLAYER_OPTION_DISABLE_SLIDE_SHOW:
                        MApp_Photo_SlideShow(FALSE);
                        break;

                    case MPLAYER_OPTION_SET_SLIDE_SHOW_TIMEOUT:
                        _gu16Photo_SlideShowTimeOutInSec = u32Param;
                        MPLAYER_MSG_DBG("SlideShowTimeOutInSec:%d\n",_gu16Photo_SlideShowTimeOutInSec);
                        break;

                    case MPLAYER_OPTION_CAPTURE_LOGO:
                        #if (DISPLAY_LOGO)
                        {
                            MPLAYER_MSG_TRACE("save logo now \n");
                            if(MApp_MPlayer_CaptureLogo() != E_MPLAYER_RET_OK)
                            {
                                MPLAYER_MSG_ERR("save logo fail\n");
                                u32Data = (U32)FALSE;
                            }
                        }
                        #endif
                        break;

                    case MPLAYER_OPTION_CAPTURE_LOGO_BYADDR:
                    #if (DISPLAY_LOGO)
                        {
                            U32 u32SrcAddr;
                            U32 u32Pitch, u32Width, u32Height;
                            GFX_Buffer_Format SrcFmt;
                            EN_CAPTURE_SRC_FORMAT fmt;

                            u32SrcAddr = MAKEU32(pu8Data, 4);
                            u32Pitch = MAKEU32(pu8Data, 8);
                            u32Width = MAKEU32(pu8Data, 12);
                            u32Height = MAKEU32(pu8Data, 16);
                            fmt = (EN_CAPTURE_SRC_FORMAT)pu8Data[20];
                            switch(fmt)
                            {
                                case E_FMT_RGB565:
                                    SrcFmt = GFX_FMT_RGB565;
                                    break;

                                case E_FMT_ARGB8888:
                                    SrcFmt = GFX_FMT_ARGB8888;
                                    break;

                                case E_FMT_YUV422:
                                    SrcFmt = GFX_FMT_YUV422;
                                    break;

                                default:
                                    u32Data = (U32)FALSE;
                                    MPLAYER_MSG_ERR("capture source format:%x is not supported!\n",(U8)fmt);
                                    break;
                            }
                            if(u32Data != FALSE)
                            {
                                MPLAYER_MSG_TRACE("save logo now \n");
                                if(MApp_MPlayer_CaptureLogoByAddr(u32SrcAddr, u32Pitch, u32Width, u32Height, SrcFmt) != E_MPLAYER_RET_OK)
                                {
                                    MPLAYER_MSG_ERR("save logo fail\n");
                                    u32Data = (U32)FALSE;
                                }
                            }
                        }
                    #endif
                        break;

                    case MPLAYER_OPTION_PHOTO_ONLY_DECODE:
                        _gbPhotoOnlyDecode = TRUE;
                        break;

                    case MPLAYER_OPTION_REPEATAB:
                        u32Data = (U32)TRUE;
                        if ((eType != E_MPLAYER_MEDIA_MOVIE) || (m_eTrickMode[eType] != E_MPLAYER_MOVIE_NORMAL))
                        {
                            MPLAYER_MSG_ERR("mpalyer play mode error\n");
                            u32Data = (U32)FALSE;
                            break;
                        }

                        if (m_eMplayerState[eType] == MPLAYER_STATE_PLAYING)
                        {
                            if (MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_MAX_FB_SPEED) == 0)
                            {
                                MPLAYER_MSG_ERR("movie without index table\n");
                                u32Data = (U32)FALSE;
                                break;
                            }
                            if(u32Param== REPEATAB_MODE_A)
                            {// Repeat A
                                MPLAYER_MSG_INFO("repeat A\n");
                                m_enRpeatABMode = REPEATAB_MODE_A;
                                m_u32MovieRepeatTime[0] = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CUR_TIME);
                                MApp_VDPlayer_SetRepeatAB((EN_SET_REPEATAB)m_enRpeatABMode);
                            }
                            else if(u32Param == REPEATAB_MODE_AB)
                            {// Repeat B
                                MPLAYER_MSG_INFO("repeat AB\n");
                                if(m_enRpeatABMode != REPEATAB_MODE_A)
                                {
                                    MPLAYER_MSG_ERR("has not set repeat mode A\n");
                                    u32Data = (U32)FALSE;
                                    break;
                                }
                                m_enRpeatABMode = REPEATAB_MODE_AB;
                                m_u32MovieRepeatTime[1] = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CUR_TIME);
                                if( m_u32MovieRepeatTime[1] >  m_u32MovieRepeatTime[0])
                                {
                                    MApp_VDPlayer_SetRepeatAB((EN_SET_REPEATAB)m_enRpeatABMode);
                                    _msAPI_NPlayer_ReinitRepeatABSubtitle();
                                }
                                else
                                {
                                    MPLAYER_MSG_ERR("Invalid timer : B <= A\n");
                                    _msAPI_NPlayer_MovieCancelRepeatAB();
                                    u32Data = (U32)FALSE;
                                }
                            }
                            else
                            {// Clear A->B
                                MPLAYER_MSG_INFO("repeat cancel\n");
                                _msAPI_NPlayer_MovieCancelRepeatAB();
                            }
                        }
                        break;

                    case MPLAYER_OPTION_SET_DRM_KEY:
                        {
                            U32 u32Size = MAKEU32(pu8Data, 4);
                            u32Data = (U32)MApp_VDPlayer_WMDRMPD_SavePrivate(&pu8Data[8], u32Size);
                            MPLAYER_MSG_DBG("set DRM key size = %d, key data:%x%x%x%x...\n", u32Size,pu8Data[8],pu8Data[9],pu8Data[10],pu8Data[11]);
                        }
                        break;

                    case MPLAYER_OPTION_SET_SUBTITLE_DELAY:
                        if (m_eMplayerState[eType] == MPLAYER_STATE_PLAYING)
                        {
                            U32 u32steps = MAKEU32(pu8Data, 4);
                            MApp_VDPlayer_SubtitleTimeShift(0, 0);
                            MApp_MPlayer_SetSubtitleDelaySteps(u32steps);
                            MPLAYER_MSG_MUST("set subtitle delay steps = %d\n", u32steps);
                        }
                        break;

                    case MPLAYER_OPTION_SET_SUBTITLE_ADVANCE:
                        if (m_eMplayerState[eType] == MPLAYER_STATE_PLAYING)
                        {
                            U32 u32steps = MAKEU32(pu8Data, 4);
                            MPLAYER_MSG_MUST("set subtitle advance steps = %d\n", u32steps);
                            if( MApp_VDPlayer_SubtitleTimeShift(0, u32steps* 100) )
                            {
                                MApp_MPlayer_SetSubtitleAdvanceSteps(u32steps);
                            }
                        }
                        break;

                    case MPLAYER_OPTION_CANCEL_SUBTITLE_DELAY_ADVANCE:
                        if (m_eMplayerState[eType] == MPLAYER_STATE_PLAYING)
                        {
                            MPLAYER_MSG_MUST("cancel subtitle delay/advance steps.\n");
                            MApp_VDPlayer_SubtitleTimeShift(0, 0);
                            MApp_MPlayer_SetSubtitleDelaySteps(0);
                            MApp_MPlayer_SetSubtitleAdvanceSteps(0);
                        }
                        break;

                    case MPLAYER_OPTION_BACKLIGHT_ON_OFF:
                        m_bBacklightOnOff = u32Param;
                        if(m_bBacklightOnOff == TRUE)
                            MApi_PNL_SetBackLight(TRUE);
                        else
                            MApi_PNL_SetBackLight(FALSE);
                        break;

                    case MPLAYER_OPTION_MEMC_ON_OFF:
                        m_bMemcOnOff = u32Param;
                        break;

                    case MPLAYER_OPTION_TRANSMIT_KEY:
                        m_u8TransmitKey = u32Param;
                        break;

                    default:
                        break;
                }
            }
            break;

        case MPLAYER_COMMAND_GET_OPTION:
            eType = (EN_MPLAYER_MEDIA_TYPE)pu8Data[2];
            if (eType >= E_MPLAYER_MEDIA_INVALID)
            {
                MPLAYER_MSG_ERR("Wrong media type setting for get option:%x!!!\n", eType);
                return 0;
            }
            EN_MPLAYER_OPTION_TYPE eOption = (EN_MPLAYER_OPTION_TYPE)pu8Data[3];

            switch (eOption)
            {
                case MPLAYER_OPTION_TRICK_MODE:
                    u32Data = m_eTrickMode[eType];
                    break;

                case MPLAYER_OPTION_ASPECT_RATIO:
                    u32Data = ST_VIDEO.eAspectRatio;
                    break;

                case MPLAYER_OPTION_PICTURE_MODE:
                    u32Data = ST_VIDEO.ePicture;
                    break;

                case MPLAYER_OPTION_SET_SEAMLESS_MODE:
                #if SEAMLESS_PLAYING_ENABLE
                    u32Data = MApp_VDPlayer_GetSeamlessMode();
                #else
                    u32Data = 0;
                #endif
                    break;

                case MPLAYER_OPTION_BACKLIGHT_ON_OFF:
                    u32Data = m_bBacklightOnOff;
                    break;

                case MPLAYER_OPTION_MEMC_ON_OFF:
                    u32Data = m_bMemcOnOff;
                    break;

                case MPLAYER_OPTION_TRANSMIT_KEY:
                    u32Data = m_u8TransmitKey;
                    break;

                case MPLAYER_OPTION_GET_MUSIC_TYPE:
                    u32Data = (U32) _geMPLAYER_MusicType;
                    break;

                case MPLAYER_OPTION_VOLUME:
                    u32Data = stGenSetting.g_SoundSetting.Volume;
                    break;

                case MPLAYER_OPTION_MUTE:
                    u32Data = msAPI_AUD_IsAudioMutedByUser();
                    break;

                case MPLAYER_OPTION_DISABLE_MUSIC_LYRIC:
                    if(m_eMusicFlag & E_MPLAYER_MUSIC_FLG_LYRIC_VALID)
                    {
                        u32Data = (U32)TRUE;
                    }
                    else
                    {
                        u32Data = (U32)FALSE;
                    }
                    break;

                case MPLAYER_OPTION_MUSIC_SHARE_MEM_ADDR:
                    u32Data = m_u32MusicShareMemAddr;
                    break;

                case MPLAYER_OPTION_MUSIC_SHARE_MEM_SIZE:
                    u32Data = m_u32MusicShareMemLength;
                    break;

                case MPLAYER_OPTION_MUSIC_INFO:
                    {
                        EN_MPLAYER_INFO eMusicInfoType;
                        U8* pu8String;
                        U32 u32StrLen;
                        U16* u16pCharBuf = (U16*)_msAPI_NPlayer_GetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO);

                        eMusicInfoType = (EN_MPLAYER_INFO)MAKEU32(pu8Data, 4);
                        switch(eMusicInfoType)
                        {
                            case MPLAYER_INFO_MUSIC_LAYER_LEN:
                                if(_geMPLAYER_MusicType == MPLAYER_SUBTYPE_MP3)
                                {
                                    u32StrLen = (U32)MApp_Music_GetInfoStringLength(MP3_INFO_LAYER);
                                    if (u32StrLen != 0)
                                    {
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }

                                break;

                            case MPLAYER_INFO_MUSIC_BITRATE_LEN:
                                if(_geMPLAYER_MusicType == MPLAYER_SUBTYPE_MP3)
                                {
                                    u32StrLen = 12;
                                    if (u32StrLen != 0)
                                    {
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }
                                else
                                {
                                    u32StrLen = 32;
                                    if (u32StrLen != 0)
                                    {
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }
                                break;

                            case MPLAYER_INFO_MUSIC_SAMPLINGRATE_LEN:
                                if(_geMPLAYER_MusicType == MPLAYER_SUBTYPE_MP3)
                                {
                                    u32StrLen = 12;
                                    if (u32StrLen != 0)
                                    {
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }
                                else
                                {
                                    u32StrLen = 32;
                                    if (u32StrLen != 0)
                                    {
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }
                                break;

                            case MPLAYER_INFO_MUSIC_ALBUM_LEN:
                                if(_geMPLAYER_MusicType == MPLAYER_SUBTYPE_MP3)
                                {
                                    u32StrLen = (U32)MApp_Music_GetInfoStringLength(MP3_INFO_ALBUM);
                                    u32StrLen = u32StrLen*2; //it will be converted to unicode
                                    if (u32StrLen != 0)
                                    {
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }
                                else
                                {
                                    u32StrLen = 32*2;
                                    if (u32StrLen != 0)
                                    {
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }
                                break;

                            case MPLAYER_INFO_MUSIC_TITLE_LEN:
                                if(_geMPLAYER_MusicType == MPLAYER_SUBTYPE_MP3)
                                {
                                    u32StrLen = (U32)MApp_Music_GetInfoStringLength(MP3_INFO_TITLE);
                                    u32StrLen = u32StrLen*2; //it will be converted to unicode
                                    if (u32StrLen != 0)
                                    {
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }
                                else
                                {
                                    u32StrLen = 32*2;
                                    if (u32StrLen != 0)
                                    {
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }
                                break;

                            case MPLAYER_INFO_MUSIC_ARTIST_LEN:
                                if(_geMPLAYER_MusicType == MPLAYER_SUBTYPE_MP3)
                                {
                                    u32StrLen = (U32)MApp_Music_GetInfoStringLength(MP3_INFO_ARTIST);
                                    u32StrLen = u32StrLen*2; //it will be converted to unicode
                                    if (u32StrLen != 0)
                                    {
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }
                                else
                                {
                                    u32StrLen = 32*2;
                                    if (u32StrLen != 0)
                                    {
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }
                                break;

                            case MPLAYER_INFO_MUSIC_YEAR_LEN:
                                if(_geMPLAYER_MusicType == MPLAYER_SUBTYPE_MP3)
                                {
                                    u32StrLen = (U32)MApp_Music_GetInfoStringLength(MP3_INFO_YEAR);
                                    u32StrLen = u32StrLen*2; //it will be convert unicode
                                    if (u32StrLen != 0)
                                    {
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }
                                else
                                {
                                    u32StrLen = 32*2;
                                    if (u32StrLen != 0)
                                    {
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }
                                break;

                            case MPLAYER_INFO_MUSIC_GENRE_LEN:
                                if(_geMPLAYER_MusicType == MPLAYER_SUBTYPE_MP3)
                                {
                                    u32StrLen = (U32)MApp_Music_GetInfoStringLength(MP3_INFO_GENRE);
                                    if (u32StrLen != 0)
                                    {
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }
                                break;

                            case MPLAYER_INFO_MUSIC_COMMENT_LEN:
                                if(_geMPLAYER_MusicType == MPLAYER_SUBTYPE_MP3)
                                {
                                    u32StrLen = (U32)MApp_Music_GetInfoStringLength(MP3_INFO_COMMENT);
                                    if (u32StrLen != 0)
                                    {
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }
                                break;

                            case MPLAYER_INFO_MUSIC_CHECK_FF_FB_LEN:
                                if(_geMPLAYER_MusicType == MPLAYER_SUBTYPE_MP3)
                                {
                                    u32StrLen = (U32)MApp_Music_GetInfoStringLength(MP3_INFO_CHECK_FF_FB);
                                    if (u32StrLen != 0)
                                    {
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }
                                else
                                {
                                    u32StrLen = 32;
                                    if (u32StrLen != 0)
                                    {
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }
                                break;
                            case MPLAYER_INFO_MUSIC_LAYER:
                                if(_geMPLAYER_MusicType == MPLAYER_SUBTYPE_MP3)
                                {
                                    pu8String = MApp_Music_GetInfoString(MP3_INFO_LAYER, NULL);
                                    u32StrLen = (U32)MApp_Music_GetInfoStringLength(MP3_INFO_LAYER);
                                    if (pu8String != NULL && u32StrLen > 0)
                                    {
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO,pu8String,u32StrLen);
                                        u32Data = TRUE;
                                    }
                                }

                                break;

                            case MPLAYER_INFO_MUSIC_BITRATE:
                                if(_geMPLAYER_MusicType == MPLAYER_SUBTYPE_MP3)
                                {
                                    pu8String = MApp_Music_GetInfoString(MP3_INFO_BITRATE, NULL);
                                    u32StrLen = 12;
                                    if (pu8String != NULL)
                                    {
                                        memset((U8*)u16pCharBuf,0,u32StrLen);
                                        snprintf((char*)u16pCharBuf, 6, "%s", pu8String);
                                        FS_ASCII2Unicode((U8*)u16pCharBuf);
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }
                                else
                                {
                                    pu8String = MApp_WMA_GetInfoString(WMA_INFO_BITRATE, NULL);
                                    u32StrLen = 32;
                                    if (pu8String != NULL)
                                    {
                                        memset((U8*)u16pCharBuf,0,u32StrLen);
                                        snprintf((char*)u16pCharBuf, 6, "%s", pu8String);
                                        FS_ASCII2Unicode((U8*)u16pCharBuf);
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }
                                break;

                            case MPLAYER_INFO_MUSIC_SAMPLINGRATE:
                                if(_geMPLAYER_MusicType == MPLAYER_SUBTYPE_MP3)
                                {
                                    pu8String = MApp_Music_GetInfoString(MP3_INFO_SAMPLINGRATE, NULL);
                                    u32StrLen =12;
                                    if (pu8String != NULL)
                                    {
                                        memset((U8*)u16pCharBuf,0,u32StrLen);
                                        snprintf((char*)u16pCharBuf, 6, "%s", pu8String);
                                        FS_ASCII2Unicode((U8*)u16pCharBuf);
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }
                                else
                                {
                                    pu8String = MApp_WMA_GetInfoString(WMA_INFO_SAMPLINGRATE, NULL);
                                    u32StrLen = 32;
                                    if (pu8String != NULL)
                                    {
                                        memset((U8*)u16pCharBuf,0,u32StrLen);
                                        snprintf((char*)u16pCharBuf, 6, "%s", pu8String);
                                        FS_ASCII2Unicode((U8*)u16pCharBuf);
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }
                                break;

                            case MPLAYER_INFO_MUSIC_ALBUM:
                                if(_geMPLAYER_MusicType == MPLAYER_SUBTYPE_MP3)
                                {
                                    pu8String = MApp_Music_GetInfoString(MP3_INFO_ALBUM, NULL);
                                    u32StrLen = (U32)MApp_Music_GetInfoStringLength(MP3_INFO_ALBUM);
                                    if (pu8String != NULL)
                                    {
                                        _msAPI_NPlayer_ConvertMusicString2Unicode(pu8String, u16pCharBuf, u32StrLen);
                                        u32StrLen = u32StrLen*2;
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }
                                else
                                {
                                    pu8String = MApp_WMA_GetInfoString(WMA_INFO_ALBUM, NULL);
                                    u32StrLen = 32;
                                    if (pu8String != NULL)
                                    {
                                        _msAPI_NPlayer_ConvertMusicString2Unicode(pu8String, u16pCharBuf, u32StrLen);
                                        u32StrLen = u32StrLen*2;
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }
                                break;

                            case MPLAYER_INFO_MUSIC_TITLE:
                                if(_geMPLAYER_MusicType == MPLAYER_SUBTYPE_MP3)
                                {
                                    pu8String = MApp_Music_GetInfoString(MP3_INFO_TITLE, NULL);
                                    u32StrLen = (U32)MApp_Music_GetInfoStringLength(MP3_INFO_TITLE);

                                    if (pu8String != NULL)
                                    {
                                        _msAPI_NPlayer_ConvertMusicString2Unicode(pu8String, u16pCharBuf, u32StrLen);
                                        u32StrLen = u32StrLen*2;

                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }
                                else
                                {
                                    pu8String = MApp_WMA_GetInfoString(WMA_INFO_TITLE, NULL);
                                    u32StrLen = 32;
                                    if (pu8String != NULL)
                                    {
                                        _msAPI_NPlayer_ConvertMusicString2Unicode(pu8String, u16pCharBuf, u32StrLen);
                                        u32StrLen = u32StrLen*2;
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }
                                break;

                            case MPLAYER_INFO_MUSIC_ARTIST:
                                if(_geMPLAYER_MusicType == MPLAYER_SUBTYPE_MP3)
                                {
                                    pu8String = MApp_Music_GetInfoString(MP3_INFO_ARTIST NULL);
                                    u32StrLen = (U32)MApp_Music_GetInfoStringLength(MP3_INFO_ARTIST);
                                    if (pu8String != NULL)
                                    {
                                        _msAPI_NPlayer_ConvertMusicString2Unicode(pu8String, u16pCharBuf, u32StrLen);
                                        u32StrLen = u32StrLen*2;
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }
                                else
                                {
                                    pu8String = MApp_WMA_GetInfoString(WMA_INFO_ARTIST, NULL);
                                    u32StrLen = 32;
                                    if (pu8String != NULL)
                                    {
                                        _msAPI_NPlayer_ConvertMusicString2Unicode(pu8String, u16pCharBuf, u32StrLen);
                                        u32StrLen = u32StrLen*2;
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }
                                break;

                            case MPLAYER_INFO_MUSIC_YEAR:
                                if(_geMPLAYER_MusicType == MPLAYER_SUBTYPE_MP3)
                                {
                                    pu8String = MApp_Music_GetInfoString(MP3_INFO_YEAR, NULL);
                                    u32StrLen = (U32)MApp_Music_GetInfoStringLength(MP3_INFO_YEAR);
                                    if (pu8String != NULL)
                                    {
                                        _msAPI_NPlayer_ConvertMusicString2Unicode(pu8String, u16pCharBuf, u32StrLen);
                                        u32StrLen = u32StrLen*2;
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }
                                else
                                {
                                    pu8String = MApp_WMA_GetInfoString(WMA_INFO_YEAR, NULL);
                                    u32StrLen = 32;
                                    if (pu8String != NULL)
                                    {
                                        _msAPI_NPlayer_ConvertMusicString2Unicode(pu8String, u16pCharBuf, u32StrLen);
                                        u32StrLen = u32StrLen*2;
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        u32Data = TRUE;
                                    }
                                }
                                break;

                            case MPLAYER_INFO_MUSIC_GENRE:
                                if(_geMPLAYER_MusicType == MPLAYER_SUBTYPE_MP3)
                                {
                                    pu8String = MApp_Music_GetInfoString(MP3_INFO_GENRE, NULL);
                                    u32StrLen = (U32)MApp_Music_GetInfoStringLength(MP3_INFO_GENRE);
                                    if (pu8String != NULL)
                                    {
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO,pu8String,u32StrLen);
                                        u32Data = TRUE;
                                    }
                                }
                                break;

                            case MPLAYER_INFO_MUSIC_COMMENT:
                                if(_geMPLAYER_MusicType == MPLAYER_SUBTYPE_MP3)
                                {
                                    pu8String = MApp_Music_GetInfoString(MP3_INFO_COMMENT, NULL);
                                    u32StrLen = (U32)MApp_Music_GetInfoStringLength(MP3_INFO_COMMENT);
                                    if (pu8String != NULL)
                                    {
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO,pu8String,u32StrLen);
                                        u32Data = TRUE;
                                    }
                                }
                                break;

                            case MPLAYER_INFO_MUSIC_CHECK_FF_FB:
                                if(_geMPLAYER_MusicType == MPLAYER_SUBTYPE_MP3)
                                {
                                    pu8String = MApp_Music_GetInfoString(MP3_INFO_CHECK_FF_FB, NULL);
                                    u32StrLen = (U32)MApp_Music_GetInfoStringLength(MP3_INFO_CHECK_FF_FB);
                                    if (pu8String != NULL)
                                    {
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO,pu8String,u32StrLen);
                                        u32Data = TRUE;
                                    }
                                }
                                else
                                {
                                    pu8String = MApp_WMA_GetInfoString(WMA_INFO_CHECK_FF_FB, NULL);
                                    u32StrLen = 32;
                                    if (pu8String != NULL)
                                    {
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_TYPE,(U8*)&eMusicInfoType,sizeof(eMusicInfoType));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO_LEN,(U8*)&u32StrLen,sizeof(u32StrLen));
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_STRING_INFO,pu8String,u32StrLen);
                                        u32Data = TRUE;
                                    }
                                }
                                break;

                            case MPLAYER_INFO_MUSIC_ERROR_CODE:
                                if(_geMPLAYER_MusicType == MPLAYER_SUBTYPE_MP3)
                                {
                                    u32Data = (U32)MApp_Music_GetErrCode();
                                }
                                else
                                {
                                    u32Data = (U32)MApp_Wma_GetErrCode();
                                }
                                break;

                            default:
                                break;
                        }
                    }
                    break;

                case MPLAYER_OPTION_ZOOM:
                    if (m_eMplayerState[eType] == MPLAYER_STATE_PLAYING)
                    {
                        if (eType == E_MPLAYER_MEDIA_MOVIE)
                        {
                            u32Data = m_eZoom;
                        }
                        else if ((eType == E_MPLAYER_MEDIA_PHOTO) && (_gePhoto_State[_gu8Photo_DisplayIdx] == E_PHOTO_SLOT_STATE_DISPLAYING))
                        {
                            u32Data = (U32)m_ViewInfo[eType].eZoom;
                        }
                        else
                        {
                            u32Data = (U32)E_ZOOM_1;
                        }
                    }
                    else
                    {
                        u32Data = (U32)E_ZOOM_1;
                    }
                    break;

                case MPLAYER_OPTION_ROTATION:
                    {
                        // state checking
                        // allowed when media IS playing
                        if (!msAPI_NPlayer_IsPlaying(eType))
                        {
                            // exception for photo
                            if ((eType == E_MPLAYER_MEDIA_PHOTO)
                                    && (_gePhoto_State[_gu8Photo_DisplayIdx] == E_PHOTO_SLOT_STATE_DISPLAYING))
                            {
                                // allow when there is photo displaying
                            }
                            else
                            {
                                return  (U32)E_ROTATION_0;
                            }
                        }

                        if(eType == E_MPLAYER_MEDIA_PHOTO)
                        {
                            u32Data = (U32)m_ViewInfo[eType].eRotation;
                        }
                        else
                        {
                            //not support for video and music now
                            u32Data = (U32)E_ROTATION_0;
                        }
                    }
                    break;

                case MPLAYER_OPTION_GET_PHOTO_FREE_SLOT:
                    u32Data = _msAPI_NPlayer_Photo_GetFreeSlot();
                    if(_gePhoto_State[_gu8Photo_DecodeIdx] == E_PHOTO_SLOT_STATE_DECODING || m_eMplayerState[E_MPLAYER_MEDIA_PHOTO] == MPLAYER_STATE_PRE_INIT)
                    {
                        u32Data = 0;
                        MPLAYER_MSG_DBG("index :%x is decoding. Need wait  or pre-picture not finish init.\n",_gu8Photo_DecodeIdx);
                    }
                    break;

                case MPLAYER_OPTION_GET_PHOTO_INFO:
                    {
                        EN_MPLAYER_INFO ePhotoInfoType;

                        ePhotoInfoType = (EN_MPLAYER_INFO)MAKEU32(pu8Data,4);
                        switch (ePhotoInfoType)
                        {
                            case MPLAYER_INFO_PHOTO_DISPLAYING_WIDTH:
                                return _gu16Photo_Wdith[_gu8Photo_DisplayIdx];

                            case MPLAYER_INFO_PHOTO_DISPLAYING_HEIGHT:
                                return _gu16Photo_Height[_gu8Photo_DisplayIdx];

                            case MPLAYER_INFO_PHOTO_DISPLAYING_SIZE:
                                return _gu32Photo_Size[_gu8Photo_DisplayIdx];

                            case MPLAYER_INFO_PHOTO_DECODED_WIDTH:
                                return _gu16Photo_Wdith[_gu8Photo_DecodeIdx];

                            case MPLAYER_INFO_PHOTO_DECODED_HEIGHT:
                                return _gu16Photo_Height[_gu8Photo_DecodeIdx];

                            case MPLAYER_INFO_PHOTO_IMAGE_ORIGINAL_WIDTH:
                                return MApp_Photo_GetInfo(E_PHOTO_INFO_IMAGE_WIDTH);

                            case MPLAYER_INFO_PHOTO_IMAGE_ORIGINAL_HEIGHT:
                                return MApp_Photo_GetInfo(E_PHOTO_INFO_IMAGE_HEIGHT);

                            case MPLAYER_INFO_PHOTO_DECODED_PITCH:
                                return MApp_Photo_GetInfo(E_PHOTO_INFO_PITCH);

                            case MPLAYER_INFO_PHOTO_DECODE_PROGRESS:
                                return MApp_Photo_GetInfo(E_PHOTO_INFO_PROGRESS);

                            case MPLAYER_INFO_PHOTO_DECODE_OUTBUF_ADDR:
                                return PHOTO_OUTPUT_BUFFER_ADDR;

                            case MPLAYER_INFO_PHOTO_ERROR_CODE:
                                return MApp_Photo_GetErrCode();

                            case MPLAYER_INFO_PHOTO_CODEC_TYPE:
                                {
                                    EN_MPLAYER_SUB_TYPE PhotoType;

                                    switch(MApp_Photo_GetInfo(E_PHOTO_INFO_FILE_FORMAT))
                                    {
                                        case E_PHOTO_FILE_JPEG:
                                            PhotoType = MPLAYER_SUBTYPE_JPEG;
                                            break;
                                        case E_PHOTO_FILE_BMP:
                                            PhotoType = MPLAYER_SUBTYPE_BMP;
                                            break;
                                        case E_PHOTO_FILE_PNG:
                                            PhotoType = MPLAYER_SUBTYPE_PNG;
                                            break;
                                        default:
                                            PhotoType = MPLAYER_SUBTYPE_UNKNOWN;
                                            break;
                                    }
                                    return PhotoType;
                                }

                            default:
                                break;
                        }
                    }
                    break;

                case MPLAYER_OPTION_GET_MOVIE_THUMBNAIL_INFO:
                    {
                        EN_MPLAYER_INFO eInfoType = (EN_MPLAYER_INFO)MAKEU32(pu8Data,4);
                        switch (eInfoType)
                        {
                            case MPLAYER_INFO_MOVIE_THUMBNAIL_WIDTH:
                                return m_sCaptureRect.u16RectW;
                                break;
                            case MPLAYER_INFO_MOVIE_THUMBNAIL_HEIGHT:
                                return m_sCaptureRect.u16RectH;
                                break;
                            case MPLAYER_INFO_MOVIE_THUMBNAIL_PITCH:
                                return (U32)(((m_sCaptureRect.u16RectW+7)>>3)<<3 )* 2;
                                break;
                            case MPLAYER_INFO_MOVIE_THUMBNAIL_OUTBUF_ADDR:
                                return m_sCaptureRect.u32BuffAddr;
                                break;
                            default:
                                break;
                        }
                    }
                    break;

                default:
                    break;
            }
            break;

        case MPLAYER_COMMAND_PAUSE:
            eType = (EN_MPLAYER_MEDIA_TYPE)pu8Data[2];
            if (eType >= E_MPLAYER_MEDIA_INVALID)
            {
                MPLAYER_MSG_ERR("Wrong media type setting for pause cmd:%x!!!\n", eType);
                return 0;
            }
            u32PID = MAKEU32(pu8Data, 3);

            if ((m_eBufferType[eType] == MPLAYER_BUFFER_NORMAL) &&
                (m_eTrickMode[eType] != MPLAYER_TRICK_PAUSE) &&
                (m_eStreamMode[eType] != MPLAYER_RTSP_MODE) &&
                (m_u32PID[eType] == u32PID))
            {
                msAPI_NPlayer_SetTrickMode(eType, MPLAYER_TRICK_PAUSE);
            }
            u32Data = m_eTrickMode[eType];
            break;

        case MPLAYER_COMMAND_RESUME:
            eType = (EN_MPLAYER_MEDIA_TYPE)pu8Data[2];
            if (eType >= E_MPLAYER_MEDIA_INVALID)
            {
                MPLAYER_MSG_ERR("Wrong media type setting for RESUME cmd:%x!!!\n", eType);
                return 0;
            }
            u32PID = MAKEU32(pu8Data, 3);

            if ((m_eBufferType[eType] == MPLAYER_BUFFER_NORMAL) &&
                (m_eTrickMode[eType] != MPLAYER_TRICK_NORMAL) &&
                (m_eStreamMode[eType] != MPLAYER_RTSP_MODE) &&
                (m_u32PID[eType] == u32PID))
            {
                msAPI_NPlayer_SetTrickMode(eType, MPLAYER_TRICK_NORMAL);
            }
            u32Data = m_eTrickMode[eType];
            break;

        case MPLAYER_COMMAND_FF:
            eType = (EN_MPLAYER_MEDIA_TYPE)pu8Data[2];
            if (eType >= E_MPLAYER_MEDIA_INVALID)
            {
                MPLAYER_MSG_ERR("Wrong media type setting for FF cmd:%x!!!\n", eType);
                return 0;
            }
            u32PID = MAKEU32(pu8Data, 3);

            if ((m_eBufferType[eType] == MPLAYER_BUFFER_NORMAL) &&
                (m_eStreamMode[eType] != MPLAYER_RTSP_MODE) &&
                (m_u32PID[eType] == u32PID))
            {
                if (m_eTrickMode[eType] < MPLAYER_TRICK_FF_2X || m_eTrickMode[eType] > MPLAYER_TRICK_FF_16X)
                {
                    msAPI_NPlayer_SetTrickMode(eType, MPLAYER_TRICK_FF_2X);
                }
                else if(m_eTrickMode[eType] == MPLAYER_TRICK_FF_16X)
                {
                    msAPI_NPlayer_SetTrickMode(eType, MPLAYER_TRICK_NORMAL);
                }
                else
                {
                    msAPI_NPlayer_SetTrickMode(eType, (EN_MPLAYER_TRICK_MODE)(m_eTrickMode[eType]+1));
                }
            }
            u32Data = m_eTrickMode[eType];
            break;

        case MPLAYER_COMMAND_RW:
            eType = (EN_MPLAYER_MEDIA_TYPE)pu8Data[2];
            if (eType >= E_MPLAYER_MEDIA_INVALID)
            {
                MPLAYER_MSG_ERR("Wrong media type setting for RW cmd:%x!!!\n", eType);
                return 0;
            }
            u32PID = MAKEU32(pu8Data, 3);

            if ((m_eBufferType[eType] == MPLAYER_BUFFER_NORMAL) &&
                (m_eStreamMode[eType] != MPLAYER_RTSP_MODE) &&
                (m_u32PID[eType] == u32PID))
            {
                if (eType != E_MPLAYER_MEDIA_MOVIE ||
                    ((eType == E_MPLAYER_MEDIA_MOVIE) &&  MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_MAX_FB_SPEED) != 0 ))
                {
                    if (m_eTrickMode[eType] < MPLAYER_TRICK_FB_2X || m_eTrickMode[eType] > MPLAYER_TRICK_FB_16X)
                    {
                        msAPI_NPlayer_SetTrickMode(eType, MPLAYER_TRICK_FB_2X);
                    }
                    else if(m_eTrickMode[eType] == MPLAYER_TRICK_FB_16X)
                    {
                        msAPI_NPlayer_SetTrickMode(eType, MPLAYER_TRICK_NORMAL);
                    }
                    else
                    {
                        msAPI_NPlayer_SetTrickMode(eType,(EN_MPLAYER_TRICK_MODE)(m_eTrickMode[eType]+1));
                    }
                }
                else if (m_eTrickMode[eType] != MPLAYER_TRICK_NORMAL)
                {
                    msAPI_NPlayer_SetTrickMode(eType, MPLAYER_TRICK_NORMAL);
                }
            }
            u32Data = m_eTrickMode[eType];
            break;

        case MPLAYER_COMMAND_SEEK:
            eType = (EN_MPLAYER_MEDIA_TYPE)pu8Data[2];
            if (eType >= E_MPLAYER_MEDIA_INVALID)
            {
                MPLAYER_MSG_ERR("Wrong media type setting for SEEK cmd:%x!!!\n", eType);
                return 0;
            }
            u32PID = MAKEU32(pu8Data, 7);

            if ((eType == E_MPLAYER_MEDIA_MOVIE) &&
                (m_eStreamMode[eType] != MPLAYER_RTSP_MODE) &&
                (m_eMplayerState[eType] == MPLAYER_STATE_PLAYING) &&
                (m_u32PID[eType] == u32PID))
            {
                U32 u32GotoTimeMs, u32Time;

                u32GotoTimeMs = MAKEU32(pu8Data, 3);
                u32Time = u32GotoTimeMs / 1000;
                MPLAYER_MSG_INFO("PlaySeek(%d)[%02d:", MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_MAX_FB_SPEED), u32Time/3600);
                u32Time %= 3600;
                MPLAYER_MSG_INFO("%02d:", u32Time/60);
                u32Time %= 60;
                MPLAYER_MSG_INFO("%02d]/", u32Time);
                u32Time = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_TOTAL_TIME) / 1000;
                MPLAYER_MSG_INFO("[%02d:", u32Time/3600);
                u32Time %= 3600;
                MPLAYER_MSG_INFO("%02d:", u32Time/60);
                u32Time %= 60;
                MPLAYER_MSG_INFO("%02d]\n", u32Time);

                if (u32GotoTimeMs < MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_TOTAL_TIME))
                {
                    if (MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_MAX_FB_SPEED) != 0)
                    {
                        if ((m_eStreamMode[eType] == MPLAYER_UNSEEKABLE_STREAM_MODE) || (m_eStreamMode[eType] == MPLAYER_SEEKABLE_STREAM_MODE))
                        {
                            msAPI_NPlayer_SendCmd(eType,MPLAYER_COMMAND_NOTIFY, MPLAYER_INSUFFICIENT_DATA);
                            MApp_VDPlayer_SetTrickMode(MODE_NORMAL_PLAY, PLAY_SPEEDx1);
                            MApp_VDPlayer_SetPlayPosition(u32GotoTimeMs);
                            MApp_VDPlayer_Pause();
                            m_eBufferType[eType] = MPLAYER_BUFFER_INSUFFICIENT;
                        }
                        else
                        {
                            MApp_VDPlayer_SetTrickMode(MODE_NORMAL_PLAY, PLAY_SPEEDx1);
                            MApp_VDPlayer_SetPlayPosition(u32GotoTimeMs);
                            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                        }
                        m_eTrickMode[eType] = MPLAYER_TRICK_NORMAL;
                        u32Data = TRUE;
                    }
                }
            }
            break;

        case MPLAYER_COMMAND_STOP:  //MApi_MPlayer_Ack
            eType = (EN_MPLAYER_MEDIA_TYPE)pu8Data[2];
            if (eType >= E_MPLAYER_MEDIA_INVALID)
            {
                MPLAYER_MSG_MUST("Wrong media type setting for stop cmd:%x!!!\n", eType);
                return 0;
            }
            if (m_u32PID[eType] == MAKEU32(pu8Data, 3))
            {
                msAPI_NPlayer_Stop(eType, MPLAYER_NOTIFY_NULL);
                u32Data = TRUE;
            }
            break;

        case MPLAYER_COMMAND_CAPTURE:
            eType = (EN_MPLAYER_MEDIA_TYPE)pu8Data[2];

            if ((eType == E_MPLAYER_MEDIA_MOVIE) && (m_eMplayerState[eType] == MPLAYER_STATE_PLAYING))
            {
                U8 *pu8Filename;
                U16 u16FileNameLen = 512;
                pu8Filename = (U8*)msAPI_Memory_Allocate(u16FileNameLen, BUF_ID_FILEBROWER);

                if (pu8Filename == NULL)
                {
                    __ASSERT(0);
                    u32Data = (U32)FALSE;
                    break;
                }
                if (_msAPI_NPlayer_GenCaptureFileName(pu8Filename, u16FileNameLen))
                {
                    U8 tempFBId = 31;
                    GOP_GwinFBAttr fbAttr;

                    if (MApi_GOP_GWIN_CreateFB(tempFBId, 0, 0, g_IPanel.Width(), g_IPanel.Height(), GFX_FMT_ARGB8888) != GWIN_OK)
                    {
                        MPLAYER_MSG_MUST("Cant allocate temp FB, capture fail!\n");
                    }
                    MApi_GOP_GWIN_GetFBInfo(tempFBId, &fbAttr);

                    if (!msAPI_NPlayer_SetTrickMode(eType, MPLAYER_TRICK_PAUSE))
                    {
                        msAPI_Memory_Free(pu8Filename, BUF_ID_FILEBROWER);
                        u32Data = (U32)FALSE;
                        break;
                    }
                #if (ENABLE_MPLAYER_VIDEO_CAPTURE)
                    if (!_MApp_MPlayer_CaptureVideo2JPGFile(pu8Filename, fbAttr.addr, fbAttr.size))// tempBuffer, tempSize) )
                    {
                        MPLAYER_MSG_MUST("CaptureVideo fail\n");
                        u32Data = (U32)FALSE;
                    }
                    else
                    {
                        MPLAYER_MSG_MUST("CaptureVideo finish\n");
                        u32Data = (U32)TRUE;
                    }
                #endif
                    msAPI_NPlayer_SetTrickMode(eType, MPLAYER_TRICK_NORMAL);
                    msAPI_Memory_Free(pu8Filename, BUF_ID_FILEBROWER);
                    MApi_GOP_GWIN_DestroyFB(tempFBId);
                }
            }
            break;
    }

    return u32Data;
}

//------------------------------------------------------------------------------
// Public Function Prototypes
//-----------------------------------------------------------------------------
BOOLEAN msAPI_NPlayer_IsPlaying(EN_MPLAYER_MEDIA_TYPE eType)
{
    return m_bNplayerPlay[eType];
}

//------------------------------------------------------------------------------
static U32 msAPI_NPlayer_CheckBuffer(EN_MPLAYER_MEDIA_TYPE eType,BOOLEAN bStart)
{
    BOOL bEof = FALSE;
    U32 u32StrmHdl = 0;
    U32 u32ReadPos;
    U32 u32WritePos;
    U32 u32BufferSize;
    S32 s32BufferRemainder = 0;
    U32 u32AbailableData = 0;

    if ((m_eStreamMode[eType] == MPLAYER_UNSEEKABLE_STREAM_MODE) || (m_eStreamMode[eType] == MPLAYER_SEEKABLE_STREAM_MODE))
    {
        static U32 u32Timer, u32Cnt;
        if (MsOS_GetSystemTime()-u32Timer > 100)
            u32Timer = MsOS_GetSystemTime();
        else
            return 0;

        u32ReadPos = RingBufferIndex32(u32StrmHdl, INDEX_STREAM_READ_POS);
        u32WritePos = RingBufferIndex32(u32StrmHdl, INDEX_STREAM_WRITE_POS);
        u32BufferSize = RingBufferIndex32(u32StrmHdl, INDEX_RING_BUFFER_END) - RingBufferIndex32(u32StrmHdl, INDEX_RING_BUFFER_START);
        if (u32WritePos > u32ReadPos)
            u32AbailableData = u32WritePos - u32ReadPos;
        else if (u32WritePos < u32ReadPos)
            u32AbailableData = u32BufferSize + u32WritePos - u32ReadPos;
        else if ((RingBufferIndex32(u32StrmHdl, INDEX_STREAM_FLAG) & STREAM_FLAG_FULL) == STREAM_FLAG_FULL)
            u32AbailableData = u32BufferSize;
        else
            u32AbailableData = 0;
        bEof = ((RingBufferIndex32(u32StrmHdl, INDEX_STREAM_FLAG) & STREAM_FLAG_EOF) == STREAM_FLAG_EOF);

        if (bStart)
        {
            return (bEof ? 0xFFFFFFFF : u32AbailableData);
        }
        else
        {
            S32 s32Diff, s32Div, s32Percent;
            s32BufferRemainder = u32AbailableData + MApp_VDPlayer_Get_Buffer_Info(E_BUFFER_INFO_LEVEL);

            if (MApp_VDPlayer_Get_Buffer_Info(E_BUFFER_INFO_BITRATE) > 0)
            {
                m_s32DiffBitrate = MApp_VDPlayer_Get_Buffer_Info(E_BUFFER_INFO_BITRATE) - RingBufferIndex32(0, INDEX_STREAM_BITRATE);
                m_s32MinBufferSize = (m_s32MinBufferSec*m_s32DiffBitrate*128);
                m_s32MaxBufferSize = (m_s32MaxBufferSec*m_s32DiffBitrate*128);
            }
            else
            {
                m_s32DiffBitrate = 0;
                m_s32MinBufferSize = m_s32MinBufferSec*0x20000;
                m_s32MaxBufferSize = m_s32MaxBufferSec*0x20000;
            }

            s32Diff = s32BufferRemainder - m_s32MinBufferSize;
            s32Div = m_s32MaxBufferSize - m_s32MinBufferSize;
            if ((s32Diff <= 0) || (s32Div <= 0))
                s32Percent = 0;
            else if (s32Diff >= s32Div)
                s32Percent = 100;
            else
                s32Percent = 100*s32Diff/s32Div;
            _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_BUFFER_INFO+E_SHAREMEM_BUFFER_INFO_SIZE-1, s32Percent);

            if (((++u32Cnt)%10) ==0)
            {
                MPLAYER_MSG_DBG("BF1:[%06X][%06d][%06d]", (U32)s32BufferRemainder, MApp_VDPlayer_Get_Buffer_Info(E_BUFFER_INFO_BITRATE), RingBufferIndex32(0, INDEX_STREAM_BITRATE));
                MPLAYER_MSG_DBG("[%06d][%06d]\n", MApp_VDPlayer_Get_Buffer_Info(E_BUFFER_INFO_DURATION), s32Percent);
            }

            if ((s32BufferRemainder < m_s32MinBufferSize) && (!bEof) && (u32AbailableData != u32BufferSize) && (m_s32DiffBitrate >= 0))
            {
                if (m_eBufferType[eType] == MPLAYER_BUFFER_NORMAL)
                {
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    msAPI_NPlayer_SendCmd(eType,MPLAYER_COMMAND_NOTIFY, MPLAYER_INSUFFICIENT_DATA);
                    MApp_VDPlayer_Pause();
                    m_eBufferType[eType] = MPLAYER_BUFFER_INSUFFICIENT;
                }
            }
            else if (((s32BufferRemainder >= m_s32MaxBufferSize) && (RingBufferIndex32(0, INDEX_STREAM_BITRATE) > 0)) || bEof || (u32AbailableData == u32BufferSize) || (m_s32DiffBitrate < 0))
            {
                if (m_eBufferType[eType] == MPLAYER_BUFFER_INSUFFICIENT)
                {
                    m_bCheckMute = TRUE;
                    m_u32MuteTimer = (U32)MsOS_GetSystemTime() + 250;
                    msAPI_NPlayer_SendCmd(eType,MPLAYER_COMMAND_NOTIFY, MPLAYER_SUFFICIENT_DATA);
                    MApp_VDPlayer_SetTrickMode(MODE_NORMAL_PLAY, PLAY_SPEEDx1);
                    m_eBufferType[eType] = MPLAYER_BUFFER_NORMAL;
                }
            }
            return 0xFFFFFFFF;
        }
    }
    else
    {
        return 0xFFFFFFFF;
    }
}

//-----------------------------------------------------------------------------
void msAPI_NPlayer_Task(void)
{
    static U32 u32Hdl_Video;
    U8 param[16];
    EN_RET eRet;

    //Measure loop time
    if (m_eDebugLevle >= MPLAYER_DBG_LEVEL_TRACE)
    {
        if (u32LoopTimer[0] != 0)
        {
            U32 u32Diff = MsOS_GetSystemTime() - u32LoopTimer[0];
            u32LoopTimer[0] = MsOS_GetSystemTime();
            if (u32Diff > u32TaskLoopMax[0])
            {
                u32TaskLoopMax[2] = u32TaskLoopMax[1];
                u32TaskLoopMax[1] = u32TaskLoopMax[0];
                u32TaskLoopMax[0] = u32Diff;
            }
            else if (u32Diff > u32TaskLoopMax[1])
            {
                u32TaskLoopMax[2] = u32TaskLoopMax[1];
                u32TaskLoopMax[1] = u32Diff;
            }
            else if (u32Diff > u32TaskLoopMax[2])
            {
                u32TaskLoopMax[2] = u32Diff;
            }

            u32TaskLoopCnt++;
            if ((MsOS_GetSystemTime() - u32LoopTimer[1]) >= 10000)
            {
                u32LoopTimer[1] = MsOS_GetSystemTime();
                MPLAYER_MSG_MUST("CLOOP[%08d]:[%08d][%08d][%08d]\n", 10000/u32TaskLoopCnt, u32TaskLoopMax[0], u32TaskLoopMax[1], u32TaskLoopMax[2]);
                u32TaskLoopCnt = 0;
            }
        }
        else
        {
            u32LoopTimer[0] = u32LoopTimer[1] = MsOS_GetSystemTime();
        }
    }

    msAPI_NPlayer_Polling();

    //movie process
    if (m_eStreamMode[E_MPLAYER_MEDIA_MOVIE] == MPLAYER_RTSP_MODE)
    {
        if ((m_eMplayerState[E_MPLAYER_MEDIA_MOVIE] == MPLAYER_STATE_PLAYING) && (m_bCheckScreen))
        {
            if (!MApi_XC_IsFreezeImg(MAIN_WINDOW) && (MApi_XC_IsBlackVideoEnable(MAIN_WINDOW) == FALSE))
            {
                m_bCheckScreen = FALSE;
                MPLAYER_MSG_INFO("Screen unmute0(%d)!\n", (U32)MsOS_GetSystemTime()-u32AudioMonitTimer);
            }
            if (MsOS_GetSystemTime()-u32AudioMonitTimer > 1000)
            {
                m_bCheckScreen = FALSE;
                MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);
                MApi_XC_GenerateBlackVideo( DISABLE, MAIN_WINDOW );
                MPLAYER_MSG_INFO("Screen unmute1(%d)!\n", (U32)MsOS_GetSystemTime()-u32AudioMonitTimer);
            }
        }
    }
    else
    {
        switch (m_eMplayerState[E_MPLAYER_MEDIA_MOVIE])
        {
            case MPLAYER_STATE_PRE_INIT:
                MPLAYER_MSG_INFO("MPLAYER_STATE_PRE_INIT(%d)\n", msAPI_Timer_GetTime0()-m_u32VdplayerInitStartTimer);
                m_u32VdplayerInitStartTimer = msAPI_Timer_GetTime0();
                m_eMplayerState[E_MPLAYER_MEDIA_MOVIE] = MPLAYER_STATE_INIT;
                if ((m_eStreamMode[E_MPLAYER_MEDIA_MOVIE]== MPLAYER_UNSEEKABLE_STREAM_MODE) || (m_eStreamMode[E_MPLAYER_MEDIA_MOVIE] == MPLAYER_SEEKABLE_STREAM_MODE))
                {
                    LongLong sFilelen;
                    U64 u64FileLength = 0;
                    msAPI_NPlayer_SendCmd(E_MPLAYER_MEDIA_MOVIE,MPLAYER_COMMAND_NOTIFY, MPLAYER_INSUFFICIENT_DATA);
                    u32Hdl_Video = msAPI_NPlayer_StreamOpen(NULL, OPEN_MODE_FOR_READ, E_DATA_STREAM_TYPE_VIDEO);
                    if (INVALID_DATA_STREAM_HDL != u32Hdl_Video)
                    {
                        sFilelen= msAPI_NPlayer_StreamLength(u32Hdl_Video);
                        if ((sFilelen.Hi == 0xFFFFFFFF) && (sFilelen.Lo == 0xFFFFFFFF))
                        {
                            MPLAYER_MSG_MUST("AP report file length: -1!\n");
                            m_bNotSupportStreamLen = TRUE;
                            MApp_VDPlayer_SetCfg(E_VDPLAYER_CFG_BM_STREAM_MODE, E_BM_STREAM_MODE_NETWORK_UNSEEKABLE);
                        }
                        u64FileLength = sFilelen.Lo + (((U64)sFilelen.Hi) << 32);
                    }
                    if (m_u32RingBufferNum[E_MPLAYER_MEDIA_MOVIE] > 1)
                    {
                        msAPI_NPlayer_StreamOpen(NULL, OPEN_MODE_FOR_READ, E_DATA_STREAM_TYPE_IN_SUB);
                    }
                    if ((u64FileLength == 0) ||
                        ((m_u32RingBufferNum[E_MPLAYER_MEDIA_MOVIE] > 1) && (m_StmHdl[E_DATA_STREAM_TYPE_IN_SUB] == INVALID_DATA_STREAM_HDL)))
                    {
                        msAPI_NPlayer_Stop(E_MPLAYER_MEDIA_MOVIE, MPLAYER_EXIT_ERROR_FILE);
                    }
                    MPLAYER_MSG_INFO("StreamOpen time(%d)\n", msAPI_Timer_GetTime0()-m_u32VdplayerInitStartTimer);
                    m_u32VdplayerInitStartTimer = msAPI_Timer_GetTime0();
                }
                break;

            case MPLAYER_STATE_INIT:
                if (msAPI_NPlayer_CheckBuffer(E_MPLAYER_MEDIA_MOVIE, TRUE) >= m_u32InitDataSize)
                {
                    MPLAYER_MSG_INFO("MPLAYER_STATE_INIT(%d)\n", msAPI_Timer_GetTime0()-m_u32VdplayerInitStartTimer);
                    msAPI_COPRO_Init(BIN_ID_CODE_VDPLAYER,((AEON_MEM_MEMORY_TYPE & MIU1) ? (AEON_MM_MEM_ADR | MIU_INTERVAL) : (AEON_MM_MEM_ADR)),AEON_MM_MEM_LEN);

                    param[0] = COMMAND_TO_NETAP;
                    param[1] = NETAP_COMMAND_MPLAYER_STATE;
                    param[2] = MPLAYER_STATE_INIT;
                    param[3] = E_MPLAYER_MEDIA_MOVIE;
                    msAPI_NPlayer_Query(m_u32PID[E_MPLAYER_MEDIA_MOVIE], 4, param);
                    MApp_MPlayer_SubtitleInit();
                    msAPI_NPlayer_ParseSubtitleFile();

                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    m_u32VdplayerInitStartTimer = msAPI_Timer_GetTime0();

                    if (m_bMovieThumbnail)
                    {
                        memset(&m_sCaptureRect, 0, sizeof(m_sCaptureRect));
                        MApp_VDPlayer_BeginThumbnail();
                    }

                    if (MApp_VDPlayer_Init(VIDEO_PLAYER_INPUT_SOURCE_MM, VIDEO_PLAYER_PLAYING_TYPE_INVALID, NULL))
                    {
                        MPLAYER_MSG_INFO("MApp_VDPlayer_Play_before(%d)\n", msAPI_Timer_GetTime0()-m_u32VdplayerInitStartTimer);

                        if (m_bMovieThumbnail)
                        {
                            if (!MApp_VDPlayer_MovieThumbnail_SetMVOP())
                            {
                                MPLAYER_MSG_INFO("MApp_VDPlayer_MovieThumbnail_SetMVOP fail\n");
                                msAPI_NPlayer_Stop(E_MPLAYER_MEDIA_MOVIE, MPLAYER_EXIT_ERROR_FILE);
                            }
                            else
                            {
                                m_eMplayerState[E_MPLAYER_MEDIA_MOVIE] = MPLAYER_STATE_PLAYING;
                            }
                            break;
                        }

                        if (MApp_VDPlayer_Play())
                        {
                            MPLAYER_MSG_INFO("MApp_VDPlayer_Play_end(%d)(%d)[0x%x]\n", msAPI_Timer_GetTime0()-m_u32VdplayerInitStartTimer, msAPI_Timer_GetTime0()-m_u32StartPlayTimer, m_u32ReadTotalSize);
                            u32AudioMonitTimer = MsOS_GetSystemTime();
                            param[0] = COMMAND_TO_NETAP;
                            param[1] = NETAP_COMMAND_MPLAYER_STATE;
                            param[2] = MPLAYER_STATE_PLAYING;
                            param[3] = E_MPLAYER_MEDIA_MOVIE;
                            msAPI_NPlayer_Query(m_u32PID[E_MPLAYER_MEDIA_MOVIE], 4, param);

                            if (m_bNotSupportStreamLen)
                            {
                                _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_MAX_FAST_BACKWARD_SPEED, 0);
                            }

                            m_eMplayerState[E_MPLAYER_MEDIA_MOVIE] = MPLAYER_STATE_PLAYING;
                            if ((m_u32StartGotoTime > 0) &&
                                (m_u32StartGotoTime < MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_TOTAL_TIME)) &&
                                (MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_MAX_FB_SPEED) != 0))
                            {
                                msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, 1000, MAIN_WINDOW);
                                MApp_VDPlayer_SetPlayPosition(m_u32StartGotoTime);
                            }
                            msAPI_NPlayer_SendCmd(E_MPLAYER_MEDIA_MOVIE, MPLAYER_COMMAND_NOTIFY, MPLAYER_START_PLAY);

                            if ((m_eStreamMode[E_MPLAYER_MEDIA_MOVIE] == MPLAYER_UNSEEKABLE_STREAM_MODE) || (m_eStreamMode[E_MPLAYER_MEDIA_MOVIE] == MPLAYER_SEEKABLE_STREAM_MODE))
                                MPLAYER_MSG_DBG("BF0:[%08X][%08d][%08d]\n", MApp_VDPlayer_Get_Buffer_Info(E_BUFFER_INFO_LEVEL), MApp_VDPlayer_Get_Buffer_Info(E_BUFFER_INFO_BITRATE), RingBufferIndex32(0, INDEX_STREAM_BITRATE));
                            else
                                MPLAYER_MSG_DBG("BF0:[%08X][%08d]\n", MApp_VDPlayer_Get_Buffer_Info(E_BUFFER_INFO_LEVEL), MApp_VDPlayer_Get_Buffer_Info(E_BUFFER_INFO_BITRATE));
                            if ((MApp_VDPlayer_Get_Buffer_Info(E_BUFFER_INFO_BITRATE) > 0) &&
                                ((m_eStreamMode[E_MPLAYER_MEDIA_MOVIE] == MPLAYER_UNSEEKABLE_STREAM_MODE) || (m_eStreamMode[E_MPLAYER_MEDIA_MOVIE] == MPLAYER_SEEKABLE_STREAM_MODE)))
                            {
                                m_s32DiffBitrate = MApp_VDPlayer_Get_Buffer_Info(E_BUFFER_INFO_BITRATE) - RingBufferIndex32(0, INDEX_STREAM_BITRATE);
                                m_s32MinBufferSize = (m_s32MinBufferSec*m_s32DiffBitrate*128);
                                m_s32MaxBufferSize = (m_s32MaxBufferSec*m_s32DiffBitrate*128);
                                if (m_s32DiffBitrate < 0)
                                    msAPI_NPlayer_SendCmd(E_MPLAYER_MEDIA_MOVIE, MPLAYER_COMMAND_NOTIFY, MPLAYER_SUFFICIENT_DATA);
                            }
                            else
                            {
                                m_s32DiffBitrate = 0;
                                m_s32MinBufferSize = m_s32MinBufferSec*0x20000;
                                m_s32MaxBufferSize = m_s32MaxBufferSec*0x20000;
                            }
                            _Mapp_VDPlayer_SetShareMemData(E_SHAREMEM_BUFFER_INFO+E_SHAREMEM_BUFFER_INFO_SIZE-1, 100);

                        #if SEAMLESS_PLAYING_ENABLE
                            if (MApp_VDPlayer_GetSeamlessMode() && (m_eTrickMode[E_MPLAYER_MEDIA_MOVIE] != MPLAYER_TRICK_NORMAL))
                            {
                                msAPI_NPlayer_SetTrickMode(E_MPLAYER_MEDIA_MOVIE, m_eTrickMode[E_MPLAYER_MEDIA_MOVIE]);
                            }
                        #endif

                            if (m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_INVALID)
                            {
                                MApp_MPlayer_CheckInternalSubtitleEnabledFirst();
                            }

                            m_bCheckMute = TRUE;
                            m_u32MuteTimer = (U32)MsOS_GetSystemTime() + 250;
                            break;
                        }
                        else if (m_u8ForceStop != 1)
                        {
                            msAPI_NPlayer_Stop(E_MPLAYER_MEDIA_MOVIE, (m_u8ForceStop ? MPLAYER_EXIT_FORCE : MPLAYER_EXIT_ERROR_FILE));
                        }
                    }
                    else if (m_u8ForceStop != 1)
                    {
                        msAPI_NPlayer_Stop(E_MPLAYER_MEDIA_MOVIE, (m_u8ForceStop ? MPLAYER_EXIT_FORCE : MPLAYER_EXIT_ERROR_FILE));
                    }
                }
                break;

            case MPLAYER_STATE_PLAYING:
                if (m_bMovieThumbnail)
                {
                    U32 u32dwin_addr=0 ;
                    U16 u16_width = (((MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_FRAMEINFO_WIDTH)+7)>>3)<<3);
                    U16 u16_height = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_FRAMEINFO_HEIGHT);

                    m_sCaptureRect.u16RectX = 0;
                    m_sCaptureRect.u16RectY = 0;
                    m_sCaptureRect.u16RectW =u16_width;
                    m_sCaptureRect.u16RectH =u16_height;

                    // Refine the start position of thumbnail.
                    MApp_VDPlayer_MovieThumbnail_DWINCapture(&u32dwin_addr);
                    m_sCaptureRect.u32BuffAddr= u32dwin_addr;
                    msAPI_NPlayer_Stop(E_MPLAYER_MEDIA_MOVIE, MPLAYER_NOTIFY_NULL);
                    msAPI_NPlayer_SendCmd(E_MPLAYER_MEDIA_MOVIE,MPLAYER_COMMAND_NOTIFY, MPLAYER_MOVIE_THUMBNAIL_DECODE_DONE);
                    break;
                }

                eRet = MApp_VDPlayer_Main();

                if (m_bCheckMute)
                {
                    if (MsOS_GetSystemTime() > m_u32MuteTimer)
                    {
                        m_bCheckMute = FALSE;
                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_MOMENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                    }
                }

                if ((m_eStreamMode[E_MPLAYER_MEDIA_MOVIE]== MPLAYER_UNSEEKABLE_STREAM_MODE) || (m_eStreamMode[E_MPLAYER_MEDIA_MOVIE] == MPLAYER_SEEKABLE_STREAM_MODE))
                {
                    if (m_bNotSupportStreamLen && ((RingBufferIndex32(u32Hdl_Video, INDEX_STREAM_FLAG) & STREAM_FLAG_EOF) == STREAM_FLAG_EOF))
                    {
                        static U32 u32preFrameCount = 0;
                        static U32 u32preReadEndTimer = 0xFFFFFFFF;
                        U32 u32CurFrameCount;
                        LongLong lSzie;
                        U64 u64SeekPos, u64FileLength;

                        //check whether the data in ringbuf is consumed
                        u64FileLength = RingBufferIndex64(u32Hdl_Video, INDEX_STREAM_LENGTH);
                        lSzie = msAPI_NPlayer_StreamTell(u32Hdl_Video);
                        u64SeekPos = ((U64)lSzie.Hi << 32) + lSzie.Lo;

                        if (u64SeekPos >= u64FileLength)
                        {
                            MPLAYER_MSG_MUST("Reach file end!!\n");

                            u32CurFrameCount = MApi_VDEC_GetFrameCnt(); //refine later. Need codec provide new sharemem info
                            MPLAYER_MSG_DBG("frame count:%d\n",u32CurFrameCount);

                            if(u32preReadEndTimer == 0xFFFFFFFF)
                            {
                                u32preReadEndTimer = msAPI_Timer_GetTime0();
                            }

                            if(u32CurFrameCount != u32preFrameCount)
                            {
                                u32preReadEndTimer = msAPI_Timer_GetTime0();
                                u32preFrameCount = u32CurFrameCount;
                            }
                            else if (u32CurFrameCount == u32preFrameCount && msAPI_Timer_DiffTimeFromNow(u32preReadEndTimer) >= 10000)
                            {
                                MPLAYER_MSG_MUST("--->stop\n");
                                msAPI_NPlayer_Stop(E_MPLAYER_MEDIA_MOVIE, MPLAYER_EXIT_OK);
                                u32preReadEndTimer = 0xFFFFFFFF;
                                return;
                            }
                        }
                    }
                }

                if (eRet == EXIT_VDPLAYER_WAIT)
                {
                    msAPI_NPlayer_Stop(E_MPLAYER_MEDIA_MOVIE, MPLAYER_EXIT_OK);
                }
                else if (eRet == EXIT_VDPLAYER_EXIT)
                {
                    msAPI_NPlayer_Stop(E_MPLAYER_MEDIA_MOVIE, MPLAYER_EXIT_ERROR_FILE);
                }
                else
                {
                    if (m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_INVALID)
                    {
                        MApp_MPlayer_CheckInternalSubtitleValid();
                    }

                    if (m_enRpeatABMode == REPEATAB_MODE_AB)
                    {
                        U32 u32CurTime = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CUR_TIME);
                        // if at the start A point, clear the subtitle queue
                        if (m_bNewRepeatABLoop && u32CurTime < m_u32MovieRepeatTime[0] + 200)
                        {
                            //MPLAYER_MSG_INFO("clear subtitle queue\n");
                            _msAPI_NPlayer_ReinitRepeatABSubtitle();
                            break;
                        }
                        if (u32CurTime > m_u32MovieRepeatTime[1] - 200)
                        {
                            m_bNewRepeatABLoop = TRUE;
                        }
                    }

                    MApp_MPlayer_ExternalAndInternalTextSubtitleDraw();
                    msAPI_NPlayer_CheckBuffer(E_MPLAYER_MEDIA_MOVIE, FALSE);
                }
                break;

            default:
                break;
        }
    }

    //music process
    {
        switch (m_eMplayerState[E_MPLAYER_MEDIA_MUSIC])
        {
            case MPLAYER_STATE_PRE_INIT:
                m_eMplayerState[E_MPLAYER_MEDIA_MUSIC] = MPLAYER_STATE_INIT;
                break;

            case MPLAYER_STATE_INIT:
                {
                    BOOLEAN bIsWMA = FALSE;
                    BOOLEAN bSupport = TRUE;
                    BOOLEAN bRet = FALSE;
                    U32 u32TotalTime = 0;

                    param[0] = COMMAND_TO_NETAP;
                    param[1] = NETAP_COMMAND_MPLAYER_STATE;
                    param[2] = MPLAYER_STATE_INIT;
                    param[3] = E_MPLAYER_MEDIA_MUSIC;
                    msAPI_NPlayer_Query(m_u32PID[E_MPLAYER_MEDIA_MUSIC], 4, param);

                    m_u32LyricSubtitleCurTime = -1;
                    m_u16CurLyricPos = -1;
                    m_u32PlayCheckTime = -1;
                    m_eMusicFlag = E_MPLAYER_MUSIC_FLG_NULL;
                    m_bIsLyricUnicode = FALSE;
                    m_u32PlayTime = -1;
                    memset((U8 *)_PA2VA(m_u32MusicShareMemAddr), 0, m_u32MusicShareMemLength);

                    //init audio
                   MApi_AUDIO_SetCommand(MSAPI_AUD_DVB2_DECCMD_STOP);
                   MApi_AUDIO_SetSystem(MSAPI_AUD_DVB2_NONE);
                   MApi_AUDIO_SetSystem(MSAPI_AUD_DVB2_MP3);

                    _geMPLAYER_MusicType = _msAPI_NPlayer_VerifyMusicType(NULL,_geMPLAYER_MusicType);

                    switch(_geMPLAYER_MusicType)
                    {
                        case MPLAYER_SUBTYPE_MP3:
                            _genMusicType = EN_MUSIC_MP3;
                            break;

                        case MPLAYER_SUBTYPE_AAC:
                            _genMusicType = EN_MUSIC_AAC;
                            break;

                        case MPLAYER_SUBTYPE_WAV:
                            _genMusicType = EN_MUSIC_WAV;
                            break;

                        case MPLAYER_SUBTYPE_PCM:
                            _genMusicType = EN_MUSIC_PCM;
                            break;

                        case MPLAYER_SUBTYPE_WMA:
                            bIsWMA = TRUE;
                            break;

                        default:
                            printf("not support music type.\n");
                            bSupport = FALSE;
                            break;
                    }

                    if(bSupport)
                    {
                        if(bIsWMA)
                        {
                            MApp_Wma_StopAfterFBBegin(TRUE);
                            eRet = MApp_WMA_Main();
                            if(EXIT_WMA_INIT== eRet)
                            {
                                bRet = TRUE;
                                u32TotalTime = MApp_WMA_GetTotalTime();
                            }
                        }
                        else
                        {
                            MApp_Music_StopAfterFBBegin(TRUE);
                            eRet = MApp_Music_Main(_genMusicType);
                            if(EXIT_MP3_INIT== eRet)
                            {
                                bRet = TRUE;
                                u32TotalTime = (U32)MApp_Music_GetTotalTime();
                            }
                        }

                        if(bRet)
                        {
                            m_eMusicFlag &= (EN_MPLAYER_MUSIC_FLAG)~E_MPLAYER_MUSIC_FLG_LYRIC_VALID;
                            if(_msAPI_NPlayer_Music_Lyric_Parser())
                            {
                                m_eMusicFlag |= (E_MPLAYER_MUSIC_FLG_LYRIC_VALID|E_MPLAYER_MUSIC_FLG_LYRIC_ENABLE);
                            }
                        }
                    }

                    if (bRet)
                    {
                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_TOTAL_TIME,(U8*)&u32TotalTime,sizeof(u32TotalTime));

                        param[0] = COMMAND_TO_NETAP;
                        param[1] = NETAP_COMMAND_MPLAYER_STATE;
                        param[2] = MPLAYER_STATE_PLAYING;
                        param[3] = E_MPLAYER_MEDIA_MUSIC;
                        msAPI_NPlayer_Query(m_u32PID[E_MPLAYER_MEDIA_MUSIC], 4, param);

                        m_eMplayerState[E_MPLAYER_MEDIA_MUSIC] = MPLAYER_STATE_PLAYING;
                        msAPI_NPlayer_SendCmd(E_MPLAYER_MEDIA_MUSIC, MPLAYER_COMMAND_NOTIFY, MPLAYER_START_PLAY);
                    }
                    else
                    {
                        msAPI_NPlayer_Stop(E_MPLAYER_MEDIA_MUSIC,MPLAYER_EXIT_ERROR_FILE);
                    }
                }
                break;

            case MPLAYER_STATE_PLAYING:
                {
                    BOOLEAN bStop = FALSE;
                    EN_MPLAYER_NOTIFY_TYPE eNotifyType = MPLAYER_NOTIFY_NULL;

                    if(_geMPLAYER_MusicType == MPLAYER_SUBTYPE_WMA)
                    {
                        eRet = MApp_WMA_Main();
                        switch(eRet)
                        {
                            case EXIT_WMA_WAIT:
                                // stop normally
                                m_u32PlayCheckTime = -1;
                                bStop = TRUE;
                                eNotifyType = MPLAYER_EXIT_OK;
                                break;

                            case EXIT_WMA_EXIT:
                                // stop abnormally
                                m_u32PlayCheckTime = -1;
                                bStop = TRUE;
                                eNotifyType = MPLAYER_EXIT_ERROR_FILE;
                                break;

                            default:
                                if(msAPI_Timer_DiffTimeFromNow(m_u32PlayCheckTime)>100)
                                {
                                    U32 u32CurTime;
                                    U8 *pu8Dst;
                                    Music_Lyric_Tag curLyricTag;

                                    if((m_eMusicFlag & E_MPLAYER_MUSIC_FLG_LYRIC_VALID) &&
                                        (m_eMusicFlag & E_MPLAYER_MUSIC_FLG_LYRIC_ENABLE))
                                    {
                                        u32CurTime = MApp_WMA_GetCurrentTimeMs();
                                        if(MApp_Music_GetLyricTag(&curLyricTag, u32CurTime))
                                        {
                                            if(curLyricTag.u32Time != m_u32LyricSubtitleCurTime)
                                            {
                                                pu8Dst = msAPI_Memory_Allocate(LYRIC_MAX_SIZE+2, BUF_ID_FILEBROWER);

                                                if(pu8Dst)
                                                {
                                                    _msAPI_NPlayer_GetLyric(curLyricTag.u16LyricPos, pu8Dst);
                                                    _msAPI_NPlayer_NotifyMusicLyric(TRUE, _VA2PA((U32)pu8Dst) , LYRIC_MAX_SIZE);
                                                    msAPI_Memory_Free(pu8Dst, BUF_ID_FILEBROWER);
                                                    pu8Dst = NULL;
                                                }
                                                else
                                                {
                                                    __ASSERT(0);
                                                }
                                                m_u16CurLyricPos = curLyricTag.u16LyricPos;
                                                m_u32LyricSubtitleCurTime = curLyricTag.u32Time;
                                            }
                                        }
                                    }
                                    // Music time tick
                                    u32CurTime = MApp_WMA_GetCurrentTimeMs();

                                    if ((m_u32PlayTime / 1000) != (u32CurTime / 1000))
                                    {
                                        // record current play time
                                        m_u32PlayTime = u32CurTime;

                                        // record current play time
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_CURRENT_TIME,(U8*)&u32CurTime,sizeof(u32CurTime));
                                    }

                                    m_u32PlayCheckTime = msAPI_Timer_GetTime0();
                                }
                                break;
                        }
                    }
                    else
                    {
                        eRet = MApp_Music_Main(_genMusicType);
                        switch(eRet)
                        {
                            case EXIT_MP3_WAIT:
                                // stop normally
                                m_u32PlayCheckTime = -1;
                                bStop = TRUE;
                                eNotifyType = MPLAYER_EXIT_OK;
                                break;

                            case EXIT_MP3_EXIT:
                                // stop abnormally
                                m_u32PlayCheckTime = -1;
                                bStop = TRUE;
                                eNotifyType = MPLAYER_EXIT_ERROR_FILE;
                                break;

                            default:
                                if(msAPI_Timer_DiffTimeFromNow(m_u32PlayCheckTime)>100)
                                {
                                    U32 u32CurTime;
                                    U8 *pu8Dst;
                                    Music_Lyric_Tag curLyricTag;

                                    if((m_eMusicFlag & E_MPLAYER_MUSIC_FLG_LYRIC_VALID) &&
                                        (m_eMusicFlag & E_MPLAYER_MUSIC_FLG_LYRIC_ENABLE))
                                    {
                                        u32CurTime = MApp_Music_GetCurrentTimeMs();
                                        if(MApp_Music_GetLyricTag(&curLyricTag, u32CurTime))
                                        {
                                            if(curLyricTag.u32Time != m_u32LyricSubtitleCurTime)
                                            {
                                                pu8Dst = msAPI_Memory_Allocate(LYRIC_MAX_SIZE+2, BUF_ID_FILEBROWER);

                                                if(pu8Dst)
                                                {
                                                    _msAPI_NPlayer_GetLyric(curLyricTag.u16LyricPos, pu8Dst);
                                                    _msAPI_NPlayer_NotifyMusicLyric(TRUE, _VA2PA((U32)pu8Dst) , LYRIC_MAX_SIZE);
                                                    msAPI_Memory_Free(pu8Dst, BUF_ID_FILEBROWER);
                                                    pu8Dst = NULL;
                                                }
                                                else
                                                {
                                                    __ASSERT(0);
                                                }
                                                m_u16CurLyricPos = curLyricTag.u16LyricPos;
                                                m_u32LyricSubtitleCurTime = curLyricTag.u32Time;
                                            }
                                        }
                                    }
                                    // Music time tick
                                    u32CurTime = MApp_Music_GetCurrentTimeMs();

                                    if ((m_u32PlayTime / 1000) != (u32CurTime / 1000))
                                    {
                                        // record current play time
                                        m_u32PlayTime = u32CurTime;
                                        // record current play time
                                        _msAPI_NPlayer_SetMusicShareMem(INDEX_MUSIC_SHAR_CURRENT_TIME,(U8*)&u32CurTime,sizeof(u32CurTime));
                                    }
                                    m_u32PlayCheckTime = msAPI_Timer_GetTime0();
                                }
                                break;
                        }
                    }
                    // stop when necessary
                    if (bStop == TRUE)
                    {
                        msAPI_NPlayer_Stop(E_MPLAYER_MEDIA_MUSIC,eNotifyType);
                    }
                }
                break;

            default:
                break;
        }
    }

    //photo process
    {
        switch (m_eMplayerState[E_MPLAYER_MEDIA_PHOTO])
        {
            case MPLAYER_STATE_PRE_INIT:
                {
                    if (m_eStreamMode[E_MPLAYER_MEDIA_PHOTO] == MPLAYER_SEEKABLE_STREAM_MODE ||
                        m_eStreamMode[E_MPLAYER_MEDIA_PHOTO] == MPLAYER_UNSEEKABLE_STREAM_MODE)
                    {
                        MApp_Photo_EnableStreamMode(TRUE);
                    }
                    else
                    {
                        MApp_Photo_EnableStreamMode(FALSE);
                    }

                    if (!MApp_Photo_DecodeFile_Init(NULL, m_bThumbnail))
                    {
                        // play failed, stop sub-module unconditionally to reset the change we have made
                        msAPI_NPlayer_Stop(E_MPLAYER_MEDIA_PHOTO,MPLAYER_EXIT_ERROR_FILE);
                    }
                    else
                    {
                        // record decoded photo info
                        _gu16Photo_Wdith[_gu8Photo_DecodeIdx]   = MApp_Photo_GetInfo(E_PHOTO_INFO_WIDTH);
                        _gu16Photo_Height[_gu8Photo_DecodeIdx]  = MApp_Photo_GetInfo(E_PHOTO_INFO_HEIGHT);
                        _gu32Photo_Size[_gu8Photo_DecodeIdx]    = MApp_Photo_GetInfo(E_PHOTO_INFO_FILE_SIZE);

                        param[0] = COMMAND_TO_NETAP;
                        param[1] = NETAP_COMMAND_MPLAYER_STATE;
                        param[2] = MPLAYER_STATE_INIT;
                        param[3] = E_MPLAYER_MEDIA_PHOTO;
                        msAPI_NPlayer_Query(m_u32PID[E_MPLAYER_MEDIA_PHOTO], 4, param);

                        if(!_gbPhotoOnlyDecode)
                        {
                            if (m_bFullScreen == FALSE)
                            {
                                // imply preview
                                MApp_Photo_Display_SetViewWin(
                                        g_sDispWindow.x,
                                        g_sDispWindow.y,
                                        g_sDispWindow.width,
                                        g_sDispWindow.height);
                            }
                            else
                            {
                                // if full screen and all slots are free, call MApp_Photo_InitFullScreenDisplay()
                                if (_msAPI_NPlayer_Photo_GetFreeSlot() == PHOTO_TOTAL_SLOT)
                                {
                                    MPLAYER_MSG_DBG("Init photo to full screen display\n");
                                    MApp_Photo_InitFullScreenDisplay();

                                    // send event
                                    msAPI_NPlayer_SendCmd(E_MPLAYER_MEDIA_PHOTO,MPLAYER_COMMAND_NOTIFY, MPLAYER_PHOTO_DECODING_NEXT);
                                }
                            }
                        }

                        // send event
                        param[0] = COMMAND_TO_NETAP;
                        param[1] = NETAP_COMMAND_MPLAYER_STATE;
                        param[2] = MPLAYER_STATE_PLAYING;
                        param[3] = E_MPLAYER_MEDIA_PHOTO;
                        msAPI_NPlayer_Query(m_u32PID[E_MPLAYER_MEDIA_PHOTO], 4, param);

                        _gePhoto_State[_gu8Photo_DecodeIdx] = E_PHOTO_SLOT_STATE_DECODING;
                        m_eMplayerState[E_MPLAYER_MEDIA_PHOTO] = MPLAYER_STATE_PLAYING;

                        msAPI_NPlayer_SendCmd(E_MPLAYER_MEDIA_PHOTO, MPLAYER_COMMAND_NOTIFY, MPLAYER_START_PLAY);
                    }
                }

                break;

            case MPLAYER_STATE_PLAYING:
                {
                    // photo playing
                    // note: photo decode process has to be in front of display process because decoded
                    // photo has to be displayed immediately if that is possible or the small time periord
                    // between current decode and next display of next loop may cause problem

                    // photo decode process
                    #define PHOTO_DBG 1
                    #if PHOTO_DBG
                        static U32 u32PhotoDisplayStartTime = 0;
                        static U32 u32PhotoDisplayTick = 0;
                    #endif

                    BOOLEAN bStop = FALSE;

                    {
                        // note: if next file is jpeg and there is photo displaying,
                        // decode can start only when current displaying photo times out
                        // TBD: this is JPEG pause decode
                        if ((MApp_Photo_GetInfo(E_PHOTO_INFO_FILE_FORMAT) == E_PHOTO_FILE_JPEG)
                                && (_gePhoto_State[_gu8Photo_DisplayIdx] == E_PHOTO_SLOT_STATE_DISPLAYING))
                        {
                            // do nothing
                        }
                        else
                        {
                            eRet = MApp_Photo_Main();
                            if (eRet == EXIT_PHOTO_DECODE_FAIL)
                            {
                                // decode failed
                                bStop = TRUE;

                                MPLAYER_MSG_DBG("DM: slot state changed for decode fail.\n");
                                MPLAYER_MSG_DBG("\tdecode,  idx: %d, state: %d - > %d\n",
                                        _gu8Photo_DecodeIdx, _gePhoto_State[_gu8Photo_DecodeIdx], E_PHOTO_SLOT_STATE_FREE);
                                MPLAYER_MSG_DBG("\tdisplay, idx: %d, state: %d\n\n",
                                        _gu8Photo_DisplayIdx, _gePhoto_State[_gu8Photo_DisplayIdx]);

                                // change photo state to free
                                _gePhoto_State[_gu8Photo_DecodeIdx] = E_PHOTO_SLOT_STATE_FREE;

                                // send event
                                msAPI_NPlayer_SendCmd(E_MPLAYER_MEDIA_PHOTO,MPLAYER_COMMAND_NOTIFY, MPLAYER_PHOTO_DECODE_FAILED);
                            }
                            else if (eRet == EXIT_PHOTO_DECODE_DONE)
                            {
                                // decode done
                                bStop = TRUE;

                                MPLAYER_MSG_DBG("DM: slot state changed for decode done.\n");
                                MPLAYER_MSG_DBG("\tdecode,  idx: %d -> %d, state: %d - > %d\n",
                                        _gu8Photo_DecodeIdx, PHOTO_NEXT_SLOT(_gu8Photo_DecodeIdx),
                                        _gePhoto_State[_gu8Photo_DecodeIdx], E_PHOTO_SLOT_STATE_DECODED);
                                MPLAYER_MSG_DBG("\tdisplay, idx: %d, state: %d\n\n",
                                        _gu8Photo_DisplayIdx, _gePhoto_State[_gu8Photo_DisplayIdx]);

                                if(_gbPhotoOnlyDecode)
                                {
                                    // change photo state to free for only request decode
                                    _gePhoto_State[_gu8Photo_DecodeIdx] = E_PHOTO_SLOT_STATE_FREE;
                                }
                                else
                                {
                                    // change photo state to decoded
                                    _gePhoto_State[_gu8Photo_DecodeIdx] = E_PHOTO_SLOT_STATE_DECODED;
                                    _gu8Photo_DecodeIdx = PHOTO_NEXT_SLOT(_gu8Photo_DecodeIdx);
                                }

                                // send event
                                msAPI_NPlayer_SendCmd(E_MPLAYER_MEDIA_PHOTO,MPLAYER_COMMAND_NOTIFY, MPLAYER_PHOTO_DECODE_DONE);
                            }
                        }

                        // stop when necessary
                        if (bStop == TRUE)
                        {
                            MApp_Photo_Stop();
                        }
                    }

                    // photo display process, 3 steps
                    // 1. check slide show pause state to decide next display action
                    if (_gePhoto_SlideShowPauseState == E_PHOTO_SLIDE_SHOW_PAUSED)
                    {
                        // slide show paused, don't examine step 2 & 3
                    }
                    else if (_gePhoto_SlideShowPauseState == E_PHOTO_SLIDE_SHOW_PAUSE_RELEASED)
                    {
                        _gePhoto_SlideShowPauseState = E_PHOTO_SLIDE_SHOW_FREE_RUN;

                        // slide show pause released, invalid current displayed photo immediately
                        if (_gePhoto_State[_gu8Photo_DisplayIdx] == E_PHOTO_SLOT_STATE_DISPLAYING)
                        {
                            if (_gePhoto_State[PHOTO_NEXT_SLOT(_gu8Photo_DisplayIdx)] == E_PHOTO_SLOT_STATE_DECODING)
                            {
                                // if next file is still decoding, send notificatino
                                msAPI_NPlayer_SendCmd(E_MPLAYER_MEDIA_PHOTO,MPLAYER_COMMAND_NOTIFY, MPLAYER_PHOTO_DECODING_NEXT);
                            }
                            else
                            {
                                goto invalid_current_displayed_photo;
                            }
                        }
                    }
                    else
                    {
                        // 2. if photo is displayed, check if slide show times out
                        if (_gePhoto_State[_gu8Photo_DisplayIdx] == E_PHOTO_SLOT_STATE_DISPLAYING)
                        {
                #if PHOTO_DBG
                            if ((msAPI_Timer_GetTime0() / 1000) != (u32PhotoDisplayStartTime / 1000))
                            {
                                MPLAYER_MSG_DBG("DM: Photo display tick(%d)\n", u32PhotoDisplayTick++);
                                u32PhotoDisplayStartTime = msAPI_Timer_GetTime0();
                            }
                #endif

                            if (msAPI_Timer_DiffTimeFromNow(m_u32PhotoPlayTime)
                                    >= (U32)_gu16Photo_SlideShowTimeOutInSec * 1000)
                            {
                invalid_current_displayed_photo:
                                switch (_gePhoto_State[PHOTO_NEXT_SLOT(_gu8Photo_DisplayIdx)])
                                {
                                    case E_PHOTO_SLOT_STATE_FREE:
                                    case E_PHOTO_SLOT_STATE_DECODED:
                                        MPLAYER_MSG_DBG("DM: slot state changed for display time out.\n");
                                        MPLAYER_MSG_DBG("\tdecode,  idx: %d, state: %d\n",
                                                _gu8Photo_DecodeIdx, _gePhoto_State[_gu8Photo_DecodeIdx]);
                                        MPLAYER_MSG_DBG("\tdisplay, idx: %d -> %d, state: %d -> %d\n\n",
                                                _gu8Photo_DisplayIdx, PHOTO_NEXT_SLOT(_gu8Photo_DisplayIdx),
                                                _gePhoto_State[_gu8Photo_DisplayIdx], E_PHOTO_SLOT_STATE_FREE);
                                        // change photo state to free
                                        _gePhoto_State[_gu8Photo_DisplayIdx] = E_PHOTO_SLOT_STATE_FREE;
                                        _gu8Photo_DisplayIdx = PHOTO_NEXT_SLOT(_gu8Photo_DisplayIdx);
                                        break;

                                    case E_PHOTO_SLOT_STATE_DECODING:
                                        // TBD: this is JPEG pause decode
                                        if (MApp_Photo_GetInfo(E_PHOTO_INFO_FILE_FORMAT) == E_PHOTO_FILE_JPEG)
                                        {
                                            MPLAYER_MSG_DBG("DM: slot state changed for display time out & next is jpeg.\n");
                                            MPLAYER_MSG_DBG("\tdecode,  idx: %d, state: %d\n",
                                                    _gu8Photo_DecodeIdx, _gePhoto_State[_gu8Photo_DecodeIdx]);
                                            MPLAYER_MSG_DBG("\tdisplay, idx: %d -> %d, state: %d -> %d\n\n",
                                                    _gu8Photo_DisplayIdx, PHOTO_NEXT_SLOT(_gu8Photo_DisplayIdx),
                                                    _gePhoto_State[_gu8Photo_DisplayIdx], E_PHOTO_SLOT_STATE_FREE);

                                            // change photo state to free
                                            _gePhoto_State[_gu8Photo_DisplayIdx] = E_PHOTO_SLOT_STATE_FREE;
                                            _gu8Photo_DisplayIdx = PHOTO_NEXT_SLOT(_gu8Photo_DisplayIdx);
                                        }
                                        break;

                                    default:
                                        break;

                                }
                            }
                        }

                        // 3. if no photo is displayed and one is ready, display it
                        if (_gePhoto_State[_gu8Photo_DisplayIdx] == E_PHOTO_SLOT_STATE_DECODED)
                        {
                            // reset photo relative variables
                            m_ViewInfo[E_MPLAYER_MEDIA_PHOTO].s16ShiftX = 0;
                            m_ViewInfo[E_MPLAYER_MEDIA_PHOTO].s16ShiftY = 0;
                            m_ViewInfo[E_MPLAYER_MEDIA_PHOTO].eZoom = E_ZOOM_1;
                            m_ViewInfo[E_MPLAYER_MEDIA_PHOTO].eRotation = E_ROTATION_0;

                            // change photo state to displaying
                            _gePhoto_State[_gu8Photo_DisplayIdx] = E_PHOTO_SLOT_STATE_DISPLAYING;

                            // display photo
                            MApp_Photo_Display(!m_bFullScreen);

                            // record start time of current photo displaying
                            m_u32PhotoPlayTime = msAPI_Timer_GetTime0();

                            MPLAYER_MSG_DBG("DM: slot state changed for displaying.\n");
                            MPLAYER_MSG_DBG("\tdecode,  idx: %d, state: %d\n",
                                    _gu8Photo_DecodeIdx, _gePhoto_State[_gu8Photo_DecodeIdx]);
                            MPLAYER_MSG_DBG("\tdisplay, idx: %d, state: %d -> %d\n\n",
                                    _gu8Photo_DisplayIdx, E_PHOTO_SLOT_STATE_DECODED, E_PHOTO_SLOT_STATE_DISPLAYING);
            #if PHOTO_DBG
                            u32PhotoDisplayStartTime = m_u32PhotoPlayTime;
                            u32PhotoDisplayTick = 0;
            #endif
                            // send event
                            msAPI_NPlayer_SendCmd(E_MPLAYER_MEDIA_PHOTO,MPLAYER_COMMAND_NOTIFY, MPLAYER_PHOTO_DISPLAYED);
                        }
                    }
                }
                break;

            default:
                break;
        }
    }
}

//-----------------------------------------------------------------------------
U8 msAPI_NPlayer_KeyHandle(U8 u8keyData)
{
    if (m_bNplayerRun)
    {
        switch (u8keyData)
        {
            case KEY_EXIT:
                if (msAPI_NPlayer_IsPlaying(E_MPLAYER_MEDIA_MOVIE) ||
                    msAPI_NPlayer_IsPlaying(E_MPLAYER_MEDIA_MUSIC) ||
                    msAPI_NPlayer_IsPlaying(E_MPLAYER_MEDIA_PHOTO))
                {
                    if (m_u8TransmitKey&E_TRANSMIT_KEY_EXIT)
                    {
                        msAPI_APEngine_TransmitKey(KEY_EXIT);
                    }
                    else
                    {
                        if (msAPI_NPlayer_IsPlaying(E_MPLAYER_MEDIA_MOVIE))
                            msAPI_NPlayer_Stop(E_MPLAYER_MEDIA_MOVIE, MPLAYER_EXIT_FORCE);
                        if (msAPI_NPlayer_IsPlaying(E_MPLAYER_MEDIA_MUSIC))
                            msAPI_NPlayer_Stop(E_MPLAYER_MEDIA_MUSIC, MPLAYER_EXIT_FORCE);
                        if (msAPI_NPlayer_IsPlaying(E_MPLAYER_MEDIA_PHOTO))
                            msAPI_NPlayer_Stop(E_MPLAYER_MEDIA_PHOTO, MPLAYER_EXIT_FORCE);
                    }
                }
                else
                {
                    msAPI_APEngine_TransmitKey(KEY_EXIT);
                }
                u8keyData = KEY_NULL;
                break;

            case KEY_VOLUME_PLUS:
                if (m_u8TransmitKey&E_TRANSMIT_KEY_VOLUME_PLUS)
                {
                    msAPI_APEngine_TransmitKey(u8keyData);
                    u8keyData = KEY_NULL;
                }
                break;

            case KEY_VOLUME_MINUS:
                if (m_u8TransmitKey&E_TRANSMIT_KEY_VOLUME_MINUS)
                {
                    msAPI_APEngine_TransmitKey(u8keyData);
                    u8keyData = KEY_NULL;
                }
                break;

            case KEY_MUTE:
                if (m_u8TransmitKey&E_TRANSMIT_KEY_MUTE)
                {
                    msAPI_APEngine_TransmitKey(u8keyData);
                    u8keyData = KEY_NULL;
                }
                break;

            default:
                break;
        }
    }

    return u8keyData;
}

//-----------------------------------------------------------------------------
void msAPI_NPlayer_IPCInit(void)
{
    U8 i;
    MPLAYER_MSG_MUST("msAPI_NPlayer_IPCInit(%s)\n", IPC_VERSION);

    m_bInSend = FALSE;
    m_bNplayerRun = FALSE;
    m_eDebugLevle = MPLAYER_DBG_LEVEL_INFO;
    m_u32NplayerCnt = 0;

    for (i = E_MPLAYER_MEDIA_MIN; i < E_MPLAYER_MEDIA_NUM; i++)
    {
        m_u32PID[i] = 0xFFFFFFFF;
        m_bNplayerPlay[i] = FALSE;
        m_eStreamMode[i] = MPLAYER_FILE_MODE;
    }

    if (m_bInit == FALSE)
    {
        key_t key;
        key = ftok(IPC_PATH, 0);
        MPLAYER_MSG_INFO("key[%x]\n", key);
        shmid = shmget(key, (MSG_BUFFER_TOTAL_SIZE+SHARE_MEM_TOTAL_SIZE), IPC_CREAT|0666);
        MPLAYER_MSG_INFO("shmid[%d]\n", shmid);
        if (-1 == shmid)
        {
            MPLAYER_MSG_ERR("create shared memory error\n");
            return;
        }
        m_pMsgAddr = (U8 *)shmat(shmid, 0, 0);
        MPLAYER_MSG_INFO("shm[%x]\n", (U32)m_pMsgAddr);
        if (-1 == (S32)m_pMsgAddr)
        {
            MPLAYER_MSG_ERR("attach shared memory error\n");
            return;
        }
        memset(m_pMsgAddr, 0x00, (MSG_BUFFER_TOTAL_SIZE+SHARE_MEM_TOTAL_SIZE));
        m_pShmAddr = m_pMsgAddr+MSG_BUFFER_TOTAL_SIZE;

        semid = semget(key, 2, IPC_CREAT|0666);
        MPLAYER_MSG_INFO("semid[%d]\n", semid);
        if (-1 == semid)
        {
            MPLAYER_MSG_ERR("create semaphore error\n");
            return;
        }
        union semun sem;
        sem.val = 1;
        semctl(semid, 0, SETVAL, sem);
        semctl(semid, 1, SETVAL, sem);

        m_bInit = TRUE;
    }
}

void msAPI_NPlayer_Polling(void)
{
    if (m_bInit == TRUE)
    {
        if ((m_bInSend == FALSE) && (MsgiBufferIndex8(MSG_SEND_HANDLE,0) != 0))
        {
            m_bInSend = TRUE;
            U32  u32RetData = msAPI_NPlayer_Callback(MsgiBufferAddress8(MSG_SEND_HANDLE,1));
            MsgiBufferIndex8(MSG_RETURN_HANDLE,0) = (u32RetData & 0xff);
            MsgiBufferIndex8(MSG_RETURN_HANDLE,1) = ((u32RetData >> 8) & 0xff);
            MsgiBufferIndex8(MSG_RETURN_HANDLE,2) = ((u32RetData >> 16) & 0xff);
            MsgiBufferIndex8(MSG_RETURN_HANDLE,3) = ((u32RetData >> 24) & 0xff);

            MPLAYER_MSG_FW("msAPI_NPlayer_Polling(%x, %x)\n", MsgiBufferIndex8(MSG_SEND_HANDLE,0), u32RetData);
            memset(MsgiBufferAddress8(MSG_SEND_HANDLE,1), 0x00, MSG_BUFFER_SIZE-1);
            MsgiBufferIndex8(MSG_SEND_HANDLE,0) = 0;
            m_bInSend = FALSE;
        }
    }
}

#endif
#undef MSAPI_NPLAYER_C

