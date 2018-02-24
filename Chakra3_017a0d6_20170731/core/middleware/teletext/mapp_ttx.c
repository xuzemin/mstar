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
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
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

#define MAPP_TTX_C

/******************************************************************************/
/*                            Header Files                                    */
/******************************************************************************/
#include <string.h>
#include <stdio.h>
#include "Board.h"
#include "debug.h"

#if ENABLE_TTX
#include "sysinfo.h"
#include "MsTypes.h"
#include "Panel.h"
#include "msAPI_audio.h"
#include "msAPI_Timer.h"
#include "apiGOP.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "MApp_GlobalSettingSt.h"
#include "apiXC_Sys.h"
#include "msAPI_Tuning.h"
#include "msAPI_TTX.h"
#include "mapp_ttx.h"
#include "msAPI_VD.h"
#include "MApp_UiMenuDef.h"
#include "MApp_PCMode.h"
#include "MApp_GlobalFunction.h"
#include "msAPI_CNI.h"
#include "InfoBlock.h"
#include "MApp_Scaler.h"
#include "MApp_XC_PQ.h"
#include "MApp_VDMode.h"
#include "MApp_ZUI_Main.h"
#include "MApp_SaveData.h"
#include "MApp_ChannelChange.h"
#include "MApp_TV.h"
#if(MHEG5_ENABLE)
#include "MApp_MHEG5_Main.h"
#endif
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"
#include "MApp_MVDMode.h"
#if ENABLE_TTX_ACI
#include "MApp_Main.h"
#include "MApp_ATV_Scan.h"
#include "msAPI_FreqTableATV.h"
#include "msAPI_ATVSystem.h"
#include "MApp_TopStateMachine.h"
#endif

#if ENABLE_DTV
#include "mapp_si.h"
#include "MApp_Subtitle.h"
#endif

#if ENABLE_PVR
#include "MApp_PVR.h"
#endif

#include "apiPNL.h" //panel module
#include "Panel.h"

#include "MApp_ZUI_ACTcoexistWin.h"

#include "TT_PacketBuffer.h"

//=====================================================


#define DEBUG_APP_TTX(x)    //x



typedef enum
{
    TTX_RENDERING_PHASE_OFF = 1 << 0,
    TTX_RENDERING_PHASE_NORMAL = 1 << 1,
    TTX_RENDERING_PHASE_MIX = 1 << 2,
    TTX_RENDERING_PHASE_VIDEO_TTX = 1 << 3
}TTX_RenderingPhase;

// enable or disable TTX double buffer drawing

#define TTX_TRAN_COLOR_KEY 0x7C3F
#define TTX_TRAN_COLOR  0xFF08FF

#define TTX_OSD_MARGINV 10
#define TTX_OSD_MARGINH  8

#define TTX_DISPLAY_NORMAL   0 // TTX, OFF
#define TTX_DISPLAY_PAT     1  // TTX, MIX_MODE, VIDEO_TTX, OFF
#define TTX_DISPLAY_3MODE   2   // TTX, MIX_MODE, OFF
#define TTX_DISPLAY_MODE    TTX_DISPLAY_NORMAL
/******************************************************************************/
/*                              Macro                                         */
/******************************************************************************/
#define TTX_CLOCK_MODE_TIMEOUT  5000    // TTX Time out spec is 5sec.
#define TTX_SHOWNOSUBPAGE_TIMEOUT  2000
/******************************************************************************/
/*                               Local                                        */
/******************************************************************************/
U32 g_u32MonitorTTXClockTimer;
U32 g_u32MonitorShowNoSubpageTimer;

static EN_TELETEXT_MODE _enTTXMode = TTX_MODE_NORMAL; // use this flag to let TTX & TTX clock mutual exclusive

static TTX_RenderingPhase _RenderingPhase = TTX_RENDERING_PHASE_OFF;

static U16 _u16MagPage = 0x88;
static U16 _u16SubPage = 0xFFFF;
U_INT8 SubtitlePageIndex = 0;//xFF;

// The P830 status display position of X, Y
static U16 _u8StatusDisplayPosX = 100;
static U16 _u8StatusDisplayPosY = 100;

#if ENABLE_TTX_ACI
EN_TTX_ACI_STATE    enTTXACIState = STATE_TTX_ACI_NONE;
U_INT8  g_u8ACITimeoutType = 0; // which ACI timeout to be calculated!
U32 g_u32ACITimeout = 0;    // timeout calculation!
#endif


static BOOLEANS m_BOOLEANS;
#define m_bIsTeletextOn                  m_BOOLEANS.bBOOL_0
#define m_bIsTeletextOffSuddenly         m_BOOLEANS.bBOOL_1

static WORD m_wVBIUpCountTimer;

static BOOLEAN m_bShowChInfo = FALSE;


/*******************************************************************************/
/*                               Functions                                     */
/*******************************************************************************/
#if ENABLE_DTV
static U16 _u16SubtitleTTX_PID = MSAPI_DMX_INVALID_PID;
static U16 _u16DefaultTTX_PID = MSAPI_DMX_INVALID_PID;
static BOOL _isFilterStarted = FALSE;

MS_TELETEXT_INFO gstTtxInfo;

U16 MApp_TTX_GetSubtitleTTX_PID(void)
{
    return _u16SubtitleTTX_PID;
}

void MApp_TTX_SetSubtitleTTX_PID(U16 pid)
{
    //printf("Set subtitle PID 0x%x\n", pid);
    _u16SubtitleTTX_PID = pid;
}

U16 MApp_TTX_GetDefaultTTX_PID(void)
{
    return _u16DefaultTTX_PID;
}

void MApp_TTX_SetDefaultTTX_PID(U16 pid)
{
    //printf("Set default PID 0x%x\n", pid);
    _u16DefaultTTX_PID = pid;
    _isFilterStarted = FALSE;
}

static U16 g_u16DtvPID = 0;
void _Dmx_Callback(U8 dmxId, DMX_EVENT enEvent)
{
    if((DMX_EVENT_BUF_OVERFLOW == enEvent)
        && (*MApp_Dmx_GetFid(EN_TTX_FID) == dmxId))
    {
        printf("TTX DMX overflow : %d, %d \n",  dmxId, enEvent);
        msAPI_TTX_VBIAcquireEnable(FALSE);
        msAPI_DMX_CloseFilter( *MApp_Dmx_GetFid(EN_TTX_FID) );
        MApp_Dmx_SetFid(MSAPI_DMX_INVALID_FLT_ID, EN_TTX_FID);
#if ENABLE_PVR

        if (MApp_PVR_IsPlaybacking())
        {
            MS_DMX_SECTIONMONITOR_PARA stSectionMonitor;
            memset(&stSectionMonitor, 0 , sizeof(MS_DMX_SECTIONMONITOR_PARA));
            stSectionMonitor.u16PID = g_u16DtvPID;
            stSectionMonitor.u32SectionFltType = MSAPI_DMX_FILTER_TYPE_TELETEXT|MSAPI_DMX_FILTER_SOURCE_TYPE_FILE;
            stSectionMonitor.pfNotify = _Dmx_Callback;
            stSectionMonitor.u16TimeoutMilliSec = MSAPI_DMX_TIMEOUT_INFINITE;
            stSectionMonitor.SectMode = DMX_SECT_MODE_CONTI|DMX_SECT_MODE_AUTO_ADDR;
            stSectionMonitor.pu8FID = MApp_Dmx_GetFid(EN_TTX_FID);

            msAPI_DMX_SectionMonitor(&stSectionMonitor, TRUE);
        }
        else
#endif
        {
            MS_DMX_SECTIONMONITOR_PARA stSectionMonitor;
            memset(&stSectionMonitor, 0 , sizeof(MS_DMX_SECTIONMONITOR_PARA));
            stSectionMonitor.u16PID = g_u16DtvPID;
            stSectionMonitor.u32SectionFltType = MSAPI_DMX_FILTER_TYPE_TELETEXT;
            stSectionMonitor.pfNotify = _Dmx_Callback;
            stSectionMonitor.u16TimeoutMilliSec = MSAPI_DMX_TIMEOUT_INFINITE;
            stSectionMonitor.SectMode = DMX_SECT_MODE_CONTI|DMX_SECT_MODE_AUTO_ADDR;
            stSectionMonitor.pu8FID = MApp_Dmx_GetFid(EN_TTX_FID);

            msAPI_DMX_SectionMonitor(&stSectionMonitor, FALSE);
        }

        msAPI_TTX_SetTTXFid(*MApp_Dmx_GetFid(EN_TTX_FID));
        TT_PacketBufferReset();
        msAPI_TTX_VBIAcquireEnable(TRUE);
    }
}

