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

#define _MAPP_MHEG5_C_

/******************************************************************************/
/*                            Header Files                                    */
/* ****************************************************************************/
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "ZUI_tables_h.inl"

#if MHEG5_ENABLE

#include "MsTypes.h"
#include "drvBDMA.h"
#include "hwreg.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "apiXC_Sys.h"

#include "MApp_GlobalSettingSt.h"
#include "MApp_MHEG5_Main.h"
#include "mapp_mheg5.h"
#include "msAPI_Timer.h"
#include "msAPI_MailBox.h"

#define ENABLE_GE_TIMER 1
#include "MApp_MVDMode.h"
#include "MApp_GlobalFunction.h"
#include "MApp_SignalMonitor.h"
#include "mapp_demux.h"
#include "MApp_Scaler.h"
#include "MApp_Audio.h"
#include "MApp_MVDMode.h"

#include "MApp_ChannelChange.h"
#include "MApp_TopStateMachine.h"
#include "MApp_PCMode.h"
#include "MApp_UiMenuDef.h"
#include "MApp_ZUI_Main.h" //ZUI
#include "ZUI_exefunc.h" //ZUI
#include "MApp_TV.h" //ZUI
#include "mapp_si.h"
#include "msAPI_audio.h"
#include "MApp_Main.h"
#include "MApp_Sleep.h"
#include "msAPI_MHEG5.h"
#include "msAPI_Subtitle_Pub.h"
#include "msAPI_DrvInit.h"
#include "msAPI_MIU.h"

#include <string.h>

#if CIPLUS_MHEG
#include "msAPI_CI.h"
#endif

#if (ENABLE_PVR == 1)
#include "MApp_TimeShift.h"
#include "MApp_Playback.h"
#endif


#if (ENABLE_PIP)
#include "MApp_PIP.h"
#endif

#define M5DBG(x)        //x
U16 g_u16MHEG5_VideoPID=0, g_u16MHEG5_AudioPID=0;
BOOLEAN g_PIDfromMHEG5=false;
BOOLEAN g_bQuietlyTune=false;

#if (CIPLUS_MHEG && ENABLE_CI_PLUS)
static void MApp_MHEG5_CIMHEGProcessMailBox(U8 *u8MailBox);
#endif

extern MHEG5EventHandle _mheg5EventHandle;
#define M5_VIDEO_TYPE_MPEG2     0
#define M5_VIDEO_TYPE_H264      1
#define M5_VIDEO_TYPE_INVAILD   2


/******************************************************************************/
///- extern M5API
/******************************************************************************/
extern void M5API_GFX_SetMHEGDrawFlag(bool bDrawing);

/******************************************************************************/


static U32 u32DSMCC_Start_Timer = 0;

void MApp_MHEG5_DsmccTime_Update()
{
    u32DSMCC_Start_Timer = msAPI_Timer_GetTime0();
}

void MApp_MHEG5_DsmccTime_Reset()
{
    u32DSMCC_Start_Timer = 0;
}

U32 MApp_MHEG5_DsmccTime_Get()
{
    return u32DSMCC_Start_Timer;
}

void MApp_MHEG5_BootingMonitor()
{
    if (MApp_MHEG5_CheckMHEG5Status() == SI_MHEG5_DATA_ONLY && msAPI_Timer_DiffTimeFromNow(MApp_MHEG5_DsmccTime_Get()) < 1*1000)//display at least i seconds
        return;
#if CIPLUS_MHEG
    // cimheg still runs when "no signal"
    if (msAPI_IsCIMHEGRun()==E_MHEG_CI_RUNNING)
    {
        if ((MApp_ZUI_GetActiveOSD()!=E_OSD_EMPTY) && (SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW)!=EN_SCREENSAVER_NULL))
        {
    #if CIMHEG_DBG
            printf("shut down NO SIGNAL ui.... in cimheg\n");
    #endif
            // shut down UI
            MApp_ZUI_ACT_ShutdownOSD();
            SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW) = EN_SCREENSAVER_NULL;
        }
    }
#endif

#if 0
    // kill the god damn "mheg only" screen saver because the criteria to run mheg is that no other osd is shown.
    // it takes time to show mheg osd. show the "mheg only" screen saver is so ugly.
    // i don't know who defines the mheg only screen saver spec when no mheg osd is shown.
    if (SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW)==EN_SCREENSAVER_MHEGONLY)
    {
        SYS_SCREEN_SAVER_TYPE(MAIN_WINDOW) = EN_SCREENSAVER_NULL;
    }
#endif
    if (    (MApp_ZUI_GetActiveOSD() == E_OSD_SCREEN_SAVER)
         || (MApp_ZUI_GetActiveOSD() == E_OSD_EMPTY)
         || (MApp_ZUI_GetActiveOSD() == E_OSD_PVR)
         )
    {
        M5_MB_RETURN_STATE  return_state = MApp_MHEG5_ProcessMailBox();
        if (return_state == MB_RETURN_NO_MHEG5_DATA)
        {
            MApp_MHEG5_Enable_LiveMHEG5(FALSE);
        }
        if (return_state == MB_RETURN_MHEG5_AUTOBOOT)
        {
            MApp_MHEG5_Enable_LiveMHEG5(TRUE);

    #if CIPLUS_MHEG
            if (msAPI_IsCIMHEGRun()==E_MHEG_CI_RUNNING)
            {
                MApp_MHEG5_Enable_LiveMHEG5(FALSE);
        #if CIMHEG_DBG
                printf("mheg ci got autoboot...\n");
        #endif

                if (MApp_MHEG5_CheckGoMHEG5Process()==FALSE
                    #if (ENABLE_PIP) //Do not allow entering MHEG5 when PIP mode is ON
                    && (MApp_Get_PIPMode() == EN_PIP_MODE_OFF)
                    #endif
                   )
                {
                    MApp_MHEG5_SetGoMHEG5Process(TRUE);
                }

                MApp_MHEG5_DsmccTime_Reset();
            }
            else
    #endif
            if ((MApp_MHEG5_CheckMHEG5Status() == SI_MHEG5_WITH_VIDEO)||
                (MApp_MHEG5_CheckMHEG5Status() == SI_MHEG5_DATA_ONLY))
            {
                MApp_MHEG5_DsmccTime_Reset();

                if (MApp_MHEG5_CheckGoMHEG5Process()==FALSE
                    #if ENABLE_PVR
                    && (!MApp_PVR_IsPlaybacking())
                    #endif
                    #if (ENABLE_PIP) //Do not allow entering MHEG5 when PIP mode is ON
                    && (MApp_Get_PIPMode() == EN_PIP_MODE_OFF)
                    #endif
                )
                {
                    MApp_MHEG5_SetGoMHEG5Process(TRUE);
                }
            }
            else//PMT change case
            {
                if (MApp_SI_Get_PMT_PID() != MSAPI_DMX_INVALID_PID)
                {
                    msAPI_MHEG5_TriggerDsmcc(MApp_SI_Get_PMT_PID());
                    MApp_MHEG5_DsmccTime_Reset();
                }
            }
        }
    }
}


