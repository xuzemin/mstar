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
// Copyright (c) 2006-2007 MStar Semiconductor, Inc.
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
 Copyright (c) 2008 MStar Semiconductor, Inc.
 All rights reserved.

 [Module Name]: DTZ0W302G.c
 [Date]:        02-JUN-2008
 [Comment]:
   CHONGQING QINGJIA's tuner subroutine
 [Reversion History]:
*******************************************************************************/

#ifndef DTI1E4I1VH_C
#define DTI1E4I1VH_C

// System

// Common
#include <stdio.h>

#include "drvIIC.h"

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
    BYTE cTunerData[5];
    U16 u16Freq;
    eBand =eBand;

    // Write DB1,DB2,CB,BB
    cTunerData[0] = HIBYTE(wPLLData);
    cTunerData[1] = LOBYTE(wPLLData);
	cTunerData[2]  = 0xa3;//0xB3;

   u16Freq = msAPI_CFT_ConvertPLLtoIntegerOfFrequency(wPLLData-msAPI_Tuner_GetIF());
	if(eBand == E_RFBAND_VHF_LOW)
     {  
            cTunerData[3] = 0x51;
     }
    else if(eBand == E_RFBAND_VHF_HIGH)
    {
        if ( u16Freq <= 300 )
        {
            cTunerData[3] = 0x52;
        }
        else  
        {
            cTunerData[3] = 0x92;
        }

    }
    else
    {
        if ( u16Freq <= 700 )
        {
            cTunerData[3] = 0x88;
        }
        else
        {
	            cTunerData[3] = 0x48;//0xC8;//
        }
    }
	
	if(msAPI_Tuner_IsTuningProcessorBusy())
		cTunerData[4] = 0xe2;//0xc3;
	else
		cTunerData[4] = 0xc3;//0xc3;
	
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD)
    {
        U16 u16Temp=0x0200;

        u16Temp|=_TUNER_I2C_ID;
        MDrv_IIC_WriteBytes(u16Temp,  0, NULL, 5, cTunerData);
    }
#else
    devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 4, cTunerData);
#endif
}

void devTunerInit(void)
{


}

#define DIGITAL_TUNER_IF	36.000

void devDigitalTuner_Init()
{
      unsigned char DataInit[5];

	DataInit[0] = 0x00;  
	DataInit[1] = 0x00;
	DataInit[2] = 0x80;  
	DataInit[3] = 0x62;
	DataInit[4] = 0xe2;
	#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD)
    	{
        	U16 u16Temp=0x0200;

        	u16Temp|=_TUNER_I2C_ID;
        	MDrv_IIC_WriteBytes(u16Temp,  0, NULL, 5, DataInit);
    	}
 	#else
    		devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 5, CONFIG);
	#endif
}


void devDigitalTuner_SetFreq ( double Freq, RF_CHANNEL_BANDWIDTH eBandWidth)
{
	unsigned int value;
	unsigned char CONFIG[5];

	value = ( unsigned int ) ( ( Freq + DIGITAL_TUNER_IF ) * 6 + 0.5);

	//CONFIG[0]=_TUNER_I2C_ID;
	//DB1
	CONFIG[0] = ( unsigned char ) ( value >> 8 );

	//DB2
	CONFIG[1] = ( unsigned char ) ( value );
 	CONFIG[2] = 0x80;
	 if ( ( Freq + DIGITAL_TUNER_IF ) < 474 )
        	CONFIG[3] =0x62;
	 else if( ( Freq + DIGITAL_TUNER_IF ) < 642)
	 	CONFIG[3] = 0xa8;
	 else
	 	CONFIG[3] = 0xe8;
 	switch ( eBandWidth )
	{
	       case E_RF_CH_BAND_7MHz:
			//CLRBIT( CONFIG[4], 4 );
			SETBIT( CONFIG[3], 4 );
			break;
			
		case E_RF_CH_BAND_8MHz:
			//SETBIT( CONFIG[4], 4 );
			CLRBIT( CONFIG[3], 4 );
			break;
			
		default:
                    break;
	
	}
	  	CONFIG[4] = 0xe2;

    #if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD)
    {
        	U16 u16Temp=0x0200;

        	u16Temp|=_TUNER_I2C_ID;
        	MDrv_IIC_WriteBytes(u16Temp,  0, NULL, 5, CONFIG);
    }
    #else
    		devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 5, CONFIG);
    #endif
    printf( "frequency=%d \n" ,Freq) ;
}

#endif
