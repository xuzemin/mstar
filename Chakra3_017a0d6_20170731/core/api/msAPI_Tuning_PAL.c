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
#include "debug.h"

#include "msAPI_ATVSystem.h"
#include "msAPI_Timer.h"
#include "IF_Demodulator.h"
#include "MApp_ATV_Scan.h"
#include "ZUI_tables_h.inl"

//------------------------------------------------------
//
//------------------------------------------------------
    static AUTO_SEARCH_TYPE eAutoSearchType;
    static U8 u8NoSyncCount;
    static U8 u8StartFrom;
    static U16 u16PreviosTunerPLL;
    U16 u16JumpDistance;
    TUNING_STATUS eTuningStatus;
static U16 u16VdStatus;
    U8 u8SortingPriority;


#if TV_SCAN_PAL_SECAM_ONCE//Define for variable
    static U16 u16Record_BG_Sync_PLL_BASE;//Sync SECAM-L and BG Base
    static U8   bNeedToRecord_BG_Sync_PLL;//Sync SECAM-L and BG Base
    //FRANCE_SUPPORT_DOUBLE_CHECK_L
    static BOOLEAN bDoubleCheckL;
    static U8 bDoubleCheckL_State;
    static U16 u16BGLockedPLL;
    #define DOUBLE_CHECK_L_STATE_FALSE          0
    #define DOUBLE_CHECK_L_STATE_FOUND_BG       1
    #define DOUBLE_CHECK_L_STATE_FOUND_L        2
    static U16 u16Record_FALSE_SIGNAL_TunerPLL;

#endif

#if AUTO_SCAN_TIME_PRINT
    static U32 u32StartAutoTuningTime;
#endif

#if ENABLE_AUTOTEST
    extern BOOLEAN g_bAutobuildDebug;
#endif
//------------------------------------------------------
//
//------------------------------------------------------

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
  #if 0 // Marked by coverity_0150
    else if ( eFreqDev >= E_AFC_ABOVE_PLUS_187p5KHz )
    {
        return E_TUNING_STATUS_OVER_MORE;
    }

    else
    {
        /* ASSERT */
    }

    return E_TUNING_STATUS_GOOD;
  #else
    else // only 8
    {
        return E_TUNING_STATUS_OVER_MORE;
    }
  #endif
}

void msAPI_Tuning_GetStationName(void) //move to tuning.c
{
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
}

#if (FRONTEND_TUNER_TYPE == SILAB_2158_TUNER)
extern S16 Si2158_GetATV_AFC_freq(void);
#endif
void _msAPI_Tuning_AutoFineTuning(void)
{
    #define MAX_AFT_UPPER_BOUND 30
    #define MAX_AFT_LOWER_THRES (MAX_AFT_UPPER_BOUND/3)
    #define MAX_AFT_UPPER_THRES (MAX_AFT_LOWER_THRES*2)
    #define MAX_AFT_GOOD_LEAK   (MAX_AFT_UPPER_BOUND/10)

    AFC eFreqDev;
#if (FRONTEND_TUNER_TYPE == SILAB_2158_TUNER)
    S16 _u16TunerAFC;
#endif

    if (_GetTuningStatus() == E_TUNING_STATUS_GOOD)
    {
        if (u8ScanAFTCount >= MAX_AFT_GOOD_LEAK)
            u8ScanAFTCount -= MAX_AFT_GOOD_LEAK;
        else
            u8ScanAFTCount =0;
        #if (FRONTEND_TUNER_TYPE == SILAB_2158_TUNER)
        if(Si2158_GetATV_AFC_freq() != 0)
        {
            _u16TunerAFC = Si2158_GetATV_AFC_freq();
            _SetTunerPLL( PLLSTEP(_u16TunerAFC) );
        }
        #endif

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
            //AUTO_TUNING_PRINT(printf("BaseFre=%3.2f ",(float)_TunerPLLDbg(_u16RealtimeAFTBaseTunerPLL)));
            //AUTO_TUNING_PRINT(printf("CurFre=%3.2f \n",(float)_TunerPLLDbg(_u16TunerPLL)));
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
    else if ((DIFFERENCE(_u16RealtimeAFTBaseTunerPLL,_u16TunerPLL) > TUNER_PLL_PLUS_2MHz )
              &&(eFreqDev == E_AFC_OUT_OF_AFCWIN))
    {   // roll PLL to +/- 2MHz
        if (_u16RealtimeAFTBaseTunerPLL>_u16TunerPLL)
            _u16TunerPLL = _u16RealtimeAFTBaseTunerPLL + TUNER_PLL_PLUS_2MHz;
        else
            _u16TunerPLL = _u16RealtimeAFTBaseTunerPLL - TUNER_PLL_PLUS_2MHz;

        _SetTunerPLL(_u16TunerPLL);
        msAPI_Tuner_SetIF();
    }
    else if ((DIFFERENCE(_u16RealtimeAFTBaseTunerPLL,_u16TunerPLL) <= TUNER_PLL_PLUS_2MHz))
    {

    #if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)
       int  i;
    #endif
        eFreqDev = MDrv_IFDM_GetFreqDev();
        debugTuningPrint("AFT: 0x%bx\n", eFreqDev);

#if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)
       for ( i = 0; i <= TUNER_PLL_PLUS_2MHz ; i++ )
#endif
       {
        switch ( eFreqDev ) //fine tuning in AFC windows
        {
            case E_AFC_BELOW_MINUS_187p5KHz:    _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_187p5KHz) );break;
            case E_AFC_MINUS_162p5KHz:  _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_162p5KHz) );   break;
            case E_AFC_MINUS_137p5KHz:  _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_137p5KHz) );   break;
            case E_AFC_MINUS_112p5KHz:  _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_112p5KHz) );   break;
            case E_AFC_MINUS_87p5KHz:   _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_87p5KHz) );    break;
            case E_AFC_MINUS_62p5KHz:   _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_62p5KHz) );    break;
            case E_AFC_MINUS_37p5KHz:
