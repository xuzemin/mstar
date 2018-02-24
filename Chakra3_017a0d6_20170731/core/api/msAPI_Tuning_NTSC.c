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


#define VD_CHECK_HSYNC_LOCKED             BIT14

TUNING_STATUS _GetTuningStatus(void)
{
    AFC eFreqDev;

    eFreqDev = MDrv_IFDM_GetFreqDev();

#if (FRONTEND_TUNER_TYPE == NXP_FQD1136_TUNER)
    if ( eFreqDev == E_AFC_GOOD )
    {
        return E_TUNING_STATUS_GOOD;
    }
    else if ( eFreqDev == E_AFC_MINUS_62p5KHz )
    {
        return E_TUNING_STATUS_UNDER;
    }
    else if ( eFreqDev == E_AFC_PLUS_62p5KHz )
    {
        return E_TUNING_STATUS_OVER;
    }
    else if ( eFreqDev == E_AFC_BELOW_MINUS_125pKHz )
    {
        return E_TUNING_STATUS_UNDER_MORE;
    }
    else if ( eFreqDev == E_AFC_ABOVE_PLUS_125pKHz )
    {
        return E_TUNING_STATUS_OVER_MORE;
    }
    else
    {
        __ASSERT(0);
        return E_TUNING_STATUS_OUT_OF_AFCWIN;
    }
#else
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
        __ASSERT(0);
        return E_TUNING_STATUS_OUT_OF_AFCWIN;
    }
#endif

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
    U8 u8SortingPriority = 0;
    U8 i;

#if defined(AUTO_TUNING_DEBUG)
    static U32 u32StartAutoTuningTime;
