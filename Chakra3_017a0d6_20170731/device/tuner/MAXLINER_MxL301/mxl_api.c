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
/*

 Driver APIs for MxLxxxRF Tuner
 
 Copyright, Maxlinear, Inc.
 All Rights Reserved
 
 File Name:      MxL_API.c
 
 Version:    9.2.2
*/


/*#include "StdAfx.h"*/
#include "mxl_api.h"
//#include "mxl_user_define.h"
/* For customer:  include appropriate tuner driver file */
/* #include "mxl302rf.h" */
/* #include "mxl301rf.h" */
/* #include "mxl202rf.h" */



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//																		   //
//							Tuner Functions								   //
//																		   //
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
MxL_ERR_MSG MxL_Set_Register(MxLxxxRF_TunerConfigS* myTuner, UINT8 RegAddr, UINT8 RegData)
{
	UINT32 Status=0;
	UINT8 pArray[2];
	pArray[0] = RegAddr;
	pArray[1] = RegData;
	
	Status = MxL_I2C_Write((UINT8)myTuner->I2C_Addr, pArray, 2);
	if(Status) return MxL_ERR_SET_REG;

	return MxL_OK;
}

MxL_ERR_MSG MxL_Get_Register(MxLxxxRF_TunerConfigS* myTuner, UINT8 RegAddr, UINT8 *RegData)
{
	if(MxL_I2C_Read((UINT8)myTuner->I2C_Addr, RegAddr, RegData))
		return MxL_ERR_GET_REG;
	return MxL_OK;

}

MxL_ERR_MSG MxL_Soft_Reset(MxLxxxRF_TunerConfigS* myTuner)
{
	UINT32 Status=0;
	UINT8 reg_reset;
	reg_reset = 0xFF;
	Status = MxL_I2C_Write((UINT8)myTuner->I2C_Addr, &reg_reset, 1);
	if(Status)
		return (MxL_ERR_MSG)Status;

	return MxL_OK;
}


MxL_ERR_MSG MxL_Stand_By(MxLxxxRF_TunerConfigS* myTuner)
{
	UINT8 pArray[4];	/* a array pointer that store the addr and data pairs for I2C write	*/
	
	pArray[0] = 0x01;
	pArray[1] = 0x0;
	pArray[2] = 0x13;
	pArray[3] = 0x0;

	if(MxL_I2C_Write((UINT8)myTuner->I2C_Addr, pArray, 4))
		return MxL_ERR_OTHERS;

	return MxL_OK;
}

MxL_ERR_MSG MxL_Wake_Up(MxLxxxRF_TunerConfigS* myTuner)
{
	UINT8 pArray[2];	/* a array pointer that store the addr and data pairs for I2C write	*/

	pArray[0] = 0x01;
	pArray[1] = 0x01;

	if(MxL_I2C_Write((UINT8)myTuner->I2C_Addr, pArray, 2))
		return MxL_ERR_OTHERS;

	if(MxL_Tuner_RFTune(myTuner, myTuner->RF_Freq_Hz, myTuner->BW_MHz))
		return MxL_ERR_RFTUNE;

	return MxL_OK;
}

