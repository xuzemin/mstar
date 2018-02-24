////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MSAPI_MHEG5_H_
#define _MSAPI_MHEG5_H_

#include "datatype.h"
#include "MApp_GlobalVar.h"
#include "MApp_ATVProc.h"
#include "mapp_iframe.h"
#include "msAPI_Video.h"
#include "msAPI_Memory.h"
#include "drvISR.h"
#include "drvCPU.h"
#include "apiGOP.h"
#include "sysinfo.h"


#undef INTERFACE

#ifdef _MSAPI_MHEG5_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif

#if ENABLE_CI_PLUS
#define HD_MHEG5                    1
#define CIPLUS_MHEG_1_3         	1
#else
#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)
#define HD_MHEG5                    1
#else
#define HD_MHEG5                    0
#endif
#define CIPLUS_MHEG_1_3         	0
#endif
#define CIPLUS_MHEG                 1   // this flag will enable MHEG in CI+ card
#define INTERACTION_CHANNEL         0   //this flag will wnable HDMHEG5 - Interaction Channel
#define INTERACTION_CHANNEL_STREAM  0   //this flag will wnable HDMHEG5 - Interaction Channel Streaming
#define CIMHEG_DBG                  0
#define MHEG5_NETWORK               0   // enable mheg with net or not
#define MHEG5_NDT                   0   // enable NonDestructiveTune in D-Book6
#define MHEG5_NDT_UNINTERRUPT_AV    0   // when NDT tunes (EnableChannel/DisableChannel), need to keep the AV uninterrupted
#define MHEG5_WITH_SUBTITLE         0

#if ENABLE_CI_PLUS
#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) \
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)\
   )//for Milan only have GOP0+GOP1
#define MHEG5_GOP                   E_GOP_APP
#else
#define MHEG5_GOP                   E_GOP_CAP
#endif
#else
#define MHEG5_GOP                   E_GOP_APP
#endif

#define MHEG5_STATIC_FB             0
#if (MEMORY_MAP==MMAP_64MB) //For A7P internal DDR2 64MB, set MIU1
#define MHEG5_GOP_MIU               1   // GOP in MIU 1
#else
#define MHEG5_GOP_MIU               0   // GOP in MIU 0

#endif
#ifdef GOP_GWIN_RB2_ADR // Move the GOP od APP from MIU0 to MIU1
#undef MHEG5_STATIC_FB
#define MHEG5_STATIC_FB             1
    #if (GOP_GWIN_RB2_MEMORY_TYPE & MIU1)
    #undef MHEG5_GOP_MIU
    #define MHEG5_GOP_MIU           1   // GOP in MIU 1
    #endif
#else
#define MHEG5_STATIC_FB             0
#endif

#if MHEG5_STATIC_FB
// TODO: change the "MHEG5_STATIC_FB_START" and make sure it does not used by someone else
#define MHEG5_STATIC_FB_OFFSET      MHEG_XRES*MHEG_YRES*2   // x-res*y-res*argb4444

#ifdef GOP_GWIN_RB2_ADR
    #if (MHEG5_GOP_MIU == 1)
    #define MHEG5_STATIC_FB_START   (GOP_GWIN_RB2_ADR | MIU_INTERVAL)
    #else
    #define MHEG5_STATIC_FB_START   GOP_GWIN_RB2_ADR
    #endif
#else
    #define MHEG5_STATIC_FB_START   MHEG5_FRAMEBUFFER_ADR//PVR_TRICK_MODE_ADR
#endif

#define MHEG5_STATIC_RT_FB_ADDR     MHEG5_STATIC_FB_START
#define MHEG5_STATIC_OS_FB_ADDR     MHEG5_STATIC_FB_START+MHEG5_STATIC_FB_OFFSET
#define MHEG5_STATIC_DLA_FB_ADDR    MHEG5_STATIC_FB_START+MHEG5_STATIC_FB_OFFSET*2
#endif

#if MHEG5_ENABLE
#define DEBUG_SYS_INFO_REPORT   0
#define MHEG5_GE_AFD_SAME_SIZE  0
#define MHEG5_BINFILE_COMPRESS  0
#else
#define DEBUG_SYS_INFO_REPORT   0
#define MHEG5_BINFILE_COMPRESS  0
#endif

#if MHEG5_ENABLE

#define MHEG5_WITH_OSD          1


#if HD_MHEG5
#define MHEG_XRES               1280
#define MHEG_YRES               720
#else
#define MHEG_XRES               720
#define MHEG_YRES               576
#endif

#if HD_MHEG5
#define MHEG_XRES_OS        1280    //  1024
#define MHEG_YRES_OS        720
#else
#define MHEG_XRES_OS        720
#define MHEG_YRES_OS        576
#endif


#define MMGAP                      4

#define MHEG_XRES_COORD         720
#define MHEG_YRES_COORD         576

