/*******************************************************************************
 *
 * FILE NAME          : MxL661_TunerApi.h
 * 
 * AUTHOR             : Sunghoon Park 
 *                      Dong Liu
 *
 * DATE CREATED       : 07/10/2011
 *                      05/23/2013
 *
 * DESCRIPTION        : This file is header file for MxL661_TunerApi.cpp 
 *
 *******************************************************************************
 *                Copyright (c) 2011, MaxLinear, Inc.
 ******************************************************************************/

#ifndef __MXL661_TUNER_API_H__
#define __MXL661_TUNER_API_H__

/******************************************************************************
    Include Header Files
    (No absolute paths - paths handled by make file)
******************************************************************************/

#include "MaxLinearDataTypes.h"
#include "MxL661_TunerCfg.h"

/******************************************************************************
    Macros
******************************************************************************/

#define  MXL661_VERSION_SIZE         4   
#define  MAX_MXL661_DEVICES       4  

//#define MXL661_CUSTOMER_SPECIFIC_SETTING_1
//#define MXL661_CUSTOMER_SPECIFIC_SETTING_2
/******************************************************************************
    User-Defined Types (Typedefs)
******************************************************************************/

/* Command Types  */
typedef enum
{ 
  // For API_ConfigDevice interface
  MXL661_DEV_SOFT_RESET_CFG = 0,
  MXL661_DEV_OVERWRITE_DEFAULT_CFG,
  MXL661_DEV_XTAL_SET_CFG,
  MXL661_DEV_POWER_MODE_CFG,
  MXL661_DEV_IF_OUT_CFG,
  MXL661_DEV_GPO_CFG,         

  // For API_GetDeviceStatus interface 
  MXL661_DEV_ID_VERSION_REQ,
  MXL661_DEV_GPO_STATE_REQ,             
  MXL661_DEV_PLL_STATE_REQ, 

  // For API_ConfigTuner interface
  MXL661_TUNER_MODE_CFG,
  MXL661_TUNER_POWER_UP_CFG,
  MXL661_TUNER_START_TUNE_CFG,
  MXL661_TUNER_AGC_CFG,
  MXL661_TUNER_CHAN_TUNE_CFG,
  MXL661_TUNER_SPUR_SHIFT_ADJ_CFG,
  MXL661_TUNER_FINE_TUNE_CFG,
  MXL661_TUNER_ENABLE_FINE_TUNE_CFG,
  MXL661_TUNER_HLFRF_CFG,
  MXL661_TUNER_AFC_CFG,
#ifdef MXL661_ENABLE_TELETEXT_SPUR_FEATURE  
  MXL661_TUNER_TELETEXT_SPUR_CFG,
#endif 
  MXL661_TUNER_BALUNLESS_CFG,
  MXL661_TUNER_ATV_DELAY_CFG,

  // For API_GetTunerStatus interface
  MXL661_TUNER_SIGNAL_TYPE_REQ,
  MXL661_TUNER_LOCK_STATUS_REQ, 
  MXL661_TUNER_AGC_LOCK_REQ, 
  MXL661_TUNER_RX_PWR_REQ,
  MXL661_TUNER_AFC_CORRECTION_REQ,
  MXL661_TUNER_ATV_DELAY_REQ,
  MXL661_TUNER_HPF_LPF_CFG,

  MXL661_MAX_NUM_COMMAND
} MXL661_CMD_TYPE_E;

/* MXL661_RESET_CFG_T  */
typedef struct
{
  UINT8 I2cSlaveAddr;           /* IN, I2C Address of MxL Device */
} MXL661_RESET_CFG_T, *PMXL661_RESET_CFG_T;

/* MXL661_OVERWRITE_DEFAULT_CFG_T */
typedef struct
{
  UINT8 I2cSlaveAddr;           /* IN, I2C Address of MxL Device */
  MXL_BOOL SingleSupply_3_3V;   /* IN, Single Supply 3.3v */
} MXL661_OVERWRITE_DEFAULT_CFG_T, *PMXL661_OVERWRITE_DEFAULT_CFG_T;

