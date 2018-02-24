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

#ifndef _MAPP_VIDEOPLAYER_H
#define _MAPP_VIDEOPLAYER_H

//-------------------------------------------------------------------------------------------------
// Standard include files:
//-------------------------------------------------------------------------------------------------
#include "datatype.h"
#include "MApp_Exit.h"
#include "MApp_Key.h"
#include "mapp_mplayer.h"
#include "msAPI_Video.h"
#ifdef TRITON_DDI
#include "MApp_EMPMsg.h"
#endif
#include "mapp_mplayer_subtitle.h"
#include "MApp_GlobalSettingSt.h"
#include "mapp_photo_display.h"

#if ENABLE_HK_MM
#include "mapp_vdplayer_sharememcfg_HK_MM.h"
#else
#include "mapp_vdplayer_sharememcfg.h"
#endif

#ifdef MAPP_VIDEOPLAYER_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

//-------------------------------------------------------------------------------------------------
// Project include files:
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
#define FBL_ZOOM                                1

// Here defines the functionality relating to CHIP
#define MJPEG_HARDWARE_MODE                     1

#define MJPEG_HARDWARE_MODE_ENABLED (defined(MJPEG_HARDWARE_MODE) && (MJPEG_HARDWARE_MODE))

#define VDPLAYER_CHECK_PREVIEW_ABORT            1
#define VDPLAYER_CHECK_COPROCESSOR_STATUS       1

#define VDPLAYER_MVOP_REAL_FRAMERATE            1
#define VDPLAYER_VERIFY_SCALER_FPGA             0
#if (VDPLAYER_VERIFY_SCALER_FPGA == 1)
#undef VDPLAYER_MVOP_REAL_FRAMERATE
#define VDPLAYER_MVOP_REAL_FRAMERATE            0
#define VDPLAYER_VSYNC_RATE                     10
#endif // #if (VDPLAYER_VERIFY_SCALER_FPGA == 1)

#define VDPLAYER_INIT_TIMEOUT                   20000
#define VDPLAYER_COPROCESSOR_CHECK_TIMEOUT      8000

//now only "h264 file mode", 'VC1 advance profile" will support DS("h264 ts", "VC1 main profile", "RM" don't support DS)
#define DYNSCALING                              0
#define DYNAMIC_SCALING_VB_H                    1920//960
#define DYNAMIC_SCALING_VB_V                    1080

//MVC enable
#define ENABLE_MVC  0

//change aspect ratio without bluescreen
#define CHANGE_AR_WITHOUT_BLUESCREEN            DISABLE

#define SEAMLESS_PLAYING_ENABLE                 ENABLE

#define SUPPORTED_PLAYABLE_AUDIO_TRACK_CHECK     1

#define SUPPERTED_ADVERTISEMENT_MODE        DISABLE

#define SUPPERTED_SEAMLESS_SMOTH    DISABLE

typedef enum
{
    MODE_NORMAL_PLAY = 0,
    MODE_PAUSE,
    MODE_SLOW_FORWARD,
    MODE_FAST_FORWARD,
    MODE_FAST_BACKWARD,
} EN_PLAY_MODE;

typedef enum
{
    SET_REPEAT_AB_NONE = 0,
    SET_REPEAT_A,
    SET_REPEAT_B,
} EN_SET_REPEATAB;


typedef enum
{
    PLAY_SPEEDx1 = 1,
    PLAY_SPEEDx2,
    PLAY_SPEEDx4,
    PLAY_SPEEDx8,
    PLAY_SPEEDx16,
    PLAY_SPEEDx32,
    PLAY_SPEED_MAX
} EN_PLAY_SPEED;

typedef enum
{
    E_SUBTITLE_STATE_COMMAND_NOT_SHOW=0,
    E_SUBTITLE_STATE_COMMAND_SHOW,
    E_SUBTITLE_STATE_COMMAND_ENABLE_ALL_SUBTITLE,
    E_SUBTITLE_STATE_COMMAND_ENABLE_PICT_SUBTITLE,
    E_SUBTITLE_STATE_COMMAND_ENABLE_TEXT_SUBTITLE,
    E_SUBTITLE_STATE_COMMAND_DISABLE_ALL_SUBTITLE,
    E_SUBTITLE_STATE_COMMAND_DISABLE_TS_SUBTITLE,
    E_SUBTITLE_STATE_COMMAND_DISABLE_BMP_SUBTITLE,
} EN_SUBTITLE_STATE_COMMAND;


typedef enum
{
    E_SUBTITLE_INFO_NB_TRACK,
    E_SUBTITLE_INFO_TRACK_ID,
    E_SUBTITLE_INFO_TYPE,
} EN_SUBTITLE_INFO;

/// Specify the TS subtitle attribute flag
typedef enum
{
    E_TS_INTERNAL_SUBTITLE_BMP        = BIT0,    /// BMP subtitle
    E_TS_INTERNAL_SUBTITLE_PGS        = BIT1,    /// PGS subtitle
} EN_TS_SUBTITLE_FLAG;


typedef enum
{
    /// Video codec type is unknow.
    E_VDPLAYER_VIDEO_UNKNOW = -1,
    /// Video codec type is MPEG 4.
    E_VDPLAYER_VIDEO_MPEG4,
    /// Video codec type is motion JPG.
    E_VDPLAYER_VIDEO_MJPEG,
    /// Video codec type is H264.
    E_VDPLAYER_VIDEO_H264,
    /// Video codec type is RealVideo.
    E_VDPLAYER_VIDEO_RM,
    /// Video codec type is TS File.
    E_VDPLAYER_VIDEO_TS,
    /// Video codec type is MPEG 1/2.
    E_VDPLAYER_VIDEO_MPG,
    /// Video codec type is VC1.
    E_VDPLAYER_VIDEO_VC1,
    /// Video codec type is Audio Video Standard.
    E_VDPLAYER_VIDEO_AVS,
    /// Video codec type is FLV.
    E_VDPLAYER_VIDEO_FLV,
    /// Video codec type is MVC.
    E_VDPLAYER_VIDEO_MVC,
    /// Video codec type is VP6.
    E_VDPLAYER_VIDEO_VP6,
    /// Video codec type is VP8.
    E_VDPLAYER_VIDEO_VP8,
    /// Video codec type is H265.
    E_VDPLAYER_VIDEO_HEVC,
}EN_VDPLAYER_VIDEO_TYPE;


typedef struct
{
    EN_VDP_PLAY_MODE enPlayMode;
    EN_VDP_PLAY_SPEED enPlaySpeed;
} TRICK_STATUS;


typedef enum
{
    E_VDPLAYER_STATUS_STOP,
    E_VDPLAYER_STATUS_INIT,
    E_VDPLAYER_STATUS_PLAYING,
    E_VDPLAYER_STATUS_PAUSE,
} EN_VDPLAYER_STATUS;

