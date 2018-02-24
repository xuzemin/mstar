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
 * FILE NAME          : MxL601_TunerApi.h
 *
 * AUTHOR             : Sunghoon Park
 *                      Dong Liu
 *
 * DATE CREATED       : 07/10/2011
 *                      03/14/2013
 *
 * DESCRIPTION        : This file is header file for MxL601_TunerApi.cpp
 *
 *******************************************************************************
 *                Copyright (c) 2011, MaxLinear, Inc.
 ******************************************************************************/

#ifndef __MXL601_TUNER_API_H__
#define __MXL601_TUNER_API_H__

/******************************************************************************
    Include Header Files
    (No absolute paths - paths handled by make file)
******************************************************************************/

#include "MaxLinearDataTypes.h"
#include "MxL601_TunerCfg.h"

/******************************************************************************
    Macros
******************************************************************************/

#define  MXL_VERSION_SIZE         4   
#define  MAX_MXL601_DEVICES       4

//#define CUSTOMER_SPECIFIC_SETTING_1
//#define CUSTOMER_SPECIFIC_SETTING_2
/******************************************************************************
    User-Defined Types (Typedefs)
******************************************************************************/

/* Command Types  */
typedef enum
{
  // For API_ConfigDevice interface
  MXL_DEV_SOFT_RESET_CFG = 0,
  MXL_DEV_OVERWRITE_DEFAULT_CFG,
  MXL_DEV_XTAL_SET_CFG,
  MXL_DEV_POWER_MODE_CFG,
  MXL_DEV_IF_OUT_CFG,
  MXL_DEV_GPO_CFG,

  // For API_GetDeviceStatus interface
  MXL_DEV_ID_VERSION_REQ,
  MXL_DEV_GPO_STATE_REQ,
  MXL_DEV_PLL_STATE_REQ, 

  // For API_ConfigTuner interface
  MXL_TUNER_MODE_CFG,
  MXL_TUNER_POWER_UP_CFG,
  MXL_TUNER_START_TUNE_CFG,
  MXL_TUNER_AGC_CFG,
  MXL_TUNER_CHAN_TUNE_CFG,
  MXL_TUNER_SPUR_SHIFT_ADJ_CFG,
  MXL_TUNER_FINE_TUNE_CFG,
  MXL_TUNER_ENABLE_FINE_TUNE_CFG,
  MXL_TUNER_HLFRF_CFG,
  MXL_TUNER_AFC_CFG,
#ifdef ENABLE_TELETEXT_SPUR_FEATURE  
  MXL_TUNER_TELETEXT_SPUR_CFG,
#endif 
  MXL_TUNER_BALUNLESS_CFG,

  // For API_GetTunerStatus interface
  MXL_TUNER_SIGNAL_TYPE_REQ,
  MXL_TUNER_LOCK_STATUS_REQ,
  MXL_TUNER_AGC_LOCK_REQ,
  MXL_TUNER_RX_PWR_REQ,
  MXL_TUNER_AFC_CORRECTION_REQ,

  MAX_NUM_COMMAND
} MXL_CMD_TYPE_E;

/* MXL_DEV_SOFT_RESET_CFG  */
typedef struct
{
  UINT8 I2cSlaveAddr;           /* IN, I2C Address of MxL Device */
} MXL_RESET_CFG_T, *PMXL_RESET_CFG_T;

/* MXL_DEV_OVERWRITE_DEFAULT_CFG */
typedef struct
{
  UINT8 I2cSlaveAddr;           /* IN, I2C Address of MxL Device */
  MXL_BOOL SingleSupply_3_3V;   /* IN, Single Supply 3.3v */
} MXL_OVERWRITE_DEFAULT_CFG_T, *PMXL_OVERWRITE_DEFAULT_CFG_T;

/* MXL_DEV_XTAL_SET_CFG  */
typedef enum
{
  XTAL_16MHz = 0,
  XTAL_24MHz = 1,
  XTAL_FREQ_NA = 99
} MXL_XTAL_FREQ_E;

