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
// (MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////


#define MSAPI_SCAN_ATAC_C


#include <string.h>
#include <stdio.h>
#include "Board.h"
#include "datatype.h"
#include "msAPI_Global.h"
#include "msAPI_Tuner_ATSC.h"
#include "RF_Tuner_ATSC.h"
#include "msAPI_Scan_ATSC.h"
#include "msAPI_Timer.h"
#include "msAPI_VD.h"
#if(FRONTEND_IF_DEMODE_TYPE == MSTAR_INTERN_VIF)
#include "IF_Demodulator.h"
#endif
#include "drvGPIO.h"
#include "drvGlobal.h"

#include "MApp_GlobalVar.h"


#define DEMOD_FSYNC_TIMEOUT     1200
#define DEMOD_PRELOCK_TIMEOUT   330

#define DEBUG_ATSC_SCAN_FLOW(x) //x

#define LIB_SCAN_API_DBG(x)     //x


#define DEMOD_RESET_DELAY  10
#define DEMOD_FIRST_CHECK_LOCK_DELAY 20
#if (NEW_DEMOD_SCAN)
#define DEMOD_FIRST_CHECK_LOCK_PERIOD 330 //1500//1000//330
#define DEMOD_FIRST_QAM_CHECK_LOCK_PERIOD 1500 //1500//1000//330

extern MS_U8 u8RetQamNoChannelDetect;
#else
#define DEMOD_FIRST_CHECK_LOCK_PERIOD 330
#endif

static EN_NTSC_SCAN_STATE  enNTSCScanState;
static EN_VSB_SCAN_STATE   enVSBScanState;
static EN_QAM_SCAN_STATE   enQAMScanState;
static U32 Check_demod_fsyc_time;
static U32 Check_demod_QamPre_lock_time;

// VSB Setting
#define VSB_FREQ_OFFSET_MAX_COUNT 1

S16 VSB_FREQ_OFFSET_TABLE[VSB_FREQ_OFFSET_MAX_COUNT]={0};        //Unit: KHz

// QAM Setting
#define QAM_FREQ_OFFSET_MAX_COUNT 1
S16 QAM_FREQ_OFFSET_TABLE[QAM_FREQ_OFFSET_MAX_COUNT]={0};        //Unit: KHz

void msAPI_IFDM_SetVIF_Notch(void)
{
    return;
}

void msAPI_SCAN_Init(void)
{
    enNTSCScanState = STATE_NTSC_SCAN_INIT;
    enVSBScanState = STATE_VSB_SCAN_INIT;
    enQAMScanState = STATE_QAM_SCAN_INIT;
    msAPI_DemodState_INIT_ATSC();
    bInitDemod = FALSE;
}

