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

* File  : SILAB_2158.c
**********************************************************************/
/*@ </FileComment ID=1246257763274> @*/

/*@ <Include> @*/

#include "TDSY_G230D.h"
#include "drvIIC.h"
#if 0
#include "SI2158/Si2158_L1_API.h"
// #include "SI2158/Si2158_firmware_0_C_build_4.h"
#include "SI2158/Si2158_firmware_0_C_build_6.h"

/* Si2158 API Specific Includes */
#include "SI2158/Si2158_L2_API.h"               /* Include file for this code */
#include "SI2158/Si2158_firmware_0_E_build_15.h"       /* firmware compatible with Si2158-marking */
#include "SI2158/Si2158_firmware_2_0_build_x.h"
#define Si2158_BYTES_PER_LINE 8
#ifdef USING_ALIF_FILTER
#include "SI2158/write_ALIF_video_coeffs.h"   /* .h file from custom Video filter Tool output */
#endif
#ifdef USING_DLIF_FILTER
#include "SI2158/write_DLIF_video_coeffs.h"   /* .h file from custom Video filter Tool output */
#endif
#endif

#include "msAPI_FreqTableATV.h"
#include "msAPI_Tuning.h"

static MS_U8 platform_I2CRead(
    MS_U8  bus_id,
    MS_U8  i2c_slave_id,
    MS_U8* subadrptr,
    MS_U16 subadrlen,
    MS_U8* dataptr,
    MS_U16 datalen
    );

static MS_U8 platform_I2CWrite(
    MS_U8  bus_id,
    MS_U8  i2c_slave_id,
    MS_U8* subadrptr,
    MS_U16 subadrlen,
    MS_U8* dataptr,
    MS_U16 datalen
    );
static void platform_ms_delay(MS_U32);
static MS_U8 platform_gpio_control(MS_U8 high);
#include "TDSY_G230D/LGIT_Tuner_bsp.c"
#include "TDSY_G230D/LGIT_TDSY_G230D_api.c"
#define DBG_TUNER(x)   //x

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


#define C_Si2158_LO_ADDRESS           ((U8)  0xC2)
#define C_Si2158_LO_DIVIDER_STEP       ((U32) 1000)  /* Hz */
#define C_Si2158_LO_DIVIDER_STEP_ANA   ((U16)  1000)  /* Hz */
#define C_SILABS_Si2158_STR                        "SILABS_Si2158"

#define Si2158_BASE_ADDRESS 0xC2

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
} Network_Type;


static L1_Si2158_Context *api;
static MS_BOOL tuner_init = false;

BOOLEAN  m_bDeviceBusy = FALSE;

static EN_TUNER_MODE m_eMode = E_TUNER_INVALID;
static AUDIOSTANDARD_TYPE_ m_OtherMode = E_AUDIOSTANDARD_NOTSTANDARD_;

extern IF_FREQ MDrv_IFDM_GetIF(void);
void SetIfDemod(RF_CHANNEL_BANDWIDTH eBandWidth, Network_Type eNetworktype, SI_AnalogTVSystem TV_SYS);

//*--------------------------------------------------------------------------------------
//* Function Name       :   platform_I2CRead
//* Object              :
//* Input Parameters    :   MS_U8  bus_id,
//*                         MS_U8  i2c_slave_id,
//*                         MS_U8* subadrptr,
//*                         MS_U16 subadrlen,
//*                         MS_U8* dataptr,
//*                         MS_U16 datalen,
//* Output Parameters   :   MS_U8 bRet,
//*                         1:OK, 0:Fail
//*--------------------------------------------------------------------------------------
static MS_U8 platform_I2CRead(
    MS_U8  bus_id,
    MS_U8  i2c_slave_id,
    MS_U8* subadrptr,
    MS_U16 subadrlen,
    MS_U8* dataptr,
    MS_U16 datalen
    )
{
    /* Variable declarations */
    MS_U8 bRet = 1;
	UNUSED(bus_id);
    if(MDrv_IIC_ReadBytes((U16)((G230D_I2C_ADDR&0xff00)|i2c_slave_id), subadrlen, subadrptr, datalen, dataptr) == FALSE)
    {
        bRet = 0;
        printf("\nTuner_IIC read  fail\n");
    }

    return bRet;
}

