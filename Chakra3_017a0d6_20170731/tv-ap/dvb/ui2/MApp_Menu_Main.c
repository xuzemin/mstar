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

#define MAPP_MENU_MAIN_C

/******************************************************************************/
/*                 Header Files                                               */
/* ****************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"

#include "apiXC.h"
#include "apiXC_Adc.h"
#include "MApp_GlobalSettingSt.h"

#include "MApp_Exit.h"
#include "MApp_Key.h"
#include "MApp_UiMenuDef.h"
#include "MApp_ZUI_Main.h"
#include "ZUI_tables_h.inl"
#include "MApp_Menu_Main.h"
#include "MApp_OSDPage_Main.h"
#include "ZUI_exefunc.h"
#include "MApp_TV.h"

#include "MApp_ChList_Main.h" //ZUI:
#include "msAPI_FreqTableDTV.h"
#include "MApp_SaveData.h"
#include "MApp_InputSource.h"

#if ENABLE_ATSC
#include "MApp_ZUI_ACTmainpage.h"
#include "msAPI_Timer.h"
#include "MApp_ChannelChange.h"
#include "msAPI_Tuner_ATSC.h"
#include "MApp_ChannelProc_ATSC.h"
#endif

#include "MApp_ZUI_ACTinstall.h"
///////////////////////////////////////////////////////////

EN_MENU_STATE enMainMenuState;

#if(DVBC_CERTIFICATION_AUTOSCAN_ENABLE)
extern BOOLEAN bNeedShowtuning;
#endif

//////////////////////////////////////////////////////////

EN_MENU_STATE MApp_Menu_Main_GetState(void)
{
    return enMainMenuState;
}

#if ENABLE_TTX
extern void MApp_TTX_SetChInfoOnOff(BOOLEAN val);
#endif

#if (ENABLE_ATSC)
BOOLEAN MApp_UiMenu_CheckTVSignal(SignalType type)
{
    U8 u8TmpPreSNR;

    switch(type)
    {
        case DTV_SIGNAL:
            u8TmpPreSNR = msAPI_Tuner_CheckSignalSNR();
           // if((u8TmpPreSNR+1) != u8PreSignalSNR)
            {
                if(IS_HIDE_CH_ATSC(MApp_ChanProc_GetCurProgIndex()))
                {
                    u8PreSignalSNR = (U8)SIGNAL_NO;
                }
                else
                {
                    u8PreSignalSNR = u8TmpPreSNR;
                }
                switch(u8PreSignalSNR)
                {
                    case SIGNAL_NO: //no signal
                        enDTVSignalStatus = DTV_SIGNAL_NONE;
                        break;
                    case SIGNAL_WEAK: //weak signal
                        enDTVSignalStatus = DTV_SIGNAL_BAD;
                        break;
                    case SIGNAL_MODERATE: //moderate signal
                        enDTVSignalStatus = DTV_SIGNAL_NORMAL;
                        break;
                    case SIGNAL_STRONG: //strong signal
                    case SIGNAL_VERY_STRONG: //very strong signal
                        enDTVSignalStatus = DTV_SIGNAL_GOOD;
                        break;
                     default:
                        enDTVSignalStatus = DTV_SIGNAL_NONE;
                        break;
                }
            }
            break;

        case ATV_SIGNAL:
            u8PreSignalSNR = 0;
            break;

        default:
            break;
    }
    return TRUE;
}

#endif

EN_RET MApp_Menu_Main(void)
{
#if (ENABLE_ATSC)
    static U32 s_u32LastRefreshTime = 0;
#endif
    EN_RET enRetVal =EXIT_NULL;

    #if(DVBC_CERTIFICATION_AUTOSCAN_ENABLE)
        if(bNeedShowtuning == TRUE)
        {
            enMainMenuState = STATE_MENU_GOTO_SCAN;
            bNeedShowtuning = FALSE;
        }
    #endif
   
    switch(enMainMenuState)
    {
        case STATE_MENU_INIT:
            MApp_ZUI_ACT_StartupOSD(E_OSD_MAIN_MENU);
            enMainMenuState = STATE_MENU_WAIT;
          #if ENABLE_TTX
            MApp_TTX_SetChInfoOnOff(FALSE);
          #endif
            break;

        case STATE_MENU_WAIT:
            MApp_ZUI_ProcessKey(u8KeyCode);
            u8KeyCode = KEY_NULL;

          #if (ENABLE_ATSC)
            if(bChListKeyPress)
            {
                if(msAPI_Timer_DiffTimeFromNow(u32ChListKeyPressStartTime) > 300)
                {
                    bChListKeyPress = FALSE;
                    u32ChListKeyPressStartTime= 0;
                    MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
                }
            }
            else if(MApp_ZUI_GetActiveOSD() == E_OSD_MAIN_MENU)
            {
                if( SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW) == INPUT_SOURCE_DTV )
                {
                    if( msAPI_Timer_DiffTime_2(s_u32LastRefreshTime, msAPI_Timer_GetTime0()) > 1000 )
                    {
                        s_u32LastRefreshTime = msAPI_Timer_GetTime0();
                        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_MAINMENU_DTV_SIGNAL_REFLASH);
                    }
                }
            }
          #endif

          #if ENABLE_DVBC
            if(MApp_ZUI_ACT_Get_InstallGuidePage() == PAGE_INSTALL_SELECT_DVBC)
            {
                MApp_ZUI_ACT_Set_InstallGuidePage(PAGE_INSTALL_TUNING_COUNTRY);
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_GOTO_DVB_SELECT_INPUT_PASSWORD_DLG);
            }
          #endif
            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_UPDATE_SIGNAL_INFORMAT);
            break;

        //case STATE_MENU_EPGTIMER_WAIT:
            //MApp_UiMenu_EPGTimer_ProcessUserInput();
            //break;

        case STATE_MENU_CLEAN_UP:
            MApp_ZUI_ACT_ShutdownOSD();
            enMainMenuState = STATE_MENU_INIT;
            enRetVal =EXIT_CLOSE;
            break;

        case STATE_MENU_GOTO_STANDBY:
            MApp_ZUI_ACT_ShutdownOSD();
            u8KeyCode = KEY_POWER;
            enRetVal =EXIT_GOTO_STANDBY;
            break;

        case STATE_MENU_GOTO_SCAN:
            enMainMenuState = STATE_MENU_INIT;
#if ENABLE_CI_PLUS
			stGenSetting.stCIPlusSetting.OpMenuRestartWhenChooseNo = FALSE; // clean flag
#endif

          #if ENABLE_ATSC
            if (IsAtscInUse()||IsATVInUse())
            {
                enRetVal = EXIT_GOTO_ATSC_SCAN;
            }
            else
          #endif
            {
                MApp_ZUI_ACT_ShutdownOSD();
                MApp_ZUI_ACT_StartupOSD(E_OSD_AUTO_TUNING);
                enRetVal = EXIT_GOTO_SCAN;
            }
            break;

        case STATE_MENU_GOTO_EPG:
            MApp_ZUI_ACT_ShutdownOSD();
            enMainMenuState = STATE_MENU_INIT;
            enRetVal =EXIT_GOTO_EPG;
            break;

#if ENABLE_FM_RADIO
        case STATE_MENU_GOTO_FMRADIO:
            MApp_ZUI_ACT_ShutdownOSD();
            enMainMenuState = STATE_MENU_INIT;
            enRetVal =EXIT_GOTO_FMRADIO;
            break;
#endif

#if ENABLE_DTV
        case STATE_MENU_GOTO_DTV_MANUALTUNING:
  #if (ENABLE_DVBC)
            if(IsDVBCInUse())//TODO need add DVB-C case
            {
            //#if (!ENABLE_T_C_COMBO)
                msAPI_CM_ResetAllProgram();
            //#endif
                stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType=EN_DVB_T_TYPE;
                MApp_SaveScanMenuSetting();
                msAPI_Tuner_SwitchSource((EN_DVB_TYPE)stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType, TRUE);
                //stGenSetting.stScanMenuSetting.u8PreRFChannelNumber = INVALID_IDINDEX;
                stGenSetting.stScanMenuSetting.u8PreRFChannelNumber = INVALID_RF_CHANNEL_NUMBER;
                stGenSetting.stScanMenuSetting.u8RFChannelNumber = msAPI_DFT_GetFirstPhysicalChannelNumber();
            }
    #if 0
            MApp_ZUI_ACT_StartupOSD(E_OSD_CADTV_MANUAL_TUNING);
            enMainMenuState = STATE_MENU_INIT;
            enRetVal = EXIT_GOTO_DTV_MANUALTUNING;
            break;
    #endif
  #endif
            MApp_ZUI_ACT_ShutdownOSD();
            MApp_Set_IdleInputValue(0);
            MApp_Set_IdleDigitCount(0);
            /* make sure input source is dtv */

            /* make sure input source is dtv */

            MApp_ZUI_ACT_StartupOSD(E_OSD_DTV_MANUAL_TUNING);

            enMainMenuState = STATE_MENU_INIT;
            enRetVal = EXIT_GOTO_DTV_MANUALTUNING;
            break;
