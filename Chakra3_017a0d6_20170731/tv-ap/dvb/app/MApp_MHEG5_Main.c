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

#define _MAPP_MHEG5_MAIN_C_

/******************************************************************************/
/*                            Header Files                                    */
/* ****************************************************************************/
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include <string.h>

#include "debug.h"

#if MHEG5_ENABLE
#include "MApp_MHEG5_Main.h"

#include "MApp_MVDMode.h"
#include "MApp_GlobalFunction.h"
#include "MApp_SignalMonitor.h"
#include "mapp_demux.h"
#include "MApp_Scaler.h"
#include "MApp_XC_Sys.h"
#include "MApp_Audio.h"
#include "MApp_MVDMode.h"
#include "MApp_TV.h"
#include "msAPI_MailBox.h"

#include "MsTypes.h"
#include "drvBDMA.h"
#include "hwreg.h"
#include "apiXC.h"
#include "apiXC_Sys.h"
#include "msAPI_audio.h"
#include "MApp_ChannelChange.h"
#include "MApp_TopStateMachine.h"
#include "MApp_PCMode.h"
#include "MApp_UiMenuDef.h"
#include "MApp_ZUI_Main.h"
#include "ZUI_tables_h.inl"

#include "ZUI_exefunc.h" //ZUI
#include "MApp_ZUI_ACTcoexistWin.h"
#include "mapp_si.h"
#include "MApp_Main.h"
#include "MApp_Sleep.h"
#include "msAPI_MHEG5.h"
#include "mapp_mheg5.h"
#include "mapp_iframe.h"

#include "MApp_Subtitle.h"

#include "msAPI_CPU.h"
#include "msAPI_DrvInit.h"
#include "msAPI_Timer.h"
#if INTERACTION_CHANNEL
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include "msAPI_Sha1.h"
#endif
#if ENABLE_CI
#include "msAPI_CI.h"
#include "MApp_CIMMI.h"
#endif
#if CIPLUS_MHEG_1_3
#include "msAPI_MPEG_Subtitle.h"
#endif
// panel module
#include "Panel.h"
#include "apiPNL.h"
#include "apiGOP.h"
#if (ENABLE_PVR == 1)
#include "MApp_ZUI_ACTpvr.h"
#endif
#include "MApp_ZUI_ACTmenufunc.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_ZUI_ACTsublang.h"

#if (ENABLE_PIP)
#include "MApp_PIP.h"
#endif


static void MApp_MHEG5_SendVID_ChangeStream(void);
static void MApp_MHEG5_PreProcess(void);
static void MApp_MHEG5_Restore_FullScreen(void);
static void MApp_MHEG5_GOP_GWIN_SwitchGOP(U8 u8GOP);
static void MApp_MHEG5_Display_Finalize(void);
static void MApp_MHEG5_SetGraphInfoMonitor(void);
static void MApp_MHEG5_ResumeAV(void);
extern BOOLEAN g_PIDfromMHEG5;
extern U16 g_u16MHEG5_VideoPID;
extern U16 g_u16MHEG5_AudioPID;
extern BOOLEAN g_bCloseSubtitleAndOpenMheg5;
BOOLEAN g_ExitMhegTottx=false;

#define GFX_PRE_SCALER      0
#define CheckM5Sate         0
#define MAX_SIGNAL_LOST_TIMES        3
#define ENABLE_UPDATE_MHEG5_FRAME_BUFFER  TRUE

static BOOLEAN  g_bGoMHEG5Process = FALSE;
static U8       g_u8PrePlayMode;
static BOOLEAN  g_bPre_IsImageFrozen = FALSE;

EN_MHEG5_STATE enMHEG5State = STATE_MHEG5_INIT;
BOOL _EnableCheckMHEG5Status=TRUE;

#define M5DBG(x) //x
/******************************************************************************/
/*              Local                                                         */
/* ****************************************************************************/
U8 MHEG5_GWINID, MHEG5_RT_FBID;

#if MHEG5_STATIC_FB
U8 MHEG5_OS_FBID = 0;
#endif
//ZUI_TODO: static MenuItemActionType MHEG5_HOTKEY_MODE = MIA_NOTHING;
//ZUI: extern EN_DISP_WINDOW_TYPE enCurTVWin;

static U8 u8PreKeyCode;

//  default pid and type of AV in current channel
static U16 wPreVideo_PID,wPreAudio_PID,wPreAudioType;
VDEC_CodecType ePreVideoType;
//  end

static U32 _u32StartMheg5Time = 0;
static BOOLEAN _bMheg5Runing = FALSE;

/******************************************************************************/
///- extern M5API
/******************************************************************************/
extern void M5API_GFX_SetMHEGDrawFlag(bool bDrawing);

/******************************************************************************/


/******************************************************************************/
/// this will keep MHEG-5 default program type
/// @param video \b : IN - default video
/// @param audio \b : IN - default audio
/// @param audioType \b : IN - default audio type
/// @param bAVCH264 \b : IN - H264 or not
/******************************************************************************/
void MApp_MHEG5_Update_Program(U16 video, U16 audio, U16 audioType, VDEC_CodecType eVideoType )
{
    wPreVideo_PID=video;
    wPreAudio_PID=audio;
    wPreAudioType = audioType;
    ePreVideoType= eVideoType;

}
////////////////////////////////////////////////////////////////////////////////

#if CheckM5Sate
EN_MHEG5_STATE enMHEG5StateBK = STATE_MHEG5_INIT;
/******************************************************************************/
/// this will print MHEG-5 State
/******************************************************************************/
void MApp_Check_MHEG5_State(void)
{
    if(enMHEG5State != enMHEG5StateBK)
    {
        putchar('M');putchar('5');putchar(':');
        switch(enMHEG5State)
        {
            case STATE_MHEG5_INIT:
                putchar('I');putchar('n');putchar('i');putchar('t');
                break;
            case STATE_MHEG5_WAIT:
                putchar('I');putchar('d');putchar('l');putchar('e');
                break;
            case STATE_MHEG5_CHANNEL_CHANGE:
                putchar('C');putchar('h');putchar('C');putchar('g');
                break;
            case STATE_MHEG5_TO_MENU:
                putchar('M');putchar('e');putchar('n');putchar('u');
                break;
            case STATE_MHEG5_EXIT:
                putchar('M');putchar('E');putchar('x');putchar('t');
                break;
            case STATE_MHEG5_MENU_EXIT:
                putchar('M');putchar('M');putchar('E');putchar('X');
                break;
            case STATE_MHEG5_WITH_OSD:
                putchar( 'O' );putchar( 'S' );putchar( 'D' );putchar( '_' );
                break;
            case STATE_MHEG5_NONE:
                putchar('N');putchar('o');putchar('n');putchar('e');
                break;
            default:
                putchar('D');putchar('e');putchar('f');putchar('a');
                break;

        }
        putchar('\n');
        enMHEG5StateBK = enMHEG5State;
    }
}
#endif

/******************************************************************************/
/// this will set MHEG-5 State
/// @param state \b : IN MHEG-5 State
/******************************************************************************/
void msAPI_SetMHEG5_State(M5_MB_RETURN_STATE state)
{
    switch(state)
    {
        case MB_RETURN_51_STATE_CHANNEL_CHANGE:
            if(enMHEG5State == STATE_MHEG5_WAIT)
                enMHEG5State = STATE_MHEG5_CHANNEL_CHANGE;
            break;
        case MB_RETURN_51_STATE_MHEG5_TO_MENU:
            if(enMHEG5State == STATE_MHEG5_WAIT)
                enMHEG5State = STATE_MHEG5_TO_MENU;
            break;
        case MB_RETURN_MHEG5_EXIT:
            if(enMHEG5State == STATE_MHEG5_TO_MENU)
            {
                enMHEG5State = STATE_MHEG5_MENU_EXIT;
                msAPI_MHEG5_SetGoBackMHEG5(true);
            }
            else if(enMHEG5State == STATE_MHEG5_CHANNEL_CHANGE)
            {
                enMHEG5State = STATE_MHEG5_EXIT;
            }
            else
            {
                enMHEG5State = STATE_MHEG5_EXIT;
            }
            break;
        case MB_RETURN_MHEG5_CHANNELCHANGE:
            enMHEG5State = STATE_MHEG5_EXIT;
            break;
        case MB_RETURN_MHEG5_SELECTED_QUIT_SEL:
            enMHEG5State = STATE_MHEG5_MENU_EXIT;
            msAPI_MHEG5_SetGoBackMHEG5(true);
            u8KeyCode = KEY_SELECT;
            break;
        case MB_RETURN_MHEG5_SELECTED_QUIT_0:
            enMHEG5State = STATE_MHEG5_MENU_EXIT;
            msAPI_MHEG5_SetGoBackMHEG5(true);
            u8KeyCode = KEY_0;
            break;
        case MB_RETURN_MHEG5_SELECTED_QUIT_1:
            enMHEG5State = STATE_MHEG5_MENU_EXIT;
            msAPI_MHEG5_SetGoBackMHEG5(true);
            u8KeyCode = KEY_1;
            break;
        case MB_RETURN_MHEG5_SELECTED_QUIT_2:
            enMHEG5State = STATE_MHEG5_MENU_EXIT;
            msAPI_MHEG5_SetGoBackMHEG5(true);
            u8KeyCode = KEY_2;
            break;
        case MB_RETURN_MHEG5_SELECTED_QUIT_3:
            enMHEG5State = STATE_MHEG5_MENU_EXIT;
            msAPI_MHEG5_SetGoBackMHEG5(true);
            u8KeyCode = KEY_3;
            break;
        case MB_RETURN_MHEG5_SELECTED_QUIT_4:
            enMHEG5State = STATE_MHEG5_MENU_EXIT;
            msAPI_MHEG5_SetGoBackMHEG5(true);
            u8KeyCode = KEY_4;
            break;
        case MB_RETURN_MHEG5_SELECTED_QUIT_5:
            enMHEG5State = STATE_MHEG5_MENU_EXIT;
            msAPI_MHEG5_SetGoBackMHEG5(true);
            u8KeyCode = KEY_5;
            break;
        case MB_RETURN_MHEG5_SELECTED_QUIT_6:
            enMHEG5State = STATE_MHEG5_MENU_EXIT;
            msAPI_MHEG5_SetGoBackMHEG5(true);
            u8KeyCode = KEY_6;
            break;
        case MB_RETURN_MHEG5_SELECTED_QUIT_7:
            enMHEG5State = STATE_MHEG5_MENU_EXIT;
            msAPI_MHEG5_SetGoBackMHEG5(true);
            u8KeyCode = KEY_7;
            break;
        case MB_RETURN_MHEG5_SELECTED_QUIT_8:
            enMHEG5State = STATE_MHEG5_MENU_EXIT;
            msAPI_MHEG5_SetGoBackMHEG5(true);
            u8KeyCode = KEY_8;
            break;
        case MB_RETURN_MHEG5_SELECTED_QUIT_9:
            enMHEG5State = STATE_MHEG5_MENU_EXIT;
            msAPI_MHEG5_SetGoBackMHEG5(true);
            u8KeyCode = KEY_9;
            break;
        default:
            break;
    }
}

/******************************************************************************/
/// this will make MHEG5 exit
/******************************************************************************/
void MApp_MHEG5_Force_Exit(void)
{
    int wait;
    MBX_MSGQ_Status MsgQueueStatus;
    MBX_Result mbx_result;
    U32 u32CurrentMsgNumber = 0;
    MBX_Msg msg;

    //printf("force exit MHEG5\n");

    memset(&MsgQueueStatus, 0, sizeof(MBX_MSGQ_Status));
    memset(&msg, 0, sizeof(MBX_Msg));

#if 0//MHEG5_NDT
    if (msAPI_MHEG5_BeWaitingNDTPid())
    {
        printf("ndt no force exit mheg when disable channel in ndt....\n");
        return;
    }
    else
    {
        printf("force exit mheg...\n");
    }
#endif

    if(enMHEG5State == STATE_MHEG5_WAIT)
    {
    #if CIPLUS_MHEG
        // reset CIMHEG variable
        if (msAPI_IsCIMHEGRun()!=E_MHEG_CI_OFF)
        {
            msAPI_MHEG5_SendCIMHEGAbort();
            msAPI_MHEG5_SetCIMHEGRun(E_MHEG_CI_OFF);
        }
    #endif

        // Switch to MHEG5 GOP0
        MApp_MHEG5_GOP_GWIN_SwitchGOP(MHEG5_GOP);
        wait=0;

    #if CIPLUS_MHEG_1_3
        msAPI_MHEG5_Key_Transmit( KEY_MENU, 0 );
    #else
        msAPI_MHEG5_Key_Transmit( KEY_INFO, 0 );
    #endif

        while(wait++ < 200)
        {
            msAPI_Timer_Delayms(10);
            mbx_result = MSApi_MBX_GetMsgQueueStatus(E_MBX_CLASS_MHEG5_STATE, &MsgQueueStatus);

            if(MsgQueueStatus.status & MBX_STATUS_QUEUE_HAS_INSTANT_MSG)
                u32CurrentMsgNumber = MsgQueueStatus.u32InstantMsgCount;
            else if(MsgQueueStatus.status & MBX_STATUS_QUEUE_HAS_NORMAL_MSG)
                u32CurrentMsgNumber = MsgQueueStatus.u32NormalMsgCount;

            if(u32CurrentMsgNumber>0)
            {
                if(MSApi_MBX_RecvMsg(E_MBX_CLASS_MHEG5_STATE, &msg, 0, MBX_CHECK_NORMAL_MSG) == E_MBX_SUCCESS)
                {
                    if(((U8)msg.u8Index) == MB_MHEG5_STATE_CMD_EXIT)
                    {
                        //printf("force exit MHEG5---\n");
                        break;
                    }
                }
            }
        }

        MApp_MHEG5_Display_Finalize();

        if(g_MHEG5Video.bIFrame)
        {
            MApp_IFrame_Hide();
        }
        // Switch back to OSD GOP1
        MApp_MHEG5_GOP_GWIN_SwitchGOP(E_GOP_OSD);
#if 0 //for compile error
        if (MHEG5_HOTKEY_MODE == MIA_MUTE )
        {
            MHEG5_HOTKEY_MODE = MIA_NOTHING;
        }

        MApp_UiMenu2_SwitchToGwin(g_u8CurOSDGwinID);
#endif
        enMHEG5State = STATE_MHEG5_INIT;

        //2008.05.08: We add this because video doesn't return to fullscreen after force exit.
        if(!g_MHEG5Video.bFullScreen)
        {
            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, 300, MAIN_WINDOW);
            stSystemInfo[MAIN_WINDOW].enAspectRatio = MApp_Scaler_GetAspectRatio(MAIN_WINDOW,ST_VIDEO.eAspectRatio);
            MApp_Scaler_SetWindow(NULL, NULL, NULL,
                                           stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
        }
        MApp_MHEG5_SetGoMHEG5Process(FALSE);
        if ( MApi_XC_IsBlackVideoEnable(MAIN_WINDOW) )
        {
            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, 100, MAIN_WINDOW);
        }
        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_MHEG5, DISABLE, 0, MAIN_WINDOW);

        // keep OSD layer always on top
        //MApi_GOP_GWIN_OutputLayerSwitch(MHEG5_GOP);
        MApp_MHEG5_Restore_FullScreen();
        msAPI_MHEG5_SetRun( FALSE );

        MApp_MHEG5_RestoreOriginalAV();
        // resume av if needed
        MApp_MHEG5_ResumeAV();
		if(stGenSetting.g_SysSetting.fEnableSubTitle == TRUE  && msAPI_VID_GetPlayMode()!= MSAPI_VID_PLAY)
            msAPI_VID_Command(MSAPI_VID_PLAY);
    }
#if CIPLUS_MHEG
    // reset CIMHEG variable
    else if (msAPI_IsCIMHEGRun()!=E_MHEG_CI_OFF)
    {
        msAPI_MHEG5_SetCIMHEGRun(E_MHEG_CI_OFF);
        msAPI_MHEG5_SendCIMHEGExitWaitBootState();
    }
#endif
    MApp_MHEG5_Enable_LiveMHEG5(TRUE);
}

static void MApp_MHEG5_ResumeAV()
{
    // resume video if needed

    if(wPreVideo_PID != INVALID_PID  && wPreVideo_PID == g_u16Current_VideoPID)
    {
        if ( (g_u8PrePlayMode == MSAPI_VID_PLAY && msAPI_VID_GetPlayMode()!= MSAPI_VID_PLAY))
        {
            msAPI_VID_Command(MSAPI_VID_PLAY);
            gbPVRSetModeWhenExitMheg5 = TRUE;

            g_bIsImageFrozen = g_bPre_IsImageFrozen;
            MApi_XC_FreezeImg(g_bIsImageFrozen, MAIN_WINDOW);
        }
    }

    // resume audio if needed
    if (msAPI_MHEG_AUD_GetMadCmd()!=AU_DVB_DECCMD_PLAY)
    {
        MApi_AUDIO_SetCommand(MSAPI_AUD_DVB_DECCMD_PLAY);
    }
}