//*--------------------------------------------------------------------------------------
//* Function Name       :   platform_I2CWrite
//* Object              :
//* Input Parameters    :   MS_U8  bus_id,
//*                         MS_U8  i2c_slave_id,
//*                         MS_U8* subadrptr,
//*                         MS_U16 subadrlen,
//*                         MS_U8* dataptr,
//*                         MS_U16 datalen,
//* Output Parameters   :   MS_U8 bRet,
//*                         1:OK, 0:Fail
//*--------------------------------------------------------------------------------------
static MS_U8 platform_I2CWrite(
    MS_U8  bus_id,
    MS_U8  i2c_slave_id,
    MS_U8* subadrptr,
    MS_U16 subadrlen,
    MS_U8* dataptr,
    MS_U16 datalen
    )
{
    /* Variable declarations */
    MS_U8 bRet = 1;

	UNUSED(bus_id);
    if(MDrv_IIC_WriteBytes((U16)((G230D_I2C_ADDR&0xff00)|i2c_slave_id), subadrlen, subadrptr, datalen, dataptr) == FALSE)
    {
        bRet = 0;
        printf("\nTuner_IIC read  fail\n");
    }

    return bRet;
}

//*--------------------------------------------------------------------------------------
//* Function Name       : platform_ms_delay
//* Object              :
//* Input Parameters    :   MS_U32 tms
//*
//* Output Parameters   :   void
//*--------------------------------------------------------------------------------------
static void platform_ms_delay(MS_U32 tms)
{
    /* Variable declarations */

    MsOS_DelayTask(tms);
    return;
}

//*--------------------------------------------------------------------------------------
//* Function Name       : platform_gpio_control
//* Object              :
//* Input Parameters    : MS_U8 high
//*
//* Output Parameters   : bRet
//*--------------------------------------------------------------------------------------
static MS_U8 platform_gpio_control(MS_U8 high)
{
    MS_U8 bRet = 1;
    high =  high;
/*
    mapi_gpio *gptr = mapi_gpio::GetGPIO_Dev(Tuner);

    if (gptr == NULL)
    {
        bRet = 0;
    }
    else
    {
        if (high == 0)
        {
            gptr->SetOff();
        }
        else
        {
            gptr->SetOn();
        }
    }

    if (bRet == 0)
        printf("\nTuner gpio control fail\n");
*/
    return bRet;
}

static Lgit_tuner_standard_t std_conversion(EN_TUNER_MODE eMode,MS_U8 OtherMode)
{
    Lgit_tuner_standard_t tv_sys = LGIT_TUNER_STD_ATV_SCAN;

    switch (eMode)
    {
        case E_TUNER_ATV_PAL_MODE:
        {
            switch(OtherMode)
            {
                case E_AUDIOSTANDARD_BG_:
                case E_AUDIOSTANDARD_BG_A2_:
                case E_AUDIOSTANDARD_BG_NICAM_:
                    tv_sys = LGIT_TUNER_STD_PAL_B;
                    break;
                case E_AUDIOSTANDARD_I_:
                    tv_sys = LGIT_TUNER_STD_PAL_I;
                    break;
                case E_AUDIOSTANDARD_DK_:
                case E_AUDIOSTANDARD_DK1_A2_:
                case E_AUDIOSTANDARD_DK2_A2_:
                case E_AUDIOSTANDARD_DK3_A2_:
                case E_AUDIOSTANDARD_DK_NICAM_:
                    tv_sys = LGIT_TUNER_STD_PAL_D;
                    break;
                case E_AUDIOSTANDARD_L_:
                    tv_sys = LGIT_TUNER_STD_SECAM_L;
                    break;
                case E_AUDIOSTANDARD_M_:
                case E_AUDIOSTANDARD_M_BTSC_:
                case E_AUDIOSTANDARD_M_A2_:
                case E_AUDIOSTANDARD_M_EIA_J_:
                    tv_sys = LGIT_TUNER_STD_PAL_M;
                    break;
                case E_AUDIOSTANDARD_NOTSTANDARD_:
                default:
                    tv_sys =  LGIT_TUNER_STD_ATV_SCAN;
                    break;
            }
            break;
        case E_TUNER_ATV_SECAM_L_PRIME_MODE:
            tv_sys =  LGIT_TUNER_STD_SECAM_LP;
            break;
        case E_TUNER_ATV_NTSC_MODE:
            tv_sys = LGIT_TUNER_STD_NTSC;
            break;
        case E_TUNER_DTV_ISDB_MODE:
            tv_sys = LGIT_TUNER_STD_ISDBT;
            break;
        case E_TUNER_DTV_DVB_T_MODE:
            tv_sys = LGIT_TUNER_STD_DVBT;
            break;
        case E_TUNER_DTV_DVB_C_MODE:
            tv_sys = LGIT_TUNER_STD_DVBC;
            break;
        case E_TUNER_DTV_DVB_S_MODE:
            tv_sys = LGIT_TUNER_STD_DVBS;
            break;
        case E_TUNER_DTV_DTMB_MODE:
            tv_sys = LGIT_TUNER_STD_DTMB;
            break;
        case E_TUNER_DTV_ATSC_MODE:
            tv_sys = LGIT_TUNER_STD_8VSB;
            break;
        case E_TUNER_DTV_DVB_T2_MODE:
            tv_sys = LGIT_TUNER_STD_DVBT2;
            break;
        default:
            tv_sys =  LGIT_TUNER_STD_ATV_SCAN;
            break;
        }
    }
    return tv_sys;
}