typedef struct
{
  UINT8 I2cSlaveAddr;           /* IN, I2C Address of MxL Device */
  MXL_XTAL_FREQ_E XtalFreqSel;  /* IN, XTAL Frequency, refers above */
  UINT8 XtalCap;                /* IN, XTAL capacity, 1 LSB = 1pF, maximum is 31pF */
  MXL_BOOL ClkOutEnable;        /* IN, enable or disable clock out */
  MXL_BOOL ClkOutDiv;           /* IN, indicate if XTAL frequency is dived by 4 or not */
  MXL_BOOL SingleSupply_3_3V;   /* IN, Single Supply 3.3v */
  MXL_BOOL XtalSharingMode;     /* IN, XTAL sharing mode. default Master, MXL_ENABLE to config Slave mode */
} MXL_XTAL_SET_CFG_T, *PMXL_XTAL_SET_CFG_T;

/* MXL_DEV_POWER_MODE_CFG  */
typedef enum
{
  MXL_PWR_MODE_SLEEP = 0,
  MXL_PWR_MODE_ACTIVE,
  MXL_PWR_MODE_STANDBY
} MXL_PWR_MODE_E;

typedef struct
{
  UINT8 I2cSlaveAddr;           /* IN, I2C Address of MxL Device */
  MXL_PWR_MODE_E PowerMode;     /* IN, power saving mode */
} MXL_PWR_MODE_CFG_T, *PMXL_PWR_MODE_CFG_T;

/* MXL_DEV_IF_OUT_CFG  */
typedef enum
{
  IF_PATH1 = 1,
  IF_PATH2 = 2
} MXL_IF_PATH_E;

typedef enum
{
  IF_3_65MHz  = 0,
  IF_4MHz     = 1,
  IF_4_1MHz   = 2,
  IF_4_15MHz  = 3,
  IF_4_5MHz   = 4,
  IF_4_57MHz  = 5,
  IF_5MHz     = 6,
  IF_5_38MHz  = 7,
  IF_6MHz     = 8,
  IF_6_28MHz  = 9,
  IF_7_2MHz   = 10,
  IF_8_25MHz  = 11,
  IF_35_25MHz = 12,
  IF_36MHz    = 13,
  IF_36_15MHz = 14,
  IF_36_65MHz = 15,
  IF_44MHz    = 16,
  IF_FREQ_NA  = 99
} MXL_IF_FREQ_E;

typedef struct
{
  UINT8 I2cSlaveAddr;           /* IN, I2C Address of MxL Device */
  MXL_IF_FREQ_E IFOutFreq;      /* IN, band width of IF out signal */
  UINT32 ManualIFOutFreqInKHz;  /* IN, IF out frequency selection when ManualIFOutCtrl = 0*/
  MXL_BOOL ManualFreqSet;       /* IN, IF out frequency is set by manual or not */
  MXL_BOOL IFInversion;         /* IN, IF spectrum is inverted or not */
  UINT8 GainLevel;              /* IN, IF out gain level */
  MXL_IF_PATH_E PathSel;        /* IN, define which path is selected */
}MXL_IF_OUT_CFG_T, *PMXL_IF_OUT_CFG_T;

/* MXL_DEV_GPO_CFG  */
typedef enum
{
  GPO1 = 0,
  GPO2 = 1,
  GPO3 = 2
} MXL_GPO_ID_E;

typedef enum
{
  PORT_LOW = 0,
  PORT_HIGH = 1,
  PORT_AUTO_CTRL = 2
} MXL_GPO_STATE_E;

typedef struct
{
  UINT8 I2cSlaveAddr;           /* IN, I2C Address of MxL Device */
  MXL_GPO_ID_E GPOId;           /* IN, GPO port number. 0 for GPO0, 1 for GPO1, and 2 for GPO2 */
  MXL_GPO_STATE_E GPOState;     /* IN, configuration. */
} MXL_GPO_CFG_T, *PMXL_GPO_CFG_T;

/* MXL_DEV_ID_VERSION_REQ */
typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  UINT8 ChipId;                       /* OUT, Device chip ID information  */
  UINT8 ChipVersion;                  /* OUT, Device chip revision  */
  UINT8 MxLWareVer[MXL_VERSION_SIZE]; /* OUT, MxLWare version information */
} MXL_DEV_INFO_T, *PMXL_DEV_INFO_T;

/* MXL_DEV_GPO_STATE_REQ  */
typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  MXL_GPO_STATE_E GPO1;               /* OUT, GPO0 status */
  MXL_GPO_STATE_E GPO2;               /* OUT, GPO1 status */
  MXL_GPO_STATE_E GPO3;               /* OUT, GPO2 status */
} MXL_GPO_INFO_T, *PMXL_GPO_INFO_T;

