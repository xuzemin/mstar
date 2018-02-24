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

#ifndef TDTC_G311D_C
#define TDTC_G311D_C

#include <stdio.h>

#include "Board.h"
#include "datatype.h"
#include "drvIIC.h"

#include "COFDM_Demodulator.h"
#include "Tuner.h"
#include "msAPI_FreqTableATV.h"
#include "msAPI_Tuning.h"
#include "MApp_GlobalSettingSt.h"
#define DIVIDER_RATIO_31_25KHz  0x04
#define DIVIDER_RATIO_62_5KHz   0x03
#define DIVIDER_RATIO_166_7KHz  0x00
#define DIVIDER_RATIO_50KHz     0x05

#define USE_EXTERNAL_RF_AGC        1

#if (TN_FREQ_STEP == FREQ_STEP_31_25KHz)
#define DIVIDER_RATIO      DIVIDER_RATIO_31_25KHz
#elif (TN_FREQ_STEP == FREQ_STEP_50KHz)
#define DIVIDER_RATIO      DIVIDER_RATIO_50KHz
#elif (TN_FREQ_STEP == FREQ_STEP_62_5KHz)
#define DIVIDER_RATIO      DIVIDER_RATIO_62_5KHz
#endif

#define DEBUG_PAL_TUNER   0

#define  PAL_DBG_MSG(x)  x

static FREQSTEP m_eFrequencyStep;

U8 ucStatus; // tuner status

void devTunerSetFreqStep(FREQSTEP eFreqStep)
{
    switch(eFreqStep)
    {
    case FREQSTEP_31_25KHz:
    case FREQSTEP_62_5KHz:
    case FREQSTEP_50KHz:
        m_eFrequencyStep = eFreqStep;
        break;

    default:
        m_eFrequencyStep = FREQSTEP_31_25KHz;
        break;
    }
}

void devTunerSetPLLData(WORD wPLLData, RFBAND eBand)
{

    BYTE cTunerData[5];
    U16  u16Freq;
    // Write DB1,DB2,CB,BB
    cTunerData[0] = HIBYTE(wPLLData);
    cTunerData[1] = LOBYTE(wPLLData);

    u16Freq = msAPI_CFT_ConvertPLLtoIntegerOfFrequency(wPLLData-msAPI_Tuner_GetIF());

    #if USE_EXTERNAL_RF_AGC
    cTunerData[2] = 0x80|DIVIDER_RATIO|IF_OUT_LEVEL_Disable;
    #else
    cTunerData[2] = 0x80|DIVIDER_RATIO|IF_OUT_LEVEL_106;
    #endif

    if(eBand == E_RFBAND_VHF_LOW)
    {
        if ( u16Freq <= 100 )
        {
            cTunerData[3] = 0x81;
        }
        else
        {
            cTunerData[3] = 0xc1;

        }

    }
    else if(eBand == E_RFBAND_VHF_HIGH)
    {
        if ( u16Freq <= 300 )
        {
            cTunerData[3] = 0x82;
        }
        else
        {
            cTunerData[3] = 0xC2;

        }

    }
    else
    {
        if ( u16Freq <= 700 )
        {
            cTunerData[3] = 0x98;
        }
        else
        {
            cTunerData[3] = 0xd8;

        }
    }

    cTunerData[4] = 0xc3;

#if 0
printf("---> ATV Tuner: \n");

    {
        BYTE i;
        for(i=0;i<5;i++)
            printf("%lx ", (U32)cTunerData[i]);
        printf("\n\r");
    }
#endif

#define BD_MST087A_D01A_S       0x0702   // 256p QFP
#define BD_MST087B_S7M_D01A_S   0x0703   // S7M - support URSA3
#define BD_MST087B_S7_D01A_S    0x0704   // S7
#define BD_MST087C_D02A_S       0x0705   // SEC X1
#define BD_MST087D_D01A_S       0x0706   // S7

#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_J2) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)|| \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7L) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5)  || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A6) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)

    {
        U16 u16Temp=0x0200;

        u16Temp|=_TUNER_I2C_ID;
        MDrv_IIC_WriteBytes(u16Temp,  0, NULL, 5, cTunerData);
    }
#else
    devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 5, cTunerData);
