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

#define FQD1116_C

// System

// Common
#include <stdio.h>

#include "Board.h"
#include "datatype.h"
#include "Drviic.h"

#include "COFDM_Demodulator.h"

#include "FQD1116.h"
//#include "SWI2C.h"

#define DIVIDER_RATIO_62_5KHz   0x08
//#define DIVIDER_RATIO_166_7KHz  0x0A
//#define DIVIDER_RATIO_50KHz     0x0B

#if (TN_FREQ_STEP == FREQ_STEP_50KHz)
#define DIVIDER_RATIO      DIVIDER_RATIO_50KHz
#define LO_BAND_MID1    0x16A8
#define LO_BAND_MID2    0x20D0
#define LO_BAND_HIGH1    0x3070
#define LO_BAND_HIGH2    0x40D8
#elif (TN_FREQ_STEP == FREQ_STEP_62_5KHz)
#define DIVIDER_RATIO      DIVIDER_RATIO_62_5KHz
#define LO_BAND_MID1    0x1220
#define LO_BAND_MID2    0x1A40
#define LO_BAND_HIGH1    0x26C0
#define LO_BAND_HIGH2    0x33E0
#endif
#define DEBUG_PAL_TUNER   0

#define  PAL_DBG_MSG(x)  x


static FREQSTEP m_eFrequencyStep;

void devTunerSetFreqStep(FREQSTEP eFreqStep)
{
    switch(eFreqStep)
    {
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
    BYTE CONFIG[6];
      double Freq;

       eBand = eBand; //To remove  warning

    if(DIVIDER_RATIO == DIVIDER_RATIO_62_5KHz)
        Freq = wPLLData * 0.0625;

    // Write DB1,DB2
    CONFIG[0] = HIBYTE(wPLLData);
    CONFIG[1] = LOBYTE(wPLLData);

    //CB1(D/A=1)
    CONFIG[2] = 0xC8;

      //CONFIG[3] = CB2
                if (((Freq ) >= 84.00) && ((Freq  ) <= 126.00))
                 {
                    CONFIG[3] = 0x81;
                 }
                 else if (((Freq  ) <= 150.00))
                 {
                    CONFIG[3]  = 0xA1;
                 }
                 else if (((Freq  ) <= 175.00))
                 {
                    CONFIG[3]  = 0xC1;
                 }
                 else if ( ((Freq  ) <= 193.00))
                 {
                    CONFIG[3]  = 0xE1;
                 }
                 else if (((Freq  ) <= 306.00))
                 {
                    CONFIG[3]  = 0x82;
                 }
                 else if (((Freq  ) <= 386.00))
                 {
                    CONFIG[3]  = 0xA2;
                 }
                 else if ( ((Freq  ) <= 435.00))
                 {
                    CONFIG[3]  = 0xC2;
                 }//
                 else if ( ((Freq ) <= 480.00))
                 {
                    CONFIG[3]  = 0xE2;
                 }
                 else if (((Freq  ) <= 636.00))
                 {
                    CONFIG[3]  = 0x84;
                 }
                 else if (((Freq  ) <= 736.00))
                 {
                    CONFIG[3]  = 0xA4;
                 }
                 else if ( ((Freq  ) <= 836.00))
                 {
                    CONFIG[3]  = 0xC4;
                 }
                 else if (((Freq  ) <= 904.00))
                 {
                    CONFIG[3]  = 0xE4;
                 }
               //end
      //CONFIG[4] = CB1(D/A=0)
    CONFIG[4] =0x86;

      //CONFIG[5] = CB2
    CONFIG[5] =CONFIG[3];


    devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 6, CONFIG);
}




void devTunerInit(void)
{
    BYTE cTunerData[5];

    //devTunerSetFreqStep(TN_FREQ_STEP); //Type mismatch,
    cTunerData[0] = 0;
    cTunerData[1] = 0;
    cTunerData[2] = 0xC0|DIVIDER_RATIO;
    cTunerData[3] = 0x69;
    cTunerData[4] = 0x86;
    devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 5, cTunerData);
}

#define DIGITAL_TUNER_IF    36.13
#define IF_Tuner_Address   0x86

