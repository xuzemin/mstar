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

//*--------------------------------------------------------------------------------------
//* Include Standard files
//*--------------------------------------------------------------------------------------
#ifndef _SAMSUNG_SI2176_S
#define _SAMSUNG_SI2176_S

#include <stdio.h>

#include "Board.h"
#include "datatype.h"
#include "drvIIC.h"
#include "msAPI_Timer.h"
#include "COFDM_Demodulator.h"
#include "Tuner.h"
#include "msAPI_FreqTableATV.h"
#include "msAPI_Tuning.h"
#include "drvGPIO.h"


#define DEBUG_SAMSUNG(x)    //x


#define DIGITAL_TUNER_IF_SAMSUNG 5000   //KHz

static L0_Context Tuner_Si2176_L0_Context;
static L1_Si2176_Context Tuner_nim_Si2176_L1_Si2176_Context={&Tuner_Si2176_L0_Context};
static L1_Si2176_Context *Tuner_lpSi2176= &Tuner_nim_Si2176_L1_Si2176_Context;

static Si2176_CmdReplyObj _Tuner_Si2176_CmdReplyObj;
static Si2176_CmdReplyObj *Tuner_lprsp = &_Tuner_Si2176_CmdReplyObj;

static Si2176_PropObj Tuner_Si2176_PropObj;
static Si2176_PropObj *Tuner_lpprop = &Tuner_Si2176_PropObj;

static double dRFfreq;



#define WAIT_TUNER_STABLE_TIME  40

//*--------------------------------------------------------------------------------------
//* Prototype of function to be provided by customer
//*--------------------------------------------------------------------------------------

extern IF_FREQ MDrv_IFDM_GetIF(void);


U8 IfFreqConvertToTunerSystem( IF_FREQ eIf_Freq)
{
    U8 u8TunerSystem;

    switch(eIf_Freq)
    {
        case  IF_FREQ_B:
            u8TunerSystem = SEMCO_TUNE_ANALOG_B;
            break;
        case  IF_FREQ_G:
            u8TunerSystem = SEMCO_TUNE_ANALOG_G;
            break;
        case  IF_FREQ_DK: // 4
            u8TunerSystem = SEMCO_TUNE_ANALOG_DK; // 5
            break;
        case  IF_FREQ_I:
            u8TunerSystem = SEMCO_TUNE_ANALOG_I;
            break;
        case  IF_FREQ_L:
            u8TunerSystem = SEMCO_TUNE_ANALOG_L;
            break;
        case  IF_FREQ_L_PRIME:
            u8TunerSystem = SEMCO_TUNE_ANALOG_LP;
            break;
        case  IF_FREQ_MN:
            u8TunerSystem = SEMCO_TUNE_ANALOG_M;
            break;
        default:
            u8TunerSystem = SEMCO_TUNE_ANALOG_DK;
            break;
    }

    return u8TunerSystem;
}


static U32 s_Tuner_Samsung_u32Time_LastSetFreq = 0;

static BOOL devTuner_WaitStable(void)
{
    // Wait stable ...
    // Check time pass
    if( s_Tuner_Samsung_u32Time_LastSetFreq )
    {
        while( msAPI_Timer_DiffTime_2(s_Tuner_Samsung_u32Time_LastSetFreq, MsOS_GetSystemTime()) < WAIT_TUNER_STABLE_TIME )
        {
            //printf("[Wait]");
        }
        s_Tuner_Samsung_u32Time_LastSetFreq = 0;
    }

    return TRUE;
}

//BOOL g_Debug_Tuner = 0;

void devTunerSetFreq(U32 u32Freq)
{
    int errorcode = -1;
    IF_FREQ eCurIF_Freq = MDrv_IFDM_GetIF();
    U8 u8TunerSystem = IfFreqConvertToTunerSystem(eCurIF_Freq);
    U8 u8TunerAudioSystem = Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_WIDE_SCAN;
    //U8 u8TunerAudioSystem = SEMCO_TUNE_ANALOG_DK;


    DEBUG_SAMSUNG( printf(" devTunerSetFreq(freq=%lu)\n", u32Freq); );

    dRFfreq = u32Freq/1000; // Unit: KHz


    if( (u8TunerSystem != Si2176Cfg.nSel_atv_video_mode_video_sys)
      ||(u8TunerAudioSystem != Si2176Cfg.nSel_atv_audio_mode_audio_sys)
      )
    {
        Si2176Cfg.nSel_atv_video_mode_video_sys = u8TunerSystem;
        Si2176Cfg.nSel_atv_audio_mode_audio_sys = u8TunerAudioSystem;

        DEBUG_SAMSUNG( printf(" tunerSys=%u,Aud=%u\n", Si2176Cfg.nSel_atv_video_mode_video_sys,
                                                        Si2176Cfg.nSel_atv_audio_mode_audio_sys ); );

        errorcode = Si2176_Configure(Tuner_lpSi2176, Tuner_lprsp, Tuner_lpprop, SI2176_XTAL_INTERNAL);
        if( errorcode != 0 )
        {
            printf("\nError: Tuner Configure error code is %d\r\n",errorcode);
        }

        errorcode = Si2176_SetAmpForCVBS_SIF( Si2176Cfg.nSel_atv_video_mode_video_sys,Tuner_lpSi2176 ,Tuner_lprsp, Tuner_lpprop);
        if(errorcode!=0)
        {
            printf("\nError: Si2176_SetAmpForCVBS_SIF() failed: errorcode=%u\n", errorcode);
        }
    }

    errorcode = Si2176_SetFrequency( Si2176Cfg.nSel_atv_video_mode_video_sys, Tuner_lpSi2176, Tuner_lprsp, dRFfreq, 8000, 0);
    if(errorcode==0)
    {
        printf("\nError: Si2176_SetFrequency() failed: freq=%u\n", u32Freq/1000);
    }

    s_Tuner_Samsung_u32Time_LastSetFreq = MsOS_GetSystemTime();

#if 0 // Test
    //if( g_Debug_Tuner )
    {
        U32 t1, t2;

        t1 = MsOS_GetSystemTime();

        // Wait
        while(1)
        {
            t2 = MsOS_GetSystemTime();
            if( (t2 - t1) > 100 )
            {
                break;
            }

            printf("Tuner:%u %u %d\n", (t2-t1), devTunerGetVIFLockStatus(), devTunerGetFreqOffset());
        }
    }
#endif

}