#if HD_MHEG5
#define MHEG_XRES_RANGE         1280
#define MHEG_YRES_RANGE         720
#else
#define MHEG_XRES_RANGE         720
#define MHEG_YRES_RANGE         576
#endif
// MHEG5 Settings
#define MHEG_ARGB4444   0
#define MHEG_ARGB8888   1
#define MHEG_GE_FORMAT  MHEG_ARGB4444

#if MHEG_GE_FORMAT==MHEG_ARGB4444
    #define MHEG5_RenderTarget_Fmt  E_GOP_COLOR_ARGB4444
    #define MHEG_GE_FMT GFX_FMT_ARGB4444
#elif MHEG_GE_FORMAT==MHEG_ARGB8888
    #define MHEG5_RenderTarget_Fmt  E_GOP_COLOR_ARGB8888
    #define MHEG_GE_FMT GFX_FMT_ARGB8888
    #error  "MHEG ARGB8888 format not ready"
#else
    #error  "error MHEG GE format -- only support ARGB4444 or higher"
#endif


//------------------------------------------------------------------------------
// MHEG5 On Screen Stretch Method
//------------------------------------------------------------------------------
#define MHEG5_USE_GE_STRETCH            0x00
#define MHEG5_USE_GOP_STRETCH           0x01

// Horizontal
#if (MHEG5_WITH_OSD == 1)
#define MHEG5_X_STRETCH_WAY             MHEG5_USE_GOP_STRETCH //MHEG5_USE_GE_STRETCH //MHEG5_USE_GOP_STRETCH

// Vertical Stretch (Only S4 Support GOP Stretch)
#define MHEG5_Y_STRETCH_WAY             MHEG5_USE_GOP_STRETCH

#define GOP_SCALERATIO_FIXED 0

#define GOP_SCALERATIO_FIXED2 1

#else
#define MHEG5_X_STRETCH_WAY             MHEG5_USE_GE_STRETCH //MHEG5_USE_GE_STRETCH //MHEG5_USE_GOP_STRETCH
#define GOP_SCALERATIO_FIXED 0
#define MHEG5_Y_STRETCH_WAY             MHEG5_USE_GE_STRETCH
#endif

#define MB_MHEG5_EXIT_SELECTED              2

//------------------------------------------------------------------------------
#define MB_VIDEO_SET_VIDEO_DISPLAY                          0x80
#define MB_VIDEO_SET_STREAM                                 0x81
#define MB_VIDEO_SET_BOX_SIZE                               0x82
#define MB_VIDEO_SET_POSITION                               0x83
#define MB_VIDEO_SET_VIDEO_OFFSET                           0x84
#define MB_VIDEO_SET_VIDEO_SCALE                            0x85
#define MB_VIDEO_DEACTIVATION                               0x86
#define MB_VIDEO_CHANNELCHANGE                              0x87
#define MB_VIDEO_SET_STREAM_LCN                             0x88
#define MB_VIDEO_CHANNELCHANGE_LCN                          0x89
#define MB_VIDEO_ACTIVATION                                 0x8A
#define MB_VIDEO_RENDER                                     0x8B
#define MB_VIDEO_CHANNELCHANGE_QUIETLY                      0x8C
#define MB_VIDEO_CHANNELCHANGE_LCN_QUIETLY                  0x8D
#define MB_VIDEO_SET_STREAM_WITH_PID                        0x8E
#define MB_VIDEO_SET_SWA                                    0x8F
#define MB_VIDEO_SET_ARC                                    0x90
#define MB_VIDEO_SET_SCENE_AR                               0x91
#define MB_VIDEO_CHANNELCHANGE_QUIETLY_PLUS_CHKTSID         0x92
#define MB_VIDEO_CHANNELCHANGE_PLUS_CHKTSID                 0x93
#define MB_VIDEO_NDT_CHANNELCHANGE                          0x94    //  NonDestructiveTune
#define MB_VIDEO_NDT_CHANNELCHANGE_PLUS_CHKTSID             0x95    //  NonDestructiveTune
#define MB_VIDEO_NDT_CHANNELCHANGE_LCN                      0x96    //  NonDestructiveTune
#define MB_VIDEO_NDT_CHANNELCHANGE_QUIETLY                  0x97    //  NonDestructiveTune
#define MB_VIDEO_NDT_CHANNELCHANGE_PLUS_CHKTSID_QUIETLY     0x98    //  NonDestructiveTune
#define MB_VIDEO_NDT_CHANNELCHANGE_LCN_QUIETLY              0x99    //  NonDestructiveTune
#if MHEG5_WITH_SUBTITLE
#define MB_VIDEO_SUBTITLE_CONTROL                           0x9A
#endif
#if INTERACTION_CHANNEL
#define MB_IC_CHECK_INIT                                    0x9A
#endif