/******************************************************************************/
/// this will do signal monitor in MHEG and do the related works
/******************************************************************************/
void MApp_MHEG5_SignalMonitor()
{
    BOOLEAN bFE_Result = FE_NOT_LOCK;
    static U8 u8SignalUnlockTimes = 0;
    static U32 u32MHEGSignalMonitorTimer = 0;

    if (u8SignalUnlockTimes <= MAX_SIGNAL_LOST_TIMES &&  msAPI_Timer_DiffTimeFromNow( u32MHEGSignalMonitorTimer ) > 100 ) //unit = ms //20071009 for display no signal in MHEG5 mode
    {
        msAPI_Tuner_CheckLock( &bFE_Result, FALSE );
        u32MHEGSignalMonitorTimer = msAPI_Timer_GetTime0();
        if ( bFE_Result == FE_LOCK )
        {
            u8SignalUnlockTimes=0; // set as 0
        }
        else
        {
            u8SignalUnlockTimes++;      // increase signal lost counts
        }
        if(u8SignalUnlockTimes == MAX_SIGNAL_LOST_TIMES
        #if CIPLUS_MHEG
            // Neotion CI Plus Starting Kit: still need to run MHEG CIMMI when no signal
            && msAPI_IsCIMHEGRun()==E_MHEG_CI_OFF
        #endif
            )
        {
            msAPI_MHEG5_SetGoBackMHEG5(true);
            // please do not replace this "ForceExit" with "QuitOSD" because the code flow is already modified in Chakra2
            MApp_MHEG5_Force_Exit();
        }
    }
}

/******************************************************************************/
/// this will tell MHEG-5 Engine the address of frame buffer
/******************************************************************************/
static void MApp_MHEG5_Update_Frame_Buffer(void)
{
    GOP_GwinInfo gwin_OS;
    GOP_GwinFBAttr fbAttr;

    // update "render target and gwin" framebuffer address
    MApi_GOP_GWIN_GetFBInfo(MHEG5_RT_FBID,&fbAttr);
    MApi_GOP_GWIN_GetWinInfo(MHEG5_GWINID, &gwin_OS);
    msAPI_MHEG5_SendFBGWinOSAddr(fbAttr.addr, gwin_OS.u32DRAMRBlkStart);

    // update "DLA" framebuffer address
    MApi_GOP_GWIN_GetFBInfo(u8MHEG5_DLA_FBID, &fbAttr);
    msAPI_MHEG5_SendDLAInfo(fbAttr.addr);
    msAPI_MHEG5_UpdateDLAFBAddress(fbAttr.addr);
#if(ENABLE_CI && ENABLE_CI_PLUS && CIPLUS_MHEG)
    msAPI_CI_SetMHEG5BufAddr(_PA2VA(fbAttr.addr));
#endif
    //printf("MApp_MHEG5_Update_Frame_Buffer : 0x%x\n",fbAttr.addr);
}
#if ENABLE_UPDATE_MHEG5_FRAME_BUFFER
static void _MApp_MHEG5_fpGOP_CB(MS_U32 u32EventID, void* reserved0)
{
    reserved0=reserved0;
    if(enMHEG5State == STATE_MHEG5_WAIT)
    {
        if(E_GOP_EVENT_BUF_ARRANGE_BEGIN == u32EventID)
        {
            MApi_GFX_BeginDraw();
        }
        else if(E_GOP_EVENT_BUF_ARRANGE_END == u32EventID)
        {
            MApp_MHEG5_Update_Frame_Buffer();
            MApi_GFX_EndDraw();
        }
    }
}
#endif

void MApp_MHEG5_fpGOP_CB(MS_U32 u32EventID, void* reserved0)
{
    _MApp_MHEG5_fpGOP_CB(u32EventID, reserved0);
}

static void _MApp_MHEG5_Idle_ProcessUserInput(void);

/******************************************************************************/
/// this will set go mheg5 process or not
/******************************************************************************/
void MApp_MHEG5_SetGoMHEG5Process(BOOLEAN bEnable)
{
    g_bGoMHEG5Process = bEnable;
}

/******************************************************************************/
/// this will tell to go mheg5 process or not
/******************************************************************************/
BOOLEAN MApp_MHEG5_CheckGoMHEG5Process()
{
    return g_bGoMHEG5Process;
}

/******************************************************************************/
/// MHEG5 pre-process
/******************************************************************************/
static void MApp_MHEG5_PreProcess()
{

    msAPI_MHEG5_SetRun(TRUE);
    //g_u8MenuPageIndex = MAXMENU;//no need anymore(press number key is fixed outside)
    wPreVideo_PID=g_u16Current_VideoPID;
    wPreAudio_PID=g_u16Current_AudioPID;

    u8PreKeyCode = KEY_NULL;

#if MHEG5_WITH_OSD
    if(enMHEG5State == STATE_MHEG5_WAIT)
    {
        MApp_MHEG5_Update_Frame_Buffer();
    }
#endif

}

/******************************************************************************/
/// MHEG5 quit detect
/******************************************************************************/
BOOLEAN MApp_MHEG5_Quit_Detection(void)
{
    //==================================================
    //4. CHANNEL EDIT OSD showing?
    if(MApp_ZUI_GetActiveOSD()==E_OSD_PROGRAM_EDIT
	#if PVR_AND_TTX_DIFF_WITH_MHEG5
		|| MApp_TTX_CanBeTurnedOn()
	#endif
		)
    {
        MApp_MHEG5_Force_Exit();
        MApp_MHEG5_SetGoMHEG5Process(FALSE);
        msAPI_MHEG5_SetGoBackMHEG5(true);
        //printf("Quit by CHANNEL_EDIT\n");
        return FALSE;
    }

    return TRUE;
    //==================================================
}

void MApp_MHEG5_RestoreOriginalAV(void)
{
    if(wPreVideo_PID != g_u16Current_VideoPID || wPreAudio_PID != g_u16Current_AudioPID)
    {
        U16 u16TVPosition,u16RadioPosition;
#if NORDIG_FUNC //for Nordig Spec v2.0
        U16 u16DataPosition;
#endif
        gbPVRSetModeWhenExitMheg5 = TRUE;

        u16TVPosition=g_wCurrentTVUserServicePosition;
        u16RadioPosition=g_wCurrentRadioUserServicePosition;
    #if NORDIG_FUNC //for Nordig Spec v2.0
        u16DataPosition=g_wCurrentDataUserServicePosition;
    #endif
        g_PIDfromMHEG5 = true;
        g_u16MHEG5_VideoPID=wPreVideo_PID;
        g_u16MHEG5_AudioPID=wPreAudio_PID;

        if(wPreVideo_PID == g_u16Current_VideoPID)
        {
            msAPI_MHEG_AUD_ChangeAudPid(g_u16MHEG5_AudioPID,wPreAudioType);
            g_u16Current_AudioPID=g_u16MHEG5_AudioPID;
        }
        else
        {
            MApp_ChannelChange_DisableChannel(false, MAIN_WINDOW);
            g_u16MHEG5_AudioPID&=0x1FFF;
            if(wPreAudioType == E_AUDIOSTREAM_AC3)
            {
                g_u16MHEG5_AudioPID|=0x8000;
            }
            else if(wPreAudioType == E_AUDIOSTREAM_MPEG4)
            {
                g_u16MHEG5_AudioPID|=0x2000;
            }
            else if(wPreAudioType == E_AUDIOSTREAM_AAC)
            {
                g_u16MHEG5_AudioPID|=0x4000;
            }
            else if(wPreAudioType == E_AUDIOSTREAM_AC3P)
            {
                g_u16MHEG5_AudioPID|=0x6000;
            }
            msAPI_VID_SetMappingAVCParameter(ePreVideoType);

            MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
        }
        g_wCurrentTVUserServicePosition=u16TVPosition;
        g_wCurrentRadioUserServicePosition=u16RadioPosition;
    #if NORDIG_FUNC //for Nordig Spec v2.0
        g_wCurrentDataUserServicePosition=u16DataPosition;
    #endif
        g_PIDfromMHEG5 = false;
    }
}

/******************************************************************************/
/// MHEG5 main process
/******************************************************************************/
void _MApp_MHEG5_Process(void)
{
    int i;
    //static U16 wPreVideo_PID,wPreAudio_PID;
    //U8 u8TopState = MApp_TopStateMachine_GetTopState();

#if (ENABLE_PIP)
    if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
    {
        if(enMHEG5State != STATE_MHEG5_INIT)
        {
            MApp_MHEG5_Force_Exit();
        }
        return;
    }
#endif
    if(enMHEG5State == STATE_MHEG5_WAIT)
    {
        MApp_MHEG5_SignalMonitor();
        if(( g_u16MHEG5_AudioPID & ~0xE000 ) != ( g_u16Current_AudioPID& ~0xE000 ) )
        {
            msAPI_MHEG5_SendCurrentAudioPidType( g_u16Current_AudioPID);
        }
    }

    if(MApp_MHEG5_CheckGoMHEG5Process()==FALSE) // do not go mheg
    {
        return;
    }


    if(enMHEG5State == STATE_MHEG5_INIT)
    {
    #ifdef ROM_FILE
        if(0)
    #else
        if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) == FALSE || // not dtv
            (enFrotEndLockStatus != FRONTEND_LOCK            // no signal
        #if CIPLUS_MHEG
            // Neotion CI Plus Starting Kit: still need to run MHEG CIMMI when no signal
            && msAPI_IsCIMHEGRun()==E_MHEG_CI_OFF
        #endif
            )
        )
    #endif
        {
            MApp_MHEG5_SetGoMHEG5Process(FALSE);
            //printf("return:%bx,%bx,%bx\n",OSD_COUNTRY_SETTING,enFrotEndLockStatus,IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)));
            return;
        }
    }
    else
    {
        if(!MApp_MHEG5_Quit_Detection())
        {
            //EXIT;
            //printf("MApp_MHEG5_Quit_Detection\n");
            return;
        }
    }

    // still process mailbox from Aeon in MENU STATE or EPG STATE
    #ifdef ROM_FILE
    if(0)
    #elif 1
    if( MApp_ZUI_GetState() != E_ZUI_STATE_UNKNOW && MApp_ZUI_GetState() != E_ZUI_STATE_STANDBY
        #if (ENABLE_PVR == 1)
            && !MApp_ZUI_ACT_RecordPageActive()
        #endif
        && MApp_ZUI_GetActiveOSD() != E_OSD_AUDIO_VOLUME && MApp_ZUI_GetActiveOSD() != E_OSD_HOTKEY_OPTION
        && MApp_ZUI_GetActiveOSD() != E_OSD_SCREEN_SAVER ) //&& MApp_ZUI_GetActiveOSD() != E_OSD_TENKEY_NUMBER)
    #endif
    {
        // do process mailbox only ???
        // return to avoid to go mheg5 key process....
        if(u8KeyCode == KEY_TTX)
            u8KeyCode = KEY_NULL;
        if(enMHEG5State == STATE_MHEG5_WAIT )
        {
            msAPI_SetMHEG5_State(MApp_MHEG5_ProcessMailBox());
        }
        if(enMHEG5State == STATE_MHEG5_WAIT )
        {
            //Allow UI key process temp
            msAPI_MHEG5_SetGoBackMHEG5(true);
            return;
        }
    }

    #ifdef ROM_FILE
    while(1)
    #endif
    {

        #if CheckM5Sate
        MApp_Check_MHEG5_State();
        #endif

        if(msAPI_MHEG5_IsRunning()==FALSE)
        {
            MApp_MHEG5_PreProcess();
        }

        switch ( enMHEG5State )
        {
            case STATE_MHEG5_INIT:
                g_u8PrePlayMode=msAPI_VID_GetPlayMode();
                g_bPre_IsImageFrozen = g_bIsImageFrozen;
                if ( IsDTVInUse() )
                {
                    if ( MApp_MHEG5_Init() )
                    {
                        // Switch to MHEG5 GOP0
                        MApp_MHEG5_GOP_GWIN_SwitchGOP(MHEG5_GOP);
                        enMHEG5State = STATE_MHEG5_WAIT;
                        //fEnableTableMonitor = FALSE;
                        msAPI_MHEG5_SetRun(TRUE);
                        MApi_GOP_GWIN_EnableTransClr((EN_GOP_TRANSCLR_FMT)0, FALSE);
                        // Switch back to OSD GOP1
                        MApp_MHEG5_GOP_GWIN_SwitchGOP(E_GOP_OSD);
                        if((OSD_COUNTRY_SETTING == OSD_COUNTRY_IRELAND)&&(g_bCloseSubtitleAndOpenMheg5 == TRUE))
                        {
                            _u32StartMheg5Time = msAPI_Timer_GetTime0();
                        }
                    }
                    else
                    {
                        enMHEG5State = STATE_MHEG5_NONE;
                    }
                }
                else
                {
                    enMHEG5State = STATE_MHEG5_NONE;
                }

                break;

            case STATE_MHEG5_NONE:
                enMHEG5State = STATE_MHEG5_EXIT;
                break;

            case STATE_MHEG5_WAIT:
                MApp_MHEG_MultiTasks();
                msAPI_MHEG_AUD_PlayMHEG5AudioFile();
                MApp_MHEG5_SendVID_ChangeStream();
            #if MHEG5_NDT
                msAPI_MHEG5_TriggerNDT();
            #endif
        #if ENABLE_CI
                if ( msAPI_CI_Polling() )
                {
            #if MHEG5_WITH_OSD    //only if chip>=S4 in kingwok. MHEG5 always does not coexist with OSD in Kingwok if chip<=S3P
                    // mheg with CI OSD
                #if CIPLUS_MHEG
                    if (msAPI_IsCIMHEGRun()!= E_MHEG_CI_RUNNING && STATE_MHEG5_WAIT == enMHEG5State)
                #endif
                    {
                        // common mheg with ci osd
                        enMHEG5State = STATE_MHEG5_WITH_OSD;
                    }
            #else   //  MHEG5_WITH_OSD
                    msAPI_MHEG5_Key_Transmit( KEY_MENU, 0 );

                    enMHEG5State = STATE_MHEG5_MENU_EXIT;
                    msAPI_MHEG5_SetGoBackMHEG5(true);
            #endif  //  MHEG5_WITH_OSD
                }
                else
                {
                    if (msAPI_CI_CardDetect())
                    {
                        msAPI_CI_MAINLOOP();
                    }

                        if((OSD_COUNTRY_SETTING == OSD_COUNTRY_IRELAND)
                            &&(g_bCloseSubtitleAndOpenMheg5 == TRUE)
                            &&(msAPI_Timer_DiffTimeFromNow(_u32StartMheg5Time)>1000))
                        {
                                u8KeyCode = KEY_TTX;
                                g_bCloseSubtitleAndOpenMheg5 = FALSE;
                                _bMheg5Runing = TRUE;
                        }

                    _MApp_MHEG5_Idle_ProcessUserInput();
                }
        #else   // CI
                _MApp_MHEG5_Idle_ProcessUserInput();
        #endif  //  CI
                msAPI_SetMHEG5_State(MApp_MHEG5_ProcessMailBox());
                if(enMHEG5State == STATE_MHEG5_EXIT || enMHEG5State == STATE_MHEG5_TO_MENU
                || enMHEG5State == STATE_MHEG5_CHANNEL_CHANGE)
                {
                    MApp_Dmx_SetMonitorStatus(FALSE, EN_MONITOR_TABLE_ALL);
                }

                //==> Monitor if need set graph size or not. kris 051409
                MApp_MHEG5_SetGraphInfoMonitor();


                break;

            case STATE_MHEG5_CHANNEL_CHANGE:
                msAPI_SetMHEG5_State( MApp_MHEG5_ProcessMailBox() );
                break;

            case STATE_MHEG5_TO_MENU:
                msAPI_SetMHEG5_State( MApp_MHEG5_ProcessMailBox() );
                break;

            default:    // make GCC happy
                break;
        }

        #if CheckM5Sate
        MApp_Check_MHEG5_State();
        #endif

        switch(enMHEG5State)
        {

            #if MHEG5_WITH_OSD
            case STATE_MHEG5_WITH_OSD:
                msAPI_MHEG5_SetGoBackMHEG5(true);
                /*/ZUI_TODO:
                #if ENABLE_PVR
                if(!(KEY_INDEX == u8KeyCode || KEY_PLAY == u8KeyCode || KEY_PAUSE == u8KeyCode
                    || KEY_RECORD == u8KeyCode ||KEY_STOP == u8KeyCode || KEY_FF == u8KeyCode
                    || KEY_REWIND == u8KeyCode || KEY_NEXT == u8KeyCode || KEY_PREVIOUS == u8KeyCode
                    || KEY_UPDATE == u8KeyCode))
                #endif
                {
                    MApp_UiMenu2_DeleteOSDGWin( GWIN_DYNAMICMSG );
                    //MApp_UiMenu2_DeleteOSDGWin( GWIN_MUTE );
                    MApp_UiMenu2_SwitchToGwin( GWIN_MAIN_MENU );
                }
                */
                #if GFX_PRE_SCALER
                MApi_GOP_GWIN_SwitchGOP(MHEG5_GOP);
                //MApp_UiMenu2_InitGWin();
                MApi_GOP_GWIN_SetFMT0TransClr(COLOR_UI_TRANSPARENT);
                #else
                //MApp_UiMenu2_InitGWin();
                MApi_GOP_GWIN_SetFMT0TransClr(COLOR_UI_TRANSPARENT);
                #endif
                enMHEG5State = STATE_MHEG5_WAIT;
                msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_MHEG5, DISABLE, 0, MAIN_WINDOW);
                MApp_Dmx_SetMonitorStatus(TRUE, EN_MONITOR_TABLE_ALL);
                return;
                break;
            #endif

            case STATE_MHEG5_EXIT:
            case STATE_MHEG5_MENU_EXIT:
                if (enMHEG5State == STATE_MHEG5_EXIT)
                {
                    MApp_MHEG5_Restore_FullScreen();
                    if ( u8KeyCode != KEY_CHANNEL_PLUS && u8KeyCode != KEY_CHANNEL_MINUS )//let HK set enCheckMHEGLoadingStatus
                    {
                        msAPI_MHEG5_StopDsmcc(FALSE);//20071101 aeon side do it when change channel
                        enCheckMHEGLoadingStatus = EN_MHEG5_MONITOR;
                        if( u8KeyCode == KEY_POWER )
                        {
                        #if CIPLUS_MHEG_1_3
                            msAPI_MHEG5_Key_Transmit( KEY_MENU, 0 );
                        #else
                            msAPI_MHEG5_Key_Transmit( KEY_INFO, 0 );
                        #endif
                            MApi_GOP_GWIN_Enable(MHEG5_GWINID, FALSE);
                            for(i=0;i<MHEG_WAIT_AEON_TIMEOUT;i++)
                            {
                                msAPI_Timer_Delayms(1);
                                if(MApp_MHEG5_ProcessMailBox() == MB_RETURN_MHEG5_EXIT)
                                {
                        	        u8KeyCode = KEY_POWER;
                                    break;
                                }

                                if( i == ( MHEG_WAIT_AEON_TIMEOUT-1)) // Beon no response
                                {
                                    msAPI_COPRO_Disable();
                                }
                            }
                        }
                    }
                    msAPI_MHEG5_SetGoBackMHEG5(false);
                    MApp_MHEG5_Enable_LiveMHEG5(TRUE);
                }
                else if(enMHEG5State == STATE_MHEG5_MENU_EXIT)
                {
                    MApp_MHEG5_Restore_FullScreen();
                    MApp_MHEG5_RestoreOriginalAV();
                }

            #if CIPLUS_MHEG
                // reset CIMHEG variable
                if (msAPI_IsCIMHEGRun() != E_MHEG_CI_OFF)
                {
                #if ENABLE_CI_PLUS
                    const U8 u8AbortReqCode[1] = {EN_APPMMI_ABORT_CODES_SYSTEM_CANCEL};
                    msAPI_CI_AppMmi_AbortReq(u8AbortReqCode, 1);
                #endif
                }
                else
                {
                #if CIPLUS_MHEG_1_3
                    msAPI_MHEG5_SetCIPLUSSSM(2);    //  default value = 2
                    msAPI_MHEG5_SetCIPLUSSMG(FALSE);
                #endif
                }
            #endif

				if(MApp_MHEG5_CheckMHEG5Status() == SI_MHEG5_DATA_ONLY)
                {
                    MApp_ChannelChange_GoBackDataMode();
                }

                if(u8PreKeyCode != KEY_NULL)
                {
                    u8KeyCode = u8PreKeyCode;
                    u8PreKeyCode = KEY_NULL;
                }



                // Switch to MHEG5 GOP0
                MApp_MHEG5_GOP_GWIN_SwitchGOP(MHEG5_GOP);

                MApp_MHEG5_Display_Finalize();

                // keep OSD layer always on top
                //MApi_GOP_GWIN_OutputLayerSwitch(MHEG5_GOP);

                // Switch back to OSD GOP1
                MApp_MHEG5_GOP_GWIN_SwitchGOP(E_GOP_OSD);

                /*/ZUI_TODO:
                MApp_UiMenu2_DeleteOSDGWin(GWIN_DYNAMICMSG);

                if (MHEG5_HOTKEY_MODE == MIA_MUTE )
                {
                MHEG5_HOTKEY_MODE = MIA_NOTHING;
                }

                MApp_UiMenu2_SwitchToGwin(GWIN_MAIN_MENU);
                */

		   #if((FIXED_MIRROR_HD_PANEL_UI_LOSE == ENABLE) && (MirrorEnable == ENABLE))
			if((g_IPanel.Width()<=1366&&g_IPanel.Height()<=768)&&MApp_Image_GetMirror())
			{
				MApi_GOP_GWIN_Set_HStretchMode(E_GOP_HSTRCH_DUPLICATE);
				MApi_GOP_GWIN_Set_VStretchMode(E_GOP_VSTRCH_DUPLICATE);
			}
		   #endif

                #if GFX_PRE_SCALER
                MApi_GOP_GWIN_SwitchGOP(MHEG5_GOP);
                //MApp_UiMenu2_InitGWin();
                MApi_GOP_GWIN_SetFMT0TransClr(COLOR_UI_TRANSPARENT);
                #else
                //MApp_UiMenu2_InitGWin();
                MApi_GOP_GWIN_SetFMT0TransClr(COLOR_UI_TRANSPARENT);
                #endif

                enMHEG5State = STATE_MHEG5_INIT;
                MApp_MHEG5_SetGoMHEG5Process(FALSE);
                if ( MApi_XC_IsBlackVideoEnable(MAIN_WINDOW) )
                {
                    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, 100, MAIN_WINDOW);
                }
                msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_MHEG5, DISABLE, 0, MAIN_WINDOW);

                MApp_Dmx_SetMonitorStatus(TRUE, EN_MONITOR_TABLE_ALL);
                msAPI_MHEG5_SetRun(FALSE);

                if(bExitMheg5AsScartInserted == TRUE)//20071009 for display no signal in MHEG5 mode
                {
                    u8KeyCode = KEY_NULL;
                    bExitMheg5AsScartInserted = FALSE;
                }

                MApp_MHEG5_ResumeAV();

                break;

            default:
                break;

        }
    }
}