#if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)
                        return;
#else
                _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_37p5KHz) );
#endif
                break;
            case E_AFC_MINUS_12p5KHz:   return;
            case E_AFC_PLUS_12p5KHz:    return;
            case E_AFC_PLUS_37p5KHz:
#if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)
                      //To do the SW patch for Gemini-VIF
                      //Good signal = -2 ~ 1
                      // "2" is not good
                       _SetTunerPLL( PLLSTEP(-1) );
#else
                _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_37p5KHz) );
#endif
                break;
            case E_AFC_PLUS_62p5KHz:    _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_62p5KHz) );   break;
            case E_AFC_PLUS_87p5KHz:    _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_87p5KHz) );   break;
            case E_AFC_PLUS_112p5KHz:   _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_112p5KHz) );  break;
            case E_AFC_PLUS_137p5KHz:   _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_137p5KHz) );  break;
            case E_AFC_PLUS_162p5KHz:   _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_162p5KHz) );  break;
            case E_AFC_ABOVE_PLUS_187p5KHz:_SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_187p5KHz) );   break;
#if (FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)
             case E_AFC_OUT_OF_AFCWIN :

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
        _SetTunerPLL(VHF_LOWMIN_PLL);
    }
    else
    {
        _SetTunerPLL(UHF_MAX_PLL);
    }

#if (TV_SCAN_PAL_SECAM_ONCE )//Sync SECAM-L and BG Base
    u16Record_BG_Sync_PLL_BASE = _u16TunerPLL;
    bNeedToRecord_BG_Sync_PLL = 0;
    //FRANCE_SUPPORT_DOUBLE_CHECK_L
    bDoubleCheckL = FALSE;
    bDoubleCheckL_State=DOUBLE_CHECK_L_STATE_FALSE;
#endif
    _bIsAFTNeeded = TRUE;

    msAPI_AVD_TurnOffAutoAV();
#if ENABLE_TTX
    msAPI_TTX_ResetAcquisition();
#endif

#if TV_SCAN_PAL_SECAM_ONCE
    msAPI_AUD_SetAudioStandard((AUDIOSTANDARD_TYPE)E_AUDIOSTANDARD_DK);
#else
    if (_bIsLSearch)
        msAPI_AUD_SetAudioStandard((AUDIOSTANDARD_TYPE)E_AUDIOSTANDARD_L);
    else
        msAPI_AUD_SetAudioStandard((AUDIOSTANDARD_TYPE)E_AUDIOSTANDARD_DK);
#endif

    msAPI_Tuner_SetIF();

    _u8TVScanStepDownCount = 0;
    _bIsSpeedUp = TRUE;

    msAPI_AVD_SetHsyncDetectionForTuning(TRUE);

#if AUTO_SCAN_TIME_PRINT
    u32StartAutoTuningTime = msAPI_Timer_GetTime0();
#endif
}



