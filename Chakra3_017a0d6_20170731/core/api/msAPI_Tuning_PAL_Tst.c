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
#include "msAPI_ATVSystem.h"
#include "msAPI_Timer.h"


#define VD_SIGNAL_SWING_ENABLE  1   //To improve ghost channel issue by signal swing
#if (VD_SIGNAL_SWING_ENABLE==1)
#define SCAN_SIG_SWING_THRESH   6   //6*16 = 96mV
#endif
#if TV_SCAN_PAL_SECAM_ONCE
#define FRANCE_SUPPORT_PAL_L                    1   //1:support, 0: don't support
static U16 _u16TunerPLL_LoopBG=0;
static U16 _u16TunerPLL_LoopLL=0;
#endif
#if defined(AUTO_TUNING_DEBUG)
static float _TunerPLLDbg(WORD wPLL);
#endif
static TUNING_STATUS _GetTuningStatus(void)
{
    AFC eFreqDev;

    eFreqDev = MDrv_IFDM_GetFreqDev();
    AUTO_TUNING_PRINT(printf("AFCWIN=%bx\n",eFreqDev));

    if ( eFreqDev == E_AFC_OUT_OF_AFCWIN )
    {
        return E_TUNING_STATUS_OUT_OF_AFCWIN;
    }
    // else if ( eFreqDev <= E_AFC_MINUS_12p5KHz || eFreqDev >= E_AFC_PLUS_12p5KHz )
    else if ( eFreqDev <= E_AFC_GOOD_MINUS_VALUE || eFreqDev >= E_AFC_GOOD_PLUS_VALUE )
    {
        return E_TUNING_STATUS_GOOD;
    }
    else if ( eFreqDev <= E_AFC_MINUS_162p5KHz )
    {
        return E_TUNING_STATUS_UNDER;
    }
    else if ( eFreqDev >= E_AFC_PLUS_162p5KHz )
    {
        return E_TUNING_STATUS_OVER;
    }
    else if ( eFreqDev <= E_AFC_BELOW_MINUS_187p5KHz )
    {
        return E_TUNING_STATUS_UNDER_MORE;
    }
    else if ( eFreqDev >= E_AFC_ABOVE_PLUS_187p5KHz )
    {
        return E_TUNING_STATUS_OVER_MORE;
    }
    else
    {
        /* ASSERT */
    }

}

/******************************************************************************/
///- This API is called by MApp_ATVProc_Handler to keep tuning work.
/// @param eState \b IN: AFT_EXT_STEP_PERIODIC - This enum is called by ATVProc_Handler(). Don't call any other place except ATVProc_Handler().
///                  IN: AFT_EXT_STEP_SEARCHALL - This enum will start auto-tuning from VHF low to UHF max.
///                  IN: AFT_EXT_STEP_SEARCHONETOUP - This enum will search up for next one available channel.
///                  IN: AFT_EXT_STEP_SEARCHONETODOWN - This enum will search up for next one available channel.
///                  IN: AFT_EXT_STEP_SEARCH_STOP - This enum will stop searching.
/******************************************************************************/