#if CIPLUS_MHEG_1_3
U8 u8InputMask[3] = {0, 0, 0};

static bool MApp_MHEG5_TestInputMask(U8 mykey, U8 u8Reg)
{
    bool ret = false;

    if (u8Reg != 255)
    {
        return ret;
    }

    switch (mykey)
    {
        case KEY_UP:
            if (u8InputMask[0] & 0x01)
            {
                ret = true;
            }
            break;
        case KEY_DOWN:
            if (u8InputMask[0] & 0x02)
            {
                ret = true;
            }
            break;
        case KEY_LEFT:
            if (u8InputMask[0] & 0x04)
            {
                ret = true;
            }
            break;
        case KEY_RIGHT:
            if (u8InputMask[0] & 0x08)
            {
                ret = true;
            }
            break;
        case KEY_0:
        case KEY_1:
        case KEY_2:
        case KEY_3:
        case KEY_4:
        case KEY_5:
        case KEY_6:
        case KEY_7:
        case KEY_8:
        case KEY_9:
            if (u8InputMask[0] & 0x10)
            {
                ret = true;
            }
            break;
        case KEY_SELECT:
            if (u8InputMask[0] & 0x20)
            {
                ret = true;
            }
            break;
        case KEY_EXIT:
            if (u8InputMask[0] & 0x40)
            {
                ret = true;
            }
            break;
        case KEY_RED:
            if (u8InputMask[1] & 0x01)
            {
                ret = true;
            }
            break;
        case KEY_GREEN:
            if (u8InputMask[1] & 0x02)
            {
                ret = true;
            }
            break;
        case KEY_YELLOW:
            if (u8InputMask[1] & 0x04)
            {
                ret = true;
            }
            break;
        case KEY_BLUE:
            if (u8InputMask[1] & 0x08)
            {
                ret = true;
            }
            break;
        case KEY_TTX:
            if (u8InputMask[1] & 0x10)
            {
                ret = true;
            }
            break;
        case KEY_INFO:
            if (u8InputMask[1] & 0x20)
            {
                ret = true;
            }
            break;
        case KEY_STOP:
            if (u8InputMask[1] & 0x40)
            {
                ret = true;
            }
            break;
        case KEY_PLAY:
            if (u8InputMask[1] & 0x80)
            {
                ret = true;
            }
            break;
        case KEY_PAUSE:
            if (u8InputMask[2] & 0x01)
            {
                ret = true;
            }
            break;
        case KEY_NEXT:
            if (u8InputMask[2] & 0x02)
            {
                ret = true;
            }
            break;
        case KEY_PREVIOUS:
            if (u8InputMask[2] & 0x04)
            {
                ret = true;
            }
            break;
        case KEY_FF:
            if (u8InputMask[2] & 0x08)
            {
                ret = true;
            }
            break;
        case KEY_REWIND:
            if (u8InputMask[2] & 0x10)
            {
                ret = true;
            }
            break;
        // trunk have no PLAY or PAUSE mixed key. mheg5 engin already modified!
	/*
		case KEY_PLAY_PAUSE:
			if (u8InputMask[2] & 0x40)
			{
				ret = true;
			}
			break;
	*/
        case KEY_EPG:
            if (u8InputMask[2] & 0x20)
            {
                ret = true;
            }
            break;
        default:
            ret = false;
    }

    return ret;

}
#endif


/******************************************************************************/
/// MHEG5 key processing function
/******************************************************************************/
static void _MApp_MHEG5_Idle_ProcessUserInput(void)
{
#ifdef ROM_FILE
    MApp_MHEG5_Idle_ProcessUserInput();
    return;
#endif
    U8 u8MHEG5_Key_Register = msAPI_MHEG5_GetKeyRegisterGroup();

    // TODO: THESE TODOs IS FOR WARNING ONLY
    // TODO:  PLEASE DO NOT POLLUTE MHEG CODE
    // TODO: SCREEN SAVER CODE SHOULD NOT BE ADDED HERE. THINK MORE BEFORE YOU ADD CODE

    if ( u8KeyCode != KEY_NULL )
    {
        switch ( u8KeyCode )
        {

            case KEY_CHANNEL_PLUS:
            case KEY_CHANNEL_MINUS:
                //msAPI_MHEG5_Key_Transmit( u8KeyCode, 0 );
                if((OSD_COUNTRY_SETTING == OSD_COUNTRY_IRELAND)
                        &&(_bMheg5Runing == TRUE)
                        )
                {
                    _bMheg5Runing = FALSE;
#if ENABLE_SUBTITLE
                    MApp_ZUI_ACT_Subtitle_Toggle(TRUE);
                    MApp_ZUI_ACT_ExecuteSubtitleLanguageAction(EN_EXE_CLOSE_CURRENT_OSD);
#endif
                }

                // For Ziggo CI+ : HCv2 tune_request
                #if ENABLE_CI_PLUS
                if (FALSE == IsCiVodMode())
                {
                    MApi_MHEG5_Disable(EN_MHEG5_DM_DISABLE_AND_STOPDSMCC);
                }
                #endif
            break;

            case KEY_POWER:
                enMHEG5State = STATE_MHEG5_EXIT;
                break;

    #if 1//(ENABLE_PVR)
            case KEY_STOP:
            case KEY_RECORD:
            case KEY_FF:
            case KEY_REWIND:
            case KEY_NEXT:
            case KEY_PREVIOUS:
            case KEY_PLAY:
            case KEY_PAUSE:
            case KEY_INDEX:
            case KEY_UPDATE:
            #if CIPLUS_MHEG_1_3
                if (MApp_MHEG5_TestInputMask(u8KeyCode, u8MHEG5_Key_Register))
                {
                    msAPI_MHEG5_Key_Transmit(u8KeyCode, 0);
                    u8KeyCode = KEY_NULL;
                }
            #endif

            #if INTERACTION_CHANNEL_STREAM
                if (u8MHEG5_Key_Register == 6) //for ICStreaming
                {
                        msAPI_MHEG5_Key_Transmit( u8KeyCode, 0);
                        u8KeyCode = KEY_NULL;
                        break;
                }
            #endif
#if MHEG5_WITH_OSD
                                enMHEG5State = STATE_MHEG5_WITH_OSD;
                                msAPI_MHEG5_SetGoBackMHEG5(true);
#else
                                enMHEG5State = STATE_MHEG5_MENU_EXIT;
#endif
                break; // Fix coverity
    #endif

            case KEY_MUTE:
            case KEY_MENU:
            case KEY_INFO:
            case KEY_EPG:
            case KEY_CHANNEL_LIST:
            case KEY_CHANNEL_FAV_LIST:
            case KEY_INPUT_SOURCE:
            case KEY_TV_RADIO:
            case KEY_CHANNEL_RETURN:
            case KEY_MTS:
            case KEY_EPGTIMER_COUNTDOWN:
            case KEY_VOLUME_PLUS:
            case KEY_VOLUME_MINUS:
            case KEY_SUBTITLE:
            case KEY_ZOOM:
            case KEY_SLEEP:
            case KEY_AUDIO:
            case KEY_PICTURE:
            case KEY_FREEZE:
            case KEY_REVEAL:
           //case KEY_PLAY_PAUSE:
        #if ENABLE_TTX
                if(OSD_COUNTRY_SETTING == OSD_COUNTRY_NEWZEALAND)
                {
                    if ( u8KeyCode == KEY_SUBTITLE&& MApp_TTX_GetDefaultTTX_PID() != MSAPI_DMX_INVALID_PID
                         &&msAPI_TTX_CheckTTXSignal()
    				 #if PVR_AND_TTX_DIFF_WITH_MHEG5
                         &&MApp_TTX_CanBeTurnedOn()
                     #endif
                     #if (ENABLE_PIP)
                         && (MApp_Get_PIPMode() == EN_PIP_MODE_OFF)
                     #endif
                       )
                    {
                        enMHEG5State = STATE_MHEG5_EXIT;
                        break;
                    }
                }
        #endif

            #if CIPLUS_MHEG_1_3
                if (MApp_MHEG5_TestInputMask(u8KeyCode, u8MHEG5_Key_Register))
                {
                    msAPI_MHEG5_Key_Transmit(u8KeyCode, 0);
                    u8KeyCode = KEY_NULL;
                }
                else
            #endif
                {
                #if MHEG5_WITH_OSD
                    if (u8KeyCode == KEY_EPG && (u8MHEG5_Key_Register == 13 || u8MHEG5_Key_Register == 14 || u8MHEG5_Key_Register == 15)) // i.e. EPG key for NZ, HK
                    {
                        msAPI_MHEG5_Key_Transmit( u8KeyCode, 0);
                        u8KeyCode = KEY_NULL;
                    }
                    else
                    {
                        enMHEG5State = STATE_MHEG5_WITH_OSD;
                        msAPI_MHEG5_SetGoBackMHEG5(true);
                        //ZUI: MHEG5_HOTKEY_MODE = MIA_NOTHING;
                    }
                #endif
                }

                break; // Fix coverity


        #if (ENABLE_PIP)
            case KEY_PIP:
                if(IsPIPSupported())
                {
                #if MHEG5_WITH_OSD
                    enMHEG5State = STATE_MHEG5_WITH_OSD;
                    msAPI_MHEG5_SetGoBackMHEG5(true);
                #else
                    enMHEG5State = STATE_MHEG5_MENU_EXIT;
                #endif
                    MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_INC_PIPMODE);
                }
                break;
        #endif

            case KEY_DTV:
            case KEY_TV:
            case KEY_PC:
            case KEY_COMPONENT:
            case KEY_HDMI:
            case KEY_SCART:
            case KEY_AV:
            case KEY_SV:
                u8PreKeyCode = u8KeyCode;
            #if CIPLUS_MHEG_1_3
                msAPI_MHEG5_Key_Transmit( KEY_MENU, 0 );
            #else
                msAPI_MHEG5_Key_Transmit( KEY_INFO, 0 );
            #endif
                break;

            case KEY_0:
            case KEY_1:
            case KEY_2:
            case KEY_3:
            case KEY_4:
            case KEY_5:
            case KEY_6:
            case KEY_7:
            case KEY_8:
            case KEY_9:
            #if CIPLUS_MHEG_1_3
                if (MApp_MHEG5_TestInputMask(u8KeyCode, u8MHEG5_Key_Register))
                {
                    msAPI_MHEG5_Key_Transmit(u8KeyCode, 0);
                    u8KeyCode = KEY_NULL;
                }
                else
            #endif
#if INTERACTION_CHANNEL_STREAM
                if (u8MHEG5_Key_Register == 4 || u8MHEG5_Key_Register ==14 || u8MHEG5_Key_Register == 6)
#else
                if (u8MHEG5_Key_Register == 4 || u8MHEG5_Key_Register ==14)
#endif
                {
                    msAPI_MHEG5_Key_Transmit(u8KeyCode, 0);
                    u8KeyCode = KEY_NULL;
                }
                else
                {
                #if MHEG5_WITH_OSD
                    enMHEG5State = STATE_MHEG5_WITH_OSD;
                    msAPI_MHEG5_SetGoBackMHEG5(true);
                #else
                    enMHEG5State = STATE_MHEG5_MENU_EXIT;
                #endif
                }
                break;

            // the keys below are for MHEG

            case KEY_UP:
            case KEY_DOWN:
            case KEY_RIGHT:
            case KEY_LEFT:
            case KEY_SELECT:
            #if CIPLUS_MHEG_1_3
                if (MApp_MHEG5_TestInputMask(u8KeyCode, u8MHEG5_Key_Register))
                {
                    msAPI_MHEG5_Key_Transmit(u8KeyCode, 0);
                    u8KeyCode = KEY_NULL;
                }
                else
            #endif
#if INTERACTION_CHANNEL_STREAM
                if (u8MHEG5_Key_Register == 4 || u8MHEG5_Key_Register == 5 ||
                    u8MHEG5_Key_Register == 14 || u8MHEG5_Key_Register == 15 ||
                    u8MHEG5_Key_Register == 6)
#else
                if (u8MHEG5_Key_Register == 4 || u8MHEG5_Key_Register == 5 ||
                    u8MHEG5_Key_Register == 14 || u8MHEG5_Key_Register == 15)
#endif
                {
                    msAPI_MHEG5_Key_Transmit(u8KeyCode, 0);
                    u8KeyCode = KEY_NULL;
                }
                else
                {
                    #if MHEG5_WITH_OSD
                    enMHEG5State = STATE_MHEG5_WITH_OSD;
                    msAPI_MHEG5_SetGoBackMHEG5(true);
                    #else
                    enMHEG5State = STATE_MHEG5_MENU_EXIT;
                    #endif
                }
                break;

            case KEY_RED:
            case KEY_GREEN:
            case KEY_YELLOW:
            case KEY_BLUE:
            case KEY_TTX:
            case KEY_EXIT:
	#if ENABLE_TTX
			if(OSD_COUNTRY_SETTING == OSD_COUNTRY_NEWZEALAND)
			{
				if ( u8KeyCode == KEY_TTX && MApp_TTX_GetDefaultTTX_PID() != MSAPI_DMX_INVALID_PID
					 &&msAPI_TTX_CheckTTXSignal()
				#if PVR_AND_TTX_DIFF_WITH_MHEG5
					 &&MApp_TTX_CanBeTurnedOn()
				#endif
        		#if (ENABLE_PIP)
					 && (MApp_Get_PIPMode() == EN_PIP_MODE_OFF)
        		#endif
				   )
				{
					enMHEG5State = STATE_MHEG5_EXIT;
					break;
				}
			}
	#endif

                    if((OSD_COUNTRY_SETTING == OSD_COUNTRY_IRELAND)
                            &&(u8KeyCode == KEY_TTX)
                            &&(_bMheg5Runing == TRUE)
                            )
                    {
                        _bMheg5Runing = FALSE;
#if ENABLE_SUBTITLE
                        MApp_ZUI_ACT_Subtitle_Toggle(TRUE);
                        MApp_ZUI_ACT_ExecuteSubtitleLanguageAction(EN_EXE_CLOSE_CURRENT_OSD);
#endif
                        MApi_MHEG5_Disable(EN_MHEG5_DM_DISABLE_AND_STOPDSMCC);
                    }

		  {
                #if CIPLUS_MHEG_1_3
                    if (MApp_MHEG5_TestInputMask(u8KeyCode, u8MHEG5_Key_Register))
                    {
                        msAPI_MHEG5_Key_Transmit(u8KeyCode, 0);
                        u8KeyCode = KEY_NULL;
                    }
                    else
                #endif

    #if INTERACTION_CHANNEL_STREAM
                    if (u8MHEG5_Key_Register == 3 || u8MHEG5_Key_Register == 4 || u8MHEG5_Key_Register == 5 ||
                        u8MHEG5_Key_Register == 13 || u8MHEG5_Key_Register == 14 || u8MHEG5_Key_Register == 15 ||
                        u8MHEG5_Key_Register == 6)

    #else
                    if (u8MHEG5_Key_Register == 3 || u8MHEG5_Key_Register == 4 || u8MHEG5_Key_Register == 5 ||
                        u8MHEG5_Key_Register == 13 || u8MHEG5_Key_Register == 14 || u8MHEG5_Key_Register == 15)
    #endif
                    {
                        msAPI_MHEG5_Key_Transmit(u8KeyCode, 0);
                        u8KeyCode = KEY_NULL;
                    }
                    else
                    {
                    #if MHEG5_WITH_OSD
                        enMHEG5State = STATE_MHEG5_WITH_OSD;
                        msAPI_MHEG5_SetGoBackMHEG5(true);
                    #else
                        enMHEG5State = STATE_MHEG5_MENU_EXIT;
                    #endif
                    }
		  }
                break;

            default:
                msAPI_MHEG5_Key_Transmit( u8KeyCode, 0 );
                u8KeyCode = KEY_NULL;   // only reset those keys defined in mheg spec.
                break;
        }
    }

}