/******************************************************************************/
/// This APP will process mail box
/// @return MB_RETURN_STATE: Mailbox process result status.
/******************************************************************************/
M5_MB_RETURN_STATE MApp_MHEG5_ProcessMailBox(void)
{
    int i;
    MBX_Class mbxClassArray[9] = {
                        E_MBX_CLASS_MHEG5_STATE ,
                        E_MBX_CLASS_CHANNEL ,
                        E_MBX_CLASS_MPEG ,
                        E_MBX_CLASS_VIDEO ,
                        E_MBX_CLASS_AUDIO ,
                        E_MBX_CLASS_LZSS,
                        E_MBX_CLASS_INPUT,
                        E_MBX_CLASS_SYSTEM,
                        E_MBX_CLASS_CI
                        };

    MBX_MSGQ_Status MsgQueueStatus;

    memset(&MsgQueueStatus, 0, sizeof(MBX_MSGQ_Status));

    //printf("HK %s:%d\n",__FUNCTION__,__LINE__);

#if CIPLUS_MHEG
    for(i=0;i<9;i++)
#else
    for(i=0;i<8;i++)
#endif
    {
        U32 u32CurrentMsgNumber = 0;
        //U16 msgCounter = 0;
        MBX_Result mbx_result;
        mbx_result = MSApi_MBX_GetMsgQueueStatus(mbxClassArray[i], &MsgQueueStatus);
        //mbx_result = MSApi_MBX_GetMsgQueueStatus(E_MBX_CLASS_MHEG5_STATE, &MsgQueueStatus);
        //printf("MSApi_MBX_GetMsgQueueStatus:%bx\n",mbx_result);
        //printf("MsgQueueStatus:%lx , %lu, %lu\n",MsgQueueStatus.status , MsgQueueStatus.u32InstantMsgCount , MsgQueueStatus.u32NormalMsgCount);

        //Bit MBX_STATUS_QUEUE_OVER_FLOW means message queue is overflow and new message will be dropped;
        //Bit MBX_STATUS_QUEUE_HAS_INSTANT_MSG means there is INSTANT message in message queue;
        //Bit MBX_STATUS_QUEUE_HAS_NORMAL_MSG means there is NORMAL message in message queue;

        if(MsgQueueStatus.status & MBX_STATUS_QUEUE_HAS_INSTANT_MSG)
        {
            u32CurrentMsgNumber = MsgQueueStatus.u32InstantMsgCount;
            //printf("MBX_STATUS_QUEUE_HAS_INSTANT_MSG1:%lu\n",u32CurrentMsgNumber);
        }
        else
        if(MsgQueueStatus.status & MBX_STATUS_QUEUE_HAS_NORMAL_MSG)
        {
            u32CurrentMsgNumber = MsgQueueStatus.u32NormalMsgCount;
            //printf("MBX_STATUS_QUEUE_HAS_NORMAL_MSG2:%lu\n",u32CurrentMsgNumber);
        }

        //for(msgCounter = 0; msgCounter < u32CurrentMsgNumber ; msgCounter++)
        if(u32CurrentMsgNumber > 0)
        {
            MBX_Msg msg;
            U8 u8Msg[13];

            memset(&msg, 0, sizeof(MBX_Msg));

            //(MBX_Class eTargetClass, MBX_Msg *pMsg, MS_U32 u32WaitMillSecs, MS_U32 u32Flag);
            /*
            MBX_CHECK_ALL_MSG_CLASS -->recv any message class, this means, the targetClass is useless if this bit is set.
            MBX_CHECK_INSTANT_MSG-->check INSTANT message
            MBX_CHECK_NORMAL_MSG->Check Normal message
            MBX_CHECK_BLOCK_RECV-->block this function call until time out if no message available
            */

            if(MSApi_MBX_RecvMsg(mbxClassArray[i], &msg, 0, MBX_CHECK_NORMAL_MSG) == E_MBX_SUCCESS)
            {
                if(msg.u8MsgClass == E_MBX_CLASS_VIDEO)
                {
                    if(msg.u8Index & 0x40)
                    {
                        msg.u8MsgClass = E_MBX_CLASS_MPEG;
                        msg.u8Index &= 0xBF;
                    }
                }

                //printf("msg.u8MsgClass:%bx\n",(U8)msg.u8MsgClass);
                memcpy(&u8Msg[2],&msg.u8Parameters[0],10);
                u8Msg[1] = msg.u8Index;
                u8Msg[0] = msg.u8MsgClass;

                switch ((U8)msg.u8MsgClass) //command class
                {
                #if (CIPLUS_MHEG && ENABLE_CI_PLUS)
                    case E_MBX_CLASS_CI:
                        MApp_MHEG5_CIMHEGProcessMailBox( u8Msg);
                        break;
                #endif    // CIPLUS_MHEG


                    case E_MBX_CLASS_CHANNEL:
                      #if INTERACTION_CHANNEL
                        if(u8Msg[1]==MB_IC_CHECK_INIT)
                        {
                            MApp_MHEG5_ICProcessMailbox(msg.u8Parameters[0], msg.u8Parameters[1]);
                        }
                        else
                      #endif
                            MApp_MHEG5_ChannelProcessMailbox( u8Msg);
                        break;

                    case E_MBX_CLASS_MPEG:
                        MApp_IFrame_ProcessMailboxMsg(u8Msg);
                        break;

                    case E_MBX_CLASS_VIDEO:
                        MApp_VID_ProcessMailboxMsg( u8Msg);

                        if (((U8)msg.u8Index==MB_VIDEO_CHANNELCHANGE)||(msg.u8Index==MB_VIDEO_CHANNELCHANGE_LCN)||(msg.u8Index==MB_VIDEO_CHANNELCHANGE_PLUS_CHKTSID))
                        {
                            return MB_RETURN_MHEG5_CHANNELCHANGE;
                        }
                        else if(((U8)msg.u8Index==MB_VIDEO_CHANNELCHANGE_QUIETLY)||(msg.u8Index==MB_VIDEO_CHANNELCHANGE_LCN_QUIETLY)||(msg.u8Index==MB_VIDEO_CHANNELCHANGE_QUIETLY_PLUS_CHKTSID))
                        {
                            return MB_RETURN_MHEG5_EXIT;
                        }
                        break;

                    case E_MBX_CLASS_AUDIO:
                        msAPI_MHEG_AUD_ProcessMailbox( u8Msg);
                        break;

                    case E_MBX_CLASS_MHEG5_STATE:
                        //printf("PARM : %bx,%bx,%bx\n",(U8)msg.u8Index ,(U8)msg.u8Parameters[0],(U8)msg.u8Parameters[1]);
                        if (((U8)msg.u8Index) == MB_MHEG5_STATE_CMD_EXIT) //command index: MHEG-5 EXIT
                        {
                            if((U8)msg.u8Parameters[0]== MB_MHEG5_EXIT_SELECTED)
                            {
                                switch((U8)msg.u8Parameters[1])
                                {
                                    case KEY_SELECT:
                                    return MB_RETURN_MHEG5_SELECTED_QUIT_SEL;
                                    case KEY_0:
                                    return MB_RETURN_MHEG5_SELECTED_QUIT_0;
                                    case KEY_1:
                                    return MB_RETURN_MHEG5_SELECTED_QUIT_1;
                                    case KEY_2:
                                    return MB_RETURN_MHEG5_SELECTED_QUIT_2;
                                    case KEY_3:
                                    return MB_RETURN_MHEG5_SELECTED_QUIT_3;
                                    case KEY_4:
                                    return MB_RETURN_MHEG5_SELECTED_QUIT_4;
                                    case KEY_5:
                                    return MB_RETURN_MHEG5_SELECTED_QUIT_5;
                                    case KEY_6:
                                    return MB_RETURN_MHEG5_SELECTED_QUIT_6;
                                    case KEY_7:
                                    return MB_RETURN_MHEG5_SELECTED_QUIT_7;
                                    case KEY_8:
                                    return MB_RETURN_MHEG5_SELECTED_QUIT_8;
                                    case KEY_9:
                                    return MB_RETURN_MHEG5_SELECTED_QUIT_9;
                                }
                            }
                            else
                            {
                                return MB_RETURN_MHEG5_EXIT;
                            }
                        }
                        else if ((U8)msg.u8Index == MB_MHEG5_STATE_CMD_AUTOBOOT) //command index: MHEG-5 AUTO-BOOT
                        {
                            return MB_RETURN_MHEG5_AUTOBOOT;
                        }
                        else if ((U8)msg.u8Index == MB_MHEG5_STATE_CMD_NO_MHEG5) //command index: no mheg5 data
                        {
                            return MB_RETURN_NO_MHEG5_DATA;
                        }
                        else if ((U8)msg.u8Index == MB_MHEG5_STATE_CMD_CHANNEL_CHANGE) //command index: MHEG-5 CHANNEL_CHANGE
                        {
                            u8KeyCode=msg.u8Parameters[0];
                            return MB_RETURN_51_STATE_CHANNEL_CHANGE;
                        }
                        else if ((U8)msg.u8Index == MB_MHEG5_STATE_CMD_MHEG5_TO_MENU) //command index: MHEG-5 MHEG5_TO_MENU
                        {
                            u8KeyCode=msg.u8Parameters[0];
                            return MB_RETURN_51_STATE_MHEG5_TO_MENU;
                        }
                        else if ((U8)msg.u8Index == MB_MHEG5_STATE_CMD_KEY_REGISTER) //command index: MHEG-5 KEY_REGISTER
                        {
                            msAPI_MHEG5_SetKeyRegisterGroup(msg.u8Parameters[0]);
                        #if CIPLUS_MHEG_1_3
                            u8InputMask[0] = 0;
                            u8InputMask[1] = 0;
                            u8InputMask[2] = 0;

                            if (msAPI_MHEG5_GetKeyRegisterGroup() == 255)
                            {
                                U8 myindex = 0;
                                for (myindex=0; (myindex< msg.u8Parameters[2]) && (myindex<3); myindex++)
                                {
                                    u8InputMask[myindex] = msg.u8Parameters[myindex+3];
                                }
                            }
                            #if CIMHEG_DBG
                            printf("%d %d %d\n", u8InputMask[0], u8InputMask[1], u8InputMask[2]);
                            #endif
                        #endif
                            break;
                        }
                        else if ((U8)msg.u8Index == MB_MHEG5_STATE_DRAW_EVENT) //command index: MHEG-5 DRAWING EVENT
                        {
                            if(_mheg5EventHandle.DrawingCallback!=NULL)
                                _mheg5EventHandle.DrawingCallback(msg.u8Parameters[0]);
                            M5API_GFX_SetMHEGDrawFlag(msg.u8Parameters[0]);

                            break;
                        }
                        else //command index: unknown command index
                        {
                            break;
                        }

                        break; // Added by coverity_0609

                    default:
                        break;
                }
            }
        }
    }

    return M5_MB_RETURN_OK;
}


