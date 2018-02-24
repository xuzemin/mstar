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
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
/// @file msAPI_Video.h
/// @brief API for Digital Video
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////

#define MSAPI_VIDEO_C

/******************************************************************************/
/*                    Header Files                                            */
/* ****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "Board.h"

#include "MsCommon.h"
#include "datatype.h"
#include "debug.h"
#include "sysinfo.h"


//#include "drvGlobal.h"
#include "drvMIU.h"

#include "apiDMX.h"
#include "apiAUDIO.h"
#include "apiXC.h"
#include "apiVDEC.h"

#include "msAPI_Global.h"
#include "msAPI_MIU.h"
#include "msAPI_Timer.h"

// Common Definition
#include "msAPI_Video.h"

#if (ENABLE_DYNAMIC_H264_FW_LOADING || ENABLE_DYNAMIC_MVD_FW_LOADING)
#include "BinInfo.h"
#include "InfoBlock.h"
void MDrv_Sys_Get_BinInfo(BININFO *pBinInfo, BOOLEAN *pbResult);
#endif


#include "msAPI_BDMA.h"


#if ENABLE_AUTOTEST
extern BOOLEAN g_bAutobuildDebug;
#endif

#if ENABLE_VDEC_INFO_MONITOR
MS_U32 u32decodemonitortimer=0;
MS_BOOL gbsyncreach=FALSE;
#endif


#if( CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA)

    #define DTV_MPEG2_FBL_MODE_THRESHOLD        (1920UL*1088UL)
    #define DTV_H264_FBL_MODE_THRESHOLD         (1920UL*1088UL)
    #define DTV_OTHER_CODEC_FBL_MODE_THRESHOLD  (1920UL*1088UL)

#else

  #if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)    \
   /*||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) */  \
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER)  \
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD)\
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA)   \
   )

    #define DTV_MPEG2_FBL_MODE_THRESHOLD    (1280*720)

  #else // EDEN/MAYA/Marlon

    #define DTV_MPEG2_FBL_MODE_THRESHOLD    (1920UL*1088UL)

  #endif

    #define DTV_H264_FBL_MODE_THRESHOLD         (1800UL*1000UL)

    #define DTV_OTHER_CODEC_FBL_MODE_THRESHOLD  (1280*720)

#endif


#define _ENABLE_VDEC_DEBUG_LOG_         0
/******************************************************************************/
/*                     Local                                                  */
/* ****************************************************************************/
static U8 u8SyncEnable                      = 1;

#if (ENABLE_DMP || ENABLE_PVR)
static VDEC_TrickDec eTrickDec;
static U8 u8DisplayDuration                 = 1;
#endif

static U8 u8PlayMode                        = MSAPI_VID_STOP;

static U32 _u32PrevWP;
static U32 _u32VdecBsBufLen                 = VDEC_AEON_LEN;

static code U16 _H264_ASPECT_RATIO[17][2]   = {{1,1},
                                               {1,1},
                                               {12,11},
                                               {10,11},
                                               {16,11},
                                               {40,33},
                                               {24,11},
                                               {20,11},
                                               {32,11},
                                               {80,33},
                                               {18,11},
                                               {15,11},
                                               {64,33},
                                               {160,99},
                                               {4,3},
                                               {3,2},
                                               {2,1}};

/******************************************************************************/
/*                   Functions                                                */
/******************************************************************************/

static U32 g_VDEC_u32Dtv_SD_FrameBufSize = 0;

void _msAPI_VID_SetMemoryLayout(VDEC_InitParam *pInitParam)
{
#ifdef VDEC_AEON_DTV_ADR
    //pInitParam->SysConfig.u32CodeBufAddr = VDEC_AEON_DTV_ADR;
    pInitParam->SysConfig.u32CodeBufAddr = ((VDEC_AEON_DTV_MEMORY_TYPE & MIU1) ? (VDEC_AEON_DTV_ADR|MIU_INTERVAL) : (VDEC_AEON_DTV_ADR));
    pInitParam->SysConfig.u32CodeBufSize = VDEC_AEON_DTV_LEN;
#else
    //pInitParam->SysConfig.u32CodeBufAddr = VDEC_AEON_ADR;
    pInitParam->SysConfig.u32CodeBufAddr = ((VDEC_AEON_MEMORY_TYPE & MIU1) ? (VDEC_AEON_ADR|MIU_INTERVAL) : (VDEC_AEON_ADR));
    pInitParam->SysConfig.u32CodeBufSize = VDEC_AEON_LEN;
#endif

#if( defined(VDEC_FRAMEBUFFER_DTV_ADR) )
    //pInitParam->SysConfig.u32FrameBufAddr = VDEC_FRAMEBUFFER_DTV_ADR;
    pInitParam->SysConfig.u32FrameBufAddr = ((VDEC_FRAMEBUFFER_DTV_MEMORY_TYPE & MIU1) ? (VDEC_FRAMEBUFFER_DTV_ADR|MIU_INTERVAL) : (VDEC_FRAMEBUFFER_DTV_ADR));
    pInitParam->SysConfig.u32FrameBufSize = VDEC_FRAMEBUFFER_DTV_LEN;
#else
    //pInitParam->SysConfig.u32FrameBufAddr = VDEC_FRAMEBUFFER_ADR;
    pInitParam->SysConfig.u32FrameBufAddr = ((VDEC_FRAMEBUFFER_MEMORY_TYPE & MIU1) ? (VDEC_FRAMEBUFFER_ADR|MIU_INTERVAL) : (VDEC_FRAMEBUFFER_ADR));
    pInitParam->SysConfig.u32FrameBufSize = VDEC_FRAMEBUFFER_LEN;
#endif

    g_VDEC_u32Dtv_SD_FrameBufSize = pInitParam->SysConfig.u32FrameBufSize;

#if( defined(VDEC_FRAMEBUFFER_DTV_SD_ADR) )

    g_VDEC_u32Dtv_SD_FrameBufSize = VDEC_FRAMEBUFFER_DTV_SD_LEN;

  #if 0//(VDEC_FRAMEBUFFER_DTV_SD_LEN != 0)
    if ((pInitParam->eCodecType == E_VDEC_CODEC_TYPE_MPEG2) ||(pInitParam->eCodecType == E_VDEC_CODEC_TYPE_VC1_ADV))
    {
        pInitParam->SysConfig.u32FrameBufAddr = VDEC_FRAMEBUFFER_DTV_SD_ADR;
        pInitParam->SysConfig.u32FrameBufSize = VDEC_FRAMEBUFFER_DTV_SD_LEN;
    }
  #endif

#elif( defined(VDEC_FRAMEBUFFER_SD_ADR) )

    g_VDEC_u32Dtv_SD_FrameBufSize = VDEC_FRAMEBUFFER_SD_LEN;

#endif

#ifdef VDEC_BITSTREAM_DTV_LEN
    //pInitParam->SysConfig.u32BitstreamBufAddr = VDEC_BITSTREAM_DTV_ADR;
    pInitParam->SysConfig.u32BitstreamBufAddr = ((VDEC_BITSTREAM_DTV_MEMORY_TYPE & MIU1) ? (VDEC_BITSTREAM_DTV_ADR|MIU_INTERVAL) : (VDEC_BITSTREAM_DTV_ADR));
    pInitParam->SysConfig.u32BitstreamBufSize = VDEC_BITSTREAM_DTV_LEN;
#else
    //pInitParam->SysConfig.u32BitstreamBufAddr = VDEC_BITSTREAM_ADR;
    pInitParam->SysConfig.u32BitstreamBufAddr = ((VDEC_BITSTREAM_MEMORY_TYPE & MIU1) ? (VDEC_BITSTREAM_ADR|MIU_INTERVAL) : (VDEC_BITSTREAM_ADR));
    pInitParam->SysConfig.u32BitstreamBufSize = VDEC_BITSTREAM_LEN;
#endif

#if (ENABLE_MIU_1)
    pInitParam->SysConfig.u32DrvProcBufAddr = pInitParam->SysConfig.u32BitstreamBufAddr;
    pInitParam->SysConfig.u32DrvProcBufSize = 0xA000;
#endif

}

