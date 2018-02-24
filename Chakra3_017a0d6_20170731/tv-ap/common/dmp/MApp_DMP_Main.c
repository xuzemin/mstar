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

#define MAPP_DMP_MAIN_C

/******************************************************************************/
/*                 Header Files                                               */
/* ****************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "debug.h"

// Common Definition
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "MApp_GlobalSettingSt.h"

#include "drvISR.h"
#include "apiDMX.h"
#if ENABLE_CI
#include "msAPI_CI.h"
#endif
#include "apiXC_Sys.h"

#include "MApp_Exit.h"
#include "MApp_Key.h"
#include "MApp_UiMenuDef.h"
#include "MApp_ZUI_Main.h"
#include "ZUI_tables_h.inl"
#include "MApp_DMP_Main.h"
#include "mapp_mplayer.h"
#include "MApp_UiMediaPlayer_Define.h"
#include "IOUtil.h"
//#include "BinInfo.h"
#include "InfoBlock.h"
#include "drvCPU.h"
#include "msAPI_CPU.h"

#include "MApp_APEngine.h"
#include "msAPI_APEngine.h"
#include "msAPI_Timer.h"
#include "msAPI_Memory.h"
#include "msAPI_MIU.h"
#include "MsOS.h"
#include "MApp_InputSource.h"
#include "ZUI_exefunc.h"
#include "mapp_videoplayer.h"
#include "SysInit.h"
#include "msAPI_MPEG_Subtitle.h"
#include "MApp_ZUI_ACTdmp.h"
#include "drvMIU.h"


#if (ENABLE_DMP)
///////////////////////////////////////////////////////////
#define DMP_WAITCONNECT_MS      3000

static ST_DMP_VAR     m_enDmpVar;

extern void MApp_DMP_NotifyUiState(EN_DMP_UI_STATE enDmpUiState);
extern BOOLEAN MApp_UiMediaPlayer_IsSubtitleEnabled(void);

//////////////////////////////////////////////////////////
#if 0
static void _MApp_DMP_StretchOSD(BOOLEAN bEnable)
{
    U8 u8CurGop = MApi_GOP_GWIN_GetCurrentGOP();
    MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD);
    if (bEnable)
    {
        MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_OSD, E_GOP_DST_OP0,0, 0, ZUI_DMP_WIDTH, ZUI_DMP_HEIGHT);
        MApi_GOP_GWIN_Set_HSCALE(TRUE, ZUI_DMP_WIDTH, PANEL_WIDTH);
        MApi_GOP_GWIN_Set_VSCALE(TRUE, ZUI_DMP_HEIGHT, PANEL_HEIGHT);
    }
    else
    {
        MApi_GOP_GWIN_Set_HSCALE(TRUE, ZUI_DMP_WIDTH, ZUI_DMP_WIDTH);
        MApi_GOP_GWIN_Set_VSCALE(TRUE, ZUI_DMP_HEIGHT, ZUI_DMP_HEIGHT);
        MApi_GOP_GWIN_Set_STRETCHWIN(E_GOP_OSD, E_GOP_DST_OP0,0, 0, PANEL_WIDTH, PANEL_HEIGHT);
    }
    MApi_GOP_GWIN_SwitchGOP(u8CurGop);
}
#endif

BOOLEAN MApp_DMP_IsSuccessorWinVisible(HWND hWnd)
{
    HWND child, last_succ;
    last_succ = MApp_ZUI_API_GetLastSuccessor(hWnd);
    for (child = hWnd; child <= last_succ; child++)
    {
        if(child != HWND_DMP_PLAYBACK_TRANSPARENT_BG &&
            MApp_ZUI_API_IsWindowVisible(child))
        {
            return TRUE;
        }
    }
    return FALSE;
}
BOOLEAN MApp_DMP_IsOSDVisible(void)
{
      if (  //MApp_DMP_IsSuccessorWinVisible(HWND_DMP_BG_GRADIENT_TOP)||
            //MApp_DMP_IsSuccessorWinVisible(HWND_DMP_BG_GRADIENT_BOTTOM) ||
            //MApp_DMP_IsSuccessorWinVisible(HWND_DMP_SEL_BAR_GROUP) ||
			MApp_DMP_IsSuccessorWinVisible(HWND_DMP_MENU_BG) ||
            MApp_DMP_IsSuccessorWinVisible(HWND_DMP_MEDIA_TYPE_PAGE) ||
            MApp_DMP_IsSuccessorWinVisible(HWND_DMP_DRIVE_PAGE)||
            MApp_DMP_IsSuccessorWinVisible(HWND_DMP_FILE_SELECT_PAGE) ||
            MApp_DMP_IsSuccessorWinVisible(HWND_DMP_PLAYBACK_PAGE) ||
            MApp_DMP_IsSuccessorWinVisible(HWND_DMP_ALERT_WINDOW) ||
            MApp_DMP_IsSuccessorWinVisible(HWND_DMP_PROGRESS_WINDOW) ||
            MApp_DMP_IsSuccessorWinVisible(HWND_DMP_VOLUME_LIST) ||
            MApp_DMP_IsSuccessorWinVisible(HWND_DMP_DRM_WINDOW) ||
            MApp_DMP_IsSuccessorWinVisible(HWND_DMP_RESUME_STOP_WINDOW)
         )
        {
            return TRUE;
        }
        else
        {
           return FALSE;
        }
}

static void _MApp_DMP_Init(void)
{
    if(!(m_enDmpVar.enDmpFlag & DMP_FLAG_INITED))
    {
        DMP_DBG(printf("MApp_UiMediaPlayer_Init()\n"));

        MApp_MPlayer_InitializeKernel();
        MApp_DMP_SetCurDrvIdxAndCalPageIdx(0);

        m_enDmpVar.enDmpUiState = DMP_UI_STATE_MEDIA_SELECT;

        MApp_MPlayer_InitRepeatMode(E_MPLAYER_REPEAT_ALL);
    #if RANDOM_PLAY
        MApp_MPlayer_InitRandomMode(E_MPLAYER_RANDOM_NONE);
    #endif

        MApp_MPlayer_EnableNotify(E_MPLAYER_NOTIFY_ALL, TRUE);
        // TODO: this line may be redundant?
        //MApp_MPlayer_SetCurrentMediaType(E_MPLAYER_TYPE_PHOTO, FALSE);

    #if( VD_PLAYER_IS_IN_CROP_CPU )
        MApp_VDPlayer_LoadBinToCrop();
    #endif
        m_enDmpVar.enDmpFlag |= DMP_FLAG_INITED;
    }
}

void MApp_DMP_Reset(void)
{
    DMP_DBG(printf("MApp_UiMediaPlayer_Reset()\n"));
    MApp_DMP_SetCurDrvIdxAndCalPageIdx(0);
    m_enDmpVar.enDmpFlag = DMP_FLAG_INITED;
    MApp_MPlayer_InitRepeatMode(E_MPLAYER_REPEAT_ALL);
#if RANDOM_PLAY
    MApp_MPlayer_InitRandomMode(E_MPLAYER_RANDOM_NONE);
#endif
}

static void _MApp_DMP_Switch2Dmp(void)
{
    //MApi_AUDIO_AbsoluteBass(0);  // set the bass to 0 to avoid voice broken
#if ENABLE_DMP_MINI_MENU
    if(MApp_DMP_GetDmpUiState() != DMP_UI_STATE_FILE_SELECT)
#endif
    {
        if( MApp_MPlayer_SetCurrentMediaType(E_MPLAYER_TYPE_PHOTO, TRUE) == E_MPLAYER_RET_FAIL)
        {
            DMP_DBG(printf("MApp_MPlayer_SetCurrentMediaType fail"););
        }
    }
    if(m_enDmpVar.enDmpFlag & DMP_FLAG_INITED)
    {
        DMP_DBG(printf("\n\n\n*******************MApp_DMP_Reset()\n"));
        MApp_DMP_Reset();
        MApp_MPlayer_ConnectDrive(m_enDmpVar.stDrvInfo.au8MapTbl[m_enDmpVar.stDrvInfo.u8Idx]);
    }
    else
    {
        DMP_DBG(printf("\n\n\n*******************_MApp_DMP_Init()\n"));
        _MApp_DMP_Init();
    }

    return;
}

BOOLEAN MApp_DMP_RecalculateDriveMappingTable(void)
{
    MPlayerDrive driveInfo;
    BOOLEAN bConnect = FALSE;
    U8 i, /*j,*/ driveIdx, count=0;

    if(MApp_MPlayer_QueryCurrentDeviceIndex() == E_MPLAYER_USB0 ||
        MApp_MPlayer_QueryCurrentDeviceIndex() == E_MPLAYER_USB1 ||
        MApp_MPlayer_QueryCurrentDeviceIndex() == E_MPLAYER_USB2 ||
        MApp_MPlayer_QueryCurrentDeviceIndex() == E_MPLAYER_USB3)
    {
    // TODO: need to refine for loop!? 20090824
        DMP_DBG(printf("[DMP] Total Drives : %u\n", MApp_MPlayer_QueryTotalDriveNum()));
        memset(m_enDmpVar.stDrvInfo.au8MapTbl, 0xFF, sizeof(U8)*NUM_OF_MAX_DRIVE);
        //for(j = 0; j < NUM_OF_MAX_DRIVE; j++)
        //{//Sorting the partition table.
            for(i = 0; i < NUM_OF_MAX_DRIVE; i++)
            {
                driveIdx = MApp_MPlayer_QueryPartitionIdxInDrive(i, &driveInfo);

                if(driveIdx != 0xFF && driveInfo.eDeviceType != E_MPLAYER_INVALID
                    /*&&j == driveInfo.u8Partition*/)
                {
                    bConnect = TRUE;
                    DMP_DBG(printf("[DMP] %u USB%u  LUN%u   Partition%u\n", driveIdx, (U8)driveInfo.eDeviceType, driveInfo.u8Lun, driveInfo.u8Partition);)
                    {
                        m_enDmpVar.stDrvInfo.au8MapTbl[count++] = driveInfo.u8Partition;
                    }
                }
            } //end of i
        //} //end of j
    }

    return bConnect;
}