#define MB_SERVICE_CHECK_IF_EXIST       0x80
#define MB_SERVICE_EXIST                0x81
#define MB_SERVICE_NOT_EXIST            0x82
#define MB_SERVICE_GET_SERVICE_INDEX    0x90
#define MB_SERVICE_SI_GET_SERVICE_INFO  0x92
#define MB_SERVICE_SI_GET_EVENT_INFO    0x93
#define MB_SERVICE_SI_GET_SERVICE_INFO_OK  0x94
#define MB_SERVICE_SI_GET_SERVICE_INFO_FAIL  0x95
#define MB_SERVICE_SI_GET_EVENT_INFO_OK 0x96
#define MB_SERVICE_SI_GET_EVENT_INFO_FAIL 0x97

#define SET_VIDEO_BOX_SIZE_FLAG         0x01
#define SET_VIDEO_POSITION_FLAG         0x02
#define SET_VIDEO_OFFSET_FLAG           0x04
#define SET_VIDEO_SCALE_FLAG            0x08
#define SAME_VIDEO_SCALE                0x10
#define EVER_SET_VIDEO_BOX_SIZE         0x20
#define EVER_SET_VIDEO_STREAM           0x40

#define SCENE_Normal                      0x01
#define SCENE_16_9_TO_DIS_4_3             0x02
#define SCENE_4_3_TO_DIS_16_9             0x04
#define SCENE_CCO                         0x08 //Centre-Cut-Out
#define SCENE_LB                          0x10 //Letter-BOX

#define VIDEO_ALL_SET_FLAG  (SET_VIDEO_BOX_SIZE_FLAG | SET_VIDEO_POSITION_FLAG | SET_VIDEO_OFFSET_FLAG | SET_VIDEO_SCALE_FLAG)

#define SEND_VIDEO_BOX_SIZE_FLAG        0x01
#define SEND_VIDEO_POSITION_FLAG        0x02
#define SEND_VIDEO_OFFSET_FLAG          0x04
#define SEND_VIDEO_SCALE_FLAG           0x08
#define SEND_VIDEO_WSA_Centre_Cut_Out   0x10
#define SEND_VIDEO_WSA_Letterbox        0x20
#define SEND_SCENE_INFO_CHANGE          0x40
#define SEND_VIDEO_WSA_NORMAL           0xC0
#define STILL_HAS_BOX_SIZE_CMD          0x10
#define STILL_HAS_POSITION_CMD          0x20
#define STILL_HAS_OFFSET_CMD            0x40
#define STILL_HAS_SCALE_CMD             0x80

#define SETARC_FULL_SCREEN_GE           0x10
#define SETARC                          0x20
#define SETARC_ADJ_H                    0x40
#define SETARC_ADJ_V                    0x80

#define SENDARC_MHEG5_INIT              0x01
#define SENDARC_ARC_CHANGE              0x02
#define SENDARC_AFD_FOR_GE              0x04
#define SENDARC_AFD                     0x08
#define SENDARC_AFD_FOR_GE_MHEG5_INIT   0x10
#define SENDARC_SCENE_RATIO_CHANGE      0x20
#define SENDARC_AFD_TRANS               0x40
#define SENDARC_AFD_TRANS_FULLSCREEN    0x80

#define SCENE_AR_None                   EN_MHEG5_SceneAspectRatio_None // 0
#define SCENE_AR_16_9                   EN_MHEG5_SceneAspectRatio_16X9 // 1
#define SCENE_AR_4_3                    EN_MHEG5_SceneAspectRatio_4X3  // 2

typedef enum
{
    UNKNOW_SCALING_FACTOR = 0,
    SCALING_FULL,
    SCALING_2X,
    SCALING_QUARTER
} MB_VIDEO_SCALING;

typedef enum
{
    MB_VIDEO_CMD_PLAY,
    MB_VIDEO_CMD_PAUSE,
    MB_VIDEO_CMD_STOP
} MB_VIDEO_CMD;

typedef enum
{
    MSAPI_AUD_AEON_CMD_51_DECCMD_STOP,
    MSAPI_AUD_AEON_CMD_51_DECCMD_PLAY,
    MSAPI_AUD_AEON_CMD_51_DECCMD_RESYNC,
    MSAPI_AUD_AEON_CMD_51_DECCMD_PLAYFILE,
    MSAPI_AUD_AEON_CMD_51_DECCMD_PLAYFILE_PARAM,
    MSAPI_AUD_AEON_CMD_51_DECCMD_PAUSE,
    MSAPI_AUD_AEON_CMD_51_DECCMD_CONTINUE,
    MSAPI_AUD_AEON_CMD_51_SETVOLUME,
    MSAPI_AUD_AEON_CMD_51_SET_PID,
    MSAPI_AUD_AEON_CMD_51_DECCMD_STOP_FILEPLAY
} En_AEON251_MailBoxType;

typedef struct MHEG5AudioFileParams
{
    U32 u32MHEGAudioAddr;
    U32 u32MHEGAudioLoopCounts;
    U32 u32MHEGAudioLength;
    U8  u8MHEGAudioIsInfinite;
    U32 u32MHEGAudioFileIndex;
    U8  u8MHEG5AudioBeDecoded;
} MHEG5AudioFileParams;

typedef enum
{
    AUD_MAILBOX_CLASS_COMMON = 0,
    AUD_MAILBOX_CLASS_MHEG5
} AUDIO_MAILBOX_CLASS;