void _msAPI_Tuner_TuningProcessor(eAFTSTEP eState)
{
    static AUTO_SEARCH_TYPE eAutoSearchType;
    static U8 u8NoSyncCount;
    static U8 u8StartFrom;
    static U16 u16PreviosTunerPLL;
    U16 u16JumpDistance;
    TUNING_STATUS eTuningStatus;
    U16 u16VdStatus;
    AFC eFreqDev;
    U8 u8SortingPriority;
    #define MAX_AFT_UPPER_BOUND 30
    #define MAX_AFT_LOWER_THRES (MAX_AFT_UPPER_BOUND/3)
    #define MAX_AFT_UPPER_THRES (MAX_AFT_LOWER_THRES*2)
    #define MAX_AFT_GOOD_LEAK   (MAX_AFT_UPPER_BOUND/10)

#if TV_SCAN_PAL_SECAM_ONCE//Define for variable
    #define DOUBLE_CHECK_L_STATE_FALSE          0
    #define DOUBLE_CHECK_L_STATE_FOUND_BG       1
    #define DOUBLE_CHECK_L_STATE_FOUND_L        2
    //FRANCE_SUPPORT_DOUBLE_CHECK_L
    static BOOLEAN bDoubleCheckL;
    static U8 bDoubleCheckL_State;
    #define LL_BG_SWITCH        BIT0   // 1: for LL_BG switched
    #define LL_TO_BG_RDY        BIT1   // 1: for Rdy
    #define BG_TO_LL_RDY        BIT2   // 1: for Rdy
    #define CH_SCAN_RING_BG     BIT4   // 1: for over Max or under min on BG loop
    #define CH_SCAN_RING_LL     BIT5   // 1: for over Max or under min on LL loop
    #define CH_SCAN_RING        BIT6   // 1: for over Max or under min
    #define CH_DETECT           BIT7   // 1: for detected
    static U8 u8ScanOnceFlag = 0;
#endif

#if AUTO_SCAN_TIME_PRINT
    static U32 u32StartAutoTuningTime;
#endif

    if ( eState != AFT_EXT_STEP_PERIODIC )
    {
        if ( _eCurrentTuningState == AFT_IDLE && eState == AFT_EXT_STEP_SEARCHSTOP )
        {
            return;
        }

        if (eState == AFT_TUNING_SUSPEND)
        {
            _IsTuningSuspend = TRUE;
            return;
        }
        else if (eState == AFT_TUNING_RESUME)
        {
            _IsTuningSuspend = FALSE;
            return;
        }

        _eCurrentTuningState = eState;
        _u16TuningWaitTimer = 0;
        _IsTuningSuspend = FALSE;

    }

    if (_IsTuningSuspend == TRUE)
        return;

    if ( _eCurrentTuningState != AFT_IDLE )
    {
        if ( _IsTunerStable() == FALSE )
        {
            return;
        }
    }

    #if defined(AUTO_TUNING_DEBUG)
    {
        static eAFTSTEP _ePreTuningState;
        static U32 u32TuningStateTime;
        if ((_eCurrentTuningState != AFT_IDLE) && (_bIsLSearch))
        {
            AUTO_TUNING_PRINT(printf("Fre_LL=%3.2f ",(float)_TunerPLLDbg(_u16TunerPLL_LoopLL)));
            AUTO_TUNING_PRINT(printf("Fre_BG=%3.2f\n",(float)_TunerPLLDbg(_u16TunerPLL_LoopBG)));
        }
        if ( _eCurrentTuningState != AFT_IDLE )
        {
            AUTO_TUNING_PRINT( printf("TUN_STATE: 0x%BX -> 0x%BX (%lu)\n",
                                      _ePreTuningState,
                                      _eCurrentTuningState,
                                      msAPI_Timer_DiffTimeFromNow(u32TuningStateTime)) );
            AUTO_TUNING_PRINT(printf("Fre=%3.2f ",(float)_TunerPLLDbg(_u16TunerPLL)));
            AUTO_TUNING_PRINT(printf("PLL=%d\n",_u16TunerPLL));
            AUTO_TUNING_PRINT(printf("AudStd=0x%bx, IFstd=0x%bx\n",msAPI_AUD_GetAudioStandard(),MDrv_IFDM_GetIF()));
            _ePreTuningState = _eCurrentTuningState;
            u32TuningStateTime = msAPI_Timer_GetTime0();
        }
    }
    #endif

    switch ( _eCurrentTuningState )
    {
    case AFT_IDLE:
        _u16AFTIdleTimer++;

        if ( _u16AFTIdleTimer >= 0xFFF0 )
        {
            _u16AFTIdleTimer = 1;
        }

        if ( _u16UpdateStationNameTimer >= 1 )
        {
            _u16UpdateStationNameTimer--;

            if ( _u16UpdateStationNameTimer == 1 )
            {
#if ENABLE_TTX
                if ( TRUE != msAPI_TTX_GetStationNameFromTeletext(_sCurrentStationName, MAX_STATION_NAME, NULL) )
#endif
                {
                    msAPI_Tuner_ConvertMediumAndChannelNumberToString(_eMedium, _u8ChannelNumber, _sCurrentStationName);
                }

                _u16UpdateStationNameTimer = 0;
            }
        }

        if ( E_INPUT_SOURCE_ATV != msAPI_AVD_GetVideoSource() ||
             ( E_INPUT_SOURCE_ATV == msAPI_AVD_GetVideoSource() &&
               TRUE == msAPI_AVD_IsAutoAVActive(E_AUTOAV_SOURCE_ALL) )
           )
        {
            u8ScanAFTCount = 0;
            return;
        }

        if ( IS_RT_AFT_ENABLED == FALSE )
        {
            u8ScanAFTCount = 0;
            return;
        }

        if ( (_u16AFTIdleTimer % 19) == 0 )
        {
            if ( FALSE == _bIsAFTNeeded )
            {
                u8ScanAFTCount = 0;
                return;
            }

            if (_GetTuningStatus() == E_TUNING_STATUS_GOOD)
            {
                if (u8ScanAFTCount>=MAX_AFT_GOOD_LEAK)
                    u8ScanAFTCount -=MAX_AFT_GOOD_LEAK;
                else
                    u8ScanAFTCount =0;
                debugTuningPrint("u8ScanAFTCount=%bd\n", u8ScanAFTCount);
                return;
            }

            #if defined(AUTO_TUNING_DEBUG)
            {
                static eAFTSTEP _ePreTuningState;
                static U32 u32TuningStateTime;
                //if ( _eCurrentTuningState != AFT_IDLE )
                {
                    AUTO_TUNING_PRINT( printf("AFT_STATE: 0x%BX -> 0x%BX (%lu)\n",
                                              _ePreTuningState,
                                              _eCurrentTuningState,
                                              msAPI_Timer_DiffTimeFromNow(u32TuningStateTime)) );
                    AUTO_TUNING_PRINT(printf("BaseFre=%3.2f ",(float)_TunerPLLDbg(_u16RealtimeAFTBaseTunerPLL)));
                    AUTO_TUNING_PRINT(printf("CurFre=%3.2f \n",(float)_TunerPLLDbg(_u16TunerPLL)));
                    _ePreTuningState = _eCurrentTuningState;
                    u32TuningStateTime = msAPI_Timer_GetTime0();
                }
            }
            #endif
            eFreqDev = MDrv_IFDM_GetFreqDev();
            debugTuningPrint("AFT_1: 0x%bx\n", eFreqDev);
            debugTuningPrint("u8ScanAFTCount=%bd\n", u8ScanAFTCount);

            if (!(MDrv_AVD_GetStatus()&(VD_CHECK_SYNC_LOCKED|VD_CHECK_HSYNC_LOCKED)))
            {
                if (u8ScanAFTCount < MAX_AFT_UPPER_BOUND)
                    u8ScanAFTCount ++;
            }
            else
            {
                if (u8ScanAFTCount)
                    u8ScanAFTCount --;
            }

            if (u8ScanAFTCount>MAX_AFT_UPPER_THRES)
                u8ScanAFTFlag = 1;
            else if (u8ScanAFTCount<MAX_AFT_LOWER_THRES)
                u8ScanAFTFlag = 0;

            if (u8ScanAFTFlag)
            {
                if (_u16TunerPLL!=_u16RealtimeAFTBaseTunerPLL)
                {
                    _SetTunerPLL(_u16RealtimeAFTBaseTunerPLL);
                    msAPI_Tuner_SetIF();
                }
            }
            else if ((DIFFERENCE(_u16RealtimeAFTBaseTunerPLL,_u16TunerPLL) > TUNER_PLL_PLUS_2MHz ) &&
                     (eFreqDev == E_AFC_OUT_OF_AFCWIN))
            {
                if (_u16RealtimeAFTBaseTunerPLL>_u16TunerPLL)
                {
                    _u16TunerPLL = _u16RealtimeAFTBaseTunerPLL + TUNER_PLL_PLUS_2MHz;
                }
                else
                {
                    _u16TunerPLL = _u16RealtimeAFTBaseTunerPLL - TUNER_PLL_PLUS_2MHz;
                }
                _SetTunerPLL(_u16TunerPLL);
                msAPI_Tuner_SetIF();
            }
            else if ((DIFFERENCE(_u16RealtimeAFTBaseTunerPLL,_u16TunerPLL) <= TUNER_PLL_PLUS_2MHz))
            {
                eFreqDev = MDrv_IFDM_GetFreqDev();
                debugTuningPrint("AFT: 0x%bx\n", eFreqDev);

                //for ( i = 0; i <= TUNER_PLL_PLUS_4MHz ; i++ )
                {
                    switch ( eFreqDev )
                    {
                    case E_AFC_BELOW_MINUS_187p5KHz:
                        _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_187p5KHz) );
                        break;

                    case E_AFC_MINUS_162p5KHz:
                        _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_162p5KHz) );
                        break;

                    case E_AFC_MINUS_137p5KHz:
                        _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_137p5KHz) );
                        break;

                    case E_AFC_MINUS_112p5KHz:
                        _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_112p5KHz) );
                        break;

                    case E_AFC_MINUS_87p5KHz:
                        _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_87p5KHz) );
                        break;

                    case E_AFC_MINUS_62p5KHz:
                        _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_62p5KHz) );
                        break;

                    case E_AFC_MINUS_37p5KHz:
                        _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_37p5KHz) );
                        break;

                    case E_AFC_MINUS_12p5KHz:
                        return;

                    case E_AFC_PLUS_12p5KHz:
                        return;

                    case E_AFC_PLUS_37p5KHz:
                        _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_37p5KHz) );
                        break;

                    case E_AFC_PLUS_62p5KHz:
                        _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_62p5KHz) );
                        break;

                    case E_AFC_PLUS_87p5KHz:
                        _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_87p5KHz) );
                        break;

                    case E_AFC_PLUS_112p5KHz:
                        _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_112p5KHz) );
                        break;

                    case E_AFC_PLUS_137p5KHz:
                        _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_137p5KHz) );
                        break;

                    case E_AFC_PLUS_162p5KHz:
                        _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_162p5KHz) );
                        break;

                    case E_AFC_ABOVE_PLUS_187p5KHz:
                        _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_187p5KHz) );
                        break;

                    default://E_AFC_OUT_OF_AFCWIN
                        _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_0p25MHz) );
                        break;
                    }
                    msAPI_Tuner_SetIF();
                }
            }
            #if 0
            else
            {
                if ( ((_u16AFTIdleTimer % (19 * 18)) == 0) ||
                     (msAPI_AVD_IsSyncLocked() == TRUE) )
                {
                    debugTuningPrint("One Channel AFT in Real Time\n", 0);

                    _SetTunerPLL(_u16RealtimeAFTBaseTunerPLL);
                    msAPI_Tuner_SetIF();
                    _OneChannelAFT();
                }
                else
                {
                    if ( TUNER_PLL_PLUS_1MHz < DIFFERENCE(_u16RealtimeAFTBaseTunerPLL,_u16TunerPLL) )
                    {
                        if ( _u16RealtimeAFTBaseTunerPLL > _u16TunerPLL )
                        {
                            _SetTunerPLL( _u16TunerPLL + TUNER_PLL_PLUS_1MHz );
                        }
                        else
                        {
                            _SetTunerPLL( _u16TunerPLL + TUNER_PLL_MINUS_1MHz );
                        }
                    }
                    else
                    {
                        if ( _u16RealtimeAFTBaseTunerPLL > _u16TunerPLL )
                        {
                            _SetTunerPLL( _u16RealtimeAFTBaseTunerPLL + TUNER_PLL_PLUS_2p25MHz );
                        }
                        else
                        {
                            _SetTunerPLL( _u16RealtimeAFTBaseTunerPLL + TUNER_PLL_MINUS_2p25MHz );
                        }
                    }
                }
            }
            #endif
        }
        return;

    case AFT_EXT_STEP_SEARCHALL:

        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE,E_AUDIO_INTERNAL_2_MUTEON,E_AUDIOMUTESOURCE_ATV);

        msAPI_Timer_Delayms(DELAY_FOR_ENTERING_MUTE);

        _eCurrentTuningState = AFT_CHECKSYNC;

        eAutoSearchType = E_AUTO_SEARCH_TYPE_ALLWAYUP;

        u8StartFrom = msAPI_ATV_GetCurrentProgramNumber();

        // msAPI_VD_EnableAutoGainControl(TRUE); // <-<<< USELESS

        if ( eAutoSearchType == E_AUTO_SEARCH_TYPE_ALLWAYUP )
        {
            _SetTunerPLL(VHF_LOWMIN_PLL);
        }
        else
        {
            _SetTunerPLL(UHF_MAX_PLL);
        }