U32 msAPI_VID_GetESWriteCnt(void)
{
    U32 cnt = 0;
    MS_U32 ptr = MApi_VDEC_GetESWritePtr();

    if (_u32PrevWP < ptr)
    {
        cnt = ptr - _u32PrevWP;
    }
    else
    {
        cnt = _u32VdecBsBufLen - (_u32PrevWP - ptr);
    }

    _u32PrevWP = ptr;

    return cnt;
}

//******************************************************************************
/// issue Video command
/// @param u8VIDCommand \b IN
///   - # MSAPI_VID_PLAY play command
///   - # MSAPI_VID_PAUSE pause command
///   - # MSAPI_VID_STOP stop command
///   - # MSAPI_VID_RESET reset command
///   - # MSAPI_VID_FREERUN disable video-sync command
//******************************************************************************
void msAPI_VID_Command(U8 u8VIDcommand)
{
    static VDEC_CodecType s_LastVDEC_CodecType = E_VDEC_CODEC_TYPE_NONE;
    if((u8VIDcommand == MSAPI_VID_PLAY) && (u8PlayMode == MSAPI_VID_PLAY) && (s_LastVDEC_CodecType == msAPI_VID_GetCodecType()))
    {
        return;
    }
    u8PlayMode = u8VIDcommand;
    s_LastVDEC_CodecType = msAPI_VID_GetCodecType();

    VDEC_Result ret = E_VDEC_FAIL;

    switch (u8VIDcommand)
    {
        case MSAPI_VID_PLAY:
            ret = MApi_VDEC_Play();
            SwitchChannelTimePrintf("[SwitchChannelTime]MApi_VDEC_Play() --- %ld\n");
            if( E_VDEC_OK != ret )
            {
               MS_DEBUG_MSG(printf("msAPI_VID_Command(0x%x) not success! ret = %d\n", u8VIDcommand, ret));
            }
            // Must Call AVSyncOn to do AV syyc
            //ret = MApi_VDEC_AVSyncOn(TRUE,0,0);
            ret = MApi_VDEC_AVSyncOn(TRUE,180,0);       //sync offset will influence DTV lip-sync
                                                        //If you want to change sync offset, please info Audio team and Video team

            if ( s_LastVDEC_CodecType == E_VDEC_CODEC_TYPE_MPEG2 )
                MApi_VDEC_SetAVSyncFreerunThreshold(5000*90);           //5 sec for video AV sync time out

            break;

        case MSAPI_VID_RESUME:
            ret = MApi_VDEC_Resume();
            u8SyncEnable = 1;

            break;

        case MSAPI_VID_PAUSE:
            ret = MApi_VDEC_Pause();

            break;

        case MSAPI_VID_STOP:
            ret = MApi_VDEC_Exit();

            if (E_VDEC_RET_NOT_INIT == ret) // already stopped, fine to return success
            {
                return;
            }

            break;

        case MSAPI_VID_RESET:
            ret = MApi_VDEC_Rst();

            break;

        case MSAPI_VID_FREERUN:
            ret = MApi_VDEC_AVSyncOn(FALSE, 0, 0);
            u8SyncEnable = 0;

            break;

#if ENABLE_DMP
        case MSAPI_VID_TRICK_PLAY:
            ret = MApi_VDEC_SetTrickMode(eTrickDec);
            u8SyncEnable = 0;

            break;

        case MSAPI_VID_STEP_PLAY:
            ret = MApi_VDEC_StepDisp();
            u8SyncEnable = 0;

            break;

        case MSAPI_VID_PLAY_EXTENSION:
            ret = MApi_VDEC_Play();
            u8SyncEnable = 1;

            break;
#endif  // #if ENABLE_DMP

        case MSAPI_VID_STEP_PLAY_EXTENSION:
            ret = MApi_VDEC_StepDisp();
            u8SyncEnable = 0;

            break;

        default:
            break;
    }

    if (E_VDEC_OK != ret)
    {
        MS_DEBUG_MSG(printf("msAPI_VID_Command(0x%x) not success! ret = %d\n", u8VIDcommand, ret));
    }
}

