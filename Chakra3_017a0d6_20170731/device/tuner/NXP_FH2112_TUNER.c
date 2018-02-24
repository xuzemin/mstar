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

#ifndef NXP_FN2112_C
#define NXP_FN2112_C

#include <stdio.h>

#include "Board.h"
#include "datatype.h"
#include "drvIIC.h"

#include "drvGPIO.h"

#include "COFDM_Demodulator.h"
#include "Tuner.h"
#include "msAPI_FreqTableATV.h"
#include "msAPI_Tuning.h"
#include "MApp_GlobalSettingSt.h"

#define DIVIDER_RATIO_31_25KHz          0x01
#define DIVIDER_RATIO_50KHz             0x00
#define DIVIDER_RATIO_62_5KHz           0x03
#define DIVIDER_RATIO_166_7KHz          0x02


#define USE_EXTERNAL_RF_AGC        1
#define EN_AGC_CONTROL             1

#if (TN_FREQ_STEP == FREQ_STEP_50KHz)
#define DIVIDER_RATIO      DIVIDER_RATIO_50KHz
#elif (TN_FREQ_STEP == FREQ_STEP_62_5KHz)
#define DIVIDER_RATIO      DIVIDER_RATIO_62_5KHz
#endif

#define  PAL_DBG_MSG(x)  //x

static FREQSTEP m_eFrequencyStep;

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
    BYTE cTunerData[6];
    U16  u16Freq;

    eBand = eBand;
    
    // Write DB1,DB2,CB,BB
    cTunerData[0] = HIBYTE(wPLLData);
    cTunerData[1] = LOBYTE(wPLLData);
    
#if (EN_AGC_CONTROL)
     EXT_RF_AGC_ON();
#endif

    u16Freq = msAPI_CFT_ConvertPLLtoIntegerOfFrequency(wPLLData);

    if ( u16Freq <= 136 )
    {
        cTunerData[2] = 0xBE;
        cTunerData[3] = 0x81;
        cTunerData[4] = 0x9E;
    }
    else if(u16Freq < 166)
    {
        cTunerData[2] = 0xF6;
        cTunerData[3] = 0x81;
        cTunerData[4] = 0xDE;
    }
    else if(u16Freq < 186)
    {
        cTunerData[2] = 0xFE;
        cTunerData[3] = 0x81;
        cTunerData[4] = 0xDE;
    }
    else if(u16Freq < 376)
    {
        cTunerData[2] = 0xBE;
        cTunerData[3] = 0x82;
        cTunerData[4] = 0x9E;
    }
    else if(u16Freq < 416)
    {
        cTunerData[2] = 0xF6;
        cTunerData[3] = 0x82;
        cTunerData[4] = 0xDE;
    }
    else if(u16Freq < 458)
    {
        cTunerData[2] = 0xFE;
        cTunerData[3] = 0x82;
        cTunerData[4] = 0xDE;
    }
    else if(u16Freq < 686)
    {
        cTunerData[2] = 0xBE;
        cTunerData[3] = 0x84;
        cTunerData[4] = 0x9E;
    }
    else if(u16Freq < 836)
    {
        cTunerData[2] = 0xF6;
        cTunerData[3] = 0x84;
        cTunerData[4] = 0xDE;
    }
    else if(u16Freq < 903)
    {
        cTunerData[2] = 0xFE;
        cTunerData[3] = 0x84;
        cTunerData[4] = 0xDE;
    }
    
    cTunerData[5] = 0xE0;

#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD)
    {
        U16 u16Temp = 0x0200;
        u16Temp |=_TUNER_I2C_ID;
        MDrv_IIC_WriteBytes(u16Temp,  0, NULL, sizeof(cTunerData), cTunerData);
    }
#else
    devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, sizeof(cTunerData), cTunerData);
#endif
}

void devTunerInit(void)
{
    BYTE cTunerData[6];

    cTunerData[0] = 0x00;
    cTunerData[1] = 0x00;

#if (EN_AGC_CONTROL)
    EXT_RF_AGC_ON();
#endif

    cTunerData[2] = 0xBE;
    cTunerData[3] = 0x81;
    cTunerData[4] = 0x9E;
    cTunerData[5] = 0xE0;
    
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD)
    U16 u16Temp = 0x0200;
    u16Temp |=_TUNER_I2C_ID;
    MDrv_IIC_WriteBytes(u16Temp,  0, NULL, sizeof(cTunerData), cTunerData);