BOOLEAN msAPI_NTSC_Scan_CheckVDStatus_Loop(U16 u16WaitVdStableTime)
{
    U32 u32StartTime = msAPI_Timer_GetTime0();

#if(CHAKRA3_AUTO_TEST)
    U16 u16CurVdStatus = 0;
    AVD_VideoStandardType eCurVdStd;
#endif

    do
    {
    #if (FRONTEND_IF_DEMODE_TYPE  == MSTAR_INTERN_VIF)
        MDrv_VIF_Handler(TRUE);
    #endif

        if ( msAPI_AVD_CheckStatusLoop() & VD_HSYNC_LOCKED )
        {
        #if(CHAKRA3_AUTO_TEST)
            // This is a patch for auto test:
            // Because autotest use NO.2 line to test ATSC, it's not a good envirement for ATSC
            // Solution: Only scan NTSC signal.
            u16WaitVdStableTime = 500;

            AFC eFreqDev = MDrv_IFDM_GetFreqDev();
            //printf("VIF: AFCWIN = 0x%X\n", eFreqDev);
            if( eFreqDev == E_AFC_OUT_OF_AFCWIN )
            {
                printf("Out AFC Win\n");
            }

            u16CurVdStatus = 0;
            eCurVdStd = MDrv_AVD_GetStandardDetection(&u16CurVdStatus);
            printf("VD Status=0x%X, Std=%u, use %u\n", u16CurVdStatus, eCurVdStd, msAPI_Timer_DiffTime_2(u32StartTime, msAPI_Timer_GetTime0()));
            if( (E_VIDEOSTANDARD_NTSC_M == eCurVdStd)
              &&((u16CurVdStatus&VD_VSYNC_50HZ) == 0 )
              )
            {
                printf("VD NTSC Lock\n" );
                return TRUE;
            }
        #else
            // Only check H Sync lock
            printf("VD H Lock\n" );
            return TRUE;
        #endif
        }
    }
    while( msAPI_Timer_DiffTime_2(u32StartTime, msAPI_Timer_GetTime0()) < u16WaitVdStableTime );

#if(CHAKRA3_AUTO_TEST)
    u16CurVdStatus = 0;
    eCurVdStd = MDrv_AVD_GetStandardDetection(&u16CurVdStatus);
    printf("VD Status=0x%X, Std=%u, use %u\n", u16CurVdStatus, eCurVdStd, msAPI_Timer_DiffTime_2(u32StartTime, msAPI_Timer_GetTime0()));
#endif

    return FALSE;
}