#endif

        case STATE_MENU_GOTO_ATV_MANUALTUNING:
            MApp_ZUI_ACT_ShutdownOSD();
            enMainMenuState = STATE_MENU_INIT;
            enRetVal = EXIT_GOTO_ATV_MANUALTUNING;
            break;

        case STATE_MENU_GOTO_CHANNELCHANGE:
            MApp_ZUI_ACT_ShutdownOSD();
            enMainMenuState = STATE_MENU_INIT;
            enRetVal = EXIT_GOTO_CHANNELCHANGE;
            break;

        case STATE_MENU_GOTO_CIMMI:
            MApp_ZUI_ACT_ShutdownOSD();
            enMainMenuState = STATE_MENU_INIT;
            enRetVal = EXIT_GOTO_MMI;
            break;

#if ENABLE_DMP
        case STATE_MENU_GOTO_DMP:
            MApp_ZUI_ACT_ShutdownOSD();
            enMainMenuState = STATE_MENU_INIT;
            enRetVal = EXIT_GOTO_DMP;
            break;
#endif

#ifdef ENABLE_BT
        case STATE_MENU_GOTO_BT:
            MApp_ZUI_ACT_ShutdownOSD();
            enMainMenuState = STATE_MENU_INIT;
            enRetVal = EXIT_GOTO_BT;
            break;
