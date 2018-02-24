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
///////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2010 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef _MAPP_DIGITAL_MEDIA_H_
#define _MAPP_DIGITAL_MEDIA_H_

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

///////////////////////////////////////////////////////////////////////////////
/*! \file mapp_digitalmedia.h
    \brief APIs for playing digital media.
    \author MStar Semiconductor Inc.

    \details This file contains the interface for digital media module.
    This module request the caller to provide streaming I/O callback
    functions before requesting any playback command. \n\n
    There is a simple idea about the sequence of  streaming I/O callback
    functions and playback commands.\n
    \note All streaming I/O callback is provided by caller and called by
    digital media module.

    - \e Step 1, Init, caller --> digital media module.\n
    \note Caller has to specify the streaming I/O callback functions while
    initialization.
    - \e Step 2, Play, caller --> digital media module.\n
    \note Before playback command returns, streaming I/O callback functions
    will be used for getting the total size in bytes of data stream, reading
    amount of data and \b maybe seek to a specific position of the data stream.
    - \e Step 3, Playback, caller --> digital media module.\n
    \note As specified in \e Step 2, streaming I/O callback functions may be
    used for seeking to specific position and reading amount of data.
    - \e Step 4, Stop, caller --> digital media module.\n
    \note Stop data stream playback. */
///////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// Include Files
//------------------------------------------------------------------------------
#include "MsCommon.h"

#include "msAPI_FSCommon.h" // for LongLong

//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
#undef INTERFACE
#ifdef _MAPP_DIGITAL_MEDIA_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif // #ifdef _MAPP_DIGITAL_MEDIA_C_

/*! \brief The default photo slideshow time out value in second. */
#define DM_PHOTO_SLIDESHOW_TIMEOUT  (5)
/*! \brief The value used to identify an invalid data stream handle. */
#define INVALID_DM_STRM_HDL         (0xffffffff)

/*!  \cond */
// the assumed preview window settings are based on ASSUMED_PANEL_WIDTH x ASSUMED_PANEL_HEIGHT panel
// and user shouldn't use these assumed values at all time
#define ASSUMED_PANEL_WIDTH                 1366
#define ASSUMED_PANEL_HEIGHT                 768

#define ASSUMED_PREVIEW_WND_X                780
#define ASSUMED_PREVIEW_WND_Y                150
#define ASSUMED_PREVIEW_WND_WIDTH            548
#define ASSUMED_PREVIEW_WND_HEIGHT           290
/*!  \endcond */

/*! \brief The x-coordinate of default preview window */
#define DEFAULT_PREVIEW_WND_X               ((ASSUMED_PREVIEW_WND_X * PANEL_WIDTH) / ASSUMED_PANEL_WIDTH)
/*! \brief The y-coordinate of default preview window */
#define DEFAULT_PREVIEW_WND_Y               ((ASSUMED_PREVIEW_WND_Y * PANEL_HEIGHT) / ASSUMED_PANEL_HEIGHT)
/*! \brief The width of default preview window */
#define DEFAULT_PREVIEW_WND_WIDTH           ((ASSUMED_PREVIEW_WND_WIDTH * PANEL_WIDTH) / ASSUMED_PANEL_WIDTH)
/*! \brief The height of default preview window. */
#define DEFAULT_PREVIEW_WND_HEIGHT          ((ASSUMED_PREVIEW_WND_HEIGHT * PANEL_HEIGHT) / ASSUMED_PANEL_HEIGHT)

//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Type and Structure Declaration
//------------------------------------------------------------------------------
/*! \brief The ID of stream handle used to identify a data stream.
    \details When playing a digital media instance, 1 or more data streams
    are needed. For example, when playing a movie, the stream handle specified
    by \e E_DM_STRM_HDL_VIDEO is the one and the only one handle that can't be
    NULL. If upper layer wishes to decode/display internal subtitle, one more
    stream handle has to be specified by \e E_DM_STRM_HDL_IN_SUB. One can think
    of that to be 2 file descriptors opened upon same file on Linux system.
    For more details about the usage of this enumeration type, please refer to
    \e MApp_DigitalMedia_Init(). */
