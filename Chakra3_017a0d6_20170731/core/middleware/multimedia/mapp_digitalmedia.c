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
// Copyright (c) 2006-2008 MStar Semiconductor, Inc.
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

#define _MAPP_DIGITAL_MEDIA_C_
///////////////////////////////////////////////////////////////////////////////
/// \file   mapp_digitalmedia.c
/// \brief  Digital media playing Module
/// \author MStar Semiconductor Inc.
///
/// \details This file is the function body that accomplish the playback
/// command from upper layer for playing a media instance.
///////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
// Include Files
//-------------------------------------------------------------------------------------------------
#include "MsCommon.h"
#include "MsOS.h"

#include <string.h>
#include "debug.h"

#include "mapp_digitalmedia.h"

#include "drvGlobal.h"
#include "InfoBlock.h"

#include "msAPI_Timer.h"
#include "msAPI_CPU.h"
#include "Panel.h"
#include "msAPI_MailBox.h"
#include "msAPI_DataStreamIO.h"

#include "apiXC.h"
#include "apiXC_Sys.h"

#include "msAPI_FCtrl.h"
#include "mapp_videoplayer.h"
#include "mapp_music.h"
#include "mapp_wma.h"
#include "msAPI_Memory.h"
#include "ctype.h"
#include "msAPI_BDMA.h"

#include "mapp_photo.h"
#include "mapp_photo_display.h"

#include "SW_Config.h"

//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
/// \cond
/// \brief DM_PHOTO_TOTAL_SLOT can't < 1 and if DM_PHOTO_TOTAL_SLOT == 1, no pre-decode
#define DM_PHOTO_TOTAL_SLOT (2)

/// \brief Default photo slide show time out value in secons
#define DM_PHOTO_SLIDESHOW_TIME_OUT (20)

#define LYRIC_MAX_SIZE                      76
#define DIGITALMEDIA_DBG(x)                  //x

#define PHOTO_DBG   0
/// \endcond

//-------------------------------------------------------------------------------------------------
// Type and Structure Declaration
//-------------------------------------------------------------------------------------------------
/// \cond
typedef enum
{
    E_DM_STATE_STANDBY = 0,
    E_DM_STATE_INITED,
    E_DM_STATE_PLAYING,
} E_DM_STATE;

typedef enum
{
    E_DM_PHOTO_SLOT_STATE_FREE = 0,
    E_DM_PHOTO_SLOT_STATE_DECODING,
    E_DM_PHOTO_SLOT_STATE_DECODED,
    E_DM_PHOTO_SLOT_STATE_DISPLAYING,
} E_DM_PHOTO_SLOT_STATE;

typedef enum
{
    E_DM_PHOTO_SLIDE_SHOW_FREE_RUN = 0,
    E_DM_PHOTO_SLIDE_SHOW_PAUSED,
    E_DM_PHOTO_SLIDE_SHOW_PAUSE_RELEASED,
} E_DM_PHOTO_PAUSE_STATE;

typedef enum
{
    E_DM_MUSIC_FLG_NULL = 0,
    E_DM_MUSIC_FLG_LYRIC_VALID,
    E_DM_MUSIC_FLG_LYRIC_ENABLE,
} E_DM_MUSIC_FLAG;

typedef struct
{
    E_DM_STATE eState;
    DM_STRM_HDL dmStrmHdl[E_DM_STRM_HDL_MAX];
    E_DM_STRM_ATTRIB eAttrib;
    DM_STRM_IO fnCallbacks;
    pfnNotificaton pfnNotify;

    // setting
    BOOLEAN     bFullScreen;
    ST_DM_RECT  stViewWindow;

    S16 s16ShiftX, s16ShiftY;
    E_DM_REPEAT_AB eRepeatAB;
    E_DM_PLAY_MODE ePlayMode;
    E_DM_ROTATION  eRotation;
    E_DM_SPEED  eSpeed;
    E_DM_ZOOM   eZoom;
    U32 u32PlayTime;

    E_DM_MUSIC_FLAG eMusicFlag;
    E_DM_EVENT eEventMask;

    //double buffer
    BOOLEAN bEnableDoubleBuf;
    LongLong u64StreamPos;
    DM_STRM_HDL Hdl_EnableDoubleBuf;
    BOOLEAN bNeedResetBuf;
    BOOLEAN bFileEnd;
    U32 u32DoubleBufAddr;
    U32 u32DoubleBufSize;
    U8 CurrentBufIndex;
    U32 InputBufInfo[2][3]; //InputBufInfo[][0]:Address;InputBufInfo[][1]:buf length;InputBufInfo[][2]:read offset;
} ST_DIGITAL_MEDIA;
/// \endcond

//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------
/// \details This definition is used to check the stream type in every
///  function.
#define INVALID_STRM_TYPE(eType) ((eType >= E_DM_STRM_TYPE_NUM)         \
                                    ? TRUE : FALSE)

/// \cond
/// \brief This macro is used to send event
#define SEND_EVENT_NOTIFICATION(type, event, info, len)                     \
    if ((event != E_DM_EVENT_NONE)                                          \
            && (_gstMedias[type].eEventMask & event)                        \
            && (_gstMedias[type].pfnNotify != NULL))                        \
    {                                                                       \
        _gstMedias[type].pfnNotify(type, event, info, len);                 \
    }

#define PHOTO_NEXT_SLOT(idx)    ((idx + 1) % DM_PHOTO_TOTAL_SLOT)
/// \endcond

//-------------------------------------------------------------------------------------------------
// Global Variables
//-------------------------------------------------------------------------------------------------
#if (ENABLE_DIGITAL_MEDIA_API)
static ST_DIGITAL_MEDIA _gstMedias[E_DM_STRM_TYPE_NUM];
static FN_DATA_STRM_IO _gDataStreamIOFunc;
static BOOLEAN _bPowerOnInited = FALSE;

// music specific variables
static E_DM_MUSIC_TYPE _geDM_MusicType = E_DM_MUSIC_NONE;
static EN_MUSIC_TYPE _genMusicType = EN_MUSIC_MP3;
static U32 m_u32PlayCheckTime;
static U32 m_u32LyricSubtitleCurTime;
static U16 m_u16CurLyricPos;
static BOOLEAN m_bIsLyricUnicode = FALSE;

// photo specific variables
static U8 _gu8Photo_DecodeIdx;
static U8 _gu8Photo_DisplayIdx;
static E_DM_PHOTO_SLOT_STATE _gePhoto_State[DM_PHOTO_TOTAL_SLOT];
static U16 _gu16Photo_SlideShowTimeOutInSec;
static E_DM_PHOTO_PAUSE_STATE _gePhoto_SlideShowPauseState;

static U16 _gu16Photo_Wdith[DM_PHOTO_TOTAL_SLOT];
static U16 _gu16Photo_Height[DM_PHOTO_TOTAL_SLOT];
static U32 _gu32Photo_Size[DM_PHOTO_TOTAL_SLOT];
#endif //#if (ENABLE_DIGITAL_MEDIA_API)

//-------------------------------------------------------------------------------------------------
// Local Variables
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
// Local Function Prototypes
//-------------------------------------------------------------------------------------------------
#if (ENABLE_DIGITAL_MEDIA_API)
static void _MApp_DigitalMedia_Reset(E_DM_STRM_TYPE eType);
static void _MApp_DigitalMedia_UnconditionalStop(E_DM_STRM_TYPE eType);
static void _MApp_DigitalMedia_InitCoProcessor(void);

static void _MApp_DigitalMedia_RegisterDataStreamIOCallBack(void);
static void _MApp_DigitalMedia_UnRegisterDataStreamIOCallBack(E_DM_STRM_TYPE eType);

static E_DM_STRM_TYPE   _MApp_DigitalMedia_GetStrmType(DM_STRM_HDL dmHdl);

static VDPLAYER_ZOOM_FACT   _MApp_DigitalMedia_Movie_TransformZoomFactor(E_DM_ZOOM eDmZoom);
static EN_PHOTO_ZOOMING     _MApp_DigitalMedia_Photo_TransformZoomFactor(E_DM_ZOOM eDmZoom);
static EN_PHOTO_DIRECTION   _MApp_DigitalMedia_Photo_TransformDirection(E_DM_DIRECTION eDirection);
static EN_PHOTO_ROTATION    _MApp_DigitalMedia_Photo_TransformRotation(E_DM_ROTATION eRotation);

static BOOLEAN  _MApp_DigitalMedia_Init_DoubleBuf(E_DM_STRM_TYPE eType, U32 u32BufAddr, U32 u32BufSize,DM_STRM_HDL Hdl_EnableDoubleBuf);
static void     _MApp_DigitalMedia_Reset_DoubleBuf(E_DM_STRM_TYPE eType);
static U32      _MApp_DigitalMedia_Read_DoubleBuf(E_DM_STRM_TYPE eType, U8* pdata, U32 u32length);

static BOOLEAN  _MApp_DigitalMedia_Music_Lyric_Parser(void);
static void     _MApp_DigitalMedia_GetLyric(U16 u16LyricPos, U8 *pu8Dst);

static E_DM_MUSIC_TYPE _MApp_DigitalMedia_VerifyMusicType(FileEntry *pEntry,E_DM_MUSIC_TYPE enMusicType);

#endif //#if (ENABLE_DIGITAL_MEDIA_API)

//-------------------------------------------------------------------------------------------------
// Function Prototypes
//-------------------------------------------------------------------------------------------------
#if (ENABLE_DIGITAL_MEDIA_API)
U32         MApp_DigitalMedia_DataStream_Open(void *pPrivate, U8 u8Mode, E_DATA_STREAM_TYPE eType);
BOOLEAN     MApp_DigitalMedia_DataStream_Close(U32 u32Hdl);
U32         MApp_DigitalMedia_DataStream_Read(U32 u32Hdl, void *pBuffAddr, U32 u32Length);
BOOLEAN     MApp_DigitalMedia_DataStream_Seek(U32 u32Hdl, LongLong u64Pos, E_DATA_STREAM_SEEK_OPTION eOption);
LongLong    MApp_DigitalMedia_DataStream_Tell(U32 u32Hdl);
LongLong    MApp_DigitalMedia_DataStream_Length(U32 u32Hdl);

BOOLEAN     MApp_DigitalMedia_MovieStopInit(EN_VDPLAYER_FORCE_STOP eType);

void    MApp_DigitalMedia_DrawExternalSubtitle(BOOLEAN bShowSubtitile, U32 u32TextDataAddress, U16 u16Len);
#endif //#if (ENABLE_DIGITAL_MEDIA_API)

//-------------------------------------------------------------------------------------------------
// extern Function
//-------------------------------------------------------------------------------------------------
extern U16 MApp_Transfer2Unicode(U16 u16Code);

//-------------------------------------------------------------------------------------------------
// Function Implementation -- interfaces for out world
//-------------------------------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Main task of digital media module.

    \param None

    \return None */
///////////////////////////////////////////////////////////////////////////////
void MApp_DigitalMedia_Task(void)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    return;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    EN_RET eRet;
    BOOLEAN bStop = FALSE;

#if PHOTO_DBG
    static U32 u32PhotoDisplayStartTime = 0;
    static U32 u32PhotoDisplayTick = 0;