#endif

#ifdef ENABLE_KTV
        case STATE_MENU_GOTO_KTV:
            MApp_ZUI_ACT_ShutdownOSD();
            enMainMenuState = STATE_MENU_INIT;
            enRetVal = EXIT_GOTO_KTV;
            break;
#endif

#if(ENABLE_PVR ==1)
        case STATE_MENU_GOTO_PVR_CHECK_FS:
            MApp_ZUI_ACT_ShutdownOSD();
            enMainMenuState = STATE_MENU_INIT;
            enRetVal = EXIT_GOTO_PVR_CHECK_FS;
            break;
#endif

#if ENABLE_DVBC
        case STATE_MENU_GOTO_CADTV_MANUALTUNING:
            MApp_ZUI_ACT_ShutdownOSD();
            enMainMenuState = STATE_MENU_INIT;
            enRetVal = EXIT_GOTO_CADTV_MANUALTUNING;
            break;
#endif

        case STATE_MENU_GOTO_OSDPAGE:
            MApp_ZUI_ACT_ShutdownOSD();
            enMainMenuState = STATE_MENU_INIT;
            enRetVal = EXIT_GOTO_OSDPAGE;
            break;

        case STATE_MENU_GOTO_INPUT_SOURCE:
            MApp_ZUI_ACT_ShutdownOSD();
            enMainMenuState = STATE_MENU_INIT;
            enRetVal = EXIT_GOTO_INPUTSOURCE;
            break;

        case STATE_MENU_GOTO_CHANNEL_LIST:
            MApp_ZUI_ACT_ShutdownOSD();
            enMainMenuState = STATE_MENU_INIT;
            enRetVal = EXIT_GOTO_OSDPAGE;
            MApp_OSDPage_SetOSDPage(E_OSD_CHANNEL_LIST);
            MApp_ChannelList_SetMode(MODE_CHLIST_TV);
            break;

        case STATE_MENU_GOTO_FAVORITE_LIST:
            MApp_ZUI_ACT_ShutdownOSD();
            enMainMenuState = STATE_MENU_INIT;
            enRetVal = EXIT_GOTO_OSDPAGE;
            MApp_OSDPage_SetOSDPage(E_OSD_CHANNEL_LIST);
            MApp_ChannelList_SetMode(MODE_CHLIST_TV_FAV);
            break;

        case STATE_MENU_GOTO_INFO:
            MApp_ZUI_ACT_ShutdownOSD();
            enMainMenuState = STATE_MENU_INIT;
            enRetVal = EXIT_GOTO_INFO;
            break;

#ifdef ENABLE_YOUTUBE
        case STATE_MENU_GOTO_YOUTUBE:
            MApp_ZUI_ACT_ShutdownOSD();
           enMainMenuState = STATE_MENU_INIT;
            enRetVal =EXIT_GOTO_YOUTUBE;
            break;
#endif
#ifdef ENABLE_RSS
        case STATE_MENU_GOTO_RSS:
            MApp_ZUI_ACT_ShutdownOSD();
            enMainMenuState = STATE_MENU_INIT;
            enRetVal =EXIT_GOTO_RSS;
            break;
#endif
//#ifdef ENABLE_NETFLIX
//        case STATE_MENU_GOTO_NETFLIX:
//            MApp_ZUI_ACT_ShutdownOSD();
//            enMainMenuState = STATE_MENU_INIT;
//            enRetVal =EXIT_GOTO_NETFLIX;
//            break;
//#endif
#ifdef ENABLE_EXTENSION
        case STATE_MENU_GOTO_EXTENSION:
        {
            MApp_ZUI_ACT_ShutdownOSD();
            enMainMenuState = STATE_MENU_INIT;
            enRetVal =EXIT_GOTO_EXTENSION;
        }
        break;
#endif
    #if(ENABLE_S2)
        case STATE_MENU_GOTO_DISHSETUP:
        {
            MApp_ZUI_ACT_ShutdownOSD();
            enMainMenuState = STATE_MENU_INIT;
            enRetVal = EXIT_GOTO_DISHSETUP;

            printf("STATE_MENU_GOTO_DISHSETUP end \r\n");
        }
        break;
    #endif
        default:
            enMainMenuState = STATE_MENU_WAIT;
            break;
    }
    return enRetVal;
}

#undef MAPP_MENU_MAIN_C

