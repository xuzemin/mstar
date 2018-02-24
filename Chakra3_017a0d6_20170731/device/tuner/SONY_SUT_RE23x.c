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

* Class : device_tuner_sony_sut_re23x
* File  : device_tuner_sony_sut_re23x.cpp
**********************************************************************/
/*@ </FileComment ID=1246257763274> @*/

/*@ <Include> @*/
#if 0
#include <unistd.h>
#include "debug.h"
#include "device_tuner_sony_sut_re23x.h"
#include "mapi_i2c.h"
#include "mapi_i2c_devTable.h"
#include "mapi_interface.h"
#include "mapi_gpio.h"
#include "mapi_gpio_devTable.h"
#include "mapi_vif.h"
#include "mapi_audio.h"

#include "MsTypes.h"
#include "drvDMD_common.h"
#include "drvDMD_INTERN_DVBT.h"
#include "drvDMD_INTERN_DVBC.h"
#endif

#include "drvIIC.h"

#include "msAPI_FreqTableATV.h"
#include "msAPI_Tuning.h"
#include "MApp_GlobalVar.h"
#include "MApp_TopStateMachine.h"


// #include "sony_sut_re23x/sut_rx23x_V021.c"
// #include "sony_sut_re23x/sut_rx23x_V040.c"
#include "sony_sut_re23x/sut_rx23x_v060.c"

#define DBG_TUNER(x)  // x

// ------------------------------------------------------------
// Other Define
// ------------------------------------------------------------
#if 0
#define DIVIDER_RATIO_50KHz         0x05
#define DIVIDER_RATIO_31_25KHz      0x04
#define DIVIDER_RATIO_62_5KHz       0x03
#define DIVIDER_RATIO_125KHz        0x02
#define DIVIDER_RATIO_142_85KHz     0x01
#define DIVIDER_RATIO_166_7KHz      0x00

#define TN_FREQ_STEP                E_FREQ_STEP_50KHz
#define DIVIDER_RATIO               DIVIDER_RATIO_50KHz
#define TUNER_IF_FREQ_KHz           38900L
#define TUNER_L_PRIME_IF_FREQ_KHz   33950L

#define TUNER_VHF_LOWMIN_FREQ             43000L//47000l//46250L
#define TUNER_VHF_LOWMAX_FREQ             147250L//142000L
#define TUNER_VHF_HIGHMIN_FREQ            154250L//149000L
#define TUNER_VHF_HIGHMAX_FREQ            431250L//426000L
#define TUNER_UHF_MIN_FREQ                434000L
#define TUNER_UHF_MAX_FREQ                863250L


#define DIVIDER_166K                0
#define DIVIDER_142K                1
#define DIVIDER_80K                 2
#define DIVIDER_62K                 3
#define DIVIDER_31K                 4
#define DIVIDER_50K                 5

#define TN_FREQ_SS_INVERSE_625      16      // 1/0.0625
#define TN_RSA_RSB_625              0x06
#define TN_RSA_RSB_50               0x05
#define TN_FREQ_SS_625              62.5    // kHz
#define TN_FREQ_SS_50               50      // kHz
#define TN_FREQ_SS_INVERSE_50       20      // 1/0.05
#define TN_FREQ_SS              TN_FREQ_SS_625

#define TN_LOW_BAND                 0x01
#define TN_MID_BAND                 0x02
#define TN_HIGH_BAND                0x04

#define IF_OUT_LEVEL_114            0
#define IF_OUT_LEVEL_112            (1<<3)
#define IF_OUT_LEVEL_110            (2<<3)
#define IF_OUT_LEVEL_108            (3<<3)
#define IF_OUT_LEVEL_106            (4<<3)
#define IF_OUT_LEVEL_104            (5<<3)
#define IF_OUT_LEVEL_105            (6<<3)
#define IF_OUT_LEVEL_Disable        (7<<3)

#define DIGITAL_IF_AGC_ON       0x00
#define DIGITAL_IF_AGC_OFF       0x08

