/*******************************************************************************
 *
 * FILE NAME          : MxL661_TunerSpurTable.h
 * 
 * AUTHOR             : Dong Liu
 *  
 * DATE CREATED       : 11/16/2011
 *
 * DESCRIPTION        : This file contains spur table definition.
 *
 *******************************************************************************
 *                Copyright (c) 2011, MaxLinear, Inc.
 ******************************************************************************/

#ifndef __MXL661_TUNER_SPUR_TABLE_H__
#define __MXL661_TUNER_SPUR_TABLE_H__

/******************************************************************************
    Include Header Files
    (No absolute paths - paths handled by make file)
******************************************************************************/
#include "MaxLinearDataTypes.h"

/******************************************************************************
    Macros
******************************************************************************/
#define   MXL661_MAX_SPUR_REG_NUM    4 
/******************************************************************************
    User-Defined Types (Typedefs)
******************************************************************************/
typedef struct
{
  UINT8 SpurRegNum;  
  UINT8 SpurRegAddr[MXL661_MAX_SPUR_REG_NUM];
} MXL661_CHAN_DEPENDENT_SPUR_REGISTER_T, *PMXL661_CHAN_DEPENDENT_SPUR_REGISTER_T;

typedef struct
{
  UINT32 centerFreqHz;
  UINT8  rfLutSwp1Reg;
  UINT8  rfLutDivInBypReg;
  UINT8  refLutBypReg;
  UINT8  refIntModReg;
} MXL661_CHAN_DEPENDENT_FREQ_TABLE_T, *PMXL661_CHAN_DEPENDENT_FREQ_TABLE_T;

/******************************************************************************
    Global Variable Declarations
******************************************************************************/
extern MXL661_CHAN_DEPENDENT_SPUR_REGISTER_T MxL661_SPUR_REGISTER;

extern MXL661_CHAN_DEPENDENT_FREQ_TABLE_T MXL661_NTSC_FREQ_LUT_XTAL_16MHZ_LIF[];
extern MXL661_CHAN_DEPENDENT_FREQ_TABLE_T MXL661_NTSC_FREQ_LUT_XTAL_24MHZ[];
extern MXL661_CHAN_DEPENDENT_FREQ_TABLE_T MXL661_NTSC_FREQ_LUT_HRC_16MHZ[];
extern MXL661_CHAN_DEPENDENT_FREQ_TABLE_T MXL661_NTSC_FREQ_LUT_HRC_24MHZ[];
extern MXL661_CHAN_DEPENDENT_FREQ_TABLE_T MXL661_NTSC_FREQ_LUT_IRC_16MHZ[];
extern MXL661_CHAN_DEPENDENT_FREQ_TABLE_T MXL661_NTSC_FREQ_LUT_IRC_24MHZ[];

extern MXL661_CHAN_DEPENDENT_FREQ_TABLE_T MXL661_PAL_BG_7MHZ_LUT_XTAL_16MHZ_LIF[];
extern MXL661_CHAN_DEPENDENT_FREQ_TABLE_T MXL661_PAL_BG_7MHZ_LUT_XTAL_24MHZ[];
extern MXL661_CHAN_DEPENDENT_FREQ_TABLE_T MXL661_PAL_BG_8MHZ_LUT_XTAL_16MHZ_LIF[];
extern MXL661_CHAN_DEPENDENT_FREQ_TABLE_T MXL661_PAL_BG_8MHZ_LUT_XTAL_24MHZ[];

extern MXL661_CHAN_DEPENDENT_FREQ_TABLE_T MXL661_PAL_D_LUT_XTAL_16MHZ_LIF[]; 
extern MXL661_CHAN_DEPENDENT_FREQ_TABLE_T MXL661_PAL_D_LUT_XTAL_24MHZ[]; 

extern MXL661_CHAN_DEPENDENT_FREQ_TABLE_T MXL661_PAL_I_LUT_XTAL_16MHZ_LIF[]; 
extern MXL661_CHAN_DEPENDENT_FREQ_TABLE_T MXL661_PAL_I_LUT_XTAL_24MHZ[]; 

extern MXL661_CHAN_DEPENDENT_FREQ_TABLE_T MXL661_SECAM_L_LUT_XTAL_16MHZ[];
extern MXL661_CHAN_DEPENDENT_FREQ_TABLE_T MXL661_SECAM_L_LUT_XTAL_24MHZ[];

extern MXL661_CHAN_DEPENDENT_FREQ_TABLE_T MXL661_PAL_D_LUT_XTAL_16MHZ_HIF[];
extern MXL661_CHAN_DEPENDENT_FREQ_TABLE_T MXL661_PAL_I_LUT_XTAL_16MHZ_HIF[]; 
extern MXL661_CHAN_DEPENDENT_FREQ_TABLE_T MXL661_PAL_BG_7MHZ_LUT_XTAL_16MHZ_HIF[];
extern MXL661_CHAN_DEPENDENT_FREQ_TABLE_T MXL661_PAL_BG_8MHZ_LUT_XTAL_16MHZ_HIF[];
extern MXL661_CHAN_DEPENDENT_FREQ_TABLE_T MXL661_NTSC_FREQ_LUT_XTAL_16MHZ_HIF[];

extern MXL661_CHAN_DEPENDENT_FREQ_TABLE_T MXL661_DIG_CABLE_FREQ_LUT_BW_6MHZ[];
extern MXL661_CHAN_DEPENDENT_FREQ_TABLE_T MXL661_DIG_CABLE_FREQ_LUT_BW_8MHZ[];
extern MXL661_CHAN_DEPENDENT_FREQ_TABLE_T MXL661_DIG_TERR_FREQ_LUT_BW_6MHZ[];
extern MXL661_CHAN_DEPENDENT_FREQ_TABLE_T MXL661_DIG_TERR_FREQ_LUT_BW_7MHZ[];
extern MXL661_CHAN_DEPENDENT_FREQ_TABLE_T MXL661_DIG_TERR_FREQ_LUT_BW_8MHZ[];

/******************************************************************************
    Prototypes
******************************************************************************/

#endif /* __MXL661_TUNER_SPUR_TABLE_H__*/



