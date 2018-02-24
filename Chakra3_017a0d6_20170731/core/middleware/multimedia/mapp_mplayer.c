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
/// @file MApp_MPlayer.c
/// @brief Media player kernel
/// @author MStar Semiconductor Inc.
///
/// Media player kernel provide a simple interface to let users implement
/// media player on MStar chip.
///
///////////////////////////////////////////////////////////////////////////////

#define MAPP_MPLAYER_C

#include <stdio.h>
#include <string.h>
#include "ctype.h"
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"

#include "default_option_define.h"
#include "SysInit.h"
#include "drvCPU.h"
#include "MApp_Exit.h"
#include "sysinfo.h"
#include "GPIO.h"

// XC related include files
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"

//Mass Storage ========================
//#include "msAPI_FCtrl.h"
#include "msAPI_FS_SysInfo.h"
#include "MApp_MassStorage.h"
#include "MApp_FileBrowser.h"
//=====================================
#include "msAPI_Memory.h"
#include "msAPI_MIU.h"
#include "msAPI_Timer.h"
#include "apiGOP.h"
//#include "msAPI_MPEG2.h"
#include "msAPI_MPEG_Subtitle.h"
#include "msAPI_APEngine.h"
#include "msAPI_FSCommon.h"
//#include "msAPI_MPEG4.h"
//#include "msAPI_VideoPlayer.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "apiXC_Sys.h"
#include "IOUtil.h"
#include "msAPI_audio.h"
#include "msAPI_Flash.h"
#include "msAPI_DrvInit.h"
#include "msAPI_MailBox.h"

#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalVar.h"
//#include "MApp_UiMenuStr.h"

#if (ENABLE_DMP)
#include "mapp_mplayer.h"
#include "mapp_music.h"
#include "msAPI_DataStreamIO.h"
#if (ENABLE_WMA)
#include "mapp_wma.h"
#endif

#include "msAPI_CPU.h"
#include "msAPI_MMap.h"

#include "mapp_photo.h"
#include "mapp_photo_display.h"

#include "drvPQ.h"

#define ENABLE_MOVIE_PREVIEW    1

#include "mapp_videoplayer.h"
#include "mapp_txt.h"
#include "mapp_gb2unicode.h"
#include "mapp_big52unicode.h"
#include "MApp_CharTable.h"
#include "MApp_Audio.h"
#include "MApp_Logo.h"
#include "MApp_SaveData.h"
#include "MApp_InputSource.h"
#include "MApp_XC_PQ.h"

#include "mapp_buffermanage.h"

#if (ENABLE_SUBTITLE_DMP)
#include "mapp_mplayer_subtitle.h"
#endif

#if ENABLE_WMDRMPD
#include "mapp_wmdrmpd.h"
#endif

#if 0//ndef ZUI
#include "MApp_UiMediaPlayer.h"
#else
#include "MApp_DMP_Main.h"
#include "FSUtil.h"
//#include "MApp_ZUI_ACTmediaplayer.h"
extern BOOLEAN MApp_UiMediaPlayer_Notify(enumMPlayerNotifyType eNotify, void *pInfo);
extern BOOLEAN MApp_UiMediaPlayer_IsSubtitleEnabled(void);
extern void MApp_DMP_GetZUIFbAttr(GOP_GwinFBAttr *pFbAttr);
#endif
#ifdef ENABLE_PTP
#include "MApp_UiMenuStr1.h"
#include "MApp_PTP.h"
#include "msAPI_PTP.h"
#endif
#if ENABLE_MPLAYER_PLUGIN
#include "MApp_APEngine.h"
#endif

#if RANDOM_PLAY
#include <stdlib.h>
#endif

//panel module
#include "Panel.h"
#include "apiPNL.h"

#if ((OBA2 == 1) && (ENABLE_BABAO_PLAYER == ENABLE))
#include "msAPI_Nplayer.h"
#endif

#if (ENABLE_3D_PROCESS)
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#if (ENABLE_MFC_6M20 || ENABLE_MFC_6M30)
#include "ZUI_exefunc.h"
#endif
#endif

//*****************************************************************************
//              Definitions
//*****************************************************************************
//Black(30m) , Red(31m) , GREEN(32m) , YELLOW(33m) , BLUE(34m) , MAGENTA(35m) , CYAN(36m) , WHITE(37m)
#define MPLAYER_ERROR(format,args...)  printf("\033[15;31m"format"\033[0m",##args)
#define MPLAYER_DBG(x)                  //x
#define SUBTITLE_DBG(x)                 //x

#if (ENABLE_MPLAYER_AUDIO_CAPTURE || ENABLE_MPLAYER_VIDEO_CAPTURE)
#define CAPTURE_DBG(x)                  //x
#define CAPTURE_PFM(x)                  //x
#define CAPTURE_ERR(x)                  x

#define CAPTURE_USB_FREESPACE_THRESHOLD 1 // KB
#endif

#define EXT_FILENAME_SIZE               3
#define NUM_OF_MAX_FILE_DEPTH           (NUM_OF_MAX_DIRECTORY_DEPTH+1)

#define VIDEO_SHIFT_BOUNDARY_X          8
#define VIDEO_SHIFT_BOUNDARY_Y          8

#define SUBTITLE_LYRIC_LONG_FILENAME_SIZE   256
#define LYRIC_MAX_SIZE                      100//76
#define FILE_OP_NAME_LEN                    512
#define FILE_OPERATION_BUFFER               ((MAD_JPEG_INTERBUFF_MEMORY_TYPE & MIU1) ? (MAD_JPEG_INTERBUFF_ADR | MIU_INTERVAL) : (MAD_JPEG_INTERBUFF_ADR))//MAD_JPEG_DISPLAY_ADR

#define DRIVE_IS_VALID(dev, devAddr, lun, partition)                        \
    ((m_MPlayerDeviceStatus[dev].u16LunValid & (1<<lun)) &&                 \
     (m_MPlayerDeviceStatus[dev].u16PartitionValid[lun] & (1<<partition)))

#ifndef U64
#define U64 MS_U64
#endif
/*************************************************************************************************************/

#if ENABLE_MPLAYER_PHOTO
    #define IS_JPG_FILE(ext)    _MApp_IsMedia_File_ByExtName(E_MPLAYER_SUBTYPE_JPG, ext)
  #if ENABLE_BMP
    #define IS_BMP_FILE(ext)    _MApp_IsMedia_File_ByExtName(E_MPLAYER_SUBTYPE_BMP, ext)
  #else
    #define IS_BMP_FILE(ext)    FALSE
  #endif
  #if ENABLE_PNG
    #define IS_PNG_FILE(ext)    _MApp_IsMedia_File_ByExtName(E_MPLAYER_SUBTYPE_PNG, ext)
  #else
    #define IS_PNG_FILE(ext)    FALSE
  #endif
  #if ENABLE_TIFF
    #define IS_TIFF_FILE(ext)   _MApp_IsMedia_File_ByExtName(E_MPLAYER_SUBTYPE_TIFF, ext)
  #else
    #define IS_TIFF_FILE(ext)   FALSE
  #endif
  #if ENABLE_GIF
    #define IS_GIF_FILE(ext)    _MApp_IsMedia_File_ByExtName(E_MPLAYER_SUBTYPE_GIF, ext)
  #else
    #define IS_GIF_FILE(ext)    FALSE
  #endif

#if(CHIP_FAMILY_TYPE == CHIP_FAMILY_A6)
    #define IS_PHOTO_FILE(ext)  (IS_JPG_FILE(ext))
#else
    #define IS_PHOTO_FILE(ext)  (IS_JPG_FILE(ext) || IS_BMP_FILE(ext) || IS_PNG_FILE(ext) || IS_TIFF_FILE(ext) || IS_GIF_FILE(ext))
#endif
#endif  // #if ENABLE_MPLAYER_PHOTO

/*************************************************************************************************************/

#if ENABLE_MPLAYER_MUSIC
    #define IS_MP3_FILE(ext)    _MApp_IsMedia_File_ByExtName(E_MPLAYER_SUBTYPE_MP3, ext)

  #if (ENABLE_FLAC)
    #define IS_FLAC_FILE(ext)   _MApp_IsMedia_File_ByExtName(E_MPLAYER_SUBTYPE_FLAC, ext)
  #else
    #define IS_FLAC_FILE(ext)   FALSE
  #endif
  #if (ENABLE_AC3)
    #define IS_AC3_FILE(ext)   _MApp_IsMedia_File_ByExtName(E_MPLAYER_SUBTYPE_AC3, ext)
  #else
    #define IS_AC3_FILE(ext)   FALSE
  #endif
  #if (ENABLE_AAC)
    #define IS_AAC_FILE(ext)    _MApp_IsMedia_File_ByExtName(E_MPLAYER_SUBTYPE_AAC, ext)
  #else
    #define IS_AAC_FILE(ext)    FALSE
  #endif

  #if (ENABLE_WAV)
    #define IS_WAV_FILE(ext)    _MApp_IsMedia_File_ByExtName(E_MPLAYER_SUBTYPE_WAV, ext)
  #else
    #define IS_WAV_FILE(ext)    FALSE
  #endif

  #if (ENABLE_WMA)
    #define IS_WMA_FILE(ext)    _MApp_IsMedia_File_ByExtName(E_MPLAYER_SUBTYPE_WMA, ext)
  #else
    #define IS_WMA_FILE(ext)    FALSE
  #endif

  #if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
    #define IS_LOAS_FILE(ext)   _MApp_IsMedia_File_ByExtName(E_MPLAYER_SUBTYPE_LOAS, ext)
  #else
    #define IS_LOAS_FILE(ext)   FALSE
  #endif

#if (ENABLE_OGG)
#define IS_OGG_FILE(ext)    _MApp_IsMedia_File_ByExtName(E_MPLAYER_SUBTYPE_OGG, ext)
#else
#define IS_OGG_FILE(ext) FALSE
#endif

#if (ENABLE_AMR)
#define IS_AMR_FILE(ext)    _MApp_IsMedia_File_ByExtName(E_MPLAYER_SUBTYPE_AMR, ext)
#define IS_AWB_FILE(ext)    _MApp_IsMedia_File_ByExtName(E_MPLAYER_SUBTYPE_AWB, ext)
#else
#define IS_AMR_FILE(ext)    FALSE
#define IS_AWB_FILE(ext)    FALSE
#endif

#if(CHIP_FAMILY_TYPE == CHIP_FAMILY_A6)
#define IS_MUSIC_FILE(ext)  (IS_MP3_FILE(ext))
#else
#define IS_MUSIC_FILE(ext)  (IS_MP3_FILE(ext) || IS_AAC_FILE(ext) || IS_WAV_FILE(ext) || IS_WMA_FILE(ext) || IS_LOAS_FILE(ext) || IS_OGG_FILE(ext) || IS_AMR_FILE(ext) || IS_AWB_FILE(ext) || IS_FLAC_FILE(ext) || IS_AC3_FILE(ext))
#endif
#endif  // #if ENABLE_MPLAYER_MUSIC

/*************************************************************************************************************/

#if ENABLE_MPLAYER_MOVIE
    #define IS_MPEG2_FILE(ext)  _MApp_IsMedia_File_ByExtName(E_MPLAYER_SUBTYPE_MPEG, ext)
    #define IS_MPEG4_FILE(ext)  _MApp_IsMedia_File_ByExtName(E_MPLAYER_SUBTYPE_MPEG4, ext)
    #define IS_TS_FILE(ext)     _MApp_IsMedia_File_ByExtName(E_MPLAYER_SUBTYPE_TS, ext)
    #define IS_RM_FILE(ext)     _MApp_IsMedia_File_ByExtName(E_MPLAYER_SUBTYPE_RM, ext)
  #if (ENABLE_WMV)
    #define IS_WMV_FILE(ext)    _MApp_IsMedia_File_ByExtName(E_MPLAYER_SUBTYPE_WMV, ext)
  #else
    #define IS_WMV_FILE(ext)    FALSE
  #endif
  #if (ENABLE_DVD)
    #define IS_DVD_FILE(ext)    _MApp_IsMedia_File_ByExtName(E_MPLAYER_SUBTYPE_DVD, ext)
    #define IS_IFO_FILE(ext)    _MApp_IsMedia_File_ByExtName(E_MPLAYER_SUBTYPE_IFO, ext)
  #else
    #define IS_DVD_FILE(ext)    FALSE
    #define IS_IFO_FILE(ext)    FALSE
  #endif
    #define IS_MOVIE_FILE(ext)  (IS_MPEG2_FILE(ext) || IS_MPEG4_FILE(ext) || IS_TS_FILE(ext) || IS_RM_FILE(ext) || IS_WMV_FILE(ext) || IS_DVD_FILE(ext))
#endif  // #if ENABLE_MPLAYER_MOVIE

/*************************************************************************************************************/

#if ENABLE_MPLAYER_TEXT
#define IS_TXT_FILE(ext)    _MApp_IsMedia_File_ByExtName(E_MPLAYER_SUBTYPE_TEXT, ext)
#endif  // #if ENABLE_MPLAYER_TEXT
#if ENABLE_MPLAYER_PLUGIN
#define IS_NES_FILE(ext)    _MApp_IsMedia_File_ByExtName(E_MPLAYER_SUBTYPE_PLG, ext)
#endif //#if ENABLE_MPLAYER_PLUGIN

//#define PLAY_LIST_NUM_PER_WIN   (4096 / sizeof(MPlayerPlayListInfo))

#define PLAY_LIST_PATH(i, j)    (pstPlayListInfo[(i)].u16PlayListPath[j])
#define PLAY_LIST_DRIVE(i)      (pstPlayListInfo[(i)].u16Drive)
#define PLAY_LIST(i)            (pstPlayListInfo[(i)])
#define PLAY_LIST_FILE_ENTRY(i) (pstPlayListInfo[(i)].fileEntry)
#define PLAY_LIST_EXT_NAME(i)   (pstPlayListInfo[(i)].u8ExtName)
#define PLAY_LIST_ATTRIBUTE(i)  (pstPlayListInfo[(i)].eAttribute)

#if ENABLE_SUBTITLE_COPY_AND_DELETE
#define PLAY_LIST_EXTFILESTOTALSIZE(i)  (pstPlayListInfo[(i)].u32ExtFilesTotalSize)
#endif

static BOOLEAN m_bNotifyRtn;
BOOLEAN bPauseToNextFlag=FALSE;
#define NOTIFY(notify, info)                            \
    MPLAYER_DBG(printf("NOTIFY: %bx %lx\n", notify, m_u64NotifyEnableFlags));   \
    if(m_u64NotifyEnableFlags & ((U64)1<<notify))       \
    {                                                   \
        m_bNotifyRtn = MApp_UiMediaPlayer_Notify(notify, info);        \
    }

#ifndef min
#define min(x, y) (((x) < (y)) ? (x) : (y))
#endif

#define ATTRIB_DIRECTORY ENTRY_ATTRIB_DIRECTORY //<= very strange....

#if (ENABLE_MOVIE_PREVIEW_ALL_AND_1ST_FRAME && ENABLE_MOVIE_PREVIEW_1ST_FRAME)
#error "Cannot set both flags to be 1!"
#endif

#if (ENABLE_MOVIE_PREVIEW_ALL_AND_1ST_FRAME && MOVIE_REPEAT_PREVIEW)
#error "Cannot set both flags to be 1!"
#endif

#define E_VDPLAYER_SUBTITLE_NUM         E_MPLAYER_SUBTITLE_NUM
#define MAX_DEDICATED_FILE_EXT_NUM      E_VDPLAYER_SUBTITLE_NUM

#if (defined(MPLAYER_MUSIC_FILE_BUFFER_LEN) && (MPLAYER_MUSIC_FILE_BUFFER_LEN > 0))
#define STORE_SUBTITLE_ENTRY_TO_SUBTITLE_BUFFER     ( 0 &&(ENABLE_MPLAYER_MOVIE && ENABLE_SUBTITLE_DMP))
#else
#define STORE_SUBTITLE_ENTRY_TO_SUBTITLE_BUFFER     1
#endif

#if STORE_SUBTITLE_ENTRY_TO_SUBTITLE_BUFFER
#define MPLAYER_SUBTITLE_FILE_BUFFER_ADR    ((MPLAYER_MUSIC_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_MUSIC_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_MUSIC_FILE_BUFFER_ADR))
#define MPLAYER_SUBTITLE_FILE_BUFFER_LEN    (MPLAYER_MUSIC_FILE_BUFFER_LEN)
#endif

#if (ENABLE_4K2K)

#if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA))
#define GE_COORDINATE_LIMITATION    2048
#else
#define GE_COORDINATE_LIMITATION    4096
#endif

#define CHECK_GE_BOUNDARY(x)        MIN(x, GE_COORDINATE_LIMITATION)
#endif

#if (ENABLE_MPLAYER_AUDIO_CAPTURE)
#define CAPTURE_AUDIO_WAV_HEADER_LEN        44 //In WAV spec, the header length is 44
#define CAPTURE_AUDIO_WAV_CHANNELS          2
#define CAPTURE_AUDIO_WAV_SAMPLE_RATE       48000
#define CAPTURE_AUDIO_WAV_BITS_PER_SAMPLE   16

#define CAPTURE_AUDIO_READ_LEN              0x10000 // User can adjust it, but we suggust that this value is 64k
#define CAPTURE_AUDIO_MAX_READ_FACTOR       8       // Dynamic read size, max size=CAPTURE_AUDIO_READ_LEN*CAPTURE_AUDIO_MAX_READ_FACTOR
#endif

//*****************************************************************************
//              enums
//*****************************************************************************
typedef enum
{
    E_MPLAYER_KNL_FLG_NULL                  = 0,        //
    E_MPLAYER_KNL_FLG_COPY_FILE_SELECTED    = BIT0,    // Copy file is set.
    E_MPLAYER_KNL_FLG_COPYING               = BIT1,    // Copying the file.
    E_MPLAYER_KNL_FLG_FILE_OP_DIFF_DRIVE    = BIT2,    // The drive is different when process file operations.
    E_MPLAYER_KNL_FLG_INITIALIZED           = BIT3,   // Initialized media player.
    E_MPLAYER_KNL_FLG_DEVICE_INITIALIZED    = BIT4,   // Initialized device.
    E_MPLAYER_KNL_FLG_THUMBNAIL_MODE        = BIT5,   // thumbnail mode
    E_MPLAYER_KNL_FLG_THUMBNAIL_INIT        = BIT6,    // Initialize one thumbnail file. //movie thumbnail srate 1
#if ENABLE_MPLAYER_PHOTO
    E_MPLAYER_KNL_FLG_THUMBNAIL             = BIT7,    // need to do thumbnail
#endif  // #if ENABLE_MPLAYER_PHOTO
    E_MPLAYER_KNL_FLG_INTERNAL_SUBTITLE_INIT_DONE   = BIT8,//  Whether internal subtitle init done or not.
#if 1//def ZUI
    E_MPLAYER_KNL_FLG_DECODE_N_THUMBNAIL    = BIT9,   // To decode Nth thumbnail
    E_MPLAYER_KNL_FLG_THUMBNAIL_DECODE      = BIT10,  // movie thumbnail srate 2
    E_MPLAYER_KNL_FLG_THUMBNAIL_DONE        = BIT11,  // movie thumbnail srate 3
#endif //#ifdef ZUI
    E_MPLAYER_KNL_FLG_COPY_PLAY             = BIT12,    // Turn on file operation.
    E_MPLAYER_KNL_FLG_COPY_INIT             = BIT13,    // Init file operation.
    E_MPLAYER_KNL_FLG_DELETE_PLAY           = BIT14,    // Turn on file delete operation.
    E_MPLAYER_KNL_FLG_DELETE_INIT           = BIT15,    // Init file delete operation.
    E_MPLAYER_KNL_FLG_DELETING              = BIT16,    // Deleting the file.

} enumMPlayerKnlFlags;

typedef enum
{
    E_MPLAYER_KNL_FLG1_NULL                 = 0,        //
    E_MPLAYER_KNL_FLG1_FILE_INIT            = BIT0,   // Need to do some initialization for media file.
    E_MPLAYER_KNL_FLG1_RECORDING_MUSIC      = BIT1,    // Recording music
#if ENABLE_MPLAYER_MOVIE
    E_MPLAYER_KNL_FLG1_SUBTITLE_ENABLE      = BIT2,    // subtitle is enabled by users.
    E_MPLAYER_KNL_FLG1_SUBTITLE_VALID       = BIT3,    // subtitle is valid.
#endif  // #if ENABLE_MPLAYER_MOVIE
#if ENABLE_MPLAYER_MUSIC
    E_MPLAYER_KNL_FLG1_LYRIC_ENABLE         = BIT4,    // lyric is enabled by users.
    E_MPLAYER_KNL_FLG1_LYRIC_VALID          = BIT5,    // lyric is valid.
#endif  // #if ENABLE_MPLAYER_MUSIC
#if ENABLE_MPLAYER_PHOTO
    E_MPLAYER_KNL_FLG1_PHOTO_PLAY           = BIT6,    // Photo is playing.
#endif  // #if ENABLE_MPLAYER_PHOTO
#if ENABLE_MPLAYER_MUSIC
    E_MPLAYER_KNL_FLG1_MUSIC_PLAY           = BIT7,    // Music is playing.
#endif  // #if ENABLE_MPLAYER_MUSIC
#if ENABLE_MPLAYER_MOVIE
    E_MPLAYER_KNL_FLG1_MOVIE_PLAY           = BIT8,    // Movie is playing.
#endif  // #if ENABLE_MPLAYER_MOVIE
#if ENABLE_MPLAYER_TEXT
    E_MPLAYER_KNL_FLG1_TEXT_PLAY            = BIT9,   // Text is playing.
#endif  // #if ENABLE_MPLAYER_TEXT
#if ENABLE_MPLAYER_MOVIE
    E_MPLAYER_KNL_FLG1_SUBTITLE_SHOWN       = BIT10,   // Has shown the subtitle.
    E_MPLAYER_KNL_FLG1_PREDECODE_OK         = BIT11,   // Specify it is a valid movie.
    E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL    = BIT12,   // Subtitle is external.
    E_MPLAYER_KNL_FLG1_HIDE_SUBTITLE        = BIT13,   // Hide or show subtitle.
#endif  // #if ENABLE_MPLAYER_MOVIE
#if ENABLE_MPLAYER_PLUGIN
    E_MPLAYER_KNL_FLG1_PLUGIN_PLAY          = BIT14,   // Plug-in APP is playing
#endif //#if ENABLE_MPLAYER_PLUGIN
#if ENABLE_DRM
    E_MPLAYER_KNL_FLG1_FILE_WAIT_DRM_UI     = BIT15,
    E_MPLAYER_KNL_FLG1_MOVIE_INIT_OK        = BIT16,
#endif
    E_MPLAYER_KNL_FLG1_SUBTITLE_TEXT        = BIT17,   // Subtitle is text.
} enumMPlayerKnlFlags1;

typedef enum
{
    STATE_MPLAYER_INIT,
    STATE_MPLAYER_WAIT,
    STATE_MPLAYER_EXIT_TO_MENU,
    STATE_MPLAYER_STANDBY,
} enumMplayerStateMachineState;

typedef enum
{
    E_MPLAYER_STATE_NONE                 = 0,
    E_MPLAYER_PHOTO_STATE_DISPLAY        = BIT0,
    E_MPLAYER_PHOTO_STATE_PLAY_END       = BIT1,
    E_MPLAYER_PHOTO_STATE_PAUSE          = BIT2,
    E_MPLAYER_PHOTO_STATE_DECODE_PAUSE   = BIT3,
    E_MPLAYER_PHOTO_STATE_ERROR_PENDING  = BIT4,

    E_MPLAYER_MUSIC_STATE_ALL_ERROR      = BIT8,
    E_MPLAYER_MUSIC_STATE_PLAY_END       = BIT9,
    E_MPLAYER_MUSIC_STATE_ERROR_PENDING  = BIT10,

    E_MPLAYER_MOVIE_STATE_ALL_ERROR      = BIT16,
    E_MPLAYER_MOVIE_STATE_PLAY_END       = BIT17,
    E_MPLAYER_MOVIE_STATE_ERROR_PENDING  = BIT18,

    E_MPLAYER_TEXT_STATE_ERROR_PENDING   = BIT24,
} enumMediaPlayingStatus;

typedef enum
{
    E_MPLAYER_PLAY_DIRECTION_NEXT,
    E_MPLAYER_PLAY_DIRECTION_PREV,
} EN_MPLAYER_PLAY_DIRECTION;

typedef enum
{
    E_MPLAYER_PHOTO_WAIT = 0,
    E_MPLAYER_PHOTO_VALID,
    E_MPLAYER_PHOTO_INVALID,
} EN_PHOTO_VALID_OR_NOT;

typedef enum
{
    E_MPLAYER_FOREGROUND_PLAYER           = 0,
    E_MPLAYER_BACKGROUND_PLAYER,
    E_MPLAYER_MAX_CONCURRENT_PLAYER_NUM,
} enumMPlayerIdx;

#if ENABLE_USB_DETECT_STEP_BY_STEP
typedef enum
{
    STATE_USB_DETECT_START          = 0,
    STATE_USB_DETECT_GET_DEVICE_AND_DRIVE,
    STATE_USB_DETECT_CHECK_PORT_CHANGED,
    STATE_USB_DETECT_CURRENT_PORT_CHANGED_PROCESS_INIT,
    STATE_USB_DETECT_CURRENT_PORT_CHANGED_PROCESS_DONE,
    STATE_USB_DETECT_ANOTHER_PORT_CHANGED_PROCESS_INIT,
    STATE_USB_DETECT_ANOTHER_PORT_CHANGED_PROCESS_DONE,
} enumUSBDetectState;
#endif

#if ENABLE_MPLAYER_PHOTO
#define PHOTO_PLAYER E_MPLAYER_FOREGROUND_PLAYER
#endif //#if ENABLE_MPLAYER_PHOTO

#if ENABLE_MPLAYER_MUSIC
#define MUSIC_PLAYER E_MPLAYER_BACKGROUND_PLAYER
#endif //#if ENABLE_MPLAYER_MUSIC

#if ENABLE_MPLAYER_MOVIE
#define MOVIE_PLAYER E_MPLAYER_FOREGROUND_PLAYER
#endif //#if ENABLE_MPLAYER_MOVIE

#if ENABLE_MPLAYER_TEXT
#define TEXT_PLAYER E_MPLAYER_FOREGROUND_PLAYER
#endif //#if ENABLE_MPLAYER_TEXT

#if ENABLE_EMBEDDED_PHOTO_DISPLAY
#define INVALID_FILE_INDEX 0xFFFF
#endif

#if RANDOM_PLAY
#define INVALID_RANDOM_NUMBER 0xFFFF
#endif
//*****************************************************************************
//              Data structure
//*****************************************************************************
/// Specify the file operation information
typedef struct // max 4k bytes
{
    BOOLEAN bCopySrcSelected;

    U8 u8CopySrcDeviceIndex;
    U8 u8CopySrcDriveIndex;

    U8 u8CopySrcDeviceNo;
    S8 ps8CopySrcLongName[FILE_INFO_LONG_FILENAME_SIZE]; // longest name for NTFS
    U8 u8ExtFileName[3+1];                   /// Short extension file name

    FileEntry stCopySrcEntry;
} stFileOpInfo;

#define MPLAYER_PLAY_LIST_INFO_EXTNAME_SIZE      4
#define MPLAYER_PLAY_LIST_INFO_ATTRIBUTE_SIZE    4

#if OBA2 //os, sizeof(FileEntry)=284
#define MPLAYER_PLAY_LIST_INFO_FILE_ENTRY_SIZE   284
#define MPLAYER_PLAY_LIST_INFO_SIZE_TMP     ((NUM_OF_MAX_DIRECTORY_DEPTH+2)*2+MPLAYER_PLAY_LIST_INFO_FILE_ENTRY_SIZE+MPLAYER_PLAY_LIST_INFO_EXTNAME_SIZE+MPLAYER_PLAY_LIST_INFO_ATTRIBUTE_SIZE)
#else //non-os, sizeof(FileEntry)=40
#define MPLAYER_PLAY_LIST_INFO_FILE_ENTRY_SIZE   40
#if ENABLE_SUBTITLE_COPY_AND_DELETE //4 means U32 u32ExtFilesTotalSize;
#define MPLAYER_PLAY_LIST_INFO_EXT_FILES_TOTAL_SIZE     4
#define MPLAYER_PLAY_LIST_INFO_SIZE_TMP     ((NUM_OF_MAX_DIRECTORY_DEPTH+2)*2+MPLAYER_PLAY_LIST_INFO_FILE_ENTRY_SIZE+MPLAYER_PLAY_LIST_INFO_EXTNAME_SIZE+MPLAYER_PLAY_LIST_INFO_EXT_FILES_TOTAL_SIZE+MPLAYER_PLAY_LIST_INFO_ATTRIBUTE_SIZE)
#else
#define MPLAYER_PLAY_LIST_INFO_SIZE_TMP     ((NUM_OF_MAX_DIRECTORY_DEPTH+2)*2+MPLAYER_PLAY_LIST_INFO_FILE_ENTRY_SIZE+MPLAYER_PLAY_LIST_INFO_EXTNAME_SIZE+MPLAYER_PLAY_LIST_INFO_ATTRIBUTE_SIZE)
#endif
#endif

//note:
//os,   sizeof(MPlayerPlayListInfo) will be 512 byte
//non-os, sizeof(MPlayerPlayListInfo) will be 128 byte
#if (MPLAYER_PLAY_LIST_INFO_SIZE_TMP > 512)
    #error "MPlayerPlayListInfo is too large!"
#elif ((MPLAYER_PLAY_LIST_INFO_SIZE_TMP == 128)||(MPLAYER_PLAY_LIST_INFO_SIZE_TMP == 256)||(MPLAYER_PLAY_LIST_INFO_SIZE_TMP == 512))
    #define MPLAYER_PLAY_LIST_INFO_SIZE     MPLAYER_PLAY_LIST_INFO_SIZE_TMP // 128, 256, 512
    typedef struct
    {
        U16 u16Drive;
        U16 u16PlayListPath[NUM_OF_MAX_DIRECTORY_DEPTH+1];
        FileEntry fileEntry;
        U8 u8ExtName[4];
    } MPlayerPlayListInfo;
#else
    #if (MPLAYER_PLAY_LIST_INFO_SIZE_TMP < 128)
    #define MPLAYER_PLAY_LIST_INFO_SIZE     128
    #elif (MPLAYER_PLAY_LIST_INFO_SIZE_TMP < 256)
    #define MPLAYER_PLAY_LIST_INFO_SIZE     256
    #elif (MPLAYER_PLAY_LIST_INFO_SIZE_TMP < 512)
    #define MPLAYER_PLAY_LIST_INFO_SIZE     512
    #endif
    typedef struct
    {
        U16 u16Drive;
        U16 u16PlayListPath[NUM_OF_MAX_DIRECTORY_DEPTH+1];
        FileEntry fileEntry;
        U8 u8ExtName[4];
    #if ENABLE_SUBTITLE_COPY_AND_DELETE
        U32 u32ExtFilesTotalSize;
    #endif
        enumFileAttribute eAttribute;
        U8 u8Dummy[MPLAYER_PLAY_LIST_INFO_SIZE-MPLAYER_PLAY_LIST_INFO_SIZE_TMP];
    } MPlayerPlayListInfo;
#endif

#if (MPLAYER_PHOTO_PLAYLIST_LEN < NUM_OF_MAX_SELECTED_FILE * MPLAYER_PLAY_LIST_INFO_SIZE)
#error "MPLAYER_PHOTO_PLAYLIST_LEN is too small"
#endif

#if (MPLAYER_MUSIC_PLAYLIST_LEN < NUM_OF_MAX_SELECTED_FILE * MPLAYER_PLAY_LIST_INFO_SIZE)
#error "MPLAYER_MUSIC_PLAYLIST_LEN is too small"
#endif

#if (MPLAYER_MOVIE_PLAYLIST_LEN < NUM_OF_MAX_SELECTED_FILE * MPLAYER_PLAY_LIST_INFO_SIZE)
#error "MPLAYER_MOVIE_PLAYLIST_LEN is too small"
#endif

#if (MPLAYER_TEXT_PLAYLIST_LEN < NUM_OF_MAX_SELECTED_FILE * MPLAYER_PLAY_LIST_INFO_SIZE)
#error "MPLAYER_TEXT_PLAYLIST_LEN is too small"
#endif

typedef struct
{
    enumMPlayerKnlFlags1 eKnlFlag1;

    enumMPlayerMediaType eMediaType;
    enumMPlayerMediaSubType eMediaSubType;
    enumMPlayerPlayMode ePlayMode;
    enumMPlayerRepeatMode eRepeatMode;
#if RANDOM_PLAY
    enumMPlayerRandomMode eRandomMode;
#endif

    U8 u8BrowserHandle;

    U16 u16PlayingIdx;

    U16 u16CurrentDrive;
    FileEntry curPlayingFileEntry;
    U16 u16TotalFileNum;
    U16 u16TotalDirNum;
    U32 u32ErrorDelayTime; //the duration for a displayed error message in milliseconds
    U32 u32ErrorMsgTimer; //the error message display start time in milliseconds
    enumMediaPlayingStatus eMediaPlayingStatus; //the playing status such as error message pending
    EN_MPLAYER_PLAY_DIRECTION eMediaPlayingDirection;
} MPlayerPlayingFileInfo;

#if ENABLE_USB_DETECT_STEP_BY_STEP
typedef struct
{
    U32 u32ValidDevice, u8TotalDriveNum;
    enumMPlayerUSBDeviceStatus eUSBDeviceStatus;
    enumUSBDetectState eCurrentState;
    BOOLEAN bDetectStepByStep;
}MPlayerUSBDetectStruct;
#endif

typedef struct
{
    ST_PHOTO_CAPTURE_RECT stPhotoImgTo, stPhotoImgFrom;
    EN_RET eRet_thumb;
}MPlayerThumbStruct;

typedef struct
{
    U8 au8LangCode[3];
    enumMPlayerLanguage enMPlayerLang;
} ST_MPLAYER_ISO639_LANG;

#if (ENABLE_MPLAYER_AUDIO_CAPTURE)
typedef struct
{
    //WAV header
    U32 u32DataChunkSize;
    U32 u32SampleRate;
    U16 u16Channels;
    U16 u16BitsPerSample;

    U32 u32CurPCMOffset;
    U32 u32PrePCMOffset;
    U8 u8WriteFileHandle;
} MPlayerAudioCapture;
#endif

#if (ENABLE_MPLAYER_VIDEO_CAPTURE)
typedef struct
{
    U32 u32EncodeDstBuffer;    /// The memory which saves the JPEG data
    U8 u8Progress;             /// Encoding Progress
    U8 u8WriteFileHandle;
} MPlayerVideoCapture;
#endif

//*****************************************************************************
//              Global variables
//*****************************************************************************
static MPlayerThumbStruct stThumb;
BOOLEAN bMusicRecording;
extern U8* pMediaStrBuf;

#if REMOVE_DRIVE_SELECT_TO_FILE_LIST
extern BOOLEAN bIsDriveSelected; 
#endif

#if ENABLE_SUBTITLE_DMP
#if ENABLE_INTERNAL_SUBTITLE
extern U32 u32subtitletype;
#if (TS_INTERNAL_SUBTITLE_BMP || TS_INTERNAL_SUBTITLE_PGS)
extern U16 u16CPageID;
extern U16 u16APageID;
#endif
#endif //ENABLE_INTERNAL_SUBTITLE
#endif //ENABLE_SUBTITLE_DMP


#ifdef ENABLE_PTP
static BOOLEAN _MApp_MPlayer_PTP_PlayerInit(enumMPlayerIdx eMPlayerIdx, enumMPlayerMediaType eMediaType, BOOLEAN bPreview);
void _MApp_MPlayer_PTP_Browser_EnumCurDirectory();
enumMPlayerRet MApp_MPlayer_PTP_EnterDirectory(enumMPlayerFileIndexBegin eBegin, U16 u16Idx);
#endif

BOOLEAN g_bOutputMMAliveMessage = FALSE;
BOOLEAN g_b2ndRunPreviewMute = FALSE;

#if ENABLE_LAST_MEMORY==1
#if ENABLE_LAST_MEMORY_STORAGE_SAVE==0
stLastMemoryInfo m_LastMemoryInfo[LAST_MEMORY_FILENUMBER];
U16 m_LastMemoryOrderTbl[LAST_MEMORY_FILENUMBER]; // start from 1,2,3.....
#endif
#if ENABLE_LAST_MEMORY_PLAYTIME_UPDATE==1
U32 m_u32LastMemoryCheckTime;
#endif
U32 m_u32LastMemorySeekPosL;
U32 m_u32LastMemorySeekPosH;
U32 m_u32LastMemorySeekPTS;//ms
U16 m_u16LastMemoryAudioTrack;
U16 m_u16LastMemorySubtitleTrack;
BOOLEAN m_bLastMemorySubtitleShow;

U32 m_u32LastMemoryCurIdx=0xFFFF;
U8 m_u8LastMemoryCheck=FALSE;//no LastMemory check when preview, only normal play will check LastMemory
U8 m_u8LastMemorySearchHit=FALSE;
#endif//#if ENABLE_LAST_MEMORY==1

#if ENABLE_DIVX_PLUS
BOOL g_bChangeFile = FALSE;
U32 g_u32DivxPlusPTS;   // ggg
extern U8 g_u8TitleId;
extern U8 g_u8EditionId;
//extern enumMPlayerMoviePlayMode g_eMoviePlayMode;
#endif
#if ENABLE_DRM
extern BOOLEAN g_bIsResumePlay;
extern BOOLEAN g_bReplay;
#endif
//*****************************************************************************
//              Local variables
//*****************************************************************************
static enumMPlayerKnlFlags m_eMPlayerKnlFlags;
static MPlayerDeviceStatus m_MPlayerDeviceStatus[NUM_OF_SUPPORT_DEVICES];
//static U16 m_u16DeviceConnectStatus;
static U32  m_u32DeviceValidStatus;
static U8 m_u8TotalDriveNum;
static MPlayerDrive m_DriveInfo[NUM_OF_MAX_DRIVE];
static U8 m_u8CurDeviceIdx;
static U16 m_u16CurDriveIdx;
static U32 m_u32DriveStatus;
static U16 m_u16CurDirectory[NUM_OF_MAX_DIRECTORY_DEPTH+1];
#if (ENABLE_MPLAYER_SORT)
static U16 m_u16CurDirectoryPhy[NUM_OF_MAX_DIRECTORY_DEPTH+1];
typedef BOOLEAN (*PF_FILEINFOCMP_LESS)(MPlayerFileInfo* src, MPlayerFileInfo* dst);
#if ENABLE_MPLAYER_SORT_EX
static enumMPlayerFileSortMode m_eFileSortingMode = E_MPLAYER_SORT_NONE;
static enumMPlayerFileSortSubMode m_eFileSortingOrderMode = E_MPLAYER_SORT_INCREMENT_ORDER;
//m_pfFileInfoCmp_Less: True = src < dst.
static PF_FILEINFOCMP_LESS m_pfFileInfoCmp_Less;
#endif //ENABLE_MPLAYER_SORT_EX
#endif
static U16 m_u16DirectoryNum[NUM_OF_MAX_DIRECTORY_DEPTH+1];
static U16 m_u16PathIndex[NUM_OF_MAX_DIRECTORY_DEPTH+1];
static U16 m_u16CurDirectoryDepth;
#if (HIGH_SPEED_BROWSER)
static U16 m_u16BufDirectoryDepth;
static U16 m_u16BufDirectory[NUM_OF_MAX_DIRECTORY_DEPTH+1];
static U16 m_u16BufTotalFileNum;
static U16 m_u16BufDirectoryNum;
static U16 m_u16BufReadLongNameIdx;
#endif
static U16 m_u16CurFileIdx;
static U8 m_u8UserBrowserHandle = INVALID_BROWSER_HANDLE;
static U16 m_u16TotalFileNum;

#if (ENABLE_BGM)
static U16 m_u16TotalMusicFileNum;
static U16 m_u16CurMusicDirectoryNumber;
static U16 m_u16RealMusicFileNum;
static U16 m_u16TotalBGMFileNum;
#if PLAYLIST_BGM
static U16 m_u16BGMSelectedFileNum = 0;
static BOOLEAN m_bBGMPlaylistInit = FALSE;
#endif
#endif

#if STORE_SUBTITLE_ENTRY_TO_SUBTITLE_BUFFER
static U16 m_u16TotalSubtitleFileNum;
#endif
static U16 m_u16CurPage1stFileIdx;
static U16 m_u16TotalPageNum;
static U16 m_u16CurPageIdx;
static U16 m_u16FilesPerPage;
static U16 m_u16SelectedFileNum[E_MPLAYER_TYPE_NUM];

//static U16 m_u16SelectedFileIdx[E_MPLAYER_PLAY_MODE_NUM][NUM_OF_MAX_SELECTED_FILE][NUM_OF_MAX_FILE_DEPTH];
//static U16 m_u16CopyDirectory[NUM_OF_MAX_DIRECTORY_DEPTH];
//static U16 m_u16CopyFileIdx;
//static MPlayerDrive m_CopyFileDrive;
static enumMPlayerMediaType m_eMediaType;
static U8 m_u8CurThumbnailDrawIdx;
#if 1//def ZUI
#define THUMBNAIL_NUM_MAX   32
static U8 m_u8ThumbnailNIdx;
static U8 m_u8ThumbQMax;
static U8 m_au8ThumbQueue[THUMBNAIL_NUM_MAX];
#endif //#ifdef ZUI
static GOP_GwinFBAttr m_thumbnailFbAttr;
EN_RET PreMApp_Jpeg_Main, CurMApp_Jpeg_Main;
static BOOLEAN m_bPlaylistChanged;
#if ENABLE_MPLAYER_PLUGIN
static FileEntry fileEntryPlugin;
#endif
static MPlayerPhotoInfo m_photoInfo;
#if RANDOM_PLAY
static BOOLEAN m_bPlayNext;
static enumMPlayerRandomMode m_eRandomMode[E_MPLAYER_MAX_CONCURRENT_PLAYER_NUM];
static U8 m_au8RandomPlayTable[E_MPLAYER_MAX_CONCURRENT_PLAYER_NUM][(NUM_OF_MAX_FILES_PER_DIRECTORY+7)/8]={{0}};
static U16 m_u16RandomPlaySelectedNum[E_MPLAYER_MAX_CONCURRENT_PLAYER_NUM] = {0};
#endif

#if ENABLE_MPLAYER_MOVIE
#if (ENABLE_MOVIE_PREVIEW_ALL_AND_1ST_FRAME || ENABLE_MOVIE_PREVIEW_1ST_FRAME)
static BOOLEAN bMute=FALSE;
#endif
#endif

U8 code m_au8JPG_ExtFileName[][EXT_FILENAME_SIZE] =
{
    JPG_EXT_FILENAME
};

U8 code m_au8BMP_ExtFileName[][EXT_FILENAME_SIZE] =
{
    BMP_EXT_FILENAME
};

U8 code m_au8PNG_ExtFileName[][EXT_FILENAME_SIZE] =
{
    PNG_EXT_FILENAME
};

U8 code m_au8TIFF_ExtFileName[][EXT_FILENAME_SIZE] =
{
    TIFF_EXT_FILENAME
};

U8 code m_au8GIF_ExtFileName[][EXT_FILENAME_SIZE] =
{
    GIF_EXT_FILENAME
};

U8 code m_au8MPEG_ExtFileName[][EXT_FILENAME_SIZE] =
{
    MPEG_EXT_FILENAME
};

U8 code m_au8TS_ExtFileName[][EXT_FILENAME_SIZE] =
{
    TS_EXT_FILENAME
};

U8 code m_au8RM_ExtFileName[][EXT_FILENAME_SIZE] =
{
    RM_EXT_FILENAME
};

U8 code m_au8MPEG4_ExtFileName[][EXT_FILENAME_SIZE] =
{
    MPEG4_EXT_FILENAME
};

U8 code m_au8WMV_ExtFileName[][EXT_FILENAME_SIZE] =
{
    WMV_EXT_FILENAME
};

U8 code m_au8DVD_ExtFileName[][EXT_FILENAME_SIZE] =
{
    DVD_EXT_FILENAME
};

U8 code m_au8IFO_ExtFileName[][EXT_FILENAME_SIZE] =
{
    IFO_EXT_FILENAME
};

U8 code m_au8MP3_ExtFileName[][EXT_FILENAME_SIZE] =
{
    MP3_EXT_FILENAME
};

#if (ENABLE_WMA)
U8 code m_au8WMA_ExtFileName[][EXT_FILENAME_SIZE] =
{
    WMA_EXT_FILENAME
};
#endif

#if (ENABLE_FLAC)
U8 code m_au8FLAC_ExtFileName[][EXT_FILENAME_SIZE] =
{
    FLAC_EXT_FILENAME
};
#endif
#if (ENABLE_AC3)
U8 code m_au8AC3_ExtFileName[][EXT_FILENAME_SIZE] =
{
    AC3_EXT_FILENAME
};
#endif


#if (ENABLE_AAC)
U8 code m_au8AAC_ExtFileName[][EXT_FILENAME_SIZE] =
{
    AAC_EXT_FILENAME
};
#endif

#if (ENABLE_WAV)
U8 code m_au8WAV_ExtFileName[][EXT_FILENAME_SIZE] =
{
    WAV_EXT_FILENAME
};
#endif

#if (ENABLE_OGG)
U8 code m_au8OGG_ExtFileName[][EXT_FILENAME_SIZE] =
{
    OGG_EXT_FILENAME
};
#endif

#if (ENABLE_AMR)
U8 code m_au8AMR_ExtFileName[][EXT_FILENAME_SIZE] =
{
    AMR_EXT_FILENAME
};

U8 code m_au8AWB_ExtFileName[][EXT_FILENAME_SIZE] =
{
    AWB_EXT_FILENAME
};
#endif

U8 code m_au8TXT_ExtFileName[][EXT_FILENAME_SIZE] =
{
    TXT_EXT_FILENAME
};

#if ENABLE_MPLAYER_PLUGIN
U8 code m_au8NES_ExtFileName[][EXT_FILENAME_SIZE] =
{
    PLG_EXT_FILENAME
};
#endif //#if ENABLE_MPLAYER_PLUGIN

#if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
U8 code m_au8LOAS_ExtFileName[][EXT_FILENAME_SIZE] =
{
    LOAS_EXT_FILENAME
};
#endif

U16 code m_u16ThumbnailArray[][2] = THUMBNAIL_POSITION_ARRAY;

static enumPhotoPreviewState m_ePhotoPreviewState;
static enumMusicPreviewState m_eMusicPreviewState;
static enumMoviePreviewState m_eMoviePreviewState;
static enumTextPreviewState  m_eTextPreviewState;
#if ENABLE_EMBEDDED_PHOTO_DISPLAY
static enumEmbeddedPhotoState m_eEmbeddedPhotoState;
static U16 m_u16PreFileIdx;
static U32 m_u32EmbeddedPhoto_FileHandle = INVALID_DATA_STREAM_HDL;
static U32 m_u32EmbeddedPhotoOffset = 0xFFFFFFFF;
static U32 m_u32EmbeddedPhotoSize = 0xFFFFFFFF;
#endif

static U32 m_u32PreviewTimer;
static U32 m_u32PlayCheckTime;
static U32 m_u32PlayingTickTime;
//static U32 m_u32LyricSubtitleCheckTime;
static U32 m_u32LyricSubtitleCurTime;
static U16 m_u16CurLyricPos;
static U32 m_u32CurSubtitlePos;
static BOOLEAN m_bIsLyricUnicode = FALSE;
static BOOLEAN m_bIsUtf8 = FALSE;
static enumMplayerStateMachineState m_eMPlayerStateMachineState;
static enumMPlayerRepeatMode m_eRepeatMode[E_MPLAYER_MAX_CONCURRENT_PLAYER_NUM];
static enumMPlayerPlayMode m_ePlayMode;
static U64 m_u64NotifyEnableFlags;
static U32 m_u32PhotoSlideShowDelayTimeS;
static U32 m_u32PhotoSlideShowTimer;
static U32 m_u32PhotoErrorDelayTimeS=0; //ms
static U32 m_u32MusicErrorDelayTimeS=0; //ms
#if ENABLE_MPLAYER_MOVIE
static U32 m_u32MovieErrorDelayTimeS=0; //ms
#endif

#if ENABLE_MPLAYER_TEXT
static U32 m_u32TextErrorDelayTimeS=0; //ms
#endif

static U8 m_u8DecodedPics;
static EN_PHOTO_VALID_OR_NOT m_ePhotoValidOrNot;
static enumMPlayerMediaSubType m_ePhotoType[2];
static enumMPlayerZoom m_eZoom;
//static enumMPlayerPhotoRotate m_ePhotoRotate;
static enumMPlayerMoviePlayMode m_eMoviePlayMode;
static enumMPlayerMusicPlayMode m_eMusicPlayMode;
static U32 m_u32DeviceCheckTimer;

#if (ENABLE_SUBTITLE_DMP)
static MPlayer_Subtitle_Tag m_Subtitle_Tag;
static enumMPlayerSubtitleType m_eExternalSubtitleType;
static enumMplayerSubtitleCoding m_eSubtitleCodingType;
static U8 m_u8ExternalSubtitleFileHandle=FCTRL_INVALID_FILE_HANDLE;
static U16 m_u16ExternalSubtitleIdx=0;
static BOOLEAN m_bIsSubtitleTaskAlive = FALSE;
#if (ENABLE_SUBTITLE_SUBIDX)
#if (ENABLE_SMALL_BUF_SUBTITLE==0)
static U32 m_u32NextExternalSubtitleStartTime=0;
#endif
#endif
static MPlayer_Subtitle_Tag m_aAliveSubtitles[MAX_ALIVE_SUBTITLE_NUM];
static U8 m_u8AliveSubtitleNum=0;
static S32 m_s32SubtitleTimeShift=0; //Subtitle time shift controlled by user
#endif // #if (ENABLE_SUBTITLE_DMP)

static S16 m_s16VideoShiftX, m_s16VideoShiftY;
static EN_RET m_eMovieMainExit = EXIT_VDPLAYER_NULL;
static enumMPlayerUSBDeviceStatus m_PrevUSBDeviceStatus=E_MPLAYER_USB_NONE;

static MPlayerPlayingFileInfo m_MPlayerInfo[E_MPLAYER_MAX_CONCURRENT_PLAYER_NUM];

#if ENABLE_USB_DETECT_STEP_BY_STEP
static MPlayerUSBDetectStruct m_MPlayerUSBDetect;
#endif

#if (ENABLE_SUBTITLE_DMP)
// Note: The order musct be the same as enumVDPlayerSubtitleType.
static code U8 m_pu8SubtitleFileExt[E_MPLAYER_SUBTITLE_NUM][EXT_FILENAME_SIZE]=
{
    "SRT",
  #if (ENABLE_SUBTITLE_SUBIDX)
    "IDX",
  #endif
    "SSA", "ASS"
#if (ENABLE_SUBTITLE_SMI)
    , {"SMI"}
#endif
#if (ENABLE_SUBTITLE_TXT)
    , "TXT", "TTX"
#endif
#if (ENABLE_SUBTITLE_SUB)
    , "SUB"
#endif
};
#endif //#if (ENABLE_SUBTITLE_DMP)

// array of iso 639 language code
static code ST_MPLAYER_ISO639_LANG m_aIso639_LanguageCode[] =
{
    {{'e','n'},     E_MPLAYER_LANGUAGE_ENGLISH},
    {{'e','n','g'}, E_MPLAYER_LANGUAGE_ENGLISH},
    {{'f','r'},     E_MPLAYER_LANGUAGE_FRENCH},
    {{'f','r','a'}, E_MPLAYER_LANGUAGE_FRENCH},
    {{'f','r','e'}, E_MPLAYER_LANGUAGE_FRENCH},
    {{'d','e'},     E_MPLAYER_LANGUAGE_GERMAN},
    {{'g','e','r'}, E_MPLAYER_LANGUAGE_GERMAN},
    {{'d','e','u'}, E_MPLAYER_LANGUAGE_GERMAN},
    {{'i','t'},     E_MPLAYER_LANGUAGE_ITALIAN},
    {{'i','t','a'}, E_MPLAYER_LANGUAGE_ITALIAN},
    {{'e','s'},     E_MPLAYER_LANGUAGE_SPANISH},
    {{'s','p','a'}, E_MPLAYER_LANGUAGE_SPANISH},
    {{'e','s','l'}, E_MPLAYER_LANGUAGE_SPANISH},
    {{'s','v'},     E_MPLAYER_LANGUAGE_SWEDISH},
    {{'s','w','e'}, E_MPLAYER_LANGUAGE_SWEDISH},
    {{'f','i'},     E_MPLAYER_LANGUAGE_FINNISH},
    {{'f','i','n'}, E_MPLAYER_LANGUAGE_FINNISH},
    {{'p','t'},     E_MPLAYER_LANGUAGE_PORTUGUESE},
    {{'p','o','r'}, E_MPLAYER_LANGUAGE_PORTUGUESE},
    {{'t','r'},     E_MPLAYER_LANGUAGE_TURKISH},
    {{'t','u','r'}, E_MPLAYER_LANGUAGE_TURKISH},
    {{'c','s'},     E_MPLAYER_LANGUAGE_CZECH},
    {{'c','z','e'}, E_MPLAYER_LANGUAGE_CZECH},
    {{'c','e','s'}, E_MPLAYER_LANGUAGE_CZECH},
    {{'d','a'},     E_MPLAYER_LANGUAGE_DANISH},
    {{'d','a','n'}, E_MPLAYER_LANGUAGE_DANISH},
    {{'n','l'},     E_MPLAYER_LANGUAGE_DUTCH},
    {{'d','u','t'}, E_MPLAYER_LANGUAGE_DUTCH},
    {{'n','l','d'}, E_MPLAYER_LANGUAGE_DUTCH},
    {{'p','l'},     E_MPLAYER_LANGUAGE_POLISH},
    {{'p','o','l'}, E_MPLAYER_LANGUAGE_POLISH},
    {{'e','l'},     E_MPLAYER_LANGUAGE_GREEK},
    {{'g','r','e'}, E_MPLAYER_LANGUAGE_GREEK},
    {{'e','l','l'}, E_MPLAYER_LANGUAGE_GREEK},
    {{'h','u'},     E_MPLAYER_LANGUAGE_HUNGARIAN},
    {{'h','u','n'}, E_MPLAYER_LANGUAGE_HUNGARIAN},
    {{'n','n'},     E_MPLAYER_LANGUAGE_NORWEGIAN},
    {{'n','o','r'}, E_MPLAYER_LANGUAGE_NORWEGIAN},
    {{'r','o'},     E_MPLAYER_LANGUAGE_ROMANIAN},
    {{'r','u','m'}, E_MPLAYER_LANGUAGE_ROMANIAN},
    {{'r','o','m'}, E_MPLAYER_LANGUAGE_ROMANIAN},
    {{'r','o','n'}, E_MPLAYER_LANGUAGE_ROMANIAN},
    {{'r','u'},     E_MPLAYER_LANGUAGE_RUSSIAN},
    {{'r','u','s'}, E_MPLAYER_LANGUAGE_RUSSIAN},
    {{'a','r'},     E_MPLAYER_LANGUAGE_ARABIC},
    {{'a','r','a'}, E_MPLAYER_LANGUAGE_ARABIC},
    {{'h','e'},     E_MPLAYER_LANGUAGE_HEBREW},
    {{'h','e','b'}, E_MPLAYER_LANGUAGE_HEBREW},
    {{'s','r'},     E_MPLAYER_LANGUAGE_SERBIAN},
    {{'s','c','c'}, E_MPLAYER_LANGUAGE_SERBIAN},
    {{'s','r','p'}, E_MPLAYER_LANGUAGE_SERBIAN},
    {{'s','l'},     E_MPLAYER_LANGUAGE_SLOVENIAN},
    {{'s','l','v'}, E_MPLAYER_LANGUAGE_SLOVENIAN},
    {{'s','h'},     E_MPLAYER_LANGUAGE_CROATIAN},
    {{'s','c','r'}, E_MPLAYER_LANGUAGE_CROATIAN},
    {{'h','r','v'}, E_MPLAYER_LANGUAGE_CROATIAN},
    {{'b','g'},     E_MPLAYER_LANGUAGE_BULGARIAN},
    {{'b','u','l'}, E_MPLAYER_LANGUAGE_BULGARIAN},
    {{'c','y'},     E_MPLAYER_LANGUAGE_WELSH},
    {{'w','e','l'}, E_MPLAYER_LANGUAGE_WELSH},
    {{'c','y','m'}, E_MPLAYER_LANGUAGE_WELSH},
    {{'g','d'},     E_MPLAYER_LANGUAGE_GAELIC},
    {{'g','l','a'}, E_MPLAYER_LANGUAGE_GAELIC},
    {{'g','a','e'}, E_MPLAYER_LANGUAGE_GAELIC},
    {{'g','d','h'}, E_MPLAYER_LANGUAGE_GAELIC},
    {{'g','a'},     E_MPLAYER_LANGUAGE_IRISH},
    {{'g','l','e'}, E_MPLAYER_LANGUAGE_IRISH},
    {{'k','o'},     E_MPLAYER_LANGUAGE_KOREAN},
    {{'k','o','r'}, E_MPLAYER_LANGUAGE_KOREAN},
    {{'j','a'},     E_MPLAYER_LANGUAGE_JAPAN},
    {{'j','p','n'}, E_MPLAYER_LANGUAGE_JAPAN},
    {{'z','h'},     E_MPLAYER_LANGUAGE_CHINESE},
    {{'c','h','i'}, E_MPLAYER_LANGUAGE_CHINESE},
    {{'z','h','o'}, E_MPLAYER_LANGUAGE_CHINESE},
    {{'g','l'},     E_MPLAYER_LANGUAGE_GALLEGAN},
    {{'g','l','g'}, E_MPLAYER_LANGUAGE_GALLEGAN},
    {{'e','u'},     E_MPLAYER_LANGUAGE_BASQUE},
    {{'b','a','q'}, E_MPLAYER_LANGUAGE_BASQUE},
    {{'e','u','s'}, E_MPLAYER_LANGUAGE_BASQUE},
    {{'l','b'},     E_MPLAYER_LANGUAGE_LUXEMBOURGISH},
    {{'l','t','z'}, E_MPLAYER_LANGUAGE_LUXEMBOURGISH},
    {{'i','s'},     E_MPLAYER_LANGUAGE_ICELANDIC},
    {{'i','c','e'}, E_MPLAYER_LANGUAGE_ICELANDIC},
    {{'i','s','l'}, E_MPLAYER_LANGUAGE_ICELANDIC},
    {{'l','v'},     E_MPLAYER_LANGUAGE_LATVIAN},
    {{'l','a','v'}, E_MPLAYER_LANGUAGE_LATVIAN},
    {{'e','t'},     E_MPLAYER_LANGUAGE_ESTONIAN},
    {{'e','s','t'}, E_MPLAYER_LANGUAGE_ESTONIAN},
    {{'l','t'},     E_MPLAYER_LANGUAGE_LITHUANIAN},
    {{'l','i','t'}, E_MPLAYER_LANGUAGE_LITHUANIAN},
    {{'u','k'},     E_MPLAYER_LANGUAGE_UKRAINIAN},
    {{'u','k','r'}, E_MPLAYER_LANGUAGE_UKRAINIAN},
    {{'b','e'},     E_MPLAYER_LANGUAGE_BELARUSIAN},
    {{'b','e','l'}, E_MPLAYER_LANGUAGE_BELARUSIAN},
    {{'h','i'},     E_MPLAYER_LANGUAGE_HINDI},
    {{'h','i','n'}, E_MPLAYER_LANGUAGE_HINDI},
    {{'r','n'},     E_MPLAYER_LANGUAGE_KIRUNDI},
    {{'u','n','d'}, E_MPLAYER_LANGUAGE_KIRUNDI},
    {{'m','i'},     E_MPLAYER_LANGUAGE_MAORI},
    {{'m','a','o'}, E_MPLAYER_LANGUAGE_MAORI},
    {{'s','k'},     E_MPLAYER_LANGUAGE_SLOVAK},
    {{'s','l','o'}, E_MPLAYER_LANGUAGE_SLOVAK},
    {{'s','l','k'}, E_MPLAYER_LANGUAGE_SLOVAK},
    {{'c','a'},     E_MPLAYER_LANGUAGE_CATALAN},
    {{'c','a','t'}, E_MPLAYER_LANGUAGE_CATALAN},
    {{'v','o'},     E_MPLAYER_LANGUAGE_VOLAPUK},
    {{'v','o','l'}, E_MPLAYER_LANGUAGE_VOLAPUK},
    {{'c','m','n'}, E_MPLAYER_LANGUAGE_MANDARIN},
    {{'y','u','e'}, E_MPLAYER_LANGUAGE_CANTONESE},
    {{'s','m','i'}, E_MPLAYER_LANGUAGE_SAMI},
    {{'q','a','a'}, E_MPLAYER_LANGUAGE_QAA},   /* qaa :: Reserved for local use */
    {{'t','h'},     E_MPLAYER_LANGUAGE_THAI},
    {{'t','h','a'}, E_MPLAYER_LANGUAGE_THAI},
    {{'i','d'},     E_MPLAYER_LANGUAGE_INDONESIAN},
    {{'i','n','d'}, E_MPLAYER_LANGUAGE_INDONESIAN},
    {{'m','s'},     E_MPLAYER_LANGUAGE_MALAY},
    {{'m','a','y'}, E_MPLAYER_LANGUAGE_MALAY},
    {{'m','s','a'}, E_MPLAYER_LANGUAGE_MALAY},
    {{'v','i'},     E_MPLAYER_LANGUAGE_VIETNAMESE},
    {{'v','i','e'}, E_MPLAYER_LANGUAGE_VIETNAMESE},
    {{'u','r'},     E_MPLAYER_LANGUAGE_URDU},
    {{'u','r','d'}, E_MPLAYER_LANGUAGE_URDU},
    {{'a','f'},     E_MPLAYER_LANGUAGE_AFRIKAANS},
    {{'a','f','r'}, E_MPLAYER_LANGUAGE_AFRIKAANS},
    {{'z','u'},     E_MPLAYER_LANGUAGE_ZULU},
    {{'z','u','l'}, E_MPLAYER_LANGUAGE_ZULU},
    {{'a','m'},     E_MPLAYER_LANGUAGE_AMHARIC},
    {{'a','m','h'}, E_MPLAYER_LANGUAGE_AMHARIC},
    {{'y','o'},     E_MPLAYER_LANGUAGE_YORUBA},
    {{'y','o','r'}, E_MPLAYER_LANGUAGE_YORUBA},
    {{'h','a'},     E_MPLAYER_LANGUAGE_HAUSA},
    {{'h','a','u'}, E_MPLAYER_LANGUAGE_HAUSA},
    {{'x','h'},     E_MPLAYER_LANGUAGE_XHOSA},
    {{'x','h','o'}, E_MPLAYER_LANGUAGE_XHOSA},
    {{'s','w'},     E_MPLAYER_LANGUAGE_SWAHILI},
    {{'s','w','a'}, E_MPLAYER_LANGUAGE_SWAHILI},
    {{'i','b','o'}, E_MPLAYER_LANGUAGE_IGBO},
};

// --------------------------------------------------------------------------------------
// Photo
static U32 m_u32PhotoCurrentDisplayedIdx = 0;
static S32 m_s32Photo_LastDecodeIdx = -1;
static S32 m_s32Photo_LastDecodeFailIdx = -1;
static U32 m_u32Photo_PlayPrevDecodeFailCount = 0;
// --------------------------------------------------------------------------------------

// --------------------------------------------------------------------------------------
// Movie
#if ENABLE_MPLAYER_MOVIE
static enumMPlayerMovieRepeatAB m_enRepeatABMode = E_MPLAYER_MOVIE_SET_REPEAT_AB_NONE;
static U32 m_u32MovieRepeatTime[2];
#if ENABLE_SUBTITLE_DMP
static BOOLEAN m_bNewRepeatABLoop = FALSE;
#endif
#endif
// --------------------------------------------------------------------------------------
// Copy & Paste
#if ENABLE_COPY_SELECTED_FILES
static BOOLEAN m_bIsCopyMode = FALSE;
static U16 u16CurrentCopyIndex;
static U8 m_u8CopySrcLun;
static U8 m_u8CopyDstLun;
static U16 m_u16SrcDriveIdx;
static U16 m_u16CopySrcDriveIdx;
static U16 m_u16CopyDstDriveIdx;
static U8 m_u8CopySrcFileBrowserHandle = INVALID_BROWSER_HANDLE;
static U8 m_u8CopyDstFileBrowserHandle = INVALID_BROWSER_HANDLE;
static U8  m_u8FileOpReadHandle, m_u8FileOpWriteHandle;
static FileEntry m_CopyDstDirEntry;
static U32 m_u32CopyDataLeft, m_u32CopyDataLen;
static U64 m_u64TotalCopySize;
static U64 m_u64TotalCopiedSize;
static U32 m_u32TotalCopiedSizeInKB;
static U32 m_u32TotalCopiedPercentage;
static BOOLEAN m_bEndofCopyFiles;
static BOOLEAN m_bAfterCopyDoneStayInSrcFolder = TRUE;
static BOOLEAN m_bUserBreakCopy = FALSE;

#if ENABLE_SUBTITLE_COPY_AND_DELETE
typedef struct
{
    FileEntry fileEntry;
    U8 u8ExtFileName[3+1];
}ST_MPLAYER_ExtFileInfo;

#if (ENABLE_EXTERNAL_SUBTITLE_FAST_SWITCHING)
    static ST_MPLAYER_ExtFileInfo m_aExtFileInfoList[MAX_DEDICATED_FILE_EXT_NUM];
#else
    static ST_MPLAYER_ExtFileInfo m_ExtFileInfo;
#endif
static U8 m_u8CurCopyingDeletingExtSubtitleFileIdx;
static U8 m_u8CopyDeleteExtSubtitleFileNum;
static BOOLEAN m_bCopyingExtSubtitleFile=FALSE;
static BOOLEAN m_bDeletingExtSubtitleFile=FALSE;
#endif
#endif
// --------------------------------------------------------------------------------------

// Delete
#if ENABLE_DELETE_SELECTED_FILES
static U8 m_u8DeleteLun;
static BOOLEAN m_bUserBreakDelete = FALSE;
static U16 m_u16CurDeletePlaylistIdx;
static U16 m_u16DeleteCount;
static U16 m_u16TotalDeleteCount;
static U32 m_u32TotalDeletedPercentage;
static FileEntry m_CurDeleteFileEntry;
static BOOLEAN m_bEndofDeleteFiles;
#endif
// --------------------------------------------------------------------------------------
static enumSubtitleCharsetType m_enSubtitleCharsetType = SUBTITLE_CHARSET_DEFAULT;

// --------------------------------------------------------------------------------------
// Capture
#if (ENABLE_MPLAYER_AUDIO_CAPTURE)
static MPlayerAudioCapture m_AudioCapture = {
    //WAV header
    .u32DataChunkSize = 0,
    .u32SampleRate = 0,
    .u16Channels = 0,
    .u16BitsPerSample = 0,

    .u32CurPCMOffset = 0,
    .u32PrePCMOffset = 0,
    .u8WriteFileHandle = INVALID_FILE_HANDLE,
};

static ST_AUDIO_CAPTURE_SET_INFO m_AudioCaptureSetting;
#endif

#if (ENABLE_MPLAYER_VIDEO_CAPTURE)
static MPlayerVideoCapture m_VideoCapture = {
    .u32EncodeDstBuffer = 0,
    .u8WriteFileHandle = INVALID_FILE_HANDLE,
    .u8Progress = 0,
};

static ST_VIDEO_CAPTURE_SET_INFO m_VideoCaptureSetting;
#endif
// --------------------------------------------------------------------------------------

#if ENABLE_SUBTITLE_DMP
typedef struct
{
    FileEntry fileEntry;
    U8 u8ExtFileName[3+1];
}ST_MPLAYER_ExtFileInfo;
#endif
//*****************************************************************************
//              Local Functions Prototype
//*****************************************************************************
//******************************************************************************
/// Clear the photo information for the current photo file.
/// @param
/// @return
//******************************************************************************
void MApp_MPlayer_ClearPhotoInfo(void)
{
    memset(&m_photoInfo, 0, sizeof(MPlayerPhotoInfo));
}

#if 0
static void _MApp_MPlayer_RemoveAllFilesFromPlayingListAccordingToDriveIdx(U16 u16DriveIdx);
#endif

#if(STORE_SUBTITLE_ENTRY_TO_SUBTITLE_BUFFER || ENABLE_BGM) //fix compile error
static void _MApp_MPlayer_GetLongFileName(MPlayerFileInfo *pFileInfo);
#endif
#if (ENABLE_MPLAYER_SORT)
static U16 _MApp_MPlayer_LookupPhysicalIndex(U16 u16Idx);
#if ENABLE_MPLAYER_SORT_EX
static void _MApp_MPlayer_SetFileSortingMode(enumMPlayerFileSortMode eSortMode);
static void _MApp_MPlayer_SetFileSortingOrderMode(enumMPlayerFileSortSubMode eOrderMode);
static BOOLEAN _MApp_MPlayer_FileInfoCmpByName_Less(MPlayerFileInfo *src, MPlayerFileInfo *dst);
static BOOLEAN _MApp_MPlayer_FileInfoCmpByPhyIndex_Less(MPlayerFileInfo *src, MPlayerFileInfo *dst);
static BOOLEAN _MApp_MPlayer_FileInfoCmpByTime_Less(MPlayerFileInfo *src, MPlayerFileInfo *dst);
static void _MApp_MPlayer_SortDirAndMove_EX(U16 u16DirCnt);
static U16 _MApp_MPlayer_SortFileAndMove_EX(U16 u16DirCnt, U16 u16TotalCnt);
#else
static void _MApp_MPlayer_SortDirAndMove(U16 u16DirCnt);
static U16 _MApp_MPlayer_SortFileAndMove(U16 u16DirCnt, U16 u16TotalCnt);
#endif //ENABLE_MPLAYER_SORT_EX
#endif
extern U16 MApp_Transfer2Unicode(U16 u16Code);
#if ENABLE_EMBEDDED_PHOTO_DISPLAY
static BOOLEAN MApp_MPlayer_EmbeddedPhoto_DecodeMemory_Init(FileEntry *pFileEntry, BOOLEAN bThumbnail, MApp_Photo_DataRequestCallBack pfCallBack);
static S32 _MApp_MPlayer_EmbeddedPhoto_DataRequestCallBack(U8 *pu8BufferAddr, U32 u32RequestSize);
static BOOLEAN MApp_MPlayer_EmbeddedPhotoIO_Close(void);
#endif
#if PLAYLIST_BGM
static void _MApp_MPlayer_BGM_Playlist_Swap(void);
#endif
#if RANDOM_PLAY
static BOOLEAN _MApp_MPlayer_ResetRandomPlayTable(enumMPlayerIdx eMPlayerIdx);
static U16 _MApp_MPlayer_RandomPlay_Rand(enumMPlayerIdx eMPlayerIdx);
static BOOLEAN _MApp_MPlayer_SetRandomPlayTable(enumMPlayerIdx eMPlayerIdx);
#endif

#if ENABLE_SUBTITLE_DMP
static BOOLEAN _MApp_MPlayer_HideSubtitle(void);
static BOOLEAN _MApp_MPlayer_InitSubtitleTask(void);
static BOOLEAN _MApp_MPlayer_EnableSubtitleTask(void);
static BOOLEAN _MApp_MPlayer_DisableSubtitleTask(void);
static BOOLEAN _MApp_MPlayer_SubtitleTask(U32 u32CurTime);
#endif

#if ENABLE_COPY_SELECTED_FILES
static BOOLEAN _MApp_MPlayer_CopySelectedFile(U16 u16FileIdx);
#if ENABLE_SUBTITLE_COPY_AND_DELETE
static BOOLEAN _MApp_MPlayer_CopyExtFiles(U8 u8ExtFileInx);
#endif
static BOOLEAN _MApp_MPlayer_CopyNext(void);
static BOOLEAN _MApp_MPlayer_BeginPasteFileAndRenameIfFileExisted(void);
#endif

#if ENABLE_EMBEDDED_PHOTO_DISPLAY
static BOOLEAN _MApp_MPlayer_MusicMetaData_Probe(MPlayerFileInfo fileInfo,ST_MPLAYER_PROBE_INFO *pstTempMplayerProbeInfo, EN_MUSIC_INFO eMusicInfoType);
#endif

#if (ENABLE_MPLAYER_VIDEO_CAPTURE || ENABLE_MPLAYER_AUDIO_CAPTURE)
static enumCaptureRet _MApp_MPlayer_CaptureCheckDrive(U8 u8ConnectDrive);
static BOOLEAN _MApp_MPlayer_ChangeToSpecificDirectory(U16 *pu16DstPath, U16 pu16DstPathLen);
static BOOLEAN _MApp_MPlayer_RenameFileIfFileExisted(U16 *pu16SrcFileName, U16 u16MaxNameBufferLen);
#endif

#if (ENABLE_MPLAYER_VIDEO_CAPTURE)
static BOOLEAN _MApp_MPlayer_CaptureVideo2BufferAndEncodeInit(U32 u32FirstBufferAddr, U32 u32FirstBufferSize, U32 u32SecondBufferAddr, U32 u32SecondBufferSize);
static BOOLEAN _MApp_MPlayer_SetVideoCaptureSetting(ST_VIDEO_CAPTURE_SET_INFO* pVideoCaptureSetInfo);
static BOOLEAN _MApp_MPlayer_GetVideoCaptureSetting(ST_VIDEO_CAPTURE_SET_INFO* pVideoCaptureSetInfo);
#endif

#if (ENABLE_MPLAYER_AUDIO_CAPTURE)
static BOOLEAN _Mapp_MPlayer_WAVHeaderGenerator(U8 *pu8Header, U32 u32HeaderLength, MPlayerAudioCapture* stAudioCaptureInfo);
static BOOLEAN _MApp_MPlayer_SetAudioCaptureSetting(ST_AUDIO_CAPTURE_SET_INFO* pAudioCaptureSetInfo);
static BOOLEAN _MApp_MPlayer_GetAudioCaptureSetting(ST_AUDIO_CAPTURE_SET_INFO* pAudioCaptureSetInfo);
#endif

//*****************************************************************************
//              Local Functions
//*****************************************************************************
#if ENABLE_MPLAYER_MOVIE
static void _MApp_MPlayer_OutputFilename(MPlayerFileInfo *pfileInfo)
{
    if (g_bOutputMMAliveMessage)
    {
        U16 u16LongFileName[(FILE_INFO_LONG_FILENAME_SIZE+1) >> 1];

        memset(u16LongFileName,0,sizeof(u16LongFileName));
        memcpy(&u16LongFileName[0], &pfileInfo->u8LongFileName[0], FILE_INFO_LONG_FILENAME_SIZE);
        FS_Unicode2ASCII(&u16LongFileName[0]);
        //printf("MM: playing %s\n", (U8 *)&u16LongFileName[0]);
    }
}
#endif

static void _MApp_MPlayer_OutputFilenameByFileEntry(FileEntry *pFileEntry)
{
    if (g_bOutputMMAliveMessage)
    {
        U16 u16LongFileName[FILE_INFO_LONG_FILENAME_SIZE >> 1];
        U8 u8Len;
        U8 *u8FileName = (U8 *)u16LongFileName;

        // Get long file name from file entry.
        u8Len = MApp_FileBrowser_GetLongFileNameByFileEntry(
                        pFileEntry,
                        (U32)(&u8FileName[0]),
                        (FILE_INFO_LONG_FILENAME_SIZE/2-1));
        u8Len = (u8Len > (FILE_INFO_LONG_FILENAME_SIZE/2-1)) ?
                        FILE_INFO_LONG_FILENAME_SIZE/2-1:
                        u8Len;
        u8FileName[u8Len*2] = 0;
        u8FileName[u8Len*2+1] = 0;

        FS_Unicode2ASCII(&u16LongFileName[0]);
        //printf("MM: playing %s\n", (U8 *)&u16LongFileName[0]);
    }
}

static int _MApp_MPlayer_ToLower(U16 c)
{
    if (c >= 'A' && c <= 'Z')
    {
        c = 'a' + (c - 'A');
    }
    return c;
}

#if (ENABLE_SUBTITLE_DMP)
static void _MApp_MPlayer_ToUpper(U8 *pu8Data, U16 u16Len)
{
    U16 i;

    for(i=0;i<u16Len;i++)
    {
        if(pu8Data[i] >= 'a' && pu8Data[i] <= 'z')
        {
            pu8Data[i] = pu8Data[i] - 'a' + 'A';
        }
    }
}
#endif

static BOOLEAN _MApp_MPlayer_GetPlayListAddressByMediaType(enumMPlayerMediaType eMediaType, U32 *pu32XdataWindowBase)
{
    if(pu32XdataWindowBase == NULL)
    {
        return FALSE;
    }

    switch(eMediaType)
    {
    #if ENABLE_MPLAYER_PHOTO
        case E_MPLAYER_TYPE_PHOTO:
            *pu32XdataWindowBase = ((MPLAYER_PHOTO_PLAYLIST_MEMORY_TYPE & MIU1) ? (MPLAYER_PHOTO_PLAYLIST_ADR | MIU_INTERVAL) : (MPLAYER_PHOTO_PLAYLIST_ADR));
            break;
    #endif

    #if ENABLE_MPLAYER_MUSIC
        case E_MPLAYER_TYPE_MUSIC:
            *pu32XdataWindowBase = ((MPLAYER_MUSIC_PLAYLIST_MEMORY_TYPE & MIU1) ? (MPLAYER_MUSIC_PLAYLIST_ADR | MIU_INTERVAL) : (MPLAYER_MUSIC_PLAYLIST_ADR));
            break;
    #endif  // #if ENABLE_MPLAYER_MUSIC

    #if ENABLE_MPLAYER_MOVIE
        case E_MPLAYER_TYPE_MOVIE:
            *pu32XdataWindowBase = ((MPLAYER_MOVIE_PLAYLIST_MEMORY_TYPE & MIU1) ? (MPLAYER_MOVIE_PLAYLIST_ADR | MIU_INTERVAL) : (MPLAYER_MOVIE_PLAYLIST_ADR));
            break;
    #endif  // #if ENABLE_MPLAYER_MOVIE

    #if ENABLE_MPLAYER_TEXT
        case E_MPLAYER_TYPE_TEXT:
            *pu32XdataWindowBase = ((MPLAYER_TEXT_PLAYLIST_MEMORY_TYPE & MIU1) ? (MPLAYER_TEXT_PLAYLIST_ADR | MIU_INTERVAL) : (MPLAYER_TEXT_PLAYLIST_ADR));
            break;
    #endif  // #if ENABLE_MPLAYER_TEXT

    #if ENABLE_MPLAYER_PLUGIN
        case E_MPLAYER_TYPE_PLUGIN:
            *pu32XdataWindowBase = ((MPLAYER_EMU_PLAYLIST_MEMORY_TYPE & MIU1) ? (MPLAYER_EMU_PLAYLIST_ADR | MIU_INTERVAL) : (MPLAYER_EMU_PLAYLIST_ADR));
            break;
    #endif  // #if ENABLE_MPLAYER_PLUGIN
        default:
            return FALSE;
    }

    return TRUE;
}

#if ENABLE_SUBTITLE_DMP
static void _MApp_MPlayer_ReinitRepeatABSubtitle(void)
{
    MApp_VDPlayer_TextSubtitleInit();
    m_bNewRepeatABLoop = FALSE;
}

static U16 MApp_MPlayer_ConvertDecimalString2Digit(U8 *pu8Data, U32 *pu32Val)
{
    U16 u16Index;

    pu32Val[0] = 0;
    for(u16Index=0;
        pu8Data[u16Index] >= '0' && pu8Data[u16Index] <= '9';
        u16Index++)
    {
        pu32Val[0] = pu32Val[0] * 10 + (U32)(pu8Data[u16Index] - '0');
    }
    return u16Index;
}

static U16 MApp_MPlayer_ConvertHexString2Digit(U8 *pu8Data, U32 *pu32Val)
{
    #define IS_HEX(x) ((x >= '0' && x <= '9') || (x >= 'a' && x <= 'f') || (x >= 'A' && x <= 'F'))
    U16 u16Index;
    U8 u32CharVal = 0;

    pu32Val[0] = 0;
    for(u16Index=0; IS_HEX(pu8Data[u16Index]); u16Index++)
    {
        if(pu8Data[u16Index] <= '9')
        {
            u32CharVal = pu8Data[u16Index] - '0';
        }
        else if(pu8Data[u16Index] <= 'F')
        {
            u32CharVal = pu8Data[u16Index] - 'A'+ 0xa; //0xA ~ 0xF
        }
        else if(pu8Data[u16Index] <= 'f')
        {
            u32CharVal = pu8Data[u16Index] - 'a'+ 0xa; //0xa ~ 0xf
        }
        pu32Val[0] = pu32Val[0] * 16 + u32CharVal;
    }
    return u16Index;
}
#endif //ENABLE_SUBTITLE_DMP

static U16 _MApp_MPlayer_WcsNCaseCmp(U16 *src, U16 *dst, U16 len)
{
    U16 iRet, i;

    for (i = 0; i < len; i++)
    {
        iRet = _MApp_MPlayer_ToLower(src[i]) - _MApp_MPlayer_ToLower(dst[i]);
        if(iRet)
        {
            return iRet;
        }
    }

    return 0;
}

static BOOLEAN _MApp_MPlayer_GetNotifyRtn(void)
{
    BOOLEAN bRtn = m_bNotifyRtn;
    m_bNotifyRtn = FALSE;
    return bRtn;
}

#if ENABLE_MPLAYER_MOVIE
static BOOLEAN _MApp_MPlayer_IsSupportedMovie(enumMPlayerMediaSubType eMediaSubType)
{
    enumMPlayerMediaSubType endType = E_MPLAYER_SUBTYPE_MOVIE;

    if(eMediaSubType >= E_MPLAYER_SUBTYPE_TS &&
        eMediaSubType <= endType)
    {
        return TRUE;
    }
    return FALSE;
}
#endif

#if ENABLE_MPLAYER_MUSIC
//******************************************************************************
/// Determine input media subtype is music or not.
/// @param  eMediaSubType \b IN Specify the media subtype.
/// @return TRUE/FALSE.
//******************************************************************************
static BOOLEAN _MApp_MPlayer_IsSupportedMusic(enumMPlayerMediaSubType eMediaSubType)
{
    BOOLEAN bMusicType = FALSE;
    switch (eMediaSubType)
    {
  #if (ENABLE_FLAC)
      case E_MPLAYER_SUBTYPE_FLAC:
          bMusicType = TRUE;
          break;
  #endif

  #if (ENABLE_AC3)
      case E_MPLAYER_SUBTYPE_AC3:
          bMusicType = TRUE;
          break;
  #endif

  #if (ENABLE_WMA)
        case E_MPLAYER_SUBTYPE_WMA:
            bMusicType = TRUE;
            break;
  #endif

  #if (ENABLE_AAC)
        case E_MPLAYER_SUBTYPE_AAC:
            bMusicType = TRUE;
            break;
  #endif

    #if (ENABLE_WAV)
        case E_MPLAYER_SUBTYPE_WAV:
            bMusicType = TRUE;
            break;
    #endif

        case E_MPLAYER_SUBTYPE_MP3:
            bMusicType = TRUE;
            break;

  #if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
        case E_MPLAYER_SUBTYPE_LOAS:
            bMusicType = TRUE;
            break;
  #endif

    #if (ENABLE_OGG)
        case E_MPLAYER_SUBTYPE_OGG:
            bMusicType = TRUE;
            break;
    #endif

    #if (ENABLE_AMR)
        case E_MPLAYER_SUBTYPE_AMR:
            bMusicType = TRUE;
            break;

        case E_MPLAYER_SUBTYPE_AWB:
            bMusicType = TRUE;
            break;
    #endif

        default:
            break;
    }

    return bMusicType;
}
#endif

static BOOLEAN _MApp_IsMedia_File_ByExtName(enumMPlayerMediaSubType eType, U8 *pu8ExtName)
{
    U8 i, *pu8MediaTypeName, u8ExtNum, j;

    switch(eType)
    {
#if ENABLE_MPLAYER_PHOTO
    case E_MPLAYER_SUBTYPE_JPG:
        pu8MediaTypeName = &m_au8JPG_ExtFileName[0][0];
        u8ExtNum = sizeof(m_au8JPG_ExtFileName)/EXT_FILENAME_SIZE;
        break;
#if (ENABLE_BMP)
    case E_MPLAYER_SUBTYPE_BMP:
        pu8MediaTypeName = &m_au8BMP_ExtFileName[0][0];
        u8ExtNum = sizeof(m_au8BMP_ExtFileName)/EXT_FILENAME_SIZE;
        break;
#endif
#if (ENABLE_PNG)
    case E_MPLAYER_SUBTYPE_PNG:
        pu8MediaTypeName = &m_au8PNG_ExtFileName[0][0];
        u8ExtNum = sizeof(m_au8PNG_ExtFileName)/EXT_FILENAME_SIZE;
        break;
#endif
#if (ENABLE_TIFF)
    case E_MPLAYER_SUBTYPE_TIFF:
        pu8MediaTypeName = &m_au8TIFF_ExtFileName[0][0];
        u8ExtNum = sizeof(m_au8TIFF_ExtFileName)/EXT_FILENAME_SIZE;
        break;
#endif
#if (ENABLE_GIF)
    case E_MPLAYER_SUBTYPE_GIF:
        pu8MediaTypeName = &m_au8GIF_ExtFileName[0][0];
        u8ExtNum = sizeof(m_au8GIF_ExtFileName)/EXT_FILENAME_SIZE;
        break;
#endif
#endif  // #if ENABLE_MPLAYER_PHOTO
#if ENABLE_MPLAYER_MUSIC
    case E_MPLAYER_SUBTYPE_MP3:
        pu8MediaTypeName = &m_au8MP3_ExtFileName[0][0];
        u8ExtNum = sizeof(m_au8MP3_ExtFileName)/EXT_FILENAME_SIZE;
        break;
#if (ENABLE_FLAC)
    case E_MPLAYER_SUBTYPE_FLAC:
        pu8MediaTypeName = &m_au8FLAC_ExtFileName[0][0];
        u8ExtNum = sizeof(m_au8FLAC_ExtFileName)/EXT_FILENAME_SIZE;
        break;
#endif
#if (ENABLE_AC3)
    case E_MPLAYER_SUBTYPE_AC3:
        pu8MediaTypeName = &m_au8AC3_ExtFileName[0][0];
        u8ExtNum = sizeof(m_au8AC3_ExtFileName)/EXT_FILENAME_SIZE;
        break;
#endif
#if (ENABLE_AAC)
    case E_MPLAYER_SUBTYPE_AAC:
        pu8MediaTypeName = &m_au8AAC_ExtFileName[0][0];
        u8ExtNum = sizeof(m_au8AAC_ExtFileName)/EXT_FILENAME_SIZE;
        break;
#endif
#if (ENABLE_WAV)
    case E_MPLAYER_SUBTYPE_WAV:
        pu8MediaTypeName = &m_au8WAV_ExtFileName[0][0];
        u8ExtNum = sizeof(m_au8WAV_ExtFileName)/EXT_FILENAME_SIZE;
        break;
#endif
#if (ENABLE_WMA)
    case E_MPLAYER_SUBTYPE_WMA:
        pu8MediaTypeName = &m_au8WMA_ExtFileName[0][0];
        u8ExtNum = sizeof(m_au8WMA_ExtFileName)/EXT_FILENAME_SIZE;
        break;
#endif  // #if ENABLE_WMA
#if ENABLE_NON_PARSING_AUDIO_DATA_INPUT
    case E_MPLAYER_SUBTYPE_LOAS:
        pu8MediaTypeName = &m_au8LOAS_ExtFileName[0][0];
        u8ExtNum = sizeof(m_au8LOAS_ExtFileName)/(EXT_FILENAME_SIZE);
        break;
#endif
#if (ENABLE_OGG)
    case E_MPLAYER_SUBTYPE_OGG:
        pu8MediaTypeName = &m_au8OGG_ExtFileName[0][0];
        u8ExtNum = sizeof(m_au8OGG_ExtFileName)/EXT_FILENAME_SIZE;
        break;
#endif
#if (ENABLE_AMR)
    case E_MPLAYER_SUBTYPE_AMR:
        pu8MediaTypeName = &m_au8AMR_ExtFileName[0][0];
        u8ExtNum = sizeof(m_au8AMR_ExtFileName)/EXT_FILENAME_SIZE;
        break;
    case E_MPLAYER_SUBTYPE_AWB:
        pu8MediaTypeName = &m_au8AWB_ExtFileName[0][0];
        u8ExtNum = sizeof(m_au8AWB_ExtFileName)/EXT_FILENAME_SIZE;
        break;
#endif
#endif  // #if ENABLE_MPLAYER_MUSIC
#if ENABLE_MPLAYER_MOVIE
    case E_MPLAYER_SUBTYPE_TS:
        pu8MediaTypeName = &m_au8TS_ExtFileName[0][0];
        u8ExtNum = sizeof(m_au8TS_ExtFileName)/EXT_FILENAME_SIZE;
        break;
    case E_MPLAYER_SUBTYPE_RM:
        pu8MediaTypeName = &m_au8RM_ExtFileName[0][0];
        u8ExtNum = sizeof(m_au8RM_ExtFileName)/EXT_FILENAME_SIZE;
        break;
    case E_MPLAYER_SUBTYPE_MPEG:
        pu8MediaTypeName = &m_au8MPEG_ExtFileName[0][0];
        u8ExtNum = sizeof(m_au8MPEG_ExtFileName)/EXT_FILENAME_SIZE;
        break;
    case E_MPLAYER_SUBTYPE_MPEG4:
        pu8MediaTypeName = &m_au8MPEG4_ExtFileName[0][0];
        u8ExtNum = sizeof(m_au8MPEG4_ExtFileName)/EXT_FILENAME_SIZE;
        break;
#if ENABLE_WMV
    case E_MPLAYER_SUBTYPE_WMV:
        pu8MediaTypeName = &m_au8WMV_ExtFileName[0][0];
        u8ExtNum = sizeof(m_au8WMV_ExtFileName)/EXT_FILENAME_SIZE;
        break;
#endif
#if ENABLE_DVD
    case E_MPLAYER_SUBTYPE_DVD:
        pu8MediaTypeName = &m_au8DVD_ExtFileName[0][0];
        u8ExtNum = sizeof(m_au8DVD_ExtFileName)/EXT_FILENAME_SIZE;
        break;
    case E_MPLAYER_SUBTYPE_IFO:
        pu8MediaTypeName = &m_au8IFO_ExtFileName[0][0];
        u8ExtNum = sizeof(m_au8IFO_ExtFileName)/EXT_FILENAME_SIZE;
        break;
#endif
#endif  // #if ENABLE_MPLAYER_MOVIE
#if ENABLE_MPLAYER_TEXT
    case E_MPLAYER_SUBTYPE_TEXT:
        pu8MediaTypeName = &m_au8TXT_ExtFileName[0][0];
        u8ExtNum = sizeof(m_au8TXT_ExtFileName)/EXT_FILENAME_SIZE;
        break;
#endif  // #if ENABLE_MPLAYER_TEXT
#if ENABLE_MPLAYER_PLUGIN
    case E_MPLAYER_SUBTYPE_PLG:
        pu8MediaTypeName = &m_au8NES_ExtFileName[0][0];
        u8ExtNum = sizeof(m_au8NES_ExtFileName)/EXT_FILENAME_SIZE;
        break;
#endif //#if ENABLE_MPLAYER_PLUGIN
    default:
        pu8MediaTypeName = NULL;
        u8ExtNum = 0;
    }

    for(i=0;i<u8ExtNum;i++)
    {
        for(j=0;j<EXT_FILENAME_SIZE;j++)
        {
            if(toupper(pu8ExtName[j]) != pu8MediaTypeName[j])
            {
                break;
            }
        }
        if(j >= EXT_FILENAME_SIZE)
        {
            return TRUE;
        }
        pu8MediaTypeName += EXT_FILENAME_SIZE;
    }

    return FALSE;
}

#if ENABLE_DVD
static BOOLEAN _MApp_IsRootIFO_File(FileEntry *pFileEntry)
{
    U8 u8Len;
    U16 u16LongFileName[FILE_INFO_LONG_FILENAME_SIZE >> 1];
    U8 *u8FileName = (U8 *)u16LongFileName;

    // Get long file name from file entry.
    u8Len = MApp_FileBrowser_GetLongFileNameByFileEntry(
                    pFileEntry,
                    (U32)(&u8FileName[0]),
                    (FILE_INFO_LONG_FILENAME_SIZE/2-1));
    u8Len = (u8Len > (FILE_INFO_LONG_FILENAME_SIZE/2-1)) ?
                    FILE_INFO_LONG_FILENAME_SIZE/2-1: u8Len;
    u8FileName[u8Len*2] = 0;
    u8FileName[u8Len*2+1] = 0;
    FS_Unicode2ASCII(&u16LongFileName[0]);
    if (strncmp((char *)u8FileName, "VIDEO_TS", 8) == 0)
        return TRUE;
    else
        return FALSE;
}
#endif

static BOOLEAN _MApp_MPlayer_MapDriveToPhysicalDevice(void)
{
    U8 u8DeviceIdx;
    U8 u8LunIdx;
    U8 u8PartitionIdx;
    U8 u8DriveNum;
    U8 u8IndexEnd = MSD_USB_4_INDEX_END;

    u8DriveNum = 0;
    memset(m_DriveInfo, 0, sizeof(MPlayerDrive)*NUM_OF_MAX_DRIVE);
    for(u8DeviceIdx=0;u8DeviceIdx<NUM_OF_SUPPORT_DEVICES;u8DeviceIdx++)
    {
        // 1. Check lun is valid.
        for(u8LunIdx=0;u8LunIdx<u8IndexEnd;u8LunIdx++)
        {
            for(u8PartitionIdx=0;
                u8PartitionIdx<NUM_OF_MAX_DRIVE;
                u8PartitionIdx++)
            {
                if(DRIVE_IS_VALID(u8DeviceIdx, 0, u8LunIdx, u8PartitionIdx))
                {
                    m_DriveInfo[u8DriveNum].eDeviceType =
                        m_MPlayerDeviceStatus[u8DeviceIdx].eDeviceType;
                    m_DriveInfo[u8DriveNum].u8DeviceAddr = 0;
                    m_DriveInfo[u8DriveNum].u8Lun = u8LunIdx;
                    m_DriveInfo[u8DriveNum].u8Partition = u8PartitionIdx;
                    u8DriveNum++;
                }
            }
        }
    }
    #if 0
    {
        U8 i;
        for(i=0; i<16; i++)
        {
            printf("[DriveInfo] USB%bu. LUN%bu -- Partition%bu\n", (U8)m_DriveInfo[i].eDeviceType, m_DriveInfo[i].u8Lun, m_DriveInfo[i].u8Partition);
        }
    }
    #endif
    if(u8DriveNum != m_u8TotalDriveNum)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

static void _MApp_MPlayer_Browser_ChangeBrowsingEnv(U8 u8BrowserHandle)
{
    MApp_FileBrowser_SetEnvironment(u8BrowserHandle);
}

// change the browser to different drive
static BOOLEAN _MApp_MPlayer_Browser_ChangeBrowsingDrive(U8 *pu8BrowserHandle, U8 u8OldDriveIdx, U8 u8NewDriveIdx)
{
    BOOLEAN bRet = TRUE;

    if (*pu8BrowserHandle != INVALID_BROWSER_HANDLE)
    {
        MApp_FileBrowser_Destroy(*pu8BrowserHandle);
    }

    *pu8BrowserHandle = MApp_FileBrowser_Create(u8NewDriveIdx);
    if (*pu8BrowserHandle == INVALID_BROWSER_HANDLE)
    {
        *pu8BrowserHandle = MApp_FileBrowser_Create(u8OldDriveIdx);
        bRet = FALSE;
    }

    return bRet;
}

static void _MApp_MPlayer_Browser_FirstEntry(void)
{
    MApp_FileBrowser_ToFirstEntryInCurrentDirectory();
}

static void _MApp_MPlayer_Browser_SaveCurFileInfo(U16 u16FileIdx, U16 u16PhyIdx, U32 u32PhyBufferAddr)
{
    MPlayerFileInfo fileInfo;
    MPlayerFileInfo *pFileInfo;
    DirEntryStruct * pCurrentDirEntry;
//    U8 *pu8Short;
//    BOOLEAN bLongSameAsShort;
//    S16 i;
    U32 u32Addr;
    U8 u8FileNameLen;

    memset(&fileInfo, 0, sizeof(fileInfo));//remove klocwork warning message
    pCurrentDirEntry = MApp_FileBrowser_GetCurrentDirEntry();
    //remove klocwork warning message
    if(pCurrentDirEntry == NULL)
    {
        __ASSERT(0);
        return;
    }
//    UNUSED(pu8Short);
//    UNUSED(bLongSameAsShort);
//    UNUSED(i);
    // Save file entry for file name.
#if (HIGH_SPEED_BROWSER)
    MApp_FileBrowser_GetCurrentFileEntry(&fileInfo.fileEntry);
#endif // #if (HIGH_SPEED_BROWSER)
    u8FileNameLen = MApp_FileBrowser_GetCurrentLongName(
                        (U32)(&fileInfo.u8LongFileName[0]),
                        (FILE_INFO_LONG_FILENAME_SIZE/2-1));
    u8FileNameLen = (u8FileNameLen > (FILE_INFO_LONG_FILENAME_SIZE/2-1)) ?
                    FILE_INFO_LONG_FILENAME_SIZE/2-1:
                    u8FileNameLen;
    fileInfo.u8LongFileName[u8FileNameLen*2] = 0;
    fileInfo.u8LongFileName[u8FileNameLen*2+1] = 0;

    fileInfo.eAttribute = (enumFileAttribute)pCurrentDirEntry->u8DirEntryAttrib;
    fileInfo.u64FileSize = MApp_FileBrowser_GetCurrentLength_LongLong();

    fileInfo.u16Year = FS_GET_YEAR (pCurrentDirEntry->u16DirEntryDate);
    fileInfo.u8Month = FS_GET_MONTH(pCurrentDirEntry->u16DirEntryDate);
    fileInfo.u8Day   = FS_GET_DAY  (pCurrentDirEntry->u16DirEntryDate);

    fileInfo.u8Hour   = FS_GET_HOUR(pCurrentDirEntry->u16DirEntryTime);
    fileInfo.u8Minute = FS_GET_MIN (pCurrentDirEntry->u16DirEntryTime);
    fileInfo.u8Second = FS_GET_SEC (pCurrentDirEntry->u16DirEntryTime);

#if (ENABLE_MPLAYER_SORT)
    fileInfo.u16PhyIndex = u16PhyIdx;
#else
    UNUSED(u16PhyIdx);
#endif

    if(E_MPLAYER_FILE_DIRECTORY & fileInfo.eAttribute)
    {
        memset(fileInfo.u8ExtFileName, ' ', 3);
        fileInfo.u8ExtFileName[3] = '\0';
    }
    else
    {
        memcpy(fileInfo.u8ExtFileName, pCurrentDirEntry->ps8DirEntryExtName, 3);
        fileInfo.u8ExtFileName[3] = 0;
    }

    fileInfo.bLongFileNameValid = TRUE;

    u32Addr = u32PhyBufferAddr + (U32)u16FileIdx*sizeof(MPlayerFileInfo);

    pFileInfo = (MPlayerFileInfo *)_PA2VA(u32Addr);
    memcpy(pFileInfo, &fileInfo, sizeof(MPlayerFileInfo));

}

static void _MApp_MPlayer_Browser_SetSelected(U16 u16FileIdx, BOOLEAN bSelect)
{
    MPlayerFileInfo *pFileInfo;
    U32 u32Addr;

    u32Addr = (U32)((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR)) + (U32)u16FileIdx*sizeof(MPlayerFileInfo);

    pFileInfo = (MPlayerFileInfo *)_PA2VA(u32Addr);
    //modify file attribute in filter area of file buffer.
    //filter area = the front of 1/2 file buffer.
    if(bSelect)
    {
        pFileInfo->eAttribute |= E_MPLAYER_FILE_SELECT;
    }
    else
    {
        Remove_enumFileAttribute(pFileInfo->eAttribute, E_MPLAYER_FILE_SELECT);
    }
}

static BOOLEAN _MApp_MPlayer_Browser_IsInPlayingList(enumMPlayerMediaType eType, U16 u16FileIdx)
{
    U16 i = 0;
    U16 j = 0;
    BOOLEAN bMatched = FALSE;
    MPlayerPlayListInfo *pstPlayListInfo;
    U16 u16PlayListNum;
    U32 u32XdataWindowBase;

    //pstPlayListInfo = (MPlayerPlayListInfo xdata *)msAPI_MIU_GetW1StartAddress();
    u16PlayListNum = m_u16SelectedFileNum[eType];

    if(_MApp_MPlayer_GetPlayListAddressByMediaType(eType, &u32XdataWindowBase)==FALSE)
    {
        goto _MApp_MPlayer_Browser_IsInPlayingList_END;
    }

    pstPlayListInfo = (MPlayerPlayListInfo *) (_PA2VA(u32XdataWindowBase));

#if ENABLE_MPLAYER_SORT
    m_u16CurDirectoryPhy[m_u16CurDirectoryDepth] = u16FileIdx-m_u16DirectoryNum[m_u16CurDirectoryDepth];
#else
    m_u16CurDirectory[m_u16CurDirectoryDepth] = u16FileIdx-m_u16DirectoryNum[m_u16CurDirectoryDepth];
#endif

    for(i=0;i<u16PlayListNum;i++)
    {
        bMatched = TRUE;

        if (PLAY_LIST_DRIVE(i) != m_u16CurDriveIdx)
        {
            bMatched = FALSE;
        }
    #if ENABLE_MPLAYER_SORT
        else if(PLAY_LIST_PATH(i, m_u16CurDirectoryDepth) != m_u16CurDirectoryPhy[m_u16CurDirectoryDepth])
    #else
        else if(PLAY_LIST_PATH(i, m_u16CurDirectoryDepth) != m_u16CurDirectory[m_u16CurDirectoryDepth])
    #endif
        {
            bMatched = FALSE;
        }
        else
        {
            for(j=0;j<NUM_OF_MAX_DIRECTORY_DEPTH+1;j++)
            {
            #if ENABLE_MPLAYER_SORT
                if(PLAY_LIST_PATH(i, j) != m_u16CurDirectoryPhy[j])
            #else
                if(PLAY_LIST_PATH(i, j) != m_u16CurDirectory[j])
            #endif
                {
                    bMatched = FALSE;
                }
            }
        }

        if(bMatched==TRUE)
        {
            goto _MApp_MPlayer_Browser_IsInPlayingList_END;
        }
    }

_MApp_MPlayer_Browser_IsInPlayingList_END:
#if 0
    printf("3:Selected File number %u\n", u16PlayListNum);
    printf("Target, Drive: %u, Path: %d, %d, %d, %d\n", m_u16CurDriveIdx, m_u16CurDirectory[0], m_u16CurDirectory[1], m_u16CurDirectory[2], m_u16CurDirectory[4]);
    for(i=0;i<u16PlayListNum;i++)
    {
        pstPlayListInfo = (MPlayerPlayListInfo *)(u32XdataWindowBase + i * sizeof(MPlayerPlayListInfo));
        printf("3:Selected File Drive %u (= %c)\n", PLAY_LIST_DRIVE(i), (U8)PLAY_LIST_DRIVE(i) + 'C');
        printf("3:Selected File Path %d %d %d %d\n",
               PLAY_LIST_PATH(i, 0), PLAY_LIST_PATH(i, 1),
               PLAY_LIST_PATH(i, 2), PLAY_LIST_PATH(i, 3));
    }
    printf("\n");
#endif

#if ENABLE_MPLAYER_SORT
    m_u16CurDirectoryPhy[m_u16CurDirectoryDepth] = MPLAYER_INVALID_INDEX;
#else
    m_u16CurDirectory[m_u16CurDirectoryDepth] = MPLAYER_INVALID_INDEX;
#endif

    return bMatched;
}

static U16 _MApp_MPlayer_Browser_QueryPlayingList(enumMPlayerMediaType eType, U16 u16FileIdx)
{
    U16 i = 0;
    U16 j = 0;
    U16 u16Index = MPLAYER_INVALID_INDEX;
    BOOLEAN bMatched = FALSE;
    MPlayerPlayListInfo *pstPlayListInfo;
    U16 u16PlayListNum;
    U32 u32XdataWindowBase;

    //pstPlayListInfo = (MPlayerPlayListInfo xdata *)msAPI_MIU_GetW1StartAddress();
    u16PlayListNum = m_u16SelectedFileNum[eType];

    if(_MApp_MPlayer_GetPlayListAddressByMediaType(eType, &u32XdataWindowBase)==FALSE)
    {
        goto _MApp_MPlayer_Browser_IsInPlayingList_END;
    }

    pstPlayListInfo = (MPlayerPlayListInfo *) (_PA2VA(u32XdataWindowBase));

#if ENABLE_MPLAYER_SORT
    m_u16CurDirectoryPhy[m_u16CurDirectoryDepth] = u16FileIdx-m_u16DirectoryNum[m_u16CurDirectoryDepth];
#else
    m_u16CurDirectory[m_u16CurDirectoryDepth] = u16FileIdx-m_u16DirectoryNum[m_u16CurDirectoryDepth];
#endif

    for(i=0;i<u16PlayListNum;i++)
    {
        bMatched = TRUE;

        if (PLAY_LIST_DRIVE(i) != m_u16CurDriveIdx)
        {
            bMatched = FALSE;
        }
    #if ENABLE_MPLAYER_SORT
        else if(PLAY_LIST_PATH(i, m_u16CurDirectoryDepth) != m_u16CurDirectoryPhy[m_u16CurDirectoryDepth])
    #else
        else if(PLAY_LIST_PATH(i, m_u16CurDirectoryDepth) != m_u16CurDirectory[m_u16CurDirectoryDepth])
    #endif
        {
            bMatched = FALSE;
        }
        else
        {
            for(j=0;j<NUM_OF_MAX_DIRECTORY_DEPTH+1;j++)
            {
            #if ENABLE_MPLAYER_SORT
                if(PLAY_LIST_PATH(i, j) != m_u16CurDirectoryPhy[j])
            #else
                if(PLAY_LIST_PATH(i, j) != m_u16CurDirectory[j])
            #endif
                {
                    bMatched = FALSE;
                }
            }
        }

        if(bMatched==TRUE)
        {
            u16Index = i;
            goto _MApp_MPlayer_Browser_IsInPlayingList_END;
        }
    }

_MApp_MPlayer_Browser_IsInPlayingList_END:

#if ENABLE_MPLAYER_SORT
    m_u16CurDirectoryPhy[m_u16CurDirectoryDepth] = MPLAYER_INVALID_INDEX;
#else
    m_u16CurDirectory[m_u16CurDirectoryDepth] = MPLAYER_INVALID_INDEX;
#endif

    return u16Index;
}

#if STORE_SUBTITLE_ENTRY_TO_SUBTITLE_BUFFER
//******************************************************************************
/// Determine input extension name is subtitle or not.
/// @param  pu8ExtName \b IN Specify extension name
/// @return TRUE/FALSE.
//******************************************************************************
static BOOLEAN _MApp_MPlayer_IsSubtitleFile(U8 *pu8ExtName)
{
    if(pu8ExtName == NULL)
    {
        return FALSE;
    }

    U8 i;
    for(i=0;i<E_MPLAYER_SUBTITLE_NUM;i++)
    {
        if(memcmp(pu8ExtName,
                  &m_pu8SubtitleFileExt[i],
                  EXT_FILENAME_SIZE) == 0)
        {
            return TRUE;
        }
    }
    return FALSE;
}
#endif

static BOOLEAN _MApp_MPlayer_IsSpecifyMediaType(enumMPlayerMediaType eMediaType, U8 *pu8ExtName)
{
    if(pu8ExtName == NULL || eMediaType >= E_MPLAYER_TYPE_NUM)
    {
        return FALSE;
    }

    if( 0
              #if ENABLE_MPLAYER_PHOTO
       || ((eMediaType == E_MPLAYER_TYPE_PHOTO) && IS_PHOTO_FILE(pu8ExtName))
              #endif
              #if ENABLE_MPLAYER_MUSIC
       || ((eMediaType == E_MPLAYER_TYPE_MUSIC) && IS_MUSIC_FILE(pu8ExtName))
              #endif  // #if ENABLE_MPLAYER_MUSIC
              #if ENABLE_MPLAYER_MOVIE
       || ((eMediaType == E_MPLAYER_TYPE_MOVIE) && IS_MOVIE_FILE(pu8ExtName))
              #endif  // #if ENABLE_MPLAYER_MOVIE
              #if ENABLE_MPLAYER_TEXT
       || ((eMediaType == E_MPLAYER_TYPE_TEXT) && IS_TXT_FILE(pu8ExtName))
              #endif  // #if ENABLE_MPLAYER_TEXT
              #if ENABLE_MPLAYER_PLUGIN
       || ((eMediaType == E_MPLAYER_TYPE_PLUGIN) && IS_NES_FILE(pu8ExtName))
              #endif //#if ENABLE_MPLAYER_PLUGIN
              #if ENABLE_MPLAYER_MIXED
       || ((eMediaType == E_MPLAYER_TYPE_MIXED) && (IS_PHOTO_FILE(pu8ExtName)||IS_MUSIC_FILE(pu8ExtName)||IS_MOVIE_FILE(pu8ExtName)||IS_TXT_FILE(pu8ExtName)))
              #endif //#if ENABLE_MPLAYER_MIXED
    )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static BOOLEAN _MApp_MPlayer_Browser_EnumCurDirectory(void)
{
    #define FILE_BUFFER ((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR))
    #define MUSIC_BUFFER ((MPLAYER_MUSIC_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_MUSIC_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_MUSIC_FILE_BUFFER_ADR))
    #define SUBTITLE_BUFFER MPLAYER_SUBTITLE_FILE_BUFFER_ADR

    DirEntryStruct * pCurrentDirEntry   = NULL;     //global current dir entry
    FileEntry fileEntry;

    memset(&fileEntry, 0, sizeof(FileEntry));

#if (HIGH_SPEED_BROWSER)
    U16 u16FileIdx;
    U16 u16PlayListIdx;
    U16 u16DirCnt=0, u16Depth;
    U16 u16FileCnt=0, u16MediaFileCnt;
    BOOLEAN bNeedRead = FALSE;
    #define extName     pFileInfo->u8ExtFileName

    MPLAYER_DBG(printf("_MApp_MPlayer_Browser_EnumCurDirectory, m_u16CurDirectoryDepth=%d\n", m_u16CurDirectoryDepth););

#ifdef ENABLE_PTP
    if (MApp_PTP_DeviceInUse())
    {
        _MApp_MPlayer_PTP_Browser_EnumCurDirectory();
        return;
    }
#endif

    // 0: Check whether change directory
    if(m_u16BufDirectoryDepth != m_u16CurDirectoryDepth)
    {
        bNeedRead = TRUE;
    }
    else
    {
        for(u16Depth=0;u16Depth<m_u16CurDirectoryDepth;u16Depth++)
        {
            if(m_u16BufDirectory[u16Depth] != m_u16CurDirectory[u16Depth])
            {
                bNeedRead = TRUE;
            }
        }
    }

    if(bNeedRead)
    {
        // 1. Read all files & directories.
        m_u16BufTotalFileNum = 0;
    #if DIRECTORY_BGM //ENABLE_BGM
        m_u16TotalBGMFileNum = 0;
    #endif
    #if STORE_SUBTITLE_ENTRY_TO_SUBTITLE_BUFFER
        m_u16TotalSubtitleFileNum = 0;
    #endif
        _MApp_MPlayer_Browser_FirstEntry();
        pCurrentDirEntry = MApp_FileBrowser_GetCurrentDirEntry();
        MApp_FileBrowser_GetCurrentFileEntry(&fileEntry);
        //If first file entry in folder is not DOT,it is abnormal case, return FALSE.
        if(fileEntry.EntryType != ENTRY_TYPE_DIR_DOT)
        {
            return FALSE;
        }

        while(pCurrentDirEntry && (m_u16BufTotalFileNum<NUM_OF_MAX_FILES_PER_DIRECTORY))
        {
            MApp_FileBrowser_GetCurrentFileEntry(&fileEntry);

#if HIDE_HIDDEN_FILE
            if(!(fileEntry.EntryAttrib & ENTRY_ATTRIB_HIDDEN) ||
                (fileEntry.EntryType == ENTRY_TYPE_DIR_DOT) ||
                (fileEntry.EntryType == ENTRY_TYPE_DIR_DOTDOT))
				{
#endif
//>>wht1203017_1
	     if((1 != MApp_MPlayer_QueryTotalDriveNum()) && (0 == MApp_MPlayer_QueryDirectoryDepth()))
	     {
			MApp_FileBrowser_GetCurrentFileEntry(&fileEntry);
			if(!(fileEntry.EntryAttrib & ENTRY_ATTRIB_HIDDEN) )
            {
                if(pCurrentDirEntry->u8DirEntryAttrib & ATTRIB_DIRECTORY)
                {
                    _MApp_MPlayer_Browser_SaveCurFileInfo(u16DirCnt+NUM_OF_MAX_FILES_PER_DIRECTORY, u16DirCnt, FILE_BUFFER);
                    u16DirCnt++;
                }
                else
                {
                    if(u16FileCnt < NUM_OF_MAX_FILES_PER_DIRECTORY - u16DirCnt)
                    {
                        if(_MApp_MPlayer_IsSpecifyMediaType(m_eMediaType, pCurrentDirEntry->ps8DirEntryExtName)==TRUE)
                        {
                            _MApp_MPlayer_Browser_SaveCurFileInfo(u16FileCnt, u16FileCnt, FILE_BUFFER);
                            u16FileCnt++;
                        }
                    }
                	#if DIRECTORY_BGM//ENABLE_BGM
                    if((m_eMediaType == E_MPLAYER_TYPE_PHOTO
                        #if ENABLE_MPLAYER_TEXT
                        ||m_eMediaType == E_MPLAYER_TYPE_TEXT
                        #endif
                        )
                    && m_u16TotalBGMFileNum<NUM_OF_MAX_FILES_PER_DIRECTORY
                    && _MApp_MPlayer_IsSpecifyMediaType(E_MPLAYER_TYPE_MUSIC, pCurrentDirEntry->ps8DirEntryExtName))
                    {
                        //Don't care physical index, so we set NULL.
                        _MApp_MPlayer_Browser_SaveCurFileInfo(m_u16TotalBGMFileNum, NULL, MUSIC_BUFFER);
                        m_u16TotalBGMFileNum++;
                    }
                	#endif
                	#if STORE_SUBTITLE_ENTRY_TO_SUBTITLE_BUFFER
                    if(m_eMediaType == E_MPLAYER_TYPE_MOVIE
                    && m_u16TotalSubtitleFileNum<NUM_OF_MAX_FILES_PER_DIRECTORY
                    && _MApp_MPlayer_IsSubtitleFile(pCurrentDirEntry->ps8DirEntryExtName))
                    {
                        //Don't care physical index, so we set NULL.
                        _MApp_MPlayer_Browser_SaveCurFileInfo(m_u16TotalSubtitleFileNum, NULL, SUBTITLE_BUFFER);
                        m_u16TotalSubtitleFileNum++;
                    }
                	#endif
                	}
					m_u16BufTotalFileNum++;	  
				}
		 }else{
			//printf("HIDE_HIDDEN_FILE  2\n ");
			MApp_FileBrowser_GetCurrentFileEntry(&fileEntry);
			if(!(fileEntry.EntryAttrib & ENTRY_ATTRIB_HIDDEN) &&
				(fileEntry.EntryType != ENTRY_TYPE_DIR_DOT))
			{
				if(pCurrentDirEntry->u8DirEntryAttrib & ATTRIB_DIRECTORY)
				{
					_MApp_MPlayer_Browser_SaveCurFileInfo(u16DirCnt+NUM_OF_MAX_FILES_PER_DIRECTORY, u16DirCnt, FILE_BUFFER);
					u16DirCnt++;
				}
				else
				{
					if(u16FileCnt < NUM_OF_MAX_FILES_PER_DIRECTORY - u16DirCnt)
                    {
                        if(_MApp_MPlayer_IsSpecifyMediaType(m_eMediaType, pCurrentDirEntry->ps8DirEntryExtName)==TRUE)
                        {
                            _MApp_MPlayer_Browser_SaveCurFileInfo(u16FileCnt, u16FileCnt, FILE_BUFFER);
                            u16FileCnt++;
                        }
                    }
                	#if DIRECTORY_BGM//ENABLE_BGM
                    if((m_eMediaType == E_MPLAYER_TYPE_PHOTO
                        #if ENABLE_MPLAYER_TEXT
                        ||m_eMediaType == E_MPLAYER_TYPE_TEXT
                        #endif
                        )
                    && m_u16TotalBGMFileNum<NUM_OF_MAX_FILES_PER_DIRECTORY
                    && _MApp_MPlayer_IsSpecifyMediaType(E_MPLAYER_TYPE_MUSIC, pCurrentDirEntry->ps8DirEntryExtName))
                    {
                        //Don't care physical index, so we set NULL.
                        _MApp_MPlayer_Browser_SaveCurFileInfo(m_u16TotalBGMFileNum, NULL, MUSIC_BUFFER);
                        m_u16TotalBGMFileNum++;
                    }
                	#endif
                	#if STORE_SUBTITLE_ENTRY_TO_SUBTITLE_BUFFER
                    if(m_eMediaType == E_MPLAYER_TYPE_MOVIE
                    && m_u16TotalSubtitleFileNum<NUM_OF_MAX_FILES_PER_DIRECTORY
                    && _MApp_MPlayer_IsSubtitleFile(pCurrentDirEntry->ps8DirEntryExtName))
                    {
                        //Don't care physical index, so we set NULL.
                        _MApp_MPlayer_Browser_SaveCurFileInfo(m_u16TotalSubtitleFileNum, NULL, SUBTITLE_BUFFER);
                        m_u16TotalSubtitleFileNum++;
                    }
                	#endif
                	}
				m_u16BufTotalFileNum++;	     
			}
		 }
#if HIDE_HIDDEN_FILE
            }
#endif
//<<wht1203017_1
            msAPI_Timer_ResetWDT();
            pCurrentDirEntry = MApp_FileBrowser_GetNextDirEntry(1);
        }
        u16FileCnt = MIN(u16FileCnt, NUM_OF_MAX_FILES_PER_DIRECTORY-u16DirCnt);
        m_u16BufTotalFileNum = u16DirCnt + u16FileCnt;
        m_u16DirectoryNum[m_u16CurDirectoryDepth] = u16DirCnt;
        m_u16BufDirectoryNum = u16DirCnt;

        if(u16FileCnt>0)
        {
            // Copy files from top FILE_BUFFER to bottom FILE_BUFFER, and put files behind directories.
            memcpy((void*)_PA2VA(((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR))+
                           ((U32)u16DirCnt+(U32)NUM_OF_MAX_FILES_PER_DIRECTORY)*sizeof(MPlayerFileInfo)),
                    (void*)_PA2VA((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR)),
                    (U32)sizeof(MPlayerFileInfo)*u16FileCnt);
        }

        // Copy directories and files from bottom FILE_BUFFER to top FILE_BUFFER(without sort).
        memcpy((void*)_PA2VA((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR)),
               (void*)_PA2VA(((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR))+
                       (U32)NUM_OF_MAX_FILES_PER_DIRECTORY*sizeof(MPlayerFileInfo)),
                       (U32)sizeof(MPlayerFileInfo)*m_u16BufTotalFileNum);


        m_u16BufDirectoryDepth = m_u16CurDirectoryDepth;
        for(u16Depth=0;u16Depth<m_u16CurDirectoryDepth;u16Depth++)
        {
        #if ENABLE_MPLAYER_SORT
            m_u16BufDirectory[u16Depth] = m_u16CurDirectoryPhy[u16Depth];
        #else
            m_u16BufDirectory[u16Depth] = m_u16CurDirectory[u16Depth];
        #endif
        }
        m_u16BufDirectory[m_u16CurDirectoryDepth] = MPLAYER_INVALID_INDEX;
    }

    // Enumerate files.
#if (ENABLE_MPLAYER_SORT)
    #if ENABLE_MPLAYER_SORT_EX
        _MApp_MPlayer_SortDirAndMove_EX(m_u16BufDirectoryNum);
        u16MediaFileCnt = _MApp_MPlayer_SortFileAndMove_EX(m_u16BufDirectoryNum, m_u16BufTotalFileNum);
    #else
        _MApp_MPlayer_SortDirAndMove(m_u16BufDirectoryNum);
        u16MediaFileCnt = _MApp_MPlayer_SortFileAndMove(m_u16BufDirectoryNum, m_u16BufTotalFileNum);
    #endif
#else
    u16MediaFileCnt = m_u16BufTotalFileNum - m_u16BufDirectoryNum;
#endif
    m_u16DirectoryNum[m_u16CurDirectoryDepth] = m_u16BufDirectoryNum;
    m_u16TotalFileNum = u16MediaFileCnt + m_u16BufDirectoryNum;
    m_u16BufReadLongNameIdx = 0;

    // Set selected files.
    for(u16FileIdx=m_u16BufDirectoryNum;
        u16FileIdx<m_u16TotalFileNum;
        u16FileIdx++)
    {
        u16PlayListIdx = _MApp_MPlayer_Browser_QueryPlayingList(m_eMediaType, u16FileIdx);
        if(u16PlayListIdx != MPLAYER_INVALID_INDEX)
        {
            _MApp_MPlayer_Browser_SetSelected(u16FileIdx, TRUE);
            // If the file in play list is decoded fail, set the file in FILE_BUFFER
            if(MApp_MPlayer_GetFileDecodedFail(u16PlayListIdx,m_eMediaType,E_MPLAYER_PLAY_SELECTED))
            {
                MApp_MPlayer_SetFileDecodedFail(u16FileIdx,TRUE,m_eMediaType,E_MPLAYER_PLAY_ONE_DIRECTORY);
            }
        }
        msAPI_Timer_ResetWDT();
    }
#else
    #define extName     pCurrentDirEntry->ps8DirEntryExtName
    m_u16TotalFileNum = 0;

    // Directory Browsing ----------------------------------------------------
    _MApp_MPlayer_Browser_FirstEntry();
    pCurrentDirEntry = MApp_FileBrowser_GetCurrentDirEntry();
    MApp_FileBrowser_GetCurrentFileEntry(&fileEntry);
    if(fileEntry.EntryType != ENTRY_TYPE_DIR_DOT)
    {
        return FALSE;
    }
    while(pCurrentDirEntry && (m_u16TotalFileNum<NUM_OF_MAX_FILES_PER_DIRECTORY))
    {
        if(pCurrentDirEntry->u8DirEntryAttrib & ATTRIB_DIRECTORY)
        {
            //Don't care physical index, so we set NULL.
            _MApp_MPlayer_Browser_SaveCurFileInfo(m_u16TotalFileNum, NULL, FILE_BUFFER);
            m_u16TotalFileNum++;
        }

        pCurrentDirEntry = MApp_FileBrowser_GetNextDirEntry(1);
    }
    m_u16DirectoryNum[m_u16CurDirectoryDepth] = m_u16TotalFileNum;
    // End of Directory Browsing ----------------------------------------------------

    // File Browsing ---------------------------------------------
    if(m_u16TotalFileNum<NUM_OF_MAX_FILES_PER_DIRECTORY)
    {
        _MApp_MPlayer_Browser_FirstEntry();
        pCurrentDirEntry = MApp_FileBrowser_GetCurrentDirEntry();
        while(pCurrentDirEntry &&
              (m_u16TotalFileNum<NUM_OF_MAX_FILES_PER_DIRECTORY))
        {
            if(!(pCurrentDirEntry->u8DirEntryAttrib & ATTRIB_DIRECTORY))
            {
                if( 0
#if ENABLE_MPLAYER_PHOTO
                   || ((m_eMediaType == E_MPLAYER_TYPE_PHOTO) && IS_PHOTO_FILE(extName))
#endif
#if ENABLE_MPLAYER_MUSIC
                   || ((m_eMediaType == E_MPLAYER_TYPE_MUSIC) && IS_MUSIC_FILE(extName))
#endif  // #if ENABLE_MPLAYER_MUSIC
#if ENABLE_MPLAYER_MOVIE
                   || ((m_eMediaType == E_MPLAYER_TYPE_MOVIE) && IS_MOVIE_FILE(extName))
#endif  // #if ENABLE_MPLAYER_MOVIE
#if ENABLE_MPLAYER_TEXT
                   || ((m_eMediaType == E_MPLAYER_TYPE_TEXT) && IS_TXT_FILE(extName))
#endif  // #if ENABLE_MPLAYER_TEXT
                  )
                {
                    // Let the last 3 character be extension name
                    //Don't care physical index, so we set NULL.
                    _MApp_MPlayer_Browser_SaveCurFileInfo(m_u16TotalFileNum, NULL, FILE_BUFFER);
                    if(_MApp_MPlayer_Browser_IsInPlayingList(m_eMediaType, m_u16TotalFileNum))
                    {
                        _MApp_MPlayer_Browser_SetSelected(m_u16TotalFileNum, TRUE);
                    }
                    m_u16TotalFileNum++;
                }
            }

            pCurrentDirEntry = MApp_FileBrowser_GetNextDirEntry(1);
        }
        // End of File Browsing ---------------------------------------------
    }
#endif  // #if (HIGH_SPEED_BROWSER)

    MPLAYER_DBG(printf("m_u16TotalFileNum = %x\n", m_u16TotalFileNum));
    return TRUE;
}

static BOOLEAN _MApp_MPlayer_Browser_FindNextDirectory(U16 u16Count)
{
//    DirEntryStruct * pNextDirEntry      = NULL;
    DirEntryStruct * pCurrentDirEntry   = NULL;

    pCurrentDirEntry = MApp_FileBrowser_GetCurrentDirEntry();
    u16Count++;  // If u8Count == 0, means to find the 1st directory.
    while(pCurrentDirEntry)
    {
#if HIDE_HIDDEN_FILE
        FileEntry fileEntry;
        memset(&fileEntry, 0, sizeof(FileEntry));

        MApp_FileBrowser_GetCurrentFileEntry(&fileEntry);
        if((pCurrentDirEntry->u8DirEntryAttrib & ATTRIB_DIRECTORY) &&
           (!(fileEntry.EntryAttrib & ENTRY_ATTRIB_HIDDEN) ||
             (fileEntry.EntryType == ENTRY_TYPE_DIR_DOT) ||
             (fileEntry.EntryType == ENTRY_TYPE_DIR_DOTDOT)))
#else
        if(pCurrentDirEntry->u8DirEntryAttrib & ATTRIB_DIRECTORY)
#endif
        {
            u16Count--;
            if(u16Count == 0)
            {
                break;
            }
        }
        pCurrentDirEntry = MApp_FileBrowser_GetNextDirEntry(1);
    }

    if(pCurrentDirEntry)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static void _MApp_MPlayer_Change2CurrentDirectory(void)
{
    U16 i;

#ifdef ENABLE_PTP
    return;
#endif

    // Change to the root directory.
    MApp_FileBrowser_ChangeToRootDirectory();
    for(i=0;i<m_u16CurDirectoryDepth;i++)
    {
        // Go to the 1st entry.
        _MApp_MPlayer_Browser_FirstEntry();
#if (ENABLE_MPLAYER_SORT)
        //U16 u16Idx;

        //u16Idx = _MApp_MPlayer_LookupPhysicalIndex(m_u16CurDirectory[i]);
        if(_MApp_MPlayer_Browser_FindNextDirectory(m_u16CurDirectoryPhy[i]) == TRUE)
#else
        if(_MApp_MPlayer_Browser_FindNextDirectory(m_u16CurDirectory[i]) == TRUE)
#endif
        {
            MApp_FileBrowser_EnterDirectory(0);
        }
        else
        {
            break;
        }
    }

    // Go to the 1st entry.
    _MApp_MPlayer_Browser_FirstEntry();
}

#ifdef MEDIA_PLAYER_HIGHLIGHT_CHANGE
static void _MApp_MPlayer_Change2TargetDirectory(U16 depth, U16 *dir)
{
#if ENABLE_MPLAYER_SORT
    U16 i;
    BOOLEAN bMatch = TRUE;

    if(m_u16CurDirectoryDepth != depth)
    {
        bMatch = FALSE;
    }
    else
    {
        for(i=0;i<depth;i++)
        {
            if(m_u16CurDirectoryPhy[i] != dir[i])
                bMatch = FALSE;
        }
    }

    if(bMatch==TRUE)
        return;

    // Change to the root directory.
    MApp_FileBrowser_ChangeToRootDirectory();

    for(i=0;i<NUM_OF_MAX_DIRECTORY_DEPTH+1;i++)
    {
        m_u16BufDirectory[i] = MPLAYER_INVALID_INDEX;
        m_u16CurDirectoryPhy[i] = MPLAYER_INVALID_INDEX;
    }

    m_u16CurDirectoryDepth = 0;
    m_u16BufDirectoryDepth = MPLAYER_INVALID_INDEX;
    m_u16BufReadLongNameIdx = MPLAYER_INVALID_INDEX;
    memset(m_u16DirectoryNum, 0, sizeof(U16)*NUM_OF_MAX_DIRECTORY_DEPTH);

    _MApp_MPlayer_Browser_EnumCurDirectory();

    for(i=0;i<depth;i++)
    {
        // Go to the 1st entry.
        _MApp_MPlayer_Browser_FirstEntry();

        if(_MApp_MPlayer_Browser_FindNextDirectory(dir[i]) == TRUE)
        {
            MApp_FileBrowser_EnterDirectory(0);
            m_u16CurDirectoryPhy[m_u16CurDirectoryDepth] = dir[i];
            m_u16CurDirectoryDepth++;
            _MApp_MPlayer_Browser_EnumCurDirectory();
        }
        else
        {
            break;
        }
    }
    m_u16CurFileIdx = 0;
    m_u16CurPage1stFileIdx = 0;
    m_u16CurPageIdx =0;

    if(m_u16TotalFileNum && m_u16FilesPerPage>0)
    {
        m_u16TotalPageNum = (m_u16TotalFileNum+m_u16FilesPerPage-1) /m_u16FilesPerPage;
    }

    // Go to the 1st entry.
    _MApp_MPlayer_Browser_FirstEntry();

#else
    U16 i;

    // Change to the root directory.
    MApp_FileBrowser_ChangeToRootDirectory();

    for(i=0;i<NUM_OF_MAX_DIRECTORY_DEPTH+1;i++)
    {
        m_u16CurDirectory[i] = MPLAYER_INVALID_INDEX;
        m_u16BufDirectory[i] = MPLAYER_INVALID_INDEX;
    }

    m_u16CurDirectoryDepth = 0;
    m_u16BufDirectoryDepth = MPLAYER_INVALID_INDEX;
    m_u16BufReadLongNameIdx = MPLAYER_INVALID_INDEX;
    memset(m_u16DirectoryNum, 0, sizeof(U16)*NUM_OF_MAX_DIRECTORY_DEPTH);
    m_u16CurFileIdx = 0;

    _MApp_MPlayer_Browser_EnumCurDirectory();

    m_u16CurPage1stFileIdx = 0;
    m_u16CurPageIdx =0;

    if(m_u16TotalFileNum && m_u16FilesPerPage>0)
    {
        m_u16TotalPageNum = (m_u16TotalFileNum+m_u16FilesPerPage-1) /m_u16FilesPerPage;
    }

    for(i=0;i<depth;i++)
    {
        m_u16CurFileIdx = dir[i];
        MApp_MPlayer_EnterDirectory(E_MPLAYER_INDEX_CURRENT_DIRECTORY, dir[i]);
    }

    // Go to the 1st entry.
    _MApp_MPlayer_Browser_FirstEntry();
#endif
}

//******************************************************************************
/// Query current directory path
/// @param  depth \b IN  Specify the target directory depth.
/// @param  dir \b IN  Specify the desire directory depth for each node.
/// @return TRUE or FALSE
//******************************************************************************
BOOLEAN MApp_MPlayer_Change2TargetDirectory(U16 u16DriveIdx, U16 *dir, U16 depth)
{
    if (u16DriveIdx != m_u16CurDriveIdx)
    {
        if(MApp_MPlayer_ConnectDrive(u16DriveIdx) == E_MPLAYER_RET_FAIL)
        {
            return FALSE;
        }
    }

    _MApp_MPlayer_Change2TargetDirectory(depth,dir);

    //_MApp_MPlayer_Browser_EnumCurDirectory();
    m_u16CurFileIdx = 0;
    m_u16CurPage1stFileIdx = 0;
    m_u16CurPageIdx =0;

    if(m_u16TotalFileNum && m_u16FilesPerPage>0)
    {
        m_u16TotalPageNum = (m_u16TotalFileNum+m_u16FilesPerPage-1) /m_u16FilesPerPage;
    }

    return TRUE;
}
#endif

#if ENABLE_BGM
//This function will be called while playing music.
//In music mode, need to move directories and files from top FILE_BUFFER to top MUSIC_FILE_BUFFER.
//In photo/text mode, it is BGM mode, the music files are already in MUSIC_FILE_BUFFER.
//In movie mode, music shoule not be played.
void _MApp_MPlayer_StoreMusicFileInCurDirectory(void)
{
    if(m_eMediaType == E_MPLAYER_TYPE_MUSIC)
    {
        if(m_u16TotalFileNum > 0)
        {
            // Copy directories and files from top FILE_BUFFER to top MUSIC_FILE_BUFFER(already sorted).
            memcpy((void*)_PA2VA(((MPLAYER_MUSIC_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_MUSIC_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_MUSIC_FILE_BUFFER_ADR))),
                   (void*)_PA2VA(((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR))),
                   (U32)sizeof(MPlayerFileInfo)*m_u16TotalFileNum);
        }

        m_u16TotalMusicFileNum = m_u16TotalFileNum;
        m_u16CurMusicDirectoryNumber = m_u16DirectoryNum[m_u16CurDirectoryDepth];
        m_u16RealMusicFileNum = m_u16TotalMusicFileNum - m_u16CurMusicDirectoryNumber;
    }
    else
    {
        m_u16CurMusicDirectoryNumber = 0;
        m_u16TotalMusicFileNum = m_u16RealMusicFileNum = m_u16TotalBGMFileNum;
    }
}

enumMPlayerRet _MApp_MPlayer_GetMusicFileInfo(U16 u16Idx, MPlayerFileInfo *pInfo)
{
    U32 u32Addr;
    MPlayerFileInfo *pFileInfo;

    if(u16Idx >= m_u16TotalMusicFileNum)
    {
        return E_MPLAYER_RET_FAIL;
    }

    u32Addr = (U32)((MPLAYER_MUSIC_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_MUSIC_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_MUSIC_FILE_BUFFER_ADR))+(U32)u16Idx*sizeof(MPlayerFileInfo);

    pFileInfo = (MPlayerFileInfo *)_PA2VA(u32Addr);

    _MApp_MPlayer_GetLongFileName(pFileInfo);

    memcpy(pInfo, pFileInfo, sizeof(MPlayerFileInfo));

    return E_MPLAYER_RET_OK;
}

U16 MAPP_MPlayer_GetMusicTotalFileNum(void)
{
    return m_u16RealMusicFileNum;
}
#endif

#if (ENABLE_SUBTITLE_SUBIDX)
#if (ENABLE_SMALL_BUF_SUBTITLE==0)
static BOOLEAN _MApp_MPlayer_PushSubtitleSUB(void)
{
    #define READ_BUF_SIZE   EXTERNAL_IMAGE_SUBTITLE_READ_BUFFER_SIZE
#if ENABLE_INTERNAL_AND_EXTERNAL_SUBTITLE
    #define READ_BUF_ADR            EXTERNAL_IMAGE_SUBTITLE_READ_BUFFER_ADR
#else
    #define READ_BUF_ADR            (((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))+MP4_SUBTITLE_BUFFER_LEN/2)
#endif
    U32 u32SubtitleBuff=0;
    U8 *pu8Data;
    U16 *pu16Data;
    U16 u16DataIdx;
    BOOLEAN bRet=FALSE;
    U16 u16PacketLen;
    U16 u16HeaderLen, u16CopyLen;
    U16 u16SubtitleLen, u16SubtitleLenAligned, u16SubtitleDstPos;
    U32 u32ReadBufAddr;

    u16SubtitleLen = 0;
    if((m_u8ExternalSubtitleFileHandle != FCTRL_INVALID_FILE_HANDLE) &&
       (MApp_MPlayer_GetSubtitleTagByIdx(&m_Subtitle_Tag, m_u16ExternalSubtitleIdx)))
    {
        u32ReadBufAddr = READ_BUF_ADR;

        if(msAPI_FCtrl_FileSeek(m_u8ExternalSubtitleFileHandle,
                                m_Subtitle_Tag.u32SubtitlePos,
                                FILE_SEEK_SET) == FALSE)
        {
            goto _MApp_MPlayer_PushSubtitleSUB_END;
        }
        if(0 != msAPI_FCtrl_FileRead(m_u8ExternalSubtitleFileHandle,
                                     READ_BUF_ADR,
                                     READ_BUF_SIZE))
        {
            goto _MApp_MPlayer_PushSubtitleSUB_END;
        }

        // Parse subtitle.
        u16SubtitleLen = 0;
        u16SubtitleDstPos = 0;
        u16DataIdx = 0;
        pu8Data = (U8 *)_PA2VA(u32ReadBufAddr);
        pu16Data = (U16 *)_PA2VA(u32ReadBufAddr);
        do
        {
            // Process start code
            if(*(U32*)_PA2VA((u32ReadBufAddr + u16DataIdx)) != 0xBA010000)
            {
                goto _MApp_MPlayer_PushSubtitleSUB_END;
            }
            u16DataIdx += 4;

            switch(pu8Data[u16DataIdx] & 0xC0)
            {
            case 0x40:
                u16DataIdx += 10;
                break;
            case 0x20:
                u16DataIdx += 8;
                break;
            default:
                goto _MApp_MPlayer_PushSubtitleSUB_END;
            }

            if((pu16Data[u16DataIdx>>1]!=0x0000) || (pu16Data[(u16DataIdx>>1)+1]!=0xBD01))    // private stream 1
            {
                goto _MApp_MPlayer_PushSubtitleSUB_END;
            }
            u16DataIdx += 4;
//            u16PacketLen = *(U16*)((void *)&pu8Data[u16DataIdx]);
            u16PacketLen = ((pu8Data[u16DataIdx]<<8)|(pu8Data[u16DataIdx+1]));
            u16DataIdx+=2;
            if((pu8Data[u16DataIdx] & 0xC0) != 0x80)
            {
                goto _MApp_MPlayer_PushSubtitleSUB_END;
            }
            u16DataIdx += 2;
            u16HeaderLen = (U16)pu8Data[u16DataIdx];

            u16DataIdx += u16HeaderLen + 1 + 1;
            u16CopyLen = u16PacketLen - (u16HeaderLen + 4);

        #if ENABLE_INTERNAL_AND_EXTERNAL_SUBTITLE
            if(u16SubtitleLen == 0)
            {
                // Read remain data to DRAM.
//                u16SubtitleLen = *(U16*)((void *)&pu8Data[u16DataIdx]);
                u16SubtitleLen = ((pu8Data[u16DataIdx]<<8)|(pu8Data[u16DataIdx+1]));
                if(u16SubtitleLen == 0)
                {
                    goto _MApp_MPlayer_PushSubtitleSUB_END;
                }

                u32SubtitleBuff = msAPI_MpegSP_SpuQueue_GetSDRAMAddress(u16SubtitleLen);
                if(u32SubtitleBuff == 0)
                {
                    goto _MApp_MPlayer_PushSubtitleSUB_END;
                }

                u16SubtitleLenAligned = (u16SubtitleLen + VOBSUB_PACKET_MASK) & 0xF800;
            }
        #else
            if(u16SubtitleLen == 0)
            {
                // Read remain data to DRAM.
//                u16SubtitleLen = *(U16*)((void *)&pu8Data[u16DataIdx]);
                u16SubtitleLen = ((pu8Data[u16DataIdx]<<8)|(pu8Data[u16DataIdx+1]));

                if(u16SubtitleLen == 0)
                {
                    goto _MApp_MPlayer_PushSubtitleSUB_END;
                }
                u16SubtitleLenAligned = (u16SubtitleLen + VOBSUB_PACKET_MASK) & 0xF800;
                if(u16SubtitleLenAligned > READ_BUF_SIZE)
                {
                    if(msAPI_FCtrl_FileRead(m_u8ExternalSubtitleFileHandle,
                                            (READ_BUF_ADR+READ_BUF_SIZE),
                                            u16SubtitleLenAligned-READ_BUF_SIZE) != 0)
                    {
                        goto _MApp_MPlayer_PushSubtitleSUB_END;
                    }
                }
            }
        #endif

            // Copy Subtitle to buffer.
            //msAPI_MIU_Copy((U32)(u32ReadBufAddr+u16DataIdx), (U32)(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))+u16SubtitleDstPos), u16CopyLen, MIU_SDRAM2SDRAM);
        #if ENABLE_INTERNAL_AND_EXTERNAL_SUBTITLE
            memcpy((U8 *)_PA2VA(u32SubtitleBuff+u16SubtitleDstPos), (U8 *)_PA2VA((u32ReadBufAddr+u16DataIdx)), u16CopyLen);
        #else
            memcpy((U8 *)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))+u16SubtitleDstPos), (U8 *)_PA2VA((u32ReadBufAddr+u16DataIdx)), u16CopyLen);
        #endif
            u16SubtitleDstPos += u16CopyLen;
            if(u16SubtitleDstPos >= u16SubtitleLen)
            {
                break;
            }

            u16DataIdx += u16CopyLen;

            if((u16DataIdx & VOBSUB_PACKET_MASK) != 0)
            {
                goto _MApp_MPlayer_PushSubtitleSUB_END;
            }
            else if(u16DataIdx >= READ_BUF_SIZE)
            {
            #if ENABLE_INTERNAL_AND_EXTERNAL_SUBTITLE
                if(msAPI_FCtrl_FileRead(m_u8ExternalSubtitleFileHandle,
                    READ_BUF_ADR,READ_BUF_SIZE) != 0)
                    {
                        goto _MApp_MPlayer_PushSubtitleSUB_END;
                    }
                u32ReadBufAddr = READ_BUF_ADR;
            #else
                u32ReadBufAddr += READ_BUF_SIZE;
            #endif
                u16DataIdx = 0;
                pu8Data = (U8 *)_PA2VA(u32ReadBufAddr);
                pu16Data = (U16 *)_PA2VA(u32ReadBufAddr);
            }

        } while(1);
    #if (ENABLE_INTERNAL_AND_EXTERNAL_SUBTITLE==0)
        u32SubtitleBuff = msAPI_MpegSP_SpuQueue_GetSDRAMAddress(u16SubtitleLen);
    #endif

        if(u32SubtitleBuff >0)
        {
            //msAPI_MIU_Copy(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)), u32SubtitleBuff, u16SubtitleLen, MIU_SDRAM2SDRAM);
        #if (ENABLE_INTERNAL_AND_EXTERNAL_SUBTITLE==0)
            memcpy((U8 *)_PA2VA(u32SubtitleBuff), (U8 *)_PA2VA(((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR))), u16SubtitleLen);
        #endif
            msAPI_MpegSP_SpuQueue_Push(E_VDP_CODEC_ID_SUBTITLE_IMAGE_VOBSUB,  //E_SUBTITLE_VIDEO_TYPE_MPEG4,
                       u32SubtitleBuff, u16SubtitleLen, m_Subtitle_Tag.u32TimeStart * 90, 0);
            m_u32NextExternalSubtitleStartTime = m_Subtitle_Tag.u32TimeStart;
            bRet = TRUE;
        }

_MApp_MPlayer_PushSubtitleSUB_END:
        m_u16ExternalSubtitleIdx++;
    }

    return bRet;
}
#endif //(ENABLE_SMALL_BUF_SUBTITLE==0)
#endif //#if (ENABLE_SUBTITLE_SUBIDX)

#if ENABLE_MPLAYER_MIXED
U32 MApp_MPlayer_QueryPlayListIndex(enumMPlayerMediaType eType, U32 u32FileListIndex)
{
    S32 i, j;
    MPlayerFileInfo fileInfo;

    MApp_MPlayer_PlayList_CleanUp();
    for (i = m_u16DirectoryNum[m_u16CurDirectoryDepth], j = -1; (U32)i <= u32FileListIndex; i++)
    {

        if(MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY, i, &fileInfo) == E_MPLAYER_RET_OK)
        {
           if (MApp_MPlayer_QueryMediaTypeByFileExtName(&fileInfo) == eType)
           {
               j++;
           }
        }
        else
            return (U32)(-1);
    }
    //printf("GetPlayListIndex[%d]\n ",(j+m_u16DirectoryNum[m_u16CurDirectoryDepth]));
    return (U32)(j+m_u16DirectoryNum[m_u16CurDirectoryDepth]);
}
U32 MApp_MPlayer_QueryFileListIndex(enumMPlayerMediaType eType,U16 u16PlayingIdx)
{
    S32 i, j;
    MPlayerFileInfo fileInfo;

    for (i = m_u16DirectoryNum[m_u16CurDirectoryDepth], j = -1; (U32)i < m_u16TotalFileNum; i++)
    {

        if(MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY, i, &fileInfo) == E_MPLAYER_RET_OK)
        {
           if (MApp_MPlayer_QueryMediaTypeByFileExtName(&fileInfo) == eType)
           {
               j++;
               if(j ==u16PlayingIdx-m_u16DirectoryNum[m_u16CurDirectoryDepth])
                break;
           }
        }
        else
            return (U32)(-1);
    }
    //printf("GetFileListIndex[%d]\n ",(i));
    return (U32)(i);
}
#endif

static BOOLEAN _MApp_MPlayer_PlayerInit(enumMPlayerIdx eMPlayerIdx, enumMPlayerMediaType eMediaType, BOOLEAN bPreview)
{
    U16 u16TotalFileNumber = m_u16TotalFileNum;
    U16 u16DirectoryNumber = m_u16DirectoryNum[m_u16CurDirectoryDepth];

//printf("_MApp_MPlayer_PlayerInit()\n");

#ifdef ENABLE_PTP
    if (MApp_PTP_DeviceInUse())
    {
        return _MApp_MPlayer_PTP_PlayerInit(eMPlayerIdx, eMediaType, bPreview);
    }
#endif

    if (eMPlayerIdx == E_MPLAYER_FOREGROUND_PLAYER)
    {
        m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &= (enumMPlayerKnlFlags1)~(0
#if ENABLE_MPLAYER_PHOTO
            | E_MPLAYER_KNL_FLG1_PHOTO_PLAY
#endif  // #if ENABLE_MPLAYER_PHOTO
#if ENABLE_MPLAYER_MOVIE
            | E_MPLAYER_KNL_FLG1_MOVIE_PLAY
#endif  // #if ENABLE_MPLAYER_MOVIE
#if ENABLE_MPLAYER_TEXT
            | E_MPLAYER_KNL_FLG1_TEXT_PLAY
#endif  // #if ENABLE_MPLAYER_TEXT
            );

        if( eMediaType == E_MPLAYER_TYPE_PHOTO ) // photo
        {
            m_u32PhotoCurrentDisplayedIdx = 0;
            m_s32Photo_LastDecodeIdx = -1;
            m_s32Photo_LastDecodeFailIdx = -1;
            m_u32Photo_PlayPrevDecodeFailCount = 0;

            MApp_MPlayer_ClearPhotoInfo(); //solve issue: photo info error when play very big file.
        }
    }

    if (eMPlayerIdx == E_MPLAYER_BACKGROUND_PLAYER)
    {
        m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &= (enumMPlayerKnlFlags1)~(0
#if ENABLE_MPLAYER_MUSIC
            | E_MPLAYER_KNL_FLG1_MUSIC_PLAY
#endif  // #if ENABLE_MPLAYER_MUSIC
            );

        if (!bPreview)
        {
        #if DIRECTORY_BGM//(ENABLE_BGM)
            _MApp_MPlayer_StoreMusicFileInCurDirectory();
            u16TotalFileNumber = m_u16TotalMusicFileNum;
            u16DirectoryNumber = m_u16CurMusicDirectoryNumber;
        #else
            if(m_eMediaType != E_MPLAYER_TYPE_MUSIC)
            {
                u16TotalFileNumber = 0;
                u16DirectoryNumber = 0;
            }
        #endif
        }
    }

    m_MPlayerInfo[eMPlayerIdx].eMediaType = eMediaType;
    m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_INVALID;
    m_MPlayerInfo[eMPlayerIdx].eRepeatMode = m_eRepeatMode[eMPlayerIdx];
#if RANDOM_PLAY
    m_MPlayerInfo[eMPlayerIdx].eRandomMode = m_eRandomMode[eMPlayerIdx];
#endif
    m_MPlayerInfo[eMPlayerIdx].ePlayMode = m_ePlayMode;
    m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus = E_MPLAYER_STATE_NONE;
    m_MPlayerInfo[eMPlayerIdx].eMediaPlayingDirection = E_MPLAYER_PLAY_DIRECTION_NEXT;

    if (m_ePlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT)
    {
        m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx = m_u16CurFileIdx;
    }
    else if (m_ePlayMode == E_MPLAYER_PLAY_SELECTED_FROM_CURRENT)
    {
       if (_MApp_MPlayer_Browser_IsInPlayingList(eMediaType, MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)))
           m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx = _MApp_MPlayer_Browser_QueryPlayingList(eMediaType, MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY));
       else m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx = 0;
    }
    else
    {
        m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx = 0;
    }

    if (eMPlayerIdx == E_MPLAYER_FOREGROUND_PLAYER)
    {
        if( eMediaType == E_MPLAYER_TYPE_PHOTO ) // photo
        {
            m_u32PhotoCurrentDisplayedIdx = m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx; //give beginning playing idx
        }
    }
    m_MPlayerInfo[eMPlayerIdx].u16TotalFileNum = u16TotalFileNumber; // directories are included
    m_MPlayerInfo[eMPlayerIdx].u16TotalDirNum = u16DirectoryNumber;

    if ((m_MPlayerInfo[eMPlayerIdx].u8BrowserHandle == INVALID_BROWSER_HANDLE)
            || (m_MPlayerInfo[eMPlayerIdx].u16CurrentDrive != m_u16CurDriveIdx))
    {
        if (m_MPlayerInfo[eMPlayerIdx].u8BrowserHandle != INVALID_BROWSER_HANDLE)
        {
            MApp_FileBrowser_Destroy(m_MPlayerInfo[eMPlayerIdx].u8BrowserHandle);
        }

        m_MPlayerInfo[eMPlayerIdx].u16CurrentDrive = m_u16CurDriveIdx;
        m_MPlayerInfo[eMPlayerIdx].u8BrowserHandle =
                MApp_FileBrowser_Create(m_MPlayerInfo[eMPlayerIdx].u16CurrentDrive);
    }

    return (m_MPlayerInfo[eMPlayerIdx].u8BrowserHandle != INVALID_BROWSER_HANDLE ? TRUE : FALSE);
}

static void _MApp_MPlayer_ReCalcMPlayerPlayingIdx(enumMPlayerMediaType eMediaType, BOOLEAN bAddToList, U16 u16StartIdx, U16 u16EndIdx)
{
    enumMPlayerIdx eMPlayerIdx;

    for (eMPlayerIdx = E_MPLAYER_FOREGROUND_PLAYER; eMPlayerIdx < E_MPLAYER_MAX_CONCURRENT_PLAYER_NUM; eMPlayerIdx++)
    {
        if ((eMediaType == m_MPlayerInfo[eMPlayerIdx].eMediaType)
                && (m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 & (0
#if ENABLE_MPLAYER_PHOTO
                        | E_MPLAYER_KNL_FLG1_PHOTO_PLAY
#endif  // #if ENABLE_MPLAYER_PHOTO
#if ENABLE_MPLAYER_MUSIC
                        | E_MPLAYER_KNL_FLG1_MUSIC_PLAY
#endif  // #if ENABLE_MPLAYER_MUSIC
#if ENABLE_MPLAYER_MOVIE
                        | E_MPLAYER_KNL_FLG1_MOVIE_PLAY
#endif  // #if ENABLE_MPLAYER_MOVIE
#if ENABLE_MPLAYER_TEXT
                        | E_MPLAYER_KNL_FLG1_TEXT_PLAY
#endif  // #if ENABLE_MPLAYER_TEXT
                        )))
        {
            if (bAddToList) // add to play list
            {
                if (u16StartIdx > m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx)
                {
                    // all adding files are below currently playing file, do nothing
                }
                else if (m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx >= u16EndIdx)
                {
                    // all adding files are above currently playing file, plus (u16EndIdx - u16StartIdx) to playing idx
                    m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx += (u16EndIdx - u16StartIdx + 1);
                }
                else
                {
                    // no other situration is possible
                }
            }
            else // remove from play list
            {
                if (u16StartIdx > m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx)
                {
                    // all removing files are below currently playing file, do nothing
                }
                else if (m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx > u16EndIdx)
                {
                    // all removing files are above currently playing file, minus (u16EndIdx - u16StartIdx) from playing idx
                    m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx -= (u16EndIdx - u16StartIdx + 1);
                }
                else
                {
                    // currently playing file is in middle of removing files
                    if (u16StartIdx == 0)
                    {
                        // no other file is above currently playing file, do nothing
                    }
                    else if (u16EndIdx == (m_u16SelectedFileNum[m_eMediaType] - 1))
                    {
                        // no other file is below currently playing file, set playing idx to currently total selected number.
                        // next call to play next file will set playing idx to 0
                        m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx = u16EndIdx;
                    }
                    else
                    {
                        // set playing idx to start
                        m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx = u16StartIdx;
                    }
                }
            }
        }
    }
}

#if ENABLE_MPLAYER_PHOTO
static EN_RET _MApp_MPlayer_PhotoDecode(void)
{
    EN_RET eRet;

    m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaPlayingStatus &= (enumMediaPlayingStatus)~E_MPLAYER_PHOTO_STATE_DECODE_PAUSE;
    switch(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType)
    {
        case E_MPLAYER_SUBTYPE_JPG:
#if (ENABLE_BMP)
        case E_MPLAYER_SUBTYPE_BMP:
#endif
#if (ENABLE_PNG)
        case E_MPLAYER_SUBTYPE_PNG:
#endif
#if (ENABLE_TIFF)
        case E_MPLAYER_SUBTYPE_TIFF:
#endif
#if (ENABLE_GIF)
        case E_MPLAYER_SUBTYPE_GIF:
#endif
            eRet = MApp_Photo_Main();
            break;

        default:
            eRet = EXIT_PHOTO_WAIT;
            break;
    }

    return eRet;
}
#endif  // #if ENABLE_MPLAYER_PHOTO

static U8 _MApp_MPlayer_FindCurrentDedicatedFile(U8 *pExtName, U8 u8ExtNum, U8 u8BrowserHandle, FileEntry *pCurPlayingFileEntry, FileEntry *pEntry, U8 u8MaxFileEntryNum)
{
    S16 s16BaseNameLen;
    U16 *pu16FileName=NULL;
    U8 strLen;
    DirEntryStruct * pCurrentDirEntry;     //global current dir entry
    U16 *pTemp = NULL;
    U32 u32FoundFlag=0;
    U8 u8ExtIdx;
#if (ENABLE_EXTERNAL_SUBTITLE_FAST_SWITCHING)
    U8 u8FileCnt=0;
#endif
    FileEntry fileEntry[MAX_DEDICATED_FILE_EXT_NUM];

    memset(fileEntry,0,sizeof(fileEntry));

    pu16FileName = (U16*)msAPI_Memory_Allocate(SUBTITLE_LYRIC_LONG_FILENAME_SIZE,
                                             BUF_ID_FILEBROWER);
    if(pu16FileName == NULL)
    {
        __ASSERT(0);
        goto MApp_MPlayer_FindDedicatedFile_END;
    }

    // Following function calls started with MApp_FileBrowser_XXX will change MPlayer browser environment
    // when getting dedicate file on different directory or event on different drive.
    // This isn't wanted especially when foreground/background player affect the MPlayer browser environment.
    // Therefore, we have to change to the environemt prepared for foreground/background player and
    // change it back to MPlayer browser environment when searching dedicated file is done.
    _MApp_MPlayer_Browser_ChangeBrowsingEnv(u8BrowserHandle);

    strLen = MApp_FileBrowser_GetLongFileNameByFileEntry(
                 pCurPlayingFileEntry,
                 (U32)(pu16FileName),
                 (SUBTITLE_LYRIC_LONG_FILENAME_SIZE/2-1));
    pu16FileName[strLen] = 0;

    // Process the long file name.
    for(s16BaseNameLen = strLen; s16BaseNameLen > 0; s16BaseNameLen--)
    {
        if(pu16FileName[s16BaseNameLen] == '.')
        {
            break;
        }
    }

    pTemp=msAPI_Memory_Allocate((SUBTITLE_LYRIC_LONG_FILENAME_SIZE),
                                BUF_ID_FILEBROWER);
    if(pTemp==NULL)
    {
        __ASSERT(0);
        goto MApp_MPlayer_FindDedicatedFile_END;
    }
    if(u8ExtNum > MAX_DEDICATED_FILE_EXT_NUM)
    {
        u8ExtNum = MAX_DEDICATED_FILE_EXT_NUM;
    }

    MApp_FileBrowser_EnterDirectoryToContained(pCurPlayingFileEntry);

    _MApp_MPlayer_Browser_FirstEntry();
    pCurrentDirEntry = MApp_FileBrowser_GetCurrentDirEntry();
    while(pCurrentDirEntry)
    {
        for(u8ExtIdx=0;u8ExtIdx<u8ExtNum;u8ExtIdx++)
        {
            if(memcmp(pCurrentDirEntry->ps8DirEntryExtName,
                      &pExtName[u8ExtIdx*EXT_FILENAME_SIZE],
                      EXT_FILENAME_SIZE) == 0)
            {
                strLen=MApp_FileBrowser_GetCurrentLongName((U32)(pTemp),
                                                           (SUBTITLE_LYRIC_LONG_FILENAME_SIZE/2-1));
                if(_MApp_MPlayer_WcsNCaseCmp(pu16FileName, pTemp, (s16BaseNameLen + 1)) == 0)
                {
                    u32FoundFlag |= (1<<u8ExtIdx);
                    MApp_FileBrowser_GetCurrentFileEntry(&fileEntry[u8ExtIdx]);
#if (ENABLE_EXTERNAL_SUBTITLE_FAST_SWITCHING)
                    memcpy(&pEntry[u8FileCnt], &fileEntry[u8ExtIdx], sizeof(FileEntry));
                    u8FileCnt++;
#endif
                    if(u8ExtIdx == 0)
                    {
                        break;
                    }
                }
            }
        }
#if (ENABLE_EXTERNAL_SUBTITLE_FAST_SWITCHING)
        if(u8FileCnt >= u8MaxFileEntryNum)
        {
            break;
        }
#endif
        pCurrentDirEntry = MApp_FileBrowser_GetNextDirEntry(1);
    }

MApp_MPlayer_FindDedicatedFile_END:
    if(pu16FileName)
    {
        msAPI_Memory_Free(pu16FileName, BUF_ID_FILEBROWER);
    }
    if(pTemp)
    {
        msAPI_Memory_Free(pTemp,BUF_ID_FILEBROWER);
    }

    _MApp_MPlayer_Browser_ChangeBrowsingEnv(m_u8UserBrowserHandle);

#if (ENABLE_EXTERNAL_SUBTITLE_FAST_SWITCHING)
    if(u32FoundFlag)
    {
        return u8FileCnt;
    }
    else
    {
        return 0x0FF;
    }
#else
    if(u32FoundFlag)
    {
        for(u8ExtIdx=0;u8ExtIdx<u8ExtNum;u8ExtIdx++)
        {
            if((1<<u8ExtIdx) & u32FoundFlag)
            {
                memcpy(pEntry, &fileEntry[u8ExtIdx], sizeof(FileEntry));
                return(u8ExtIdx);
            }
        }
    }

    return 0xFF;
#endif
}

#if STORE_SUBTITLE_ENTRY_TO_SUBTITLE_BUFFER
//******************************************************************************
/// Find dedicated files in current folder by file entry.
/// @param  pExtName \b IN Specify dedicated extension file name.
/// @param  u8ExtNum \b IN Specify dedicated extension file name number.
/// @param  u32PhyAddr \b IN Specify file buffer address.
/// @param  u16BufTotalFileNum \b IN Specify total file number in file buffer.
/// @param  pCurPlayingFileEntry \b IN Specify file entry.
/// @param  pExtFileInfo \b OUT Specify dedicated file info.
/// @param  u8MaxFileEntryNum \b IN Specify maximum dedicated file number.
/// @return Dedicated file number.
//******************************************************************************
static U8 _MApp_MPlayer_FindCurrentDedicatedFileInCurrentFolder(U8 *pExtName, U8 u8ExtNum, U32 u32PhyAddr, U16 u16BufTotalFileNum, FileEntry *pCurPlayingFileEntry, ST_MPLAYER_ExtFileInfo *pExtFileInfo, U8 u8MaxFileEntryNum)
{
    S16 s16BaseNameLen;
    U16 *pu16FileName=NULL;
    U8 strLen;
    U16 *pTemp = NULL;
    U32 u32FoundFlag=0;
    U8 u8ExtIdx;
#if (ENABLE_EXTERNAL_SUBTITLE_FAST_SWITCHING)
    U8 u8FileCnt=0;
#endif
    FileEntry fileEntry[MAX_DEDICATED_FILE_EXT_NUM];
    U16 u16EntryIndex;
    MPlayerFileInfo *pFileInfo;
    U32 u32Addr, u32BuffAddr;
    u32Addr = _PA2VA(u32PhyAddr);
    u32BuffAddr = _PA2VA((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR));

    pu16FileName = (U16*)msAPI_Memory_Allocate(FILE_INFO_LONG_FILENAME_SIZE,
                                             BUF_ID_FILEBROWER);
    if(pu16FileName == NULL)
    {
        __ASSERT(0);
        goto MApp_MPlayer_FindDedicatedFile_END;
    }

    BOOLEAN bFind = FALSE;
    for(u16EntryIndex=m_u16BufDirectoryNum; u16EntryIndex<m_u16TotalFileNum; u16EntryIndex++)
    {
        pFileInfo = (MPlayerFileInfo *)(u32BuffAddr+u16EntryIndex*sizeof(MPlayerFileInfo));
        if(memcmp(pCurPlayingFileEntry->EntryID,     pFileInfo->fileEntry.EntryID,     4)==0
        && memcmp(pCurPlayingFileEntry->EntryID_Ext, pFileInfo->fileEntry.EntryID_Ext, 8)==0
        && pCurPlayingFileEntry->FileSystemID == pFileInfo->fileEntry.FileSystemID)
        {
            _MApp_MPlayer_GetLongFileName(pFileInfo);
            bFind = TRUE;
            break;
        }
    }

    if(bFind)
    {
        memcpy(pu16FileName, pFileInfo->u8LongFileName, FILE_INFO_LONG_FILENAME_SIZE);
        strLen = (U16)FS_strlen_U(pu16FileName);
    }
    else
    {
        strLen = MApp_FileBrowser_GetLongFileNameByFileEntry(
                     pCurPlayingFileEntry,
                     (U32)(pu16FileName),
                     (FILE_INFO_LONG_FILENAME_SIZE/2-1));
        pu16FileName[strLen] = 0;
    }

    // Process the long file name.
    for(s16BaseNameLen = strLen; s16BaseNameLen > 0; s16BaseNameLen--)
    {
        if(pu16FileName[s16BaseNameLen] == '.')
        {
            break;
        }
    }

    pTemp=msAPI_Memory_Allocate((FILE_INFO_LONG_FILENAME_SIZE),
                                BUF_ID_FILEBROWER);
    if(pTemp==NULL)
    {
        __ASSERT(0);
        goto MApp_MPlayer_FindDedicatedFile_END;
    }
    if(u8ExtNum > MAX_DEDICATED_FILE_EXT_NUM)
    {
        u8ExtNum = MAX_DEDICATED_FILE_EXT_NUM;
    }

    for(u16EntryIndex=0;u16EntryIndex<u16BufTotalFileNum;u16EntryIndex++)
    {
        pFileInfo = (MPlayerFileInfo *)(u32Addr+(U32)u16EntryIndex*sizeof(MPlayerFileInfo));

        for(u8ExtIdx=0;u8ExtIdx<u8ExtNum;u8ExtIdx++)
        {
            if(memcmp(pFileInfo->u8ExtFileName,
                      &pExtName[u8ExtIdx*EXT_FILENAME_SIZE],
                      EXT_FILENAME_SIZE) == 0)
            {
                _MApp_MPlayer_GetLongFileName(pFileInfo);
                memcpy(pTemp, pFileInfo->u8LongFileName, FILE_INFO_LONG_FILENAME_SIZE);

                if(_MApp_MPlayer_WcsNCaseCmp(pu16FileName, pTemp, (s16BaseNameLen + 1)) == 0)
                {
                    u32FoundFlag |= (1<<u8ExtIdx);
                    memcpy(&fileEntry[u8ExtIdx], &pFileInfo->fileEntry, sizeof(FileEntry));
#if (ENABLE_EXTERNAL_SUBTITLE_FAST_SWITCHING)
                    memcpy(&pExtFileInfo[u8FileCnt].fileEntry, &fileEntry[u8ExtIdx], sizeof(FileEntry));
                    memcpy(&pExtFileInfo[u8FileCnt].u8ExtFileName, &pFileInfo->u8ExtFileName, EXT_FILENAME_SIZE);
                    pExtFileInfo[u8FileCnt].u8ExtFileName[3] = '\0';
                    u8FileCnt++;
#endif
                }
                break;
            }
        }
#if (ENABLE_EXTERNAL_SUBTITLE_FAST_SWITCHING)
        if(u8FileCnt >= u8MaxFileEntryNum)
        {
            break;
        }
#endif
    }

MApp_MPlayer_FindDedicatedFile_END:
    if(pu16FileName)
    {
        msAPI_Memory_Free(pu16FileName, BUF_ID_FILEBROWER);
    }
    if(pTemp)
    {
        msAPI_Memory_Free(pTemp,BUF_ID_FILEBROWER);
    }

#if (ENABLE_EXTERNAL_SUBTITLE_FAST_SWITCHING)
    if(u32FoundFlag)
    {
        return u8FileCnt;
    }
    else
    {
        return 0x0FF;
    }
#else
    if(u32FoundFlag)
    {
        for(u8ExtIdx=0;u8ExtIdx<u8ExtNum;u8ExtIdx++)
        {
            if((1<<u8ExtIdx) & u32FoundFlag)
            {
                memcpy(&pExtFileInfo->fileEntry, &fileEntry[u8ExtIdx], sizeof(FileEntry));
                memcpy(&pExtFileInfo->u8ExtFileName, &pFileInfo->u8ExtFileName, EXT_FILENAME_SIZE);
                pExtFileInfo->u8ExtFileName[3] = '\0';
                return(u8ExtIdx);
            }
        }
    }

    return 0xFF;
#endif
}
#endif

#if ENABLE_SUBTITLE_COPY_AND_DELETE
//******************************************************************************
/// Scan subtitle files by movie file entry in USB or Subtitle file buffer,
/// and store subtitle files in m_aExtFileInfoList.
/// PS:Search in USB is slow , and search in Subtitle file buffer is fast.
/// @param  pstFileEntry \b IN Specify movie file entry
/// @param  bScanUSB \b IN Specify search subtitle file in USB or Subtitle file buffer.
/// @return Subtitle file number.
//******************************************************************************
static U8 _MApp_MPlayer_ScanExtSubtitleFileNumByMovieFileEntry(FileEntry *pstFileEntry, BOOLEAN bScanUSB)
{
    U8 u8ExtFileNum = 0;

    if(m_eMediaType == E_MPLAYER_TYPE_MOVIE)
    {
        U8 u8FileExtIdx;

        if(bScanUSB)
        {
        #if ENABLE_EXTERNAL_SUBTITLE_FAST_SWITCHING
            u8FileExtIdx = _MApp_MPlayer_FindCurrentDedicatedFile_ex
                           (&m_pu8SubtitleFileExt[0][0],
                            E_VDPLAYER_SUBTITLE_NUM,
                            pstFileEntry->EnvironmentID,
                            pstFileEntry,
                            m_aExtFileInfoList, MAX_DEDICATED_FILE_EXT_NUM);
            if(u8FileExtIdx != 0xFF)
            {
                u8ExtFileNum = u8FileExtIdx;
            }
        #else
            u8FileExtIdx = _MApp_MPlayer_FindCurrentDedicatedFile_ex
                           (&m_pu8SubtitleFileExt[0][0],
                            E_VDPLAYER_SUBTITLE_NUM,
                            pstFileEntry->EnvironmentID,
                            pstFileEntry,
                            &m_ExtFileInfo, MAX_DEDICATED_FILE_EXT_NUM);
            if(u8FileExtIdx != 0xFF)
            {
                u8ExtFileNum = 1;
            }
        #endif
        }
    #if STORE_SUBTITLE_ENTRY_TO_SUBTITLE_BUFFER
        else
        {
            if(m_u16TotalSubtitleFileNum > 0)
            {
            #if ENABLE_EXTERNAL_SUBTITLE_FAST_SWITCHING
                u8FileExtIdx = _MApp_MPlayer_FindCurrentDedicatedFileInCurrentFolder
                               (&m_pu8SubtitleFileExt[0][0],
                                E_VDPLAYER_SUBTITLE_NUM,
                                MPLAYER_SUBTITLE_FILE_BUFFER_ADR,
                                m_u16TotalSubtitleFileNum,
                                pstFileEntry,
                                m_aExtFileInfoList, MAX_DEDICATED_FILE_EXT_NUM);
                if(u8FileExtIdx != 0xFF)
                {
                    u8ExtFileNum = u8FileExtIdx;
                }
            #else
                u8FileExtIdx = _MApp_MPlayer_FindCurrentDedicatedFileInCurrentFolder
                               (&m_pu8SubtitleFileExt[0][0],
                                E_VDPLAYER_SUBTITLE_NUM,
                                MPLAYER_SUBTITLE_FILE_BUFFER_ADR,
                                m_u16TotalSubtitleFileNum,
                                pstFileEntry,
                                &m_ExtFileInfo, MAX_DEDICATED_FILE_EXT_NUM);
                if(u8FileExtIdx != 0xFF)
                {
                    u8ExtFileNum = 1;
                }
            #endif
            }
        }
    #endif
    }
    return u8ExtFileNum;
}
#endif

#if ENABLE_SUBTITLE_DMP
static U8 _MApp_MPlayer_FindCurrentDedicatedFile_ex(U8 *pExtName, U8 u8ExtNum, U8 u8BrowserHandle, FileEntry *pCurPlayingFileEntry, ST_MPLAYER_ExtFileInfo *pExtFileInfo, U8 u8MaxFileEntryNum)
{
    S16 s16BaseNameLen;
    U16 *pu16FileName=NULL;
    U8 strLen;
    DirEntryStruct * pCurrentDirEntry;     //global current dir entry
    U16 *pTemp = NULL;
    U32 u32FoundFlag=0;
    U8 u8ExtIdx;
#if (ENABLE_EXTERNAL_SUBTITLE_FAST_SWITCHING)
    U8 u8FileCnt=0;
#endif
    FileEntry fileEntry[MAX_DEDICATED_FILE_EXT_NUM];

    memset(fileEntry, 0, sizeof(FileEntry)*MAX_DEDICATED_FILE_EXT_NUM);

    pu16FileName = (U16*)msAPI_Memory_Allocate(SUBTITLE_LYRIC_LONG_FILENAME_SIZE,
                                             BUF_ID_FILEBROWER);
    if(pu16FileName == NULL)
    {
        __ASSERT(0);
        goto MApp_MPlayer_FindDedicatedFile_END;
    }

    // Following function calls started with MApp_FileBrowser_XXX will change MPlayer browser environment
    // when getting dedicate file on different directory or event on different drive.
    // This isn't wanted especially when foreground/background player affect the MPlayer browser environment.
    // Therefore, we have to change to the environemt prepared for foreground/background player and
    // change it back to MPlayer browser environment when searching dedicated file is done.
    _MApp_MPlayer_Browser_ChangeBrowsingEnv(u8BrowserHandle);

    strLen = MApp_FileBrowser_GetLongFileNameByFileEntry(
                 pCurPlayingFileEntry,
                 (U32)(pu16FileName),
                 (SUBTITLE_LYRIC_LONG_FILENAME_SIZE/2-1));
    pu16FileName[strLen] = 0;

    // Process the long file name.
    for(s16BaseNameLen = strLen; s16BaseNameLen > 0; s16BaseNameLen--)
    {
        if(pu16FileName[s16BaseNameLen] == '.')
        {
            break;
        }
    }

    pTemp=msAPI_Memory_Allocate((SUBTITLE_LYRIC_LONG_FILENAME_SIZE),
                                BUF_ID_FILEBROWER);
    if(pTemp==NULL)
    {
        __ASSERT(0);
        goto MApp_MPlayer_FindDedicatedFile_END;
    }
    if(u8ExtNum > MAX_DEDICATED_FILE_EXT_NUM)
    {
        u8ExtNum = MAX_DEDICATED_FILE_EXT_NUM;
    }

    MApp_FileBrowser_EnterDirectoryToContained(pCurPlayingFileEntry);

    _MApp_MPlayer_Browser_FirstEntry();
    pCurrentDirEntry = MApp_FileBrowser_GetCurrentDirEntry();
    while(pCurrentDirEntry)
    {
        for(u8ExtIdx=0;u8ExtIdx<u8ExtNum;u8ExtIdx++)
        {
            if(memcmp(pCurrentDirEntry->ps8DirEntryExtName,
                      &pExtName[u8ExtIdx*EXT_FILENAME_SIZE],
                      EXT_FILENAME_SIZE) == 0)
            {
                strLen=MApp_FileBrowser_GetCurrentLongName((U32)(pTemp),
                                                           (SUBTITLE_LYRIC_LONG_FILENAME_SIZE/2-1));
                if(_MApp_MPlayer_WcsNCaseCmp(pu16FileName, pTemp, (s16BaseNameLen + 1)) == 0)
                {
                    u32FoundFlag |= (1<<u8ExtIdx);
                    MApp_FileBrowser_GetCurrentFileEntry(&fileEntry[u8ExtIdx]);
#if (ENABLE_EXTERNAL_SUBTITLE_FAST_SWITCHING)
                    memcpy(&pExtFileInfo[u8FileCnt].fileEntry, &fileEntry[u8ExtIdx], sizeof(FileEntry));
                    memcpy(&pExtFileInfo[u8FileCnt].u8ExtFileName, &pCurrentDirEntry->ps8DirEntryExtName, EXT_FILENAME_SIZE);
                    pExtFileInfo[u8FileCnt].u8ExtFileName[3] = '\0';
                    u8FileCnt++;
#endif
                    if(u8ExtIdx == 0)
                    {
                        break;
                    }
                }
            }
        }
#if (ENABLE_EXTERNAL_SUBTITLE_FAST_SWITCHING)
        if(u8FileCnt >= u8MaxFileEntryNum)
        {
            break;
        }
#endif
        pCurrentDirEntry = MApp_FileBrowser_GetNextDirEntry(1);
    }

MApp_MPlayer_FindDedicatedFile_END:
    if(pu16FileName)
    {
        msAPI_Memory_Free(pu16FileName, BUF_ID_FILEBROWER);
    }
    if(pTemp)
    {
        msAPI_Memory_Free(pTemp,BUF_ID_FILEBROWER);
    }

    _MApp_MPlayer_Browser_ChangeBrowsingEnv(m_u8UserBrowserHandle);

#if (ENABLE_EXTERNAL_SUBTITLE_FAST_SWITCHING)
    if(u32FoundFlag)
    {
        return u8FileCnt;
    }
    else
    {
        return 0x0FF;
    }
#else
    if(u32FoundFlag)
    {
        for(u8ExtIdx=0;u8ExtIdx<u8ExtNum;u8ExtIdx++)
        {
            if((1<<u8ExtIdx) & u32FoundFlag)
            {
                memcpy(&pCopyExtFileInfo->fileEntry, &fileEntry[u8ExtIdx], sizeof(FileEntry));
                memcpy(&pCopyExtFileInfo->u8ExtFileName, &pCurrentDirEntry->ps8DirEntryExtName, EXT_FILENAME_SIZE);
                pCopyExtFileInfo->u8ExtFileName[3] = '\0';
                return(u8ExtIdx);
            }
        }
    }

    return 0xFF;
#endif
}

#endif
#if (ENABLE_LRC_LYRIC)
static BOOLEAN _MApp_MPlayer_Music_Lyric_Parser(void)
{
    #define MAX_FILE_ENTRY    10

    U8 *pu8Data;
    U32 u32FileSize;
    FileEntry fileEntry[MAX_FILE_ENTRY];
    U8 u8FileNum;
    U8 i = 0;
    U8 u8FileHandle=(U8)(FCTRL_INVALID_FILE_HANDLE);

    MApp_Music_LyricInit();

    if((u8FileNum = _MApp_MPlayer_FindCurrentDedicatedFile((U8*)"LRC",
            1,
            m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].u8BrowserHandle,
            &m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].curPlayingFileEntry,
            &fileEntry[0],MAX_FILE_ENTRY)) == 0xFF)
    {
        goto _MApp_MPlayer_Music_Lyric_Parser_END;
    }

#if (ENABLE_EXTERNAL_SUBTITLE_FAST_SWITCHING)
    for(i = 0; i < u8FileNum; i++)
#endif
    {
        u8FileHandle = msAPI_FCtrl_FileOpen(&fileEntry[i], OPEN_MODE_FOR_READ);
        if(FCTRL_INVALID_FILE_HANDLE == u8FileHandle)
        {
            MPLAYER_DBG(printf("Open file failed\n"));
#if (ENABLE_EXTERNAL_SUBTITLE_FAST_SWITCHING)
            continue;
#else
            goto _MApp_MPlayer_Music_Lyric_Parser_END;
#endif
        }

        u32FileSize = msAPI_FCtrl_FileLength(u8FileHandle);
        // Read file.
    pu8Data = (U8*)_PA2VA(((MUSIC_LYRIC_BUFFER_MEMORY_TYPE & MIU1) ? (MUSIC_LYRIC_BUFFER_ADR | MIU_INTERVAL) : (MUSIC_LYRIC_BUFFER_ADR)));
    memset(pu8Data, 0, MUSIC_LYRIC_BUFFER_LEN);
        msAPI_FCtrl_FileRead(u8FileHandle, ((MUSIC_LYRIC_BUFFER_MEMORY_TYPE & MIU1) ? (MUSIC_LYRIC_BUFFER_ADR | MIU_INTERVAL) : (MUSIC_LYRIC_BUFFER_ADR)),
                             MIN(u32FileSize+512, MUSIC_LYRIC_BUFFER_LEN));

        pu8Data = (U8*)_PA2VA(((MUSIC_LYRIC_BUFFER_MEMORY_TYPE & MIU1) ? (MUSIC_LYRIC_BUFFER_ADR | MIU_INTERVAL) : (MUSIC_LYRIC_BUFFER_ADR)));
        if(pu8Data[0]==0xFF && pu8Data[1]==0xFE)
        {
            m_bIsLyricUnicode = TRUE;   //EN_TEXT_UNIS
            m_bIsUtf8 = FALSE;
        }
        else
        {
            m_bIsLyricUnicode = FALSE;
            if(pu8Data[0]==0xEF && pu8Data[1]==0xBB && pu8Data[2]==0xBF)
            {
                m_bIsUtf8 = TRUE;
            }
            else
            {
                m_bIsUtf8 = FALSE;
            }
        }

        if(MApp_Music_LRC_Lyrics_Parser(u32FileSize))
        {
            msAPI_FCtrl_FileClose(u8FileHandle);
            return TRUE;
        }
        else
        {
            msAPI_FCtrl_FileClose(u8FileHandle);
            u8FileHandle = FCTRL_INVALID_FILE_HANDLE;
        }
    }
#if (ENABLE_EXTERNAL_SUBTITLE_FAST_SWITCHING)
_MApp_MPlayer_Music_Lyric_Parser_END:
#if 0
    if(FCTRL_INVALID_FILE_HANDLE != u8FileHandle)
    {
        msAPI_FCtrl_FileClose(u8FileHandle);
    }
#endif
#endif
    return FALSE;
}
#endif

#if (ENABLE_SUBTITLE_DMP)
static BOOLEAN _MApp_MPLayer_GetSubtitleTypeByFileExtName(enumMPlayerSubtitleType *peType, U8* pExtFileName)
{
    U8 i;
    BOOLEAN bRet = FALSE;

    _MApp_MPlayer_ToUpper(pExtFileName, EXT_FILENAME_SIZE);

    for(i=0;i<E_VDPLAYER_SUBTITLE_NUM;i++)
    {
        if(memcmp(pExtFileName,
                  m_pu8SubtitleFileExt[i],
                  EXT_FILENAME_SIZE) == 0)
        {
            *peType = (enumMPlayerSubtitleType)i;
            bRet = TRUE;
            break;
        }
    }

    return bRet;
}

static BOOLEAN _MApp_MPlayer_MP4_Subtitle_Parser(void)
{
    SUBTITLE_DBG(printf("-- _MApp_MPlayer_MP4_Subtitle_Parser\n"));
    U32 u32FileSize;
#if (ENABLE_EXTERNAL_SUBTITLE_FAST_SWITCHING)
    ST_MPLAYER_ExtFileInfo astExfileInfo[MAX_DEDICATED_FILE_EXT_NUM];
#if (ENABLE_SUBTITLE_SUBIDX)
    FileEntry fileEntrySUB;
#endif
    U8 u8Cnt=0;
    U8 i;
    enumMPlayerSubtitleType eSubtitleType = E_MPLAYER_SUBTITLE_INVALID;
#else
    FileEntry fileEntry, fileEntrySUB;
#endif
    BOOLEAN bRet = FALSE;
    U8 uFileExtIdx;

#if (ENABLE_EXTERNAL_SUBTITLE_FAST_SWITCHING)
    memset(astExfileInfo, 0, sizeof(astExfileInfo));
    for(i = 0; i < MAX_DEDICATED_FILE_EXT_NUM; i++)
    {
        astExfileInfo[i].fileEntry.EntryType = ENTRY_TYPE_NULL;
        astExfileInfo[i].fileEntry.EnvironmentID = 0xFF;
        astExfileInfo[i].fileEntry.FileSystemID = 0xFF;
        astExfileInfo[i].fileEntry.EntryAttrib = 0xFF;
     }
#endif
    m_eSubtitleCodingType = E_MPLAYER_SUBTITLE_CODING_INVALID;
    m_eExternalSubtitleType = E_MPLAYER_SUBTITLE_INVALID;
    MApp_MPlayer_SubtitleInit();

#if (ENABLE_EXTERNAL_SUBTITLE_FAST_SWITCHING)
    m_u8ExternalSubtitleFileHandle = FCTRL_INVALID_FILE_HANDLE;
    uFileExtIdx = _MApp_MPlayer_FindCurrentDedicatedFile_ex(&m_pu8SubtitleFileExt[0][0],
                        E_VDPLAYER_SUBTITLE_NUM,
                        m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].u8BrowserHandle,
                        &m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].curPlayingFileEntry,
                        &astExfileInfo[0],MAX_DEDICATED_FILE_EXT_NUM);
    u8Cnt = 0;
    SUBTITLE_DBG((uFileExtIdx<0xFF)?printf("-- Total External Subtitle: %d\n", uFileExtIdx):printf("-- None Subtitle\n"));

    if(uFileExtIdx==0xFF) //check if no subtitle, go to end
    {
        goto _MApp_MPlayer_MP4_Subtitle_Parser_END;
    }

  PARSE_AGAIN:

    MApp_MPlayer_SubtitleSetFileInfo(&astExfileInfo[u8Cnt].fileEntry);

    _MApp_MPLayer_GetSubtitleTypeByFileExtName(&eSubtitleType, astExfileInfo[u8Cnt].u8ExtFileName);

    u32FileSize=0;

    if(MApp_MPlayer_Subtitle_Parser(&eSubtitleType, u32FileSize, &m_eSubtitleCodingType))
    {
        SUBTITLE_DBG(printf("-- External Subtitle Index (%d) Parse Done\n",u8Cnt));

        bRet = TRUE;
    #if (ENABLE_SUBTITLE_SUBIDX)
        if(eSubtitleType == E_MPLAYER_SUBTITLE_SUBIDX)
        {
            if(_MApp_MPlayer_FindCurrentDedicatedFile((U8*)"SUB",
                    1,
                    m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].u8BrowserHandle,
                    &m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].curPlayingFileEntry,
                    &fileEntrySUB,1) == 0xFF)
            {
                goto _MApp_MPlayer_MP4_Subtitle_Parser_END;
            }

            m_u8ExternalSubtitleFileHandle = msAPI_FCtrl_FileOpen(&fileEntrySUB, OPEN_MODE_FOR_READ);
            if(m_u8ExternalSubtitleFileHandle != FCTRL_INVALID_FILE_HANDLE)
            {
         #if (ENABLE_SMALL_BUF_SUBTITLE)
                MApp_MPlayer_SubtitleSetSUBIDXFileHandle(m_u8ExternalSubtitleFileHandle);
         #endif
                m_u16ExternalSubtitleIdx = 0;
                bRet = TRUE;
            }
            else
            {
                bRet = FALSE;
            }
        }
    #endif //#if (ENABLE_SUBTITLE_SUBIDX)
    }
    else
    {
        SUBTITLE_DBG(printf("-- SUBTITLE INVALID\n"));
    }

    u8Cnt++;
    if((u8Cnt<uFileExtIdx) &&
        (MApp_MPlayer_GetInfo(E_MPLAYER_EXT_SUBTITLE_INFO_NB_TRACK)<SUPPORT_SUBITILE_TRACK_MAX))
    {
        goto PARSE_AGAIN;
    }

#else
    m_u8ExternalSubtitleFileHandle = FCTRL_INVALID_FILE_HANDLE;
    uFileExtIdx = _MApp_MPlayer_FindCurrentDedicatedFile(&m_pu8SubtitleFileExt[0][0],
                        E_VDPLAYER_SUBTITLE_NUM,
                        m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].u8BrowserHandle,
                        &m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].curPlayingFileEntry,
                        &fileEntry, 1);
    if(uFileExtIdx != 0xFF)
    {
        m_eExternalSubtitleType = (enumMPlayerSubtitleType)uFileExtIdx;
    }
    else
    {
        goto _MApp_MPlayer_MP4_Subtitle_Parser_END;
    }

  #if (ENABLE_SUBTITLE_SUBIDX)
    if(m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SUBIDX)
    {
        if(_MApp_MPlayer_FindCurrentDedicatedFile((U8*)"SUB",
                1,
                m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].u8BrowserHandle,
                &m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].curPlayingFileEntry,
                &fileEntrySUB, 1) == 0xFF)
        {
            goto _MApp_MPlayer_MP4_Subtitle_Parser_END;
        }
    }
  #endif //#if (ENABLE_SUBTITLE_SUBIDX)

    u8FileHandle = msAPI_FCtrl_FileOpen(&fileEntry, OPEN_MODE_FOR_READ);
    if(FCTRL_INVALID_FILE_HANDLE == u8FileHandle)
    {
        MPLAYER_DBG(printf("Open file failed\n"));
        goto _MApp_MPlayer_MP4_Subtitle_Parser_END;
    }

    u32FileSize = msAPI_FCtrl_FileLength(u8FileHandle);
  #if (ENABLE_SMALL_BUF_SUBTITLE)
    MApp_MPlayer_SubtitleSetFileInfo(&fileEntry);
  #else
    MApp_MPlayer_SubtitleSetFileHandle(u8FileHandle);

    // Read file.
    u32FileSize = MIN(u32FileSize+512, MP4_SUBTITLE_BUFFER_LEN);
    msAPI_FCtrl_FileRead(u8FileHandle, ((MP4_SUBTITLE_BUFFER_MEMORY_TYPE & MIU1) ? (MP4_SUBTITLE_BUFFER_ADR | MIU_INTERVAL) : (MP4_SUBTITLE_BUFFER_ADR)), u32FileSize);
  #endif

    if(MApp_MPlayer_Subtitle_Parser(&m_eExternalSubtitleType, u32FileSize, &m_eSubtitleCodingType))
    {
        SUBTITLE_DBG(printf("-- External Subtitle Index (%d) Parse Done\n",u8Cnt));
        msAPI_FCtrl_FileClose(u8FileHandle);
        u8FileHandle = FCTRL_INVALID_FILE_HANDLE;
    #if (ENABLE_SUBTITLE_SUBIDX)
        if(m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SUBIDX)
        {
            m_u8ExternalSubtitleFileHandle = msAPI_FCtrl_FileOpen(&fileEntrySUB, OPEN_MODE_FOR_READ);
            if(m_u8ExternalSubtitleFileHandle != FCTRL_INVALID_FILE_HANDLE)
            {
                m_u16ExternalSubtitleIdx = 0;
                bRet = TRUE;
            }
            else
            {
                bRet = FALSE;
            }
        }
    #endif //#if (ENABLE_SUBTITLE_SUBIDX)
        bRet = TRUE;
    }
#endif

_MApp_MPlayer_MP4_Subtitle_Parser_END:

    return bRet;
}

//This end of line size is for UNICODE(UI subtitle format)
#define END_OF_LINE_SIZE 2

static U16 _MApp_MPlayer_GetSubtitle(U8 *pu8Dst, U32 u32BufSize, U32 u32SubtitlePos)
{
    U16 u16Src, u16Dst, u16Tmp;
    U8 *pu8Src=NULL;
    U32 u32CurTrk;

    if(u32SubtitlePos == 0xFFFFFFFF)
    {
        pu8Dst[0] = '\0';
        pu8Dst[1] = '\0';
        return 0;
    }

    //reserve the end of line space
    u32BufSize = u32BufSize - END_OF_LINE_SIZE;

    u32CurTrk = MApp_MPlayer_GetInfo(E_MPLAYER_EXT_SUBTITLE_INFO_TRACK_ID);

    if(m_eExternalSubtitleType==E_MPLAYER_SUBTITLE_INVALID)
    {
        pu8Src = (U8*)_PA2VA(INTERNAL_TEXT_SUBTITLE_BUFFER_ADR+u32SubtitlePos);
    }
    else
    {
    #if (ENABLE_SMALL_BUF_SUBTITLE)
        pu8Src = (U8*)_PA2VA(u32SubtitlePos);
    #else
        pu8Src = (U8*)_PA2VA(SUBTITLE_BUFFER_ADR+u32CurTrk*SUBTITLE_BUFFER_PER_TRACK+u32SubtitlePos);
    #endif
    }

 #if ENABLE_MPLAYER_MOVIE
    if(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL)
    {
        U32 eSubtitleCodingType = MApp_MPlayer_GetInfo(E_MPLAYER_EXT_SUBTITLE_INFO_SUBTITLE_CODING_TYPE);

        if (eSubtitleCodingType == E_MPLAYER_SUBTITLE_CODING_UTF8)
        {   // Internal subtitle, assume it is UTF8.
            for(u16Dst=0,u16Src=0;(u16Dst<u32BufSize || u16Src<u32BufSize);)
            {
                if(pu8Src[u16Src] == '\0')
                {
                    pu8Dst[u16Dst] = '\0';
                    pu8Dst[u16Dst+1] = '\0';
                    return u16Dst;
                }
                else if(pu8Src[u16Src] == '\r')
                {
                    pu8Dst[u16Dst+1] = 0xE0;//'\0';
                    pu8Dst[u16Dst] = 0x8A;//'\r';
                    u16Src++;
                    u16Dst+=2;

                    if(pu8Src[u16Src] == '\n')
                    {   // Skip '\n'.
                        u16Src++;
                    }
                }
                else if(pu8Src[u16Src] == '\n')
                {
                    pu8Dst[u16Dst+1] = 0xE0;//'\0';
                    pu8Dst[u16Dst] = 0x8A;//'\r';
                    u16Src++;
                    u16Dst+=2;
                }
                else if(pu8Src[u16Src] & 0x80)   // Not ASCII
                {
                    if((pu8Src[u16Src] & 0xF0) == 0xE0)
                    {   // 3-byte
                        pu8Dst[u16Dst+1] = (pu8Src[u16Src] << 4) | ((pu8Src[u16Src+1] >> 2) & 0x0F);
                        pu8Dst[u16Dst] = (pu8Src[u16Src+1] << 6) | (pu8Src[u16Src+2] & 0x3F);
                        u16Dst += 2;
                        u16Src += 3;
                    }
                    else if((pu8Src[u16Src] & 0xE0) == 0xC0)
                    {   // 2-byte
                        pu8Dst[u16Dst + 1] = (pu8Src[u16Src] >> 2) & 0x07;
                        pu8Dst[u16Dst] = (pu8Src[u16Src] << 6) | (pu8Src[u16Src+1] & 0x3F);
                        u16Dst += 2;
                        u16Src += 2;
                    }
                    else
                    {
                        u16Src++;
                    }
                }
#if (ENABLE_SUBTITLE_SMI)
                else if((pu8Src[u16Src] == '<')&&(pu8Src[u16Src+1] == 'b')
                        &&(pu8Src[u16Src+2] == 'r')&&(pu8Src[u16Src+3] == '>')
                        &&(m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SMI))
                {
                    pu8Dst[u16Dst+1] =  0xE0;//'\0';
                    pu8Dst[u16Dst] = 0x8A;//'\n';
                    u16Src += 4;
                    u16Dst+=2;
                }
                else if((pu8Src[u16Src] == '<')&&(pu8Src[u16Src+1] == 'B')
                        &&(pu8Src[u16Src+2] == 'R')&&(pu8Src[u16Src+3] == '>')
                        &&(m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SMI))
                {
                    pu8Dst[u16Dst+1] = 0xE0;//'\0';
                    pu8Dst[u16Dst] = 0x8A;//'\n';
                    u16Src += 4;
                    u16Dst+=2;
                }
                else if((pu8Src[u16Src] == '<')&&(pu8Src[u16Src+1] == 'b')
                        &&(pu8Src[u16Src+2] == 'r')&&(pu8Src[u16Src+3] == ' ')
                        &&(pu8Src[u16Src+4] == '/')&&(pu8Src[u16Src+5] == '>')
                        &&(m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SMI))
                {
                    pu8Dst[u16Dst+1] =  0xE0;//'\0';
                    pu8Dst[u16Dst] = 0x8A;//'\n';
                    u16Src += 6;
                    u16Dst+=2;
                }
                else if((pu8Src[u16Src] == '<')&&(pu8Src[u16Src+1] == 'B')
                        &&(pu8Src[u16Src+2] == 'R')&&(pu8Src[u16Src+3] == ' ')
                        &&(pu8Src[u16Src+4] == '/')&&(pu8Src[u16Src+5] == '>')
                        &&(m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SMI))
                {
                    pu8Dst[u16Dst+1] = 0xE0;//'\0';
                    pu8Dst[u16Dst] = 0x8A;//'\n';
                    u16Src += 6;
                    u16Dst+=2;
                }
#endif
                else if((m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SRT ||
                         m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SMI ||
                         m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SSA ||
                         m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_ASS)  &&
                        (pu8Src[u16Src] == '<'))
                {
                    SUBTITLE_DBG(printf("UTF8: found <\n"));
                    U16 u16Parsed = u16Src;
                    BOOLEAN bFoundEnd = FALSE;
                    // Skip <>instructions.
                    for(;u16Parsed<u32BufSize;u16Parsed++)
                    {
                        if((pu8Src[u16Parsed] == '\0'))
                        {
                            //avoid parsing next subtitle
                            //ex:  line 1<brA '\0'li>ne 2'\0'
                            // screen will show "line 1 ne2" (wrong)
                            pu8Dst[u16Dst+1] = '\0';
                            pu8Dst[u16Dst] = pu8Src[u16Src];
                            u16Dst+=2;
                            u16Src ++;
                            SUBTITLE_DBG(printf("UTF8: no > found\n"));
                            break;
                        }
                        if(pu8Src[u16Parsed] == '>')
                        {
                            SUBTITLE_DBG(printf("UTF8: found > \n"));
                            bFoundEnd = TRUE;
                            break;
                        }
                    }

                    if(bFoundEnd)
                    {
                        u16Src = u16Parsed + 1;
                    }
                }
                else if((pu8Src[u16Src] == '&') && (pu8Src[u16Src+1] == 'n') &&
                        (pu8Src[u16Src+2] == 'b') && (pu8Src[u16Src+3] == 's') &&
                        (pu8Src[u16Src+4] == 'p') && (pu8Src[u16Src+5] == ';'))
                {
                    pu8Dst[u16Dst+1] = '\0';
                    pu8Dst[u16Dst] = '\n';
                    u16Dst+=2;
                    u16Src += 6;
                }
                else if((pu8Src[u16Src] == '&') && (pu8Src[u16Src+1] == 'n') &&
                        (pu8Src[u16Src+2] == 'b') && (pu8Src[u16Src+3] == 's') &&
                        (pu8Src[u16Src+4] == 'p'))
                {
                    pu8Dst[u16Dst+1] = '\0';
                    pu8Dst[u16Dst] = '\n';
                    u16Dst+=2;
                    u16Src += 5;
                }
                else
                {
                    // ASCII
                    pu8Dst[u16Dst+1] = '\0';
                    pu8Dst[u16Dst] = pu8Src[u16Src];
                    u16Src++;
                    u16Dst+=2;
                }
            }

            pu8Dst[u32BufSize] = '\0';
            pu8Dst[u32BufSize+1] = '\0';
            return u32BufSize;
        }
        else if(eSubtitleCodingType == E_MPLAYER_SUBTITLE_CODING_UNICODE)
        {
            //printf("[0] = %x , [1] = %x\n", pu8Src[0], pu8Src[1]);
            //printf("16 [0] = %x\n", pu16Src[0]);
            for(u16Dst=0,u16Src=0;u16Dst<u32BufSize; u16Src += 2)
            {
            #if 0
                if((pu8Src[u16Src + 1] == 0x00) && (pu8Src[u16Src] == 0x7B))    // '{'
                {
                    U32 u32Parsed = u16Src + 2;
                    BOOL bFoundEnd = FALSE;
                    // Skip SSA instructions.
                    for(;u32Parsed<SUBTITLE_MAX_SIZE * 2;u32Parsed+=2)
                    {
                        if((pu8Src[u32Parsed +1] == 0x00) && (pu8Src[u32Parsed] == 0x7D) )    // '}'
                        {
                            bFoundEnd = TRUE;
                            break;
                        }
                    }
                    if(bFoundEnd)
                    {
                        u16Src = u32Parsed;
                    }
                }
                else
            #endif
#if (ENABLE_SUBTITLE_SMI)
                if((m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SMI) &&
                        ((pu8Src[u16Src] == '<')&&(pu8Src[u16Src+1] == '\0')) &&
                        ((pu8Src[u16Src+2] == 'b')&&(pu8Src[u16Src+3] == '\0')) &&
                        ((pu8Src[u16Src+4] == 'r')&&(pu8Src[u16Src+5] == '\0')) &&
                        ((pu8Src[u16Src+6] == '>')&&(pu8Src[u16Src+7] == '\0')))
                {
                    pu8Dst[u16Dst+1] = 0xE0;//'\0';//0xE0;
                    pu8Dst[u16Dst] = 0x8A;;//'\n';//0x8A;
                    u16Dst+=2;
                    u16Src += 8-2;
                }
                else if((m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SMI) &&
                        ((pu8Src[u16Src] == '<')&&(pu8Src[u16Src+1] == '\0')) &&
                        ((pu8Src[u16Src+2] == 'B')&&(pu8Src[u16Src+3] == '\0')) &&
                        ((pu8Src[u16Src+4] == 'R')&&(pu8Src[u16Src+5] == '\0')) &&
                        ((pu8Src[u16Src+6] == '>')&&(pu8Src[u16Src+7] == '\0')))
                {
                    pu8Dst[u16Dst+1] = 0xE0;//'\0';//0xE0;
                    pu8Dst[u16Dst] = 0x8A;;//'\n';//0x8A;
                    u16Dst+=2;
                    u16Src += 8-2;
                }
                else if((m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SMI) &&
                        ((pu8Src[u16Src] == '<')&&(pu8Src[u16Src+1] == '\0')) &&
                        ((pu8Src[u16Src+2] == 'b')&&(pu8Src[u16Src+3] == '\0')) &&
                        ((pu8Src[u16Src+4] == 'r')&&(pu8Src[u16Src+5] == '\0')) &&
                        ((pu8Src[u16Src+6] == ' ')&&(pu8Src[u16Src+7] == '\0')) &&
                        ((pu8Src[u16Src+8] == '/')&&(pu8Src[u16Src+9] == '\0')) &&
                        ((pu8Src[u16Src+10] == '>')&&(pu8Src[u16Src+11] == '\0')))
                {
                    pu8Dst[u16Dst+1] = 0xE0;//'\0';//0xE0;
                    pu8Dst[u16Dst] = 0x8A;;//'\n';//0x8A;
                    u16Dst+=2;
                    u16Src += 12-2;
                }
                else if((m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SMI) &&
                        ((pu8Src[u16Src] == '<')&&(pu8Src[u16Src+1] == '\0')) &&
                        ((pu8Src[u16Src+2] == 'B')&&(pu8Src[u16Src+3] == '\0')) &&
                        ((pu8Src[u16Src+4] == 'R')&&(pu8Src[u16Src+5] == '\0')) &&
                        ((pu8Src[u16Src+6] == ' ')&&(pu8Src[u16Src+7] == '\0')) &&
                        ((pu8Src[u16Src+8] == '/')&&(pu8Src[u16Src+9] == '\0')) &&
                        ((pu8Src[u16Src+10] == '>')&&(pu8Src[u16Src+11] == '\0')))
                {
                    pu8Dst[u16Dst+1] = 0xE0;//'\0';//0xE0;
                    pu8Dst[u16Dst] = 0x8A;;//'\n';//0x8A;
                    u16Dst+=2;
                    u16Src += 12-2;
                }
                else
#endif
                if((m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SRT ||
                    m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SMI ||
                    m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SSA ||
                    m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_ASS) &&
                    (pu8Src[u16Src + 1] == 0x00) && (pu8Src[u16Src] == '<'))    // '<'
                {
                    U32 u32Parsed = u16Src + 2;
                    BOOL bFoundEnd = FALSE;
                    // Skip SSA <font> etc.

                    SUBTITLE_DBG(printf("unicode: found <\n"));
                    for(;u32Parsed<u32BufSize * 2;u32Parsed+=2)
                    {
                        if((pu8Src[u32Parsed] == 0x00) && (pu8Src[u32Parsed+1]== '\0'))
                        {
                            //avoid parsing next subtitle
                            //ex:  line 1<brA '\0'li>ne 2'\0'
                            // screen will show "line 1 ne2" (wrong)
                            SUBTITLE_DBG(printf("unicode: no > found\n"));
                            //copy to pu8Dst so single < will show
                            pu8Dst[u16Dst++] = pu8Src[u16Src];
                            pu8Dst[u16Dst++] = pu8Src[u16Src + 1] ;
                            break;
                        }
                        if((pu8Src[u32Parsed +1] == 0x00) && (pu8Src[u32Parsed] == '>') )    // '>'
                        {
                            SUBTITLE_DBG(printf("unicode: found >\n"));
                            bFoundEnd = TRUE;
                            break;
                        }
                    }
                    if(bFoundEnd)
                    {
                        u16Src = u32Parsed;
                    }
                }
                else if((pu8Src[u16Src] == '&') && (pu8Src[u16Src+1] == '\0') &&
                        (pu8Src[u16Src+2] == 'n') && (pu8Src[u16Src+3] == '\0') &&
                        (pu8Src[u16Src+4] == 'b') && (pu8Src[u16Src+5] == '\0') &&
                        (pu8Src[u16Src+6] == 's') && (pu8Src[u16Src+7] == '\0') &&
                        (pu8Src[u16Src+8] == 'p') && (pu8Src[u16Src+9] == '\0') &&
                        (pu8Src[u16Src+10] == ';') && (pu8Src[u16Src+11] == '\0'))
                {
                    pu8Dst[u16Dst+1] = '\0';
                    pu8Dst[u16Dst] = '\n';
                    u16Dst+=2;
                    u16Src += 12-2;
                }
                else if((pu8Src[u16Src] == '&') && (pu8Src[u16Src+1] == '\0') &&
                        (pu8Src[u16Src+2] == 'n') && (pu8Src[u16Src+3] == '\0') &&
                        (pu8Src[u16Src+4] == 'b') && (pu8Src[u16Src+5] == '\0') &&
                        (pu8Src[u16Src+6] == 's') && (pu8Src[u16Src+7] == '\0') &&
                        (pu8Src[u16Src+8] == 'p') && (pu8Src[u16Src+9] == '\0'))
                {
                    pu8Dst[u16Dst+1] = '\0';
                    pu8Dst[u16Dst] = '\n';
                    u16Dst+=2;
                    u16Src += 10-2;
                }
                else if(pu8Src[u16Src + 1] == 0)
                {
                        if(pu8Src[u16Src] == 0x0)/*||
                            (pu8Src[u16Src] == 0x0D) ||
                            (pu8Src[u16Src] == 0x0A))*/
                        {
                            pu8Dst[u16Dst] = 0;
                            pu8Dst[u16Dst+1] = 0;
                            SUBTITLE_DBG(printf("Unicode: return u16Dst:%d\n",u16Dst));
                            return u16Dst;
                        }
                        else if(pu8Src[u16Src] == 0x0D) //'\r'
                        {
                            pu8Dst[u16Dst+1] = 0xE0;//'\0';
                            pu8Dst[u16Dst] = 0x8A;//'\r';
                            u16Dst += 2;

                            if(pu8Src[u16Src+2] == 0x000A)
                            {   //skip '\n'
                                u16Src += 2;
                            }
                        }
                        else if(pu8Src[u16Src] == 0x0A) //'\n'
                        {
                            pu8Dst[u16Dst+1] = 0xE0;//'\0';
                            pu8Dst[u16Dst] = 0x8A;//'\r';
                            u16Dst += 2;
                        }
                    #if 0
                        else if((pu8Src[u16Src] == 0x5C) &&
                            (((pu8Src[u16Src+3] == 0x00) && (pu8Src[u16Src+2] == 0x4E)) || ((pu8Src[u16Src+3] == 0x00) && (pu8Src[u16Src+2] == 0x6E))))
                        {
                                //   /N /n case
                                //printf("find N\n");
                                pu8Dst[u16Dst+1] = 0xE0;//'\0';
                                pu8Dst[u16Dst] = 0x8A;//'\r';
                                u16Dst += 2;
                                u16Src += 2;
                        }
                    #endif
#if (ENABLE_SUBTITLE_SUB)
                        else if(pu8Src[u16Src] == 0x7C)
                        {
                                pu8Dst[u16Dst+1] = 0xE0;//'\0';
                                pu8Dst[u16Dst] = 0x8A;//'\r';
                                u16Dst += 2;
                        }
#endif //#if (ENABLE_SUBTITLE_SUB)
                        else
                        {
                            pu8Dst[u16Dst++] = pu8Src[u16Src];
                            pu8Dst[u16Dst++] = pu8Src[u16Src + 1] ;
                        }
                }
                else
                {
                    pu8Dst[u16Dst++] = pu8Src[u16Src];
                    pu8Dst[u16Dst++] = pu8Src[u16Src + 1] ;
                }
            }
            pu8Dst[u32BufSize] = '\0';
            pu8Dst[u32BufSize+1] = '\0';
            return u32BufSize;
        }
        else
        {
            for(u16Dst=0,u16Src=0;u16Dst<u32BufSize;)
            {
#if (ENABLE_SUBTITLE_SMI)
                if((pu8Src[u16Src] == '<')&&(pu8Src[u16Src+1] == 'b')
                        &&(pu8Src[u16Src+2] == 'r')&&(pu8Src[u16Src+3] == '>')
                        &&(m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SMI))
                {
                    pu8Dst[u16Dst+1] =  0xE0;//'\0';
                    pu8Dst[u16Dst] = 0x8A;//'\n';
                    u16Src += 4;
                    u16Dst+=2;
                }
                else if((pu8Src[u16Src] == '<')&&(pu8Src[u16Src+1] == 'B')
                        &&(pu8Src[u16Src+2] == 'R')&&(pu8Src[u16Src+3] == '>')
                        &&(m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SMI))
                {
                    pu8Dst[u16Dst+1] = 0xE0;//'\0';
                    pu8Dst[u16Dst] = 0x8A;//'\n';
                    u16Src += 4;
                    u16Dst+=2;
                }
                else if((pu8Src[u16Src] == '<')&&(pu8Src[u16Src+1] == 'b')
                        &&(pu8Src[u16Src+2] == 'r')&&(pu8Src[u16Src+3] == ' ')
                        &&(pu8Src[u16Src+4] == '/')&&(pu8Src[u16Src+5] == '>')
                        &&(m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SMI))
                {
                    pu8Dst[u16Dst+1] =  0xE0;//'\0';
                    pu8Dst[u16Dst] = 0x8A;//'\n';
                    u16Src += 6;
                    u16Dst+=2;
                }
                else if((pu8Src[u16Src] == '<')&&(pu8Src[u16Src+1] == 'B')
                        &&(pu8Src[u16Src+2] == 'R')&&(pu8Src[u16Src+3] == ' ')
                        &&(pu8Src[u16Src+2] == '/')&&(pu8Src[u16Src+3] == '>')
                        &&(m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SMI))
                {
                    pu8Dst[u16Dst+1] = 0xE0;//'\0';
                    pu8Dst[u16Dst] = 0x8A;//'\n';
                    u16Src += 6;
                    u16Dst+=2;
                }
                else
#endif
                if((m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SRT ||
                    m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SMI ||
                    m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SSA ||
                    m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_ASS)  &&
                    (pu8Src[u16Src] == '<'))
                {
                    U16 u16Parsed = u16Src;
                    BOOLEAN bFoundEnd = FALSE;
                    // Skip <>instructions.
                    for(;u16Parsed<u32BufSize;u16Parsed++)
                    {
                        if((pu8Src[u16Parsed] == '\0'))
                        {
                            //avoid parsing next subtitle
                            //ex:  line 1<brA '\0'li>ne 2'\0'
                            // screen will show "line 1 ne2" (wrong)
                            SUBTITLE_DBG(printf("no > found\n"));
                            break;
                        }

                        if(pu8Src[u16Parsed] == '>')
                        {
                            // sequential <><>
                            if(pu8Src[u16Parsed+1] == '<')
                            {
                                // do nothing
                                //printf("sequential found < \n");
                                continue;
                            }
                            else
                            {
                                bFoundEnd = TRUE;
                                break;
                            }
                        }
                    }

                    if(bFoundEnd)
                    {
                        u16Src = u16Parsed + 1;
                    }
                }

                if(isprint(pu8Src[u16Src]) || (pu8Src[u16Src] == 0x09))
                {
                    pu8Dst[u16Dst+1] = '\0';
                    pu8Dst[u16Dst] = pu8Src[u16Src];

                #if (ENABLE_SUBTITLE_SUB)
                    if(pu8Src[u16Src] == '|')
//                            && (m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_MICRODVD))
                    {
                        pu8Dst[u16Dst] = 0x8A; //MicroDVD & Subviewer10 change line
                        pu8Dst[u16Dst+1] = 0xE0;
                    }
                    else if((pu8Src[u16Src] == '[')&&(pu8Src[u16Src+1] == 'b')
                            &&(pu8Src[u16Src+2] == 'r')&&(pu8Src[u16Src+3] == ']')
                            && (m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SUBVIEWER))
                    {
                        pu8Dst[u16Dst] = 0x8A; //Subviewer20 changeline
                        pu8Dst[u16Dst+1] = 0xE0;
                        u16Src += 3;
                    }
                #endif //#if (ENABLE_SUBTITLE_SUB)

                #if (ENABLE_SUBTITLE_SMI)
                    if (m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SMI)
                    {
                        // "&nbsp;" means ' '
                        if ( (pu8Src[u16Src] == '&')
                            &&(pu8Src[u16Src+1] == 'n')
                            &&(pu8Src[u16Src+2] == 'b')
                            &&(pu8Src[u16Src+3] == 's')
                            &&(pu8Src[u16Src+4] == 'p')
                            &&(pu8Src[u16Src+5] == ';') )
                        {
                            pu8Dst[u16Dst+1] = '\0';//0xA0;
                            pu8Dst[u16Dst] = '\n';
                            u16Src += 5;
                        }
                        else if ( (pu8Src[u16Src] == '&')
                                &&(pu8Src[u16Src+1] == 'n')
                                &&(pu8Src[u16Src+2] == 'b')
                                &&(pu8Src[u16Src+3] == 's')
                                &&(pu8Src[u16Src+4] == 'p') )
                        {
                            pu8Dst[u16Dst+1] = '\0';//0xA0;
                            pu8Dst[u16Dst] = '\n';
                            u16Src += 4;
                        }
                        else if ( (pu8Src[u16Src] == '&')//&lt;i&gt; == <i>
                            &&(pu8Src[u16Src+1] == 'l')
                            &&(pu8Src[u16Src+2] == 't')
                            &&(pu8Src[u16Src+3] == ';')
                            &&(pu8Src[u16Src+4] == 'i')
                            &&(pu8Src[u16Src+5] == '&')
                            &&(pu8Src[u16Src+6] == 'g')
                            &&(pu8Src[u16Src+7] == 't')
                            &&(pu8Src[u16Src+8] == ';') )
                        {
                            u16Src += 8;
                            u16Dst -= 2;
                        }
                        else if( (pu8Src[u16Src] == '&')//&lt;/i&gt; == </i>
                            &&(pu8Src[u16Src+1] == 'l')
                            &&(pu8Src[u16Src+2] == 't')
                            &&(pu8Src[u16Src+3] == ';')
                            &&(pu8Src[u16Src+4] == '/')
                            &&(pu8Src[u16Src+5] == 'i')
                            &&(pu8Src[u16Src+6] == '&')
                            &&(pu8Src[u16Src+7] == 'g')
                            &&(pu8Src[u16Src+8] == 't')
                            &&(pu8Src[u16Src+9] == ';') )
                        {
                            u16Src += 9;
                            u16Dst -= 2;
                        }
                        else if ( (pu8Src[u16Src] == '<')//no meaning
                            &&(pu8Src[u16Src+1] == '/')
                            &&(pu8Src[u16Src+2] == 'T')
                            &&(pu8Src[u16Src+3] == 'A')
                            &&(pu8Src[u16Src+4] == 'B')
                            &&(pu8Src[u16Src+5] == 'L'))
                        {
                            u16Src += 5;
                            u16Dst -= 2;
                        }
                        else if( (pu8Src[u16Src] == '&')
                            &&(pu8Src[u16Src+1] == '#'))
                        {
                            U32 u32Val;
                            U16 u16DigitCnt, u16SkipByte = 2;//skip '&'+'#' = 2

                            if(_MApp_MPlayer_ToLower(pu8Src[u16Src+u16SkipByte]) == 'x')
                            {
                                u16SkipByte++;//skip 'x'
                                u16DigitCnt = MApp_MPlayer_ConvertHexString2Digit(&pu8Src[u16Src+u16SkipByte], &u32Val);
                            }
                            else
                            {
                                u16DigitCnt = MApp_MPlayer_ConvertDecimalString2Digit(&pu8Src[u16Src+u16SkipByte], &u32Val);
                            }

                            if(u16DigitCnt > 0)
                            {
                                u16SkipByte += u16DigitCnt; //EX: skip &#xAA or skip &#99
                                if(pu8Src[u16Src+u16SkipByte] == ';')
                                {
                                    u16SkipByte++;//skip ';'
                                    pu8Dst[u16Dst+1] = ((u32Val>>8)&0xFF);
                                    pu8Dst[u16Dst] = (u32Val&0xFF);
                                    u16Src += (u16SkipByte-1);
                                }
                            }
                        }
                    }
                #endif

                    u16Src++;
                    u16Dst+=2;
                }
                else if (pu8Src[u16Src] == '\0')
                {
                    pu8Dst[u16Dst] = '\0';
                    pu8Dst[u16Dst+1] = '\0';
                    return u16Dst;
                }
                else if(pu8Src[u16Src] == '\r')
                {
                    pu8Dst[u16Dst+1] = 0xE0;//'\0';
                    pu8Dst[u16Dst] = 0x8A;//'\r';
                    u16Src++;
                    u16Dst+=2;

                    if(pu8Src[u16Src] == '\n')
                    {   // Skip '\n'.
                        u16Src++;
                    }
                }
                else if(pu8Src[u16Src] == '\n')
                {
                    pu8Dst[u16Dst+1] = 0xE0;//'\0';
                    pu8Dst[u16Dst] = 0x8A;//'\r';
                    u16Src++;
                    u16Dst+=2;;
                }
                else
                {
                    switch(m_enSubtitleCharsetType)
                    {
                        case SUBTITLE_CHARSET_CP874:
                        {
                            u16Tmp = MApp_CharTable_MappingCharToUCS2(WINDOWS_CP874, pu8Src[u16Src]);
                            memcpy(&pu8Dst[u16Dst], &u16Tmp, 2);
                            u16Src++;
                            u16Dst+=2;
                        }
                        break;
                        case SUBTITLE_CHARSET_CP1250:
                        {
                            u16Tmp = MApp_CharTable_MappingCharToUCS2(WINDOWS_CP1250, pu8Src[u16Src]);
                            memcpy(&pu8Dst[u16Dst], &u16Tmp, 2);
                            u16Src++;
                            u16Dst+=2;
                        }
                        break;
                        case SUBTITLE_CHARSET_CP1251:
                        {
                            u16Tmp = MApp_CharTable_MappingCharToUCS2(WINDOWS_CP1251, pu8Src[u16Src]);
                            memcpy(&pu8Dst[u16Dst], &u16Tmp, 2);
                            u16Src++;
                            u16Dst+=2;
                        }
                        break;
                        case SUBTITLE_CHARSET_CP1252:
                        {
                            u16Tmp = MApp_CharTable_MappingCharToUCS2(WINDOWS_CP1252, pu8Src[u16Src]);
                            memcpy(&pu8Dst[u16Dst], &u16Tmp, 2);
                            u16Src++;
                            u16Dst+=2;
                        }
                        break;
                case SUBTITLE_CHARSET_CP1253:
                {
                            u16Tmp = MApp_CharTable_MappingCharToUCS2(WINDOWS_CP1253, pu8Src[u16Src]);
                            memcpy(&pu8Dst[u16Dst], &u16Tmp, 2);
                            u16Src++;
                            u16Dst+=2;
                }
                break;
                        case SUBTITLE_CHARSET_CP1254:
                        {
                            u16Tmp = MApp_CharTable_MappingCharToUCS2(WINDOWS_CP1254, pu8Src[u16Src]);
                            memcpy(&pu8Dst[u16Dst], &u16Tmp, 2);
                            u16Src++;
                            u16Dst+=2;
                        }
                        break;
                        case SUBTITLE_CHARSET_CP1255:
                        {
                            u16Tmp = MApp_CharTable_MappingCharToUCS2(WINDOWS_CP1255, pu8Src[u16Src]);
                            memcpy(&pu8Dst[u16Dst], &u16Tmp, 2);
                            u16Src++;
                            u16Dst+=2;
                        }
                        break;
                        case SUBTITLE_CHARSET_CP1256:
                        {
                            u16Tmp = MApp_CharTable_MappingCharToUCS2(WINDOWS_CP1256, pu8Src[u16Src]);
                            memcpy(&pu8Dst[u16Dst], &u16Tmp, 2);
                            u16Src++;
                            u16Dst+=2;
                        }
                        break;
                case SUBTITLE_CHARSET_CP1257:
                {
                            u16Tmp = MApp_CharTable_MappingCharToUCS2(WINDOWS_CP1257, pu8Src[u16Src]);
                            memcpy(&pu8Dst[u16Dst], &u16Tmp, 2);
                            u16Src++;
                            u16Dst+=2;
                }
                break;
                case SUBTITLE_CHARSET_CP1258:
                {
                            u16Tmp = MApp_CharTable_MappingCharToUCS2(WINDOWS_CP1258, pu8Src[u16Src]);
                            memcpy(&pu8Dst[u16Dst], &u16Tmp, 2);
                            u16Src++;
                            u16Dst+=2;
                }
                break;
                        case SUBTITLE_CHARSET_CROATIAN_MAC:
                        {
                            u16Tmp = MApp_CharTable_MappingCharToUCS2(WINDOWS_CROATIAN_MAC, pu8Src[u16Src]);
                            memcpy(&pu8Dst[u16Dst], &u16Tmp, 2);
                            u16Src++;
                            u16Dst+=2;
                        }
                        break;
                        case SUBTITLE_CHARSET_ISO_8859_05:
                        {
                            u16Tmp = MApp_CharTable_MappingCharToUCS2(ISO_8859_05, pu8Src[u16Src]);
                            memcpy(&pu8Dst[u16Dst], &u16Tmp, 2);
                            u16Src++;
                            u16Dst+=2;
                        }
                        break;
                        case SUBTITLE_CHARSET_ISO_8859_10:
                        {
                            u16Tmp = MApp_CharTable_MappingCharToUCS2(ISO_8859_10, pu8Src[u16Src]);
                            memcpy(&pu8Dst[u16Dst], &u16Tmp, 2);
                            u16Src++;
                            u16Dst+=2;
                        }
                        break;
                        case SUBTITLE_CHARSET_KOREAN:
                        {
                        #if(CHAR_TABLE_SUPPORT_KOREAN_CODE)
                            u16Tmp = ((pu8Src[u16Src+1]) | ((pu8Src[u16Src])<<8));
                            u16Tmp = MApp_CharTable_MappingKor2Unicode(u16Tmp);
                            memcpy(&pu8Dst[u16Dst], &u16Tmp, 2);
                            u16Src+=2;
                            u16Dst+=2;
                        #else
                            //#error "32M unsupport Korean unicode"
                            printf("\nError: 32M unsupport Korean unicode\n");
                        #endif
                        }
                        break;
                        case SUBTITLE_CHARSET_GBK:
                        case SUBTITLE_CHARSET_DEFAULT:
                        default:
                        {
                            // It is GB code.
                            u16Tmp = ((pu8Src[u16Src+1]) | ((pu8Src[u16Src])<<8));
                            u16Tmp = MApp_Transfer2Unicode(u16Tmp);
                            memcpy(&pu8Dst[u16Dst], &u16Tmp, 2);
                            u16Src+=2;
                            u16Dst+=2;
                        }
                        break;
                    }
                }
            }
            pu8Dst[u32BufSize] = '\0';
            pu8Dst[u32BufSize+1] = '\0';
            return u32BufSize;
        }
    }
    else
    {
        // Internal subtitle, assume it is UTF8.
        for(u16Dst=0,u16Src=0;u16Dst<u32BufSize;)
        {
            if(pu8Src[u16Src] == '\0')
            {
                pu8Dst[u16Dst] = '\0';
                pu8Dst[u16Dst+1] = '\0';
                return u16Dst;
            }
            else if((pu8Src[u16Src] == '\r')||(pu8Src[u16Src] == '\n'))
            {
                if((pu8Src[u16Src] == '\r')&&(pu8Src[u16Src+1] == '\n'))
                {
                    pu8Dst[u16Dst+1] = 0xE0;//'\0';
                    pu8Dst[u16Dst] = 0x8A;//'\r';
                    u16Src+=2;
                    u16Dst+=2;
                }
                else
                {
                    pu8Dst[u16Dst+1] = 0xE0;//'\0';
                    pu8Dst[u16Dst] = 0x8A;//'\r';
                    u16Src++;
                    u16Dst+=2;
                }
            }
            else if((pu8Src[u16Src] == '\\') && ((pu8Src[u16Src + 1] == 'n') || (pu8Src[u16Src + 1] == 'N')))
            {
                pu8Dst[u16Dst+1] = 0xE0;//'\0';
                pu8Dst[u16Dst] = 0x8A;//'\r';
                u16Src+=2;
                u16Dst+=2;
            }
//            else if(pu8Src[u16Src] == '\n')
//            {   // Skip '\n'.
//                u16Src++;
//            }
            else if(pu8Src[u16Src] & 0x80)   // Not ASCII
            {
                if((pu8Src[u16Src] & 0xF0) == 0xE0)
                {   // 3-byte
                    pu8Dst[u16Dst+1] = (pu8Src[u16Src] << 4) | ((pu8Src[u16Src+1] >> 2) & 0x0F);
                    pu8Dst[u16Dst] = (pu8Src[u16Src+1] << 6) | (pu8Src[u16Src+2] & 0x3F);
                    u16Dst += 2;
                    u16Src += 3;
                }
                else if((pu8Src[u16Src] & 0xE0) == 0xC0)
                {   // 2-byte
                    pu8Dst[u16Dst + 1] = (pu8Src[u16Src] >> 2) & 0x07;
                    pu8Dst[u16Dst] = (pu8Src[u16Src] << 6) | (pu8Src[u16Src+1] & 0x3F);
                    u16Dst += 2;
                    u16Src += 2;
                }
                else
                {
                    u16Src++;
                }
            }
            else
            {
                pu8Dst[u16Dst+1] = '\0';
                pu8Dst[u16Dst] = pu8Src[u16Src];
                u16Src++;
                u16Dst+=2;
            }
        }

        pu8Dst[u32BufSize] = '\0';
        pu8Dst[u32BufSize+1] = '\0';
        return u32BufSize;
    }
#endif  // #if ENABLE_MPLAYER_MOVIE

#if 0
{
    U16* pu16Dst = (U16*) pu8Dst;
    for(u16Dst=0;u16Dst<96;u16Dst++)
    {
        if((u16Dst%16)==0)
            printf("\n");
        printf("%d ", pu16Dst[u16Dst]);
        //pu16Dst[u16Dst] = 268;
    }
    pu16Dst[u16Dst] = 0;
    printf("\n");
}
#endif
}
#endif //#if (ENABLE_SUBTITLE_DMP)

#if ENABLE_MPLAYER_MUSIC
static enumMPlayerMediaSubType _MApp_MPlayer_VerifyMusicType(FileEntry *pEntry,enumMPlayerMediaSubType enMusicType)
{
    U8 *pFileBufPtr;
#if ENABLE_WMA
    U32 i;
#endif
    U32 u32FileHandle,u16Mp3HeaderOffset,u32Delta,u32Offset = 0,u32TagSize = 0,u32FileSize;;
    U32 u32FileBuffAddr = ((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (MP3_INFO_READ_ADR | MIU_INTERVAL) : (MP3_INFO_READ_ADR));

    u32FileHandle = msAPI_DataStreamIO_Open(pEntry, OPEN_MODE_FOR_READ,E_DATA_STREAM_TYPE_MUSIC);
    if(u32FileHandle == INVALID_DATA_STREAM_HDL)
    {
        MPLAYER_DBG(printf("Open file failed\n"));
        return enMusicType;
    }

    u32FileSize = msAPI_DataStreamIO_Length(u32FileHandle);
    msAPI_DataStreamIO_Seek(u32FileHandle, 0,E_DATA_STREAM_SEEK_SET);
    msAPI_DataStreamIO_Read(u32FileHandle, (void*)u32FileBuffAddr, FAT_SECTOR_SIZE_512BYTE * 8); // 4k is xdata window size

    pFileBufPtr = (U8 *)_PA2VA(u32FileBuffAddr);
    // if has ID3 v2,skip it.
    if ((pFileBufPtr[0] == 'I') && (pFileBufPtr[1] == 'D') && (pFileBufPtr[2] == '3'))
    {
        MPLAYER_DBG(printf("\nskip ID3 tag\n"));
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
                MPLAYER_DBG(printf("two ID3 tag\n"));
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

#if (ENABLE_WAV)
    //check whether it is  WAV file
    if((pFileBufPtr[0] == 'R') && (pFileBufPtr[1] == 'I') &&  (pFileBufPtr[2] == 'F') && (pFileBufPtr[3] == 'F'))
    {
    #if 0
        if((pFileBufPtr[8] == 'W') && (pFileBufPtr[9] == 'A') &&
            (pFileBufPtr[10] == 'V') && (pFileBufPtr[11] == 'E') &&
            (pFileBufPtr[12] == 'f') && (pFileBufPtr[13] == 'm') &&
            (pFileBufPtr[14] == 't') && (pFileBufPtr[15] == ' '))
        {
            U16 u16FormatTag;

            memcpy(&u16FormatTag,(void*)(&pFileBufPtr[20]),2);
            if( (u16FormatTag == (U16)WAVE_FORMAT_PCM) ||
                (u16FormatTag == (U16)WAVE_FORMAT_M_ADPCM) ||
                (u16FormatTag == (U16)WAVE_FORMAT_EXTENSIBLE) ||
                (u16FormatTag == (U16)WAVE_FORMAT_IEEE_FLOAT) ||
                (u16FormatTag == (U16)WAVE_FORMAT_ALAW) ||
                (u16FormatTag == (U16)WAVE_FORMAT_MULAW) ||
                (u16FormatTag == (U16)WAVE_FORMAT_IMA_ADPCM) )
            {
                MPLAYER_DBG(printf("It is WAV file\n"));
                enMusicType = E_MPLAYER_SUBTYPE_WAV;   // it is WAV file
                goto _MApp_MPlayer_VerifyMusicType_end;
            }
        }
    #else
        U32 offset=8;
        U32 tag;
        U32 tagsize;

        MApp_Music_GetRIFFTag(&pFileBufPtr[offset], &tag, &tagsize);
        offset+=4;

        if (tag==RIFF_TAG_WAVE)
        {
            while (1)
            {
                if ((u32Delta+offset+10)>FAT_SECTOR_SIZE_512BYTE * 8)
                    goto _MApp_MPlayer_VerifyMusicType_end;

                MApp_Music_GetRIFFTag(&pFileBufPtr[offset], &tag, &tagsize);
                if (tag==RIFF_TAG_fmt)
                {
                    U16 u16FormatTag;

                    memcpy(&u16FormatTag,(void*)(&pFileBufPtr[offset+8]),2);
                    if( (u16FormatTag == (U16)WAVE_FORMAT_PCM) ||
                        (u16FormatTag == (U16)WAVE_FORMAT_M_ADPCM) ||
                        (u16FormatTag == (U16)WAVE_FORMAT_EXTENSIBLE) ||
                        (u16FormatTag == (U16)WAVE_FORMAT_IEEE_FLOAT) ||
                        (u16FormatTag == (U16)WAVE_FORMAT_ALAW) ||
                        (u16FormatTag == (U16)WAVE_FORMAT_MULAW) ||
                        (u16FormatTag == (U16)WAVE_FORMAT_IMA_ADPCM) )
                    {
                        MPLAYER_DBG(printf("It is WAV file\n"));
                        enMusicType = E_MPLAYER_SUBTYPE_WAV;   // it is WAV file
                        goto _MApp_MPlayer_VerifyMusicType_end;
                    }
                }
                offset+=(tagsize+8);
            }
        }
    #endif
    }
#endif

#if ENABLE_WMA
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
                MPLAYER_DBG(printf("It is WMA file\n"));
                enMusicType = E_MPLAYER_SUBTYPE_WMA;   // it is WMA file
                goto _MApp_MPlayer_VerifyMusicType_end;
            }
        }
    }
#endif

#if (ENABLE_AAC)
    //check whether it is AAC file
    if((pFileBufPtr[4] == 'f') && (pFileBufPtr[5] == 't') && (pFileBufPtr[6] == 'y') && (pFileBufPtr[7] == 'p'))
    {
        //AAC M4A file
        MPLAYER_DBG(printf("It is AAC M4A file\n"));
        enMusicType = E_MPLAYER_SUBTYPE_AAC;
        goto _MApp_MPlayer_VerifyMusicType_end;
    }
    else if((pFileBufPtr[0] == 'A') && (pFileBufPtr[1] == 'D') && (pFileBufPtr[2] == 'I') && (pFileBufPtr[3] == 'F'))
    {
        //ADIF file
        MPLAYER_DBG(printf("It is AAC ADIF file\n"));
        enMusicType = E_MPLAYER_SUBTYPE_AAC;
        goto _MApp_MPlayer_VerifyMusicType_end;
    }
    else if((pFileBufPtr[0] == 0xFF)&&((pFileBufPtr[1] & 0xF6) == 0xF0))
    {
        //ADTS file
        MPLAYER_DBG(printf("It is AAC ADTS file\n"));
        enMusicType = E_MPLAYER_SUBTYPE_AAC;
        goto _MApp_MPlayer_VerifyMusicType_end;
    }
#endif

#if (ENABLE_OGG)
    if((pFileBufPtr[0] == 'O') && (pFileBufPtr[1] == 'g') && (pFileBufPtr[2] == 'g') && (pFileBufPtr[3] == 'S'))
    {
        //ogg file
        MPLAYER_DBG(printf("It is Ogg file\n"));
        enMusicType = E_MPLAYER_SUBTYPE_OGG;
        goto _MApp_MPlayer_VerifyMusicType_end;
    }
#endif
#if (ENABLE_AMR)
    if(!memcmp(pFileBufPtr,"#!AMR-WB\n",9))
    {
        //awb file
        MPLAYER_DBG(printf("It is awb file\n"));
        enMusicType = E_MPLAYER_SUBTYPE_AWB;
        goto _MApp_MPlayer_VerifyMusicType_end;
    }
    else if(!memcmp(pFileBufPtr,"#!AMR\n",6))
    {
        //amr file
        MPLAYER_DBG(printf("It is amr file\n"));
        enMusicType = E_MPLAYER_SUBTYPE_AMR;
        goto _MApp_MPlayer_VerifyMusicType_end;
    }
#endif
#if (ENABLE_FLAC)
    if((pFileBufPtr[0] == 'f') && (pFileBufPtr[1] == 'L') && (pFileBufPtr[2] == 'a') && (pFileBufPtr[3] == 'C'))
    {
        MPLAYER_DBG(printf("It is flac file\n"));
        enMusicType = E_MPLAYER_SUBTYPE_FLAC;
        goto _MApp_MPlayer_VerifyMusicType_end;
    }
#endif
#if (ENABLE_AC3)
    if(((pFileBufPtr[0] == 0x0B) && (pFileBufPtr[1] == 0x77))  || ((pFileBufPtr[0] == 0x77) && (pFileBufPtr[1] == 0x0B)))
    {
        MPLAYER_DBG(printf("It is AC3 file\n"));
        enMusicType = E_MPLAYER_SUBTYPE_AC3;
        goto _MApp_MPlayer_VerifyMusicType_end;
    }
#endif

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
            MPLAYER_DBG(printf("It is mp3 file\n"));
            enMusicType = E_MPLAYER_SUBTYPE_MP3;   // it is MP3 file
            goto _MApp_MPlayer_VerifyMusicType_end;
        }
    }

    MPLAYER_DBG(printf("can not find match type, return type according file ext\n"));

_MApp_MPlayer_VerifyMusicType_end:
    msAPI_DataStreamIO_Close(u32FileHandle);
    u32FileHandle = INVALID_DATA_STREAM_HDL;
    return enMusicType;
}
#endif

static BOOLEAN _MApp_MPlayer_PlayDirectory(enumMPlayerIdx eMPlayerIdx)
{
    MPlayerFileInfo fileInfo;
    enumMPlayerRet eRet;
    U16 u16FileFailCount = 0;

    MPLAYER_DBG(printf("_MApp_MPlayer_PlayDirectory, u16PlayingIdx=%d\n", m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx););

//    m_u32LyricSubtitleCheckTime = 0;
    m_u32LyricSubtitleCurTime   = -1;
    m_u16CurLyricPos = -1;
    m_u32CurSubtitlePos = -1;
    m_u32PlayCheckTime = -1;

    if(m_MPlayerInfo[eMPlayerIdx].u16TotalFileNum - m_MPlayerInfo[eMPlayerIdx].u16TotalDirNum == 0)
    {
        return FALSE;
    }

    memset(&fileInfo, 0, sizeof(fileInfo));//remove klocwork warning message

    // Find the media file.
    while(m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx < m_MPlayerInfo[eMPlayerIdx].u16TotalFileNum)
    {
    #if DIRECTORY_BGM//ENABLE_BGM
        if (eMPlayerIdx == E_MPLAYER_BACKGROUND_PLAYER)
        {
            eRet = _MApp_MPlayer_GetMusicFileInfo(m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx, &fileInfo);
        }
        else
    #endif // #if ENABLE_BGM
        {
            eRet = MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,
                                       m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx,
                                       &fileInfo);
        }

        if ((eRet == E_MPLAYER_RET_OK) &&
            (!(fileInfo.eAttribute & E_MPLAYER_FILE_DIRECTORY)) &&
            (!(fileInfo.eAttribute & E_MPLAYER_FILE_DECODED_FAIL))
            )
        {
            break;
        }

        u16FileFailCount++;

        if(u16FileFailCount == m_MPlayerInfo[eMPlayerIdx].u16TotalFileNum)
        {
            return FALSE;
        }

        if(m_MPlayerInfo[eMPlayerIdx].eMediaPlayingDirection == E_MPLAYER_PLAY_DIRECTION_PREV)
        {
            m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx--;

            if(m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx < m_MPlayerInfo[eMPlayerIdx].u16TotalDirNum)
            {
                if( m_MPlayerInfo[eMPlayerIdx].eRepeatMode == E_MPLAYER_REPEAT_NONE)
                {
                    return FALSE;
                }
                else
                {
                    m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx = m_MPlayerInfo[eMPlayerIdx].u16TotalFileNum - 1;
                }
            }
        }
        else
        {
            m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx++;

            if((m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx >= m_MPlayerInfo[eMPlayerIdx].u16TotalFileNum))
            {// go to 1st file
                if( m_MPlayerInfo[eMPlayerIdx].eRepeatMode == E_MPLAYER_REPEAT_NONE)
                {
                    m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx = m_MPlayerInfo[eMPlayerIdx].u16TotalFileNum - 1; // avoid to get the wrong playing index
                    return FALSE;
                }
                else
                {
                    m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx = m_MPlayerInfo[eMPlayerIdx].u16TotalDirNum;
                }
            }
        }
    }

    MPLAYER_DBG(printf("u16PlayingIdx=%d\n", m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx););

    msAPI_MIU_SetRoundRobin(FALSE);  // If the file is JPG, will enable round robin.
    if(m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx < m_MPlayerInfo[eMPlayerIdx].u16TotalFileNum)
    {
        memcpy(&m_MPlayerInfo[eMPlayerIdx].curPlayingFileEntry, &fileInfo.fileEntry, sizeof(FileEntry));
        // Playing the media file ---------------------------------------------------------------------
        switch(m_MPlayerInfo[eMPlayerIdx].eMediaType)
        {
    #if ENABLE_MPLAYER_PHOTO
        case E_MPLAYER_TYPE_PHOTO:
            m_s32Photo_LastDecodeIdx = m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx;
            //printf("m_s32Photo_LastDecodeIdx=%ld\n", m_s32Photo_LastDecodeIdx);
            //MApp_MPlayer_ClearPhotoInfo();
            m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus &= (enumMediaPlayingStatus)~E_MPLAYER_PHOTO_STATE_DECODE_PAUSE;

            if (IS_PHOTO_FILE(fileInfo.u8ExtFileName))
            {
                if (IS_JPG_FILE(fileInfo.u8ExtFileName))
                {
                    m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_JPG;

                    msAPI_MIU_SetRoundRobin(TRUE);      // Fix the DDR bandwidth issue.

                    if (m_u8DecodedPics == 1)
                    {
                        // now JPEG decoder on S4 is fast enough for baseline JPEG.
                        // To save memory, JPEG decoder is asked to decode file when
                        // currently displayed JPEG file times out
                        m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= E_MPLAYER_PHOTO_STATE_DECODE_PAUSE;
                    }
                }
        #if (ENABLE_BMP)
                else if (IS_BMP_FILE(fileInfo.u8ExtFileName))
                {
                    m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_BMP;
                }
        #endif
        #if (ENABLE_PNG)
                else if (IS_PNG_FILE(fileInfo.u8ExtFileName))
                {
                    m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_PNG;
                }
        #endif
        #if (ENABLE_TIFF)
                else if (IS_TIFF_FILE(fileInfo.u8ExtFileName))
                {
                    m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_TIFF;
                }
        #endif
        #if (ENABLE_GIF)
                else if (IS_GIF_FILE(fileInfo.u8ExtFileName))
                {
                    m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_GIF;
                }
        #endif
                MApp_Photo_Stop();
                m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_PHOTO_PLAY;
                m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_FILE_INIT;
            }
            else
            {
                if(m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus & E_MPLAYER_PHOTO_STATE_DISPLAY)
                {
                    m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= E_MPLAYER_PHOTO_STATE_PLAY_END;
                    return TRUE;
                }

                return FALSE;
            }
            break;
    #endif  // #if ENABLE_MPLAYER_PHOTO

    #if ENABLE_MPLAYER_MUSIC
        case E_MPLAYER_TYPE_MUSIC:
        #if (ENABLE_AAC)
            if ( IS_AAC_FILE(fileInfo.u8ExtFileName) )
            {
                m_MPlayerInfo[eMPlayerIdx].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_AAC; //AAC
            }
            else
        #endif
        #if (ENABLE_WAV)
            if ( IS_WAV_FILE(fileInfo.u8ExtFileName) )
            {
                m_MPlayerInfo[eMPlayerIdx].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_WAV; //WAV
            }
            else
        #endif
        #if (ENABLE_WMA)
            if ( IS_WMA_FILE(fileInfo.u8ExtFileName) )
            {
                m_MPlayerInfo[eMPlayerIdx].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_WMA; //WMA
            }
            else
        #endif //#if (ENABLE_WMA)
        #if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
            if(IS_LOAS_FILE(fileInfo.u8ExtFileName))
            {
                m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_LOAS;
            }
            else
        #endif //#if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
        #if (ENABLE_OGG)
            if(IS_OGG_FILE(fileInfo.u8ExtFileName))
            {
                m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_OGG;
            }
            else
        #endif
#if (ENABLE_AMR)
            if(IS_AMR_FILE(fileInfo.u8ExtFileName))
            {
                m_MPlayerInfo[eMPlayerIdx].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_AMR; //AMR
            }
            else if(IS_AWB_FILE(fileInfo.u8ExtFileName))
            {
                m_MPlayerInfo[eMPlayerIdx].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_AWB; //AWB
            }
            else
#endif
            {
                m_MPlayerInfo[eMPlayerIdx].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_MP3; //MP3
            }

        #if (!ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
            m_MPlayerInfo[eMPlayerIdx].eMediaSubType = _MApp_MPlayer_VerifyMusicType(&m_MPlayerInfo[eMPlayerIdx].curPlayingFileEntry, m_MPlayerInfo[eMPlayerIdx].eMediaSubType);
        #endif //#if (!ENABLE_NON_PARSING_AUDIO_DATA_INPUT)

            switch(m_MPlayerInfo[eMPlayerIdx].eMediaSubType)
            {
        #if (ENABLE_AAC)
            case E_MPLAYER_SUBTYPE_AAC:
        #endif
        #if (ENABLE_FLAC)
            case E_MPLAYER_SUBTYPE_FLAC:
        #endif
        #if (ENABLE_AC3)
            case E_MPLAYER_SUBTYPE_AC3:
        #endif
        #if (ENABLE_WAV)
            case E_MPLAYER_SUBTYPE_WAV:
        #endif
            default:
            case E_MPLAYER_SUBTYPE_MP3:
        #if (ENABLE_OGG)
            case E_MPLAYER_SUBTYPE_OGG:
        #endif
        #if (ENABLE_AMR)
            case E_MPLAYER_SUBTYPE_AMR:
            case E_MPLAYER_SUBTYPE_AWB:
        #endif
#if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
            case E_MPLAYER_SUBTYPE_LOAS:
#endif //#if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
                MApp_Music_SetFileEntry(&m_MPlayerInfo[eMPlayerIdx].curPlayingFileEntry);
                break;
        #if (ENABLE_WMA)
            case E_MPLAYER_SUBTYPE_WMA:
                MApp_WMA_SetFileEntry(&m_MPlayerInfo[eMPlayerIdx].curPlayingFileEntry);
                break;
        #endif //#if (ENABLE_WMA)
            }

            m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_MUSIC_PLAY;
            m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_FILE_INIT;
            break;
    #endif  // #if ENABLE_MPLAYER_MUSIC

    #if ENABLE_MPLAYER_MOVIE
        case E_MPLAYER_TYPE_MOVIE:
            _MApp_MPlayer_OutputFilename(&fileInfo);


        #if (ENABLE_DVD)
            if(IS_DVD_FILE(fileInfo.u8ExtFileName))
            {
                m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_DVD; //DVD
            }
        #endif
            m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_MOVIE_PLAY;
            m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_FILE_INIT;
            m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_PREDECODE_OK;
            m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &=
                (enumMPlayerKnlFlags1)~(E_MPLAYER_KNL_FLG1_SUBTITLE_VALID |
                  E_MPLAYER_KNL_FLG1_SUBTITLE_ENABLE |
                  E_MPLAYER_KNL_FLG1_SUBTITLE_SHOWN |
                  E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL);
            break;
    #endif  // #if ENABLE_MPLAYER_MOVIE

    #if ENABLE_MPLAYER_TEXT
        case E_MPLAYER_TYPE_TEXT:
            if(IS_TXT_FILE(fileInfo.u8ExtFileName))
            {
                MApp_Text_SetFileEntry(&m_MPlayerInfo[eMPlayerIdx].curPlayingFileEntry);
                m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_TEXT;
                m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_FILE_INIT;
                m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_TEXT_PLAY;
            }
            break;
    #endif  // #if ENABLE_MPLAYER_TEXT

        default:
            break;
        }
    #if RANDOM_PLAY
        _MApp_MPlayer_SetRandomPlayTable(eMPlayerIdx);
    #endif
        return TRUE;
    }
    else
    {
    #if ENABLE_MPLAYER_PHOTO
        if((m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus & E_MPLAYER_PHOTO_STATE_DISPLAY) &&
           (m_MPlayerInfo[eMPlayerIdx].eMediaType == E_MPLAYER_TYPE_PHOTO))
        {
            m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= E_MPLAYER_PHOTO_STATE_PLAY_END;
            return TRUE;
        }
    #endif

        return FALSE;
    }
}

static BOOLEAN _MApp_MPlayer_PlayList(enumMPlayerIdx eMPlayerIdx)
{
//    BOOLEAN bMatched = FALSE;
//    U16 i = 0;
    MPlayerPlayListInfo *pstPlayListInfo, stPlayFileInfo;
    U16  u16PlayListNum;
    U16 u16FileFailCount = 0;
    U32 u32XdataWindowBase;

    MPLAYER_DBG(printf("_MApp_MPlayer_PlayList, u16PlayingIdx=%d\n", m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx););

    u16PlayListNum = m_u16SelectedFileNum[m_MPlayerInfo[eMPlayerIdx].eMediaType];

    //MPLAYER_DBG(printf("    - u16PlayListNum = %u\n",u16PlayListNum));
    if(u16PlayListNum == 0)
    {
        return FALSE;
    }

    // Fix Coverity: CID-182799 Uninitialized scalar variable
    // Clear stPlayFileInfo
    memset( &stPlayFileInfo, 0, sizeof(stPlayFileInfo) );


//    m_u32LyricSubtitleCheckTime = 0;
    m_u32LyricSubtitleCurTime   = -1;
    m_u16CurLyricPos = -1;
    m_u32CurSubtitlePos = -1;
    m_u32PlayCheckTime = -1;

    msAPI_MIU_SetRoundRobin(FALSE);  // If the file is JPG, will enable round robin.
    msAPI_MIU_SetRoundRobin(FALSE);  // If the file is JPG, will enable round robin.

    if(FALSE==_MApp_MPlayer_GetPlayListAddressByMediaType(m_MPlayerInfo[eMPlayerIdx].eMediaType, &u32XdataWindowBase))
    {
        return FALSE;
    }

    pstPlayListInfo = (MPlayerPlayListInfo *) (_PA2VA(u32XdataWindowBase));

    while(m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx < u16PlayListNum)
    {
        memcpy(&stPlayFileInfo, &PLAY_LIST(m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx), sizeof(MPlayerPlayListInfo));

        //eAttribute can not be decode fail , if decode fail it need jump to next index
        if ((stPlayFileInfo.eAttribute&E_MPLAYER_FILE_DECODED_FAIL) == FALSE)
        {
            break;
        }

        u16FileFailCount++;

        if(u16FileFailCount == u16PlayListNum)
        {
            return FALSE;
        }

        if(m_MPlayerInfo[eMPlayerIdx].eMediaPlayingDirection == E_MPLAYER_PLAY_DIRECTION_PREV)
        {
            if(m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx == 0)
            {
                if(m_MPlayerInfo[eMPlayerIdx].eRepeatMode == E_MPLAYER_REPEAT_NONE)
                {
                    return FALSE;
                }
                else
                {
                    m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx = m_u16SelectedFileNum[m_MPlayerInfo[eMPlayerIdx].eMediaType] - 1;
                }
            }
            else
            {
                m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx--;
            }
        }
        else
        {
            m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx++;

            if(m_MPlayerInfo[eMPlayerIdx].eRepeatMode == E_MPLAYER_REPEAT_ALL)
            {
                if(m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx >= m_u16SelectedFileNum[m_MPlayerInfo[eMPlayerIdx].eMediaType])
                {
                    m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx = 0;
                }
            }
            else if(m_MPlayerInfo[eMPlayerIdx].eRepeatMode == E_MPLAYER_REPEAT_NONE)
            {
                if(m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx >= m_u16SelectedFileNum[m_MPlayerInfo[eMPlayerIdx].eMediaType])
                {
                    m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx = m_u16SelectedFileNum[m_MPlayerInfo[eMPlayerIdx].eMediaType] - 1;
                    return FALSE;
                }
            }
        }
    }

    MPLAYER_DBG(printf("Mplayer: %bu, Next File: %c, %x %x %x %x\n",
            eMPlayerIdx,
            (U8)stPlayFileInfo.u16Drive + 'C',
            stPlayFileInfo.u16PlayListPath[0],
            stPlayFileInfo.u16PlayListPath[1],
            stPlayFileInfo.u16PlayListPath[2],
            stPlayFileInfo.u16PlayListPath[3]));

    // Change to new drive when necessary
    if (stPlayFileInfo.u16Drive != m_MPlayerInfo[eMPlayerIdx].u16CurrentDrive)
    {
        if (!_MApp_MPlayer_Browser_ChangeBrowsingDrive(
                &m_MPlayerInfo[eMPlayerIdx].u8BrowserHandle,
                m_MPlayerInfo[eMPlayerIdx].u16CurrentDrive,
                stPlayFileInfo.u16Drive))
        {
            return FALSE;
        }
    }

    memcpy(&m_MPlayerInfo[eMPlayerIdx].curPlayingFileEntry, &stPlayFileInfo.fileEntry, sizeof(stPlayFileInfo.fileEntry));
    m_MPlayerInfo[eMPlayerIdx].u16CurrentDrive = stPlayFileInfo.u16Drive;

    _MApp_MPlayer_OutputFilenameByFileEntry(&m_MPlayerInfo[eMPlayerIdx].curPlayingFileEntry);

    m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_FILE_INIT;
    // Playing the media file ---------------------------------------------------------------------
    switch(m_MPlayerInfo[eMPlayerIdx].eMediaType)
    {
#if ENABLE_MPLAYER_PHOTO
    case E_MPLAYER_TYPE_PHOTO:
        m_s32Photo_LastDecodeIdx = m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx;
        //printf("m_s32Photo_LastDecodeIdx=%ld\n", m_s32Photo_LastDecodeIdx);

        //MApp_MPlayer_ClearPhotoInfo();
        m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus &= (enumMediaPlayingStatus)~E_MPLAYER_PHOTO_STATE_DECODE_PAUSE;

        if(IS_PHOTO_FILE(stPlayFileInfo.u8ExtName))
        {
            if (IS_JPG_FILE(stPlayFileInfo.u8ExtName))
            {
                m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_JPG;

                msAPI_MIU_SetRoundRobin(TRUE);      // Fix the DDR bandwidth issue.

                if (m_u8DecodedPics == 1)
                {
                    // now JPEG decoder on S4 is fast enough for baseline JPEG.
                    // To save memory, JPEG decoder is asked to decode file when
                    // currently displayed JPEG file times out
                    m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= E_MPLAYER_PHOTO_STATE_DECODE_PAUSE;
                }
            }
        #if (ENABLE_BMP)
            else if (IS_BMP_FILE(stPlayFileInfo.u8ExtName))
            {
                m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_BMP;
            }
        #endif
        #if (ENABLE_PNG)
            else if (IS_PNG_FILE(stPlayFileInfo.u8ExtName))
            {
                m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_PNG;
            }
        #endif
        #if (ENABLE_TIFF)
            else if (IS_TIFF_FILE(stPlayFileInfo.u8ExtName))
            {
                m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_TIFF;
            }
        #endif
        #if (ENABLE_GIF)
            else if (IS_GIF_FILE(stPlayFileInfo.u8ExtName))
            {
                m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_GIF;
            }
        #endif
            MApp_Photo_Stop();
            m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_PHOTO_PLAY;
            m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_FILE_INIT;
        }
        break;
#endif  // #if ENABLE_MPLAYER_PHOTO

#if ENABLE_MPLAYER_MUSIC
    case E_MPLAYER_TYPE_MUSIC:
        #if (ENABLE_AAC)
            if ( IS_AAC_FILE(stPlayFileInfo.u8ExtName) )
            {
                m_MPlayerInfo[eMPlayerIdx].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_AAC; //AAC
            }
            else
        #endif
        #if (ENABLE_WAV)
            if ( IS_WAV_FILE(stPlayFileInfo.u8ExtName) )
            {
                m_MPlayerInfo[eMPlayerIdx].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_WAV; //WAV
            }
            else
        #endif
        #if (ENABLE_WMA)
            if ( IS_WMA_FILE(stPlayFileInfo.u8ExtName) )
            {
                m_MPlayerInfo[eMPlayerIdx].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_WMA; //WMA
            }
            else
        #endif //#if (ENABLE_WMA)
        #if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
            if(IS_LOAS_FILE(stPlayFileInfo.u8ExtName))
            {
                m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_LOAS;
            }
            else
        #endif //#if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
        #if (ENABLE_OGG)
            if(IS_OGG_FILE(stPlayFileInfo.u8ExtName))
            {
                m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_OGG;
            }
            else
        #endif
#if (ENABLE_AMR)
            if(IS_AMR_FILE(stPlayFileInfo.u8ExtName))
            {
                m_MPlayerInfo[eMPlayerIdx].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_AMR; //AMR
            }
            else if(IS_AWB_FILE(stPlayFileInfo.u8ExtName))
            {
                m_MPlayerInfo[eMPlayerIdx].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_AWB; //AWB
            }
            else
#endif
            {
                m_MPlayerInfo[eMPlayerIdx].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_MP3; //MP3
            }

        #if (!ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
            m_MPlayerInfo[eMPlayerIdx].eMediaSubType = _MApp_MPlayer_VerifyMusicType(&m_MPlayerInfo[eMPlayerIdx].curPlayingFileEntry, m_MPlayerInfo[eMPlayerIdx].eMediaSubType);
        #endif //#if (!ENABLE_NON_PARSING_AUDIO_DATA_INPUT)

            switch(m_MPlayerInfo[eMPlayerIdx].eMediaSubType)
            {
#if (ENABLE_AAC)
                case E_MPLAYER_SUBTYPE_AAC:
#endif
#if (ENABLE_WAV)
                case E_MPLAYER_SUBTYPE_WAV:
#endif
                default:
                case E_MPLAYER_SUBTYPE_MP3:
#if (ENABLE_OGG)
                case E_MPLAYER_SUBTYPE_OGG:
#endif
#if (ENABLE_FLAC)
                case E_MPLAYER_SUBTYPE_FLAC:
#endif
#if (ENABLE_AC3)
                case E_MPLAYER_SUBTYPE_AC3:
#endif

#if (ENABLE_AMR)
                case E_MPLAYER_SUBTYPE_AMR:
                case E_MPLAYER_SUBTYPE_AWB:
#endif
#if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
                case E_MPLAYER_SUBTYPE_LOAS:
#endif //#if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
                    MApp_Music_SetFileEntry(&m_MPlayerInfo[eMPlayerIdx].curPlayingFileEntry);
                    break;
#if (ENABLE_WMA)
                case E_MPLAYER_SUBTYPE_WMA:
                    MApp_WMA_SetFileEntry(&m_MPlayerInfo[eMPlayerIdx].curPlayingFileEntry);
                    break;
#endif //#if (ENABLE_WMA)
            }

        m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_MUSIC_PLAY;
        m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_FILE_INIT;
        break;
#endif  // #if ENABLE_MPLAYER_MUSIC

#if ENABLE_MPLAYER_MOVIE
    case E_MPLAYER_TYPE_MOVIE:
      #if (ENABLE_DVD)
        if(IS_DVD_FILE(stPlayFileInfo.u8ExtName))
        {
            m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_DVD;    //DVD
        }
      #endif
        m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_FILE_INIT;
        m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_MOVIE_PLAY;
        m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_PREDECODE_OK;
        m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &=
            (enumMPlayerKnlFlags1)~(E_MPLAYER_KNL_FLG1_SUBTITLE_VALID |
              E_MPLAYER_KNL_FLG1_SUBTITLE_ENABLE |
              E_MPLAYER_KNL_FLG1_SUBTITLE_SHOWN |
              E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL);
        break;
#endif  // #if ENABLE_MPLAYER_MOVIE

#if ENABLE_MPLAYER_TEXT
    case E_MPLAYER_TYPE_TEXT:
        if(IS_TXT_FILE(stPlayFileInfo.u8ExtName))
        {
            MApp_Text_SetFileEntry(&m_MPlayerInfo[eMPlayerIdx].curPlayingFileEntry);
            m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_TEXT;
            m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_FILE_INIT;
            m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_TEXT_PLAY;
        }
        break;
#endif  // #if ENABLE_MPLAYER_TEXT

    default:
        break;
    }
#if RANDOM_PLAY
    _MApp_MPlayer_SetRandomPlayTable(eMPlayerIdx);
#endif
    return TRUE;
}
static BOOLEAN _MApp_MPlayer_PlayPrev(enumMPlayerIdx eMPlayerIdx)
{
    MPLAYER_DBG(printf("_MApp_MPlayer_PlayPrev\n"););
    if (eMPlayerIdx == E_MPLAYER_FOREGROUND_PLAYER)
    {
        m_eZoom = E_MPLAYER_ZOOM_1;

#if ENABLE_MPLAYER_MOVIE
        if( m_MPlayerInfo[eMPlayerIdx].eMediaType == E_MPLAYER_TYPE_MOVIE ) // movie
        {
            m_eMoviePlayMode = E_MPLAYER_MOVIE_NORMAL;
            m_eMovieMainExit = EXIT_VDPLAYER_NULL;
        }
#endif
    }
    else if (eMPlayerIdx == E_MPLAYER_BACKGROUND_PLAYER)
    {
        m_eMusicPlayMode = E_MPLAYER_MUSIC_NORMAL;
    }
    m_MPlayerInfo[eMPlayerIdx].eMediaPlayingDirection = E_MPLAYER_PLAY_DIRECTION_PREV;

    if( (m_MPlayerInfo[eMPlayerIdx].eRepeatMode == E_MPLAYER_REPEAT_1)
      ||(m_MPlayerInfo[eMPlayerIdx].ePlayMode == E_MPLAYER_PLAY_ONE) )
    {
        // Do nothing ...
        // it should play current file repeatly.
    }
    else
    {
        U32 u32FindFrom, u32NextDecodeIdx;
    #if ENABLE_MPLAYER_PHOTO
        if( m_MPlayerInfo[eMPlayerIdx].eMediaType == E_MPLAYER_TYPE_PHOTO )
        {
            if( m_u32Photo_PlayPrevDecodeFailCount )
            {
                u32FindFrom = m_s32Photo_LastDecodeFailIdx;
            }
            else
            {
                u32FindFrom = m_u32PhotoCurrentDisplayedIdx;
            }
        }
        else
    #endif
        {
            u32FindFrom = m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx;
        }

        //printf("u32FindFrom=%lu\n", u32FindFrom);

        if(((m_MPlayerInfo[eMPlayerIdx].ePlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY) ||
            (m_MPlayerInfo[eMPlayerIdx].ePlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT)) &&
            (u32FindFrom <= m_MPlayerInfo[eMPlayerIdx].u16TotalDirNum))
        {
            // first file in directory.
            if(m_MPlayerInfo[eMPlayerIdx].eRepeatMode == E_MPLAYER_REPEAT_NONE)
            {
                // Play directory and repeat mode is none --> return to file list
                return FALSE;
            }
            u32NextDecodeIdx = m_MPlayerInfo[eMPlayerIdx].u16TotalFileNum - 1;
        }
        else if(((m_MPlayerInfo[eMPlayerIdx].ePlayMode == E_MPLAYER_PLAY_SELECTED) ||
                 (m_MPlayerInfo[eMPlayerIdx].ePlayMode == E_MPLAYER_PLAY_SELECTED_FROM_CURRENT)) &&
                 (u32FindFrom == 0))
        {
            //first file in playlist.
            if(m_MPlayerInfo[eMPlayerIdx].eRepeatMode == E_MPLAYER_REPEAT_NONE)
            {
                // Play list and repeat mode is none --> return to file list
                return FALSE;
            }
            u32NextDecodeIdx = m_u16SelectedFileNum[m_MPlayerInfo[eMPlayerIdx].eMediaType] - 1;
        }
        else
        {
            u32NextDecodeIdx = u32FindFrom - 1;
        }
        //printf(" -> u32NextDecodeIdx=%lu\n", u32NextDecodeIdx);

        m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx = u32NextDecodeIdx;
    }

    BOOLEAN bRet = FALSE;

    if((m_MPlayerInfo[eMPlayerIdx].ePlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY) ||
       (m_MPlayerInfo[eMPlayerIdx].ePlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT))
    {
        bRet = _MApp_MPlayer_PlayDirectory(eMPlayerIdx);
    }
    else
    {
        bRet = _MApp_MPlayer_PlayList(eMPlayerIdx);
    }

#ifdef MEDIA_PLAYER_HIGHLIGHT_CHANGE
    if ((eMPlayerIdx == E_MPLAYER_FOREGROUND_PLAYER) && (bRet==TRUE))
    {
        NOTIFY(E_MPLAYER_NOTIFY_PLAY_PREVIOUS_FILE, NULL);
    }
#endif
    return bRet;
}

static BOOLEAN _MApp_MPlayer_PlayNext(enumMPlayerIdx eMPlayerIdx)
{
    if (eMPlayerIdx == E_MPLAYER_FOREGROUND_PLAYER)
    {
        m_eZoom = E_MPLAYER_ZOOM_1;
//        m_ePhotoRotate = E_MPLAYER_PHOTO_ROTATE_0;
        m_eMoviePlayMode = E_MPLAYER_MOVIE_NORMAL;
        m_eMovieMainExit = EXIT_VDPLAYER_NULL;
    }
    else if (eMPlayerIdx == E_MPLAYER_BACKGROUND_PLAYER)
    {
        m_eMusicPlayMode = E_MPLAYER_MUSIC_NORMAL;
    }
    m_MPlayerInfo[eMPlayerIdx].eMediaPlayingDirection = E_MPLAYER_PLAY_DIRECTION_NEXT;

    MPLAYER_DBG(printf("_MApp_MPlayer_PlayNext()\n"));

    if(m_MPlayerInfo[eMPlayerIdx].eRepeatMode != E_MPLAYER_REPEAT_1)
    {
    #if RANDOM_PLAY
        if(m_MPlayerInfo[eMPlayerIdx].eRandomMode == E_MPLAYER_RANDOM && m_bPlayNext == FALSE)
        {
            U16 u16PlayingIdxTemp = _MApp_MPlayer_RandomPlay_Rand(eMPlayerIdx);

            if(u16PlayingIdxTemp == INVALID_RANDOM_NUMBER)
            {
                return FALSE;
            }
            else
            {
                m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx = u16PlayingIdxTemp;
            }
        }
        else
    #endif
        {
            if(TRUE == bPauseToNextFlag)
            {
                bPauseToNextFlag =FALSE;
            }
            else
            {
                m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx++;
            }
        }
    }
    if(m_MPlayerInfo[eMPlayerIdx].eRepeatMode == E_MPLAYER_REPEAT_ALL)
    {
        if((m_MPlayerInfo[eMPlayerIdx].ePlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY) ||
           (m_MPlayerInfo[eMPlayerIdx].ePlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT))
        {
            if(m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx >= m_MPlayerInfo[eMPlayerIdx].u16TotalFileNum)
            {
                m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx = 0;
            }
        }
        else
        {
            if(m_MPlayerInfo[eMPlayerIdx].eMediaType < E_MPLAYER_TYPE_NUM)
            {
                if(m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx >= m_u16SelectedFileNum[m_MPlayerInfo[eMPlayerIdx].eMediaType])
                {
                    m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx = 0;
                }
            }
            else
            {
                return FALSE;
            }
        }
    }
    else if(m_MPlayerInfo[eMPlayerIdx].eRepeatMode == E_MPLAYER_REPEAT_NONE)
    {
        if((m_MPlayerInfo[eMPlayerIdx].ePlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY) ||
           (m_MPlayerInfo[eMPlayerIdx].ePlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT))
        {
            if(m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx >= m_MPlayerInfo[eMPlayerIdx].u16TotalFileNum)
            {
                m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx = m_MPlayerInfo[eMPlayerIdx].u16TotalFileNum - 1;
                 return FALSE;
            }
        }
        else
        {
            if(m_MPlayerInfo[eMPlayerIdx].eMediaType < E_MPLAYER_TYPE_NUM)
            {
                if(m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx >= m_u16SelectedFileNum[m_MPlayerInfo[eMPlayerIdx].eMediaType])
                {
                    m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx = m_u16SelectedFileNum[m_MPlayerInfo[eMPlayerIdx].eMediaType] - 1;
                    return FALSE;
                }
            }
            else
            {
                return FALSE;
            }
        }
    }

    if((m_MPlayerInfo[eMPlayerIdx].ePlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY) ||
       (m_MPlayerInfo[eMPlayerIdx].ePlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT))
    {
        //MPLAYER_DBG(printf("        - play one directory\n"));
    #ifdef MEDIA_PLAYER_HIGHLIGHT_CHANGE
        BOOLEAN bRet = FALSE;

        if (eMPlayerIdx == E_MPLAYER_FOREGROUND_PLAYER)
        {
            bRet = _MApp_MPlayer_PlayDirectory(eMPlayerIdx);
            if (bRet)
            {
                NOTIFY(E_MPLAYER_NOTIFY_PLAY_NEXT_FILE, NULL);
            }
            return bRet;
        }
        else
        {
        return(_MApp_MPlayer_PlayDirectory(eMPlayerIdx));
    }
    #else
        return(_MApp_MPlayer_PlayDirectory(eMPlayerIdx));
    #endif
    }
    else
    {
        if(m_MPlayerInfo[eMPlayerIdx].eMediaType < E_MPLAYER_TYPE_NUM)
        {
            //MPLAYER_DBG(printf("        - u16PlayingIdx = %d\n", m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx));
            //MPLAYER_DBG(printf("        - m_u16SelectedFileNum[%bu] = %d\n", (U8)m_MPlayerInfo[eMPlayerIdx].eMediaType, m_u16SelectedFileNum[m_MPlayerInfo[eMPlayerIdx].eMediaType]));
            if(m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx >= m_u16SelectedFileNum[m_MPlayerInfo[eMPlayerIdx].eMediaType])
            {
            #if ENABLE_MPLAYER_PHOTO
                if(m_MPlayerInfo[eMPlayerIdx].eMediaType == E_MPLAYER_TYPE_PHOTO)
                {
                    if(m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 & E_MPLAYER_KNL_FLG1_PHOTO_PLAY)
                    {
                        m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= E_MPLAYER_PHOTO_STATE_PLAY_END;
                        return TRUE;
                    }
                }
            #endif
                return FALSE;
            }
        }
        else
        {
            return FALSE;
        }
        //MPLAYER_DBG(printf("        - play list\n\n\n"));
    #ifdef MEDIA_PLAYER_HIGHLIGHT_CHANGE
        {
            BOOLEAN bRet = FALSE;

            if (eMPlayerIdx == E_MPLAYER_FOREGROUND_PLAYER)
            {
                bRet = _MApp_MPlayer_PlayList(eMPlayerIdx);
                if (bRet)
                {
                    NOTIFY(E_MPLAYER_NOTIFY_PLAY_NEXT_FILE, NULL);
                }
                return bRet;
            }
            else
            {
                return _MApp_MPlayer_PlayList(eMPlayerIdx);
            }
        }
    #else
        return _MApp_MPlayer_PlayList(eMPlayerIdx);
    #endif
    }

    return TRUE;
}

static BOOLEAN _MApp_MPlayer_PlayAgain(enumMPlayerIdx eMPlayerIdx)
{
    m_eZoom = E_MPLAYER_ZOOM_1;
    m_eMoviePlayMode = E_MPLAYER_MOVIE_NORMAL;
    m_eMovieMainExit = EXIT_VDPLAYER_NULL;
    m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_FILE_INIT;
 #if ENABLE_MPLAYER_MOVIE
    m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_PREDECODE_OK;
    m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &=
        (enumMPlayerKnlFlags1)~(E_MPLAYER_KNL_FLG1_SUBTITLE_VALID |
          E_MPLAYER_KNL_FLG1_SUBTITLE_ENABLE|
          E_MPLAYER_KNL_FLG1_SUBTITLE_SHOWN |
          E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL);
 #endif
    m_u32LyricSubtitleCurTime   = -1;

    return TRUE;
}

/*
static void _MApp_MPlayer_ExitPlayback(void)
{
    _MApp_MPlayer_Change2CurrentDirectory();
    _MApp_MPlayer_Browser_EnumCurDirectory();
}
*/

#if ENABLE_MPLAYER_PHOTO
static BOOLEAN _MApp_MPlayer_PhotoProcessPrevNext(BOOLEAN bNext)
{
    BOOLEAN bErrorPending = FALSE;

    if(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaPlayingStatus & E_MPLAYER_PHOTO_STATE_ERROR_PENDING)
    {
        bErrorPending = TRUE;
    }
    m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaPlayingStatus &= (enumMediaPlayingStatus)~E_MPLAYER_PHOTO_STATE_DISPLAY;
    m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaPlayingStatus &= (enumMediaPlayingStatus)~E_MPLAYER_PHOTO_STATE_ERROR_PENDING;

    if(bNext)
    {
    #if RANDOM_PLAY
        if(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eRandomMode == E_MPLAYER_RANDOM)
        {
            m_u8DecodedPics = 0;
            m_ePhotoType[1] = E_MPLAYER_SUBTYPE_INVALID;

            if ((m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_JPG)
            #if (ENABLE_BMP)
             || (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_BMP)
            #endif
            #if (ENABLE_PNG)
             || (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_PNG)
            #endif
            #if (ENABLE_TIFF)
             || (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_TIFF)
            #endif
            #if (ENABLE_GIF)
             || (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_GIF)
            #endif
             )
            {
                MApp_Photo_Stop();
            }

            m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].u16PlayingIdx = m_u32PhotoCurrentDisplayedIdx;
            if(!_MApp_MPlayer_PlayNext(E_MPLAYER_FOREGROUND_PLAYER))
            {
                //_MApp_MPlayer_ExitPlayback();
                return FALSE;
            }
        }
        else
    #endif
        {
            if(bErrorPending == TRUE)
            {
                return TRUE;
            }

            //if init done
            if(!(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_FILE_INIT))
            {
                if(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaPlayingStatus & E_MPLAYER_PHOTO_STATE_DECODE_PAUSE)
                {
                    m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaPlayingStatus &= (enumMediaPlayingStatus)~E_MPLAYER_PHOTO_STATE_DECODE_PAUSE;
                    m_u8DecodedPics = 0;
                    m_ePhotoType[1] = E_MPLAYER_SUBTYPE_INVALID;
                }
                else
                {
                    EN_RET eRet;
                    eRet = _MApp_MPlayer_PhotoDecode();

                    if(eRet == EXIT_PHOTO_DECODE_DONE)
                    {
                        m_ePhotoType[m_u8DecodedPics] = m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType;
                        m_u8DecodedPics++;
                    }

                    if((eRet == EXIT_PHOTO_DECODING)&&(m_u8DecodedPics<2))
                    {
                        if(m_u8DecodedPics==1)
                        {
                            m_u8DecodedPics--;
                            m_ePhotoType[1] = E_MPLAYER_SUBTYPE_INVALID;
                            return TRUE;
                        }

                        if ((m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_JPG)
                        #if (ENABLE_BMP)
                        ||  (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_BMP)
                        #endif
                        #if (ENABLE_PNG)
                        ||  (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_PNG)
                        #endif
                        #if (ENABLE_TIFF)
                        ||  (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_TIFF)
                        #endif
                        #if (ENABLE_GIF)
                        ||  (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_GIF)
                        #endif
                        )
                        {
                            MApp_Photo_Stop();
                        }
                    }
                    else
                    {
                        if(m_u8DecodedPics==2)
                        {
                            m_u8DecodedPics--;
                            m_ePhotoType[0] = m_ePhotoType[1];
                            m_ePhotoType[1] = E_MPLAYER_SUBTYPE_INVALID;
                            return TRUE;
                        }
                        else if(m_ePhotoValidOrNot == E_MPLAYER_PHOTO_INVALID)
                        {
                            m_u8DecodedPics = 0;
                            m_ePhotoType[0] = E_MPLAYER_SUBTYPE_INVALID;
                            m_ePhotoType[1] = E_MPLAYER_SUBTYPE_INVALID;
                            return TRUE;
                        }
                    }
                    m_u8DecodedPics = 0;
                    if(!_MApp_MPlayer_PlayNext(E_MPLAYER_FOREGROUND_PLAYER))
                    {
                        //_MApp_MPlayer_ExitPlayback();
                        return FALSE;
                    }
                }
            }
            else
            {
                if(m_u8DecodedPics==0)
                {
                    //do nothing.
                }
                else if(m_u8DecodedPics==1)
                {
                    m_u8DecodedPics--;
                }
                else if(m_u8DecodedPics==2)
                {
                    m_u8DecodedPics--;
                    m_ePhotoType[0] = m_ePhotoType[1];
                    m_ePhotoType[1] = E_MPLAYER_SUBTYPE_INVALID;
                }
                else
                {
                    printf("[ERROR]:m_u8DecodedPics > 2\n");
                }
            }
        }
    }
    else
    {
        m_u8DecodedPics = 0;
        m_ePhotoType[1] = E_MPLAYER_SUBTYPE_INVALID;

        if ((m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_JPG)
        #if (ENABLE_BMP)
        ||  (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_BMP)
        #endif
        #if (ENABLE_PNG)
        ||  (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_PNG)
        #endif
        #if (ENABLE_TIFF)
        ||  (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_TIFF)
        #endif
        )
        {
            MApp_Photo_Stop();
        }

        m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaPlayingStatus &= (enumMediaPlayingStatus)~E_MPLAYER_PHOTO_STATE_PLAY_END;

        if(!_MApp_MPlayer_PlayPrev(E_MPLAYER_FOREGROUND_PLAYER))
        {
            //_MApp_MPlayer_ExitPlayback();
            return FALSE;
        }
    }
    return TRUE;
}
#endif  // #if ENABLE_MPLAYER_PHOTO

static BOOLEAN _MApp_MPlayer_ReCalcDeviceDriveInfo(void)
{
    U8 u8DeviceCnt;
#if (ENABLE_USB || ENABLE_USB_2 || ENABLE_USB_3 || ENABLE_USB_4)
    U8 u8LunIdx;
    U8 u8IndexEnd;
    U8 i, driveCount;
    U32 u32DeviceValidMask;
#endif

    u8DeviceCnt = 0;
    m_u8TotalDriveNum = MApp_MassStorage_GetTotalDriveNum();

#if (!ENABLE_USB_2)
    m_u32DriveStatus = ((U32)1<<m_u8TotalDriveNum) - 1;
#endif

    memset(m_MPlayerDeviceStatus, 0, sizeof(MPlayerDeviceStatus)*NUM_OF_SUPPORT_DEVICES);

#if (ENABLE_USB)
    u8IndexEnd = MSD_USB_INDEX_END;
    u32DeviceValidMask = BMASK((MSD_USB_INDEX_START+MSD_USB_NUM-1):MSD_USB_INDEX_START);
    //printf("USB1: u16DeviceValidMask=%X\n", u16DeviceValidMask);
    m_MPlayerDeviceStatus[0].u16LunValid = m_u32DeviceValidStatus & (u32DeviceValidMask); // daniel_check

    if(m_MPlayerDeviceStatus[0].u16LunValid)
    {
        // The 1st device is USB host 0.
        m_MPlayerDeviceStatus[0].eDeviceType = E_MPLAYER_USB0;
        if(m_MPlayerDeviceStatus[0].u16LunValid & (1<<MSD_USB_INDEX_START))
        {
            //if(MApp_MassStorage_DeviceGetStatus(MSD_USB_INDEX_START, 0))
            { // Use sequencial search to find all drives.
                driveCount = 0;
                for(i = 0; i < NUM_OF_MAX_DRIVE; i++)
                {
                    if(driveCount >= MApp_MassStorage_GetTotalDriveNumPerPort(MSD_PORT_1))
                    {
                        break;
                    }
                    //Set partition bit
                    if(MApp_MassStorage_GetDrivePort(i) == MSD_PORT_1)
                    {
                        m_MPlayerDeviceStatus[0].u16PartitionValid[MSD_USB_INDEX_START] |= (1<<i);
                        driveCount++;
                    }
                }
                //printf("[USB0] Partition Valid : 0x%X\n", m_MPlayerDeviceStatus[0].u16PartitionValid[0]);
            }
        }
        else
        {   // USB card reader.
            for(u8LunIdx=MSD_USB_INDEX_START;u8LunIdx<u8IndexEnd;u8LunIdx++)
            {
                if(m_MPlayerDeviceStatus[0].u16LunValid & (1<<u8LunIdx))
                {
                    for(i=0; i<NUM_OF_MAX_DRIVE; i++)
                    {
                        if(MApp_MassStorage_GetDriveDevice(i) == u8LunIdx)
                            m_MPlayerDeviceStatus[0].u16PartitionValid[u8LunIdx] |= (1<<i);
                    }
                }
            }
        }
    }
    u8DeviceCnt++;
#endif

#if (ENABLE_USB_2)
    u8IndexEnd = MSD_USB_2_INDEX_END;
/*
  #if (ENABLE_USB)
    m_MPlayerDeviceStatus[u8DeviceCnt].u16LunValid = m_u32DeviceValidStatus & 0xF0;
  #else
    m_MPlayerDeviceStatus[u8DeviceCnt].u16LunValid = m_u32DeviceValidStatus & 0xF;
  #endif
*/

  u32DeviceValidMask = BMASK((MSD_USB_2_INDEX_START+MSD_USB_2_NUM-1):MSD_USB_2_INDEX_START);
  //printf("USB2: u16DeviceValidMask=%X\n", u16DeviceValidMask);
  m_MPlayerDeviceStatus[u8DeviceCnt].u16LunValid = m_u32DeviceValidStatus & (u32DeviceValidMask); // daniel_check

    if(m_MPlayerDeviceStatus[u8DeviceCnt].u16LunValid)
    {
        // The 2nd device is USB2
        //m_MPlayerDeviceStatus[u8DeviceCnt].eDeviceType = E_MPLAYER_USB1;
        //m_MPlayerDeviceStatus[u8DeviceCnt].u16LunValid = (m_u32DeviceValidStatus & 0xF0)>>4;
        //if(m_MPlayerDeviceStatus[u8DeviceCnt].u16LunValid)

        // The 1st device is USB host 0.
        m_MPlayerDeviceStatus[u8DeviceCnt].eDeviceType = E_MPLAYER_USB1;
        if(m_MPlayerDeviceStatus[u8DeviceCnt].u16LunValid & (1<<MSD_USB_2_INDEX_START))
        {
            //if(MApp_MassStorage_DeviceGetStatus(MSD_USB_2_INDEX_START, 0))
            { // Use sequencial search to find all drives.
                driveCount = 0;
                for(i = 0; i < NUM_OF_MAX_DRIVE; i++)
                {
                    if(driveCount >= MApp_MassStorage_GetTotalDriveNumPerPort(MSD_PORT_2))
                    {
                        break;
                    }
                    //Set partition bit
                    if(MApp_MassStorage_GetDrivePort(i) == MSD_PORT_2)
                    {
                        m_MPlayerDeviceStatus[u8DeviceCnt].u16PartitionValid[MSD_USB_2_INDEX_START] |= (1<<i);
                        driveCount++;
                    }
                }
                //printf("[USB1] Partition Valid : 0x%X\n", m_MPlayerDeviceStatus[1].u16PartitionValid[MSD_USB_2_INDEX_START]);
            }
        }
        else
        {   // USB card reader.
            for(u8LunIdx=MSD_USB_2_INDEX_START;u8LunIdx<u8IndexEnd;u8LunIdx++)
            {
                if(m_MPlayerDeviceStatus[u8DeviceCnt].u16LunValid & (1<<u8LunIdx))
                {
                    for(i=0; i<NUM_OF_MAX_DRIVE; i++)
                    {
                        if(MApp_MassStorage_GetDriveDevice(i) == u8LunIdx)
                            m_MPlayerDeviceStatus[u8DeviceCnt].u16PartitionValid[u8LunIdx] |= (1<<i);
                    }
                }
            }
        }

    }
    //Re-calculate drive status
    m_u32DriveStatus = 0;
    for(i=0; i < NUM_OF_MAX_DRIVE; i++)
    {
        if(MApp_MassStorage_GetDrivePort(i) == MSD_PORT_1 ||
            MApp_MassStorage_GetDrivePort(i) == MSD_PORT_2 ||
            MApp_MassStorage_GetDrivePort(i) == MSD_PORT_3 ||
            MApp_MassStorage_GetDrivePort(i) == MSD_PORT_4)
        {
            //printf("[Drive %bu] is in PORT%bu\n", i, (U8)MApp_MassStorage_GetDrivePort(i));
            m_u32DriveStatus |= ((U32)1<<i);
        }
    }
    //printf("================> m_u8TotalDriveNum(%bu)\n", m_u8TotalDriveNum);
    //printf("[m_u32DriveStatus] 0x%lX\n", m_u32DriveStatus);
    u8DeviceCnt++;
#endif

#if (ENABLE_USB_3)
    u8IndexEnd = MSD_USB_3_INDEX_END;
/*
  #if (ENABLE_USB)
    m_MPlayerDeviceStatus[u8DeviceCnt].u16LunValid = m_u32DeviceValidStatus & 0xF0;
  #else
    m_MPlayerDeviceStatus[u8DeviceCnt].u16LunValid = m_u32DeviceValidStatus & 0xF;
  #endif
*/

  u32DeviceValidMask = BMASK((MSD_USB_3_INDEX_START+MSD_USB_3_NUM-1):MSD_USB_3_INDEX_START);
  //printf("USB2: u16DeviceValidMask=%X\n", u16DeviceValidMask);
  m_MPlayerDeviceStatus[u8DeviceCnt].u16LunValid = m_u32DeviceValidStatus & (u32DeviceValidMask); // daniel_check

    if(m_MPlayerDeviceStatus[u8DeviceCnt].u16LunValid)
    {
        // The 2nd device is USB2
        //m_MPlayerDeviceStatus[u8DeviceCnt].eDeviceType = E_MPLAYER_USB1;
        //m_MPlayerDeviceStatus[u8DeviceCnt].u16LunValid = (m_u32DeviceValidStatus & 0xF0)>>4;
        //if(m_MPlayerDeviceStatus[u8DeviceCnt].u16LunValid)

        // The 1st device is USB host 0.
        m_MPlayerDeviceStatus[u8DeviceCnt].eDeviceType = E_MPLAYER_USB2;
        if(m_MPlayerDeviceStatus[u8DeviceCnt].u16LunValid & (1<<MSD_USB_3_INDEX_START))
        {
            //if(MApp_MassStorage_DeviceGetStatus(MSD_USB_2_INDEX_START, 0))
            { // Use sequencial search to find all drives.
                driveCount = 0;
                for(i = 0; i < NUM_OF_MAX_DRIVE; i++)
                {
                    if(driveCount >= MApp_MassStorage_GetTotalDriveNumPerPort(MSD_PORT_3))
                    {
                        break;
                    }
                    //Set partition bit
                    if(MApp_MassStorage_GetDrivePort(i) == MSD_PORT_3)
                    {
                        m_MPlayerDeviceStatus[u8DeviceCnt].u16PartitionValid[MSD_USB_3_INDEX_START] |= (1<<i);
                        driveCount++;
                    }
                }
                //printf("[USB1] Partition Valid : 0x%X\n", m_MPlayerDeviceStatus[1].u16PartitionValid[MSD_USB_2_INDEX_START]);
            }
        }
        else
        {   // USB card reader.
            for(u8LunIdx=MSD_USB_3_INDEX_START;u8LunIdx<u8IndexEnd;u8LunIdx++)
            {
                if(m_MPlayerDeviceStatus[u8DeviceCnt].u16LunValid & (1<<u8LunIdx))
                {
                    for(i=0; i<NUM_OF_MAX_DRIVE; i++)
                    {
                        if(MApp_MassStorage_GetDriveDevice(i) == u8LunIdx)
                            m_MPlayerDeviceStatus[u8DeviceCnt].u16PartitionValid[u8LunIdx] |= (1<<i);
                    }
                }
            }
        }

    }
    //Re-calculate drive status
    m_u32DriveStatus = 0;
    for(i=0; i < NUM_OF_MAX_DRIVE; i++)
    {
        if(MApp_MassStorage_GetDrivePort(i) == MSD_PORT_1 ||
            MApp_MassStorage_GetDrivePort(i) == MSD_PORT_2 ||
            MApp_MassStorage_GetDrivePort(i) == MSD_PORT_3 ||
            MApp_MassStorage_GetDrivePort(i) == MSD_PORT_4)
        {
            //printf("[Drive %bu] is in PORT%bu\n", i, (U8)MApp_MassStorage_GetDrivePort(i));
            m_u32DriveStatus |= ((U32)1<<i);
        }
    }
    //printf("================> m_u8TotalDriveNum(%bu)\n", m_u8TotalDriveNum);
    //printf("[m_u32DriveStatus] 0x%lX\n", m_u32DriveStatus);
    u8DeviceCnt++;
#endif

#if (ENABLE_USB_4)
    u8IndexEnd = MSD_USB_4_INDEX_END;
/*
  #if (ENABLE_USB)
    m_MPlayerDeviceStatus[u8DeviceCnt].u16LunValid = m_u32DeviceValidStatus & 0xF0;
  #else
    m_MPlayerDeviceStatus[u8DeviceCnt].u16LunValid = m_u32DeviceValidStatus & 0xF;
  #endif
*/

  u32DeviceValidMask = BMASK((MSD_USB_4_INDEX_START+MSD_USB_4_NUM-1):MSD_USB_4_INDEX_START);
  //printf("USB2: u16DeviceValidMask=%X\n", u16DeviceValidMask);
  m_MPlayerDeviceStatus[u8DeviceCnt].u16LunValid = m_u32DeviceValidStatus & (u32DeviceValidMask); // daniel_check

    if(m_MPlayerDeviceStatus[u8DeviceCnt].u16LunValid)
    {
        // The 2nd device is USB2
        //m_MPlayerDeviceStatus[u8DeviceCnt].eDeviceType = E_MPLAYER_USB1;
        //m_MPlayerDeviceStatus[u8DeviceCnt].u16LunValid = (m_u32DeviceValidStatus & 0xF0)>>4;
        //if(m_MPlayerDeviceStatus[u8DeviceCnt].u16LunValid)

        // The 1st device is USB host 0.
        m_MPlayerDeviceStatus[u8DeviceCnt].eDeviceType = E_MPLAYER_USB3;
        if(m_MPlayerDeviceStatus[u8DeviceCnt].u16LunValid & (1<<MSD_USB_4_INDEX_START))
        {
            //if(MApp_MassStorage_DeviceGetStatus(MSD_USB_2_INDEX_START, 0))
            { // Use sequencial search to find all drives.
                driveCount = 0;
                for(i = 0; i < NUM_OF_MAX_DRIVE; i++)
                {
                    if(driveCount >= MApp_MassStorage_GetTotalDriveNumPerPort(MSD_PORT_4))
                    {
                        break;
                    }
                    //Set partition bit
                    if(MApp_MassStorage_GetDrivePort(i) == MSD_PORT_4)
                    {
                        m_MPlayerDeviceStatus[u8DeviceCnt].u16PartitionValid[MSD_USB_4_INDEX_START] |= (1<<i);
                        driveCount++;
                    }
                }
                //printf("[USB1] Partition Valid : 0x%X\n", m_MPlayerDeviceStatus[1].u16PartitionValid[MSD_USB_2_INDEX_START]);
            }
        }
        else
        {   // USB card reader.
            for(u8LunIdx=MSD_USB_4_INDEX_START;u8LunIdx<u8IndexEnd;u8LunIdx++)
            {
                if(m_MPlayerDeviceStatus[u8DeviceCnt].u16LunValid & (1<<u8LunIdx))
                {
                    for(i=0; i<NUM_OF_MAX_DRIVE; i++)
                    {
                        if(MApp_MassStorage_GetDriveDevice(i) == u8LunIdx)
                            m_MPlayerDeviceStatus[u8DeviceCnt].u16PartitionValid[u8LunIdx] |= (1<<i);
                    }
                }
            }
        }

    }
    //Re-calculate drive status
    m_u32DriveStatus = 0;
    for(i=0; i < NUM_OF_MAX_DRIVE; i++)
    {
        if(MApp_MassStorage_GetDrivePort(i) == MSD_PORT_1 ||
            MApp_MassStorage_GetDrivePort(i) == MSD_PORT_2 ||
            MApp_MassStorage_GetDrivePort(i) == MSD_PORT_3 ||
            MApp_MassStorage_GetDrivePort(i) == MSD_PORT_4)
        {
            //printf("[Drive %bu] is in PORT%bu\n", i, (U8)MApp_MassStorage_GetDrivePort(i));
            m_u32DriveStatus |= ((U32)1<<i);
        }
    }
    //printf("================> m_u8TotalDriveNum(%bu)\n", m_u8TotalDriveNum);
    //printf("[m_u32DriveStatus] 0x%lX\n", m_u32DriveStatus);
    u8DeviceCnt++;
#endif

#if (ENABLE_CARDREADER)
    // The 3rd device is card reader
    if( MApp_MassStorage_GetValidDevice() & (1<<MSD_CREADER_INDEX_START) )
    {
        if(MApp_MassStorage_DeviceGetStatus(MSD_CREADER_INDEX_START, 0))
        {
            // The 3rd device is card reader
            m_MPlayerDeviceStatus[u8DeviceCnt].eDeviceType = E_MPLAYER_CARDREADER0;
            m_MPlayerDeviceStatus[u8DeviceCnt].u16LunValid = 1;
            m_MPlayerDeviceStatus[u8DeviceCnt].u16PartitionValid[0] = 1;
        }
    }
#endif
    if(m_u8TotalDriveNum)
    {
        _MApp_MPlayer_MapDriveToPhysicalDevice();
        return TRUE;
    }
    return FALSE;
}

static BOOLEAN _MApp_MPlayer_DisconnectDrive(void)
{
    U8 i;
    enumMPlayerIdx eMPlayerIdx;

    MApp_MPlayer_StopPreview();

#if ENABLE_MPLAYER_PHOTO
    if(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_PHOTO_PLAY)
    {
        switch(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType)
        {
        case E_MPLAYER_SUBTYPE_JPG:
        #if (ENABLE_BMP)
        case E_MPLAYER_SUBTYPE_BMP:
        #endif
        #if (ENABLE_PNG)
        case E_MPLAYER_SUBTYPE_PNG:
        #endif
        #if (ENABLE_TIFF)
        case E_MPLAYER_SUBTYPE_TIFF:
        #endif
        #if (ENABLE_GIF)
        case E_MPLAYER_SUBTYPE_GIF:
        #endif
#if (ENABLE_4K2K == 1)
       MApp_Photo_Display_Disable4K2KPhotoDisplay();
#endif
            MApp_Photo_Stop();
            break;

        default:
            break;
        }

        m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_PHOTO_PLAY;
    }
#endif  // #if ENABLE_MPLAYER_PHOTO
#if ENABLE_MPLAYER_MUSIC
    MApp_MPlayer_StopMusic();
#endif  // #if ENABLE_MPLAYER_MUSIC
#if ENABLE_MPLAYER_MOVIE
    if(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_MOVIE_PLAY)
    {
        msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
        MApi_XC_GenerateBlackVideo(ENABLE, MAIN_WINDOW);
#if ENABLE_DIVX_PLUS
        g_bChangeFile = FALSE;
#endif
        MApp_VDPlayer_Stop();

#if (ENABLE_SUBTITLE_DMP)
        if(m_u8ExternalSubtitleFileHandle != FCTRL_INVALID_FILE_HANDLE)
        {
            msAPI_FCtrl_FileClose(m_u8ExternalSubtitleFileHandle);
            m_u8ExternalSubtitleFileHandle = FCTRL_INVALID_FILE_HANDLE;
#if (ENABLE_INTERNAL_BMP_SUBTITLE || ENABLE_EXTERNAL_BMP_SUBTITLE)
            msAPI_MpegSP_Dinit();
#endif
        }
#endif //#if (ENABLE_SUBTITLE_DMP)

        m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_MOVIE_PLAY;
    }
#endif  // #if ENABLE_MPLAYER_MOVIE
#if ENABLE_MPLAYER_TEXT
    if(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_TEXT_PLAY)
    {
    }
#endif  // #if ENABLE_MPLAYER_TEXT

    MApp_FileBrowser_DeInit();

    if(MApp_MassStorage_GetDrivePort(m_u16CurDriveIdx)!=INVALID_MSD_PORT)
    {
        MApp_MassStorage_DriveDisconnect(m_u16CurDriveIdx);
    }

#ifdef ENABLE_PTP
    MApp_PTP_SetDeviceState(FALSE);
#endif

    for (eMPlayerIdx = E_MPLAYER_FOREGROUND_PLAYER; eMPlayerIdx < E_MPLAYER_MAX_CONCURRENT_PLAYER_NUM; eMPlayerIdx++)
    {
        m_MPlayerInfo[eMPlayerIdx].u8BrowserHandle = INVALID_BROWSER_HANDLE;
        m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_INVALID;
    }

    for(i=0;i<NUM_OF_MAX_DIRECTORY_DEPTH+1;i++)
    {
        m_u16CurDirectory[i] = MPLAYER_INVALID_INDEX;
    #if ENABLE_MPLAYER_SORT
        m_u16CurDirectoryPhy[i] = MPLAYER_INVALID_INDEX;
    #endif
#if (HIGH_SPEED_BROWSER)
        m_u16BufDirectory[i] = MPLAYER_INVALID_INDEX;
#endif

    }

    m_u16CurDirectoryDepth = 0;
#if (HIGH_SPEED_BROWSER)
    m_u16BufDirectoryDepth = MPLAYER_INVALID_INDEX;
    m_u16BufReadLongNameIdx = MPLAYER_INVALID_INDEX;
#endif
    m_u16CurFileIdx        = 0;
    m_u16TotalFileNum      = 0;
    m_u16CurPage1stFileIdx = 0;
    m_u16TotalPageNum      = 0;
    m_u16CurPageIdx        = 0;
    m_u16FilesPerPage      = 0;
    m_u8CurDeviceIdx        = 0;
//    memset(m_u16SelectedFileNum, 0, sizeof(U16)*E_MPLAYER_TYPE_NUM);

//    for(i=0;i<NUM_OF_MAX_DIRECTORY_DEPTH;i++)
//    {
//        m_u16CopyDirectory[i] = MPLAYER_INVALID_INDEX;
//    }
//    m_u16CopyFileIdx = MPLAYER_INVALID_INDEX;

//    memset(&m_CopyFileDrive, 0, sizeof(MPlayerDrive));
    memset(m_u16DirectoryNum, 0, sizeof(U16)*NUM_OF_MAX_DIRECTORY_DEPTH);
    //m_eMediaType = E_MPLAYER_TYPE_INVALID;    //do not set media type as invalid here, UI will do somehting
                                                // based on this variable after usb device is removed

    m_ePhotoPreviewState = E_PHOTO_PREVIEW_NONE;
    m_eMusicPreviewState = E_MUSIC_PREVIEW_NONE;
    m_eMoviePreviewState = E_MOVIE_PREVIEW_NONE;
    m_eTextPreviewState  = E_TEXT_PREVIEW_NONE;
#if RANDOM_PLAY
    m_bPlayNext = FALSE;
    m_eRandomMode[E_MPLAYER_FOREGROUND_PLAYER] = E_MPLAYER_RANDOM_NONE;
    m_eRandomMode[E_MPLAYER_BACKGROUND_PLAYER] = E_MPLAYER_RANDOM_NONE;
#endif

    m_eMPlayerStateMachineState = STATE_MPLAYER_INIT;
    m_eRepeatMode[E_MPLAYER_FOREGROUND_PLAYER] = E_MPLAYER_REPEAT_NONE;
    m_eRepeatMode[E_MPLAYER_BACKGROUND_PLAYER] = E_MPLAYER_REPEAT_NONE;
    m_ePlayMode   = E_MPLAYER_PLAY_SELECTED_FROM_CURRENT;
    m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaPlayingStatus = E_MPLAYER_STATE_NONE;
    m_u8DecodedPics = 0;
    m_ePhotoType[0] = m_ePhotoType[1] = E_MPLAYER_SUBTYPE_INVALID;
    m_eZoom = E_MPLAYER_ZOOM_1;
//    m_ePhotoRotate = E_MPLAYER_PHOTO_ROTATE_0;
    m_eMoviePlayMode = E_MPLAYER_MOVIE_NORMAL;
    m_eMusicPlayMode = E_MPLAYER_MUSIC_NORMAL;
    m_eMovieMainExit = EXIT_VDPLAYER_NULL;
    bMusicRecording = FALSE;
    m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_DELETE_PLAY;
    m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_COPY_PLAY;
#if PLAYLIST_BGM
    MApp_MPlayer_BGM_Playlist_DeInit();
#endif
#if ENABLE_COPY_SELECTED_FILES
    MApp_MPlayer_ExitCopyMode();
#endif

    return TRUE;
}

static void _MApp_MPlayer_GetLyric(U16 u16LyricPos, U8 *pu8Dst)
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
        else if(m_bIsUtf8)
        {
            MPLAYER_DBG(printf("utf8 src:%x,%x,%x",pu8Src[u16Src],pu8Src[u16Src+1],pu8Src[u16Src+2]));
            if((pu8Src[u16Src]&0x80) == 0)
            {
                if(pu8Src[u16Src] == '\r' || pu8Src[u16Src] == '\n' || pu8Src[u16Src] == '\0')
                {
                    pu8Dst[u16Dst] = '\0';
                    pu8Dst[u16Dst+1] = '\0';
                    break;
                }
                else
                {
                    u16Data = (U16)pu8Src[u16Src+0];
                    memcpy(&pu8Dst[u16Dst], &u16Data, 2);
                }
                u16Src += 1;
            }
           else if((pu8Src[u16Src]&0xE0) == 0xC0)
           {  //two byte  110x-xxxx 10xx-xxxx
               if((pu8Src[u16Src+1] &0xC0)!=0x80)
               {
                     MPLAYER_DBG(printf("Serious error when convert UTF-8 to unicode, unsync header code at %d\n", (int)u16Src+1));
                     break;
               }
               u16Data =( (((U16)pu8Src[u16Src+0])&0x1F)<<6) | (pu8Src[u16Src+1]&0x3F);
               memcpy(&pu8Dst[u16Dst], &u16Data, 2);
               u16Src += 2;
           }
           else if((pu8Src[u16Src]&0xF0) == 0xE0)
           {  //three byte  1110-xxxx 10xx-xxxx 10xx-xxxx
               if((pu8Src[u16Src+1] &0xC0)!=0x80 || (pu8Src[u16Src+2] &0xC0)!=0x80)
               {
                     MPLAYER_DBG(printf("Serious error when convert UTF-8 to unicode, unsync header code at %d\n", (int)u16Src+1));
                     break;
               }
               u16Data = ((((U16)pu8Src[u16Src+0])&0x0F)<<12) | ((((U16)pu8Src[u16Src+1])&0x3F)<<6) | (pu8Src[u16Src+2]&0x3F) ;
               memcpy(&pu8Dst[u16Dst], &u16Data, 2);
               u16Src += 3;
           }
           else
           {
              MPLAYER_DBG(printf("Serious error when convert UTF-8 to unicode, unsync header code at %d\n", (int)u16Src));
              break;
           }
           MPLAYER_DBG(printf("->unicode:%x\n",u16Data));
           u16Dst+=2;
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

static BOOLEAN _MApp_MPlayer_AddCurFileToPlayingList(void)
{
    U16 u16PLidx;   // Play list index.
    U16 u16Level;   // Directory and file level.
    BOOLEAN bFound=FALSE;
    BOOLEAN bRet = FALSE;
    S16 i;
    MPlayerPlayListInfo *pstPlayListInfo;
    U16 *pu16PlayListNum;
    U32 u32XdataWindowBase;
    MPlayerPlayListInfo tmpMPlayerPlayListInfo;
    MPlayerFileInfo fileInfo;

    memset(&fileInfo,0,sizeof(MPlayerFileInfo));

    if(NUM_OF_MAX_SELECTED_FILE <= m_u16SelectedFileNum[m_eMediaType])
    {
        goto _MApp_MPlayer_AddCurFileToPlayingList_END;
    }

    if(_MApp_MPlayer_GetPlayListAddressByMediaType(m_eMediaType, &u32XdataWindowBase)==FALSE)
    {
        goto _MApp_MPlayer_AddCurFileToPlayingList_END;
    }

    pu16PlayListNum = &m_u16SelectedFileNum[m_eMediaType];
    pstPlayListInfo = (MPlayerPlayListInfo *) (_PA2VA(u32XdataWindowBase));

#if ENABLE_MPLAYER_SORT
    m_u16CurDirectoryPhy[m_u16CurDirectoryDepth] = m_u16CurFileIdx-m_u16DirectoryNum[m_u16CurDirectoryDepth];
#else
    m_u16CurDirectory[m_u16CurDirectoryDepth] = m_u16CurFileIdx-m_u16DirectoryNum[m_u16CurDirectoryDepth];
#endif

    bRet = TRUE;
    // Search to find the entry.
    for(u16PLidx=0; u16PLidx<*pu16PlayListNum; u16PLidx++)
    {
        // Find the 1st entry that match current drive
        if (PLAY_LIST_DRIVE(u16PLidx) < m_u16CurDriveIdx)
        {
            continue;
        }

        // Get the file directory and file level.
        for(u16Level=0;u16Level<NUM_OF_MAX_DIRECTORY_DEPTH+1;u16Level++)
        {
            if(PLAY_LIST_PATH(u16PLidx, u16Level) == MPLAYER_INVALID_INDEX)
            {
                break;
            }
        }
        if(u16Level > (m_u16CurDirectoryDepth+1))
        {
            // Found the entry because the next level if bigger than current.
            bFound = TRUE;
            break;
        }
        else if(u16Level == (m_u16CurDirectoryDepth+1))
        {
            // The directory level is equal to the current.
            // Need to do file search.
            break;
        }
    }
    if(!bFound)
    {
        for(; u16PLidx<*pu16PlayListNum && !bFound; u16PLidx++)
        {
            if (PLAY_LIST_DRIVE(u16PLidx) > m_u16CurDriveIdx)
            {
                bFound = TRUE;
                break;
            }

            for(u16Level = 0; u16Level < NUM_OF_MAX_DIRECTORY_DEPTH+1; u16Level ++)
            {
                if(u16Level < NUM_OF_MAX_DIRECTORY_DEPTH)
                {
                    if((PLAY_LIST_PATH(u16PLidx, u16Level+1) != MPLAYER_INVALID_INDEX) &&
                    #if ENABLE_MPLAYER_SORT
                       (m_u16CurDirectoryPhy[u16Level+1] == MPLAYER_INVALID_INDEX))
                    #else
                       (m_u16CurDirectory[u16Level+1] == MPLAYER_INVALID_INDEX))
                    #endif
                    {
                        u16PLidx--;
                        bFound = TRUE;
                        break;
                    }
                }
            #if ENABLE_MPLAYER_SORT
                if(PLAY_LIST_PATH(u16PLidx, u16Level) > m_u16CurDirectoryPhy[u16Level])
            #else
                if(PLAY_LIST_PATH(u16PLidx, u16Level) > m_u16CurDirectory[u16Level])
            #endif
                {
                    u16PLidx--;
                    bFound = TRUE;
                    break;
                }
            #if ENABLE_MPLAYER_SORT
                else if(PLAY_LIST_PATH(u16PLidx, u16Level) < m_u16CurDirectoryPhy[u16Level])
            #else
                else if(PLAY_LIST_PATH(u16PLidx, u16Level) < m_u16CurDirectory[u16Level])
            #endif
                {
                    break;
                }
            }
        }
    }

    // if any media player is playing, re calculate playing idx
    _MApp_MPlayer_ReCalcMPlayerPlayingIdx(m_eMediaType, TRUE, u16PLidx, u16PLidx);

    // move play list downward if necessary
    for(i=(S16)(*pu16PlayListNum)-1;i>=(S16)u16PLidx;i--)
    {
        memcpy(&tmpMPlayerPlayListInfo, &PLAY_LIST(i), sizeof(MPlayerPlayListInfo));
        memcpy(&PLAY_LIST(i+1), &tmpMPlayerPlayListInfo, sizeof(MPlayerPlayListInfo));
    }

    // add new file to list
    PLAY_LIST_DRIVE(u16PLidx) = m_u16CurDriveIdx;
    for(u16Level=0; u16Level < NUM_OF_MAX_DIRECTORY_DEPTH+1; u16Level++)
    {
    #if ENABLE_MPLAYER_SORT
        PLAY_LIST_PATH(u16PLidx, u16Level) = m_u16CurDirectoryPhy[u16Level];
    #else
        PLAY_LIST_PATH(u16PLidx, u16Level) = m_u16CurDirectory[u16Level];
    #endif
    }

    MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,
                               m_u16CurFileIdx,
                               &fileInfo);

    memcpy(&PLAY_LIST_FILE_ENTRY(u16PLidx), &fileInfo.fileEntry, sizeof(FileEntry));
    memcpy(PLAY_LIST_EXT_NAME(u16PLidx), fileInfo.u8ExtFileName, 3);
    PLAY_LIST_ATTRIBUTE(u16PLidx)=fileInfo.eAttribute; // for decoded fail file
#if ENABLE_SUBTITLE_COPY_AND_DELETE
    if(m_eMediaType == E_MPLAYER_TYPE_MOVIE)
    {
        U8 u8Cnt=0, u8ExtFileNum;
        U32 u32ExtFilesTotalSize = 0;
    #if STORE_SUBTITLE_ENTRY_TO_SUBTITLE_BUFFER
        //Search subtitle file in Subtitle file buffer. PS:Search in USB is slow , and search in Subtitle file buffer is fast.
        u8ExtFileNum = _MApp_MPlayer_ScanExtSubtitleFileNumByMovieFileEntry(&fileInfo.fileEntry, FALSE);
    #else
        //Search subtitle file in USB. PS:Search in USB is slow , and search in Subtitle file buffer is fast.
        u8ExtFileNum = _MApp_MPlayer_ScanExtSubtitleFileNumByMovieFileEntry(&fileInfo.fileEntry, TRUE);
    #endif

    #if ENABLE_EXTERNAL_SUBTITLE_FAST_SWITCHING
        for(; u8Cnt<u8ExtFileNum; u8Cnt++)
        {
            u32ExtFilesTotalSize += m_aExtFileInfoList[u8Cnt].fileEntry.EntryFileLength;
        }
    #else
        if(u8ExtFileNum == 1)
        {
            u32ExtFilesTotalSize = m_ExtFileInfo.fileEntry.EntryFileLength;
        }
    #endif
        MPLAYER_DBG(printf("\033[0;35m_MApp_MPlayer_AddCurFileToPlayingList, u32ExtFilesTotalSize = %ld\033[0m\n", u32ExtFilesTotalSize););
        PLAY_LIST_EXTFILESTOTALSIZE(u16PLidx) = u32ExtFilesTotalSize;
    }
#endif

    (*pu16PlayListNum)++;
    m_bPlaylistChanged = TRUE;

    MPLAYER_DBG(printf("_MApp_MPlayer_AddCurFileToPlayingList, idx=%d, totlistnum=%d\n", u16PLidx, *pu16PlayListNum););

_MApp_MPlayer_AddCurFileToPlayingList_END:
#if 0
    printf("1:Selected File number %d\n", *pu16PlayListNum);
    for(u16PLidx=0;u16PLidx<*pu16PlayListNum;u16PLidx++)
    {
        pstPlayListInfo = (MPlayerPlayListInfo *) (u32XdataWindowBase + (U32)u16PLidx * sizeof(MPlayerPlayListInfo));
        printf("1:Selected File Drive %u (= %c)\n", PLAY_LIST_DRIVE(u16PLidx), (U8)PLAY_LIST_DRIVE(u16PLidx) + 'C');
        printf("1:Selected File Path %d %d %d %d\n",
               PLAY_LIST_PATH(u16PLidx, 0), PLAY_LIST_PATH(u16PLidx, 1),
               PLAY_LIST_PATH(u16PLidx, 2), PLAY_LIST_PATH(u16PLidx, 3));
    }
    printf("\n");
#endif

#if ENABLE_MPLAYER_SORT
    m_u16CurDirectoryPhy[m_u16CurDirectoryDepth] = MPLAYER_INVALID_INDEX;
#else
    m_u16CurDirectory[m_u16CurDirectoryDepth] = MPLAYER_INVALID_INDEX;
#endif

    return bRet;
}

static BOOLEAN _MApp_MPlayer_RemoveFileFromPlayingList(BOOLEAN bDeleteFile)
{
    U16 u16PLidx;   // Play list index.
    U16 u16Level;   // Directory and file level.
    BOOLEAN bMatched=FALSE;
    MPlayerPlayListInfo *pstPlayListInfo;
    U16 *pu16PlayListNum;
    U32 u32XdataWindowBase;
    U16 u16DirDepth;
    MPlayerPlayListInfo tmpMPlayerPlayListInfo;

    if(_MApp_MPlayer_GetPlayListAddressByMediaType(m_eMediaType, &u32XdataWindowBase)==FALSE)
    {
        goto _MApp_MPlayer_RemoveFileFromPlayingList_END;
    }

    pu16PlayListNum = &m_u16SelectedFileNum[m_eMediaType];
    //pstPlayListInfo = (MPlayerPlayListInfo xdata *)msAPI_MIU_GetW1StartAddress();

    pstPlayListInfo = (MPlayerPlayListInfo *) (_PA2VA(u32XdataWindowBase));

#if ENABLE_MPLAYER_SORT
    m_u16CurDirectoryPhy[m_u16CurDirectoryDepth] = m_u16CurFileIdx-m_u16DirectoryNum[m_u16CurDirectoryDepth];
#else
    m_u16CurDirectory[m_u16CurDirectoryDepth] = m_u16CurFileIdx-m_u16DirectoryNum[m_u16CurDirectoryDepth];
#endif

    for(u16PLidx=0;u16PLidx<*pu16PlayListNum;u16PLidx++)
    {
        if (PLAY_LIST_DRIVE(u16PLidx) < m_u16CurDriveIdx)
        {
            continue;
        }

        bMatched = TRUE;
        for(u16Level=0;u16Level<m_u16CurDirectoryDepth+1;u16Level++)
        {
        #if ENABLE_MPLAYER_SORT
            if(PLAY_LIST_PATH(u16PLidx, u16Level) != m_u16CurDirectoryPhy[u16Level])
        #else
            if(PLAY_LIST_PATH(u16PLidx, u16Level) != m_u16CurDirectory[u16Level])
        #endif
            {
                bMatched = FALSE;
            }
        }
        if(bMatched==TRUE)
        {
            // if any media player is playing, re calculate playing idx
            _MApp_MPlayer_ReCalcMPlayerPlayingIdx(m_eMediaType, FALSE, u16PLidx, u16PLidx);

            for(u16Level=u16PLidx;u16Level<*pu16PlayListNum;u16Level++)
            {
                if(bDeleteFile)
                {
                    bMatched = TRUE;

                    for(u16DirDepth=0;u16DirDepth<m_u16CurDirectoryDepth;u16DirDepth++)
                    {
                    #if ENABLE_MPLAYER_SORT
                        if(PLAY_LIST_PATH(u16Level+1, u16DirDepth) != m_u16CurDirectoryPhy[u16DirDepth])
                    #else
                        if(PLAY_LIST_PATH(u16Level+1, u16DirDepth) != m_u16CurDirectory[u16DirDepth])
                    #endif
                        {
                            bMatched = FALSE;
                        }
                    }

                    if(bMatched)
                    {
                        PLAY_LIST_PATH(u16Level+1, m_u16CurDirectoryDepth)--;
                    }
                }

                memcpy(&tmpMPlayerPlayListInfo,
                       &PLAY_LIST(u16Level+1),
                       sizeof(MPlayerPlayListInfo));

//                pstPlayListInfo = (MPlayerPlayListInfo *) ( 0x1000 * ((U16)((u32XdataWindowBase + 0 * sizeof(MPlayerPlayListInfo)) >> 12)));

                memcpy(&PLAY_LIST(u16Level),
                       &tmpMPlayerPlayListInfo,
                       sizeof(MPlayerPlayListInfo));
            }

            pstPlayListInfo = (MPlayerPlayListInfo *) (_PA2VA(u32XdataWindowBase));

            PLAY_LIST_DRIVE(*pu16PlayListNum) = MPLAYER_INVALID_INDEX;
            for(u16DirDepth=0;u16DirDepth<NUM_OF_MAX_DIRECTORY_DEPTH+1;u16DirDepth++)
            {
                PLAY_LIST_PATH(*pu16PlayListNum, u16DirDepth) = MPLAYER_INVALID_INDEX;
            }
            (*pu16PlayListNum)--; // fix playlist abnormal after add&remove
            m_bPlaylistChanged = TRUE;

            MPLAYER_DBG(printf("_MApp_MPlayer_RemoveFileFromPlayingList, idx=%d, totlistnum=%d\n", u16PLidx, *pu16PlayListNum););

            goto _MApp_MPlayer_RemoveFileFromPlayingList_END;
        }
    }

_MApp_MPlayer_RemoveFileFromPlayingList_END:
#if 0
    printf("2:Selected File number %d\n", *pu16PlayListNum);
    for(u16PLidx=0;u16PLidx<*pu16PlayListNum;u16PLidx++)
    {
        pstPlayListInfo = (MPlayerPlayListInfo xdata *) ( u32XdataWindowBase +
                                            (U32)u16PLidx * sizeof(MPlayerPlayListInfo)) ;
        printf("2:Selected File Drive %u (= %c)\n", PLAY_LIST_DRIVE(u16PLidx), (U8)PLAY_LIST_DRIVE(u16PLidx) + 'C');
        printf("2:Selected File Path %d %d %d %d\n",
               PLAY_LIST_PATH(u16PLidx, 0), PLAY_LIST_PATH(u16PLidx, 1),
               PLAY_LIST_PATH(u16PLidx, 2), PLAY_LIST_PATH(u16PLidx, 3));
    }
    printf("\n");
#endif

#if ENABLE_MPLAYER_SORT
    m_u16CurDirectoryPhy[m_u16CurDirectoryDepth] = MPLAYER_INVALID_INDEX;
#else
    m_u16CurDirectory[m_u16CurDirectoryDepth] = MPLAYER_INVALID_INDEX;
#endif

    return bMatched;
}

#if 0
static void _MApp_MPlayer_RemoveAllFilesFromPlayingListAccordingToDriveIdx(U16 u16DriveIdx)
{
    U16 u16PLidxS, u16PLidxE, u16PLcount;   // Play list index.
    U8 u8Idx;
    MPlayerPlayListInfo *pstPlayListInfo;
    U16 *pu16PlayListNum;
    U32 u32XdataWindowBase;
    MPlayerPlayListInfo tmpMPlayerPlayListInfo;
    U16 u16DirDepth;

    for(u8Idx=0;u8Idx<E_MPLAYER_TYPE_NUM;u8Idx++)
    {
        if(FALSE==_MApp_MPlayer_GetPlayListAddressByMediaType((enumMPlayerMediaType)u8Idx, &u32XdataWindowBase))
        {
            continue;
        }

        pu16PlayListNum = &m_u16SelectedFileNum[u8Idx];
        pstPlayListInfo = (MPlayerPlayListInfo xdata *)msAPI_MIU_GetW1StartAddress();

        // if no file selected, do nothing
        if (*pu16PlayListNum == 0)
        {
            goto _MApp_MPlayer_RemoveAllFilesFromPlayingListAccordingToDriveIdx_END;
        }

        // find the 1st file that is in the specific drive
        for(u16PLidxS=0;u16PLidxS<*pu16PlayListNum;u16PLidxS++)
        {
            pstPlayListInfo = (MPlayerPlayListInfo xdata *) (0x1000 *
                    ((U16)((u32XdataWindowBase +
                                                u16PLidxS * sizeof(MPlayerPlayListInfo)) >> 12)));
            if (PLAY_LIST_DRIVE(u16PLidxS) == u16DriveIdx)
            {
                break;
            }
        }

        if (u16PLidxS == *pu16PlayListNum)
        {
            // no file is in the specific drive, do nothing
            goto _MApp_MPlayer_RemoveAllFilesFromPlayingListAccordingToDriveIdx_END;
        }

        // find the 1st file that isn't in the specific drive, starting from u16PLidxS
        for(u16PLidxE=u16PLidxS;u16PLidxE<*pu16PlayListNum;u16PLidxE++)
        {
            pstPlayListInfo = (MPlayerPlayListInfo xdata *) ( 0x1000 *
                        ((U16)((u32XdataWindowBase +
                                                u16PLidxE * sizeof(MPlayerPlayListInfo)) >> 12)));
            if (PLAY_LIST_DRIVE(u16PLidxE) != u16DriveIdx)
            {
                break;
            }
        }

        u16PLcount = u16PLidxE-u16PLidxS;

        // the files between u16PLidxS and u16PLidxE are the target to be removed from play list
        for( ;u16PLidxS<*pu16PlayListNum;u16PLidxS++)
        {
            if (u16PLidxE < *pu16PlayListNum)
            {
                pstPlayListInfo = (MPlayerPlayListInfo xdata *) (0x1000 *
                            ((U16)((u32XdataWindowBase +
                                                    u16PLidxE * sizeof(MPlayerPlayListInfo)) >> 12)));
                memcpy(&tmpMPlayerPlayListInfo,
                       &PLAY_LIST(u16PLidxE),
                       sizeof(MPlayerPlayListInfo));

                pstPlayListInfo = (MPlayerPlayListInfo xdata *) ( 0x1000 *
                            ((U16)((u32XdataWindowBase +
                                                    u16PLidxS * sizeof(MPlayerPlayListInfo)) >> 12)));
                memcpy(&PLAY_LIST(u16PLidxS),
                       &tmpMPlayerPlayListInfo,
                       sizeof(MPlayerPlayListInfo));
                u16PLidxE++;
            }
            else
            {
                pstPlayListInfo = (MPlayerPlayListInfo xdata *) ( 0x1000 *
                        ((U16)((u32XdataWindowBase +
                                                    u16PLidxS * sizeof(MPlayerPlayListInfo)) >> 12)));
                PLAY_LIST_DRIVE(u16PLidxS) = MPLAYER_INVALID_INDEX;
                for(u16DirDepth=0;u16DirDepth<NUM_OF_MAX_DIRECTORY_DEPTH+1;u16DirDepth++)
                {
                    PLAY_LIST_PATH(u16PLidxS, u16DirDepth) = MPLAYER_INVALID_INDEX;
                }
            }
        }

        // re-calculate play list count
        *pu16PlayListNum = *pu16PlayListNum - u16PLcount;

_MApp_MPlayer_RemoveAllFilesFromPlayingListAccordingToDriveIdx_END:
        u8Idx = u8Idx;
#if 0
        printf("4:Media Type %bu, Selected File number %d\n", eMediaType[u8Idx], m_u16SelectedFileNum[eMediaType[u8Idx]]);
        for(u16PLidxS=0;u16PLidxS<m_u16SelectedFileNum[eMediaType[u8Idx]];u16PLidxS++)
        {
            pstPlayListInfo = (MPlayerPlayListInfo xdata *)(0x1000 *
                        ((U16)((u32XdataWindowBase +
                                                u16PLidxS * sizeof(MPlayerPlayListInfo)) >> 12)));
            printf("4:Selected File Drive %u (= %c)\n", PLAY_LIST_DRIVE(u16PLidxS), (U8)PLAY_LIST_DRIVE(u16PLidxS) + 'C');
            printf("4:Selected File Path %d %d %d %d\n",
                   PLAY_LIST_PATH(u16PLidxS, 0), PLAY_LIST_PATH(u16PLidxS, 1),
                   PLAY_LIST_PATH(u16PLidxS, 2), PLAY_LIST_PATH(u16PLidxS, 3));
        }
        printf("\n");
#endif
    }
}
#endif

#if (DISPLAY_LOGO)
#ifdef MSOS_TYPE_LINUX
BOOLEAN _MApp_MPlayer_SaveLogo_To_File(U32 u32SrcAddr, U32 u32DataSize)
{
    extern char LOGO_FILE[];
    FILE *logo_fptr;

    logo_fptr = fopen(LOGO_FILE, "wb");
    if(logo_fptr != NULL)
    {
        fwrite((void *)_PA2VA(u32SrcAddr), 1, u32DataSize, logo_fptr);
        fclose(logo_fptr);
        sync();
        stGenSetting.g_SysSetting.UsrLogo = POWERON_LOGO_USER; //use user logo
        MApp_SaveSysSetting();
        return TRUE;
    }
    return FALSE;
}
#endif
BOOLEAN _MApp_MPlayer_SaveLogo(U32 u32SrcAddr, U32 u32DataSize, U32 u32FlashStartAddr, U32 u32LogoLen)
{
#if (!ENABLE_MPLAYER_CAPTURE_LOGO)
    UNUSED(u32SrcAddr);
    UNUSED(u32DataSize);
    UNUSED(u32FlashStartAddr);
    UNUSED(u32LogoLen);
    //printf("Extra flash isn't available\n");
    return FALSE;
#else
#ifdef MSOS_TYPE_LINUX
    UNUSED(u32FlashStartAddr);
    UNUSED(u32LogoLen);
    return _MApp_MPlayer_SaveLogo_To_File(u32SrcAddr, u32DataSize);
#else
    U8 u8UsrLogoCnt = 0;
    BOOLEAN bRet = FALSE;

    MPLAYER_DBG(printf(" Save Logo Src %lx Dest %lx Size %lx  ", u32SrcAddr, u32FlashStartAddr, u32DataSize));

    if (u32DataSize > u32LogoLen)
    {
        //printf("Saved logo too big\n");
        return FALSE;
    }

    //msAPI_Flash_ChipSelect(E_FLASH_CHIP_SELECT_1);
    //MDrv_SERFLASH_Init();

    u8UsrLogoCnt = stGenSetting.g_SysSetting.u8UsrLogoCnt;
    u8UsrLogoCnt++; // next logo idx
    u8UsrLogoCnt %= USER_LOGO_MAX_NUMBER;

    if (msAPI_Flash_AddressErase(u32FlashStartAddr + u8UsrLogoCnt * u32LogoLen, u32LogoLen, TRUE) == FALSE)
    {
        return FALSE;
    }

#if (WATCH_DOG == ENABLE)
    msAPI_Timer_ResetWDT();
#endif

    if (msAPI_Flash_Write(u32FlashStartAddr + u8UsrLogoCnt * u32LogoLen, u32DataSize, (U8 *)_PA2VA(u32SrcAddr)) == TRUE)
    {
        stGenSetting.g_SysSetting.UsrLogo = POWERON_LOGO_USER; //use user logo
        stGenSetting.g_SysSetting.u8UsrLogoCnt = u8UsrLogoCnt;
        // TBD: if user want the previous logo still be the bootup logo, move following statement
        stGenSetting.g_SysSetting.u8UsrLogoIdx = u8UsrLogoCnt;

        MApp_SaveSysSetting();
        bRet = TRUE;
    }

    //msAPI_Flash_ChipSelect(E_FLASH_CHIP_SELECT_0);
   // MDrv_SERFLASH_Init();

    return bRet;
#endif
#endif
}
#endif  // #if (DISPLAY_LOGO)

#if 0 //(ENABLE_MPLAYER_VIDEO_CAPTURE) //Old video capture flow. It can be removed
//******************************************************************************
/// Capture the current image and save it as a JPEG file.
/// @param  pFileName \b IN Specify the file name.
/// @param  u8pTmpBuffAddr \b IN Specify the tmp buffer addr.
/// @param  u8pTmpBuffAddr \b IN Specify the tmp buffer size.
/// @return enumMPlayerRet
//******************************************************************************
BOOLEAN _MApp_MPlayer_CaptureImage2JPGFile(U8 *pFileName, U32 u32TmpBuffAddr, U32 u32TmpBuffSize)
{
    U8 gopBank;
//    U8 u8GWinId;
    U8 u8HandleNo;
    U16 u16OutputWidth, u16OutputHeight, u16OutputX, u16OutputY;
    U32 u32BufferAddr1, u32BufferAddr2, u32Size, u32BufferSize1;
    GOP_DwinProperty dwinProperty;
    GEBitBltInfo stBitbltInfo;
    GEPitBaseInfo stPitBaseInfo;
    U32 u32PoolMemAddr, u32OutputBufferAddr;
    U32 u32PoolMemSize, u32OutputBufferSize;

    XC_ApiStatus stXC_WinTime_Info;

    if(MApi_XC_GetStatus(&stXC_WinTime_Info, MAIN_WINDOW) == FALSE)
    {
        //printf("MApi_XC_GetStatus failed because of InitData wrong, please update header file and compile again\n");
    }

    //pFileName = pFileName;
#if 0//(VIDEO_CAPTURE_USE_GE_BUFFER)
    for (u8GWinId = 0; u8GWinId < MApi_GOP_GWIN_GetMAXWinID(); u8GWinId++)
    {
        if (MApi_GOP_GWIN_IsGWINEnabled(u8GWinId))
        {
            return FALSE;
        }
    }
#endif
    u32Size = (U32)(g_IPanel.Width()) * g_IPanel.Height();
    if (u32TmpBuffSize < u32Size)
    {
        return FALSE;
    }

    u16OutputX = stXC_WinTime_Info.stDispWin.x;
    u16OutputY = stXC_WinTime_Info.stDispWin.y;
    u16OutputWidth = stXC_WinTime_Info.stDispWin.width & 0xFFF0;   // Need 16 pixel alignment for JPEG encoder.
    u16OutputHeight = stXC_WinTime_Info.stDispWin.height;
    if(u16OutputHeight > g_IPanel.Height())
    {
        u16OutputHeight = g_IPanel.Height();
    }

#if ENABLE_MPLAYER_PHOTO
    if (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaType == E_MPLAYER_TYPE_PHOTO)
    {
#if defined(PHOTO_SLIDE_SHOW_EFFECT) && (PHOTO_SLIDE_SHOW_EFFECT == 1)
        MApp_Photo_GetImageCoordinatesOnScreen(&u16OutputX, &u16OutputY, &u16OutputWidth, &u16OutputHeight);

        if(u16OutputWidth > g_IPanel.Width())
        {
            u16OutputWidth = g_IPanel.Width();
        }
        u16OutputWidth &= 0xfffc;
#endif // #if defined(PHOTO_SLIDE_SHOW_EFFECT) && (PHOTO_SLIDE_SHOW_EFFECT == 1)
    }
#endif  // #if ENABLE_MPLAYER_PHOTO

    MPLAYER_DBG(printf("display, x: %u, y: %u, w: %u, h: %u\n",
            u16OutputX,
            u16OutputY,
            u16OutputWidth,
            u16OutputHeight));

    u32BufferAddr1 = u32TmpBuffAddr;
    u32BufferAddr2 = ((CAPTURE_VIDEO_BUFFER_MEMORY_TYPE & MIU1) ? (CAPTURE_VIDEO_BUFFER_ADR | MIU_INTERVAL) : (CAPTURE_VIDEO_BUFFER_ADR));

    u32BufferSize1 = u32TmpBuffSize;

#if ENABLE_MPLAYER_PHOTO
    if (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaType == E_MPLAYER_TYPE_PHOTO)
    {
        u32BufferAddr2 = ((SUBTITLE_MEMORY_TYPE & MIU1) ? (SUBTITLE_ADR | MIU_INTERVAL) : (SUBTITLE_ADR));
    }
#endif //#if ENABLE_MPLAYER_PHOTO

    // Use DWIN to capture Image ------------------------------------------
    MPLAYER_DBG(printf("JPEG Encode: use DWIN to capture Image\n"));

    gopBank = MApi_GOP_GWIN_GetCurrentGOP();
    MApi_GOP_GWIN_SwitchGOP(E_GOP_CAP);

    // set GOPD clock
    MApi_GOP_SetClkForCapture();

    MApi_GOP_DWIN_Init();

    MApi_GOP_DWIN_SelectSourceScanType(DWIN_SCAN_MODE_PROGRESSIVE);
    MApi_GOP_DWIN_SetDataFmt(DWIN_DATA_FMT_UV8Y8);
    dwinProperty.u16x = u16OutputX;
    dwinProperty.u16y = u16OutputY;
    dwinProperty.u16h = u16OutputHeight - 1;
    dwinProperty.u32fbaddr0 = u32BufferAddr1;
    dwinProperty.u32fbaddr1 = u32BufferAddr1 + u32BufferSize1;
    dwinProperty.u16w = (u16OutputWidth & 0xffff);
    dwinProperty.u16fbw = u16OutputWidth & 0xffff;

    // enable DWIN progressive INT
    MApi_GOP_DWIN_SetWinProperty(&dwinProperty);
    MApi_GOP_DWIN_SetAlphaValue(0x0f); // set to solid
    msAPI_Timer_Delayms(10);
    MApi_GOP_DWIN_CaptureOneFrame2();
    msAPI_Timer_Delayms(10);

    MApi_GOP_GWIN_SwitchGOP(gopBank);

// re-use u16OutputX/u16OutputY because they are no longer needed
#define u16CaptureWidth u16OutputX
#define u16CaptureHeight u16OutputY

    u16CaptureWidth = VIDEO_CAPTURE_WIDTH;
    u16CaptureHeight = VIDEO_CAPTURE_HEIGHT;

#if ENABLE_MPLAYER_PHOTO
    u16CaptureWidth &= 0xfff0; // JPEG encoder requires 16-pixel alignment of width
    u16CaptureHeight &= 0xfff8; // JPEG encoder requires 8-pixel alignment of height

    // keep the aspect ratio for photo
    if (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaType == E_MPLAYER_TYPE_PHOTO)
    {
        if((((U32)u16CaptureWidth * 128) / (U32)u16CaptureHeight) >
                (((U32)u16OutputWidth * 128) / (U32)u16OutputHeight))
        {
            // Height major
            u16CaptureWidth = (U16)(((U32)u16CaptureHeight * 128 / (U32)u16OutputHeight) *
                                  (U32)u16OutputWidth / 128) & 0xFFF0;
        }
        else
        {
            // Width major
            u16CaptureHeight = (U16)(((U32)u16CaptureWidth * 128 / (U32)u16OutputWidth) *
                                  (U32)u16OutputHeight / 128) & 0xFFF8;
        }
    }
#endif  // #if ENABLE_MPLAYER_PHOTO

    MPLAYER_DBG(printf("output: %ux%u, %ux%u\n",
            u16CaptureWidth,
            u16CaptureHeight,
            (U16)VIDEO_CAPTURE_WIDTH,
            (U16)VIDEO_CAPTURE_HEIGHT));

    // Zoom source to be 1024x768.
    stPitBaseInfo.sb_pit = u16OutputWidth * 2;      // 2 bytes per pixel, the pitch is referring to original image
    stPitBaseInfo.sb_base = u32BufferAddr1;         // the address is referring to original image
    stPitBaseInfo.db_pit = u16CaptureWidth * 2; // YUV422
    stPitBaseInfo.db_base = u32BufferAddr2;

    stBitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
    stBitbltInfo.BmpFlag        = GFXDRAW_FLAG_DEFAULT;
    stBitbltInfo.dst_fm         = GFX_FMT_YUV422;
    stBitbltInfo.src_fm         = GFX_FMT_YUV422;
//    To get rid of the green line at the edge, use follow statements
//    stBitbltInfo.src_width      = u16OutputWidth - 1;
//    stBitbltInfo.src_height     = u16OutputHeight - 1;
//    stBitbltInfo.BitbltCoordinate.v2_x = 1;
    stBitbltInfo.src_width      = u16OutputWidth;
    stBitbltInfo.src_height     = u16OutputHeight;
    stBitbltInfo.BitbltCoordinate.v2_x = 0;
    stBitbltInfo.BitbltCoordinate.v2_y = 0;
    stBitbltInfo.BitbltCoordinate.direction = 0; // TODO: what's this?
    stBitbltInfo.BitbltCoordinate.v0_x = 0;
    stBitbltInfo.BitbltCoordinate.v0_y = 0;

    stBitbltInfo.BitbltCoordinate.width = u16CaptureWidth;
    stBitbltInfo.BitbltCoordinate.height = u16CaptureHeight;

    msAPI_OSD_SetClipWindow(0, 0, u16CaptureWidth, u16CaptureHeight);

    MApi_GFX_SetNearestMode(FALSE);
    MApi_GFX_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YUYV,  GFX_YUV_YUYV);
    MApi_GFX_SetPatchMode(TRUE);

    // output image to destination buffer
    msAPI_GE_BitBlt(&stBitbltInfo, &stPitBaseInfo);
    // after BitBlt, flush cmd
    MApi_GFX_FlushQueue();

    MApi_GFX_SetPatchMode(FALSE);

    msAPI_OSD_SetClipWindow(0, 0, g_IPanel.Width(), g_IPanel.Height());

    // Compress image to JPEG ------------------------------------------
    u32OutputBufferAddr = u32BufferAddr1;
    u32OutputBufferSize = 0x100000;  // 1M
    u32PoolMemAddr = u32OutputBufferAddr + u32OutputBufferSize;
    u32PoolMemSize = 0x80000;  // 512K

    MApp_Photo_MemCfg(
            u32BufferAddr2, (U32)u16CaptureWidth * u16CaptureHeight * 2,
            u32OutputBufferAddr, u32OutputBufferSize,
            u32PoolMemAddr, u32PoolMemSize);

    u32Size = 0;
    if (MApp_Photo_EncodeMemory_Init(u16CaptureWidth, u16CaptureHeight, NULL))
    {
        EN_RET enPhotoRet;

        while ((enPhotoRet = MApp_Photo_Main()) == EXIT_PHOTO_DECODING)
            ;

        if ((enPhotoRet == EXIT_PHOTO_DECODE_DONE) && (MApp_Photo_GetErrCode() == E_PHOTO_ERR_NONE))
        {
        u32Size = MApp_Photo_GetInfo(E_PHOTO_INFO_SIZE);
    }
    }

    MApp_Photo_Stop();

#undef u16CaptureWidth
#undef u16CaptureHeight

    // Save to file ------------------------------------------
    MPLAYER_DBG(printf("JPEG Encode: Save to file \"%s\", total %u bytes\n", pFileName, u32Size));
    ASCIItoUnicode2((S8 *)pFileName, strlen((char*)pFileName));
    if ((m_u8TotalDriveNum == 0)
            || ((u8HandleNo = MApp_FileBrowser_OpenNewFileForWrite((U16 *)(void *)pFileName,UnicodeLen((S8*)pFileName))) == INVALID_FILE_HANDLE))
    {
        return FALSE;
    }

    msAPI_FCtrl_FileWrite(u8HandleNo, u32BufferAddr1, u32Size);
    msAPI_FCtrl_FileClose(u8HandleNo);
    MPLAYER_DBG(printf("JPEG encode done\n"));

    return TRUE;
}

//******************************************************************************
/// Capture the current video and save it as a JPEG file.
/// @param  pFileName \b IN Specify the file name.
/// @param  u8pTmpBuffAddr \b IN Specify the tmp buffer addr.
/// @param  u8pTmpBuffAddr \b IN Specify the tmp buffer size.
/// @return enumMPlayerRet
//******************************************************************************
BOOLEAN _MApp_MPlayer_CaptureVideo2JPGFile(U8 *pFileName, U32 u32TmpBuffAddr, U32 u32TmpBuffSize)
{
    U8 gopBank;
//    U8 u8GWinId;
    U8 u8HandleNo;
    U16 u16OutputWidth, u16OutputHeight, u16OutputX, u16OutputY;
    U32 u32BufferAddr1, u32BufferAddr2, u32Size, u32BufferSize1;
    GOP_DwinProperty dwinProperty;
    GEBitBltInfo stBitbltInfo;
    GEPitBaseInfo stPitBaseInfo;
    U32 u32PoolMemAddr, u32OutputBufferAddr;
    U32 u32PoolMemSize, u32OutputBufferSize;

    U16 u16CaptureWidth, u16CaptureHeight;

    XC_ApiStatus stXC_WinTime_Info;

    if(MApi_XC_GetStatus(&stXC_WinTime_Info, MAIN_WINDOW) == FALSE)
    {
        //printf("MApi_XC_GetStatus failed because of InitData wrong, please update header file and compile again\n");
    }

    MPLAYER_DBG(printf("\n  capture video DWIN addr=%x ,  size=%x", u32TmpBuffAddr, u32TmpBuffSize ));
    MApi_GFX_ClearFrameBuffer(u32TmpBuffAddr, u32TmpBuffSize, 0x0); // fill frame buffer with 0, black
    // after clear frame buffer, flush cmd
    MApi_GFX_FlushQueue();

    u32Size = (U32)(g_IPanel.Width()) * g_IPanel.Height();
    if (u32TmpBuffSize < u32Size)
    {
        return FALSE;
    }

    u16OutputX = stXC_WinTime_Info.stDispWin.x;
    u16OutputY = stXC_WinTime_Info.stDispWin.y;
    u16OutputWidth = stXC_WinTime_Info.stDispWin.width & 0xFFF0;   // Need 16 pixel alignment for JPEG encoder.
    u16OutputHeight = stXC_WinTime_Info.stDispWin.height;
    if(u16OutputHeight > g_IPanel.Height())
    {
        u16OutputHeight = g_IPanel.Height();
    }

    MPLAYER_DBG(printf("display, x: %u, y: %u, w: %u, h: %u\n",
            u16OutputX,
            u16OutputY,
            u16OutputWidth,
            u16OutputHeight));

    u16OutputHeight=u16OutputHeight/2;

    u32BufferAddr1 = u32TmpBuffAddr;
    u32BufferAddr2 = ((CAPTURE_VIDEO_BUFFER_MEMORY_TYPE & MIU1) ? (CAPTURE_VIDEO_BUFFER_ADR | MIU_INTERVAL) : (CAPTURE_VIDEO_BUFFER_ADR));

    u32BufferSize1 = u32TmpBuffSize;

    // Use DWIN to capture Image ------------------------------------------
    MPLAYER_DBG(printf("use DWIN to capture video\n"));

#if 1
    MApi_GOP_DWIN_EnableR2YCSC(ENABLE);
#endif

    // ------------------
    // top helf image
    // ------------------

    MApi_GOP_DWIN_Init();
    gopBank = MApi_GOP_GWIN_GetCurrentGOP();
    MApi_GOP_GWIN_SwitchGOP(E_GOP_CAP);

    //RIU[0x1012F2] &= (~0x10); //temp setting, remove later.

    // set GOPD clock
    MApi_GOP_SetClkForCapture();
    MApi_GOP_DWIN_SelectSourceScanType(DWIN_SCAN_MODE_PROGRESSIVE);
    MApi_GOP_DWIN_SetDataFmt(DWIN_DATA_FMT_UV8Y8);
    MApi_GOP_DWIN_SetSourceSel(DWIN_SRC_OP);
    dwinProperty.u16x = 0;//u16OutputX;
    dwinProperty.u16y = 0;//u16OutputY;
    dwinProperty.u16h = u16OutputHeight; //- 1;
    dwinProperty.u32fbaddr0 = u32BufferAddr1;
    dwinProperty.u32fbaddr1 = u32BufferAddr1 + u32BufferSize1;
    dwinProperty.u16w = (u16OutputWidth & 0xffff);
    dwinProperty.u16fbw = u16OutputWidth & 0xffff;

    MPLAYER_DBG(printf("\n video DWIN x=%d , y=%d , w=%d , h=%d   ",dwinProperty.u16x, dwinProperty.u16y, dwinProperty.u16w , dwinProperty.u16h) );
    MPLAYER_DBG(printf("\n video DWIN addr low=%d, addr high=%d ",dwinProperty.u32fbaddr0 ,dwinProperty.u32fbaddr1 ));

    // enable DWIN progressive INT
    MApi_GOP_DWIN_SetWinProperty(&dwinProperty);
    MApi_GOP_DWIN_SetAlphaValue(0x0f); // set to solid
    msAPI_Timer_Delayms(10);
    MApi_GOP_DWIN_CaptureOneFrame();
    msAPI_Timer_Delayms(50);
    MApi_GOP_DWIN_Enable(FALSE);
    MApi_GOP_GWIN_SwitchGOP(gopBank);

    u16CaptureWidth = VIDEO_CAPTURE_WIDTH;
    u16CaptureHeight = VIDEO_CAPTURE_HEIGHT;

    u16CaptureWidth &= 0xfff0; // JPEG encoder requires 16-pixel alignment of width
    u16CaptureHeight &= 0xfff8; // JPEG encoder requires 8-pixel alignment of height

    MPLAYER_DBG(printf("output: %ux%u, %ux%u\n",
            u16CaptureWidth,
            u16CaptureHeight,
            (U16)VIDEO_CAPTURE_WIDTH,
            (U16)VIDEO_CAPTURE_HEIGHT));

    // Zoom source to be 1024x768.
    stPitBaseInfo.sb_pit = u16OutputWidth * 2;      // 2 bytes per pixel, the pitch is referring to original image
    stPitBaseInfo.sb_base = u32BufferAddr1;         // the address is referring to original image
    stPitBaseInfo.db_pit = u16CaptureWidth * 2; // YUV422
    stPitBaseInfo.db_base = u32BufferAddr2;

    MPLAYER_DBG(printf("\n bitblt addr=%x ", u32BufferAddr2));

    stBitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
    stBitbltInfo.BmpFlag        = GFXDRAW_FLAG_DEFAULT;
    stBitbltInfo.dst_fm         = GFX_FMT_YUV422;
    stBitbltInfo.src_fm         = GFX_FMT_YUV422;
    stBitbltInfo.src_width      = u16OutputWidth;
    stBitbltInfo.src_height     = u16OutputHeight;
    stBitbltInfo.BitbltCoordinate.v2_x = 0;
    stBitbltInfo.BitbltCoordinate.v2_y = 0;
    stBitbltInfo.BitbltCoordinate.direction = 0; // TODO: what's this?
    stBitbltInfo.BitbltCoordinate.v0_x = 0;
    stBitbltInfo.BitbltCoordinate.v0_y = 0;

    stBitbltInfo.BitbltCoordinate.width = u16CaptureWidth;
    stBitbltInfo.BitbltCoordinate.height = u16CaptureHeight/2;

    MPLAYER_DBG(printf("\n bitblt src w=%d, h=%d ", stBitbltInfo.src_width ,stBitbltInfo.src_height ) );
    MPLAYER_DBG(printf("\n bitblt dst w=%d, h=%d ", stBitbltInfo.BitbltCoordinate.width,stBitbltInfo.BitbltCoordinate.height ));

    msAPI_OSD_SetClipWindow(0, 0, u16CaptureWidth, u16CaptureHeight);

    MApi_GFX_SetNearestMode(FALSE);
    MApi_GFX_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_255, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YVYU,  GFX_YUV_YUYV);
    MApi_GFX_SetPatchMode(TRUE);

    // output image to destination buffer
    msAPI_GE_BitBlt(&stBitbltInfo, &stPitBaseInfo);
    // after BitBlt, flush cmd
    MApi_GFX_FlushQueue();

    MApi_GFX_SetPatchMode(FALSE);

    msAPI_OSD_SetClipWindow(0, 0, g_IPanel.Width(), g_IPanel.Height());

    // ------------------
    // top helf image
    // ------------------
    // ------------------
    // bottom helf image
    // ------------------
    // Use DWIN to capture Image ------------------------------------------
    MPLAYER_DBG(printf("use DWIN to capture video\n"));

    gopBank = MApi_GOP_GWIN_GetCurrentGOP();
    MApi_GOP_GWIN_SwitchGOP(E_GOP_CAP);
    MApi_GOP_DWIN_Init();
    //RIU[0x1012F2] &= (~0x10); //temp setting, remove later.
    // set GOPD clock
    MApi_GOP_SetClkForCapture();
    MApi_GOP_DWIN_SetSourceSel(DWIN_SRC_OP);
    MApi_GOP_DWIN_SelectSourceScanType(DWIN_SCAN_MODE_PROGRESSIVE);
    MApi_GOP_DWIN_SetDataFmt(DWIN_DATA_FMT_UV8Y8);
    dwinProperty.u16x = 0; //u16OutputX;
    dwinProperty.u16y = u16OutputHeight; //u16OutputY;
    dwinProperty.u16h = u16OutputHeight;//-4;
    dwinProperty.u32fbaddr0 = u32BufferAddr1;
    dwinProperty.u32fbaddr1 = u32BufferAddr1 + u32BufferSize1;
    dwinProperty.u16w = (u16OutputWidth & 0xffff);
    dwinProperty.u16fbw = u16OutputWidth & 0xffff;
    MPLAYER_DBG(printf("\n video DWIN x=%d , y=%d , w=%d , h=%d   ",dwinProperty.u16x, dwinProperty.u16y, dwinProperty.u16w , dwinProperty.u16h ));
    MPLAYER_DBG(printf("\n video DWIN addr low=%d, addr high=%d ",dwinProperty.u32fbaddr0 ,dwinProperty.u32fbaddr1) );

    // enable DWIN progressive INT
    MApi_GOP_DWIN_SetWinProperty(&dwinProperty);
    MApi_GOP_DWIN_SetAlphaValue(0x0f); // set to solid
    msAPI_Timer_Delayms(10);
    MApi_GOP_DWIN_CaptureOneFrame();
    msAPI_Timer_Delayms(50);
    MApi_GOP_DWIN_Enable(FALSE);
    MApi_GOP_GWIN_SwitchGOP(gopBank);

    // Zoom source to be 1024x768.
    stPitBaseInfo.sb_pit = u16OutputWidth * 2;      // 2 bytes per pixel, the pitch is referring to original image
    stPitBaseInfo.sb_base = u32BufferAddr1;         // the address is referring to original image
    stPitBaseInfo.db_pit = u16CaptureWidth * 2; // YUV422
    stPitBaseInfo.db_base = u32BufferAddr2;

    stBitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
    stBitbltInfo.BmpFlag        = GFXDRAW_FLAG_DEFAULT;
    stBitbltInfo.dst_fm         = GFX_FMT_YUV422;
    stBitbltInfo.src_fm         = GFX_FMT_YUV422;
    stBitbltInfo.src_width      = u16OutputWidth;
    stBitbltInfo.src_height     = u16OutputHeight;//-4;
    stBitbltInfo.BitbltCoordinate.v2_x = 0;
    stBitbltInfo.BitbltCoordinate.v2_y = 0;
    stBitbltInfo.BitbltCoordinate.direction = 0; // TODO: what's this?
    stBitbltInfo.BitbltCoordinate.v0_x = 0;
    stBitbltInfo.BitbltCoordinate.v0_y = u16CaptureHeight/2;
    stBitbltInfo.BitbltCoordinate.width = u16CaptureWidth;
    stBitbltInfo.BitbltCoordinate.height = u16CaptureHeight/2;

    MPLAYER_DBG(printf("\n bitblt src w=%d, h=%d ", stBitbltInfo.src_width ,stBitbltInfo.src_height ) );
    MPLAYER_DBG(printf("\n bitblt dst w=%d, h=%d ", stBitbltInfo.BitbltCoordinate.width,stBitbltInfo.BitbltCoordinate.height ));

    msAPI_OSD_SetClipWindow(0, 0, u16CaptureWidth, u16CaptureHeight);

    MApi_GFX_SetNearestMode(FALSE);
    MApi_GFX_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_255, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YVYU,  GFX_YUV_YUYV);
    MApi_GFX_SetPatchMode(TRUE);

    // output image to destination buffer
    msAPI_GE_BitBlt(&stBitbltInfo, &stPitBaseInfo);
    // after BitBlt, flush cmd
    MApi_GFX_FlushQueue();

    MApi_GFX_SetPatchMode(FALSE);

    msAPI_OSD_SetClipWindow(0, 0, g_IPanel.Width(), g_IPanel.Height());

    // ------------------
    // bottom helf image
    // ------------------


    // Compress image to JPEG ------------------------------------------
    //MApp_VDPlayer_UartSwitch(E_UART_SWITCH_TO_COPROCESSOR);
    u32OutputBufferAddr = u32BufferAddr1;
    u32OutputBufferSize = 0x100000;  // 1M
    u32PoolMemAddr = u32OutputBufferAddr + u32OutputBufferSize;
    u32PoolMemSize = 0x80000;  // 512K

    MApp_Photo_MemCfg(
            u32BufferAddr2, (U32)u16CaptureWidth * u16CaptureHeight * 2,
            u32OutputBufferAddr, u32OutputBufferSize,
            u32PoolMemAddr, u32PoolMemSize);

    u32Size = 0;
    if (MApp_Photo_EncodeMemory_Init(u16CaptureWidth, u16CaptureHeight, NULL))
    {
        EN_RET enPhotoRet;

        while ((enPhotoRet = MApp_Photo_Main()) == EXIT_PHOTO_DECODING);

        if ((enPhotoRet == EXIT_PHOTO_DECODE_DONE) && (MApp_Photo_GetErrCode() == E_PHOTO_ERR_NONE))
        {
            u32Size = MApp_Photo_GetInfo(E_PHOTO_INFO_SIZE);
        }
    }

    MApp_Photo_Stop();

#if 1
    MApi_GOP_DWIN_EnableR2YCSC(DISABLE);
#endif
    // Save to file ------------------------------------------
    MPLAYER_DBG(printf("JPEG Encode: Save to file \"%s\", total %u bytes\n", pFileName, u32Size));

#if ((OBA2 == 1) && (ENABLE_BABAO_PLAYER == ENABLE))
    if (msAPI_NPlayer_IsPlaying(E_MPLAYER_MEDIA_MOVIE))
    {
        FILE *fp;
        char *pBuffer = (char*)_PA2VA(u32BufferAddr1);
        fp = fopen((char*)pFileName, "w+");
        if(fp == NULL)
        {
            //printf("open JPG file for write fail\n");
            return FALSE;
        }

        fwrite(pBuffer, u32Size, 1, fp);
        fflush(fp);
        fclose(fp);
    }
    else
#endif
    {
        ASCIItoUnicode2((S8 *)pFileName, strlen((char*)pFileName));
        if ((m_u8TotalDriveNum == 0)
                || ((u8HandleNo = MApp_FileBrowser_OpenNewFileForWrite((U16 *)(void *)pFileName,UnicodeLen((S8*)pFileName))) == INVALID_FILE_HANDLE))
        {
            //printf("\n open file for write fail  [m_u8TotalDriveNum=%d]", m_u8TotalDriveNum);
            return FALSE;
        }

        msAPI_FCtrl_FileWrite(u8HandleNo, u32BufferAddr1, u32Size);
        msAPI_FCtrl_FileClose(u8HandleNo);
    }
#if OBA2
    sync();
#endif
    MPLAYER_DBG(printf("JPEG encode done\n"));

    return TRUE;
}
#endif  // #if (ENABLE_MPLAYER_VIDEO_CAPTURE)

//******************************************************************************
/// Initialize and start co-processor for media player
/// @return enumMPlayerRet
//******************************************************************************
void _MApp_Mplayer_InitializeCoProcessor(void)
{
#if 0 //def AEON_VDPLAYER
    if (gCurrentBinID != BIN_ID_CODE_VDPLAYER)
    {
        MPLAYER_DBG(printf("install mplayer code\n"));
        msAPI_BEON_Init(BIN_ID_CODE_VDPLAYER,((BEON_MEM_MEMORY_TYPE & MIU1) ? (BEON_MEM_ADR | MIU_INTERVAL) : ( BEON_MEM_ADR)),BEON_MEM_LEN);
    }
#endif

}

extern void msAPI_MpegSP_SpuQueue_Reset(void);
#if (ENABLE_SUBTITLE_SUBIDX)
static BOOLEAN _MApp_MPlayer_SetMpegSubtitle(void)
{
#if(ENABLE_SMALL_BUF_SUBTITLE)
    msAPI_MpegSP_SpuQueue_Reset();
#else
    U32 u32CurTime, u32TmpIdx;

    //msAPI_MpegSP_Reset_SpuQueue();
    msAPI_MpegSP_SpuQueue_Reset();

    u32CurTime = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CUR_TIME);

    //Get new tag time: movie current time == subtitle tag time + user time shift
    u32CurTime = ((S32)u32CurTime - m_s32SubtitleTimeShift)>0 ? ((S32)u32CurTime - m_s32SubtitleTimeShift):0;

    u32TmpIdx = MApp_MPlayer_SearchSubtitleTag(u32CurTime);

    if( u32TmpIdx != 0xFFFF)
    {
        m_u16ExternalSubtitleIdx = u32TmpIdx;
    }
    else
    {
        //curTime less than all subtitle start time.
        m_u16ExternalSubtitleIdx = 0;
    }
#endif//(ENABLE_SMALL_BUF_SUBTITLE)
    return TRUE;
}
#endif //#if (ENABLE_SUBTITLE_SUBIDX)

//*****************************************************************************
//              Functions
//*****************************************************************************
//=============================================================================/
//============================ Command Interface ==============================
//=============================================================================/

//******************************************************************************
/// It will initialize the state machine of media player and all status, variables to the default.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_InitializeKernel(void)
{
    U16 i;
    enumMPlayerIdx eMPlayerIdx;

#if ENABLE_HK_MM
    if(MApp_VDPlayer_MediaCodec_Initialize() != TRUE)
    {
        MPLAYER_ERROR("!!!!!! %s --> MApp_VDPlayer_MediaCodec_Initialize FALSE \n",__FUNCTION__);
        return E_MPLAYER_RET_FAIL;
    }
#endif

    MPLAYER_DBG(printf("MPlayerFileInfo size=%d(%d), max file per dir=%d\n", (U16)sizeof(MPlayerFileInfo), MPlayerFileInfo_SIZE, NUM_OF_MAX_FILES_PER_DIRECTORY));
    MPLAYER_DBG(printf("MPlayerPlayListInfo size=%d, max file in list=%d, max dir depth=%d\n", (U16)sizeof(MPlayerPlayListInfo), NUM_OF_MAX_SELECTED_FILE, NUM_OF_MAX_DIRECTORY_DEPTH));

    //Check if "MPlayerFileInfo size error!!"
    STATIC_ASSERT((4096 % sizeof(MPlayerFileInfo))!= 0);

    #if ENABLE_MPLAYER_PHOTO
    //Check if "MPlayerPlayList size  < photo play list size"
    STATIC_ASSERT(((U32)NUM_OF_MAX_SELECTED_FILE * sizeof(MPlayerPlayListInfo)) > MPLAYER_PHOTO_PLAYLIST_LEN);
    #endif // #if ENABLE_MPLAYER_PHOTO

    #if ENABLE_MPLAYER_MUSIC
    //Check if "MPlayerPlayList size  < music play list size"
    STATIC_ASSERT(((U32)NUM_OF_MAX_SELECTED_FILE * sizeof(MPlayerPlayListInfo)) > MPLAYER_MUSIC_PLAYLIST_LEN);
    #endif // #if ENABLE_MPLAYER_MUSIC

    #if ENABLE_MPLAYER_MOVIE
    //Check if "MPlayerPlayList size  < movie play list size"
    STATIC_ASSERT(((U32)NUM_OF_MAX_SELECTED_FILE * sizeof(MPlayerPlayListInfo)) > MPLAYER_MOVIE_PLAYLIST_LEN);
    #endif // #if ENABLE_MPLAYER_MOVIE

    #if ENABLE_MPLAYER_TEXT
    //Check if "MPlayerPlayList size  < text play list size"
    STATIC_ASSERT(((U32)NUM_OF_MAX_SELECTED_FILE * sizeof(MPlayerPlayListInfo)) > MPLAYER_TEXT_PLAYLIST_LEN);
    #endif // #if ENABLE_MPLAYER_TEXT

#if (HIGH_SPEED_BROWSER)
    //Check if "MPLAYER_FILE_BUFFER_ADRx2 is too small!"
    STATIC_ASSERT((2L*(U32)NUM_OF_MAX_FILES_PER_DIRECTORY*sizeof(MPlayerFileInfo)) >
       MPLAYER_FILE_BUFFER_LEN);
#else
    //Check if "MPLAYER_FILE_BUFFER_ADR is too small!"
    STATIC_ASSERT(((U32)NUM_OF_MAX_FILES_PER_DIRECTORY*sizeof(MPlayerFileInfo)) >
       MPLAYER_FILE_BUFFER_LEN);
#endif

#if DIRECTORY_BGM//ENABLE_BGM
    //Check if "MPLAYER_MUSIC_FILE_BUFFER_LEN is too small!"
    STATIC_ASSERT(((U32)NUM_OF_MAX_FILES_PER_DIRECTORY*sizeof(MPlayerFileInfo)) >
       MPLAYER_MUSIC_FILE_BUFFER_LEN);
#endif // #if ENABLE_BGM

#if ENABLE_SUBTITLE_DMP
#if ENABLE_INTERNAL_SUBTITLE
    if(VDPLAYER_SUBTITLE_BITSTREAM_BUFF_LEN==0)
    {
        MPLAYER_ERROR("Enable Internal Subtitle but VDPLAYER_SUBTITLE_BITSTREAM_BUFF_LEN is 0!\n");
        //while(1);
    }
#endif //ENABLE_INTERNAL_SUBTITLE
#endif //ENABLE_SUBTITLE_DMP

    m_eMPlayerKnlFlags = E_MPLAYER_KNL_FLG_NULL;
    for (eMPlayerIdx = E_MPLAYER_FOREGROUND_PLAYER; eMPlayerIdx < E_MPLAYER_MAX_CONCURRENT_PLAYER_NUM; eMPlayerIdx++)
    {
        m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 = E_MPLAYER_KNL_FLG1_NULL;
        m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_INVALID;
        m_MPlayerInfo[eMPlayerIdx].u8BrowserHandle = INVALID_BROWSER_HANDLE;
    }

//    m_u16DeviceConnectStatus = 0;
    m_u32DeviceValidStatus = 0;
    memset(m_MPlayerDeviceStatus, 0, sizeof(MPlayerDeviceStatus)*NUM_OF_SUPPORT_DEVICES);
    memset(m_DriveInfo, 0, sizeof(MPlayerDrive)*NUM_OF_MAX_DRIVE);
    m_u8TotalDriveNum = 0;
    m_u16CurDriveIdx = MPLAYER_INVALID_INDEX;
    m_u32DriveStatus = 0;

    for(i=0;i<NUM_OF_MAX_DIRECTORY_DEPTH+1;i++)
    {
        m_u16CurDirectory[i] = MPLAYER_INVALID_INDEX;
    #if ENABLE_MPLAYER_SORT
        m_u16CurDirectoryPhy[i] = MPLAYER_INVALID_INDEX;
    #endif
#if (HIGH_SPEED_BROWSER)
        m_u16BufDirectory[i] = MPLAYER_INVALID_INDEX;
#endif

    }

    m_u16CurDirectoryDepth = 0;
#if (HIGH_SPEED_BROWSER)
    m_u16BufDirectoryDepth = MPLAYER_INVALID_INDEX;
    m_u16BufReadLongNameIdx = MPLAYER_INVALID_INDEX;
#endif
    m_u16CurFileIdx        = 0;
    m_u16TotalFileNum      = 0;
    m_u16CurPage1stFileIdx = 0;
    m_u16TotalPageNum      = 0;
    m_u16CurPageIdx        = 0;
    m_u16FilesPerPage      = 0;

    memset(m_u16SelectedFileNum, 0, sizeof(U16)*E_MPLAYER_TYPE_NUM);
#if PLAYLIST_BGM
    m_u16BGMSelectedFileNum = 0;
#endif
//    for(i=0;i<NUM_OF_MAX_DIRECTORY_DEPTH;i++)
//    {
//        m_u16CopyDirectory[i] = MPLAYER_INVALID_INDEX;
//    }
//    m_u16CopyFileIdx = MPLAYER_INVALID_INDEX;

//    memset(&m_CopyFileDrive, 0, sizeof(MPlayerDrive));
    memset(m_u16DirectoryNum, 0, sizeof(U16)*NUM_OF_MAX_DIRECTORY_DEPTH);
    m_eMediaType = E_MPLAYER_TYPE_INVALID;

    m_ePhotoPreviewState = E_PHOTO_PREVIEW_NONE;
    m_eMusicPreviewState = E_MUSIC_PREVIEW_NONE;
    m_eMoviePreviewState = E_MOVIE_PREVIEW_NONE;
    m_eTextPreviewState  = E_TEXT_PREVIEW_NONE;
#if ENABLE_EMBEDDED_PHOTO_DISPLAY
    m_eEmbeddedPhotoState = E_EMBEDDED_PHOTO_WAIT;
    m_u16PreFileIdx = INVALID_FILE_INDEX;
#endif
#if ENABLE_MPLAYER_SORT_EX
    _MApp_MPlayer_SetFileSortingMode(E_MPLAYER_SORT_NONE);
    _MApp_MPlayer_SetFileSortingOrderMode(E_MPLAYER_SORT_INCREMENT_ORDER);
#endif
    m_eMPlayerStateMachineState = STATE_MPLAYER_INIT;
    m_eRepeatMode[E_MPLAYER_FOREGROUND_PLAYER] = E_MPLAYER_REPEAT_NONE;
    m_eRepeatMode[E_MPLAYER_BACKGROUND_PLAYER] = E_MPLAYER_REPEAT_NONE;
#if RANDOM_PLAY
    m_bPlayNext = FALSE;
    m_eRandomMode[E_MPLAYER_FOREGROUND_PLAYER] = E_MPLAYER_RANDOM_NONE;
    m_eRandomMode[E_MPLAYER_BACKGROUND_PLAYER] = E_MPLAYER_RANDOM_NONE;
#endif
    m_ePlayMode   = E_MPLAYER_PLAY_SELECTED_FROM_CURRENT;
    m_u64NotifyEnableFlags = 0;
    m_u32PhotoSlideShowDelayTimeS = DEFAULT_PHOTO_SLIDESHOW_DELAY_TIME*1000;
    m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].u32ErrorDelayTime= 0;
    m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaPlayingStatus = E_MPLAYER_STATE_NONE;
    m_u8DecodedPics = 0;
    m_ePhotoType[0] = m_ePhotoType[1] = E_MPLAYER_SUBTYPE_INVALID;
    m_eZoom = E_MPLAYER_ZOOM_1;
//    m_ePhotoRotate = E_MPLAYER_PHOTO_ROTATE_0;
    m_eMoviePlayMode = E_MPLAYER_MOVIE_NORMAL;
    m_eMusicPlayMode = E_MPLAYER_MUSIC_NORMAL;
    m_eMovieMainExit = EXIT_VDPLAYER_NULL;
    bMusicRecording = FALSE;
    m_PrevUSBDeviceStatus = E_MPLAYER_USB_NONE;
    m_u8UserBrowserHandle = INVALID_BROWSER_HANDLE;

    m_eMPlayerKnlFlags |= E_MPLAYER_KNL_FLG_INITIALIZED;

    _MApp_Mplayer_InitializeCoProcessor();

    //Init FS
    MApp_MassStorage_Init();
    msAPI_FS_Init();
    msAPI_MSDCtrl_CheckDevices();
    m_u8CurDeviceIdx = E_MPLAYER_INVALID;
    m_u16CurDriveIdx = MPLAYER_INVALID_INDEX;
    m_eMPlayerKnlFlags |= E_MPLAYER_KNL_FLG_DEVICE_INITIALIZED;
    m_u32DeviceCheckTimer = msAPI_Timer_GetTime0();

    if(sizeof(stFileOpInfo)>0x1000)
    {
        __ASSERT(0);
    }

#if PLAYLIST_BGM
    MApp_MPlayer_BGM_Playlist_DeInit();
#endif
#if ENABLE_COPY_SELECTED_FILES
    MApp_MPlayer_ExitCopyMode();
#endif

    // Register Buff management
    //MApp_BufferManage_Register(TRUE);
    MApp_BufferManage_Register(FALSE);    //close buffer management, not necessary

    return E_MPLAYER_RET_OK;
}

//******************************************************************************
/// It will initialize the all devices.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_InitializeAllDevices(void)
{
    U8 u8DeviceCnt;

    MPLAYER_DBG(printf("MApp_MPlayer_InitializeAllDevices\n"));
    u8DeviceCnt = 0;
    m_PrevUSBDeviceStatus = E_MPLAYER_USB_NONE;
    memset(m_MPlayerDeviceStatus, 0, sizeof(MPlayerDeviceStatus)*NUM_OF_SUPPORT_DEVICES);
    m_u8TotalDriveNum = 0;

//    m_u16DeviceConnectStatus = MApp_MassStorage_DeviceConnectionDetect();
#if (ENABLE_CARDREADER)
    if(MApp_MassStorage_DeviceConnectionDetect() & (MS_USB_CONNECTED | MS_CREAD_CONNECTED))
#else
     if((MApp_MassStorage_DeviceConnectionDetect() & MS_USB_CONNECTED) ||
        (MApp_MassStorage_DeviceConnectionDetect() & MS_USB2_CONNECTED) ||
        (MApp_MassStorage_DeviceConnectionDetect() & MS_USB3_CONNECTED) ||
        (MApp_MassStorage_DeviceConnectionDetect() & MS_USB4_CONNECTED))
#endif
    {
        MApp_MassStorage_DeviceStatusCheck();
        m_u32DeviceValidStatus = MApp_MassStorage_GetValidDevice();

        if(_MApp_MPlayer_ReCalcDeviceDriveInfo())
        {
            if(MApp_MassStorage_DeviceConnectionDetect() & MS_USB_CONNECTED)
            {
                m_u8CurDeviceIdx = E_MPLAYER_USB0;
            }
            else if(MApp_MassStorage_DeviceConnectionDetect() & MS_USB2_CONNECTED)
            {
                m_u8CurDeviceIdx = E_MPLAYER_USB1;
            }
            else if(MApp_MassStorage_DeviceConnectionDetect() & MS_USB3_CONNECTED)
            {
                m_u8CurDeviceIdx = E_MPLAYER_USB2;
            }
            else if(MApp_MassStorage_DeviceConnectionDetect() & MS_USB4_CONNECTED)
            {
                m_u8CurDeviceIdx = E_MPLAYER_USB3;
            }
            else
            {
                m_u8CurDeviceIdx = E_MPLAYER_INVALID;
            }
            m_u16CurDriveIdx = MPLAYER_INVALID_INDEX;
//            MApp_MPlayer_ConnectDrive(m_u16CurDriveIdx);

            m_eMPlayerKnlFlags |= E_MPLAYER_KNL_FLG_DEVICE_INITIALIZED;

            m_u32DeviceCheckTimer = msAPI_Timer_GetTime0();
            return E_MPLAYER_RET_OK;
        }
    }

    m_u16CurDriveIdx = MPLAYER_INVALID_INDEX;
    m_eMPlayerKnlFlags |= E_MPLAYER_KNL_FLG_DEVICE_INITIALIZED;
    m_u32DeviceCheckTimer = msAPI_Timer_GetTime0();

    return E_MPLAYER_RET_FAIL;
}

//******************************************************************************
/// It will exit media player kernel, free all resources.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_ExitMediaPlayer(void)
{
    MPLAYER_DBG(printf("MApp_MPlayer_ExitMediaPlayer\n"));

    m_u8TotalDriveNum = 0;
//#ifndef ENABLE_PVR //do not reset for PVR system
//    msAPI_FS_Init(); //for switch source and USB abnorma
//#endif
    //MDrv_EjectUsbDevice();
    #if (!ENABLE_PVR)
    MApp_MPlayer_DisconnectAllDevices();
    #endif
    //_MApp_MPlayer_DisconnectDrive();

    MApp_MPlayer_StopMusic();
#if ENABLE_BGM
    U8 u8BGMHandler = m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].u8BrowserHandle;
    if(u8BGMHandler != INVALID_FS_ENVIRONMENT_INDEX)
    {
        MApp_FileBrowser_Destroy(u8BGMHandler);
        m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].u8BrowserHandle = INVALID_FS_ENVIRONMENT_INDEX;
    }
#endif

    //Stop USB Device Detection
    m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_DEVICE_INITIALIZED;

    memset(m_u16SelectedFileNum, 0, sizeof(U16)*E_MPLAYER_TYPE_NUM);

#if ENABLE_HK_MM
    if(MApp_VDPlayer_MediaCodec_Finalize() != TRUE)
    {
        MPLAYER_ERROR("!!!!!! %s --> MApp_VDPlayer_MediaCodec_Finalize FALSE \n",__FUNCTION__);
        return E_MPLAYER_RET_FAIL;
    }
#endif
    return E_MPLAYER_RET_OK;
}

//******************************************************************************
/// It will disconnect all USB and card reader devices.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_DisconnectAllDevices(void)
{
    enumMPlayerIdx eMPlayerIdx;

    msAPI_MSDCtrl_ResetDevices();
    msAPI_MSDCtrl_ResetPorts();
    MApp_FileBrowser_DeInit();

    if(m_u16CurDriveIdx != MPLAYER_INVALID_INDEX)
    {
        if(m_DriveInfo[m_u16CurDriveIdx].eDeviceType == E_MPLAYER_USB0)
        {
            MApp_MassStorage_DriveDisconnect(m_u16CurDriveIdx);
        }
      #if (ENABLE_USB_2)
        else if(m_DriveInfo[m_u16CurDriveIdx].eDeviceType == E_MPLAYER_USB1)
        {
            MApp_MassStorage_DriveDisconnect(m_u16CurDriveIdx);
        }
      #endif
      #if (ENABLE_CARDREADER)
        else if(m_DriveInfo[m_u16CurDriveIdx].eDeviceType == E_MPLAYER_CARDREADER0)
        {
            MApp_MassStorage_DriveDisconnect(m_u16CurDriveIdx);
        }
      #endif
    }

    m_u8UserBrowserHandle = INVALID_BROWSER_HANDLE;
    m_eMPlayerKnlFlags = E_MPLAYER_KNL_FLG_NULL;
    for (eMPlayerIdx = E_MPLAYER_FOREGROUND_PLAYER; eMPlayerIdx < E_MPLAYER_MAX_CONCURRENT_PLAYER_NUM; eMPlayerIdx++)
    {
        m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 = E_MPLAYER_KNL_FLG1_NULL;
        m_MPlayerInfo[eMPlayerIdx].u8BrowserHandle = INVALID_BROWSER_HANDLE;
    }

    return E_MPLAYER_RET_OK;
}
#if 0
//******************************************************************************
/// Disconnect the specific device.
/// @param  pDeviceInfo \b IN Specify the device. Ignore the u8DeviceAddr and u8Lun currently.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_DisconnectOneDevice(MPlayerDevice *pDeviceInfo)
{
    U8 u8DeviceIdx;
    U8 u8LunIdx;
    U8 u8PartitionIdx;

    for(u8DeviceIdx=0;u8DeviceIdx<NUM_OF_SUPPORT_DEVICES;u8DeviceIdx++)
    {
        if(m_MPlayerDeviceStatus[u8DeviceIdx].eDeviceType ==
           pDeviceInfo->eDeviceType)    // Already exists.
        {
            if(pDeviceInfo->eDeviceType == E_MPLAYER_USB0)
            {
                //for(u8LunIdx=0;u8LunIdx<NUM_OF_MAX_USB_LUN;u8LunIdx++)
                for(u8LunIdx=0;u8LunIdx<NUM_OF_MAX_LUN_PER_DEVICE;u8LunIdx++)
                {
                    if(m_MPlayerDeviceStatus[u8DeviceIdx].u16LunValid & (1<<u8LunIdx))
                    {
                        for(u8PartitionIdx=0;
                            u8PartitionIdx<NUM_OF_MAX_DRIVE_PER_LUN;
                            u8PartitionIdx++)
                        {
                            if(DRIVE_IS_VALID(u8DeviceIdx, 0, u8LunIdx, u8PartitionIdx))
                            {
                                m_u8TotalDriveNum--;
                            }
                        }

                        msAPI_MSDCtrl_ResetDevice(u8LunIdx);
                    }
                }
            }
          #if (ENABLE_CARDREADER)
            else if(pDeviceInfo->eDeviceType == E_MPLAYER_CARDREADER0)
            {
                if(DRIVE_IS_VALID(u8DeviceIdx, 0, 0, 0))
                {
                    m_u8TotalDriveNum--;
                }
                msAPI_MSDCtrl_ResetDevice(4);
            }
          #endif
            memset(&m_MPlayerDeviceStatus[u8DeviceIdx], 0, sizeof(MPlayerDeviceStatus));

            _MApp_MPlayer_MapDriveToPhysicalDevice();
            return E_MPLAYER_RET_OK;
        }
    }

    return E_MPLAYER_RET_FAIL;
}
#endif
//******************************************************************************
/// Set the drive to be the current drive and initialize file system for it.
/// @param  u16DriveIdx \b IN Speccify the drive index.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_ConnectDrive(U16 u16DriveIdx)
{
    //static U16 u16PrevDrive = 0;
    static U8 u8PreUserBrowserHandle = INVALID_BROWSER_HANDLE;
    UNUSED(u8PreUserBrowserHandle);
    BOOLEAN bFound = FALSE;
    U8 i;

    MPLAYER_DBG(printf("MApp_MPlayer_ConnectDrive %d\n", u16DriveIdx));
    //Check drive index and assign active drive
    for(i=0; i<MApp_MassStorage_GetTotalDriveNum(); i++)
    {
        //printf("[Connect Drive] %bu. Partition = %bu (%d)\n", i, m_DriveInfo[i].u8Partition, u16DriveIdx);
        if(m_DriveInfo[i].u8Partition == u16DriveIdx)
        {
        #if ENABLE_USB
            if(m_DriveInfo[i].u8Lun < MSD_USB_INDEX_END)
            {
                m_u8CurDeviceIdx = E_MPLAYER_USB0;
                bFound = TRUE;
                break;
            }
        #endif
        #if ENABLE_USB_2
            if(m_DriveInfo[i].u8Lun < MSD_USB_2_INDEX_END)
            {
                m_u8CurDeviceIdx = E_MPLAYER_USB1;
                bFound = TRUE;
                break;
            }
        #endif
        #if ENABLE_USB_3
            if(m_DriveInfo[i].u8Lun < MSD_USB_3_INDEX_END)
            {
                m_u8CurDeviceIdx = E_MPLAYER_USB2;
                bFound = TRUE;
                break;
            }
        #endif
        #if ENABLE_USB_4
            if(m_DriveInfo[i].u8Lun < MSD_USB_4_INDEX_END)
            {
                m_u8CurDeviceIdx = E_MPLAYER_USB3;
                bFound = TRUE;
                break;
            }
        #endif
        }
    }
    //printf("[Connect Drive] m_u8CurDeviceIdx = 0x%bX\n", m_u8CurDeviceIdx);
    if(!bFound)
    {
        return E_MPLAYER_RET_FAIL;
    }
    MApp_FileBrowser_Destroy(u8PreUserBrowserHandle);
    //MApp_MassStorage_DriveDisconnect(u16PrevDrive);
    if(m_u8UserBrowserHandle != u8PreUserBrowserHandle)
    {
        MApp_FileBrowser_Destroy(m_u8UserBrowserHandle);
    }

    m_u16TotalFileNum = 0;
    if(!MApp_MassStorage_DriveConnect(u16DriveIdx))
    {
        MPLAYER_DBG(printf("MApp_MPlayer_ConnectDrive No Device\n"));
        return E_MPLAYER_RET_FAIL;
    }
    //u16PrevDrive = u16DriveIdx;

#ifdef ENABLE_PTP
    if (!MApp_PTP_IsValidDevice_ByDrive(u16DriveIdx))
    {
        m_u8UserBrowserHandle = MApp_FileBrowser_Create(u16DriveIdx);
        if(m_u8UserBrowserHandle == INVALID_BROWSER_HANDLE)                                     //<--FILE BROWSER SECOND
        {
            MPLAYER_DBG(printf("MApp_MPlayer_ConnectDrive File browser Failed\n"));
            return E_MPLAYER_RET_FAIL;
        }
        u8PreUserBrowserHandle = m_u8UserBrowserHandle;
        MApp_FileBrowser_SetEnvironment(m_u8UserBrowserHandle);
        MApp_PTP_SetDeviceState(FALSE);
    }
    else
    {
        msAPI_PTP_StateInit();
        MApp_PTP_SetUsbPort_ByDrive(u16DriveIdx);
        MApp_PTP_SetDeviceState(TRUE);
    }
#else
    m_u8UserBrowserHandle = MApp_FileBrowser_Create(u16DriveIdx);
    if(m_u8UserBrowserHandle == INVALID_BROWSER_HANDLE)                                     //<--FILE BROWSER SECOND
    {
        MPLAYER_DBG(printf("MApp_MPlayer_ConnectDrive File browser Failed\n"));
        return E_MPLAYER_RET_FAIL;
    }
    u8PreUserBrowserHandle = m_u8UserBrowserHandle;
    MApp_FileBrowser_SetEnvironment(m_u8UserBrowserHandle);
#endif

    //fill "PATH_INFO_BUFFER_ADR" with "\"  when enter root
    {
        U16 *ppath;
        ppath = (U16 *)_PA2VA((((PATH_INFO_BUFFER_MEMORY_TYPE & MIU1) ? (PATH_INFO_BUFFER_ADR | MIU_INTERVAL) : (PATH_INFO_BUFFER_ADR))));
        ppath[0] = '\\';
        ppath[1] = 0;
    }

    for(i=0;i<NUM_OF_MAX_DIRECTORY_DEPTH+1;i++)
    {
        m_u16CurDirectory[i] = MPLAYER_INVALID_INDEX;
    #if ENABLE_MPLAYER_SORT
        m_u16CurDirectoryPhy[i] = MPLAYER_INVALID_INDEX;
    #endif
      #if (HIGH_SPEED_BROWSER)
        m_u16BufDirectory[i] = MPLAYER_INVALID_INDEX;
      #endif
    }

    m_u16CurDirectoryDepth = 0;
#if (HIGH_SPEED_BROWSER)
    m_u16BufDirectoryDepth = MPLAYER_INVALID_INDEX;
    m_u16BufReadLongNameIdx = MPLAYER_INVALID_INDEX;
#endif
    memset(m_u16DirectoryNum, 0, sizeof(U16)*NUM_OF_MAX_DIRECTORY_DEPTH);
    m_u16CurFileIdx = 0;

    m_u16CurDriveIdx = u16DriveIdx;
    m_u8TotalDriveNum = MApp_MassStorage_GetTotalDriveNum();

    if(_MApp_MPlayer_Browser_EnumCurDirectory()==FALSE)
    {
        return E_MPLAYER_RET_FAIL;
    }

    m_u16CurPage1stFileIdx = 0;
    m_u16CurPageIdx =0;

    if(m_u16FilesPerPage>0)
    {
        m_u16TotalPageNum = (m_u16TotalFileNum+m_u16FilesPerPage-1) / m_u16FilesPerPage;
    }

//    memset(m_u16SelectedFileNum, 0, sizeof(U16)*E_MPLAYER_TYPE_NUM);

    return E_MPLAYER_RET_OK;
}

//******************************************************************************
/// Set a file as selected.
/// About the meaning of eBegin, please refer to the figure 3-4. When there are 18 files in the current directory. The current page is page 1. Users want to select the 9th (FILE_06.JPG) file, can call the function as.
/// 1. MApp_MPlayer_SetFileSelected(E_MPLAYER_INDEX_CURRENT_PAGE, 2) or
/// 2. MApp_MPlayer_SetFileSelected(E_MPLAYER_INDEX_CURRENT_DIRECTORY, 8)
/// @param  eBegin     \b IN Specify set the base of file index is current directory or current page
/// @param  u16FileIdx \b IN Specify the file index offset.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_SetFileSelected(enumMPlayerFileIndexBegin eBegin, U16 u16FileIdx)
{
    if(eBegin == E_MPLAYER_INDEX_CURRENT_PAGE)
    {
        u16FileIdx += m_u16CurPage1stFileIdx;
    }
    else if(eBegin != E_MPLAYER_INDEX_CURRENT_DIRECTORY)
    {
        return E_MPLAYER_RET_FAIL;
    }

    _MApp_MPlayer_AddCurFileToPlayingList();
    _MApp_MPlayer_Browser_SetSelected(u16FileIdx, TRUE);

    return E_MPLAYER_RET_OK;
}

//******************************************************************************
/// Set a file as unselected.
/// @param  eBegin     \b IN Specify set the base of file index is current directory or current page
/// @param  u16FileIdx \b IN Specify the file index offset.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_SetFileUnselected(enumMPlayerFileIndexBegin eBegin, U16 u16FileIdx)
{
    if(eBegin == E_MPLAYER_INDEX_CURRENT_PAGE)
    {
        u16FileIdx += m_u16CurPage1stFileIdx;
    }
    else if(eBegin != E_MPLAYER_INDEX_CURRENT_DIRECTORY)
    {
        return E_MPLAYER_RET_FAIL;
    }

    _MApp_MPlayer_RemoveFileFromPlayingList(FALSE);
    _MApp_MPlayer_Browser_SetSelected(u16FileIdx, FALSE);

    return E_MPLAYER_RET_OK;
}

//******************************************************************************
/// Set a file as the current file.
/// About the meaning of eBegin, please refer to the figure 3-4. When there are 18 files in the current directory. The current page is page 1. Users want to set the 9th (FILE_06.JPG) file, can call the function as.
/// 1. MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_PAGE, 2) or
/// 2. MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, 8)
/// @param  eBegin     \b IN Specify set the base of file index is current directory or current page
/// @param  u16FileIdx \b IN Specify the file index offset.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_SetCurrentFile(enumMPlayerFileIndexBegin eBegin, U16 u16FileIdx)
{
    if(eBegin == E_MPLAYER_INDEX_CURRENT_PAGE)
    {
        u16FileIdx += m_u16CurPage1stFileIdx;
    }
    else if(eBegin != E_MPLAYER_INDEX_CURRENT_DIRECTORY)
    {
        MPLAYER_DBG(printf("Set Current File : Fail 1\n"));
        return E_MPLAYER_RET_FAIL;
    }

#if (THUMBNAIL_SHOW_DIRECTORY == 0)
    if(m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_THUMBNAIL_MODE)
    {
        if(u16FileIdx < m_u16DirectoryNum[m_u16CurDirectoryDepth])
        {
            MPLAYER_DBG(printf("Set Current File : Fail 2\n"));
            return E_MPLAYER_RET_FAIL;
        }
    }
#endif

    if(u16FileIdx >= m_u16TotalFileNum)
    {
        MPLAYER_DBG(printf("Set Current File : Fail 3\n"));
        return E_MPLAYER_RET_FAIL;
    }

    m_u16CurFileIdx = u16FileIdx;
    return E_MPLAYER_RET_OK;
}

#if 0
//******************************************************************************
/// Set a file as the copy file. This file is used as source when call MApp_MPlayer_BeginPasteFile later.
/// About the meaning of eBegin, please refer to the figure 3-4. When there are 18 files in the current directory. The current page is page 1. Users want to set the 9th (FILE_06.JPG) file, can call the function as.
/// 1. MApp_MPlayer_SetCopyFile(E_MPLAYER_INDEX_CURRENT_PAGE, 2) or
/// 2. MApp_MPlayer_SetCopyFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, 8)
/// @param  eBegin     \b IN Specify set the base of file index is current directory or current page
/// @param  u16FileIdx \b IN Specify the file index offset.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_SetCopyFile(enumMPlayerFileIndexBegin eBegin,
                                        U16 u16FileIdx)
{
    U8 u8CurrentDriveNo;
    stFileOpInfo *pstFileOpInfo;

//    U16 u16Len = 512; // full path, long name, '\0'
    MPlayerFileInfo fileInfo;

    if(eBegin == E_MPLAYER_INDEX_CURRENT_PAGE)
    {
        u16FileIdx += m_u16CurPage1stFileIdx;
    }
    else if(eBegin != E_MPLAYER_INDEX_CURRENT_DIRECTORY)
    {
        return E_MPLAYER_RET_FAIL;
    }

    if((MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,
                                   u16FileIdx,
                                   &fileInfo) !=  E_MPLAYER_RET_OK) ||
        (fileInfo.eAttribute & E_MPLAYER_FILE_DIRECTORY))
    {
        return E_MPLAYER_RET_FAIL;
    }

    u8CurrentDriveNo = MApp_FileBrowser_GetCurrentDriveName();

    pstFileOpInfo = (stFileOpInfo *)_PA2VA(((FILE_OPERATION_INFO_BUFFER_MEMORY_TYPE & MIU1) ? (FILE_OPERATION_INFO_BUFFER_ADR | MIU_INTERVAL) : (FILE_OPERATION_INFO_BUFFER_ADR)));
    memset(pstFileOpInfo, 0, sizeof(*pstFileOpInfo));
    pstFileOpInfo->u8CopySrcDeviceNo = u8CurrentDriveNo;
    pstFileOpInfo->u8CopySrcDriveIndex = m_u16CurDriveIdx;
    pstFileOpInfo->stCopySrcEntry = fileInfo.fileEntry;

    U8 u8Len;
    U8 *pu8LongFileName = (U8*)_PA2VA((FILE_OPERATION_INFO_BUFFER_MEMORY_TYPE & MIU1) ? (FILE_OPERATION_INFO_BUFFER_ADR | MIU_INTERVAL) : (FILE_OPERATION_INFO_BUFFER_ADR))+((U32)(((stFileOpInfo *)NULL)->ps8CopySrcLongName));
    // Get long file name from file entry.
    u8Len = MApp_FileBrowser_GetLongFileNameByFileEntry(&fileInfo.fileEntry, (U32)pu8LongFileName,
                                                     (FILE_INFO_LONG_FILENAME_SIZE/2-1));
    u8Len = (u8Len > (FILE_INFO_LONG_FILENAME_SIZE/2-1)) ?
             FILE_INFO_LONG_FILENAME_SIZE/2-1 : u8Len;

    pu8LongFileName[u8Len*2] = 0;
    pu8LongFileName[u8Len*2+1] = 0;

    m_eMPlayerKnlFlags |= E_MPLAYER_KNL_FLG_COPY_FILE_SELECTED;

    return E_MPLAYER_RET_OK;
}

//******************************************************************************
/// Check the copy file is exist.
/// @return TRUE if copy file flag was set.
//******************************************************************************
BOOLEAN MApp_MPlayer_IsCopyFileExist(void)
{
    return (m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_COPY_FILE_SELECTED);
}
#endif

#if ENABLE_COPY_SELECTED_FILES
BOOLEAN MApp_MPlayer_EnterCopyMode(void)
{
    m_bIsCopyMode = TRUE;
    return TRUE;
}

BOOLEAN MApp_MPlayer_ExitCopyMode(void)
{
    m_bIsCopyMode = FALSE;
    return TRUE;
}

BOOLEAN MApp_MPlayer_QueryIsCopyMode(void)
{
    return m_bIsCopyMode;
}

static BOOLEAN _MApp_MPlayer_CopySelectedFile(U16 u16FileIdx)
{
    MPlayerPlayListInfo *pstPlayListInfo;
    U32 u32XdataWindowBase;

    if(NUM_OF_MAX_SELECTED_FILE < m_u16SelectedFileNum[m_eMediaType]
    ||                        0 == m_u16SelectedFileNum[m_eMediaType])
    {
        return FALSE;
    }

    if(_MApp_MPlayer_GetPlayListAddressByMediaType(m_eMediaType, &u32XdataWindowBase)==FALSE)
    {
        return FALSE;
    }

    pstPlayListInfo = (MPlayerPlayListInfo *) (_PA2VA(u32XdataWindowBase));

    //check if dst drive space is enough.
    U32 u32FileSizeInKB, u32DriveUnusedSizeInKB;

    u32FileSizeInKB = (PLAY_LIST_FILE_ENTRY(u16FileIdx).FileLength.Lo+1023)/1024;
    u32DriveUnusedSizeInKB = msAPI_FCtrl_GetUnusedSizeInKB_ByDriveIndex_New(m_u16CopyDstDriveIdx);

    if(u32FileSizeInKB > u32DriveUnusedSizeInKB)
    {
        NOTIFY(E_MPLAYER_NOTIFY_NO_ENOUGH_SPACE_OF_COPY_FILE,(U16*)&u16CurrentCopyIndex);
        return FALSE;
    }

    U8 u8CurrentDriveNo;
    stFileOpInfo *pstFileOpInfo;

    if(m_u16CopySrcDriveIdx != PLAY_LIST_DRIVE(u16FileIdx))
    {

        if(FALSE == _MApp_MPlayer_Browser_ChangeBrowsingDrive(&m_u8CopySrcFileBrowserHandle,
                                            m_u16CopySrcDriveIdx, PLAY_LIST_DRIVE(u16FileIdx)))
        {
            return FALSE;
        }

        m_u16CopySrcDriveIdx = PLAY_LIST_DRIVE(u16FileIdx);
    }

    if(m_u8CopySrcFileBrowserHandle != MApp_FileBrowser_GetEnvironment())
    {
        //change to copy src file browser handle.
        MApp_FileBrowser_SetEnvironment(m_u8CopySrcFileBrowserHandle);
    }

    u8CurrentDriveNo = MApp_FileBrowser_GetCurrentDriveName();

    pstFileOpInfo = (stFileOpInfo *)_PA2VA(((FILE_OPERATION_INFO_BUFFER_MEMORY_TYPE & MIU1) ? (FILE_OPERATION_INFO_BUFFER_ADR | MIU_INTERVAL) : (FILE_OPERATION_INFO_BUFFER_ADR)));
    memset(pstFileOpInfo, 0, sizeof(*pstFileOpInfo));
    pstFileOpInfo->u8CopySrcDeviceNo = u8CurrentDriveNo;
    pstFileOpInfo->u8CopySrcDriveIndex = m_u16CurDriveIdx;
    pstFileOpInfo->stCopySrcEntry = PLAY_LIST_FILE_ENTRY(u16FileIdx);
    memcpy(pstFileOpInfo->u8ExtFileName, PLAY_LIST_EXT_NAME(u16FileIdx), 3+1);

    U8 u8Len;
    U8 *pu8LongFileName = (U8*)_PA2VA((FILE_OPERATION_INFO_BUFFER_MEMORY_TYPE & MIU1) ? (FILE_OPERATION_INFO_BUFFER_ADR | MIU_INTERVAL) : (FILE_OPERATION_INFO_BUFFER_ADR))+((U32)(((stFileOpInfo *)NULL)->ps8CopySrcLongName));
    // Get long file name from file entry.
    u8Len = MApp_FileBrowser_GetLongFileNameByFileEntry(&pstFileOpInfo->stCopySrcEntry, (U32)pu8LongFileName,
                                                     (FILE_INFO_LONG_FILENAME_SIZE/2-1));
    u8Len = (u8Len > (FILE_INFO_LONG_FILENAME_SIZE/2-1)) ?
             FILE_INFO_LONG_FILENAME_SIZE/2-1 : u8Len;

    pu8LongFileName[u8Len*2] = 0;
    pu8LongFileName[u8Len*2+1] = 0;

#if ENABLE_SUBTITLE_COPY_AND_DELETE
    //Before copy next movie file, we have to find the external subtitle file number.
    m_u8CurCopyingDeletingExtSubtitleFileIdx = 0;
#if STORE_SUBTITLE_ENTRY_TO_SUBTITLE_BUFFER
    //Search subtitle file in Subtitle file buffer. PS:Search in USB is slow , and search in Subtitle file buffer is fast.
    m_u8CopyDeleteExtSubtitleFileNum = _MApp_MPlayer_ScanExtSubtitleFileNumByMovieFileEntry(&pstFileOpInfo->stCopySrcEntry, FALSE);
#else
    //Search subtitle file in USB. PS:Search in USB is slow , and search in Subtitle file buffer is fast.
    m_u8CopyDeleteExtSubtitleFileNum = _MApp_MPlayer_ScanExtSubtitleFileNumByMovieFileEntry(&pstFileOpInfo->stCopySrcEntry, TRUE);
#endif
#endif

    m_eMPlayerKnlFlags |= E_MPLAYER_KNL_FLG_COPY_INIT;

    return TRUE;
}

#if ENABLE_SUBTITLE_COPY_AND_DELETE
static BOOLEAN _MApp_MPlayer_CopyExtFiles(U8 u8ExtFileInx)
{
    U8 u8CurrentDriveNo;
    stFileOpInfo *pstFileOpInfo;
    FileEntry fileEntry;
    U8 u8ExtFileName[3+1];

    if(m_u8CopySrcFileBrowserHandle != MApp_FileBrowser_GetEnvironment())
    {
        //change to copy src file browser handle.
        MApp_FileBrowser_SetEnvironment(m_u8CopySrcFileBrowserHandle);
    }

    u8CurrentDriveNo = MApp_FileBrowser_GetCurrentDriveName();

    pstFileOpInfo = (stFileOpInfo *)_PA2VA(((FILE_OPERATION_INFO_BUFFER_MEMORY_TYPE & MIU1) ? (FILE_OPERATION_INFO_BUFFER_ADR | MIU_INTERVAL) : (FILE_OPERATION_INFO_BUFFER_ADR)));

    #if ENABLE_EXTERNAL_SUBTITLE_FAST_SWITCHING
        fileEntry = m_aExtFileInfoList[u8ExtFileInx].fileEntry;
        memcpy(&u8ExtFileName, &m_aExtFileInfoList[u8ExtFileInx].u8ExtFileName, EXT_FILENAME_SIZE+1);
    #else
        fileEntry = m_ExtFileInfo.fileEntry;
        memcpy(&u8ExtFileName, &m_ExtFileInfo.u8ExtFileName, EXT_FILENAME_SIZE+1);
        UNUSED(u8ExtFileInx);
    #endif

    //check if dst drive space is enough.
    U32 u32FileSizeInKB, u32DriveUnusedSizeInKB;

    u32FileSizeInKB = (fileEntry.FileLength.Lo+1023)/1024;
    u32DriveUnusedSizeInKB = msAPI_FCtrl_GetUnusedSizeInKB_ByDriveIndex_New(m_u16CopyDstDriveIdx);

    if(u32FileSizeInKB > u32DriveUnusedSizeInKB)
    {
        NOTIFY(E_MPLAYER_NOTIFY_NO_ENOUGH_SPACE_OF_COPY_FILE,(U16*)&u16CurrentCopyIndex);
        return FALSE;
    }

    pstFileOpInfo->stCopySrcEntry = fileEntry;
    memcpy(&pstFileOpInfo->u8ExtFileName, u8ExtFileName, EXT_FILENAME_SIZE+1);

    U8 u8Len;
    U8 *pu8LongFileName = (U8*)_PA2VA((FILE_OPERATION_INFO_BUFFER_MEMORY_TYPE & MIU1) ? (FILE_OPERATION_INFO_BUFFER_ADR | MIU_INTERVAL) : (FILE_OPERATION_INFO_BUFFER_ADR))+((U32)(((stFileOpInfo *)NULL)->ps8CopySrcLongName));
    // Get long file name from file entry.
    u8Len = MApp_FileBrowser_GetLongFileNameByFileEntry(&fileEntry, (U32)pu8LongFileName,
                                                     (FILE_INFO_LONG_FILENAME_SIZE/2-1));
    u8Len = (u8Len > (FILE_INFO_LONG_FILENAME_SIZE/2-1)) ?
             FILE_INFO_LONG_FILENAME_SIZE/2-1 : u8Len;

    pu8LongFileName[u8Len*2] = 0;
    pu8LongFileName[u8Len*2+1] = 0;

    m_eMPlayerKnlFlags |= E_MPLAYER_KNL_FLG_COPY_INIT;

    return TRUE;
}

//******************************************************************************
/// Get extension files total size by playlist index.
/// @param  u16FileIdx \b IN Specify index of play list
/// @param  eMediaType \b IN Specify Media Type
/// @return Total EXT files size.
//******************************************************************************
U32 MApp_MPlayer_GetExternalSubtitleFileSizeByPlaylistIndex(U16 u16FileIdx, enumMPlayerMediaType eMediaType)
{
    if(m_u16SelectedFileNum[eMediaType] <= u16FileIdx)
    {
        return 0;
    }

    MPlayerPlayListInfo *pstPlayListInfo = NULL;
    U32 u32XdataWindowBase;

    if(_MApp_MPlayer_GetPlayListAddressByMediaType(eMediaType, &u32XdataWindowBase)==FALSE)
    {
        return 0;
    }

    pstPlayListInfo = (MPlayerPlayListInfo *) (_PA2VA(u32XdataWindowBase));

    MPLAYER_DBG(printf("\033[0;35mMApp_MPlayer_GetExtFilesTotalSizeByPlaylistIndex, u32ExtFilesTotalSize = %ld\033[0m\n", PLAY_LIST_EXTFILESTOTALSIZE(u16FileIdx)););
    return PLAY_LIST_EXTFILESTOTALSIZE(u16FileIdx);
}
#endif

static BOOLEAN _MApp_MPlayer_CopyNext(void)
{
    MPLAYER_DBG(printf("_MApp_MPlayer_CopyNext()\n"));

#if ENABLE_SUBTITLE_COPY_AND_DELETE
    if(m_bCopyingExtSubtitleFile)
    {
        m_u8CurCopyingDeletingExtSubtitleFileIdx++;
    }

    if(m_u8CurCopyingDeletingExtSubtitleFileIdx < m_u8CopyDeleteExtSubtitleFileNum)
        {
        //TRUE: means int needs to copy external subtitle file instead of next movie file.
        m_bCopyingExtSubtitleFile = TRUE;
        }
        else
        {
        //FALSE: means it needs to copy next movie file instead of external subtitle file.
        m_bCopyingExtSubtitleFile = FALSE;
    }

    if(m_bCopyingExtSubtitleFile)
    {
        //Copy external subtitle file.
        if(_MApp_MPlayer_CopyExtFiles(m_u8CurCopyingDeletingExtSubtitleFileIdx)==FALSE)
        {
            return FALSE;
        }
    }
    else
#endif
    {
        u16CurrentCopyIndex++;
        if(u16CurrentCopyIndex >= m_u16SelectedFileNum[m_eMediaType])
        {
            //end of last copy file.
            m_bEndofCopyFiles = TRUE;
            return FALSE;
        }
        //Copy movie file.
        if(_MApp_MPlayer_CopySelectedFile(u16CurrentCopyIndex)==FALSE)
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOLEAN MApp_MPlayer_BeginCopySelectedFiles(U16 u16DstDriveNo, U16* pu16DstPath)
{
    U8 au8FolderName[FILE_INFO_LONG_FILENAME_SIZE] = {0};
    U16 *pu16FolderName = (void*)au8FolderName;
    U16 *pu16TempDstPath = pu16DstPath;
    MPlayerDrive DriveInfo;

    memset(&DriveInfo,0,sizeof(MPlayerDrive));
    if((u16DstDriveNo >= NUM_OF_MAX_DRIVE) || (pu16DstPath == NULL)||(m_u16SelectedFileNum[m_eMediaType]==0))
    {
        return FALSE;
    }

    U16 u16Count, u16SelectedCount;
    LongLong stFileLength;

    u16SelectedCount = MApp_MPlayer_QueryPlayListFileNum(m_eMediaType);
    m_u64TotalCopySize = 0;

    for(u16Count=0; u16Count<u16SelectedCount; u16Count++)
    {
        MApp_MPlayer_GetFileSizeByPlaylistIndex(u16Count, m_eMediaType, &stFileLength);
        m_u64TotalCopySize += (((U64)stFileLength.Hi)<<32) + ((U64)stFileLength.Lo);
    #if ENABLE_SUBTITLE_COPY_AND_DELETE
        if(m_eMediaType==E_MPLAYER_TYPE_MOVIE)
        {
            m_u64TotalCopySize += (U64)MApp_MPlayer_GetExternalSubtitleFileSizeByPlaylistIndex(u16Count, m_eMediaType);
        }
    #endif
    }

    m_u8CopySrcFileBrowserHandle = MApp_FileBrowser_GetEnvironment();
    m_u16SrcDriveIdx = m_u16CurDriveIdx;
    m_u16CopySrcDriveIdx = m_u16SrcDriveIdx;
    m_u16CopyDstDriveIdx = u16DstDriveNo;
    MApp_MPlayer_QueryPartitionIdxInDrive(m_u16SrcDriveIdx, &DriveInfo);
    m_u8CopySrcLun = DriveInfo.u8Lun;
    MApp_MPlayer_QueryPartitionIdxInDrive(m_u16CopyDstDriveIdx, &DriveInfo);
    m_u8CopyDstLun = DriveInfo.u8Lun;
    u16CurrentCopyIndex = 0;
    m_u64TotalCopiedSize = 0;
    m_u32TotalCopiedPercentage = 0;
    m_bEndofCopyFiles = FALSE;
#if ENABLE_SUBTITLE_COPY_AND_DELETE
    m_bCopyingExtSubtitleFile = FALSE;
#endif

    //always add new browser handle, even the drive is used.
    m_u8CopyDstFileBrowserHandle = MApp_FileBrowser_Create(u16DstDriveNo);

    if(m_u8CopyDstFileBrowserHandle == INVALID_BROWSER_HANDLE)
    {
        return FALSE;
    }
    //change to copy dst file browser handle.
    MApp_FileBrowser_SetEnvironment(m_u8CopyDstFileBrowserHandle);

    if(MApp_FileBrowser_GetCurrentFileSystemType() != FILE_SYSTEM_TYPE_FAT)
    {
        //change to copy src file browser handle.
        MApp_FileBrowser_SetEnvironment(m_u8CopySrcFileBrowserHandle);
        MApp_FileBrowser_Destroy(m_u8CopyDstFileBrowserHandle);
        m_u8CopyDstFileBrowserHandle = INVALID_BROWSER_HANDLE;
        NOTIFY(E_MPLAYER_NOTIFY_UNSUPPORT_FS_OF_COPY_FILE,(U16*)&u16CurrentCopyIndex);

        return FALSE;
    }

    BOOLEAN bIsCopyInitOK = FALSE;
    U16 i=0, j=0;

    printf("Check dst Path begin.....\n");
    //pu16DstPath--->\111\222\333
    if(pu16DstPath[0] == '\\')
    {
        if(pu16DstPath[1] == '\0')
        {
            //root
            bIsCopyInitOK = TRUE;
        }
        else
        {
            i=1;
            pu16TempDstPath = &pu16DstPath[i];
            while(i < FILE_INFO_LONG_FILENAME_SIZE/2)
            {
                if(pu16DstPath[i] == '\\' || pu16DstPath[i] == '\0')
                {
                    if(j != 0)
                    {
                        memcpy(pu16FolderName, pu16TempDstPath, j*2);
                        pu16FolderName[j] = '\0';

                        if(MApp_FilrBrowser_GetNameExistedInCurrent(pu16FolderName, j, &m_CopyDstDirEntry) == FALSE)
                        {
                            if(MApp_FileBrowser_OpenNewFolder(pu16FolderName, j) == FALSE)
                            {
                                printf("ERROR MApp_FileBrowser_OpenNewFolder Fail \n");
                                break;
                            }
                            if(MApp_FilrBrowser_GetNameExistedInCurrent(pu16FolderName, j, &m_CopyDstDirEntry) == FALSE)
                            {
                                printf("ERROR MApp_FilrBrowser_GetNameExistedInCurrent Fail \n");
                                break;
                            }
                        }

                        if(MApp_FileBrowser_DirectoryChange(&m_CopyDstDirEntry) == FALSE)
                        {
                            printf("ERROR MApp_FileBrowser_DirectoryChange Fail \n");
                            break;
                        }

                        if(pu16DstPath[i] == '\0')
                        {
                            bIsCopyInitOK = TRUE;
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }

                    i++;
                    j=0;
                    pu16TempDstPath = &pu16DstPath[i];
                }
                else
                {
                    i++;
                    j++;
                }
            }
        }
    }

    //change to copy src file browser handle.
    MApp_FileBrowser_SetEnvironment(m_u8CopySrcFileBrowserHandle);

    if(bIsCopyInitOK == FALSE)
    {
        printf("Check dst Path Error\n");
        MApp_FileBrowser_Destroy(m_u8CopyDstFileBrowserHandle);
        m_u8CopyDstFileBrowserHandle = INVALID_BROWSER_HANDLE;
        return FALSE;
    }

    printf("Check dst Path done and enter dst path done\n");

    m_bUserBreakCopy = FALSE;

    if(_MApp_MPlayer_CopySelectedFile(u16CurrentCopyIndex) == FALSE)
    {
        MApp_FileBrowser_Destroy(m_u8CopyDstFileBrowserHandle);
        m_u8CopyDstFileBrowserHandle = INVALID_BROWSER_HANDLE;
        return FALSE;
    }

    m_eMPlayerKnlFlags |= E_MPLAYER_KNL_FLG_COPY_PLAY;

    return TRUE;
}

//******************************************************************************
/// Begin copy selected files and set return folder.
/// @param  u16DstDriveNo \b IN Specify destination pasted drive.
/// @param  pu16DstPath \b IN Specify destination pasted Path.
/// @param  bAfterCopyDoneStayInSrcFolder  \b IN    TRUE: return to source folder.
///                                                 FALSE: return to destination folder.
/// @return TRUE/FALSE.
//******************************************************************************
BOOLEAN MApp_MPlayer_BeginCopySelectedFiles_New(U16 u16DstDriveNo, U16* pu16DstPath, BOOLEAN bAfterCopyDoneStayInSrcFolder)
{
    m_bAfterCopyDoneStayInSrcFolder = bAfterCopyDoneStayInSrcFolder;

    return MApp_MPlayer_BeginCopySelectedFiles(u16DstDriveNo, pu16DstPath);
}

static BOOLEAN _MApp_MPlayer_BeginPasteFileAndRenameIfFileExisted(void)
{
    if(!(m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_COPY_INIT))
    {
        return FALSE;
    }

    //change to copy dst file browser handle.
    MApp_FileBrowser_SetEnvironment(m_u8CopyDstFileBrowserHandle);

    #define MAX_EXTNAME_SIZE_IN_LONGFILENAME_CASE   4
    #define EXTNAME_SIZE_IN_SHORTNAME_CASE          3
    U16 u16UniFileNameLen;
    U16 u16CaptureIdx = 1, u16OrgDotPosition=0, u16NewDotPosition;
    U16 au16Filename[FILE_INFO_LONG_FILENAME_SIZE/2+1];
    U8 au8ExtFileName[MAX_EXTNAME_SIZE_IN_LONGFILENAME_CASE]={0}, u8ExtFileNameLen=0;
    U8 *pu8Filename = (void*)au16Filename;
    memset(pu8Filename, 0, FILE_INFO_LONG_FILENAME_SIZE);
    stFileOpInfo *pstFileOpInfo;

    pstFileOpInfo = (stFileOpInfo *)_PA2VA(((FILE_OPERATION_INFO_BUFFER_MEMORY_TYPE & MIU1) ? (FILE_OPERATION_INFO_BUFFER_ADR | MIU_INTERVAL) : (FILE_OPERATION_INFO_BUFFER_ADR)));

    // Truncate long string name
    memcpy(pu8Filename, pstFileOpInfo->ps8CopySrcLongName, FILE_INFO_LONG_FILENAME_SIZE);
    u16UniFileNameLen = (U16)FS_strlen_U(au16Filename);

    BOOLEAN bFindDot = FALSE;
    S16 s16Cnt = u16UniFileNameLen*2;
    //Try to find last dot.
    for(;s16Cnt >= 0; s16Cnt-=2)
    {
        if(pu8Filename[s16Cnt]==0x2E)//'.'
        {
            u16OrgDotPosition = s16Cnt;
            bFindDot = TRUE;
            break;
        }
    }

    if(bFindDot == TRUE)
    {
        s16Cnt += 2;
        while((s16Cnt < u16UniFileNameLen*2) && (u8ExtFileNameLen < MAX_EXTNAME_SIZE_IN_LONGFILENAME_CASE))
        {
            au8ExtFileName[u8ExtFileNameLen] = pu8Filename[s16Cnt];
            u8ExtFileNameLen++;
            s16Cnt += 2;
        }
    }
    else
    {
        //Long file name size is longer than buffer size.
        //In this case, dot and extension name are lost.
    }

    //Extension name be truncated,
    //Use extension name got from file info and rename.
    if(bFindDot==FALSE
    || u16OrgDotPosition > (FILE_INFO_LONG_FILENAME_SIZE & 0xfffe)-(EXTNAME_SIZE_IN_SHORTNAME_CASE+1)*2)//(ext + dot)*2
    {
        u8ExtFileNameLen = EXTNAME_SIZE_IN_SHORTNAME_CASE;
        au8ExtFileName[0] = pstFileOpInfo->u8ExtFileName[0];
        au8ExtFileName[1] = pstFileOpInfo->u8ExtFileName[1];
        au8ExtFileName[2] = pstFileOpInfo->u8ExtFileName[2];

        U16 u16TempPos;
        u16OrgDotPosition = MIN(u16UniFileNameLen*2, (FILE_INFO_LONG_FILENAME_SIZE & 0xfffe)-(u8ExtFileNameLen+2)*2);//(ext + dot + \0)*2

        //fill dot
        pu8Filename[u16OrgDotPosition] = 0x2E; //'.'
        pu8Filename[u16OrgDotPosition+1] = 0x00;

        u16TempPos = u16OrgDotPosition+2;

        //fill ext file name
        for(s16Cnt=0;s16Cnt<u8ExtFileNameLen;s16Cnt++)
        {
            pu8Filename[u16TempPos] = au8ExtFileName[s16Cnt];
            pu8Filename[u16TempPos+1] = 0x00;
            u16TempPos += 2;
        }

        //fill /0
        pu8Filename[u16TempPos] = 0x00;
        pu8Filename[u16TempPos+1] = 0x00;

        u16UniFileNameLen = (U16)FS_strlen_U(au16Filename);
    }
    else
    {
        if(u8ExtFileNameLen==0)
        {
            return FALSE;
        }
    }

    if(MApp_MPlayer_IsFilenameExistInCurrentDirectory(au16Filename, u16UniFileNameLen))
    {
        u16NewDotPosition = u16OrgDotPosition + 4*2;//original dot position + _xxx*2

        u16NewDotPosition = MIN(u16NewDotPosition, (FILE_INFO_LONG_FILENAME_SIZE & 0xfffe)-(u8ExtFileNameLen+2)*2);//(ext + dot + \0)*2
        u16UniFileNameLen = (u16NewDotPosition + (1+u8ExtFileNameLen)*2)/2; //(dot position + (dot + ext)*2)

        U16 u16TempPos;

        //fill dot
        pu8Filename[u16NewDotPosition] = 0x2E; //'.'
        pu8Filename[u16NewDotPosition+1] = 0x00;

        u16TempPos = u16NewDotPosition+2;

        //fill ext file name
        for(s16Cnt=0;s16Cnt<u8ExtFileNameLen;s16Cnt++)
        {
            pu8Filename[u16TempPos] = au8ExtFileName[s16Cnt];
            pu8Filename[u16TempPos+1] = 0x00;
            u16TempPos += 2;
        }

        //fill /0
        pu8Filename[u16TempPos] = 0x00;
        pu8Filename[u16TempPos+1] = 0x00;

        do
        {
            msAPI_Timer_ResetWDT();
            if(u16CaptureIdx == 1000)
            { // maximum captured number
                //sprintf(u8Digit, "_%02d", u16CaptureIdx);
                break;
            }

            //fill _xxx
            pu8Filename[u16NewDotPosition-8] = 0x5F; // '_'
            pu8Filename[u16NewDotPosition-7] = 0x00;
            pu8Filename[u16NewDotPosition-6] = 0x30+((u16CaptureIdx/100)%10);
            pu8Filename[u16NewDotPosition-5] = 0x00;
            pu8Filename[u16NewDotPosition-4] = 0x30+((u16CaptureIdx/10)%10);
            pu8Filename[u16NewDotPosition-3] = 0x00;
            pu8Filename[u16NewDotPosition-2] = 0x30+(u16CaptureIdx%10);
            pu8Filename[u16NewDotPosition-1] = 0x00;
            u16CaptureIdx++;
        }
        while(MApp_MPlayer_IsFilenameExistInCurrentDirectory(au16Filename, u16UniFileNameLen));
    }

    BOOLEAN bOK;
    if(MApp_MPlayer_BeginPasteFile(pu8Filename)==E_MPLAYER_RET_OK)
    {
        MPLAYER_DBG(printf("MApp_MPlayer_BeginPasteFile success\n"););
        bOK = TRUE;
    }
    else
    {
        MPLAYER_DBG(printf("MApp_MPlayer_BeginPasteFile fail\n"););
        bOK = FALSE;
    }

    //change to copy src file browser handle.
    MApp_FileBrowser_SetEnvironment(m_u8CopySrcFileBrowserHandle);

    return bOK;
}

//******************************************************************************
/// Generate a new file to the current directory, the source file is defined by _MApp_MPlayer_CopySelectedFile.
/// @param  pFileName \b IN Specify destination file name.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_BeginPasteFile(U8 *pFileName)
{
    stFileOpInfo *pstFileOpInfo;
    FileEntry copySrcFileEntry;
    U16 au16FileName[FILE_INFO_LONG_FILENAME_SIZE];
    U8 len;

    // get src info, also save dest full path
    pstFileOpInfo = (stFileOpInfo  *)_PA2VA(((FILE_OPERATION_INFO_BUFFER_MEMORY_TYPE & MIU1) ? (FILE_OPERATION_INFO_BUFFER_ADR | MIU_INTERVAL) : (FILE_OPERATION_INFO_BUFFER_ADR)));
    memcpy(&copySrcFileEntry ,&(pstFileOpInfo->stCopySrcEntry),sizeof(FileEntry));

    //len=UnicodeLen(pstFileOpInfo->ps8CopySrcLongName);
    len=UnicodeLen((S8*)pFileName);

    memset(au16FileName,0,FILE_INFO_LONG_FILENAME_SIZE);
    //memcpy(au16FileName,pstFileOpInfo->ps8CopySrcLongName,sizeof(au16FileName));
    memcpy(au16FileName,pFileName,FILE_INFO_LONG_FILENAME_SIZE);

    m_u8FileOpReadHandle = msAPI_FCtrl_FileOpen(&copySrcFileEntry,OPEN_MODE_BINARY_FOR_READ);

    if (m_u8FileOpReadHandle == INVALID_FILE_HANDLE)
    {
        MPLAYER_DBG(printf("FCTRL_INVALID_FILE_HANDLE(read)\n"));
        goto MApp_MPlayer_BeginPasteFile_END;
    }

    // initial the src device/drive if it's needed
    m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_FILE_OP_DIFF_DRIVE;

    MApp_MPlayer_StopPreview();

    // create read file handle
    m_u32CopyDataLeft = msAPI_FCtrl_FileLength(m_u8FileOpReadHandle);
    m_u32CopyDataLen = m_u32CopyDataLeft;

    m_u8FileOpWriteHandle = MApp_FileBrowser_OpenNewFileForWrite(au16FileName, len);
    if (m_u8FileOpWriteHandle == FCTRL_INVALID_FILE_HANDLE)
    {
        __ASSERT(0);
        MPLAYER_DBG(printf("FCTRL_INVALID_FILE_HANDLE(write)\n"));
        goto MApp_MPlayer_BeginPasteFile_END;
    }

    return E_MPLAYER_RET_OK;

MApp_MPlayer_BeginPasteFile_END:

    if(m_u8FileOpWriteHandle != FCTRL_INVALID_FILE_HANDLE)
    {
        msAPI_FCtrl_FileClose(m_u8FileOpWriteHandle);
    }
    if(m_u8FileOpReadHandle != FCTRL_INVALID_FILE_HANDLE)
    {
        msAPI_FCtrl_FileClose(m_u8FileOpReadHandle);
    }

    return E_MPLAYER_RET_FAIL;
}

//******************************************************************************
/// Set user break to TRUE.
/// @return N/A
//******************************************************************************
void MApp_MPlayer_StopCopy(void)
{
    m_bUserBreakCopy = TRUE;
}

//******************************************************************************
/// Read back the current complete percentage for copying file.
/// @return 0~100: Indicate the complete percentage.
///         Other: Failed to get the status.
//******************************************************************************
U16 MApp_MPlayer_QueryPasteFileStatus(void)
{
#if 0
    U32 u32CopyedData;

    if(m_u32CopyDataLeft == 0)
    {
        return 100;     // 100%
    }
    else
    {
        if(m_u32CopyDataLen == 0)
        {
            return 0;
        }
        u32CopyedData = m_u32CopyDataLen - m_u32CopyDataLeft;

        if(m_u32CopyDataLen < 1024)
        {
            //Avoid division by zero
            return ((u32CopyedData) * 100) / (m_u32CopyDataLen);
        }
        else
        {
            //Divide 1024 first to avoid U32 overflow
            return ((u32CopyedData/1024) * 100) / (m_u32CopyDataLen/1024);
        }
    }
#else
    if(m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_COPY_PLAY)
    {
        return (U16)m_u32TotalCopiedPercentage;
    }
    else
    {
        return 0;
    }

#endif
}

//******************************************************************************
/// Check the file is coping.
/// @return TRUE if copy file flag was set.
//******************************************************************************
BOOLEAN MApp_MPlayer_IsCopying(void)
{
    if ((m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_COPY_PLAY) == 0 )
        return 0;
    else
        return 1;
}

//******************************************************************************
/**
 * @brief       Query current selected copying file index
 * @remarks
 * @return      current selected  copying file index
 */
//******************************************************************************
U16 MApp_MPlayer_QueryCurrentSelectedCopyingFileIndex(void)
{
    return u16CurrentCopyIndex;
}
#endif

#if ENABLE_DELETE_SELECTED_FILES
//******************************************************************************
/// Delete a file.
/// About the meaning of eBegin, please refer to the figure 3-4. When there are 18 files in the current directory. The current page is page 1. Users want to set the 9th (FILE_06.JPG) file, can call the function as.
/// 1. MApp_MPlayer_DeleteFile(E_MPLAYER_INDEX_CURRENT_PAGE, 2) or
/// 2. MApp_MPlayer_DeleteFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, 8)
/// @param  eBegin     \b IN Specify set the base of file index is current directory or current page
/// @param  u16FileIdx \b IN Specify the file index offset.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_DeleteFile(enumMPlayerFileIndexBegin eBegin, U16 u16FileIdx)
{
    MPlayerFileInfo fileInfo;
    enumMPlayerIdx eMPlayerIdx;

    if(eBegin == E_MPLAYER_INDEX_CURRENT_PAGE)
    {
        u16FileIdx += m_u16CurPage1stFileIdx;
    }
    else if(eBegin != E_MPLAYER_INDEX_CURRENT_DIRECTORY)
    {
        return E_MPLAYER_RET_FAIL;
    }

    if(MApp_MPlayer_QueryCurrentFileSystemType() == FILE_SYSTEM_TYPE_NONE)
    {
        // check if file system not support
        return E_MPLAYER_RET_UNSUPPORT_FILESYSTEM;
    }

    if(MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,
                                  u16FileIdx,
                                  &fileInfo) != E_MPLAYER_RET_OK)
    {
        return E_MPLAYER_RET_FAIL;
    }

    if(fileInfo.eAttribute & E_MPLAYER_FILE_DIRECTORY)
    {   // Do not support directory delete.
        return E_MPLAYER_RET_UNSUPPORT;
    }

    // can't delete this file if it's being played
    for (eMPlayerIdx = E_MPLAYER_FOREGROUND_PLAYER; eMPlayerIdx < E_MPLAYER_MAX_CONCURRENT_PLAYER_NUM; eMPlayerIdx++)
    {
        if ( (m_eMediaType == m_MPlayerInfo[eMPlayerIdx].eMediaType)
          && (m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 & (0
                      #if ENABLE_MPLAYER_PHOTO
                        | E_MPLAYER_KNL_FLG1_PHOTO_PLAY
                      #endif  // #if ENABLE_MPLAYER_PHOTO
                      #if ENABLE_MPLAYER_MUSIC
                        | E_MPLAYER_KNL_FLG1_MUSIC_PLAY
                      #endif  // #if ENABLE_MPLAYER_MUSIC
                      #if ENABLE_MPLAYER_MOVIE
                        | E_MPLAYER_KNL_FLG1_MOVIE_PLAY
                      #endif  // #if ENABLE_MPLAYER_MOVIE
                      #if ENABLE_MPLAYER_TEXT
                        | E_MPLAYER_KNL_FLG1_TEXT_PLAY
                      #endif  // #if ENABLE_MPLAYER_TEXT
              )))
        {
            MPLAYER_DBG(printf("drv: %u, %u\n", m_MPlayerInfo[eMPlayerIdx].u16CurrentDrive, m_u16CurDriveIdx));

            if (m_MPlayerInfo[eMPlayerIdx].u16CurrentDrive == m_u16CurDriveIdx)
            {
                if (memcmp(&fileInfo.fileEntry, &m_MPlayerInfo[eMPlayerIdx].curPlayingFileEntry, sizeof(fileInfo.fileEntry)) == 0)
                {
                    return E_MPLAYER_RET_FAIL;
                }
            }
        }
    }

    // file, delete file from file system and play list
    if(MApp_FileBrowser_DeleteFileByFileEntry(&fileInfo.fileEntry) == TRUE)
    {
        if (fileInfo.eAttribute & E_MPLAYER_FILE_SELECT)
        {
            _MApp_MPlayer_RemoveFileFromPlayingList(TRUE);
        }

        // force to re-enum current directory because
        // change to dest directory
    #if (HIGH_SPEED_BROWSER)
        m_u16BufDirectoryDepth = MPLAYER_INVALID_INDEX;
    #endif
        _MApp_MPlayer_Browser_EnumCurDirectory();
        m_u16TotalPageNum = (m_u16TotalFileNum+m_u16FilesPerPage-1) /m_u16FilesPerPage;
        if (m_u16CurPageIdx >= m_u16TotalPageNum)
        {
            m_u16CurPageIdx = m_u16TotalPageNum - 1;
            m_u16CurPage1stFileIdx -= NUM_OF_PHOTO_FILES_PER_PAGE;
            m_u16CurFileIdx -= 1;
        }

        return E_MPLAYER_RET_OK;
    }
    else
    {
        return E_MPLAYER_RET_FAIL;
    }
}

enumMPlayerRet MApp_MPlayer_DeleteSelectedFile_Init(U16 u16DeletePlayListIndex, FileEntry *pfileEntry)
{
    if(pfileEntry == NULL)
    {
        return E_MPLAYER_RET_FAIL;
    }

#if ENABLE_SUBTITLE_COPY_AND_DELETE
    //This means , it needs to delete external subtitle file instead of movie,
    //so we have to get external subtitle file FileEntry.
    if(m_bDeletingExtSubtitleFile == TRUE)
    {
    #if ENABLE_EXTERNAL_SUBTITLE_FAST_SWITCHING
        *pfileEntry = m_aExtFileInfoList[m_u8CurCopyingDeletingExtSubtitleFileIdx].fileEntry;
    #else
        *pfileEntry = m_ExtFileInfo.fileEntry;
    #endif
        return E_MPLAYER_RET_OK;
    }
#endif

    MPlayerPlayListInfo *pstPlayListInfo;
    U32 u32XdataWindowBase;

    if(_MApp_MPlayer_GetPlayListAddressByMediaType(m_eMediaType, &u32XdataWindowBase)==FALSE)
    {
       return E_MPLAYER_RET_FAIL;
    }

    pstPlayListInfo = (MPlayerPlayListInfo *) (_PA2VA(u32XdataWindowBase));

    EN_FILE_SYSTEM_FORMAT enFileSystemFormat;
    enFileSystemFormat = msAPI_FCtrl_GetFileSystemFormatByDriveIndex(PLAY_LIST_DRIVE(u16DeletePlayListIndex));

    if(enFileSystemFormat == FILE_SYSTEM_FORMAT_UNKNOW)
    {
        //check if file system not support
        return E_MPLAYER_RET_UNSUPPORT_FILESYSTEM;
    }

    //printf("m_u16SelectedFileNum[m_eMediaType]=%d\n",m_u16SelectedFileNum[m_eMediaType]);
    //printf("u16DeletePlayListIndex=%d\n",u16DeletePlayListIndex);

    /*
    MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,
                                u16DeletePlayListIndex,
                                &fileInfo);
    if(fileInfo.eAttribute & E_MPLAYER_FILE_DIRECTORY)
    {
        // Do not support directory delete.
        return E_MPLAYER_RET_UNSUPPORT;
    }
    */
    enumMPlayerIdx eMPlayerIdx;

    // can't delete this file if it's being played
    for (eMPlayerIdx = E_MPLAYER_FOREGROUND_PLAYER; eMPlayerIdx < E_MPLAYER_MAX_CONCURRENT_PLAYER_NUM; eMPlayerIdx++)
    {
        if ( (m_eMediaType == m_MPlayerInfo[eMPlayerIdx].eMediaType)
          && (m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 & (0
                      #if ENABLE_MPLAYER_PHOTO
                        | E_MPLAYER_KNL_FLG1_PHOTO_PLAY
                      #endif  // #if ENABLE_MPLAYER_PHOTO
                      #if ENABLE_MPLAYER_MUSIC
                        | E_MPLAYER_KNL_FLG1_MUSIC_PLAY
                      #endif  // #if ENABLE_MPLAYER_MUSIC
                      #if ENABLE_MPLAYER_MOVIE
                        | E_MPLAYER_KNL_FLG1_MOVIE_PLAY
                      #endif  // #if ENABLE_MPLAYER_MOVIE
                      #if ENABLE_MPLAYER_TEXT
                        | E_MPLAYER_KNL_FLG1_TEXT_PLAY
                      #endif  // #if ENABLE_MPLAYER_TEXT
              )))
        {
            MPLAYER_DBG(printf("drv: %u, %u\n", m_MPlayerInfo[eMPlayerIdx].u16CurrentDrive, m_u16CurDriveIdx));

            if (m_MPlayerInfo[eMPlayerIdx].u16CurrentDrive == m_u16CurDriveIdx)
            {
                if (memcmp(&PLAY_LIST_FILE_ENTRY(u16DeletePlayListIndex), &m_MPlayerInfo[eMPlayerIdx].curPlayingFileEntry, sizeof(FileEntry)) == 0)
                {
                    //file is being played.
                    return E_MPLAYER_RET_FAIL;
                }
            }
        }
    }

    *pfileEntry = PLAY_LIST_FILE_ENTRY(u16DeletePlayListIndex);

#if ENABLE_SUBTITLE_COPY_AND_DELETE
    //Before delete next movie file, we have to find the external subtitle file number.
    m_u8CurCopyingDeletingExtSubtitleFileIdx = 0;
#if STORE_SUBTITLE_ENTRY_TO_SUBTITLE_BUFFER
    //Search subtitle file in Subtitle file buffer. PS:Search in USB is slow , and search in Subtitle file buffer is fast.
    m_u8CopyDeleteExtSubtitleFileNum = _MApp_MPlayer_ScanExtSubtitleFileNumByMovieFileEntry(pfileEntry, FALSE);
#else
    //Search subtitle file in USB. PS:Search in USB is slow , and search in Subtitle file buffer is fast.
    m_u8CopyDeleteExtSubtitleFileNum = _MApp_MPlayer_ScanExtSubtitleFileNumByMovieFileEntry(pfileEntry, TRUE);
#endif
#endif

    return E_MPLAYER_RET_OK;
}

enumMPlayerRet MApp_MPlayer_BeginDeleteSelectedFiles(void)
{
    if(NUM_OF_MAX_SELECTED_FILE < m_u16SelectedFileNum[m_eMediaType]
    ||                        0 == m_u16SelectedFileNum[m_eMediaType])
    {
        //no selected file or wrong selected file number.
        return E_MPLAYER_RET_FAIL;
    }

    MPlayerDrive DriveInfo;
    memset(&DriveInfo,0,sizeof(MPlayerDrive));

    if(MApp_MPlayer_QueryPartitionIdxInDrive(m_u16CurDriveIdx, &DriveInfo)==0xFF)
    {
        return E_MPLAYER_RET_FAIL;
    }
    m_u8DeleteLun = DriveInfo.u8Lun;
    m_u16CurDeletePlaylistIdx = 0;
    m_u16DeleteCount = 0;
    m_u16TotalDeleteCount = m_u16SelectedFileNum[m_eMediaType];
    m_u32TotalDeletedPercentage = 0;
    m_bEndofDeleteFiles = FALSE;
    m_bUserBreakDelete = FALSE;
#if ENABLE_SUBTITLE_COPY_AND_DELETE
    m_bDeletingExtSubtitleFile = FALSE;
#endif

    m_eMPlayerKnlFlags |= (enumMPlayerKnlFlags)E_MPLAYER_KNL_FLG_DELETE_PLAY;
    m_eMPlayerKnlFlags |= (enumMPlayerKnlFlags)E_MPLAYER_KNL_FLG_DELETE_INIT;

    return E_MPLAYER_RET_OK;
}

static BOOLEAN _MApp_MPlayer_DeleteNext(void)
{
#if ENABLE_SUBTITLE_COPY_AND_DELETE
    if(m_bDeletingExtSubtitleFile)
    {
        m_u8CurCopyingDeletingExtSubtitleFileIdx++;
    }

    if(m_u8CurCopyingDeletingExtSubtitleFileIdx < m_u8CopyDeleteExtSubtitleFileNum)
    {
        //TRUE: means int needs to delete external subtitle file instead of next movie file.
        m_bDeletingExtSubtitleFile = TRUE;
    }
    else
    {
        //FALSE: means it needs to delete next movie file instead of external subtitle file.
        m_bDeletingExtSubtitleFile = FALSE;
    }

    if(m_bDeletingExtSubtitleFile == FALSE)
#endif
    {
        //no selected file or wrong selected file number.
        if(NUM_OF_MAX_SELECTED_FILE < m_u16SelectedFileNum[m_eMediaType])
        {
            return FALSE;
        }
        if(0 == m_u16SelectedFileNum[m_eMediaType])
        {
            m_bEndofDeleteFiles = TRUE;
            return FALSE;
        }
        //always delete 0th file in playlist
        m_u16CurDeletePlaylistIdx = 0;
    }

    m_eMPlayerKnlFlags |= (enumMPlayerKnlFlags)E_MPLAYER_KNL_FLG_DELETE_INIT;

    return TRUE;
}

BOOLEAN MApp_MPlayer_StopDelete(void)
{
    m_bUserBreakDelete = TRUE;

    return TRUE;
}

//******************************************************************************
/// Check the file is deleting.
/// @return TRUE if delete file flag was set.
//******************************************************************************
BOOLEAN MApp_MPlayer_IsDeleting(void)
{
    if ((m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_DELETE_PLAY) == 0 )
        return 0;
    else
        return 1;
}

//******************************************************************************
/**
 * @brief       Query current selected deleting file index
 * @remarks
 * @return      current selected  copying file index
 */
//******************************************************************************
U16 MApp_MPlayer_QueryCurrentSelectedDeletingFileIndex(void)
{
    return m_u16CurDeletePlaylistIdx;
}

//******************************************************************************
/// Read back the current complete percentage for deleting file.
/// @return 0~100: Indicate the complete percentage.
///         Other: Failed to get the status.
//******************************************************************************
U16 MApp_MPlayer_QueryDeleteFileStatus(void)
{
    if(m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_DELETE_PLAY)
    {
        return (U16)m_u32TotalDeletedPercentage;
    }
    else
    {
        return 0;
    }
}
#endif

//******************************************************************************
/// Rename a file.
/// About the meaning of eBegin, please refer to the figure 3-4. When there are 18 files in the current directory. The current page is page 1. Users want to set the 9th (FILE_06.JPG) file, can call the function as.
/// 1. MApp_MPlayer_DeleteFile(E_MPLAYER_INDEX_CURRENT_PAGE, 2, "FILE_new.JPG") or
/// 2. MApp_MPlayer_DeleteFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY, 8, "FILE_new.JPG")
/// @param  eBegin     \b IN Specify set the base of file index is current directory or current page
/// @param  u16FileIdx \b IN Specify the file index offset.
/// @param  pFileName \b IN Specify new file name.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_RenameFile(enumMPlayerFileIndexBegin eBegin, U16 u16FileIdx, U8 *pFileName)
{
    eBegin = eBegin;
    u16FileIdx = u16FileIdx;
    pFileName = pFileName;

    return E_MPLAYER_RET_FAIL;
}

//******************************************************************************
/// Record the path.
/// @param  bPop     \b IN Specify the user action. If bPop is true, user goes out of a directory. Otherwise, user goes into a directory
//******************************************************************************
BOOLEAN MApp_MPlayer_RecordPath(BOOLEAN bPop)
{
    U16 *pu16FullPath=NULL, *pu16EntryName=NULL, u16Index, u16i;

    pu16EntryName = (U16*)msAPI_Memory_Allocate(FILE_INFO_LONG_FILENAME_SIZE, BUF_ID_FILEBROWER);

    if(pu16EntryName==NULL)
    {
        __ASSERT(0);
        return FALSE;
    }

    if (bPop == TRUE)
    {
        u16Index = m_u16CurDirectoryDepth + 1;
        m_u16PathIndex[u16Index] = 0xffff;

        pu16FullPath = (U16 *)_PA2VA((((PATH_INFO_BUFFER_MEMORY_TYPE & MIU1) ? (PATH_INFO_BUFFER_ADR | MIU_INTERVAL) : (PATH_INFO_BUFFER_ADR))));
        pu16FullPath[m_u16PathIndex[m_u16CurDirectoryDepth]] = 0x0U;

    }
    else
    {
        MPlayerFileInfo stFileInfo;

        MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_PAGE,
                            MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_PAGE),
                            &stFileInfo);

        u16Index = m_u16CurDirectoryDepth - 1;

        pu16FullPath = (U16 *)_PA2VA((((PATH_INFO_BUFFER_MEMORY_TYPE & MIU1) ? (PATH_INFO_BUFFER_ADR | MIU_INTERVAL) : (PATH_INFO_BUFFER_ADR))));
        if (u16Index == 0)
        {
            memset(m_u16PathIndex, 0xff, sizeof(m_u16PathIndex));
            memset(pu16FullPath, 0x0, PATH_INFO_BUFFER_LEN);
            pu16FullPath[0] = '\\';
            m_u16PathIndex[0] = 1;
        }

        pu16FullPath += m_u16PathIndex[u16Index];

        memcpy(pu16EntryName, stFileInfo.u8LongFileName, FILE_INFO_LONG_FILENAME_SIZE);
        for (u16i = 0; (u16i < FILE_INFO_LONG_FILENAME_SIZE) && (pu16EntryName[u16i] != 0x0U); u16i++)
        {
            pu16FullPath[u16i] = pu16EntryName[u16i];
        }

        if (u16i > 0)
        {
            pu16FullPath[u16i++] = '\\';
        }
        m_u16PathIndex[u16Index + 1] = m_u16PathIndex[u16Index] + u16i;
        pu16FullPath[u16i++] = 0x0U;
    }

    msAPI_Memory_Free(pu16EntryName,BUF_ID_FILEBROWER);

    return TRUE;
}

//******************************************************************************
/// Get Path info
/// @param  pu16Buffer     \b Out Specify the user buffer to put full path info
/// @param  u16Length     \b IN Specify the length of user buffer
/// @return  enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_GetFullPath(U16 *pu16Buffer, U16 u16Length)
{
    U16 u16Slash[NUM_OF_MAX_DIRECTORY_DEPTH];
    U16 *pu16Src, u16Len, u16i;

#ifndef _SHOWN_LONG_FILE_NAME_MAX_LEN
#define _SHOWN_LONG_FILE_NAME_MAX_LEN        22
#endif

    memset(pu16Buffer, 0, u16Length);
    memset(u16Slash, 0, sizeof(u16Slash));

    if (u16Length < (_SHOWN_LONG_FILE_NAME_MAX_LEN)*2)
        return E_MPLAYER_RET_FAIL;

    if (m_u16CurDirectoryDepth == 0)
        return E_MPLAYER_RET_OK;

    // calculate the total length of full path
    // step 1, split the path into tokens. The separator is '\'
    pu16Src = (U16 *)_PA2VA(((PATH_INFO_BUFFER_MEMORY_TYPE & MIU1) ? (PATH_INFO_BUFFER_ADR | MIU_INTERVAL) : (PATH_INFO_BUFFER_ADR)));
    for(u16i = 0, u16Len = 0;
        (*pu16Src != 0x0U) && (u16Len < (PATH_INFO_BUFFER_LEN /2) && (u16i < NUM_OF_MAX_DIRECTORY_DEPTH));
        u16Len++, pu16Src++)
    {
        if (*pu16Src == '\\')
        {
            u16Slash[u16i] = u16Len;
            u16i++;
        }
    }

    // step 2, copy path to buffer
    pu16Src = (U16 *)_PA2VA(((PATH_INFO_BUFFER_MEMORY_TYPE & MIU1) ? (PATH_INFO_BUFFER_ADR | MIU_INTERVAL) : (PATH_INFO_BUFFER_ADR)));
    if(m_u16CurDirectoryDepth == 1)
    {
        if(u16Slash[m_u16CurDirectoryDepth] <= _SHOWN_LONG_FILE_NAME_MAX_LEN)
        {
            memcpy(pu16Buffer, pu16Src, (u16Slash[m_u16CurDirectoryDepth])*2);
        }
        else
        {
            memcpy(pu16Buffer, pu16Src, (_SHOWN_LONG_FILE_NAME_MAX_LEN)*2);
            pu16Buffer[_SHOWN_LONG_FILE_NAME_MAX_LEN-1] = 0x2026U;
            pu16Buffer[_SHOWN_LONG_FILE_NAME_MAX_LEN] = '\\';
        }
    }
    else
    {
        u16Length = _SHOWN_LONG_FILE_NAME_MAX_LEN;
        for(u16i=0;u16i<m_u16CurDirectoryDepth;u16i++)
        {
            if(u16i)
            {
                u16Length = _SHOWN_LONG_FILE_NAME_MAX_LEN-2;
            }

            if((u16Slash[m_u16CurDirectoryDepth]-u16Slash[u16i]) <= u16Length)
            {
                break;
            }
        }

        if(u16i == 0)
        {
            memcpy(pu16Buffer, &pu16Src[u16Slash[u16i]], (u16Slash[m_u16CurDirectoryDepth])*2);
        }
        else
        {
            memcpy(&pu16Buffer[2], &pu16Src[u16Slash[u16i]], (_SHOWN_LONG_FILE_NAME_MAX_LEN-2)*2);
            if(u16i == m_u16CurDirectoryDepth)
            {
                pu16Buffer[_SHOWN_LONG_FILE_NAME_MAX_LEN-1] = 0x2026U;
                pu16Buffer[_SHOWN_LONG_FILE_NAME_MAX_LEN] = '\\';
            }
            pu16Buffer[0] = '\\';
            pu16Buffer[1] = 0x2026U;
        }
    }

    return E_MPLAYER_RET_OK;
}


//******************************************************************************
/// Enter the specific directory.
/// @param  eBegin     \b IN Specify set the base of file index is current directory or current page
/// @param  u16Idx \b IN Specify the file index offset.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_EnterDirectory(enumMPlayerFileIndexBegin eBegin, U16 u16Idx)
{
    DirEntryStruct * pCurrentDirEntry;     //global current dir entry
	
#ifdef ENABLE_PTP
    if (MApp_PTP_DeviceInUse())
    {
        return MApp_MPlayer_PTP_EnterDirectory(eBegin, u16Idx);
    }
#endif
	
    if(eBegin == E_MPLAYER_INDEX_CURRENT_PAGE)
    {
        u16Idx += m_u16CurPage1stFileIdx;
    }
    else if(eBegin != E_MPLAYER_INDEX_CURRENT_DIRECTORY)
    {
        return E_MPLAYER_RET_FAIL;
    }

    if(u16Idx >= m_u16TotalFileNum)
    {
        return E_MPLAYER_RET_FAIL;
    }

    m_u16CurFileIdx = u16Idx;
	if(1 != MApp_MPlayer_QueryTotalDriveNum() && 0 < MApp_MPlayer_QueryDirectoryDepth()){
		u16Idx = u16Idx + 1;
	}
#if (ENABLE_MPLAYER_SORT)
    u16Idx = _MApp_MPlayer_LookupPhysicalIndex(u16Idx);
#endif

    _MApp_MPlayer_Browser_FirstEntry();
	if(1 != MApp_MPlayer_QueryTotalDriveNum()){
		if(!_MApp_MPlayer_Browser_FindNextDirectory(u16Idx))
		{
			return E_MPLAYER_RET_FAIL;
		}
	}else{
		if(!_MApp_MPlayer_Browser_FindNextDirectory(u16Idx+1))
		{
			return E_MPLAYER_RET_FAIL;
		}
	}
	printf("MApp_MPlayer_QueryTotalDriveNum 1 ---- \n");
    pCurrentDirEntry = MApp_FileBrowser_GetCurrentDirEntry();

    //remove klocwork warning message
    if(pCurrentDirEntry == NULL)
    {
        __ASSERT(0);
        return E_MPLAYER_RET_FAIL;
    }

    if((strncmp((char*)pCurrentDirEntry->ps8DirEntryName, ".       ", 8) != 0) ||
       (strncmp((char*)pCurrentDirEntry->ps8DirEntryExtName, "   ", 3) != 0))
    {
        BOOLEAN bPop = FALSE;
		/*U16 u16BackupDirectory;
		if(1 != MApp_MPlayer_QueryTotalDriveNum()){
			if( 0 < MApp_MPlayer_QueryDirectoryDepth()){
				u16BackupDirectory = m_u16CurDirectory[m_u16CurDirectoryDepth-2];
			}else{
				u16BackupDirectory = m_u16CurDirectory[m_u16CurDirectoryDepth-1];
			}
		}else{
			u16BackupDirectory = m_u16CurDirectory[m_u16CurDirectoryDepth-2];
		}
    #if ENABLE_MPLAYER_SORT
        U16 u16BackupPhyDirectory = m_u16CurDirectoryPhy[m_u16CurDirectoryDepth -2	];
    #endif
	*/
        if((strncmp((char*)pCurrentDirEntry->ps8DirEntryName, "..      ", 8) == 0) &&
           (strncmp((char*)pCurrentDirEntry->ps8DirEntryExtName, "   ", 3) == 0))
        {
            m_u16CurDirectoryDepth--;
            m_u16CurDirectory[m_u16CurDirectoryDepth] = MPLAYER_INVALID_INDEX;
#if (ENABLE_MPLAYER_SORT)
            m_u16CurDirectoryPhy[m_u16CurDirectoryDepth] = MPLAYER_INVALID_INDEX;
        #endif
            bPop = TRUE;
        }
        else
        {
            m_u16CurDirectoryDepth++;
        }

        if(m_u16CurDirectoryDepth <= NUM_OF_MAX_DIRECTORY_DEPTH)
        {
            if (!bPop)
            {
				if(1 != MApp_MPlayer_QueryTotalDriveNum()){
					m_u16CurDirectory[m_u16CurDirectoryDepth-1] = m_u16CurFileIdx;
				}else{
					m_u16CurDirectory[m_u16CurDirectoryDepth-2] = m_u16CurFileIdx;
				}
            #if (ENABLE_MPLAYER_SORT)
                m_u16CurDirectoryPhy[m_u16CurDirectoryDepth-2] = _MApp_MPlayer_LookupPhysicalIndex(m_u16CurFileIdx);
            #endif
            }

            if(pCurrentDirEntry->u8DirEntryAttrib & ATTRIB_DIRECTORY)
            {
                MApp_MPlayer_RecordPath(bPop);
                MApp_FileBrowser_EnterDirectory(0);
            }
            m_u16DirectoryNum[m_u16CurDirectoryDepth] = 0;
            m_u16CurFileIdx = 0;
        #if (ENABLE_SELECT_FILE_ACROSS_DIRECTORY == 0)
            //In BGM mode or Copy mode no need clear playlist.
            if( m_bIsCopyMode == FALSE
        #if PLAYLIST_BGM
            &&  m_bBGMPlaylistInit == FALSE
        #endif
            )
            {
                memset(m_u16SelectedFileNum, 0, sizeof(m_u16SelectedFileNum));
            }
        #endif

            _MApp_MPlayer_Browser_EnumCurDirectory();

            m_u16CurPage1stFileIdx = 0;
            m_u16CurPageIdx =0;
            if(m_u16TotalFileNum && m_u16FilesPerPage>0)
            {
                m_u16TotalPageNum = (m_u16TotalFileNum+m_u16FilesPerPage-1) / m_u16FilesPerPage;
            }
            else
            {
                return E_MPLAYER_RET_FAIL;
            }

            return E_MPLAYER_RET_OK;
        }
        else
        {
            m_u16CurDirectoryDepth = NUM_OF_MAX_DIRECTORY_DEPTH;
        }
    }

    return E_MPLAYER_RET_FAIL;
}

//******************************************************************************
/// Change to the next page for file browser.
/// Please refer to the figure 3-5. When the current page is page 1,
/// the current page will change to page 2 after calling MApp_MPlayer_NextPage.
/// Users have to notice that, the OSD and UI need to control by users.
/// Media player only manage the files in the current directory.
/// For example, users need to call MApp_MPlayer_SetCurrentFile to tell
/// media player.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_NextPage(void)
{
    if((m_u16CurPageIdx+1) < m_u16TotalPageNum)
    {
        m_u16CurPageIdx++;
        if(m_u16FilesPerPage)
        {
            m_u16CurPage1stFileIdx += m_u16FilesPerPage;
            return E_MPLAYER_RET_OK;
        }
    }
    return E_MPLAYER_RET_FAIL;
}

//******************************************************************************
/// Change to the previous page for file browser.
/// Please refer to the description of MApp_MPlayer_NextPage to know the detail.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_PrevPage(void)
{
    if(m_u16CurPageIdx >= 1)
    {
        m_u16CurPageIdx--;
        if(m_u16FilesPerPage)
        {
            m_u16CurPage1stFileIdx -= m_u16FilesPerPage;
            return E_MPLAYER_RET_OK;
        }
    }
    return E_MPLAYER_RET_FAIL;
}

//******************************************************************************
/// Users can change the file browser pages directly.
/// @param  u16PageIdx \b IN Specify the current page index.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_SetCurrentPageIndex(U16 u16PageIdx)
{
    if(u16PageIdx < m_u16TotalPageNum)
    {
        m_u16CurPageIdx = u16PageIdx;
        m_u16CurPage1stFileIdx = u16PageIdx * m_u16FilesPerPage;

    #if (THUMBNAIL_SHOW_DIRECTORY == 0)
        if(m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_THUMBNAIL_MODE)
        {
            m_u16CurPage1stFileIdx += m_u16DirectoryNum[m_u16CurDirectoryDepth];
        }
    #endif
        return E_MPLAYER_RET_OK;
    }
    return E_MPLAYER_RET_FAIL;
}

#if ENABLE_MPLAYER_PHOTO
//******************************************************************************
/// Begin the photo preview.
/// It will call MApp_UiMPlayer_Notify when complete the preview.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_PhotoBeginPreview(void)
{
    MPlayerFileInfo fileInfo;
    memset(&fileInfo, 0, sizeof(MPlayerFileInfo));

    m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType = E_MPLAYER_SUBTYPE_INVALID;

#if (THUMBNAIL_PRIORITY_HIGHER_PREVIEW)
    if(m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_THUMBNAIL)
    {
        return E_MPLAYER_RET_FAIL;
    }
#endif

    if((m_eMediaType == E_MPLAYER_TYPE_PHOTO) &&
       (m_ePhotoPreviewState == E_PHOTO_PREVIEW_NONE))
    {
        if(MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,m_u16CurFileIdx,&fileInfo) == E_MPLAYER_RET_OK)
        {
            if(!(fileInfo.eAttribute & E_MPLAYER_FILE_DIRECTORY))
            {
    //            msAPI_Scaler_SetBlueScreen(TRUE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    //            MApi_XC_GenerateBlackVideo( ENABLE, MAIN_WINDOW );

                m_u32PreviewTimer = msAPI_Timer_GetTime0();
                m_ePhotoPreviewState = E_PHOTO_PREVIEW_TIMER_ENABLE;
                MApp_Photo_Display_SetViewWin(PHOTO_PREVIEW_X, PHOTO_PREVIEW_Y, PHOTO_PREVIEW_WIDTH, PHOTO_PREVIEW_HEIGHT);
                return E_MPLAYER_RET_OK;
            }
        }
    }

    return E_MPLAYER_RET_FAIL;
}
#endif  // #if ENABLE_MPLAYER_PHOTO

#if ENABLE_MPLAYER_MUSIC
//******************************************************************************
/// Begin the music preview.
/// It will call MApp_UiMPlayer_Notify when complete the preview.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_MusicBeginPreview(void)
{

    MPlayerFileInfo fileInfo;
    memset(&fileInfo, 0, sizeof(MPlayerFileInfo));
/*
#if (THUMBNAIL_PRIORITY_HIGHER_PREVIEW)
    if(m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_THUMBNAIL)
    {
        return E_MPLAYER_RET_FAIL;
    }
#endif
*/
    if((m_eMediaType == E_MPLAYER_TYPE_MUSIC) &&
       (m_eMusicPreviewState == E_MUSIC_PREVIEW_NONE))
    {
        if(MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,m_u16CurFileIdx,&fileInfo) == E_MPLAYER_RET_OK)
        {
            if(!(fileInfo.eAttribute & E_MPLAYER_FILE_DIRECTORY))
            {
    //            msAPI_Scaler_SetBlueScreen(TRUE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    //            MApi_XC_GenerateBlackVideo( ENABLE, MAIN_WINDOW );

                m_u32PreviewTimer = msAPI_Timer_GetTime0();
                m_eMusicPreviewState = E_MUSIC_PREVIEW_TIMER_ENABLE;
                return E_MPLAYER_RET_OK;
            }
        }
    }

    return E_MPLAYER_RET_FAIL;
}
#endif  // #if ENABLE_MPLAYER_MUSIC

#if ENABLE_MPLAYER_MOVIE
//******************************************************************************
/// Begin the movie preview.
/// It will call MApp_UiMPlayer_Notify when complete the preview.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_MovieBeginPreview(void)
{
    MPlayerFileInfo fileInfo;
    memset(&fileInfo, 0, sizeof(MPlayerFileInfo));

    if((m_eMediaType == E_MPLAYER_TYPE_MOVIE) &&
       (m_eMoviePreviewState == E_MOVIE_PREVIEW_NONE))
    {
        if(MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,m_u16CurFileIdx,&fileInfo) == E_MPLAYER_RET_OK)
        {
            if(!(fileInfo.eAttribute & E_MPLAYER_FILE_DIRECTORY))
            {
    //            msAPI_Scaler_SetBlueScreen(TRUE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    //            MApi_XC_GenerateBlackVideo( ENABLE, MAIN_WINDOW );

                m_u32PreviewTimer = msAPI_Timer_GetTime0();
                m_eMoviePreviewState = E_MOVIE_PREVIEW_TIMER_ENABLE;
                return E_MPLAYER_RET_OK;
            }
        }
    }
    return E_MPLAYER_RET_FAIL;
}
#endif  // #if ENABLE_MPLAYER_MOVIE

#if ENABLE_MPLAYER_TEXT
//******************************************************************************
/// Begin the text preview.
/// It will call MApp_UiMPlayer_Notify when complete the preview.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_TextBeginPreview(void)
{
    MPlayerFileInfo fileInfo;
    memset(&fileInfo, 0, sizeof(MPlayerFileInfo));

    if((m_eMediaType == E_MPLAYER_TYPE_TEXT) &&
       (m_eTextPreviewState == E_TEXT_PREVIEW_NONE))
    {
        if(MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,m_u16CurFileIdx,&fileInfo) == E_MPLAYER_RET_OK)
        {
            if(!(fileInfo.eAttribute & E_MPLAYER_FILE_DIRECTORY))
            {
                m_u32PreviewTimer = msAPI_Timer_GetTime0();
                m_eTextPreviewState = E_TEXT_PREVIEW_TIMER_ENABLE;
                return E_MPLAYER_RET_OK;
            }
        }
    }
    return E_MPLAYER_RET_FAIL;
}
#endif  // #if ENABLE_MPLAYER_TEXT

//******************************************************************************
/// Begin the current media file preview.
/// It will call MApp_UiMPlayer_Notify when complete the preview.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_BeginPreview(void)
{
    MPlayerFileInfo fileInfo;
    memset(&fileInfo, 0, sizeof(MPlayerFileInfo));

#if ENABLE_MPLAYER_PLUGIN
    if(m_eMediaType == E_MPLAYER_TYPE_PLUGIN)
    {
        return E_MPLAYER_RET_FAIL;
    }
#endif //#if ENABLE_MPLAYER_PLUGIN

    if(MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,m_u16CurFileIdx,&fileInfo) == E_MPLAYER_RET_OK)
    {
        if(!(fileInfo.eAttribute & E_MPLAYER_FILE_DIRECTORY))
        {
            if(m_eMediaType == E_MPLAYER_TYPE_MUSIC &&
                m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_MUSIC_PLAY)
            {// If BGM is playing, do not allow PREVIEW action.
                return E_MPLAYER_RET_FAIL;
            }

            _MApp_Mplayer_InitializeCoProcessor();

            switch(m_eMediaType)
            {
            #if ENABLE_MPLAYER_PHOTO
                case E_MPLAYER_TYPE_PHOTO:
                    return(MApp_MPlayer_PhotoBeginPreview());
            #endif

            #if ENABLE_MPLAYER_MUSIC
                case E_MPLAYER_TYPE_MUSIC:
                    return(MApp_MPlayer_MusicBeginPreview());
            #endif

            #if ENABLE_MPLAYER_MOVIE
                case E_MPLAYER_TYPE_MOVIE:
                    if (MApp_MPlayer_IsMusicPlaying())
                    {
                        MApp_MPlayer_StopMusic();
                    }
                    return(MApp_MPlayer_MovieBeginPreview());
            #endif  // #if ENABLE_MPLAYER_MOVIE

            #if ENABLE_MPLAYER_TEXT
                case E_MPLAYER_TYPE_TEXT:
                    return(MApp_MPlayer_TextBeginPreview());
            #endif  // #if ENABLE_MPLAYER_TEXT

                default:
                    break;
            }
        }
    }
    return E_MPLAYER_RET_FAIL;
}

#if ENABLE_MPLAYER_PHOTO
//******************************************************************************
/// Stop the photo preview.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_PhotoStopPreview(void)
{
    if(m_ePhotoPreviewState != E_PHOTO_PREVIEW_TIMER_ENABLE)
    {
        MApp_Photo_Display_Stop();
    }

    if(m_ePhotoPreviewState == E_PHOTO_PREVIEW_RUNNING)
    {
        MApp_Photo_Stop();
    }

    //Disable MVOP, when stop preview
    MDrv_MVOP_Enable( FALSE );
    m_ePhotoPreviewState = E_PHOTO_PREVIEW_NONE;

#if (ENABLE_MIU_1 == ENABLE)
    //switch MIU to 1
    MDrv_MVOP_MiuSwitch(1);
#endif

    return E_MPLAYER_RET_OK;
}
#endif  // #if ENABLE_MPLAYER_PHOTO

#if ENABLE_MPLAYER_MUSIC
//******************************************************************************
/// Stop the music preview.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_MusicStopPreview(void)
{
    if(m_eMusicPreviewState == E_MUSIC_PREVIEW_RUNNING)
    {
    #if ENABLE_EMBEDDED_PHOTO_DISPLAY
        //Not use STOPTHUMBNAIL , Because we need the state in WAIT
        MApp_MPlayer_ClearEmbeddedPhoto();
    #endif
    #if (ENABLE_WMA)
        MApp_WMA_Stop();
    #endif
        MApp_Music_Stop();
    }
    m_eMusicPreviewState = E_MUSIC_PREVIEW_NONE;

    return E_MPLAYER_RET_OK;
}
#endif  // #if ENABLE_MPLAYER_MUSIC

#if ENABLE_MPLAYER_MOVIE
//******************************************************************************
/// Stop the movie preview.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_MovieStopPreview(void)
{

#if DYNSCALING
    XC_DynamicScaling_Info stDS_Info;
    memset(&stDS_Info, 0, sizeof(XC_DynamicScaling_Info));
    stDS_Info.bOP_DS_On = FALSE;
    stDS_Info.bIPS_DS_On = FALSE;
    stDS_Info.bIPM_DS_On = FALSE;
    if(TRUE != MApi_XC_SetDynamicScaling(&stDS_Info, sizeof(XC_DynamicScaling_Info), MAIN_WINDOW))
    {
        MPLAYER_DBG(printf("Set DS error\n"));
    }
    MDrv_PQ_SetDS_OnOFF(PQ_MAIN_WINDOW,  FALSE);
#endif

    if(m_eMoviePreviewState != E_MOVIE_PREVIEW_TIMER_ENABLE)
    {
        msAPI_Scaler_SetBlueScreen(TRUE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
        MApi_XC_GenerateBlackVideo( ENABLE, MAIN_WINDOW );
        MApp_VDPlayer_Stop();
    }

    if(m_eMoviePreviewState == E_MOVIE_PREVIEW_RUNNING || m_eMoviePreviewState == E_MOVIE_PREVIEW_1ST_FRAME_DECODE || m_eMoviePreviewState == E_MOVIE_PREVIEW_1ST_FRAME_PREDECODE)
    {
        msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
      #if ENABLE_DVD
        if (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_DVD)
        {
            MApp_VDPlayer_DVD_Stop();
        }
        else
      #endif
        {
            MApp_VDPlayer_Stop();
        }

      #if (ENABLE_SUBTITLE_DMP)
        if(m_u8ExternalSubtitleFileHandle != FCTRL_INVALID_FILE_HANDLE)
        {
            msAPI_FCtrl_FileClose(m_u8ExternalSubtitleFileHandle);
            m_u8ExternalSubtitleFileHandle = FCTRL_INVALID_FILE_HANDLE;

          #if (ENABLE_INTERNAL_BMP_SUBTITLE || ENABLE_INTERNAL_TEXT_SUBTITLE)
            msAPI_MpegSP_Dinit();
          #endif
        }
      #endif //#if (ENABLE_SUBTITLE_DMP)

        MApp_VDPlayer_StopPreview();
        m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType = E_MPLAYER_SUBTYPE_INVALID;
    }

#if (ENABLE_MOVIE_PREVIEW_ALL_AND_1ST_FRAME || ENABLE_MOVIE_PREVIEW_1ST_FRAME)
    if(m_eMoviePreviewState == E_MOVIE_PREVIEW_1ST_FRAME_DECODE || m_eMoviePreviewState == E_MOVIE_PREVIEW_1ST_FRAME_PREDECODE)
    {
        if(bMute)
        {
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
        }
        else
        {
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
        }
    }
#endif

#if((MEMORY_MAP <= MMAP_32MB)) // 32M
  #if( defined(SCALER_DNR_BUF_SDMM_ADR) )
    //printf("Set FB = SDMM %X %X\n", SCALER_DNR_BUF_SDMM_ADR, SCALER_DNR_BUF_SDMM_LEN );
    MApi_XC_SetFrameBufferAddress( SCALER_DNR_BUF_SDMM_ADR, SCALER_DNR_BUF_SDMM_LEN, MAIN_WINDOW);
  #endif
#else
  #ifdef SCALER_DNR_BUF_PREV_ADR
    MApi_XC_SetFrameBufferAddress(((SCALER_DNR_BUF_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_ADR)), SCALER_DNR_BUF_LEN, MAIN_WINDOW);
    //printf("Set FB = DNR %X %X\n", ((SCALER_DNR_BUF_MEMORY_TYPE & MIU1) ? (SCALER_DNR_BUF_ADR | MIU_INTERVAL) : (SCALER_DNR_BUF_ADR)), SCALER_DNR_BUF_LEN);
  #endif
#endif

    m_eMoviePreviewState = E_MOVIE_PREVIEW_NONE;

    return E_MPLAYER_RET_OK;
}
#endif  // #if ENABLE_MPLAYER_MOVIE

#if ENABLE_MPLAYER_TEXT
//******************************************************************************
/// Stop the text preview.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_TextStopPreview(void)
{
    if(m_eTextPreviewState != E_TEXT_PREVIEW_NONE)
    {
        TEXT_FileClose();
        m_eTextPreviewState = E_TEXT_PREVIEW_NONE;
    }
    return E_MPLAYER_RET_OK;
}
#endif  // #if ENABLE_MPLAYER_TEXT

void MApp_MPlayer_ResetPreviewTimer(void)
{
    m_u32PreviewTimer = msAPI_Timer_GetTime0();
}

#if ENABLE_EMBEDDED_PHOTO_DISPLAY
//******************************************************************************
/// Clear the embedded photo and set black screen.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_ClearEmbeddedPhoto(void)
{
    if(m_eMediaType == E_MPLAYER_TYPE_MUSIC)
    {
        if(m_eEmbeddedPhotoState != E_EMBEDDED_PHOTO_EXIT)
        {
            if(m_eEmbeddedPhotoState != E_EMBEDDED_PHOTO_DONE)
            {
                MApp_Photo_Stop();
            }
            MApp_Photo_Display_Stop();
        }
        m_eEmbeddedPhotoState = E_EMBEDDED_PHOTO_WAIT;
        m_u16PreFileIdx = INVALID_FILE_INDEX;

        MApp_MPlayer_EmbeddedPhotoIO_Close();

        return E_MPLAYER_RET_OK;
    }

    return E_MPLAYER_RET_FAIL;
}

//******************************************************************************
/// Stop the embedded photo and set black screen.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_StopEmbeddedPhoto(void)
{
    if(m_eMediaType == E_MPLAYER_TYPE_MUSIC)
    {
        if(MApp_MPlayer_IsMusicPlaying() || m_eMusicPreviewState != E_MUSIC_PREVIEW_NONE)
        {
            if(m_eEmbeddedPhotoState != E_EMBEDDED_PHOTO_DONE)
            {
                MApp_Photo_Stop();
            }
            MApp_Photo_Display_Stop();

            m_eEmbeddedPhotoState = E_EMBEDDED_PHOTO_EXIT;

            MApp_MPlayer_EmbeddedPhotoIO_Close();
        }

        return E_MPLAYER_RET_OK;
    }

    return E_MPLAYER_RET_FAIL;
}

//******************************************************************************
/// Stop the embedded photo decode only.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_StopEmbeddedPhotoDecode(void)
{
    if(m_eMediaType == E_MPLAYER_TYPE_MUSIC)
    {
        MApp_Photo_Stop();
        MApp_MPlayer_EmbeddedPhotoIO_Close();

        return E_MPLAYER_RET_OK;
    }

    return E_MPLAYER_RET_FAIL;
}

//******************************************************************************
/// Resume the embedded photo.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_ResumeEmbeddedPhoto(void)
{
    m_eEmbeddedPhotoState = E_EMBEDDED_PHOTO_WAIT;
    m_u16PreFileIdx = INVALID_FILE_INDEX;

    return E_MPLAYER_RET_OK;
}
#endif  // #if ENABLE_EMBEDDED_PHOTO_DISPLAY

//******************************************************************************
/// Stop the current media file preview.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_StopPreview(void)
{
    if(MApp_MPlayer_QueryPreviewState(m_eMediaType)!= 0)
    {
        switch(m_eMediaType)
        {
        #if ENABLE_MPLAYER_PHOTO
            case E_MPLAYER_TYPE_PHOTO:
                return(MApp_MPlayer_PhotoStopPreview());
        #endif

        #if ENABLE_MPLAYER_MUSIC
            case E_MPLAYER_TYPE_MUSIC:
                return(MApp_MPlayer_MusicStopPreview());
        #endif

        #if ENABLE_MPLAYER_MOVIE
            case E_MPLAYER_TYPE_MOVIE:
                return(MApp_MPlayer_MovieStopPreview());
        #endif  // #if ENABLE_MPLAYER_MOVIE

        #if ENABLE_MPLAYER_TEXT
            case E_MPLAYER_TYPE_TEXT:
                return(MApp_MPlayer_TextStopPreview());
        #endif  // #if ENABLE_MPLAYER_TEXT

            default:
                break;
        }
    }
    return E_MPLAYER_RET_OK;
}

#if ENABLE_MPLAYER_PHOTO
//******************************************************************************
/// Enter thumbnail mode.
/// @param  pFBAttr \b IN Specify the GWIN buffer attributes.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_EnterThumbnailMode(GOP_GwinFBAttr *pFBAttr)
{
#if( ENABLE_MPLAYER_TEXT)
    if((m_eMediaType == E_MPLAYER_TYPE_TEXT))
    {
        return E_MPLAYER_RET_FAIL;
    }
#endif

#if ENABLE_MPLAYER_PHOTO
    MApp_MPlayer_PhotoStopPreview();
#endif
#if ENABLE_MPLAYER_MOVIE
    MApp_MPlayer_MovieStopPreview();
#endif
#if ENABLE_MPLAYER_MUSIC
    MApp_MPlayer_MusicStopPreview();
#endif
    m_eMPlayerKnlFlags |= E_MPLAYER_KNL_FLG_THUMBNAIL_MODE;
    m_u16FilesPerPage = NUM_OF_THUMBNAIL_FILES_PER_PAGE;
#if (THUMBNAIL_SHOW_DIRECTORY == 0)
    m_u16TotalPageNum = (m_u16TotalFileNum -
                         m_u16DirectoryNum[m_u16CurDirectoryDepth] +
                         m_u16FilesPerPage-1) / m_u16FilesPerPage;
    if(m_u16CurFileIdx > m_u16DirectoryNum[m_u16CurDirectoryDepth])
    {
        m_u16CurPageIdx = (m_u16CurFileIdx-m_u16DirectoryNum[m_u16CurDirectoryDepth]) / m_u16FilesPerPage;
    }
    else
    {
        m_u16CurPageIdx = 0;
    }
    m_u16CurPage1stFileIdx = m_u16CurPageIdx * m_u16FilesPerPage + m_u16DirectoryNum[m_u16CurDirectoryDepth];
#endif

#if 1//def ZUI
    m_u8ThumbQMax = 0;
#endif

    m_thumbnailFbAttr = *pFBAttr;

    return E_MPLAYER_RET_OK;
}

//******************************************************************************
/// Leave thumbnail mode.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_LeaveThumbnailMode(void)
{
#if ENABLE_MPLAYER_TEXT
    if((m_eMediaType == E_MPLAYER_TYPE_TEXT))
    {
        //printf("MApp_MPlayer_LeaveThumbnailMode: Failed!\n");
        return E_MPLAYER_RET_FAIL;
    }
#endif

    MApp_MPlayer_StopThumbnail();

    m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_THUMBNAIL_MODE;
    m_u16FilesPerPage = NUM_OF_PHOTO_FILES_PER_PAGE;

#if (THUMBNAIL_SHOW_DIRECTORY == 0)
    m_u16TotalPageNum = (m_u16TotalFileNum + m_u16FilesPerPage-1) / m_u16FilesPerPage;
    m_u16CurFileIdx += m_u16DirectoryNum[m_u16CurDirectoryDepth];
    m_u16CurPageIdx = m_u16CurFileIdx / m_u16FilesPerPage;
    m_u16CurPage1stFileIdx = m_u16CurPageIdx * m_u16FilesPerPage;
#endif

    return E_MPLAYER_RET_OK;
}

#if 1//def ZUI
//******************************************************************************
/// Begin to draw u8Idx thumbnail.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_DrawThumbnailByIdx(U8 u8Idx)
{
    if(((m_eMediaType != E_MPLAYER_TYPE_PHOTO)
#if ENABLE_MPLAYER_MOVIE
      &&(m_eMediaType != E_MPLAYER_TYPE_MOVIE)
#endif
      &&(m_eMediaType != E_MPLAYER_TYPE_MUSIC))||
       !(m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_THUMBNAIL_MODE) ||
       (m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_DECODE_N_THUMBNAIL))
    {
        if(m_u8ThumbQMax < THUMBNAIL_NUM_MAX)
        {
            m_au8ThumbQueue[m_u8ThumbQMax] = u8Idx;
            m_u8ThumbQMax++;
        }
        else
        {
            MPLAYER_DBG(printf("Error! Thumbnail queue overflow!\n"));
        }
            return E_MPLAYER_RET_FAIL;
    }

        m_au8ThumbQueue[m_u8ThumbQMax] = u8Idx;
        m_u8ThumbQMax++;
        m_u8ThumbnailNIdx = 0;
        m_eMPlayerKnlFlags |= E_MPLAYER_KNL_FLG_DECODE_N_THUMBNAIL;
        m_eMPlayerKnlFlags |= E_MPLAYER_KNL_FLG_THUMBNAIL_INIT;
        MApp_DMP_GetZUIFbAttr(&m_thumbnailFbAttr);
        //MApi_GOP_GWIN_EnableTransClr(GOPTRANSCLR_FMT0, FALSE);
        //MApi_GOP_GWIN_SetBlending(m_thumbnailFbAttr.gWinId, FALSE, 63);

    return E_MPLAYER_RET_OK;
}
#endif //#ifdef ZUI

//******************************************************************************
/// Begin to draw thumbnail.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_BeginThumbnail(void)
{
#if 0
    U8 u8StartPageIdx;
#endif
    if((m_eMediaType != E_MPLAYER_TYPE_PHOTO) ||
       !(m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_THUMBNAIL_MODE) ||
       (m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_THUMBNAIL))
    {
        return E_MPLAYER_RET_FAIL;
    }

    m_u8CurThumbnailDrawIdx = 0;
    m_eMPlayerKnlFlags |= E_MPLAYER_KNL_FLG_THUMBNAIL;
    m_eMPlayerKnlFlags |= E_MPLAYER_KNL_FLG_THUMBNAIL_INIT;
    //MApi_GOP_GWIN_EnableTransClr(GOPTRANSCLR_FMT0, FALSE);
    //MApi_GOP_GWIN_SetBlending(m_thumbnailFbAttr.gWinId, FALSE, 63);

    return E_MPLAYER_RET_OK;
}

//******************************************************************************
/// Stop to draw thumbnail.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_StopThumbnail(void)
{

    if(!(m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_THUMBNAIL_MODE))
    {
        //__ASSERT(0);
        return E_MPLAYER_RET_FAIL;
    }
#if ENABLE_MPLAYER_PHOTO
    if (m_eMediaType == E_MPLAYER_TYPE_PHOTO)
    {
        MApp_Photo_Stop();
    }
#endif
#if ENABLE_MPLAYER_MOVIE
    else if(m_eMediaType == E_MPLAYER_TYPE_MOVIE)
    {
        if (m_eMPlayerKnlFlags &(enumMPlayerKnlFlags)E_MPLAYER_KNL_FLG_DECODE_N_THUMBNAIL)
            MApp_VDPlayer_Stop();
        MApi_XC_GenerateBlackVideo(TRUE, MAIN_WINDOW);
    }
#endif
#if ENABLE_EMBEDDED_PHOTO_DISPLAY
    else if (m_eMediaType == E_MPLAYER_TYPE_MUSIC)
    {
        MApp_MPlayer_StopEmbeddedPhotoDecode();
    }
#endif

    m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_THUMBNAIL;
    MApi_GOP_GWIN_EnableTransClr(GOPTRANSCLR_FMT0, TRUE);

#if 1//def ZUI
    m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_DECODE_N_THUMBNAIL;
    m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_THUMBNAIL_INIT;
    m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_THUMBNAIL_DECODE;
    m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_THUMBNAIL_DONE;
    memset(m_au8ThumbQueue, 0, THUMBNAIL_NUM_MAX);
    m_u8ThumbQMax = 0;
    m_u8ThumbnailNIdx = 0;
#endif

    return E_MPLAYER_RET_OK;
}
#endif  // #if ENABLE_MPLAYER_PHOTO

#if (ENABLE_MPLAYER_MOVIE && ENABLE_SUBTITLE_DMP)
//******************************************************************************
/// Enable media player kernel to search the dedicated SRT subtitle file,
/// parse it. Call MApp_UiMPlayer_Notify when there are subtitle events
/// generated.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_EnableSubtitle(void)
{
    if(E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL & m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1)
    {
#if (ENABLE_SUBTITLE_SUBIDX)
        if(m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SUBIDX)
        {
            _MApp_MPlayer_SetMpegSubtitle();
        }
#endif
    }
    else
    {
        if((m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_SUBTITLE_TEXT) == 0)
        {
#if (ENABLE_INTERNAL_BMP_SUBTITLE==1)
            if(u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP)
            {
                U32 u32CurTime = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CUR_TIME);
                msAPI_MpegSP_Enable_Subtitle_Gwin(u32CurTime);
            }
#endif
        }
    }
    m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_SUBTITLE_ENABLE;

    return E_MPLAYER_RET_OK;
}

//******************************************************************************
/// Call media player kernel to stop SRT subtitle parsing.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_DisableSubtitle(void)
{
    _MApp_MPlayer_HideSubtitle();
    m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_SUBTITLE_ENABLE;

    return E_MPLAYER_RET_OK;
}

//******************************************************************************
/// Show or hide the subtitle, it works for SUB/IDX external subtitle
/// and TS internal subtitle only. It worked only after movie playback.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_ShowSubtitle(BOOLEAN bShow)
{
#if (ENABLE_SUBTITLE_SUBIDX)
    if(((m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_SUBTITLE_ENABLE) &&
        (m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SUBIDX)) ||
       (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_TS))
#else
    if(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_TS)
#endif
    {
        if(bShow)
        {
            if(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_HIDE_SUBTITLE)
            {
                m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_HIDE_SUBTITLE;

#if (ENABLE_SUBTITLE_SUBIDX)
                _MApp_MPlayer_SetMpegSubtitle();
#endif
#if (ENABLE_INTERNAL_BMP_SUBTITLE || ENABLE_EXTERNAL_BMP_SUBTITLE)
                msAPI_MpegSP_Show();
#endif
            }
        }
        else
        {
            m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_HIDE_SUBTITLE;
#if (ENABLE_INTERNAL_BMP_SUBTITLE || ENABLE_EXTERNAL_BMP_SUBTITLE)
            msAPI_MpegSP_Unshow();
#endif
        }
        return E_MPLAYER_RET_OK;
    }

    return E_MPLAYER_RET_FAIL;
}
#endif  // #if (ENABLE_MPLAYER_MOVIE && ENABLE_SUBTITLE_DMP)

#if ENABLE_MPLAYER_MUSIC
//******************************************************************************
/// Enable media player kernel to search the dedicated LRC lyric file,
/// parse it. Call MApp_UiMPlayer_Notify when there are lyric events generated.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_EnableLRCLyric(void)
{
    m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_LYRIC_ENABLE;
    return E_MPLAYER_RET_OK;
}

//******************************************************************************
/// Call media player kernel to stop LRC lyric.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_DisableLRCLyric(void)
{
    m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_LYRIC_ENABLE;
    return E_MPLAYER_RET_OK;
}
#endif  // #if ENABLE_MPLAYER_MUSIC

//******************************************************************************
/// Init the media player repeat mode.
/// @param  eMode \b IN Specify the play mode is repeat one file, repeat all file, random repeat or repeat none.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_InitRepeatMode(enumMPlayerRepeatMode eMode)
{
    if(eMode == E_MPLAYER_REPEAT_NONE
    || eMode == E_MPLAYER_REPEAT_1
    || eMode == E_MPLAYER_REPEAT_ALL)
    {
    #if ENABLE_BGM
        m_eRepeatMode[E_MPLAYER_BACKGROUND_PLAYER] = eMode;
        m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eRepeatMode = eMode;
    #endif
        m_eRepeatMode[E_MPLAYER_FOREGROUND_PLAYER] = eMode;
        m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eRepeatMode = eMode;

        return E_MPLAYER_RET_OK;
    }
    else
    {
        return E_MPLAYER_RET_FAIL;
    }
}

//******************************************************************************
/// Set the media player repeat mode.
/// @param  eMode \b IN Specify the play mode is repeat one file, repeat all file, random repeat or repeat none.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_SetRepeatMode(enumMPlayerRepeatMode eMode)
{
    if(eMode == E_MPLAYER_REPEAT_NONE
    || eMode == E_MPLAYER_REPEAT_1
    || eMode == E_MPLAYER_REPEAT_ALL)
    {
    #if ENABLE_BGM
        if(m_eMediaType == E_MPLAYER_TYPE_MUSIC)
        {
            m_eRepeatMode[E_MPLAYER_BACKGROUND_PLAYER] = eMode;
            m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eRepeatMode = eMode;
        }
        else
    #endif
        {
            m_eRepeatMode[E_MPLAYER_FOREGROUND_PLAYER] = eMode;
            m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eRepeatMode = eMode;
            if(m_eMediaType == E_MPLAYER_TYPE_PHOTO)
            {
                // Because of pre-decoding, we need to stop the photo decode and no pre-decoding photo is existed.
                // And re-assign playing index to current display index
                // then call _MApp_MPlayer_PlayNext to decide next index
                // this idea from _MApp_MPlayer_PhotoProcessPrevNext
                if(m_u8DecodedPics > 0
                    || (m_u8DecodedPics == 0 && m_ePhotoType[0] != E_MPLAYER_SUBTYPE_INVALID) /* Patch for next progressive JPG or BMP*/
                    )
                {
                    m_u8DecodedPics = 1;
                    m_ePhotoType[1] = E_MPLAYER_SUBTYPE_INVALID;
                    MApp_Photo_Stop();

                    m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].u16PlayingIdx = m_u32PhotoCurrentDisplayedIdx;
                    if(!_MApp_MPlayer_PlayNext(E_MPLAYER_FOREGROUND_PLAYER))
                    {
                        m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaPlayingStatus |= E_MPLAYER_PHOTO_STATE_PLAY_END;
                    }
                    else
                    {
                        // We need to down the PLAY_END flag for the last photo while switching from REPEAT_NONE -> REPEAT_ONE
                        m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaPlayingStatus &= (enumMediaPlayingStatus)~E_MPLAYER_PHOTO_STATE_PLAY_END;
                    }
                    m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaPlayingStatus &= (enumMediaPlayingStatus)~E_MPLAYER_PHOTO_STATE_DECODE_PAUSE;
                }
            }
        }
        return E_MPLAYER_RET_OK;
    }
    else
    {
        return E_MPLAYER_RET_FAIL;
    }
}

//******************************************************************************
/// Set the media player repeat mode by MPlayer Type.
/// @param  eMPlayerIdx \b IN  Specify the mplayer type.
/// @param  eMode \b IN Specify the play mode is repeat one file, repeat all file, random repeat or repeat none.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_SetRepeatModeByMPlayerType(enumMPlayerMediaType eType, enumMPlayerRepeatMode eMode)
{
    if(eMode == E_MPLAYER_REPEAT_NONE
    || eMode == E_MPLAYER_REPEAT_1
    || eMode == E_MPLAYER_REPEAT_ALL)
    {
    #if ENABLE_BGM
        if(eType == E_MPLAYER_TYPE_MUSIC)
        {
            m_eRepeatMode[E_MPLAYER_BACKGROUND_PLAYER] = eMode;
            m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eRepeatMode = eMode;
        }
        else
    #else
        UNUSED(eType);
    #endif
        {
            m_eRepeatMode[E_MPLAYER_FOREGROUND_PLAYER] = eMode;
            m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eRepeatMode = eMode;
        }
        return E_MPLAYER_RET_OK;
    }
    else
    {
        return E_MPLAYER_RET_FAIL;
    }
}

#if RANDOM_PLAY
//******************************************************************************
/// Init the media player random mode.
/// @param  eMode \b IN Specify the play mode is random all file or random none.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_InitRandomMode(enumMPlayerRandomMode eMode)
{
    if(eMode == E_MPLAYER_RANDOM_NONE
    || eMode == E_MPLAYER_RANDOM)
    {
    #if ENABLE_BGM
        m_eRandomMode[E_MPLAYER_BACKGROUND_PLAYER] = eMode;
        m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eRandomMode = eMode;
    #endif
        m_eRandomMode[E_MPLAYER_FOREGROUND_PLAYER] = eMode;
        m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eRandomMode = eMode;

        if(eMode == E_MPLAYER_RANDOM)
        {
            _MApp_MPlayer_ResetRandomPlayTable(E_MPLAYER_MAX_CONCURRENT_PLAYER_NUM);
        }

        return E_MPLAYER_RET_OK;
    }
    else
    {
        return E_MPLAYER_RET_FAIL;
    }
}

//******************************************************************************
/// Set the media player random mode.
/// @param  eMode \b IN Specify the play mode is random all file or random none.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_SetRandomMode(enumMPlayerRandomMode eMode)
{
    enumMPlayerIdx eMPlayerIdx = E_MPLAYER_FOREGROUND_PLAYER;

    if(eMode == E_MPLAYER_RANDOM_NONE
    || eMode == E_MPLAYER_RANDOM)
    {
    #if ENABLE_BGM
        if(m_eMediaType == E_MPLAYER_TYPE_MUSIC)
        {
            eMPlayerIdx = E_MPLAYER_BACKGROUND_PLAYER;
            m_eRandomMode[eMPlayerIdx] = eMode;
            m_MPlayerInfo[eMPlayerIdx].eRandomMode = eMode;
        }
        else
    #endif
        {
            m_eRandomMode[eMPlayerIdx] = eMode;
            m_MPlayerInfo[eMPlayerIdx].eRandomMode = eMode;
        }

        if(eMode == E_MPLAYER_RANDOM)
        {
            _MApp_MPlayer_ResetRandomPlayTable(eMPlayerIdx);
        }

        return E_MPLAYER_RET_OK;
    }
    else
    {
         return E_MPLAYER_RET_FAIL;
    }
}

//******************************************************************************
/// Set the media player random mode.
/// @param  eMPlayerIdx \b IN  Specify the mplayer type.
/// @param  eMode \b IN Specify the play mode is random all file or random none.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_SetRandomModeByMPlayerType(enumMPlayerMediaType eType, enumMPlayerRandomMode eMode)
{
    enumMPlayerIdx eMPlayerIdx = E_MPLAYER_FOREGROUND_PLAYER;

    if(eMode == E_MPLAYER_RANDOM_NONE
    || eMode == E_MPLAYER_RANDOM)
    {
    #if ENABLE_BGM
        if(eType == E_MPLAYER_TYPE_MUSIC)
        {
            eMPlayerIdx = E_MPLAYER_BACKGROUND_PLAYER;
            m_eRandomMode[eMPlayerIdx] = eMode;
            m_MPlayerInfo[eMPlayerIdx].eRandomMode = eMode;
        }
        else
    #else
        UNUSED(eType);
    #endif
        {
            m_eRandomMode[eMPlayerIdx] = eMode;
            m_MPlayerInfo[eMPlayerIdx].eRandomMode = eMode;
        }

        if(eMode == E_MPLAYER_RANDOM)
        {
            _MApp_MPlayer_ResetRandomPlayTable(eMPlayerIdx);
        }

        return E_MPLAYER_RET_OK;
    }
    else
    {
         return E_MPLAYER_RET_FAIL;
    }
}
#endif

//******************************************************************************
/// Set the media player play mode.
/// @param  ePlayMode \b IN Specify the play mode is:
///     E_MPLAYER_PLAY_ONE:           Play only the current file.
///     E_MPLAYER_PLAY_SELECTED:      Play the files in the selected list.
///     E_MPLAYER_PLAY_SELECTED_FROM_CURRENT: Play the files from current selected within the selected list.
///     E_MPLAYER_PLAY_ONE_DIRECTORY: Play all files in the current directory.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_SetPlayMode(enumMPlayerPlayMode ePlayMode)
{
    if(ePlayMode == E_MPLAYER_PLAY_ONE                   ||
       ePlayMode == E_MPLAYER_PLAY_SELECTED              ||
       ePlayMode == E_MPLAYER_PLAY_SELECTED_FROM_CURRENT ||
       ePlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY         ||
       ePlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT)
    {
        m_ePlayMode = ePlayMode;
        return E_MPLAYER_RET_OK;
    }
    else
    {
        return E_MPLAYER_RET_FAIL;
    }
}

//******************************************************************************
/// Set the media player media type.
/// @param  eType  \b IN Specify the current media type is photo, music, movie or text.
/// @param  bReset \b IN TRUE:  enumerate the current directory.
///                      FALSE: Do not enumerate the current directory.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_SetCurrentMediaType(enumMPlayerMediaType eType, BOOLEAN bReset)
{
    switch(eType)
    {
    #if ENABLE_MPLAYER_PHOTO
        case E_MPLAYER_TYPE_PHOTO:
            m_u16FilesPerPage = NUM_OF_PHOTO_FILES_PER_PAGE;
            break;
    #endif  // #if ENABLE_MPLAYER_PHOTO

    #if ENABLE_MPLAYER_MUSIC
        case E_MPLAYER_TYPE_MUSIC:
            m_u16FilesPerPage = NUM_OF_MUSIC_FILES_PER_PAGE;
            break;
    #endif  // #if ENABLE_MPLAYER_MUSIC

    #if ENABLE_MPLAYER_MOVIE
        case E_MPLAYER_TYPE_MOVIE:
            m_u16FilesPerPage = NUM_OF_MOVIE_FILES_PER_PAGE;
            break;
    #endif  // #if ENABLE_MPLAYER_MOVIE

    #if ENABLE_MPLAYER_TEXT
        case E_MPLAYER_TYPE_TEXT:
            m_u16FilesPerPage = NUM_OF_TEXT_FILES_PER_PAGE;
            break;
    #endif  // #if ENABLE_MPLAYER_TEXT

    #if ENABLE_MPLAYER_PLUGIN
        case E_MPLAYER_TYPE_PLUGIN:
            m_u16FilesPerPage = NUM_OF_TEXT_FILES_PER_PAGE;
            break;
    #endif //#if ENABLE_MPLAYER_PLUGIN

    #if ENABLE_MPLAYER_MIXED
        case E_MPLAYER_TYPE_MIXED:
            m_u16FilesPerPage = NUM_OF_TEXT_FILES_PER_PAGE;
            break;
    #endif //#if ENABLE_MPLAYER_MIXED

        default:
            return E_MPLAYER_RET_FAIL;
    }
    m_eMediaType = eType;

    if(!bReset)
    {
        return E_MPLAYER_RET_OK;
    }

#if ENABLE_MPLAYER_MIXED
    if(eType == E_MPLAYER_TYPE_MIXED)
    {
          MApp_DMP_SetDmpFlag(DMP_FLAG_BROWSER_MIXED);
    }
    else
    {
          MApp_DMP_ClearDmpFlag(DMP_FLAG_BROWSER_MIXED);
    }
#endif

    //memset(m_u16DirectoryNum, 0, sizeof(U16)*NUM_OF_MAX_DIRECTORY_DEPTH);
    m_u16DirectoryNum[m_u16CurDirectoryDepth] = 0;
    m_u16CurFileIdx = 0;
#if (HIGH_SPEED_BROWSER)
    // force to re-enum current directory
    m_u16BufDirectoryDepth = MPLAYER_INVALID_INDEX;
#endif
    _MApp_MPlayer_Browser_EnumCurDirectory();

    m_u16CurPage1stFileIdx = 0;
    m_u16CurPageIdx =0;

    if(m_u16TotalFileNum && m_u16FilesPerPage>0)
    {
        m_u16TotalPageNum = (m_u16TotalFileNum+m_u16FilesPerPage-1) / m_u16FilesPerPage;
    }
    else
    {
        return E_MPLAYER_RET_FAIL;
    }

    return E_MPLAYER_RET_OK;

}

//******************************************************************************
/// Enable or disable to call MApp_UiMediaPlayer_Notify function when there is event.
/// @param  eNotify \b IN Specify the notification which will be enabled or disabled.
/// @param  bEnable \b IN TRUE:   Enable notification
///                     FALSE:  Disable notification
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_EnableNotify(enumMPlayerNotifyType eNotify, BOOLEAN bEnable)
{
    if(eNotify < E_MPLAYER_NOTIFY_NUM)
    {
        if(bEnable)
        {
            m_u64NotifyEnableFlags |= ((U64)1<<(U64)eNotify);
        }
        else
        {
            m_u64NotifyEnableFlags &= ~((U64)1<<(U64)eNotify);
        }
        return E_MPLAYER_RET_OK;
    }
    else if(eNotify == E_MPLAYER_NOTIFY_ALL)
    {
        if(bEnable)
        {
            m_u64NotifyEnableFlags |= (((U64)1<<(U64)E_MPLAYER_NOTIFY_NUM)-1);
        }
        else
        {
            m_u64NotifyEnableFlags = 0;
        }
        return E_MPLAYER_RET_OK;
    }

    return E_MPLAYER_RET_FAIL;
}

#if 0 //(ENABLE_MPLAYER_VIDEO_CAPTURE) //Old video capture flow. It can be removed
//******************************************************************************
/// Capture the current video and save it as a JPEG file.
/// @param  pFileName \b IN Specify the file name.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_CaptureVideo(U8 *pFileName, GOP_GwinFBAttr *pFBAttr)
{
    enumMPlayerRet eRet = E_MPLAYER_RET_FAIL;
    enumMPlayerMoviePlayMode eOriginalMoviePlayMode;

    if(IsStorageInUse())
    {
        switch(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType)
        {
        #if ENABLE_MPLAYER_MOVIE
            case E_MPLAYER_SUBTYPE_TS:
            case E_MPLAYER_SUBTYPE_RM:
            case E_MPLAYER_SUBTYPE_MPEG:
            case E_MPLAYER_SUBTYPE_MPEG4:
            case E_MPLAYER_SUBTYPE_MOVIE:
                eOriginalMoviePlayMode = m_eMoviePlayMode;

                if (MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_PAUSE) != E_MPLAYER_RET_OK)
                {
                    return E_MPLAYER_RET_FAIL;
                }

                eRet = (_MApp_MPlayer_CaptureVideo2JPGFile(pFileName, pFBAttr->addr, pFBAttr->size) ? E_MPLAYER_RET_OK : E_MPLAYER_RET_FAIL);

              #if (HIGH_SPEED_BROWSER)
                if (eRet == E_MPLAYER_RET_OK)
                {
                    // enable the flag to re-enum current directory later
                    m_u16BufDirectoryDepth = MPLAYER_INVALID_INDEX;
                }
              #endif

                // even _MApp_MPlayer_CaptureVideo2JPGFile() failed, MApp_VDPlayer_AfterCaptureVideo() has to be called
                if (MApp_MPlayer_MovieChangePlayMode(eOriginalMoviePlayMode) != E_MPLAYER_RET_OK)
                {
                    return E_MPLAYER_RET_FAIL;
                }
                break;
        #endif  // #if ENABLE_MPLAYER_MOVIE

        #if (defined(ALLOW_CAPTURE_SCREEN_WHEN_SLIDE_SHOW) && ALLOW_CAPTURE_SCREEN_WHEN_SLIDE_SHOW)
          #if ENABLE_MPLAYER_PHOTO
            #if (ENABLE_BMP)
            case E_MPLAYER_SUBTYPE_BMP:
            #endif
            case E_MPLAYER_SUBTYPE_JPG:
            #if (ENABLE_PNG)
            case E_MPLAYER_SUBTYPE_PNG:
            #endif
            #if (ENABLE_TIFF)
            case E_MPLAYER_SUBTYPE_TIFF:
            #endif
            #if (ENABLE_GIF)
            case E_MPLAYER_SUBTYPE_GIF:
            #endif
            if(_MApp_MPlayer_CaptureImage2JPGFile(pFileName, pFBAttr->addr, pFBAttr->size))
            {
            #if (HIGH_SPEED_BROWSER)
                // enable the flag to re-enum current directory later
                m_u16BufDirectoryDepth = MPLAYER_INVALID_INDEX;
            #endif
                return E_MPLAYER_RET_OK;
            }
            break;
          #endif  // #if ENABLE_MPLAYER_PHOTO
        #endif //#if (defined(ALLOW_CAPTURE_SCREEN_WHEN_SLIDE_SHOW) && ALLOW_CAPTURE_SCREEN_WHEN_SLIDE_SHOW)

            default:
                break;
        }
    }
    else
    {
        if(_MApp_MPlayer_CaptureImage2JPGFile(pFileName, pFBAttr->addr, pFBAttr->size))
        {
            return E_MPLAYER_RET_OK;
        }
    }

    return eRet;
}
#endif  // #if (ENABLE_MPLAYER_VIDEO_CAPTURE)

//******************************************************************************
/// Generate the file name for captured video JPEG file name.
/// @param  pFileName      \b IN Specify the file name.
/// @param  u16FileNameLen \b IN Specify the length of file name.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_GenCaptureFileName(U8 *pFileName, U16 u16FileNameLen)
{
    U16 u16CaptureIdx = 1;
    U16 u16Len = 14; // file name length (12) + '\0' (1)
    U16 *pString;

    if ((pFileName == NULL) || (u16FileNameLen < u16Len))
    {
        __ASSERT(0);
        return E_MPLAYER_RET_FAIL;
    }

    memset(pFileName, 0, u16FileNameLen);
    pString = (U16 *)msAPI_Memory_Allocate(u16Len * sizeof(U16), BUF_ID_FILEBROWER);

    if (pString == NULL)
    {
        __ASSERT(0);
        return E_MPLAYER_RET_FAIL;
    }

    do
    {
        if (u16CaptureIdx == 65000)
        { // maximum captured number
            snprintf((char*)pFileName, u16Len, "CAP%06d.JPG", u16CaptureIdx);
            msAPI_Memory_Free(pString, BUF_ID_FILEBROWER);

            return E_MPLAYER_RET_FAIL;
        }

        snprintf((char*)pFileName, u16Len, "CAP%06d.JPG", u16CaptureIdx++);

        memcpy(pString, pFileName, u16Len);
        ASCIItoUnicode2((S8*)pString, u16Len);
    }
    while (MApp_FilrBrowser_CheckNameExistedInCurrent(pString, u16Len-1));

    msAPI_Memory_Free(pString, BUF_ID_FILEBROWER);
    return E_MPLAYER_RET_OK;
}

//******************************************************************************
/// Set the photo slide show delay time in seconds.
/// @param  u16DelayTime \b IN Specify the delay time in seconds.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_SetPhotoSlideShowDelayTime(U16 u16DelayTime)
{
    m_u32PhotoSlideShowDelayTimeS = (U32)u16DelayTime * 1000;
    return E_MPLAYER_RET_OK;
}

//******************************************************************************
/// Reset slideshow start time
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_ResetSlideStartTime(void)
{
    m_u32PhotoSlideShowTimer = msAPI_Timer_GetTime0();
    return E_MPLAYER_RET_OK;
}

//******************************************************************************
/// Stop the error message pending on current media type.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_StopPlayerErrorMsgPending(void)
{
    enumMPlayerRet Ret = E_MPLAYER_RET_FAIL;

    if (m_eMediaType < E_MPLAYER_TYPE_INVALID)
    {
        switch(m_eMediaType)
        {
            case E_MPLAYER_TYPE_MUSIC:
                m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaPlayingStatus &= (enumMediaPlayingStatus)~E_MPLAYER_MUSIC_STATE_ERROR_PENDING;
                Ret = E_MPLAYER_RET_OK;
                break;
#if ENABLE_MPLAYER_MOVIE
            case E_MPLAYER_TYPE_MOVIE:
                m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaPlayingStatus &= (enumMediaPlayingStatus)~E_MPLAYER_MOVIE_STATE_ERROR_PENDING;
                Ret = E_MPLAYER_RET_OK;
                break;
#endif
            case E_MPLAYER_TYPE_PHOTO:
                m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaPlayingStatus &= (enumMediaPlayingStatus)~E_MPLAYER_PHOTO_STATE_ERROR_PENDING;
                Ret = E_MPLAYER_RET_OK;
                break;

#if ENABLE_MPLAYER_TEXT
            case E_MPLAYER_TYPE_TEXT:
                m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaPlayingStatus &= (enumMediaPlayingStatus)~E_MPLAYER_TEXT_STATE_ERROR_PENDING;
                Ret = E_MPLAYER_RET_OK;
                break;
#endif
            default:
                break;
        }
    }

    return Ret;
}


//******************************************************************************
/// Set the player error message delay time in seconds.
/// @param  eType \b IN Specify the current media type is photo, music, movie or text.
/// @param  u16DelayTime \b IN Specify the delay time in seconds.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_SetPlayerErrorDelayTime(enumMPlayerMediaType eType, U16 u16DelayTime)
{
    enumMPlayerRet Ret = E_MPLAYER_RET_FAIL;

    if (eType < E_MPLAYER_TYPE_INVALID)
    {
        switch(eType)
        {
            case E_MPLAYER_TYPE_MUSIC:
                m_u32MusicErrorDelayTimeS = (U32)u16DelayTime * 1000;
                Ret = E_MPLAYER_RET_OK;
                break;
#if ENABLE_MPLAYER_MOVIE
            case E_MPLAYER_TYPE_MOVIE:
                m_u32MovieErrorDelayTimeS = (U32)u16DelayTime * 1000;
                Ret = E_MPLAYER_RET_OK;
                break;
#endif
            case E_MPLAYER_TYPE_PHOTO:
                m_u32PhotoErrorDelayTimeS = (U32)u16DelayTime * 1000;
                Ret = E_MPLAYER_RET_OK;
                break;
#if ENABLE_MPLAYER_TEXT
            case E_MPLAYER_TYPE_TEXT:
                m_u32TextErrorDelayTimeS = (U32)u16DelayTime * 1000;
                Ret = E_MPLAYER_RET_OK;
                break;
#endif
            default:
                break;
        }

    }

    return Ret;
}

//******************************************************************************
/// Query the player Error delay time in seconds.
/// @param  eType \b IN Specify the current media type is photo, music, movie or text.
/// @return u32ErrorTime
//******************************************************************************
U32 MApp_MPlayer_QueryPlayerErrorDelayTime(enumMPlayerMediaType eType)
{
    U32 u32ErrorTime = 0; //in seconds

    if (eType < E_MPLAYER_TYPE_INVALID)
    {
        switch(eType)
        {
            case E_MPLAYER_TYPE_MUSIC:
                u32ErrorTime = m_u32MusicErrorDelayTimeS/1000;
                break;
#if ENABLE_MPLAYER_MOVIE
            case E_MPLAYER_TYPE_MOVIE:
                u32ErrorTime = m_u32MovieErrorDelayTimeS/1000;
                break;
#endif
            case E_MPLAYER_TYPE_PHOTO:
                u32ErrorTime = m_u32PhotoErrorDelayTimeS/1000;
                break;
#if ENABLE_MPLAYER_TEXT
            case E_MPLAYER_TYPE_TEXT:
                u32ErrorTime = m_u32TextErrorDelayTimeS/1000;
                break;
#endif
            default:
                u32ErrorTime = 0;
                break;
        }
    }

    return u32ErrorTime;
}



//******************************************************************************
/// Set Movie preview window size
//******************************************************************************
void MApp_MPlayer_SetMoviePreviewWindow(U16 u16X, U16 u16Y, U16 u16Width, U16 u16Height,EN_ASPECT_RATIO_TYPE eAspectRatioType)
{
    MApp_VDPlayer_SetPreviewWindow(u16X,u16Y,u16Width,u16Height,eAspectRatioType);
}


//******************************************************************************
/// Begin to play media files.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_Play(void)
{
    enumMPlayerRet eRet = E_MPLAYER_RET_OK;

    if (m_eMediaType >= E_MPLAYER_TYPE_NUM)
    {
        return eRet;
    }

    enumMPlayerIdx eMPlayerIdx = E_MPLAYER_FOREGROUND_PLAYER;

#if ENABLE_MPLAYER_MUSIC
    // select background player if user is browsing music
    if (m_eMediaType == E_MPLAYER_TYPE_MUSIC)
    {
        eMPlayerIdx = E_MPLAYER_BACKGROUND_PLAYER;
    }
#endif  // #if ENABLE_MPLAYER_MUSIC

#if RANDOM_PLAY
    m_bPlayNext = FALSE;
    _MApp_MPlayer_ResetRandomPlayTable(eMPlayerIdx);
#endif

#if ENABLE_MPLAYER_PLUGIN
    if(m_eMediaType == E_MPLAYER_TYPE_PLUGIN)
    {
        MApp_MPlayer_DisconnectAllDevices();  //Handle USB connect in APEngine!!
        m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 |= (enumMPlayerKnlFlags1)E_MPLAYER_KNL_FLG1_PLUGIN_PLAY;
        return eRet;
    }
#endif //#if ENABLE_MPLAYER_PLUGIN

#if ENABLE_MPLAYER_MUSIC
    if (m_eMediaType == E_MPLAYER_TYPE_MUSIC)
    {
        return MApp_MPlayer_PlayMusic();
    }
#endif // #if ENABLE_MPLAYER_MUSIC

    _MApp_Mplayer_InitializeCoProcessor();

    MApp_MPlayer_StopPreview();

    // Initialize variables for photo playback
    m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaPlayingStatus = E_MPLAYER_STATE_NONE;
    m_u8DecodedPics = 0;
    m_ePhotoType[0] = E_MPLAYER_SUBTYPE_INVALID;
    m_ePhotoType[1] = E_MPLAYER_SUBTYPE_INVALID;

    m_eZoom = E_MPLAYER_ZOOM_1;
    m_eMoviePlayMode = E_MPLAYER_MOVIE_NORMAL;
    m_eMovieMainExit = EXIT_VDPLAYER_NULL;
    m_s16VideoShiftX = m_s16VideoShiftY = 0;

#if PHOTO_SLIDE_SHOW_EFFECT
    if(m_eMediaType == E_MPLAYER_TYPE_PHOTO)
    {
    #if (!ENABLE_4K2K)
        // 4K2K is used GOP now, no need to setup MVOP, scaler.
        MApp_Photo_InitFullScreenDisplay();
    #endif
    }
#endif

#if ENABLE_MPLAYER_MOVIE
    if ((m_eMediaType == E_MPLAYER_TYPE_MOVIE)
            && MApp_MPlayer_IsMusicPlaying())
    {
        MApp_MPlayer_StopMusic();
    }
#endif // #if ENABLE_MPLAYER_MOVIE

    if (_MApp_MPlayer_PlayerInit(E_MPLAYER_FOREGROUND_PLAYER, m_eMediaType, FALSE) == FALSE)
    {
        goto MApp_MPlayer_Play_END;
    }

    if((m_ePlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY) ||
       (m_ePlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT))
    {
        if(_MApp_MPlayer_PlayDirectory(E_MPLAYER_FOREGROUND_PLAYER))
        {
            goto MApp_MPlayer_Play_END;
        }
    }
    else
    {
        if(_MApp_MPlayer_PlayList(E_MPLAYER_FOREGROUND_PLAYER))
        {
            goto MApp_MPlayer_Play_END;
        }
    }

    NOTIFY(E_MPLAYER_NOTIFY_END_OF_PLAY_ALL_FILE, &m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaType);
    eRet = E_MPLAYER_RET_FAIL;

MApp_MPlayer_Play_END:
    return eRet;
}

//******************************************************************************
/// Begin to play background music.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_PlayMusic(void)
{
    enumMPlayerRet bRet = E_MPLAYER_RET_OK;

    if (MApp_MPlayer_IsMusicPlaying())
        return E_MPLAYER_RET_OK;

    MApp_MPlayer_MusicStopPreview();

    // Initialize playback mode.
    bMusicRecording = FALSE;
    m_eMusicPlayMode = E_MPLAYER_MUSIC_NORMAL;

    if (_MApp_MPlayer_PlayerInit(E_MPLAYER_BACKGROUND_PLAYER, E_MPLAYER_TYPE_MUSIC, FALSE) == FALSE)
    {
        goto MApp_MPlayer_PlayBackGroundMusic_END;
    }

    // when using hot key to play music while browsing photo/movie/text, always set play index to 0
    if (m_eMediaType != E_MPLAYER_TYPE_MUSIC)
    {
        m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].u16PlayingIdx = 0;
        if(m_u16SelectedFileNum[E_MPLAYER_TYPE_MUSIC] == 0)
        {
            m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].ePlayMode = E_MPLAYER_PLAY_ONE_DIRECTORY;

            if(!_MApp_MPlayer_PlayDirectory(E_MPLAYER_BACKGROUND_PLAYER))
            {
                bRet = E_MPLAYER_RET_FAIL;
            }
        }
        else
        {
            m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].ePlayMode = E_MPLAYER_PLAY_SELECTED;

            if(!_MApp_MPlayer_PlayList(E_MPLAYER_BACKGROUND_PLAYER))
            {
                bRet = E_MPLAYER_RET_FAIL;
            }
        }
        goto MApp_MPlayer_PlayBackGroundMusic_END;
    }
    else if((m_ePlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY) ||
       (m_ePlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT))
    {
        if(_MApp_MPlayer_PlayDirectory(E_MPLAYER_BACKGROUND_PLAYER))
        {
            goto MApp_MPlayer_PlayBackGroundMusic_END;
        }
    }
    else
    {
        if(_MApp_MPlayer_PlayList(E_MPLAYER_BACKGROUND_PLAYER))
        {
            goto MApp_MPlayer_PlayBackGroundMusic_END;
        }
    }
    NOTIFY(E_MPLAYER_NOTIFY_END_OF_PLAY_ALL_FILE, &m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaType);
    bRet = E_MPLAYER_RET_FAIL;

MApp_MPlayer_PlayBackGroundMusic_END:
    return bRet;
}

//******************************************************************************
/// Resume background music.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_ResumeMusic(void)
{
#if (!ENABLE_BGM)
    return E_MPLAYER_RET_IGNORE;
#else
    if (!MApp_MPlayer_IsMusicPlaying())
        return E_MPLAYER_RET_FAIL;

  #if (ENABLE_WMA)
    if (E_MPLAYER_SUBTYPE_WMA == m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType)
        MApp_WMA_Resume();
    else
  #endif
        MApp_Music_Resume();

    m_eMusicPlayMode = E_MPLAYER_MUSIC_NORMAL;

    return E_MPLAYER_RET_OK;
#endif // #if (!ENABLE_BGM)
}

//******************************************************************************
/// Stop the current playing and play the next media file.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_PlayNextFile(void)
{
    BOOLEAN bRet=FALSE;
    enumMPlayerIdx eMPlayerIdx = E_MPLAYER_FOREGROUND_PLAYER;

#if ENABLE_MPLAYER_MUSIC
    // select background player if user is browsing music
    if (m_eMediaType == E_MPLAYER_TYPE_MUSIC)
    {
        eMPlayerIdx = E_MPLAYER_BACKGROUND_PLAYER;
    }
#endif  // #if ENABLE_MPLAYER_MUSIC

#if RANDOM_PLAY
    m_bPlayNext = TRUE;
    _MApp_MPlayer_ResetRandomPlayTable(eMPlayerIdx);
#endif

    // Initialize playback mode.
    if (eMPlayerIdx == E_MPLAYER_FOREGROUND_PLAYER)
    {
        m_eZoom = E_MPLAYER_ZOOM_1;
//        m_ePhotoRotate = E_MPLAYER_PHOTO_ROTATE_0;
        m_eMoviePlayMode = E_MPLAYER_MOVIE_NORMAL;
        m_eMovieMainExit = EXIT_VDPLAYER_NULL;
        m_s16VideoShiftX = m_s16VideoShiftY = 0;
    }
    if (eMPlayerIdx == E_MPLAYER_BACKGROUND_PLAYER)
    {
        m_eMusicPlayMode = E_MPLAYER_MUSIC_NORMAL;
        bMusicRecording = FALSE;
    }

     //MPLAYER_DBG(printf("MApp_MPlayer_PlayNextFile() : m_eMediaType = %bu\n", (U8)m_eMediaType));
     //MPLAYER_DBG(printf("MApp_MPlayer_PlayNextFile() : eMediaSubType = %bu\n", (U8)m_MPlayerInfo[eMPlayerIdx].eMediaSubType));
    switch(m_MPlayerInfo[eMPlayerIdx].eMediaSubType)
    {
    #if ENABLE_MPLAYER_PHOTO
        case E_MPLAYER_SUBTYPE_JPG:
        #if (ENABLE_BMP)
        case E_MPLAYER_SUBTYPE_BMP:
        #endif
        #if (ENABLE_PNG)
        case E_MPLAYER_SUBTYPE_PNG:
        #endif
        #if (ENABLE_TIFF)
        case E_MPLAYER_SUBTYPE_TIFF:
        #endif
        #if (ENABLE_GIF)
        case E_MPLAYER_SUBTYPE_GIF:
        #endif
            if(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaPlayingStatus & E_MPLAYER_PHOTO_STATE_PAUSE)
            {
                //bPauseToNextFlag=TRUE;
                if(m_u8DecodedPics<2)
                    m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_FILE_INIT;
            }
            m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaPlayingStatus &= (enumMediaPlayingStatus)~E_MPLAYER_PHOTO_STATE_PAUSE;
            bRet = _MApp_MPlayer_PhotoProcessPrevNext(TRUE);
            break;
    #endif  // #if ENABLE_MPLAYER_PHOTO

    #if ENABLE_MPLAYER_MUSIC
        case E_MPLAYER_SUBTYPE_MP3:
#if (ENABLE_FLAC)
        case E_MPLAYER_SUBTYPE_FLAC:
#endif
#if (ENABLE_AC3)
        case E_MPLAYER_SUBTYPE_AC3:
#endif
#if (ENABLE_AAC)
        case E_MPLAYER_SUBTYPE_AAC:
#endif
#if (ENABLE_WAV)
        case E_MPLAYER_SUBTYPE_WAV:
#endif
      #if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
        case E_MPLAYER_SUBTYPE_LOAS:
      #endif //#if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
#if (ENABLE_OGG)
    case E_MPLAYER_SUBTYPE_OGG:
#endif
#if (ENABLE_AMR)
        case E_MPLAYER_SUBTYPE_AMR:
        case E_MPLAYER_SUBTYPE_AWB:
#endif
            MApp_Music_Stop();
            break;

      #if (ENABLE_WMA)
        case E_MPLAYER_SUBTYPE_WMA:
            MApp_WMA_Stop();
            break;
      #endif  // #if ENABLE_WMA
    #endif  // #if ENABLE_MPLAYER_MUSIC

    #if ENABLE_MPLAYER_MOVIE
        case E_MPLAYER_SUBTYPE_TS:
        case E_MPLAYER_SUBTYPE_RM:
        case E_MPLAYER_SUBTYPE_MPEG:
        case E_MPLAYER_SUBTYPE_MPEG4:
        case E_MPLAYER_SUBTYPE_MOVIE:

            msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
            MApi_XC_GenerateBlackVideo(ENABLE, MAIN_WINDOW);
            MApp_VDPlayer_Stop();

      #if (ENABLE_SUBTITLE_DMP)
            if(m_u8ExternalSubtitleFileHandle != FCTRL_INVALID_FILE_HANDLE)
            {
                msAPI_FCtrl_FileClose(m_u8ExternalSubtitleFileHandle);
                m_u8ExternalSubtitleFileHandle = FCTRL_INVALID_FILE_HANDLE;
#if (ENABLE_INTERNAL_BMP_SUBTITLE || ENABLE_EXTERNAL_BMP_SUBTITLE)
                msAPI_MpegSP_Dinit();
#endif
            }
      #endif //#if (ENABLE_SUBTITLE_DMP)

        break;
#endif  // #if ENABLE_MPLAYER_MOVIE
#if ENABLE_MPLAYER_TEXT
    case E_MPLAYER_SUBTYPE_TEXT:
        TEXT_FileClose();
        break;
#endif  // #if ENABLE_MPLAYER_TEXT
    default:
        MPLAYER_DBG(printf("        - unknown media sub-type!\n"));
        break; //return E_MPLAYER_RET_FAIL;
    }

#if ENABLE_MPLAYER_PHOTO
    if(m_MPlayerInfo[eMPlayerIdx].eMediaType != E_MPLAYER_TYPE_PHOTO)
#endif  // #if ENABLE_MPLAYER_PHOTO
    {
        if (eMPlayerIdx == E_MPLAYER_FOREGROUND_PLAYER)
        {
#if ENABLE_MPLAYER_PHOTO
            m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_PHOTO_PLAY;
#endif  // #if ENABLE_MPLAYER_PHOTO
#if ENABLE_MPLAYER_MOVIE
            m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_MOVIE_PLAY;
#endif  // #if ENABLE_MPLAYER_MOVIE
#if ENABLE_MPLAYER_TEXT
            m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_TEXT_PLAY;
#endif  // #if ENABLE_MPLAYER_TEXT
        }
        if (eMPlayerIdx == E_MPLAYER_BACKGROUND_PLAYER)
        {
#if ENABLE_MPLAYER_MUSIC
            m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_MUSIC_PLAY;
#endif  // #if ENABLE_MPLAYER_MUSIC
        }

        bRet = _MApp_MPlayer_PlayNext(eMPlayerIdx);

#if ENABLE_EMBEDDED_PHOTO_DISPLAY
        if(!bRet)
        {
            m_eEmbeddedPhotoState = E_EMBEDDED_PHOTO_WAIT;
        }
#endif

    }

    if(bRet)
    {
        return E_MPLAYER_RET_OK;
    }
    else
    {
        NOTIFY(E_MPLAYER_NOTIFY_END_OF_PLAY_ALL_FILE, &m_MPlayerInfo[eMPlayerIdx].eMediaType);
        return E_MPLAYER_RET_FAIL;
    }
}

//******************************************************************************
/// Stop the current playing and play the previous media file.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_PlayPrevFile(void)
{
    BOOLEAN bRet=FALSE;
    enumMPlayerIdx eMPlayerIdx = E_MPLAYER_FOREGROUND_PLAYER;

#if ENABLE_MPLAYER_MUSIC
    // select background player if user is browsing music
    if (m_eMediaType == E_MPLAYER_TYPE_MUSIC)
    {
        eMPlayerIdx = E_MPLAYER_BACKGROUND_PLAYER;
    }
#endif  // #if ENABLE_MPLAYER_MUSIC

#if RANDOM_PLAY
    _MApp_MPlayer_ResetRandomPlayTable(eMPlayerIdx);
#endif

    // Initialize variables for photo playback
//    m_ePhotoRotate = E_MPLAYER_PHOTO_ROTATE_0;

    // Initialize playback mode.
    if (eMPlayerIdx == E_MPLAYER_FOREGROUND_PLAYER)
    {
        m_eZoom = E_MPLAYER_ZOOM_1;
//        m_ePhotoRotate = E_MPLAYER_PHOTO_ROTATE_0;
        m_eMoviePlayMode = E_MPLAYER_MOVIE_NORMAL;
        m_eMovieMainExit = EXIT_VDPLAYER_NULL;
        m_s16VideoShiftX = m_s16VideoShiftY = 0;
    }
    if (eMPlayerIdx == E_MPLAYER_BACKGROUND_PLAYER)
    {
        m_eMusicPlayMode = E_MPLAYER_MUSIC_NORMAL;
        bMusicRecording = FALSE;
    }

    switch(m_MPlayerInfo[eMPlayerIdx].eMediaSubType)
    {
#if ENABLE_MPLAYER_PHOTO
    case E_MPLAYER_SUBTYPE_JPG:
    #if (ENABLE_BMP)
    case E_MPLAYER_SUBTYPE_BMP:
    #endif
    #if (ENABLE_PNG)
    case E_MPLAYER_SUBTYPE_PNG:
    #endif
    #if (ENABLE_TIFF)
    case E_MPLAYER_SUBTYPE_TIFF:
    #endif
    #if (ENABLE_GIF)
    case E_MPLAYER_SUBTYPE_GIF:
    #endif
        m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaPlayingStatus &= (enumMediaPlayingStatus)~E_MPLAYER_PHOTO_STATE_PAUSE;
        bRet = _MApp_MPlayer_PhotoProcessPrevNext(FALSE);
        break;
#endif  // #if ENABLE_MPLAYER_PHOTO
#if ENABLE_MPLAYER_MUSIC
    case E_MPLAYER_SUBTYPE_MP3:
#if (ENABLE_AAC)
    case E_MPLAYER_SUBTYPE_AAC:
#endif
#if (ENABLE_WAV)
    case E_MPLAYER_SUBTYPE_WAV:
#endif
#if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
    case E_MPLAYER_SUBTYPE_LOAS:
#endif //#if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
#if (ENABLE_OGG)
    case E_MPLAYER_SUBTYPE_OGG:
#endif
#if (ENABLE_FLAC)
    case E_MPLAYER_SUBTYPE_FLAC:
#endif
#if (ENABLE_AC3)
    case E_MPLAYER_SUBTYPE_AC3:
#endif
#if (ENABLE_AMR)
    case E_MPLAYER_SUBTYPE_AMR:
    case E_MPLAYER_SUBTYPE_AWB:
#endif
        MApp_Music_Stop();
        break;
#if (ENABLE_WMA)
    case E_MPLAYER_SUBTYPE_WMA:
        MApp_WMA_Stop();
        break;
#endif  // #if ENABLE_WMA
#endif  // #if ENABLE_MPLAYER_MUSIC
#if ENABLE_MPLAYER_MOVIE
    case E_MPLAYER_SUBTYPE_TS:
    case E_MPLAYER_SUBTYPE_RM:
    case E_MPLAYER_SUBTYPE_MPEG:
    case E_MPLAYER_SUBTYPE_MPEG4:
    case E_MPLAYER_SUBTYPE_MOVIE:

        msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
        MApi_XC_GenerateBlackVideo(ENABLE, MAIN_WINDOW);
        MApp_VDPlayer_Stop();

#if (ENABLE_SUBTITLE_DMP)
        if(m_u8ExternalSubtitleFileHandle != FCTRL_INVALID_FILE_HANDLE)
        {
            msAPI_FCtrl_FileClose(m_u8ExternalSubtitleFileHandle);
            m_u8ExternalSubtitleFileHandle = FCTRL_INVALID_FILE_HANDLE;
#if (ENABLE_INTERNAL_BMP_SUBTITLE || ENABLE_EXTERNAL_BMP_SUBTITLE)
            msAPI_MpegSP_Dinit();
#endif
        }
#endif //#if (ENABLE_SUBTITLE_DMP)

        break;
#endif  // #if ENABLE_MPLAYER_MOVIE
#if ENABLE_MPLAYER_TEXT
    case E_MPLAYER_SUBTYPE_TEXT:
        TEXT_FileClose();
        break;
#endif  // #if ENABLE_MPLAYER_TEXT
    default:
        return E_MPLAYER_RET_FAIL;
    }

#if ENABLE_MPLAYER_PHOTO
    if(m_eMediaType != E_MPLAYER_TYPE_PHOTO)
#endif  // #if ENABLE_MPLAYER_PHOTO
    {
        if (eMPlayerIdx == E_MPLAYER_FOREGROUND_PLAYER)
        {
#if ENABLE_MPLAYER_PHOTO
            m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_PHOTO_PLAY;
#endif  // #if ENABLE_MPLAYER_PHOTO
#if ENABLE_MPLAYER_MOVIE
            m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_MOVIE_PLAY;
#endif  // #if ENABLE_MPLAYER_MOVIE
#if ENABLE_MPLAYER_TEXT
            m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_TEXT_PLAY;
#endif  // #if ENABLE_MPLAYER_TEXT
        }
        if (eMPlayerIdx == E_MPLAYER_BACKGROUND_PLAYER)
        {
#if ENABLE_MPLAYER_MUSIC
            m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_MUSIC_PLAY;
#endif  // #if ENABLE_MPLAYER_MUSIC
        }

        bRet = _MApp_MPlayer_PlayPrev(eMPlayerIdx);

#if ENABLE_EMBEDDED_PHOTO_DISPLAY
            if(!bRet)
            {
                m_eEmbeddedPhotoState = E_EMBEDDED_PHOTO_WAIT;
            }
#endif

    }
    if(bRet)
    {
        return E_MPLAYER_RET_OK;
    }
    else
    {
        NOTIFY(E_MPLAYER_NOTIFY_END_OF_PLAY_ALL_FILE, &m_MPlayerInfo[eMPlayerIdx].eMediaType);
        return E_MPLAYER_RET_FAIL;
    }
}

//******************************************************************************
/// Play a media file.
/// When use this function, will destroy the media player kernel internal
/// file management. Users need to manage the file browser.
/// @param  pFullPathName \b IN Specify the full name with full path.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_PlayOneMediaFile(U8 *pFullPathName)
{
    pFullPathName = pFullPathName;

    return E_MPLAYER_RET_FAIL;
}

//******************************************************************************
/// Stop play media files
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_Stop(void)
{
#if RANDOM_PLAY
    m_bPlayNext = FALSE;
#endif
    if (m_eMediaType >= E_MPLAYER_TYPE_NUM)
    {
        return E_MPLAYER_RET_FAIL;
    }

#if ENABLE_MPLAYER_PLUGIN
    if(m_eMediaType == E_MPLAYER_TYPE_PLUGIN)
    {
        m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_PLUGIN_PLAY;
        return E_MPLAYER_RET_OK;
    }
#endif //#if ENABLE_MPLAYER_PLUGIN

#if ENABLE_MPLAYER_MUSIC
    if (m_eMediaType == E_MPLAYER_TYPE_MUSIC)
    {
        m_eMusicPlayMode = E_MPLAYER_MUSIC_STOP;
        return MApp_MPlayer_StopMusic();
    }
#endif // #if ENABLE_MPLAYER_MUSIC

#if ENABLE_MPLAYER_PHOTO
        m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_PHOTO_PLAY;
#endif  // #if ENABLE_MPLAYER_PHOTO
#if ENABLE_MPLAYER_MOVIE
        m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_MOVIE_PLAY;
#endif  // #if ENABLE_MPLAYER_MOVIE
#if ENABLE_MPLAYER_TEXT
        m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_TEXT_PLAY;
#endif  // #if ENABLE_MPLAYER_TEXT

    switch(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType)
    {
#if ENABLE_MPLAYER_PHOTO
    case E_MPLAYER_SUBTYPE_JPG:
    #if (ENABLE_BMP)
    case E_MPLAYER_SUBTYPE_BMP:
    #endif
    #if (ENABLE_PNG)
    case E_MPLAYER_SUBTYPE_PNG:
    #endif
    #if (ENABLE_TIFF)
    case E_MPLAYER_SUBTYPE_TIFF:
    #endif
    #if (ENABLE_GIF)
    case E_MPLAYER_SUBTYPE_GIF:
    #endif

    #if (ENABLE_4K2K == 1)
        MApp_Photo_Display_Disable4K2KPhotoDisplay();
    #else
        //MDrv_MVOP_Enable(FALSE);
        MApp_Photo_Display_Stop();
    #endif
        MApp_Photo_Stop();
        break;
#endif  // #if ENABLE_MPLAYER_PHOTO

#if ENABLE_MPLAYER_MOVIE
    case E_MPLAYER_SUBTYPE_TS:
    case E_MPLAYER_SUBTYPE_RM:
    case E_MPLAYER_SUBTYPE_MPEG:
    case E_MPLAYER_SUBTYPE_MPEG4:
    case E_MPLAYER_SUBTYPE_MOVIE:

        m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType = E_MPLAYER_SUBTYPE_INVALID;

        msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
        //MApi_XC_GenerateBlackVideo(ENABLE, MAIN_WINDOW);
#if DYNSCALING
        XC_DynamicScaling_Info stDS_Info;
        memset(&stDS_Info, 0, sizeof(XC_DynamicScaling_Info));
        stDS_Info.bOP_DS_On = FALSE;
        stDS_Info.bIPS_DS_On = FALSE;
        stDS_Info.bIPM_DS_On = FALSE;
        if(TRUE != MApi_XC_SetDynamicScaling(&stDS_Info, sizeof(XC_DynamicScaling_Info), MAIN_WINDOW))
        {
            MPLAYER_DBG(printf("Set DS error\n"));
        }
        MDrv_PQ_SetDS_OnOFF(PQ_MAIN_WINDOW,  FALSE);
#endif
        MApp_VDPlayer_Stop();

        // Disable scaler periodic task
        MAPI_XC_MUX_ONOFF_PERIODIC_HANDLER(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), DISABLE);

//        if(m_u8ExternalSubtitleFileHandle != FCTRL_INVALID_FILE_HANDLE)
#if (ENABLE_SUBTITLE_DMP)
        if(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_SUBTITLE_VALID)
        {
            msAPI_FCtrl_FileClose(m_u8ExternalSubtitleFileHandle);
            m_u8ExternalSubtitleFileHandle = FCTRL_INVALID_FILE_HANDLE;
            MApp_MPlayer_EnableInternalSubtitle(FALSE);
#if (ENABLE_INTERNAL_BMP_SUBTITLE || ENABLE_EXTERNAL_BMP_SUBTITLE)
            msAPI_MpegSP_Reset_SpuQueue();
            msAPI_MpegSP_Dinit();
#endif
            MApp_MPlayer_SubtitleDeInit();
        }
#endif //#if (ENABLE_SUBTITLE_DMP)
        break;

#if ENABLE_DVD
    case E_MPLAYER_SUBTYPE_DVD:
        msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
        //MApi_XC_GenerateBlackVideo(ENABLE, MAIN_WINDOW);
        MApp_VDPlayer_DVD_Stop();
        break;
#endif

#endif  // #if ENABLE_MPLAYER_MOVIE
#if ENABLE_MPLAYER_TEXT
    case E_MPLAYER_SUBTYPE_TEXT:
        TEXT_FileClose();
        break;
#endif  // #if ENABLE_MPLAYER_TEXT

    default:
        return E_MPLAYER_RET_FAIL;
    }

     if(1 == MApp_MPlayer_QueryTotalDriveNum())//wht120815_1
     {
    	//_MApp_MPlayer_Change2CurrentDirectory();
     }
    //_MApp_MPlayer_Browser_EnumCurDirectory();

    // The reason we need this statement here is when user capture video when playing PHOTO,
    // the m_u16TotalPageNum may change because total photo count is changed.
    if(m_u16FilesPerPage>0)
    {
        m_u16TotalPageNum = (m_u16TotalFileNum+m_u16FilesPerPage-1) /m_u16FilesPerPage;
    }

    return E_MPLAYER_RET_OK;
}

//******************************************************************************
/// Stop play background music
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_StopMusic(void)
{
    if (!MApp_MPlayer_IsMusicPlaying())
        return E_MPLAYER_RET_OK;

#if ENABLE_EMBEDDED_PHOTO_DISPLAY
    //Not use STOPTHUMBNAIL , Because we need the state in WAIT
    MApp_MPlayer_ClearEmbeddedPhoto();
#endif

#if ENABLE_MPLAYER_MUSIC
        m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_MUSIC_PLAY;
#endif // #if ENABLE_MPLAYER_MUSIC

    switch(m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType)
    {
#if ENABLE_MPLAYER_MUSIC
        case E_MPLAYER_SUBTYPE_MP3:
#if (ENABLE_AAC)
        case E_MPLAYER_SUBTYPE_AAC:
#endif
#if (ENABLE_WAV)
        case E_MPLAYER_SUBTYPE_WAV:
#endif
#if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
        case E_MPLAYER_SUBTYPE_LOAS:
#endif //#if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
#if (ENABLE_OGG)
        case E_MPLAYER_SUBTYPE_OGG:
#endif
#if (ENABLE_AMR)
        case E_MPLAYER_SUBTYPE_AMR:
        case E_MPLAYER_SUBTYPE_AWB:
#endif
#if (ENABLE_FLAC)
        case E_MPLAYER_SUBTYPE_FLAC:
#endif
#if (ENABLE_AC3)
        case E_MPLAYER_SUBTYPE_AC3:
#endif

            MApp_Music_Stop();
            break;

    #if (ENABLE_WMA)
        case E_MPLAYER_SUBTYPE_WMA:
            MApp_WMA_Stop();
            break;
    #endif
#endif  // #if ENABLE_MPLAYER_MUSIC

    default:
        return E_MPLAYER_RET_FAIL;
    }

    return E_MPLAYER_RET_OK;
}

#if ENABLE_MPLAYER_PHOTO
//******************************************************************************
/// Change the zoom scale for the current playing photo.
/// The zoom scale will set the normal (1x) for the next photo.
/// @param  eZoom \b IN Specify the zoom scale.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_PhotoZoom(enumMPlayerZoom eZoom)
{
    //Background MUSIC: need input data!
    MApp_MPlayer_BGM_Bitstream_Handle();

    if(eZoom < E_MPLAYER_ZOOM_NUM)
    {
        m_eZoom = eZoom;
        // Note: mustc confirm the jpeg and RGB zoom is from 1/8 to 8.
        eZoom ++;
#if (PHOTO_SLIDE_SHOW_EFFECT)
        switch(m_ePhotoType[0])
        {
        case E_MPLAYER_SUBTYPE_JPG:
        #if (ENABLE_BMP)
        case E_MPLAYER_SUBTYPE_BMP:
        #endif
        #if (ENABLE_PNG)
        case E_MPLAYER_SUBTYPE_PNG:
        #endif
        #if (ENABLE_TIFF)
        case E_MPLAYER_SUBTYPE_TIFF:
        #endif
        #if (ENABLE_GIF)
        case E_MPLAYER_SUBTYPE_GIF:
        #endif
            MApp_Photo_Zooming((EN_PHOTO_ZOOMING)eZoom);
            break;
        default:
            return E_MPLAYER_RET_FAIL;
        }
#endif  // #if (PHOTO_SLIDE_SHOW_EFFECT)
    }
    else
    {
        return E_MPLAYER_RET_FAIL;
    }
    return E_MPLAYER_RET_OK;
}
#endif  // #if ENABLE_MPLAYER_PHOTO

#if ENABLE_MPLAYER_MOVIE
//******************************************************************************
/// Change the zoom scale for the current playing movie.
/// The zoom scale will set the normal (1x) for the next movie.
/// @param  eZoom \b IN Specify the zoom scale.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_MovieZoom(enumMPlayerZoom eZoom)
{
    //MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);  //for MM pause screen flicker issue
    //MApi_XC_FreezeImg set TRUE at pausing movie
    if(eZoom < E_MPLAYER_ZOOM_NUM)
    {

        m_eZoom = eZoom;
        m_s16VideoShiftX = m_s16VideoShiftY = 0;
        // Note: mustc confirm the MPEG2 and MPEG4 zoom is from 1/4 to 8.
#if ENABLE_MPLAYER_MOVIE
        if(_MApp_MPlayer_IsSupportedMovie(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType))
        {
#if (FBL_ZOOM==1)
            if(MApi_XC_IsCurrentFrameBufferLessMode() || g_bForceToFB)
            {
                MApp_VDPlayer_ScaleVideo_FBL((VDPLAYER_ZOOM_FACT) eZoom);
            }
            else
#endif
            MApp_VDPlayer_ScaleVideo((VDPLAYER_ZOOM_FACT)eZoom);
        }
#endif
    }
    else
    {
        return E_MPLAYER_RET_FAIL;
    }
    return E_MPLAYER_RET_OK;
}
#endif  // #if ENABLE_MPLAYER_MOVIE

//******************************************************************************
/// Change the zoom scale for the current playing media.
/// The zoom scale will set the normal (1x) for the next media.
/// Media player will call MApp_MPlayer_MovieZoom or MApp_MPlayer_PhotoZoom
/// according to the current media type.
/// @param  eZoom \b IN Specify the zoom scale.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_Zoom(enumMPlayerZoom eZoom)
{
    switch(m_eMediaType)
    {
#if ENABLE_MPLAYER_PHOTO
    case E_MPLAYER_TYPE_PHOTO:
        return(MApp_MPlayer_PhotoZoom(eZoom));
#endif  // #if ENABLE_MPLAYER_PHOTO
#if ENABLE_MPLAYER_MOVIE
    case E_MPLAYER_TYPE_MOVIE:
        return(MApp_MPlayer_MovieZoom(eZoom));
#endif  // #if ENABLE_MPLAYER_MOVIE
    default:
        break;
    }

    return E_MPLAYER_RET_UNSUPPORT;
}

#if ENABLE_MPLAYER_PHOTO
//******************************************************************************
/// Move zoomed video to the specific position.
/// It is only valid when the video is zoomed in.
/// The next played video will be reset to the center.
/// @param  eDirection \b IN Specify the direction of moving
/// @param  u16Offset  \b IN Specify the offset in pixels to move the photo.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_PhotoMove(enumMPlayerMoveDirection eDirection, U16 u16Offset)
{
    //Background MUSIC: need input data!
    MApp_MPlayer_BGM_Bitstream_Handle();

#if (PHOTO_SLIDE_SHOW_EFFECT)
    switch(m_ePhotoType[0])
    {
    case E_MPLAYER_SUBTYPE_JPG:
    #if (ENABLE_BMP)
    case E_MPLAYER_SUBTYPE_BMP:
    #endif
    #if (ENABLE_PNG)
    case E_MPLAYER_SUBTYPE_PNG:
    #endif
    #if (ENABLE_TIFF)
    case E_MPLAYER_SUBTYPE_TIFF:
    #endif
    #if (ENABLE_GIF)
    case E_MPLAYER_SUBTYPE_GIF:
    #endif
        MApp_Photo_MoveViewWindow((EN_PHOTO_DIRECTION)eDirection, u16Offset);
        break;
    default:
        return E_MPLAYER_RET_FAIL;
    }
#endif  // #if (PHOTO_SLIDE_SHOW_EFFECT)
    return E_MPLAYER_RET_OK;
}
#endif  // #if ENABLE_MPLAYER_PHOTO


#if ENABLE_MPLAYER_MOVIE
//******************************************************************************
/// Move zoomed video to the specific position.
/// It is only valid when the video is zoomed in.
/// The next played video will be reset to the center.
/// @param  eDirection \b IN Specify the direction of moving
/// @param  u16Offset  \b IN Specify the offset in pixels to move the movie.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_MovieMove(enumMPlayerMoveDirection eDirection, U16 u16Offset)
{
    S16 s16X, s16Y;

    s16X = m_s16VideoShiftX;
    s16Y = m_s16VideoShiftY;
    switch(eDirection)
    {
    case E_MPLAYER_DIRECTION_UP:
        s16Y -= u16Offset;
        break;
    case E_MPLAYER_DIRECTION_DOWN:
        s16Y += u16Offset;
        break;
    case E_MPLAYER_DIRECTION_LEFT:
        s16X -= u16Offset;
        break;
    case E_MPLAYER_DIRECTION_RIGHT:
        s16X += u16Offset;
        break;
    default:
        return E_MPLAYER_RET_FAIL;
    }
#if ENABLE_MPLAYER_MOVIE
    if(_MApp_MPlayer_IsSupportedMovie(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType))
    {
        if(MApp_VDPlayer_ShiftVideo(&s16X,
                                    &s16Y,
                                    0,
                                    0,
                                    (VDPLAYER_ZOOM_FACT)m_eZoom))
        {
            m_s16VideoShiftX = s16X;
            m_s16VideoShiftY = s16Y;
        }
    }
    else
#endif
    {
        return E_MPLAYER_RET_FAIL;
    }

    return E_MPLAYER_RET_OK;
}
#endif  // #if ENABLE_MPLAYER_MOVIE

//******************************************************************************
/// Move zoomed video or photo to the specific position.
/// It is only valid when the video or photo are zoomed in.
/// Media player will call MApp_MPlayer_MovieMove or MApp_MPlayer_PhotoMove
/// according to the current media type.
/// The next played video or photo will be reset to the center.
/// @param  eDirection \b IN Specify the direction of moving
/// @param  u16Offset  \b IN Specify the offset in pixels to move the video.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_Move(enumMPlayerMoveDirection eDirection, U16 u16Offset)
{
    switch(m_eMediaType)
    {
#if ENABLE_MPLAYER_PHOTO
    case E_MPLAYER_TYPE_PHOTO:
        return MApp_MPlayer_PhotoMove(eDirection, u16Offset);
#endif  // #if ENABLE_MPLAYER_PHOTO
#if ENABLE_MPLAYER_MOVIE
    case E_MPLAYER_TYPE_MOVIE:
        return MApp_MPlayer_MovieMove(eDirection, u16Offset);
#endif  // #if ENABLE_MPLAYER_MOVIE
    default:
        break;
    }
    return E_MPLAYER_RET_FAIL;
}

#if ENABLE_MPLAYER_MOVIE
//******************************************************************************
/// Change the movie playback mode. Reset to normal playback for the next movie file playing.
/// @param  ePlayMode \b IN Specify the play mode want to change.
///                       E_MPLAYER_MOVIE_NORMAL:    Enter normal play mode
///                       E_MPLAYER_MOVIE_PAUSE:     Pause
///                       E_MPLAYER_MOVIE_FF_2X:     Fast forward 2x
///                       E_MPLAYER_MOVIE_FF_4X:     Fast forward 4x
///                       E_MPLAYER_MOVIE_FF_8X:     Fast forward 8x
///                       E_MPLAYER_MOVIE_FF_16X:    Fast forward 16x
///                       E_MPLAYER_MOVIE_FF_32X:    Fast forward 32x
///                       E_MPLAYER_MOVIE_FB_2X:     Fast backward 2x
///                       E_MPLAYER_MOVIE_FB_4X:     Fast backward 4x
///                       E_MPLAYER_MOVIE_FB_8X:     Fast backward 8x
///                       E_MPLAYER_MOVIE_FB_16X:    Fast backward 16x
///                       E_MPLAYER_MOVIE_FB_32X:    Fast backward 32x
///                       E_MPLAYER_MOVIE_SF_2X:     Slow forward 2x
///                       E_MPLAYER_MOVIE_SF_4X:     Slow forward 4x
///                       E_MPLAYER_MOVIE_SF_8X:     Slow forward 8x
///                       E_MPLAYER_MOVIE_SF_16X:    Slow forward 16x
///                       E_MPLAYER_MOVIE_STEP:      STEP to the next video
///                       E_MPLAYER_MOVIE_STOP:      Stop playback
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_MovieChangePlayMode(enumMPlayerMoviePlayMode ePlayMode)
{
    enumMPlayerRet eRet = E_MPLAYER_RET_FAIL;

    if(ePlayMode == E_MPLAYER_MOVIE_NORMAL)
        MApi_XC_Enable_TwoInitFactor(TRUE, MAIN_WINDOW);
    else
        MApi_XC_Enable_TwoInitFactor(FALSE, MAIN_WINDOW);

    if(ePlayMode < E_MPLAYER_MOVIE_PLAY_MODE_NUM)
    {
#if ENABLE_MPLAYER_MOVIE
        if(_MApp_MPlayer_IsSupportedMovie(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType))
        {
#if ENABLE_SUBTITLE_DMP
        #if (ENALBE_RENDER_SUBTITLE_IN_TRICK_MODE==0)
            if(ePlayMode == E_MPLAYER_MOVIE_NORMAL || ePlayMode == E_MPLAYER_MOVIE_PAUSE)
            {
                _MApp_MPlayer_EnableSubtitleTask();
            }
            else
            {
                _MApp_MPlayer_DisableSubtitleTask();
            }
        #endif
#endif
            switch(ePlayMode)
            {
            case E_MPLAYER_MOVIE_NORMAL:
                if(MApp_VDPlayer_SetTrickMode(E_VDP_PLAY_MODE_NORMAL_PLAY, E_VDP_PLAY_SPEED_X1))
                {
                    eRet = E_MPLAYER_RET_OK;
                }

                if(m_eMoviePlayMode >= E_MPLAYER_MOVIE_FF_2X  &&
                   m_eMoviePlayMode <= E_MPLAYER_MOVIE_SF_16X)
                {
                #if (ENABLE_SMALL_BUF_SUBTITLE)
                    MApp_MPlayer_EnableReloadAppositeSubtitleBuf(TRUE);
                #endif
                    //turn-on NR after trick mode to fix display residue
                    #if (ENABLE_3D_PROCESS)
                    //fix FF Video become white
                    if(MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_MODE_NONE)
                    #endif
                        MApi_XC_Sys_PQ_SetNR((E_XC_PQ_3D_NR)ST_VIDEO.eNRMode.eNR, MAIN_WINDOW);

                    msAPI_Timer_Delayms(50); //vdplayer time stamp be stable
#if (TS_INTERNAL_SUBTITLE_BMP || TS_INTERNAL_SUBTITLE_PGS)
                    if ((u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP_TS)||(u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_PGS_TS))
                    {
                        if(m_eMoviePlayMode >= E_MPLAYER_MOVIE_FF_4X  &&
                           m_eMoviePlayMode <= E_MPLAYER_MOVIE_FB_16X)
                        {
                        #if(ENABLE_API_MMAP_GET_BUF) // Use MMAP API
                            U32 u32SubtitleBufAddr = 0, u32SubtitleBufSize = 0;
                            msAPI_MMAP_Get_BufInfo(E_BUFID_SUBTITLE, &u32SubtitleBufAddr, &u32SubtitleBufSize );
                            msAPI_Subtitle_Init_Queue(_PA2VA(u32SubtitleBufAddr), u32SubtitleBufSize);
                        #else
                            msAPI_Subtitle_Init_Queue(_PA2VA(((SUBTITLE_MEMORY_TYPE & MIU1) ? (SUBTITLE_ADR | MIU_INTERVAL) : (SUBTITLE_ADR))), SUBTITLE_LEN); // clr Q
                        #endif

                            msAPI_Subtitle_SetPageIDs(u16CPageID, u16APageID);
                        }
                        else
                        {
                            MApp_TS_Subtitle_Remove();
                        }
                    }
#endif
                }

                break;

            case E_MPLAYER_MOVIE_PAUSE:
                // 20100310:DanielWu: For garbage issue when Pause then Play
                //MApi_XC_FreezeImg(TRUE, MAIN_WINDOW);
                if(MApp_VDPlayer_Pause())
                {
                    eRet = E_MPLAYER_RET_OK;
                }
                break;

            case E_MPLAYER_MOVIE_FF_2X:
            case E_MPLAYER_MOVIE_FF_4X:
            case E_MPLAYER_MOVIE_FF_8X:
            case E_MPLAYER_MOVIE_FF_16X:
            case E_MPLAYER_MOVIE_FF_32X:
                if(MApp_VDPlayer_SetTrickMode(E_VDP_PLAY_MODE_FAST_FORWARD, E_VDP_PLAY_SPEED_X2+(EN_VDP_PLAY_SPEED)(ePlayMode-E_MPLAYER_MOVIE_FF_2X)))
                {
                    //disable NR while in trick mode to fix display residue
                    if(m_eMoviePlayMode == E_MPLAYER_MOVIE_NORMAL)
                    {
               		#if (ENABLE_3D_PROCESS)
                    //fix FF Video become white
               			if(MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_MODE_NONE)
                    #endif
                        	MApi_XC_Sys_PQ_SetNR( E_XC_PQ_3D_NR_OFF, MAIN_WINDOW );
                    }

                    eRet = E_MPLAYER_RET_OK;
                }
                break;

            case E_MPLAYER_MOVIE_FB_2X:
            case E_MPLAYER_MOVIE_FB_4X:
            case E_MPLAYER_MOVIE_FB_8X:
            case E_MPLAYER_MOVIE_FB_16X:
            case E_MPLAYER_MOVIE_FB_32X:
                if(MApp_VDPlayer_SetTrickMode(E_VDP_PLAY_MODE_SCAN_BACKWARD, E_VDP_PLAY_SPEED_X2+(EN_VDP_PLAY_SPEED)(ePlayMode-E_MPLAYER_MOVIE_FB_2X)))
                {
                    //disable NR while in trick mode to fix display residue
                    if(m_eMoviePlayMode == E_MPLAYER_MOVIE_NORMAL)
                    {
               		#if (ENABLE_3D_PROCESS)
                        //fix Fb Video become white
               			if(MApi_XC_Get_3D_Output_Mode() == E_XC_3D_OUTPUT_MODE_NONE)
                    #endif
                        	MApi_XC_Sys_PQ_SetNR( E_XC_PQ_3D_NR_OFF, MAIN_WINDOW );
                    }

                    eRet = E_MPLAYER_RET_OK;
                }
                break;

            case E_MPLAYER_MOVIE_SF_2X:
            case E_MPLAYER_MOVIE_SF_4X:
            case E_MPLAYER_MOVIE_SF_8X:
            case E_MPLAYER_MOVIE_SF_16X:
                if(MApp_VDPlayer_SetTrickMode(E_VDP_PLAY_MODE_SLOW_FORWARD, E_VDP_PLAY_SPEED_X2+(EN_VDP_PLAY_SPEED)(ePlayMode-E_MPLAYER_MOVIE_SF_2X)))
                {
                    eRet = E_MPLAYER_RET_OK;
                }
                break;

            case E_MPLAYER_MOVIE_STEP:
                if(MApp_VDPlayer_SetStep())
                {
                    eRet = E_MPLAYER_RET_OK;
                }
                break;

            case E_MPLAYER_MOVIE_STOP:
                msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
                MApi_XC_GenerateBlackVideo(ENABLE, MAIN_WINDOW);
                MApp_VDPlayer_Stop();

#if (ENABLE_SUBTITLE_DMP)
                if(m_u8ExternalSubtitleFileHandle != FCTRL_INVALID_FILE_HANDLE)
                {
                    msAPI_FCtrl_FileClose(m_u8ExternalSubtitleFileHandle);
                    m_u8ExternalSubtitleFileHandle = FCTRL_INVALID_FILE_HANDLE;
#if (ENABLE_INTERNAL_BMP_SUBTITLE || ENABLE_EXTERNAL_BMP_SUBTITLE)
                    msAPI_MpegSP_Dinit();
#endif
                }
#endif //#if (ENABLE_SUBTITLE_DMP)

                break;
            default:
                break;
            }
        }
#endif
        if(eRet == E_MPLAYER_RET_OK)
        {
            m_eMoviePlayMode = ePlayMode;
        }
    }

    return eRet;
}

enumMPlayerRet MApp_MPlayer_MovieSetRepeatAB(enumMPlayerMovieRepeatAB enAction, U32 u32RepeatTime)
{
    enumMPlayerRet eRet = E_MPLAYER_RET_FAIL;

    //need index table to support repeatAB(except TS & MPEG)
    if(MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_MAX_FB_SPEED) != 0)
    {
        if(MApp_VDPlayer_SetRepeatAB((EN_SET_REPEATAB)enAction))
        {
            m_enRepeatABMode = enAction;

            if(enAction == E_MPLAYER_MOVIE_SET_REPEAT_A)
            {
                m_u32MovieRepeatTime[0] = u32RepeatTime;
            }
            else if(enAction == E_MPLAYER_MOVIE_SET_REPEAT_B)
            {
                m_u32MovieRepeatTime[1] = u32RepeatTime;
#if (ENABLE_SUBTITLE_DMP)
                _MApp_MPlayer_ReinitRepeatABSubtitle();
#endif
            }
            else //cancel
            {
                m_u32MovieRepeatTime[0] = 0;
                m_u32MovieRepeatTime[1] = 0;
            }

            eRet = E_MPLAYER_RET_OK;
        }
    }
    return eRet;
}

//******************************************************************************
/// When play transport stream file, maybe it exists more than one program.
/// Users can use this function to change to the next program.
/// @param  bPlus \b IN Specify change direction.
///                     TRUE:   Plus
///                     FALSE:  Minus
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_MovieChangeNextProgram(BOOLEAN bPlus)
{
    UNUSED(bPlus);
    return E_MPLAYER_RET_FAIL;
}

//******************************************************************************
/// When play some movie file, maybe it exists more than one audio channel.
/// Users can use this function to change to the next audio channel.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_MovieChangeNextAudio(void)
{
    return E_MPLAYER_RET_FAIL;
}

enumMPlayerRet MApp_MPlayer_MovieChangeProgram(U8 u8ProgramIdx)
{
    if(MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_NB_PROGRAM)>1)
    {
        msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
        MApi_XC_GenerateBlackVideo(ENABLE, MAIN_WINDOW);

        if(MApp_VDPlayer_ChangeProgam(u8ProgramIdx))
        {
            m_eZoom = E_MPLAYER_ZOOM_1;
            m_s16VideoShiftX = m_s16VideoShiftY = 0;
            m_eMoviePlayMode = E_MPLAYER_MOVIE_NORMAL;
            return E_MPLAYER_RET_OK;
        }
    }
    return E_MPLAYER_RET_FAIL;
}

enumMPlayerRet MApp_MPlayer_MovieChangeAudioTrack(U8 u8TrackId)
{
    if((MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_NB_AUDIO_TRACK) > 1)
    && (MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_AUDIO_TRACK_ID) != u8TrackId))
    {
        if(MApp_VDPlayer_SetAudioTrackID(u8TrackId))
        {
            return E_MPLAYER_RET_OK;
        }
    }
    return E_MPLAYER_RET_FAIL;
}

#if (ENABLE_DIVX_PLUS == 1)
enumMPlayerRet MApp_MPlayer_MovieChangeTitle(U8 u8TitleId)
{
    //if (MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_NB_TITLE) > 1)
    if(MApp_VDPlayer_GetTitleID() == u8TitleId)
    {
        return E_MPLAYER_RET_FAIL;
    }

        //printf("timo change Title %d\n",u8TitleId);
        if (MApp_VDPlayer_SetTitleID(u8TitleId))
        {
        /*
            MApp_MPlayer_Stop();
            g_bChangeFile = TRUE;
            MApp_MPlayer_Play();
        */
            return E_MPLAYER_RET_OK;
        }
    return E_MPLAYER_RET_FAIL;
}

enumMPlayerRet MApp_MPlayer_MovieChangeEdition(U8 u8EditionId)
{
    if (MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_NB_EDITION) > 1)
    {
        if(MApp_VDPlayer_GetEditionID() == u8EditionId)
        {
            return E_MPLAYER_RET_FAIL;
        }

        if (MApp_VDPlayer_SetEditionID(u8EditionId))
        {
            //MApp_MPlayer_Stop();
            //g_bChangeFile = TRUE;
            //MApp_MPlayer_Play();
            return E_MPLAYER_RET_OK;
        }
    }
    return E_MPLAYER_RET_FAIL;
}

enumMPlayerRet MApp_MPlayer_MovieChangeChapter(U8 u8ChapterId)
{
    if (MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_NB_CHAPTER) > 1)
    {
        MApp_VDPlayer_SetSubtitleShow(E_SUBTITLE_STATE_COMMAND_NOT_SHOW);
        NOTIFY(E_MPLAYER_NOTIFY_HIDE_SUBTITLE, NULL);

        if (MApp_VDPlayer_SetChapterID(u8ChapterId))
        {
#if (ENABLE_SUBTITLE_DMP)
    //                if(m_eMoviePlayMode >= E_MPLAYER_MOVIE_FF_2X  &&
    //                   m_eMoviePlayMode <= E_MPLAYER_MOVIE_FB_16X)
            {
                if(m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SUBIDX)
                {
                    if(MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CUR_TIME) >m_u32NextExternalSubtitleStartTime)
                    {
                        _MApp_MPlayer_SetMpegSubtitle();
                    }
                }
                else if(MApp_VDPlayer_IsTextSubtitle())
                {
                    MApp_VDPlayer_TextSubtitleInit();
                }

                MApp_VDPlayer_SetSubtitleShow(E_SUBTITLE_STATE_COMMAND_SHOW);
                msAPI_Timer_Delayms(50); //vdplayer time stamp be stable
            }
#endif //#if (ENABLE_SUBTITLE_DMP)
            return E_MPLAYER_RET_OK;
        }
        MApp_VDPlayer_SetSubtitleShow(E_SUBTITLE_STATE_COMMAND_SHOW);
    }
    return E_MPLAYER_RET_FAIL;
}

enumMPlayerRet MApp_MPlayer_MovieChangeAutoGenChapter(U8 u8ChapterId)
{

    MApp_VDPlayer_SetSubtitleShow(E_SUBTITLE_STATE_COMMAND_NOT_SHOW);
    NOTIFY(E_MPLAYER_NOTIFY_HIDE_SUBTITLE, NULL);

    if (MApp_VDPlayer_SetAutoGenChapterID(u8ChapterId))
    {
#if (ENABLE_SUBTITLE_DMP)
    //                if(m_eMoviePlayMode >= E_MPLAYER_MOVIE_FF_2X  &&
    //                   m_eMoviePlayMode <= E_MPLAYER_MOVIE_FB_16X)
            {
                if(m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SUBIDX)
                {
                    if(MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CUR_TIME) >m_u32NextExternalSubtitleStartTime)
                    {
                        _MApp_MPlayer_SetMpegSubtitle();
                    }
                }
                else if(MApp_VDPlayer_IsTextSubtitle())
                {
                    MApp_VDPlayer_TextSubtitleInit();
                }

                MApp_VDPlayer_SetSubtitleShow(E_SUBTITLE_STATE_COMMAND_SHOW);
                //msAPI_Timer_Delayms(50); //vdplayer time stamp be stable
            }
#endif //#if (ENABLE_SUBTITLE_DMP)
        return E_MPLAYER_RET_OK;
    }

    MApp_VDPlayer_SetSubtitleShow(E_SUBTITLE_STATE_COMMAND_SHOW);
    return E_MPLAYER_RET_FAIL;
}
#endif

#if (ENABLE_SUBTITLE_DMP)
enumMPlayerRet MApp_MPlayer_MovieChangeSubtitleTrack(U8 u8TrackId)
{
#if ENABLE_INTERNAL_AND_EXTERNAL_SUBTITLE
    U16 u16ExternalSubtitleNum = MApp_MPlayer_GetInfo(E_MPLAYER_EXT_SUBTITLE_INFO_NB_TRACK);
    U16 u16TotalSubtitleNum = u16ExternalSubtitleNum + MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_NB_SUBTITLE_TRACK);

    if(u8TrackId < u16TotalSubtitleNum)
    {
        if(u8TrackId < u16ExternalSubtitleNum)
        {
            if((m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL)==0)
            {
                m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 |= (E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL);
            }
        }
        else
        {
            if(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL)
            {
                m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 &=(enumMPlayerKnlFlags1)~(E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL);
            }
            u8TrackId -= u16ExternalSubtitleNum;
        }
    }
    else
    {
        return E_MPLAYER_RET_FAIL;
    }
#endif

    if(E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL & m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1)
    {
        if(MApp_MPlayer_SetSubtitleTrackID(u8TrackId))
        {
            _MApp_MPlayer_HideSubtitle();

            m_eExternalSubtitleType = (enumMPlayerSubtitleType)MApp_MPlayer_GetInfo(E_MPLAYER_EXT_SUBTITLE_INFO_SUBTITLE_TYPE);
            m_u16ExternalSubtitleIdx = 0;

        #if (ENABLE_SUBTITLE_SUBIDX)
            if(m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SUBIDX)
            {
                MApp_VDPlayer_SetSuspendInternalSubtitle2Queue(TRUE);
                _MApp_MPlayer_SetMpegSubtitle();
                m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 &=(enumMPlayerKnlFlags1)~(E_MPLAYER_KNL_FLG1_SUBTITLE_TEXT );
            }
            else
        #endif //#if (ENABLE_SUBTITLE_SUBIDX)
            {
                m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 |= (E_MPLAYER_KNL_FLG1_SUBTITLE_TEXT );
                m_u8AliveSubtitleNum = 0; //clear for text subtitle
                MApp_MPlayer_ResetAliveTextSubtitleStatus();
            }

            return E_MPLAYER_RET_OK;
        }
    }
    else
    {
        if(MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_NB_SUBTITLE_TRACK)>0)
        {
            if(MApp_VDPlayer_SetSubtitleTrackID(u8TrackId))
            {
                _MApp_MPlayer_HideSubtitle();
                m_eExternalSubtitleType = E_MPLAYER_SUBTITLE_INVALID;

                if(MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CURRENT_SUBTITLE_TEXT))
                {
                    if( MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CURRENT_SUBTITLE_ISUNICODE) )
                    {
                        m_eSubtitleCodingType = E_MPLAYER_SUBTITLE_CODING_UNICODE;
                    }
                    else
                    {
                        m_eSubtitleCodingType = E_MPLAYER_SUBTITLE_CODING_ASC;
                    }

                    m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 |= (E_MPLAYER_KNL_FLG1_SUBTITLE_TEXT );
                    m_u8AliveSubtitleNum = 0; //clear for text subtitle
                }
                else
                {
                    MApp_VDPlayer_SetSuspendInternalSubtitle2Queue(FALSE);
                    m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 &=(enumMPlayerKnlFlags1)~(E_MPLAYER_KNL_FLG1_SUBTITLE_TEXT );
                }
                return E_MPLAYER_RET_OK;
            }
        }
    }
    return E_MPLAYER_RET_FAIL;
}
#endif //#if (ENABLE_SUBTITLE_DMP)

#endif  // #if ENABLE_MPLAYER_MOVIE

#if ENABLE_MPLAYER_PHOTO
//******************************************************************************
/// Change the photo playback mode.
/// Reset to normal playback for the next photo file playing.
/// @param  ePlayMode \b IN Specify the play mode want to change.
///                       E_MPLAYER_PHOTO_NORMAL: Normal mode
///                       E_MPLAYER_PHOTO_PAUSE:  Pause
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_PhotoChangePlayMode(enumMPlayerPhotoPlayMode ePlayMode)
{
    if(m_eMediaType == E_MPLAYER_TYPE_PHOTO)
    {
        // do nothing if asked to paused when paused or asked to be normal when already in normal
        if (((ePlayMode == E_MPLAYER_PHOTO_PAUSE) && (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaPlayingStatus & E_MPLAYER_PHOTO_STATE_PAUSE))
        ||  ((ePlayMode == E_MPLAYER_PHOTO_NORMAL) && (!(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaPlayingStatus & E_MPLAYER_PHOTO_STATE_PAUSE))))
        {
            return E_MPLAYER_RET_OK;
        }

        switch(ePlayMode)
        {
        case E_MPLAYER_PHOTO_NORMAL:
            m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaPlayingStatus &= (enumMediaPlayingStatus)~E_MPLAYER_PHOTO_STATE_PAUSE;
            _MApp_MPlayer_PlayAgain(E_MPLAYER_FOREGROUND_PLAYER);
            if (m_u8DecodedPics > 1)
            {
                m_u8DecodedPics--;
            }
            break;
        case E_MPLAYER_PHOTO_PAUSE:
            m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaPlayingStatus |= E_MPLAYER_PHOTO_STATE_PAUSE;
            MApp_Photo_Stop();
            //MApp_Photo_Buf_Init();
            m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_FILE_INIT;
            break;
        default:
            break;
        }
        return E_MPLAYER_RET_OK;
    }
    return E_MPLAYER_RET_FAIL;
}

//******************************************************************************
/// Rotate the current playing photo on the screen.
/// Reset to normal for the next photo file playing.
/// @param  eRotate \b IN Specify the degree to rotate.
///                     E_MPLAYER_PHOTO_ROTATE_0:   rotate 0 degree
///                     E_MPLAYER_PHOTO_ROTATE_90:  rotate 90 degree
///                     E_MPLAYER_PHOTO_ROTATE_180: rotate 180 degree
///                     E_MPLAYER_PHOTO_ROTATE_270: rotate 270 degree
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_PhotoRotate(enumMPlayerPhotoRotate eRotate)
{
    //Background MUSIC: need input data!
    MApp_MPlayer_BGM_Bitstream_Handle();

    // Should refer to photo type of current displayed photo for rotation.
#if (PHOTO_SLIDE_SHOW_EFFECT)
    switch(m_ePhotoType[0])
    {
    case E_MPLAYER_SUBTYPE_JPG:
    #if (ENABLE_BMP)
    case E_MPLAYER_SUBTYPE_BMP:
    #endif
    #if (ENABLE_PNG)
    case E_MPLAYER_SUBTYPE_PNG:
    #endif
    #if (ENABLE_TIFF)
    case E_MPLAYER_SUBTYPE_TIFF:
    #endif
    #if (ENABLE_GIF)
    case E_MPLAYER_SUBTYPE_GIF:
    #endif
        MApp_Photo_Rotate((EN_PHOTO_ROTATION)eRotate);
        return E_MPLAYER_RET_OK;
    default:
        break;
    }
#endif  // #if (PHOTO_SLIDE_SHOW_EFFECT)

    return E_MPLAYER_RET_FAIL;
}
#endif  // #if ENABLE_MPLAYER_PHOTO

#if ENABLE_MPLAYER_MUSIC
//******************************************************************************
/// Change the music playback mode.
/// Reset to normal playback for the next music file playing.
/// @param  ePlayMode \b IN Specify the play mode want to change.
///                     E_MPLAYER_MUSIC_NORMAL: Enter normal play mode
///                     E_MPLAYER_MUSIC_PAUSE:  Pause
///                     E_MPLAYER_MUSIC_FF:     Fast forward
///                     E_MPLAYER_MUSIC_FB:     Fast backward
///                     E_MPLAYER_MUSIC_STOP:   Stop playback
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_MusicChangePlayMode(enumMPlayerMusicPlayMode ePlayMode)
{
    enumMPlayerRet eRet = E_MPLAYER_RET_FAIL;
    // Removed this condition : because UI may need to change BGM play mode
    //   in other media type, such as PHOTO.
    #if !ENABLE_BGM
    if(m_eMediaType == E_MPLAYER_TYPE_MUSIC)
    #endif
    {
        switch(ePlayMode)
        {
        case E_MPLAYER_MUSIC_NORMAL:
            if(m_eMusicPlayMode == E_MPLAYER_MUSIC_PAUSE)
            {
                switch(m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType)
                {
#if (ENABLE_WMA)
                case E_MPLAYER_SUBTYPE_WMA:
                    MApp_WMA_Resume();
                    break;
#endif
                default:
                    MApp_Music_Resume();
                    break;
                }

                eRet = E_MPLAYER_RET_OK;
            }
            else
            {
                switch(m_eMusicPlayMode)
                {
                case E_MPLAYER_MUSIC_FF_2X:
                case E_MPLAYER_MUSIC_FF_4X:
                case E_MPLAYER_MUSIC_FF_8X:
                case E_MPLAYER_MUSIC_FF_16X:
                case E_MPLAYER_MUSIC_FB_2X:
                case E_MPLAYER_MUSIC_FB_4X:
                case E_MPLAYER_MUSIC_FB_8X:
                case E_MPLAYER_MUSIC_FB_16X:
                    switch(m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType)
                    {
#if (ENABLE_WMA)
                    case E_MPLAYER_SUBTYPE_WMA:
                        if(MApp_WMA_FastForwardBackward(TRUE, EN_WMA_SPEED_X1))
                        {
                            eRet = E_MPLAYER_RET_OK;
                        }
                        break;
#endif
                    default:
                        if(MApp_Music_FastForwardBackward(TRUE, EN_MP3_SPEED_X1))
                        {
                            eRet = E_MPLAYER_RET_OK;
                        }
                        break;
                    }
                    break;
                default:
                    break;
                }
           }
            break;

        case E_MPLAYER_MUSIC_PAUSE:
            switch(m_eMusicPlayMode)
            {
            case E_MPLAYER_MUSIC_NORMAL:
            case E_MPLAYER_MUSIC_FF_2X:
            case E_MPLAYER_MUSIC_FF_4X:
            case E_MPLAYER_MUSIC_FF_8X:
            case E_MPLAYER_MUSIC_FF_16X:
            case E_MPLAYER_MUSIC_FB_2X:
            case E_MPLAYER_MUSIC_FB_4X:
            case E_MPLAYER_MUSIC_FB_8X:
            case E_MPLAYER_MUSIC_FB_16X:
                switch(m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType)
                {
#if (ENABLE_WMA)
                case E_MPLAYER_SUBTYPE_WMA:
                    if(MApp_WMA_Pause())
                    {
                        eRet = E_MPLAYER_RET_OK;
                    }
                    break;
#endif
                default:
                    if(MApp_Music_Pause())
                    {
                        eRet = E_MPLAYER_RET_OK;
                    }
                    break;
                }
                break;
            default:
                break;
            }
            break;

        case E_MPLAYER_MUSIC_FF_2X:
        case E_MPLAYER_MUSIC_FF_4X:
        case E_MPLAYER_MUSIC_FF_8X:
        case E_MPLAYER_MUSIC_FF_16X:
            switch(m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType)
            {
#if (ENABLE_WMA)
            case E_MPLAYER_SUBTYPE_WMA:
                if(MApp_WMA_FastForwardBackward(TRUE,
                    (EN_WMA_SPEED)((U16)EN_WMA_SPEED_X2 + (U16)ePlayMode - (U16)E_MPLAYER_MUSIC_FF_2X)))
                {
                    eRet = E_MPLAYER_RET_OK;
                }
                break;
#endif
            default:
                if(MApp_Music_FastForwardBackward(TRUE,
                    (EN_MP3_SPEED)((U16)EN_MP3_SPEED_X2 + (U16)ePlayMode - (U16)E_MPLAYER_MUSIC_FF_2X)))
                {
                    eRet = E_MPLAYER_RET_OK;
                }
                break;
            }
            break;

        case E_MPLAYER_MUSIC_FB_2X:
        case E_MPLAYER_MUSIC_FB_4X:
        case E_MPLAYER_MUSIC_FB_8X:
        case E_MPLAYER_MUSIC_FB_16X:
            switch(m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType)
            {
#if (ENABLE_WMA)
            case E_MPLAYER_SUBTYPE_WMA:
                if(MApp_WMA_FastForwardBackward(FALSE,
                    (EN_WMA_SPEED)((U16)EN_WMA_SPEED_X2 + (U16)ePlayMode - (U16)E_MPLAYER_MUSIC_FB_2X)))
                {
                    eRet = E_MPLAYER_RET_OK;
                }
                break;
#endif
            default:
                if(MApp_Music_FastForwardBackward(FALSE,
                    (EN_MP3_SPEED)((U16)EN_MP3_SPEED_X2 + (U16)ePlayMode - (U16)E_MPLAYER_MUSIC_FB_2X)))
                {
                    eRet = E_MPLAYER_RET_OK;
                }
                break;
            }
            break;

        case E_MPLAYER_MUSIC_STOP:
            switch(m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType)
            {
#if (ENABLE_WMA)
            case E_MPLAYER_SUBTYPE_WMA:
                MApp_WMA_Stop();
                break;
#endif
            default:
                MApp_Music_Stop();
                break;
            }
            eRet = E_MPLAYER_RET_OK;
            break;
        default:
            break;
        }

        if(eRet == E_MPLAYER_RET_OK)
        {
            m_eMusicPlayMode = ePlayMode;
        }
    }
    return eRet;
}
#endif  // #if ENABLE_MPLAYER_MUSIC


#if ENABLE_MPLAYER_TEXT
//******************************************************************************
/// Change playing text files to the next page.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_TextNextPage(void)
{
    if(MApp_Text_NextPage())
    {
        NOTIFY(E_MPLAYER_NOTIFY_TEXT_NEXT_PAGE, NULL);
        return E_MPLAYER_RET_OK;
    }
    return E_MPLAYER_RET_FAIL;
}

//******************************************************************************
/// Change playing text files to the previous page.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_TextPrevPage(void)
{
    if(MApp_Text_PrevPage())
    {
        NOTIFY(E_MPLAYER_NOTIFY_TEXT_PREV_PAGE, NULL);
        return E_MPLAYER_RET_OK;
    }
    return E_MPLAYER_RET_FAIL;
}

//******************************************************************************
/// Stop current text file playback.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_TextStop(void)
{
    TEXT_FileClose();
    return E_MPLAYER_RET_FAIL;
}
#endif
//******************************************************************************
/// Capture the current file to be boot-up logo.
/// @return enumMPlayerRet
//******************************************************************************
#if (DISPLAY_LOGO)
#if ENABLE_MPLAYER_PHOTO
#if (!ENABLE_MPLAYER_CAPTURE_LOGO)
enumMPlayerRet MApp_MPlayer_CaptureLogo(void)
{
    return E_MPLAYER_RET_FAIL;
}
enumMPlayerRet MApp_MPlayer_CaptureLogoByAddr(U32 u32SrcAddr, U32 u32Pitch, U32 u32Width, U32 u32Height, GFX_Buffer_Format SrcFormat)
{
    UNUSED(u32SrcAddr);
    UNUSED(u32Pitch);
    UNUSED(u32Width);
    UNUSED(u32Height);
    UNUSED(SrcFormat);
    return E_MPLAYER_RET_FAIL;
}
#else
enumMPlayerRet MApp_MPlayer_CaptureLogo(void)
{
    U32 u32PhotoAddr, u32PhotoLen;
    U32 u32LogoAddr, u32LogoLen;
    U32 u32MemPoolAddr, u32MemPoolLen;
    U32 u32BuffAddr, u32BuffLen;
    U16 u16PhotoWidth, u16PhotoHeight;
    enumMPlayerRet bRet = E_MPLAYER_RET_FAIL;


    u32BuffAddr = (U32)((MAD_JPEG_OUT_MEMORY_TYPE & MIU1) ? (MAD_JPEG_OUT_ADR | MIU_INTERVAL) : (MAD_JPEG_OUT_ADR));
    u32BuffLen = MAD_JPEG_OUT_LEN;

    // reserve 1M for logo
    u32LogoLen = 1024 * 1024;

    // reserve 512K for memory pool
    u32MemPoolLen = 512 * 1024;

    // check if there is enough memory
    if (u32LogoLen + u32MemPoolLen > u32BuffLen)
    {
        __ASSERT(0);
        return E_MPLAYER_RET_FAIL;
    }

    // buffer assign
    u32LogoAddr = u32BuffAddr;
    u32MemPoolAddr = u32LogoAddr + u32LogoLen;

    // get inter buffer from mapp_photo
    MApp_Photo_GetInterBuffInfo(&u16PhotoWidth, &u16PhotoHeight, &u32PhotoAddr, &u32PhotoLen);

    // stop current photo activity
    MApp_Photo_Stop();

    // set encode memory
    MApp_Photo_MemCfg(
            u32PhotoAddr, u32PhotoLen,
            u32LogoAddr, u32LogoLen,
            u32MemPoolAddr, u32MemPoolLen, u32MemPoolLen);

    //encode dest need aligned
    u16PhotoWidth = ALIGN_16(u16PhotoWidth);
    u16PhotoHeight = ALIGN_8(u16PhotoHeight);

    // encode jpeg
    if (MApp_Photo_EncodeMemory_Init(u16PhotoWidth, u16PhotoHeight, NULL))
    {
        EN_RET enPhotoRet;

        while ((enPhotoRet = MApp_Photo_Main()) == EXIT_PHOTO_DECODING)
        {
#if (WATCH_DOG == ENABLE)
            msAPI_Timer_ResetWDT();
#endif
        }

        if ((enPhotoRet == EXIT_PHOTO_DECODE_DONE) && (MApp_Photo_GetErrCode() == E_PHOTO_ERR_NONE))
        {
            bRet = _MApp_MPlayer_SaveLogo(u32LogoAddr, MApp_Photo_GetInfo(E_PHOTO_INFO_SIZE), USER_LOGO_FLASH_START_ADDR, USER_LOGO_LENGTH_PER_LOGO) ? E_MPLAYER_RET_OK : E_MPLAYER_RET_FAIL;
        }
    }

    MApp_Photo_Stop();
#if (OBA2 == 1)
    if (msAPI_NPlayer_IsPlaying(E_MPLAYER_MEDIA_PHOTO))
    {
        return bRet;
    }
    else
#endif
    {
        // ask photo to re-decode last photo
        _MApp_MPlayer_PlayAgain(E_MPLAYER_FOREGROUND_PLAYER);
        if (m_u8DecodedPics > 1)
        {
            m_u8DecodedPics--;
        }
    }
    return bRet;
}
//For AP use
enumMPlayerRet MApp_MPlayer_CaptureLogoByAddr(U32 u32SrcAddr, U32 u32Pitch, U32 u32Width, U32 u32Height, GFX_Buffer_Format SrcFormat)
{
#if (OBA2 == 1)
    U32 u32PhotoAddr, u32PhotoLen;
    U32 u32LogoAddr, u32LogoLen;
    U32 u32MemPoolAddr, u32MemPoolLen;
    U32 u32BuffAddr, u32BuffLen;
    U16 u16PhotoWidth, u16PhotoHeight;
    U32 u32Aligned, u32MIU;
    enumMPlayerRet bRet = E_MPLAYER_RET_FAIL;


    u32BuffAddr = ((MAD_JPEG_OUT_MEMORY_TYPE & MIU1) ? (MAD_JPEG_OUT_ADR | MIU_INTERVAL) : (MAD_JPEG_OUT_ADR));
    u32BuffLen = MAD_JPEG_OUT_LEN;

    // reserve 1M for logo
    u32LogoLen = 1024 * 1024;

    // reserve 512K for memory pool
    u32MemPoolLen = 512 * 1024;

    // check if there is enough memory
    if (u32LogoLen + u32MemPoolLen > u32BuffLen)
    {
        __ASSERT(0);
        return E_MPLAYER_RET_FAIL;
    }

    // buffer assign
    u32LogoAddr = u32BuffAddr;
    u32MemPoolAddr = u32LogoAddr + u32LogoLen;

    // get inter buffer from mapp_photo
    MApp_Photo_GetInterBuffInfo(&u16PhotoWidth, &u16PhotoHeight, &u32PhotoAddr, &u32PhotoLen);
    if(!MAdp_SYS_GetMemoryInfo("CAPTURE_LOGO", (MS_U32*)&u32PhotoAddr, (MS_U32*)&u32PhotoLen, (MS_U32*)&u32Aligned, (MS_U32*)&u32MIU))
    {
        MPLAYER_DBG(printf("can't find memory setting of CAPTURE_LOGO\n"));
        return E_MPLAYER_RET_FAIL;
    }
    MPLAYER_DBG(printf("src BuffAddr:%x; size:%x; srcw:%d;h:%d;panelsize:%d,%d\n",u32SrcAddr,u32PhotoLen,u32Width,u32Height,u16PhotoWidth,u16PhotoHeight));
    if(SrcFormat == GFX_FMT_ARGB8888 || SrcFormat == GFX_FMT_RGB565||SrcFormat == GFX_FMT_YUV422)
    {
        GEBitBltInfo BitbltInfo;
        GEPitBaseInfo PitBaseInfo;
        U16 u16DstW,u16DstH;

        // 1. Clear internal buffer to black.
        msAPI_GE_ClearFrameBufferByWord((U32)u32PhotoAddr,
                                       u32PhotoLen,
                                       0x80008000);
        // after clear frame buffer, flush cmd
        MApi_GFX_FlushQueue();

        if((U32)u16PhotoWidth * u32Height >
           (U32)u16PhotoHeight * u32Width)
        {
            u16DstW = (U16)(u32Width * u16PhotoHeight /
                            u32Height);
            u16DstH = u16PhotoHeight;
        }
        else
        {
            u16DstH = (U16)(u32Height * u16PhotoWidth /
                            u32Width);
            u16DstW = u16PhotoWidth;
        }

        MPLAYER_DBG(printf(" \n u16DstW=%d,  u16DstH=%d",u16DstW, u16DstH ));
        MPLAYER_DBG(printf(" \n ADJUSTED_PANEL_WIDTH=%d,  PANEL_HEIGHT=%d\n",u16PhotoWidth, u16PhotoHeight ));

        MApi_GFX_EnableAlphaBlending(FALSE);
        memset(&BitbltInfo, 0, sizeof(GEBitBltInfo));
        memset(&PitBaseInfo, 0, sizeof(GEPitBaseInfo));

        msAPI_GE_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YUYV,  GFX_YUV_YUYV); //test to mark for color error

        BitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
        BitbltInfo.BmpFlag = GFXDRAW_FLAG_DEFAULT;
        BitbltInfo.dst_fm = GFX_FMT_YUV422;
        BitbltInfo.src_fm = SrcFormat;
        BitbltInfo.BitbltCoordinate.v2_x = 0;
        BitbltInfo.BitbltCoordinate.v2_y = 0;
        BitbltInfo.BitbltCoordinate.direction = 0;

        BitbltInfo.BitbltCoordinate.width =u16DstW & 0xfffe;
        BitbltInfo.BitbltCoordinate.height = u16DstH& 0xfffe;

        BitbltInfo.BitbltCoordinate.v0_x =(u16PhotoWidth - u16DstW)/2;
        BitbltInfo.BitbltCoordinate.v0_y = (u16PhotoHeight - u16DstH)/2;

        BitbltInfo.src_width= u32Width&0xfffe;
        BitbltInfo.src_height=u32Height&0xfffe;
        PitBaseInfo.sb_pit = u32Pitch;

        PitBaseInfo.db_pit = ((u16PhotoWidth+15)&0xfff0)*2;
        PitBaseInfo.sb_base = u32SrcAddr; //inter buf
        PitBaseInfo.db_base = u32PhotoAddr;//RGB_PIC_DISPLAY_FB_ADDR; //display buf

        if(u16PhotoWidth > u16PhotoHeight)
        {
            msAPI_OSD_SetClipWindow(0, 0, u16PhotoWidth, u16PhotoWidth);
        }
        else
        {
            msAPI_OSD_SetClipWindow(0, 0, u16PhotoHeight, u16PhotoHeight);
        }


        msAPI_GE_SetNearestMode(FALSE);


        msAPI_GE_BitBlt(&BitbltInfo, &PitBaseInfo);
        // after BitBlt, flush cmd
        MApi_GFX_FlushQueue();

        MPLAYER_DBG(printf("MApp_Photo_Bitblt\n"));
        MPLAYER_DBG(printf("stBitbltInfo: \n"));
        MPLAYER_DBG(printf("\ttype flag: %u\n", BitbltInfo.BitBltTypeFlag));
        MPLAYER_DBG(printf("\tbmp flag: %u\n", BitbltInfo.BmpFlag));
        MPLAYER_DBG(printf("\tdest fmt: %u\n", BitbltInfo.dst_fm));
        MPLAYER_DBG(printf("\tsrc fmt: %u\n", BitbltInfo.src_fm));
        MPLAYER_DBG(printf("\tbmp hnd: %d\n", BitbltInfo.bmphandle));
        MPLAYER_DBG(printf("\tsrc width: %u\n", BitbltInfo.src_width));
        MPLAYER_DBG(printf("\tsrc height: %u\n", BitbltInfo.src_height));
        MPLAYER_DBG(printf("\tcoord v0x: %u\n", BitbltInfo.BitbltCoordinate.v0_x));
        MPLAYER_DBG(printf("\tcoord v0y: %u\n", BitbltInfo.BitbltCoordinate.v0_y));
        MPLAYER_DBG(printf("\tcoord width: %u\n", BitbltInfo.BitbltCoordinate.width));
        MPLAYER_DBG(printf("\tcoord height: %u\n", BitbltInfo.BitbltCoordinate.height));
        MPLAYER_DBG(printf("\tcoord v2x: %u\n", BitbltInfo.BitbltCoordinate.v2_x));
        MPLAYER_DBG(printf("\tcoord v2y: %u\n", BitbltInfo.BitbltCoordinate.v2_y));
        MPLAYER_DBG(printf("\tcoord direct: %u\n", BitbltInfo.BitbltCoordinate.direction));
        MPLAYER_DBG(printf("stPitBaseInfo: \n"));
        MPLAYER_DBG(printf("\tsrc pitch: %x\n",PitBaseInfo.sb_pit));
        MPLAYER_DBG(printf("\tdst pitch: %x\n",PitBaseInfo.db_pit));
        MPLAYER_DBG(printf("\tsrc base: %x\n",PitBaseInfo.sb_base));
        MPLAYER_DBG(printf("\tdst base: %x\n",PitBaseInfo.db_base));
    }
    else
    {
         MPLAYER_DBG(printf("Src format is not supported!.\n"));
         return E_MPLAYER_RET_FAIL;
    }
    // stop current photo activity
    MApp_Photo_Stop();

    // set encode memory
    MApp_Photo_MemCfg(
            u32PhotoAddr, u32PhotoLen,
            u32LogoAddr, u32LogoLen,
            u32MemPoolAddr, u32MemPoolLen, u32MemPoolLen);

    //encode dest need aligned
    u16PhotoWidth = ALIGN_16(u16PhotoWidth);
    u16PhotoHeight = ALIGN_8(u16PhotoHeight);

    // encode jpeg
    if (MApp_Photo_EncodeMemory_Init(u16PhotoWidth, u16PhotoHeight, NULL))
    {
        EN_RET enPhotoRet;

        while ((enPhotoRet = MApp_Photo_Main()) == EXIT_PHOTO_DECODING)
        {
#if (WATCH_DOG == ENABLE)
            msAPI_Timer_ResetWDT();
#endif
        }

        if ((enPhotoRet == EXIT_PHOTO_DECODE_DONE) && (MApp_Photo_GetErrCode() == E_PHOTO_ERR_NONE))
        {
            bRet = _MApp_MPlayer_SaveLogo(u32LogoAddr, MApp_Photo_GetInfo(E_PHOTO_INFO_SIZE), USER_LOGO_FLASH_START_ADDR, USER_LOGO_LENGTH_PER_LOGO) ? E_MPLAYER_RET_OK : E_MPLAYER_RET_FAIL;
        }
    }

    MApp_Photo_Stop();

    return bRet;
#else
    UNUSED(u32SrcAddr);
    UNUSED(u32Pitch);
    UNUSED(u32Width);
    UNUSED(u32Height);
    UNUSED(SrcFormat);
    MPLAYER_DBG(printf("This interface is only for obama AP use!.\n"));
    return E_MPLAYER_RET_FAIL;
#endif
}
#endif

#endif  // #if ENABLE_MPLAYER_PHOTO
#endif  // #if (DISPLAY_LOGO)

#if ENABLE_MPLAYER_MUSIC
//******************************************************************************
/// Start to capture the current playing music to be boot-up music.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_StartCaptureBootUpMusic(void)
{
#if (ENABLE_MPLAYER_CAPTURE_MUSIC)
    if((m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_MP3)
        && (m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_MUSIC_PLAY
       || m_eMusicPreviewState == E_MUSIC_PREVIEW_RUNNING))
    {
        MApp_Music_StartCapture();
        bMusicRecording = TRUE;
        return E_MPLAYER_RET_OK;
    }
#endif // #if (ENABLE_MPLAYER_CAPTURE_MUSIC)

    return E_MPLAYER_RET_FAIL;
}

//******************************************************************************
/// End to capture the current playing music to be boot-up music.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_EndCaptureBootUpMusic(void)
{
#if (ENABLE_MPLAYER_CAPTURE_MUSIC)
    if((m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_MP3)
        && (m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_MUSIC_PLAY
            || m_eMusicPreviewState == E_MUSIC_PREVIEW_RUNNING))
    {
        MApp_Music_StopCapture();
        bMusicRecording = FALSE;
        return E_MPLAYER_RET_OK;
    }
#endif // #if (ENABLE_MPLAYER_CAPTURE_MUSIC)

    return E_MPLAYER_RET_FAIL;
}
#endif  // #if ENABLE_MPLAYER_MUSIC

//******************************************************************************
/// This function go to the user specified position of playing file in milliseconds.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_SetPlayPosition(U32 u32TimeInMS)
{
    enumMPlayerRet eRet=E_MPLAYER_RET_FAIL;

    switch(m_eMediaType)
    {
#if ENABLE_MPLAYER_MOVIE
    case E_MPLAYER_TYPE_MOVIE:
        if(MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_MAX_FB_SPEED) != 0)
        {
            if(MApp_VDPlayer_SetPlayPosition(u32TimeInMS))
            {
                if(E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL & m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1)
                {
                #if (ENABLE_SUBTITLE_SUBIDX)
                    if(m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SUBIDX)
                    {
                        _MApp_MPlayer_SetMpegSubtitle();
                    }
                #endif
                #if (ENABLE_SMALL_BUF_SUBTITLE)
                    MApp_MPlayer_EnableReloadAppositeSubtitleBuf(TRUE);
                #endif
                }
                eRet = E_MPLAYER_RET_OK;
            }
        }
        break;
#else
    UNUSED(u32TimeInMS);
#endif
    default:
        break;
    }
    return eRet;
}

//******************************************************************************
/// This function tell media player to go to menu state machine in top state
/// machines. Users need to set the correct menu index and show correct menu
/// by themselves.
/// @return enumMPlayerRet
//******************************************************************************
#if 0//ndef ZUI
enumMPlayerRet MApp_MPlayer_GotoMenuState(void)
{
    //modified for usb disk insert/remove
    if(m_eMPlayerStateMachineState == STATE_MPLAYER_WAIT ||
        m_eMPlayerStateMachineState == STATE_MPLAYER_INIT)
    {
        m_eMPlayerStateMachineState = STATE_MPLAYER_EXIT_TO_MENU;
        return E_MPLAYER_RET_OK;
    }
    else
    {
        return E_MPLAYER_RET_FAIL;
    }
}
#endif  // #if ZUI

#if 0//ENABLE_MPLAYER_MOVIE
//******************************************************************************
/// Scale the video to the current setting
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_ScaleVideo(void)
{
    switch(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType)
    {
    case E_MPLAYER_SUBTYPE_MPEG4:
        MApp_VDPlayer_ScaleVideo((VDPLAYER_ZOOM_FACT)m_eZoom);
        return E_MPLAYER_RET_OK;

    case E_MPLAYER_SUBTYPE_MPEG:
        msAPI_MPEG2_ScaleVideo((MPEG2_ZOOM_FACT)m_eZoom);
        return E_MPLAYER_RET_OK;
    }

    return E_MPLAYER_RET_FAIL;
}
#endif  // #if ENABLE_MPLAYER_MOVIE

//=============================================================================/
//============================ Query Interface ================================
//=============================================================================/

//******************************************************************************
/// Read back the file information.
/// @param  eBegin     \b IN Specify set the base of file index is current directory or current page
/// @param  u16FileIdx \b IN Specify the file index offset.
/// @param  pInfo      \b OUT Return the file information.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_QueryFileInfo(enumMPlayerFileIndexBegin eBegin, U16 u16FileIdx, MPlayerFileInfo *pInfo)
{
    U32 u32Addr;
    MPlayerFileInfo *pFileInfo;

     if(eBegin == E_MPLAYER_INDEX_CURRENT_PAGE)
     {
         u16FileIdx += m_u16CurPage1stFileIdx;
     }
     else if(eBegin != E_MPLAYER_INDEX_CURRENT_DIRECTORY)
     {
         return E_MPLAYER_RET_FAIL;
     }

     if(u16FileIdx >= m_u16TotalFileNum)
     {
         return E_MPLAYER_RET_FAIL;
     }

     u32Addr = (U32)((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR)) + (U32)u16FileIdx*sizeof(MPlayerFileInfo);

     pFileInfo = (MPlayerFileInfo *)_PA2VA(u32Addr);

 #if (HIGH_SPEED_BROWSER)
     if(!pFileInfo->bLongFileNameValid)
     {
         U8 u8Len;

         // Get long file name from file entry.
         u8Len = MApp_FileBrowser_GetLongFileNameByFileEntry(
                     &pFileInfo->fileEntry,
                     (U32)(&pInfo->u8LongFileName[0]),
                     (FILE_INFO_LONG_FILENAME_SIZE/2-1));
         u8Len = (u8Len > (FILE_INFO_LONG_FILENAME_SIZE/2-1)) ?
                     FILE_INFO_LONG_FILENAME_SIZE/2-1:
                     u8Len;
         pInfo->u8LongFileName[u8Len*2] = 0;
         pInfo->u8LongFileName[u8Len*2+1] = 0;
         memcpy(&pFileInfo->u8LongFileName[0], &pInfo->u8LongFileName[0], FILE_INFO_LONG_FILENAME_SIZE);
         pFileInfo->bLongFileNameValid = TRUE;
     }
 #endif
     memcpy(pInfo, pFileInfo, sizeof(MPlayerFileInfo));

     return E_MPLAYER_RET_OK;
}

//******************************************************************************
/// Read back device connection status.
/// Media player returns an MPlayerDeviceStatus array.
/// This array size is NUM_OF_SUPPORT_DEVICES.
/// @param  pStatus \b OUT Return the device status.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_QueryDeviceConnectionStatus(MPlayerDeviceStatus **pStatus)
{
    *pStatus = m_MPlayerDeviceStatus;
    return E_MPLAYER_RET_OK;
}

//******************************************************************************
/// Read back drive connection status.
/// @param  pu32DriveStatus \b OUT Return the drive status.
///                                Bit 0 represents the status of the 1st drive.
///                                When the bit is set, the connection status
///                                is OK.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_QueryDriveConnectionStatus(U32 *pu32DriveStatus)
{
    *pu32DriveStatus = m_u32DriveStatus;
    return E_MPLAYER_RET_OK;
}

//******************************************************************************
/// Read back the current page index for file browser.
/// @return MPLAYER_INVALID_INDEX Failed to read the current page index.
///         Other                 Correct page index
//******************************************************************************
U16 MApp_MPlayer_QueryCurrentPageIndex(void)
{
#if REMOVE_DRIVE_SELECT_TO_FILE_LIST
    if(!bIsDriveSelected) 
    {
    	return (U16)(MApp_DMP_GetDrvPageIdx() - 1);
    }
    else
#endif
	{
    	return m_u16CurPageIdx;
	}
}

#ifdef MEDIA_PLAYER_HIGHLIGHT_CHANGE
//******************************************************************************
/// Read back the current playing file index for file browser.
/// @param  N/A
/// @return Correct playing file index
//******************************************************************************
U16 MApp_MPlayer_QueryCurrentPlayingFileIndex(void)
{
    enumMPlayerIdx ePlayerIdx = E_MPLAYER_FOREGROUND_PLAYER;

#if ENABLE_MPLAYER_MUSIC
    if (m_eMediaType == E_MPLAYER_TYPE_MUSIC)
    {
        ePlayerIdx = E_MPLAYER_BACKGROUND_PLAYER;
    }
#endif  // #if ENABLE_MPLAYER_MUSIC
    if((MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_SELECTED) ||
       (MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_SELECTED_FROM_CURRENT))
    {
        return MApp_MPlayer_QueryCurrentPlayingListFileIndex();
    }
    else
    {
        if(m_eMediaType == E_MPLAYER_TYPE_PHOTO)
        {
            if(m_u32PhotoCurrentDisplayedIdx == 0)
            {
                return m_MPlayerInfo[ePlayerIdx].u16PlayingIdx;
            }
            else
            {
                return (U16)m_u32PhotoCurrentDisplayedIdx;
            }
        }
        return m_MPlayerInfo[ePlayerIdx].u16PlayingIdx;
    }
}

//******************************************************************************
/// Read back the current playing drive index for file browser.
/// @param  N/A
/// @return Correct playing drive index
//******************************************************************************
U8 MApp_MPlayer_QueryCurrentPlayingDriveIndex(void)
{
    return (U8)m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].u16CurrentDrive;
}

U16 MApp_MPlayer_QueryCurrentPlayingListFileIndex(void)
{
    U16 i = 0;
    MPlayerPlayListInfo *pstPlayListInfo, stPlayFileInfo;
    U16  u16PlayListNum;
    U32 u32XdataWindowBase;
    enumMPlayerIdx ePlayerIdx = E_MPLAYER_FOREGROUND_PLAYER;
    U8 end = 0;
    U16 u16PlayingIdx;

#if ENABLE_MPLAYER_MUSIC
    if(m_eMediaType == E_MPLAYER_TYPE_MUSIC)
    {
        ePlayerIdx = E_MPLAYER_BACKGROUND_PLAYER;
    }
#endif
#if ENABLE_MPLAYER_PHOTO
    if(m_eMediaType == E_MPLAYER_TYPE_PHOTO)
    {
        u16PlayingIdx = (U16)m_u32PhotoCurrentDisplayedIdx;
    }
    else
#endif
    {
        u16PlayingIdx = m_MPlayerInfo[ePlayerIdx].u16PlayingIdx;
    }

    msAPI_MIU_SetRoundRobin(FALSE);  // If the file is JPG, will enable round robin.

    if(_MApp_MPlayer_GetPlayListAddressByMediaType(m_eMediaType, &u32XdataWindowBase)==FALSE)
    {
        return FALSE;
    }

    u16PlayListNum = m_u16SelectedFileNum[m_eMediaType];

    //MPLAYER_DBG(printf("    - u8PlayListNum = %bu\n",u8PlayListNum));
    if(u16PlayListNum == 0)
    {
        return FALSE;
    }

    pstPlayListInfo = (MPlayerPlayListInfo *) (_PA2VA(u32XdataWindowBase));

    memcpy(&stPlayFileInfo, &PLAY_LIST(u16PlayingIdx), sizeof(MPlayerPlayListInfo));

    for (i=0; i < NUM_OF_MAX_DIRECTORY_DEPTH+1; i++)
    {
        if (stPlayFileInfo.u16PlayListPath[i] == MPLAYER_INVALID_INDEX)
        {
            end = i;
            break;
        }
    }

    if (0 == end && MPLAYER_INVALID_INDEX != stPlayFileInfo.u16PlayListPath[0] )
        end = NUM_OF_MAX_DIRECTORY_DEPTH+1;

    if (end == 0)
        return 0;
    else
    {
        return (stPlayFileInfo.u16PlayListPath[end-1] + m_u16BufDirectoryNum);
    }
}

//******************************************************************************
/// Set the current playing file index for file browser.
/// @param  u16FileIndex - current playing file index.
/// @return N/A.
//******************************************************************************
void MApp_MPlayer_SetCurrentPlayingFileIndex(U16 u16FileIndex)
{
    enumMPlayerIdx ePlayerIdx = E_MPLAYER_FOREGROUND_PLAYER;

#if ENABLE_MPLAYER_MUSIC
    if (m_eMediaType == E_MPLAYER_TYPE_MUSIC)
    {
        ePlayerIdx = E_MPLAYER_BACKGROUND_PLAYER;
    }
#endif  // #if ENABLE_MPLAYER_MUSIC

    if (u16FileIndex >= m_u16TotalFileNum)
    {
        m_MPlayerInfo[ePlayerIdx].u16PlayingIdx = m_u16TotalFileNum - 1;
        return;
    }
    else if (u16FileIndex < m_u16BufDirectoryNum)
    {
        m_MPlayerInfo[ePlayerIdx].u16PlayingIdx = m_u16TotalFileNum - 1;
        return;
    }
    m_MPlayerInfo[ePlayerIdx].u16PlayingIdx = u16FileIndex;
}

U16  MApp_MPlayer_QueryCurrentPlayingList()
{
    enumMPlayerIdx ePlayerIdx = E_MPLAYER_FOREGROUND_PLAYER;

#if ENABLE_MPLAYER_MUSIC
    if (m_eMediaType == E_MPLAYER_TYPE_MUSIC)
    {
        ePlayerIdx = E_MPLAYER_BACKGROUND_PLAYER;
    }
#endif  // #if ENABLE_MPLAYER_MUSIC

    if(m_eMediaType == E_MPLAYER_TYPE_PHOTO)
    {
        return (U16)m_u32PhotoCurrentDisplayedIdx;
    }

    return m_MPlayerInfo[ePlayerIdx].u16PlayingIdx;
}
#if ENABLE_MPLAYER_MUSIC
U16  MApp_MPlayer_QueryBGMPlayingList(void)
{
    return m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].u16PlayingIdx;
}
#endif  // #if ENABLE_MPLAYER_MUSIC
void MApp_MPlayer_SetCurrentPlayingList(U16 u16PLIndex)
{
    U16 u16PlayListNum;
    enumMPlayerIdx ePlayerIdx = E_MPLAYER_FOREGROUND_PLAYER;

#if ENABLE_MPLAYER_MUSIC
    if (m_eMediaType == E_MPLAYER_TYPE_MUSIC)
    {
        ePlayerIdx = E_MPLAYER_BACKGROUND_PLAYER;
    }
#endif  // #if ENABLE_MPLAYER_MUSIC

    u16PlayListNum = m_u16SelectedFileNum[m_eMediaType];

    if(u16PlayListNum == 0)
    {
        m_MPlayerInfo[ePlayerIdx].u16PlayingIdx = 0;
    }

    if (u16PLIndex >= u16PlayListNum)
        m_MPlayerInfo[ePlayerIdx].u16PlayingIdx = u16PlayListNum - 1;
    else
        m_MPlayerInfo[ePlayerIdx].u16PlayingIdx = u16PLIndex;
}

BOOLEAN MApp_MPlayer_IsPathDifferent(U16 u16PLIndex)
{
    U16 i = 0;
    MPlayerPlayListInfo *pstPlayListInfo, stPlayFileInfo;
    U16  u16PlayListNum;
    U32 u32XdataWindowBase;
    enumMPlayerIdx ePlayerIdx = E_MPLAYER_FOREGROUND_PLAYER;
    BOOLEAN ret = FALSE;
    U8 end = 0;

#if ENABLE_MPLAYER_MUSIC
    if(m_eMediaType == E_MPLAYER_TYPE_MUSIC)
    {
        ePlayerIdx = E_MPLAYER_BACKGROUND_PLAYER;
    }
#endif

    msAPI_MIU_SetRoundRobin(FALSE);  // If the file is JPG, will enable round robin.

    if(_MApp_MPlayer_GetPlayListAddressByMediaType(m_eMediaType, &u32XdataWindowBase)==FALSE)
    {
        return FALSE;
    }

    u16PlayListNum = m_u16SelectedFileNum[m_eMediaType];

    //MPLAYER_DBG(printf("    - u16PlayListNum = %u\n",u16PlayListNum));
    if(u16PlayListNum == 0)
    {
        return ret;
    }

    pstPlayListInfo = (MPlayerPlayListInfo *) (_PA2VA(u32XdataWindowBase));
    memcpy(&stPlayFileInfo, &PLAY_LIST(u16PLIndex), sizeof(MPlayerPlayListInfo));

    if (stPlayFileInfo.u16Drive != m_u16CurDriveIdx)
    {
        ret = TRUE;
        return ret;
    }

    for (i=0; i < NUM_OF_MAX_DIRECTORY_DEPTH+1; i++)
    {
        if (stPlayFileInfo.u16PlayListPath[i] == MPLAYER_INVALID_INDEX)
        {
            end = i;
            break;
        }
    }

    if (m_u16CurDirectoryDepth != (end - 1))
    {
        ret = TRUE;
    }
    else
    {
        for (i = 0; i < (end - 1); i++)
        {
        #if ENABLE_MPLAYER_SORT
            if (m_u16CurDirectoryPhy[i] != stPlayFileInfo.u16PlayListPath[i])
        #else
            if (m_u16CurDirectory[i] != stPlayFileInfo.u16PlayListPath[i])
        #endif
            {
                ret = TRUE;
                break;
            }
        }
    }

    return ret;
}

BOOLEAN MApp_MPlayer_Change2TargetPath(U16 u16PLIndex)
{
#if EN_DMP_SEARCH_ALL
    MPLAYER_DBG(printf("In Search all mode, do not allow to change path.\n"));
    return TRUE;
#endif

    U16 i = 0;
    MPlayerPlayListInfo *pstPlayListInfo, stPlayFileInfo;
    U16  u16PlayListNum;
    U32 u32XdataWindowBase;
    enumMPlayerIdx ePlayerIdx = E_MPLAYER_FOREGROUND_PLAYER;
    BOOLEAN ret = FALSE;
    BOOLEAN bChangePath = FALSE;
    U8 end = 0;

#if ENABLE_MPLAYER_MUSIC
    if(m_eMediaType == E_MPLAYER_TYPE_MUSIC)
    {
        ePlayerIdx = E_MPLAYER_BACKGROUND_PLAYER;
    }
#endif

    msAPI_MIU_SetRoundRobin(FALSE);  // If the file is JPG, will enable round robin.

    if(_MApp_MPlayer_GetPlayListAddressByMediaType(m_eMediaType, &u32XdataWindowBase)==FALSE)
    {
        return FALSE;
    }

    u16PlayListNum = m_u16SelectedFileNum[m_eMediaType];

    //MPLAYER_DBG(printf("    - u16PlayListNum = %u\n",u16PlayListNum));
    if(u16PlayListNum == 0)
    {
        return ret;
    }

    pstPlayListInfo = (MPlayerPlayListInfo *) (_PA2VA(u32XdataWindowBase));
    memcpy(&stPlayFileInfo, &PLAY_LIST(u16PLIndex), sizeof(MPlayerPlayListInfo));

    for (i=0; i < NUM_OF_MAX_DIRECTORY_DEPTH+1; i++)
    {
        if (stPlayFileInfo.u16PlayListPath[i] == MPLAYER_INVALID_INDEX)
        {
            end = i;
            break;
        }
    }

    if (0 == end && MPLAYER_INVALID_INDEX != stPlayFileInfo.u16PlayListPath[0] )
        end = NUM_OF_MAX_DIRECTORY_DEPTH+1;

    if (stPlayFileInfo.u16Drive != m_u16CurDriveIdx)
    {
#if 0
        _MApp_MPlayer_Browser_ChangeBrowsingDrive(
            &m_u8UserBrowserHandle,
            m_u16CurDriveIdx,
            stPlayFileInfo.u16Drive);
        m_u16CurDriveIdx = stPlayFileInfo.u16Drive;
#else
        MApp_MPlayer_ConnectDrive(stPlayFileInfo.u16Drive);
        bChangePath = TRUE;
#endif
    }
    else // in the same drive, check if the same path
    {
        if (m_u16CurDirectoryDepth != (end - 1))
        {
            bChangePath = TRUE;
        }
        else
        {
            for (i = 0; i < (end - 1); i++)
            {
                if (m_u16CurDirectory[i] != stPlayFileInfo.u16PlayListPath[i])
                {
                    bChangePath = TRUE;
                    break;
                }
            }
        }
    }

    if(bChangePath)
    {
        //m_u16BufDirectoryDepth = MPLAYER_INVALID_INDEX;
        if(end>0)
        {
            _MApp_MPlayer_Change2TargetDirectory(end-1, &stPlayFileInfo.u16PlayListPath[0]);
        }
        else
        {
            __ASSERT(0);
        }
    }

    _MApp_MPlayer_Browser_EnumCurDirectory();
    m_u16CurFileIdx = 0;
    m_u16CurPage1stFileIdx = 0;
    m_u16CurPageIdx =0;

    if(m_u16TotalFileNum && m_u16FilesPerPage>0)
    {
        m_u16TotalPageNum = (m_u16TotalFileNum+m_u16FilesPerPage-1) /m_u16FilesPerPage;
    }

    return TRUE;
}

#endif  // MEDIA_PLAYER_HIGHLIGHT_CHANGE

#if 0
//******************************************************************************
/// Query the current file system type from file browser.
/// @param  N/A
/// @return FILE_SYSTEM_TYPE_NONE=0, FILE_SYSTEM_TYPE_FAT=1,FILE_SYSTEM_TYPE_NTFS=2
//******************************************************************************
#endif
//******************************************************************************
/// Query the current file system type from file browser.
/// @return EN_FILE_SYSTEM_TYPE
//******************************************************************************
EN_FILE_SYSTEM_TYPE MApp_MPlayer_QueryCurrentFileSystemType(void)
{
    return MApp_FileBrowser_GetCurrentFileSystemType();
}

//******************************************************************************
/// Query the file system format by drive index.
/// @return EN_FILE_SYSTEM_FORMAT
//******************************************************************************
EN_FILE_SYSTEM_FORMAT MApp_MPlayer_QueryFileSystemFormatByDriveIndex(U8 u8DriveIndex)
{
    return msAPI_FCtrl_GetFileSystemFormatByDriveIndex(u8DriveIndex);
}

//******************************************************************************
/// Read back the current file index for file browser.
/// @param  eBegin \b IN Specify set the base of file index is current directory or current page
/// @return MPLAYER_INVALID_INDEX Failed to read the current file index.
///         Other                 Correct file index
//******************************************************************************
U16 MApp_MPlayer_QueryCurrentFileIndex(enumMPlayerFileIndexBegin eBegin)
{
    if(m_u16CurFileIdx != MPLAYER_INVALID_INDEX)
    {
        if(eBegin == E_MPLAYER_INDEX_CURRENT_PAGE)
        {
            //Add protection - When we just call MApp_MPlayer_EnterThumbnailMode(), m_u16CurFileIdx = 0
            // and m_u16CurPage1stFileIdx will be directory number, it causes return value become very big(6553x).
            return((m_u16CurFileIdx > m_u16CurPage1stFileIdx ? m_u16CurFileIdx - m_u16CurPage1stFileIdx:0));
        }
        else if(eBegin == E_MPLAYER_INDEX_CURRENT_DIRECTORY)
        {
            return m_u16CurFileIdx;
        }
    }
    return MPLAYER_INVALID_INDEX;
}

//******************************************************************************
/// Read back the total pages for file browser.
/// @return MPLAYER_INVALID_INDEX Failed to read the total pages.
///         Other                 Correct total pages for the current directory.
//******************************************************************************
U16 MApp_MPlayer_QueryTotalPages(void)
{
#if REMOVE_DRIVE_SELECT_TO_FILE_LIST
    if(!bIsDriveSelected) 
    {
		return (U16)(MApp_MPlayer_QueryTotalDriveNum()/9 + 1);
    }
    else
#endif
	{
    	return m_u16TotalPageNum;
	}
}

#if ENABLE_MPLAYER_MOVIE
//******************************************************************************
/// Check whether there is dedicated SRT subtitle file for the current media
/// file. This function is only valid in the notification of
/// E_MPLAYER_NOTIFY_BEFORE_PLAY_ONE_FILE.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_IsCurrentExternalSubtitleAvailable(void)
{
    if(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL)
    {
        return E_MPLAYER_RET_OK;
    }

    return E_MPLAYER_RET_FAIL;
}
#endif  // #if ENABLE_MPLAYER_MOVIE

#if ENABLE_MPLAYER_MUSIC
//******************************************************************************
/// Check whether there is dedicated LRC lyric file for the current media file.
/// This function is only valid in the notification of
/// E_MPLAYER_NOTIFY_BEFORE_PLAY_ONE_FILE.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_IsCurrentLRCLyricAvailable(void)
{
    if(m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_LYRIC_VALID)
    {
        return E_MPLAYER_RET_OK;
    }

    return E_MPLAYER_RET_FAIL;
}
#endif  // #if ENABLE_MPLAYER_MUSIC

//******************************************************************************
/// Get the current media type from media player.
/// @return enumMPlayerMediaType
//******************************************************************************
enumMPlayerMediaType MApp_MPlayer_QueryCurrentMediaType(void)
{
#if ((OBA2 == 1) && (ENABLE_BABAO_PLAYER == ENABLE))
    if (msAPI_NPlayer_IsPlaying(E_MPLAYER_MEDIA_MOVIE))
        return E_MPLAYER_TYPE_MOVIE;
    else
#endif
        return m_eMediaType;
}

//******************************************************************************
/// Get the current play mode from media player.
/// @return enumMPlayerPlayMode
//******************************************************************************
enumMPlayerPlayMode MApp_MPlayer_QueryPlayMode(void)
{
    return m_ePlayMode;
}

#if ENABLE_MPLAYER_PHOTO
//******************************************************************************
/// Get the photo information for the current photo file.
/// @param  pInfo \b OUT Return the photo information.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_QueryPhotoInfo(MPlayerPhotoInfo *pInfo)
{
    memcpy(pInfo, &m_photoInfo, sizeof(MPlayerPhotoInfo));

    return E_MPLAYER_RET_OK;
}
#endif  // #if ENABLE_MPLAYER_PHOTO

//******************************************************************************
/// Get the media sub type for the current media file.
/// @return enumMPlayerMediaSubType
//******************************************************************************
enumMPlayerMediaSubType MApp_MPlayer_QueryCurrentFileMediaSubType(void)
{
    MPlayerFileInfo fileInfo;

    if (0
#if ENABLE_MPLAYER_PHOTO
            || ((m_eMediaType == E_MPLAYER_TYPE_PHOTO)
                    && (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_PHOTO_PLAY))
#endif
            )
    {
        return m_ePhotoType[0];
    }
    else if (0
#if ENABLE_MPLAYER_MOVIE
            || ((m_eMediaType == E_MPLAYER_TYPE_MOVIE)
                    && (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_MOVIE_PLAY))
#endif  // #if ENABLE_MPLAYER_MOVIE
#if ENABLE_MPLAYER_TEXT
            || ((m_eMediaType == E_MPLAYER_TYPE_TEXT)
                    && (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_TEXT_PLAY))
#endif  // #if ENABLE_MPLAYER_TEXT
            )
    {
        return m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType;
    }
    else if (0
#if ENABLE_MPLAYER_MUSIC
            || ((m_eMediaType == E_MPLAYER_TYPE_MUSIC)
                    && (m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_MUSIC_PLAY))
#endif  // #if ENABLE_MPLAYER_MUSIC
            )
    {
        return m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType;
    }
    else
    {
        if(MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,
                                       m_u16CurFileIdx,
                                       &fileInfo) == E_MPLAYER_RET_OK)
        {
#if ENABLE_MPLAYER_PHOTO
    #if (ENABLE_BMP)
            if(IS_BMP_FILE(fileInfo.u8ExtFileName))
            {
                return E_MPLAYER_SUBTYPE_BMP;
            }
    #endif
            if(IS_JPG_FILE(fileInfo.u8ExtFileName))
            {
                return E_MPLAYER_SUBTYPE_JPG;
            }
    #if (ENABLE_PNG)
            if(IS_PNG_FILE(fileInfo.u8ExtFileName))
            {
                return E_MPLAYER_SUBTYPE_PNG;
            }
    #endif
    #if (ENABLE_TIFF)
            if(IS_TIFF_FILE(fileInfo.u8ExtFileName))
            {
                return E_MPLAYER_SUBTYPE_TIFF;
            }
    #endif
    #if (ENABLE_GIF)
            if(IS_GIF_FILE(fileInfo.u8ExtFileName))
            {
                return E_MPLAYER_SUBTYPE_GIF;
            }
    #endif
#endif  // #if ENABLE_MPLAYER_PHOTO
#if ENABLE_MPLAYER_MUSIC
            if(IS_MP3_FILE(fileInfo.u8ExtFileName))
            {
                return E_MPLAYER_SUBTYPE_MP3;
            }

    #if (ENABLE_FLAC)
            if(IS_FLAC_FILE(fileInfo.u8ExtFileName))
            {
                return E_MPLAYER_SUBTYPE_FLAC;
            }
    #endif
    #if (ENABLE_AC3)
            if(IS_AC3_FILE(fileInfo.u8ExtFileName))
            {
                return E_MPLAYER_SUBTYPE_AC3;
            }
    #endif
    #if (ENABLE_AAC)
            if(IS_AAC_FILE(fileInfo.u8ExtFileName))
            {
                return E_MPLAYER_SUBTYPE_AAC;
            }
    #endif
    #if (ENABLE_WAV)
            if(IS_WAV_FILE(fileInfo.u8ExtFileName))
            {
                return E_MPLAYER_SUBTYPE_WAV;
            }
    #endif
    #if (ENABLE_WMA)
            if(IS_WMA_FILE(fileInfo.u8ExtFileName))
            {
                return E_MPLAYER_SUBTYPE_WMA;
            }
    #endif  // #if ENABLE_WMA
    #if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
            if(IS_LOAS_FILE(fileInfo.u8ExtFileName))
            {
                return E_MPLAYER_SUBTYPE_LOAS;
            }
    #endif  // #if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
    #if (ENABLE_OGG)
            if(IS_OGG_FILE(fileInfo.u8ExtFileName))
            {
                return E_MPLAYER_SUBTYPE_OGG;
            }
    #endif
    #if (ENABLE_AMR)
            if(IS_AMR_FILE(fileInfo.u8ExtFileName))
            {
                return E_MPLAYER_SUBTYPE_AMR;
            }
            if(IS_AWB_FILE(fileInfo.u8ExtFileName))
            {
                return E_MPLAYER_SUBTYPE_AWB;
            }
    #endif
#endif  // #if ENABLE_MPLAYER_MUSIC
#if ENABLE_MPLAYER_MOVIE
            if(IS_MPEG2_FILE(fileInfo.u8ExtFileName))
            {
                return E_MPLAYER_SUBTYPE_MPEG;
            }
            if(IS_MPEG4_FILE(fileInfo.u8ExtFileName))
            {
                return E_MPLAYER_SUBTYPE_MPEG4;
            }
            if(IS_TS_FILE(fileInfo.u8ExtFileName))
            {
                return E_MPLAYER_SUBTYPE_TS;
            }
            if(IS_RM_FILE(fileInfo.u8ExtFileName))
            {
                return E_MPLAYER_SUBTYPE_RM;
            }
#if (ENABLE_WMV)
            if(IS_WMV_FILE(fileInfo.u8ExtFileName))
            {
                return E_MPLAYER_SUBTYPE_WMV;
            }
#endif
#if (ENABLE_DVD)
            if(IS_DVD_FILE(fileInfo.u8ExtFileName))
            {
                return E_MPLAYER_SUBTYPE_DVD;
            }
#endif

#endif  // #if ENABLE_MPLAYER_MOVIE
#if ENABLE_MPLAYER_TEXT
            if(IS_TXT_FILE(fileInfo.u8ExtFileName))
            {
                return E_MPLAYER_SUBTYPE_TEXT;
            }
#endif  // #if ENABLE_MPLAYER_TEXT
        }

        return E_MPLAYER_SUBTYPE_INVALID;
    }
}

//******************************************************************************
/// Get the media sub type for the current media file.
/// @return enumMPlayerMediaSubType
//******************************************************************************
enumMPlayerMediaSubType MApp_MPlayer_QueryCurrentMediaSubType(void)
{
    return m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType;
}

#if ENABLE_MPLAYER_MOVIE
#if ( KEEP_UNUSED_FUNC == 1 )
//******************************************************************************
/// Get the movie video type.
/// @return enumMPlayerMovieVideoType
//******************************************************************************
enumMPlayerMovieVideoType MApp_MPlayer_QueryCurrentMovieVideoType(void)
{
    // TODO: Implement it later.

    return E_MPLAYER_VIDEO_TYPE_INVALID;
}
#endif

//******************************************************************************
/// Get the movie audio type.
/// @return enumMPlayerMovieAudioType
//******************************************************************************
enumMPlayerMovieAudioType MApp_MPlayer_QueryCurrentMovieAudioType(void)
{
    // TODO: Implement it later.

    return E_MPLAYER_AUDIO_TYPE_INVALID;
}
#endif  // #if ENABLE_MPLAYER_MOVIE

#if ENABLE_MPLAYER_MOVIE
//******************************************************************************
/// Get the play mode for current playing movie.
/// @return enumMPlayerMoviePlayMode
//******************************************************************************
enumMPlayerMoviePlayMode MApp_MPlayer_QueryMoviePlayMode(void)
{
    return m_eMoviePlayMode;
}
#if ENABLE_DIVX_PLUS
void MApp_MPlayer_SetMoviePlayMode(enumMPlayerMoviePlayMode eMoviePlayMode)
{
    m_eMoviePlayMode = eMoviePlayMode;
}
#endif
#endif  // #if ENABLE_MPLAYER_MOVIE

#if ENABLE_MPLAYER_PHOTO
//******************************************************************************
/// Get the pay mode for the current playing photo.
/// @return enumMPlayerPhotoPlayMode
//******************************************************************************
enumMPlayerPhotoPlayMode MApp_MPlayer_QueryPhotoPlayMode(void)
{
    if(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaPlayingStatus & E_MPLAYER_PHOTO_STATE_PAUSE)
    {
        return E_MPLAYER_PHOTO_PAUSE;
    }
    else
    {
        return E_MPLAYER_PHOTO_NORMAL;
    }
}
#endif  // #if ENABLE_MPLAYER_PHOTO

#if ENABLE_MPLAYER_MUSIC
//******************************************************************************
/// Get the pay mode for the current playing music.
/// @return enumMPlayerMusicPlayMode
//******************************************************************************
enumMPlayerMusicPlayMode MApp_MPlayer_QueryMusicPlayMode(void)
{
    return m_eMusicPlayMode;
}
#endif  // #if ENABLE_MPLAYER_MUSIC

#if ENABLE_MPLAYER_MOVIE
//******************************************************************************
/// Read back the program number in the current playing movie.
/// @eturn MPLAYER_INVALID_INDEX: Failed to get the information.
///        Other                : Return the program number in the current playing movie.
//******************************************************************************
U16 MApp_MPlayer_QueryMovieProgramNum(void)
{
    return((U16)MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_NB_PROGRAM));
}

//******************************************************************************
/// Read back the audio channel number in the current playing movie.
/// @return MPLAYER_INVALID_INDEX: Failed to get the information.
///         Other                : return the audio channel number in the current playing movie.
//******************************************************************************
U16 MApp_MPlayer_QueryMovieAudioChannelNum(void)
{
    return((U16)MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_NB_AUDIO_TRACK));
}

#if (ENABLE_DIVX_PLUS == 1)
U16 MApp_MPlayer_QueryMovieTitleNum(void)
{
    return((U16)MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_NB_TITLE));
}

U16 MApp_MPlayer_QueryMovieEditionNum(void)
{
    return((U16)MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_NB_EDITION));
}

U16 MApp_MPlayer_QueryMovieChapterNum(void)
{
    return((U16)MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_NB_CHAPTER));
}
#endif

#if (ENABLE_SUBTITLE_DMP)
U16 MApp_MPlayer_QueryMovieSubtitleNum(void)
{
#if ENABLE_INTERNAL_AND_EXTERNAL_SUBTITLE
    U16 u16ExternalSubtitleNum = MApp_MPlayer_GetInfo(E_MPLAYER_EXT_SUBTITLE_INFO_NB_TRACK);
    U16 u16InternalSubtitleNum = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_NB_SUBTITLE_TRACK);
    return u16ExternalSubtitleNum + u16InternalSubtitleNum;
#else
    if(E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL & m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1)
    {
        return((U16)MApp_MPlayer_GetInfo(E_MPLAYER_EXT_SUBTITLE_INFO_NB_TRACK));
    }
    else
    {
        return((U16)MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_NB_SUBTITLE_TRACK));
    }
#endif
}
#endif //#if (ENABLE_SUBTITLE_DMP)

U16 MApp_MPlayer_QueryMovieCurProgramIdx(void)
{
    return((U16)MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_PROGRAM_ID));
}

U16 MApp_MPlayer_QueryMovieCurAudioTrackIdx(void)
{
    return((U16)MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_AUDIO_TRACK_ID));
}

#if (ENABLE_SUBTITLE_DMP)
U16 MApp_MPlayer_QueryMovieCurSubtitleTrackIdx(void)
{
#if ENABLE_INTERNAL_AND_EXTERNAL_SUBTITLE
    if(E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL & m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1)
    {
        return((U16)MApp_MPlayer_GetInfo(E_MPLAYER_EXT_SUBTITLE_INFO_TRACK_ID));
    }
    else
    {
        U16 u16ExternalSubtitleNum = MApp_MPlayer_GetInfo(E_MPLAYER_EXT_SUBTITLE_INFO_NB_TRACK);
        return(u16ExternalSubtitleNum + (U16)MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_SUBTITLE_TRACK_ID));
    }
#else
    if(E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL & m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1)
    {
        return((U16)MApp_MPlayer_GetInfo(E_MPLAYER_EXT_SUBTITLE_INFO_TRACK_ID));
    }
    else
    {
        return((U16)MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_SUBTITLE_TRACK_ID));
    }
#endif
}
#endif //#if (ENABLE_SUBTITLE_DMP)

#endif  // #if ENABLE_MPLAYER_MOVIE

//******************************************************************************
/// Get the current drive information by current partition index 'm_u16CurDriveIdx'.
/// @param  pDriveInfo \b OUT Return the drive information. Ignore u8DeviceAddr currently.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_QueryCurrentDrive(MPlayerDrive *pDriveInfo)
{
    if(m_u16CurDriveIdx != MPLAYER_INVALID_INDEX)
    {
        //m_u16CurDriveIdx <-- This means partition index of msAPI_FCtrl.c instead of drive index in mapp_mplayer.c
        if(MApp_MPlayer_QueryPartitionIdxInDrive(m_u16CurDriveIdx, pDriveInfo)!=0xFF)
        {
            return E_MPLAYER_RET_OK;
        }
    }
    return E_MPLAYER_RET_FAIL;
}

//******************************************************************************
/// Get the current drive index.
/// @return U16: specify the current drive index.
//******************************************************************************
U16 MApp_MPlayer_QueryCurrentDriveIndex(void)
{
    return(m_u16CurDriveIdx);
}

//******************************************************************************
/// Get the device total number.
/// @return MPLAYER_INVALID_INDEX: Failed to get the information.
///         Other                : Return the device number.
//******************************************************************************
U16 MApp_MPlayer_QueryTotalDeviceNum(void)
{
    U16 u16DeviceNum, i;

    u16DeviceNum = 0;
    for(i=0;i<NUM_OF_SUPPORT_DEVICES;i++)
    {
        if(m_MPlayerDeviceStatus[i].eDeviceType != E_MPLAYER_INVALID)
        {
            u16DeviceNum++;
        }
    }
    return u16DeviceNum;
}

//******************************************************************************
/// GGet the device information by device index.
/// @param  u16DeviceIdx \b IN  Specify the device index.
/// @param  pDeviceInfo  \b OUT Specify the device. Ignore the u8DeviceAddr and
///                             u8Lun currently.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_QueryDeviceInfo(U16 u16DeviceIdx, MPlayerDevice *pDeviceInfo)
{
    if(m_MPlayerDeviceStatus[u16DeviceIdx].eDeviceType != E_MPLAYER_INVALID)
    {
        memcpy(pDeviceInfo, &m_MPlayerDeviceStatus[u16DeviceIdx], sizeof(MPlayerDevice));
        return E_MPLAYER_RET_OK;
    }
    return E_MPLAYER_RET_FAIL;
}

//******************************************************************************
/// Get the total drive number.
/// @return MPLAYER_INVALID_INDEX: Failed to get the information.
///         Other                : Return the drive number.
//******************************************************************************
U16 MApp_MPlayer_QueryTotalDriveNum(void)
{
    return (U16)m_u8TotalDriveNum;
}

//******************************************************************************
/// Get the total file number.
/// @return MPLAYER_INVALID_INDEX: Failed to get the information.
///         Other                : Return the file number.
//******************************************************************************
U16 MApp_MPlayer_QueryTotalFileNum(void)
{
#if REMOVE_DRIVE_SELECT_TO_FILE_LIST
	 if(!bIsDriveSelected) 
	 {
		m_u16TotalFileNum = (U16)m_u8TotalDriveNum;
	 }
#endif
     return m_u16TotalFileNum;
}

#if PLAYLIST_BGM
U16 MApp_MPlayer_QueryTotalMusicFileNum(void)
{
        return m_u16TotalMusicFileNum;
}
#endif

//******************************************************************************
/// Get the drive information by drive index.
/// @param  u16DriveIdx \b IN  Drive index.
/// @param  pDriveInfo  \b OUT Return the drive information. Ignore u8DeviceAddr currently.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_QueryDriveInfo(U16 u16DriveIdx, MPlayerDrive *pDriveInfo)
{
    if((u16DriveIdx < NUM_OF_MAX_DRIVE)
    && (m_u32DriveStatus & (1<<m_DriveInfo[u16DriveIdx].u8Partition)))
    {
        memcpy(pDriveInfo, &m_DriveInfo[u16DriveIdx], sizeof(MPlayerDrive));
        return E_MPLAYER_RET_OK;
    }
    return E_MPLAYER_RET_FAIL;
}

//******************************************************************************
/// Get the drive index by partition index.
/// @param  u16PartitionIdx \b IN  Partition index.
/// @param  pDriveInfo  \b OUT Return the drive information. Ignore u8DeviceAddr currently.
/// @return drive index
//******************************************************************************
U8 MApp_MPlayer_QueryPartitionIdxInDrive(U16 u16PartitionIdx, MPlayerDrive *pDriveInfo)
{
    if((u16PartitionIdx < NUM_OF_MAX_DRIVE)
        &&(m_u32DriveStatus & (1<<u16PartitionIdx))
        )
    {
        U8 i;
        for(i=0; i<NUM_OF_MAX_DRIVE; i++)
        {
            if(m_DriveInfo[i].u8Partition == u16PartitionIdx)
            {
                memcpy(pDriveInfo, &m_DriveInfo[i], sizeof(MPlayerDrive));
                return i;
            }
        }
    }
    return 0xFF;
}

//******************************************************************************
/// Get the drive index by lun.
/// @param  u16PartitionIdx \b IN  lun.
/// @param  pDriveInfo  \b OUT Return the drive information. Ignore u8DeviceAddr currently.
/// @return drive index
//******************************************************************************
U8 MApp_MPlayer_QueryDriveInfoByLun(U8 u8Lun, MPlayerDrive *pDriveInfo)
{
    U8 i;
    for(i=0; i<NUM_OF_MAX_DRIVE; i++)
    {
        if(m_DriveInfo[i].u8Lun == u8Lun)
        {
            memcpy(pDriveInfo, &m_DriveInfo[i], sizeof(MPlayerDrive));
            return i;
        }
    }

    return 0xFF;
}

//******************************************************************************
/// Query the current zoom scale.
/// @return The current zoom mode.
//******************************************************************************
enumMPlayerZoom MApp_MPlayer_QueryZoomScale(void)
{
    return m_eZoom;
}

#if ENABLE_MPLAYER_PHOTO
//******************************************************************************
/// Query the current photo rotation mode.
/// @return The current photo rotation mode.
//******************************************************************************
enumMPlayerPhotoRotate MApp_MPlayer_QueryPhotoRotateMode(void)
{
    // All the PHOTO rorate now use PHOTO_SLIDE_SHOW_EFFECT by MApp_Jpeg_GetRotationMode
    // so we can get the value simply by just call this function.
    return (enumMPlayerPhotoRotate)MApp_Photo_GetRotationMode();
}
#endif  // #if ENABLE_MPLAYER_PHOTO

//******************************************************************************
/// Query the current repeat mode.
/// @return The current repeat mode.
//******************************************************************************
enumMPlayerRepeatMode MApp_MPlayer_QueryRepeatMode(void)
{
#if ENABLE_BGM
    if(m_eMediaType == E_MPLAYER_TYPE_MUSIC)
    {
        return m_eRepeatMode[E_MPLAYER_BACKGROUND_PLAYER];
    }
    else
#endif
    {
        return m_eRepeatMode[E_MPLAYER_FOREGROUND_PLAYER];
    }
}

//******************************************************************************
/// Query the current repeat mode.
/// @param  eMPlayerIdx \b IN  Specify the mplayer type.
/// @return The current repeat mode.
//******************************************************************************
enumMPlayerRepeatMode MApp_MPlayer_QueryRepeatModeByMPlayerType(enumMPlayerMediaType eType)
{
#if ENABLE_BGM
    if(eType == E_MPLAYER_TYPE_MUSIC)
    {
        return m_eRepeatMode[E_MPLAYER_BACKGROUND_PLAYER];
    }
    else
#else
    UNUSED(eType);
#endif
    {
        return m_eRepeatMode[E_MPLAYER_FOREGROUND_PLAYER];
    }
}

#if RANDOM_PLAY
//******************************************************************************
/// Query the current Random mode.
/// @return The current Random mode.
//******************************************************************************
enumMPlayerRandomMode MApp_MPlayer_QueryRandomMode(void)
{
#if ENABLE_BGM
    if(m_eMediaType == E_MPLAYER_TYPE_MUSIC)
    {
        return m_eRandomMode[E_MPLAYER_BACKGROUND_PLAYER];
    }
    else
#endif
    {
        return m_eRandomMode[E_MPLAYER_FOREGROUND_PLAYER];
    }
}

//******************************************************************************
/// Query the current Random mode.
/// @param  eMPlayerIdx \b IN  Specify the mplayer type.
/// @return The current Random mode.
//******************************************************************************
enumMPlayerRandomMode MApp_MPlayer_QueryRandomModeByMPlayerType(enumMPlayerMediaType eType)
{
#if ENABLE_BGM
    if(eType == E_MPLAYER_TYPE_MUSIC)
    {
        return m_eRandomMode[E_MPLAYER_BACKGROUND_PLAYER];
    }
    else
#else
    UNUSED(eType);
#endif
    {
        return m_eRandomMode[E_MPLAYER_FOREGROUND_PLAYER];
    }
}
#endif

#if (ENABLE_WMA)
static EN_WMA_INFO _MApp_MPlayer_Mp3Info2WmaInfo(EN_MP3_INFO enInfo)
{
    EN_WMA_INFO enWmaInfo = WMA_INFO_BITRATE;
    switch(enInfo)
    {
        case MP3_INFO_BITRATE:
            enWmaInfo = WMA_INFO_BITRATE;
            break;
        case MP3_INFO_SAMPLINGRATE:
            enWmaInfo = WMA_INFO_SAMPLINGRATE;
            break;
        case MP3_INFO_ALBUM:
            enWmaInfo = WMA_INFO_ALBUM;
            break;
        case MP3_INFO_ARTIST:
            enWmaInfo = WMA_INFO_ARTIST;
            break;
        case MP3_INFO_TITLE:
            enWmaInfo = WMA_INFO_TITLE;
            break;
        case MP3_INFO_YEAR:
            enWmaInfo = WMA_INFO_YEAR;
            break;
        case MP3_INFO_CHECK_FF_FB:
            enWmaInfo = WMA_INFO_CHECK_FF_FB;
            break;
        default:
            break;
    }
    return enWmaInfo;
}
#endif

#if ENABLE_MPLAYER_MUSIC
//******************************************************************************
/// Query the music info. This function is only valid in the notification of
/// E_MPLAYER_NOTIFY_BEFORE_PLAY_ONE_FILE.
/// @param  eInfo    \b IN  Specify the information type.
/// @return the wanted info string or NULL if no such info available
//******************************************************************************
U8 *MApp_MPlayer_QueryMusicInfo(EN_MP3_INFO enInfo, U8* pu8Length)
{
    enumMPlayerMediaSubType eMediaSubType = m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType;
    switch(eMediaSubType){
        case E_MPLAYER_SUBTYPE_MP3 :
#if (ENABLE_AAC)
        case E_MPLAYER_SUBTYPE_AAC :
#endif
#if (ENABLE_WAV)
        case E_MPLAYER_SUBTYPE_WAV :
#endif
#if (ENABLE_OGG)
        case E_MPLAYER_SUBTYPE_OGG :
#endif
#if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
        case E_MPLAYER_SUBTYPE_LOAS :
#endif
#if (ENABLE_FLAC)
        case E_MPLAYER_SUBTYPE_FLAC :
#endif
#if (ENABLE_AC3)
        case E_MPLAYER_SUBTYPE_AC3 :
#endif
#if (ENABLE_AMR)
        case E_MPLAYER_SUBTYPE_AMR :
        case E_MPLAYER_SUBTYPE_AWB :
#endif
            return MApp_Music_GetInfoString(enInfo, pu8Length);
#if (ENABLE_WMA)
        case E_MPLAYER_SUBTYPE_WMA :
        {
            EN_WMA_INFO enWmaInfo = _MApp_MPlayer_Mp3Info2WmaInfo(enInfo);
            return MApp_WMA_GetInfoString(enWmaInfo, pu8Length);
        }
#endif
        default :
            return NULL;
    }
}

#endif  // #if ENABLE_MPLAYER_MUSIC

//******************************************************************************
/// Query the selected file number by media type.
/// @param  eType \b IN  Specify the media type.
/// @return number of selected file.
//******************************************************************************
U16 MApp_MPlayer_QuerySelectedFileNum(enumMPlayerMediaType eType)
{
    if(eType < E_MPLAYER_TYPE_NUM)
    {
        return(m_u16SelectedFileNum[(U8)eType]);
    }

    return 0;
}

//******************************************************************************
/// Check whether the music is recording.
/// @return TRUE:   The music is recording.
///         FALSE:  No music is recording.
//******************************************************************************
BOOLEAN MApp_MPlayer_IsMusicRecording(void)
{
    return bMusicRecording;
}
#if ENABLE_MPLAYER_MOVIE
BOOLEAN MApp_MPlayer_IsMovieIndexTableExist(void)
{
    if(MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_MAX_FB_SPEED) != 0)
    {
        return TRUE;
    }
    return FALSE;
}
//******************************************************************************
/// Check whether the movie is playing.
/// @return TRUE:   The movie is playing.
///         FALSE:  The movie is not playing.
//******************************************************************************
BOOLEAN MApp_MPlayer_IsMoviePlaying(void)
{
    if(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_MOVIE_PLAY)
        return TRUE;

    return FALSE;
}
//******************************************************************************
/// Play movie on demand (ex: to smooth the playing effect when drawing OSD)
/// @return None.
//******************************************************************************
void MApp_MPlayer_PlayMovieOnDemand(void)
{
    return;
#if 0
    if(!MApp_MPlayer_IsMoviePlaying())
        return;

    if(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_MPEG4)
    {
        // If predecode is in OK state, not necessary to call following function.
        if(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_PREDECODE_OK)
        {
            if(m_eMovieMainExit != EXIT_VDPLAYER_WAIT &&
               m_eMovieMainExit != EXIT_VDPLAYER_EXIT)
            {
                m_eMovieMainExit = MApp_VDPlayer_Main();
            }
        }
    }
#endif
}

#if (ENABLE_SUBTITLE_DMP)
void MApp_MPlayer_QueryCurrentSubtitle(U8 *pu8Subtitle, U32 u32BufSize)
{
    _MApp_MPlayer_GetSubtitle(pu8Subtitle, u32BufSize, m_u32CurSubtitlePos);
}
#endif //#if (ENABLE_SUBTITLE_DMP)

#endif  // #if ENABLE_MPLAYER_MOVIE

//******************************************************************************
/// Check that is there any media files playing.
/// @return TRUE:   There is media file playing.
///         FALSE:  There is no media file playing.
//******************************************************************************
BOOLEAN MApp_MPlayer_IsMediaFileInPlaying(void)
{
    if((m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1
            | m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1
            )
        & (0
#if ENABLE_MPLAYER_PHOTO
                             | E_MPLAYER_KNL_FLG1_PHOTO_PLAY
#endif  // #if ENABLE_MPLAYER_PHOTO
#if ENABLE_MPLAYER_MUSIC
                             | E_MPLAYER_KNL_FLG1_MUSIC_PLAY
#endif  // #if ENABLE_MPLAYER_MUSIC
#if ENABLE_MPLAYER_MOVIE
                             | E_MPLAYER_KNL_FLG1_MOVIE_PLAY
#endif  // #if ENABLE_MPLAYER_MOVIE
#if ENABLE_MPLAYER_TEXT
                             | E_MPLAYER_KNL_FLG1_TEXT_PLAY
#endif  // #if ENABLE_MPLAYER_TEXT
                             ))
    {
        return TRUE;
    }

    return FALSE;
}

//******************************************************************************
/// Check that is there PLUG-IN APP playing.
/// @return TRUE:   There is PLUG-IN APP playing.
///         FALSE:  There is no PLUG-IN APP playing.
//******************************************************************************
#if ENABLE_MPLAYER_PLUGIN
BOOLEAN MApp_MPlayer_IsPlugInAppPlaying(void)
{
    if(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_PLUGIN_PLAY)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
#endif

//******************************************************************************
/// Check that is there background music playing.
/// @return TRUE:   There is background music playing.
///         FALSE:  There is no background music playing.
//******************************************************************************
BOOLEAN MApp_MPlayer_IsMusicPlaying(void)
{
    return (m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 & (0
#if ENABLE_MPLAYER_MUSIC
            | E_MPLAYER_KNL_FLG1_MUSIC_PLAY)
#endif //#if ENABLE_MPLAYER_MUSIC
            );
}

/******************************************************************************/
/// Transfer music data to Dram ,if background music is playing.
///
/******************************************************************************/
void MApp_MPlayer_BGM_Bitstream_Handle(void)
{
    enumMPlayerIdx eMPlayerIdx;

    //For background music service
    if (m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 & (0
#if ENABLE_MPLAYER_MUSIC
            | E_MPLAYER_KNL_FLG1_MUSIC_PLAY
#endif  // #if ENABLE_MPLAYER_MOVIE
            ))
    {
        eMPlayerIdx = E_MPLAYER_BACKGROUND_PLAYER;
#if ENABLE_MPLAYER_MUSIC
        if(m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &
E_MPLAYER_KNL_FLG1_MUSIC_PLAY)
        {
            switch (m_MPlayerInfo[eMPlayerIdx].eMediaSubType)
            {
            #if (ENABLE_WMA)
                case E_MPLAYER_SUBTYPE_WMA:
                    MApp_WMA_Main();
                    break;
            #endif

            #if (ENABLE_AAC)
                case E_MPLAYER_SUBTYPE_AAC:
                    MApp_Music_Main(EN_MUSIC_AAC);
                    break;
            #endif

            #if (ENABLE_WAV)
                case E_MPLAYER_SUBTYPE_WAV:
                    MApp_Music_Main(EN_MUSIC_WAV);
                    break;
            #endif

                case E_MPLAYER_SUBTYPE_MP3:
                    MApp_Music_Main(EN_MUSIC_MP3);
                    break;

            #if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
                case E_MPLAYER_SUBTYPE_LOAS:
                    MApp_Music_Main(EN_MUSIC_LOAS);
                    break;
            #endif

            #if (ENABLE_OGG)
                case E_MPLAYER_SUBTYPE_OGG:
                    MApp_Music_Main(EN_MUSIC_OGG);
                    break;
            #endif

            #if (ENABLE_AMR)
                case E_MPLAYER_SUBTYPE_AMR:
                    MApp_Music_Main(EN_MUSIC_AMR);
                    break;

                case E_MPLAYER_SUBTYPE_AWB:
                    MApp_Music_Main(EN_MUSIC_AWB);
                    break;
            #endif

                default:
                    break;
            }
        }
#endif
    }
}

//******************************************************************************
/// Check that is there only background music playing.
/// @return TRUE:   There is only background music playing.
///         FALSE:  Not only background music playing.
//******************************************************************************
BOOLEAN MApp_MPlayer_IsOnlyMusicPlaying(void)
{
    if (m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 & (0
#if ENABLE_MPLAYER_MUSIC
                            | E_MPLAYER_KNL_FLG1_MUSIC_PLAY
#endif  // #if ENABLE_MPLAYER_MUSIC
                             ))
    {
        if (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & (0
#if ENABLE_MPLAYER_PHOTO
                                | E_MPLAYER_KNL_FLG1_PHOTO_PLAY
#endif  // #if ENABLE_MPLAYER_PHOTO
#if ENABLE_MPLAYER_MOVIE
                                | E_MPLAYER_KNL_FLG1_MOVIE_PLAY
#endif  // #if ENABLE_MPLAYER_MOVIE
#if ENABLE_MPLAYER_TEXT
                                | E_MPLAYER_KNL_FLG1_TEXT_PLAY
#endif  // #if ENABLE_MPLAYER_TEXT
                                 ))
        {
            return FALSE;
        }

        return TRUE;
    }

    return FALSE;
}

//******************************************************************************
/// Query current directory depth
/// @return directory depth
//******************************************************************************
U16 MApp_MPlayer_QueryDirectoryDepth(void)
{
    return m_u16CurDirectoryDepth;
}

//******************************************************************************
/// Query current directory number
/// @return directory depth
//******************************************************************************
U16 MApp_MPlayer_QueryDirectoryNumber(void)
{
    return m_u16DirectoryNum[m_u16CurDirectoryDepth];
}

#if PLAYLIST_BGM
U16 MApp_MPlayer_QueryMusicDirectoryNumber(void)
{
    return m_u16CurMusicDirectoryNumber;
}
#endif

//******************************************************************************
/// Query the time in sec the current music file is played
/// @return the play time in sec
//******************************************************************************
#if (ENABLE_MPLAYER_MUSIC)
U32 MApp_MPlayer_QueryMusicFilePlayTime(void)
{
    U32 u32MusicTotalTime = 0;

    switch(m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType)
    {
#if (ENABLE_WMA)
    case E_MPLAYER_SUBTYPE_WMA:
        u32MusicTotalTime = MApp_WMA_GetTotalTime();
        break;
#endif
    case E_MPLAYER_SUBTYPE_MP3:
#if (ENABLE_AAC)
    case E_MPLAYER_SUBTYPE_AAC:
#endif
#if (ENABLE_WAV)
    case E_MPLAYER_SUBTYPE_WAV:
#endif
#if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
    case E_MPLAYER_SUBTYPE_LOAS:
#endif //#if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
#if (ENABLE_OGG)
    case E_MPLAYER_SUBTYPE_OGG:
#endif
#if (ENABLE_FLAC)
    case E_MPLAYER_SUBTYPE_FLAC:
#endif
#if (ENABLE_AC3)
    case E_MPLAYER_SUBTYPE_AC3:
#endif
#if (ENABLE_AMR)
    case E_MPLAYER_SUBTYPE_AMR:
    case E_MPLAYER_SUBTYPE_AWB:
#endif
        u32MusicTotalTime = MApp_Music_GetTotalTime();
        break;
    default:
        break;
    }

    return u32MusicTotalTime;
}

U32 MApp_MPlayer_QueryMusicFileCurrentTime(void)
{
    U32 u32MusicCurrentTime = 0;

    switch(m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType)
    {
#if (ENABLE_WMA)
    case E_MPLAYER_SUBTYPE_WMA:
        u32MusicCurrentTime = MApp_WMA_GetCurrentTime();
        break;
#endif
    case E_MPLAYER_SUBTYPE_MP3:
#if (ENABLE_AAC)
    case E_MPLAYER_SUBTYPE_AAC:
#endif
#if (ENABLE_WAV)
    case E_MPLAYER_SUBTYPE_WAV:
#endif
#if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
    case E_MPLAYER_SUBTYPE_LOAS:
#endif //#if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
#if (ENABLE_OGG)
    case E_MPLAYER_SUBTYPE_OGG:
#endif
#if (ENABLE_FLAC)
    case E_MPLAYER_SUBTYPE_FLAC:
#endif
#if (ENABLE_AC3)
    case E_MPLAYER_SUBTYPE_AC3:
#endif
#if (ENABLE_AMR)
    case E_MPLAYER_SUBTYPE_AMR:
    case E_MPLAYER_SUBTYPE_AWB:
#endif
        u32MusicCurrentTime = MApp_Music_GetCurrentTime();
        break;
    default:
        break;
    }

    return u32MusicCurrentTime;
}

void MApp_MPlayer_QueryCurrentLyric(U8 *pu8Lyric)
{
    _MApp_MPlayer_GetLyric(m_u16CurLyricPos, pu8Lyric);
}
#endif  // #if (ENABLE_MPLAYER_MUSIC)

#if (ENABLE_MPLAYER_PHOTO)
BOOLEAN MApp_MPlayer_IsThumbnailMode(void)
{
    return ((m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_THUMBNAIL_MODE) == E_MPLAYER_KNL_FLG_THUMBNAIL_MODE);
}
//******************************************************************************
/// Check whether the photo is playing.
/// @return TRUE:   The photo is playing.
///         FALSE:  The photo is not playing.
//******************************************************************************
BOOLEAN MApp_MPlayer_IsPhotoPlaying(void)
{
    if(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_PHOTO_PLAY)
        return TRUE;

    return FALSE;
}
#endif  // #if (ENABLE_MPLAYER_PHOTO)

#if 0//ndef ZUI
//=============================================================================/
//============================ State Machine ==================================
//=============================================================================/
//******************************************************************************
/// Media player state machine
/// @return EN_RET
//******************************************************************************
EN_RET MApp_MPlayer_Main(void)
{
    switch(m_eMPlayerStateMachineState)
    {
    case STATE_MPLAYER_INIT:
        m_eMPlayerStateMachineState = STATE_MPLAYER_WAIT;
        return EXIT_MPLAYER_NULL;

    case STATE_MPLAYER_WAIT:
        if(u8KeyCode != KEY_NULL)
        {
            MApp_UiMediaPlayer_ProcessKey(u8KeyCode);
            u8KeyCode = KEY_NULL;
        }
        return EXIT_MPLAYER_NULL;

    case STATE_MPLAYER_EXIT_TO_MENU:
        m_eMPlayerStateMachineState = STATE_MPLAYER_WAIT;
        return EXIT_MPLAYER_TRAN_MENU;

    case STATE_MPLAYER_STANDBY:
        return EXIT_MPLAYER_TRAN_STANDBY;
    }
}
#endif  // #ifndef ZUI

#if ENABLE_USB_DETECT_STEP_BY_STEP
//for switch source step by step
void MApp_MPlayer_CheckUSBStatus(void)
{
    switch(m_MPlayerUSBDetect.eCurrentState)
    {
        case STATE_USB_DETECT_START:
            //printf("\n------  mapp_mplayer_task : start to check device and port ------\n");
            if(MApp_MassStorage_DeviceChangeStatusCheck())
            {
                MApp_MassStorage_DeviceStatusCheck();
                m_MPlayerUSBDetect.eCurrentState = STATE_USB_DETECT_GET_DEVICE_AND_DRIVE;
            }
            break;

        case STATE_USB_DETECT_GET_DEVICE_AND_DRIVE:
            m_MPlayerUSBDetect.u32ValidDevice = MApp_MassStorage_GetValidDevice();
            m_MPlayerUSBDetect.u8TotalDriveNum = MApp_MassStorage_GetTotalDriveNum();
            m_MPlayerUSBDetect.eCurrentState = STATE_USB_DETECT_CHECK_PORT_CHANGED;
            break;

        case STATE_USB_DETECT_CHECK_PORT_CHANGED:
            {
                BOOLEAN bPort1Changed, bPort2Changed, bPort3Changed, bPort4Changed;
                bPort1Changed = msAPI_MSDCtrl_IsPortChanged(MSD_PORT_1);
                bPort2Changed = msAPI_MSDCtrl_IsPortChanged(MSD_PORT_2);
                bPort3Changed = msAPI_MSDCtrl_IsPortChanged(MSD_PORT_3);
                bPort4Changed = msAPI_MSDCtrl_IsPortChanged(MSD_PORT_4);
                //printf("device and port remember ok. m_u16DeviceValidStatus=%bx,  m_u8TotalDriveNum=%bx  \n ",m_u16DeviceValidStatus, m_u8TotalDriveNum);
                if((m_u32DeviceValidStatus != m_MPlayerUSBDetect.u32ValidDevice) ||
                   (m_MPlayerUSBDetect.u8TotalDriveNum != m_u8TotalDriveNum) ||
                   (bPort1Changed || bPort2Changed || bPort3Changed || bPort4Changed))
                {
                    m_u32DeviceValidStatus = m_MPlayerUSBDetect.u32ValidDevice;
                    m_u8TotalDriveNum = m_MPlayerUSBDetect.u8TotalDriveNum;
                    //if(bDriveDisconnect)
                    if( (bPort1Changed && m_u8CurDeviceIdx == E_MPLAYER_USB0) ||
                        (bPort2Changed && m_u8CurDeviceIdx == E_MPLAYER_USB1) ||
                        (bPort3Changed && m_u8CurDeviceIdx == E_MPLAYER_USB2) ||
                        (bPort4Changed && m_u8CurDeviceIdx == E_MPLAYER_USB3) ||
                        m_u8CurDeviceIdx == E_MPLAYER_INVALID)
                    {
                        // clean play list here instead of clean it in MApp_MPlayer_ConnectDrive()
                        // allows selecting file across drive and clean play list when any device
                        // insert/delete happens
                        memset(m_u16SelectedFileNum, 0, sizeof(U16)*E_MPLAYER_TYPE_NUM);
                        //printf("\n _MApp_MPlayer_DisconnectDrive.------- clean play list when any device  insert/delete happens\n");
                        _MApp_MPlayer_DisconnectDrive();
                        m_MPlayerUSBDetect.eCurrentState = STATE_USB_DETECT_CURRENT_PORT_CHANGED_PROCESS_INIT;
                    }
                    else
                    {
                        // Active device still connected, only redraw UI
                        //printf("\n  Active device still connected, only redraw UI");
                        m_u32DeviceValidStatus = MApp_MassStorage_GetValidDevice();
                        //printf("\n[MPlayer Task] Drive Change : m_u32DeviceValidStatus = 0X%bx\n", m_u32DeviceValidStatus);
                        m_MPlayerUSBDetect.eCurrentState = STATE_USB_DETECT_ANOTHER_PORT_CHANGED_PROCESS_INIT;
                    }
                }
                else
                {
                    //printf("keep check port status");
                    m_MPlayerUSBDetect.eUSBDeviceStatus = (enumMPlayerUSBDeviceStatus)msAPI_GetUsbDeviceStatus();
                    //printf("\n  eUSBDeviceStatus=%bx\n",(U8)eUSBDeviceStatus);
                    if(m_PrevUSBDeviceStatus != m_MPlayerUSBDetect.eUSBDeviceStatus)
                    {
                        if(m_PrevUSBDeviceStatus != E_MPLAYER_USB_NONE)
                        {
                        //#if ENABLE_MPLAYER_PLUGIN
                        //    if(!MApp_MPlayer_IsPlugInAppPlaying())
                        //#endif
                            {
                                NOTIFY(E_MPLAYER_NOTIFY_USB_DEVICE_STATUS_CHANGE, &m_MPlayerUSBDetect.eUSBDeviceStatus);
                            }
                        }
                        m_PrevUSBDeviceStatus = m_MPlayerUSBDetect.eUSBDeviceStatus;
                    }
                    m_MPlayerUSBDetect.eCurrentState = STATE_USB_DETECT_START;
                }
            }
            break;

        case STATE_USB_DETECT_CURRENT_PORT_CHANGED_PROCESS_INIT:
            MApp_MPlayer_InitializeAllDevices();
            //printf("\n [MPlayer Task 1] m_u8CurDeviceIdx : 0x%bX\n", m_u8CurDeviceIdx);
            m_MPlayerUSBDetect.eCurrentState = STATE_USB_DETECT_CURRENT_PORT_CHANGED_PROCESS_DONE;
            break;

        case STATE_USB_DETECT_CURRENT_PORT_CHANGED_PROCESS_DONE:
        //#if ENABLE_MPLAYER_PLUGIN
        //    if(!MApp_MPlayer_IsPlugInAppPlaying())
        //#endif
            {
                NOTIFY(E_MPLAYER_NOTIFY_USB_ACTIVE_DEVICE_STATUS_CHANGE, &m_u32DriveStatus);
            }
            //msAPI_MSDCtrl_SetPortChanged();
            m_MPlayerUSBDetect.eCurrentState = STATE_USB_DETECT_START;
            break;

        case STATE_USB_DETECT_ANOTHER_PORT_CHANGED_PROCESS_INIT:
            _MApp_MPlayer_ReCalcDeviceDriveInfo();
            //printf("\n[MPlayer Task 2] m_u8CurDeviceIdx : 0x%bX , m_u8TotalDriveNum : %bu\n", m_u8CurDeviceIdx,m_u8TotalDriveNum);
            m_MPlayerUSBDetect.eCurrentState = STATE_USB_DETECT_ANOTHER_PORT_CHANGED_PROCESS_DONE;
            break;

        case STATE_USB_DETECT_ANOTHER_PORT_CHANGED_PROCESS_DONE:
        //#if ENABLE_MPLAYER_PLUGIN
        //    if(!MApp_MPlayer_IsPlugInAppPlaying())
        //#endif
            {
                NOTIFY(E_MPLAYER_NOTIFY_DRIVE_CHANGE, NULL);
            }
            m_MPlayerUSBDetect.eCurrentState = STATE_USB_DETECT_START;
            break;
    }

}

#else
//for switch source and USB abnormal
void MApp_MPlayer_CheckUSBStatus(void)
{
    U8 u8TotalDriveNum;
    U32 u32ValidDevice;
    BOOLEAN bPort1Changed, bPort2Changed, bPort3Changed, bPort4Changed;
    enumMPlayerUSBDeviceStatus eUSBDeviceStatus;

    //printf("\n------  mapp_mplayer_task : start to check device and port ------\n");
    if(MApp_MassStorage_DeviceChangeStatusCheck())
    {
        MApp_MassStorage_DeviceStatusCheck();
        u32ValidDevice = MApp_MassStorage_GetValidDevice();
        u8TotalDriveNum = MApp_MassStorage_GetTotalDriveNum();
    }
    else
    {
        u32ValidDevice = m_u32DeviceValidStatus;
        u8TotalDriveNum = m_u8TotalDriveNum;
    }

    //if((m_u32DeviceValidStatus != u32ValidDevice) ||
    //   (u8TotalDriveNum != m_u8TotalDriveNum))
    bPort1Changed = msAPI_MSDCtrl_IsPortChanged(MSD_PORT_1);
    bPort2Changed = msAPI_MSDCtrl_IsPortChanged(MSD_PORT_2);
    bPort3Changed = msAPI_MSDCtrl_IsPortChanged(MSD_PORT_3);
    bPort4Changed = msAPI_MSDCtrl_IsPortChanged(MSD_PORT_4);
    //printf("device and port remember ok. m_u32DeviceValidStatus=%bx,  m_u8TotalDriveNum=%bx  \n ",m_u16DeviceValidStatus, m_u8TotalDriveNum);
    if((m_u32DeviceValidStatus != u32ValidDevice) ||
       (u8TotalDriveNum != m_u8TotalDriveNum) ||
    (bPort1Changed || bPort2Changed || bPort3Changed || bPort4Changed))
    {
        //printf(" device or port changed.");
    #if NOTIFY_ACTIVE_DEVICE_CHANGE_ONLY_WHEN_CURRENT_LUN_REMOVE
        BOOL bRemoveCurrentDrive =FALSE;
        //if current device is removed, MApp_MassStorage_GetCurrentDeviceIndex() will return 0xFF.
        U8 u8NewDeviceIndex = MApp_MassStorage_GetCurrentDeviceIndex();
        //if current drive is removed, MApp_MassStorage_GetCurrentDriveIndex() will return 0xFF.
        U8 u8NewDriveIndex = MApp_MassStorage_GetCurrentDriveIndex();

        if(u8NewDeviceIndex != 0xFF && (1 << u8NewDeviceIndex & u32ValidDevice))
        {
            bRemoveCurrentDrive = FALSE;
            printf("Current Drive No Changed\n");
        }
        else
        {
            bRemoveCurrentDrive = TRUE;
            printf("!!!!Current Drive Changed!!!\n");
        }

        if(!bRemoveCurrentDrive)
        {
            // Mapping to new drive index when insert or remove memory card
            if(u8NewDriveIndex != 0xFF && u8NewDriveIndex < u8TotalDriveNum)
            {
                if(m_u16CurDriveIdx != u8NewDriveIndex)
                {
                    // Update file browser to new drive index
                    m_u16CurDriveIdx = u8NewDriveIndex;
                    MApp_FileBrowser_Destroy(m_u8UserBrowserHandle);
                    m_u8UserBrowserHandle = MApp_FileBrowser_Create(m_u16CurDriveIdx);
                    if(m_u8UserBrowserHandle == INVALID_BROWSER_HANDLE)                                     //<--FILE BROWSER SECOND
                    {
                        printf("MApp_MPlayer_ConnectDrive File browser Failed\n");
                    }
                    MApp_FileBrowser_SetEnvironment(m_u8UserBrowserHandle);
                }
            }
            else
            {
                printf("ERROR!!! new mapping drive index ID(0 based) > total drive number -1\n");
                printf("CurIdx=0x%x, TotalDriveNum=0x%x\n",m_u16CurDriveIdx,u8TotalDriveNum);
                bRemoveCurrentDrive = TRUE;
            }
        }
    #endif
        m_u32DeviceValidStatus = u32ValidDevice;
        m_u8TotalDriveNum = u8TotalDriveNum;
        //if(bDriveDisconnect)
    #if NOTIFY_ACTIVE_DEVICE_CHANGE_ONLY_WHEN_CURRENT_LUN_REMOVE
        if((bRemoveCurrentDrive && bPort1Changed && m_u8CurDeviceIdx == E_MPLAYER_USB0) ||
           (bRemoveCurrentDrive && bPort2Changed && m_u8CurDeviceIdx == E_MPLAYER_USB1) ||
           (bRemoveCurrentDrive && bPort3Changed && m_u8CurDeviceIdx == E_MPLAYER_USB2) ||
           (bRemoveCurrentDrive && bPort4Changed && m_u8CurDeviceIdx == E_MPLAYER_USB3) ||
            m_u8CurDeviceIdx == E_MPLAYER_INVALID)
    #else
        if((bPort1Changed && m_u8CurDeviceIdx == E_MPLAYER_USB0) ||
           (bPort2Changed && m_u8CurDeviceIdx == E_MPLAYER_USB1) ||
           (bPort3Changed && m_u8CurDeviceIdx == E_MPLAYER_USB2) ||
           (bPort4Changed && m_u8CurDeviceIdx == E_MPLAYER_USB3) ||
            m_u8CurDeviceIdx == E_MPLAYER_INVALID)
    #endif
        {
            // clean play list here instead of clean it in MApp_MPlayer_ConnectDrive()
            // allows selecting file across drive and clean play list when any device
            // insert/delete happens
            memset(m_u16SelectedFileNum, 0, sizeof(U16)*E_MPLAYER_TYPE_NUM);
            //printf("\n _MApp_MPlayer_DisconnectDrive.------- clean play list when any device  insert/delete happens\n");
            _MApp_MPlayer_DisconnectDrive();
            MApp_MPlayer_InitializeAllDevices();
            //printf("\n [MPlayer Task 1] m_u8CurDeviceIdx : 0x%bX\n", m_u8CurDeviceIdx);
        //#if ENABLE_MPLAYER_PLUGIN
        //    if(!MApp_MPlayer_IsPlugInAppPlaying())
        //#endif
            {
                NOTIFY(E_MPLAYER_NOTIFY_USB_ACTIVE_DEVICE_STATUS_CHANGE, &m_u32DriveStatus);
            }
            //msAPI_MSDCtrl_SetPortChanged();
        }
        else
        { // Active device still connected, only redraw UI
            //printf("\n  Active device still connected, only redraw UI");
            m_u32DeviceValidStatus = MApp_MassStorage_GetValidDevice();
            //printf("\n[MPlayer Task] Drive Change : m_u16DeviceValidStatus = 0X%bx\n", m_u32DeviceValidStatus);
            _MApp_MPlayer_ReCalcDeviceDriveInfo();
            //printf("\n[MPlayer Task 2] m_u8CurDeviceIdx : 0x%bX , m_u8TotalDriveNum : %bu\n", m_u8CurDeviceIdx,m_u8TotalDriveNum);
        //#if ENABLE_MPLAYER_PLUGIN
        //    if(!MApp_MPlayer_IsPlugInAppPlaying())
        //#endif
            {
                NOTIFY(E_MPLAYER_NOTIFY_DRIVE_CHANGE, NULL);
            }
        }

    }
    else
    {
        //printf("keep check port status");
        eUSBDeviceStatus = (enumMPlayerUSBDeviceStatus)msAPI_GetUsbDeviceStatus();
        //printf("\n  eUSBDeviceStatus=%bx\n",(U8)eUSBDeviceStatus);
        if(m_PrevUSBDeviceStatus != eUSBDeviceStatus)
        {
            if(m_PrevUSBDeviceStatus != E_MPLAYER_USB_NONE)
            {
            //#if ENABLE_MPLAYER_PLUGIN
            //    if(!MApp_MPlayer_IsPlugInAppPlaying())
            //#endif
                {
                    NOTIFY(E_MPLAYER_NOTIFY_USB_DEVICE_STATUS_CHANGE, &eUSBDeviceStatus);
                }
            }
            m_PrevUSBDeviceStatus = eUSBDeviceStatus;
        }
    }
}
#endif

#if ENABLE_DRM
void MApp_MPlayer_PlayDRMFile(BOOLEAN bPlayDRM)
{
    if(bPlayDRM)
    {
        m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 |= (enumMPlayerKnlFlags1)E_MPLAYER_KNL_FLG1_MOVIE_INIT_OK;
        m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_FILE_WAIT_DRM_UI;
    }
    else
    {
        m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_MOVIE_INIT_OK;
        m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_FILE_WAIT_DRM_UI;
        MApp_VDPlayer_Stop();
        //_MApp_VDPlayer_Exit();
    }
}

void MApp_MPlayer_CheckDRMActivation(void)
{
    if(MApp_VDPlayer_CheckDRMActivationFile() == TRUE)
    {
        DMP_DBG(printf("activation!\n"););
//        MApp_LoadGenSetting();
        MApp_LoadDrmSetting();

        if(stGenSetting.g_VDplayerDRMInfo.bIsActivated==FALSE)
        {
            printf("timo set actived!!!\n");
            stGenSetting.g_VDplayerDRMInfo.bIsActivated = TRUE;
            stGenSetting.g_VDplayerDRMInfo.bIsDeactivated = FALSE;
            MApp_SaveDrmSetting();
//            MApp_SaveGenSetting();
        }
    }
    else
    {
        DMP_DBG(printf("MApp_VDPlayer_CheckDRMActivationFile() == FALSE\n"););
    }
}
#endif

#if ENABLE_4K2K
//************************************************************************************************************
/// Restrict photo decode resolution parameters by GE limitation.
/// @param  pstPhotoResolution \b OUT Specify the pointer of ST_PHOTO_DECODE_RESOLUTION_DEFINTIONS struction
/// @return void.
//************************************************************************************************************
void _MApp_MPlayer_RestrictPhotoDecodeResolution(ST_PHOTO_DECODE_RESOLUTION_DEFINTIONS *pstPhotoResolution)
{
    pstPhotoResolution->u32MinDecodeWidth                 = CHECK_GE_BOUNDARY(PHOTO_DECODE_MIN_WIDTH);
    pstPhotoResolution->u32MinDecodeHeight                = CHECK_GE_BOUNDARY(PHOTO_DECODE_MIN_HEIGHT);
    pstPhotoResolution->u32MaxDecodeJpegBaselineWidth     = CHECK_GE_BOUNDARY(PHOTO_DECODE_JPEG_BASELINE_MAX_WIDTH);
    pstPhotoResolution->u32MaxDecodeJpegBaselineHeight    = CHECK_GE_BOUNDARY(PHOTO_DECODE_JPEG_BASELINE_MAX_HEIGHT);
    pstPhotoResolution->u32MaxDecodeJpegProgressiveWidth  = CHECK_GE_BOUNDARY(PHOTO_DECODE_JPEG_PROGRESSIVE_MAX_WIDTH);
    pstPhotoResolution->u32MaxDecodeJpegProgressiveHeight = CHECK_GE_BOUNDARY(PHOTO_DECODE_JPEG_PROGRESSIVE_MAX_HEIGHT);
    pstPhotoResolution->u32MaxDecodeBmpWidth              = CHECK_GE_BOUNDARY(PHOTO_DECODE_BMP_MAX_WIDTH);
    pstPhotoResolution->u32MaxDecodeBmpHeight             = CHECK_GE_BOUNDARY(PHOTO_DECODE_BMP_MAX_HEIGHT);
    pstPhotoResolution->u32MaxDecodePngWidth              = CHECK_GE_BOUNDARY(PHOTO_DECODE_PNG_MAX_WIDTH);
    pstPhotoResolution->u32MaxDecodePngHeight             = CHECK_GE_BOUNDARY(PHOTO_DECODE_PNG_MAX_HEIGHT);
    pstPhotoResolution->u32MaxDecodeTiffWidth             = CHECK_GE_BOUNDARY(PHOTO_DECODE_TIFF_MAX_WIDTH);
    pstPhotoResolution->u32MaxDecodeTiffHeight            = CHECK_GE_BOUNDARY(PHOTO_DECODE_TIFF_MAX_HEIGHT);
    pstPhotoResolution->u32MaxDecodeGifWidth              = CHECK_GE_BOUNDARY(PHOTO_DECODE_GIF_MAX_WIDTH);
    pstPhotoResolution->u32MaxDecodeGifHeight             = CHECK_GE_BOUNDARY(PHOTO_DECODE_GIF_MAX_HEIGHT);
    pstPhotoResolution->u32MaxDecodeMpoBaselineWidth      = CHECK_GE_BOUNDARY(PHOTO_DECODE_MPO_BASELINE_MAX_WIDTH);
    pstPhotoResolution->u32MaxDecodeMpoBaselineHeight     = CHECK_GE_BOUNDARY(PHOTO_DECODE_MPO_BASELINE_MAX_HEIGHT);
    pstPhotoResolution->u32MaxDecodeMpoProgressiveWidth   = CHECK_GE_BOUNDARY(PHOTO_DECODE_MPO_PROGRESSIVE_MAX_WIDTH);
    pstPhotoResolution->u32MaxDecodeMpoProgressiveHeight  = CHECK_GE_BOUNDARY(PHOTO_DECODE_MPO_PROGRESSIVE_MAX_HEIGHT);
}
#endif

//=============================================================================/
//============================ Meida player task ==================================
//=============================================================================/
//******************************************************************************
/// Media player task
//******************************************************************************
void MApp_MPlayer_Task(void)
{
//    U16 u16DeviceConnectStatus;
//    U8 u32ValidDevice, u8TotalDriveNum;
//    BOOLEAN bDriveDisconnect=FALSE;
#if ENABLE_MPLAYER_PHOTO
    BOOLEAN bThumbnail, bPreview;
#endif  // #if ENABLE_MPLAYER_PHOTO
    U32 u32CurTime;
#if ((ENABLE_MPLAYER_MUSIC) && ((ENABLE_LYRICS3) || (ENABLE_LRC_LYRIC)))
    Music_Lyric_Tag curLyricTag;
#endif  // #if ENABLE_MPLAYER_MUSIC
    BOOLEAN bContinue;
    EN_RET eRet=EXIT_NULL;
    U8 *pu8Dst=NULL;

//    enumMPlayerUSBDeviceStatus eUSBDeviceStatus;
    enumMPlayerIdx eMPlayerIdx=E_MPLAYER_FOREGROUND_PLAYER;
    MPlayerFileInfo fileInfo;
    VIDEO_PLAYER_PLAYING_TYPE eType = VIDEO_PLAYER_PLAYING_TYPE_INVALID;

#if (!ENABLE_MPLAYER_MOVIE)
    UNUSED(eType);
#endif

    if((m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_DEVICE_INITIALIZED)
        && (msAPI_Timer_DiffTimeFromNow(m_u32DeviceCheckTimer) > 500)
#if ENABLE_MPLAYER_PLUGIN
        && (!MApp_MPlayer_IsPlugInAppPlaying())
#endif
        )
    {
        MApp_MPlayer_CheckUSBStatus();

#if ENABLE_USB_DETECT_STEP_BY_STEP
        if( (m_MPlayerUSBDetect.eCurrentState==STATE_USB_DETECT_GET_DEVICE_AND_DRIVE) ||
            (MApp_MPlayer_IsMoviePlaying()) )
#endif
        {
            m_u32DeviceCheckTimer = msAPI_Timer_GetTime0();
        }
    }

#if ENABLE_MPLAYER_PHOTO
    bThumbnail = FALSE;
    bPreview = FALSE;
#if (THUMBNAIL_PRIORITY_HIGHER_PREVIEW)
    if(m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_THUMBNAIL)
    {
        bThumbnail = TRUE;
    }
    else if(m_ePhotoPreviewState != E_PHOTO_PREVIEW_NONE)
    {
        bPreview = TRUE;
    }
#else
    if(m_ePhotoPreviewState != E_PHOTO_PREVIEW_NONE)
    {
        bPreview = TRUE;
    }
    else if(m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_THUMBNAIL)
    {
        bThumbnail = TRUE;
    }
#endif

    if(bPreview)
    {
        switch(m_ePhotoPreviewState)
        {
        case E_PHOTO_PREVIEW_TIMER_ENABLE:       // Begin count down.
            if(msAPI_Timer_DiffTimeFromNow(m_u32PreviewTimer) > PHOTO_PREVIEW_DELAY_TIME_MS)
            {
                if(MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,
                                              m_u16CurFileIdx,
                                              &fileInfo) == E_MPLAYER_RET_OK)
                {
                #if (ENABLE_3D_PROCESS)
                    if(DB_3D_SETTING.en3DType != EN_3D_BYPASS)
                    {
                        msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
                        DB_3D_SETTING.en3DType = EN_3D_BYPASS;
                      #if ENABLE_NEW_3D_FLOW
                        MApp_Scaler_SetVideo3DMode(EN_3D_BYPASS);
                      #else
                        MApp_Scaler_SetVideo3DMode(MAPP_Scaler_Map3DFormatTo3DUserMode(E_XC_3D_INPUT_MODE_NONE));
                      #endif
                        msAPI_Scaler_SetBlueScreen(DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
                    }
                #endif
                    _MApp_MPlayer_PlayerInit(E_MPLAYER_FOREGROUND_PLAYER, m_eMediaType, TRUE);
                    memcpy(&m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].curPlayingFileEntry,
                            &fileInfo.fileEntry,
                            sizeof(FileEntry));

                    if (IS_PHOTO_FILE(fileInfo.u8ExtFileName))
                    {
                        if (IS_JPG_FILE(fileInfo.u8ExtFileName))
                        {
                            m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType = E_MPLAYER_SUBTYPE_JPG;
                        }
                        #if (ENABLE_BMP)
                        else if (IS_BMP_FILE(fileInfo.u8ExtFileName))
                        {
                            m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType = E_MPLAYER_SUBTYPE_BMP;
                        }
                        #endif
                        #if (ENABLE_PNG)
                        else if (IS_PNG_FILE(fileInfo.u8ExtFileName))
                        {
                            m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType = E_MPLAYER_SUBTYPE_PNG;
                        }
                        #endif
                        #if (ENABLE_TIFF)
                        else if (IS_TIFF_FILE(fileInfo.u8ExtFileName))
                        {
                            m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType = E_MPLAYER_SUBTYPE_TIFF;
                        }
                        #endif
                        #if (ENABLE_GIF)
                        else if (IS_GIF_FILE(fileInfo.u8ExtFileName))
                        {
                            m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType = E_MPLAYER_SUBTYPE_GIF;
                        }
                        #endif

                    #if (ENABLE_4K2K)
                        ST_PHOTO_DECODE_RESOLUTION_DEFINTIONS stPhotoResolution;
                        _MApp_MPlayer_RestrictPhotoDecodeResolution(&stPhotoResolution);

                        MApp_Photo_DecodeResolutionCfg(stPhotoResolution);
                    #endif

                        if (MApp_Photo_DecodeFile_Init(&m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].curPlayingFileEntry, FALSE) == TRUE)
                        {
                            EN_PHOTO_ORIENTATION eOrientation;
#if (SHOW_PARTIALLY_DECODING_PHOTO)
                            MApp_Photo_InitPreviewDisplay();
#endif // #if (SHOW_PARTIALLY_DECODING_PHOTO)

                            m_photoInfo.u16Width    = MApp_Photo_GetInfo(E_PHOTO_INFO_IMAGE_WIDTH);
                            m_photoInfo.u16Height   = MApp_Photo_GetInfo(E_PHOTO_INFO_IMAGE_HEIGHT);
                            m_photoInfo.u32FileSize = MApp_Photo_GetInfo(E_PHOTO_INFO_FILE_SIZE);

                            //Update Exif information
                            m_photoInfo.u32ExifWidth    = MApp_Photo_GetInfo(E_PHOTO_INFO_EXIF_WIDTH);
                            m_photoInfo.u32ExifHeight   = MApp_Photo_GetInfo(E_PHOTO_INFO_EXIF_HEIGHT);
                            MApp_Photo_GetExifInfo(E_PHOTO_EXIF_INFO_CAMERA_MAKER,  &m_photoInfo.au8CameraMaker, sizeof(m_photoInfo.au8CameraMaker));
                            MApp_Photo_GetExifInfo(E_PHOTO_EXIF_INFO_CAMERA_MODEL,  &m_photoInfo.au8CameraModel, sizeof(m_photoInfo.au8CameraModel));
                            MApp_Photo_GetExifInfo(E_PHOTO_EXIF_INFO_FLASH_MODE,    &m_photoInfo.u32FlashMode,   sizeof(m_photoInfo.u32FlashMode));
                            MApp_Photo_GetExifInfo(E_PHOTO_EXIF_INFO_ISO_SPEED,     &m_photoInfo.u32ISOSpeed,    sizeof(m_photoInfo.u32ISOSpeed));
                            MApp_Photo_GetExifInfo(E_PHOTO_EXIF_INFO_EXPOSURE_BIAS, &m_photoInfo.stExposureBias, sizeof(m_photoInfo.stExposureBias));
                            MApp_Photo_GetExifInfo(E_PHOTO_EXIF_INFO_EXPOSURE_TIME, &m_photoInfo.stExposureTime, sizeof(m_photoInfo.stExposureTime));
                            MApp_Photo_GetExifInfo(E_PHOTO_EXIF_INFO_F_STOP,        &m_photoInfo.stF_Stop,       sizeof(m_photoInfo.stF_Stop));

                            m_photoInfo.bHasDateTime = MApp_Photo_GetInfo(E_PHOTO_INFO_HAS_DATE_TIME);
                            eOrientation = (EN_PHOTO_ORIENTATION)MApp_Photo_GetInfo(E_PHOTO_INFO_ORIENTATION);
                            if(eOrientation < E_PHOTO_ORIENT_NOT_FOUND)
                            {
                                m_photoInfo.eOrientation = (enumMPlayerJPGOrient)eOrientation;
                            }
                            else
                            {
                                m_photoInfo.eOrientation = E_MPLAYER_JPEG_ORIENT_ORIGINAL;
                            }

                            if (m_photoInfo.bHasDateTime)
                            {
                                m_photoInfo.u32Year     = MApp_Photo_GetInfo(E_PHOTO_INFO_DATE_TIME_YEAR);
                                m_photoInfo.u32Month    = MApp_Photo_GetInfo(E_PHOTO_INFO_DATE_TIME_MONTH);
                                m_photoInfo.u32Day      = MApp_Photo_GetInfo(E_PHOTO_INFO_DATE_TIME_DAY);
                                m_photoInfo.u32Hour     = MApp_Photo_GetInfo(E_PHOTO_INFO_DATE_TIME_HOUR);
                                m_photoInfo.u32Minute   = MApp_Photo_GetInfo(E_PHOTO_INFO_DATE_TIME_MINUTE);
                                m_photoInfo.u32Second   = MApp_Photo_GetInfo(E_PHOTO_INFO_DATE_TIME_SECOND);
                            }

                            if(MApp_Photo_GetInfo(E_PHOTO_INFO_FILE_FORMAT) == E_PHOTO_FILE_GIF)
                            {
                                MApp_Photo_GIFResetDisplay();
                            }
                            NOTIFY(E_MPLAYER_NOTIFY_BEFORE_PHOTO_PREVIEW, NULL);
                            m_ePhotoPreviewState = E_PHOTO_PREVIEW_RUNNING;
                        }
                        else
                        {
                            NOTIFY(E_MPLAYER_NOTIFY_ERROR_OF_PLAY_FILE, &m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaType);
                            m_ePhotoPreviewState = E_PHOTO_PREVIEW_NONE;
                        }
                    }
                }
            }
            break;

        case E_PHOTO_PREVIEW_RUNNING:            // Initialize preview.
            if ((m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_JPG)
                #if (ENABLE_BMP)
                    || (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_BMP)
                #endif
                #if (ENABLE_PNG)
                    || (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_PNG)
                #endif
                #if (ENABLE_TIFF)
                    || (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_TIFF)
                #endif
                    )
            {
                switch (MApp_Photo_Main())
                {
                    case EXIT_PHOTO_DECODE_FAIL:
                        MApp_Photo_Stop();
                        m_ePhotoPreviewState = E_PHOTO_PREVIEW_NONE;
                        NOTIFY(E_MPLAYER_NOTIFY_ERROR_OF_PLAY_FILE, &m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaType);
                        break;

                    case EXIT_PHOTO_DECODE_ONE_FRAME_DONE:
                        if(MApp_Photo_GetInfo(E_PHOTO_INFO_IS_MPO_DISPARITY_TYPE) == TRUE)
                        {
                            //for mpo preview, only decode first frame.
                            MApp_Photo_Stop();
                        }
                        // fall through
                    case EXIT_PHOTO_DECODE_DONE:
                        if(MApp_Photo_GetInfo(E_PHOTO_INFO_IS_MPO_DISPARITY_TYPE) == TRUE)
                        {
                            MApp_Photo_MPODisplay(TRUE);
                        }
                        else
                        {
                            MApp_Photo_Display(TRUE);
                        }
                        MApp_Photo_Stop();
                        m_ePhotoPreviewState = E_PHOTO_PREVIEW_DONE;
                        NOTIFY(E_MPLAYER_NOTIFY_END_OF_PHOTO_PREVIEW, NULL);
                        break;

#if (SHOW_PARTIALLY_DECODING_PHOTO)
                    case EXIT_PHOTO_DECODING:
#if ENABLE_AUTO_ROTATION
                        //if has rotation, show when decode done
                        if(m_photoInfo.eOrientation < E_MPLAYER_JPEG_ORIENT_TOP_RIGHT || m_photoInfo.eOrientation > E_MPLAYER_JPEG_ORIENT_LEFT_BOTTOM)
#endif
                        {
                            MApp_Photo_Display(TRUE);
                        }
                        // fall through
#endif // #if (SHOW_PARTIALLY_DECODING_PHOTO)

                    default:
                        break;
                }
            }
#if (ENABLE_GIF)
            else if(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_GIF)
            {
                switch (MApp_Photo_Main())
                {
                    case EXIT_PHOTO_DECODE_FAIL:
                        MApp_Photo_Stop();
                        m_ePhotoPreviewState = E_PHOTO_PREVIEW_NONE;
                        NOTIFY(E_MPLAYER_NOTIFY_ERROR_OF_PLAY_FILE, &m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaType);
                        break;

                    case EXIT_PHOTO_DECODE_DONE:
                        break;

#if (SHOW_PARTIALLY_DECODING_PHOTO)
                    case EXIT_PHOTO_DECODING:
                        if(MApp_Photo_GetInfo(E_PHOTO_INFO_DECODED_FRAME_INDEX) == 0xFFFFFFFF)
                        {
                            MApp_Photo_Display(TRUE);
                        }
                        // fall through
#endif // #if (SHOW_PARTIALLY_DECODING_PHOTO)
                    default:
                        break;
                }
                if(MApp_Photo_GIFIsDisplayDone())
                {
                    MApp_Photo_Stop();
                    m_ePhotoPreviewState = E_PHOTO_PREVIEW_DONE;
                    NOTIFY(E_MPLAYER_NOTIFY_END_OF_PHOTO_PREVIEW, NULL);
                }
                else
                {
                    MApp_Photo_GIFDisplay(TRUE);
                }
            }
#endif
            break;

        default:
            break;
        }
    }
    else if(bThumbnail) //Will not go this way now
    {
        ST_PHOTO_CAPTURE_RECT stPhotoImgTo, stPhotoImgFrom;
        MPlayerNotifyOneThumbnail notifyThumbnail;

        msAPI_Timer_ResetWDT();

        if(m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_THUMBNAIL_INIT)
        {
            m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType = E_MPLAYER_SUBTYPE_INVALID;
            if(MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,
                                          m_u16CurPage1stFileIdx+m_u8CurThumbnailDrawIdx,
                                          &fileInfo) == E_MPLAYER_RET_OK)
            {
                memcpy(&m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].curPlayingFileEntry,
                        &fileInfo.fileEntry,
                        sizeof(FileEntry));

                if (IS_PHOTO_FILE(fileInfo.u8ExtFileName))
                {
                    if (IS_JPG_FILE(fileInfo.u8ExtFileName))
                    {
                        BOOLEAN bInitOk;

                        // ask photo decoder to decode thumbnail
                        bInitOk = MApp_Photo_DecodeFile_Init(&m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].curPlayingFileEntry, TRUE);

#if ENABLE_DECODE_FULL_PHOTO_IF_NOTHUMB
                        if ((bInitOk == FALSE) && (MApp_Photo_GetErrCode() == E_PHOTO_ERR_NO_THUMBNAIL))
                        {
                            // ask photo decoder to decode full image because no thumbnail can be found
                            MApp_Photo_Stop();

                            bInitOk = MApp_Photo_DecodeFile_Init(&m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].curPlayingFileEntry, FALSE);
                        }
#endif // #if ENABLE_DECODE_FULL_PHOTO_IF_NOTHUMB

                        if (bInitOk == TRUE)
                        {
                            if (IS_JPG_FILE(fileInfo.u8ExtFileName))
                            {
                                m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType = E_MPLAYER_SUBTYPE_JPG;
                            }
                        }
                    }
                }
            }
            else
            {
                m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_THUMBNAIL;
            }
            m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_THUMBNAIL_INIT;
        }

        if(m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_THUMBNAIL)
        {
            if(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_JPG)
            {
                eRet = MApp_Photo_Main();
            }
            else
            {
                eRet = EXIT_PHOTO_DECODE_NO_THUMBNAIL;
            }

            switch (eRet)
            {
            case EXIT_PHOTO_DECODE_FAIL:
            case EXIT_PHOTO_DECODE_NO_THUMBNAIL:
            default:
                // send decode fail notification
                notifyThumbnail.u16FileIdx = m_u8CurThumbnailDrawIdx;
                notifyThumbnail.bOK = FALSE;
                NOTIFY(E_MPLAYER_NOTIFY_END_OF_ONE_THUMBNAIL, &notifyThumbnail);

                // decode next file
                m_u8ThumbnailNIdx++;
                m_eMPlayerKnlFlags |= E_MPLAYER_KNL_FLG_THUMBNAIL_INIT;
                break;

            case EXIT_PHOTO_DECODE_ONE_FRAME_DONE:
                if(MApp_Photo_GetInfo(E_PHOTO_INFO_IS_MPO_DISPARITY_TYPE) == TRUE)
                {
                    //for mpo thumbnail, only decode first frame.
                    MApp_Photo_Stop();
                }
                // fall through
            case EXIT_PHOTO_DECODE_DONE:
                memset(&stPhotoImgTo, 0, sizeof(stPhotoImgTo));
                memset(&stPhotoImgFrom, 0, sizeof(stPhotoImgFrom));

                stPhotoImgTo.u32BuffAddr = m_thumbnailFbAttr.addr;
                stPhotoImgTo.u16BuffW = m_thumbnailFbAttr.width;
                stPhotoImgTo.u16BuffH = m_thumbnailFbAttr.height;
                stPhotoImgTo.u8FbFmt = GFX_FMT_ARGB1555;

                stPhotoImgFrom.u16RectX= 0;
                stPhotoImgFrom.u16RectY = 0;
                stPhotoImgFrom.u16RectW = MApp_Photo_GetInfo(E_PHOTO_INFO_WIDTH) & 0xfffc;
                stPhotoImgFrom.u16RectH = MApp_Photo_GetInfo(E_PHOTO_INFO_HEIGHT);

                // Refine the start position of thumbnail.
                stPhotoImgTo.u16RectX = m_u16ThumbnailArray[m_u8CurThumbnailDrawIdx][0]+UI_MEDIAPLAYER_MAINITEM_FRM_LINE_WIDTH;
                stPhotoImgTo.u16RectY = m_u16ThumbnailArray[m_u8CurThumbnailDrawIdx][1]+UI_MEDIAPLAYER_MAINITEM_FRM_LINE_WIDTH;
                stPhotoImgTo.u16RectW = THUMBNAIL_WIDTH;
                stPhotoImgTo.u16RectH = THUMBNAIL_HEIGHT;

                MApp_Photo_Display_Thumbnail(
                        &stPhotoImgTo,
                        &stPhotoImgFrom,
                        EN_PHOTO_ALIGN_MIDDLE_CENTERED,
                        EN_PHOTO_FIT_BOUNDARY);

                // send decode done notification
                notifyThumbnail.u16FileIdx = m_u8CurThumbnailDrawIdx;
                notifyThumbnail.bOK = TRUE;
                NOTIFY(E_MPLAYER_NOTIFY_END_OF_ONE_THUMBNAIL, &notifyThumbnail);

                m_u8CurThumbnailDrawIdx++;
                m_eMPlayerKnlFlags |= E_MPLAYER_KNL_FLG_THUMBNAIL_INIT;
                break;

            case EXIT_PHOTO_DECODING:
                break;
            }
        }

        if((m_u8CurThumbnailDrawIdx >= NUM_OF_THUMBNAIL_FILES_PER_PAGE) ||
           !(m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_THUMBNAIL))
        {
            NOTIFY(E_MPLAYER_NOTIFY_END_OF_THUMBNAIL, NULL);
            m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_THUMBNAIL;
        }
    }
    else
#endif  // #if ENABLE_MPLAYER_PHOTO
#if ENABLE_MPLAYER_MUSIC

    if(m_eMusicPreviewState != E_MUSIC_PREVIEW_NONE)
    {
        switch(m_eMusicPreviewState)
        {
        case E_MUSIC_PREVIEW_TIMER_ENABLE:       // Begin count down.
            if(msAPI_Timer_DiffTimeFromNow(m_u32PreviewTimer) > MUSIC_PREVIEW_DELAY_TIME_MS)
            {
                if(MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,
                                              m_u16CurFileIdx,
                                              &fileInfo) == E_MPLAYER_RET_OK)
                {
                    MApp_Music_Stop();
                #if (ENABLE_WMA)
                    MApp_WMA_Stop();
                #endif
                    m_u32PlayCheckTime = -1;
                    _MApp_MPlayer_PlayerInit(E_MPLAYER_BACKGROUND_PLAYER, m_eMediaType, TRUE);
                    memcpy(&m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].curPlayingFileEntry,
                            &fileInfo.fileEntry,
                            sizeof(FileEntry));
                #if (ENABLE_FLAC)
                    if ( IS_FLAC_FILE(fileInfo.u8ExtFileName) )
                    {
                        m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_FLAC; //FLAC
                    }
                    else
                #endif
                #if (ENABLE_AC3)
                    if ( IS_AC3_FILE(fileInfo.u8ExtFileName) )
                    {
                        m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_AC3; //AC3
                    }
                    else
                #endif
                #if (ENABLE_AAC)
                    if ( IS_AAC_FILE(fileInfo.u8ExtFileName) )
                    {
                        m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_AAC; //AAC
                    }
                    else
                #endif
                #if (ENABLE_WAV)
                    if ( IS_WAV_FILE(fileInfo.u8ExtFileName) )
                    {
                        m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_WAV; //WAV
                    }
                    else
                #endif
                #if (ENABLE_WMA)
                    if ( IS_WMA_FILE(fileInfo.u8ExtFileName) )
                    {
                        m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_WMA; //WMA
                    }
                    else
                #endif //#if (ENABLE_WMA)
                #if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
                    if(IS_LOAS_FILE(fileInfo.u8ExtFileName))
                    {
                        m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_LOAS;
                    }
                    else
                #endif //#if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
                #if (ENABLE_OGG)
                    if(IS_OGG_FILE(fileInfo.u8ExtFileName))
                    {
                        m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_OGG;
                    }
                    else
                #endif
#if (ENABLE_AMR)
                    if ( IS_AMR_FILE(fileInfo.u8ExtFileName) )
                    {
                        m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_AMR; //AMR
                    }
                    else if ( IS_AWB_FILE(fileInfo.u8ExtFileName) )
                    {
                        m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_AWB; //AWB
                    }
                    else
#endif
                    {
                        m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_MP3; //MP3
                    }

                #if (!ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
                    m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType = _MApp_MPlayer_VerifyMusicType(&m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].curPlayingFileEntry, m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType);
                #endif //#if (!ENABLE_NON_PARSING_AUDIO_DATA_INPUT)

                    switch(m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType)
                    {
#if (ENABLE_AAC)
                        case E_MPLAYER_SUBTYPE_AAC:
#endif
#if (ENABLE_WAV)
                        case E_MPLAYER_SUBTYPE_WAV:
#endif
                        default:
                        case E_MPLAYER_SUBTYPE_MP3:
#if (ENABLE_OGG)
                        case E_MPLAYER_SUBTYPE_OGG:
#endif
#if (ENABLE_AMR)
                        case E_MPLAYER_SUBTYPE_AMR:
                        case E_MPLAYER_SUBTYPE_AWB:
#endif
#if (ENABLE_FLAC)
                        case E_MPLAYER_SUBTYPE_FLAC:
#endif
#if (ENABLE_AC3)
                        case E_MPLAYER_SUBTYPE_AC3:
#endif
#if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
                        case E_MPLAYER_SUBTYPE_LOAS:
#endif //#if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
                            MApp_Music_SetFileEntry(&m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].curPlayingFileEntry);
                            MApp_Music_Init();
                            break;
#if (ENABLE_WMA)
                        case E_MPLAYER_SUBTYPE_WMA:
                            MApp_WMA_SetFileEntry(&m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].curPlayingFileEntry);
                            MApp_Wma_Init();
                            break;
#endif //#if (ENABLE_WMA)
                    }

                    NOTIFY(E_MPLAYER_NOTIFY_BEFORE_MUSIC_PREVIEW, NULL);
                    m_eMusicPreviewState = E_MUSIC_PREVIEW_RUNNING;
                }
            }
            break;
        case E_MUSIC_PREVIEW_RUNNING:            // Initialize preview.
            switch(m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType)
            {
        #if (ENABLE_WMA)
            case E_MPLAYER_SUBTYPE_WMA:
                eRet = MApp_WMA_Main();
                break;
        #endif
        #if (ENABLE_FLAC)
            case E_MPLAYER_SUBTYPE_FLAC:
                eRet = MApp_Music_Main(EN_MUSIC_FLAC);
                break;
        #endif
        #if (ENABLE_AC3)
            case E_MPLAYER_SUBTYPE_AC3:
                eRet = MApp_Music_Main(EN_MUSIC_AC3);
                break;
        #endif
        #if (ENABLE_AAC)
            case E_MPLAYER_SUBTYPE_AAC:
                eRet = MApp_Music_Main(EN_MUSIC_AAC);
                break;
        #endif
        #if (ENABLE_WAV)
            case E_MPLAYER_SUBTYPE_WAV:
                eRet = MApp_Music_Main(EN_MUSIC_WAV);
                break;
        #endif

            case E_MPLAYER_SUBTYPE_MP3:
                eRet = MApp_Music_Main(EN_MUSIC_MP3);
                break;

        #if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
            case E_MPLAYER_SUBTYPE_LOAS:
                eRet = MApp_Music_Main(EN_MUSIC_LOAS);
                break;
        #endif

        #if (ENABLE_OGG)
            case E_MPLAYER_SUBTYPE_OGG:
                eRet = MApp_Music_Main(EN_MUSIC_OGG);
                break;
        #endif

        #if (ENABLE_AMR)
            case E_MPLAYER_SUBTYPE_AMR:
                eRet = MApp_Music_Main(EN_MUSIC_AMR);
                break;

            case E_MPLAYER_SUBTYPE_AWB:
                eRet = MApp_Music_Main(EN_MUSIC_AWB);
                break;
        #endif
            default:
                eRet = EXIT_NULL;
                break;
            }

        #if (ENABLE_WMA)
            if (E_MPLAYER_SUBTYPE_WMA == m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType)
            {
                switch(eRet)
                {
                case EXIT_WMA_WAIT:
                    //m_eMusicPreviewState = E_MUSIC_PREVIEW_NONE;
                    NOTIFY(E_MPLAYER_NOTIFY_END_OF_MUSIC_PREVIEW, NULL);//will set m_eMusicPreviewState to none
                  #if (MUSIC_REPEAT_PREVIEW)
                    m_eMusicPreviewState = E_MUSIC_PREVIEW_TIMER_ENABLE;
                  #endif
                    m_u32PlayCheckTime = -1;
                    break;

                case EXIT_WMA_EXIT:
                    m_eMusicPreviewState = E_MUSIC_PREVIEW_NONE;
                    NOTIFY(E_MPLAYER_NOTIFY_ERROR_OF_PLAY_FILE, &m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaType);
                    m_u32PlayCheckTime = -1;
                    break;


                case EXIT_WMA_INPUT:
                    NOTIFY(E_MPLAYER_NOTIFY_SHOW_MUSIC_NFO, NULL);
                    break;

                case EXIT_WMA_INIT:
                    m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_LYRIC_VALID;
                  #if (ENABLE_LRC_LYRIC)
                    if(_MApp_MPlayer_Music_Lyric_Parser())
                    {
                        m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_LYRIC_VALID;
                    }
                  #endif
                    //go on to next process
                default:

                    if(msAPI_Timer_DiffTimeFromNow(m_u32PlayCheckTime)>100)
                    {
                    #if (ENABLE_LYRICS3) || (ENABLE_LRC_LYRIC)
                        if((m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_LYRIC_VALID) &&
                            (m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_LYRIC_ENABLE))
                        {
                            u32CurTime = MApp_WMA_GetCurrentTimeMs();
                            if(MApp_Music_GetLyricTag(&curLyricTag, u32CurTime))
                            {
                                if(curLyricTag.u32Time != m_u32LyricSubtitleCurTime)
                                {
                                    pu8Dst = msAPI_Memory_Allocate(LYRIC_MAX_SIZE+2, BUF_ID_FILEBROWER);

                                    if(pu8Dst)
                                    {
                                        _MApp_MPlayer_GetLyric(curLyricTag.u16LyricPos, pu8Dst);
                                        NOTIFY(E_MPLAYER_NOTIFY_SHOW_LYRIC, pu8Dst);
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
                    #endif

                        // Music time tick
                        u32CurTime = MApp_WMA_GetCurrentTime();
                        if (m_u32PlayingTickTime != u32CurTime)
                        {
                            m_u32PlayingTickTime = u32CurTime;
                            NOTIFY(E_MPLAYER_NOTIFY_PLAYING_TIME_TICK,
                                    (U32*)&m_u32PlayingTickTime);
                        }

                        m_u32PlayCheckTime = msAPI_Timer_GetTime0();
                    }
                    break;
                } //end switch (eRet)
            }
            else
        #endif //#if (ENABLE_WMA)
            {
                switch(eRet)
                {
                case EXIT_MP3_WAIT:
                    //m_eMusicPreviewState = E_MUSIC_PREVIEW_NONE;
                    NOTIFY(E_MPLAYER_NOTIFY_END_OF_MUSIC_PREVIEW, NULL);
                  #if (MUSIC_REPEAT_PREVIEW)
                    m_eMusicPreviewState = E_MUSIC_PREVIEW_TIMER_ENABLE;
                  #endif
                    m_u32PlayCheckTime = -1;
                    break;

                case EXIT_MP3_EXIT:
                    m_eMusicPreviewState = E_MUSIC_PREVIEW_NONE;
                    NOTIFY(E_MPLAYER_NOTIFY_ERROR_OF_PLAY_FILE, &m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaType);
                    m_u32PlayCheckTime = -1;
                    break;

                case EXIT_MP3_INPUT:
                    NOTIFY(E_MPLAYER_NOTIFY_SHOW_MUSIC_NFO, NULL);
                    break;

                case EXIT_MP3_INIT:
                    //E_MPLAYER_KNL_FLG1_LYRIC_VALID have to set before NOTIFY function!
                    m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_LYRIC_VALID;
                  #if (ENABLE_LRC_LYRIC)
                    if(_MApp_MPlayer_Music_Lyric_Parser())
                    {
                        m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_LYRIC_VALID;
                    }
                  #endif
                    //go on to next process

                default:
                    if(msAPI_Timer_DiffTimeFromNow(m_u32PlayCheckTime)>100)
                    {
                    #if (ENABLE_LYRICS3) || (ENABLE_LRC_LYRIC)
                        if((m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_LYRIC_VALID) &&
                            (m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_LYRIC_ENABLE))
                        {
                            u32CurTime = MApp_Music_GetCurrentTimeMs();
                            if(MApp_Music_GetLyricTag(&curLyricTag, u32CurTime))
                            {
                                if(curLyricTag.u32Time != m_u32LyricSubtitleCurTime)
                                {
                                    pu8Dst = msAPI_Memory_Allocate(LYRIC_MAX_SIZE+2, BUF_ID_FILEBROWER);

                                    if(pu8Dst)
                                    {
                                        _MApp_MPlayer_GetLyric(curLyricTag.u16LyricPos, pu8Dst);
                                        NOTIFY(E_MPLAYER_NOTIFY_SHOW_LYRIC, pu8Dst);
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
                    #endif

                        // Music time tick
                        u32CurTime = MApp_Music_GetCurrentTime();
                        if (m_u32PlayingTickTime != u32CurTime)
                        {
                            m_u32PlayingTickTime = u32CurTime;
                            NOTIFY(E_MPLAYER_NOTIFY_PLAYING_TIME_TICK,
                                    (U32*)&m_u32PlayingTickTime);
                        }

                        m_u32PlayCheckTime = msAPI_Timer_GetTime0();
                    }
                    break;
                } //end switch (eRet)
            } // end else

            break;
        default:
            break;
        }
    }
    else
#endif  // #if ENABLE_MPLAYER_MUSIC

#if ENABLE_MPLAYER_MOVIE
    if(m_eMoviePreviewState != E_MOVIE_PREVIEW_NONE)
    {
        switch(m_eMoviePreviewState)
        {
        case E_MOVIE_PREVIEW_TIMER_ENABLE:       // Begin count down.
            if(msAPI_Timer_DiffTimeFromNow(m_u32PreviewTimer) > MOVIE_PREVIEW_DELAY_TIME_MS)
            {
                if(MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,
                                              m_u16CurFileIdx,
                                              &fileInfo) == E_MPLAYER_RET_OK)
                {
                    eType=VIDEO_PLAYER_PLAYING_TYPE_INVALID;

                    _MApp_MPlayer_PlayerInit(E_MPLAYER_FOREGROUND_PLAYER, m_eMediaType, TRUE);
                    memcpy(&m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].curPlayingFileEntry,
                            &fileInfo.fileEntry,
                            sizeof(FileEntry));
                    _MApp_MPlayer_OutputFilename(&fileInfo);

                #if (ENABLE_DVD)
                    if(IS_DVD_FILE(fileInfo.u8ExtFileName))
                    {
                        eType = VIDEO_PLAYER_PLAYING_TYPE_DVD;
                        m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType = E_MPLAYER_SUBTYPE_DVD;
                    }

                    if (eType == VIDEO_PLAYER_PLAYING_TYPE_DVD)
                    {
                        MApp_VDPlayer_BeginPreview();
                        if(MApp_VDPlayer_DVD_Init(VIDEO_PLAYER_INPUT_SOURCE_MM, eType, &m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].curPlayingFileEntry) == TRUE)
                        {
                            m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType = E_MPLAYER_SUBTYPE_DVD;
                            m_eMoviePreviewState = E_MOVIE_PREVIEW_RUNNING;
                        }
                        else
                        {
                            MApp_VDPlayer_StopPreview();
                            m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType = E_MPLAYER_SUBTYPE_INVALID;
                            NOTIFY(E_MPLAYER_NOTIFY_ERROR_OF_PLAY_FILE, &m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaType);
                            m_eMoviePreviewState = E_MOVIE_PREVIEW_NONE;
                        }
                    }
                    else
                #endif  // ENABLE_DVD

//                    if(eType < VIDEO_PLAYER_PLAYING_TYPE_NUM)
                    {
                        MApp_VDPlayer_BeginPreview();
                    #if (ENABLE_3D_PROCESS)
                        if(DB_3D_SETTING.en3DType != EN_3D_BYPASS)
                        {
                            msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
                            DB_3D_SETTING.en3DType = EN_3D_BYPASS;
                          #if ENABLE_NEW_3D_FLOW
                            MApp_Scaler_SetVideo3DMode(EN_3D_BYPASS);
                          #else
                            MApp_Scaler_SetVideo3DMode(MAPP_Scaler_Map3DFormatTo3DUserMode(E_XC_3D_INPUT_MODE_NONE));
                          #endif
                            msAPI_Scaler_SetBlueScreen(DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
                        }
                    #endif
                        m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &=
                            (enumMPlayerKnlFlags1)~(E_MPLAYER_KNL_FLG1_SUBTITLE_VALID |
                              E_MPLAYER_KNL_FLG1_SUBTITLE_ENABLE |
                              E_MPLAYER_KNL_FLG1_SUBTITLE_SHOWN |
                              E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL);

                    #if 0//(ENABLE_SUBTITLE_DMP)
                        if(_MApp_MPlayer_MP4_Subtitle_Parser())
                        {
                            m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= (E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL);
                        }
                    #endif

                        if(MApp_VDPlayer_Init(VIDEO_PLAYER_INPUT_SOURCE_MM, eType, &m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].curPlayingFileEntry) == TRUE)
                        {
                        #if ENABLE_DRM
                            if (MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_DRM_FILE_FORMAT)==TRUE)
                            {
                                MApp_VDPlayer_Stop();
                            #if (ENABLE_SUBTITLE_DMP)
                                if(m_u8ExternalSubtitleFileHandle != FCTRL_INVALID_FILE_HANDLE)
                                {
                                    msAPI_FCtrl_FileClose(m_u8ExternalSubtitleFileHandle);
                                    m_u8ExternalSubtitleFileHandle = FCTRL_INVALID_FILE_HANDLE;
                                    #if (ENABLE_INTERNAL_BMP_SUBTITLE || ENABLE_EXTERNAL_BMP_SUBTITLE)
                                    msAPI_MpegSP_Dinit();
                                    #endif
                                }
                            #endif //#if (ENABLE_SUBTITLE_DMP)
                                MApp_VDPlayer_StopPreview();
                                m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType = E_MPLAYER_SUBTYPE_INVALID;
                                NOTIFY(E_MPLAYER_NOTIFY_ERROR_OF_PLAY_FILE, &m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaType);
                                m_eMoviePreviewState = E_MOVIE_PREVIEW_NONE;
                            }
                            else
                        #endif // #if ENABLE_DRM
                            {
                            #if DWIN_MOVIE_PREVIEW
                                GOP_GwinFBAttr stFbAttr;
                            #endif
                                m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType = E_MPLAYER_SUBTYPE_MOVIE;
                                #if (ENABLE_MOVIE_PREVIEW_1ST_FRAME)
                                m_eMoviePreviewState = E_MOVIE_PREVIEW_1ST_FRAME_PREDECODE;
                                #else
                                m_eMoviePreviewState = E_MOVIE_PREVIEW_RUNNING;
                                #endif
                                MApp_VDPlayer_Play();
                                MApp_VDPlayer_EnableVideoOutputFlag(ENABLE);
                                NOTIFY(E_MPLAYER_NOTIFY_BEFORE_MOVIE_PREVIEW, NULL);
                            #if DWIN_MOVIE_PREVIEW
                                //add to open GWIN here
                                MApp_VDPlayer_PreviewGWIN_Create(&stFbAttr);
                                // capture video by DWIN here
                                MApp_VDPlayer_DWINMoviePreview(stFbAttr);
                                //when leave DWIN movie preview, need to close GWIN and DWIN and FB.
                            #endif
                            }
                        }
                        else
                        {
                            MApp_VDPlayer_StopPreview();
                            m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType = E_MPLAYER_SUBTYPE_INVALID;
                            NOTIFY(E_MPLAYER_NOTIFY_ERROR_OF_PLAY_FILE, &m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaType);
                            m_eMoviePreviewState = E_MOVIE_PREVIEW_NONE;
                        }
                    }
                    m_eMovieMainExit = EXIT_VDPLAYER_NULL;
                }
            }
            break;

        case E_MOVIE_PREVIEW_RUNNING:            // Initialize preview.
            if(_MApp_MPlayer_IsSupportedMovie(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType))
            {

                if(m_eMovieMainExit != EXIT_VDPLAYER_WAIT &&
                   m_eMovieMainExit != EXIT_VDPLAYER_EXIT)
                {
                #if ENABLE_DVD
                    if(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_DVD)
                        m_eMovieMainExit = MApp_VDPlayer_DVD_Main();
                    else
                #endif
                    m_eMovieMainExit = MApp_VDPlayer_Main();
                }
                switch(m_eMovieMainExit)
                {
                case EXIT_VDPLAYER_WAIT:
            #if (ENABLE_MOVIE_PREVIEW_ALL_AND_1ST_FRAME)
                {
                    eType=VIDEO_PLAYER_PLAYING_TYPE_INVALID;
                #if ENABLE_DVD
                    if(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_DVD)
                    {
                        eType = VIDEO_PLAYER_PLAYING_TYPE_DVD;
                    }
                #endif

                    MApp_VDPlayer_EnableVideoOutputFlag(DISABLE);
                    if(MApp_VDPlayer_Init(VIDEO_PLAYER_INPUT_SOURCE_MM, eType, &m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].curPlayingFileEntry) == TRUE)
                    {
                        m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType = E_MPLAYER_SUBTYPE_MOVIE;

                        bMute = msAPI_AUD_IsAudioMutedByUser();

                        if(bMute)
                        {
                            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                        }
                        else
                        {
                            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                        }

                        m_eMoviePreviewState = E_MOVIE_PREVIEW_1ST_FRAME_DECODE;
                        g_b2ndRunPreviewMute = TRUE;
                        MApp_VDPlayer_Play();
                        m_u32PreviewTimer = msAPI_Timer_GetTime0();
                    }
                    else
                    {
                        MApp_VDPlayer_StopPreview();
                        m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType = E_MPLAYER_SUBTYPE_INVALID;
                        m_eMoviePreviewState = E_MOVIE_PREVIEW_NONE;
                        m_eMovieMainExit = EXIT_VDPLAYER_NULL;
                        NOTIFY(E_MPLAYER_NOTIFY_ERROR_OF_PLAY_FILE, &m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaType);
                    }
                }
            #elif (MOVIE_REPEAT_PREVIEW == 0)
                    MApp_VDPlayer_StopPreview();
                    m_eMoviePreviewState = E_MOVIE_PREVIEW_DONE;
                    NOTIFY(E_MPLAYER_NOTIFY_END_OF_MOVIE_PREVIEW, NULL);
            #elif (MOVIE_REPEAT_PREVIEW == 1)
                    m_u32PreviewTimer = msAPI_Timer_GetTime0();
                    m_eMoviePreviewState = E_MOVIE_PREVIEW_TIMER_ENABLE;
            #endif
                    m_eMovieMainExit = EXIT_VDPLAYER_NULL;
                    break;

                case EXIT_VDPLAYER_EXIT:
                    MApp_VDPlayer_StopPreview();
                    m_eMoviePreviewState = E_MOVIE_PREVIEW_DONE;
                    m_eMovieMainExit = EXIT_VDPLAYER_NULL;
                    //printf("[MPlayer] VD Player return (%ld)\n",MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_ERROR_INFO));
                    if(MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_ERROR_INFO) == EN_VDP_ERRORCODE_NONE)
                    {
                        NOTIFY(E_MPLAYER_NOTIFY_END_OF_MOVIE_PREVIEW, NULL);
                    }
                    else
                    {
                        NOTIFY(E_MPLAYER_NOTIFY_ERROR_OF_PLAY_FILE, &m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaType);
                    }
                    break;
                default:
                    break;
                }
            }
            break;

    #if (ENABLE_MOVIE_PREVIEW_ALL_AND_1ST_FRAME || ENABLE_MOVIE_PREVIEW_1ST_FRAME)
        case E_MOVIE_PREVIEW_1ST_FRAME_PREDECODE:
        case E_MOVIE_PREVIEW_1ST_FRAME_DECODE:
            bContinue = TRUE;

            while(msAPI_Timer_DiffTimeFromNow(m_u32PreviewTimer) <
                  ENABLE_MOVIE_PREVIEW_1ST_FRAME_POS_MS)
            {
                if(_MApp_MPlayer_IsSupportedMovie(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType))
                {
                    switch(MApp_VDPlayer_Main())
                    {
                    case EXIT_VDPLAYER_WAIT:
                    case EXIT_VDPLAYER_EXIT:
                        MApp_VDPlayer_StopPreview();
                        m_eMoviePreviewState = E_MOVIE_PREVIEW_DONE;
                        m_eMovieMainExit = EXIT_VDPLAYER_NULL;
                        bContinue = FALSE;
                        break;
                    default:
                        break;
                    }
                }
            }
            if(bContinue)
            {
                m_eMoviePreviewState = E_MOVIE_PREVIEW_DONE;
                m_eMovieMainExit = EXIT_VDPLAYER_NULL;
                MApp_Picture_Setting_SetColor(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
                MApp_VDPlayer_Stop();
                NOTIFY(E_MPLAYER_NOTIFY_END_OF_MOVIE_PREVIEW, NULL);

            #if (ENABLE_SUBTITLE_DMP)
                if(m_u8ExternalSubtitleFileHandle != FCTRL_INVALID_FILE_HANDLE)
                {
                    msAPI_FCtrl_FileClose(m_u8ExternalSubtitleFileHandle);
                    m_u8ExternalSubtitleFileHandle = FCTRL_INVALID_FILE_HANDLE;
                    #if (ENABLE_INTERNAL_BMP_SUBTITLE || ENABLE_EXTERNAL_BMP_SUBTITLE)
                    msAPI_MpegSP_Dinit();
                    #endif
                }
            #endif //#if (ENABLE_SUBTITLE_DMP)

                MApp_VDPlayer_StopPreview();

                if(bMute)
                {
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                }
                else
                {
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYUSER_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                }
            }

            if (g_b2ndRunPreviewMute == TRUE)
            {
                //printf("preview 2nd run audio unmute\n");
                g_b2ndRunPreviewMute = FALSE;
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            }
            break;
    #endif  // #if (ENABLE_MOVIE_PREVIEW_ALL_AND_1ST_FRAME || ENABLE_MOVIE_PREVIEW_1ST_FRAME)

        default:
            break;
        }
    }
    else
#endif  // #if ENABLE_MPLAYER_MOVIE

#if ENABLE_MPLAYER_TEXT
    if(m_eTextPreviewState != E_TEXT_PREVIEW_NONE)
    {
        switch(m_eTextPreviewState)
        {
        case E_TEXT_PREVIEW_TIMER_ENABLE:       // Begin count down.
            if(msAPI_Timer_DiffTimeFromNow(m_u32PreviewTimer) > TEXT_PREVIEW_DELAY_TIME_MS)
            {
                if(MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,
                                              m_u16CurFileIdx,
                                              &fileInfo) == E_MPLAYER_RET_OK)
                {
                    _MApp_MPlayer_PlayerInit(E_MPLAYER_FOREGROUND_PLAYER, m_eMediaType, TRUE);
                    memcpy(&m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].curPlayingFileEntry,
                            &fileInfo.fileEntry,
                            sizeof(FileEntry));

                    if(IS_TXT_FILE(fileInfo.u8ExtFileName))
                    {
                        MApp_Text_SetFileEntry(&m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].curPlayingFileEntry);
                        m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType = E_MPLAYER_SUBTYPE_TEXT;
                        m_eTextPreviewState = E_TEXT_PREVIEW_RUNNING;
                    }
                }
            }
            break;
        case E_TEXT_PREVIEW_RUNNING:            // Initialize preview.
            if(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_TEXT)
            {
                if(!MApp_Text_Preview())
                {
                    NOTIFY(E_MPLAYER_NOTIFY_ERROR_OF_PLAY_FILE, &m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaType);
                }
                else
                {
                    MApp_MPlayer_TextStopPreview();
                    NOTIFY(E_MPLAYER_NOTIFY_END_OF_TEXT_PREVIEW, NULL);
                }
            }
            m_eTextPreviewState = E_TEXT_PREVIEW_NONE;
            break;
        default:
            break;
        }
    }
#endif  // #if ENABLE_MPLAYER_TEXT

    if((
      #if ENABLE_MPLAYER_PHOTO
        !(m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_THUMBNAIL) &&
        (m_ePhotoPreviewState == E_PHOTO_PREVIEW_NONE) &&
      #endif  // #if ENABLE_MPLAYER_PHOTO

      #if ENABLE_MPLAYER_MUSIC
        (m_eMusicPreviewState == E_MUSIC_PREVIEW_NONE) &&
      #endif  // #if ENABLE_MPLAYER_MUSIC
        (m_eMoviePreviewState == E_MOVIE_PREVIEW_NONE) &&
        (m_eTextPreviewState  == E_TEXT_PREVIEW_NONE))
      #if ENABLE_BGM
        || MApp_MPlayer_IsMusicPlaying()
      #endif // #if ENABLE_BGM
        )
    {
        // check if foreground player need service
        if (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & (0
              #if ENABLE_MPLAYER_PHOTO
                | E_MPLAYER_KNL_FLG1_PHOTO_PLAY
              #endif  // #if ENABLE_MPLAYER_PHOTO
              #if ENABLE_MPLAYER_MOVIE
                | E_MPLAYER_KNL_FLG1_MOVIE_PLAY
              #endif  // #if ENABLE_MPLAYER_MOVIE
              #if ENABLE_MPLAYER_TEXT
                | E_MPLAYER_KNL_FLG1_TEXT_PLAY
              #endif  // #if ENABLE_MPLAYER_TEXT
              #if ENABLE_MPLAYER_PLUGIN
                | E_MPLAYER_KNL_FLG1_PLUGIN_PLAY
              #endif //#ifdef ENABLE_MPLAYER_PLUGIN
                ))
        {
            eMPlayerIdx = E_MPLAYER_FOREGROUND_PLAYER;

        #if ENABLE_MPLAYER_PHOTO
            if(m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 & E_MPLAYER_KNL_FLG1_PHOTO_PLAY)
            {
                bContinue = TRUE;
                m_MPlayerInfo[eMPlayerIdx].u32ErrorDelayTime = m_u32PhotoErrorDelayTimeS;
                if(m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 & E_MPLAYER_KNL_FLG1_FILE_INIT)
                {
                    if (MApp_Photo_DecodeFile_Init(&m_MPlayerInfo[eMPlayerIdx].curPlayingFileEntry, FALSE) == TRUE)
                    {
                        //printf("DecodeInit ok %u\n", m_MPlayerInfo[0].u16PlayingIdx);
                        m_ePhotoValidOrNot = E_MPLAYER_PHOTO_VALID;
                        m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_FILE_INIT;
                    }
                    else
                    {
                        m_ePhotoValidOrNot = E_MPLAYER_PHOTO_INVALID;
                        m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_FILE_INIT;
                    }
                }

                if(m_ePhotoValidOrNot == E_MPLAYER_PHOTO_VALID)
                {
                    //Because we do pre-decode , so if predecode done ,
                    //we can not send Notify to UI before "Current slide show display done " or "Error message display time out"
                    if(!(m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus & E_MPLAYER_PHOTO_STATE_DISPLAY)
                    && !(m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus & E_MPLAYER_PHOTO_STATE_ERROR_PENDING))
                    {
                        m_ePhotoValidOrNot = E_MPLAYER_PHOTO_WAIT;
                        NOTIFY(E_MPLAYER_NOTIFY_BEFORE_PLAY_ONE_FILE, &m_MPlayerInfo[eMPlayerIdx].eMediaType);
                    }
                }

                //loop check gif decode state, it can begin display after part frames decoded
                if(MApp_Photo_GetInfo(E_PHOTO_INFO_FILE_FORMAT) == E_PHOTO_FILE_GIF)
                {
                    MApp_Photo_GIFDisplay(FALSE);
                }

                if(m_u8DecodedPics && !(m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus & E_MPLAYER_PHOTO_STATE_PAUSE))
                {
                    if(!(m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus & E_MPLAYER_PHOTO_STATE_DISPLAY)
                    && !(m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus & E_MPLAYER_PHOTO_STATE_ERROR_PENDING))
                    {
                        BOOLEAN bCanPlayNext = FALSE;
                        EN_PHOTO_ORIENTATION eOrientation;

                    #if PHOTO_SLIDE_SHOW_EFFECT
                        //let it can be played with slide show effect when there is only one file under playing
                        if((m_MPlayerInfo[eMPlayerIdx].eRepeatMode == E_MPLAYER_REPEAT_1)
                       ||(((m_MPlayerInfo[eMPlayerIdx].u16TotalFileNum-m_MPlayerInfo[eMPlayerIdx].u16TotalDirNum == 1)||(m_u16SelectedFileNum[m_MPlayerInfo[eMPlayerIdx].eMediaType] == 1))
                        &&  m_MPlayerInfo[eMPlayerIdx].eRepeatMode == E_MPLAYER_REPEAT_ALL))
                        {
                        #if ENABLE_MPO_3D_PROCESS
                            // This MPO in 3D mode
                            if(MApp_Photo_GetInfo(E_PHOTO_INFO_IS_MPO_DISPARITY_TYPE) == FALSE)
                        #endif
                            {
                            #if (!ENABLE_4K2K)
                                // 4K2K is used GOP now, no need to setup MVOP, scaler.
                                MApp_Photo_InitFullScreenDisplay();
                            #endif
                            }
                        }
                    #endif
                        if(MApp_Photo_GetInfo(E_PHOTO_INFO_FILE_FORMAT) == E_PHOTO_FILE_GIF)
                        {
                            MApp_Photo_GIFDisplay(FALSE);
                        }
                    #if (ENABLE_MPO_3D_PROCESS && (!ENABLE_4K2K))
                        // This MPO in 3D mode
                        else if(MApp_Photo_GetInfo(E_PHOTO_INFO_IS_MPO_DISPARITY_TYPE) == TRUE)
                        {
                          #if ENABLE_NEW_3D_FLOW
                            MApp_Scaler_SetVideo3DMode(EN_3D_FRAME_PACKING);
                          #else
                            MApp_Scaler_SetVideo3DMode(MAPP_Scaler_Map3DFormatTo3DUserMode(E_XC_3D_INPUT_FRAME_PACKING));
                          #endif
                            MApp_Photo_MPODisplay(FALSE);
                        }
                    #endif
                        else
                        {
                        #if ENABLE_4K2K
                            //for 4K2K photo, use GOP to display.
                            MApp_Photo_4K2K_DisplayByGOP(FALSE);
                        #else
                            MApp_Photo_Display(FALSE);
                        #endif
                        }

                        m_photoInfo.u16Width    = MApp_Photo_GetInfo(E_PHOTO_INFO_IMAGE_WIDTH);
                        m_photoInfo.u16Height   = MApp_Photo_GetInfo(E_PHOTO_INFO_IMAGE_HEIGHT);
                        m_photoInfo.u32FileSize = MApp_Photo_GetInfo(E_PHOTO_INFO_FILE_SIZE);

                        //Update Exif information
                        m_photoInfo.u32ExifWidth    = MApp_Photo_GetInfo(E_PHOTO_INFO_EXIF_WIDTH);
                        m_photoInfo.u32ExifHeight   = MApp_Photo_GetInfo(E_PHOTO_INFO_EXIF_HEIGHT);
                        MApp_Photo_GetExifInfo(E_PHOTO_EXIF_INFO_CAMERA_MAKER,  &m_photoInfo.au8CameraMaker, sizeof(m_photoInfo.au8CameraMaker));
                        MApp_Photo_GetExifInfo(E_PHOTO_EXIF_INFO_CAMERA_MODEL,  &m_photoInfo.au8CameraModel, sizeof(m_photoInfo.au8CameraModel));
                        MApp_Photo_GetExifInfo(E_PHOTO_EXIF_INFO_FLASH_MODE,    &m_photoInfo.u32FlashMode,   sizeof(m_photoInfo.u32FlashMode));
                        MApp_Photo_GetExifInfo(E_PHOTO_EXIF_INFO_ISO_SPEED,     &m_photoInfo.u32ISOSpeed,    sizeof(m_photoInfo.u32ISOSpeed));
                        MApp_Photo_GetExifInfo(E_PHOTO_EXIF_INFO_EXPOSURE_BIAS, &m_photoInfo.stExposureBias, sizeof(m_photoInfo.stExposureBias));
                        MApp_Photo_GetExifInfo(E_PHOTO_EXIF_INFO_EXPOSURE_TIME, &m_photoInfo.stExposureTime, sizeof(m_photoInfo.stExposureTime));
                        MApp_Photo_GetExifInfo(E_PHOTO_EXIF_INFO_F_STOP,        &m_photoInfo.stF_Stop,       sizeof(m_photoInfo.stF_Stop));

                        eOrientation = (EN_PHOTO_ORIENTATION)MApp_Photo_GetInfo(E_PHOTO_INFO_ORIENTATION);
                        if(eOrientation < E_PHOTO_ORIENT_NOT_FOUND)
                        {
                            m_photoInfo.eOrientation = (enumMPlayerJPGOrient)eOrientation;
                        }
                        else
                        {
                            m_photoInfo.eOrientation = E_MPLAYER_JPEG_ORIENT_ORIGINAL;
                        }

                        m_photoInfo.bHasDateTime = MApp_Photo_GetInfo(E_PHOTO_INFO_HAS_DATE_TIME);
                        if (m_photoInfo.bHasDateTime)
                        {
                            m_photoInfo.u32Year     = MApp_Photo_GetInfo(E_PHOTO_INFO_DATE_TIME_YEAR);
                            m_photoInfo.u32Month    = MApp_Photo_GetInfo(E_PHOTO_INFO_DATE_TIME_MONTH);
                            m_photoInfo.u32Day      = MApp_Photo_GetInfo(E_PHOTO_INFO_DATE_TIME_DAY);
                            m_photoInfo.u32Hour     = MApp_Photo_GetInfo(E_PHOTO_INFO_DATE_TIME_HOUR);
                            m_photoInfo.u32Minute   = MApp_Photo_GetInfo(E_PHOTO_INFO_DATE_TIME_MINUTE);
                            m_photoInfo.u32Second   = MApp_Photo_GetInfo(E_PHOTO_INFO_DATE_TIME_SECOND);
                        }
                        m_u32PhotoCurrentDisplayedIdx = m_MPlayerInfo[0].u16PlayingIdx;
                        //printf("Display photo %u\n", m_u32PhotoCurrentDisplayedIdx);

                        // E_MPLAYER_NOTIFY_PHOTO_INFO_OK is put here for reason
                        NOTIFY(E_MPLAYER_NOTIFY_PHOTO_INFO_OK, (void*)NULL);

                        // record the start time of showing jpeg
                        m_u32PhotoSlideShowTimer = msAPI_Timer_GetTime0();

                        if(MApp_Photo_GetInfo(E_PHOTO_INFO_FILE_FORMAT) == E_PHOTO_FILE_GIF)
                        {
                            //gif need play all frame done before play next file.
                            if(MApp_Photo_GIFIsDisplayDone())
                            {
                                MApp_Photo_GIFResetDisplay();
                                NOTIFY(E_MPLAYER_NOTIFY_END_OF_PLAY_ONE_FILE, NULL);
                                m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= E_MPLAYER_PHOTO_STATE_DISPLAY;
                                bCanPlayNext = TRUE;
                            }
                        }
                        else
                        {
                            NOTIFY(E_MPLAYER_NOTIFY_END_OF_PLAY_ONE_FILE, NULL);
                            m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= E_MPLAYER_PHOTO_STATE_DISPLAY;
                            if(m_u8DecodedPics <= 1)
                            {
                                bCanPlayNext = TRUE;
                            }
                        }

                        if(bCanPlayNext)
                        {
                        #if PHOTO_SLIDE_SHOW_EFFECT
                            //let it can be played with slide show effect when there is only one file is playing
                            if(_MApp_MPlayer_PlayNext(eMPlayerIdx)==FALSE)
                            {
                                //last photo
                                m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= E_MPLAYER_PHOTO_STATE_PLAY_END;
                            }
                        #else
                            // If there is only 1 photo to be played, let it stay in PAUSE state to avoid blinking.
                            //bContinue = _MApp_MPlayer_PlayNext(eMPlayerIdx);
                            if((m_MPlayerInfo[eMPlayerIdx].eMediaType == E_MPLAYER_TYPE_PHOTO)
                            && (m_MPlayerInfo[eMPlayerIdx].eRepeatMode == E_MPLAYER_REPEAT_ALL ||
                                m_MPlayerInfo[eMPlayerIdx].eRepeatMode == E_MPLAYER_REPEAT_NONE)
                            && (m_MPlayerInfo[eMPlayerIdx].u16TotalFileNum-m_MPlayerInfo[eMPlayerIdx].u16TotalDirNum > 1 ||
                                m_u16SelectedFileNum[m_MPlayerInfo[eMPlayerIdx].eMediaType] > 1))
                            {
                                if(_MApp_MPlayer_PlayNext(eMPlayerIdx)==FALSE)
                                {
                                    //last photo
                                    m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= E_MPLAYER_PHOTO_STATE_PLAY_END;
                                }
                            }
                            else
                            {
                                m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= E_MPLAYER_PHOTO_STATE_PAUSE;
                            }
                        #endif
                        }
                    }

                    if(m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus & E_MPLAYER_PHOTO_STATE_DISPLAY)
                    {
                        if (msAPI_Timer_DiffTimeFromNow(m_u32PhotoSlideShowTimer) >
                            m_u32PhotoSlideShowDelayTimeS)
                        {
                            m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus &= (enumMediaPlayingStatus)~E_MPLAYER_PHOTO_STATE_DISPLAY;
                            if(m_u8DecodedPics == 2)
                            {
                               m_ePhotoType[0] = m_ePhotoType[1];
                            }
                            m_ePhotoType[1] = E_MPLAYER_SUBTYPE_INVALID;
                            m_u8DecodedPics--;
                            //printf("Clear display flag\n");
                            //printf("m_u8DecodedPics=%u\n", m_u8DecodedPics);
                        }
                    }
                }

                if(!(m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus & E_MPLAYER_PHOTO_STATE_DECODE_PAUSE) ||
                    (m_u8DecodedPics < 1))
                {
                    if((m_u8DecodedPics<=1) &&
                      !(m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus & E_MPLAYER_PHOTO_STATE_PLAY_END))
                    {
                        switch(_MApp_MPlayer_PhotoDecode())
                        {
                        case EXIT_PHOTO_DECODE_ONE_FRAME_DONE:
                            if(MApp_Photo_GetInfo(E_PHOTO_INFO_IS_MPO_DISPARITY_TYPE) == TRUE)
                            {
                            #if (ENABLE_MPO_3D_PROCESS && (!ENABLE_4K2K))
                                MApp_Photo_MPODisplay(FALSE);
                                break;
                            #else
                                //for unsupported 3D case, mpo only decode first frame.
                                MApp_Photo_Stop();
                                // Important !! Must Read
                                // fall through to EXIT_PHOTO_DECODE_DONE
                            #endif
                            }
                            else
                            {
                                //This is GIF case only
                                break;
                            }
                        case EXIT_PHOTO_DECODE_DONE:
                            //printf("case EXIT_PHOTO_DECODE_DONE\n");
                            m_ePhotoType[m_u8DecodedPics] = m_MPlayerInfo[eMPlayerIdx].eMediaSubType;
//                            m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_INVALID;
                            m_u8DecodedPics++;
                            m_MPlayerInfo[eMPlayerIdx].eMediaPlayingDirection = E_MPLAYER_PLAY_DIRECTION_NEXT;
                            m_u32Photo_PlayPrevDecodeFailCount = 0;
                            m_s32Photo_LastDecodeFailIdx = -1;
                        #if RANDOM_PLAY
                            m_bPlayNext = FALSE;
                        #endif
                            //printf("m_u8DecodedPics=%u, LastDecodeFailCount=0\n", m_u8DecodedPics);
                            break;
                        case EXIT_PHOTO_DECODE_FAIL:
                            //printf("case EXIT_PHOTO_DECODE_FAIL\n");
                            //printf("m_u8DecodedPics=%u\n", m_u8DecodedPics);
                            m_ePhotoValidOrNot = E_MPLAYER_PHOTO_INVALID;
                            break;

                        default:
                            break;
                        }
                    }
                }

                if(m_ePhotoValidOrNot == E_MPLAYER_PHOTO_INVALID)
                {
                    BOOLEAN bWaiting = TRUE;

                    if(m_MPlayerInfo[eMPlayerIdx].u32ErrorDelayTime== 0)
                    {
                        //m_u32PhotoErrorDelayTimeS = 0 , means UI will not show ERROR OSD ,
                        //so mplayer can continously to decode next photo and send Notify(Error) immediatly
                        bWaiting = FALSE;
                    }
                    else if(!(m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus & E_MPLAYER_PHOTO_STATE_DISPLAY)
                         && !(m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus & E_MPLAYER_PHOTO_STATE_ERROR_PENDING))
                    {
                        //Because we do pre-decode , so if init fail or decode fail ,
                        //it means E_MPLAYER_PHOTO_INVALID , we can not send Notify to UI before "Current slide show display done " or "Error message display time out"
                        bWaiting = FALSE;
                        m_u32PhotoCurrentDisplayedIdx = m_MPlayerInfo[0].u16PlayingIdx;
                    #if (!ENABLE_4K2K)
                        // 4K2K is used GOP now, no need to setup MVOP, scaler.
                        MApp_Photo_InitFullScreenDisplay();//clean prev photo
                    #endif
                    }

                    if(bWaiting == FALSE)
                    {
                        m_ePhotoValidOrNot = E_MPLAYER_PHOTO_WAIT;
                        m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= (enumMediaPlayingStatus)E_MPLAYER_PHOTO_STATE_ERROR_PENDING;
                        m_MPlayerInfo[eMPlayerIdx].u32ErrorMsgTimer = msAPI_Timer_GetTime0();
                        NOTIFY(E_MPLAYER_NOTIFY_ERROR_OF_PLAY_FILE, &m_MPlayerInfo[eMPlayerIdx].eMediaType);

                        if(_MApp_MPlayer_GetNotifyRtn()==FALSE)
                        {
                            //all photo fail.
                            m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= E_MPLAYER_PHOTO_STATE_PLAY_END;
                        }
                        else
                        {
                            if( m_MPlayerInfo[eMPlayerIdx].eMediaPlayingDirection == E_MPLAYER_PLAY_DIRECTION_PREV // Last command is play previous
                            &&  m_MPlayerInfo[eMPlayerIdx].u32ErrorDelayTime== 0)
                            {
                                m_u32Photo_PlayPrevDecodeFailCount ++;
                                m_s32Photo_LastDecodeFailIdx = m_s32Photo_LastDecodeIdx;
                                //printf("LastDecodeFailCount=%lu, LastDecodeFailIdx=%ld\n", m_u32Photo_PlayPrevDecodeFailCount, m_s32Photo_LastDecodeFailIdx);
                                if(!_MApp_MPlayer_PlayPrev(eMPlayerIdx))
                                {
                                    //last photo
                                    m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= E_MPLAYER_PHOTO_STATE_PLAY_END;
                                }
                            }
                            else
                            {
                                if(!_MApp_MPlayer_PlayNext(eMPlayerIdx))
                                {
                                    //last photo
                                    m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= E_MPLAYER_PHOTO_STATE_PLAY_END;
                                }
                            }
                        }
                    }
                }

                if(m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus & E_MPLAYER_PHOTO_STATE_ERROR_PENDING)
                {
                    if(msAPI_Timer_DiffTimeFromNow(m_MPlayerInfo[eMPlayerIdx].u32ErrorMsgTimer) >= m_MPlayerInfo[eMPlayerIdx].u32ErrorDelayTime)
                    {
                        m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus &= (enumMediaPlayingStatus)~E_MPLAYER_PHOTO_STATE_ERROR_PENDING;
                    }
                }

                if( (m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus & E_MPLAYER_PHOTO_STATE_PLAY_END)
                && !(m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus & E_MPLAYER_PHOTO_STATE_DISPLAY)
                && !(m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus & E_MPLAYER_PHOTO_STATE_ERROR_PENDING))
                {
                    bContinue = FALSE;
                }

                if(bContinue == FALSE)
                {
                    m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_PHOTO_PLAY;
                    NOTIFY(E_MPLAYER_NOTIFY_END_OF_PLAY_ALL_FILE, &m_MPlayerInfo[eMPlayerIdx].eMediaType);
                }
            }
        #endif  // #if ENABLE_MPLAYER_PHOTO

        #if ENABLE_MPLAYER_MOVIE
            bContinue = TRUE;
            if((m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 & E_MPLAYER_KNL_FLG1_MOVIE_PLAY) && !(m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_DECODE_N_THUMBNAIL))
            {
                static BOOLEAN bInitOk = FALSE;
                m_MPlayerInfo[eMPlayerIdx].u32ErrorDelayTime = m_u32MovieErrorDelayTimeS;

                if(m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 & E_MPLAYER_KNL_FLG1_FILE_INIT)
                {
                    m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &=
                        (enumMPlayerKnlFlags1)~(E_MPLAYER_KNL_FLG1_SUBTITLE_VALID |
                                                E_MPLAYER_KNL_FLG1_SUBTITLE_ENABLE |
                                                E_MPLAYER_KNL_FLG1_SUBTITLE_SHOWN |
                                                E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL);
                    m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_INTERNAL_SUBTITLE_INIT_DONE;

                #if (ENABLE_3D_PROCESS)
                    if(DB_3D_SETTING.en3DType != EN_3D_BYPASS || DB_3D_SETTING.en3DTo2DType != EN_3D_TO_2D_OFF )
                    {
                        msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
                        //DB_3D_SETTING.en3DType = EN_3D_BYPASS;
                        //DB_3D_SETTING.en3DTo2DType = EN_3D_TO_2D_OFF;
                    #if (ENABLE_MFC_6M20 || ENABLE_MFC_6M30)
                        MApp_ZUI_Set_UI_3D_Mode(E_UI_3D_OUTPUT_MODE_NONE);
                        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_ALL);
                        MDrv_Ursa_6M30_3D_MODE (PANEL_3D_MODE_NONE);
                    #else
                        if(DB_3D_SETTING.en3DType != EN_3D_BYPASS)
                        {
                            DB_3D_SETTING.en3DType = EN_3D_BYPASS;
                          #if ENABLE_NEW_3D_FLOW
                            MApp_Scaler_SetVideo3DMode(EN_3D_BYPASS);
                          #else
                            MApp_Scaler_SetVideo3DMode(MAPP_Scaler_Map3DFormatTo3DUserMode(E_XC_3D_INPUT_MODE_NONE));
                          #endif
                        }

                        if (DB_3D_SETTING.en3DTo2DType != EN_3D_TO_2D_OFF)
                        {
                            DB_3D_SETTING.en3DTo2DType = EN_3D_TO_2D_OFF;
                            MApi_Scaler_Set3DInfo(E_XC_3D_INPUT_MODE_NONE, E_XC_3D_OUTPUT_FRAME_L);
                          #if ENABLE_NEW_3D_FLOW
                            MApp_Scaler_SetVideo3DMode(EN_3D_BYPASS);
                          #else
                            MApp_Scaler_SetVideo3DMode(E_USER_3D_MODE_OFF);
                          #endif
                        }
                        // MApp_Scaler_SetVideo3DMode(MAPP_Scaler_Map3DFormatTo3DUserMode(E_XC_3D_INPUT_MODE_NONE));
                    #endif
                        msAPI_Scaler_SetBlueScreen(DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
                    }
                #endif
                #if (ENABLE_SUBTITLE_DMP)
                    SUBTITLE_DBG(printf("-- Subtitle init\n"));
                    _MApp_MPlayer_InitSubtitleTask();
                    m_u8AliveSubtitleNum = 0; //clear for text subtitle
                    m_s32SubtitleTimeShift = 0; //clear subtitle shift time
                    MApp_MPlayer_ResetAliveTextSubtitleStatus();
                    if(_MApp_MPlayer_MP4_Subtitle_Parser())
                    {
                        MApp_MPlayer_SetSubtitleTrackID(0); //occupied one file handle for external subtitle if found

                        m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= (E_MPLAYER_KNL_FLG1_SUBTITLE_VALID |
                                                                 E_MPLAYER_KNL_FLG1_SUBTITLE_ENABLE |
                                                                 E_MPLAYER_KNL_FLG1_SUBTITLE_TEXT |
                                                                 E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL);
                        m_eExternalSubtitleType = (enumMPlayerSubtitleType)MApp_MPlayer_GetInfo(E_MPLAYER_EXT_SUBTITLE_INFO_SUBTITLE_TYPE);
#if (ENABLE_SUBTITLE_SUBIDX)
                        if(m_u8ExternalSubtitleFileHandle != FCTRL_INVALID_FILE_HANDLE)
                        {
                            msAPI_MpegSP_Init();
                            msAPI_MpegSP_Show();
                            m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 &=(enumMPlayerKnlFlags1)~(E_MPLAYER_KNL_FLG1_SUBTITLE_TEXT);
                        }
#endif //#if (ENABLE_SUBTITLE_SUBIDX)
                    }
                #endif //#if (ENABLE_SUBTITLE_DMP)

                    m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_FILE_INIT;

                    eType=VIDEO_PLAYER_PLAYING_TYPE_INVALID;
                #if ENABLE_DVD
                    if(m_MPlayerInfo[eMPlayerIdx].eMediaSubType == E_MPLAYER_SUBTYPE_DVD)
                    {
                        eType = VIDEO_PLAYER_PLAYING_TYPE_DVD;
                    }
                #endif

                    MApp_VDPlayer_EnableVideoOutputFlag(ENABLE);

#if ENABLE_LAST_MEMORY==1
                        m_u8LastMemoryCheck=TRUE;
#if ENABLE_LAST_MEMORY_PLAYTIME_UPDATE==1
                        m_u32LastMemoryCheckTime = msAPI_Timer_GetTime0();
#endif
                        m_u8LastMemorySearchHit = MApp_MPlayer_LastMemory_Search(&m_MPlayerInfo[eMPlayerIdx].curPlayingFileEntry);
#if ENABLE_DRM

                        if(m_u8LastMemorySearchHit == FALSE)
                            {
                                #if ENABLE_DIVX_PLUS
                                g_u8TitleId = 0;
                                #endif
                                g_bIsResumePlay = FALSE;
                            }
#endif
#endif//#if ENABLE_LAST_MEMORY==1

                #if ENABLE_DVD
                    if(eType == VIDEO_PLAYER_PLAYING_TYPE_DVD)
                    {
                        if(MApp_VDPlayer_DVD_Init(VIDEO_PLAYER_INPUT_SOURCE_MM, eType, &m_MPlayerInfo[eMPlayerIdx].curPlayingFileEntry) == TRUE)
                        {
                            bInitOk = TRUE;
                            NOTIFY(E_MPLAYER_NOTIFY_BEFORE_PLAY_ONE_FILE, &m_MPlayerInfo[eMPlayerIdx].eMediaType);
                            m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_PREDECODE_OK;
                        #if RANDOM_PLAY
                            m_bPlayNext = FALSE;
                        #endif
                        }
                        else
                        {
                            // ERROR Handling :
                            // MUST not set media sub-type to E_MPLAYER_SUBTYPE_INVALID, or it will be blocked
                            //   in MApp_MPlayer_PlayNextFile().
                            //m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_INVALID;
                            bInitOk = FALSE;
                            m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= (enumMediaPlayingStatus)E_MPLAYER_MOVIE_STATE_ERROR_PENDING;
                            m_MPlayerInfo[eMPlayerIdx].u32ErrorMsgTimer= msAPI_Timer_GetTime0();
                            m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_INVALID;
                            NOTIFY(E_MPLAYER_NOTIFY_ERROR_OF_PLAY_FILE, &m_MPlayerInfo[eMPlayerIdx].eMediaType);
                            if(_MApp_MPlayer_GetNotifyRtn() == FALSE) // Need to refine
                            {
                                m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= (enumMediaPlayingStatus)E_MPLAYER_MOVIE_STATE_ALL_ERROR;
                            }
                        #if (ENABLE_SUBTITLE_DMP)
                            if(m_u8ExternalSubtitleFileHandle != FCTRL_INVALID_FILE_HANDLE)
                            {
                                msAPI_FCtrl_FileClose(m_u8ExternalSubtitleFileHandle);
                                m_u8ExternalSubtitleFileHandle = FCTRL_INVALID_FILE_HANDLE;
                                #if (ENABLE_INTERNAL_BMP_SUBTITLE || ENABLE_EXTERNAL_BMP_SUBTITLE)
                                msAPI_MpegSP_Dinit();
                                #endif
                            }
                        #endif
                            return; //prevent to skip twice at same time when meets error file.
                        }
                    }
                    else
                #endif  // ENABLE_DVD

                    if(MApp_VDPlayer_Init(VIDEO_PLAYER_INPUT_SOURCE_MM, eType, &m_MPlayerInfo[eMPlayerIdx].curPlayingFileEntry) == TRUE)
                    {
#if (ENABLE_SUBTITLE_SUBIDX)
                        //set off in _MApp_VDPlayer_VarInit() by default and check if on for SUBIDX after play init OK.
                        if(m_eExternalSubtitleType==E_MPLAYER_SUBTITLE_SUBIDX)
                        {
                            MApp_VDPlayer_SetSuspendInternalSubtitle2Queue(TRUE);
                        }
#endif //(ENABLE_SUBTITLE_SUBIDX)
#if ENABLE_DRM
#if ENABLE_LAST_MEMORY==1

                        if(m_u8LastMemorySearchHit == 1 && g_bIsResumePlay)
                        {
                            goto SKIP_DRM_CHECK;
                        }
#endif
                        MPLAYER_DBG(printf("\n vdplayer init ok and NOTIFY DRM"));

                        if(MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_DRM_FILE_FORMAT))
                        {
                            MPLAYER_DBG(printf("\n DRM file..."));
                            BOOLEAN  bNotifyDRMUI = TRUE;
                            m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_FILE_WAIT_DRM_UI;

                            if(MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_DRM_AUTHORIZATION_STATUS))
                            {
                                BOOLEAN bIsRental;
                                U8 u8UseLimit;
                                U8 u8UseCount;

                                if(!MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_DRM_RENTAL_EXPIRE_STATUS))
                                {
                                    MApp_MPlayer_CheckDRMActivation();
                                    MApp_VDPlayer_QueryDRMRentalStatus(&bIsRental, &u8UseLimit, &u8UseCount);
                                    printf("bIsRental=%d =%d %d \n",bIsRental,u8UseLimit,u8UseCount);

                                    if(!bIsRental)
                                    {
                                        m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= (enumMPlayerKnlFlags1)E_MPLAYER_KNL_FLG1_MOVIE_INIT_OK;
                                        m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_FILE_WAIT_DRM_UI;
                                        bNotifyDRMUI = FALSE;
                                    }

                                    if(bIsRental)
                                    {
                                        MApp_VDPlayer_SaveVISUALDRMMemory();
                                        g_bIsResumePlay = TRUE;
                                    }
                                }
                            }

                            if(bNotifyDRMUI)
                            {
                                NOTIFY(E_MPLAYER_NOTIFY_DRM_INIT , NULL);
                            }
                        }
                        else
                        {
                            MPLAYER_DBG(printf("\n not DRM file..."));
                            m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_MOVIE_INIT_OK;
                        }
                    }
                    else
                    {
                        U16 u16Error;
                        // ERROR Handling :
                        // MUST not set media sub-type to E_MPLAYER_SUBTYPE_INVALID, or it will be blocked
                        MPLAYER_DBG(printf("\n vdplayer init fail \n"));

                        m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_INVALID;

                        u16Error = (U16) MApp_VDPlayer_GetDRMErrCode();//MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_ERROR_INFO);
                        MPLAYER_DBG(printf(">>>   u16Error=%x\n ",u16Error));

                        if(u16Error==EN_VDP_ERRORCODE_DRM_ERR_NOT_REGISTERED)
                        {
                            m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_FILE_WAIT_DRM_UI;
                            NOTIFY(E_MPLAYER_NOTIFY_DRM_INIT , NULL);
                        }
                        else if(u16Error==EN_VDP_ERRORCODE_DRM_ERR_NOT_AUTHORIZED)
                        {
                            m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_FILE_WAIT_DRM_UI;
                            NOTIFY(E_MPLAYER_NOTIFY_DRM_INIT , NULL);
                        }
                        else if(u16Error==EN_VDP_ERRORCODE_DRM_ERR_RENTAL_EXPIRED)
                        {
                            m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_FILE_WAIT_DRM_UI;
                            NOTIFY(E_MPLAYER_NOTIFY_DRM_INIT , NULL);
                        }
                        else if(u16Error==EN_VDP_ERRORCODE_DRM_ERR_VERSION_EXPIRED)
                        {
                            m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_FILE_WAIT_DRM_UI;
                            NOTIFY(E_MPLAYER_NOTIFY_DRM_INIT , NULL);
                        }
                        else
                        {
                            //for user-stop case, not error case
                            if(MApp_VDPlayer_CheckFailStatus()==E_VDPLAYER_FAIL_STATUS_USER_EXIT)
                            {
                                m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &=(enumMPlayerKnlFlags1)~ E_MPLAYER_KNL_FLG1_MOVIE_PLAY;
                            }
                            else
                            {
                                bInitOk = FALSE;
                                m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_MOVIE_INIT_OK;
                                m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_FILE_WAIT_DRM_UI;
                                m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= (enumMediaPlayingStatus)E_MPLAYER_MOVIE_STATE_ERROR_PENDING;
                                m_MPlayerInfo[eMPlayerIdx].u32ErrorMsgTimer= msAPI_Timer_GetTime0();
                                NOTIFY(E_MPLAYER_NOTIFY_ERROR_OF_PLAY_FILE, &m_MPlayerInfo[eMPlayerIdx].eMediaType);
                                if(_MApp_MPlayer_GetNotifyRtn() == FALSE) // Need to refine
                                {
                                    m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= (enumMediaPlayingStatus)E_MPLAYER_MOVIE_STATE_ALL_ERROR;
                                }

                            #if (ENABLE_SUBTITLE_DMP)
                                if(m_u8ExternalSubtitleFileHandle != FCTRL_INVALID_FILE_HANDLE)
                                {
                                    msAPI_FCtrl_FileClose(m_u8ExternalSubtitleFileHandle);
                                    m_u8ExternalSubtitleFileHandle = FCTRL_INVALID_FILE_HANDLE;
                                    #if (ENABLE_INTERNAL_BMP_SUBTITLE || ENABLE_EXTERNAL_BMP_SUBTITLE)
                                    msAPI_MpegSP_Dinit();
                                    #endif
                                }
                            #endif
                            }
                            return; //prevent to skip twice at same time when meets error file.
                        }
                    } // if(MApp_VDPlayer_Init)
                } // if(m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 & E_MPLAYER_KNL_FLG1_FILE_INIT)

                if(m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 & E_MPLAYER_KNL_FLG1_FILE_WAIT_DRM_UI)
                {
                    // printf("\n E_MPLAYER_KNL_FLG1_FILE_WAIT_DRM_UI");
                    // wait UI here
                    // if want to play, set E_MPLAYER_KNL_FLG1_MOVIE_INIT_OK
                    MApp_VDPlayer_MailBoxHandler();
                    return;
                }

                if(m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 & E_MPLAYER_KNL_FLG1_MOVIE_INIT_OK) //(DRM and init ok)
                {
                    m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_MOVIE_INIT_OK;
#if ENABLE_LAST_MEMORY==1
SKIP_DRM_CHECK:
#endif
#endif //#if ENABLE_DRM
#if ENABLE_WMDRMPD
                        if (MApp_VDPlayer_WMDRMPD_IsProtected())
                        {
                            if (!MApp_VDPlayer_WMDRMPD_GetLicense())
                            {
                                 bInitOk = FALSE;
                                 m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= (enumMediaPlayingStatus)E_MPLAYER_MOVIE_STATE_ERROR_PENDING;
                                 m_MPlayerInfo[eMPlayerIdx].u32ErrorMsgTimer= msAPI_Timer_GetTime0();
                                 m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_INVALID;
                                 NOTIFY(E_MPLAYER_NOTIFY_ERROR_OF_PLAY_FILE, &m_MPlayerInfo[eMPlayerIdx].eMediaType);
                                 if(_MApp_MPlayer_GetNotifyRtn() == FALSE) // Need to refine
                                 {
                                     m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= (enumMediaPlayingStatus)E_MPLAYER_MOVIE_STATE_ALL_ERROR;
                                 }

                            #if (ENABLE_SUBTITLE_DMP)
                                if(m_u8ExternalSubtitleFileHandle != FCTRL_INVALID_FILE_HANDLE)
                                {
                                    msAPI_FCtrl_FileClose(m_u8ExternalSubtitleFileHandle);
                                    m_u8ExternalSubtitleFileHandle = FCTRL_INVALID_FILE_HANDLE;
                                    #if (ENABLE_INTERNAL_BMP_SUBTITLE || ENABLE_EXTERNAL_BMP_SUBTITLE)
                                    msAPI_MpegSP_Dinit();
                                    #endif
                                }
                            #endif
                                 return;
                            }
                        }
#endif
                        m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType = E_MPLAYER_SUBTYPE_MOVIE;

                        bInitOk = TRUE;
                        if((MApp_VDPlayer_Play()==FALSE) && (MApp_VDPlayer_CheckFailStatus()==E_VDPLAYER_FAIL_STATUS_USER_EXIT)) //UI NOTIFY should be issued after PLAY. The 1st cmd to codec should be PLAY after INIT
                        {
                            m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &=(enumMPlayerKnlFlags1)~ E_MPLAYER_KNL_FLG1_MOVIE_PLAY;
                            return;
                        }

                        //MApp_VDPlayer_Play();
#if (ENABLE_INTERNAL_BMP_SUBTITLE || ENABLE_EXTERNAL_BMP_SUBTITLE)
                        msAPI_MpegSP_SetVideoDimension(
                            (U16)MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_H_SIZE),
                            (U16)MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_V_SIZE));
#endif
                        NOTIFY(E_MPLAYER_NOTIFY_MEDIA_PREDECODE_OK, NULL);
                        m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_PREDECODE_OK;

                        NOTIFY(E_MPLAYER_NOTIFY_BEFORE_PLAY_ONE_FILE, &m_MPlayerInfo[eMPlayerIdx].eMediaType);
                    #if RANDOM_PLAY
                        m_bPlayNext = FALSE;
                    #endif
#if ENABLE_LAST_MEMORY==1
                        if (m_u8LastMemorySearchHit==1)
                        {
                            MPLAYER_DBG(printf("NOTIFY_LAST_MEMORY_RESUME_PLAY\n"));
                            #if ENABLE_DIVX_PLUS
                            if(g_bChangeFile == FALSE)
                            #endif
                            {
                                NOTIFY(E_MPLAYER_NOTIFY_LAST_MEMORY_RESUME_PLAY, NULL);
                            }
                        }

#endif//#if ENABLE_LAST_MEMORY==1

#if ENABLE_DRM==0
#if 0
                    {   //no need, just for Source Insight.
#endif
                    }
                    else
                    {
                        // ERROR Handling :
                        // MUST not set media sub-type to E_MPLAYER_SUBTYPE_INVALID, or it will be blocked
                        //   in MApp_MPlayer_PlayNextFile().
                        //m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_INVALID;
                        bInitOk = FALSE;
                        m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= (enumMediaPlayingStatus)E_MPLAYER_MOVIE_STATE_ERROR_PENDING;
                        m_MPlayerInfo[eMPlayerIdx].u32ErrorMsgTimer= msAPI_Timer_GetTime0();
                        m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_INVALID;
                        NOTIFY(E_MPLAYER_NOTIFY_ERROR_OF_PLAY_FILE, &m_MPlayerInfo[eMPlayerIdx].eMediaType);
                        if(_MApp_MPlayer_GetNotifyRtn() == FALSE) // Need to refine
                        {
                            m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= (enumMediaPlayingStatus)E_MPLAYER_MOVIE_STATE_ALL_ERROR;
                        }

                    #if (ENABLE_SUBTITLE_DMP)
                        if(m_u8ExternalSubtitleFileHandle != FCTRL_INVALID_FILE_HANDLE)
                        {
                            msAPI_FCtrl_FileClose(m_u8ExternalSubtitleFileHandle);
                            m_u8ExternalSubtitleFileHandle = FCTRL_INVALID_FILE_HANDLE;
                            #if (ENABLE_INTERNAL_BMP_SUBTITLE || ENABLE_EXTERNAL_BMP_SUBTITLE)
                            msAPI_MpegSP_Dinit();
                            #endif
                        }
                    #endif
                        return; //prevent to skip twice at same time when meets error file.
                    }
#endif
                } //if(m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 & E_MPLAYER_KNL_FLG1_FILE_INIT)
                bContinue = TRUE;
                if(_MApp_MPlayer_IsSupportedMovie(m_MPlayerInfo[eMPlayerIdx].eMediaSubType))
                {
                    if(m_eMovieMainExit != EXIT_VDPLAYER_WAIT &&
                       m_eMovieMainExit != EXIT_VDPLAYER_EXIT)
                    {
                    #if ENABLE_DVD
                        if(m_MPlayerInfo[eMPlayerIdx].eMediaSubType == E_MPLAYER_SUBTYPE_DVD)
                            m_eMovieMainExit = MApp_VDPlayer_DVD_Main();
                        else
                    #endif
                        m_eMovieMainExit = MApp_VDPlayer_Main();
                    }
                    switch(m_eMovieMainExit)
                    {
                    case EXIT_VDPLAYER_WAIT:
                    case EXIT_VDPLAYER_EXIT:
                      #if (ENABLE_SUBTITLE_DMP)
                        if(m_u8ExternalSubtitleFileHandle != FCTRL_INVALID_FILE_HANDLE)
                        {
                            msAPI_FCtrl_FileClose(m_u8ExternalSubtitleFileHandle);
                            m_u8ExternalSubtitleFileHandle = FCTRL_INVALID_FILE_HANDLE;
                            #if (ENABLE_INTERNAL_BMP_SUBTITLE || ENABLE_EXTERNAL_BMP_SUBTITLE)
                            msAPI_MpegSP_Dinit();
                            #endif
                        }
                      #endif
                      #if (SUPPERTED_ADVERTISEMENT_MODE)
                        g_u32TraceTimer0 = msAPI_Timer_GetTime0();
                      #else
                        NOTIFY(E_MPLAYER_NOTIFY_END_OF_PLAY_ONE_FILE, NULL);
                      #endif
                        if(m_eMovieMainExit == EXIT_VDPLAYER_EXIT)
                        {
                            m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= (enumMediaPlayingStatus)E_MPLAYER_MOVIE_STATE_ERROR_PENDING;
                            m_MPlayerInfo[eMPlayerIdx].u32ErrorMsgTimer= msAPI_Timer_GetTime0();
                            m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_INVALID;
                            NOTIFY(E_MPLAYER_NOTIFY_ERROR_OF_PLAY_FILE, &m_MPlayerInfo[eMPlayerIdx].eMediaType);
                            if(_MApp_MPlayer_GetNotifyRtn() == FALSE) // Need to refine
                            {
                                m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= (enumMediaPlayingStatus)E_MPLAYER_MOVIE_STATE_ALL_ERROR;
                            }
                        }
                        else if(m_eMovieMainExit == EXIT_VDPLAYER_WAIT)
                        {
                            // If fast backward to start of file, still start playing current file.
                            if(MApp_MPlayer_QueryCurrentMediaType() == E_MPLAYER_TYPE_MOVIE)
                            {
                                if(MApp_MPlayer_QueryMoviePlayMode() >= E_MPLAYER_MOVIE_FB_2X &&
                                    MApp_MPlayer_QueryMoviePlayMode() <= E_MPLAYER_MOVIE_FB_32X)
                                {
                                    if(!_MApp_MPlayer_PlayAgain(eMPlayerIdx))
                                    {
                                        m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= (enumMediaPlayingStatus)E_MPLAYER_MOVIE_STATE_PLAY_END;
                                    }
                                }
                                else
                                {
                                    if(!_MApp_MPlayer_PlayNext(eMPlayerIdx))
                                    {
                                        m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= (enumMediaPlayingStatus)E_MPLAYER_MOVIE_STATE_PLAY_END;
                                    }
                                }
                            }
                            else
                            {
                                if(!_MApp_MPlayer_PlayNext(eMPlayerIdx))
                                {
                                    m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= (enumMediaPlayingStatus)E_MPLAYER_MOVIE_STATE_PLAY_END;
                                }
                            }
                        }
                        break;
#if ENABLE_DRM
                    case EXIT_VDPLAYER_DECODING:
                        // If fast backward to start of file, still start playing current file.
                        {
                            // If fast backward to start of file, still start playing current file.
                            if(MApp_MPlayer_QueryMoviePlayMode() >= E_MPLAYER_MOVIE_FB_2X &&
                                MApp_MPlayer_QueryMoviePlayMode() <= E_MPLAYER_MOVIE_FB_32X)
                            {
                                if(g_bReplay)
                                {
#if 0   //ENABLE_DIVX_PLUS
                                    if (_MApp_VDPlayer_GetShareMemData(E_SHAREMEM_TRICK_PLAY_TRACK))
                                    {
                                        if (MApp_VDPlayer_GetTitleID() == 1)
                                        {
                                            MApp_MPlayer_MovieChangeTitle(0);
                                        }
                                    }
                                    g_eMoviePlayMode = E_MPLAYER_MOVIE_NORMAL;
#endif
                                    g_bReplay = FALSE;
                                    m_eMoviePlayMode = E_MPLAYER_MOVIE_NORMAL;
#if ENABLE_SUBTITLE_DMP
                                    //enable internal subtitle
                                    if(MApp_VDPlayer_IsTextSubtitle())
                                    {
                                        MApp_VDPlayer_TextSubtitleInit();
                                    }
                                #if (ENALBE_RENDER_SUBTITLE_IN_TRICK_MODE==0)
                                    _MApp_MPlayer_EnableSubtitleTask();
                                #endif
#endif
                                    NOTIFY(E_MPLAYER_NOTIFY_BEFORE_PLAY_ONE_FILE, NULL);
                                }
                            }
                        }
                        break;
#endif
                    default:
                        break;
                    }
                }
                else
                {
                    if(m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus & E_MPLAYER_MOVIE_STATE_ERROR_PENDING)
                    {
                        if(msAPI_Timer_DiffTimeFromNow(m_MPlayerInfo[eMPlayerIdx].u32ErrorMsgTimer) >= m_MPlayerInfo[eMPlayerIdx].u32ErrorDelayTime)
                        {
                            m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus &= (enumMediaPlayingStatus)~E_MPLAYER_MOVIE_STATE_ERROR_PENDING;
                        }
                    }

                    if(!(m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus & E_MPLAYER_MOVIE_STATE_ERROR_PENDING))
                    {
                        if(m_MPlayerInfo[eMPlayerIdx].eMediaPlayingDirection == E_MPLAYER_PLAY_DIRECTION_PREV)
                        {
                            if(!_MApp_MPlayer_PlayPrev(eMPlayerIdx))
                            {
                                m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= (enumMediaPlayingStatus)E_MPLAYER_MOVIE_STATE_PLAY_END;
                            }

                        }
                        else
                        {
                            if(!_MApp_MPlayer_PlayNext(eMPlayerIdx))
                            {
                                m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus |= (enumMediaPlayingStatus)E_MPLAYER_MOVIE_STATE_PLAY_END;
                            }
                        }
                    }

                }

                if( m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus & E_MPLAYER_MOVIE_STATE_PLAY_END
                    || (m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus & E_MPLAYER_MOVIE_STATE_ALL_ERROR
                    &&(!(m_MPlayerInfo[eMPlayerIdx].eMediaPlayingStatus & E_MPLAYER_MOVIE_STATE_ERROR_PENDING))))
                {
                    bContinue = FALSE;
                }

                if(bContinue == FALSE)
                {
                    m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_MOVIE_PLAY;
                    NOTIFY(E_MPLAYER_NOTIFY_END_OF_PLAY_ALL_FILE, &m_MPlayerInfo[eMPlayerIdx].eMediaType);
                }
                else if(bInitOk)    // Process subtitle.
                {
                #if (SUPPERTED_ADVERTISEMENT_MODE)
                    if (MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CUR_TIME)+200 >= MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_TOTAL_TIME))
                    {
                        bInitOk = FALSE;
                        g_u32TraceTimer0 = msAPI_Timer_GetTime0();
                        MApp_VDPlayer_Stop();
                        _MApp_MPlayer_PlayNext(eMPlayerIdx);
                    }
                #endif
                #if (ENABLE_SUBTITLE_DMP && ENABLE_INTERNAL_SUBTITLE)
                    if((m_eMPlayerKnlFlags&E_MPLAYER_KNL_FLG_INTERNAL_SUBTITLE_INIT_DONE)==FALSE)
                    {
                        if(MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_NB_SUBTITLE_TRACK))
                        {
                            m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_SUBTITLE_VALID;
                            m_eMPlayerKnlFlags |= E_MPLAYER_KNL_FLG_INTERNAL_SUBTITLE_INIT_DONE;

                            //enable internal subtitle
                            MApp_VDPlayer_SetSubtitleShow( E_SUBTITLE_STATE_COMMAND_SHOW/*TRUE*/ );

                            if((m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 & E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL) == 0)
                            {
                                if(MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CURRENT_SUBTITLE_TEXT))
                                {
                                    if( MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CURRENT_SUBTITLE_ISUNICODE) )
                                    {
                                        m_eSubtitleCodingType = E_MPLAYER_SUBTITLE_CODING_UNICODE;
                                    }
                                    else
                                    {
                                        m_eSubtitleCodingType = E_MPLAYER_SUBTITLE_CODING_ASC;
                                    }
                                    m_eExternalSubtitleType = E_MPLAYER_SUBTITLE_INVALID;
                                    m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_SUBTITLE_TEXT;
                                }
                                else
                                {
                                    m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_SUBTITLE_TEXT ;
                                }
                            }
                        }
                    }
                #endif

                    if(msAPI_Timer_DiffTimeFromNow(m_u32PlayCheckTime)>200)
                    {
                        if(_MApp_MPlayer_IsSupportedMovie(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType))
                        {
                            u32CurTime = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CUR_TIME);
                        #if (ENABLE_SUBTITLE_DMP)
                            _MApp_MPlayer_SubtitleTask(u32CurTime);
                        #endif //#if (ENABLE_SUBTITLE_DMP)

                            // MPEG4 time tick
                            u32CurTime /= 1000;
                            if (m_u32PlayingTickTime != u32CurTime)
                            {
                                m_u32PlayingTickTime = u32CurTime;
                                NOTIFY(E_MPLAYER_NOTIFY_PLAYING_TIME_TICK,
                                       (U32*)&m_u32PlayingTickTime);
                            }
                        }
                        m_u32PlayCheckTime = msAPI_Timer_GetTime0();
#if ENABLE_DIVX_PLUS    // timothy
                        g_u32DivxPlusPTS = _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_DIVX_CURRENT_STATUS);
                        g_u8TitleId = (U8)(g_u32DivxPlusPTS >> 24);
                        g_u8EditionId = (U8)(g_u32DivxPlusPTS >> 16);
#endif
                    }
#if ENABLE_LAST_MEMORY==1
#if ENABLE_LAST_MEMORY_PLAYTIME_UPDATE==1
                    //in case of suddently power off,
                    //set timer to keep updating LastMemory during playing
                    if (m_u8LastMemoryCheck==TRUE)
                    {
                        if(msAPI_Timer_DiffTimeFromNow(m_u32LastMemoryCheckTime)>LAST_MEMORY_UPDATE_INTERVAL)
                        {
                            if(_MApp_MPlayer_IsSupportedMovie(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType))
                            {
                                if ((MApp_MPlayer_QueryMoviePlayMode()!=E_MPLAYER_MOVIE_PAUSE)&&(MApp_MPlayer_QueryMoviePlayMode()!=E_MPLAYER_MOVIE_STOP))
                                {
                                    //save current pos/pts into LastMemory
                                    MApp_MPlayer_LastMemory_SetResumePlayAttribute(0);
                                }
                            }
                            m_u32LastMemoryCheckTime = msAPI_Timer_GetTime0();
                        }
                    }
#endif
#endif//#if ENABLE_LAST_MEMORY==1
                }
            }
        #endif  // #if ENABLE_MPLAYER_MOVIE

        #if ENABLE_MPLAYER_TEXT
            if(m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 & E_MPLAYER_KNL_FLG1_TEXT_PLAY)
            {
                bContinue = FALSE;
                MPLAYER_DBG(printf("E_MPLAYER_KNL_FLG1_TEXT_PLAY\n"));
                if(m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 & E_MPLAYER_KNL_FLG1_FILE_INIT)
                {
                    m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_FILE_INIT;
                    NOTIFY(E_MPLAYER_NOTIFY_BEFORE_PLAY_ONE_FILE, &m_MPlayerInfo[eMPlayerIdx].eMediaType);
                }
                if(!Mapp_Text_Browser())
                {
                    NOTIFY(E_MPLAYER_NOTIFY_ERROR_OF_PLAY_FILE, NULL);
                    bContinue = _MApp_MPlayer_GetNotifyRtn();
                }
                else
                {
                #if RANDOM_PLAY
                    m_bPlayNext = FALSE;
                #endif
                    NOTIFY(E_MPLAYER_NOTIFY_TEXT_NEXT_PAGE, NULL);
                }
                if(!bContinue)
                {
                    m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_TEXT_PLAY;
                }
                else
                {
                    m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_FILE_INIT;
                }
            }
        #endif  // #if ENABLE_MPLAYER_TEXT

        #if ENABLE_MPLAYER_PLUGIN
            if(m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 & E_MPLAYER_KNL_FLG1_PLUGIN_PLAY)
            {
              #if 1 //def AP_COWORK
                if( MApp_APEngine_CheckRetVal() == EXIT_APENGINE_EXIT)
              #else
                if(MApp_APEngine_Process() == EXIT_APENGINE_EXIT)
              #endif
                {
                    MApp_MPlayer_Stop();
                    NOTIFY(E_MPLAYER_NOTIFY_END_OF_PLAY_ALL_FILE, NULL);
                }
            }
        #endif //#if ENABLE_MPLAYER_PLUGIN
        }

        // check if background player need service
        if (m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 & (0
              #if ENABLE_MPLAYER_MUSIC
                | E_MPLAYER_KNL_FLG1_MUSIC_PLAY
              #endif  // #if ENABLE_MPLAYER_MOVIE
                ))
        {

        #if ENABLE_MPLAYER_MUSIC
            bContinue = TRUE;
            m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].u32ErrorDelayTime = m_u32MusicErrorDelayTimeS;
            if(m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_MUSIC_PLAY)
            {
                EN_RET bRet= EXIT_NULL;

                if(m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_FILE_INIT)
                {
                    m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_LYRIC_VALID;

                #if (ENABLE_LRC_LYRIC)
                    if(_MApp_MPlayer_Music_Lyric_Parser())
                    {
                         m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_LYRIC_VALID;
                }
                #endif

                    MApp_Music_Init();
                #if (ENABLE_WMA)
                    MApp_Wma_Init();
                #endif
                    m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_FILE_INIT;
                    m_u32PlayCheckTime = -1;
                    m_u32PlayingTickTime = -1;
                    m_u32LyricSubtitleCurTime = -1;
                    m_u16CurLyricPos = -1;

#if (ENABLE_LAST_MEMORY==1)&&ENABLE_LAST_MEMORY_ENABLE_MUSIC
                    m_u8LastMemoryCheck=TRUE;
#if(ENABLE_LAST_MEMORY_PLAYTIME_UPDATE==1)
                    m_u32LastMemoryCheckTime = msAPI_Timer_GetTime0();
#endif
                    m_u8LastMemorySearchHit = MApp_MPlayer_LastMemory_Search(&m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].curPlayingFileEntry);
#endif//#if (ENABLE_LAST_MEMORY==1)&&ENABLE_LAST_MEMORY_ENABLE_MUSIC
                }

                switch (m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType)
                {
                  #if (ENABLE_WMA)
                    case E_MPLAYER_SUBTYPE_WMA:
                        bRet = MApp_WMA_Main();
                        break;
                  #endif
                  #if (ENABLE_FLAC)
                    case E_MPLAYER_SUBTYPE_FLAC:
                        bRet = MApp_Music_Main(EN_MUSIC_FLAC);
                        break;
                  #endif

                  #if (ENABLE_AC3)
                    case E_MPLAYER_SUBTYPE_AC3:
                        bRet = MApp_Music_Main(EN_MUSIC_AC3);
                        break;
                  #endif
                  #if (ENABLE_AAC)
                    case E_MPLAYER_SUBTYPE_AAC:
                        bRet = MApp_Music_Main(EN_MUSIC_AAC);
                        break;
                  #endif

                    #if (ENABLE_WAV)
                    case E_MPLAYER_SUBTYPE_WAV:
                        bRet = MApp_Music_Main(EN_MUSIC_WAV);
                        break;
                    #endif

                    case E_MPLAYER_SUBTYPE_MP3:
                        bRet = MApp_Music_Main(EN_MUSIC_MP3);
                        break;

                  #if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
                    case E_MPLAYER_SUBTYPE_LOAS:
                        bRet = MApp_Music_Main(EN_MUSIC_LOAS);
                        break;
                  #endif

                    #if (ENABLE_OGG)
                    case E_MPLAYER_SUBTYPE_OGG:
                        bRet = MApp_Music_Main(EN_MUSIC_OGG);
                        break;
                    #endif

                    #if (ENABLE_AMR)
                    case E_MPLAYER_SUBTYPE_AMR:
                        bRet = MApp_Music_Main(EN_MUSIC_AMR);
                        break;

                    case E_MPLAYER_SUBTYPE_AWB:
                        bRet = MApp_Music_Main(EN_MUSIC_AWB);
                        break;
                    #endif

                    default:
                        break;
                }

                if(_MApp_MPlayer_IsSupportedMusic(m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType))
                {
                    switch(bRet)
                    {
                        case EXIT_MP3_INIT:
                        #if (ENABLE_WMA)
                        case EXIT_WMA_INIT:
                        #endif
                        {
                            #if RANDOM_PLAY
                                m_bPlayNext = FALSE;
                            #endif
                        #if (ENABLE_LAST_MEMORY==1)&&ENABLE_LAST_MEMORY_ENABLE_MUSIC
                            if (m_u8LastMemorySearchHit==1)
                            {
                                MPLAYER_DBG(printf("NOTIFY_LAST_MEMORY_RESUME_PLAY\n"));
                                NOTIFY(E_MPLAYER_NOTIFY_LAST_MEMORY_RESUME_PLAY, NULL);
                            }
                        #endif//#if (ENABLE_LAST_MEMORY==1)&&ENABLE_LAST_MEMORY_ENABLE_MUSIC
                        }
                        break;
                      #if (ENABLE_WMA)
                        case EXIT_WMA_INPUT:
                      #endif
                        case EXIT_MP3_INPUT:
                        {
                            NOTIFY(E_MPLAYER_NOTIFY_BEFORE_PLAY_ONE_FILE, &m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaType);
                        }
                        break;
                      #if (ENABLE_WMA)
                        case EXIT_WMA_WAIT:
                      #endif
                        case EXIT_MP3_WAIT:
                        {
                        #if (ENABLE_LAST_MEMORY==1)&&ENABLE_LAST_MEMORY_ENABLE_MUSIC
                            if (m_u8LastMemoryCheck==TRUE)
                            {
                                MApp_MPlayer_LastMemory_SetResumePlayAttribute(1);
                                m_u8LastMemoryCheck=FALSE;
                            }
                        #endif
                            NOTIFY(E_MPLAYER_NOTIFY_END_OF_PLAY_ONE_FILE, NULL);
                            if(!_MApp_MPlayer_PlayNext(E_MPLAYER_BACKGROUND_PLAYER))
                            {
                                m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaPlayingStatus |= (enumMediaPlayingStatus)E_MPLAYER_MUSIC_STATE_PLAY_END;
                            }
                         }
                         break;

                      #if (ENABLE_WMA)
                        case EXIT_WMA_EXIT:
                      #endif
                        case EXIT_MP3_EXIT:
                        {
                        #if (ENABLE_LAST_MEMORY==1)&&ENABLE_LAST_MEMORY_ENABLE_MUSIC
                            if (m_u8LastMemoryCheck==TRUE)
                            {
                                MApp_MPlayer_LastMemory_SetResumePlayAttribute(1);
                                m_u8LastMemoryCheck=FALSE;
                            }
                        #endif
                                m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaPlayingStatus |= (enumMediaPlayingStatus)E_MPLAYER_MUSIC_STATE_ERROR_PENDING;
                                m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].u32ErrorMsgTimer= msAPI_Timer_GetTime0();
                                m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType = E_MPLAYER_SUBTYPE_INVALID;
                                NOTIFY(E_MPLAYER_NOTIFY_ERROR_OF_PLAY_FILE, &m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaType);
                                if(_MApp_MPlayer_GetNotifyRtn() == FALSE) // Need to refine
                                {
                                    m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaPlayingStatus |= (enumMediaPlayingStatus)E_MPLAYER_MUSIC_STATE_ALL_ERROR;
                                }
                        }
                        break;

                        default:
                            break;
                    }
                }
                else
                {
                    if (m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaPlayingStatus & E_MPLAYER_MUSIC_STATE_ERROR_PENDING)
                    {
                        if(msAPI_Timer_DiffTimeFromNow(m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].u32ErrorMsgTimer) >= m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].u32ErrorDelayTime)
                        {
                            m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaPlayingStatus &= (enumMediaPlayingStatus)~E_MPLAYER_MUSIC_STATE_ERROR_PENDING;
                        }
                    }

                    if(!(m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaPlayingStatus & E_MPLAYER_MUSIC_STATE_ERROR_PENDING))
                    {
                        if(m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaPlayingDirection == E_MPLAYER_PLAY_DIRECTION_PREV)
                        {
                            if(!_MApp_MPlayer_PlayPrev(E_MPLAYER_BACKGROUND_PLAYER))
                            {
                                m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaPlayingStatus |= (enumMediaPlayingStatus)E_MPLAYER_MUSIC_STATE_PLAY_END;
                            }
                        }
                        else
                        {
                            if(!_MApp_MPlayer_PlayNext(E_MPLAYER_BACKGROUND_PLAYER))
                            {
                                m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaPlayingStatus |= (enumMediaPlayingStatus)E_MPLAYER_MUSIC_STATE_PLAY_END;
                            }
                        }
                    }
                }

                if( m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaPlayingStatus & E_MPLAYER_MUSIC_STATE_PLAY_END
                    || (m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaPlayingStatus & E_MPLAYER_MUSIC_STATE_ALL_ERROR
                    &&(!(m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaPlayingStatus & E_MPLAYER_MUSIC_STATE_ERROR_PENDING))))
                {
                    bContinue = FALSE;
                }


                if(bContinue == FALSE)
                {
                    m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_MUSIC_PLAY;
#if ENABLE_EMBEDDED_PHOTO_DISPLAY
                    m_eEmbeddedPhotoState = E_EMBEDDED_PHOTO_WAIT;
#endif
                    NOTIFY(E_MPLAYER_NOTIFY_END_OF_PLAY_ALL_FILE, &m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaType);
                }
                else if(msAPI_Timer_DiffTimeFromNow(m_u32PlayCheckTime)>100)
                {
//                #if (ENABLE_WMA)
//                    if(E_MPLAYER_SUBTYPE_WMA == m_MPlayerInfo[eMPlayerIdx].eMediaSubType)
//                    {
//                        //>>> TODO: add notify show lyric for wma later, 20080624, yc.chen(peter)@HsinChu
//                    }
//                    else
//                #endif

                #if (ENABLE_LYRICS3) || (ENABLE_LRC_LYRIC)
                    {
                        if((m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_LYRIC_VALID) &&
                            (m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_LYRIC_ENABLE))
                        {

                        #if (ENABLE_WMA)
                            if(E_MPLAYER_SUBTYPE_WMA == m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType)
                            {
                                u32CurTime = MApp_WMA_GetCurrentTimeMs();
                            }
                            else
                        #endif
                            {
                                u32CurTime = MApp_Music_GetCurrentTimeMs();
                            }

                            if(MApp_Music_GetLyricTag(&curLyricTag, u32CurTime))
                            {
                                if(curLyricTag.u32Time != m_u32LyricSubtitleCurTime)
                                {
                                    pu8Dst = msAPI_Memory_Allocate(LYRIC_MAX_SIZE+2, BUF_ID_FILEBROWER);

                                    if(pu8Dst)
                                    {
                                        _MApp_MPlayer_GetLyric(curLyricTag.u16LyricPos, pu8Dst);
                                        NOTIFY(E_MPLAYER_NOTIFY_SHOW_LYRIC, pu8Dst);
                                        msAPI_Memory_Free(pu8Dst, BUF_ID_FILEBROWER);
                                    }
                                    else
                                    {
                                        __ASSERT(0);
                                    }
                                    //curLyricTag.u16LyricPos = curLyricTag.u16LyricPos;
                                    m_u32LyricSubtitleCurTime = curLyricTag.u32Time;
                                }
                            }

                        }
                    }
                #endif

                    // Music time tick
                #if (ENABLE_WMA)
                    if(E_MPLAYER_SUBTYPE_WMA == m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType)
                    {
                        u32CurTime = MApp_WMA_GetCurrentTime();
                    }
                    else
                #endif
                    {
                        u32CurTime = MApp_Music_GetCurrentTime();
                    }

                    if (m_u32PlayingTickTime != u32CurTime)
                    {
                        m_u32PlayingTickTime = u32CurTime;
                        NOTIFY(E_MPLAYER_NOTIFY_PLAYING_TIME_TICK,
                               (U32*)&m_u32PlayingTickTime);
                        if((m_eMusicPlayMode != E_MPLAYER_MUSIC_NORMAL) &&  (u32CurTime == 0))
                        {
                            m_eMusicPlayMode  = E_MPLAYER_MUSIC_NORMAL;
                        }
                    }

                    m_u32PlayCheckTime = msAPI_Timer_GetTime0();
                }
#if (ENABLE_LAST_MEMORY==1)&&ENABLE_LAST_MEMORY_ENABLE_MUSIC
#if ENABLE_LAST_MEMORY_PLAYTIME_UPDATE==1
                //in case of suddently power off,
                //set timer to keep updating LastMemory during playing
                if (m_u8LastMemoryCheck==TRUE)
                {
                    if(msAPI_Timer_DiffTimeFromNow(m_u32LastMemoryCheckTime)>LAST_MEMORY_UPDATE_INTERVAL)
                    {
                        if ((MApp_MPlayer_QueryMusicPlayMode()!=E_MPLAYER_MUSIC_PAUSE)&&(MApp_MPlayer_QueryMusicPlayMode()!=E_MPLAYER_MUSIC_STOP))
                        {
                            //save current pos/pts into LastMemory
                            MApp_MPlayer_LastMemory_SetResumePlayAttribute(0);
                        }
                        m_u32LastMemoryCheckTime = msAPI_Timer_GetTime0();
                    }
                }
#endif
#endif//#if (ENABLE_LAST_MEMORY==1)&&ENABLE_LAST_MEMORY_ENABLE_MUSIC
            }
        #endif  // #if ENABLE_MPLAYER_MUSIC
        }
    }

#if ENABLE_EMBEDDED_PHOTO_DISPLAY
if(m_eMediaType == E_MPLAYER_TYPE_MUSIC)
{
    if( (MApp_MPlayer_IsMusicPlaying() || m_eMusicPreviewState != E_MUSIC_PREVIEW_NONE)
#if PLAYLIST_BGM
        &&  !m_bBGMPlaylistInit
#endif
      )
    {
        if(MApp_MPlayer_IsMusicPlaying())
        {
            if(m_u16PreFileIdx != m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].u16PlayingIdx)
            {
                if(m_eEmbeddedPhotoState != E_EMBEDDED_PHOTO_EXIT)
                {
                    if(m_eEmbeddedPhotoState != E_EMBEDDED_PHOTO_DONE)
                    {
                        MApp_MPlayer_StopEmbeddedPhotoDecode();
                    }
                    MApp_Photo_Display_Stop();
                }
                m_eEmbeddedPhotoState = E_EMBEDDED_PHOTO_WAIT;
                m_u16PreFileIdx = m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].u16PlayingIdx;
            }
        }

        if(m_eEmbeddedPhotoState == E_EMBEDDED_PHOTO_WAIT
        || m_eEmbeddedPhotoState == E_EMBEDDED_PHOTO_RUNNING)
        {
            switch(m_eEmbeddedPhotoState)
            {
            case E_EMBEDDED_PHOTO_WAIT:       // Initialize embedded photo.
                {
                    if(m_eMusicPreviewState == E_MUSIC_PREVIEW_TIMER_ENABLE)//media has not be initialed yet.
                    {
                        break;
                    }

                    if (m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_MP3
#if (ENABLE_WMA)
                        ||m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_WMA
#endif
                        )
                    {
                        BOOLEAN bInitOK = FALSE;

                        m_u32PhotoCurrentDisplayedIdx = 0;
                        m_s32Photo_LastDecodeIdx = -1;
                        m_s32Photo_LastDecodeFailIdx = -1;
                        m_u32Photo_PlayPrevDecodeFailCount = 0;

                        memcpy(&m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER],
                               &m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER],
                               sizeof(MPlayerPlayingFileInfo));

                        if(MApp_MPlayer_EmbeddedPhoto_DecodeMemory_Init(&m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].curPlayingFileEntry, FALSE, _MApp_MPlayer_EmbeddedPhoto_DataRequestCallBack) == TRUE)
                        {
                            bInitOK = TRUE;
                        }
                        else
                        {
                            bInitOK = FALSE;
                        }

                        if(bInitOK)
                        {
                            if (m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_MUSIC_PLAY)
                                MApp_Photo_Display_SetViewWin(EMBEDDED_PHOTO_X, EMBEDDED_PHOTO_Y, EMBEDDED_PHOTO_WIDTH, EMBEDDED_PHOTO_HEIGHT);
                            else
                                MApp_Photo_Display_SetViewWin(PHOTO_PREVIEW_X, PHOTO_PREVIEW_Y, PHOTO_PREVIEW_WIDTH, PHOTO_PREVIEW_HEIGHT);

                            EN_PHOTO_ORIENTATION eOrientation;
#if (SHOW_PARTIALLY_DECODING_PHOTO)
                            MApp_Photo_InitPreviewDisplay();
#endif // #if (SHOW_PARTIALLY_DECODING_PHOTO)

                            eOrientation = (EN_PHOTO_ORIENTATION)MApp_Photo_GetInfo(E_PHOTO_INFO_ORIENTATION);
                            if(eOrientation < E_PHOTO_ORIENT_NOT_FOUND)
                            {
                                m_photoInfo.eOrientation = (enumMPlayerJPGOrient)eOrientation;
                            }
                            else
                            {
                                m_photoInfo.eOrientation = E_MPLAYER_JPEG_ORIENT_ORIGINAL;
                            }

                            if(MApp_Photo_GetInfo(E_PHOTO_INFO_FILE_FORMAT) == E_PHOTO_FILE_GIF)
                            {
                                MApp_Photo_GIFResetDisplay();
                            }
                            m_eEmbeddedPhotoState = E_EMBEDDED_PHOTO_RUNNING;

                            NOTIFY(E_MPLAYER_NOTIFY_BEFORE_EMBEDDED_PHOTO_DISPLAY, &m_eMusicPreviewState);
                        }
                        else
                        {
                            MApp_MPlayer_StopEmbeddedPhoto();
                            NOTIFY(E_MPLAYER_NOTIFY_ERROR_OF_EMBEDDED_PHOTO_DISPLAY, NULL);
                        }
                    }
                }
                break;

            case E_EMBEDDED_PHOTO_RUNNING:            //Embedded photo decode and display.
                if ((MApp_Photo_GetInfo(E_PHOTO_INFO_FILE_FORMAT) == E_PHOTO_FILE_JPEG)
                 || (MApp_Photo_GetInfo(E_PHOTO_INFO_FILE_FORMAT) == E_PHOTO_FILE_BMP)
                 || (MApp_Photo_GetInfo(E_PHOTO_INFO_FILE_FORMAT) == E_PHOTO_FILE_PNG)
                 || (MApp_Photo_GetInfo(E_PHOTO_INFO_FILE_FORMAT) == E_PHOTO_FILE_TIFF))
                {
                    switch (MApp_Photo_Main())
                    {
                        case EXIT_PHOTO_DECODE_FAIL:
                            MApp_MPlayer_StopEmbeddedPhoto();
                            NOTIFY(E_MPLAYER_NOTIFY_ERROR_OF_EMBEDDED_PHOTO_DISPLAY, NULL);
                            break;

                        case EXIT_PHOTO_DECODE_ONE_FRAME_DONE:
                            if(MApp_Photo_GetInfo(E_PHOTO_INFO_IS_MPO_DISPARITY_TYPE) == TRUE)
                            {
                                //for mpo preview, only decode first frame.
                                MApp_Photo_Stop();
                            }
                            // fall through
                        case EXIT_PHOTO_DECODE_DONE:
                            if(MApp_Photo_GetInfo(E_PHOTO_INFO_IS_MPO_DISPARITY_TYPE) == TRUE)
                            {
                                MApp_Photo_MPODisplay(TRUE);
                            }
                            else
                            {
                                MApp_Photo_Display(TRUE);
                            }
                            MApp_MPlayer_StopEmbeddedPhotoDecode();
                            m_eEmbeddedPhotoState = E_EMBEDDED_PHOTO_DONE;
                            NOTIFY(E_MPLAYER_NOTIFY_END_OF_EMBEDDED_PHOTO_DISPLAY, NULL);
                            break;

#if (SHOW_PARTIALLY_DECODING_PHOTO)
                        case EXIT_PHOTO_DECODING:
#if ENABLE_AUTO_ROTATION
                            //if has rotation, show when decode done
                            if(m_photoInfo.eOrientation < E_MPLAYER_JPEG_ORIENT_TOP_RIGHT || m_photoInfo.eOrientation > E_MPLAYER_JPEG_ORIENT_LEFT_BOTTOM)
#endif
                            {
                                MApp_Photo_Display(TRUE);
                            }
                            // fall through
#endif // #if (SHOW_PARTIALLY_DECODING_PHOTO)

                        default:
                            break;
                    }
                }
                else if(MApp_Photo_GetInfo(E_PHOTO_INFO_FILE_FORMAT) == E_PHOTO_FILE_GIF)
                {
                    switch (MApp_Photo_Main())
                    {
                        case EXIT_PHOTO_DECODE_FAIL:
                            MApp_MPlayer_StopEmbeddedPhoto();
                            NOTIFY(E_MPLAYER_NOTIFY_ERROR_OF_EMBEDDED_PHOTO_DISPLAY, NULL);
                            break;

                        case EXIT_PHOTO_DECODE_DONE:
                            break;

#if (SHOW_PARTIALLY_DECODING_PHOTO)
                        case EXIT_PHOTO_DECODING:
                            if(MApp_Photo_GetInfo(E_PHOTO_INFO_DECODED_FRAME_INDEX) == 0xFFFFFFFF)
                            {
                                MApp_Photo_Display(TRUE);
                            }
                            // fall through
#endif // #if (SHOW_PARTIALLY_DECODING_PHOTO)
                        default:
                            break;
                    }
                    if(MApp_Photo_GIFIsDisplayDone())
                    {
                        MApp_MPlayer_StopEmbeddedPhotoDecode();
                        m_eEmbeddedPhotoState = E_EMBEDDED_PHOTO_DONE;
                        NOTIFY(E_MPLAYER_NOTIFY_END_OF_EMBEDDED_PHOTO_DISPLAY, NULL);
                    }
                    else
                    {
                        MApp_Photo_GIFDisplay(TRUE);
                    }
                }
                break;

            default:
                break;
            }
        }
    }
}
#endif

    if(0)
    {
    }
#if ENABLE_DELETE_SELECTED_FILES
    else if(m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_DELETE_PLAY)
    {
        bContinue = TRUE;

        //check usb status.
        MPlayerDrive srcDriveInfo;

        if(MApp_MPlayer_QueryDriveInfoByLun(m_u8DeleteLun, &srcDriveInfo)==0xFF)
        {
            m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_DELETE_INIT;
            m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_DELETING;
            bContinue = FALSE;

            NOTIFY(E_MPLAYER_NOTIFY_DELETE_USED_USB_REMOVE,(U16*)&m_u16DeleteCount);
        }
        else
        {
            //todo
        }

        if(m_bUserBreakDelete)
        {
            m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_DELETE_INIT;
            m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_DELETING;
            m_bEndofDeleteFiles = TRUE;
            bContinue = FALSE;
        }

        if(m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_DELETE_INIT)
        {
            //start file operation
            if(E_MPLAYER_RET_OK == MApp_MPlayer_DeleteSelectedFile_Init(m_u16CurDeletePlaylistIdx, &m_CurDeleteFileEntry))
            {
                MPLAYER_DBG(printf("Delete0 init done\n"));
                m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_DELETE_INIT;
                m_eMPlayerKnlFlags |= (enumMPlayerKnlFlags)E_MPLAYER_KNL_FLG_DELETING;
                //delete i th file start.
                NOTIFY(E_MPLAYER_NOTIFY_BEFORE_DELETE_ONE_FILE,(U16*)&m_u16DeleteCount);
            }
            else
            {
                MPLAYER_DBG(printf("Delete0 init fail\n"));
                m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_DELETE_INIT;
                NOTIFY(E_MPLAYER_NOTIFY_ERROR_OF_DELETE_FILE,(U16*)&m_u16DeleteCount);

                if(_MApp_MPlayer_DeleteNext()==FALSE)
                {
                    bContinue = FALSE;
                }
            }

        }
        else if(m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_DELETING)
        {
            if(MApp_FileBrowser_DeleteFileByFileEntry(&m_CurDeleteFileEntry) == TRUE)
            {
                MPLAYER_DBG(printf("Delete1 done\n"));
            #if ENABLE_SUBTITLE_COPY_AND_DELETE
                if(m_bDeletingExtSubtitleFile==FALSE)
            #endif
                {
                    MApp_MPlayer_RemoveFileFromPlayList(m_eMediaType, m_u16CurDeletePlaylistIdx, TRUE);

                    //When user delete mp3 file , we have to check the mp3 is in BGM or not.
                    //If the deleted mp3 is in BGM list , we have to remove the mp3 in BGM list also
                    //PS:m_u16BGMSelectedFileNum this means BGM be selected number
                #if PLAYLIST_BGM
                    if(m_eMediaType == E_MPLAYER_TYPE_MUSIC
                    && m_u16BGMSelectedFileNum > 0)
                    {
                        U16 i;
                        FileEntry stFileEntry;

                        MApp_MPlayer_BGM_Playlist_Init(); //Swap MUSIC play list and BGM play list
                        //-------Enter BGM mode-----------------

                        for(i=0; i<m_u16SelectedFileNum[E_MPLAYER_TYPE_MUSIC]; i++)
                        {
                            if(MApp_MPlayer_GetFileEntryByPlaylistIndex(i, E_MPLAYER_TYPE_MUSIC, &stFileEntry))
                            {
                                if(memcmp(m_CurDeleteFileEntry.EntryID,     stFileEntry.EntryID,     4)==0
                                && memcmp(m_CurDeleteFileEntry.EntryID_Ext, stFileEntry.EntryID_Ext, 8)==0
                                && m_CurDeleteFileEntry.FileSystemID == stFileEntry.FileSystemID)
                                {
                                    MApp_MPlayer_RemoveFileFromPlayList(E_MPLAYER_TYPE_MUSIC, i, TRUE);
                                    break;
                                }
                            }
                        }
                        //-------Exit BGM mode-----------------
                        MApp_MPlayer_BGM_Playlist_DeInit(); //Swap MUSIC play list and BGM play list
                    }
                #endif

                    m_u16DeleteCount++;
                    MPLAYER_DBG(printf("m_u16TotalDeleteCount = %d\n", m_u16TotalDeleteCount));

                    U32 u32TempPercentage;
                    u32TempPercentage = (U32)(m_u16DeleteCount*100/m_u16TotalDeleteCount);

                    if(u32TempPercentage > m_u32TotalDeletedPercentage)
                    {
                        m_u32TotalDeletedPercentage = u32TempPercentage;
                    }
                    //no.i file delete OK.
                    NOTIFY(E_MPLAYER_NOTIFY_END_OF_DELETE_ONE_FILE,(U16*)&m_u16DeleteCount);
                }
                if(_MApp_MPlayer_DeleteNext()==FALSE)
                {
                    bContinue = FALSE;
                }
            }
            else
            {
                MPLAYER_ERROR(" !!! Delete fail, force STOP !!!\n");
                //no.i file delete fail.
                NOTIFY(E_MPLAYER_NOTIFY_ERROR_OF_DELETE_FILE,(U16*)&m_u16DeleteCount);
                //Delete fail, stop !!!
                bContinue = FALSE;
            }

            m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_DELETING;
        }

        if(bContinue == FALSE)
        {
            m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_DELETE_PLAY;

        #if (HIGH_SPEED_BROWSER)
            m_u16BufDirectoryDepth = MPLAYER_INVALID_INDEX;
        #endif
            _MApp_MPlayer_Browser_EnumCurDirectory();
            m_u16TotalPageNum = (m_u16TotalFileNum+m_u16FilesPerPage-1) /m_u16FilesPerPage;
            if (m_u16CurPageIdx >= m_u16TotalPageNum)
            {
                m_u16CurPageIdx = m_u16TotalPageNum - 1;
                m_u16CurPage1stFileIdx -= NUM_OF_PHOTO_FILES_PER_PAGE;
                m_u16CurFileIdx = 1;//todo , now force to 1
            }

            //end of delete all files.
            if(m_bEndofDeleteFiles == TRUE)
            {
                NOTIFY(E_MPLAYER_NOTIFY_END_OF_DELETE_ALL_FILE,(U16*)&m_u16DeleteCount);
            }
        }
    }
#endif
#if ENABLE_COPY_SELECTED_FILES
    else if(m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_COPY_PLAY)
    {
        bContinue = TRUE;

        //check usb status.
        MPlayerDrive srcDriveInfo, dstDriveInfo;

        if(MApp_MPlayer_QueryDriveInfoByLun(m_u8CopySrcLun, &srcDriveInfo)==0xFF
        || MApp_MPlayer_QueryDriveInfoByLun(m_u8CopyDstLun, &dstDriveInfo)==0xFF)
        {
            m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_COPY_INIT;
            m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_COPYING;
            bContinue = FALSE;

            NOTIFY(E_MPLAYER_NOTIFY_COPY_USED_USB_REMOVE,(U16*)&u16CurrentCopyIndex);
        }
        else
        {
            //todo
        }

        if(m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_COPY_INIT)
        {
            //User break
            if(m_bUserBreakCopy)
            {
                m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_COPY_INIT;
                m_bEndofCopyFiles = TRUE;
                bContinue = FALSE;
            }
            else
            {
                //start file operation
                if(_MApp_MPlayer_BeginPasteFileAndRenameIfFileExisted() == TRUE)
                {
                    MPLAYER_DBG(printf("Copy init done\n"));
                    m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_COPY_INIT;
                    m_eMPlayerKnlFlags |= (enumMPlayerKnlFlags)E_MPLAYER_KNL_FLG_COPYING;
                    //copy i th file start.
                    NOTIFY(E_MPLAYER_NOTIFY_BEFORE_COPY_ONE_FILE,(U16*)&u16CurrentCopyIndex);
                }
                else
                {
                    MPLAYER_DBG(printf(" !!! Copy init fail !!!\n"));
                    m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_COPY_INIT;
                    NOTIFY(E_MPLAYER_NOTIFY_ERROR_OF_COPY_FILE,(U16*)&u16CurrentCopyIndex);

                    if(_MApp_MPlayer_CopyNext() == FALSE)
                    {
                        bContinue = FALSE;
                    }
                }
            }
        }
        else if(m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_COPYING)
        {
            //User break
            if(m_bUserBreakCopy)
            {
                m_u32CopyDataLeft = 0xFFFFFFFF;
                m_bEndofCopyFiles = TRUE;
            }
            else
            {
                U32 u32CopyLength;
                #define COPY_MAX_LEN    0x400000UL

                u32CopyLength = m_u32CopyDataLeft < COPY_MAX_LEN ?
                                m_u32CopyDataLeft : COPY_MAX_LEN;
                if ((msAPI_FCtrl_FileRead(m_u8FileOpReadHandle,
                                         FILE_OPERATION_BUFFER,
                                         u32CopyLength) == 0) &&
                    (msAPI_FCtrl_FileWrite(m_u8FileOpWriteHandle,
                                          FILE_OPERATION_BUFFER,
                                          u32CopyLength) == 0))
                {
                    //todo: add notify -- return u32CopyLength
                    MPLAYER_DBG(printf("copy: %lu\n", u32CopyLength));
                    m_u32CopyDataLeft -= u32CopyLength;
                    m_u64TotalCopiedSize += u32CopyLength;
                #if 1
                    U32 u32TempPercentage;
                    if(m_u64TotalCopySize == 0)
                    {
                        u32TempPercentage = 100;
                    }
                    else if(m_u64TotalCopySize < 100)

                    {
                        u32TempPercentage = (U32)(m_u64TotalCopiedSize*100/m_u64TotalCopySize);
                    }
                    else
                    {
                        u32TempPercentage = (U32)(m_u64TotalCopiedSize/(m_u64TotalCopySize/100));
                    }

                    if(u32TempPercentage > m_u32TotalCopiedPercentage)
                    {
                        m_u32TotalCopiedPercentage = u32TempPercentage;
                        m_u32TotalCopiedSizeInKB  = (U32)(m_u64TotalCopiedSize >> 10);
                        NOTIFY(E_MPLAYER_NOTIFY_UPDATE_COPIED_FILE_SIZE,(U32*)&m_u32TotalCopiedSizeInKB);
                    }
                #else
                    m_u32TotalCopiedSizeInKB  = (U32)(m_u64TotalCopiedSize >> 10);
                    NOTIFY(E_MPLAYER_NOTIFY_UPDATE_COPIED_FILE_SIZE,(U32*)&m_u32TotalCopiedSizeInKB);
                #endif
                }
                else
                {
                    MPLAYER_ERROR(" !!! copy fail !!!\n");
                    NOTIFY(E_MPLAYER_NOTIFY_ERROR_OF_COPY_FILE,(U16*)&u16CurrentCopyIndex);
                    m_u32CopyDataLeft = 0xFFFFFFFF;
                }
            }

            if (m_u32CopyDataLeft == 0 || m_u32CopyDataLeft == 0xFFFFFFFF)
            {
                FileEntry stBackupDstFileEntry;
                memset(&stBackupDstFileEntry, 0, sizeof(FileEntry));
                BOOLEAN bRet = msAPI_FCtrl_EntryGetByHandle(m_u8FileOpWriteHandle, &stBackupDstFileEntry);

                msAPI_FCtrl_FileClose(m_u8FileOpReadHandle);
                m_u8FileOpReadHandle = FCTRL_INVALID_FILE_HANDLE;
                msAPI_FCtrl_FileClose(m_u8FileOpWriteHandle);
                m_u8FileOpWriteHandle = FCTRL_INVALID_FILE_HANDLE;

                m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_COPYING;

                if (m_u32CopyDataLeft == 0xFFFFFFFF)
                {
                    //something error or user break.
                    //For copy, need to check how to delete
                    if(bRet == TRUE)
                    {
                        msAPI_FCtrl_FileDelete(&stBackupDstFileEntry);
                    }
                    bContinue = FALSE;
                }
                else
                {
                #if ENABLE_SUBTITLE_COPY_AND_DELETE
                    //2 case: Case1:If no external subtitle file, it needs to notify UI.
                    //        Case2: If movie with related subtitle all copy done , it needs to notify UI.
                    if((m_bCopyingExtSubtitleFile == FALSE && m_u8CopyDeleteExtSubtitleFileNum == 0)
                    || (m_bCopyingExtSubtitleFile == TRUE && m_u8CurCopyingDeletingExtSubtitleFileIdx == m_u8CopyDeleteExtSubtitleFileNum-1))
                #endif
                    {
                        NOTIFY(E_MPLAYER_NOTIFY_END_OF_COPY_ONE_FILE,(U16*)&u16CurrentCopyIndex);
                    }

                    if(_MApp_MPlayer_CopyNext() == FALSE)
                    {
                        bContinue = FALSE;
                    }
                }
            }
        }

        //all file copied or user break or error
        if(bContinue == FALSE)
        {
            if(m_bAfterCopyDoneStayInSrcFolder)
            {
                // return to source folder.
                MApp_FileBrowser_Destroy(m_u8CopyDstFileBrowserHandle);
                m_u8CopyDstFileBrowserHandle = INVALID_BROWSER_HANDLE;
                MApp_FileBrowser_SetEnvironment(m_u8CopySrcFileBrowserHandle);
                m_u16CurDriveIdx = m_u16CopySrcDriveIdx;
            }
            else
            {
                // return to destination folder.
                MApp_FileBrowser_Destroy(m_u8CopySrcFileBrowserHandle);
                m_u8CopySrcFileBrowserHandle = INVALID_BROWSER_HANDLE;
                MApp_FileBrowser_SetEnvironment(m_u8CopyDstFileBrowserHandle);
                m_u8UserBrowserHandle = m_u8CopyDstFileBrowserHandle;
                m_u16CurDriveIdx = m_u16CopyDstDriveIdx;

            #if (HIGH_SPEED_BROWSER)
                // force to re-enum current directory
                m_u16BufDirectoryDepth = MPLAYER_INVALID_INDEX;
            #endif
                _MApp_MPlayer_Browser_EnumCurDirectory();

                if(m_u16TotalFileNum && m_u16FilesPerPage>0)
                {
                    m_u16TotalPageNum = (m_u16TotalFileNum+m_u16FilesPerPage-1) /m_u16FilesPerPage;
                }
            }

            m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_COPYING;
            m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_COPY_PLAY;

            //todo: add notify -- end of all copy files.
            if(m_bEndofCopyFiles == TRUE)
            {
                NOTIFY(E_MPLAYER_NOTIFY_END_OF_COPY_ALL_FILE,NULL);
            }
        }
    }
#endif
#if 1//def ZUI
    else if(m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_DECODE_N_THUMBNAIL)
    {
        BOOLEAN bInitOk;
        //printf("\n E_MPLAYER_KNL_FLG_DECODE_N_THUMBNAIL ");
        msAPI_Timer_ResetWDT();
        if(m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_THUMBNAIL_INIT)
        {
            //printf("\n E_MPLAYER_KNL_FLG_THUMBNAIL_INIT ");
            memset(&stThumb, 0, sizeof(stThumb));
            //printf("[Thumb] %d. idx = %d  + 1st Idx(%d)\n", m_u8ThumbnailNIdx, m_au8ThumbQueue[m_u8ThumbnailNIdx], m_u16CurPage1stFileIdx);
            m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType = E_MPLAYER_SUBTYPE_INVALID;
         if(MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,
                                          m_u16CurPage1stFileIdx+m_au8ThumbQueue[m_u8ThumbnailNIdx],
                                          &fileInfo) == E_MPLAYER_RET_OK)
        {
                memcpy(&m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].curPlayingFileEntry,
                        &fileInfo.fileEntry,
                        sizeof(FileEntry));

                if (IS_PHOTO_FILE(fileInfo.u8ExtFileName))
                {
                    if (IS_JPG_FILE(fileInfo.u8ExtFileName)
                        #if (ENABLE_PHOTO_SOFTWARE_DECODER_THUMBNAIL)
                            || IS_BMP_FILE(fileInfo.u8ExtFileName)
                            || IS_PNG_FILE(fileInfo.u8ExtFileName)
                            || IS_TIFF_FILE(fileInfo.u8ExtFileName)
                        #endif //#if (ENABLE_PHOTO_SOFTWARE_DECODER_THUMBNAIL)
                        )
                    {
                    #if (ENABLE_4K2K)
                        ST_PHOTO_DECODE_RESOLUTION_DEFINTIONS stPhotoResolution;
                        _MApp_MPlayer_RestrictPhotoDecodeResolution(&stPhotoResolution);

                        MApp_Photo_DecodeResolutionCfg(stPhotoResolution);
                    #endif
                        // ask photo decoder to decode thumbnail
                        bInitOk = MApp_Photo_DecodeFile_Init(&m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].curPlayingFileEntry, TRUE);

                    #if ENABLE_DECODE_FULL_PHOTO_IF_NOTHUMB
                        if ((bInitOk == FALSE) && ((MApp_Photo_GetErrCode() == E_PHOTO_ERR_NO_THUMBNAIL) || (MApp_Photo_GetErrCode() == E_PHOTO_ERR_DECODE_FAILURE)))
                        {
                            // ask photo decoder to decode full image because no thumbnail can be found
                            MApp_Photo_Stop();
                        #if (ENABLE_4K2K)
                            MApp_Photo_DecodeResolutionCfg(stPhotoResolution);
                        #endif
                            bInitOk = MApp_Photo_DecodeFile_Init(&m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].curPlayingFileEntry, FALSE);
                        }
                    #endif // #if ENABLE_DECODE_FULL_PHOTO_IF_NOTHUMB

                        if (bInitOk == TRUE)
                        {
                            if (IS_JPG_FILE(fileInfo.u8ExtFileName))
                            {
                                m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType = E_MPLAYER_SUBTYPE_JPG;
                            }
                        #if (ENABLE_PHOTO_SOFTWARE_DECODER_THUMBNAIL)
                            #if (ENABLE_BMP)
                            else if (IS_BMP_FILE(fileInfo.u8ExtFileName))
                            {
                                m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType = E_MPLAYER_SUBTYPE_BMP;
                            }
                            #endif
                            #if (ENABLE_PNG)
                            else if (IS_PNG_FILE(fileInfo.u8ExtFileName))
                            {
                                m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType = E_MPLAYER_SUBTYPE_PNG;
                            }
                            #endif
                            #if (ENABLE_TIFF)
                            else if (IS_TIFF_FILE(fileInfo.u8ExtFileName))
                            {
                                m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType = E_MPLAYER_SUBTYPE_TIFF;
                            }
                            #endif
                        #endif //#if (ENABLE_PHOTO_SOFTWARE_DECODER_THUMBNAIL)
                        }
                    }
                }
                #if ENABLE_MPLAYER_MOVIE
                 else if (IS_MOVIE_FILE(fileInfo.u8ExtFileName))//(m_eMediaType==E_MPLAYER_TYPE_MOVIE)//(IS_MOVIE_FILE(fileInfo.u8ExtFileName))
                {
                    m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_MOVIE;

                    MApp_VDPlayer_EnableVideoOutputFlag(ENABLE);
                    MApp_VDPlayer_BeginThumbnail();

                    if(MApp_VDPlayer_Init(VIDEO_PLAYER_INPUT_SOURCE_MM, eType, &m_MPlayerInfo[eMPlayerIdx].curPlayingFileEntry) == TRUE)
                    {
                        if (!MApp_VDPlayer_MovieThumbnail_SetMVOP())
                        {
                            MApp_VDPlayer_StopThumbnail();
                            MApp_VDPlayer_Stop();
                            MApp_VDPlayer_StopPreview();
                            m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_INVALID;
                        }
                    }
                    else
                    {
                        MApp_VDPlayer_StopThumbnail();
                        MApp_VDPlayer_Stop();
                        MApp_VDPlayer_StopPreview();
                        m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_INVALID;
                    }
                }
                 #endif
                #if ENABLE_EMBEDDED_PHOTO_DISPLAY
                 else if (IS_MUSIC_FILE(fileInfo.u8ExtFileName))
                {
                    if (IS_MP3_FILE(fileInfo.u8ExtFileName) || IS_WMA_FILE(fileInfo.u8ExtFileName))
                    {
                        // ask photo decoder to decode thumbnail
                        if(MApp_MPlayer_EmbeddedPhoto_DecodeMemory_Init(&m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].curPlayingFileEntry, FALSE, _MApp_MPlayer_EmbeddedPhoto_DataRequestCallBack) == TRUE)
                        {
                            bInitOk = TRUE;
                        }
                        else
                        {
                            bInitOk = FALSE;
                            //bInitOk = MApp_Photo_DecodeFile_Init(&m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].curPlayingFileEntry, FALSE);
                        }

                        if (bInitOk == TRUE)
                        {
                            if (IS_MP3_FILE(fileInfo.u8ExtFileName))
                            {
                                m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType = E_MPLAYER_SUBTYPE_MP3;
                            }
#if (ENABLE_WMA)
                            else if (IS_WMA_FILE(fileInfo.u8ExtFileName))
                            {
                                m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType = E_MPLAYER_SUBTYPE_WMA;
                            }
#endif
                        }
                    }
                }
                #endif
                m_eMPlayerKnlFlags |= (enumMPlayerKnlFlags)E_MPLAYER_KNL_FLG_THUMBNAIL_DECODE;
            }
            else
            {
                m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_DECODE_N_THUMBNAIL;
            }
            m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_THUMBNAIL_INIT;
            return; //for IR key sensitivity
        }

        if(m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_THUMBNAIL_DECODE)//E_MPLAYER_KNL_FLG_DECODE_N_THUMBNAIL)
        {
            //printf("\n E_MPLAYER_KNL_FLG_THUMBNAIL_DECODE ");
            if ((m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_JPG)
#if (ENABLE_PHOTO_SOFTWARE_DECODER_THUMBNAIL)
                    #if (ENABLE_BMP)
                    || (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_BMP)
                    #endif
                    #if (ENABLE_PNG)
                    || (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_PNG)
                    #endif
                    #if (ENABLE_TIFF)
                    || (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_TIFF)
                    #endif
#endif // #if (ENABLE_PHOTO_SOFTWARE_DECODER_THUMBNAIL)
                )
            {
                stThumb.eRet_thumb = MApp_Photo_Main();
            }
#if ENABLE_MPLAYER_MOVIE
            else if (m_MPlayerInfo[eMPlayerIdx].eMediaSubType == E_MPLAYER_SUBTYPE_MOVIE)
            {
                U32 u32dwin_addr=0 ;
                U16 u16_width = (((MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_FRAMEINFO_WIDTH)+7)>>3)<<3);
                U16 u16_height = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_FRAMEINFO_HEIGHT);

                m_eMovieMainExit = EXIT_VDPLAYER_NULL;

                stThumb.stPhotoImgFrom.u16RectX = 0;
                stThumb.stPhotoImgFrom.u16RectY = 0;
                stThumb.stPhotoImgFrom.u16RectW = u16_width; //(U16)MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_H_SIZE);   //PANEL_WIDTH;
                stThumb.stPhotoImgFrom.u16RectH = u16_height;  // (U16)MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_V_SIZE);  // PANEL_HEIGHT;

                // Refine the start position of thumbnail.
                stThumb.stPhotoImgTo.u16RectX = m_u16ThumbnailArray[m_au8ThumbQueue[m_u8ThumbnailNIdx]][0];//+UI_MEDIAPLAYER_MAINITEM_FRM_LINE_WIDTH;
                stThumb.stPhotoImgTo.u16RectY = m_u16ThumbnailArray[m_au8ThumbQueue[m_u8ThumbnailNIdx]][1];//+UI_MEDIAPLAYER_MAINITEM_FRM_LINE_WIDTH;
                stThumb.stPhotoImgTo.u16RectW = THUMBNAIL_WIDTH;
                stThumb.stPhotoImgTo.u16RectH = THUMBNAIL_HEIGHT;

                MApp_VDPlayer_MovieThumbnail_DWINCapture(&u32dwin_addr);
                stThumb.stPhotoImgFrom.u32BuffAddr = u32dwin_addr;
                stThumb.eRet_thumb = EXIT_VDPLAYER_EXIT;
            }
  #endif
  #if ENABLE_EMBEDDED_PHOTO_DISPLAY
            else if (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_MP3
#if (ENABLE_WMA)
                    ||m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eMediaSubType == E_MPLAYER_SUBTYPE_WMA
#endif
                    )
            {
                //music thumbnail decode
                stThumb.eRet_thumb = MApp_Photo_Main();
            }
  #endif
            else
            {
                MPLAYER_DBG(printf("\n EXIT_PHOTO_DECODE_NO_THUMBNAIL "));
                stThumb.eRet_thumb = EXIT_PHOTO_DECODE_NO_THUMBNAIL;
            }
            m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_THUMBNAIL_DECODE;
            m_eMPlayerKnlFlags |= (enumMPlayerKnlFlags)E_MPLAYER_KNL_FLG_THUMBNAIL_DONE;

            return;
        }

        if(m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_THUMBNAIL_DONE)
        {
            MPlayerNotifyOneThumbnail notifyThumbnail;
            //printf("\n E_MPLAYER_KNL_FLG_THUMBNAIL_DONE ");
            m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_THUMBNAIL_DONE;
            switch (stThumb.eRet_thumb)
            {
            case EXIT_PHOTO_DECODE_FAIL:
            case EXIT_PHOTO_DECODE_NO_THUMBNAIL:
            default:
                // send decode fail notification
                notifyThumbnail.u16FileIdx = m_au8ThumbQueue[m_u8ThumbnailNIdx];
                notifyThumbnail.bOK = FALSE;
            #if ENABLE_EMBEDDED_PHOTO_DISPLAY
                MApp_MPlayer_StopEmbeddedPhotoDecode();
            #endif
                NOTIFY(E_MPLAYER_NOTIFY_END_OF_ONE_THUMBNAIL, &notifyThumbnail);

                // decode next file
                m_u8ThumbnailNIdx++;
                m_eMPlayerKnlFlags |= E_MPLAYER_KNL_FLG_THUMBNAIL_INIT;
                break;

            case EXIT_PHOTO_DECODE_ONE_FRAME_DONE:
                if(MApp_Photo_GetInfo(E_PHOTO_INFO_IS_MPO_DISPARITY_TYPE) == TRUE)
                {
                    //for mpo thumbnail, only decode first frame.
                    MApp_Photo_Stop();
                }
                // fall through
        #if (SHOW_PARTIALLY_DECODING_THUMBNAIL)
            case EXIT_PHOTO_DECODING:
                m_eMPlayerKnlFlags |= E_MPLAYER_KNL_FLG_THUMBNAIL_DECODE;
                // fall through
        #endif // #if (SHOW_PARTIALLY_DECODING_THUMBNAIL)
            case EXIT_PHOTO_DECODE_DONE:
                memset(&stThumb.stPhotoImgTo, 0, sizeof(stThumb.stPhotoImgTo));
                memset(&stThumb.stPhotoImgFrom, 0, sizeof(stThumb.stPhotoImgFrom));

                MApp_DMP_GetZUIFbAttr(&m_thumbnailFbAttr);
                stThumb.stPhotoImgTo.u32BuffAddr = m_thumbnailFbAttr.addr;
                stThumb.stPhotoImgTo.u16BuffW = m_thumbnailFbAttr.width;
                stThumb.stPhotoImgTo.u16BuffH = m_thumbnailFbAttr.height;
                stThumb.stPhotoImgTo.u8FbFmt =(U8) m_thumbnailFbAttr.fbFmt; // it is because GOP driver, please ask min-cha ////GFX_FMT_ARGB1555
                //printf("\n u32BuffAddr=%lx, u16BuffW=%x , u16BuffH=%x  , fmt=%x \n",m_thumbnailFbAttr.addr,m_thumbnailFbAttr.width, m_thumbnailFbAttr.height , (U8)m_thumbnailFbAttr.fbFmt);

                stThumb.stPhotoImgFrom.u16RectX = 0;
                stThumb.stPhotoImgFrom.u16RectY = 0;
                stThumb.stPhotoImgFrom.u16RectW = MApp_Photo_GetInfo(E_PHOTO_INFO_WIDTH) & 0xfffc;
                stThumb.stPhotoImgFrom.u16RectH = MApp_Photo_GetInfo(E_PHOTO_INFO_HEIGHT);

                // Refine the start position of thumbnail.
                stThumb.stPhotoImgTo.u16RectX = m_u16ThumbnailArray[m_au8ThumbQueue[m_u8ThumbnailNIdx]][0];//+UI_MEDIAPLAYER_MAINITEM_FRM_LINE_WIDTH;
                stThumb.stPhotoImgTo.u16RectY = m_u16ThumbnailArray[m_au8ThumbQueue[m_u8ThumbnailNIdx]][1];//+UI_MEDIAPLAYER_MAINITEM_FRM_LINE_WIDTH;
                stThumb.stPhotoImgTo.u16RectW = THUMBNAIL_WIDTH;
                stThumb.stPhotoImgTo.u16RectH = THUMBNAIL_HEIGHT;

                MApp_Photo_Display_Thumbnail(
                        &stThumb.stPhotoImgTo,
                        &stThumb.stPhotoImgFrom,
                        EN_PHOTO_ALIGN_MIDDLE_CENTERED,
                        EN_PHOTO_FIT_BOUNDARY);

            #if (SHOW_PARTIALLY_DECODING_THUMBNAIL)
                if ((stThumb.eRet_thumb == EXIT_PHOTO_DECODE_DONE) || (stThumb.eRet_thumb == EXIT_PHOTO_DECODE_ONE_FRAME_DONE))
            #endif // #if (SHOW_PARTIALLY_DECODING_THUMBNAIL)
                {
                    // send decode done notification
                    notifyThumbnail.u16FileIdx = m_au8ThumbQueue[m_u8ThumbnailNIdx];
                    notifyThumbnail.bOK = TRUE;
                #if ENABLE_EMBEDDED_PHOTO_DISPLAY
                    MApp_MPlayer_StopEmbeddedPhotoDecode();
                #endif
                    NOTIFY(E_MPLAYER_NOTIFY_END_OF_ONE_THUMBNAIL, &notifyThumbnail);

                    // decode next file
                    m_u8ThumbnailNIdx++;
                    m_eMPlayerKnlFlags |= E_MPLAYER_KNL_FLG_THUMBNAIL_INIT;
                }
                break;

        #if (!SHOW_PARTIALLY_DECODING_THUMBNAIL)
            case EXIT_PHOTO_DECODING:
                m_eMPlayerKnlFlags |= E_MPLAYER_KNL_FLG_THUMBNAIL_DECODE;
                break;
        #endif // #if (!SHOW_PARTIALLY_DECODING_THUMBNAIL)

            case EXIT_VDPLAYER_EXIT:
                MApp_DMP_GetZUIFbAttr(&m_thumbnailFbAttr);
                stThumb.stPhotoImgTo.u32BuffAddr = m_thumbnailFbAttr.addr;
                stThumb.stPhotoImgTo.u16BuffW = m_thumbnailFbAttr.width;
                stThumb.stPhotoImgTo.u16BuffH = m_thumbnailFbAttr.height;
                stThumb.stPhotoImgTo.u8FbFmt = (U8) m_thumbnailFbAttr.fbFmt; // it is because GOP driver, please ask ming-cha
                MPLAYER_DBG(printf("\n [m_thumbnailFbAttr] u32BuffAddr=%lx, u16BuffW=%x , u16BuffH=%x  , fmt=%x \n",m_thumbnailFbAttr.addr,m_thumbnailFbAttr.width, m_thumbnailFbAttr.height ,(U8) m_thumbnailFbAttr.fbFmt));

                MApp_VDPlayer_MovieThumbnail_OutputImage(
                                   &stThumb.stPhotoImgTo,
                                   &stThumb.stPhotoImgFrom);
                MApp_VDPlayer_Stop();
                MApp_VDPlayer_StopPreview();
                // send decode done notification
                notifyThumbnail.u16FileIdx = m_au8ThumbQueue[m_u8ThumbnailNIdx];
                notifyThumbnail.bOK = TRUE;
                NOTIFY(E_MPLAYER_NOTIFY_END_OF_ONE_THUMBNAIL, &notifyThumbnail);
                // decode next file
                m_u8ThumbnailNIdx++;
                m_eMPlayerKnlFlags |= E_MPLAYER_KNL_FLG_THUMBNAIL_INIT;
                break;
            }
        }

        //printf("[Thumb] m_u8ThumbnailNIdx(%d) vs m_u8ThumbQMax(%d)\n", m_u8ThumbnailNIdx, m_u8ThumbQMax);
        if((m_u8ThumbnailNIdx >= m_u8ThumbQMax) ||
           !(m_eMPlayerKnlFlags & E_MPLAYER_KNL_FLG_DECODE_N_THUMBNAIL))
        {
            MApp_VDPlayer_StopThumbnail();
        #if ENABLE_EMBEDDED_PHOTO_DISPLAY
            MApp_MPlayer_StopEmbeddedPhotoDecode();
        #endif
            m_u8ThumbQMax = 0;
            NOTIFY(E_MPLAYER_NOTIFY_END_OF_THUMBNAIL, NULL);
            m_eMPlayerKnlFlags &= (enumMPlayerKnlFlags)~E_MPLAYER_KNL_FLG_DECODE_N_THUMBNAIL;
        }
    }
#endif //#ifdef ZUI

#if ENABLE_HK_MM
    if (MApp_VDPlayer_MediaCodec_IsReady() == TRUE)
    {
        //Movie Normal Play & Preview
        if(MApp_MPlayer_IsMoviePlaying() || m_eMoviePreviewState != E_MOVIE_PREVIEW_NONE)
        {
            if (MApp_MediaCodecTask() == FALSE)
            {
                // MM do nothing now.
            }
        }
    }
#endif
}

void MApp_MPlayer_SetZUIFbAttr(GOP_GwinFBAttr FbAttr)
{
    m_thumbnailFbAttr=FbAttr;
}

//******************************************************************************
/// To set system to standby mode.
/// @return N/A
//******************************************************************************
void MApp_MPlayer_Standby(void)
{
    m_eMPlayerStateMachineState = STATE_MPLAYER_STANDBY;
}

//******************************************************************************
/// Check the input file name is exist in current directory.
/// @param  pString \b IN  Specify the file name.
/// @param  charLen  \b IN Specify the file name length.
/// @return TRUE if input file name is exist.
//******************************************************************************
BOOLEAN MApp_MPlayer_IsFilenameExistInCurrentDirectory(U16* pString,U8 charLen)
{
    return MApp_FilrBrowser_CheckNameExistedInCurrent(pString, charLen);
}

//******************************************************************************
/// Query USB disk total size.
/// @param  u8DriveIndex \b IN  Specify the drive index.
/// @return Total size in KB.
//******************************************************************************
U32 MApp_MPlayer_QueryUsbDiskTotalSizeInKB(U8 u8DriveIndex)
{
    return msAPI_FCtrl_GetTotalSizeInKB_ByDriveIndex(u8DriveIndex);
}

//******************************************************************************
/// Query USB disk unused size.
/// @param  u8DriveIndex \b IN  Specify the drive index.
/// @return Unused size in KB.
//******************************************************************************
U32 MApp_MPlayer_QueryUsbDiskUnusedSizeInKB(U8 u8DriveIndex)
{
#if 0
    return msAPI_FCtrl_GetUnusedSizeInKB_ByDriveIndex(u8DriveIndex);
#else
//Fix DMS01156400 , some fat file system u32FSI_Free_Count = 0xFFFFFFFF
    return msAPI_FCtrl_GetUnusedSizeInKB_ByDriveIndex_New(u8DriveIndex);
#endif
}

//******************************************************************************
/// Query preview state by media type.
/// @param  eType \b IN  Specify the media type.
/// @return Preview state.
//******************************************************************************
U8 MApp_MPlayer_QueryPreviewState(enumMPlayerMediaType eType)
{
    switch(eType)
    {
    #if ENABLE_MPLAYER_PHOTO
        case E_MPLAYER_TYPE_PHOTO:
            return (U8)m_ePhotoPreviewState;
    #endif

    #if ENABLE_MPLAYER_MUSIC
         case E_MPLAYER_TYPE_MUSIC:
            return (U8)m_eMusicPreviewState;
   #endif

   #if ENABLE_MPLAYER_MOVIE
         case E_MPLAYER_TYPE_MOVIE:
            return (U8)m_eMoviePreviewState;
  #endif
  #if ENABLE_MPLAYER_TEXT
         case E_MPLAYER_TYPE_TEXT:
            return (U8)m_eTextPreviewState;
  #endif
        default:
            return (U8)0xff;
    }
}

//******************************************************************************
/// Go to root directory.
/// @return N/A
//******************************************************************************
void MApp_MPlayer_GotoRootDirEntry(void)
{
    MApp_FileBrowser_ChangeToRootDirectory();
#if (HIGH_SPEED_BROWSER)
    m_u16BufDirectoryDepth = MPLAYER_INVALID_INDEX;
#endif
    _MApp_MPlayer_Browser_EnumCurDirectory();
}

//******************************************************************************
/// Go to current directory.
/// @return N/A
//******************************************************************************
void MApp_MPlayer_GotoCurrentDirEntry(void)
{
    _MApp_MPlayer_Change2CurrentDirectory();
#if (HIGH_SPEED_BROWSER)
    m_u16BufDirectoryDepth = MPLAYER_INVALID_INDEX;
#endif
    _MApp_MPlayer_Browser_EnumCurDirectory();
}

//******************************************************************************
/// Query current device index.
/// @return enumMPlayerDeviceType.
//******************************************************************************
enumMPlayerDeviceType MApp_MPlayer_QueryCurrentDeviceIndex(void)
{
    return (enumMPlayerDeviceType)m_u8CurDeviceIdx;
}

//******************************************************************************
/// Query current device connected or not.
/// @return TRUE or FALSE.
//******************************************************************************
BOOLEAN MApp_MPlayer_QueryCurrentDeviceIsConnected(void)
{
    switch(MApp_MPlayer_QueryCurrentDeviceIndex())
    {
        case E_MPLAYER_USB0:
            return msAPI_MSDCtrl_IsDeviceConnected(MSD_PORT_1);
        case E_MPLAYER_USB1:
            return msAPI_MSDCtrl_IsDeviceConnected(MSD_PORT_2);
        case E_MPLAYER_USB2:
            return msAPI_MSDCtrl_IsDeviceConnected(MSD_PORT_3);
        case E_MPLAYER_USB3:
            return msAPI_MSDCtrl_IsDeviceConnected(MSD_PORT_4);
        default:
            return FALSE;
    }
}

//******************************************************************************
/// Query playlist number of specific media type.
/// @param  eType \b IN  Specify the media type.
/// @return playlist number.
//******************************************************************************
U16 MApp_MPlayer_QueryPlayListFileNum(enumMPlayerMediaType eType)
{
    return m_u16SelectedFileNum[eType];
}

//******************************************************************************
/// Remove file from playlist of specific media type.
/// If the remove file be delete, it needs to modify file index and play list order.
/// Otherwise if remove file does not need to delete, it just modify play list order only.
/// @param  eType \b IN  Specify the media type.
/// @param  u16Index \b IN  Specify the file index.
/// @param  bDeleteFile \b IN  Specify removed file be deleted or not.
/// @return enumMPlayerRet.
//******************************************************************************
enumMPlayerRet MApp_MPlayer_RemoveFileFromPlayList(enumMPlayerMediaType eType, U16 u16Index, BOOLEAN bDeleteFile)
{
    U32 u32XdataWindowBase;
    U16 u16PLidx;
    enumMPlayerRet eRet = E_MPLAYER_RET_FAIL;

    if(m_u16SelectedFileNum[eType] <= u16Index)
    {
        goto MApp_MPlayer_RemoveFileFromPlayingList_END;
    }

    if(_MApp_MPlayer_GetPlayListAddressByMediaType(eType, &u32XdataWindowBase)==FALSE)
    {
        goto MApp_MPlayer_RemoveFileFromPlayingList_END;
    }

    MPlayerPlayListInfo *pstPlayListInfo;
    pstPlayListInfo = (MPlayerPlayListInfo *) (_PA2VA(u32XdataWindowBase));
    BOOLEAN bMatched = TRUE;
    U16 u16DirDepth, u16CurDepth = NUM_OF_MAX_DIRECTORY_DEPTH;

    //find file depth.
    for(u16DirDepth=0;u16DirDepth<NUM_OF_MAX_DIRECTORY_DEPTH+1;u16DirDepth++)
    {
        if(PLAY_LIST_PATH(u16Index, u16DirDepth) == MPLAYER_INVALID_INDEX)
        {
            if(u16DirDepth==0)
            {
                u16CurDepth = u16DirDepth;
            }
            else
            {
                u16CurDepth = u16DirDepth-1;
            }
            break;
        }
    }

    for(u16PLidx=u16Index;u16PLidx<m_u16SelectedFileNum[eType]-1;u16PLidx++)
    {
        //msAPI_MIU_Copy(u32XdataWindowBase + ((U32)u16PLidx + 1) * sizeof(MPlayerPlayListInfo),
        //               u32XdataWindowBase + (U32)u16PLidx * sizeof(MPlayerPlayListInfo),
        //               sizeof(MPlayerPlayListInfo),
        //               MIU_SDRAM2SDRAM);
        if(bDeleteFile && bMatched)
        {
            if(u16CurDepth == NUM_OF_MAX_DIRECTORY_DEPTH
            || PLAY_LIST_PATH(u16PLidx+1, u16CurDepth+1)==MPLAYER_INVALID_INDEX)
            {
                //if file depth is same , then it need check the file path is same or not
                for(u16DirDepth=0;u16DirDepth<u16CurDepth;u16DirDepth++)
                {
                    if(PLAY_LIST_PATH(u16PLidx+1, u16DirDepth) != PLAY_LIST_PATH(u16Index, u16DirDepth))
                    {
                        bMatched = FALSE;
                    }
                }
            }
            else
            {
                bMatched = FALSE;
            }

            if(bMatched)
            {
                PLAY_LIST_PATH(u16PLidx+1, u16CurDepth)--;
            }
        }
        memcpy((U8 *)_PA2VA((u32XdataWindowBase + (U32)u16PLidx * sizeof(MPlayerPlayListInfo))),
               (U8 *)_PA2VA((u32XdataWindowBase + ((U32)u16PLidx + 1) * sizeof(MPlayerPlayListInfo))),
               sizeof(MPlayerPlayListInfo));

    }
    m_u16SelectedFileNum[eType]--;

    if ((m_eMediaType == eType) && MApp_MPlayer_IsMediaFileInPlaying())
    {
        enumMPlayerIdx ePlayerIdx = E_MPLAYER_FOREGROUND_PLAYER;
#if ENABLE_MPLAYER_MUSIC
        if (m_eMediaType == E_MPLAYER_TYPE_MUSIC)
        {
            ePlayerIdx = E_MPLAYER_BACKGROUND_PLAYER;
        }
#endif  // #if ENABLE_MPLAYER_MUSIC

        if (u16Index < m_MPlayerInfo[ePlayerIdx].u16PlayingIdx)
        {
            m_MPlayerInfo[ePlayerIdx].u16PlayingIdx --;
#if ENABLE_MPLAYER_PHOTO
            if (m_eMediaType == E_MPLAYER_TYPE_PHOTO)
            {
                if(m_u32PhotoCurrentDisplayedIdx != MPLAYER_INVALID_INDEX)
                {
                     if(u16Index == m_u32PhotoCurrentDisplayedIdx)
                         m_u32PhotoCurrentDisplayedIdx = MPLAYER_INVALID_INDEX;
                     else
                         m_u32PhotoCurrentDisplayedIdx --;
                }
            }
#endif  // #if ENABLE_MPLAYER_PHOTO
        }
    }

    eRet = E_MPLAYER_RET_OK;

MApp_MPlayer_RemoveFileFromPlayingList_END:

    return eRet;
}

#if 0
enumMPlayerRet MApp_MPlayer_QueryFileNameInPlayList(enumMPlayerMediaType eType, U16 u16Index, U8 *pu8FileName, U16 u16BufLen)
{
    MPlayerPlayListInfo *pstPlayListInfo;
    U32 u32XdataWindowBase;
    U8 u8Len;
    enumMPlayerRet eRet=E_MPLAYER_RET_FAIL;
    FileEntry fileEnrty;

    MDrv_Sys_PushXdataWindow1Base();
    pstPlayListInfo = (MPlayerPlayListInfo xdata *)msAPI_MIU_GetW1StartAddress();

    if(u16Index >= m_u16SelectedFileNum[eType])
    {
        goto MApp_MPlayer_QueryPlayListFileNum_END;
    }

    if(_MApp_MPlayer_GetPlayListAddressByMediaType(eType, &u32XdataWindowBase)==FALSE)
    {
        goto MApp_MPlayer_QueryPlayListFileNum_END;
    }

    MDrv_Sys_SetXdataWindow1Base((U16)((u32XdataWindowBase +
                                        (U32)u16Index * sizeof(MPlayerPlayListInfo)) >> 12));
    memcpy(&fileEnrty, &PLAY_LIST_FILE_ENTRY(u16Index), sizeof(FileEntry));


    // Get long file name from file entry.
    u8Len = MApp_FileBrowser_GetLongFileNameByFileEntry(
                &fileEnrty,
                (U32)(&pu8FileName[0]),
                (u16BufLen/2-1));
    u8Len = (u8Len > (u16BufLen/2-1)) ? u16BufLen/2-1 : u8Len;
    pu8FileName[u8Len*2] = 0;
    pu8FileName[u8Len*2+1] = 0;
    eRet = E_MPLAYER_RET_OK;

MApp_MPlayer_QueryPlayListFileNum_END:

    return eRet;
}
#endif

//******************************************************************************
/// Query file name of current playing file.
/// @param  pu8LongFilename \b OUT  Specify the buffer for logn file name.
/// @return enumMPlayerRet.
//******************************************************************************
enumMPlayerRet MApp_MPlayer_QueryCurrentPlayingFileName(U8 *pu8LongFilename)
{
    MPlayerFileInfo stFileInfo;
    U16 u16QueryIdx=MPLAYER_INVALID_INDEX;
    enumMPlayerRet eRet = E_MPLAYER_RET_FAIL;

    switch(m_eMediaType)
    {
#if ENABLE_MPLAYER_PHOTO
        case E_MPLAYER_TYPE_PHOTO:
            if(m_ePlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY ||
                m_ePlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT)
            {
                u16QueryIdx = (U16)m_u32PhotoCurrentDisplayedIdx;
            }
            else if((m_ePlayMode == E_MPLAYER_PLAY_SELECTED) || (m_ePlayMode == E_MPLAYER_PLAY_SELECTED_FROM_CURRENT))
            {
                u16QueryIdx = (U16)m_u32PhotoCurrentDisplayedIdx;
            }
            break;
#endif

#if ENABLE_MPLAYER_MOVIE
        case E_MPLAYER_TYPE_MOVIE:
            if(m_ePlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY ||
                m_ePlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT)
            {
                u16QueryIdx = m_MPlayerInfo[0].u16PlayingIdx;
            }
            else if((m_ePlayMode == E_MPLAYER_PLAY_SELECTED) || (m_ePlayMode == E_MPLAYER_PLAY_SELECTED_FROM_CURRENT))
            {
                u16QueryIdx = MApp_MPlayer_QueryCurrentPlayingListFileIndex();
            }
            break;
#endif

#if ENABLE_MPLAYER_MUSIC
        case E_MPLAYER_TYPE_MUSIC:
            if(m_ePlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY ||
                m_ePlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT)
            {
                u16QueryIdx = m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].u16PlayingIdx;
            }
            else if((m_ePlayMode == E_MPLAYER_PLAY_SELECTED) || (m_ePlayMode == E_MPLAYER_PLAY_SELECTED_FROM_CURRENT))
            {
                u16QueryIdx = MApp_MPlayer_QueryCurrentPlayingListFileIndex();
            }
            break;
#endif
        default:
            return E_MPLAYER_RET_FAIL;
    }

    if(m_ePlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY ||
        m_ePlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT)
    {
        eRet = MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16QueryIdx, &stFileInfo);
        memcpy(pu8LongFilename, stFileInfo.u8LongFileName, FILE_INFO_LONG_FILENAME_SIZE);
    }
    else if((m_ePlayMode == E_MPLAYER_PLAY_SELECTED) || (m_ePlayMode == E_MPLAYER_PLAY_SELECTED_FROM_CURRENT))
    {
        U8 u8Len = 0;
        if(MApp_MPlayer_QueryLongFilenameByPlayingIdx(MApp_MPlayer_QueryCurrentPlayingList(), pu8LongFilename, u8Len))
        {
            eRet = E_MPLAYER_RET_OK;
        }
    }

    if(eRet != E_MPLAYER_RET_OK)
    {
        MPLAYER_DBG(printf("[Error] Query file info failed!\n"));
    }

    return eRet;
}

#if(STORE_SUBTITLE_ENTRY_TO_SUBTITLE_BUFFER || ENABLE_BGM) //fix compile error
static void _MApp_MPlayer_GetLongFileName(MPlayerFileInfo *pFileInfo)
{
    if(!pFileInfo->bLongFileNameValid)
    {
        U8 u8Len;
        U8 u8FileName[FILE_INFO_LONG_FILENAME_SIZE];

        // Get long file name from file entry.
        u8Len = MApp_FileBrowser_GetLongFileNameByFileEntry(
                        &pFileInfo->fileEntry,
                        (U32)(&u8FileName[0]),
                        (FILE_INFO_LONG_FILENAME_SIZE/2-1));
        u8Len = (u8Len > (FILE_INFO_LONG_FILENAME_SIZE/2-1)) ?
                        FILE_INFO_LONG_FILENAME_SIZE/2-1:
                        u8Len;
        u8FileName[u8Len*2] = 0;
        u8FileName[u8Len*2+1] = 0;
        memcpy(&pFileInfo->u8LongFileName[0], &u8FileName[0], FILE_INFO_LONG_FILENAME_SIZE);
        pFileInfo->bLongFileNameValid = TRUE;
    }
}
#endif

#if (ENABLE_MPLAYER_SORT)
static BOOLEAN Strcmp_Unicode_Less(U16 *src, U16 *dst, U16 len)
{
    U16 i;

    for (i = 0; i < len; i++)
    {
        if (src[i] < dst[i])
        {
            return TRUE;
        }
        else if (src[i] > dst[i])
        {
            return FALSE;
        }
    }
    return FALSE;
}

//******************************************************************************
/// Compare src name with dst name.
/// @param  src \b IN  Specify the pointer of source file information.
/// @param  dst \b IN  Specify the pointer of destination file information.
/// @return Is src name less than dst name.
//******************************************************************************
static BOOLEAN _MApp_MPlayer_FileInfoCmpByName_Less(MPlayerFileInfo *src, MPlayerFileInfo *dst)
{
    if(src == NULL || dst == NULL)
    {
        MPLAYER_DBG(printf("_MApp_MPlayer_FileInfoCmpByName_Less Failed\n"));
        ASSERT(0);
    }

    return Strcmp_Unicode_Less((U16 *)(void *)src->u8LongFileName, (U16 *)(void *)dst->u8LongFileName, FILE_INFO_LONG_FILENAME_SIZE / 2);
}

//******************************************************************************
/// Sort files by MPlayerFileInfo.
/// @param  u32PhyBuffAddr \b IN  Specify physical buffer address.
/// @param  u16StartIdx \b IN  Specify index of first file to be sorted.
/// @param  u16FileNum \b IN  Specify the number of files to be sorted.
/// @param  pfCompareLess \b IN  Specify compare function.
/// @param  bIncrement \b IN  Specify Ascending or Descending.
/// @return void
//******************************************************************************
static void _MApp_MPlayer_HeapSort(U32 u32PhyBuffAddr, U16 u16StartIdx, U16 u16FileNum, PF_FILEINFOCMP_LESS pfCompareLess, BOOLEAN bIncrement)
{
    if(pfCompareLess == NULL)
    {
        return;
    }

    U16 i, u16CurIdx, u16ParentIdx;
    U32 u32BuffAddr = _PA2VA(u32PhyBuffAddr);
    MPlayerFileInfo stTempFileInfo;
    #define HEAP(index) ((MPlayerFileInfo *)(u32BuffAddr+(u16StartIdx+index-1)*sizeof(MPlayerFileInfo)))

    //Create heap tree
    for(i=1; i<=u16FileNum; i++)
    {
        u16CurIdx = i;
        u16ParentIdx = i / 2;
        while(u16CurIdx >= 2
        && pfCompareLess(HEAP(u16ParentIdx), HEAP(u16CurIdx))==bIncrement)
        {
            memcpy(&stTempFileInfo,     HEAP(u16CurIdx),    sizeof(MPlayerFileInfo));
            memcpy(HEAP(u16CurIdx),     HEAP(u16ParentIdx), sizeof(MPlayerFileInfo));
            memcpy(HEAP(u16ParentIdx),  &stTempFileInfo,    sizeof(MPlayerFileInfo));
            u16CurIdx = u16ParentIdx;
            u16ParentIdx = u16CurIdx / 2;
        }
    }

    //Heap sort
    U16 u16FileCnt = u16FileNum;
    while(u16FileCnt > 1)
    {
        memcpy(&stTempFileInfo,     HEAP(1),            sizeof(MPlayerFileInfo));
        memcpy(HEAP(1),             HEAP(u16FileCnt),   sizeof(MPlayerFileInfo));
        memcpy(HEAP(u16FileCnt),    &stTempFileInfo,    sizeof(MPlayerFileInfo));
        u16FileCnt--;

        u16ParentIdx = 1;
        u16CurIdx = 2 * u16ParentIdx;

        while(u16CurIdx <= u16FileCnt)
        {
            if(u16CurIdx < u16FileCnt
            && pfCompareLess(HEAP(u16CurIdx), HEAP(u16CurIdx+1))==bIncrement)
            {
                u16CurIdx++;
            }
            if(pfCompareLess(HEAP(u16ParentIdx), HEAP(u16CurIdx))==(!bIncrement))
            {
                break;
            }
            memcpy(&stTempFileInfo,     HEAP(u16CurIdx),    sizeof(MPlayerFileInfo));
            memcpy(HEAP(u16CurIdx),     HEAP(u16ParentIdx), sizeof(MPlayerFileInfo));
            memcpy(HEAP(u16ParentIdx),  &stTempFileInfo,    sizeof(MPlayerFileInfo));
            u16ParentIdx = u16CurIdx;
            u16CurIdx = 2 * u16ParentIdx;
        }
    }
}

static U16 _MApp_MPlayer_LookupPhysicalIndex(U16 u16Idx)
{
    U32 u32Addr;
    MPlayerFileInfo *pFileInfo;

    u32Addr = (U32)((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR)) + (U32)(u16Idx)*sizeof(MPlayerFileInfo);

    pFileInfo = (MPlayerFileInfo *)_PA2VA(u32Addr);
    u16Idx = pFileInfo->u16PhyIndex;

    return u16Idx;
}

#if ENABLE_MPLAYER_SORT_EX
//******************************************************************************
/// Compare src physical index with dst physical index.
/// @param  src \b IN  Specify the pointer of source file information.
/// @param  dst \b IN  Specify the pointer of destination file information.
/// @return Is src time less than dst time.
//******************************************************************************
static BOOLEAN _MApp_MPlayer_FileInfoCmpByPhyIndex_Less(MPlayerFileInfo *src, MPlayerFileInfo *dst)
{
    if(src == NULL || dst == NULL)
    {
        MPLAYER_DBG(printf("_MApp_MPlayer_FileInfoCmpByPhyIndex_Less Failed\n"));
        ASSERT(0);
    }

    if(src->u16PhyIndex < dst->u16PhyIndex)
        return TRUE;
    else
        return FALSE;
}

//******************************************************************************
/// Compare src time with dst time.
/// @param  src \b IN  Specify the pointer of source file information.
/// @param  dst \b IN  Specify the pointer of destination file information.
/// @return Is src time less than dst time.
//******************************************************************************
static BOOLEAN _MApp_MPlayer_FileInfoCmpByTime_Less(MPlayerFileInfo *src, MPlayerFileInfo *dst)
{
    if(src == NULL || dst == NULL)
    {
        MPLAYER_DBG(printf("_MApp_MPlayer_FileInfoCmpByTime_Less Failed\n"));
        ASSERT(0);
    }

    if(src->u16Year < dst->u16Year)
        return TRUE;
    else if(src->u16Year > dst->u16Year)
        return FALSE;

    if(src->u8Month < dst->u8Month)
        return TRUE;
    else if(src->u8Month > dst->u8Month)
        return FALSE;

    if(src->u8Day < dst->u8Day)
        return TRUE;
    else if(src->u8Day > dst->u8Day)
        return FALSE;

    if(src->u8Hour < dst->u8Hour)
        return TRUE;
    else if(src->u8Hour > dst->u8Hour)
        return FALSE;

    if(src->u8Minute < dst->u8Minute)
        return TRUE;
    else if(src->u8Minute > dst->u8Minute)
        return FALSE;

    if(src->u8Second < dst->u8Second)
        return TRUE;
    else
        return FALSE;
}

//******************************************************************************
/// Resort + filter files by media type and move to file buffer.
/// @param  eSortMode \b IN  Specify the file sorting mode.
/// @param  eOrderMode \b IN  Specify the order mode of file sorting.
/// @return
//******************************************************************************
void MApp_MPlayer_ReSortFileBrowser(enumMPlayerFileSortMode eSortMode, enumMPlayerFileSortSubMode eOrderMode)
{
    //U16 u16FileIdx;
    if(eSortMode == m_eFileSortingMode)
    {
        if(eSortMode == E_MPLAYER_SORT_NONE
        || eOrderMode == m_eFileSortingOrderMode)
        {
            return;
        }
    }

    _MApp_MPlayer_SetFileSortingMode(eSortMode);
    _MApp_MPlayer_SetFileSortingOrderMode(eOrderMode);

    _MApp_MPlayer_SortDirAndMove_EX(m_u16BufDirectoryNum);
    _MApp_MPlayer_SortFileAndMove_EX(m_u16BufDirectoryNum, m_u16BufTotalFileNum);
}

enumMPlayerFileSortMode MApp_MPlayer_QueryCurrentFileSortingMode()
{
    return m_eFileSortingMode;
}

enumMPlayerFileSortSubMode MApp_MPlayer_QueryCurrentFileSortingOrderMode()
{
    return m_eFileSortingOrderMode;
}

//******************************************************************************
/// Set the file sorting mode and file info compare function.
/// @param  eSortMode \b IN  Specify the file sorting mode.
/// @return
//******************************************************************************
static void _MApp_MPlayer_SetFileSortingMode(enumMPlayerFileSortMode eSortMode)
{
    m_eFileSortingMode = eSortMode;

    switch(m_eFileSortingMode)
    {
        case E_MPLAYER_SORT_NONE:
            m_pfFileInfoCmp_Less = _MApp_MPlayer_FileInfoCmpByPhyIndex_Less;
            break;

        case E_MPLAYER_SORT_BY_NAME:
            m_pfFileInfoCmp_Less = _MApp_MPlayer_FileInfoCmpByName_Less;
            break;

        case E_MPLAYER_SORT_BY_TIME:
            m_pfFileInfoCmp_Less = _MApp_MPlayer_FileInfoCmpByTime_Less;
            break;

        default:
            //something error
            break;
    }
}

//******************************************************************************
/// Set the order mode of file sorting.
/// @param  eOrderMode \b IN  Specify the order mode of file sorting.
/// @return
//******************************************************************************
static void _MApp_MPlayer_SetFileSortingOrderMode(enumMPlayerFileSortSubMode eOrderMode)
{
    m_eFileSortingOrderMode = eOrderMode;
}

//******************************************************************************
/// Sort directory and move to File buffer.
/// @param  u16DirCnt \b IN  Specify the directory count.
/// @return Sorted directory count.
//******************************************************************************
static void _MApp_MPlayer_SortDirAndMove_EX(U16 u16DirCnt)
{
    BOOLEAN bIncrement = TRUE;
    U16 u16StartIdx=0;
    U32 u32PhyBuffAddr = ((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR));
    MPlayerFileInfo *pFileInfo;

    //if folder only has "." and ".." no need to sort.
    if(u16DirCnt <= 2)
        return;

    if(m_eFileSortingMode >= E_MPLAYER_SORT_TYPE_NUM
    || m_pfFileInfoCmp_Less == NULL)
    {
        //something error
        _MApp_MPlayer_SetFileSortingMode(E_MPLAYER_SORT_NONE);
    }

    if(m_eFileSortingOrderMode == E_MPLAYER_SORT_DECREASING_ORDER
    && m_eFileSortingMode != E_MPLAYER_SORT_NONE)
    {
        bIncrement = FALSE;
    }

    pFileInfo = (MPlayerFileInfo *)_PA2VA(u32PhyBuffAddr);

    if(pFileInfo->fileEntry.EntryType == ENTRY_TYPE_DIR_DOT)
    {
        u16StartIdx++;
        pFileInfo++;
        if(pFileInfo->fileEntry.EntryType == ENTRY_TYPE_DIR_DOTDOT)
        {
            u16StartIdx++;
        }
    }
    else if(pFileInfo->fileEntry.EntryType == ENTRY_TYPE_DIR_DOTDOT)
    {
        u16StartIdx++;
    }
    _MApp_MPlayer_HeapSort(u32PhyBuffAddr, u16StartIdx, u16DirCnt-u16StartIdx, m_pfFileInfoCmp_Less, bIncrement);
}

//******************************************************************************
/// Filter + Sort files by media type and move to File buffer.
/// @param  u16DirCnt \b IN  Specify the directory count.
/// @param  u16TotalCnt \b IN  Specify the total file count.
/// @return filtered + Sorted files count.
//******************************************************************************
static U16 _MApp_MPlayer_SortFileAndMove_EX(U16 u16DirCnt, U16 u16TotalCnt)
{
    BOOLEAN bIncrement = TRUE;
    U32 u32PhyBuffAddr = ((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR));
    U16 u16MediaFileNum = u16TotalCnt - u16DirCnt;

    if(m_eFileSortingMode >= E_MPLAYER_SORT_TYPE_NUM
    || m_pfFileInfoCmp_Less == NULL)
    {
        //something error
        _MApp_MPlayer_SetFileSortingMode(E_MPLAYER_SORT_NONE);
    }

    if(m_eFileSortingOrderMode == E_MPLAYER_SORT_DECREASING_ORDER
    && m_eFileSortingMode != E_MPLAYER_SORT_NONE)
    {
        bIncrement = FALSE;
    }
    _MApp_MPlayer_HeapSort(u32PhyBuffAddr, u16DirCnt, u16MediaFileNum, m_pfFileInfoCmp_Less, bIncrement);

    return u16MediaFileNum;
}
#else
static void _MApp_MPlayer_SortDirAndMove(U16 u16DirCnt)
{
    U16 u16StartIdx=0;
    U32 u32PhyBuffAddr = ((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR));
    MPlayerFileInfo *pFileInfo;

    //if folder only has "." and ".." no need to sort.
    if(u16DirCnt <= 2)
        return;

    pFileInfo = (MPlayerFileInfo *)_PA2VA(u32PhyBuffAddr);

    if(pFileInfo->fileEntry.EntryType == ENTRY_TYPE_DIR_DOT)
    {
        u16StartIdx++;
        pFileInfo++;
        if(pFileInfo->fileEntry.EntryType == ENTRY_TYPE_DIR_DOTDOT)
        {
            u16StartIdx++;
        }
    }
    else if(pFileInfo->fileEntry.EntryType == ENTRY_TYPE_DIR_DOTDOT)
    {
        u16StartIdx++;
    }
    _MApp_MPlayer_HeapSort(u32PhyBuffAddr, u16StartIdx, u16DirCnt-u16StartIdx, _MApp_MPlayer_FileInfoCmpByName_Less, TRUE);
}

static U16 _MApp_MPlayer_SortFileAndMove(U16 u16DirCnt, U16 u16TotalCnt)
{
    U32 u32PhyBuffAddr = ((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR));
    U16 u16MediaFileNum = u16TotalCnt - u16DirCnt;

    _MApp_MPlayer_HeapSort(u32PhyBuffAddr, u16DirCnt, u16MediaFileNum, _MApp_MPlayer_FileInfoCmpByName_Less, TRUE);

    return u16MediaFileNum;
}
#endif //ENABLE_MPLAYER_SORT_EX
#endif //ENABLE_MPLAYER_SORT

#ifdef ENABLE_PTP

static BOOLEAN _MApp_MPlayer_PTP_PlayerInit(enumMPlayerIdx eMPlayerIdx, enumMPlayerMediaType eMediaType, BOOLEAN bPreview)
{
    U16 u16TotalFileNumber = m_u16TotalFileNum;

    bPreview = bPreview;
    if (eMPlayerIdx == E_MPLAYER_FOREGROUND_PLAYER)
    {
        m_MPlayerInfo[eMPlayerIdx].eKnlFlag1 &= (enumMPlayerKnlFlags1)~(0
          #if ENABLE_MPLAYER_PHOTO
            | E_MPLAYER_KNL_FLG1_PHOTO_PLAY
          #endif  // #if ENABLE_MPLAYER_PHOTO
          #if ENABLE_MPLAYER_MOVIE
            | E_MPLAYER_KNL_FLG1_MOVIE_PLAY
          #endif  // #if ENABLE_MPLAYER_MOVIE
          #if ENABLE_MPLAYER_TEXT
            | E_MPLAYER_KNL_FLG1_TEXT_PLAY
          #endif  // #if ENABLE_MPLAYER_TEXT
            );
    }

    m_MPlayerInfo[eMPlayerIdx].eMediaType = eMediaType;
    m_MPlayerInfo[eMPlayerIdx].eMediaSubType = E_MPLAYER_SUBTYPE_INVALID;
    m_MPlayerInfo[eMPlayerIdx].eRepeatMode = m_eRepeatMode[eMPlayerIdx];
#if RANDOM_PLAY
    m_MPlayerInfo[eMPlayerIdx].eRandomMode = m_eRandomMode[eMPlayerIdx];
#endif
    m_MPlayerInfo[eMPlayerIdx].ePlayMode = m_ePlayMode;

    if (m_ePlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT)
    {
        m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx = m_u16CurFileIdx;
    }
    else if (m_ePlayMode == E_MPLAYER_PLAY_SELECTED_FROM_CURRENT)
    {
        if (_MApp_MPlayer_Browser_IsInPlayingList(eMediaType, MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY)))
            m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx = _MApp_MPlayer_Browser_QueryPlayingList(eMediaType, MApp_MPlayer_QueryCurrentFileIndex(E_MPLAYER_INDEX_CURRENT_DIRECTORY));
        else
            m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx = 0;
    }
    else
    {
        m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx = 0;
    }

    m_MPlayerInfo[eMPlayerIdx].u16TotalFileNum = u16TotalFileNumber; // directories are included
    m_MPlayerInfo[eMPlayerIdx].u16TotalDirNum = m_u16DirectoryNum[m_u16CurDirectoryDepth];

    return TRUE;
}

static void _MApp_MPlayer_PTP_Browser_SaveCurFileInfo(tPTPOBJECTINFO *ptObjectInfo, U16 u16FileIdx)
{
    MPlayerFileInfo fileInfo;
    MPlayerFileInfo *pFileInfo;
    PTPFileEntry *pPTPFileEntry;
    U32 u32Addr;
    U8 *ptr;

    memset(&fileInfo, 0, sizeof(MPlayerFileInfo));

    // Save file entry for file name.
    memcpy(&fileInfo.u8LongFileName[0], (U8 *)&ptObjectInfo->pObjectInfo->Filename[0], 26);
    if (msAPI_PTP_IsDirectory(ptObjectInfo->pObjectInfo->ObjectFormat))
    {
        memset(fileInfo.u8ExtFileName, ' ', 3);
        fileInfo.u8ExtFileName[3] = 0;
        fileInfo.eAttribute = E_MPLAYER_FILE_DIRECTORY;
    }
    else
    {
        ptr = (U8 *)&ptObjectInfo->pObjectInfo->Filename[9];
        fileInfo.u8ExtFileName[0] = ptr[1];
        fileInfo.u8ExtFileName[1] = ptr[3];
        fileInfo.u8ExtFileName[2] = ptr[5];
        fileInfo.u8ExtFileName[3] = 0;

    fileInfo.eAttribute = E_MPLAYER_FILE_RDONLY;
    }
    fileInfo.u32FileSize = ptObjectInfo->pObjectInfo->ObjectCompressedSize;
    // date ??

    fileInfo.bLongFileNameValid = TRUE;

    pPTPFileEntry = (PTPFileEntry *)&fileInfo.fileEntry;
    pPTPFileEntry->u8UsbPort = msAPI_PTP_QueryCurrentUsbPort();
    pPTPFileEntry->u32ObjectHandle = ptObjectInfo->u32ObjectHandle;
    pPTPFileEntry->u32ParentObjectHandle = ptObjectInfo->pObjectInfo->ParentObject;
    pPTPFileEntry->u32ObjectSize = ptObjectInfo->pObjectInfo->ObjectCompressedSize;
    pPTPFileEntry->u32ThumbSize = ptObjectInfo->pObjectInfo->ThumbCompressedSize;

    u32Addr = (U32)((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR)) + (U32)u16FileIdx * sizeof(MPlayerFileInfo);

    pFileInfo = (MPlayerFileInfo *)_PA2VA((void *)u32Addr);
    memcpy(pFileInfo, &fileInfo, sizeof(MPlayerFileInfo));

}

static void _MApp_MPlayer_PTP_Browser_SaveDotFileInfo(tPTPOBJECTINFO *ptObjectInfo, U16 u16FileIdx, U8 u8Type)
{
    MPlayerFileInfo fileInfo;
    MPlayerFileInfo *pFileInfo;
    PTPFileEntry *pPTPFileEntry;

    U16 *pu16Buf;
    U32 u32Addr;

    ptObjectInfo = ptObjectInfo;
    memset(&fileInfo, 0, sizeof(FileEntry));
    pu16Buf = (U16 *)&fileInfo.u8LongFileName[0];

    if (u8Type)
    {
        pu16Buf[0] = '.';
        pu16Buf[1] = '.';
        pu16Buf[2] = 0x0;
    }
    else
    {
        pu16Buf[0] = '.';
        pu16Buf[1] = 0x0;
    }

    fileInfo.eAttribute = E_MPLAYER_FILE_DIRECTORY;
    fileInfo.bLongFileNameValid = TRUE;

    u32Addr = (U32)((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR)) + (U32)u16FileIdx * sizeof(MPlayerFileInfo);

    pFileInfo = (MPlayerFileInfo *)_PA2VA((void *)u32Addr);
    memcpy(pFileInfo, &fileInfo, sizeof(MPlayerFileInfo));

    pPTPFileEntry = (PTPFileEntry *)&fileInfo.fileEntry;
    pPTPFileEntry->u8UsbPort = msAPI_PTP_QueryCurrentUsbPort();
    pPTPFileEntry->u32ParentObjectHandle = msAPI_PTP_QueryParentHandle(m_u16CurDirectoryDepth);

}

static void _MApp_MPlayer_PTP_Browser_EnumCurDirectory()
{
    U16 u16ObjectNum;
    tPTPOBJECTINFO tObjectInfo;
    PTP_OBJECTINFO *pObjectInfo;
    U16 u16FileIdx;
    U16 u16DirCnt;
    U16 u16FileCnt, u16MediaFileCnt;
    U32 u32Addr;
    MPlayerFileInfo fileInfo, *pFileInfo;
    BOOLEAN bNeedRead = FALSE;
    enumMPlayerMediaType eMediaType = MApp_MPlayer_QueryCurrentMediaType();
    #define extName     pFileInfo->u8ExtFileName

    // 0: Check whether change directory
    if (m_u16BufDirectoryDepth != m_u16CurDirectoryDepth)
    {
        bNeedRead = TRUE;
    }
    else
    {
        for (u16DirCnt = 0; u16DirCnt < m_u16CurDirectoryDepth; u16DirCnt++)
        {
            if (m_u16BufDirectory[u16DirCnt] != m_u16CurDirectory[u16DirCnt])
            {
                bNeedRead = TRUE;
            }
        }
    }

    if (bNeedRead)
    {
        U32 u32ObjectHandle;
        U8 u8Port = msAPI_PTP_QueryCurrentUsbPort();
        U32 u32CurrentHandle = msAPI_PTP_QueryCurrentHandle();

        // 1. Read all PTP object.
        u16ObjectNum = msAPI_PTP_GetObjectHandles(u8Port, 0x0, msAPI_PTP_QueryCurrentHandle());

        m_u16BufTotalFileNum = 0;

        u16FileCnt = 0;
        u16DirCnt = 0;

        // Add dummy dot or dotdot directory
        _MApp_MPlayer_PTP_Browser_SaveDotFileInfo(NULL, u16DirCnt + NUM_OF_MAX_FILES_PER_DIRECTORY, 0);
        u16DirCnt++;
        if (m_u16CurDirectoryDepth)
        {
            _MApp_MPlayer_PTP_Browser_SaveDotFileInfo(NULL, u16DirCnt + NUM_OF_MAX_FILES_PER_DIRECTORY, 1);
            u16DirCnt++;
        }

        while ((m_u16BufTotalFileNum < u16ObjectNum) && (m_u16BufTotalFileNum < NUM_OF_MAX_FILES_PER_DIRECTORY))
        {
            u32ObjectHandle = msAPI_PTP_GetObjectHandleByIndex(u8Port, m_u16BufTotalFileNum);
            pObjectInfo = msAPI_PTP_GetObjectInfo(u8Port, u32ObjectHandle);
            if (pObjectInfo)
            {
                tObjectInfo.u32ObjectHandle = u32ObjectHandle;
                tObjectInfo.pObjectInfo = pObjectInfo;

                if (pObjectInfo->ParentObject == u32CurrentHandle)
                {
                    if (msAPI_PTP_IsDirectory(pObjectInfo->ObjectFormat))
                    {
                        _MApp_MPlayer_PTP_Browser_SaveCurFileInfo(&tObjectInfo, u16DirCnt + NUM_OF_MAX_FILES_PER_DIRECTORY);
                        u16DirCnt++;
                    }
                    else
                    {
                        _MApp_MPlayer_PTP_Browser_SaveCurFileInfo(&tObjectInfo, u16FileCnt);
                        u16FileCnt++;
                    }
                }
            }
            else
            {
                if (msAPI_PTP_GetError(u8Port))
                {
                    //printf("PTP error\n");
                    break;
                }
            }
            m_u16BufTotalFileNum++;
            msAPI_Timer_ResetWDT();
        }
        m_u16DirectoryNum[m_u16CurDirectoryDepth] = u16DirCnt;
        m_u16BufDirectoryNum = u16DirCnt;
        m_u16BufTotalFileNum = u16DirCnt + u16FileCnt;
        //printf("%u %u %u\n", u16DirCnt, u16FileCnt, m_u16BufTotalFileNum);
        msAPI_PTP_SetParentHandle(m_u16CurDirectoryDepth, msAPI_PTP_QueryCurrentHandle());

        msAPI_MIU_Copy((U32)((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR)),
                       (U32)((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR)) +
                       ((U32)u16DirCnt + (U32)NUM_OF_MAX_FILES_PER_DIRECTORY) * sizeof(MPlayerFileInfo),
                       (U32)sizeof(MPlayerFileInfo) * u16FileCnt,
                       MIU_SDRAM2SDRAM);

        // Copy directories.
        msAPI_MIU_Copy((U32)((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR)) +
                       (U32)NUM_OF_MAX_FILES_PER_DIRECTORY * sizeof(MPlayerFileInfo),
                       (U32)((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR)),
                       (U32)sizeof(MPlayerFileInfo) * u16DirCnt,
                       MIU_SDRAM2SDRAM);

        m_u16BufDirectoryDepth = m_u16CurDirectoryDepth;
        for (u16DirCnt = 0; u16DirCnt < m_u16CurDirectoryDepth; u16DirCnt++)
        {
            m_u16BufDirectory[u16DirCnt] = m_u16CurDirectory[u16DirCnt];
        }
        m_u16BufDirectory[m_u16CurDirectoryDepth] = MPLAYER_INVALID_INDEX;
    }

    // Enumerate files.
    u16MediaFileCnt = 0;
    for (u16FileIdx = 0; u16FileIdx < (m_u16BufTotalFileNum - m_u16BufDirectoryNum); u16FileIdx++)
    {
        u32Addr = (U32)((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR)) +
                  (U32)(u16FileIdx + NUM_OF_MAX_FILES_PER_DIRECTORY + m_u16BufDirectoryNum) * sizeof(MPlayerFileInfo);
        pFileInfo = (MPlayerFileInfo *)_PA2VA((void *)u32Addr);

        if ( 0
          #if ENABLE_MPLAYER_PHOTO
           || ((eMediaType == E_MPLAYER_TYPE_PHOTO) && IS_PHOTO_FILE(extName))
          #endif
//          #if ENABLE_MPLAYER_MUSIC
//           || ((eMediaType == E_MPLAYER_TYPE_MUSIC) && IS_MUSIC_FILE(extName))
//          #endif  // #if ENABLE_MPLAYER_MUSIC
        )
        {
            memcpy(&fileInfo, pFileInfo, sizeof(MPlayerFileInfo));

            u32Addr = (U32)((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR)) + (U32)(u16MediaFileCnt + m_u16BufDirectoryNum) * sizeof(MPlayerFileInfo);

            pFileInfo = (MPlayerFileInfo *)_PA2VA((void *)u32Addr);

            memcpy(pFileInfo, &fileInfo, sizeof(MPlayerFileInfo));
            pFileInfo->bLongFileNameValid = TRUE;
            u16MediaFileCnt++;
        }

        msAPI_Timer_ResetWDT();
    }
    m_u16DirectoryNum[m_u16CurDirectoryDepth] = m_u16BufDirectoryNum;
    m_u16TotalFileNum = u16MediaFileCnt + m_u16BufDirectoryNum;
    m_u16BufReadLongNameIdx = 0;

    // Set selected files.
    for (u16FileIdx = m_u16BufDirectoryNum; u16FileIdx < m_u16TotalFileNum; u16FileIdx++)
    {
        if (_MApp_MPlayer_Browser_IsInPlayingList(eMediaType, u16FileIdx))
        {
            _MApp_MPlayer_Browser_SetSelected(u16FileIdx, TRUE);
        }
        msAPI_Timer_ResetWDT();
    }

    MPLAYER_DBG(printf("m_u16TotalFileNum = %x\n", m_u16TotalFileNum));
}

enumMPlayerRet MApp_MPlayer_PTP_EnterDirectory(enumMPlayerFileIndexBegin eBegin, U16 u16Idx)
{
    MPlayerFileInfo fileInfo, *pFileInfo;
    U32 u32Addr;

    if(eBegin == E_MPLAYER_INDEX_CURRENT_PAGE)
    {
        u16Idx += m_u16CurPage1stFileIdx;
    }
    else if(eBegin != E_MPLAYER_INDEX_CURRENT_DIRECTORY)
    {
        return E_MPLAYER_RET_FAIL;
    }

    u32Addr = (U32)((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR)) + (U32)(u16Idx)*sizeof(MPlayerFileInfo);
    pFileInfo = (MPlayerFileInfo *)_PA2VA((void *)u32Addr);
    memcpy(&fileInfo, pFileInfo, sizeof(MPlayerFileInfo));

    if (MApp_UiMediaPlayer_IsDot(&fileInfo.u8LongFileName[0]) == FALSE)
    {
        BOOLEAN bPop = FALSE;

        if (MApp_UiMediaPlayer_IsDotDot(&fileInfo.u8LongFileName[0]) == TRUE)
        {
            m_u16CurDirectoryDepth--;
            m_u16CurDirectory[m_u16CurDirectoryDepth] = MPLAYER_INVALID_INDEX;
            bPop = TRUE;
            {
                PTPFileEntry *pPTPFileEntry;

                pPTPFileEntry = (PTPFileEntry *)&fileInfo.fileEntry;
                msAPI_PTP_SetCurrentHandle(msAPI_PTP_QueryParentHandle(m_u16CurDirectoryDepth));
            }
        }
        else
        {
            m_u16CurDirectoryDepth++;
            {
                PTPFileEntry *pPTPFileEntry;

                pPTPFileEntry = (PTPFileEntry *)&fileInfo.fileEntry;
                msAPI_PTP_SetParentHandle(m_u16CurDirectoryDepth, msAPI_PTP_QueryCurrentHandle());
                msAPI_PTP_SetCurrentHandle(pPTPFileEntry->u32ObjectHandle);
            }
        }

        if(m_u16CurDirectoryDepth <= NUM_OF_MAX_DIRECTORY_DEPTH)
        {
            if (!bPop)
            {
                m_u16CurDirectory[m_u16CurDirectoryDepth-1] = m_u16CurFileIdx;
            }

            if(fileInfo.eAttribute & E_MPLAYER_FILE_DIRECTORY)
            {
                MApp_MPlayer_RecordPath(bPop);
                //MApp_FileBrowser_EnterDirectory(0);
            }
            m_u16DirectoryNum[m_u16CurDirectoryDepth] = 0;
            m_u16CurFileIdx = 0;

        #if (ENABLE_SELECT_FILE_ACROSS_DIRECTORY == 0)
            //In BGM mode or Copy mode no need clear playlist.
            if(m_bIsCopyMode == FALSE
        #if PLAYLIST_BGM
            &&  m_bBGMPlaylistInit == FALSE
        #endif
            )
            {
                memset(m_u16SelectedFileNum, 0, sizeof(m_u16SelectedFileNum));
            }
        #endif

            _MApp_MPlayer_PTP_Browser_EnumCurDirectory();

            m_u16CurPage1stFileIdx = 0;
            m_u16CurPageIdx =0;
            if(m_u16TotalFileNum && m_u16FilesPerPage>0)
            {
                m_u16TotalPageNum = (m_u16TotalFileNum+m_u16FilesPerPage-1) / m_u16FilesPerPage;
            }
            else
            {
                return E_MPLAYER_RET_FAIL;
            }

            return E_MPLAYER_RET_OK;
        }
        else
        {
            m_u16CurDirectoryDepth = NUM_OF_MAX_DIRECTORY_DEPTH-1;
        }
    }

    return E_MPLAYER_RET_FAIL;
}

#endif // ENABLE_PTP

#if (ENABLE_MPLAYER_PHOTO)
//******************************************************************************
/// Query photo decode state.
/// @return enumMPlayerPhotoDecoderState.
//******************************************************************************
enumMPlayerPhotoDecoderState MApp_MPlayer_QueryPhotoDecoderState(void)
{
    MPlayerFileInfo fileInfo;
    if(MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY,
                                   m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].u16PlayingIdx,
                                   &fileInfo) == E_MPLAYER_RET_OK)
    {
        // TODO: do I really need this function? It will ask PHOTO to tell MM the state mechine used internally
    }

    return E_MPLAYER_PHOTO_DECODER_INVALID_NUM;
}
#endif

//******************************************************************************
/// Query long file name of specific file that is identified by playing index.
/// @param  u16PlayingIdx \b IN  Specify the playing index of file.
/// @param  pFilename \b OUT  Specify the buffer for file name.
/// @param  u8Len \b OUT  Specify the length of file name.
/// @return TRUE or FALSE
//******************************************************************************
BOOLEAN MApp_MPlayer_QueryLongFilenameByPlayingIdx(U16 u16PlayingIdx, U8 *pFilename, U8 u8Len)
{
    MPlayerPlayListInfo *pstPlayListInfo, stPlayFileInfo;
    U16  u16PlayListNum;
    U32 u32XdataWindowBase;
    U8 u8BrowserHandleTemp = INVALID_BROWSER_HANDLE;
    enumMPlayerIdx ePlayerIdx = E_MPLAYER_FOREGROUND_PLAYER;
    U8 u8FileName[FILE_INFO_LONG_FILENAME_SIZE];

#if ENABLE_MPLAYER_MUSIC
    if(m_eMediaType == E_MPLAYER_TYPE_MUSIC)
    {
        ePlayerIdx = E_MPLAYER_BACKGROUND_PLAYER;
    }
#endif

    //printf("MApp_MPlayer_QueryLongFilenameByPlayingIdx(%d)\n", u16PlayingIdx);
    msAPI_MIU_SetRoundRobin(FALSE);  // If the file is JPG, will enable round robin.

    if(_MApp_MPlayer_GetPlayListAddressByMediaType(m_eMediaType, &u32XdataWindowBase)==FALSE)
    {
        return FALSE;
    }
    u16PlayListNum = m_u16SelectedFileNum[m_eMediaType];

    //(printf("    - u16PlayListNum = %bu\n",u16PlayListNum));
    if(u16PlayListNum == 0)
    {
        return FALSE;
    }

    pstPlayListInfo = (MPlayerPlayListInfo *) (_PA2VA(u32XdataWindowBase));
    memcpy(&stPlayFileInfo, &PLAY_LIST(u16PlayingIdx), sizeof(MPlayerPlayListInfo));

    // Change browser handle
    if(stPlayFileInfo.u16Drive != m_u16CurDriveIdx)
    {
        u8BrowserHandleTemp = MApp_FileBrowser_Create(stPlayFileInfo.u16Drive);
        if(u8BrowserHandleTemp != INVALID_BROWSER_HANDLE)
        {
            _MApp_MPlayer_Browser_ChangeBrowsingEnv(u8BrowserHandleTemp);
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        u8BrowserHandleTemp = INVALID_BROWSER_HANDLE;
    }

    // get long filename by file entry
    u8Len = MApp_FileBrowser_GetLongFileNameByFileEntry(
                    &stPlayFileInfo.fileEntry,
                    (U32)(&u8FileName[0]),
                    (FILE_INFO_LONG_FILENAME_SIZE/2-1));
    u8Len = (u8Len > (FILE_INFO_LONG_FILENAME_SIZE/2-1)) ?
                    FILE_INFO_LONG_FILENAME_SIZE/2-1:
                    u8Len;
    u8FileName[u8Len*2] = 0;
    u8FileName[u8Len*2+1] = 0;
    memcpy(pFilename, &u8FileName[0], FILE_INFO_LONG_FILENAME_SIZE);

    //Destroy temp Handle
    if(u8BrowserHandleTemp != INVALID_BROWSER_HANDLE)
    {
        MApp_FileBrowser_Destroy(u8BrowserHandleTemp);
        _MApp_MPlayer_Browser_ChangeBrowsingEnv(m_u8UserBrowserHandle);
    }

    return TRUE;
}

//******************************************************************************
/// Query the state that playlist is changed or not.
/// @return TRUE or FALSE
//******************************************************************************
BOOLEAN MApp_MPlayer_IsPlayListChanged(void)
{
    return m_bPlaylistChanged;
}

//******************************************************************************
/// Reset the state playlist change to FALSE.
/// @return N/A
//******************************************************************************
void MApp_MPlayer_PlayListIsSet(void)
{
    m_bPlaylistChanged = FALSE;
}

#if ENABLE_MPLAYER_MUSIC
//******************************************************************************
/// Play specific playing index file of music playlist.
/// @param  u16Idx \b IN  Specify the playing index of file.
/// @return TRUE or FALSE
//******************************************************************************
BOOLEAN MApp_MPlayer_MusicPlayList_PlayByIdx(U16 u16Idx)
{
    MPlayerPlayListInfo *pstPlayListInfo, stPlayFileInfo;
    U16  u16PlayListNum;
    U32 u32XdataWindowBase;

//    m_u32LyricSubtitleCheckTime = 0;
    m_u32LyricSubtitleCurTime   = -1;
    m_u16CurLyricPos = -1;
    m_u32CurSubtitlePos = -1;
    m_u32PlayCheckTime = -1;

    msAPI_MIU_SetRoundRobin(FALSE);  // If the file is JPG, will enable round robin.

    u32XdataWindowBase = ((MPLAYER_MUSIC_PLAYLIST_MEMORY_TYPE & MIU1) ? (MPLAYER_MUSIC_PLAYLIST_ADR | MIU_INTERVAL) : (MPLAYER_MUSIC_PLAYLIST_ADR));
    m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].u16PlayingIdx = u16Idx;
    u16PlayListNum = m_u16SelectedFileNum[m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaType];

    //MPLAYER_DBG(printf("    - u16PlayListNum = %bu\n",u16PlayListNum));
    if(u16PlayListNum == 0)
    {
        return FALSE;
    }

    pstPlayListInfo = (MPlayerPlayListInfo *)_PA2VA(u32XdataWindowBase);
    memcpy(&stPlayFileInfo, &PLAY_LIST(m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].u16PlayingIdx), sizeof(MPlayerPlayListInfo));

    // Change to new drive when necessary
    if (stPlayFileInfo.u16Drive != m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].u16CurrentDrive)
    {
        if (!_MApp_MPlayer_Browser_ChangeBrowsingDrive(
                &m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].u8BrowserHandle,
                m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].u16CurrentDrive,
                stPlayFileInfo.u16Drive))
        {
            return FALSE;
        }
    }

    memcpy(&m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].curPlayingFileEntry, &stPlayFileInfo.fileEntry, sizeof(stPlayFileInfo.fileEntry));
    m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].u16CurrentDrive = stPlayFileInfo.u16Drive;

    m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_FILE_INIT;

    // Playing the media file ---------------------------------------------------------------------
#if (ENABLE_AAC)
    if ( IS_AAC_FILE(stPlayFileInfo.u8ExtName) )
    {
        m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_AAC; //AAC
    }
    else
#endif
#if (ENABLE_WAV)
    if ( IS_WAV_FILE(stPlayFileInfo.u8ExtName) )
    {
        m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_WAV; //WAV
    }
    else
#endif
#if (ENABLE_WMA)
    if ( IS_WMA_FILE(stPlayFileInfo.u8ExtName) )
    {
        m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_WMA; //WMA
    }
    else
#endif //#if (ENABLE_WMA)
#if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
    if(IS_LOAS_FILE(stPlayFileInfo.u8ExtName))
    {
        m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_LOAS;
    }
    else
#endif //#if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
#if (ENABLE_OGG)
    if(IS_OGG_FILE(stPlayFileInfo.u8ExtName))
    {
        m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_OGG;
    }
    else
#endif
#if (ENABLE_AMR)
    if ( IS_AMR_FILE(stPlayFileInfo.u8ExtName) )
    {
        m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_AMR; //AMR
    }
    else if ( IS_AWB_FILE(stPlayFileInfo.u8ExtName) )
    {
        m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_AWB; //AWB
    }
    else
#endif
    {
        m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_MP3; //MP3
    }

#if (!ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
    m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType = _MApp_MPlayer_VerifyMusicType(&m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].curPlayingFileEntry, m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType);
#endif //#if (!ENABLE_NON_PARSING_AUDIO_DATA_INPUT)

    switch(m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eMediaSubType)
    {
#if (ENABLE_FLAC)
        case E_MPLAYER_SUBTYPE_FLAC:
#endif
#if (ENABLE_AC3)
        case E_MPLAYER_SUBTYPE_AC3:
#endif
#if (ENABLE_AAC)
        case E_MPLAYER_SUBTYPE_AAC:
#endif
#if (ENABLE_WAV)
        case E_MPLAYER_SUBTYPE_WAV:
#endif
        default:
        case E_MPLAYER_SUBTYPE_MP3:
#if (ENABLE_OGG)
        case E_MPLAYER_SUBTYPE_OGG:
#endif
#if (ENABLE_AMR)
        case E_MPLAYER_SUBTYPE_AMR:
        case E_MPLAYER_SUBTYPE_AWB:
#endif
#if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
        case E_MPLAYER_SUBTYPE_LOAS:
#endif //#if (ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
            MApp_Music_SetFileEntry(&m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].curPlayingFileEntry);
            break;
#if (ENABLE_WMA)
        case E_MPLAYER_SUBTYPE_WMA:
            MApp_WMA_SetFileEntry(&m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].curPlayingFileEntry);
            break;
#endif //#if (ENABLE_WMA)
    }

    m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 |= (enumMPlayerKnlFlags1)E_MPLAYER_KNL_FLG1_MUSIC_PLAY;
    m_MPlayerInfo[E_MPLAYER_BACKGROUND_PLAYER].eKnlFlag1 |= (enumMPlayerKnlFlags1)E_MPLAYER_KNL_FLG1_FILE_INIT;

    return TRUE;
}
#endif  // #if ENABLE_MPLAYER_MUSIC

//******************************************************************************
/// Query file index by file playing index.
/// @param  u16PlayingIdx \b IN  Specify the playing index.
/// @return file index.
//******************************************************************************
U16 MApp_MPlayer_QueryFileIdxByPlayingIdx(U16 u16PlayingIdx)
{
    U16 i = 0;
    MPlayerPlayListInfo *pstPlayListInfo, stPlayFileInfo;
    U16  u16PlayListNum;
    U32 u32XdataWindowBase;
    enumMPlayerIdx ePlayerIdx = E_MPLAYER_FOREGROUND_PLAYER;
    U8 end = 0;

    msAPI_MIU_SetRoundRobin(FALSE);  // If the file is JPG, will enable round robin.

#if ENABLE_MPLAYER_MUSIC
    if(m_eMediaType == E_MPLAYER_TYPE_MUSIC)
    {
        ePlayerIdx = E_MPLAYER_BACKGROUND_PLAYER;
    }
#endif

    if(_MApp_MPlayer_GetPlayListAddressByMediaType(m_eMediaType, &u32XdataWindowBase)==FALSE)
    {
        return FALSE;
    }

    u16PlayListNum = m_u16SelectedFileNum[m_eMediaType];

    //MPLAYER_DBG(printf("    - u16PlayListNum = %bu\n",u16PlayListNum));
    if(u16PlayListNum == 0)
    {
        return FALSE;
    }

    pstPlayListInfo = (MPlayerPlayListInfo *) (_PA2VA(u32XdataWindowBase));
    memcpy(&stPlayFileInfo, &PLAY_LIST(u16PlayingIdx), sizeof(MPlayerPlayListInfo));

    for (i=0; i < NUM_OF_MAX_DIRECTORY_DEPTH+1; i++)
    {
        if (stPlayFileInfo.u16PlayListPath[i] == MPLAYER_INVALID_INDEX)
        {
            end = i;
            break;
        }
    }

    if (end == 0)
        return 0;
    else
    {
        return (stPlayFileInfo.u16PlayListPath[i-1] + m_u16BufDirectoryNum);
    }
}

#if ENABLE_MPLAYER_PLUGIN
//******************************************************************************
/// Search file entry for specific file name.
/// @param  pFilename \b IN  Specify the file name for search.
/// @return TRUE or FALSE
//******************************************************************************
BOOLEAN MApp_MPlayer_SearchPlugInBinFileEntry(U8 *pFilename)
{
    DirEntryStruct * pCurrentDirEntry;     //global current dir entry
    FileEntry fileEntry;
    U16 u16FileIdx;
    U16 u16DirCnt;
    U16 u16FileCnt;

    u16FileIdx = 0;
    u16DirCnt = 0;
    u16FileCnt = 0;
    _MApp_MPlayer_Browser_FirstEntry();
    pCurrentDirEntry = MApp_FileBrowser_GetCurrentDirEntry();
    while(pCurrentDirEntry && u16FileIdx<NUM_OF_MAX_FILES_PER_DIRECTORY)
    {
        MApp_FileBrowser_GetCurrentFileEntry(&fileEntry);
        if(!(fileEntry.EntryAttrib & ENTRY_ATTRIB_HIDDEN) ||
            (fileEntry.EntryType == ENTRY_TYPE_DIR_DOT) ||
            (fileEntry.EntryType == ENTRY_TYPE_DIR_DOTDOT))
        {
            if(pCurrentDirEntry->u8DirEntryAttrib & ATTRIB_DIRECTORY)
            {
                //Don't care physical index, so we set NULL.
                //_MApp_MPlayer_Browser_SaveCurFileInfo(u16DirCnt+NUM_OF_MAX_FILES_PER_DIRECTORY, NULL, FILE_BUFFER);
                u16DirCnt++;
            }
            else
            {
                BOOLEAN bBin = TRUE;
                char au8Bin[3] = "BIN";
                U8 j = 0;
                //Don't care physical index, so we set NULL.
                //_MApp_MPlayer_Browser_SaveCurFileInfo(u16FileCnt, NULL, FILE_BUFFER);
                u16FileCnt++;
                for(j=0;j<3;j++)
                {
                    if(toupper(au8Bin[j]) != pCurrentDirEntry->ps8DirEntryExtName[j])
                    {
                        bBin = FALSE;
                        break;
                    }
                }
                if(bBin)
                {
                    U8 u8Len = 0;
                    U8 u8FileName[FILE_INFO_LONG_FILENAME_SIZE];
                    U8 u8BinName[FILE_INFO_LONG_FILENAME_SIZE];
                    BOOLEAN bMatch = TRUE;
                  #if 0
                    U8 u8Header[APP_HEADER_LENGTH];
                    U8 _u8FileHandle = FCTRL_INVALID_FILE_HANDLE;
                    U32 uRomSize = 0;
                    U32 uRet = 1;
                    BOOLEAN bRet = FALSE;
                  #endif

                    memset(u8FileName, 0, sizeof(u8FileName));//remove klocwork warning message
                    memset(u8BinName, 0, sizeof(u8BinName));

                    // Get long file name from file entry.
                    u8Len = MApp_FileBrowser_GetLongFileNameByFileEntry(
                                    &fileEntry,
                                    (U32)(&u8FileName[0]),
                                    (FILE_INFO_LONG_FILENAME_SIZE/2-1));
                    strncpy((char*)u8BinName, (char*)pFilename,MIN(sizeof(u8BinName),strlen((char*)pFilename)));  //Array over range protection!
                    FS_ASCII2Unicode(u8BinName);
                    for(j=0; j<u8Len*2; j++)
                    {
                        if(u8BinName[j] != u8FileName[j])
                        {
                            bMatch = FALSE;
                            break;
                        }
                    }
                    if(bMatch)
                    {
                      #if 1
                        memcpy(&fileEntryPlugin, &fileEntry, sizeof(FileEntry));
                        //printf("matched\n");
                        return TRUE;
                      #else
                        if((_u8FileHandle = msAPI_FCtrl_FileOpen(&fileEntry, OPEN_MODE_FOR_READ)) != FCTRL_INVALID_FILE_HANDLE)
                        {
                            U8 u8Extension[4];
                            U8 *pHeader = NULL;
                            uRomSize = msAPI_FCtrl_FileLength(_u8FileHandle);
                            bRet = msAPI_FCtrl_FileSeek(_u8FileHandle, uRomSize-APP_HEADER_LENGTH, FILE_SEEK_SET);
                            __ASSERT(bRet);
                            uRet = msAPI_FCtrl_FileRead(_u8FileHandle, (U32)(&u8Header[0]), APP_HEADER_LENGTH);
                            __ASSERT(uRet==0);
                            if ( msAPI_APEngine_AppIsHeaderValid(APP_GAME, u8Header, APP_HEADER_LENGTH) )
                            {
                                pHeader = (U8*)u8Header;
                                if(msAPI_APEngine_GetExtension(u8Extension, 4, pHeader, APP_HEADER_LENGTH))
                                {
                                    memcpy((void*)m_au8NES_ExtFileName[0], (void*)u8Extension, 3);
                                }
                                bRet = msAPI_FCtrl_FileSeek(_u8FileHandle, 0, FILE_SEEK_SET);
                                __ASSERT(bRet);

                                U32 u32TmpAddr = (((CAPE_BUFFER_MEMORY_TYPE & MIU1) ? (CAPE_BUFFER_ADR | MIU_INTERVAL) : (CAPE_BUFFER_ADR)) + CAPE_BUFFER_LEN - uRomSize) & ~(8-1);
                                uRet = msAPI_FCtrl_FileRead(_u8FileHandle, u32TmpAddr, uRomSize);
                                __ASSERT(uRet==0);
                                if ( msAPI_APEngine_AppIsContentValid((U8*)u32TmpAddr, uRomSize) )
                                {
                                    memcpy(&fileEntryPlugin, &fileEntry, sizeof(FileEntry));
                                    msAPI_FCtrl_FileClose(_u8FileHandle);
                                    return TRUE;
                                }
                            }
                            msAPI_FCtrl_FileClose(_u8FileHandle);
                        }
                      #endif
                    }
                }
            }
            u16FileIdx++;
        }
        msAPI_Timer_ResetWDT();
        pCurrentDirEntry = MApp_FileBrowser_GetNextDirEntry(1);
    }

    return FALSE;
}

//******************************************************************************
/// Return file entry that is searched in advance.
/// @return FileEntry
//******************************************************************************
FileEntry * MApp_MPlayer_GetPlugInBinFileEntry(void)
{
    return &fileEntryPlugin;
}
#endif //#if ENABLE_MPLAYER_PLUGIN

//******************************************************************************
/// Clear selected file number of all playlist.
/// @return N/A
//******************************************************************************
void MApp_MPlayer_PlayList_CleanUp(void)
{
    memset(m_u16SelectedFileNum, 0, sizeof(U16)*E_MPLAYER_TYPE_NUM);
}

//******************************************************************************
/// Set total file number.
/// @param  bufum \b IN  Specify the number to buffer total file.
/// @param  num \b IN  Specify the total file number.
/// @return N/A
//******************************************************************************
void MApp_MPlayer_SetFileNum(U16 bufum, U16 num)
{
    m_u16BufTotalFileNum = bufum;
    m_u16TotalFileNum = num;

    if(m_u16TotalFileNum && m_u16FilesPerPage>0)
    {
        m_u16TotalPageNum = (m_u16TotalFileNum+m_u16FilesPerPage-1) /m_u16FilesPerPage;
    }
}

//******************************************************************************
/// Set specific file as selected.
/// @param  DCnt \b IN  Specify the beginning file index.
/// @param  FTCnt \b IN  Specify the file count to set.
/// @return N/A
//******************************************************************************
void MApp_MPlayer_ReSetSelected(U16 DCnt, U16 FTCnt)
{
    U16 u16FileIdx;
    m_u16CurDirectoryDepth = 0;
    m_u16DirectoryNum[m_u16CurDirectoryDepth] = DCnt;
    for(u16FileIdx=DCnt;
        u16FileIdx<FTCnt;
        u16FileIdx++)
    {
        if(_MApp_MPlayer_Browser_IsInPlayingList(m_eMediaType, u16FileIdx))
        {
            _MApp_MPlayer_Browser_SetSelected(u16FileIdx, TRUE);
        }
        msAPI_Timer_ResetWDT();
    }
}

//******************************************************************************
/// Reset current file index to 0.
/// @return N/A
//******************************************************************************
void MApp_MPlayer_ReSetCurIdx(void)
{
    m_u16CurFileIdx = 0;
    m_u16CurPage1stFileIdx = 0;
    m_u16CurPageIdx = 0;
}
void MApp_MPlayer_ReSetThumbnailFileIdx(void)
{
    m_u16CurPage1stFileIdx = (m_u16CurPage1stFileIdx/24)*24+m_u16DirectoryNum[m_u16CurDirectoryDepth];
}

//******************************************************************************
/// Enable/Disable CoProcessor message on UART.
/// @param  DCnt \b IN  TRUE to output message on UART, otherwise, FALSE.
/// @return N/A
//******************************************************************************
void MApp_MPlayer_CoProcessorMsg(BOOL bEnable)
{
    MApp_VDPlayer_CodecDbgMsg(bEnable);
}

#if ENABLE_DVD

void MApp_MPlayer_DVD_StartPlay(void)
{
    if (m_eMoviePreviewState == E_MOVIE_PREVIEW_RUNNING)
    {
        MApp_VDPlayer_EnableVideoOutputFlag(ENABLE);
        NOTIFY(E_MPLAYER_NOTIFY_BEFORE_MOVIE_PREVIEW, NULL);
    }
    else
    {
#if (ENABLE_INTERNAL_BMP_SUBTITLE || ENABLE_EXTERNAL_BMP_SUBTITLE)
        msAPI_MpegSP_SetVideoDimension(
            (U16)MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_H_SIZE),
            (U16)MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_V_SIZE));
#endif
        NOTIFY(E_MPLAYER_NOTIFY_MEDIA_PREDECODE_OK, NULL);
    }
}

U8 MApp_MPlayer_DVD_Command(enumMPlayerDVDCmdType cmd)
{
    U8 ret = 0;

    switch (cmd)
    {
        case E_MPLAYER_DVD_CMD_PLAY_PAUSE:
            {
                enumMPlayerMoviePlayMode eMoviePlayMode = MApp_MPlayer_QueryMoviePlayMode();

                if ((eMoviePlayMode != E_MPLAYER_MOVIE_PAUSE) &&
                    (eMoviePlayMode != E_MPLAYER_MOVIE_STEP) )
                {
                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_PAUSE);
                    ret = 1;
                }
                else
                {
                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_NORMAL);
                    ret = 2;
                }
            }
            return ret;
        case E_MPLAYER_DVD_CMD_FF:
            {
                enumMPlayerMoviePlayMode ePlayMode = MApp_MPlayer_QueryMoviePlayMode();

                if (!(ePlayMode >= E_MPLAYER_MOVIE_FF_2X && ePlayMode <= E_MPLAYER_MOVIE_FF_32X))
                {
                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FF_2X);
                    ret = 1;
                }
                else if (ePlayMode == E_MPLAYER_MOVIE_FF_2X)
                {
                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FF_4X);
                    ret = 2;
                }
                else if (ePlayMode == E_MPLAYER_MOVIE_FF_4X)
                {
                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FF_8X);
                    ret = 3;
                }
                else if (ePlayMode == E_MPLAYER_MOVIE_FF_8X)
                {
                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FF_16X);
                    ret = 4;
                }
                else if (ePlayMode == E_MPLAYER_MOVIE_FF_16X)
                {
                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FF_32X);
                    ret = 5;
                }
                else if (ePlayMode == E_MPLAYER_MOVIE_FF_32X)
                {
                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_NORMAL);
                    ret = 6;
                }

            }
            return ret;
        case E_MPLAYER_DVD_CMD_FB:
            {
                enumMPlayerMoviePlayMode ePlayMode = MApp_MPlayer_QueryMoviePlayMode();

                if (!(ePlayMode >= E_MPLAYER_MOVIE_FB_2X && ePlayMode <= E_MPLAYER_MOVIE_FB_32X))
                {
                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FB_2X);
                    ret = 1;
                }
                else if (ePlayMode == E_MPLAYER_MOVIE_FB_2X)
                {
                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FB_4X);
                    ret = 2;
                }
                else if (ePlayMode == E_MPLAYER_MOVIE_FB_4X)
                {
                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FB_8X);
                    ret = 3;
                }
                else if (ePlayMode == E_MPLAYER_MOVIE_FB_8X)
                {
                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FB_16X);
                    ret = 4;
                }
                else if (ePlayMode == E_MPLAYER_MOVIE_FB_16X)
                {
                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_FB_32X);
                    ret = 5;
                }
                else if (ePlayMode == E_MPLAYER_MOVIE_FB_32X)
                {
                    MApp_MPlayer_MovieChangePlayMode(E_MPLAYER_MOVIE_NORMAL);
                    ret = 6;
                }
            }
            return ret;
        default:
            return (MApp_VDPlayer_DVD_Command(cmd));
    }
}
#endif  // ENABLE_DVD

BOOLEAN MApp_MPlayer_GetPlayListFileInfo(U16 u16PlayingIdx, MPlayerFileInfo *pInfo)
{
   MPlayerPlayListInfo *pstPlayListInfo, stPlayFileInfo;
    U16 u16PlayListNum;
    U32 u32Addr;;
    U8 u8BrowserHandleTemp = INVALID_BROWSER_HANDLE;
    enumMPlayerIdx ePlayerIdx = E_MPLAYER_FOREGROUND_PLAYER;
    U8 u8FileName[FILE_INFO_LONG_FILENAME_SIZE];
    U8 u8Len;

    MPLAYER_DBG(printf("\nu16PlayingIdx=%u\n", u16PlayingIdx));

     u16PlayListNum = m_u16SelectedFileNum[m_eMediaType];
      if(u16PlayListNum == 0 || u16PlayingIdx >= u16PlayListNum)
      {
          return FALSE;
      }
      switch(m_eMediaType)
      {
  #if ENABLE_MPLAYER_PHOTO
      case E_MPLAYER_TYPE_PHOTO:
       u32Addr=(U32)((MPLAYER_PHOTO_PLAYLIST_MEMORY_TYPE & MIU1) ? (MPLAYER_PHOTO_PLAYLIST_ADR | MIU_INTERVAL) : (MPLAYER_PHOTO_PLAYLIST_ADR)) + (U32)u16PlayingIdx*sizeof(MPlayerPlayListInfo);
          break;
  #endif
  #if ENABLE_MPLAYER_MUSIC
      case E_MPLAYER_TYPE_MUSIC:
           u32Addr=(U32)((MPLAYER_MUSIC_PLAYLIST_MEMORY_TYPE & MIU1) ? (MPLAYER_MUSIC_PLAYLIST_ADR | MIU_INTERVAL) : (MPLAYER_MUSIC_PLAYLIST_ADR)) + (U32)u16PlayingIdx*sizeof(MPlayerPlayListInfo);
          ePlayerIdx = E_MPLAYER_BACKGROUND_PLAYER;
          break;
  #endif  // #if ENABLE_MPLAYER_MUSIC
  #if ENABLE_MPLAYER_MOVIE
      case E_MPLAYER_TYPE_MOVIE:
           u32Addr=(U32)((MPLAYER_MOVIE_PLAYLIST_MEMORY_TYPE & MIU1) ? (MPLAYER_MOVIE_PLAYLIST_ADR | MIU_INTERVAL) : (MPLAYER_MOVIE_PLAYLIST_ADR)) + (U32)u16PlayingIdx*sizeof(MPlayerPlayListInfo);
          break;
  #endif  // #if ENABLE_MPLAYER_MOVIE
  #if ENABLE_MPLAYER_TEXT
      case E_MPLAYER_TYPE_TEXT:
          u32Addr=(U32)((MPLAYER_TEXT_PLAYLIST_MEMORY_TYPE & MIU1) ? (MPLAYER_TEXT_PLAYLIST_ADR | MIU_INTERVAL) : (MPLAYER_TEXT_PLAYLIST_ADR)) + (U32)u16PlayingIdx*sizeof(MPlayerPlayListInfo);
          break;
  #endif  // #if ENABLE_MPLAYER_TEXT
      default:
          return FALSE;
      }
      pstPlayListInfo = (MPlayerPlayListInfo *)_PA2VA(u32Addr);
      memcpy(&stPlayFileInfo, pstPlayListInfo, sizeof(MPlayerPlayListInfo));

      //printf("\nu16dirveid=%u\n", stPlayFileInfo.u16Drive);

      // Change browser handle
      if(stPlayFileInfo.u16Drive != m_u16CurDriveIdx)
      {
          u8BrowserHandleTemp = MApp_FileBrowser_Create(stPlayFileInfo.u16Drive);
          _MApp_MPlayer_Browser_ChangeBrowsingEnv(u8BrowserHandleTemp);
      }
      else
      {
          u8BrowserHandleTemp = INVALID_BROWSER_HANDLE;
      }

      // get long filename by file entry
      //printf("\nm_u16CurDriveIdx=%u\n", m_u16CurDriveIdx);
      u8Len = MApp_FileBrowser_GetLongFileNameByFileEntry(
                      &stPlayFileInfo.fileEntry,
                       (U32)(&u8FileName[0]),
                      (FILE_INFO_LONG_FILENAME_SIZE/2-1));
      u8Len = (u8Len > (FILE_INFO_LONG_FILENAME_SIZE/2-1)) ?
                      FILE_INFO_LONG_FILENAME_SIZE/2-1:
                      u8Len;
      u8FileName[u8Len*2] = 0;
      u8FileName[u8Len*2+1] = 0;

    memcpy(pInfo->u8LongFileName, &u8FileName[0], FILE_INFO_LONG_FILENAME_SIZE);
    memcpy(pInfo->u8ExtFileName, &stPlayFileInfo.u8ExtName, 4);
    memcpy(&pInfo->fileEntry, &stPlayFileInfo.fileEntry, sizeof(stPlayFileInfo.fileEntry));

    pInfo->u64FileSize = pInfo->fileEntry.FileLength;

    FS_TIME fs_time;
    msAPI_FS_ConvertSeconds2StTime(pInfo->fileEntry.EntrySeconds, &fs_time);
    pInfo->u16Year = fs_time.u16Year;
    pInfo->u8Month  = fs_time.u8Month;
    pInfo->u8Day = fs_time.u8Day;
    pInfo->u8Hour = fs_time.u8Hour;
    pInfo->u8Minute = fs_time.u8Min;
    pInfo->u8Second = fs_time.u8Sec;

    //Destroy temp Handle
    if(u8BrowserHandleTemp != INVALID_BROWSER_HANDLE)
    {
        MApp_FileBrowser_Destroy(u8BrowserHandleTemp);
        _MApp_MPlayer_Browser_ChangeBrowsingEnv(m_u8UserBrowserHandle);
    }
        Remove_enumFileAttribute(pInfo->eAttribute, E_MPLAYER_FILE_DIRECTORY);
    return TRUE;
}

#if (EN_DMP_SEARCH_ALL || EN_DMP_SEARCH_FAV)
//******************************************************************************
/// Load the file information from play list buffer to file buffer
/// @param eMediaType \b IN: media type
/// @param bIsNeedDot \b IN: TRUE for need the "." in root directory
/// @return BOOLEAN
//******************************************************************************
BOOLEAN MApp_MPlayer_LoadPlayList2FileBuffer(enumMPlayerMediaType eMediaType, BOOLEAN bIsNeedDot)
{
    U8 u8ReservedDirNum = 0;
    U16 u16idx = 0;
    U16 u16PlayListNum = m_u16SelectedFileNum[eMediaType];
    U32 u32PhyBufferAddr = (MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR);
    MPlayerFileInfo* pstFileInfo = (MPlayerFileInfo *)_PA2VA(u32PhyBufferAddr);
    FileEntry fileEntry;

    memset(&fileEntry, 0, sizeof(FileEntry));

    if(bIsNeedDot)
    {
        fileEntry.EntryType = ENTRY_TYPE_DIR_DOT;
        fileEntry.EntryAttrib=ENTRY_ATTRIB_DIRECTORY;
        memcpy(&pstFileInfo->fileEntry, &fileEntry, sizeof(FileEntry));
        pstFileInfo++;
        u8ReservedDirNum = 1;
    }

    //load playlist to file buffer one by one
    for(u16idx = 0; u16idx < u16PlayListNum; u16idx++)
    {
        if(!MApp_MPlayer_GetPlayListFileInfo(u16idx ,pstFileInfo))
        {
            printf("Unexpected error in %s\n",__FUNCTION__);
            return FALSE;
        }
        Remove_enumFileAttribute(pstFileInfo->eAttribute, E_MPLAYER_FILE_SELECT);
        pstFileInfo++;
    }

    //re-assign the global variables
    m_u16TotalFileNum = u16PlayListNum + u8ReservedDirNum;
    memset(m_u16DirectoryNum, 0, sizeof(U16)*NUM_OF_MAX_DIRECTORY_DEPTH);
    m_u16DirectoryNum[0] = u8ReservedDirNum;
    m_u16BufDirectoryNum = u8ReservedDirNum;
    m_u16CurDirectoryDepth = 0;

    m_u16TotalPageNum = (m_u16TotalFileNum+m_u16FilesPerPage-1) /m_u16FilesPerPage;
    MPLAYER_DBG(printf("\n m_u16TotalPageNum= %d",(U16)m_u16TotalPageNum));

    return TRUE;
}
#endif

#if EN_DMP_SEARCH_FAV
/// Favorite play list file header
/// 0~21: Prefix "MSTAR MPLAYERPLAYLIST "
/// 22~23: Play list structure size
/// 24~31: Reserved
#define MSTAR_FAV_PLAYLIST_HEADER  'M','S','T','A',\
    'R',' ','M','P',\
    'L','A','Y','E',\
    'R','P','L','A',\
    'Y','L','I','S',\
    'T',' ',0,0,\
    0,0,0,0,\
    0,0,0,0
#define MSTAR_FAV_PLAYLIST_HEADER_LEN 32
#define MSTAR_FAV_PLAYLIST_PREFIX_LEN 22
//******************************************************************************
/// Save the file information from play list buffer to USB disk
/// @param eMediaType \b IN: media type
/// @return BOOLEAN
//******************************************************************************
BOOLEAN MApp_MPlayer_SavePlayListToDisk(enumMPlayerMediaType eMediaType)
{
    U8 u8PlaylistName[E_MPLAYER_TYPE_NUM][64] =
    {
        "PhotoPlaylist.mst",
        "MusicPlaylist.mst",
        "MoviePlaylist.mst",
        "TextPlaylist.mst"
    };

    U8 u8Header[MSTAR_FAV_PLAYLIST_HEADER_LEN] ={
        MSTAR_FAV_PLAYLIST_HEADER
    };

    U8 u8HandleNo;
    U8 u8EnvHandle = INVALID_BROWSER_HANDLE;
    U8 u8PreEnvHandle = INVALID_BROWSER_HANDLE;
    U16 u16PlayListStructSize;
    U32 u32DesiredSaveLength;
    U32 u32XdataWindowBase;
    FileEntry stFileEntry;
    BOOLEAN bOpenNewFile = TRUE;

    memset(&stFileEntry,0,sizeof(FileEntry));
    u16PlayListStructSize = sizeof(MPlayerPlayListInfo);

    if(m_u8TotalDriveNum == 0)
    {
        printf("[Save] No device. Fail\n");
        return FALSE;
    }

    if(_MApp_MPlayer_GetPlayListAddressByMediaType(eMediaType, &u32XdataWindowBase)==FALSE)
    {
        printf("[Save] Get list address. Fail\n");
        return FALSE;
    }

    if(m_u16SelectedFileNum[eMediaType] == 0)
    {
        printf("[Save] No selected file.\n");
        return FALSE;
    }

    u32DesiredSaveLength = m_u16SelectedFileNum[eMediaType]*u16PlayListStructSize;

    u8EnvHandle = MApp_FileBrowser_Create(m_u16CurDriveIdx);
    if(u8EnvHandle == INVALID_BROWSER_HANDLE)
    {
        printf("[Save] No File browser.\n");
        return FALSE;
    }
    u8PreEnvHandle = MApp_FileBrowser_GetEnvironment();
    MApp_FileBrowser_SetEnvironment(u8EnvHandle);

    ASCIItoUnicode2((S8 *)u8PlaylistName[eMediaType], strlen((char*)u8PlaylistName[eMediaType]));

    if(MApp_FilrBrowser_GetNameExistedInCurrent((U16 *)(void *)u8PlaylistName[eMediaType], UnicodeLen((S8*)u8PlaylistName[eMediaType]), &stFileEntry))
    {
        U32 u32CurrentFileLength;
        u8HandleNo = msAPI_FCtrl_FileOpen(&stFileEntry, OPEN_MODE_FOR_READ_WRITE);
        u32CurrentFileLength = msAPI_FCtrl_FileLength(u8HandleNo);

        // bOpenNewFile = FALSE -> reduce time to open one new file
        if(u32CurrentFileLength > u32DesiredSaveLength)
        {
            msAPI_FCtrl_FileClose(u8HandleNo);
            msAPI_FCtrl_FileDelete(&stFileEntry);
        }
        else
        {
            bOpenNewFile = FALSE;
        }
    }

    if(bOpenNewFile == TRUE)
    {
        u8HandleNo = MApp_FileBrowser_OpenNewFileForWrite((U16 *)(void *)u8PlaylistName[eMediaType], UnicodeLen((S8*)u8PlaylistName[eMediaType]));
    }

    if(u8HandleNo == INVALID_FILE_HANDLE)
    {
        printf("[Save] Create file error.\n");
        return FALSE;
    }

    // Update header
    memcpy(&u8Header[MSTAR_FAV_PLAYLIST_PREFIX_LEN],&u16PlayListStructSize,2);

    msAPI_FCtrl_FileWrite(u8HandleNo, (U32)u8Header, MSTAR_FAV_PLAYLIST_HEADER_LEN);
    msAPI_FCtrl_FileWrite(u8HandleNo, u32XdataWindowBase, u32DesiredSaveLength);
    msAPI_FCtrl_FileClose(u8HandleNo);
    MApp_FileBrowser_Destroy(u8EnvHandle);
    MApp_FileBrowser_SetEnvironment(u8PreEnvHandle);

    return TRUE;

}

//******************************************************************************
/// Load the file information from USB disk to play list buffer
/// @param eMediaType \b IN: media type
/// @return BOOLEAN
//******************************************************************************
BOOLEAN MApp_MPlayer_LoadPlayListFromDisk(enumMPlayerMediaType eMediaType)
{
    U8 u8PlaylistName[E_MPLAYER_TYPE_NUM][64] =
    {
        "PhotoPlaylist.mst",
        "MusicPlaylist.mst",
        "MoviePlaylist.mst",
        "TextPlaylist.mst"
    };

    U8 u8Header[MSTAR_FAV_PLAYLIST_HEADER_LEN] ={
        MSTAR_FAV_PLAYLIST_HEADER
    };

    U8 u8HandleNo;
    U16 u16SavedPlayListFileNum;
    U16 u16CurrentIdx;
    U16 u16PlayListStructSize;
    U32 u32CurrentFileLength;
    U32 u32XdataWindowBase;
    U32 u32RetRead;
    FileEntry stFileEntry;

    MPlayerPlayListInfo *pstReadPlayListInfo;

    memset(&stFileEntry,0,sizeof(stFileEntry));

    if(_MApp_MPlayer_GetPlayListAddressByMediaType(eMediaType, &u32XdataWindowBase)==FALSE)
    {
        printf("[Load] Get List Address. Fail\n");
        return FALSE;
    }

    ASCIItoUnicode2((S8 *)u8PlaylistName[eMediaType], strlen((char*)u8PlaylistName[eMediaType]));

    if(MApp_FilrBrowser_GetNameExistedInCurrent((U16 *)(void *)u8PlaylistName[eMediaType], UnicodeLen((S8*)u8PlaylistName[eMediaType]), &stFileEntry))
    {
        u8HandleNo = msAPI_FCtrl_FileOpen(&stFileEntry, OPEN_MODE_FOR_READ);
        if (u8HandleNo == INVALID_FILE_HANDLE)
        {
            printf("[Load] Open mst file. Fail\n");
            return FALSE;
        }

        //read header
        u32RetRead = msAPI_FCtrl_FileRead(u8HandleNo, u32XdataWindowBase, MSTAR_FAV_PLAYLIST_HEADER_LEN);
        if(u32RetRead > 0)
        {
            msAPI_FCtrl_FileClose(u8HandleNo);
            printf("[Load] Read mst file. Fail\n");
            return FALSE;
        }

        if(memcmp((U8*)_PA2VA(u32XdataWindowBase),
                      &u8Header,
                      MSTAR_FAV_PLAYLIST_PREFIX_LEN) != 0)
        {
            printf("[Load] Wrong version of mst file. Fail\n");
            return FALSE;
        }

        //Play list data structure size is not matched.
        u16PlayListStructSize = *(U16*)_PA2VA(u32XdataWindowBase+MSTAR_FAV_PLAYLIST_PREFIX_LEN);
        if(u16PlayListStructSize != sizeof(MPlayerPlayListInfo))
        {
            printf("[Load] Play list data structure size is not matched.\n");
            return FALSE;
        }

        u32CurrentFileLength = msAPI_FCtrl_FileLength(u8HandleNo);
        u16SavedPlayListFileNum = (u32CurrentFileLength-MSTAR_FAV_PLAYLIST_HEADER_LEN)/sizeof(MPlayerPlayListInfo);
        if(u16SavedPlayListFileNum > NUM_OF_MAX_SELECTED_FILE)
        {
            u16SavedPlayListFileNum = NUM_OF_MAX_SELECTED_FILE;
        }

        u32RetRead = msAPI_FCtrl_FileRead(u8HandleNo, u32XdataWindowBase, u16SavedPlayListFileNum*sizeof(MPlayerPlayListInfo));

        if(u32RetRead > 0)
        {
            msAPI_FCtrl_FileClose(u8HandleNo);
            return FALSE;
        }

        m_u16SelectedFileNum[eMediaType] = u16SavedPlayListFileNum;
        pstReadPlayListInfo = (MPlayerPlayListInfo *)_PA2VA(u32XdataWindowBase);

        for(u16CurrentIdx = 0 ;u16CurrentIdx < u16SavedPlayListFileNum; u16CurrentIdx++)
        {
            // Check if this play list item is existed in current USB disk or not
            // Without API for checking if files in USB, we use alternate API.
            // If the files is deleted in USB. The GetLongFileNameByFileEntry funtion will return 0.
            if(MApp_FileBrowser_GetLongFileNameByFileEntry(&(pstReadPlayListInfo->fileEntry),(U32)u8PlaylistName[eMediaType],32))
            {
                pstReadPlayListInfo++;
            }
            else
            {
                // m_u16SelectedFileNum[eMediaType] is updated in this function, we do not need to minus it.
                MApp_MPlayer_RemoveFileFromPlayList(eMediaType,u16CurrentIdx,TRUE);
            }
        }
        msAPI_FCtrl_FileClose(u8HandleNo);
    }
    else
    {
        printf("[Load] Not found mst file\n");
        return FALSE;
    }

    //update the file if one playlist info is missed.
    if(m_u16SelectedFileNum[eMediaType] != u16SavedPlayListFileNum)
    {
        MApp_MPlayer_SavePlayListToDisk(eMediaType);
    }

    return TRUE;
}
#endif

#if EN_DMP_SEARCH_ALL
BOOLEAN MApp_SelectAllFileInCurDir(void)
{
    U16 i,first,total,cur;

    first=m_u16DirectoryNum[m_u16CurDirectoryDepth];
    total=m_u16TotalFileNum;
    cur=m_u16CurFileIdx;

    for(i=first;i<total;i++)
    {
        if(MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY,i)!=E_MPLAYER_RET_OK)
            return FALSE;
        if(MApp_MPlayer_SetFileSelected(E_MPLAYER_INDEX_CURRENT_DIRECTORY, i)!=E_MPLAYER_RET_OK)
            return FALSE;
    }
    if(MApp_MPlayer_SetCurrentFile(E_MPLAYER_INDEX_CURRENT_DIRECTORY,cur)!=E_MPLAYER_RET_OK)
        return FALSE;

    return TRUE;
}

enumMPlayerRet MApp_MPlayer_ExitDirectory(enumMPlayerFileIndexBegin eBegin)
{
    DirEntryStruct * pCurrentDirEntry;     //global current dir entry
    U16 u16Idx = 0x01;

#ifdef ENABLE_PTP
    if (MApp_PTP_DeviceInUse())
    {
        return MApp_MPlayer_PTP_EnterDirectory(eBegin, u16Idx);
    }
#endif

    if(eBegin == E_MPLAYER_INDEX_CURRENT_PAGE)
    {
        u16Idx += m_u16CurPage1stFileIdx;
    }
    else if(eBegin != E_MPLAYER_INDEX_CURRENT_DIRECTORY)
    {
        return E_MPLAYER_RET_FAIL;
    }

#if (ENABLE_MPLAYER_SORT)
    u16Idx = _MApp_MPlayer_LookupPhysicalIndex(u16Idx);
#endif

    _MApp_MPlayer_Browser_FirstEntry();
    if(!_MApp_MPlayer_Browser_FindNextDirectory(u16Idx))
    {
        return E_MPLAYER_RET_FAIL;
    }

    pCurrentDirEntry = MApp_FileBrowser_GetCurrentDirEntry();

    //remove klocwork warning message
    if(pCurrentDirEntry == NULL)
    {
        __ASSERT(0);
        return E_MPLAYER_RET_FAIL;
    }

    if((strncmp((char*)pCurrentDirEntry->ps8DirEntryName, ".       ", 8) != 0) ||
       (strncmp((char*)pCurrentDirEntry->ps8DirEntryExtName, "   ", 3) != 0))
    {
        BOOLEAN bPop = FALSE;

        if(m_u16CurDirectoryDepth > 0)
        {
            m_u16CurDirectoryDepth--;
            m_u16CurDirectory[m_u16CurDirectoryDepth] = MPLAYER_INVALID_INDEX;
        #if ENABLE_MPLAYER_SORT
            m_u16CurDirectoryPhy[m_u16CurDirectoryDepth] = MPLAYER_INVALID_INDEX;
        #endif
            bPop = TRUE;
        }

        if(m_u16CurDirectoryDepth <= NUM_OF_MAX_DIRECTORY_DEPTH)
        {
            if (!bPop)
            {
                m_u16CurDirectory[m_u16CurDirectoryDepth-1] = m_u16CurFileIdx;
            #if ENABLE_MPLAYER_SORT
                m_u16CurDirectoryPhy[m_u16CurDirectoryDepth-1] = _MApp_MPlayer_LookupPhysicalIndex(m_u16CurFileIdx);
            #endif
            }

            if(pCurrentDirEntry->u8DirEntryAttrib & ATTRIB_DIRECTORY)
            {
                MApp_MPlayer_RecordPath(bPop);
                MApp_FileBrowser_EnterDirectory(0);
            }
            m_u16DirectoryNum[m_u16CurDirectoryDepth] = 0;
            m_u16CurFileIdx = 0;
#if (ENABLE_SELECT_FILE_ACROSS_DIRECTORY == 0)
            //In BGM mode or Copy mode no need clear playlist.
            if( m_bIsCopyMode == FALSE
        #if PLAYLIST_BGM
            &&  m_bBGMPlaylistInit == FALSE
        #endif
            )
            {
                memset(m_u16SelectedFileNum, 0, sizeof(m_u16SelectedFileNum));
            }
#endif

            _MApp_MPlayer_Browser_EnumCurDirectory();

            m_u16CurPage1stFileIdx = 0;
            m_u16CurPageIdx =0;
            if(m_u16TotalFileNum)
            {
                m_u16TotalPageNum = (m_u16TotalFileNum+m_u16FilesPerPage-1) /
                                    m_u16FilesPerPage;
            }
            else
            {
                return E_MPLAYER_RET_FAIL;
            }

            return E_MPLAYER_RET_OK;
        }
        else
        {
            m_u16CurDirectoryDepth = NUM_OF_MAX_DIRECTORY_DEPTH;
        }
    }

    return E_MPLAYER_RET_FAIL;
}


void MApp_MPlayer_GetAllFilesInCurDiretory(void)
{
       U8 u8FolderIdx;

       if(m_u16CurDirectoryDepth == NUM_OF_MAX_DIRECTORY_DEPTH)
         return;

       for(u8FolderIdx=2;u8FolderIdx<MApp_MPlayer_QueryDirectoryNumber();u8FolderIdx++)
       {
          if(MApp_MPlayer_EnterDirectory(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u8FolderIdx) != E_MPLAYER_RET_OK)
              continue;
          _MApp_MPlayer_Browser_FirstEntry();

           //printf("\nam_u16CurDirectoryDepth:%d",(U16)m_u16CurDirectoryDepth);
          _MApp_MPlayer_Browser_EnumCurDirectory();

            m_u16CurFileIdx = 0;
            m_u16CurPage1stFileIdx = 0;
            m_u16CurPageIdx =0;
            m_u16CurDirectory[m_u16CurDirectoryDepth-1] = u8FolderIdx;
        #if ENABLE_MPLAYER_SORT
            m_u16CurDirectoryPhy[m_u16CurDirectoryDepth-1] = _MApp_MPlayer_LookupPhysicalIndex(u8FolderIdx);
        #endif

            MApp_SelectAllFileInCurDir();
            MApp_MPlayer_GetAllFilesInCurDiretory();
            MApp_MPlayer_ExitDirectory(E_MPLAYER_INDEX_CURRENT_DIRECTORY);  // ".."
            _MApp_MPlayer_Browser_FirstEntry();
            _MApp_MPlayer_Browser_EnumCurDirectory();
         }
}
void MApp_MPlayer_SetSearchAllModeTotalFiles(void)
{
      m_u16TotalFileNum = m_u16SelectedFileNum[m_eMediaType];
}

void MApp_MPlayer_GetAllFilesInCurDrive(void)
{
    U16 u16FolderIdx;
    U32 u32Timer;

    //printf("usb search all file\n");
    u32Timer = msAPI_Timer_GetTime0();

    MApp_MPlayer_PlayList_CleanUp();
    MApp_FileBrowser_ChangeToRootDirectory();
    _MApp_MPlayer_Browser_FirstEntry();
    _MApp_MPlayer_Browser_EnumCurDirectory();
    MApp_SelectAllFileInCurDir();
    for(u16FolderIdx=1;u16FolderIdx<MApp_MPlayer_QueryDirectoryNumber();u16FolderIdx++)
    {
        if(MApp_MPlayer_EnterDirectory(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16FolderIdx) != E_MPLAYER_RET_OK)
            continue;
        _MApp_MPlayer_Browser_FirstEntry();
        //printf("\nam_u16CurDirectoryDepth:%d",(U16)m_u16CurDirectoryDepth);
        _MApp_MPlayer_Browser_EnumCurDirectory();
        m_u16CurFileIdx = 0;
        m_u16CurPage1stFileIdx = 0;
        m_u16CurPageIdx =0;
        m_u16CurDirectory[m_u16CurDirectoryDepth-1] = u16FolderIdx;
    #if ENABLE_MPLAYER_SORT
        m_u16CurDirectoryPhy[m_u16CurDirectoryDepth-1] = _MApp_MPlayer_LookupPhysicalIndex(u16FolderIdx);
    #endif
        MApp_SelectAllFileInCurDir();
        MApp_MPlayer_GetAllFilesInCurDiretory();
        MApp_MPlayer_ExitDirectory(E_MPLAYER_INDEX_CURRENT_DIRECTORY);  // ".."
        _MApp_MPlayer_Browser_FirstEntry();
        _MApp_MPlayer_Browser_EnumCurDirectory();
    }

    MApp_FileBrowser_ChangeToRootDirectory();
    _MApp_MPlayer_Browser_FirstEntry();
    _MApp_MPlayer_Browser_EnumCurDirectory();
    MApp_MPlayer_SetCurrentPlayingList(0);

    MPLAYER_DBG(printf("\nSerach Time:= %d ms",(U16)(msAPI_Timer_DiffTimeFromNow(u32Timer))));
    MPLAYER_DBG(printf("\nm_u16SelectedFileNum[E_MPLAYER_TYPE_PHOTO]= %d",(U16)m_u16SelectedFileNum[E_MPLAYER_TYPE_PHOTO]));
    MPLAYER_DBG(printf("\nm_u16SelectedFileNum[E_MPLAYER_TYPE_MUSIC]= %d",(U16)m_u16SelectedFileNum[E_MPLAYER_TYPE_MUSIC]));
    MPLAYER_DBG(printf("\nm_u16SelectedFileNum[E_MPLAYER_TYPE_MOVIE]= %d",(U16)m_u16SelectedFileNum[E_MPLAYER_TYPE_MOVIE]));
    MPLAYER_DBG(printf("\nm_u16SelectedFileNum[E_MPLAYER_TYPE_TEXT]= %d",(U16)m_u16SelectedFileNum[E_MPLAYER_TYPE_TEXT]));
      m_u16TotalPageNum = (m_u16TotalFileNum+m_u16FilesPerPage-1) /m_u16FilesPerPage;
    MPLAYER_DBG(printf("\n m_u16TotalPageNum= %d",(U16)m_u16TotalPageNum));
}


 #if 0
 void MApp_MPlayer_Search_AllDevice_TargetDirs(void)
 {
     U8 u8driveidx ;

     printf("m_u8TotalDriveNum = %d\n",(U16)m_u8TotalDriveNum);
     MApp_MPlayer_PlayList_CleanUp();
     for(u8driveidx= 0;u8driveidx<m_u8TotalDriveNum;u8driveidx++)
     {
         MApp_DMP_SetCurDrvIdxAndCalPageIdx(u8driveidx);
         if(MApp_MPlayer_ConnectDrive(MApp_DMP_GetDriveFromMappingTable(MApp_DMP_GetCurDrvIdx())) == E_MPLAYER_RET_OK)
               MApp_MPlayer_GetAllFilesInCurDrive();
         else
               printf("Connect [%d] drive fail !\n = %d\n",(U16)u8driveidx);

     }

 }
 #endif
#endif//#if EN_DMP_SEARCH_ALL
#if ENABLE_MPLAYER_MIXED
void MApp_MPlayer_SetMediaTypeByFileExtName(MPlayerFileInfo *pFileInfo)
{
    #define extName     pFileInfo->u8ExtFileName
    enumMPlayerMediaType eMediaTye = E_MPLAYER_TYPE_INVALID;

    if(IS_PHOTO_FILE(extName))
        eMediaTye = E_MPLAYER_TYPE_PHOTO;
    else if(IS_MUSIC_FILE(extName))
        eMediaTye = E_MPLAYER_TYPE_MUSIC;
    else if(IS_MOVIE_FILE(extName))
        eMediaTye = E_MPLAYER_TYPE_MOVIE;
    else if(IS_TXT_FILE(extName))
        eMediaTye = E_MPLAYER_TYPE_TEXT;
//    else
        //printf("Do not support this file!\n ");

    MApp_MPlayer_SetCurrentMediaType(eMediaTye, TRUE);
    MApp_DMP_SetDmpFlag(DMP_FLAG_BROWSER_MIXED);
}
enumMPlayerMediaType MApp_MPlayer_QueryMediaTypeByFileExtName(MPlayerFileInfo *pFileInfo)
{
    #define extName     pFileInfo->u8ExtFileName

    if(IS_PHOTO_FILE(extName))
        return E_MPLAYER_TYPE_PHOTO;
    else if(IS_MUSIC_FILE(extName))
        return E_MPLAYER_TYPE_MUSIC;
    else if(IS_MOVIE_FILE(extName))
        return E_MPLAYER_TYPE_MOVIE;
    else if(IS_TXT_FILE(extName))
        return E_MPLAYER_TYPE_TEXT;
    else
        return E_MPLAYER_TYPE_INVALID;
}
#endif
#if ENABLE_LAST_MEMORY==1
U8 MApp_MPlayer_LastMemory_Info_Get(U16 InfoIndex, stLastMemoryInfo** ppLastMemInfo)
{
    U8 ret;

    if (InfoIndex>=LAST_MEMORY_FILENUMBER)
    {
        *ppLastMemInfo= NULL;
        ret = FALSE;
    }
    else
    //if (index<LAST_MEMORY_FILENUMBER)
    {
        #if ENABLE_LAST_MEMORY_STORAGE_SAVE==1
        *ppLastMemInfo = &stGenSetting.g_MmLastMemorySetting.m_LastMemoryInfo[InfoIndex];
        #else
        *ppLastMemInfo = &m_LastMemoryInfo[InfoIndex];
        #endif
        ret = TRUE;
    }

    return ret;
}

U8 MApp_MPlayer_LastMemory_Info_Save(U16 InfoIndex, stLastMemoryInfo* pLastMemInfo)
{
    U8 ret;

    if (InfoIndex>=LAST_MEMORY_FILENUMBER)
    {
        ret = FALSE;
    }
    else
    //if (index<LAST_MEMORY_FILENUMBER)
    {
        #if ENABLE_LAST_MEMORY_STORAGE_SAVE==1
        memcpy(&stGenSetting.g_MmLastMemorySetting.m_LastMemoryInfo[InfoIndex], pLastMemInfo, sizeof(stLastMemoryInfo));
        #else
        memcpy(&m_LastMemoryInfo[InfoIndex], pLastMemInfo, sizeof(stLastMemoryInfo));
        #endif
        ret = TRUE;
    }

    return ret;
}

U8 MApp_MPlayer_LastMemory_Info_Update(U16 InfoIndex, U8 enable, stLastMemoryAttribute stLastMemAttr)
{
    U8 ret;
    stLastMemoryInfo tmpLastMemInfo;
    stLastMemoryInfo* pLastMemInfo;

    #if ENABLE_LAST_MEMORY_DEBUG==1
    MPLAYER_DBG(printf("LastMemory info update, idx=%d, enable=%d, pos=0x%x%x, pts=%dms\n", InfoIndex, enable, stLastMemAttr.u32LastMemorySeekPosH, stLastMemAttr.u32LastMemorySeekPosL, stLastMemAttr.u32LastMemorySeekPTS););
    #endif

    if (InfoIndex>=LAST_MEMORY_FILENUMBER)
    {
        ret = FALSE;
    }
    else
    //if (index<LAST_MEMORY_FILENUMBER)
    {
        MApp_MPlayer_LastMemory_Info_Get(InfoIndex, &pLastMemInfo);
        memcpy((U8*)&tmpLastMemInfo, (U8*)pLastMemInfo, sizeof(stLastMemoryInfo));
        memcpy((U8*)&tmpLastMemInfo.stLastMemAttribute, (U8*)&stLastMemAttr, sizeof(stLastMemoryAttribute));

        //tmpLastMemInfo.u8LastMemoryEnable = enable;
        UNUSED(enable);
        MApp_MPlayer_LastMemory_Info_Save(InfoIndex, &tmpLastMemInfo);
        ret = TRUE;
    }

    return ret;
}

U8 MApp_MPlayer_LastMemory_FileMatch_Entry(LastMemoryFileEntry* pFileEntry_db, FileEntry* pFileEntry_cur)
{
#if (OBA2 == 1)
    if ((strcmp(pFileEntry_db->fullname, pFileEntry_cur->fullname)==0)&&
        (pFileEntry_db->FileSystemID==pFileEntry_cur->FileSystemID))//drive id
        return TRUE;
#else
    U32 firstcluster_db, firstcluster_cur;

    memcpy( (U8*)&firstcluster_db, (U8*)&(pFileEntry_db->EntryID[0]), 4 );
    memcpy( (U8*)&firstcluster_cur, (U8*)&(pFileEntry_cur->EntryID[0]), 4 );
    if ((firstcluster_db == firstcluster_cur)&&
        (pFileEntry_db->FileSystemID==pFileEntry_cur->FileSystemID))//drive id
        return TRUE;
#endif

    return FALSE;
}

U8 MApp_MPlayer_LastMemory_OrderTbl_Get(U16** buf)
{
    #if ENABLE_LAST_MEMORY_STORAGE_SAVE==1
    *buf = &stGenSetting.g_MmLastMemorySetting.m_LastMemoryOrderTbl[0];
    #else
    *buf = m_LastMemoryOrderTbl;
    #endif

    return TRUE;
}

U8 MApp_MPlayer_LastMemory_OrderTbl_Save(U16* buf)
{
    #if ENABLE_LAST_MEMORY_STORAGE_SAVE==1
    memcpy((U8*)&stGenSetting.g_MmLastMemorySetting.m_LastMemoryOrderTbl[0], (U8*)buf, sizeof(U16)*LAST_MEMORY_FILENUMBER);
    #else
    memcpy((U8*)m_LastMemoryOrderTbl, (U8*)buf, sizeof(U16)*LAST_MEMORY_FILENUMBER);
    #endif

    return TRUE;
}

//mode--0:del, 1:add
U8 MApp_MPlayer_LastMemory_OrderTbl_Rearrange(U8 del_add, U16 IndexToModify, U16* buf)
{
    U16 CurOrder=LAST_MEMORY_ORDER_NONE, tmp;
    U16 i, ordervalue, validcnt=0;
    U8 resorting=0;

    for (i=0; i<LAST_MEMORY_FILENUMBER; i++)
    {
        tmp = buf[i];
        if ((tmp>=LAST_MEMORY_ORDER_MINIMUM)&&(tmp<=LAST_MEMORY_ORDER_MAXIMUM))
            validcnt++;
    }

    CurOrder = buf[IndexToModify];
    if ((CurOrder>=LAST_MEMORY_ORDER_MINIMUM)&&(CurOrder<=LAST_MEMORY_ORDER_MAXIMUM))
    {
        resorting=1;
    }

    if (resorting==1)
    {
        for (i=0; i<LAST_MEMORY_FILENUMBER; i++)
        {
            tmp = buf[i];
            //if ((tmp!=LAST_MEMORY_ORDER_NONE)&&(tmp>CurOrder))
            if ((tmp>LAST_MEMORY_ORDER_MINIMUM)&&(tmp<=LAST_MEMORY_ORDER_MAXIMUM)&&(tmp>CurOrder))
            {
                tmp--;
                buf[i] = tmp;
            }
        }
    }

    if (del_add==0)//del
    {
        ordervalue = LAST_MEMORY_ORDER_NONE;
    }
    else//add
    {
        if (resorting==1)
            ordervalue = validcnt;
        else
            ordervalue = validcnt+1;
    }
    buf[IndexToModify]= ordervalue;

    return TRUE;
}


//mode -- 0:del entry, 1:add new entry, 2:touch entry
U8 MApp_MPlayer_LastMemory_OrderTbl_Update(U8 mode, U16 Index_Del_Touch, U16* Index_Add)
{
    U16 i, tmp;
    U16* pOrderTbl;
    U16 empty_found=0, empty_idx=0;
    U16 minorder_idx=0;
    //U16 minorder=(U16)(LAST_MEMORY_ORDER_MAXIMUM);


    MApp_MPlayer_LastMemory_OrderTbl_Get(&pOrderTbl);

    #if ENABLE_LAST_MEMORY_DEBUG==1
    MPLAYER_DBG(printf("LastMemory order table update, Del(0)Add(1)Touch(2)=%d, Index=%d\n", mode, Index_Del_Touch););
    MPLAYER_DBG(printf("m_LastMemoryOrderTbl="););
    for (i=0; i<LAST_MEMORY_FILENUMBER; i++)
    {
        MPLAYER_DBG(printf("%d, ", pOrderTbl[i]););
    }
    MPLAYER_DBG(printf("\n"););
    #endif

    if (mode==0)//to del one LastMemory info entry
    {
        MApp_MPlayer_LastMemory_OrderTbl_Rearrange(0, Index_Del_Touch, pOrderTbl);
    }
    else if (mode==2)//to touch one LastMemory info entry
    {
        MApp_MPlayer_LastMemory_OrderTbl_Rearrange(1, Index_Del_Touch, pOrderTbl);
    }
    else//to add one LastMemory info entry
    {
        //check entry to add
        for (i=0; i<LAST_MEMORY_FILENUMBER; i++)
        {
            tmp = pOrderTbl[i];
            if ((tmp<LAST_MEMORY_ORDER_MINIMUM)||(tmp>LAST_MEMORY_ORDER_MAXIMUM))
            {
                empty_found = 1;
                empty_idx = i;
                break;
            }
#if 0
            else
            {
                if (tmp<minorder)
                {
                    minorder = tmp;
                    minorder_idx = i;
                }
            }
#endif
        }
        if (empty_found==1)//there is empty entry
        {
            MApp_MPlayer_LastMemory_OrderTbl_Rearrange(1, empty_idx, pOrderTbl);
            *Index_Add = empty_idx;
        }
        else//no empty entry
        {
            MApp_MPlayer_LastMemory_OrderTbl_Rearrange(1, minorder_idx, pOrderTbl);
            *Index_Add = minorder_idx;
            #if ENABLE_LAST_MEMORY_DEBUG==1
            MPLAYER_DBG(printf("LastMemory, order table full\n"););
            #endif
        }
        #if ENABLE_LAST_MEMORY_DEBUG==1
        MPLAYER_DBG(printf("LastMemory, order table add idx=%d\n", *Index_Add););
        #endif
    }

    MApp_MPlayer_LastMemory_OrderTbl_Save(pOrderTbl);

    #if ENABLE_LAST_MEMORY_DEBUG==1
    MPLAYER_DBG(printf("m_LastMemoryOrderTbl="););
    for (i=0; i<LAST_MEMORY_FILENUMBER; i++)
    {
        MPLAYER_DBG(printf("%d, ", pOrderTbl[i]););
    }
    MPLAYER_DBG(printf("\n"););
    #endif

    return TRUE;
}

U8 MApp_MPlayer_LastMemory_Search(FileEntry* pFileEntry)
{
    U8 ret=FALSE;
    FileEntry tmpEntry;
    stLastMemoryInfo* pLastMemInfo;
    stLastMemoryInfo tmpLastMemInfo;
    stLastMemoryAttribute *pstAttribute;
    stLastMemoryAttribute stZeroMemoryAttr;
    memset(&stZeroMemoryAttr, 0, sizeof(stLastMemoryAttribute));

    U16 i, idx_to_add;
    U16* pOrderTbl;

    idx_to_add = 0;//init value

#if(ENABLE_LAST_MEMORY_DEBUG==1)
    MPLAYER_DBG(printf("FSid, u16DriveID = %d\n", pFileEntry->FileSystemID););
#endif

    m_u32LastMemoryCurIdx = 0xFFFF;

    memcpy((U8*)&tmpEntry, (U8*)pFileEntry, sizeof(FileEntry));
    #if 0//ENABLE_LAST_MEMORY_DEBUG==1
    MPLAYER_DBG(printf("EntryAttrib = 0x%x\n", tmpEntry.EntryAttrib););
    MPLAYER_DBG(printf("EntrySeconds = 0x%x\n", tmpEntry.EntrySeconds););
    MPLAYER_DBG(printf("EntryFileLength = 0x%x\n", tmpEntry.EntryFileLength););
    MPLAYER_DBG(printf("FileLength = 0x%x\n", tmpEntry.FileLength););
    MPLAYER_DBG(printf("EntryType = 0x%x\n", tmpEntry.EntryType););
    MPLAYER_DBG(printf("EntryID[0] = 0x%x%x%x%x\n", tmpEntry.EntryID[3], tmpEntry.EntryID[2], tmpEntry.EntryID[1], tmpEntry.EntryID[0]););
    MPLAYER_DBG(printf("EntryID[4] = 0x%x%x%x%x\n", tmpEntry.EntryID[7], tmpEntry.EntryID[6], tmpEntry.EntryID[5], tmpEntry.EntryID[4]););
    MPLAYER_DBG(printf("EnvironmentID = 0x%x\n", tmpEntry.EnvironmentID););
    MPLAYER_DBG(printf("FileSystemID = 0x%x\n", tmpEntry.FileSystemID););
    MPLAYER_DBG(printf("EntryID_Ext[0] = 0x%x%x%x%x\n", tmpEntry.EntryID_Ext[3], tmpEntry.EntryID_Ext[2], tmpEntry.EntryID_Ext[1], tmpEntry.EntryID_Ext[0]););
    MPLAYER_DBG(printf("EntryID_Ext[4] = 0x%x%x%x%x\n", tmpEntry.EntryID_Ext[7], tmpEntry.EntryID_Ext[6], tmpEntry.EntryID_Ext[5], tmpEntry.EntryID_Ext[4]););
    #endif

#if ENABLE_LAST_MEMORY_STORAGE_SAVE==1
    MApp_MPlayer_LastMemory_Storage_Read();
#endif

    MApp_MPlayer_LastMemory_OrderTbl_Get(&pOrderTbl);

    //check invalid entry
    for (i=0; i<LAST_MEMORY_FILENUMBER; i++)
    {
        MApp_MPlayer_LastMemory_Info_Get(i, &pLastMemInfo);
        //if (pLastMemInfo->u8LastMemoryEnable)
        //if (pOrderTbl[i]!=LAST_MEMORY_ORDER_NONE)
        if ((pOrderTbl[i]>=LAST_MEMORY_ORDER_MINIMUM)&&
            (pOrderTbl[i]<=LAST_MEMORY_ORDER_MAXIMUM))
        {
            if (pLastMemInfo->stLastMemAttribute.u32LastMemorySeekPTS==0)
            {
                //invalid seek PTS, del this entry
                MApp_MPlayer_LastMemory_OrderTbl_Update(0, i, NULL);
                MApp_MPlayer_LastMemory_Info_Update(i, 0, stZeroMemoryAttr);
            }
        }
    }

    for (i=0; i<LAST_MEMORY_FILENUMBER; i++)
    {
        MApp_MPlayer_LastMemory_Info_Get(i, &pLastMemInfo);
        pstAttribute = &(pLastMemInfo->stLastMemAttribute);
        //if (pLastMemInfo->u8LastMemoryEnable)
        //if (pOrderTbl[i]!=LAST_MEMORY_ORDER_NONE)
        if ((pOrderTbl[i]>=LAST_MEMORY_ORDER_MINIMUM)&&
            (pOrderTbl[i]<=LAST_MEMORY_ORDER_MAXIMUM))
        {
            if (MApp_MPlayer_LastMemory_FileMatch_Entry(&(pLastMemInfo->fEntry), &tmpEntry)==TRUE)
            {
                m_u32LastMemorySeekPosL = pstAttribute->u32LastMemorySeekPosL;
                m_u32LastMemorySeekPosH = pstAttribute->u32LastMemorySeekPosH;
                m_u32LastMemorySeekPTS = pstAttribute->u32LastMemorySeekPTS;
                m_u16LastMemoryAudioTrack = pstAttribute->u16LastAudioTrack;
            #if ENABLE_SUBTITLE_DMP
                m_u16LastMemorySubtitleTrack = pstAttribute->u16LastSubtitleTrack;
                m_bLastMemorySubtitleShow = pstAttribute->bSubtitleShow;
            #endif
                m_u32LastMemoryCurIdx = i;
                MApp_MPlayer_LastMemory_OrderTbl_Update(2, i, NULL);

#if ENABLE_LAST_MEMORY_STORAGE_SAVE==1
                MApp_MPlayer_LastMemory_Storage_Write();
#endif
                #if ENABLE_LAST_MEMORY_DEBUG==1
                MPLAYER_DBG(printf("LastMemory, Search hit, idx=%d, pos=0x%x%x, pts=%dms\n", i, m_u32LastMemorySeekPosH, m_u32LastMemorySeekPosL, m_u32LastMemorySeekPTS););
                #endif
                return TRUE;
            }
        }
    }


    //no LastMemory entry found, add new entry
    MApp_MPlayer_LastMemory_OrderTbl_Update(1, 0, &idx_to_add);

    m_u32LastMemorySeekPosL = 0;
    m_u32LastMemorySeekPosH = 0;
    m_u32LastMemorySeekPTS= 0;
    m_u16LastMemoryAudioTrack = 0;
#if ENABLE_SUBTITLE_DMP
    m_u16LastMemorySubtitleTrack = 0;
    m_bLastMemorySubtitleShow = FALSE;
#endif
    memset((U8*)(&tmpLastMemInfo), 0, sizeof(tmpLastMemInfo));

    tmpLastMemInfo.fEntry.EntryType = tmpEntry.EntryType;
    tmpLastMemInfo.fEntry.FileLength = tmpEntry.FileLength.Lo;
    tmpLastMemInfo.fEntry.EntryFileLength = tmpEntry.EntryFileLength;
    tmpLastMemInfo.fEntry.EntrySeconds = tmpEntry.EntrySeconds;
    #if (OBA2 == 1)
    tmpLastMemInfo.fEntry.st_mode = tmpEntry.st_mode;
    memcpy(tmpLastMemInfo.fEntry.fullname, tmpEntry.fullname, sizeof(tmpLastMemInfo.fEntry.fullname));
    #else
    memcpy(tmpLastMemInfo.fEntry.EntryID, tmpEntry.EntryID, 8);
    memcpy(tmpLastMemInfo.fEntry.EntryID_Ext, tmpEntry.EntryID_Ext, 8);
    #endif
    tmpLastMemInfo.fEntry.EnvironmentID = tmpEntry.EnvironmentID;
    tmpLastMemInfo.fEntry.FileSystemID = tmpEntry.FileSystemID;
    tmpLastMemInfo.fEntry.EntryAttrib = tmpEntry.EntryAttrib;
    //tmpLastMemInfo.u8LastMemoryEnable = 0;//init to be 0, after play start with pos/pts available, then set to 1,
    MApp_MPlayer_LastMemory_Info_Save(idx_to_add, &tmpLastMemInfo);
    m_u32LastMemoryCurIdx = idx_to_add;

#if ENABLE_LAST_MEMORY_STORAGE_SAVE==1
    MApp_MPlayer_LastMemory_Storage_Write();
#endif

    #if ENABLE_LAST_MEMORY_DEBUG==1
    MPLAYER_DBG(printf("first time play, save info to idx=%d\n", idx_to_add););
    #endif

    #if 0//ENABLE_LAST_MEMORY_DEBUG==1
    MApp_MPlayer_LastMemory_Info_Get(idx_to_add, &pLastMemInfo);
    memcpy((U8*)&tmpEntry, (U8*)&(pLastMemInfo->fileEntry), sizeof(FileEntry));
    MPLAYER_DBG(printf("EntryAttrib = 0x%x\n", tmpEntry.EntryAttrib););
    MPLAYER_DBG(printf("EntrySeconds = 0x%x\n", tmpEntry.EntrySeconds););
    MPLAYER_DBG(printf("EntryFileLength = 0x%x\n", tmpEntry.EntryFileLength););
    MPLAYER_DBG(printf("FileLength = 0x%x\n", tmpEntry.FileLength););
    MPLAYER_DBG(printf("EntryType = 0x%x\n", tmpEntry.EntryType););
    MPLAYER_DBG(printf("EntryID[0] = 0x%x%x%x%x\n", tmpEntry.EntryID[3], tmpEntry.EntryID[2], tmpEntry.EntryID[1], tmpEntry.EntryID[0]););
    MPLAYER_DBG(printf("EntryID[4] = 0x%x%x%x%x\n", tmpEntry.EntryID[7], tmpEntry.EntryID[6], tmpEntry.EntryID[5], tmpEntry.EntryID[4]););
    MPLAYER_DBG(printf("EnvironmentID = 0x%x\n", tmpEntry.EnvironmentID););
    MPLAYER_DBG(printf("FileSystemID = 0x%x\n", tmpEntry.FileSystemID););
    MPLAYER_DBG(printf("EntryID_Ext[0] = 0x%x%x%x%x\n", tmpEntry.EntryID_Ext[3], tmpEntry.EntryID_Ext[2], tmpEntry.EntryID_Ext[1], tmpEntry.EntryID_Ext[0]););
    MPLAYER_DBG(printf("EntryID_Ext[4] = 0x%x%x%x%x\n", tmpEntry.EntryID_Ext[7], tmpEntry.EntryID_Ext[6], tmpEntry.EntryID_Ext[5], tmpEntry.EntryID_Ext[4]););
    #endif

    return ret;
}

U8 MApp_MPlayer_LastMemory_SetResumePlayAttribute(U8 clear)
{
    enumMPlayerMediaType eMediaType;
    U32 TotalTime;
    stLastMemoryAttribute stLastMemoryAttr;
    memset(&stLastMemoryAttr, 0, sizeof(stLastMemoryAttribute));

#if ENABLE_LAST_MEMORY_STORAGE_SAVE==1
    MApp_MPlayer_LastMemory_Storage_Read();
#endif
    eMediaType = MApp_MPlayer_QueryCurrentMediaType();

#if ENABLE_MPLAYER_MOVIE
    if (eMediaType==E_MPLAYER_TYPE_MOVIE)
    {
        if (clear)
        {
            //error or play to end, clear entry
            #if ENABLE_LAST_MEMORY_DEBUG==1
            MPLAYER_DBG(printf("SetCurrentPos, LastMemory, clear, idx=%d\n", m_u32LastMemoryCurIdx));
            #endif
            //clean LastMemory for this file
            MApp_MPlayer_LastMemory_OrderTbl_Update(0, m_u32LastMemoryCurIdx, NULL);
            MApp_MPlayer_LastMemory_Info_Update(m_u32LastMemoryCurIdx, 0, stLastMemoryAttr);
        }
        else
        {
            TotalTime = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_TOTAL_TIME);
            //CurTime = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CUR_TIME);
            stLastMemoryAttr.u32LastMemorySeekPosL = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_RESUME_PLAY_SEEKPOS_LOW);
            stLastMemoryAttr.u32LastMemorySeekPosH = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_RESUME_PLAY_SEEKPOS_HIGH);
            stLastMemoryAttr.u32LastMemorySeekPTS = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_RESUME_PLAY_SEEKPTS);
            #if ENABLE_LAST_MEMORY_DEBUG==1
            MPLAYER_DBG(printf("SetCurrentPos, LastMemory, idx=%d, pos=0x%x%x, seek pts=%dms\n", m_u32LastMemoryCurIdx, SeekPosH, SeekPosL, SeekPTS));
            #endif
            if (((stLastMemoryAttr.u32LastMemorySeekPosL != 0)
               ||(stLastMemoryAttr.u32LastMemorySeekPosH != 0)
               ||(stLastMemoryAttr.u32LastMemorySeekPTS != 0))
                /*&& (SeekPTS<TotalTime)*/)
            {
                //save last pos/pts into LastMemory
                stLastMemoryAttr.u16LastAudioTrack = MApp_MPlayer_QueryMovieCurAudioTrackIdx();
            #if ENABLE_SUBTITLE_DMP
                stLastMemoryAttr.u16LastSubtitleTrack = MApp_MPlayer_QueryMovieCurSubtitleTrackIdx();
                stLastMemoryAttr.bSubtitleShow = (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_SUBTITLE_ENABLE)? TRUE:FALSE;
            #endif
                MApp_MPlayer_LastMemory_Info_Update(m_u32LastMemoryCurIdx, 1, stLastMemoryAttr);
            }
            else
            {
                //MApp_MPlayer_LastMemory_OrderTbl_Update(0, m_u32LastMemoryCurIdx, NULL);
                //MApp_MPlayer_LastMemory_Info_Update(m_u32LastMemoryCurIdx, 0, 0, 0, 0);
            }
        }
    }
#endif

#if ENABLE_MPLAYER_MUSIC
    if (eMediaType==E_MPLAYER_TYPE_MUSIC)
    {
        if (clear)
        {
            //error or play to end, clear entry
            #if ENABLE_LAST_MEMORY_DEBUG==1
            MPLAYER_DBG(printf("SetCurrentPos, LastMemory, clear, idx=%d\n", m_u32LastMemoryCurIdx));
            #endif
            //clean LastMemory for this file
            MApp_MPlayer_LastMemory_OrderTbl_Update(0, m_u32LastMemoryCurIdx, NULL);
            MApp_MPlayer_LastMemory_Info_Update(m_u32LastMemoryCurIdx, 0, stLastMemoryAttr);
        }
        else
        {
            TotalTime = MApp_MPlayer_QueryMusicFilePlayTime()*1000;
            stLastMemoryAttr.u32LastMemorySeekPTS = MApp_MPlayer_QueryMusicFileCurrentTime()*1000;
            #if ENABLE_LAST_MEMORY_DEBUG==1
            MPLAYER_DBG(printf("SetCurrentPos, LastMemory, idx=%d, CurTime=%dms, TotalTime=%dms\n", m_u32LastMemoryCurIdx, SeekPTS, TotalTime));
            #endif
            if (stLastMemoryAttr.u32LastMemorySeekPTS<TotalTime)
            {
                //save last pos/pts into LastMemory
                MApp_MPlayer_LastMemory_Info_Update(m_u32LastMemoryCurIdx, 1, stLastMemoryAttr);
            }
            else
            {
                //MApp_MPlayer_LastMemory_OrderTbl_Update(0, m_u32LastMemoryCurIdx, NULL);
                //MApp_MPlayer_LastMemory_Info_Update(m_u32LastMemoryCurIdx, 0, 0, 0, 0);
            }
        }
    }
#endif

#if ENABLE_LAST_MEMORY_STORAGE_SAVE==1
    MApp_MPlayer_LastMemory_Storage_Write();
#endif

    return TRUE;
}

U8 MApp_MPlayer_LastMemory_GetResumePos(U32* pTimeMs, U32* pPosL, U32* pPosH)
{
    enumMPlayerMediaType eMediaType;

    eMediaType = MApp_MPlayer_QueryCurrentMediaType();
#if ENABLE_MPLAYER_MOVIE
    if (eMediaType==E_MPLAYER_TYPE_MOVIE)
    {
        *pTimeMs = m_u32LastMemorySeekPTS;
        if (pPosL)
            *pPosL = m_u32LastMemorySeekPosL;
        if (pPosH)
            *pPosH = m_u32LastMemorySeekPosH;
    }
#endif
#if ENABLE_MPLAYER_MUSIC
    if (eMediaType==E_MPLAYER_TYPE_MUSIC)
    {
        *pTimeMs = m_u32LastMemorySeekPTS;
        if (pPosL)
            *pPosL = 0;
        if (pPosH)
            *pPosH = 0;
    }
#endif
    return TRUE;
}

BOOLEAN MApp_MPlayer_LastMemory_GetResumePlayInfo(stLastMemoryInfo* pstLastMemoryInfo)
{
    if(pstLastMemoryInfo == NULL)
    {
        return FALSE;
    }

    enumMPlayerMediaType eMediaType;
    stLastMemoryAttribute *pstAttribute;

    pstAttribute = &(pstLastMemoryInfo->stLastMemAttribute);

    eMediaType = MApp_MPlayer_QueryCurrentMediaType();
#if ENABLE_MPLAYER_MOVIE
    if (eMediaType==E_MPLAYER_TYPE_MOVIE)
    {
        pstAttribute->u32LastMemorySeekPTS = m_u32LastMemorySeekPTS;
        pstAttribute->u32LastMemorySeekPosL = m_u32LastMemorySeekPosL;
        pstAttribute->u32LastMemorySeekPosH = m_u32LastMemorySeekPosH;
        pstAttribute->u16LastAudioTrack = m_u16LastMemoryAudioTrack;
    #if ENABLE_SUBTITLE_DMP
        pstAttribute->u16LastSubtitleTrack = m_u16LastMemorySubtitleTrack;
        pstAttribute->bSubtitleShow = m_bLastMemorySubtitleShow;
    #endif
    }
#endif
#if ENABLE_MPLAYER_MUSIC
    if (eMediaType==E_MPLAYER_TYPE_MUSIC)
    {
        pstAttribute->u32LastMemorySeekPTS = m_u32LastMemorySeekPTS;
        pstAttribute->u32LastMemorySeekPosL = 0;
        pstAttribute->u32LastMemorySeekPosH = 0;
        pstAttribute->u16LastAudioTrack = 0;
    #if ENABLE_SUBTITLE_DMP
        pstAttribute->u16LastSubtitleTrack = 0;
        pstAttribute->bSubtitleShow = FALSE;
    #endif
    }
#endif
    return TRUE;
}

#if ENABLE_LAST_MEMORY_STORAGE_SAVE==1
U8 MApp_MPlayer_LastMemory_Storage_Read(void)
{
    #if 0
    if ((m_u8LastMemoryInfoInited==FALSE)||(m_u8LastMemoryOrderTblInited==FALSE))
    {
        //read from storage
        //m_LastMemoryInfo[LAST_MEMORY_FILENUMBER];
        //m_LastMemoryOrderTbl[LAST_MEMORY_FILENUMBER];

        m_u8LastMemoryInfoInited=TRUE;
        m_u8LastMemoryOrderTblInited=TRUE;
    }
    #endif

    return TRUE;
}

U8 MApp_MPlayer_LastMemory_Storage_Write(void)
{
    #if 0
    //save to storage
    //m_LastMemoryInfo[LAST_MEMORY_FILENUMBER];
    //m_LastMemoryOrderTbl[LAST_MEMORY_FILENUMBER];
    #endif

    return TRUE;
}
#endif
#endif//#if ENABLE_LAST_MEMORY==1

void MApp_MPlayer_SetSubtitleCharsetType(enumSubtitleCharsetType enType)
{
    m_enSubtitleCharsetType = enType;
}

enumSubtitleCharsetType MApp_MPlayer_GetSubtitleCharsetType(void)
{
    return m_enSubtitleCharsetType;
}

void MApp_MPlayer_SetTextCharsetType(enumTextCharsetType enType)
{
    MApp_Text_SetTextCharsetType(enType);
}

enumTextCharsetType MApp_MPlayer_GetTextCharsetType(void)
{
    return MApp_Text_GetTextCharsetType();
}

#if (SUPPERTED_SEAMLESS_SMOTH)
#define SEAMLESS_MAX_HANDLE_NUM         4

static U8 _s_u8FileHdl[SEAMLESS_MAX_HANDLE_NUM];
static U32 _s_u32filepos[SEAMLESS_MAX_HANDLE_NUM];
static U32 _s_u32filesize[SEAMLESS_MAX_HANDLE_NUM];

BOOLEAN MApi_Seamless_Stream_Init(void)
{
    U8 u8Idx = 0;
    for(u8Idx = 0; u8Idx < SEAMLESS_MAX_HANDLE_NUM; u8Idx++)
    {
        _s_u8FileHdl[u8Idx] = INVALID_FILE_HANDLE;
        _s_u32filepos[u8Idx] = 0;
        _s_u32filesize[u8Idx] = 0;
    }

    return TRUE;
}

U32 MApi_Seamless_Stream_Open(void *pPrivate, U8 u8Mode, E_DATA_STREAM_TYPE eType)
{
    U8 u8Idx = 0;
    LongLong u64FileLength;

    for(u8Idx = 0; u8Idx < SEAMLESS_MAX_HANDLE_NUM; u8Idx++)
    {
        if(_s_u8FileHdl[u8Idx] == INVALID_FILE_HANDLE)
        {
            break;
        }
    }

    if(u8Idx == SEAMLESS_MAX_HANDLE_NUM)
    {
        printf("[Seamless_Stream_Open] fail, the seamless file handle space is full\n");
        return INVALID_FILE_HANDLE;
    }

    eType = eType;
    _s_u8FileHdl[u8Idx] = msAPI_FCtrl_FileOpen((FileEntry *)pPrivate, u8Mode);
    if (_s_u8FileHdl[u8Idx] != INVALID_FILE_HANDLE)
    {
        u64FileLength = msAPI_FCtrl_FileLength_LongLong(_s_u8FileHdl[u8Idx]);
        _s_u32filepos[u8Idx] = 0;
        _s_u32filesize[u8Idx] = u64FileLength.Lo;
    }

    return _s_u8FileHdl[u8Idx];
}

BOOLEAN MApi_Seamless_Stream_Close(U32 u32Hdl)
{
    U8 u8Idx = 0;;

    if(u32Hdl != INVALID_FILE_HANDLE)
    {
        for(u8Idx = 0; u8Idx < SEAMLESS_MAX_HANDLE_NUM; u8Idx++)
        {
            if(_s_u8FileHdl[u8Idx] == u32Hdl)
            {
                break;
            }
        }

        if(u8Idx == SEAMLESS_MAX_HANDLE_NUM)
        {
            printf("[Seamless_Stream_Close] fail, Wrong file handle:%d\n",u32Hdl);
            return FALSE;
        }

        if(msAPI_FCtrl_FileClose(_s_u8FileHdl[u8Idx]) == FILE_CLOSE_RESULT_ERROR)
        {
            _s_u8FileHdl[u8Idx] = INVALID_FILE_HANDLE;
            printf("[Seamless_Stream_Close] file close fail\n");
            return FALSE;
        }
        else
        {
            _s_u8FileHdl[u8Idx] = INVALID_FILE_HANDLE;
            return TRUE;
        }
    }
    else
    {
        return FALSE;
    }
}

LongLong MApi_Seamless_Stream_Length(U32 u32Hdl)
{
    LongLong ret;

    u32Hdl = u32Hdl;
    ret.Hi = 0xFFFFFFFF;
    ret.Lo = 0xFFFFFFFF;
    return ret;
}

U32 MApi_Seamless_Stream_Read(U32 u32Hdl, void *pBuffAddr, U32 u32Length)
{
    U32 retsize, readsize;
    LongLong u64FileLength;
    U8 u8Idx = 0;
    U8 u8CurIdx = 0;

    if (u32Hdl != INVALID_FILE_HANDLE)
    {
        for(u8CurIdx = 0; u8CurIdx < SEAMLESS_MAX_HANDLE_NUM; u8CurIdx++)
        {
            if(_s_u8FileHdl[u8CurIdx] == u32Hdl)
            {
                break;
            }
        }

        if(u8CurIdx == SEAMLESS_MAX_HANDLE_NUM)
        {
            printf("[Seamless_Stream_Read] wrong file handle:%d\n",u32Hdl);
            return FALSE;
        }

        retsize = msAPI_FCtrl_FileRead(_s_u8FileHdl[u8CurIdx], (U32)pBuffAddr, u32Length);
        readsize = u32Length - retsize;
        _s_u32filepos[u8CurIdx] += readsize;
        if (_s_u32filepos[u8CurIdx] >= _s_u32filesize[u8CurIdx])
        {
            enumMPlayerKnlFlags1 eKnlFlag1;

            for(u8Idx = 0; u8Idx < SEAMLESS_MAX_HANDLE_NUM; u8Idx++)
            {
                msAPI_FCtrl_FileClose(_s_u8FileHdl[u8Idx]);
                _s_u8FileHdl[u8Idx] = INVALID_FILE_HANDLE;
            }
            eKnlFlag1 = m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1;
            if(_MApp_MPlayer_PlayNext(E_MPLAYER_FOREGROUND_PLAYER))
            {
                m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 = eKnlFlag1;
                //Need to refine: if a new file handle is created, the new file handles are not the same as formers.
                for(u8Idx = 0; u8Idx < SEAMLESS_MAX_HANDLE_NUM; u8Idx++)
                {
                    _s_u8FileHdl[u8Idx] = msAPI_FCtrl_FileOpen(&m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].curPlayingFileEntry, OPEN_MODE_FOR_READ);
                }
                u64FileLength = msAPI_FCtrl_FileLength_LongLong(_s_u8FileHdl[u8CurIdx]);
                _s_u32filepos[u8CurIdx] = 0;
                _s_u32filesize[u8CurIdx] = u64FileLength.Lo;
            }
            else
            {
                printf("[Seamless Play] Play next fail. Video force stop\n");
                MApp_VDPlayer_VideoForceFileEnd();
            }
        }
        return retsize;
    }
    else
    {
        return u32Length;
    }
}
#endif

#if SUPPORT_ONE_FILE_HANDLE_APP_BUT_DEMUX_USE_2_FILE_HANDLE
//******************************************************************************
/// Set Stream mode.
/// @param  bStreamMode \b IN  Specify Stream mode or not.
/// @return TRUE or FALSE
//******************************************************************************
BOOL MApp_MPlayer_SetStreamMode(BOOL bStreamMode)
{
    return MApp_VDPlayer_SetStreamMode(bStreamMode);
}
#endif

#if ENABLE_PROBE_MOVIE_HEADER
BOOLEAN MApp_MPlayer_ProbeMovieHeaderOnly(enumMPlayerFileIndexBegin eBegin, U16 u16FileIdx)
{
    BOOLEAN bRet;
    MPlayerFileInfo fileInfo;

    if(eBegin == E_MPLAYER_INDEX_CURRENT_PAGE)
    {
        u16FileIdx += m_u16CurPage1stFileIdx;
    }
    else if(eBegin != E_MPLAYER_INDEX_CURRENT_DIRECTORY)
    {
        return FALSE;
    }

    MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16FileIdx, &fileInfo);

    MApp_VDPlayer_BeginProbeHeaderOnly();

    bRet = MApp_VDPlayer_Init(VIDEO_PLAYER_INPUT_SOURCE_MM, VIDEO_PLAYER_PLAYING_TYPE_INVALID, &fileInfo.fileEntry);

    MApp_VDPlayer_Stop();
    MApp_VDPlayer_StopProbeHeaderOnly();

    return bRet;
}
#endif

//******************************************************************************
/// Query current directory path
/// @param  ptr \b OUT  Output current directory Path node.
/// @param  DirDepth \b IN  Specify the desire directory depth.
/// @return TRUE or FALSE
//******************************************************************************
BOOLEAN MApp_MPlayer_QueryDirectoryNode(U16 *ptr , U16 DirDepth)
{
    U16 i;

    MPLAYER_DBG(printf("---->DirDepth=%d \n",DirDepth));
    //If DirDepth < m_u16CurDirectoryDepth
    if(DirDepth <= m_u16CurDirectoryDepth)
    {
        for(i=0;i<DirDepth;i++)
        {
        #if ENABLE_MPLAYER_SORT
            ptr[i]=m_u16CurDirectoryPhy[i];
        #else
            ptr[i]=m_u16CurDirectory[i];
        #endif
        }
    }
    else//else DirDepth > m_u16CurDirectoryDepth
    {
        for(i=0;i<m_u16CurDirectoryDepth;i++)
        {
        #if ENABLE_MPLAYER_SORT
            ptr[i]=m_u16CurDirectoryPhy[i];
        #else
            ptr[i]=m_u16CurDirectory[i];
        #endif
        }

    }

#if 0//debug
            int jj;
            printf("        SLIDE SHOW DIR PATH = ");
            for(jj=0;jj<=m_u16CurDirectoryDepth;jj++)
            {
                printf("(%d) ",m_u16CurDirectory[jj]);
            }
            printf("\n\n");

            printf("        BACK SLIDE SHOW DIR PATH = ");
            for(jj=0;jj<=m_u16CurDirectoryDepth;jj++)
            {
                printf("(%d) ",ptr[jj]);
            }
            printf("\n\n");
#endif
    return TRUE;
}

#if ENABLE_EMBEDDED_PHOTO_DISPLAY
// NOTES:
// MApp_Photo_DataRequestCallBack is the callback function registered by caller of this module.
// This callback function will be called when MApp_Photo module requires more data to be filled by caller.
// It should return how many bytes of data actually read and a negative return value implies EOF
//******************************************************************************
/// Embedded photo data request callback function.
/// @param  pu8BufferAddr \b destination data address.
/// @param  u32RequestSize  \b request data size.
/// @return positive: actually read bytes , negative: EOF
//******************************************************************************
static S32 _MApp_MPlayer_EmbeddedPhoto_DataRequestCallBack(U8 *pu8BufferAddr, U32 u32RequestSize)
{
    #define EOF -1
    U32 u32PhysicalBufferAddr = _VA2PA((U32)pu8BufferAddr);
    U32 u32ReadSizeLeft = 0;
    U32 u32EmbeddedPhoto_EndPos = m_u32EmbeddedPhotoOffset + m_u32EmbeddedPhotoSize;
    U32 u32CurrentPos = msAPI_DataStreamIO_Tell(m_u32EmbeddedPhoto_FileHandle);

    if(u32CurrentPos >= u32EmbeddedPhoto_EndPos)
    {
        // end of file
        return EOF;
    }

    if (u32RequestSize == 0)
        return u32RequestSize;

    if (u32CurrentPos + u32RequestSize >= u32EmbeddedPhoto_EndPos)
    {
        // if we don't have enough data asked by JPD, we have to clear the buffer first or garbage will be left
        msAPI_Music_CleanFileEndData(u32PhysicalBufferAddr, u32RequestSize, 0x0UL);
        u32RequestSize = u32EmbeddedPhoto_EndPos - u32CurrentPos;
    }

    u32ReadSizeLeft = msAPI_DataStreamIO_Read(m_u32EmbeddedPhoto_FileHandle, (void*)u32PhysicalBufferAddr, u32RequestSize);

    return u32RequestSize - u32ReadSizeLeft;
}


// NOTES:
// MApp_MPlayer_MusicMetaData_Probe_ByPlayListIndex is a function that can show music meta data
// in a playlist such as duration without playing it.
//******************************************************************************
/// show music duration by the index in playlist.
/// @param  u16Index  \b index in playlist.
/// @param  *pstTempMplayerProbeInfo  \b meta data information.
/// @param  eMusicInfoType  \b meata data type.
/// @return TRUE: SUCCESS , FALSE: FAIL
//******************************************************************************
BOOLEAN MApp_MPlayer_MusicMetaData_Probe_ByPlayListIndex(U16 u16Index,ST_MPLAYER_PROBE_INFO *pstTempMplayerProbeInfo,EN_MUSIC_INFO eMusicInfoType)
{
    BOOLEAN bRet = FALSE;
    if(pstTempMplayerProbeInfo==NULL)
    {
        MPLAYER_DBG(printf("pstTempMplayerProbeInfo is NULL"));
        return FALSE;
    }
    if(m_u16SelectedFileNum[E_MPLAYER_TYPE_MUSIC] <= u16Index)
    {
        return FALSE;
    }

    MPlayerFileInfo fileInfo;
    memset(&fileInfo,0,sizeof(MPlayerFileInfo));

    MPlayerPlayListInfo *pstPlayListInfo = NULL;
    U32 u32XdataWindowBase;

    if(_MApp_MPlayer_GetPlayListAddressByMediaType(E_MPLAYER_TYPE_MUSIC, &u32XdataWindowBase)==FALSE)
    {
        return FALSE;
    }

    pstPlayListInfo = (MPlayerPlayListInfo *) (_PA2VA(u32XdataWindowBase));

    memcpy(&fileInfo.u8ExtFileName, &pstPlayListInfo[u16Index].u8ExtName,sizeof(fileInfo.u8ExtFileName));
    memcpy(&fileInfo.fileEntry, &pstPlayListInfo[u16Index].fileEntry,sizeof(FileEntry));

    bRet = _MApp_MPlayer_MusicMetaData_Probe(fileInfo, pstTempMplayerProbeInfo, eMusicInfoType);
    MPLAYER_DBG(printf("u16Index: %d  pstTempMplayerProbeInfo->u32Duration: %lu\n",u16Index,pstTempMplayerProbeInfo->u32Duration));
    MPLAYER_DBG(printf("u16BitRate:%d  u32SampleRate:%d \n",pstTempMplayerProbeInfo->u16BitRate,pstTempMplayerProbeInfo->u32SampleRate));
    MPLAYER_DBG(printf("pstTempMplayerProbeInfo->u32PicOffset:%lu   u32PicSize:%lu\n\n",pstTempMplayerProbeInfo->u32PicOffset,pstTempMplayerProbeInfo->u32PicSize));
    return bRet;


}


// NOTES:
// MApp_MPlayer_MusicMetaData_Probe_ByDirectoryIndex is a function that can show music meta data
// such as duration without playing it.
//******************************************************************************
/// show music duration by the index in directory.
/// @param  eBegin \b where file index begin.
/// @param  u16Index  \b file index.
/// @param  *pstTempMplayerProbeInfo  \b meta data information.
/// @param  eMusicInfoType  \b meata data type.
/// @return TRUE: SUCCESS , FALSE: FAIL
//******************************************************************************
BOOLEAN MApp_MPlayer_MusicMetaData_Probe_ByDirectoryIndex(enumMPlayerFileIndexBegin eBegin,U16 u16Index,ST_MPLAYER_PROBE_INFO *pstTempMplayerProbeInfo,EN_MUSIC_INFO eMusicInfoType)
{
    BOOLEAN bRet = FALSE;
    if(pstTempMplayerProbeInfo==NULL)
    {
        MPLAYER_DBG(printf("pstTempProbeInfo is NULL"));
        return FALSE;
    }


    MPlayerFileInfo fileInfo;
    memset(&fileInfo,0,sizeof(MPlayerFileInfo));

    if(MApp_MPlayer_QueryFileInfo(eBegin,u16Index,&fileInfo) == E_MPLAYER_RET_OK)
    {
        bRet = _MApp_MPlayer_MusicMetaData_Probe(fileInfo, pstTempMplayerProbeInfo, eMusicInfoType);
        MPLAYER_DBG(printf("u16Index: %d  pstTempProbeInfo->u32Duration: %lu\n",u16Index,pstTempMplayerProbeInfo->u32Duration));
        MPLAYER_DBG(printf("u16BitRate:%d  u32SampleRate:%d \n",pstTempMplayerProbeInfo->u16BitRate,pstTempMplayerProbeInfo->u32SampleRate));
        MPLAYER_DBG(printf("pstTempMplayerProbeInfo->u32PicOffset:%lu   u32PicSize:%lu\n\n",pstTempMplayerProbeInfo->u32PicOffset,pstTempMplayerProbeInfo->u32PicSize));
        return bRet;
    }
    else
    {
        MPLAYER_DBG(printf("get music file info fail!\n"));
        return FALSE;
    }

}


// NOTES:
// _MApp_MPlayer_MusicMetaData_Probe is a function that can show music meta data
// with a given file information
//******************************************************************************
/// show music duration by the index in playlist.
/// @param  fileInfo  \b file information.
/// @param  *pstTempMplayerProbeInfo  \b meta data information.
/// @param  eMusicInfoType  \b meata data type.
/// @return TRUE: SUCCESS , FALSE: FAIL
//******************************************************************************
static BOOLEAN _MApp_MPlayer_MusicMetaData_Probe(MPlayerFileInfo fileInfo,ST_MPLAYER_PROBE_INFO *pstTempMplayerProbeInfo, EN_MUSIC_INFO eMusicInfoType)
{
    BOOLEAN bRet = FALSE;

    if(pstTempMplayerProbeInfo==NULL)
    {
        MPLAYER_DBG(printf("pstTempMplayerProbeInfo is NULL"));
        return FALSE;
    }


    U32 u32FileHandle = INVALID_DATA_STREAM_HDL;
    u32FileHandle = msAPI_FCtrl_FileOpen(&fileInfo.fileEntry, OPEN_MODE_FOR_READ);

    if(u32FileHandle==INVALID_DATA_STREAM_HDL)
    {
        MPLAYER_DBG(printf("open file fail!!!\n"));
        return FALSE;
    }

    enumMPlayerMediaSubType eMediaSubType = E_MPLAYER_SUBTYPE_INVALID;


#if (ENABLE_AAC)
    if ( IS_AAC_FILE(fileInfo.u8ExtFileName) )
    {
       eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_AAC; //AAC
    }
    else
#endif
#if (ENABLE_WAV)
    if ( IS_WAV_FILE(fileInfo.u8ExtFileName) )
    {
        eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_WAV; //WAV
    }
    else
#endif
#if (ENABLE_FLAC)
    if ( IS_FLAC_FILE(fileInfo.u8ExtFileName) )
    {
        eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_FLAC; //FLAC
    }
    else
#endif
#if (ENABLE_AC3)
    if ( IS_AC3_FILE(fileInfo.u8ExtFileName) )
    {
        eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_AC3; //AC3
    }
    else
#endif
#if (ENABLE_WMA)
    if ( IS_WMA_FILE(fileInfo.u8ExtFileName) )
    {
        eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_WMA; //WMA
    }
    else
#endif //#if (ENABLE_WMA)
#if (ENABLE_OGG)
    if ( IS_OGG_FILE(fileInfo.u8ExtFileName) )
    {
        eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_OGG; //OGG
    }
    else
#endif //#if (ENABLE_WMA)

    if ( IS_MP3_FILE(fileInfo.u8ExtFileName) )
    {
        eMediaSubType = (enumMPlayerMediaSubType)E_MPLAYER_SUBTYPE_MP3; //MP3
    }

#if (!ENABLE_NON_PARSING_AUDIO_DATA_INPUT)
    eMediaSubType = _MApp_MPlayer_VerifyMusicType(&fileInfo.fileEntry, eMediaSubType);
#endif


    ST_MUSIC_PROBE_INFO stMusicProbeInfo;
    memset(&stMusicProbeInfo,0,sizeof(ST_MUSIC_PROBE_INFO));

#if (ENABLE_WMA)
    ST_WMA_PROBE_INFO stWmaProbeInfo;
    memset(&stWmaProbeInfo,0,sizeof(ST_WMA_PROBE_INFO));
#endif

    switch(eMediaSubType)
    {
        case E_MPLAYER_SUBTYPE_MP3:
            bRet=MApp_Music_MP3_Probe(u32FileHandle, &stMusicProbeInfo, eMusicInfoType);
            break;
#if (ENABLE_WMA)
        case E_MPLAYER_SUBTYPE_WMA:
            bRet=MApp_WMA_Probe(u32FileHandle, &stWmaProbeInfo, eMusicInfoType);
            break;
#endif
#if (ENABLE_WAV)
        case E_MPLAYER_SUBTYPE_WAV:
            bRet=MApp_Music_WAV_Probe(u32FileHandle, &stMusicProbeInfo, eMusicInfoType);
            break;
#endif
#if (ENABLE_FLAC)
        case E_MPLAYER_SUBTYPE_FLAC:
            bRet=MApp_Music_FLAC_Probe(u32FileHandle, &stMusicProbeInfo, eMusicInfoType);
            break;
#endif
#if (ENABLE_AC3)
        case E_MPLAYER_SUBTYPE_AC3:
            bRet=MApp_Music_AC3_Probe(u32FileHandle, &stMusicProbeInfo, eMusicInfoType);
            break;
#endif
#if (ENABLE_AAC)
        case E_MPLAYER_SUBTYPE_AAC:
            if(MApp_Music_M4A_Probe(u32FileHandle, &stMusicProbeInfo, eMusicInfoType)==FALSE)
            {
                bRet=MApp_Music_AAC_Probe(u32FileHandle, &stMusicProbeInfo, eMusicInfoType);
            }
            else
            {
                bRet = TRUE;
            }
            break;
#endif
#if (ENABLE_OGG)
        case E_MPLAYER_SUBTYPE_OGG:
            bRet=MApp_Music_OGG_Probe(u32FileHandle, &stMusicProbeInfo, eMusicInfoType);
            break;
#endif
        default:
            MPLAYER_DBG(printf("Not in above type\n"));
            break;
    }

    memset(pstTempMplayerProbeInfo,0,sizeof(ST_MPLAYER_PROBE_INFO));


    if(bRet==TRUE)
    {
        switch(eMediaSubType)
        {
#if (ENABLE_WMA)
            case E_MPLAYER_SUBTYPE_WMA:
                pstTempMplayerProbeInfo->u32Duration = stWmaProbeInfo.u32Duration;
                pstTempMplayerProbeInfo->u32PicOffset = stWmaProbeInfo.u32PicOffset;
                pstTempMplayerProbeInfo->u32PicSize = stWmaProbeInfo.u32PicSize;
                break;
#endif
            case E_MPLAYER_SUBTYPE_MP3:
#if (ENABLE_WAV)
            case E_MPLAYER_SUBTYPE_WAV:
#endif
#if (ENABLE_AAC)
            case E_MPLAYER_SUBTYPE_AAC:
#endif
#if (ENABLE_FLAC)
            case E_MPLAYER_SUBTYPE_FLAC:
#endif
#if (ENABLE_AC3)
            case E_MPLAYER_SUBTYPE_AC3:
#endif
#if (ENABLE_OGG)
            case E_MPLAYER_SUBTYPE_OGG:
#endif
            default:
                pstTempMplayerProbeInfo->u32Duration = stMusicProbeInfo.u32Duration;
                pstTempMplayerProbeInfo->u32PicOffset = stMusicProbeInfo.u32PicOffset;
                pstTempMplayerProbeInfo->u32PicSize = stMusicProbeInfo.u32PicSize;
                break;
        }
    }

    if(u32FileHandle!=INVALID_DATA_STREAM_HDL)
    {
        msAPI_FCtrl_FileClose(u32FileHandle);
    }

    return bRet;
}

//******************************************************************************
/// Embedded photo initial via memory.
/// @param  pFileEntry \b IN  source file entry.
/// @param  bThumbnail  \b IN thumbnail or not.
/// @param  pfCallBack  \b IN photo decode callback function.
/// @return TRUE: Success , FALSE: FAIL
//******************************************************************************
static BOOLEAN MApp_MPlayer_EmbeddedPhoto_DecodeMemory_Init(FileEntry *pFileEntry, BOOLEAN bThumbnail, MApp_Photo_DataRequestCallBack pfCallBack)
{

    ST_MPLAYER_PROBE_INFO stTempMPlayerProbeInfo;
    BOOLEAN bRet = FALSE;

    memset(&stTempMPlayerProbeInfo,0,sizeof(ST_MPLAYER_PROBE_INFO));

    if(m_u32EmbeddedPhoto_FileHandle != INVALID_DATA_STREAM_HDL)
    {
        MApp_MPlayer_EmbeddedPhotoIO_Close();
    }
    m_u32EmbeddedPhoto_FileHandle = msAPI_DataStreamIO_Open(pFileEntry, OPEN_MODE_FOR_READ, E_DATA_STREAM_TYPE_MUSIC);

    if(m_u32EmbeddedPhoto_FileHandle == INVALID_DATA_STREAM_HDL)
    {
        MPLAYER_ERROR("MApp_MPlayer_EmbeddedPhoto_DecodeMemory_Init(), open failed\n");
        return FALSE;
    }

    MPlayerFileInfo stFileInfo;
    memset(&stFileInfo,0,sizeof(MPlayerFileInfo));
    memcpy(&stFileInfo.fileEntry,pFileEntry,sizeof(FileEntry));

    if( _MApp_MPlayer_MusicMetaData_Probe(stFileInfo,&stTempMPlayerProbeInfo, E_MUSIC_INFO_BASIC))
    {
        if(stTempMPlayerProbeInfo.u32PicOffset != 0 && stTempMPlayerProbeInfo.u32PicSize!=0)
        {
            if(msAPI_DataStreamIO_Seek(m_u32EmbeddedPhoto_FileHandle, stTempMPlayerProbeInfo.u32PicOffset, E_DATA_STREAM_SEEK_SET) == FALSE)
            {
                printf("MApp_MPlayer_EmbeddedPhoto_DecodeMemory_Init(), File seek Fail \n");
                return FALSE;
            }

            m_u32EmbeddedPhotoOffset = stTempMPlayerProbeInfo.u32PicOffset;
            m_u32EmbeddedPhotoSize = stTempMPlayerProbeInfo.u32PicSize;

            MApp_Photo_MemCfg(
            ((MAD_JPEG_READBUFF_MEMORY_TYPE & MIU1) ? (MAD_JPEG_READBUFF_ADR | MIU_INTERVAL) : (MAD_JPEG_READBUFF_ADR)), MAD_JPEG_READBUFF_LEN,
            ((MAD_JPEG_OUT_MEMORY_TYPE & MIU1) ? (MAD_JPEG_OUT_ADR | MIU_INTERVAL) : (MAD_JPEG_OUT_ADR)), MAD_JPEG_OUT_LEN,
            ((MAD_JPEG_INTERBUFF_MEMORY_TYPE & MIU1) ? (MAD_JPEG_INTERBUFF_ADR | MIU_INTERVAL) : (MAD_JPEG_INTERBUFF_ADR)), MAD_JPEG_INTERBUFF_LEN, PHOTO_MEMPOOL_BUFFER_SIZE);

            bRet = MApp_Photo_DecodeMemory_Init(bThumbnail, pfCallBack);
        }
    }

    if(bRet == FALSE)
    {
        MApp_MPlayer_EmbeddedPhotoIO_Close();
    }
    return bRet;
}

//******************************************************************************
/// Embedded photo close.
/// @return TRUE: Success , FALSE: FAIL
//******************************************************************************
static BOOLEAN MApp_MPlayer_EmbeddedPhotoIO_Close()
{
    if(m_u32EmbeddedPhoto_FileHandle != INVALID_DATA_STREAM_HDL)
    {
        if(msAPI_DataStreamIO_Close(m_u32EmbeddedPhoto_FileHandle) == FALSE)
        {
            ASSERT(0);
            MPLAYER_ERROR("_MApp_MPlayer_EmbeddedPhoto_DataRequestCallBack() file close failed\n");
            return FALSE;
        }

        m_u32EmbeddedPhoto_FileHandle = INVALID_DATA_STREAM_HDL;
    }
    return TRUE;
}
#endif //#if ENABLE_EMBEDDED_PHOTO_DISPLAY

#if PLAYLIST_BGM
BOOLEAN MApp_MPlayer_BGM_Playlist_Init()
{
    if(m_bBGMPlaylistInit == FALSE)
    {
        _MApp_MPlayer_BGM_Playlist_Swap();
        m_bBGMPlaylistInit = TRUE;
    }

    return TRUE;
}

BOOLEAN MApp_MPlayer_BGM_Playlist_DeInit()
{
    if(m_bBGMPlaylistInit == TRUE)
    {
        _MApp_MPlayer_BGM_Playlist_Swap();
        m_bBGMPlaylistInit = FALSE;
    }

    return TRUE;
}

static void _MApp_MPlayer_BGM_Playlist_Swap()
{
    MPlayerPlayListInfo *pstMusicPlayList, *pstBGMPlayList;
    MPlayerPlayListInfo stTempPlayListInfo;
    U16 u16TempSelectedFileNum, u16SwapNum;

    pstMusicPlayList = (MPlayerPlayListInfo *)_PA2VA((MPLAYER_MUSIC_PLAYLIST_MEMORY_TYPE & MIU1) ? (MPLAYER_MUSIC_PLAYLIST_ADR | MIU_INTERVAL) : (MPLAYER_MUSIC_PLAYLIST_ADR));
    pstBGMPlayList = (MPlayerPlayListInfo *)_PA2VA((MPLAYER_BGM_PLAYLIST_MEMORY_TYPE & MIU1) ? (MPLAYER_BGM_PLAYLIST_ADR | MIU_INTERVAL) : (MPLAYER_BGM_PLAYLIST_ADR));

    if(m_u16BGMSelectedFileNum >= m_u16SelectedFileNum[E_MPLAYER_TYPE_MUSIC])
    {
        u16SwapNum = m_u16BGMSelectedFileNum;
    }
    else
    {
        u16SwapNum = m_u16SelectedFileNum[E_MPLAYER_TYPE_MUSIC];
    }

    U16 i;

    for(i=0; i<u16SwapNum; i++)
    {
        stTempPlayListInfo = pstMusicPlayList[i];
        pstMusicPlayList[i] = pstBGMPlayList[i];
        pstBGMPlayList[i] = stTempPlayListInfo;
    }

    u16TempSelectedFileNum = m_u16SelectedFileNum[E_MPLAYER_TYPE_MUSIC];
    m_u16SelectedFileNum[E_MPLAYER_TYPE_MUSIC] = m_u16BGMSelectedFileNum;
    m_u16BGMSelectedFileNum = u16TempSelectedFileNum;
}
#endif

#if FILE_SYSTEM_GET_VOLUME_LABEL_ENABLE
#define SHOWN_VOLUME_NAME_MAX_LEN        12
U8 MApp_MPlayer_GetVolumName(U8 u8DriveID,U8* pVolumStrBuf, U8 VolumStrLen)
{
    U8 u8Length = 0;
    U16 u16ItemIdx;
    U16 VolumStrBuf16to8[VolumStrLen];
    if(MApp_MPlayer_QueryTotalDriveNum()>0)
    {
        U16 strBuf[SHOWN_VOLUME_NAME_MAX_LEN];
        U8 BufTooShort = 0;
        BOOLEAN bIsUnicode;
        memset(strBuf,0,SHOWN_VOLUME_NAME_MAX_LEN);
        memset(pVolumStrBuf,0,VolumStrLen);
        u8Length = msAPI_FCtrl_VolumeLabelGetByDriveIndex(u8DriveID, (U16 *)strBuf, SHOWN_VOLUME_NAME_MAX_LEN, &bIsUnicode);
        //memset((U8 *)&strBuf[u8Length],0,2);
        if(u8Length>0)
        {
            for(u16ItemIdx=0;u16ItemIdx<u8Length;u16ItemIdx++)
            {
                if(bIsUnicode==FALSE && strBuf[u16ItemIdx]>=0x80)
                {
                    strBuf[u16ItemIdx]=MApp_Transfer2Unicode(strBuf[u16ItemIdx]);
                }
                if(u16ItemIdx == VolumStrLen-1)
                {
                    strBuf[u16ItemIdx++] = 0x00;
                    BufTooShort = 1;
                    break;
                }
            }
            if(u8Length < SHOWN_VOLUME_NAME_MAX_LEN || BufTooShort == 0)
            {
                for(u16ItemIdx=u8Length;u16ItemIdx<SHOWN_VOLUME_NAME_MAX_LEN;u16ItemIdx++)
                {
                    strBuf[u16ItemIdx] = 0x00;
                }
            }
            memcpy(VolumStrBuf16to8, strBuf, (SHOWN_VOLUME_NAME_MAX_LEN+SHOWN_VOLUME_NAME_MAX_LEN));
        }

        //add if to display the volume label centeredly
        if(u8Length > SHOWN_VOLUME_NAME_MAX_LEN)
            u8Length = SHOWN_VOLUME_NAME_MAX_LEN-1;
    }
    for(u16ItemIdx=0;u16ItemIdx<u8Length;u16ItemIdx++)
    {
        pVolumStrBuf[u16ItemIdx] = VolumStrBuf16to8[u16ItemIdx];
    }
    return u8Length;
}
#endif //FILE_SYSTEM_GET_VOLUME_LABEL_ENABLE

#if RANDOM_PLAY
//******************************************************************************
/// Clear random play table by current playing index.
/// @param  eMPlayerIdx \b IN  Specify the mplayer type.
/// @return TRUE: success, FALSE: fail.
//******************************************************************************
static BOOLEAN _MApp_MPlayer_ResetRandomPlayTable(enumMPlayerIdx eMPlayerIdx)
{
    if(eMPlayerIdx > E_MPLAYER_MAX_CONCURRENT_PLAYER_NUM)
    {
        return FALSE;
    }

    if(eMPlayerIdx == E_MPLAYER_MAX_CONCURRENT_PLAYER_NUM)
    {
        memset(m_au8RandomPlayTable, 0, sizeof(m_au8RandomPlayTable));
        memset(m_u16RandomPlaySelectedNum, 0, sizeof(m_u16RandomPlaySelectedNum));
    }
    else
    {
        memset(m_au8RandomPlayTable[eMPlayerIdx], 0, sizeof(m_au8RandomPlayTable[eMPlayerIdx]));
        m_u16RandomPlaySelectedNum[eMPlayerIdx] = 0;
    }

    return TRUE;
}

//******************************************************************************
/// Generate random number by random play table.
/// @param  eMPlayerIdx \b IN  Specify the mplayer type.
/// @return INVALID_RANDOM_NUMBER: fail, otherwise: random number.
//******************************************************************************
static U16 _MApp_MPlayer_RandomPlay_Rand(enumMPlayerIdx eMPlayerIdx)
{
    if(eMPlayerIdx >= E_MPLAYER_MAX_CONCURRENT_PLAYER_NUM)
    {
        return INVALID_RANDOM_NUMBER;
    }

    U16 u16TotalPlayNum, u16RandomNum;

    //Calculate total play file number.
    if(MApp_MPlayer_QueryPlayListFileNum(m_MPlayerInfo[eMPlayerIdx].eMediaType)> 0)//select some files to play
    {
        u16TotalPlayNum = MApp_MPlayer_QueryPlayListFileNum(m_MPlayerInfo[eMPlayerIdx].eMediaType);
    }
    else//play all files without selection
    {
        u16TotalPlayNum = (m_MPlayerInfo[eMPlayerIdx].u16TotalFileNum - m_MPlayerInfo[eMPlayerIdx].u16TotalDirNum);
    }

    //if all files in random play table are played and repeat mode is repeat all--> reset random play table.
    if(m_u16RandomPlaySelectedNum[eMPlayerIdx] == u16TotalPlayNum
    && m_MPlayerInfo[eMPlayerIdx].eRepeatMode == E_MPLAYER_REPEAT_ALL)
    {
        _MApp_MPlayer_ResetRandomPlayTable(eMPlayerIdx);
    }

    //all files are selected, return INVALID_RANDOM_NUMBER
    if(m_u16RandomPlaySelectedNum[eMPlayerIdx] >= u16TotalPlayNum)
    {
        return INVALID_RANDOM_NUMBER;
    }

    srand(MsOS_GetSystemTime());
    u16RandomNum = (rand() % (u16TotalPlayNum - m_u16RandomPlaySelectedNum[eMPlayerIdx]));

    U16 i, u16Count = 0;
    //Generate new play index
    for(i=0; i< u16TotalPlayNum ; i++)
    {
        if((m_au8RandomPlayTable[eMPlayerIdx][i>>3] & (1<<(i&0x7))) == 0)
        {
            if(u16Count == u16RandomNum)
            {
                break;
            }
            u16Count++;
        }
    }

    if(i == u16TotalPlayNum)
    {
        printf("[ERROR]:_MApp_MPlayer_RandomPlay_Rand can not find next random index.");
        return INVALID_RANDOM_NUMBER;
    }

    //if play mode is play directory, add total directory number to i.
    if(MApp_MPlayer_QueryPlayListFileNum(m_MPlayerInfo[eMPlayerIdx].eMediaType) == 0)
    {
        i += m_MPlayerInfo[eMPlayerIdx].u16TotalDirNum;
    }

    return i;
}

//******************************************************************************
/// Set random play table by current playing index.
/// @param  eMPlayerIdx \b IN  Specify the mplayer type.
/// @return TRUE: success, FALSE: fail.
//******************************************************************************
static BOOLEAN _MApp_MPlayer_SetRandomPlayTable(enumMPlayerIdx eMPlayerIdx)
{
    if(eMPlayerIdx >= E_MPLAYER_MAX_CONCURRENT_PLAYER_NUM)
    {
        return FALSE;
    }

    U16 u16Index = m_MPlayerInfo[eMPlayerIdx].u16PlayingIdx;

    if(MApp_MPlayer_QueryPlayListFileNum(m_MPlayerInfo[eMPlayerIdx].eMediaType) == 0)
    {
        u16Index -= m_MPlayerInfo[eMPlayerIdx].u16TotalDirNum;
    }

    //When nth file is playing, set nth-bit to 1.
    if(m_au8RandomPlayTable[eMPlayerIdx][u16Index>>3] & (1<<(u16Index&0x7)))
    {
        //u16Index has been set.
    }
    else
    {
        m_u16RandomPlaySelectedNum[eMPlayerIdx]++;
        m_au8RandomPlayTable[eMPlayerIdx][u16Index>>3] |= (1<<(u16Index&0x7));
    }

    return TRUE;
}
#endif

#if ENABLE_SUBTITLE_DMP
//****************************************************************************
/// Hide subtitle on screen
/// @param void
/// @return TRUE if success, FALSE otherwise
//****************************************************************************
static BOOLEAN _MApp_MPlayer_HideSubtitle(void)
{
    //1. Hide external and internal text subtitle.
    if (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_SUBTITLE_SHOWN)
    {
        NOTIFY(E_MPLAYER_NOTIFY_HIDE_SUBTITLE, NULL);
        m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_SUBTITLE_SHOWN;
    }
    //2. Hide external and internal image subtitle.
    msAPI_MpegSP_Clear_Highlight();
    //3. Hide TS subtitle.
    MApp_VDPlayer_TS_SubtitleErase();

    return TRUE;
}

static BOOLEAN _MApp_MPlayer_InitSubtitleTask(void)
{
    m_bIsSubtitleTaskAlive = TRUE;

    return TRUE;
}

//****************************************************************************
/// Enable subtilte task and do pre-things
/// @param void
/// @return TRUE if success, FALSE otherwise
//****************************************************************************
static BOOLEAN _MApp_MPlayer_EnableSubtitleTask(void)
{
    if(E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL & m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1)
    {
#if (ENABLE_SUBTITLE_SUBIDX)
        if(m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SUBIDX)
        {
            _MApp_MPlayer_SetMpegSubtitle();
        }
#endif
#if (ENABLE_SMALL_BUF_SUBTITLE)
        MApp_MPlayer_EnableReloadAppositeSubtitleBuf(TRUE);
#endif
    }
    else
    {
        if((m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_SUBTITLE_TEXT) == 0)
        {
#if (ENABLE_INTERNAL_BMP_SUBTITLE==1)
            if(u32subtitletype == E_VDP_CODEC_ID_SUBTITLE_IMAGE_BMP)
            {
                U32 u32CurTime = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CUR_TIME);
                msAPI_MpegSP_Enable_Subtitle_Gwin(u32CurTime);
            }
#endif
        }
    }
    m_bIsSubtitleTaskAlive = TRUE;

    return TRUE;
}

//****************************************************************************
/// Disable subtilte task and clear subtitle on screen
/// @param void
/// @return TRUE if success, FALSE otherwise
//****************************************************************************
static BOOLEAN _MApp_MPlayer_DisableSubtitleTask(void)
{
    _MApp_MPlayer_HideSubtitle();
    m_bIsSubtitleTaskAlive = FALSE;

    return TRUE;
}

//****************************************************************************
/// Entries for all types subtitle type to get alive subtitle and show
/// @param u32CurTime \b IN: Specify the time in milliseconds
/// @return TRUE if success, FALSE otherwise
//****************************************************************************
static BOOLEAN _MApp_MPlayer_SubtitleTask(U32 u32CurTime)
{
    //Get new tag time: movie current time == subtitle tag time + user time shift
    u32CurTime = ((S32)u32CurTime - m_s32SubtitleTimeShift)>0 ? ((S32)u32CurTime - m_s32SubtitleTimeShift):0;

    if(m_bIsSubtitleTaskAlive==FALSE)
    {
        MApp_VDPlayer_RefreshTextSubtitleTag(u32CurTime);
    #if (ENABLE_SMALL_BUF_SUBTITLE)
        MApp_MPlayer_RefreshTextSubtitleTag(u32CurTime);
    #endif

        return FALSE;
    }
    else
    {
        if((m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_SUBTITLE_VALID) &&
           (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_SUBTITLE_ENABLE))
        {
          #if (ENABLE_SMALL_BUF_SUBTITLE)
            if(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL)
            {
                 MApp_MPlayer_SubtitleParser_Main(u32CurTime);
            }
          #endif

            // Deal with subtitle.
            if((m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_SUBTITLE_TEXT) == 0)
            {
                if(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL)
                {
            #if (ENABLE_SUBTITLE_SUBIDX)
                    SUBTITLE_DBG(printf("\n[%d] External Image",u32CurTime));
                    if(m_eExternalSubtitleType == E_MPLAYER_SUBTITLE_SUBIDX)
                    {
                      #if(ENABLE_SMALL_BUF_SUBTITLE==0)
                        if(msAPI_MpegSP_SpuQueue_GetCount() < 2)
                        {
                            _MApp_MPlayer_PushSubtitleSUB();
                        }
                      #endif
                        msAPI_MpegSP_Main(u32CurTime*90);
                    }
                    if (m_enRepeatABMode == E_MPLAYER_MOVIE_SET_REPEAT_B)
                    {
                        // if at the start A point, clear the subtitle queue
                        if (m_bNewRepeatABLoop && u32CurTime < m_u32MovieRepeatTime[0] + 200)
                        {
                            SUBTITLE_DBG(printf("clear subtitle queue\n"));
                            m_bNewRepeatABLoop = FALSE;
                            #if (ENABLE_SMALL_BUF_SUBTITLE)
                                msAPI_MpegSP_SpuQueue_Reset();
                                MApp_MPlayer_EnableReloadAppositeSubtitleBuf(TRUE);
                            #endif
                            return TRUE;
                        }
                        if (u32CurTime > m_u32MovieRepeatTime[1] - 200)
                        {
                            m_bNewRepeatABLoop = TRUE;
                        }
                    }
            #endif //#if (ENABLE_SUBTITLE_SUBIDX)
                }
                else
                {
                    SUBTITLE_DBG(printf("\n[%d] Internal Image",u32CurTime));
                    MApp_VDPlayer_SubtitleDraw();
                }
            }
            else
            {
                if (m_enRepeatABMode == E_MPLAYER_MOVIE_SET_REPEAT_B)
                {
                    // if at the start A point, clear the subtitle queue
                    if (m_bNewRepeatABLoop && u32CurTime < m_u32MovieRepeatTime[0] + 200)
                    {
                        SUBTITLE_DBG(printf("clear subtitle queue\n"));
                        _MApp_MPlayer_ReinitRepeatABSubtitle();
                    #if (ENABLE_SMALL_BUF_SUBTITLE)
                        MApp_MPlayer_EnableReloadAppositeSubtitleBuf(TRUE);
                    #endif
                        return TRUE;
                    }
                    if (u32CurTime > m_u32MovieRepeatTime[1] - 200)
                    {
                        m_bNewRepeatABLoop = TRUE;
                    }
                }
                // Check if hide the current subtitle.
                S16 i;
                if(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_SUBTITLE_SHOWN)
                {
                    for(i=m_u8AliveSubtitleNum-1; i>=0; i--)
                    {
                        if(m_aAliveSubtitles[i].u32TimeEnd <= u32CurTime||m_aAliveSubtitles[i].u32TimeStart > u32CurTime)
                        {
                            NOTIFY(E_MPLAYER_NOTIFY_HIDE_SUBTITLE, NULL);
                            m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 &= (enumMPlayerKnlFlags1)~E_MPLAYER_KNL_FLG1_SUBTITLE_SHOWN;
                            SUBTITLE_DBG(printf("\n[%d] <HIDE SUBTITLE>",u32CurTime,i));
                            break;
                        }
                    }
                }
                if(u32CurTime > 0)
                {
                    U16 u16SubtitleLength=0;
                    BOOLEAN bHasNewAliveSubtitle = FALSE;
                    //transfer subtitle show flag to BOOLEAN
                    BOOLEAN bSubtitleShownFLG = (m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_SUBTITLE_SHOWN) ? TRUE:FALSE;

                    if(m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 & E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL)
                    {
                        bHasNewAliveSubtitle = MApp_MPlayer_GetAliveTextSubtitleTag(u32CurTime, &m_u8AliveSubtitleNum, m_aAliveSubtitles, bSubtitleShownFLG);
                        SUBTITLE_DBG(printf("\n[%d] External Text -- AliveSubtitleNum:%d ",u32CurTime,m_u8AliveSubtitleNum));
                    }
                    else
                    {
                        bHasNewAliveSubtitle = MApp_VDPlayer_GetAliveTextSubtitleTag(u32CurTime, &m_u8AliveSubtitleNum, m_aAliveSubtitles, bSubtitleShownFLG);
                        SUBTITLE_DBG(printf("\n[%d] Internal Text -- AliveSubtitleNum:%d ",u32CurTime,m_u8AliveSubtitleNum));
                    }

                    if(bHasNewAliveSubtitle == TRUE)
                    {
                        U8 *pu8Dst = msAPI_Memory_Allocate(m_u8AliveSubtitleNum*(SUBTITLE_MAX_SIZE+2), BUF_ID_FILEBROWER);
                        if(pu8Dst)
                        {
                            m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1 |= E_MPLAYER_KNL_FLG1_SUBTITLE_SHOWN;
                            SUBTITLE_DBG(printf(" <SHOW SUBTITLE> "));

                            for(i=m_u8AliveSubtitleNum-1; i>=0; i--)
                            {
                                u16SubtitleLength += _MApp_MPlayer_GetSubtitle(&pu8Dst[u16SubtitleLength], (SUBTITLE_MAX_SIZE+2), m_aAliveSubtitles[i].u32SubtitlePos);

                                if(i != 0)
                                {
                                    pu8Dst[u16SubtitleLength] = 0x8A;//'\r';
                                    pu8Dst[u16SubtitleLength+1] = 0xE0;//'\0';
                                }
                                u16SubtitleLength += 2;
                            }
                            NOTIFY(E_MPLAYER_NOTIFY_SHOW_SUBTITLE, (void*)pu8Dst);
                            msAPI_Memory_Free(pu8Dst, BUF_ID_FILEBROWER);
                            pu8Dst = NULL;
                        }
                        else
                        {
                            __ASSERT(0);
                        }

                        m_Subtitle_Tag = m_aAliveSubtitles[m_u8AliveSubtitleNum-1];
                        m_u32CurSubtitlePos = m_Subtitle_Tag.u32SubtitlePos;
                        m_u32LyricSubtitleCurTime = m_Subtitle_Tag.u32TimeStart;
                        SUBTITLE_DBG(printf(" TextSubtitleFormat:%d TimeStart:%d TimeEnd:%d Length:%d", MApp_MPlayer_GetInfo(E_MPLAYER_EXT_SUBTITLE_INFO_SUBTITLE_TYPE), m_Subtitle_Tag.u32TimeStart, m_Subtitle_Tag.u32TimeEnd, u16SubtitleLength));
                    }
                }
            }
        }

        return TRUE;
    }
}

//****************************************************************************
/// Set external subtitle time shift
/// @param u32TimeShift \b IN: Specify the time in milliseconds
/// @return void
//****************************************************************************
void MApp_MPlayer_SetSubtitleTimeShift(S32 u32TimeShift)
{
    m_s32SubtitleTimeShift = u32TimeShift;
    MApp_MPlayer_EnableReloadAppositeSubtitleBuf(TRUE);
}

//****************************************************************************
/// Get external subtitle time shift value
/// @param void
/// @return m_s32SubtitleTimeShift: external subtitle time shift value
//****************************************************************************
S32 MApp_MPlayer_GetSubtitleTimeShift(void)
{
    return m_s32SubtitleTimeShift;
}
#endif
//******************************************************************************
/// Set video delay time in millisecond for A/V sync.
/// @param  u32VideoSyncDelayMsTime \b IN  Specify video delay time in millisecond.
/// @return TRUE or FALSE
//******************************************************************************
BOOLEAN MApp_MPlayer_SetVideoSyncDelayMsTime(U32 u32VideoSyncDelayMsTime)
{
    return MApp_VDPlayer_SetVideoSyncDelayMsTime(u32VideoSyncDelayMsTime);
}

//******************************************************************************
/// Get video delay time in millisecond for A/V sync.
/// @param  NA
/// @return video delay time in millisecond.
//******************************************************************************
U32 MApp_MPlayer_GetVideoSyncDelayMsTime(void)
{
    return MApp_VDPlayer_GetVideoSyncDelayMsTime();
}

//******************************************************************************
/**
 * @brief       Format partition by FCtrl DriveIndex
 * @remarks
 * @param       formatMode: FORMAT_FAST/FORMAT_COMPLETED
 * @param       u8DriveIndex: This means partition index
 * @return      TRUE if success, FALSE otherwise
 */
//******************************************************************************
BOOLEAN MApp_MPlayer_FormatPartitionByDriveIndex(EN_FORMAT_MODE formatMode,U8 u8DriveIndex)
{
    BOOLEAN bRet;

    bRet = msAPI_FCtrl_FormatPartitionByDriveIndex(formatMode, u8DriveIndex);

    if(bRet)
    {
        MPlayerDrive DriveInfo;
        //Get drive info by partition, u8DriveIndex(mplayer) == partition(FCtrl).
        memset(&DriveInfo,0,sizeof(MPlayerDrive));
        MApp_MPlayer_QueryPartitionIdxInDrive(u8DriveIndex, &DriveInfo);

        //We should re-initialize drive infomation.
        if (m_u16CurDriveIdx == u8DriveIndex)
        {
            MApp_MPlayer_InitializeAllDevices();
        }

        //Get drive info by Lun.
        MApp_MPlayer_QueryDriveInfoByLun(DriveInfo.u8Lun, &DriveInfo);
        MApp_MPlayer_ConnectDrive(DriveInfo.u8Partition);

        NOTIFY(E_MPLAYER_NOTIFY_END_OF_FORMAT, NULL);
    }
    else
    {
        NOTIFY(E_MPLAYER_NOTIFY_UNSUPPORT_FS_OF_FORMAT, NULL);
    }
    return bRet;
}

//****************************************************************************
/// Get ISO639 language code
/// @param pSrc \b IN: point of ISO639 language
/// @return EN_LANGUAGE : language code
//****************************************************************************
enumMPlayerLanguage _MApp_MPlayer_GetLanguageByISO639LangCode(U8 *pu8ISO639)
{
    U16 i, u16Num;

    for(i=0;i<3;i++)
    {
        if( pu8ISO639[i] >= 'A' &&  pu8ISO639[i] <= 'Z')
        {
             pu8ISO639[i] =  pu8ISO639[i] - 'A' + 'a';
        }
    }
    u16Num=sizeof(m_aIso639_LanguageCode)/sizeof(ST_MPLAYER_ISO639_LANG);

    for(i=0;i<u16Num;i++)
    {
        if(memcmp(pu8ISO639, m_aIso639_LanguageCode[i].au8LangCode, 3) == 0)
        {
            return m_aIso639_LanguageCode[i].enMPlayerLang;
        }
    }

    return E_MPLAYER_LANGUAGE_UNDEFINED;
}

//******************************************************************************
/// Query current movie audio language.
/// @param  NA
/// @return enumMPlayerLanguage
//******************************************************************************
enumMPlayerLanguage MApp_MPlayer_QueryCurMovieAudioLanguage(void)
{
    U32 u32Lang;
    U8 u8Lang[3];

    u32Lang = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_AUDIO_LANGUAGE);

    u8Lang[0] = (U8)(u32Lang&0xFF);
    u8Lang[1] = (U8)((u32Lang>>8)&0xFF);
    u8Lang[2] = (U8)((u32Lang>>16)&0xFF);

    return _MApp_MPlayer_GetLanguageByISO639LangCode(u8Lang);
}

//******************************************************************************
/// Query current movie subtitle language.
/// @param  NA
/// @return enumMPlayerLanguage
//******************************************************************************
#if ENABLE_MPLAYER_MOVIE
enumMPlayerLanguage MApp_MPlayer_QueryCurMovieSubtitleLanguage(void)
{
    U32 u32Lang;
    U8 u8Lang[3];

    if(E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL & m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1)
    {
        u32Lang = MApp_MPlayer_GetCurExternalSubtitleLanguage();
    }
    else
    {
        u32Lang = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_SUBTITLE_LANGUAGE);
    }

    u8Lang[0] = (U8)(u32Lang&0xFF);
    u8Lang[1] = (U8)((u32Lang>>8)&0xFF);
    u8Lang[2] = (U8)((u32Lang>>16)&0xFF);

    return _MApp_MPlayer_GetLanguageByISO639LangCode(u8Lang);
}

//******************************************************************************
/// Query movie subtitle language by subtitle track index.
/// @param u16SubtitleTrack \b IN: subtitle track index
/// @return enumMPlayerLanguage
//******************************************************************************
enumMPlayerLanguage MApp_MPlayer_QueryMovieSubtitleLanguageByTrackIndex(U16 u16SubtitleTrack)
{
    U32 u32Lang;
    U8 u8Lang[3];

    if(E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL & m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1)
    {
        u32Lang = MApp_MPlayer_GetExternalSubtitleLanguageByTrackIndex(u16SubtitleTrack);
    }
    else
    {
        U16 u16ExternalSubtitleNum = MApp_MPlayer_GetInfo(E_MPLAYER_EXT_SUBTITLE_INFO_NB_TRACK);
        u16SubtitleTrack = u16SubtitleTrack - u16ExternalSubtitleNum;

        u32Lang = MApp_VDPlayer_GetInternalSubtitleLanguageByTrackIndex(u16SubtitleTrack);
    }

    //Notice that this is used for handling different data placing method in vdplayer.
    if(EN_VDP_FILE_FORMAT_TS == _MApp_VDPlayer_GetShareMemData(E_SHAREMEM_FILE_FORMAT))
    {
        u8Lang[0] = (U8)((u32Lang>>24)&0xFF);
        u8Lang[1] = (U8)((u32Lang>>16)&0xFF);
        u8Lang[2] = (U8)((u32Lang>>8)&0xFF);
    }
    else
    {
        u8Lang[0] = (U8)(u32Lang&0xFF);
        u8Lang[1] = (U8)((u32Lang>>8)&0xFF);
        u8Lang[2] = (U8)((u32Lang>>16)&0xFF);
    }

    return _MApp_MPlayer_GetLanguageByISO639LangCode(u8Lang);
}


//******************************************************************************
/// Get current subttitle is text or not
/// @param  NA
/// @return TRUE if text, FALSE not text.
//******************************************************************************
BOOLEAN MApp_MPlayer_IsCurSubtitleText(void)
{
    if(E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL & m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1)
    {
#if (ENABLE_SUBTITLE_SUBIDX)
        if(m_eExternalSubtitleType != E_MPLAYER_SUBTITLE_SUBIDX)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
#else
        return TRUE;
#endif
    }
    else
    {
        if(MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CURRENT_SUBTITLE_TEXT))
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
}

//******************************************************************************
/// Get current subttitle is external or not
/// @param  NA
/// @return TRUE if external subtitle, FALSE not external subtitle.
//******************************************************************************
BOOLEAN MApp_MPlayer_IsCurSubtitleExternal(void)
{
    if(E_MPLAYER_KNL_FLG1_SUBTITLE_EXTERNAL & m_MPlayerInfo[E_MPLAYER_FOREGROUND_PLAYER].eKnlFlag1)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}

#endif
//******************************************************************************
/// Query movie audio language by audio track index.
/// @param u16AudioTrack \b IN: audio track index
/// @return enumMPlayerLanguage
//******************************************************************************
enumMPlayerLanguage MApp_MPlayer_QueryMovieAudioLanguageByTrackIndex(U16 u16AudioTrack)
{
    U32 u32Lang;
    U8 u8Lang[3];

    u32Lang = MApp_VDPlayer_GetAudioLanguageByTrackIndex(u16AudioTrack);

    u8Lang[0] = (U8)(u32Lang&0xFF);
    u8Lang[1] = (U8)((u32Lang>>8)&0xFF);
    u8Lang[2] = (U8)((u32Lang>>16)&0xFF);

    return _MApp_MPlayer_GetLanguageByISO639LangCode(u8Lang);
}



//******************************************************************************
/// Get current movie audio codecID can support or not.
/// @param  NA
/// @return TRUE if supported, FALSE not supported.
//******************************************************************************

BOOLEAN MApp_MPlayer_GetMovieAudioCodecSupported(void)
{
    return MApp_VDPlayer_GetMovieAudioCodecSupported();
}



//******************************************************************************
/// Get file size by playlist index.
/// @param  u16FileIdx \b IN Specify index of play list
/// @param  eMediaType \b IN Specify Media Type
/// @param  pfileSize  \b OUT Specify file size
/// @return TRUE/FALSE.
//******************************************************************************
BOOLEAN MApp_MPlayer_GetFileSizeByPlaylistIndex(U16 u16FileIdx, enumMPlayerMediaType eMediaType, LongLong *pfileSize)
{
    if(m_u16SelectedFileNum[eMediaType] <= u16FileIdx)
    {
        return FALSE;
    }

    MPlayerPlayListInfo *pstPlayListInfo = NULL;
    U32 u32XdataWindowBase;

    if(_MApp_MPlayer_GetPlayListAddressByMediaType(eMediaType, &u32XdataWindowBase)==FALSE)
    {
        return FALSE;
    }

    pstPlayListInfo = (MPlayerPlayListInfo *) (_PA2VA(u32XdataWindowBase));

    pfileSize->Hi = PLAY_LIST_FILE_ENTRY(u16FileIdx).FileLength.Hi;
    pfileSize->Lo = PLAY_LIST_FILE_ENTRY(u16FileIdx).FileLength.Lo;

    return TRUE;
}

//******************************************************************************
/// MApp_MPlayer_GetFileEntryByPlaylistIndex
/// @param  u16FileIdx \b IN Specify index of play list
/// @param  eMediaType \b IN Specify Media Type
/// @param  pFileEntry \b OUT Specify file entry
/// @return TRUE/FALSE.
//******************************************************************************
BOOLEAN MApp_MPlayer_GetFileEntryByPlaylistIndex(U16 u16FileIdx, enumMPlayerMediaType eMediaType, FileEntry *pFileEntry)
{
    if(m_u16SelectedFileNum[eMediaType] <= u16FileIdx)
    {
        return FALSE;
    }

    MPlayerPlayListInfo *pstPlayListInfo = NULL;
    U32 u32XdataWindowBase;

    if(_MApp_MPlayer_GetPlayListAddressByMediaType(eMediaType, &u32XdataWindowBase)==FALSE)
    {
        return FALSE;
    }

    pstPlayListInfo = (MPlayerPlayListInfo *) (_PA2VA(u32XdataWindowBase));

    memcpy(pFileEntry, &PLAY_LIST_FILE_ENTRY(u16FileIdx), sizeof(FileEntry));

    return TRUE;
}

#if PHOTO_SLIDE_SHOW_EFFECT
void MApp_MPlayer_SetSlideShowEffect(EN_PHOTO_SLIDE_SHOW_EFFECT eSlideShowEffect)
{
    MApp_Photo_SetSlideShowEffect(eSlideShowEffect);
}
#endif

BOOLEAN MApp_MPlayer_SetForceStopCallBackFunction(enumMPlayerMediaType eMediaType, PF_FORCE_STOP pfForceStopCallBack)
{
    switch(eMediaType)
    {
    #if ENABLE_MPLAYER_PHOTO
        case E_MPLAYER_TYPE_PHOTO:
            return TRUE;
    #endif

    #if ENABLE_MPLAYER_MUSIC
        case E_MPLAYER_TYPE_MUSIC:
            return TRUE;
    #endif

    #if ENABLE_MPLAYER_MOVIE
        case E_MPLAYER_TYPE_MOVIE:
            return MApp_VDPlayer_SetCfg(E_VDPLAYER_CFG_FORCE_STOP_CALLBACK, (U32)pfForceStopCallBack);
    #else
        UNUSED(pfForceStopCallBack);
    #endif

    #if ENABLE_MPLAYER_TEXT
        case E_MPLAYER_TYPE_TEXT:
            return TRUE;
    #endif

        default:
            return FALSE;
    }
}

BOOLEAN MApp_MPlayer_SetForceDisplayPhotoPartialError(BOOLEAN bForceDisPlay)
{
    MApp_Photo_SetForceDisplayPhotoPartialError(bForceDisPlay);

    return TRUE;
}

//******************************************************************************
/// Set the file to a decoded fail or success file
/// @param  u16FileIdx \b IN  Specify the file index.
/// @param  bFailed \b IN  Specify fail or success.
/// @param  MediaType \b IN  Specify the media type.
/// @param  PlayMode \b IN  Specify the play mode.
/// @return enumMPlayerRet
//******************************************************************************
enumMPlayerRet MApp_MPlayer_SetFileDecodedFail(U16 u16FileIdx, U8 bFailed, enumMPlayerMediaType MediaType, enumMPlayerPlayMode PlayMode)
{
    MPlayerPlayListInfo *pstPlayListInfo;
    U32 u32XdataWindowBase;
    MPlayerFileInfo *pFileInfo;
    U32 u32Addr;

    pstPlayListInfo = NULL;


    if((PlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY) || (PlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT) || (PlayMode == E_MPLAYER_PLAY_ONE))
    {
        //The Dir must same as slideshow folder or it will be wrong
        //printf("********** Music/Photo/Movie Mode/Play DIR: u16FileIdx=%d , bFailed=%d **********\n",u16FileIdx,bFailed);
        u32Addr = (U32)((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR)) + (U32)u16FileIdx*sizeof(MPlayerFileInfo);

        pFileInfo = (MPlayerFileInfo *)_PA2VA(u32Addr);
        if (bFailed)
        {
            pFileInfo->eAttribute |= E_MPLAYER_FILE_DECODED_FAIL;
        }
        else
        {
            Remove_enumFileAttribute(pFileInfo->eAttribute, E_MPLAYER_FILE_DECODED_FAIL);
        }
    }
    else
    {
        if(FALSE==_MApp_MPlayer_GetPlayListAddressByMediaType(MediaType, &u32XdataWindowBase))
        {
                return E_MPLAYER_RET_FAIL;
        }

        //printf("********** Music/Photo/Movie Mode/Play List: u16FileIdx=%d , bFailed=%d **********\n",u16FileIdx,bFailed);

        pstPlayListInfo = (MPlayerPlayListInfo *) (_PA2VA(u32XdataWindowBase));


        if (bFailed)
        {
            PLAY_LIST_ATTRIBUTE(u16FileIdx) |= E_MPLAYER_FILE_DECODED_FAIL;
        }
        else
        {
            PLAY_LIST_ATTRIBUTE(u16FileIdx) = PLAY_LIST_ATTRIBUTE(u16FileIdx) & (enumFileAttribute)(~E_MPLAYER_FILE_DECODED_FAIL);
        }
    }

    return E_MPLAYER_RET_OK;
}

BOOLEAN MApp_MPlayer_GetFileDecodedFail(U16 u16FileIdx, enumMPlayerMediaType MediaType, enumMPlayerPlayMode PlayMode)
{
    MPlayerPlayListInfo *pstPlayListInfo, stPlayFileInfo;
    U32 u32XdataWindowBase;
    MPlayerFileInfo *pFileInfo;
    U32 u32Addr;
    BOOLEAN ret = FALSE;

    pstPlayListInfo = NULL;


    if((PlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY) || (PlayMode == E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT) || (PlayMode == E_MPLAYER_PLAY_ONE))
    {
        //The Dir must same as slideshow folder or it will be wrong
        //printf("********** Music/Photo/Movie Mode/Play DIR: u16FileIdx=%d **********\n",u16FileIdx);
        u32Addr = (U32)((MPLAYER_FILE_BUFFER_MEMORY_TYPE & MIU1) ? (MPLAYER_FILE_BUFFER_ADR | MIU_INTERVAL) : (MPLAYER_FILE_BUFFER_ADR)) + (U32)u16FileIdx*sizeof(MPlayerFileInfo);

        pFileInfo = (MPlayerFileInfo *)_PA2VA(u32Addr);
        if (pFileInfo->eAttribute & E_MPLAYER_FILE_DECODED_FAIL)
        {
            ret = TRUE;//fail flag set
        }
        else
        {
            ret = FALSE;//fail flag not set
        }
    }
    else
    {
        if(FALSE==_MApp_MPlayer_GetPlayListAddressByMediaType(MediaType, &u32XdataWindowBase))
        {
                return E_MPLAYER_RET_FAIL;
        }

        //printf("********** Music/Photo/Movie Mode/Play List: u16FileIdx=%d **********\n",u16FileIdx);

        pstPlayListInfo = (MPlayerPlayListInfo *) (_PA2VA(u32XdataWindowBase));
        memcpy(&stPlayFileInfo, &PLAY_LIST(u16FileIdx), sizeof(MPlayerPlayListInfo));//Get PlayingIdx fileInfo

        if(stPlayFileInfo.eAttribute & E_MPLAYER_FILE_DECODED_FAIL)
        {
            ret = TRUE;//fail flag set
        }
        else
        {
            ret = FALSE;//fail flag not set
        }
    }

    return ret;
}

BOOLEAN MApp_MPlayer_QueryPlayListFileAvailable(enumMPlayerMediaType eMediaType, U16 u16PlayingIdx)
{
    MPlayerPlayListInfo *pstPlayListInfo, stPlayFileInfo;
    U16 u16PlayListNum;
    U32 u32XdataWindowBase;
    U8 u8BrowserHandleTemp = INVALID_BROWSER_HANDLE;
    U8 au8FileName[FILE_INFO_LONG_FILENAME_SIZE];
    U8 u8Len;

    memset(&stPlayFileInfo, 0, sizeof(MPlayerPlayListInfo));

    if(_MApp_MPlayer_GetPlayListAddressByMediaType(eMediaType, &u32XdataWindowBase)==FALSE)
    {
        return FALSE;
    }

    u16PlayListNum = m_u16SelectedFileNum[eMediaType];

    if(u16PlayListNum == 0)
    {
        return FALSE;
    }

    pstPlayListInfo = (MPlayerPlayListInfo *) (_PA2VA(u32XdataWindowBase));
    memcpy(&stPlayFileInfo, &PLAY_LIST(u16PlayingIdx), sizeof(MPlayerPlayListInfo));

    // Create temp browser handle
    if(stPlayFileInfo.u16Drive != m_u16CurDriveIdx)
    {
        u8BrowserHandleTemp = MApp_FileBrowser_Create(stPlayFileInfo.u16Drive);
        if(u8BrowserHandleTemp != INVALID_BROWSER_HANDLE)
        {
            _MApp_MPlayer_Browser_ChangeBrowsingEnv(u8BrowserHandleTemp);
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        u8BrowserHandleTemp = INVALID_BROWSER_HANDLE;
    }

    // get long filename by file entry
    u8Len = MApp_FileBrowser_GetLongFileNameByFileEntry(
                    &stPlayFileInfo.fileEntry,
                    (U32)(&au8FileName[0]),
                    (FILE_INFO_LONG_FILENAME_SIZE/2-1));

    // Restore file browser handle
    if(u8BrowserHandleTemp != INVALID_BROWSER_HANDLE)
    {
        MApp_FileBrowser_Destroy(u8BrowserHandleTemp);
        _MApp_MPlayer_Browser_ChangeBrowsingEnv(m_u8UserBrowserHandle);
    }

    if (u8Len > 0)
    {
        return TRUE;
    }

    return FALSE;
}

#if (ENABLE_MPLAYER_VIDEO_CAPTURE)
//******************************************************************************
/// Begin to capture a photo from the current screen
/// @param  pCaptureVideoinfo  \b IN Specify ST_VIDEO_CAPTURE_SET_INFO
/// @return enumCaptureRet
//******************************************************************************
enumCaptureRet MApp_MPlayer_CaptureVideoBegin(ST_VIDEO_CAPTURE_SET_INFO *pCaptureVideoinfo)
{
    enumCaptureRet eRet = E_CAPTURE_RET_FAIL;

    CAPTURE_DBG(printf("[Video Capture][Time:%d] Begin\n",msAPI_Timer_GetTime0()));
    if(pCaptureVideoinfo == NULL)
    {
        return E_CAPTURE_RET_FAIL;
    }

    if(MApp_MPlayer_IsCapturingVideo())
    {
        CAPTURE_ERR(printf("[Video Capture Error] Video capturing! Fail to begin a new capture.\n");)
        return E_CAPTURE_RET_IGNORE;
    }

    if(((pCaptureVideoinfo->u8ConnectPort==0)&&(MApp_MassStorage_DeviceConnectionDetect()&MS_USB_CONNECTED))
        ||((pCaptureVideoinfo->u8ConnectPort==1)&&(MApp_MassStorage_DeviceConnectionDetect()&MS_USB2_CONNECTED))
      )
    {
    }
    else
    {
        CAPTURE_ERR(printf("[Video Capture Error] There is no USB connected\n");)
        return E_CAPTURE_RET_USB_FAIL;
    }

    _MApp_MPlayer_SetVideoCaptureSetting(pCaptureVideoinfo);

    U16* pu16RenameFile;
    U16* pu16RenamePath;
    U8 u8CurFileBrowserHandle = INVALID_BROWSER_HANDLE;
    U8 u8PreFileBrwoserHandle = INVALID_BROWSER_HANDLE;
    pu16RenameFile = (U16*)msAPI_Memory_Allocate(CAPTURE_MAX_FILENAME_BUFFER_SIZE,BUF_ID_FILEBROWER);

    pu16RenamePath = pu16RenameFile;

    //Step 1. Dwin, BitBlt, Encode memory init
    if(!_MApp_MPlayer_CaptureVideo2BufferAndEncodeInit(CAPTURE_OUTPUT_BUFFER_ADR, CAPTURE_OUTPUT_BUFFER_LEN, CAPTURE_VIDEO_BUFFER_ADR, CAPTURE_VIDEO_BUFFER_LEN))
    {
        CAPTURE_ERR(printf("[Video Capture Error] Capture to buffer or encode init error\n"));
        eRet = E_CAPTURE_RET_FAIL;
        goto MApp_MPlayer_CaptureVideoBegin_END;
    }

    //Step 2. Check target usb status
    if((eRet = _MApp_MPlayer_CaptureCheckDrive(pCaptureVideoinfo->u8ConnectDrive)) != E_CAPTURE_RET_OK)
    {
        goto MApp_MPlayer_CaptureVideoBegin_END;
    }
    eRet = E_CAPTURE_RET_FAIL;

    //Step 3. Save Previous FileBrowser handle and create a new one
    u8PreFileBrwoserHandle = MApp_FileBrowser_GetEnvironment();
    u8CurFileBrowserHandle = MApp_FileBrowser_Create(pCaptureVideoinfo->u8ConnectDrive);
    if(u8CurFileBrowserHandle == INVALID_BROWSER_HANDLE)
    {
        CAPTURE_ERR(printf("[Video Capture Error] FileBroswser handle create failed\n"));
        eRet = E_CAPTURE_RET_FAIL;
        goto MApp_MPlayer_CaptureVideoBegin_END;
    }
    CAPTURE_DBG(printf("[Video Capture][Time:%d] Connect Drive(%d)\n", msAPI_Timer_GetTime0() ,pCaptureVideoinfo->u8ConnectDrive));
    MApp_FileBrowser_SetEnvironment(u8CurFileBrowserHandle);

    //Step 4. Go to target path and call back for updating new path
    memset(pu16RenameFile, 0, CAPTURE_MAX_FILENAME_BUFFER_SIZE);
    memcpy(pu16RenamePath, pCaptureVideoinfo->pu16CapturePath, pCaptureVideoinfo->u16CapturePathLen*sizeof(U16));
    do
    {
        if(FALSE == _MApp_MPlayer_ChangeToSpecificDirectory(pu16RenamePath, pCaptureVideoinfo->u16CapturePathLen))
        {
            CAPTURE_ERR(printf("[Video Capture Error] Change to specific directory fail\n"));
            eRet = E_CAPTURE_RET_FAIL;
            goto MApp_MPlayer_CaptureVideoBegin_END;
        }
    }
    while(pCaptureVideoinfo->pfnIsPathUpdate != NULL && TRUE == pCaptureVideoinfo->pfnIsPathUpdate(pu16RenamePath, CAPTURE_MAX_FILENAME_BUFFER_SIZE/2));

    //Step 5. Check file name
    if(pCaptureVideoinfo->pfnRenameFileIfFileExisted!= NULL)
    {
        memset(pu16RenameFile, 0, CAPTURE_MAX_FILENAME_BUFFER_SIZE);
        memcpy(pu16RenameFile, pCaptureVideoinfo->pu16FileName, pCaptureVideoinfo->u16FileNameLen*sizeof(U16));
        while(TRUE == MApp_MPlayer_IsFilenameExistInCurrentDirectory(pu16RenamePath, FS_strlen_U(pu16RenamePath)))
        {
            if(FALSE == pCaptureVideoinfo->pfnRenameFileIfFileExisted(pu16RenamePath, CAPTURE_MAX_FILENAME_BUFFER_SIZE/2))
            {
                CAPTURE_ERR(printf("[Video Capture Error] Rename file fail\n"));
                eRet = E_CAPTURE_RET_FAIL;
                goto MApp_MPlayer_CaptureVideoBegin_END;
            }
        }
    }

    //Step 6. Create file
    CAPTURE_DBG(printf("[Video Capture][Time:%d] Create file \"%s\"\n",msAPI_Timer_GetTime0(), pu16RenameFile));
    m_VideoCapture.u8WriteFileHandle = MApp_FileBrowser_OpenNewFileForWrite(pu16RenameFile, FS_strlen_U(pu16RenameFile));

    if(m_VideoCapture.u8WriteFileHandle == INVALID_FILE_HANDLE)
    {
        CAPTURE_ERR(printf("[Video Capture Error] open file for write fail  [m_u8TotalDriveNum=%d]\n ", m_u8TotalDriveNum));
        eRet = E_CAPTURE_RET_DISK_FULL;
        goto MApp_MPlayer_CaptureVideoBegin_END;
    }

    CAPTURE_ERR(printf("[Video Capture][Time:%d] Video Capture Begin OK!\n",msAPI_Timer_GetTime0()));
    eRet = E_CAPTURE_RET_OK;

MApp_MPlayer_CaptureVideoBegin_END:

    msAPI_Memory_Free(pu16RenameFile,BUF_ID_FILEBROWER);

    if(eRet != E_CAPTURE_RET_OK)
    {
        CAPTURE_DBG(printf("[Video Capture][Time:%d] Video Capture Begin Fail!\n", msAPI_Timer_GetTime0()));
        MApp_MPlayer_CaptureVideoStop();
    }

    if(u8CurFileBrowserHandle != INVALID_BROWSER_HANDLE)
    {
        MApp_FileBrowser_SetEnvironment(u8PreFileBrwoserHandle);
        MApp_FileBrowser_Destroy(u8CurFileBrowserHandle);
    }

    return eRet;
}

//******************************************************************************
/// Ask coprocessor whether picture is encoded ok and save picture to a file.
/// @param  N/A
/// @return enumCaptureRet
//******************************************************************************
enumCaptureRet MApp_MPlayer_CaptureVideoTask()
{
    if(!MApp_MPlayer_IsCapturingVideo())
    {
        return E_CAPTURE_RET_FAIL;
    }

    ST_VIDEO_CAPTURE_SET_INFO stVideoCaptureSetting;
    memset(&stVideoCaptureSetting, 0, sizeof(ST_VIDEO_CAPTURE_SET_INFO));

    if(!_MApp_MPlayer_GetVideoCaptureSetting(&stVideoCaptureSetting))
    {
        CAPTURE_ERR(printf("[Video Capture Error] Unexpected error\n"));
        MApp_MPlayer_CaptureVideoStop();
        return E_CAPTURE_RET_FAIL;
    }

    //Step 1. Check USB connection
    if(((stVideoCaptureSetting.u8ConnectPort==0)&&(MApp_MassStorage_DeviceConnectionDetect()&MS_USB_CONNECTED))
        ||((stVideoCaptureSetting.u8ConnectPort==1)&&(MApp_MassStorage_DeviceConnectionDetect()&MS_USB2_CONNECTED))
      )
    {
    }
    else
    {
        CAPTURE_ERR(printf("[Video Capture Error] USB device (%d) is unplugged\n",stVideoCaptureSetting.u8ConnectPort));
        MApp_MPlayer_CaptureVideoStop();
        return E_CAPTURE_RET_USB_FAIL;
    }

    EN_RET enPhotoRet;
    enumCaptureRet bRet = E_CAPTURE_RET_CONTINUE;
    U32 u32EncodePhotoSize;
    U32 u32RemainBytes = 0;

    FileEntry stBackupDstFileEntry;
    memset(&stBackupDstFileEntry, 0, sizeof(FileEntry));

    //Step 2. Check current encoding status
    enPhotoRet = MApp_Photo_Main();

    switch(enPhotoRet)
    {
        case EXIT_PHOTO_DECODING:
            m_VideoCapture.u8Progress = MApp_Photo_GetInfo(E_PHOTO_INFO_PROGRESS);
            //CAPTURE_DBG(printf("[Video Capture][Time:%d] Photo Encoding Progress:%lu\n",msAPI_Timer_GetTime0(), m_VideoCapture.u8Progress));
            break;
        case EXIT_PHOTO_DECODE_DONE:
            u32EncodePhotoSize = MApp_Photo_GetInfo(E_PHOTO_INFO_SIZE);

            MApp_Photo_Stop();

            CAPTURE_DBG(printf("[Video Capture][Time:%d] JPEG Encode:  total %u bytes\n",msAPI_Timer_GetTime0(), u32EncodePhotoSize));

            u32RemainBytes = msAPI_FCtrl_FileWrite(m_VideoCapture.u8WriteFileHandle, m_VideoCapture.u32EncodeDstBuffer, u32EncodePhotoSize);

            if(u32RemainBytes > 0) // if write file error, delete the created file
            {
                CAPTURE_ERR(printf("[Video Capture Error] This file disk is full, and write file error\n"));
                bRet = E_CAPTURE_RET_DISK_FULL;

                if(msAPI_FCtrl_EntryGetByHandle(m_VideoCapture.u8WriteFileHandle, &stBackupDstFileEntry))
                {
                    CAPTURE_DBG(printf("[Video Capture] This file disk is full, delete the created file\n"));
                    msAPI_FCtrl_FileDelete(&stBackupDstFileEntry);
                }
            }
            else
            {
                CAPTURE_DBG(printf("[Video Capture][Time:%d] JPEG save file done\n",msAPI_Timer_GetTime0()));
                bRet = E_CAPTURE_RET_OK;
            }

            MApp_MPlayer_CaptureVideoStop();

            break;
        default:
            CAPTURE_DBG(printf("[Video Capture][Time:%d] Photo Encode Error. Ret:%d\n",msAPI_Timer_GetTime0(),enPhotoRet));
            // if encoding error, delete the created file
            if(msAPI_FCtrl_EntryGetByHandle(m_VideoCapture.u8WriteFileHandle, &stBackupDstFileEntry))
            {
                CAPTURE_DBG(printf("[Video Capture] This file disk is full, delete the created file\n"));
                msAPI_FCtrl_FileDelete(&stBackupDstFileEntry);
            }
            MApp_MPlayer_CaptureVideoStop();
            bRet = E_CAPTURE_RET_FAIL;
            break;
    }

    return bRet;
}

//******************************************************************************
/// Stop the video capture process
/// @param  N/A
/// @return enumCaptureRet
//******************************************************************************
enumCaptureRet MApp_MPlayer_CaptureVideoStop(void)
{
    ST_VIDEO_CAPTURE_SET_INFO stVideoCaptureSetting;
    memset(&stVideoCaptureSetting, 0, sizeof(ST_VIDEO_CAPTURE_SET_INFO));

    if(!_MApp_MPlayer_GetVideoCaptureSetting(&stVideoCaptureSetting))
    {
        CAPTURE_ERR(printf("[Video Capture Error] Unexpected error\n"));
        return E_CAPTURE_RET_USB_FAIL;
    }

    if(m_VideoCapture.u8WriteFileHandle != INVALID_FILE_HANDLE)
    {
        msAPI_FCtrl_FileClose(m_VideoCapture.u8WriteFileHandle);
        m_VideoCapture.u8WriteFileHandle = INVALID_FILE_HANDLE;
    }

    MApp_Photo_Stop();
    if(stVideoCaptureSetting.bLoadCoprocessor == TRUE)
    {
        MDrv_COPRO_Disable();
    }

    return E_CAPTURE_RET_OK;
}

//******************************************************************************
/// Check if the video capturing is on-going.
/// @param  N/A
/// @return BOOLEAN
//******************************************************************************
BOOLEAN MApp_MPlayer_IsCapturingVideo(void)
{
    if(m_VideoCapture.u8WriteFileHandle != INVALID_FILE_HANDLE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

//******************************************************************************
/// Get ST_VIDEO_CAPTURE_GET_INFO from Video Capture variables
/// @param  pVideoCaptureInfo  \b OUT Specify ST_VIDEO_CAPTURE_GET_INFO
/// @return TRUE/FALSE.
//******************************************************************************
BOOLEAN MApp_MPlayer_GetVideoCaptureInfo(ST_VIDEO_CAPTURE_GET_INFO* pVideoCaptureGetInfo)
{

    if (pVideoCaptureGetInfo == NULL)
    {
        return FALSE;
    }

    pVideoCaptureGetInfo->u8Progress = m_VideoCapture.u8Progress;

    return TRUE;
}

//******************************************************************************
/// Capture the current screen by Dwin and bitblt, and initialize encoding.
///           -------------                  --------------
/// 1.Dwin ->|             | -> 2.BitBlt -> |              |
///          |             |                |              |
///          | FirstBuffer |<- 3.Thumbnail<-| SecondBuffer |
///          |             |                |              |
///          |             | <- 4.Encode <- |              |
///           -------------                  --------------
/// @param  pFileName \b IN Specify the file name.
/// @param  u8pTmpBuffAddr \b IN Specify the tmp buffer addr.
/// @param  u8pTmpBuffAddr \b IN Specify the tmp buffer size.
/// @return BOOLEAN
//******************************************************************************
static BOOLEAN _MApp_MPlayer_CaptureVideo2BufferAndEncodeInit(U32 u32FirstBufferAddr, U32 u32FirstBufferSize, U32 u32SecondBufferAddr, U32 u32SecondBufferSize)
{
    U8 gopBank;
    GOP_DwinProperty dwinProperty;
    GEBitBltInfo stBitbltInfo;
    GEPitBaseInfo stPitBaseInfo;

    BOOLEAN bIsFreezeByCapture = FALSE;

    XC_ApiStatus stXC_WinTime_Info;
    ST_VIDEO_CAPTURE_SET_INFO stVideoCaptureSetting;

    U32 u32DwinDstBuffer, u32DwinDstBufferSize;
    U32 u32BitBltDstBuffer, u32BitBltDstBufferSize;
    U32 u32EncodeDstBuffer, u32EncodeDstBufferSize;
    U32 u32EncodePoolMemAddr, u32EncodePoolMemSize;

    U16 u16DwinCaptureWidth, u16DwinCaptureHeight;
    U16 u16BitBltDstWidth, u16BitBltDstHeight;

    //Dwin Dst Buffer = First Buffer
    u32DwinDstBuffer     = u32FirstBufferAddr;
    u32DwinDstBufferSize = u32FirstBufferSize;

    //BitBlt Dst Buffer = Second Buffer
    u32BitBltDstBuffer     = u32SecondBufferAddr;
    u32BitBltDstBufferSize = u32SecondBufferSize;

    //Encode Dst Buffer = First Buffer
    u32EncodeDstBuffer     = u32FirstBufferAddr;
    u32EncodeDstBufferSize = 0x100000;  // 1 MB

    //Encode Pool Mem
    u32EncodePoolMemAddr = u32EncodeDstBuffer + u32EncodeDstBufferSize;
    u32EncodePoolMemSize = 0x80000;  // 512K

    //initialize
    memset(&stBitbltInfo, 0, sizeof(GEBitBltInfo));
    memset(&stPitBaseInfo, 0, sizeof(GEPitBaseInfo));
    memset(&stXC_WinTime_Info, 0, sizeof(XC_ApiStatus));
    memset(&stVideoCaptureSetting, 0, sizeof(ST_VIDEO_CAPTURE_SET_INFO));

    if(!_MApp_MPlayer_GetVideoCaptureSetting(&stVideoCaptureSetting))
    {
        return FALSE;
    }

    /////////////////////////////////
    //// Step 1. Freeze Screen
    /////////////////////////////////

    if(stVideoCaptureSetting.bScreenFreeze == FALSE) // screen is not freezed
    {
        CAPTURE_DBG(printf("[Video Capture][Time:%d] Freeze screen\n",msAPI_Timer_GetTime0()));
        MApi_XC_FreezeImg(TRUE, MAIN_WINDOW);
        bIsFreezeByCapture = TRUE;
    }
    /////////////////////////////////
    //// Step 2. Get Scaler info
    /////////////////////////////////

    CAPTURE_DBG(printf("[Video Capture][Time:%d] Get Scaler Info\n",msAPI_Timer_GetTime0()));
    if(MApi_XC_GetStatus(&stXC_WinTime_Info, MAIN_WINDOW) == FALSE)
    {
        CAPTURE_ERR(printf("MApi_XC_GetStatus failed because of InitData wrong, please update header file and compile again\n"));
        return FALSE;
    }
    CAPTURE_DBG(printf("[Video capture] video DWIN addr=%x, size=%x\n", u32DwinDstBuffer, u32DwinDstBufferSize));
    CAPTURE_DBG(printf("\tXC info x: %u, y: %u, w: %u, h: %u\n",
            stXC_WinTime_Info.stDispWin.x,
            stXC_WinTime_Info.stDispWin.y,
            stXC_WinTime_Info.stDispWin.width,
            stXC_WinTime_Info.stDispWin.height));
    //MApi_GFX_ClearFrameBuffer(u32TmpBuffAddr, u32TmpBuffSize, 0x0); // fill frame buffer with 0, black
    //after clear frame buffer, flush cmd
    //MApi_GFX_FlushQueue();

    u16DwinCaptureWidth = stXC_WinTime_Info.stDispWin.width & 0xFFF0;   // Need 16 pixel alignment for JPEG encoder.
    u16DwinCaptureHeight = stXC_WinTime_Info.stDispWin.height;

    if(u16DwinCaptureHeight > g_IPanel.Height())
    {
        u16DwinCaptureHeight = g_IPanel.Height();
    }

    if((U32)u16DwinCaptureWidth*u16DwinCaptureHeight*2 > u32DwinDstBufferSize)
    {
        CAPTURE_ERR(printf("[Video capture Error] Dwin Buffer (0x%x) is smaller than WxHx2 (%ux%ux2)\n",u32DwinDstBufferSize,u16DwinCaptureWidth,u16DwinCaptureHeight));
        return FALSE;
    }

    CAPTURE_DBG(printf("\tDisplay, x: %u, y: %u, w: %u, h: %u\n",
            stXC_WinTime_Info.stDispWin.x,
            stXC_WinTime_Info.stDispWin.y,
            u16DwinCaptureWidth,
            u16DwinCaptureHeight));
    /////////////////////////////////
    //// Step 3. Use DWIN to capture Image
    /////////////////////////////////

    CAPTURE_DBG(printf("[Video Capture][Time:%d] Use DWIN to capture video\n",msAPI_Timer_GetTime0()));

    MApi_GOP_DWIN_EnableR2YCSC(ENABLE);
    MApi_GOP_DWIN_Init();
    gopBank = MApi_GOP_GWIN_GetCurrentGOP();
    if(gopBank != E_GOP_CAP)
    {
       MApi_GOP_GWIN_SwitchGOP(E_GOP_CAP);
    }

    // set GOPD clock
    MApi_GOP_SetClkForCapture();
    MApi_GOP_DWIN_SelectSourceScanType(DWIN_SCAN_MODE_PROGRESSIVE);
    MApi_GOP_DWIN_SetDataFmt(DWIN_DATA_FMT_UV8Y8);
    MApi_GOP_DWIN_SetSourceSel(DWIN_SRC_OP);
    //MApi_GOP_DWIN_SetUVSwap(ENABLE); // UV values should be swaped if skip the bitblit.
    //For M12 chip, because the of scaler timing of main window, the original point is the left-top of main window, not panal.
    dwinProperty.u16x = 0;
    dwinProperty.u16y = 0;
    dwinProperty.u16h = u16DwinCaptureHeight; //- 1;
    dwinProperty.u32fbaddr0 = u32DwinDstBuffer;
    dwinProperty.u32fbaddr1 = u32DwinDstBuffer + u32DwinDstBufferSize;
    dwinProperty.u16w = (u16DwinCaptureWidth & 0xffff);
    dwinProperty.u16fbw = u16DwinCaptureWidth & 0xffff;

    CAPTURE_DBG(printf("\tDWIN x=%d , y=%d , w=%d , h=%d \n",dwinProperty.u16x, dwinProperty.u16y, dwinProperty.u16w , dwinProperty.u16h) );
    CAPTURE_DBG(printf("\tDWIN addr low=0x%x, addr high=0x%x \n",dwinProperty.u32fbaddr0 ,dwinProperty.u32fbaddr1 ));

    // enable DWIN progressive INT
    MApi_GOP_DWIN_SetWinProperty(&dwinProperty);
    MApi_GOP_DWIN_SetAlphaValue(0x0f); // set to solid
    msAPI_Timer_Delayms(10);
    MApi_GOP_DWIN_CaptureOneFrame();
    msAPI_Timer_Delayms(50);
    MApi_GOP_DWIN_Enable(FALSE);
    if(gopBank != E_GOP_CAP)
    {
        MApi_GOP_GWIN_SwitchGOP(gopBank);
    }

    MApi_GOP_DWIN_EnableR2YCSC(DISABLE);

    /////////////////////////////////
    //// Step 4. De-freeze Screen
    /////////////////////////////////

    CAPTURE_DBG(printf("[Video Capture][Time:%d] DeFreeze\n", msAPI_Timer_GetTime0()));
    if (MApi_XC_IsFreezeImg(MAIN_WINDOW) && bIsFreezeByCapture)
    {
        MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);
    }

    /////////////////////////////////
    //// Step 5. BitBlt
    /////////////////////////////////

    //keep bitblit step for customizing the output size and rotating photo in mirror mode
    u16BitBltDstWidth = u16DwinCaptureWidth;
    u16BitBltDstHeight = u16DwinCaptureHeight;

    u16BitBltDstWidth &= 0xfff0; // JPEG encoder requires 16-pixel alignment of width
    u16BitBltDstHeight &= 0xfff8; // JPEG encoder requires 8-pixel alignment of height

    CAPTURE_DBG(printf("[Video Capture][Time:%d] Bitblt dst addr=0x%x\n", msAPI_Timer_GetTime0(), u32BitBltDstBuffer));
    CAPTURE_DBG(printf("\tBitBlt: %ux%u --> %ux%u\n",
            u16DwinCaptureWidth,
            u16DwinCaptureHeight,
            u16BitBltDstWidth,
            u16BitBltDstHeight));

    if((U32)u16BitBltDstWidth*u16BitBltDstHeight*2 > u32BitBltDstBuffer)
    {
        CAPTURE_ERR(printf("[Video capture Error] BitBlt Dst Buffer (0x%x) is smaller than W*H*2 (%ux%ux2)\n",u32BitBltDstBuffer,u16BitBltDstWidth,u16BitBltDstHeight));
        return FALSE;
    }

    // Zoom source
    stPitBaseInfo.sb_pit = u16DwinCaptureWidth * 2;      // 2 bytes per pixel, the pitch is referring to original image
    stPitBaseInfo.sb_base = u32DwinDstBuffer;     // the address is referring to original image
    stPitBaseInfo.db_pit = u16BitBltDstWidth * 2;
    stPitBaseInfo.db_base = u32BitBltDstBuffer;

    stBitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
    stBitbltInfo.BmpFlag        = GFXDRAW_FLAG_DEFAULT;
    stBitbltInfo.dst_fm         = GFX_FMT_YUV422;
    stBitbltInfo.src_fm         = GFX_FMT_YUV422;
    stBitbltInfo.src_width      = u16DwinCaptureWidth;
    stBitbltInfo.src_height     = u16DwinCaptureHeight;
    stBitbltInfo.BitbltCoordinate.v2_x = 0;
    stBitbltInfo.BitbltCoordinate.v2_y = 0;
    stBitbltInfo.BitbltCoordinate.direction = 0; // TODO: what's this?
    stBitbltInfo.BitbltCoordinate.v0_x = 0;
    stBitbltInfo.BitbltCoordinate.v0_y = 0;

    stBitbltInfo.BitbltCoordinate.width = u16BitBltDstWidth;
    stBitbltInfo.BitbltCoordinate.height = u16BitBltDstHeight;

    CAPTURE_DBG(printf("\tBitblt src w=%d, h=%d \n", stBitbltInfo.src_width ,stBitbltInfo.src_height ) );
    CAPTURE_DBG(printf("\tBitblt dst w=%d, h=%d \n", stBitbltInfo.BitbltCoordinate.width,stBitbltInfo.BitbltCoordinate.height ));

    msAPI_OSD_SetClipWindow(0, 0, u16BitBltDstWidth, u16BitBltDstHeight);

    MApi_GFX_SetNearestMode(FALSE);
    MApi_GFX_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_255, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YVYU,  GFX_YUV_YUYV);
    MApi_GFX_SetPatchMode(TRUE);

    //if in mirror mode, rotate.
    if(MApi_XC_GetMirrorModeType() == MIRROR_HV)
    {
        msAPI_GE_SetRotate(GEROTATE_180);
    }

    // output image to destination buffer
    msAPI_GE_BitBlt(&stBitbltInfo, &stPitBaseInfo);
    // after BitBlt, flush cmd
    MApi_GFX_FlushQueue();

    MApi_GFX_SetPatchMode(FALSE);

    // NOTE: it's critical to reset GE registers after rotation
    msAPI_GE_SetMirror(0, 0);
    msAPI_GE_SetRotate(GEROTATE_0);

    msAPI_OSD_SetClipWindow(0, 0, g_IPanel.Width(), g_IPanel.Height());

    /////////////////////////////////
    //// Step 6. Thumbnail
    /////////////////////////////////

    if(stVideoCaptureSetting.ThumbBitBltInfo.bThumbnail)
    {
        ST_PHOTO_SHRINK_SETTING stShrinkSetting;
        memset(&stShrinkSetting, 0, sizeof(ST_PHOTO_SHRINK_SETTING));

        // co-buffers using FirstBuffer
        // 1.0, thumbnail shrink buffer 0
        #define PHOTO_CAPTURE_SHRINK_BUFFER_0_ADDR    PHOTO_ALIGNMENT(u32FirstBufferAddr)
        #define PHOTO_CAPTURE_SHRINK_BUFFER_0_SIZE    (YUV422_BYTE_PER_PIXEL * PHOTO_SHRINK_BUFFER_0_WIDTH * PHOTO_SHRINK_BUFFER_0_HEIGHT)

        // 1.1, thumbnail shrink buffer 0
        #define PHOTO_CAPTURE_SHRINK_BUFFER_1_ADDR    PHOTO_ALIGNMENT(PHOTO_CAPTURE_SHRINK_BUFFER_0_ADDR + PHOTO_CAPTURE_SHRINK_BUFFER_0_SIZE)
        #define PHOTO_CAPTURE_SHRINK_BUFFER_1_SIZE    (YUV422_BYTE_PER_PIXEL * PHOTO_SHRINK_BUFFER_1_WIDTH * PHOTO_SHRINK_BUFFER_1_HEIGHT)

        stPitBaseInfo.sb_pit = u16BitBltDstWidth * 2;      // YUV422: 2 bytes per pixel, the pitch is referring to original image
        stPitBaseInfo.sb_base = u32BitBltDstBuffer;         // the address is referring to original image
        stPitBaseInfo.db_pit = stVideoCaptureSetting.ThumbBitBltInfo.u16Pitch;
        stPitBaseInfo.db_base = stVideoCaptureSetting.ThumbBitBltInfo.u32BufferBaseAddr;

        CAPTURE_DBG(printf("Thumbnail[Time:%d] Bitblt Srcaddr=0x%x Dstaddr=0x%x\n", msAPI_Timer_GetTime0(), u32BitBltDstBuffer, stPitBaseInfo.db_base));

        stBitbltInfo.BitBltTypeFlag = GEBitbltType_Normal;
        stBitbltInfo.BmpFlag        = GFXDRAW_FLAG_DEFAULT;
        stBitbltInfo.dst_fm         = stVideoCaptureSetting.ThumbBitBltInfo.format;
        stBitbltInfo.src_fm         = GFX_FMT_YUV422;
        stBitbltInfo.src_width      = u16BitBltDstWidth;
        stBitbltInfo.src_height     = u16BitBltDstHeight;
        stBitbltInfo.BitbltCoordinate.v2_x = 0;
        stBitbltInfo.BitbltCoordinate.v2_y = 0;
        stBitbltInfo.BitbltCoordinate.direction = 0; // TODO: what's this?
        stBitbltInfo.BitbltCoordinate.v0_x = stVideoCaptureSetting.ThumbBitBltInfo.u16Coordinate_X;
        stBitbltInfo.BitbltCoordinate.v0_y = stVideoCaptureSetting.ThumbBitBltInfo.u16Coordinate_Y;

        stBitbltInfo.BitbltCoordinate.width = stVideoCaptureSetting.ThumbBitBltInfo.u16Width;
        stBitbltInfo.BitbltCoordinate.height = stVideoCaptureSetting.ThumbBitBltInfo.u16Height;

        CAPTURE_DBG(printf("\tThumbnail: Bitblt Mirror H:%d V:%d \n", stVideoCaptureSetting.ThumbBitBltInfo.bHMirror,stVideoCaptureSetting.ThumbBitBltInfo.bVMirror));
        msAPI_GE_SetMirror(stVideoCaptureSetting.ThumbBitBltInfo.bHMirror,stVideoCaptureSetting.ThumbBitBltInfo.bVMirror);

        CAPTURE_DBG(printf("\tThumbnail: Bitblt src w=%d, h=%d \n", stBitbltInfo.src_width ,stBitbltInfo.src_height ) );
        CAPTURE_DBG(printf("\tThumbnail: Bitblt dst w=%d, h=%d \n", stBitbltInfo.BitbltCoordinate.width,stBitbltInfo.BitbltCoordinate.height ));

        stShrinkSetting.enRotation = EN_PHOTO_ROTATE_0;
        stShrinkSetting.u32SpecialEffectBuffer0 = PHOTO_CAPTURE_SHRINK_BUFFER_0_ADDR;
        stShrinkSetting.u32SpecialEffectBuffer0Length = PHOTO_CAPTURE_SHRINK_BUFFER_0_SIZE;
        stShrinkSetting.u32SpecialEffectBuffer1 = PHOTO_CAPTURE_SHRINK_BUFFER_1_ADDR;
        stShrinkSetting.u32SpecialEffectBuffer1Length = PHOTO_CAPTURE_SHRINK_BUFFER_1_SIZE;
        MApp_Photo_ShrinkImage(&stBitbltInfo, &stPitBaseInfo, &stShrinkSetting);

        msAPI_OSD_SetClipWindow(stVideoCaptureSetting.ThumbBitBltInfo.u16Coordinate_X, stVideoCaptureSetting.ThumbBitBltInfo.u16Coordinate_Y,
            stVideoCaptureSetting.ThumbBitBltInfo.u16Coordinate_X+stVideoCaptureSetting.ThumbBitBltInfo.u16Width,
            stVideoCaptureSetting.ThumbBitBltInfo.u16Coordinate_Y+stVideoCaptureSetting.ThumbBitBltInfo.u16Height);

        MApi_GFX_SetNearestMode(FALSE);

        msAPI_GE_SetDC_CSC_FMT(GFX_YUV_RGB2YUV_PC, GFX_YUV_OUT_255, GFX_YUV_IN_255, GFX_YUV_YUYV, GFX_YUV_YUYV);
        msAPI_GE_SetPatchMode(TRUE);

        // output image to destination buffer
        msAPI_GE_BitBlt(&stBitbltInfo, &stPitBaseInfo);
        // after BitBlt, flush cmd
        MApi_GFX_FlushQueue();
        MApi_GFX_SetPatchMode(FALSE);

        // NOTE: it's critical to reset GE registers after rotation
        msAPI_GE_SetMirror(0, 0);
        msAPI_GE_SetRotate(GEROTATE_0);

        msAPI_OSD_SetClipWindow(0, 0, g_IPanel.Width(), g_IPanel.Height());
    }

    /////////////////////////////////
    //// Step 7. Init Coprocessor
    /////////////////////////////////

    if(stVideoCaptureSetting.bLoadCoprocessor == TRUE)
    {
        //Todo: while in MM, coprocessor init process will have error.
        CAPTURE_DBG(printf("[Video Capture][Time:%d] Init Coprocessor\n",msAPI_Timer_GetTime0()));

#if( VD_PLAYER_IS_IN_CROP_CPU )
        #if defined(MIPS_CHAKRA) || defined(MSOS_TYPE_LINUX) || defined(__AEONR2__)
            msAPI_COPRO_Init(BIN_ID_CODE_VDPLAYER,((AEON_MEM_MEMORY_TYPE & MIU1) ? (AEON_MM_MEM_ADR | MIU_INTERVAL) : (AEON_MM_MEM_ADR)),AEON_MM_MEM_LEN);
        #else
            msAPI_COPRO_Init(BIN_ID_CODE_VDPLAYER,((BEON_MEM_MEMORY_TYPE & MIU1) ? (BEON_MEM_ADR | MIU_INTERVAL) : ( BEON_MEM_ADR)),BEON_MEM_LEN);
        #endif
#endif
    }

    /////////////////////////////////
    //// Step 8. Encode memory config
    /////////////////////////////////

    CAPTURE_DBG(printf("[Video Capture][Time:%d] Compress image to JPEG\n", msAPI_Timer_GetTime0()));

    MApp_Photo_MemCfg(
            u32BitBltDstBuffer, (U32)u16BitBltDstWidth* u16BitBltDstHeight* 2,
            u32EncodeDstBuffer, u32EncodeDstBufferSize,
            u32EncodePoolMemAddr, u32EncodePoolMemSize, u32EncodePoolMemSize);

    CAPTURE_DBG(printf("\tPhoto Mem Data Addr:0x%x Size:0x%x, Output Addr:0x%x Size:0x%x, Pool Addr:0x%x Size:0x%x\n",
            u32BitBltDstBuffer, (U32)u16BitBltDstWidth * u16BitBltDstHeight * 2,
            u32EncodeDstBuffer, u32EncodeDstBufferSize,
            u32EncodePoolMemAddr, u32EncodePoolMemSize));

    m_VideoCapture.u32EncodeDstBuffer = u32EncodeDstBuffer;
    m_VideoCapture.u8Progress = 0;

    /////////////////////////////////
    //// Step 9. Encode memory init and start decode
    /////////////////////////////////

    if (MApp_Photo_EncodeMemory_Init(u16BitBltDstWidth, u16BitBltDstHeight, NULL))
    {
        CAPTURE_DBG(printf("[Video Capture][Time:%d] MApp_Photo_EncodeMemory_Init OK\n", msAPI_Timer_GetTime0()));
        MApp_Photo_Main(); // send command to coprocessor to start encode immediately
        return TRUE;
    }

    return FALSE;
}

//******************************************************************************
/// Set ST_VIDEO_CAPTURE_SET_INFO to m_VideoCaptureSetting
/// @param  pVideoCaptureSetInfo  \b IN Specify ST_VIDEO_CAPTURE_SET_INFO
/// @return TRUE/FALSE.
//******************************************************************************
static BOOLEAN _MApp_MPlayer_SetVideoCaptureSetting(ST_VIDEO_CAPTURE_SET_INFO* pVideoCaptureSetInfo)
{
    BOOLEAN ret = FALSE;

    if (pVideoCaptureSetInfo != NULL)
    {
        if(pVideoCaptureSetInfo->pfnRenameFileIfFileExisted == NULL)
        {
            pVideoCaptureSetInfo->pfnRenameFileIfFileExisted = &_MApp_MPlayer_RenameFileIfFileExisted;
        }

        memcpy(&m_VideoCaptureSetting, pVideoCaptureSetInfo, sizeof(ST_VIDEO_CAPTURE_SET_INFO));
        ret = TRUE;
    }

    return ret;
}

//******************************************************************************
/// Get ST_VIDEO_CAPTURE_SET_INFO from m_VideoCaptureSetting
/// @param  pVideoCaptureSetInfo  \b IN Specify ST_VIDEO_CAPTURE_SET_INFO
/// @return TRUE/FALSE.
//******************************************************************************
static BOOLEAN _MApp_MPlayer_GetVideoCaptureSetting(ST_VIDEO_CAPTURE_SET_INFO* pVideoCaptureSetInfo)
{
    if (pVideoCaptureSetInfo == NULL)
    {
        return FALSE;
    }

    memcpy(pVideoCaptureSetInfo, &m_VideoCaptureSetting, sizeof(ST_VIDEO_CAPTURE_SET_INFO));

    return TRUE;
}

#endif  // #if (ENABLE_MPLAYER_VIDEO_CAPTURE)

#if (ENABLE_MPLAYER_AUDIO_CAPTURE)
//******************************************************************************
/// Begin to capture audio data from PCM buffer
/// @param  pCaptureAudioinfo  \b IN Specify ST_AUDIO_CAPTURE_SET_INFO
/// @return enumCaptureRet
//******************************************************************************
enumCaptureRet MApp_MPlayer_CaptureAudioBegin(ST_AUDIO_CAPTURE_SET_INFO *pCaptureAudioinfo)
{
    enumCaptureRet eRet = E_CAPTURE_RET_FAIL;

    CAPTURE_DBG(printf("[Audio Capture] Begin\n"));
    if(pCaptureAudioinfo == NULL)
    {
        return E_CAPTURE_RET_FAIL;
    }

    if(MApp_MPlayer_IsCapturingAudio())
    {
        CAPTURE_ERR(printf("[Audio Capture Error] Audio capturing! Fail to begin a new capture.\n");)
        return E_CAPTURE_RET_IGNORE;
    }

    if(((pCaptureAudioinfo->u8ConnectPort==0)&&(MApp_MassStorage_DeviceConnectionDetect()&MS_USB_CONNECTED))
        ||((pCaptureAudioinfo->u8ConnectPort==1)&&(MApp_MassStorage_DeviceConnectionDetect()&MS_USB2_CONNECTED))
      )
    {
    }
    else
    {
        CAPTURE_ERR(printf("[Audio Capture Error] There is no USB connected\n");)
        return E_CAPTURE_RET_USB_FAIL;
    }

    _MApp_MPlayer_SetAudioCaptureSetting(pCaptureAudioinfo);

    U16* pu16RenameFile;
    U16* pu16RenamePath;
    U8 u8CurFileBrowserHandle = INVALID_BROWSER_HANDLE;
    U8 u8PreFileBrwoserHandle = INVALID_BROWSER_HANDLE;
    U8 u8Header[CAPTURE_AUDIO_WAV_HEADER_LEN];

    pu16RenameFile = (U16*)msAPI_Memory_Allocate(CAPTURE_MAX_FILENAME_BUFFER_SIZE,BUF_ID_FILEBROWER);
    pu16RenamePath = pu16RenameFile;

    //Step 1. Check target usb status
    if((eRet = _MApp_MPlayer_CaptureCheckDrive(pCaptureAudioinfo->u8ConnectDrive)) != E_CAPTURE_RET_OK)
    {
        goto MApp_MPlayer_CaptureAudioBegin_END;
    }
    eRet = E_CAPTURE_RET_FAIL;

    if(!IsStorageInUse())
    {
        CAPTURE_DBG(printf("[Audio Capture] Init FS, MassStorage.\n"));
        MApp_MassStorage_Init();
        msAPI_FS_Init();

        if(!msAPI_FCtrl_IsDriveMounted(pCaptureAudioinfo->u8ConnectDrive))
        {
            if (MApp_MassStorage_DeviceChangeStatusCheck())
            {
                MApp_MassStorage_DeviceStatusCheck();
                MApp_MPlayer_InitializeAllDevices();
            }
        }
    }

    //Step 2. Save Previous FileBrowser handle and create a new one
    u8PreFileBrwoserHandle = MApp_FileBrowser_GetEnvironment();
    u8CurFileBrowserHandle = MApp_FileBrowser_Create(pCaptureAudioinfo->u8ConnectDrive);
    if(u8CurFileBrowserHandle == INVALID_BROWSER_HANDLE)
    {
        CAPTURE_ERR(printf("[Audio Capture Error] FileBroswser handle create failed\n"));
        eRet = E_CAPTURE_RET_FAIL;
        goto MApp_MPlayer_CaptureAudioBegin_END;
    }
    CAPTURE_DBG(printf("[Audio Capture][Time:%d] Connect Drive(%d)\n", msAPI_Timer_GetTime0() ,pCaptureAudioinfo->u8ConnectDrive));
    MApp_FileBrowser_SetEnvironment(u8CurFileBrowserHandle);

    //Step 3. Go to target path and call back for updating new path
    memset(pu16RenameFile, 0, CAPTURE_MAX_FILENAME_BUFFER_SIZE);
    memcpy(pu16RenamePath, pCaptureAudioinfo->pu16CapturePath, sizeof(U16)*FS_strlen_U(pCaptureAudioinfo->pu16CapturePath));
    do
    {
        if(FALSE == _MApp_MPlayer_ChangeToSpecificDirectory(pu16RenamePath, pCaptureAudioinfo->u16CapturePathLen))
        {
            CAPTURE_ERR(printf("[Audio Capture Error] Change to specific directory fail\n"));
            eRet = E_CAPTURE_RET_FAIL;
            goto MApp_MPlayer_CaptureAudioBegin_END;
        }
    }
    while(pCaptureAudioinfo->pfnIsPathUpdate != NULL && TRUE == pCaptureAudioinfo->pfnIsPathUpdate(pu16RenamePath, CAPTURE_MAX_FILENAME_BUFFER_SIZE/2));

    //Step 4. Check file name
    if(pCaptureAudioinfo->pfnRenameFileIfFileExisted!= NULL)
    {
        memset(pu16RenameFile, 0, CAPTURE_MAX_FILENAME_BUFFER_SIZE);
        memcpy(pu16RenameFile, pCaptureAudioinfo->pu16FileName, pCaptureAudioinfo->u16FileNameLen*sizeof(U16));
        while(TRUE == MApp_MPlayer_IsFilenameExistInCurrentDirectory(pu16RenamePath, FS_strlen_U(pu16RenamePath)))
        {
            if(FALSE == pCaptureAudioinfo->pfnRenameFileIfFileExisted(pu16RenamePath, CAPTURE_MAX_FILENAME_BUFFER_SIZE/2))
            {
                CAPTURE_ERR(printf("[Audio Capture Error] Rename file fail\n"));
                eRet = E_CAPTURE_RET_FAIL;
                goto MApp_MPlayer_CaptureAudioBegin_END;
            }
        }
    }

    //Step 5. Create file
    CAPTURE_DBG(printf("[Audio Capture] Create file \"%s\"\n", pu16RenameFile));
    m_AudioCapture.u8WriteFileHandle = MApp_FileBrowser_OpenNewFileForWrite(pu16RenameFile, FS_strlen_U(pu16RenameFile));

    if(m_AudioCapture.u8WriteFileHandle == INVALID_FILE_HANDLE)
    {
        CAPTURE_ERR(printf("[Audio Capture Error] open file for write fail\n"));
        eRet = E_CAPTURE_RET_DISK_FULL;
        goto MApp_MPlayer_CaptureAudioBegin_END;
    }

    //Step 6. Generate WAV header
    m_AudioCapture.u32DataChunkSize = 0;
    m_AudioCapture.u16Channels = CAPTURE_AUDIO_WAV_CHANNELS;
    m_AudioCapture.u32SampleRate = CAPTURE_AUDIO_WAV_SAMPLE_RATE;
    m_AudioCapture.u16BitsPerSample = CAPTURE_AUDIO_WAV_BITS_PER_SAMPLE;
    m_AudioCapture.u32CurPCMOffset = 0;
    m_AudioCapture.u32PrePCMOffset = 0;

    if(_Mapp_MPlayer_WAVHeaderGenerator(u8Header, sizeof(u8Header), &m_AudioCapture))
    {
        MsOS_Dcache_Flush((U32)u8Header, sizeof(u8Header));
        MsOS_FlushMemory();
        msAPI_FCtrl_FileWrite(m_AudioCapture.u8WriteFileHandle, _VA2PA((U32)&u8Header), CAPTURE_AUDIO_WAV_HEADER_LEN);
        CAPTURE_DBG(printf("[Audio Capture] Get sample rate=%d\n",m_AudioCapture.u32SampleRate));
        CAPTURE_DBG(printf("[Audio Capture] Reading Length: 0x%x\n",CAPTURE_AUDIO_READ_LEN));
    }
    else
    {
        CAPTURE_ERR(printf("[Audio Capture Error] Wrong WAV Header at begin\n"));
        eRet = E_CAPTURE_RET_FAIL;
        goto MApp_MPlayer_CaptureAudioBegin_END;
    }

    //Step 7. Enable PCM capture function
    if(MApi_AUDIO_PCMCapture_Init(E_DEVICE0, E_CAPTURE_CH5))
    {
        MApi_AUDIO_PCMCapture_Start(E_DEVICE0);
        eRet = E_CAPTURE_RET_OK;
        CAPTURE_ERR(printf("[Audio Capture] Init OK\n"));
    }
    else
    {
        eRet = E_CAPTURE_RET_FAIL;
        CAPTURE_ERR(printf("[Audio Capture] Init Fail\n"));
    }

MApp_MPlayer_CaptureAudioBegin_END:

    msAPI_Memory_Free(pu16RenameFile,BUF_ID_FILEBROWER);

    if(eRet != E_CAPTURE_RET_OK)
    {
        MApp_MPlayer_CaptureAudioStop();
    }

    if(u8CurFileBrowserHandle != INVALID_BROWSER_HANDLE)
    {
        MApp_FileBrowser_SetEnvironment(u8PreFileBrwoserHandle);
        MApp_FileBrowser_Destroy(u8CurFileBrowserHandle);
    }

    return eRet;
}

//******************************************************************************
/// Capture the current audio and save audio data to a file.
/// @param  N/A
/// @return enumCaptureRet
//******************************************************************************
enumCaptureRet MApp_MPlayer_CaptureAudioTask()
{
    enumCaptureRet eRet = E_CAPTURE_RET_FAIL;

    if(!MApp_MPlayer_IsCapturingAudio())
    {
        eRet = E_CAPTURE_RET_FAIL;
        goto MApp_MPlayer_CaptureAudioTask_END;
    }

    ST_AUDIO_CAPTURE_SET_INFO stAudioCaptureSetting;
    memset(&stAudioCaptureSetting, 0, sizeof(ST_AUDIO_CAPTURE_SET_INFO));

    if(!_MApp_MPlayer_GetAudioCaptureSetting(&stAudioCaptureSetting))
    {
        CAPTURE_ERR(printf("[Audio Capture Error] Unexpected error\n"));
        eRet = E_CAPTURE_RET_FAIL;
        goto MApp_MPlayer_CaptureAudioTask_END;
    }

    //Step 1. Check USB connection
    if(((stAudioCaptureSetting.u8ConnectPort==0)&&(MApp_MassStorage_DeviceConnectionDetect()&MS_USB_CONNECTED))
        ||((stAudioCaptureSetting.u8ConnectPort==1)&&(MApp_MassStorage_DeviceConnectionDetect()&MS_USB2_CONNECTED))
      )
    {
    }
    else
    {
        CAPTURE_ERR(printf("[Audio Capture Error] USB device (%d) is unplugged\n",stAudioCaptureSetting.u8ConnectPort));
        eRet = E_CAPTURE_RET_USB_FAIL;
        goto MApp_MPlayer_CaptureAudioTask_END;
    }

    U32 u32CurrentPCMOffset = 0;
    U32 u32ResidualPCMSize = 0;
    U32 u32RemainBytes = 0;
    U8 u8Header[CAPTURE_AUDIO_WAV_HEADER_LEN];
    U32 u32Timer;
    U32 u32USBFreeSpace = msAPI_FCtrl_GetUnusedSizeInKB_ByDriveIndex_New(stAudioCaptureSetting.u8ConnectDrive);

    //Step 2. Check Drive free space
    CAPTURE_DBG(printf("[Audio Capture] Current USB Free Space: %d KB\n",u32USBFreeSpace));
    if(CAPTURE_USB_FREESPACE_THRESHOLD > u32USBFreeSpace)
    {
        CAPTURE_ERR(printf("[Audio Capture Error] This file disk has remain %d KB. It is less than the free space threshold (%d KB).\n",u32USBFreeSpace,CAPTURE_USB_FREESPACE_THRESHOLD));
        eRet = E_CAPTURE_RET_DISK_FULL;
        goto MApp_MPlayer_CaptureAudioTask_END;
    }

    //Step 3. Update PCM Address from DSP
    MApp_MPlayer_CaptureAudioRead();

    u32CurrentPCMOffset = m_AudioCapture.u32CurPCMOffset;
    if(u32CurrentPCMOffset <= CAPTURE_AUDIO_BUFFER_LEN)
    {
        CAPTURE_DBG(printf("[Audio Capture] PCM Address: Pre=0x%x Cur=0x%x\n",m_AudioCapture.u32PrePCMOffset,u32CurrentPCMOffset));
    }
    else
    {
        CAPTURE_ERR(printf("[Audio Capture] PCM address (0x%x) from DSP is wrong while capturing.\n",u32CurrentPCMOffset));
        MApp_MPlayer_CaptureAudioStop();
        return E_CAPTURE_RET_FAIL;
    }

    //Step 4. Update PCM Address from DSP
    if(u32CurrentPCMOffset < m_AudioCapture.u32PrePCMOffset)
    {
        u32ResidualPCMSize = CAPTURE_AUDIO_BUFFER_LEN - m_AudioCapture.u32PrePCMOffset + u32CurrentPCMOffset;
    }
    else
    {
        u32ResidualPCMSize = u32CurrentPCMOffset - m_AudioCapture.u32PrePCMOffset;
    }

    CAPTURE_DBG(printf("[Audio Capture] Residual PCM Size=0x%x\n",u32ResidualPCMSize));

    //Step 5. Compute what size should be written
    if(u32ResidualPCMSize >= CAPTURE_AUDIO_READ_LEN)
    {
        U8 u8Factor = u32ResidualPCMSize/CAPTURE_AUDIO_READ_LEN;
        U32 u32DesiredReadBytes = CAPTURE_AUDIO_READ_LEN;

        if(u8Factor > CAPTURE_AUDIO_MAX_READ_FACTOR)
        {
            u32DesiredReadBytes = CAPTURE_AUDIO_READ_LEN*CAPTURE_AUDIO_MAX_READ_FACTOR;
        }
        else
        {
            u32DesiredReadBytes = CAPTURE_AUDIO_READ_LEN*u8Factor;
        }

        CAPTURE_DBG(printf("[Audio Capture] Current Read Size=0x%x (0x%x*%d)\n",u32DesiredReadBytes,CAPTURE_AUDIO_READ_LEN,u8Factor));

        //Step 6. Write data to USB
        if((m_AudioCapture.u32PrePCMOffset+u32DesiredReadBytes) > CAPTURE_AUDIO_BUFFER_LEN)
        {
            u32Timer = msAPI_Timer_GetTime0();
            u32RemainBytes = msAPI_FCtrl_FileWrite(m_AudioCapture.u8WriteFileHandle, CAPTURE_AUDIO_BUFFER_ADR+m_AudioCapture.u32PrePCMOffset, (CAPTURE_AUDIO_BUFFER_LEN-m_AudioCapture.u32PrePCMOffset));
            CAPTURE_PFM(printf("\033[15;31m[Audio Capture Peformace] Write size: 0x%x. Cost time : %d\n\033[0m",(CAPTURE_AUDIO_BUFFER_LEN-m_AudioCapture.u32PrePCMOffset),msAPI_Timer_DiffTimeFromNow(u32Timer)));
            u32DesiredReadBytes -= (CAPTURE_AUDIO_BUFFER_LEN-m_AudioCapture.u32PrePCMOffset);
            m_AudioCapture.u32DataChunkSize += (CAPTURE_AUDIO_BUFFER_LEN-m_AudioCapture.u32PrePCMOffset);
            //PCM Offset should return to the head of the buffer
            m_AudioCapture.u32PrePCMOffset = 0;
        }

        u32Timer = msAPI_Timer_GetTime0();
        u32RemainBytes += msAPI_FCtrl_FileWrite(m_AudioCapture.u8WriteFileHandle, CAPTURE_AUDIO_BUFFER_ADR+m_AudioCapture.u32PrePCMOffset, u32DesiredReadBytes);
        CAPTURE_PFM(printf("\033[15;31m[Audio Capture Peformace] Write size: 0x%x. Cost time : %d\n\033[0m",u32DesiredReadBytes,msAPI_Timer_DiffTimeFromNow(u32Timer)));
        m_AudioCapture.u32PrePCMOffset += u32DesiredReadBytes;
        m_AudioCapture.u32DataChunkSize += u32DesiredReadBytes;

        //Step 7. Update WAV header
        if(_Mapp_MPlayer_WAVHeaderGenerator(u8Header, sizeof(u8Header), &m_AudioCapture))
        {
            MsOS_Dcache_Flush((U32)u8Header, sizeof(u8Header));
            MsOS_FlushMemory();
            u32Timer = msAPI_Timer_GetTime0();
            msAPI_FCtrl_FileSeek(m_AudioCapture.u8WriteFileHandle, 0 , FILE_SEEK_SET);
            msAPI_FCtrl_FileWrite(m_AudioCapture.u8WriteFileHandle, _VA2PA((U32)&u8Header), CAPTURE_AUDIO_WAV_HEADER_LEN);
            msAPI_FCtrl_FileSeek(m_AudioCapture.u8WriteFileHandle, m_AudioCapture.u32DataChunkSize + CAPTURE_AUDIO_WAV_HEADER_LEN, FILE_SEEK_SET);
            CAPTURE_PFM(printf("\033[15;31m[Audio Capture Peformace] Header Update Write. Cost time : %d\n\033[0m",msAPI_Timer_DiffTimeFromNow(u32Timer)));
        }
        else
        {
            CAPTURE_ERR(printf("[Audio Capture Error] Wrong WAV Header while capturing\n"));
            eRet = E_CAPTURE_RET_FAIL;
            goto MApp_MPlayer_CaptureAudioTask_END;
        }
    }
    else
    {
        CAPTURE_DBG(printf("[Audio Capture] Not capture this time, wait more PCM packet\n"));
    }

    //Step 5. Write fail cases
    if(u32RemainBytes > 0)
    {
        if(((stAudioCaptureSetting.u8ConnectPort==0)&&(MApp_MassStorage_DeviceConnectionDetect()&MS_USB_CONNECTED))
            ||((stAudioCaptureSetting.u8ConnectPort==1)&&(MApp_MassStorage_DeviceConnectionDetect()&MS_USB2_CONNECTED))
          )
        {
            CAPTURE_ERR(printf("[Audio Capture Error] This file disk is full, and write file error. Current record file size: %d\n",msAPI_FCtrl_FileLength(m_AudioCapture.u8WriteFileHandle)));
            if(msAPI_FCtrl_FileLength(m_AudioCapture.u8WriteFileHandle) == 0)
            {
                FileEntry stBackupDstFileEntry;
                memset(&stBackupDstFileEntry, 0, sizeof(FileEntry));
                if(msAPI_FCtrl_EntryGetByHandle(m_AudioCapture.u8WriteFileHandle, &stBackupDstFileEntry))
                {
                    CAPTURE_ERR(printf("[Audeo Capture] This file size is 0, and delete this file\n"));
                    msAPI_FCtrl_FileDelete(&stBackupDstFileEntry);
                }
            }
            eRet = E_CAPTURE_RET_DISK_FULL;
            goto MApp_MPlayer_CaptureAudioTask_END;
        }
        else
        {
            CAPTURE_ERR(printf("[Audio Capture Error] Write file error. There is no USB connected\n"));
            eRet = E_CAPTURE_RET_USB_FAIL;
            goto MApp_MPlayer_CaptureAudioTask_END;
        }
    }

    eRet = E_CAPTURE_RET_OK;

MApp_MPlayer_CaptureAudioTask_END:

    if(eRet != E_CAPTURE_RET_OK)
    {
        MApp_MPlayer_CaptureAudioStop();
    }

    return eRet;

}

//******************************************************************************
/// Read capturing audio buffer
/// @param  N/A
/// @return enumCaptureRet
//******************************************************************************
enumCaptureRet MApp_MPlayer_CaptureAudioRead(void)
{
    U32 u32ResidualPCMSize = 0;

    u32ResidualPCMSize = MApi_AUDIO_PCMCapture_GetBufferLevel(E_DEVICE0);

    if((m_AudioCapture.u32CurPCMOffset+u32ResidualPCMSize) > CAPTURE_AUDIO_BUFFER_LEN)
    {
        if (MApi_AUDIO_PCMCapture_Read(E_DEVICE0, (void*)_PA2VA(CAPTURE_AUDIO_BUFFER_ADR+m_AudioCapture.u32CurPCMOffset), (CAPTURE_AUDIO_BUFFER_LEN-m_AudioCapture.u32CurPCMOffset)))
        {
            u32ResidualPCMSize -= (CAPTURE_AUDIO_BUFFER_LEN-m_AudioCapture.u32CurPCMOffset);
            //PCM Offset should return to the head of the buffer
            m_AudioCapture.u32CurPCMOffset = 0;
        }
    }

    if (MApi_AUDIO_PCMCapture_Read(E_DEVICE0, (void*)_PA2VA(CAPTURE_AUDIO_BUFFER_ADR+m_AudioCapture.u32CurPCMOffset), u32ResidualPCMSize))
    {
        m_AudioCapture.u32CurPCMOffset += u32ResidualPCMSize;
    }

    return E_CAPTURE_RET_OK;
}

//******************************************************************************
/// Stop capturing the audio
/// @param  N/A
/// @return enumCaptureRet
//******************************************************************************
enumCaptureRet MApp_MPlayer_CaptureAudioStop(void)
{
    if(MApp_MPlayer_IsCapturingAudio())
    {
        CAPTURE_ERR(printf("[Audio Capture] Stop Audio Capture\n"));
        MApi_AUDIO_PCMCapture_Stop(E_DEVICE0);
        msAPI_FCtrl_FileClose(m_AudioCapture.u8WriteFileHandle);
        m_AudioCapture.u8WriteFileHandle = INVALID_FILE_HANDLE;
    }
    return E_CAPTURE_RET_OK;
}

//******************************************************************************
/// Check if the audio capturing is on-going.
/// @param  N/A
/// @return BOOLEAN
//******************************************************************************
BOOLEAN MApp_MPlayer_IsCapturingAudio(void)
{
    if(m_AudioCapture.u8WriteFileHandle != INVALID_FILE_HANDLE)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

//******************************************************************************
/// Get AudioCaptureInfo from Audo Capture vaiables
/// @param  pAudioCaptureInfo  \b OUT Specify AudioCaptureInfo
/// @return TRUE/FALSE.
//******************************************************************************
BOOLEAN MApp_MPlayer_GetAudioCaptureInfo(ST_AUDIO_CAPTURE_GET_INFO* pAudioCaptureInfo)
{
    if(pAudioCaptureInfo == NULL)
    {
        return FALSE;
    }

    U32 u32ByteRate = 0;

    //Duration
    u32ByteRate = m_AudioCapture.u32SampleRate * m_AudioCapture.u16Channels * m_AudioCapture.u16BitsPerSample/8;
    pAudioCaptureInfo->u32Duration = m_AudioCapture.u32DataChunkSize/u32ByteRate;

    return TRUE;
}

//******************************************************************************
/// Generate the file header for captured audio WAV file.
/// @param  pu8Header       \b IN Specify the file header.
/// @param  u32HeaderLength \b IN Specify the length of file header.
/// @param  stAudioCaptureInfo \b IN Specify the parameters of header.
/// @return BOOLEAN
//******************************************************************************
static BOOLEAN _Mapp_MPlayer_WAVHeaderGenerator(U8 *pu8Header, U32 u32HeaderLength, MPlayerAudioCapture* pstAudioCaptureInfo)
{
    U8 u8Header[CAPTURE_AUDIO_WAV_HEADER_LEN] ={
        'R','I','F','F',      //ChunkID: RIFF
        0,0,0,0,              //*Chunk Size: to be filled
        'W','A','V','E',      //Format: WAVE
        'f','m','t',' ',      //SubChunk1 ID: fmt
        0x10,0,0,0,           //SubChunk1 Size: 16
        1,0,                  //Audio Format: PCM=1
        0,0,                  //*Num channel: to be filled
        0,0,0,0,              //*Sample Rate: to be filled
        0,0,0,0,              //*Byte Rate: SampleRate * Channels * BitsPerSample/8
        0,0,                  //*Block Align: Channels * BitsPerSample/8
        0,0,                  //*Bits per Sample: to be filled
        'd','a','t','a',      //SubChunk2 ID: data
        0,0,0,0               //*SubChunk2 Size: to be filled
    };

    U32 u32FileSize = 0;
    U32 u32ByteRate = 0;
    U16 u16BlockAlign = 0;

    if(pu8Header==NULL)
    {
        return FALSE;
    }
    if(u32HeaderLength < CAPTURE_AUDIO_WAV_HEADER_LEN)
    {
        return FALSE;
    }
    //Chunk Size, not include header
    u32FileSize =  pstAudioCaptureInfo->u32DataChunkSize + CAPTURE_AUDIO_WAV_HEADER_LEN - 8;
    memcpy(&u8Header[4],&u32FileSize,4);

    //Num channel
    memcpy(&u8Header[22], &pstAudioCaptureInfo->u16Channels,2);

    //Sample rate
    memcpy(&u8Header[24], &pstAudioCaptureInfo->u32SampleRate,4);

    //Byte Rate: SampleRate * Channels * BitsPerSample/8
    u32ByteRate = pstAudioCaptureInfo->u32SampleRate * pstAudioCaptureInfo->u16Channels * pstAudioCaptureInfo->u16BitsPerSample/8;
    memcpy(&u8Header[28], &u32ByteRate,4);

    //Block Align
    u16BlockAlign = pstAudioCaptureInfo->u16Channels * pstAudioCaptureInfo->u16BitsPerSample/8;
    memcpy(&u8Header[32], &u16BlockAlign,2);

    //Bits per Sample
    memcpy(&u8Header[34],&pstAudioCaptureInfo->u16BitsPerSample,2);

    //SubChunk2 Size: data file size
    memcpy(&u8Header[40], &pstAudioCaptureInfo->u32DataChunkSize,4);

    //copy u8Header to *pu8Header
    memcpy(pu8Header,&u8Header,CAPTURE_AUDIO_WAV_HEADER_LEN);

    CAPTURE_DBG(printf("[Audio Capture] Header Duration=%d\n",pstAudioCaptureInfo->u32DataChunkSize/u32ByteRate));

    return TRUE;
}

//******************************************************************************
/// Set ST_AUDIO_CAPTURE_SET_INFO to m_AudioCaptureSetting
/// @param  pAudioCaptureSetInfo  \b IN Specify ST_AUDIO_CAPTURE_SET_INFO
/// @return TRUE/FALSE.
//******************************************************************************
static BOOLEAN _MApp_MPlayer_SetAudioCaptureSetting(ST_AUDIO_CAPTURE_SET_INFO* pAudioCaptureSetInfo)
{
    BOOLEAN ret = FALSE;

    if (pAudioCaptureSetInfo != NULL)
    {
        if(pAudioCaptureSetInfo->pfnRenameFileIfFileExisted == NULL)
        {
            pAudioCaptureSetInfo->pfnRenameFileIfFileExisted = &_MApp_MPlayer_RenameFileIfFileExisted;
        }

        memcpy(&m_AudioCaptureSetting, pAudioCaptureSetInfo, sizeof(ST_AUDIO_CAPTURE_SET_INFO));
        ret = TRUE;
    }

    return ret;
}

//******************************************************************************
/// Get ST_AUDIO_CAPTURE_SET_INFO from m_AudioCaptureSetting
/// @param  pAudioCaptureSetInfo  \b IN Specify ST_AUDIO_CAPTURE_SET_INFO
/// @return TRUE/FALSE.
//******************************************************************************
static BOOLEAN _MApp_MPlayer_GetAudioCaptureSetting(ST_AUDIO_CAPTURE_SET_INFO* pAudioCaptureSetInfo)
{
    if (pAudioCaptureSetInfo == NULL)
    {
        return FALSE;
    }

    memcpy(pAudioCaptureSetInfo, &m_AudioCaptureSetting, sizeof(ST_AUDIO_CAPTURE_SET_INFO));

    return TRUE;
}
#endif

#if (ENABLE_MPLAYER_VIDEO_CAPTURE || ENABLE_MPLAYER_AUDIO_CAPTURE)
//******************************************************************************
/// Connect and check the target drive.
/// @param  u8ConnectDrive \b IN Specify the target drive.
/// @return enumCaptureRet
//******************************************************************************
static enumCaptureRet _MApp_MPlayer_CaptureCheckDrive(U8 u8ConnectDrive)
{
    U32 u32USBFreeSpace;
    MSDCtrl_Drive stDrive;
    memset(&stDrive, 0, sizeof(MSDCtrl_Drive));

    if(u8ConnectDrive == INVALID_DRIVE_INDEX)
    {
        CAPTURE_ERR(printf("[Video Capture Error] Get connect drive error\n"));
        return E_CAPTURE_RET_USB_FAIL;
    }

    if(!msAPI_FCtrl_IsDriveMounted(u8ConnectDrive))
    {
        if (MApp_MassStorage_DeviceChangeStatusCheck())
        {
            MApp_MassStorage_DeviceStatusCheck();
            MApp_MPlayer_InitializeAllDevices();
        }
    }
    CAPTURE_DBG(printf("[Video Capture][Time:%d] USB port update done\n", msAPI_Timer_GetTime0()));

    msAPI_FCtrl_GetDriveByIndex(u8ConnectDrive, &stDrive);
    if(stDrive.FileSystemType !=  FILE_SYSTEM_TYPE_FAT)
    {
        CAPTURE_ERR(printf("[Video Capture Error] The file system format of this USB is not FAT\n"));
        return E_CAPTURE_RET_UNSUPPORT_FILESYSTEM;
    }

    u32USBFreeSpace = msAPI_FCtrl_GetUnusedSizeInKB_ByDriveIndex_New(u8ConnectDrive);
    CAPTURE_DBG(printf("[Video Capture Begin] Free Space: %d KB (Threshold : %d KB)\n", u32USBFreeSpace, CAPTURE_USB_FREESPACE_THRESHOLD));
    if(CAPTURE_USB_FREESPACE_THRESHOLD > u32USBFreeSpace)
    {
        CAPTURE_ERR(printf("[Video Capture Error] This file disk has remain %d KB. It is less than the free space threshold (%d KB).\n",u32USBFreeSpace,CAPTURE_USB_FREESPACE_THRESHOLD));
        return E_CAPTURE_RET_DISK_FULL;
    }

    return E_CAPTURE_RET_OK;
}

//******************************************************************************
/// Change to a specific directory
/// @param  pu8DstPathBuf \b IN Specify the path
/// @param  pu16DstPathLen \b IN Specify the path length in string
/// @return BOOLEAN
//******************************************************************************
BOOLEAN _MApp_MPlayer_ChangeToSpecificDirectory(U16 *pu16DstPath, U16 pu16DstPathLen)
{
    BOOLEAN bRet = FALSE;
    U16 i, u16DirNameLen;
    U16* pu16TempDstPath;
    U16 pu16FolderName[128]={0};

    FileEntry stDirEntry;
    memset(&stDirEntry, 0, sizeof(FileEntry));

    if(MApp_FileBrowser_ChangeToRootDirectory() == FALSE)
    {
        printf("Change to Root fail\n");
        goto MApp_MPlayer_ChangeToSpecificDirectory_END;
    }

    i=0;
    u16DirNameLen=0;

    if(pu16DstPath[0] == '\\')
    {
        if(pu16DstPath[1] == '\0')
        {
            //root
        }
        else
        {
            i=1;
            pu16TempDstPath = &pu16DstPath[i];
            while(i < pu16DstPathLen)
            {
                if(pu16DstPath[i] == '\\' || pu16DstPath[i] == '\0')
                {
                    if(u16DirNameLen != 0)
                    {
                        memcpy(pu16FolderName, pu16TempDstPath, u16DirNameLen*2);
                        pu16FolderName[u16DirNameLen] = '\0';

                        //open new folder and enter
                        if(FALSE == MApp_FileBrowser_OpenNewFolder_And_GetFileEntry(pu16FolderName,u16DirNameLen, &stDirEntry))
                        {
                            printf("ERROR MApp_FileBrowser_OpenNewFolder_And_GetFileEntry Fail 1\n");
                            goto MApp_MPlayer_ChangeToSpecificDirectory_END;
                        }

                        if(FALSE == MApp_FileBrowser_DirectoryChange(&stDirEntry))
                        {
                            printf("ERROR MApp_FileBrowser_DirectoryChange Fail 1\n");
                            goto MApp_MPlayer_ChangeToSpecificDirectory_END;
                        }

                        if(pu16DstPath[i] == '\0')
                        {
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }

                    i++;
                    u16DirNameLen=0;
                    pu16TempDstPath = &pu16DstPath[i];
                }
                else
                {
                    i++;
                    u16DirNameLen++;
                }
            }
        }
    }

    bRet = TRUE;
MApp_MPlayer_ChangeToSpecificDirectory_END:

    return bRet;
}

//******************************************************************************
/// Rename the file if the file is already existed in current directory.
/// @param  pu16FileName \b IN Specify the file name.
/// @param  u16MaxNameBufferLen \b IN Specify the max file length.
/// @return TRUE/FALSE.
//******************************************************************************
static BOOLEAN _MApp_MPlayer_RenameFileIfFileExisted(U16 *pu16SrcFileName, U16 u16MaxNameBufferLen)
{
    #define MAX_EXTNAME_SIZE_IN_LONGFILENAME_CASE 4
    #define RENAME_FILENAME_SUFFIX_LEN 4

    U16 u16SrcFileNameLen = FS_strlen_U(pu16SrcFileName);
    S16 s16Cnt = u16SrcFileNameLen;
    BOOLEAN bFindDot = FALSE;
    U16 u16OrgDotPosition = 0;
    U16 u16NewDotPosition = 0;
    U16 u16NewFileNameLen = 0;
    U16 au16ExtFileName[MAX_EXTNAME_SIZE_IN_LONGFILENAME_CASE]={0};
    U8 u8ExtFileNameLen = 0;

    if(pu16SrcFileName == NULL)
    {
        return FALSE;
    }

    if(u16SrcFileNameLen + RENAME_FILENAME_SUFFIX_LEN > u16MaxNameBufferLen)
    {
        printf("Error. Dst Buffer size is not enough!\n");
        return FALSE;
    }

    //Try to find last dot.
    for(;s16Cnt >= 0; s16Cnt--)
    {
        if(pu16SrcFileName[s16Cnt]==0x2E)//'.'
        {
            u16OrgDotPosition = s16Cnt;
            bFindDot = TRUE;
            break;
        }
    }

    if(bFindDot == TRUE)
    {
        s16Cnt++;
        while((s16Cnt < u16SrcFileNameLen) && (u8ExtFileNameLen < MAX_EXTNAME_SIZE_IN_LONGFILENAME_CASE))
        {
            au16ExtFileName[u8ExtFileNameLen] = pu16SrcFileName[s16Cnt];
            u8ExtFileNameLen++;
            s16Cnt++;
        }
    }
    else
    {
        return FALSE;
    }

    if(MApp_MPlayer_IsFilenameExistInCurrentDirectory(pu16SrcFileName, u16SrcFileNameLen))
    {

        u16NewDotPosition = u16OrgDotPosition + RENAME_FILENAME_SUFFIX_LEN; //original dot position + _xxx

        u16NewFileNameLen = u16SrcFileNameLen + RENAME_FILENAME_SUFFIX_LEN;

        U16 u16CaptureIdx = 0;

        memset(&pu16SrcFileName[u16OrgDotPosition], 0, sizeof(U16)*RENAME_FILENAME_SUFFIX_LEN);
        //fill dot
        pu16SrcFileName[u16NewDotPosition] = '.';
        memcpy(&pu16SrcFileName[u16NewDotPosition+1],&au16ExtFileName[0],(u8ExtFileNameLen)*sizeof(U16));


        //fill /0
        pu16SrcFileName[u16NewFileNameLen] = '\0';

        do
        {
            if(u16CaptureIdx == 1000)
            { // maximum captured number
                //sprintf(u8Digit, "_%02d", u16CaptureIdx);
                return FALSE;
            }

            //fill _xxx
            pu16SrcFileName[u16NewDotPosition-4] = '_';
            pu16SrcFileName[u16NewDotPosition-3] = 0x30+((u16CaptureIdx/100)%10);
            pu16SrcFileName[u16NewDotPosition-2] = 0x30+((u16CaptureIdx/10)%10);
            pu16SrcFileName[u16NewDotPosition-1] = 0x30+(u16CaptureIdx%10);
            u16CaptureIdx++;
        }
        while(MApp_MPlayer_IsFilenameExistInCurrentDirectory(pu16SrcFileName, u16NewFileNameLen));
    }
    else
    {
        printf("No file name is updated\n");
    }

    U8 i;
    printf("File name -> ");
    for(i = 0; i<= u16NewFileNameLen; i++)
    {
        printf("%c", pu16SrcFileName[i]);
    }
    printf("\n");

    return TRUE;
}
#endif

#endif // #if (ENABLE_DMP)

#undef MAPP_MPLAYER_C
