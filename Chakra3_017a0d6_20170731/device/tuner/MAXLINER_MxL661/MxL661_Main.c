#include <stdio.h>
#include "MxL661_TunerApi.h"
#include "MxL661_OEM_Drv.h"

#define MXL661_I2C_ADDR     0x60

#define MXL661_DEFAULT_SINGLE_POWER_SUPPLY  MXL_DISABLE   // Dual power supply
#if (MS_BOARD_TYPE_SEL == BD_MST094B_20ARJ_16234)
#define MXL661_DEFAULT_XTAL_FREQ_SEL        MXL661_XTAL_24MHz    // 24MHz
#else
#define MXL661_DEFAULT_XTAL_FREQ_SEL        MXL661_XTAL_16MHz    // 16MHz
#endif
#define MXL661_DEFAULT_XTAL_CAP             25            // 25 PF
#define MXL661_DEFAULT_XTAL_CLOCK_OUT       MXL_ENABLE    // Enable clock out
#define MXL661_DEFAULT_XTAL_CLOCK_DIV       MXL_DISABLE   // Disable clock div
#define MXL661_DEFAULT_IF_PATH              MXL661_IF_PATH2      // IF path 2
#define MXL661_DEFAULT_IF_FREQ_SEL          MXL661_IF_4MHz       // 4MHz
#define MXL661_DEFAULT_IF_INVERSION         MXL_ENABLE // IF spectrum inversion
#define MXL661_DEFAULT_IF_GAIN              11  // For digital range is 5 to 11
#define MXL661_DEFAULT_AGC_TYPE             MXL661_AGC_EXTERNAL  // External AGC
#define MXL661_DEFAULT_AGC_SEL              MXL661_AGC2          // Select AGC2
#define MXL661_DEFAULT_AGC_SET_POINT        66  // Default value for Self AGC

// Define MxL661 device power supply, Xtal, IF out and AGC setting
typedef struct
{

  MXL_BOOL Single_3_3_v_Supply; // Define Tuner is single 3.3v power supply or not.
  MXL661_XTAL_FREQ_E XtalFreqSel;  // XTAL frequency selection, either 16MHz or 24MHz
  UINT8 XtalCap;                // XTAL capacity
  MXL_BOOL XtalClkOut;          // XTAL clock out enable or disable
  MXL_BOOL XtalClkDiv;          // Define if clock out freq is divided by 4 or not
  UINT8 SignalMode;             // Tuner work mode, refers MXL_SIGNAL_MODE_E definition
  UINT8 BandWidth;              // signal band width in MHz unit
  UINT8 IFPath;                 // define which IF path is selected
  MXL661_IF_FREQ_E IFFreqSel;      // IF out signel frequency selection. Refers MXL661_IF_FREQ_E define.
  MXL_BOOL IFInversion;         // IF spectrum is inverted or not
  UINT8 IFGain;                 // IF out gain level
  MXL661_AGC_TYPE_E AgcType;       // AGC mode selection, self or closed loop
  MXL661_AGC_ID_E AgcSel;          // AGC selection, AGC1 or AGC2
  UINT8 AgcSetPoint;            // AGC attack point set value
} MXL661_CHARACTER_SET_T;

static MXL661_CHARACTER_SET_T MxL661_Default_Set =
{
  MXL661_DEFAULT_SINGLE_POWER_SUPPLY, // power supply type
  MXL661_DEFAULT_XTAL_FREQ_SEL,  // Xtal freq selection
  MXL661_DEFAULT_XTAL_CAP,       // Xtal cap
  MXL661_DEFAULT_XTAL_CLOCK_OUT, // clock out
  MXL661_DEFAULT_XTAL_CLOCK_DIV, // clock div
  MXL661_ANA_PAL_BG,  // PAL_BG
  8,  // 8MHz
  MXL661_DEFAULT_IF_PATH, // IF path
  MXL661_DEFAULT_IF_FREQ_SEL, // IF freq selection
  MXL661_DEFAULT_IF_INVERSION, // IF spectrum inversion
  MXL661_DEFAULT_IF_GAIN,  // IF gain
  MXL661_DEFAULT_AGC_TYPE, // AGC type, self or external
  MXL661_DEFAULT_AGC_SEL,  // AGC selection
  MXL661_DEFAULT_AGC_SET_POINT // AGC set point, effective for self AGC
};