typedef enum
{
    E_VDPLAYER_CMD_STOP,
    E_VDPLAYER_CMD_PLAY,
    E_VDPLAYER_CMD_PAUSE,
    E_VDPLAYER_CMD_RESUME,
    E_VDPLAYER_CMD_SLOW_FORWARD,
    E_VDPLAYER_CMD_FAST_FORWARD,
    E_VDPLAYER_CMD_FAST_BACKWARD,
    E_VDPLAYER_CMD_CHANGE_AUDIO,
    E_VDPLAYER_CMD_CHANGE_SUBTITLE,
    E_VDPLAYER_CMD_TIME_SEEK,
    E_VDPLAYER_CMD_NONE,
} EN_VDPLAYER_COMMAND;

typedef enum
{
    E_VDPLAYER_PHASE_STANDBY = 0,
    E_VDPLAYER_PHASE_INIT,
    E_VDPLAYER_PHASE_START_PLAY,
    E_VDPLAYER_PHASE_DECODE,
    E_VDPLAYER_PHASE_WAIT_DECODE_DONE,
    E_VDPLAYER_PHASE_SLEEP,
    E_VDPLAYER_PHASE_PAUSE,
    E_VDPLAYER_PHASE_STOP,
    E_VDPLAYER_PHASE_EXIT,
} EN_VDPLAYER_PHASE;

typedef enum
{
    E_VDPLAYER_INFO_TOTAL_TIME,
    E_VDPLAYER_INFO_CUR_TIME,
    E_VDPLAYER_INFO_FRM_PER_SEC,
    E_VDPLAYER_INFO_DEMUX_FRM_RATE,
    E_VDPLAYER_INFO_H_SIZE,
    E_VDPLAYER_INFO_V_SIZE,
    E_VDPLAYER_INFO_NB_AUDIO_TRACK,
    E_VDPLAYER_INFO_AUDIO_TRACK_ID,
    E_VDPLAYER_INFO_NB_SUBTITLE_TRACK,
    E_VDPLAYER_INFO_SUBTITLE_TRACK_ID,
    E_VDPLAYER_INFO_NB_PROGRAM,
    E_VDPLAYER_INFO_PROGRAM_ID,
#if (ENABLE_DIVX_PLUS == 1)
    E_VDPLAYER_INFO_NB_TITLE,
    E_VDPLAYER_INFO_NB_EDITION,
    E_VDPLAYER_INFO_NB_CHAPTER,
#endif
    E_VDPLAYER_INFO_SHARE_MEM_ADDR,
    E_VDPLAYER_INFO_CURRENT_SUBTITLE_TEXT,
    E_VDPLAYER_INFO_CURRENT_SUBTITLE_TAGCOUNT,
    E_VDPLAYER_INFO_CURRENT_SUBTITLE_ISUNICODE ,
    E_VDPLAYER_INFO_ERROR_INFO ,
    E_VDPLAYER_INFO_MAX_FB_SPEED,
    E_VDPLAYER_INFO_PAR_H_SIZE,
    E_VDPLAYER_INFO_PAR_V_SIZE,
    E_VDPLAYER_INFO_DEMUX_H_SIZE,
    E_VDPLAYER_INFO_DEMUX_V_SIZE,
    E_VDPLAYER_INFO_Audio_Request_Size,
#if ENABLE_DRM
    E_VDPLAYER_INFO_DRM_FILE_FORMAT,
    E_VDPLAYER_INFO_DRM_RENTAL_EXPIRE_STATUS,
    E_VDPLAYER_INFO_DRM_AUTHORIZATION_STATUS,
    E_VDPLAYER_INFO_DRM_RETURN_CODE,
    E_VDPLAYER_INFO_DRM_RENTAL_FILE,
    E_VDPLAYER_INFO_DRM_RENTAL_USE_LIMIT,
    E_VDPLAYER_INFO_DRM_RENTAL_USE_COUNT,
#endif
    E_VDPLAYER_INFO_FRAMEINFO_WIDTH,
    E_VDPLAYER_INFO_FRAMEINFO_HEIGHT,
#if ENABLE_LAST_MEMORY==1
    E_VDPLAYER_INFO_RESUME_PLAY_SEEKPOS_LOW,
    E_VDPLAYER_INFO_RESUME_PLAY_SEEKPOS_HIGH,
    E_VDPLAYER_INFO_RESUME_PLAY_SEEKPTS,
    E_VDPLAYER_INFO_RESUME_PLAY_PROGRAM_IDX,
    E_VDPLAYER_INFO_RESUME_PLAY_AUDIO_TRACK_ID,
    E_VDPLAYER_INFO_RESUME_PLAY_SUBTITLE_TRACK_ID,
#endif
    E_VDPLAYER_INFO_AUDIO_CODEC,
    E_VDPLAYER_INFO_VIDEO_CODEC,
    E_VDPLAYER_INFO_AUDIO_LANGUAGE,
    E_VDPLAYER_INFO_SUBTITLE_LANGUAGE,
    E_VDPLAYER_INFO_AUDIO_CHANNEL,
    E_VDPLAYER_INFO_PLAY_MODE,
    E_VDPLAYER_INFO_PLAY_SPEED,
#if ENBALE_PARENTALRATING_MM
    E_VDPLAYER_INFO_CURRENT_PROGRAME_RATING,
#endif
}EN_VDPLAYER_INFO;

/// Define audio codec type
typedef enum
{
    /// Audio codec type is none.
    E_VDPLAYER_AUDIO_UNKNOW = -1,
    /// Audio codec type is WMA.
    E_VDPLAYER_AUDIO_WMA,
    /// Audio codec type is DTS.
    E_VDPLAYER_AUDIO_DTS,
    /// Audio codec type is MP3.
    E_VDPLAYER_AUDIO_MP3,
    /// Audio codec type is MPEG.
    E_VDPLAYER_AUDIO_MPEG,
    /// Audio codec type is AAC.
    E_VDPLAYER_AUDIO_AC3,
    /// Audio codec type is AC3 PLUS.
    E_VDPLAYER_AUDIO_AC3_PLUS,
    /// Audio codec type is AAC.
    E_VDPLAYER_AUDIO_AAC,
    /// Audio codec type is PCM.
    E_VDPLAYER_AUDIO_PCM,
    /// Audio codec type is ADPCM.
    E_VDPLAYER_AUDIO_ADPCM,
    /// Audio codec type is RAAC.
    E_VDPLAYER_AUDIO_RAAC,
    /// Audio codec type is COOK.
    E_VDPLAYER_AUDIO_COOK,
    /// Audio codec type is FLAC.
    E_VDPLAYER_AUDIO_FLAC,
    /// Audio codec type is VORBIS.
    E_VDPLAYER_AUDIO_VORBIS,
    /// Audio codec type is AMR NB
    E_VDPLAYER_AUDIO_AMR_NB,
    /// Audio codec type is AMR WB
    E_VDPLAYER_AUDIO_AMR_WB,
    /// Audio codec type is DRA
    E_VDPLAYER_AUDIO_DRA,
} EN_VDPLAYER_AUDIO_TYPE;


