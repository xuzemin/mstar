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

* Class : device_tuner_si_2157
* File  : device_tuner_si_2157.cpp
**********************************************************************/
/*@ </FileComment ID=1246257763274> @*/

/*@ <Include> @*/

#if 0
#include <unistd.h>
#include "debug.h"
#include "mapi_i2c.h"
#include "mapi_i2c_devTable.h"
#include "mapi_interface.h"
#include "mapi_gpio.h"
#include "mapi_gpio_devTable.h"
#include "mapi_vif.h"
#include "mapi_vif_datatype.h"
#include "mapi_audio.h"
#include "mapi_utility.h"

#include "MsTypes.h"
#include "drvDMD_common.h"
#include "drvDMD_INTERN_DVBT.h"
#include "drvDMD_INTERN_DVBC.h"
#endif

#define __SILAB_2157_C__

#include "drvIIC.h"

#include "msAPI_FreqTableATV.h"
#include "msAPI_Tuning.h"
#include "MApp_GlobalVar.h"
#include "MApp_TopStateMachine.h"

#include "SILAB_2157.h"
#include "si2157/Si2157_L1_API.h"

/* Si2157 API Specific Includes */
#include "si2157/Si2157_L2_API.h"               /* Include file for this code */


//static int Si2157_printf(const char *format, ...);
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

#include "si2157/Si2157_L2_API.c"
#include "si2157/Si2157_Properties_Strings.c"
#include "si2157/Si2157_L1_Properties.c"
#include "si2157/Si2157_L1_API.c"
#include "si2157/Si2157_L1_Commands.c"
#include "si2157/Silabs_L0_Connection.c"
#include "si2157/si2157_i2c_api.c"
#include "si2157/Si2157_User_Properties.c"
   
#define DBG_TUNER(x)  // x

#define C_Si2157_LO_ADDRESS           ((U8)  0xC0)
#define SILAB_2157_I2C_ADDR (((U16)TUNER_IIC_BUS<<8)| C_Si2157_LO_ADDRESS)

#if 0
#define TN_FREQ_STEP                    E_FREQ_STEP_50KHz

#define TUNER_VHF_LOWMIN_FREQ             46250L
#define TUNER_VHF_LOWMAX_FREQ             142000L
#define TUNER_VHF_HIGHMIN_FREQ            149000L
#define TUNER_VHF_HIGHMAX_FREQ            426000L
#define TUNER_UHF_MIN_FREQ_UK             470000L
#define TUNER_UHF_MIN_FREQ                434000L
#define TUNER_UHF_MAX_FREQ                863250L

#define VIF_TUNER_TYPE                  1                   // 0: RF Tuner; 1: Silicon Tuner
#define VIF_CR_RATE_B                   0x000A5ED1 // 4.75M + 2.25M   // [21:0], CR_RATE for 7.0 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_B                 0                       // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_GH                  0x000A5ED1 // 4.25M + 2.75M       // [21:0], CR_RATE for 7.0 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_GH                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_DK                  0x000BDA13 // 5.25M + 2.75M   // [21:0], CR_RATE for 8.0 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_DK                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_I                   0x000B1C72 // 4.75M + 2.75M          // [21:0], CR_RATE for 7.5 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_I                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_L                   0x000BDA13 // 5.25M + 2.75M   // [21:0], CR_RATE for 8.0 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_L                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_LL                  0x000BDA13 // 5.25M + 2.75M  // [21:0], CR_RATE for 8.0 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_LL                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_MN                  0x0008E38E // 4.25 + 1.75M  // [21:0], CR_RATE for 6.0 MHz, HEX((xxx/43.2) * (2^22))
#define VIF_CR_INVERT_MN                0                   // Video carrier position; 0: high side; 1:low side
#endif

#if 0
#define TUNER_DTV_IQ_SWAP               1 // iq swap
#define TUNER_VIF_TAGC_ODMODE           0 // IF AGC OD MODE
#define TUNER_DVB_IF_AGC_MODE           0
#endif

// VideoIF = 7.0M
const U16 VIF_A1_A2_SOS11_SOS12_B_Stereo_A2[16]=
{
 0x03C0,0x0628,0x0418,
 0x03C7,0x0628,0x0411,
 0x0143,0x0628,0x0200,0x06B0,0x0200,
 0x03C0,0x0628,0x0200,0x0418,0x0200
};

// VideoIF = 7.0M
const U16 VIF_A1_A2_SOS11_SOS12_B_Mono_NICAM[16]=
{
 0x03C0,0x0628,0x0418,
 0x03C9,0x0628,0x040E,
 0x0143,0x0628,0x0200,0x06B0,0x0200,
 0x03C0,0x0628,0x0200,0x0418,0x0200
};

// VideoIF = 7.0M
const U16 VIF_A1_A2_SOS11_SOS12_GH_Stereo_A2[16]=
{
 0x03C0,0x0628,0x0418,
 0x03C7,0x0628,0x0411,
 0x00B9,0x0628,0x0200,0x0740,0x0200,
 0x03C0,0x0628,0x0200,0x0418,0x0200
};

// VideoIF = 7.0M
const U16 VIF_A1_A2_SOS11_SOS12_GH_Mono_NICAM[16]=
{
 0x03C0,0x0628,0x0418,
 0x03C9,0x0628,0x040E,
 0x00B9,0x0628,0x0200,0x0740,0x0200,
 0x03C0,0x0628,0x0200,0x0418,0x0200
};

// VideoIF = 8.0M
const U16 VIF_A1_A2_SOS11_SOS12_DK1_Stereo_A2[16]=
{
 0x03C0,0x0628,0x0418,
 0x03B8,0x0628,0x0421,
 0x00B9,0x0628,0x0200,0x0740,0x0200,
 0x03C0,0x0628,0x0200,0x0418,0x0200
};

// VideoIF = 8.0M
const U16 VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2[16]=
{
 0x03C0,0x0628,0x0418,
 0x03C7,0x0628,0x0411,
 0x00B9,0x0628,0x0200,0x0740,0x0200,
 0x03C0,0x0628,0x0200,0x0418,0x0200
};

// VideoIF = 8.0M
const U16 VIF_A1_A2_SOS11_SOS12_DK3_Stereo_A2[16]=
{
 0x03C0,0x0628,0x0418,
 0x03A2,0x0628,0x0437,
 0x00B9,0x0628,0x0200,0x0740,0x0200,
 0x03C0,0x0628,0x0200,0x0418,0x0200
};

// VideoIF = 8.0M
const U16 VIF_A1_A2_SOS11_SOS12_DK_Mono_NICAM[16]=
{
 0x03C0,0x0628,0x0418,
 0x03A7,0x0628,0x0432,
 0x00B9,0x0628,0x0200,0x0740,0x0200,
 0x03C0,0x0628,0x0200,0x0418,0x0200
};

// VideoIF = 7.5M
const U16 VIF_A1_A2_SOS11_SOS12_I[16]=
{
 0x03C0,0x0628,0x0418,
 0x03CE,0x0628,0x040A,
 0x00B9,0x0628,0x0200,0x0740,0x0200,
 0x03C0,0x0628,0x0200,0x0418,0x0200
};

// VideoIF = 6.0M
const U16 VIF_A1_A2_SOS11_SOS12_MN[16]=
{
 0x03C0,0x0628,0x0418,
 0x03C6,0x0628,0x0412,
 0x01C6,0x0628,0x0200,0x0627,0x0200,
 0x03C0,0x0628,0x0200,0x0418,0x0200
};

