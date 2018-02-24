/*******************************************************************************
 *
 * FILE NAME          : MxL661_TunerCfg.cpp
 *
 * AUTHOR             : Sunghoon Park
 *                      Dong Liu
 *
 * DATE CREATED       : 11/16/2011
 *                      11/20/2011 - MK
 *
 * DESCRIPTION        : This file contains demod and RF control parameters.
 *                      add a new function named MxL661_Ctrl_WriteRegField
 *
 *******************************************************************************
 *                Copyright (c) 2011, MaxLinear, Inc.
 ******************************************************************************/

#include "MxL661_TunerCfg.h"
#include "MxL_Debug.h"
#include <math.h>

MXL661_REG_CTRL_INFO_T MxL661_OverwriteDefaults[] =
{
  {0x00, 0xFF, 0x01},
  {0x96, 0xFF, 0x00},
  {0x00, 0xFF, 0x00},
  {0x14, 0xFF, 0x13},
  {0x6D, 0xFF, 0x8A},
  {0x6D, 0xFF, 0x0A},
  {0xDF, 0xFF, 0x19},
  {0x45, 0xFF, 0x1B},
  {0xA9, 0xFF, 0x59},
  {0xAA, 0xFF, 0x6A},
  {0xBE, 0xFF, 0x4C},
  {0xCF, 0xFF, 0x2A}, // 0x31},
  {0xD2, 0xFF, 0xF5}, // 0xFC},
  {0xD0, 0xFF, 0x34},
  {0x77, 0xFF, 0xE7},
  {0x78, 0xFF, 0xE3},
  {0x6F, 0xFF, 0x51},
  {0x7B, 0xFF, 0x84},
  {0x7C, 0xFF, 0x9F},
  {0x56, 0xFF, 0x41},
  {0xCD, 0xFF, 0x64},
  {0xC3, 0xFF, 0x2C},
  {0x9D, 0xFF, 0x61},
  {0xF7, 0xFF, 0x52},
  {0x58, 0xFF, 0x81},
  {0xB1, 0xFF, 0x30},
  {0,    0,    0}
};

// Analog NTSC application mode setting
MXL661_REG_CTRL_INFO_T MxL661_AnalogNtsc[] =
{
  {0x0C, 0xFF, 0x08},
 #ifdef  MXL661_ENABLE_MANUAL_AFC
  {0x13, 0xFB, 0x00},  // Protect Bit<2> of 0x13
 #else
  {0x13, 0xFF, 0x00},
 #endif
  {0x53, 0xFF, 0x7E},
  {0x57, 0xFF, 0x91},
  {0x5C, 0xFF, 0xB1},
  {0x62, 0xFF, 0xC2},
  {0x6E, 0xFF, 0x01},
  {0x6F, 0xFF, 0x51},
  {0x87, 0xFF, 0x56},
  {0x88, 0xFF, 0x44},
  {0x93, 0xFF, 0x33},
  {0x97, 0xFF, 0xA3},
  {0xBA, 0xFF, 0x40},
  {0x98, 0xFF, 0xA5},
  {0x9B, 0xFF, 0x20},
  {0x9C, 0xFF, 0x20},
  {0xA0, 0xFF, 0x10},
  {0xA5, 0xFF, 0x0F},
  {0xC2, 0xFF, 0xAB},
  {0xC5, 0xFF, 0x7C},
  {0xCD, 0xFF, 0x64}, // dfe_agc_rssi_cnt_thld = 100
  {0xCE, 0xFF, 0x7C},
  {0xD5, 0xFF, 0x05},
  {0xD9, 0xFF, 0x00},
  {0xEA, 0xFF, 0x00},
  {0xDC, 0xFF, 0x1C},
  {0,    0,    0}
};

// DFE_RFLUT_DIV_IN_SWP for NTSC HIF mode
MXL661_REG_CTRL_INFO_T MxL661_Ntsc_RfLutSwpHIF[] =
{
  {0x4A, 0xFF, 0x1B},
  {0x4B, 0xFF, 0x1A},
  {0x4C, 0xFF, 0x19},
  {0x4D, 0xFF, 0x16},
  {0x4E, 0xFF, 0x15},
  {0x4F, 0xFF, 0x14},
  {0x50, 0xFF, 0x13},
  {0x51, 0xFF, 0x12},
  {0x52, 0xFF, 0x17},
  {0,    0,    0}
};