/* MXL_DEV_PLL_STATE_REQ  */
typedef enum
{
  PLL_STATE_NORMAL = 0,
  PLL_STATE_WRONG  = 1,
  PLL_STATE_NA = 2
} MXL_PLL_STATE_E;

typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */   
  MXL_PLL_STATE_E PllState;           /* OUT, indicate PLL state is wrong or normal */       
} MXL_PLL_INFO_T, *PMXL_PLL_INFO_T;

/* MXL_TUNER_MODE_CFG */
typedef enum
{
  ANA_NTSC_MODE = 0x0,
  ANA_PAL_BG = 0x01,
  ANA_PAL_I = 0x02,
  ANA_PAL_D = 0x03,
  ANA_SECAM_I = 0x04,
  ANA_SECAM_L = 0x05,
  DIG_DVB_C = 0x06,
  DIG_ISDBT_ATSC = 0x07,
  DIG_DVB_T_DTMB = 0x08,
  DIG_J83B = 0x09,
  ATV_SCAN = 0x0A,
  MXL_SIGNAL_NA = 99
} MXL_SIGNAL_MODE_E;

typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  MXL_SIGNAL_MODE_E SignalMode;       /* IN , Tuner application mode */
  UINT32 IFOutFreqinKHz;              /* IN, IF Frequency in KHz */
  MXL_XTAL_FREQ_E XtalFreqSel;        /* XTAL Frequency, refers above */
  UINT8 IFOutGainLevel;               /* IF out gain level */
} MXL_TUNER_MODE_CFG_T, *PMXL_TUNER_MODE_CFG_T;

/* MXL_TUNER_POWER_UP_CFG */
typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  MXL_BOOL Enable;                    /* IN , enable or disable all sections of main path */
} MXL_POWER_UP_CFG_T, *PMXL_POWER_UP_CFG_T;

/* MXL_TUNER_START_TUNE_CFG */
typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  MXL_BOOL StartTune;                 /* IN , sequence set, 0 means start sequence, 1 means finish */
} MXL_START_TUNE_CFG_T, *PMXL_START_TUNE_CFG_T;

/* MXL_TUNER_AGC_CFG */
typedef enum
{
  AGC2 = 0,
  AGC1 = 1
} MXL_AGC_ID_E;

typedef enum
{
  AGC_SELF = 0,
  AGC_EXTERNAL = 1
} MXL_AGC_TYPE_E;

typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  MXL_AGC_ID_E AgcSel;                /* IN, AGC selection, AGC1 or AGC2 */
  MXL_AGC_TYPE_E AgcType;             /* IN, AGC mode selection, self or closed loop */
  UINT8 SetPoint;                     /* IN, AGC attack point set value */
  MXL_BOOL AgcPolarityInverstion;     /* IN, Config AGC Polarity inversion */
} MXL_AGC_SET_CFG_T, *PMXL_AGC_SET_CFG_T;

/* MXL_TUNER_CHAN_TUNE_CFG */
typedef enum
{
  ANA_TV_DIG_CABLE_BW_6MHz = 0x00,    /* Analog TV and Digital Cable Mode 6MHz */
  ANA_TV_DIG_CABLE_BW_7MHz = 0x01,    /* Analog TV and Digital Cable Mode 7MHz */
  ANA_TV_DIG_CABLE_BW_8MHz = 0x02,    /* Analog TV and Digital Cable Mode 8MHz */
  DIG_TERR_BW_6MHz = 0x20,            /* Digital Terrestrial Mode 6MHz */
  DIG_TERR_BW_7MHz = 0x21,            /* Digital Terrestrial Mode 7MHz */
  DIG_TERR_BW_8MHz = 0x22             /* Digital Terrestrial Mode 8MHz */
} MXL_BW_E;

typedef enum
{
  VIEW_MODE = 0,
  SCAN_MODE
} MXL_TUNE_TYPE_E;

typedef enum
{
  MXL_NTSC_CARRIER_NA = 0,
  MXL_NTSC_CARRIER_HRC = 1,
  MXL_NTSC_CARRIER_IRC = 2
} MXL_NTSC_CARRIERS_E;

typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  MXL_TUNE_TYPE_E TuneType;           /* IN, Tune mode, view mode or channel scan mode */
  MXL_BW_E BandWidth;                 /* IN, band width in MHz */
  UINT32 FreqInHz;                    /* IN, Radio Frequency in Hz */
  MXL_SIGNAL_MODE_E SignalMode;       /* IN , Tuner application mode */
  MXL_XTAL_FREQ_E XtalFreqSel;        /* IN, Xtal frequency */
  MXL_NTSC_CARRIERS_E NtscCarrier;    /* IN, NTSC Carriers HRC or IRC (used for tunning NTSC channels only) */
  UINT32 IFOutFreqinKHz;              /* IN, IF Frequency in KHz */
} MXL_TUNER_TUNE_CFG_T, *PMXL_TUNER_TUNE_CFG_T;

/* MXL_TUNER_SPUR_SHIFT_ADJ_CFG */
typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  UINT8 SpurShiftingClkAdjValue;      /* IN, Spur shifting clock adjust value, range [205, 227] */
} MXL_SPUR_SHIFT_ADJ_CFG_T, *PMXL_SPUR_SHIFT_ADJ_CFG_T;

/* MXL_TUNER_HLFRF_OPTIMIZATION_CFG  */
typedef struct
{
  UINT8 I2cSlaveAddr;           /* IN, I2C Address of MxL Device */
  MXL_BOOL Enable;              /* IN, Enable or Disable the control */
} MXL_HLFRF_CFG_T, *PMXL_HLFRF_CFG_T;

/* MXL_TUNER_AFC_CFG */
typedef enum
{
  MXL601_AFC_DISABLE = 0,
  MXL601_AFC_30KHZ = 30,
  MXL601_AFC_50KHZ = 50,
  MXL601_AFC_DEFAULT = 100
} MXL601_AFC_RANGE_E;

typedef struct
{
  UINT8 I2cSlaveAddr;                  /* IN, I2C Address of MxL Device */
  MXL601_AFC_RANGE_E AfcRangeInKHz;    /* IN, AFC range in KHz unit  */
} MXL_TUNER_AFC_CFG_T, *PMXL_TUNER_AFC_CFG_T;

/* MXL_TUNER_FINE_TUNE_CFG */
typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  MXL_BOOL ScaleUp;                   /* IN, 0 means decrease one step, 1 means increase one step */
} MXL_FINE_TUNE_CFG_T, *PMXL_FINE_TUNE_CFG_T;

/* MXL_TUNER_ENABLE_FINE_TUNE_CFG */
typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  MXL_BOOL EnableFineTune;            /* IN, enable/disable fine tune */
} MXL_ENABLE_FINE_TUNE_CFG_T, *PMXL_ENABLE_FINE_TUNE_CFG_T;

/* MXL_TUNER_BALUNLESS_CFG */
typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  MXL_SIGNAL_MODE_E SignalMode;       /* IN , Tuner application mode */               
} MXL_TUNER_BALUNLESS_CFG_T, *PMXL_TUNER_BALUNLESS_CFG_T;

/* MXL_TUNER_SIGNAL_TYPE_REQ */
typedef enum
{
  SIGNAL_TYPE_DIGITAL = 0,
  SIGNAL_TYPE_ANALOG
} MXL_SIGNAL_TYPE_E;

typedef struct
{
  UINT8 I2cSlaveAddr;
  MXL_SIGNAL_TYPE_E SignalMode;
} MXL_SIGNAL_TYPE_T, *PMXL_SIGNAL_TYPE_T;

/* MXL_TUNER_LOCK_STATUS_REQ */
typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  MXL_BOOL RfSynLock;                 /* OUT, Tuner RF synthesis lock Status */
  MXL_BOOL RefSynLock;                /* OUT, Tuner Ref synthesis lock Status */
} MXL_TUNER_LOCK_STATUS_T, *PMXL_TUNER_LOCK_STATUS_T;

/* MXL_TUNER_AGC_LOCK_REQ */
typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  MXL_BOOL AgcLock;                   /* OUT, Tuner AGC lock Status */
} MXL_TUNER_AGC_LOCK_T, *PMXL_TUNER_AGC_LOCK_T;