U8 MApp_DMP_GetDriveFromMappingTable(U8 u8Idx)
{
    return m_enDmpVar.stDrvInfo.au8MapTbl[u8Idx];
}

void MApp_DMP_InitDMPStat(void)
{
    DMP_DBG(printf("MApp_DMP_InitDMPStat\n"));
    m_enDmpVar.enDmpState = DMP_STATE_INIT;
    m_enDmpVar.enDmpFlag = DMP_FLAG_NONE;
}

void MApp_DMP_Exit(void)
{
    DMP_DBG(printf("MApp_DMP_Exit\n"));
    m_enDmpVar.enDmpState = DMP_STATE_INIT;
    MApp_MPlayer_StopPreview();
    if(m_enDmpVar.enDmpFlag & DMP_FLAG_BGM_MODE)
    {
        MApp_DMP_ClearDmpFlag(DMP_FLAG_BGM_MODE);
        MApp_MPlayer_StopMusic();
    }
    if(m_enDmpVar.enDmpFlag & DMP_FLAG_MEDIA_FILE_PLAYING)
    {
        MApp_MPlayer_Stop();
    }
    m_enDmpVar.enDmpFlag = DMP_FLAG_NONE;
    //MApp_ZUI_API_StoreFocusCheckpoint(HWND_DMP_MEDIA_TYPE_PHOTO);
    MApp_MPlayer_ExitMediaPlayer();

#if( VD_PLAYER_IS_IN_CROP_CPU )
    // Stop aeon CPU
    MDrv_COPRO_Disable();

  #if( ENABLE_AEON_MEM_USE_MIU_PROTECT )
    // Aeon_mem is co-buffer with other IP, so we must disable MIU protect when exit DMP
    // Disable MIU protect
    if( FALSE == MDrv_MIU_Protect(AEON_MEM_USE_MIU_PROTECT_BLOCK_ID, NULL, 0, 0x100000, DISABLE) )
    {
        printf("\nError: Disable MIU protect(%u) failed!\n", AEON_MEM_USE_MIU_PROTECT_BLOCK_ID);
    }
  #endif

#endif

    MsOS_EnableInterrupt(E_INT_IRQ_TSP2HK);
    //MApi_DMX_Init();

}

