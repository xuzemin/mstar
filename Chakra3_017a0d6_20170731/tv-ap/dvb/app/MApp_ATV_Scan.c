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

#define MAPP_ATV_SCAN_C

//******************************************************************************
//                    Header Files
//******************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Board.h"
#include "datatype.h"
#include "msAPI_Global.h"
#include "msAPI_IR.h"
#include "msAPI_Tuning.h"
#include "msAPI_audio.h"
#include "msAPI_VD.h"
#include "msAPI_Timer.h"
#include "apiXC.h"
#include "MApp_GlobalVar.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_Exit.h"
#include "MApp_Key.h"
#include "MApp_UiMenuDef.h"
#include "MApp_InputSource.h"
#include "MApp_ATVProc.h"

#include "ZUI_exefunc.h"
#include "MApp_ZUI_Main.h"

#include"MApp_BlockSys.h"
#include"MApp_MultiTasks.h"
#include "MApp_ATV_Scan.h"
#include "IF_Demodulator.h"

#if (ENABLE_DTV)
#include "mapp_demux.h"
#endif

#include "MApp_SaveData.h"
#include "MApp_GlobalFunction.h"
#include "MApp_SignalMonitor.h"
#if ENABLE_TTX
#include "mapp_ttx.h"
#endif
#include "MApp_ChannelChange.h"
#include "MApp_TopStateMachine.h"
#if ENABLE_SBTVD_CM_APP
#include "msAPI_ChProc.h"
#endif
#if MHEG5_ENABLE
#include "MApp_MHEG5_Main.h"
#endif

#if (ENABLE_PIP)
#include "MApp_PIP.h"
#endif

#include "MApp_ParentalRating.h"
#include "MApp_Scan.h"



extern EN_OSD_TUNE_TYPE_SETTING eTuneType;
extern BOOLEAN bOriginalSrcIsDvbc;

#ifndef SCAN_TEST_MODE_ENABLE
#define SCAN_TEST_MODE_ENABLE 0
#endif
#define SCAN_FREQ_ATTIME    1

//********************************************************************************
//                     Macro
//********************************************************************************
#define ATV_SCAN_DBINFO(y)      //y
#define ENABLE_PRINT_SCAN_TIME  DISABLE // air + cable

//********************************************************************************
//                     Local
//********************************************************************************
static EN_ATV_SCAN_STATE enATVScanState = STATE_ATV_SCAN_INIT;
static EN_ATV_SCAN_STATE enPreATVScanState = STATE_ATV_SCAN_INIT;
static BOOLEAN fReturnToPrevious=FALSE;
static BOOLEAN fEndHalt=FALSE;

#if SCAN_FREQ_ATTIME
static U16 PreATVScanPLL;
#else
static U8 PreATVScanPercent;
#endif

#if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_SCAN || (TV_SYSTEM == TV_NTSC) )
static U8 PreATVScanChannel;
#endif
static void MApp_ATV_Scan_ProcessUserInput ( void );

#if((FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)||(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF))
    extern BOOLEAN gbTVAutoScanChannelEnable;
#elif(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)        // GEM_SYNC_0815
    #include "Tuner.h"
    #include "drvVIF_MSB1210.h"

    extern BOOLEAN gbTVAutoScanEn;
#endif

#if ENABLE_PRINT_SCAN_TIME
static U32 _u32ScanTime;
#endif

//********************************************************************************
//                     Functions
//********************************************************************************
EN_ATV_SCAN_STATE MApp_ATV_Scan_ScanState ( void )
{
    return enATVScanState;
}

void MApp_ATV_Scan_State_Init ( void )
{
    enATVScanState = STATE_ATV_SCAN_INIT;
}

void MApp_ATV_Scan_End ( void )
{
    if ( msAPI_Tuner_IsTuningProcessorBusy() == TRUE )
    {
        msAPI_Tuner_TuningProcessor(AFT_EXT_STEP_SEARCHSTOP);
    }
    #if (FRONTEND_TUNER_TYPE == SILAB_2158_TUNER)
    if ( stGenSetting.stScanMenuSetting.u8ScanType == SCAN_TYPE_AUTO )
    {
        ATV_Set_Artificial_Snow(1);
    }
    #endif

#if((FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)||(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF))
    gbTVAutoScanChannelEnable=FALSE;
#elif(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)     // GEM_SYNC_0815
    gbTVAutoScanEn=FALSE;
    MDrv_VIF_SetHandler(gbTVAutoScanEn, GAIN_DISTRIBUTION_THR);
#endif

#if ENABLE_SBTVD_CM_APP
    if(IS_SBTVD_APP && ANT_AIR == msAPI_ATV_GetCurrentAntenna())
    {
        if(msAPI_ATV_GetActiveProgramCount())
            msAPI_CHPROC_CM_InitOridial();
          msAPI_ATV_SetCurrentProgramNumber(msAPI_ATV_GetFirstProgramNumber(FALSE));
    }
#endif
#if 0//( TV_FREQ_SHIFT_CLOCK )
    msAPI_Tuner_Patch_TVShiftClk(FALSE);
#endif
}