typedef enum {
    E_HEADERPARSER_OK = TRUE,        // Fully Success
    E_HEADERPARSER_NOT_OK = FALSE,        // Generic errors
    E_HEADERPARSER_NOT_ENOUGH_INFO = -1,      // Parse OK, but not have enough metainfo
    E_HEADERPARSER_NOT_ENOUGH_RESOURCE     =-3,        // Insufficient resources, like no mediaItem, or can not file read or seek
    E_HEADERPARSER_NOT_SUPPORTED           =-4,        // Parse OK, but VDPlayer not supported
    E_HEADERPARSER_TIMEOUT                 =-6,        // The time-out period expired
} EN_HEADERPARSER_STATUS;


typedef enum
{
    E_SCREEN_SETTINGS_NONE=0,
    E_SCREEN_SETTINGS_SCALER_BLUESCREEN,
    E_SCREEN_SETTINGS_SCALER_FREEZESCREEN,
    E_SCREEN_SETTINGS_SCALER_ACE_PATCHTRICKMODE,
    E_SCREEN_SETTINGS_SCALER_ACE_FILMMODE,
    E_SCREEN_SETTINGS_SCALER_PQ_Y_MOTION,
} EN_VDPLAYER_SCREEN_SETTINGS;


typedef enum
{
    VDPLAYER_ZOOM_FACT_1_DIV_4     = 0,
    VDPLAYER_ZOOM_FACT_1_DIV_2     = 1,
    VDPLAYER_ZOOM_FACT_NORMAL      = 2,
    VDPLAYER_ZOOM_FACT_2X          = 3,
    VDPLAYER_ZOOM_FACT_4X          = 4,
    VDPLAYER_ZOOM_FACT_8X          = 5,
    VDPLAYER_ZOOM_FACT_UNSUPPORT
} VDPLAYER_ZOOM_FACT;

typedef enum
{
    E_VDPLAYER_FLG_NONE         = 0x00,
    E_VDPLAYER_FLG_PREVIEW      = 0x01,
    E_VDPLAYER_FLG_SHOWVIDEO    = 0x02,
} enumVDPlayerFlags;

typedef enum
{
    E_UART_SWITCH_TO_NONE,
    E_UART_SWITCH_TO_HK,
    E_UART_SWITCH_TO_COPROCESSOR,
    E_UART_SWITCH_TO_VDEC,
} EN_VDPLAYER_UART_SWITCH;

#if ENABLE_DVD
typedef enum
{
    E_VDPLAYER_DVD_AUDIO_AC3,
    E_VDPLAYER_DVD_AUDIO_MPEG1,
    E_VDPLAYER_DVD_AUDIO_MPEG2EXT,
    E_VDPLAYER_DVD_AUDIO_LPCM,
    E_VDPLAYER_DVD_AUDIO_DTS,
    E_VDPLAYER_DVD_AUDIO_UNKNOWN,
} enumDVDAudioType;

typedef enum
{
    E_VDPLAYER_DVD_STATE_RUNNING,
    E_VDPLAYER_DVD_STATE_WAIT,
    E_VDPLAYER_DVD_STATE_WAITDONE,
    E_VDPLAYER_DVD_STATE_STILL,
    E_VDPLAYER_DVD_STATE_STILL_CHECK,
    E_VDPLAYER_DVD_STATE_PAUSE,
    E_VDPLAYER_DVD_STATE_TRICKMODE,
    E_VDPLAYER_DVD_STATE_STOP,
} enumVDPlayerDVDState;

typedef enum
{
    E_VDPLAYER_DVD_TRICKMODE_STATE_INIT,
    E_VDPLAYER_DVD_TRICKMODE_STATE_RUNNING,
    E_VDPLAYER_DVD_TRICKMODE_STATE_RUNNING_SCAN,
    E_VDPLAYER_DVD_TRICKMODE_STATE_DONE,
} enumVDPlayerDVDTrickModeState;

#endif

typedef enum
{
    E_VDPLAYER_FAIL_STATUS_NONE,
    E_VDPLAYER_FAIL_STATUS_USER_EXIT,
    E_VDPLAYER_FAIL_STATUS_VDPLAYER_ERROR,
    E_VDPLAYER_FAIL_STATUS_NUM,
} EN_VDPLAYER_FAIL_STATUS;

//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------

// Memory Layout for AEON VDPLAYER
#define VDPLAYER_SHAREMEM_ADDR  ((VDPLAYER_DATA_MEMORY_TYPE & MIU1) ? (VDPLAYER_DATA_ADR | MIU_INTERVAL) : (VDPLAYER_DATA_ADR))
#define VDPLAYER_SHAREMEM_SIZE  0x1000   // 4K
#define VDPLAYER_AEON_DATABUFF_ADDR   VDPLAYER_SHAREMEM_ADDR+VDPLAYER_SHAREMEM_SIZE
#define VDPLAYER_AEON_DATABUFF_SIZE VDPLAYER_DATA_LEN-VDPLAYER_SHAREMEM_SIZE


#if 0
//-------------------------------
// MB_CLASS_MPEG2_FS
//-------------------------------
//Issue Command Index
#define MB_MPEG2_FS_PARSE                       0x01        //[0]~[3]: PS buffer start
                                                            //[4]~[7]: PS buffer end
#define MB_MPEG2_FS_INFO                        0x02        //[0]~[3]: File length
#define MB_MPEG2_FS_SET_POS                     0x03        //[0]~[3]: File position
#define MB_MPEG2_FS_PRE_PARSE                   0x04        //[0]~[3]: PS buffer start
                                                            //[4]~[7]: PS buffer end
//Receive Command Index
#define MB_MPEG2_FS_PARSE_COMPLETED             0x80        //[0]: 0: forward Seek. 1: backward Seek.
                                                            //[1]~[4]: Offset
                                                            //[5]~[8]: Request size
#define MB_MPEG2_FS_PARSE_COMPLETED_DATA        0x83        //[0]: 0: forward Seek. 1: backward Seek.
                                                             //[1]~[4]: video demux num
                                                            //[5]~[8]: audio demux num
#define MB_MPEG2_FS_PRE_PARSE_COMPLETED         0x81        //[0]: 0: Can't support decode, 1: Can support decode.
                                                            //[1]: MPEG file type.
                                                            //[2]: MPEG file audio count.
#define MB_MPEG2_FS_PRE_PARSE_COMPLETED_DATA    0x84        //[0]: subpic count
                                                            //[1]~[3]: sub pic ID