// VideoIF = 8.0M
const U16 VIF_A1_A2_SOS11_SOS12_L[16]=
{
 0x03C0,0x0628,0x0418,
 0x03A7,0x0628,0x0432,
 0x00B9,0x0628,0x0200,0x0740,0x0200,
 0x03C0,0x0628,0x0200,0x0418,0x0200
};

// VideoIF = 8.0M
const U16 VIF_A1_A2_SOS11_SOS12_LP[16]=
{
 0x03C0,0x0628,0x0418,
 0x03A7,0x0628,0x0432,
 0x00B9,0x0628,0x0200,0x0740,0x0200,
 0x03C0,0x0628,0x0200,0x0418,0x0200
};

    
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


static L1_Si2157_Context *api = NULL;
static BOOLEAN tuner_init = FALSE;
static BOOLEAN  m_bDeviceBusy = FALSE;
static EN_TUNER_MODE m_eMode = E_TUNER_DTV_DVB_T_MODE;//E_TUNER_INVALID;
static AUDIOSTANDARD_TYPE_ m_OtherMode = E_AUDIOSTANDARD_NOTSTANDARD_;

static void SetIfDemod(RF_CHANNEL_BANDWIDTH eBandWidth, Network_Type eNetworktype, SI_AnalogTVSystem TV_SYS);
static U32 Si2157_GetDefaultIF(U32 Freq, SI_AnalogTVSystem TV_SYS);
static BOOLEAN Si2157_GetRSSILevel(float *strength_dBm);
extern IF_FREQ MDrv_IFDM_GetIF(void);

   
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
    U8 bRet = 1;

    UNUSED(bus_id);
    UNUSED(i2c_slave_id);

    if(MDrv_IIC_ReadBytes(SILAB_2157_I2C_ADDR, (U8) subadrlen, subadrptr, (U16) datalen, dataptr) == false)
    {
        bRet = 0;
        printf("\nTuner_IIC read  fail\n");
    }
    else 
    {
        // printf("\nReadData-");
        bRet = 1;
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
    U8 bRet = 1;

    UNUSED(bus_id);
    UNUSED(i2c_slave_id);

    if(MDrv_IIC_WriteBytes(SILAB_2157_I2C_ADDR, (U8) subadrlen, subadrptr, (U16) datalen, dataptr) == false)
    {
        bRet = 0;
        printf("\nTuner_IIC read  fail\n");
    }
    else 
    {
        // printf("\nReadData-");
        bRet = 1;
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
    U8 bRet = 1;
    UNUSED(high);
#if 0    
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
#endif
    return bRet;

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
                        ret_atv_sys = si_tv_system_dk;
                        break;
                }
            }
            break;    
        case E_TUNER_ATV_SECAM_L_PRIME_MODE:
            ret_atv_sys = si_tv_system_lp;
            break;
//        case E_TUNER_ATV_SECAM_L_MODE:
//            ret_atv_sys = si_tv_system_l;
//            break;            
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
#if 0            
        case E_TUNER_DTV_QAM_US_MODE:
            ret_dtv_sys = E_Network_Type_QAM_US;
            break;
#endif
        case E_TUNER_ATV_PAL_MODE:   
        case E_TUNER_ATV_SECAM_L_PRIME_MODE:
        case E_TUNER_ATV_NTSC_MODE:            
        default:
            ret_dtv_sys = E_Network_Type_DVBT;
            break;
    }
    return ret_dtv_sys;
}


static BOOLEAN device_tuner_si_2157_init(void)
{
    //ADD YOU TUNER DRIVER CODE IN HERE    
    BOOLEAN retb = FALSE;

    if (tuner_init == TRUE) 
    {
        printf("Warning, init again, %s, %d\n",__FUNCTION__,__LINE__);
        return TRUE;
    }
    
    api = (L1_Si2157_Context *)malloc(sizeof(L1_Si2157_Context));
    /* Allocate rsp variable */

    //HW reset, silab 2157 is low reset.
    // pull low
    platform_gpio_control(0);
    // 10ms delay
    platform_ms_delay(10);
    // pull high
    platform_gpio_control(1);
    // 10ms delay
    platform_ms_delay(10);
    
    /* Software Init */
    Si2157_L1_API_Init(api,C_Si2157_LO_ADDRESS);

    if (Si2157_Init(api) != 0 ) {
      printf("\n");
      printf("ERROR ----------------------------------\n");
      printf("ERROR initializing the Si2157!\n");
      printf("ERROR ----------------------------------\n");
      printf("\n");

      retb = FALSE;
    }
    else
    {
      tuner_init = true;
      api->prop->atv_video_mode.video_sys = 0xff;
      api->prop->dtv_mode.modulation = 0xff;
      api->prop->dtv_agc_speed.if_agc_speed = 0xff;
      retb = TRUE;
    }
    return retb;   
}