/* MXL661_DEV_XTAL_SET_CFG  */
typedef enum
{
  MXL661_XTAL_16MHz = 0,
  MXL661_XTAL_24MHz = 1,
  MXL661_XTAL_FREQ_NA = 99
} MXL661_XTAL_FREQ_E;

typedef struct
{
  UINT8 I2cSlaveAddr;           /* IN, I2C Address of MxL Device */
  MXL661_XTAL_FREQ_E XtalFreqSel;  /* IN, XTAL Frequency, refers above */
  UINT8 XtalCap;                /* IN, XTAL capacity, 1 LSB = 1pF, maximum is 31pF */
  MXL_BOOL ClkOutEnable;        /* IN, enable or disable clock out */
  MXL_BOOL ClkOutDiv;           /* IN, indicate if XTAL frequency is dived by 4 or not */
  MXL_BOOL SingleSupply_3_3V;   /* IN, Single Supply 3.3v */
  MXL_BOOL XtalSharingMode;     /* IN, XTAL sharing mode. default Master, MXL_ENABLE to config Slave mode */
} MXL661_XTAL_SET_CFG_T, *PMXL661_XTAL_SET_CFG_T;

/* MXL661_DEV_POWER_MODE_CFG  */
typedef enum
{
  MXL661_PWR_MODE_SLEEP = 0,
  MXL661_PWR_MODE_ACTIVE,
  MXL661_PWR_MODE_STANDBY
} MXL661_PWR_MODE_E;

typedef struct
{
  UINT8 I2cSlaveAddr;           /* IN, I2C Address of MxL Device */
  MXL661_PWR_MODE_E PowerMode;     /* IN, power saving mode */
} MXL661_PWR_MODE_CFG_T, *PMXL661_PWR_MODE_CFG_T;

/* MXL661_DEV_IF_OUT_CFG  */
typedef enum
{
  MXL661_IF_PATH1 = 1,
  MXL661_IF_PATH2 = 2
} MXL661_IF_PATH_E;

typedef enum
{
  MXL661_IF_3_65MHz  = 0,
  MXL661_IF_4MHz     = 1,
  MXL661_IF_4_1MHz   = 2,
  MXL661_IF_4_15MHz  = 3,
  MXL661_IF_4_5MHz   = 4, 
  MXL661_IF_4_57MHz  = 5,
  MXL661_IF_5MHz     = 6,
  MXL661_IF_5_38MHz  = 7, 
  MXL661_IF_6MHz     = 8,
  MXL661_IF_6_28MHz  = 9,
  MXL661_IF_7_2MHz   = 10, 
  MXL661_IF_8_25MHz  = 11,
  MXL661_IF_35_25MHz = 12,
  MXL661_IF_36MHz    = 13, 
  MXL661_IF_36_15MHz = 14, 
  MXL661_IF_36_65MHz = 15,
  MXL661_IF_44MHz    = 16,
  MXL661_IF_FREQ_NA  = 99
} MXL661_IF_FREQ_E;

typedef struct
{
  UINT8 I2cSlaveAddr;           /* IN, I2C Address of MxL Device */
  MXL661_IF_FREQ_E IFOutFreq;      /* IN, band width of IF out signal */
  UINT32 ManualIFOutFreqInKHz;  /* IN, IF out frequency selection when ManualIFOutCtrl = 0*/
  MXL_BOOL ManualFreqSet;       /* IN, IF out frequency is set by manual or not */
  MXL_BOOL IFInversion;         /* IN, IF spectrum is inverted or not */
  UINT8 GainLevel;              /* IN, IF out gain level */
  MXL661_IF_PATH_E PathSel;        /* IN, define which path is selected */
}MXL661_IF_OUT_CFG_T, *PMXL661_IF_OUT_CFG_T;

/* MXL661_DEV_GPO_CFG  */
typedef enum
{
  MXL661_GPO1 = 0,
  MXL661_GPO2 = 1,
  MXL661_GPO3 = 2
} MXL661_GPO_ID_E;