// DFE_RFLUT_DIV_IN_SWP for NTSC - 16 MHz XTAL LIF mode
MXL661_REG_CTRL_INFO_T MxL661_Ntsc_16MHzRfLutSwpLIF[] =
{
  {0x4A, 0xFF, 0x1B},
  {0x4B, 0xFF, 0x1A},
  {0x4C, 0xFF, 0x19},
  {0x4D, 0xFF, 0x17},
  {0x4E, 0xFF, 0x16},
  {0x4F, 0xFF, 0x15},
  {0x50, 0xFF, 0x14},
  {0x51, 0xFF, 0x13},
  {0x52, 0xFF, 0x12},
  {0,    0,    0}
};

// DFE_RFLUT_DIV_IN_SWP for NTSC - 24 MHz XTAL LIF mode
MXL661_REG_CTRL_INFO_T MxL661_Ntsc_24MHzRfLutSwpLIF[] =
{
  {0x4A, 0xFF, 0x1C},
  {0x4B, 0xFF, 0x1B},
  {0x4C, 0xFF, 0x1A},
  {0x4D, 0xFF, 0x19},
  {0x4E, 0xFF, 0x17},
  {0x4F, 0xFF, 0x16},
  {0x50, 0xFF, 0x15},
  {0x51, 0xFF, 0x14},
  {0x52, 0xFF, 0x13},
  {0,    0,    0}
};

// DFE_RFLUT_DIV_IN_SWP for NTSC - HRC mode
MXL661_REG_CTRL_INFO_T MxL661_Ntsc_HRCRfLutSwpLIF[] =
{
  {0x4A, 0xFF, 0x1C},
  {0x4B, 0xFF, 0x1B},
  {0x4C, 0xFF, 0x1A},
  {0x4D, 0xFF, 0x19},
  {0x4E, 0xFF, 0x17},
  {0x4F, 0xFF, 0x16},
  {0x50, 0xFF, 0x15},
  {0x51, 0xFF, 0x14},
  {0x52, 0xFF, 0x13},
  {0xDD, 0xFF, 0x01},
  {0,    0,    0}
};

// DFE_RFLUT_DIV_IN_SWP settings mode PAL LIF
MXL661_REG_CTRL_INFO_T MxL661_Pal_RfLutSwpLIF[] =
{
  {0x4B, 0xFF, 0x1B},
  {0x4C, 0xFF, 0x1A},
  {0x4D, 0xFF, 0x19},
  {0x4E, 0xFF, 0x17},
  {0x4F, 0xFF, 0x16},
  {0x50, 0xFF, 0x15},
  {0x51, 0xFF, 0x14},
  {0x52, 0xFF, 0x13},
  {0,    0,    0}
};

// DFE_RFLUT_DIV_IN_SWP settings mode PAL-D HIF
MXL661_REG_CTRL_INFO_T MxL661_PalD_RfLutSwpHIF[] =
{
  {0x4B, 0xFF, 0x14},
  {0x4C, 0xFF, 0x13},
  {0x4D, 0xFF, 0x15},
  {0x4E, 0xFF, 0x1B},
  {0x4F, 0xFF, 0x1E},
  {0x50, 0xFF, 0x16},
  {0x51, 0xFF, 0x1A},
  {0x52, 0xFF, 0x19},
  {0,    0,    0}
};

// DFE_RFLUT_DIV_IN_SWP settings mode PAL-I HIF
MXL661_REG_CTRL_INFO_T MxL661_PalI_RfLutSwpHIF[] =
{
  {0x4B, 0xFF, 0x16},
  {0x4C, 0xFF, 0x15},
  {0x4D, 0xFF, 0x14},
  {0x4E, 0xFF, 0x13},
  {0x4F, 0xFF, 0x1B},
  {0x50, 0xFF, 0x19},
  {0x51, 0xFF, 0x1A},
  {0x52, 0xFF, 0x17},
  {0,    0,    0}
};