#else
    devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, sizeof(cTunerData), cTunerData);
#endif
}


#define DIGITAL_TUNER_IF	36

#define DIVIDER_50K               2
#define DIVIDER_62K               0
#define DIVIDER_166K              3

#if ENABLE_T_C_COMBO
extern EN_DVB_TYPE MApp_DVBType_GetCurrentType(void);
#endif

/*************************************************************************
  Subject:    FQD1216 tuner initialized function
  Function:   MDrv_Tuner_Init
  Parmeter:   CONFIG: pointer to tuner address
  Return :    NONE
  Remark: 
**************************************************************************/
void devDigitalTuner_Init()
{
#if (EN_AGC_CONTROL)
    EXT_RF_AGC_OFF();
#endif
}

void devDigitalTuner_SetFreq(double Freq, RF_CHANNEL_BANDWIDTH eBandWidth)
{
    unsigned int value;
    unsigned char CONFIG[6];
    unsigned char u8DivisonRatio;
    
    eBandWidth = eBandWidth;

#if (EN_AGC_CONTROL)
    EXT_RF_AGC_OFF();
    CONFIG[5] = 0xA0;
#endif

    Freq += DIGITAL_TUNER_IF;

#if ENABLE_T_C_COMBO
    if(MApp_DVBType_GetCurrentType() == EN_DVB_C_TYPE)
    {
        u8DivisonRatio = 0x06; //step size = 62.5KHz
        value = (unsigned int)(Freq * 16);
    }
    else
#endif
    {
        u8DivisonRatio = 0x04;  // Step 166.7 Khz   1000/166.7 = 6
        value = (unsigned int)(Freq * 6 + 0.5);
    }

    //DB1
    CONFIG[0] = ( unsigned char ) ( value >> 8 );

    //DB2
    CONFIG[1] = ( unsigned char ) ( value );


    if (Freq <= 136)
    {
        CONFIG[2] = (0xB8|u8DivisonRatio);
        CONFIG[3] = 0x81;
        CONFIG[4] = (0x98|u8DivisonRatio);
    }
    else if (Freq < 166)
    {
        CONFIG[2] = (0xF0|u8DivisonRatio);
        CONFIG[3] = 0x81;
        CONFIG[4] = (0xD8|u8DivisonRatio);
    }
    else if (Freq < 186)
    {
        CONFIG[2] = (0xF8|u8DivisonRatio);
        CONFIG[3] = 0x81;
        CONFIG[4] = (0xD8|u8DivisonRatio);
    }
    else if (Freq < 376)
    {
        CONFIG[2] = (0xB8|u8DivisonRatio);
        CONFIG[3] = 0x82;
        CONFIG[4] = (0x98|u8DivisonRatio);
    }
    else if (Freq < 416)
    {
        CONFIG[2] = (0xF0|u8DivisonRatio);
        CONFIG[3] = 0x82;
        CONFIG[4] = (0xD8|u8DivisonRatio);
    }
    else if (Freq < 458)
    {
        CONFIG[2] = (0xF8|u8DivisonRatio);
        CONFIG[3] = 0x82;
        CONFIG[4] = (0xD8|u8DivisonRatio);
    }
    else if (Freq < 686)
    {
        CONFIG[2] = (0xB8|u8DivisonRatio);
        CONFIG[3] = 0x84;
        CONFIG[4] = (0x98|u8DivisonRatio);
    }
    else if (Freq < 836)
    {
        CONFIG[2] = (0xF0|u8DivisonRatio);
        CONFIG[3] = 0x84;
        CONFIG[4] = (0xD8|u8DivisonRatio);
    }
    else if (Freq < 903)
    {
        CONFIG[2] = (0xF8|u8DivisonRatio);
        CONFIG[3] = 0x84;
        CONFIG[4] = (0xD8|u8DivisonRatio);
    }

#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD)
    {
       U16 u16Temp = 0x0200;
       u16Temp |=_TUNER_I2C_ID;
       MDrv_IIC_WriteBytes(u16Temp, 0, NULL, sizeof(CONFIG), CONFIG);
    }
#else
    devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, sizeof(CONFIG), CONFIG);
#endif
}

#undef NXP_FN2112_C
#endif