#endif

    // if not inited, do nothing
    if (_bPowerOnInited == FALSE)
    {
        return;
    }

    // movie playing
    if (_gstMedias[E_DM_STRM_TYPE_MOVIE].eState == E_DM_STATE_PLAYING)
    {
        eRet = MApp_VDPlayer_Main();
        if (eRet == EXIT_VDPLAYER_WAIT)
        {
            // stop normally
            bStop = TRUE;
            SEND_EVENT_NOTIFICATION(E_DM_STRM_TYPE_MOVIE, E_DM_EVENT_STOP_NORMALLY, NULL, 0);
        }
        else if (eRet == EXIT_VDPLAYER_EXIT)
        {
            // stop abnormally
            bStop = TRUE;
            SEND_EVENT_NOTIFICATION(E_DM_STRM_TYPE_MOVIE, E_DM_EVENT_STOP_ABNORMALLY, NULL, 0);
        }
        else if (eRet == EXIT_VDPLAYER_DECODING)
        {
            // check play time
            U32 u32CurrentPlayTime = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CUR_TIME);

            // report time tick per second
            if ((_gstMedias[E_DM_STRM_TYPE_MOVIE].u32PlayTime / 1000) != (u32CurrentPlayTime / 1000))
            {
                // record current play time
                _gstMedias[E_DM_STRM_TYPE_MOVIE].u32PlayTime = u32CurrentPlayTime;

                // record current play time
                SEND_EVENT_NOTIFICATION(
                        E_DM_STRM_TYPE_MOVIE,
                        E_DM_EVENT_PLAYING_TIME_TICK,
                        (U32)&_gstMedias[E_DM_STRM_TYPE_MOVIE].u32PlayTime,
                        sizeof(_gstMedias[E_DM_STRM_TYPE_MOVIE].u32PlayTime));
            }
        }

        //draw external subtitle or internal text subtiltle
        MApp_MPlayer_ExternalAndInternalTextSubtitleDraw();

        // stop when necessary
        if (bStop == TRUE)
        {
            MApp_DigitalMedia_Stop(E_DM_STRM_TYPE_MOVIE);
        }
    }

    //music playing
    bStop = FALSE;
    if(_gstMedias[E_DM_STRM_TYPE_MUSIC].eState == E_DM_STATE_PLAYING)
    {
        if(_geDM_MusicType == E_DM_MUSIC_WMA)
        {
            eRet = MApp_WMA_Main();
            switch(eRet)
            {
                case EXIT_WMA_WAIT:
                    // stop normally
                    SEND_EVENT_NOTIFICATION(E_DM_STRM_TYPE_MUSIC, E_DM_EVENT_STOP_NORMALLY, NULL, 0);
                    m_u32PlayCheckTime = -1;
                    bStop = TRUE;
                    break;

                case EXIT_WMA_EXIT:
                    // stop abnormally
                    SEND_EVENT_NOTIFICATION(E_DM_STRM_TYPE_MUSIC, E_DM_EVENT_STOP_ABNORMALLY, NULL, 0);
                    m_u32PlayCheckTime = -1;
                    bStop = TRUE;
                    break;

                default:
                    if(msAPI_Timer_DiffTimeFromNow(m_u32PlayCheckTime)>100)
                    {
                        U32 u32CurTime;
                        U8 *pu8Dst;
                        Music_Lyric_Tag curLyricTag;

                        if((_gstMedias[E_DM_STRM_TYPE_MUSIC].eMusicFlag & E_DM_MUSIC_FLG_LYRIC_VALID) &&
                            (_gstMedias[E_DM_STRM_TYPE_MUSIC].eMusicFlag & E_DM_MUSIC_FLG_LYRIC_ENABLE))
                        {
                            u32CurTime = MApp_WMA_GetCurrentTimeMs();
                            if(MApp_Music_GetLyricTag(&curLyricTag, u32CurTime))
                            {
                                if(curLyricTag.u32Time != m_u32LyricSubtitleCurTime)
                                {
                                    pu8Dst = msAPI_Memory_Allocate(LYRIC_MAX_SIZE+2, BUF_ID_FILEBROWER);

                                    if(pu8Dst)
                                    {
                                        _MApp_DigitalMedia_GetLyric(curLyricTag.u16LyricPos, pu8Dst);
                                        SEND_EVENT_NOTIFICATION(E_DM_STRM_TYPE_MUSIC, E_DM_EVENT_SHOW_LYRIC, (U32)pu8Dst, LYRIC_MAX_SIZE);
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

                        if ((_gstMedias[E_DM_STRM_TYPE_MUSIC].u32PlayTime / 1000) != (u32CurTime / 1000))
                        {
                            // record current play time
                            _gstMedias[E_DM_STRM_TYPE_MUSIC].u32PlayTime = u32CurTime;

                            // record current play time
                            SEND_EVENT_NOTIFICATION(
                                    E_DM_STRM_TYPE_MUSIC,
                                    E_DM_EVENT_PLAYING_TIME_TICK,
                                    (U32)&_gstMedias[E_DM_STRM_TYPE_MUSIC].u32PlayTime,
                                    sizeof(_gstMedias[E_DM_STRM_TYPE_MUSIC].u32PlayTime));
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
                    SEND_EVENT_NOTIFICATION(E_DM_STRM_TYPE_MUSIC, E_DM_EVENT_STOP_NORMALLY, NULL, 0);
                    m_u32PlayCheckTime = -1;
                    bStop = TRUE;
                    break;

                case EXIT_MP3_EXIT:
                    // stop abnormally
                    SEND_EVENT_NOTIFICATION(E_DM_STRM_TYPE_MUSIC, E_DM_EVENT_STOP_ABNORMALLY, NULL, 0);
                    m_u32PlayCheckTime = -1;
                    bStop = TRUE;
                    break;

                default:

                    if(msAPI_Timer_DiffTimeFromNow(m_u32PlayCheckTime)>100)
                    {
                        U32 u32CurTime;
                        U8 *pu8Dst;
                        Music_Lyric_Tag curLyricTag;

                        if((_gstMedias[E_DM_STRM_TYPE_MUSIC].eMusicFlag & E_DM_MUSIC_FLG_LYRIC_VALID) &&
                            (_gstMedias[E_DM_STRM_TYPE_MUSIC].eMusicFlag & E_DM_MUSIC_FLG_LYRIC_ENABLE))
                        {
                            u32CurTime = MApp_Music_GetCurrentTimeMs();
                            if(MApp_Music_GetLyricTag(&curLyricTag, u32CurTime))
                            {
                                if(curLyricTag.u32Time != m_u32LyricSubtitleCurTime)
                                {
                                    pu8Dst = msAPI_Memory_Allocate(LYRIC_MAX_SIZE+2, BUF_ID_FILEBROWER);

                                    if(pu8Dst)
                                    {
                                        _MApp_DigitalMedia_GetLyric(curLyricTag.u16LyricPos, pu8Dst);
                                        SEND_EVENT_NOTIFICATION(E_DM_STRM_TYPE_MUSIC, E_DM_EVENT_SHOW_LYRIC, (U32)pu8Dst, LYRIC_MAX_SIZE);
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

                        if ((_gstMedias[E_DM_STRM_TYPE_MUSIC].u32PlayTime / 1000) != (u32CurTime / 1000))
                        {
                            // record current play time
                            _gstMedias[E_DM_STRM_TYPE_MUSIC].u32PlayTime = u32CurTime;

                            // record current play time
                            SEND_EVENT_NOTIFICATION(
                                    E_DM_STRM_TYPE_MUSIC,
                                    E_DM_EVENT_PLAYING_TIME_TICK,
                                    (U32)&_gstMedias[E_DM_STRM_TYPE_MUSIC].u32PlayTime,
                                    sizeof(_gstMedias[E_DM_STRM_TYPE_MUSIC].u32PlayTime));
                        }

                        m_u32PlayCheckTime = msAPI_Timer_GetTime0();
                    }
                    break;
            }
        }

        // stop when necessary
        if (bStop == TRUE)
        {
            MApp_DigitalMedia_Stop(E_DM_STRM_TYPE_MUSIC);
        }
    }

    // photo playing
    // note: photo decode process has to be in front of display process because decoded
    // photo has to be displayed immediately if that is possible or the small time periord
    // between current decode and next display of next loop may cause problem

    // photo decode process
    bStop = FALSE;
    if (_gstMedias[E_DM_STRM_TYPE_PHOTO].eState == E_DM_STATE_PLAYING)
    {
        // note: if next file is jpeg and there is photo displaying,
        // decode can start only when current displaying photo times out
        // TBD: this is JPEG pause decode
        if ((MApp_Photo_GetInfo(E_PHOTO_INFO_FILE_FORMAT) == E_PHOTO_FILE_JPEG)
                && (_gePhoto_State[_gu8Photo_DisplayIdx] == E_DM_PHOTO_SLOT_STATE_DISPLAYING))
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

#if PHOTO_DBG
                printf("DM: slot state changed for decode fail.\n");
                printf("\tdecode,  idx: %d, state: %d - > %d\n",
                        _gu8Photo_DecodeIdx, _gePhoto_State[_gu8Photo_DecodeIdx], E_DM_PHOTO_SLOT_STATE_FREE);
                printf("\tdisplay, idx: %d, state: %d\n\n",
                        _gu8Photo_DisplayIdx, _gePhoto_State[_gu8Photo_DisplayIdx]);
#endif

                // change photo state to free
                _gePhoto_State[_gu8Photo_DecodeIdx] = E_DM_PHOTO_SLOT_STATE_FREE;

                // send event
                SEND_EVENT_NOTIFICATION(E_DM_STRM_TYPE_PHOTO, E_DM_EVENT_PHOTO_DECODE_FAILED, NULL, 0);
            }
            else if (eRet == EXIT_PHOTO_DECODE_DONE)
            {
                // decode done
                bStop = TRUE;

#if PHOTO_DBG
                printf("DM: slot state changed for decode done.\n");
                printf("\tdecode,  idx: %d -> %d, state: %d - > %d\n",
                        _gu8Photo_DecodeIdx, PHOTO_NEXT_SLOT(_gu8Photo_DecodeIdx),
                        _gePhoto_State[_gu8Photo_DecodeIdx], E_DM_PHOTO_SLOT_STATE_DECODED);
                printf("\tdisplay, idx: %d, state: %d\n\n",
                        _gu8Photo_DisplayIdx, _gePhoto_State[_gu8Photo_DisplayIdx]);
#endif

                // change photo state to decoded
                _gePhoto_State[_gu8Photo_DecodeIdx] = E_DM_PHOTO_SLOT_STATE_DECODED;
                _gu8Photo_DecodeIdx = PHOTO_NEXT_SLOT(_gu8Photo_DecodeIdx);

                // send event
                SEND_EVENT_NOTIFICATION(E_DM_STRM_TYPE_PHOTO, E_DM_EVENT_PHOTO_DECODE_DONE, 0, 0);
            }
        }

        // stop when necessary
        if (bStop == TRUE)
        {
            MApp_DigitalMedia_Stop(E_DM_STRM_TYPE_PHOTO);
        }
    }

    // photo display process, 3 steps
    // 1. check slide show pause state to decide next display action
    if (_gePhoto_SlideShowPauseState == E_DM_PHOTO_SLIDE_SHOW_PAUSED)
    {
        // slide show paused, don't examine step 2 & 3
    }
    else if (_gePhoto_SlideShowPauseState == E_DM_PHOTO_SLIDE_SHOW_PAUSE_RELEASED)
    {
        _gePhoto_SlideShowPauseState = E_DM_PHOTO_SLIDE_SHOW_FREE_RUN;

        // slide show pause released, invalid current displayed photo immediately
        if (_gePhoto_State[_gu8Photo_DisplayIdx] == E_DM_PHOTO_SLOT_STATE_DISPLAYING)
        {
            if (_gePhoto_State[PHOTO_NEXT_SLOT(_gu8Photo_DisplayIdx)] == E_DM_PHOTO_SLOT_STATE_DECODING)
            {
                // if next file is still decoding, send notificatino
                SEND_EVENT_NOTIFICATION(E_DM_STRM_TYPE_PHOTO, E_DM_EVENT_PHOTO_DECODING_NEXT, NULL, 0);
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
        if (_gePhoto_State[_gu8Photo_DisplayIdx] == E_DM_PHOTO_SLOT_STATE_DISPLAYING)
        {
#if PHOTO_DBG
            if ((msAPI_Timer_GetTime0() / 1000) != (u32PhotoDisplayStartTime / 1000))
            {
                printf("DM: Photo display tick(%d)\n", u32PhotoDisplayTick++);
                u32PhotoDisplayStartTime = msAPI_Timer_GetTime0();
            }
#endif

            if (msAPI_Timer_DiffTimeFromNow(_gstMedias[E_DM_STRM_TYPE_PHOTO].u32PlayTime)
                    >= (U32)_gu16Photo_SlideShowTimeOutInSec * 1000)
            {
invalid_current_displayed_photo:
                switch (_gePhoto_State[PHOTO_NEXT_SLOT(_gu8Photo_DisplayIdx)])
                {
                    case E_DM_PHOTO_SLOT_STATE_FREE:
                    case E_DM_PHOTO_SLOT_STATE_DECODED:
#if PHOTO_DBG
                        printf("DM: slot state changed for display time out.\n");
                        printf("\tdecode,  idx: %d, state: %d\n",
                                _gu8Photo_DecodeIdx, _gePhoto_State[_gu8Photo_DecodeIdx]);
                        printf("\tdisplay, idx: %d -> %d, state: %d -> %d\n\n",
                                _gu8Photo_DisplayIdx, PHOTO_NEXT_SLOT(_gu8Photo_DisplayIdx),
                                _gePhoto_State[_gu8Photo_DisplayIdx], E_DM_PHOTO_SLOT_STATE_FREE);
#endif
                        // change photo state to free
                        _gePhoto_State[_gu8Photo_DisplayIdx] = E_DM_PHOTO_SLOT_STATE_FREE;
                        _gu8Photo_DisplayIdx = PHOTO_NEXT_SLOT(_gu8Photo_DisplayIdx);
                        break;

                    case E_DM_PHOTO_SLOT_STATE_DECODING:
                        // TBD: this is JPEG pause decode
                        if (MApp_Photo_GetInfo(E_PHOTO_INFO_FILE_FORMAT) == E_PHOTO_FILE_JPEG)
                        {
#if PHOTO_DBG
                            printf("DM: slot state changed for display time out & next is jpeg.\n");
                            printf("\tdecode,  idx: %d, state: %d\n",
                                    _gu8Photo_DecodeIdx, _gePhoto_State[_gu8Photo_DecodeIdx]);
                            printf("\tdisplay, idx: %d -> %d, state: %d -> %d\n\n",
                                    _gu8Photo_DisplayIdx, PHOTO_NEXT_SLOT(_gu8Photo_DisplayIdx),
                                    _gePhoto_State[_gu8Photo_DisplayIdx], E_DM_PHOTO_SLOT_STATE_FREE);
#endif
                            // change photo state to free
                            _gePhoto_State[_gu8Photo_DisplayIdx] = E_DM_PHOTO_SLOT_STATE_FREE;
                            _gu8Photo_DisplayIdx = PHOTO_NEXT_SLOT(_gu8Photo_DisplayIdx);
                        }
                        break;

                    default:
                        break;

                }
            }
        }

        // 3. if no photo is displayed and one is ready, display it
        if (_gePhoto_State[_gu8Photo_DisplayIdx] == E_DM_PHOTO_SLOT_STATE_DECODED)
        {
            // reset photo relative variables
            _gstMedias[E_DM_STRM_TYPE_PHOTO].s16ShiftX = 0;
            _gstMedias[E_DM_STRM_TYPE_PHOTO].s16ShiftY = 0;
            _gstMedias[E_DM_STRM_TYPE_PHOTO].eZoom = E_DM_ZOOM_1;
            _gstMedias[E_DM_STRM_TYPE_PHOTO].eRotation = E_DM_ROTATION_0;

            // change photo state to displaying
            _gePhoto_State[_gu8Photo_DisplayIdx] = E_DM_PHOTO_SLOT_STATE_DISPLAYING;

            // display photo
            MApp_Photo_Display(!_gstMedias[E_DM_STRM_TYPE_PHOTO].bFullScreen);

            // record start time of current photo displaying
            _gstMedias[E_DM_STRM_TYPE_PHOTO].u32PlayTime = msAPI_Timer_GetTime0();

#if PHOTO_DBG
            printf("DM: slot state changed for displaying.\n");
            printf("\tdecode,  idx: %d, state: %d\n",
                    _gu8Photo_DecodeIdx, _gePhoto_State[_gu8Photo_DecodeIdx]);
            printf("\tdisplay, idx: %d, state: %d -> %d\n\n",
                    _gu8Photo_DisplayIdx, E_DM_PHOTO_SLOT_STATE_DECODED, E_DM_PHOTO_SLOT_STATE_DISPLAYING);

            u32PhotoDisplayStartTime = _gstMedias[E_DM_STRM_TYPE_PHOTO].u32PlayTime;
            u32PhotoDisplayTick = 0;
#endif

            // send event
            SEND_EVENT_NOTIFICATION(E_DM_STRM_TYPE_PHOTO, E_DM_EVENT_PHOTO_DISPLAYED, NULL, 0);
        }
    }
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: This function is the fundamental initialization
    procedure that should be called before any of other functions provided by
    digital media module be called. The result is unpredictable if the procedure
    isn't followed

    \param None

    \return None */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_ModuleInit(void)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));
    return FALSE;

#else
    U32 u32Idx;

    _MApp_DigitalMedia_InitCoProcessor();

    E_DM_STRM_TYPE eTypeIdx;

    for (eTypeIdx = E_DM_STRM_TYPE_MIN; eTypeIdx < E_DM_STRM_TYPE_NUM; eTypeIdx++)
    {
        E_DM_STRM_HDL eHdlIdx;

        _gstMedias[eTypeIdx].eState     = E_DM_STATE_STANDBY;
        _gstMedias[eTypeIdx].eAttrib    = E_DM_STRM_ATTR_NONE;
        _gstMedias[eTypeIdx].pfnNotify  = NULL;
        memset(&_gstMedias[eTypeIdx].fnCallbacks, 0, sizeof(_gstMedias[eTypeIdx].fnCallbacks));
        for (eHdlIdx = E_DM_STRM_HDL_MIN; eHdlIdx < E_DM_STRM_HDL_MAX; eHdlIdx++)
        {
            _gstMedias[eTypeIdx].dmStrmHdl[eHdlIdx] = INVALID_DM_STRM_HDL;
        }

        _gstMedias[eTypeIdx].bFullScreen            = FALSE;
        _gstMedias[eTypeIdx].stViewWindow.u16X      = DEFAULT_PREVIEW_WND_X;
        _gstMedias[eTypeIdx].stViewWindow.u16Y      = DEFAULT_PREVIEW_WND_Y;
        _gstMedias[eTypeIdx].stViewWindow.u16Width  = DEFAULT_PREVIEW_WND_WIDTH;
        _gstMedias[eTypeIdx].stViewWindow.u16Height = DEFAULT_PREVIEW_WND_HEIGHT;

        _gstMedias[eTypeIdx].s16ShiftX = 0;
        _gstMedias[eTypeIdx].s16ShiftY = 0;

        _gstMedias[eTypeIdx].eRepeatAB = E_DM_REPEAT_NONE;
        _gstMedias[eTypeIdx].ePlayMode = E_DM_PLAY_MODE_NORMAL;
        _gstMedias[eTypeIdx].eRotation = E_DM_ROTATION_0;
        _gstMedias[eTypeIdx].eSpeed = E_DM_SPEED_X1;
        _gstMedias[eTypeIdx].eZoom = E_DM_ZOOM_1;
        _gstMedias[eTypeIdx].u32PlayTime = 0;

        _gstMedias[eTypeIdx].eMusicFlag = E_DM_MUSIC_FLG_NULL;
    }

    // reset music specific vairables
    _geDM_MusicType = E_DM_MUSIC_NONE;
    _genMusicType = EN_MUSIC_MP3;
    m_u32PlayCheckTime = 0;
    m_u32LyricSubtitleCurTime = 0;
    m_u16CurLyricPos = 0;
    m_bIsLyricUnicode = FALSE;

    // reset photo specific vairables
    _gu8Photo_DecodeIdx     = 0;
    _gu8Photo_DisplayIdx    = 0;

    _gu16Photo_SlideShowTimeOutInSec    = DM_PHOTO_SLIDESHOW_TIME_OUT;
    _gePhoto_SlideShowPauseState        = E_DM_PHOTO_SLIDE_SHOW_FREE_RUN;
    for (u32Idx = 0; u32Idx < DM_PHOTO_TOTAL_SLOT; u32Idx++)
    {
        _gePhoto_State[u32Idx] = E_DM_PHOTO_SLOT_STATE_FREE;

        _gu16Photo_Wdith[u32Idx]  = 0;
        _gu16Photo_Height[u32Idx] = 0;
        _gu32Photo_Size[u32Idx]   = 0;
    }

    _bPowerOnInited = TRUE;

    return TRUE;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Before digital media module can start to decode
    and render data, this function has to be called. And before returning from
    this function, digital media module.

    \param <IN>     \b pStreamHdl: An array of \e DM_STRM_HDL. The entry count
                        of this array should be \e E_DM_STRM_HDL_MAX.
    \param <IN>     \b eType: Type of media instance.
    \param <IN>     \b eAttrib: Attribute of media instance.
    \param <IN>     \b pfnCallbacks: Streaming I/O callback functions.

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise.

    \note
        Depends on the media instance type specified by \e eType, stream
        handle(s) has to be assigned to the specific entry of the array
        \e pStreamHdl. At least one of these entires is mandatory and others
        are optional. \e INVALID_DM_STRM_HDL is the value that should be
        assigned to eh un-used entries and the optional entries which has
        no data stream associating with. Here is the relationship between
        \e eType and the entry properties of \e pStreamHdl. \n
        - \e eType is  E_DM_STRM_TYPE_MOVIE
            - pStreamHdl[E_DM_STRM_HDL_VIDEO]: mandatory
            - pStreamHdl[E_DM_STRM_HDL_AUDIO]: optional
            - pStreamHdl[E_DM_STRM_HDL_IN_SUB]: optional
            - pStreamHdl[E_DM_STRM_HDL_EX_SUB_0]: optional
            - pStreamHdl[E_DM_STRM_HDL_EX_SUB_1]: optional
            - others: not used
        - \e eType is  E_DM_STRM_TYPE_PHOTO
            - pStreamHdl[E_DM_STRM_HDL_PHOTO]: mandatory
            - others: not used
        - \e eType is  E_DM_STRM_TYPE_MUSIC
            - pStreamHdl[E_DM_STRM_HDL_MUSIC]: mandatory
            - pStreamHdl[E_DM_STRM_HDL_LYRIC]: optional
            - others: not used */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_Init(DM_STRM_HDL *pStreamHdl, E_DM_STRM_TYPE eType, E_DM_STRM_ATTRIB eAttrib, DM_STRM_IO *pfnCallbacks)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(pStreamHdl);
    UNUSED(eType);
    UNUSED(eAttrib);
    UNUSED(pfnCallbacks);
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    E_DM_STRM_HDL eStrmHdl;
    BOOLEAN bRet = FALSE;

    // test if already power on inited
    if (_bPowerOnInited == FALSE)
    {
        return FALSE;
    }

    // parameter validation
    if ((pStreamHdl == NULL) || (pfnCallbacks == NULL))
    {
        return FALSE;
    }

    // type ckecking
    if (INVALID_STRM_TYPE(eType))
    {
        return FALSE;
    }

    // state checking
    // allowed when media IS NOT stopped
    if (_gstMedias[eType].eState != E_DM_STATE_STANDBY)
    {
        MApp_DigitalMedia_Stop(eType);
    }

    _MApp_DigitalMedia_Reset(eType);

    // save information
    for (eStrmHdl = E_DM_STRM_HDL_MIN; eStrmHdl < E_DM_STRM_HDL_MAX; eStrmHdl++)
    {
        _gstMedias[eType].dmStrmHdl[eStrmHdl] = pStreamHdl[eStrmHdl];
    }
    _gstMedias[eType].eAttrib = eAttrib;
    _gstMedias[eType].fnCallbacks = *pfnCallbacks;
    if (_gstMedias[eType].pfnNotify != pfnCallbacks->pfnNotify)
    {
        // exception for photo because MApp_DigitalMedia_Init() is for decoding
        // but we still need to send notify when displaying
        if ((eType == E_DM_STRM_TYPE_PHOTO) && (pfnCallbacks->pfnNotify == NULL))
        {
            // ignore the NULL callback because original callback is needed for photo slideshow
        }
        else
        {
            _gstMedias[eType].pfnNotify = pfnCallbacks->pfnNotify;
        }
    }

    // register data stream I/O callback
    _MApp_DigitalMedia_RegisterDataStreamIOCallBack();

    // send cmd to sub-module
    switch (eType)
    {
        case E_DM_STRM_TYPE_MOVIE:
            MApp_VDPlayer_SetCfg(E_VDPLAYER_CFG_BM_STREAM_MODE, _gstMedias[eType].eAttrib & E_DM_STRM_ATTR_SEEKABLE ? E_BM_STREAM_MODE_NORMAL : E_BM_STREAM_MODE_NETWORK_UNSEEKABLE);
            MApp_VDPlayer_SetCfg(E_VDPLAYER_CFG_FORCE_STOP_CALLBACK, (U32)MApp_DigitalMedia_MovieStopInit);

            MApp_MPlayer_Register_Notify(E_SUBTITLE_NOTIFY_AP_UNICODE, MApp_DigitalMedia_DrawExternalSubtitle);
            MApp_MPlayer_ExternalSubtitle_Parser(NULL, NULL);

            if(eAttrib & E_DM_STRM_ATTR_VIDEO_ONLY)
            {
                DIGITALMEDIA_DBG(printf("enable video only mode\n"));
                MApp_VDPlayer_EnableVideoOnly(TRUE);
            }
            else
            {
                //init audio
                MApi_AUDIO_SetCommand(MSAPI_AUD_DVB2_DECCMD_STOP);
                MApi_AUDIO_SetSystem(MSAPI_AUD_DVB2_NONE);
                MApi_AUDIO_SetSystem(MSAPI_AUD_DVB2_MP3);
            }

            // TODO: VIDEO_PLAYER_PLAYING_TYPE_TS of MApp_VDPlayer_Init() is only for now and it should be removed
            bRet = MApp_VDPlayer_Init(
                        VIDEO_PLAYER_INPUT_SOURCE_MM,
                        VIDEO_PLAYER_PLAYING_TYPE_TS,
                        NULL
                    );
            break;

        case E_DM_STRM_TYPE_PHOTO:
            // check if there is free slot for photo decode
            if (MApp_DigitalMedia_Photo_GetFreeSlot() > 0)
            {
                bRet = MApp_Photo_DecodeFile_Init(NULL, eAttrib & E_DM_STRM_ATTR_THUMBNAIL);
            }
            break;

        case E_DM_STRM_TYPE_MUSIC:
            {
                EN_RET eRet;
                BOOLEAN bIsWMA = FALSE;
                BOOLEAN bSupport = TRUE;

                m_u32LyricSubtitleCurTime = -1;
                m_u16CurLyricPos = -1;
                m_u32PlayCheckTime = -1;

                //init audio
               MApi_AUDIO_SetCommand(MSAPI_AUD_DVB2_DECCMD_STOP);
               MApi_AUDIO_SetSystem(MSAPI_AUD_DVB2_NONE);
               MApi_AUDIO_SetSystem(MSAPI_AUD_DVB2_MP3);

                _geDM_MusicType = _MApp_DigitalMedia_VerifyMusicType(NULL,_geDM_MusicType);

                switch(_geDM_MusicType)
                {
                    case E_DM_MUSIC_MP3:
                        _genMusicType = EN_MUSIC_MP3;
                        break;

                    case E_DM_MUSIC_AAC:
                        _genMusicType = EN_MUSIC_AAC;
                        break;

                    case E_DM_MUSIC_WAV:
                        _genMusicType = EN_MUSIC_WAV;
                        break;

                    case E_DM_MUSIC_WMA:
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
                        eRet = MApp_WMA_Main();
                        if(EXIT_WMA_INIT== eRet)
                        {
                            bRet = TRUE;
                        }
                    }
                    else
                    {
                        eRet = MApp_Music_Main(_genMusicType);
                        if(EXIT_MP3_INIT== eRet)
                        {
                            bRet = TRUE;
                        }
                    }

                    if(bRet)
                    {
                        _gstMedias[eType].eMusicFlag &= (E_DM_MUSIC_FLAG)~E_DM_MUSIC_FLG_LYRIC_VALID;
                        if(_MApp_DigitalMedia_Music_Lyric_Parser())
                        {
                            _gstMedias[eType].eMusicFlag |= (E_DM_MUSIC_FLG_LYRIC_VALID|E_DM_MUSIC_FLG_LYRIC_ENABLE);
                        }

                        //tmp use subtitle buffer as double buf
                        _MApp_DigitalMedia_Init_DoubleBuf(E_DM_STRM_TYPE_MUSIC,
                                                   (U32)((SUBTITLE_MEMORY_TYPE & MIU1) ? (SUBTITLE_ADR | MIU_INTERVAL) : (SUBTITLE_ADR)),
                                                   (SUBTITLE_LEN>0x100000 ? (0x100000):(SUBTITLE_LEN)),
                                                   _gstMedias[eType].dmStrmHdl[E_DM_STRM_HDL_MUSIC]);
                    }
                }
            }
            break;

        default:
            break;
    }

    // state change when necessary
    if (bRet == TRUE)
    {
        _gstMedias[eType].eState = E_DM_STATE_INITED;

        _gu16Photo_Wdith[_gu8Photo_DecodeIdx]   = 0;
        _gu16Photo_Height[_gu8Photo_DecodeIdx]  = 0;
        _gu32Photo_Size[_gu8Photo_DecodeIdx]    = 0;
    }
    else
    {
        // init failed, stop sub-module unconditionally to reset the change we have made
        _MApp_DigitalMedia_UnconditionalStop(eType);
    }

    return bRet;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Start the decodeing/rendering process.

    \param <IN>     \b eType: Type of media instance.

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_Play(E_DM_STRM_TYPE eType)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(eType);
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    BOOLEAN bRet = FALSE;

    // type ckecking
    if (INVALID_STRM_TYPE(eType))
    {
        return FALSE;
    }

    // state checking
    // allowed when media IS initialized
    if (_gstMedias[eType].eState != E_DM_STATE_INITED)
    {
        return FALSE;
    }

    // send cmd to sub-module
    switch (eType)
    {
        case E_DM_STRM_TYPE_MOVIE:
            // reset relative variables
            _gstMedias[eType].s16ShiftX = 0;
            _gstMedias[eType].s16ShiftY = 0;

            // reset play mode & speed
            _gstMedias[eType].eRepeatAB = E_DM_REPEAT_NONE;
            _gstMedias[eType].ePlayMode = E_DM_PLAY_MODE_NORMAL;
            _gstMedias[eType].eSpeed = E_DM_SPEED_X1;
            _gstMedias[eType].eZoom = E_DM_ZOOM_1;
            _gstMedias[eType].u32PlayTime = 0;

            if (_gstMedias[eType].bFullScreen == FALSE)
            {
                // imply preview
                MApp_VDPlayer_BeginPreview();
                MApp_VDPlayer_SetPreviewWindow(
                        _gstMedias[eType].stViewWindow.u16X,
                        _gstMedias[eType].stViewWindow.u16Y,
                        _gstMedias[eType].stViewWindow.u16Width,
                        _gstMedias[eType].stViewWindow.u16Height);
            }

            if ((bRet = MApp_VDPlayer_Play()) == TRUE)
            {
                // send event
                SEND_EVENT_NOTIFICATION(eType, E_DM_EVENT_INFO_OK, NULL, 0);
            }

            MApp_MPlayer_CheckInternalSubtitleEnabledFirst();
            break;

        case E_DM_STRM_TYPE_PHOTO:
            // record decoded photo info
            _gu16Photo_Wdith[_gu8Photo_DecodeIdx]   = MApp_Photo_GetInfo(E_PHOTO_INFO_WIDTH);
            _gu16Photo_Height[_gu8Photo_DecodeIdx]  = MApp_Photo_GetInfo(E_PHOTO_INFO_HEIGHT);
            _gu32Photo_Size[_gu8Photo_DecodeIdx]    = MApp_Photo_GetInfo(E_PHOTO_INFO_FILE_SIZE);

            if (_gstMedias[eType].bFullScreen == FALSE)
            {
                // imply preview
                MApp_Photo_Display_SetViewWin(
                        _gstMedias[eType].stViewWindow.u16X,
                        _gstMedias[eType].stViewWindow.u16Y,
                        _gstMedias[eType].stViewWindow.u16Width,
                        _gstMedias[eType].stViewWindow.u16Height);
            }
            else
            {
                // if full screen and all slots are free, call MApp_Photo_InitFullScreenDisplay()
                if (MApp_DigitalMedia_Photo_GetFreeSlot() == DM_PHOTO_TOTAL_SLOT)
                {
                    MApp_Photo_InitFullScreenDisplay();

                    // send event
                    SEND_EVENT_NOTIFICATION(eType, E_DM_EVENT_PHOTO_DECODING_NEXT, NULL, 0);
                }
            }

            // send event
            SEND_EVENT_NOTIFICATION(eType, E_DM_EVENT_INFO_OK, NULL, 0);
            bRet = TRUE;
            break;

        case E_DM_STRM_TYPE_MUSIC:
            _gstMedias[eType].ePlayMode = E_DM_PLAY_MODE_NORMAL;
            _gstMedias[eType].eSpeed = E_DM_SPEED_X1;
            _gstMedias[eType].u32PlayTime = 0;
            _gstMedias[eType].eMusicFlag = E_DM_MUSIC_FLG_NULL;

            // send event
            SEND_EVENT_NOTIFICATION(eType, E_DM_EVENT_INFO_OK, NULL, 0);
            bRet = TRUE;
            break;

        default:
            break;
    }

    // state change
    if (bRet == TRUE)
    {
        _gstMedias[eType].eState = E_DM_STATE_PLAYING;
        _gePhoto_State[_gu8Photo_DecodeIdx] = E_DM_PHOTO_SLOT_STATE_DECODING;
    }
    else
    {
        // play failed, stop sub-module unconditionally to reset the change we have made
        _MApp_DigitalMedia_UnconditionalStop(eType);
    }

    return bRet;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Stop the decodeing/rendering process.

    \param <IN>     \b eType: Type of media instance.

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
void MApp_DigitalMedia_Stop(E_DM_STRM_TYPE eType)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(eType);
    return;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    // type ckecking
    if (INVALID_STRM_TYPE(eType))
    {
        return;
    }

    // state checking
    // allowed when media IS NOT standing by
    if (_gstMedias[eType].eState == E_DM_STATE_STANDBY)
    {
        return;
    }

    _MApp_DigitalMedia_UnconditionalStop(eType);
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Pause the decodeing/rendering process.

    \param <IN>     \b eType: Type of media instance.

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_Pause(E_DM_STRM_TYPE eType)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(eType);
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    BOOLEAN bRet = FALSE;

    // type ckecking
    if (INVALID_STRM_TYPE(eType))
    {
        return FALSE;
    }

    // state checking
    // allowed when media IS playing
    if (_gstMedias[eType].eState != E_DM_STATE_PLAYING)
    {
        // exception for photo
        if ((eType == E_DM_STRM_TYPE_PHOTO)
                && (_gePhoto_State[_gu8Photo_DisplayIdx] == E_DM_PHOTO_SLOT_STATE_DISPLAYING))
        {
            // allow when there is photo displaying
        }
        else
        {
            return FALSE;
        }
    }

    // send cmd to sub-module
    switch (eType)
    {
        case E_DM_STRM_TYPE_MOVIE:
            bRet = MApp_VDPlayer_Pause();
            break;

        case E_DM_STRM_TYPE_PHOTO:
            _gePhoto_SlideShowPauseState = E_DM_PHOTO_SLIDE_SHOW_PAUSED;
            bRet = TRUE;
            break;

        case E_DM_STRM_TYPE_MUSIC:
            if(_geDM_MusicType == E_DM_MUSIC_WMA)
            {
                MApp_WMA_Pause();
            }
            else
            {
                MApp_Music_Pause();
            }
            bRet = TRUE;
            break;

        default:
            break;
    }

    // reset play mode & speed when necessary
    if (bRet == TRUE)
    {
        _gstMedias[eType].ePlayMode = E_DM_PLAY_MODE_PAUSE;
        _gstMedias[eType].eSpeed = E_DM_SPEED_X1;
    }

    return bRet;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Resume the decodeing/rendering process.

    \param <IN>     \b eType: Type of media instance.

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_Resume(E_DM_STRM_TYPE eType)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(eType);
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    BOOLEAN bRet = FALSE;
    // type ckecking
    if (INVALID_STRM_TYPE(eType))
    {
        return FALSE;
    }

    // state checking
    // allowed when media IS playing
    if (_gstMedias[eType].eState != E_DM_STATE_PLAYING)
    {
        // exception for photo
        if ((eType == E_DM_STRM_TYPE_PHOTO)
                && (_gePhoto_State[_gu8Photo_DisplayIdx] == E_DM_PHOTO_SLOT_STATE_DISPLAYING))
        {
            // allow when there is photo displaying
        }
        else
        {
            return FALSE;
        }
    }

    // send cmd to sub-module
    switch (eType)
    {
        case E_DM_STRM_TYPE_MOVIE:
            // MApp_VDPlayer_Resume() isn't usful, use MApp_VDPlayer_SetTrickMode() for resume
            // bRet = MApp_VDPlayer_Resume();
            bRet = MApp_VDPlayer_SetTrickMode(MODE_NORMAL_PLAY, PLAY_SPEEDx1);
            break;

        case E_DM_STRM_TYPE_PHOTO:
            _gePhoto_SlideShowPauseState = E_DM_PHOTO_SLIDE_SHOW_PAUSE_RELEASED;
            bRet = TRUE;
            break;

        case E_DM_STRM_TYPE_MUSIC:
            if(_geDM_MusicType == E_DM_MUSIC_WMA)
            {
                MApp_WMA_Resume();
            }
            else
            {
                MApp_Music_Resume();
            }
            bRet = TRUE;
            break;

        default:
            break;
    }

    // reset play mode & speed when necessary
    if (bRet == TRUE)
    {
        _gstMedias[eType].ePlayMode = E_DM_PLAY_MODE_NORMAL;
        _gstMedias[eType].eSpeed = E_DM_SPEED_X1;
    }

    return bRet;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Change video program. The new program is
    specified by \e u8TrackIdx.

    \param <IN>     \b eType: Type of media instance.
    \param <IN>     \b u8TrackIdx: Index of new video program.

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_ChangeProgram(E_DM_STRM_TYPE eType, U8 u8TrackIdx)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(eType);
    UNUSED(u8TrackIdx);
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    BOOLEAN bRet = FALSE;
    U32 u32TotalTrack;

    // type ckecking
    if (INVALID_STRM_TYPE(eType))
    {
        return FALSE;
    }

    // state checking
    // allowed when media IS playing
    if (_gstMedias[eType].eState != E_DM_STATE_PLAYING)
    {
        return FALSE;
    }

    // send cmd to sub-module
    switch (eType)
    {
        case E_DM_STRM_TYPE_MOVIE:
            u32TotalTrack = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_NB_PROGRAM);
            if ((u32TotalTrack > 1) && (u8TrackIdx < u32TotalTrack))
            {
                if ((bRet = MApp_VDPlayer_ChangeProgam(u8TrackIdx)) == TRUE)
                {
                    // reset shift offset
                    _gstMedias[eType].s16ShiftX = 0;
                    _gstMedias[eType].s16ShiftY = 0;

                    // reset zoom
                    _gstMedias[eType].eZoom = E_DM_ZOOM_1;

                    // reset play mode & speed
                    _gstMedias[eType].ePlayMode = E_DM_PLAY_MODE_NORMAL;
                    _gstMedias[eType].eSpeed = E_DM_SPEED_X1;

                    // cancel repeat AB
                    if (MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_MAX_FB_SPEED) != 0)
                    {
                        // cancel repeat AB only when index table exist
                        MApp_VDPlayer_SetRepeatAB(SET_REPEAT_AB_NONE);
                        _gstMedias[eType].eRepeatAB = E_DM_REPEAT_NONE;
                    }
                }
            }
            break;

        default:
            break;
    }

    return bRet;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Change audio track. The new audio track is
    specified by \e u8TrackIdx.

    \param <IN>     \b eType: Type of media instance.
    \param <IN>     \b u8TrackIdx: Index of new audio track.

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_ChangeAudio(E_DM_STRM_TYPE eType, U8 u8TrackIdx)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(eType);
    UNUSED(u8TrackIdx);
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    BOOLEAN bRet = FALSE;
    U32 u32TotalTrack;

    // type ckecking
    if (INVALID_STRM_TYPE(eType))
    {
        return FALSE;
    }

    // state checking
    // allowed when media IS playing
    if (_gstMedias[eType].eState != E_DM_STATE_PLAYING)
    {
        return FALSE;
    }

    // send cmd to sub-module
    switch (eType)
    {
        case E_DM_STRM_TYPE_MOVIE:
            u32TotalTrack = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_NB_AUDIO_TRACK);
            if ((u32TotalTrack > 1) && (u8TrackIdx < u32TotalTrack))
            {
                bRet = MApp_VDPlayer_SetAudioTrackID(u8TrackIdx);
            }
            break;

        default:
            break;
    }

    return bRet;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Change subtitle track. The new subtitle track is
    specified by \e u8TrackIdx.

    \param <IN>     \b eType: Type of media instance.
    \param <IN>     \b u8TrackIdx: Index of new subtitle track.

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_ChangeSubtitle(E_DM_STRM_TYPE eType, U8 u8TrackIdx)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(eType);
    UNUSED(u8TrackIdx);
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    BOOLEAN bRet = FALSE;
    // type ckecking
    if (INVALID_STRM_TYPE(eType))
    {
        return FALSE;
    }

    // state checking
    // allowed when media IS playing
    if (_gstMedias[eType].eState != E_DM_STATE_PLAYING)
    {
        return FALSE;
    }

    // send cmd to sub-module
    switch (eType)
    {
        case E_DM_STRM_TYPE_MOVIE:
            bRet = MApp_MPlayer_ChangeSubtitleTrack(u8TrackIdx);
            break;

        default:
            break;
    }

    return bRet;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}


///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Change external subtitle The new subtitle  is
    specified by \e eSubtitleType and stream handle.

    \param <IN>     \b eSubtitleType: Type of external subitle,if it set E_DM_SUBTITLE_INVALID,it means external subtitle is disabled.
    \param <IN>     \b SubtitleHdl: external subtitle stream handle.
    \param <IN>     \b SubStreamHdl: if it is vobsub subtitle, it should specify sub stream handle, otherwise ,this is set INVALID_DM_STRM_HDL.

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_ChangeExternalSubtitle(E_DM_SUBTITLE_TYPE eSubtitleType,DM_STRM_HDL SubtitleHdl,DM_STRM_HDL SubStreamHdl)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(eSubtitleType);
    UNUSED(SubtitleHdl);
    UNUSED(SubStreamHdl);
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    BOOLEAN bRet = TRUE;

    if (E_DM_SUBTITLE_INVALID == eSubtitleType)
    {
        //disable external subtitle
        if(MApp_MPlayer_ExternalSubtitleIsEnabled())//it is external subtitle
        {
            MApp_DigitalMedia_DisableSubtitle();
        }
        return TRUE;
    }

    if(eSubtitleType >= E_DM_SUBTITLE_NUM || SubtitleHdl == INVALID_DM_STRM_HDL)
    {
        return FALSE;
    }

    if(eSubtitleType == E_DM_SUBTITLE_SUBIDX && SubStreamHdl == INVALID_DM_STRM_HDL)
    {
        DIGITALMEDIA_DBG(printf("Subhandle is invalid for subidx subtitle!\n");)
        return FALSE;
    }

    DIGITALMEDIA_DBG(printf("Begin Parser Subtitle stream!\n");)

    MApp_MPlayer_Subtitle_Dinit();
    MApp_DigitalMedia_SetExternalSubtitleType(eSubtitleType);
    _gstMedias[E_DM_STRM_TYPE_MOVIE].dmStrmHdl[E_DM_STRM_HDL_EX_SUB_0] = SubtitleHdl;
    _gstMedias[E_DM_STRM_TYPE_MOVIE].dmStrmHdl[E_DM_STRM_HDL_EX_SUB_1] = SubStreamHdl;

    bRet = MApp_MPlayer_ExternalSubtitle_Parser(NULL, NULL);
    MApp_MPlayer_MicroDVD_Subtitle_ReCalceTime();
    return bRet;

#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Set external subtitle type.

    \param <IN>     \b eSubtitleType: Type of external subtitle.

    \return None */
///////////////////////////////////////////////////////////////////////////////
void MApp_DigitalMedia_SetExternalSubtitleType(E_DM_SUBTITLE_TYPE eSubtitleType)
{
#if ((!ENABLE_DIGITAL_MEDIA_API) || (ENABLE_SUBTITLE_DMP == 0))
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(eSubtitleType);
    return;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    enumMPlayerSubtitleType eSubtitle_Type;

    switch(eSubtitleType)
    {
        case E_DM_SUBTITLE_SRT:
            eSubtitle_Type = E_MPLAYER_SUBTITLE_SRT;
            break;
        case E_DM_SUBTITLE_SUBIDX:
            eSubtitle_Type = E_MPLAYER_SUBTITLE_SUBIDX;
            break;
        case E_DM_SUBTITLE_SSA:
            eSubtitle_Type = E_MPLAYER_SUBTITLE_SSA;
            break;
        case E_DM_SUBTITLE_ASS:
            eSubtitle_Type = E_MPLAYER_SUBTITLE_ASS;
            break;
        case E_DM_SUBTITLE_SMI:
            eSubtitle_Type = E_MPLAYER_SUBTITLE_SMI;
            break;
        case E_DM_SUBTITLE_SUB:
            eSubtitle_Type = E_MPLAYER_SUBTITLE_SUB;
            break;
        case E_DM_SUBTITLE_SUBVIEWER:
            eSubtitle_Type = E_MPLAYER_SUBTITLE_SUBVIEWER;
            break;
        case E_DM_SUBTITLE_MICRODVD:
            eSubtitle_Type = E_MPLAYER_SUBTITLE_MICRODVD;
            break;
        case E_DM_SUBTITLE_DVDSUBTITLESYSTEM:
            eSubtitle_Type = E_MPLAYER_SUBTITLE_DVDSUBTITLESYSTEM;
            break;
        default:
            eSubtitle_Type = E_MPLAYER_SUBTITLE_INVALID;
            break;

    }
    MApp_MPlayer_SetExternalSubtitleType(eSubtitle_Type);
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Enable the subtitle decodeing/rendering process.

    \param None

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_EnableSubtitle(void)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    return MApp_MPlayer_EnableMovieSubtitle();
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Disable the subtitle decodeing/rendering process.

    \param None

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_DisableSubtitle(void)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    return MApp_MPlayer_DisableMovieSubtitle();
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Jump to the time in millisecond specified by
    \e u32TimeInMs.

    \param <IN>     \b eType: Type of media instance.
    \param <IN>     \b u32TimeInMs: Specific time in millisecond.

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise.

    \note
        If the state of the media instance isn't at normal play, e.g. paused,
        it will set to normal play after this function returns TRUE. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_GotoTime(E_DM_STRM_TYPE eType, U32 u32TimeInMs)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(eType);
    UNUSED(u32TimeInMs);
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    BOOLEAN bRet = FALSE;
    U32 u32TotalTime;

    // type ckecking
    if (INVALID_STRM_TYPE(eType))
    {
        return FALSE;
    }

    // state checking
    // allowed when media IS playing
    if (_gstMedias[eType].eState != E_DM_STATE_PLAYING)
    {
        return FALSE;
    }

    // send cmd to sub-module
    switch (eType)
    {
        case E_DM_STRM_TYPE_MOVIE:
            // check if index table exists
            if (MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_MAX_FB_SPEED) == 0)
            {
                return FALSE;
            }

            u32TotalTime = MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_TOTAL_TIME);
            if (u32TimeInMs <= u32TotalTime)
            {
                if ((bRet = MApp_VDPlayer_SetPlayPosition(u32TimeInMs)) == TRUE)
                {
                    // cancel repeat AB
                    MApp_VDPlayer_SetRepeatAB(SET_REPEAT_AB_NONE);
                    _gstMedias[eType].eRepeatAB = E_DM_REPEAT_NONE;
                }
            }
            break;

        case E_DM_STRM_TYPE_MUSIC:
            // Someday, this may be needed.
            break;

        default:
            break;
    }

    return bRet;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Set trick mode by specifying \e ePlayMode
    and \e eSpeed.

    \param <IN>     \b eType: Type of media instance.
    \param <IN>     \b ePlayMode: New play mode.
    \param <IN>     \b eSpeed: Play speed.

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_SetTrickMode(E_DM_STRM_TYPE eType, E_DM_PLAY_MODE ePlayMode, E_DM_SPEED eSpeed)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(eType);
    UNUSED(ePlayMode);
    UNUSED(eSpeed);
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    BOOLEAN bRet = FALSE;

    // for movie
    EN_PLAY_MODE eMoviePlayMode;
    EN_PLAY_SPEED eMoviePlaySpeed;

    // type ckecking
    if (INVALID_STRM_TYPE(eType))
    {
        return FALSE;
    }

    // state checking
    // allowed when media IS playing
    if (_gstMedias[eType].eState != E_DM_STATE_PLAYING)
    {
        return FALSE;
    }

    // send cmd to sub-module
    switch (eType)
    {
        case E_DM_STRM_TYPE_MOVIE:
            // transform mode
            switch (ePlayMode)
            {
                case E_DM_PLAY_MODE_NORMAL:
                    eMoviePlayMode = MODE_NORMAL_PLAY;
                    break;

                case E_DM_PLAY_MODE_PAUSE:
                    eMoviePlayMode = MODE_PAUSE;
                    break;

                case E_DM_PLAY_MODE_SLOW_FORWARD:
                    eMoviePlayMode = MODE_SLOW_FORWARD;
                    break;

                case E_DM_PLAY_MODE_FAST_FORWARD:
                    eMoviePlayMode = MODE_FAST_FORWARD;
                    break;

                case E_DM_PLAY_MODE_FAST_BACKWORD:
                    eMoviePlayMode = MODE_FAST_BACKWARD;
                    break;

                default:
                    return FALSE;
            }

            // transform speed
            switch (eSpeed)
            {
                case E_DM_SPEED_X1:
                    eMoviePlaySpeed = PLAY_SPEEDx1;
                    break;

                case E_DM_SPEED_X2:
                    eMoviePlaySpeed = PLAY_SPEEDx2;
                    break;

                case E_DM_SPEED_X4:
                    eMoviePlaySpeed = PLAY_SPEEDx4;
                    break;

                case E_DM_SPEED_X8:
                    eMoviePlaySpeed = PLAY_SPEEDx8;
                    break;

                case E_DM_SPEED_X16:
                    eMoviePlaySpeed = PLAY_SPEEDx16;
                    break;

                case E_DM_SPEED_X32:
                    eMoviePlaySpeed = PLAY_SPEEDx32;
                    break;

                default:
                    return FALSE;
            }

            // cancel repeat AB when necessary
            switch (eMoviePlayMode)
            {
                case MODE_SLOW_FORWARD:
                case MODE_FAST_FORWARD:
                case MODE_FAST_BACKWARD:
                    if (MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_MAX_FB_SPEED) != 0)
                    {
                        // cancel repeat AB only when index table exist
                        MApp_VDPlayer_SetRepeatAB(SET_REPEAT_AB_NONE);
                        _gstMedias[eType].eRepeatAB = E_DM_REPEAT_NONE;
                    }
                    break;

                default:
                    break;
            }

            // send cmd
            if ((bRet = MApp_VDPlayer_SetTrickMode(eMoviePlayMode, eMoviePlaySpeed)) == TRUE)
            {
                // reset play mode & speed
                _gstMedias[eType].ePlayMode = ePlayMode;
                _gstMedias[eType].eSpeed = eSpeed;
            }
            break;

        case E_DM_STRM_TYPE_PHOTO:
            switch (ePlayMode)
            {
                case E_DM_PLAY_MODE_PAUSE:
                    // for photo, pause display, not decode
                    MApp_DigitalMedia_Pause(eType);
                    break;

                case E_DM_PLAY_MODE_NORMAL:
                    if (_gstMedias[eType].ePlayMode == E_DM_PLAY_MODE_PAUSE)
                    {
                        // for photo, resume display, not decode
                        MApp_DigitalMedia_Resume(eType);
                    }
                    break;

                default:
                    break;
            }
            break;

        case E_DM_STRM_TYPE_MUSIC:
            {
                BOOLEAN bForward = TRUE;

                // transform mode
                switch (ePlayMode)
                {
                    case E_DM_PLAY_MODE_NORMAL:
                        if(_gstMedias[eType].ePlayMode == E_DM_PLAY_MODE_PAUSE)
                        {
                            if(_geDM_MusicType == E_DM_MUSIC_WMA)
                            {
                                MApp_WMA_Resume();
                            }
                            else
                            {
                                MApp_Music_Resume();
                            }

                            // reset play mode & speed
                            _gstMedias[eType].ePlayMode = E_DM_PLAY_MODE_NORMAL;
                            _gstMedias[eType].eSpeed = E_DM_SPEED_X1;
                            return TRUE;
                        }
                        else
                        {
                            bForward = TRUE;
                            eSpeed = E_DM_SPEED_X1;
                        }
                        break;

                    case E_DM_PLAY_MODE_PAUSE:
                        if(_geDM_MusicType == E_DM_MUSIC_WMA)
                        {
                            MApp_WMA_Pause();
                        }
                        else
                        {
                            MApp_Music_Pause();
                        }

                        // reset play mode
                        _gstMedias[eType].ePlayMode = E_DM_PLAY_MODE_PAUSE;
                        return TRUE;

                    case E_DM_PLAY_MODE_SLOW_FORWARD:
                    case E_DM_PLAY_MODE_FAST_FORWARD:
                        bForward = TRUE;
                        break;

                    case E_DM_PLAY_MODE_FAST_BACKWORD:
                        bForward = FALSE;
                        break;

                    default:
                        return FALSE;
                }

                if(_geDM_MusicType == E_DM_MUSIC_WMA)
                {
                    EN_WMA_SPEED eWmaSpeed;

                    // transform speed
                    switch (eSpeed)
                    {
                        case E_DM_SPEED_X1:
                            eWmaSpeed = EN_WMA_SPEED_X1;
                            break;

                        case E_DM_SPEED_X2:
                            eWmaSpeed = EN_WMA_SPEED_X2;
                            break;

                        case E_DM_SPEED_X4:
                            eWmaSpeed = EN_WMA_SPEED_X4;
                            break;

                        case E_DM_SPEED_X8:
                            eWmaSpeed = EN_WMA_SPEED_X8;
                            break;

                        case E_DM_SPEED_X16:
                            eWmaSpeed = EN_WMA_SPEED_X16;
                            break;

                        case E_DM_SPEED_X32:
                            eWmaSpeed = EN_WMA_SPEED_X32;
                            break;

                        default:
                            return FALSE;
                    }

                    bRet = MApp_WMA_FastForwardBackward(bForward,eWmaSpeed);
                }
                else
                {
                    EN_MP3_SPEED eMp3Speed;

                    // transform speed
                    switch (eSpeed)
                    {
                        case E_DM_SPEED_X1:
                            eMp3Speed = EN_MP3_SPEED_X1;
                            break;

                        case E_DM_SPEED_X2:
                            eMp3Speed = EN_MP3_SPEED_X2;
                            break;

                        case E_DM_SPEED_X4:
                            eMp3Speed = EN_MP3_SPEED_X4;
                            break;

                        case E_DM_SPEED_X8:
                            eMp3Speed = EN_MP3_SPEED_X8;
                            break;

                        case E_DM_SPEED_X16:
                            eMp3Speed = EN_MP3_SPEED_X16;
                            break;

                        case E_DM_SPEED_X32:
                            eMp3Speed = EN_MP3_SPEED_X32;
                            break;

                        default:
                            return FALSE;
                    }

                    bRet = MApp_Music_FastForwardBackward(bForward,eMp3Speed);
                }

                if(bRet)
                {
                    // reset play mode & speed
                    _gstMedias[eType].ePlayMode = ePlayMode;
                    _gstMedias[eType].eSpeed = eSpeed;
                }
            }
            break;

        default:
            break;
    }

    return bRet;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Get current trick mode.

    \param <IN>     \b eType: Type of media instance.
    \param <OUT>    \b pePlayMode: Current play mode.
    \param <OUT>    \b peSpeed: Current play speed.

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_GetTrickMode(E_DM_STRM_TYPE eType, E_DM_PLAY_MODE *pePlayMode, E_DM_SPEED *peSpeed)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__)));

    UNUSED(eType);
    UNUSED(pePlayMode);
    UNUSED(peSpeed);
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    BOOLEAN bRet = FALSE;

    // type ckecking
    if (INVALID_STRM_TYPE(eType))
    {
        return FALSE;
    }

    // parameter checking
    if ((pePlayMode == NULL) || (peSpeed == NULL))
    {
        return FALSE;
    }

    // retrive setting
    switch (eType)
    {
        case E_DM_STRM_TYPE_MOVIE:
        case E_DM_STRM_TYPE_PHOTO:
        case E_DM_STRM_TYPE_MUSIC:
            *pePlayMode = _gstMedias[eType].ePlayMode;
            *peSpeed = _gstMedias[eType].eSpeed;
            bRet = TRUE;
            break;

        default:
            break;
    }

    return bRet;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Set repeat A/B or cancel it. A and B represent
    markers on the time line of media instance playing. And A always smaller
    than B. Here is the secnario of this function. \n
    First repeatA marker is set when normal playing. After a period of time
    repeatB marker is set. The playing of media instance will jump back to the
    time represented by marker A and plays normally. When the time represented
    by marker B is reached, playing then jumps back to the time of A. This
    repeating play stops when
    - \e MApp_DigitalMedia_SetRepeatAB() is called again to cancel it when
    \e eRepeatAct is \e E_DM_REPEAT_NONE.
    - video program changed by calling \e MApp_DigitalMedia_ChangeProgram().
    - fast forward, fast backward or slow forward is requested by calling
    \e MApp_DigitalMedia_SetTrickMode().
    - Jumping to a specific time is issued by calling \e
    MApp_DigitalMedia_GotoTime().

    \param <IN>     \b eType: Type of media instance.
    \param <IN>     \b eRepeatAct: Repeating actoin.
    \param <IN>     \b peSpeed: Current play speed.

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_SetRepeatAB(E_DM_STRM_TYPE eType, E_DM_REPEAT_AB eRepeatAct)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(eType);
    UNUSED(eRepeatAct);
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    BOOLEAN bRet = FALSE;

    // for movie
    EN_SET_REPEATAB eMovieRepeatAction;

    // type ckecking
    if (INVALID_STRM_TYPE(eType))
    {
        return FALSE;
    }

    // state checking
    // allowed when media IS playing
    if (_gstMedias[eType].eState != E_DM_STATE_PLAYING)
    {
        return FALSE;
    }

    // send cmd to sub-module
    switch (eType)
    {
        case E_DM_STRM_TYPE_MOVIE:
            // transform repeat action
            switch (eRepeatAct)
            {
                case E_DM_REPEAT_NONE:
                    eMovieRepeatAction = SET_REPEAT_AB_NONE;
                    break;

                case E_DM_REPEAT_A:
                    eMovieRepeatAction = SET_REPEAT_A;
                    break;

                case E_DM_REPEAT_B:
                    eMovieRepeatAction = SET_REPEAT_B;
                    break;

                default:
                    return FALSE;
            }

            // send cmd
            if (MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_MAX_FB_SPEED) != 0)
            {
                // set repeat AB only when index table exist
                bRet = MApp_VDPlayer_SetRepeatAB(eMovieRepeatAction);
                _gstMedias[eType].eRepeatAB = eRepeatAct;
            }
            break;

        default:
            break;
    }

    return bRet;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Get current repeat A/B setting.

    \param <IN>     \b eType: Type of media instance.
    \param <OUT>    \b peRepeatAct: Current repeating setting.

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_GetRepeatAB(E_DM_STRM_TYPE eType, E_DM_REPEAT_AB *peRepeatAct)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(eType);
    UNUSED(peRepeatAct);
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    BOOLEAN bRet = FALSE;

    // type ckecking
    if (INVALID_STRM_TYPE(eType))
    {
        return FALSE;
    }

    // parameter checking
    if (peRepeatAct == NULL)
    {
        return FALSE;
    }

    // retrive setting
    switch (eType)
    {
        case E_DM_STRM_TYPE_MOVIE:
            *peRepeatAct = _gstMedias[eType].eRepeatAB;
            bRet = TRUE;
            break;

        default:
            break;
    }

    return bRet;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Set desired view window size and position.
    This function has effects when \e eType is \e E_DM_STRM_TYPE_MOVIE or
    \e E_DM_STRM_TYPE_PHOTO.

    \param <IN>     \b eType: Type of media instance.
    \param <IN>     \b bFullScreen: Full screen display or not.
    \param <IN>     \b pstViewWin: Desired view window.

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise.

    \note
        - This function can be called before calling \e MApp_DigitalMedia_Play().
        - If \e bFullScreen is TRUE, the values stored in \e pstViewWin will not
        be examed.
        - If \e bFullScreen is FALSE, the value of \e u16Width and \e u16Height
        in \e pstViewWin can't exceed \e DEFAULT_PREVIEW_WND_WIDTH and
        \e DEFAULT_PREVIEW_WND_HEIGHT respectively. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_SetView(E_DM_STRM_TYPE eType, BOOLEAN bFullScreen, ST_DM_RECT *pstViewWin)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(eType);
    UNUSED(bFullScreen);
    UNUSED(pstViewWin);
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    BOOLEAN bRet = FALSE;
    ST_DM_RECT stViewWin;

    // type ckecking
    if (INVALID_STRM_TYPE(eType))
    {
        return FALSE;
    }

    // state checking
    // allowed when media IS NOT playing
    if (_gstMedias[eType].eState == E_DM_STATE_PLAYING)
    {
        // exception for photo
        if (eType == E_DM_STRM_TYPE_PHOTO)
        {
            if (MApp_DigitalMedia_Photo_GetFreeSlot() != DM_PHOTO_TOTAL_SLOT)
            {
                // also dosen't allow when there is any photo decoding/displaying
                return FALSE;
            }
        }
        else
        {
            return FALSE;
        }
    }

    // parameter checking
    if (bFullScreen == TRUE)
    {
        stViewWin.u16X = 0;
        stViewWin.u16Y = 0;
        stViewWin.u16Width  = PANEL_WIDTH;
        stViewWin.u16Height = PANEL_HEIGHT;
        goto set_view_window_directly;
    }

    if (pstViewWin == NULL)
    {
        return FALSE;
    }

    stViewWin = *pstViewWin;

    if ((stViewWin.u16X == 0) && (stViewWin.u16Y == 0)
            && (stViewWin.u16Width == PANEL_WIDTH) && (stViewWin.u16Height == PANEL_HEIGHT))
    {
        bFullScreen = TRUE;
        goto set_view_window_directly;
    }

    // NOTE: now, if it isn't full screen,
    // NOTE: the view window size can't exceed (DEFAULT_PREVIEW_WND_WIDTH x DEFAULT_PREVIEW_WND_HEIGHT)
    if (stViewWin.u16Width > DEFAULT_PREVIEW_WND_WIDTH)
    {
        stViewWin.u16Width = DEFAULT_PREVIEW_WND_WIDTH;
    }

    if (stViewWin.u16Height > DEFAULT_PREVIEW_WND_HEIGHT)
    {
        stViewWin.u16Height = DEFAULT_PREVIEW_WND_HEIGHT;
    }

    // boundary checking
    if (((stViewWin.u16X + stViewWin.u16Width) > PANEL_WIDTH)
        || ((stViewWin.u16Y + stViewWin.u16Height) > PANEL_HEIGHT))
    {
        return FALSE;
    }


