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

* Class : device_tuner_sony_sut_re23x_tsb
* File  : device_tuner_sony_sut_re23x_tsb.cpp
**********************************************************************/
/*@ </FileComment ID=1246257763274> @*/

/*@ <Include> @*/

#include "drvIIC.h"

#include "msAPI_FreqTableATV.h"
#include "msAPI_Tuning.h"
#include "MApp_GlobalVar.h"
#include "MApp_TopStateMachine.h"

#include "sony_sut_pex41/sut_pex41_sat_V1000.c"
#include "sony_sut_pex41/sut_pex41_terr_V1000.c"

#define DBG_TUNER(x)  x

// ------------------------------------------------------------
// Other Define
// ------------------------------------------------------------
#define DIVIDER_RATIO_50KHz         0x05
#define DIVIDER_RATIO_31_25KHz      0x04
#define DIVIDER_RATIO_62_5KHz       0x03
#define DIVIDER_RATIO_125KHz        0x02
#define DIVIDER_RATIO_142_85KHz     0x01
#define DIVIDER_RATIO_166_7KHz      0x00

//#define TN_FREQ_STEP                E_FREQ_STEP_50KHz
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

#define IFP_ANALOG_M        5750
#define IFP_ANALOG_BG       7300 
#define IFP_ANALOG_IDK      7850
#define IFP_ANALOG_L        7850
#define IFP_ANALOG_L_DASH   2200 


#define IF_DVBT_6M          3600
#define IF_DVBT_7M          4200
#define IF_DVBT_8M          4800
#define IF_DVBT2_6M         3600
#define IF_DVBT2_7M         4200
#define IF_DVBT2_8M         4800
#define IF_DVBC             4900
#define IF_DTMB             5100
#define IF_ATSC             3700
#define IF_ISDBT            4750

/*@ </Definitions> @*/

#define SONY_SUT_RE23x_I2C_ADDR (((UINT16)TUNER_IIC_BUS<<8)|0xC0 )

// IFP_ANALOG_BG       7300
const MS_U16 VIF_A1_A2_SOS11_SOS12_B_Stereo_A2[16]=
{
 0x03B6,0x0628,0x0423,
 0x03BE,0x0628,0x041A,
 0x011A,0x0628,0x0200,0x06DA,0x0200,
 0x03B6,0x0628,0x0200,0x0423,0x0200
};

// IFP_ANALOG_BG       7300
const MS_U16 VIF_A1_A2_SOS11_SOS12_B_Mono_NICAM[16]=
{
 0x03B6,0x0628,0x0423,
 0x03C1,0x0628,0x0417,
 0x011A,0x0628,0x0200,0x06DA,0x0200,
 0x03B6,0x0628,0x0200,0x0423,0x0200
};

// IFP_ANALOG_BG       7300
const MS_U16 VIF_A1_A2_SOS11_SOS12_GH_Stereo_A2[16]=
{
 0x03B6,0x0628,0x0423,
 0x03BE,0x0628,0x041A,
 0x008E,0x0628,0x0200,0x076C,0x0200,
 0x03B6,0x0628,0x0200,0x0423,0x0200
};

// IFP_ANALOG_BG       7300
const MS_U16 VIF_A1_A2_SOS11_SOS12_GH_Mono_NICAM[16]=
{
 0x03B6,0x0628,0x0423,
 0x03C1,0x0628,0x0417,
 0x008E,0x0628,0x0200,0x076C,0x0200,
 0x03B6,0x0628,0x0200,0x0423,0x0200
};

// IFP_ANALOG_IDK      7850
const MS_U16 VIF_A1_A2_SOS11_SOS12_DK1_Stereo_A2[16]=
{
 0x03C4,0x0628,0x0414,
 0x03BD,0x0628,0x041B,
 0x00CE,0x0628,0x0200,0x072A,0x0200,
 0x03C4,0x0628,0x0200,0x0414,0x0200
};

// IFP_ANALOG_IDK      7850
const MS_U16 VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2[16]=
{
 0x03C4,0x0628,0x0414,
 0x03CA,0x0628,0x040D,
 0x00CE,0x0628,0x0200,0x072A,0x0200,
 0x03C4,0x0628,0x0200,0x0414,0x0200
};

