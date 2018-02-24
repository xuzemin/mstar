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
#ifndef ALTOBEAM_H
#define ALTOBEAM_H

#ifndef u_int8
#define u_int8 unsigned char
#endif

#ifndef u_int16
#define u_int16 unsigned short
#endif

#ifndef u_int32
#define u_int32 unsigned int
#endif

#define TS_PARALLEL_MODE 1
#define TS_SERIAL_MODE   0

#define TS_OUTPUT_FALLING_EDGE 1
#define TS_OUTPUT_RISING_EDGE  0

#define TS_CLOCK_CONST_OUTPUT 1
#define TS_CLOCK_VALID_OUTPUT 0

#define  TUNER_SHARP2093 0
#define  TUNER_SHARP5093 1
#define  TUNER_SHARP6093 2
#define  TUNER_SHARP5060 3
#define  TUNER_SHARP6060 4
#define  TUNER_SHARP6092 5
#define  TUNER_SHARP6402 6
#define  TUNER_SHARP5402 7
#define  TUNER_SHARP1402 8
#define  TUNER_ENV59M01D8F 9
#define  TUNER_ALPS_TDAD 10
#define  TUNER_ALPS_TDAC 11
#define  TUNER_MAX2165 12
#define  TUNER_ADMTV102 13
#define  TUNER_ADMTV803 14
#define  TUNER_MXL5003S 15
#define  TUNER_MXL5007 16

#define TUNER_IF_FREQ_36_DOT_166_M 0
#define TUNER_IF_FREQ_36_M 1
#define TUNER_IF_FREQ_36_DOT_125_M 2
 /*silicon tuners may have this config*/
#define TUNER_IF_FREQ_0_M 3

#define SWAP_IQ 0
#define NO_SWAP_IQ 1

#define CRYSTAL 0
#define OSCILLATOR 1

#define CLK_30_DOT_4_M     1
#define CLK_28_DOT_6363_M  0

#define STATIC_RECEIVING  1
#define MOBILE_RECEIVING  0


typedef enum
{
    COFDM_FEC_LOCK,
    COFDM_PSYNC_LOCK,
    COFDM_TPS_LOCK,
    COFDM_DCR_LOCK,
    COFDM_AGC_LOCK,
    COFDM_MODE_DET,
} COFDM_LOCK_STATUS;

 /*
*struct MPEG_TS_mode_t
*
*@TS_Transfer_Type: TS stream transfer type, can be set to parallel(8 data bus) or serial(1 data bus) mode
*
*@Demod output edge:demod will send TS data on this edge of TS stream clock
*
*@SPI_clock_constant_output:TS stream clock  can be set to valid for all the time or only for TS data valid (188 bytes)
*/
struct MPEG_TS_mode_t
{
	u_int8 TS_Transfer_Type;
	u_int8 output_edge;
	u_int8 SPI_clock_constant_output;
};

/*
*struct tuner_config_t
*
*@tuner_type : name of tuner
*
*@IF_Frequency: tuner IF frequency output in Mhz,most of silicon tuner IF is 0, except maxlinear(36.125Mhz)
*
*@IQ_mode: when tuner IF is 0, demod need to know if IQ is swaped or no swaped on hardware board
*/
struct tuner_config_t
{
    u_int8 tuner_type;
    u_int8 IF_Frequency;
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
*@receiving_mode: STB or Dongle may be used in fixed or mobile circumstance
*
*/

struct custom_config_t
{
    struct tuner_config_t tuner_config;
    struct MPEG_TS_mode_t  ts_mode;
    u_int8 CRYSTAL_OR_OSCILLATOR;
	u_int8 sample_clk_Frequency;
    u_int8  receiving_mode ;
};



void ATBMIChipID(void);
void ATBMInit(void);

void ATBMConfig(struct custom_config_t custom_config);

void ATBMReset(u_int8 cry_or_osc);
void ATBMSetTSMode(struct MPEG_TS_mode_t ts_mode);   /*Default SPI , it can be configured to Serial mode*/
int ATBMSetOSC(struct tuner_config_t tuner_config,u_int8 sample_clk_Frequency);


/* Optimizing funcion*/
void ATBM_Static_channel(void);
void ATBM_Mobile_channel(void);

void ATBMTunerAGC( u_int8 tuner_type);

void ATBMI2CByPassOn(void);
void ATBMI2CByPassOff(void);

int  ATBMLockedFlag(void);
int ATBMLockedLoopCheck(void);


u_int16 ATBMSignalStrength(void);
float   ATBMSignalNoiseRatio(void);
u_int16 ATBMFrameErrorRatio(void);

int ATBMSignalQuality(void);
u_int16 ATBMSignalStrength_Sharp2093(void);
u_int16 ATBMSignalStrength_Maxim2165(void);

void ATBMDebugRegiseter(void);
u_int8  ATBMGetTPS(void);

int  ATBMRead(u_int8 base_addr, u_int8 register_addr, u_int8 *data);
int  ATBMWrite(u_int8 base_addr, u_int8 register_addr, u_int8 *data);

#endif