extern BOOLEAN MApp_ZUI_ACT_ExecuteAutoTuningAction(U16 act);

EN_RET MApp_ATV_Scan ( void )
{
    EN_RET enATVScanRetVal;
    BOOLEAN bIsAutoScanInProgress;
    BOOLEAN bIsOneProgramDetected;
    U8 u8ManProcess;
    static U8 u8ManProcessStart=0;
#if ENABLE_SKIP_ATV_PROGRAMS_SAME_TO_DTV_LCN
    static U16 U16CurATVNumber=0;
#endif

    static U16 _u16PreTunerPLL=0;
    enATVScanRetVal = EXIT_NULL;

    MApp_ATV_Scan_ProcessUserInput();

    switch ( enATVScanState )
    {
        case STATE_ATV_SCAN_INIT:
            ATV_SCAN_DBINFO( printf( "STATE_ATV_SCAN_INIT>>\n" ) );

        #if ENABLE_PRINT_SCAN_TIME
            if(msAPI_ATV_GetCurrentAntenna() == ANT_AIR)
            {
                _u32ScanTime = msAPI_Timer_GetTime0();
            }
        #endif

          #if((FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)||(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF))
            gbTVAutoScanChannelEnable=TRUE;
          #elif(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)    // GEM_SYNC_0815
            gbTVAutoScanEn=TRUE;
            MDrv_VIF_SetHandler(gbTVAutoScanEn, GAIN_DISTRIBUTION_THR);
          #endif

          #if ENABLE_OFFLINE_SIGNAL_DETECTION
            MApp_OffLineInit();
          #endif
            u8ScanAtvChNum = 0;

        #if SCAN_FREQ_ATTIME
            PreATVScanPLL = msAPI_Tuner_GetCurrentChannelPLL();
        #else
            PreATVScanPercent = 0;
        #endif

        #if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_SCAN || (TV_SYSTEM == TV_NTSC) )
            PreATVScanChannel = 0;
        #endif


        #if 0
          #if (ENABLE_DTV)
            if ( UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_DTV )
            {
              #if MHEG5_ENABLE
                MApi_MHEG5_Disable(EN_MHEG5_DM_DISABLE_AND_WAIT);
              #endif
            }
          #endif
        #else
          #if MHEG5_ENABLE
            MApi_MHEG5_Disable(EN_MHEG5_DM_DISABLE_AND_WAIT);
          #endif
        #endif

            //PIP behavior: If PIP is enabled, close sub window and turn on ATV in the main window.
        #if (ENABLE_PIP)
            if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
            {
                BOOLEAN bResetSrc = FALSE;

                if (  IsSrcTypeScart(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))
                   || IsSrcTypeAV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))
                   || IsSrcTypeSV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
                {
                    bResetSrc = TRUE;
                }

                if (stGenSetting.g_stPipSetting.enPipSoundSrc == EN_PIP_SOUND_SRC_SUB)
                {
                    stGenSetting.g_stPipSetting.enPipSoundSrc = EN_PIP_SOUND_SRC_MAIN;
                    MApp_InputSource_PIP_ChangeAudioSource(MAIN_WINDOW);
                }

                E_UI_INPUT_SOURCE ePreSrc = UI_SUB_INPUT_SOURCE_TYPE;
                UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_NONE;
                MApp_InputSource_ChangeInputSource(SUB_WINDOW);
                UI_SUB_INPUT_SOURCE_TYPE = ePreSrc;
                stGenSetting.g_stPipSetting.enPipMode = EN_PIP_MODE_OFF;
                if(bResetSrc)
                {//Set sub window source type to 1st compatible src with the main window.
                    UI_SUB_INPUT_SOURCE_TYPE = MApp_InputSource_GetUIInputSourceType(MApp_InputSource_PIP_Get1stCompatibleSrc(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)));
                }
            }
        #endif // #if (ENABLE_PIP)

        #if ENABLE_TTX_ACI
            MApp_TTX_InitACI();
        #endif

            MApp_ChannelChange_DisableChannel(TRUE, MAIN_WINDOW);

          #if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_SCAN || (TV_SYSTEM == TV_NTSC) )
            stGenSetting.stScanMenuSetting.u8VideoSystem_Brazil=E_VIDEOSTANDARD_BRAZIL_AUTO;
          #endif

            if ( UI_INPUT_SOURCE_TYPE != UI_INPUT_SOURCE_ATV )
            {
                MApp_InputSource_RecordSource(UI_INPUT_SOURCE_TYPE);

                //UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ATV;
                MApp_InputSrc_Set_UiInputSrcType(UI_INPUT_SOURCE_ATV);

                MApp_InputSource_ChangeInputSource(MAIN_WINDOW);
            }

        #if (ENABLE_DTV)
            if(TRUE == MApp_Get_ParentalBlock_state())
            {
                MApp_ParentalControl_SetBlockStatus(FALSE);
                MApp_Set_ParentalBlock_state(DISABLE);
            }
        #endif

          #if ENABLE_TTX
            MApp_TTX_EnableScan( 1 );
          #endif

            //Cancel Freeze
            if(MApp_IsImageFrozen())
            {
                MApp_SetImageFrozen(FALSE);
                MApi_XC_FreezeImg(FALSE, MAIN_WINDOW);
            }

            // Switch Antenna
        #if(ENABLE_SBTVD_ATV_SYSTEM)
            if( IS_COUNTRY_USE_SBTVD() )
            {
                if( MApp_TopStateMachine_GetTopState() == STATE_TOP_CATV_SCAN ) // Need refine
                {
                    msAPI_ATV_SetCurrentAntenna(ANT_CATV);
                }
                else
                {
                    msAPI_ATV_SetCurrentAntenna(ANT_AIR);
                }
            }
        #endif


            if ( stGenSetting.stScanMenuSetting.u8ScanType == SCAN_TYPE_AUTO )
            {
              #if (FRONTEND_TUNER_TYPE == SILAB_2158_TUNER)
                ATV_Set_Artificial_Snow(0);
              #endif

              #if 0//ENABLE_T_C_COMBO
                if(   (eTuneType == OSD_TUNE_TYPE_ATV_ONLY)
                    #if(!ENABLE_SBTVD_SCAN)
                    ||(eTuneType == OSD_TUNE_TYPE_DTV_PLUS_ATV)
                    #endif
                  )
                {
                    MDrv_IFDM_Init();
                #if(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF)
                    msAPI_Tuner_Clear_IfFreqStatus();
                #endif
                }
              #endif

              #if ( ENABLE_DVB_TAIWAN_APP || (TV_SYSTEM == TV_NTSC) )
                msAPI_ATV_SetCurrentProgramNumber(msAPI_ATV_GetChannelMin()-1);
              #else
                #if ENABLE_SBTVD_SCAN
                if(IS_SBTVD_APP)
                {
                    msAPI_ATV_SetCurrentProgramNumber(msAPI_ATV_GetChannelMin()-1);
                }
                else
                #endif
                {
                    ATV_SCAN_DBINFO( printf( "<<<SCAN_TYPE_AUT>O>> " ) );
                    msAPI_Tuning_IsScanL(stGenSetting.stScanMenuSetting.u8LSystem);

                    if ( stGenSetting.stScanMenuSetting.u8LSystem )
                    {
                        ATV_SCAN_DBINFO( printf( "L System\n" ) );
                    }
                    else
                    {
                        ATV_SCAN_DBINFO( printf( "BG System\n" ) );
                    }
                    msAPI_ATV_SetCurrentProgramNumber(0);
                }
              #endif

                msAPI_Tuner_TuningProcessor(AFT_EXT_STEP_SEARCHALL);

                enATVScanState = STATE_ATV_SCAN_WAIT;
            }
            else
            {
                ATV_SCAN_DBINFO( printf( "<<<SCAN_TYPE_MANUAL>>> \n" ) );
                if (stGenSetting.stScanMenuSetting.u8ATVManScanType == ATV_MAN_SCAN_TYPE_ONECH)
                {
                    ATV_SCAN_DBINFO( printf( "ATV_MAN_SCAN_TYPE_ONECH>>\n" ) );
                    if ( stGenSetting.stScanMenuSetting.u8ATVManScanDir == ATV_MAN_SCAN_UP )
                    {
                        ATV_SCAN_DBINFO( printf( "ATV_MAN_SCAN_UP>>\n" ) );
                        msAPI_Tuner_TuningProcessor(AFT_EXT_STEP_SEARCHONETOUP);
                    }
                    else
                    {
                        ATV_SCAN_DBINFO( printf( "ATV_MAN_SCAN_DOWN>>\n" ) );
                        msAPI_Tuner_TuningProcessor(AFT_EXT_STEP_SEARCHONETODOWN);
                    }
                    enATVScanState = STATE_ATV_SCAN_WAIT;
                }
                else
                {
                    enATVScanState = STATE_ATV_SCAN_END;
                }
                u8ManProcessStart = msAPI_Tuner_GetTuningProcessPercent();
            }
            break;


        case STATE_ATV_SCAN_WAIT:
            if ( stGenSetting.stScanMenuSetting.u8ScanType == SCAN_TYPE_AUTO )
            {
                bIsAutoScanInProgress = msAPI_Tuner_IsTuningProcessorBusy();

                if ( FALSE == bIsAutoScanInProgress )
                {
                    ATV_SCAN_DBINFO( printf( "Scan finished>>\n" ) );

                    enATVScanState = STATE_ATV_SCAN_END;

                    if(eTuneType == OSD_TUNE_TYPE_ATV_ONLY)
                    {
                        MApp_ZUI_ACT_ExecuteAutoTuningAction(EN_EXE_SCAN_CONFIRM_BTN_YES);
                    }
                    break;
                }

                bIsOneProgramDetected = msAPI_Tuner_IsOneProgramDetected();

                if ( TRUE == bIsOneProgramDetected )
                {
                #if ENABLE_SKIP_ATV_PROGRAMS_SAME_TO_DTV_LCN
                    U16CurATVNumber = msAPI_ATV_GetCurrentProgramNumber()+1;
                #endif
                    ATV_SCAN_DBINFO( printf( "One channel detected>>\n" ) );
                    enATVScanState = STATE_ATV_SCAN_SHOW_INFO;
                }

                if (msAPI_Tuner_PreProgramDeteted())
                {
                    if(_u16PreTunerPLL != msAPI_Tuner_GetCurrentChannelPLL())
                    {
                        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_AUTOTUNING_PROGRESS);
                        _u16PreTunerPLL = msAPI_Tuner_GetCurrentChannelPLL();
                    }
                }
                else
                {
                #if ( ENABLE_DVB_TAIWAN_APP || (TV_SYSTEM == TV_NTSC) )
                    U8 u8Channel = msAPI_ATV_GetCurrentProgramNumber()+1;

                    if ( PreATVScanChannel  != u8Channel)
                    {
                        PreATVScanChannel = u8Channel;
                        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_AUTOTUNING_PROGRESS);
                    }
                #else
                    #if ENABLE_SBTVD_SCAN
                    if(IS_SBTVD_APP)
                    {
                        U8 u8Channel = msAPI_ATV_GetCurrentProgramNumber()+1;

                        if ( PreATVScanChannel  != u8Channel)
                        {
                            PreATVScanChannel = u8Channel;
                            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_AUTOTUNING_PROGRESS);
                        }
                    }
                    else
                    #endif
                    {
                      #if SCAN_FREQ_ATTIME
                        if ( PreATVScanPLL != msAPI_Tuner_GetCurrentChannelPLL())
                        {
                            PreATVScanPLL = msAPI_Tuner_GetCurrentChannelPLL();
                            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_AUTOTUNING_PROGRESS);
                        }
                      #else
                        U8 u8Temp;

                        u8Temp = msAPI_Tuner_GetTuningProcessPercent();

                        if ( PreATVScanPercent  < u8Temp)
                        {
                            PreATVScanPercent = u8Temp;
                            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_AUTOTUNING_PROGRESS);
                        }
                      #endif
                    }
                #endif
                }
            }
            else
            {
                if ( stGenSetting.stScanMenuSetting.u8ATVManScanType == ATV_MAN_SCAN_TYPE_ONECH )
                {
                    bIsOneProgramDetected = msAPI_Tuner_IsOneProgramDetected();

                    if ( TRUE == bIsOneProgramDetected )
                    {
                        u8ManProcessStart = msAPI_Tuner_GetTuningProcessPercent();
                        enATVScanState = STATE_ATV_SCAN_SHOW_INFO;
                    }
                    else
                    {
                        u8ManProcess = msAPI_Tuner_GetTuningProcessPercent();

                        if ( stGenSetting.stScanMenuSetting.u8ATVManScanDir == ATV_MAN_SCAN_UP )
                        {
                            if(u8ManProcessStart == 0)
                            {
                                if(u8ManProcess == 99)
                                {
                                    enATVScanState = STATE_ATV_SCAN_SHOW_INFO;
                                }
                            }
                            else
                            {
                                if(u8ManProcess == (u8ManProcessStart-1))
                                {
                                    enATVScanState = STATE_ATV_SCAN_SHOW_INFO;
                                }
                            }
                        }
                        else
                        {
                            if(u8ManProcessStart == 0)
                            {
                                if(u8ManProcess == 1)
                                {
                                    enATVScanState = STATE_ATV_SCAN_SHOW_INFO;
                                }
                            }
                            else
                            {
                                if(u8ManProcessStart == 100)
                                {
                                    if (u8ManProcess == 0)
                                    {
                                        enATVScanState = STATE_ATV_SCAN_SHOW_INFO;
                                    }
                                }
                                else if (u8ManProcess == (u8ManProcessStart+1))
                                {
                                    enATVScanState = STATE_ATV_SCAN_SHOW_INFO;
                                }
                            }
                        }

                        // Blink <<< or >>>
                        bIsAutoScanInProgress = msAPI_Tuner_IsTuningProcessorBusy();

                      #if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_SCAN || (TV_SYSTEM == TV_NTSC) )
                        if(msAPI_ATV_GetDirectTuneFlag())
                        {
                            if ( FALSE == bIsAutoScanInProgress )
                            {
                                enATVScanState = STATE_ATV_SCAN_END;
                                break;
                            }
                            else
                                break;
                        }
                      #endif

                        if ( msAPI_Timer_DiffTimeFromNow( u32MonitorDiagnosticsSnrTimer )> DIAGNOSTICS_SNR_UPDATE_DELAY )
                        {
                            if ( stGenSetting.stScanMenuSetting.u8ATVManScanDir == ATV_MAN_SCAN_UP )
                            {
                              u32MonitorDiagnosticsSnrTimer = msAPI_Timer_GetTime0();
                            }
                            else
                            {
                              u32MonitorDiagnosticsSnrTimer = msAPI_Timer_GetTime0();
                            }
                        }
                      #if SCAN_FREQ_ATTIME
                        if ( PreATVScanPLL!= msAPI_Tuner_GetCurrentChannelPLL())
                        {
                            PreATVScanPLL = msAPI_Tuner_GetCurrentChannelPLL();
                            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_ATV_MANUAL_SCAN_SHOW_INFO);
                        }
                      #else
                         MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_ATV_MANUAL_SCAN_SHOW_INFO);
                      #endif

                        if ( FALSE == bIsAutoScanInProgress )
                        {
                            enATVScanState = STATE_ATV_SCAN_END;
                            break;
                        }
                    }
                }
            }
            break;


        case STATE_ATV_SCAN_SHOW_INFO:
            ATV_SCAN_DBINFO( printf( "STATE_ATV_SCAN_SHOW_INFO>>\n" ) );

            if ( stGenSetting.stScanMenuSetting.u8ScanType == SCAN_TYPE_AUTO )
            {
              //2013.07.02 sync chakra2/chakra2 M12 to sovle NTSC system scan OSD bug
              #if 0 // ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_SCAN || (TV_SYSTEM == TV_NTSC) )
                if(msAPI_ATV_IsProgramSearched(msAPI_ATV_GetCurrentProgramNumber()-1))
              #endif
                {
              #if ENABLE_SKIP_ATV_PROGRAMS_SAME_TO_DTV_LCN
                    if(ANT_AIR == msAPI_ATV_GetCurrentAntenna())
                    {
                        U16 u16Position;
                        U16 u16Number;
                        LOGICAL_CHANNEL_NUMBER LCN;
                        U16 u16TotalChCount = u8ScanAtvChNum + msAPI_CHPROC_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                        for(u16Position = 0; u16Position < u16TotalChCount; u16Position++)
                        {
                            u16Number = msAPI_CM_GetLogicalChannelNumber((MEMBER_SERVICETYPE)E_SERVICETYPE_DTV,u16Position);
                            LCN.wLCN = (WORD)u16Number;
                            if (LCN.stLCN.bPhysicalChannel == U16CurATVNumber)
                            {
                                msAPI_ATV_SkipProgram(msAPI_ATV_GetCurrentProgramNumber(), TRUE);
                                break;
                            }
                        }
                    }
              #endif
                    u8ScanAtvChNum++;
                }
                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_REPAINT_AUTOTUNING_PROGRESS);
                enATVScanState = STATE_ATV_SCAN_WAIT;
            }
            else
            {
                // Update OSD to show station name, medium(CATV/Air), channel number and station name about detected channel.
                enATVScanState = STATE_ATV_SCAN_END;

            #if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_SCAN || (TV_SYSTEM == TV_NTSC) )
               if(msAPI_ATV_GetDirectTuneFlag() == FALSE)
            #endif
                {
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_ATV_MANUAL_SCAN_END);
                }
            }
            break;

        case STATE_ATV_SCAN_END:
        case STATE_ATV_SCAN_EXIT_2_MAIN_MENU:
            {
                AUDIOSTANDARD_TYPE u8CurAudioSystem;
                MApp_ATV_Scan_End();

            #if ENABLE_SBTVD_SCAN
                if(IS_SBTVD_APP)
                {
                    stGenSetting.stScanMenuSetting.u8Antenna = msAPI_ATV_GetCurrentAntenna();
                }
            #endif

                if ( stGenSetting.stScanMenuSetting.u8ScanType == SCAN_TYPE_AUTO )
                {
                    msAPI_ATV_SetCurrentProgramNumber(msAPI_ATV_GetFirstProgramNumber(FALSE));

                        if ( enATVScanState == STATE_ATV_SCAN_EXIT_2_MAIN_MENU ||(eTuneType == OSD_TUNE_TYPE_ATV_ONLY))
                        {
                            enATVScanRetVal =EXIT_GOTO_PREVIOUS;
                            //msAPI_ATV_SetCurrentProgramNumber(msAPI_ATV_GetFirstProgramNumber(FALSE));
                            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_SIF, E_AUDIOMUTESOURCE_ATV);
                            //BY 20090406 msAPI_VD_AdjustVideoFactor(E_ADJUST_VIDEOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_TUNER);
                            msAPI_AVD_TurnOffAutoAV();
                            msAPI_Tuner_ChangeProgram();
                            //msAPI_VD_ClearSyncCheckCounter();
                            msAPI_AVD_ClearAspectRatio();
                            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_INTERNAL_2_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                            MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_AUTO_SCAN_FINISH);
                            ATV_SCAN_DBINFO( printf( "STATE_ATV_SCAN_EXIT_2_MAIN_MENU>>\n" ) );

                        #if ENABLE_TTX
                            msAPI_TTX_VBIAcquireEnable(TRUE);
                        #endif
                        }
                        else
                        {
                        #if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_SCAN || (TV_SYSTEM == TV_NTSC) )
                            if(msAPI_ATV_GetCurrentAntenna() == ANT_CATV)
                            {
                                enATVScanRetVal =EXIT_GOTO_PREVIOUS;
                                //MApp_UiMenu_ExecuteKeyEvent( MIA_FINISH_SCAN );

                                //msAPI_ATV_SetCurrentProgramNumber(msAPI_ATV_GetFirstProgramNumber(FALSE));
                              #if ENABLE_SBTVD_SCAN
                                MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_AUTO_SCAN_FINISH);
                              #endif

                                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_SIF, E_AUDIOMUTESOURCE_ATV);
                                //BY 20090406 msAPI_VD_AdjustVideoFactor(E_ADJUST_VIDEOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_TUNER);
                                msAPI_AVD_TurnOffAutoAV();
                                msAPI_Tuner_ChangeProgram();
                                //msAPI_VD_ClearSyncCheckCounter();
                                msAPI_AVD_ClearAspectRatio();

                                // to prevent sound when analog tuning is finished
                                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_INTERNAL_2_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);

                            #if ENABLE_PRINT_SCAN_TIME
                                printf(">>>>>>> Scan time = %d sec\n", msAPI_Timer_DiffTimeFromNow(_u32ScanTime)/1000);
                            #endif

                            }
                            else
                        #endif
                            {
                            #if (SCAN_TEST_MODE_ENABLE==1)
                                if (AutoScanTest.u8State==TEST_MODE_ATV_SCAN_STATE_VERIFY)
                                {
                                    AutoScanTest.u16VerifyCount++;
                                    if (AutoScanTest.u16VerifyCount<10)
                                    {
                                        enATVScanState = STATE_ATV_SCAN_INIT;
                                        return enATVScanRetVal;
                                    }
                                    else
                                    {
                                        AutoScanTest.u8State=TEST_MODE_ATV_SCAN_STATE_DISABLE;
                                        AutoScanTest.u16VerifyCount=0;
                                        AutoScanTest.u16Total_Lost_Channel=0;
                                        AutoScanTest.u16Total_Ghost_Channel=0;
                                    }
                                }

                             #if FRONTEND_TUNER_TYPE == XUGUANG_TDQ_6FT_W116H
                                enATVScanRetVal = EXIT_GOTO_PREVIOUS;//EXIT_ATV_SCAN_TRAN_PREVIOUS;
                             #else
                                if (eTuneType == OSD_TUNE_TYPE_ATV_ONLY)
                                {
                                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_AUTO_SCAN_FINISH);
                                }
                              #if (ENABLE_DTV)
                                else
                                {
                                    if( UI_INPUT_SOURCE_TYPE!= UI_INPUT_SOURCE_DTV)
                                    {
                                        UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DTV;
                                        MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_TYPE, MAIN_WINDOW );
                                        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_INTERNAL_2_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                                    }

                                  #if ENABLE_SBTVD_SCAN
                                    if(IS_SBTVD_APP)
                                    {
                                        enATVScanRetVal =EXIT_GOTO_CATVSCAN;
                                    }
                                    else
                                  #endif
                                    {
                                        enATVScanRetVal =EXIT_GOTO_DTVSCAN;
                                    }
                                }
                              #endif // #if (ENABLE_DTV)
                             #endif // #if FRONTEND_TUNER_TYPE == XUGUANG_TDQ_6FT_W116H
                            #else // #if (SCAN_TEST_MODE_ENABLE==1)
                              #if (ENABLE_DTV)
                                MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);

                                // Change source to last DTV source ...
                            #if 0 // Refine
                                if( MApp_InputSrc_Get_UiInputSrcType() != MApp_InputSrc_Get_LastDtvUiSrcType() )
                                {
                                    //UI_INPUT_SOURCE_TYPE = MApp_InputSrc_Get_LastDtvUiSrcType();
                                    MApp_InputSrc_Set_UiInputSrcType( MApp_InputSrc_Get_LastDtvUiSrcType() );
                                    MApp_InputSource_ChangeInputSource(MAIN_WINDOW);
                                }
                            #else
                             #if(ENABLE_DVBC)
                                if(bOriginalSrcIsDvbc == TRUE) //original source is DVBC when do auto scan(ATV+DTV)
                                {
                                    if( UI_INPUT_SOURCE_TYPE != DTV_DVBC_USE_UI_INPUTSOURCE )
                                    {
                                        UI_INPUT_SOURCE_TYPE = DTV_DVBC_USE_UI_INPUTSOURCE;
                                        //MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_TYPE, MAIN_WINDOW );
                                        MApp_InputSource_ChangeInputSource(MAIN_WINDOW);
                                        //msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_INTERNAL_2_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                                    }
                                }
                                else
                             #endif
                             #if ENABLE_SBTVD_SCAN
                                if(!IS_SBTVD_APP)
                             #endif
                                {
                                    if( UI_INPUT_SOURCE_TYPE != SYS_DEFAULT_DTV_UI_INPUTSOURCE )
                                    {
                                        UI_INPUT_SOURCE_TYPE = SYS_DEFAULT_DTV_UI_INPUTSOURCE;
                                        //MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_TYPE, MAIN_WINDOW );
                                        MApp_InputSource_ChangeInputSource(MAIN_WINDOW);
                                        //msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_INTERNAL_2_MUTEON, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                                    }
                                }
                            #endif

                              #if (ENABLE_PIP)
                                if(MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
                                {
                                    MApp_ClosePIPSubWindowSource();
                                }
                              #endif

                              #if ENABLE_SBTVD_SCAN
                                if(IS_SBTVD_APP)
                                {
                                    enATVScanRetVal = EXIT_GOTO_CATVSCAN;
                                }
                                else
                              #endif
                                {
                                    MApp_InputSource_ChangeInputSource(MAIN_WINDOW );

                                    enATVScanRetVal = EXIT_GOTO_DTVSCAN;
                                }
                              #else // #if (ENABLE_DTV)
                                enATVScanRetVal =EXIT_GOTO_PREVIOUS;
                              #endif
                                //ATV_SCAN_DBINFO( printf( "STATE_ATV_SCAN_END>>\n" ) );
                              #endif // #if (SCAN_TEST_MODE_ENABLE==1)
                            }
                        }

                        if(bOriginalSrcIsDvbc==TRUE)
                        {
                           bOriginalSrcIsDvbc = FALSE;
                        }

                    }
                    else
                    {
                        enATVScanRetVal =EXIT_GOTO_PREVIOUS;
                        u8CurAudioSystem=msAPI_AUD_GetAudioStandard();
                        msAPI_AUD_SetAudioStandard(u8CurAudioSystem);
                        msAPI_Tuner_SetIF();
                    }
                enATVScanState = STATE_ATV_SCAN_INIT;
            }
            break;


        case STATE_ATV_SCAN_PAUSE:
            ATV_SCAN_DBINFO( printf( "STATE_ATV_SCAN_PAUSE>>\n" ) );
            if(fEndHalt)
            {
                ATV_SCAN_DBINFO( printf( "End Halt>>\n" ) );
                if(fReturnToPrevious)
                {
                    ATV_SCAN_DBINFO( printf( "Return to previous state>>\n" ) );
                    enATVScanState=enPreATVScanState;
                }
                else
                {
                    ATV_SCAN_DBINFO( printf( "Go to end>>\n" ) );
                        enATVScanState=STATE_ATV_SCAN_EXIT_2_MAIN_MENU;
                }
                fEndHalt=FALSE;
            }
            else
            {
                ATV_SCAN_DBINFO( printf( "Start halt>>\n" ) );
            }
            break;


        case STATE_ATV_SCAN_GOTO_STANDBY:
            MApp_ATV_Scan_End();
            if ( g_enScanType == SCAN_TYPE_AUTO )
            {
                MApp_ZUI_ACT_ShutdownOSD();
            }

            enATVScanRetVal =EXIT_GOTO_STANDBY;
            enATVScanState = STATE_ATV_SCAN_INIT;
            break;
    }

    return enATVScanRetVal;
}