#endif

    static BOOLEAN bIsSignalExist;

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

    if ( _eCurrentTuningState != AFT_IDLE )
    {
        if ( _IsTunerStable() == FALSE )
        {
            return;
        }
    }

    if (_IsTuningSuspend == TRUE)
        return;

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
                return;
            }

            if ( IS_RT_AFT_ENABLED == FALSE )
            {
                return;
            }

            if ( (_u16AFTIdleTimer % 19) == 0 )
            {
                if ( FALSE == _bIsAFTNeeded )
                {
                    return;
                }

                eFreqDev = MDrv_IFDM_GetFreqDev();

            #if (FRONTEND_TUNER_TYPE == NXP_FQD1136_TUNER)
                if ( eFreqDev == E_AFC_GOOD )
                {
                    return;
                }

                if ( DIFFERENCE(_u16RealtimeAFTBaseTunerPLL,_u16TunerPLL) <= TUNER_PLL_PLUS_2MHz && msAPI_AVD_IsSyncLocked() == TRUE )
                {
                    debugTuningPrint("Real Time AFT: 0x%x\n", eFreqDev);

                    for ( i = 0; i <= TUNER_PLL_PLUS_4MHz ; i++ )
                    {
                        switch ( eFreqDev )
                        {
                        case E_AFC_BELOW_MINUS_125pKHz:
                            _SetTunerPLL( PLLSTEP(2) );
                            break;

                        case E_AFC_MINUS_62p5KHz:
                            _SetTunerPLL( PLLSTEP(1) );
                            break;

                        case E_AFC_PLUS_62p5KHz:
                            _SetTunerPLL( PLLSTEP(-1) );
                            break;

                        case E_AFC_ABOVE_PLUS_125pKHz:
                            _SetTunerPLL( PLLSTEP(-2) );
                            break;

                        default:
                            _SetTunerPLL(_u16RealtimeAFTBaseTunerPLL);
                            msAPI_Tuner_SetIF();
                            return;
                        }
            #else

                if ( eFreqDev == E_AFC_MINUS_12p5KHz || eFreqDev == E_AFC_PLUS_12p5KHz )
                {
                    return;
                }

                if ( DIFFERENCE(_u16RealtimeAFTBaseTunerPLL,_u16TunerPLL) <= TUNER_PLL_PLUS_2MHz && msAPI_AVD_IsSyncLocked() == TRUE )
                {
                    debugTuningPrint("Real Time AFT: 0x%x\n", eFreqDev);

                    for ( i = 0; i <= TUNER_PLL_PLUS_4MHz ; i++ )
                    {
                        switch ( eFreqDev )
                        {
                        case E_AFC_BELOW_MINUS_187p5KHz:
                            _SetTunerPLL( PLLSTEP(8) );
                            break;

                        case E_AFC_MINUS_162p5KHz:
                            _SetTunerPLL( PLLSTEP(5) );
                            break;

                        case E_AFC_MINUS_137p5KHz:
                            _SetTunerPLL( PLLSTEP(4) );
                            break;

                        case E_AFC_MINUS_112p5KHz:
                            _SetTunerPLL( PLLSTEP(3) );
                            break;

                        case E_AFC_MINUS_87p5KHz:
                            _SetTunerPLL( PLLSTEP(3) );
                            break;

                        case E_AFC_MINUS_62p5KHz:
                            _SetTunerPLL( PLLSTEP(2) );
                            break;

                        case E_AFC_MINUS_37p5KHz:
                            _SetTunerPLL( PLLSTEP(1) );
                            break;

                        case E_AFC_MINUS_12p5KHz:
                            return;

                        case E_AFC_PLUS_12p5KHz:
                            return;

                        case E_AFC_PLUS_37p5KHz:
                            _SetTunerPLL( PLLSTEP(-1) );
                            break;

                        case E_AFC_PLUS_62p5KHz:
                            _SetTunerPLL( PLLSTEP(-2) );
                            break;

                        case E_AFC_PLUS_87p5KHz:
                            _SetTunerPLL( PLLSTEP(-3) );
                            break;

                        case E_AFC_PLUS_112p5KHz:
                            _SetTunerPLL( PLLSTEP(-3) );
                            break;

                        case E_AFC_PLUS_137p5KHz:
                            _SetTunerPLL( PLLSTEP(-4) );
                            break;

                        case E_AFC_PLUS_162p5KHz:
                            _SetTunerPLL( PLLSTEP(-5) );
                            break;

                        case E_AFC_ABOVE_PLUS_187p5KHz:
                            _SetTunerPLL( PLLSTEP(-8) );
                            break;

                        default:
                            _SetTunerPLL(_u16RealtimeAFTBaseTunerPLL);
                            msAPI_Tuner_SetIF();
                            return;
                        }
            #endif

                        if ( DIFFERENCE(_u16RealtimeAFTBaseTunerPLL,_u16TunerPLL) > TUNER_PLL_PLUS_2MHz )
                        {
                            if ( _IsLPrime() == TRUE )
                            {
                                if ( _u16TunerPLL < _u16RealtimeAFTBaseTunerPLL )
                                {
                                    _SetTunerPLL( _u16RealtimeAFTBaseTunerPLL + TUNER_PLL_PLUS_2MHz );
                                }
                                else
                                {
                                    _SetTunerPLL( _u16RealtimeAFTBaseTunerPLL + TUNER_PLL_MINUS_2MHz );
                                }
                            }
                            else
                            {
                                debugTuningPrint("One Channel AFT in Real Time\n", 0);

                                _SetTunerPLL(_u16RealtimeAFTBaseTunerPLL);

                                msAPI_Tuner_SetIF();

                                _OneChannelAFT();
                                return;
                            }
                        }

                        eFreqDev = MDrv_IFDM_GetFreqDev();
                    }
                }
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
            } // if ( (_u16AFTIdleTimer % 19) == 0 )
            return;

        case AFT_EXT_STEP_SEARCHALL:
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE,E_AUDIO_INTERNAL_2_MUTEON,E_AUDIOMUTESOURCE_ATV);

            msAPI_Timer_Delayms(DELAY_FOR_ENTERING_MUTE);

            _eCurrentTuningState = AFT_CHECKSYNC;

            eAutoSearchType = E_AUTO_SEARCH_TYPE_ALLWAYUP;

            u8StartFrom = msAPI_ATV_GetCurrentProgramNumber();
        #if ENABLE_DVB_TAIWAN_APP
            _SetTunerPLL(msAPI_ATV_MapChanToFreq(msAPI_ATV_GetChannelMin()));
        #else
            _SetTunerPLL(msAPI_ATV_MapChanToFreq(msAPI_ATV_GetChannelMin())-TUNER_PLL_PLUS_3MHz);
        #endif
            _bIsAFTNeeded = TRUE;

            msAPI_AVD_TurnOffAutoAV();

        #if ENABLE_TTX
            msAPI_TTX_ResetAcquisition();
        #endif


#if  (AUDIO_SYSTEM_SEL == AUDIO_SYSTEM_BTSC)    // for BTSC countries.
            msAPI_AUD_SetAudioStandard((AUDIOSTANDARD_TYPE)E_AUDIOSTANDARD_M_BTSC);
#elif (AUDIO_SYSTEM_SEL == AUDIO_SYSTEM_A2)   // for Korea A2.
            msAPI_AUD_SetAudioStandard((AUDIOSTANDARD_TYPE)E_AUDIOSTANDARD_M);
#endif
            msAPI_Tuner_SetIF();

            msAPI_AVD_SetHsyncDetectionForTuning(TRUE);

        #if defined(AUTO_TUNING_DEBUG)
            {
                u32StartAutoTuningTime = msAPI_Timer_GetTime0();
            }
        #endif
            break;

        case AFT_EXT_STEP_SEARCHONETOUP:
        case AFT_EXT_STEP_SEARCHONETODOWN:
        /* Direct Tune------------------------------------------------------------------------*/

            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE,E_AUDIO_INTERNAL_2_MUTEON,E_AUDIOMUTESOURCE_ATV);

            msAPI_Timer_Delayms(DELAY_FOR_ENTERING_MUTE);

            _SetTunerPLL( msAPI_ATV_MapChanToFreq(msAPI_ATV_GetCurrentProgramNumber()+1) );

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

            _bIsAFTNeeded = TRUE;

            msAPI_Tuner_SetIF();

            msAPI_AVD_SetHsyncDetectionForTuning(TRUE);
        break;

        case AFT_CHECKSYNC:
            AUTO_TUNING_PRINT(printf("\r\n AFT_CHECKSYNC"));

            u8NoSyncCount = 0;
            bIsSignalExist = FALSE;

            if ( TRUE == msAPI_AVD_IsSyncLocked() )
            {
                _eCurrentTuningState = AFT_SYNCOK_1;
            }
            else
            {
                _eCurrentTuningState = AFT_NOSYNC_1;
            }
            break;

        case AFT_SYNCOK_1:
        case AFT_SYNCOK_2:
            if ( TRUE == msAPI_AVD_IsSyncLocked() )
            {
                _eCurrentTuningState++;
            }
            else
            {
                _eCurrentTuningState = AFT_NOSYNC_1;
            }
            break;

        case AFT_SYNCOK_3:
            AUTO_TUNING_PRINT(printf("\r\n AFT_SYNCOK_3"));

            if ( TRUE == msAPI_AVD_IsSyncLocked() )
            {
                u8NoSyncCount = 0;
                u16PreviosTunerPLL = _u16TunerPLL;
                _eCurrentTuningState = AFT_TUNING;
            }
            else
            {
                _eCurrentTuningState = AFT_NOSYNC_1;
            }
            break;

        case AFT_NOSYNC_1:
        case AFT_NOSYNC_2:
            if ( ++u8NoSyncCount >= (NO_SYNC_COUNT_THRESHOLD*2) )
            {
                _eCurrentTuningState = AFT_JUMPNEARHALF;

                debugTuningPrint("-Unstable Sync: %dMHz\n", msAPI_CFT_ConvertPLLtoIntegerOfFrequency(_u16TunerPLL));//, msAPI_CFT_ConvertPLLtoFractionOfFrequency(_u16TunerPLL));
                break;
            }

            if ( FALSE == msAPI_AVD_IsSyncLocked() )
            {
                _eCurrentTuningState++;
            }
            else
            {
                _eCurrentTuningState = AFT_SYNCOK_1;
            }
            break;

        case AFT_NOSYNC_3:
            AUTO_TUNING_PRINT(printf("\r\n AFT_NOSYNC_3"));

            if ( FALSE == msAPI_AVD_IsSyncLocked() )
            {
                _eCurrentTuningState = AFT_JUMPNEAR;

                debugTuningPrint("-No Sync: %dMHz\n", msAPI_CFT_ConvertPLLtoIntegerOfFrequency(_u16TunerPLL));//, msAPI_CFT_ConvertPLLtoFractionOfFrequency(_u16TunerPLL));
            }
            else
            {
                _eCurrentTuningState = AFT_SYNCOK_1;
            }
            break;

        case AFT_JUMPNEXT:
            _eCurrentTuningState = AFT_CHECKSYNC;
            break;

        case AFT_JUMPFAR:
        case AFT_JUMPNEAR:
        case AFT_JUMPNEARHALF:
            if ( _eCurrentTuningState == AFT_JUMPFAR )
            {
                u16JumpDistance = TUNER_PLL_PLUS_1p75MHz;
            }
            else if( _eCurrentTuningState == AFT_JUMPNEARHALF )
            {
                u16JumpDistance = TUNER_PLL_PLUS_0p5MHz;
            }
            else
            {
                u16JumpDistance = TUNER_PLL_PLUS_1p25MHz;
            }

            if((msAPI_ATV_MapChanToFreq(msAPI_ATV_GetCurrentProgramNumber()+1))<_u16TunerPLL )
            {
                _eCurrentTuningState = AFT_MEMORIZEPRDATA;
                break;
            }

            _SetTunerPLL( PLLSTEP(u16JumpDistance) );

            msAPI_Tuner_SetIF();

            _eCurrentTuningState = AFT_CHECKSYNC;
            break;

        case AFT_TUNING:
            AUTO_TUNING_PRINT(printf("\r\n AFT_TUNING"));
            u16VdStatus = msAPI_AVD_CheckStatusLoop();
            eTuningStatus = _GetTuningStatus();
            if(u16VdStatus & VD_CHECK_HSYNC_LOCKED)
            {
                switch ( eTuningStatus )
                {
                case E_TUNING_STATUS_GOOD:
                    MApi_AUDIO_SIF_StartAutoStandardDetection();
                    msAPI_AVD_StartAutoStandardDetection();
                #if ENABLE_TTX
                    msAPI_TTX_ResetAcquisition();
                #endif
                    _u16AFTIdleTimer = 0;

                    if ( msAPI_AVD_GetVerticalFreq() == E_VIDEO_FQ_NOSIGNAL )
                    {
                        for(i=0; i<10; i++)
                        {
                            if( msAPI_AVD_GetVerticalFreq() != E_VIDEO_FQ_NOSIGNAL )
                                break;
                            else
                                msAPI_Timer_Delayms(50);
                        }
                    }
                     _eCurrentTuningState = AFT_SHOWTIME1;
                     return;

                    break;

                case E_TUNING_STATUS_OVER:
                    _SetTunerPLL( PLLSTEP(-1) );
                    break;

                case E_TUNING_STATUS_UNDER:
                    _SetTunerPLL( PLLSTEP(1) );
                    break;

                case E_TUNING_STATUS_OVER_MORE:
                #if (FRONTEND_TUNER_TYPE == NXP_FQD1136_TUNER)
                    _SetTunerPLL( PLLSTEP(-2) );
                #else
                    _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_0p25MHz) );
                #endif
                    break;

                case E_TUNING_STATUS_UNDER_MORE:
                    _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_0p25MHz) );
                    break;

                default:
                    /* ASSERT */
                    break;
                }

                if ( (u8NoSyncCount++) == 20 )
                {
                    _eCurrentTuningState = AFT_JUMPNEARHALF;
                }
                else if((msAPI_ATV_MapChanToFreq(msAPI_ATV_GetCurrentProgramNumber()+1)+TUNER_PLL_PLUS_3MHz)<_u16TunerPLL)
                {
                    _eCurrentTuningState = AFT_MEMORIZEPRDATA;
                }
                else if((msAPI_ATV_MapChanToFreq(msAPI_ATV_GetCurrentProgramNumber()+1)-TUNER_PLL_PLUS_3MHz)>_u16TunerPLL)
                {
                    _eCurrentTuningState = AFT_JUMPNEARHALF;
                }
            }
            else
            {
                if(eAutoSearchType == E_AUTO_SEARCH_TYPE_ALLWAYUP)
                    _eCurrentTuningState = AFT_JUMPNEARHALF;
                else
                _eCurrentTuningState = AFT_MEMORIZEPRDATA;
            }

            if ( _eCurrentTuningState == AFT_JUMPNEARHALF )
            {
                if ( u16PreviosTunerPLL > _u16TunerPLL )
                {
                    _SetTunerPLL( u16PreviosTunerPLL );
                }
            }
            break;

        case AFT_SHOWTIME1:
            _u16AFTIdleTimer++;

            if ( _u16AFTIdleTimer >= WAIT_230ms )
            {
                _eCurrentTuningState = AFT_DETECTVIDEO;
            }
            break;

        case AFT_DETECTVIDEO:
            msAPI_AVD_GetResultOfAutoStandardDetection();
            _u16AFTIdleTimer = 0;
            _eCurrentTuningState = AFT_SHOWTIME2;
            break;

        case AFT_SHOWTIME2:
            _u16AFTIdleTimer++;

            if ( _u16AFTIdleTimer >= ATVSCAN_AUDIO_WAIT_TIME )
            {
                if ( msAPI_AVD_IsSyncLocked() == TRUE )
                {
                    _eCurrentTuningState = AFT_DETECTAUDIO;
                }
                else
                {
                    debugTuningPrint("-Unlocked Sync: %dMHz", msAPI_CFT_ConvertPLLtoIntegerOfFrequency(_u16TunerPLL));//, msAPI_CFT_ConvertPLLtoFractionOfFrequency(_u16TunerPLL));

                    if ( _u16TunerPLL < u16PreviosTunerPLL )
                    {
                        _SetTunerPLL(u16PreviosTunerPLL);
                    }

                    _eCurrentTuningState = AFT_JUMPNEARHALF;
                }
            }
            _bIsOneProgramDetected = FALSE;
        break;

        case AFT_DETECTAUDIO:
            msAPI_AUD_GetResultOfAutoStandardDetection();
            bIsSignalExist = TRUE;
            _eCurrentTuningState = AFT_MEMORIZEPRDATA;
            break;

        case AFT_MEMORIZECHDATA:
            break;

        case AFT_MEMORIZEPRDATA:
            AUTO_TUNING_PRINT(printf("\r\n AFT_MEMORIZEPRDATA"));

            if(bIsSignalExist)
                msAPI_ATV_SetProgramPLLData(msAPI_ATV_GetCurrentProgramNumber(), _u16TunerPLL);
            else
                msAPI_ATV_SetProgramPLLData(msAPI_ATV_GetCurrentProgramNumber(), msAPI_ATV_MapChanToFreq(msAPI_ATV_GetCurrentProgramNumber()+1));

            msAPI_ATV_SetAudioStandard(msAPI_ATV_GetCurrentProgramNumber(), msAPI_AUD_GetAudioStandard());
            msAPI_ATV_SkipProgram(msAPI_ATV_GetCurrentProgramNumber(), (!bIsSignalExist));
        #if 0//(CM_MULTI_FAVORITE)
            msAPI_ATV_SetFavoriteProgram(msAPI_ATV_GetCurrentProgramNumber(), FALSE, E_FAVORITE_TYPE_ALL);
        #else
            msAPI_ATV_SetFavoriteProgram(msAPI_ATV_GetCurrentProgramNumber(), FALSE);
        #endif
            msAPI_ATV_LockProgram(msAPI_ATV_GetCurrentProgramNumber(), FALSE);
            msAPI_ATV_NeedAFT(msAPI_ATV_GetCurrentProgramNumber(), (!bIsSignalExist));
            msAPI_ATV_SetSearchedProgram(msAPI_ATV_GetCurrentProgramNumber(), bIsSignalExist);
            msAPI_ATV_SetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber(), msAPI_AVD_GetVideoStandard());
            msAPI_AVD_WaitForVideoSyncLock();
            msAPI_ATV_SetSortingPriority(u8SortingPriority);

            switch ( (U8)eAutoSearchType )
            {
                case E_AUTO_SEARCH_TYPE_ALLWAYUP:
                case E_AUTO_SEARCH_TYPE_ALLWAYDOWN:
                    _eCurrentTuningState = AFT_INCREASEPRNUMBER;
                    break;

                case E_AUTO_SEARCH_TYPE_ONETOUP:
                case E_AUTO_SEARCH_TYPE_ONETODOWN:
                    _eCurrentTuningState = AFT_COMPLETE;
                    break;
            }

            _bIsOneProgramDetected = TRUE;

            // TODO
            msAPI_Tuner_PrintTVAVSourceInformation();
            break;

        case AFT_INCREASEPRNUMBER:
            if (TRUE != msAPI_ATV_IncCurrentProgramNumber())
            {
                _eCurrentTuningState = AFT_COMPLETE;
                break;
            }
            else
            {
            #if ENABLE_DVB_TAIWAN_APP
                _SetTunerPLL( msAPI_ATV_MapChanToFreq(msAPI_ATV_GetCurrentProgramNumber()+1));
            #else
                _SetTunerPLL( msAPI_ATV_MapChanToFreq(msAPI_ATV_GetCurrentProgramNumber()+1)-TUNER_PLL_PLUS_3MHz );
            #endif
                _eCurrentTuningState = AFT_CHECKSYNC;
            }

            msAPI_Tuner_SetIF();
            break;

        case AFT_COMPLETE:
            AUTO_TUNING_PRINT( printf("Total Auto Tuning Time: %lu\n", msAPI_Timer_DiffTimeFromNow(u32StartAutoTuningTime)) );

            _eCurrentTuningState = AFT_IDLE;

            msAPI_AVD_SuppressAutoAV();

            switch ( (U8)eAutoSearchType )
            {
            case E_AUTO_SEARCH_TYPE_ALLWAYUP:
            case E_AUTO_SEARCH_TYPE_ALLWAYDOWN:

            #if ( ENABLE_DTMB_CHINA_APP || ENABLE_DVB_TAIWAN_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP || (TV_SYSTEM == TV_NTSC) )
            #else
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

    switch ( (U8)eAutoSearchType )
    {
        case E_AUTO_SEARCH_TYPE_ALLWAYUP:
        case E_AUTO_SEARCH_TYPE_ALLWAYDOWN:
            if ( _u16TunerPLL >= UHF_MAX_PLL )
            {
                _eCurrentTuningState = AFT_COMPLETE;

                _bChangeProgram = FALSE;
            }
            break;

        case E_AUTO_SEARCH_TYPE_ONETOUP:
        case E_AUTO_SEARCH_TYPE_ONETODOWN:
            if ( _u16TunerPLL >= UHF_MAX_PLL )
            {
                _SetTunerPLL(VHF_LOWMIN_PLL);
                msAPI_Tuner_SetIF();
                _eCurrentTuningState = AFT_CHECKSYNC;
            }
            break;
    }
}

#if ( ENABLE_DVB_TAIWAN_APP )
U8 _msAPI_Tuner_GetTuningProcessPercent(void)
{
    U8 u8Percent;
    U8 u8MAXCH;
    U8 u8MINCH;
    U8 u8CurrCH;

    if ( _eCurrentTuningState == AFT_IDLE || _eCurrentTuningState == AFT_EXT_STEP_SEARCHALL )
    {
        return 0;
    }

    u8Percent = 0;
    u8MAXCH = msAPI_ATV_GetChannelMax();
    u8MINCH = msAPI_ATV_GetChannelMin();
    u8CurrCH = msAPI_ATV_GetCurrentProgramNumber();
    if(u8CurrCH< u8MINCH)
    {
        return 0;
    }

    if ( (u8MAXCH - u8MINCH) )
    {
        u8Percent = (U8)(((u8CurrCH+1 - u8MINCH))*100 / (u8MAXCH - u8MINCH));
    }
    return u8Percent;
}

#else
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

    return u8Percent;
}

#endif