/*************************************************************************
  Subject:    FQD1116 tuner initialized function
  Function:   MDrv_Tuner_Init
  Parmeter:   CONFIG: pointer to tuner address
  Return :    NONE
  Remark:
**************************************************************************/
void devDigitalTuner_Init()
{
    unsigned char CONFIG[6];
    CONFIG[0] = 00;
    CONFIG[1] = 00;
    CONFIG[2] = 0xBC;
    CONFIG[3] = 0x01; // Take Over Point
    CONFIG[4] = 0x50;
    devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 5, CONFIG);
}
/*************************************************************************
  Subject:    FQD1116 tuner digital if  set  function
  Function:   void ifdmSetDigitalIF(void)
  Parmeter:   NONE
  Return :    NONE
  Remark:
**************************************************************************/
void ifdmSetDigitalIF(void)
{
    BYTE DIGITA_IF[11];

    DIGITA_IF[0]=0x00;//Sub address
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
//  Subject:    FQD1116 tuner paremeter write
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

      unsigned char CONFIG[6];

    // always init tuner here because annalog will chane the init value
    // todo: consider app flow, don't init value every channel change.
    //MDrv_Tuner_Init();
    eBandWidth=eBandWidth;//remove warning
    value = ( unsigned int ) ( ( Freq + DIGITAL_TUNER_IF ) * 6);

    //DB1
    CONFIG[0] = ( unsigned char ) ( value >> 8 );
    //DB2
    CONFIG[1] = ( unsigned char ) ( value );
    //CB1(D/A=1)
    CONFIG[2] = 0xCA;



      //CONFIG[3] = CB2
                if (((Freq + DIGITAL_TUNER_IF) >= 84.00) && ((Freq + DIGITAL_TUNER_IF) <= 126.00))
                 {
                    CONFIG[3] = 0x41;
                 }
                 else if ( ((Freq + DIGITAL_TUNER_IF) <= 150.00))
                 {
                    CONFIG[3]  = 0x61;
                 }
                 else if ( ((Freq + DIGITAL_TUNER_IF) <= 175.00))
                 {
                    CONFIG[3]  = 0x81;
                 }
                 else if (((Freq + DIGITAL_TUNER_IF) <= 193.00))
                 {
                    CONFIG[3]  = 0xC1;
                 }
                 else if (((Freq + DIGITAL_TUNER_IF) <= 336.00))
                 {
                    CONFIG[3]  = 0x42;
                 }
                 else if (((Freq + DIGITAL_TUNER_IF) <= 393.00))
                 {
                    CONFIG[3]  = 0x62;
                 }
                 else if (((Freq + DIGITAL_TUNER_IF) <= 425.00))
                 {
                    CONFIG[3]  = 0x82;
                 }//
                 else if (((Freq + DIGITAL_TUNER_IF) <= 456.00))
                 {
                    CONFIG[3]  = 0xA2;
                 }
                 else if (((Freq + DIGITAL_TUNER_IF) <= 480.00))
                 {
                    CONFIG[3]  = 0xC2;
                 }
                 else if ( ((Freq + DIGITAL_TUNER_IF) <= 691.00))
                 {
                    CONFIG[3]  = 0x64;
                 }
                 else if ( ((Freq + DIGITAL_TUNER_IF) <= 811.00))
                 {
                    CONFIG[3]  = 0x84;
                 }
                 else if (((Freq + DIGITAL_TUNER_IF) <= 859.00))
                 {
                    CONFIG[3]  = 0xA4;
                 }
                 else if (((Freq + DIGITAL_TUNER_IF) <= 896.00))
                 {
                    CONFIG[3]  = 0xE4;
                 }//end
      //CONFIG[4] = CB1(D/A=0)
    CONFIG[4] =0x88;//modified by demod vendor laser

      //CONFIG[5] = CB2
    CONFIG[5] =CONFIG[3];







        //printf("Tuner:%bx, %bx, %bx, %bx, %bx\n", CONFIG[0], CONFIG[1], CONFIG[2], CONFIG[3], CONFIG[4]);

        devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 6, CONFIG);
        ifdmSetDigitalIF();
}


#undef FQD1116_C

