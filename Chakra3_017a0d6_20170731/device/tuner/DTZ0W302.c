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

 [Module Name]: DDT8A1C.c
 [Date]:        30-Aug-2007
 [Comment]:
   CHENGDU XUGUANG's tuner subroutine
 [Reversion History]:
*******************************************************************************/

#ifndef DTZ0W302_C
#define DTZ0W302_C

// System

// Common
#include <stdio.h>

#include "Board.h"
#include "datatype.h"
#include "drvIIC.h"

#include "COFDM_Demodulator.h"

//#include "Tuner.h"

#include "msAPI_FreqTableATV.h"
#include "msAPI_Tuning.h"

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
    BYTE cTunerData[6];
    U16 u16Freq;
    eBand =eBand;
    // Write DB1,DB2,CB,BB
    cTunerData[0] = HIBYTE(wPLLData);
    cTunerData[1] = LOBYTE(wPLLData);

   u16Freq = msAPI_CFT_ConvertPLLtoIntegerOfFrequency(wPLLData);

    cTunerData[2] = 0x85;
    cTunerData[3] = 0x30;
    if ( u16Freq < 342 )
    {
        cTunerData[2] |= CHARGE_PUMP_155uA;
    }
    else if ( u16Freq < 402 )
    {
        cTunerData[2] |= CHARGE_PUMP_330uA;
    }
    else if ( u16Freq < 425 )
    {
        cTunerData[2] |= CHARGE_PUMP_690uA;
    }
    else if ( u16Freq < 752 )
    {
        cTunerData[2] |= CHARGE_PUMP_330uA;
    }
    else if ( u16Freq < 832 )
    {
        cTunerData[2] |= CHARGE_PUMP_690uA;
    }
    else if ( u16Freq < 867 )
    {
        cTunerData[2] |= CHARGE_PUMP_1450uA;
    }
    else
    {
        cTunerData[2] |= CHARGE_PUMP_1450uA;
    }

    if(E_RFBAND_VHF_LOW == eBand)
        cTunerData[3] |= TN_DIG_7M_LOW_BAND;
    else if(E_RFBAND_VHF_HIGH== eBand)
        cTunerData[3] |= TN_DIG_7M_MID_BAND;
    else
        cTunerData[3] |= TN_DIG_7M_HIGH_BAND;

    cTunerData[4] = 0x75;
    if ( u16Freq >= 752 )
        cTunerData[4] |= 0x80;

    cTunerData[5] = 0xB0;
    {
        BYTE i;
        for(i=0;i<6;i++)
            printf("%lx ", (U32)cTunerData[i]);
        printf("\n\r");
    }

    devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 6, cTunerData) ;

}
void devTunerInit(void)
{


}

#define DIGITAL_TUNER_IF    36.125//36.167

void devDigitalTuner_Init()
{
}

void devDigitalTuner_SetFreq ( double Freq, RF_CHANNEL_BANDWIDTH eBandWidth)
{
    unsigned int value;
    unsigned char CONFIG[7];
       //value = ( unsigned int ) ( ( Freq + DIGITAL_TUNER_IF ) * 6);
       value = ( unsigned int ) ( ( Freq + DIGITAL_TUNER_IF ) * 6 + 0.5);
    //DB1
    CONFIG[0] = ( unsigned char ) ( value >> 8 );

    //DB2
    CONFIG[1] = ( unsigned char ) ( value );

    CONFIG[2] = 0x93;
    CONFIG[3] = 0x30;

    if ( ( eBandWidth == E_RF_CH_BAND_6MHz ) || ( eBandWidth == E_RF_CH_BAND_7MHz ) )
      {
        if ( Freq < 155 )
        {
            CONFIG[2] |= CHARGE_PUMP_155uA;
            CONFIG[3] |= TN_DIG_7M_LOW_BAND;
        }
        else if ( Freq < 342 )
        {
            CONFIG[2] |= CHARGE_PUMP_155uA;
            CONFIG[3] |= TN_DIG_7M_MID_BAND;
        }
        else if ( Freq < 402 )
        {
            CONFIG[2] |= CHARGE_PUMP_330uA;
            CONFIG[3] |= TN_DIG_7M_MID_BAND;
        }
        else if ( Freq < 425 )
        {
            CONFIG[2] |= CHARGE_PUMP_690uA;
            CONFIG[3] |= TN_DIG_7M_MID_BAND;
        }
        else if ( Freq < 752 )
        {
            CONFIG[2] |= CHARGE_PUMP_330uA;
            CONFIG[3] |= TN_DIG_7M_HIGH_BAND;
        }
        else if ( Freq < 832 )
        {
            CONFIG[2] |= CHARGE_PUMP_690uA;
            CONFIG[3] |= TN_DIG_7M_HIGH_BAND;
        }
        else
        {
            CONFIG[2] |= CHARGE_PUMP_1450uA;
            CONFIG[3] |= TN_DIG_7M_HIGH_BAND;
        }
    }
    else if ( eBandWidth == E_RF_CH_BAND_8MHz )
    {
        if ( Freq < 155 )
        {
            CONFIG[2] |= CHARGE_PUMP_155uA;
            CONFIG[3] |= TN_DIG_8M_LOW_BAND;
        }
        else if ( Freq < 342 )
        {
            CONFIG[2] |= CHARGE_PUMP_155uA;
            CONFIG[3] |= TN_DIG_8M_MID_BAND;
        }
        else if ( Freq < 402 )
        {
            CONFIG[2] |= CHARGE_PUMP_330uA;
            CONFIG[3] |= TN_DIG_8M_MID_BAND;
        }
        else if ( Freq < 425 )
        {
            CONFIG[2] |= CHARGE_PUMP_690uA;
            CONFIG[3] |= TN_DIG_8M_MID_BAND;
        }
        else if ( Freq < 752 )
        {
            CONFIG[2] |= CHARGE_PUMP_330uA;
            CONFIG[3] |= TN_DIG_8M_HIGH_BAND;
        }
        else if ( Freq < 832 )
        {
            CONFIG[2] |= CHARGE_PUMP_690uA;
            CONFIG[3] |= TN_DIG_8M_HIGH_BAND;
        }
        else
        {
            CONFIG[2] |= CHARGE_PUMP_1450uA;
            CONFIG[3] |= TN_DIG_8M_HIGH_BAND;
        }

    }

    CONFIG[4] = 0X71; //max:0x77   min:0x70
    if ( Freq >= 752 )
        CONFIG[4] |= 0x80;
    CONFIG[5] = 0x80;
    //printf("Freq = %d\n", (int)Freq);
    //printf("Tuner: %bx, %bx, %bx, %bx, %bx,%bx\n", CONFIG[0], CONFIG[1], CONFIG[2], CONFIG[3], CONFIG[4],CONFIG[5]);
    devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 6, CONFIG);

}


#endif