typedef enum
{
    MB_SERVICE_CMD_SERVICE_ID,
    MB_SERVICE_CMD_LCN,
    MB_SERVICE_CMD_SERVICE_ID_PLUS_CHECKTSID
}MB_SERVICE_CMD;

//====================== MHEG5 Video Infomation ===================
typedef enum
{
    EN_MHEG5_SceneAspectRatio_Min,
    EN_MHEG5_SceneAspectRatio_None = EN_MHEG5_SceneAspectRatio_Min,
    EN_MHEG5_SceneAspectRatio_16X9,
    EN_MHEG5_SceneAspectRatio_4X3,
    EN_MHEG5_SceneAspectRatio_Num
} EN_MHEG5_SCENE_ASPECT_RATIO;

typedef enum
{
    EN_MHEG5_WAM_Min,
    EN_MHEG5_WAM_None=EN_MHEG5_WAM_Min,
    EN_MHEG5_WAM_Centre_Cut_Out,
    EN_MHEG5_WAM_LetterBox,
    EN_MHEG5_WAM_Num
} EN_MHEG5_WAM;


typedef struct
{
    U16 u16H_CapStart;          ///< Programmable ARC Capture window H start
    U16 u16V_CapStart;          ///< Programmable ARC Capture window V start
    U16 u16H_CapSize;           ///< Programmable ARC Capture window H Size
    U16 u16V_CapSize;           ///< Programmable ARC Capture window V Size

    U16 u16H_DisStart;          ///< Programmable ARC Display window H Start
    U16 u16H_DisSize;           ///< Programmable ARC Display window H Size
    U16 u16V_DisStart;          ///< Programmable ARC Display window V Start
    U16 u16V_DisSize;           ///< Programmable ARC Display window V Size

}MS_ARC_PROG_WIN, *PMS_ARC_PROG_WIN;

typedef struct
{
    U16 u16BoxSize_X;
    U16 u16BoxSize_Y;
    U16 u16Scale_Width;
    U16 u16Scale_Height;

    S16 s16Position_X;
    S16 s16Position_Y;
    S16 s16VideoOffset_X;
    S16 s16VideoOffset_Y;
}MS_MHEG5_VIDEO_ACTION;

typedef struct
{
    U16 u16DstSize_X;
    U16 u16DstSize_Y;
    U16 u16SrcSize_X;
    U16 u16SrcSize_Y;
    U16 u16DstPosition_X;
    U16 u16DstPosition_Y;
    U16 u16SrcPosition_X;
    U16 u16SrcPosition_Y;
}MS_MHEG5_VIDEO_CLIPWIN;

typedef struct
{
    BOOLEAN bFullScreen;
    BOOLEAN bPrevFullScreen;
    BOOLEAN bIFrame;
    BOOLEAN bHaveVideo;
    BOOLEAN bARCChange;
    BOOLEAN bARCAdj_V;
    BOOLEAN bARCAdj_H;
    BOOLEAN bVideoActionNotRdy;
	BOOLEAN bRecodeMVDDONE;
    U8  u8VideoFlag;
    U8  u8PrevVideoFlag;
    U8  u8VideoFlag2;
    U8  u8ARC_Control;
    U8  active_status;
    U8  KEEP_STATUS;
    U8  PrevKEEP_STATUS;
    U8  u8VCapStartPatchOffset;
    MS_MHEG5_VIDEO_ACTION stMHEG5VideoAction;
    MS_MHEG5_VIDEO_ACTION stMHEG5IFrameAction;
    MS_MHEG5_VIDEO_ACTION stPrevMHEG5VideoAction;
    MS_MHEG5_VIDEO_CLIPWIN stMHEG5VideoClipWin;
    MS_MHEG5_VIDEO_CLIPWIN stPrevMHEG5VideoClipWin;
    MS_ARC_PROG_WIN stARCWin;
    MS_ARC_PROG_WIN stAFDWin;
    EN_MHEG5_WAM                eWAM;
    EN_MHEG5_WAM                Pre_eWAM;
    EN_MHEG5_SCENE_ASPECT_RATIO eSceneAspectRatio;
    EN_MHEG5_SCENE_ASPECT_RATIO eSceneAspectRatio_FromTransitionTo;
    EN_MHEG5_SCENE_ASPECT_RATIO Pre_eSceneAspectRatio;
}MS_MHEG5_VIDEO_INFO_TYPE, *PMS_MHEG5_VIDEO_INFO_TYPE;

INTERFACE MS_MHEG5_VIDEO_INFO_TYPE g_MHEG5Video;


typedef struct MHEG5CalInfo
{
    U16 u16DstSize_X;
    U16 u16DstSize_Y;
    U16 u16SrcSize_X;
    U16 u16SrcSize_Y;
    U16 u16DstPosition_X;
    U16 u16DstPosition_Y;
    U16 u16SrcPosition_X;
    U16 u16SrcPosition_Y;
    BOOLEAN KEEP_STATUS;
} MHEG5VideoCalInfo;