static S16 s16Prev_finetune=0;
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
    U8 previous_video_sys = 0;

    DBG_TUNER(printf("%s, %d, Freq=%ld Khz, eBand=%d, mode=%d, otherMode=%d\n",__FUNCTION__,__LINE__,u32FreqKHz,eBand,eMode,OtherMode);)
    
    eBand = eBand;

    if (m_bDeviceBusy == FALSE)
    {
        printf("[Error]%s,%d\n",__FILE__,__LINE__);
        return FALSE;
    }

    previous_video_sys = api->prop->atv_video_mode.video_sys;

    TV_SYS = Atv_system_enum_conversion(eMode,(AUDIOSTANDARD_TYPE_)OtherMode);

    DBG_TUNER(printf ("ATV_SetTune freq = %ld; SYS = %d...........\n", u32FreqKHz, TV_SYS);)

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
                    freqHz = (u32FreqKHz * 1000) + C_Si2157_PF_TO_CF_SHIFT_B*1000;
                }
                else
                {
                    freqHz = (u32FreqKHz * 1000) + C_Si2157_PF_TO_CF_SHIFT_G*1000;
                }
                api->prop->tuner_lo_injection.band_1      = Si2157_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
                api->prop->tuner_lo_injection.band_2      = Si2157_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE;
                api->prop->tuner_lo_injection.band_3      = Si2157_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE;
                if (Si2157_L1_SetProperty2(api,Si2157_TUNER_LO_INJECTION_PROP) != 0)
                {
                        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_TUNER_LO_INJECTION_PROP\n"));
                }
                if (u32FreqKHz < 300000 && previous_video_sys != Si2157_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B )
                {
                    api->prop->atv_video_mode.video_sys=Si2157_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B;
                    api->prop->atv_lif_freq.offset = C_Si2157_IF_CENTER_B;
                    if (Si2157_L1_SetProperty2(api, Si2157_ATV_LIF_FREQ_PROP) != 0)
                    {
                        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_ATV_LIF_FREQ_PROP\n"));
                    }                     
                    SetIfDemod(E_RF_CH_BAND_8MHz, E_Network_Type_Analog_T, TV_SYS);
                    break;
                }
                if (u32FreqKHz >= 300000 && previous_video_sys != Si2157_ATV_VIDEO_MODE_PROP_VIDEO_SYS_GH)
                {
                    api->prop->atv_video_mode.video_sys=Si2157_ATV_VIDEO_MODE_PROP_VIDEO_SYS_GH;
                    api->prop->atv_lif_freq.offset = C_Si2157_IF_CENTER_GH;
                    if (Si2157_L1_SetProperty2(api, Si2157_ATV_LIF_FREQ_PROP) != 0)
                    {
                        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_ATV_LIF_FREQ_PROP\n"));
                    }
                    SetIfDemod(E_RF_CH_BAND_8MHz, E_Network_Type_Analog_T, TV_SYS);
                    break;
                }
                break;
            case si_tv_system_dk:
                freqHz = (u32FreqKHz * 1000) + C_Si2157_PF_TO_CF_SHIFT_DK*1000;
                api->prop->tuner_lo_injection.band_1      = Si2157_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
                api->prop->tuner_lo_injection.band_2      = Si2157_TUNER_LO_INJECTION_PROP_BAND_2_HIGH_SIDE;
                api->prop->tuner_lo_injection.band_3      = Si2157_TUNER_LO_INJECTION_PROP_BAND_3_HIGH_SIDE;
                if (Si2157_L1_SetProperty2(api,Si2157_TUNER_LO_INJECTION_PROP) != 0)
                {
                        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_TUNER_LO_INJECTION_PROP\n"));
                }
                if (previous_video_sys != Si2157_ATV_VIDEO_MODE_PROP_VIDEO_SYS_DK)
                {
                    SetIfDemod(E_RF_CH_BAND_8MHz, E_Network_Type_Analog_T, TV_SYS);
                }
                break;
            case si_tv_system_i:
                freqHz = (u32FreqKHz * 1000) + C_Si2157_PF_TO_CF_SHIFT_I*1000;
                api->prop->tuner_lo_injection.band_1      = Si2157_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
                api->prop->tuner_lo_injection.band_2      = Si2157_TUNER_LO_INJECTION_PROP_BAND_2_HIGH_SIDE;
                api->prop->tuner_lo_injection.band_3      = Si2157_TUNER_LO_INJECTION_PROP_BAND_3_HIGH_SIDE;
                if (Si2157_L1_SetProperty2(api,Si2157_TUNER_LO_INJECTION_PROP) != 0)
                {
                        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_TUNER_LO_INJECTION_PROP\n"));
                }
                if (previous_video_sys != Si2157_ATV_VIDEO_MODE_PROP_VIDEO_SYS_I)
                {
                    SetIfDemod(E_RF_CH_BAND_8MHz, E_Network_Type_Analog_T, TV_SYS);
                }
                break;
            case si_tv_system_m:
                freqHz = (u32FreqKHz * 1000) + C_Si2157_PF_TO_CF_SHIFT_M*1000;
                api->prop->tuner_lo_injection.band_1      = Si2157_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
                api->prop->tuner_lo_injection.band_2      = Si2157_TUNER_LO_INJECTION_PROP_BAND_2_HIGH_SIDE;
                api->prop->tuner_lo_injection.band_3      = Si2157_TUNER_LO_INJECTION_PROP_BAND_3_HIGH_SIDE;
                if (Si2157_L1_SetProperty2(api,Si2157_TUNER_LO_INJECTION_PROP) != 0)
                {
                        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_TUNER_LO_INJECTION_PROP\n"));
                }
                if (previous_video_sys != Si2157_ATV_VIDEO_MODE_PROP_VIDEO_SYS_M)
                {
                    SetIfDemod(E_RF_CH_BAND_8MHz, E_Network_Type_Analog_T, TV_SYS);
                }
                break;
            case si_tv_system_l:
                freqHz = (u32FreqKHz * 1000) + C_Si2157_PF_TO_CF_SHIFT_L*1000;
                api->prop->tuner_lo_injection.band_1      = Si2157_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
                api->prop->tuner_lo_injection.band_2      = Si2157_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE;
                api->prop->tuner_lo_injection.band_3      = Si2157_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE;
                if (Si2157_L1_SetProperty2(api,Si2157_TUNER_LO_INJECTION_PROP) != 0)
                {
                        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_TUNER_LO_INJECTION_PROP\n"));
                }
                if (previous_video_sys != Si2157_ATV_VIDEO_MODE_PROP_VIDEO_SYS_L)
                {
                    SetIfDemod(E_RF_CH_BAND_8MHz, E_Network_Type_Analog_T, TV_SYS);
                }
                break;
            case si_tv_system_lp:
                freqHz = (u32FreqKHz * 1000) - C_Si2157_PF_TO_CF_SHIFT_L1*1000;
                api->prop->tuner_lo_injection.band_1      = Si2157_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
                api->prop->tuner_lo_injection.band_2      = Si2157_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE;
                api->prop->tuner_lo_injection.band_3      = Si2157_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE;
                if (Si2157_L1_SetProperty2(api,Si2157_TUNER_LO_INJECTION_PROP) != 0)
                {
                        mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_TUNER_LO_INJECTION_PROP\n"));
                }
                if (previous_video_sys != Si2157_ATV_VIDEO_MODE_PROP_VIDEO_SYS_LP)
                {
                    SetIfDemod(E_RF_CH_BAND_8MHz, E_Network_Type_Analog_T, TV_SYS);
                }
                break;
            case si_tv_system_invalid:
            default:                
                printf("[Error]%s, %s, %d\n", __FILE__,__FUNCTION__,__LINE__);
                break;
        }

        if(s16Finetune!=0)
        {
            freq_offset= (int) (s16Finetune*625/10);// 1 FinetuneStep is 62.5KHz
            api->prop->atv_lif_freq.offset = (unsigned int)(freq_offset+Si2157_GetDefaultIF(u32FreqKHz, TV_SYS));
            if (Si2157_L1_SetProperty2(api, Si2157_ATV_LIF_FREQ_PROP) != 0)
            {
                mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_ATV_LIF_FREQ_PROP\n"));
            }
        }
        else
        {
            if(s16Prev_finetune!=0)  // current finetune=0, previous finetune!=0, restore original lif_freq_offset
            {
                api->prop->atv_lif_freq.offset = Si2157_GetDefaultIF(u32FreqKHz, TV_SYS);
                if (Si2157_L1_SetProperty2(api, Si2157_ATV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_ATV_LIF_FREQ_PROP\n"));
                }
            }
        }
        s16Prev_finetune = s16Finetune;

        if (freqHz < Si2157_TUNER_TUNE_FREQ_CMD_FREQ_MIN || freqHz > Si2157_TUNER_TUNE_FREQ_CMD_FREQ_MAX)
        {
            printf("[Silabs]:<= Frequency out of Range\n");
            mcSHOW_HW_MSG((" [Silabs]: <= Frequency out of Range\n"));
            return FALSE;
        }
            
        if (Si2157_L1_TUNER_TUNE_FREQ(api,Si2157_TUNER_TUNE_FREQ_CMD_MODE_ATV,  freqHz) != 0)
        {
            printf("[Silabs]:Error Si2157_L1_TUNER_TUNE_FREQ\n");
            mcSHOW_HW_MSG((" [Silabs]: Error Si2157_L1_TUNER_TUNE_FREQ\n"));
        }

        /* wait for TUNINT, timeout is 40ms */
        timeout = 40;
        start_time = MsOS_GetSystemTime();
        while( MsOS_Timer_DiffTimeFromNow(start_time) < timeout )
        {
            if (Si2157_L1_CheckStatus(api) != 0)
                return FALSE;
            if (api->status->tunint)
            {
                DBG_TUNER(printf("!!!!!!!!!!!!!LOCK..................................\n");)
                retb = TRUE;
                break;
            }
        }
        /* wait for ATVINT, timeout is 150ms */
        timeout = 150;
        start_time = MsOS_GetSystemTime();
        while( MsOS_Timer_DiffTimeFromNow(start_time) < timeout )
        {
            if (Si2157_L1_CheckStatus(api) != 0)
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
{
    BOOLEAN retb = FALSE;
    U32 freqHz = 0;
    int count=0;
    U32 start_time = 0;
    U32 timeout = 0;
    Network_Type eNetworktype = E_Network_Type_DVBT;
    static RF_CHANNEL_BANDWIDTH pre_bw = E_RF_CH_BAND_INVALID;
    unsigned char previous_dtv_mode = 0;
    unsigned char previous_agc_speed = 0;


    DBG_TUNER(printf("%s, %d, Freq=%f Hz, bw=%d, mode=%d\n",__FUNCTION__,__LINE__,Freq,eBandWidth,eMode);)

    eNetworktype = Dtv_system_enum_conversion(eMode);

    if (m_bDeviceBusy == FALSE)
    {
        printf("[Error]%s,%d\n",__FILE__,__LINE__);
        return FALSE;
    }
    
    previous_dtv_mode=api->prop->dtv_mode.modulation;
    previous_agc_speed=api->prop->dtv_agc_speed.if_agc_speed;

    DBG_TUNER(printf ("Si2157_TunerSetFreq freq = %d; Band = %d Network = %d\n", (U16)Freq,eBandWidth, eNetworktype);)

    if(tuner_init)
    {
        api->prop->tuner_lo_injection.band_1      = Si2157_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
        api->prop->tuner_lo_injection.band_2      = Si2157_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE;
        api->prop->tuner_lo_injection.band_3      = Si2157_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE;
        if (Si2157_L1_SetProperty2(api,Si2157_TUNER_LO_INJECTION_PROP) != 0)
        {
                mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_TUNER_LO_INJECTION_PROP\n"));
        }
        switch (eNetworktype)
        {
           case E_Network_Type_DVBT:
                if ( (previous_dtv_mode != Si2157_DTV_MODE_PROP_MODULATION_DVBT)
                    || (previous_agc_speed!=Si2157_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO)
                    || (eBandWidth != pre_bw)
                    )
                    SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
                break;                
           case E_Network_Type_DVBT2:
                if ( (previous_dtv_mode != Si2157_DTV_MODE_PROP_MODULATION_DVBT)
                    || (previous_agc_speed!=Si2157_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_39)
                    || (eBandWidth != pre_bw)
                   )
                    SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
                break;
           case E_Network_Type_DVBC:
                if (previous_dtv_mode != Si2157_DTV_MODE_PROP_MODULATION_DVBC)
                    SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
                break;
           case E_Network_Type_ISDBT:
                if (previous_dtv_mode != Si2157_DTV_MODE_PROP_MODULATION_ISDBT)
                    SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
                break;             
           case E_Network_Type_ISDBC:
                if (previous_dtv_mode != Si2157_DTV_MODE_PROP_MODULATION_ISDBC)
                    SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
                break;       
           case E_Network_Type_DTMB:  
                if (previous_dtv_mode != Si2157_DTV_MODE_PROP_MODULATION_DTMB)
                    SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
                break;   
           case E_Network_Type_ATSC:
                if (previous_dtv_mode != Si2157_DTV_MODE_PROP_MODULATION_ATSC)
                    SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
                break;            
           case E_Network_Type_QAM_US:
                if (previous_dtv_mode != Si2157_DTV_MODE_PROP_MODULATION_QAM_US)
                    SetIfDemod(eBandWidth, eNetworktype, si_tv_system_invalid);
                break;
           case E_Network_Type_Analog_T:
           case E_Network_Type_Analog_C:
           case E_Network_Type_DVBS:   
           default:
                printf("[Error]%s,%s,%d\n",__FILE__,__FUNCTION__,__LINE__);
                break;
        }

        if (eMode == E_TUNER_DTV_ATSC_MODE)
            freqHz = (U32)(Freq * 1000.0);
        else
            freqHz = (U32)(Freq * 1000000.0);

        if (freqHz < Si2157_TUNER_TUNE_FREQ_CMD_FREQ_MIN || freqHz > Si2157_TUNER_TUNE_FREQ_CMD_FREQ_MAX)
        {
            printf("[Silabs]:<= Frequency out of Range\n");
            mcSHOW_HW_MSG((" [Silabs]: <= Frequency out of Range\n"));
            return FALSE;
        }

        if (Si2157_L1_TUNER_TUNE_FREQ(api,Si2157_TUNER_TUNE_FREQ_CMD_MODE_DTV,  freqHz) != 0)
        {
            printf("[Silabs]:Error Si2157_L1_TUNER_TUNE_FREQ\n");
            mcSHOW_HW_MSG((" [Silabs]: Error Si2157_L1_TUNER_TUNE_FREQ\n"));
            return FALSE;
        }

        /* wait for TUNINT, timeout is 40ms */
        timeout = 140;
        start_time = MsOS_GetSystemTime();
        while( MsOS_Timer_DiffTimeFromNow(start_time) < timeout )
        {
            if (Si2157_L1_CheckStatus(api) != 0)
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
        while( MsOS_Timer_DiffTimeFromNow(start_time) < timeout )
        {
            if (Si2157_L1_CheckStatus(api) != 0)
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
BOOLEAN ExtendCommand(U8 u8SubCmd, U32 u32Param1, U32 u32Param2, void* pvoidParam3)
{

    DBG_TUNER(printf("%s, %d, u8SubCmd=%d, u32Param1=%ld, u32Param2=%ld\n",__FUNCTION__,__LINE__,u8SubCmd,u32Param1,u32Param2);)

    switch(u8SubCmd)
    {
        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_FREQ_STEP:
        {
            EN_FREQ_STEP *eFreqStep = (EN_FREQ_STEP*)pvoidParam3;
            *eFreqStep = TN_FREQ_STEP;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_IF_FREQ:
        {
            U16 *u16IFFreq = (U16 *)pvoidParam3;
            *u16IFFreq = C_Si2157_IF_CENTER_B;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_L_PRIME_IF_FREQ:
        {
            U16 *u16IFFreq = (U16 *)pvoidParam3;
            *u16IFFreq = C_Si2157_IF_CENTER_L1;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_VHF_LOWMIN_FREQ:
        {
            U32 *u32Freq = (U32 *)pvoidParam3;
            *u32Freq = TUNER_VHF_LOWMIN_FREQ;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_VHF_LOWMAX_FREQ:
        {
            U32 *u32Freq = (U32 *)pvoidParam3;
            *u32Freq = TUNER_VHF_LOWMAX_FREQ;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_VHF_HIGHMIN_FREQ:
        {
            U32 *u32Freq = (U32 *)pvoidParam3;
            *u32Freq = TUNER_VHF_HIGHMIN_FREQ;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_VHF_HIGHMAX_FREQ:
        {
            U32 *u32Freq = (U32 *)pvoidParam3;
            *u32Freq = TUNER_VHF_HIGHMAX_FREQ;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_UHF_MIN_FREQ:
        {
            U32 *u32Freq = (U32 *)pvoidParam3;
            *u32Freq = TUNER_UHF_MIN_FREQ;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_UHF_MAX_FREQ:
        {
            U32 *u32Freq = (U32 *)pvoidParam3;
            *u32Freq = TUNER_UHF_MAX_FREQ;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_VIF_TUNER_TYPE:
        {
            U8 *u8VifTunerType = (U8 *)pvoidParam3;
            *u8VifTunerType = VIF_TUNER_TYPE;
        }
            break;
        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_VIF_PARA:
        {
            mapi_vif_datatype::stVIFInitialIn *p_stVIFInitialIn = (mapi_vif_datatype::stVIFInitialIn *)pvoidParam3;

            p_stVIFInitialIn->VifCrRate_B = VIF_CR_RATE_B;
            p_stVIFInitialIn->VifCrInvert_B = VIF_CR_INVERT_B;
            p_stVIFInitialIn->VifCrRate_GH = VIF_CR_RATE_GH;
            p_stVIFInitialIn->VifCrInvert_GH = VIF_CR_INVERT_GH;
            p_stVIFInitialIn->VifCrRate_DK = VIF_CR_RATE_DK;
            p_stVIFInitialIn->VifCrInvert_DK = VIF_CR_INVERT_DK;
            p_stVIFInitialIn->VifCrRate_I = VIF_CR_RATE_I;
            p_stVIFInitialIn->VifCrInvert_I = VIF_CR_INVERT_I;
            p_stVIFInitialIn->VifCrRate_L = VIF_CR_RATE_L;
            p_stVIFInitialIn->VifCrInvert_L = VIF_CR_INVERT_L;
            p_stVIFInitialIn->VifCrRate_LL = VIF_CR_RATE_LL;
            p_stVIFInitialIn->VifCrInvert_LL = VIF_CR_INVERT_LL;
            p_stVIFInitialIn->VifCrRate_MN = VIF_CR_RATE_MN;
            p_stVIFInitialIn->VifCrInvert_MN = VIF_CR_INVERT_MN;
        }
            break;
        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_VIF_NOTCH_SOSFILTER:
        {
            U16 *pu16_vif_notch_coef = NULL;
            U16 *pu16_list = (U16*)pvoidParam3;
            U8 indx = 0;
            
            switch((mapi_vif_datatype::EN_VIF_SOUND_SYSTEM)u32Param1)
            {
                case mapi_vif_datatype::E_VIF_SOUND_B_STEREO_A2:                    
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_B_Stereo_A2;
                    break;
                    
                case mapi_vif_datatype::E_VIF_SOUND_B_MONO_NICAM:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_B_Mono_NICAM;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_GH_STEREO_A2:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_GH_Stereo_A2;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_GH_MONO_NICAM:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_GH_Mono_NICAM;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_I:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_I;
                    break;
                case mapi_vif_datatype::E_VIF_SOUND_DK1_STEREO_A2:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_DK1_Stereo_A2;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_DK2_STEREO_A2:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_DK3_STEREO_A2:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_DK3_Stereo_A2;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_DK_MONO_NICAM:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_DK_Mono_NICAM;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_L:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_L;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_LL:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_LP;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_MN:
                    pu16_vif_notch_coef = VIF_A1_A2_SOS11_SOS12_MN;
                    break;
                default:
                    printf("Error:%s(),%d\n",__func__,__LINE__);
                    return FALSE;
                    break;
            }
            
            if (pu16_vif_notch_coef == NULL) return FALSE;

            for (indx = 0;indx < 16;indx++)
            {
                *(pu16_list+indx) = *(pu16_vif_notch_coef+indx);
            }
              
        }
            break;          
        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_DTV_IF_FREQ:
        {
            switch (u32Param1) // demod mode
            {
                case E_TUNER_DTV_DVB_T2_MODE:
                    switch(u32Param2) // bandwidth
                    {
                        case E_RF_CH_BAND_6MHz:
                            *((U32 *)pvoidParam3)=C_Si2157_IF_FREQUENCY;
                            break;
                        case E_RF_CH_BAND_7MHz:
                            *((U32 *)pvoidParam3)=C_Si2157_IF_FREQUENCY;
                            break;
                        case E_RF_CH_BAND_8MHz:
                            *((U32 *)pvoidParam3)=C_Si2157_IF_FREQUENCY;
                            break;
                        default:
                            printf("Error:%s(),%d\n",__func__,__LINE__);
                            return FALSE;
                            break;
                    }
                    break;
                case E_TUNER_DTV_DVB_T_MODE:
                    switch(u32Param2) // bandwidth
                    {
                        case E_RF_CH_BAND_6MHz:
                            *((U32 *)pvoidParam3)=C_Si2157_IF_FREQUENCY;
                            break;
                        case E_RF_CH_BAND_7MHz:
                            *((U32 *)pvoidParam3)=C_Si2157_IF_FREQUENCY;
                            break;
                        case E_RF_CH_BAND_8MHz:
                            *((U32 *)pvoidParam3)=C_Si2157_IF_FREQUENCY;
                            break;
                        default:
                            printf("Error:%s(),%d\n",__func__,__LINE__);
                            return FALSE;
                            break;
                    }
                    break;
                case E_TUNER_DTV_DVB_C_MODE:
                    switch(u32Param2)
                    {
                        case E_RF_CH_BAND_6MHz:
                        case E_RF_CH_BAND_7MHz:
                        case E_RF_CH_BAND_8MHz:
                            *((U32 *)pvoidParam3)=C_Si2157_IF_FREQUENCY;
                            break;
                        default:
                            printf("Error:%s(),%d\n",__func__,__LINE__);
                            return FALSE;
                            break;
                    }
                    break;
                case E_TUNER_DTV_ATSC_MODE:
                case E_TUNER_DTV_DTMB_MODE:
                case E_TUNER_DTV_ISDB_MODE:                    
                    *((U32 *)pvoidParam3)=C_Si2157_IF_FREQUENCY;
                    break;
                default:
                    printf("Error:%s(),%d\n",__func__,__LINE__);
                    return FALSE;
                    break;
            }
        }
            break;
        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_IQ_SWAP:
        {
            U8 *u8IqSwap = (U8 *)pvoidParam3;
            *u8IqSwap = TUNER_DTV_IQ_SWAP;
            if ( u32Param1 )
            {
                *u8IqSwap ^= 0x01;
            }
        }
            break;
        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_RF_TABLE:
        {
            (*(DMD_SSI_TABLE **)pvoidParam3)=NULL; // if not used, should return NULL;
            return FALSE;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_RF_LEVEL:
        {
            float ssi_dbm = 0.0;
            Si2157_GetRSSILevel(&ssi_dbm); 
            *((float *)pvoidParam3) = ssi_dbm;
            return TRUE;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_DEMOD_CONFIG:
        {

            switch (u32Param1) // demod mode
            {
                case E_TUNER_DTV_DVB_T_MODE:
                    *((U8 **)pvoidParam3)=NULL;
                    break;
                case E_TUNER_DTV_DVB_C_MODE:
                    *((U8 **)pvoidParam3)=NULL;
                    break;
                case E_TUNER_ATV_PAL_MODE:
                case E_TUNER_ATV_SECAM_L_PRIME_MODE:
                case E_TUNER_ATV_NTSC_MODE:
                {
                    U32 *u32AgcOdMode = (U32 *)pvoidParam3;
                    *u32AgcOdMode = TUNER_VIF_TAGC_ODMODE;
                }
                    break;
                case E_TUNER_DTV_DVB_T2_MODE:
                {
                    U8 *u8if_AgcMode = (U8 *)pvoidParam3;
                    *u8if_AgcMode = TUNER_DVB_IF_AGC_MODE;
                }
                  break;
                default:
                    printf("Error:%s(),%d\n",__func__,__LINE__);
                    return FALSE;
                    break;
            }
        }
            break;
        default:
            UNUSED(u8SubCmd);
            UNUSED(u32Param1);
            UNUSED(u32Param2);
            UNUSED(pvoidParam3);
            return FALSE;
            break;
    }

    return TRUE;
}
#endif

BOOLEAN device_tuner_si_2157(void)
{
    m_bDeviceBusy = FALSE;
    if (device_tuner_si_2157_init() == FALSE)
    {
        printf("[Error]%s, %d, tuner init fail.\n",__FUNCTION__,__LINE__);
        return FALSE;
    }
    else
        m_bDeviceBusy = TRUE;

    return TRUE;
}

static BOOLEAN Connect(void)
{
    DBG_TUNER(printf("device_tuner_si_2157: Connect\n");)
    if (m_bDeviceBusy == TRUE)
        return FALSE;

    m_bDeviceBusy = TRUE;

    return TRUE;
}
#if 0
static BOOLEAN Disconnect()
{
    DBG_TUNER(printf("device_tuner_si_2157: Disconnect\n");)

    // m_bDeviceBusy = FALSE;

    return TRUE;
}
#endif
// ATV init..........
void devTunerInit(void)
{
    BOOLEAN bRet = TRUE;
    if(tuner_init == TRUE)
    {
       return;
    }
    bRet &= device_tuner_si_2157();
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
    bRet &= device_tuner_si_2157();
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


/************************************************************************************************************************
  NAME: Si2157_GetRSSILevel
  DESCRIPTION: Get RSSI from Si2157. RSSI returned by Si2157 is defined with a CW signal to prevent to make assumptions about the analog/digital content.
  For DVB-T, input power level (dBm)=RSSI -6dB
  Parameter:  Pointer to Si2157 Context (I2C address)
  Returns:    RSSI value
************************************************************************************************************************/
static BOOLEAN Si2157_GetRSSILevel(float *strength_dBm)
{
    int return_code = 0;
    if ((return_code=Si2157_L1_TUNER_STATUS(api,Si2157_TUNER_STATUS_CMD_INTACK_CLEAR))!=0) {
        mcSHOW_HW_MSG((" [Silabs]: ERROR_READING_COMMAND Si2157_TUNER_STATUS\n"));
        return return_code;
    }
    *strength_dBm=(float) api->rsp->tuner_status.rssi;
    return TRUE;
}

/************************************************************************************************************************
  NAME: Si2157_GetATV_AFC_freq
  DESCRIPTION: Get ATV AFC frequency from Si2157. AFC frequency returned by Si2157 is valid once Si2157 is locked on ATV channel 
  Parameter:  Pointer to Si2157 Context (I2C address)
  Returns:    AFC_freq value in Hz, although AFC frequency resolution is in kHz
************************************************************************************************************************/
BOOLEAN Si2157_GetATV_AFC_freq(int* AFC_freqHz)
{
    int return_code = 0;

    if ((return_code=Si2157_L1_ATV_STATUS(api,Si2157_ATV_STATUS_CMD_INTACK_OK))!=0) {
        mcSHOW_HW_MSG((" [Silabs]: ERROR_READING_COMMAND Si2157_ATV_STATUS\n"));
        printf("[Error]%s, %d\n",__FILE__,__LINE__);
        return FALSE;
    }
    *AFC_freqHz= 1000*api->rsp->atv_status.afc_freq;

    DBG_TUNER(printf("%s, %d, AFC=%ld Hz\n",*AFC_freqHz);)

    return TRUE;
}

// return dbm value, 0dBm~-98dBm
BOOLEAN mdev_GetSignalStrength(float* f_strength)
{    
    return Si2157_GetRSSILevel(f_strength);
}

/* Setup properties to switch standards. */
static void SetIfDemod(RF_CHANNEL_BANDWIDTH eBandWidth, Network_Type eNetworktype, SI_AnalogTVSystem TV_SYS)
{
    // set a global here to save the video standard,  because it's not always available from the caller.
    if(TV_SYS == si_tv_system_invalid)
    {
        switch (eNetworktype)
        {
           case E_Network_Type_DVBT:
                api->prop->dtv_mode.modulation = Si2157_DTV_MODE_PROP_MODULATION_DVBT;
                if(eBandWidth == E_RF_CH_BAND_6MHz)
                    api->prop->dtv_mode.bw = Si2157_DTV_MODE_PROP_BW_BW_6MHZ;
                else if (eBandWidth == E_RF_CH_BAND_7MHz)
                    api->prop->dtv_mode.bw = Si2157_DTV_MODE_PROP_BW_BW_7MHZ;
                else
                    api->prop->dtv_mode.bw = Si2157_DTV_MODE_PROP_BW_BW_8MHZ;

                api->prop->dtv_mode.invert_spectrum = Si2157_DTV_MODE_PROP_INVERT_SPECTRUM_INVERTED;

                if (Si2157_L1_SetProperty2(api, Si2157_DTV_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_MODE_PROP\n"));
                }
                api->prop->dtv_agc_speed.if_agc_speed = Si2157_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
                api->prop->dtv_agc_speed.agc_decim = Si2157_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_AGC_SPEED_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_AGC_SPEED_PROP\n"));
                }
                api->prop->dtv_initial_agc_speed_period.period = 0;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_INITIAL_AGC_SPEED_PERIOD_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_INITIAL_AGC_SPEED_PERIOD_PROP\n"));
                }
                /* AMP=17 to get IF_AGC=1.24Vrms in DVB-T when AMP is controlled by demod AGC (DTV_AGC_SOURCE=DLIF_AGC_3DB) */
                api->prop->dtv_lif_out.amp =27;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_LIF_OUT_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_LIF_OUT_PROP\n"));
                }
                api->prop->dtv_lif_freq.offset =C_Si2157_IF_FREQUENCY;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_LIF_FREQ_PROP\n"));
                }
                break;
           case E_Network_Type_DVBT2:
                api->prop->dtv_mode.modulation = Si2157_DTV_MODE_PROP_MODULATION_DVBT;
                if(eBandWidth == E_RF_CH_BAND_8MHz)
                    api->prop->dtv_mode.bw = Si2157_DTV_MODE_PROP_BW_BW_8MHZ;
                else if (eBandWidth == E_RF_CH_BAND_7MHz)
                    api->prop->dtv_mode.bw = Si2157_DTV_MODE_PROP_BW_BW_7MHZ;
                else
                    api->prop->dtv_mode.bw = Si2157_DTV_MODE_PROP_BW_BW_6MHZ;
                api->prop->dtv_mode.invert_spectrum = Si2157_DTV_MODE_PROP_INVERT_SPECTRUM_INVERTED;

                if (Si2157_L1_SetProperty2(api, Si2157_DTV_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_MODE_PROP\n"));
                }
                api->prop->dtv_agc_speed.if_agc_speed = Si2157_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_39;
                api->prop->dtv_agc_speed.agc_decim = Si2157_DTV_AGC_SPEED_PROP_AGC_DECIM_4;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_AGC_SPEED_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_AGC_SPEED_PROP\n"));
                }
                api->prop->dtv_initial_agc_speed_period.period = 210;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_INITIAL_AGC_SPEED_PERIOD_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_INITIAL_AGC_SPEED_PERIOD_PROP\n"));
                }
                /* AMP=32 to get IF_AGC=1.24Vrms in DVB-T2 when AMP is controlled by demod AGC (DTV_AGC_SOURCE=DLIF_AGC_3DB) */
                api->prop->dtv_lif_out.amp =32;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_LIF_OUT_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_LIF_OUT_PROP\n"));
                }
                api->prop->dtv_lif_freq.offset =C_Si2157_IF_FREQUENCY;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_LIF_FREQ_PROP\n"));
                }
                break;
           case E_Network_Type_DVBC:
                api->prop->dtv_mode.modulation = Si2157_DTV_MODE_PROP_MODULATION_DVBC;
                api->prop->dtv_mode.bw = Si2157_DTV_MODE_PROP_BW_BW_8MHZ;
                api->prop->dtv_mode.invert_spectrum = Si2157_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_INVERTED;

                if (Si2157_L1_SetProperty2(api, Si2157_DTV_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_MODE_PROP\n"));
                }
                api->prop->dtv_agc_speed.if_agc_speed = Si2157_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
                api->prop->dtv_agc_speed.agc_decim = Si2157_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_AGC_SPEED_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_AGC_SPEED_PROP\n"));
                }
                api->prop->dtv_initial_agc_speed_period.period = 0;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_INITIAL_AGC_SPEED_PERIOD_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_INITIAL_AGC_SPEED_PERIOD_PROP\n"));
                }
                /* AMP=14 to get IF_AGC=1.20Vrms in DVB-C when AMP is controlled by demod AGC (DTV_AGC_SOURCE=DLIF_AGC_3DB) */
                api->prop->dtv_lif_out.amp =27;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_LIF_OUT_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_LIF_OUT_PROP\n"));
                }
                api->prop->dtv_lif_freq.offset =C_Si2157_IF_FREQUENCY;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_LIF_FREQ_PROP\n"));
                }
                break;
           case E_Network_Type_ISDBT:
                api->prop->dtv_mode.modulation = Si2157_DTV_MODE_PROP_MODULATION_ISDBT;
                api->prop->dtv_mode.bw = Si2157_DTV_MODE_PROP_BW_BW_6MHZ;
                api->prop->dtv_mode.invert_spectrum = Si2157_DTV_MODE_PROP_INVERT_SPECTRUM_INVERTED;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_MODE_PROP\n"));
                }
                api->prop->dtv_agc_speed.if_agc_speed = Si2157_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
                api->prop->dtv_agc_speed.agc_decim = Si2157_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_AGC_SPEED_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_AGC_SPEED_PROP\n"));
                }
                api->prop->dtv_initial_agc_speed_period.period = 0;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_INITIAL_AGC_SPEED_PERIOD_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_INITIAL_AGC_SPEED_PERIOD_PROP\n"));
                }
                /* AMP=55 to get IF_AGC 1.0v in MSB1400 on 149B-C01A when AMP is controlled by demod AGC (DTV_AGC_SOURCE=DLIF_AGC_3DB) */
                api->prop->dtv_lif_out.amp = 44;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_LIF_OUT_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_LIF_OUT_PROP\n"));
                }
                api->prop->dtv_lif_freq.offset =C_Si2157_IF_FREQUENCY;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_LIF_FREQ_PROP\n"));
                }
                break;   
           case E_Network_Type_ATSC:
                api->prop->dtv_mode.modulation = Si2157_DTV_MODE_PROP_MODULATION_ATSC;
                api->prop->dtv_mode.bw = Si2157_DTV_MODE_PROP_BW_BW_6MHZ;
                api->prop->dtv_mode.invert_spectrum = Si2157_DTV_MODE_PROP_INVERT_SPECTRUM_NORMAL;

                if (Si2157_L1_SetProperty2(api, Si2157_DTV_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_MODE_PROP\n"));
                }
                api->prop->dtv_agc_speed.if_agc_speed = Si2157_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
                api->prop->dtv_agc_speed.agc_decim = Si2157_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_AGC_SPEED_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_AGC_SPEED_PROP\n"));
                }
                api->prop->dtv_initial_agc_speed_period.period = 0;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_INITIAL_AGC_SPEED_PERIOD_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_INITIAL_AGC_SPEED_PERIOD_PROP\n"));
                }
                /* AMP=17 to get IF_AGC=1.24Vrms in DVB-T when AMP is controlled by demod AGC (DTV_AGC_SOURCE=DLIF_AGC_3DB) */
                api->prop->dtv_lif_out.amp =27;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_LIF_OUT_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_LIF_OUT_PROP\n"));
                }
                api->prop->dtv_lif_freq.offset = C_Si2157_IF_FREQUENCY;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_LIF_FREQ_PROP\n"));
                }
                 api->prop->tuner_return_loss.mode = Si2157_TUNER_RETURN_LOSS_PROP_MODE_TERRESTRIAL;
                 if (Si2157_L1_SetProperty2(api, Si2157_TUNER_RETURN_LOSS_PROP_CODE) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_TUNER_RETURN_LOSS_PROP_CODE\n"));
                }

                api->prop->dtv_pga_limits.max = 56;
                api->prop->dtv_pga_limits.min = 24;
                if (Si2157_L1_SetProperty2(api,Si2157_DTV_PGA_LIMITS_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_PGA_LIMITS_PROP\n"));
                }

                break;
           case E_Network_Type_QAM_US:
                api->prop->dtv_mode.modulation = Si2157_DTV_MODE_PROP_MODULATION_QAM_US;
                api->prop->dtv_mode.bw = Si2157_DTV_MODE_PROP_BW_BW_6MHZ;
                api->prop->dtv_mode.invert_spectrum = Si2157_DTV_MODE_PROP_INVERT_SPECTRUM_NORMAL;

                if (Si2157_L1_SetProperty2(api, Si2157_DTV_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_MODE_PROP\n"));
                }
                api->prop->dtv_agc_speed.if_agc_speed = Si2157_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
                api->prop->dtv_agc_speed.agc_decim = Si2157_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_AGC_SPEED_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_AGC_SPEED_PROP\n"));
                }
                api->prop->dtv_initial_agc_speed_period.period = 0;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_INITIAL_AGC_SPEED_PERIOD_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_INITIAL_AGC_SPEED_PERIOD_PROP\n"));
                }
                /* AMP=17 to get IF_AGC=1.24Vrms in DVB-T when AMP is controlled by demod AGC (DTV_AGC_SOURCE=DLIF_AGC_3DB) */
                api->prop->dtv_lif_out.amp =27;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_LIF_OUT_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_LIF_OUT_PROP\n"));
                }
                api->prop->dtv_lif_freq.offset = C_Si2157_IF_FREQUENCY;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_LIF_FREQ_PROP\n"));
                }

                api->prop->tuner_return_loss.mode = Si2157_TUNER_RETURN_LOSS_PROP_MODE_TERRESTRIAL;
                 if (Si2157_L1_SetProperty2(api, Si2157_TUNER_RETURN_LOSS_PROP_CODE) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_TUNER_RETURN_LOSS_PROP_CODE\n"));
                }
                api->prop->dtv_pga_limits.max = 56;
                api->prop->dtv_pga_limits.min = 24;
                if (Si2157_L1_SetProperty2(api,Si2157_DTV_PGA_LIMITS_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_PGA_LIMITS_PROP\n"));
                }
                break;                
           case E_Network_Type_DTMB:
                api->prop->dtv_mode.modulation = Si2157_DTV_MODE_PROP_MODULATION_DTMB;
                api->prop->dtv_mode.bw = Si2157_DTV_MODE_PROP_BW_BW_8MHZ;
                api->prop->dtv_mode.invert_spectrum = Si2157_DTV_MODE_PROP_INVERT_SPECTRUM_NORMAL;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_MODE_PROP\n"));
                }
                api->prop->dtv_agc_speed.if_agc_speed = Si2157_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
                api->prop->dtv_agc_speed.agc_decim = Si2157_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_AGC_SPEED_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_AGC_SPEED_PROP\n"));
                }
                api->prop->dtv_initial_agc_speed_period.period = 0;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_INITIAL_AGC_SPEED_PERIOD_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_INITIAL_AGC_SPEED_PERIOD_PROP\n"));
                }
                /* AMP=55 to get IF_AGC 1.0v in MSB1400 on 149B-C01A when AMP is controlled by demod AGC (DTV_AGC_SOURCE=DLIF_AGC_3DB) */
                api->prop->dtv_lif_out.amp = 44;
                if (Si2157_L1_SetProperty2(api, Si2157_DTV_LIF_OUT_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_LIF_OUT_PROP\n"));
                }
				/*
				api->prop->dtv_lif_freq.offset =C_Si2157_IF_FREQUENCY;
				if (Si2157_L1_SetProperty2(api, Si2157_DTV_LIF_FREQ_PROP) != 0)
				{
					mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_DTV_LIF_FREQ_PROP\n"));
				}
				*/
                break;    
           case E_Network_Type_ISDBC:    
           case E_Network_Type_Analog_T:
           case E_Network_Type_Analog_C:
           case E_Network_Type_DVBS:   
           default:
                printf("[Error]%s,%s,%d\n",__FILE__,__FUNCTION__,__LINE__);
                break;                
        }
    }
    else
    {
        switch (TV_SYS)
        {
            case si_tv_system_bg:                
                api->prop->atv_video_mode.color = Si2157_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;
                api->prop->atv_video_mode.invert_spectrum = Si2157_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_INVERTED;
                if (Si2157_L1_SetProperty2(api, Si2157_ATV_VIDEO_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_ATV_VIDEO_MODE_PROP\n"));
                }
                break;
            case si_tv_system_dk:
                api->prop->atv_video_mode.video_sys = Si2157_ATV_VIDEO_MODE_PROP_VIDEO_SYS_DK;
                api->prop->atv_video_mode.color = Si2157_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;
                api->prop->atv_video_mode.invert_spectrum = Si2157_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_INVERTED;
                if (Si2157_L1_SetProperty2(api, Si2157_ATV_VIDEO_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_ATV_VIDEO_MODE_PROP\n"));
                }
                api->prop->atv_lif_freq.offset = C_Si2157_IF_CENTER_DK;
                if (Si2157_L1_SetProperty2(api, Si2157_ATV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_ATV_LIF_FREQ_PROP\n"));
                }
                break;
            case si_tv_system_i:
                api->prop->atv_video_mode.video_sys = Si2157_ATV_VIDEO_MODE_PROP_VIDEO_SYS_I;
                api->prop->atv_video_mode.color = Si2157_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;
                api->prop->atv_video_mode.invert_spectrum = Si2157_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_INVERTED;
                if (Si2157_L1_SetProperty2(api, Si2157_ATV_VIDEO_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_ATV_VIDEO_MODE_PROP\n"));
                }
                api->prop->atv_lif_freq.offset = C_Si2157_IF_CENTER_I;
                if (Si2157_L1_SetProperty2(api, Si2157_ATV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_ATV_LIF_FREQ_PROP\n"));
                }
                break;
            case si_tv_system_m:
                api->prop->atv_video_mode.video_sys = Si2157_ATV_VIDEO_MODE_PROP_VIDEO_SYS_M;
                api->prop->atv_video_mode.color = Si2157_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;
                api->prop->atv_video_mode.invert_spectrum = Si2157_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_INVERTED;
                if (Si2157_L1_SetProperty2(api, Si2157_ATV_VIDEO_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_ATV_VIDEO_MODE_PROP\n"));
                }
                api->prop->atv_lif_freq.offset = C_Si2157_IF_CENTER_M;
                if (Si2157_L1_SetProperty2(api, Si2157_ATV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_ATV_LIF_FREQ_PROP\n"));
                }
                break;
            case si_tv_system_l:
                api->prop->atv_video_mode.video_sys = Si2157_ATV_VIDEO_MODE_PROP_VIDEO_SYS_L;
                api->prop->atv_video_mode.color = Si2157_ATV_VIDEO_MODE_PROP_COLOR_SECAM;
                api->prop->atv_video_mode.invert_spectrum = Si2157_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_INVERTED;
                if (Si2157_L1_SetProperty2(api, Si2157_ATV_VIDEO_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_ATV_VIDEO_MODE_PROP\n"));
                }
                api->prop->atv_lif_freq.offset = C_Si2157_IF_CENTER_L;
                if (Si2157_L1_SetProperty2(api, Si2157_ATV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_ATV_LIF_FREQ_PROP\n"));
                }
                api->prop->atv_lif_out.offset = Si2157_ATV_LIF_OUT_PROP_OFFSET_DEFAULT;
                break;
            case si_tv_system_lp:
                api->prop->atv_video_mode.video_sys = Si2157_ATV_VIDEO_MODE_PROP_VIDEO_SYS_LP;
                api->prop->atv_video_mode.color = Si2157_ATV_VIDEO_MODE_PROP_COLOR_SECAM;
                api->prop->atv_video_mode.invert_spectrum = Si2157_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_INVERTED;
                if (Si2157_L1_SetProperty2(api, Si2157_ATV_VIDEO_MODE_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_ATV_VIDEO_MODE_PROP\n"));
                }
                api->prop->atv_lif_freq.offset = C_Si2157_IF_CENTER_L1;
                if (Si2157_L1_SetProperty2(api, Si2157_ATV_LIF_FREQ_PROP) != 0)
                {
                    mcSHOW_HW_MSG((" [Silabs]: ERROR_SETTING_PROPERTY Si2157_ATV_LIF_FREQ_PROP\n"));
                }
                break;
            case si_tv_system_invalid:
            default:
                break;
        }
    }
}

static U32 Si2157_GetDefaultIF(U32 Freq, SI_AnalogTVSystem TV_SYS)
{
    U32 offset=0;
    switch (TV_SYS)
    {
        case si_tv_system_bg:
            if (Freq < 300000)
            {
                offset = C_Si2157_IF_CENTER_B;
                break;
            }
            if (Freq >= 300000)
            {
                offset = C_Si2157_IF_CENTER_GH;
                break;
            }
            break;
        case si_tv_system_dk:
            offset = C_Si2157_IF_CENTER_DK;
            break;
        case si_tv_system_i:
            offset = C_Si2157_IF_CENTER_I;
            break;
        case si_tv_system_m:
            offset = C_Si2157_IF_CENTER_M;
            break;
        case si_tv_system_l:
            offset = C_Si2157_IF_CENTER_L;
            break;
        case si_tv_system_lp:
            offset = C_Si2157_IF_CENTER_L1;
            break;
        case si_tv_system_invalid:
        default:
            printf("[Error]%s, %s, %d\n",__FILE__,__FUNCTION__,__LINE__);
            break;
    }
    return offset;
}
#if 0
int Si2157_printf(const char *format, ...)
{  
    //format = format;
     printf(format);
    return 0;
}
#endif