// IFP_ANALOG_IDK      7850
const MS_U16 VIF_A1_A2_SOS11_SOS12_DK3_Stereo_A2[16]=
{
 0x03C4,0x0628,0x0414,
 0x03A9,0x0628,0x0430,
 0x00CE,0x0628,0x0200,0x072A,0x0200,
 0x03C4,0x0628,0x0200,0x0414,0x0200
};


// IFP_ANALOG_IDK      7850
const MS_U16 VIF_A1_A2_SOS11_SOS12_DK_Mono_NICAM[16]=
{
 0x03C4,0x0628,0x0414,
 0x03AE,0x0628,0x042B,
 0x00CE,0x0628,0x0200,0x072A,0x0200,
 0x03C4,0x0628,0x0200,0x0414,0x0200
};

// IFP_ANALOG_IDK      7850
const MS_U16 VIF_A1_A2_SOS11_SOS12_I[16]=
{
 0x03B4,0x0628,0x0425,
 0x03C6,0x0628,0x0412,
 0x0087,0x0628,0x0200,0x0773,0x0200,
 0x03B4,0x0628,0x0200,0x0425,0x0200
};

// IFP_ANALOG_M        5750
const MS_U16 VIF_A1_A2_SOS11_SOS12_MN[16]=
{
 0x03C7,0x0628,0x0411,
 0x03CC,0x0628,0x040B,
 0x01E5,0x0628,0x0200,0x0606,0x0200,
 0x03C7,0x0628,0x0200,0x0411,0x0200
};

// IFP_ANALOG_L        7850
const MS_U16 VIF_A1_A2_SOS11_SOS12_L[16]=
{
 0x03C4,0x0628,0x0414,
 0x03AE,0x0628,0x042B,
 0x00CE,0x0628,0x0200,0x072A,0x0200,
 0x03C4,0x0628,0x0200,0x0414,0x0200
};

// IFP_ANALOG_L_DASH   2200
const MS_U16 VIF_A1_A2_SOS11_SOS12_LP[16]=
{
 0x0128,0x0628,0x06CC,
 0x017F,0x0628,0x0671,
 0x03D2,0x0628,0x0200,0x0405,0x0200,
 0x0128,0x0628,0x0200,0x06CC,0x0200
};

static EN_TUNER_MODE m_eMode = E_TUNER_DTV_DVB_T_MODE;//E_TUNER_INVALID;
static AUDIOSTANDARD_TYPE_ m_OtherMode = E_AUDIOSTANDARD_NOTSTANDARD_;
static BOOLEAN devTuner_init = FALSE;
static int x41TunerStatus;

extern IF_FREQ MDrv_IFDM_GetIF(void);

BOOLEAN DTV_SetTune(double FreqMHz, RF_CHANNEL_BANDWIDTH eBandWidth, EN_TUNER_MODE eMode);
BOOLEAN ATV_SetTune(UINT32 u32FreqKHz,RFBAND eBand, EN_TUNER_MODE eMode,UINT8 u8OtherMode);
BOOLEAN TunerInit(void);
BOOLEAN DTV_SetTune_Sat(MS_U16 u16CenterFreq_MHz, MS_U32 u32SymbolRate_Ks);

//*--------------------------------------------------------------------------------------
//* Prototype of function to be provided by customer
//*--------------------------------------------------------------------------------------
MS_U8 platform_I2CRead(
    MS_U8  bus_id,
    MS_U8  i2c_slave_id,
    MS_U8* subadrptr,
    MS_U16 subadrlen,
    MS_U8* dataptr,
    MS_U16 datalen
    );

MS_U8 platform_I2CWrite(
    MS_U8  bus_id,
    MS_U8  i2c_slave_id,
    MS_U8* subadrptr,
    MS_U16 subadrlen,
    MS_U8* dataptr,
    MS_U16 datalen
    );

void platform_ms_delay(MS_U32);