void MxL661_API_Init(void)
{
  MXL_STATUS status;
  MXL661_COMMAND_T apiCmd;

  // Soft Reset MxL661
  apiCmd.commandId = MXL661_DEV_SOFT_RESET_CFG;
  apiCmd.MxLIf.cmdResetCfg.I2cSlaveAddr = MXL661_I2C_ADDR;
  status = MxLWare661_API_ConfigDevice(&apiCmd);

  // Overwrite Default
  apiCmd.commandId = MXL661_DEV_OVERWRITE_DEFAULT_CFG;
  apiCmd.MxLIf.cmdOverwriteDefault.I2cSlaveAddr = MXL661_I2C_ADDR;
  apiCmd.MxLIf.cmdOverwriteDefault.SingleSupply_3_3V = MxL661_Default_Set.Single_3_3_v_Supply;
  status = MxLWare661_API_ConfigDevice(&apiCmd);

  // Xtal Setting
  apiCmd.commandId = MXL661_DEV_XTAL_SET_CFG;
  apiCmd.MxLIf.cmdXtalCfg.I2cSlaveAddr = MXL661_I2C_ADDR;
  apiCmd.MxLIf.cmdXtalCfg.XtalFreqSel = MxL661_Default_Set.XtalFreqSel;
  apiCmd.MxLIf.cmdXtalCfg.XtalCap = MxL661_Default_Set.XtalCap;
  apiCmd.MxLIf.cmdXtalCfg.ClkOutEnable = MxL661_Default_Set.XtalClkOut;
  apiCmd.MxLIf.cmdXtalCfg.ClkOutDiv = MxL661_Default_Set.XtalClkDiv;
  apiCmd.MxLIf.cmdXtalCfg.SingleSupply_3_3V = MxL661_Default_Set.Single_3_3_v_Supply;
  status = MxLWare661_API_ConfigDevice(&apiCmd);

  // Power up setting
  apiCmd.commandId = MXL661_TUNER_POWER_UP_CFG;
  apiCmd.MxLIf.cmdTunerPoweUpCfg.I2cSlaveAddr = MXL661_I2C_ADDR;
  apiCmd.MxLIf.cmdTunerPoweUpCfg.Enable = MXL_ENABLE;
  status = MxLWare661_API_ConfigTuner(&apiCmd);
}

void MxL661_API_SetAppMode(UINT8 AppMode)
{
  MXL_STATUS status;
  MXL661_COMMAND_T apiCmd;
  UINT32 IFAbsFreqInKHz[] = {3650, 4000, 4100, 4150, 4500, 4570, 5000, 5380, 6000, 6280, 7200, 8250, 35250, 36000, 36150, 36650, 44000};

  // IF Out setting
  apiCmd.commandId = MXL661_DEV_IF_OUT_CFG;
  apiCmd.MxLIf.cmdIfOutCfg.I2cSlaveAddr = MXL661_I2C_ADDR;
  apiCmd.MxLIf.cmdIfOutCfg.IFOutFreq = MxL661_Default_Set.IFFreqSel;
  apiCmd.MxLIf.cmdIfOutCfg.IFInversion = MxL661_Default_Set.IFInversion;
  apiCmd.MxLIf.cmdIfOutCfg.GainLevel = MxL661_Default_Set.IFGain;
  apiCmd.MxLIf.cmdIfOutCfg.PathSel = MxL661_Default_Set.IFPath;
  apiCmd.MxLIf.cmdIfOutCfg.ManualFreqSet = MXL_DISABLE;
  apiCmd.MxLIf.cmdIfOutCfg.ManualIFOutFreqInKHz = 0;
  status = MxLWare661_API_ConfigDevice(&apiCmd);

  // AGC Setting
  apiCmd.commandId = MXL661_TUNER_AGC_CFG;
  apiCmd.MxLIf.cmdAgcSetCfg.I2cSlaveAddr = MXL661_I2C_ADDR;
  apiCmd.MxLIf.cmdAgcSetCfg.AgcSel = MxL661_Default_Set.AgcSel;
  apiCmd.MxLIf.cmdAgcSetCfg.AgcType = MxL661_Default_Set.AgcType;
  apiCmd.MxLIf.cmdAgcSetCfg.SetPoint = MxL661_Default_Set.AgcSetPoint;
  apiCmd.MxLIf.cmdAgcSetCfg.AgcPolarityInverstion = MXL_DISABLE;
  status = MxLWare661_API_ConfigTuner(&apiCmd);

  // Application Mode setting
  apiCmd.commandId = MXL661_TUNER_MODE_CFG;
  apiCmd.MxLIf.cmdModeCfg.I2cSlaveAddr = MXL661_I2C_ADDR;
  apiCmd.MxLIf.cmdModeCfg.SignalMode = (MXL661_SIGNAL_MODE_E)AppMode;
  apiCmd.MxLIf.cmdModeCfg.IFOutFreqinKHz = IFAbsFreqInKHz[MxL661_Default_Set.IFFreqSel];
  apiCmd.MxLIf.cmdModeCfg.XtalFreqSel = MxL661_Default_Set.XtalFreqSel;
  apiCmd.MxLIf.cmdModeCfg.IFOutGainLevel = MxL661_Default_Set.IFGain;
  status = MxLWare661_API_ConfigTuner(&apiCmd);

  MxL661_Default_Set.SignalMode = AppMode;
}