// only do this when STATE_MHEG_WAIT
/******************************************************************************/
/// MHEG5 sends vid change stream
/******************************************************************************/
static void MApp_MHEG5_SendVID_ChangeStream()
{
    // fTVSetModeDone is set in Mapp_Multitask.
    // we don't do set_mvd_mode in our MHEG multitask, we use the global mapp_multitask
    // so, we just have to reference this "fTVSetModeDone" value to know whether mvd set mode is done or not

	if(fTVSetModeDone == TRUE )
        g_MHEG5Video.bRecodeMVDDONE = fTVSetModeDone;

    if (g_MHEG5Video.bVideoActionNotRdy == FALSE/*wait get full mailbox of video*/
        && g_MHEG5Video.bRecodeMVDDONE == TRUE )//for GE DMA share, only do in STATE_MHEG5_WAIT state
    {
        g_MHEG5Video.u8VideoFlag &= ~(EVER_SET_VIDEO_STREAM|EVER_SET_VIDEO_BOX_SIZE);

        msAPI_MHEG5_VID_Send_CHANGESTREAM();
		g_MHEG5Video.bRecodeMVDDONE = FALSE;
    }
}

/******************************************************************************/
/// MHEG5 makes quarter screen video to full screen
/******************************************************************************/
void MApp_MHEG5_Restore_FullScreen(void)
{
    if(!msAPI_MHEG5_VID_IsFullScreen(&g_MHEG5Video.stMHEG5VideoAction))
    {
        g_MHEG5Video.stMHEG5VideoAction.u16BoxSize_X = MHEG_XRES_COORD;
        g_MHEG5Video.stMHEG5VideoAction.u16BoxSize_Y = MHEG_YRES_COORD;
        g_MHEG5Video.stMHEG5VideoAction.u16Scale_Width = MHEG_XRES_COORD;
        g_MHEG5Video.stMHEG5VideoAction.u16Scale_Height = MHEG_YRES_COORD;
        g_MHEG5Video.stMHEG5VideoAction.s16Position_X = 0;
        g_MHEG5Video.stMHEG5VideoAction.s16Position_Y = 0;
        g_MHEG5Video.stMHEG5VideoAction.s16VideoOffset_X =0;
        g_MHEG5Video.stMHEG5VideoAction.s16VideoOffset_Y = 0;
        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, 100, MAIN_WINDOW);
        MApp_Scaler_SetWindow(NULL, NULL, NULL,
                                           stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
    }
}


#define DELAY_FOR_MB_SEND

/******************************************************************************/
/// MHEG5 init
/******************************************************************************/
BOOLEAN MApp_MHEG5_Init(void)
{
    U32 u32alignWidth;
    U32 u32Height;
    U32 u32Width;
    U16 u16Pid_codec=0;
    //U8  savePageIndex;

#if 0//CIPLUS_MHEG_1_3
	//	in MApp_MHEG5_Init, if subtitle is enabled and the gwin id of subtitle is valid, disable the gwin of subtitle
	if((stGenSetting.g_SysSetting.fEnableSubTitle == TRUE)&& (u8SubtitleMenuNum != 0))
	{
        MApp_Subtitle_Force_Exit();
	}
#endif

#if (MHEG5_GOP_MIU == 0)
    MApi_GOP_MIUSel(MHEG5_GOP, E_GOP_SEL_MIU0);
#else
    MApi_GOP_MIUSel(MHEG5_GOP, E_GOP_SEL_MIU1);
#endif

#if GFX_PRE_SCALER
    XC_ApiStatus stXCStatus;

    if(MApi_XC_GetStatus(&stXCStatus, MAIN_WINDOW) == FALSE)
    {
        printf("MApi_XC_GetStatus failed because of InitData wrong, please update header file and compile again\n");
    }
#endif

    msAPI_MHEG5_SetKeyRegisterGroup(3);
    // Transmit system time
    msAPI_MHEG5_SystemTime_Transmit(msAPI_Timer_GetSystemTime(), msAPI_Timer_GetOffsetTime());

#if MHEG5_NETWORK
    DELAY_FOR_MB_SEND;
    msAPI_MHEG5_InitNetwork();
#endif

    // this files is for S4, S4L...
    // we need to make GOP0 on top. i.e. if MHEG coexists with OSD, OSD (GOP0) will on the top layer.
    MApi_GOP_GWIN_OutputLayerSwitch(E_GOP_OSD);

#if GFX_PRE_SCALER
//    MApp_UiMenu2_DeleteALLOSDWindow();
    //ZUI_TODO: MApp_UiMenu2_DeleteALLOSDWinExcept(GWIN_MUTE);

    MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD); //sw to GOP1
#else
//    MApp_UiMenu2_DeleteALLOSDWindow();
    //ZUI_TODO: MApp_UiMenu2_DeleteALLOSDWinExcept(GWIN_MUTE);

    // Initial GOP setting
//    MDrv_Scaler_Set_GOPSel(MS_NIP_SEL_GOP0);
    MApi_GOP_GWIN_SetGOPDst(MHEG5_GOP, E_GOP_DST_OP0);     // Refine GOP dst configuration function.
//    MApi_GOP_SetGOPClk(MHEG5_GOP, E_GOP_DST_OP0);
#endif
    // Save original page index
    //ZUI_TODO: savePageIndex=g_u8MsgPageIndex;
    // We want to create Volume GWin
    //ZUI_TODO: g_u8MsgPageIndex = MENU_AUDIO_VOLUME_CONFIG;
    //ZUI_TODO: MApp_UiMenu2_CreateOSDGWin(GWIN_DYNAMICMSG);
    //ZUI_TODO: MApp_UiMenu2_CreateOSDGWin(GWIN_MUTE);
    // Restore UI page index
    //ZUI_TODO: g_u8MsgPageIndex = savePageIndex;

    bExitMheg5AsScartInserted = FALSE;

    g_MHEG5Video.bFullScreen        = TRUE;
    g_MHEG5Video.bPrevFullScreen    = TRUE;
    g_MHEG5Video.bIFrame            = FALSE;
    g_MHEG5Video.bVideoActionNotRdy = FALSE;
    g_MHEG5Video.bRecodeMVDDONE     = FALSE;

    g_MHEG5Video.eSceneAspectRatio  = SCENE_AR_None;
    g_MHEG5Video.Pre_eSceneAspectRatio = SCENE_AR_None;
    g_MHEG5Video.u8VideoFlag2       = SCENE_Normal;
    g_MHEG5Video.u8PrevVideoFlag    = 0;

    g_MHEG5Video.eWAM = EN_MHEG5_WAM_None;
    g_MHEG5Video.Pre_eWAM = EN_MHEG5_WAM_None;

    g_MHEG5Video.eSceneAspectRatio_FromTransitionTo = SCENE_AR_None;

    g_MHEG5Video.stMHEG5VideoAction.u16BoxSize_X         = MHEG_XRES_COORD;
    g_MHEG5Video.stMHEG5VideoAction.u16BoxSize_Y         = MHEG_YRES_COORD;
    g_MHEG5Video.stMHEG5VideoAction.u16Scale_Width       = MHEG_XRES_COORD;
    g_MHEG5Video.stMHEG5VideoAction.u16Scale_Height      = MHEG_YRES_COORD;
    g_MHEG5Video.stMHEG5VideoAction.s16Position_X        = 0;
    g_MHEG5Video.stMHEG5VideoAction.s16Position_Y        = 0;
    g_MHEG5Video.stMHEG5VideoAction.s16VideoOffset_X     = 0;
    g_MHEG5Video.stMHEG5VideoAction.s16VideoOffset_Y     = 0;

    g_MHEG5Video.stPrevMHEG5VideoAction.u16BoxSize_X     = 0xFFFF;
    g_MHEG5Video.stPrevMHEG5VideoAction.u16BoxSize_Y     = 0xFFFF;
    g_MHEG5Video.stPrevMHEG5VideoAction.u16Scale_Width   = 0xFFFF;
    g_MHEG5Video.stPrevMHEG5VideoAction.u16Scale_Height  = 0xFFFF;
    g_MHEG5Video.stPrevMHEG5VideoAction.s16Position_X    = 0xFFFF;
    g_MHEG5Video.stPrevMHEG5VideoAction.s16Position_Y    = 0xFFFF;
    g_MHEG5Video.stPrevMHEG5VideoAction.s16VideoOffset_X = 0xFFFF;
    g_MHEG5Video.stPrevMHEG5VideoAction.s16VideoOffset_Y = 0xFFFF;

    //Init Drawing Flag
    M5API_GFX_SetMHEGDrawFlag(FALSE);
    /*/ZUI_TODO:
    MHEG5_HOTKEY_MODE = MIA_NOTHING;
    }*/
    DELAY_FOR_MB_SEND;

    msAPI_MHEG5_Key_Transmit(KEY_TTX, 0);

    DELAY_FOR_MB_SEND;

    u32Height = MHEG_OS_FB_HEIGHT;
    u32Width = MHEG_OS_FB_WIDTH;

    if ( MHEG5_RenderTarget_Fmt == E_GOP_COLOR_ARGB8888 )
    {
        u32alignWidth = ((u32Width * 4 + 0x0F) & ~(0x0F))/4;
    }
    else //if ( MHEG5_RenderTarget_Fmt == E_GOP_COLOR_ARGB4444 )
    {
         u32alignWidth = ((u32Width * 2 + 0x0F) & ~(0x0F))/2;
    }
    DELAY_FOR_MB_SEND;



    if(g_eCurrent_VideoType==E_VDEC_CODEC_TYPE_H264)
        u16Pid_codec = ((g_u16Current_VideoPID & ~0xE000)|0x8000);
    else
        u16Pid_codec = (g_u16Current_VideoPID & ~0xE000);


    msAPI_MHEG5_SendOSWidthHeight_AudioPid_PanelRatio(u32alignWidth, u32Height, g_u16Current_AudioPID & ~0xE000, u16Pid_codec);

    DELAY_FOR_MB_SEND;

    msAPI_MHEG5_SendPanelInfo();

    DELAY_FOR_MB_SEND;

    // mailbox to tell aeon that S4 use Ge semaphore
    msAPI_MHEG5_UseGeSemaphore();

    DELAY_FOR_MB_SEND;

    //Set AEON that MHEG5 only refresh when aspect ratio change
#if GOP_SCALERATIO_FIXED2
    msAPI_MHEG5_Send_ARC_Setting(TRUE,TRUE,TRUE,FALSE,TRUE);
#else
    msAPI_MHEG5_Send_ARC_Setting(TRUE,FALSE,TRUE,FALSE,TRUE);
#endif

    DELAY_FOR_MB_SEND;

    // Switch to MHEG5 GOP0
    MApp_MHEG5_GOP_GWIN_SwitchGOP(MHEG5_GOP);

    //To accelerate init time.
    MApi_GOP_GWIN_SetForceWrite(TRUE);

    MHEG5_RT_FBID = MApi_GOP_GWIN_GetFreeFBID();
#if MHEG5_STATIC_FB
    MApi_GOP_GWIN_CreateFBbyStaticAddr(MHEG5_RT_FBID, 0, 0, MHEG_XRES, MHEG_YRES, MHEG_GE_FMT, MHEG5_STATIC_RT_FB_ADDR);

    MHEG5_OS_FBID = MApi_GOP_GWIN_GetFreeFBID();
    MApi_GOP_GWIN_CreateFBbyStaticAddr(MHEG5_OS_FBID, 0, 0, u32alignWidth, u32Height, MHEG_GE_FMT, MHEG5_STATIC_OS_FB_ADDR);

    MHEG5_GWINID = MApi_GOP_GWIN_GetFreeWinID();
    if (MHEG5_GWINID==0xFF)
    {
        ASSERT(0);
    }
    else
    {
        MApi_GOP_GWIN_MapFB2Win(MHEG5_OS_FBID, MHEG5_GWINID);
    }