typedef enum
{
    E_DM_STRM_HDL_MIN,  /*!< brief The minimum ID number of stream handle. */

    E_DM_STRM_HDL_0         = E_DM_STRM_HDL_MIN,
    E_DM_STRM_HDL_1,
    E_DM_STRM_HDL_2,
    E_DM_STRM_HDL_3,
    E_DM_STRM_HDL_4,

    E_DM_STRM_HDL_MAX,  /*!< brief The maximum ID number of stream handle. */

    // for movie
    E_DM_STRM_HDL_VIDEO     = E_DM_STRM_HDL_0,  /*!< \brief The ID of the main stream for movie playback. */
    E_DM_STRM_HDL_AUDIO     = E_DM_STRM_HDL_1,  /*!< \brief The ID of the audio stream for movie playback. If the handle
                                                     specified by this ID is not \e INVALID_DM_STRM_HDL, audio data will
                                                     be extracted from the date stream specified by this ID. */
    E_DM_STRM_HDL_IN_SUB    = E_DM_STRM_HDL_2,  /*!< \brief The ID of internal subtitle for movie playback. If the handle
                                                     specified by this ID is not \e INVALID_DM_STRM_HDL, internal subtitle
                                                     data will be extracted from the data stream specified by this ID.
                                                     Or if \e INVALID_DM_STRM_HDL is specified, no internal subtitle data
                                                     will be decoded/displayed. */
    E_DM_STRM_HDL_EX_SUB_0  = E_DM_STRM_HDL_3, // external subtitle 0
    E_DM_STRM_HDL_EX_SUB_1  = E_DM_STRM_HDL_4, // external subtitle 1

    // for photo
    E_DM_STRM_HDL_PHOTO     = E_DM_STRM_HDL_0,  /*!< \brief The ID of the main stream for photo playback. */

    // for music (if BGM is enabled, music has to use a stream other than photo)
    E_DM_STRM_HDL_MUSIC     = E_DM_STRM_HDL_1,  /*!< \brief The ID of the main stream for music playback. */
    E_DM_STRM_HDL_MUSIC2    = E_DM_STRM_HDL_2,  /*!< \brief The ID of the main stream for music playback,for M4A AAC case,it need. */
    E_DM_STRM_HDL_LYRIC     = E_DM_STRM_HDL_3,  /*!< \brief The ID of the lyric stream for the music playback. */
} E_DM_STRM_HDL;

/*! \brief The handle(s) specified in \e MApp_DigitalMedia_Init() and used with
    streaming I/O callback functions for upper layer to identify which data
    stream the I/O is operating upon. Please note that <b> digital media module
    won't use data stream handles for any other operations except streaming
    I/O and the value won't be referred/modified. </b> */
typedef U32 DM_STRM_HDL;

/*! \brief Types of digital media data. */
typedef enum
{
    E_DM_STRM_TYPE_MIN      = 0,
    E_DM_STRM_TYPE_MOVIE    = E_DM_STRM_TYPE_MIN,   /*!< Movie. */
    E_DM_STRM_TYPE_PHOTO,                           /*!< Photo. */
    E_DM_STRM_TYPE_MUSIC,                           /*!< Music. */
    E_DM_STRM_TYPE_NUM,
} E_DM_STRM_TYPE;

/*! \brief Types fo error that a streaming I/O callback function will have. */
typedef enum
{
    E_DM_STRM_IO_NO_ERROR,  /*!< I/O operation has completed successfully. */
    E_DM_STRM_IO_WAIT,      /*!< I/O operation needs more time than expected. */
} E_DM_STRM_IO_ERR;

/*! \brief Events that will be generated by digital media moudle.
    \details After \e MApp_DigitalMedia_Play() has returned, digital media module
    starts to play media instance. Some events will be automatically generated
    and reported to upper layer via \e pfnNotify() if it was registered. For
    example, if the playback stopped normally or abnormally. */