#define MB_MPEG2_FS_PRE_PARSE_NEXT_BUFF         0x82        //
//-------------------------------
// MB_CLASS_MPEG2
//-------------------------------
//Issue Command Index
#define MB_MPEG2_SET_VID_PARS_TYPE              0x01        //[0]: Parse type.
                                                            //[1]~[4]: Output buffer start
                                                            //[5]~[8]: Output buffer end
#define MB_MPEG2_SET_VID_RD_PTR                 0x03        //[0]~[3]: TSP Read buffer pointer
#define MB_MPEG2_SET_AUD_PARS_TYPE              0x04        //[0]: Parse type.
                                                            //[1]~[4]: Output buffer start
                                                            //[5]~[8]: Output buffer end
#define MB_MPEG2_SET_AUD_RD_PTR                 0x06
#define MB_MPEG2_PARS_ENABLE                    0x08        //[0]: 0x1, enable video parsing. 0x2, enable audio parsing.
                                                            //[1]~[2]: Video PID (type is TS)
                                                            //[3]~[4]: Audio PID (type is TS)
#define MB_MPEG2_PARS_DISABLE                   0x09        //[0]: 0x1, disable video parsing. 0x2, disable audio parsing.
#define MB_MPEG2_PARS_CTL                       0x0a        //[0]: 0x0, Stop parsing process.
                                                            //     0x1, Normal parsing process.
                                                            //     0x2, Forward I frame parsing process.
                                                            //     0x3, Backward I frame parsing process.
#define MB_MPEG2_GET_PTS_POS                    0x0b        //[0]~[3]: PTS

#define MB_MPEG2_SET_AUD_INFO                   0x0c        //[0]: Audio Type
                                                            //[1]: Audio stream_id or sub_Stream_id

#define MB_MPEG2_SET_PCR_INFO                   0x0d        //[0]~[1]: PCR PID

#define MB_MPEG2_RESET_TSP_BUFF_PTR             0x0e        //[0]~[3]: TSP buffer pointer
#define MB_MPEG2_SET_PTS_SHARE_ADR                 0x0f        //[0]~[3]: PTS buffer pointer
#define MB_MPEG2_SET_SUBPIC_INFO                0x10        //[0]: subpic stream_id



//Receive Command Index
#define MB_MPEG2_SET_STC                        0x80        //[0]: STC bit 32, [1]: STC bit 31~24,
                                                            //[2]: STC bit 23~16, [3]: STC bit 15~8, [4]: STC bit 7~0,
#define MB_MPEG2_SET_TSP_PTR                    0x81        //[0]~[3]: TSP buffer write pointer
#define MB_MPEG2_SET_VID_ES_PTR                 0x82
#define MB_MPEG2_SET_AUD_ES_PTR                 0x83        //[0]~[3]: ES buffer write pointer
                                                            //[4]~[7]: PTS

#define MB_MPEG2_SET_TS_PGINFO                  0x84        //[0]: Program Index
                                                            //[1]~[2]: Program number
                                                            //[3]~[4]: PCR Pid
                                                            //[5]~[6]: Video Pid
                                                            //[7]~[8]: Audio Pid
                                                            //[9]: Audio type
#define MB_MPEG2_SET_TS_PGINFO2                 0x85        //[0]: Program Index
                                                            //[1]~[2]: Sub-pic Pid
#define MB_MPEG2_SET_TS_PGCOUNT                 0x86        //[0]~[3]: Program count
#define MB_MPEG2_SET_DMA_REQUEST                0x87        //[0]~[2]: Dst addr (256 bytes alignment)
                                                            //[3]~[5]: Src addr (256 bytes alignment)
                                                            //[6]~[9]: DMA size (byte unit)
#define MB_MPEG2_PARS_SPU                       0x88
#endif


//-------------------------------
// MB_CLASS_VDPLAYER_FS
//-------------------------------
//Receive Command Index
#define MB_VDPLAYER_FS_INIT                        0x01         //[0]~[3]: VDPlayer info buffer start
                                                                //[4]~[7]: VDPlayer data buffer start

#define MB_VDPLAYER_FS_PAR_STREAM_INFO             0x02         //[0]: no. of stream

#define MB_VDPLAYER_FS_PAR_FRAME_INFO              0x03         //[0]~[3]: Frame info buffer address

#define MB_VDPLAYER_INIT_INDEX                     0x04

#define MB_VDPLAYER_INIT_AUDIO                     0x05
#define MB_VDPLAYER_INIT_AUDIO_2                   0x06
#define MB_VDPLAYER_INIT_AUDIO_3                   0x07
#define MB_VDPLAYER_INIT_AC3                       0x08

//Issue Command Index
#define MB_VDPLAYER_FS_INIT_DONE                   0x80         //[0]: 0: success. 1: fail.







//-------------------------------
// MB_CLASS_VDPLAYER
//-------------------------------
// Move to mapp_vdplayer_sharememcfg.h
#if 0
//51-->Aeon Command Index
#define MB_VDPLAYER_INIT                    0x01
#define MB_VDPLAYER_MEM_INIT                0x02
#define MB_VDPLAYER_STATE_INIT              0x03
#define MB_VDPLAYER_RESET                   0x04
#define MB_VDPLAYER_SET_PREVIEW_MODE        0x05

#define MB_VDPLAYER_PLAY                    0x10
#define MB_VDPLAYER_STOP                    0x11
#define MB_VDPLAYER_PAUSE                   0x12
#define MB_VDPLAYER_RESUME                  0x13
#define MB_VDPLAYER_FF                      0x14
#define MB_VDPLAYER_REW                     0x15
#define MB_VDPLAYER_SET_TRICK_MODE          0x16
#define MB_VDPLAYER_GET_TRICK_MODE          0x17
#define MB_VDPLAYER_REPEAT_AB               0x18
#define MB_VDPLAYER_STEP                    0x19

#define MB_VDPLAYER_SET_SUBTITLE_TRACKID    0x21
#define MB_VDPLAYER_GET_SUBTITLE_STATE      0x22
#define MB_VDPLAYER_GET_VDPLAYER_INFO       0x23
#define MB_VDPLAYER_BEFORE_CAPTURE_VIDEO    0x24
#define MB_VDPLAYER_AFTER_CAPTURE_VIDEO     0x25
#define MB_VDPLAYER_SET_PLAYER_POSITION     0x26

#define MB_VDPLAYER_ACK_51ToAEON            0x30

