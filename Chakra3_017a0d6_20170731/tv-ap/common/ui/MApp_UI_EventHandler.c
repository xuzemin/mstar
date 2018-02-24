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

#include "Board.h"

#include "MApp_GlobalFunction.h"
#include "MApp_GlobalVar.h"

#include "MApp_Sleep.h"

#if (ENABLE_PIP)
#include "MApp_PIP.h"
#endif

#include "MApp_UI_EventHandler.h"

#include "MApp_ZUI_Main.h"
#include "ZUI_tables_h.inl"
#include "ZUI_exefunc.h"




#define DEBUG_UI_NOTIFY(x)  //x

void MApp_UI_NotifySysEvent(EnuSysEvent enSysEvent, void* pPara)
{
    SCALER_WIN enScalerWin = MAIN_WINDOW;
    INPUT_SOURCE_TYPE_t enInputSrc_Main = SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW);

    pPara=pPara;

    if( enSysEvent >= E_SYS_EVENT_NUMS )
    {
        printf("\nError: enSysEvent=%u is invalid!\n", enSysEvent);
        return ;
    }


    switch(enSysEvent)
    {
        default:
            break;

        case E_SYS_EVENT_PC_MODE_CHANGE_START:  //
        #if 0  //for mantis 918086
            DEBUG_UI_NOTIFY( printf("[E_SYS_EVENT_PC_MODE_CHANGE_START]\n"); );
            #if (ENABLE_PIP)
             if(MApp_Get_PIPMode() == EN_PIP_MODE_OFF)
            #endif
             {
                 if ((MApp_ZUI_GetActiveOSD() != E_OSD_EMPTY) && (MApp_ZUI_GetActiveOSD() != E_OSD_FACTORY_MENU))
                 {
                     MApp_ZUI_ACT_ShutdownOSD();
                 }
             }
        #endif

            break;
        case E_SYS_EVENT_VD_SET_MODE_DONE:
            DEBUG_UI_NOTIFY( printf("[E_SYS_EVENT_VD_MODE_CHANGED]\n"); );

            if( MApp_IsSrcHasSignal(enScalerWin) )
            {
                if( IsSrcTypeATV(enInputSrc_Main) )
                {

                }
                else
                {
                    if( MApp_ZUI_GetActive_ChannelInfo_OSD() )
                    {
                        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_SOURCE_BANNER);
                    }
                    else if( MApp_ZUI_GetActiveOSD()== E_OSD_EMPTY )
                    {
                        MApp_ZUI_ACT_Startup_ChannelInfo_OSD();
                        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_SOURCE_BANNER);
                    }
                }
            }
            break;

        case E_SYS_EVENT_PC_AUTO_TUNE_START:
            DEBUG_UI_NOTIFY( printf("[E_SYS_EVENT_PC_AUTO_TUNE_START]\n"); );

        #if (ENABLE_PIP)
             if( MApp_Get_PIPMode() == EN_PIP_MODE_OFF )
        #endif
             {
                 MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                 MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_AUTO_ADJUSTING_MSGBOX);
                 // MApp_PCMode_RunSelfAuto(eWindow);
             }
            break;

        case E_SYS_EVENT_PC_YPBPR_HDMI_SET_MODE_DONE:
            DEBUG_UI_NOTIFY( printf("[E_SYS_EVENT_PC_YPBPR_HDMI_SET_MODE_DONE]\n"); );
    #if ENABLE_DMP
        #if (ENABLE_PIP)
            if(!IsStorageInUse())
        #endif
    #endif
            {
                if( MApp_ZUI_GetActive_ChannelInfo_OSD() )
                {
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_SOURCE_BANNER);
                }
                else if(MApp_ZUI_GetActiveOSD()==E_OSD_EMPTY)
                {
                    MApp_ZUI_ACT_Startup_ChannelInfo_OSD();
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_SOURCE_BANNER);
                }
            }
            break;

        case E_SYS_EVENT_HDMI_AVMUTE_1_TO_0:
            DEBUG_UI_NOTIFY( printf("[E_SYS_EVENT_HDMI_AVMUTE_1_TO_0]\n"); );
        #if ENABLE_DMP
          #if (ENABLE_PIP)
            if( !IsStorageInUse( ))
          #endif
        #endif
            {
                if(MApp_ZUI_GetActive_ChannelInfo_OSD())
                {
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_SOURCE_BANNER);
                }
                else if(MApp_ZUI_GetActiveOSD()==E_OSD_EMPTY)
                {
                    MApp_ZUI_ACT_Startup_ChannelInfo_OSD();
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_SOURCE_BANNER);
                }
            }
            break;

    #if (NO_SIGNAL_AUTO_SHUTDOWN )
        case E_SYS_EVENT_NO_SIGNAL_AUTO_SLEEP_COUNT_DOWN_1_MIN:
            DEBUG_UI_NOTIFY( printf("[E_SYS_EVENT_NO_SIGNAL_AUTO_SLEEP_COUNT_DOWN_1_MIN]\n"); );
            //printf("todo: UI need draw count down time\n");
            if( u8KeyCode != KEY_NULL )
            {
                //MApp_NoSignalAutoSleep_Reset_StartTime();
                //u8KeyCode = KEY_NULL;
                enIndicateTimerSource = TS_TYPE_NONE;
                MApp_ZUI_ACT_ShutdownOSD();
            }
            else
            {
                if( MApp_ZUI_GetActiveOSD() != E_OSD_MESSAGE_BOX )
                {
                    if( MApp_ZUI_GetActiveOSD() != E_OSD_EMPTY )
                    {
                        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
                    }
                    enIndicateTimerSource = TS_TYPE_SLEEPTIMER_NOSIGNAL;
                    MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_POWER_OFF_COUNTDOWN_MSG_BOX);
                }
            }
            break;
    #endif

        case E_SYS_EVENT_DECOMP_BIN_USE_GOP_BUF:
            DEBUG_UI_NOTIFY( printf("[E_SYS_EVENT_DECOMP_BIN_USE_GOP_BUF]\n"); );

            // Close ZUI...
            DEBUG_UI_NOTIFY( printf("Close ZUI for decomp\n"); );
            MApp_ZUI_ACT_ShutdownOSD();
            break;

        case E_SYS_EVENT_SIGNAL_DETECT_CLOSEWBX:
            DEBUG_UI_NOTIFY( printf("[E_SYS_EVENT_SIGNAL_DETECT_CLOSEWBX]\n"); );

            // Close no-signal time out MBX ZUI...
            DEBUG_UI_NOTIFY( printf("Close WARNNING MBX ZUI window\n"); );

            if( (MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_QUERY_IS_POWER_OFF_COUNTDOWN_MSG_BOX)) && (TS_TYPE_SLEEPTIMER_NOSIGNAL == enIndicateTimerSource) )
            {
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
            }
            break;

        case E_SYS_EVENT_NO_OPERATE_AUTO_SLEEP_COUNT_DOWN_5_MIN:
            if (MApp_ZUI_GetActiveOSD() != E_OSD_MESSAGE_BOX ||
            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_QUERY_IS_POWER_OFF_COUNTDOWN_MSG_BOX) == FALSE)
            {

                if (MApp_ZUI_GetActiveOSD()!=E_OSD_EMPTY)
                {
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_CLOSE_CURRENT_OSD);
                }
                enIndicateTimerSource = TS_TYPE_AUTOSLEEP_OFFTIMER;
                MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_SHOW_POWER_OFF_COUNTDOWN_MSG_BOX);
            }
            break;

    }

}