static Lgit_tuner_bandwidth_t bw_conversion(RF_CHANNEL_BANDWIDTH eBandWidth)
{
    Lgit_tuner_bandwidth_t bw = LGIT_TUNER_BW_1_7MHz;

    switch (eBandWidth)
    {
        case E_RF_CH_BAND_6MHz:
            bw = LGIT_TUNER_BW_6MHz;
            break;
        case E_RF_CH_BAND_7MHz:
            bw = LGIT_TUNER_BW_7MHz;
            break;
        case E_RF_CH_BAND_8MHz:
            bw = LGIT_TUNER_BW_8MHz;
            break;
        case E_RF_CH_BAND_INVALID:
        default:
            bw = LGIT_TUNER_BW_8MHz;
            break;
    }
    return bw;
}
U32 Si2158_GetDefaultIF(U32 Freq, SI_AnalogTVSystem TV_SYS);
#if 0
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
            ret_atv_sys = si_tv_system_invalid;
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
        case E_TUNER_ATV_PAL_MODE:
        case E_TUNER_ATV_SECAM_L_PRIME_MODE:
        case E_TUNER_ATV_NTSC_MODE:
        default:
            ret_dtv_sys = E_Network_Type_ISDBT;
            break;
    }
    return ret_dtv_sys;
}
#endif

static BOOLEAN device_tuner_G230D(void)
{
    //ADD YOU TUNER DRIVER CODE IN HERE
    BOOLEAN retb = FALSE;

    //HW reset, silab 2158 is low reset.
    // pull low
    platform_gpio_control(0);
    // 10ms delay
    platform_ms_delay(10);
    // pull high
    platform_gpio_control(1);
    // 10ms delay
    platform_ms_delay(10);

    LGIT_TDSY_G230D_Open();
    if (LGIT_TDSY_G230D_Initialize() == FALSE)
    {
        printf("[Error]%s, %d, tuner init fail.\n",__FUNCTION__,__LINE__);
        tuner_init = 0;
    }
    else
    {
        tuner_init = 1;
        retb=TRUE;
    }

    return retb;
}