EN_SCAN_RESULT msAPI_NTSC_Scan(MS_TP_SETTING_ATSC *pstTPSetting, U8 CurRFCh, EN_SCAN_ANT_TYPE CurChType)
{
    static U8 u8Freq_Offset_Count;
    static U16 u16Init_Freq;
    S16 s16FinalFreqOffset;

    switch(enNTSCScanState)
    {
        case STATE_NTSC_SCAN_INIT:
            LIB_SCAN_API_DBG( printf("[STATE_NTSC_SCAN_INIT]at %u\n", MsOS_GetSystemTime()); );
            u16Init_Freq = pstTPSetting->u16Frequency;
            pstTPSetting->fModulation=DEMOD_ATSC_MODE_NTSC;
            u8Freq_Offset_Count = 0;
            //enNTSCScanState = STATE_NTSC_JUMP;
            if (((CurRFCh == 5) || (CurRFCh == 6)) && (SCAN_ANT_CATV == CurChType))  //from -1.8Mhz ~ +2.3Mhz
                pstTPSetting->u16Frequency = (NTSC_CH5CH6_OFFSET_TABLE[u8Freq_Offset_Count]);
            else    //from -1.8Mhz ~ +1.8Mhz
                pstTPSetting->u16Frequency = (NTSC_AUTO_FREQ_OFFSET_TABLE[u8Freq_Offset_Count]);
            pstTPSetting->u16Frequency += u16Init_Freq;
            LIB_SCAN_API_DBG(printf("In NTSC Scan Init Freq/FREQ_STEP= %ld\n", (U32) (pstTPSetting->u16Frequency)););
            //LIB_SCAN_API_DBG(printf("In NTSC Scan Init Freq= %ld\n", (U32) ((U32)(pstTPSetting->u16Frequency)*FREQ_STEP)););
            msAPI_Tuner_SetFreq(pstTPSetting->u16Frequency, (EN_DEMOD_ATSC_MODE)pstTPSetting->fModulation);

            //msAPI_Tuner_Wait(TUNER_PLL_STABLE_TIME);

        #if (FRONTEND_IF_DEMODE_TYPE  == MSTAR_INTERN_VIF) // BY 20090715
            // ATV mode
            msAPI_AVD_SetVideoSource( E_INPUT_SOURCE_ATV );  // vd mcu code should be loaded before vif initial
            EXT_RF_AGC_ON();
             //printf("KKK: (Temp)EXT_RF_AGC_On...for ATV\n");
            MDrv_IFDM_Init();
            MDrv_IFDM_SetIF(IF_FREQ_MN);
            MDrv_IFDM_SetVifIfFreq(TUNER_IF_FREQ_KHz);
            msAPI_IFDM_SetVIF_Notch();

            msAPI_Tuner_Wait(TUNER_PLL_STABLE_TIME);

          #if 1 // Use new method
            if( msAPI_NTSC_Scan_CheckVDStatus_Loop(VD_STABLE_TIME) )
            {
                //enNTSCScanState = STATE_NTSC_SCAN_INIT;
                msAPI_AVD_SetHsyncDetectionForTuning(FALSE);
                return LOCK;
            }
          #else
            {
                U32 u32StartTime = msAPI_Timer_GetTime0();
                while( msAPI_Timer_DiffTime_2(u32StartTime, msAPI_Timer_GetTime0()) < VD_STABLE_TIME )
                {
                    MDrv_VIF_Handler(TRUE);
                    if ( msAPI_AVD_CheckStatusLoop() & VD_HSYNC_LOCKED )
                    {
                        LIB_SCAN_API_DBG(printf("VD lock time0 %d\r\n",msAPI_Timer_GetTime0()-u32StartTime););
                        enNTSCScanState = STATE_NTSC_SCAN_INIT;
                        msAPI_AVD_SetHsyncDetectionForTuning(FALSE);
                        return LOCK;
                    }
                }
            }
          #endif

            //msAPI_Tuner_Wait(TUNER_PLL_STABLE_TIME*2); // remove for faster NTSC scan.
        #else
            msAPI_Timer_Delayms(TUNER_PLL_STABLE_TIME);     //wait for PLL stable
        #endif

            enNTSCScanState = STATE_NTSC_CHECK_LOCK;
            break;

        case STATE_NTSC_JUMP:
            LIB_SCAN_API_DBG( printf("[STATE_NTSC_JUMP] at %u\n", MsOS_GetSystemTime()); );
            if (((CurRFCh == 5) || (CurRFCh == 6)) && (SCAN_ANT_CATV == CurChType))  //from -1.8Mhz ~ +2.3Mhz
                pstTPSetting->u16Frequency = (NTSC_CH5CH6_OFFSET_TABLE[u8Freq_Offset_Count]);
            else    //from -1.8Mhz ~ +1.8Mhz
                pstTPSetting->u16Frequency = (NTSC_AUTO_FREQ_OFFSET_TABLE[u8Freq_Offset_Count]);
            pstTPSetting->u16Frequency += u16Init_Freq;

            LIB_SCAN_API_DBG(printf("In NTSC Scan Init Freq/FREQ_STEP = %u\n", (U32) (pstTPSetting->u16Frequency)););
            //LIB_SCAN_API_DBG(printf("In NTSC Scan Init Freq= %ld\n", (U32) ((U32)(pstTPSetting->u16Frequency)*FREQ_STEP)););

            msAPI_Tuner_SetFreq(pstTPSetting->u16Frequency, (EN_DEMOD_ATSC_MODE)pstTPSetting->fModulation);

            msAPI_Tuner_Wait(TUNER_PLL_STABLE_TIME);
            enNTSCScanState = STATE_NTSC_CHECK_LOCK;
            break;

        case STATE_NTSC_CHECK_LOCK:
            LIB_SCAN_API_DBG( printf("[STATE_NTSC_CHECK_LOCK] at %u\n", MsOS_GetSystemTime()); );

          #if 1
            if( msAPI_NTSC_Scan_CheckVDStatus_Loop(10) )
          #else
            if( msAPI_AVD_CheckStatusLoop() & VD_HSYNC_LOCKED )
          #endif
            {
                if (TRUE == msAPI_NTSC_GetFreq_Offset(pstTPSetting))
                {
                    s16FinalFreqOffset = (pstTPSetting->u16Frequency) - u16Init_Freq;
                    if ((s16FinalFreqOffset >= FREQ_OFFSET_RANGE_LEFT) && (s16FinalFreqOffset <= FREQ_OFFSET_RANGE_Ch5Ch6_RIGHT))
                    {
                        if ((s16FinalFreqOffset <= FREQ_OFFSET_RANGE_RIGHT) || ((CurRFCh == 5) || (CurRFCh == 6)))
                        {
                           LIB_SCAN_API_DBG(printf("SUCCESS!Final Freq/FREQ_STEP= %ld\n", (U32)(pstTPSetting->u16Frequency)););
                           //LIB_SCAN_API_DBG(printf("SUCCESS!Final Freq= %ld\n", (U32)(pstTPSetting->u16Frequency)*FREQ_STEP););
                            enNTSCScanState = STATE_NTSC_SCAN_INIT;
                           msAPI_AVD_SetHsyncDetectionForTuning(FALSE);
                            return LOCK;
                        }
                    }
                    LIB_SCAN_API_DBG(printf("Fail, VD_HSYNC_LOCK, But frequency out of spec.\n"););
                }
                else
                {
                    LIB_SCAN_API_DBG(printf("ERROR !VD_HSYNC_LOCK, Get Exact Freq Fail!\n"););
                }
            }
            else
            {
                LIB_SCAN_API_DBG(printf("VD UnLock !VD_HSYNC_GET Fail\n"););
            }
            u8Freq_Offset_Count++;
            if(u8Freq_Offset_Count >= NTSC_FREQ_OFFSET_MAX_COUNT)
            {
                pstTPSetting->u16Frequency = u16Init_Freq;
                enNTSCScanState = STATE_NTSC_SCAN_INIT;
                return UNLOCK;
            }
            enNTSCScanState = STATE_NTSC_JUMP;
            break;

         default:
            break;
        }
        return CHECKING;
}