typedef enum
{
    E_DM_EVENT_NONE                 = 0,

    E_DM_EVENT_PLAYING_TIME_TICK    = BIT0, /*!< \brief The time tick in second. */
    E_DM_EVENT_INFO_OK              = BIT1, /*!< \brief The information about the media instance is ready for upper layer. */

    E_DM_EVENT_STOP_NORMALLY        = BIT2, /*!< \brief The playing of the media instance was stopped normally. */
    E_DM_EVENT_STOP_ABNORMALLY      = BIT3, /*!< \brief The playing of the media instance was stopped abnormally. */

    E_DM_EVENT_SHOW_LYRIC           = BIT4, /*!< \brief It's time for upper layer to retrive and show music lyric. */
    E_DM_EVENT_HIDE_LYRIC           = BIT5, /*!< \brief It's time for upper layer to remove last shown lyric from screen. */

    E_DM_EVENT_SHOW_MOVIE_SUBTITLE  = BIT6, /*!< \brief It's time for upper layer to retrive and show movie subtitle. */
    E_DM_EVENT_HIDE_MOVIE_SUBTITLE  = BIT7, /*!< \brief It's time for upper layer to remove last shown movie subtitle from screen. */

    E_DM_EVENT_BUFFER_EMPTY         = BIT8, /*!< \brief It's time for upper layer to fill double buffer */


    E_DM_EVENT_PHOTO_DECODE_DONE    = BIT9,     /*!< \brief The photo decode process has finished successfully. */
    E_DM_EVENT_PHOTO_DECODE_FAILED  = BIT10,    /*!< \brief The photo decode process is failed. */

    E_DM_EVENT_PHOTO_DECODING_NEXT  = BIT11,    /*!< \brief Next file is decoding and no decoded photo is ready for display. */
    E_DM_EVENT_PHOTO_DISPLAYED      = BIT12,    /*!< \brief One decoded photo is now displayed. */

    // more ...

    E_DM_EVENT_MAX,
    E_DM_EVENT_ALL = 0xFFFFFFFF,
} E_DM_EVENT;

/*! \brief Types of external subtitle for movie playback. */
typedef enum
{
    E_DM_SUBTITLE_SRT,
    E_DM_SUBTITLE_SUBIDX,
    E_DM_SUBTITLE_SSA,
    E_DM_SUBTITLE_ASS,
    E_DM_SUBTITLE_SMI,
    E_DM_SUBTITLE_SUB,
    E_DM_SUBTITLE_SUBVIEWER,
    E_DM_SUBTITLE_MICRODVD,
    E_DM_SUBTITLE_DVDSUBTITLESYSTEM,
    E_DM_SUBTITLE_NUM,
    E_DM_SUBTITLE_INVALID,
} E_DM_SUBTITLE_TYPE;

/*! \brief Types of music type. */
typedef enum
{
    E_DM_MUSIC_NONE                 = 0,

    E_DM_MUSIC_MP3,
    E_DM_MUSIC_AAC,
    E_DM_MUSIC_WAV,
    E_DM_MUSIC_WMA,
    //more ...

    E_DM_MUSIC_MAX,
} E_DM_MUSIC_TYPE;

/*! \details \b Description: The prototype of notification callback.

    \param <IN>     \b eType: Type of media instance.
    \param <IN>     \b eEvent: Type of event.
    \param <IN>     \b u32Info: The info of \e eEvent.
    \param <IN>     \b u16Len: The length of \e u32Info.

    \return None */
typedef void (*pfnNotificaton)(E_DM_STRM_TYPE eType, E_DM_EVENT eEvent, U32 u32Info, U16 u16Len);

//------------------------------------------------------------------------------
/*! \brief The streaming I/O callback functions.
    \details To isolate data streaming from codec, digital media module requires
    upper layer to provide streaming I/O callback functions when calling
    \e MApp_DigitalMedia_Init(). \e DM_STRM_IO is the structure that contains
    these callbacks. Some of them are requirement and some are optional. If upper
    layer has no interest in the events or queries from digital media module,
    it should set NULL to the callback function entry. */