/******************************************************************************/
/// @internal
///- API for process video mailbox msg from Aeon
/// @param *u8MailBox \b IN: pointer to mail box
/******************************************************************************/
void MApp_VID_ProcessMailboxMsg(U8 *u8MailBox)
{
    U16 wService_ID = 0;
    U16 wOriNetwork_ID = 0;
    U16 wTsID = 0;
    BOOLEAN bCheckTsID = FALSE;
    EN_MHEG_5_TUNE_TYPE tuneType = TYPE_CHANNEL_CHANGE_SER_ID;

    MS_MHEG5_VIDEO_ACTION *pstMHEG5VideoAction = &g_MHEG5Video.stMHEG5VideoAction;
    MS_MHEG5_VIDEO_ACTION *pstPrevMHEG5VideoAction = &g_MHEG5Video.stPrevMHEG5VideoAction;
    //MS_MHEG5_VIDEO_CLIPWIN *pstMHEG5VideoClipWin = &g_MHEG5Video.stMHEG5VideoClipWin;

//    SHOW_VIDEO_INFO(("MApp_VID_ProcessMailboxMsg"));

    // Command Index
    M5DBG(printf("u8MailBox[1]:%bx,%bx\n",u8MailBox[1],u8MailBox[2]));
    switch (u8MailBox[1])
    {
    #if MHEG5_WITH_SUBTITLE
        case MB_VIDEO_SUBTITLE_CONTROL:
            msAPI_MHEG5_SetSubtitleMode(u8MailBox[2]);
            break;
    #endif
        case MB_VIDEO_SET_VIDEO_DISPLAY:
            switch (u8MailBox[2])
            {
                case MB_VIDEO_CMD_PLAY:
                    //printf("MB_VIDEO_CMD_PLAY\n");
                    M5API_VID_Command(MSAPI_VID_PLAY);
                    g_bIsImageFrozen = FALSE;
                    #if( ENABLE_PVR )
                     if(!(((MApp_TimeShift_StateMachineGet()==E_TIMESHIFT_STATE_RECORDING) && MApp_TimeShift_IfPause())
                        || (MApp_Playback_StateMachineGet()==E_PLAYBACK_STATE_PAUSE)))
                    #endif
                    {
                        MApi_XC_FreezeImg(g_bIsImageFrozen, MAIN_WINDOW);
                    }

                    if ( MApi_XC_IsBlackVideoEnable(MAIN_WINDOW) )
                    {
                        // Delay 500ms to prvent showing temprary video action
                        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, 500, MAIN_WINDOW);
                        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_MHEG5, DISABLE, 0, MAIN_WINDOW);
                    }
                    else
                    {
                        msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_MHEG5, DISABLE, 0, MAIN_WINDOW);
                    }

                    fEnableMvdTimingMonitor = TRUE;

                    if(g_u16Current_VideoPID !=INVALID_PID)
                        g_MHEG5Video.bHaveVideo = TRUE;
                    else
                        g_MHEG5Video.bHaveVideo = FALSE;

                    break;
                case MB_VIDEO_CMD_PAUSE:
                    //printf("MB_VIDEO_CMD_PAUSE\n");
                    M5API_VID_Command(MSAPI_VID_PAUSE);
                    g_bIsImageFrozen = TRUE;
                    MApi_XC_FreezeImg(g_bIsImageFrozen, MAIN_WINDOW);
                    fEnableMvdTimingMonitor = FALSE;
                    break;
                case MB_VIDEO_CMD_STOP:
                    //printf("MB_VIDEO_CMD_STOP\n");
                    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_MHEG5, ENABLE, 0, MAIN_WINDOW);
                    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, DISABLE, 0, MAIN_WINDOW);
                    M5API_VID_Command(MSAPI_VID_STOP);
                    //MAPI_VID_Init(msAPI_VID_GetCodecType(),FALSE);
                    //msAPI_VID_Init(FALSE);
                    g_MHEG5Video.bHaveVideo = FALSE;
                    msAPI_MHEG5_SetGraphInfoRefreshType(SENDARC_AFD_FOR_GE);
                    break;
                default:
                    break;
            }
            break;

        case MB_VIDEO_SET_STREAM_WITH_PID:

            //printf("MB_VIDEO_SET_STREAM_WITH_PID \n");
            wService_ID = ( (((U16)u8MailBox[2]) & 0x00FF) | ((((U16)u8MailBox[3]) << 8) & 0xFF00) );
            g_u16MHEG5_VideoPID = ( (((U16)u8MailBox[4]) & 0x00FF) | ((((U16)u8MailBox[5]) << 8) & 0xFF00) );
            g_u16MHEG5_AudioPID = ( (((U16)u8MailBox[6]) & 0x00FF) | ((((U16)u8MailBox[7]) << 8) & 0xFF00) );
            wOriNetwork_ID = ( (((U16)u8MailBox[8]) & 0x00FF) | ((((U16)u8MailBox[9]) << 8) & 0xFF00) );
            {
                VDEC_CodecType eCodecType=E_VDEC_CODEC_TYPE_MPEG2;
                if(u8MailBox[10] == M5_VIDEO_TYPE_INVAILD)
                {
                    //printf("==M5_VIDEO_TYPE_INVAILD==\n");
                    eCodecType = msAPI_CM_IsAVCService(wOriNetwork_ID,wService_ID) ? E_VDEC_CODEC_TYPE_H264 : E_VDEC_CODEC_TYPE_MPEG2;
                }
                else if(u8MailBox[10] == M5_VIDEO_TYPE_H264)
                {
                    eCodecType=E_VDEC_CODEC_TYPE_H264;
                }
                //msAPI_VID_SetMappingAVCParameter(eCodecType);
                M5API_VID_Switch2Codec(eCodecType, 0);
            }
            //printf("bAVCH264 %bu\n",bAVCH264);

            g_PIDfromMHEG5 = true;
            //printf("\nMB_VIDEO_SET_STREAM: wService_ID= %u\n", wService_ID);
            //printf("MB_VIDEO_SET_STREAM: u16VedioPID= %u\n", g_u16MHEG5_VideoPID);
            //printf("MB_VIDEO_SET_STREAM: u16AudioPID= %u\n", g_u16MHEG5_AudioPID);
            //printf("MB_VIDEO_SET_STREAM: g_PIDfromMHEG5= %bu\n", (U8)g_PIDfromMHEG5);

            g_MHEG5Video.u8VideoFlag |= EVER_SET_VIDEO_STREAM;
            MApp_ChannelChange_ChangeSpeciChannel( wService_ID, wOriNetwork_ID, wTsID, TYPE_TUNE_STREAM_SER_ID, bCheckTsID, TRUE);
            if ((g_u16MHEG5_AudioPID != INVALID_PID))
            {
                // if audio pid is valid, just unmute.
                // if we do unmute outside as before, in some cases, it will not get unmute successfully.
                // take DTG 6.10B as an example, it set stream with valid AV pids + stop video + decode_iframe
                // in a very short time, there should be sounds, but there is not.

                // 20151203:  Should not delay here! Even need delay, should delay inside msAPI_AUD_AdjustAudioFactor()
                //msAPI_Timer_Delayms(200);
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_PERMANENT_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            }

            if ( g_u16MHEG5_VideoPID == INVALID_PID && !g_MHEG5Video.bIFrame)
            {
                msAPI_Scaler_SetBlueScreen(ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
                //msAPI_MHEG5_VID_Send_CHANGESTREAM();
            }

            //=====================================================================
            //Switch Codec must execute after MApp_ChannelChange_ChangeSpeciChannel
            {
                VDEC_CodecType eCodecType=E_VDEC_CODEC_TYPE_MPEG2;

                if(u8MailBox[10] == M5_VIDEO_TYPE_INVAILD)
                {
                    eCodecType = msAPI_CM_IsAVCService(wOriNetwork_ID,wService_ID) ? E_VDEC_CODEC_TYPE_H264 : E_VDEC_CODEC_TYPE_MPEG2;
                }
                else
                if(u8MailBox[10])
                {
                    eCodecType=E_VDEC_CODEC_TYPE_H264;
                }
                //msAPI_VID_SetMappingAVCParameter(eCodecType);
                M5API_VID_Switch2Codec(eCodecType, 0);
            }
            //=====================================================================

            g_PIDfromMHEG5 = false;
           // printf("\nMB_VIDEO_SET_STREAM: g_PIDfromMHEG5= %bu\n", (U8)g_PIDfromMHEG5);


            break;

        case MB_VIDEO_SET_STREAM:

            //printf("MB_VIDEO_SET_STREAM \n");
            wService_ID = ( (((U16)u8MailBox[2]) & 0x00FF) | ((((U16)u8MailBox[3]) << 8) & 0xFF00) );
            MApp_ChannelChange_ChangeSpeciChannel( wService_ID, wOriNetwork_ID, wTsID, TYPE_TUNE_STREAM_SER_ID, bCheckTsID, TRUE);
            break;

    #if MHEG5_NDT
        // Non Destructive Tune
        case MB_VIDEO_NDT_CHANNELCHANGE_QUIETLY:
        case MB_VIDEO_NDT_CHANNELCHANGE_PLUS_CHKTSID_QUIETLY:
        case MB_VIDEO_NDT_CHANNELCHANGE:
        case MB_VIDEO_NDT_CHANNELCHANGE_PLUS_CHKTSID:
    #endif
        case MB_VIDEO_CHANNELCHANGE_QUIETLY:
        case MB_VIDEO_CHANNELCHANGE_QUIETLY_PLUS_CHKTSID:
        case MB_VIDEO_CHANNELCHANGE:
        case MB_VIDEO_CHANNELCHANGE_PLUS_CHKTSID:
        #if 0
            if (u8MailBox[1] == MB_VIDEO_CHANNELCHANGE_QUIETLY || u8MailBox[1] == MB_VIDEO_CHANNELCHANGE_QUIETLY_PLUS_CHKTSID
        #if MHEG5_NDT
                || u8MailBox[1] == MB_VIDEO_NDT_CHANNELCHANGE_QUIETLY || u8MailBox[1] == MB_VIDEO_NDT_CHANNELCHANGE_PLUS_CHKTSID_QUIETLY
        #endif
                )
            {
                g_bQuietlyTune = TRUE;
            }
        #if MHEG5_NDT
            if (u8MailBox[1] == MB_VIDEO_NDT_CHANNELCHANGE_QUIETLY ||
                u8MailBox[1] == MB_VIDEO_NDT_CHANNELCHANGE_PLUS_CHKTSID_QUIETLY ||
                u8MailBox[1] == MB_VIDEO_NDT_CHANNELCHANGE ||
                u8MailBox[1] == MB_VIDEO_NDT_CHANNELCHANGE_PLUS_CHKTSID)
            {
                msAPI_MHEG5_WaitNDTPid(true);
            }
        #endif
        #endif

            //printf("MB_VIDEO_CHANNELCHANGE \n");
            wService_ID = ( (((U16)u8MailBox[2]) & 0x00FF) | ((((U16)u8MailBox[3]) << 8) & 0xFF00) );
            wOriNetwork_ID= ( (((U16)u8MailBox[4]) & 0x00FF) | ((((U16)u8MailBox[5]) << 8) & 0xFF00) );
            wTsID   = ( (((U16)u8MailBox[6]) & 0x00FF) | ((((U16)u8MailBox[7]) << 8) & 0xFF00) );
            //printf("\nwService_ID= %u %u %u\n", wService_ID,wOriNetwork_ID,wTsID);
            //printf("wOriNetwork_ID: u16VedioPID= %u\n", wOriNetwork_ID);
            //printf("wTsID: u16AudioPID= %u\n", wTsID);

        #if 1

            switch(u8MailBox[1])
            {
                case MB_VIDEO_CHANNELCHANGE_QUIETLY_PLUS_CHKTSID:
                    bCheckTsID = TRUE;
                    tuneType = TYPE_CHANNEL_CHANGE_SER_ID_QUIETLY;
                    g_bQuietlyTune = TRUE;
                    break;
                case MB_VIDEO_CHANNELCHANGE_PLUS_CHKTSID:
                    bCheckTsID = TRUE;
                    tuneType = TYPE_CHANNEL_CHANGE_SER_ID;
                    break;
                case MB_VIDEO_CHANNELCHANGE_QUIETLY:
                    tuneType = TYPE_CHANNEL_CHANGE_SER_ID_QUIETLY;
                    g_bQuietlyTune = TRUE;
                    break;
                case MB_VIDEO_CHANNELCHANGE:
                    tuneType = TYPE_CHANNEL_CHANGE_SER_ID;
                    break;
            #if MHEG5_NDT
                case MB_VIDEO_NDT_CHANNELCHANGE_PLUS_CHKTSID_QUIETLY:
                    tuneType = TYPE_CHANNEL_CHANGE_SER_ID_QUIETLY_NDT;
                    bCheckTsID = TRUE;
                    g_bQuietlyTune = TRUE;
                    msAPI_MHEG5_WaitNDTPid(true);
                    msAPI_MHEG5_SetNDTChannelChange(true);
                    break;
                case MB_VIDEO_NDT_CHANNELCHANGE_PLUS_CHKTSID:
                    tuneType = TYPE_CHANNEL_CHANGE_SER_ID_NDT;
                    bCheckTsID = TRUE;
                    msAPI_MHEG5_WaitNDTPid(true);
                    msAPI_MHEG5_SetNDTChannelChange(true);
                    break;
                case MB_VIDEO_NDT_CHANNELCHANGE_QUIETLY:
                    tuneType = TYPE_CHANNEL_CHANGE_SER_ID_QUIETLY_NDT;
                    g_bQuietlyTune = TRUE;
                    msAPI_MHEG5_WaitNDTPid(true);
                    msAPI_MHEG5_SetNDTChannelChange(true);
                    break;
                case MB_VIDEO_NDT_CHANNELCHANGE:
                    tuneType = TYPE_CHANNEL_CHANGE_SER_ID_NDT;
                    msAPI_MHEG5_WaitNDTPid(true);
                    msAPI_MHEG5_SetNDTChannelChange(true);
                    break;
            #endif
                default:
                    ASSERT(0);
                    break;
            }

            MApp_ChannelChange_ChangeSpeciChannel(wService_ID, wOriNetwork_ID, wTsID, tuneType, bCheckTsID, TRUE);

            #if MHEG5_NDT
            msAPI_MHEG5_SetNDTChannelChange(false);
            #endif


        #else
            if ((u8MailBox[1]== MB_VIDEO_CHANNELCHANGE_QUIETLY_PLUS_CHKTSID) || (u8MailBox[1]==MB_VIDEO_CHANNELCHANGE_PLUS_CHKTSID))
            {
                bCheckTsID = TRUE;
                MApp_ChannelChange_ChangeSpeciChannel(wService_ID, wOriNetwork_ID, wTsID, u8MailBox[1] == MB_VIDEO_CHANNELCHANGE_PLUS_CHKTSID ? TYPE_CHANNEL_CHANGE_SER_ID : TYPE_CHANNEL_CHANGE_SER_ID_QUIETLY, bCheckTsID);
            }
        #if MHEG5_NDT
            else if (u8MailBox[1] == MB_VIDEO_CHANNELCHANGE_QUIETLY || u8MailBox[1] == MB_VIDEO_CHANNELCHANGE)
        #else
            else
        #endif
            {
                MApp_ChannelChange_ChangeSpeciChannel(wService_ID, wOriNetwork_ID, wTsID, u8MailBox[1] == MB_VIDEO_CHANNELCHANGE ? TYPE_CHANNEL_CHANGE_SER_ID : TYPE_CHANNEL_CHANGE_SER_ID_QUIETLY, bCheckTsID);
            }
        #if MHEG5_NDT
            else if (u8MailBox[1] == MB_VIDEO_NDT_CHANNELCHANGE_PLUS_CHKTSID_QUIETLY || u8MailBox[1] == MB_VIDEO_NDT_CHANNELCHANGE_PLUS_CHKTSID)
            {
                bCheckTsID = true;
                MApp_ChannelChange_ChangeSpeciChannel(wService_ID, wOriNetwork_ID, wTsID, u8MailBox[1] == MB_VIDEO_NDT_CHANNELCHANGE_PLUS_CHKTSID ? TYPE_CHANNEL_CHANGE_SER_ID_NDT : TYPE_CHANNEL_CHANGE_SER_ID_QUIETLY_NDT, bCheckTsID);
            }
            else if (u8MailBox[1] == MB_VIDEO_NDT_CHANNELCHANGE_QUIETLY || u8MailBox[1] == MB_VIDEO_NDT_CHANNELCHANGE)
            {
                MApp_ChannelChange_ChangeSpeciChannel(wService_ID, wOriNetwork_ID, wTsID, u8MailBox[1] == MB_VIDEO_NDT_CHANNELCHANGE ? TYPE_CHANNEL_CHANGE_SER_ID_NDT : TYPE_CHANNEL_CHANGE_SER_ID_QUIETLY_NDT, bCheckTsID);
            }
            else
            {
                // nothing
            }
        #endif
        #endif
            break;

        case MB_VIDEO_SET_STREAM_LCN:

            //printf("MB_VIDEO_SET_STREAM_LCN \n");
            // lcn: reuse the wService_ID
            wService_ID = ( (((U16)u8MailBox[2]) & 0x00FF) | ((((U16)u8MailBox[3]) << 8) & 0xFF00) );
            MApp_ChannelChange_ChangeSpeciChannel( wService_ID, wOriNetwork_ID, wTsID, TYPE_TUNE_STREAM_LCN, bCheckTsID, TRUE);

            break;

    #if MHEG5_NDT
        // Non Destructive Tune
        case MB_VIDEO_NDT_CHANNELCHANGE_LCN_QUIETLY:
        case MB_VIDEO_NDT_CHANNELCHANGE_LCN:
    #endif
        case MB_VIDEO_CHANNELCHANGE_LCN_QUIETLY:
        case MB_VIDEO_CHANNELCHANGE_LCN:
            if (u8MailBox[1] == MB_VIDEO_CHANNELCHANGE_LCN_QUIETLY
        #if MHEG5_NDT
                || u8MailBox[1] == MB_VIDEO_NDT_CHANNELCHANGE_LCN_QUIETLY
        #endif
                )
            {
                g_bQuietlyTune=TRUE;
            }

        #if MHEG5_NDT
            if (u8MailBox[1] == MB_VIDEO_NDT_CHANNELCHANGE_LCN_QUIETLY ||
                u8MailBox[1] == MB_VIDEO_NDT_CHANNELCHANGE_LCN)
            {
                msAPI_MHEG5_WaitNDTPid(true);
            }
        #endif

            //printf("MB_VIDEO_CHANNELCHANGE_LCN \n");
            // lcn: reuse the wService_ID
            wService_ID = ( (((U16)u8MailBox[2]) & 0x00FF) | ((((U16)u8MailBox[3]) << 8) & 0xFF00) );

            if (u8MailBox[1] == MB_VIDEO_CHANNELCHANGE_LCN || u8MailBox[1] == MB_VIDEO_CHANNELCHANGE_LCN_QUIETLY)
            {
                MApp_ChannelChange_ChangeSpeciChannel( wService_ID, wOriNetwork_ID, wTsID, u8MailBox[1] == MB_VIDEO_CHANNELCHANGE_LCN ? TYPE_CHANNEL_CHANGE_LCN : TYPE_CHANNEL_CHANGE_LCN_QUIETLY, bCheckTsID, TRUE);
            }
        #if MHEG5_NDT
            else if (u8MailBox[1] == MB_VIDEO_NDT_CHANNELCHANGE_LCN_QUIETLY || u8MailBox[1] == MB_VIDEO_NDT_CHANNELCHANGE_LCN)
            {
                MApp_ChannelChange_ChangeSpeciChannel( wService_ID, wOriNetwork_ID, wTsID, u8MailBox[1] == MB_VIDEO_NDT_CHANNELCHANGE_LCN ? TYPE_CHANNEL_CHANGE_LCN_NDT : TYPE_CHANNEL_CHANGE_LCN_QUIETLY_NDT, bCheckTsID, TRUE);
            }
        #endif
            break;

        case MB_VIDEO_SET_BOX_SIZE:

            //printf("MB_VIDEO_SET_BOX_SIZE\n");

            g_MHEG5Video.u8VideoFlag |= SET_VIDEO_BOX_SIZE_FLAG;

            pstMHEG5VideoAction->u16BoxSize_X = ( (((U16)u8MailBox[2]) & 0x00FF) | ((((U16)u8MailBox[3]) << 8) & 0xFF00) );
            pstMHEG5VideoAction->u16BoxSize_Y = ( (((U16)u8MailBox[4]) & 0x00FF) | ((((U16)u8MailBox[5]) << 8) & 0xFF00) );


            if ( !(g_MHEG5Video.u8VideoFlag & EVER_SET_VIDEO_BOX_SIZE) )
            {
                //printf("Set EverSetBoxSize Flag\n");
                g_MHEG5Video.u8VideoFlag |= EVER_SET_VIDEO_BOX_SIZE;
            }

            //printf("u16BoxSize_X = %04U, u16BoxSize_Y = %04U\n", pstMHEG5VideoAction->u16BoxSize_X, pstMHEG5VideoAction->u16BoxSize_Y);
            break;

        case MB_VIDEO_SET_POSITION:

            //printf("MB_VIDEO_SET_POSITION\n");

            {
                U16 u16Position_X, u16Position_Y;
                U8  u8XY_Negative;

            u16Position_X = ( (((U16)u8MailBox[2]) & 0x00FF) | ((((U16)u8MailBox[3]) << 8) & 0xFF00) );
            u16Position_Y = ( (((U16)u8MailBox[4]) & 0x00FF) | ((((U16)u8MailBox[5]) << 8) & 0xFF00) );

            u8XY_Negative = u8MailBox[6] & 0x0F;

            pstMHEG5VideoAction->s16Position_X = ( (u8XY_Negative & 0x1)?(-u16Position_X):(u16Position_X) );
            pstMHEG5VideoAction->s16Position_Y = ( (u8XY_Negative & 0x2)?(-u16Position_Y):(u16Position_Y) );
                g_MHEG5Video.u8VideoFlag |= SET_VIDEO_POSITION_FLAG;

            }
            //printf("u16Position_X = %04U, u16Position_Y = %04U\n", u16Position_X, u16Position_Y);
            //printf("s16Position_X = %04D, s16Position_Y = %04D\n", s16Position_X, s16Position_Y);

            break;

        case MB_VIDEO_SET_VIDEO_OFFSET:
            {
            //printf("MB_VIDEO_SET_VIDEO_OFFSET\n");
                U16 u16VideoOffset_X, u16VideoOffset_Y;
                U8  u8XY_Negative;

            u16VideoOffset_X = ( (((U16)u8MailBox[2]) & 0x00FF) | ((((U16)u8MailBox[3]) << 8) & 0xFF00) );
            u16VideoOffset_Y = ( (((U16)u8MailBox[4]) & 0x00FF) | ((((U16)u8MailBox[5]) << 8) & 0xFF00) );

            u8XY_Negative = u8MailBox[6] & 0x0F;

            pstMHEG5VideoAction->s16VideoOffset_X = ( (u8XY_Negative & 0x4)?(-u16VideoOffset_X):(u16VideoOffset_X) );
            pstMHEG5VideoAction->s16VideoOffset_Y = ( (u8XY_Negative & 0x8)?(-u16VideoOffset_Y):(u16VideoOffset_Y) );

            g_MHEG5Video.u8VideoFlag |= SET_VIDEO_OFFSET_FLAG;

            //printf("u8VideoFlag = 0x%02bx\n", g_MHEG5Video.u8VideoFlag);


            if ( (g_MHEG5Video.u8VideoFlag & 0x0F) == SET_VIDEO_OFFSET_FLAG )
            {
/*
                if ( (pstMHEG5VideoAction->u16Scale_Width != pstPrevMHEG5VideoAction->u16Scale_Width) ||
                     (pstMHEG5VideoAction->u16Scale_Height != pstPrevMHEG5VideoAction->u16Scale_Height) )
                {

                    MApp_Scaler_SetWindow(NULL, NULL, NULL,
                                           stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);

                    pstPrevMHEG5VideoAction->u16Scale_Width = pstMHEG5VideoAction->u16Scale_Width;
                    pstPrevMHEG5VideoAction->u16Scale_Height = pstMHEG5VideoAction->u16Scale_Height;
                }
                else
                {
                    if ( (pstMHEG5VideoAction->s16VideoOffset_X != pstPrevMHEG5VideoAction->s16VideoOffset_X) &&
                         (pstMHEG5VideoAction->s16VideoOffset_Y != pstPrevMHEG5VideoAction->s16VideoOffset_Y) )
                    {
                        if ( (g_MHEG5Video.u8PrevVideoFlag & 0x0F) == SET_VIDEO_OFFSET_FLAG )
                        {
*/
                            if ( msAPI_VID_GetVidInfo(&gstVidStatus) )
                            {
//#if (VIDEO_CROP)
                                MApp_Scaler_SetWindow(NULL, NULL, NULL,
                                           stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);//#else
                                //msAPI_MHEG5_VID_SetCapDisWin();
//#endif
                            }
/*
                            else
                            {
                                ;//printf("No VideoStatus !!!\n");
                            }
                        }
                        else
                        {
                            g_MHEG5Video.u8PrevVideoFlag = g_MHEG5Video.u8VideoFlag & 0x0F;
                        }
                    }

                    //printf("u16BoxSize_X = %04U, u16BoxSize_Y = %04U\n", pstMHEG5VideoAction->u16BoxSize_X, pstMHEG5VideoAction->u16BoxSize_Y);
                    //printf("u16Scale_Width = %04U, u16Scale_Height = %04U\n", pstMHEG5VideoAction->u16Scale_Width, pstMHEG5VideoAction->u16Scale_Height);
                    //printf("s16Position_X = %04D, s16Position_Y = %04D\n", pstMHEG5VideoAction->s16Position_X, pstMHEG5VideoAction->s16Position_Y);
                    //printf("s16VideoOffset_X = %04D, s16VideoOffset_Y = %04D\n\n", pstMHEG5VideoAction->s16VideoOffset_X, pstMHEG5VideoAction->s16VideoOffset_Y);

                }
*/
                pstPrevMHEG5VideoAction->s16VideoOffset_X = pstMHEG5VideoAction->s16VideoOffset_X;
                pstPrevMHEG5VideoAction->s16VideoOffset_Y = pstMHEG5VideoAction->s16VideoOffset_Y;

            }

            g_MHEG5Video.u8VideoFlag &= ~VIDEO_ALL_SET_FLAG;

            //printf("u16VideoOffset_X = %04U, u16VideoOffset_Y = %04U\n", pstMHEG5VideoAction->u16VideoOffset_X, pstMHEG5VideoAction->u16VideoOffset_Y);
            //printf("s16VideoOffset_X = %04D, s16VideoOffset_Y = %04D\n\n", pstMHEG5VideoAction->s16VideoOffset_X, pstMHEG5VideoAction->s16VideoOffset_Y);

            }
            break;

        case MB_VIDEO_SET_VIDEO_SCALE:

            //printf("MB_VIDEO_SET_VIDEO_SCALE\n");

            g_MHEG5Video.u8VideoFlag |= SET_VIDEO_SCALE_FLAG;

            pstMHEG5VideoAction->u16Scale_Width = ( (((U16)u8MailBox[2]) & 0x00FF) | ((((U16)u8MailBox[3]) << 8) & 0xFF00) );
            pstMHEG5VideoAction->u16Scale_Height = ( (((U16)u8MailBox[4]) & 0x00FF) | ((((U16)u8MailBox[5]) << 8) & 0xFF00) );

            //printf("u16Scale_Width = %04U, u16Scale_Height = %04U\n", pstMHEG5VideoAction->u16Scale_Width, pstMHEG5VideoAction->u16Scale_Height);
            break;

        case MB_VIDEO_DEACTIVATION:
          #if( ENABLE_PVR )
            if(MApp_TimeShift_StateMachineGet() != E_TIMESHIFT_STATE_RECORDING)
          #endif
            {
                if(g_MHEG5Video.stMHEG5VideoAction.u16Scale_Width != 0xFFFF && g_MHEG5Video.stMHEG5VideoAction.u16Scale_Height != 0xFFFF
                && g_MHEG5Video.stMHEG5VideoAction.u16BoxSize_X != 0xFFFF && g_MHEG5Video.stMHEG5VideoAction.u16BoxSize_Y != 0xFFFF
                && g_MHEG5Video.stPrevMHEG5VideoAction.u16Scale_Width != 0xFFFF && g_MHEG5Video.stPrevMHEG5VideoAction.u16Scale_Height != 0xFFFF
                && g_MHEG5Video.stPrevMHEG5VideoAction.u16BoxSize_X != 0xFFFF && g_MHEG5Video.stPrevMHEG5VideoAction.u16BoxSize_Y != 0xFFFF
                && (!g_MHEG5Video.bFullScreen && !g_MHEG5Video.bPrevFullScreen && g_MHEG5Video.bHaveVideo))
                {
                    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY,ENABLE,200, MAIN_WINDOW);
                }
            }
            break;

        case MB_VIDEO_ACTIVATION:

            //printf("MB_VIDEO_ACTIVATION\n");
            if ( MApi_XC_IsBlackVideoEnable(MAIN_WINDOW) )
            {
                // Delay 500ms to prvent showing temprary video action
                msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY, ENABLE, 500, MAIN_WINDOW);
                msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_MHEG5, DISABLE, 0, MAIN_WINDOW);
            }
            else
            {
                msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_MHEG5, DISABLE, 0, MAIN_WINDOW);
            }
            M5API_VID_Command(MSAPI_VID_PLAY);

            if(g_u16Current_VideoPID !=INVALID_PID)
                g_MHEG5Video.bHaveVideo = TRUE;
            else
                g_MHEG5Video.bHaveVideo = FALSE;
            break;

        case MB_VIDEO_SET_SCENE_AR:
            {
                if  (g_MHEG5Video.eSceneAspectRatio != u8MailBox[2])
                {
                    //BlackScreen_for_Ratio_Change = TRUE;
                    //printf("SAR from :%bu to %bu\n", g_MHEG5Video.eSceneAspectRatio, u8MailBox[2]);
                    msAPI_MHEG5_SetGraphInfoRefreshType(SENDARC_AFD_FOR_GE);
                }

                g_MHEG5Video.Pre_eSceneAspectRatio = g_MHEG5Video.eSceneAspectRatio;
                g_MHEG5Video.eSceneAspectRatio = (EN_MHEG5_SCENE_ASPECT_RATIO) u8MailBox[2];
                g_MHEG5Video.eSceneAspectRatio_FromTransitionTo = (EN_MHEG5_SCENE_ASPECT_RATIO) u8MailBox[2];
/*
                if (g_MHEG5Video.eSceneAspectRatio != SCENE_AR_None)
                {
                    //for scene 16:9 & scene 4:3
                    //printf("MB_VIDEO_SET_SCENE_AR is not 0 case 3\n");
                    msAPI_MHEG5_SetGraphInfoRefreshType(SENDARC_SCENE_RATIO_CHANGE);
                }
*/

                // clear the variable , when we chagne scene but the video is still playing.
                pstPrevMHEG5VideoAction->u16Scale_Width  = 0;
                pstPrevMHEG5VideoAction->u16Scale_Height = 0;
            }

             //printf("HK51 : MB_VIDEO_SET_SCENE_AR from %bx to %bx\n",g_MHEG5Video.Pre_eSceneAspectRatio,g_MHEG5Video.eSceneAspectRatio);

            break;

        case MB_VIDEO_RENDER:

             //printf("MB_VIDEO_RENDER\n");
            //printf("stVidStatus.u16HorSize = %04U\n", stVidStatus.u16HorSize);
            //printf("stVidStatus.u16VerSize = %04U\n", stVidStatus.u16VerSize);

            g_MHEG5Video.bVideoActionNotRdy = FALSE;

            if ( (g_MHEG5Video.bHaveVideo == FALSE) || (g_MHEG5Video.bIFrame == TRUE) ||
                 (MApp_Scramble_GetCurStatus() == TRUE) )
            {
                return;
            }

            //if ( !msAPI_VID_GetVidInfo(&stVidStatus) )
            //    printf("No VideoStatus !!!\n");

            if ( u8MailBox[11] == 0 )
            {
                 //temporal solution for blink issue, will remove later.
                ;
            }
            else if ( u8MailBox[11] == SEND_VIDEO_WSA_Centre_Cut_Out)
            {

                {

                    if (g_MHEG5Video.u8VideoFlag2 != SCENE_CCO)
                    {
                        //printf("SCENE_CCO : WAM_Change Pre FLAG %bx ",g_MHEG5Video.u8VideoFlag2);
                        //BlackScreen_for_WAM_Change = TRUE;
                    }

                    g_MHEG5Video.u8VideoFlag2 = SCENE_CCO;
                }

                //printf("MAIL BOX : --> CCO  %bx\n ",g_MHEG5Video.u8VideoFlag2);

            }
            else if ( u8MailBox[11] == SEND_VIDEO_WSA_Letterbox)
            {

                {

                    if (g_MHEG5Video.u8VideoFlag2  != SCENE_LB)
                    {
                        //printf("SCENE_LB : WAM_Change Pre FLAG %bx ",g_MHEG5Video.u8VideoFlag2);
                        //BlackScreen_for_WAM_Change = TRUE;
                    }

                    g_MHEG5Video.u8VideoFlag2 = SCENE_LB;
                }

                //printf("MAIL BOX : --> LB  %bx\n ",g_MHEG5Video.u8VideoFlag2);
            }
            else if ( u8MailBox[11] == SEND_VIDEO_WSA_NORMAL)
            {
                g_MHEG5Video.u8VideoFlag2 = SCENE_Normal;

            }
            else if ( u8MailBox[11] == (SEND_VIDEO_BOX_SIZE_FLAG | SEND_VIDEO_SCALE_FLAG | STILL_HAS_POSITION_CMD | STILL_HAS_OFFSET_CMD) )
            {
                pstMHEG5VideoAction->u16BoxSize_X = ( (((U16)u8MailBox[2]) & 0x00FF) | ((((U16)u8MailBox[3]) << 8) & 0xFF00) );
                pstMHEG5VideoAction->u16BoxSize_Y = ( (((U16)u8MailBox[4]) & 0x00FF) | ((((U16)u8MailBox[5]) << 8) & 0xFF00) );
                pstMHEG5VideoAction->u16Scale_Width = ( (((U16)u8MailBox[6]) & 0x00FF) | ((((U16)u8MailBox[7]) << 8) & 0xFF00) );
                pstMHEG5VideoAction->u16Scale_Height = ( (((U16)u8MailBox[8]) & 0x00FF) | ((((U16)u8MailBox[9]) << 8) & 0xFF00) );

                g_MHEG5Video.bVideoActionNotRdy = TRUE;

                //printf("u16BoxSize_X = %04U, u16BoxSize_Y = %04U\n", pstMHEG5VideoAction->u16BoxSize_X, pstMHEG5VideoAction->u16BoxSize_Y);
                //printf("u16Scale_Width = %04U, u16Scale_Height = %04U\n", pstMHEG5VideoAction->u16Scale_Width, pstMHEG5VideoAction->u16Scale_Height);
                //printf("Pre_u16BoxSize_X = %04U, Pre_u16BoxSize_Y = %04U\n", pstPrevMHEG5VideoAction->u16BoxSize_X, pstPrevMHEG5VideoAction->u16BoxSize_Y);
                //printf("Pre_u16Scale_Width = %04U, Pre_u16Scale_Height = %04U\n", pstPrevMHEG5VideoAction->u16Scale_Width, pstPrevMHEG5VideoAction->u16Scale_Height);
                //printf("MAIL BOX :(SEND_VIDEO_BOX_SIZE_FLAG | SEND_VIDEO_SCALE_FLAG | STILL_HAS_POSITION_CMD | STILL_HAS_OFFSET_CMD)\n ");

                return;
            }
            else
            {
                if ( u8MailBox[11] == (SEND_VIDEO_BOX_SIZE_FLAG | SEND_VIDEO_SCALE_FLAG) )
                {
                    pstMHEG5VideoAction->u16BoxSize_X = ( (((U16)u8MailBox[2]) & 0x00FF) | ((((U16)u8MailBox[3]) << 8) & 0xFF00) );
                    pstMHEG5VideoAction->u16BoxSize_Y = ( (((U16)u8MailBox[4]) & 0x00FF) | ((((U16)u8MailBox[5]) << 8) & 0xFF00) );
                    pstMHEG5VideoAction->u16Scale_Width = ( (((U16)u8MailBox[6]) & 0x00FF) | ((((U16)u8MailBox[7]) << 8) & 0xFF00) );
                    pstMHEG5VideoAction->u16Scale_Height = ( (((U16)u8MailBox[8]) & 0x00FF) | ((((U16)u8MailBox[9]) << 8) & 0xFF00) );


                    //printf("MAIL BOX :(SEND_VIDEO_BOX_SIZE_FLAG | SEND_VIDEO_SCALE_FLAG)\n ");
                    //printf("u16BoxSize_X = %04U, u16BoxSize_Y = %04U\n", pstMHEG5VideoAction->u16BoxSize_X, pstMHEG5VideoAction->u16BoxSize_Y);
                    //printf("u16Scale_Width = %04U, u16Scale_Height = %04U\n", pstMHEG5VideoAction->u16Scale_Width, pstMHEG5VideoAction->u16Scale_Height);
                    //printf("Pre_u16BoxSize_X = %04U, Pre_u16BoxSize_Y = %04U\n", pstPrevMHEG5VideoAction->u16BoxSize_X, pstPrevMHEG5VideoAction->u16BoxSize_Y);
                    //printf("Pre_u16Scale_Width = %04U, Pre_u16Scale_Height = %04U\n", pstPrevMHEG5VideoAction->u16Scale_Width, pstPrevMHEG5VideoAction->u16Scale_Height);
                }
                else if ( u8MailBox[11] == (SEND_VIDEO_POSITION_FLAG | SEND_VIDEO_OFFSET_FLAG) )
                {
                    U16 u16Position_X, u16Position_Y,u16VideoOffset_X, u16VideoOffset_Y;
                    U8 u8XY_Negative;

                    u16Position_X = ( (((U16)u8MailBox[2]) & 0x00FF) | ((((U16)u8MailBox[3]) << 8) & 0xFF00) );
                    u16Position_Y = ( (((U16)u8MailBox[4]) & 0x00FF) | ((((U16)u8MailBox[5]) << 8) & 0xFF00) );

                    u16VideoOffset_X = ( (((U16)u8MailBox[6]) & 0x00FF) | ((((U16)u8MailBox[7]) << 8) & 0xFF00) );
                    u16VideoOffset_Y = ( (((U16)u8MailBox[8]) & 0x00FF) | ((((U16)u8MailBox[9]) << 8) & 0xFF00) );

                    u8XY_Negative = u8MailBox[10] & 0x0F;
                    g_MHEG5Video.u8ARC_Control = u8MailBox[10] & (SETARC | SETARC_ADJ_H | SETARC_ADJ_V);

                    pstMHEG5VideoAction->s16Position_X = ( (u8XY_Negative & 0x1)?(-u16Position_X):(u16Position_X) );
                    pstMHEG5VideoAction->s16Position_Y = ( (u8XY_Negative & 0x2)?(-u16Position_Y):(u16Position_Y) );
                    pstMHEG5VideoAction->s16VideoOffset_X = ( (u8XY_Negative & 0x4)?(-u16VideoOffset_X):(u16VideoOffset_X) );
                    pstMHEG5VideoAction->s16VideoOffset_Y = ( (u8XY_Negative & 0x8)?(-u16VideoOffset_Y):(u16VideoOffset_Y) );

                    //printf("u16Position_X =         %04U, u16Position_Y =           %04U\n", u16Position_X, u16Position_Y);
                    //printf("s16Position_X =         %04D, s16Position_Y =           %04D\n", pstMHEG5VideoAction->s16Position_X, pstMHEG5VideoAction->s16Position_Y);
                    //printf("u16VideoOffset_X =      %04U, u16VideoOffset_Y =        %04U\n", u16VideoOffset_X, u16VideoOffset_Y);
                    //printf("s16VideoOffset_X =      %04D, s16VideoOffset_Y =        %04D\n", pstMHEG5VideoAction->s16VideoOffset_X, pstMHEG5VideoAction->s16VideoOffset_Y);
                    //printf("MAIL BOX :(SEND_VIDEO_POSITION_FLAG | SEND_VIDEO_OFFSET_FLAG)\n ");
                }

                if ( msAPI_MHEG5_VID_IsSameVideoAction(&g_MHEG5Video.stMHEG5VideoAction,&g_MHEG5Video.stPrevMHEG5VideoAction) == TRUE )
                {
                    if (( !(g_MHEG5Video.u8VideoFlag & EVER_SET_VIDEO_STREAM) )
                        && (!(g_MHEG5Video.u8ARC_Control ))
                        && (g_MHEG5Video.u8VideoFlag2 == SCENE_Normal)
                        && (g_MHEG5Video.eSceneAspectRatio == SCENE_AR_None))
                    {
                            //printf("MB RETURN:  DO NOTHING\n");
                            return;
                    }
                }

                if((fTVSetModeDone == TRUE) || (g_MHEG5Video.bRecodeMVDDONE == TRUE))
                {
                    g_MHEG5Video.u8VideoFlag &= ~(EVER_SET_VIDEO_STREAM | EVER_SET_VIDEO_BOX_SIZE);
                }

                if (g_MHEG5Video.u8VideoFlag & EVER_SET_VIDEO_STREAM )//video not ready,do in MApp_MVD_SetMode()
                {
                    return;
                }

                if(g_MHEG5Video.bPrevFullScreen != msAPI_MHEG5_VID_IsFullScreen(&g_MHEG5Video.stMHEG5VideoAction))
                {
                     if(msAPI_MHEG5_VID_IsFullScreen(&g_MHEG5Video.stMHEG5VideoAction) == FALSE)
                    {
                        msAPI_MHEG5_SetGraphInfoRefreshType(SENDARC_AFD_FOR_GE);
                    }
                    msAPI_Scaler_SetScreenMute(E_SCREEN_MUTE_TEMPORARY,ENABLE,200, MAIN_WINDOW);
                }
                // if video is frozen, un-freeze it before scaling. and freeze it again after scaling
                if (g_bIsImageFrozen)
                {
                    MApi_XC_FreezeImg(false, MAIN_WINDOW);
                }

                MApp_Scaler_SetWindow(NULL, NULL, NULL,
                                           stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);

                // if video is frozen, un-freeze it before scaling. and freeze it again after scaling
                if (g_bIsImageFrozen)
                {
                    msAPI_Timer_Delayms(100);   // need to delay ms to let video shown correctly
                    MApi_XC_FreezeImg(true, MAIN_WINDOW);
                }

                g_MHEG5Video.u8VideoFlag &= ~VIDEO_ALL_SET_FLAG;
                g_MHEG5Video.u8ARC_Control = 0;

                // Move to msAPI_MHEG5_VID_SetWindowInfo
                //g_MHEG5Video.stPrevMHEG5VideoAction = g_MHEG5Video.stMHEG5VideoAction;
                //g_MHEG5Video.bPrevFullScreen = g_MHEG5Video.bFullScreen;
                g_MHEG5Video.u8PrevVideoFlag = 0;

                //printf("Prev u16BoxSize_X = %04U, Prev u16BoxSize_Y = %04U\n", pstPrevMHEG5VideoAction->u16BoxSize_X, pstPrevMHEG5VideoAction->u16BoxSize_Y);
                //printf("Prev u16Scale_Width = %04U, Prev u16Scale_Height = %04U\n", pstPrevMHEG5VideoAction->u16Scale_Width, pstPrevMHEG5VideoAction->u16Scale_Height);

            }

            break;

        default:
            break;
    }
}
#if INTERACTION_CHANNEL
/******************************************************************************/
/// @internal
///- API for process channel mailbox msg from Aeon
/// @param *u8MailBox \b IN: pointer to mail box
/******************************************************************************/
void MApp_MHEG5_ICProcessMailbox(U8 type, U8 item)
{
    U16 NetInitStatus;
    //GOP_GwinFBAttr fbAttr;

    printf("=========MApp_MHEG5_ICProcessMailbox========\n");

    if(type == 1)
    {
        unsigned char *ICStr;
        ICStr = (unsigned char *)_PA2VA(0x0003F10000);
        //MApi_GOP_GWIN_GetFBInfo(u8MHEG5_DLA_FBID, &fbAttr);
        msAPI_MHEG5_SendICAddr((U32)ICStr);

    }
    else if(type == 2)
    {
        unsigned char *ICStr, *FullICStr;
        ICStr = (unsigned char *)_PA2VA(0x0003F10000);
        FullICStr = (unsigned char *)_PA2VA(0x0003F30000);
        //printf("StrAddr : %s\n",ICStr);
        NetInitStatus = MApp_MHEG5_Init_Net(ICStr, FullICStr, item);

        printf("Get NetInitStatus : %d\n",NetInitStatus);

        msAPI_MHEG5_SendICStatus(NetInitStatus);
    }
    else if(type == 3)
    {
        unsigned char *TsSource;
        unsigned int *TsSize;
        TsSource = (unsigned char *)_PA2VA(0x0003F50000);
        TsSize = (unsigned int *)_PA2VA(0x0003F40000);
        printf("Get ICS Mail\n");
        MApp_MHEG5_ProcessICS(TsSource, TsSize);

        //msAPI_MHEG5_SendICStatus(NetInitStatus);
    }
    printf("Send mail!\n");
}

