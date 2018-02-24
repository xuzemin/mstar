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
/*******************************************************************************
 *
 * FILE NAME          : MxL601_TunerCfg.h
 *
 * AUTHOR             : Dong Liu
 *
 * DATE CREATED       : 11/16/2011
 *                      03/14/2013
 *
 * DESCRIPTION        : This file contains MxL601 common control register
 *                      definitions
 *
 *******************************************************************************
 *                Copyright (c) 2011, MaxLinear, Inc.
 ******************************************************************************/

#ifndef __MXL601_TUNER_CFG_H__
#define __MXL601_TUNER_CFG_H__

/******************************************************************************
    Include Header Files
    (No absolute paths - paths handled by make file)
******************************************************************************/

#include "MxL601_OEM_Drv.h"
#include "MxL601_TunerSpurTable.h"
#include "MxL601_Features.h"

/******************************************************************************
    Macros
******************************************************************************/

//#define CUSTOMER_SPECIFIC_SETTING_1

#define AIC_RESET_REG                  0xFF // For MxL601 Tuner

#define PAGE_CHANGE_REG                0x00 // Page change, can configured as page 0 or page 1
#define XTAL_CAP_CTRL_REG              0x01 // Xtal frequency and CAP register
#define XTAL_ENABLE_DIV_REG            0x02 // Xtal enable and frequency div 4 register
#define XTAL_CALI_SET_REG              0x03 // Xtal calibration enable register enable register
#define IF_FREQ_SEL_REG                0x04 // IF frequency selection and manual set bypass register
#define IF_PATH_GAIN_REG               0x05 // IF gain level and path selection register
#define IF_FCW_LOW_REG                 0x06 // Low register of IF FCW set when manual program IF frequency
#define IF_FCW_HIGH_REG                0x07 // High register of IF FCW set when manual program IF frequency
#define AGC_CONFIG_REG                 0x08 // AGC configuration, include AGC select and AGC type
#define AGC_SET_POINT_REG              0x09
#define AGC_FLIP_REG                   0x5E
#define AGC_SLOPE_REG                  0xB5
#define AGC_OFFSET_REG                 0xB4
#define GPO_SETTING_REG                0x0A // GPO set and inquiring register
#define TUNER_ENABLE_REG               0x0B // Power up register, bit<0>
#define TUNE_MODE_REG                  0x0D
#define MAIN_REG_AMP                   0x0E
#define CHAN_TUNE_BW_REG               0x0F // Band width register
#define CHAN_TUNE_LOW_REG              0x10 // Tune frequency set low byte
#define CHAN_TUNE_HI_REG               0x11 // Tune frequency set high byte
#define START_TUNE_REG                 0x12 // sequencer setting register
#define FINE_TUNE_SET_REG              0x13 // Fine tune operation register
#define FINE_TUNE_CTRL_REG_0           0x13 // Fine tune operation register
#define FINE_TUNE_CTRL_REG_1           0x14 // Fine tune operation register

#define FINE_TUNE_OFFSET_LOW_REG       0x14 // Fine tune frequency offset low byte
#define FINE_TUNE_OFFSET_HIGH_REG      0x15 // Fine tune frequency offset high byte
#define AFC_RANGE_SET_LOW_REG          0x16 // Tuner AFC range set register low byte 
#define AFC_RANGE_SET_HIGH_REG         0x17 // Tuner AFC range set register high byte 
#define CHIP_ID_REQ_REG                0x18 // Tuner Chip ID register
#define CHIP_VERSION_REQ_REG           0x1A // Tuner Chip Revision register

#define RFPIN_RB_LOW_REG               0x1D // RF power low 8 bit register
#define RFPIN_RB_HIGH_REG              0x1E // RF power high 8 bit register
#define SIGNAL_TYPE_REG                0x1E // Signal type

#define DFE_CTRL_ACCUM_LOW_REG         0x24 // Bit<7:0>
#define DFE_CTRL_ACCUM_MID_REG         0x25 // Bit<7:0>
#define DFE_CTRL_ACCUM_HI_REG          0x26 // Bit<1:0>