set_view_window_directly:
    // save setting
    switch (eType)
    {
        case E_DM_STRM_TYPE_MOVIE:
        case E_DM_STRM_TYPE_PHOTO:
            _gstMedias[eType].bFullScreen = bFullScreen;
            _gstMedias[eType].stViewWindow = stViewWin;
            bRet = TRUE;
            break;

        default:
            break;
    }

    return bRet;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Get current view window size and position.
    This function has effects when \e eType is \e E_DM_STRM_TYPE_MOVIE or
    \e E_DM_STRM_TYPE_PHOTO.

    \param <IN>     \b eType: Type of media instance.
    \param <OUT>    \b pstViewWin: Current view window setting.

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_GetView(E_DM_STRM_TYPE eType, ST_DM_RECT *pstViewWin)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(eType);
    UNUSED(pstViewWin);
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    BOOLEAN bRet = FALSE;

    // type ckecking
    if (INVALID_STRM_TYPE(eType))
    {
        return FALSE;
    }

    // parameter checking
    if (pstViewWin == NULL)
    {
        return FALSE;
    }

    // retrive setting
    switch (eType)
    {
        case E_DM_STRM_TYPE_MOVIE:
        case E_DM_STRM_TYPE_PHOTO:
            *pstViewWin = _gstMedias[eType].stViewWindow;
            bRet = TRUE;
            break;

        default:
            break;
    }

    return bRet;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Set rotation angle of rendered image. This
    function has effects when \e eType is \e E_DM_STRM_TYPE_PHOTO.

    \param <IN>     \b eType: Type of media instance.
    \param <IN>     \b eRotate: Desired rotation angle.

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_SetRotation(E_DM_STRM_TYPE eType, E_DM_ROTATION eRotate)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(eType);
    UNUSED(eRotate);
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    BOOLEAN bRet = FALSE;

    // for photo
    EN_PHOTO_ROTATION ePhotoRotation;

    // type ckecking
    if (INVALID_STRM_TYPE(eType))
    {
        return FALSE;
    }

    // state checking
    // allowed when media IS playing
    if (_gstMedias[eType].eState != E_DM_STATE_PLAYING)
    {
        // exception for photo
        if ((eType == E_DM_STRM_TYPE_PHOTO)
                && (_gePhoto_State[_gu8Photo_DisplayIdx] == E_DM_PHOTO_SLOT_STATE_DISPLAYING))
        {
            // allow when there is photo displaying
        }
        else
        {
            return FALSE;
        }
    }

    // send cmd to sub-module
    switch (eType)
    {
        case E_DM_STRM_TYPE_PHOTO:
            // transform rotation
            ePhotoRotation = _MApp_DigitalMedia_Photo_TransformRotation(eRotate);
            if (ePhotoRotation == EN_PHOTO_ROTATE_NOT_SUPPORT)
            {
                return FALSE;
            }

            // send cmd
            bRet = MApp_Photo_Rotate(ePhotoRotation);
            break;

        default:
            break;
    }

    // save setting
    if (bRet == TRUE)
    {
        _gstMedias[eType].eRotation = eRotate;

        // auto pause for photo siide show
        if (eType == E_DM_STRM_TYPE_PHOTO)
        {
            _gePhoto_SlideShowPauseState = E_DM_PHOTO_SLIDE_SHOW_PAUSED;

            _gstMedias[eType].ePlayMode = E_DM_PLAY_MODE_PAUSE;
            _gstMedias[eType].eSpeed = E_DM_SPEED_X1;
        }
    }

    return bRet;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Get current rotation angle of rendered image.
    This function has effects when \e eType is \e E_DM_STRM_TYPE_PHOTO.

    \param <IN>     \b eType: Type of media instance.
    \param <OUT>    \b peRotate: Current rotation angle.

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_GetRotation(E_DM_STRM_TYPE eType, E_DM_ROTATION *peRotate)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(eType);
    UNUSED(peRotate);
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    BOOLEAN bRet = FALSE;

    // type ckecking
    if (INVALID_STRM_TYPE(eType))
    {
        return FALSE;
    }

    // parameter checking
    if (peRotate == NULL)
    {
        return FALSE;
    }

    // state checking
    // allowed when media IS playing
    if (_gstMedias[eType].eState != E_DM_STATE_PLAYING)
    {
        // exception for photo
        if ((eType == E_DM_STRM_TYPE_PHOTO)
                && (_gePhoto_State[_gu8Photo_DisplayIdx] == E_DM_PHOTO_SLOT_STATE_DISPLAYING))
        {
            // allow when there is photo displaying
        }
        else
        {
            return FALSE;
        }
    }

    // retrive setting
    switch (eType)
    {
        case E_DM_STRM_TYPE_PHOTO:
            *peRotate = _gstMedias[eType].eRotation;
            bRet = TRUE;
            break;

        default:
            break;
    }

    return bRet;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Set zoom factor to rendered frame/image.
    This function has effects when \e eType is \e E_DM_STRM_TYPE_MOVIE or
    \e E_DM_STRM_TYPE_PHOTO.

    \param <IN>     \b eType: Type of media instance.
    \param <IN>     \b eZoom: Desired zoom factor.

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_SetZoom(E_DM_STRM_TYPE eType, E_DM_ZOOM eZoom)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(eType);
    UNUSED(eZoom);
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    BOOLEAN bRet = FALSE;

    // for movie
    VDPLAYER_ZOOM_FACT eMovieZoom;

    // for photo
    EN_PHOTO_ZOOMING ePhotoZoom;

    // type ckecking
    if (INVALID_STRM_TYPE(eType))
    {
        return FALSE;
    }

    // state checking
    // allowed when media IS playing
    if (_gstMedias[eType].eState != E_DM_STATE_PLAYING)
    {
        // exception for photo
        if ((eType == E_DM_STRM_TYPE_PHOTO)
                && (_gePhoto_State[_gu8Photo_DisplayIdx] == E_DM_PHOTO_SLOT_STATE_DISPLAYING))
        {
            // allow when there is photo displaying
        }
        else
        {
            return FALSE;
        }
    }

    // send cmd to sub-module
    switch (eType)
    {
        case E_DM_STRM_TYPE_MOVIE:
            // transform zoom factor
            eMovieZoom = _MApp_DigitalMedia_Movie_TransformZoomFactor(eZoom);
            if (eMovieZoom == VDPLAYER_ZOOM_FACT_UNSUPPORT)
            {
                return FALSE;
            }

            // send cmd
            MApp_VDPlayer_ScaleVideo(eMovieZoom);
            bRet = TRUE;
            break;

        case E_DM_STRM_TYPE_PHOTO:
            // transform zoom factor
            ePhotoZoom = _MApp_DigitalMedia_Photo_TransformZoomFactor(eZoom);
            if (ePhotoZoom == EN_PHOTO_ZOOM_NOT_SUPPORT)
            {
                return FALSE;
            }

            // send cmd
            bRet = MApp_Photo_Zooming(ePhotoZoom);
            break;

        default:
            break;
    }

    // save setting
    if (bRet == TRUE)
    {
        _gstMedias[eType].s16ShiftX = 0;
        _gstMedias[eType].s16ShiftY = 0;

        _gstMedias[eType].eZoom = eZoom;

        // auto pause for photo siide show
        if (eType == E_DM_STRM_TYPE_PHOTO)
        {
            _gePhoto_SlideShowPauseState = E_DM_PHOTO_SLIDE_SHOW_PAUSED;

            _gstMedias[eType].ePlayMode = E_DM_PLAY_MODE_PAUSE;
            _gstMedias[eType].eSpeed = E_DM_SPEED_X1;
        }
    }

    return bRet;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Get current zoom factor to rendered frame/image.
    This function has effects when \e eType is \e E_DM_STRM_TYPE_MOVIE or
    \e E_DM_STRM_TYPE_PHOTO.

    \param <IN>     \b eType: Type of media instance.
    \param <OUT>    \b peZoom: Current zoom factor.

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_GetZoom(E_DM_STRM_TYPE eType, E_DM_ZOOM *peZoom)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(eType);
    UNUSED(peZoom);
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    BOOLEAN bRet = FALSE;

    // type ckecking
    if (INVALID_STRM_TYPE(eType))
    {
        return FALSE;
    }

    // parameter checking
    if (peZoom == NULL)
    {
        return FALSE;
    }

    // state checking
    // allowed when media IS playing
    if (_gstMedias[eType].eState != E_DM_STATE_PLAYING)
    {
        // exception for photo
        if ((eType == E_DM_STRM_TYPE_PHOTO)
                && (_gePhoto_State[_gu8Photo_DisplayIdx] == E_DM_PHOTO_SLOT_STATE_DISPLAYING))
        {
            // allow when there is photo displaying
        }
        else
        {
            return FALSE;
        }
    }

    // retrive setting
    switch (eType)
    {
        case E_DM_STRM_TYPE_MOVIE:
        case E_DM_STRM_TYPE_PHOTO:
            *peZoom = _gstMedias[eType].eZoom;
            bRet = TRUE;
            break;

        default:
            break;
    }

    return bRet;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: After zooming in, frmae/image pixels go out of
    view ragne. This function is used to get these pixes back to screen.
    This function has effects when \e eType is \e E_DM_STRM_TYPE_MOVIE or
    \e E_DM_STRM_TYPE_PHOTO.

    \param <IN>     \b eType: Type of media instance.
    \param <IN>     \b eDirection: Desired moving direction.
    \param <IN>     \b u16Offset: Offset in pixel.

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_MoveView(E_DM_STRM_TYPE eType, E_DM_DIRECTION eDirection, U16 u16Offset)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(eType);
    UNUSED(eDirection);
    UNUSED(u16Offset);
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    BOOLEAN bRet = FALSE;
    S16 s16X, s16Y;

    // for movie
    VDPLAYER_ZOOM_FACT eMovieZoom;

    // for photo
    EN_PHOTO_DIRECTION ePhotoMoveDirection;

    // type ckecking
    if (INVALID_STRM_TYPE(eType))
    {
        return FALSE;
    }

    // state checking
    // allowed when media IS playing
    if (_gstMedias[eType].eState != E_DM_STATE_PLAYING)
    {
        // exception for photo
        if ((eType == E_DM_STRM_TYPE_PHOTO)
                && (_gePhoto_State[_gu8Photo_DisplayIdx] == E_DM_PHOTO_SLOT_STATE_DISPLAYING))
        {
            // allow when there is photo displaying
        }
        else
        {
            return FALSE;
        }
    }

    // calculate shift quantity
    s16X = _gstMedias[eType].s16ShiftX;
    s16Y = _gstMedias[eType].s16ShiftY;
    switch(eDirection)
    {
        case E_DM_DIRECTION_UP:
            s16Y -= u16Offset;
            break;

        case E_DM_DIRECTION_DOWN:
            s16Y += u16Offset;
            break;

        case E_DM_DIRECTION_LEFT:
            s16X -= u16Offset;
            break;

        case E_DM_DIRECTION_RIGHT:
            s16X += u16Offset;
            break;

        default:
            return FALSE;
    }

    // send cmd to sub-module
    switch (eType)
    {
        case E_DM_STRM_TYPE_MOVIE:
            // transform zoom factor
            eMovieZoom = _MApp_DigitalMedia_Movie_TransformZoomFactor(_gstMedias[eType].eZoom);

            // send cmd
            bRet = MApp_VDPlayer_ShiftVideo(&s16X, &s16Y, 0, 0, eMovieZoom);
            break;

        case E_DM_STRM_TYPE_PHOTO:
            // transform direction
            ePhotoMoveDirection = _MApp_DigitalMedia_Photo_TransformDirection(eDirection);
            if (ePhotoMoveDirection == EN_PHOTO_MOVE_NOT_SUPPORT)
            {
                return FALSE;
            }

            // send cmd
            bRet = MApp_Photo_MoveViewWindow(ePhotoMoveDirection, u16Offset);
            break;

        default:
            break;
    }

    // save setting
    if (bRet == TRUE)
    {
        _gstMedias[eType].s16ShiftX = s16X;
        _gstMedias[eType].s16ShiftY = s16Y;
    }

    return bRet;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Check how many slots left for next photo decode.
    Photo decode is possible only when the return value of this function greater
    than 0.

    \param None

    \return
        Photo slot left for next decode procedure. */