//DivX MM Function
#define MB_VDPLAYER_GET_AUDIO_TRACK_COUNT_TO_AEON       0x41
#define MB_VDPLAYER_GET_AUDIO_TRACK_ID_TO_AEON          0x42
#define MB_VDPLAYER_SET_AUDIO_TRACK_ID_TO_AEON          0x43
//Subtitle
#define MB_VDPLAYER_SPUQUEUE_GET_DRAM_ADDR_TO_AEON      0x44
#define MB_VDPLAYER_SPUQUEUE_PUSH                       0x45
#define MB_VDPLAYER_MPEG_SUBTITLE_MAIN                  0x46
#define MB_VDPLAYER_MPEG_SET_SUBTITLE_SHOW              0x47
#define MB_VDPLAYER_MPEG_SUBTITLE_INIT_DEINIT           0x48//Init: 0 deinit:1
#define MB_VDPLAYER_MPEG_SUBTITLE_RESET                 0x49
#define MB_VDPLAYER_MPEG_SUBTITLE_SETHEADERINFO         0x4A
#define MB_VDPLAYER_MPEG_SUBTITLE_GETQUEUEINFO          0x4B
#define MB_VDPLAYER_MPEG_SUBTITLE_FILEPROCESS           0x4C
#define MB_VDPLAYER_SUBTITLE_TIMESHIFT                  0x4D
// DRM
#define MB_VDPLAYER_GET_DRM_REG_CODE                    0x50
#define MB_VDPLAYER_CHECK_DRM_AUTHORIZATION             0x51
#define MB_VDPLAYER_QUERY_DRM_RENTAL_STATUS             0x52
#define MB_VDPLAYER_GET_DRM_REG_CODE_2                  0x53
#define MB_VDPLAYER_GET_DRM_DEACTIVATION_CODE           0x54

#define MB_VDPLAYER_TS_SET_PROGRAM                      0x60
#if (ENABLE_DIVX_PLUS == 1)
#define MB_VDPLAYER_SET_TITLE_ID                        0x61
#define MB_VDPLAYER_SET_EDITION_ID                      0x62
#define MB_VDPLAYER_SET_CHAPTER_ID                      0x63
#define MB_VDPLAYER_SET_AUTOGEN_CHAPTER_ID              0x64
#endif

#define MB_VDPLAYER_SETDYNSCALINGPARAMS                 0x70 //for DS ZOOM

//Aeon->51 Command Index
#define MB_VDPLAYER_FILE_READ               0x80
#define MB_VDPLAYER_FILE_SEEK               0x81
#define MB_VDPLAYER_FILE_OPEN               0x82
#define MB_VDPLAYER_FILE_CLOSE              0x83
#define MB_VDPLAYER_VIDEO_INIT              0x84
#define MB_VDPLAYER_AUDIO_INIT              0x85
#define MB_VDPLAYER_SETUP_DISPLAY           0x86
#define MB_VDPLAYER_CLOSE_DISPLAY           0x87
#define MB_VDPLAYER_AUDIO_START             0x88
#define MB_VDPLAYER_FILE_READ_NONBLOCKING   0X89
#define MB_VDPLAYER_FILE_DUMP_RAW           0x8A
#define MB_VDPLAYER_GET_DISPLAY_INFO        0x8B
#define MB_VDPLAYER_SET_DISPLAY_INFO        0x8C
#define MB_VDPLAYER_FILE_SEEK_NONBLOCKING   0x8D


#define MB_VDPLAYER_ACK_AEONTo51                    0xA0
#define MB_VDPLAYER_STATE_RET                       0xA1
#define MB_VDPLAYER_STATE_RET_WAIT                  0xA2
#define MB_VDPLAYER_STATE_RET_EXIT                  0xA3
#define MB_VDPLAYER_FILE_READ_NONBLOCKING_DONE      0XA4
#define MB_VDPLAYER_FILE_SEEK_NONBLOCKING_DONE      0XA5

//TS MM Function
//#define MB_VDPLAYER_SET_INTERRUPT    0xA5
//#define MB_VDPLAYER_AUDIO_SETTING    0xA6
//#define MB_VDPLAYER_SCALER_API       0xA7
#define MB_VDPLAYER_AUD_API                             0xA8
//#define MB_VDPLAYER_VID_API          0xA9

//DivX MM Function
#define MB_VDPLAYER_GET_AUDIO_TRACK_COUNT_FROM_AEON     0x90
#define MB_VDPLAYER_GET_AUDIO_TRACK_ID_FROM_AEON        0x91

//DVD  MM Function
#define MB_VDPLAYER_DVD_INIT                        0xB0
#define MB_VDPLAYER_DVD_PREDECODE                   0xB1
#define MB_VDPLAYER_DVD_SEEKPLAY                    0xB2
#define MB_VDPLAYER_DVD_WAIT                        0xB3
#define MB_VDPLAYER_DVD_DISCONTINUITY               0xB4
#define MB_VDPLAYER_DVD_WAITDONE                    0xB5
#define MB_VDPLAYER_DVD_SET_TRICK_MODE              0xB6
#define MB_VDPLAYER_DVD_PLAY                        0xB7
#define MB_VDPLAYER_DVD_SCANSYNC                    0xB8
#define MB_VDPLAYER_DVD_SCANDONE                    0xB9
#define MB_VDPLAYER_DVD_SCANEXIT                    0xBA
#endif

//-------------------------------------------------------------------------------------------------
// Type and Structure Declaration
//-------------------------------------------------------------------------------------------------
typedef enum
{
    VIDEO_PLAYER_PLAYING_TYPE_MPEG4 = 0,
    VIDEO_PLAYER_PLAYING_TYPE_MPEG2,                // mpeg2
    VIDEO_PLAYER_PLAYING_TYPE_TS,                   // TS file
    VIDEO_PLAYER_PLAYING_TYPE_RM,                   // RM file
#if ENABLE_WMV
    VIDEO_PLAYER_PLAYING_TYPE_WMV,                  // WMV
#endif
#if ENABLE_DVD
    VIDEO_PLAYER_PLAYING_TYPE_DVD,                  // DVD
#endif
    VIDEO_PLAYER_PLAYING_TYPE_NUM,
    VIDEO_PLAYER_PLAYING_TYPE_INVALID,
}VIDEO_PLAYER_PLAYING_TYPE;

typedef enum
{
    VIDEO_PLAYER_INPUT_SOURCE_MM = 0,       //For multimedia
#ifdef ENABLE_KTV
    VIDEO_PLAYER_INPUT_SOURCE_KTV,            //For KTV
#endif
    VIDEO_PLAYER_INPUT_SOURCE_NUM,
    VIDEO_PLAYER_INPUT_SOURCE_INVALID,
}VIDEO_PLAYER_INPUT_SOURCE_TYPE;

typedef struct
{
    U32 duration;
    U32 framerate ;
    U16 width;
    U16 height;
    U8 fileformat;
    U8 drm;
} VDplayerFileHeaderInfo;

typedef enum
{
    E_HP_FILE_FORMAT_NONE=0,
    E_HP_FILE_FORMAT_AVI,
    E_HP_FILE_FORMAT_MP4,
    E_HP_FILE_FORMAT_MKV,
    E_HP_FILE_FORMAT_RM,
    E_HP_FILE_FORMAT_TS,
    E_HP_FILE_FORMAT_VOB,
    E_HP_FILE_FORMAT_DAT,
    E_HP_FILE_FORMAT_MPEG1_PKT,
    E_HP_FILE_FORMAT_VIDEO_ES,
    E_HP_FILE_FORMAT_MPEG2_PKT,
    E_HP_FILE_FORMAT_TRP,
    E_HP_FILE_FORMAT_MAX,
} EN_HEADERPARSER_FILE_FORMAT;