typedef enum
{
  MXL661_PORT_LOW = 0,
  MXL661_PORT_HIGH = 1,
  MXL661_PORT_AUTO_CTRL = 2
} MXL661_GPO_STATE_E;

typedef struct
{
  UINT8 I2cSlaveAddr;           /* IN, I2C Address of MxL Device */
  MXL661_GPO_ID_E GPOId;           /* IN, GPO port number. 0 for GPO0, 1 for GPO1, and 2 for GPO2 */
  MXL661_GPO_STATE_E GPOState;     /* IN, configuration. */
} MXL661_GPO_CFG_T, *PMXL661_GPO_CFG_T;

/* MXL661_DEV_ID_VERSION_REQ */
typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  UINT8 ChipId;                       /* OUT, Device chip ID information  */
  UINT8 ChipVersion;                  /* OUT, Device chip revision  */
  UINT8 MxLWareVer[MXL661_VERSION_SIZE]; /* OUT, MxLWare version information */    
} MXL661_DEV_INFO_T, *PMXL661_DEV_INFO_T;

/* MXL661_DEV_GPO_STATE_REQ  */
typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */   
  MXL661_GPO_STATE_E GPO1;               /* OUT, GPO0 status */
  MXL661_GPO_STATE_E GPO2;               /* OUT, GPO1 status */
  MXL661_GPO_STATE_E GPO3;               /* OUT, GPO2 status */        
} MXL661_GPO_INFO_T, *PMXL661_GPO_INFO_T;

/* MXL661_DEV_PLL_STATE_REQ  */
typedef enum
{
  MXL661_PLL_STATE_NORMAL = 0,
  MXL661_PLL_STATE_WRONG  = 1,
  MXL661_PLL_STATE_NA = 2
} MXL661_PLL_STATE_E;

typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */   
  MXL661_PLL_STATE_E PllState;           /* OUT, indicate PLL state is wrong or normal */       
} MXL661_PLL_INFO_T, *PMXL661_PLL_INFO_T;

/* MXL661_TUNER_MODE_CFG */
typedef enum
{
  MXL661_ANA_NTSC_MODE = 0x0,
  MXL661_ANA_PAL_BG = 0x01,
  MXL661_ANA_PAL_I = 0x02,
  MXL661_ANA_PAL_D = 0x03,
  MXL661_ANA_SECAM_I = 0x04,
  MXL661_ANA_SECAM_L = 0x05,
  MXL661_DIG_DVB_C = 0x06, 
  MXL661_DIG_ISDBT_ATSC = 0x07,
  MXL661_DIG_DVB_T_DTMB = 0x08,
  MXL661_DIG_J83B = 0x09,
  MXL661_SIGNAL_NA = 99
} MXL661_SIGNAL_MODE_E;

typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  MXL661_SIGNAL_MODE_E SignalMode;       /* IN , Tuner application mode */
  UINT32 IFOutFreqinKHz;              /* IN, IF Frequency in KHz */
  MXL661_XTAL_FREQ_E XtalFreqSel;        /* XTAL Frequency, refers above */
  UINT8 IFOutGainLevel;               /* IF out gain level */
} MXL661_TUNER_MODE_CFG_T, *PMXL661_TUNER_MODE_CFG_T;

/* MXL661_TUNER_POWER_UP_CFG */
typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  MXL_BOOL Enable;                    /* IN , enable or disable all sections of main path */
} MXL661_POWER_UP_CFG_T, *PMXL661_POWER_UP_CFG_T;

/* MXL661_TUNER_START_TUNE_CFG */ 
typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  MXL_BOOL StartTune;                 /* IN , sequence set, 0 means start sequence, 1 means finish */
} MXL661_START_TUNE_CFG_T, *PMXL661_START_TUNE_CFG_T;

/* MXL_TUNER_AGC_CFG */ 
typedef enum
{
  MXL661_AGC2 = 0,
  MXL661_AGC1 = 1
} MXL661_AGC_ID_E;