#if (TV_SCAN_PAL_SECAM_ONCE )//Sync SECAM-L and BG Base
        //FRANCE_SUPPORT_DOUBLE_CHECK_L
        bDoubleCheckL = FALSE;
        bDoubleCheckL_State=DOUBLE_CHECK_L_STATE_FALSE;
        u8ScanOnceFlag = 0;
        _u16TunerPLL_LoopLL = _u16TunerPLL;
        _u16TunerPLL_LoopBG = _u16TunerPLL;
#endif
        _bIsAFTNeeded = TRUE;

        msAPI_AVD_TurnOffAutoAV();
#if ENABLE_TTX
        msAPI_TTX_ResetAcquisition();
#endif

#if 0//TV_SCAN_PAL_SECAM_ONCE
        msAPI_AUD_SetAudioStandard((AUDIOSTANDARD_TYPE)E_AUDIOSTANDARD_L);
#else
        if (_bIsLSearch)
        {
            msAPI_AUD_SetAudioStandard((AUDIOSTANDARD_TYPE)E_AUDIOSTANDARD_L);
        }
        else
        {
            msAPI_AUD_SetAudioStandard((AUDIOSTANDARD_TYPE)E_AUDIOSTANDARD_BG);
        }
#endif
        msAPI_Tuner_SetIF();

        _u8TVScanStepDownCount = 0;
        _bIsSpeedUp = TRUE;

        msAPI_AVD_SetHsyncDetectionForTuning(TRUE);

#if AUTO_SCAN_TIME_PRINT
            u32StartAutoTuningTime = msAPI_Timer_GetTime0();
#endif

        break;

    case AFT_EXT_STEP_SEARCHONETOUP:

        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE,E_AUDIO_INTERNAL_2_MUTEON,E_AUDIOMUTESOURCE_ATV);

        msAPI_Timer_Delayms(DELAY_FOR_ENTERING_MUTE);

        _eCurrentTuningState = AFT_CHECKSYNC;

        eAutoSearchType = E_AUTO_SEARCH_TYPE_ONETOUP;

        if ( msAPI_AVD_IsAutoAVActive(E_AUTOAV_SOURCE_ALL) == TRUE )
        {
            msAPI_AVD_TurnOffAutoAV();
            msAPI_AVD_WaitForVideoSyncLock();
            msAPI_AVD_DetectVideoStandard(OPERATIONMETHOD_MANUALLY);
        }

        // msAPI_VD_EnableAutoGainControl(TRUE); // <-<<< USELESS
#if ENABLE_TTX
        msAPI_TTX_ResetAcquisition();
#endif

#if (VD_SYNC_CRITERION_CONFIG_ENABLE)
        if ( TRUE == msAPI_Tuner_VD_IsSyncDetected(SYNC_DETECTED_BASE_NUM, SYNC_DETECTED_PASS_NUM))
#else
        if ( TRUE == msAPI_AVD_IsSyncLocked())
#endif

        {
            if ( msAPI_AUD_GetAudioStandard() == E_AUDIOSTANDARD_M )
            {
                _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_4MHz) );
            }
            else
            {
#if TV_SCAN_PAL_SECAM_ONCE
                if (_bIsLSearch)
                {
                    if ( _CheckLPrimeBoundary() == TRUE )
                        _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_2p75MHz) );
                    else
                        _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_5p25MHz) );
                }
                else
#endif
                {
                    _SetTunerPLL( PLLSTEP(TUNER_PLL_NEXT_CHANNEL_JUMP) );
                }
            }
        }
#if TV_SCAN_PAL_SECAM_ONCE
        if (_bIsLSearch)
        {
            //FRANCE_SUPPORT_DOUBLE_CHECK_L
            bDoubleCheckL = FALSE;
            bDoubleCheckL_State=DOUBLE_CHECK_L_STATE_FALSE;
            u8ScanOnceFlag = 0;
            _u16TunerPLL_LoopLL = _u16TunerPLL;
            _u16TunerPLL_LoopBG = _u16TunerPLL;
        }