void MApp_TTX_SetDTV_TTXSystem(U16 pid, BOOLEAN bExitPVR)
{
#if ENABLE_PVR
    BOOLEAN bPVRPlaybacking = FALSE;
    UNUSED(bExitPVR);
    if (MApp_PVR_IsPlaybacking())
        bPVRPlaybacking = TRUE;

    if(bPVRPlaybacking && *MApp_Dmx_GetFid(EN_TTX_FID) && _isFilterStarted)
        return;

    _isFilterStarted = TRUE;
#else
    UNUSED(bExitPVR);
#endif

    msAPI_TTX_VBIAcquireEnable(FALSE);
    msAPI_DMX_CloseFilter( *MApp_Dmx_GetFid(EN_TTX_FID) );
    MApp_Dmx_SetFid(MSAPI_DMX_INVALID_FLT_ID, EN_TTX_FID);

#if ENABLE_PVR

        if (MApp_PVR_IsPlaybacking())
        {
            MS_DMX_SECTIONMONITOR_PARA stSectionMonitor;
            memset(&stSectionMonitor, 0 , sizeof(MS_DMX_SECTIONMONITOR_PARA));
            stSectionMonitor.u16PID = pid;
            stSectionMonitor.u32SectionFltType = MSAPI_DMX_FILTER_TYPE_TELETEXT|MSAPI_DMX_FILTER_SOURCE_TYPE_FILE;
            stSectionMonitor.pfNotify = _Dmx_Callback;
            stSectionMonitor.u16TimeoutMilliSec = MSAPI_DMX_TIMEOUT_INFINITE;
            stSectionMonitor.SectMode = DMX_SECT_MODE_CONTI|DMX_SECT_MODE_AUTO_ADDR;
            stSectionMonitor.pu8FID = MApp_Dmx_GetFid(EN_TTX_FID);

            msAPI_DMX_SectionMonitor(&stSectionMonitor, TRUE);
        }
        else
#endif
        {
            MS_DMX_SECTIONMONITOR_PARA stSectionMonitor;
            memset(&stSectionMonitor, 0 , sizeof(MS_DMX_SECTIONMONITOR_PARA));
            stSectionMonitor.u16PID = pid;
            stSectionMonitor.u32SectionFltType = MSAPI_DMX_FILTER_TYPE_TELETEXT;
            stSectionMonitor.pfNotify = _Dmx_Callback;
            stSectionMonitor.u16TimeoutMilliSec = MSAPI_DMX_TIMEOUT_INFINITE;
            stSectionMonitor.SectMode = DMX_SECT_MODE_CONTI|DMX_SECT_MODE_AUTO_ADDR;
            stSectionMonitor.pu8FID = MApp_Dmx_GetFid(EN_TTX_FID);

            msAPI_DMX_SectionMonitor(&stSectionMonitor, FALSE);
        }

    msAPI_TTX_SetTTXFid(*MApp_Dmx_GetFid(EN_TTX_FID));
    MApp_TTX_Reflesh();
    msAPI_TTX_VBIAcquireEnable(TRUE);
    g_u16DtvPID = pid;
}
#endif

static
void _MApp_TTX_SetControlMode(EN_TELETEXT_MODE mode)
{
    _enTTXMode = mode;
}

EN_TELETEXT_MODE MApp_TTX_GetControlMode(void)
{
    return _enTTXMode;
}

void MApp_TTX_BackToOSDMode(void)
{
}


void MApp_TTX_BackToTTXMode(void)

{
}


BOOLEAN MApp_TTX_TurnOnTTSource ( void )
{
    BOOLEAN result;

    result = FALSE;

    #if ENABLE_DTV
    if ( IsDTVInUse() )
    {
        if(MApp_TTX_GetDefaultTTX_PID()!=MSAPI_DMX_INVALID_PID)
        {
            result = TRUE;
        }
    }
    else
    #endif
    {
        if(msAPI_TTX_CheckTTX())
        {
            // put header packet into VBI without decoder
        }
        result = TRUE;
    }

    return result;
}

void MApp_TTX_InitVBITeletext(void)
{
#if ENABLE_ISDBT
    if(IS_SBTVD_APP)
        return;
#endif

    m_bIsTeletextOn = FALSE;
    m_bIsTeletextOffSuddenly = FALSE;
    m_wVBIUpCountTimer = 0;
    msAPI_TTX_SetVideoStandard(E_VIDEOSTANDARD_PAL_BGHI);
    msAPI_TTX_ResetAcquisition();
}

void MApp_TTX_SetTeletextOnOff(BOOLEAN val)
{
    m_bIsTeletextOn = val;
}

BOOLEAN MApp_TTX_IsTeletextOn(void)
{
    return m_bIsTeletextOn;
}

void MApp_TTX_SetChInfoOnOff(BOOLEAN val)
{
    m_bShowChInfo = val;
}

BOOLEAN MApp_TTX_IsChInfoOn(void)
{
    return m_bShowChInfo;
}

BOOLEAN MApp_TTX_IsTeletextOffSuddenly(void)
{
    if( m_bIsTeletextOffSuddenly == FALSE )
        return FALSE;

    m_bIsTeletextOffSuddenly = FALSE;
    return TRUE;
}

#if 0
#ifdef PANEL_WIDTH
#undef PANEL_WIDTH
#define PANEL_WIDTH 1366
#endif
#ifdef PANEL_HEIGHT
#undef PANEL_HEIGHT
#define PANEL_HEIGHT 768
#endif
#endif