#endif

}

void devTunerInit(void)
{
    BYTE cTunerData[4];

    //devTunerSetFreqStep(TN_FREQ_STEP);//Type mismatch,
    cTunerData[0] = 0;
    cTunerData[1] = 0;
    #if USE_EXTERNAL_RF_AGC
    cTunerData[2] = 0x80|DIVIDER_RATIO|IF_OUT_LEVEL_Disable;
    #else
    cTunerData[2] = 0x80|DIVIDER_RATIO|IF_OUT_LEVEL_106;
    #endif
    cTunerData[3] = 0x60;
#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_J2) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)|| \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7L) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5)  || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A6) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)
    {
        U16 u16Temp=0x0200;

        u16Temp|=_TUNER_I2C_ID;
        MDrv_IIC_WriteBytes(u16Temp,  0, NULL, 4, cTunerData);
    }
#else
    devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 4, cTunerData);
#endif
}


#define DIGITAL_TUNER_IF    36.167

/*************************************************************************
  Subject:    FQD1216 tuner initialized function
  Function:   MDrv_Tuner_Init
  Parmeter:   CONFIG: pointer to tuner address
  Return :    NONE
  Remark:
**************************************************************************/
void devDigitalTuner_Init()
{
}


#define DIVIDER_166K              0
#define DIVIDER_142K              1
#define DIVIDER_80K               2
#define DIVIDER_62K               3
#define DIVIDER_31K               4
#define DIVIDER_50K               5

void devDigitalTuner_SetFreq ( double Freq, RF_CHANNEL_BANDWIDTH eBandWidth)
{
    unsigned int value;
    unsigned char CONFIG[6];

    //MDrv_Set_Digital_TUNER1(Freq, eBandWidth);


    // Step 166.7 Khz   1000/166.7 = 6
#if ENABLE_T_C_COMBO//TODO only support internal demod
    if(msAPI_Tuner_GetSourceType() == EN_DVB_C_TYPE)
    {
        value = ( unsigned int ) ( ( Freq + DIGITAL_TUNER_IF ) * 16 + 0.5); //step size = 62.5KHz
    }
    else
    {
        value = ( unsigned int ) ( ( Freq + DIGITAL_TUNER_IF ) * 6 + 0.5);
    }
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD)
    value = ( unsigned int ) ( ( Freq + DIGITAL_TUNER_IF ) * 16 + 0.5); //step size = 62.5KHz
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1210_DEMOD) || (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD)   // GEM_SYNC_0815
    value = ( unsigned int ) ( ( Freq + DIGITAL_TUNER_IF ) * 6 + 0.5);
#else
    value = ( unsigned int ) ( ( Freq + DIGITAL_TUNER_IF ) * 32);
#endif

    //DB1
    CONFIG[0] = ( unsigned char ) ( value >> 8 );

    //DB2
    CONFIG[1] = ( unsigned char ) ( value );
#if ENABLE_T_C_COMBO//TODO only support internal demod
    if(msAPI_Tuner_GetSourceType() == EN_DVB_C_TYPE)
    {
        CONFIG[2] = 0x80 | IF_OUT_LEVEL_100 | DIVIDER_62K; // CB1
    }
    else
    {
        CONFIG[2] = 0x80 | IF_OUT_LEVEL_106 | DIVIDER_166K; // CB1
    }
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD)
    CONFIG[2] = 0x80 | IF_OUT_LEVEL_100 | DIVIDER_62K; // CB1
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1210_DEMOD) || (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD)   // GEM_SYNC_0815
    CONFIG[2] = 0x80 | IF_OUT_LEVEL_106 | DIVIDER_166K; // CB1
#else
    CONFIG[2] = 0x80 | IF_OUT_LEVEL_106 | DIVIDER_31K; // CB1