typedef struct MHEG5VideoStatus
{
    U8  u8VideoFlag;
    U8  u8VideoFlag2;
    U16 u16BoxSize_X;
    U16 u16BoxSize_Y;
    U16 u16Scale_Width;
    U16 u16Scale_Height;
    U16 u16Position_X;
    U16 u16Position_Y;
    U16 u16VideoOffset_X;
    U16 u16VideoOffset_Y;
    S16 s16Position_X;
    S16 s16Position_Y;
    S16 s16VideoOffset_X;
    S16 s16VideoOffset_Y;

    bool bFullScreen;
    U8 u8VCapStartPatchOffset;
    BOOLEAN active_status;

} MHEG5VideoStatus;

//-------------------------------
// MB_CLASS_SYSTEM
//-------------------------------
typedef enum
{
    MB_SYS_CMD_QUERY_STATUS,
    MB_SYS_CMD_SYS_TIMER,
    MB_SYS_CMD_SYS_NETWORK,
} M5_MB_SYSTEM_CLASS;

//-----------------------------------------------
// Class :: MPEG
//-----------------------------------------------
typedef enum
{
    MB_MPEG_IFRAME_DECODE            = 0x80,
    MB_MPEG_IFRAME_ENABLE            = 0x81,
    MB_MPEG_IFRAME_SET_POSITION      = 0x82,
    MB_MPEG_IFRAME_SCALE             = 0x83,
    MB_MPEG_IFRAME_SET_POSITION_CROP = 0x84,
    MB_MPEG_IFRAME_SCALE_CROP        = 0x85,
    MB_MPEG_IFRAME_SET_VIDOFFSET     = 0x86,
    MB_MPEG_IFRAME_BOXSIZE           = 0x87
} M5_MB_MPEG;

//-------------------------------
// MB_CLASS_TSP
//-------------------------------
typedef enum
{
    MB_TSP_CMD_ADD_PID,
    MB_TSP_CMD_DEL_PID,
    MB_TSP_CMD_EXIT_MHEG,
    MB_TSP_CMD_NDT_PID
} M5_MB_TSP_CLASS;

//-------------------------------
// MB_CLASS_VIDEO
//-------------------------------
typedef enum
{
    MB_VID_CMD_CHANGESTREAM     = 0,
    MB_VID_CMD_SETAFD           = 1,
    MB_VID_CMD_SETARC_PART1     = 2,
    MB_VID_CMD_SETARC_PART2     = 3,
    MB_VID_CMD_SETVTG           = 4,
    MB_VID_CMD_SETVTG2          = 5,
    MB_VID_CMD_SETVTG_SETTING   = 6,
    MB_VID_CMD_SETVTG_EVENT     = 7,
} MB_VIDEO_CMD_INDEX;


//-------------------------------
// MB_CLASS_AUTOTEST
//-------------------------------

typedef enum
{
    MB_AUTOTEST_ENABLE = 0,
} MB_AUTOTEST_CLASS;
//-------------------------------
// MB_CLASS_MHEG5_STATE
//-------------------------------
typedef enum
{
    //HK => CP
    MB_MHEG5_STATE_CMD_AUD_PID_PNL_RATIO    = 0x00,
    MB_MHEG5_STATE_CMD_OS_FB                = 0x01,
    MB_MHEG5_STATE_CMD_SETARC_PART1         = 0x02,
    MB_MHEG5_STATE_CMD_SETARC_PART2         = 0x03,

    MB_MHEG5_STATE_CMD_PNL_INFO             = 0x05,
    MB_MHEG5_STATE_CMD_SEMAPHORE            = 0x06,
    MB_MHEG5_STATE_CMD_OS_BAK_COLOR         = 0x07,
    MB_MHEG5_STATE_CMD_RT_FB                = 0x08,
    MB_MHEG5_STATE_CMD_DLA_FB               = 0x09,
    MB_MHEG5_STATE_CMD_IFRAME_CONTROL       = 0x0A,
    MB_MHEG5_STATE_CMD_SETARC_SETTING       = 0x0B,

#ifdef MHEG5_BIG5_FONT_ENABLE
    MB_MHEG5_STATE_CMD_M5FONTSIZE           = 0x0C,
#endif
    MB_MHEG5_STATE_CMD_MMAP                 = 0x0E,
    MB_MHEG5_STATE_CMD_HKMB_READY           = 0x0F,
    MB_MHEG5_STATE_CMD_UPDATE_CUR_AUDIO     = 0x10,


    //CP => HK
    MB_MHEG5_STATE_CMD_EXIT                 = 0x80,
    MB_MHEG5_STATE_CMD_AUTOBOOT             = 0x81,
    MB_MHEG5_STATE_CMD_CHANNEL_CHANGE       = 0x82,
    MB_MHEG5_STATE_CMD_MHEG5_TO_MENU        = 0x83,
    MB_MHEG5_STATE_CMD_RESOURCE_CHANGE      = 0x84,
    MB_MHEG5_STATE_CMD_KEY_REGISTER         = 0x85,
    MB_MHEG5_STATE_CMD_NO_MHEG5             = 0x86,
    MB_MHEG5_STATE_DRAW_EVENT               = 0x87,
    MB_MHEG5_STATE_DSMCC_EXIT               = 0x88,

    MB_MHEG5_STATE_CMD_MMAP_OK              = 0x8E,
    MB_MHEG5_STATE_CMD_CPMB_READY           = 0x8F,
} MB_MHEG5_STATE_CLASS;

