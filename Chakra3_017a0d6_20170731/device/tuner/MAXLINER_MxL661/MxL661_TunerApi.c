/*******************************************************************************
 *
 * FILE NAME          : MxL661_TunerApi.cpp
 *
 * AUTHOR             : Sunghoon Park
 *                      Dong Liu
 *                      Joy Zhang
 *
 *
 * DATE CREATED       : 07/12/2011
 *                      05/23/2013
 *                      09/10/2013
 *
 * DESCRIPTION        : This file contains MxL661 driver APIs
 *
 *
 *******************************************************************************
 *                Copyright (c) 2013, MaxLinear, Inc.
 ******************************************************************************/

#include <math.h>
#include "MxL661_TunerApi.h"
#include "MxL_Debug.h"

#define  BASIC_MXL661_I2C_ADDR      0xC0

/* MxLWare Driver version for MxL661 */
const UINT8 MxLWare661DrvVersion[] = {4, 1, 2, 3};

// Candidate version number, 0 means for release version
const UINT8 MxL661BuildNumber = 0;

static MXL661_XTAL_SPUR_CFG_T MxL661xtalSpurCfg[MAX_MXL661_DEVICES] = {{BASIC_MXL661_I2C_ADDR, 0, 0, 99},
                                         {BASIC_MXL661_I2C_ADDR+2, 0, 0, 99},
                                         {BASIC_MXL661_I2C_ADDR+4, 0, 0, 99},
                                         {BASIC_MXL661_I2C_ADDR+6, 0, 0, 99},};

static MXL661_IF_FCW_CFG_T MxL661ifFcwCfg[MAX_MXL661_DEVICES] = {{BASIC_MXL661_I2C_ADDR, 0, 0, 0, 0},
                                   {BASIC_MXL661_I2C_ADDR+2, 0, 0, 0, 0},
                                   {BASIC_MXL661_I2C_ADDR+4, 0, 0, 0, 0},
                                   {BASIC_MXL661_I2C_ADDR+6, 0, 0, 0, 0},};