void _no_use_devTunerSetPLLData(WORD wPLLData, RFBAND eBand)
{
    DEBUG_SAMSUNG(printf("devTunerSetPLLData(wPLLData=%u, eBand=%u)\n", wPLLData, eBand););

    UNUSED(eBand);
    int Tuner_Status=0;
    int Tuner_lock_status=0;
    int errorcode;

    errorcode=Si2176_Configure(Tuner_lpSi2176,Tuner_lprsp,Tuner_lpprop,SI2176_XTAL_INTERNAL);
    //Si2176Cfg.nSel_atv_video_mode_video_sys = SEMCO_TUNE_ANALOG_DK;
#if (TN_FREQ_STEP == FREQ_STEP_62_5KHz)
    dRFfreq = (double)((wPLLData-msAPI_Tuner_GetIF())*62.5);
#elif (TN_FREQ_STEP == FREQ_STEP_50KHz)
    dRFfreq = (double)((wPLLData-msAPI_Tuner_GetIF())*50);
#else
    dRFfreq = (double)((wPLLData-msAPI_Tuner_GetIF())*31.25);
#endif

    DEBUG_SAMSUNG(printf("dRFfreq=%u\n", (U32)dRFfreq););

    Si2176Cfg.nSel_atv_audio_mode_audio_sys =SEMCO_TUNE_ANALOG_DK ;
    Si2176Cfg.nSel_atv_video_mode_video_sys = SEMCO_TUNE_ANALOG_DK;
    Si2176_SetFrequency( Si2176Cfg.nSel_atv_audio_mode_audio_sys, Tuner_lpSi2176, Tuner_lprsp,  dRFfreq, 8000, 0);

    Tuner_Status=Si2176_GetTunerStatus(Tuner_lpSi2176, Tuner_lprsp);
    Tuner_lock_status=Si2176_ATV_Sync_Lock(Tuner_lpSi2176, Tuner_lprsp);
    Si2176_SetAmpForCVBS_SIF( Si2176Cfg.nSel_atv_audio_mode_audio_sys,Tuner_lpSi2176 ,Tuner_lprsp, Tuner_lpprop);


    Si2176_GetAnalogStatus(Tuner_lpSi2176, Tuner_lprsp);
    //printf("Brian Tuner_lock_status is %d\r\n",Tuner_lock_status);
    //printf("Brian Tuner frequency offset %d\r\n",Si2176_GetCarrierFreqOffset(Tuner_lpSi2176,Tuner_lprsp));
    //printf("Brian PLL is %u r\n",wPLLData);
}