// DFE_RFLUT_DIV_IN_SWP settings mode PAL-BG 8 MHz BW HIF
MXL661_REG_CTRL_INFO_T MxL661_PalBG_8MHzBW_RfLutSwpHIF[] =
{
  {0x4B, 0xFF, 0x1B},
  {0x4C, 0xFF, 0x1A},
  {0x4D, 0xFF, 0x19},
  {0x4E, 0xFF, 0x17},
  {0x4F, 0xFF, 0x16},
  {0x50, 0xFF, 0x15},
  {0x51, 0xFF, 0x14},
  {0x52, 0xFF, 0x13},
  {0,    0,    0}
};

// DFE_RFLUT_DIV_IN_SWP settings mode PAL-BG 7 MHz BW HIF
MXL661_REG_CTRL_INFO_T MxL661_PalBG_7MHzBW_RfLutSwpHIF[] =
{
  {0x4B, 0xFF, 0x1B},
  {0x4C, 0xFF, 0x1A},
  {0x4D, 0xFF, 0x15},
  {0x4E, 0xFF, 0x14},
  {0x4F, 0xFF, 0x13},
  {0x50, 0xFF, 0x16},
  {0x51, 0xFF, 0x17},
  {0x52, 0xFF, 0x19},
  {0,    0,    0}
};

// Analog PAL application mode setting
MXL661_REG_CTRL_INFO_T MxL661_AnalogPal[] =
{
#ifdef	MXL661_ENABLE_MANUAL_AFC
  {0x13, 0xFB, 0x00},   // Protect Bit<2> of 0x13
#else
  {0x13, 0xFF, 0x00},
#endif
  {0x53, 0xFF, 0x7E},
  {0x57, 0xFF, 0x91},
  {0x5C, 0xFF, 0xB1},
  {0x62, 0xFF, 0xC2},
  {0x6E, 0xFF, 0x01},
  {0x6F, 0xFF, 0x51},
  {0x87, 0xFF, 0x56},
  {0x88, 0xFF, 0x44},
  {0x93, 0xFF, 0x33},
  {0x97, 0xFF, 0xA3},
  {0xBA, 0xFF, 0x40},
  {0x98, 0xFF, 0xA5},
  {0x9B, 0xFF, 0x20},
  {0x9C, 0xFF, 0x20},
  {0xA0, 0xFF, 0x00},
  {0xA5, 0xFF, 0x0F},
  {0xC2, 0xFF, 0xAB},
  {0xC5, 0xFF, 0x7C},
  {0xCD, 0xFF, 0x64}, // dfe_agc_rssi_cnt_thld = 100
  {0xCE, 0xFF, 0x7C},
  {0xD5, 0xFF, 0x05},
  {0xD9, 0xFF, 0x00},
  {0xEA, 0xFF, 0x00},
  {0x49, 0xFF, 0x1D},
  {0x4A, 0xFF, 0x1C},
  {0xDD, 0xFF, 0x06},
  {0xDC, 0xFF, 0x1C},
  {0,    0,    0}
};

// Analog SECAM application mode setting
MXL661_REG_CTRL_INFO_T MxL661_AnalogSecam[] =
{
  {0x13, 0xFF, 0x00},
  {0x53, 0xFF, 0x7E},
  {0x57, 0xFF, 0x91},
  {0x5C, 0xFF, 0xB1},
  {0x62, 0xFF, 0xC2},
  {0x6E, 0xFF, 0x01},
  {0x6F, 0xFF, 0x51},
  {0x87, 0xFF, 0x56},
  {0x88, 0xFF, 0x44},
  {0x93, 0xFF, 0x33},
  {0x97, 0xFF, 0xA3},
  {0xBA, 0xFF, 0x40},
  {0x98, 0xFF, 0x95},
//{0x9B, 0xFF, 0x66},
  {0x9B, 0xFF, 0x60},    // suggested by Jay(MXL engineer), modify the register to lock SECAM L'/L signal stably.
  {0x9C, 0xFF, 0x1F},
  {0xA0, 0xFF, 0x10},
  {0xA5, 0xFF, 0x0F},
  {0xC2, 0xFF, 0xA8},
  {0xC5, 0xFF, 0xBD},
  {0xCD, 0xFF, 0x64}, // dfe_agc_rssi_cnt_thld = 100
  {0xCE, 0xFF, 0x7C},
  {0xD5, 0xFF, 0x05},
  {0xD9, 0xFF, 0x00},
  {0xEA, 0xFF, 0x00},
  {0x49, 0xFF, 0x1D},
  {0x4A, 0xFF, 0x1C},
  {0x4B, 0xFF, 0x1B},
  {0x4C, 0xFF, 0x1A},
  {0x4D, 0xFF, 0x19},
  {0x4E, 0xFF, 0x17},
  {0x4F, 0xFF, 0x16},
  {0x50, 0xFF, 0x15},
  {0x51, 0xFF, 0x14},
  {0x52, 0xFF, 0x13},
  {0xDD, 0xFF, 0x06},
  {0xDC, 0xFF, 0x1C},
  {0,    0,    0}
};