#define CHARGE_PUMP_1            (1<<6)
#define CHARGE_PUMP_2           (2<<6)

#define CHARGE_PUMP_3           (1<<1)

#define ANALOG_IF_OUT       0x04
#define DIGITAL_IF_OUT      0x00

#define FAST_LOCK           0x20

#define BAND_SWITCH_UHF             0x04
#define BAND_SWITCH_VHF_HIGH        0x02
#define BAND_SWITCH_VHF_LOW         0x01

#define TUNER_HIBYTE(w)             ((MAPI_U8) (((MAPI_U16) (w) >> 8) & 0xFF))
#define TUNER_LOBYTE(w)             ((MAPI_U8) (w & 0xFF))
#endif

//#define TM_FALSE  1
#define SUT_RE23x_BUSY  1
#define SUT_RE23x_FREE  0

#define SONY_SUT_RE23x_I2C_ADDR (((UINT16)TUNER_IIC_BUS<<8)|0xC0 )

#if 0
// IFP_ANALOG_BG       7300
UINT16 VIF_A1_A2_SOS11_SOS12_B_Stereo_A2[16]=
{
 0x03B6,0x0628,0x0423,
 0x03BE,0x0628,0x041A,
 0x011A,0x0628,0x0200,0x06DA,0x0200,
 0x03B6,0x0628,0x0200,0x0423,0x0200
};

// IFP_ANALOG_BG       7300
UINT16 VIF_A1_A2_SOS11_SOS12_B_Mono_NICAM[16]=
{
 0x03B6,0x0628,0x0423,
 0x03C1,0x0628,0x0417,
 0x011A,0x0628,0x0200,0x06DA,0x0200,
 0x03B6,0x0628,0x0200,0x0423,0x0200
};

// IFP_ANALOG_BG       7300
UINT16 VIF_A1_A2_SOS11_SOS12_GH_Stereo_A2[16]=
{
 0x03B6,0x0628,0x0423,
 0x03BE,0x0628,0x041A,
 0x008E,0x0628,0x0200,0x076C,0x0200,
 0x03B6,0x0628,0x0200,0x0423,0x0200
};

// IFP_ANALOG_BG       7300
UINT16 VIF_A1_A2_SOS11_SOS12_GH_Mono_NICAM[16]=
{
 0x03B6,0x0628,0x0423,
 0x03C1,0x0628,0x0417,
 0x008E,0x0628,0x0200,0x076C,0x0200,
 0x03B6,0x0628,0x0200,0x0423,0x0200
};

// IFP_ANALOG_IDK      7850
UINT16 VIF_A1_A2_SOS11_SOS12_DK1_Stereo_A2[16]=
{
 0x03C4,0x0628,0x0414,
 0x03BD,0x0628,0x041B,
 0x00CE,0x0628,0x0200,0x072A,0x0200,
 0x03C4,0x0628,0x0200,0x0414,0x0200
};

// IFP_ANALOG_IDK      7850
UINT16 VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2[16]=
{
 0x03C4,0x0628,0x0414,
 0x03CA,0x0628,0x040D,
 0x00CE,0x0628,0x0200,0x072A,0x0200,
 0x03C4,0x0628,0x0200,0x0414,0x0200
};

// IFP_ANALOG_IDK      7850
UINT16 VIF_A1_A2_SOS11_SOS12_DK3_Stereo_A2[16]=
{
 0x03C4,0x0628,0x0414,
 0x03A9,0x0628,0x0430,
 0x00CE,0x0628,0x0200,0x072A,0x0200,
 0x03C4,0x0628,0x0200,0x0414,0x0200
};


// IFP_ANALOG_IDK      7850
UINT16 VIF_A1_A2_SOS11_SOS12_DK_Mono_NICAM[16]=
{
 0x03C4,0x0628,0x0414,
 0x03AE,0x0628,0x042B,
 0x00CE,0x0628,0x0200,0x072A,0x0200,
 0x03C4,0x0628,0x0200,0x0414,0x0200
};