static MXL661_IF_FCW_LUT_T MxL661ifFcwOverwriteTable[17] = {{0x0092, 0x0083},
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

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_ConfigDevReset - MXL661_DEV_SOFT_RESET_CFG
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

static MXL_STATUS MxL661_ConfigDevReset(PMXL661_RESET_CFG_T resetCfg)
{
  UINT8 status = MXL_TRUE;
  UINT8 idx = 0;

  MxL_DLL_DEBUG0("MXL661_DEV_SOFT_RESET_CFG \n");

  // Write 0xFF with 0 to reset tuner
  status = MxLWare661_OEM_WriteRegister(resetCfg->I2cSlaveAddr, AIC_RESET_REG, 0x00);

  for (idx = 0; idx < MAX_MXL661_DEVICES; idx++)
  {
    if (MxL661xtalSpurCfg[idx].i2cAddr == resetCfg->I2cSlaveAddr) break;
  }

  if (idx == MAX_MXL661_DEVICES)
  {
    /* This Device was never registered */
    /* Find empty slot */
    for (idx = 0; idx < MAX_MXL661_DEVICES; idx++)
    {
      if (MxL661xtalSpurCfg[idx].i2cAddr == 0) break;
    }

    /* No empty slot */
    if (idx == MAX_MXL661_DEVICES)
    {
      return MXL_FALSE;
    }
  }

  MxL661xtalSpurCfg[idx].i2cAddr = resetCfg->I2cSlaveAddr;
  MxL661xtalSpurCfg[idx].appMode = MXL661_SIGNAL_NA;
  MxL661xtalSpurCfg[idx].xtalAmp_Rb = 0;
  MxL661xtalSpurCfg[idx].xtalAmp_LinRb = 0;

  MxL661ifFcwCfg[idx].i2cAddr = resetCfg->I2cSlaveAddr;
  MxL661ifFcwCfg[idx].if_sel = MXL661_IF_FREQ_NA;

  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_ConfigDevOverwriteDefault -
--|                                               MXL661_DEV_OVERWRITE_DEFAULT_CFG
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

static MXL_STATUS MxL661_ConfigDevOverwriteDefault(PMXL661_OVERWRITE_DEFAULT_CFG_T overDefaultPtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 readData = 0;

  MxL_DLL_DEBUG0("MXL661_DEV_OVERWRITE_DEFAULT_CFG \n");
  status |= MxL661_Ctrl_ProgramRegisters(overDefaultPtr->I2cSlaveAddr, MxL661_OverwriteDefaults);

  status |= MxLWare661_OEM_WriteRegister(overDefaultPtr->I2cSlaveAddr, 0x00, 0x01);
  status |= MxLWare661_OEM_ReadRegister(overDefaultPtr->I2cSlaveAddr, 0x31, &readData);
  readData &= 0x2F;
  readData |= 0xD0;
  status |= MxLWare661_OEM_WriteRegister(overDefaultPtr->I2cSlaveAddr, 0x31, readData);
  status |= MxLWare661_OEM_WriteRegister(overDefaultPtr->I2cSlaveAddr, 0x00, 0x00);


  /* If Single supply 3.3v is used */
  if (MXL_ENABLE == overDefaultPtr->SingleSupply_3_3V)
    status |= MxLWare661_OEM_WriteRegister(overDefaultPtr->I2cSlaveAddr, MAIN_REG_AMP, 0x04);

  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_ConfigDevPowerMode - MXL661_DEV_POWER_MODE_CFG
--|
--| AUTHOR        : Dong Liu
--|                 Sunghoon Park
--|
--| DATE CREATED  : 06/21/2011
--|                 06/15/2011
--|
--| DESCRIPTION   : This API configures MxL661 power mode
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

static MXL_STATUS MxL661_ConfigDevPowerMode(PMXL661_PWR_MODE_CFG_T pwrModePtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 i2cAddr;

  MxL_DLL_DEBUG0("MXL661_DEV_POWER_MODE_CFG \n");
  i2cAddr = pwrModePtr->I2cSlaveAddr;

  switch(pwrModePtr->PowerMode)
  {
    case MXL661_PWR_MODE_SLEEP:
      break;

    case MXL661_PWR_MODE_ACTIVE:
      status |= MxLWare661_OEM_WriteRegister(i2cAddr, TUNER_ENABLE_REG, MXL_ENABLE);
      status |= MxLWare661_OEM_WriteRegister(i2cAddr, START_TUNE_REG, MXL_ENABLE);
      break;

    case MXL661_PWR_MODE_STANDBY:
      status |= MxLWare661_OEM_WriteRegister(i2cAddr, START_TUNE_REG, MXL_DISABLE);
      status |= MxLWare661_OEM_WriteRegister(i2cAddr, TUNER_ENABLE_REG, MXL_DISABLE);
      break;

    default:
      return MXL_FALSE;
  }

  return(MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_ConfigDevXtalSet - MXL661_DEV_XTAL_SET_CFG
--|
--| AUTHOR        : Sunghoon Park
--|                 Dong Liu
--|
--| DATE CREATED  : 11/13/2011 (MK) - Update Reg address for V2
--|                 08/29/2012
--|
--| DESCRIPTION   : This API is used to configure XTAL settings of MxL661 tuner
--|                 device. XTAL settings include frequency, capacitance &
--|                 clock out
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

static MXL_STATUS MxL661_ConfigDevXtalSet(PMXL661_XTAL_SET_CFG_T xtalSetPtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 control = 0;

  MxL_DLL_DEBUG0("MXL661_DEV_XTAL_SET_CFG \n");

  // XTAL freq and cap setting, Freq set is located at bit<5>, cap bit<4:0>
  control = (UINT8)((xtalSetPtr->XtalFreqSel << 5) | (xtalSetPtr->XtalCap & 0x1F));
  control |= (xtalSetPtr->ClkOutEnable << 7);
  status |= MxLWare661_OEM_WriteRegister(xtalSetPtr->I2cSlaveAddr, XTAL_CAP_CTRL_REG, control);

  // XTAL frequency div 4 setting <1> and  XTAL clock out enable <0>
  // XTAL sharing mode in slave
  control = (0x01 & (UINT8)xtalSetPtr->ClkOutDiv);
  if (xtalSetPtr->XtalSharingMode == MXL_ENABLE)
  {
    control |= 0x40;
    status |= MxLWare661_OEM_WriteRegister(xtalSetPtr->I2cSlaveAddr, XTAL_ENABLE_DIV_REG, control);
    status |= MxLWare661_OEM_WriteRegister(xtalSetPtr->I2cSlaveAddr, XTAL_EXT_BIAS_REG, 0x80);
  }
  else
  {
    control &= 0x01;
    status |= MxLWare661_OEM_WriteRegister(xtalSetPtr->I2cSlaveAddr, XTAL_ENABLE_DIV_REG, control);
    status |= MxLWare661_OEM_WriteRegister(xtalSetPtr->I2cSlaveAddr, XTAL_EXT_BIAS_REG, 0x0A);
  }

  // Main regulator re-program
  if (MXL_ENABLE == xtalSetPtr->SingleSupply_3_3V)
    status |= MxLWare661_OEM_WriteRegister(xtalSetPtr->I2cSlaveAddr, MAIN_REG_AMP, 0x14);

  return(MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_ConfigDevIfOutSet - MXL661_DEV_IF_OUT_CFG
--|
--| AUTHOR        : Sunghoon Park
--|                 Dong Liu
--|
--| DATE CREATED  : 06/15/2011
--|                 09/22/2011
--|
--| DESCRIPTION   : This function is used to configure IF out settings of MxL661
--|                 tuner device.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

static MXL_STATUS MxL661_ConfigDevIfOutSet(PMXL661_IF_OUT_CFG_T ifOutPtr)
{
  UINT16 ifFcw;
  UINT8 status = MXL_TRUE;
  UINT8 readData = 0;
  UINT8 control = 0;
  UINT8 idx = 0;

  MxL_DLL_DEBUG0("MXL661_DEV_IF_OUT_CFG: Manual set = %d \n", ifOutPtr->ManualFreqSet);

  for (idx = 0; idx < MAX_MXL661_DEVICES; idx++)
  {
    if (MxL661ifFcwCfg[idx].i2cAddr == ifOutPtr->I2cSlaveAddr) break;
  }

  if (idx >= 4) return (MXL_STATUS)status;

  // Read back register for manual IF Out
  status |= MxLWare661_OEM_ReadRegister(ifOutPtr->I2cSlaveAddr, IF_FREQ_SEL_REG, &readData);

  if (ifOutPtr->ManualFreqSet == MXL_ENABLE)
  {

    MxL661ifFcwCfg[idx].if_fcw_byp = 1;
    MxL661ifFcwCfg[idx].manualIFOutFreqInKHz = ifOutPtr->ManualIFOutFreqInKHz;

    // IF out manual setting : bit<5>
    readData |= 0x20;
    status |= MxLWare661_OEM_WriteRegister(ifOutPtr->I2cSlaveAddr, IF_FREQ_SEL_REG, readData);

    MxL_DLL_DEBUG0("Manual Freq set = %d \n", ifOutPtr->ManualIFOutFreqInKHz);

    // Manual IF freq set
    ifFcw = (UINT16)(ifOutPtr->ManualIFOutFreqInKHz * 8192 / 216000);
    control = (ifFcw & 0xFF); // Get low 8 bit
    status |= MxLWare661_OEM_WriteRegister(ifOutPtr->I2cSlaveAddr, IF_FCW_LOW_REG, control);

    control = ((ifFcw >> 8) & 0x0F); // Get high 4 bit
    status |= MxLWare661_OEM_WriteRegister(ifOutPtr->I2cSlaveAddr, IF_FCW_HIGH_REG, control);
  }
  else
  {
    MxL661ifFcwCfg[idx].if_fcw_byp = 0;
    MxL661ifFcwCfg[idx].if_sel = ifOutPtr->IFOutFreq;

    // bit<5> = 0, use IF frequency from IF frequency table
    readData &= 0xC0;

    // IF Freq <4:0>
    readData |= ifOutPtr->IFOutFreq;
    status |= MxLWare661_OEM_WriteRegister(ifOutPtr->I2cSlaveAddr, IF_FREQ_SEL_REG, readData);
  }

  // Set spectrum invert, gain level and IF path
  // Spectrum invert indication is bit<7:6>
  if (MXL_ENABLE == ifOutPtr->IFInversion)
  {
    MxL661ifFcwCfg[idx].if_invert = 1;
    control = 0x3 << 6;
  }
  else
  {
    MxL661ifFcwCfg[idx].if_invert = 0;
  }

  // Path selection is bit<5:4>
  control += ((ifOutPtr->PathSel & 0x03) << 4);

  // Gain level is bit<3:0>
  control += (ifOutPtr->GainLevel & 0x0F);
  status |= MxLWare661_OEM_WriteRegister(ifOutPtr->I2cSlaveAddr, IF_PATH_GAIN_REG, control);

  return(MXL_STATUS) status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_ConfigDevGPO - MXL661_DEV_GPO_CFG
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 3/24/2011
--|
--| DESCRIPTION   : This API configures GPOs of MxL661 tuner device.
--|                 (General Purpose Output Port) of the MxL661.
--|                 There are 3 GPOs in MxL661
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

static MXL_STATUS  MxL661_ConfigDevGPO(PMXL661_GPO_CFG_T gpoParamPtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 regData = 0;

  MxL_DLL_DEBUG0("MXL661_DEV_GPO_CFG \n");

  status |= MxLWare661_OEM_ReadRegister(gpoParamPtr->I2cSlaveAddr, GPO_SETTING_REG, &regData);

  switch (gpoParamPtr->GPOId)
  {
    case MXL661_GPO1:
      if (MXL661_PORT_AUTO_CTRL == gpoParamPtr->GPOState)
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

    case MXL661_GPO2:
      if (MXL661_PORT_AUTO_CTRL == gpoParamPtr->GPOState)
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

    case MXL661_GPO3:
      if (MXL661_PORT_AUTO_CTRL == gpoParamPtr->GPOState)
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
    status |= MxLWare661_OEM_WriteRegister(gpoParamPtr->I2cSlaveAddr, GPO_SETTING_REG, regData);

  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_GetDeviceInfo - MXL661_DEV_ID_VERSION_REQ
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 6/21/2011
--|
--| DESCRIPTION   : This function is used to get MxL661 version information.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

static MXL_STATUS MxL661_GetDeviceInfo(PMXL661_DEV_INFO_T DevInfoPtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 readBack = 0;
  UINT8 i2cAddr = 0;
  UINT8 k = 0;

  MxL_DLL_DEBUG0("MXL661_DEV_ID_VERSION_REQ \n");

  i2cAddr = DevInfoPtr->I2cSlaveAddr;

  status |= MxLWare661_OEM_ReadRegister(i2cAddr, CHIP_ID_REQ_REG, &readBack);
  DevInfoPtr->ChipId = (readBack & 0xFF);

  status |= MxLWare661_OEM_ReadRegister(i2cAddr, CHIP_VERSION_REQ_REG, &readBack);
  DevInfoPtr->ChipVersion = (readBack & 0xFF);

  MxL_DLL_DEBUG0("Chip ID = 0x%d, Version = 0x%d \n",
                                    DevInfoPtr->ChipId, DevInfoPtr->ChipVersion);

  // Get MxLWare version infromation
  for (k = 0; k < MXL661_VERSION_SIZE; k++)
    DevInfoPtr->MxLWareVer[k] = MxLWare661DrvVersion[k];

  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_GetDeviceGpoState - MXL661_DEV_GPO_STATE_REQ
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 3/24/2011
--|
--| DESCRIPTION   : This API is used to get GPO's status information from
--|                 MxL661 tuner device
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

static MXL_STATUS  MxL661_GetDeviceGpoState(PMXL661_GPO_INFO_T gpoPtr)
{
  MXL_STATUS status = MXL_TRUE;
  UINT8 regData = 0;

  MxL_DLL_DEBUG0("MXL661_DEV_GPO_STATE_REQ \n");

  status = MxLWare661_OEM_ReadRegister(gpoPtr->I2cSlaveAddr, GPO_SETTING_REG, &regData);

  // GPO1 bit<1:0>
  if ((regData & 0x01) == 0) gpoPtr->GPO1 = MXL661_PORT_AUTO_CTRL;
  else gpoPtr->GPO1 = (MXL661_GPO_STATE_E)((regData & 0x02) >> 1);

  // GPO2 bit<3:2>
  if ((regData & 0x04) == 0) gpoPtr->GPO2 = MXL661_PORT_AUTO_CTRL;
  else gpoPtr->GPO2 = (MXL661_GPO_STATE_E)((regData & 0x08) >> 3);

  // GPO3 bit<5:4>
  if ((regData & 0x10) == 0) gpoPtr->GPO3 = MXL661_PORT_AUTO_CTRL;
  else gpoPtr->GPO3 = (MXL661_GPO_STATE_E)((regData & 0x20) >> 5);

  return status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_GetDevicePllState - MXL661_DEV_PLL_STATE_REQ
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

static MXL_STATUS  MxL661_GetDevicePllState(PMXL661_PLL_INFO_T pllPtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 condition[3] = {0};
  UINT8 regAddr[7] = {0x2B, 0x30, 0x32, 0x34, 0x2F, 0x31, 0x33};
  UINT8 k, regData[7] = {0};

  MxL_DLL_DEBUG0("MXL661_DEV_PLL_STATE_REQ \n");
  pllPtr->PllState = MXL661_PLL_STATE_NA;

  for (k = 0; k < 7; k++)
  {
    // inquire PLL circuitry status and RSSI read back registers
    status |= MxLWare661_OEM_ReadRegister(pllPtr->I2cSlaveAddr, regAddr[k], &regData[k]);
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
      pllPtr->PllState = MXL661_PLL_STATE_WRONG;
    else
      pllPtr->PllState = MXL661_PLL_STATE_NORMAL;
  }

  MxL_DLL_DEBUG0("Tuner PLL state = %d (0:Normal, 1:Wrong) \n", pllPtr->PllState);
  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_ConfigTunerEnableState - MXL661_TUNER_POWER_UP_CFG
--|
--| AUTHOR        : Dong Liu
--|                 Sunghoon Park
--|
--| DATE CREATED  : 1/27/2011
--|                 6/22/2011
--|
--| DESCRIPTION   : This function is used to power up/down MxL661 tuner module
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

static MXL_STATUS MxL661_ConfigTunerPowerUp(PMXL661_POWER_UP_CFG_T topMasterCfgPtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 regData = 0;

  MxL_DLL_DEBUG0("MXL661_TUNER_POWER_UP_CFG, ENABLE = %d \n", topMasterCfgPtr->Enable);

  // Power up tuner <0> = 1 for enable, 0 for disable
  if (MXL_ENABLE == topMasterCfgPtr->Enable) regData |= 0x01;

  status = MxLWare661_OEM_WriteRegister(topMasterCfgPtr->I2cSlaveAddr, TUNER_ENABLE_REG, regData);

  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_ConfigTunerSequenceSet - MXL661_TUNER_START_TUNE_CFG
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

static MXL_STATUS MxL661_ConfigTunerSequenceSet(PMXL661_START_TUNE_CFG_T sequnCfgPtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 regData = 0;
  UINT8 idx = 0;
  UINT8 regData0 = 0;

  MxL_DLL_DEBUG0("MXL661_TUNER_START_TUNE_CFG, SEQUENCE SET = %d \n",
                                                      sequnCfgPtr->StartTune);

  status |= MxLWare661_OEM_WriteRegister(sequnCfgPtr->I2cSlaveAddr, START_TUNE_REG, 0x00);

  if (sequnCfgPtr->StartTune == MXL_ENABLE)
  {

    for (idx = 0; idx < MAX_MXL661_DEVICES; idx++)
    {
      if (MxL661xtalSpurCfg[idx].i2cAddr == sequnCfgPtr->I2cSlaveAddr)
        break;
    }

    if (idx >= MAX_MXL661_DEVICES) //It has no device.
    {
      return MXL_FALSE;
    }

    // Set DIG_ANA_XTAL_CLK_EN_BYPS = 1 before start tune
    status |= MxLWare661_OEM_ReadRegister(sequnCfgPtr->I2cSlaveAddr, 0x6E, &regData);
    status |= MxLWare661_OEM_WriteRegister(sequnCfgPtr->I2cSlaveAddr, 0x6E, (regData | 0x80));

    status |= MxLWare661_OEM_ReadRegister(sequnCfgPtr->I2cSlaveAddr, 0x14, &regData);
    status |= MxLWare661_OEM_WriteRegister(sequnCfgPtr->I2cSlaveAddr, 0x14, (regData & 0xDF));

    // Bit <0> 1 : start , 0 : abort calibrations
    status |= MxLWare661_OEM_WriteRegister(sequnCfgPtr->I2cSlaveAddr, START_TUNE_REG, 0x01);

    MxLWare661_OEM_Sleep(10);

    // Resume DIG_ANA_XTAL_CLK_EN_BYPS = 0 after start tune
    status |= MxLWare661_OEM_ReadRegister(sequnCfgPtr->I2cSlaveAddr, 0x6E, &regData0);
    status |= MxLWare661_OEM_WriteRegister(sequnCfgPtr->I2cSlaveAddr, 0x6E, (regData0 & 0x7F));

#ifdef MXL661_CUSTOMER_SPECIFIC_SETTING_3

    status |= MxLWare661_OEM_WriteRegister(sequnCfgPtr->I2cSlaveAddr, 0x14, (regData | 0x20));

    status |= MxLWare661_OEM_ReadRegister(sequnCfgPtr->I2cSlaveAddr, 0x13, &regData);

     // Check if signal type is Analog
    if (MxL661xtalSpurCfg[idx].appMode == MXL661_ANA_NTSC_MODE)
    {
      // Apply N+1 blocker settings
      status |= MxLWare661_OEM_WriteRegister(sequnCfgPtr->I2cSlaveAddr, DFE_FINETUNE_STEP_REG, 0x83);
    }
    else
    {
      // Undo N+1 blocker settings if app mode is not NTSC
      status |= MxLWare661_OEM_WriteRegister(sequnCfgPtr->I2cSlaveAddr, DFE_FINETUNE_STEP_REG, 0x80);
    }
    regData &= 0xFC; // Set Bit<1:0> = 00
    status |= MxLWare661_OEM_WriteRegister(sequnCfgPtr->I2cSlaveAddr, 0x13, regData);
    regData |= 0x01; // Set Bit<1:0> = 01
    status |= MxLWare661_OEM_WriteRegister(sequnCfgPtr->I2cSlaveAddr, 0x13, regData);
#endif
  }

  return(MXL_STATUS) status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_ConfigTunerAtvHpfLpf - MXL661_TUNER_HPF_LPF_CFG
--|
--| AUTHOR        : Joy Zhang
--|
--| DATE CREATED  : 09/09/2013
--|
--| DESCRIPTION   : This API implement the algorithm for HPF and LPF on/off for ATV.
--|
--| RETURN VALUE  : MXL_TRUE, MXL_FALSE or MXL_NOT_SUPPORTED
--|
--|---------------------------------------------------------------------------*/

static MXL_STATUS MxL661_ConfigTunerAtvHpfLpf(PMXL661_TUNER_HPF_LPF_CFG_T atvTunerHpfLpfCfgPtr)
{
  SINT32 dfeRSSIOnePercentdB;
  SINT32 RFStrOnePercentdB;
  UINT16 dfeAgcDuCalRef;
  UINT16 dfeAgcDuCal;
  UINT8  status = MXL_TRUE;
  UINT8  readData=0;//fix coverity 90931
  UINT8  waitTimeCnt = 0;

  MxL_DLL_DEBUG0("MXL661_TUNER_HPF_LPF_CFG, signal type = %d, Freq = %d \n", atvTunerHpfLpfCfgPtr->SignalMode, atvTunerHpfLpfCfgPtr->FreqInHz);

  if (atvTunerHpfLpfCfgPtr->SignalMode >= MXL661_DIG_DVB_C) return (MXL_STATUS)status;

  status = MxLWare661_OEM_ReadRegister(atvTunerHpfLpfCfgPtr->I2cSlaveAddr, CHIP_VERSION_REQ_REG, &readData);
  if(readData != 0x4)
  {
    MxL_DLL_DEBUG0("This version chip doesn't support HPF and LPF config \n");
    return (MXL_STATUS)status;
  }

  MxLWare661_OEM_Sleep(WAIT_TIME_FOR_RSSI_MS);

  status = MxL661_GetRSSI(atvTunerHpfLpfCfgPtr->I2cSlaveAddr, &dfeRSSIOnePercentdB);  // Get RSSI
    if(status != MXL_TRUE) return (MXL_STATUS)status;

  MxL_DLL_DEBUG0("dfeRSSI =  %d (0.01dB), RSSI_TH = %d (0.01dB), if dfeRSSI is greater than RSSI_THRESHOLD continue... \n", dfeRSSIOnePercentdB, RSSI_THRESHOLD);
  if(dfeRSSIOnePercentdB >= RSSI_THRESHOLD) // (-55dBm), RSSI_THRESHOLD is -38.
  {
    status |= MxL661_GetRFStrenth(atvTunerHpfLpfCfgPtr->I2cSlaveAddr, &RFStrOnePercentdB);
    status |= MxL661_GetRSSI(atvTunerHpfLpfCfgPtr->I2cSlaveAddr, &dfeRSSIOnePercentdB); if(status != MXL_TRUE) return (MXL_STATUS)status;
    if((RFStrOnePercentdB - RF_RSSI_OFFSET) < (dfeRSSIOnePercentdB - DFE_RSSI_OFFSET)) {
      MxL_DLL_DEBUG0("Warning: RF Strength is smaller than RSSI. \n");
      return (MXL_STATUS)status; // dfeAgcDuCalRef is below 0, so hpf keep off.
    }

    dfeAgcDuCalRef = (RFStrOnePercentdB - RF_RSSI_OFFSET) - (dfeRSSIOnePercentdB - DFE_RSSI_OFFSET);
    MxL_DLL_DEBUG0("[HPF OFF]RF_Strength =  %d (0.01dB), dfeRSSI = %d (0.01dB), dfeAgcDuCal = %d (0.01dB)\n",
                  (RFStrOnePercentdB - RF_RSSI_OFFSET), (dfeRSSIOnePercentdB - DFE_RSSI_OFFSET), dfeAgcDuCalRef);

    waitTimeCnt = MAX_WAIT_TIME_FOR_RSSI_MS/WAIT_TIME_FOR_RSSI_STEP_MS;

    // If du ref >= 30 and RF_freq >=400MHz, enable HPF
    if ((dfeAgcDuCalRef >= AGC_DU_THRESHOLD) && (atvTunerHpfLpfCfgPtr->FreqInHz >= HPF_FREQ_HZ_THRESHOLD))
    {
      // enable HPF
      status |= MxLWare661_OEM_ReadRegister(atvTunerHpfLpfCfgPtr->I2cSlaveAddr, HPF_CTRL_REG, &readData);
      readData |= 0x04;
      status |= MxLWare661_OEM_WriteRegister(atvTunerHpfLpfCfgPtr->I2cSlaveAddr, HPF_CTRL_REG, readData);
      MxL_DLL_DEBUG0("HPF is on \n");

      do {
        MxLWare661_OEM_Sleep(WAIT_TIME_FOR_RSSI_STEP_MS);
        status |= MxLWare661_OEM_ReadRegister(atvTunerHpfLpfCfgPtr->I2cSlaveAddr, RF_RSSI_DB_RB, &readData);
        if (readData != 0)
          break;
        waitTimeCnt --;
      }while (waitTimeCnt > 0);
      MxL_DLL_DEBUG0("waitTimeCnt = %d \n",waitTimeCnt);
      if(waitTimeCnt == 0)
      {
        MxL_DLL_DEBUG0("Warning: RF RSSI is zero after HPF on. \n");
        //disable HPF
        status |= MxLWare661_OEM_ReadRegister(atvTunerHpfLpfCfgPtr->I2cSlaveAddr, HPF_CTRL_REG, &readData);
        readData &= 0xFB;
        status |= MxLWare661_OEM_WriteRegister(atvTunerHpfLpfCfgPtr->I2cSlaveAddr, HPF_CTRL_REG, readData);
        return (MXL_STATUS)status;
      }

      // Get RF Strenth and RSSI to calculate DU
      status |= MxL661_GetRFStrenth(atvTunerHpfLpfCfgPtr->I2cSlaveAddr, &RFStrOnePercentdB);
      status |= MxL661_GetRSSI(atvTunerHpfLpfCfgPtr->I2cSlaveAddr, &dfeRSSIOnePercentdB); if(status != MXL_TRUE) return (MXL_STATUS)status;
      if((RFStrOnePercentdB - RF_RSSI_OFFSET) < (dfeRSSIOnePercentdB - DFE_RSSI_OFFSET))
      {
        MxL_DLL_DEBUG0("Warning: RF Strength is smaller than RSSI. \n");
        return (MXL_STATUS)status;
      }

      dfeAgcDuCal = (RFStrOnePercentdB - RF_RSSI_OFFSET) - (dfeRSSIOnePercentdB - DFE_RSSI_OFFSET);
      MxL_DLL_DEBUG0("[HPF ON]RF_Strength =  %d (0.01dB), dfeRSSI = %d (0.01dB), dfeAgcDuCal = %d (0.01dB)\n",
                    (RFStrOnePercentdB - RF_RSSI_OFFSET), (dfeRSSIOnePercentdB - DFE_RSSI_OFFSET), dfeAgcDuCal);

      // If DU decreases more than 10, keep HPF on, otherwise disable it.
      if(!((dfeAgcDuCal < dfeAgcDuCalRef) &&((dfeAgcDuCalRef-dfeAgcDuCal) >= DU_LEVEL_DIFF_THRESHOLD) ))
      {
        //disable HPF
        status |= MxLWare661_OEM_ReadRegister(atvTunerHpfLpfCfgPtr->I2cSlaveAddr, HPF_CTRL_REG, &readData);
        readData &= 0xFB;
        status |= MxLWare661_OEM_WriteRegister(atvTunerHpfLpfCfgPtr->I2cSlaveAddr, HPF_CTRL_REG, readData);
      }//otherwise keep HPF on.
    }// Else if dfe_agc_du_rb >= 20 and RF_freq <=250MHz, enable LPF
    else if ((dfeAgcDuCalRef >= AGC_DU_THRESHOLD) && (atvTunerHpfLpfCfgPtr->FreqInHz <= LPF_FREQ_HZ_THRESHOLD))
    {
      // enable LPF
      status |= MxLWare661_OEM_ReadRegister(atvTunerHpfLpfCfgPtr->I2cSlaveAddr, LPF_CTRL_REG, &readData);
      readData |= 0x08;
      status |= MxLWare661_OEM_WriteRegister(atvTunerHpfLpfCfgPtr->I2cSlaveAddr, LPF_CTRL_REG, readData);
      MxL_DLL_DEBUG0("LPF is on \n");

      do {
        MxLWare661_OEM_Sleep(WAIT_TIME_FOR_RSSI_STEP_MS);
        status |= MxLWare661_OEM_ReadRegister(atvTunerHpfLpfCfgPtr->I2cSlaveAddr, RF_RSSI_DB_RB, &readData);
        if (readData != 0)
          break;
        waitTimeCnt --;
      }while (waitTimeCnt > 0);
      MxL_DLL_DEBUG0("waitTimeCnt = %d \n",waitTimeCnt);
      if(waitTimeCnt == 0)
      {
        MxL_DLL_DEBUG0("Warning: RF RSSI is zero after LPF on. \n");
        //disable LPF
        status |= MxLWare661_OEM_ReadRegister(atvTunerHpfLpfCfgPtr->I2cSlaveAddr, LPF_CTRL_REG, &readData);
        readData &= 0xF7;
        status |= MxLWare661_OEM_WriteRegister(atvTunerHpfLpfCfgPtr->I2cSlaveAddr, LPF_CTRL_REG, readData);
        return (MXL_STATUS)status;
      }

      status |= MxL661_GetRFStrenth(atvTunerHpfLpfCfgPtr->I2cSlaveAddr, &RFStrOnePercentdB); // Get RF Strenth
      status |= MxL661_GetRSSI(atvTunerHpfLpfCfgPtr->I2cSlaveAddr, &dfeRSSIOnePercentdB); // Get RSSI
      if((RFStrOnePercentdB - RF_RSSI_OFFSET) < (dfeRSSIOnePercentdB - DFE_RSSI_OFFSET)) {
        MxL_DLL_DEBUG0("Warning: RF Strength is smaller than RSSI. \n");
        return (MXL_STATUS)status;
      }
      dfeAgcDuCal = (RFStrOnePercentdB - RF_RSSI_OFFSET) - (dfeRSSIOnePercentdB - DFE_RSSI_OFFSET);
      MxL_DLL_DEBUG0("RF_Strength =  %d (0.01dB), dfeRSSI = %d (0.01dB), dfeAgcDuCal = %d (0.01dB)\n",
                    (RFStrOnePercentdB - RF_RSSI_OFFSET), (dfeRSSIOnePercentdB - DFE_RSSI_OFFSET), dfeAgcDuCal);

      // If DU decreases more than 10, keep LPF on, otherwise disable it.
      if(!((dfeAgcDuCal < dfeAgcDuCalRef) &&((dfeAgcDuCalRef-dfeAgcDuCal) >= DU_LEVEL_DIFF_THRESHOLD) ))
      {
        //disable LPF
        status |= MxLWare661_OEM_ReadRegister(atvTunerHpfLpfCfgPtr->I2cSlaveAddr, LPF_CTRL_REG, &readData);
        readData &= 0xF7;
        status |= MxLWare661_OEM_WriteRegister(atvTunerHpfLpfCfgPtr->I2cSlaveAddr, LPF_CTRL_REG, readData);
      }//otherwise keep LPF on.
    }
    else
    {
      MxL_DLL_DEBUG0(" dfeAgcDuCalRef is less than 30, DU = %d (dB)\n", dfeAgcDuCalRef/100);
    }
  }
  else
  {
    MxL_DLL_DEBUG0(" RSSI is less than -38, RSSI = %d (dB)\n", (dfeRSSIOnePercentdB/100));
  }

  return(MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_ConfigTunerApplicationModeSet - MXL661_TUNER_MODE_CFG
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 07/13/2012
--|
--| DESCRIPTION   : This fucntion is used to configure MxL661 tuner's
--|                 application modes like DVB-T, DTMB, DVB-C, ISDB-T, PAL, SECAM,
--|                 ATSC, NTSC etc.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

static MXL_STATUS MxL661_ConfigTunerApplicationModeSet(PMXL661_TUNER_MODE_CFG_T modeSetPtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 dfeRegData = 0;
  MXL661_REG_CTRL_INFO_T* tmpRegTable = NULL;
  UINT8 idx = 0;
  UINT8 regData = 0;
  UINT16 ifFcw = 0;

  {
    MxL_DLL_DEBUG0("MXL661_TUNER_MODE_CFG, application mode = %d , IF = %d\n",
                                                            modeSetPtr->SignalMode,
                                                            modeSetPtr->IFOutFreqinKHz);

    switch(modeSetPtr->SignalMode)
    {
      // Application modes settings for NTSC mode
      case MXL661_ANA_NTSC_MODE:
        tmpRegTable = MxL661_AnalogNtsc;
        status |= MxL661_Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, tmpRegTable);

        if (modeSetPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ)
        {
          // Low power IF dependent settings
#ifdef MXL661_CUSTOMER_SPECIFIC_SETTING_1
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xFE);
#else
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0x7E);
#endif
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x10);

          if (modeSetPtr->XtalFreqSel == MXL661_XTAL_16MHz)
          {
            tmpRegTable = MxL661_Ntsc_16MHzRfLutSwpLIF;
            dfeRegData = 0x00;
          }
          else
          {
            tmpRegTable = MxL661_Ntsc_24MHzRfLutSwpLIF;
            dfeRegData = 0x01;
          }

          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, 0xDD, dfeRegData);

        }
        else
        {
          // High power IF dependent settings
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xD9);
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x16);

          tmpRegTable = MxL661_Ntsc_RfLutSwpHIF;
        }

        if (tmpRegTable)
          status |= MxL661_Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, tmpRegTable);
        else
          status |= MXL_FALSE;

        break;

      // Application modes settings for PAL-BG mode
      case MXL661_ANA_PAL_BG:

        tmpRegTable = MxL661_AnalogPal;
        status |= MxL661_Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, tmpRegTable);

        if (modeSetPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ)
        {
          // Low power IF dependent settings
#ifdef MXL661_CUSTOMER_SPECIFIC_SETTING_1
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xFE);
#else
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0x7E);
#endif
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x10);

          status |= MxL661_Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, MxL661_Pal_RfLutSwpLIF);
        }
        else
        {
          // High power IF dependent settings
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xD9);
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x16);
        }

        break;

      // Application modes settings for PAL-I mode
      case MXL661_ANA_PAL_I:
        status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, 0x0C, 0x0B);

        tmpRegTable = MxL661_AnalogPal;
        status |= MxL661_Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, tmpRegTable);

        if (modeSetPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ)
        {
          // Low power IF dependent settings
#ifdef MXL661_CUSTOMER_SPECIFIC_SETTING_1
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xFE);
#else
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0x7E);
#endif
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x10);

          status |= MxL661_Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, MxL661_Pal_RfLutSwpLIF);
        }
        else
        {
          // High power IF dependent settings
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xD9);
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x16);

          status |= MxL661_Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, MxL661_PalI_RfLutSwpHIF);

        }

        break;

      // Application modes settings for PAL-D mode
      case MXL661_ANA_PAL_D:
        status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, 0x0C, 0x0C);

        tmpRegTable = MxL661_AnalogPal;
        status |= MxL661_Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, tmpRegTable);

        if (modeSetPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ)
        {
          // Low power IF dependent settings
#ifdef MXL661_CUSTOMER_SPECIFIC_SETTING_1
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xFE);
#else
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0x7E);
#endif
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x10);

          status |= MxL661_Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, MxL661_Pal_RfLutSwpLIF);
        }
        else
        {
          // High power IF dependent settings
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xD9);
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x16);

          status |= MxL661_Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, MxL661_PalD_RfLutSwpHIF);

        }
        break;

      // Application modes settings for SECAM-I mode
      case MXL661_ANA_SECAM_I:
        status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, 0x0C, 0x0B);

        tmpRegTable = MxL661_AnalogSecam;
        status |= MxL661_Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, tmpRegTable);

        if (modeSetPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ)
        {
          // Low power IF dependent settings
#ifdef MXL661_CUSTOMER_SPECIFIC_SETTING_1
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xFE);
#else
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0x7E);
#endif
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x10);
        }
        else
        {
          // High power IF dependent settings
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xD9);
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x16);
        }
        break;

      // Application modes settings for SECAM-L mode
      case MXL661_ANA_SECAM_L:
        status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, 0x0C, 0x0C);

        tmpRegTable = MxL661_AnalogSecam;
        status |= MxL661_Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, tmpRegTable);

        if (modeSetPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ)
        {
          // Low power IF dependent settings
#ifdef MXL661_CUSTOMER_SPECIFIC_SETTING_1
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xFE);
#else
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0x7E);
#endif
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x10);
        }
        else
        {
          // High power IF dependent settings
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xD9);
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x16);
        }
        break;

      // Application modes settings for DVB-C/J.83B modes
      case MXL661_DIG_DVB_C:
      case MXL661_DIG_J83B:
        tmpRegTable = MxL661_DigitalDvbc;
        status |= MxL661_Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, tmpRegTable);

        if (modeSetPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ)
        {
          // Low power IF dependent settings
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xFE);
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x10);
        }
        else
        {
          // High power IF dependent settings
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xD9);
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x16);
        }

        if (modeSetPtr->XtalFreqSel == MXL661_XTAL_16MHz) dfeRegData = 0x0D;
        else dfeRegData = 0x0E;

        status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DFE_CSF_SS_SEL, dfeRegData);

        break;

      // Application modes settings for ISDB-T & ATSC modes
      case MXL661_DIG_ISDBT_ATSC:
        tmpRegTable = MxL661_DigitalIsdbtAtsc;
        status |= MxL661_Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, tmpRegTable);

        if (modeSetPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ)
        {
          // Low power IF dependent settings
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xF9);
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x18);
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_PWR, 0xF1);
        }
        else
        {
          // High power IF dependent settings
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xD9);
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x16);
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_PWR, 0xB1);
        }

        if (MXL661_XTAL_16MHz == modeSetPtr->XtalFreqSel) dfeRegData = 0x0D;
        else if (MXL661_XTAL_24MHz == modeSetPtr->XtalFreqSel) dfeRegData = 0x0E;

        status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DFE_CSF_SS_SEL, dfeRegData);

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
        status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DFE_DACIF_GAIN, dfeRegData);

        break;

      // Application modes settings for DVB-T mode and DTMB
      case MXL661_DIG_DVB_T_DTMB:
        tmpRegTable = MxL661_DigitalDvbt;
        status |= MxL661_Ctrl_ProgramRegisters(modeSetPtr->I2cSlaveAddr, tmpRegTable);

        if (modeSetPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ)
        {
          // Low power IF dependent settings
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xFE);
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x10); /* If it¡¦s low IF, change here */
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_PWR, 0xB1); /* If it¡¦s low IF, change here */
        }
        else
        {
          // High power IF dependent settings
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_0, 0xD9);
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x16);
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_PWR, 0xB1);
        }

        if (MXL661_XTAL_16MHz == modeSetPtr->XtalFreqSel) dfeRegData = 0x0D;
        else if (MXL661_XTAL_24MHz == modeSetPtr->XtalFreqSel) dfeRegData = 0x0E;

        status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DFE_CSF_SS_SEL, dfeRegData);

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

        // 2014.07.31 modify for improve Monaco DVB-T CN performance.
        // forcibly overwrite register 0x5B to 0x10 and register 0x5C to 0xB1 for DVB-T.
        #if 1 /* Overwrite register 0x5B(DIG_ANA_IF_CFG_1) to 0x10, and register 0x5C(DIG_ANA_IF_PWR) to 0xB1.  */
        status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_CFG_1, 0x10);
        status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DIG_ANA_IF_PWR, 0xB1);
        #endif

        status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DFE_DACIF_GAIN, dfeRegData);
        break;

      default:
        status |= MXL_FALSE;
        break;
    }

  }

  if (MXL_FALSE != status)
  {
    status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, XTAL_EXT_BIAS_REG, 0x0A);

    // XTAL calibration
    status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, XTAL_CALI_SET_REG, 0x00);
    status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, XTAL_CALI_SET_REG, 0x01);

    // 50 ms sleep after XTAL calibration
    MxLWare661_OEM_Sleep(50);

    // Only for Analog modes
    if (modeSetPtr->SignalMode <= MXL661_ANA_SECAM_L)
    {
      // check MxL661 version, if it is V3 or V4, call below code
      status |= MxLWare661_OEM_ReadRegister(modeSetPtr->I2cSlaveAddr, CHIP_VERSION_REQ_REG, &regData);
      if((regData & 0xFF) == 0x4)//MxL661 V4
      {
        // Program 0x0169 register with 0x01
        status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, PAGE_CHANGE_REG, 0x01);
        status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DFE_SEQ_SPARE2_REG, 0x01);
        status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, PAGE_CHANGE_REG, 0x00);
        MxL_DLL_DEBUG0("Program 0x0169 register with 0x01 for MxL661 v4. \n");
      }
	  else if((regData & 0xFF) == 0x2)
	  {
        status |= MxLWare661_OEM_ReadRegister(modeSetPtr->I2cSlaveAddr,0x5F, &regData);
        if (regData != 0x00) ////MxL661 V3
        {
          // Program 0x0169 register with 0x01
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, PAGE_CHANGE_REG, 0x01);
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, DFE_SEQ_SPARE2_REG, 0x01);
          status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, PAGE_CHANGE_REG, 0x00);
          MxL_DLL_DEBUG0("Program 0x0169 register with 0x01 for MxL661 v3. \n");
        }
	  }
      // read data to improve xtal spurs - to be used during channel tune function
      for (idx = 0; idx < MAX_MXL661_DEVICES; idx++)
      {
#ifdef MXL661_CUSTOMER_SPECIFIC_SETTING_3
        if (modeSetPtr->SignalMode == MXL661_ANA_NTSC_MODE)
        {
          if (MxL661ifFcwCfg[idx].i2cAddr == modeSetPtr->I2cSlaveAddr)
          {
            if (MxL661ifFcwCfg[idx].if_fcw_byp == 0)
            {
              status |= MxLWare661_OEM_ReadRegister(modeSetPtr->I2cSlaveAddr, IF_FREQ_SEL_REG, &regData);
              status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, IF_FREQ_SEL_REG, (regData | 0x20));

              if (MxL661ifFcwCfg[idx].if_invert == 0)
                ifFcw = MxL661ifFcwOverwriteTable[MxL661ifFcwCfg[idx].if_sel].if_fcw_noninvert;
              else
                ifFcw = MxL661ifFcwOverwriteTable[MxL661ifFcwCfg[idx].if_sel].if_fcw_invert;
            }
            else
            {
              if (MxL661ifFcwCfg[idx].if_invert == 0)
                ifFcw = (UINT16)((MxL661ifFcwCfg[idx].manualIFOutFreqInKHz - 188) * 8192 / 216000);
              else
                ifFcw = (UINT16)((MxL661ifFcwCfg[idx].manualIFOutFreqInKHz + 188) * 8192 / 216000);
            }

            regData = (UINT8)(ifFcw & 0x00FF);
            status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, IF_FCW_LOW_REG, regData);

            regData = (UINT8)((ifFcw >> 8) & 0x000F);
            status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, IF_FCW_HIGH_REG, regData);

          }
        }
        else
        {
          // Apply IF frequency values for other application modes, without offset
          if (MxL661ifFcwCfg[idx].i2cAddr == modeSetPtr->I2cSlaveAddr)
          {
            status |= MxLWare661_OEM_ReadRegister(modeSetPtr->I2cSlaveAddr, IF_FREQ_SEL_REG, &regData);

            // IF value from pre-set IF_SEL table
            if (MxL661ifFcwCfg[idx].if_fcw_byp == 0)
            {
              regData &= 0xC0;
              regData |= MxL661ifFcwCfg[idx].if_sel; // saved IF Freq value from IF_SEL table
              status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, IF_FREQ_SEL_REG, regData);
            }
            else
            {
              // IF out manual setting : bit<5>
              regData |= 0x20;
              status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, IF_FREQ_SEL_REG, regData);

              // Manual IF freq set
              ifFcw = (UINT16)(MxL661ifFcwCfg[idx].manualIFOutFreqInKHz * 8192 / 216000);
              regData = (ifFcw & 0xFF); // Get low 8 bit
              status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, IF_FCW_LOW_REG, regData);

              regData = ((ifFcw >> 8) & 0x0F); // Get high 4 bit
              status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, IF_FCW_HIGH_REG, regData);

            }
          }
        }
 #endif
        if (MxL661xtalSpurCfg[idx].i2cAddr == modeSetPtr->I2cSlaveAddr)
        {
          // If previous Application mode is PAL-BG & current mode
          // is also PAL B/G then do not read reg values.
          if (!((MxL661xtalSpurCfg[idx].appMode == (UINT8)MXL661_ANA_PAL_BG) && (modeSetPtr->SignalMode == MXL661_ANA_PAL_BG)))
          {
            // change page to 1
            status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, 0x00, 0x01);

            // read reg ana_dig_refsx_xtal_amp_rb
            status |= MxLWare661_OEM_ReadRegister(modeSetPtr->I2cSlaveAddr, 0xA2, &MxL661xtalSpurCfg[idx].xtalAmp_Rb);

            // read reg ana_dig_refsx_xtal_amp_lin_rb
            status |= MxLWare661_OEM_ReadRegister(modeSetPtr->I2cSlaveAddr, 0xA1, &MxL661xtalSpurCfg[idx].xtalAmp_LinRb);

            MxL661xtalSpurCfg[idx].xtalAmp_LinRb &= 0x30;
            MxL661xtalSpurCfg[idx].xtalAmp_LinRb >>= 4;

            // change page to 0
            status |= MxLWare661_OEM_WriteRegister(modeSetPtr->I2cSlaveAddr, 0x00, 0x00);

            MxL661xtalSpurCfg[idx].appMode = (UINT8)modeSetPtr->SignalMode;

          }
        }
      }
    }

    for (idx = 0; idx < MAX_MXL661_DEVICES; idx++)
    {
      if (MxL661xtalSpurCfg[idx].i2cAddr == modeSetPtr->I2cSlaveAddr)
      {
        MxL661xtalSpurCfg[idx].appMode = (UINT8)modeSetPtr->SignalMode;
        break;
      }
    }
  }

  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_ConfigTunerAgcSet - MXL661_TUNER_AGC_CFG
