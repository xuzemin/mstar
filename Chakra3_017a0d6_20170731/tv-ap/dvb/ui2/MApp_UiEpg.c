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

#define MAPP_EPG_MAIN_C

/******************************************************************************/
/*                 Header Files                                               */
/* ****************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "MsCommon.h"


#include "msAPI_Timer.h"

#include "MApp_Exit.h"
#include "MApp_UiEpg.h"


#include "apiXC.h"
#include "apiXC_Adc.h"
#include "MApp_GlobalSettingSt.h"

#include "MApp_Key.h"
#include "MApp_UiMenuDef.h"
#include "MApp_ZUI_Main.h"
#include "ZUI_tables_h.inl"
#include "MApp_UiEpg.h"

#include "ZUI_exefunc.h"
#include "MApp_EpgTimer.h"
#include "MApp_UiPvr.h"




//#if (ENABLE_PIP)
#if (ENABLE_ATSC)
#if ENABLE_ATSC_EPG_UI
extern BOOLEAN MApp_ZUI_ACT_ExecuteEpgAction_ATSC(U16 act);
#endif
#endif
extern BOOLEAN MApp_ZUI_ACT_ExecuteMenuItemAction(U16 act);
#if (ENABLE_EPG_MUX)
extern void MApp_BarkerEPG_Exit(void);
#endif
//#endif
///////////////////////////////////////////////////////////
#if ENABLE_AUTOTEST
extern BOOLEAN g_bAutobuildDebug;
#endif
extern DWORD        m_dwEPGManualTimerMonitorTimer;
extern U32 u32LatestManualTimerStartDate;
extern U8           m_u8EpgNextStartUpIdx;
extern DWORD        m_u32EpgNextStartUpTime;
extern EN_EPG_TIMER_ACT_TYPE _TimerActType;

EN_EPG_MODE _eEpgMode;


#if (ENABLE_ATSC && ENABLE_ATSC_EPG_UI)
    #define ENABLE_EPG_REDRAW_BY_TIMER  0 // No need redraw EPG page!!
#else
    #define ENABLE_EPG_REDRAW_BY_TIMER  0
#endif

#if(ENABLE_EPG_REDRAW_BY_TIMER)
static U32 s_u32ThisEPG_SystemTimeUpdate;
#endif
//////////////////////////////////////////////////////////

EN_RET MApp_Epg_Main(void)
{
    EN_RET enRetVal =EXIT_NULL;

    switch(enEpgState)
    {
        case STATE_EPG_INIT:
            //printf("STATE_EPG_INIT:\n");

          #if ENABLE_AUTOTEST
            if(g_bAutobuildDebug)
            {
                printf("101_EPGGuide\n");
            }
          #endif

            MApp_ZUI_ACT_StartupOSD(E_OSD_EPG);

#if (ENABLE_ATSC)
        #if ENABLE_ATSC_EPG_UI
            if( IsAtscInUse() )
            {
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_EPG_SHOW_PROGRAMMEGUIDE_EVENT_PAGE);
            }
            else
        #endif
#endif
            {
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_EPG_SHOW_PROGRAMMEGUIDE_TIME_PAGE);
            }
            enEpgState = STATE_EPG_WAIT;
            break;

        case STATE_EPG_WAIT:

        #if(ENABLE_EPG_REDRAW_BY_TIMER)
            if( IsAtscInUse() )
            {
                if (msAPI_Timer_DiffTimeFromNow(s_u32ThisEPG_SystemTimeUpdate)> EPGUI_SYSTEMTIME_UPATE_PERIOD)
                {
                    MApp_ZUI_ACT_ExecuteEpgAction_ATSC(EN_EXE_EPG_SHOW_INFO_ATSC);
                    s_u32ThisEPG_SystemTimeUpdate = msAPI_Timer_GetTime0();
                }
            }
        #endif

            MApp_ZUI_ProcessKey(u8KeyCode);
            u8KeyCode = KEY_NULL;
            break;

        //case STATE_EPG_EPGTIMER_WAIT:
            //MApp_UiMenu_EPGTimer_ProcessUserInput();
            //break;

        case STATE_EPG_CLEAN_UP:
#if (ENABLE_ATSC)
        #if ENABLE_ATSC_EPG_UI
            if( IsAtscInUse() )
            {
            }
            else
        #endif
#endif
            {
		#if (ENABLE_EPG_MUX)
			MApp_BarkerEPG_Exit();
		#endif
            }

            printf("shut down OSD\n");
            MApp_ZUI_ACT_ShutdownOSD();
            enEpgState = STATE_EPG_INIT;
            enRetVal =EXIT_CLOSE;
            break;

        case STATE_EPG_GOTO_STANDBY:
            MApp_ZUI_ACT_ShutdownOSD();
            u8KeyCode = KEY_POWER;
            enRetVal =EXIT_GOTO_STANDBY;
            break;

    #if (ENABLE_PIP)
        case STATE_EPG_GOTO_PIP:
            if(IsPIPSupported())
            {
                MApp_ZUI_ACT_ShutdownOSD();
                enEpgState = STATE_EPG_ENABLE_PIP;
            }
            break;
        case STATE_EPG_ENABLE_PIP:
            if(IsPIPSupported())
            {
                MApp_ZUI_ACT_ExecuteMenuItemAction(EN_EXE_INC_PIPMODE);
                enEpgState = STATE_EPG_INIT;
                enRetVal =EXIT_CLOSE;
            }
            break;
    #endif

        default:
            enEpgState = STATE_EPG_WAIT;
            break;
    }
    return enRetVal;
}


#undef MAPP_EPG_MAIN_C