//********************************************************************************
//            Static Functions
//********************************************************************************
static void MApp_ATV_Scan_ProcessUserInput( void )
{
    switch ( u8KeyCode )
    {
        case KEY_POWER:
        case DSC_KEY_PWROFF:
            enATVScanState = STATE_ATV_SCAN_GOTO_STANDBY;
            MApp_ZUI_ProcessKey(u8KeyCode);
            break;

        case KEY_EXIT:
        case KEY_MENU:
            if ( stGenSetting.stScanMenuSetting.u8ScanType == SCAN_TYPE_AUTO )
            {
                if(enATVScanState ==STATE_ATV_SCAN_PAUSE )
                {
                    u8KeyCode = NULL;
                }
                else
                {
                    if(eTuneType == OSD_TUNE_TYPE_ATV_ONLY)
                    {
                        u8KeyCode = KEY_EXIT;
                    }

                    fEndHalt = FALSE;
                    fReturnToPrevious = FALSE;
                    enPreATVScanState = enATVScanState;
                    enATVScanState = STATE_ATV_SCAN_PAUSE;
                    MApp_ZUI_ProcessKey(u8KeyCode);
                }
            }
            else if( stGenSetting.stScanMenuSetting.u8ScanType == SCAN_TYPE_MANUAL )
            {
                if(KEY_EXIT == u8KeyCode && msAPI_Tuner_IsTuningProcessorBusy())
                {
                    enATVScanState = STATE_ATV_SCAN_END;
                    MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_ATV_MANUAL_SCAN_END);
                }
            }
            u8KeyCode = NULL;
            break;

        case KEY_SELECT:
            if ( stGenSetting.stScanMenuSetting.u8ScanType == SCAN_TYPE_AUTO )
            {
                MApp_ZUI_ProcessKey(u8KeyCode);
            }
            break;

        case KEY_LEFT:
        case KEY_RIGHT:
            if ( stGenSetting.stScanMenuSetting.u8ScanType == SCAN_TYPE_AUTO )
            {
                MApp_ZUI_ProcessKey(u8KeyCode);
            }
            else if( stGenSetting.stScanMenuSetting.u8ScanType == SCAN_TYPE_MANUAL )
            {
                if(msAPI_Tuner_IsTuningProcessorBusy())
                {
                    if( (KEY_RIGHT == u8KeyCode && stGenSetting.stScanMenuSetting.u8ATVManScanDir == ATV_MAN_SCAN_DOWN) ||
                        (KEY_LEFT == u8KeyCode && stGenSetting.stScanMenuSetting.u8ATVManScanDir == ATV_MAN_SCAN_UP))
                    {
                        enATVScanState = STATE_ATV_SCAN_END;
                        MApp_ZUI_ACT_ExecuteWndAction(EN_EXE_ATV_MANUAL_SCAN_END);
                    }
                }
            }
            break;

            default:
                break;
    }
    u8KeyCode = KEY_NULL;
}


void MApp_ATV_SetATVScanState(EN_ATV_SCAN_STATE atvScanState)
{
    enATVScanState = atvScanState;
}


void MApp_ATV_ExitATVScanPauseState(void)
{
    fEndHalt = TRUE;
    enATVScanState = enPreATVScanState;
    fReturnToPrevious =TRUE;
}

void MApp_ATV_ExitATVScanPause2Menu(void)
{
    fEndHalt = TRUE;
    enPreATVScanState = STATE_ATV_SCAN_EXIT_2_MAIN_MENU;
    fReturnToPrevious =TRUE;

}

void MApp_ATV_ExitATVScanPause2ScanEnd(void)
{
    fEndHalt = TRUE;
    enPreATVScanState = STATE_ATV_SCAN_END;
    fReturnToPrevious =TRUE;
}




//******************************************************************************

#undef MAPP_ATV_SCAN_C