EN_SCAN_RESULT msAPI_VSB_Scan(MS_TP_SETTING_ATSC *pstTPSetting)
{
    static U8 u8Freq_Offset_Count;
    static U16 u16Init_Freq;
    EN_SCAN_RESULT Result;
    static BOOLEAN bPilotLockCheck = 0;

    Result = CHECKING;

    switch(enVSBScanState)
    {
        case STATE_VSB_SCAN_INIT:
            DEBUG_ATSC_SCAN_FLOW(printf("case STATE_VSB_SCAN_INIT:\n"););

            #if (FRONTEND_DEMOD_ATSC_TYPE == EMBEDDED_ATSC_DEMOD)
            EXT_RF_AGC_OFF();
            #endif
            u16Init_Freq = pstTPSetting->u16Frequency;
            pstTPSetting->fModulation = DEMOD_ATSC_MODE_8VSB;
            u8Freq_Offset_Count = 0;
            enVSBScanState = STATE_VSB_INIT_DEMODE;
            pstTPSetting->u16Frequency = u16Init_Freq + VSB_FREQ_OFFSET_TABLE[u8Freq_Offset_Count];
            msAPI_Tuner_Initialization_ATSC(1);
            bPilotLockCheck = 0;

            //Set Tuner
            msAPI_Tuner_SetFreq(pstTPSetting->u16Frequency, (EN_DEMOD_ATSC_MODE)pstTPSetting->fModulation);
            msAPI_Demodulator_Reset_ATSC();
            msAPI_Timer_Delayms(DEMOD_RESET_DELAY);
            if (msAPI_Demodulator_Init((EN_DEMOD_ATSC_MODE)pstTPSetting->fModulation, (EN_DEMOD_ATSC_SPECTRUM_MODE)pstTPSetting->fSpectrum) == FALSE)
            {
                enVSBScanState = STATE_VSB_SCAN_INIT;
                LIB_SCAN_API_DBG(printf("Error!!! MApp_VSB_Scan Demod init Fail \n"););
                Result = UNLOCK;
            }
            Check_demod_fsyc_time = msAPI_Timer_GetTime0();  //Max 0521 sync check lock flow
            enVSBScanState=STATE_VSB_CHECK_FSYNC_LOCK;
            break;

        case STATE_VSB_INIT_DEMODE:
            DEBUG_ATSC_SCAN_FLOW(printf("case STATE_VSB_INIT_DEMODE:\n"););
            pstTPSetting->u16Frequency = u16Init_Freq + VSB_FREQ_OFFSET_TABLE[u8Freq_Offset_Count];
            msAPI_Demodulator_Reset_ATSC();
            //Set Tuner
            msAPI_Tuner_SetFreq(pstTPSetting->u16Frequency, (EN_DEMOD_ATSC_MODE)pstTPSetting->fModulation);
            msAPI_Timer_Delayms(VSB_TUNER_PLL_STABLE_TIME);     //wait for PLL stable
            if (msAPI_Demodulator_Init((EN_DEMOD_ATSC_MODE)pstTPSetting->fModulation, (EN_DEMOD_ATSC_SPECTRUM_MODE)pstTPSetting->fSpectrum) == FALSE)
            {
                enVSBScanState = STATE_VSB_SCAN_INIT;
                LIB_SCAN_API_DBG(printf("Error!!! MApp_VSB_Scan Demod init Fail \n"););
                Result = UNLOCK;
            }
            msAPI_Timer_Delayms(VSB_DEMOD_STABLE_TIME);
            enVSBScanState=STATE_VSB_CHECK_LOCK;
            break;


        case STATE_VSB_CHECK_FSYNC_LOCK:
                {
                    if(msAPI_Timer_DiffTimeFromNow(Check_demod_fsyc_time) > 20)
                    {
                        if(msAPI_VSB_Check_FsyncLock())
                        {
                            Result = LOCK;
                        }
                        else
                        {
                            if((msAPI_Timer_DiffTimeFromNow(Check_demod_fsyc_time) > DEMOD_FSYNC_TIMEOUT))
                            {
                                Result = UNLOCK;
                            }
                            else
                            {
                                if(bPilotLockCheck == 0)
                                {
                                    if((msAPI_Timer_DiffTimeFromNow(Check_demod_fsyc_time) > DEMOD_PRELOCK_TIMEOUT))
                                    {
                                        printf("Pilot lock timeout ....unlock\n");
                                        Result = UNLOCK;
                                    }
                                    else
                                    {
                                        //Check pilot lock for empty RF
#if (NEW_DEMOD_SCAN)
                                        if(u8RetQamNoChannelDetect == 1)
                                        {
#endif
                                        if(msAPI_VSB_Check_PreLock())
                                        {
                                            Result = CHECKING; // Pilot lock --> Check Fsync lock
                                            printf("Pilot lock --> need to check Fsync lock\n");
                                            bPilotLockCheck=1;// Pilot lock once--> no need to check Pilot lock anymore
                                        }
#if (NEW_DEMOD_SCAN)
                                        }
                                        else if(u8RetQamNoChannelDetect == 2)
                                        {
                                            Result = UNLOCK;
                                            return Result;
                                        }
                                        else  //u8RetQamNoChannelDetect==0
                                        {    Check_demod_fsyc_time = msAPI_Timer_GetTime0();
                                             Result = CHECKING;
                                        }
#else
                                        else
#endif
                                        {
                                            Result = CHECKING; //Pilot unlock --> Checking during timing
                                        }
                                    }
                                }
                            }
                        }
                        ///LIB_SCAN_API_DBG(printf("msAPI_VSB_Check_FsyncLock=%d \n", (U8) Result););
                    }



                }

           break;

        case STATE_VSB_CHECK_LOCK:
            DEBUG_ATSC_SCAN_FLOW(printf("case STATE_VSB_CHECK_LOCK:\n"););
            //Check Lock Loop
            Result = msAPI_VSB_Check_Lock();
            LIB_SCAN_API_DBG(printf("MApp_VSB_Scan Demod Check Lock=%d \n", (U8) Result););
            if (Result == LOCK)
            {
                enVSBScanState = STATE_VSB_SCAN_INIT;
            }
            else if ( Result == UNLOCK)
            {
                u8Freq_Offset_Count++;
                if(u8Freq_Offset_Count >= VSB_FREQ_OFFSET_MAX_COUNT)
                {
                    pstTPSetting->u16Frequency = u16Init_Freq;
                    enVSBScanState = STATE_VSB_SCAN_INIT;
                }
            }
            else if( Result == CHECKEND )
                enVSBScanState = STATE_VSB_INIT_DEMODE;
            break;
         default:
            break;
    }

    return Result;
}