void MApp_TTX_VBIDataProcessor(void)
{
    AVD_InputSourceType eVideoSource;

    if ( msAPI_Tuner_IsTuningProcessorBusy() == TRUE )
    {
        return;
    }

    eVideoSource = msAPI_AVD_GetVideoSource();
    if( eVideoSource != E_INPUT_SOURCE_ATV &&
        eVideoSource != E_INPUT_SOURCE_CVBS1 &&
        eVideoSource != E_INPUT_SOURCE_CVBS2 &&
        eVideoSource != E_INPUT_SOURCE_SVIDEO1 &&
        eVideoSource != E_INPUT_SOURCE_SVIDEO2 &&
        eVideoSource != E_INPUT_SOURCE_SCART1 &&
        eVideoSource != E_INPUT_SOURCE_SCART2 )
    {
        return;
    }

    m_wVBIUpCountTimer++;
    if(m_wVBIUpCountTimer >= 0xFFF0)
        m_wVBIUpCountTimer = 1;

    if( (m_wVBIUpCountTimer % 47) == 0 )
    {
        if(m_bIsTeletextOn == TRUE)
        {
        #if(0 == ENABLE_TTX_SHOW_OFF_SIGNAL)
            if(IsVDHasSignal()==FALSE)
            {
                msAPI_TTX_ResetAcquisition();
                if( m_bIsTeletextOn == FALSE )
                {
                    m_bIsTeletextOffSuddenly = TRUE;
                }
                return;
            }
        #endif
    }
    }
}
////////////////////////////////////////////////////////////
//      MApp_TTX_SetRP_Video_TTX()
//      Set or Restore Video Window for Video+TTX Rendering Phase
//      Input: 0:Restore, Other: Set
////////////////////////////////////////////////////////////
void MApp_TTX_SetRP_Video_TTX(BOOLEAN bIsVideoTTX)
{
    static XC_SETWIN_INFO _orgWinInfo;
    BOOLEAN bResult;

    if ((bIsVideoTTX) && (_RenderingPhase == TTX_RENDERING_PHASE_VIDEO_TTX))
    {
        U32 windowWidth;
        XC_ApiStatus xcStatus;

        msAPI_TTX_GetInternalTTXWindowSize(&windowWidth,
                                                0,
                                                TTX_OSD_MARGINH,
                                                TTX_OSD_MARGINV,
                                                PANEL_WIDTH/2,
                                                0);
        bResult = MApi_XC_GetStatus(&xcStatus, MAIN_WINDOW);
        ASSERT(bResult);
        memcpy(&_orgWinInfo, &xcStatus, sizeof(_orgWinInfo));
        _orgWinInfo.bPreHCusScaling = 0;
        _orgWinInfo.bPreVCusScaling = 0;

        _orgWinInfo.stDispWin.width = (PANEL_WIDTH - windowWidth) - TTX_OSD_MARGINH;
        _orgWinInfo.stDispWin.height = PANEL_HEIGHT - TTX_OSD_MARGINV*2;
        _orgWinInfo.stDispWin.x = TTX_OSD_MARGINH;
        _orgWinInfo.stDispWin.y = TTX_OSD_MARGINV;
        bResult = MApi_XC_SetWindow(&_orgWinInfo, sizeof(_orgWinInfo), MAIN_WINDOW);
        ASSERT(bResult);

        _orgWinInfo.stDispWin.width = xcStatus.stDispWin.width;
        _orgWinInfo.stDispWin.height = xcStatus.stDispWin.height;
        _orgWinInfo.stDispWin.x = xcStatus.stDispWin.x;
        _orgWinInfo.stDispWin.y = xcStatus.stDispWin.y;
    }
    else if (bIsVideoTTX == FALSE)
    {
        bResult = MApi_XC_SetWindow(&_orgWinInfo, sizeof(_orgWinInfo), MAIN_WINDOW);
        ASSERT(bResult);
    }
}
static void _MApp_TTX_RenderingPhaseToggle(BOOLEAN bTransparent)
{
    U8 idx = 0;
    TTX_RenderingPhase OriginalRenderingPhase = _RenderingPhase;
#if (TTX_DISPLAY_MODE == TTX_DISPLAY_NORMAL)
    TTX_RenderingPhase eTTXRenderingPhaseLoop[] = {TTX_RENDERING_PHASE_OFF, TTX_RENDERING_PHASE_NORMAL};
#elif (TTX_DISPLAY_MODE == TTX_DISPLAY_PAT)
    TTX_RenderingPhase eTTXRenderingPhaseLoop[] = {TTX_RENDERING_PHASE_OFF, TTX_RENDERING_PHASE_NORMAL, TTX_RENDERING_PHASE_MIX, TTX_RENDERING_PHASE_VIDEO_TTX};
#else
    TTX_RenderingPhase eTTXRenderingPhaseLoop[] = {TTX_RENDERING_PHASE_OFF, TTX_RENDERING_PHASE_NORMAL, TTX_RENDERING_PHASE_MIX};
#endif
#define TTX_RENDERING_LIST_COUNT (sizeof(eTTXRenderingPhaseLoop)/sizeof(eTTXRenderingPhaseLoop[0]))

    for (idx = 0; idx < TTX_RENDERING_LIST_COUNT; idx++)
    {
        if (_RenderingPhase == eTTXRenderingPhaseLoop[idx])
        {
            break;
        }
    }
    if (idx < (TTX_RENDERING_LIST_COUNT-1))
    {
        _RenderingPhase = eTTXRenderingPhaseLoop[idx+1];
    }
    else
    {
        _RenderingPhase = eTTXRenderingPhaseLoop[0];
    }

    switch (_RenderingPhase)
    {
        default:
        case TTX_RENDERING_PHASE_OFF:
        {
            msAPI_TTX_CloseRenderObj();
            msAPI_TTX_Command(TTX_TV);
            break;
        }

        case TTX_RENDERING_PHASE_NORMAL:
        {
            msAPI_TTX_OpenRenderObj(TTX_OSD_MARGINH,
                                    TTX_OSD_MARGINV,
                                    0,
                                    0,
                                    PANEL_WIDTH,
                                    PANEL_HEIGHT,
                                    bTransparent);
            msAPI_TTX_Command(TTX_TEXT);
            break;
        }

        case TTX_RENDERING_PHASE_VIDEO_TTX:
        {
            U32 windowWidth;

            msAPI_TTX_GetInternalTTXWindowSize(&windowWidth,
                                                    0,
                                                    TTX_OSD_MARGINH,
                                                    TTX_OSD_MARGINV,
                                                    PANEL_WIDTH/2,
                                                    0);
            msAPI_TTX_CloseRenderObj();
            msAPI_TTX_Command(TTX_TV);

            msAPI_TTX_OpenRenderObj(TTX_OSD_MARGINH,
                                    TTX_OSD_MARGINV,
                                    PANEL_WIDTH - windowWidth,
                                    0,
                                    windowWidth,
                                    PANEL_HEIGHT,
                                    bTransparent);
            msAPI_TTX_Command(TTX_TEXT);

            MApp_TTX_SetRP_Video_TTX(TRUE);
            break;
        }

        case TTX_RENDERING_PHASE_MIX:
        {
            msAPI_TTX_Command(TTX_MIX);
            break;
        }
    }

    if (OriginalRenderingPhase == TTX_RENDERING_PHASE_VIDEO_TTX)
    {
        MApp_TTX_SetRP_Video_TTX(FALSE);
    }

    if(_RenderingPhase == TTX_RENDERING_PHASE_OFF)
        MApp_TTX_SetTeletextOnOff(FALSE);
    else
        MApp_TTX_SetTeletextOnOff(TRUE);

}
static
void _MApp_TTX_Close(void)
{

    msAPI_TTX_CloseRenderObj();
    _MApp_TTX_SetControlMode(TTX_MODE_NORMAL);
    MApp_TTX_SetTeletextOnOff(FALSE);


    if(_RenderingPhase == TTX_RENDERING_PHASE_VIDEO_TTX)
    {
        MApp_TTX_SetRP_Video_TTX(FALSE);
    }

    _RenderingPhase = TTX_RENDERING_PHASE_OFF;

  #if (CHIP_FAMILY_TYPE == CHIP_FAMILY_MELODY)
    if (msAPI_AUD_IsAudioMutedByUser())       //chj
    {
        MApp_UiMenu_MuteWin_Show();
    }
  #endif
}

static
BOOLEAN _MApp_TTX_IsSubtitlePage(MS_U16 magPage, MS_U16 subPage)
{
    MS_U32 i;
    MS_U32 availableSubtitlePages = MApp_TTX_GetSubtitlesAvailable();

    for(i = 0;
        i < availableSubtitlePages;
        ++i)
    {
        if(msAPI_TTX_GetSubtitlePage(i, &magPage, &subPage))
            return TRUE;
    }

    return FALSE;
}

static FUNCTION_RESULT
_MApp_TTX_Open(TELETEXT_COMMAND command,
               BOOLEAN bTransparent,
               BOOLEAN bClearOSD)
{
    FUNCTION_RESULT ret = E_RESULT_SUCCESS;

#if ENABLE_SUBTITLE
    if(MApp_Subtitle_IsRunning())
        MApp_Subtitle_Force_Exit();
#endif

    if (bClearOSD)
    {
        MApp_ZUI_ACT_ShutdownOSD();

      #if (CHIP_FAMILY_TYPE == CHIP_FAMILY_MELODY)
        if (  msAPI_AUD_IsAudioMutedByUser()
           && (MApp_TTX_IsTeletextOn() == FALSE) )
        {
            MApp_UiMenu_MuteWin_Hide();
        }
      #endif
    }

    switch (command)
    {
        case TTX_TEXT: //normal TTX
            _MApp_TTX_SetControlMode(TTX_MODE_NORMAL);
            _MApp_TTX_RenderingPhaseToggle(bTransparent);
            break;

        case TTX_SUBTITLE_TTX_ON:
            if(_MApp_TTX_IsSubtitlePage(_u16MagPage,_u16SubPage) == FALSE)
            {
                ret = E_RESULT_FAILURE;
                break;
            }

            _MApp_TTX_SetControlMode(TTX_MODE_SUBTITLE);

            msAPI_TTX_OpenRenderObj(TTX_OSD_MARGINH,
                                    TTX_OSD_MARGINV,
                                    0,
                                    0,
                                PANEL_WIDTH,
                                PANEL_HEIGHT,
                                    bTransparent);

            msAPI_TTX_CommandExt(TTX_SUBTITLE_TTX_ON,
                                 TRUE,
                                 _u16MagPage,
                                 _u16SubPage);
            MApp_TTX_SetTeletextOnOff(TRUE);
            break;

        case TTX_SUBTITLE_NAVIGATION_MODE:
            {
                BOOLEAN bValid;

                msAPI_TTX_IsStatusValid(TT_VALID_DISPLAY_OPENED, &bValid);
                if(!bValid)
                {
                    MApp_TTX_SetTeletextOnOff(TRUE);
                    _MApp_TTX_SetControlMode(TTX_MODE_SUBTITLE);
                    msAPI_TTX_OpenRenderObj(TTX_OSD_MARGINH,
                                            TTX_OSD_MARGINV,
                                            0,
                                            0,
                                            PANEL_WIDTH,
                                            PANEL_HEIGHT,
                                            bTransparent);
                }

                msAPI_TTX_Command(TTX_SUBTITLE_NAVIGATION_MODE);

                msAPI_TTX_IsStatusValid(TT_VALID_DISPLAY_OPENED, &bValid);
                if(!bValid)
                {
                    _MApp_TTX_Close();
                }
            }
            break;

        case TTX_CLOCK:
            _MApp_TTX_SetControlMode(TTX_MODE_CLOCK);
            msAPI_TTX_OpenRenderObj(TTX_OSD_MARGINH,
                                TTX_OSD_MARGINV,
                                0,
                                0,
                                PANEL_WIDTH,
                                PANEL_HEIGHT,
                                bTransparent);
            msAPI_TTX_Command(TTX_CLOCK);
            MApp_TTX_SetTeletextOnOff(TRUE);
            break;

        case TTX_STATUS_DISPLAY:
            _MApp_TTX_SetControlMode(TTX_MODE_STATUS);
            msAPI_TTX_OpenRenderObj(TTX_OSD_MARGINH,
                                TTX_OSD_MARGINV,
                                0,
                                0,
                                PANEL_WIDTH,
                                PANEL_HEIGHT,
                                bTransparent);
            msAPI_TTX_CommandExt(TTX_STATUS_DISPLAY,
                                 TRUE,
                                 _u8StatusDisplayPosX,
                                 _u8StatusDisplayPosY);
            MApp_TTX_SetTeletextOnOff(TRUE);
            break;

        default:
            MS_DEBUG_MSG(printf("unsupport command to open TTX\n"));
            break;
    }

    if (bClearOSD)
    {
      #if (CHIP_FAMILY_TYPE == CHIP_FAMILY_MELODY)
        if (  msAPI_AUD_IsAudioMutedByUser()
           && (MApp_TTX_IsTeletextOn() == FALSE) )
        {
            MApp_UiMenu_MuteWin_Show();
        }
      #endif
    }

    return ret;
}