MxL_ERR_MSG MxL_Tuner_Init(MxLxxxRF_TunerConfigS* myTuner)
{	
	UINT8 pArray[MAX_ARRAY_SIZE];	/* a array pointer that store the addr and data pairs for I2C write */
	UINT32 Array_Size;				/* a integer pointer that store the number of element in above array */
	UINT8 Status;

	/* Soft reset tuner */
	if(MxL_Soft_Reset(myTuner))
		return MxL_ERR_INIT;

	/* perform initialization calculation */
	if(myTuner->TunerID == MxL_TunerID_MxL202RF)
	{
		/* Uncomment section below for MxL202RF */
		/*Status = MxL202RF_Init(pArray, &Array_Size, (UINT8)myTuner->Mode, (UINT32)myTuner->Xtal_Freq,
				(UINT32)myTuner->IF_Freq, (UINT8)myTuner->IF_Spectrum, (UINT8)myTuner->ClkOut_Setting, (UINT8)myTuner->ClkOut_Amp,
				(UINT8)myTuner->Xtal_Cap, (UINT8)myTuner->BW_MHz, (UINT8)myTuner->AGC);
		if(Status) //if failure
			return (MxL_ERR_MSG)Status;
		*/
	}
	else if (myTuner->TunerID == MxL_TunerID_MxL301RF)
	{	
		/* Uncomment section below for MxL301RF */
		Status = MxL301RF_Init(pArray, &Array_Size, (UINT8)myTuner->Mode, (UINT32)myTuner->Xtal_Freq,
				(UINT32)myTuner->IF_Freq, (UINT8)myTuner->IF_Spectrum, (UINT8)myTuner->ClkOut_Setting, (UINT8)myTuner->ClkOut_Amp,
				(UINT8)myTuner->Xtal_Cap, (UINT8)myTuner->AGC, (UINT8)myTuner->IF_Path);
		if(Status) //if failure
			return (MxL_ERR_MSG)Status;
		
	}
	else if (myTuner->TunerID == MxL_TunerID_MxL302RF)
	{	
		/* Uncomment section below for MxL302RF */
		/* Status = MxL302RF_Init(pArray, &Array_Size, (UINT8)myTuner->Mode, (UINT32)myTuner->Xtal_Freq,
				(UINT32)myTuner->IF_Freq, (UINT8)myTuner->IF_Spectrum, (UINT8)myTuner->ClkOut_Setting, (UINT8)myTuner->ClkOut_Amp,
				(UINT8)myTuner->Xtal_Cap, (UINT8)myTuner->AGC, (UINT8)myTuner->IF_Split, (UINT8)myTuner->IF_Path);
		if(Status) //if failure
			return (MxL_ERR_MSG)Status;
		*/
	}

	/* perform I2C write here */
	if(MxL_I2C_Write((UINT8)myTuner->I2C_Addr, pArray, Array_Size))
		return MxL_ERR_INIT;

	MxL_Delay(1);	/* 1ms delay*/

	return MxL_OK;
}


MxL_ERR_MSG MxL_Tuner_RFTune(MxLxxxRF_TunerConfigS* myTuner, UINT32 RF_Freq_Hz, MxLxxxRF_BW_MHz BWMHz)
{
	UINT8 pArray[MAX_ARRAY_SIZE];	/* a array pointer that store the addr and data pairs for I2C write */
	UINT32 Array_Size;				/* a integer pointer that store the number of element in above array */	
	UINT8 Status;
	UINT8 Data1, Data2;
	SINT16 Data;
	UINT8 i;

	/* Store information into struc	 */
	myTuner->RF_Freq_Hz = RF_Freq_Hz;
	myTuner->BW_MHz = BWMHz;

	/* perform Channel Change calculation */
	if(myTuner->TunerID == MxL_TunerID_MxL202RF)
	{
		/* Uncomment section below for MxL202RF */
		/*Status = MxL202RF_RFTune(pArray,&Array_Size,RF_Freq_Hz,BWMHz, myTuner->Mode); 
		if (Status)
			return MxL_ERR_RFTUNE;
		*/
	}
	else if (myTuner->TunerID == MxL_TunerID_MxL301RF)
	{	
		/* Uncomment section below for MxL301RF */
		 Status = MxL301RF_RFTune(pArray,&Array_Size,RF_Freq_Hz,BWMHz, myTuner->Mode);
		if (Status)
			return MxL_ERR_RFTUNE;
		
	}
	else if (myTuner->TunerID == MxL_TunerID_MxL302RF)
	{
		/* Uncomment section below for MxL302RF */	
		/* Status = MxL302RF_RFTune(pArray,&Array_Size,RF_Freq_Hz,BWMHz, myTuner->Mode, myTuner->IF_Split);
		if (Status)
			return MxL_ERR_RFTUNE;
		*/
	}

	/* perform I2C write here */
	if(MxL_I2C_Write((UINT8)myTuner->I2C_Addr, pArray, Array_Size)) 
		return MxL_ERR_RFTUNE;

	/* Register read-back based setting for Analog M/N split mode only */ 
	if (myTuner->TunerID == MxL_TunerID_MxL302RF && myTuner->Mode >= MxL_MODE_ANA_MN && myTuner->IF_Split == MxL_IF_SPLIT_ENABLE)
	{
		MxL_Delay(1); /* Added V9.2.1.0 */

		MxL_Get_Register(myTuner, 0xE3, &Data1);
		MxL_Get_Register(myTuner, 0xE4, &Data2);
		Data = ((Data2&0x03)<<8) + Data1;
		if(Data >= 512) 
			Data = Data - 1024;
				
		if(Data < 20)
		{
			MxL_Set_Register(myTuner, 0x85, 0x43);
			MxL_Set_Register(myTuner, 0x86, 0x08);
		}
		else if (Data >= 20)
		{
			MxL_Set_Register(myTuner, 0x85, 0x9E);
			MxL_Set_Register(myTuner, 0x86, 0x0F);
		}
		
		for(i = 0; i<Array_Size; i+=2)
		{
			if(pArray[i] == 0x11)
				Data1 = pArray[i+1];
			if(pArray[i] == 0x12)
				Data2 = pArray[i+1];
		}
		MxL_Set_Register(myTuner, 0x11, Data1);
		MxL_Set_Register(myTuner, 0x12, Data2);
	}

	if (myTuner->TunerID == MxL_TunerID_MxL302RF)	
		MxL_Set_Register(myTuner, 0x13, 0x01);
	
	MxL_Delay(30);

	if(myTuner->Mode >= MxL_MODE_ANA_MN)
	{
		Status = MxL_Set_Register(myTuner, 0x1A, 0x0D);
		if (Status)
			return MxL_ERR_SET_REG;
	}

	return MxL_OK;
}