typedef enum
{
  MXL661_AGC_SELF = 0,
  MXL661_AGC_EXTERNAL = 1
} MXL661_AGC_TYPE_E;

typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  MXL661_AGC_ID_E AgcSel;                /* IN, AGC selection, AGC1 or AGC2 */
  MXL661_AGC_TYPE_E AgcType;             /* IN, AGC mode selection, self or closed loop */
  UINT8 SetPoint;                     /* IN, AGC attack point set value */
  MXL_BOOL AgcPolarityInverstion;     /* IN, Config AGC Polarity inversion */
} MXL661_AGC_SET_CFG_T, *PMXL661_AGC_SET_CFG_T;

/* MXL661_TUNER_CHAN_TUNE_CFG */
typedef enum
{
  MXL661_ANA_TV_DIG_CABLE_BW_6MHz = 0x00,    /* Analog TV and Digital Cable Mode 6MHz */ 
  MXL661_ANA_TV_DIG_CABLE_BW_7MHz = 0x01,    /* Analog TV and Digital Cable Mode 7MHz */
  MXL661_ANA_TV_DIG_CABLE_BW_8MHz = 0x02,    /* Analog TV and Digital Cable Mode 8MHz */
  MXL661_DIG_TERR_BW_6MHz = 0x20,            /* Digital Terrestrial Mode 6MHz */
  MXL661_DIG_TERR_BW_7MHz = 0x21,            /* Digital Terrestrial Mode 7MHz */
  MXL661_DIG_TERR_BW_8MHz = 0x22             /* Digital Terrestrial Mode 8MHz */
} MXL661_BW_E;

typedef enum
{
  MXL661_VIEW_MODE = 0, 
  MXL661_SCAN_MODE 
} MXL661_TUNE_TYPE_E;

typedef enum
{
  MXL661_NTSC_CARRIER_NA = 0,
  MXL661_NTSC_CARRIER_HRC = 1,
  MXL661_NTSC_CARRIER_IRC = 2
} MXL661_NTSC_CARRIERS_E;

typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  MXL661_TUNE_TYPE_E TuneType;           /* IN, Tune mode, view mode or channel scan mode */
  MXL661_BW_E BandWidth;                 /* IN, band width in MHz */
  UINT32 FreqInHz;                    /* IN, Radio Frequency in Hz */
  MXL661_SIGNAL_MODE_E SignalMode;       /* IN , Tuner application mode */
  MXL661_XTAL_FREQ_E XtalFreqSel;        /* IN, Xtal frequency */
  MXL661_NTSC_CARRIERS_E NtscCarrier;    /* IN, NTSC Carriers HRC or IRC (used for tunning NTSC channels only) */
  UINT32 IFOutFreqinKHz;              /* IN, IF Frequency in KHz */
} MXL661_TUNER_TUNE_CFG_T, *PMXL661_TUNER_TUNE_CFG_T;

/* MXL661_TUNER_SPUR_SHIFT_ADJ_CFG */
typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  UINT8 SpurShiftingClkAdjValue;      /* IN, Spur shifting clock adjust value, range [205, 227] */ 
} MXL661_SPUR_SHIFT_ADJ_CFG_T, *PMXL661_SPUR_SHIFT_ADJ_CFG_T;

/* MXL661_TUNER_HLFRF_OPTIMIZATION_CFG  */
typedef struct
{
  UINT8 I2cSlaveAddr;           /* IN, I2C Address of MxL Device */
  MXL_BOOL Enable;              /* IN, Enable or Disable the control */
} MXL661_HLFRF_CFG_T, *PMXL661_HLFRF_CFG_T;

/* MXL661_TUNER_AFC_CFG */
typedef enum
{
  MXL661_AFC_DISABLE = 0,
  MXL661_AFC_30KHZ = 30,
  MXL661_AFC_50KHZ = 50,
  MXL661_AFC_DEFAULT = 100
} MXL661_AFC_RANGE_E;