EN_SCAN_RESULT msAPI_QAM_Scan(MS_TP_SETTING_ATSC *pstTPSetting)
{
    static U8 u8Freq_Offset_Count;
    static U16 u16Init_Freq;
    EN_SCAN_RESULT Result;

    Result = CHECKING;

    switch(enQAMScanState)
    {
        case STATE_QAM_SCAN_INIT:
            #if (FRONTEND_DEMOD_ATSC_TYPE == EMBEDDED_ATSC_DEMOD)
            EXT_RF_AGC_OFF();
            #endif
            u8Freq_Offset_Count=0;
            u16Init_Freq = pstTPSetting->u16Frequency;
            pstTPSetting->fModulation = DEMOD_ATSC_MODE_256QAM;
            enQAMScanState=STATE_QAM_INIT_DEMODE;
            pstTPSetting->u16Frequency = u16Init_Freq + QAM_FREQ_OFFSET_TABLE[u8Freq_Offset_Count];
            TVSCAN_QAM_SETUP();

            if(!bInitDemod)
            {
                msAPI_Tuner_Initialization_ATSC(1);
            }

 #if ENABLE_TVSCANQAMTIME
            printf("msAPI_Tuner_Initialization_ATSC :=%ld ms\n", msAPI_Timer_DiffTimeFromNow(gU32TVScanQAMTime));
            TVSCAN_QAM_SETUP();
 #endif
            msAPI_Tuner_SetFreq(pstTPSetting->u16Frequency, (EN_DEMOD_ATSC_MODE)pstTPSetting->fModulation);
 #if ENABLE_TVSCANQAMTIME
            printf("msAPI_Tuner_SetFreq :=%ld ms\n", msAPI_Timer_DiffTimeFromNow(gU32TVScanQAMTime));
            TVSCAN_QAM_SETUP();
 #endif
            msAPI_Demodulator_Reset_ATSC();
 #if ENABLE_TVSCANQAMTIME
            printf("msAPI_Demodulator_Reset_ATSC :=%ld ms\n", msAPI_Timer_DiffTimeFromNow(gU32TVScanQAMTime));
            TVSCAN_QAM_SETUP();
 #endif
            msAPI_Timer_Delayms(DEMOD_RESET_DELAY);
            TVSCAN_QAM_SETUP();
            if (msAPI_Demodulator_Init((EN_DEMOD_ATSC_MODE)pstTPSetting->fModulation, (EN_DEMOD_ATSC_SPECTRUM_MODE)pstTPSetting->fSpectrum) == FALSE)
            {
                printf("Error!!! MApp_QAM_Scan Demod init Fail \n");
                enQAMScanState = STATE_QAM_SCAN_INIT;
                Result = UNLOCK;
                bInitDemod = FALSE;
            }
 #if ENABLE_TVSCANQAMTIME
            printf("msAPI_Demodulator_Init :=%ld ms\n", msAPI_Timer_DiffTimeFromNow(gU32TVScanQAMTime));
 #endif
            //msAPI_Timer_Delayms(QAM_DEMOD_STABLE_TIME);
             enQAMScanState = STATE_QAM_CHECK_PRE_LOCK;
             Check_demod_QamPre_lock_time = msAPI_Timer_GetTime0();  //Max 0326 sync X13N check lock flow
            break;

        case STATE_QAM_INIT_DEMODE:
            pstTPSetting->u16Frequency = u16Init_Freq + QAM_FREQ_OFFSET_TABLE[u8Freq_Offset_Count];
            TVSCAN_QAM_SETUP();

            msAPI_Demodulator_Reset_ATSC();
 #if ENABLE_TVSCANQAMTIME
            printf("INIT_DEMODE_Demodulator_Reset :=%ld ms\n", msAPI_Timer_DiffTimeFromNow(gU32TVScanQAMTime));
            TVSCAN_QAM_SETUP();
 #endif
            msAPI_Tuner_SetFreq(pstTPSetting->u16Frequency, (EN_DEMOD_ATSC_MODE)pstTPSetting->fModulation);
 #if ENABLE_TVSCANQAMTIME
            printf("INIT_DEMODE_Tuner_SetFreq :=%ld ms\n", msAPI_Timer_DiffTimeFromNow(gU32TVScanQAMTime));
 #endif

            msAPI_Timer_Delayms(QAM_TUNER_PLL_STABLE_TIME);
            TVSCAN_QAM_SETUP();
            if (msAPI_Demodulator_Init((EN_DEMOD_ATSC_MODE)pstTPSetting->fModulation, (EN_DEMOD_ATSC_SPECTRUM_MODE)pstTPSetting->fSpectrum) == FALSE)
            {
                //printf("Error!!! MApp_QAM_Scan Demod init Fail \n");
                enQAMScanState = STATE_QAM_SCAN_INIT;
                Result = UNLOCK;
            }
 #if ENABLE_TVSCANQAMTIME
            printf("INIT_DEMODE_Demodulator_Init :=%ld ms\n", msAPI_Timer_DiffTimeFromNow(gU32TVScanQAMTime));
 #endif
            msAPI_Timer_Delayms(QAM_DEMOD_STABLE_TIME);
            enQAMScanState = STATE_QAM_CHECK_LOCK;
            break;

        case STATE_QAM_CHECK_PRE_LOCK:
            {
#if (NEW_DEMOD_SCAN)
                if(u8RetQamNoChannelDetect == 1)
#endif
            {
                if(msAPI_Timer_DiffTimeFromNow(Check_demod_QamPre_lock_time) > DEMOD_FIRST_CHECK_LOCK_DELAY)
                {
                    if(msAPI_Qam_Check_PrecLock())
                    {
                        Result = LOCK;
                        enQAMScanState=STATE_QAM_SCAN_INIT;
                        bInitDemod = FALSE;

                      #if (DEMOD_ATSC_USE_UTOPIA)
                        pstTPSetting->fModulation = msAPI_Demod_ATSC_Get_ModulationMode();
                      #else
                        if ( INTERN_ATSC_Check8VSB64_256QAM() == QAM256 )
                        {
                            pstTPSetting->fModulation=DEMOD_ATSC_MODE_256QAM;
                        }
                        else
                        {
                            pstTPSetting->fModulation=DEMOD_ATSC_MODE_64QAM;
                        }
                      #endif
                    }
                    else
                    {
#if (NEW_DEMOD_SCAN)
                        if((msAPI_Timer_DiffTimeFromNow(Check_demod_QamPre_lock_time) > DEMOD_FIRST_QAM_CHECK_LOCK_PERIOD))
#else
                        if((msAPI_Timer_DiffTimeFromNow(Check_demod_QamPre_lock_time) > DEMOD_FIRST_CHECK_LOCK_PERIOD))
#endif
                        {
                            Result = UNLOCK;
                            pstTPSetting->u16Frequency = u16Init_Freq;
                            enQAMScanState = STATE_QAM_SCAN_INIT;
                            bInitDemod = FALSE;
                        }
                        else
                        {
                            Result = CHECKING;
                        }

                    }
                    LIB_SCAN_API_DBG(printf("msAPI_Qam_Check_PrecLock=%d \n", (U8) Result););
                }
            }
#if (NEW_DEMOD_SCAN)
                else if(u8RetQamNoChannelDetect == 2)
                {
                    Result = UNLOCK;
                    enQAMScanState = STATE_QAM_SCAN_INIT;
                    pstTPSetting->u16Frequency = u16Init_Freq;
                    bInitDemod = FALSE;
                    //return Result;
                }
                else
                {   Check_demod_QamPre_lock_time = msAPI_Timer_GetTime0();
                     return CHECKING;
                }
                    LIB_SCAN_API_DBG(printf("msAPI_Qam_Check_PrecLock=%d \n", (U8) Result););
#endif
            }
            break;



        case STATE_QAM_CHECK_LOCK:
            Result = msAPI_QAM_Check_Lock(pstTPSetting);
            if (Result == LOCK)
            {
                enQAMScanState=STATE_QAM_SCAN_INIT;
            }
            else if ( Result == CHECKEND )
            {
                printf("-Go to-STATE_QAM_INIT_DEMODE--\n");
                enQAMScanState = STATE_QAM_INIT_DEMODE;
            }
            else if ( Result == UNLOCK )
            {
                u8Freq_Offset_Count++;
                if(u8Freq_Offset_Count >= QAM_FREQ_OFFSET_MAX_COUNT)
                {
                    pstTPSetting->u16Frequency = u16Init_Freq;
                    enQAMScanState = STATE_QAM_SCAN_INIT;
                }
            }
            break;
         default:
            Result = CHECKING;
            break;
    }

    return Result;
}