void _msAPI_Tuning_Start_SEARCHONETOUP_DOWN_PAL(void)
{
    U32 _eTempCurrentTuningState = _eCurrentTuningState;

#if (TV_FREQ_SHIFT_CLOCK)
    msAPI_Tuner_Patch_TVShiftClk(FALSE);
#endif

    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE,E_AUDIO_INTERNAL_2_MUTEON,E_AUDIOMUTESOURCE_ATV);

    msAPI_Timer_Delayms(DELAY_FOR_ENTERING_MUTE);

    if(_eTempCurrentTuningState == AFT_EXT_STEP_SEARCHONETOUP)
        eAutoSearchType = E_AUTO_SEARCH_TYPE_ONETOUP;
    else
        eAutoSearchType = E_AUTO_SEARCH_TYPE_ONETODOWN;

    if ( msAPI_AVD_IsAutoAVActive(E_AUTOAV_SOURCE_ALL) == TRUE )
    {
        msAPI_AVD_TurnOffAutoAV();
        msAPI_AVD_WaitForVideoSyncLock();
        msAPI_AVD_DetectVideoStandard(OPERATIONMETHOD_MANUALLY);
    }

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
            if(_eTempCurrentTuningState == AFT_EXT_STEP_SEARCHONETOUP)
                _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_4MHz) );
            else
                _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_4MHz) );
        }
        else
        {
        #if TV_SCAN_PAL_SECAM_ONCE
            if (_bIsLSearch)
            {
                if ( _CheckLPrimeBoundary() == TRUE )
                {
                    if(_eTempCurrentTuningState == AFT_EXT_STEP_SEARCHONETOUP)
                        _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_2p75MHz) );
                    else
                        _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_2p75MHz) );
                }
                else
                {
                    if(_eTempCurrentTuningState == AFT_EXT_STEP_SEARCHONETOUP)
                        _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_5p25MHz) );
                    else
                        _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_5p25MHz) );
                }
            }
            else
        #endif
            {
                if(_eTempCurrentTuningState == AFT_EXT_STEP_SEARCHONETOUP)
                    _SetTunerPLL( PLLSTEP(TUNER_PLL_NEXT_CHANNEL_JUMP) );
                else
                    _SetTunerPLL( PLLSTEP((TUNER_PLL_NEXT_CHANNEL_JUMP*(-1))) );
            }
        }
    #if TV_SCAN_PAL_SECAM_ONCE
        if (_bIsLSearch)
        {
            u16Record_BG_Sync_PLL_BASE=_u16TunerPLL;
            //FRANCE_SUPPORT_DOUBLE_CHECK_L
            bDoubleCheckL = FALSE;
            bDoubleCheckL_State=DOUBLE_CHECK_L_STATE_FALSE;
        }
    #endif
    }

    _bIsAFTNeeded = TRUE;
    msAPI_Tuner_SetIF();
    msAPI_AVD_SetHsyncDetectionForTuning(TRUE);
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