//*************************************************************************
//Function name:        msAPI_TTX_ClockMode_Monitor
//Description:          Monitor TTX clock mode, after TTX_CLOCK_MODE_TIMEOUT rexpired
//                           turn off clock mode
//*************************************************************************
void MApp_TTX_ClockMode_Monitor(void)
{
     // add for mantis 1328076: core dump on MM.
     if(IsStorageInUse())
     {
        return;
     }

    if(MApp_TTX_GetControlMode()==TTX_MODE_CLOCK)
    {
        if(msAPI_Timer_DiffTimeFromNow(g_u32MonitorTTXClockTimer)>=TTX_CLOCK_MODE_TIMEOUT)
            MApp_TTX_TeletextCommand(TTX_TV);
    }
    else if(MApp_TTX_GetControlMode()==TTX_MODE_SUBTITLE)  //monitor VolumeBar timeout
    {
    }

    BOOLEAN bValid;
    msAPI_TTX_IsStatusValid(TT_VALID_SHOWNOSUBPAGE, &bValid);
    if(bValid)
    {
        if(msAPI_Timer_DiffTimeFromNow(g_u32MonitorShowNoSubpageTimer)>=TTX_SHOWNOSUBPAGE_TIMEOUT)
        {
            MApp_TTX_TeletextCommand(TTX_SUBPAGE);
        }
    }
}

//*************************************************************************
//Function name:        msAPI_TTX_EnableScan
//Passing parameter:    U_INT8 on
//Return parameter:     none
//Description:          Before scanning must call this function with on = 1
//                           after scanning, must call this function with on = 0
//*************************************************************************
void MApp_TTX_EnableScan(U_INT8 on)
{
#if ENABLE_ISDBT
    if(IS_SBTVD_APP)
        return;
#endif
    if(on)
    {
        // we don't need to call DecCreate here, it is moved to initial stage
        //msAPI_TTX_DecCreate();
        MApp_TTX_Reflesh();
        msAPI_TTX_VBIAcquireScanEnable(ENABLE);
    }
    else
    {
        msAPI_TTX_VBIAcquireScanEnable(DISABLE);
    }
}

//*************************************************************************
//Function name:        MApp_TTX_TeletextCommand
//Passing parameter:    TELETEXT_COMMAND eCommand
//Return parameter:     Execution state
//Description:          Dispatch all TTX-related commands to TTX system
//*************************************************************************
FUNCTION_RESULT MApp_TTX_TeletextCommand(TELETEXT_COMMAND eCommand)
{
#if ENABLE_ISDBT
    if(IS_SBTVD_APP)
        return E_RESULT_FAILURE;
#endif
    FUNCTION_RESULT ret = E_RESULT_SUCCESS;

    if (eCommand >= TTX_MAX_TEXT_COMMAND)
    {
        return E_RESULT_FAILURE;
    }

    if (IsDTVInUse() && (eCommand==TTX_SUBTITLE_TTX_ON) )
    {
    #if ENABLE_PVR
        if (MApp_PVR_IsPlaybacking())
        {
            #if ENABLE_DTV
            MApp_TTX_SetDTV_TTXSystem(MApp_TTX_GetDefaultTTX_PID(), FALSE);
            #endif
        }
        else
    #endif
        {
        #if ENABLE_DTV
            if(MApp_TTX_GetSubtitleTTX_PID()!=MApp_TTX_GetDefaultTTX_PID())
            {
                // the PID of TTX subtitle PID is different from default TTX subtitle, so we need to re-set the TTX filter
                // stop default TTX filter. change to selected TTX subtitle filter
                MApp_TTX_SetDTV_TTXSystem(MApp_TTX_GetSubtitleTTX_PID(), FALSE);
                MApp_TTX_SetDefaultTTX_PID(MApp_TTX_GetSubtitleTTX_PID());
            }
        #endif
        }
    }


    switch(eCommand)
    {
        case TTX_DIGIT_0:
        case TTX_DIGIT_1:
        case TTX_DIGIT_2:
        case TTX_DIGIT_3:
        case TTX_DIGIT_4:
        case TTX_DIGIT_5:
        case TTX_DIGIT_6:
        case TTX_DIGIT_7:
        case TTX_DIGIT_8:
        case TTX_DIGIT_9:
            msAPI_TTX_Command(eCommand);
            break;

    #if ENABLE_TTX_ACI
        case TTX_UP:
            msAPI_TTX_SetCMD(TT_DEC_ACI_UP, 0, 0);
            break;

        case TTX_DOWN:
            msAPI_TTX_SetCMD(TT_DEC_ACI_DOWN, 0, 0);
            break;

        case TTX_OK:
            msAPI_TTX_SetCMD(TT_DEC_ACI_SELECT, 0, 0);
            break;
    #endif

        case TTX_PAGE_UP:
            msAPI_TTX_Command(eCommand);
            break;

        case TTX_PAGE_DOWN:
            msAPI_TTX_Command(eCommand);
            break;

        case TTX_SUBPAGE:
            msAPI_TTX_Command(eCommand);
            break;

        case TTX_PAGE_LEFT:
            msAPI_TTX_Command(eCommand);
            break;

          case TTX_PAGE_RIGHT:
            msAPI_TTX_Command(eCommand);
            break;

        case TTX_RED:
            msAPI_TTX_Command(eCommand);
            break;

        case TTX_GREEN:
            msAPI_TTX_Command(eCommand);
            break;

        case TTX_YELLOW:
            msAPI_TTX_Command(eCommand);
            break;

        case TTX_CYAN:
            msAPI_TTX_Command(eCommand);
            break;

        case TTX_MIX:
            if (TTX_DISPLAY_MODE == TTX_DISPLAY_NORMAL)
                msAPI_TTX_Command(eCommand);
            break;

    #if ENABLE_TTX_ACI
        case TTX_ACI:
            if(MApp_TTX_IsTeletextOn()==TRUE)
            {
                ret = E_RESULT_FAILURE;
                break;
            }

            _MApp_TTX_Open(TTX_ACI, FALSE, TRUE);
            msAPI_TTX_SetCMD(TTX_DEC_ACI_GO, 0x1BE, 0);
            break;
    #endif

        case TTX_SUBTITLE_TTX_ON:
            if(MApp_TTX_IsTeletextOn()==TRUE)
            {
                ret = E_RESULT_FAILURE;
                break;
            }

            if ( !MApp_TTX_TurnOnTTSource() )
            {
                ret = E_RESULT_FAILURE;
                break;
            }
            else
            {
                ret = _MApp_TTX_Open(TTX_SUBTITLE_TTX_ON, TRUE, FALSE);
            }
            break;

        case TTX_SUBTITLE_NAVIGATION_MODE:
            if ( !MApp_TTX_TurnOnTTSource() )
            {
                ret = E_RESULT_FAILURE;
                break;
            }
            else
            {
                _MApp_TTX_Open(TTX_SUBTITLE_NAVIGATION_MODE, TRUE, FALSE);
            }
            break;

        case TTX_TEXT:
            if ( !MApp_TTX_TurnOnTTSource() )
            {
                ret = E_RESULT_FAILURE;
                break;
            }
            else
            {
                _MApp_TTX_Open(TTX_TEXT, FALSE, TRUE);
            }

            break;

        case TTX_TV:
            if(MApp_TTX_IsTeletextOn()==FALSE)
            {
                ret = E_RESULT_FAILURE;
                break;
            }

            if(MApp_TTX_GetControlMode()==TTX_MODE_NORMAL)
            {
                msAPI_TTX_Command(eCommand);
            }
            else if(MApp_TTX_GetControlMode()==TTX_MODE_SUBTITLE)
            {
                msAPI_TTX_Command(eCommand);

            #if ENABLE_PVR
                if (MApp_PVR_IsPlaybacking())
                {
                    #if ENABLE_DTV
                    MApp_TTX_SetDTV_TTXSystem(MApp_TTX_GetDefaultTTX_PID(), FALSE);
                    #endif
                }
                else
            #endif
                {
                    #if ENABLE_DTV
                    if(IsDTVInUse()&&(MApp_TTX_GetSubtitleTTX_PID()!=MApp_TTX_GetDefaultTTX_PID()))
                    {
                        // the PID of TTX subtitle PID is different from default TTX subtitle, so we need to re-set the TTX filter
                        // stop default TTX filter. change to selected TTX subtitle filter
                        MApp_TTX_SetDTV_TTXSystem(MApp_TTX_GetDefaultTTX_PID(), FALSE);
                    }
                    #endif
                }
            }
            else if(MApp_TTX_GetControlMode()==TTX_MODE_CLOCK)
            {
                 msAPI_TTX_CommandExt(TTX_CLOCK,
                                     FALSE,
                                     0U,
                                     0U);
            }
            else if(MApp_TTX_GetControlMode()==TTX_MODE_STATUS)
            {
                 msAPI_TTX_CommandExt(TTX_STATUS_DISPLAY,
                                     FALSE,
                                     0U,
                                     0U);
            }

            _MApp_TTX_Close();

            //ZUI_TODO: if(msAPI_AUD_IsAudioMutedByUser())
            //ZUI_TODO:     MApp_UiMenu_DrawMuteWin();

            return ret;


        case TTX_CLOCK:
            if(MApp_TTX_IsTeletextOn()==TRUE)
            {
                ret = E_RESULT_FAILURE;
                break;
            }

            if ( !MApp_TTX_TurnOnTTSource() )
            {
                _MApp_TTX_SetControlMode(TTX_MODE_NORMAL);
                ret = E_RESULT_FAILURE;
                break;
            }
            else
            {
                _MApp_TTX_Open(TTX_CLOCK, TRUE, TRUE);
            }
            break;

       case TTX_STATUS_DISPLAY:
            if(MApp_TTX_IsTeletextOn()==TRUE)
            {
                ret = E_RESULT_FAILURE;
                break;
            }

            if ( !MApp_TTX_TurnOnTTSource() )
            {
                _MApp_TTX_SetControlMode(TTX_MODE_NORMAL);
                ret = E_RESULT_FAILURE;
                break;
            }
            else
            {
                _MApp_TTX_Open(TTX_STATUS_DISPLAY, TRUE, TRUE);
            }

            break;

        case TTX_UPDATE:
             msAPI_TTX_Command(eCommand);
            break;

        case TTX_INDEX:
             msAPI_TTX_Command(eCommand);
            break;

        case TTX_HOLD:
             msAPI_TTX_Command(eCommand);
            break;

        case TTX_LIST:
             msAPI_TTX_Command(eCommand);
             break;

        case TTX_TIME:
            break;

        case TTX_SIZE:
            msAPI_TTX_Command(eCommand);
            break;

        case TTX_REVEAL:
             msAPI_TTX_Command(eCommand);
             break;

        case TTX_CLEAR_LIST:
             msAPI_TTX_Command(eCommand);
             break;
        case TTX_CYCLE_SUBPAGE:
            msAPI_TTX_Command(eCommand);
            break;
        case TTX_CANCEL:
            msAPI_TTX_Command(eCommand);
            break;
        default:
            ret = E_RESULT_FAILURE;
            break;
    }

    return ret;
}