#if (ENABLE_DMP || ENABLE_PVR)
//******************************************************************************
//Function name:    msAPI_VID_SetTrickModeInfo
//Passing parameter:    U8 u8DecodeType
//                      U8 u8FrameDuration
//Return parameter:     none
//Description:  set MVD command
//  [Doxygen]
/// API for set MVD command
/// @param u8MVDCommand \b IN MVD command, e.g., PLAY, PAUSE, STOP, CHANNEL_CHANGE, RESET
//******************************************************************************
void msAPI_VID_SetTrickModeInfo(U8 u8DecodeType, U8 u8FrameDuration)
{
    SHOW_VIDEO_INFO(("msAPI_VID_SetTrickModeInfo,%d,%d",u8DecodeType,u8FrameDuration));
    u8DisplayDuration = u8FrameDuration;

//    if (bAVCH264)

    if( (msAPI_VID_GetCodecType() == E_VDEC_CODEC_TYPE_H264)
    #if ( CHIP_SUPPORT_HEVC ) // IMPLEMENT_DTV_H265
       ||(msAPI_VID_GetCodecType() == E_VDEC_CODEC_TYPE_HEVC)
    #endif
      )
    {
        if (u8DecodeType == 0)
        {
            eTrickDec = E_VDEC_TRICK_DEC_ALL;
        }
        else if (u8DecodeType == 1)
        {
            eTrickDec = E_VDEC_TRICK_DEC_I;
        }
        else if (u8DecodeType == 2)
        {
            eTrickDec = E_VDEC_TRICK_DEC_IP;
        }
        else
        {
            MS_DEBUG_MSG(printf("dec type %d is undefined\n", u8DecodeType));
        }
    }
    else
    {
        if (u8DecodeType == 0)
        {
            eTrickDec = E_VDEC_TRICK_DEC_ALL;
        }
        else if (u8DecodeType == 1)
        {
            eTrickDec = E_VDEC_TRICK_DEC_IP;
        }
        else if (u8DecodeType == 2)
        {
            eTrickDec = E_VDEC_TRICK_DEC_I;
        }
        else
        {
            MS_DEBUG_MSG(printf("dec type %d is undefined\n", u8DecodeType));
        }
    }
}
#endif // #if ENABLE_DMP

//*************************************************************************
/// get MVD current play status
/// @return
///   - # MSAPI_VID_PLAY, MSAPI_VID_PAUSE, MSAPI_VID_STOP, MSAPI_VID_RESET, MSAPI_VID_FREERUN
//*************************************************************************
U8 msAPI_VID_GetPlayMode(void)
{
    return u8PlayMode;
}

//*************************************************************************
/// get if MVD video sync is enable
/// @return
///   - # TRUE video-sync is enable
///   - # FALSE otherwise
//*************************************************************************
U8 msAPI_VID_IsSyncEnable()
{
    return u8SyncEnable;
}

//******************************************************************************
/// get video information from MPEG2 video header
/// @param pstVidStatus \b OUT information about progressive/interlace, resolution, framerate, aspect ratio
/// @return
///   - # TRUE video header has no problem
///   - # FALSE otherwise
//******************************************************************************
BOOLEAN msAPI_VID_GetVidInfo(VDEC_DispInfo *pstVidStatus)
{
    VDEC_DispInfo   info;
    VDEC_Result     ret;

//    SHOW_VIDEO_INFO(("msAPI_VID_GetVidInfo"));

    if (msAPI_VID_GetCodecType() == E_VDEC_CODEC_TYPE_MPEG2)
    {
        if (E_VDEC_OK != MApi_VDEC_IsWithValidStream()) /*--- check valid mpeg ---*/
        {
           return FALSE;
        }
    }

    memset(&info, 0, sizeof(VDEC_DispInfo));
    ret = MApi_VDEC_GetDispInfo(&info);

    if (E_VDEC_OK != ret)
    {
        return FALSE;
    }
    else
    {
        pstVidStatus->u16HorSize    = info.u16HorSize;
        pstVidStatus->u16VerSize    = info.u16VerSize;
        pstVidStatus->u32FrameRate  = info.u32FrameRate;
        pstVidStatus->u8AspectRate  = info.u8AspectRate;
        pstVidStatus->u8Interlace   = info.u8Interlace;
        pstVidStatus->u16SarWidth   = info.u16SarWidth;
        pstVidStatus->u16SarHeight  = info.u16SarHeight;
        pstVidStatus->u16CropRight  = info.u16CropRight;
        pstVidStatus->u16CropLeft   = info.u16CropLeft;
        pstVidStatus->u16CropBottom = info.u16CropBottom;
        pstVidStatus->u16CropTop    = info.u16CropTop;
        pstVidStatus->bWithChroma    = info.bWithChroma;

        if(msAPI_VID_GetCodecType() == E_VDEC_CODEC_TYPE_MPEG2)
        {
            pstVidStatus->u8AFD         = info.u8AFD;
            pstVidStatus->u16Pitch      = info.u16Pitch;
            pstVidStatus->u16PTSInterval = info.u16PTSInterval;
            pstVidStatus->u8MPEG1       = info.u8MPEG1;
            pstVidStatus->u8PlayMode    = info.u8PlayMode;
            pstVidStatus->u8FrcMode     = info.u8FrcMode;

            if (pstVidStatus->u32FrameRate == 0
#if AUTO_ASPECT_RATIO
                ||
                pstVidStatus->u8AspectRate == FORBIDDEN ||
                pstVidStatus->u8AspectRate >= ASP_MAXNUM
#endif
                ||
                pstVidStatus->u16HorSize == 0 ||
                pstVidStatus->u16HorSize > 2000 ||
                pstVidStatus->u16VerSize == 0 ||
                pstVidStatus->u16VerSize > 1100)
            {
                return FALSE;
            }
//            pstVidStatus->u8AFD = msAPI_VID_GetActiveFormat();
            pstVidStatus->u8AFD = MApi_VDEC_GetActiveFormat();
            return TRUE;
        }
    }
    return TRUE;
}