void _msAPI_Tuner_TuningProcessor(eAFTSTEP eState)
{
#if (FRONTEND_TUNER_TYPE == SILAB_2158_TUNER)
    S16 _u16TunerAFC;
#endif
#if ATVSCAN_USE_TIMER_DELAY
    static U_INT32 u32DetectAudioStart;
#endif
#if (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
    AVD_VideoStandardType eVideoStandType;
    static BOOLEAN  bIsAutoTune=TRUE;
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
            AUTO_TUNING_PRINT( printf("TUN_STATE: 0x%BX -> 0x%BX (%lu)\n",
                                      _ePreTuningState,
                                      _eCurrentTuningState,
                                      msAPI_Timer_DiffTimeFromNow(u32TuningStateTime)) );

            _ePreTuningState = _eCurrentTuningState;
            u32TuningStateTime = msAPI_Timer_GetTime0();
        }
    }

    {
        U8 u8locked;
        printf("\r\n VIF Lock=%x",(WORD)MDrv_VIF_Read_CR_LOCK_STATUS());
        printf(" FOE=%x",(WORD)MDrv_VIF_Read_CR_FOE());

        MDrv_AVD_SetRegValue(0x3504, 0x21);
        u8locked= MDrv_AVD_GetRegValue(0x3501)&BIT3;
        printf("\r\n VD lock=%x",(WORD)u8locked);
    }

    #endif
    switch ( _eCurrentTuningState )
    {
        case AFT_IDLE:
            if ( E_INPUT_SOURCE_ATV != msAPI_AVD_GetVideoSource()
                 || ( E_INPUT_SOURCE_ATV == msAPI_AVD_GetVideoSource()
                        && TRUE == msAPI_AVD_IsAutoAVActive(E_AUTOAV_SOURCE_ALL) )
                 || _bIsAFTNeeded == FALSE
                 || IS_RT_AFT_ENABLED == FALSE )
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
          #if (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
            bIsAutoTune=TRUE;
          #endif
            _msAPI_Tuning_Start_SEARCHALL_PAL();
          if((MApp_ATV_Scan_ScanState() == STATE_ATV_SCAN_INIT) &&
          (stGenSetting.stScanMenuSetting.u8ScanType == SCAN_TYPE_AUTO))
          {
              MApp_ZUI_API_InvalidateAllSuccessors(HWND_TUNE_SCAN_PROGRESS_ATV_FREQ);
          }
            _eCurrentTuningState = AFT_CHECKSYNC;
            break;

        case AFT_EXT_STEP_SEARCHONETOUP:
        case AFT_EXT_STEP_SEARCHONETODOWN:
          #if (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
            bIsAutoTune=FALSE;
          #endif
            _msAPI_Tuning_Start_SEARCHONETOUP_DOWN_PAL();
            _eCurrentTuningState = AFT_CHECKSYNC;
            break;

        case AFT_CHECKSYNC:
            u8NoSyncCount = 0;
            u16VdStatus = msAPI_AVD_CheckStatusLoop();

            if ( u16VdStatus & VD_CHECK_HSYNC_LOCKED )
            {
                u16PreviosTunerPLL = _u16TunerPLL;
                _eCurrentTuningState = AFT_TUNING;
                _u8TVScanStepDownCount = 3;
                //_u16TuningWaitTimer = WAIT_120ms; // <-<<<
                _bIsSpeedUp = FALSE;
            }
            else // No Lock
        case AFT_SIGNAL_WEAK:
        {
        #if TV_SCAN_PAL_SECAM_ONCE //AFT_SIGNAL_WEAK
            if (_bIsLSearch)
            {
                //printf("\r\nAudioStandard = %bd \n", msAPI_AUD_GetAudioStandard());
                if (E_AUDIOSTANDARD_DK == msAPI_AUD_GetAudioStandard())
                {
                    msAPI_AUD_SetAudioStandard(E_AUDIOSTANDARD_L);
                    _SetTunerPLL(u16Record_BG_Sync_PLL_BASE);//Sync SECAM-L and BG Base
                    msAPI_Tuner_SetIF();
                    _eCurrentTuningState = AFT_CHECKSYNC;
                    L_SEARCH_DBG(printf("\nchange L"));
                    return;
                }
                else
                {//For bouncing issue
                    if (_eCurrentTuningState==AFT_SIGNAL_WEAK)
                        {//Alread did AFT_TUNING
                            _u8TVScanStepDownCount = 0;
                        }
                }
            }
        #endif

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

        break;

        case AFT_JUMPNEAR:
          #if TV_SCAN_PAL_SECAM_ONCE
            //FRANCE_SUPPORT_DOUBLE_CHECK_L
            if (_bIsLSearch && bDoubleCheckL == FALSE)
            {
                if (E_AUDIOSTANDARD_L == msAPI_AUD_GetAudioStandard())
                {
                   MApi_AUDIO_SIF_SetStandard(E_AUDIOSTANDARD_DK);
                    L_SEARCH_DBG(printf("\nchange PAL"));
                    bNeedToRecord_BG_Sync_PLL=1;//Sync SECAM-L and BG Base
                    _u16TunerPLL=u16Record_BG_Sync_PLL_BASE;//Sync SECAM-L and BG Base;;Need to back to base value

                }
            }
          #endif

    case AFT_JUMPNEARHALF:
        if( _eCurrentTuningState == AFT_JUMPNEARHALF )
        {
          #if(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210)
            u16JumpDistance = TUNER_PLL_PLUS_0p25MHz;
          #else
            u16JumpDistance = TUNER_PLL_PLUS_0p5MHz;
          #endif
        }
        else
        {
          #if((FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF)||(FRONTEND_IF_DEMODE_TYPE == MSTAR_VIF_MSB1210||(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF)))
               #if(MS_BOARD_TYPE_SEL == BD_MSD309PX_HIS)
                   u16JumpDistance = TUNER_PLL_PLUS_0p75MHz;//TUNER_PLL_PLUS_1p5MHz;
               #else
                  u16JumpDistance = TUNER_PLL_PLUS_1MHz;//TUNER_PLL_PLUS_1p5MHz;
               #endif
          #else
            u16JumpDistance = TUNER_PLL_PLUS_1p5MHz;//TUNER_PLL_PLUS_1p5MHz;
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


    #if TV_SCAN_PAL_SECAM_ONCE//Sync SECAM-L and BG Base
        //FRANCE_SUPPORT_DOUBLE_CHECK_L
        if (_bIsLSearch)
        {
            if ( bDoubleCheckL && _u16TunerPLL > u16BGLockedPLL &&
                 _u16TunerPLL - u16BGLockedPLL >= TUNER_PLL_PLUS_0p5MHz )
            {
                bDoubleCheckL = FALSE;
                bDoubleCheckL_State=DOUBLE_CHECK_L_STATE_FALSE;
                _u16TunerPLL = u16BGLockedPLL;

                if ( _CheckLPrimeBoundary() == TRUE )
                {
                    _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_2p75MHz) );
                }
                else
                {
                    _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_5p25MHz) );
                }

                u16Record_BG_Sync_PLL_BASE = _u16TunerPLL;
            }
            else if (bNeedToRecord_BG_Sync_PLL)
            {
                u16Record_BG_Sync_PLL_BASE = _u16TunerPLL;
                bNeedToRecord_BG_Sync_PLL = 0;
            }
        }
    #endif

        msAPI_Tuner_SetIF();

        _eCurrentTuningState = AFT_CHECKSYNC;
        break;

    case AFT_TUNING:
        u16VdStatus = msAPI_AVD_CheckStatusLoop();
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
        AUTO_TUNING_PRINT(printf("Tuning: 0x%04X, 0x%02BX\n", u16VdStatus, eTuningStatus));

        if ( (eTuningStatus != E_TUNING_STATUS_OUT_OF_AFCWIN) &&
             (u16VdStatus & VD_CHECK_HSYNC_LOCKED) )
        {
            switch ( eTuningStatus )
            {
            case E_TUNING_STATUS_GOOD:
                if ( IS_SYSTEM_L_ENABLED == FALSE )
                {
                    if( msAPI_AVD_GetVerticalFreq() == E_VIDEO_FQ_50Hz )
                    {
                        if( E_AUDIOSTANDARD_M == MApi_AUDIO_SIF_ConvertToBasicAudioStandard(msAPI_AUD_GetAudioStandard()) )
                        {
                            msAPI_AUD_SetAudioStandard(E_AUDIOSTANDARD_DK);
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
#if(ENABLE_AUDIO_AUTO_DETECT)
                // for detect PAL MN
                MDrv_IFDM_BypassDBBAudioFilter(TRUE);
                MApi_AUDIO_SIF_StartAutoStandardDetection();

#if DEBUG_AUDIO_DETECT_TIME
                u32Start=msAPI_Timer_GetTime0();
                printf(">>> start0 %d", u32Start);
#endif


#if ATVSCAN_USE_TIMER_DELAY
                u32DetectAudioStart=msAPI_Timer_GetTime0();
#endif
#endif//(ENABLE_AUDIO_AUTO_DETECT)
#if 0
#if (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
                if(msAPI_ATV_GetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber()) == E_VIDEOSTANDARD_AUTO)
#endif
                msAPI_AVD_StartAutoStandardDetection();
#endif

            #if (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
                {
                    if(bIsAutoTune)
                    {
                        msAPI_AVD_StartAutoStandardDetection();
                    }
                    else
                    {
                        eVideoStandType=msAPI_ATV_GetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber());
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
                }
            #else
                msAPI_AVD_StartAutoStandardDetection();
            #endif



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
              #if ATVSCAN_USE_TIMER_DELAY
              #else
                _u16AFTIdleTimer = 0;
              #endif
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

            if ( (u8NoSyncCount++) == 20 )
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
#if (FRANCE_SUPPORT_SECAM_BG_SECAM_DK)
                if (eAudioType != E_AUDIOSTANDARD_L)
                {
                    msAPI_AUD_SetAudioStandard(E_AUDIOSTANDARD_DK);
                    bIsChanged = TRUE;
                }
#else
                if (eAudioType != E_AUDIOSTANDARD_L)
                {
                    msAPI_AUD_SetAudioStandard(E_AUDIOSTANDARD_L);
                    bIsChanged = TRUE;
                }
#endif
                L_SEARCH_DBG(printf("\nIt's SECAM\n"));
            }
            else
            {
                if (eAudioType != E_AUDIOSTANDARD_DK)
                {
                    msAPI_AUD_SetAudioStandard(E_AUDIOSTANDARD_DK);
                    bIsChanged = TRUE;
                }
                L_SEARCH_DBG(printf("\nIt's PAL\n"));
            }
            if (bIsChanged)
            {
                msAPI_Tuner_SetIF();
                MApi_AUDIO_SIF_StartAutoStandardDetection();

#if DEBUG_AUDIO_DETECT_TIME
                u32Start=msAPI_Timer_GetTime0();
                printf(">>> start1 %d", u32Start);
#endif
                msAPI_AVD_StartAutoStandardDetection();
#if ENABLE_TTX
                msAPI_TTX_ResetAcquisition();
#endif
            }

        }
    #if ATVSCAN_USE_TIMER_DELAY
    #else
        _u16AFTIdleTimer = 0;
    #endif
        _eCurrentTuningState = AFT_DETECTVIDEO; // AFT_SHOWTIME1;

        return; // <-<<<
#endif

    case AFT_DETECTVIDEO:
        if ( MDrv_AVD_GetStatus() & VD_CHECK_STATUS_RDY )
        {

        #if 0
        #if (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
            if(msAPI_ATV_GetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber()) == E_VIDEOSTANDARD_AUTO)
        #endif
                msAPI_AVD_GetResultOfAutoStandardDetection();
        #endif

        #if (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
            if (bIsAutoTune)
            {
                msAPI_AVD_GetResultOfAutoStandardDetection();
            }
            else
            {
                eVideoStandType = msAPI_ATV_GetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber());
                if(eVideoStandType == E_VIDEOSTANDARD_AUTO)
                {
                    msAPI_AVD_GetResultOfAutoStandardDetection();
                }
                else if (eVideoStandType == E_VIDEOSTANDARD_PAL_BGHI)
                {
                    eVideoStandType=msAPI_AVD_GetStandardDetection();
                    if(eVideoStandType != E_VIDEOSTANDARD_PAL_BGHI &&
                       eVideoStandType != E_VIDEOSTANDARD_PAL_M &&
                       eVideoStandType != E_VIDEOSTANDARD_PAL_N &&
                       eVideoStandType != E_VIDEOSTANDARD_PAL_60)
                    {
                        msAPI_AVD_SetVideoStandard(E_VIDEOSTANDARD_PAL_BGHI);
                    }
                    else
                    {
                        msAPI_AVD_SetVideoStandard(eVideoStandType);
                    }

                    //msAPI_VD_DisableForceMode();
                    msAPI_AVD_StartAutoStandardDetection();
                }
                else if(eVideoStandType == E_VIDEOSTANDARD_NTSC_M)
                {
                    eVideoStandType=msAPI_AVD_GetStandardDetection();
                    if(eVideoStandType != E_VIDEOSTANDARD_NTSC_M &&
                       eVideoStandType != E_VIDEOSTANDARD_NTSC_44)
                    {
                        msAPI_AVD_SetVideoStandard(E_VIDEOSTANDARD_NTSC_M);
                    }
                    else
                    {
                        msAPI_AVD_SetVideoStandard(eVideoStandType);
                    }
                    //msAPI_VD_DisableForceMode();
                    msAPI_AVD_StartAutoStandardDetection();
                }
            }
        #else
            msAPI_AVD_GetResultOfAutoStandardDetection();
        #endif

        #if ATVSCAN_USE_TIMER_DELAY
        #else
            _u16AFTIdleTimer = 0;
        #endif

            _eCurrentTuningState = AFT_SHOWTIME2;
            _bIsPreProgramDetected = TRUE;
        }
        break;

    case AFT_SHOWTIME2:
    #if(ENABLE_AUDIO_AUTO_DETECT)
      #if ATVSCAN_USE_TIMER_DELAY
        if((msAPI_Timer_DiffTime(u32DetectAudioStart, msAPI_Timer_GetTime0()))>ATVSCAN_AUDIO_WAIT_TIME2)
      #else
        _u16AFTIdleTimer++;
        if ( _u16AFTIdleTimer >= ATVSCAN_AUDIO_WAIT_TIME)
      #endif
    #endif//(ENABLE_AUDIO_AUTO_DETECT)

        {
        #if (VD_SYNC_CRITERION_CONFIG_ENABLE)
            if ( msAPI_Tuner_VD_IsSyncLocked(SYNC_LOCKED_BASE_NUM,SYNC_LOCKED_PASS_NUM) == TRUE )
        #else
            if ( msAPI_AVD_IsSyncLocked())
        #endif
            {
            #if(ENABLE_AUDIO_AUTO_DETECT)
                _eCurrentTuningState = AFT_DETECTAUDIO;
            #else
                _eCurrentTuningState = AFT_MEMORIZEPRDATA;
            #endif//(ENABLE_AUDIO_AUTO_DETECT)
            }
            else
            {
                debugTuningPrint("-Unlocked Sync: %dMHz", msAPI_CFT_ConvertPLLtoIntegerOfFrequency(_u16TunerPLL));//, msAPI_CFT_ConvertPLLtoFractionOfFrequency(_u16TunerPLL));

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
        }
        _bIsOneProgramDetected = FALSE;
        break;

    case AFT_DETECTAUDIO:
      #if DEBUG_AUDIO_DETECT_TIME
        u32Get=msAPI_Timer_GetTime0();

        printf("\n >>> Get0 %d",u32Get );
        if((msAPI_Timer_DiffTime(u32Start, u32Get))< (U32)g_u8WaitAudioTime*100)
            break;
      #endif

        msAPI_AUD_GetResultOfAutoStandardDetection();

        // for detect PAL MN
        MDrv_IFDM_BypassDBBAudioFilter(FALSE);
    #if (TV_SCAN_PAL_SECAM_ONCE)//FRANCE_SUPPORT_DOUBLE_CHECK_L
        if ( _bIsLSearch && bDoubleCheckL && msAPI_AUD_GetAudioStandard() != E_AUDIOSTANDARD_L )
        {
            bDoubleCheckL = FALSE;
            bDoubleCheckL_State=DOUBLE_CHECK_L_STATE_FALSE;
            if ( _CheckLPrimeBoundary() == TRUE )
            {
                _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_2p75MHz) );
            }
            else
            {
                _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_5p25MHz) );
            }

            u16Record_BG_Sync_PLL_BASE = _u16TunerPLL;
            msAPI_AUD_SetAudioStandard((AUDIOSTANDARD_TYPE)E_AUDIOSTANDARD_DK);
            msAPI_Tuner_SetIF();

            _eCurrentTuningState = AFT_CHECKSYNC;
        }
        else
        {

            if(msAPI_AUD_IsAudioDetected() == FALSE)
            {
                u16Record_FALSE_SIGNAL_TunerPLL = _u16TunerPLL;
                u16JumpDistance = TUNER_PLL_PLUS_0p5MHz;
                if ( eAutoSearchType == E_AUTO_SEARCH_TYPE_ALLWAYDOWN ||
                eAutoSearchType == E_AUTO_SEARCH_TYPE_ONETODOWN )
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
            _eCurrentTuningState = AFT_MEMORIZEPRDATA;
        }
    #else // FRANCE_SUPPORT_SECAM_BG_SECAM_DK && FRANCE_SUPPORT_DOUBLE_CHECK_L
        _eCurrentTuningState = AFT_CHECK_FALSESIGNAL;
    #endif // FRANCE_SUPPORT_SECAM_BG_SECAM_DK && FRANCE_SUPPORT_DOUBLE_CHECK_L
        break;

    case AFT_CHECK_FALSESIGNAL:
      #if(TV_SCAN_PAL_SECAM_ONCE)
        u16VdStatus = msAPI_AVD_CheckStatusLoop();

        if( u16VdStatus & VD_CHECK_HSYNC_LOCKED)
        {
            _u16TunerPLL = u16Record_FALSE_SIGNAL_TunerPLL;
            _eCurrentTuningState = AFT_MEMORIZEPRDATA;

        }
        else
        {
            printf("\r\n Abandon FALSE SIGNAL");
            u16JumpDistance = TUNER_PLL_PLUS_1MHz;
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

        }
      #else
        {
            AVD_VideoStandardType eStandard = msAPI_AVD_GetResultOfAutoStandardDetection();
            AUDIOSTANDARD_TYPE eAudioType = msAPI_AUD_GetAudioStandard();
            if (eAudioType == E_AUDIOSTANDARD_L && eStandard != E_VIDEOSTANDARD_SECAM)
            {
                MS_DEBUG_MSG(printf("\r\n PAL-L, no need save"));
            if ( eAutoSearchType == E_AUTO_SEARCH_TYPE_ALLWAYDOWN ||
                 eAutoSearchType == E_AUTO_SEARCH_TYPE_ONETODOWN )
                    _u16TunerPLL -= TUNER_PLL_PLUS_2MHz; // need to fine-tune
                else
                    _u16TunerPLL += TUNER_PLL_PLUS_2MHz; // need to fine-tune

                _SetTunerPLL(_u16TunerPLL);
                _eCurrentTuningState = AFT_SIGNAL_WEAK;
            }
            else
                _eCurrentTuningState = AFT_MEMORIZEPRDATA;
        }
      #endif
        break;

    case AFT_MEMORIZECHDATA:
        break;

    case AFT_MEMORIZEPRDATA:
        switch ( eAutoSearchType )
        {
        case E_AUTO_SEARCH_TYPE_ALLWAYUP:
        case E_AUTO_SEARCH_TYPE_ALLWAYDOWN:

          #if (TV_SCAN_PAL_SECAM_ONCE /*&& FRANCE_KILL_NON_SECAM_L*/)//&& FRANCE_SUPPORT_DOUBLE_CHECK_L
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

        #if(ENABLE_AUDIO_AUTO_DETECT)
            msAPI_ATV_SetAudioMode(E_AUDIOSOURCE_ATV, (AUDIOMODE_TYPE)MApi_AUDIO_SIF_GetSoundMode());
        #else
            msAPI_ATV_SetAudioMode(E_AUDIOSOURCE_ATV, E_AUDIOMODE_MONO);
        #endif//(ENABLE_AUDIO_AUTO_DETECT)

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

        #if 0
        #if (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
            msAPI_ATV_SetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber(), msAPI_ATV_GetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber()));
        #endif
            msAPI_ATV_SetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber(), msAPI_AVD_GetVideoStandard());
        #endif

      #if 0
        #if (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
            {
                VIDEOSTANDARD_TYPE eVideoStandType;
                eVideoStandType=msAPI_ATV_GetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber());
                if(eVideoStandType != E_VIDEOSTANDARD_PAL_BGHI && eVideoStandType != E_VIDEOSTANDARD_NTSC_M)
                {
                    printf("## video standard=%bx, set to AUTO !!\n",eVideoStandType);
                    msAPI_ATV_SetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber(),E_VIDEOSTANDARD_AUTO);
                }
                else
                {
                    msAPI_ATV_SetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber(),eVideoStandType);
                }
            }
        #else
            msAPI_ATV_SetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber(), msAPI_AVD_GetVideoStandard());
        #endif
      #else
            msAPI_ATV_SetVideoStandardOfProgram(msAPI_ATV_GetCurrentProgramNumber(), msAPI_AVD_GetVideoStandard());
      #endif

            msAPI_AVD_WaitForVideoSyncLock();

        #if ENABLE_TTX
            if ( TRUE != msAPI_TTX_GetStationNameFromTeletext(_sCurrentStationName, MAX_STATION_NAME, &u8SortingPriority) )
        #endif
            {
            //printf("_u8ChannelNumber~~~~~~~~=%d\n",_u8ChannelNumber);
                msAPI_Tuner_ConvertMediumAndChannelNumberToString(_eMedium, _u8ChannelNumber, _sCurrentStationName);
                u8SortingPriority = LOWEST_SORTING_PRIORITY;
            }

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
            break;

        case E_AUTO_SEARCH_TYPE_ONETOUP:
        case E_AUTO_SEARCH_TYPE_ONETODOWN:
            msAPI_Tuner_UpdateMediumAndChannelNumber();
            _DetectStationName();

            _eCurrentTuningState = AFT_COMPLETE;
            {
                MS_U32 u32Index = 0;
                MS_BOOL bProgramExist = FALSE;
                for(;u32Index < msAPI_ATV_GetActiveProgramCount(); u32Index++)
                {
                    if(_u16TunerPLL == msAPI_ATV_GetProgramPLLData(u32Index))
                    {
                        bProgramExist = TRUE;
                        msAPI_ATV_SetCurrentProgramNumber(u32Index);
                    }
                }

                if(bProgramExist)
                    break;

            }
            msAPI_ATV_SetCurrentProgramNumber(msAPI_ATV_GetActiveProgramCount());
            msAPI_ATV_SetProgramPLLData(msAPI_ATV_GetCurrentProgramNumber(), _u16TunerPLL);
            msAPI_ATV_SetAudioStandard(msAPI_ATV_GetCurrentProgramNumber(), msAPI_AUD_GetAudioStandard());