typedef struct
{
  UINT8 I2cSlaveAddr;                  /* IN, I2C Address of MxL Device */
  MXL661_AFC_RANGE_E AfcRangeInKHz;    /* IN, AFC range in KHz unit  */
} MXL661_TUNER_AFC_CFG_T, *PMXL661_TUNER_AFC_CFG_T;

/* MXL661_TUNER_FINE_TUNE_CFG */
typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  MXL_BOOL ScaleUp;                   /* IN, 0 means decrease one step, 1 means increase one step */
} MXL661_FINE_TUNE_CFG_T, *PMXL661_FINE_TUNE_CFG_T;

/* MXL661_TUNER_ENABLE_FINE_TUNE_CFG */
typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  MXL_BOOL EnableFineTune;            /* IN, enable/disable fine tune */
} MXL661_ENABLE_FINE_TUNE_CFG_T, *PMXL661_ENABLE_FINE_TUNE_CFG_T;

/* MXL661_TUNER_BALUNLESS_CFG */
typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  MXL661_SIGNAL_MODE_E SignalMode;       /* IN , Tuner application mode */    
  MXL_BOOL EnableHPF;                 /* IN, enable/disable HPF */
  MXL_BOOL EnableLPF;                 /* IN, enable/disable LPF */
} MXL661_TUNER_BALUNLESS_CFG_T, *PMXL661_TUNER_BALUNLESS_CFG_T;

/* MXL661_TUNER_ATV_DELAY_CFG and MXL661_TUNER_ATV_DELAY_REQ */
typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  UINT16 DelayTimeInOneTenthUs;       /* IN/OUT, ATV delay time in 0.1us unit */ 
} MXL661_TUNER_ATV_DELAY_CFG_T, *PMXL661_TUNER_ATV_DELAY_CFG_T;

/* MXL661_TUNER_HPF_LPF_CFG_T */
typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  MXL661_SIGNAL_MODE_E SignalMode;       /* IN , Tuner application mode */
  UINT32 FreqInHz;                    /* IN, Radio Frequency in Hz */
} MXL661_TUNER_HPF_LPF_CFG_T, *PMXL661_TUNER_HPF_LPF_CFG_T;

/* MXL661_TUNER_SIGNAL_TYPE_REQ */
typedef enum
{
  MXL661_SIGNAL_TYPE_DIGITAL = 0,
  MXL661_SIGNAL_TYPE_ANALOG 
} MXL661_SIGNAL_TYPE_E;

typedef struct
{
  UINT8 I2cSlaveAddr;      
  MXL661_SIGNAL_TYPE_E SignalMode;  
} MXL661_SIGNAL_TYPE_T, *PMXL661_SIGNAL_TYPE_T;

/* MXL661_TUNER_LOCK_STATUS_REQ */
typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  MXL_BOOL RfSynLock;                 /* OUT, Tuner RF synthesis lock Status */
  MXL_BOOL RefSynLock;                /* OUT, Tuner Ref synthesis lock Status */
} MXL661_TUNER_LOCK_STATUS_T, *PMXL661_TUNER_LOCK_STATUS_T;

/* MXL661_TUNER_AGC_LOCK_REQ */
typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  MXL_BOOL AgcLock;                   /* OUT, Tuner AGC lock Status */
} MXL661_TUNER_AGC_LOCK_T, *PMXL661_TUNER_AGC_LOCK_T;

/* MXL661_TUNER_RX_PWR_REQ */
typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  SINT16 RxPwr;                       /* OUT, Tuner RF Input Power in dBm */
} MXL661_TUNER_RX_PWR_T, *PMXL661_TUNER_RX_PWR_T;

/* MXL661_TUNER_AFC_CORRECTION_REQ */
typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  SINT32 AfcOffsetKHz;                /* OUT, Tuner AFC correction offset in kHz */
} MXL661_TUNER_AFC_CORRECTION_T, *PMXL661_TUNER_AFC_CORRECTION_T;