U_INT8 MApp_TTX_GetSubtitlesAvailable(void)
{
    return msAPI_TTX_GetSubtitlesAvailable();
}

//*************************************************************************
//Function name:        MApp_TTX_SetSubtitlePage
//Passing parameter:    Magazine & Page number of Subtitle Page
//Description:          Set digital TTX subtitle page number
//*************************************************************************
void MApp_TTX_SetSubtitlePage(U16 magPage, U16 subPage)
{
    _u16MagPage = magPage;
    _u16SubPage = subPage;
}

void MApp_TTX_Decoder_Process(void)
{
    MApp_TTX_BackToTTXMode();
    msAPI_TTX_Decoder_Process();
    MApp_TTX_BackToOSDMode();
}

void MApp_TTX_SetP830_DisplayPos(U16 u8X, U16 u8Y)
{
    _u8StatusDisplayPosX = u8X;
    _u8StatusDisplayPosY = u8Y;
}

void MApp_TTX_Reflesh(void)
{
#if ENABLE_ISDBT
    if(IS_SBTVD_APP)
        return;
#endif
    if(IsDigitalSourceInUse()||IsDTVInUse())
        msAPI_TTX_ResetAcquisition();//msAPI_TTX_SetCMD(TT_DEC_RESET, 0, 0);
}

FUNCTION_RESULT MApp_TTX_SetCountry(MEMBER_COUNTRY eCountry)
{
#if ENABLE_ISDBT
    if(IS_SBTVD_APP)
        return E_RESULT_FAILURE;
#endif
    DEBUG_APP_TTX( printf("MApp_TTX_SetCountry(eCountry=%u)\n", eCountry); );

    switch(eCountry)
    {
        case E_BULGARIA:
        case E_RUSSIA:
            msAPI_TTX_SetLanguageGroup(TT_Charset_Group_Russian);
            break;

        case E_CZECH:
        case E_ESTONIA:
        case E_CROATIA:
        //case E_LATVIA:
        case E_POLAND:
        case E_ROMANIA:
        case E_SLOVAKIA:
        case E_SLOVENIA:
        case E_SERBIA:
            msAPI_TTX_SetLanguageGroup(TT_Charset_Group_East);
            break;

        case E_TURKEY:
        case E_UNITED_ARAB_EMIRATES:
        case E_MOROCCO:
        //case E_HEBREW:
        //case E_ARAB:
        case E_KUWAIT:
        case E_OMAN:
        case E_QATAR:
        case E_SAUDI_ARABIA:
        case E_BAHRAIN:
            msAPI_TTX_SetLanguageGroup(TT_Charset_Group_Arabic);
            break;

        case E_IRAN:
            msAPI_TTX_SetLanguageGroup(TT_Charset_Group_Farsi);
            break;

        case E_DENMARK:
        case E_GERMANY:
        case E_AUSTRIA:
        case E_UK:
        case E_SPAIN:
        case E_GREECE:
        case E_FRANCE:
        case E_ITALY:
        case E_HUNGARY:
        case E_NETHERLANDS:
        case E_NORWAY:
        case E_PORTUGAL:
        case E_FINLAND:
        case E_SWEDEN:
        case E_SWITZERLAND:
        //case E_OTHERS:
        case E_AUSTRALIA:
        case E_NEWZEALAND:
        case E_MALAYSIA:
        case E_INDONESIA:
        case E_THAILAND:
        case E_VIETNAM:
        case E_SINGAPORE:
#if (ENABLE_COUNTRY_KENYA)
        case E_KENYA:
#endif
#if (ENABLE_COUNTRY_MYANMAR)
        case E_MYANMAR:
#endif
        default:
            msAPI_TTX_SetLanguageGroup(TT_Charset_Group_West);
            break;
    }


//** osmans 220408 CNI/VPS specific country and language functions changed so deleted msAPI_CNI_SetCountryLangId() */
    switch(eCountry)
    {
        case E_CZECH:
            msAPI_CNI_SetCountryLangId(COUNTRYID_CZECH, 0);
            break;
        case E_POLAND:
            msAPI_CNI_SetCountryLangId(COUNTRYID_POLAND, 0);
            break;
        case E_DENMARK:
            msAPI_CNI_SetCountryLangId(COUNTRYID_DENMARK, 0);
            break;
        case E_GERMANY:
            msAPI_CNI_SetCountryLangId(COUNTRYID_GERMANY, 0);
            break;
        case E_AUSTRIA:
            msAPI_CNI_SetCountryLangId(COUNTRYID_AUSTRIA, 0);
            break;
        case E_UK:
            msAPI_CNI_SetCountryLangId(COUNTRYID_UK, 0);
            break;
        case E_SPAIN:
            msAPI_CNI_SetCountryLangId(COUNTRYID_SPAIN, 0);
            break;
        case E_FRANCE:
            msAPI_CNI_SetCountryLangId(COUNTRYID_FRANCE, 0);
            break;
        case E_ITALY:
            msAPI_CNI_SetCountryLangId(COUNTRYID_ITALY, 0);
            break;
        case E_HUNGARY:
            msAPI_CNI_SetCountryLangId(COUNTRYID_HUNGARY, 0);
            break;
        case E_NETHERLANDS:
            msAPI_CNI_SetCountryLangId(COUNTRYID_NETHERLANDS, 0);
            break;
        case E_NORWAY:
            msAPI_CNI_SetCountryLangId(COUNTRYID_NORWAY, 0);
            break;
        case E_FINLAND:
            msAPI_CNI_SetCountryLangId(COUNTRYID_FINLAND, 0);
            break;
        case E_SWEDEN:
            msAPI_CNI_SetCountryLangId(COUNTRYID_SWEDEN, 0);
            break;
        case E_SWITZERLAND:
            if(GET_OSD_MENU_LANGUAGE()==LANGUAGE_GERMAN)
                msAPI_CNI_SetCountryLangId(COUNTRYID_SWITZERLAND, COUNTRYID_SWI1_GERMAN);
            else if(GET_OSD_MENU_LANGUAGE()==LANGUAGE_FRENCH)
                msAPI_CNI_SetCountryLangId(COUNTRYID_SWITZERLAND, COUNTRYID_SWI2_FRENCH);
            else if(GET_OSD_MENU_LANGUAGE()==LANGUAGE_ITALIAN)
                msAPI_CNI_SetCountryLangId(COUNTRYID_SWITZERLAND, COUNTRYID_SWI3_ITALIAN);
            else
                msAPI_CNI_SetCountryLangId(COUNTRYID_SWITZERLAND, COUNTRYID_SWI1_GERMAN);

            break;
        case E_BELGIUM:
            if(GET_OSD_MENU_LANGUAGE()==LANGUAGE_GERMAN)
                msAPI_CNI_SetCountryLangId(COUNTRYID_BELGIUM, COUNTRYID_BEL1_FRENCH);
            else if(GET_OSD_MENU_LANGUAGE()==LANGUAGE_GERMAN)
                msAPI_CNI_SetCountryLangId(COUNTRYID_BELGIUM, COUNTRYID_BEL2_DUTCH);
            else
                msAPI_CNI_SetCountryLangId(COUNTRYID_BELGIUM, COUNTRYID_BEL1_FRENCH);

            break;
        default:
            msAPI_CNI_SetCountryLangId(0, 0);
            break;
    }

    if (  eCountry == E_GERMANY
       || eCountry == E_AUSTRIA    // kk 0331-1 teletext - doesn't set here
       || eCountry == E_ITALY
       || eCountry == E_SWITZERLAND )
    {
         msAPI_TTX_SetFlofTopEnable();
    }
    else
    {
         msAPI_TTX_SetFlofTopEnable();
    }

    return E_RESULT_SUCCESS;
}