#endif
        _bIsAFTNeeded = TRUE;
        msAPI_Tuner_SetIF();
        msAPI_AVD_SetHsyncDetectionForTuning(TRUE);
        break;

    case AFT_EXT_STEP_SEARCHONETODOWN:

        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE,E_AUDIO_INTERNAL_2_MUTEON,E_AUDIOMUTESOURCE_ATV);

        msAPI_Timer_Delayms(DELAY_FOR_ENTERING_MUTE);

        _eCurrentTuningState = AFT_CHECKSYNC;

        eAutoSearchType = E_AUTO_SEARCH_TYPE_ONETODOWN;

        if ( msAPI_AVD_IsAutoAVActive(E_AUTOAV_SOURCE_ALL) == TRUE )
        {
            msAPI_AVD_TurnOffAutoAV();
            msAPI_AVD_WaitForVideoSyncLock();
            msAPI_AVD_DetectVideoStandard(OPERATIONMETHOD_MANUALLY);
        }

        // msAPI_VD_EnableAutoGainControl(TRUE); // <-<<< USELESS
#if ENABLE_TTX
        msAPI_TTX_ResetAcquisition();
#endif

#if (VD_SYNC_CRITERION_CONFIG_ENABLE)
        if ( TRUE == msAPI_Tuner_VD_IsSyncDetected(SYNC_DETECTED_BASE_NUM, SYNC_DETECTED_PASS_NUM))
#else
        if ( TRUE == msAPI_AVD_IsSyncLocked())
#endif
        {
            if ( msAPI_AUD_GetAudioStandard() == E_AUDIOSTANDARD_M )
            {
                _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_4MHz) );
            }
            else
            {
#if TV_SCAN_PAL_SECAM_ONCE
                if (_bIsLSearch)
                {
                    if ( _CheckLPrimeBoundary() == TRUE )
                        _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_2p75MHz) );
                    else
                        _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_5p25MHz) );
                }
                else
#endif
                {
                    _SetTunerPLL( PLLSTEP((TUNER_PLL_NEXT_CHANNEL_JUMP*(-1))) );
                }
            }
        }
#if TV_SCAN_PAL_SECAM_ONCE
        if (_bIsLSearch)
        {
            //FRANCE_SUPPORT_DOUBLE_CHECK_L
            bDoubleCheckL = FALSE;
            bDoubleCheckL_State=DOUBLE_CHECK_L_STATE_FALSE;
            u8ScanOnceFlag = 0;
            _u16TunerPLL_LoopLL = _u16TunerPLL;
            _u16TunerPLL_LoopBG = _u16TunerPLL;
        }
#endif
        _bIsAFTNeeded = TRUE;
        msAPI_Tuner_SetIF();
        msAPI_AVD_SetHsyncDetectionForTuning(TRUE);
        break;
    case AFT_CHECKSYNC:
        u8NoSyncCount = 0;

        u16VdStatus = msAPI_AVD_CheckStatusLoop();

        if ( u16VdStatus & VD_CHECK_HSYNC_LOCKED )
        {
            u16PreviosTunerPLL = _u16TunerPLL;
            _eCurrentTuningState = AFT_TUNING;
            _u8TVScanStepDownCount = 3;
            //_u16TuningWaitTimer = 12; // <-<<<
            _bIsSpeedUp = FALSE;
        }
        else // No Lock
    case AFT_SIGNAL_WEAK:
        {
#if (VD_SIGNAL_SWING_ENABLE==1)
        MDrv_WriteByteMask (BK_AFEC_D8, 0 << 4, BITMASK(7:4));
#endif
#if TV_SCAN_PAL_SECAM_ONCE
            if (_bIsLSearch)
            {
                if (u8ScanOnceFlag&CH_SCAN_RING) // over UHF_MAX_PLL or under VHF_LOWMIN_PLL
                {
                    if (E_AUDIOSTANDARD_L == msAPI_AUD_GetAudioStandard())
                    {
                        u8ScanOnceFlag  |= LL_TO_BG_RDY;
                        if (u8ScanOnceFlag & CH_SCAN_RING_BG)
                            u8ScanOnceFlag  &= ~(CH_SCAN_RING_BG|CH_SCAN_RING_LL);
                        else
                            u8ScanOnceFlag  |= CH_SCAN_RING_LL;
                    }
                    else /*if (E_AUDIOSTANDARD_BG == msAPI_AUD_GetAudioStandard()) */
                    {
                        u8ScanOnceFlag  |= BG_TO_LL_RDY;
                        if (u8ScanOnceFlag & CH_SCAN_RING_LL)
                            u8ScanOnceFlag &= ~(CH_SCAN_RING_BG|CH_SCAN_RING_LL);
                        else
                            u8ScanOnceFlag |= CH_SCAN_RING_BG;
                    }
                }
                else if ( eAutoSearchType == E_AUTO_SEARCH_TYPE_ALLWAYDOWN ||
                          eAutoSearchType == E_AUTO_SEARCH_TYPE_ONETODOWN )
                {
                    //if (!(u8ScanOnceFlag&CH_SCAN_RING))
                    {
                        if ((E_AUDIOSTANDARD_L == msAPI_AUD_GetAudioStandard())&&
                            (_u16TunerPLL <=_u16TunerPLL_LoopBG)&&
                            (_u16TunerPLL_LoopLL -_u16TunerPLL > TUNER_PLL_PLUS_3MHz)&&
                            ((u8ScanOnceFlag & CH_SCAN_RING_BG)==0))
                            u8ScanOnceFlag  |= LL_TO_BG_RDY;
                        else if ((E_AUDIOSTANDARD_L != msAPI_AUD_GetAudioStandard())&&
                            (_u16TunerPLL <=_u16TunerPLL_LoopLL)&&
                            (_u16TunerPLL_LoopBG -_u16TunerPLL > TUNER_PLL_PLUS_3MHz)&&
                            ((u8ScanOnceFlag & CH_SCAN_RING_LL)==0))
                            u8ScanOnceFlag  |= BG_TO_LL_RDY;
                    }
                }
                else if ( eAutoSearchType == E_AUTO_SEARCH_TYPE_ALLWAYUP ||
                          eAutoSearchType == E_AUTO_SEARCH_TYPE_ONETOUP )
                {
                    //if (!(u8ScanOnceFlag&CH_SCAN_RING))
                    {
                        if ((E_AUDIOSTANDARD_L == msAPI_AUD_GetAudioStandard())&&
                            (_u16TunerPLL >=_u16TunerPLL_LoopBG)&&
                            (_u16TunerPLL-_u16TunerPLL_LoopLL > TUNER_PLL_PLUS_3MHz)&&
                            ((u8ScanOnceFlag & CH_SCAN_RING_BG)==0))
                            u8ScanOnceFlag  |= LL_TO_BG_RDY;
                        else if ((E_AUDIOSTANDARD_L != msAPI_AUD_GetAudioStandard())&&
                            (_u16TunerPLL >=_u16TunerPLL_LoopLL)&&
                            (_u16TunerPLL-_u16TunerPLL_LoopBG > TUNER_PLL_PLUS_3MHz)&&
                            ((u8ScanOnceFlag & CH_SCAN_RING_LL)==0))
                                u8ScanOnceFlag  |= BG_TO_LL_RDY;
                    }
                }
                if (u8ScanOnceFlag & LL_TO_BG_RDY)
                {
                    MApi_AUDIO_SIF_SetStandard(E_AUDIOSTANDARD_BG);
                    _u16TunerPLL_LoopLL=_u16TunerPLL;
                    _u16TunerPLL=_u16TunerPLL_LoopBG;
                    _SetTunerPLL(_u16TunerPLL);
                    msAPI_Tuner_SetIF();
                    L_SEARCH_DBG(printf("\nchange PAL"));
                    u8ScanOnceFlag |= LL_BG_SWITCH;
                    u8ScanOnceFlag &= ~(LL_TO_BG_RDY|CH_SCAN_RING);
                }
                else if (u8ScanOnceFlag & BG_TO_LL_RDY)
                {
                    MApi_AUDIO_SIF_SetStandard(E_AUDIOSTANDARD_L);
                    _u16TunerPLL_LoopBG=_u16TunerPLL;
                    _u16TunerPLL=_u16TunerPLL_LoopLL;
                    _SetTunerPLL(_u16TunerPLL);
                    msAPI_Tuner_SetIF();
                    L_SEARCH_DBG(printf("\nchange L"));
                    u8ScanOnceFlag |= LL_BG_SWITCH;
                    u8ScanOnceFlag &= ~(BG_TO_LL_RDY|CH_SCAN_RING);
                }
                if (_eCurrentTuningState==AFT_SIGNAL_WEAK)
                {
                    if ((u8ScanOnceFlag&CH_DETECT)&&(!(u8ScanOnceFlag&LL_BG_SWITCH)))
                        _eCurrentTuningState = AFT_CHECKSYNC;
                    else
                        _eCurrentTuningState = AFT_JUMPNEAR;
                }
                else
                    _eCurrentTuningState = AFT_JUMPNEAR;
                u8ScanOnceFlag &= ~(CH_DETECT|LL_BG_SWITCH);
            }
            else
#endif
            {
                if ( _u8TVScanStepDownCount == 0 )
                {
                    _eCurrentTuningState = AFT_JUMPNEAR;
                }
                else
                {
                    _eCurrentTuningState = AFT_JUMPNEARHALF;
                    _u8TVScanStepDownCount--;
                }
                _bIsSpeedUp = TRUE;
            }
        }
        break;

    case AFT_JUMPNEAR:
    case AFT_JUMPNEARHALF:
