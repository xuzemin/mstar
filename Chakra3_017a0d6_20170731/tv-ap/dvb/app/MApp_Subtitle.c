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

/// @file  MApp_Subtitle.c
/// @brief Subtitle Display
/// @author MStar Semiconductor Inc.

//------------------------------------------------------------------------------
// Include Files
//------------------------------------------------------------------------------


#include <stdio.h>
#include <string.h>

// Common Definition
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"

#include "debug.h"
#if (ENABLE_SUBTITLE)

#define MAPP_SUBTITLE_C
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "apiGOP.h"
#include "msAPI_Timer.h"
#include "msAPI_MPEG_Subtitle.h"
#include "msAPI_Subtitle_Pub.h"
#include "msAPI_Video.h"
#include "msAPI_MMap.h"

// APP Layer
#include "MApp_GlobalFunction.h"
#include "MApp_Exit.h"
#include "mapp_demux.h"
#include "MApp_Audio.h"
#include "MApp_MVDMode.h"
#include "MApp_Subtitle.h"
#include "MApp_UiMenuDef.h"
#if MHEG5_ENABLE
#include "MApp_MHEG5_Main.h"
#include "mapp_mheg5.h"
#endif
#include "MApp_TopStateMachine.h"
#include "MApp_TV.h"
#if ENABLE_PVR
#include "MApp_PVR.h"
#endif
#ifdef MSOS_TYPE_LINUX
#include "MsOS.h"
#endif
#include "MApp_XC_Sys.h"

#if ENABLE_CI
#include "msAPI_CI.h"
#include "MApp_CIMMI.h"
#endif

// panel module
#include "Panel.h"
#include "apiPNL.h"

#if ENABLE_PIP
#include "MApp_PIP.h"
#endif

#ifndef ENABLE_CHECK_SUBTITLE_PID
#define ENABLE_CHECK_SUBTITLE_PID   ENABLE
#endif

//-------------------------------------------------------------------------------------------------
// Local Defines
//-------------------------------------------------------------------------------------------------
#define DUMP_PID                    FALSE
#define SBTL_ERR(x)                 MS_DEBUG_MSG(x)
#define VERBOSE                     FALSE
#define PRINT_HEADER                FALSE
#define PES_HEADER_LEN              16         // min bytes of data that are needed to know the PES packet length and it has to be 4-byte alignment
#define PES_BLOCK_LEN               512        // this depends on demux design
#define VIDEO_SYNC_DELAY 120*90

//-------------------------------------------------------------------------------------------------
// Enum
//-------------------------------------------------------------------------------------------------
enum
{
    Subtitle_Org = 0,
    Subtitle_4x3,
    Subtitle_14x9,
    Subtitle_Zoom1,
    Subtitle_Zoom2,
    Subtitle_16x9,
    Subtitle_Panorama
};

//-------------------------------------------------------------------------------------------------
// Local Variables
//-------------------------------------------------------------------------------------------------
static BOOLEAN              _bGOP2OP                    = FALSE;
static BOOLEAN              _bSubtitleOn                = FALSE;
static BOOLEAN              _bForceUpdatePID            = FALSE;
static BOOLEAN              _bSubtitleIdxUpdatedByUI    = FALSE;
static U16                  _u16_video_width            = 0;
static U16                  _u16_video_height           = 0;
static U16                  _u16PesDataLength           = 0;
static U16                  _u16CurSubtitlePID          = MSAPI_DMX_INVALID_PID;
static U16                  _u16CPID                    = MSAPI_DMX_INVALID_PID;
static U16                  _u16APID                    = MSAPI_DMX_INVALID_PID;
static EN_RET               _enSubtitleRetVal           = EXIT_SUBTITLE_EXIT;
static EN_SUBTITLE_STATE    _enSubtitleState            = STATE_SUBTITLE_INIT;
#if(ENABLE_OSD_SUBTITLE_EXCLUSIVE == ENABLE)
static BOOLEAN      _bShowSubtitle     = FALSE;
#endif
static BOOLEAN bSubtitleSelIdxInvaild  = FALSE;

//static BIT bSubtitlePIDUpdatedByPMT = FALSE;

#if ( SUBTITLE_WITH_OSD )
static U8                   _u8OriGWId = GWIN_ID_INVALID;
static U16                  _u16OriX0  = 0xFFFF;
static U16                  _u16OriY0  = 0xFFFF;
static U16                  _u16OriX1  = 0xFFFF;
static U16                  _u16OriY1  = 0xFFFF;
#endif

#if ENABLE_AUTOTEST
extern BOOLEAN g_bAutobuildDebug;
#endif
#if ENABLE_FileIn_PMTMonitor
extern BOOLEAN _RecordUpdateAllPIDs;
#endif
////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApp_Subtitle_GetSTC()
/// @brief \b Function \b Description : Return the system STC from TSP
///
/// @param <IN>        \b None :
/// @param <OUT>       \b None :
/// @param <RET>       \b U32  : STC from TSP
////////////////////////////////////////////////////////////////////////////////
static U32 MApp_Subtitle_GetSTC(void)
{
    U32 u32STC, u32SystemSTC_H;
    MApi_DMX_Stc_Get(&u32SystemSTC_H, &u32STC);

    return u32STC;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApp_Subtitle_Delete_OSDGWIN()
/// @brief \b Function \b Description : Delete OSD GWIN
///
/// @param <IN>        \b None :
/// @param <OUT>       \b None :
/// @param <RET>       \b None :
////////////////////////////////////////////////////////////////////////////////
static void MApp_Subtitle_Delete_OSDGWIN(void)
{
    U16 u16StretchWidth;
    U16 u16StretchHeight;
    _bSubtitleOn = TRUE;

    if (_bGOP2OP)
    {
        MApi_GOP_GWIN_SetGOPDst(E_GOP_APP, E_GOP_DST_OP0);
    }
    else
    {
        MApi_GOP_GWIN_SetGOPDst(E_GOP_APP, E_GOP_DST_IP0);
    }

    MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);

    if (_bGOP2OP)
    {
        u16StretchWidth = g_IPanel.Width() < 720 ? g_IPanel.Width() : 720;
        u16StretchHeight = g_IPanel.Height() < 576 ? g_IPanel.Height() : 576;
        MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_OP0, 0, 0, u16StretchWidth, u16StretchHeight);
        MApi_GOP_GWIN_Set_HSCALE(TRUE, u16StretchWidth, g_IPanel.Width()) ;
        MApi_GOP_GWIN_Set_VSCALE(TRUE, u16StretchHeight, g_IPanel.Height()) ;
    }
    else
    {
        u16StretchWidth = (_u16_video_width > 1920) ? 1920 : _u16_video_width;
        u16StretchHeight = (_u16_video_height > 1080) ? 1080 : _u16_video_height;

        #if SUBTITLE_REDUCE_GWIN
        // If HD reduce gwin to 1/2 video width and using GOP stretch to video width
        if(u16StretchWidth >= 1280)
        {
            msAPI_Subtitle_SetReduceGwin(TRUE);
            MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_IP0, 0, 0, u16StretchWidth/2, u16StretchHeight);
            MApi_GOP_GWIN_Set_HSCALE(TRUE, 1, 2);
        }
        else
        #endif
        {
            msAPI_Subtitle_SetReduceGwin(FALSE);
            MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_IP0, 0, 0, u16StretchWidth, u16StretchHeight);
            MApi_GOP_GWIN_Set_HSCALE(TRUE, 1, 1);
        }
        MApi_GOP_GWIN_Set_VSCALE(TRUE, 1, 1);

#if (ENABLE_VOP_DUPLICATE)
        if (MDrv_MVOP_GetIsHDuplicate())
        {
            MApi_GOP_GWIN_Set_HSCALE(TRUE, _u16_video_width, _u16_video_width*2);
        }
#endif
    }

}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApp_Subtitle_Restore_OSDGWIN()
/// @brief \b Function \b Description : Restore OSD GWIN
///
/// @param <IN>        \b None :
/// @param <OUT>       \b None :
/// @param <RET>       \b None :
////////////////////////////////////////////////////////////////////////////////
static void MApp_Subtitle_Restore_OSDGWIN(void)
{
    _bSubtitleOn = FALSE;
#if (MHEG5_ENABLE && ENABLE_CI)
    msAPI_MHEG5_RESTORE();
#else
#if (UI_SKIN_SEL ==  UI_SKIN_1920X1080X565)
    MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
	MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_OP0, 0, 0, 1920, 1080);
	MApi_GOP_GWIN_Set_HSCALE(TRUE, 1920, g_IPanel.Width());
	MApi_GOP_GWIN_Set_VSCALE(TRUE, 1080, g_IPanel.Height());
	MApi_GOP_GWIN_SetGOPDst(E_GOP_APP, E_GOP_DST_OP0);
	MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD);
#else
	MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
	MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_APP, E_GOP_DST_OP0, 0, 0, 1366, 768);
	MApi_GOP_GWIN_Set_HSCALE(TRUE, 1366, g_IPanel.Width());
	MApi_GOP_GWIN_Set_VSCALE(TRUE, 768, g_IPanel.Height());
	MApi_GOP_GWIN_SetGOPDst(E_GOP_APP, E_GOP_DST_OP0);
	MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD);
#endif
#endif
    msAPI_MIU_Set_DRAM2DRAM_Mode(TRUE);
}