///////////////////////////////////////////////////////////////////////////////
U32 MApp_DigitalMedia_Photo_GetFreeSlot(void)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    //printf("%s: not activated\n", __FUNCTION__);
    return 0;
#else // #if (!ENABLE_DIGITAL_MEDIA_API)

    U32 u32Idx, u32Cnt;

    for (u32Idx = 0, u32Cnt = 0; u32Idx < DM_PHOTO_TOTAL_SLOT; u32Idx++)
    {
        if (_gePhoto_State[u32Idx] == E_DM_PHOTO_SLOT_STATE_FREE)
        {
            u32Cnt++;
        }
    }

    return u32Cnt;
#endif
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Disable photo displaying.

    \param None

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_Photo_StopDisplay(void)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    U8 u8Idx;

    msAPI_Scaler_SetBlueScreen(TRUE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
    MApi_XC_GenerateBlackVideo(ENABLE, MAIN_WINDOW);

    MApp_DigitalMedia_Photo_SlideShow(TRUE);

    for (u8Idx = 0; u8Idx < DM_PHOTO_TOTAL_SLOT; u8Idx++)
    {
        _gePhoto_State[u8Idx] = E_DM_PHOTO_SLOT_STATE_FREE;

        _gu16Photo_Wdith[u8Idx]     = 0;
        _gu16Photo_Height[u8Idx]    = 0;
        _gu32Photo_Size[u8Idx]      = 0;
    }
    _gu8Photo_DecodeIdx = 0;
    _gu8Photo_DisplayIdx = 0;

    return TRUE;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Enable/Disable photo slide show.

    \param <IN>     \b bEnable: Enable or Disable.

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_Photo_SlideShow(BOOLEAN bEnable)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(bEnable);
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    MApp_Photo_SlideShow(bEnable);
    return TRUE;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Set photo slide show time out value in second.

    \param <IN>     \b u16TimeOutInSec: Desired time out value in second.

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_Photo_SlideShowTimeOut(U16 u16TimeOutInSec)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(u16TimeOutInSec);
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    _gu16Photo_SlideShowTimeOutInSec = u16TimeOutInSec;
    return TRUE;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Get relative information of media instance after
    the event \e E_DM_EVENT_INFO_OK is notified.

    \param <IN>     \b eType: Type of media instance.
    \param <IN>     \b enInfo: Desired information.

    \return: Value of the information */
///////////////////////////////////////////////////////////////////////////////
U32 MApp_DigitalMedia_GetInfo(E_DM_STRM_TYPE eType, E_DM_INFO enInfo)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(eType);
    UNUSED(enInfo);
    return 0;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    // type ckecking
    if (INVALID_STRM_TYPE(eType))
    {
        return 0;
    }

    // state checking
    // allowed when media IS playing
    if (_gstMedias[eType].eState == E_DM_STATE_STANDBY)
    {
        return 0;
    }

    switch (eType)
    {
        case E_DM_STRM_TYPE_MOVIE:
            switch (enInfo)
            {
                case E_DM_INFO_H_SIZE:
                    return MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_H_SIZE);

                case E_DM_INFO_V_SIZE:
                    return MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_V_SIZE);

                case E_DM_INFO_FRM_PER_SEC:
                    return MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_FRM_PER_SEC);

                case E_DM_INFO_TOTAL_TIME:
                    return MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_TOTAL_TIME) / 1000;

                case E_DM_INFO_CUR_TIME:
                    return MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_CUR_TIME) / 1000;

                case E_DM_INFO_NB_PROGRAM:
                    return MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_NB_PROGRAM);

                case E_DM_INFO_PROGRAM_IDX:
                    return MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_PROGRAM_ID);

                case E_DM_INFO_NB_AUDIO_TRACK:
                    return MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_NB_AUDIO_TRACK);

                case E_DM_INFO_AUDIO_TRACK_IDX:
                    return MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_AUDIO_TRACK_ID);

                case E_DM_INFO_NB_SUBTITLE_TRACK:
                    return (U32)MApp_MPlayer_QuerySubtitleNum();

                case E_DM_INFO_SUBTITLE_TRACK_IDX:
                    return (U32)MApp_MPlayer_QueryCurSubtitleTrackIdx();

                case E_DM_INFO_CURRENT_SUBTITLE_TEXT:
                    return (U32)MApp_MPlayer_CurSubtitleIsText();

                case E_DM_INFO_CURRENT_SUBTITLE_ISUNICODE:
                    return (U32)MApp_MPlayer_CurSubtitleIsUnicode();

                case E_DM_INFO_MAX_FB_SPEED:
                    return MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_MAX_FB_SPEED);

                default:
                    break;
            }
            break;

        case E_DM_STRM_TYPE_PHOTO:
            switch (enInfo)
            {
                case E_DM_INFO_H_SIZE:
                    return _gu16Photo_Wdith[_gu8Photo_DisplayIdx];

                case E_DM_INFO_V_SIZE:
                    return _gu16Photo_Height[_gu8Photo_DisplayIdx];

                case E_DM_INFO_DISPLAYING_PHOTO_SIZE:
                    return _gu32Photo_Size[_gu8Photo_DisplayIdx];

                case E_DM_INFO_DECODED_PHOTO_WDITH:
                    return _gu16Photo_Wdith[_gu8Photo_DecodeIdx];

                case E_DM_INFO_DECODED_PHOTO_HEIGHT:
                    return _gu16Photo_Height[_gu8Photo_DecodeIdx];

                case E_DM_INFO_PHOTO_DECODE_PROGRESS:
                    return MApp_Photo_GetInfo(E_PHOTO_INFO_PROGRESS);

                default:
                    break;
            }
            break;

        case E_DM_STRM_TYPE_MUSIC:
            switch (enInfo)
            {
                case E_DM_INFO_TOTAL_TIME:
                    if(_geDM_MusicType == E_DM_MUSIC_WMA)
                        return MApp_WMA_GetTotalTime();
                    else
                        return (U32)MApp_Music_GetTotalTime();

                case E_DM_INFO_CUR_TIME:
                    if(_geDM_MusicType == E_DM_MUSIC_WMA)
                        return MApp_WMA_GetCurrentTime();
                    else
                        return (U32)MApp_Music_GetCurrentTime();

                case E_DM_INFO_MUSIC_LAYER_LEN:
                    if(_geDM_MusicType == E_DM_MUSIC_WMA)
                        return 0;//not support for wma
                    else
                        return (U32)MApp_Music_GetInfoStringLength(MP3_INFO_LAYER);

                case E_DM_INFO_MUSIC_BITRATE_LEN:
                    if(_geDM_MusicType == E_DM_MUSIC_WMA)
                        return 32;
                    else
                        return (U32)MApp_Music_GetInfoStringLength(MP3_INFO_BITRATE);

                case E_DM_INFO_MUSIC_SAMPLINGRATE_LEN:
                    if(_geDM_MusicType == E_DM_MUSIC_WMA)
                        return 32;
                    else
                        return (U32)MApp_Music_GetInfoStringLength(MP3_INFO_SAMPLINGRATE);

                case E_DM_INFO_MUSIC_ALBUM_LEN:
                    if(_geDM_MusicType == E_DM_MUSIC_WMA)
                        return 32;
                    else
                        return (U32)MApp_Music_GetInfoStringLength(MP3_INFO_ALBUM);

                case E_DM_INFO_MUSIC_TITLE_LEN:
                    if(_geDM_MusicType == E_DM_MUSIC_WMA)
                        return 32;
                    else
                        return (U32)MApp_Music_GetInfoStringLength(MP3_INFO_TITLE);

                case E_DM_INFO_MUSIC_ARTIST_LEN:
                    if(_geDM_MusicType == E_DM_MUSIC_WMA)
                        return 32;
                    else
                        return (U32)MApp_Music_GetInfoStringLength(MP3_INFO_ARTIST);

                case E_DM_INFO_MUSIC_YEAR_LEN:
                    if(_geDM_MusicType == E_DM_MUSIC_WMA)
                        return 32;
                    else
                        return (U32)MApp_Music_GetInfoStringLength(MP3_INFO_YEAR);

                case E_DM_INFO_MUSIC_GENRE_LEN:
                    if(_geDM_MusicType == E_DM_MUSIC_WMA)
                        return 0;//not support for wma
                    else
                        return (U32)MApp_Music_GetInfoStringLength(MP3_INFO_GENRE);

                case E_DM_INFO_MUSIC_COMMENT_LEN:
                    if(_geDM_MusicType == E_DM_MUSIC_WMA)
                        return 0;   //not support for wma
                    else
                        return (U32)MApp_Music_GetInfoStringLength(MP3_INFO_COMMENT);

                case E_DM_INFO_MUSIC_CHECK_FF_FB_LEN:
                    if(_geDM_MusicType == E_DM_MUSIC_WMA)
                        return 32;
                    else
                        return (U32)MApp_Music_GetInfoStringLength(MP3_INFO_CHECK_FF_FB);

                case E_DM_INFO_MUSIC_TYPE:
                    return (U32)_geDM_MusicType;
                default:
                    break;

            }

        default:
            break;
    }

    return 0;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