#else

    MApi_GOP_GWIN_CreateFB(MHEG5_RT_FBID, 0, 0, MHEG_XRES, MHEG_YRES + MMGAP, MHEG_GE_FMT);
    MApi_GOP_GWIN_SwitchGOP(MHEG5_GOP);
    MApi_GOP_GWIN_Set_STRETCHWIN(MHEG5_GOP,E_GOP_DST_OP0, MHEG_XRES_OS ,MHEG_YRES_OS, MHEG_XRES_OS, MHEG_YRES_OS);

    MHEG5_GWINID = MApi_GOP_GWIN_CreateWin(u32alignWidth, u32Height, MHEG_GE_FMT);
#endif
    //printf("MHEG5_GWINID=%bx\n",MHEG5_GWINID); //in normally situation, MHEG5_GWINID value should be 0.
#if GFX_PRE_SCALER
    MApi_GOP_GWIN_SetWinPosition(
    MHEG5_GWINID,
    stXC_WinTime_Info.stCapWin.x / 2,
    stXC_WinTime_Info.bInterlace ? 1 : 1); // y position of GOP is 1 base
#else
    MApi_GOP_GWIN_SetWinDispPosition(MHEG5_GWINID, (MApi_GOP_GWIN_Get_HSTART()), 0);
#endif

    MApi_GOP_GWIN_Switch2Gwin(MHEG5_GWINID);

    msAPI_OSD_SetClipWindow(0, 0, u32alignWidth, u32Height);

    MApi_GOP_GWIN_SetBlending(MHEG5_GWINID, TRUE, 0);

    // clear frame buffer
    {
        GOP_GwinFBAttr fbAttr;
        MApi_GOP_GWIN_GetFBInfo(MApi_GOP_GWIN_GetCurrentFBID(), &fbAttr);
        MDrv_GE_ClearFrameBuffer(fbAttr.addr, fbAttr.size, 0x0);
    }

    #if GOP_SCALERATIO_FIXED// need to move and should check AFD case
        MApi_GOP_GWIN_SetHDisplaySize(MHEG5_GWINID,(((PANEL_WIDTH+0x07)& ~0x07)/2),0);

        //MApi_GOP_GWIN_Set_HSCALE(TRUE, (((PANEL_WIDTH+0x07)& ~0x07)/2), (g_IPanel.Width()+7) & ~0x07);
        MApi_GOP_GWIN_Set_HSCALE(TRUE, (PANEL_WIDTH/2), g_IPanel.Width()+2);
        MApi_GOP_GWIN_Set_VSCALE(TRUE, (((PANEL_HEIGHT+0x07)& ~0x07)/2), (g_IPanel.Height()+7) & ~0x07);
    #elif GOP_SCALERATIO_FIXED2
        MApi_GOP_GWIN_SetHDisplaySize(MHEG5_GWINID,MHEG_XRES_OS,0);
    #endif

    #if(MHEG5_Y_STRETCH_WAY != MHEG5_USE_GOP_STRETCH)
        MApi_GOP_GWIN_Set_VSCALE(FALSE,0,0);
    #endif

    MApi_GOP_GWIN_SetForceWrite(FALSE);
    MApi_GOP_GWIN_Enable(MHEG5_GWINID, TRUE);

    //Init src and disp window


    stSystemInfo[MAIN_WINDOW].enAspectRatio = MApp_Scaler_GetAspectRatio(MAIN_WINDOW,ST_VIDEO.eAspectRatio);

    //printf("stSystemInfo.enAspectRatio:%bx\n",stSystemInfo.enAspectRatio);


    if ( msAPI_Picture_isAFDEnable(stSystemInfo[MAIN_WINDOW].enAspectRatio) &&
         msAPI_Picture_isCurrentAFDVaild(gstVidStatus.u8AFD))
    {
            MApp_MHEG5_SetGraphARCInfo(SENDARC_AFD_FOR_GE_MHEG5_INIT,stSystemInfo[MAIN_WINDOW].enAspectRatio);
            MApp_MHEG5_SetGraphARCInfo(SENDARC_AFD,stSystemInfo[MAIN_WINDOW].enAspectRatio);
    }
    else
    {
        MApp_MHEG5_SetGraphARCInfo(SENDARC_MHEG5_INIT,stSystemInfo[MAIN_WINDOW].enAspectRatio);
    }

    DELAY_FOR_MB_SEND;

    // allocate DLA FrameBuffer for MHEG Dynamic Line Art usage
    msAPI_MHEG5_AllocateDLAFB();

    DELAY_FOR_MB_SEND;

    #ifdef MHEG5_BIG5_FONT_ENABLE
    msAPI_MHEG5_SendM5FontInfo();
    DELAY_FOR_MB_SEND;
    #endif
    // pass framebuffer and os screen info to MHEG Engine
    MApp_MHEG5_Update_Frame_Buffer();

    DELAY_FOR_MB_SEND;

    // Switch back to OSD GOP1
    MApp_MHEG5_GOP_GWIN_SwitchGOP(E_GOP_OSD);
#if ENABLE_UPDATE_MHEG5_FRAME_BUFFER
    MApi_GOP_RegisterEventNotify(MApp_fpGOP_CB);
#endif
    //If MHEG5 draw anything on scree, it will call MApp_MHEG5_AudioScreenSaver
    //msAPI_MHEG5_SetDrawingCallback(MApp_MHEG5_AudioScreenSaver);
    return TRUE;
}
#if INTERACTION_CHANNEL
#define   winsock_version   0x0101
#define   MHEG5IC_HTTP_LENGTH 1500
#define   MHEG5IC_REC_LENGTH 1500000
int StrToInt(char * str)
{
    int value = 0;
    int sign = 1;
    if(*str == '-')
    {
            sign = -1;
            str++;
    }
    while(*str)
    {
            value = value * 10 + *str - '0';
            str++;
    }
    return sign*value;
}

U16 MApp_MHEG5_CheckServer_Status(void)
{
        int sd, port;
        U16 ReturnStatus = 0;
        char host_name[256];
        struct hostent *nlp_host;
        struct sockaddr_in pin;

        strcpy((char *)host_name,(const char *)"dtgtest.org");

        port=80;//33322;

        printf("host_name : %s\n",host_name);

        if((nlp_host=gethostbyname(host_name))==NULL)
        {
            printf("error : %d\n",h_errno);
            printf("Resolve Error!\n");
        }

        //set initial variable
        bzero(&pin,sizeof(pin));
        pin.sin_family=AF_INET;                 //AF_INETªí¥?¨?¥?IPv4
       // pin.sin_addr.s_addr=htonl(INADDR_ANY);
        //pin.sin_addr.s_addr=inet_addr("119.160.246.23");//inet_addr(inet_ntoa(*((struct in_addr *)nlp_host->h_addr)));//inet_addr(nlp_host->h_addr);//inet_addr(nlp_host);//"172.16.17.201");//htonl(INADDR_ANY);
        //pin.sin_addr.s_addr=((struct in_addr *)(nlp_host->h_addr))->s_addr;//inet_addr(inet_ntoa(*((struct in_addr *)nlp_host->h_addr)));//inet_addr(nlp_host->h_addr);//inet_addr(nlp_host);//"172.16.17.201");//htonl(INADDR_ANY);

        if(nlp_host == NULL)
        {
            pin.sin_addr.s_addr=inet_addr("dtgtest.org");
        }
        else
        {
            //pin.sin_addr=*(struct in_addr *)*nlp_host->h_addr_list;//inet_addr(inet_ntoa(*((struct in_addr *)nlp_host->h_addr)));//inet_addr(nlp_host->h_addr);//inet_addr(nlp_host);//"172.16.17.201");//htonl(INADDR_ANY);
            memcpy(&pin.sin_addr.s_addr, nlp_host->h_addr, 4);
        }

        //pin.sin_addr.s_addr=htonl(INADDR_ANY);
       // pin.sin_addr=*((struct in_addr *)nlp_host->h_addr);
        pin.sin_port=htons(port);

        //built socket
        printf("Start Socket set\n");
        if((sd=socket(AF_INET,SOCK_STREAM,0))<0)
        {
        	 //perror("socket");
            printf("Socket Error\n");
    	      return (U32)errno;
        }
        printf("Start connect\n");
        //connect to server
        while (connect(sd,(struct sockaddr*)&pin,sizeof(pin))==-1)
        {
          //perror("connect");
          printf("error : %d\n",errno);
          printf("connect error\n");
          return (U32)errno;
        }

        return ReturnStatus;
}

U16 MApp_MHEG5_Connect_Server(char *ICStraddr, int *st)
{
   int port, RemoteAddrLen = sizeof(struct sockaddr_in);
   struct sockaddr_in RemoteAddr;
   struct hostent *nlp_host;
   char host_name[256];
   struct timeval tv;


   tv.tv_sec = 30000 / 1000 ;
   tv.tv_usec = ( 30000 % 1000) * 1000;


   strcpy((char *)host_name,(const char *)ICStraddr);

   if((nlp_host=gethostbyname(host_name))==NULL)
    {
       // printf("error  : %d\n",h_errno);
        printf("Resolve Error!\n");
        //return (U32)h_errno;
    }

    printf("host_name  : %s\n",host_name);

    printf("write data to remoteaddr\n");
    port = 3333;
    //Set remote server info
   bzero(&RemoteAddr,sizeof(RemoteAddr));
   RemoteAddr.sin_family=AF_INET;                 //AF_INET -> IPv4
   RemoteAddrLen = sizeof(RemoteAddr);
   RemoteAddr.sin_port = htons(port);
   //If system can`t resolve web name, we set default server to check connect status
   if(nlp_host == NULL)
   {
        RemoteAddr.sin_addr.s_addr=inet_addr(host_name);
   }
   else
   {
        //RemoteAddr.sin_addr = *((struct in_addr *)*nlp_host->h_addr_list);
        memcpy(&RemoteAddr.sin_addr.s_addr, nlp_host->h_addr, 4);
   }

   if((*st=socket(AF_INET,SOCK_STREAM,0))<0)
   {
      // printf("Socket Error\n");
	 return (U16)errno;
   }

   while (connect(*st,(struct sockaddr*)&RemoteAddr,sizeof(RemoteAddr))==-1)
   {
     //perror("connect");
     printf("connect error\n");
     shutdown(*st, 2);
     return (U16)errno;
   }


  /*  setsockopt(*st,SOL_SOCKET,SO_RCVBUF,(const char*)&nRecvBuf,sizeof(int));



    setsockopt(*st,SOL_SOCKET,SO_SNDBUF,(const char*)&nSendBuf,sizeof(int));

  if(setsockopt(*st,   SOL_SOCKET,   SO_RCVTIMEO,   (char*)&timeout,   sizeof(timeout))   <  0)
  {
        printf("Set Sock TimeOut error\n");
  }
*/



	/*tv.tv_sec = milliseconds / 1000 ;
	tv.tv_usec = ( milliseconds % 1000) * 1000  ;

    return setsockopt (connectSocket, SOL_SOCKET, SO_RCVTIMEO, (char
*)&tv, sizeof tv);*/

   setsockopt(*st,SOL_SOCKET,SO_RCVTIMEO,(char *)&tv,sizeof(tv));

  return 0;
}

U16 MApp_MHEG5_Check_And_Recv_Remainder(char *dest, int *Finaldestsize, int *st, int RecvSize,unsigned char *Finaldest )
{
    int optval, optlen = sizeof(optval), receivesize = 0;
    fd_set fds;
    struct timeval timeout={5,0}; //waiting time = 3 sec, 0 to non-block
    int     flags, i;

    if ((flags = fcntl(*st, F_GETFL, 0)) < 0)
    {
        printf("Get fcnt error\n");
    }

    if (fcntl(*st, F_SETFL, flags | O_NONBLOCK) < 0)
    {
        printf("Set fcnt error\n");
    }

   {
        if (fcntl(*st, F_SETFL, flags) < 0)
        {
            printf("Reset Cntl error\n");
        }


      // if(*nRet>0)
       {

        //Try Non-Block Socket
        while(1)
        {

            FD_ZERO(&fds); //reset fds everytime

            FD_SET(*st,&fds); //set socket

            printf("<<<<<<<<<<<<Check Server>>>>>>>>>>>>\n");

            switch(select(*st+1,&fds,NULL,NULL,&timeout)) //set select and run
            {

                case -1:
                    return 1;
                    break;

                case 0:
                    break;

                default:

                    if(FD_ISSET(*st,&fds))
                    {

                        if (getsockopt(*st, SOL_SOCKET, SO_ERROR, &optval, (socklen_t *)&optlen) < 0)
                        {
                            printf("Get SOCKEOPT ERROR\n");
                            break;
                        }

                        if (optval != 0)
                        {
                           printf("SOCKEOPT ERROR\n");
                           break;
                        }

                          printf("start to receive data\n");

                          receivesize=recv(*st,dest,RecvSize,0);

                         if(receivesize<0)
                         {
                            printf("Receive error\n");
                            return 1;
                            break;
                         }
                         else if(receivesize==0)
                         {
                            printf("Receive disconnect\n");
                            return 1;
                            break;
                         }
                          /*  {
                           dest[*nRet]=0;
                            }
                          else
                           dest[0]=0;*/
                           memcpy(&Finaldest[*Finaldestsize],dest, receivesize);


                       //   for(i=0;i<10;i++)
                       //     printf("Finaldest[%d]:%x\n",i,Finaldest[*Finaldestsize+i]);

                          *Finaldestsize += receivesize;
                          printf("\nReceived   bytes:%d\n",receivesize);
                          printf("*Finaldestsize   bytes:%d\n",*Finaldestsize);


                          /*printf("============STRAT HEADER INFO==============\n");
                          printf("Result:\n%.*s",*nRet,dest);
                          printf("\n============END HEADER INFO==============\n");*/

                         // return 0;
                    }// end if break;

            }// end switch

         }//end while

        }
   }

   printf("Can`t get data from server\n");
   //system can`t find data from server
   return 1;
}

U16 MApp_MHEG5_Send_And_Recv(char *dest, char *ReqStr, int *nRet, int *st, int RecvSize)
{
    int i, optval, optlen = sizeof(optval), totalsize = 0;
    fd_set fds;
    struct timeval timeout={5,0}; //waiting time = 3 sec, 0 to non-block
    int     flags;

    if ((flags = fcntl(*st, F_GETFL, 0)) < 0)
    {
        printf("Get fcnt error\n");
    }

    if (fcntl(*st, F_SETFL, flags | O_NONBLOCK) < 0)
    {
        printf("Set fcnt error\n");
    }

   *nRet   =   send(*st,   ReqStr,   strlen(ReqStr),   0);

   if(*nRet   <= 0)
   {
      printf("send()   failed");
      return (U32)errno;
   }
   else
   {
       printf("send()   OK : %d\n", *nRet);

        if (fcntl(*st, F_SETFL, flags) < 0)
        {
            printf("Reset Cntl error\n");
        }


      // if(*nRet>0)
       {

        //Try Non-Block Socket
        for(i=0;i<100;i++)
        {

            FD_ZERO(&fds); //reset fds everytime

            FD_SET(*st,&fds); //set socket

            printf("<<<<<<<<<<<<Check Server>>>>>>>>>>>>\n");

            switch(select(*st+1,&fds,NULL,NULL,&timeout)) //set select and run
            {

                case -1: exit(-1);
                    break;

                case 0:
                    break;

                default:

                    if(FD_ISSET(*st,&fds))
                    {

                        if (getsockopt(*st, SOL_SOCKET, SO_ERROR, &optval, (socklen_t *)&optlen) < 0)
                        {
                            printf("Get SOCKEOPT ERROR\n");
                            break;
                        }

                        if (optval != 0)
                        {
                           printf("SOCKEOPT ERROR\n");
                           break;
                        }

                          printf("start to receive data\n");

                          *nRet=recv(*st,dest,RecvSize,0);

                         if(*nRet<0)
                         {
                            printf("Receive error\n");
                            return 1;
                            break;
                         }
                         else if(*nRet==0)
                         {
                            printf("Receive disconnect\n");
                            return 1;
                            break;
                         }
                          /*  {
                           dest[*nRet]=0;
                            }
                          else
                           dest[0]=0;*/
                          totalsize += *nRet;
                          printf("\nReceived   bytes:%d\n",*nRet);
                          printf("\totalsize   bytes:%d\n",totalsize);
                          printf("============STRAT HEADER INFO==============\n");
                          printf("Result:\n%.*s",*nRet,dest);
                          printf("\n============END HEADER INFO==============\n");

                          return 0;
                    }// end if break;

            }// end switch

         }//end while

        }
   }

   printf("Can`t get data from server\n");
   //system can`t find data from server
   return 1;
}