#endif
#if(MHEG5_SIINFO_ENABLE)
void U16CpyToBuf(U8 *pBuf, U16* array, int len)
{
    int i=0;
    for(i=0;i<len;i++)
    {
        *(pBuf++)=(U8)((array[i]>>8)&0xFF);
        *(pBuf++)=(U8)((array[i]   )&0xFF);
    }
}
void U32CpyToBuf(U8 *pBuf, U32* array, int len)
{
    int i=0;
    for(i=0;i<len;i++)
    {
        *(pBuf++)=(U8)((array[i]>>24)&0xFF);
        *(pBuf++)=(U8)((array[i]>>16)&0xFF);
        *(pBuf++)=(U8)((array[i]>>8)&0xFF);
        *(pBuf++)=(U8)((array[i]   )&0xFF);
    }
}
#endif
/******************************************************************************/
/// @internal
///- API for process channel mailbox msg from Aeon
/// @param *u8MailBox \b IN: pointer to mail box
/******************************************************************************/
void MApp_MHEG5_ChannelProcessMailbox(U8 *u8MailBox)
{
    switch (u8MailBox[1])
    {
        case MB_SERVICE_CHECK_IF_EXIST:
            {
                U16 u16InputValue = 0;
                U16 u16InputValue2 = 0;
                U16 u16InputValue3 = 0;
                BOOL bResult = 0;
                U16 u16TsID = 0;
                U16 u16OnID = 0;
                 U8 u8IsValid = 0;
                U16 u16ServiceID= 0;

                u16InputValue = ( (((U16)u8MailBox[4]) & 0x00FF) | ((((U16)u8MailBox[3]) << 8) & 0xFF00) );
                u16InputValue2 = ( (((U16)u8MailBox[6]) & 0x00FF) | ((((U16)u8MailBox[5]) << 8) & 0xFF00) );
                u16InputValue3 = ( (((U16)u8MailBox[8]) & 0x00FF) | ((((U16)u8MailBox[7]) << 8) & 0xFF00) );
                bResult = msAPI_MHEG5_ServiceValidChecking((MB_SERVICE_CMD) u8MailBox[2], u16InputValue, u16InputValue2, u16InputValue3, &u16ServiceID, &u16OnID, &u16TsID, &u8IsValid);

                //printf("check service ready %bu\n", bResult);

                // send result to MHEG engine
                msAPI_MHEG5_SendChannelInfo((bResult ? MB_SERVICE_EXIST : MB_SERVICE_NOT_EXIST),u16ServiceID,u16OnID,u16TsID,u8IsValid);
            }
            break;
#if(MHEG5_SIINFO_ENABLE)
        case MB_SERVICE_SI_GET_SERVICE_INFO:
            {
                U32 addr=0,len;
                BOOL bResult = 0;
                U16 u16TsID = 0,u16OnID=0,u16SvcID=0;
                int databuflen=0,index;
                U8 *pbuf,*databuf;
                MS_SI_SERVICEINFO svc_info;
                memset(&svc_info,0,sizeof(svc_info));
                addr=u8MailBox[2];
                addr = (addr<<8)+u8MailBox[3];
                addr = (addr<<8)+u8MailBox[4];
                addr = (addr<<8)+u8MailBox[5];
                len=u8MailBox[6];
                len = (addr<<8)+u8MailBox[7];
                len = (addr<<8)+u8MailBox[8];
                len = (addr<<8)+u8MailBox[9];
                pbuf=PA2KSEG1(addr);
                databuf=pbuf;
                databuflen=len;
                u16OnID = ( (((U16)databuf[1]) & 0x00FF) | ((((U16)databuf[0]) << 8) & 0xFF00) );
                u16TsID = ( (((U16)databuf[3]) & 0x00FF) | ((((U16)databuf[2]) << 8) & 0xFF00) );
                u16SvcID = ( (((U16)databuf[5]) & 0x00FF) | ((((U16)databuf[4]) << 8) & 0xFF00) );
                bResult=msAPI_CM_GetServiceInfo(u16TsID,u16OnID,u16SvcID,&svc_info);
                index=0;
                if(bResult)
                {
                    int tmplen;
                    if(databuflen>0)
                        databuf[index++]=svc_info.u8ServiceType;
                    tmplen=strlen(svc_info.bServiceName);
                    tmplen=((databuflen-index)>tmplen)?tmplen:(databuflen-index-1);
                    if(tmplen>0)
                    {
                        databuf[index++]=(U8)tmplen;
                        memcpy(databuf+index,svc_info.bServiceName,tmplen);
                        index += tmplen;

                        tmplen=strlen(svc_info.bProviderName);
                        tmplen=((databuflen-index)>tmplen)?tmplen:(databuflen-index-1);
                        if(tmplen>0)
                        {
                            databuf[index++]=(U8)tmplen;
                            memcpy(databuf+index,svc_info.bProviderName,tmplen);
                            index += tmplen;
                        }
                    }
                }
                // send result to MHEG engine
                msAPI_MHEG5_SendChannelInfo((bResult ? MB_SERVICE_SI_GET_SERVICE_INFO_OK : MB_SERVICE_SI_GET_SERVICE_INFO_FAIL),index,0,0,0);
            }
            break;
        case MB_SERVICE_SI_GET_EVENT_INFO:
            {
                U32 addr=0,len;
                BOOL bResult = 0;
                U16 u16TsID = 0,u16OnID=0,u16SvcID=0;
                int databuflen=0,index;
                U8 *pbuf,*databuf;
                int porf=0;
                MW_EN_EPG_PF_STATUS pf=MW_EN_EPG_PRESENT_STATUS;
                MW_MHEG5_GET_EPG_EVENT_INFO event_info;
                memset(&event_info,0,sizeof(event_info));
                addr=u8MailBox[2];
                addr = (addr<<8)+u8MailBox[3];
                addr = (addr<<8)+u8MailBox[4];
                addr = (addr<<8)+u8MailBox[5];
                len=u8MailBox[6];
                len = (addr<<8)+u8MailBox[7];
                len = (addr<<8)+u8MailBox[8];
                len = (addr<<8)+u8MailBox[9];
                pbuf=PA2KSEG1(addr);
                databuf=pbuf;
                databuflen=len;
                u16OnID = ( (((U16)databuf[1]) & 0x00FF) | ((((U16)databuf[0]) << 8) & 0xFF00) );
                u16TsID = ( (((U16)databuf[3]) & 0x00FF) | ((((U16)databuf[2]) << 8) & 0xFF00) );
                u16SvcID = ( (((U16)databuf[5]) & 0x00FF) | ((((U16)databuf[4]) << 8) & 0xFF00) );
                porf=(U8)(databuf[6]);
                if(porf==0)pf=MW_EN_EPG_PRESENT_STATUS;
                else pf=MW_EN_EPG_FOLLOW_STATUS;
                bResult=MApp_EPG_GetEventInfo(u16TsID,u16OnID,u16SvcID,pf,&event_info);
                index=0;
                if(bResult)
                {
                    if(len>=(1+sizeof(U16)*EPG_TIMER_MAX_EVENT_NAME_LEN
                             +sizeof(U16)*MW_MAX_SHORT_EVENT_DESCRIPTOR_LEN
                             +sizeof(U32)*3
                             +4)
                      )
                    {
                        databuf[index++]=event_info.u8ParentalRating;
                        U16CpyToBuf(&databuf[index],event_info.u16EventName,EPG_TIMER_MAX_EVENT_NAME_LEN);
                        index+=sizeof(U16)*EPG_TIMER_MAX_EVENT_NAME_LEN;
                        U16CpyToBuf(&databuf[index],event_info.u16ShortDescriptionData,MW_MAX_SHORT_EVENT_DESCRIPTOR_LEN);
                        index+=sizeof(U16)*MW_MAX_SHORT_EVENT_DESCRIPTOR_LEN;
                        U32CpyToBuf(&databuf[index],&event_info.stEventTimeDate.u32StartDateInMJD,1);
                        index+=sizeof(U32);
                        U32CpyToBuf(&databuf[index],&event_info.stEventTimeDate.u32StartTimeInUTC,1);
                        index+=sizeof(U32);
                        U32CpyToBuf(&databuf[index],&event_info.stEventTimeDate.u32Duration,1);
                        index+=sizeof(U32);
                        databuf[index++]=event_info.stNibblePfCa.u8Content_nibble_level1;
                        databuf[index++]=event_info.stNibblePfCa.u8Content_nibble_level2;
                        databuf[index++]=event_info.stNibblePfCa.u8PFType;
                        databuf[index++]=event_info.stNibblePfCa.u8FreeNotCA;
                    }
                }
                // send result to MHEG engine
                msAPI_MHEG5_SendChannelInfo((bResult ? MB_SERVICE_SI_GET_EVENT_INFO_OK : MB_SERVICE_SI_GET_EVENT_INFO_FAIL),index,0,0,0);
            }
            break;
#endif
        default:
            break;
    }
}