/// Mail box return state
typedef enum
{
    M5_MB_RETURN_OK,
    MB_RETURN_MHEG5_EXIT,                                               ///< Mail box return EXIT
    MB_RETURN_MHEG5_AUTOBOOT,                                               ///< Mail box return AUTOBOOT
    MB_RETURN_MHEG5_CHANNELCHANGE,                                               ///< Mail box return Channelchange
    MB_RETURN_MHEG5_SELECTED_QUIT_SEL,                                               ///< Mail box return quit by "select key"
    MB_RETURN_MHEG5_SELECTED_QUIT_0,                                               ///< Mail box return quit by selected state "0 key"
    MB_RETURN_MHEG5_SELECTED_QUIT_1,                                               ///< Mail box return quit by selected state "1 key"
    MB_RETURN_MHEG5_SELECTED_QUIT_2,                                               ///< Mail box return quit by selected state "2 key"
    MB_RETURN_MHEG5_SELECTED_QUIT_3,                                               ///< Mail box return quit by selected state "3 key"
    MB_RETURN_MHEG5_SELECTED_QUIT_4,                                               ///< Mail box return quit by selected state "4 key"
    MB_RETURN_MHEG5_SELECTED_QUIT_5,                                               ///< Mail box return quit by selected state "5 key"
    MB_RETURN_MHEG5_SELECTED_QUIT_6,                                               ///< Mail box return quit by selected state "6 key"
    MB_RETURN_MHEG5_SELECTED_QUIT_7,                                               ///< Mail box return quit by selected state "7 key"
    MB_RETURN_MHEG5_SELECTED_QUIT_8,                                               ///< Mail box return quit by selected state "8 key"
    MB_RETURN_MHEG5_SELECTED_QUIT_9,                                               ///< Mail box return quit by selected state "9 key"
    MB_RETURN_51_STATE_CHANNEL_CHANGE,                                               ///< Mail box return 51 state channel change
    MB_RETURN_51_STATE_MHEG5_TO_MENU,                                               ///< Mail box return 51 state MHEG5 to Menu
    MB_RETURN_NO_MHEG5_DATA

} M5_MB_RETURN_STATE;


//====callback function type define==============
typedef void (* CALLBACK) (BOOLEAN);

typedef struct MHEG5EventHandle
{
    CALLBACK DrawingCallback;

} MHEG5EventHandle;

extern U8   u8MHEG5_DLA_FBID;


#if ENABLE_AUTOTEST
INTERFACE void msAPI_MHEG5_AUTOTEST_Enable(BOOLEAN bAutoTest);
#endif

// prototype
#if MHEG5_NDT
INTERFACE void msAPI_MHEG5_WaitNDTPid(BOOLEAN bSetNDT);
INTERFACE BOOLEAN msAPI_MHEG5_BeWaitingNDTPid(void);
INTERFACE void msAPI_MHEG5_TriggerNDT(void);
void msAPI_MHEG5_SetNDTChannelChange(BOOLEAN bChannelChange);
BOOLEAN msAPI_MHEG5_GetNDTChannelChange(void);
#endif

INTERFACE U8      msAPI_MHEG5_GetKeyRegisterGroup(void);
INTERFACE void    msAPI_MHEG5_SetKeyRegisterGroup(U8 u8RegisterGroup);
INTERFACE void    msAPI_MHEG5_SetRun(BOOLEAN bEnable);
INTERFACE BOOLEAN msAPI_MHEG5_IsRunning(void);
INTERFACE BOOLEAN msAPI_MHEG5_IsIFrameExist(void);
INTERFACE BOOLEAN msAPI_MHEG5_IsMHEGDraw(void);
#if INTERACTION_CHANNEL
INTERFACE void msAPI_MHEG5_SendICStatus(U16 u8Status);
INTERFACE void msAPI_MHEG5_SendICAddr(U32 u32ICAddr);
#endif
//AUDIO
INTERFACE void  msAPI_MHEG_AUD_PlayMHEG5AudioFile(void);
INTERFACE U32   msAPI_MHEG_AUD_ReadMailBox(BYTE paramNum);
INTERFACE void  msAPI_MHEG_AUD_IntMAD(WORD cmd);
INTERFACE void  msAPI_MHEG_AUD_WriteMailBox(BYTE paramNum, WORD data1);
INTERFACE void  msAPI_MHEG_AUD_SetMADIntFlag(BOOLEAN bSet);
INTERFACE U8    msAPI_MHEG_AUD_GetMADIntFlag(void);
INTERFACE void  msAPI_MHEG_AUD_ClearMADIntFlag(void);
INTERFACE void  msAPI_MHEG_AUD_ProcessMailbox(U8 *u8AeonMailBox);
INTERFACE void  msAPI_MHEG_AUD_ChangeAudPid(S32 s32AudioPID, WORD wAudType);
INTERFACE void  msAPI_MHEG_AUD_Stop(void);
INTERFACE AU_DVB_DECCMD msAPI_MHEG_AUD_GetMadCmd(void);