--|
--| AUTHOR        : Dong Liu
--|                 Sunghoon Park
--|
--| DATE CREATED  : 06/21/2011
--|                 04/21/2011
--|                 11/13/2011 (MK) - Change bit address for AGC Type function.
--|
--| DESCRIPTION   : This function is used to configure AGC settings of MxL661
--|                 tuner device.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

static MXL_STATUS MxL661_ConfigTunerAgcSet(PMXL661_AGC_SET_CFG_T agcSetPtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 regData = 0;

  MxL_DLL_DEBUG0("MXL661_TUNER_AGC_CFG, AGC mode = %d, sel = %d, set point = %d",
    agcSetPtr->AgcSel, agcSetPtr->AgcType, agcSetPtr->SetPoint);

  // AGC selecton <3:2> and mode setting <0>
  status |= MxLWare661_OEM_ReadRegister(agcSetPtr->I2cSlaveAddr, AGC_CONFIG_REG, &regData);
  regData &= 0xF2; // Clear bits <3:2> & <0>
  regData = (UINT8) (regData | (agcSetPtr->AgcType << 2) | agcSetPtr->AgcSel);
  status |= MxLWare661_OEM_WriteRegister(agcSetPtr->I2cSlaveAddr, AGC_CONFIG_REG, regData);

  // AGC set point <6:0>
  status |= MxLWare661_OEM_ReadRegister(agcSetPtr->I2cSlaveAddr, AGC_SET_POINT_REG, &regData);
  regData &= 0x80; // Clear bit <6:0>
  regData |= agcSetPtr->SetPoint;
  status |= MxLWare661_OEM_WriteRegister(agcSetPtr->I2cSlaveAddr, AGC_SET_POINT_REG, regData);

  // AGC Polarity <4>
  status |= MxLWare661_OEM_ReadRegister(agcSetPtr->I2cSlaveAddr, AGC_FLIP_REG, &regData);
  regData &= 0xEF; // Clear bit <4>
  regData |= (agcSetPtr->AgcPolarityInverstion << 4);
  status |= MxLWare661_OEM_WriteRegister(agcSetPtr->I2cSlaveAddr, AGC_FLIP_REG, regData);

  return(MXL_STATUS) status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_ConfigTunerFineTune - MXL661_TUNER_FINE_TUNE_CFG
--|
--| AUTHOR        : Dong Liu
--|                 Sunghoon Park
--|
--| DATE CREATED  : 06/25/2012
--|                 04/22/2011
--|
--| DESCRIPTION   : This function is used to control fine tune step (freq offset)
--|                 when MxL661 is used in Analog mode.
--|
--| RETURN VALUE  : MXL_TRUE, MXL_FALSE or MXL_INVALID_PARAMETER
--|
--|---------------------------------------------------------------------------*/

static MXL_STATUS MxL661_ConfigTunerFineTune(PMXL661_FINE_TUNE_CFG_T fineTunePtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 regData = 0;

#ifdef MXL661_CUSTOMER_SPECIFIC_SETTING_3
  S8 fineTuneStepRb  = 0;
  UINT8 idx = 0;
  UINT8 fineTuneStepRbMax  = ANA_NTSC_FINETUNE_STEP_RB_MAX;
  UINT8 fineTuneStepRbMin  = ANA_NTSC_FINETUNE_STEP_RB_MIN;

  for (idx = 0; idx < MAX_MXL661_DEVICES; idx++)
  {
    if (MxL661xtalSpurCfg[idx].i2cAddr == fineTunePtr->I2cSlaveAddr)
	{
	  // Check if signal type is Analog
	  if (MxL661xtalSpurCfg[idx].appMode == MXL661_ANA_NTSC_MODE)
	  {
	    // Apply N+1 blocker settings
	    fineTuneStepRbMax = ANA_NTSC_FINETUNE_STEP_RB_MAX;
	    fineTuneStepRbMin = ANA_NTSC_FINETUNE_STEP_RB_MIN;
	  }
	  else
	  {
	    // Undo N+1 blocker settings if app mode is not NTSC
	    fineTuneStepRbMax = ANA_FINETUNE_STEP_RB_MAX;
	    fineTuneStepRbMin = ANA_FINETUNE_STEP_RB_MIN;
	  }
	  break;
	}
  }

  MxL_DLL_DEBUG0("MXL661_TUNER_FINE_TUNE_CFG( MXL661_CUSTOMER_SPECIFIC_SETTING_3 ), fine tune = %d, appMode = %d \n",
                                                             fineTunePtr->ScaleUp, MxL661xtalSpurCfg[idx].appMode);

  // When doing fine tune, we need to first readback dfe_finetune_step_rb (current fine_tune step),
  // then overwrite the new fine_tune step value (dfe_finetune_step_rb+1 if tuning up, or dfe_finetune_step_rb-1 if tuning down)
  // to the register dfe_finetune_step_w (0x84[6:0]).
  // The dfe_finetune_step_w 0x84[7] is DFE_FINETUNE_STEP_BYP, so we should keep this bit with 1.
  status |= MxLWare661_OEM_ReadRegister(fineTunePtr->I2cSlaveAddr, DFE_FINETUNE_STEP_RB,  &regData);
  fineTuneStepRb = regData;
  if (MXL_FINE_TUNE_STEP_UP == fineTunePtr->ScaleUp)
  {
	if( fineTuneStepRbMax == fineTuneStepRb )
      fineTuneStepRb = fineTuneStepRbMin;
	else
      fineTuneStepRb = (fineTuneStepRb - 1);
    if (fineTuneStepRb < 0)
      regData = ( (fineTuneStepRb + 0x80) | 0x80 ); // ( to make MSB=1);
    else
      regData = ( fineTuneStepRb | 0x80 );
  }
  else if (MXL_FINE_TUNE_STEP_DOWN == fineTunePtr->ScaleUp)
  {
	if( fineTuneStepRbMin == fineTuneStepRb )
	  regData = ( fineTuneStepRbMax | 0x80 );
	else
      regData = ( (fineTuneStepRb + 1) | 0x80 );
  }
  else
    return MXL_INVALID_PARAMETER;

  status |= MxLWare661_OEM_WriteRegister(fineTunePtr->I2cSlaveAddr, DFE_FINETUNE_STEP_REG, regData);
#else

  MxL_DLL_DEBUG0("MXL661_TUNER_FINE_TUNE_CFG, fine tune = %d", fineTunePtr->ScaleUp);

  status |= MxLWare661_OEM_ReadRegister(fineTunePtr->I2cSlaveAddr, DFE_FINETUNE_STEP_REG, &regData);
  if ((regData & 0x80) == 0x80)  // Fine tune is by passed
  {
    regData &= 0x7F;
    status |= MxLWare661_OEM_WriteRegister(fineTunePtr->I2cSlaveAddr, DFE_FINETUNE_STEP_REG, regData); // Set Bit<7> = 0
  }
#endif

  status |= MxLWare661_OEM_ReadRegister(fineTunePtr->I2cSlaveAddr, FINE_TUNE_SET_REG, &regData);

  // Fine tune <1:0>
  regData &= 0xFC;
  status |= MxLWare661_OEM_WriteRegister(fineTunePtr->I2cSlaveAddr, FINE_TUNE_SET_REG, regData);

  if (MXL_FINE_TUNE_STEP_UP == fineTunePtr->ScaleUp)
    regData |= FINE_TUNE_FREQ_INCREASE;
  else
    regData |= FINE_TUNE_FREQ_DECREASE;

  status |= MxLWare661_OEM_WriteRegister(fineTunePtr->I2cSlaveAddr, FINE_TUNE_SET_REG, regData);

  return(MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_ConfigTunerEnableFineTune -
--|                                           MXL661_TUNER_ENABLE_FINE_TUNE_CFG
--|
--| AUTHOR        : Sunghoon Park
--|                 Dong Liu
--|
--| DATE CREATED  : 04/22/2011
--|                 07/01/2011
--|
--| DESCRIPTION   : This fucntion is used to enable or disable fine tune function
--|                 when MxL661 device is used in Analog mode.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

static MXL_STATUS MxL661_ConfigTunerEnableFineTune(PMXL661_ENABLE_FINE_TUNE_CFG_T fineTunePtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 fineTuneReg1 = 0;
  UINT8 fineTuneReg2 = 0;

  MxL_DLL_DEBUG0("MXL661_TUNER_ENABLE_FINE_TUNE_CFG, fine tune = %d",
                                                    fineTunePtr->EnableFineTune);

  status |= MxLWare661_OEM_ReadRegister(fineTunePtr->I2cSlaveAddr, FINE_TUNE_CTRL_REG_0, &fineTuneReg1);
  status |= MxLWare661_OEM_ReadRegister(fineTunePtr->I2cSlaveAddr, FINE_TUNE_CTRL_REG_1, &fineTuneReg2);

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

  status |= MxLWare661_OEM_WriteRegister(fineTunePtr->I2cSlaveAddr, FINE_TUNE_CTRL_REG_0, fineTuneReg1);
  status |= MxLWare661_OEM_WriteRegister(fineTunePtr->I2cSlaveAddr, FINE_TUNE_CTRL_REG_1, fineTuneReg2);

  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_ConfigTunerChanTune - MXL661_TUNER_CHAN_TUNE_CFG
--|
--| AUTHOR        : Sunghoon Park
--|                 Mahendra Kondur
--|                 Dong Liu
--|
--| DATE CREATED  : 3/17/2011
--|                 04/21/2012 - S1 blocker improvements for PAL-D
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

static MXL_STATUS MxL661_ConfigTunerChanTune(PMXL661_TUNER_TUNE_CFG_T tuneParamPtr)
{
  UINT32 frequency;
  UINT32 freq = 0;
  UINT8 status = MXL_TRUE;
  UINT8 regData = 0;
  UINT8 idx = 0;
  SINT16 tmpData = 0;
#ifdef MXL661_CUSTOMER_SPECIFIC_SETTING_1
  MXL661_ENABLE_FINE_TUNE_CFG_T fineTuneCfg;
#endif
  MXL661_CHAN_DEPENDENT_FREQ_TABLE_T *freqLutPtr = NULL;

  MxL_DLL_DEBUG0("MXL661_TUNER_CHAN_TUNE_CFG, signal type = %d (%d), Freq = %d, BW = %d, Xtal = %d \n",
                                              tuneParamPtr->SignalMode,
                                              tuneParamPtr->NtscCarrier,
                                              tuneParamPtr->FreqInHz,
                                              tuneParamPtr->BandWidth,
                                              tuneParamPtr->XtalFreqSel);

  // Here we need set HPF and LPF to default when tuner is MxL661 and work at Analog TV mode
  if (tuneParamPtr->SignalMode <= MXL661_ANA_SECAM_L)
  {
    status |= MxLWare661_OEM_ReadRegister(tuneParamPtr->I2cSlaveAddr, CHIP_VERSION_REQ_REG, &regData);
    if(regData != 0x4)
      MxL_DLL_DEBUG0(" It's not the MxL661 chip, don't need set HPF and LPF to default. \n");
    else
    {
      status |= MxLWare661_OEM_ReadRegister(tuneParamPtr->I2cSlaveAddr, HPF_CTRL_REG, &regData);
      regData &= 0xFB;
      status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, HPF_CTRL_REG, regData);


      status |= MxLWare661_OEM_ReadRegister(tuneParamPtr->I2cSlaveAddr, LPF_CTRL_REG, &regData);
      regData &= 0xF7;
      status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, LPF_CTRL_REG, regData);
    }
  }

  if ((tuneParamPtr->SignalMode <= MXL661_ANA_SECAM_L) && (tuneParamPtr->TuneType == MXL661_VIEW_MODE))
  {
    // RF Frequency VCO Band Settings
    regData = 0;
    if (tuneParamPtr->FreqInHz < APP_MODE_FREQ_HZ_THRESHOLD_3)
    {
      status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, 0x7C, 0x1F);
      if ((tuneParamPtr->SignalMode == MXL661_DIG_DVB_C) || (tuneParamPtr->SignalMode == MXL661_DIG_J83B))
        regData = 0xC1;
      else
        regData = 0x81;

    }
    else
    {
      status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, 0x7C, 0x9F);

      if ((tuneParamPtr->SignalMode == MXL661_DIG_DVB_C) || (tuneParamPtr->SignalMode == MXL661_DIG_J83B))
        regData = 0xD1;
      else
        regData = 0x91;

    }

    status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, 0x00, 0x01);
    status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, 0x31, regData);
    status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, 0x00, 0x00);

    switch(tuneParamPtr->SignalMode)
    {
      // Signal type is NTSC mode
      case MXL661_ANA_NTSC_MODE:

        // If 16MHz XTAL is used then need to program registers based on frequency value
        if (MXL661_XTAL_16MHz == tuneParamPtr->XtalFreqSel)
        {
          if (MXL661_NTSC_CARRIER_NA == tuneParamPtr->NtscCarrier)
          {
            // Select spur shifting LUT to be used based NTSC, HRC or IRC frequency
            if ((tuneParamPtr->FreqInHz % 1000000) == 0)
            {
              // Apply spur shifting LUT based on HIF or LIF setting
              if (tuneParamPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ) freqLutPtr = MXL661_NTSC_FREQ_LUT_XTAL_16MHZ_LIF;
              else freqLutPtr = MXL661_NTSC_FREQ_LUT_XTAL_16MHZ_HIF;

            }
            else if ((tuneParamPtr->FreqInHz % 12500) == 0)
            {
              freqLutPtr = MXL661_NTSC_FREQ_LUT_IRC_16MHZ;
            }
            else
            {
              freqLutPtr = MXL661_NTSC_FREQ_LUT_HRC_16MHZ;
              status |= MxL661_Ctrl_ProgramRegisters(tuneParamPtr->I2cSlaveAddr, MxL661_Ntsc_HRCRfLutSwpLIF);
            }
          }
          else
          {
            // Select LUT based on NTSC carriers
            if (MXL661_NTSC_CARRIER_HRC == tuneParamPtr->NtscCarrier)
            {
              freqLutPtr = MXL661_NTSC_FREQ_LUT_HRC_16MHZ;
              status |= MxL661_Ctrl_ProgramRegisters(tuneParamPtr->I2cSlaveAddr, MxL661_Ntsc_HRCRfLutSwpLIF);
            }
            else
            {
              freqLutPtr = MXL661_NTSC_FREQ_LUT_IRC_16MHZ;
            }
          }
        } // end of if (16 MHz XTAL
        else if (MXL661_XTAL_24MHz == tuneParamPtr->XtalFreqSel)
        {
          if (MXL661_NTSC_CARRIER_NA == tuneParamPtr->NtscCarrier)
          {
            // Select spur shifting LUT to be used based NTSC, HRC or IRC frequency
            if ((tuneParamPtr->FreqInHz % 1000000) == 0)
            {
              freqLutPtr = MXL661_NTSC_FREQ_LUT_XTAL_24MHZ;
            }
            else if ((tuneParamPtr->FreqInHz % 12500) == 0)
            {
              freqLutPtr = MXL661_NTSC_FREQ_LUT_IRC_24MHZ;
            }
            else
            {
              freqLutPtr = MXL661_NTSC_FREQ_LUT_HRC_24MHZ;
              status |= MxL661_Ctrl_ProgramRegisters(tuneParamPtr->I2cSlaveAddr, MxL661_Ntsc_HRCRfLutSwpLIF);
            }

          }
          else
          {
             // Select LUT based on NTSC carriers
            if (MXL661_NTSC_CARRIER_HRC == tuneParamPtr->NtscCarrier)
            {
              freqLutPtr = MXL661_NTSC_FREQ_LUT_HRC_24MHZ;
              status |= MxL661_Ctrl_ProgramRegisters(tuneParamPtr->I2cSlaveAddr, MxL661_Ntsc_HRCRfLutSwpLIF);
            }
            else
            {
              freqLutPtr = MXL661_NTSC_FREQ_LUT_IRC_24MHZ;
            }

          }

        } // end of if (24 MHz XTAL

        if (freqLutPtr)
          status |= MxL661_Ctrl_SetRfFreqLutReg(tuneParamPtr->I2cSlaveAddr, tuneParamPtr->FreqInHz, freqLutPtr);

        break;

      // Signal type is PAL D
      case MXL661_ANA_PAL_D:

        // If 16MHz XTAL is used then need to program registers based on frequency value
        if (MXL661_XTAL_16MHz == tuneParamPtr->XtalFreqSel)
        {
          if (tuneParamPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ) freqLutPtr = MXL661_PAL_D_LUT_XTAL_16MHZ_LIF;
          else freqLutPtr = MXL661_PAL_D_LUT_XTAL_16MHZ_HIF;

        } // end of if (16 MHz XTAL
        else if (MXL661_XTAL_24MHz == tuneParamPtr->XtalFreqSel)
        {
          freqLutPtr = MXL661_PAL_D_LUT_XTAL_24MHZ;
        } // end of if (24 MHz XTAL

        if (freqLutPtr)
          status |= MxL661_Ctrl_SetRfFreqLutReg(tuneParamPtr->I2cSlaveAddr, tuneParamPtr->FreqInHz, freqLutPtr);

        // For PAL-D, additional registers need to be programmed for
        // S1 blocker performance improvement in VHF channels.
        if (tuneParamPtr->FreqInHz >= APP_MODE_FREQ_HZ_THRESHOLD_1)
        {
          status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, 0x93, 0x33);
          status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, 0x94, 0x44);
          status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, 0xBA, 0x40);
          status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, 0x5D, 0x0E);
        }
        else
        {
          status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, 0x93, 0x44);
          status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, 0x94, 0x55);
          status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, 0xBA, 0x50);
          status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, 0x5D, 0x0F);
        }

        break;

      case MXL661_ANA_PAL_BG:

        switch(tuneParamPtr->BandWidth)
        {
          case MXL661_ANA_TV_DIG_CABLE_BW_7MHz:
            regData = 0x09;
            break;

          case MXL661_ANA_TV_DIG_CABLE_BW_8MHz:
            regData = 0x0A;
            break;

          case MXL661_ANA_TV_DIG_CABLE_BW_6MHz:
          case MXL661_DIG_TERR_BW_6MHz:
          case MXL661_DIG_TERR_BW_7MHz:
          case MXL661_DIG_TERR_BW_8MHz:
          default:
            break;
        }

        status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, 0x0C, regData);

        // check MxL661 version, if it is V3 or V4, call below code
        status |= MxLWare661_OEM_ReadRegister(tuneParamPtr->I2cSlaveAddr, CHIP_VERSION_REQ_REG, &regData);
        if((regData & 0xFF) == 0x4)//MxL661 V4
        {
          // Program 0x0169 register with 0x00
          status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, PAGE_CHANGE_REG, 0x01);
          status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, DFE_SEQ_SPARE2_REG, 0x00);
          status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, PAGE_CHANGE_REG, 0x00);
          MxL_DLL_DEBUG0("Program 0x0169 register with 0x00 for MxL661 v4. \n");
        }
        else if((regData & 0xFF) == 0x2)
        {
          status |= MxLWare661_OEM_ReadRegister(tuneParamPtr->I2cSlaveAddr,0x5F, &regData);
          if (regData != 0x00) ////MxL661 V3
          {
          // Program 0x0169 register with 0x00
          status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, PAGE_CHANGE_REG, 0x01);
          status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, DFE_SEQ_SPARE2_REG, 0x00);
          status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, PAGE_CHANGE_REG, 0x00);
          MxL_DLL_DEBUG0("Program 0x0169 register with 0x00 for MxL661 v3. \n");
          }
        }

        // If 16MHz XTAL is used then need to program registers based on frequency value
        if (MXL661_XTAL_16MHz == tuneParamPtr->XtalFreqSel)
        {
          // PAL - BG 7 MHz Frequency range
          if (MXL661_ANA_TV_DIG_CABLE_BW_7MHz == tuneParamPtr->BandWidth)
          {
            if (tuneParamPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ)
            {
              freqLutPtr = MXL661_PAL_BG_7MHZ_LUT_XTAL_16MHZ_LIF;
              status |= MxL661_Ctrl_ProgramRegisters(tuneParamPtr->I2cSlaveAddr, MxL661_Pal_RfLutSwpLIF);
            }
            else
            {
              freqLutPtr = MXL661_PAL_BG_7MHZ_LUT_XTAL_16MHZ_HIF;
              status |= MxL661_Ctrl_ProgramRegisters(tuneParamPtr->I2cSlaveAddr, MxL661_PalBG_7MHzBW_RfLutSwpHIF);
            }

          }
          else
          {
            if (tuneParamPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ)
            {
              freqLutPtr = MXL661_PAL_BG_8MHZ_LUT_XTAL_16MHZ_LIF;
              status |= MxL661_Ctrl_ProgramRegisters(tuneParamPtr->I2cSlaveAddr, MxL661_Pal_RfLutSwpLIF);
            }
            else
            {
              freqLutPtr = MXL661_PAL_BG_8MHZ_LUT_XTAL_16MHZ_HIF;
              status |= MxL661_Ctrl_ProgramRegisters(tuneParamPtr->I2cSlaveAddr, MxL661_PalBG_8MHzBW_RfLutSwpHIF);
            }
          }

        } // end of if (MXL661_XTAL_16MHz
        else if (MXL661_XTAL_24MHz == tuneParamPtr->XtalFreqSel)
        {
          // If 16MHz XTAL is used then need to program registers based on frequency value
          // PAL - BG 7 MHz Frequency range
          if (MXL661_ANA_TV_DIG_CABLE_BW_7MHz == tuneParamPtr->BandWidth)
          {
            freqLutPtr = MXL661_PAL_BG_7MHZ_LUT_XTAL_24MHZ;

            if (tuneParamPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ)
              status |= MxL661_Ctrl_ProgramRegisters(tuneParamPtr->I2cSlaveAddr, MxL661_Pal_RfLutSwpLIF);
            else
              status |= MxL661_Ctrl_ProgramRegisters(tuneParamPtr->I2cSlaveAddr, MxL661_PalBG_7MHzBW_RfLutSwpHIF);

          }
          else
          {
            freqLutPtr = MXL661_PAL_BG_8MHZ_LUT_XTAL_24MHZ;

            if (tuneParamPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ)
              status |= MxL661_Ctrl_ProgramRegisters(tuneParamPtr->I2cSlaveAddr, MxL661_Pal_RfLutSwpLIF);
            else
              status |= MxL661_Ctrl_ProgramRegisters(tuneParamPtr->I2cSlaveAddr, MxL661_PalBG_8MHzBW_RfLutSwpHIF);

          }

        } // end of if (MXL661_XTAL_24MHz

        if (freqLutPtr)
          status |= MxL661_Ctrl_SetRfFreqLutReg(tuneParamPtr->I2cSlaveAddr, tuneParamPtr->FreqInHz, freqLutPtr);

        break;

      case MXL661_ANA_PAL_I:

        // If 16MHz XTAL is used then need to program registers based on frequency value
        if (MXL661_XTAL_16MHz == tuneParamPtr->XtalFreqSel)
        {
          if (tuneParamPtr->IFOutFreqinKHz < HIGH_IF_35250_KHZ) freqLutPtr = MXL661_PAL_I_LUT_XTAL_16MHZ_LIF;
          else freqLutPtr = MXL661_PAL_I_LUT_XTAL_16MHZ_HIF;
        }
        else
        {
          freqLutPtr = MXL661_PAL_I_LUT_XTAL_24MHZ;
        }

        if (freqLutPtr)
          status |= MxL661_Ctrl_SetRfFreqLutReg(tuneParamPtr->I2cSlaveAddr, tuneParamPtr->FreqInHz, freqLutPtr);

        break;

      case MXL661_ANA_SECAM_L:

        // If 16MHz XTAL is used then need to program registers based on frequency value
        if (MXL661_XTAL_16MHz == tuneParamPtr->XtalFreqSel)
        {
          freqLutPtr = MXL661_SECAM_L_LUT_XTAL_16MHZ;
        } // end of if (16 MHz XTAL
        else
        {
          freqLutPtr = MXL661_SECAM_L_LUT_XTAL_24MHZ;
        }

        if (freqLutPtr)
          status |= MxL661_Ctrl_SetRfFreqLutReg(tuneParamPtr->I2cSlaveAddr, tuneParamPtr->FreqInHz, freqLutPtr);
        break;

      case MXL661_DIG_DVB_C:
      case MXL661_DIG_J83B:
        if ((tuneParamPtr->BandWidth == MXL661_DIG_TERR_BW_6MHz) || (tuneParamPtr->BandWidth == MXL661_DIG_TERR_BW_8MHz))
        {
          if (tuneParamPtr->BandWidth == MXL661_DIG_TERR_BW_6MHz) freqLutPtr = MXL661_DIG_CABLE_FREQ_LUT_BW_6MHZ;
          else freqLutPtr = MXL661_DIG_CABLE_FREQ_LUT_BW_8MHZ;

          status |= MxL661_Ctrl_SetRfFreqLutReg(tuneParamPtr->I2cSlaveAddr, tuneParamPtr->FreqInHz, freqLutPtr);
        }
        break;

      case MXL661_DIG_ISDBT_ATSC:
      case MXL661_DIG_DVB_T_DTMB:

        if (tuneParamPtr->BandWidth == MXL661_DIG_TERR_BW_6MHz) freqLutPtr = MXL661_DIG_TERR_FREQ_LUT_BW_6MHZ;
        else if (tuneParamPtr->BandWidth == MXL661_DIG_TERR_BW_7MHz) freqLutPtr = MXL661_DIG_TERR_FREQ_LUT_BW_7MHZ;
        else freqLutPtr = MXL661_DIG_TERR_FREQ_LUT_BW_8MHZ;

        status |= MxL661_Ctrl_SetRfFreqLutReg(tuneParamPtr->I2cSlaveAddr, tuneParamPtr->FreqInHz, freqLutPtr);
        break;

      case MXL661_SIGNAL_NA:
      default:
        break;
    }
  }

  // Tune mode <0>
  status |= MxLWare661_OEM_ReadRegister(tuneParamPtr->I2cSlaveAddr, TUNE_MODE_REG, &regData);
  regData &= 0xFE;

  if (MXL661_SCAN_MODE == tuneParamPtr->TuneType) regData |= 0x01;

  status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, TUNE_MODE_REG, regData);

  // Bandwidth <7:0>
  status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, CHAN_TUNE_BW_REG, (UINT8)tuneParamPtr->BandWidth);

  // Frequency
  frequency = tuneParamPtr->FreqInHz / 1000;

  /* Calculate RF Channel = DIV(64*RF(Hz), 1E6) */
  frequency *= 64;
  freq = (UINT32)((frequency + 500)/ 1000); // Round operation

  // Set RF
  status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, CHAN_TUNE_LOW_REG, (UINT8)(freq & 0xFF));
  status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, CHAN_TUNE_HI_REG, (UINT8)((freq >> 8 ) & 0xFF));

  // Only for Analog modes
  if (tuneParamPtr->SignalMode <= MXL661_ANA_SECAM_L)
  {
    // apply xtal spur improvement settings
    for (idx = 0; idx < MAX_MXL661_DEVICES; idx++)
    {
      if (MxL661xtalSpurCfg[idx].i2cAddr == tuneParamPtr->I2cSlaveAddr)
      {
        regData = 0x80;
        tmpData = (MxL661xtalSpurCfg[idx].xtalAmp_Rb + MxL661xtalSpurCfg[idx].xtalAmp_LinRb);

        //if ((tuneParamPtr->FreqInHz < 300000000) && (tuneParamPtr->SignalMode <= MXL661_ANA_SECAM_L))
        if (tuneParamPtr->FreqInHz < 300000000)
        {
          if ((tmpData - 5) > 0)
            regData += ((MxL661xtalSpurCfg[idx].xtalAmp_Rb + MxL661xtalSpurCfg[idx].xtalAmp_LinRb)-5);
        }
        else
        {
          regData += (MxL661xtalSpurCfg[idx].xtalAmp_Rb + MxL661xtalSpurCfg[idx].xtalAmp_LinRb);
        }

        status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, XTAL_EXT_BIAS_REG, regData);

        break;
      }
    }
  }

