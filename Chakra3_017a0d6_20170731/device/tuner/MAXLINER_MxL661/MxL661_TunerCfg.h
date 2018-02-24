/*******************************************************************************
 *
 * FILE NAME          : MxL661_TunerCfg.h
 * 
 * AUTHOR             : Dong Liu
 *  
 * DATE CREATED       : 03/14/2013
 *
 * DESCRIPTION        : This file contains MxL661 common control register 
 *                      definitions
 *
 *******************************************************************************
 *                Copyright (c) 2011, MaxLinear, Inc.
 ******************************************************************************/

#ifndef __MXL661_TUNER_CFG_H__
#define __MXL661_TUNER_CFG_H__

/******************************************************************************
    Include Header Files
    (No absolute paths - paths handled by make file)
******************************************************************************/

#include "MxL661_OEM_Drv.h"
#include "MxL661_TunerSpurTable.h"
#include "MxL661_Features.h"

/******************************************************************************
    Macros
******************************************************************************/

//#define MXL661_CUSTOMER_SPECIFIC_SETTING_1         

#define AIC_RESET_REG                  0xFF // For MxL661 Tuner

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
#define DFE_FINETUNE_STEP_RB           0x1F // Fine tune step read back

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

#define DFE_SEQ_SPARE2_REG             0x69

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


#define DFE_CSF_SS_SEL                 0xEA
#define DFE_DACIF_GAIN                 0xDC

#define DFE_DP_DELAY_LOW_REG           0xF9
#define DFE_DP_DELAY_HIGH_REG          0xFA

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
#define DFE_AGC_DU_RB                  0xCF // Page 1 <5:0> dfe_agc_du_rb

#define HPF_CTRL_REG                   0x58
#define LPF_CTRL_REG                   0x57


#define DFE_FDC_IIR0_1                 0x87
#define DFE_FDC_IIR2_3                 0x88
#define DFE_FINETUNE_STEP_REG          0x84 

#define RF_RSSI_DB_RB                  0x2D

#define DIG2_RSSI_DB_RB_L              0x31
#define DIG2_RSSI_DB_RB_H              0x32

#define AGC_TOTALGAIN_RB_L             0x33
#define AGC_TOTALGAIN_RB_H             0x34

#define AGC_ATTN_LNA_BO                0x35

#define RSSI_THRESHOLD                 -3800 //-38dB 
#define AGC_DU_THRESHOLD               3000 //30dB
#define RF_RSSI_OFFSET                 400  //4dB 
#define DFE_RSSI_OFFSET                2200 //22dB 
#define DU_LEVEL_DIFF_THRESHOLD        1000 //20dB
#define HPF_FREQ_HZ_THRESHOLD          400000000 
#define LPF_FREQ_HZ_THRESHOLD          250000000 
#define WAIT_TIME_FOR_RSSI_MS          100 
#define MAX_WAIT_TIME_FOR_RSSI_MS      400 
#define WAIT_TIME_FOR_RSSI_STEP_MS     50 

#define FINE_TUNE_FREQ_DECREASE        0x01
#define FINE_TUNE_FREQ_INCREASE        0x02

#define RF_SX_FRAC_N_RANGE             0xDD
#define HIGH_IF_35250_KHZ              35250

#define MAX_LUT_SIZE                   8
#define MAX_DC_CAL_SAMPLES             50

#define MAX_ATV_DELAY_TIME_ONE_TENTH_US  756  //75.6 us 

#define APP_MODE_FREQ_HZ_THRESHOLD_1   358000000
#define APP_MODE_FREQ_HZ_THRESHOLD_2   625000000
#define APP_MODE_FREQ_HZ_THRESHOLD_3   700000000

#define SPUR_SHIFT_FREQ_WINDOW         500000  // +- 0.5MHz

#define IF_GAIN_SET_POINT1             10 
#define IF_GAIN_SET_POINT2             11 
#define IF_GAIN_SET_POINT3             12 

#define SPUR_SHIFT_CLOCK_ADJUST_MIN    205 
#define SPUR_SHIFT_CLOCK_ADJUST_MAX    227 