void MApp_TTX_NavigateSubtitlePagesInTTXMode(void)
{
    static MS_S32 currPageIndex = -1;
    static MS_S32 pageNum = 0 ;

    if(currPageIndex == -1 ||
        currPageIndex >= pageNum)
    {
        pageNum = MApp_TTX_GetSubtitlesAvailable();
        currPageIndex = 0;
    }

    if(currPageIndex < pageNum)
    {
        U16 magPage=0;
        U16 subPage=0;

        if(msAPI_TTX_GetSubtitlePage(currPageIndex, &magPage, &subPage))
        {
            msAPI_TTX_CommandExt(TTX_GOTO_PAGE,
                                    TRUE,
                                    magPage,
                                    subPage);
        }
    }

    currPageIndex++;
}

#if ENABLE_DTV
//****************************************************************************
/// check if EBU subtitle exist via type
/// @param eType \b IN: ttx type
/// -@see EN_TTX_TYPE
/// @return BOOLEAN :
/// - 1: exist
/// - 0: not exist
//****************************************************************************
BOOLEAN MApp_TTX_Is_EBUSubtitleExist(EN_TTX_TYPE eType)
{
    U8 i,u8NumofTTX;

    if((u8NumofTTX = gstTtxInfo.u8NumTTXType) > 0)
    {
        for(i=0;i<u8NumofTTX;i++)
        {
            if(gstTtxInfo.stTTXInfo[i].u8TTXType == eType)
            {
                return TRUE;
            }
        }
    }
    return FALSE;
}

#if 1
//****************************************************************************
/// Get Teletext information via type and language
/// @param eType \b IN: ttx type
/// -@see EN_TTX_TYPE
/// @param lang \b IN: language
/// -@see EN_LANGUAGE
/// @param pu8TTXMagNum \b IN: point of magazine number
/// @param pu8TTXPageNum \b IN: point of page number
/// @return BOOLEAN :
/// - 1: success
/// - 0: false
//****************************************************************************
BOOLEAN MApp_TTX_Get_TTXInfoByTypeAndLang(EN_TTX_TYPE eType, EN_LANGUAGE lang, U8 *pu8TTXMagNum, U8 *pu8TTXPageNum)
{
    U8 i,u8NumofTTX;

    if((u8NumofTTX = gstTtxInfo.u8NumTTXType) > 0)
    {
        for(i=0;i<u8NumofTTX;i++)
        {
            if(gstTtxInfo.stTTXInfo[i].u8TTXType == eType)
            {
                if(MApp_GetLanguageBySILanguage(msAPI_SI_GetLanguageByISO639LangCode(gstTtxInfo.stTTXInfo[i].u8lanuage_code))==lang)
                {
                    *pu8TTXMagNum=gstTtxInfo.stTTXInfo[i].u8TTXMagNum;
                    *pu8TTXPageNum=gstTtxInfo.stTTXInfo[i].u8TTXPageNum;
                    return TRUE;

                }
            }
        }
    }
    return FALSE;
}
#endif
void MApp_TTX_Reset_TTX_Info(void)
{
    gstTtxInfo.u8NumTTXType=0;
    gstTtxInfo.u16TTX_Pid = 0;
}

#if 1
static BOOLEAN _GetInitialPage(EN_LANGUAGE lang, U8 *pu8TTXMagNum, U8 *pu8TTXPageNum)
{
  if(MApp_TTX_Get_TTXInfoByTypeAndLang(EN_TTX_INIT_TTX,
                                       lang,
                                       pu8TTXMagNum,
                                       pu8TTXPageNum))
    return TRUE;

  if(MApp_TTX_Get_TTXInfoByTypeAndLang(EN_TTX_PROG_SCHEDULE,
                                       lang,
                                       pu8TTXMagNum,
                                       pu8TTXPageNum))
    return TRUE;

  if(MApp_TTX_Get_TTXInfoByTypeAndLang(EN_TTX_ADDITIONAL_INFO,
                                       lang,
                                       pu8TTXMagNum,
                                       pu8TTXPageNum))
    return TRUE;

#if 0
  if(MApp_TTX_Get_TTXInfoByTypeAndLang(EN_TTX_SUBTITLE,
                                       lang,
                                       pu8TTXMagNum,
                                       pu8TTXPageNum))
    return TRUE;

  if(MApp_TTX_Get_TTXInfoByTypeAndLang(EN_TTX_SUBTITLE_HEAR,
                                       lang,
                                       pu8TTXMagNum,
                                       pu8TTXPageNum))
    return TRUE;
#endif

  return FALSE;
}
#endif

