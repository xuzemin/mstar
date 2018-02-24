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
#include "MApp_GlobalSettingSt_Common.h"

#include "COFDM_Demodulator.h"
#include "NUTUNE_FI4801.h"


#define DIVIDER_RATIO      0x01 //142.86khz

#define DEBUG_PAL_TUNER   0

#define  PAL_DBG_MSG(x)  x
extern EN_ANT_TYPE msAPI_ATV_GetCurrentAntenna(void);

//---------------------------------------------------------------------
void devTunerSetPLLData(WORD wPLLData, RFBAND eBand)
{
     BYTE cTunerData[5];

    cTunerData[0] = HIBYTE(wPLLData);
    cTunerData[1] = LOBYTE(wPLLData);
    cTunerData[2] = 0xc0;//62.5kHz
    cTunerData[3] = 0x40;//set smallest CP

   if (msAPI_ATV_GetCurrentAntenna() == ANT_AIR)
    cTunerData[3] |= 0x8;//selsect AIR RF signal

    if(eBand == E_RFBAND_VHF_LOW)
        cTunerData[3] |= 0x1;
    else if (eBand == E_RFBAND_VHF_HIGH)
        cTunerData[3] |= 0x2;
    else
        cTunerData[3] |= 0x4;
    cTunerData[4] = 0x82;

    //printf("\n ATV  Tuner: %bx,  %bx,  %bx,  %bx ", cTunerData[0], cTunerData[1], cTunerData[2], cTunerData[3]);
      devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 5, cTunerData);
}




void devTunerInit(void)
{
    BYTE cTunerData[5];

    //devTunerSetFreqStep(TN_FREQ_STEP);//Type mismatch,
    cTunerData[0] = 0;
    cTunerData[1] = 0;
    cTunerData[2] = 0xC0; //TN_FREQ_STEP = FREQ_STEP_62_5KHz
    cTunerData[3] = 0x49;
    cTunerData[4] = 0x82;

    devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 5, cTunerData);

}

#define DIGITAL_TUNER_IF    44

void devDigitalTuner_Init()
{
    BYTE cTunerData[5];

    //devTunerSetFreqStep(TN_FREQ_STEP);//Type mismatch,
    cTunerData[0] = 0;
    cTunerData[1] = 0;
    cTunerData[2] = 0xC1; //TN_FREQ_STEP = FREQ_STEP_142_86KHz for Digital
    cTunerData[3] = 0x49;
    cTunerData[4] = 0x82;

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
    U16 value;
//    U8 i;
    unsigned char cTunerData[5];

    eBandWidth = eBandWidth;

    //printf("set to Ch32\n");
    //Freq=578;  //ch34
    //Step 142.86 Khz   1000/142.86 = 7
    value = ( U16 ) ( ( Freq + DIGITAL_TUNER_IF ) * 7 + 0.5);

    //printf("N_pro = %d\n", value);

    //DB1
    cTunerData[0] = ( unsigned char ) ( value >> 8 );

    //DB2
    cTunerData[1] = ( unsigned char ) ( value );

    cTunerData[2] = 0xC1;//142.86KHz

    cTunerData[3] = 0x08; //Air RF Port

	if((U16)Freq<=82)
	cTunerData[3] |= 0x40;
	else if((U16)Freq<=107)
	cTunerData[3] |= 0x60;
	else if((U16)Freq<=132)
	cTunerData[3] |= 0x80;
	else if((U16)Freq<=150)
	cTunerData[3] |= 0xa0;
	else if((U16)Freq<=292)
	cTunerData[3] |= 0x40;
	else if((U16)Freq<=350)
	cTunerData[3] |= 0x60;
	else if((U16)Freq<=402)
	cTunerData[3] |= 0x80;
	else if((U16)Freq<=420)
	cTunerData[3] |= 0xa0;
	else if((U16)Freq<=647)
	cTunerData[3] |= 0x60;
	else if((U16)Freq<=767)
	cTunerData[3] |= 0x80;
	else if((U16)Freq<=860)
	cTunerData[3] |= 0xa0;


    if ( (U16)Freq <= 150 ) // VHF low
        cTunerData[3]|=BAND_SWITCH_VHF_LOW;
    else if( (U16)Freq >= 420)   //UHF
        cTunerData[3]|=BAND_SWITCH_UHF;
    else // VHF high
        cTunerData[3]|=BAND_SWITCH_VHF_HIGH;

    cTunerData[4] = 0x82;

   // printf("add 0x%02x Tuner: 0x%02x,  0x%02x,  0x%02x,  0x%02x,  0x%02x\n", _TUNER_I2C_ID, cTunerData[0], cTunerData[1], cTunerData[2], cTunerData[3], cTunerData[4]);
    devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 5, cTunerData);
}

#undef VA1E1CD2403_C
#endif