void msAPI_VID_SetMappingAVCParameter(VDEC_CodecType eVDEC_CodecType)
{
    SHOW_VIDEO_INFO(("msAPI_VID_SetMappingAVCParameter eVDEC_CodecType=%d",eVDEC_CodecType));
    g_eCodecType = eVDEC_CodecType;
    msAPI_VID_SetCodecType(eVDEC_CodecType);
}

void msAPI_VID_SetCodecType(VDEC_CodecType eVDEC_CodecType)
{
    geVDEC_CodecType = eVDEC_CodecType;
}

VDEC_CodecType msAPI_VID_GetCodecType(void)
{
    return geVDEC_CodecType;
}


#if _ENABLE_VDEC_DEBUG_LOG_
static void _VdecCB(MS_U32 u32Event, void *param)
{
    //printf("[_VdecCB]");
    param = param;
    if (u32Event & E_VDEC_EVENT_DISP_ONE)
    {
        MS_U32 u32stc32, u32stc;
        MApi_DMX_Stc_Get(&u32stc32, &u32stc);
        printf("S:%ld P:%ld D:%ld, AD:%ld, E:%ld\n",
            (u32stc / 90)%10000,
            (MApi_VDEC_GetPTS())%10000,
            (MS_S32)(MApi_VDEC_GetVideoPtsStcDelta() / 90),     (MS_S32)(MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_ADEC1_33bit_STCPTS_DIFF) & 0xFFFFFFFF) / 90,
            MApi_VDEC_GetErrCnt());
    }
}
#endif


#define DEBUG_VID_INIT(x)   //x

U16 msAPI_VID_Get_VdecBinId(VDEC_CodecType eCodecType)
{
    U16 u16BinId = 0;

    DEBUG_VID_INIT( printf("msAPI_VID_Get_VdecBinId(eCodecType=%u)\n", eCodecType); );

#if( VDEC_BIN_IS_FW_VPU ) // Milan/Mulan/Maya
    UNUSED(eCodecType);
    u16BinId = BIN_ID_CODE_VDEC_FW_VPU;
#else
    {
        switch(eCodecType)
        {
        #if( CHIP_SUPPORT_HEVC )
            case E_VDEC_CODEC_TYPE_HEVC:

            #if (CHIP_FAMILY_TYPE==CHIP_FAMILY_MELODY) // Melody ISDB DTV USE
                u16BinId = BIN_ID_MM_EVD;

            #elif( (CHIP_FAMILY_TYPE==CHIP_FAMILY_NASA)   \
                 ||(CHIP_FAMILY_TYPE==CHIP_FAMILY_WHISKY) \
                 )
                u16BinId = BIN_ID_CODE_AEON_H265;

            #else

                u16BinId = BIN_ID_CODE_AEON_H264;
            #endif
                break;
        #endif

            case E_VDEC_CODEC_TYPE_H264:
            case E_VDEC_CODEC_TYPE_AVS:
            #if (CHIP_FAMILY_TYPE==CHIP_FAMILY_MELODY) // Melody ISDB DTV USE
                {
                    u16BinId = BIN_ID_MM_HVD;
                }
            #else
                {
                    u16BinId = BIN_ID_CODE_AEON_H264;
                }
            #endif
                break;

            default:
            case E_VDEC_CODEC_TYPE_MPEG2:
            case E_VDEC_CODEC_TYPE_VC1_ADV:
            #if (CHIP_FAMILY_TYPE==CHIP_FAMILY_MELODY) // Melody ISDB DTV USE
                {
                    u16BinId = BIN_ID_MM_MVD;
                }
            #else
                {
                    u16BinId = BIN_ID_CODE_AEON_MVD;
                }
            #endif
                break;
        }
    }
#endif

    DEBUG_VID_INIT( printf(" => u16BinId=0x%X\n", u16BinId); );

    return u16BinId;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief
///         Initial Video codec
/// @par [In] eCodecType:input codec type
///         [In] bEnableDropErrFrame: Does enable drop error frame
/// @ret TRUE:success
///         FALSE: fail
////////////////////////////////////////////////////////////////////////////////

#define ENABLE_MIU_PROTECT_VDEC_AEON    0

BOOLEAN msAPI_VID_Init(BOOLEAN bEnableDropErrFrame, VDEC_SrcMode enSrcMode)
{
    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_START());

    VDEC_InitParam initParam;

    //PRINT_CURRENT_LINE();
    DEBUG_VID_INIT( printf("msAPI_VID_Init(bEnableDropErrFrame=%u, enSrcMode=%u)\n", bEnableDropErrFrame, enSrcMode); );
    SHOW_VIDEO_INFO(("msAPI_VID_Init bEnableDropErrFrame=%d codec=%d",bEnableDropErrFrame,msAPI_VID_GetCodecType()));


#if (ENABLE_AUTOTEST || ENABLE_BOOTTIME)
  #if (ENABLE_BOOTTIME==DISABLE)
    if (g_bAutobuildDebug == TRUE)
  #endif
    {
        gU32TmpTime = msAPI_Timer_DiffTimeFromNow(gU32BootTime);
        MS_DEBUG_MSG(printf("[TIME] Initial Video codec = %ld\n", gU32TmpTime));
    }