//VIDEO
INTERFACE void      msAPI_MHEG5_VID_Send_CHANGESTREAM(void);
INTERFACE void      msAPI_MHEG5_VID_SendUserArcEvent(void);
INTERFACE void      msAPI_MHEG5_VID_SendARCInfo( U8 u8Flag , U8 u8UIARC );
INTERFACE void      msAPI_MHEG5_VID_SetCapDisWin( void );
INTERFACE void      msAPI_MHEG5_VID_CalculateClipWin( MS_MHEG5_VIDEO_ACTION *pstVideoAction, MS_MHEG5_VIDEO_CLIPWIN *pstClipWin );
INTERFACE void      msAPI_MHEG5_VID_GetMaxMinPosition( INPUT_SOURCE_TYPE_t enInputSourceType, MVOP_Timing *ptiming, EN_ASPECT_RATIO_TYPE enVideoScreen, S16 *s16VMax, S16 *s16VMin, S16 *s16HMax, S16 *s16HMin);
INTERFACE BOOLEAN   msAPI_MHEG5_VID_IsFullScreen( MS_MHEG5_VIDEO_ACTION *pstMHEG5VideoAction );
INTERFACE BOOLEAN   msAPI_MHEG5_VID_AFD_Status(void);
INTERFACE BOOLEAN   msAPI_MHEG5_VID_IsSameVideoAction( MS_MHEG5_VIDEO_ACTION *pstMHEG5VideoAction, MS_MHEG5_VIDEO_ACTION *pstPrevMHEG5VideoAction);
INTERFACE BOOLEAN   msAPI_MHEG5_VID_SetWindowInfo(XC_SETWIN_INFO *pstXC_SetWin_Info,SCALER_WIN eScalerWindow);

INTERFACE BOOLEAN           M5API_VID_Switch2Codec(VDEC_CodecType eVDEC_CodecType, BOOLEAN bIframe);
INTERFACE void              M5API_VID_Command(U8 u8VIDcommand);

INTERFACE void  msAPI_MHEG5_Key_Transmit(U8 u8Key, U8 Status);
INTERFACE void  msAPI_MHEG5_QuitOSD(void);
INTERFACE void  msAPI_MHEG5_ChangeOSBackgroundColor(U32 u32Color);
INTERFACE void  msAPI_MHEG5_SendPanelInfo(void);
INTERFACE void  msAPI_MHEG5_SendOSWidthHeight_AudioPid_PanelRatio(U32 u32Width, U32 u32Height, U16 u16AudioPid, U16 u16VideoPid);
INTERFACE void msAPI_MHEG5_SendCurrentAudioPidType(U16 u16AudioPid);
INTERFACE void  msAPI_MHEG5_SendFBGWinOSAddr(U32 u32FBAddr, U32 u32DRAMRBlkStart);
INTERFACE void  msAPI_MHEG5_SendDLAInfo(U32 fbAddr);
INTERFACE void  msAPI_MHEG5_Send_ARC_Setting(BOOLEAN OnlyRefresh,BOOLEAN bGEDisplayfollowARC,BOOLEAN u8IFrameContorl,BOOLEAN bNeedGetDrawingEventByReg,BOOLEAN bNeedGetDrawingEventByMail);

INTERFACE U8    msAPI_MHEG5_CreateFrameBuffer(GFX_Buffer_Format gefmt, GOP_GwinFBAttr *fbAttr, U16 width, U16 height, U32 *fbAddr, U8 *fbId);

INTERFACE void  msAPI_MHEG5_UseGeSemaphore(void);
INTERFACE void  msAPI_MHEG5_TriggerDsmcc(U16 u16PmtPid);
INTERFACE void  msAPI_MHEG5_StopDsmcc(BOOLEAN bWait);


INTERFACE U32   msAPI_MHEG5_GetDLAFBAddress(void);
INTERFACE void  msAPI_MHEG5_UpdateDLAFBAddress(U32 u32DLABufferAddress_update);
INTERFACE void  msAPI_MHEG5_DestroyDLAFB(void);
INTERFACE U32   msAPI_MHEG5_AllocateDLAFB(void);



INTERFACE U8   msAPI_MHEG5_GetGraphInfoRefreshType(void);
INTERFACE void msAPI_MHEG5_SetGraphInfoRefreshType(U8 type);

INTERFACE BOOLEAN msAPI_MHEG5_CalcSceneAspectRatio(MS_WINDOW_TYPE *pstDstWin);