typedef struct
{
    BOOLEAN     (*pfnClose) (DM_STRM_HDL dmStrmHdl);    /*!< \brief A \b requied callback function. Used by digital media
                                                             module to close the data stream specified by \e dmStrmHdl. */
    U32         (*pfnRead)  (DM_STRM_HDL dmStrmHdl, void *pBuff, U32 u32Size, E_DM_STRM_IO_ERR *peIoErr);
                                                        /*!< \brief A \b requied callback function. Digital media module
                                                             use this callback to request more data from the stream
                                                             specified by \e dmStrmHdl. <b>Please note that the return
                                                             value of this callback function is the requested data minus
                                                             data put to \e pBuff. Also note that \e pBuff stands for the
                                                             physical address for read data. </b> */
    BOOLEAN     (*pfnSeek)  (DM_STRM_HDL dmStrmHdl, LongLong u64Pos, E_DM_STRM_IO_ERR *peIoErr);
                                                        /*!< \brief A \b requied callback function. Digital media module
                                                             use this callback to seek to dedicated position of the data
                                                             stream. specified by \e dmStrmHdl. If the media instance is
                                                             not seekable, please bitwise OR the attribute
                                                             '\e E_DM_STRM_ATTR_SEEKABLE' when calling
                                                             \e MApp_DigitalMedia_Init(). <b>Please note that even
                                                             '\e E_DM_STRM_ATTR_SEEKABLE' is indicated, this callback
                                                             function is still required. </b> */
    LongLong    (*pfnTell)  (DM_STRM_HDL dmStrmHdl);    /*!< \brief A \b requied callback function. Used by digital media
                                                             module to query current position of the data stream specified
                                                             by \e dmStrmHdl. */
    LongLong    (*pfnLength)    (DM_STRM_HDL dmStrmHdl);
                                                        /*!< \brief A \b requied callback function. Used by digital media
                                                             module to query total size of the data stream specified by
                                                             \e dmStrmHdl. */
    BOOLEAN     (*pfnIsClosed)  (DM_STRM_HDL dmStrmHdl);
                                                        /*!< \brief A \b optional callback function. Sometimes, the data
                                                             stream is closed by upper layer before \e MApp_DigitalMedia_Stop()
                                                             is called. For an example, network connection has broken. This
                                                             callback function is used by digital media module to check if
                                                             the data stream specified by \e dmStrmHdl has been closed. */
    BOOLEAN     (*pfnIsStopAsked)   (void);             /*!< \brief A \b optional callback function. Depends on the content
                                                             of media instance, sometimes it takes a long time to parse
                                                             relative information of that instance. This parsing process
                                                             happens when \e MApp_DigitalMedia_Init() is called. There is
                                                             no way for upper layer to stop this procedure before
                                                             \e MApp_DigitalMedia_Init() returns. This callback function
                                                             provide an alternate way for digital media module to query if
                                                             upper layer wishes to stop the parsing procedure. */
    pfnNotificaton pfnNotify;                           /*!< \brief A \b optional callback function. Used by digital media
                                                             module to notify upper layer that something has happened. */
} DM_STRM_IO;

/*! \brief Attributes of data stream(s). */
typedef enum
{
    E_DM_STRM_ATTR_NONE         = 0,

    E_DM_STRM_ATTR_SEEKABLE     = BIT0, /*!< \brief If data stream(s) is seekable or not. For some applications,
                                             data stream is seekable, e.g. most files. But others aren't, e.g.
                                             network live streams. */

    E_DM_STRM_ATTR_THUMBNAIL    = BIT1, /*!< \brief If uppder layer wishes to decode thumbnail from the data
                                             stream, this flag has to be set. It applies to
                                             \e E_DM_STRM_TYPE_PHOTO.*/

    E_DM_STRM_ATTR_VIDEO_ONLY    = BIT2, /*!< \brief enable video only, disable audio. For KTV mode design.*/
} E_DM_STRM_ATTRIB;

/*! \brief Speeds of playback. Apply to \e E_DM_STRM_TYPE_MOVIE and \e E_DM_STRM_TYPE_MUSIC. */
typedef enum
{
    E_DM_SPEED_X1,
    E_DM_SPEED_X2,
    E_DM_SPEED_X4,
    E_DM_SPEED_X8,
    E_DM_SPEED_X16,
    E_DM_SPEED_X32,

    E_DM_SPEED_MAX,
} E_DM_SPEED;