#if (VD_SIGNAL_SWING_ENABLE==1)
        MDrv_WriteByteMask (BK_AFEC_D8, 0 << 4, BITMASK(7:4));
#endif
        if( _eCurrentTuningState == AFT_JUMPNEARHALF )
        {
            u16JumpDistance = TUNER_PLL_PLUS_0p5MHz;
        }
        else
        {
          #if(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)
            u16JumpDistance = TUNER_PLL_PLUS_1MHz;//TUNER_PLL_PLUS_1p5MHz;
          #else
            u16JumpDistance = TUNER_PLL_PLUS_1p5MHz;
          #endif
        }
#if TV_SCAN_PAL_SECAM_ONCE//To check Step
        if (_bIsLSearch)
        {
            if ( _CheckLPrimeBoundary() == TRUE )
            {
                if( _eCurrentTuningState == AFT_JUMPNEARHALF )
                    u16JumpDistance = TUNER_PLL_PLUS_0p2MHz;
                else
                    u16JumpDistance = TUNER_PLL_PLUS_0p75MHz;
            }

        }
#else
        if ( _IsLPrime() == TRUE )
        {
            if( _eCurrentTuningState == AFT_JUMPNEARHALF )
                u16JumpDistance = TUNER_PLL_PLUS_0p2MHz;
            else
                u16JumpDistance = TUNER_PLL_PLUS_0p75MHz;
        }
#endif

        if ( eAutoSearchType == E_AUTO_SEARCH_TYPE_ALLWAYDOWN ||
             eAutoSearchType == E_AUTO_SEARCH_TYPE_ONETODOWN )
        {
            _SetTunerPLL( PLLSTEP( (u16JumpDistance*(-1)) ) );
        }
        else
        {
            _SetTunerPLL( PLLSTEP(u16JumpDistance) );
        }
        msAPI_Tuner_SetIF();
        _eCurrentTuningState = AFT_CHECKSYNC;
        break;

    case AFT_TUNING:
        u16VdStatus = msAPI_AVD_CheckStatusLoop();
        eTuningStatus = _GetTuningStatus();

        AUTO_TUNING_PRINT(printf("Tuning: 0x%04X, 0x%02BX\n", u16VdStatus, eTuningStatus));

        if ( (eTuningStatus != E_TUNING_STATUS_OUT_OF_AFCWIN) &&
             (u16VdStatus & VD_CHECK_HSYNC_LOCKED) )
        {
            switch ( eTuningStatus )
            {
            case E_TUNING_STATUS_GOOD:
                if ( IS_SYSTEM_L_ENABLED == FALSE
            #if TV_SCAN_PAL_SECAM_ONCE
                    && (!_bIsLSearch)
            #endif
                   )
                {
                    if( msAPI_AVD_GetVerticalFreq() == E_VIDEO_FQ_50Hz )
                    {
                        if( E_AUDIOSTANDARD_M == MApi_AUDIO_SIF_ConvertToBasicAudioStandard(msAPI_AUD_GetAudioStandard()) )
                        {
                            msAPI_AUD_SetAudioStandard(E_AUDIOSTANDARD_BG);
                            msAPI_Tuner_SetIF();
                        }
                    }
                    else if( msAPI_AVD_GetVerticalFreq() == E_VIDEO_FQ_60Hz )
                    {
                        if( E_AUDIOSTANDARD_M != MApi_AUDIO_SIF_ConvertToBasicAudioStandard(msAPI_AUD_GetAudioStandard()) )
                        {
                            msAPI_AUD_SetAudioStandard(E_AUDIOSTANDARD_M);
                            msAPI_Tuner_SetIF();
                        }
                    }
                }
#if (VD_SIGNAL_SWING_ENABLE==1)
                //To avoid the false channel due to signal swing  < 96mv
                MDrv_WriteByteMask (BK_AFEC_D8, SCAN_SIG_SWING_THRESH << 4, BITMASK(7:4));
#endif
                MApi_AUDIO_SIF_StartAutoStandardDetection();
                msAPI_AVD_StartAutoStandardDetection();
#if ENABLE_TTX
                msAPI_TTX_ResetAcquisition();
#endif
#if TV_SCAN_PAL_SECAM_ONCE
                if (_bIsLSearch)
                {
                    _eCurrentTuningState = AFT_L_SEARCH_CHECK;
                    return;
                }
#endif
                _u16AFTIdleTimer = 0;
                _eCurrentTuningState = AFT_DETECTVIDEO; // AFT_SHOWTIME1;

                return; // <-<<<

            case E_TUNING_STATUS_OVER:
                _SetTunerPLL( PLLSTEP(-1) );
                break;

            case E_TUNING_STATUS_UNDER:
                _SetTunerPLL( PLLSTEP(1) );
                break;

            case E_TUNING_STATUS_OVER_MORE:
                _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_0p25MHz) );
                break;

            case E_TUNING_STATUS_UNDER_MORE:
            #if(FRONTEND_TUNER_TYPE == NXP_TD1616EF_TUNER)
                _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_0p5MHz) );
            #else
                _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_0p25MHz) );
            #endif
                break;

            default:
                /* ASSERT */
                break;
            }

            if ( (u8NoSyncCount++) >= 20 )
            {
                _eCurrentTuningState = AFT_SIGNAL_WEAK;
            }
        }
        else if ( (u16VdStatus != VD_CHECK_RESET_ON) && (u8NoSyncCount != 0) ) // (u8NoSyncCount != 0) <- i.e. ever lock AFC win
        {
            AUTO_TUNING_PRINT(printf("#"));

            if ( eAutoSearchType == E_AUTO_SEARCH_TYPE_ALLWAYDOWN ||
                 eAutoSearchType == E_AUTO_SEARCH_TYPE_ONETODOWN )
            {
                _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_0p25MHz) );
            }
            else
            {
                _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_0p25MHz) );
            }
        }
        else
        {
            AUTO_TUNING_PRINT(printf("@"));
            _eCurrentTuningState = AFT_JUMPNEARHALF;
        }

        if ( _eCurrentTuningState == AFT_JUMPNEARHALF )
        {
            if ( eAutoSearchType == E_AUTO_SEARCH_TYPE_ALLWAYDOWN ||
                 eAutoSearchType == E_AUTO_SEARCH_TYPE_ONETODOWN )
            {
                if ( u16PreviosTunerPLL < _u16TunerPLL )
                {
                    _SetTunerPLL( u16PreviosTunerPLL );
                }
            }
            else
            {
                if ( u16PreviosTunerPLL > _u16TunerPLL )
                {
                    _SetTunerPLL( u16PreviosTunerPLL );
                }
            }
        }

        break;