void MApp_TTX_NotifyPMTTTXInfoChanged(void)
{
#if ENABLE_ISDBT
    if(IS_SBTVD_APP)
        return;
#endif

	U8	magNum,
		pageNum,
		indexMagNum,
		indexPageNum;

	EN_LANGUAGE  u8BycountryforNordicTest = LANGUAGE_NONE;

    DEBUG_APP_TTX(printf("---[%s]->%d.IS_NORDIC_COUNTRY=%d.\n",__func__,__LINE__,
                                                IS_NORDIC_COUNTRY(OSD_COUNTRY_SETTING)));
    DEBUG_APP_TTX(printf("---[%s]->%d.OSD_COUNTRY_SETTING=%d.\n",__func__,__LINE__,
                                                OSD_COUNTRY_SETTING));
    DEBUG_APP_TTX(printf("---[%s]->%d.msAPI_OSD_GetOSDLanguage()=%d.\n",__func__,__LINE__,
                                                msAPI_OSD_GetOSDLanguage()));

#if 0
	if(IS_NORDIC_COUNTRY(OSD_COUNTRY_SETTING))
	{
	    //for fixed mantis 1281177---
	    if(msAPI_OSD_GetOSDLanguage() == LANGUAGE_OSD_NORWEGIAN)
		//if(OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY)
		{
			u8BycountryforNordicTest = LANGUAGE_NORWEGIAN;
		}
		else if(msAPI_OSD_GetOSDLanguage() == LANGUAGE_OSD_SWEDISH)
		//else if(OSD_COUNTRY_SETTING == OSD_COUNTRY_SWEDEN)
		{
			u8BycountryforNordicTest = LANGUAGE_SWEDISH;
		}
		else if(msAPI_OSD_GetOSDLanguage() == LANGUAGE_OSD_DANISH)
		//else if(OSD_COUNTRY_SETTING == OSD_COUNTRY_DENMARK)
		{
			u8BycountryforNordicTest = LANGUAGE_DANISH;
		}
		else if(msAPI_OSD_GetOSDLanguage() == LANGUAGE_OSD_FINNISH)
		//else if(OSD_COUNTRY_SETTING == OSD_COUNTRY_FINLAND)
		{
			u8BycountryforNordicTest = LANGUAGE_FINNISH;
		}
		else if(msAPI_OSD_GetOSDLanguage() == LANGUAGE_OSD_IRISH)
		//else if(OSD_COUNTRY_SETTING == OSD_COUNTRY_IRELAND)
		{
			u8BycountryforNordicTest = LANGUAGE_IRISH;
		}
        //-----
	}
	else
#endif
	{
		u8BycountryforNordicTest = GET_OSD_MENU_LANGUAGE();
	}

	if(_GetInitialPage(u8BycountryforNordicTest,
					   &magNum,
					   &pageNum))
	{
		if(MApp_TTX_Get_TTXInfoByTypeAndLang(EN_TTX_INIT_TTX,
											 u8BycountryforNordicTest,
											 &indexMagNum,
											 &indexPageNum))
		{
			msAPI_TTX_SetDTVIndexPage(indexMagNum,
									  indexPageNum);
		}
		else
		{
			msAPI_TTX_SetDTVIndexPage(magNum,
									  pageNum);
		}
	}
}

#endif

#if ENABLE_TTX_ACI
void MApp_TTX_InitACI(void)
{
    // set aciusing only when autoscan!! i.e. tell TTX lib to enable aci detect
    msAPI_TTX_ACIUsing(TRUE);
    // change to aci init state
    enTTXACIState=STATE_TTX_ACI_INIT;
}

void MApp_TTX_ProcessACI(void)
{
    switch (enTTXACIState)
    {
        case STATE_TTX_ACI_INIT:
            if (msAPI_TTX_IsACIAccExist())
            {
                enTTXACIState = STATE_TTX_ACI_WAIT;
                //printf("ACI is found!\n");
                msAPI_TTX_InitialACI(0x1BE);    // 0x1BE or 0x1BC or ....., it depends on country setting
            }
            break;

        case STATE_TTX_ACI_WAIT:
            if (MApp_TopStateMachine_GetTopState() == STATE_TOP_ATV_SCAN)
            {
                // enter ttx-aci!!
                enTTXACIState=STATE_TTX_ACI_FINALIZE_EXIT;
                //printf("enter ttx aci 2...\n");
                MApp_TTX_TeletextCommand(TTX_ACI);
                // modify enTopState to skip go ATV scan processing and make user input works
                MApp_TopStateMachine_SetTopState(STATE_TOP_DIGITALINPUTS);
            }
            break;

        case STATE_TTX_ACI_FINALIZE_EXIT:
            MApp_TTX_AciTryGetScanData();
            break;

        default:
            break;
    }
}

void MApp_TTX_AciTryGetScanData(void)
{
    if (msAPI_TTX_IsACIEnd())   // end of aci
    {
        U_INT8  aciDataState = msAPI_TTX_GetACIDataState();
//      printf("stat %bu\n", aciDataState);
        switch (aciDataState)
        {
            case E_ACI_DATA_STATE_END:

                // reset variable and aciState -- before exit ttx (TTX_TV)
                msAPI_TTX_ACIUsing(FALSE);
                enTTXACIState=STATE_TTX_ACI_NONE;

                // exit ttx
                MApp_TTX_TeletextCommand(TTX_TV);

                // Draw OSD Menu for Scan
                g_u8MsgPageIndex = MENU_SETUP_A1_Scan_AutoScan;

                MApp_UiMenu2_CreateOSDGWin(GWIN_MENU_LEVEL2);
                MApp_UiMenu2_HideOSDGwin(GWIN_MENU_LEVEL2);

                MApp_UiMenu2_CreateOSDGWin(GWIN_AUTO_SCAN); // create auto scan gwin
                MApp_UiMenu2_HideOSDGwin(GWIN_AUTO_SCAN);
                g_u8MenuMainItemIndex = 0;
                g_u8MenuPageIndex = MENU_SETUP_A1_Scan_AutoScan;
                MApp_UiMenu_DrawMenuPage();

                // Clear CH number
                g_u16GroupXPos=0;
                g_u16GroupYPos=0;
                MApp_UiMenu_DrawComponents(DrawA1_Scan_AutoScanBMAP_PROGRESS, EN_CPSTATE_SELECT);
                MApp_UiMenu2_ShowOSDGWin(GWIN_AUTO_SCAN);


                MApp_UiMenuFunc_A_StartAutoScanFunction();

                // before going to end of atv scan, set the atv channel we got!
                u8ScanAtvChNum = msAPI_ATV_GetActiveProgramCount();

                MApp_TopStateMachine_SetTopState(STATE_TOP_ATV_SCAN);
                MApp_ATV_SetATVScanState(STATE_ATV_SCAN_END);

                break;

            case E_ACI_DATA_STATE_READY:
                {
                    // prepare 42 aci data
                    ACI_FMT_DATA aci_data[2];
                    U8   i, iEnd;

                    msAPI_TTX_GetAciData(aci_data);

                    // fixed format 21, variable format 42
                    iEnd = (msAPI_TTX_GetAciDataFormat()==0 ? 1 : 2);

                    for (i=0; i<iEnd; i++)
                    {
                        if (aci_data[i].preset_num == 1000)
                        {
                            break;
                        }
                        else
                        {
                            U8 u8ProgNum;
                            AUDIOSTANDARD_TYPE u8AudType;
                            AVD_VideoStandardType u8VidType;
                            U16 u16Freq;
                            u8ProgNum = aci_data[i].preset_num;
                            u16Freq = msAPI_CFT_ConvertFrequncyToPLL(aci_data[i].frequency_int, aci_data[i].frequency_fraction);
                            if (aci_data[i].information[3]=='I')
                            {
                                switch (aci_data[i].information[4])
                                {
                                    case 'I':
                                        u8AudType = E_AUDIOSTANDARD_BG; u8VidType = E_VIDEOSTANDARD_PAL_BGHI; break;
                                    case 'd':
                                        u8AudType = E_AUDIOSTANDARD_L; u8VidType = E_VIDEOSTANDARD_SECAM; break;
                                    case 's':
                                        u8AudType = E_AUDIOSTANDARD_M; u8VidType = E_VIDEOSTANDARD_PAL_M; break;
                                    case '8':
                                        u8AudType = E_AUDIOSTANDARD_M_BTSC; u8VidType = E_VIDEOSTANDARD_NTSC_M; break;
                                    case '/':
                                        u8AudType = E_AUDIOSTANDARD_I; u8VidType = E_VIDEOSTANDARD_PAL_BGHI; break;
                                    case 'P':
                                        u8AudType = E_AUDIOSTANDARD_DK; u8VidType = E_VIDEOSTANDARD_SECAM; break;
                                    default:
                                        break;
                                }
                            }
                            else if (aci_data[i].information[3]=='s')
                            {
                                u8AudType = E_AUDIOSTANDARD_NOTSTANDARD; u8VidType = E_VIDEOSTANDARD_NOTSTANDARD; break;
                                #if 0
                                switch (aci_data[i].information[5])
                                {
                                    case 'I':
                                        u8AudType = E_AUDIOSTANDARD_NOTSTANDARD; u8VidType = E_VIDEOSTANDARD_NOTSTANDARD; break;
                                    case 'd':
                                        u8AudType = E_AUDIOSTANDARD_NOTSTANDARD; u8VidType = E_VIDEOSTANDARD_NOTSTANDARD; break;
                                    case 's':
                                        u8AudType = E_AUDIOSTANDARD_NOTSTANDARD; u8VidType = E_VIDEOSTANDARD_NOTSTANDARD; break;
                                    case '8':
                                        u8AudType = E_AUDIOSTANDARD_NOTSTANDARD; u8VidType = E_VIDEOSTANDARD_NOTSTANDARD; break;
                                    default:
                                        break;
                                }
                                #endif
                            }

                            msAPI_ATV_SetProgramPLLData(u8ProgNum, u16Freq);
                            msAPI_ATV_SetAudioStandard(u8ProgNum, u8AudType);
                            msAPI_ATV_SkipProgram(u8ProgNum, FALSE);
                            msAPI_ATV_SetFavoriteProgram(u8ProgNum, FALSE);
                            msAPI_ATV_LockProgram(u8ProgNum, FALSE);
                            msAPI_ATV_NeedAFT(u8ProgNum, FALSE);
                            msAPI_ATV_SetVideoStandardOfProgram(u8ProgNum, u8VidType);
                            msAPI_ATV_SetStationName(u8ProgNum, aci_data[i].channel_name);
                        }

                    }
                    msAPI_TTX_ClearACIDataState(0);
                }
                break;
            default:
                break;
        }
    }
    else
    {
        MApp_TTX_AciTimeoutProcess();
    }
}


