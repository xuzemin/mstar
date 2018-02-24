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
/**********************************************************************
 Copyright (c) 2006-2009 MStar Semiconductor, Inc.
 All rights reserved.

 Unless otherwise stipulated in writing, any and all information contained
 herein regardless in any format shall remain the sole proprietary of
 MStar Semiconductor Inc. and be kept in strict confidence
 (MStar Confidential Information) by the recipient.
 Any unauthorized act including without limitation unauthorized disclosure,
 copying, use, reproduction, sale, distribution, modification, disassembling,
 reverse engineering and compiling of the contents of MStar Confidential
 Information is unlawful and strictly prohibited. MStar hereby reserves the
 rights to any and all damages, losses, costs and expenses resulting therefrom.

* File  : SILAB_2158_A20.c
**********************************************************************/
/*@ </FileComment ID=1246257763274> @*/

/*@ <Include> @*/

#include "SILAB_2158_A20.h"
#include "SILAB_2158_A20/Si2158_L1_API.h"
// #include "SI2158/Si2158_firmware_0_C_build_4.h"
#include "SILAB_2158_A20/Si2158_firmware_0_C_build_6.h"

/* Si2158 API Specific Includes */
#include "SILAB_2158_A20/Si2158_L2_API.h"               /* Include file for this code */
#include "SILAB_2158_A20/Si2158_firmware_0_E_build_15.h"       /* firmware compatible with Si2158-marking */
#include "SILAB_2158_A20/Si2158_firmware_2_0_build_x.h"
#define Si2158_BYTES_PER_LINE 8
#ifdef USING_ALIF_FILTER
#include "SILAB_2158_A20/write_ALIF_video_coeffs.h"   /* .h file from custom Video filter Tool output */
#endif
#ifdef USING_DLIF_FILTER
#include "SILAB_2158_A20/write_DLIF_video_coeffs.h"   /* .h file from custom Video filter Tool output */
#endif

#include "msAPI_FreqTableATV.h"
#include "msAPI_Tuning.h"
#include "MApp_GlobalVar.h"
#include "MApp_TopStateMachine.h"

#define DBG_TUNER(x)   // x

//PLL lock check parameters
#define C_Si2158_POLL_INTERVAL      5 //ms
#define C_Si2158_PLL_POLL_TIMETOUT      100 //ms
#define C_Si2158_PLL_POLL_CNT           C_Si2158_PLL_POLL_TIMETOUT/C_Si2158_POLL_INTERVAL //counter
#define C_Si2158_PF_TO_CF_SHIFT_B 2250 /*KHZ*/
#define C_Si2158_PF_TO_CF_SHIFT_G 2750 /*KHZ*/
#define C_Si2158_PF_TO_CF_SHIFT_DK 2750 /*KHZ*/
#define C_Si2158_PF_TO_CF_SHIFT_I  2750 /*KHZ*/
#define C_Si2158_PF_TO_CF_SHIFT_L  2750 /*KHZ*/
#define C_Si2158_PF_TO_CF_SHIFT_M  1750 /*KHZ*/
#define C_Si2158_PF_TO_CF_SHIFT_L1 2750 /*KHZ*/

// center frequencies
#define C_Si2158_IF_CENTER_B  5000 /*KHZ*/
#define C_Si2158_IF_CENTER_GH 5000 /*KHZ*/
#define C_Si2158_IF_CENTER_DK 5000 /*KHZ*/
#define C_Si2158_IF_CENTER_I  5000 /*KHZ*/
#define C_Si2158_IF_CENTER_L  5000 /*KHZ*/
#define C_Si2158_IF_CENTER_L1 5000 /*KHZ*/
#define C_Si2158_IF_CENTER_M  5000 /*KHZ*/
#define C_Si2158_IF_CENTER_N  5000 /*KHZ*/
#define C_Si2158_IF_FREQUENCY          ((U16)  4570)  /* kHz */


#define C_Si2158_LO_ADDRESS           ((U8)  0xC0) //Very Important
#define C_Si2158_LO_DIVIDER_STEP       ((U32) 1000)  /* Hz */
#define C_Si2158_LO_DIVIDER_STEP_ANA   ((U16)  1000)  /* Hz */
#define C_SILABS_Si2158_STR                        "SILABS_Si2158_A20"
#define Si2158_BASE_ADDRESS 0xc0

typedef enum SI_Network
{
    SI_network_none        = 0x00,    /**< No network */
    SI_network_dvbt1       = 0x01,    /**< DVB-T (Terrestrial) */
    SI_network_dvbs1       = 0x02,    /**< DVB-S (Satellite)   */
    SI_network_dvbc        = 0x04,    /**< DVB-C (Cable) */
    SI_network_analog      = 0x08,    /**< Analog */
    SI_network_dvbt2       = 0x10,    /**< DVB-T2 (Terrestrial) */
    SI_network_dvbs2       = 0x20,    /**< DVB-S2 (Satellite)   */
    SI_network_dvbt        = 0x11,    /**< DVB-T, DVB-T2 (Terrestrial) */
    SI_network_dvbs        = 0x22,    /**< DVB-S, DVB-S2 (Satellite)   */
    SI_network_ip          = 0x40,    /**< IP network   */
    SI_network_fm          = 0x80     /**< Fm Radio    */
} SI_Network;

typedef enum SI_AnalogTVSystem
{
    si_tv_system_m,
    si_tv_system_bg,
    si_tv_system_i,
    si_tv_system_dk,
    si_tv_system_l,
    si_tv_system_lp,
    si_tv_system_invalid
}SI_AnalogTVSystem;

typedef enum
{
    E_Network_Type_DVBT =1,
    E_Network_Type_DVBC ,
    E_Network_Type_Analog_T ,
    E_Network_Type_Analog_C ,
    E_Network_Type_DVBT2,
    E_Network_Type_ATSC,
    E_Network_Type_ISDBT,
    E_Network_Type_ISDBC,
    E_Network_Type_DVBS,
    E_Network_Type_DTMB,
    E_Network_Type_QAM_US,
} Network_Type;


static L1_Si2158_Context *api;
static MS_BOOL tuner_init = false;
#ifdef DUAL_TUNER_EXT_IF_AGC               /** Different IF AGC pin controlled by different demod */
// Please refer to HW circuit for the actual connection of AGC1 and AGC2 pins respectively
#define TUNER_IF_AGC_BY_INTERN_DEMOD  Si2158_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_AGC2_3DB
#define TUNER_IF_AGC_BY_EXTERN_DEMOD  Si2158_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_AGC1_3DB
#endif

BOOLEAN  m_bDeviceBusy = FALSE;

static EN_TUNER_MODE m_eMode = E_TUNER_DTV_DVB_T_MODE;//E_TUNER_INVALID;
static AUDIOSTANDARD_TYPE_ m_OtherMode = E_AUDIOSTANDARD_NOTSTANDARD_;

extern IF_FREQ MDrv_IFDM_GetIF(void);
int Si2158_LoadFirmware(L1_Si2158_Context *api, unsigned char fw_table[], int nbLines);
int Si2158_Configure(L1_Si2158_Context *api);
void SetIfDemod(RF_CHANNEL_BANDWIDTH eBandWidth, Network_Type eNetworktype, SI_AnalogTVSystem TV_SYS);
U32 Si2158_GetDefaultIF(U32 Freq, SI_AnalogTVSystem TV_SYS);

void ATV_Set_Artificial_Snow(BOOLEAN bEnable)
{
    if(bEnable == 1)
    {
        api->prop->atv_artificial_snow.gain= Si2158_ATV_ARTIFICIAL_SNOW_PROP_GAIN_AUTO;
    }
    else
    {
        api->prop->atv_artificial_snow.gain= Si2158_ATV_ARTIFICIAL_SNOW_PROP_GAIN_OFF;
    }
    api->prop->atv_artificial_snow.offset = 0;
    if (Si2158_L1_SetProperty2(api,Si2158_TUNER_LO_INJECTION_PROP) != 0)
    {
        printf("ERROR ---Si2158_L1_SetProperty2(api,Si2158_TUNER_LO_INJECTION_PROP)----\n");
    }

}
static SI_AnalogTVSystem Atv_system_enum_conversion(EN_TUNER_MODE eMode,AUDIOSTANDARD_TYPE_ OtherMode)
{

    SI_AnalogTVSystem ret_atv_sys = si_tv_system_invalid;

    switch (eMode)
    {
        case E_TUNER_ATV_PAL_MODE:
            {
                switch(OtherMode)
                {
                    case E_AUDIOSTANDARD_BG_:
                    case E_AUDIOSTANDARD_BG_A2_:
                    case E_AUDIOSTANDARD_BG_NICAM_:
                        ret_atv_sys = si_tv_system_bg;
                        break;
                    case E_AUDIOSTANDARD_I_:
                        ret_atv_sys = si_tv_system_i;
                        break;
                    case E_AUDIOSTANDARD_DK_:
                    case E_AUDIOSTANDARD_DK1_A2_:
                    case E_AUDIOSTANDARD_DK2_A2_:
                    case E_AUDIOSTANDARD_DK3_A2_:
                    case E_AUDIOSTANDARD_DK_NICAM_:
                        ret_atv_sys = si_tv_system_dk;
                        break;
                    case E_AUDIOSTANDARD_L_:
                        ret_atv_sys = si_tv_system_l;
                        break;
                    case E_AUDIOSTANDARD_M_:
                    case E_AUDIOSTANDARD_M_BTSC_:
                    case E_AUDIOSTANDARD_M_A2_:
                    case E_AUDIOSTANDARD_M_EIA_J_:
                        ret_atv_sys = si_tv_system_m;
                        break;
                    case E_AUDIOSTANDARD_NOTSTANDARD_:
                    default:
                        ret_atv_sys = si_tv_system_invalid;
                        break;
                }
            }
            break;
        case E_TUNER_ATV_SECAM_L_PRIME_MODE:
            ret_atv_sys = si_tv_system_lp;
            break;
        case E_TUNER_ATV_SECAM_L_MODE:
            ret_atv_sys = si_tv_system_l;
            break;
        case E_TUNER_ATV_NTSC_MODE:
            ret_atv_sys = si_tv_system_m;
            break;
        case E_TUNER_DTV_ISDB_MODE:
        case E_TUNER_DTV_DVB_T_MODE:
        case E_TUNER_DTV_DVB_C_MODE:
        case E_TUNER_DTV_DVB_S_MODE:
        case E_TUNER_DTV_DTMB_MODE:
        case E_TUNER_DTV_ATSC_MODE:
        case E_TUNER_DTV_DVB_T2_MODE:
        default:
            ret_atv_sys = si_tv_system_invalid;
            break;
    }

    return ret_atv_sys;
}