// Digital DVB-C application mode setting
MXL661_REG_CTRL_INFO_T MxL661_DigitalDvbc[] =
{
  {0x0C, 0xFF, 0x00},
  {0x13, 0xFF, 0x04},
  {0x53, 0xFF, 0x7E},
  {0x57, 0xFF, 0x91},
  {0x5C, 0xFF, 0xB1},
  {0x62, 0xFF, 0xF2},
  {0x6E, 0xFF, 0x03},
  {0x6F, 0xFF, 0xD1},
  {0x87, 0xFF, 0x77},
  {0x88, 0xFF, 0x55},
  {0x93, 0xFF, 0x33},
  {0x97, 0xFF, 0x03},
  {0xBA, 0xFF, 0x40},
  {0x98, 0xFF, 0xAF},
  {0x9B, 0xFF, 0x20},
  {0x9C, 0xFF, 0x1E},
  {0xA0, 0xFF, 0x18},
  {0xA5, 0xFF, 0x09},
  {0xC2, 0xFF, 0xA9},
  {0xCD, 0xFF, 0x64}, // dfe_agc_rssi_cnt_thld = 100
  {0xCE, 0xFF, 0x7C},
  {0xC5, 0xFF, 0x7C},
  {0xD5, 0xFF, 0x05},
  {0xD9, 0xFF, 0x00},
  {0xEA, 0xFF, 0x00},
  {0xDC, 0xFF, 0x1C},
  {0,    0,    0}
};

// Digital ISDBT & ATSC application mode setting
MXL661_REG_CTRL_INFO_T MxL661_DigitalIsdbtAtsc[] =
{
  {0x0C, 0xFF, 0x00},
  {0x13, 0xFF, 0x04},
  {0x53, 0xFF, 0xFE},
  {0x57, 0xFF, 0x91}, // dig_ana_dnx_lna_bias = 0
  {0x62, 0xFF, 0xC2},
  {0x6E, 0xFF, 0x01},
  {0x6F, 0xFF, 0x51},
  {0x87, 0xFF, 0x77},
#ifdef MXL661_CUSTOMER_SPECIFIC_SETTING_1
  {0x88, 0xFF, 0x77},
#else
  {0x88, 0xFF, 0x55},
#endif
  {0x93, 0xFF, 0x22},
  {0x97, 0xFF, 0x02},
  {0xBA, 0xFF, 0x30},
  {0x98, 0xFF, 0xAF},
  {0x9B, 0xFF, 0x20},
  {0x9C, 0xFF, 0x1E},
  {0xA0, 0xFF, 0x18},
  {0xA5, 0xFF, 0x09},
  {0xC2, 0xFF, 0xA9},
  {0xC5, 0xFF, 0x7C},
//  {0xCD, 0xFF, 0xE8}, // dfe_agc_rssi_cnt_thld = 1000
//  {0xCE, 0xFF, 0x7F},
  {0xD5, 0xFF, 0x03},
  {0xD9, 0xFF, 0x04},
  {0x5B, 0xFF, 0x10},
  {0x5C, 0xFF, 0xB1},
  {0xB5, 0xFF, 0x63},
  {0,    0,    0}
};