#ifdef MXL661_CUSTOMER_SPECIFIC_SETTING_1
  if ((tuneParamPtr->SignalMode <= MXL661_ANA_SECAM_L) && (tuneParamPtr->TuneType == MXL661_VIEW_MODE))
  {
    // Disable Fine tune for Analog mode channels
    fineTuneCfg.I2cSlaveAddr = tuneParamPtr->I2cSlaveAddr;
    fineTuneCfg.EnableFineTune = MXL_DISABLE;
    status |= MxL661_ConfigTunerEnableFineTune(&fineTuneCfg);

    regData = 0;
    status |= MxLWare661_OEM_ReadRegister(tuneParamPtr->I2cSlaveAddr, FINE_TUNE_CTRL_REG_1, &regData);
    regData |= 0x20;
    status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, FINE_TUNE_CTRL_REG_1, regData);

  }
#endif

#ifdef MXL661_CUSTOMER_SPECIFIC_SETTING_2
  if ((tuneParamPtr->SignalMode <= MXL661_ANA_SECAM_L) && (tuneParamPtr->TuneType == MXL661_VIEW_MODE))
  {
    status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, PAGE_CHANGE_REG, 1);

    status |= MxLWare661_OEM_ReadRegister(tuneParamPtr->I2cSlaveAddr, DIG_ANA_GINJO_LT_REG, &regData);
    if (tuneParamPtr->FreqInHz >= APP_MODE_FREQ_HZ_THRESHOLD_1)
      regData |= 0x10; // Bit<4> = 1
    else
      regData &= 0xEF; // Bit<4> = 0
    status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, DIG_ANA_GINJO_LT_REG, regData);
    status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, PAGE_CHANGE_REG, 0);

    if (tuneParamPtr->FreqInHz >= APP_MODE_FREQ_HZ_THRESHOLD_1)
      status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, FINE_TUNE_INIT1_REG, 0x26);
    else
      status |= MxLWare661_OEM_WriteRegister(tuneParamPtr->I2cSlaveAddr, FINE_TUNE_INIT1_REG, 0x48);
  }