static Network_Type Dtv_system_enum_conversion(EN_TUNER_MODE eMode)
{

    Network_Type ret_dtv_sys = E_Network_Type_ISDBT;

    switch (eMode)
    {
        case E_TUNER_DTV_ISDB_MODE:
            ret_dtv_sys = E_Network_Type_ISDBT;
            break;
        case E_TUNER_DTV_DVB_T_MODE:
            ret_dtv_sys = E_Network_Type_DVBT;
            break;
        case E_TUNER_DTV_DVB_C_MODE:
            ret_dtv_sys = E_Network_Type_DVBC;
            break;
        case E_TUNER_DTV_DVB_S_MODE:
            ret_dtv_sys = E_Network_Type_DVBS;
            break;
        case E_TUNER_DTV_DTMB_MODE:
            ret_dtv_sys = E_Network_Type_DTMB;
            break;
        case E_TUNER_DTV_ATSC_MODE:
            ret_dtv_sys = E_Network_Type_ATSC;
            break;
        case E_TUNER_DTV_DVB_T2_MODE:
            ret_dtv_sys = E_Network_Type_DVBT2;
            break;
        case E_TUNER_DTV_QAM_US_MODE:
            ret_dtv_sys = E_Network_Type_QAM_US;
            break;
        case E_TUNER_ATV_PAL_MODE:
        case E_TUNER_ATV_SECAM_L_PRIME_MODE:
        case E_TUNER_ATV_NTSC_MODE:
        default:
            ret_dtv_sys = E_Network_Type_ISDBT;
            break;
    }
    return ret_dtv_sys;
}


static BOOLEAN device_tuner_si_2158(void)
{
    //ADD YOU TUNER DRIVER CODE IN HERE
    //int return_code =0;
    BOOLEAN retb = FALSE;

    api = (L1_Si2158_Context *)malloc(sizeof(L1_Si2158_Context));
    /* Allocate rsp variable */

    //HW reset
    /* Software Init */
    Si2158_L1_API_Init(api,C_Si2158_LO_ADDRESS);

    if (Si2158_Init(api) != 0 ) {
      printf("\n");
      printf("ERROR ----------------------------------\n");
      printf("ERROR initializing the Si2158 at 0x%02x!\n",C_Si2158_LO_ADDRESS);
      printf("ERROR ----------------------------------\n");
      printf("\n");

      retb = FALSE;
    }
    else
      api->prop->atv_video_mode.video_sys = 0xff;
      api->prop->dtv_mode.modulation = 0xff;
      api->prop->dtv_agc_speed.if_agc_speed = 0xff;
      retb = TRUE;

    return retb;
}


static BOOLEAN Connect(void)
{
    if (m_bDeviceBusy == TRUE)
    {
        // Connect should not be called again.
        printf("[Warning]%s,%d\n",__FILE__,__LINE__);
        return FALSE;
    }

    m_bDeviceBusy = TRUE;
    return TRUE;
}

