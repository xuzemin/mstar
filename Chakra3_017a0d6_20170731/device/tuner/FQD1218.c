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

/******************************************************************************
 Copyright (c) 2007 MStar Semiconductor, Inc.
 All rights reserved.

 [Module Name]: DevTuner.c
 [Date]:        24-oct-2007
 [Comment]:
   TV tuner subroutines.
 [Reversion History]: del 1667KHz step
*******************************************************************************/

#define FQD1218_C

// System

// Common
#include <stdio.h>

#include "Board.h"
#include "datatype.h"
#include "Drviic.h"

#include "COFDM_Demodulator.h"

#include "FQD1218.h"

#define DIVIDER_RATIO_62_5KHz   0x06

#define DIVIDER_RATIO      DIVIDER_RATIO_62_5KHz

static FREQSTEP m_eFrequencyStep;

void devTunerSetFreqStep(FREQSTEP eFreqStep)
{
    switch(eFreqStep)
    {
    //case fqs31_25KHz:
    case FREQSTEP_62_5KHz:
    //case fqs50KHz:
        m_eFrequencyStep = eFreqStep;
        break;

    default:
        m_eFrequencyStep = FREQSTEP_62_5KHz;
        break;
    }
}


void devTunerSetPLLData(WORD wPLLData, RFBAND eBand)
{
    BYTE cTunerData[5];

    BYTE i=    eBand;

    double Freq;

    if(DIVIDER_RATIO == DIVIDER_RATIO_62_5KHz)
        Freq = wPLLData * 0.0625;

    // Set PLL
    cTunerData[0] = HIBYTE(wPLLData);
    cTunerData[1] = LOBYTE(wPLLData);

    // set AB Byte
      cTunerData[2]= 0xDE;
      cTunerData[3]= 0x60;
    devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 4, cTunerData);


     if (Freq <= 180.00)
     {
        cTunerData[2] = 0x80|DIVIDER_RATIO; cTunerData[3] = 0x01;
     }
     else if (Freq <= 194.125)
     {
        cTunerData[2] = 0xC0|DIVIDER_RATIO; cTunerData[3] = 0x01;
     }
     else if (Freq <= 470.00)
     {
        cTunerData[2] = 0x80|DIVIDER_RATIO; cTunerData[3] = 0x02;
     }
     else if (Freq <= 479.125)
     {
        cTunerData[2] = 0xC0|DIVIDER_RATIO; cTunerData[3] = 0x02;
     }
     else if (Freq <= 855.00)
     {
        cTunerData[2] = 0x80|DIVIDER_RATIO; cTunerData[3] = 0x04;
     }
     else if (Freq <= 903.125)
     {
        cTunerData[2] = 0xC0|DIVIDER_RATIO; cTunerData[3] = 0x04;
     }
     devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 4, cTunerData);
}

void devTunerInit(void)
{
}

#define DIGITAL_TUNER_IF    36.13
#define IF_Tuner_Address   0x86

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
/*************************************************************************
  Subject:    FQD1218 tuner digital if  set  function
  Function:   void ifdmSetDigitalIF(void)
  Parmeter:   NONE
  Return :    NONE
  Remark:
**************************************************************************/
void ifdmSetDigitalIF(void)
{
    BYTE DIGITA_IF[11];

    DIGITA_IF[0]=0x00;
    DIGITA_IF[1]=0x00;
    DIGITA_IF[2]=0x00;
    DIGITA_IF[3]=0x00;
    DIGITA_IF[4]=0x67;
    DIGITA_IF[5]=0x1f;
    DIGITA_IF[6]=0x01;
    DIGITA_IF[7]=0x00;
    DIGITA_IF[8]=0x00;
    DIGITA_IF[9]=0x00;
    DIGITA_IF[10]=0x00;

    devCOFDM_PassThroughI2C_WriteBytes(IF_Tuner_Address, 0, NULL, 11, DIGITA_IF);
}

//------------------------------------------------------------------------------
//  Subject:    FQD1218 tuner paremeter write
//  Function:   Set_Digital_TUNER
//  Parmeter:   Freq: "RF+IF" in MHz
//                 eBandWidth: 6MHZ, 7MHZ, 8MHZ
//                 CONFIG: pointer to tuner address
//  Return :    NONE
//  Remark:
//------------------------------------------------------------------------------
void devDigitalTuner_SetFreq ( double Freq, RF_CHANNEL_BANDWIDTH eBandWidth)
{
    unsigned int value;
    unsigned char CONFIG[5];

    eBandWidth=eBandWidth;//remove warning
    value = ( unsigned int ) ( ( Freq + DIGITAL_TUNER_IF ) * 6);
    //CONFIG[0]=_TUNER_I2C_ID;
    //DB1
    CONFIG[0] = ( unsigned char ) ( value >> 8 );

    //DB2
    CONFIG[1] = ( unsigned char ) ( value );

    // set AB Byte
      CONFIG[2]= 0xDC;
      CONFIG[3]= 0x20;
    devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 4, CONFIG);

    // always init tuner here because annalog will chane the init value
    // todo: consider app flow, don't init value every channel change.
    //MDrv_Tuner_Init();

    //if(eBandWidth==E_RF_CH_BAND_8MHz)
    {
        //VHF LOW
        if((Freq+DIGITAL_TUNER_IF)<=180)
        {
            CONFIG[2] = 0xBC;
            CONFIG[3]= 0x01;

        }
        //VHF  HIGH
        else if((Freq+DIGITAL_TUNER_IF)<=193.13)
        {
            CONFIG[2] = 0xF4;
            CONFIG[3]= 0x01;
        }
        else if((Freq+DIGITAL_TUNER_IF)<=366)
        {
            CONFIG[2] = 0xBC;
            CONFIG[3]= 0x02;
        }
        else if((Freq+DIGITAL_TUNER_IF)<=478.13)
        {
            CONFIG[2] = 0xF4;;
            CONFIG[3]= 0x02;
        }
        //UHF
        else if((Freq+DIGITAL_TUNER_IF)<=662)
        {
            CONFIG[2] = 0xBC;
            CONFIG[3]= 0x04;
        }
        else if((Freq+DIGITAL_TUNER_IF)<=840)
        {
            CONFIG[2] = 0xF4;
            CONFIG[3]= 0x04;
        }
        else
        {
            CONFIG[2] = 0xFC;
            CONFIG[3]= 0x04;
        }
    }
    //printf("Tuner:%bx, %bx, %bx, %bx, %bx\n", CONFIG[0], CONFIG[1], CONFIG[2], CONFIG[3], CONFIG[4]);
    devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 4, CONFIG);
    ifdmSetDigitalIF();
}


#undef FQD1218_C

