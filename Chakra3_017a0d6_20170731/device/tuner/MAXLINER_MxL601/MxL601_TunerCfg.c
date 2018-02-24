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
 * FILE NAME          : MxL601_TunerCfg.cpp
 *
 * AUTHOR             : Sunghoon Park
 *                      Dong Liu
 *
 * DATE CREATED       : 11/16/2011
 *                      11/20/2011 - MK
 *
 * DESCRIPTION        : This file contains demod and RF control parameters.
 *                      add a new function named Ctrl_WriteRegField
 *
 *******************************************************************************
 *                Copyright (c) 2011, MaxLinear, Inc.
 ******************************************************************************/

#include "MxL601_TunerCfg.h"
#include "MxL_Debug.h"
#include <math.h>

REG_CTRL_INFO_T MxL_OverwriteDefaults[] =
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
  {0xCF, 0xFF, 0x25},
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
REG_CTRL_INFO_T AnalogNtsc[] =
{
  {0x0C, 0xFF, 0x08},
 #ifdef  ENABLE_MANUAL_AFC 	
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
REG_CTRL_INFO_T Ntsc_RfLutSwpHIF[] =
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
REG_CTRL_INFO_T Ntsc_16MHzRfLutSwpLIF[] =
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
REG_CTRL_INFO_T Ntsc_24MHzRfLutSwpLIF[] =
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
REG_CTRL_INFO_T Ntsc_HRCRfLutSwpLIF[] =
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
REG_CTRL_INFO_T Pal_RfLutSwpLIF[] =
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
REG_CTRL_INFO_T PalD_RfLutSwpHIF[] =
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
REG_CTRL_INFO_T PalI_RfLutSwpHIF[] =
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
REG_CTRL_INFO_T PalBG_8MHzBW_RfLutSwpHIF[] =
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
REG_CTRL_INFO_T PalBG_7MHzBW_RfLutSwpHIF[] =
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
REG_CTRL_INFO_T AnalogPal[] =
{
#ifdef	ENABLE_MANUAL_AFC
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
REG_CTRL_INFO_T AnalogSecam[] =
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
  {0x9B, 0xFF, 0x66},
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
REG_CTRL_INFO_T DigitalDvbc[] =
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
REG_CTRL_INFO_T DigitalIsdbtAtsc[] =
{
  {0x0C, 0xFF, 0x00},
  {0x13, 0xFF, 0x04},
  {0x53, 0xFF, 0xFE},
  {0x57, 0xFF, 0x91}, // dig_ana_dnx_lna_bias = 0
  {0x62, 0xFF, 0xC2},
  {0x6E, 0xFF, 0x01},
  {0x6F, 0xFF, 0x51},
  {0x87, 0xFF, 0x77},
#ifdef CUSTOMER_SPECIFIC_SETTING_1
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
  {0xCD, 0xFF, 0x64}, // dfe_agc_rssi_cnt_thld = 1000
  {0xCE, 0xFF, 0x7C},
  {0xB5, 0xFF, 0x63},
  {0xD5, 0xFF, 0x03},
  {0xD9, 0xFF, 0x04},
  {0,    0,    0}
};

// Digital DVB-T 6MHz application mode setting
REG_CTRL_INFO_T DigitalDvbt[] =
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
--| FUNCTION NAME : Ctrl_ProgramRegisters
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

MXL_STATUS Ctrl_ProgramRegisters(UINT8 I2cAddr, PREG_CTRL_INFO_T ctrlRegInfoPtr)
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
      status = Ctrl_ReadRegister(I2cAddr,ctrlRegInfoPtr[i].regAddr, &tmp);
      if (status != MXL_TRUE) break;;
    }

    tmp &= (UINT8) (~ctrlRegInfoPtr[i].mask);
    tmp |= (UINT8) (ctrlRegInfoPtr[i].data);

    status = Ctrl_WriteRegister(I2cAddr,ctrlRegInfoPtr[i].regAddr, tmp);
    if (status != MXL_TRUE) break;

    i++;
  }

  return status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : Ctrl_WriteRegField
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

MXL_STATUS Ctrl_WriteRegField(UINT8 I2cAddr, PREG_CTRL_INFO_T ctrlRegInfoPtr)
{
  MXL_STATUS status;
  UINT8 tmp = 0;


  if ((ctrlRegInfoPtr->regAddr == 0) && (ctrlRegInfoPtr->mask == 0) && (ctrlRegInfoPtr->data == 0)) return MXL_FALSE;

  // Check if partial bits of register were updated
  if (ctrlRegInfoPtr->mask != 0xFF)
  {
      status = Ctrl_ReadRegister(I2cAddr, ctrlRegInfoPtr->regAddr, &tmp);

      if (status != MXL_TRUE) return status;
   }

  // Clear the field that need to set value
  tmp &= (UINT8) (~ctrlRegInfoPtr->mask);
  tmp |= ( ctrlRegInfoPtr->data & ctrlRegInfoPtr->mask );

  status = Ctrl_WriteRegister(I2cAddr, ctrlRegInfoPtr->regAddr, tmp);

  return status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : Ctrl_SetRfFreqLutReg
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 11/21/2011
--|
--| DESCRIPTION   : This function is called by MxL601_ConfigTunerChanTune,
--|                 configure 0xDC, 0xDD, 0xF0 and 0xF1 registers when XTAL is
--|                 16MHz and 24Hz case
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS Ctrl_SetRfFreqLutReg(UINT8 i2cAddress, UINT32 FreqInHz, PCHAN_DEPENDENT_FREQ_TABLE_T freqLutPtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 idx = 0;
  UINT8 regSetData[MAX_SPUR_REG_NUM] = {0, 0, 0, 0};

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
  for (idx = 0; idx < MxL601_SPUR_REGISTER.SpurRegNum; idx++)
    status |= Ctrl_WriteRegister(i2cAddress, MxL601_SPUR_REGISTER.SpurRegAddr[idx], regSetData[idx]);

  return(MXL_STATUS)status;
}

#ifdef ENABLE_TELETEXT_SPUR_FEATURE
/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL_GetTunerSignedBits
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

REAL32 MxL_GetTunerSignedBits(UINT32 bits, UINT8 signedUnsigned, UINT8 numBits, UINT8 fractionBit)
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

  MxL_DLL_DEBUG0(printf("Sx = %lf \n", result));

  return result;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL_CalculateVariance
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

REAL64 MxL_CalculateVariance(REAL32 *dataPtr, UINT8 numOfItems)
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

