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
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define VA1E1CD2403_C
#ifndef SHARP_C
#define SHARP_C

// System

// Common
#include <stdio.h>

#include "Board.h"
#include "datatype.h"
//#include "Drviic.h"

#include "COFDM_Demodulator.h"
#include "VA1E1CD2403.h"


#define DIVIDER_RATIO      0x00 //166.7khz

#define DEBUG_PAL_TUNER   0

#define  PAL_DBG_MSG(x)  x


static FREQSTEP m_eFrequencyStep;

void devTunerSetFreqStep(FREQSTEP eFreqStep)
{
    switch(eFreqStep)
    {
    case FREQSTEP_50KHz:
        m_eFrequencyStep = eFreqStep;
        break;

    default:
        m_eFrequencyStep = FREQSTEP_50KHz;
        break;
    }
}

//---------------------------------------------------------------------
void devTunerSetPLLData(WORD wPLLData, RFBAND eBand)
{
     BYTE cTunerData[5];

    cTunerData[0] = HIBYTE(wPLLData);
    cTunerData[1] = LOBYTE(wPLLData);

#if ( TN_FREQ_STEP == FREQ_STEP_166_67KHz)
      cTunerData[2] = 0x80 | 0x38;//Disable internal RF AGC by jiangtao 2009-12-21
#else  //default 50Khz
      cTunerData[2] = 0x87 | 0x38;//Disable internal RF AGC by jiangtao 2009-12-21
#endif

    if(eBand == E_RFBAND_VHF_LOW)
          cTunerData[3] = 0x91;
    else if (eBand == E_RFBAND_VHF_HIGH)
        cTunerData[3] = 0x92;
    else
        cTunerData[3] = 0x94;
    cTunerData[4] = 0xDD;

//    printf("\n ATV  Tuner: %bx,  %bx,  %bx,  %bx ", cTunerData[0], cTunerData[1], cTunerData[2], cTunerData[3]);
      devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 5, cTunerData);
}




void devTunerInit(void)
{
    BYTE cTunerData[5];

    //devTunerSetFreqStep(TN_FREQ_STEP);//Type mismatch,
    cTunerData[0] = 0;
    cTunerData[1] = 0;
    cTunerData[2] = 0x87;
    cTunerData[3] = 0x91;
    cTunerData[4] = 0xDD;

    devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 5, cTunerData);

}

#define DIGITAL_TUNER_IF    36.166

void devDigitalTuner_Init()
{
    BYTE cTunerData[5];

    //devTunerSetFreqStep(TN_FREQ_STEP);//Type mismatch,
    cTunerData[0] = 0;
    cTunerData[1] = 0;
    cTunerData[2] = 0x80|DIVIDER_RATIO;
    cTunerData[3] = 0x91;
    cTunerData[4] = 0xD1;

    devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 5, cTunerData);
}

/*************************************************************************
  Subject:   SHARP tuner paremeter write
  Function:   Set_Digital_TUNER
  Parmeter:   Freq: "RF+IF" in MHz
                 eBandWidth: BW_MODE_6MHZ, BW_MODE_7MHZ, BW_MODE_8MHZ
                 CONFIG: pointer to tuner address
  Return :    NONE
  Remark:
**************************************************************************/
#define BAND_SWITCH_UHF           0x04
#define BAND_SWITCH_VHF_HIGH      0x02
#define BAND_SWITCH_VHF_LOW       0x01

#define DIVIDER_166K              0
#define DIVIDER_50K               7

void devDigitalTuner_SetFreq ( double Freq, RF_CHANNEL_BANDWIDTH eBandWidth)
{
    unsigned int value;
//    U8 i;
    unsigned char CONFIG[6];

    eBandWidth = eBandWidth;

    printf("set freq %dM\n",(U16)Freq);

    //printf("set to Ch32\n");
    //Freq=578;  //ch34
    //eBandWidth=3;  //8M
    // Step 166.7 Khz   1000/166.7 = 6
//    value = ( unsigned int ) ( ( Freq + DIGITAL_TUNER_IF ) * 20);
    value = ( unsigned int ) ( ( Freq + DIGITAL_TUNER_IF ) * 6);  //VA1T1ED-60606



    //DB1
    CONFIG[0] = ( unsigned char ) ( value >> 8 );

    //DB2
    CONFIG[1] = ( unsigned char ) ( value );

    CONFIG[2] = 0x80 | DIVIDER_166K;

    CONFIG[3] = 0x90;

    if ( (U16)Freq <= (U16)(VHF_LOWMAX_FREQ/1000) ) // VHF low
        CONFIG[3]|=BAND_SWITCH_VHF_LOW;
    else if( (U16)Freq >= (U16)(UHF_MIN_FREQ/1000))   //UHF
        CONFIG[3]|=BAND_SWITCH_UHF;
    else // VHF high
        CONFIG[3]|=BAND_SWITCH_VHF_HIGH;

    CONFIG[4] = 0xD1;

    //printf("add 0x%02x Tuner: 0x%02x,  0x%02x,  0x%02x,  0x%02x,  0x%02x\n", _TUNER_I2C_ID, CONFIG[0], CONFIG[1], CONFIG[2], CONFIG[3], CONFIG[4]);
    devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 5, CONFIG);
}

#undef VA1E1CD2403_C
#endif