// IFP_ANALOG_IDK      7850
UINT16 VIF_A1_A2_SOS11_SOS12_I[16]=
{
 0x03B4,0x0628,0x0425,
 0x03C6,0x0628,0x0412,
 0x0087,0x0628,0x0200,0x0773,0x0200,
 0x03B4,0x0628,0x0200,0x0425,0x0200
};

// IFP_ANALOG_M        5750
UINT16 VIF_A1_A2_SOS11_SOS12_MN[16]=
{
 0x03C7,0x0628,0x0411,
 0x03CC,0x0628,0x040B,
 0x01E5,0x0628,0x0200,0x0606,0x0200,
 0x03C7,0x0628,0x0200,0x0411,0x0200
};

// IFP_ANALOG_L        7850
UINT16 VIF_A1_A2_SOS11_SOS12_L[16]=
{
 0x03C4,0x0628,0x0414,
 0x03AE,0x0628,0x042B,
 0x00CE,0x0628,0x0200,0x072A,0x0200,
 0x03C4,0x0628,0x0200,0x0414,0x0200
};

// IFP_ANALOG_L_DASH   2200
UINT16 VIF_A1_A2_SOS11_SOS12_LP[16]=
{
 0x0128,0x0628,0x06CC,
 0x017F,0x0628,0x0671,
 0x03D2,0x0628,0x0200,0x0405,0x0200,
 0x0128,0x0628,0x0200,0x06CC,0x0200
};
#endif
static UINT8 u8SUT_RE23xBusy=SUT_RE23x_FREE;
static BOOLEAN devTuner_init = FALSE;

static EN_TUNER_MODE m_eMode = E_TUNER_DTV_DVB_T_MODE;//E_TUNER_INVALID;
static AUDIOSTANDARD_TYPE_ m_OtherMode = E_AUDIOSTANDARD_NOTSTANDARD_;

extern IF_FREQ MDrv_IFDM_GetIF(void);
BOOLEAN DTV_SetTune(double FreqMHz, RF_CHANNEL_BANDWIDTH eBandWidth, EN_TUNER_MODE eMode);
BOOLEAN ATV_SetTune(UINT32 u32FreqKHz,RFBAND eBand, EN_TUNER_MODE eMode,UINT8 u8OtherMode);

//*--------------------------------------------------------------------------------------
//* Prototype of function to be provided by customer
//*--------------------------------------------------------------------------------------
UINT8 platform_I2CRead(
    UINT8  bus_id,
    UINT8  i2c_slave_id,
    UINT8* subadrptr,
    UINT16 subadrlen,
    UINT8* dataptr,
    UINT16 datalen
    );

UINT8 platform_I2CWrite(
    UINT8  bus_id,
    UINT8  i2c_slave_id,
    UINT8* subadrptr,
    UINT16 subadrlen,
    UINT8* dataptr,
    UINT16 datalen
    );

void platform_ms_delay(UINT32);

UINT8 platform_gpio_control(UINT8 high);


//*--------------------------------------------------------------------------------------
//* Function Name       :   platform_I2CRead
//* Object              :
//* Input Parameters    :   UINT8  bus_id,
//*                         UINT8  i2c_slave_id,
//*                         UINT8* subadrptr,
//*                         UINT16 subadrlen,
//*                         UINT8* dataptr,
//*                         UINT16 datalen,
//* Output Parameters   :   UINT8 bRet,
//*--------------------------------------------------------------------------------------
UINT8 platform_I2CRead(
    UINT8  bus_id,
    UINT8  i2c_slave_id,
    UINT8* subadrptr,
    UINT16 subadrlen,
    UINT8* dataptr,
    UINT16 datalen
    )
{
    /* Variable declarations */
    UINT8 bRet = 1;
	UNUSED(bus_id);
    if(MDrv_IIC_ReadBytes((UINT16)((SONY_SUT_RE23x_I2C_ADDR&0xff00)|i2c_slave_id), subadrlen, subadrptr, datalen, dataptr) == FALSE)
    {
        bRet = 0;
        printf("\nTuner_IIC read  fail\n");
    }        
    return bRet;
}