/*! \brief Modes of playback. */
typedef enum
{
    E_DM_PLAY_MODE_NORMAL,          /*!< \brief Apply to all media types. */
    E_DM_PLAY_MODE_PAUSE,           /*!< \brief Apply to all media types. */
    E_DM_PLAY_MODE_SLOW_FORWARD,    /*!< \brief Apply to \e E_DM_STRM_TYPE_MOVIE. */
    E_DM_PLAY_MODE_FAST_FORWARD,    /*!< \brief Apply to \e E_DM_STRM_TYPE_MOVIE and \e E_DM_STRM_TYPE_MUSIC. */
    E_DM_PLAY_MODE_FAST_BACKWORD,   /*!< \brief Apply to \e E_DM_STRM_TYPE_MOVIE and \e E_DM_STRM_TYPE_MUSIC. */

    E_DM_PLAY_MODE_MAX,
} E_DM_PLAY_MODE;

/*! \brief The view window. */
/*! \details Because of some underlying limitation (currently, FBL or Frame BufferLess),
    there are only 2 options for the size of view window. \n
    - 1. Full screen. \n
    (\e u16X == 0) && (\e u16Y == 0) && \n
    (\e u16Width == \e PANEL_WIDTH) && (\e u16Height == \e PANEL_HEIGHT) \n
    - 2. Preview. \n
    (\e u16Width <= \e DEFAULT_PREVIEW_WND_WIDTH) && (\e u16Height <= \e DEFAULT_PREVIEW_WND_HEIGHT) && \n
    (\e u16X + \e u16Width <= \e PANEL_WIDTH) && (\e u16Y + \e u16Height <= \e PANEL_HEIGHT) \n  */
typedef struct
{
    U16 u16X;
    U16 u16Y;
    U16 u16Width;
    U16 u16Height;
} ST_DM_RECT;

/*! \brief Rotation angle. Apply to \e E_DM_STRM_TYPE_PHOTO. */
typedef enum
{
    E_DM_ROTATION_0,
    E_DM_ROTATION_90,
    E_DM_ROTATION_180,
    E_DM_ROTATION_270,

    E_DM_ROTATION_MAX,
} E_DM_ROTATION;

/*! \brief Zooming factor. Apply to \e E_DM_STRM_TYPE_MOVIE and \e E_DM_STRM_TYPE_PHOTO. */
typedef enum
{
    E_DM_ZOOM_1_DIV_8,  /*!< Zoom in, X(1/8). */
    E_DM_ZOOM_1_DIV_4,  /*!< Zoom in, X(1/4). */
    E_DM_ZOOM_1_DIV_2,  /*!< Zoom in, X(1/2). */
    E_DM_ZOOM_1,        /*!< Normal, X1. */
    E_DM_ZOOM_2,        /*!< Zoom out, X2. */
    E_DM_ZOOM_4,        /*!< Zoom out, X4. */
    E_DM_ZOOM_8,        /*!< Zoom out, X8. */

    E_DM_ZOOM_MAX,
} E_DM_ZOOM;

/*! \brief Moving direction. Apply to \e E_DM_STRM_TYPE_MOVIE and \e E_DM_STRM_TYPE_PHOTO. */
typedef enum
{
    E_DM_DIRECTION_UP,
    E_DM_DIRECTION_DOWN,
    E_DM_DIRECTION_LEFT,
    E_DM_DIRECTION_RIGHT,

    E_DM_DIRECTION_MAX,
} E_DM_DIRECTION;

/*! \brief Repeating marker. Apply to \e E_DM_STRM_TYPE_MOVIE. Refer to
    \e MApp_DigitalMedia_SetRepeatAB() or \e MApp_DigitalMedia_GetRepeatAB()
    for more details. */
typedef enum
{
    E_DM_REPEAT_NONE,
    E_DM_REPEAT_A,
    E_DM_REPEAT_B,

    E_DM_REPEAT_MAX,
} E_DM_REPEAT_AB;

