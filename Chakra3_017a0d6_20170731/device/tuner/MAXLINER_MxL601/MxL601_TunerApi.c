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
 * FILE NAME          : MxL601_TunerApi.cpp
 *
 * AUTHOR             : Sunghoon Park
 *                      Dong Liu
 *
 *
 * DATE CREATED       : 07/12/2011
 *                      3/14/2013
 *
 * DESCRIPTION        : This file contains MxL601 driver APIs
 *
 *
 *******************************************************************************
 *                Copyright (c) 2012, MaxLinear, Inc.
 ******************************************************************************/

#include <math.h>
#include "MxL601_TunerApi.h"
#include "MxL_Debug.h"

#define  BASIC_MXL601_I2C_ADDR      192 

/* MxLWare Driver version for MxL601 */
const UINT8 MxLWareDrvVersion[] = {2, 1, 10, 9}; 

// Candidate version number, 0 means for release version
const UINT8 BuildNumber = 0;

XTAL_SPUR_CFG_T xtalSpurCfg[MAX_MXL601_DEVICES] = {{BASIC_MXL601_I2C_ADDR, 0, 0, 99},
                                         {BASIC_MXL601_I2C_ADDR+2, 0, 0, 99},
                                         {BASIC_MXL601_I2C_ADDR+4, 0, 0, 99},
                                         {BASIC_MXL601_I2C_ADDR+6, 0, 0, 99},};
                                         //{0, 0, 0, 0}};

IF_FCW_CFG_T ifFcwCfg[MAX_MXL601_DEVICES] = {{BASIC_MXL601_I2C_ADDR, 0, 0, 0, 0},
                                   {BASIC_MXL601_I2C_ADDR+2, 0, 0, 0, 0},
                                   {BASIC_MXL601_I2C_ADDR+4, 0, 0, 0, 0},
                                   {BASIC_MXL601_I2C_ADDR+6, 0, 0, 0, 0},};
                                   //{0, 0, 0, 0}};

#ifdef CUSTOMER_SPECIFIC_SETTING_3
static IF_FCW_LUT_T ifFcwOverwriteTable[17] = {{0x0092, 0x0083},
                                               {0x009F, 0x0091},
                                               {0x00A3, 0x0094},
                                               {0x00A4, 0x0096},
                                               {0x00B2, 0x00A4},
                                               {0x00B4, 0x00A6},
                                               {0x00C5, 0x00B7},
                                               {0x00D3, 0x00C5},
                                               {0x00EB, 0x00DC},
                                               {0x00F5, 0x00E7},
                                               {0x0118, 0x010A},
                                               {0x0140, 0x0132},
                                               {0x0540, 0x0532},
                                               {0x055C, 0x054E},
                                               {0x0562, 0x0554},
                                               {0x0575, 0x0567},
                                               {0x068C, 0x067E}};