void MApp_TTX_AciTimeoutProcess(void)
{
    U_INT8  aciTimeoutType = msAPI_TTX_GetACITimeoutType();
    if (aciTimeoutType!=E_ACI_TIMEOUT_NONE)
    {
        if (aciTimeoutType != g_u8ACITimeoutType)   // if the previous type != current type, start the timer!
        {
            g_u32ACITimeout = msAPI_Timer_GetTime0();   // start the timer!
        }
        else    // check if timeout
        {
            U32 time2timeout = 0;
            if (g_u8ACITimeoutType & E_ACI_TIMEOUT_PAGE_NOT_FOUND)  // cannot find aci page in db
            {
                time2timeout = 10000;    // 10 secs
                // checking
                if (msAPI_Timer_DiffTimeFromNow(g_u32ACITimeout)>time2timeout)
                {
                    // show ui -- todo
                    // continue to go processing ATV scan!!
                    // reset variable and aciState -- before exit ttx (TTX_TV)
                    msAPI_TTX_ACIUsing(FALSE);
                    enTTXACIState=STATE_TTX_ACI_NONE;
                    // exit ttx
                    MApp_TTX_TeletextCommand(TTX_TV);
                    // set as ATV scan
                    MApp_TopStateMachine_SetTopState(STATE_TOP_ATV_SCAN);
                    // Draw OSD Menu for Scan
                    g_u8MsgPageIndex = MENU_SETUP_A1_Scan_AutoScan;
                    MApp_UiMenu2_CreateOSDGWin(GWIN_MENU_LEVEL2);
                    MApp_UiMenu2_HideOSDGwin(GWIN_MENU_LEVEL2);
                    //MApp_UiMenu2_DeleteOSDGWin(GWIN_DYNAMICMSG);//delete confirm message
                    MApp_UiMenu2_CreateOSDGWin(GWIN_AUTO_SCAN); // create auto scan gwin
                    MApp_UiMenu2_HideOSDGwin(GWIN_AUTO_SCAN);
                    g_u8MenuMainItemIndex = 0;
                    g_u8MenuPageIndex = MENU_SETUP_A1_Scan_AutoScan;
                    MApp_UiMenu_DrawMenuPage();
                    // Clear CH number
                    g_u16GroupXPos=0;
                    g_u16GroupYPos=0;
                    MApp_UiMenu_DrawComponents(Draw_AutoScan_ATV_Percent, EN_CPSTATE_SELECT);
                    MApp_UiMenu2_ShowOSDGWin(GWIN_AUTO_SCAN);
                    MApp_UiMenuFunc_A_StartAutoScanFunction();
                }
            }
            else if (g_u8ACITimeoutType & E_ACI_TIMEOUT_MULTIPACKAGE_WAITING_INPUT) // no user input timeout when aci multi-package
            {
                time2timeout = 20000;   // 20 secs
                // checking
                if (msAPI_Timer_DiffTimeFromNow(g_u32ACITimeout)>time2timeout)  // timeout
                {
                    msAPI_TTX_GoACIDefaultPage();  // go processing the default page defined in aci milti-package
                }
            }
        }
    }
    else
    {
        // stop counting time!
        g_u32ACITimeout = 0;
    }
    g_u8ACITimeoutType = aciTimeoutType;
}
#endif

#if 0   // SH@ 20090717, testing TTX'S VE functions...(Put this in 'MAPP_MultiTask.c')
/*
 * Testing for VE...
 */
#include "drvTVEncoder.h"

#define MAX_TTX_LINES           6
#define MAX_TTX_LINE_CHARS      48

static U32 u32VETest = 0;
static U8 u8VEFlag = FALSE;
static U8 au8VEdata[MAX_TTX_LINE_CHARS * (MAX_TTX_LINES+1)];

void MApp_TTX_VE_UniTest(void)
{
    U32 i, j;
    U8 *pp;

    if(u32VETest == 0)
        u32VETest = msAPI_Timer_GetTime0();

    // Wait 20 sec, then start to test...
    if((!u8VEFlag) && ((msAPI_Timer_GetTime0()-u32VETest) > 20000))
    {
        u8VEFlag = TRUE;
    }

    if(u8VEFlag && ((msAPI_Timer_GetTime0()-u32VETest) > 20))
    {
        //printf("\n...VE testing...\n");

        // every 20 ms, then it will trigger to encode...
        pp = (U8 *)((((U32)au8VEdata >> 4) << 4) + 16);     // alignment
        memset(pp, 0x00, MAX_TTX_LINE_CHARS * MAX_TTX_LINES);

        for(i=0; i<MAX_TTX_LINES; i++)
        {
            for(j=0; j<MAX_TTX_LINE_CHARS; j++)
            {
                if((j%16) == 15)
                    pp[j+(i*MAX_TTX_LINE_CHARS)] = i;       // Keep line number
                else
                    pp[j+(i*MAX_TTX_LINE_CHARS)] = j%16;    // data: 0x00 ~ 0x0E
            }
        }

        MDrv_VE_SetVbiTtxActiveLines(MAX_TTX_LINES);
        MDrv_VE_SetTtxBuffer((U32)pp, MAX_TTX_LINE_CHARS * MAX_TTX_LINES);

        //printf("\n addr=0x%lx (0x%lx)\n", (U32)pp, (U32)au8VEdata);

        u32VETest = msAPI_Timer_GetTime0();
    }
}
#endif

void MApp_TTX_Set_ChannelChangeTime(void)
{
    msAPI_TTX_SetChannelChangeTime(msAPI_Timer_GetTime0());
}
#if PVR_AND_TTX_DIFF_WITH_MHEG5
void MApp_TTX_TurnTTXOnOff(BOOLEAN bOn)
{
    if(bOn)
    {
        if(g_enTurnOnTTX != TTX_ON)
        {
            g_enTurnOnTTX = TTX_ON;
        #if MHEG5_ENABLE
            MApp_MHEG5_ExitMheg5();
        #endif
            MApp_TTX_SetDTV_TTXSystem(MApp_TTX_GetDefaultTTX_PID(), FALSE);
            msAPI_TTX_Run();
        }
    }
    else
    {
        if(g_enTurnOnTTX != MHEG5_ON)
        {
            g_enTurnOnTTX = MHEG5_ON;
            MApp_TTX_TeletextCommand(TTX_TV);
            MApp_TTX_SetTeletextOnOff(FALSE);
            msAPI_TTX_Stop();
            msAPI_DMX_CloseFilter( *MApp_Dmx_GetFid(EN_TTX_FID));
            MApp_Dmx_SetFid(MSAPI_DMX_INVALID_FLT_ID, EN_TTX_FID);
            msAPI_TTX_VBIAcquireEnable(FALSE);
            msAPI_TTX_ResetAcquisition();
        }
    }
}

BOOLEAN MApp_TTX_CanBeTurnedOn(void)
{
    if (((MApp_SI_CheckMHEG5Status() == SI_MHEG5_WITH_VIDEO) || (MApp_SI_CheckMHEG5Status() == SI_MHEG5_DATA_ONLY))
        &&(!stGenSetting.g_SysSetting.fEnableTTXSubTitle || MApp_Subtitle_Select_Language(u8SubtitleItemSelIdx -1)))
    {
        if(g_enTurnOnTTX != MHEG5_ON)
        {
            MApp_TTX_TurnTTXOnOff(FALSE);
        }
        return FALSE;
    }
    else
    {
        if(g_enTurnOnTTX != TTX_ON)
        {
            MApp_TTX_TurnTTXOnOff(TRUE);
        }
        return TRUE;
    }
}
#endif
#endif // ENABLE_TTX

#undef MAPP_TTX_C