void MApp_DMP_BW_Control(BOOL bOsdOn)
{
#if 0 // remove for Euler default
    if (bSystemDDR800)
    {
        if(bOsdOn==TRUE)
        {
            MApp_VDPlayer_QuarterPixel(DISABLE);
            MApp_VDPlayer_DeBlocking(DISABLE);
        }
        else
        {
            MApp_VDPlayer_QuarterPixel(ENABLE);
            MApp_VDPlayer_DeBlocking(ENABLE);
        }
    }
#else
    bOsdOn=bOsdOn;
#endif
}

BOOLEAN u8DMPStartFlag = FALSE;
EN_RET MApp_DMP_Main(void)
{
    EN_RET enRetVal = EXIT_NULL;
    static U32 u32time = 0;
    static U8 u8GWinId = 0;
    static EN_DMP_STATE eLastDmpState = DMP_STATE_INIT;


    if( m_enDmpVar.enDmpState != eLastDmpState )
    {
        //printf("DmpMain:DmpState: %u --> %u, DmpUiState=%u\n", eLastDmpState, m_enDmpVar.enDmpState, m_enDmpVar.enDmpUiState );
        eLastDmpState = m_enDmpVar.enDmpState;
    }

    switch(m_enDmpVar.enDmpState)
    {
        case DMP_STATE_INIT:
            //printf("DMP_STATE_INIT\n");
            srand(msAPI_Timer_GetTime0());
            //_MApp_DMP_StretchOSD(TRUE);
            MApp_ZUI_ACT_StartupOSD(E_OSD_DMP);
            _MApp_DMP_Switch2Dmp();
            u32time = msAPI_Timer_GetTime0();
            m_enDmpVar.enDmpState = DMP_STATE_CONNECTING;
            u8GWinId = MApp_ZUI_API_QueryGWinID();
            u8DMPStartFlag = TRUE;
            break;

        case DMP_STATE_CONNECTING:
            if(msAPI_Timer_DiffTimeFromNow(u32time) > DMP_WAITCONNECT_MS
                || m_enDmpVar.enDmpFlag & DMP_FLAG_DRIVE_CONNECT_OK)
            {
                m_enDmpVar.enDmpState = DMP_STATE_UI;
            }
            break;

        case DMP_STATE_UI:
            MApp_DMP_NotifyUiState(m_enDmpVar.enDmpUiState);
            m_enDmpVar.enDmpState = DMP_STATE_WAIT;
            break;

        case DMP_STATE_WAIT:
            //MApp_VDPlayer_MailBoxHandler();
            if(u8KeyCode == KEY_MUTE)
            {
                MApp_ZUI_ProcessKey(u8KeyCode);
                u8KeyCode = KEY_NULL;
                break;
            }
            #if ENABLE_DMP_MINI_MENU
            if((MApp_MPlayer_IsMoviePlaying()))
            {
                MApp_DMP_SetDmpUiState(DMP_UI_STATE_PLAYING_STAGE);
                MApp_DMP_GotoDMPMiniMenu();
            }
            #endif
#if (ENABLE_MPLAYER_MOVIE)
#if DMP_UI_BMPSUBTITLE_EXCLUSIVE
            //Patch for bandwidth issue - disable GOP when no UI on the screen
            if(((MApp_UiMediaPlayer_IsSubtitleEnabled())&&(MApi_GOP_GWIN_GetMaxGOPNum()==1)&&(u8KeyCode == 0xFF)&&(m_enDmpVar.enDmpUiState == DMP_UI_STATE_PLAYING_STAGE)&&(!MApp_DMP_IsOSDVisible())&&(!MApp_MPlayer_IsCurSubtitleText())&&(!msAPI_MpegSP_Get_Render_Status()))
            ||((MApp_UiMediaPlayer_IsSubtitleEnabled())&&(MApi_GOP_GWIN_GetMaxGOPNum()!=1)&&(u8KeyCode == 0xFF)&&(m_enDmpVar.enDmpUiState == DMP_UI_STATE_PLAYING_STAGE)&&(!MApp_DMP_IsOSDVisible())&&(!MApp_MPlayer_IsCurSubtitleText())))
            {
                if(MApi_GOP_GWIN_IsGWINEnabled(u8GWinId))
                {
                    MApi_GOP_GWIN_Enable(u8GWinId, FALSE);
                    MApp_DMP_BW_Control(FALSE);
                    DMP_DBG(printf("MApp_ZUI_API_TerminateGDI dmp_main.c\n"););
                    MApp_ZUI_API_EmptyMessageQueue();
                    MApp_ZUI_API_TerminateGDI();
                    DMP_DBG(printf("draw subtitle 2\n"););
                    msAPI_MpegSP_SetShowStatus(TRUE);
#if(DMP_TS_SUBTITLE_UI_EXCLUSIVE)
                    MApp_TS_Subtitle_SetShowStatus(TRUE);
#endif
                }
            }
            if(u8KeyCode != 0xFF &&
                m_enDmpVar.enDmpUiState == DMP_UI_STATE_PLAYING_STAGE)
            {
                if(((MApi_GOP_GWIN_GetMaxGOPNum()==1)&&(MApp_ZUI_GetActiveOSD() != E_OSD_AUDIO_VOLUME))
                ||((MApi_GOP_GWIN_GetMaxGOPNum()!=1)&&(!MApi_GOP_GWIN_IsGWINEnabled(u8GWinId))))
                {
                    DMP_DBG(printf("close subtitle 0\n"););
                    msAPI_MpegSP_SetShowStatus(FALSE);
#if(DMP_TS_SUBTITLE_UI_EXCLUSIVE)
                    MApp_TS_Subtitle_SetShowStatus(FALSE);
#endif
                    MApp_DMP_BW_Control(TRUE);
                    //Reinit MM OSD
                    {
                        RECT rect;
                        RECT_SET(rect,
                            ZUI_DMP_XSTART, ZUI_DMP_YSTART,
                            ZUI_DMP_WIDTH, ZUI_DMP_HEIGHT);
                        if (!MApp_ZUI_API_InitGDI(&rect))
                        {
                            DMP_DBG(printf("[ZUI]GDI RE-INIT Failed!\n"));
                            //ABORT();
                            //return EXIT_NULL;
                        }
                        DMP_DBG(printf("MApp_ZUI_API_InitGDI \n"););
                    }
                    MApi_GOP_GWIN_Enable(u8GWinId, TRUE);
                }
            }
            else if(m_enDmpVar.enDmpUiState == DMP_UI_STATE_MEDIA_SELECT)
            {
                if(!MApi_GOP_GWIN_IsGWINEnabled(u8GWinId))
                {
                    DMP_DBG(printf("close subtitle 1\n"););
                    msAPI_MpegSP_SetShowStatus(FALSE);
#if(DMP_TS_SUBTITLE_UI_EXCLUSIVE)
                    MApp_TS_Subtitle_SetShowStatus(FALSE);
#endif
                    MApp_DMP_BW_Control(TRUE);
                    //Reinit MM OSD
                    {
                        RECT rect;
                        RECT_SET(rect,
                            ZUI_DMP_XSTART, ZUI_DMP_YSTART,
                            ZUI_DMP_WIDTH, ZUI_DMP_HEIGHT);
                        if (!MApp_ZUI_API_InitGDI(&rect))
                        {
                            printf("[ZUI]GDI RE-INIT Failed 1!\n");
                            //ABORT();
                            //return EXIT_NULL;
                        }
                        DMP_DBG(printf("MApp_ZUI_API_InitGDI 1\n"););
                    }
                    MApi_GOP_GWIN_Enable(u8GWinId, TRUE);
                }
            }
            else if(m_enDmpVar.enDmpUiState == DMP_UI_STATE_FILE_SELECT)
            {
                if(!MApi_GOP_GWIN_IsGWINEnabled(u8GWinId))
                {
                    MApp_DMP_BW_Control(TRUE);
                    //Reinit MM OSD
                    {
                        RECT rect;
                        RECT_SET(rect,
                            ZUI_DMP_XSTART, ZUI_DMP_YSTART,
                            ZUI_DMP_WIDTH, ZUI_DMP_HEIGHT);
                        if (!MApp_ZUI_API_InitGDI(&rect))
                        {
                            printf("[ZUI]GDI RE-INIT Failed  2!\n");
                            //ABORT();
                            //return EXIT_NULL;
                        }
                        DMP_DBG(printf("MApp_ZUI_API_InitGDI 2\n"););
                    }
                    MApi_GOP_GWIN_Enable(u8GWinId, TRUE);
                }
            }
            else
            {
                //for debugging
                //printf("m_enDmpVar.enDmpUiState = %d\n", m_enDmpVar.enDmpUiState);
            }
#endif //DMP_UI_BMPSUBTITLE_EXCLUSIVE
#endif
            MApp_ZUI_ProcessKey(u8KeyCode);
            u8KeyCode = KEY_NULL;
            break;

        case DMP_STATE_CLEAN_UP:
            MApp_ZUI_ACT_ShutdownOSD();
            m_enDmpVar.enDmpState = DMP_STATE_INIT;
            enRetVal =EXIT_MPLAYER_EXIT;
            break;

        case DMP_STATE_GOTO_STANDBY:
            MApp_ZUI_ACT_ShutdownOSD();
            u8KeyCode = KEY_POWER;
            enRetVal =EXIT_MPLAYER_TRAN_STANDBY;
            break;

        case DMP_STATE_GOTO_MENU:
        #if ENABLE_EMBEDDED_PHOTO_DISPLAY
            MApp_MPlayer_StopEmbeddedPhoto();
        #endif
            MApp_ZUI_ACT_ShutdownOSD();
            m_enDmpVar.enDmpState = DMP_STATE_RETURN_FROM_MENU;
            enRetVal = EXIT_MPLAYER_TRAN_MENU;
            break;
        case DMP_STATE_GOTO_INPUTSOURCE:
        #if ENABLE_EMBEDDED_PHOTO_DISPLAY
            MApp_MPlayer_StopEmbeddedPhoto();
        #endif
            MApp_ZUI_ACT_ShutdownOSD();
            m_enDmpVar.enDmpState = DMP_STATE_RETURN_FROM_MENU;
            enRetVal = EXIT_MPLAYER_TRAN_INPUTSOURCE;
            break;

        #if ENABLE_DMP_MINI_MENU
        case DMP_STATE_GOTO_DMP_MINIMENU:
        #if ENABLE_EMBEDDED_PHOTO_DISPLAY
            MApp_MPlayer_StopEmbeddedPhoto();
        #endif
            MApp_ZUI_ACT_ShutdownOSD();
            m_enDmpVar.enDmpState = DMP_STATE_RETURN_FROM_MENU;
            enRetVal = EXIT_MPLAYER_TRAN_DMP_MINIMENU;
            break;
        #endif

        case DMP_STATE_GOTO_PREV_SRC:
            MApp_ZUI_ACT_ShutdownOSD();
            m_enDmpVar.enDmpState = DMP_STATE_INIT;
            enRetVal =EXIT_MPLAYER_EXIT;
            MApp_DMP_Exit();
            MApp_InputSource_RestoreSource();
            //UI_INPUT_SOURCE_TYPE = MApp_InputSource_GetRecordSource();
            //MApp_InputSource_ChangeInputSource();
          #ifdef ATSC_SYSTEM
            MApp_ZUI_ACT_Startup_ChannelInfo_OSD();
          #else
            if(IsAnyTVSourceInUse())
            {
                MApp_ZUI_ACT_Startup_ChannelInfo_OSD();
                //MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_BRIEF_CH_INFO);//channel info bar show twice when exit dmp
            }
            else//non DTV/ATV sources
            {
                MApp_ZUI_ACT_Startup_ChannelInfo_OSD();
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_SOURCE_BANNER);
            }
          #endif
            break;

        case DMP_STATE_RETURN_FROM_MENU:
        #if ENABLE_EMBEDDED_PHOTO_DISPLAY
            MApp_MPlayer_ResumeEmbeddedPhoto();
        #endif
            //printf("DMP_STATE_RETURN_FROM_MENU\n");
            m_enDmpVar.enDmpState = DMP_STATE_UI;
            MApp_ZUI_ACT_StartupOSD(E_OSD_DMP);
            break;
		case DMP_STATE_RESET:
            MApp_DMP_Exit();
            break;
    }
    return enRetVal;
}

