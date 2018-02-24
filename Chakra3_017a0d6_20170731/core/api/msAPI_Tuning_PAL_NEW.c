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
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"

#include "MApp_TopStateMachine.h"


#define AUTO_TUNING_FLOW_DEBUG      FALSE//TRUE//FALSE

#if (AUTO_TUNING_FLOW_DEBUG)
    #define TUNING_FLOW_MSG(x)      x
    #define TUNING_LOCK_MSG(x)      x
    #define TUNING_NOLOCK_MSG(x)    x

#else
    #define TUNING_FLOW_MSG(x)      //x
    #define TUNING_LOCK_MSG(x)      //x
    #define TUNING_NOLOCK_MSG(x)    //x
#endif


#if ( ENABLE_DTMB_CHINA_APP || ENABLE_DVB_TAIWAN_APP || ENABLE_ATV_CHINA_APP)
#define NTSC_SYSTEM_DETECT        TRUE//TRUE//FALSE
#else
#define NTSC_SYSTEM_DETECT        FALSE
#endif

//
//====================================================
//

//------------------------------------------------------
//
//------------------------------------------------------
    static AUTO_SEARCH_TYPE eAutoSearchType;
    static U8 u8NoSyncCount;

    static U8 u8StartFrom;
    static U16 _u16PreviousStationTunerPLL;

static U16 u16JumpDistance;

    TUNING_STATUS eTuningStatus;
//    U16 u16VdStatus;
    U8 u8SortingPriority;
    static U16 u16Record_FALSE_SIGNAL_TunerPLL;
    static AUDIOSTANDARD_TYPE u8SoundSystem;
    static AVD_VideoStandardType u8VideoSystem;
    static AUDIOSTANDARD_TYPE    u8AudioStandard;
    static AUDIOMODE_TYPE        u8AudioMode;



#if AUTO_SCAN_TIME_PRINT
    static U32 u32StartAutoTuningTime;
#endif

#if ENABLE_AUTOTEST
    extern BOOLEAN g_bAutobuildDebug;
#endif

static U32 s_Tuning_u32DetectVideoStartTime;

//------------------------------------------------------
//
//------------------------------------------------------


#define DEBUG_AFT(x)        //x
#define DEBUG_AFCWIN(x)     //x


void msAPI_Dbg_TunningStatusText(TUNING_STATUS eTuningSts)
{
    switch (eTuningSts)
    {
        case E_TUNING_STATUS_GOOD:
            DEBUG_AFT( printf("E_TUNING_STATUS_GOOD \n") );
            break;

        case E_TUNING_STATUS_OVER:
            DEBUG_AFT( printf("E_TUNING_STATUS_OVER \n") );
            break;

        case E_TUNING_STATUS_UNDER:
            DEBUG_AFT( printf("E_TUNING_STATUS_UNDER \n") );
            break;

        case E_TUNING_STATUS_OVER_LITTLE:
            DEBUG_AFT( printf("E_TUNING_STATUS_OVER_LITTLE \n") );
            break;

        case E_TUNING_STATUS_UNDER_LITTLE:
            DEBUG_AFT( printf("E_TUNING_STATUS_UNDER_LITTLE \n") );
            break;

        case E_TUNING_STATUS_OVER_MORE:
            DEBUG_AFT( printf("E_TUNING_STATUS_OVER_MORE \n") );
            break;

        case E_TUNING_STATUS_UNDER_MORE:
            DEBUG_AFT( printf("E_TUNING_STATUS_UNDER_MORE \n") );
            break;

        case E_TUNING_STATUS_OUT_OF_AFCWIN:
            DEBUG_AFT( printf("E_TUNING_STATUS_OUT_OF_AFCWIN \n") );
            break;

        default:
            break;
    }
}


#if (FRONTEND_TUNER_TYPE == SILAB_2158_TUNER)
extern S16 Si2158_GetATV_AFC_freq(void);
#endif

void _msAPI_Tuning_AutoFineTuning(void)
{
    #define MAX_AFT_UPPER_BOUND     30
    #define MAX_AFT_LOWER_THRES     (MAX_AFT_UPPER_BOUND/3)
    #define MAX_AFT_UPPER_THRES     (MAX_AFT_LOWER_THRES*2)
    #define MAX_AFT_GOOD_LEAK       (MAX_AFT_UPPER_BOUND/10)

    AFC eFreqDev;
#if (FRONTEND_TUNER_TYPE == SILAB_2158_TUNER)
    S16 _u16TunerAFC;
#endif

    TUNING_STATUS eTuningSts = _GetTuningStatus();

    if (eTuningSts == E_TUNING_STATUS_GOOD)
    {
        if (u8ScanAFTCount >= MAX_AFT_GOOD_LEAK)
            u8ScanAFTCount -= MAX_AFT_GOOD_LEAK;
        else
            u8ScanAFTCount =0;

    #if (FRONTEND_TUNER_TYPE == SILAB_2158_TUNER)
        _u16TunerAFC = Si2158_GetATV_AFC_freq();
        if(_u16TunerAFC > 8 || _u16TunerAFC< -8)
        {
            printf("[AFT]_u16TunerAFC = %d\n", _u16TunerAFC);
            _SetTunerPLL( PLLSTEP(_u16TunerAFC) );
        }
    #endif

        if (u8ScanAFTCount != 0)
        {
            DEBUG_AFT( printf("u8ScanAFTCount=%bd\n", u8ScanAFTCount) );
        }

        return;
    }
    else
    {
        DEBUG_AFT( printf("_GetTuningStatus(%bd) = ", eTuningSts) );
        msAPI_Dbg_TunningStatusText(eTuningSts);
    }

  #if defined(AUTO_TUNING_DEBUG)
    {
        static eAFTSTEP _ePreTuningState;
        static U32 u32TuningStateTime;
        //if ( _eCurrentTuningState != AFT_IDLE )
        {
            DEBUG_AFT( printf("AFT_STATE: 0x%BX -> 0x%BX (%lu)\n",
                                      _ePreTuningState,
                                      _eCurrentTuningState,
                                      msAPI_Timer_DiffTimeFromNow(u32TuningStateTime)) );
            //AUTO_TUNING_PRINT(printf("BaseFre=%3.2f ",(float)_TunerPLLDbg(_u16RealtimeAFTBaseTunerPLL)));
            //AUTO_TUNING_PRINT(printf("CurFre=%3.2f \n",(float)_TunerPLLDbg(_u16TunerPLL)));
            _ePreTuningState = _eCurrentTuningState;
            u32TuningStateTime = msAPI_Timer_GetTime0();
        }
    }
  #endif

    eFreqDev = MDrv_IFDM_GetFreqDev();
//    DEBUG_AFT( printf("AFT : 0x%bx \n", eFreqDev) );
//    DEBUG_AFT( printf("u8ScanAFTCount = %bd \n", u8ScanAFTCount) );

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
    {
        u8ScanAFTFlag = 1;
    }
    else if (u8ScanAFTCount<MAX_AFT_LOWER_THRES)
    {
        u8ScanAFTFlag = 0;
    }

    if (u8ScanAFTFlag)
    {
        if (_u16TunerPLL != _u16RealtimeAFTBaseTunerPLL)
        {
            DEBUG_AFT( printf("[AFT-1]"); );
            _SetTunerPLL(_u16RealtimeAFTBaseTunerPLL);
            msAPI_Tuner_SetIF();
        }
    }
    else if ( (DIFFERENCE(_u16RealtimeAFTBaseTunerPLL,_u16TunerPLL) > TUNER_PLL_PLUS_2MHz )
            &&(eFreqDev == E_AFC_OUT_OF_AFCWIN))
    {   // roll PLL to +/- 2MHz
        if (_u16RealtimeAFTBaseTunerPLL>_u16TunerPLL)
            _u16TunerPLL = _u16RealtimeAFTBaseTunerPLL + TUNER_PLL_PLUS_2MHz;
        else
            _u16TunerPLL = _u16RealtimeAFTBaseTunerPLL - TUNER_PLL_PLUS_2MHz;

        DEBUG_AFT( printf("[AFT-2] \n"); );
        _SetTunerPLL(_u16TunerPLL);
        msAPI_Tuner_SetIF();
    }
    else if ((DIFFERENCE(_u16RealtimeAFTBaseTunerPLL,_u16TunerPLL) <= TUNER_PLL_PLUS_2MHz))
    {
    #if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)
       int  i;
    #endif

        eFreqDev = MDrv_IFDM_GetFreqDev();
        DEBUG_AFT( printf("[AFT-3: 0x%X] \n", eFreqDev) );

    #if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)
       for ( i = 0; i <= TUNER_PLL_PLUS_2MHz ; i++ )
    #endif
        {
            switch ( eFreqDev ) //fine tuning in AFC windows
            {
                case E_AFC_BELOW_MINUS_187p5KHz:
                    DEBUG_AFCWIN( printf("E_AFC_BELOW_MINUS_187p5KHz (%d)\n", E_AFC_BELOW_MINUS_187p5KHz) );
                    _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_187p5KHz) );
                    break;

                case E_AFC_MINUS_162p5KHz:
                    DEBUG_AFCWIN( printf("E_AFC_MINUS_162p5KHz (%d)\n", E_AFC_MINUS_162p5KHz) );
                    _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_162p5KHz) );
                    break;

                case E_AFC_MINUS_137p5KHz:
                    DEBUG_AFCWIN( printf("E_AFC_MINUS_137p5KHz (%d)\n", E_AFC_MINUS_137p5KHz) );
                    _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_137p5KHz) );
                    break;

                case E_AFC_MINUS_112p5KHz:
                    DEBUG_AFCWIN( printf("E_AFC_MINUS_112p5KHz (%d)\n", E_AFC_MINUS_112p5KHz) );
                    _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_112p5KHz) );
                    break;

                case E_AFC_MINUS_87p5KHz:
                    DEBUG_AFCWIN( printf("E_AFC_MINUS_87p5KHz (%d)\n", E_AFC_MINUS_87p5KHz) );
                    _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_87p5KHz) );
                    break;

                case E_AFC_MINUS_62p5KHz:
                    DEBUG_AFCWIN( printf("E_AFC_MINUS_62p5KHz (%d)\n", E_AFC_MINUS_62p5KHz) );
                    _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_62p5KHz) );
                    break;

                case E_AFC_MINUS_37p5KHz:
                    DEBUG_AFCWIN( printf("E_AFC_MINUS_37p5KHz (%d)\n", E_AFC_MINUS_37p5KHz) );
                  #if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)
                    return;
                  #else
                    _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_37p5KHz) );
                  #endif
                    break;

                case E_AFC_MINUS_12p5KHz:   return;
                case E_AFC_PLUS_12p5KHz:    return;

                case E_AFC_PLUS_37p5KHz:
                    DEBUG_AFCWIN( printf("E_AFC_PLUS_37p5KHz (%d)\n", E_AFC_PLUS_37p5KHz) );
                  #if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)
                    //To do the SW patch for Gemini-VIF
                    //Good signal = -2 ~ 1
                    // "2" is not good
                    _SetTunerPLL( PLLSTEP(-1) );
                  #else
                    _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_37p5KHz) );
                  #endif
                    break;

                case E_AFC_PLUS_62p5KHz:
                    DEBUG_AFCWIN( printf("E_AFC_PLUS_62p5KHz (%d)\n", E_AFC_PLUS_62p5KHz) );
                    _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_62p5KHz) );
                    break;

                case E_AFC_PLUS_87p5KHz:
                    DEBUG_AFCWIN( printf("E_AFC_PLUS_87p5KHz (%d)\n", E_AFC_PLUS_87p5KHz) );
                    _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_87p5KHz) );
                    break;

                case E_AFC_PLUS_112p5KHz:
                    DEBUG_AFCWIN( printf("E_AFC_PLUS_112p5KHz (%d)\n", E_AFC_PLUS_112p5KHz) );
                    _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_112p5KHz) );
                    break;

                case E_AFC_PLUS_137p5KHz:
                    DEBUG_AFCWIN( printf("E_AFC_PLUS_137p5KHz (%d)\n", E_AFC_PLUS_137p5KHz) );
                    _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_137p5KHz) );
                    break;

                case E_AFC_PLUS_162p5KHz:
                    DEBUG_AFCWIN( printf("E_AFC_PLUS_162p5KHz (%d)\n", E_AFC_PLUS_162p5KHz) );
                    _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_162p5KHz) );
                    break;

                case E_AFC_ABOVE_PLUS_187p5KHz:
                    DEBUG_AFCWIN( printf("E_AFC_ABOVE_PLUS_187p5KHz (%d)\n", E_AFC_ABOVE_PLUS_187p5KHz) );
                    _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_187p5KHz) );
                    break;

              #if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)
                case E_AFC_OUT_OF_AFCWIN :
                    DEBUG_AFCWIN( printf("E_AFC_OUT_OF_AFCWIN (%d)\n", E_AFC_OUT_OF_AFCWIN) );
                    if(_u16TunerPLL > (_u16RealtimeAFTBaseTunerPLL+TUNER_PLL_PLUS_1MHz))             //+800KHz
                    {
                        _SetTunerPLL(_u16RealtimeAFTBaseTunerPLL+TUNER_PLL_PLUS_1MHz);
                    }
                    else if(_u16TunerPLL < (_u16RealtimeAFTBaseTunerPLL-TUNER_PLL_PLUS_1MHz))    //-500K
                    {
                        //_SetTunerPLL(PLLSTEP(22));// +1.3MHz
                        _SetTunerPLL(PLLSTEP(TUNER_PLL_PLUS_2MHz));// +2.0MHz
                    }
                    else
                    {
                        _SetTunerPLL( PLLSTEP(-6) );
                        i += (TUNER_PLL_PLUS_187p5KHz *2);
                    }
                    break;

                default:
                    return;
                    break;
              #else

                default://E_AFC_OUT_OF_AFCWIN
                    _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_0p25MHz) );
                    break;
              #endif
            }

            msAPI_Tuner_SetIF();
          #if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)
            MsOS_DelayTask(100);
            eFreqDev = MDrv_IFDM_GetFreqDev();
          #endif
        }

    #if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)
        u8ScanAFTFlag=1;
        u8ScanAFTCount = MAX_AFT_UPPER_BOUND;
    #endif
    }
    else
    {
        _SetTunerPLL(_u16RealtimeAFTBaseTunerPLL);
        msAPI_Tuner_SetIF();
    }
}


