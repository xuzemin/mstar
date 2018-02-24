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
/***************************************************************************** 
Copyright 2011, AltoBeam Inc. All rights reserved.
     
   
Released 2011-05-29
******************************************************************************/

#ifndef ATBM884X_H
#define ATBM884X_H

typedef unsigned char u_int8;
typedef unsigned short u_int16;
typedef unsigned int u_int32;

/* 
*struct MPEG_TS_mode_t 
*
*@TS_Transfer_Type: TS stream transfer type, can be set to parallel(8 data bus) or serial(1 data bus) mode
*
*@Demod output edge: demod will send TS data on this edge of TS stream clock
*
*@SPI_clock_constant_output: TS stream clock  can be set to valid for all the time or only during TS data valid (188 bytes) 
*/
struct MPEG_TS_mode_t 
{
#define TS_PARALLEL_MODE 1
#define TS_SERIAL_MODE   0
	u_int8 TS_Transfer_Type;

#define TS_OUTPUT_FALLING_EDGE 1
#define TS_OUTPUT_RISING_EDGE  0
	u_int8 output_edge; 

#define TS_CLOCK_CONST_OUTPUT 1
#define TS_CLOCK_VALID_OUTPUT 0	
	u_int8 SPI_clock_constant_output; 		
};

/*symbol_rate: typicaly use 6875K, range from 3000K to 6952K*/
struct DVBC_Params_t 
{   
	u_int32	symbol_rate; 
};


/*
*struct tuner_config_t
*
*@IF_Frequency_KHz: tuner IF frequency output in MHz. Most silicon tuners' IF is 0. Most CAN Tuners' are 36M, 36.167M
*
*@or 36.125 MHz (Typical IF used by DVB-C tuners)
*
*@IQ_mode: when tuner IF is zero or, demod needs to know if IQ is swapped or not on hardware board, also related with spectrum inverse
*/
struct tuner_config_t 
{

	/*CAN tuners or some silicon tuners may have these configurations*/      
	/*36.1667, 36, 36.125 MHz*/

	/*silicon tuners may have ZIF configuration, 0 MHz*/

	u_int32 IF_Frequency_KHz;

#define SWAP_IQ 0
#define NO_SWAP_IQ 1
	u_int8 IQ_mode;	
};

/* 
* struct     custom_config_t 
*
*@tuner_config: struct of tuner configuration
*
*@ts_mode: struct of TS mode
*
*@CRYSTAL_OR_OSCILLATOR: demod can use crystal or oscillator 
*
*@sample_clk_Frequency: crystal or oscillator frequency on hardware board for demod
*
*@dtmb_dvbc_mode:select receiving mode DTMB or DVB-C for ATBM884x
*
*@dvbc_params: DVB-C parameters
*/

struct custom_config_t
{
	struct tuner_config_t tuner_config;

	struct MPEG_TS_mode_t  ts_mode;	

#define CRYSTAL 0
#define OSCILLATOR 1
	u_int8 CRYSTAL_OR_OSCILLATOR;

	u_int32 sample_clk_Frequency_KHz;

#define ATBM_DTMB_MODE  1
#define ATBM_DVBC_MODE  0    
	u_int8 dtmb_dvbc_mode;	
	struct DVBC_Params_t  dvbc_params;
};

extern unsigned char ATBM_ChipID;

/********DTMB and DVB-C common API functions*************/
u_int8 ATBMChipID(void);
void ATBMI2CByPassOn(void);
void ATBMI2CByPassOff(void);
int  ATBMLockedFlag(void);
int ATBMLockedLoopCheck(void);
void ATBM_Standby(void);
void ATBM_Standby_WakeUp(void);
void ATBM_Suspend(void);

/****DTMB API Functions******************************/
void ATBMInit_DTMB_Mode(void); 
void ATBMHoldDSP(void);
void ATBMStartDSP(void);
u_int16 ATBMSignalStrength(void);	
u_int32   ATBMSignalNoiseRatio(void);
int  ATBMSignalQuality(void);
u_int16 ATBMSignalStrength_Sharp2093(void);
u_int16 ATBMSignalStrength_TDAC2_C02A(void);		
u_int16 ATBMSignalStrength_Maxim2165(void);	
u_int16 ATBMFrameErrorRatio(void);

u_int32 Log10_Convert(u_int32 InValue);
/****DVB-C API Functions******************************/
void ATBMInit_DVBC_Mode(void);
u_int32   ATBM_DVBC_SNR(void);
u_int32   ATBM_DVBC_BER(u_int32 *BerE);
u_int32   ATBM_DVBC_UncorrectablePER(u_int32 *PktsExponent);
u_int8   ATBM_DVBC_GetQAM(void);
u_int16 ATBM_DVBC_SignalStrength(void);
u_int16 ATBM_DVBC_SignalStrength_TDAC2_C02A(void);
/**************************************************/

/*************DVB-C internal functions************************/
void ATBM_DVBC_Init(struct custom_config_t custom_config);
void ATBM_DVBC_SetSymbolRate(u_int32 OSC_Freq_K, u_int32 dSymbolRatek);
void ATBM_DVBC_SetCarrier(u_int32 OSC_Freq_K, u_int32  dSymbolRatek);
void ATBM_DVBC_SetQAM(void);

/******************Demodulator Internal functions***********************/
void ATBMInit(void);
void ATBMConfig(struct custom_config_t custom_config);
u_int8 ATBM_Check_Demod_Status(void);
u_int8 PLL_Lock_Flag(void);
u_int8 ATBM_Check_PLL_Status(void);
void ATBMReset(u_int8 cry_or_osc);
void ATBMSetTSMode(struct MPEG_TS_mode_t ts_mode);   /*Default SPI , it can be configured to Serial mode*/
int ATBMSetOSC(struct tuner_config_t tuner_config, u_int32 sample_clk_Frequency_K); 
u_int8  ATBMGetTPS(void);
void ATBMDebugRegister(void);
void ATBMTunerAGC(void);
/****************Testing utility functions*******************/
void ATBM_PPM_Test(void);


/****DTMB I2C interface functions*********************/
void ATBMWriteRegArray(u_int8 *reg_table, u_int32 table_len);
void ATBMDebugRegArray(u_int8 *reg_table, u_int32 table_len);
u_int8  ATBMRead(u_int8 base_addr, u_int8 register_addr);
void  ATBMWrite(u_int8 base_addr, u_int8 register_addr, u_int8 data);

/****DVB-C I2C interface functions*********************/
u_int8  ATBMTransRead(u_int8 base_addr, u_int8 register_addr);
void ATBMTransWrite(u_int8 base_addr, u_int8 register_addr, u_int8 data);
void ATBM_DVBC_Write(u_int32 uAddress, u_int32 u32Data);
u_int32 ATBM_DVBC_Read(u_int32  uAddress);

extern void Delayms (int ms);
extern void DemodHardwareReset(void);

extern int I2CWrite(u_int8 I2CSlaveAddr, u_int8 *pdata, int length);
extern int I2CRead(u_int8 I2CSlaveAddr, u_int8 *pdata, int length);

#endif