#endif

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL601_ConfigDevReset - MXL_DEV_SOFT_RESET_CFG
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 03/23/2011
--|
--| DESCRIPTION   : By writing any value into address 0xFF, all control
--|                 registers are initialized to the default value.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL601_ConfigDevReset(PMXL_RESET_CFG_T resetCfg)
{
  UINT8 status = MXL_TRUE;
  UINT8 idx = 0;

  MxL_DLL_DEBUG0(printf("\r\n MXL_DEV_SOFT_RESET_CFG \n"));

  // Write 0xFF with 0 to reset tuner
  status = Ctrl_WriteRegister(resetCfg->I2cSlaveAddr, AIC_RESET_REG, 0x00);

  for (idx = 0; idx < MAX_MXL601_DEVICES; idx++)
  {
    if (xtalSpurCfg[idx].i2cAddr == resetCfg->I2cSlaveAddr) break;
  }

  if (idx == MAX_MXL601_DEVICES)
  {
    /* This Device was never registered */
    /* Find empty slot */
    for (idx = 0; idx < MAX_MXL601_DEVICES; idx++)
    {
      if (xtalSpurCfg[idx].i2cAddr == 0) break;
    }

    /* No empty slot */
    if (idx == MAX_MXL601_DEVICES)
    {
      return MXL_FALSE;
    }
  }

  xtalSpurCfg[idx].i2cAddr = resetCfg->I2cSlaveAddr;
  xtalSpurCfg[idx].appMode = MXL_SIGNAL_NA;
  xtalSpurCfg[idx].xtalAmp_Rb = 0;
  xtalSpurCfg[idx].xtalAmp_LinRb = 0;

  ifFcwCfg[idx].i2cAddr = resetCfg->I2cSlaveAddr;
  ifFcwCfg[idx].if_sel = IF_FREQ_NA;

  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL601_ConfigDevOverwriteDefault -
--|                                               MXL_DEV_OVERWRITE_DEFAULT_CFG
--|
--| AUTHOR        : Sunghoon Park
--|                 Dong Liu
--|
--| DATE CREATED  : 06/14/2011
--|                 06/21/2011
--|
--| DESCRIPTION   : Register(s) that requires default values to be overwritten
--|                 during initialization
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL601_ConfigDevOverwriteDefault(PMXL_OVERWRITE_DEFAULT_CFG_T overDefaultPtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 readData = 0;

  MxL_DLL_DEBUG0(printf("MXL_DEV_OVERWRITE_DEFAULT_CFG \n"));
  status |= Ctrl_ProgramRegisters(overDefaultPtr->I2cSlaveAddr, MxL_OverwriteDefaults);

  status |= Ctrl_WriteRegister(overDefaultPtr->I2cSlaveAddr, 0x00, 0x01);
  status |= Ctrl_ReadRegister(overDefaultPtr->I2cSlaveAddr, 0x31, &readData);
  readData &= 0x2F;
  readData |= 0xD0;
  status |= Ctrl_WriteRegister(overDefaultPtr->I2cSlaveAddr, 0x31, readData);
  status |= Ctrl_WriteRegister(overDefaultPtr->I2cSlaveAddr, 0x00, 0x00);


  /* If Single supply 3.3v is used */
  if (MXL_ENABLE == overDefaultPtr->SingleSupply_3_3V)
    status |= Ctrl_WriteRegister(overDefaultPtr->I2cSlaveAddr, MAIN_REG_AMP, 0x04);

  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL601_ConfigDevPowerMode - MXL_DEV_POWER_MODE_CFG
--|
--| AUTHOR        : Dong Liu
--|                 Sunghoon Park
--|
--| DATE CREATED  : 06/21/2011
--|                 06/15/2011
--|
--| DESCRIPTION   : This API configures MxL601 power mode
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL601_ConfigDevPowerMode(PMXL_PWR_MODE_CFG_T pwrModePtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 i2cAddr;

  MxL_DLL_DEBUG0(printf("MXL_DEV_POWER_MODE_CFG \n"));
  i2cAddr = pwrModePtr->I2cSlaveAddr;

  switch(pwrModePtr->PowerMode)
  {
    case MXL_PWR_MODE_SLEEP:
      break;

    case MXL_PWR_MODE_ACTIVE:
      status |= Ctrl_WriteRegister(i2cAddr, TUNER_ENABLE_REG, MXL_ENABLE);
      status |= Ctrl_WriteRegister(i2cAddr, START_TUNE_REG, MXL_ENABLE);
      break;

    case MXL_PWR_MODE_STANDBY:
      status |= Ctrl_WriteRegister(i2cAddr, START_TUNE_REG, MXL_DISABLE);
      status |= Ctrl_WriteRegister(i2cAddr, TUNER_ENABLE_REG, MXL_DISABLE);
      break;

    default:
      return MXL_FALSE;
  }

  return(MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL601_ConfigDevXtalSet - MXL_DEV_XTAL_SET_CFG
--|
--| AUTHOR        : Sunghoon Park
--|                 Dong Liu
--|
--| DATE CREATED  : 11/13/2011 (MK) - Update Reg address for V2
--|                 08/29/2012 
--|
--| DESCRIPTION   : This API is used to configure XTAL settings of MxL601 tuner
--|                 device. XTAL settings include frequency, capacitance &
--|                 clock out
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL601_ConfigDevXtalSet(PMXL_XTAL_SET_CFG_T xtalSetPtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 control = 0;

  MxL_DLL_DEBUG0(printf("MXL_DEV_XTAL_SET_CFG \n"));

  // XTAL freq and cap setting, Freq set is located at bit<5>, cap bit<4:0>
  control = (UINT8)((xtalSetPtr->XtalFreqSel << 5) | (xtalSetPtr->XtalCap & 0x1F));
  control |= (xtalSetPtr->ClkOutEnable << 7);
  status |= Ctrl_WriteRegister(xtalSetPtr->I2cSlaveAddr, XTAL_CAP_CTRL_REG, control);

  // XTAL frequency div 4 setting <1> and  XTAL clock out enable <0>
  // XTAL sharing mode in slave
  control = (0x01 & (UINT8)xtalSetPtr->ClkOutDiv);
  if (xtalSetPtr->XtalSharingMode == MXL_ENABLE) 
  { 
    control |= 0x40; 
  status |= Ctrl_WriteRegister(xtalSetPtr->I2cSlaveAddr, XTAL_ENABLE_DIV_REG, control);
    status |= Ctrl_WriteRegister(xtalSetPtr->I2cSlaveAddr, XTAL_EXT_BIAS_REG, 0x80);
  }
  else 
  {
    control &= 0x01; 
    status |= Ctrl_WriteRegister(xtalSetPtr->I2cSlaveAddr, XTAL_ENABLE_DIV_REG, control); 
    status |= Ctrl_WriteRegister(xtalSetPtr->I2cSlaveAddr, XTAL_EXT_BIAS_REG, 0x0A);
  }

  // Main regulator re-program
  if (MXL_ENABLE == xtalSetPtr->SingleSupply_3_3V)
    status |= Ctrl_WriteRegister(xtalSetPtr->I2cSlaveAddr, MAIN_REG_AMP, 0x14);

  return(MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL601_ConfigDevIfOutSet - MXL_DEV_IF_OUT_CFG
--|
--| AUTHOR        : Sunghoon Park
--|                 Dong Liu
--|
--| DATE CREATED  : 06/15/2011
--|                 09/22/2011
--|
--| DESCRIPTION   : This function is used to configure IF out settings of MxL601
--|                 tuner device.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL601_ConfigDevIfOutSet(PMXL_IF_OUT_CFG_T ifOutPtr)
{
  UINT16 ifFcw;
  UINT8 status = MXL_TRUE;
  UINT8 readData = 0;
  UINT8 control = 0;
  UINT8 idx = 0;

  MxL_DLL_DEBUG0(printf("MXL_DEV_IF_OUT_CFG: Manual set = %d \n", ifOutPtr->ManualFreqSet));

  for (idx = 0; idx < MAX_MXL601_DEVICES; idx++)
  {
    if (ifFcwCfg[idx].i2cAddr == ifOutPtr->I2cSlaveAddr) break;
  }

  if (idx >= 4) return (MXL_STATUS)status;

  // Read back register for manual IF Out
  status |= Ctrl_ReadRegister(ifOutPtr->I2cSlaveAddr, IF_FREQ_SEL_REG, &readData);

  if(ifOutPtr->ManualFreqSet == MXL_ENABLE)
  {

    ifFcwCfg[idx].if_fcw_byp = 1;
    ifFcwCfg[idx].manualIFOutFreqInKHz = ifOutPtr->ManualIFOutFreqInKHz;

    // IF out manual setting : bit<5>
    readData |= 0x20;
    status |= Ctrl_WriteRegister(ifOutPtr->I2cSlaveAddr, IF_FREQ_SEL_REG, readData);

    MxL_DLL_DEBUG0(printf("Manual Freq set = %d \n", ifOutPtr->ManualIFOutFreqInKHz));

    // Manual IF freq set
    ifFcw = (UINT16)(ifOutPtr->ManualIFOutFreqInKHz * 8192 / 216000);
    control = (ifFcw & 0xFF); // Get low 8 bit
    status |= Ctrl_WriteRegister(ifOutPtr->I2cSlaveAddr, IF_FCW_LOW_REG, control);

    control = ((ifFcw >> 8) & 0x0F); // Get high 4 bit
    status |= Ctrl_WriteRegister(ifOutPtr->I2cSlaveAddr, IF_FCW_HIGH_REG, control);
  }
  else
  {
    ifFcwCfg[idx].if_fcw_byp = 0;
    ifFcwCfg[idx].if_sel = ifOutPtr->IFOutFreq;

    // bit<5> = 0, use IF frequency from IF frequency table
    readData &= 0xC0;

    // IF Freq <4:0>
    readData |= ifOutPtr->IFOutFreq;
    status |= Ctrl_WriteRegister(ifOutPtr->I2cSlaveAddr, IF_FREQ_SEL_REG, readData);
  }

  // Set spectrum invert, gain level and IF path
  // Spectrum invert indication is bit<7:6>
  if (MXL_ENABLE == ifOutPtr->IFInversion)
  {
    ifFcwCfg[idx].if_invert = 1;
    control = 0x3 << 6;
  }
  else
  {
    ifFcwCfg[idx].if_invert = 0;
  }

  // Path selection is bit<5:4>
  control += ((ifOutPtr->PathSel & 0x03) << 4);

  // Gain level is bit<3:0>
  control += (ifOutPtr->GainLevel & 0x0F);
  status |= Ctrl_WriteRegister(ifOutPtr->I2cSlaveAddr, IF_PATH_GAIN_REG, control);

  return(MXL_STATUS) status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL601_ConfigDevGPO - MXL_DEV_GPO_CFG
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 3/24/2011
--|
--| DESCRIPTION   : This API configures GPOs of MxL601 tuner device.
--|                 (General Purpose Output Port) of the MxL601.
--|                 There are 3 GPOs in MxL601
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS  MxL601_ConfigDevGPO(PMXL_GPO_CFG_T gpoParamPtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 regData = 0;

  MxL_DLL_DEBUG0(printf("MXL_DEV_GPO_CFG \n"));

  status |= Ctrl_ReadRegister(gpoParamPtr->I2cSlaveAddr, GPO_SETTING_REG, &regData);

  switch (gpoParamPtr->GPOId)
  {
    case GPO1:
      if (PORT_AUTO_CTRL == gpoParamPtr->GPOState)
      {
        regData &= 0xFE;
      }
      else
      {
        regData &= 0xFC;
        // Bit<0> = 1, user manual set GP1
        regData |= (UINT8)(0x01 | (gpoParamPtr->GPOState << 1));
      }
      break;

    case GPO2:
      if (PORT_AUTO_CTRL == gpoParamPtr->GPOState)
      {
        regData &= 0xFB;
      }
      else
      {
        regData &= 0xF3;
        // Bit<2> = 1, user manual set GP2
        regData |= (UINT8) (0x04 | (gpoParamPtr->GPOState << 3));
      }
      break;

    case GPO3:
      if (PORT_AUTO_CTRL == gpoParamPtr->GPOState)
      {
        regData &= 0xEF;
      }
      else
      {
        regData &= 0xCF;

        // Bit<4> = 1, user manual set GP3
        regData |= (UINT8)(0x10 | (gpoParamPtr->GPOState << 5));
      }
      break;

    default:
      status |= MXL_FALSE;
      break;
  }

  if (MXL_FALSE != status)
    status |= Ctrl_WriteRegister(gpoParamPtr->I2cSlaveAddr, GPO_SETTING_REG, regData);

  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL601_GetDeviceInfo - MXL_DEV_ID_VERSION_REQ
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 6/21/2011
--|
--| DESCRIPTION   : This function is used to get MxL601 version information.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL601_GetDeviceInfo(PMXL_DEV_INFO_T DevInfoPtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 readBack = 0;
  UINT8 i2cAddr = 0;
  UINT8 k = 0;

  MxL_DLL_DEBUG0(printf("MXL_DEV_ID_VERSION_REQ \n"));

  i2cAddr = DevInfoPtr->I2cSlaveAddr;

  status |= Ctrl_ReadRegister(i2cAddr, CHIP_ID_REQ_REG, &readBack);
  DevInfoPtr->ChipId = (readBack & 0xFF);

  status |= Ctrl_ReadRegister(i2cAddr, CHIP_VERSION_REQ_REG, &readBack);
  DevInfoPtr->ChipVersion = (readBack & 0xFF);

  MxL_DLL_DEBUG0(printf("Chip ID = 0x%d, Version = 0x%d \n", DevInfoPtr->ChipId, DevInfoPtr->ChipVersion));

  // Get MxLWare version infromation
  for (k = 0; k < MXL_VERSION_SIZE; k++)
    DevInfoPtr->MxLWareVer[k] = MxLWareDrvVersion[k];

  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL601_GetDeviceGpoState - MXL_DEV_GPO_STATE_REQ
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 3/24/2011
--|
--| DESCRIPTION   : This API is used to get GPO's status information from
--|                 MxL601 tuner device
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS  MxL601_GetDeviceGpoState(PMXL_GPO_INFO_T gpoPtr)
{
  MXL_STATUS status = MXL_TRUE;
  UINT8 regData = 0;

  MxL_DLL_DEBUG0(printf("MXL_DEV_GPO_STATE_REQ \n"));

  status = Ctrl_ReadRegister(gpoPtr->I2cSlaveAddr, GPO_SETTING_REG, &regData);

  // GPO1 bit<1:0>
  if ((regData & 0x01) == 0) gpoPtr->GPO1 = PORT_AUTO_CTRL;
  else gpoPtr->GPO1 = (MXL_GPO_STATE_E)((regData & 0x02) >> 1);

  // GPO2 bit<3:2>
  if ((regData & 0x04) == 0) gpoPtr->GPO2 = PORT_AUTO_CTRL;
  else gpoPtr->GPO2 = (MXL_GPO_STATE_E)((regData & 0x08) >> 3);

  // GPO3 bit<5:4>
  if ((regData & 0x10) == 0) gpoPtr->GPO3 = PORT_AUTO_CTRL;
  else gpoPtr->GPO3 = (MXL_GPO_STATE_E)((regData & 0x20) >> 5);

  return status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL601_GetDevicePllState - MXL_DEV_PLL_STATE_REQ
--| 
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 11/20/2012
--|
--| DESCRIPTION   : This API is used to inquire PLL state. 
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS  MxL601_GetDevicePllState(PMXL_PLL_INFO_T pllPtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 condition[3] = {0};
  UINT8 regAddr[7] = {0x2B, 0x30, 0x32, 0x34, 0x2F, 0x31, 0x33};
  UINT8 k, regData[7] = {0}; 

  MxL_DLL_DEBUG0(printf("MXL_DEV_PLL_STATE_REQ \n")); 
  pllPtr->PllState = PLL_STATE_NA; 

  for (k = 0; k < 7; k++)
  {
    // inquire PLL circuitry status and RSSI read back registers  
    status |= Ctrl_ReadRegister(pllPtr->I2cSlaveAddr, regAddr[k], &regData[k]);
  }

  if ((MXL_STATUS)status == MXL_SUCCESS)
  {
    // Check 0x2B register 
    condition[0] = (regData[0] != 0x07)? 1 : 0;

    // Check if register 0x30, 0x32, 0x34 values are all 0 
    condition[1] = ((regData[1] == 0) && (regData[2] == 0) && (regData[3] == 0)) ? 1: 0; 

    // Check if register 0x30, 0x32, 0x34 values are all 0 
    condition[2] = ((regData[1] == regData[2]) && (regData[2] == regData[3]) 
                 && (regData[4] == regData[5]) && (regData[5] == regData[6])) ? 1: 0;

    if ((condition[0] == 1) || (condition[1] == 1) || (condition[2] == 1))
      pllPtr->PllState = PLL_STATE_WRONG; 
    else 
      pllPtr->PllState = PLL_STATE_NORMAL; 
  }

  MxL_DLL_DEBUG0(printf("Tuner PLL state = %d (0:Normal, 1:Wrong) \n", pllPtr->PllState));
  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL601_ConfigTunerEnableState - MXL_TUNER_POWER_UP_CFG
--|
--| AUTHOR        : Dong Liu
--|                 Sunghoon Park
--|
--| DATE CREATED  : 1/27/2011
--|                 6/22/2011
--|
--| DESCRIPTION   : This function is used to power up/down MxL601 tuner module
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL601_ConfigTunerPowerUp(PMXL_POWER_UP_CFG_T topMasterCfgPtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 regData = 0;

  MxL_DLL_DEBUG0(printf("MXL_TUNER_POWER_UP_CFG, ENABLE = %d \n", topMasterCfgPtr->Enable));

  // Power up tuner <0> = 1 for enable, 0 for disable
  if (MXL_ENABLE == topMasterCfgPtr->Enable) regData |= 0x01;

  status = Ctrl_WriteRegister(topMasterCfgPtr->I2cSlaveAddr, TUNER_ENABLE_REG, regData);

  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL601_ConfigTunerSequenceSet - MXL_TUNER_START_TUNE_CFG
--|
--| AUTHOR        : Sunghoon Park
--|                 Dong Liu
--|                 Mahee
--|
--|
--| DATE CREATED  : 03/24/2011
--|                 06/18/2012
--|                 09/23/2011 - 1.1.11.1
--|                 Change in flow chart for resetting RSSI when START_TUNE = 1
--|                 N+1 blocker settings for Analog modes - 05/18
--|
--| DESCRIPTION   : This function is used to start or abort channel tune.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL601_ConfigTunerSequenceSet(PMXL_START_TUNE_CFG_T sequnCfgPtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 regData = 0;
  UINT8 idx = 0;
  MxL_DLL_DEBUG0(printf("MXL_TUNER_START_TUNE_CFG, SEQUENCE SET = %d \n", sequnCfgPtr->StartTune));

  status |= Ctrl_WriteRegister(sequnCfgPtr->I2cSlaveAddr, START_TUNE_REG, 0x00);

  if (sequnCfgPtr->StartTune == MXL_ENABLE)
  {

    for (idx = 0; idx < MAX_MXL601_DEVICES; idx++)
    {
      if (xtalSpurCfg[idx].i2cAddr == sequnCfgPtr->I2cSlaveAddr)
        break;
    }

    // Set DIG_ANA_XTAL_CLK_EN_BYPS = 1 before start tune 
    status |= Ctrl_ReadRegister(sequnCfgPtr->I2cSlaveAddr, 0x6E, &regData); 
    status |= Ctrl_WriteRegister(sequnCfgPtr->I2cSlaveAddr, 0x6E, (regData | 0x80)); 
    
    status |= Ctrl_ReadRegister(sequnCfgPtr->I2cSlaveAddr, 0x14, &regData);
    status |= Ctrl_WriteRegister(sequnCfgPtr->I2cSlaveAddr, 0x14, (regData & 0xDF));

    // Bit <0> 1 : start , 0 : abort calibrations
    status |= Ctrl_WriteRegister(sequnCfgPtr->I2cSlaveAddr, START_TUNE_REG, 0x01);
    MxL_Sleep(10);

    // Resume DIG_ANA_XTAL_CLK_EN_BYPS = 0 after start tune 
    status |= Ctrl_ReadRegister(sequnCfgPtr->I2cSlaveAddr, 0x6E, &regData); 
    status |= Ctrl_WriteRegister(sequnCfgPtr->I2cSlaveAddr, 0x6E, (regData & 0x7F)); 

#ifdef CUSTOMER_SPECIFIC_SETTING_3		

    status |= Ctrl_WriteRegister(sequnCfgPtr->I2cSlaveAddr, 0x14, (regData | 0x20));

    status |= Ctrl_ReadRegister(sequnCfgPtr->I2cSlaveAddr, 0x13, &regData);

     // Check if signal type is Analog
    if (xtalSpurCfg[idx].appMode == ANA_NTSC_MODE)
    {
      // Apply N+1 blocker settings
      status |= Ctrl_WriteRegister(sequnCfgPtr->I2cSlaveAddr, DFE_FINETUNE_STEP_REG, 0x83);
    }
    else
    {
      // Undo N+1 blocker settings if app mode is not NTSC
      status |= Ctrl_WriteRegister(sequnCfgPtr->I2cSlaveAddr, DFE_FINETUNE_STEP_REG, 0x80);
    }
    regData &= 0xFC; // Set Bit<1:0> = 00
    status |= Ctrl_WriteRegister(sequnCfgPtr->I2cSlaveAddr, 0x13, regData);
    regData |= 0x01; // Set Bit<1:0> = 01
    status |= Ctrl_WriteRegister(sequnCfgPtr->I2cSlaveAddr, 0x13, regData);
#endif 	
  }

  return(MXL_STATUS) status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL601_ConfigTunerApplicationModeSet - MXL_TUNER_MODE_CFG
--| 
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 07/13/2012
--|
--| DESCRIPTION   : This fucntion is used to configure MxL601 tuner's 
--|                 application modes like DVB-T, DTMB, DVB-C, ISDB-T, PAL, SECAM, 
--|                 ATSC, NTSC etc.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL601_ConfigTunerApplicationModeSet(PMXL_TUNER_MODE_CFG_T modeSetPtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 dfeRegData = 0;
  REG_CTRL_INFO_T* tmpRegTable = NULL;
  UINT8 idx = 0;
#ifdef CUSTOMER_SPECIFIC_SETTING_3  
  UINT8 regData = 0;
  UINT16 ifFcw = 0;
#endif
  {
    MxL_DLL_DEBUG0(printf("MXL_TUNER_MODE_CFG, application mode = %d , IF = %d\n",
                                                            modeSetPtr->SignalMode,
                                                            modeSetPtr->IFOutFreqinKHz));

    switch(modeSetPtr->SignalMode)
    {
      // Application modes settings for NTSC mode
      case ANA_NTSC_MODE:
        tmpRegTable = AnalogNtsc;
        status |= Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, tmpRegTable);

        if (modeSetPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ)
        {
          // Low power IF dependent settings
        #ifdef CUSTOMER_SPECIFIC_SETTING_1
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xFE);
        #else
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0x7E);
        #endif
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x10);

          if (modeSetPtr->XtalFreqSel == XTAL_16MHz)
          {
            tmpRegTable = Ntsc_16MHzRfLutSwpLIF;
            dfeRegData = 0x00;
          }
          else
          {
            tmpRegTable = Ntsc_24MHzRfLutSwpLIF;
            dfeRegData = 0x01;
          }

          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, 0xDD, dfeRegData);

        }
        else
        {
          // High power IF dependent settings
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xD9);
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x16);

          tmpRegTable = Ntsc_RfLutSwpHIF;
        }

        if (tmpRegTable)
          status |= Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, tmpRegTable);
        else
          status |= MXL_FALSE;

        break;

      // Application modes settings for PAL-BG mode
      case ANA_PAL_BG:

        tmpRegTable = AnalogPal;
        status |= Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, tmpRegTable);

        if (modeSetPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ)
        {
          // Low power IF dependent settings
        #ifdef CUSTOMER_SPECIFIC_SETTING_1
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xFE);
        #else
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0x7E);
        #endif
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x10);

          status |= Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, Pal_RfLutSwpLIF);
        }
        else
        {
          // High power IF dependent settings
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xD9);
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x16);
        }

        break;

      // Application modes settings for PAL-I mode
      case ANA_PAL_I:
        status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, 0x0C, 0x0B);

        tmpRegTable = AnalogPal;
        status |= Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, tmpRegTable);

        if (modeSetPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ)
        {
          // Low power IF dependent settings
#ifdef CUSTOMER_SPECIFIC_SETTING_1
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xFE);
#else
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0x7E);
#endif
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x10);

          status |= Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, Pal_RfLutSwpLIF);
        }
        else
        {
          // High power IF dependent settings
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xD9);
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x16);

          status |= Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, PalI_RfLutSwpHIF);

        }

        break;

      // Application modes settings for PAL-D mode
      case ANA_PAL_D:
        status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, 0x0C, 0x0C);

        tmpRegTable = AnalogPal;
        status |= Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, tmpRegTable);
        status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, 0x9B, 0x40);//Mstar Add for ATV disturb

        if (modeSetPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ)
        {
          // Low power IF dependent settings
#ifdef CUSTOMER_SPECIFIC_SETTING_1
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xFE);
#else
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0x7E);
#endif
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x10);

          status |= Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, Pal_RfLutSwpLIF);
        }
        else
        {
          // High power IF dependent settings
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xD9);
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x16);

          status |= Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, PalD_RfLutSwpHIF);

        }
        break;

      // Application modes settings for SECAM-I mode
      case ANA_SECAM_I:
        status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, 0x0C, 0x0B);

        tmpRegTable = AnalogSecam;
        status |= Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, tmpRegTable);

        if (modeSetPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ)
        {
          // Low power IF dependent settings
#ifdef CUSTOMER_SPECIFIC_SETTING_1
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xFE);
#else
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0x7E);
#endif
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x10);
        }
        else
        {
          // High power IF dependent settings
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xD9);
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x16);
        }
        break;

      // Application modes settings for SECAM-L mode
      case ANA_SECAM_L:
        status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, 0x0C, 0x0C);

        tmpRegTable = AnalogSecam;
        status |= Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, tmpRegTable);

        if (modeSetPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ)
        {
          // Low power IF dependent settings
#ifdef CUSTOMER_SPECIFIC_SETTING_1
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xFE);
#else
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0x7E);
#endif
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x10);
        }
        else
        {
          // High power IF dependent settings
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xD9);
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x16);
        }
        break;

      // Application modes settings for Analog TV scan mode, DVB-C/J.83B modes
      case ATV_SCAN:
      case DIG_DVB_C:
      case DIG_J83B:
        tmpRegTable = DigitalDvbc;
        status |= Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, tmpRegTable);

        if (modeSetPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ)
        {
          // Low power IF dependent settings
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xFE);
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x10);
        }
        else
        {
          // High power IF dependent settings
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xD9);
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x16);
        }

        if (modeSetPtr->XtalFreqSel == XTAL_16MHz) dfeRegData = 0x0D;
        else dfeRegData = 0x0E;

        status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DFE_CSF_SS_SEL, dfeRegData);

        break;

      // Application modes settings for ISDB-T & ATSC modes
      case DIG_ISDBT_ATSC:
        tmpRegTable = DigitalIsdbtAtsc;
        status |= Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, tmpRegTable);

        if (modeSetPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ)
        {
          // Low power IF dependent settings
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xFE);
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x10);
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_PWR, 0xB1);
        }
        else
        {
          // High power IF dependent settings
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xD9);
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x16);
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_PWR, 0xB1);
        }

        if (XTAL_16MHz == modeSetPtr->XtalFreqSel) dfeRegData = 0x0D;
        else if (XTAL_24MHz == modeSetPtr->XtalFreqSel) dfeRegData = 0x0E;

        status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DFE_CSF_SS_SEL, dfeRegData);

        dfeRegData = 0x1C;

        // IF gain dependent settings
        switch(modeSetPtr->IFOutGainLevel)
        {
          case 0x09: dfeRegData = 0x44; break;
          case 0x08: dfeRegData = 0x43; break;
          case 0x07: dfeRegData = 0x42; break;
          case 0x06: dfeRegData = 0x41; break;
          case 0x05: dfeRegData = 0x40; break;
          default: break;
        }
        status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DFE_DACIF_GAIN, dfeRegData);

        break;

      // Application modes settings for DVB-T mode and DTMB
      case DIG_DVB_T_DTMB:
        tmpRegTable = DigitalDvbt;
        status |= Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, tmpRegTable);

        if (modeSetPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ)
        {
          // Low power IF dependent settings
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xFE);
          //status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x18);
          //status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_PWR, 0xF1);
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x10);//Mstar modify to increse large output level
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_PWR, 0xB1);//Mstar modify to increse large output level
        }
        else
        {
          // High power IF dependent settings
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xD9);
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x16);
          status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_PWR, 0xB1);
        }

        if (XTAL_16MHz == modeSetPtr->XtalFreqSel) dfeRegData = 0x0D;
        else if (XTAL_24MHz == modeSetPtr->XtalFreqSel) dfeRegData = 0x0E;

        status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DFE_CSF_SS_SEL, dfeRegData);

        dfeRegData = 0;
        // IF gain dependent settings
        switch(modeSetPtr->IFOutGainLevel)
        {
          case 0x09: dfeRegData = 0x44; break;
          case 0x08: dfeRegData = 0x43; break;
          case 0x07: dfeRegData = 0x42; break;
          case 0x06: dfeRegData = 0x41; break;
          case 0x05: dfeRegData = 0x40; break;
          default: break;
        }

        status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, DFE_DACIF_GAIN, dfeRegData);
        break;

      default:
        status |= MXL_FALSE;
        break;
    }

  }

  if (MXL_FALSE != status)
  {
    //status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, 0x6D, 0x00);
    status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, XTAL_EXT_BIAS_REG, 0x0A);

    // XTAL calibration
    status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, XTAL_CALI_SET_REG, 0x00);
    status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, XTAL_CALI_SET_REG, 0x01);

    // 50 ms sleep after XTAL calibration
    MxL_Sleep(50);

    // Only for Analog modes
    if (modeSetPtr->SignalMode <= ANA_SECAM_L)
    {
      // read data to improve xtal spurs - to be used during channel tune function
      for (idx = 0; idx < MAX_MXL601_DEVICES; idx++)
      {
#ifdef CUSTOMER_SPECIFIC_SETTING_3
        if (modeSetPtr->SignalMode == ANA_NTSC_MODE)
        {
          if (ifFcwCfg[idx].i2cAddr == modeSetPtr->I2cSlaveAddr)
          {
            if (ifFcwCfg[idx].if_fcw_byp == 0)
            {
              status |= Ctrl_ReadRegister(modeSetPtr->I2cSlaveAddr, IF_FREQ_SEL_REG, &regData);
              status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, IF_FREQ_SEL_REG, (regData | 0x20));

              if (ifFcwCfg[idx].if_invert == 0)
                ifFcw = ifFcwOverwriteTable[ifFcwCfg[idx].if_sel].if_fcw_noninvert;
              else
                ifFcw = ifFcwOverwriteTable[ifFcwCfg[idx].if_sel].if_fcw_invert;
            }
            else
            {
              if (ifFcwCfg[idx].if_invert == 0)
                ifFcw = (UINT16)((ifFcwCfg[idx].manualIFOutFreqInKHz - 188) * 8192 / 216000);
              else
                ifFcw = (UINT16)((ifFcwCfg[idx].manualIFOutFreqInKHz + 188) * 8192 / 216000);
            }

            regData = (UINT8)(ifFcw & 0x00FF);
            status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, IF_FCW_LOW_REG, regData);

            regData = (UINT8)((ifFcw >> 8) & 0x000F);
            status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, IF_FCW_HIGH_REG, regData);

          }
        }
        else
        {
          // Apply IF frequency values for other application modes, without offset
          if (ifFcwCfg[idx].i2cAddr == modeSetPtr->I2cSlaveAddr)
          {
            status |= Ctrl_ReadRegister(modeSetPtr->I2cSlaveAddr, IF_FREQ_SEL_REG, &regData);

            // IF value from pre-set IF_SEL table
            if (ifFcwCfg[idx].if_fcw_byp == 0)
            {
              regData &= 0xC0;
              regData |= ifFcwCfg[idx].if_sel; // saved IF Freq value from IF_SEL table
              status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, IF_FREQ_SEL_REG, regData);
            }
            else
            {
              // IF out manual setting : bit<5>
              regData |= 0x20;
              status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, IF_FREQ_SEL_REG, regData);

              // Manual IF freq set
              ifFcw = (UINT16)(ifFcwCfg[idx].manualIFOutFreqInKHz * 8192 / 216000);
              regData = (ifFcw & 0xFF); // Get low 8 bit
              status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, IF_FCW_LOW_REG, regData);

              regData = ((ifFcw >> 8) & 0x0F); // Get high 4 bit
              status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, IF_FCW_HIGH_REG, regData);

            }
          }
        }
 #endif  
        if (xtalSpurCfg[idx].i2cAddr == modeSetPtr->I2cSlaveAddr)
        {
          // If previous Application mode is PAL-BG & current mode
          // is also PAL B/G then do not read reg values.
          if (!((xtalSpurCfg[idx].appMode == (UINT8)ANA_PAL_BG) && (modeSetPtr->SignalMode == ANA_PAL_BG)))
          {
            // change page to 1
            status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, 0x00, 0x01);

            // read reg ana_dig_refsx_xtal_amp_rb
            status |= Ctrl_ReadRegister(modeSetPtr->I2cSlaveAddr, 0xA2, &xtalSpurCfg[idx].xtalAmp_Rb);

            // read reg ana_dig_refsx_xtal_amp_lin_rb
            status |= Ctrl_ReadRegister(modeSetPtr->I2cSlaveAddr, 0xA1, &xtalSpurCfg[idx].xtalAmp_LinRb);

            xtalSpurCfg[idx].xtalAmp_LinRb &= 0x30;
            xtalSpurCfg[idx].xtalAmp_LinRb >>= 4;

            // change page to 0
            status |= Ctrl_WriteRegister(modeSetPtr->I2cSlaveAddr, 0x00, 0x00);

            xtalSpurCfg[idx].appMode = (UINT8)modeSetPtr->SignalMode;

          }
        }
      }
    }
   if(idx<MAX_MXL601_DEVICES)
    {
        xtalSpurCfg[idx].appMode = (UINT8)modeSetPtr->SignalMode;
    }
  }

  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL601_ConfigTunerAgcSet - MXL_TUNER_AGC_CFG