static BOOLEAN Connect(void)
{
    if (m_bDeviceBusy == TRUE)
    {
        // Connect should not be called again.
        // But code flow let ATV and DTV both init.
        // (Some tuner init step at ATV and DTV are different.)
        printf("[Tuner Already Connect]%s,%d.\n",__FILE__,__LINE__);
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
#if 0
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

    eBand = eBand;

    TV_SYS = Atv_system_enum_conversion(eMode,(AUDIOSTANDARD_TYPE_)OtherMode);

    DBG_TUNER(printf ("ATV_SetTune freq = %ld; SYS = %d...........%d\n", u32FreqKHz, TV_SYS,tuner_init);)

    if(s16Finetune!=0)
    {
        u32FreqKHz -= (s16Finetune*625/10); //re-calcuate original freq w/o finetune
        //for example, current frequency is 224250KHz, if AnalogFinetune is set to +1(+62.5KHz), that means middleware will call u32FreqKHz:224313KHz(224250+63) Finetune:1
    }
    if(tuner_init)
    {
        /* do not go through SetIfdemod if same TV_SYS is used but only frequency is changed*/
        switch (TV_SYS)
        {
            case si_tv_system_bg:
                if(u32FreqKHz < 300000)
                {
                    freqHz = (u32FreqKHz * 1000) + C_Si2158_PF_TO_CF_SHIFT_B*1000;
                }
                else
                {
                    freqHz = (u32FreqKHz * 1000) + C_Si2158_PF_TO_CF_SHIFT_G*1000;
                }
                api->prop->tuner_lo_injection.band_1      = Si2158_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
                api->prop->tuner_lo_injection.band_2      = Si2158_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE;
                api->prop->tuner_lo_injection.band_3      = Si2158_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE;
                if (Si2158_L1_SetProperty2(api,Si2158_TUNER_LO_INJECTION_PROP) != 0)
                {
                        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_TUNER_LO_INJECTION_PROP\n"));
                }
                if (u32FreqKHz < 300000 && previous_video_sys != Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B )
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
                if (u32FreqKHz >= 300000 && previous_video_sys != Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_GH)
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
                printf("[Error]%s, %s, %s\n", __FILE__,__FUNCTION__,__LINE__);
                break;
        }
printf("tuner 1\n");
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
printf("tuner 2\n");
        if (freqHz < Si2158_TUNER_TUNE_FREQ_CMD_FREQ_MIN || freqHz > Si2158_TUNER_TUNE_FREQ_CMD_FREQ_MAX)
        {
            printf("[Silabs]:<= Frequency out of Range\n");
            mcSHOW_HW_MSG((" [Silabs]: <= Frequency out of Range\n"));
            return FALSE;
        }

        if (Si2158_L1_TUNER_TUNE_FREQ(api,Si2158_TUNER_TUNE_FREQ_CMD_MODE_ATV,  freqHz) != 0)
        {
            printf("[Silabs]:Error Si2158_L1_TUNER_TUNE_FREQ\n");
            mcSHOW_HW_MSG((" [Silabs]: Error Si2158_L1_TUNER_TUNE_FREQ\n"));
        }
printf("tuner 3\n");
        /* wait for TUNINT, timeout is 40ms */
        timeout = 40;
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
printf("tuner 4\n");
        /* wait for ATVINT, timeout is 150ms */
        timeout = 150;
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
printf("tuner 5\n");
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
        api->prop->tuner_lo_injection.band_1      = Si2158_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
        api->prop->tuner_lo_injection.band_2      = Si2158_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE;
        api->prop->tuner_lo_injection.band_3      = Si2158_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE;
        if (Si2158_L1_SetProperty2(api,Si2158_TUNER_LO_INJECTION_PROP) != 0)
        {
                mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_TUNER_LO_INJECTION_PROP\n"));
        }
        switch (eNetworktype)
        {
           case E_Network_Type_DVBT:
                if ( (previous_dtv_mode != Si2158_DTV_MODE_PROP_MODULATION_DVBT)
                    || (previous_agc_speed!=Si2158_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO)
                    || (eBandWidth != pre_bw)
                    )
                    SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
                break;
           case E_Network_Type_DVBT2:
                if ( (previous_dtv_mode != Si2158_DTV_MODE_PROP_MODULATION_DVBT)
                    || (previous_agc_speed!=Si2158_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_39)
                    || (eBandWidth != pre_bw)
                   )
                    SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
                break;
           case E_Network_Type_DVBC:
                if (previous_dtv_mode != Si2158_DTV_MODE_PROP_MODULATION_DVBC)
                    SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
                break;
           case E_Network_Type_ISDBT:
                if (previous_dtv_mode != Si2158_DTV_MODE_PROP_MODULATION_ISDBT)
                    SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
                break;
           case E_Network_Type_ISDBC:
                if (previous_dtv_mode != Si2158_DTV_MODE_PROP_MODULATION_ISDBC)
                    SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
                break;
           case E_Network_Type_DTMB:
                if (previous_dtv_mode != Si2158_DTV_MODE_PROP_MODULATION_DTMB)
                    SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
                break;
           case E_Network_Type_ATSC:
                if (previous_dtv_mode != Si2158_DTV_MODE_PROP_MODULATION_ATSC)
                    SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
                break;
           case E_Network_Type_Analog_T:
           case E_Network_Type_Analog_C:
           case E_Network_Type_DVBS:
           default:
                printf("[Error]%s,%s,%s\n",__FILE__,__FUNCTION__,__LINE__);
                break;
        }

        freqHz = (U32)(Freq * 1000000.0);

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
#endif
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
    p_api->prop->dtv_lif_out.amp = 17;
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
    unsigned char ret = NO_Si2158_ERROR;
    int rssi = -128;

    if ((ret=Si2158_L1_TUNER_STATUS(Si2158,Si2158_TUNER_STATUS_CMD_INTACK_CLEAR)) != 0)
    {
        mcSHOW_HW_MSG((" [Silabs]: ERROR_READING_COMMAND Si2158_TUNER_STATUS\n"));
    }
	else
	{
        rssi = (((int)(Si2158->rsp->tuner_status.rssi))<<24) >> 24;  // type conversion with arithmetic shift for sign extension
    }
    *strength_dBm = (float)rssi;
    return (float)rssi;
}

#if 0
/************************************************************************************************************************
  NAME: Si2158_GetATV_AFC_freq
  DESCRIPTION: Get ATV AFC frequency from Si2158. AFC frequency returned by Si2158 is valid once Si2158 is locked on ATV channel
  Parameter:  Pointer to Si2158 Context (I2C address)
  Returns:    AFC_freq value in Hz, although AFC frequency resolution is in kHz
************************************************************************************************************************/
U32 Si2158_GetATV_AFC_freq(U32 AFC_freqHz)
{
    int return_code;
    int AFC_freqkHz;
    U32 AFC_freq;
    return_code=0;
    AFC_freqkHz=0;
    AFC_freq=0;

    AFC_freqHz = AFC_freqHz;

    if ((return_code=Si2158_L1_ATV_STATUS(api,Si2158_ATV_STATUS_CMD_INTACK_OK))!=0) {
        mcSHOW_HW_MSG((" [Silabs]: ERROR_READING_COMMAND Si2158_ATV_STATUS\n"));
        return return_code;
    }
    AFC_freqkHz= api->rsp->atv_status.afc_freq;
    AFC_freq=(U32)(1000*AFC_freqkHz);
    return AFC_freq;
}
#endif

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

                api->prop->dtv_mode.invert_spectrum = Si2158_DTV_MODE_PROP_INVERT_SPECTRUM_INVERTED;

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
                api->prop->dtv_lif_out.amp =17;
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
                api->prop->dtv_lif_out.amp =27;//32;
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
                api->prop->dtv_lif_out.amp =14;
                if (Si2158_L1_SetProperty2(api, Si2158_DTV_LIF_OUT_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_LIF_OUT_PROP\n"));
                }
                break;
           case E_Network_Type_ISDBT:
                api->prop->dtv_mode.modulation = Si2158_DTV_MODE_PROP_MODULATION_ISDBT;
                api->prop->dtv_mode.bw = Si2158_DTV_MODE_PROP_BW_BW_6MHZ;
                api->prop->dtv_mode.invert_spectrum = Si2158_DTV_MODE_PROP_INVERT_SPECTRUM_INVERTED;
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
                api->prop->dtv_lif_out.amp = 44;
                if (Si2158_L1_SetProperty2(api, Si2158_DTV_LIF_OUT_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_LIF_OUT_PROP\n"));
                }

                api->prop->dtv_lif_freq.offset =4000;
                if (Si2158_L1_SetProperty2(api, Si2158_DTV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2158_DTV_LIF_FREQ_PROP\n"));
                }
                break;
           case E_Network_Type_ISDBC:
           case E_Network_Type_DTMB:
           case E_Network_Type_ATSC:
           case E_Network_Type_Analog_T:
           case E_Network_Type_Analog_C:
           case E_Network_Type_DVBS:
           default:
                printf("[Error]%s,%s,%s\n",__FILE__,__FUNCTION__,__LINE__);
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
            printf("[Error]%s, %s, %s\n",__FILE__,__FUNCTION__,__LINE__);
            break;
    }
    return offset;
}

//Now chakra3 code flow will call both devDigitalTuner_Init and devTunerInit.
//It will show Init tuner twice..
// ATV init..........
void devTunerInit(void)
{
    BOOLEAN bRet_Tuner = TRUE;
    BOOLEAN bRet_Connect = TRUE;


    bRet_Tuner &= device_tuner_G230D();
    bRet_Connect &= Connect();


    if((bRet_Tuner==TRUE) && (bRet_Connect==TRUE))
    {
        tuner_init = TRUE;
    }
    else if ((bRet_Tuner==TRUE) && (bRet_Connect==FALSE))
    {
        printf("Init tuner twice. %s,%d\n",__FILE__,__LINE__);  // Maybe init at DTV and ATV. Necessary code flow.
    }
    else
    {
        printf("[Error]%s,%d\n",__FILE__,__LINE__);
    }


    if (tuner_init) printf("devTunerInit OK\n");
    return;
}

// DTV init..........
void devDigitalTuner_Init(void)
{
    BOOLEAN bRet = TRUE;

    bRet &= device_tuner_G230D();
    bRet &= Connect();

    if (bRet == FALSE)
        printf("[Error]%s,%d\n",__FILE__,__LINE__);
    else
        tuner_init = TRUE;

    return;
}

void devDigitalTuner_SetFreq ( double Freq,  RF_CHANNEL_BANDWIDTH eBandWidth)
{

    DBG_TUNER(printf("[devDigitalTuner_SetFreq]Freq=%ld, eBandWidth=%d, m_eMode=%d\n",Freq*10,(U8)eBandWidth,(U8)m_eMode);)

    if (m_bDeviceBusy == FALSE)
    {
        // devDigitalTuner_Init should be called first.
        printf("[Error]%s,%d\n",__FILE__,__LINE__);
        return;
    }


    Lgit_tuner_standard_t TV_SYS = std_conversion(m_eMode, 0);
    Lgit_tuner_bandwidth_t bw    = bw_conversion(eBandWidth);

    DBG_TUNER(printf("%s, %d, Freq=%f Hz, bw=%d, mode=%d\n",__FUNCTION__,__LINE__,Freq,eBandWidth,m_eMode);)


    DBG_TUNER(printf ("Si2158_TunerSetFreq TV_SYS = %d; bw = %d\n", (MS_U16)TV_SYS,bw);)

    LGIT_TDSY_G230D_ChangeStandard(TV_SYS, bw);

    LGIT_TDSY_G230D_Tune( (MS_U32)(Freq*1000), TV_SYS, bw);

    return ;
}


void devTunerSetFreq(U32 u32Freq)
{
    IF_FREQ CurrentStandard = MDrv_IFDM_GetIF();

    if (m_bDeviceBusy == FALSE)
    {
        printf("[Error]%s,%d\n",__FILE__,__LINE__);
        return;
    }

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


    Lgit_tuner_standard_t TV_SYS = std_conversion(m_eMode,m_OtherMode);

    DBG_TUNER(printf("%s, %d, Freq=%ld Khz, mode=%d, otherMode=%d\n",__FUNCTION__,__LINE__,u32Freq,m_eMode,m_OtherMode);)

    DBG_TUNER(printf ("ATV_SetTune freq = %ld; SYS = %d...........\n", u32Freq, TV_SYS);)

    LGIT_TDSY_G230D_ChangeStandard(TV_SYS, LGIT_TUNER_BW_8MHz);

    LGIT_TDSY_G230D_Tune( u32Freq/1000, TV_SYS, LGIT_TUNER_BW_8MHz);

    return ;
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

int Si2158_printf(const char *format, ...)
{
    format = format;
     //printf(format);
    return 0;
}


