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

#ifndef _MxL_301_S
#define _MxL_301_S

#include <stdio.h>

#include "Board.h"
#include "datatype.h"
#include "drvIIC.h"
#include "msAPI_Timer.h"
#include "COFDM_Demodulator.h"
#include "Tuner.h"
#include "msAPI_FreqTableATV.h"
#include "msAPI_Tuning.h"
#include "drvGPIO.h"


#ifndef MHz
	#define MHz 1000000
#endif
#define Mxl_IF1	0x01
#define MxLIF2	0x02
#define MxLIF_PATH Mxl_IF1
extern IF_FREQ MDrv_IFDM_GetIF(void);

void devTunerSetPLLData(WORD wPLLData, RFBAND eBand)
{
        double dRFfreq;
	 MxLxxxRF_TunerConfigS MxL_tuner;
	 IF_FREQ CurrentStandard;
        UNUSED(eBand);
	
        #if (TN_FREQ_STEP == FREQ_STEP_62_5KHz)
        dRFfreq = (double)((wPLLData-msAPI_Tuner_GetIF())*62.5);
        #elif (TN_FREQ_STEP == FREQ_STEP_50KHz)
        dRFfreq = (double)((wPLLData-msAPI_Tuner_GetIF())*50);
        #else
        dRFfreq = (double)((wPLLData-msAPI_Tuner_GetIF())*31.25);
        #endif 
	MxL_tuner.RF_Freq_Hz=dRFfreq*1000;  
	CurrentStandard=MDrv_IFDM_GetIF();
	switch(CurrentStandard)
		{
		case IF_FREQ_B:
		case IF_FREQ_G:
			MxL_tuner.Mode=MxL_MODE_ANA_BG;
			MxL_tuner.BW_MHz=MxL_BW_8MHz;
			MxL_tuner.RF_Freq_Hz+=2750000ul; //if freq offset
			break;
		case IF_FREQ_I:
			MxL_tuner.Mode=MxL_MODE_ANA_I;
			MxL_tuner.BW_MHz=MxL_BW_8MHz;
			MxL_tuner.RF_Freq_Hz+=2750000ul;
			break;
		case IF_FREQ_DK:
		case IF_FREQ_L:
			MxL_tuner.Mode=MxL_MODE_ANA_DKL;
			MxL_tuner.BW_MHz=MxL_BW_8MHz;
			MxL_tuner.RF_Freq_Hz+=2750000ul;
			break;
		case IF_FREQ_L_PRIME:
			MxL_tuner.Mode=MxL_MODE_ANA_SECAM_ACC;
			MxL_tuner.BW_MHz=MxL_BW_8MHz;
			MxL_tuner.RF_Freq_Hz-=2750000ul;
			break;
		case IF_FREQ_MN:	
			MxL_tuner.Mode=MxL_MODE_ANA_MN;
			MxL_tuner.BW_MHz=MxL_BW_6MHz;
			MxL_tuner.RF_Freq_Hz+=1750000ul;
			break;
		default:
			MxL_tuner.Mode=MxL_MODE_ANA_BG;
			MxL_tuner.BW_MHz=MxL_BW_8MHz;
			MxL_tuner.RF_Freq_Hz+=2750000ul;
			break;
		}
		
   MxL_tuner.I2C_Addr=MxL_I2C_ADDR_96;   
   MxL_tuner.TunerID = MxL_TunerID_MxL301RF;   
   MxL_tuner.IF_Freq=MxL_IF_6_MHZ;
   MxL_tuner.IF_Spectrum=MxL_INVERT_IF;
   #if (MxLIF_PATH==Mxl_IF1)
   MxL_tuner.IF_Path=MxL_IF_PATH1;
   MxL_tuner.AGC = MxL_AGC_SEL1;
   #else
   MxL_tuner.IF_Path=MxL_IF_PATH2;
   MxL_tuner.AGC = MxL_AGC_SEL2;
   #endif
   MxL_tuner.Xtal_Freq = MxL_XTAL_24_MHZ;
   MxL_tuner.ClkOut_Setting = MxL_CLKOUT_DISABLE;
   MxL_tuner.ClkOut_Amp=MxL_CLKOUT_AMP_0;
   MxL_tuner.Xtal_Cap = MxL_XTAL_CAP_12_PF;  
   MxL_tuner.IF_Split=MxL_IF_SPLIT_DISABLE;
    MxL_Tuner_Init(&MxL_tuner);
   //printf("SetAnalogl\n");
    MxL_Tuner_RFTune(&MxL_tuner,MxL_tuner.RF_Freq_Hz, MxL_tuner.BW_MHz);

}