#define RF_REF_STATUS_REG              0x2B // RF/REF lock status register 
#define AGC_SAGCLOCK_STATUS_REG        0x2C 

#define DFE_DACIF_BYP_GAIN_REG         0x43 
#define DFE_RFLUT_SWP1_REG             0x49 
#define DIG_ANA_RFRSSI_REG             0x57 
#define DIG_ANA_IF_CFG_0               0x5A
#define DIG_ANA_IF_CFG_1               0x5B
#define DIG_ANA_IF_PWR                 0x5C
#define XTAL_EXT_BIAS_REG              0x6D 

#define RSSI_RESET_REG                 0x78
#define DFE_CTRL_RB_HI_REG             0x7B // Bit<7:0>
#define DFE_CTRL_RB_LOW_REG            0x7A // Bit<1:0>

#define DIG_ANA_GINJO_LT_REG           0x96 

#define DFE_CTRL_TRIG_REG              0xA0 // Bit<3>
#define FINE_TUNE_INIT1_REG            0xA9 
#define FINE_TUNE_INIT2_REG            0xAA

#define DFE_AGC_CEIL1_REG              0xB0 
#define DFE_AGC_TOPMAXRF_REG           0xB1 

#define DFE_RFLUT_BYP_REG              0xDB  
#define DFE_RFLUT_DIV_MOD_REG          0xDB  // Dec: 221 

#define DFE_RFSX_FRAC_MOD1_REG         0xDF
#define DFE_RFSX_FRAC_MOD2_REG         0xE0
#define DFE_RFSX_FRAC_MOD3_REG         0xE1
#define DFE_RFSX_FRAC_MOD4_REG         0xE2

#define DFE_REFLUT_BYP_REG             0xEA  // Dec: 240, bit<6>
#define DFE_REFSX_INT_MOD_REG          0xEB  // Dec: 241

#define DIG_ANA_IF_CFG_0               0x5A
#define DIG_ANA_IF_CFG_1               0x5B
#define DIG_ANA_IF_PWR                 0x5C

#define DFE_CSF_SS_SEL                 0xEA
#define DFE_DACIF_GAIN                 0xDC

#define DFE_FDC_OFFSET_I_LSB           0xAF  // Page 1
#define DFE_FDC_OFFSET_I_MSB           0xB0  // Page 1

#define DFE_FDC_OFFSET_Q_LSB           0xB1  // Page 1
#define DFE_FDC_OFFSET_Q_MSB           0xB2  // Page 1

#define DFE_REFINTMOD_RB               0x3B  // <8 bits>
#define DFE_RFLUT_DIV_IN_RB            0xB8  // Page 1 <5 bits>
#define DFE_RFINITMOD_RB               0xB9  // Page 1 <7 bits>
#define DFE_RFFRACMOD_RB               0xBA  // Page 1 <26 bits>
#define DFE_RFLUT_BYP                  0x32  // Page 1 <1 bit>
#define DFE_RFINITMOD_W                0x33  // Page 1 <7 bits>
#define DFE_RFFRACMOD_W                0x34  // Page 1 <26 bits>

#define DFE_SEQ_RFSX_MOD_VALID_BYP     0x58 // Page 1 <bit 1> dfe_seq_digana_rfsx_mod_valid_byp
#define DFE_SEQ_RFSX_MOD_VALID         0x58 // Page 1 <bit 0> dfe_seq_digana_rfsx_mod_valid

#define DFE_FDC_IIR0_1                 0x87
#define DFE_FDC_IIR2_3                 0x88
#define DFE_FINETUNE_STEP_REG          0x84 

#define FINE_TUNE_FREQ_DECREASE        0x01
#define FINE_TUNE_FREQ_INCREASE        0x02

#define RF_SX_FRAC_N_RANGE             0xDD
#define HIGH_IF_35250_KHZ              35250