void _msAPI_Tuning_Start_SEARCHALL_PAL(void)
{
#if (TV_FREQ_SHIFT_CLOCK)
    msAPI_Tuner_Patch_TVShiftClk(FALSE);
#endif

    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE,E_AUDIO_INTERNAL_2_MUTEON,E_AUDIOMUTESOURCE_ATV);

    msAPI_Timer_Delayms(DELAY_FOR_ENTERING_MUTE);

    eAutoSearchType = E_AUTO_SEARCH_TYPE_ALLWAYUP;

    u8StartFrom = msAPI_ATV_GetCurrentProgramNumber();

    if ( eAutoSearchType == E_AUTO_SEARCH_TYPE_ALLWAYUP )
    {
      #if ENABLE_DBG_ATV_SCAN // for debug
        if (!_IsDbgTuning)
      #endif
        {
            _u16Tune_MAX_PLL = UHF_MAX_PLL;
            _u16Tune_LOW_PLL = VHF_LOWMIN_PLL;
        }
        _SetTunerPLL(_u16Tune_LOW_PLL);
    }
    else
    {
        _SetTunerPLL(UHF_MAX_PLL);

        _u16Tune_MAX_PLL = VHF_LOWMIN_PLL;
        _u16Tune_LOW_PLL = UHF_MAX_PLL;
    }

    _bIsAFTNeeded = TRUE;

    msAPI_AVD_TurnOffAutoAV();
#if ENABLE_TTX
    msAPI_TTX_ResetAcquisition();
#endif

    if (_bIsLSearch)
    {
        msAPI_AUD_SetAudioStandard((AUDIOSTANDARD_TYPE)E_AUDIOSTANDARD_L);
        u8SoundSystem = E_AUDIOSTANDARD_L;
    }
    else
    {
        msAPI_AUD_SetAudioStandard((AUDIOSTANDARD_TYPE)E_AUDIOSTANDARD_DK);
        u8SoundSystem = E_AUDIOSTANDARD_DK;


    }
    msAPI_Tuner_SetIF();

    _u8TVScanStepDownCount = 0;
    _bIsSpeedUp = TRUE;

    msAPI_AVD_SetHsyncDetectionForTuning(TRUE);

#if AUTO_SCAN_TIME_PRINT
    u32StartAutoTuningTime = msAPI_Timer_GetTime0();
#endif


  #if 1 // debug
    TUNING_FLOW_MSG(printf("\n %ld -> %ld ", _u16Tune_LOW_PLL, _u16Tune_MAX_PLL));

    TUNING_FLOW_MSG(printf("\n Scan %ld.%ld Mhz",                               \
                msAPI_CFT_ConvertPLLtoIntegerOfFrequency(_u16Tune_LOW_PLL),     \
                msAPI_CFT_ConvertPLLtoFractionOfFrequency(_u16Tune_LOW_PLL)));

    TUNING_FLOW_MSG(printf(" to %ld.%ld Mhz \n",                                \
                msAPI_CFT_ConvertPLLtoIntegerOfFrequency(_u16Tune_MAX_PLL),     \
                msAPI_CFT_ConvertPLLtoFractionOfFrequency(_u16Tune_MAX_PLL)));
  #endif
}



void _msAPI_Tuning_Start_SEARCHONETOUP_DOWN_PAL(void)
{
    U32 _eTempCurrentTuningState = _eCurrentTuningState;
    U16 u16TargetPLL;

#if (TV_FREQ_SHIFT_CLOCK)
    msAPI_Tuner_Patch_TVShiftClk(FALSE);
#endif

    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE,E_AUDIO_INTERNAL_2_MUTEON,E_AUDIOMUTESOURCE_ATV);

    msAPI_Timer_Delayms(DELAY_FOR_ENTERING_MUTE);

    if(_eTempCurrentTuningState == AFT_EXT_STEP_SEARCHONETOUP)
    {
        eAutoSearchType = E_AUTO_SEARCH_TYPE_ONETOUP;

        _u16Tune_MAX_PLL = UHF_MAX_PLL;
        _u16Tune_LOW_PLL = VHF_LOWMIN_PLL;
    }
    else
    {
        eAutoSearchType = E_AUTO_SEARCH_TYPE_ONETODOWN;

        _u16Tune_MAX_PLL = VHF_LOWMIN_PLL;
        _u16Tune_LOW_PLL = UHF_MAX_PLL;
    }

    if ( msAPI_AVD_IsAutoAVActive(E_AUTOAV_SOURCE_ALL) == TRUE )
    {
        msAPI_AVD_TurnOffAutoAV();
        msAPI_AVD_WaitForVideoSyncLock();
        msAPI_AVD_DetectVideoStandard(OPERATIONMETHOD_MANUALLY);
    }

#if ENABLE_TTX
    msAPI_TTX_ResetAcquisition();
#endif

#if (VIF_TUNER_TYPE==1)
    if (_bIsLSearch)
    {
        msAPI_AUD_SetAudioStandard((AUDIOSTANDARD_TYPE)E_AUDIOSTANDARD_L);
        u8SoundSystem = E_AUDIOSTANDARD_L;
        MDrv_IFDM_SetIF(IF_FREQ_L);
    }
    else
    {
        msAPI_AUD_SetAudioStandard((AUDIOSTANDARD_TYPE)E_AUDIOSTANDARD_DK);
        u8SoundSystem = E_AUDIOSTANDARD_DK;
        MDrv_IFDM_SetIF(IF_FREQ_DK);
    }

    _SetTunerPLL(_u16TunerPLL);
