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
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define MAPP_DTV_MANUALTUNING_MAIN_C
#include "Board.h"
#if ENABLE_DVB //(ENABLE_DTV)
/******************************************************************************/
/*                 Header Files                                               */
/* ****************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "datatype.h"
#include "msAPI_Global.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "msAPI_FreqTableDTV.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_Key.h"
#include "MApp_UiMenuDef.h"
#include "MApp_ZUI_Main.h"
#include "MApp_DTV_ManualTuning_Main.h"
#include "MApp_ChannelChange.h"
#include "MApp_InputSource.h"
#include "msAPI_FreqTableDTV.h"
#include "msAPI_Timer.h"
#if  NTV_FUNCTION_ENABLE
#include "MApp_GlobalFunction.h"
#include "MApp_Scan.h"
#endif

#ifdef ENABLE_SELECT_NONESEARCH_CH
#include "MApp_TV.h"
#endif
#if ENABLE_DVB_T2
#include "MApp_Scan.h"
#include "msAPI_Timer.h"
#endif

#if (ENABLE_PIP)
#include "MApp_PIP.h"
#endif

#if (CHAKRA3_AUTO_TEST)
#include "MApp_AutoTest.h"
#include "MApp_ZUI_APIwindow.h"
#include "MApp_ZUI_ACTdtvmanualtuning.h"
#include "ZUI_exefunc.h"
#endif

///////////////////////////////////////////////////////////

EN_DTV_MANUALTUNING_STATE enDtvManualTuningState;

#if ENABLE_SBTVD_DTV_SYSTEM
extern E_ANTENNA_SOURCE_TYPE enLastWatchAntennaType;
#endif

U32 u32ManualScanMonitorSignalTimer = 0;

//////////////////////////////////////////////////////////
EN_RET MApp_DTV_ManualTuning_Main(void)
{
    EN_RET enRetVal = EXIT_NULL;
    MS_TP_SETTING stTempTP;

    switch(enDtvManualTuningState)
    {
        case STATE_DTV_MANUALTUNING_INIT:
            u32ManualScanMonitorSignalTimer = msAPI_Timer_GetTime0();

          #if ENABLE_DVB_T2
            MApp_DTV_Scan_T2_EnterSignalMonitorStatus(TRUE);
            if(IsDVBTInUse())
            {
                MAPP_DTV_Scan_T2_DoScan(DVB_T_DEMOD,FALSE);
            }
		  #endif

            #if 0
		    if(msAPI_CM_GetCountry() == E_NORWAY)
		    {
				msAPI_DFT_VHF_CrossBWFreq_SetFinishScanStatus(FALSE);
		    }
		    #endif
            //MApp_ZUI_ACT_StartupOSD(E_OSD_DTV_MANUAL_TUNING);
            MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);

            #if (ENABLE_PIP)
            if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
            {
                MApp_ClosePIPSubWindowSource();
            }
            #endif

          #if ENABLE_SBTVD_DTV_SYSTEM
            if(IS_SBTVD_APP)
            {
                if(enLastWatchAntennaType!=ANTENNA_DTV_TYPE)
                {
                    enLastWatchAntennaType = ANTENNA_DTV_TYPE;
                    MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_TYPE , MAIN_WINDOW );
                  #ifdef ENABLE_SELECT_NONESEARCH_CH
                    u16ChannelReturn_Num2=IVALID_TV_RETURN_NUM;
                  #endif
                }
            }
            else
          #endif
            {
                MApp_InputSource_ChangeInputSource(MAIN_WINDOW);
            }


            enDtvManualTuningState = STATE_DTV_MANUALTUNING_WAIT;

            if( msAPI_DFT_GetTSSetting(stGenSetting.stScanMenuSetting.u8RFChannelNumber, &stTempTP) == TRUE)
            {
                msAPI_Tuner_Tune2RfCh(&stTempTP);
            }
            stGenSetting.stScanMenuSetting.u8PreRFChannelNumber=stGenSetting.stScanMenuSetting.u8RFChannelNumber;

            break;

        case STATE_DTV_MANUALTUNING_WAIT:
            MApp_ZUI_ProcessKey(u8KeyCode);
            if(u8KeyCode == KEY_EXIT)
            {
                u32ManualScanMonitorSignalTimer = msAPI_Timer_GetTime0();
            }
            {
                BOOLEAN bLockStatus = FALSE;

                if(IsDTVInUse())
                {
                    msAPI_Tuner_CheckLock(&bLockStatus, FALSE);
                    if(bLockStatus != FALSE)
                    {
                        u32ManualScanMonitorSignalTimer = msAPI_Timer_GetTime0();
                        g_CurSignalStrength = msAPI_Tuner_GetSignalQualityPercentage();
                        #if 0
						if(msAPI_CM_GetCountry() == E_NORWAY)
						{
							msAPI_DFT_VHF_CrossBWFreq_SetFinishScanStatus(TRUE);
						}
						#endif
                    }
                    else
                    {
                        if(msAPI_Timer_DiffTimeFromNow(u32ManualScanMonitorSignalTimer) >= 4000)
                        {
						#if ENABLE_DVB_T2
                            if(IsDVBTInUse())
                            {
                                if( DVB_T_DEMOD == MApp_DTV_Scan_T2_ScanCheckSignal()
                                  || MApp_DTV_Scan_T2_ForceMonitorT2Signal()
                                  )
                                {
                                    MAPP_DTV_Scan_T2_DoScan(DVB_T2_DEMOD,TRUE);
                                    MApp_DTV_Scan_T2_SetForceMonitorT2Signal(FALSE);
                                }
                                else
                                {
                                    MAPP_DTV_Scan_T2_DoScan(DVB_T_DEMOD,TRUE);
                                }
                            }
						#endif

                            if( msAPI_DFT_GetTSSetting(stGenSetting.stScanMenuSetting.u8RFChannelNumber, &stTempTP) == TRUE)
                            {
                                #if 0
								if(msAPI_CM_GetCountry() == E_NORWAY)
								{
									if((msAPI_DFT_VHF_CrossBWFreq_GetFinishScanStatus() == FALSE)
										&& (stGenSetting.stScanMenuSetting.u8RFChannelNumber >= 5 && stGenSetting.stScanMenuSetting.u8RFChannelNumber <= 120))
									{
										if(msAPI_DFT_GetBandwidth() == E_RF_CH_BAND_7MHz)
										{
											msAPI_DFT_SetBandwidth(E_RF_CH_BAND_8MHz);
											stTempTP.enBandWidth = E_RF_CH_BAND_8MHz;
										}
										else
										{
											msAPI_DFT_SetBandwidth(E_RF_CH_BAND_7MHz);
											stTempTP.enBandWidth = E_RF_CH_BAND_7MHz;
										}
										msAPI_DFT_VHF_CrossBWFreq_SetFinishScanStatus(TRUE);
									}
								}
								#endif
                                msAPI_Tuner_Tune2RfCh(&stTempTP);
                            }
                            u32ManualScanMonitorSignalTimer = msAPI_Timer_GetTime0();
                            g_CurSignalStrength = 0;
                            break;
                        }
                        g_CurSignalStrength = 0;
                    }
                    g_LockStatus = bLockStatus;
                }
            }
            u8KeyCode = KEY_NULL;

          #if (CHAKRA3_AUTO_TEST)
            if( g_AT_enDTVManualTuningState == E_AUTO_TEST_TUNING_WAIT_START )
            {
                // Get channel number from AutoTest
                U16 u16DtvManualTuneChannelNumber = MApp_AT_Get_DtvManualTuneChannelNumber();
                if( u16DtvManualTuneChannelNumber > 99 )
                    u16DtvManualTuneChannelNumber = 99;

                MS_U8 u8First = u16DtvManualTuneChannelNumber / 10;
                MS_U8 u8Second = u16DtvManualTuneChannelNumber % 10;

                MApp_ZUI_ACT_ExecuteDtvManualTuningAction( (EN_OSD_WNDEXEACTION_ENUM)(EN_EXE_MANUAL_SCAN_NUMBERKEY_0 + u8First));
                MApp_ZUI_ACT_ExecuteDtvManualTuningAction((EN_OSD_WNDEXEACTION_ENUM)(EN_EXE_MANUAL_SCAN_NUMBERKEY_0 + u8Second));

                MApp_ZUI_ACT_ExecuteDtvManualTuningAction(EN_EXE_MANUAL_SCAN_CHANGE_RF);

                g_AT_enDTVManualTuningState = E_AUTO_TEST_TUNING_START;
            }
          #endif

            break;

        case STATE_DTV_MANUALTUNING_CLEAN_UP:
          #if ENABLE_DVB_T2
            MApp_DTV_Scan_T2_EnterSignalMonitorStatus(FALSE);
          #endif
            MApp_ZUI_ACT_ShutdownOSD();
          #if  NTV_FUNCTION_ENABLE
            if(OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY)
            {
                if(MApp_Get_ScanGoRegion_Status() == FALSE)
                {
                    MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
                }
            }
            else
            {
                MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
            }
          #else
            MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
          #endif

            enDtvManualTuningState = STATE_DTV_MANUALTUNING_INIT;

          #if  0//NTV_FUNCTION_ENABLE //wait to do
            if(MApp_Get_ScanGoRegion_Status())
            {
                enRetVal = EXIT_GOTO_NTV_LIST;
                MApp_DTV_Scan_SetSelectFavoriteNetwork(INVALID_NETWORKINDEX);
            }
            else
            {
                enRetVal = EXIT_CLOSE;

            }
          #else
            enRetVal = EXIT_CLOSE;
          #endif
            break;

        case STATE_DTV_MANUALTUNING_GOTO_STANDBY:
          #if ENABLE_DVB_T2
            MApp_DTV_Scan_T2_EnterSignalMonitorStatus(FALSE);
          #endif
            MApp_ZUI_ACT_ShutdownOSD();
            u8KeyCode = KEY_POWER;
            enRetVal = EXIT_GOTO_STANDBY;
            break;

        case STATE_DTV_MANUALTUNING_GOTO_MAIN_MENU:
          #if ENABLE_DVB_T2
            MApp_DTV_Scan_T2_EnterSignalMonitorStatus(FALSE);
          #endif
            MApp_ZUI_ACT_ShutdownOSD();
            MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
            enDtvManualTuningState = STATE_DTV_MANUALTUNING_INIT;
            enRetVal = EXIT_GOTO_MENU;
            break;

        case STATE_DTV_MANUALTUNING_GOTO_DTV_SCAN:
            enDtvManualTuningState = STATE_DTV_MANUALTUNING_WAIT;
            enRetVal = EXIT_GOTO_DTVSCAN;
            break;

        default:
            enDtvManualTuningState = STATE_DTV_MANUALTUNING_WAIT;
            break;
    }
    return enRetVal;
}
#endif//#if (ENABLE_DTV)



/***************************************************************************************/

#undef MAPP_DTV_MANUALTUNING_MAIN_C