#define MAX_LUT_SIZE                   8
#define MAX_DC_CAL_SAMPLES             50

#define APP_MODE_FREQ_HZ_THRESHOLD_1   358000000
#define APP_MODE_FREQ_HZ_THRESHOLD_2   625000000
#define APP_MODE_FREQ_HZ_THRESHOLD_3   700000000

#define SPUR_SHIFT_FREQ_WINDOW         500000  // +- 0.5MHz

#define IF_GAIN_SET_POINT1             10 
#define IF_GAIN_SET_POINT2             11 
#define IF_GAIN_SET_POINT3             12 

#define SPUR_SHIFT_CLOCK_ADJUST_MIN    205 
#define SPUR_SHIFT_CLOCK_ADJUST_MAX    227 

/******************************************************************************
    User-Defined Types (Typedefs)
******************************************************************************/

typedef struct
{
  UINT8 regAddr;
  UINT8 mask;
  UINT8 data;
} REG_CTRL_INFO_T, *PREG_CTRL_INFO_T;

typedef struct
{
  UINT8 i2cAddr;
  UINT8 xtalAmp_Rb;
  UINT8 xtalAmp_LinRb;
  UINT8 appMode;
} XTAL_SPUR_CFG_T;

typedef struct
{
  UINT16 if_fcw_invert;
  UINT16 if_fcw_noninvert;  
} IF_FCW_LUT_T;

typedef struct
{
  UINT8 i2cAddr;
  UINT8 if_sel;
  UINT8 if_fcw_byp;
  UINT8 if_invert;
  UINT32 manualIFOutFreqInKHz;
} IF_FCW_CFG_T;

/******************************************************************************
    Global Variable Declarations
******************************************************************************/
extern REG_CTRL_INFO_T MxL_OverwriteDefaults[];
extern REG_CTRL_INFO_T AnalogNtsc[];
extern REG_CTRL_INFO_T AnalogPal[];
extern REG_CTRL_INFO_T AnalogSecam[];
extern REG_CTRL_INFO_T DigitalDvbc[];
extern REG_CTRL_INFO_T DigitalIsdbtAtsc[];
extern REG_CTRL_INFO_T DigitalDvbt[];

extern REG_CTRL_INFO_T Ntsc_RfLutSwpHIF[];
extern REG_CTRL_INFO_T Ntsc_16MHzRfLutSwpLIF[];
extern REG_CTRL_INFO_T Ntsc_24MHzRfLutSwpLIF[];

extern REG_CTRL_INFO_T Pal_RfLutSwpLIF[];
extern REG_CTRL_INFO_T PalD_RfLutSwpHIF[];
extern REG_CTRL_INFO_T PalI_RfLutSwpHIF[];
extern REG_CTRL_INFO_T PalBG_8MHzBW_RfLutSwpHIF[];
extern REG_CTRL_INFO_T PalBG_7MHzBW_RfLutSwpHIF[];
extern REG_CTRL_INFO_T Ntsc_HRCRfLutSwpLIF[];

/******************************************************************************
    Prototypes
******************************************************************************/

// Functions for register write operation 
MXL_STATUS Ctrl_ProgramRegisters(UINT8 I2cAddr, PREG_CTRL_INFO_T ctrlRegInfoPtr);
MXL_STATUS Ctrl_WriteRegField(UINT8 I2cAddr, PREG_CTRL_INFO_T ctrlRegInfoPtr); 

// Functions called by MxLWare API
MXL_STATUS Ctrl_SetRfFreqLutReg(UINT8 i2cAddress, UINT32 FreqInHz, PCHAN_DEPENDENT_FREQ_TABLE_T freqLutPtr);

REAL32 MxL_GetTunerSignedBits(UINT32 bits, UINT8 signedUnsigned, UINT8 numBits, UINT8 fractionBit);
REAL64 MxL_CalculateVariance(REAL32 *dataPtr, UINT8 numOfItems);
#endif /* __MXL601_TUNER_CFG_H__*/




