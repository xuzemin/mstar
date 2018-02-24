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

#define MAPP_DMP_MINIMENU_MAIN_C
#if ENABLE_DMP
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
#if ENABLE_DMP_MINI_MENU
#include "MApp_DMP_MiniMenu_Main.h"

static EN_DMP_MINIMENU_STATE enDmpMiniMenuState;

///////////////////////////////////////////////////////////
#define DMP_WAITCONNECT_MS      3000
#define DMP_PR(x)               //x
//static ST_DMP_VAR     m_enDmpVar;

extern void MApp_DMP_NotifyUiState(EN_DMP_UI_STATE enDmpUiState);
extern BOOLEAN MApp_UiMediaPlayer_IsSubtitleEnabled(void);
BOOLEAN MApp_DMP_GotoDMP_FileSelect(void)
{
    //printf("m_enDmpVar.enDmpState = DMP_STATE_GOTO_MENU;\n");
    enDmpMiniMenuState = STATE_DMP_MINIMENU_GOTO_DMP;
    MApp_DMP_SetDMPStat(DMP_STATE_INIT);
    MApp_DMP_SetDmpUiState(DMP_UI_STATE_FILE_SELECT);
    return TRUE;
}

EN_RET MApp_DMP_MiniMenu_Main(void)
{
    EN_RET enRetVal =EXIT_NULL;
    static EN_DMP_MINIMENU_STATE eLastDmpState = STATE_DMP_MINIMENU_INIT;


    if( enDmpMiniMenuState != eLastDmpState )
    {
        printf("DmpMain:DmpMiniState: %u --> %u\n", eLastDmpState, enDmpMiniMenuState);
        eLastDmpState = enDmpMiniMenuState;
    }

    switch(enDmpMiniMenuState)
    {
        case STATE_DMP_MINIMENU_INIT:
            MApp_ZUI_ACT_StartupOSD(E_OSD_DMP_MINI_MENU);
            enDmpMiniMenuState = STATE_DMP_MINIMENU_WAIT;
            break;

        case STATE_DMP_MINIMENU_WAIT:
            MApp_ZUI_ProcessKey(u8KeyCode);
            u8KeyCode = KEY_NULL;
            break;

        case STATE_DMP_MINIMENU_CLEAN_UP:
            MApp_ZUI_ACT_ShutdownOSD();
            enDmpMiniMenuState = STATE_DMP_MINIMENU_INIT;
            enRetVal = EXIT_CLOSE;
            break;

        case STATE_DMP_MINIMENU_GOTO_STANDBY:
            MApp_ZUI_ACT_ShutdownOSD();
            u8KeyCode = KEY_POWER;
            enRetVal = EXIT_GOTO_STANDBY;
            break;

        case STATE_DMP_MINIMENU_GOTO_OSDPAGE:
            MApp_ZUI_ACT_ShutdownOSD();
            enDmpMiniMenuState = STATE_DMP_MINIMENU_INIT;
            enRetVal = EXIT_GOTO_OSDPAGE;
            break;

        case STATE_DMP_MINIMENU_GOTO_MAIN_MENU:
            MApp_ZUI_ACT_ShutdownOSD();
            enDmpMiniMenuState = STATE_DMP_MINIMENU_INIT;
            enRetVal = EXIT_GOTO_MENU;
            break;
#if ENABLE_DMP
        case STATE_DMP_MINIMENU_GOTO_DMP:
            MApp_ZUI_ACT_ShutdownOSD();
            enDmpMiniMenuState = STATE_DMP_MINIMENU_INIT;
            enRetVal = EXIT_GOTO_DMP;
            break;
#endif
#if (ENABLE_FM_RADIO)
        case STATE_DMP_MINIMENU_GOTO_RADIO:
            MApp_ZUI_ACT_ShutdownOSD();
            enDmpMiniMenuState = STATE_DMP_MINIMENU_INIT;
            enRetVal = EXIT_GOTO_FMRADIO;
            break;
#endif

        case STATE_DMP_MINIMENU_GOTO_CH_INFO:
            MApp_ZUI_ACT_ShutdownOSD();
            enDmpMiniMenuState = STATE_DMP_MINIMENU_INIT;
            enRetVal = EXIT_GOTO_INFO;
            break;

#ifdef ENABLE_BT
        case STATE_DMP_MINIMENU_GOTO_BT:
            MApp_ZUI_ACT_ShutdownOSD();
            enDmpMiniMenuState = STATE_INPUTSOURCE_INIT;
            enRetVal =EXIT_GOTO_BT;
            break;
#endif
#ifdef ENABLE_KTV
        case STATE_DMP_MINIMENU_GOTO_KTV:
            MApp_ZUI_ACT_ShutdownOSD();
            enDmpMiniMenuState = STATE_DMP_MINIMENU_INIT;
            enRetVal =EXIT_GOTO_KTV;
            break;
#endif

#ifdef ENABLE_YOUTUBE
    case STATE_DMP_MINIMENU_GOTO_YOUTUBE:
        MApp_ZUI_ACT_ShutdownOSD();
        enDmpMiniMenuState = STATE_DMP_MINIMENU_INIT;
        enRetVal =EXIT_GOTO_YOUTUBE;
        break;
#endif

#ifdef ENABLE_RSS
    case STATE_DMP_MINIMENU_GOTO_RSS:
        MApp_ZUI_ACT_ShutdownOSD();
        enDmpMiniMenuState = STATE_DMP_MINIMENU_INIT;
        enRetVal =EXIT_GOTO_RSS;
        break;
#endif

#if GAME_ENABLE
    case STATE_DMP_MINIMENU_GOTO_GAME:
        {
            MApp_ZUI_ACT_ShutdownOSD();
            enDmpMiniMenuState = STATE_DMP_MINIMENU_INIT;
            enRetVal = EXIT_GOTO_GAME_LIST;
        }
        break;
#endif
#ifdef ENABLE_EXTENSION
    case STATE_DMP_MINIMENU_GOTO_EXTENSION:
        {
        MApp_ZUI_ACT_ShutdownOSD();
        enDmpMiniMenuState = STATE_DMP_MINIMENU_INIT;
        enRetVal =EXIT_GOTO_EXTENSION;
        }
        break;
#endif

    default:
        enDmpMiniMenuState = STATE_DMP_MINIMENU_WAIT;
        break;
    }
    return enRetVal;
}

#endif // #if ENABLE_DMP_MINI_MENU
#endif // #if (ENABLE_DMP)
#undef MAPP_DMP_MAIN_C