#if TV_SCAN_PAL_SECAM_ONCE
    case AFT_L_SEARCH_CHECK:
        {
            AVD_VideoStandardType eStandard = msAPI_AVD_GetResultOfAutoStandardDetection();
            AUDIOSTANDARD_TYPE eAudioType = msAPI_AUD_GetAudioStandard();
            U8                 bIsChanged;

            bIsChanged = FALSE;
            L_SEARCH_DBG(printf("\nAudio = %x, Video=%x", (int)eAudioType, (int)eStandard));

            if (eStandard == E_VIDEOSTANDARD_SECAM)
            {
                L_SEARCH_DBG(printf("\nIt's SECAM\n"));
            }
            else
            {   // in L/L'-Loop, if videostd = pal, force to BG(pal-bg), so cannot support pal-l
                if (eAudioType != E_AUDIOSTANDARD_BG)
                {
                  #if (FRANCE_SUPPORT_PAL_L)
                    L_SEARCH_DBG(printf("\nIt's PAL-L\n"));
                  #else
                    // since found PAL-L and don't support, so need to do as below
                    L_SEARCH_DBG(printf("\nIt's PAL-L but don't support\n"));
                    if ( _IsLPrime() == TRUE )
                        _u16TunerPLL += TUNER_PLL_PLUS_2MHz; // need to fine-tune
                    else
                        _u16TunerPLL += TUNER_PLL_PLUS_3MHz; // need to fine-tune
                    _eCurrentTuningState = AFT_SIGNAL_WEAK;
                    #if (VD_SIGNAL_SWING_ENABLE==1)
                    MDrv_WriteByteMask (BK_AFEC_D8, 0 << 4, BITMASK(7:4));
                    #endif
                    return;
                  #endif
                }
                L_SEARCH_DBG(printf("\nIt's PAL\n"));
            }
            if (bIsChanged)
            {
                msAPI_Tuner_SetIF();
                MApi_AUDIO_SIF_StartAutoStandardDetection();
                msAPI_AVD_StartAutoStandardDetection();
#if ENABLE_TTX
                msAPI_TTX_ResetAcquisition();
#endif
            }

        }
        _u16AFTIdleTimer = 0;
        _eCurrentTuningState = AFT_DETECTVIDEO; // AFT_SHOWTIME1;

        return; // <-<<<