#endif


    MApi_XC_set_FD_Mask(FALSE);//Disable FD mask


    VDEC_Status vdecStatus;
    memset(&vdecStatus, 0, sizeof(VDEC_Status));
    MS_BOOL bRet = MApi_VDEC_GetStatus(&vdecStatus);
    if( bRet == TRUE && vdecStatus.bInit == TRUE ) // msAPI_VID_Init run once only
    {
        PRINT_CURRENT_LINE();
        printf("\nWarning: Skip init vdec!\n");
        return TRUE;
    }

#if ENABLE_VDEC_INFO_MONITOR
    u32decodemonitortimer = 0;
    gbsyncreach=FALSE;
#endif

    memset(&initParam, 0, sizeof(VDEC_InitParam));
    initParam.bDisableDropErrFrame = (!bEnableDropErrFrame);
    initParam.eCodecType = msAPI_VID_GetCodecType();
    initParam.VideoInfo.eSrcMode = enSrcMode ;//E_VDEC_SRC_MODE_DTV;
    DEBUG_VID_INIT( printf(" eCodecType=%u\n", initParam.eCodecType); );


    // Setup aeon/bitstream/framebuffer memory range
    _msAPI_VID_SetMemoryLayout(&initParam);

    BININFO BinInfo;
    BOOLEAN bResult;

#if ENABLE_MIU_PROTECT_VDEC_AEON // Protect VDEC-aeon buffer
    {
        U8 au8ProtectIds_2[4] = {0, 0, 0 };
        msAPI_MIU_Set_MiuProtect(2, au8ProtectIds_2, 0, 0,
            DISABLE);
    }
#endif

    // Get correct bin id by codec type
    BinInfo.B_ID = msAPI_VID_Get_VdecBinId(initParam.eCodecType);

    // Check if bin exist
    MDrv_Sys_Get_BinInfo(&BinInfo, &bResult);
    if (bResult != PASS)
    {
        printf("\nError: Fail to find VDEC bin=0x%X on flash.\n", BinInfo.B_ID);
        return FALSE;
    }

    switch( BinInfo.B_IsComp )
    {
        case LZSS_COMPRESS:
        case MS_COMPRESS:
        case MS_COMPRESS7:
          {
            U32 u32DstVA = _PA2VA( (initParam.SysConfig.u32FrameBufAddr) );
            U32 u32DecVA = u32DstVA + BUF_FOR_VDEC_DECOMPRESS_OFFSET1;
            U32 u32TmpVA = u32DstVA + BUF_FOR_VDEC_DECOMPRESS_OFFSET2;

            // Decompress bin to dram
            if( FAILURE == MDrv_DMA_LoadBin(&BinInfo, u32DstVA, u32DecVA, u32TmpVA) )
            {
                printf("\nError: Decomp vdec bin failed!\n");
                return FALSE;
            }

            initParam.SysConfig.eFWSourceType = E_VDEC_FW_SOURCE_DRAM;
            initParam.SysConfig.u32FWBinaryAddr = initParam.SysConfig.u32FrameBufAddr;
            //initParam.SysConfig.u32FWBinarySize = 109720;
            initParam.SysConfig.u32FWBinarySize = BinInfo.B_Len;

            MsOS_FlushMemory();
          }
            break;

        default:
            //printf("~~2~~  NO COMPRESS\n");
            // No need copy bin to dram by app, driver will do it
            initParam.SysConfig.eFWSourceType = E_VDEC_FW_SOURCE_FLASH;
            initParam.SysConfig.u32FWBinaryAddr = BinInfo.B_FAddr;
            initParam.SysConfig.u32FWBinarySize = BinInfo.B_Len;
        break;
    }

#if ENABLE_VDEC_INFO_MONITOR
    initParam.SysConfig.eDbgMsgLevel = E_VDEC_DBG_LEVEL_DBG;
#else
    initParam.SysConfig.eDbgMsgLevel = E_VDEC_DBG_LEVEL_ERR;
#endif


#if 0
    printf("VDEC FW add = 0x%lx\n", initParam.SysConfig.u32CodeBufAddr);
    printf("VDEC FB add = 0x%lx\n", initParam.SysConfig.u32FrameBufAddr);
    printf("VDEC FB size = 0x%lx\n", initParam.SysConfig.u32FrameBufSize);
    printf("VDEC BS add = 0x%lx\n", initParam.SysConfig.u32BitstreamBufAddr);
#endif


    BOOLEAN bForceMvopOutInterlace = FALSE;

#if( CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA )
    if( (initParam.eCodecType == E_VDEC_CODEC_TYPE_AVS) ) // For special stream issue
    {
        bForceMvopOutInterlace = TRUE;
    }

#elif( CHIP_FAMILY_TYPE==CHIP_FAMILY_MAYA )

     if( (initParam.eCodecType != E_VDEC_CODEC_TYPE_HEVC)
      && (initParam.eCodecType != E_VDEC_CODEC_TYPE_AVS) ) // not do force interlace!!
    {
        bForceMvopOutInterlace = TRUE;
    }

#else

  #if(ENABLE_NZ_FREEVIEW) // For special stream will i/p switch, and can't mute screen
   #if ( CHIP_SUPPORT_HEVC )
    if( (initParam.eCodecType != E_VDEC_CODEC_TYPE_HEVC) )
   #endif
    {
        bForceMvopOutInterlace = TRUE;
    }
  #endif

#endif

    if( bForceMvopOutInterlace )
    {
        MApi_VDEC_PreSetControl(VDEC_USER_CMD_FORCE_INTERLACE_MODE, 1);
    }

#if( !ENABLE_VDEC_2_0 )
    if (IsATVInUse())
    {
        MApi_VDEC_PreSetControl(VDEC_USER_CMD_MVD_HWBUFFER_REMAPPING_MODE, 1);
    }