#define ANA_NTSC_FINETUNE_STEP_RB_MAX    0x63 
#define ANA_NTSC_FINETUNE_STEP_RB_MIN    0x23 
#define ANA_FINETUNE_STEP_RB_MAX         0x60 
#define ANA_FINETUNE_STEP_RB_MIN         0x20 

/******************************************************************************
    User-Defined Types (Typedefs)
******************************************************************************/

typedef struct
{
  UINT8 regAddr;
  UINT8 mask;
  UINT8 data;
} MXL661_REG_CTRL_INFO_T, *PMXL661_REG_CTRL_INFO_T;

typedef struct
{
  UINT8 i2cAddr;
  UINT8 xtalAmp_Rb;
  UINT8 xtalAmp_LinRb;
  UINT8 appMode;
} MXL661_XTAL_SPUR_CFG_T;

typedef struct
{
  UINT16 if_fcw_invert;
  UINT16 if_fcw_noninvert;  
} MXL661_IF_FCW_LUT_T;

typedef struct
{
  UINT8 i2cAddr;
  UINT8 if_sel;
  UINT8 if_fcw_byp;
  UINT8 if_invert;
  UINT32 manualIFOutFreqInKHz;
} MXL661_IF_FCW_CFG_T;

/******************************************************************************
    Global Variable Declarations
******************************************************************************/

extern MXL661_REG_CTRL_INFO_T MxL661_OverwriteDefaults[];
extern MXL661_REG_CTRL_INFO_T MxL661_AnalogNtsc[];
extern MXL661_REG_CTRL_INFO_T MxL661_AnalogPal[];
extern MXL661_REG_CTRL_INFO_T MxL661_AnalogSecam[];
extern MXL661_REG_CTRL_INFO_T MxL661_DigitalDvbc[];
extern MXL661_REG_CTRL_INFO_T MxL661_DigitalIsdbtAtsc[];
extern MXL661_REG_CTRL_INFO_T MxL661_DigitalDvbt[];

extern MXL661_REG_CTRL_INFO_T MxL661_Ntsc_RfLutSwpHIF[];
extern MXL661_REG_CTRL_INFO_T MxL661_Ntsc_16MHzRfLutSwpLIF[];
extern MXL661_REG_CTRL_INFO_T MxL661_Ntsc_24MHzRfLutSwpLIF[];

extern MXL661_REG_CTRL_INFO_T MxL661_Pal_RfLutSwpLIF[];
extern MXL661_REG_CTRL_INFO_T MxL661_PalD_RfLutSwpHIF[];
extern MXL661_REG_CTRL_INFO_T MxL661_PalI_RfLutSwpHIF[];
extern MXL661_REG_CTRL_INFO_T MxL661_PalBG_8MHzBW_RfLutSwpHIF[];
extern MXL661_REG_CTRL_INFO_T MxL661_PalBG_7MHzBW_RfLutSwpHIF[];
extern MXL661_REG_CTRL_INFO_T MxL661_Ntsc_HRCRfLutSwpLIF[];

/******************************************************************************
    Prototypes
******************************************************************************/

// Functions for register write operation 
MXL_STATUS MxL661_Ctrl_ProgramRegisters(UINT8 I2cAddr, PMXL661_REG_CTRL_INFO_T ctrlRegInfoPtr);
MXL_STATUS MxL661_Ctrl_WriteRegField(UINT8 I2cAddr, PMXL661_REG_CTRL_INFO_T ctrlRegInfoPtr); 

// Functions called by MxLWare API
MXL_STATUS MxL661_Ctrl_SetRfFreqLutReg(UINT8 i2cAddress, UINT32 FreqInHz, PMXL661_CHAN_DEPENDENT_FREQ_TABLE_T freqLutPtr);
MXL_STATUS MxL661_GetRFStrenth(UINT8 I2cTunerAddr, SINT32 *pRFStrength);
MXL_STATUS MxL661_GetRSSI(UINT8 I2cTunerAddr, SINT32 *pdfeRSSI);

REAL32 MxL661_GetTunerSignedBits(UINT32 bits, UINT8 signedUnsigned, UINT8 numBits, UINT8 fractionBit);
REAL64 MxL661_CalculateVariance(REAL32 *dataPtr, UINT8 numOfItems);
#endif /* __MXL661_TUNER_CFG_H__*/