typedef enum
{
    E_BM_STREAM_MODE_NORMAL,
    E_BM_STREAM_MODE_NETWORK_UNSEEKABLE,
    E_BM_STREAM_MODE_NETWORK_SEEKABLE,
    E_BM_STREAM_MODE_INVALID,
} EN_BM_STREAM_MODE;

typedef enum
{
    E_VDPLAYER_CFG_BM_STREAM_MODE = 0,
    E_VDPLAYER_CFG_ENABLE_INTERNAL_SUBTITLE,
    E_VDPLAYER_CFG_FORCE_STOP_CALLBACK,
} EN_VDPLAYER_CFG;

typedef enum
{
    E_FORCE_STOP_INIT,
    E_FORCE_STOP_PLAY,
} EN_VDPLAYER_FORCE_STOP;

typedef enum
{
    E_VDPLAYER_CONTINUE_PLAYING,
    E_VDPLAYER_USER_EXIT,
    E_VDPLAYER_ERROR_EXIT,
} EN_VDPLAYER_FORCE_STOP_RESULT;

typedef EN_VDPLAYER_FORCE_STOP_RESULT (*pfnForceStopCallBack)(EN_VDPLAYER_FORCE_STOP eType);

typedef struct
{
U8 u8DrmRentalStatus;
U8 u8DrmFileFormat;
U8 u8DrmAuthorization;
U32 u32VDPlayerErrCode;
U32 u32DrmRentalCode;
U32 u32DrmRentalFile;
U32 u32DrmRentalLimit;
U32 u32DrmRentalUseCount;
} stDRMinfo;

//-------------------------------------------------------------------------------------------------
// Extern Global Variabls
//-------------------------------------------------------------------------------------------------
#if (FBL_ZOOM==1)
INTERFACE BOOLEAN g_bForceToFB;
#endif
INTERFACE BOOL g_bNonBlockingRead;
INTERFACE BOOL g_bNonBlockingSeek;
INTERFACE BOOL g_bIsTSRadioOnly ;
INTERFACE EN_VDPLAYER_VIDEO_TYPE g_enVDPlayerVideoType;

#if (SUPPERTED_ADVERTISEMENT_MODE)
INTERFACE U32 g_u32TraceTimer0, g_u32TraceTimer1;
#define MM_TRACE() printf("(%s:%d)[%d/%d]\n", __FUNCTION__, __LINE__, msAPI_Timer_GetTime0()-g_u32TraceTimer0, msAPI_Timer_GetTime0()-g_u32TraceTimer1); g_u32TraceTimer1 = msAPI_Timer_GetTime0();
#endif

//-------------------------------------------------------------------------------------------------
// Extern Functions
///-------------------------------------------------------------------------------------------------
INTERFACE void MApp_VDPlayer_ShowTSSubtitle(BOOLEAN bEnable);
INTERFACE BOOLEAN MApp_VDPlayer_SetSubtitleShow(EN_SUBTITLE_STATE_COMMAND setting);
INTERFACE void MApp_VDPlayer_GetSubtitleSettings( U8 *, U8 *);
INTERFACE U32 MApp_VDPlayer_GetSubtitleInfo(EN_SUBTITLE_INFO eInfo);
INTERFACE void msAPI_VDPlayer_SubtitlePushQueue(EN_VDP_CODECID sbtype, U32 StarAddr, U32 size , U32 PTSstart  , U32 PTSend  );

INTERFACE BOOLEAN MApp_VDPlayer_SetSubtitleTrackID(U8 u8TrackId);
INTERFACE BOOLEAN MApp_VDPlayer_GetAliveTextSubtitleTag(U32 u32Time, U8* pu8AliveSubtitleNum, MPlayer_Subtitle_Tag *pAliveSubtitles, BOOLEAN bSubtitleShownFLG);
INTERFACE void MApp_VDPlayer_RefreshTextSubtitleTag(U32 u32Time);
INTERFACE U16 MApp_VDPlayer_GetTextSubtitleTag(MPlayer_Subtitle_Tag *pTag, U32 u32Time);
INTERFACE void MApp_VDPlayer_TextSubtitleInit(void);
INTERFACE BOOLEAN MApp_VDPlayer_IsTextSubtitle(void);

INTERFACE BOOLEAN MApp_VDPlayer_GetIntSubtitleSettings(S8 setting, S8 *settingVal);
INTERFACE BOOLEAN MApp_VDPlayer_SetIntSubtitleSettings(S8 setting, S8 settingVal);
INTERFACE BOOL MApp_VDPlayer_SubtitleTimeShift(BOOL bDirection, U16 u16TimeShift);

#if ENABLE_DRM
//INTERFACE void MApp_VDPlayer_OperateDRMData(EN_DRM_OP_MODE eMode, VDplayerDRMInfo *pDRM_info);
INTERFACE BOOLEAN MApp_VDPlayer_CheckAndGenDRMData(void);
INTERFACE BOOLEAN MApp_VDPlayer_CheckDRMActivationFile(void);
INTERFACE BOOLEAN MApp_VDPlayer_Deactivate(void);
INTERFACE BOOLEAN MApp_VDPlayer_LoadVISUALDRMMemory(void);
INTERFACE BOOLEAN MApp_VDPlayer_SaveVISUALDRMMemory(void);
//INTERFACE BOOLEAN MApp_VDPlayer_CheckDRMActivationFile(void);
#endif

INTERFACE BOOLEAN MApp_VDPlayer_GetDRMRegistrationCode(U32 drmCodeAddr);
INTERFACE BOOLEAN MApp_VDPlayer_GetDRMDeactivationCode(U32 drmCodeAddr);
INTERFACE BOOLEAN MApp_VDPlayer_CheckDRMAutuorization(void);
INTERFACE BOOLEAN MApp_VDPlayer_QueryDRMRentalStatus(BOOLEAN *isRental,
                                        U8 *useLimit, U8 *useCount);
INTERFACE BOOLEAN MApp_VDPlayer_Test_GetDRMRegistrationCode(void);
INTERFACE BOOLEAN MApp_VDPlayer_Test_ClearDRMMemory(void);
INTERFACE BOOLEAN MApp_VDPlayer_Test_DumpDRMMemory(void);

INTERFACE BOOLEAN MApp_VDPlayer_GetDRMRegistrationCode_Demo(U32 drmCodeAddr);
INTERFACE BOOLEAN MApp_VDPlayer_ClearDRMMemory_Demo(void);
INTERFACE BOOLEAN MApp_VDPlayer_ClearDRMMemory(void);
INTERFACE BOOLEAN MApp_VDPlayer_LoadDRMMemory(void);
INTERFACE BOOLEAN MApp_VDPlayer_SaveDRMMemory(void);