void MxL661_API_ChannelTune(UINT32 RfCenterFreqInHz, UINT8 BandWidthInMHz)
{
  MXL_STATUS status;
  MXL661_COMMAND_T apiCmd;
  MXL661_SIGNAL_MODE_E TunerAppMode;
  MXL661_BW_E bandWidth = MXL661_ANA_TV_DIG_CABLE_BW_8MHz;

  TunerAppMode = (MXL661_SIGNAL_MODE_E)MxL661_Default_Set.SignalMode;

  if (TunerAppMode <= MXL661_DIG_DVB_C)
  {
    switch(BandWidthInMHz)
    {
      case 6: bandWidth = MXL661_ANA_TV_DIG_CABLE_BW_6MHz; break;
      case 7: bandWidth = MXL661_ANA_TV_DIG_CABLE_BW_7MHz; break;
      case 8: bandWidth = MXL661_ANA_TV_DIG_CABLE_BW_8MHz; break;
      default: break;
    }
  }
  else
  {
    switch(BandWidthInMHz)
    {
      case 6: bandWidth = MXL661_DIG_TERR_BW_6MHz; break;
      case 7: bandWidth = MXL661_DIG_TERR_BW_7MHz; break;
      case 8: bandWidth = MXL661_DIG_TERR_BW_8MHz; break;
      default: break;
    }
  }
  // Channel frequency & bandwidth setting
  apiCmd.commandId = MXL661_TUNER_CHAN_TUNE_CFG;
  apiCmd.MxLIf.cmdChanTuneCfg.I2cSlaveAddr = MXL661_I2C_ADDR;
  apiCmd.MxLIf.cmdChanTuneCfg.TuneType = MXL661_VIEW_MODE;
  apiCmd.MxLIf.cmdChanTuneCfg.BandWidth = bandWidth;
  apiCmd.MxLIf.cmdChanTuneCfg.FreqInHz = RfCenterFreqInHz;
  apiCmd.MxLIf.cmdChanTuneCfg.SignalMode = TunerAppMode;
  apiCmd.MxLIf.cmdChanTuneCfg.XtalFreqSel = MxL661_Default_Set.XtalFreqSel;
  status = MxLWare661_API_ConfigTuner(&apiCmd);

  // Sequencer setting, disable tune
  apiCmd.commandId = MXL661_TUNER_START_TUNE_CFG;
  apiCmd.MxLIf.cmdStartTuneCfg.I2cSlaveAddr = MXL661_I2C_ADDR;
  apiCmd.MxLIf.cmdStartTuneCfg.StartTune = MXL_DISABLE;
  status = MxLWare661_API_ConfigTuner(&apiCmd);

  // Sequencer setting, enable tune
  apiCmd.commandId = MXL661_TUNER_START_TUNE_CFG;
  apiCmd.MxLIf.cmdStartTuneCfg.I2cSlaveAddr = MXL661_I2C_ADDR;
  apiCmd.MxLIf.cmdStartTuneCfg.StartTune = MXL_ENABLE;
  status = MxLWare661_API_ConfigTuner(&apiCmd);

  MxL661_Default_Set.BandWidth = BandWidthInMHz;
}