INTERFACE BOOLEAN   msAPI_MHEG5_GetBinStatus(void);
INTERFACE void      msAPI_MHEG5_SetBinStatus(BOOLEAN status);

INTERFACE void msAPI_MHEG5_SetDrawingCallback(CALLBACK callback);

INTERFACE void msAPI_MHEG5_Bean_Init(void);



INTERFACE BOOLEAN msAPI_MHEG5_ServiceValidChecking(MB_SERVICE_CMD eCmdType, U16 u16InputValue, U16 u16InputValue2, U16 u16InputValue3, U16 *u16OutputValue, U16 *u16OutputValue2, U16 *u16OutputValue3, U8 *u8IsValid);
INTERFACE void msAPI_MHEG5_SendChannelInfo(U8 bResult ,U16 u16ServiceID,U16 u16OnID,U16 u16TsID,U8 u8IsValid);

INTERFACE void msAPI_MHEG5_SetBaseYear(U16 u16BaseYear);
INTERFACE void msAPI_MHEG5_SystemTime_Transmit(U32 u32SystemTime, S32 s32OffsetTime);

INTERFACE BOOLEAN msAPI_MHEG5_checkGoBackMHEG5(void);
INTERFACE void msAPI_MHEG5_SetGoBackMHEG5(BOOLEAN bGoBack);

#if MHEG5_WITH_SUBTITLE
INTERFACE U8 msAPI_MHEG5_GetSubtitleMode(void);
INTERFACE void msAPI_MHEG5_SetSubtitleMode(U8 subtitleControl);
#endif

#if CIPLUS_MHEG_1_3
INTERFACE U8 msAPI_MHEG5_GoMHEGWhenSubtitleOn(void);
INTERFACE void msAPI_MHEG5_SetCIPLUSSSM(U8 ssm);
INTERFACE void msAPI_MHEG5_SetCIPLUSSMG(BOOL smg);
#endif


#if MHEG5_NETWORK
INTERFACE void msAPI_MHEG5_InitNetwork(void);
#endif

#ifdef MHEG5_BIG5_FONT_ENABLE
INTERFACE void msAPI_MHEG5_LoadBig5Font(void);
INTERFACE void msAPI_MHEG5_SendM5FontInfo(void);
#endif

#if CIPLUS_MHEG
typedef enum
{
    MB_CI_CMD_MHEGCI_INITOBJ=0,                   // HK->MHEG
    MB_CI_CMD_MHEGCI_FILEREADY=1,                 // HK->MHEG
    MB_CI_CMD_MHEGCI_FILEREQUEST=2,               // MHEG->HK
    MB_CI_CMD_MHEGCI_SENDMESSAGE=3,               // MHEG->HK
    MB_CI_CMD_MHEGCI_SENDEXITMESSAGE=4,           // MHEG->HK
    MB_CI_CMD_MHEGCI_ABORT=5,                     // HK->MHEG
    MB_CI_CMD_MHEGCI_FILE_EXISTENCE_CHECK=6,      // MHEG->HK
    MB_CI_CMD_MHEGCI_FILE_EXISTENCE_RESPONSE=7,   //  HK->MHEG
    MB_CI_CMD_MHEGCI_FILE_NG=8,                   //  HK->MHEG
    MB_CI_CMD_MHEGCI_SMG=9,                         //  MHEG->HK
    MB_CI_CMD_MHEGCI_EXIT_CIMHEG5_STATE        =   0xFF,      //  housekeepng->mheg
} MB_CI_CLASS;

typedef enum
{
    E_MHEG_CI_OFF,
    E_MHEG_CI_TRIGGER,
    E_MHEG_CI_RUNNING
} E_MHEG_CI_STATUS;

#define MB_CI_CMD_MHEGCI    0

INTERFACE void msAPI_MHEG5_SendCIMHEGAbort(void);
INTERFACE void msAPI_MHEG5_SendCIMHEGRequestStart(void);
INTERFACE void msAPI_MHEG5_SendCIMHEGFileReady(void);
INTERFACE void msAPI_MHEG5_SendCIMHEGFileExistence(BOOL bExistence);
INTERFACE void msAPI_MHEG5_SendCIMHEGFileNG(void);
INTERFACE void msAPI_MHEG5_SetCIMHEGRun(E_MHEG_CI_STATUS bRun);
INTERFACE E_MHEG_CI_STATUS msAPI_IsCIMHEGRun(void);
INTERFACE void msAPI_MHEG5_AllocateCIMHEGBuffer(void);
INTERFACE void msAPI_MHEG5_CIMHEGNG(void);
INTERFACE void msAPI_MHEG5_SendCIMHEGExitWaitBootState(void);
#endif
INTERFACE void msAPI_MHEG5_RESTORE(void);

#if DEBUG_SYS_INFO_REPORT
INTERFACE void msAPI_System_StatusReport(void);
#endif

#endif
#undef INTERFACE

#endif  // _MSAPI_MHEG5_H_