/* MXL_TUNER_RX_PWR_REQ */
typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  SINT16 RxPwr;                       /* OUT, Tuner RF Input Power in dBm */
} MXL_TUNER_RX_PWR_T, *PMXL_TUNER_RX_PWR_T;

/* MXL_TUNER_AFC_CORRECTION_REQ */
typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  SINT32 AfcOffsetKHz;                /* OUT, Tuner AFC correction offset in kHz */
} MXL_TUNER_AFC_CORRECTION_T, *PMXL_TUNER_AFC_CORRECTION_T;

#ifdef ENABLE_TELETEXT_SPUR_FEATURE
/* MXL_TUNER_TELETEXT_SPUR_CFG */
typedef struct
{
  UINT8 I2cSlaveAddr;                 /* IN, I2C Address of MxL Device */
  UINT32 numofDCCalSamples;
  UINT32 dcCalSamplesInterval;
  UINT32 initialTimeDelay;
  REAL64 dcCalThreshold;
} MXL_TELETEXT_SPUR_CFG_T, *PMXL_TELETEXT_SPUR_CFG_T;
#endif 

/* API COMMAND interface structure */
typedef struct
{
  MXL_CMD_TYPE_E commandId;  /* Command Identifier */

  union
  {
    MXL_RESET_CFG_T cmdResetCfg;
    MXL_OVERWRITE_DEFAULT_CFG_T cmdOverwriteDefault;
    MXL_XTAL_SET_CFG_T cmdXtalCfg;
    MXL_PWR_MODE_CFG_T cmdPwrModeCfg;
    MXL_IF_OUT_CFG_T cmdIfOutCfg;
    MXL_GPO_CFG_T cmdGpoCfg;

    MXL_DEV_INFO_T cmdDevInfoReq;
    MXL_GPO_INFO_T cmdGpoReq;
    MXL_PLL_INFO_T cmdPllReq;

    MXL_TUNER_MODE_CFG_T cmdModeCfg;
    MXL_POWER_UP_CFG_T cmdTunerPoweUpCfg;
    MXL_START_TUNE_CFG_T cmdStartTuneCfg;
    MXL_AGC_SET_CFG_T cmdAgcSetCfg;
    MXL_TUNER_TUNE_CFG_T cmdChanTuneCfg;
    MXL_SPUR_SHIFT_ADJ_CFG_T cmdSuprShiftAdjCfg;
    MXL_FINE_TUNE_CFG_T cmdFineTuneCfg;
    MXL_ENABLE_FINE_TUNE_CFG_T cmdEnableFineTuneCfg;
    MXL_HLFRF_CFG_T cmdHlfrfCfg;
    MXL_TUNER_AFC_CFG_T cmdAfcCfg; 
#ifdef ENABLE_TELETEXT_SPUR_FEATURE	
    MXL_TELETEXT_SPUR_CFG_T cmdTeletextSpurCfg;
#endif 
    MXL_TUNER_BALUNLESS_CFG_T cmdBalunlessCfg; 

    MXL_SIGNAL_TYPE_T cmdTunerSignalTypeReq;
    MXL_TUNER_LOCK_STATUS_T cmdTunerLockReq;
    MXL_TUNER_RX_PWR_T cmdTunerPwrReq;
    MXL_TUNER_AGC_LOCK_T cmdTunerAgcLockReq;
    MXL_TUNER_AFC_CORRECTION_T cmdTunerAfcCorectionReq;
  } MxLIf;
} MXL_COMMAND_T;

/******************************************************************************
    Global Variable Declarations
******************************************************************************/

extern const UINT8 MxLWareDrvVersion[];
extern const UINT8 BuildNumber;

/******************************************************************************
    Prototypes
******************************************************************************/

#ifndef __MXL_GUI__
MXL_STATUS MxLWare601_API_ConfigDevice(MXL_COMMAND_T *ParamPtr);
MXL_STATUS MxLWare601_API_GetDeviceStatus(MXL_COMMAND_T *ParamPtr);
MXL_STATUS MxLWare601_API_ConfigTuner(MXL_COMMAND_T *ParamPtr);
MXL_STATUS MxLWare601_API_GetTunerStatus(MXL_COMMAND_T *ParamPtr);
#endif

#endif /* __MXL601_TUNER_API_H__*/