BOOLEAN MApp_DigitalMedia_GetMusicInfo(E_DM_INFO enInfo, U8* pBuf, U16 u16Len)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(pBuf);
    UNUSED(enInfo);
    UNUSED(u16Len);
    return TRUE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    U8 *pu8String;
    U16 u16StringLen;
    BOOLEAN bRet = FALSE;

    if(_geDM_MusicType == E_DM_MUSIC_WMA)
    {
        EN_WMA_INFO eWmaInfo;

        switch(enInfo)
        {
            case  E_DM_INFO_MUSIC_BITRATE:
                eWmaInfo = WMA_INFO_BITRATE;
                break;

            case  E_DM_INFO_MUSIC_SAMPLINGRATE:
                eWmaInfo = WMA_INFO_SAMPLINGRATE;
                break;

            case  E_DM_INFO_MUSIC_ALBUM:
                eWmaInfo = WMA_INFO_ALBUM;
                break;

            case  E_DM_INFO_MUSIC_TITLE:
                eWmaInfo = WMA_INFO_TITLE;
                break;

            case  E_DM_INFO_MUSIC_ARTIST:
                eWmaInfo = WMA_INFO_ARTIST;
                break;

            case  E_DM_INFO_MUSIC_YEAR:
                eWmaInfo = WMA_INFO_YEAR;
                break;

            case  E_DM_INFO_MUSIC_CHECK_FF_FB:
                eWmaInfo = WMA_INFO_CHECK_FF_FB;
                break;

            default:
                return FALSE;
        }

        pu8String = MApp_WMA_GetInfoString(eWmaInfo, NULL);
        if ((pu8String != NULL) && (pBuf != NULL))
        {
            memcpy(pBuf, pu8String, u16Len);
            bRet = TRUE;
        }

        return bRet;
    }
    else if(_geDM_MusicType > E_DM_MUSIC_NONE && _geDM_MusicType < E_DM_MUSIC_WMA)
    {
        EN_MP3_INFO  enMP3Info;

        switch(enInfo)
        {
            case  E_DM_INFO_MUSIC_BITRATE:
                enMP3Info = MP3_INFO_BITRATE;
                break;

            case  E_DM_INFO_MUSIC_SAMPLINGRATE:
                enMP3Info = MP3_INFO_SAMPLINGRATE;
                break;

            case  E_DM_INFO_MUSIC_ALBUM:
                enMP3Info = MP3_INFO_ALBUM;
                break;

            case  E_DM_INFO_MUSIC_TITLE:
                enMP3Info = MP3_INFO_TITLE;
                break;

            case  E_DM_INFO_MUSIC_ARTIST:
                enMP3Info = MP3_INFO_ARTIST;
                break;

            case  E_DM_INFO_MUSIC_YEAR:
                enMP3Info = MP3_INFO_YEAR;
                break;

            case  E_DM_INFO_MUSIC_GENRE:
                enMP3Info = MP3_INFO_GENRE;
                break;

            case  E_DM_INFO_MUSIC_COMMENT:
                enMP3Info = MP3_INFO_COMMENT;
                break;

            case  E_DM_INFO_MUSIC_CHECK_FF_FB:
                u16StringLen = 1;
                enMP3Info = MP3_INFO_CHECK_FF_FB;
                break;

            default:
                  return FALSE;
        }

        pu8String = MApp_Music_GetInfoString(enMP3Info, NULL);
        if ((pu8String != NULL) && (pBuf != NULL))
        {
            memcpy(pBuf, pu8String, u16Len);
            bRet = TRUE;
        }

        return bRet;
    }
    return bRet;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Set DRM key.

    \param <IN>     \b pu8Key: The buffer which stores the DRM key.
    \param <IN>     \b u32Size: The size in byte of DRM key.

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_SetDRMKey(U8 *pu8Key, U32 u32Size)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(pu8Key);
    UNUSED(u32Size);
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    return MApp_VDPlayer_WMDRMPD_SavePrivate(pu8Key, u32Size);
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Set Music type.

    \param <IN>     \b pu8Key: The buffer which stores the DRM key.
    \param <IN>     \b u32Size: The size in byte of DRM key.

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_SetMusicType(E_DM_MUSIC_TYPE enMusicType)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(enMusicType);
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    if(enMusicType < E_DM_MUSIC_MAX && enMusicType > E_DM_MUSIC_NONE)
    {
        _geDM_MusicType =  enMusicType;
        return TRUE;
    }
    else
    {
        _geDM_MusicType = E_DM_MUSIC_NONE;
    }

    return FALSE;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Enable LRC Lyric.

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_EnableLRCLyric(void)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    _gstMedias[E_DM_STRM_TYPE_MUSIC].eMusicFlag |= E_DM_MUSIC_FLG_LYRIC_ENABLE;
    return TRUE;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Disable LRC Lyric.

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_DisableLRCLyric(void)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    _gstMedias[E_DM_STRM_TYPE_MUSIC].eMusicFlag &= (E_DM_MUSIC_FLAG)~E_DM_MUSIC_FLG_LYRIC_ENABLE;
    return TRUE;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: judge whether the current LRCLyric is available.

    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_IsCurrentLRCLyricAvail(void)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__)));
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    if(_gstMedias[E_DM_STRM_TYPE_MUSIC].eMusicFlag & E_DM_MUSIC_FLG_LYRIC_VALID)
    {
        return TRUE;
    }

    return FALSE;
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Enable envent.
    \param <IN>     \b eType: Type of media instance.
    \param <IN>     \b eEvent: event type, E_DM_EVENT_ALL means enable all events.
    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise.
    \note
        defaultly, E_DM_EVENT_PLAYING_TIME_TICK is disabled
        and other event is enabled. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_EnableEvent(E_DM_STRM_TYPE eType, E_DM_EVENT eEvent)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(eType);
    UNUSED(eEvent);
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    if(eEvent < E_DM_EVENT_MAX || eEvent == E_DM_EVENT_ALL)
    {
        _gstMedias[eType].eEventMask |= eEvent;
        DIGITALMEDIA_DBG(printf("now event mask is:%x\n",_gstMedias[eType].eEventMask));
        return TRUE;
    }
    else
    {
        return FALSE;
    }
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Disable envent.
    \param <IN>     \b eType: Type of media instance.
    \param <IN>     \b eEvent: event type,E_DM_EVENT_ALL means disable all events.
    \return
        \b TRUE, if this function complete successfully. \n
        \b FALSE, otherwise. */