#endif

    VDEC_Result ret = MApi_VDEC_Init(&initParam);
    if (E_VDEC_OK != ret)
    {
        printf("\nError: MApi_VDEC_Init() fail!\n");
        return FALSE;
    }
    SwitchChannelTimePrintf("[SwitchChannelTime]MApi_VDEC_Init() --- %ld\n");

  #if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)  \
    || (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) \
     )
    // Set default frame rate: If can't get fram rate from stream, it will use the default value in driver
    MApi_VDEC_SetControl(VDEC_USER_CMD_FRAMERATE_HANDLING, 30000);
  #endif

  #if _ENABLE_VDEC_DEBUG_LOG_
    MApi_VDEC_SetEvent(E_VDEC_EVENT_DISP_ONE, _VdecCB, NULL);
  #endif

#if( ENABLE_VDEC_2_0 )
/*
  #if( CHIP_SUPPORT_HEVC && (CHIP_FAMILY_TYPE==CHIP_FAMILY_MAYA) )//IMPLEMENT_DTV_H265
    if( (initParam.eCodecType != E_VDEC_CODEC_TYPE_HEVC)
     && (initParam.eCodecType != E_VDEC_CODEC_TYPE_AVS) ) // not do force interlace!!
    {
        if( MApi_VDEC_SetControl(VDEC_USER_CMD_FORCE_INTERLACE_MODE,1) != E_VDEC_OK )
        {
            printf(" VDEC_USER_CMD_FORCE_INTERLACE_MODE  fail !\n");
        }
    }
  #else
    if( MApi_VDEC_SetControl(VDEC_USER_CMD_FORCE_INTERLACE_MODE,1) != E_VDEC_OK)
    {
        printf(" VDEC_USER_CMD_FORCE_INTERLACE_MODE  fail !\n");
    }
  #endif
  */

#else

    if( IsATVInUse() )
    {
        MApi_VDEC_SetControl(VDEC_USER_CMD_SHOW_FIRST_FRAME_DIRECT, TRUE);
        MApi_VDEC_SetControl(VDEC_USER_CMD_PUSH_DISPQ_WITH_REF_NUM, TRUE);
    }

#endif


#if ENABLE_MIU_PROTECT_VDEC_AEON // Protect VDEC-aeon buffer
    PRINT_CURRENT_LINE();
  #if 0 //Vdec-Aeon
    {
        U8 au8ProtectIds_2[4] = {MIU_CLIENT_MAU1_RW, 0, 0, 0 };
        PRINT_CURRENT_LINE();
        msAPI_MIU_Set_MiuProtect(2, au8ProtectIds_2,
            //VDEC_AEON_ADR, VDEC_AEON_ADR+VDEC_AEON_LEN,
            //SUBTITLE_ADR, SUBTITLE_ADR+SUBTITLE_LEN,
            VDEC_BITSTREAM_ADR, VDEC_BITSTREAM_ADR+VDEC_BITSTREAM_LEN,
            ENABLE);
    }
  #else
    { // Vdec BitStream
        U8 au8ProtectIds_2[4] = {MIU_CLIENT_MVD_BBU_RW, 0, 0, 0 };
        msAPI_MIU_Set_MiuProtect(2, au8ProtectIds_2,
            VDEC_BITSTREAM_ADR, VDEC_BITSTREAM_ADR+VDEC_BITSTREAM_LEN,
            ENABLE);
    }
  #endif
#endif

    DEBUG_BOOT_TIME(DEBUG_FUNC_TIME_END());

    return TRUE;
}