#define DEBUG_ZIGZAG_FREQ(x)    //x
S16 msAPI_ScanGetFreqByZigZagPoint(EN_DEMOD_ATSC_MODE Modulation, U8 ZigZagPt, U8 CurRF)
{
    S16 TempFreq=0;

    DEBUG_ZIGZAG_FREQ( printf("msAPI_ScanGetFreqByZigZagPoint(Modulation=%u, ZigZagPt=%u, CurRF=%u)\n", Modulation, ZigZagPt, CurRF); );

    switch (Modulation)
    {
        case DEMOD_ATSC_MODE_8VSB:
            if(ZigZagPt<VSB_FREQ_OFFSET_MAX_COUNT)
                TempFreq=VSB_FREQ_OFFSET_TABLE[ZigZagPt];
            break;

        case DEMOD_ATSC_MODE_NTSC:       //CATV Ch5 or Ch6 => -1.8Mhz ~ +2.3Mhz,      others=> -1.8Mhz ~ +1.8Mhz
            if(ZigZagPt<NTSC_FREQ_OFFSET_MAX_COUNT)
            {
                if ((CurRF == 5) || (CurRF == 6))
                {
                    TempFreq = NTSC_CH5CH6_OFFSET_TABLE[ZigZagPt];
                    //DEBUG_ZIGZAG_FREQ( printf(" => TempFreq=%d\n", TempFreq); );
                }
                else
                    TempFreq=NTSC_AUTO_FREQ_OFFSET_TABLE[ZigZagPt];
            }
            break;

        default:
            break;
    }

    DEBUG_ZIGZAG_FREQ( printf(" => TempFreq=%d\n", TempFreq); );

    return TempFreq;
}

BOOL msAPI_InNTSC_FreqOffset_Range(S16 freq_offset, U8 CurRF)
{
    if ((freq_offset >= FREQ_OFFSET_RANGE_LEFT) && (freq_offset <= FREQ_OFFSET_RANGE_Ch5Ch6_RIGHT))
    {
        if ((freq_offset <= FREQ_OFFSET_RANGE_RIGHT) || ((CurRF == 5) || (CurRF == 6)))
        return TRUE;
    }
    return FALSE;
}

#undef MSAPI_SCAN_ATAC_C