///////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_DigitalMedia_DisableEvent(E_DM_STRM_TYPE eType, E_DM_EVENT eEvent)
{
#if (!ENABLE_DIGITAL_MEDIA_API)
    MS_DEBUG_MSG(printf("%s: not activated\n", __FUNCTION__));

    UNUSED(eType);
    UNUSED(eEvent);
    return FALSE;

#else // #if (!ENABLE_DIGITAL_MEDIA_API)
    if(eEvent < E_DM_EVENT_MAX || eEvent == E_DM_EVENT_ALL)
    {
        _gstMedias[eType].eEventMask &= (E_DM_EVENT)~eEvent;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
#endif // #if (!ENABLE_DIGITAL_MEDIA_API)
}

#if (ENABLE_DIGITAL_MEDIA_API)
//-------------------------------------------------------------------------------------------------
// Function Implementation -- data stream I/O callbacks
//-------------------------------------------------------------------------------------------------
U32 MApp_DigitalMedia_DataStream_Open(void *pPrivate, U8 u8Mode, E_DATA_STREAM_TYPE eType)
{
    U32 u32Hdl = INVALID_DATA_STREAM_HDL;

    UNUSED(pPrivate);
    UNUSED(u8Mode);

    switch (eType)
    {
        // for movie playing
        case E_DATA_STREAM_TYPE_VIDEO:
            u32Hdl = (U32)_gstMedias[E_DM_STRM_TYPE_MOVIE].dmStrmHdl[E_DM_STRM_HDL_VIDEO];
            break;

        case E_DATA_STREAM_TYPE_AUDIO:
            u32Hdl = (U32)_gstMedias[E_DM_STRM_TYPE_MOVIE].dmStrmHdl[E_DM_STRM_HDL_AUDIO];
            break;

        case E_DATA_STREAM_TYPE_IN_SUB:
            u32Hdl = (U32)_gstMedias[E_DM_STRM_TYPE_MOVIE].dmStrmHdl[E_DM_STRM_HDL_IN_SUB];
            break;

        case E_DATA_STREAM_TYPE_EX_SUB0:
            u32Hdl = (U32)_gstMedias[E_DM_STRM_TYPE_MOVIE].dmStrmHdl[E_DM_STRM_HDL_EX_SUB_0];
            break;

        case E_DATA_STREAM_TYPE_EX_SUB1:
            u32Hdl = (U32)_gstMedias[E_DM_STRM_TYPE_MOVIE].dmStrmHdl[E_DM_STRM_HDL_EX_SUB_1];
            break;

        // for music playing
        case E_DATA_STREAM_TYPE_MUSIC:
            u32Hdl = (U32)_gstMedias[E_DM_STRM_TYPE_MUSIC].dmStrmHdl[E_DM_STRM_HDL_MUSIC];
            break;

        case E_DATA_STREAM_TYPE_MUSIC2:
            u32Hdl = (U32)_gstMedias[E_DM_STRM_TYPE_MUSIC].dmStrmHdl[E_DM_STRM_HDL_MUSIC2];
            break;

        case E_DATA_STREAM_TYPE_LYRIC:
            u32Hdl = (U32)_gstMedias[E_DM_STRM_TYPE_MUSIC].dmStrmHdl[E_DM_STRM_HDL_LYRIC];
            break;

        // for photo playing
        case E_DATA_STREAM_TYPE_PHOTO:
            u32Hdl = (U32)_gstMedias[E_DM_STRM_TYPE_PHOTO].dmStrmHdl[E_DM_STRM_HDL_PHOTO];
            break;

        default:
            break;
    }

    //seek to begin.
    if(INVALID_DATA_STREAM_HDL != u32Hdl)
    {
        LongLong u64Pos;
        u64Pos.Hi = 0;
        u64Pos.Lo = 0;
        MApp_DigitalMedia_DataStream_Seek(u32Hdl,u64Pos, E_DATA_STREAM_SEEK_SET);
    }
    return u32Hdl;
}

BOOLEAN MApp_DigitalMedia_DataStream_Close(U32 u32Hdl)
{
    E_DM_STRM_TYPE eType;

    // get corresponding digital media type
    eType = _MApp_DigitalMedia_GetStrmType((DM_STRM_HDL)u32Hdl);
    if (eType == E_DM_STRM_TYPE_NUM)
    {
        // wrong handl or already closed
        return FALSE;
    }

    // do not close here because some case need reopen. So close file in _MApp_DigitalMedia_UnconditionalStop().
    /*if (_gstMedias[eType].fnCallbacks.pfnClose)
    {
        return _gstMedias[eType].fnCallbacks.pfnClose((DM_STRM_HDL)u32Hdl);
    }*/

    return FALSE;
}

U32 MApp_DigitalMedia_DataStream_Read(U32 u32Hdl, void *pBuffAddr, U32 u32Length)
{
    E_DM_STRM_TYPE eType;

    // get corresponding digital media type
    eType = _MApp_DigitalMedia_GetStrmType((DM_STRM_HDL)u32Hdl);
    if (eType == E_DM_STRM_TYPE_NUM)
    {
        // wrong handl or already closed
        return u32Length;
    }

    // satisfy request if possible
    if (_gstMedias[eType].fnCallbacks.pfnRead)
    {
        U32 u32UnRead;

        if(_gstMedias[eType].bEnableDoubleBuf && _gstMedias[eType].Hdl_EnableDoubleBuf  == u32Hdl )
        {
            u32UnRead= _MApp_DigitalMedia_Read_DoubleBuf(eType,(void*)((U32)pBuffAddr),u32Length);
            _gstMedias[eType].u64StreamPos.Lo += (u32Length - u32UnRead); //refine later
        }
        else
        {
            E_DM_STRM_IO_ERR eIoErr;

            u32UnRead = _gstMedias[eType].fnCallbacks.pfnRead((DM_STRM_HDL)u32Hdl, pBuffAddr, u32Length, &eIoErr);
            // TODO: what to do with eIoErr?
        }
        return u32UnRead;
    }

    return u32Length;
}

BOOLEAN MApp_DigitalMedia_DataStream_Seek(U32 u32Hdl, LongLong u64Pos, E_DATA_STREAM_SEEK_OPTION eOption)
{
    E_DM_STRM_TYPE eType;

    // get corresponding digital media type
    eType = _MApp_DigitalMedia_GetStrmType((DM_STRM_HDL)u32Hdl);
    if (eType == E_DM_STRM_TYPE_NUM)
    {
        // wrong handl or already closed
        return FALSE;
    }

    // satisfy request if possible
    if (_gstMedias[eType].fnCallbacks.pfnSeek)
    {
        E_DM_STRM_IO_ERR eIoErr;
        BOOLEAN bRet;

        // TBD: since u64Pos is LongLong (a non-negative type), we can't do substraction
        // TBD: what' can we do?
        ASSERT(eOption != E_DATA_STREAM_SEEK_CUR);

        bRet = _gstMedias[eType].fnCallbacks.pfnSeek((DM_STRM_HDL)u32Hdl, u64Pos, &eIoErr);
        // TODO: what to do with eIoErr?
        if(_gstMedias[eType].bEnableDoubleBuf && _gstMedias[eType].Hdl_EnableDoubleBuf  == u32Hdl )
        {
            DIGITALMEDIA_DBG(printf("seek to %x\n",u64Pos.Lo);)
            if(u64Pos.Lo != _gstMedias[eType].u64StreamPos.Lo)
            {
                _MApp_DigitalMedia_Reset_DoubleBuf(eType);
            }
            _gstMedias[eType].u64StreamPos = u64Pos;
        }
        return bRet;
    }

    return FALSE;
}

LongLong MApp_DigitalMedia_DataStream_Tell(U32 u32Hdl)
{
    E_DM_STRM_TYPE eType;
    LongLong u64Pos;

    u64Pos.Hi = 0;
    u64Pos.Lo = 0;

    // get corresponding digital media type
    eType = _MApp_DigitalMedia_GetStrmType((DM_STRM_HDL)u32Hdl);
    if (eType == E_DM_STRM_TYPE_NUM)
    {
        // wrong handl or already closed
        return u64Pos;
    }

    // satisfy request if possible
    if (_gstMedias[eType].fnCallbacks.pfnTell)
    {
        if(_gstMedias[eType].bEnableDoubleBuf && _gstMedias[eType].Hdl_EnableDoubleBuf  == u32Hdl )
        {
            return _gstMedias[eType].u64StreamPos;
        }
        else
        {
            return _gstMedias[eType].fnCallbacks.pfnTell((DM_STRM_HDL)u32Hdl);
        }
    }

    return u64Pos;
}

LongLong MApp_DigitalMedia_DataStream_Length(U32 u32Hdl)
{
    E_DM_STRM_TYPE eType;
    LongLong u64Length;

    u64Length.Hi = 0;
    u64Length.Lo = 0;

    // get corresponding digital media type
    eType = _MApp_DigitalMedia_GetStrmType((DM_STRM_HDL)u32Hdl);
    if (eType == E_DM_STRM_TYPE_NUM)
    {
        // wrong handl or already closed
        return u64Length;
    }

    // satisfy request if possible
    if (_gstMedias[eType].fnCallbacks.pfnLength)
    {
        return _gstMedias[eType].fnCallbacks.pfnLength((DM_STRM_HDL)u32Hdl);
    }

    return u64Length;
}

BOOLEAN MApp_DigitalMedia_MovieStopInit(EN_VDPLAYER_FORCE_STOP eType)
{
    if (eType == E_FORCE_STOP_INIT)
    {
        if (_gstMedias[E_DM_STRM_TYPE_MOVIE].fnCallbacks.pfnIsStopAsked)
        {
            return _gstMedias[E_DM_STRM_TYPE_MOVIE].fnCallbacks.pfnIsStopAsked();
        }
    }

    return FALSE;
}
#endif //#if (ENABLE_DIGITAL_MEDIA_API)

//-------------------------------------------------------------------------------------------------
// Local funcion -- misc functions
//-------------------------------------------------------------------------------------------------
#if (ENABLE_DIGITAL_MEDIA_API)
static void _MApp_DigitalMedia_Reset(E_DM_STRM_TYPE eType)
{
    E_DM_STRM_HDL eHdlIdx;

    _gstMedias[eType].eState    = E_DM_STATE_STANDBY;
    _gstMedias[eType].eAttrib   = E_DM_STRM_ATTR_NONE;
    memset(&_gstMedias[eType].fnCallbacks, 0, sizeof(_gstMedias[eType].fnCallbacks));

    for (eHdlIdx = E_DM_STRM_HDL_MIN; eHdlIdx < E_DM_STRM_HDL_MAX; eHdlIdx++)
    {
        _gstMedias[eType].dmStrmHdl[eHdlIdx] = INVALID_DM_STRM_HDL;
    }

    _gstMedias[eType].bEnableDoubleBuf = FALSE;
    _MApp_DigitalMedia_Reset_DoubleBuf(eType);

    MApp_DigitalMedia_EnableEvent(eType, E_DM_EVENT_ALL);
    MApp_DigitalMedia_DisableEvent(eType, E_DM_EVENT_PLAYING_TIME_TICK); //defaultly , disable notify time.
}

static void _MApp_DigitalMedia_UnconditionalStop(E_DM_STRM_TYPE eType)
{
    // send cmd to sub-module
    switch (eType)
    {
        case E_DM_STRM_TYPE_MOVIE:
            MApp_VDPlayer_SetCfg(E_VDPLAYER_CFG_BM_STREAM_MODE, E_BM_STREAM_MODE_NORMAL);
            MApp_VDPlayer_SetCfg(E_VDPLAYER_CFG_FORCE_STOP_CALLBACK, (U32)NULL);

            // TBD: cancel repeat AB anyway? --> Yes, because CoProcessor doesn't do so.
            if (MApp_VDPlayer_GetInfo(E_VDPLAYER_INFO_MAX_FB_SPEED) != 0)
            {
                // cancel repeat AB only when index table exist
                MApp_VDPlayer_SetRepeatAB(SET_REPEAT_AB_NONE);
                _gstMedias[eType].eRepeatAB = E_DM_REPEAT_NONE;
            }

            MApp_VDPlayer_StopAndCloseDisplay();
            MApp_VDPlayer_StopPreview();
            MApp_MPlayer_Subtitle_Dinit();
            MApp_VDPlayer_EnableVideoOnly(FALSE);

            if (_gstMedias[eType].fnCallbacks.pfnClose)
            {
                if(_gstMedias[eType].dmStrmHdl[E_DM_STRM_HDL_VIDEO] != INVALID_DATA_STREAM_HDL)
                {
                    _gstMedias[eType].fnCallbacks.pfnClose((DM_STRM_HDL)_gstMedias[eType].dmStrmHdl[E_DM_STRM_HDL_VIDEO]);
                    _gstMedias[eType].dmStrmHdl[E_DM_STRM_HDL_VIDEO] = INVALID_DATA_STREAM_HDL;
                }

                if(_gstMedias[eType].dmStrmHdl[E_DM_STRM_HDL_AUDIO] != INVALID_DATA_STREAM_HDL)
                {
                    _gstMedias[eType].fnCallbacks.pfnClose((DM_STRM_HDL)_gstMedias[eType].dmStrmHdl[E_DM_STRM_HDL_AUDIO]);
                    _gstMedias[eType].dmStrmHdl[E_DM_STRM_HDL_AUDIO] = INVALID_DATA_STREAM_HDL;
                }

                if(_gstMedias[eType].dmStrmHdl[E_DM_STRM_HDL_IN_SUB] != INVALID_DATA_STREAM_HDL)
                {
                    _gstMedias[eType].fnCallbacks.pfnClose((DM_STRM_HDL)_gstMedias[eType].dmStrmHdl[E_DM_STRM_HDL_IN_SUB]);
                    _gstMedias[eType].dmStrmHdl[E_DM_STRM_HDL_IN_SUB] = INVALID_DATA_STREAM_HDL;
                }

                if(_gstMedias[eType].dmStrmHdl[E_DM_STRM_HDL_EX_SUB_0] != INVALID_DATA_STREAM_HDL)
                {
                    _gstMedias[eType].fnCallbacks.pfnClose((DM_STRM_HDL)_gstMedias[eType].dmStrmHdl[E_DM_STRM_HDL_EX_SUB_0]);
                    _gstMedias[eType].dmStrmHdl[E_DM_STRM_HDL_EX_SUB_0] = INVALID_DATA_STREAM_HDL;
                }

                if(_gstMedias[eType].dmStrmHdl[E_DM_STRM_HDL_EX_SUB_1] != INVALID_DATA_STREAM_HDL)
                {
                    _gstMedias[eType].fnCallbacks.pfnClose((DM_STRM_HDL)_gstMedias[eType].dmStrmHdl[E_DM_STRM_HDL_EX_SUB_1]);
                    _gstMedias[eType].dmStrmHdl[E_DM_STRM_HDL_EX_SUB_1] = INVALID_DATA_STREAM_HDL;
                }

            }
            break;

        case E_DM_STRM_TYPE_PHOTO:
            MApp_Photo_Stop();

            if (_gstMedias[eType].fnCallbacks.pfnClose)
            {
                if(_gstMedias[eType].dmStrmHdl[E_DM_STRM_HDL_PHOTO] != INVALID_DATA_STREAM_HDL)
                {
                    _gstMedias[eType].fnCallbacks.pfnClose((DM_STRM_HDL)_gstMedias[eType].dmStrmHdl[E_DM_STRM_HDL_PHOTO]);
                    _gstMedias[eType].dmStrmHdl[E_DM_STRM_HDL_PHOTO] = INVALID_DATA_STREAM_HDL;
                }
            }
            break;

        case E_DM_STRM_TYPE_MUSIC:
            if(_geDM_MusicType == E_DM_MUSIC_WMA)
            {
                MApp_WMA_Stop();
            }
            else
            {
                MApp_Music_Stop();
            }

            if (_gstMedias[eType].fnCallbacks.pfnClose)
            {
                if(_gstMedias[eType].dmStrmHdl[E_DM_STRM_HDL_MUSIC] != INVALID_DATA_STREAM_HDL)
                {
                    _gstMedias[eType].fnCallbacks.pfnClose((DM_STRM_HDL)_gstMedias[eType].dmStrmHdl[E_DM_STRM_HDL_MUSIC]);
                    _gstMedias[eType].dmStrmHdl[E_DM_STRM_HDL_MUSIC] = INVALID_DATA_STREAM_HDL;
                }

                if(_gstMedias[eType].dmStrmHdl[E_DM_STRM_HDL_MUSIC2] != INVALID_DATA_STREAM_HDL)
                {
                    _gstMedias[eType].fnCallbacks.pfnClose((DM_STRM_HDL)_gstMedias[eType].dmStrmHdl[E_DM_STRM_HDL_MUSIC2]);
                    _gstMedias[eType].dmStrmHdl[E_DM_STRM_HDL_MUSIC2] = INVALID_DATA_STREAM_HDL;
                }

                if(_gstMedias[eType].dmStrmHdl[E_DM_STRM_HDL_LYRIC] != INVALID_DATA_STREAM_HDL)
                {
                    _gstMedias[eType].fnCallbacks.pfnClose((DM_STRM_HDL)_gstMedias[eType].dmStrmHdl[E_DM_STRM_HDL_LYRIC]);
                    _gstMedias[eType].dmStrmHdl[E_DM_STRM_HDL_LYRIC] = INVALID_DATA_STREAM_HDL;
                }
            }
            break;

        default:
            break;
    }

    // unregister data stream I/O callback
    _MApp_DigitalMedia_UnRegisterDataStreamIOCallBack(eType);

    // TODO: re-consider again for new architecture
    _MApp_DigitalMedia_Reset(eType);
}

static void _MApp_DigitalMedia_InitCoProcessor(void)
{
#if defined(MIPS_CHAKRA) || defined(MSOS_TYPE_LINUX) || defined(__AEONR2__) || defined(ARM_CHAKRA)
    msAPI_COPRO_Init(BIN_ID_CODE_VDPLAYER,((AEON_MEM_MEMORY_TYPE & MIU1) ? (AEON_MM_MEM_ADR | MIU_INTERVAL) : (AEON_MM_MEM_ADR)),AEON_MM_MEM_LEN);
#else
    msAPI_COPRO_Init(BIN_ID_CODE_VDPLAYER,((BEON_MEM_MEMORY_TYPE & MIU1) ? (BEON_MEM_ADR | MIU_INTERVAL) : (BEON_MEM_ADR)),BEON_MEM_LEN);
#endif
    msAPI_Timer_Delayms(50);
}

static void _MApp_DigitalMedia_RegisterDataStreamIOCallBack(void)
{
    BOOLEAN bCallbackNeeded = TRUE;
    E_DM_STRM_TYPE eTypeIdx;

    // check if data stream I/O callback is already registered
    for (eTypeIdx = E_DM_STRM_TYPE_MIN; eTypeIdx < E_DM_STRM_TYPE_NUM; eTypeIdx++)
    {
        if (_gstMedias[eTypeIdx].eState != E_DM_STATE_STANDBY)
        {
            bCallbackNeeded = FALSE;
            break;
        }
    }

    if (bCallbackNeeded == TRUE)
    {
        _gDataStreamIOFunc.pfnOpen      = MApp_DigitalMedia_DataStream_Open;
        _gDataStreamIOFunc.pfnClose     = MApp_DigitalMedia_DataStream_Close;
        _gDataStreamIOFunc.pfnRead      = MApp_DigitalMedia_DataStream_Read;
        _gDataStreamIOFunc.pfnSeek      = MApp_DigitalMedia_DataStream_Seek;
        _gDataStreamIOFunc.pfnTell      = MApp_DigitalMedia_DataStream_Tell;
        _gDataStreamIOFunc.pfnLength    = MApp_DigitalMedia_DataStream_Length;
        msAPI_DataStreamIO_OptionRegistation(&_gDataStreamIOFunc);
    }
}

static void _MApp_DigitalMedia_UnRegisterDataStreamIOCallBack(E_DM_STRM_TYPE eType)
{
    BOOLEAN bCallbackNeeded = TRUE;
    E_DM_STRM_TYPE eTypeIdx;

    if (eType == E_DM_STRM_TYPE_NUM)
    {
        bCallbackNeeded = FALSE;
    }
    else
    {
        // check if data stream I/O callback is been using by other type of media
        for (eTypeIdx = E_DM_STRM_TYPE_MIN; eTypeIdx < E_DM_STRM_TYPE_NUM; eTypeIdx++)
        {
            if ((_gstMedias[eTypeIdx].eState != E_DM_STATE_STANDBY)
                    && (eTypeIdx != eType))
            {
                break;
            }
        }

        if (eTypeIdx == E_DM_STRM_TYPE_NUM)
        {
            bCallbackNeeded = FALSE;
        }
    }

    if (bCallbackNeeded == FALSE)
    {
        msAPI_DataStreamIO_OptionRegistation(NULL);
    }
}

static E_DM_STRM_TYPE _MApp_DigitalMedia_GetStrmType(DM_STRM_HDL dmHdl)
{
    E_DM_STRM_TYPE eTypeIdx;
    E_DM_STRM_HDL eHdlIdx;

    if(dmHdl == INVALID_DATA_STREAM_HDL)
    {
        DIGITALMEDIA_DBG(printf("invalid stream handle\n");)
        return E_DM_STRM_TYPE_NUM;
    }

    for (eTypeIdx = E_DM_STRM_TYPE_MIN; eTypeIdx < E_DM_STRM_TYPE_NUM; eTypeIdx++)
    {
        for (eHdlIdx = E_DM_STRM_HDL_MIN; eHdlIdx < E_DM_STRM_HDL_MAX; eHdlIdx++)
        {
            if (dmHdl == _gstMedias[eTypeIdx].dmStrmHdl[eHdlIdx])
            {
                break;
            }
        }

        // break 1st for loop when found
        if (eHdlIdx != E_DM_STRM_HDL_MAX)
        {
            break;
        }
    }

    return eTypeIdx;
}

static VDPLAYER_ZOOM_FACT _MApp_DigitalMedia_Movie_TransformZoomFactor(E_DM_ZOOM eDmZoom)
{
    // transform zoom factor
    switch (eDmZoom)
    {
        case E_DM_ZOOM_1_DIV_4:
            return VDPLAYER_ZOOM_FACT_1_DIV_4;

        case E_DM_ZOOM_1_DIV_2:
            return VDPLAYER_ZOOM_FACT_1_DIV_2;

        case E_DM_ZOOM_1:
            return VDPLAYER_ZOOM_FACT_NORMAL;

        case E_DM_ZOOM_2:
            return VDPLAYER_ZOOM_FACT_2X;

        case E_DM_ZOOM_4:
            return VDPLAYER_ZOOM_FACT_4X;

        case E_DM_ZOOM_8:
            return VDPLAYER_ZOOM_FACT_8X;

        default:
            break;
    }

    return VDPLAYER_ZOOM_FACT_UNSUPPORT;
}

static EN_PHOTO_ZOOMING _MApp_DigitalMedia_Photo_TransformZoomFactor(E_DM_ZOOM eDmZoom)
{
    // transform zoom factor
    switch (eDmZoom)
    {
        case E_DM_ZOOM_1_DIV_8:
            return EN_PHOTO_ZOOM_1_8;

        case E_DM_ZOOM_1_DIV_4:
            return EN_PHOTO_ZOOM_1_4;

        case E_DM_ZOOM_1_DIV_2:
            return EN_PHOTO_ZOOM_1_2;

        case E_DM_ZOOM_1:
            return EN_PHOTO_ZOOM_1;

        case E_DM_ZOOM_2:
            return EN_PHOTO_ZOOM_2;

        case E_DM_ZOOM_4:
            return EN_PHOTO_ZOOM_4;

        case E_DM_ZOOM_8:
            return EN_PHOTO_ZOOM_8;

        default:
            break;
    }

    return EN_PHOTO_ZOOM_NOT_SUPPORT;
}

static EN_PHOTO_DIRECTION _MApp_DigitalMedia_Photo_TransformDirection(E_DM_DIRECTION eDirection)
{
    // transform move direction
    switch (eDirection)
    {
        case E_DM_DIRECTION_UP:
            return EN_PHOTO_MOVE_UP;

        case E_DM_DIRECTION_DOWN:
            return EN_PHOTO_MOVE_DOWN;

        case E_DM_DIRECTION_LEFT:
            return EN_PHOTO_MOVE_LEFT;

        case E_DM_DIRECTION_RIGHT:
            return EN_PHOTO_MOVE_RIGHT;

        default:
            break;
    }

    return EN_PHOTO_MOVE_NOT_SUPPORT;
}

static EN_PHOTO_ROTATION _MApp_DigitalMedia_Photo_TransformRotation(E_DM_ROTATION eRotation)
{
    // transform rotation
    switch (eRotation)
    {
        case E_DM_ROTATION_0:
            return EN_PHOTO_ROTATE_0;

        case E_DM_ROTATION_90:
            return EN_PHOTO_ROTATE_90;

        case E_DM_ROTATION_180:
            return EN_PHOTO_ROTATE_180;

        case E_DM_ROTATION_270:
            return EN_PHOTO_ROTATE_270;

        default:
            break;
    }

    return EN_PHOTO_ROTATE_NOT_SUPPORT;
}
#endif //#if (ENABLE_DIGITAL_MEDIA_API)

//-------------------------------------------------------------------------------------------------
// Local funcion -- lyric & subtitle
//-------------------------------------------------------------------------------------------------
#if (ENABLE_DIGITAL_MEDIA_API)
static BOOLEAN _MApp_DigitalMedia_Music_Lyric_Parser(void)
{
    U8 *pu8Data;
    U32 u32FileSize,u32ReadSize;
    U32 u32StreamHandleIdx_LRC;

    MApp_Music_LyricInit();

    if(INVALID_DATA_STREAM_HDL == (u32StreamHandleIdx_LRC = msAPI_DataStreamIO_Open(NULL, OPEN_MODE_FOR_READ, E_DATA_STREAM_TYPE_LYRIC)))
    {
        goto _MApp_DigitalMedia_Music_Lyric_Parser_END;
    }
    u32FileSize = msAPI_DataStreamIO_Length(u32StreamHandleIdx_LRC);
    if(u32FileSize == 0)
    {
        goto _MApp_DigitalMedia_Music_Lyric_Parser_END;
    }

    // Read file.
    msAPI_DataStreamIO_Seek(u32StreamHandleIdx_LRC,0,E_DATA_STREAM_SEEK_SET);
    u32ReadSize = MIN(u32FileSize+512, MUSIC_LYRIC_BUFFER_LEN);
    if(u32ReadSize == msAPI_DataStreamIO_Read(u32StreamHandleIdx_LRC, (void*)((MUSIC_LYRIC_BUFFER_MEMORY_TYPE & MIU1) ? (MUSIC_LYRIC_BUFFER_ADR | MIU_INTERVAL) : (MUSIC_LYRIC_BUFFER_ADR)),u32ReadSize))
    {
        goto _MApp_DigitalMedia_Music_Lyric_Parser_END;
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

    if(MApp_Music_LRC_Lyrics_Parser(u32FileSize))
    {
        msAPI_DataStreamIO_Close(u32StreamHandleIdx_LRC);
        return TRUE;
    }

_MApp_DigitalMedia_Music_Lyric_Parser_END:
    if(INVALID_DATA_STREAM_HDL != u32StreamHandleIdx_LRC)
    {
        msAPI_DataStreamIO_Close(u32StreamHandleIdx_LRC);
    }

    return FALSE;
}

static void _MApp_DigitalMedia_GetLyric(U16 u16LyricPos, U8 *pu8Dst)
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

static E_DM_MUSIC_TYPE _MApp_DigitalMedia_VerifyMusicType(FileEntry *pEntry,E_DM_MUSIC_TYPE enMusicType)
{
    U8 *pFileBufPtr;
    U32 u32FileHandle,u16Mp3HeaderOffset,u32Delta,u32Offset = 0,i,u32TagSize = 0,u32FileSize;;
    U32 u32FileBuffAddr = ((MP3_INFO_READ_MEMORY_TYPE & MIU1) ? (MP3_INFO_READ_ADR | MIU_INTERVAL) : (MP3_INFO_READ_ADR));


    u32FileHandle = msAPI_DataStreamIO_Open(pEntry, OPEN_MODE_FOR_READ,E_DATA_STREAM_TYPE_MUSIC);
    if(u32FileHandle == INVALID_DATA_STREAM_HDL)
    {
        DIGITALMEDIA_DBG(printf("Open file failed\n"));
        return enMusicType;
    }
    u32FileSize = msAPI_DataStreamIO_Length(u32FileHandle);
    msAPI_DataStreamIO_Seek(u32FileHandle, 0,E_DATA_STREAM_SEEK_SET);
    msAPI_DataStreamIO_Read(u32FileHandle, (void*)u32FileBuffAddr, FAT_SECTOR_SIZE_512BYTE * 8); // 4k is xdata window size


    pFileBufPtr = (U8 *)_PA2VA(u32FileBuffAddr);

    // if has ID3 v2,skip it.
    if ((pFileBufPtr[0] == 'I') && (pFileBufPtr[1] == 'D') && (pFileBufPtr[2] == '3'))
    {
        DIGITALMEDIA_DBG(printf("\nskip ID3 tag\n"));
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
                DIGITALMEDIA_DBG(printf("two ID3 tag\n"));
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
                DIGITALMEDIA_DBG(printf("It is WAV file\n"));
                enMusicType = E_DM_MUSIC_WAV;   // it is WAV file
                goto _MApp_DigitalMedia_VerifyMusicType_end;
            }
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
                DIGITALMEDIA_DBG(printf("It is WMA file\n"));
                enMusicType = E_DM_MUSIC_WMA;   // it is WMA file
                goto _MApp_DigitalMedia_VerifyMusicType_end;
            }
        }
    }

     //check whether it is AAC file
    if((pFileBufPtr[4] == 'f') && (pFileBufPtr[5] == 't') && (pFileBufPtr[6] == 'y') && (pFileBufPtr[7] == 'p'))
    {
        //AAC M4A file
        DIGITALMEDIA_DBG(printf("It is AAC M4A file\n"));
        enMusicType = E_DM_MUSIC_AAC;
        goto _MApp_DigitalMedia_VerifyMusicType_end;
    }
    else if((pFileBufPtr[0] == 'A') && (pFileBufPtr[1] == 'D') && (pFileBufPtr[2] == 'I') && (pFileBufPtr[3] == 'F'))
    {
        //ADIF file
        DIGITALMEDIA_DBG(printf("It is AAC ADIF file\n"));
        enMusicType = E_DM_MUSIC_AAC;
        goto _MApp_DigitalMedia_VerifyMusicType_end;
    }
    else if((pFileBufPtr[0] == 0xFF)&&((pFileBufPtr[1] & 0xF6) == 0xF0))
    {
        //ADTS file
        DIGITALMEDIA_DBG(printf("It is AAC ADTS file\n"));
        enMusicType = E_DM_MUSIC_AAC;
        goto _MApp_DigitalMedia_VerifyMusicType_end;
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
            DIGITALMEDIA_DBG(printf("It is mp3 file\n"));
            enMusicType = E_DM_MUSIC_MP3;   // it is MP3 file
            goto _MApp_DigitalMedia_VerifyMusicType_end;
        }
    }

    DIGITALMEDIA_DBG(printf("can not find match type, return type according file ext\n"));