/*
static BOOLEAN Disconnect(void)
{
    DBG_TUNER(printf("device_tuner_si_2158: Disconnect\n"));

    m_bDeviceBusy = FALSE;

    return TRUE;
}
*/
/*

*/
//**************************************************************************
//	[Function Name]:
//					 MApp_Si2158_FineTune()
//	[Description]
//
//	[para]:
//					 persistence:   0 = NON_PERSISTENT,1 = PERSISTENT
//					 This bit makes the offset persistent across TUNER_TUNE_FREQ,
//
//					apply_to_lif:    0 = DO_NOT_APPLY_TO_LIF, 1 = APPLY_TO_LIF
//					When enabled, this applies the frequency shift to the LIF output.
//
//					offset_500hz:  Range OFFSET_500HZ_MIN = -4000 to OFFSET_500HZ_MAX = 4000.
//								Offset the RF center frequency (x 500 Hz).
//
//	[Return]:
//					 none
//@20081007 by hansen.chen
//**************************************************************************
#if ((FIXED_SI2158_FINE_TUNE_GARBAGE)&&(!BLOADER))
BOOLEAN MApp_Si2158_FineTune(unsigned char persistence,unsigned char apply_to_lif,int offset_500hz)
{
	Si2158_L1_FINE_TUNE(api,persistence,apply_to_lif,offset_500hz);
	return 0;
}
#endif
static MS_S16 s16Prev_finetune=0;
BOOLEAN ATV_SetTune( U32 u32FreqKHz,RFBAND eBand, EN_TUNER_MODE eMode,U8 OtherMode)
{
    BOOLEAN retb = FALSE;
    U32 freqHz = 0;
    int count=0;
    int freq_offset=0;
    U32 start_time = 0;
    U32 timeout = 0;
    S16 s16Finetune = 0;
    SI_AnalogTVSystem TV_SYS = si_tv_system_invalid;
    U8 previous_video_sys = api->prop->atv_video_mode.video_sys;
    U8 Current_video_sys = api->prop->atv_video_mode.video_sys;
    U8 Current_color = 0;
    IF_FREQ CurrentStandard = MDrv_IFDM_GetIF();

    eBand = eBand;

    TV_SYS = Atv_system_enum_conversion(eMode,(AUDIOSTANDARD_TYPE_)OtherMode);

    DBG_TUNER(printf ("ATV_SetTune freq = %ld; SYS = %d...........\n", u32FreqKHz, TV_SYS);)

    if(s16Finetune!=0)
    {
        u32FreqKHz -= (s16Finetune*625/10); //re-calcuate original freq w/o finetune
        //for example, current frequency is 224250KHz, if AnalogFinetune is set to +1(+62.5KHz), that means middleware will call u32FreqKHz:224313KHz(224250+63) Finetune:1
    }
	#if ((FIXED_SI2158_FINE_TUNE_GARBAGE)&&(!BLOADER))
	if(g_u16Si2158FineTuneCenterFreq!=0)
	{
		MApp_Si2158_FineTune(0,0,0);
		g_u16Si2158FineTuneCenterFreq = 0;
	}
	#endif
    if(tuner_init)
    {
        /* do not go through SetIfdemod if same TV_SYS is used but only frequency is changed*/
        switch (TV_SYS)
        {
            case si_tv_system_bg:
				if(CurrentStandard==IF_FREQ_G)
				{
                    freqHz = (u32FreqKHz * 1000) + C_Si2158_PF_TO_CF_SHIFT_G*1000;
				}
				else//IF_FREQ_B
				{
                    freqHz = (u32FreqKHz * 1000) + C_Si2158_PF_TO_CF_SHIFT_B*1000;
				}
				/*
		                if(u32FreqKHz < 300000)
		                {
		                    freqHz = (u32FreqKHz * 1000) + C_Si2158_PF_TO_CF_SHIFT_B*1000;
		                }
		                else
		                {
		                    freqHz = (u32FreqKHz * 1000) + C_Si2158_PF_TO_CF_SHIFT_G*1000;
		                }
		         */
                api->prop->tuner_lo_injection.band_1      = Si2158_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
                api->prop->tuner_lo_injection.band_2      = Si2158_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE;
                api->prop->tuner_lo_injection.band_3      = Si2158_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE;
                if (Si2158_L1_SetProperty2(api,Si2158_TUNER_LO_INJECTION_PROP) != 0)
                {
                        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_TUNER_LO_INJECTION_PROP\n"));
                }
//                if (u32FreqKHz < 300000 && previous_video_sys != Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B )
				if (CurrentStandard != IF_FREQ_G)
                {
                    api->prop->atv_video_mode.video_sys=Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B;
                    api->prop->atv_lif_freq.offset = C_Si2158_IF_CENTER_B;
                    if (Si2158_L1_SetProperty2(api, Si2158_ATV_LIF_FREQ_PROP) != 0)
                    {
                        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_ATV_LIF_FREQ_PROP\n"));
                    }
                    SetIfDemod(E_RF_CH_BAND_8MHz, E_Network_Type_Analog_T, TV_SYS);
                    break;
                }
//                if (u32FreqKHz >= 300000 && previous_video_sys != Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_GH)
				if (CurrentStandard == IF_FREQ_G)
                {
                    api->prop->atv_video_mode.video_sys=Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_GH;
                    api->prop->atv_lif_freq.offset = C_Si2158_IF_CENTER_GH;
                    if (Si2158_L1_SetProperty2(api, Si2158_ATV_LIF_FREQ_PROP) != 0)
                    {
                        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_ATV_LIF_FREQ_PROP\n"));
                    }
                    SetIfDemod(E_RF_CH_BAND_8MHz, E_Network_Type_Analog_T, TV_SYS);
                    break;
                }
                break;
            case si_tv_system_dk:
                freqHz = (u32FreqKHz * 1000) + C_Si2158_PF_TO_CF_SHIFT_DK*1000;
                api->prop->tuner_lo_injection.band_1      = Si2158_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
                api->prop->tuner_lo_injection.band_2      = Si2158_TUNER_LO_INJECTION_PROP_BAND_2_HIGH_SIDE;
                api->prop->tuner_lo_injection.band_3      = Si2158_TUNER_LO_INJECTION_PROP_BAND_3_HIGH_SIDE;
                if (Si2158_L1_SetProperty2(api,Si2158_TUNER_LO_INJECTION_PROP) != 0)
                {
                        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_TUNER_LO_INJECTION_PROP\n"));
                }
                if (previous_video_sys != Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_DK)
                {
                    SetIfDemod(E_RF_CH_BAND_8MHz, E_Network_Type_Analog_T, TV_SYS);
                }
                break;
            case si_tv_system_i:
                freqHz = (u32FreqKHz * 1000) + C_Si2158_PF_TO_CF_SHIFT_I*1000;
                api->prop->tuner_lo_injection.band_1      = Si2158_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
                api->prop->tuner_lo_injection.band_2      = Si2158_TUNER_LO_INJECTION_PROP_BAND_2_HIGH_SIDE;
                api->prop->tuner_lo_injection.band_3      = Si2158_TUNER_LO_INJECTION_PROP_BAND_3_HIGH_SIDE;
                if (Si2158_L1_SetProperty2(api,Si2158_TUNER_LO_INJECTION_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_TUNER_LO_INJECTION_PROP\n"));
                }
                if (previous_video_sys != Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_I)
                {
                    SetIfDemod(E_RF_CH_BAND_8MHz, E_Network_Type_Analog_T, TV_SYS);
                }
                break;
            case si_tv_system_m:
                freqHz = (u32FreqKHz * 1000) + C_Si2158_PF_TO_CF_SHIFT_M*1000;
                api->prop->tuner_lo_injection.band_1      = Si2158_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
                api->prop->tuner_lo_injection.band_2      = Si2158_TUNER_LO_INJECTION_PROP_BAND_2_HIGH_SIDE;
                api->prop->tuner_lo_injection.band_3      = Si2158_TUNER_LO_INJECTION_PROP_BAND_3_HIGH_SIDE;
                if (Si2158_L1_SetProperty2(api,Si2158_TUNER_LO_INJECTION_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_TUNER_LO_INJECTION_PROP\n"));
                }
                if (previous_video_sys != Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_M)
                {
                    SetIfDemod(E_RF_CH_BAND_8MHz, E_Network_Type_Analog_T, TV_SYS);
                }
                break;
            case si_tv_system_l:
                freqHz = (u32FreqKHz * 1000) + C_Si2158_PF_TO_CF_SHIFT_L*1000;
                api->prop->tuner_lo_injection.band_1      = Si2158_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
                api->prop->tuner_lo_injection.band_2      = Si2158_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE;
                api->prop->tuner_lo_injection.band_3      = Si2158_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE;
                if (Si2158_L1_SetProperty2(api,Si2158_TUNER_LO_INJECTION_PROP) != 0)
                {
                        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_TUNER_LO_INJECTION_PROP\n"));
                }
                if (previous_video_sys != Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_L)
                {
                    SetIfDemod(E_RF_CH_BAND_8MHz, E_Network_Type_Analog_T, TV_SYS);
                }
                break;
            case si_tv_system_lp:
                freqHz = (u32FreqKHz * 1000) - C_Si2158_PF_TO_CF_SHIFT_L1*1000;
                api->prop->tuner_lo_injection.band_1      = Si2158_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
                api->prop->tuner_lo_injection.band_2      = Si2158_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE;
                api->prop->tuner_lo_injection.band_3      = Si2158_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE;
                if (Si2158_L1_SetProperty2(api,Si2158_TUNER_LO_INJECTION_PROP) != 0)
                {
                        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_TUNER_LO_INJECTION_PROP\n"));
                }
                if (previous_video_sys != Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_LP)
                {
                    SetIfDemod(E_RF_CH_BAND_8MHz, E_Network_Type_Analog_T, TV_SYS);
                }
                break;
            case si_tv_system_invalid:
            default:
                printf("[Error]%s, %s, %d\n", __FILE__,__FUNCTION__,__LINE__);
                break;
        }
        Current_video_sys = api->prop->atv_video_mode.video_sys;

#ifdef DUAL_TUNER_EXT_IF_AGC
        api->prop->atv_config_if_port.atv_agc_source = Si2158_ATV_CONFIG_IF_PORT_PROP_ATV_AGC_SOURCE_AGC2_3DB;
        if (Si2158_L1_SetProperty2(api, Si2158_ATV_CONFIG_IF_PORT_PROP) != 0)
        {
            mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_ATV_CONFIG_IF_PORT_PROP\n"));
        }
#endif

        if(s16Finetune!=0)
        {
            freq_offset= (int) (s16Finetune*625/10);// 1 FinetuneStep is 62.5KHz
            api->prop->atv_lif_freq.offset = (unsigned int)(freq_offset+Si2158_GetDefaultIF(u32FreqKHz, TV_SYS));
            if (Si2158_L1_SetProperty2(api, Si2158_ATV_LIF_FREQ_PROP) != 0)
            {
                mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_ATV_LIF_FREQ_PROP\n"));
            }
        }
        else
        {
            if(s16Prev_finetune!=0)  // current finetune=0, previous finetune!=0, restore original lif_freq_offset
            {
                api->prop->atv_lif_freq.offset = Si2158_GetDefaultIF(u32FreqKHz, TV_SYS);
                if (Si2158_L1_SetProperty2(api, Si2158_ATV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_ATV_LIF_FREQ_PROP\n"));
                }
            }
        }
        s16Prev_finetune = s16Finetune;

        if (freqHz < Si2158_TUNER_TUNE_FREQ_CMD_FREQ_MIN || freqHz > Si2158_TUNER_TUNE_FREQ_CMD_FREQ_MAX)
        {
            printf("[Silabs]:<= Frequency out of Range\n");
            mcSHOW_HW_MSG((" [Silabs]: <= Frequency out of Range\n"));
            return FALSE;
        }

        if( Si2158_ATV_Channel_Spur_Shifting(api, freqHz, Current_video_sys, Current_color)!= 0)
        {
             printf((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DEBUG_SAMPLE_FREQ_PROP\n"));
        }

        if (Si2158_L1_TUNER_TUNE_FREQ(api,Si2158_TUNER_TUNE_FREQ_CMD_MODE_ATV,  freqHz) != 0)
        {
            printf("[Silabs]:Error Si2158_L1_TUNER_TUNE_FREQ\n");
            mcSHOW_HW_MSG((" [Silabs]: Error Si2158_L1_TUNER_TUNE_FREQ\n"));
        }
		//sync with tuner Engineer to reduce wait time from190ms to 130ms
        /* wait for TUNINT, timeout is 40ms */
        timeout = 30;
        start_time = MsOS_GetSystemTime();
        while( (MsOS_GetSystemTime() - start_time) < timeout )
        {
            if (Si2158_L1_CheckStatus(api) != 0)
                return FALSE;
            if (api->status->tunint)
            {
                DBG_TUNER(printf("!!!!!!!!!!!!!LOCK..................................\n");)
                retb = TRUE;
                break;
            }
        }

        if( MApp_TopStateMachine_GetTopState() == STATE_TOP_ATV_SCAN
    #if ENABLE_SBTVD_ATV_SYSTEM
         || MApp_TopStateMachine_GetTopState() == STATE_TOP_CATV_SCAN
    #endif
        )
        {
            if(stGenSetting.stScanMenuSetting.u8ScanType == SCAN_TYPE_AUTO )
            {
                system_wait(20); //wait 20ms
//                printf("!!!!!!!!!!!!!STATE_TOP_ATV_SCAN return\n");
                return retb;
            }
        }

        /* wait for ATVINT, timeout is 150ms */
        timeout = 100;
        start_time = MsOS_GetSystemTime();
        while( (MsOS_GetSystemTime() - start_time) < timeout )
        {
            if (Si2158_L1_CheckStatus(api) != 0)
                return FALSE;
            if (api->status->atvint)
            {
                DBG_TUNER(printf("!!!!!!!!!!!!!ATV ----------LOCK....................\n");)
                retb = TRUE;
                break;
            }
        }

        if (!count)
            return retb;
    }

    return retb;
}


BOOLEAN DTV_SetTune(double Freq, RF_CHANNEL_BANDWIDTH eBandWidth, EN_TUNER_MODE eMode)
// void mdev_TunerDigitalSetFreq_Si2158(U32 Freq, RF_CHANNEL_BANDWIDTH eBandWidth,Network_Type eNetworktype)
{
    BOOLEAN retb = FALSE;
    U32 freqHz = 0;
    int count=0;
    U32 start_time = 0;
    U32 timeout = 0;
    Network_Type eNetworktype = E_Network_Type_DVBT;
    static RF_CHANNEL_BANDWIDTH pre_bw = E_RF_CH_BAND_INVALID;

    eNetworktype = Dtv_system_enum_conversion(eMode);

    unsigned char previous_dtv_mode=api->prop->dtv_mode.modulation;
    unsigned char previous_agc_speed=api->prop->dtv_agc_speed.if_agc_speed;

    DBG_TUNER(printf ("Si2158_TunerSetFreq freq = %d; Band = %d Network = %d\n", (U16)Freq,eBandWidth, eNetworktype);)

    if(tuner_init)
    {
          /* Make sure the sample freq is auto for all DTV tunes */
          api->prop->debug_sample_freq.fs_mhz = 0;
         /* update DEBUG_SAMPLE_FREQ property */
          if (Si2158_L1_SetProperty2(api, Si2158_DEBUG_SAMPLE_FREQ_PROP) != 0)
         {
                printf((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DEBUG_SAMPLE_FREQ_PROP\n"));
         }

        api->prop->tuner_lo_injection.band_1      = Si2158_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
        api->prop->tuner_lo_injection.band_2      = Si2158_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE;
        api->prop->tuner_lo_injection.band_3      = Si2158_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE;
        if (Si2158_L1_SetProperty2(api,Si2158_TUNER_LO_INJECTION_PROP) != 0)
        {
                mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_TUNER_LO_INJECTION_PROP\n"));
        }

    #ifdef DUAL_TUNER_EXT_IF_AGC
        if (eNetworktype == E_Network_Type_DVBT2)
        {
            api->prop->dtv_config_if_port.dtv_agc_source = TUNER_IF_AGC_BY_EXTERN_DEMOD;
        }
		else
        {
            api->prop->dtv_config_if_port.dtv_agc_source = TUNER_IF_AGC_BY_INTERN_DEMOD;
        }
		if (Si2158_L1_SetProperty2(api, Si2158_DTV_CONFIG_IF_PORT_PROP) != 0)
		{
            mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_CONFIG_IF_PORT_PROP\n"));
		}
    #endif

        switch (eNetworktype)
        {
           case E_Network_Type_DVBT:
                freqHz = 1000000;
                if ( (previous_dtv_mode != Si2158_DTV_MODE_PROP_MODULATION_DVBT)
                    || (previous_agc_speed!=Si2158_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO)
                    || (eBandWidth != pre_bw)
                    )
                    SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
                break;
           case E_Network_Type_DVBT2:
                freqHz = 1000000;
                if ( (previous_dtv_mode != Si2158_DTV_MODE_PROP_MODULATION_DVBT)
                    || (previous_agc_speed!=Si2158_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_39)
                    || (eBandWidth != pre_bw)
                   )
                    SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
                break;
           case E_Network_Type_DVBC:
                freqHz = 1000000;
                if (previous_dtv_mode != Si2158_DTV_MODE_PROP_MODULATION_DVBC)
                    SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
                break;
           case E_Network_Type_ISDBT:
                freqHz = 1000000;
                if (previous_dtv_mode != Si2158_DTV_MODE_PROP_MODULATION_ISDBT)
                    SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
                break;
           case E_Network_Type_ISDBC:
                freqHz = 1000000;
                if (previous_dtv_mode != Si2158_DTV_MODE_PROP_MODULATION_ISDBC)
                    SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
                break;
           case E_Network_Type_DTMB:
                freqHz = 1000000;
                if (previous_dtv_mode != Si2158_DTV_MODE_PROP_MODULATION_DTMB)
                    SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
                break;
           case E_Network_Type_ATSC:
                freqHz = 1000;
                if (previous_dtv_mode != Si2158_DTV_MODE_PROP_MODULATION_ATSC)
                    SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
                break;
           case E_Network_Type_QAM_US:
                freqHz = 1000;
                if (previous_dtv_mode != Si2158_DTV_MODE_PROP_MODULATION_QAM_US)
                    SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
                break;
           case E_Network_Type_Analog_T:
           case E_Network_Type_Analog_C:
           case E_Network_Type_DVBS:
           default:
                freqHz = 1000000;
                printf("[Error]%s,%s,%d\n",__FILE__,__FUNCTION__,__LINE__);
                break;
        }
        freqHz *= (U32)(Freq);

        if (freqHz < Si2158_TUNER_TUNE_FREQ_CMD_FREQ_MIN || freqHz > Si2158_TUNER_TUNE_FREQ_CMD_FREQ_MAX)
        {
            printf("[Silabs]:<= Frequency out of Range\n");
            mcSHOW_HW_MSG((" [Silabs]: <= Frequency out of Range\n"));
            return FALSE;
        }

        if (Si2158_L1_TUNER_TUNE_FREQ(api,Si2158_TUNER_TUNE_FREQ_CMD_MODE_DTV,  freqHz) != 0)
        {
            printf("[Silabs]:Error Si2158_L1_TUNER_TUNE_FREQ\n");
            mcSHOW_HW_MSG((" [Silabs]: Error Si2158_L1_TUNER_TUNE_FREQ\n"));
            return FALSE;
        }

        /* wait for TUNINT, timeout is 40ms */
        timeout = 140;
        start_time = MsOS_GetSystemTime();
        while( (MsOS_GetSystemTime() - start_time) < timeout )
        {
            if (Si2158_L1_CheckStatus(api) != 0)
                return FALSE;
            if (api->status->tunint)
            {
                retb = TRUE;
                DBG_TUNER(printf("!!!!!!!!!!!!!LOCK...................\n");)
                break;
            }
        }
        /* wait for DTVINT, timeout is 20ms */
        timeout = 20;
        start_time = MsOS_GetSystemTime();
        while( (MsOS_GetSystemTime() - start_time) < timeout )
        {
            if (Si2158_L1_CheckStatus(api) != 0)
                return FALSE;
            if (api->status->dtvint)
            {
                DBG_TUNER(printf("!!!!!!!!!!!!!DTV ----------LOCK................\n");)
                retb = TRUE;
                break;
            }
        }

        if (retb == TRUE)
            pre_bw = eBandWidth;

        if (!count)
            return retb;
    }

    if (retb == TRUE)
        pre_bw = eBandWidth;

    return retb;
}
#if 0
/************************************************************************************************************************
  NAME: Si2158_LoadFirmware
  DESCRIPTON: Load firmware from FIRMWARE_TABLE array in Si2158_Firmware_x_y_build_z.h file into Si2158
              Requires Si2158 to be in bootloader mode after PowerUp
  Programming Guide Reference:    Flowchart A.3 (Download FW PATCH flowchart)

  Parameter:  Si2158 Context (I2C address)
  Returns:    Si2158/I2C transaction error code, 0 if successful
************************************************************************************************************************/
int Si2158_LoadFirmware(L1_Si2158_Context *p_api, unsigned char fw_table[], int nbLines)
{
    int return_code = 0;
    int line;
    DBG_TUNER(printf("Si2158_LoadFirmware nbLines %d Begin.......\n", nbLines);)
    /* for each 8 bytes in fw_table */
    for (line = 0; line < nbLines; line++)
    {
        /* send that 8 byte I2C command to Si2158 */
        if ((return_code = Si2158_L1_API_Patch(p_api, 8, fw_table+8*line)) != 0)
        {
          printf("Si2158_LoadFirmware error 0x%02x patching line %d: %s\n", return_code, line, Si2158_L1_API_ERROR_TEXT(return_code) );
          if (line == 0) {
          printf("The firmware is incompatible with the part!\n");
          }
          return ERROR_Si2158_LOADING_FIRMWARE;
        }

    }
    DBG_TUNER(printf("Si2158_LoadFirmware complete...\n");)
    return 0;
}

/************************************************************************************************************************
  NAME: configureSi2158
  DESCRIPTION: Setup Si2158 video filters, GPIOs/clocks, Common Properties startup, Tuner startup, ATV startup, and DTV startup.
  Parameter:  Pointer to Si2158 Context (I2C address)
  Returns:    I2C transaction error code, 0 if successful
************************************************************************************************************************/
int Si2158_Configure           (L1_Si2158_Context *p_api)
{
    int return_code;
    return_code=0;

    /* Set All Properties startup configuration */
    p_api->prop->tuner_ien.tcien = Si2158_TUNER_IEN_PROP_TCIEN_ENABLE;
    p_api->prop->tuner_ien.rssilien = Si2158_TUNER_IEN_PROP_RSSILIEN_DISABLE;
    p_api->prop->tuner_ien.rssihien = Si2158_TUNER_IEN_PROP_RSSIHIEN_DISABLE;
    if ((return_code=Si2158_L1_SetProperty2(p_api,Si2158_TUNER_IEN_PROP)) != 0)
    {
       mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_TUNER_IEN_PROP\n"));
       return return_code;
    }
    p_api->prop->dtv_ien.chlien = Si2158_DTV_IEN_PROP_CHLIEN_ENABLE;
    if ((return_code=Si2158_L1_SetProperty2(p_api,Si2158_DTV_IEN_PROP)) != 0)
    {
        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_IEN_PROP\n"));
       return return_code;
    }
     p_api->prop->atv_ien.chlien = Si2158_ATV_IEN_PROP_CHLIEN_ENABLE;
     p_api->prop->atv_ien.pclien = Si2158_ATV_IEN_PROP_PCLIEN_DISABLE;
    if ((return_code=Si2158_L1_SetProperty2(p_api,Si2158_ATV_IEN_PROP)) != 0)
    {
        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_ATV_IEN_PROP\n"));
       return return_code;
    }
    p_api->prop->dtv_mode.bw = Si2158_DTV_MODE_PROP_BW_BW_8MHZ;
    p_api->prop->dtv_mode.modulation = Si2158_DTV_MODE_PROP_MODULATION_DVBT;
    p_api->prop->dtv_mode.invert_spectrum = Si2158_DTV_MODE_PROP_INVERT_SPECTRUM_INVERTED;
    if ((return_code=Si2158_L1_SetProperty2(p_api,Si2158_DTV_MODE_PROP)) != 0)
    {
        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_MODE_PROP\n"));
       return return_code;
    }

    p_api->prop->atv_video_mode.color= Si2158_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;
    p_api->prop->atv_video_mode.invert_spectrum= Si2158_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_INVERTED;
    p_api->prop->atv_video_mode.video_sys = Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_GH;
   if ((return_code=Si2158_L1_SetProperty2(p_api,Si2158_ATV_VIDEO_MODE_PROP)) != 0)
    {
       mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_ATV_VIDEO_MODE_PROP\n"));
       return return_code;
    }


    p_api->prop->atv_config_if_port.atv_agc_source = Si2158_ATV_CONFIG_IF_PORT_PROP_ATV_AGC_SOURCE_AGC2_3DB;
    p_api->prop->atv_config_if_port.atv_out_type = Si2158_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE_LIF_DIFF_IF1;
    if ((return_code=Si2158_L1_SetProperty2(p_api, Si2158_ATV_CONFIG_IF_PORT_PROP)) != 0)
    {
        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_ATV_CONFIG_IF_PORT_PROP\n"));
        return return_code;
    }

   p_api->prop->atv_lif_freq.offset = C_Si2158_IF_CENTER_GH;
   if ((return_code=Si2158_L1_SetProperty2(p_api, Si2158_ATV_LIF_FREQ_PROP)) != 0)
   {
       mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_ATV_LIF_FREQ_PROP\n"));
       return return_code;
   }
   p_api->prop->tuner_lo_injection.band_1      = Si2158_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
   p_api->prop->tuner_lo_injection.band_2      = Si2158_TUNER_LO_INJECTION_PROP_BAND_2_HIGH_SIDE;
   p_api->prop->tuner_lo_injection.band_3      = Si2158_TUNER_LO_INJECTION_PROP_BAND_3_HIGH_SIDE;
   if ((return_code=Si2158_L1_SetProperty2(p_api,Si2158_TUNER_LO_INJECTION_PROP)) != 0)
   {
           mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_TUNER_LO_INJECTION_PROP\n"));
           return return_code;
   }
    p_api->prop->atv_agc_speed.if_agc_speed= Si2158_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_185;
    if ((return_code=Si2158_L1_SetProperty2(p_api,Si2158_ATV_AGC_SPEED_PROP)) != 0)
    {
        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_ATV_AGC_SPEED_PROP\n"));
        return return_code;
    }
    p_api->prop->atv_ext_agc.max_10mv= Si2158_ATV_EXT_AGC_PROP_MAX_10MV_DEFAULT;
    p_api->prop->atv_ext_agc.min_10mv= Si2158_ATV_EXT_AGC_PROP_MIN_10MV_DEFAULT;
    if ((return_code=Si2158_L1_SetProperty2(p_api,Si2158_ATV_EXT_AGC_PROP)) != 0)
    {
        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_ATV_EXT_AGC_PROP\n"));
        return return_code;
    }

//    p_api->prop->atv_afc_range.range_khz= 2000;
    p_api->prop->atv_afc_range.range_khz= 100;
    if ((return_code=Si2158_L1_SetProperty2(p_api, Si2158_ATV_AFC_RANGE_PROP)) != 0)
    {
        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_ATV_AFC_RANGE_PROP\n"));
        return return_code;
    }
    p_api->prop->atv_lif_out.offset = Si2158_ATV_LIF_OUT_PROP_OFFSET_DEFAULT;
    p_api->prop->atv_lif_out.amp = 148;
    if ((return_code=Si2158_L1_SetProperty2(p_api, Si2158_ATV_LIF_OUT_PROP)) != 0)
    {
        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_ATV_LIF_OUT_PROP\n"));
        return return_code;
    }
    p_api->prop->dtv_config_if_port.dtv_out_type   = Si2158_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LIF_IF1;
    p_api->prop->dtv_config_if_port.dtv_agc_source = Si2158_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_AGC2_3DB;
    if ((return_code=Si2158_L1_SetProperty2(p_api,Si2158_DTV_CONFIG_IF_PORT_PROP)) != 0)
    {
        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_CONFIG_IF_PROP\n"));
        return return_code;
    }

    // Si2158_DTV_PGA_LIMITS_PROP
    p_api->prop->dtv_pga_limits.max = 56;
    p_api->prop->dtv_pga_limits.min = 24;
    if ((return_code=Si2158_L1_SetProperty2(p_api,Si2158_DTV_PGA_LIMITS_PROP)) != 0)
    {
        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_PGA_LIMITS_PROP\n"));
        return return_code;
    }

    // p_api->prop->dtv_rf_top.dtv_rf_top= Si2158_DTV_RF_TOP_PROP_DTV_RF_TOP_M2DB;
    p_api->prop->dtv_rf_top.dtv_rf_top= Si2158_DTV_RF_TOP_PROP_DTV_RF_TOP_P6DB;
    if ((return_code=Si2158_L1_SetProperty2(p_api, Si2158_DTV_RF_TOP_PROP)) != 0)
    {
        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_RF_TOP_PROP\n"));
        return return_code;
    }
    p_api->prop->dtv_filter_select.filter             = Si2158_DTV_FILTER_SELECT_PROP_FILTER_CUSTOM1; /* (default 'DEFAULT') */
    if ((return_code=Si2158_L1_SetProperty2(p_api,Si2158_DTV_FILTER_SELECT_PROP)) != 0)
    {
        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_FILTER_SELECT_PROP\n"));
        return return_code;
    }
    p_api->prop->dtv_lif_out.offset = Si2158_DTV_LIF_OUT_PROP_OFFSET_DEFAULT;
    /* AMP=17 to get IF_AGC=1.24Vrms in DVB-T when AMP is controlled by demod AGC (DTV_AGC_SOURCE=DLIF_AGC_3DB) */
    p_api->prop->dtv_lif_out.amp = 40;
    if ((return_code=Si2158_L1_SetProperty2(p_api, Si2158_DTV_LIF_OUT_PROP)) != 0)
    {
        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_LIF_OUT_PROP\n"));
        return return_code;
    }
    p_api->prop->dtv_lif_freq.offset=C_Si2158_IF_FREQUENCY;
    if ((return_code=Si2158_L1_SetProperty2(p_api, Si2158_DTV_LIF_FREQ_PROP)) != 0)
    {
        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_LIF_FREQ_PROP\n"));
        return return_code;
    }

    return 0;
}
#endif
/************************************************************************************************************************
  NAME: Si2158_GetRSSILevel
  DESCRIPTION: Get RSSI from Si2158. RSSI returned by Si2158 is defined with a CW signal to prevent to make assumptions about the analog/digital content.
  For DVB-T, input power level (dBm)=RSSI -6dB
  Parameter:  Pointer to Si2158 Context (I2C address)
  Returns:    RSSI value
************************************************************************************************************************/
float Si2158_GetRSSILevel(float *strength_dBm)
{
    unsigned char return_code = NO_Si2158_ERROR;
    int rssi = -128;

    if ((return_code=Si2158_L1_TUNER_STATUS(api,Si2158_TUNER_STATUS_CMD_INTACK_CLEAR)) != 0)
    {
        mcSHOW_HW_MSG((" [Silabs]: ERROR_READING_COMMAND Si2158_TUNER_STATUS\n"));
    }
    else
    {
        rssi = (((int)(api->rsp->tuner_status.rssi))<<24) >> 24;  // type conversion with arithmetic shift for sign extension
    }
	*strength_dBm = (float)rssi;
    return (float)rssi;
}
/************************************************************************************************************************
  NAME: Si2158_GetATV_AFC_freq
  DESCRIPTION: Get ATV AFC frequency from Si2158. AFC frequency returned by Si2158 is valid once Si2158 is locked on ATV channel
  Parameter:  Pointer to Si2158 Context (I2C address)
  Returns:    AFC_freq value in Hz, although AFC frequency resolution is in kHz
************************************************************************************************************************/
S16 Si2158_GetATV_AFC_freq(void)
{
    int return_code;
    int AFC_freqkHz;
	S16 AFC_freq_I,AFC_freq_F;
    S32 AFC_freq;
    return_code=0;
    AFC_freqkHz=0;
    AFC_freq=0;

    if ((return_code=Si2158_L1_ATV_STATUS(api,Si2158_ATV_STATUS_CMD_INTACK_OK))!=0)
	{
        mcSHOW_HW_MSG((" [Silabs]: ERROR_READING_COMMAND Si2158_ATV_STATUS\n"));
        return return_code;
    }
    AFC_freqkHz= api->rsp->atv_status.afc_freq;
    AFC_freq=(U32)(((1000*AFC_freqkHz)*10)/625);
	AFC_freq_I = AFC_freq/1000;
	AFC_freq_F = AFC_freq%1000;
	if(AFC_freq_F > 500)
	{
		AFC_freq_I = AFC_freq_I + 1;
	}
	else if(AFC_freq_F < -500)
	{
		AFC_freq_I = AFC_freq_I - 1;
	}
	AFC_freq = AFC_freq_I;
    return AFC_freq;
}

BOOLEAN mdev_ATV_GetSignalStrength_Si2158(U16 *strength)
{
    float Prel = 0.0;
    float f_ssi = 0;
    float ch_power_db_a=0;
    float ch_power_db=0;

    ch_power_db_a = ch_power_db_a;
    Prel = Prel;

    ch_power_db = Si2158_GetRSSILevel(&ch_power_db);
	//printf("ch_power_db =%d\n",(S32)ch_power_db);
    //the range of Si2158 strength if -5 to -75
    #if 1//for nordig -95 to -40
	f_ssi = f_ssi;
    if ( ch_power_db < -95)
    {
		*strength = 0;
    }
    else if ( ch_power_db <= -80)//information 0-20
    {
		*strength = (U16)((ch_power_db-(-95))*4)/3;
    }
    else if ( ch_power_db <= -70)//information 21-50
    {
		*strength = (U16)((ch_power_db-(-80))*3)+20;
    }
    else if ( ch_power_db <= -60)//information 51-80
    {
		*strength = (U16)((ch_power_db-(-70))*3)+50;
    }
    else if ( ch_power_db <= -50)//information 81-95
    {
		*strength = (U16)(((ch_power_db-(-60))*3)/2)+80;
    }
    else if ( ch_power_db <= -40)//information 96-100
    {
		*strength = (U16)((ch_power_db-(-50))/2)+95;
    }
    else
	{
		*strength = 100;
	}
	#else
    if ( ch_power_db < -75)
    {
        ch_power_db=-75;
    }
    else if ( ch_power_db >-5)
    {
        ch_power_db=-5;
    }
    f_ssi=(((-4)-(ch_power_db))*100)/72;
    *strength = (U16)(100-f_ssi);
	#endif
    mcSHOW_HW_MSG((">>> SSI_CH_PWR(dB) = %f , Score = %d<<<\n", ch_power_db, f_ssi));
    mcSHOW_HW_MSG((">>> SSI = %d <<<\n", (int)*strength));
    return TRUE;
}




/* Setup properties to switch standards. */
void SetIfDemod(RF_CHANNEL_BANDWIDTH eBandWidth, Network_Type eNetworktype, SI_AnalogTVSystem TV_SYS)
{
    // set a global here to save the video standard,  because it's not always available from the caller.
    if(TV_SYS == si_tv_system_invalid)
    {
        switch (eNetworktype)
        {
           case E_Network_Type_DVBT:
                api->prop->dtv_mode.modulation = Si2158_DTV_MODE_PROP_MODULATION_DVBT;
                if(eBandWidth == E_RF_CH_BAND_6MHz)
                    api->prop->dtv_mode.bw = Si2158_DTV_MODE_PROP_BW_BW_6MHZ;
                else if (eBandWidth == E_RF_CH_BAND_7MHz)
                    api->prop->dtv_mode.bw = Si2158_DTV_MODE_PROP_BW_BW_7MHZ;
                else
                    api->prop->dtv_mode.bw = Si2158_DTV_MODE_PROP_BW_BW_8MHZ;

                api->prop->dtv_mode.invert_spectrum = Si2158_DTV_MODE_PROP_INVERT_SPECTRUM_NORMAL;

                if (Si2158_L1_SetProperty2(api, Si2158_DTV_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_MODE_PROP\n"));
                }
                api->prop->dtv_agc_speed.if_agc_speed = Si2158_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
                api->prop->dtv_agc_speed.agc_decim = Si2158_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF;
                if (Si2158_L1_SetProperty2(api, Si2158_DTV_AGC_SPEED_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_AGC_SPEED_PROP\n"));
                }
                api->prop->dtv_initial_agc_speed_period.period = 0;
                if (Si2158_L1_SetProperty2(api, Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP\n"));
                }
                /* AMP=17 to get IF_AGC=1.24Vrms in DVB-T when AMP is controlled by demod AGC (DTV_AGC_SOURCE=DLIF_AGC_3DB) */
                api->prop->dtv_lif_out.amp =28;//40;
                if (Si2158_L1_SetProperty2(api, Si2158_DTV_LIF_OUT_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_LIF_OUT_PROP\n"));
                }
                break;
           case E_Network_Type_DVBT2:
                api->prop->dtv_mode.modulation = Si2158_DTV_MODE_PROP_MODULATION_DVBT;
                if(eBandWidth == E_RF_CH_BAND_8MHz)
                    api->prop->dtv_mode.bw = Si2158_DTV_MODE_PROP_BW_BW_8MHZ;
                else if (eBandWidth == E_RF_CH_BAND_7MHz)
                    api->prop->dtv_mode.bw = Si2158_DTV_MODE_PROP_BW_BW_7MHZ;
                else
                    api->prop->dtv_mode.bw = Si2158_DTV_MODE_PROP_BW_BW_6MHZ;
                api->prop->dtv_mode.invert_spectrum = Si2158_DTV_MODE_PROP_INVERT_SPECTRUM_INVERTED;

                if (Si2158_L1_SetProperty2(api, Si2158_DTV_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_MODE_PROP\n"));
                }
                api->prop->dtv_agc_speed.if_agc_speed = Si2158_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_39;
                api->prop->dtv_agc_speed.agc_decim = Si2158_DTV_AGC_SPEED_PROP_AGC_DECIM_4;
                if (Si2158_L1_SetProperty2(api, Si2158_DTV_AGC_SPEED_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_AGC_SPEED_PROP\n"));
                }
                api->prop->dtv_initial_agc_speed_period.period = 210;
                if (Si2158_L1_SetProperty2(api, Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP\n"));
                }
                /* AMP=32 to get IF_AGC=1.24Vrms in DVB-T2 when AMP is controlled by demod AGC (DTV_AGC_SOURCE=DLIF_AGC_3DB) */
                api->prop->dtv_lif_out.amp =40;
                if (Si2158_L1_SetProperty2(api, Si2158_DTV_LIF_OUT_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_LIF_OUT_PROP\n"));
                }
                break;
           case E_Network_Type_DVBC:
                api->prop->dtv_mode.modulation = Si2158_DTV_MODE_PROP_MODULATION_DVBC;
                api->prop->dtv_mode.bw = Si2158_DTV_MODE_PROP_BW_BW_8MHZ;
                api->prop->dtv_mode.invert_spectrum = Si2158_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_INVERTED;

                if (Si2158_L1_SetProperty2(api, Si2158_DTV_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_MODE_PROP\n"));
                }
                api->prop->dtv_agc_speed.if_agc_speed = Si2158_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
                api->prop->dtv_agc_speed.agc_decim = Si2158_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF;
                if (Si2158_L1_SetProperty2(api, Si2158_DTV_AGC_SPEED_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_AGC_SPEED_PROP\n"));
                }
                api->prop->dtv_initial_agc_speed_period.period = 0;
                if (Si2158_L1_SetProperty2(api, Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP\n"));
                }
                /* AMP=14 to get IF_AGC=1.20Vrms in DVB-C when AMP is controlled by demod AGC (DTV_AGC_SOURCE=DLIF_AGC_3DB) */
                api->prop->dtv_lif_out.amp =40;
                if (Si2158_L1_SetProperty2(api, Si2158_DTV_LIF_OUT_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_LIF_OUT_PROP\n"));
                }
                break;
           case E_Network_Type_ISDBT:
                api->prop->dtv_mode.modulation = Si2158_DTV_MODE_PROP_MODULATION_ISDBT;
                api->prop->dtv_mode.bw = Si2158_DTV_MODE_PROP_BW_BW_6MHZ;
                #if ((CHIP_FAMILY_TYPE==CHIP_FAMILY_EULER) || \
                     (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN) || \
                     (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA))
                api->prop->dtv_mode.invert_spectrum = 0;
                #else
                api->prop->dtv_mode.invert_spectrum = Si2158_DTV_MODE_PROP_INVERT_SPECTRUM_INVERTED;
                #endif
                if (Si2158_L1_SetProperty2(api, Si2158_DTV_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_MODE_PROP\n"));
                }
                api->prop->dtv_agc_speed.if_agc_speed = Si2158_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
                api->prop->dtv_agc_speed.agc_decim = Si2158_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF;
                if (Si2158_L1_SetProperty2(api, Si2158_DTV_AGC_SPEED_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_AGC_SPEED_PROP\n"));
                }
                api->prop->dtv_initial_agc_speed_period.period = 0;
                if (Si2158_L1_SetProperty2(api, Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP\n"));
                }
                /* AMP=55 to get IF_AGC 1.0v in MSB1400 on 149B-C01A when AMP is controlled by demod AGC (DTV_AGC_SOURCE=DLIF_AGC_3DB) */
                api->prop->dtv_lif_out.amp = 40;
                if (Si2158_L1_SetProperty2(api, Si2158_DTV_LIF_OUT_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_LIF_OUT_PROP\n"));
                }

                api->prop->dtv_lif_freq.offset =6000;
                if (Si2158_L1_SetProperty2(api, Si2158_DTV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_LIF_FREQ_PROP\n"));
                }
                break;
           case E_Network_Type_ATSC:
                api->prop->dtv_mode.modulation = Si2158_DTV_MODE_PROP_MODULATION_ATSC;
                api->prop->dtv_mode.bw = Si2158_DTV_MODE_PROP_BW_BW_6MHZ;
                api->prop->dtv_mode.invert_spectrum = Si2158_DTV_MODE_PROP_INVERT_SPECTRUM_NORMAL;

                if (Si2158_L1_SetProperty2(api, Si2158_DTV_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_MODE_PROP\n"));
                }
                api->prop->dtv_agc_speed.if_agc_speed = Si2158_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
                api->prop->dtv_agc_speed.agc_decim = Si2158_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF;
                if (Si2158_L1_SetProperty2(api, Si2158_DTV_AGC_SPEED_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_AGC_SPEED_PROP\n"));
                }
                api->prop->dtv_initial_agc_speed_period.period = 0;
                if (Si2158_L1_SetProperty2(api, Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP\n"));
                }
                /* AMP=17 to get IF_AGC=1.24Vrms in DVB-T when AMP is controlled by demod AGC (DTV_AGC_SOURCE=DLIF_AGC_3DB) */
                api->prop->dtv_lif_out.amp =40;
                if (Si2158_L1_SetProperty2(api, Si2158_DTV_LIF_OUT_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_LIF_OUT_PROP\n"));
                }
                api->prop->dtv_lif_freq.offset = 6000;
                if (Si2158_L1_SetProperty2(api, Si2158_DTV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_LIF_FREQ_PROP\n"));
                }
                 api->prop->tuner_return_loss.mode = Si2158_TUNER_RETURN_LOSS_PROP_MODE_TERRESTRIAL;
                 if (Si2158_L1_SetProperty2(api, Si2158_TUNER_RETURN_LOSS_PROP_CODE) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_TUNER_RETURN_LOSS_PROP_CODE\n"));
                }

                api->prop->dtv_pga_limits.max = 56;
                api->prop->dtv_pga_limits.min = 24;
                if (Si2158_L1_SetProperty2(api,Si2158_DTV_PGA_LIMITS_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_PGA_LIMITS_PROP\n"));
                }

                break;
           case E_Network_Type_QAM_US:
                api->prop->dtv_mode.modulation = Si2158_DTV_MODE_PROP_MODULATION_QAM_US;
                api->prop->dtv_mode.bw = Si2158_DTV_MODE_PROP_BW_BW_6MHZ;
                api->prop->dtv_mode.invert_spectrum = Si2158_DTV_MODE_PROP_INVERT_SPECTRUM_NORMAL;

                if (Si2158_L1_SetProperty2(api, Si2158_DTV_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_MODE_PROP\n"));
                }
                api->prop->dtv_agc_speed.if_agc_speed = Si2158_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
                api->prop->dtv_agc_speed.agc_decim = Si2158_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF;
                if (Si2158_L1_SetProperty2(api, Si2158_DTV_AGC_SPEED_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_AGC_SPEED_PROP\n"));
                }
                api->prop->dtv_initial_agc_speed_period.period = 0;
                if (Si2158_L1_SetProperty2(api, Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP\n"));
                }
                /* AMP=17 to get IF_AGC=1.24Vrms in DVB-T when AMP is controlled by demod AGC (DTV_AGC_SOURCE=DLIF_AGC_3DB) */
                api->prop->dtv_lif_out.amp =40;
                if (Si2158_L1_SetProperty2(api, Si2158_DTV_LIF_OUT_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_LIF_OUT_PROP\n"));
                }
                api->prop->dtv_lif_freq.offset = 6000;
                if (Si2158_L1_SetProperty2(api, Si2158_DTV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_LIF_FREQ_PROP\n"));
                }

                api->prop->tuner_return_loss.mode = Si2158_TUNER_RETURN_LOSS_PROP_MODE_TERRESTRIAL;
                 if (Si2158_L1_SetProperty2(api, Si2158_TUNER_RETURN_LOSS_PROP_CODE) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_TUNER_RETURN_LOSS_PROP_CODE\n"));
                }
                api->prop->dtv_pga_limits.max = 56;
                api->prop->dtv_pga_limits.min = 24;
                if (Si2158_L1_SetProperty2(api,Si2158_DTV_PGA_LIMITS_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_PGA_LIMITS_PROP\n"));
                }


                break;

            case E_Network_Type_DTMB:
           case E_Network_Type_ISDBC:
           case E_Network_Type_Analog_T:
           case E_Network_Type_Analog_C:
           case E_Network_Type_DVBS:
           default:
                printf("[Error]%s,%s,%d\n",__FILE__,__FUNCTION__,__LINE__);
                printf(" eNetworktype=%d\n", eNetworktype);
                break;
        }
    }
    else
    {
        switch (TV_SYS)
        {
            case si_tv_system_bg:
                api->prop->atv_video_mode.color = Si2158_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;
                api->prop->atv_video_mode.invert_spectrum = Si2158_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_INVERTED;
                // api->prop->atv_video_mode.trans = Si2158_ATV_VIDEO_MODE_PROP_TRANS_CABLE;
                if (Si2158_L1_SetProperty2(api, Si2158_ATV_VIDEO_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_ATV_VIDEO_MODE_PROP\n"));
                }
                break;
            case si_tv_system_dk:
                api->prop->atv_video_mode.video_sys = Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_DK;
                api->prop->atv_video_mode.color = Si2158_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;
                api->prop->atv_video_mode.invert_spectrum = Si2158_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_INVERTED;
                // api->prop->atv_video_mode.trans = Si2158_ATV_VIDEO_MODE_PROP_TRANS_CABLE;
                if (Si2158_L1_SetProperty2(api, Si2158_ATV_VIDEO_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_ATV_VIDEO_MODE_PROP\n"));
                }
                api->prop->atv_lif_freq.offset = C_Si2158_IF_CENTER_DK;
                if (Si2158_L1_SetProperty2(api, Si2158_ATV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_ATV_LIF_FREQ_PROP\n"));
                }
                break;
            case si_tv_system_i:
                api->prop->atv_video_mode.video_sys = Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_I;
                api->prop->atv_video_mode.color = Si2158_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;
                api->prop->atv_video_mode.invert_spectrum = Si2158_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_INVERTED;
                // api->prop->atv_video_mode.trans = Si2158_ATV_VIDEO_MODE_PROP_TRANS_CABLE;
                if (Si2158_L1_SetProperty2(api, Si2158_ATV_VIDEO_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_ATV_VIDEO_MODE_PROP\n"));
                }
                api->prop->atv_lif_freq.offset = C_Si2158_IF_CENTER_I;
                if (Si2158_L1_SetProperty2(api, Si2158_ATV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_ATV_LIF_FREQ_PROP\n"));
                }
                break;
            case si_tv_system_m:
                api->prop->atv_video_mode.video_sys = Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_M;
                api->prop->atv_video_mode.color = Si2158_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;
                api->prop->atv_video_mode.invert_spectrum = Si2158_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_INVERTED;
                // api->prop->atv_video_mode.trans = Si2158_ATV_VIDEO_MODE_PROP_TRANS_CABLE;
                if (Si2158_L1_SetProperty2(api, Si2158_ATV_VIDEO_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_ATV_VIDEO_MODE_PROP\n"));
                }
                api->prop->atv_lif_freq.offset = C_Si2158_IF_CENTER_M;
                if (Si2158_L1_SetProperty2(api, Si2158_ATV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_ATV_LIF_FREQ_PROP\n"));
                }
                break;
            case si_tv_system_l:
                api->prop->atv_video_mode.video_sys = Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_L;
                api->prop->atv_video_mode.color = Si2158_ATV_VIDEO_MODE_PROP_COLOR_SECAM;
                api->prop->atv_video_mode.invert_spectrum = Si2158_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_INVERTED;
                // api->prop->atv_video_mode.trans = Si2158_ATV_VIDEO_MODE_PROP_TRANS_CABLE;
                if (Si2158_L1_SetProperty2(api, Si2158_ATV_VIDEO_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_ATV_VIDEO_MODE_PROP\n"));
                }
                api->prop->atv_lif_freq.offset = C_Si2158_IF_CENTER_L;
                if (Si2158_L1_SetProperty2(api, Si2158_ATV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_ATV_LIF_FREQ_PROP\n"));
                }
                api->prop->atv_lif_out.offset = Si2158_ATV_LIF_OUT_PROP_OFFSET_DEFAULT;
                break;
            case si_tv_system_lp:
                api->prop->atv_video_mode.video_sys = Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_LP;
                api->prop->atv_video_mode.color = Si2158_ATV_VIDEO_MODE_PROP_COLOR_SECAM;
                api->prop->atv_video_mode.invert_spectrum = Si2158_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_INVERTED;
                // api->prop->atv_video_mode.trans = Si2158_ATV_VIDEO_MODE_PROP_TRANS_CABLE;
                if (Si2158_L1_SetProperty2(api, Si2158_ATV_VIDEO_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_ATV_VIDEO_MODE_PROP\n"));
                }
                api->prop->atv_lif_freq.offset = C_Si2158_IF_CENTER_L1;
                if (Si2158_L1_SetProperty2(api, Si2158_ATV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_ATV_LIF_FREQ_PROP\n"));
                }
                break;
            case si_tv_system_invalid:
            default:
                break;
        }
    }
}

U32 Si2158_GetDefaultIF(U32 Freq, SI_AnalogTVSystem TV_SYS)
{
    U32 offset=0;
    switch (TV_SYS)
    {
        case si_tv_system_bg:
            if (Freq < 300000)
            {
                offset = C_Si2158_IF_CENTER_B;
                break;
            }
            if (Freq >= 300000)
            {
                offset = C_Si2158_IF_CENTER_GH;
                break;
            }
            break;
        case si_tv_system_dk:
            offset = C_Si2158_IF_CENTER_DK;
            break;
        case si_tv_system_i:
            offset = C_Si2158_IF_CENTER_I;
            break;
        case si_tv_system_m:
            offset = C_Si2158_IF_CENTER_M;
            break;
        case si_tv_system_l:
            offset = C_Si2158_IF_CENTER_L;
            break;
        case si_tv_system_lp:
            offset = C_Si2158_IF_CENTER_L1;
            break;
        case si_tv_system_invalid:
        default:
            printf("[Error]%s, %s, %d\n",__FILE__,__FUNCTION__,__LINE__);
            break;
    }
    return offset;
}

// ATV init..........
void devTunerInit(void)
{
    BOOLEAN bRet = TRUE;
    if(tuner_init == TRUE)
    {
	  return;
     }
    bRet &= device_tuner_si_2158();
    bRet &= Connect();

    if (bRet == FALSE)
    {
       printf("[Error]%s,%d\n",__FILE__,__LINE__);
     }
    else
     {
         tuner_init = TRUE;
     }

    return;
}

// DTV init..........
void devDigitalTuner_Init(void)
{
    BOOLEAN bRet = TRUE;
    if(tuner_init == TRUE)
    {
	  return;
     }
    bRet &= device_tuner_si_2158();
    bRet &= Connect();

    if (bRet == FALSE)
    {
       printf("[Error]%s,%d\n",__FILE__,__LINE__);
     }
    else
     {
         tuner_init = TRUE;
     }
    return;
}

void devDigitalTuner_SetFreq ( double Freq,  RF_CHANNEL_BANDWIDTH eBandWidth)
{

    BOOLEAN bRet = TRUE;

    DBG_TUNER(printf("[devDigitalTuner_SetFreq]Freq=%d, eBandWidth=%d, m_eMode=%d\n",(U16)Freq,(U8)eBandWidth,(U8)m_eMode);)

    if (m_bDeviceBusy == FALSE)
    {
        // devDigitalTuner_Init should be called first.
        printf("[Error]%s,%d\n",__FILE__,__LINE__);
        return;
    }

    // Freq (MHz)
    bRet &= DTV_SetTune(Freq, eBandWidth, m_eMode);

    if (bRet == FALSE)
        printf("[Error]%s,%d\n",__FILE__,__LINE__);

    return;
}


void devTunerSetFreq(U32 u32Freq)
{
    BOOLEAN retb = TRUE;
    IF_FREQ CurrentStandard = MDrv_IFDM_GetIF();

    if (m_bDeviceBusy == FALSE)
    {
        retb = FALSE;
        printf("[Error]%s,%d\n",__FILE__,__LINE__);
        return;
    }

	//printf("[CurrentStandard],%d\n",CurrentStandard);
    if(CurrentStandard==IF_FREQ_B)
    {
        m_eMode = E_TUNER_ATV_PAL_MODE;
        m_OtherMode = E_AUDIOSTANDARD_BG_;
    }
    else if  (CurrentStandard==IF_FREQ_G)
    {
        m_eMode = E_TUNER_ATV_PAL_MODE;
        m_OtherMode = E_AUDIOSTANDARD_BG_;
    }
    else if  (CurrentStandard==IF_FREQ_I)
    {
        m_eMode = E_TUNER_ATV_PAL_MODE;
        m_OtherMode = E_AUDIOSTANDARD_I_;
    }
    else if  (CurrentStandard==IF_FREQ_DK)
    {
        m_eMode = E_TUNER_ATV_PAL_MODE;
        m_OtherMode = E_AUDIOSTANDARD_DK_;
    }
    else if  (CurrentStandard==IF_FREQ_L)
    {
        m_eMode = E_TUNER_ATV_SECAM_L_MODE;
        m_OtherMode = E_AUDIOSTANDARD_L_;
    }
    else if  (CurrentStandard==IF_FREQ_L_PRIME)
    {
        m_eMode = E_TUNER_ATV_SECAM_L_PRIME_MODE;
        m_OtherMode = E_AUDIOSTANDARD_L_;
    }
    else if  (CurrentStandard==IF_FREQ_MN)
    {
        m_eMode = E_TUNER_ATV_PAL_MODE;
        m_OtherMode = E_AUDIOSTANDARD_M_;
    }
    else
    {
        m_eMode = E_TUNER_ATV_PAL_MODE;
        m_OtherMode = E_AUDIOSTANDARD_BG_;
    }

    DBG_TUNER(printf("[devTunerSetFreq]%s, %d,  m_OtherMode=%d, u32Freq=%ld, CurrentStandard=%d\n",__FILE__,__LINE__,m_OtherMode,u32Freq,CurrentStandard);)

    retb &= ATV_SetTune(u32Freq/1000,(RFBAND)0, m_eMode,(U8)m_OtherMode);

    if (retb == FALSE)
        printf("[Error]%s,%d\n",__FILE__,__LINE__);

    return;
}

BOOLEAN devDigitalTuner_Std_set(EN_TUNER_MODE eMode)
{
    BOOLEAN bRet = TRUE;
    m_eMode = eMode;

    DBG_TUNER(printf("devDigitalTuner_Std_set,eMode=%d\n",eMode);)

    return bRet;
}

BOOLEAN devTuner_Std_set(EN_TUNER_MODE eMode, AUDIOSTANDARD_TYPE_ OtherMode)
{
    BOOLEAN bRet = TRUE;
    m_eMode = eMode;
    m_OtherMode = OtherMode;

    DBG_TUNER(printf("devTuner_Std_set, eMode=%d, OtherMode=%d\n",eMode,OtherMode);)

    return bRet;
}
#if 0
void devTunerSetFreq_ATSC(U16 u16Freq_over_freq_step_khz, EN_DEMOD_TYPE enModulation)
{
    BOOLEAN retb = TRUE;
    U32 u32Freq = 0;
    if (m_bDeviceBusy == FALSE)
    {
        retb = FALSE;
        printf("[Error]%s,%d\n",__FILE__,__LINE__);
        return;
    }

    u32Freq =(U32)(u16Freq_over_freq_step_khz)*FREQ_STEP*1000;
#if (ENABLE_TVSCAN_DEBUGINFO)
    printf("[devTunerSetFreq_ATSC] enModulation=%d, u16Freq_over_freq_step_khz=%d, u32Freq=%ld KHz\n",enModulation,u16Freq_over_freq_step_khz,u32Freq/1000);
#endif
    if(enModulation == DEMOD_TYPE_NTSC)
       retb &= ATV_SetTune(u32Freq/1000,(RFBAND)0, E_TUNER_ATV_NTSC_MODE,E_AUDIOSTANDARD_M_);
    else if(enModulation == DEMOD_TYPE_8VSB)
       retb &= DTV_SetTune((double)u32Freq/1000000.0,E_RF_CH_BAND_6MHz, E_TUNER_DTV_ATSC_MODE);
    else
       retb &= DTV_SetTune((double)u32Freq/1000000.0,E_RF_CH_BAND_6MHz, E_TUNER_DTV_QAM_US_MODE);

    if (retb == FALSE)
        printf("[Error]%s,%d\n",__FILE__,__LINE__);

    return;
}
#endif
void devTunerSetXo_Cap(U32 u8Value)
{
     api->prop->crystal_trim.xo_cap                  =    u8Value; /* (default    12) */
     if (Si2158_L1_SetProperty2(api, Si2158_CRYSTAL_TRIM_PROP_CODE) != 0)
     {
          mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_CRYSTAL_TRIM_PROP_CODE\n"));
     }

}
void devTunerSetATV_CW_Test(BOOLEAN bEnable)
{
     api->cmd->atv_cw_test.pc_lock=bEnable;
     if (Si2158_L1_SendCommand2(api, Si2158_ATV_CW_TEST_CMD_CODE) != 0)
     {
          mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_ATV_CW_TEST_CMD_CODE\n"));
     }

}
void devTunerSetPowerDown_HW(void)
{
      if(Si2158_Powerdown_HW(api)!=0)
      {
          mcSHOW_HW_MSG((" [Silabs]: devTunerSetPowerDown_HW\n"));
      }
}

int Si2158_printf(const char *format, ...)
{
    format = format;
    // printf(format);
    return 0;
}