// Digital DVB-T application mode setting
MXL661_REG_CTRL_INFO_T MxL661_DigitalDvbt[] =
{
  {0x13, 0xFF, 0x04},
  {0x0C, 0xFF, 0x00},
  {0x53, 0xFF, 0xFE},
  {0x57, 0xFF, 0x91}, // dig_ana_dnx_lna_bias = 0
  {0x62, 0xFF, 0xC2},
  {0x6E, 0xFF, 0x01},
  {0x6F, 0xFF, 0x51},
  {0x87, 0xFF, 0x77},
  {0x88, 0xFF, 0x55},
  {0x93, 0xFF, 0x22},
  {0x97, 0xFF, 0x02},
  {0xB5, 0xFF, 0x64}, // new Add (V4.1.2.4)
  {0xBA, 0xFF, 0x30},
  {0x98, 0xFF, 0xAF},
  {0x9B, 0xFF, 0x20},
  {0x9C, 0xFF, 0x1E},
  {0xA0, 0xFF, 0x18},
  {0xA5, 0xFF, 0x09},
  {0xC2, 0xFF, 0xA9},
  {0xC5, 0xFF, 0x7C},
  {0xD5, 0xFF, 0x03},
  {0xD9, 0xFF, 0x04},
  {0,    0,    0}
};

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_Ctrl_ProgramRegisters
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 07/23/2010
--|
--| DESCRIPTION   : This function writes multiple registers with provided data array.
--|
--| RETURN VALUE  : None
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL661_Ctrl_ProgramRegisters(UINT8 I2cAddr, PMXL661_REG_CTRL_INFO_T ctrlRegInfoPtr)
{
  MXL_STATUS status = MXL_TRUE;
  UINT16 i = 0;
  UINT8 tmp = 0;

  while (status == MXL_TRUE)
  {
    if ((ctrlRegInfoPtr[i].regAddr == 0) && (ctrlRegInfoPtr[i].mask == 0) && (ctrlRegInfoPtr[i].data == 0)) break;

    // Check if partial bits of register were updated
    if (ctrlRegInfoPtr[i].mask != 0xFF)
    {
      status = MxLWare661_OEM_ReadRegister(I2cAddr,ctrlRegInfoPtr[i].regAddr, &tmp);
      if (status != MXL_TRUE) break;;
    }

    tmp &= (UINT8) (~ctrlRegInfoPtr[i].mask);
    tmp |= (UINT8) (ctrlRegInfoPtr[i].data);

    status = MxLWare661_OEM_WriteRegister(I2cAddr,ctrlRegInfoPtr[i].regAddr, tmp);
    if (status != MXL_TRUE) break;

    i++;
  }

  return status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_Ctrl_WriteRegField
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 11/3/2009
--|
--| DESCRIPTION   : This function writes registers field that defined by Mask
--|                 and bit width. The write field position and width are defined
--|                 by mask byte. For example, if want to write 0x02 to a
--|                 register bit<5:4>, the input parameter shall be
--|                 ctrlRegInfoPtr struct:{ Reg_Addr, 0x30, (0x02)<<4 }
--|                 after writing, RegAddr content is --10---- (Bin Format)
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL661_Ctrl_WriteRegField(UINT8 I2cAddr, PMXL661_REG_CTRL_INFO_T ctrlRegInfoPtr)
{
  MXL_STATUS status;
  UINT8 tmp = 0;


  if ((ctrlRegInfoPtr->regAddr == 0) && (ctrlRegInfoPtr->mask == 0) && (ctrlRegInfoPtr->data == 0)) return MXL_FALSE;

  // Check if partial bits of register were updated
  if (ctrlRegInfoPtr->mask != 0xFF)
  {
      status = MxLWare661_OEM_ReadRegister(I2cAddr, ctrlRegInfoPtr->regAddr, &tmp);

      if (status != MXL_TRUE) return status;
   }

  // Clear the field that need to set value
  tmp &= (UINT8) (~ctrlRegInfoPtr->mask);
  tmp |= ( ctrlRegInfoPtr->data & ctrlRegInfoPtr->mask );

  status = MxLWare661_OEM_WriteRegister(I2cAddr, ctrlRegInfoPtr->regAddr, tmp);

  return status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_Ctrl_SetRfFreqLutReg
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 11/21/2011
--|
--| DESCRIPTION   : This function is called by MxL661_ConfigTunerChanTune,
--|                 configure 0xDC, 0xDD, 0xF0 and 0xF1 registers when XTAL is
--|                 16MHz and 24Hz case
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL661_Ctrl_SetRfFreqLutReg(UINT8 i2cAddress, UINT32 FreqInHz, PMXL661_CHAN_DEPENDENT_FREQ_TABLE_T freqLutPtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 idx = 0;
  UINT8 regSetData[MXL661_MAX_SPUR_REG_NUM] = {0, 0, 0, 0};

  if (freqLutPtr)
  {
    // Find and get default value firstly.
    for (idx = 0; 0 != freqLutPtr->centerFreqHz; idx++, freqLutPtr++)
    {
      if (freqLutPtr->centerFreqHz == 1)
      {
        // When center frequency is 1 means corresponding data is default value
        regSetData[0] = freqLutPtr->rfLutSwp1Reg;
        regSetData[1] = freqLutPtr->rfLutDivInBypReg;
        regSetData[2] = freqLutPtr->refLutBypReg;
        regSetData[3] = freqLutPtr->refIntModReg;

        break;
      } // end of if ((freqLutPtr->centerFreqHz -
    } // end of for (idx = 0;

    // Check in LUT
    for (idx = 0; 0 != freqLutPtr->centerFreqHz; idx++, freqLutPtr++)
    {
      if ((freqLutPtr->centerFreqHz - SPUR_SHIFT_FREQ_WINDOW) <= FreqInHz &&
          (freqLutPtr->centerFreqHz + SPUR_SHIFT_FREQ_WINDOW) >= FreqInHz)
      {
        regSetData[0] = freqLutPtr->rfLutSwp1Reg;
        regSetData[1] = freqLutPtr->rfLutDivInBypReg;
        regSetData[2] = freqLutPtr->refLutBypReg;
        regSetData[3] = freqLutPtr->refIntModReg;

        break;
      } // end of if ((freqLutPtr->centerFreqHz -
    } // end of for (idx = 0;
  }

  // Program registers
  for (idx = 0; idx < MxL661_SPUR_REGISTER.SpurRegNum; idx++)
    status |= MxLWare661_OEM_WriteRegister(i2cAddress, MxL661_SPUR_REGISTER.SpurRegAddr[idx], regSetData[idx]);

  return(MXL_STATUS)status;
}

/*--------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_GetRFStrenth
--|
--| AUTHOR        : Joy Zhang
--|
--| DATE CREATED  : 30/08/2013
--|
--| DESCRIPTION   : Read back RSSIRF, LNA BO and ATTN BO to calculate RF Strength.
--|                 Unit is 0.01dB.
--|
--| RETURN VALUE  : True or False
--|
--|-----------------------------------------------------------------------------*/
MXL_STATUS MxL661_GetRFStrenth(UINT8 I2cTunerAddr, SINT32 *pRFStrength)
{
  SINT32  dfeRfrssiDbCal;
  SINT32  dfeAgcAttnBoRb;
  SINT32  dfeAgcLnaBoRb;
  UINT8   status = MXL_TRUE;
  UINT8   readData=0;//fix coverity 90934

  status |= MxLWare661_OEM_ReadRegister(I2cTunerAddr, RF_RSSI_DB_RB, &readData);
  dfeRfrssiDbCal = (readData & 0xFF);
  dfeRfrssiDbCal = ((dfeRfrssiDbCal*100 + 8) / 16);

  status |= MxLWare661_OEM_ReadRegister(I2cTunerAddr, AGC_ATTN_LNA_BO, &readData);
  dfeAgcAttnBoRb = (readData & 0x0F);
  dfeAgcLnaBoRb  = (readData>>4) & 0x7;

  *pRFStrength = (dfeRfrssiDbCal+(3*(dfeAgcAttnBoRb + dfeAgcLnaBoRb)-40)*100);

  return (MXL_STATUS)status;
}

/*--------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_GetRSSI
--|
--| AUTHOR        : Joy Zhang
--|
--| DATE CREATED  : 30/08/2013
--|
--| DESCRIPTION   : Read back dfe_agc_slope, dfe_agc_gaincodeoffset, total_gain_code,
--|                 and RSSIDig2 to calculate RSSI, unit is 0.01dB.
--|
--| RETURN VALUE  : True or False
--|
--|-----------------------------------------------------------------------------*/
MXL_STATUS MxL661_GetRSSI(UINT8 I2cTunerAddr, SINT32 *pdfeRSSI)
{
  SINT32 dfeAgcTotalGain;
  SINT32 defAgcSlope;
  SINT32 dfeAgcGainOffset;
  SINT32 dfeRSSIDig2;
  UINT8  status = MXL_TRUE;
  UINT8  readData=0;//fix coverity 90935

  // Read dfe_agc_slope
  status |= MxLWare661_OEM_ReadRegister(I2cTunerAddr, AGC_SLOPE_REG, &readData);
  defAgcSlope = (readData & 0x07);
  defAgcSlope = ((defAgcSlope*100 + 2) / 4);

  // Read dfe_agc_gaincodeoffset
  status |= MxLWare661_OEM_ReadRegister(I2cTunerAddr, AGC_OFFSET_REG, &readData);
  dfeAgcGainOffset = (readData & 0x3F);

  // Read total_gain_code
  status |= MxLWare661_OEM_ReadRegister(I2cTunerAddr, AGC_TOTALGAIN_RB_L, &readData);
  dfeAgcTotalGain = (readData & 0xFF);
  status |= MxLWare661_OEM_ReadRegister(I2cTunerAddr, AGC_TOTALGAIN_RB_H, &readData);
  dfeAgcTotalGain |= ((readData & 0x1F) << 8);

  // Read RSSIDig2
  status |= MxLWare661_OEM_ReadRegister(I2cTunerAddr, DIG2_RSSI_DB_RB_L, &readData);
  dfeRSSIDig2 = (readData & 0xFF);
  status |= MxLWare661_OEM_ReadRegister(I2cTunerAddr, DIG2_RSSI_DB_RB_H, &readData);
  dfeRSSIDig2 |= ((readData & 0x1F) << 8);
  dfeRSSIDig2 = ((dfeRSSIDig2*100 +32 ) / 64 );

  if(dfeAgcGainOffset > dfeAgcTotalGain) return MXL_NOT_SUPPORTED;
  *pdfeRSSI = dfeRSSIDig2-(((dfeAgcTotalGain - dfeAgcGainOffset)*defAgcSlope+32)/64);

  return (MXL_STATUS)status;
}

#ifdef MXL661_ENABLE_TELETEXT_SPUR_FEATURE
/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_GetTunerSignedBits
--|
--| AUTHOR        : Brenndon Lee
--|
--| DATE CREATED  : 12/16/2008
--|
--| DESCRIPTION   : Convert data format to signed floating point number
--|
--| RETURN VALUE  : None
--|
--|---------------------------------------------------------------------------*/

REAL32 MxL661_GetTunerSignedBits(UINT32 bits, UINT8 signedUnsigned, UINT8 numBits, UINT8 fractionBit)
{
  SINT32 ConvertedData, SignMask;
  REAL32 result;

  // Check if the number is signed or not
  ConvertedData = 0;

  if (signedUnsigned == 1)
  {
    // Signed number. Check if it is negative number
    if ((bits >> (numBits - 1)) & 0x1)
    {
      // Negative number. Extend sign bit
      SignMask = 0xFFFFFFFF;
      SignMask <<= numBits;

      ConvertedData = SignMask;
    }
  }

  // Sign extented data
  ConvertedData |= bits;

  // Convert Data type
  // output = data / 2^(fractionBit)
  result = (REAL32)((REAL32)ConvertedData / pow((REAL32)2,fractionBit));

  MxL_DLL_DEBUG0("Sx = %lf \n", result);

  return result;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_CalculateVariance
--|
--| AUTHOR        : Mahendra Kondur
--|
--| DATE CREATED  : March 06, 2012
--|
--| DESCRIPTION   : This function used to calculate variance.
--|
--| RETURN VALUE  : None
--|
--|---------------------------------------------------------------------------*/

REAL64 MxL661_CalculateVariance(REAL32 *dataPtr, UINT8 numOfItems)
{
  REAL64 variance = 0.0;
  REAL64 mean = 0.0;
  REAL64 tmp = 0.0;
  UINT8 idx = 0;

  for (idx = 0; idx < numOfItems; idx++)
  {
    mean += (dataPtr[idx]);
  }

  // Calculate mean value
  mean = (mean/numOfItems);

  for (idx = 0; idx < numOfItems; idx++)
  {
    tmp = (dataPtr[idx] - mean);
    variance += (tmp * tmp);
  }

  // Calculate variance
  variance = (variance/numOfItems);

  return variance;
}
#endif