#endif

#if (VD_SYNC_CRITERION_CONFIG_ENABLE)
    if ( TRUE == msAPI_Tuner_VD_IsSyncDetected(SYNC_DETECTED_BASE_NUM, SYNC_DETECTED_PASS_NUM))
#else
    if ( TRUE == msAPI_AVD_IsSyncLocked())
#endif
    {
        if ( msAPI_AUD_GetAudioStandard() == E_AUDIOSTANDARD_M )
        {
            if(_eTempCurrentTuningState == AFT_EXT_STEP_SEARCHONETOUP)
                u16TargetPLL = ( PLLSTEP(TUNER_PLL_PLUS_4MHz) );
            else
                u16TargetPLL = ( PLLSTEP(TUNER_PLL_MINUS_4MHz) );


        }
        else
        {
            if(_eTempCurrentTuningState == AFT_EXT_STEP_SEARCHONETOUP)
                u16TargetPLL = ( PLLSTEP(TUNER_PLL_NEXT_CHANNEL_JUMP) );
            else
                u16TargetPLL = ( PLLSTEP((TUNER_PLL_NEXT_CHANNEL_JUMP*(-1))) );
        }

        _SetTunerPLL( u16TargetPLL );
    }

    _bIsAFTNeeded = TRUE;
    msAPI_Tuner_SetIF();
    msAPI_AVD_SetHsyncDetectionForTuning(TRUE);

  #if 1 // debug
    TUNING_FLOW_MSG(printf("\n %ld -> %ld ", _u16Tune_LOW_PLL, _u16Tune_MAX_PLL));

    TUNING_FLOW_MSG(printf("\n Scan %ld.%ld Mhz",                               \
                msAPI_CFT_ConvertPLLtoIntegerOfFrequency(_u16Tune_LOW_PLL),     \
                msAPI_CFT_ConvertPLLtoFractionOfFrequency(_u16Tune_LOW_PLL)));

    TUNING_FLOW_MSG(printf(" to %ld.%ld Mhz \n",                                \
                msAPI_CFT_ConvertPLLtoIntegerOfFrequency(_u16Tune_MAX_PLL),     \
                msAPI_CFT_ConvertPLLtoFractionOfFrequency(_u16Tune_MAX_PLL)));
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
U32 u32Get;
U32 u32Start;
U8 g_u8WaitAudioTime=10; // 100ms per step

#define DEBUG_AUDIO_DETECT_TIME 0

eAFTSTEP msAPI_Gettuingstatus(void)
{
    printf("_eCurrentTuningState = 0x%X \n", _eCurrentTuningState);
    return _eCurrentTuningState;
}

void _msAPI_Tuning_SetupNextFreqAndSys(U16 u16NewTunerPll)
{
#if( ENABLE_DEBUG_TUNING_TIME )
    U32 u32Time1 = MsOS_GetSystemTime();
    //U32 u32Time2 = MsOS_GetSystemTime();
#endif

    if ( (_bIsLSearch) && (u8SoundSystem == E_AUDIOSTANDARD_L) )
    {
        //printf("[SCAN] => S DK\n");
        msAPI_AUD_SetAudioStandard((AUDIOSTANDARD_TYPE)E_AUDIOSTANDARD_DK);
        u8SoundSystem = E_AUDIOSTANDARD_DK;

        // Use para as new tuner freq.
        if( u16NewTunerPll )
        {
            _u16TunerPLL = u16NewTunerPll;
        }

        if(_CheckLPrimeBoundary())
        {
            _SetTunerPLL(_u16TunerPLL);
        }

        msAPI_Tuner_SetIF();
    }
    else
    {
        if ( (_bIsLSearch) && (u8SoundSystem == E_AUDIOSTANDARD_DK) )
        {
            //printf("[SCAN] => S L\n");
            msAPI_AUD_SetAudioStandard((AUDIOSTANDARD_TYPE)E_AUDIOSTANDARD_L);
            u8SoundSystem = E_AUDIOSTANDARD_L;
        }

        // Deside new tuner freq is...
        u16JumpDistance = TUNER_PLL_PLUS_1MHz;

        if (  (eAutoSearchType == E_AUTO_SEARCH_TYPE_ALLWAYDOWN)
           || (eAutoSearchType == E_AUTO_SEARCH_TYPE_ONETODOWN) )
        {
            _u16TunerPLL = PLLSTEP( (u16JumpDistance*(-1)) );
        }
        else
        {
            _u16TunerPLL = PLLSTEP(u16JumpDistance);
        }

        _SetTunerPLL( _u16TunerPLL );
        msAPI_Tuner_SetIF();
    }

#if( ENABLE_DEBUG_TUNING_TIME )
    printf("_msAPI_Tuning_SetupNextFreqAndSys use %u\n", msAPI_Timer_DiffTime_2(u32Time1,MsOS_GetSystemTime()));
#endif

}

static void _msAPI_Tuning_Set_State( eAFTSTEP eState )
{
    if( _eCurrentTuningState == eState )
    {
        return;
    }

    // Save time for AFT_DETECTVIDEO
    if ( (eState == AFT_DETECTVIDEO)
       ||(eState == AFT_DETECTVIDEO_NTSC) )
    {
        s_Tuning_u32DetectVideoStartTime = MsOS_GetSystemTime();
    }

    _eCurrentTuningState = eState;
}