#endif
  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_ConfigSpurShiftAdjustment -
--|                                                MXL661_TUNER_SPUR_SHIFT_ADJ_CFG
--|
--| AUTHOR        : Mahee
--|
--| DATE CREATED  : 11/22/2011
--|                 12/20/2011
--|
--| DESCRIPTION   : This API configures MxL661 to move spurs caused by digital clock
--|                 out of band by adjusting digital clock frequency. The clock
--|                 frequency  adjustment value should be from 205 & 227.
--|                 Apply sequencer settings after updating registers.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

static MXL_STATUS MxL661_ConfigSpurShiftAdjustment(PMXL661_SPUR_SHIFT_ADJ_CFG_T spurShiftAdjPtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 regData = 0;

  MxL_DLL_DEBUG0("MXL661_TUNER_SPUR_SHIFT_ADJ_CFG, Clock freq adjustment value = %d\n",
                                            spurShiftAdjPtr->SpurShiftingClkAdjValue);

  /* Check for spur shift clock adjustment value.
     The value should be greater than 205 & less than 227 */
  if ((spurShiftAdjPtr->SpurShiftingClkAdjValue >= SPUR_SHIFT_CLOCK_ADJUST_MIN) &&
      (spurShiftAdjPtr->SpurShiftingClkAdjValue <= SPUR_SHIFT_CLOCK_ADJUST_MAX))
  {
    status |= MxLWare661_OEM_ReadRegister(spurShiftAdjPtr->I2cSlaveAddr, 0xEA, &regData);
    regData |= 0x20;
    status |= MxLWare661_OEM_WriteRegister(spurShiftAdjPtr->I2cSlaveAddr, 0xEA, regData);

    status |= MxLWare661_OEM_WriteRegister(spurShiftAdjPtr->I2cSlaveAddr,
                                 0xEB,
                                 spurShiftAdjPtr->SpurShiftingClkAdjValue);

    status |= MxLWare661_OEM_WriteRegister(spurShiftAdjPtr->I2cSlaveAddr, START_TUNE_REG, 0x00);
    status |= MxLWare661_OEM_WriteRegister(spurShiftAdjPtr->I2cSlaveAddr, START_TUNE_REG, 0x01);

  }
  else status = MXL_FALSE;

  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_ConfigHlfrfSettings -
--|                                     MXL661_TUNER_HLFRF_CFG
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

static MXL_STATUS MxL661_ConfigHlfrfSettings(PMXL661_HLFRF_CFG_T hlfrfCfgPtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 regData0 = 0;
  UINT8 regData1 = 0;

  MxL_DLL_DEBUG0("MXL661_TUNER_HLFRF_CFG\n");

  status |= MxLWare661_OEM_WriteRegister(hlfrfCfgPtr->I2cSlaveAddr, PAGE_CHANGE_REG, 0x01);
  status |= MxLWare661_OEM_ReadRegister(hlfrfCfgPtr->I2cSlaveAddr, DIG_ANA_GINJO_LT_REG, &regData0);

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

  status |= MxLWare661_OEM_WriteRegister(hlfrfCfgPtr->I2cSlaveAddr, DIG_ANA_GINJO_LT_REG, regData0);
  status |= MxLWare661_OEM_WriteRegister(hlfrfCfgPtr->I2cSlaveAddr, PAGE_CHANGE_REG, 0x00);

  status |= MxLWare661_OEM_WriteRegister(hlfrfCfgPtr->I2cSlaveAddr, 0xA9, regData1);

  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_ConfigTunerAfc -
--|                                     MXL661_TUNER_AFC_CFG
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

static MXL_STATUS MxL661_ConfigTunerAfc(PMXL661_TUNER_AFC_CFG_T afcCfgPtr)
{
  UINT32 u32FreqOffsetKHz, u32AfcRegWriteVal;
  UINT8  highByte, lowByte=0;//fix coverity 90929
  UINT8 status = MXL_TRUE;

  MxL_DLL_DEBUG0("MXL661_TUNER_HLFRF_CFG\n");

  u32FreqOffsetKHz = (UINT32)afcCfgPtr->AfcRangeInKHz;
 	if (u32FreqOffsetKHz == MXL661_AFC_DISABLE)
	 {
	   // Disable AFC , program 0x13<2> to 1
    status = MxLWare661_OEM_ReadRegister(afcCfgPtr->I2cSlaveAddr, FINE_TUNE_SET_REG, &lowByte);
	   lowByte |= 0x04;
	   status |= MxLWare661_OEM_WriteRegister(afcCfgPtr->I2cSlaveAddr, FINE_TUNE_SET_REG, lowByte);
	 }
	 else
	 {
	   status = MxLWare661_OEM_ReadRegister(afcCfgPtr->I2cSlaveAddr, FINE_TUNE_SET_REG, &lowByte);
	   if ((lowByte & 0x04) == 0x04)  // Bit<2> = 1
	   {
	     lowByte &= 0xFB;  // Bit<2> = 0, enable AFC
	     status |= MxLWare661_OEM_WriteRegister(afcCfgPtr->I2cSlaveAddr, FINE_TUNE_SET_REG, lowByte);
	   }
	   u32AfcRegWriteVal = u32FreqOffsetKHz * 1000 / 824 ;
	   highByte = (u32AfcRegWriteVal >> 8 ) & 0x03;
	   lowByte =  (u32AfcRegWriteVal & 0xFF);
	   status |= MxLWare661_OEM_WriteRegister(afcCfgPtr->I2cSlaveAddr, AFC_RANGE_SET_HIGH_REG, highByte);
	   status |= MxLWare661_OEM_WriteRegister(afcCfgPtr->I2cSlaveAddr, AFC_RANGE_SET_LOW_REG, lowByte);
  }

  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_ConfigTunerBalunless - MXL661_TUNER_BALUNLESS_CFG
--|
--| AUTHOR        : Joy Zhang
--|
--| DATE CREATED  : 07/11/2013
--|
--| DESCRIPTION   : This API compensates the unbalanced signal effect at low VHF
--|                 when tuner works at Balunless configuration.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

static MXL_STATUS MxL661_ConfigTunerBalunless(PMXL661_TUNER_BALUNLESS_CFG_T balunlessCfgPtr)
{
    UINT8 status = MXL_TRUE;
    UINT8 regData=0;//fix coverity 90932

    MxL_DLL_DEBUG0("MXL661_TUNER_BALUNLESS_CFG\n");

    if (balunlessCfgPtr->SignalMode < MXL661_DIG_DVB_C)
    {
        status |= MxLWare661_OEM_ReadRegister(balunlessCfgPtr->I2cSlaveAddr, DFE_AGC_TOPMAXRF_REG, &regData);
        if(regData != 0x1E)
          status |= MxLWare661_OEM_WriteRegister(balunlessCfgPtr->I2cSlaveAddr, DFE_AGC_TOPMAXRF_REG, 0x1E);

        if((balunlessCfgPtr->EnableHPF == MXL_ENABLE) && (balunlessCfgPtr->EnableLPF == MXL_ENABLE))
		{
            MxL_DLL_DEBUG0("[INVALID PARAMETER]HPF and LPF cannot be enabled at the same time \n");
			return MXL_INVALID_PARAMETER;
		}

        status |= MxLWare661_OEM_ReadRegister(balunlessCfgPtr->I2cSlaveAddr, CHIP_VERSION_REQ_REG, &regData);
        if(regData != 0x4)
            MxL_DLL_DEBUG0("This version chip doesn't support HPF and LPF config \n");
        else
        {
        	status |= MxLWare661_OEM_ReadRegister(balunlessCfgPtr->I2cSlaveAddr, HPF_CTRL_REG, &regData);
        	if(balunlessCfgPtr->EnableHPF == MXL_ENABLE)  // If enable HPF, then do the below flow
        		regData |= 0x04;
        	else
        		regData &= 0xFB;
        	status |= MxLWare661_OEM_WriteRegister(balunlessCfgPtr->I2cSlaveAddr, HPF_CTRL_REG, regData);


        	status |= MxLWare661_OEM_ReadRegister(balunlessCfgPtr->I2cSlaveAddr, LPF_CTRL_REG, &regData);
        	if(balunlessCfgPtr->EnableLPF == MXL_ENABLE)  // If enable LPF, then do the below flow
        		regData |= 0x08;
        	else
        		regData &= 0xF7;
      		status |= MxLWare661_OEM_WriteRegister(balunlessCfgPtr->I2cSlaveAddr, LPF_CTRL_REG, regData);
        }
    }

  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_ConfigTunerAtvDelay - MXL661_TUNER_ATV_DELAY_CFG
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 04/04/2013
--|
--| DESCRIPTION   : This API insert delay time in tuner output signal path.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

static MXL_STATUS MxL661_ConfigTunerAtvDelay(PMXL661_TUNER_ATV_DELAY_CFG_T atvDelayCfgPtr)
{
  UINT32 tmpData;
  UINT16 delayTimeInOneTenthUs;
  UINT16 delayPrecisionInNs;
  UINT8 status = MXL_TRUE;
  UINT8 regData=0;//fix coverity 90930

  MxL_DLL_DEBUG0("MXL661_TUNER_ATV_DELAY_CFG\n");

  status |= MxLWare661_OEM_ReadRegister(atvDelayCfgPtr->I2cSlaveAddr, CHIP_VERSION_REQ_REG, &regData);
  if((regData & 0xFF) != 0x4)
  {
    MxL_DLL_DEBUG0("This version chip doesn't support ATV delay time function \n");
    return MXL_NOT_SUPPORTED;
  }

  delayTimeInOneTenthUs = atvDelayCfgPtr->DelayTimeInOneTenthUs;
  delayPrecisionInNs = 148; // Default value 0.148us for chip

  tmpData = delayPrecisionInNs;
  // Check if delay time is big than maximun
  if (delayTimeInOneTenthUs >= (tmpData * 511 / 100))
  {
    MxL_DLL_DEBUG0("Warning: Invalid parameter, delayTimeInOneTenthUs = %d \n", delayTimeInOneTenthUs);
    delayTimeInOneTenthUs = (UINT16)(tmpData * 511 / 100);
  }
  else if (delayTimeInOneTenthUs <= 0)
    delayTimeInOneTenthUs = 0;

  regData = delayTimeInOneTenthUs/10; // Change to us value
  MxL_DLL_DEBUG0("delay time = %d.%d us, one step precision = %d ns \n", \
                  regData, delayTimeInOneTenthUs - regData * 10, delayPrecisionInNs);

  tmpData = delayTimeInOneTenthUs;
  tmpData = tmpData * 100 + delayPrecisionInNs / 2; // round operation

  regData = (UINT8)((tmpData / delayPrecisionInNs) & 0xFF);
  status = MxLWare661_OEM_WriteRegister(atvDelayCfgPtr->I2cSlaveAddr, DFE_DP_DELAY_LOW_REG, regData);

  regData = (UINT8)(((tmpData / delayPrecisionInNs) >> 8) & 0x01);
  status |= MxLWare661_OEM_WriteRegister(atvDelayCfgPtr->I2cSlaveAddr, DFE_DP_DELAY_HIGH_REG, regData);

  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_GetTunerSignalType - MXL661_TUNER_SIGNAL_TYPE_REQ
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

static MXL_STATUS MxL661_GetTunerSignalType(PMXL661_SIGNAL_TYPE_T tuneSigTypePtr)
{
  MXL_STATUS status = MXL_TRUE;
  UINT8 regData = 0;

  status = MxLWare661_OEM_ReadRegister(tuneSigTypePtr->I2cSlaveAddr, SIGNAL_TYPE_REG, &regData);

  // Signal type
  if ((regData & 0x10) == 0x10) tuneSigTypePtr->SignalMode = MXL661_SIGNAL_TYPE_ANALOG;
  else tuneSigTypePtr->SignalMode = MXL661_SIGNAL_TYPE_DIGITAL;

  return status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_GetTunerLockStatus - MXL661_TUNER_LOCK_STATUS_REQ
--|
--| AUTHOR        : Dong Liu
--|                 Sunghoon Park
--|
--| DATE CREATED  : 6/21/2011
--|                 6/24/2011
--|
--| DESCRIPTION   : This function returns Tuner Lock status of MxL661 tuner.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

static MXL_STATUS MxL661_GetTunerLockStatus(PMXL661_TUNER_LOCK_STATUS_T tunerLockStatusPtr)
{
  MXL_STATUS status = MXL_TRUE;
  UINT8 regData = 0;
  MXL_BOOL rfSynthStatus = MXL_UNLOCKED;
  MXL_BOOL refSynthStatus = MXL_UNLOCKED;

  MxL_DLL_DEBUG0("MXL661_TUNER_LOCK_STATUS_REQ \n");

  status = MxLWare661_OEM_ReadRegister(tunerLockStatusPtr->I2cSlaveAddr, RF_REF_STATUS_REG, &regData);

  if ((regData & 0x01) == 0x01) refSynthStatus = MXL_LOCKED;

  if ((regData & 0x02) == 0x02) rfSynthStatus = MXL_LOCKED;

  MxL_DLL_DEBUG0(" RfSynthStatus = %d, RefSynthStatus = %d",
                                    (UINT8)rfSynthStatus,(UINT8)refSynthStatus);

  tunerLockStatusPtr->RfSynLock =  rfSynthStatus;
  tunerLockStatusPtr->RefSynLock = refSynthStatus;

  return status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_GetTunerAgcLockStatus - MXL661_TUNER_AGC_LOCK_REQ
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 10/12/2011
--|
--| DESCRIPTION   : This function returns AGC Lock status of MxL661 tuner.
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

static MXL_STATUS MxL661_GetTunerAgcLockStatus(PMXL661_TUNER_AGC_LOCK_T agcLockStatusPtr)
{
  MXL_STATUS status = MXL_FALSE;
  UINT8 regData = 0;
  MXL_BOOL lockStatus = MXL_UNLOCKED;

  MxL_DLL_DEBUG0("MXL661_TUNER_AGC_LOCK_REQ \n");

  status = MxLWare661_OEM_ReadRegister(agcLockStatusPtr->I2cSlaveAddr, AGC_SAGCLOCK_STATUS_REG, &regData);

  // Bit<3>
  if ((regData & 0x08) == 0x08) lockStatus = MXL_LOCKED;

  MxL_DLL_DEBUG0(" Agc lock = %d", (UINT8)lockStatus);

  agcLockStatusPtr->AgcLock =  lockStatus;

  return status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_GetTunerRxPower - MXL661_TUNER_RX_PWR_REQ
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

static MXL_STATUS MxL661_GetTunerRxPower(PMXL661_TUNER_RX_PWR_T rxPwrPtr)
{
  UINT8 status = MXL_TRUE;
  UINT8 regData = 0;
  UINT16 tmpData = 0;

  MxL_DLL_DEBUG0("MXL661_TUNER_RX_PWR_REQ \n");

  // RF input power low <7:0>
  status = MxLWare661_OEM_ReadRegister(rxPwrPtr->I2cSlaveAddr, RFPIN_RB_LOW_REG, &regData);
  tmpData = regData;

  // RF input power high <1:0>
  status |= MxLWare661_OEM_ReadRegister(rxPwrPtr->I2cSlaveAddr, RFPIN_RB_HIGH_REG, &regData);
  tmpData |= (regData & 0x03) << 8;

  rxPwrPtr->RxPwr = (tmpData & 0x01FF)*25;  //100 times dBm

  if (tmpData & 0x02) rxPwrPtr->RxPwr += 50;
  if (tmpData & 0x01) rxPwrPtr->RxPwr += 25;
  if (tmpData & 0x0200) rxPwrPtr->RxPwr -= 128*100;

  MxL_DLL_DEBUG0(" Rx power = %d times 0.01dBm \n", rxPwrPtr->RxPwr);

  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_GetTunerAfcCorrection - MXL661_TUNER_AFC_CORRECTION_REQ
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

static MXL_STATUS MxL661_GetTunerAfcCorrection(PMXL661_TUNER_AFC_CORRECTION_T afcCorrectionPtr)
{
  UINT32 tmpData = 0;
  UINT8 status = MXL_TRUE;
  UINT8 regData = 0;
  UINT8 regData2 = 0;
  UINT8 regData3 = 0;
  UINT8 afcLock = 0;

  MxL_DLL_DEBUG0("MXL661_TUNER_AFC_CORRECTION_REQ \n");

  status |= MxLWare661_OEM_ReadRegister(afcCorrectionPtr->I2cSlaveAddr, RFPIN_RB_HIGH_REG, &regData);
  afcLock = (regData & 0x10) >> 4;

  // AFC offset correction readback <7:0> correponding to bit<7:0>
  status |= MxLWare661_OEM_ReadRegister(afcCorrectionPtr->I2cSlaveAddr, DFE_CTRL_ACCUM_LOW_REG, &regData);

  // AFC offset correction readback <15:8> correponding to bit<7:0>
  status |= MxLWare661_OEM_ReadRegister(afcCorrectionPtr->I2cSlaveAddr, DFE_CTRL_ACCUM_MID_REG, &regData2);

  // AFC offset correction readback <17:16> correponding to bit<1:0>
  status |= MxLWare661_OEM_ReadRegister(afcCorrectionPtr->I2cSlaveAddr, DFE_CTRL_ACCUM_HI_REG, &regData3);

  tmpData = regData3 & 0x03;
  tmpData = (tmpData << 8) + regData2;
  tmpData = (tmpData << 8) + regData;

  if ((afcLock == 0) && (tmpData == 0))
  {
    // MxL661 AFC could not find peak
	  status = MXL_FALSE;
    MxL_DLL_DEBUG0(" Can not find peak \n");
  }
  else
  {
    // Check if return data is negative number
    if (tmpData & 0x020000)  // Bit<17> = 1
      afcCorrectionPtr->AfcOffsetKHz = ((tmpData - 262144) * 1000) >> 16;
    else
      afcCorrectionPtr->AfcOffsetKHz =  (tmpData * 1000) >> 16;

    MxL_DLL_DEBUG0(" AFC correction = %d kHz \n", afcCorrectionPtr->AfcOffsetKHz);
  }

  return (MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_GetTunerAtvDelay - MXL661_TUNER_ATV_DELAY_REQ
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 04/17/2013
--|
--| DESCRIPTION   : This function returns ATV output delay time, unit is us
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

static MXL_STATUS MxL661_GetTunerAtvDelay(PMXL661_TUNER_ATV_DELAY_CFG_T atvDelayInfoPtr)
{
  UINT32 tmpData = 0;
  UINT16 delayPrecisionInNs;
  UINT8 status = MXL_TRUE;
  UINT8 readData=0;//fix coverity 90933

  MxL_DLL_DEBUG0("MXL661_TUNER_ATV_DELAY_REQ \n");

  status |= MxLWare661_OEM_ReadRegister(atvDelayInfoPtr->I2cSlaveAddr, DFE_DP_DELAY_HIGH_REG, &readData);
  tmpData = readData & 0x01;

  status |= MxLWare661_OEM_ReadRegister(atvDelayInfoPtr->I2cSlaveAddr, DFE_DP_DELAY_LOW_REG, &readData);
  tmpData = (tmpData << 8) + (readData & 0xFF);  // tmpData is 9bit value

  delayPrecisionInNs = 148; // Default value 0.148us for chip

  tmpData = (tmpData * delayPrecisionInNs) / 100;  // unit is 0.1us
  if ((MXL_STATUS)status == MXL_TRUE)
    atvDelayInfoPtr->DelayTimeInOneTenthUs = (UINT16)tmpData;
  else atvDelayInfoPtr->DelayTimeInOneTenthUs = 0; // default value

  return(MXL_STATUS)status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxL661_SetTeletextSpurMitigationAlgo -
--|                                                 MXL661_TUNER_TELETEXT_SPUR_CFG
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
#ifdef MXL661_ENABLE_TELETEXT_SPUR_FEATURE
static MXL_STATUS MxL661_SetTeletextSpurMitigation(PMXL661_TELETEXT_SPUR_CFG_T teletextSpurCfgPtr)
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

  MxL_DLL_DEBUG0("MXL661_TUNER_TELETEXT_SPUR_CFG \n");

  if (dcCalSamplePeriod == 0) dcCalSamplePeriod = 20;
  if (numOfDCCalSamples == 0) numOfDCCalSamples = 50;
  if (Sthreshold == 0) Sthreshold = 0.3;
  if (teletextSpurCfgPtr->initialTimeDelay  == 0) teletextSpurCfgPtr->initialTimeDelay = 500;

  MxL_DLL_DEBUG0("DC CAL Sample Interval = %d ms \n", dcCalSamplePeriod);
  MxL_DLL_DEBUG0("DC Number of DC CAL Samples = %d \n", numOfDCCalSamples);
  MxL_DLL_DEBUG0("DC CAL threshold = %lf ms \n", Sthreshold);

    // Program FDC BW = 20 Hz
  status |= MxLWare661_OEM_WriteRegister(teletextSpurCfgPtr->I2cSlaveAddr, DFE_FDC_IIR0_1, 0x77);
  status |= MxLWare661_OEM_WriteRegister(teletextSpurCfgPtr->I2cSlaveAddr, DFE_FDC_IIR2_3, 0x77);

  MxL_DLL_DEBUG0("%d ms delay....", teletextSpurCfgPtr->initialTimeDelay);
  MxLWare661_OEM_Sleep((UINT16)teletextSpurCfgPtr->initialTimeDelay);

  // Read DC CAL word
  for (idx = 0; idx < numOfDCCalSamples; idx++)
  {
    // Change Page to 0
    status = MxLWare661_OEM_WriteRegister(teletextSpurCfgPtr->I2cSlaveAddr, 0x00, 0x01);

    // Read dfe_fdc_offset_i
    status |= MxLWare661_OEM_ReadRegister(teletextSpurCfgPtr->I2cSlaveAddr, DFE_FDC_OFFSET_I_LSB, &regData);
    dcCalWordi = (regData & 0xFF);

    status |= MxLWare661_OEM_ReadRegister(teletextSpurCfgPtr->I2cSlaveAddr, DFE_FDC_OFFSET_I_MSB, &regData);
    dcCalWordi |= ((regData & 0x7F) << 8);

    Si = MxL661_GetTunerSignedBits(dcCalWordi, 1, 15, 4);

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
    status |= MxLWare661_OEM_ReadRegister(teletextSpurCfgPtr->I2cSlaveAddr, DFE_FDC_OFFSET_Q_LSB, &regData);
    dcCalWordq = (regData & 0xFF);

    status |= MxLWare661_OEM_ReadRegister(teletextSpurCfgPtr->I2cSlaveAddr, DFE_FDC_OFFSET_Q_MSB, &regData);
    dcCalWordq |= ((regData & 0x7F) << 8);

    Sq = MxL661_GetTunerSignedBits(dcCalWordq, 1, 15, 4);

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
    status |= MxLWare661_OEM_WriteRegister(teletextSpurCfgPtr->I2cSlaveAddr, 0x00, 0x00);

    // wait for next sample interval
    MxL_DLL_DEBUG0("%d ms delay....", dcCalSamplePeriod);
    MxLWare661_OEM_Sleep(dcCalSamplePeriod);
  }

  MxL_DLL_DEBUG0("Max Si = %lf \n", maxSi);
  MxL_DLL_DEBUG0("Min Si = %lf \n", minSi);
  MxL_DLL_DEBUG0("DELTA Si = %lf \n", (maxSi - minSi));

  MxL_DLL_DEBUG0("Max Sq = %lf \n", maxSq);
  MxL_DLL_DEBUG0("Min Sq = %lf \n", minSq);
  MxL_DLL_DEBUG0("DELTA Sq = %lf \n", (maxSq - minSq));

  // Calculate Variance Si
  SiVariance = MxL661_CalculateVariance(dcCal_i, numOfDCCalSamples);

  // Calculate Variance Sq
  SqVariance = MxL661_CalculateVariance(dcCal_q, numOfDCCalSamples);

  MxL_DLL_DEBUG0("Si Variance = %lf \n", SiVariance);
  MxL_DLL_DEBUG0("Sq Variance = %lf \n", SqVariance);


  if (((maxSi - minSi) >= Sthreshold) || ((maxSq - minSq) >= Sthreshold))
  {
    status |= MXL_SUCCESS;
  }
  else
  {
    // Program FDC BW = 251 Hz
    status |= MxLWare661_OEM_WriteRegister(teletextSpurCfgPtr->I2cSlaveAddr, DFE_FDC_IIR0_1, 0x56);
    status |= MxLWare661_OEM_WriteRegister(teletextSpurCfgPtr->I2cSlaveAddr, DFE_FDC_IIR2_3, 0x44);
  }

  return (MXL_STATUS)status;
}
#endif
/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxLWare661_API_ConfigDevice
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

MXL_STATUS MxLWare661_API_ConfigDevice(MXL661_COMMAND_T *ParamPtr)
{
  MXL_STATUS status = MXL_TRUE;
  MXL661_CMD_TYPE_E cmdType;

  if (ParamPtr == NULL) return MXL_FALSE;

  cmdType = ParamPtr->commandId;

  MxL_DLL_DEBUG0("MxLWare661_API_ConfigDevice : cmdType = %d", cmdType);

  switch (cmdType)
  {
    case MXL661_DEV_SOFT_RESET_CFG:
      status = MxL661_ConfigDevReset(&ParamPtr->MxLIf.cmdResetCfg);
      break;

    case MXL661_DEV_OVERWRITE_DEFAULT_CFG:
      status = MxL661_ConfigDevOverwriteDefault(&ParamPtr->MxLIf.cmdOverwriteDefault);
      break;

    case MXL661_DEV_XTAL_SET_CFG:
      status = MxL661_ConfigDevXtalSet(&ParamPtr->MxLIf.cmdXtalCfg);
      break;

    case MXL661_DEV_POWER_MODE_CFG:
      status = MxL661_ConfigDevPowerMode(&ParamPtr->MxLIf.cmdPwrModeCfg);
      break;

    case MXL661_DEV_IF_OUT_CFG:
      status = MxL661_ConfigDevIfOutSet(&ParamPtr->MxLIf.cmdIfOutCfg);
      break;

    case MXL661_DEV_GPO_CFG:
      status = MxL661_ConfigDevGPO(&ParamPtr->MxLIf.cmdGpoCfg);
      break;

    default:
      status = MXL_FALSE;
      break;
  }

  return status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxLWare661_API_GetDeviceStatus
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

MXL_STATUS MxLWare661_API_GetDeviceStatus(MXL661_COMMAND_T *ParamPtr)
{
  MXL_STATUS status = MXL_TRUE;
  MXL661_CMD_TYPE_E cmdType;

  if (ParamPtr == NULL) return MXL_FALSE;

  cmdType = ParamPtr->commandId;

  MxL_DLL_DEBUG0("MxLWare661_API_GetDeviceStatus : cmdType = %d", cmdType);

  switch (cmdType)
  {
    case MXL661_DEV_ID_VERSION_REQ:
      status = MxL661_GetDeviceInfo(&ParamPtr->MxLIf.cmdDevInfoReq);
      break;

    case MXL661_DEV_GPO_STATE_REQ:
      status = MxL661_GetDeviceGpoState(&ParamPtr->MxLIf.cmdGpoReq);
      break;

    case MXL661_DEV_PLL_STATE_REQ:
      status = MxL661_GetDevicePllState(&ParamPtr->MxLIf.cmdPllReq);
      break;

    default:
      status = MXL_FALSE;
      break;
  }

  return status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxLWare661_API_ConfigTuner
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 04/04/2013
--|
--| DESCRIPTION   : The tuner block specific configuration shall be handled
--|                 through this API
--|
--| RETURN VALUE  : MXL_TRUE or MXL_FALSE
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxLWare661_API_ConfigTuner(MXL661_COMMAND_T *ParamPtr)
{
  MXL_STATUS status = MXL_TRUE;
  MXL661_CMD_TYPE_E cmdType;

  if (ParamPtr == NULL) return MXL_FALSE;

  cmdType = ParamPtr->commandId;

  MxL_DLL_DEBUG0("MxLWare661_API_ConfigTuner : cmdType =%d", cmdType);

  switch (cmdType)
  {
    case MXL661_TUNER_POWER_UP_CFG:
      status = MxL661_ConfigTunerPowerUp(&ParamPtr->MxLIf.cmdTunerPoweUpCfg);
      break;

    case MXL661_TUNER_START_TUNE_CFG:
      status = MxL661_ConfigTunerSequenceSet(&ParamPtr->MxLIf.cmdStartTuneCfg);
      break;

    case MXL661_TUNER_MODE_CFG:
      status = MxL661_ConfigTunerApplicationModeSet(&ParamPtr->MxLIf.cmdModeCfg);
      break;

    case MXL661_TUNER_AGC_CFG:
      status = MxL661_ConfigTunerAgcSet(&ParamPtr->MxLIf.cmdAgcSetCfg);
      break;

    case MXL661_TUNER_FINE_TUNE_CFG:
      status = MxL661_ConfigTunerFineTune(&ParamPtr->MxLIf.cmdFineTuneCfg);
      break;

    case MXL661_TUNER_ENABLE_FINE_TUNE_CFG:
      status = MxL661_ConfigTunerEnableFineTune(&ParamPtr->MxLIf.cmdEnableFineTuneCfg);
      break;

    case MXL661_TUNER_CHAN_TUNE_CFG:
      status = MxL661_ConfigTunerChanTune(&ParamPtr->MxLIf.cmdChanTuneCfg);
      break;

    case MXL661_TUNER_SPUR_SHIFT_ADJ_CFG:
      status = MxL661_ConfigSpurShiftAdjustment(&ParamPtr->MxLIf.cmdSuprShiftAdjCfg);
      break;

    case MXL661_TUNER_HLFRF_CFG:
      status = MxL661_ConfigHlfrfSettings(&ParamPtr->MxLIf.cmdHlfrfCfg);
      break;

    case MXL661_TUNER_AFC_CFG:
      status = MxL661_ConfigTunerAfc(&ParamPtr->MxLIf.cmdAfcCfg);
      break;

#ifdef MXL661_ENABLE_TELETEXT_SPUR_FEATURE
    case MXL661_TUNER_TELETEXT_SPUR_CFG:
      status = MxL661_SetTeletextSpurMitigation(&ParamPtr->MxLIf.cmdTeletextSpurCfg);
      break;
#endif

    case MXL661_TUNER_BALUNLESS_CFG:
      status = MxL661_ConfigTunerBalunless(&ParamPtr->MxLIf.cmdBalunlessCfg);
      break;

    case MXL661_TUNER_ATV_DELAY_CFG:
      status = MxL661_ConfigTunerAtvDelay(&ParamPtr->MxLIf.cmdAtvDelayCfg);
      break;

    case MXL661_TUNER_HPF_LPF_CFG:
      status = MxL661_ConfigTunerAtvHpfLpf(&ParamPtr->MxLIf.cmdTunerAtvFilterCfg);
      break;

    default:
      status = MXL_FALSE;
      break;
  }
  return status;
}

/*--------------------------------------------------------------------------------
--| FUNCTION NAME : MxLWare661_API_GetTunerStatus
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

MXL_STATUS MxLWare661_API_GetTunerStatus(MXL661_COMMAND_T *ParamPtr)
{
  MXL_STATUS status;
  MXL661_CMD_TYPE_E cmdType;

  if (ParamPtr == NULL) return MXL_FALSE;

  cmdType = ParamPtr->commandId;

  MxL_DLL_DEBUG0("MxLWare661_API_GetTunerStatus : cmdType = %d", cmdType);

  switch (cmdType)
  {
    case MXL661_TUNER_SIGNAL_TYPE_REQ:
      status = MxL661_GetTunerSignalType(&ParamPtr->MxLIf.cmdTunerSignalTypeReq);
      break;

    case MXL661_TUNER_LOCK_STATUS_REQ:
      status = MxL661_GetTunerLockStatus(&ParamPtr->MxLIf.cmdTunerLockReq);
      break;

    case MXL661_TUNER_AGC_LOCK_REQ:
      status = MxL661_GetTunerAgcLockStatus(&ParamPtr->MxLIf.cmdTunerAgcLockReq);
      break;

    case MXL661_TUNER_RX_PWR_REQ:
      status = MxL661_GetTunerRxPower(&ParamPtr->MxLIf.cmdTunerPwrReq);
      break;

    case MXL661_TUNER_AFC_CORRECTION_REQ:
      status = MxL661_GetTunerAfcCorrection(&ParamPtr->MxLIf.cmdTunerAfcCorectionReq);
      break;

    case MXL661_TUNER_ATV_DELAY_REQ:
      status = MxL661_GetTunerAtvDelay(&ParamPtr->MxLIf.cmdAtvDelayCfg);
      break;

    default:
      status = MXL_FALSE;
      break;
  }

  return status;
}