/*! \brief Informations about media instance. */
typedef enum
{
    E_DM_INFO_ERROR_INFO,               /*!< The error code. */

    E_DM_INFO_H_SIZE,                   /*!< The horizontal size of displayed movie/photo. Apply to
                                             \e E_DM_STRM_TYPE_MOVIE and \e E_DM_STRM_TYPE_PHOTO. */
    E_DM_INFO_V_SIZE,                   /*!< The vertical size of displayed movie/photo. Apply to
                                             \e E_DM_STRM_TYPE_MOVIE and \e E_DM_STRM_TYPE_PHOTO. */

    E_DM_INFO_FRM_PER_SEC,              /*!< Frames per second. Apply to \e E_DM_STRM_TYPE_MOVIE. */
    E_DM_INFO_TOTAL_TIME,               /*!< The duration in second of media instance. Apply to
                                             \e E_DM_STRM_TYPE_MOVIE and \e E_DM_STRM_TYPE_MUSIC. */
    E_DM_INFO_CUR_TIME,                 /*!< The current time in second of media instance. Apply to
                                             \e E_DM_STRM_TYPE_MOVIE and \e E_DM_STRM_TYPE_MUSIC. */
    E_DM_INFO_NB_PROGRAM,               /*!< Total number of video programs. Apply to \e E_DM_STRM_TYPE_MOVIE. */
    E_DM_INFO_PROGRAM_IDX,              /*!< Index of current video program. Starts from 0. Apply to
                                             \e E_DM_STRM_TYPE_MOVIE. */
    E_DM_INFO_NB_AUDIO_TRACK,           /*!< Total number of audio tracks. Apply to \e E_DM_STRM_TYPE_MOVIE. */
    E_DM_INFO_AUDIO_TRACK_IDX,          /*!< Index of current audio track. Starts from 0. Apply to
                                             \e E_DM_STRM_TYPE_MOVIE. */
    // TODO:  including internal and external subtitle or ?
    E_DM_INFO_NB_SUBTITLE_TRACK,        /*!< Total number of subtitle tracks. Apply to \e E_DM_STRM_TYPE_MOVIE. */
    E_DM_INFO_SUBTITLE_TRACK_IDX,       /*!< Index of current subtitle track. Starts from 0. Apply to
                                             \e E_DM_STRM_TYPE_MOVIE. */

    // TBD: txt subtitle is handled by ?
    E_DM_INFO_CURRENT_SUBTITLE_TEXT,        /*!< Is subtitle a text subtitle. Apply to \e E_DM_STRM_TYPE_MOVIE. */
    E_DM_INFO_CURRENT_SUBTITLE_ISUNICODE,   /*!< Is text subtitle unicoded. Apply to \e E_DM_STRM_TYPE_MOVIE. */

    E_DM_INFO_MAX_FB_SPEED,             /*!< Max Fast backword speed. Apply to \e E_DM_STRM_TYPE_MOVIE.
                                             It's an alias of "if trick mode playback is possible?"
                                             The value returned with \e E_DM_INFO_MAX_FB_SPEED is the max
                                             fast backword speed supported by codec. But the foundation of this
                                             speed is index table. If the returned value is 0, it also implies
                                             no index table was found in media instance. Since trick mode
                                             playback requires index table as a reference, the return value
                                             of 0 also implies trick mode playback is impossible. */

    E_DM_INFO_DECODED_PHOTO_WDITH,      /*!< The horizontal size of decoded photo. Apply to \e E_DM_STRM_TYPE_PHOTO. */
    E_DM_INFO_DECODED_PHOTO_HEIGHT,     /*!< The vertical size of decoded photo. Apply to\e E_DM_STRM_TYPE_PHOTO. */
    E_DM_INFO_PHOTO_DECODE_PROGRESS,    /*!< Total progress of photo decoding. 0 ~ 100. Apply to
                                             \e E_DM_STRM_TYPE_PHOTO. */

    E_DM_INFO_DISPLAYING_PHOTO_SIZE,    /*!< The data size of currently displayed photo. Apply to
                                            \e E_DM_STRM_TYPE_PHOTO. */

    E_DM_INFO_MUSIC_LAYER_LEN,              /*!music info len,for wma, Layer,COMMENT and GENRE info are not supported.*/
    E_DM_INFO_MUSIC_BITRATE_LEN,
    E_DM_INFO_MUSIC_SAMPLINGRATE_LEN,
    E_DM_INFO_MUSIC_ALBUM_LEN,
    E_DM_INFO_MUSIC_TITLE_LEN,
    E_DM_INFO_MUSIC_ARTIST_LEN,
    E_DM_INFO_MUSIC_YEAR_LEN,
    E_DM_INFO_MUSIC_GENRE_LEN,
    E_DM_INFO_MUSIC_COMMENT_LEN,
    E_DM_INFO_MUSIC_CHECK_FF_FB_LEN,
    E_DM_INFO_MUSIC_LAYER,                       /*!music info,for wma, Layer,COMMENT and GENRE info are not supported. */
    E_DM_INFO_MUSIC_BITRATE,
    E_DM_INFO_MUSIC_SAMPLINGRATE,
    E_DM_INFO_MUSIC_ALBUM,
    E_DM_INFO_MUSIC_TITLE,
    E_DM_INFO_MUSIC_ARTIST,
    E_DM_INFO_MUSIC_YEAR,
    E_DM_INFO_MUSIC_GENRE,
    E_DM_INFO_MUSIC_COMMENT,
    E_DM_INFO_MUSIC_CHECK_FF_FB,

    E_DM_INFO_MUSIC_TYPE,                     /*!music type, mp3/wav/aac/wma*/
}E_DM_INFO;