void _msAPI_Tuner_TuningProcessor(eAFTSTEP eState)
{
#if (FRONTEND_TUNER_TYPE == SILAB_2158_TUNER)
    S16 _u16TunerAFC;
#endif

    static U_INT32 u32VifVDLockCheckStart;
    static U_INT32 u32CNICheckStart;


#if ATVSCAN_USE_TIMER_DELAY
    static U_INT32 u32DetectAudioStart;
#endif
#if(ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
    AVD_VideoStandardType eVideoStandType = E_VIDEOSTANDARD_NOTSTANDARD;
#endif
    static BOOLEAN  bIsAutoTune = TRUE;

#if ENABLE_ATSC
    //printf("\e[31;1m [%d]: %s \33[m \n", __LINE__, __PRETTY_FUNCTION__);
    //printf("\e[31;1m !!! ATSC should not enter here !!! \33[m \n");
    return;
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
            return;
    }

  #if defined(AUTO_TUNING_DEBUG)
    {
        static eAFTSTEP _ePreTuningState;
        static U32 u32TuningStateTime;

        if ( _eCurrentTuningState != _ePreTuningState )
        {
            AUTO_TUNING_PRINT( printf("TUN_STATE: 0x%BX -> 0x%BX (%lu) \n",
                                      _ePreTuningState,
                                      _eCurrentTuningState,
                                      msAPI_Timer_DiffTimeFromNow(u32TuningStateTime)) );

            _ePreTuningState = _eCurrentTuningState;
            u32TuningStateTime = msAPI_Timer_GetTime0();
        }
    }

    if( _eCurrentTuningState != AFT_IDLE )
    {
        U8 u8locked;
      #if ((FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)||(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)||(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF) )
        printf(" VIF Lock = %x \n",(WORD)MDrv_VIF_Read_CR_LOCK_STATUS());
        printf(" FOE = %x \n",(WORD)MDrv_VIF_Read_CR_FOE());
      #endif
        MDrv_AVD_SetRegValue(0x3504, 0x21);
        u8locked= MDrv_AVD_GetRegValue(0x3501)&BIT3;
        printf(" VD lock=%x; VD_35CC=%X; ",(WORD)u8locked, MDrv_Read2Byte(0x1035CC));
    }
  #endif // #if defined(AUTO_TUNING_DEBUG)


    switch ( _eCurrentTuningState )
    {
        case AFT_IDLE:
            if (  (E_INPUT_SOURCE_ATV != msAPI_AVD_GetVideoSource())
               || ( E_INPUT_SOURCE_ATV == msAPI_AVD_GetVideoSource()
                  && TRUE == msAPI_AVD_IsAutoAVActive(E_AUTOAV_SOURCE_ALL) )
               || (_bIsAFTNeeded == FALSE)
               || (IS_RT_AFT_ENABLED == FALSE) )
            {
                u8ScanAFTCount = 0;
                return;
            }

            msAPI_Tuning_GetStationName();

            _u16AFTIdleTimer++;
            if (_u16AFTIdleTimer >= 19)
            {
                _u16AFTIdleTimer = 1;
                _msAPI_Tuning_AutoFineTuning();
            }
            return;


        case AFT_EXT_STEP_SEARCHALL:
            TUNING_FLOW_MSG(printf("\r\n AFT_EXT_STEP_SEARCHALL \n"));
            bIsAutoTune = TRUE;
            _msAPI_Tuning_Start_SEARCHALL_PAL();
            _eCurrentTuningState = AFT_GOTO_CHECK_VIFLOCK;
            _u16PreviousStationTunerPLL = 0;
            break;


        case AFT_EXT_STEP_SEARCHONETOUP:
        case AFT_EXT_STEP_SEARCHONETODOWN:
            TUNING_FLOW_MSG(printf(" %s \n",
                ((_eCurrentTuningState==AFT_EXT_STEP_SEARCHONETOUP)?(AFT_EXT_STEP_SEARCHONETOUP):(AFT_EXT_STEP_SEARCHONETODOWN))));

            bIsAutoTune = FALSE;
            _msAPI_Tuning_Start_SEARCHONETOUP_DOWN_PAL();
            _eCurrentTuningState = AFT_GOTO_CHECK_VIFLOCK;
            break;


        case AFT_GOTO_CHECK_VIFLOCK:
            TUNING_FLOW_MSG(printf(" AFT_GOTO_CHECK_VIFLOCK [%ld.%ld Mhz] \n", \
                        msAPI_CFT_ConvertPLLtoIntegerOfFrequency(_u16TunerPLL), \
                        msAPI_CFT_ConvertPLLtoFractionOfFrequency(_u16TunerPLL)));
            u32VifVDLockCheckStart = msAPI_Timer_GetTime0();
            _eCurrentTuningState = AFT_CHECK_VIFLOCK;
            break;


        case AFT_CHECK_VIFLOCK:
            TUNING_FLOW_MSG(printf(" AFT_CHECK_VIFLOCK \n"););
            //AUTO_TUNING_SYNC_LOCK_PRINT("\n AFT_CHECK_VIFLOCK at %u ", MsOS_GetSystemTime());

            if (_GetVIFLockStatus()) //check if vif lock or not
            {
                _eCurrentTuningState = AFT_GOTO_CHECK_VDLOCK;
                TUNING_LOCK_MSG(printf(" VIF LOCK [%d ms] \n",msAPI_Timer_DiffTime(u32VifVDLockCheckStart, msAPI_Timer_GetTime0())));
            }
            else
            {
                if ( (msAPI_Timer_DiffTime(u32VifVDLockCheckStart, msAPI_Timer_GetTime0()))>ATVSCAN_VIFLOCK_TOTAL_CHECK_TIME) //next freq
                {
                    TUNING_NOLOCK_MSG(printf(" VIF no lock [status: 0x%X] \n",  \
                                                MDrv_VIF_Read_CR_LOCK_STATUS()));

                    // Setup next tuner freq and audio system
                    _msAPI_Tuning_SetupNextFreqAndSys(0);
                    _eCurrentTuningState = AFT_GOTO_CHECK_VIFLOCK;
                }
            }
            break;


        case AFT_GOTO_CHECK_VDLOCK:
            TUNING_FLOW_MSG(printf(" AFT_GOTO_CHECK_VDLOCK at %u\n", MsOS_GetSystemTime()); );
            u32VifVDLockCheckStart=msAPI_Timer_GetTime0();
            _eCurrentTuningState = AFT_CHECK_VDLOCK;
            break;


        case AFT_CHECK_VDLOCK:
        {
            TUNING_FLOW_MSG(printf(" AFT_CHECK_VDLOCK use %u\n", msAPI_Timer_DiffTime(u32VifVDLockCheckStart, msAPI_Timer_GetTime0()) ););
            U16 u16VdStatus = msAPI_AVD_CheckStatusLoop();

            TUNING_NOLOCK_MSG(printf(" u16VdStatus=0x%X\n", u16VdStatus););

            if (u16VdStatus & VD_CHECK_HSYNC_LOCKED)
            {
                _eCurrentTuningState = AFT_TUNING;
                u8NoSyncCount = 0;
                TUNING_LOCK_MSG(printf(" VD LOCK [%d ms] \n", msAPI_Timer_DiffTime(u32VifVDLockCheckStart, msAPI_Timer_GetTime0())));
            }
            else
            {
                if ( (msAPI_Timer_DiffTime(u32VifVDLockCheckStart, msAPI_Timer_GetTime0())) > ATVSCAN_VDLOCK_TOTAL_CHECK_TIME) //next freq
                {
                    TUNING_NOLOCK_MSG(printf(" VD no lock [status: 0x%X] \n", u16VdStatus));

                    // Setup next tuner freq and audio system
                    _msAPI_Tuning_SetupNextFreqAndSys(0);
                    _eCurrentTuningState = AFT_GOTO_CHECK_VIFLOCK;
                }
            }
        }
            break;


        case AFT_JUMPNEAR:
        case AFT_JUMPNEARHALF:

            if( _eCurrentTuningState == AFT_JUMPNEARHALF )
            {
                TUNING_FLOW_MSG(printf(" AFT_JUMPNEARHALF \n"));

              #if(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)
                u16JumpDistance = TUNER_PLL_PLUS_0p25MHz;
              #else
                u16JumpDistance = TUNER_PLL_PLUS_0p5MHz;
              #endif
            }
            else
            {
                TUNING_FLOW_MSG(printf(" AFT_JUMPNEAR \n"));

              #if((FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)||(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210||(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF)))
                u16JumpDistance = TUNER_PLL_PLUS_1MHz;
              #else
                u16JumpDistance = TUNER_PLL_PLUS_1p5MHz;
              #endif
            }

            if ( _IsLPrime() == TRUE )
            {
                if( _eCurrentTuningState == AFT_JUMPNEARHALF )
                    u16JumpDistance = TUNER_PLL_PLUS_0p2MHz;
                else
                    u16JumpDistance = TUNER_PLL_PLUS_0p75MHz;
            }

            if (  (eAutoSearchType == E_AUTO_SEARCH_TYPE_ALLWAYDOWN)
               || (eAutoSearchType == E_AUTO_SEARCH_TYPE_ONETODOWN) )
            {
                _SetTunerPLL( PLLSTEP( (u16JumpDistance*(-1)) ) );
            }
            else
            {
                _SetTunerPLL( PLLSTEP(u16JumpDistance) );
            }

            msAPI_Tuner_SetIF();

            _eCurrentTuningState = AFT_GOTO_CHECK_VIFLOCK;

            break;


        case AFT_TUNING:
        {
            TUNING_FLOW_MSG(printf(" AFT_TUNING \n"));
            //u16VdStatus = msAPI_AVD_CheckStatusLoop();
            eTuningStatus = _GetTuningStatus();
          #if (FRONTEND_TUNER_TYPE == SILAB_2158_TUNER)
            if(eTuningStatus == E_TUNING_STATUS_GOOD)
            {
                _u16TunerAFC = Si2158_GetATV_AFC_freq();
                if(_u16TunerAFC!=0)
                {
                    _SetTunerPLL( PLLSTEP(_u16TunerAFC) );
                }
            }
          #endif

            //TUNING_LOCK_MSG(printf("Tuning: 0x%04X, 0x%02BX\n", u16VdStatus, eTuningStatus));

            switch ( eTuningStatus )
            {
            case E_TUNING_STATUS_GOOD:

             #if(ENABLE_AUDIO_AUTO_DETECT)

                // for detect PAL MN
              #if ( (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)  \
                  ||(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)          \
                  ||(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF)   \
                  )
                MDrv_IFDM_BypassDBBAudioFilter(TRUE);
              #endif

                MApi_AUDIO_SIF_StartAutoStandardDetection();

              #if DEBUG_AUDIO_DETECT_TIME
                u32Start = msAPI_Timer_GetTime0();
                printf(">>> start0 %d", u32Start);
              #endif

                u32CNICheckStart = msAPI_Timer_GetTime0();

              #if ATVSCAN_USE_TIMER_DELAY
                u32DetectAudioStart=msAPI_Timer_GetTime0();
              #endif

             #endif//(ENABLE_AUDIO_AUTO_DETECT)


             #if (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
                if (bIsAutoTune)
                {
                    msAPI_AVD_StartAutoStandardDetection();
                }
                else
                {
                    eVideoStandType = msAPI_ATV_GetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber());
                    if(eVideoStandType == E_VIDEOSTANDARD_AUTO)
                    {
                        msAPI_AVD_StartAutoStandardDetection();
                    }
                    else if(eVideoStandType == E_VIDEOSTANDARD_PAL_BGHI)
                    {
                        msAPI_AVD_ForceVideoStandard(E_VIDEOSTANDARD_PAL_BGHI);
                    }
                    else
                    {
                        msAPI_AVD_ForceVideoStandard(E_VIDEOSTANDARD_NTSC_M);
                    }
                }
             #else
                msAPI_AVD_StartAutoStandardDetection();
             #endif

             #if ENABLE_TTX
                msAPI_TTX_ResetAcquisition();
             #endif

                _msAPI_Tuning_Set_State(AFT_DETECTVIDEO);

                TUNING_FLOW_MSG(printf(" set to [%ld.%ld Mhz] \n", \
                        msAPI_CFT_ConvertPLLtoIntegerOfFrequency(_u16TunerPLL), \
                        msAPI_CFT_ConvertPLLtoFractionOfFrequency(_u16TunerPLL)));

                return; // <-<<<

            case E_TUNING_STATUS_OVER:
                _SetTunerPLL( PLLSTEP(-2) );
                break;

            case E_TUNING_STATUS_UNDER:
                _SetTunerPLL( PLLSTEP(2) );
                break;

            case E_TUNING_STATUS_OVER_LITTLE:
                _SetTunerPLL( PLLSTEP(-1) );
                break;

            case E_TUNING_STATUS_UNDER_LITTLE:
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

          #if AUTO_TUNING_FLOW_DEBUG
            if (  (eTuningStatus > E_TUNING_STATUS_GOOD)
               && (eTuningStatus < E_TUNING_STATUS_OUT_OF_AFCWIN) )
            {
                TUNING_LOCK_MSG(printf(" AFT_TUNING: 0x%02BX to", eTuningStatus));
                TUNING_FLOW_MSG(printf(" [%ld.%ld Mhz] \n", \
                        msAPI_CFT_ConvertPLLtoIntegerOfFrequency(_u16TunerPLL), \
                        msAPI_CFT_ConvertPLLtoFractionOfFrequency(_u16TunerPLL)));
            }
          #endif

            if ( (u8NoSyncCount++) == 20 )
            {
              #if ENABLE_TTX
                msAPI_TTX_ResetAcquisition();
                printf(" msAPI_TTX_ResetAcquisition \n");
              #endif

                _msAPI_Tuning_Set_State(AFT_DETECTVIDEO);
            }

            break;
        }
        /////////////////////////////////////////
        // end of case AFT_TUNING
        /////////////////////////////////////////

        case AFT_DETECTVIDEO:
        {
            TUNING_FLOW_MSG(printf(" AFT_DETECTVIDEO use %u\n", msAPI_Timer_DiffTime_2(s_Tuning_u32DetectVideoStartTime, MsOS_GetSystemTime()) ); );

            U16 u16StatusLoop = msAPI_AVD_CheckStatusLoop();
            TUNING_FLOW_MSG(printf(" u16StatusLoop=0x%X\n", u16StatusLoop ); );

            //printf(" _bIsLSearch=%u\n", _bIsLSearch);

            //check if lock audio carrier False signal
            if (  (_bIsLSearch)
               || (u16StatusLoop & (VD_CHECK_STATUS_RDY|VD_HSYNC_LOCKED)) )
            {
                //TUNING_FLOW_MSG( printf(" if( L && VD Lock )\n"); );

                if ( !(_bIsLSearch)
                   &&( ( (msAPI_AVD_CheckLockAudioCarrier()==TRUE)
                       &&(_u16TunerPLL <= (_u16PreviousStationTunerPLL+ (TUNER_PLL_PLUS_6p5MHz))))
                     ||(msAPI_AVD_CheckFalseChannel()) )
                   )
                {
                    printf(" abandan audio carrier [%d.%d MHz] \n",
                            msAPI_CFT_ConvertPLLtoIntegerOfFrequency(_u16TunerPLL),
                            msAPI_CFT_ConvertPLLtoFractionOfFrequency(_u16TunerPLL) );

                    _msAPI_Tuning_SetupNextFreqAndSys(0);
                    _eCurrentTuningState = AFT_GOTO_CHECK_VIFLOCK;
                    break;
                }


              #if (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
                {
                    if (bIsAutoTune)
                    {
                        AVD_VideoStandardType vdStd, vdstd1;
                        vdStd = msAPI_AVD_GetCurrentVideoStandard();
                        vdstd1 = msAPI_AVD_GetStandardDetection();
                        u8VideoSystem = vdStd;

                        if( (vdStd  != vdstd1)
                          ||(vdStd  == E_VIDEOSTANDARD_NOTSTANDARD)
                          ||(vdstd1 == E_VIDEOSTANDARD_NOTSTANDARD) )
                        {
                            if( msAPI_Timer_DiffTime_2(s_Tuning_u32DetectVideoStartTime, MsOS_GetSystemTime()) < ATVSCAN_VD_CHECKREADY_TIMEOUT )
                            {
                                //printf(" retry again \n");
                                break;
                            }
                        }
                        else
                        {
                            //printf("\r\n VD detect time =%d", msAPI_Timer_DiffTime_2(s_Tuning_u32DetectVideoStartTime, MsOS_GetSystemTime()));
                            TUNING_LOCK_MSG( printf(" VD: [%s:%u] <=>", msAPI_AVD_Get_StdString(vdStd), vdStd));
                            TUNING_LOCK_MSG( printf(" [%s:%u] \n", msAPI_AVD_Get_StdString(vdstd1), vdstd1) );
                        }
                    }
                    else
                    {
                        eVideoStandType = msAPI_ATV_GetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber());

                        if (eVideoStandType == E_VIDEOSTANDARD_AUTO)
                        {
                            eVideoStandType = msAPI_AVD_GetResultOfAutoStandardDetection();
                        }
                        else if (eVideoStandType == E_VIDEOSTANDARD_PAL_BGHI)
                        {
                            eVideoStandType = msAPI_AVD_GetStandardDetection();

                            if ( (eVideoStandType != E_VIDEOSTANDARD_PAL_BGHI)
                               &&(eVideoStandType != E_VIDEOSTANDARD_PAL_M)
                               &&(eVideoStandType != E_VIDEOSTANDARD_PAL_N)
                               &&(eVideoStandType != E_VIDEOSTANDARD_PAL_60) )
                            {
                                eVideoStandType = E_VIDEOSTANDARD_PAL_BGHI;
                            }

                            msAPI_AVD_SetVideoStandard(eVideoStandType);

                            msAPI_AVD_StartAutoStandardDetection();
                        }
                        else if (eVideoStandType == E_VIDEOSTANDARD_NTSC_M)
                        {
                            eVideoStandType = msAPI_AVD_GetStandardDetection();

                            if ( (eVideoStandType != E_VIDEOSTANDARD_NTSC_M)
                               &&(eVideoStandType != E_VIDEOSTANDARD_NTSC_44) )
                            {
                                eVideoStandType = E_VIDEOSTANDARD_NTSC_M;
                            }

                            msAPI_AVD_SetVideoStandard(eVideoStandType);

                            msAPI_AVD_StartAutoStandardDetection();
                        }

                        u8VideoSystem = eVideoStandType;
                    }
                }
              #else
                {
                    BOOL bDetectVideoSuccessful = TRUE;

                    //printf(" u8VideoSystem=%u\n", u8VideoSystem);
                    //printf(" u8SoundSystem=%s\n", (u8SoundSystem == E_AUDIOSTANDARD_L)? "L" : "DK" );

                    if ( bIsAutoTune )
                    {
                        AVD_VideoStandardType eVdStd_Stable, eVdStd_Current;

                        eVdStd_Stable = msAPI_AVD_GetCurrentVideoStandard();
                        eVdStd_Current = msAPI_AVD_GetStandardDetection();
                        u8VideoSystem = eVdStd_Stable;

                        //printf("Detect VD: %u %u\n", eVdStd_Stable, eVdStd_Current );

                        if ( (eVdStd_Stable  != eVdStd_Current)
                           ||(eVdStd_Stable  == E_VIDEOSTANDARD_NOTSTANDARD)
                           ||(eVdStd_Current == E_VIDEOSTANDARD_NOTSTANDARD)
                           ) // Detect failed
                        {
                            bDetectVideoSuccessful = FALSE;
                            //printf(" s_Tuning_u32DetectVideoStartTime=%u, %u\n", s_Tuning_u32DetectVideoStartTime, msAPI_Timer_DiffTime_2(s_Tuning_u32DetectVideoStartTime, MsOS_GetSystemTime()));
                            if ( msAPI_Timer_DiffTime_2(s_Tuning_u32DetectVideoStartTime, MsOS_GetSystemTime()) < ATVSCAN_VD_CHECKREADY_TIMEOUT )
                            {
                                //printf(" retry again \n");
                                break;
                            }
                        }
                        else
                        {
                            //printf(" VD detect time =%d \n", msAPI_Timer_DiffTime_2(s_Tuning_u32DetectVideoStartTime, MsOS_GetSystemTime()));
                            TUNING_LOCK_MSG( printf(" VD: [%s:%u] <=>", msAPI_AVD_Get_StdString(eVdStd_Stable), eVdStd_Stable));
                            TUNING_LOCK_MSG( printf(" [%s:%u] \n", msAPI_AVD_Get_StdString(eVdStd_Current), eVdStd_Current) );
                        }
                    }

                    // Check if video std with audio system
                    if(_bIsLSearch)
                    {
                        if (u8VideoSystem != E_VIDEOSTANDARD_SECAM) // PAL detect
                        {
                            if (u8SoundSystem == E_AUDIOSTANDARD_L) // Current is detect SECAM
                            {
                                printf(" AudioSys is L, but VD is not SECAM\n");
                                bDetectVideoSuccessful = FALSE;
                            }
                        }
                        else // SECAM_LL detect // SECAM_L detect
                        {
                            if (u8SoundSystem == E_AUDIOSTANDARD_DK)
                            {
                                printf(" AudioSys is DK, but VD is SECAM\n");
                                //bDetectVideoSuccessful = FALSE;
                            }
                        }
                    }

                    // If detect video faild, goto next system or freq
                    if ( bDetectVideoSuccessful == FALSE )
                    {
                        // Setup next tuner freq and audio system
                        _msAPI_Tuning_SetupNextFreqAndSys(0);
                        _eCurrentTuningState = AFT_GOTO_CHECK_VIFLOCK;
                        break;
                    }

                    _eCurrentTuningState = AFT_SHOWTIME2;
                    _bIsPreProgramDetected = TRUE;
                }
              #endif // #if (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)

              #if ATVSCAN_USE_TIMER_DELAY
              #else
                _u16AFTIdleTimer = 0;
              #endif

              #if NTSC_SYSTEM_DETECT
                if ( (u8VideoSystem == E_VIDEOSTANDARD_NTSC_M)
                   ||(u8VideoSystem == E_VIDEOSTANDARD_NTSC_44) )
                {
                    _eCurrentTuningState = AFT_GOTO_CHECK_VIFLOCK_NTSC;
                    _bIsPreProgramDetected = FALSE;
                }
                else
              #endif
                {
                    _eCurrentTuningState = AFT_SHOWTIME2;
                    _bIsPreProgramDetected = TRUE;
                }
            }
            else
            {
                // Check VD ready timeout
                if ( msAPI_Timer_DiffTime_2(s_Tuning_u32DetectVideoStartTime, MsOS_GetSystemTime()) > ATVSCAN_VD_CHECKREADY_TIMEOUT )
                {
                    TUNING_FLOW_MSG(printf("AFT_DETECTVIDEO: time out \n"));
                    _msAPI_Tuning_SetupNextFreqAndSys(0);
                    _eCurrentTuningState = AFT_GOTO_CHECK_VIFLOCK;
                }
            }
            break;
        }
        /////////////////////////////////////////
        // end of case AFT_DETECTVIDEO
        /////////////////////////////////////////

      #if NTSC_SYSTEM_DETECT
        case AFT_GOTO_CHECK_VIFLOCK_NTSC:
        {
            TUNING_FLOW_MSG(printf(" AFT_GOTO_CHECK_VIFLOCK_NTSC \n"));
            msAPI_AUD_SetAudioStandard((AUDIOSTANDARD_TYPE)E_AUDIOSTANDARD_M);
            u8SoundSystem = E_AUDIOSTANDARD_M;
            MDrv_IFDM_SetIF(IF_FREQ_MN);
            _SetTunerPLL( _u16TunerPLL );
            msAPI_Tuner_SetIF();
            msAPI_AVD_StartAutoStandardDetection();
            _eCurrentTuningState = AFT_CHECK_VIFLOCK_NTSC;
            u32VifVDLockCheckStart = msAPI_Timer_GetTime0();
            break;
        }
        /////////////////////////////////////////
        // end of case AFT_GOTO_CHECK_VIFLOCK_NTSC
        /////////////////////////////////////////

        case AFT_CHECK_VIFLOCK_NTSC:
        {
            TUNING_FLOW_MSG(printf(" AFT_CHECK_VIFLOCK_NTSC \n"));

            if (_GetVIFLockStatus()) //check if vif lock or not
            {
                _eCurrentTuningState = AFT_GOTO_CHECK_VDLOCK_NTSC;

                TUNING_LOCK_MSG(printf(" VIF LOCK [%d ms] \n",
                    msAPI_Timer_DiffTime(u32VifVDLockCheckStart, msAPI_Timer_GetTime0())));
            }
            else
            {
                if ( (msAPI_Timer_DiffTime(u32VifVDLockCheckStart, msAPI_Timer_GetTime0()))
                      > ATVSCAN_VIFLOCK_TOTAL_CHECK_TIME ) //next freq
                {
                    TUNING_NOLOCK_MSG(printf(" VIF no lock [status: 0x%X] \n",  \
                                                MDrv_VIF_Read_CR_LOCK_STATUS()));

                    // Setup next tuner freq and audio system
                    msAPI_AUD_SetAudioStandard((AUDIOSTANDARD_TYPE)E_AUDIOSTANDARD_DK);
                    u8SoundSystem = E_AUDIOSTANDARD_DK;
                    MDrv_IFDM_SetIF(IF_FREQ_DK);
                    _msAPI_Tuning_SetupNextFreqAndSys(0);
                    _eCurrentTuningState = AFT_GOTO_CHECK_VIFLOCK;
                }
            }
            break;
        }
        /////////////////////////////////////////
        // end of case AFT_CHECK_VIFLOCK_NTSC
        /////////////////////////////////////////

        case AFT_GOTO_CHECK_VDLOCK_NTSC:
        {
            TUNING_FLOW_MSG(printf(" AFT_GOTO_CHECK_VDLOCK_NTSC \n"));
            u32VifVDLockCheckStart = msAPI_Timer_GetTime0();
            _eCurrentTuningState = AFT_CHECK_VDLOCK_NTSC;
            break;
        }
        /////////////////////////////////////////
        // end of case AFT_GOTO_CHECK_VDLOCK_NTSC
        /////////////////////////////////////////

        case AFT_CHECK_VDLOCK_NTSC:
        {
            U16 u16StatusLoop = msAPI_AVD_CheckStatusLoop();
            TUNING_FLOW_MSG(printf(" AFT_CHECK_VDLOCK_NTSC(0x%X) \n", u16StatusLoop));
            if (u16StatusLoop & VD_CHECK_HSYNC_LOCKED)
            {
                TUNING_LOCK_MSG(printf(" VD LOCK [%d ms] \n",
                    msAPI_Timer_DiffTime(u32VifVDLockCheckStart, msAPI_Timer_GetTime0())));

                u8NoSyncCount = 0;
                _msAPI_Tuning_Set_State(AFT_DETECTVIDEO_NTSC);
            }
            else
            {
                if ( (msAPI_Timer_DiffTime(u32VifVDLockCheckStart, msAPI_Timer_GetTime0()))
                      > ATVSCAN_VDLOCK_TOTAL_CHECK_TIME ) //next freq
                {
                    TUNING_NOLOCK_MSG(printf(" VD no lock [status: 0x%X] \n", u16VdStatus));

                    // Setup next tuner freq and audio system
                    _msAPI_Tuning_SetupNextFreqAndSys(0);
                    _eCurrentTuningState = AFT_GOTO_CHECK_VIFLOCK;
                }
            }
            break;
        }
        /////////////////////////////////////////
        // end of case AFT_CHECK_VDLOCK_NTSC
        /////////////////////////////////////////

        case AFT_DETECTVIDEO_NTSC:
        {
            U16 u16StatusLoop = msAPI_AVD_CheckStatusLoop();
            TUNING_FLOW_MSG(printf(" AFT_DETECTVIDEO_NTSC(0x%X) \n", u16StatusLoop));
            if ( u16StatusLoop & (VD_CHECK_STATUS_RDY|VD_HSYNC_LOCKED) )
            {
                if (bIsAutoTune)
                {
                    AVD_VideoStandardType vdStd, vdstd1;
                    vdStd = msAPI_AVD_GetCurrentVideoStandard();
                    vdstd1 = msAPI_AVD_GetStandardDetection();
                    u8VideoSystem = vdStd;

                    if ( (vdStd  != vdstd1)
                       ||(vdStd  == E_VIDEOSTANDARD_NOTSTANDARD)
                       ||(vdstd1 == E_VIDEOSTANDARD_NOTSTANDARD) )
                    {
                        if( msAPI_Timer_DiffTime_2(s_Tuning_u32DetectVideoStartTime, MsOS_GetSystemTime()) < ATVSCAN_VD_CHECKREADY_TIMEOUT )
                        {
                            //printf(" retry again \n");
                            break;
                        }
                    }
                    else
                    {
                        //printf(" VD detect time = %d \n", msAPI_Timer_DiffTime_2(s_Tuning_u32DetectVideoStartTime, MsOS_GetSystemTime()));
                        TUNING_LOCK_MSG( printf(" VD: [%s:%u] <=>", msAPI_AVD_Get_StdString(vdStd), vdStd));
                        TUNING_LOCK_MSG( printf(" [%s:%u] \n", msAPI_AVD_Get_StdString(vdstd1), vdstd1) );
                    }
                }
                else
                {
                    eVideoStandType = msAPI_ATV_GetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber());

                    if (eVideoStandType == E_VIDEOSTANDARD_AUTO)
                    {
                        eVideoStandType = msAPI_AVD_GetResultOfAutoStandardDetection();
                    }
                    else if (eVideoStandType == E_VIDEOSTANDARD_PAL_BGHI)
                    {
                        eVideoStandType = msAPI_AVD_GetStandardDetection();

                        if ( (eVideoStandType != E_VIDEOSTANDARD_PAL_BGHI)
                           &&(eVideoStandType != E_VIDEOSTANDARD_PAL_M)
                           &&(eVideoStandType != E_VIDEOSTANDARD_PAL_N)
                           &&(eVideoStandType != E_VIDEOSTANDARD_PAL_60) )
                        {
                            eVideoStandType = E_VIDEOSTANDARD_PAL_BGHI;
                        }

                        msAPI_AVD_SetVideoStandard(eVideoStandType);

                        msAPI_AVD_StartAutoStandardDetection();
                    }
                    else if(eVideoStandType == E_VIDEOSTANDARD_NTSC_M)
                    {
                        eVideoStandType = msAPI_AVD_GetStandardDetection();

                        if ( (eVideoStandType != E_VIDEOSTANDARD_NTSC_M)
                           &&(eVideoStandType != E_VIDEOSTANDARD_NTSC_44) )
                        {
                            eVideoStandType = E_VIDEOSTANDARD_NTSC_M;
                        }

                        msAPI_AVD_SetVideoStandard(eVideoStandType);

                        msAPI_AVD_StartAutoStandardDetection();
                    }

                    u8VideoSystem = eVideoStandType;
                }

                _eCurrentTuningState = AFT_SHOWTIME2;
                _bIsPreProgramDetected = TRUE;
            }

            break;
        }
        /////////////////////////////////////////
        // end of case AFT_DETECTVIDEO_NTSC
        /////////////////////////////////////////
      #endif // #if NTSC_SYSTEM_DETECT


        case AFT_SHOWTIME2:
        {
            //TUNING_FLOW_MSG(printf(" AFT_SHOWTIME2 \n"));

          #if(ENABLE_AUDIO_AUTO_DETECT)
            if ( (msAPI_Timer_DiffTime(u32DetectAudioStart, msAPI_Timer_GetTime0())) > ATVSCAN_AUDIO_WAIT_TIME2 )
          #endif//(ENABLE_AUDIO_AUTO_DETECT)
            {
              #if(ENABLE_AUDIO_AUTO_DETECT)
                _eCurrentTuningState = AFT_DETECTAUDIO;
              #else
                _eCurrentTuningState = AFT_CHECK_CNI;
              #endif//(ENABLE_AUDIO_AUTO_DETECT)
            }

            _bIsOneProgramDetected = FALSE;
            break;
        }
        /////////////////////////////////////////
        // end of case AFT_SHOWTIME2
        /////////////////////////////////////////


        case AFT_DETECTAUDIO:
        {
            TUNING_FLOW_MSG(printf(" AFT_DETECTAUDIO \n"));

          #if DEBUG_AUDIO_DETECT_TIME
            u32Get = msAPI_Timer_GetTime0();

            printf("\n >>> Get0 %d",u32Get );
            if((msAPI_Timer_DiffTime(u32Start, u32Get))< (U32)g_u8WaitAudioTime*100)
                break;
          #endif

            // for detect PAL MN
           #if ((FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)||(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)||(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF) )
            MDrv_IFDM_BypassDBBAudioFilter(FALSE);
           #endif

            if ( msAPI_AUD_IsAudioDetected() == FALSE )
            {
                printf("Audio not detected \n");
                u16Record_FALSE_SIGNAL_TunerPLL = _u16TunerPLL;
                u16JumpDistance = TUNER_PLL_PLUS_0p25MHz;

                if ( (eAutoSearchType == E_AUTO_SEARCH_TYPE_ALLWAYDOWN)
                   ||(eAutoSearchType == E_AUTO_SEARCH_TYPE_ONETODOWN) )
                {
                    _SetTunerPLL( PLLSTEP( (u16JumpDistance*(-1)) ) );
                }
                else
                {
                    _SetTunerPLL( PLLSTEP(u16JumpDistance) );
                }
                _eCurrentTuningState = AFT_CHECK_FALSESIGNAL;
            }
            else
            {
                AUDIOSTANDARD_TYPE eAudioStandard, eAudioStd;

                _eCurrentTuningState = AFT_CHECK_CNI;

                eAudioStd = msAPI_AUD_GetResultOfAutoStandardDetection();
                eAudioStandard = msAPI_AUD_GetAudioStandard();
                TUNING_LOCK_MSG( printf(" Audio: [%s:%u] <=>", msAPI_AUD_Get_StdString(eAudioStd), eAudioStd) );
                TUNING_LOCK_MSG( printf(" [%s:%u] \n", msAPI_AUD_Get_StdString(eAudioStandard), eAudioStandard) );
            }
            break;
        }
        /////////////////////////////////////////
        // end of case AFT_DETECTAUDIO
        /////////////////////////////////////////


        case AFT_CHECK_FALSESIGNAL:
        {
            TUNING_FLOW_MSG(printf(" AFT_CHECK_FALSESIGNAL \n"));

            U16 u16VdStatus = msAPI_AVD_CheckStatusLoop();

            if( u16VdStatus & VD_CHECK_HSYNC_LOCKED)
            {
                _u16TunerPLL = u16Record_FALSE_SIGNAL_TunerPLL;
                _SetTunerPLL(_u16TunerPLL);
                msAPI_Tuner_SetIF();
                _eCurrentTuningState = AFT_CHECK_CNI;
            }
            else
            {
                printf(" Abandon FALSE SIGNAL = %d \n",msAPI_CFT_ConvertPLLtoIntegerOfFrequency(_u16TunerPLL));
                printf(".%dMHz \n",msAPI_CFT_ConvertPLLtoFractionOfFrequency(_u16TunerPLL));

                // Setup next tuner freq and audio system
                if ((_bIsLSearch)&&(u8SoundSystem == E_AUDIOSTANDARD_L))
                {
                    _msAPI_Tuning_SetupNextFreqAndSys(u16Record_FALSE_SIGNAL_TunerPLL);
                }
                else
                {
                    _msAPI_Tuning_SetupNextFreqAndSys(0);
                }
                _eCurrentTuningState = AFT_GOTO_CHECK_VIFLOCK;
            }
        }
            break;

        /////////////////////////////////////////
        // end of case AFT_CHECK_FALSESIGNAL
        /////////////////////////////////////////


        case AFT_CHECK_CNI:
        {
            BOOLEAN bGetTTX;
            bGetTTX = TRUE;

            TUNING_FLOW_MSG(printf(" AFT_CHECK_CNI \n"));

         #if (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
            if ( (u8VideoSystem == E_VIDEOSTANDARD_NTSC_M)
               ||(u8VideoSystem == E_VIDEOSTANDARD_NTSC_44) )
            {
                TUNING_FLOW_MSG(printf(" AFT_CHECK_CNI - no TTX in NTSC \n"));
                bGetTTX = FALSE;
            }
         #endif

         #if ENABLE_TTX
          #if ATVSCAN_SORT_BY_STATION_NAME
            if ( msAPI_TTX_GetStationNameFromTeletext(_sCurrentStationName, MAX_STATION_NAME, &u8SortingPriority)
               &&(bGetTTX))
            {
                TUNING_FLOW_MSG(printf(" AFT_CHECK_CNI - get TTX \n"));
                //AUTO_TUNING_SYNC_LOCK_PRINT("\r\n CNI get time %d",msAPI_Timer_DiffTime(u32CNICheckStart, msAPI_Timer_GetTime0()));
                //printf("\r\n CNI get time %d",msAPI_Timer_DiffTime(u32CNICheckStart, msAPI_Timer_GetTime0()));
                _eCurrentTuningState = AFT_MEMORIZEPRDATA;
            }
            else if ( ((msAPI_Timer_DiffTime(u32CNICheckStart, msAPI_Timer_GetTime0())) > ATVSCAN_CNI_TOTAL_CHECK_TIME)
                    ||(bGetTTX == FALSE) )
          #endif
         #endif
            {
                TUNING_FLOW_MSG(printf(" AFT_CHECK_CNI - no TTX over 3sec \n"));
                msAPI_Tuner_UpdateMediumAndChannelNumber();
                msAPI_Tuner_ConvertMediumAndChannelNumberToString(_eMedium, _u8ChannelNumber, _sCurrentStationName);
                u8SortingPriority = LOWEST_SORTING_PRIORITY;
                _eCurrentTuningState = AFT_MEMORIZEPRDATA;
            }
            break;
        }
        /////////////////////////////////////////
        // end of case AFT_CHECK_CNI
        /////////////////////////////////////////


        case AFT_MEMORIZECHDATA:
            break;


        case AFT_MEMORIZEPRDATA:
            TUNING_FLOW_MSG(printf(" AFT_MEMORIZEPRDATA \n"));
            _u16PreviousStationTunerPLL = _u16TunerPLL;

            switch ( eAutoSearchType )
            {
            case E_AUTO_SEARCH_TYPE_ALLWAYUP:
            case E_AUTO_SEARCH_TYPE_ALLWAYDOWN:

                msAPI_Tuner_UpdateMediumAndChannelNumber();

                msAPI_ATV_SetProgramPLLData(msAPI_ATV_GetCurrentProgramNumber(), _u16TunerPLL);

              #if (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
                if ( (u8VideoSystem == E_VIDEOSTANDARD_NTSC_M)
                   ||(u8VideoSystem == E_VIDEOSTANDARD_NTSC_44)
                   ||(u8VideoSystem == E_VIDEOSTANDARD_PAL_M)
                   ||(u8VideoSystem == E_VIDEOSTANDARD_PAL_N) )
                {
                    u8AudioStandard = E_AUDIOSTANDARD_M;
                }
                else
              #endif
                {
                    u8AudioStandard = msAPI_AUD_GetAudioStandard();
                }
                msAPI_ATV_SetAudioStandard(msAPI_ATV_GetCurrentProgramNumber(), u8AudioStandard);

              #if(ENABLE_AUDIO_AUTO_DETECT)
                u8AudioMode = (AUDIOMODE_TYPE) MApi_AUDIO_SIF_GetSoundMode();
              #else
                u8AudioMode = E_AUDIOMODE_MONO;
              #endif//(ENABLE_AUDIO_AUTO_DETECT)
                msAPI_ATV_SetAudioMode(E_AUDIOSOURCE_ATV, u8AudioMode);

                msAPI_ATV_SkipProgram(msAPI_ATV_GetCurrentProgramNumber(), FALSE);

            #if 0//(CM_MULTI_FAVORITE)
                msAPI_ATV_SetFavoriteProgram(msAPI_ATV_GetCurrentProgramNumber(), FALSE, E_FAVORITE_TYPE_ALL);
            #else
                msAPI_ATV_SetFavoriteProgram(msAPI_ATV_GetCurrentProgramNumber(), FALSE);
            #endif

                msAPI_ATV_LockProgram(msAPI_ATV_GetCurrentProgramNumber(), FALSE);

            #if ENABLE_DVBC_PLUS_DTMB_CHINA_APP
                msAPI_ATV_SetProgramAntenna(msAPI_ATV_GetCurrentProgramNumber(), (!IsDVBCInUse()));
            #endif

                msAPI_ATV_NeedAFT(msAPI_ATV_GetCurrentProgramNumber(), TRUE);

                msAPI_ATV_SetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber(), msAPI_AVD_GetVideoStandard());

                msAPI_AVD_WaitForVideoSyncLock();

                msAPI_ATV_SetStationName(msAPI_ATV_GetCurrentProgramNumber(), _sCurrentStationName);

                msAPI_ATV_SetSortingPriority(u8SortingPriority);
                msAPI_ATV_SetMediumAndChannelNumber(msAPI_ATV_GetCurrentProgramNumber(), _eMedium, _u8ChannelNumber);

                _eCurrentTuningState = AFT_INCREASEPRNUMBER;

            #if ENABLE_AUTOTEST
                if(g_bAutobuildDebug)
                {
                    printf("31_ATV_Tuning\n");
                }
            #endif
                printf(" CH: %2d,  Audio: [%s:%u] \n",
                        msAPI_ATV_GetCurrentProgramNumber(),
                        msAPI_AUD_Get_StdString(msAPI_ATV_GetAudioStandard(msAPI_ATV_GetCurrentProgramNumber())),
                        msAPI_ATV_GetAudioStandard(msAPI_ATV_GetCurrentProgramNumber()) );
                break;


            case E_AUTO_SEARCH_TYPE_ONETOUP:
            case E_AUTO_SEARCH_TYPE_ONETODOWN:
                msAPI_Tuner_UpdateMediumAndChannelNumber();

                _DetectStationName();

                msAPI_ATV_SetProgramPLLData(msAPI_ATV_GetCurrentProgramNumber(), _u16TunerPLL);
                msAPI_ATV_SetAudioStandard(msAPI_ATV_GetCurrentProgramNumber(), msAPI_AUD_GetAudioStandard());

              #if(ENABLE_AUDIO_AUTO_DETECT)
                u8AudioMode = (AUDIOMODE_TYPE) MApi_AUDIO_SIF_GetSoundMode();
              #else
                u8AudioMode = E_AUDIOMODE_MONO;
              #endif//(ENABLE_AUDIO_AUTO_DETECT)
                msAPI_ATV_SetAudioMode(E_AUDIOSOURCE_ATV, u8AudioMode);

                msAPI_ATV_SkipProgram(msAPI_ATV_GetCurrentProgramNumber(), FALSE);
            #if 0//(CM_MULTI_FAVORITE)
                msAPI_ATV_SetFavoriteProgram(msAPI_ATV_GetCurrentProgramNumber(), FALSE, E_FAVORITE_TYPE_ALL);
            #else
                msAPI_ATV_SetFavoriteProgram(msAPI_ATV_GetCurrentProgramNumber(), FALSE);
            #endif

                msAPI_ATV_LockProgram(msAPI_ATV_GetCurrentProgramNumber(), FALSE);

            #if ENABLE_DVBC_PLUS_DTMB_CHINA_APP
                msAPI_ATV_SetProgramAntenna(msAPI_ATV_GetCurrentProgramNumber(), (!IsDVBCInUse()));
            #endif

                msAPI_ATV_NeedAFT(msAPI_ATV_GetCurrentProgramNumber(), TRUE);
                msAPI_ATV_SetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber(), msAPI_AVD_GetVideoStandard());
                msAPI_AVD_WaitForVideoSyncLock();

                msAPI_ATV_SetStationName(msAPI_ATV_GetCurrentProgramNumber(), _sCurrentStationName);
                msAPI_ATV_SetSortingPriority(u8SortingPriority);
                msAPI_ATV_SetMediumAndChannelNumber(msAPI_ATV_GetCurrentProgramNumber(), _eMedium, _u8ChannelNumber);

                _eCurrentTuningState = AFT_COMPLETE;
            #if ENABLE_AUTOTEST
                if(g_bAutobuildDebug)
                {
                    printf("31_ATV_Manual_Tuning\n");
                }
            #endif
                printf(" prog=%d,  Audio STD = [%s:%u] \n",
                        msAPI_ATV_GetCurrentProgramNumber(),
                        msAPI_AUD_Get_StdString(msAPI_ATV_GetAudioStandard(msAPI_ATV_GetCurrentProgramNumber())),
                        msAPI_ATV_GetAudioStandard(msAPI_ATV_GetCurrentProgramNumber()) );
                break;

            default:
                break;
            } // switch ( eAutoSearchType )

            _bIsOneProgramDetected = TRUE;

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
                    if ((_bIsLSearch)&&(u8SoundSystem == E_AUDIOSTANDARD_DK))
                    {
                        msAPI_AUD_SetAudioStandard((AUDIOSTANDARD_TYPE)E_AUDIOSTANDARD_L);
                        u8SoundSystem = E_AUDIOSTANDARD_L;
                        msAPI_Tuner_SetIF();
                    }
                #if (VIF_TUNER_TYPE==1)
                   else if ((_bIsLSearch)&&(u8SoundSystem == E_AUDIOSTANDARD_L))
                    {
                        msAPI_AUD_SetAudioStandard((AUDIOSTANDARD_TYPE)E_AUDIOSTANDARD_DK);
                        u8SoundSystem = E_AUDIOSTANDARD_DK;
                        MDrv_IFDM_SetIF(IF_FREQ_DK);
                        msAPI_Tuner_SetIF();
                    }
                   else
                    {
                        msAPI_AUD_SetAudioStandard((AUDIOSTANDARD_TYPE)E_AUDIOSTANDARD_DK);
                        u8SoundSystem = E_AUDIOSTANDARD_DK;
                        MDrv_IFDM_SetIF(IF_FREQ_DK);
                        msAPI_Tuner_SetIF();
                    }
                 #endif

                    if ( _IsLPrime() == TRUE )
                    {
                        _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_2p75MHz) );
                    }
                    else
                    {
                        _SetTunerPLL( PLLSTEP(TUNER_PLL_NEXT_CHANNEL_JUMP) );
                    }

                    _eCurrentTuningState = AFT_GOTO_CHECK_VIFLOCK;
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

                    _eCurrentTuningState = AFT_GOTO_CHECK_VIFLOCK;
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

            default:
                break;
            }

            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE,E_AUDIO_INTERNAL_2_MUTEOFF,E_AUDIOMUTESOURCE_ATV);
          #if ENABLE_TTX
            msAPI_TTX_ResetAcquisition();
          #endif
            //msAPI_VD_ClearSyncCheckCounter();

            msAPI_AVD_ClearAspectRatio();

            //if(msAPI_AVD_IsVideoFormatChanged())//20100330EL
                msAPI_AVD_SetIsVideoFormatChangedAsFalse();//20100330EL

            eAutoSearchType = E_AUTO_SEARCH_TYPE_STOPED;

            msAPI_AVD_SetHsyncDetectionForTuning(FALSE);

          #if AUTO_SCAN_TIME_PRINT
            printf("\n2 Total Auto Tuning Time: %lu\n", msAPI_Timer_DiffTimeFromNow(u32StartAutoTuningTime));
          #endif

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

        default:
            break;
    }
    // end of switch ( _eCurrentTuningState )

    /**************************************************************************/

    switch ( eAutoSearchType )
    {
        case E_AUTO_SEARCH_TYPE_ALLWAYUP:
            if ( _u16TunerPLL >= _u16Tune_MAX_PLL )
            {
              #if ENABLE_DBG_ATV_SCAN // for debug
                if ( (_IsDbgTuning) && (_u8DbgTuningLoopTime > 1) )
                {
                    _SetTunerPLL(_u16Tune_LOW_PLL);
                    msAPI_Tuner_SetIF();
                    _eCurrentTuningState = AFT_GOTO_CHECK_VIFLOCK;

                    _u8DbgTuningLoopTime--;
                    if (_u8DbgTuningLoopTime == 1)
                    {
                        _IsDbgTuning = 0;
                        _u8DbgTuningLoopTime = 0;
                        _bChangeProgram = FALSE;
                    }
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
            if ( _u16TunerPLL <= _u16Tune_LOW_PLL )
            {
                _eCurrentTuningState = AFT_COMPLETE;
                _bChangeProgram = FALSE;
            }
            break;

        case E_AUTO_SEARCH_TYPE_ONETOUP:
            if ( _u16TunerPLL >= _u16Tune_MAX_PLL )
            {
                _eCurrentTuningState = AFT_COMPLETE;
                _bChangeProgram = FALSE;
            }
            break;

        case E_AUTO_SEARCH_TYPE_ONETODOWN:
            if ( _u16TunerPLL <= _u16Tune_MAX_PLL )
            {
                _eCurrentTuningState = AFT_COMPLETE;
                _bChangeProgram = FALSE;
            }
            break;

        default:
            break;
    }
}


U8 _msAPI_Tuner_GetTuningProcessPercent(void)
{
    U8 u8Percent = 0;

  #if 1
    if ( _eCurrentTuningState == AFT_IDLE ||
         _eCurrentTuningState == AFT_EXT_STEP_SEARCHALL )
    {
        return 0;
    }

    if ( _u16Tune_MAX_PLL >= _u16Tune_LOW_PLL )
    {
        u8Percent = (U8)(((_u16TunerPLL - _u16Tune_LOW_PLL)+1)*100 / (_u16Tune_MAX_PLL - _u16Tune_LOW_PLL)) ;
    }
    else
    {
        u8Percent = (U8)(((_u16TunerPLL - _u16Tune_MAX_PLL)+1)*100 / (_u16Tune_LOW_PLL - _u16Tune_MAX_PLL)) ;
    }
  #else
    U32 u32UHFMAXPLL;
    U32 u32VHFLOWMINPLL;
    U32 u32TunerPLL;

    if ( _eCurrentTuningState == AFT_IDLE ||
         _eCurrentTuningState == AFT_EXT_STEP_SEARCHALL )
    {
        return 0;
    }

    u32UHFMAXPLL = UHF_MAX_PLL;
    u32VHFLOWMINPLL = VHF_LOWMIN_PLL;

    u32TunerPLL = _u16TunerPLL;

    if ( (u32UHFMAXPLL - u32VHFLOWMINPLL) )
    {
        u8Percent = (U8)(((u32TunerPLL - u32VHFLOWMINPLL)+1)*100 / (u32UHFMAXPLL - u32VHFLOWMINPLL)) ;
    }
  #endif

    return u8Percent;
}


#if ENABLE_DBG_ATV_SCAN // for debug

void MApp_DbgATV_Scan(DWORD dwMinPLL, DWORD dwMaxPLL, U8 bNumber)
{
    WORD wIntegerOfFreq;
    WORD wFractionOfFreq;

    _IsDbgTuning = TRUE;
    _u8DbgTuningLoopTime = bNumber;

    //printf("\n\e[31;1m >> %s \33[m \n", __FUNCTION__);

    //printf(" [%d -> %d] \n", dwMinPLL, dwMaxPLL);

    wIntegerOfFreq  = dwMinPLL/100;
    wFractionOfFreq = dwMinPLL%100;
    //printf(" [%d.%d] \n", wIntegerOfFreq, wFractionOfFreq);

    wIntegerOfFreq  = dwMaxPLL/100;
    wFractionOfFreq = dwMaxPLL%100;
    //printf(" [%d.%d] \n", wIntegerOfFreq, wFractionOfFreq);

#if TN_FREQ_STEP == FREQ_STEP_62_5KHz
    _u16Tune_LOW_PLL = dwMinPLL * 10 * 10 / 625;;
    _u16Tune_MAX_PLL = dwMaxPLL * 10 * 10 / 625;;
#elif TN_FREQ_STEP == FREQ_STEP_50KHz
    _u16Tune_LOW_PLL = dwMinPLL * 10 / 50;;
    _u16Tune_MAX_PLL = dwMaxPLL * 10 / 50;;
#else
    _u16Tune_LOW_PLL = dwMinPLL * 10 * 100 / 3125;;
    _u16Tune_MAX_PLL = dwMaxPLL * 10 * 100 / 3125;;
#endif // TN_FREQ_STEP

    if ( _u16Tune_LOW_PLL < VHF_LOWMIN_PLL )
        _u16Tune_LOW_PLL = VHF_LOWMIN_PLL;

    if ( _u16Tune_MAX_PLL > UHF_MAX_PLL )
        _u16Tune_MAX_PLL = UHF_MAX_PLL;

    //printf(" [%d -> %d] \n", _u16Tune_LOW_PLL, _u16Tune_MAX_PLL);
}

#endif


/******************************************************************************/