void devTunerInit(void)
{
   MxLxxxRF_TunerConfigS MxL_tuner;
   MxLxxxRF_ChipVersion ChipVer;
   MxL_tuner.I2C_Addr=MxL_I2C_ADDR_96;
   MxL_tuner.BW_MHz=MxL_BW_8MHz;
   MxL_tuner.Mode=MxL_MODE_ANA_BG;
   MxL_tuner.TunerID = MxL_TunerID_MxL301RF;
   MxL_tuner.IF_Freq=MxL_IF_6_MHZ;
   MxL_tuner.IF_Spectrum=MxL_INVERT_IF;
   MxL_tuner.Xtal_Freq = MxL_XTAL_24_MHZ;
   MxL_tuner.ClkOut_Setting = MxL_CLKOUT_DISABLE;
   MxL_tuner.ClkOut_Amp=MxL_CLKOUT_AMP_0;
   MxL_tuner.Xtal_Cap = MxL_XTAL_CAP_12_PF;
   #if (MxLIF_PATH==Mxl_IF1)
   MxL_tuner.IF_Path=MxL_IF_PATH1;
   MxL_tuner.AGC = MxL_AGC_SEL1;
   #else
   MxL_tuner.IF_Path=MxL_IF_PATH2;
   MxL_tuner.AGC = MxL_AGC_SEL2;
   #endif
   MxL_tuner.IF_Split=MxL_IF_SPLIT_DISABLE;
   MxL_tuner.RF_Freq_Hz=87000000;
    MxL_Tuner_Init(&MxL_tuner);
   // printf("Analogl tuner init\n");
   MxL_Check_ChipVersion(&MxL_tuner,&ChipVer);
   printf("MxL ChipVer:%bx\n",ChipVer);
}

/*************************************************************************
  Subject:    FQD1216 tuner initialized function
  Function:   MDrv_Tuner_Init
  Parmeter:   CONFIG: pointer to tuner address
  Return :    NONE
  Remark:
**************************************************************************/
void devDigitalTuner_Init()
{

   MxLxxxRF_TunerConfigS MxL_tuner;
  // MxLxxxRF_ChipVersion ChipVer;
   MxL_tuner.I2C_Addr=MxL_I2C_ADDR_96;
   MxL_tuner.BW_MHz=MxL_BW_8MHz;
   MxL_tuner.Mode=MxL_MODE_DVBT;
   MxL_tuner.TunerID = MxL_TunerID_MxL301RF;
   MxL_tuner.IF_Freq=MxL_IF_6_MHZ;
   MxL_tuner.IF_Spectrum=MxL_INVERT_IF;
      #if (MxLIF_PATH==Mxl_IF1)
   MxL_tuner.IF_Path=MxL_IF_PATH1;
   MxL_tuner.AGC = MxL_AGC_SEL1;
   #else
   MxL_tuner.IF_Path=MxL_IF_PATH2;
   MxL_tuner.AGC = MxL_AGC_SEL2;
   #endif
   MxL_tuner.Xtal_Freq = MxL_XTAL_24_MHZ;
   MxL_tuner.ClkOut_Setting = MxL_CLKOUT_DISABLE;
   MxL_tuner.ClkOut_Amp=MxL_CLKOUT_AMP_0;
   MxL_tuner.Xtal_Cap = MxL_XTAL_CAP_12_PF;
   MxL_tuner.IF_Split=MxL_IF_SPLIT_DISABLE;
   MxL_tuner.RF_Freq_Hz=87000000;
   MxL_Tuner_Init(&MxL_tuner);
  //  printf("Digital  tuner init\n");
   //MxL_Check_ChipVersion(&MxL_tuner,&ChipVer);
   

}

void devDigitalTuner_SetFreq ( double Freq,  RF_CHANNEL_BANDWIDTH eBandWidth)
{    
   MxLxxxRF_TunerConfigS MxL_tuner;
   
   MxL_tuner.I2C_Addr=MxL_I2C_ADDR_96;
   MxL_tuner.BW_MHz=(MxLxxxRF_BW_MHz)(eBandWidth+5);
   MxL_tuner.Mode=MxL_MODE_DVBT;//MxL_MODE_DVBT;
   MxL_tuner.TunerID = MxL_TunerID_MxL301RF;   
   MxL_tuner.IF_Freq=MxL_IF_6_MHZ;
   MxL_tuner.IF_Spectrum=MxL_INVERT_IF;
      #if (MxLIF_PATH==Mxl_IF1)
   MxL_tuner.IF_Path=MxL_IF_PATH1;
   MxL_tuner.AGC = MxL_AGC_SEL1;
   #else
   MxL_tuner.IF_Path=MxL_IF_PATH2;
   MxL_tuner.AGC = MxL_AGC_SEL2;
   #endif
   MxL_tuner.Xtal_Freq = MxL_XTAL_24_MHZ;
   MxL_tuner.ClkOut_Setting = MxL_CLKOUT_DISABLE;
   MxL_tuner.ClkOut_Amp=MxL_CLKOUT_AMP_0;
   MxL_tuner.Xtal_Cap = MxL_XTAL_CAP_12_PF;
   MxL_tuner.IF_Split=MxL_IF_SPLIT_DISABLE;
   MxL_tuner.RF_Freq_Hz=Freq*1000000;
   //MxL_Tuner_Init(&MxL_tuner);
   //printf("SetDigital\n");
   MxL_Tuner_RFTune(&MxL_tuner,MxL_tuner.RF_Freq_Hz, MxL_tuner.BW_MHz);
}
#undef _MxL_301_S
#endif