MxL_ERR_MSG MxL_Check_ChipVersion(MxLxxxRF_TunerConfigS* myTuner, MxLxxxRF_ChipVersion* myChipVersion)
{	
	UINT8 Data;
	if(MxL_Get_Register(myTuner, 0x17, &Data))
		return MxL_GET_ID_FAIL;
	switch(Data & 0x0F)
	{
	case 0x09: *myChipVersion=MxL_30xRF_V9; 
	printf("MxL301RF_V9 Found\n");
	break;
	default: 
		*myChipVersion=MxL_UNKNOWN_ID;
	}	

	return MxL_OK;
}
/*
MxL_ERR_MSG MxL_RFSynth_Lock_Status(MxLxxxRF_TunerConfigS* myTuner, BOOL* isLock)
{	
	UINT8 Data;
	*isLock = FALSE; 
	if(MxL_Get_Register(myTuner, 0x16, &Data))
		return MxL_ERR_OTHERS;
	Data &= 0x0C;
	if (Data == 0x0C)
		*isLock = TRUE;  //RF Synthesizer is Lock 
	return MxL_OK;
}

MxL_ERR_MSG MxL_REFSynth_Lock_Status(MxLxxxRF_TunerConfigS* myTuner, BOOL* isLock)
{
	UINT8 Data;
	*isLock = FALSE; 
	if(MxL_Get_Register(myTuner, 0x16, &Data))
		return MxL_ERR_OTHERS;
	Data &= 0x03;
	if (Data == 0x03)
		*isLock = TRUE;   //REF Synthesizer is Lock 
	return MxL_OK;
}


MxL_ERR_MSG MxL_Check_RF_Input_Power(MxLxxxRF_TunerConfigS* myTuner, REAL32* RF_Input_Level)
{	
	UINT8 RFin1, RFin2, RFOff1, RFOff2;
	REAL32 RFin, RFoff;
	REAL32 cal_factor;

    if (MxL_Set_Register(myTuner, 0x14, 0x01))	
		return MxL_ERR_SET_REG;

	MxL_Delay(1);
	if(MxL_Get_Register(myTuner, 0x18, &RFin1))  // LSBs
		return MxL_ERR_SET_REG; 
	if(MxL_Get_Register(myTuner, 0x19, &RFin2))  //MSBs 
		return MxL_ERR_SET_REG;	

	if(MxL_Get_Register(myTuner, 0xD6, &RFOff1))  //LSBs 
		return MxL_ERR_SET_REG; 
	if(MxL_Get_Register(myTuner, 0xD7, &RFOff2))  // MSBs 
		return MxL_ERR_SET_REG;	

	RFin = REAL32(((RFin2 & 0x07) << 5) + ((RFin1 & 0xF8) >> 3) + ((RFin1 & 0x07) * 0.125));
	RFoff = REAL32(((RFOff2 & 0x0F) << 2) + ((RFOff1 & 0xC0) >> 6) + (((RFOff1 & 0x38)>>3) * 0.125));
	if(myTuner->Mode == MxL_MODE_DVBT)
		cal_factor = 113.;
	else if(myTuner->Mode == MxL_MODE_ATSC)
		cal_factor = 109.;
	else if(myTuner->Mode == MxL_MODE_CAB_STD)
		cal_factor = 110.;
	else
		cal_factor = 107.;

	*RF_Input_Level = RFin - RFoff - cal_factor;

	return MxL_OK;
}
*/