U8 MApp_DMP_GetCurDrvIdx(void)
{
    return m_enDmpVar.stDrvInfo.u8Idx;      //drive idx is ZERO base
}

U8 MApp_DMP_GetDrvPageIdx(void)
{
    return m_enDmpVar.stDrvInfo.u8PageIdx;  //page idx is NONE-ZERO base
}

void MApp_DMP_SetCurDrvIdxAndCalPageIdx(U8 u8Idx)
{
    m_enDmpVar.stDrvInfo.u8Idx = u8Idx;
    m_enDmpVar.stDrvInfo.u8PageIdx = ((u8Idx+1) / DMP_DRIVE_NUM_PER_PAGE) + 1; //page idx is NONE-ZERO base
}

void MApp_DMP_SetDrvPageIdx(U8 u8Idx)
{
    m_enDmpVar.stDrvInfo.u8PageIdx = u8Idx;
}

void MApp_DMP_SetDmpFlag(EN_DMP_FLAG flag)
{
    DMP_DBG(printf("set Flag %u\n",flag););
    m_enDmpVar.enDmpFlag |= flag;
}

void MApp_DMP_ClearDmpFlag(EN_DMP_FLAG flag)
{
    DMP_DBG(printf("clear Flag %u\n",flag););
    m_enDmpVar.enDmpFlag &= (EN_DMP_FLAG)~flag;
}

