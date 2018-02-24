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
 
 Driver APIs for MxL30xRF Tuner
 
 Copyright, Maxlinear, Inc.
 All Rights Reserved
 
 File Name:      MxL_API.h

 Version:    9.2.2
 
 */
#ifndef __MxL_API_H
#define __MxL_API_H

#include "mxl_common.h"


/******************************************************************************
**
**  Name: MxL_Set_Register
**
**  Description:    Write one register to MxL Tuner
**
**  Parameters:    	myTuner				- Pointer to MxLxxxRF_TunerConfigS
**					RegAddr				- Register address to be written
**					RegData				- Data to be written
**
**  Returns:        MxL_ERR_MSG			- MxL_OK if success	
**										- MxL_ERR_SET_REG if fail
**
******************************************************************************/
MxL_ERR_MSG MxL_Set_Register(MxLxxxRF_TunerConfigS* myTuner, UINT8 RegAddr, UINT8 RegData);

/******************************************************************************
**
**  Name: MxL_Get_Register
**
**  Description:    Read one register from MxL Tuner
**
**  Parameters:    	myTuner				- Pointer to MxLxxxRF_TunerConfigS
**					RegAddr				- Register address to be read
**					RegData				- Pointer to register read
**
**  Returns:        MxL_ERR_MSG			- MxL_OK if success	
**										- MxL_ERR_GET_REG if fail
**
******************************************************************************/
MxL_ERR_MSG MxL_Get_Register(MxLxxxRF_TunerConfigS* myTuner, UINT8 RegAddr, UINT8 *RegData);

/******************************************************************************
**
**  Name: MxL_Tuner_Init
**
**  Description:    MxL Tuner Initialization
**
**  Parameters:    	myTuner				- Pointer to MxLxxxRF_TunerConfigS
**
**  Returns:        MxL_ERR_MSG			- MxL_OK if success	
**										- MxL_ERR_INIT if fail
**
******************************************************************************/
MxL_ERR_MSG MxL_Tuner_Init(MxLxxxRF_TunerConfigS* );

/******************************************************************************
**
**  Name: MxL_Tuner_RFTune
**
**  Description:    Frequency tunning for channel
**
**  Parameters:    	myTuner				- Pointer to MxLxxxRF_TunerConfigS
**					RF_Freq_Hz			- RF Frequency in Hz
**					BWMHz				- Bandwidth 6, 7 or 8 MHz
**
**  Returns:        MxL_ERR_MSG			- MxL_OK if success	
**										- MxL_ERR_RFTUNE if fail
**
******************************************************************************/
MxL_ERR_MSG MxL_Tuner_RFTune(MxLxxxRF_TunerConfigS*, UINT32 RF_Freq_Hz, MxLxxxRF_BW_MHz BWMHz);		

/******************************************************************************
**
**  Name: MxL_Soft_Reset
**
**  Description:    Software Reset the MxL Tuner
**
**  Parameters:    	myTuner				- Pointer to MxLxxxRF_TunerConfigS
**
**  Returns:        MxL_ERR_MSG			- MxL_OK if success	
**										- MxL_ERR_OTHERS if fail
**
******************************************************************************/
MxL_ERR_MSG MxL_Soft_Reset(MxLxxxRF_TunerConfigS*);

/******************************************************************************
**
**  Name: MxL_Standby
**
**  Description:    Enter Standby Mode
**
**  Parameters:    	myTuner				- Pointer to MxLxxxRF_TunerConfigS
**
**  Returns:        MxL_ERR_MSG			- MxL_OK if success	
**										- MxL_ERR_OTHERS if fail
**
******************************************************************************/
MxL_ERR_MSG MxL_Stand_By(MxLxxxRF_TunerConfigS*);

/******************************************************************************
**
**  Name: MxL_Wakeup
**
**  Description:    Wakeup from Standby Mode (Note: after wake up, please call RF_Tune again)
**
**  Parameters:    	myTuner				- Pointer to MxLxxxRF_TunerConfigS
**
**  Returns:        MxL_ERR_MSG			- MxL_OK if success	
**										- MxL_ERR_OTHERS if fail
**
******************************************************************************/
MxL_ERR_MSG MxL_Wake_Up(MxLxxxRF_TunerConfigS*);

/******************************************************************************
**
**  Name: MxL_Check_ChipVersion
**
**  Description:    Return the MxL Tuner Chip ID
**
**  Parameters:    	myTuner				- Pointer to MxLxxxRF_TunerConfigS
**					myChipVersion		- MxL_ChipVersion
**  Returns:        MxL_ERR_MSG			
**
******************************************************************************/
MxL_ERR_MSG MxL_Check_ChipVersion(MxLxxxRF_TunerConfigS*, MxLxxxRF_ChipVersion*);

/******************************************************************************
**
**  Name: MxL_RFSynth_Lock_Status
**
**  Description:    RF synthesizer lock status of MxL Tuner
**
**  Parameters:    	myTuner				- Pointer to MxLxxxRF_TunerConfigS
**					isLock				- Pointer to Lock Status
**
**  Returns:        MxL_ERR_MSG			- MxL_OK if success	
**										- MxL_ERR_OTHERS if fail
**
******************************************************************************/
//MxL_ERR_MSG MxL_RFSynth_Lock_Status(MxLxxxRF_TunerConfigS* , BOOL* isLock);

/******************************************************************************
**
**  Name: MxL_REFSynth_Lock_Status
**
**  Description:    REF synthesizer lock status of MxL Tuner
**
**  Parameters:    	myTuner				- Pointer to MxLxxxRF_TunerConfigS
**					isLock				- Pointer to Lock Status
**
**  Returns:        MxL_ERR_MSG			- MxL_OK if success	
**										- MxL_ERR_OTHERS if fail	
**
******************************************************************************/
//MxL_ERR_MSG MxL_REFSynth_Lock_Status(MxLxxxRF_TunerConfigS* , BOOL* isLock);

/******************************************************************************
**
**  Name: MxL_Check_RF_Input_Power
**
**  Description:    Reads the RF Input power from MxL Tuner
**
**  Parameters:    	myTuner				- Pointer to MxL30xRF_TunerConfigS
**					RF_Input_Level		- Pointer to return value, RF input level
**
**  Returns:        MxL_ERR_MSG			- MxL_OK if success	
**										- MxL_ERR_OTHERS if fail	
**
******************************************************************************/
//MxL_ERR_MSG MxL_Check_RF_Input_Power(MxLxxxRF_TunerConfigS* myTuner, REAL32* RF_Input_Level);

#endif /*__MxL_API_H*/