INTERFACE BOOLEAN MApp_VDPlayer_WMDRMPD_SavePrivate(U8 *pu8Private, U32 u32Size);
#if ENABLE_WMDRMPD
INTERFACE BOOLEAN MApp_VDPlayer_WMDRMPD_QueryShareMemoryAddr(U32 *u32Addr);
INTERFACE BOOLEAN MApp_VDPlayer_WMDRMPD_IsProtected(void);
INTERFACE BOOLEAN MApp_VDPlayer_WMDRMPD_QueryHeader(U32 *u32Addr, U32 *u32Size);
INTERFACE BOOLEAN MApp_VDPlayer_WMDRMPD_GetLicense(void);
#endif

INTERFACE BOOLEAN MApp_VDPlayer_SetPlayPosition(U32 timeInMs);
INTERFACE BOOLEAN MApp_VDPlayer_SetAudioTrackID(U8 u8TrackId);
#if ENBALE_PARENTALRATING_MM
INTERFACE void MApp_VDPlayer_SetRatingLimitation(U8 u8RatingLimit);
INTERFACE BOOL MApp_VDPlayer_SetRatingCtrl(U16 u16CtrlFlag);
#endif

#if (ENABLE_DIVX_PLUS == 1)
INTERFACE BOOLEAN MApp_VDPlayer_SetTitleID(U8 u8TitleId);
INTERFACE U8 MApp_VDPlayer_GetTitleID(void);
INTERFACE U8 MApp_VDPlayer_GetEditionID(void);
INTERFACE BOOLEAN MApp_VDPlayer_SetEditionID(U8 u8EditionId);
INTERFACE BOOLEAN MApp_VDPlayer_SetChapterID(U8 u8ChapterId);
INTERFACE BOOLEAN MApp_VDPlayer_SetAutoGenChapterID(U8 u8ChapterId);
#endif

INTERFACE void MApp_VDPlayer_MailBoxHandler(void);

INTERFACE EN_RET MApp_VDPlayer_Main (void);
INTERFACE BOOLEAN MApp_VDPlayer_Pause(void);
INTERFACE BOOLEAN MApp_VDPlayer_Resume(void);

INTERFACE void MApp_VDPlayer_Stop(void);
INTERFACE void MApp_VDPlayer_StopAndCloseDisplay(void);
INTERFACE BOOLEAN MApp_VDPlayer_SetCfg(EN_VDPLAYER_CFG eCfg, U32 u32Value);
INTERFACE BOOLEAN MApp_VDPlayer_Init(VIDEO_PLAYER_INPUT_SOURCE_TYPE eInSrcType, VIDEO_PLAYER_PLAYING_TYPE eType, FileEntry *pFileEntry);
INTERFACE BOOLEAN MApp_VDPlayer_Play(void);
INTERFACE BOOLEAN MApp_VDPlayer_SetTrickMode(EN_VDP_PLAY_MODE ePlayMode, EN_VDP_PLAY_SPEED ePlaySpeed);
INTERFACE BOOLEAN MApp_VDPlayer_SetRepeatAB(EN_SET_REPEATAB enAction);
INTERFACE BOOLEAN MApp_VDPlayer_SetStep(void);
INTERFACE void MApp_VDPlayer_GetTrickMode(TRICK_STATUS *param);
INTERFACE U32 MApp_VDPlayer_GetInfo(EN_VDPLAYER_INFO enInfo);
INTERFACE void MApp_VDPlayer_EnableVideoOnly(BOOLEAN bEnable);
INTERFACE BOOLEAN MApp_VDPlayer_SetFileEntry(FileEntry *pEntry);
INTERFACE void MApp_VDPlayer_BeginPreview(void);
INTERFACE void MApp_VDPlayer_StopPreview(void);
INTERFACE BOOLEAN MApp_VDPlayer_IsPreview(void);
INTERFACE void MApp_VDPlayer_SetPreviewWindow(U16 u16X, U16 u16Y, U16 u16Width, U16 u16Height, EN_ASPECT_RATIO_TYPE eAspectRatioType);
INTERFACE BOOLEAN MApp_VDPlayer_BeforeCaptureVideo(void);
INTERFACE BOOLEAN MApp_VDPlayer_AfterCaptureVideo(void);
INTERFACE BOOLEAN MApp_VDPlayer_EnableVideoOutputFlag(BOOLEAN bEnable);
INTERFACE void MApp_VDPlayer_SetCodecTimeout(U32 * u32TimeOut);
INTERFACE void MApp_VDPlayer_SetPlayTimeOut(U32 u32TimeOut);
INTERFACE void MApp_VDPlayer_CodecDbgMsg(BOOL bEnable);
INTERFACE void MApp_VDPlayer_ScaleVideo(VDPLAYER_ZOOM_FACT eZoom);
INTERFACE BOOLEAN MApp_VDPlayer_ShiftVideo(S16 *ps16OffsetX, S16 *ps16OffsetY, U16 u16BoundaryX, U16 u16BoundaryY, VDPLAYER_ZOOM_FACT eZoomFact);
INTERFACE BOOLEAN MApp_VDPlayer_ChangeProgam(U8 u8ProgramIdx);
INTERFACE BOOLEAN MApp_VDPlayer_VideoForceFileEnd(void);

INTERFACE EN_HEADERPARSER_STATUS MApp_VDPlayer_GetInfoAnother(VIDEO_PLAYER_PLAYING_TYPE eType, FileEntry *pFileEntry ,VDplayerFileHeaderInfo *info);//EN_VDPLAYER_INFO enInfo,U8 rflag);
INTERFACE EN_HEADERPARSER_STATUS MApp_VDPlayer_HeaderParser_GetInfo(VIDEO_PLAYER_PLAYING_TYPE eType, FileEntry *pFileEntry ,VDplayerFileHeaderInfo *info);

#if ENABLE_DVD
INTERFACE EN_RET MApp_VDPlayer_DVD_Main(void);
INTERFACE BOOLEAN MApp_VDPlayer_DVD_Init(VIDEO_PLAYER_INPUT_SOURCE_TYPE eInSrcType, VIDEO_PLAYER_PLAYING_TYPE eType, FileEntry *pFileEntry);
INTERFACE BOOLEAN MApp_VDPlayer_DVD_Play(void);
INTERFACE void MApp_VDPlayer_DVD_Stop(void);
INTERFACE U8 MApp_VDPlayer_DVD_Command(enumMPlayerDVDCmdType cmd);
INTERFACE BOOLEAN MApp_VDPlayer_DVD_IsAllowed(enumMPlayerDVDCmdType cmd);
#endif