--|
--| AUTHOR        : Dong Liu
--|                 Sunghoon Park
--|
--| DATE CREATED  : 06/21/2011
--|                 04/21/2011
--|                 11/13/2011 (MK) - Change bit address for AGC Type function.
--|
--| DESCRIPTION   : This function is used to configure AGC settings of MxL601
--|                 tuner device.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL601_ConfigTunerAgcSet(PMXL_AGC_SET_CFG_T agcSetPtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 regData = 0;

  MxL_DLL_DEBUG0(printf("MXL_TUNER_AGC_CFG, AGC mode = %d, sel = %d, set point = %d",
    agcSetPtr->AgcSel, agcSetPtr->AgcType, agcSetPtr->SetPoint));

  // AGC selecton <3:2> and mode setting <0>
  status |= Ctrl_ReadRegister(agcSetPtr->I2cSlaveAddr, AGC_CONFIG_REG, &regData);
  regData &= 0xF2; // Clear bits <3:2> & <0>
  regData = (UINT8) (regData | (agcSetPtr->AgcType << 2) | agcSetPtr->AgcSel);
  status |= Ctrl_WriteRegister(agcSetPtr->I2cSlaveAddr, AGC_CONFIG_REG, regData);

  // AGC set point <6:0>
  status |= Ctrl_ReadRegister(agcSetPtr->I2cSlaveAddr, AGC_SET_POINT_REG, &regData);
  regData &= 0x80; // Clear bit <6:0>
  regData |= agcSetPtr->SetPoint;
  status |= Ctrl_WriteRegister(agcSetPtr->I2cSlaveAddr, AGC_SET_POINT_REG, regData);

  // AGC Polarity <4>
  status |= Ctrl_ReadRegister(agcSetPtr->I2cSlaveAddr, AGC_FLIP_REG, &regData);
  regData &= 0xEF; // Clear bit <4>
  regData |= (agcSetPtr->AgcPolarityInverstion << 4);
  status |= Ctrl_WriteRegister(agcSetPtr->I2cSlaveAddr, AGC_FLIP_REG, regData);

  return(MXL_STATUS) status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL601_ConfigTunerFineTune - MXL_TUNER_FINE_TUNE_CFG
--|
--| AUTHOR        : Dong Liu
--|                 Sunghoon Park
--|
--| DATE CREATED  : 06/25/2012
--|                 04/22/2011
--|
--| DESCRIPTION   : This function is used to control fine tune step (freq offset)
--|                 when MxL601 is used in Analog mode.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL601_ConfigTunerFineTune(PMXL_FINE_TUNE_CFG_T fineTunePtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 regData = 0;

  MxL_DLL_DEBUG0(printf("MXL_TUNER_FINE_TUNE_CFG, fine tune = %d", fineTunePtr->ScaleUp));

  status |= Ctrl_ReadRegister(fineTunePtr->I2cSlaveAddr, DFE_FINETUNE_STEP_REG, &regData);
  if ((regData & 0x80) == 0x80)  // Fine tune is by passed
  {
    regData &= 0x7F;
    status |= Ctrl_WriteRegister(fineTunePtr->I2cSlaveAddr, DFE_FINETUNE_STEP_REG, regData); // Set Bit<7> = 0
  }

  status |= Ctrl_ReadRegister(fineTunePtr->I2cSlaveAddr, FINE_TUNE_SET_REG, &regData);

  // Fine tune <1:0>
  regData &= 0xFC;
  status |= Ctrl_WriteRegister(fineTunePtr->I2cSlaveAddr, FINE_TUNE_SET_REG, regData);

  if (MXL_FINE_TUNE_STEP_UP == fineTunePtr->ScaleUp)
    regData |= FINE_TUNE_FREQ_INCREASE;
  else
    regData |= FINE_TUNE_FREQ_DECREASE;

  status |= Ctrl_WriteRegister(fineTunePtr->I2cSlaveAddr, FINE_TUNE_SET_REG, regData);

  return(MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL601_ConfigTunerEnableFineTune -
--|                                           MXL_TUNER_ENABLE_FINE_TUNE_CFG
--|
--| AUTHOR        : Sunghoon Park
--|                 Dong Liu
--|
--| DATE CREATED  : 04/22/2011
--|                 07/01/2011
--|
--| DESCRIPTION   : This fucntion is used to enable or disable fine tune function
--|                 when MxL601 device is used in Analog mode.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

static MXL_STATUS MxL601_ConfigTunerEnableFineTune(PMXL_ENABLE_FINE_TUNE_CFG_T fineTunePtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 fineTuneReg1 = 0;
  UINT8 fineTuneReg2 = 0;

  MxL_DLL_DEBUG0(printf("MXL_TUNER_ENABLE_FINE_TUNE_CFG, fine tune = %d", fineTunePtr->EnableFineTune));

  status |= Ctrl_ReadRegister(fineTunePtr->I2cSlaveAddr, FINE_TUNE_CTRL_REG_0, &fineTuneReg1);
  status |= Ctrl_ReadRegister(fineTunePtr->I2cSlaveAddr, FINE_TUNE_CTRL_REG_1, &fineTuneReg2);

  if (MXL_ENABLE == fineTunePtr->EnableFineTune)
  {
    fineTuneReg1 |= 0x04;
    fineTuneReg2 |= 0x20;
  }
  else
  {
    fineTuneReg1 &= 0xF8;
    fineTuneReg2 &= 0xDF;
  }

  status |= Ctrl_WriteRegister(fineTunePtr->I2cSlaveAddr, FINE_TUNE_CTRL_REG_0, fineTuneReg1);
  status |= Ctrl_WriteRegister(fineTunePtr->I2cSlaveAddr, FINE_TUNE_CTRL_REG_1, fineTuneReg2);

  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL601_ConfigTunerChanTune - MXL_TUNER_CHAN_TUNE_CFG
--|
--| AUTHOR        : Sunghoon Park
--|                 Mahendra Kondur
--|                 Dong Liu
--|
--| DATE CREATED  : 3/17/2011
--|                 04/21/2012 - S1 blocker improvements for PAL-D
--|                 07/13/2012 - S1 special setting for customer   
--|                 08/30/2012 
--|
--| DESCRIPTION   : This API configures RF channel frequency and bandwidth.
--|                 Radio Frequency unit is Hz, and Bandwidth is in MHz units.
--|                 For analog broadcast standards, corresponding spur shifitng
--|                 settiings will be aplied.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

static MXL_STATUS MxL601_ConfigTunerChanTune(PMXL_TUNER_TUNE_CFG_T tuneParamPtr)
{
  UINT32 frequency;
  UINT32 freq = 0;
  UINT8 status = MXL_TRUE;
  UINT8 regData = 0;
  UINT8 idx = 0;
  SINT16 tmpData = 0;
#ifdef CUSTOMER_SPECIFIC_SETTING_1
  MXL_ENABLE_FINE_TUNE_CFG_T fineTuneCfg;
#endif
  CHAN_DEPENDENT_FREQ_TABLE_T *freqLutPtr = NULL;

  MxL_DLL_DEBUG0(printf("MXL_TUNER_CHAN_TUNE_CFG, signal type = %d (%d), Freq = %d, BW = %d, Xtal = %d \n",
                                              tuneParamPtr->SignalMode,
                                              tuneParamPtr->NtscCarrier,
                                              tuneParamPtr->FreqInHz,
                                              tuneParamPtr->BandWidth,
                                              tuneParamPtr->XtalFreqSel));

  if ((tuneParamPtr->SignalMode <= ANA_SECAM_L) && (tuneParamPtr->TuneType == VIEW_MODE))
  {
    // RF Frequency VCO Band Settings
    regData = 0;
    if (tuneParamPtr->FreqInHz < APP_MODE_FREQ_HZ_THRESHOLD_3) 
    {
      status |= Ctrl_WriteRegister(tuneParamPtr->I2cSlaveAddr, 0x7C, 0x1F);
      if ((tuneParamPtr->SignalMode == DIG_DVB_C) || (tuneParamPtr->SignalMode == DIG_J83B)
           || (tuneParamPtr->SignalMode == ATV_SCAN) )
        regData = 0xC1;
      else
        regData = 0x81;

    }
    else
    {
      status |= Ctrl_WriteRegister(tuneParamPtr->I2cSlaveAddr, 0x7C, 0x9F);

      if ((tuneParamPtr->SignalMode == DIG_DVB_C) || (tuneParamPtr->SignalMode == DIG_J83B)
          || (tuneParamPtr->SignalMode == ATV_SCAN))
        regData = 0xD1;
      else
        regData = 0x91;

    }

    status |= Ctrl_WriteRegister(tuneParamPtr->I2cSlaveAddr, 0x00, 0x01);
    status |= Ctrl_WriteRegister(tuneParamPtr->I2cSlaveAddr, 0x31, regData);
    status |= Ctrl_WriteRegister(tuneParamPtr->I2cSlaveAddr, 0x00, 0x00);

    switch(tuneParamPtr->SignalMode)
    {
      // Signal type is NTSC mode
      case ANA_NTSC_MODE:

        // If 16MHz XTAL is used then need to program registers based on frequency value
        if (XTAL_16MHz == tuneParamPtr->XtalFreqSel)
        {
          if (MXL_NTSC_CARRIER_NA == tuneParamPtr->NtscCarrier)
          {
            // Select spur shifting LUT to be used based NTSC, HRC or IRC frequency
            if ((tuneParamPtr->FreqInHz % 1000000) == 0)
            {
              // Apply spur shifting LUT based on HIF or LIF setting
              if (tuneParamPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ) freqLutPtr = NTSC_FREQ_LUT_XTAL_16MHZ_LIF;
              else freqLutPtr = NTSC_FREQ_LUT_XTAL_16MHZ_HIF;

            }
            else if ((tuneParamPtr->FreqInHz % 12500) == 0)
            {
              freqLutPtr = NTSC_FREQ_LUT_IRC_16MHZ;
            }
            else
            {
              freqLutPtr = NTSC_FREQ_LUT_HRC_16MHZ;
              status |= Ctrl_ProgramRegisters(tuneParamPtr->I2cSlaveAddr, Ntsc_HRCRfLutSwpLIF);
            }

          }
          else
          {
            // Select LUT based on NTSC carriers
            if (MXL_NTSC_CARRIER_HRC == tuneParamPtr->NtscCarrier)
            {
              freqLutPtr = NTSC_FREQ_LUT_HRC_16MHZ;
              status |= Ctrl_ProgramRegisters(tuneParamPtr->I2cSlaveAddr, Ntsc_HRCRfLutSwpLIF);
            }
            else
            {
              freqLutPtr = NTSC_FREQ_LUT_IRC_16MHZ;
            }

          }

        } // end of if (16 MHz XTAL
        else if (XTAL_24MHz == tuneParamPtr->XtalFreqSel)
        {
          if (MXL_NTSC_CARRIER_NA == tuneParamPtr->NtscCarrier)
          {
            // Select spur shifting LUT to be used based NTSC, HRC or IRC frequency
            if ((tuneParamPtr->FreqInHz % 1000000) == 0)
            {
              freqLutPtr = NTSC_FREQ_LUT_XTAL_24MHZ;
            }
            else if ((tuneParamPtr->FreqInHz % 12500) == 0)
            {
              freqLutPtr = NTSC_FREQ_LUT_IRC_24MHZ;
            }
            else
            {
              freqLutPtr = NTSC_FREQ_LUT_HRC_24MHZ;
              status |= Ctrl_ProgramRegisters(tuneParamPtr->I2cSlaveAddr, Ntsc_HRCRfLutSwpLIF);
            }

          }
          else
          {
             // Select LUT based on NTSC carriers
            if (MXL_NTSC_CARRIER_HRC == tuneParamPtr->NtscCarrier)
            {
              freqLutPtr = NTSC_FREQ_LUT_HRC_24MHZ;
              status |= Ctrl_ProgramRegisters(tuneParamPtr->I2cSlaveAddr, Ntsc_HRCRfLutSwpLIF);
            }
            else
            {
              freqLutPtr = NTSC_FREQ_LUT_IRC_24MHZ;
            }

          }

        } // end of if (24 MHz XTAL

        if (freqLutPtr)
          status |= Ctrl_SetRfFreqLutReg(tuneParamPtr->I2cSlaveAddr, tuneParamPtr->FreqInHz, freqLutPtr);

        break;

      // Signal type is PAL D
      case ANA_PAL_D:

        // If 16MHz XTAL is used then need to program registers based on frequency value
        if (XTAL_16MHz == tuneParamPtr->XtalFreqSel)
        {
          if (tuneParamPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ) freqLutPtr = PAL_D_LUT_XTAL_16MHZ_LIF;
          else freqLutPtr = PAL_D_LUT_XTAL_16MHZ_HIF;

        } // end of if (16 MHz XTAL
        else if (XTAL_24MHz == tuneParamPtr->XtalFreqSel)
        {
          freqLutPtr = PAL_D_LUT_XTAL_24MHZ;
        } // end of if (24 MHz XTAL

        if (freqLutPtr)
          status |= Ctrl_SetRfFreqLutReg(tuneParamPtr->I2cSlaveAddr, tuneParamPtr->FreqInHz, freqLutPtr);

        // For PAL-D, additional registers need to be programmed for
        // S1 blocker performance improvement in VHF channels.
        if (tuneParamPtr->FreqInHz >= APP_MODE_FREQ_HZ_THRESHOLD_1)
        {
          status |= Ctrl_WriteRegister(tuneParamPtr->I2cSlaveAddr, 0x93, 0x33);
          status |= Ctrl_WriteRegister(tuneParamPtr->I2cSlaveAddr, 0x94, 0x44);
          status |= Ctrl_WriteRegister(tuneParamPtr->I2cSlaveAddr, 0xBA, 0x40);
          status |= Ctrl_WriteRegister(tuneParamPtr->I2cSlaveAddr, 0x5D, 0x0E);
        }
        else
        {
          status |= Ctrl_WriteRegister(tuneParamPtr->I2cSlaveAddr, 0x93, 0x44);
          status |= Ctrl_WriteRegister(tuneParamPtr->I2cSlaveAddr, 0x94, 0x55);
          status |= Ctrl_WriteRegister(tuneParamPtr->I2cSlaveAddr, 0xBA, 0x50);
          status |= Ctrl_WriteRegister(tuneParamPtr->I2cSlaveAddr, 0x5D, 0x0F);
        }

        break;

      case ANA_PAL_BG:

        switch(tuneParamPtr->BandWidth)
        {
          case ANA_TV_DIG_CABLE_BW_7MHz:
            regData = 0x09;
            break;

          case ANA_TV_DIG_CABLE_BW_8MHz:
            regData = 0x0A;
            break;

          case ANA_TV_DIG_CABLE_BW_6MHz:
          case DIG_TERR_BW_6MHz:
          case DIG_TERR_BW_7MHz:
          case DIG_TERR_BW_8MHz:
          default:
            break;
        }

        status |= Ctrl_WriteRegister(tuneParamPtr->I2cSlaveAddr, 0x0C, regData);

        // If 16MHz XTAL is used then need to program registers based on frequency value
        if (XTAL_16MHz == tuneParamPtr->XtalFreqSel)
        {
          // PAL - BG 7 MHz Frequency range
          if (ANA_TV_DIG_CABLE_BW_7MHz == tuneParamPtr->BandWidth)
          {
            if (tuneParamPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ)
            {
              freqLutPtr = PAL_BG_7MHZ_LUT_XTAL_16MHZ_LIF;
              status |= Ctrl_ProgramRegisters(tuneParamPtr->I2cSlaveAddr, Pal_RfLutSwpLIF);
            }
            else
            {
              freqLutPtr = PAL_BG_7MHZ_LUT_XTAL_16MHZ_HIF;
              status |= Ctrl_ProgramRegisters(tuneParamPtr->I2cSlaveAddr, PalBG_7MHzBW_RfLutSwpHIF);
            }

          }
          else
          {
            if (tuneParamPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ)
            {
              freqLutPtr = PAL_BG_8MHZ_LUT_XTAL_16MHZ_LIF;
              status |= Ctrl_ProgramRegisters(tuneParamPtr->I2cSlaveAddr, Pal_RfLutSwpLIF);
            }
            else
            {
              freqLutPtr = PAL_BG_8MHZ_LUT_XTAL_16MHZ_HIF;
              status |= Ctrl_ProgramRegisters(tuneParamPtr->I2cSlaveAddr, PalBG_8MHzBW_RfLutSwpHIF);
            }
          }

        } // end of if (XTAL_16MHz
        else if (XTAL_24MHz == tuneParamPtr->XtalFreqSel)
        {
          // If 16MHz XTAL is used then need to program registers based on frequency value
          // PAL - BG 7 MHz Frequency range
          if (ANA_TV_DIG_CABLE_BW_7MHz == tuneParamPtr->BandWidth)
          {
            freqLutPtr = PAL_BG_7MHZ_LUT_XTAL_24MHZ;

            if (tuneParamPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ)
              status |= Ctrl_ProgramRegisters(tuneParamPtr->I2cSlaveAddr, Pal_RfLutSwpLIF);
            else
              status |= Ctrl_ProgramRegisters(tuneParamPtr->I2cSlaveAddr, PalBG_7MHzBW_RfLutSwpHIF);

          }
          else
          {
            freqLutPtr = PAL_BG_8MHZ_LUT_XTAL_24MHZ;

            if (tuneParamPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ)
              status |= Ctrl_ProgramRegisters(tuneParamPtr->I2cSlaveAddr, Pal_RfLutSwpLIF);
            else
              status |= Ctrl_ProgramRegisters(tuneParamPtr->I2cSlaveAddr, PalBG_8MHzBW_RfLutSwpHIF);

          }

        } // end of if (XTAL_24MHz

        if (freqLutPtr)
          status |= Ctrl_SetRfFreqLutReg(tuneParamPtr->I2cSlaveAddr, tuneParamPtr->FreqInHz, freqLutPtr);

        break;

      case ANA_PAL_I:

        // If 16MHz XTAL is used then need to program registers based on frequency value
        if (XTAL_16MHz == tuneParamPtr->XtalFreqSel)
        {
          if (tuneParamPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ) freqLutPtr = PAL_I_LUT_XTAL_16MHZ_LIF;
          else freqLutPtr = PAL_I_LUT_XTAL_16MHZ_HIF;
        }
        else
        {
          freqLutPtr = PAL_I_LUT_XTAL_24MHZ;
        }

        if (freqLutPtr)
          status |= Ctrl_SetRfFreqLutReg(tuneParamPtr->I2cSlaveAddr, tuneParamPtr->FreqInHz, freqLutPtr);

        break;

      case ANA_SECAM_L:

        // If 16MHz XTAL is used then need to program registers based on frequency value
        if (XTAL_16MHz == tuneParamPtr->XtalFreqSel)
        {
          freqLutPtr = SECAM_L_LUT_XTAL_16MHZ;
        } // end of if (16 MHz XTAL
        else
        {
          freqLutPtr = SECAM_L_LUT_XTAL_24MHZ;
        }

        if (freqLutPtr)
          status |= Ctrl_SetRfFreqLutReg(tuneParamPtr->I2cSlaveAddr, tuneParamPtr->FreqInHz, freqLutPtr);
        break;

      case ATV_SCAN:
      case DIG_DVB_C:
      case DIG_J83B:
        if ((tuneParamPtr->BandWidth == DIG_TERR_BW_6MHz) || (tuneParamPtr->BandWidth == DIG_TERR_BW_8MHz))
        {
          if (tuneParamPtr->BandWidth == DIG_TERR_BW_6MHz) freqLutPtr = DIG_CABLE_FREQ_LUT_BW_6MHZ;
          else freqLutPtr = DIG_CABLE_FREQ_LUT_BW_8MHZ;

          status |= Ctrl_SetRfFreqLutReg(tuneParamPtr->I2cSlaveAddr, tuneParamPtr->FreqInHz, freqLutPtr);
        }
        break;

      case DIG_ISDBT_ATSC:
      case DIG_DVB_T_DTMB:

        if (tuneParamPtr->BandWidth == DIG_TERR_BW_6MHz) freqLutPtr = DIG_TERR_FREQ_LUT_BW_6MHZ;
        else if (tuneParamPtr->BandWidth == DIG_TERR_BW_7MHz) freqLutPtr = DIG_TERR_FREQ_LUT_BW_7MHZ;
        else freqLutPtr = DIG_TERR_FREQ_LUT_BW_8MHZ;

        status |= Ctrl_SetRfFreqLutReg(tuneParamPtr->I2cSlaveAddr, tuneParamPtr->FreqInHz, freqLutPtr);
        break;

      case MXL_SIGNAL_NA:
      default:
        break;
    }
  }

  // Tune mode <0>
  status |= Ctrl_ReadRegister(tuneParamPtr->I2cSlaveAddr, TUNE_MODE_REG, &regData);
  regData &= 0xFE;

  if (SCAN_MODE == tuneParamPtr->TuneType) regData |= 0x01;

  status |= Ctrl_WriteRegister(tuneParamPtr->I2cSlaveAddr, TUNE_MODE_REG, regData);

  // Bandwidth <7:0>
  status |= Ctrl_WriteRegister(tuneParamPtr->I2cSlaveAddr, CHAN_TUNE_BW_REG, (UINT8)tuneParamPtr->BandWidth);

  // Frequency
  frequency = tuneParamPtr->FreqInHz / 1000;

  /* Calculate RF Channel = DIV(64*RF(Hz), 1E6) */
  frequency *= 64;
  freq = (UINT32)((frequency + 500)/ 1000); // Round operation 

  // Set RF
  status |= Ctrl_WriteRegister(tuneParamPtr->I2cSlaveAddr, CHAN_TUNE_LOW_REG, (UINT8)(freq & 0xFF));
  status |= Ctrl_WriteRegister(tuneParamPtr->I2cSlaveAddr, CHAN_TUNE_HI_REG, (UINT8)((freq >> 8 ) & 0xFF));

  // Only for Analog modes
  if (tuneParamPtr->SignalMode <= ANA_SECAM_L)
  {
    // apply xtal spur improvement settings
    for (idx = 0; idx < MAX_MXL601_DEVICES; idx++)
    {
      if (xtalSpurCfg[idx].i2cAddr == tuneParamPtr->I2cSlaveAddr)
      {
        regData = 0x80;
        tmpData = (xtalSpurCfg[idx].xtalAmp_Rb + xtalSpurCfg[idx].xtalAmp_LinRb);

        //if ((tuneParamPtr->FreqInHz < 300000000) && (tuneParamPtr->SignalMode <= ANA_SECAM_L))
        if (tuneParamPtr->FreqInHz < 300000000)
        {
          if ((tmpData - 5) > 0)
            regData += ((xtalSpurCfg[idx].xtalAmp_Rb + xtalSpurCfg[idx].xtalAmp_LinRb)-5);
        }
        else
        {
          regData += (xtalSpurCfg[idx].xtalAmp_Rb + xtalSpurCfg[idx].xtalAmp_LinRb);
        }

        status |= Ctrl_WriteRegister(tuneParamPtr->I2cSlaveAddr, XTAL_EXT_BIAS_REG, regData);

        break;
      }
    }
  }

#ifdef CUSTOMER_SPECIFIC_SETTING_1
  if ((tuneParamPtr->SignalMode <= ANA_SECAM_L) && (tuneParamPtr->TuneType == VIEW_MODE))
  {
    // Disable Fine tune for Analog mode channels
    fineTuneCfg.I2cSlaveAddr = tuneParamPtr->I2cSlaveAddr;
    fineTuneCfg.EnableFineTune = MXL_DISABLE;
    status |= MxL601_ConfigTunerEnableFineTune(&fineTuneCfg);

    regData = 0;
    status |= Ctrl_ReadRegister(tuneParamPtr->I2cSlaveAddr, FINE_TUNE_CTRL_REG_1, &regData);
    regData |= 0x20;
    status |= Ctrl_WriteRegister(tuneParamPtr->I2cSlaveAddr, FINE_TUNE_CTRL_REG_1, regData);

  }
#endif

#ifdef CUSTOMER_SPECIFIC_SETTING_2
  if ((tuneParamPtr->SignalMode <= ANA_SECAM_L) && (tuneParamPtr->TuneType == VIEW_MODE))
  {
    status |= Ctrl_WriteRegister(tuneParamPtr->I2cSlaveAddr, PAGE_CHANGE_REG, 1);

    status |= Ctrl_ReadRegister(tuneParamPtr->I2cSlaveAddr, DIG_ANA_GINJO_LT_REG, &regData);
    if (tuneParamPtr->FreqInHz >= APP_MODE_FREQ_HZ_THRESHOLD_1)
      regData |= 0x10; // Bit<4> = 1 
    else 
      regData &= 0xEF; // Bit<4> = 0 
    status |= Ctrl_WriteRegister(tuneParamPtr->I2cSlaveAddr, DIG_ANA_GINJO_LT_REG, regData);
    status |= Ctrl_WriteRegister(tuneParamPtr->I2cSlaveAddr, PAGE_CHANGE_REG, 0);

    if (tuneParamPtr->FreqInHz >= APP_MODE_FREQ_HZ_THRESHOLD_1)
      status |= Ctrl_WriteRegister(tuneParamPtr->I2cSlaveAddr, FINE_TUNE_INIT1_REG, 0x26);
    else 
      status |= Ctrl_WriteRegister(tuneParamPtr->I2cSlaveAddr, FINE_TUNE_INIT1_REG, 0x48);    
  }
#endif 
  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL601_ConfigSpurShiftAdjustment -
--|                                                MXL_TUNER_SPUR_SHIFT_ADJ_CFG
--|
--| AUTHOR        : Mahee
--|
--| DATE CREATED  : 11/22/2011
--|                 12/20/2011
--|
--| DESCRIPTION   : This API configures MxL601 to move spurs caused by digital clock
--|                 out of band by adjusting digital clock frequency. The clock
--|                 frequency  adjustment value should be from 205 & 227.
--|                 Apply sequencer settings after updating registers.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL601_ConfigSpurShiftAdjustment(PMXL_SPUR_SHIFT_ADJ_CFG_T spurShiftAdjPtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 regData = 0;

  MxL_DLL_DEBUG0(printf("MXL_TUNER_SPUR_SHIFT_ADJ_CFG, Clock freq adjustment value = %d\n",
                                            spurShiftAdjPtr->SpurShiftingClkAdjValue));

  /* Check for spur shift clock adjustment value.
     The value should be greater than 205 & less than 227 */
  if ((spurShiftAdjPtr->SpurShiftingClkAdjValue >= SPUR_SHIFT_CLOCK_ADJUST_MIN) &&
      (spurShiftAdjPtr->SpurShiftingClkAdjValue <= SPUR_SHIFT_CLOCK_ADJUST_MAX))
  {
    status |= Ctrl_ReadRegister(spurShiftAdjPtr->I2cSlaveAddr, 0xEA, &regData);
    regData |= 0x20;
    status |= Ctrl_WriteRegister(spurShiftAdjPtr->I2cSlaveAddr, 0xEA, regData);

    status |= Ctrl_WriteRegister(spurShiftAdjPtr->I2cSlaveAddr,
                                 0xEB,
                                 spurShiftAdjPtr->SpurShiftingClkAdjValue);

    status |= Ctrl_WriteRegister(spurShiftAdjPtr->I2cSlaveAddr, START_TUNE_REG, 0x00);
    status |= Ctrl_WriteRegister(spurShiftAdjPtr->I2cSlaveAddr, START_TUNE_REG, 0x01);

  }
  else status = MXL_FALSE;

  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL601_ConfigHlfrfSettings -
--|                                     MXL_TUNER_HLFRF_CFG
--|
--| AUTHOR        : Mahee
--|
--| DATE CREATED  : 12/28/2011
--|
--| DESCRIPTION   : This API configures register settings to improve hlfrf
--|                 performance.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL601_ConfigHlfrfSettings(PMXL_HLFRF_CFG_T hlfrfCfgPtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 regData0 = 0;
  UINT8 regData1 = 0;

  MxL_DLL_DEBUG0(printf("MXL_TUNER_HLFRF_CFG\n"));

  status |= Ctrl_WriteRegister(hlfrfCfgPtr->I2cSlaveAddr, PAGE_CHANGE_REG, 0x01);
  status |= Ctrl_ReadRegister(hlfrfCfgPtr->I2cSlaveAddr, DIG_ANA_GINJO_LT_REG, &regData0);

  if (hlfrfCfgPtr->Enable == MXL_ENABLE)
  {
    regData0 |= 0x10;
    regData1 = 0x48;
  }
  else
  {
    regData0 &= 0xEF;
    regData1 = 0x59;
  }

  status |= Ctrl_WriteRegister(hlfrfCfgPtr->I2cSlaveAddr, DIG_ANA_GINJO_LT_REG, regData0);
  status |= Ctrl_WriteRegister(hlfrfCfgPtr->I2cSlaveAddr, PAGE_CHANGE_REG, 0x00);

  status |= Ctrl_WriteRegister(hlfrfCfgPtr->I2cSlaveAddr, 0xA9, regData1);

  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL601_ConfigTunerAfc - 
--|                                     MXL_TUNER_AFC_CFG
--| 
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 08/17/2012
--|
--| DESCRIPTION   : This API configures Tuner AFC range. if range is 0, then AFC 
--|                 function will be turned off.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL601_ConfigTunerAfc(PMXL_TUNER_AFC_CFG_T afcCfgPtr)
{
  UINT32 u32FreqOffsetKHz, u32AfcRegWriteVal;
  UINT8  highByte = 0, lowByte = 0;
  UINT8 status = MXL_TRUE;
  
  MxL_DLL_DEBUG0("MXL_TUNER_HLFRF_CFG\n");

  u32FreqOffsetKHz = (UINT32)afcCfgPtr->AfcRangeInKHz; 
 	if (u32FreqOffsetKHz == MXL601_AFC_DISABLE)
	 {
	   // Disable AFC , program 0x13<2> to 1
    status = Ctrl_ReadRegister(afcCfgPtr->I2cSlaveAddr, FINE_TUNE_SET_REG, &lowByte);
	   lowByte |= 0x04;
	   status |= Ctrl_WriteRegister(afcCfgPtr->I2cSlaveAddr, FINE_TUNE_SET_REG, lowByte);
	 }
	 else
	 {
	   status = Ctrl_ReadRegister(afcCfgPtr->I2cSlaveAddr, FINE_TUNE_SET_REG, &lowByte);
	   if ((lowByte & 0x04) == 0x04)  // Bit<2> = 1
	   {
	     lowByte &= 0xFB;  // Bit<2> = 0, enable AFC
	     status |= Ctrl_WriteRegister(afcCfgPtr->I2cSlaveAddr, FINE_TUNE_SET_REG, lowByte);
	   }
	   u32AfcRegWriteVal = u32FreqOffsetKHz * 1000 / 824 ;
	   highByte = (u32AfcRegWriteVal >> 8 ) & 0x03;
	   lowByte =  (u32AfcRegWriteVal & 0xFF);
	   status |= Ctrl_WriteRegister(afcCfgPtr->I2cSlaveAddr, AFC_RANGE_SET_HIGH_REG, highByte);
	   status |= Ctrl_WriteRegister(afcCfgPtr->I2cSlaveAddr, AFC_RANGE_SET_LOW_REG, lowByte);
  }

  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL601_ConfigTunerBalunless - MXL_TUNER_BALUNLESS_CFG
--| 
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 08/17/2012
--|
--| DESCRIPTION   : This API compensates the unbalanced signal effect at low VHF
--|                 when tuner works at Balunless configuration.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL601_ConfigTunerBalunless(PMXL_TUNER_BALUNLESS_CFG_T balunlessCfgPtr)
{
  MXL_STATUS status = MXL_TRUE;
 
  MxL_DLL_DEBUG0("MXL_TUNER_BALUNLESS_CFG\n");

  if (balunlessCfgPtr->SignalMode < DIG_DVB_C)
  {
    status = Ctrl_WriteRegister(balunlessCfgPtr->I2cSlaveAddr, DFE_AGC_TOPMAXRF_REG, 0x1E);
  }

  return status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL601_GetTunerSignalType - MXL_TUNER_SIGNAL_TYPE_REQ
--|
--| AUTHOR        : Sunghoon Park
--|
--| DATE CREATED  : 6/24/2011
--|
--| DESCRIPTION   : This function returns signal type received.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL601_GetTunerSignalType(PMXL_SIGNAL_TYPE_T tuneSigTypePtr)
{
  MXL_STATUS status = MXL_TRUE;
  UINT8 regData = 0;

  status = Ctrl_ReadRegister(tuneSigTypePtr->I2cSlaveAddr, SIGNAL_TYPE_REG, &regData);

  // Signal type
  if ((regData & 0x10) == 0x10) tuneSigTypePtr->SignalMode = SIGNAL_TYPE_ANALOG;
  else tuneSigTypePtr->SignalMode = SIGNAL_TYPE_DIGITAL;

  return status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL601_GetTunerLockStatus - MXL_TUNER_LOCK_STATUS_REQ
--|
--| AUTHOR        : Dong Liu
--|                 Sunghoon Park
--|
--| DATE CREATED  : 6/21/2011
--|                 6/24/2011
--|
--| DESCRIPTION   : This function returns Tuner Lock status of MxL601 tuner.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL601_GetTunerLockStatus(PMXL_TUNER_LOCK_STATUS_T tunerLockStatusPtr)
{
  MXL_STATUS status = MXL_TRUE;
  UINT8 regData = 0;
  MXL_BOOL rfSynthStatus = MXL_UNLOCKED;
  MXL_BOOL refSynthStatus = MXL_UNLOCKED;

  MxL_DLL_DEBUG0(printf("MXL_TUNER_LOCK_STATUS_REQ \n"));

  status = Ctrl_ReadRegister(tunerLockStatusPtr->I2cSlaveAddr, RF_REF_STATUS_REG, &regData);

  if ((regData & 0x01) == 0x01) refSynthStatus = MXL_LOCKED;

  if ((regData & 0x02) == 0x02) rfSynthStatus = MXL_LOCKED;

  MxL_DLL_DEBUG0(printf(" RfSynthStatus = %d, RefSynthStatus = %d",
                                    (UINT8)rfSynthStatus,(UINT8)refSynthStatus));

  tunerLockStatusPtr->RfSynLock =  rfSynthStatus;
  tunerLockStatusPtr->RefSynLock = refSynthStatus;

  return status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL601_GetTunerAgcLockStatus - MXL_TUNER_AGC_LOCK_REQ
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 10/12/2011
--|
--| DESCRIPTION   : This function returns AGC Lock status of MxL601 tuner.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL601_GetTunerAgcLockStatus(PMXL_TUNER_AGC_LOCK_T agcLockStatusPtr)
{
  MXL_STATUS status = MXL_FALSE;
  UINT8 regData = 0;
  MXL_BOOL lockStatus = MXL_UNLOCKED;

  MxL_DLL_DEBUG0(printf("MXL_TUNER_AGC_LOCK_REQ \n"));

  status = Ctrl_ReadRegister(agcLockStatusPtr->I2cSlaveAddr, AGC_SAGCLOCK_STATUS_REG, &regData);

  // Bit<3>
  if ((regData & 0x08) == 0x08) lockStatus = MXL_LOCKED;

  MxL_DLL_DEBUG0(printf(" Agc lock = %d", (UINT8)lockStatus));

  agcLockStatusPtr->AgcLock =  lockStatus;

  return status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL601_GetTunerRxPower - MXL_TUNER_RX_PWR_REQ
--|
--| AUTHOR        : Dong Liu
--|                 Sunghoon Park
--|
--| DATE CREATED  : 06/18/2012
--|                 06/17/2011
--|
--| DESCRIPTION   : This function returns RF input power in 0.01dBm.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL601_GetTunerRxPower(PMXL_TUNER_RX_PWR_T rxPwrPtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 regData = 0;
  UINT16 tmpData = 0;

  MxL_DLL_DEBUG0(printf("MXL_TUNER_RX_PWR_REQ \n"));

  // RF input power low <7:0>
  status = Ctrl_ReadRegister(rxPwrPtr->I2cSlaveAddr, RFPIN_RB_LOW_REG, &regData);
  tmpData = regData;

  // RF input power high <1:0>
  status |= Ctrl_ReadRegister(rxPwrPtr->I2cSlaveAddr, RFPIN_RB_HIGH_REG, &regData);
  tmpData |= (regData & 0x03) << 8;

  rxPwrPtr->RxPwr = (tmpData & 0x01FF)*25;  //100 times dBm

  if (tmpData & 0x02) rxPwrPtr->RxPwr += 50;
  if (tmpData & 0x01) rxPwrPtr->RxPwr += 25;
  if (tmpData & 0x0200) rxPwrPtr->RxPwr -= 128*100;

  MxL_DLL_DEBUG0(printf(" Rx power = %d times 0.01dBm \n", rxPwrPtr->RxPwr));

  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL601_GetTunerAfcCorrection - MXL_TUNER_AFC_CORRECTION_REQ
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 04/20/2012
--|
--| DESCRIPTION   : This function returns AFC offset value, unit is kHz
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxL601_GetTunerAfcCorrection(PMXL_TUNER_AFC_CORRECTION_T afcCorrectionPtr)
{
  UINT32 tmpData = 0;
  UINT8 status = MXL_TRUE;
  UINT8 regData = 0;
  UINT8 regData2 = 0;
  UINT8 regData3 = 0;
  UINT8 afcLock = 0;

  MxL_DLL_DEBUG0(printf("MXL_TUNER_AFC_CORRECTION_REQ \n"));

  status |= Ctrl_ReadRegister(afcCorrectionPtr->I2cSlaveAddr, RFPIN_RB_HIGH_REG, &regData);
  afcLock = (regData & 0x10) >> 4;

  // AFC offset correction readback <7:0> correponding to bit<7:0>
  status |= Ctrl_ReadRegister(afcCorrectionPtr->I2cSlaveAddr, DFE_CTRL_ACCUM_LOW_REG, &regData);

  // AFC offset correction readback <15:8> correponding to bit<7:0>
  status |= Ctrl_ReadRegister(afcCorrectionPtr->I2cSlaveAddr, DFE_CTRL_ACCUM_MID_REG, &regData2);

  // AFC offset correction readback <17:16> correponding to bit<1:0>
  status |= Ctrl_ReadRegister(afcCorrectionPtr->I2cSlaveAddr, DFE_CTRL_ACCUM_HI_REG, &regData3);

  tmpData = regData3 & 0x03;
  tmpData = (tmpData << 8) + regData2;
  tmpData = (tmpData << 8) + regData;

  if ((afcLock == 0) && (tmpData == 0))
  {
    // MxL601 AFC could not find peak
    status = MXL_FALSE;
    MxL_DLL_DEBUG0(printf(" Can not find peak \n"));
  }
  else
  {
    // Check if return data is negative number
    if (tmpData & 0x020000)  // Bit<17> = 1
      afcCorrectionPtr->AfcOffsetKHz = ((tmpData - 262144) * 1000) >> 16;
    else
      afcCorrectionPtr->AfcOffsetKHz =  (tmpData * 1000) >> 16;

    MxL_DLL_DEBUG0(printf(" AFC correction = %d kHz \n", afcCorrectionPtr->AfcOffsetKHz));
  }

  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL601_SetTeletextSpurMitigationAlgo -
--|                                                 MXL_TUNER_TELETEXT_SPUR_CFG
--|
--| AUTHOR        : Mahendra Kondur
--|
--| DATE CREATED  : March 04, 2012
--|
--| DESCRIPTION   : This function will apply settings to reduce spurs caused
--|                 by teletext broadcast
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/
#ifdef ENABLE_TELETEXT_SPUR_FEATURE
static MXL_STATUS MxL601_SetTeletextSpurMitigation(PMXL_TELETEXT_SPUR_CFG_T teletextSpurCfgPtr)
{
  UINT8 numOfDCCalSamples = (UINT8)teletextSpurCfgPtr->numofDCCalSamples; // Number of DC Cal sample;
  REAL64 Sthreshold = teletextSpurCfgPtr->dcCalThreshold; // DC Cal threshold
  UINT16 dcCalSamplePeriod = (UINT16)teletextSpurCfgPtr->dcCalSamplesInterval; // 20 ms

  REAL64 maxSi = 0.0;
  REAL64 minSi = 0.0;

  REAL64 maxSq = 0.0;
  REAL64 minSq = 0.0;

  REAL64 Si = 0.0;
  REAL64 Sq = 0.0;

  REAL32 dcCal_i[MAX_DC_CAL_SAMPLES];
  REAL32 dcCal_q[MAX_DC_CAL_SAMPLES];

  REAL64 SiVariance = 0.0;
  REAL64 SqVariance = 0.0;

  UINT16 dcCalWordi = 0;
  UINT16 dcCalWordq = 0;

  UINT8 idx = 0;
  UINT8 regData = 0;
  UINT8 status = MXL_TRUE;

  MxL_DLL_DEBUG0(printf("MXL_TUNER_TELETEXT_SPUR_CFG \n"));

  if (dcCalSamplePeriod == 0) dcCalSamplePeriod = 20;
  if (numOfDCCalSamples == 0) numOfDCCalSamples = 50;
  if (Sthreshold == 0) Sthreshold = 0.3;
  if (teletextSpurCfgPtr->initialTimeDelay  == 0) teletextSpurCfgPtr->initialTimeDelay = 500;

  MxL_DLL_DEBUG0(printf("DC CAL Sample Interval = %d ms \n", dcCalSamplePeriod));
  MxL_DLL_DEBUG0(printf("DC Number of DC CAL Samples = %d \n", numOfDCCalSamples));
  MxL_DLL_DEBUG0(printf("DC CAL threshold = %lf ms \n", Sthreshold));

    // Program FDC BW = 20 Hz
  status |= Ctrl_WriteRegister(teletextSpurCfgPtr->I2cSlaveAddr, DFE_FDC_IIR0_1, 0x77);
  status |= Ctrl_WriteRegister(teletextSpurCfgPtr->I2cSlaveAddr, DFE_FDC_IIR2_3, 0x77);

  MxL_DLL_DEBUG0(printf("%d ms delay....", teletextSpurCfgPtr->initialTimeDelay));
  MxL_Sleep((UINT16)teletextSpurCfgPtr->initialTimeDelay);

  // Read DC CAL word
  for (idx = 0; idx < numOfDCCalSamples; idx++)
  {
    // Change Page to 0
    status = Ctrl_WriteRegister(teletextSpurCfgPtr->I2cSlaveAddr, 0x00, 0x01);

    // Read dfe_fdc_offset_i
    status |= Ctrl_ReadRegister(teletextSpurCfgPtr->I2cSlaveAddr, DFE_FDC_OFFSET_I_LSB, &regData);
    dcCalWordi = (regData & 0xFF);

    status |= Ctrl_ReadRegister(teletextSpurCfgPtr->I2cSlaveAddr, DFE_FDC_OFFSET_I_MSB, &regData);
    dcCalWordi |= ((regData & 0x7F) << 8);

    Si = MxL_GetTunerSignedBits(dcCalWordi, 1, 15, 4);

    dcCal_i[idx] = (REAL32)Si;

    if (idx == 0)
    {
      maxSi = minSi = Si;
    }
    else
    {
      if (Si > maxSi) maxSi = Si;
      else if (Si < minSi) minSi = Si;
    }

    // Read dfe_fdc_offset_q
    status |= Ctrl_ReadRegister(teletextSpurCfgPtr->I2cSlaveAddr, DFE_FDC_OFFSET_Q_LSB, &regData);
    dcCalWordq = (regData & 0xFF);

    status |= Ctrl_ReadRegister(teletextSpurCfgPtr->I2cSlaveAddr, DFE_FDC_OFFSET_Q_MSB, &regData);
    dcCalWordq |= ((regData & 0x7F) << 8);

    Sq = MxL_GetTunerSignedBits(dcCalWordq, 1, 15, 4);

    dcCal_q[idx] = (REAL32)Sq;

    if (idx == 0)
    {
      maxSq = minSq = Sq;
    }
    else
    {
      if (Sq > maxSq) maxSq = Sq;
      else if (Sq < minSq) minSq = Sq;
    }

    // Change Page to 1
    status |= Ctrl_WriteRegister(teletextSpurCfgPtr->I2cSlaveAddr, 0x00, 0x00);

    // wait for next sample interval
    MxL_DLL_DEBUG0(printf("%d ms delay....", dcCalSamplePeriod));
    MxL_Sleep(dcCalSamplePeriod);
  }

  MxL_DLL_DEBUG0(printf("Max Si = %lf \n", maxSi));
  MxL_DLL_DEBUG0(printf("Min Si = %lf \n", minSi));
  MxL_DLL_DEBUG0(printf("DELTA Si = %lf \n", (maxSi - minSi)));

  MxL_DLL_DEBUG0(printf("Max Sq = %lf \n", maxSq));
  MxL_DLL_DEBUG0(printf("Min Sq = %lf \n", minSq));
  MxL_DLL_DEBUG0(printf("DELTA Sq = %lf \n", (maxSq - minSq)));

  // Calculate Variance Si
  SiVariance = MxL_CalculateVariance(dcCal_i, numOfDCCalSamples);

  // Calculate Variance Sq
  SqVariance = MxL_CalculateVariance(dcCal_q, numOfDCCalSamples);

  MxL_DLL_DEBUG0(printf("Si Variance = %lf \n", SiVariance));
  MxL_DLL_DEBUG0(printf("Sq Variance = %lf \n", SqVariance));


  if (((maxSi - minSi) >= Sthreshold) || ((maxSq - minSq) >= Sthreshold))
  {
    status |= MXL_SUCCESS;
  }
  else
  {
    // Program FDC BW = 251 Hz
    status |= Ctrl_WriteRegister(teletextSpurCfgPtr->I2cSlaveAddr, DFE_FDC_IIR0_1, 0x56);
    status |= Ctrl_WriteRegister(teletextSpurCfgPtr->I2cSlaveAddr, DFE_FDC_IIR2_3, 0x44);
  }

  return (MXL_STATUS)status;
}
#endif 

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxLWare601_API_ConfigDevice
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 02/12/2011
--|
--| DESCRIPTION   : The general device configuration shall be handled
--|                 through this API.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxLWare601_API_ConfigDevice(MXL_COMMAND_T *ParamPtr)
{
  MXL_STATUS status = MXL_TRUE;
  MXL_CMD_TYPE_E cmdType;

  if (ParamPtr == NULL) return MXL_FALSE;

  cmdType = ParamPtr->commandId;

  MxL_DLL_DEBUG0(printf("MxLWare601_API_ConfigDevice : cmdType = %d\n", cmdType));

  switch (cmdType)
  {
    case MXL_DEV_SOFT_RESET_CFG:
      status = MxL601_ConfigDevReset(&ParamPtr->MxLIf.cmdResetCfg);
      break;

    case MXL_DEV_OVERWRITE_DEFAULT_CFG:
      status = MxL601_ConfigDevOverwriteDefault(&ParamPtr->MxLIf.cmdOverwriteDefault);
      break;

    case MXL_DEV_XTAL_SET_CFG:
      status = MxL601_ConfigDevXtalSet(&ParamPtr->MxLIf.cmdXtalCfg);
      break;

    case MXL_DEV_POWER_MODE_CFG:
      status = MxL601_ConfigDevPowerMode(&ParamPtr->MxLIf.cmdPwrModeCfg);
      break;

    case MXL_DEV_IF_OUT_CFG:
      status = MxL601_ConfigDevIfOutSet(&ParamPtr->MxLIf.cmdIfOutCfg);
      break;

    case MXL_DEV_GPO_CFG:
      status = MxL601_ConfigDevGPO(&ParamPtr->MxLIf.cmdGpoCfg);
      break;

    default:
      status = MXL_FALSE;
      break;
  }

  return status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxLWare601_API_GetDeviceStatus
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 01/30/2011
--|
--| DESCRIPTION   : The general device inquiries shall be handled
--|                 through this API
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxLWare601_API_GetDeviceStatus(MXL_COMMAND_T *ParamPtr)
{
  MXL_STATUS status = MXL_TRUE;
  MXL_CMD_TYPE_E cmdType;

  if (ParamPtr == NULL) return MXL_FALSE;

  cmdType = ParamPtr->commandId;

  MxL_DLL_DEBUG0(printf("MxLWare601_API_GetDeviceStatus : cmdType = %d", cmdType));

  switch (cmdType)
  {
    case MXL_DEV_ID_VERSION_REQ:
      status = MxL601_GetDeviceInfo(&ParamPtr->MxLIf.cmdDevInfoReq);
      break;

    case MXL_DEV_GPO_STATE_REQ:
      status = MxL601_GetDeviceGpoState(&ParamPtr->MxLIf.cmdGpoReq);
      break;

    case MXL_DEV_PLL_STATE_REQ:
      status = MxL601_GetDevicePllState(&ParamPtr->MxLIf.cmdPllReq);
      break;

    default:
      status = MXL_FALSE;
      break;
  }

  return status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxLWare601_API_ConfigTuner
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 02/12/2011
--|                 12/28/2011
--|                 03/14/2013
--|
--| DESCRIPTION   : The tuner block specific configuration shall be handled
--|                 through this API
--|                 New API added - MXL_TUNER_HALF_RF_OPTIMIZATION_CFG
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxLWare601_API_ConfigTuner(MXL_COMMAND_T *ParamPtr)
{
  MXL_STATUS status = MXL_TRUE;
  MXL_CMD_TYPE_E cmdType;

  if (ParamPtr == NULL) return MXL_FALSE;

  cmdType = ParamPtr->commandId;

  MxL_DLL_DEBUG0(printf("MxLWare601_API_ConfigTuner : cmdType =%d\n", cmdType));

  switch (cmdType)
  {
    case MXL_TUNER_POWER_UP_CFG:
      status = MxL601_ConfigTunerPowerUp(&ParamPtr->MxLIf.cmdTunerPoweUpCfg);
      break;

    case MXL_TUNER_START_TUNE_CFG:
      status = MxL601_ConfigTunerSequenceSet(&ParamPtr->MxLIf.cmdStartTuneCfg);
      break;

    case MXL_TUNER_MODE_CFG:
      status = MxL601_ConfigTunerApplicationModeSet(&ParamPtr->MxLIf.cmdModeCfg);
      break;

    case MXL_TUNER_AGC_CFG:
      status = MxL601_ConfigTunerAgcSet(&ParamPtr->MxLIf.cmdAgcSetCfg);
      break;

    case MXL_TUNER_FINE_TUNE_CFG:
      status = MxL601_ConfigTunerFineTune(&ParamPtr->MxLIf.cmdFineTuneCfg);
      break;

    case MXL_TUNER_ENABLE_FINE_TUNE_CFG:
      status = MxL601_ConfigTunerEnableFineTune(&ParamPtr->MxLIf.cmdEnableFineTuneCfg);
      break;

    case MXL_TUNER_CHAN_TUNE_CFG:
      status = MxL601_ConfigTunerChanTune(&ParamPtr->MxLIf.cmdChanTuneCfg);
      break;

    case MXL_TUNER_SPUR_SHIFT_ADJ_CFG:
      status = MxL601_ConfigSpurShiftAdjustment(&ParamPtr->MxLIf.cmdSuprShiftAdjCfg);
      break;

    case MXL_TUNER_HLFRF_CFG:
      status = MxL601_ConfigHlfrfSettings(&ParamPtr->MxLIf.cmdHlfrfCfg);
      break;

    case MXL_TUNER_AFC_CFG:
      status = MxL601_ConfigTunerAfc(&ParamPtr->MxLIf.cmdAfcCfg);
      break;

#ifdef ENABLE_TELETEXT_SPUR_FEATURE
    case MXL_TUNER_TELETEXT_SPUR_CFG:
      status = MxL601_SetTeletextSpurMitigation(&ParamPtr->MxLIf.cmdTeletextSpurCfg);
      break;
#endif 

    case MXL_TUNER_BALUNLESS_CFG:
      status = MxL601_ConfigTunerBalunless(&ParamPtr->MxLIf.cmdBalunlessCfg);
      break;

    default:
      status = MXL_FALSE;
      break;
  }
  return status;
}

/*--------------------------------------------------------------------------------
--| FUNCTION NAME : MxLWare601_API_GetTunerStatus
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 02/12/2011
--|
--| DESCRIPTION   : The tuner specific inquiries shall be handled through this API
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|-----------------------------------------------------------------------------*/

MXL_STATUS MxLWare601_API_GetTunerStatus(MXL_COMMAND_T *ParamPtr)
{
  MXL_STATUS status;
  MXL_CMD_TYPE_E cmdType;

  if (ParamPtr == NULL) return MXL_FALSE;

  cmdType = ParamPtr->commandId;

  MxL_DLL_DEBUG0(printf("MxLWare601_API_GetTunerStatus : cmdType = %d", cmdType));

  switch (cmdType)
  {
    case MXL_TUNER_SIGNAL_TYPE_REQ:
      status = MxL601_GetTunerSignalType(&ParamPtr->MxLIf.cmdTunerSignalTypeReq);
      break;

    case MXL_TUNER_LOCK_STATUS_REQ:
      status = MxL601_GetTunerLockStatus(&ParamPtr->MxLIf.cmdTunerLockReq);
      break;

    case MXL_TUNER_AGC_LOCK_REQ:
      status = MxL601_GetTunerAgcLockStatus(&ParamPtr->MxLIf.cmdTunerAgcLockReq);
      break;

    case MXL_TUNER_RX_PWR_REQ:
      status = MxL601_GetTunerRxPower(&ParamPtr->MxLIf.cmdTunerPwrReq);
      break;

    case MXL_TUNER_AFC_CORRECTION_REQ:
      status = MxL601_GetTunerAfcCorrection(&ParamPtr->MxLIf.cmdTunerAfcCorectionReq);
      break;

    default:
      status = MXL_FALSE;
      break;
  }

  return status;
}