void MxL661_API_GetLockStatus(UINT8* RfLock, UINT8* RefLock)
{
  MXL661_COMMAND_T apiCmd;

  // Read back Tuner lock status
  apiCmd.commandId = MXL661_TUNER_LOCK_STATUS_REQ;
  apiCmd.MxLIf.cmdTunerLockReq.I2cSlaveAddr = MXL661_I2C_ADDR;

  if (MXL_TRUE == MxLWare661_API_GetTunerStatus(&apiCmd))
  {
	   *RfLock = apiCmd.MxLIf.cmdTunerLockReq.RfSynLock;
	   *RefLock = apiCmd.MxLIf.cmdTunerLockReq.RefSynLock;
  }
  return;
}

void MxL661_API_ATV_Finetune(MXL_BOOL ScaleUp )
{
  MXL_STATUS status;
  MXL661_COMMAND_T apiCmd;

  apiCmd.commandId = MXL661_TUNER_ENABLE_FINE_TUNE_CFG;
  apiCmd.MxLIf.cmdEnableFineTuneCfg.I2cSlaveAddr = MXL661_I2C_ADDR;
  apiCmd.MxLIf.cmdEnableFineTuneCfg.EnableFineTune  = MXL_ENABLE;
  status = MxLWare661_API_ConfigTuner(&apiCmd);
  if(status != MXL_TRUE)
    printf(" Enable Fine Tune status = %d\n",status);

  apiCmd.commandId = MXL661_TUNER_FINE_TUNE_CFG;
  apiCmd.MxLIf.cmdFineTuneCfg.I2cSlaveAddr = MXL661_I2C_ADDR;
  apiCmd.MxLIf.cmdFineTuneCfg.ScaleUp = ScaleUp;
  status = MxLWare661_API_ConfigTuner(&apiCmd);
  if(status != MXL_TRUE)
    printf("Fine Tune operation status = %d\n",status);

  return;
}

int main(void)
{
  UINT8 RfLock, RefLock;
  //If it needs the fine tune flow,please define and set the \
  //ScaleUp to MXL_FINE_TUNE_STEP_UP or MXL_FINE_TUNE_STEP_DOWN.
  //MXL_BOOL ScaleUp = MXL_FINE_TUNE_STEP_UP; //or MXL_FINE_TUNE_STEP_DOWN.

  // Here user can change MxL661 character setting in MxL661_Device_Default_Set
  // MxL661_Default_Set.Single_3_3_v_Supply =
  // MxL661_Default_Set.XtalFreqSel =
  // MxL661_Default_Set.XtalCap =
  // MxL661_Default_Set.XtalClkOut =
  // MxL661_Default_Set.XtalClkDiv =
  // MxL661_Default_Set.SignalMode =
  // MxL661_Default_Set.BandWidth =
  // MxL661_Default_Set.IFPath =
  // MxL661_Default_Set.IFFreqSel =
  // MxL661_Default_Set.IFInversion =
  // MxL661_Default_Set.IFGain =
  // MxL661_Default_Set.AgcType =
  // MxL661_Default_Set.AgcSel =
  // MxL661_Default_Set.AgcSetPoint =

  // Tuner initialization only need be called once.
  MxL661_API_Init();

  // Set appllication mode and related IF out, AGC setting parameters
  MxL661_API_SetAppMode(MXL661_ANA_PAL_BG);

  // Channel tune at certain frequency point
  MxL661_API_ChannelTune(530000000, 8);

  // Inquire Tuner lock status
  MxL661_API_GetLockStatus(&RfLock, &RefLock);
  if ((MXL_LOCKED == RfLock) && (MXL_LOCKED == RefLock))
    printf(" Tuner locked\n");
  else
    printf(" Tuner unlocked\n");

  //If it needs the fine tune flow, \
  //please use "Enable Fine tune" and "Fine tune" API like the below function.
  //MxL661_API_ATV_Finetune(ScaleUp);

}