#ifdef TRITON_DDI
INTERFACE BOOLEAN MApp_VDPlayer_Init_DDI(U32 _itemID, U32 _FileLength);
INTERFACE BOOLEAN MApp_VDPlayer_SetTrickMode_DDI(EMP_TRICK_MODE_PARAM_T *param);
INTERFACE BOOLEAN MApp_VDPlayer_GetTrickMode_DDI(EMP_TRICK_MODE_PARAM_T *param);
INTERFACE BOOLEAN MApp_VDPlayer_SetIntSubtitleSettings_DDI(
                                    EMP_INT_SUBTITLE_SETTINGS_T setting, S8 settingVal);
INTERFACE BOOLEAN MApp_VDPlayer_GetIntSubtitleSettings_DDI(
                                     EMP_INT_SUBTITLE_SETTINGS_T setting, S8 *settingVal);
#endif

INTERFACE void MApp_VDPlayer_UartSwitch(U8 u8Switch);
INTERFACE U32 _MApp_VDPlayer_GetShareMemData(U16 idx_ptr);
INTERFACE void _Mapp_VDPlayer_SetShareMemData(U16 idx_ptr, U32 idx_data);
INTERFACE U8 _MApp_VDPlayer_GetShareMemoryDataByByte(U16 idx_ptr);
INTERFACE void _MApp_VDPlayer_SetShareMemoryDataByByte(U16 idx_ptr,U8 idx_data);
INTERFACE void _MApp_VDPlayer_ClearShareMem(void);

#if (VDPLAYER_CHECK_PREVIEW_ABORT)
INTERFACE BOOLEAN _MApp_VDPlayer_CheckPreviewAbortKey(void);
#endif

#if (VDPLAYER_CHECK_COPROCESSOR_STATUS)
INTERFACE BOOLEAN _Mapp_VDPlayer_CheckCoprocessorStatus(void);
#endif
//INTERFACE void _MApp_VDPlayer_Exit(void);

INTERFACE U32 MApp_RM2Player_GetInfo(EN_VDPLAYER_INFO enInfo);

#if (FBL_ZOOM==1)
INTERFACE void MApp_VDPlayer_ScaleVideo_FBL(VDPLAYER_ZOOM_FACT eZoom);
#endif

#if ENABLE_FBL_ASPECT_RATIO_BY_MVOP
INTERFACE void MApp_VDPlayer_GetMVOPBlackSize(U32 width, U32 Height, U32* p_black_width , U32* p_black_height);
#endif

INTERFACE void MApp_VDPlayer_GetMVOPBlackSizeOnDest(U32 width, U32 Height, U32* p_black_width , U32* p_black_height);

#if DWIN_MOVIE_PREVIEW
INTERFACE void MApp_VDPlayer_DWINMoviePreview(GOP_GwinFBAttr stFbAttr);
INTERFACE void MApp_VDPlayer_PreviewGWIN_Create(GOP_GwinFBAttr* pstFbAttr);
#endif

INTERFACE void MApp_VDPlayer_BeginThumbnail(void);
INTERFACE void MApp_VDPlayer_StopThumbnail(void);
INTERFACE U32 MApp_VDPlayer_Get_Buffer_Info(EN_BUFFER_INFO_INDEX eIndex);
INTERFACE void MApp_VDPlayer_MovieThumbnail_OutputImage(ST_PHOTO_CAPTURE_RECT *stTo, ST_PHOTO_CAPTURE_RECT *stFrom);
INTERFACE void MApp_VDPlayer_MovieThumbnail_DWINCapture(U32 * pu32dwin_addr);
INTERFACE bool MApp_VDPlayer_MovieThumbnail_SetMVOP(void);

#if ENABLE_DRM
INTERFACE U32 MApp_VDPlayer_GetDRMErrCode(void);
INTERFACE stDRMinfo MApp_VDPlayer_GetDRMInfo(void);
#endif

#if DYNSCALING
INTERFACE void MApp_VDPlayer_SetVirtualBox(XC_SETWIN_INFO* pstXC_SetWin_Info, MS_WINDOW_TYPE *ptSrcWin, MS_WINDOW_TYPE *ptDstWin);
#endif

INTERFACE void MApp_VDPlayer_SetQuarterPixel(XC_SETWIN_INFO* pstXC_SetWin_Info);

#if SEAMLESS_PLAYING_ENABLE
INTERFACE void MApp_VDPlayer_EnableSeamless(BOOL bEnableSeamless);
INTERFACE BOOL MApp_VDPlayer_GetSeamlessMode(void);
#endif

INTERFACE BOOLEAN MApp_VDPlayer_DeBlocking(BOOLEAN bEnable);
INTERFACE BOOLEAN MApp_VDPlayer_QuarterPixel(BOOLEAN bEnable);

#if (SUPPERTED_SEAMLESS_SMOTH)
void MApp_VDPlayer_SetSeamlessSmoth(BOOLEAN bEnable);
#endif

void MApp_VDPlayer_LoadBinToCrop(void);

INTERFACE BOOL MApp_VDPlayer_SetStreamMode(BOOL bMovieStreamMode);

#if ENABLE_HK_MM
INTERFACE BOOLEAN MApp_VDPlayer_MediaCodec_Initialize(void);
INTERFACE BOOLEAN MApp_VDPlayer_MediaCodec_Finalize(void);
INTERFACE BOOLEAN MApp_VDPlayer_MediaCodec_IsReady(void);
#endif

#if ENABLE_PROBE_MOVIE_HEADER
INTERFACE void MApp_VDPlayer_BeginProbeHeaderOnly(void);
INTERFACE void MApp_VDPlayer_StopProbeHeaderOnly(void);
#endif

INTERFACE void MApp_VDPlayer_TS_SubtitleErase(void);
INTERFACE void MApp_VDPlayer_SubtitleDraw(void);

INTERFACE BOOLEAN MApp_VDPlayer_SetVideoSyncDelayMsTime(U32 u32VideoSyncDelayMsTime);
INTERFACE U32 MApp_VDPlayer_GetVideoSyncDelayMsTime(void);

INTERFACE BOOLEAN MApp_VDPlayer_GetMovieAudioCodecSupported(void);
INTERFACE U32 MApp_VDPlayer_GetAudioLanguageByTrackIndex(U16 u16AudioTrack);
INTERFACE U32 MApp_VDPlayer_GetInternalSubtitleLanguageByTrackIndex(U16 u16SubtitleTrack);

INTERFACE BOOLEAN MApp_VDPlayer_SetSuspendInternalSubtitle2Queue(BOOLEAN bSuspend);



#if (ENABLE_PIP)
INTERFACE BOOLEAN MAPP_VDPlayer_SetPIPDisplayWindow(SCALER_WIN eWindow, MS_WINDOW_TYPE *pstDispWin);
#endif

INTERFACE EN_VDPLAYER_FAIL_STATUS MApp_VDPlayer_CheckFailStatus(void);

#undef INTERFACE

#endif // _MAPP_VIDEOPLAYER_H

