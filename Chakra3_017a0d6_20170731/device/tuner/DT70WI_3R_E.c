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
// Copyright (c) 2006-2008 MStar Semiconductor, Inc.
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

#ifndef TDTC_G001D_C
#define TDTC_G001D_C

#include <stdio.h>

//#include "board.h"
//#include "DataType.h"
#include "drvIIC.h"
//#include "drvTimer.h"

//#include "cofdm_demodulator.h"
#include "Tuner.h"
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

	if ( u16Freq < 180 )
	{
		cTunerData[2] = 0xbe;
		cTunerData[4] = 0x9e;
	}
	else if ( u16Freq < 197 )
	{
		cTunerData[2] = 0xf6;
		cTunerData[4] = 0xde;
	}
	else if ( u16Freq < 366 )
	{
		cTunerData[2] = 0xbe;
		cTunerData[4] = 0x9e;
	}
	else if ( u16Freq < 484 )
	{
		cTunerData[2] = 0xf6;
		cTunerData[4] = 0xde;
	}
	else if ( u16Freq < 646 )
	{
		cTunerData[2] = 0xbe;
		cTunerData[4] = 0x9e;
	}
	else if ( u16Freq < 830 )
	{
		cTunerData[2] = 0xf6;
		cTunerData[4] = 0xde;
	}
	else
	{
		cTunerData[2] = 0xfe;
		cTunerData[4] = 0xde;
	}

	if(E_RFBAND_VHF_LOW == eBand)
		cTunerData[3] = 0x09;
	else if(E_RFBAND_VHF_HIGH == eBand)
		cTunerData[3] = 0x0a;
	else
		cTunerData[3] = 0x0c;

	cTunerData[5] = 0x60;
       //printf("Tuner: %bx, %bx, %bx, %bx,%bx\n", cTunerData[0], cTunerData[1], cTunerData[2], cTunerData[3],cTunerData[4]);

    {
        U16 u16Temp=0x0200;

        u16Temp|=_TUNER_I2C_ID;
        MDrv_IIC_WriteBytes(u16Temp,  0, NULL, 6, cTunerData);
    }

}



void devTunerInit(void)
{

}

#define DIGITAL_TUNER_IF    36.13

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
	unsigned char CONFIG[7];

	value = ( unsigned int ) ( (Freq + DIGITAL_TUNER_IF) * 1000 / TN_DIGITAL_FREQ_STEP +0.5);

	CONFIG[0] = _TUNER_I2C_ID;
	//DB1
	CONFIG[1] = ( unsigned char ) ( value >> 8 );

	//DB2
	CONFIG[2] = ( unsigned char ) ( value );

	if ( ( eBandWidth == E_RF_CH_BAND_6MHz ) || ( eBandWidth == E_RF_CH_BAND_7MHz ) )
    {
        if ( ( Freq + DIGITAL_TUNER_IF ) < 180 )
        {
    		CONFIG[3] = 0xbc;
        	CONFIG[4] = 0x01;
			CONFIG[5] = 0x9c;
        }
        else if ( ( Freq + DIGITAL_TUNER_IF ) < 197 )
        {
    		CONFIG[3] = 0xf4;
        	CONFIG[4] = 0x01;
			CONFIG[5] = 0xdc;
        }
        else if ( ( Freq + DIGITAL_TUNER_IF ) < 366 )
        {
    		CONFIG[3] = 0xbc;
        	CONFIG[4] = 0x02;
			CONFIG[5] = 0x9c;
        }
        else if ( ( Freq + DIGITAL_TUNER_IF ) < 484 )
        {
    		CONFIG[3] = 0xf4;
        	CONFIG[4] = 0x02;
			CONFIG[5] = 0xdc;
        }
        else if ( ( Freq + DIGITAL_TUNER_IF ) < 646 )
        {
    		CONFIG[3] = 0xbc;
        	CONFIG[4] = 0x04;
			CONFIG[5] = 0x9c;
        }
        else if ( ( Freq + DIGITAL_TUNER_IF ) < 830 )
        {
    		CONFIG[3] = 0xf4;
        	CONFIG[4] = 0x04;
			CONFIG[5] = 0xdc;
        }
        else
        {
    		CONFIG[3] = 0xfc;
        	CONFIG[4] = 0x04;
			CONFIG[5] = 0xdc;
        }
    }
    else if ( eBandWidth == E_RF_CH_BAND_8MHz )
    {
    	if ( ( Freq + DIGITAL_TUNER_IF ) < 180 )
    	{
    		CONFIG[3] = 0xbc;
    		CONFIG[4] = 0x09;
			CONFIG[5] = 0x9c;
    	}
    	else if ( ( Freq + DIGITAL_TUNER_IF ) < 197 )
    	{
    		CONFIG[3] = 0xf4;
    		CONFIG[4] = 0x09;
			CONFIG[5] = 0xdc;
    	}
    	else if ( ( Freq + DIGITAL_TUNER_IF ) < 366 )
    	{
    		CONFIG[3] = 0xbc;
    		CONFIG[4] = 0x0a;
			CONFIG[5] = 0x9c;
    	}
    	else if ( ( Freq + DIGITAL_TUNER_IF ) < 484 )
    	{
    		CONFIG[3] = 0xf4;
    		CONFIG[4] = 0x0a;
			CONFIG[5] = 0xdc;
    	}
    	else if ( ( Freq + DIGITAL_TUNER_IF ) < 646 )
    	{
    		CONFIG[3] = 0xbc;
    		CONFIG[4] = 0x0c;
			CONFIG[5] = 0x9c;
    	}
    	else if ( ( Freq + DIGITAL_TUNER_IF ) < 830 )
    	{
    		CONFIG[3] = 0xf4;
    		CONFIG[4] = 0x0c;
			CONFIG[5] = 0xdc;
    	}
    	else
    	{
    		CONFIG[3] = 0xfc;
    		CONFIG[4] = 0x0c;
			CONFIG[5] = 0xdc;
    	}
    }

    CONFIG[6] = 0x20;

	switch ( eBandWidth )
	{
		case E_RF_CH_BAND_6MHz:
			CLRBIT( CONFIG[4], 3 );
			break;

		case E_RF_CH_BAND_7MHz:
			CLRBIT( CONFIG[4], 3 );
			break;

		case E_RF_CH_BAND_8MHz:
			SETBIT( CONFIG[4], 3 );
			break;
        default:
            break;
	}
{
        U16 u16Temp=0x0200;

        u16Temp|=_TUNER_I2C_ID;

        MDrv_IIC_WriteBytes(u16Temp,  0, NULL,6, &CONFIG[1]);
}
    //printf("Freq = %d\n", (int)Freq);
    //printf("Tuner: %bx, %bx, %bx, %bx, %bx\n", CONFIG[1], CONFIG[2], CONFIG[3], CONFIG[4], CONFIG[5]);
//	devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 5, &CONFIG[1]);
}

#undef TDTC_G001D_C
#endif