#endif

    CONFIG[3] = 0;
    if(eBandWidth == E_RF_CH_BAND_7MHz)
    {
        CONFIG[3] |= P5_ADC_INPUT;
    }
    else if(eBandWidth==E_RF_CH_BAND_8MHz)
    {
        CONFIG[3] |= P5_TR_ON;
    }
    else
    {
        //printf("unsupport bw: %d\n", (int)(eBandWidth+5));
    }

    if ( Freq <= 142.5 ) // VHF low
    {
#if ENABLE_T_C_COMBO//TODO only support internal demod
        if(msAPI_Tuner_GetSourceType() == EN_DVB_C_TYPE)
        {
            CONFIG[3] |= CHARGE_PUMP_70uA;
        }
        else
        {
            if ( Freq <= 100 )
            {
                CONFIG[3] |= CHARGE_PUMP_350uA;
            }
            else
            {
                CONFIG[3] |= CHARGE_PUMP_600uA;

            }
        }
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD)
        CONFIG[3] |= CHARGE_PUMP_70uA;
#else
        if ( Freq <= 100 )
        {
            CONFIG[3] |= CHARGE_PUMP_350uA;
        }
        else
        {
            CONFIG[3] |= CHARGE_PUMP_600uA;

        }
#endif
        CONFIG[3] |= BAND_SWITCH_VHF_LOW;
    }
    else if ( Freq  <= 426 ) // VHF high
    {
#if ENABLE_T_C_COMBO//TODO only support internal demod
        if(msAPI_Tuner_GetSourceType() == EN_DVB_C_TYPE)
        {
            CONFIG[3] |= CHARGE_PUMP_70uA;
        }
        else
        {
            if ( Freq <= 300 )
            {
                CONFIG[3] |= CHARGE_PUMP_350uA;
            }
            else
            {
                CONFIG[3] |= CHARGE_PUMP_600uA;

            }
        }
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD)
        CONFIG[3] |= CHARGE_PUMP_70uA;
#else
        if ( Freq <= 300 )
        {
            CONFIG[3] |= CHARGE_PUMP_350uA;
        }
        else
        {
            CONFIG[3] |= CHARGE_PUMP_600uA;

        }
#endif
        CONFIG[3] |= BAND_SWITCH_VHF_HIGH;

    }
    else  // UHF
    {
#if ENABLE_T_C_COMBO//TODO only support internal demod
        if(msAPI_Tuner_GetSourceType() == EN_DVB_C_TYPE)
        {
            CONFIG[3] |= CHARGE_PUMP_70uA;
        }
        else
        {
            if ( Freq <= 700 )
            {
                CONFIG[3] |= CHARGE_PUMP_350uA;
            }
            else
            {
                CONFIG[3] |= CHARGE_PUMP_600uA;

            }
        }
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD)
        CONFIG[3] |= CHARGE_PUMP_70uA;
    #else
        if ( Freq <= 700 )
        {
            CONFIG[3] |= CHARGE_PUMP_350uA;
        }
        else
        {
            CONFIG[3] |= CHARGE_PUMP_600uA;

        }
    #endif
        CONFIG[3] |= BAND_SWITCH_UHF;

    }

    CONFIG[4] = 0xC3; //CB2

    //printf("Tuner: %bx, %bx, %bx, %bx, %bx\n", CONFIG[0], CONFIG[1], CONFIG[2], CONFIG[3], CONFIG[4]);

#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_J2) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)|| \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7L) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A1) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A5)  || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A6) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_A7) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) || \
    (CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON)
    {
       U16 u16Temp=0x0200;
       u16Temp|=_TUNER_I2C_ID;
       MDrv_IIC_WriteBytes(u16Temp, 0, NULL, 5, CONFIG);
    }
#else
        devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 5, CONFIG);
#endif
    //printf( "frequency=%f \n" ,Freq) ;
}

#undef TDTC_G001D_C
#endif