EN_DMP_FLAG MApp_DMP_GetDmpFlag(void)
{
    return m_enDmpVar.enDmpFlag;
}

void MApp_DMP_SetDmpUiState(EN_DMP_UI_STATE state)
{
    //printf("MApp_DMP_SetDmpUiState(%u)\n", state);
    m_enDmpVar.enDmpUiState = state;
}

EN_DMP_UI_STATE MApp_DMP_GetDmpUiState(void)
{
    return m_enDmpVar.enDmpUiState;
}

void MApp_DMP_UiStateTransition(EN_DMP_UI_STATE enState)
{
    //Before UI state transition, checking status of mplayer firstly!
    DMP_DBG(printf("change to stat %u\n",enState););

    //printf("MApp_DMP_UiStateTransition:DmpUiState: %u --> %u\n", m_enDmpVar.enDmpUiState, enState);

    switch(m_enDmpVar.enDmpUiState)
    {
    #if PLAYLIST_BGM
        case DMP_UI_STATE_BGM_FILE_SELECT:
    #endif
        case DMP_UI_STATE_FILE_SELECT:
        {
            MApp_DMP_ClearDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING);
            MApp_DMP_ClearDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING_ERROR);
            enumMPlayerMediaType enMediaType = MApp_MPlayer_QueryCurrentMediaType();
            switch(enMediaType)
            {
    		#if ENABLE_MPLAYER_PHOTO
                case E_MPLAYER_TYPE_PHOTO:
                {
                    if(MApp_MPlayer_QueryPreviewState(enMediaType) == E_PHOTO_PREVIEW_RUNNING)
                    {
                        //printf("stop preview\n");
                        MApp_MPlayer_StopPreview();
                    }
                    DMP_DBG(printf("MApp_DMP_UiStateTransition E_MPLAYER_TYPE_PHOTO\n"););
                    //MApp_MPlayer_LeaveThumbnailMode();
                }
                break;
			#endif
		    #if ENABLE_MPLAYER_MUSIC
                case E_MPLAYER_TYPE_MUSIC:
                {
                    if(MApp_MPlayer_QueryPreviewState(enMediaType) == E_MUSIC_PREVIEW_RUNNING)
                    {
                        MApp_MPlayer_StopPreview();
                    }
                }
                break;
			#endif
    		#if ENABLE_MPLAYER_MOVIE
                case E_MPLAYER_TYPE_MOVIE:
                {
                    if(MApp_MPlayer_QueryPreviewState(enMediaType) == E_MOVIE_PREVIEW_RUNNING
                        || MApp_MPlayer_QueryPreviewState(enMediaType) == E_MOVIE_PREVIEW_1ST_FRAME_PREDECODE
                        || MApp_MPlayer_QueryPreviewState(enMediaType) == E_MOVIE_PREVIEW_1ST_FRAME_DECODE)
                    {
                        MApp_MPlayer_StopPreview();
                    }
                    #if ENABLE_DMP_MINI_MENU
                    if(!(MApp_DMP_GetDmpFlag() & DMP_FLAG_DRIVE_CONNECT_OK))
                        MApp_DMP_SetDmpFlag(DMP_FLAG_DRIVE_CONNECT_OK);
                    if(!(MApp_DMP_GetDmpFlag() & DMP_FLAG_INITED))
                        MApp_DMP_SetDmpFlag(DMP_FLAG_INITED);
                    #endif
                }
                break;
			#endif
   			#if ENABLE_MPLAYER_TEXT
                case E_MPLAYER_TYPE_TEXT:
                {
                    if(MApp_MPlayer_QueryPreviewState(enMediaType) == E_TEXT_PREVIEW_RUNNING)
                    {
                        MApp_MPlayer_StopPreview();
                    }
                }
                break;
			#endif
                default:
                    break;
            }
        }
        break;

        case DMP_UI_STATE_PLAYING_STAGE:
        {
        #if SLIDESHOW_STOP_BGM_STOP
            if(m_enDmpVar.enDmpFlag & DMP_FLAG_BGM_MODE)
            {
                MApp_MPlayer_StopMusic();
                MApp_DMP_ClearDmpFlag(DMP_FLAG_BGM_MODE);
            }
        #endif
            if(m_enDmpVar.enDmpFlag & DMP_FLAG_MEDIA_FILE_PLAYING)
            {
                MApp_MPlayer_Stop();
                MApp_DMP_ClearDmpFlag(DMP_FLAG_MEDIA_FILE_PLAYING);
            }
        }
        break;

        default:
            break;
    }
    m_enDmpVar.enDmpState = DMP_STATE_UI;
    m_enDmpVar.enDmpUiState = enState;
}