//*--------------------------------------------------------------------------------------
//* Function Name       :   platform_I2CWrite
//* Object              :
//* Input Parameters    :   UINT8  bus_id,
//*                         UINT8  i2c_slave_id,
//*                         UINT8* subadrptr,
//*                         UINT16 subadrlen,
//*                         UINT8* dataptr,
//*                         UINT16 datalen,
//* Output Parameters   :   UINT8 bRet,

//*--------------------------------------------------------------------------------------
UINT8 platform_I2CWrite(
    UINT8  bus_id,
    UINT8  i2c_slave_id,
    UINT8* subadrptr,
    UINT16 subadrlen,
    UINT8* dataptr,
    UINT16 datalen
    )
{
    /* Variable declarations */
    UINT8 bRet = 1;
    
	UNUSED(bus_id);
    if(MDrv_IIC_WriteBytes((UINT16)((SONY_SUT_RE23x_I2C_ADDR&0xff00)|i2c_slave_id), subadrlen, subadrptr, datalen, dataptr) == FALSE)
    {
        bRet = 0;
        printf("\nTuner_IIC read  fail\n");
    }        
    return bRet;
}

//*--------------------------------------------------------------------------------------
//* Function Name       : platform_ms_delay
//* Object              :
//* Input Parameters    :   UINT32 tms
//*
//* Output Parameters   :   void
//*--------------------------------------------------------------------------------------
void platform_ms_delay(UINT32 tms)
{
    /* Variable declarations */
    MsOS_DelayTask(tms);
    return;
}