//------------------------------------------------------------------------------
// Extern Global Variabls
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Extern Functions
//------------------------------------------------------------------------------
// main loop API
INTERFACE void      MApp_DigitalMedia_Task(void);

// init API
INTERFACE BOOLEAN   MApp_DigitalMedia_ModuleInit(void);
INTERFACE BOOLEAN   MApp_DigitalMedia_Init(DM_STRM_HDL *pStreamHdl, E_DM_STRM_TYPE eType, E_DM_STRM_ATTRIB eAttrib, DM_STRM_IO *pfnCallbacks);

// playback API
INTERFACE BOOLEAN   MApp_DigitalMedia_Play(E_DM_STRM_TYPE eType);
INTERFACE void      MApp_DigitalMedia_Stop(E_DM_STRM_TYPE eType);
INTERFACE BOOLEAN   MApp_DigitalMedia_Pause(E_DM_STRM_TYPE eType);
INTERFACE BOOLEAN   MApp_DigitalMedia_Resume(E_DM_STRM_TYPE eType);

// track switch API
INTERFACE BOOLEAN   MApp_DigitalMedia_ChangeProgram(E_DM_STRM_TYPE eType, U8 u8TrackIdx);
INTERFACE BOOLEAN   MApp_DigitalMedia_ChangeAudio(E_DM_STRM_TYPE eType, U8 u8TrackIdx);
INTERFACE BOOLEAN   MApp_DigitalMedia_ChangeSubtitle(E_DM_STRM_TYPE eType, U8 u8TrackIdx);
INTERFACE BOOLEAN   MApp_DigitalMedia_ChangeExternalSubtitle(E_DM_SUBTITLE_TYPE eSubtitleType,DM_STRM_HDL SubtitleHdl,DM_STRM_HDL SubStreamHdl);
INTERFACE void      MApp_DigitalMedia_SetExternalSubtitleType(E_DM_SUBTITLE_TYPE eSubtitleType);
INTERFACE BOOLEAN   MApp_DigitalMedia_EnableSubtitle(void);
INTERFACE BOOLEAN   MApp_DigitalMedia_DisableSubtitle(void);