bool MApp_MHEG5_Get_ReturnStatus(unsigned char *tempstr, U16 *ReturnStatus)
{
     char StrNum[3];
     unsigned char *TempChunkAddr;

     if(strncmp((const char *)tempstr,"HTTP/1.1",8) == 0)
     {
         printf("Get HTTP/1.1\n");
         TempChunkAddr = &tempstr[9];

         snprintf(&StrNum[0], sizeof(StrNum),"%.*s",1,TempChunkAddr);
         TempChunkAddr = &tempstr[10];
         snprintf(&StrNum[1], sizeof(StrNum),"%.*s",1,TempChunkAddr);
         TempChunkAddr = &tempstr[11];
         snprintf(&StrNum[2], sizeof(StrNum),"%.*s",1,TempChunkAddr);

         *ReturnStatus = (int)((StrNum[0]-48)*100 + (StrNum[1]-48)*10 + (StrNum[2]-48));
         printf("Final ReturnStatus : %d\n",*ReturnStatus);
     }

     if(*ReturnStatus==200 || *ReturnStatus==301 || *ReturnStatus==302 || *ReturnStatus==303 || *ReturnStatus==304 || *ReturnStatus==305 || *ReturnStatus==307 )
     {

return true;
     }

     return false;

}

U32 MApp_MHEG5_Signature(void)
{
    printf("Perform signature verification\n");
    return 1;
}

U32 MApp_MHEG5_Hash(unsigned char *Finaldest, int FinalInt, unsigned char *FullICStrAddr, unsigned char *ICStrAddr, U8 item)
{
    char dest[5000], ReqStr[MHEG5IC_HTTP_LENGTH];
    unsigned char sum[20];
    int st, nRet, i, urllen;
    U16 ReturnStatus = 0, ServerStatus;
    unsigned char *tempstr, *tempstr2;
    char filename[50], url[100], pathname[100];

    //Get URL
    if((tempstr = (unsigned char *)(strstr((char*)FullICStrAddr, "https://"))) == NULL)
        tempstr = (unsigned char *)(strstr((char*)FullICStrAddr, "http://"));
    tempstr2 = (unsigned char *)(strstr((char*)tempstr, "HTTP"));
    urllen = tempstr2 - tempstr - 1;

    //Get FileName
    strncpy(url, (char*)tempstr, urllen);
    for(i = urllen; i > 0; i --)
    {
        if(url[i] == '/')
        {
            strncpy(filename, url + i + 1, urllen - i);
            filename[urllen - i - 1] = '\0';
            break;
        }
    }
    url[i] = '\0';

    if(item == MHEG5IC_GETDATA_BY_GET)
    {
        snprintf(ReqStr, MHEG5IC_HTTP_LENGTH,"GET   %s/auth.hash %s", url, tempstr2);
        //snprintf(ReqStr, MHEG5IC_HTTP_LENGTH,"GET   %s",FullHashStr);
    }
    else if(item == MHEG5IC_GETDATA_BY_POST)
    {
        snprintf(ReqStr, MHEG5IC_HTTP_LENGTH,"POST   %s/auth.hash %s", url, tempstr2);
        //snprintf(ReqStr, MHEG5IC_HTTP_LENGTH,"POST   %s",FullHashStr);
    }

    printf("==========================MApp_MHEG5_Hash=====================\n");
    printf("Newreq string : %s\n",ReqStr);

    if((ServerStatus = MApp_MHEG5_Connect_Server((char *)ICStrAddr, &st))!=0)
    {
        printf("Connect Server Error\n");
        return ServerStatus;
    }

    if((ServerStatus = MApp_MHEG5_Send_And_Recv(dest, ReqStr,&nRet, &st, sizeof(dest)))!=0)
    {
         printf("Send And Recv Error\n");
         return ServerStatus;
    }

    //Start to analyze receive data

    tempstr = (unsigned char *)dest;
    if(!MApp_MHEG5_Get_ReturnStatus(tempstr, &ReturnStatus))
    {
        printf("File Not Found\n");
        return 0;
    }

    //printf("HASH CODE : ");
    if(nRet)
    {
        U16 digset_count, path_len;
        int j;
        struct Digest digest;//[20];
        struct HashName hashname;//[20][10];
        bool filenamematched = FALSE;

        dest[nRet] = 0;
        tempstr = (unsigned char *)&dest[0];

        //for( j = 0; j < nRet; j++ )
          //  printf( "%x, ", (unsigned char)tempstr[j] );
        //printf("\n");
        //printf("DEST : %.*s\n", nRet, tempstr);

        //Extract content
        tempstr = (unsigned char *)(strstr((char*)tempstr, "\n\r\n"));
        tempstr += 3;
        /*printf("\nResult:\n");
        for( j = 0; j < 10; j++ )
            printf( "%x, ", tempstr[j] );
        printf("\n");*/

        //Parsing Digest Info
        digset_count = ((*tempstr) << 8) | (*(tempstr + 1));
        tempstr += 2;
        printf("===================Parsing Digest Info================\n");
        printf("digest_count : %d\n", digset_count);

        if(digset_count != 0)
        {
            for(i = 0; i < digset_count; i++)
            {
                //Extract digest type
                digest.digest_type = *tempstr++;
                //Extract name_count
                digest.name_count = ((*tempstr) << 8) | (*(tempstr + 1));
                tempstr += 2;
                printf("Type : %x, NameCount : %x\n", digest.digest_type, digest.name_count);

                for(j = 0; j < digest.name_count; j++)
                {
                    //Extract NameLength
                    hashname.NameLength = *tempstr++;
                    if(hashname.NameLength == 0)
                        continue;
                    //Extract NameByte
                    strncpy(hashname.NameByte, (char*)tempstr, hashname.NameLength);
                    tempstr += hashname.NameLength;
                    *(hashname.NameByte + hashname.NameLength) = 0;
                    printf("NameLength : %x, NameByte : %.*s\n", hashname.NameLength, hashname.NameLength, hashname.NameByte);

                    //check if name match or not
                    if(!strcmp((char*)(&hashname.NameByte[0]), filename))
                    {
                        filenamematched = TRUE;
                        break;
                    }
                    tempstr += DIGEST_LENGTH;
                }

                if(filenamematched)
                {
                    if(digest.digest_type != 0)
                    {
                        printf("Byte : ");
                        for(j = 0; j < DIGEST_LENGTH; j++)
                        {
                            //Extract digest byte
                            digest.digest_byte[j] = *tempstr++;
                        }
                        //printf("\n==================================================\n");

                        printf("Perform SHA1 : %.*s\n", FinalInt, Finaldest);
                        //Perform SHA1
                        msAPI_sha1(Finaldest, FinalInt, sum);

                        /*for(j = 0; j < DIGEST_LENGTH; j++)
                            printf("%x", sum[j]);
                        printf("\n----------------------------------\n");
                        for(j = 0; j < DIGEST_LENGTH; j++)
                            printf("%x", digest.digest_byte[j]);
                        printf("\n");*/


                        for(j = 0; j < DIGEST_LENGTH; j++)
                        {
                            // compare digest
                            if(sum[j] != digest.digest_byte[j])
                            {
                                printf("the file contents are not consistent with the digest !!!!\n");
                                return 0;
                            }
                        }
                        printf("SHA1 Verification Sucess !!!!\n");
                    }

                    if(MApp_MHEG5_Signature())
                        return 1;

                }
            }

            printf("requested file is not listed in the hash file !!!!!\n");
            return 0;

        }
        else
        {
            //Path name matching
            printf("digset_count is 0!!!!\n");
            path_len = ((*tempstr) << 8) | (*(tempstr + 1));
            tempstr += 2;
            strncpy(pathname, (char*)tempstr, path_len);

            printf("pathname : %s\n", pathname);
            printf("url : %s\n", url);

            if((tempstr2 = (unsigned char *)(strstr(url, pathname))))
            {
                printf("tempstr2 : %s\n", tempstr2);
                if(!strcmp((char*)tempstr2, pathname))
                {
                    return 1;
                }
            }

            return 0;
        }

    }
    else
    {
        printf("no hash file exists : %d\n", nRet);
        return 0;
    }

    return 1;
}

void MApp_MHEG5_ProcessICS(unsigned char *TsSource, unsigned int *TsSize)
{
    int i;
    //Init TSP HW definition
    DMX_Filein_info stFileinInfo;
    VDEC_CodecType eCodecType;
    U8 Fid;
    U16 PID;
    U32 u32Size , DMXType;
    u32Size = (U32)*TsSize;
    DMXType = 0;
    Fid = (U8)MSAPI_DMX_INVALID_FLT_ID;
    PID = 301;
    DMXType = DMXType|MSAPI_DMX_FILTER_TYPE_VIDEO|MSAPI_DMX_FILTER_SOURCE_TYPE_FILE;

    printf("u32Size : %ld\n",u32Size);

    if (DMX_FILTER_STATUS_OK!= MApi_DMX_FlowSet(DMX_FLOW_PLAYBACK, DMX_FLOW_INPUT_MEM, FALSE, TRUE, TRUE))
    {
        printf("[VerDemux][%06d] switch to file-in fail\n", __LINE__);
    }

    //(TYPE1)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    msAPI_DMX_Stop(*MApp_Dmx_GetFid(EN_PCR_FID));               //PCR_FID
    msAPI_DMX_Close(*MApp_Dmx_GetFid(EN_PCR_FID));
    MApp_Dmx_SetFid(MSAPI_DMX_INVALID_FLT_ID, EN_PCR_FID);
    msAPI_DMX_Stop(*MApp_Dmx_GetFid(EN_VIDEO_FID) );               //VID_FID
    msAPI_DMX_Close(*MApp_Dmx_GetFid(EN_VIDEO_FID) );
    MApp_Dmx_SetFid(MSAPI_DMX_INVALID_FLT_ID, EN_VIDEO_FID);
    msAPI_DMX_Stop(*MApp_Dmx_GetFid(EN_AUDIO_FID));               //AUD_FID
    msAPI_DMX_Close(*MApp_Dmx_GetFid(EN_AUDIO_FID));
    MApp_Dmx_SetFid(MSAPI_DMX_INVALID_FLT_ID, EN_AUDIO_FID);
    msAPI_DMX_Stop(*MApp_Dmx_GetFid(EN_AD_FID));               //ADA_FID
    msAPI_DMX_Close(*MApp_Dmx_GetFid(EN_AD_FID));
    MApp_Dmx_SetFid(MSAPI_DMX_INVALID_FLT_ID, EN_AD_FID);
    //(TYPE2)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    msAPI_DMX_Stop(*MApp_Dmx_GetFid(EN_PES_FID));             //SUBTITLE_FID
    msAPI_DMX_Close(*MApp_Dmx_GetFid(EN_PES_FID));
    MApp_Dmx_SetFid(MSAPI_DMX_INVALID_FLT_ID, EN_PES_FID);


    stFileinInfo.PKT_Mode = DMX_PKTMODE_188;

    stFileinInfo.Rate = 0x2FF / 188;

    MApi_DMX_Filein_Info(&stFileinInfo);

    printf("Pass DMX info\n");

    if (!MApi_DMX_Filein_IsIdle())
    {
        printf("DMX is not idle\n");
        MApi_DMX_Filein_CMDQ_Reset();
    }

   // MApi_DMX_Filein_CMDQ_GetEmptyNum(&_u32MaxDmxCmdSlot);

   // printf("_u8MaxDmxCmdSlot=%lu\n",_u32MaxDmxCmdSlot);

    if(msAPI_DMX_StartFilter(PID, MSAPI_DMX_FILTER_TYPE_VIDEO|MSAPI_DMX_FILTER_SOURCE_TYPE_FILE, &Fid)!=DMX_FILTER_STATUS_OK)
    {
        printf("msAPI_DMX_StartFilter ERROR\n");
    }

    printf("Pass DMX StartFilter\n");

  //  msAPI_Player_ScalerFreeze();
   // msAPI_VID_Command(MSAPI_VID_STOP);
   // msAPI_Player_VideoInit(eCodecType,  2);

    //Init PID Filter

    eCodecType = E_VDEC_CODEC_TYPE_H264;
    msAPI_VID_SetMappingAVCParameter(eCodecType);

    printf("\nPass AVC\n");

    MApp_VID_VariableInit();

    printf("\nPass VID VariableInit\n");

    if(!msAPI_VID_Init(TRUE, E_VDEC_SRC_MODE_TS_FILE))
    {
        printf("VID INIT ERROR\n");
    }

    printf("\nPass VID Init\n");

   // msAPI_VID_SetTrickModeInfo(0, 1); /// Normal play

    printf("\nPass Set Trick\n");

   /* #ifndef S3PLUS
    msAPI_Player_ScalerWaitFree(10);
    #else
    msAPI_Player_ScalerWaitFree(50);
    #endif*/
   // msAPI_Player_VideoEncoderReset();
   // msAPI_Player_VideoMonitor(TRUE); // Reset GOP size info

   // msAPI_Player_ScalerFreeze();
  //  msAPI_VID_Command(MSAPI_VID_STOP);

    msAPI_VID_Command(MSAPI_VID_PLAY);
    printf("\nPass msAPI_VID_Command\n");

    if(MApi_DMX_Filein_Start(DMX_PES_NO_BYPASS_FIFO, (MS_PHYADDR)0x0003F50000, u32Size)==DMX_FILTER_STATUS_ERROR)
    {
        printf("\nMApi_DMX_Filein_Start ERROR\n");
    }

    printf("\nPass DMX FileIn\n");

    MApp_Scaler_SetWindow(NULL, NULL, NULL,
                               VIDEOSCREEN_FULL, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);

    MApi_XC_DisableInputSource(FALSE, MAIN_WINDOW);
    MApi_XC_GenerateBlackVideo( FALSE, MAIN_WINDOW );
    // set scaler window
 /*   MApp_MHEG5_GOP_GWIN_SwitchGOP(MHEG_GOP);
    MApp_MHEG5_Display_Finalize();

    // Switch back to OSD GOP1
    MApp_MHEG5_GOP_GWIN_SwitchGOP(E_GOP_OSD);*/
    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_MHEG5, DISABLE, 0, MAIN_WINDOW);
    msAPI_VE_SetBlackScreen(DISABLE);

    while(1);

}