#if (CIPLUS_MHEG && ENABLE_CI_PLUS)
/******************************************************************************/
/// @internal
///- API for process CIMHEG mailbox msg from Aeon
/// @param *u8MailBox \b IN: pointer to mail box
/******************************************************************************/
static void MApp_MHEG5_CIMHEGProcessMailBox(U8 *u8MailBox)
{
    switch (u8MailBox[1])
    {
        case MB_CI_CMD_MHEGCI_FILE_EXISTENCE_CHECK:
            {
                U32 u32DataLen = 0;
                U32 u32BufferAddr = msAPI_MHEG5_GetDLAFBAddress();


                U8 *myptr = (U8*)_PA2VA(u32BufferAddr);
                u32DataLen = (U32) myptr[0] << 24 | (U32)myptr[1] << 16 | (U32)myptr[2] << 8 | (U32)myptr[3];
            #if CIMHEG_DBG
                printf("dd2 %d\n", u32DataLen);
            #endif


            #ifdef GOP_GWIN_RB2_ADR
                // copy length and data - need to consider MIU 0/1 when MIU copy
                if (GOP_GWIN_RB2_MEMORY_TYPE & MIU1)
                {
                    if (MMI_TEXTSTRING_MEMORY_TYPE & MIU1)  // 1 -> 1
                    {
                        msAPI_MIU_Copy(u32BufferAddr, (MMI_TEXTSTRING_ADR | MIU_INTERVAL)+0x800, u32DataLen+4, MIU_SDRAM12SDRAM1);
                    }
                    else    // 1 -> 0
                    {
                        msAPI_MIU_Copy(u32BufferAddr, MMI_TEXTSTRING_ADR+0x800, u32DataLen+4, MIU_SDRAM12SDRAM0);
                    }
                }
                else
            #endif
                {
                    #if (MMI_TEXTSTRING_MEMORY_TYPE & MIU1)  // 0->1
                    {
                        msAPI_MIU_Copy(u32BufferAddr, (MMI_TEXTSTRING_ADR | MIU_INTERVAL)+0x800, u32DataLen+4, MIU_SDRAM02SDRAM1);
                    }
                    #else    // 0->0
                    {
                        msAPI_MIU_Copy( u32BufferAddr, MMI_TEXTSTRING_ADR+0x800, u32DataLen+4, MIU_SDRAM2SDRAM);
                    }
                    #endif
                }

                {
                    U8 *pu8AppMmi = msAPI_CI_AppMmiGetBufPtr();
                    if (pu8AppMmi != NULL)
                    {
                        msAPI_CI_AppMmi_FileInquire(&pu8AppMmi[sizeof(U32)], (U8)u32DataLen, EN_APPMMI_REQTYPE_FILE);
                    }
                }

            }
            break;

    #if CIPLUS_MHEG_1_3
        case MB_CI_CMD_MHEGCI_SMG:              //  suppress MHEG graphics
            msAPI_MHEG5_SetCIPLUSSMG(u8MailBox[2]);
            break;
    #endif

        case MB_CI_CMD_MHEGCI_FILEREQUEST:      // file mode
        case MB_CI_CMD_MHEGCI_SENDMESSAGE:      // data mode
            {
                U32 u32DataLen = 0;
                U32 u32BufferAddr = msAPI_MHEG5_GetDLAFBAddress();
            #if CIMHEG_DBG
                printf("mheg engine sends me cimheg file request -- ");

                if (u8MailBox[1] == MB_CI_CMD_MHEGCI_FILEREQUEST)
                {
                    printf("file mode\n");
                }
                else
                {
                    printf("data mode\n");
                }
            #endif

                U8 *myptr = (U8*)_PA2VA(u32BufferAddr);
                u32DataLen = (U32) myptr[0] << 24 | (U32)myptr[1] << 16 | (U32)myptr[2] << 8 | (U32)myptr[3];
            #if CIMHEG_DBG
                printf("dd2 %d\n", u32DataLen);
            #endif
            #if 0//CIMHEG_DBG
                printf("request file data len: %LX\n", u32DataLen);
                {
                    char testdata[50];
                    int i;
                    msAPI_MIU_Copy(u32BufferAddr, (U16)&testdata[0]-XDATASDRAM_START_ADDR, 50, MIU_SDRAM2SDRAM);

                    printf("data: ");
                    for (i=4; i<u32DataLen+4; i++)
                    {
                        printf("%02bX ", testdata[i]);
                    }
                    printf("\n");
                }
            #endif

            #ifdef GOP_GWIN_RB2_ADR
                // copy length and data - need to consider MIU 0/1 when MIU copy
                if (GOP_GWIN_RB2_MEMORY_TYPE & MIU1)
                {
                    if (MMI_TEXTSTRING_MEMORY_TYPE & MIU1)  // 1 -> 1
                    {
                        msAPI_MIU_Copy(u32BufferAddr, (MMI_TEXTSTRING_ADR | MIU_INTERVAL)+0x800, u32DataLen+4, MIU_SDRAM12SDRAM1);
                    }
                    else    // 1 -> 0
                    {
                        msAPI_MIU_Copy(u32BufferAddr, MMI_TEXTSTRING_ADR+0x800, u32DataLen+4, MIU_SDRAM12SDRAM0);
                    }
                }
                else
            #endif
                {
                    #if (MMI_TEXTSTRING_MEMORY_TYPE & MIU1)  // 0->1
                    {
                        msAPI_MIU_Copy(u32BufferAddr, (MMI_TEXTSTRING_ADR | MIU_INTERVAL)+0x800, u32DataLen+4, MIU_SDRAM02SDRAM1);
                    }
                    #else    // 0->0
                    {
                        msAPI_MIU_Copy( u32BufferAddr, MMI_TEXTSTRING_ADR+0x800, u32DataLen+4, MIU_SDRAM2SDRAM);
                    }
                    #endif
                }

                {
                    U8 *pu8AppMmi = msAPI_CI_AppMmiGetBufPtr();
                    if (pu8AppMmi != NULL)
                    {
                        if (u8MailBox[1] == MB_CI_CMD_MHEGCI_FILEREQUEST)
                        {
                            msAPI_CI_AppMmi_FileReq(&pu8AppMmi[sizeof(U32)], (U8)u32DataLen, EN_APPMMI_REQTYPE_FILE);
                        }
                        else if (u8MailBox[1] == MB_CI_CMD_MHEGCI_SENDMESSAGE)
                        {
                            msAPI_CI_AppMmi_FileReq(&pu8AppMmi[sizeof(U32)], (U8)u32DataLen, EN_APPMMI_REQTYPE_DATA);
                        }
                    }
                }
            #if 0//CIMHEG_DBG
                {
                    char testdata[50];
                    int i;
                    msAPI_MIU_Copy(MMI_TEXTSTRING_ADR+0x800, (U16)&testdata[0]-XDATASDRAM_START_ADDR, 50, MIU_SDRAM2SDRAM);

                    printf("data: ");
                    for (i=4; i<u32DataLen+4; i++)
                    {
                        printf("%02bX ", testdata[i]);
                    }
                    printf("\n");
                }
            #endif
            }
            break;
        case MB_CI_CMD_MHEGCI_SENDEXITMESSAGE:  // CIMHEG "quit"
            MApp_MHEG5_Force_Exit();
            msAPI_MHEG5_SetGoBackMHEG5(false);
            break;
        default:
            break;
    }
}

#endif


#endif

#undef _MAPP_MHEG5_MAIN_C_