void devTunerInit(void)
{
    printf("Si2176_Tuner init \r\n");

    //Si2176_On(lpSi2176,lprsp);
    //Tuner_lprsp = (Si2176_CmdReplyObj *)malloc(sizeof(Si2176_CmdReplyObj));
    //Tuner_lpprop = (Si2176_PropObj *)malloc(sizeof(Si2176_PropObj));

#if 1//def SILICON_TUNER_RESET_OFF
    SILICON_TUNER_RESET_OFF();
#endif

    MsOS_DelayTask(10);

#if 1//def SILICON_TUNER_RESET_ON
    SILICON_TUNER_RESET_ON();
#endif

    MsOS_DelayTask(10);

    int errorcode = -1;

    errorcode = Si2176_Initialize(Tuner_lpSi2176,Tuner_lprsp,Tuner_lpprop,SI2176_XTAL_INTERNAL);
    if( errorcode != 0 )
    {
        printf("\nError: Tuner initial error code is %d\r\n",errorcode);
    }
    //printf(" Si2176_Initialize end\r\n");

    Si2176Cfg.nSel_dtv_out_type= 0;
    Si2176Cfg.nSel_dtv_agc_source = 0;
    Si2176Cfg.nSel_dtv_lif_freq_offset = 5000;
    Si2176Cfg.nSel_dtv_mode_bw= 8;
    Si2176Cfg.nSel_dtv_mode_invert_spectrum =0 ;
    Si2176Cfg.nSel_dtv_mode_modulation = 2;
    Si2176Cfg.nSel_atv_cvbs_out_fine_amp=50;
    Si2176Cfg.nSel_atv_cvbs_out_fine_offset=0;
    Si2176Cfg.nSel_atv_sif_out_amp= 125;
    Si2176Cfg.nSel_atv_sif_out_offset=0;
    Si2176Cfg.nSel_atv_atv_video_mode_tran = 1;
    Si2176Cfg.nSel_atv_video_mod_color = 0;
    Si2176Cfg.nSel_atv_mode_invert_signal =0;
    Si2176Cfg.nSel_atv_audio_mode_audio_sys = Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_SCAN;
    //Si2176Cfg.nSel_atv_audio_mode_audio_sys = Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_WIDE_SCAN;
    Si2176Cfg.nSel_atv_video_mode_video_sys = SEMCO_TUNE_ANALOG_DK;
    Si2176Cfg.if_agc_speed = 0;
    dRFfreq = 55250; // 55.25MHz

    errorcode=Si2176_Configure(Tuner_lpSi2176, Tuner_lprsp, Tuner_lpprop, SI2176_XTAL_INTERNAL);
    if( errorcode != 0 )
    {
        printf("\nError: Tuner Configure error code is %d\r\n",errorcode);
    }

    //printf("Si2176_Tuner init end\r\n");
}

/*************************************************************************
  Subject:    FQD1216 tuner initialized function
  Function:   MDrv_Tuner_Init
  Parmeter:   CONFIG: pointer to tuner address
  Return :    NONE
  Remark:
**************************************************************************/
void devDigitalTuner_Init(void)
{

}

void devDigitalTuner_SetFreq ( double Freq,  RF_CHANNEL_BANDWIDTH eBandWidth)
{
    int errorcode=-1;
    UNUSED(eBandWidth);

    DEBUG_SAMSUNG(printf("devDigitalTuner_SetFreq(Freq=%lf(%u), eBandWidth=%u)\n", Freq, (U32)Freq, eBandWidth););

    Si2176Cfg.nSel_atv_audio_mode_audio_sys = SEMCO_TUNE_DIGITAL;

    errorcode = Si2176_SetFrequency(SEMCO_TUNE_DIGITAL, Tuner_lpSi2176, Tuner_lprsp,  Freq*1000, 8000, 0);
    //printf("Brian Freq is %lu     error code: %d \r\n", Freq,errorcode);
}

S32 devTunerGetFreqOffset(void)
{
    S32 s32FreqOffset;

    // Wait stable ...
    devTuner_WaitStable();

    s32FreqOffset = Si2176_GetCarrierFreqOffset(Tuner_lpSi2176,Tuner_lprsp);
    //DEBUG_SAMSUNG(printf("s32FreqOffset=%d\n", s32FreqOffset););

    return s32FreqOffset;
}

void devTunerSetIF(IF_FREQ eCurrentstandard)
{
    DEBUG_SAMSUNG(printf(" devTunerSetIF(Std=%u)\n", eCurrentstandard););
    U8 u8NewTunerSystem;
    int errorcode;


    u8NewTunerSystem = IfFreqConvertToTunerSystem(eCurrentstandard);

    if( Si2176Cfg.nSel_atv_video_mode_video_sys != u8NewTunerSystem )
    {
        Si2176Cfg.nSel_atv_video_mode_video_sys = u8NewTunerSystem;

        errorcode = Si2176_Configure(Tuner_lpSi2176, Tuner_lprsp, Tuner_lpprop, SI2176_XTAL_INTERNAL);
        if( errorcode != 0 )
        {
            printf("\nError: Tuner Configure error code is %d\r\n",errorcode);
        }

        errorcode = Si2176_SetFrequency( Si2176Cfg.nSel_atv_video_mode_video_sys, Tuner_lpSi2176, Tuner_lprsp, dRFfreq, 8000, 0);
        if(errorcode==0)
        {
            printf("\nError: Si2176_SetFrequency() failed\n");
        }

        errorcode = Si2176_SetAmpForCVBS_SIF( Si2176Cfg.nSel_atv_video_mode_video_sys, Tuner_lpSi2176 ,Tuner_lprsp, Tuner_lpprop);
        if(errorcode!=0)
        {
            printf("\nError: Si2176_SetAmpForCVBS_SIF() failed: errorcode=%u\n", errorcode);
        }

        s_Tuner_Samsung_u32Time_LastSetFreq = MsOS_GetSystemTime();
    }

}

BOOL devTunerGetVIFLockStatus(void)
{
    //printf("");

    // Wait stable ...
    devTuner_WaitStable();

    if((Si2176_ATV_Sync_Lock(Tuner_lpSi2176, Tuner_lprsp))==1)
    {
        //printf(" => 1;");
        return TRUE;
    }
    else
    {
        //printf(" => 0;");
        return FALSE;
    }
}

#undef _SAMSUNG_SI2176_S
#endif