MS_U8 platform_gpio_control(MS_U8 high);


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
//*--------------------------------------------------------------------------------------
MS_U8 platform_I2CRead(
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

    if(MDrv_IIC_ReadBytes(SONY_SUT_RE23x_I2C_ADDR, (U8) subadrlen, subadrptr, (U16) datalen, dataptr) == false)
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

//*--------------------------------------------------------------------------------------
MS_U8 platform_I2CWrite(
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

    if(MDrv_IIC_WriteBytes(SONY_SUT_RE23x_I2C_ADDR, (U8) subadrlen, subadrptr, (U16) datalen, dataptr) == false)
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
void platform_ms_delay(MS_U32 tms)
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
MS_U8 platform_gpio_control(MS_U8 high)
{
    MS_U8 bRet = 1;
    UNUSED (high);
    return bRet;
}

// ATV init..........
void devTunerInit(void)
{    
    if(devTuner_init == TRUE)
    {
      printf("Warning, Tuner init already....\n");
	  return;
    }

    if (TunerInit() == 0)
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
printf(" [DT]devTuner_Std_set, eMode=%d, OtherMode=%d\n",eMode,OtherMode);
    DBG_TUNER(printf("devTuner_Std_set, eMode=%d, OtherMode=%d\n",eMode,OtherMode);)

    return bRet;
}


// return dbm value, 3dBm~-90dBm
BOOLEAN mdev_GetSignalStrength(float* f_strength)
{
    INT16 rssi_x100;
    UINT8 ifagcreg=0,rfagcreg=0;
    float rssitemp=0.0;
			
    Terr_x_read_agc(&ifagcreg, &rfagcreg);
    rssi_x100 = Terr_tuner_calcRSSI(ifagcreg, rfagcreg);
    rssitemp = (float)rssi_x100 / 100;

    *f_strength = rssitemp;
	
    return TRUE;
}

BOOLEAN ATV_SetTune( MS_U32 u32FreqKHz,RFBAND eBand, EN_TUNER_MODE eMode,MS_U8 u8OtherMode)
{    
     UINT32 frequency;
     RECEIVE_MODE mode;

     UNUSED(eBand);
    printf("device_tuner_sony_sut_pex41: ATV_SetTune\n");
    if(x41TunerStatus != 1)
    {
       Sat_x_fin();
       x41TunerStatus=1;
    }
    frequency = u32FreqKHz; 

    if(eMode == E_TUNER_ATV_SECAM_L_PRIME_MODE)
    {
       mode = SONY_HELENE_ATV_L_DASH;
    }
    else if(eMode == E_TUNER_ATV_NTSC_MODE)
    {
        mode = SONY_HELENE_ATV_MN_SAP;
    }
    else
    {
        if(u8OtherMode == 0xff)
        {
            mode = SONY_HELENE_ATV_DK;
        }
        else
        {
            switch((AUDIOSTANDARD_TYPE_)u8OtherMode)
            {
            case E_AUDIOSTANDARD_BG_:
                mode = SONY_HELENE_ATV_BG;
                break;

            case E_AUDIOSTANDARD_I_:
                mode = SONY_HELENE_ATV_I;
                break;

            case E_AUDIOSTANDARD_DK_:
                mode = SONY_HELENE_ATV_DK;
                break;

            case E_AUDIOSTANDARD_L_:
                mode = SONY_HELENE_ATV_L;
                break;
            case E_AUDIOSTANDARD_M_:
                mode = SONY_HELENE_ATV_MN_SAP;
                break;
            default:
                mode = SONY_HELENE_ATV_DK;;
                break;
            }
        }

    }
    printf("  frequency = %ld, mode=%d\n", frequency, (int)mode);
    Terr_tuner_gpio(0,0);
	
    Terr_x_tune(frequency, mode, 1);
    Terr_waitms(50);    
    Terr_x_tune_end();
    return TRUE;
}


BOOLEAN DTV_SetTune(double FreqMHz, RF_CHANNEL_BANDWIDTH eBandWidth, EN_TUNER_MODE eMode)
{
     UINT32 frequency;
     RECEIVE_MODE mode = SONY_HELENE_DTV_DVBT_8;
    printf("device_tuner_sony_sut_pex41: DTV_SetTune\n");

    if(x41TunerStatus != 2)
    {
        Sat_x_fin();
        x41TunerStatus=2;
    }

    switch(eMode)
    {
        case E_TUNER_DTV_DVB_C_MODE:
        {
            if (eBandWidth == E_RF_CH_BAND_6MHz){
                mode = SONY_HELENE_DTV_DVBC_6;
            }else if (eBandWidth == E_RF_CH_BAND_8MHz){
                mode = SONY_HELENE_DTV_DVBC_8;
            }else{	
                mode = SONY_HELENE_DTV_DVBC_8;
            }
        }
        break;

        case E_TUNER_DTV_DVB_T_MODE:
        {
            if (eBandWidth == E_RF_CH_BAND_6MHz){
                mode = SONY_HELENE_DTV_DVBT_6;
            }else if (eBandWidth == E_RF_CH_BAND_7MHz){
                mode = SONY_HELENE_DTV_DVBT_7;
            }else if (eBandWidth == E_RF_CH_BAND_8MHz){
                mode = SONY_HELENE_DTV_DVBT_8;
            }else{
                mode = SONY_HELENE_DTV_DVBT_8;
            }
        }
        break;

        case E_TUNER_DTV_DVB_T2_MODE:
        {
            if (eBandWidth == E_RF_CH_BAND_6MHz)
                mode = SONY_HELENE_DTV_DVBT2_6;
            else if (eBandWidth == E_RF_CH_BAND_7MHz)
                mode = SONY_HELENE_DTV_DVBT2_7;
            else if (eBandWidth == E_RF_CH_BAND_8MHz)
                mode = SONY_HELENE_DTV_DVBT2_8;
        }
        break;

        case E_TUNER_DTV_DTMB_MODE:
        {
            mode = SONY_HELENE_DTV_DTMB;
        }
        break;

        case E_TUNER_DTV_ISDB_MODE:
        {
            if (eBandWidth == E_RF_CH_BAND_6MHz)
                mode = SONY_HELENE_DTV_ISDBT_6;
            else if (eBandWidth == E_RF_CH_BAND_7MHz)
                mode = SONY_HELENE_DTV_ISDBT_7;
            else if (eBandWidth == E_RF_CH_BAND_8MHz)
                mode = SONY_HELENE_DTV_ISDBT_8;
        }
        break;

        case E_TUNER_DTV_ATSC_MODE:
        {
            mode = SONY_HELENE_DTV_8VSB;
        }
        break;

        default:
            mode = SONY_HELENE_DTV_DVBT_8;
        break;
    }


    if (eMode == E_TUNER_DTV_ATSC_MODE)
        frequency = (UINT32)FreqMHz;  // KHz
    else
        frequency = (UINT32)(FreqMHz*1000.0); 

    Terr_tuner_gpio(0,1);

    Terr_x_tune(frequency, mode, 1);
    Terr_waitms(50);    
    Terr_x_tune_end();
    return TRUE;
}


BOOLEAN TunerInit(void)
{
    printf("device_tuner_sony_sut_pex41: TunerInit\n");
    /*PEX41 Initialize */
   Terr_x_pon();

    /* Satellite Initialize */
    Sat_x_pon();

    x41TunerStatus = 0;//0:sleep, 1:ATV, 2:DTV, 3:STV

    return TRUE;
}

BOOLEAN DTV_SetTune_Sat(MS_U16 u16CenterFreq_MHz, MS_U32 u32SymbolRate_Ks)
{
    UINT32 frequency;
    SAT_RECEIVE_MODE mode;
    UINT32 sr;
    printf("device_tuner_sony_sut_pex41: DTV_SetTune_Sat\n");

    if(x41TunerStatus != 3)
    {
        Terr_x_fin();
        x41TunerStatus=3;
    }
	
    mode = SONY_HORUS_SAT_SYSTEM_DVBS2;
    frequency = (UINT32)(u16CenterFreq_MHz*1000.0); 
    sr = u32SymbolRate_Ks;

    Terr_tuner_gpio(0,1);

    Sat_x_tune(frequency, mode, sr);
    return TRUE;
}

BOOLEAN MDrv_DVBS_Tuner_SetFreq(MS_U16 u16CenterFreq_MHz, MS_U32 u32SymbolRate_Ks)
{
    return DTV_SetTune_Sat(u16CenterFreq_MHz,u32SymbolRate_Ks);
}

BOOLEAN MDrv_DVBS_Tuner_Initial(void)
{
    return TRUE;
}

BOOLEAN MDrv_DVBS_Tuner_CheckLock(void)
{   
    return TRUE;
}