//******************************************************************************
/// set MVOP output timing according to MVD/h.264 video frame information
/// @param pstVOPTiming \b IN VOP timing
/// @param pstVidStatus \b IN Video Status
//******************************************************************************
BOOLEAN msAPI_VID_SetOutput(VDEC_DispInfo *pstVidStatus)
{
    MVOP_VidStat stMvopVidSt;
    MVOP_InputSel tMvopInputSel;

    VDEC_CodecType eVDEC_CodecType = msAPI_VID_GetCodecType();


#if ENABLE_FBL_ASPECT_RATIO_BY_MVOP
    if(MApi_XC_IsCurrentFrameBufferLessMode() && g_bApplyMVOPCrop)
    {
        MVOP_InputCfg dc_param;
        memset(&dc_param, 0, sizeof(MVOP_InputCfg));
        dc_param.u16CropWidth = g_tSrcWin.width;
        dc_param.u16CropHeight = g_tSrcWin.height;
        dc_param.u16CropX = g_tSrcWin.x;
        dc_param.u16CropY = g_tSrcWin.y;
        if( (eVDEC_CodecType == E_VDEC_CODEC_TYPE_MPEG2)
          ||(eVDEC_CodecType == E_VDEC_CODEC_TYPE_VC1_ADV)
          )
        {
            dc_param.enVideoType = MVOP_MPG;
        #if (VIDEO_FIRMWARE_CODE >= VIDEO_FIRMWARE_CODE_HD)
            dc_param.u16StripSize = 1920;
        #else
            dc_param.u16StripSize = 720;
        #endif
        }
        else if( (eVDEC_CodecType == E_VDEC_CODEC_TYPE_H264)
               ||(eVDEC_CodecType == E_VDEC_CODEC_TYPE_AVS)
            #if( CHIP_SUPPORT_HEVC )
               ||(eVDEC_CodecType == E_VDEC_CODEC_TYPE_HEVC)
            #endif
               )
        {
            dc_param.enVideoType = MVOP_H264;
            dc_param.u16StripSize = g_u16StripSize;
        }
        else
        {
            SHOW_VIDEO_ERR(("not support this codec type=%d", eVDEC_CodecType));
            return FAIL;
        }
        MDrv_MVOP_SetInputCfg(MVOP_INPUT_CLIP, &dc_param);
    }
    else
#endif
    {
        if ((eVDEC_CodecType == E_VDEC_CODEC_TYPE_MPEG2) ||
            (eVDEC_CodecType == E_VDEC_CODEC_TYPE_VC1_ADV))
        {
            tMvopInputSel = MVOP_INPUT_MVD;
        }
        else if(eVDEC_CodecType == E_VDEC_CODEC_TYPE_H264)
        {
            tMvopInputSel = MVOP_INPUT_H264;
        }
        else if(eVDEC_CodecType == E_VDEC_CODEC_TYPE_AVS)
        {
            tMvopInputSel = MVOP_INPUT_H264;
        }
      #if (CHIP_SUPPORT_HEVC)//IMPLEMENT_DTV_H265
        else if(eVDEC_CodecType == E_VDEC_CODEC_TYPE_HEVC)
        {
            tMvopInputSel = MVOP_INPUT_EVD;
        }
      #endif
        else
        {
            SHOW_VIDEO_ERR(("not support this codec type=%d", eVDEC_CodecType));
            return FAIL;
        }
        MDrv_MVOP_SetInputCfg(tMvopInputSel, NULL);
    }

    memset(&stMvopVidSt, 0, sizeof(MVOP_VidStat));
    stMvopVidSt.u16HorSize = pstVidStatus->u16HorSize;
    stMvopVidSt.u16VerSize = pstVidStatus->u16VerSize;
    //modify for Brazil TS which FrameRate is 14985 and video is not smooth.
    if (pstVidStatus->u32FrameRate < 23000)
    {
        stMvopVidSt.u16FrameRate = pstVidStatus->u32FrameRate << 1;
    }
    else
    {
        stMvopVidSt.u16FrameRate = pstVidStatus->u32FrameRate;
    }
    stMvopVidSt.u8AspectRate = pstVidStatus->u8AspectRate;
    stMvopVidSt.u8Interlace = pstVidStatus->u8Interlace;

#if ENABLE_FBL_ASPECT_RATIO_BY_MVOP
    if(MApi_XC_IsCurrentFrameBufferLessMode())
    {
        stMvopVidSt.u16HorOffset = g_u16HorOffset;
        stMvopVidSt.u16VerOffset = g_u16VerOffset;
    }
#endif


#if(MARLON_PATCH__MVOP_READ_OVER_RANGE)
    if( (eVDEC_CodecType == E_VDEC_CODEC_TYPE_MPEG2)
      ||(eVDEC_CodecType == E_VDEC_CODEC_TYPE_VC1_ADV)
      )
    {
        MDrv_WriteByteMask(0x101471, 0x00, 0x40); // bit[14] : 10bit
        MDrv_WriteByteMask(0x10148E, 0x02, 0x02); // bit[1] : mask LSB DMA request
    }
    else
    {
        //MDrv_WriteByteMask(0x101471, 0x00, 0x40); // bit[14] : 10bit
        MDrv_WriteByteMask(0x10148E, 0x00, 0x02); // bit[1] : mask LSB DMA request
    }
#endif


#if FIXED_480I_50HZ_CVBS_OUT_GARBAGE
    MS_BOOL bVSizeMinIs576 = TRUE;
#else
    //Set MVOP VSize Min function as false.... this function will let 480i Video output 576 vtt
    MS_BOOL bVSizeMinIs576 = FALSE;
#endif
    MVOP_Handle stMvopHd = { E_MVOP_MODULE_MAIN };
    MDrv_MVOP_SetCommand(&stMvopHd, E_MVOP_CMD_SET_VSIZE_MIN, &bVSizeMinIs576);


  #if (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)
    MDrv_MVOP_SetOutputCfg(&stMvopVidSt, FALSE);
  #else
    MDrv_MVOP_SetOutputCfg(&stMvopVidSt, TRUE);
  #endif

    // h264 only
    if( pstVidStatus->bWithChroma == FALSE )
    {
        if( (eVDEC_CodecType==E_VDEC_CODEC_TYPE_H264)
        #if( CHIP_SUPPORT_HEVC )//IMPLEMENT_DTV_H265
          ||(eVDEC_CodecType==E_VDEC_CODEC_TYPE_HEVC)
        #endif
          )
        {
            MDrv_MVOP_SetMonoMode(TRUE);
        }
    }

#if(DEBUG_CHG_SRC_TIME)
    msDebug_PrintChgSrcTime("Set MVOP Done" );
#endif

#if 0
    (printf("->u32FrameRate = %u\n", pstVidStatus->u32FrameRate));
    (printf("->u8Interlace = %x\n", pstVidStatus->u8Interlace));
    (printf("->u16HorSize = %u\n", pstVidStatus->u16HorSize));
    (printf("->u16VerSize = %u\n", pstVidStatus->u16VerSize));
    (printf("->u16Crop R/L = %u, %u\n", pstVidStatus->u16CropRight, pstVidStatus->u16CropLeft));
    (printf("->u16Crop B/T = %u, %u\n", pstVidStatus->u16CropBottom, pstVidStatus->u16CropTop));
    (printf("->u8AspectRate = %u\n", pstVidStatus->u8AspectRate));
    (printf("->u16SarWidth = %u\n", pstVidStatus->u16SarWidth));
    (printf("->u16SarHeight = %u\n", pstVidStatus->u16SarHeight));
    (printf("->bWithChroma = %u\n", pstVidStatus->bWithChroma));
#endif

    return PASS;
}