U16 MApp_MHEG5_Init_Net(unsigned char *ICStrAddr, unsigned char *FullICStrAddr, U8 item)
{
    bool IsChunked = FALSE, IsSuccess = false, IsGetData = false;
    char host_name[256],dest[MHEG5IC_REC_LENGTH],ReqStr[MHEG5IC_HTTP_LENGTH];
    int st,nRet, i, k;
    U16 ReturnStatus = 0, ServerStatus;
    unsigned char *Finaldest, *TempChunkAddr = NULL,*tempstr;
    unsigned int *FinalInt;
    Finaldest = (unsigned char *)_PA2VA(0x0003F50000);
    FinalInt = (unsigned int *)_PA2VA(0x0003F40000);

    //WEB LINK STRING EXAMPLE

  /*    char*   req="POST   http://dtgtest.org/cgi-bin/mheg_test.cgi HTTP/1.1\r\n"
    "Host:   dtgtest.org\r\n"
   // "Content-Type: application/x-sh\r\n"
   // "Content-Type:   application/x-www-form-urlencoded"
    "Content-Length:   0\r\n\r\n";*/

    if(item == MHEG5IC_CHECKSERVER_STATUS)
    {
        return MApp_MHEG5_CheckServer_Status();
    }

    printf("===============MApp_MHEG5_Init_Net========================\n");

    if(item == MHEG5IC_GETDATA_BY_GET)
    {
        snprintf(ReqStr, MHEG5IC_HTTP_LENGTH,"GET   %s",FullICStrAddr);
    }
    else if(item == MHEG5IC_GETDATA_BY_POST)
    {
        snprintf(ReqStr, MHEG5IC_HTTP_LENGTH,"POST   %s",FullICStrAddr);
    }

    printf("Newreq string : %s\n",ReqStr);
    printf("start to check remote server\n");

    for(k=0;k<10;k++)
    {
        if((ServerStatus = MApp_MHEG5_Connect_Server((char *)ICStrAddr, &st))!=0)
        {
            printf("Connect Server Error\n");
            return ServerStatus;
        }
        else
        {
           printf("connect to %s success\n",host_name);
           printf("dest size : %d\n",sizeof(dest));
           if((ServerStatus = MApp_MHEG5_Send_And_Recv(dest, ReqStr,&nRet, &st, sizeof(dest)))==0)
           {
                k = 10;
           }
           else
           {
              printf("Server no response for receive data\n");
              shutdown(st, 2);
           }
       }
   }

   //If ServerStatus != 0 means system can`t connect server or can`t get data from HTTP
   if(ServerStatus != 0)
   {
        return ServerStatus;
   }

   TempChunkAddr = (unsigned char *)dest;
   tempstr = TempChunkAddr;

    //Start to analyze receive data
   for(i = 0; i <= (MHEG5IC_HTTP_LENGTH - 4);)
   {

     if((IsGetData = MApp_MHEG5_Get_ReturnStatus(tempstr, &ReturnStatus)))
     {
        break;
     }

      i++;
      tempstr = (unsigned char *)&dest[i];

   }

   if(IsGetData)
   {
       char *EndOfLink, *LocationPos;
       unsigned int LinkLength;

       printf("Get Status : %d\n",ReturnStatus);
       IsSuccess = true;
       nRet = nRet-i;
       printf("nRet : %d\n",nRet);
       TempChunkAddr = tempstr;

       //if there is a location to redirect to other web, system should re-send info to server to get new info
       if((LocationPos = strstr((char*)tempstr, "Location:"))!=NULL)
       {
          //In Rds mode, system should return origianl link status;
          printf("Get Redirect mode\n");

          //Skip "Location: "
          LocationPos = &LocationPos[10];

          if(((EndOfLink = strstr(LocationPos,"\r\n"))!=NULL))
          {

              int gt;

              if((ServerStatus = MApp_MHEG5_Connect_Server((char *)ICStrAddr, &gt))!=0)
              {
                  printf("Connect Server Error\n");
                  return ServerStatus;
              }

              LinkLength = (unsigned int)EndOfLink - (unsigned int)LocationPos;

              //printf("LinkLength : %X\n",LinkLength);

              snprintf(ReqStr, MHEG5IC_HTTP_LENGTH,"GET   %.*s HTTP/1.1\r\nHost:   172.16.17.201\r\nContent-Type: application/x-sh\r\nContent-Length:   0\r\n\r\n",LinkLength,LocationPos);

              printf("Start to re-send Request to server\n");

              if((ServerStatus = MApp_MHEG5_Send_And_Recv(dest, ReqStr,&nRet, &gt, sizeof(dest)))!=0)
              {
                   printf("Send And Recv Error\n");
                   return ServerStatus;
              }

               TempChunkAddr = (unsigned char *)&dest[0];
               shutdown(gt, 2);
           }
           else
           {
               printf("Wrong return !!\n");
           }
       }
   }

   if(IsSuccess)
   {
       char *TempTestAddr;
       tempstr = (unsigned char *)&TempChunkAddr[0];
       printf("tempstr : %.*s\n",20,tempstr);
       memset(FinalInt, 0, MHEG5IC_HTTP_LENGTH);
       memset(Finaldest, 0, MHEG5IC_REC_LENGTH);

       if((TempTestAddr = strstr((char*)tempstr, "Transfer-Encoding"))!=NULL)
       {
          IsChunked = TRUE;
          printf("Get chunked mode\n");
       }

       if((TempTestAddr = strstr((char*)tempstr, "\r\n\r\n"))!=NULL)
       {
             int DataLength = (int)((int)TempTestAddr - (int)tempstr);

             printf("Find final symbol\n");
             TempChunkAddr = (unsigned char *)&TempTestAddr[4];
             DataLength += 4;

            if((nRet-DataLength) >= 0)
              *FinalInt = nRet-DataLength;
             else
              *FinalInt = 0;

             printf("============STRAT FINAL INFO : %d-%d=%d==============\n",nRet, DataLength, *FinalInt);
             printf("Result:\n%.*s",nRet,TempChunkAddr);
             printf("\n============END FINAL INFO==============\n");
       }
       else
       {
          printf("Error! Can`t find the end of Head-Info\n");
       }

       //If this is a chunked response, system should use different method to get data
       if(IsChunked)
       {
             char *TempTestStr;

             TempChunkAddr = &TempChunkAddr[3];
             tempstr = (unsigned char *)TempChunkAddr;

             if(strncmp((char*)tempstr, "\r\n", 2)==0)
             {
                 printf("Get another symbol\n");
                 TempChunkAddr = &TempChunkAddr[2];
                 tempstr = (unsigned char *)TempChunkAddr;
             }
             else
             {
                printf("Error! Can`t find new Web Link for Re-Location\n");
             }

             printf("============STRAT Chunked INFO : %d==============\n",*FinalInt);

             if((TempTestStr = strstr((char*)tempstr, "\r\n0\r\n"))!=NULL)
             {
                 int DataLength = (int)((int)TempTestStr - (int)tempstr);
                 printf("DataLength = %d\n",DataLength);
                 *FinalInt = DataLength;
             }
             else
             {
                printf("Error! Can`t find the end of Web Link for Re-Location\n");
             }

             if(*FinalInt > 0)
             {
                 printf("Set new string\n");
                 //move to skip "d\r\n"
                 memcpy(Finaldest, TempChunkAddr, *FinalInt);
                 printf("FinalSize : %d\n",*FinalInt);
                 printf("Finaldest : %.*s\n",*FinalInt, Finaldest);
             }
               printf("\n============END Chunked INFO==============\n");
       }
       else
       {
             printf("There is no Chunked\n");
             memcpy(Finaldest, TempChunkAddr, *FinalInt);
             printf("FinalSize : %d\n",*FinalInt);
             printf("Finaldest : %.*s\n",*FinalInt, Finaldest);

            MApp_MHEG5_Check_And_Recv_Remainder(dest,(int *)FinalInt, &st, sizeof(dest),Finaldest );

            MApp_MHEG5_ProcessICS(Finaldest,FinalInt);

             MsOS_DelayTask(1000);
       }
       if(!MApp_MHEG5_Hash(Finaldest, *FinalInt, FullICStrAddr, ICStrAddr, item))
       {
           shutdown(st, 2);
           return 0;
       }
       printf("\nGet file from Server : %s\n",ICStrAddr);
       shutdown(st, 2);

       return ReturnStatus;

   }
   else
   {
      printf("\nCant get file from Server, error status : %.*s\n",3,(const char *)tempstr);
      shutdown(st, 2);
      return ReturnStatus;
   }

   printf("FullICStrAddr : %s\n",FullICStrAddr);

    shutdown(st, 2);
    return ReturnStatus;

}
#endif
/******************************************************************************/
/// restore MHEG5 window to full screen
///@param:
///      u8DoScreenMute : Enable or Disable MHEG5 screen mute
/******************************************************************************/
void MApp_MHEG5_RestoreWindow(U8 u8DoScreenMute)//for restore back small video
{
    if((msAPI_MHEG5_VID_IsFullScreen(&g_MHEG5Video.stMHEG5VideoAction) == FALSE) &&
        msAPI_MHEG5_checkGoBackMHEG5()
        )
    {
        if (u8DoScreenMute)
        {
            msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, 500, MAIN_WINDOW);
        }
        MApp_MVD_VariableInit();

    }
}


/******************************************************************************/
/// Enable or Disable MHEG5 Gwin and set video size.
///@param:
///      bEnable : Enable or Disable MHEG5 Gwin.
///      bRestoreVideoWindowSize : TRUE , set video to correct size.
///                                FALSE, do nothing.
/******************************************************************************/

void MApp_MHEG5_Set_Display(bool bEnable, bool bRestoreVideoWindowSize)
{
    MApp_MHEG5_GOP_GWIN_SwitchGOP(MHEG5_GOP);
    MApi_GOP_GWIN_Enable(MHEG5_GWINID, bEnable);
    MApp_MHEG5_GOP_GWIN_SwitchGOP(E_GOP_OSD);

    if(bRestoreVideoWindowSize)
    {
        if(msAPI_MHEG5_IsRunning())
        {
            //To set video size with non-MHEG5 setting.
            msAPI_MHEG5_SetRun(bEnable);
            MApp_Scaler_SetWindow(NULL, NULL, NULL,
                                           stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
            msAPI_MHEG5_SetRun(TRUE);
        }
        else
        {
            MApp_Scaler_SetWindow(NULL, NULL, NULL,
                                           stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
        }
    }
}


/******************************************************************************/
/// Switch current active GOP in MHEG5
/// @param u8GOP \b IN : Number of GOP
/******************************************************************************/
static void MApp_MHEG5_GOP_GWIN_SwitchGOP(U8 u8GOP)
{
    static U8 u8CurrentOSDGwinId = GWIN_ID_INVALID, u8CurrentAPPGwinId = GWIN_ID_INVALID;

    if(u8GOP == MHEG5_GOP)
    {
        u8CurrentOSDGwinId = MApi_GOP_GWIN_GetCurrentWinId();
        MApi_GOP_GWIN_SwitchGOP(MHEG5_GOP);
        if(u8CurrentAPPGwinId != GWIN_ID_INVALID)
        {
            MApi_GOP_GWIN_Switch2Gwin(u8CurrentAPPGwinId);
        }
      //printf("MApp_MHEG5_GOP_GWIN_SwitchGOP E_GOP_OSD(%bx) ==> MHEG5_GOP(%bx)\n",u8CurrentOSDGwinId,u8CurrentAPPGwinId);
    }

    if(u8GOP == E_GOP_OSD)
    {
        u8CurrentAPPGwinId = MApi_GOP_GWIN_GetCurrentWinId();
        MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD);
        if(u8CurrentOSDGwinId != GWIN_ID_INVALID)
        {
            MApi_GOP_GWIN_Switch2Gwin(u8CurrentOSDGwinId);
        }
      //printf("MApp_MHEG5_GOP_GWIN_SwitchGOP MHEG5_GOP(%bx) ==> E_GOP_OSD(%bx)\n",u8CurrentAPPGwinId,u8CurrentOSDGwinId);
    }
}

static void MApp_MHEG5_Display_Finalize(void)
{
    MApi_GOP_GWIN_DestroyWin(MHEG5_GWINID);
    // destroy DLA FrameBuffer
    msAPI_MHEG5_DestroyDLAFB();
    // destroy RenderTarget FrameBuffer
    MApi_GOP_GWIN_DestroyFB(MHEG5_RT_FBID);
    MApi_GOP_GWIN_EnableTransClr((EN_GOP_TRANSCLR_FMT)0, TRUE);
#if MHEG5_STATIC_FB
    MApi_GOP_GWIN_DestroyFB(MHEG5_OS_FBID);
#endif

#if (MHEG5_X_STRETCH_WAY == MHEG5_USE_GOP_STRETCH)
    MApi_GOP_GWIN_Set_HSCALE(FALSE, MHEG_XRES_OS, g_IPanel.Width());
#endif
#if (MHEG5_Y_STRETCH_WAY == MHEG5_USE_GOP_STRETCH)
    MApi_GOP_GWIN_Set_VSCALE(FALSE, MHEG_YRES_OS, g_IPanel.Height());
#endif
    MApi_GOP_Initialize_StretchWindow(MHEG5_GOP);

}

void MApp_MHEG5_SetGraphARCInfo(U8 u8Flag ,EN_ASPECT_RATIO_TYPE enVideoScreen)
{
    MS_ARC_PROG_WIN * pstMHEG5_ARC_Win = &g_MHEG5Video.stARCWin;
    MS_ARC_PROG_WIN * pstMHEG5_AFD_Win = &g_MHEG5Video.stAFDWin;

    SRC_RATIO_INFO tSrcRatioInfo;

    XC_ApiStatus stXCStatus;
    XC_SETWIN_INFO stXC_SetWin_Info;

    static U16 preDisHStart=0,preDisVStart=0,preDisHSize=0,preDisVSize=0;

    msAPI_MHEG5_SetGraphInfoRefreshType(0); //Reset

    if(MApi_XC_GetStatus(&stXCStatus, MAIN_WINDOW) == FALSE)
    {
        MS_DEBUG_MSG(printf("MApi_XC_GetStatus failed because of InitData wrong, please update header file and compile again\n"));
    }
    if(msAPI_MHEG5_IsRunning()==FALSE) return;

    // copy related data
    //memcpy(&stXC_SetWin_Info.stCapWin, &stXCStatus.stCapWin, sizeof(MS_WINDOW_TYPE));
    //memcpy(&stXC_SetWin_Info.stDispWin, &stXCStatus.stDispWin, sizeof(MS_WINDOW_TYPE));
    //memcpy(&stXC_SetWin_Info.stCropWin, &stXCStatus.stCropWin, sizeof(MS_WINDOW_TYPE));

    stXC_SetWin_Info.bInterlace = stXCStatus.bInterlace;
    stXC_SetWin_Info.u16InputVFreq = stXCStatus.u16InputVFreq;


    //Init Capture , Crop , Display size.
    stXC_SetWin_Info.stCapWin.x=stXC_SetWin_Info.stCropWin.x = 0;
    stXC_SetWin_Info.stCapWin.y=stXC_SetWin_Info.stCropWin.y = 0;
    if(g_MHEG5Video.bHaveVideo == FALSE && !msAPI_MHEG5_IsIFrameExist())
    {
        stXC_SetWin_Info.stCapWin.width=stXC_SetWin_Info.stCropWin.width   = MHEG_XRES;
        stXC_SetWin_Info.stCapWin.height=stXC_SetWin_Info.stCropWin.height = MHEG_YRES;
    }
    else
    {
        stXC_SetWin_Info.stCapWin.width=stXC_SetWin_Info.stCropWin.width   = stXCStatus.stCapWin.width;
        stXC_SetWin_Info.stCapWin.height=stXC_SetWin_Info.stCropWin.height = stXCStatus.stCapWin.height;

        if((stXC_SetWin_Info.stCapWin.width ==0)||(stXC_SetWin_Info.stCapWin.height ==0))
        {
            stXC_SetWin_Info.stCapWin.width=stXC_SetWin_Info.stCropWin.width   = MHEG_XRES;
            stXC_SetWin_Info.stCapWin.height=stXC_SetWin_Info.stCropWin.height = MHEG_YRES;
        }



    }
    stXC_SetWin_Info.stDispWin.x = 0;
    stXC_SetWin_Info.stDispWin.y = 0;
    stXC_SetWin_Info.stDispWin.width = g_IPanel.Width();
    stXC_SetWin_Info.stDispWin.height= g_IPanel.Height();
    //============

    tSrcRatioInfo.u16VideoWidth  = stXC_SetWin_Info.stCapWin.width;
    tSrcRatioInfo.u16VideoHeight = stXC_SetWin_Info.stCapWin.height;
    tSrcRatioInfo.u8AspectRate = gstVidStatus.u8AspectRate;
    tSrcRatioInfo.u8AFD = gstVidStatus.u8AFD;
	tSrcRatioInfo.u32SarWidth = gstVidStatus.u16SarWidth;
	tSrcRatioInfo.u32SarHeight = gstVidStatus.u16SarHeight;

    if ( u8Flag & SENDARC_AFD )
    {
        MApp_Scaler_Adjust_AspectRatio(MAIN_WINDOW,enVideoScreen, &stXC_SetWin_Info.stCropWin, &stXC_SetWin_Info.stDispWin, &tSrcRatioInfo,FALSE);
        MApp_Scaler_Adjust_OverscanRatio(MAIN_WINDOW, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), &stXC_SetWin_Info);

        stXC_SetWin_Info.stCropWin.width = ((stXC_SetWin_Info.stCropWin.width+stXC_SetWin_Info.stCropWin.x)*MHEG_XRES + stXC_SetWin_Info.stCapWin.width/2)/ stXC_SetWin_Info.stCapWin.width;
        stXC_SetWin_Info.stCropWin.height = ((stXC_SetWin_Info.stCropWin.height+stXC_SetWin_Info.stCropWin.y)*MHEG_YRES +stXC_SetWin_Info.stCapWin.height/2)/ stXC_SetWin_Info.stCapWin.height;

        stXC_SetWin_Info.stCropWin.x = stXC_SetWin_Info.stCropWin.x*MHEG_XRES / stXC_SetWin_Info.stCapWin.width;
        stXC_SetWin_Info.stCropWin.y = stXC_SetWin_Info.stCropWin.y*MHEG_YRES / stXC_SetWin_Info.stCapWin.height;

        stXC_SetWin_Info.stCropWin.width -= stXC_SetWin_Info.stCropWin.x;
        stXC_SetWin_Info.stCropWin.height-= stXC_SetWin_Info.stCropWin.y;

        //MApp_Scaler_AlignWindow(&stCropWin, 2, 2);
        pstMHEG5_AFD_Win->u16H_CapStart = stXC_SetWin_Info.stCropWin.x;
        pstMHEG5_AFD_Win->u16V_CapStart = stXC_SetWin_Info.stCropWin.y;
        pstMHEG5_AFD_Win->u16H_DisStart = stXC_SetWin_Info.stDispWin.x;
        pstMHEG5_AFD_Win->u16V_DisStart = stXC_SetWin_Info.stDispWin.y;
        pstMHEG5_AFD_Win->u16H_CapSize = stXC_SetWin_Info.stCropWin.width;
        pstMHEG5_AFD_Win->u16V_CapSize = stXC_SetWin_Info.stCropWin.height;
        pstMHEG5_AFD_Win->u16H_DisSize = stXC_SetWin_Info.stDispWin.width;
        pstMHEG5_AFD_Win->u16V_DisSize = stXC_SetWin_Info.stDispWin.height;
    }

    else if(u8Flag & SENDARC_AFD_FOR_GE || u8Flag & SENDARC_AFD_FOR_GE_MHEG5_INIT)
    {
        //if(enVideoScreen == VIDEOSCREEN_PROGRAM)
        //    MApp_Scaler_Adjust_AspectRatio(enVideoScreen, &stSrcWin, &stDstWin);
        //Only use display window
        MApp_Scaler_Adjust_AspectRatio(MAIN_WINDOW, enVideoScreen, &stXC_SetWin_Info.stCropWin, &stXC_SetWin_Info.stDispWin, &tSrcRatioInfo,TRUE);

        MApp_Scaler_Adjust_OverscanRatio(MAIN_WINDOW, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), &stXC_SetWin_Info);
         //MApp_Scaler_AlignWindow(&stCropWin, 8, 2);

        stXC_SetWin_Info.stCropWin.width = ((stXC_SetWin_Info.stCropWin.width+stXC_SetWin_Info.stCropWin.x)*MHEG_XRES + stXC_SetWin_Info.stCapWin.width/2)/ stXC_SetWin_Info.stCapWin.width;
        stXC_SetWin_Info.stCropWin.height = ((stXC_SetWin_Info.stCropWin.height+stXC_SetWin_Info.stCropWin.y)*MHEG_YRES +stXC_SetWin_Info.stCapWin.height/2)/ stXC_SetWin_Info.stCapWin.height;

        stXC_SetWin_Info.stCropWin.x = stXC_SetWin_Info.stCropWin.x*MHEG_XRES / stXC_SetWin_Info.stCapWin.width;
        stXC_SetWin_Info.stCropWin.y = stXC_SetWin_Info.stCropWin.y*MHEG_YRES / stXC_SetWin_Info.stCapWin.height;

        stXC_SetWin_Info.stCropWin.width -= stXC_SetWin_Info.stCropWin.x;
        stXC_SetWin_Info.stCropWin.height-= stXC_SetWin_Info.stCropWin.y;

        pstMHEG5_ARC_Win->u16H_CapStart = stXC_SetWin_Info.stCropWin.x;
        pstMHEG5_ARC_Win->u16V_CapStart = stXC_SetWin_Info.stCropWin.y;
        pstMHEG5_ARC_Win->u16H_DisStart = stXC_SetWin_Info.stDispWin.x;
        pstMHEG5_ARC_Win->u16V_DisStart = stXC_SetWin_Info.stDispWin.y;
        pstMHEG5_ARC_Win->u16H_CapSize = stXC_SetWin_Info.stCropWin.width;
        pstMHEG5_ARC_Win->u16V_CapSize = stXC_SetWin_Info.stCropWin.height;
        pstMHEG5_ARC_Win->u16H_DisSize = stXC_SetWin_Info.stDispWin.width;
        pstMHEG5_ARC_Win->u16V_DisSize = stXC_SetWin_Info.stDispWin.height;

        pstMHEG5_AFD_Win->u16H_CapStart = stXC_SetWin_Info.stCropWin.x;
        pstMHEG5_AFD_Win->u16V_CapStart = stXC_SetWin_Info.stCropWin.y;
        pstMHEG5_AFD_Win->u16H_DisStart = stXC_SetWin_Info.stDispWin.x;
        pstMHEG5_AFD_Win->u16V_DisStart = stXC_SetWin_Info.stDispWin.y;
        pstMHEG5_AFD_Win->u16H_CapSize = stXC_SetWin_Info.stCropWin.width;
        pstMHEG5_AFD_Win->u16V_CapSize = stXC_SetWin_Info.stCropWin.height;
        pstMHEG5_AFD_Win->u16H_DisSize = stXC_SetWin_Info.stDispWin.width;
        pstMHEG5_AFD_Win->u16V_DisSize = stXC_SetWin_Info.stDispWin.height;

    }
    else //if ( u8Flag & SENDARC_AFD_TRANS_FULLSCREEN )
    {
        MApp_Scaler_Adjust_AspectRatio(MAIN_WINDOW, enVideoScreen, &stXC_SetWin_Info.stCropWin, &stXC_SetWin_Info.stDispWin, &tSrcRatioInfo,FALSE);
        MApp_Scaler_Adjust_OverscanRatio(MAIN_WINDOW, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), &stXC_SetWin_Info);
        //MApp_Scaler_AlignWindow(&stCropWin, 8, 2);

        stXC_SetWin_Info.stCropWin.width = ((stXC_SetWin_Info.stCropWin.width+stXC_SetWin_Info.stCropWin.x)*MHEG_XRES + stXC_SetWin_Info.stCapWin.width/2)/ stXC_SetWin_Info.stCapWin.width;
        stXC_SetWin_Info.stCropWin.height = ((stXC_SetWin_Info.stCropWin.height+stXC_SetWin_Info.stCropWin.y)*MHEG_YRES +stXC_SetWin_Info.stCapWin.height/2)/ stXC_SetWin_Info.stCapWin.height;

        stXC_SetWin_Info.stCropWin.x = stXC_SetWin_Info.stCropWin.x*MHEG_XRES / stXC_SetWin_Info.stCapWin.width;
        stXC_SetWin_Info.stCropWin.y = stXC_SetWin_Info.stCropWin.y*MHEG_YRES / stXC_SetWin_Info.stCapWin.height;

        stXC_SetWin_Info.stCropWin.width -= stXC_SetWin_Info.stCropWin.x;
        stXC_SetWin_Info.stCropWin.height-= stXC_SetWin_Info.stCropWin.y;

        pstMHEG5_AFD_Win->u16H_CapStart = stXC_SetWin_Info.stCropWin.x;
        pstMHEG5_AFD_Win->u16V_CapStart = stXC_SetWin_Info.stCropWin.y;
        pstMHEG5_AFD_Win->u16H_DisStart = stXC_SetWin_Info.stDispWin.x;
        pstMHEG5_AFD_Win->u16V_DisStart = stXC_SetWin_Info.stDispWin.y;
        pstMHEG5_AFD_Win->u16H_CapSize = stXC_SetWin_Info.stCropWin.width;
        pstMHEG5_AFD_Win->u16V_CapSize = stXC_SetWin_Info.stCropWin.height;
        pstMHEG5_AFD_Win->u16H_DisSize = stXC_SetWin_Info.stDispWin.width;
        pstMHEG5_AFD_Win->u16V_DisSize = stXC_SetWin_Info.stDispWin.height;

        pstMHEG5_ARC_Win->u16H_CapStart = stXC_SetWin_Info.stCropWin.x;
        pstMHEG5_ARC_Win->u16V_CapStart = stXC_SetWin_Info.stCropWin.y;
        pstMHEG5_ARC_Win->u16H_DisStart = stXC_SetWin_Info.stDispWin.x;
        pstMHEG5_ARC_Win->u16V_DisStart = stXC_SetWin_Info.stDispWin.y;
        pstMHEG5_ARC_Win->u16H_CapSize = stXC_SetWin_Info.stCropWin.width;
        pstMHEG5_ARC_Win->u16V_CapSize = stXC_SetWin_Info.stCropWin.height;
        pstMHEG5_ARC_Win->u16H_DisSize = stXC_SetWin_Info.stDispWin.width;
        pstMHEG5_ARC_Win->u16V_DisSize = stXC_SetWin_Info.stDispWin.height;
    }

    //printf("MHEG5 graph info,cap: %d %d %d %d\n",pstMHEG5_ARC_Win->u16H_CapStart,pstMHEG5_ARC_Win->u16V_CapStart,pstMHEG5_ARC_Win->u16H_CapSize,pstMHEG5_ARC_Win->u16V_CapSize);
    //printf("MHEG5 graph info,dis: %d %d %d %d\n",pstMHEG5_ARC_Win->u16H_DisStart,pstMHEG5_ARC_Win->u16V_DisStart,pstMHEG5_ARC_Win->u16H_DisSize,pstMHEG5_ARC_Win->u16V_DisSize);