//*--------------------------------------------------------------------------------------
//* Function Name       : platform_gpio_control
//* Object              :
//* Input Parameters    : UINT8 high
//*
//* Output Parameters   : bRet
//*--------------------------------------------------------------------------------------
UINT8 platform_gpio_control(UINT8 high)
{
    UINT8 bRet = 1;
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



UINT8 dev_sut_re23x_TunerInit(void)
{
    //* Begin
    /* Variable declarations */
    UINT8 bRet = 1;
    S_SUT_RE23x_dependency_func sut_re23x_func_obj;

    if (u8SUT_RE23xBusy==SUT_RE23x_FREE)
    {
        /* Low layer struct set-up to link with user written functions */
        sut_re23x_func_obj.i2c_read        = platform_I2CRead;
        sut_re23x_func_obj.i2c_write       = platform_I2CWrite;
        sut_re23x_func_obj.ms_delay        = platform_ms_delay;
        sut_re23x_func_obj.hw_rst_control  = platform_gpio_control;

        // platform dependency api registration.
        bRet &= mdev_Tunerfunc_SUT(&sut_re23x_func_obj);

        bRet &= mdev_TunerInit_SUT();

        u8SUT_RE23xBusy=SUT_RE23x_BUSY;
    }

    /* Send Request 55.25 MHz standard PAL B*/
    bRet &= mdev_TunerSetPllData_SUT(55250L, IF_FREQ_B);

    return bRet;
}

#if 0
UINT8 dev_sut_re23x_DigitalTuner_Init(void)
{
    //* Begin
    /* Variable declarations */
    UINT8 bRet = 1;
    S_SUT_RE23x_dependency_func sut_re23x_func_obj;

    if (u8SUT_RE23xBusy==SUT_RE23x_FREE)
    {
        /* Low layer struct set-up to link with user written functions */
        sut_re23x_func_obj.i2c_read  = platform_I2CRead;
        sut_re23x_func_obj.i2c_write = platform_I2CWrite;
        sut_re23x_func_obj.ms_delay  = platform_ms_delay;

        // platform dependency api registration.
        bRet &= mdev_Tunerfunc_SUT(&sut_re23x_func_obj);

        bRet &= mdev_TunerInit_SUT();

        u8SUT_RE23xBusy=SUT_RE23x_BUSY;
    }

    /* Send Request 666 MHz standard DVBT 8M*/
    bRet &= mdev_TunerDigitalSetFreq_SUT ( 666000L, E_RF_CH_BAND_8MHz, E_TUNER_DTV_DVB_T_MODE);

    return bRet;

}
#endif

// ATV init..........
void devTunerInit(void)
{    
    if(devTuner_init == TRUE)
    {
      printf("Warning, Tuner init already....\n");
	  return;
    }

    if (dev_sut_re23x_TunerInit() == 0)
    {
        printf("[Error]%s,%d\n",__FILE__,__LINE__);
    }
    else
    {
        devTuner_init = TRUE;
    }

    return;
}

// DTV init..........
void devDigitalTuner_Init(void)
{
    devTunerInit();
    return;
}

void devDigitalTuner_SetFreq ( double Freq,  RF_CHANNEL_BANDWIDTH eBandWidth)
{

    BOOLEAN bRet = TRUE;

    DBG_TUNER(printf("[devDigitalTuner_SetFreq]Freq=%d, eBandWidth=%d, m_eMode=%d\n",(UINT16)Freq,(UINT8)eBandWidth,(UINT8)m_eMode);)

    if (devTuner_init == FALSE)
    {
        printf("[Error]%s,%d\n",__FILE__,__LINE__);
        return;
    }

    // Freq (MHz)
    bRet &= DTV_SetTune(Freq, eBandWidth, m_eMode);

    if (bRet == FALSE)
        printf("[Error]%s,%d\n",__FILE__,__LINE__);

    return;
}


void devTunerSetFreq(UINT32 u32Freq)
{
    BOOLEAN retb = TRUE;

    if (devTuner_init == FALSE)
    {
        printf("[Error]%s,%d\n",__FILE__,__LINE__);
        return;
    }
    
    IF_FREQ CurrentStandard = MDrv_IFDM_GetIF();

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

    retb &= ATV_SetTune(u32Freq/1000,(RFBAND)0, m_eMode,(UINT8)m_OtherMode);

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


BOOLEAN ATV_SetTune(UINT32 u32FreqKHz,RFBAND eBand, EN_TUNER_MODE eMode,UINT8 u8OtherMode)
{
    UINT8 bRet = 1;
    IF_FREQ StandardMode = IF_FREQ_B;

    eBand = eBand;

    if(eMode == E_TUNER_ATV_SECAM_L_PRIME_MODE)
    {
        //printf(" \33[0;32m >>>@@@>>>@@@@>>>@@@ 111  E_TUNER_ATV_SECAM_L_PRIME_MODE \n \33[m");
        StandardMode = IF_FREQ_L_PRIME;
    }
    else
    {
        //printf(" \33[0;32m >>>@@@>>>@@@@>>>@@@ 222  E_TUNER_ATV_PAL_MODE \n \33[m");

        //printf("OtherMode[%d]\r\n",u8OtherMode);
        if(u8OtherMode == 0xff)
        {
            StandardMode = IF_FREQ_DK;
        }
        else
        {
            switch((AUDIOSTANDARD_TYPE_)u8OtherMode)
            {
            case E_AUDIOSTANDARD_BG_:
                StandardMode = IF_FREQ_B;
                break;

            case E_AUDIOSTANDARD_I_:
                StandardMode = IF_FREQ_I;
                break;

            case E_AUDIOSTANDARD_DK_:
                StandardMode = IF_FREQ_DK;
                break;

            case E_AUDIOSTANDARD_L_:
                StandardMode = IF_FREQ_L;
                break;

            case E_AUDIOSTANDARD_M_:
                StandardMode = IF_FREQ_MN;
                break;
            default:
                StandardMode = IF_FREQ_DK;
                break;
            }
        }

    }

    bRet &= mdev_TunerSetPllData_SUT(u32FreqKHz, StandardMode);

    return bRet;
}

BOOLEAN DTV_SetTune(double FreqMHz, RF_CHANNEL_BANDWIDTH eBandWidth, EN_TUNER_MODE eMode)
{
    UINT8 bRet = 1;

    bRet &= mdev_TunerDigitalSetFreq_SUT ( (UINT32)(FreqMHz*1000), eBandWidth, eMode);

    return (bRet == 1)?TRUE:FALSE;
}

// return dbm value, 3dBm~-90dBm
BOOLEAN mdev_GetSignalStrength(float* f_strength)
{
    float rssi = 0;
    if (mdev_Tuner_read_rssi(&rssi) == 0)
    {
        printf("Error, %s, %s, %d\n",__FILE__,__FUNCTION__,__LINE__);
        *f_strength = 0;
        return FALSE;
    }
    else
    {
        *f_strength = rssi;
        return TRUE;
    }    
}


#if 0
BOOLEAN device_tuner_sony_sut_re23x::ExtendCommand(UINT8 u8SubCmd, UINT32 u32Param1, UINT32 u32Param2, void* pvoidParam3)
{
    // printf("device_tuner_sony_sut_re23x::ExtendCommand\n  ");

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
            MAPI_U16 *u16IFFreq = (MAPI_U16 *)pvoidParam3;
            *u16IFFreq = TUNER_IF_FREQ_KHz;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_L_PRIME_IF_FREQ:
        {
            MAPI_U16 *u16IFFreq = (MAPI_U16 *)pvoidParam3;
            *u16IFFreq = TUNER_L_PRIME_IF_FREQ_KHz;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_VHF_LOWMIN_FREQ:
        {
            UINT32 *u32Freq = (UINT32 *)pvoidParam3;
            *u32Freq = TUNER_VHF_LOWMIN_FREQ;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_VHF_LOWMAX_FREQ:
        {
            UINT32 *u32Freq = (UINT32 *)pvoidParam3;
            *u32Freq = TUNER_VHF_LOWMAX_FREQ;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_VHF_HIGHMIN_FREQ:
        {
            UINT32 *u32Freq = (UINT32 *)pvoidParam3;
            *u32Freq = TUNER_VHF_HIGHMIN_FREQ;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_VHF_HIGHMAX_FREQ:
        {
            UINT32 *u32Freq = (UINT32 *)pvoidParam3;
            *u32Freq = TUNER_VHF_HIGHMAX_FREQ;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_UHF_MIN_FREQ:
        {
            UINT32 *u32Freq = (UINT32 *)pvoidParam3;
            *u32Freq = TUNER_UHF_MIN_FREQ;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_UHF_MAX_FREQ:
        {
            UINT32 *u32Freq = (UINT32 *)pvoidParam3;
            *u32Freq = TUNER_UHF_MAX_FREQ;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_VIF_TUNER_TYPE:
        {
            UINT8 *u8VifTunerType = (UINT8 *)pvoidParam3;
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
            MAPI_U16 *pu16_vif_notch_coef = NULL;
            MAPI_U16 *pu16_list = (MAPI_U16*)pvoidParam3;
            UINT8 indx = 0;
            
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
                case E_TUNER_DTV_DVB_T2_MODE:                    switch(u32Param2) // bandwidth
                    {
                        case E_RF_CH_BAND_6MHz:
                            *((UINT32 *)pvoidParam3)=IF_DVBT2_6M;
                            break;
                        case E_RF_CH_BAND_7MHz:
                            *((UINT32 *)pvoidParam3)=IF_DVBT2_7M;                            break;
                        case E_RF_CH_BAND_8MHz:
                            *((UINT32 *)pvoidParam3)=IF_DVBT2_8M;                
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
                            *((UINT32 *)pvoidParam3)=IF_DVBT_6M;
                            break;
                        case E_RF_CH_BAND_7MHz:
                            *((UINT32 *)pvoidParam3)=IF_DVBT_7M;
                            break;
                        case E_RF_CH_BAND_8MHz:
                            *((UINT32 *)pvoidParam3)=IF_DVBT_8M;
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
                            *((UINT32 *)pvoidParam3)=IF_DVBC;
                            break;
                        default:
                            printf("Error:%s(),%d\n",__func__,__LINE__);
                            return FALSE;
                            break;
                    }
                    break;
                case E_TUNER_DTV_ATSC_MODE:
                    *((UINT32 *)pvoidParam3)=IF_ATSC;
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
            UINT8 *u8IqSwap = (UINT8 *)pvoidParam3;
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
            float rssi = 0;
            if (mdev_Tuner_read_rssi(&rssi) == 0)
            {
                printf("Error, %s, %s, %d\n",__FILE__,__FUNCTION__,__LINE__);
                *((float *)pvoidParam3) = 0.0;
                return FALSE;
            }
            else
            {
                *((float *)pvoidParam3) = (float)rssi;
                return TRUE;
            }
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_DEMOD_CONFIG:
        {

            switch (u32Param1) // demod mode
            {
                case E_TUNER_DTV_DVB_T_MODE:

                    static UINT8 u8TUNER_DVBT_DSPRegInitExt[]={
                                                                                                1, // version, should be matched with library
                                                                                                0, // reserved
                                                                                                0, // Size_L
                                                                                                0, // Size_H
                                                                                                E_DMD_DVBT_N_IF_INV_PWM_OUT_EN, // Addr_L
                                                                                                E_DMD_DVBT_N_IF_INV_PWM_OUT_EN>>8, // Addr_H
                                                                                                0xFF, // Mask
                                                                                                0x01}; // Value
                    u8TUNER_DVBT_DSPRegInitExt[2]=(sizeof(u8TUNER_DVBT_DSPRegInitExt)-4)/4;
                    u8TUNER_DVBT_DSPRegInitExt[3]=((sizeof(u8TUNER_DVBT_DSPRegInitExt)-4)/4)>>8;
                    *((UINT8 **)pvoidParam3)=u8TUNER_DVBT_DSPRegInitExt;

                    // *((UINT8 **)pvoidParam3)=NULL;
                    break;
                case E_TUNER_DTV_DVB_C_MODE:
                    /*
                        E_DMD_DVBC_OP_ZIF_EN,                       //ZIF
                        E_DMD_DVBC_OP_NORMALIF_EN,                  //NIF
                        E_DMD_DVBC_OP_LIF_EN,                            //LIF
                        E_DMD_DVBC_OP_SAWLESS_EN,                  //SAWLESS
                        E_DMD_DVBC_OP_IQB_EN,
                        E_DMD_DVBC_CFG_ZIF,
                        E_DMD_DVBC_IF_INV_PWM_OUT_EN,           //Sony Tuner , 0x10
                    */

                    static UINT8 u8TUNER_DVBC_DSPRegInitExt[]={
                                                                                                1, // version, should be matched with library
                                                                                                0, // reserved
                                                                                                0, // Size_L
                                                                                                0, // Size_H
                                                                                                E_DMD_DVBC_IF_INV_PWM_OUT_EN, // Addr_L
                                                                                                E_DMD_DVBC_IF_INV_PWM_OUT_EN>>8, // Addr_H
                                                                                                0xFF, // Mask
                                                                                                0x01}; // Value
                    u8TUNER_DVBC_DSPRegInitExt[2]=(sizeof(u8TUNER_DVBC_DSPRegInitExt)-4)/4;
                    u8TUNER_DVBC_DSPRegInitExt[3]=((sizeof(u8TUNER_DVBC_DSPRegInitExt)-4)/4)>>8;
                    *((UINT8 **)pvoidParam3)=u8TUNER_DVBC_DSPRegInitExt;
                    
                    break;
                case E_TUNER_ATV_PAL_MODE:
                case E_TUNER_ATV_SECAM_L_PRIME_MODE:
                case E_TUNER_ATV_NTSC_MODE:
                {
                    UINT32 *u32AgcOdMode = (UINT32 *)pvoidParam3;
                    *u32AgcOdMode = TUNER_VIF_TAGC_ODMODE;
                }
                    break;
                case E_TUNER_DTV_DVB_T2_MODE:
                {
                    UINT8 *u8if_AgcMode = (UINT8 *)pvoidParam3;
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