_MApp_DigitalMedia_VerifyMusicType_end:
    msAPI_DataStreamIO_Close(u32FileHandle);
    return enMusicType;
}

///////////////////////////////////////////////////////////////////////////////
/*! \details \b Description: Draw external subtitle call back function.

    \param <IN>     \b bShowSubtitile: show or hide subtitle.
    \param <IN>     \b u32TextDataAddress: subtitle data surce.
    \param <IN>     \b u16Len: subtitle data length.

    \return None */
///////////////////////////////////////////////////////////////////////////////
void MApp_DigitalMedia_DrawExternalSubtitle(BOOLEAN bShowSubtitile, U32 u32TextDataAddress, U16 u16Len)
{
    if (bShowSubtitile == TRUE)
    {
        SEND_EVENT_NOTIFICATION(E_DM_STRM_TYPE_MOVIE, E_DM_EVENT_SHOW_MOVIE_SUBTITLE, u32TextDataAddress, u16Len);
    }
    else
    {
        SEND_EVENT_NOTIFICATION(E_DM_STRM_TYPE_MOVIE, E_DM_EVENT_HIDE_MOVIE_SUBTITLE, NULL, 0);
    }
}
#endif //#if (ENABLE_DIGITAL_MEDIA_API)

//-------------------------------------------------------------------------------------------------
// Local funcion -- double buffer
//-------------------------------------------------------------------------------------------------
#if (ENABLE_DIGITAL_MEDIA_API)
static BOOLEAN  _MApp_DigitalMedia_Init_DoubleBuf(E_DM_STRM_TYPE eType, U32 u32BufAddr, U32 u32BufSize,DM_STRM_HDL Hdl_EnableDoubleBuf)
{
    if(u32BufAddr == NULL || u32BufSize == 0 || INVALID_STRM_TYPE(eType))
    {
        return FALSE;
    }

    DIGITALMEDIA_DBG(printf("init double buffer:%x,len:%d\n",u32BufAddr,u32BufSize);)

    _gstMedias[eType].u32DoubleBufAddr = u32BufAddr;
    _gstMedias[eType].u32DoubleBufSize = u32BufSize;
    _gstMedias[eType].CurrentBufIndex = 0;
    _gstMedias[eType].InputBufInfo[0][0] = 0;
    _gstMedias[eType].InputBufInfo[0][1] = 0;
    _gstMedias[eType].InputBufInfo[0][2] = 0;
    _gstMedias[eType].InputBufInfo[1][0] = 0;
    _gstMedias[eType].InputBufInfo[1][1] = 0;
    _gstMedias[eType].InputBufInfo[1][2] = 0;
    _gstMedias[eType].bFileEnd = FALSE;
    _gstMedias[eType].bNeedResetBuf = TRUE;
    _gstMedias[eType].u64StreamPos = MApp_DigitalMedia_DataStream_Tell(Hdl_EnableDoubleBuf);
    _gstMedias[eType].Hdl_EnableDoubleBuf = Hdl_EnableDoubleBuf;

    if (_gstMedias[eType].pfnNotify != NULL)
    {
//        _gstMedias[eType].bEnableDoubleBuf = TRUE;

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static void _MApp_DigitalMedia_Reset_DoubleBuf(E_DM_STRM_TYPE eType)
{
    if(INVALID_STRM_TYPE(eType))
    {
        return;
    }

    DIGITALMEDIA_DBG(printf("reset double buffer.\n");)

    _gstMedias[eType].CurrentBufIndex = 0;
    _gstMedias[eType].InputBufInfo[0][0] = 0;
    _gstMedias[eType].InputBufInfo[0][1] = 0;
    _gstMedias[eType].InputBufInfo[0][2] = 0;
    _gstMedias[eType].InputBufInfo[1][0] = 0;
    _gstMedias[eType].InputBufInfo[1][1] = 0;
    _gstMedias[eType].InputBufInfo[1][2] = 0;
    _gstMedias[eType].bNeedResetBuf = TRUE;
    _gstMedias[eType].bFileEnd = FALSE;
}

//return unread;
static U32 _MApp_DigitalMedia_Read_DoubleBuf(E_DM_STRM_TYPE eType, U8* pdata, U32 u32length)
{
    U32 dataReadCount = 0;
    U8 idx;

    DIGITALMEDIA_DBG(printf("read doublebuff %d\n",u32length);)

    if(_gstMedias[eType].bNeedResetBuf)
    {
        idx = 0;
        DIGITALMEDIA_DBG(printf("first notify buf indx:%d empty\n",idx);)
        SEND_EVENT_NOTIFICATION(eType, E_DM_EVENT_BUFFER_EMPTY, (U32)(&idx), 1);
        idx = 1;
        DIGITALMEDIA_DBG(printf("first notify buf indx:%d empty\n",idx);)
        SEND_EVENT_NOTIFICATION(eType, E_DM_EVENT_BUFFER_EMPTY, (U32)(&idx), 1);

        #if 0
        if (_gstMedias[eType].fnCallbacks.pfnRead)//test
        {
            U32 u32UnRead;

                E_DM_STRM_IO_ERR eIoErr;

                u32UnRead = _gstMedias[eType].fnCallbacks.pfnRead(_gstMedias[eType].Hdl_EnableDoubleBuf, (void*)(_gstMedias[eType].u32DoubleBufAddr+idx*_gstMedias[eType].u32DoubleBufSize/2), (U32)_gstMedias[eType].u32DoubleBufSize/2, &eIoErr);
                if(u32UnRead!=0)
                    _gstMedias[eType].bFileEnd = TRUE;
                MApp_DigitalMedia_Fill_DoubleBufDone(eType,idx,(_gstMedias[eType].u32DoubleBufSize/2 - u32UnRead),_gstMedias[eType].bFileEnd);
                if(!_gstMedias[eType].bFileEnd)
                {
                idx = 1;
                u32UnRead = _gstMedias[eType].fnCallbacks.pfnRead(_gstMedias[eType].Hdl_EnableDoubleBuf, (void*)(_gstMedias[eType].u32DoubleBufAddr+idx*_gstMedias[eType].u32DoubleBufSize/2), (U32)_gstMedias[eType].u32DoubleBufSize/2, &eIoErr);
                if(u32UnRead!=0)
                    _gstMedias[eType].bFileEnd = TRUE;
                MApp_DigitalMedia_Fill_DoubleBufDone(eType,idx,(_gstMedias[eType].u32DoubleBufSize/2 - u32UnRead),_gstMedias[eType].bFileEnd);
                }
        }
        #endif

        _gstMedias[eType].bNeedResetBuf = FALSE;
    }

    while (dataReadCount < u32length)
    {
        U16 i = 0;

        while (!_gstMedias[eType].InputBufInfo[_gstMedias[eType].CurrentBufIndex][0])
        {
            i++;

            MsOS_DelayTask(10);
            if (i == 1000)
            {
                printf("read  double buffer time out.\n");
                return (U32)(u32length - (U16)dataReadCount);
            }
        }

        idx = _gstMedias[eType].CurrentBufIndex;
        DIGITALMEDIA_DBG(printf("idx:%d, addr:%x,len:%d,read offset:%d\n", idx, _gstMedias[eType].InputBufInfo[idx][0],_gstMedias[eType].InputBufInfo[idx][1],_gstMedias[eType].InputBufInfo[idx][2]);)
        if ((_gstMedias[eType].InputBufInfo[idx][1] - _gstMedias[eType].InputBufInfo[idx][2]) >= (u32length - dataReadCount))
        {
            //memcpy((void *)_PA2VA((U32)pdata + dataReadCount), (void *)_PA2VA(_gstMedias[eType].InputBufInfo[idx][0] + _gstMedias[eType].InputBufInfo[idx][2]), u32length - dataReadCount);
            MApi_BDMA_Copy( (_gstMedias[eType].InputBufInfo[idx][0] + _gstMedias[eType].InputBufInfo[idx][2]), (U32)(pdata + dataReadCount),u32length - dataReadCount,MIU_SDRAM2SDRAM);
            DIGITALMEDIA_DBG(printf("1 read bufid:%d size:%d\n",idx,u32length-dataReadCount);)
            _gstMedias[eType].InputBufInfo[idx][2] += (u32length - dataReadCount);
            dataReadCount = u32length;
        }
        else if( _gstMedias[eType].InputBufInfo[idx][1] > _gstMedias[eType].InputBufInfo[idx][2])
        {
            //memcpy((void *)_PA2VA((U32)pdata + dataReadCount), (void *)_PA2VA(_gstMedias[eType].InputBufInfo[idx][0] + _gstMedias[eType].InputBufInfo[idx][2]), _gstMedias[eType].InputBufInfo[idx][1] - _gstMedias[eType].InputBufInfo[idx][2]);
            MApi_BDMA_Copy((_gstMedias[eType].InputBufInfo[idx][0] + _gstMedias[eType].InputBufInfo[idx][2]), (U32)(pdata + dataReadCount), _gstMedias[eType].InputBufInfo[idx][1] - _gstMedias[eType].InputBufInfo[idx][2],MIU_SDRAM2SDRAM);
            DIGITALMEDIA_DBG(printf("2 read bufid:%d size:%d\n",idx,_gstMedias[eType].InputBufInfo[idx][1] - _gstMedias[eType].InputBufInfo[idx][2]);)
            dataReadCount+=(_gstMedias[eType].InputBufInfo[idx][1] - _gstMedias[eType].InputBufInfo[idx][2]);
            _gstMedias[eType].InputBufInfo[idx][2] = _gstMedias[eType].InputBufInfo[idx][1];
        }

        if(_gstMedias[eType].bFileEnd)
            return (U32)(u32length - (U16)dataReadCount);

        if (_gstMedias[eType].InputBufInfo[idx][2] == _gstMedias[eType].InputBufInfo[idx][1])
        {
            _gstMedias[eType].InputBufInfo[idx][0] = 0;
            _gstMedias[eType].CurrentBufIndex =(idx+1)%2;
            DIGITALMEDIA_DBG(printf("notify buf indx:%d empty\n",idx);)
            SEND_EVENT_NOTIFICATION(eType, E_DM_EVENT_BUFFER_EMPTY, (U32)(&idx), 1);

            #if 0
            //test
            if (_gstMedias[eType].fnCallbacks.pfnRead)//test
            {
                U32 u32UnRead;

                E_DM_STRM_IO_ERR eIoErr;

                u32UnRead = _gstMedias[eType].fnCallbacks.pfnRead((DM_STRM_HDL)_gstMedias[eType].Hdl_EnableDoubleBuf, (void*)(_gstMedias[eType].u32DoubleBufAddr+idx*_gstMedias[eType].u32DoubleBufSize/2), (U32)_gstMedias[eType].u32DoubleBufSize/2, &eIoErr);
                if(u32UnRead!=0)
                    _gstMedias[eType].bFileEnd = TRUE;
                MApp_DigitalMedia_Fill_DoubleBufDone(eType,idx,(_gstMedias[eType].u32DoubleBufSize/2 - u32UnRead),_gstMedias[eType].bFileEnd);
            }
            #endif

        }
    }

    return 0;
}

BOOLEAN MApp_DigitalMedia_Get_DoubleBufInfo(E_DM_STRM_TYPE eType, U32* pu32DoubleBuffAddr, U32* pu32DoubleBufSize)
{
    if(INVALID_STRM_TYPE(eType))
    {
        return FALSE;
    }

    *pu32DoubleBuffAddr = _gstMedias[eType].u32DoubleBufAddr;
    *pu32DoubleBufSize = _gstMedias[eType].u32DoubleBufSize;

    return TRUE;
}

void MApp_DigitalMedia_Fill_DoubleBufDone(E_DM_STRM_TYPE eType, U8 u8BufIndex, U32 u32Len, BOOLEAN bFileEnd)
{
    if(INVALID_STRM_TYPE(eType) || u8BufIndex >1)
    {
        return;
    }

    DIGITALMEDIA_DBG(printf("fill buf done index:%d ,len :%d\n",u8BufIndex,u32Len);)
    if(_gstMedias[eType].InputBufInfo[u8BufIndex][0] == 0)
    {
        _gstMedias[eType].InputBufInfo[u8BufIndex][0] = (_gstMedias[eType].u32DoubleBufAddr+u8BufIndex*_gstMedias[eType].u32DoubleBufSize/2);
        _gstMedias[eType].InputBufInfo[u8BufIndex][1] = u32Len;
        _gstMedias[eType].InputBufInfo[u8BufIndex][2] = 0;
        _gstMedias[eType].bFileEnd = bFileEnd;
    }
    else
    {
        DIGITALMEDIA_DBG(printf("ERROR:not finish read in buffer index:%d\n",u8BufIndex);)
    }
}
#endif //#if (ENABLE_DIGITAL_MEDIA_API)

#undef _MAPP_DIGITAL_MEDIA_C_