#endif
    case AFT_DETECTVIDEO:
        if ( MDrv_AVD_GetStatus() & VD_CHECK_STATUS_RDY )
        {
            msAPI_AVD_GetResultOfAutoStandardDetection();
            _u16AFTIdleTimer = 0;
            _eCurrentTuningState = AFT_SHOWTIME2;
            _bIsPreProgramDetected = TRUE;
        }
        break;

    case AFT_SHOWTIME2:
        _u16AFTIdleTimer++;

        if ( _u16AFTIdleTimer >= ATVSCAN_AUDIO_WAIT_TIME)
        {
#if (VD_SYNC_CRITERION_CONFIG_ENABLE)
            if ( msAPI_Tuner_VD_IsSyncLocked(SYNC_LOCKED_BASE_NUM,SYNC_LOCKED_PASS_NUM) == TRUE )
#else
            if ( msAPI_AVD_IsSyncLocked())
#endif
            {
                _eCurrentTuningState = AFT_DETECTAUDIO;
            }
            else
            {
                debugTuningPrint("-Unlocked Sync: %dMHz", msAPI_CFT_ConvertPLLtoIntegerOfFrequency(_u16TunerPLL));//, msAPI_CFT_ConvertPLLtoFractionOfFrequency(_u16TunerPLL));
                L_SEARCH_DBG(printf("Hsync lost, maybe cause by signal swing too small\n"));

                if ( eAutoSearchType == E_AUTO_SEARCH_TYPE_ALLWAYDOWN ||
                     eAutoSearchType == E_AUTO_SEARCH_TYPE_ONETODOWN )
                {
                    if ( u16PreviosTunerPLL < _u16TunerPLL )
                    {
                        _SetTunerPLL(u16PreviosTunerPLL);
                    }
                }
                else
                {
                    if ( _u16TunerPLL < u16PreviosTunerPLL )
                    {
                        _SetTunerPLL(u16PreviosTunerPLL);
                    }
                }

                _eCurrentTuningState = AFT_JUMPNEARHALF;
            }
#if (VD_SIGNAL_SWING_ENABLE==1)
            MDrv_WriteByteMask (BK_AFEC_D8, 0 << 4, BITMASK(7:4));
#endif
        }
        _bIsOneProgramDetected = FALSE;
        break;

    case AFT_DETECTAUDIO:
        msAPI_AUD_GetResultOfAutoStandardDetection();
        _eCurrentTuningState = AFT_MEMORIZEPRDATA;
        break;

    case AFT_MEMORIZECHDATA:
        break;

    case AFT_MEMORIZEPRDATA:
        switch ( eAutoSearchType )
        {
        case E_AUTO_SEARCH_TYPE_ALLWAYUP:
        case E_AUTO_SEARCH_TYPE_ALLWAYDOWN:

#if 0//(TV_SCAN_PAL_SECAM_ONCE /*&& FRANCE_KILL_NON_SECAM_L*/)//&& FRANCE_SUPPORT_DOUBLE_CHECK_L
            if ( _bIsLSearch)
            {
                if (bDoubleCheckL_State==DOUBLE_CHECK_L_STATE_FOUND_BG)
                {
                    msAPI_ATV_DecCurrentProgramNumber();
                    bDoubleCheckL_State=DOUBLE_CHECK_L_STATE_FOUND_L;
                }
            }
#endif
            msAPI_Tuner_UpdateMediumAndChannelNumber();

            msAPI_ATV_SetProgramPLLData(msAPI_ATV_GetCurrentProgramNumber(), _u16TunerPLL);
            msAPI_ATV_SetAudioStandard(msAPI_ATV_GetCurrentProgramNumber(), msAPI_AUD_GetAudioStandard());
            msAPI_ATV_SetAudioMode(E_AUDIOSOURCE_ATV, (AUDIOMODE_TYPE)MApi_AUDIO_SIF_GetSoundMode());

            msAPI_ATV_SkipProgram(msAPI_ATV_GetCurrentProgramNumber(), FALSE);
        #if 0//(CM_MULTI_FAVORITE)
            msAPI_ATV_SetFavoriteProgram(msAPI_ATV_GetCurrentProgramNumber(), FALSE, E_FAVORITE_TYPE_ALL);
        #else
            msAPI_ATV_SetFavoriteProgram(msAPI_ATV_GetCurrentProgramNumber(), FALSE);
        #endif
            msAPI_ATV_LockProgram(msAPI_ATV_GetCurrentProgramNumber(), FALSE);
            msAPI_ATV_NeedAFT(msAPI_ATV_GetCurrentProgramNumber(), TRUE);
            msAPI_ATV_SetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber(), msAPI_AVD_GetVideoStandard());
            msAPI_AVD_WaitForVideoSyncLock();
#if ENABLE_TTX
            if ( TRUE != msAPI_TTX_GetStationNameFromTeletext(_sCurrentStationName, MAX_STATION_NAME, &u8SortingPriority) )
#endif
            {
                msAPI_Tuner_ConvertMediumAndChannelNumberToString(_eMedium, _u8ChannelNumber, _sCurrentStationName);
                u8SortingPriority = LOWEST_SORTING_PRIORITY;
            }

            msAPI_ATV_SetStationName(msAPI_ATV_GetCurrentProgramNumber(), _sCurrentStationName);


            msAPI_ATV_SetSortingPriority(u8SortingPriority);
            msAPI_ATV_SetMediumAndChannelNumber(msAPI_ATV_GetCurrentProgramNumber(), _eMedium, _u8ChannelNumber);

            _eCurrentTuningState = AFT_INCREASEPRNUMBER;
            break;

        case E_AUTO_SEARCH_TYPE_ONETOUP:
        case E_AUTO_SEARCH_TYPE_ONETODOWN:

            msAPI_Tuner_UpdateMediumAndChannelNumber();

            _DetectStationName();

            _eCurrentTuningState = AFT_COMPLETE;
            break;
        }

#if 0//(TV_SCAN_PAL_SECAM_ONCE /*&& FRANCE_KILL_NON_SECAM_L*/)//FRANCE_SUPPORT_DOUBLE_CHECK_L
        if (_bIsLSearch)
        {
            if (bDoubleCheckL_State==DOUBLE_CHECK_L_STATE_FOUND_L)
            {
                bDoubleCheckL_State=DOUBLE_CHECK_L_STATE_FALSE;
                _bIsOneProgramDetected = FALSE;
            }
            else
                _bIsOneProgramDetected = TRUE;
        }
        else
            _bIsOneProgramDetected = TRUE;
#else
        _bIsOneProgramDetected = TRUE;
#endif
        // TODO
        msAPI_Tuner_PrintTVAVSourceInformation();
        break;

    case AFT_INCREASEPRNUMBER:
        if ( eAutoSearchType == E_AUTO_SEARCH_TYPE_ALLWAYUP )
        {
            if (TRUE != msAPI_ATV_IncCurrentProgramNumber())
            {
                _eCurrentTuningState = AFT_COMPLETE;
                break;
            }
            else
            {
                if ( _IsLPrime() == TRUE )
                {
                    _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_2p75MHz) );
                }
                else
                {
                    _SetTunerPLL( PLLSTEP(TUNER_PLL_NEXT_CHANNEL_JUMP) );
                }
#if TV_SCAN_PAL_SECAM_ONCE
                if (_bIsLSearch)
                {
                    _eCurrentTuningState = AFT_SIGNAL_WEAK;
                    u8ScanOnceFlag |= CH_DETECT;
                }
                else
#endif
                {
                    _eCurrentTuningState = AFT_CHECKSYNC;
                }
            }
        }
        else
        {
            if ( TRUE != msAPI_ATV_DecCurrentProgramNumber() )
            {
                _eCurrentTuningState = AFT_COMPLETE;
                break;
            }
            else
            {
                if ( _IsLPrime() == TRUE )
                {
                    _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_2p75MHz) );
                }
                else
                {
                    _SetTunerPLL( PLLSTEP(TUNER_PLL_NEXT_CHANNEL_JUMP) );
                }

                _eCurrentTuningState = AFT_CHECKSYNC;
            }
        }
        msAPI_Tuner_SetIF();
        break;

    case AFT_COMPLETE:
#if AUTO_SCAN_TIME_PRINT
        printf("\nTotal Auto Tuning Time: %lu\n", msAPI_Timer_DiffTimeFromNow(u32StartAutoTuningTime));
        #endif

        _eCurrentTuningState = AFT_IDLE;

        msAPI_AVD_SuppressAutoAV();

        switch ( eAutoSearchType )
        {
        case E_AUTO_SEARCH_TYPE_ALLWAYUP:
        case E_AUTO_SEARCH_TYPE_ALLWAYDOWN:

        #if ATVSCAN_SORT_BY_STATION_NAME
            msAPI_ATV_SortProgram(u8StartFrom, msAPI_ATV_GetCurrentProgramNumber());
        #endif

            msAPI_ATV_SetCurrentProgramNumber(u8StartFrom);

            if ( _bChangeProgram == TRUE )
            {
                msAPI_Tuner_ChangeProgram();
            }
            break;

        case E_AUTO_SEARCH_TYPE_ONETOUP:
        case E_AUTO_SEARCH_TYPE_ONETODOWN:

            msAPI_Tuner_SetIF();
            _bIsAFTNeeded = TRUE;
            msAPI_Tuner_SetRealtimeAFTBaseTunerPLL(_u16TunerPLL);
            break;
        }

        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE,E_AUDIO_INTERNAL_2_MUTEOFF,E_AUDIOMUTESOURCE_ATV);