#if(ENABLE_AUDIO_AUTO_DETECT)
            msAPI_ATV_SetAudioMode(E_AUDIOSOURCE_ATV, (AUDIOMODE_TYPE)MApi_AUDIO_SIF_GetSoundMode());
#else
            msAPI_ATV_SetAudioMode(E_AUDIOSOURCE_ATV, E_AUDIOMODE_MONO);
#endif//(ENABLE_AUDIO_AUTO_DETECT)

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
            msAPI_ATV_SetMediumAndChannelNumber(msAPI_ATV_GetCurrentProgramNumber(), _eMedium, _u8ChannelNumber);

        #if ENABLE_AUTOTEST
            if(g_bAutobuildDebug)
            {
                printf("31_ATV_Manual_Tuning\n");
            }
        #endif
            break;

        default:
            break;
        }

    #if (TV_SCAN_PAL_SECAM_ONCE /*&& FRANCE_KILL_NON_SECAM_L*/)//FRANCE_SUPPORT_DOUBLE_CHECK_L
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
            #if TV_SCAN_PAL_SECAM_ONCE
                //FRANCE_SUPPORT_DOUBLE_CHECK_L
                if ( _bIsLSearch && bDoubleCheckL == FALSE &&
                     msAPI_AUD_GetAudioStandard() != E_AUDIOSTANDARD_L )
                {
                    bDoubleCheckL = TRUE;
                    bDoubleCheckL_State=DOUBLE_CHECK_L_STATE_FOUND_BG;
                    u16BGLockedPLL = _u16TunerPLL;
                    _SetTunerPLL( PLLSTEP(TUNER_PLL_MINUS_0p5MHz) );
                }
                else
                {
                    bDoubleCheckL = FALSE;
                    bDoubleCheckL_State=DOUBLE_CHECK_L_STATE_FALSE;

                    if ( _CheckLPrimeBoundary() == TRUE )
                    {
                        _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_2p75MHz) );
                    }
                    else
                    {
                        _SetTunerPLL( PLLSTEP(TUNER_PLL_NEXT_CHANNEL_JUMP) );
                    }

                    u16Record_BG_Sync_PLL_BASE = _u16TunerPLL;
                }
            #else
                if ( _IsLPrime() == TRUE )
                {
                    _SetTunerPLL( PLLSTEP(TUNER_PLL_PLUS_2p75MHz) );
                }
                else
                {
                    _SetTunerPLL( PLLSTEP(TUNER_PLL_NEXT_CHANNEL_JUMP) );
                }
            #endif
                _eCurrentTuningState = AFT_CHECKSYNC;
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

    #if TV_SCAN_PAL_SECAM_ONCE
        //FRANCE_SUPPORT_DOUBLE_CHECK_L
        if (bDoubleCheckL)
            msAPI_AUD_SetAudioStandard((AUDIOSTANDARD_TYPE)E_AUDIOSTANDARD_L);
        else
            msAPI_AUD_SetAudioStandard((AUDIOSTANDARD_TYPE)E_AUDIOSTANDARD_DK);
    #endif
        msAPI_Tuner_SetIF();
        break;

    case AFT_COMPLETE:
      #if AUTO_SCAN_TIME_PRINT
        MS_DEBUG_MSG(printf("\nTotal Auto Tuning Time: %lu\n", msAPI_Timer_DiffTimeFromNow(u32StartAutoTuningTime)));
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
            msAPI_AUD_SetAudioStandard((AUDIOSTANDARD_TYPE)E_AUDIOSTANDARD_BG);
            if (_bIsLSearch)
            {
                u16Record_BG_Sync_PLL_BASE=_u16TunerPLL;
            }
        #endif

            msAPI_Tuner_SetIF();
            _eCurrentTuningState = AFT_CHECKSYNC;
        }
        break;

    case E_AUTO_SEARCH_TYPE_ONETODOWN:
        if ( _u16TunerPLL <= VHF_LOWMIN_PLL )
        {
            _SetTunerPLL(UHF_MAX_PLL);

        #if TV_SCAN_PAL_SECAM_ONCE
            msAPI_AUD_SetAudioStandard((AUDIOSTANDARD_TYPE)E_AUDIOSTANDARD_BG);
            if (_bIsLSearch)
            {
                u16Record_BG_Sync_PLL_BASE=_u16TunerPLL;
            }
        #endif

            msAPI_Tuner_SetIF();
            _eCurrentTuningState = AFT_CHECKSYNC;
        }
        break;

    default:
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


