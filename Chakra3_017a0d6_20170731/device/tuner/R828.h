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
//#include "..\stdafx.h"
#ifndef  _R828_H_ 
#define _R828_H_

//***************************************************************
//*                       INCLUDES.H
//***************************************************************
#define VERSION   "R828D_v1.40"


//----------------------------------------------------------//
//                   Type Define                            //
//----------------------------------------------------------//

#define UINT8  unsigned char
#define UINT16 unsigned short
#define UINT32 unsigned long

typedef enum _R828_ErrCode
{
	RT_Success = true,
	RT_Fail    = false
}R828_ErrCode;

typedef enum _Rafael_Chip_Type  //Don't modify chip list
{
	R828 = 0,
	R828D,
	R828S,
	R820T,
	R820C,
	R620D,
	R620S
}Rafael_Chip_Type;

typedef struct _I2C_LEN_TYPE
{
	UINT8 RegAddr;
	UINT8 Data[50];
	UINT8 Len;
}I2C_LEN_TYPE;

typedef struct _I2C_TYPE
{
	UINT8 RegAddr;
	UINT8 Data;
}I2C_TYPE;
//----------------------------------------------------------//
//                   R828 Parameter                        //
//----------------------------------------------------------//

extern UINT8 R828_ADDRESS;
#define R828_Xtal	  16000
//#define R828_Xtal	  24000
#define DIP_FREQ  	  320000
#define IMR_TRIAL    9
#define VCO_pwr_ref   0x01

extern UINT32 R828_IF_khz;
extern UINT32 R828_CAL_LO_khz;
extern UINT8  R828_IMR_point_num;
extern UINT8  R828_IMR_done_flag;
extern UINT8  Rafael_Chip;

typedef enum _R828_Standard_Type  //Don't remove standand list!!
{

	NTSC_MN = 0,
	PAL_I,
	PAL_DK,
	PAL_B_7M,
	PAL_GH_8M,
	SECAM_L,
	SECAM_L1_INV,
	SECAM_L1,
	ATV_SIZE,
	DVB_T_6M = ATV_SIZE,
	DVB_T_7M,
	DVB_T_7M_2,
	DVB_T_8M,
    DVB_T2_6M,
	DVB_T2_7M,
	DVB_T2_7M_2,
	DVB_T2_8M,
	DVB_T2_1_7M,
	DVB_T2_10M,
	DVB_C_8M,
	DVB_C_6M,
	ISDB_T,
	DTMB,
	ATSC,
	FM,
	STD_SIZE
}R828_Standard_Type;

extern UINT8  R828_Fil_Cal_flag[STD_SIZE];

typedef enum _R828_SetFreq_Type
{
	SETFREQ_FAST_MODE = TRUE,
	SETFREQ_NORMAL_MODE = FALSE
}R828_SetFreq_Type;

typedef enum _R828_LoopThrough_Type
{
	LOOP_THROUGH = TRUE,
	SIGLE_IN     = FALSE
}R828_LoopThrough_Type;


typedef enum _R828_InputMode_Type
{
	AIR_IN = 0,
	CABLE_IN_1,
	CABLE_IN_2
}R828_InputMode_Type;

typedef enum _R828_IfAgc_Type
{
	IF_AGC1 = 0,
	IF_AGC2
}R828_IfAgc_Type;

typedef enum _R828_GPIO_Type
{
	HI_SIG = TRUE,
	LO_SIG = FALSE
}R828_GPIO_Type;

typedef struct _R828_Set_Info
{
	UINT32        RF_KHz;
	R828_Standard_Type R828_Standard;
	R828_LoopThrough_Type RT_Input;
	//R828_InputMode_Type   RT_InputMode;
	R828_IfAgc_Type R828_IfAgc_Select; 
}R828_Set_Info;

typedef struct _R828_RF_Gain_Info
{
	UINT8   RF_gain1;
	UINT8   RF_gain2;
	UINT8   RF_gain_comb;
}R828_RF_Gain_Info;

typedef enum _R828_RF_Gain_TYPE
{
	RF_AUTO = 0,
	RF_MANUAL
}R828_RF_Gain_TYPE;

//----------------------------------------------------------//
//                   R828 Function                         //
//----------------------------------------------------------//

#define R828_Delay_MS	Sleep

R828_ErrCode R828_Init(void);
R828_ErrCode R828_Standby(R828_LoopThrough_Type R828_LoopSwitch);
R828_ErrCode R828_GPIO(R828_GPIO_Type R828_GPIO_Conrl);
R828_ErrCode R828_SetStandard(R828_Standard_Type RT_Standard);
R828_ErrCode R828_SetFrequency(R828_Set_Info R828_INFO, R828_SetFreq_Type R828_SetFreqMode);
R828_ErrCode R828_GetRfGain(R828_RF_Gain_Info *pR828_rf_gain);
R828_ErrCode R828_RfGainMode(R828_RF_Gain_TYPE R828_RfGainType);


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//                      Smart GUI                               //
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
extern UINT8 R828_IMR_XT[6];
extern UINT8 R828_IMR_YT[6];
R828_ErrCode SmartGUIFunction(void);


//***********No used for Silicon tuner,but for API*******************************
#define VHF_LOWMIN_FREQ        			46250L    // KHz
#define VHF_LOWMAX_FREQ        			142000L    // KHz
#define VHF_HIGHMIN_FREQ    			149000L    // KHz
#define VHF_HIGHMAX_FREQ    			426000L    // KHz
#define UHF_MIN_FREQ        				434000L    // KHz
#define UHF_MAX_FREQ        				863250L    // KHz
#define TUNER_IF_FREQ_KHz            		38900L    // KHz
#define TUNER_L_PRIME_IF_FREQ_KHz    	33950L    // KHz
//*********************end*************************************************
void devTunerInit(void);
void devTunerSetAtvStandard(IF_FREQ enIF_Freq);
void devTunerSetPLLData(WORD wPLLData, RFBAND eBand);

#endif