BOOLEAN MApp_DMP_GotoMainMenu(void)
{
    if((m_enDmpVar.enDmpState == DMP_STATE_INIT
        || m_enDmpVar.enDmpState == DMP_STATE_WAIT
        || m_enDmpVar.enDmpState == DMP_STATE_UI )
        &&(m_enDmpVar.enDmpUiState != DMP_UI_STATE_LOADING)
        )
    {
        //printf("m_enDmpVar.enDmpState = DMP_STATE_GOTO_MENU;\n");
        m_enDmpVar.enDmpState = DMP_STATE_GOTO_MENU;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOLEAN MApp_DMP_GotoInputSrcMenu(void)
{
    if((m_enDmpVar.enDmpState == DMP_STATE_INIT
        || m_enDmpVar.enDmpState == DMP_STATE_WAIT
        || m_enDmpVar.enDmpState == DMP_STATE_UI)
        &&(m_enDmpVar.enDmpUiState != DMP_UI_STATE_LOADING)
        )
    {
        //printf("m_enDmpVar.enDmpState = DMP_STATE_GOTO_INPUTSOURCE;\n");
        m_enDmpVar.enDmpState = DMP_STATE_GOTO_INPUTSOURCE;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

#if ENABLE_DMP_MINI_MENU
BOOLEAN MApp_DMP_GotoDMPMiniMenu(void)
{
    if((m_enDmpVar.enDmpState == DMP_STATE_INIT
        || m_enDmpVar.enDmpState == DMP_STATE_WAIT
        || m_enDmpVar.enDmpState == DMP_STATE_UI)
        &&(m_enDmpVar.enDmpUiState != DMP_UI_STATE_LOADING)
        )
    {
        //printf("m_enDmpVar.enDmpState = DMP_STATE_GOTO_INPUTSOURCE;\n");
        m_enDmpVar.enDmpState = DMP_STATE_GOTO_DMP_MINIMENU;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
#endif

BOOLEAN MApp_DMP_GotoPreSrc(void)
{
    if(m_enDmpVar.enDmpState == DMP_STATE_INIT
        || m_enDmpVar.enDmpState == DMP_STATE_WAIT
        || m_enDmpVar.enDmpState == DMP_STATE_UI)
    {
        m_enDmpVar.enDmpState = DMP_STATE_GOTO_PREV_SRC;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOLEAN MApp_DMP_IsFileTypeByIdx(U16 u16Idx)
{
    MPlayerFileInfo stFileInfo;

    if(MApp_MPlayer_QueryFileInfo(E_MPLAYER_INDEX_CURRENT_DIRECTORY, u16Idx, &stFileInfo) == E_MPLAYER_RET_OK)
    {
        if(!(stFileInfo.eAttribute & E_MPLAYER_FILE_DIRECTORY))
        {
            return TRUE;
        }
    }

    return FALSE;
}

U16 MApp_DMP_QueryTotalPlayListNum(void)
{
    U16 u16PlayListNum = MApp_MPlayer_QuerySelectedFileNum(MApp_MPlayer_QueryCurrentMediaType());

    if(MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_ONE_DIRECTORY
        || MApp_MPlayer_QueryPlayMode() == E_MPLAYER_PLAY_ONE_DIRECTORY_FROM_CURRENT)
    {
        u16PlayListNum = MApp_MPlayer_QueryTotalFileNum() - MApp_MPlayer_QueryDirectoryNumber();
    }

    return u16PlayListNum;
}


void MApp_DMP_GetZUIFbAttr(GOP_GwinFBAttr *pFbAttr)
{
    U8 CopyFbID;
    CopyFbID = MApp_ZUI_ACT_GetCopyFbId();
    if(CopyFbID == 0)
    {
        printf("\x1b[31m" "Thumbnail Define is Closed!!!(DMP_PHOTO_THUMBNAIL, DMP_MOVIE_THUMBNAIL, DMP_MUSIC_THUMBNAIL)" "\x1b[0m""\n");
    }
    else{
        MApi_GOP_GWIN_GetFBInfo(MApp_ZUI_ACT_GetCopyFbId(), pFbAttr);
    }
}
void MApp_DMP_SetDMPStat(EN_DMP_STATE stat)
{
    m_enDmpVar.enDmpState = stat;
}

EN_DMP_STATE MApp_DMP_GetDMPStat(void)
{
    return m_enDmpVar.enDmpState;
}

#endif // #if (ENABLE_DMP)

#undef MAPP_DMP_MAIN_C