//******************************************************************************
/// AVCH264 is aspect ratio wide
/// @param pstVidStatus \b in information about pic
/// @param pstVidStatus \b out is wide
/// @return
///   - # TRUE success
///   - # FALSE error
//******************************************************************************
BOOLEAN msAPI_VID_AVCH264IsAspectRatioWide(VDEC_DispInfo *pstVidStatus,
                                           BOOLEAN *bResult)
{
    U32 u32AspRatioH, u32AspRatioW;

    if (pstVidStatus->u8AspectRate == 0xFF)  //extended_sar
    {
        u32AspRatioW = (U32) pstVidStatus->u16SarWidth;
        u32AspRatioH = (U32) pstVidStatus->u16SarHeight;
    }
    else if (pstVidStatus->u8AspectRate < 17)
    {
        u32AspRatioW = (U32)
                       _H264_ASPECT_RATIO[pstVidStatus->u8AspectRate][0];
        u32AspRatioH = (U32)
                       _H264_ASPECT_RATIO[pstVidStatus->u8AspectRate][1];
    }
    else
    {
        *bResult = FALSE;
        return FALSE;
    }
    if (pstVidStatus->u16HorSize * u32AspRatioW * 2 >
        pstVidStatus->u16VerSize * u32AspRatioH * 3)
    {
        *bResult = TRUE;
    }
    else
    {
        *bResult = FALSE;
    }
    return TRUE;
}

#define DEBUG_DTV_FBL(x)    x

BOOLEAN msAPI_VID_IsNeedFrameBufferLessMode(VDEC_DispInfo *pstVidStatus)
{
    U32 u32WxH, u32VDECMemUsage = 0;
    VDEC_Result  ret;
    VDEC_CodecType eVdecCodecType = msAPI_VID_GetCodecType();
    BOOLEAN bNeedFBL = TRUE;


    DEBUG_DTV_FBL(printf(" eVdecCodecType = %u\n", eVdecCodecType););

    ret = MApi_VDEC_GetControl(VDEC_USER_CMD_GET_FB_USAGE_MEM, &u32VDECMemUsage);
    if (E_VDEC_OK != ret)
    {
        printf("\nWarning: Get VDEC use mem failed, ret = %d\n",ret);
        return bNeedFBL;
    }
    DEBUG_DTV_FBL( printf(" VDEC use mem size = %u(0x%x)\n", u32VDECMemUsage, u32VDECMemUsage); );
    DEBUG_DTV_FBL( printf(" MMAP DTV_SD_FB size = %u(0x%x)\n", g_VDEC_u32Dtv_SD_FrameBufSize, g_VDEC_u32Dtv_SD_FrameBufSize); );


    u32WxH = pstVidStatus->u16HorSize * pstVidStatus->u16VerSize;
    DEBUG_DTV_FBL(printf(" u16HorSize=%u, u16VerSize=%u, u32WxH=%u\n", pstVidStatus->u16HorSize, pstVidStatus->u16VerSize, u32WxH ););

    // Check if vdec need memory > VDEC_FRAMEBUFFER_LEN
    if( u32VDECMemUsage > g_VDEC_u32Dtv_SD_FrameBufSize )
    {
        DEBUG_DTV_FBL( printf("VDEC use mem > MMAP size ==> FBL\n"); );
        bNeedFBL = TRUE;
        return bNeedFBL;
    }

    switch(eVdecCodecType)
    {
        case E_VDEC_CODEC_TYPE_H264:
    #if (CHIP_SUPPORT_HEVC) //IMPLEMENT_DTV_H265
        case E_VDEC_CODEC_TYPE_HEVC:
    #endif
            DEBUG_DTV_FBL(printf(" [H264] "); );
            if( u32WxH <= DTV_H264_FBL_MODE_THRESHOLD )
            {
                bNeedFBL = FALSE;
            }
            break;

        case E_VDEC_CODEC_TYPE_MPEG2:
            DEBUG_DTV_FBL(printf(" [MPEG2] "); );
            if( u32WxH <= DTV_MPEG2_FBL_MODE_THRESHOLD )
            {
                bNeedFBL = FALSE;
            }
            break;

        default:
            DEBUG_DTV_FBL(printf(" [Other Codec] "); );
            if( u32WxH <= DTV_OTHER_CODEC_FBL_MODE_THRESHOLD)
            {
                bNeedFBL = FALSE;
            }
            break;
    }

    if( bNeedFBL )
    {
        DEBUG_DTV_FBL(printf(" DTV need FBL\n"); );
    }
    else
    {
        DEBUG_DTV_FBL(printf(" DTV use FB\n"); );
    }

    return bNeedFBL;
#if 0
    if( (msAPI_VID_GetCodecType() == E_VDEC_CODEC_TYPE_H264)
    #if (CHIP_SUPPORT_HEVC)//IMPLEMENT_DTV_H265
      ||(msAPI_VID_GetCodecType() == E_VDEC_CODEC_TYPE_HEVC)
    #endif
      )
    {
        if ((u32MemUsage <= u32FBSize_SD) &&
            (u32WxH < FBL_MODE_THRESHOLD))
        {
            printf("H264 SD MODE \n");
            return FALSE;
        }
        else
        {
            printf("H264 FBL MODE \n");
            return TRUE;
        }
    }
    else
    {
        if(u32WxH <= 1280 * 720)
        {
            printf("MPEG2 SD MODE \n");
            return FALSE;
        }
        else
        {
            printf("MPEG2 FBL MODE \n");
            return TRUE;
        }
    }
#endif
}

#if( CHIP_SUPPORT_HEVC )
BOOLEAN msAPI_VID_Is_CodecH265(void)
{
    if( msAPI_VID_GetCodecType() == E_VDEC_CODEC_TYPE_HEVC )
        return TRUE;

    return FALSE;
}
#endif

BOOLEAN msAPI_VID_Is_SrcOriginalInterlace(void)
{
    MS_U32 u32Info = 0;

    VDEC_Result eVDEC_Result = MApi_VDEC_GetControl(VDEC_USER_CMD_GET_ORI_INTERLACE_MODE, &u32Info);

    //PRINT_CURRENT_LINE();
    //printf("eVDEC_Result=%u, u32Info=%u\n", eVDEC_Result, u32Info);

    if( (eVDEC_Result==E_VDEC_OK)&&(u32Info) )
        return TRUE;

    return FALSE;
}

#undef MSAPI_VIDEO_C