#if ( SUBTITLE_WITH_OSD )
////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApp_Subtitle_Switch2OP()
/// @brief \b Function \b Description : Switch GOP
///
/// @param <IN>        \b None :
/// @param <OUT>       \b None :
/// @param <RET>       \b None :
////////////////////////////////////////////////////////////////////////////////
void MApp_Subtitle_Switch2OP(void)
{
    MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD);
    if (_u8OriGWId == GWIN_ID_INVALID)
    {
        return;
    }
    else
    {
        MApi_GOP_GWIN_Switch2Gwin(_u8OriGWId);
    }

    if ((_u16OriX0 == 0xFFFF) || (_u16OriX0 == 0xFFFF) || (_u16OriX0 == 0xFFFF) || (_u16OriX0 == 0xFFFF))
    {
        return;
    }
    else
    {
        msAPI_OSD_SetClipWindow(_u16OriX0, _u16OriY0, _u16OriX1, _u16OriY1);
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApp_Subtitle_Switch2OP()
/// @brief \b Function \b Description : Switch GOP
///
/// @param <IN>        \b None :
/// @param <OUT>       \b None :
/// @param <RET>       \b None :
////////////////////////////////////////////////////////////////////////////////
void MApp_Subtitle_Switch2IP(void)
{
    MApi_GOP_GWIN_SwitchGOP(E_GOP_APP);
    _u8OriGWId = MApi_GOP_GWIN_GetCurrentWinId();
    msAPI_OSD_GetClipWindow(&_u16OriX0, &_u16OriY0, &_u16OriX1, &_u16OriY1);
}
#endif

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApp_Subtitle_Initial()
/// @brief \b Function \b Description : Main Subtitle Initial
///
/// @param <IN>        \b None :
/// @param <OUT>       \b None :
/// @param <RET>       \b BOOLEAN : FALSE if Subtitle Initial Fail
////////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_Subtitle_Initial(void)
{
    VDEC_DispInfo _stVidInfo;
    MEMBER_SERVICETYPE bServiceType;
    WORD wCurrentPosition;
    WORD wVideo_PID;
    BOOLEAN bMVOPEnable = FALSE;

    if (!_bSubtitleOn)
    {
        if(g_bSetModeDone == FALSE)
        {
            return FALSE;
        }

        if(msAPI_VID_GetVidInfo(&_stVidInfo))
        {
            _u16_video_width = _stVidInfo.u16HorSize;
            _u16_video_height = _stVidInfo.u16VerSize;

            if ((_u16_video_width == 0) || (_u16_video_height == 0))
            {
                return FALSE;
            }
        }
        else
        {
            return FALSE;
        }

        bServiceType = msAPI_CM_GetCurrentServiceType();
        wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);
        wVideo_PID = msAPI_CM_GetVideoPID(bServiceType, wCurrentPosition);
        _bGOP2OP = (IsDTVInUse() && enMVDVideoStatus == MVD_BAD_VIDEO) ? TRUE : FALSE;  // if video is bad, use OP

        // check MVOP is enable or disable
        if(MDrv_MVOP_GetIsEnable(&bMVOPEnable))
        {
            return FALSE;
        }

        // if mvop is disable, set gwin force write to avoid waiting for vsync
        if(bMVOPEnable == FALSE)
        {
            MApi_GOP_GWIN_SetForceWrite(TRUE);
        }

        MApp_Subtitle_Delete_OSDGWIN();
        msAPI_MIU_SetRoundRobin(FALSE);

        // use gop frame buffer from MIU0 to MIU1
    #ifdef GOP_GWIN_RB2_ADR
        #if(GOP_GWIN_RB2_MEMORY_TYPE&MIU1)
            MApi_GOP_MIUSel(E_GOP_APP, E_GOP_SEL_MIU1);
        #else
            MApi_GOP_MIUSel(E_GOP_APP, E_GOP_SEL_MIU0);
        #endif
        msAPI_Subtitle_SetGOPParameter(TRUE, _PA2VA((GOP_GWIN_RB2_MEMORY_TYPE & MIU1) ? (GOP_GWIN_RB2_ADR | MIU_INTERVAL) : (GOP_GWIN_RB2_ADR)));
    #endif

        MApi_GOP_GWIN_Set_HStretchMode(E_GOP_HSTRCH_6TAPE);
        if (_bGOP2OP)
        {
            msAPI_Subtitle_Init_Display_OP();
        }
        else
        {
            msAPI_Subtitle_Init_Display(_u16_video_width, _u16_video_height);
        }

        if(bMVOPEnable == FALSE)
        {
            MApi_GOP_GWIN_SetForceWrite(FALSE);
        }

        bEnableSubtitleTimeoutMonitor = FALSE;
    }

    return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApp_Subtitle_Exit()
/// @brief \b Function \b Description : Exit Subtitle Gwin Display
///
/// @param <IN>        \b None :
/// @param <OUT>       \b None :
/// @param <RET>       \b None :
////////////////////////////////////////////////////////////////////////////////
void MApp_Subtitle_Exit(void)
{
#if(ENABLE_OSD_SUBTITLE_EXCLUSIVE == ENABLE)
		_bShowSubtitle = FALSE;
#endif
    if (_bSubtitleOn)
    {
        BOOLEAN bMVOPEnable = FALSE;

        // check MVOP is enable or disable
        if(MDrv_MVOP_GetIsEnable(&bMVOPEnable))
        {
            return;
        }

        // if mvop is disable, set gwin force write to avoid waiting for vsync
        if(bMVOPEnable == FALSE)
        {
            MApi_GOP_GWIN_SetForceWrite(TRUE);
        }

        msAPI_Subtitle_DeInit();
        msAPI_MIU_SetRoundRobin(TRUE);
        MApp_Subtitle_Restore_OSDGWIN();
     #if ((FIXED_MIRROR_HD_PANEL_UI_LOSE == ENABLE) && (MirrorEnable == ENABLE))
	if((g_IPanel.Width()<=1366&&g_IPanel.Height()<=768)&&MApp_Image_GetMirror())
	{
		MApi_GOP_GWIN_Set_HStretchMode(E_GOP_HSTRCH_DUPLICATE);
		MApi_GOP_GWIN_Set_VStretchMode(E_GOP_VSTRCH_DUPLICATE);
	}
     #endif

        bEnableSubtitleTimeoutMonitor = FALSE;
        _u16_video_width = 0;
        _u16_video_height = 0;

        if(bMVOPEnable == FALSE)
        {
            MApi_GOP_GWIN_SetForceWrite(FALSE);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApp_Subtitle_GetCurrentMonitorRatio()
/// @brief \b Function \b Description : Get Current Monitor Ratio
///
/// @param <IN>        \b None :
/// @param <OUT>       \b None :
/// @param <RET>       \b None :
////////////////////////////////////////////////////////////////////////////////
static SUBTITLING_TYPE MApp_Subtitle_GetCurrentMonitorRatio(void)
{
    SUBTITLING_TYPE stRet = SUBTITLING_TYPE_NORMAL_NO;

    if (ST_VIDEO.eAspectRatio == EN_AspectRatio_Original)
    {
        if (gstVidStatus.u8AspectRate == ASP_4TO3)
        {
            stRet = SUBTITLING_TYPE_NORMAL_4X3;
        }
        else if (gstVidStatus.u8AspectRate == ASP_16TO9)
        {
            stRet = SUBTITLING_TYPE_NORMAL_16X9;
        }
        else if (gstVidStatus.u8AspectRate == ASP_221TO100)
        {
            stRet = SUBTITLING_TYPE_NORMAL_221X100;
        }
        else
        {
            ;
        }
    }
    else if (ST_VIDEO.eAspectRatio == EN_AspectRatio_4X3)
    {
        stRet = SUBTITLING_TYPE_NORMAL_4X3;
    }
    else if (ST_VIDEO.eAspectRatio == EN_AspectRatio_16X9)
    {
        stRet = SUBTITLING_TYPE_NORMAL_16X9;
    }
    else
    {
        ;
    }

    // If HD stream, always return 16x9
    if(_u16_video_width > 720 || _u16_video_width > 576)
    {
        stRet = SUBTITLING_TYPE_NORMAL_16X9;
    }

    return stRet;
}

static U8 MApp_Subtitle_GetSubitleSubtype(SUBTITLING_TYPE u8SubtitleType)
{
    return ((u8SubtitleType & 0x30) >> 4) ;
}

static U8 MApp_Subtitle_GetSubtitleRatio(SUBTITLING_TYPE u8SubtitleType)
{
    return (u8SubtitleType & 0x03) ;
}

static BOOLEAN MApp_Subtitle_IsSameSubtitleType(SUBTITLING_TYPE stype1, SUBTITLING_TYPE stype2)
{
    return (MApp_Subtitle_GetSubitleSubtype(stype1) == MApp_Subtitle_GetSubitleSubtype(stype2));
}

static BOOLEAN MApp_Subtitle_IsHoH(SUBTITLING_TYPE u8type)
{
    if ((u8type == SUBTITLING_TYPE_TELETEXT_HOH) || ((SUBTITLING_TYPE_HH_NO <= u8type) && (u8type <= SUBTITLING_TYPE_HH_HD)))
        return TRUE;
    else
        return FALSE;
}

static BOOLEAN MApp_Subtitle_IsDVB(SUBTITLING_TYPE u8type)
{
    if (u8type >= SUBTITLING_TYPE_NORMAL_NO)
        return TRUE;
    else
        return FALSE;
}

static BOOLEAN MApp_Subtitle_IsHD(SUBTITLING_TYPE u8type)
{
    if (u8type & 0x04)
		return TRUE;
	else
		return FALSE;
}


////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApp_Subtitle_GetSubtitleDefinition()
/// @brief \b Function \b Description : Get subtitle HD type
///
/// @param <IN>        \b u8SubtitleType : subtitle service type
/// @param <RET>       \b U8: subtitle HD type bit
////////////////////////////////////////////////////////////////////////////////
static U8 MApp_Subtitle_GetSubtitleDefinition(SUBTITLING_TYPE u8SubtitleType)
{
    return ((u8SubtitleType & 0x04) >> 2);
}

#if 0//(ENABLE_SBTVD_BRAZIL_APP==0)
static BOOLEAN MApp_Subtitle_ExistInTTX(U8 u8k, U8 i)
{
    return ((0 == strcmp((char *)(DVBSubtitleServices[u8k].StringCodes), SubtitleMenu[i].StringCodes)) &&
            MApp_Subtitle_IsHoH(SubtitleMenu[i].u8SubtitleType) == MApp_Subtitle_IsHoH(DVBSubtitleServices[u8k].u8SubtitleType) &&
            ((SubtitleMenu[i].u8SubtitleType == SUBTITLING_TYPE_TELETEXT) || (SubtitleMenu[i].u8SubtitleType == SUBTITLING_TYPE_TELETEXT_HOH)));
}
#endif

static RET_SBTL_SERVICE_SEARCH MApp_Subtitle_FindSubtitleServices(U8 u8k, U8 *u8TTXIdx)
{
    int i = 0;

    while(
        ((0 != strcmp((char *)(DVBSubtitleServices[u8k].StringCodes), SubtitleMenu[i].StringCodes)) ||
    #if ENABLE_CHECK_SUBTITLE_PID
         (DVBSubtitleServices[u8k].u16PID != SubtitleMenu[i].u16PID) ||
    #endif
         (!MApp_Subtitle_IsSameSubtitleType(DVBSubtitleServices[u8k].u8SubtitleType, SubtitleMenu[i].u8SubtitleType)) ||
         ((MApp_Subtitle_GetSubtitleDefinition(DVBSubtitleServices[u8k].u8SubtitleType) != MApp_Subtitle_GetSubtitleDefinition(SubtitleMenu[i].u8SubtitleType))))
         &&(i < u8SubtitleMenuNum))
    {
#if 0
	#if (ENABLE_SBTVD_BRAZIL_APP==0)
        if (IS_NORDIC_COUNTRY(OSD_COUNTRY_SETTING))
        {
            if (MApp_Subtitle_ExistInTTX(u8k, i))
            {
                *u8TTXIdx = i;
                return SBTL_SERVICE_TTX_FOUND;
            }
        }
	#endif
#endif
        i++;
    }
#if 1//(ENABLE_SBTVD_BRAZIL_APP)
    *u8TTXIdx = *u8TTXIdx;
#endif
    return (i == u8SubtitleMenuNum) ? SBTL_SERVICE_NOT_FOUND : SBTL_SERVICE_FOUND;
}

static U8 _Ms_tolower ( U8 InChar )
{
    if ( InChar >='A'  &&  InChar <='Z')
        InChar=(InChar-'A')+'a';
    return( InChar );
}

static U8 MApp_Subtitle_GetServiceIdx(U8 u8Idx)
{
    U8  u8i = 0;
    U8  u8DefaultIdx = 0xff;
    U8  j=0;
    U8  u8StringCodes1[4]={0};
    U8  u8StringCodes2[4]={0};

    if ((u8Idx == 0xFF) || (u8Idx >= MAX_SUBTITLE_SERVICE_NUM))
    {
        return u8DefaultIdx;
    }

    // If video is HD type, not to check ratio
    while (
        ((0 != strcmp((char *)(DVBSubtitleServices[u8i].StringCodes), SubtitleMenu[u8Idx].StringCodes)) ||       // code
#if ENABLE_CHECK_SUBTITLE_PID
          (DVBSubtitleServices[u8i].u16PID != SubtitleMenu[u8Idx].u16PID) ||
#endif
        (!MApp_Subtitle_IsSameSubtitleType(DVBSubtitleServices[u8i].u8SubtitleType, SubtitleMenu[u8Idx].u8SubtitleType)) ||      // Hard of hearing
        (MApp_Subtitle_GetSubtitleDefinition(DVBSubtitleServices[u8i].u8SubtitleType) != MApp_Subtitle_GetSubtitleDefinition(SubtitleMenu[u8Idx].u8SubtitleType)) || // SD or HD
        ((MApp_Subtitle_GetSubtitleRatio(DVBSubtitleServices[u8i].u8SubtitleType) != MApp_Subtitle_GetSubtitleRatio(MApp_Subtitle_GetCurrentMonitorRatio()) && (!MApp_Subtitle_GetSubtitleDefinition(SubtitleMenu[u8Idx].u8SubtitleType)))))
        && (u8i < u8DVBSubtitleServiceNum))
    {
        //Both translate to lower case to compare string.
        memset(u8StringCodes1, 0, sizeof(u8StringCodes1));
        memset(u8StringCodes2, 0, sizeof(u8StringCodes2));
        for(j=0;j<3;j++)
        {
            u8StringCodes1[j] = _Ms_tolower(DVBSubtitleServices[u8i].StringCodes[j]);
            u8StringCodes2[j] = _Ms_tolower(SubtitleMenu[u8Idx].StringCodes[j]);
        }
        if ((0 == strcmp((char *)u8StringCodes1, (char *)u8StringCodes2)) &&
#if ENABLE_CHECK_SUBTITLE_PID
          (DVBSubtitleServices[u8i].u16PID == SubtitleMenu[u8Idx].u16PID) &&
#endif
                (MApp_Subtitle_IsSameSubtitleType(DVBSubtitleServices[u8i].u8SubtitleType, SubtitleMenu[u8Idx].u8SubtitleType)) &&
                (u8DefaultIdx == 0xff))
        {
            u8DefaultIdx = u8i;
        }

        u8i++;
    }

    return (u8i == u8DVBSubtitleServiceNum) ? u8DefaultIdx : u8i;
}

BOOLEAN MApp_Subtitle_SearchSubtitleLangPriority(EN_LANGUAGE* penLangList, U8 u8Number, BOOLEAN bIsHoH, BOOLEAN bIsHD, U8* pU8SelectIndex)
{
	U8 i, j;
	U16 value = 0;
	U16 Max=0;

	MApp_SetSubtitleSelIdx(TRUE);
	if(u8SubtitleMenuNum == 0)
	{
		return FALSE;
	}
	if(u8Number > 99)
	{
		u8Number=99;
	}
	*pU8SelectIndex=0;
	//Priority IsHoH > Language > IsHD
	//printf("u8SubtitleMenuNum=%d\n", u8SubtitleMenuNum);
	//printf("u8Number=%d\n", u8Number);
	for(i=0; i<u8SubtitleMenuNum; i++)
	{
		value=0;

		if(MApp_Subtitle_IsHoH(SubtitleMenu[i].u8SubtitleType) == bIsHoH)
		{
			value=5000;
		}

		for(j=0; j<u8Number; j++)
		{
			if(penLangList[j] == MApp_GetLanguageBySILanguage(msAPI_SI_GetLanguageByISO639LangCode( (U8 *)SubtitleMenu[i].StringCodes) ))
			{
				if(!bIsHoH && MApp_Subtitle_IsHoH(SubtitleMenu[i].u8SubtitleType))
				{
					continue;
				}
				else
				{
				    MApp_SetSubtitleSelIdx(FALSE);
					value += (99-j)*10;
					break;
				}
			}
		}

		if(MApp_Subtitle_IsDVB(SubtitleMenu[i].u8SubtitleType))
		{
			if(!bIsHoH && MApp_Subtitle_IsHoH(SubtitleMenu[i].u8SubtitleType))
			{
				if(i == u8SubtitleMenuNum)
				{
					break;
				}
				continue;
			}
			else
			{
				if(MApp_Subtitle_IsHD(SubtitleMenu[i].u8SubtitleType) == bIsHD)
				{
					value+=2;
				}
				else
				{
					value+=1;
				}
			}
		}
		if(value > Max)
		{
			Max=value;
			*pU8SelectIndex=i;
		}
	}

	if(!bIsHoH && MApp_Subtitle_IsHoH(SubtitleMenu[*pU8SelectIndex].u8SubtitleType))
	{
		stGenSetting.g_SysSetting.fEnableTTXSubTitle=FALSE;
		stGenSetting.g_SysSetting.fEnableSubTitle = EN_SUBTITILE_SYSTEM_OFF;
		return FALSE;
	}
       else
        {
            if(bIsHoH && MApp_Subtitle_IsHoH(SubtitleMenu[*pU8SelectIndex].u8SubtitleType))
            {
                stGenSetting.g_SysSetting.fEnableSubTitle = EN_SUBTITILE_SYSTEM_ON;
            }
            return TRUE;
       }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApp_Subtitle_Select_Language()
/// @brief \b Function \b Description : Select Subtitle Language
///
/// @param <IN>        \b SubtitleLang : Subtitle Language
/// @param <OUT>       \b None :
/// @param <RET>       \b None :
////////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_Subtitle_Select_Language(U8 SubtitleLang)
{
    if (SubtitleLang < u8SubtitleMenuNum)   //set to u8UISubTitleSelect
    {
        BOOLEAN bIdx_Updated = FALSE;

        if (u8SubtitleIdx != SubtitleLang)
        {
            bIdx_Updated = TRUE;
        }
        u8SubtitleIdx = SubtitleLang;

        //Check if teletext subtitle
        if (SubtitleMenu[u8SubtitleIdx].u8SubtitleType == SUBTITLING_TYPE_TELETEXT
                || SubtitleMenu[u8SubtitleIdx].u8SubtitleType == SUBTITLING_TYPE_TELETEXT_HOH
            #if (ENABLE_SUBTITLE)
                || SubtitleLang != u8preSubtitleMenuIdx)
            #else
                )
            #endif
        {
            return FALSE;
        }

        if (bIdx_Updated)
        {
            _bSubtitleIdxUpdatedByUI = TRUE;
        }
        return TRUE;
    }
    return FALSE;
}

BOOLEAN MApp_Subtitle_IsTTXSubtitle(U8 SubtitleLang)
{
    if (SubtitleLang < u8SubtitleMenuNum)
    {
        if (SubtitleMenu[SubtitleLang].u8SubtitleType == SUBTITLING_TYPE_TELETEXT ||
            SubtitleMenu[SubtitleLang].u8SubtitleType == SUBTITLING_TYPE_TELETEXT_HOH)
        {
            return TRUE;
        }
    }

    return FALSE;
}

U8 MApp_TTX_Subtitle_ParsePMT(MS_TELETEXT_INFO *pTTXInfo, U16 pid, U8 u8NumOfTTX, BOOLEAN *bGotInitPage)
{
    U8 i;

    for (i = pTTXInfo->u8NumTTXType; i < (pTTXInfo->u8NumTTXType + u8NumOfTTX); i++)
    {
        if (EN_TTX_INIT_TTX == pTTXInfo->stTTXInfo[i].u8TTXType)
        {
            *bGotInitPage = TRUE;
        }
        if ((pTTXInfo->stTTXInfo[i].u8TTXType == EN_TTX_SUBTITLE || pTTXInfo->stTTXInfo[i].u8TTXType == EN_TTX_SUBTITLE_HEAR) && u8SubtitleMenuNum < MAX_SUBTITLE_SERVICE_NUM)
        {
            U8 u8Index;
            BOOLEAN bExist = FALSE;

            //printf("Lang %c%c%c Mag %bx Page %bx PID 0x%x\n", pSIInfo->stPmtMonInfo.stTtx.stTTXInfo[i].u8lanuage_code[0],
            //pSIInfo->stPmtMonInfo.stTtx.stTTXInfo[i].u8lanuage_code[1], pSIInfo->stPmtMonInfo.stTtx.stTTXInfo[i].u8lanuage_code[2],
            //pSIInfo->stPmtMonInfo.stTtx.stTTXInfo[i].u8TTXMagNum, pSIInfo->stPmtMonInfo.stTtx.stTTXInfo[i].u8TTXPageNum,
            //pid);

            for (u8Index = 0; u8Index < u8SubtitleMenuNum; u8Index++)
            {
			#if 0
				//prefers DVB subtitles over Teletext subtitles when both are available
                if (IS_NORDIC_COUNTRY(OSD_COUNTRY_SETTING))
                {
                    if ((memcmp(SubtitleMenu[u8Index].StringCodes, pTTXInfo->stTTXInfo[i].u8lanuage_code, 3) == 0)
                            && (MApp_Subtitle_IsHoH(SubtitleMenu[u8Index].u8SubtitleType) == (pTTXInfo->stTTXInfo[i].u8TTXType == EN_TTX_SUBTITLE_HEAR))
                            && ((SUBTITLING_TYPE_NORMAL_NO <= SubtitleMenu[u8Index].u8SubtitleType) || (SubtitleMenu[u8Index].u8SubtitleType <= SUBTITLING_TYPE_HH_HD)))
                    {
                        /* Skip this ttx subtitle service */
                        bExist = TRUE;
                        break;
                    }
                }
			#endif
                if (SubtitleMenu[u8Index].u8SubtitleType != SUBTITLING_TYPE_TELETEXT
                        && SubtitleMenu[u8Index].u8SubtitleType != SUBTITLING_TYPE_TELETEXT_HOH)
                    continue;

                //don't store the duplicated teletext subtitle
                if (SubtitleMenu[u8Index].u8Magazine == pTTXInfo->stTTXInfo[i].u8TTXMagNum
                        && SubtitleMenu[u8Index].u8Page == pTTXInfo->stTTXInfo[i].u8TTXPageNum
                        && memcmp(SubtitleMenu[u8Index].StringCodes, pTTXInfo->stTTXInfo[i].u8lanuage_code, 3) == 0
                        && SubtitleMenu[u8Index].u8SubtitleType == pTTXInfo->stTTXInfo[i].u8TTXType)
                {
                    bExist = TRUE;
                    break;
                }
            }

            if (bExist == FALSE)
            {
                if (pTTXInfo->stTTXInfo[i].u8TTXType == EN_TTX_SUBTITLE)
                    SubtitleMenu[u8SubtitleMenuNum].u8SubtitleType = SUBTITLING_TYPE_TELETEXT;
                else
                    SubtitleMenu[u8SubtitleMenuNum].u8SubtitleType = SUBTITLING_TYPE_TELETEXT_HOH;
                memcpy(SubtitleMenu[u8SubtitleMenuNum].StringCodes, pTTXInfo->stTTXInfo[i].u8lanuage_code, 3);
                SubtitleMenu[u8SubtitleMenuNum].StringCodes[3] = '\0';
                SubtitleMenu[u8SubtitleMenuNum].u8Magazine = pTTXInfo->stTTXInfo[i].u8TTXMagNum;
                SubtitleMenu[u8SubtitleMenuNum].u8Page = pTTXInfo->stTTXInfo[i].u8TTXPageNum;
                SubtitleMenu[u8SubtitleMenuNum].u16PID = pid;
                u8SubtitleMenuNum++;
                gu8TTXSubtitleServiceNum++;
            }
        }
    }
    return gu8TTXSubtitleServiceNum;
}

BOOLEAN MApp_TTX_Subtitle_GetDefaultLang(EN_LANGUAGE lang, U8 *Magazine, U8 *Page, U16 *u16Pid)
{
    U8  i;
    U8  defaultMag = 0xff;
    U8  defaultPage = 0xff;
    U16 defaultPid = MSAPI_DMX_INVALID_PID;

    // find default mag/page
	if(OSD_COUNTRY_SETTING == OSD_COUNTRY_NEWZEALAND)
	{
		if ((SubtitleMenu[u8SubtitleItemSelIdx-1].u8SubtitleType == SUBTITLING_TYPE_TELETEXT || SubtitleMenu[u8SubtitleItemSelIdx-1].u8SubtitleType == SUBTITLING_TYPE_TELETEXT_HOH)
				&&(MApp_GetLanguageBySILanguage(msAPI_SI_GetLanguageByISO639LangCode((U8 *)(SubtitleMenu[u8SubtitleItemSelIdx-1].StringCodes))) == lang))
		{
			*Magazine = SubtitleMenu[u8SubtitleItemSelIdx-1].u8Magazine;
			*Page = SubtitleMenu[u8SubtitleItemSelIdx-1].u8Page;
			*u16Pid = SubtitleMenu[u8SubtitleItemSelIdx-1].u16PID;
			return TRUE;
		}
	}

    for (i = 0; i < u8SubtitleMenuNum; i++)
    {
        if (SubtitleMenu[i].u8SubtitleType != SUBTITLING_TYPE_TELETEXT
                && SubtitleMenu[i].u8SubtitleType != SUBTITLING_TYPE_TELETEXT_HOH)
        {
            continue;
        }

        defaultMag = SubtitleMenu[i].u8Magazine;
        defaultPage = SubtitleMenu[i].u8Page;
        defaultPid = SubtitleMenu[i].u16PID;
        break;
    }

    for (i = 0; i < u8SubtitleMenuNum; i++)
    {
        if (SubtitleMenu[i].u8SubtitleType != SUBTITLING_TYPE_TELETEXT
                && SubtitleMenu[i].u8SubtitleType != SUBTITLING_TYPE_TELETEXT_HOH)
        {
            continue;
        }
        if (MApp_GetLanguageBySILanguage(msAPI_SI_GetLanguageByISO639LangCode((U8 *)(SubtitleMenu[i].StringCodes))) != lang)
        {
            continue;
        }
        *Magazine = SubtitleMenu[i].u8Magazine;
        *Page = SubtitleMenu[i].u8Page;
        *u16Pid = SubtitleMenu[i].u16PID;
        return TRUE;
    }

    // if do not find correct lang ttx subtitle, we will assign the default one
    if (defaultMag != 0xff)
    {
        *Magazine = defaultMag;
        *Page = defaultPage;
        *u16Pid = defaultPid;
        return TRUE;
    }

    return FALSE;
}


BOOLEAN MApp_TTX_Subtitle_GetData(U8 SubtitleIndex, U8 *Magazine, U8 *Page, U16 *u16Pid)
{
    if (SubtitleIndex < u8SubtitleMenuNum)
    {
        //Check if teletext subtitle
        if (SubtitleMenu[SubtitleIndex].u8SubtitleType != SUBTITLING_TYPE_TELETEXT
                && SubtitleMenu[SubtitleIndex].u8SubtitleType != SUBTITLING_TYPE_TELETEXT_HOH)
        {
            return FALSE;
        }

        *Magazine = SubtitleMenu[SubtitleIndex].u8Magazine;
        *Page = SubtitleMenu[SubtitleIndex].u8Page;
        *u16Pid = SubtitleMenu[SubtitleIndex].u16PID;

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

#if(ENABLE_TTX)
void MAPP_TTX_SUBTITLE_ONOFF(BOOLEAN bOn)
{
    if(bOn)
    {
        MApp_TTX_TeletextCommand(TTX_SUBTITLE_TTX_ON);

    }
    else
    {
        MApp_TTX_TeletextCommand(TTX_TV);
    }
}
#endif

BOOLEAN MApp_Subtitle_ParsePMT(void)
{
    U8  u8i = 0;
    U8  u8PMTLen = 0;
    U8  u8ServiceNumCnt;
    U16 u16PID = 0;

    if (SubtitleSamePIDCnt > 1)
    {
        u8ServiceNumCnt = u8DVBSubtitleServiceNum;
    }
    else
    {
        u8ServiceNumCnt = 0;
        u8DVBSubtitleServiceNum = 0;
    }

    u16PID = ((pu8ElementaryPID[0] & 0x1f) << 8) | pu8ElementaryPID[1];
    u8PMTLen = pu8SubtitleDescriptor[1];

    if (pu8SubtitleDescriptor[0] == TAG_SbD)   // 0x59
    {
        pu8SubtitleDescriptor += 2 ;// Point to the first character of the language code
        for (u8i = 0 ; (u8i < (u8PMTLen / SIZE_OF_PMT_NODE)) && (u8i < MAX_SUBTITLE_OPTIONS) ; u8i++)
        {
            DVBSubtitleServices[u8i + u8ServiceNumCnt].u16PID = u16PID;
            memcpy(DVBSubtitleServices[u8i + u8ServiceNumCnt].StringCodes, pu8SubtitleDescriptor + u8i * SIZE_OF_PMT_NODE, 3);
            DVBSubtitleServices[u8i + u8ServiceNumCnt].StringCodes[3] = '\0';
            DVBSubtitleServices[u8i + u8ServiceNumCnt].u8SubtitleType         = (SUBTITLING_TYPE)pu8SubtitleDescriptor[3 + u8i * SIZE_OF_PMT_NODE];
            DVBSubtitleServices[u8i + u8ServiceNumCnt].u16Composition_Page_id = (pu8SubtitleDescriptor[4 + u8i * SIZE_OF_PMT_NODE] << 8) | pu8SubtitleDescriptor[5 + u8i * SIZE_OF_PMT_NODE];
            DVBSubtitleServices[u8i + u8ServiceNumCnt].u16Ancillary_Page_id   = (pu8SubtitleDescriptor[6 + u8i * SIZE_OF_PMT_NODE] << 8) | pu8SubtitleDescriptor[7 + u8i * SIZE_OF_PMT_NODE];
            u8DVBSubtitleServiceNum++;
        }

        MApp_Subtitle_OrgnizeServiceTbl();

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApp_Subtitle_OrgnizeServiceTbl()
/// @brief \b Function \b Description : Orgnize Service Table
///
/// @param <IN>        \b None :
/// @param <OUT>       \b None :
/// @param <RET>       \b None :
////////////////////////////////////////////////////////////////////////////////
void MApp_Subtitle_OrgnizeServiceTbl(void)
{
    U8 u8i, u8TTXIdx = 0;

    if (u8DVBSubtitleServiceNum > 0)
    {
        for (u8i = 0 ; u8i < u8DVBSubtitleServiceNum; u8i++)
        {
            RET_SBTL_SERVICE_SEARCH ret = MApp_Subtitle_FindSubtitleServices(u8i, &u8TTXIdx);

            /* NOT FOUND, Add into the menu. */
            if (SBTL_SERVICE_NOT_FOUND == ret)
            {
                memcpy(SubtitleMenu[u8SubtitleMenuNum].StringCodes, DVBSubtitleServices[u8i].StringCodes, 4);
                SubtitleMenu[u8SubtitleMenuNum].u8SubtitleType = DVBSubtitleServices[u8i].u8SubtitleType;
            #if ENABLE_CHECK_SUBTITLE_PID
                SubtitleMenu[u8SubtitleMenuNum].u16PID = DVBSubtitleServices[u8i].u16PID;
            #endif
                u8SubtitleMenuNum++;
            }
		#if 0
            /* Duplicate TTX Found, replace it. For nordic countries only */
            else if (SBTL_SERVICE_TTX_FOUND == ret)
            {
			#if (ENABLE_SBTVD_BRAZIL_APP==0)
                if (IS_NORDIC_COUNTRY(OSD_COUNTRY_SETTING))
                {
                    memcpy(SubtitleMenu[u8TTXIdx].StringCodes, DVBSubtitleServices[u8i].StringCodes, 4);
                    SubtitleMenu[u8TTXIdx].u8SubtitleType = DVBSubtitleServices[u8i].u8SubtitleType;
                }
			#endif
            }
		#endif
        }
        //bSubtitlePIDUpdatedByPMT = TRUE;
    }
#if (DUMP_PID)
    printf("======== DVB subtitle services ========\n");
    for (u8i = 0 ; u8i < u8DVBSubtitleServiceNum; u8i++)
    {
        printf("[%bx] : (%x,%s,%bx,%x,%x)\n", u8i, DVBSubtitleServices[u8i].u16PID, DVBSubtitleServices[u8i].StringCodes, DVBSubtitleServices[u8i].u8SubtitleType, DVBSubtitleServices[u8i].u16Composition_Page_id, DVBSubtitleServices[u8i].u16Ancillary_Page_id);
    }
    printf("u8DVBSubtitleServiceNum : %bx", u8DVBSubtitleServiceNum);
    printf("============ subtitle menu ============\n");
    for (u8i = 0 ; u8i < u8SubtitleMenuNum; u8i++)
    {
        printf("[%bx] : (%bx, %s)\n", u8i, SubtitleMenu[u8i].u8SubtitleType, SubtitleMenu[u8i].StringCodes);
    }
    printf("u8SubtitleMenuNum : %bx\n", u8SubtitleMenuNum);
#endif
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApp_Subtitle_Get_SubtitleOSDState()
/// @brief \b Function \b Description : Get Subtitle on/off status
///
/// @param <IN>        \b None :
/// @param <OUT>       \b None :
/// @param <RET>       \b BOOLEAN : FALSE if Subtitle turn off
////////////////////////////////////////////////////////////////////////////////
U8 MApp_Subtitle_Get_SubtitleOSDState(void)
{
    return _bSubtitleOn;
}

static BOOLEAN MApp_Subtitle_Data_Exit_Check(void)
{
    U8  u8Conterted = MApp_Subtitle_GetServiceIdx(u8SubtitleIdx);

#if (MHEG5_ENABLE)
#if CIPLUS_MHEG_1_3
    if (msAPI_MHEG5_GoMHEGWhenSubtitleOn() == 2)    //  subtitle exits when mheg runs only
    {
         return TRUE;
    }
#endif
#endif

    if((0xff == u8Conterted)
    || (u8Conterted >= MAX_SUBTITLE_SERVICE_NUM)
    || (u8SubtitleMenuNum <= 0)
    || (!IsDTVInUse() && !IsStorageInUse())
    || (IsDTVInUse() && (!stGenSetting.g_SysSetting.fEnableSubTitle))
#if (MHEG5_ENABLE && MHEG5_WITH_SUBTITLE)
    || (u8KeyCode == KEY_CLOCK)
#else
    || ((u8KeyCode == KEY_TTX) || (u8KeyCode == KEY_CLOCK) || (u8KeyCode == KEY_EXIT)
       ||(((u8KeyCode == KEY_CHANNEL_PLUS) || (u8KeyCode == KEY_CHANNEL_MINUS))
          &&MApp_TopStateMachine_GetTopState()==STATE_TOP_CHANNELCHANGE/*EXIT_GOTO_CHANNELCHANGE*/
         )
       )
#endif
#if ENABLE_DMP
#if (ENABLE_SUBTITLE_DMP)
    || (IsStorageInUse() && (FALSE == msAPI_MpegSP_Get_Show_Status()))
#endif
#endif
#if (ENABLE_PIP)
    || (MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
#endif
       )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

#if ( SUBTITLE_WITH_OSD )

static BOOLEAN MApp_Subtitle_Display_Exit_Check(void)
{
    VDEC_DispInfo _stVidInfo;

    if (MApp_Subtitle_Data_Exit_Check() || _bSubtitleIdxUpdatedByUI)//!stGenSetting.g_SysSetting.fEnableSubTitle)
    {
        _bSubtitleIdxUpdatedByUI = FALSE;
        return TRUE;
    }

#if 0//ENABLE_CI
    if (EN_MODULE_INITIALIZING == msAPI_CI_GetCardState())
        return TRUE;
#endif
#if (MHEG5_ENABLE)
#if CIPLUS_MHEG_1_3
    if (msAPI_MHEG5_GoMHEGWhenSubtitleOn() == 2)    //  subtitle exits when mheg runs only
    {
         return TRUE;
    }
#endif
#endif
    if (IsDTVInUse())
    {
        if (enFrotEndLockStatus != FRONTEND_LOCK) // it should check frontend status, not signal status
        {
#if ENABLE_PVR
            if (MApp_PVR_IsPlaybacking())
            {
                return FALSE;
            }
            else
#endif
            {
                return TRUE;
            }
        }
#if (ENABLE_PIP)
        if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
        {
            return TRUE;
        }
#endif
    }

    if (
    #if (MHEG5_ENABLE && (MHEG5_WITH_SUBTITLE==0))
        (u8KeyCode == KEY_TTX           ) ||
    #endif
        (u8KeyCode == KEY_POWER         ) ||
        (u8KeyCode == KEY_CHANNEL_PLUS  ) ||
        (u8KeyCode == KEY_CHANNEL_MINUS ) ||
        (u8KeyCode == KEY_CHANNEL_RETURN) ||
        (u8KeyCode == KEY_ZOOM)           ||
        ((u8KeyCode >= KEY_0) && (u8KeyCode <= KEY_9)))
    {
        return TRUE;
    }

#if (MHEG5_ENABLE && MHEG5_WITH_SUBTITLE)
    if (msAPI_MHEG5_GetSubtitleMode()==0)
    {
        return TRUE;
    }
#endif


    if(msAPI_VID_GetVidInfo(&_stVidInfo))
    {
        if ((_stVidInfo.u16HorSize != _u16_video_width) || (_stVidInfo.u16VerSize != _u16_video_height))
        {
            return TRUE;
        }
    }

    return FALSE;

}

#endif

BOOLEAN MApp_Subtitle_Exit_Check(void)
{
    VDEC_DispInfo _stVidInfo;

    if (IsDTVInUse()) // following check only for DTV input src
    {
#if ENABLE_CI
        if (msAPI_CI_Polling() || MApp_Scramble_GetCurStatus() || (!MApp_TV_IsProgramRunning()))
        {
            return TRUE;
        }
#endif
        if (enFrotEndLockStatus != FRONTEND_LOCK) // it should check frontend status, not signal status
        {
#if ENABLE_PVR
            if (MApp_PVR_IsPlaybacking())
            {
                return FALSE;
            }
            else
#endif
            {
                return TRUE;
            }
        }
#if (ENABLE_PIP)
        if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
        {
            return TRUE;
        }
#endif

    }

#if (MHEG5_ENABLE && MHEG5_WITH_SUBTITLE)
    if (msAPI_MHEG5_GetSubtitleMode()==0)
    {
        return TRUE;
    }
#endif


    if (u8KeyCode != KEY_NULL)
        return TRUE;

    if(msAPI_VID_GetVidInfo(&_stVidInfo))
    {
        if ((_stVidInfo.u16HorSize != _u16_video_width) || (_stVidInfo.u16VerSize != _u16_video_height))
        {
            return TRUE;
        }
    }

    return FALSE;

}


////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApp_Subitle_GetCurPID()
/// @brief \b Function \b Description : Get Subtitle PID
///
/// @param <IN>        \b None :
/// @param <OUT>       \b None :
/// @param <RET>       \b U16 : return Current Subtitle PID
////////////////////////////////////////////////////////////////////////////////
U16 MApp_Subitle_GetCurPID(void)
{
    return _u16CurSubtitlePID;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApp_Subtitle_Main()
/// @brief \b Function \b Description : Main Subtitle State Machine
///
/// @param <IN>        \b None :
/// @param <OUT>       \b None :
/// @param <RET>       \b EN_RET : return Subtitle State
////////////////////////////////////////////////////////////////////////////////
EN_RET MApp_Subtitle_Main(void)
{
#if 0//( SUBTITLE_WITH_OSD )
#if ENABLE_CI
    E_CARD_STATE cstatus;
#endif
#endif
#if(ENABLE_OSD_SUBTITLE_EXCLUSIVE == ENABLE)
		if(!_bShowSubtitle)
		{

            if(_enSubtitleState == STATE_SUBTITLE_DECODING)
            {
#if ( SUBTITLE_WITH_OSD )
                if (MApp_Subtitle_Display_Exit_Check())
                {
                    MApp_Subtitle_Switch2IP();
#else
                if (MApp_Subtitle_Exit_Check() == TRUE)
                {
#endif
                    MApp_Subtitle_Exit();
                    _enSubtitleState = STATE_SUBTITLE_INIT;
                    _enSubtitleRetVal = EXIT_SUBTITLE_EXIT;
                }
            }

			return EXIT_SUBTITLE_EXIT;
		}
#endif

    switch (_enSubtitleState)
    {
        case STATE_SUBTITLE_INIT:

            _enSubtitleState = STATE_SUBTITLE_INIT;
            _enSubtitleRetVal = EXIT_SUBTITLE_EXIT;

#if ( SUBTITLE_WITH_OSD )

            if (_u16CurSubtitlePID == MSAPI_DMX_INVALID_PID
                || MApp_Subtitle_Data_Exit_Check()
                || (IsDTVInUse()
                && enFrotEndLockStatus != FRONTEND_LOCK // it should check frontend status, not signal status
#if ENABLE_PVR
                && (!MApp_PVR_IsPlaybacking())
#endif
#if (ENABLE_PIP)
                && (MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
#endif

                       )
               )
            {
                break;
            }

#if ENABLE_TTX
            if (MApp_TTX_IsTeletextOn())
            {
                break;
            }
#endif

#if 0//ENABLE_CI
            cstatus = msAPI_CI_GetCardState();
            if (EN_MODULE_INITIALIZING == cstatus)
            {
                break;
            }
#endif

#if (MHEG5_ENABLE)
        #if (MHEG5_WITH_SUBTITLE==0)
            if (MApp_MHEG5_CheckGoMHEG5Process()
            #if CIPLUS_MHEG_1_3
                && (msAPI_MHEG5_GoMHEGWhenSubtitleOn() ==0) //  disable mheg when only subtitle runs
            #endif
                )
            {
                MApi_MHEG5_Disable(EN_MHEG5_DM_DISABLE_WITH_AUTOBOOT_LATER);
                break;
            }
        #endif
#endif

            // check if program is scramble and no video, it should not show subtitle.
            if(MApp_SI_CheckCurProgScramble() && enMVDVideoStatus == MVD_BAD_VIDEO)
            {
                break;
            }

            MApp_Subtitle_Switch2IP();
            if (!MApp_Subtitle_Initial())
            {
                break;
            }
            MApp_Subtitle_Switch2OP();
#else
            if (u8SubtitleMenuNum > 0)
            {
                if (!MApp_Subtitle_Initial())
                {
                    break;
                }
            }
            else
                break;
#endif
            _enSubtitleState = STATE_SUBTITLE_DECODING;
            _enSubtitleRetVal = EXIT_SUBTITLE_DECODING;

            break;

        case STATE_SUBTITLE_DECODING:

            #if ENABLE_AUTOTEST
            if (g_bAutobuildDebug)
            {
                if((stGenSetting.g_SysSetting.fEnableSubTitle == 1) && (MApp_Subtitle_IsRunning() == 1))
                {
                    printf("132_Subtitle_on\n");
                    if(u8SubtitleIdx == 1)
                    {
                        printf("134_2rd_Subtitle\n");
                    }
                    if(u8SubtitleIdx == 2)
                    {
                        printf("135_3rd_Subtitle\n");
                    }
                }
            }
            #endif

#if ( SUBTITLE_WITH_OSD )
            if (MApp_Subtitle_Display_Exit_Check())
            {
                MApp_Subtitle_Switch2IP();
#else
            if (MApp_Subtitle_Exit_Check() == TRUE)
            {
#endif
                MApp_Subtitle_Exit();
                _enSubtitleState = STATE_SUBTITLE_INIT;
                _enSubtitleRetVal = EXIT_SUBTITLE_EXIT;

                #if ENABLE_AUTOTEST
                if (g_bAutobuildDebug)
                {
                    if((stGenSetting.g_SysSetting.fEnableSubTitle!=1)||(MApp_Subtitle_IsRunning()!=1))
                    {
                        printf("133_Subtitle_off\n");
                    }
                }
                #endif
                    break;
                }
            _enSubtitleRetVal = EXIT_SUBTITLE_DECODING;
            _enSubtitleState = STATE_SUBTITLE_DECODING;
            if((*MApp_Dmx_GetFid(EN_PES_FID) != MSAPI_DMX_INVALID_FLT_ID)&&(FALSE == MApp_Dmx_GetMonitorStatus(EN_MONITOR_TABLE_ALL)))
            {
                msAPI_DMX_Proc(*MApp_Dmx_GetFid(EN_PES_FID));
            }
            U32 u32STC = MApp_Subtitle_GetSTC();
            u32STC = u32STC - VIDEO_SYNC_DELAY;
            if (msAPI_Subtitle_CheckPTS(u32STC))
            {
#if ( SUBTITLE_WITH_OSD )
                MApp_Subtitle_Switch2IP();
                msAPI_Subtitle_Decoder_Main();
                MApp_Subtitle_Switch2OP();
#else
                msAPI_Subtitle_Decoder_Main();
#endif
                #if ENABLE_AUTOTEST
                if (g_bAutobuildDebug)
                {
                    printf("131_Normal_Play\n");
                }
                #endif
                bEnableSubtitleTimeoutMonitor = TRUE;
                u32SubtitleTimeOut = msAPI_Timer_GetTime0();
            }
            break;

        default:
            _enSubtitleState  = STATE_SUBTITLE_INIT;
            _enSubtitleRetVal = EXIT_SUBTITLE_EXIT;
            break;
    }
    return _enSubtitleRetVal;
}

BOOLEAN MApp_Subtitle_IsRunning(void)
{
    if (_enSubtitleState == STATE_SUBTITLE_DECODING)
        return TRUE;
    else
        return FALSE;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApp_Subtitle_PID_Monitor()
/// @brief \b Function \b Description : Monitor Subtitle PID
///
/// @param <IN>        \b None :
/// @param <OUT>       \b None :
/// @param <RET>       \b None :
////////////////////////////////////////////////////////////////////////////////
void MApp_Subtitle_PID_Monitor()
{
    U8  u8Conterted;
#if ENABLE_ISDBT  //Mantis fixed
    if(IsISDBTInUse())
        return;
#endif
    u8Conterted = MApp_Subtitle_GetServiceIdx(u8SubtitleIdx);

    if (MApp_Subtitle_Data_Exit_Check())
    {
#if (1)//(MEMORY_MAP == MMAP_64MB)//mheg5/subtitle co-buffer
#if (MHEG5_ENABLE)
        if((_u16CurSubtitlePID != MSAPI_DMX_INVALID_PID)&&(enCheckMHEGLoadingStatus == EN_MHEG5_WAIT) && (MApp_MHEG5_DsmccTime_Get()==0))
        {
            enCheckMHEGLoadingStatus = EN_MHEG5_MONITOR;
         }
#endif
#endif
        _u16CurSubtitlePID = MSAPI_DMX_INVALID_PID;
        _u16CPID           = MSAPI_DMX_INVALID_PID;
        _u16APID           = MSAPI_DMX_INVALID_PID;

        MApp_Dmx_PES_Stop();
        return ;
    }
    // reset dmux pid when pmt version update || user selection ||aspectRatio changed
    //if (( bSubtitlePIDUpdatedByPMT ) remove it to show 2nd scene of Si02-SIT111
    //if (( _bSubtiteIdxUpdatedByUI )  removed  to show subtitle when index changed but PID not change, NZDTG Si07-SIT7
    if ((_bForceUpdatePID                                                             )  ||
        (_u16CurSubtitlePID != DVBSubtitleServices[u8Conterted].u16PID                )  ||
        (_u16CPID           != DVBSubtitleServices[u8Conterted].u16Composition_Page_id)  ||
        (_u16APID           != DVBSubtitleServices[u8Conterted].u16Ancillary_Page_id  ))
    {
    #if ENABLE_FileIn_PMTMonitor
        _RecordUpdateAllPIDs = TRUE;
	#endif
#if defined (__C51__)
        U16 u16SliceWindowAddr = MDrv_Sys_GetXdataWindow1Base();
#endif
#if (DUMP_PID)
        printf("BG : %s(%x, %x,  %x)\n", DVBSubtitleServices[u8Conterted].StringCodes, DVBSubtitleServices[u8Conterted].u16PID, DVBSubtitleServices[u8Conterted].u16Composition_Page_id, DVBSubtitleServices[u8Conterted].u16Ancillary_Page_id);
#endif
        MApp_Dmx_PES_Stop();

    #if(ENABLE_API_MMAP_GET_BUF) // Use MMAP API
        U32 u32SubtitleBufAddr = 0, u32SubtitleBufSize = 0;
        msAPI_MMAP_Get_BufInfo(E_BUFID_SUBTITLE, &u32SubtitleBufAddr, &u32SubtitleBufSize );
        msAPI_Subtitle_Init_Queue(_PA2VA(u32SubtitleBufAddr), u32SubtitleBufSize);
    #else
        msAPI_Subtitle_Init_Queue(_PA2VA(((SUBTITLE_MEMORY_TYPE & MIU1) ? (SUBTITLE_ADR | MIU_INTERVAL) : (SUBTITLE_ADR))), SUBTITLE_LEN);
    #endif

        msAPI_Subtitle_SetPageIDs(DVBSubtitleServices[u8Conterted].u16Composition_Page_id, DVBSubtitleServices[u8Conterted].u16Ancillary_Page_id);

        MApp_Subtitle_Open_Filter(DVBSubtitleServices[u8Conterted].u16PID);

        _u16CurSubtitlePID = DVBSubtitleServices[u8Conterted].u16PID;
        _u16CPID           = DVBSubtitleServices[u8Conterted].u16Composition_Page_id;
        _u16APID           = DVBSubtitleServices[u8Conterted].u16Ancillary_Page_id;
        _bForceUpdatePID   = FALSE;
    }
}

#if ENABLE_PVR
void MApp_Subtitle_SetInvalidPID()
{
#if (1)//(MEMORY_MAP == MMAP_64MB)//mheg5/subtitle co-buffer
#if (MHEG5_ENABLE)
    if((_u16CurSubtitlePID != MSAPI_DMX_INVALID_PID)&&(enCheckMHEGLoadingStatus == EN_MHEG5_WAIT) && (MApp_MHEG5_DsmccTime_Get()==0))
    {
        enCheckMHEGLoadingStatus = EN_MHEG5_MONITOR;
    }
#endif
#endif
    _u16CurSubtitlePID = MSAPI_DMX_INVALID_PID;
    _u16CPID           = MSAPI_DMX_INVALID_PID;
    _u16APID           = MSAPI_DMX_INVALID_PID;
    MApp_Dmx_PES_Stop();
}
#endif

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApp_Subtitle_Clear_ServiceData(BOOLEAN bUpdate)
/// @brief \b Function \b Description : Clear Service Data
///
/// @param <IN>        \b None :
/// @param <OUT>       \b None :
/// @param <RET>       \b None :
////////////////////////////////////////////////////////////////////////////////
void MApp_Subtitle_Clear_ServiceData(BOOLEAN bUpdate)
{
    memset(SubtitleMenu, 0, sizeof(SUBTITLE_MENU)*MAX_SUBTITLE_SERVICE_NUM);
    u8DVBSubtitleServiceNum = 0;
    u8SubtitleMenuNum = 0;

    // If clear the servce, pid is not the same as before
    if(bUpdate)
    {
        MApp_Subtitle_PID_Updated();
    }
    gu8TTXSubtitleServiceNum = 0;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApp_Subtitle_Force_Exit()
/// @brief \b Function \b Description : Force Exit Subtitle
///
/// @param <IN>        \b None :
/// @param <OUT>       \b None :
/// @param <RET>       \b None :
////////////////////////////////////////////////////////////////////////////////
void MApp_Subtitle_Force_Exit(void)
{
    _u16CurSubtitlePID = MSAPI_DMX_INVALID_PID;
    MApp_Dmx_PES_Stop();
    MApp_Subtitle_Clear_ServiceData(TRUE);
    MApp_Subtitle_Exit();
    _enSubtitleState = STATE_SUBTITLE_INIT;
    _enSubtitleRetVal = EXIT_SUBTITLE_EXIT;
}

void MApp_Subtitle_Exit_ForAutoScart(void)
{
    MApp_Subtitle_Force_Exit();
    MApp_TopStateMachine_SetTopState(STATE_TOP_DIGITALINPUTS);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApp_Subtitle_PID_Updated()
/// @brief \b Function \b Description : Update Subtitle PID
///
/// @param <IN>        \b None :
/// @param <OUT>       \b None :
/// @param <RET>       \b None :
////////////////////////////////////////////////////////////////////////////////
void MApp_Subtitle_PID_Updated()
{
    _bSubtitleIdxUpdatedByUI = TRUE;
    _bForceUpdatePID = TRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MApp_Subtitle_TimeOut_Clear()
/// @brief \b Function \b Description : Clear Subtitle Timeout
///
/// @param <IN>        \b None :
/// @param <OUT>       \b None :
/// @param <RET>       \b None :
////////////////////////////////////////////////////////////////////////////////
void MApp_Subtitle_TimeOut_Clear()
{
#if SUBTITLE_WITH_OSD
    MApp_Subtitle_Switch2IP();
    msAPI_Subtitle_Renderer_Clear();
    MApp_Subtitle_Switch2OP();
#else
    msAPI_Subtitle_Renderer_Clear();
#endif
}

//****************************************************************************
/// re-arrange DVB/EBU subtitle data
/// @param bDVBSub \b IN: enable/disable dvb subtitle
/// -TRUE: enable
/// -FALSE: disable
/// @param bEBUSub \b IN: enable/disable ebu subtitle
/// -TRUE: enable
/// -FALSE: disable
//****************************************************************************
U8 MApp_Subtitle_ReArrange(U32 u32ValidIndex, U8 u8CurIdx)
{
    U8  i, newIdx = 0, ebuSubNum = 0;
    U8 u8ValidIndex = 0, u8InValidIndex, u8Total = 0;
    SUBTITLE_MENU TmpSubtitleServices[MAX_SUBTITLE_SERVICE_NUM];
    memset(TmpSubtitleServices, 0, sizeof(SUBTITLE_MENU)*MAX_SUBTITLE_SERVICE_NUM);
    for (i = 0; i < MAX_SUBTITLE_SERVICE_NUM; i++)
    {
        if (SubtitleMenu[i].u8SubtitleType)
        {
            u8Total++;
        }
    }
    u8InValidIndex = u8Total - 1;
    for (i = 0; i < u8Total; i++)
    {
        if ((GETBIT(u32ValidIndex, i)) == 0)
        {
            CLRBIT(gCurValidSubtitleIndex, u8InValidIndex);
            TmpSubtitleServices[u8InValidIndex] = SubtitleMenu[i];
            u8InValidIndex--;
        }
        else
        {
            if (u8CurIdx == (i + 1))
            {
                newIdx = u8ValidIndex + 1;
            }
            SETBIT(gCurValidSubtitleIndex, u8ValidIndex);
            TmpSubtitleServices[u8ValidIndex] = SubtitleMenu[i];
            u8ValidIndex++;
            if ((SubtitleMenu[i].u8SubtitleType == SUBTITLING_TYPE_TELETEXT_HOH) || (SubtitleMenu[i].u8SubtitleType == SUBTITLING_TYPE_TELETEXT))
            {
                ebuSubNum++;
            }

        }
    }
    if (u8ValidIndex == 0)return u8CurIdx;
    memcpy(SubtitleMenu, TmpSubtitleServices, sizeof(SUBTITLE_MENU)*MAX_SUBTITLE_SERVICE_NUM);
    u8SubtitleMenuNum = u8ValidIndex;
    gu8TTXSubtitleServiceNum = ebuSubNum;
    return newIdx;
}

void MApp_Subtitle_SetValidIndex(U8 type, U8* lang, U32 *pu32Validndex)
{
    U8  i;
    for (i = 0; i < MAX_SUBTITLE_SERVICE_NUM; i++)
    {
        if (((SubtitleMenu[i].u8SubtitleType == type) || ((type == SUBTITLING_TYPE_NORMAL_NO) && (SubtitleMenu[i].u8SubtitleType >= SUBTITLING_TYPE_NORMAL_NO))) && (memcmp(SubtitleMenu[i].StringCodes, lang, 3) == 0))
        {
            SETBIT(*pu32Validndex, i);
        }
    }
}

/******************************************************************************/
/// Callback function of PES monitor
/***************************************************************************/
static void _MApp_Subtitle_PES_Cb(U8 u8FID, DMX_EVENT enEvent)
{
    U8  pbuff[PES_HEADER_LEN];
    U32 u32CopiedLen = 0, u32RmnSize ;
//    U16 SliceWindowAddr;
    static U16 _u16PesLength;
    static U32 _u32SDRAMAddress;
    static U32 u32SDRAMAddress;
    static U32 u32PTSLow;
    GET_PES_STATE RetState = SBTL_GET_PES_STATE_TOBECONTINUED;
    U32 u32BufferAddress = msAPI_Subtitle_GetDemuxBuffer();
    MSAPI_DMX_FILTER_STATUS enStatus;
#if ( PRINT_HEADER == 1) || ( VERBOSE == 1 )

    U16 u16PesIndex;

#endif
    enStatus = (MSAPI_DMX_FILTER_STATUS)enEvent;
    //u8FID = 0x00;// ignore the warning message
//printf("_MApp_Subtitle_PES_Cb %d %d\n",u8FID,enStatus);
//    if (( enStatus == MSAPI_DMX_FILTER_STATUS_REQUESTMEET) || (enStatus == MSAPI_DMX_FILTER_STATUS_PESAVAILABLE ))
    if (enStatus == MSAPI_DMX_FILTER_STATUS_PESAVAILABLE)
    {
        if (_u16PesDataLength == 0)
        {
            // SDRAM --> SDRAM
            //u32CopiedLen = msAPI_DMX_CopyPes(u8FID, (U32)u32BufferAddress, PES_HEADER_LEN, FALSE);
            MApi_DMX_CopyData(u8FID, (U8*)u32BufferAddress, PES_HEADER_LEN, &u32CopiedLen, &u32RmnSize, NULL) ;
            if (u32CopiedLen > 0)
            {
                // SDRAM --> XDATA
                memcpy(pbuff, (U8 *)u32BufferAddress, PES_HEADER_LEN);
#if ( PRINT_HEADER == 1) || ( VERBOSE == 1)

                printf("\n\n");
                for (u16PesIndex = 0 ; u16PesIndex < u32CopiedLen ; u16PesIndex++)
                {
                    printf("%02x ", *(pbuff + u16PesIndex));
                }
#endif
                _u16PesDataLength = pbuff[4];
                _u16PesDataLength = _u16PesDataLength << 8;
                _u16PesDataLength |= pbuff[5];
                _u16PesDataLength += 6;                  //plus header

                u32SDRAMAddress = msAPI_Subtitle_Queue_GetSDRAMAddress(_u16PesDataLength);
                _u32SDRAMAddress = u32SDRAMAddress;
                _u16PesLength = _u16PesDataLength;

                u32PTSLow = msAPI_Subtitle_SetPTS(pbuff, MApp_Subtitle_GetSTC());

                // XDATA --> SDRAM
                memcpy((U8 *)u32SDRAMAddress, pbuff, PES_HEADER_LEN);
                _u16PesDataLength -= u32CopiedLen;
                u32SDRAMAddress += u32CopiedLen;
                //[05-4]check header ==================================================//
                if (pbuff[3] != 0xbd)
                {
                    SBTL_ERR(printf("\nMSAPI_DMX: Header is incorrect !!!\n"));
                    _u16PesDataLength = 0;
                    RetState = SBTL_GET_PES_STATE_FAIL;
                }

            }
            else
            {
                SBTL_ERR(printf("\nMSAPI_DMX: Copy pes is failed1 !\n"));
                _u16PesDataLength = 0;
            }

        }
        else if (_u16PesDataLength > PES_BLOCK_LEN)// body
        {
            //u32CopiedLen = msAPI_DMX_CopyPes(u8FID, (U32)u32SDRAMAddress, PES_BLOCK_LEN, FALSE);
            MApi_DMX_CopyData(u8FID, (U8*)(u32SDRAMAddress), PES_BLOCK_LEN, &u32CopiedLen, &u32RmnSize, NULL) ;
            if (u32CopiedLen > 0)
            {

#if ( VERBOSE == 1)

                U8 u8i = 0;

                for (u8i = 0 ; u8i < (u32CopiedLen / PES_HEADER_LEN) ; u8i++)
                {
                    // replace from msAPI_MIU_Copy to memcpy
                    memcpy(pbuff, (U8 *)(u32SDRAMAddress + PES_HEADER_LEN * u8i), PES_HEADER_LEN);
                    printf("\n");

                    for (u16PesIndex = 0 ; u16PesIndex < PES_HEADER_LEN ; u16PesIndex++)
                    {
                        printf("%02x ", *(pbuff + u16PesIndex));
                    }
                }
#endif
                _u16PesDataLength = _u16PesDataLength - u32CopiedLen;
                u32SDRAMAddress += u32CopiedLen;
            }
            else
            {
                SBTL_ERR(printf("MSAPI_DMX: Copy pes is failed2 !\n"));
                _u16PesDataLength = 0;
            }
        }
        else// Tail
        {
            //u32CopiedLen = msAPI_DMX_CopyPes(u8FID, (U32)u32SDRAMAddress, _u16PesDataLength, TRUE);
            MApi_DMX_CopyData(u8FID, (U8*)u32SDRAMAddress, _u16PesDataLength, &u32CopiedLen, &u32RmnSize, NULL) ;
            if (u32CopiedLen > 0)
            {

#if ( VERBOSE == 1)

                U8 u8i = 0;

                for (u8i = 0 ; u8i < (u32CopiedLen / PES_HEADER_LEN) + 1 ; u8i++)
                {
                    // replace from msAPI_MIU_Copy to memcpy
                    memcpy(pbuff, (U8 *)(u32SDRAMAddress + PES_HEADER_LEN * u8i), PES_HEADER_LEN);

                    printf("\n");

                    for (u16PesIndex = 0 ; u16PesIndex < PES_HEADER_LEN ; u16PesIndex++)
                    {
                        printf("%02x ", *(pbuff + u16PesIndex));
                    }
                }
#endif
                if (u32CopiedLen >= _u16PesDataLength)
                {

                    // Push into the queue once the whole PES is copied.
#if ( VERBOSE ==0 )

#if ( SUBTITLE_WITH_OSD )
                    msAPI_Subtitle_Queue_Push(_u32SDRAMAddress, _u16PesLength, u32PTSLow);
#else
                    msAPI_Subtitle_Queue_Push_BG(_u32SDRAMAddress, _u16PesLength, u32PTSLow, (STATE_TOP_SUBTITLE == MApp_TopStateMachine_GetTopState()));
#endif
#endif
                    _u16PesDataLength = 0;
                    RetState = SBTL_GET_PES_STATE_FINISH;
                }
                else
                {
                    _u16PesDataLength -= u32CopiedLen;
                    u32SDRAMAddress += u32CopiedLen;
                }
            }
            else
            {
                SBTL_ERR(printf("MSAPI_DMX: Copy pes is failed3 !\n"));
                _u16PesDataLength = 0;
            }
        }
    }
    else //if (( enStatus == MAPI_DMX_FILTER_STATUS_OK) || (enStatus == MSAPI_DMX_FILTER_STATUS_OVERFLOW ))
    {
        RetState = SBTL_GET_PES_STATE_FAIL;
    }

    if (SBTL_GET_PES_STATE_FAIL == RetState)
    {
        MApp_Dmx_PES_Restart();
    }
}// if

void MApp_Subtitle_Open_Filter(U16 u16PID)
{
    BOOLEAN bFileIn=FALSE;
    #if ENABLE_PVR
    bFileIn = MApp_PVR_IsPlaybacking() ? TRUE : FALSE;
    #endif
    _u16PesDataLength = 0;
#if (1)//(MEMORY_MAP == MMAP_64MB)//mheg5/subtitle co-buffer
#if (MHEG5_ENABLE)
#if CIPLUS_MHEG_1_3
    if (msAPI_MHEG5_GoMHEGWhenSubtitleOn() ==0) //  disable mheg when only subtitle runs
#endif
    {
        MApi_MHEG5_Disable(EN_MHEG5_DM_DISABLE_AND_WAIT);
    }
#endif
#endif
    MApp_Dmx_PES_Monitor(u16PID, _MApp_Subtitle_PES_Cb,bFileIn);
}
/*
void PrintSubtitleInfo(void)
{
    printf( "\n==================================\n");

    printf( "_bSubtitleOn=%bu\n", _bSubtitleOn);

    printf( "u8SubtitleMenuNum=%u\n", u8SubtitleMenuNum);
    printf( "u8SubtitleIdx=%u\n", u8SubtitleIdx);
    printf( "_bSubtitleIdxUpdatedByUI=%bu\n", _bSubtitleIdxUpdatedByUI);
    printf( "_enSubtitleState=%u\n", _enSubtitleState);

    printf( "_u16CurSubtitlePID=%u\n", _u16CurSubtitlePID);
    printf( "_u16PesDataLength=%u\n", _u16PesDataLength);
    printf( "_bForceUpdatePID=%bu\n", _bForceUpdatePID);
    printf( "_u16CPID=%u\n", _u16CPID);
    printf( "_u16APID=%u\n", _u16APID);

    if( MApp_Dmx_GetFid(EN_PES_FID) )
        printf( "_u8PesFID=%u\n", *MApp_Dmx_GetFid(EN_PES_FID));

}
*/
#if(ENABLE_OSD_SUBTITLE_EXCLUSIVE == ENABLE)
void MApp_Subtitle_SetShowStatus(BOOLEAN bShowStatus)
{
#if(ENABLE_TTX)

    _bShowSubtitle = bShowStatus;
	if(!bShowStatus)
    {
       if(MApp_TTX_IsTeletextOn()&&stGenSetting.g_SysSetting.fEnableTTXSubTitle)
       {
           MAPP_TTX_SUBTITLE_ONOFF(FALSE);
       }
       else
       {
	       MApp_Subtitle_Exit();
       }
    }
    else
    {
        if((stGenSetting.g_SysSetting.fEnableTTXSubTitle)&&(!MApp_TTX_IsTeletextOn()))
        {
            MAPP_TTX_SUBTITLE_ONOFF(TRUE);
        }
    }
#else

	_bShowSubtitle = bShowStatus;
	if(!bShowStatus)
	       MApp_Subtitle_Exit();

#endif
}
EN_SUBTITLE_STATE MApp_Subtitle_GetStatus(void)
{
	return _enSubtitleState;
}

BOOLEAN MApp_Subtitle_GetShowStatus(void)
{
    return _bShowSubtitle;
}


void MApp_ReMoveUnShowSubtitle(void)
{
    U32 u32STC = MApp_Subtitle_GetSTC();
    if(u32STC > VIDEO_SYNC_DELAY)
    {
        u32STC = u32STC - VIDEO_SYNC_DELAY;
        msAPI_Subtitle_Remove(u32STC);
    }
}

#endif

void MApp_SetSubtitleSelIdx(BOOLEAN bSelIdx)
{
    bSubtitleSelIdxInvaild = bSelIdx;
}

BOOLEAN MApp_GetSubtitleSelIdx(void)
{
    return bSubtitleSelIdxInvaild;
}


#undef MAPP_SUBTITLE_C
#endif // SUBTITLE