// trick play API
INTERFACE BOOLEAN   MApp_DigitalMedia_GotoTime(E_DM_STRM_TYPE eType, U32 u32TimeInMs);
INTERFACE BOOLEAN   MApp_DigitalMedia_SetTrickMode(E_DM_STRM_TYPE eType, E_DM_PLAY_MODE ePlayMode, E_DM_SPEED eSpeed);
INTERFACE BOOLEAN   MApp_DigitalMedia_GetTrickMode(E_DM_STRM_TYPE eType, E_DM_PLAY_MODE *pePlayMode, E_DM_SPEED *peSpeed);
INTERFACE BOOLEAN   MApp_DigitalMedia_SetRepeatAB(E_DM_STRM_TYPE eType, E_DM_REPEAT_AB eRepeatAct);
INTERFACE BOOLEAN   MApp_DigitalMedia_GetRepeatAB(E_DM_STRM_TYPE eType, E_DM_REPEAT_AB *peRepeatAct);

// image relative API
INTERFACE BOOLEAN   MApp_DigitalMedia_SetView(E_DM_STRM_TYPE eType, BOOLEAN bFullScreen, ST_DM_RECT *pstViewWin);
INTERFACE BOOLEAN   MApp_DigitalMedia_GetView(E_DM_STRM_TYPE eType, ST_DM_RECT *pstViewWin);
INTERFACE BOOLEAN   MApp_DigitalMedia_SetRotation(E_DM_STRM_TYPE eType, E_DM_ROTATION eRotate);
INTERFACE BOOLEAN   MApp_DigitalMedia_GetRotation(E_DM_STRM_TYPE eType, E_DM_ROTATION *peRotate);
INTERFACE BOOLEAN   MApp_DigitalMedia_SetZoom(E_DM_STRM_TYPE eType, E_DM_ZOOM eZoom);
INTERFACE BOOLEAN   MApp_DigitalMedia_GetZoom(E_DM_STRM_TYPE eType, E_DM_ZOOM *peZoom);
INTERFACE BOOLEAN   MApp_DigitalMedia_MoveView(E_DM_STRM_TYPE eType, E_DM_DIRECTION eDirection, U16 u16Offset);

INTERFACE U32       MApp_DigitalMedia_Photo_GetFreeSlot(void);
INTERFACE BOOLEAN   MApp_DigitalMedia_Photo_StopDisplay(void);
INTERFACE BOOLEAN   MApp_DigitalMedia_Photo_SlideShow(BOOLEAN bEnable);
INTERFACE BOOLEAN   MApp_DigitalMedia_Photo_SlideShowTimeOut(U16 u16TimeOutInSec);

// information granting API
INTERFACE U32       MApp_DigitalMedia_GetInfo(E_DM_STRM_TYPE eType, E_DM_INFO enInfo);

// encryption relative API
INTERFACE BOOLEAN   MApp_DigitalMedia_SetDRMKey(U8 *pu8Key, U32 u32Size);

// music API
INTERFACE BOOLEAN   MApp_DigitalMedia_SetMusicType(E_DM_MUSIC_TYPE enMusicType);
INTERFACE BOOLEAN   MApp_DigitalMedia_EnableLRCLyric(void);
INTERFACE BOOLEAN   MApp_DigitalMedia_DisableLRCLyric(void);
INTERFACE BOOLEAN   MApp_DigitalMedia_IsCurrentLRCLyricAvail(void);
INTERFACE BOOLEAN   MApp_DigitalMedia_GetMusicInfo(E_DM_INFO enInfo, U8* pBuf, U16 u16Len);

//double buffer
INTERFACE BOOLEAN   MApp_DigitalMedia_Get_DoubleBufInfo(E_DM_STRM_TYPE eType, U32* pu32DoubleBuffAddr, U32* pu32DoubleBufSize);
INTERFACE void      MApp_DigitalMedia_Fill_DoubleBufDone(E_DM_STRM_TYPE eType, U8 u8BufIndex, U32 u32Len, BOOLEAN bFileEnd);
// misc
INTERFACE BOOLEAN   MApp_DigitalMedia_EnableEvent(E_DM_STRM_TYPE eType, E_DM_EVENT eEvent);
INTERFACE BOOLEAN   MApp_DigitalMedia_DisableEvent(E_DM_STRM_TYPE eType, E_DM_EVENT eEvent);

#undef INTERFACE

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef _MAPP_DIGITAL_MEDIA_H_