#if GOP_SCALERATIO_FIXED2
    if(! (u8Flag & SENDARC_AFD) )
    {
        msAPI_MHEG5_VID_SendARCInfo(u8Flag, ST_VIDEO.eAspectRatio);

        MApi_GOP_GWIN_SwitchGOP(MHEG5_GOP);
	#if 1
        if(!(preDisHStart==0 && preDisVStart==0 && preDisHSize==0 && preDisVSize==0))
        {
            S16 s16HTmpStart,s16HTmpSize,s16VTmpStart,s16VTmpSize;
            U16 i;
            if(pstMHEG5_ARC_Win->u16H_DisStart != preDisHStart || pstMHEG5_ARC_Win->u16V_DisStart != preDisVStart)
            {
                for(i=1;i<5;i++)
                {
                    s16HTmpStart = (((S16)pstMHEG5_ARC_Win->u16H_DisStart - preDisHStart)*i /20);
                    s16HTmpSize = s16HTmpStart *(-2);
                    s16VTmpStart = (((S16)pstMHEG5_ARC_Win->u16V_DisStart - preDisVStart)*i /20);
                    s16VTmpSize = s16VTmpStart *(-2);
                    //update GOP register at one time.
                    MApi_GOP_GWIN_UpdateRegOnce(TRUE);
                    MApi_GOP_GWIN_SetForceWrite(TRUE);
                    MApi_GOP_GWIN_SwitchGOP(MHEG5_GOP);
                    MApi_GOP_GWIN_Set_STRETCHWIN(MHEG5_GOP,E_GOP_DST_OP0, preDisHStart + s16HTmpStart ,preDisVStart + s16VTmpStart, MHEG_XRES_OS, MHEG_YRES_OS);
                    MApi_GOP_GWIN_Set_HSCALE(TRUE, MHEG_XRES_OS, preDisHSize + s16HTmpSize);
                    MApi_GOP_GWIN_UpdateRegOnce(FALSE);
                    MApi_GOP_GWIN_Set_VSCALE(TRUE, MHEG_YRES_OS, preDisVSize + s16VTmpSize);
                    MsOS_DelayTask(10);
                }
            }
        }
	#endif
        MApi_GOP_GWIN_UpdateRegOnce(TRUE);
        MApi_GOP_GWIN_SetForceWrite(TRUE);
        MApi_GOP_GWIN_Set_HStretchMode(E_GOP_HSTRCH_6TAPE_LINEAR);
		MApi_GOP_GWIN_SwitchGOP(MHEG5_GOP);
        MApi_GOP_GWIN_Set_STRETCHWIN(MHEG5_GOP,E_GOP_DST_OP0, pstMHEG5_ARC_Win->u16H_DisStart, pstMHEG5_ARC_Win->u16V_DisStart, MHEG_XRES_OS, MHEG_YRES_OS);
        MApi_GOP_GWIN_Set_HSCALE(TRUE, MHEG_XRES_OS, pstMHEG5_ARC_Win->u16H_DisSize);
        MApi_GOP_GWIN_UpdateRegOnce(FALSE);
        MApi_GOP_GWIN_Set_VSCALE(TRUE, MHEG_YRES_OS, pstMHEG5_ARC_Win->u16V_DisSize);

        preDisHStart = pstMHEG5_ARC_Win->u16H_DisStart;
        preDisHSize  = pstMHEG5_ARC_Win->u16H_DisSize;
        preDisVStart = pstMHEG5_ARC_Win->u16V_DisStart;
        preDisVSize  = pstMHEG5_ARC_Win->u16V_DisSize;

        MApi_GOP_GWIN_SetForceWrite(FALSE);
        MApi_GOP_GWIN_SwitchGOP(E_GOP_OSD);
    }
    else
#endif
    {
        msAPI_MHEG5_VID_SendARCInfo(u8Flag, ST_VIDEO.eAspectRatio);
    }
}

static void MApp_MHEG5_SetGraphInfoMonitor(void)
{
    if(msAPI_MHEG5_GetGraphInfoRefreshType())
    {
        MApp_MHEG5_SetGraphARCInfo(msAPI_MHEG5_GetGraphInfoRefreshType(),stSystemInfo[MAIN_WINDOW].enAspectRatio);
        if(g_MHEG5Video.bHaveVideo || msAPI_MHEG5_IsIFrameExist())
        {
            MApi_XC_SkipOPWriteOffInSetWindow(TRUE, MAIN_WINDOW);
            MApp_Scaler_SetWindow(NULL, NULL, NULL,
                              stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
            MApi_XC_SkipOPWriteOffInSetWindow(FALSE, MAIN_WINDOW);
        }
        //printf("set graph trigger========vvvvvvv====\n");
    }
}

/******************************************************************************/
/// This api function will Enable MHEG5.
/******************************************************************************/
BOOLEAN MApi_MHEG5_Enable(EN_MHEG5_ENABLE_MODE EnableMode)
{
    switch(EnableMode)
    {
        case EN_MHEG5_EM_AUTOBOOT:
            msAPI_MHEG5_SetGoBackMHEG5(TRUE);

        //case EN_MHEG5_EM_BACKGROUND_LOADING:

            break;

        default:
            break;
    }
    return TRUE;
}

/******************************************************************************/
/// This api function will Disable MHEG5.
/******************************************************************************/
BOOLEAN MApi_MHEG5_Disable(EN_MHEG5_DISABLE_MODE DisableMode)
{
    // add criteria to avoid misuse of this function - if mheg does not run or mheg bin is not loaded, return directly.
    if (msAPI_MHEG5_GetBinStatus()==FALSE)
    {
        return FALSE;
    }

    switch(DisableMode)
    {
        case EN_MHEG5_DM_DISABLE_AND_STOPDSMCC:  // This will stop MHEG5 and stop DSMCC
            msAPI_MHEG5_StopDsmcc(FALSE);
            MApp_MHEG5_Force_Exit();
            msAPI_MHEG5_SetGoBackMHEG5(FALSE);
            MApp_MHEG5_DsmccTime_Reset();
            enCheckMHEGLoadingStatus = EN_MHEG5_MONITOR;
            break;

        case EN_MHEG5_DM_DISABLE_WITH_AUTOBOOT_LATER: // This will close MHEG5 graph only, but MHEG5 will autoboot on TV monitor.
            MApp_MHEG5_Force_Exit();
            if(msAPI_MHEG5_IsRunning() == TRUE)
                msAPI_MHEG5_SetGoBackMHEG5(TRUE);
            break;

        case EN_MHEG5_DM_DISABLE:               //This will close MHEG5 graph, but it can't autoboot itself if we don't execute MApi_MHEG5_Enable(EN_MHEG5_EM_AUTOBOOT).
            MApp_MHEG5_Force_Exit();
            msAPI_MHEG5_SetGoBackMHEG5(FALSE);
            break;

        case EN_MHEG5_DM_DISABLE_AND_WAIT:
            msAPI_MHEG5_StopDsmcc(TRUE);
            MApp_MHEG5_Force_Exit();
            msAPI_MHEG5_SetGoBackMHEG5(FALSE);
            MApp_MHEG5_DsmccTime_Reset();
            enCheckMHEGLoadingStatus = EN_MHEG5_MONITOR;
            break;
        default:
            break;
    }
    return TRUE;
}

void MApp_MHEG5_Enable_LiveMHEG5(BOOL bEnable)
{
	_EnableCheckMHEG5Status=bEnable;
}

SI_MHEG5_STATUS MApp_MHEG5_CheckMHEG5Status()
{
	if(!_EnableCheckMHEG5Status)return SI_MHEG5_DISABLE;
	return MApp_SI_CheckMHEG5Status();
}

void MApp_MHEG5_ExitMheg5(void)
{
	gbPVRSetModeWhenExitMheg5 = FALSE;
	//exit mheg from small window or I frame video, force do timing change
	if ((msAPI_MHEG5_IsRunning() == TRUE)
        && ((!msAPI_MHEG5_VID_IsFullScreen(&g_MHEG5Video.stMHEG5VideoAction)) || msAPI_MHEG5_IsIFrameExist()))
	{
		gbPVRSetModeWhenExitMheg5 = TRUE;
	}
	MApi_MHEG5_Disable(EN_MHEG5_DM_DISABLE_AND_STOPDSMCC);
	if (gbPVRSetModeWhenExitMheg5 == TRUE)
	{
		MApp_VID_VariableInit();  //force timing change
		//if timing change when exit Mheg5,we should wait timing stable,then begin timeshift
		{
			#define TimingStableCount  4000
			U32 u32WaitTimingStable = msAPI_Timer_GetTime0();
			while (msAPI_Timer_DiffTimeFromNow(u32WaitTimingStable) < TimingStableCount)
			{
				MApp_VID_TimingMonitor(MAIN_WINDOW);
				if (MApp_VID_SetMode(MAIN_WINDOW))
				{
				#if(ENABLE_PVR)
					msAPI_Player_ScalerFree();
                #endif
                    PRINT_CURRENT_LINE();
					msAPI_Timer_Delayms(200);
					msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, DISABLE, 0, MAIN_WINDOW);
					break;
				}
			}
		}
	}
}
#endif

#undef _MAPP_MHEG5_MAIN_C_