#ifdef MXL661_ENABLE_TELETEXT_SPUR_FEATURE
/* MXL661_TUNER_TELETEXT_SPUR_CFG */
typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  UINT32 numofDCCalSamples;
  UINT32 dcCalSamplesInterval;
  UINT32 initialTimeDelay;
  REAL64 dcCalThreshold;
} MXL661_TELETEXT_SPUR_CFG_T, *PMXL661_TELETEXT_SPUR_CFG_T;
#endif 
/* API COMMAND interface structure */
typedef struct
{
  MXL661_CMD_TYPE_E commandId;  /* Command Identifier */

  union
  {
    MXL661_RESET_CFG_T cmdResetCfg;
    MXL661_OVERWRITE_DEFAULT_CFG_T cmdOverwriteDefault;
    MXL661_XTAL_SET_CFG_T cmdXtalCfg;
    MXL661_PWR_MODE_CFG_T cmdPwrModeCfg;
    MXL661_IF_OUT_CFG_T cmdIfOutCfg;    
    MXL661_GPO_CFG_T cmdGpoCfg;

    MXL661_DEV_INFO_T cmdDevInfoReq;
    MXL661_GPO_INFO_T cmdGpoReq;
    MXL661_PLL_INFO_T cmdPllReq;

    MXL661_TUNER_MODE_CFG_T cmdModeCfg;
    MXL661_POWER_UP_CFG_T cmdTunerPoweUpCfg;
    MXL661_START_TUNE_CFG_T cmdStartTuneCfg;
    MXL661_AGC_SET_CFG_T cmdAgcSetCfg; 
    MXL661_TUNER_TUNE_CFG_T cmdChanTuneCfg;
    MXL661_SPUR_SHIFT_ADJ_CFG_T cmdSuprShiftAdjCfg;
    MXL661_FINE_TUNE_CFG_T cmdFineTuneCfg;
    MXL661_ENABLE_FINE_TUNE_CFG_T cmdEnableFineTuneCfg;
    MXL661_HLFRF_CFG_T cmdHlfrfCfg;
    MXL661_TUNER_AFC_CFG_T cmdAfcCfg; 
#ifdef MXL661_ENABLE_TELETEXT_SPUR_FEATURE	
    MXL661_TELETEXT_SPUR_CFG_T cmdTeletextSpurCfg;
#endif 
    MXL661_TUNER_BALUNLESS_CFG_T cmdBalunlessCfg; 
    MXL661_TUNER_ATV_DELAY_CFG_T cmdAtvDelayCfg;

    MXL661_SIGNAL_TYPE_T cmdTunerSignalTypeReq;
    MXL661_TUNER_LOCK_STATUS_T cmdTunerLockReq;
    MXL661_TUNER_RX_PWR_T cmdTunerPwrReq;
    MXL661_TUNER_AGC_LOCK_T cmdTunerAgcLockReq;
    MXL661_TUNER_AFC_CORRECTION_T cmdTunerAfcCorectionReq;
	MXL661_TUNER_HPF_LPF_CFG_T   cmdTunerAtvFilterCfg;
  } MxLIf;
} MXL661_COMMAND_T;

/******************************************************************************
    Global Variable Declarations
******************************************************************************/

extern const UINT8 MxLWare661DrvVersion[];
extern const UINT8 MxL661BuildNumber;

/******************************************************************************
    Prototypes
******************************************************************************/

#ifndef __MXL_GUI__
MXL_STATUS MxLWare661_API_ConfigDevice(MXL661_COMMAND_T *ParamPtr);
MXL_STATUS MxLWare661_API_GetDeviceStatus(MXL661_COMMAND_T *ParamPtr);
MXL_STATUS MxLWare661_API_ConfigTuner(MXL661_COMMAND_T *ParamPtr);
MXL_STATUS MxLWare661_API_GetTunerStatus(MXL661_COMMAND_T *ParamPtr);
#endif

#endif /* __MXL661_TUNER_API_H__*/