#if ENABLE_TTX
        msAPI_TTX_ResetAcquisition();
#endif
        //msAPI_VD_ClearSyncCheckCounter();

        msAPI_AVD_ClearAspectRatio();

        //msAPI_AVD_IsVideoFormatChanged();
        msAPI_AVD_SetIsVideoFormatChangedAsFalse();//20100330EL

        eAutoSearchType = E_AUTO_SEARCH_TYPE_STOPED;

        msAPI_AVD_SetHsyncDetectionForTuning(FALSE);
        return;

    case AFT_EXT_STEP_SEARCHSTOP:
        msAPI_Timer_Delayms(100);

        _eCurrentTuningState = AFT_IDLE;

        eAutoSearchType = E_AUTO_SEARCH_TYPE_STOPED;

        debugTuningPrint("Stop Auto Program\n", 0);

        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE,E_AUDIO_INTERNAL_2_MUTEOFF,E_AUDIOMUTESOURCE_ATV);
#if ENABLE_TTX
        msAPI_TTX_ResetAcquisition();
#endif
        //msAPI_VD_ClearSyncCheckCounter();

        msAPI_AVD_ClearAspectRatio();

        _bIsAFTNeeded = FALSE;

        msAPI_Tuner_SetRealtimeAFTBaseTunerPLL(_u16TunerPLL);

        msAPI_AVD_SuppressAutoAV();

        msAPI_AVD_SetHsyncDetectionForTuning(FALSE);
        break;
    }

    switch ( eAutoSearchType )
    {
    case E_AUTO_SEARCH_TYPE_ALLWAYUP:
        if ( _u16TunerPLL >= UHF_MAX_PLL )
        {
#if (TV_SCAN_PAL_SECAM_ONCE==0)
            if ( msAPI_AUD_GetAudioStandard() == E_AUDIOSTANDARD_L )
            {
                debugTuningPrint("-SECAM L Tuning is finished. We will start BG/I/DK", 0);

                _SetTunerPLL(VHF_LOWMIN_PLL);

                msAPI_AUD_SetAudioStandard(E_AUDIOSTANDARD_BG);

                msAPI_Tuner_SetIF();

                _eCurrentTuningState = AFT_CHECKSYNC;
            }
            else
#endif
            {
                _eCurrentTuningState = AFT_COMPLETE;

                _bChangeProgram = FALSE;
            }
        }
        break;

    case E_AUTO_SEARCH_TYPE_ALLWAYDOWN:
        if ( _u16TunerPLL <= VHF_LOWMIN_PLL )
        {
#if (TV_SCAN_PAL_SECAM_ONCE==0)
            if ( msAPI_AUD_GetAudioStandard() == E_AUDIOSTANDARD_L )
            {
                debugTuningPrint("-SECAM L Tuning is finished. We will start BG/I/DK\n", 0);

                _SetTunerPLL(UHF_MAX_PLL);
                msAPI_AUD_SetAudioStandard(E_AUDIOSTANDARD_BG);
                msAPI_Tuner_SetIF();
                _eCurrentTuningState = AFT_CHECKSYNC;
            }
            else
#endif
            {
                _eCurrentTuningState = AFT_COMPLETE;
                _bChangeProgram = FALSE;
            }
        }
        break;

    case E_AUTO_SEARCH_TYPE_ONETOUP:
        if ( _u16TunerPLL >= UHF_MAX_PLL )
        {
            _SetTunerPLL(VHF_LOWMIN_PLL);
#if TV_SCAN_PAL_SECAM_ONCE
            if (_bIsLSearch)
            {
                _eCurrentTuningState = AFT_SIGNAL_WEAK;
                u8ScanOnceFlag |= CH_SCAN_RING;
            }
            else
#endif
                _eCurrentTuningState = AFT_CHECKSYNC;
            msAPI_Tuner_SetIF();
        }
        break;

    case E_AUTO_SEARCH_TYPE_ONETODOWN:
        if ( _u16TunerPLL <= VHF_LOWMIN_PLL )
        {
            _SetTunerPLL(UHF_MAX_PLL);
#if TV_SCAN_PAL_SECAM_ONCE
            if (_bIsLSearch)
            {
                _eCurrentTuningState = AFT_SIGNAL_WEAK;
                u8ScanOnceFlag |= CH_SCAN_RING;
            }
            else
#endif
                _eCurrentTuningState = AFT_CHECKSYNC;
            msAPI_Tuner_SetIF();
        }
        break;
    }
}

U8 _msAPI_Tuner_GetTuningProcessPercent(void)
{
    U8 u8Percent;
    U32 u32UHFMAXPLL;
    U32 u32VHFLOWMINPLL;
    U32 u32TunerPLL;

    if ( _eCurrentTuningState == AFT_IDLE ||
         _eCurrentTuningState == AFT_EXT_STEP_SEARCHALL )
    {
        return 0;
    }

    u8Percent = 0;

    u32UHFMAXPLL = UHF_MAX_PLL;

    u32VHFLOWMINPLL = VHF_LOWMIN_PLL;

    u32TunerPLL = _u16TunerPLL;

    if ( (u32UHFMAXPLL - u32VHFLOWMINPLL) )
    {
        u8Percent = (U8)(((u32TunerPLL - u32VHFLOWMINPLL)+1)*100 / (u32UHFMAXPLL - u32VHFLOWMINPLL)) ;
    }

#if (TV_SCAN_PAL_SECAM_ONCE == 0)
    if ( _bIsLSearch == TRUE )
    {
        if ( msAPI_AUD_GetAudioStandard() == E_AUDIOSTANDARD_L )
        {
            u8Percent = u8Percent / 2;
        }
        else

        {
            u8Percent = 50 + (u8Percent / 2);
        }
    }
#endif

    return u8Percent;
}

#if defined(AUTO_TUNING_DEBUG)
static float _TunerPLLDbg(WORD wPLL)
{
    float FreqStep;

#if TN_FREQ_STEP == FREQ_STEP_62_5KHz
    FreqStep = 62.5;
#elif TN_FREQ_STEP == FREQ_STEP_50KHz
    FreqStep = 50.0;
#else
    FreqStep = 31.25;
#endif
    return ((float)(wPLL*FreqStep)/1000);
}
#endif
