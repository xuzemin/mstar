/***************************************************************************************/
/* FILE: Si2176_L2_TV_Chassis.c                                                        */
/* Si2176 1.Bb3 Sample Code - TV Chassis                                               */
/* Supported ICs : Si2176                                                     */
/* Revision: 0.0                                                                       */
/* Date: March 10, 2011                                                               */
/*(C) Copyright 2011, Silicon Laboratories, Inc. All rights reserved.          */
/***************************************************************************************/
/* This is the TV chassis application of the sample code                             */
/***************************************************************************************/
#include <stdio.h>
#include <string.h>
/* Si2176 API Defines */
/* define this if using the ATV video filter */
//#undef USING_ATV_FILTER
#define USING_ATV_FILTER    // add define from yoondj recommendation by yooheeyong 20110524
/* define this if using the DTV video filter */
//#undef USING_DLIF_FILTER
#define USING_DLIF_FILTER   // add define from yoondj recommendation by yooheeyong 20110524
/************************************************************************************************************************/
/* Si2176 API Specific Includes */
//#include "Si2176_Typedefs.h"

#include "Si2176_L0_TV_Chassis.h"        /* Load LO TV chassis, MUST be updated for porting to an embedded system */

//#include "Si2176_Firmware_1_B_build_3.h"       /* Si2176 1.Bb3 firmware compatible with Si2176-B0A-GM */
//#include "Si2176_Firmware_2_B_build_6.h"         /* change by yooheeyong 20110704 */
#include "Si2176_Firmware_2_2_build_1.h"         /* Rom12, fixed MFT bug 20110728 */

// B2A  임시버전 2011년 7월 21일
//#include "Si2176_Firmware_B2A_Rom13.h"
#include "Si2176_Firmware_3_0_B2A_3_Rom13.h"     /* Rom13, fixed MFT bug 20110728 */

// B 30 2011년 8월 4일 
#include "Si2176_Firmware_B_3_0.h"

#include "Si2176_Generic_Sound_Processor.h"     /* Generic routines for customer implemented sound processor */
#include "Si2176_Generic_DTV_Demod.h"           /* Generic routines for customer implemented DTV Demodulator */
#ifdef USING_ATV_FILTER
#include "Si2176_Write_ATV_video_coeffs.h"   /* .h file from custom Video filter Tool output */
#endif
#ifdef USING_DLIF_FILTER
#include "Si2176_Write_DLIF_video_coeffs.h"   /* .h file from custom Video filter Tool output */
#endif
#include "Si2176_L2_TV_Chassis.h"        /* Include file for this code */

#ifndef UNUSED_SAMSUNG //to avoid compile warnings...
#define UNUSED_SAMSUNG(var) ((var) = (var))
#endif
/************************************************************************************************************************/
/* Si2176 API Specific Global Variables */
unsigned char wait_for_cts = 0;     /* global flag for CTS checking prior to sending a Si2176 API Command */
unsigned char wait_for_response = 1;    /* global flag for CTS checking and Response readback after sending Si2176 API Command */
/************************************************************************************************************************/
/* Chip Globals */
/* property wrapper contains all available properties in a struct */
Si2176_PropObj     prop;
/************************************************************************************************************************/
/* Channel Scan Globals */
/* define the maximum possible channels (1002MHz - 43MHz) / 6MHz  (required for the channelscan array)*/
#define MAX_POSSIBLE_CHANNELS 160
/* Global array to store the list of found channels */
unsigned long ChannelList[MAX_POSSIBLE_CHANNELS];
/* ChannelScanPal needs to store the PAL type also so allocate 4 chars each for that */
char ChannelType[MAX_POSSIBLE_CHANNELS][4];
/* Number of found channels from a channel scan */
int ChannelListSize =0;
/************************************************************************************************************************/
/*chip rev constants for integrity checking */
const char chiprev = 2;
/* Last 2 digits of part number */
const char  part = 76; /* Change this value if using a chip other than an Si2176 */
const char partMajorVersion = '1';
const char partMinorVersion = 'A'; 
const char partRomid = 0x12;
/* unique serial number for chip */
unsigned long partSerialNumber ; 
/************************************************************************************************************************/
/** globals for Top Level routine */
unsigned long newFrequency;
int ATVMode=0;
int DTVMode=0;
int ATVConfigurationChangedFlag=0;
int DTVConfigurationChangedFlag=0;
/************************************************************************************************************************
  NAME: TunerFrequencyChanged
  DESCRIPTION:  This routine checks to see if the frequency has changed by monitoring the frequency expected and
                the newFrequency global variable.   If they are different then a 1 = changed is returned.
  Parameter:    Current frequency of the tuner (Hz)
  Returns:      1 if frequency is changed by a new update in the newFrequency variable, else 0.
************************************************************************************************************************/
int TunerFrequencyChanged(unsigned long *frequency)
{
  if (newFrequency != *frequency)
  {
    *frequency = newFrequency;
    return 1;
  } 
  else
    return 0;
}
/************************************************************************************************************************/
/************************************************************************************************************************
  NAME: UpdateChannelScanFrequency
  DESCRIPTION:  This routine allows the user to implement an update of the current channel scan operation with
                the current frequency being scanned.
  Parameter:    Current frequency of the scan routine
  Parameter:  channelsFound = 0 if channel not found at that frequency , channelsFound > 0  the number of channels 
        currently found( including this frequency )
  Returns:      1 if scan abort requested, 0 if ok.
************************************************************************************************************************/
int UpdateChannelScanFrequency(int freq,int channelsFound)
{
  //static int previousFrequency;  
  //int abort = 0;
  //previousFrequency = 0;
    UNUSED_SAMSUNG(freq);
    UNUSED_SAMSUNG(channelsFound);
   return 0;
}

/************************************************************************************
  NAME: ProcessAPITopLevelSequence
  DESCRIPTION:  Main entry point into application.  See the enclosed comments on how to modify for your 
        application.
  Parameter: none
  Returns:  Tuner Error 
  Programming Guide Reference:    Flowchart A.1 (top level flowchart)
  
************************************************************************************************************************/
int ProcessAPITopLevelSequence(void) 
{
  /* Allocate the following structures for the chip */
  /* L0  (I2C Communication) Context */
  L0_Context Si2176_L0;
  /* L1 (Tuner) Context  */
  L1_Si2176_Context Si2176_L1;
  /* Allocate rsp variable */   
  Si2176_CmdReplyObj    rsp;
  int return_code=0;
  unsigned long frequency;
  
  frequency = 0;

  /* Initialize the Level 1 and Level 0 Context */
    Si2176_L1_API_Init(&Si2176_L1, &Si2176_L0, 0xc0);       /* API software initialization */

  /* Initialize the Si2173 and power up the chip */    

    if ((return_code=Si2176_Init(&Si2176_L1)) != 0)
    return return_code;
  /* At this point, FW is loaded and started. */

  /* Download Video Filters, Setup default property configurations and clocks/pin configurations */
  if ((return_code=Si2176_Configure1(&Si2176_L1, &rsp)) != 0)
      return return_code;

  /* At this point the chip is ready to be tuned. */
  while (1)
  {
    /*  TODO: set ATVMode flag if in ATV mode */
    if (ATVMode)
    {
      /* if the default configuration is changed, then write the new property values to the chip. */
      /* TODO: If a change is made to any ATV configurations, set this flag (ATVConfigurationChangedFlag =1),
               The flag will be cleared after the configuration changes are completed */
      if (ATVConfigurationChangedFlag)
      {
        /* Configure the ATV properties based on the data in the prop global variable */
        Si2176_ATVConfig (&Si2176_L1);
        /* Note: the Common properties and the tuner properties are not likely to change from the 
           startup defaults.   If you do change these you will need to execute CommonConfig(&Si2176_L1)
           and / or TunerConfig(&Si2176_L1). */

        /* retuning is required to update the ATV Configuration properties */
        Si2176_Tune(&Si2176_L1,Si2176_TUNER_TUNE_FREQ_CMD_MODE_ATV,frequency,&rsp);
        /* Clear the changed Flag */
        ATVConfigurationChangedFlag = 0;
      
      } 
      /* When the frequency is changed, tune to the new frequency */
      /* TODO: If a change is made to the frequency, update the newFrequency global variable. */
      if (TunerFrequencyChanged(&frequency))
      {
        Si2176_Tune(&Si2176_L1,Si2176_TUNER_TUNE_FREQ_CMD_MODE_ATV,frequency,&rsp);
      }
      /* Now Check the ATV Status */
      /*Programming Guide Reference:    Flowchart A.8 (ATV Status flowchart) */
      /* fetch the Tuner status */
      if (Si2176_L1_TUNER_STATUS (&Si2176_L1, wait_for_cts, wait_for_response, Si2176_DTV_STATUS_CMD_INTACK_OK, &rsp))
      {
        return ERROR_Si2176_SENDING_COMMAND;  
      }

      /* TODO: if needed, check the tuner status :
      Parameters available are:
        rsp.tuner_status.tcint
        rsp.tuner_status.rssilint
        rsp.tuner_status.rssihint
        rsp.tuner_status.tc
        rsp.tuner_status.rssil
        rsp.tuner_status.rssi
        rsp.tuner_status.freq
        rsp.tuner_status.mode
        */

      /* fetch the ATV Status */
            if (Si2176_L1_ATV_STATUS (&Si2176_L1, wait_for_cts, wait_for_response, Si2176_ATV_STATUS_CMD_INTACK_OK, &rsp))
      {
        return ERROR_Si2176_SENDING_COMMAND;  
      }
      /* TODO: if needed, check the atv status :
      Parameters of most interest are:
        rsp.atv_status.pcl      -- picture carrier lock
        rsp.atv_status.chl      -- valid channel flag
        rsp.atv_status.dl     -- demod lock
        rsp.atv_status.rssil    -- rssi > threshold
        rsp.atv_status.snrl     -- SNR not low
        rsp.atv_status.afc_freq   -- afc_frequency (kHz), offset from tuned frequency
        rsp.atv_status.video_snr  -- video SNR (1/2dB)
      */
    }
    /*  TODO: set DTVMode flag if in DTV mode */
    if (DTVMode)
    {
      if (DTVConfigurationChangedFlag)
      {
        /* Configure the DTV properties based on the data in the prop global variable */
        Si2176_DTVConfig (&Si2176_L1);
        /* retuning is required to update the DTV Configuration properties */
        Si2176_Tune(&Si2176_L1,Si2176_TUNER_TUNE_FREQ_CMD_MODE_DTV,frequency,&rsp);
        /* Clear the changed Flag */
        DTVConfigurationChangedFlag = 0;
      }
      /* When the frequency is changed, tune to the new frequency */
      /* TODO: If a change is made to the frequency, update the newFrequency global variable. */
      if (TunerFrequencyChanged(&frequency))
      {
        Si2176_Tune(&Si2176_L1,Si2176_TUNER_TUNE_FREQ_CMD_MODE_DTV,frequency,&rsp);
      }
      /* Check the DTV Status */
      /*Programming Guide Reference:    Flowchart A.9 (DTV Status flowchart) */
      /* fetch the Tuner status */
      if (Si2176_L1_TUNER_STATUS (&Si2176_L1, wait_for_cts, wait_for_response, Si2176_DTV_STATUS_CMD_INTACK_OK, &rsp))
      {
        return ERROR_Si2176_SENDING_COMMAND;  
      }
      /* TODO: if needed, check the tuner status :
      Parameters available are:
        rsp.tuner_status.tcint
        rsp.tuner_status.rssilint
        rsp.tuner_status.rssihint
        rsp.tuner_status.tc
        rsp.tuner_status.rssil
        rsp.tuner_status.rssi
        rsp.tuner_status.freq
        rsp.tuner_status.mode
        */

      /* fetch the DTV status */
      if (Si2176_L1_DTV_STATUS (&Si2176_L1, wait_for_cts, wait_for_response, Si2176_DTV_STATUS_CMD_INTACK_OK, &rsp))
      {
        return ERROR_Si2176_SENDING_COMMAND;  
      }

      /* TODO: if needed, check the dtv status :
      Parameters available are:
        rsp.dtv_status.chlint
        rsp.dtv_status.chl
        rsp.dtv_status.bw
        rsp.dtv_status.modulation
      */
    }
  }
  
    return 0;
}
/************************************************************************************************************************/
/************************************************************************************************************************
  NAME: Si2176_SetupATVDefaults
  DESCRIPTION: Setup Si2176 ATV startup configuration
  This is a list of all the ATV configuration properties.   Depending on your application, only a subset may be required.
  The properties are stored in the global property structure 'prop'.  The function Si2176_ATVConfig(..) must be called
  after any properties are modified.   
  Parameter:  none
  Returns:    0 if successful
  Programming Guide Reference:    Flowchart A.5 (ATV Setup flowchart)
  
************************************************************************************************************************/
int Si2176_SetupATVDefaults (void)
{
  prop.atv_afc_range.range_khz                  = Si2176_ATV_AFC_RANGE_PROP_RANGE_KHZ_1000_KHZ;
  prop.atv_af_out.volume                        = Si2176_ATV_AF_OUT_PROP_VOLUME_VOLUME_MAX;
  prop.atv_agc_speed.if_agc_speed               = Si2176_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
  prop.atv_audio_mode.audio_sys                 = Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_DEFAULT;
  prop.atv_audio_mode.demod_mode                = Si2176_ATV_AUDIO_MODE_PROP_DEMOD_MODE_SIF;
  prop.atv_audio_mode.chan_bw                   = Si2176_ATV_AUDIO_MODE_PROP_CHAN_BW_DEFAULT;
  prop.atv_cvbs_out.offset                      =    25;
  prop.atv_cvbs_out.amp                         =   200;
  prop.atv_vsync_tracking.min_pulses_to_lock    =     1;
  prop.atv_vsync_tracking.min_fields_to_unlock  =    16;  
  prop.atv_cvbs_out_fine.offset                 =     0;
  prop.atv_cvbs_out_fine.amp                    =   100;
  prop.atv_ien.chlien                           = Si2176_ATV_IEN_PROP_CHLIEN_ENABLE;     /* enable only CHL to drive ATVINT */
  prop.atv_ien.pclien                           = Si2176_ATV_IEN_PROP_PCLIEN_DISABLE;
  prop.atv_ien.dlien                            = Si2176_ATV_IEN_PROP_DLIEN_DISABLE;
  prop.atv_ien.snrlien                          = Si2176_ATV_IEN_PROP_SNRLIEN_DISABLE;
  prop.atv_ien.snrhien                          = Si2176_ATV_IEN_PROP_SNRHIEN_DISABLE;
  prop.atv_int_sense.chlnegen                   = Si2176_ATV_INT_SENSE_PROP_CHLNEGEN_DISABLE;
  prop.atv_int_sense.pclnegen                   = Si2176_ATV_INT_SENSE_PROP_PCLNEGEN_DISABLE;
  prop.atv_int_sense.dlnegen                    = Si2176_ATV_INT_SENSE_PROP_DLNEGEN_DISABLE;
  prop.atv_int_sense.snrlnegen                  = Si2176_ATV_INT_SENSE_PROP_SNRLNEGEN_DISABLE;
  prop.atv_int_sense.snrhnegen                  = Si2176_ATV_INT_SENSE_PROP_SNRHNEGEN_DISABLE;
  prop.atv_int_sense.chlposen                   = Si2176_ATV_INT_SENSE_PROP_CHLPOSEN_ENABLE;
  prop.atv_int_sense.pclposen                   = Si2176_ATV_INT_SENSE_PROP_PCLPOSEN_ENABLE;
  prop.atv_int_sense.dlposen                    = Si2176_ATV_INT_SENSE_PROP_DLPOSEN_ENABLE;
  prop.atv_int_sense.snrlposen                  = Si2176_ATV_INT_SENSE_PROP_SNRLPOSEN_ENABLE;
  prop.atv_int_sense.snrhposen                  = Si2176_ATV_INT_SENSE_PROP_SNRHPOSEN_ENABLE;
  prop.atv_rf_top.atv_rf_top                    = Si2176_ATV_RF_TOP_PROP_ATV_RF_TOP_AUTO;
  prop.atv_min_lvl_lock.thrs                    = 34;
  prop.atv_rsq_rssi_threshold.lo                =   -70;
  prop.atv_rsq_rssi_threshold.hi                =     0;
  prop.atv_rsq_snr_threshold.lo                 =    25;
  prop.atv_rsq_snr_threshold.hi                 =    45;
  prop.atv_sif_out.offset                       =   135;
  prop.atv_sif_out.amp                          =    60;
  prop.atv_video_equalizer.slope                =     0;
  prop.atv_video_mode.video_sys                 = Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B;
  prop.atv_video_mode.color                     = Si2176_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;
  prop.atv_video_mode.trans                     = Si2176_ATV_VIDEO_MODE_PROP_TRANS_TERRESTRIAL;
  prop.atv_video_mode.invert_signal             =     0;
  prop.atv_vsnr_cap.atv_vsnr_cap                =     0;
  prop.atv_sound_agc_speed.other_systems        =    7;
  prop.atv_sound_agc_speed.system_l             =    8;
  prop.atv_sound_agc_limit.min_gain             =    -84;
  prop.atv_sound_agc_limit.max_gain             =    84;

  return 0;
}
/************************************************************************************************************************
  NAME: Si2176_SetupDTVDefaults
  DESCRIPTION: Setup Si2176 DTV startup configuration
  This is a list of all the DTV configuration properties.   Depending on your application, only a subset may be required.
  The properties are stored in the global property structure 'prop'.  The function Si2176_DTVConfig(..) must be called
  after any properties are modified.   
  Parameter:  none
  Returns:    0 if successful
  Programming Guide Reference:    Flowchart A.6 (DTV setup flowchart)
  
************************************************************************************************************************/
int Si2176_SetupDTVDefaults(void)
{
  prop.dtv_agc_speed.if_agc_speed               = Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
  prop.dtv_agc_speed.agc_decim                  = Si2176_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF;
  prop.dtv_config_if_port.dtv_out_type          = Si2176_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LIF_IF1;
  prop.dtv_config_if_port.dtv_agc_source        =     0;
  prop.dtv_ext_agc.min_10mv                     =    50;
  prop.dtv_ext_agc.max_10mv                     =   200;
  prop.dtv_ien.chlien                           = Si2176_DTV_IEN_PROP_CHLIEN_ENABLE;      /* enable only CHL to drive DTVINT */
  prop.dtv_int_sense.chlnegen                   = Si2176_DTV_INT_SENSE_PROP_CHLNEGEN_DISABLE;
  prop.dtv_int_sense.chlposen                   = Si2176_DTV_INT_SENSE_PROP_CHLPOSEN_ENABLE;
  prop.dtv_lif_freq.offset                      =  5000;
  prop.dtv_lif_out.offset                       =   148;
  prop.dtv_lif_out.amp                          =    27;
  prop.dtv_mode.bw                              = Si2176_DTV_MODE_PROP_BW_BW_8MHZ;
  prop.dtv_mode.modulation                      = Si2176_DTV_MODE_PROP_MODULATION_DVBT;
  prop.dtv_mode.invert_spectrum                 =     0;
  prop.dtv_rf_top.dtv_rf_top                    = Si2176_DTV_RF_TOP_PROP_DTV_RF_TOP_AUTO;
  prop.dtv_rsq_rssi_threshold.lo                =   -80;
  prop.dtv_rsq_rssi_threshold.hi                =     0;
  prop.dtv_initial_agc_speed.if_agc_speed       = Si2176_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
  prop.dtv_initial_agc_speed.agc_decim          = Si2176_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_OFF;
  prop.dtv_initial_agc_speed_period.period      = 0;

  return 0;
}
/************************************************************************************************************************
  NAME: Si2176_SetupCommonDefaults
  DESCRIPTION: Setup Si2176 Common startup configuration
  This is a list of all the common configuration properties.   Depending on your application, only a subset may be required.
  The properties are stored in the global property structure 'prop'.  The function CommonConfig(..) must be called
  after any of these properties are modified.   
  Parameter:  none
  Returns:    0 if successful
  Programming Guide Reference:    Flowchart A.6a (Common setup flowchart)
************************************************************************************************************************/
int Si2176_SetupCommonDefaults(void)
{
   /**** Enable Interrupt Sources *******/
  prop.master_ien.atvien=Si2176_MASTER_IEN_PROP_ATVIEN_ON;
  prop.master_ien.ctsien=Si2176_MASTER_IEN_PROP_CTSIEN_ON;
  prop.master_ien.dtvien=Si2176_MASTER_IEN_PROP_DTVIEN_ON;
  prop.master_ien.errien=Si2176_MASTER_IEN_PROP_ERRIEN_ON;
  prop.master_ien.tunien=Si2176_MASTER_IEN_PROP_TUNIEN_ON;
  /* Crystal Trim adjustment */
  prop.crystal_trim.xo_cap = 8;
  return 0;
}
/************************************************************************************************************************
  NAME: Si2176_SetupTunerDefaults
  DESCRIPTION: Setup Si2176 Tuner startup configuration
  This is a list of all the Tuner configuration properties.   Depending on your application, only a subset may be required.
  The properties are stored in the global property structure 'prop'.  The function TunerConfig(..) must be called
  after any of these properties are modified.   
  Parameter:  none
  Returns:    0 if successful
  Programming Guide Reference:    Flowchart A.6a (Tuner setup flowchart)
************************************************************************************************************************/
int Si2176_SetupTunerDefaults(void)
{

  /* Setting Si2176_TUNER_IEN_PROP property */
    prop.tuner_ien.tcien     = Si2176_TUNER_IEN_PROP_TCIEN_ENABLE; /* enable only TC to drive TUNINT */
    prop.tuner_ien.rssilien  = Si2176_TUNER_IEN_PROP_RSSILIEN_ENABLE;
    prop.tuner_ien.rssihien  = Si2176_TUNER_IEN_PROP_RSSIHIEN_DISABLE;

  /* Setting Si2176_TUNER_BLOCK_VCO_PROP property */
  prop.tuner_blocked_vco.vco_code= 0x8000;
    
  /* Setting Si2176_TUNER_INT_SENSE_PROP property */
  prop.tuner_int_sense.rssihnegen = Si2176_TUNER_INT_SENSE_PROP_RSSIHNEGEN_DISABLE;
  prop.tuner_int_sense.rssihposen = Si2176_TUNER_INT_SENSE_PROP_RSSIHPOSEN_ENABLE;
  prop.tuner_int_sense.rssilnegen = Si2176_TUNER_INT_SENSE_PROP_RSSILNEGEN_DISABLE;
  prop.tuner_int_sense.rssilposen = Si2176_TUNER_INT_SENSE_PROP_RSSILPOSEN_ENABLE;
  prop.tuner_int_sense.tcnegen  = Si2176_TUNER_INT_SENSE_PROP_RSSIHNEGEN_DISABLE;
  prop.tuner_int_sense.tcposen  = Si2176_TUNER_INT_SENSE_PROP_TCPOSEN_ENABLE;

 
   /* Setting Si2176_TUNER_LO_INJECTION_PROP property */
  prop.tuner_lo_injection.band_1  = Si2176_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
  prop.tuner_lo_injection.band_2  = Si2176_TUNER_LO_INJECTION_PROP_BAND_2_HIGH_SIDE;
  prop.tuner_lo_injection.band_3  = Si2176_TUNER_LO_INJECTION_PROP_BAND_3_HIGH_SIDE;
  prop.tuner_lo_injection.band_4  = Si2176_TUNER_LO_INJECTION_PROP_BAND_4_HIGH_SIDE;
  prop.tuner_lo_injection.band_5  = Si2176_TUNER_LO_INJECTION_PROP_BAND_5_HIGH_SIDE;

  return 0;
}

/************************************************************************************************************************
  NAME: Si2176_ATVConfig 
  DESCRIPTION: Setup Si2176 ATV properties configuration
  This function will download all the ATV configuration properties stored in the global structure 'prop.
  Depending on your application, only a subset may be required to be modified.
  The function Si2176_SetupATVDefaults() should be called before the first call to this function. Afterwards
  to change a property change the appropriate element in the property structure 'prop' and call this routine.
  Use the comments above the SetProperty2 calls as a guide to the parameters which are changed.
  Parameter:  Pointer to Si2176 Context (I2C address)
  Returns:    I2C transaction error code, 0 if successful
  Programming Guide Reference:    Flowchart A.5 (ATV setup flowchart)
************************************************************************************************************************/
int Si2176_ATVConfig (L1_Si2176_Context *Si2176) 
{
  Si2176_CmdReplyObj rsp;
  

  /* Set ATV_CVBS_OUT property */
  //prop.atv_cvbs_out.amp,
  //prop.atv_cvbs_out.offset
   if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_CVBS_OUT_PROP, &prop, &rsp) != 0) 
   {
      return ERROR_Si2176_SENDING_COMMAND;
   }  
   
   /* Set the ATV_SIF_OUT property */
  //prop.atv_sif_out.amp,
  //prop.atv_sif_out.offset
   if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_SIF_OUT_PROP, &prop, &rsp) != 0) 
   {
      return ERROR_Si2176_SENDING_COMMAND;
   }

   /* Set the ATV_AFC_RANGE property */
  //prop.atv_afc_range.range_khz
   if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_AFC_RANGE_PROP, &prop, &rsp) != 0) 
   {
      return ERROR_Si2176_SENDING_COMMAND;
   }

   /* Set the ATV_RF_TOP property */
  //prop.atv_rf_top.atv_rf_top
   if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_RF_TOP_PROP, &prop, &rsp) != 0) 
   {
      return ERROR_Si2176_SENDING_COMMAND;
   }

   /* Set the ATV_VSYNC_TRACKING property */
  //prop.atv_vsync_tracking.min_pulses_to_lock,
  //prop.atv_vsync_tracking.min_fields_to_unlock
   if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_VSYNC_TRACKING_PROP, &prop, &rsp) != 0) 
   {
      return ERROR_Si2176_SENDING_COMMAND;
   }
   /* Set the ATV_MIN_LVL_LOCK property */
  //prop.atv_min_lvl_lock.thrs
   if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_MIN_LVL_LOCK_PROP, &prop, &rsp) != 0) 
   {
      return ERROR_Si2176_SENDING_COMMAND;
   }
   /* Set the ATV_CVBS_OUT_FINE property */
  //prop.atv_cvbs_out_fine.amp,
  //prop.atv_cvbs_out_fine.offset
   if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_CVBS_OUT_FINE_PROP, &prop, &rsp) != 0) 
   {
      return ERROR_Si2176_SENDING_COMMAND;
   }

   /* Set the ATV_AGC_SPEED property */
  //prop.atv_agc_speed.if_agc_speed
   if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_AGC_SPEED_PROP, &prop, &rsp) != 0) 
   {
      return ERROR_Si2176_SENDING_COMMAND;
   }
  /* Set the ATV_VSNR_CAP property */
  //prop.atv_vsnr_cap.atv_vsnr_cap
   if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_VSNR_CAP_PROP, &prop, &rsp) != 0) 
   {
      return ERROR_Si2176_SENDING_COMMAND;
   }
     /* Set the ATV_AF_OUT property */
  //prop.atv_af_out.volume
   if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_AF_OUT_PROP, &prop, &rsp) != 0) 
   {
      return ERROR_Si2176_SENDING_COMMAND;
   }  
   
   /*Set the ATV_RSSI_RSQ_THRESHOLD property */
  //prop.atv_rsq_rssi_threshold.hi,
  //prop.atv_rsq_rssi_threshold.lo
   if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_RSQ_RSSI_THRESHOLD_PROP, &prop, &rsp) != 0) 
   {
      return ERROR_Si2176_SENDING_COMMAND;
   }  
   
   /*Set the ATV_SNR_RSQ_THRESHOLD property */
  //prop.atv_rsq_snr_threshold.hi,
  //prop.atv_rsq_snr_threshold.lo
   if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_RSQ_SNR_THRESHOLD_PROP, &prop, &rsp) != 0) 
   {
      return ERROR_Si2176_SENDING_COMMAND;
   }

   /*Set the ATV_VIDEO_EQUALIZER property */
  //prop.atv_video_equalizer.slope
   if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_VIDEO_EQUALIZER_PROP, &prop, &rsp) != 0) 
   {
      return ERROR_Si2176_SENDING_COMMAND;
   }

   /*Set the ATV_INT_SENSE property */
  //prop.atv_int_sense.chlnegen,
  //prop.atv_int_sense.chlposen,
  //prop.atv_int_sense.dlnegen,
  //prop.atv_int_sense.dlposen,
  //prop.atv_int_sense.pclnegen,
  //prop.atv_int_sense.pclposen,
  //prop.atv_int_sense.snrhnegen,
  //prop.atv_int_sense.snrhposen,
  //prop.atv_int_sense.snrlnegen,
  //prop.atv_int_sense.snrlposen
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_INT_SENSE_PROP, &prop, &rsp) != 0) 
  {
      return ERROR_Si2176_SENDING_COMMAND;
    }
  /* setup ATV_IEN_PROP  IEN properties to enable ATVINT on CHL  */     
  
    /* prop.atv_ien.chlien, 
    prop.atv_ien.pclien, 
    prop.atv_ien.dlien , 
    prop.atv_ien.snrlien,
    prop.atv_ien.snrhien */
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_IEN_PROP, &prop, &rsp) != 0) 
  {
        return ERROR_Si2176_SENDING_COMMAND;
    }

    /* Set the ATV_AUDIO_MODE property */
  /*  prop.atv_audio_mode.audio_sys,
    prop.atv_audio_mode.chan_bw,
    prop.atv_audio_mode.demod_mode  */
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_AUDIO_MODE_PROP, &prop, &rsp) != 0) 
  {
      return ERROR_Si2176_SENDING_COMMAND;
    }

   /* Set the ATV_VIDEO_MODE property */
  /*  prop.atv_video_mode.video_sys,
    prop.atv_video_mode.trans,
    prop.atv_video_mode.color  
        prop.atv_video_mode.invert_signal*/
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_VIDEO_MODE_PROP, &prop, &rsp) != 0) 
  {
      return ERROR_Si2176_SENDING_COMMAND;
    }

    return 0;
}

/************************************************************************************************************************
  NAME: Si2176_DTVConfig 
  DESCRIPTION: Setup Si2176 DTV properties configuration
  This function will download all the DTV configuration properties stored in the global structure 'prop.
  Depending on your application, only a subset may be required to be modified.
  The function Si2176_SetupDTVDefaults() should be called before the first call to this function. Afterwards
  to change a property change the appropriate element in the property structure 'prop' and call this routine.
  Use the comments above the Si2176_L1_SetProperty2 calls as a guide to the parameters which are changed.
  Parameter:  Pointer to Si2176 Context (I2C address)
  Returns:    I2C transaction error code, 0 if successful
  Programming Guide Reference:    Flowchart A.6 (DTV setup flowchart)
************************************************************************************************************************/
int Si2176_DTVConfig (L1_Si2176_Context *Si2176) 
{
  Si2176_CmdReplyObj rsp;
 
    /* Setting DTV_CONFIG_IF_PORT_PROP property */
  /*  prop.dtv_config_if_port.dtv_out_type,
    prop.dtv_config_if_port.dtv_agc_source */
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_DTV_CONFIG_IF_PORT_PROP, &prop, &rsp) != 0) 
  {
        return ERROR_Si2176_SENDING_COMMAND;
    }

    /* Setting DTV_LIF_FREQ_PROP */
    //  prop.dtv_lif_freq.offset 
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_DTV_LIF_FREQ_PROP, &prop, &rsp) != 0) 
  {
        return ERROR_Si2176_SENDING_COMMAND;
    }

    /* Setting DTV_MODE_PROP property */
  /*  prop.dtv_mode.bw,
    prop.dtv_mode.invert_spectrum,
    prop.dtv_mode.modulation*/
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_DTV_MODE_PROP, &prop, &rsp) != 0) 
  {
        return ERROR_Si2176_SENDING_COMMAND;
    }

  /* Setting DTV_RSQ_RSSI_THRESHOLD property */
  //  prop.dtv_rsq_rssi_threshold.hi,
  //  prop.dtv_rsq_rssi_threshold.lo
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_DTV_RSQ_RSSI_THRESHOLD_PROP, &prop, &rsp) != 0) 
  {
        return ERROR_Si2176_SENDING_COMMAND;
    }
  
  /* Setting DTV_EXT_AGC property */
  //  prop.dtv_ext_agc.max_10mv,
  //  prop.dtv_ext_agc.min_10mv
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_DTV_EXT_AGC_PROP, &prop, &rsp) != 0) 
  {
        return ERROR_Si2176_SENDING_COMMAND;
    }
 
    /* Setting DTV_LIF_OUT property */
  //  prop.dtv_lif_out.amp,
  //  prop.dtv_lif_out.offset
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_DTV_LIF_OUT_PROP, &prop, &rsp) != 0) 
  {
        return ERROR_Si2176_SENDING_COMMAND;
    }

  /* Setting DTV_AGC_SPEED property */
  //  prop.dtv_agc_speed.agc_decim,
  //  prop.dtv_agc_speed.if_agc_speed
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_DTV_AGC_SPEED_PROP, &prop, &rsp) != 0) 
  {
        return ERROR_Si2176_SENDING_COMMAND;
    }

  /* Setting DTV_RF_TOP property */
  //  prop.dtv_rf_top.dtv_rf_top
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_DTV_RF_TOP_PROP, &prop, &rsp) != 0) 
  {
        return ERROR_Si2176_SENDING_COMMAND;
    }

    /* Setting DTV_INT_SENSE property */
  //  prop.dtv_int_sense.chlnegen,
  //  prop.dtv_int_sense.chlposen
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_DTV_INT_SENSE_PROP, &prop, &rsp) != 0) 
  {
        return ERROR_Si2176_SENDING_COMMAND;
    }

    /* Set DTV_IEN property */
  /*  prop.dtv_ien.chlien */
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_DTV_IEN_PROP, &prop, &rsp) != 0) 
  {
        return ERROR_Si2176_SENDING_COMMAND;
    }
    
    /* Set DTV_INITIAL_AGC_SPEED property */
  /*  prop.dtv_initial_agc_speed.if_agc_speed */
  /*  prop.dtv_initial_agc_speed.agc_decim */
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_DTV_INITIAL_AGC_SPEED_PROP, &prop, &rsp) != 0) 
  {
        return ERROR_Si2176_SENDING_COMMAND;
    }
    
    /* Set DTV_INITIAL_AGC_SPEED_PERIOD property */
  /*  prop.dtv_initial_agc_speed_period.period */
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_DTV_INITIAL_AGC_SPEED_PERIOD_PROP, &prop, &rsp) != 0) 
  {
        return ERROR_Si2176_SENDING_COMMAND;
    }    
    return 0;
}
/************************************************************************************************************************
  NAME: Si2176_CommonConfig 
  DESCRIPTION: Setup Si2176 Common properties configuration
  This function will download all the DTV configuration properties stored in the global structure 'prop.
  Depending on your application, only a subset may be required to be modified.
  The function Si2176_SetupCOMMONDefaults() should be called before the first call to this function. Afterwards
  to change a property change the appropriate element in the property structure 'prop' and call this routine.
  Use the comments above the Si2176_L1_SetProperty2 calls as a guide to the parameters which are changed.
  Parameter:  Pointer to Si2176 Context (I2C address)
  Returns:    I2C transaction error code, 0 if successful
  Programming Guide Reference:    Flowchart A.6a (Common setup flowchart)
************************************************************************************************************************/
int Si2176_CommonConfig (L1_Si2176_Context *Si2176) 
{
  Si2176_CmdReplyObj rsp;


    /* Setting Si2176_MASTER_IEN_PROP property */
   /***
     prop.master_ien.atvien,
     prop.master_ien.ctsien,
     prop.master_ien.dtvien,
     prop.master_ien.errien,
     prop.master_ien.tunien  */
 
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_MASTER_IEN_PROP, &prop, &rsp) != 0) 
  {
        return ERROR_Si2176_SENDING_COMMAND;
    }

  
    /* Setting Si2176_CRYSTAL_TRIM_PROP */
    //  prop.crystal_trim.xo_cap 
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_CRYSTAL_TRIM_PROP, &prop, &rsp) != 0) 
  {
        return ERROR_Si2176_SENDING_COMMAND;
    }
  
  return 0;
}
/************************************************************************************************************************
  NAME: Si2176_TunerConfig 
  DESCRIPTION: Setup Si2176 Tuner (RF to IF analog path) properties configuration
  This function will download all the DTV configuration properties stored in the global structure 'prop.
  Depending on your application, only a subset may be required to be modified.
  The function Si2176_SetupTUNERDefaults() should be called before the first call to this function. Afterwards
  to change a property change the appropriate element in the property structure 'prop' and call this routine.
  Use the comments above the Si2176_L1_SetProperty2 calls as a guide to the parameters which are changed.
  Parameter:  Pointer to Si2176 Context (I2C address)
  Returns:    I2C transaction error code, 0 if successful
  Programming Guide Reference:    Flowchart A.6a (Tuner setup flowchart)
************************************************************************************************************************/
int Si2176_TunerConfig (L1_Si2176_Context *Si2176) 
{
  Si2176_CmdReplyObj rsp;


  /* Set TUNER_IEN property */
  /*  prop.tuner_ien.tcien,
    prop.tuner_ien.rssilien,
    prop.tuner_ien.rssihien */
  if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_TUNER_IEN_PROP, &prop, &rsp) != 0) 
  {
    return ERROR_Si2176_SENDING_COMMAND;
  }

  /* Setting TUNER_BLOCKED_VCO property */
  /*  prop.tuner_blocked_vco.vco_code, */
  if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_TUNER_BLOCKED_VCO_PROP, &prop, &rsp) != 0) 
  {
    return ERROR_Si2176_SENDING_COMMAND;
  }
  /* Setting Si2176_TUNER_INT_SENSE_PROP property */
  /*  prop.tuner_int_sense.rssihnegen,
    prop.tuner_int_sense.rssihposen,
    prop.tuner_int_sense.rssilnegen,
    prop.tuner_int_sense.rssilposen,
    prop.tuner_int_sense.tcnegen,
    prop.tuner_int_sense.tcposen */

  if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_TUNER_INT_SENSE_PROP, &prop, &rsp) != 0) 
  {
    return ERROR_Si2176_SENDING_COMMAND;
  }

  /* Setting Si2176_TUNER_LO_INJECTION_PROP property */
  /*  prop.tuner_lo_injection.band_1,
    prop.tuner_lo_injection.band_2,
    prop.tuner_lo_injection.band_3,
    prop.tuner_lo_injection.band_4,
    prop.tuner_lo_injection.band_5 */
  if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_TUNER_LO_INJECTION_PROP, &prop, &rsp) != 0) 
  {
    return ERROR_Si2176_SENDING_COMMAND;
  }


    return 0;
}

/************************************************************************************************************************
  NAME: Si2176_Tune
  DESCRIPTIION: Tune Si2176 in specified mode (ATV/DTV) at center frequency, wait for TUNINT and xTVINT with timeout

  Parameter:  Pointer to Si2176 Context (I2C address)
  Parameter:  Mode (ATV or DTV) use Si2176_TUNER_TUNE_FREQ_CMD_MODE_ATV or Si2176_TUNER_TUNE_FREQ_CMD_MODE_DTV constants
  Parameter:  frequency (Hz) as a unsigned long integer
  Parameter:  rsp - commandResp structure to returns tune status info.
  Returns:    0 if channel found.  A nonzero value means either an error occurred or channel not locked.
  Programming Guide Reference:    Flowchart A.7 (Tune flowchart)
************************************************************************************************************************/
int Si2176_Tune (L1_Si2176_Context *Si2176, unsigned char mode, unsigned long freq, Si2176_CmdReplyObj *rsp ) 
{
    Si2176_COMMON_REPLY_struct sstatus;
    int count=0;
    int return_code = 0;
    
    if (Si2176_L1_TUNER_TUNE_FREQ (Si2176, wait_for_cts, wait_for_response,
                mode,
                freq,
                rsp) != 0) 
  {
        return ERROR_Si2176_SENDING_COMMAND;
    }

     /* wait for TUNINT, timeout is 150ms */
    for (count=75; count ;count--) 
  {
        if ((return_code = CheckStatus(Si2176, &sstatus)) != 0)
            return return_code;
        if (sstatus.tunint)
            break;
        system_wait(2);
    }
    if (!count)
        return ERROR_Si2176_TUNINT_TIMEOUT;
        
    /* wait for xTVINT, timeout is 350ms for ATVINT and 10 ms for DTVINT */
    count = ((mode==Si2176_TUNER_TUNE_FREQ_CMD_MODE_ATV) ? 175 : 5);
    for (;count ;count--) 
  {
        if ((return_code = CheckStatus(Si2176, &sstatus)) != 0)
            return return_code;
        if ((mode==Si2176_TUNER_TUNE_FREQ_CMD_MODE_ATV) ? sstatus.atvint : sstatus.dtvint)
            break;
        system_wait(2);
    }
    if (!count)
        return ERROR_Si2176_xTVINT_TIMEOUT;

    return 0;
}

/************************************************************************************************************************
  NAME: Si2176_ATVTune
  DESCRIPTION:Update ATV_VIDEO_MODE and tune ATV mode at center frequency
  Parameter:  Pointer to Si2176 Context (I2C address)
  Parameter:  frequency (Hz)
  Parameter:  Video system , e.g. use constant Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_M for system M
  Parameter:  transport,  e.g. use constant Si2176_ATV_VIDEO_MODE_PROP_TRANS_TERRESTRIAL for terrestrial
  Parameter:  color , e.g. use constant Si2176_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC for PAL or NTSC
  Parameter:  invert_signal, 0= normal, 1= inverted
  Parameter:  rsp - commandResp structure to returns tune status info.
  Returns:    I2C transaction error code, 0 if successful
  Programming Guide Reference:    Flowchart A.7 (Tune flowchart)
************************************************************************************************************************/
int  Si2176_ATVTune (L1_Si2176_Context *Si2176, unsigned long freq, unsigned char video_sys, unsigned char trans, unsigned char color, unsigned char invert_signal, Si2176_CmdReplyObj *rsp)
{
    /* update ATV_VIDEO_MODE property */
    prop.atv_video_mode.video_sys = video_sys;
    prop.atv_video_mode.trans = trans;
    prop.atv_video_mode.color = color;
    prop.atv_video_mode.invert_signal=invert_signal;
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_VIDEO_MODE_PROP, &prop, rsp) != 0)
  {
      return ERROR_Si2176_SENDING_COMMAND;
    }

    return Si2176_Tune (Si2176, Si2176_TUNER_TUNE_FREQ_CMD_MODE_ATV, freq, rsp);
}
/************************************************************************************************************************
  NAME: Si2176_DTVTune
  DESCRIPTION: Update DTV_MODE and tune DTV mode at center frequency
  Parameter:  Pointer to Si2176 Context (I2C address)
  Parameter:  frequency (Hz)
  Parameter:  bandwidth , 6,7 or 8 MHz
  Parameter:  modulation,  e.g. use constant Si2176_DTV_MODE_PROP_MODULATION_DVBT for DVBT mode
  Parameter:  invert_spectrum, NORMAL (0) or INVERTED (1)
  Parameter:  rsp - commandResp structure to returns tune status info.
  Returns:    I2C transaction error code, 0 if successful
  Programming Guide Reference:    Flowchart A.7 (Tune flowchart)
************************************************************************************************************************/
int  Si2176_DTVTune (L1_Si2176_Context *Si2176, unsigned long freq, unsigned char bw, unsigned char modulation, unsigned char invert_spectrum, Si2176_CmdReplyObj *rsp)
{
  int errcode=0;

    /* update DTV_MODE_PROP property */
    prop.dtv_mode.bw = bw;
    prop.dtv_mode.invert_spectrum = invert_spectrum;
    prop.dtv_mode.modulation = modulation;
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_DTV_MODE_PROP, &prop, rsp) != 0)
  {
        return ERROR_Si2176_SENDING_COMMAND;
    }

    errcode = Si2176_Tune (Si2176, Si2176_TUNER_TUNE_FREQ_CMD_MODE_DTV, freq, rsp);
  /* Check if the external Digital Demodulator is locked */
    if (!errcode)
    return L1_DigitalDemodLocked();
  else
    return errcode;
}


/************************************************************************************************************************
  NAME: Si2176_Configure 
  DESCRIPTION: Setup Si2176 video filters, GPIOs/clocks, Common Properties startup, Tuner startup, ATV startup, and DTV startup.
  Parameter:  Pointer to Si2176 Context (I2C address)
  Parameter:  rsp - commandResp structure buffer.
  Returns:    I2C transaction error code, 0 if successful
************************************************************************************************************************/
int Si2176_Configure1 (L1_Si2176_Context *Si2176, Si2176_CmdReplyObj *rsp) 
{
    int return_code;

    /* load ATV video filter file */
  #ifdef USING_ATV_FILTER
    if ((return_code = Si2176_LoadVideofilter(Si2176,ATV_VIDFILT_TABLE,ATV_VIDFILT_LINES)) != 0)
       return return_code;
  #endif

  /* load DTV video filter file */
  #ifdef USING_DLIF_FILTER
     if ((return_code = Si2176_LoadVideofilter(Si2176,DLIF_VIDFILT_TABLE,DLIF_VIDFILT_LINES)) != 0)
       return return_code;
  #endif

    /* Set the GPIO Pins using the CONFIG_PINS command*/
    if (Si2176_L1_CONFIG_PINS (Si2176, wait_for_cts, wait_for_response,   /* turn off BCLK1 and XOUT */
                                      Si2176_CONFIG_PINS_CMD_GPIO1_MODE_NO_CHANGE,
                                      Si2176_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ,
                                      Si2176_CONFIG_PINS_CMD_GPIO2_MODE_NO_CHANGE,
                                      Si2176_CONFIG_PINS_CMD_GPIO2_READ_DO_NOT_READ,
                                      Si2176_CONFIG_PINS_CMD_GPIO3_MODE_NO_CHANGE,
                                      Si2176_CONFIG_PINS_CMD_GPIO3_READ_DO_NOT_READ,
                              Si2176_CONFIG_PINS_CMD_BCLK1_MODE_DISABLE,
                              Si2176_CONFIG_PINS_CMD_BCLK1_READ_DO_NOT_READ,
                              Si2176_CONFIG_PINS_CMD_XOUT_MODE_DISABLE,
              rsp) !=0) 
  {
        return ERROR_Si2176_SENDING_COMMAND;
    }

  /* Set Common Properties startup configuration */
  Si2176_SetupCommonDefaults ();
    if ((return_code = Si2176_CommonConfig(Si2176)) != 0)
       return return_code;

  /* Set Tuner Properties startup configuration */
  Si2176_SetupTunerDefaults ();
    if ((return_code = Si2176_TunerConfig(Si2176)) != 0)
       return return_code;

  /* Set ATV startup configuration */
  Si2176_SetupATVDefaults ();
    if ((return_code = Si2176_ATVConfig(Si2176)) != 0)
       return return_code;

    /* Set DTV startup configuration */
  Si2176_SetupDTVDefaults ();
  if ((return_code = Si2176_DTVConfig(Si2176)) != 0)
       return return_code;

    return 0;
}

  
/************************************************************************************************************************
  NAME: Si2176_PowerUpWithPatch
  DESCRIPTION: Send Si2176 API PowerUp Command with PowerUp to bootloader,
  Check the Chip rev and part, and ROMID are compared to expected values.
  Load the Firmware Patch then Start the Firmware.
  Programming Guide Reference:    Flowchart A.2 (POWER_UP with patch flowchart)

  Parameter:  Si2176 Context (I2C address)
  Returns:    Si2176/I2C transaction error code, 0 if successful
************************************************************************************************************************/
int Si2176_PowerUpWithPatch (L1_Si2176_Context *Si2176)
{
  int return_code =0;
  Si2176_CmdReplyObj    rsp;

    if (Si2176_L1_POWER_UP (Si2176, 1, wait_for_response,         /* always wait for CTS prior to POWER_UP command */
                     Si2176_POWER_UP_CMD_SUBCODE_CODE,
                     Si2176_POWER_UP_CMD_RESERVED1_RESERVED,
                     Si2176_POWER_UP_CMD_RESERVED2_RESERVED,
                 Si2176_POWER_UP_CMD_RESERVED3_RESERVED,
                     Si2176_POWER_UP_CMD_CLOCK_MODE_XTAL,
                     Si2176_POWER_UP_CMD_CLOCK_FREQ_CLK_24MHZ,
                     Si2176_POWER_UP_CMD_ADDR_MODE_CURRENT,
                     Si2176_POWER_UP_CMD_FUNC_BOOTLOADER,        /* start in bootloader mode */
                     Si2176_POWER_UP_CMD_CTSIEN_DISABLE,
                     Si2176_POWER_UP_CMD_WAKE_UP_WAKE_UP,
                     &rsp) != 0)
  {
        return ERROR_Si2176_SENDING_COMMAND;
    }

  /* Get the Part Info from the chip.   This command is only valid in Bootloader mode */
  if (Si2176_L1_PART_INFO(Si2176,wait_for_cts,wait_for_response, &rsp) != 0)
    return ERROR_Si2176_SENDING_COMMAND;
  /* Check the Chip revision, part and ROMID against expected values and report an error if incompatible */
  if (rsp.part_info.chiprev != chiprev)
    return ERROR_Si2176_INCOMPATIBLE_PART;
  /* Part Number is represented as the last 2 digits */

  if(rsp.part_info.romid == 0x12)
  {
  if (rsp.part_info.part != part)
    return ERROR_Si2176_INCOMPATIBLE_PART;
  /* Part Major Version in ASCII */
  if (rsp.part_info.pmajor != partMajorVersion)
    return ERROR_Si2176_INCOMPATIBLE_PART;
  /* Part Minor Version in ASCII */
  if (rsp.part_info.pminor != partMinorVersion)
    return ERROR_Si2176_INCOMPATIBLE_PART;
  /* ROMID in byte representation */
  if (rsp.part_info.romid != partRomid)
    return ERROR_Si2176_INCOMPATIBLE_PART;
  /* part serial number unsigned long*/
  partSerialNumber=rsp.part_info.serial;
  }

  if(rsp.part_info.romid == 0x12)
  {
  /* Load the Firmware */
    if ((return_code = Si2176_LoadFirmware(Si2176,FIRMWARE_TABLE,NB_LINES)) != 0)   /* Load firmware */
       return return_code;
  }else if(rsp.part_info.romid == 0x13)
  {
   
    if( rsp.part_info.pmajor=='1' &&  rsp.part_info.pminor == 'F')
    {

       /* Load the Firmware */
       if ((return_code = Si2176_LoadFirmware(Si2176,FIRMWARE_TABLE_B2A,NB_LINES_B2A)) != 0)    /* Load firmware */
           return return_code;
    }else if( rsp.part_info.pmajor=='3' &&  rsp.part_info.pminor == '0' ){
        /* Load the Firmware */
        if ((return_code = Si2176_LoadFirmware(Si2176,FIRMWARE_TABLE_B30,NB_LINES_B30)) != 0)   /* Load firmware */
           return return_code;
     }
  }

  /*Start the Firmware */
    if ((return_code = Si2176_StartFirmware(Si2176, &rsp)) != 0) /* Start firmware */
       return return_code;

    return NO_Si2176_ERROR;
}

/************************************************************************************************************************
  NAME: Si2176_LoadFirmware
  DESCRIPTON: Load firmware from FIRMWARE_TABLE array in Si2176_Firmware_x_y_build_z.h file into Si2176
              Requires Si2176 to be in bootloader mode after PowerUp
  Programming Guide Reference:    Flowchart A.3 (Download FW PATCH flowchart)

  Parameter:  Si2176 Context (I2C address)
  Parameter:  pointer to firmware table array
  Parameter:  number of lines in firmware table array (size in bytes / BYTES_PER_LINE)  
  Returns:    Si2176/I2C transaction error code, 0 if successful
************************************************************************************************************************/
int Si2176_LoadFirmware (L1_Si2176_Context *Si2176,unsigned char* firmwareTable,int lines)
{
    //int return_code = 0;
    int line;

  /* for each 8 bytes in FIRMWARE_TABLE */
    for (line = 0; line < lines; line++)
  {
     /* send that 8 byte I2C command to Si2176 */
        if (Si2176_L1_API_Patch(Si2176, wait_for_cts, wait_for_response, 8, firmwareTable+8*line) != 0)
    {

          return ERROR_Si2176_LOADING_FIRMWARE;
        }
     }
   
     return 0;
}

/************************************************************************************************************************
  NAME: Si2176_StartFirmware
  DESCRIPTION: Start Si2176 firmware (put the Si2176 into run mode)
  Parameter:   Si2176 Context (I2C address)
  Parameter (passed by Reference):  ExitBootloadeer Response Status byte : tunint, atvint, dtvint, err, cts
  Returns:     I2C transaction error code, 0 if successful
************************************************************************************************************************/
int Si2176_StartFirmware (L1_Si2176_Context *Si2176, Si2176_CmdReplyObj *rsp)
{

    if (Si2176_L1_EXIT_BOOTLOADER(Si2176,wait_for_cts,wait_for_response, Si2176_EXIT_BOOTLOADER_CMD_FUNC_TUNER, Si2176_EXIT_BOOTLOADER_CMD_CTSIEN_OFF, rsp) != 0)
  {
        return ERROR_Si2176_STARTING_FIRMWARE;
    }

    return 0;
}

/************************************************************************************************************************
  NAME: Si2176_LoadVideofilter
  DESCRIPTION:        Load video filters from vidfiltTable in Si2176_write_xTV_video_coeffs.h file into Si2176
  Programming Guide Reference:    Flowchart A.4 (Download Video Filters flowchart)

  Parameter:  Si2176 Context (I2C address)
  Parameter:  pointer to video filter table array
  Parameter:  number of lines in video filter table array (size in bytes / BYTES_PER_LINE)
  Returns:    Si2176/I2C transaction error code, 0 if successful
************************************************************************************************************************/
int Si2176_LoadVideofilter (L1_Si2176_Context *Si2176,unsigned char* vidfiltTable,int lines)
{
#define BYTES_PER_LINE 8
    int line;

  /* for each 8 bytes in VIDFILT_TABLE */
    for (line = 0; line < lines; line++)
  {
    /* send that 8 byte I2C command to Si2176 */
        if (Si2176_L1_API_Patch(Si2176, wait_for_cts, wait_for_response, BYTES_PER_LINE, vidfiltTable+BYTES_PER_LINE*line) != 0)
    {
             return ERROR_Si2176_SENDING_COMMAND;
        }
    }
    return 0;
}


/************************************************************************************************************************
  NAME: Si2176_Init
  DESCRIPTION:Reset and Initialize Si2176
  Parameter:  Si2176 Context (I2C address)
  Returns:    I2C transaction error code, 0 if successful
************************************************************************************************************************/
int Si2176_Init(L1_Si2176_Context *Si2176)
{
    int return_code;

  /* Reset Si2176 */
  /* TODO: SendRSTb requires porting to toggle the RSTb line low -> high */
    SendRSTb();

  if ((return_code=(Si2176_PowerUpWithPatch(Si2176))) != 0)   /* PowerUp into bootloader */
       return return_code;
  /* At this point, FW is loaded and started.  Return 0*/
  return 0;
}
/************************************************************************************************************************
  NAME: Si2176_ATV_Channel_Scan_M 
  DESCRIPTION: Performs a channel scan for NTSC (System M) of the band 
  Programming Guide Reference:    Flowchart A.11.0 and A11.1 (ATV Channel Scan flowchart for System M)

  Parameter:  Pointer to Si2176 Context (I2C address)
  Parameter:  starting Frequency Hz
  Parameter:  ending Frequency Hz
  Parameter:  min RSSI dBm
  Parameter:  max RSSI dBm
  Parameter:  min SNR 1/2 dB
  Parameter:  max SNR 1/2 dB
  Returns:    0 if successful, otherwise an error.
************************************************************************************************************************/
int Si2176_ATV_Channel_Scan_M(L1_Si2176_Context *Si2176, unsigned long rangeMinHz, unsigned long rangeMaxHz, int minRSSIdBm, int maxRSSIdBm, int minSNRHalfdB, int maxSNRHalfdB)
{
    Si2176_CmdReplyObj rsp;

    #define SCAN_INTERVAL 1000000
    #define CHANNEL_BANDWIDTH 6000000
  #define CHANNEL_NOT_FOUND 0

    unsigned long freq;
  int i;

  /*Clear the channel list size and channel array */
  ChannelListSize=0;

  for (i=0; i< MAX_POSSIBLE_CHANNELS;i++)
    ChannelList[i]=0;
  /* configure the VideoMode property to System M, NTSC*/
    prop.atv_video_mode.video_sys = Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_M;   /* M ATV demodulation */
    prop.atv_video_mode.color     = Si2176_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;    /* PAL_NTSC color system */
    prop.atv_video_mode.trans     = Si2176_ATV_VIDEO_MODE_PROP_TRANS_TERRESTRIAL;   /* set trans to Terrestrial */
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_VIDEO_MODE_PROP, &prop, &rsp) != 0)
    {
       return ERROR_Si2176_SENDING_COMMAND;
    }
    /* configure the RSQ / RSSI threshold properties */
    prop.atv_rsq_rssi_threshold.lo = minRSSIdBm;
    prop.atv_rsq_rssi_threshold.hi = maxRSSIdBm;

    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_RSQ_RSSI_THRESHOLD_PROP, &prop, &rsp) != 0)
    {
       return ERROR_Si2176_SENDING_COMMAND;
    }

  /* configure the RSQ / SNR threshold properties */
    prop.atv_rsq_snr_threshold.lo = minSNRHalfdB;
    prop.atv_rsq_snr_threshold.hi = maxSNRHalfdB;

    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_RSQ_SNR_THRESHOLD_PROP, &prop, &rsp) != 0)
    {
      return ERROR_Si2176_SENDING_COMMAND;
    }

  /* setup IEN properties to enable TUNINT on TC  */
    prop.tuner_ien.tcien     =  Si2176_TUNER_IEN_PROP_TCIEN_ENABLE;
    prop.tuner_ien.rssilien  =  Si2176_TUNER_IEN_PROP_RSSILIEN_DISABLE;
    prop.tuner_ien.rssihien  =  Si2176_TUNER_IEN_PROP_RSSIHIEN_DISABLE;

    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_TUNER_IEN_PROP, &prop, &rsp) != 0)
    {
      return ERROR_Si2176_SENDING_COMMAND;
    }

   /* setup IEN properties to enable ATVINT on CHL  */
    prop.atv_ien.chlien    =  Si2176_ATV_IEN_PROP_CHLIEN_ENABLE;
    prop.atv_ien.pclien    =  Si2176_ATV_IEN_PROP_PCLIEN_DISABLE;
    prop.atv_ien.dlien     =  Si2176_ATV_IEN_PROP_DLIEN_DISABLE;
    prop.atv_ien.snrlien   =  Si2176_ATV_IEN_PROP_SNRLIEN_DISABLE;
    prop.atv_ien.snrhien   =  Si2176_ATV_IEN_PROP_SNRHIEN_DISABLE;
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_IEN_PROP, &prop, &rsp) != 0)
    {
      return ERROR_Si2176_SENDING_COMMAND;
    }
    /* setup ATV audio property for wide SIF scanning*/
    prop.atv_audio_mode.audio_sys    =  Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_DEFAULT;
    prop.atv_audio_mode.chan_bw    =  Si2176_ATV_AUDIO_MODE_PROP_CHAN_BW_DEFAULT;
    prop.atv_audio_mode.demod_mode    =  Si2176_ATV_AUDIO_MODE_PROP_DEMOD_MODE_SIF;
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_AUDIO_MODE_PROP, &prop, &rsp) != 0)
    {
      return ERROR_Si2176_SENDING_COMMAND;
    }
   /* setup AFC acquistion range property to 1.5MHz for scanning */
    prop.atv_afc_range.range_khz    =  1500;
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_AFC_RANGE_PROP, &prop, &rsp) != 0)
    {
      return ERROR_Si2176_SENDING_COMMAND;
    }
   /* Start Scanning */
    for (freq=rangeMinHz; freq < rangeMaxHz; )
    {

    /* before calling tune provide a callback stub that the user can update the frequency */
    /* if user requested abort then break from the loop */
    if (UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
      break;

    /* Call the Tune command to tune the frequency */
    /* if successful (a station was found) then the return value will be 0. */
    if (!Si2176_Tune (Si2176, Si2176_TUNER_TUNE_FREQ_CMD_MODE_ATV, freq, &rsp ))
    {

            /* Get ATV status */
      if (Si2176_L1_ATV_STATUS (Si2176, wait_for_cts, wait_for_response, Si2176_ATV_STATUS_CMD_INTACK_OK, &rsp))
      {
        return ERROR_Si2176_SENDING_COMMAND;
      }


      /* Add the afc_freq (khz) to the center frequency and add to the channel list */
      ChannelList[ChannelListSize]= freq + (rsp.atv_status.afc_freq * 1000);
      /* Update the callback to indicate the channel is found */
      /* if user requested abort then break from the loop */
      if (UpdateChannelScanFrequency(freq + (rsp.atv_status.afc_freq * 1000), ChannelListSize+1))
        break;

            freq = ChannelList[ChannelListSize++] + CHANNEL_BANDWIDTH;
         }
         else  /* We didn't find a station at this frequency so increment and move on */
         {
        /* if user requested abort then break from the loop */
      if (UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
        break;
      /*  channel not found! **/
             freq += SCAN_INTERVAL;
         }
    }
    /* Set AFC Range back to 100  */
    prop.atv_afc_range.range_khz    =  100;
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_AFC_RANGE_PROP, &prop, &rsp) != 0)
    {
        return ERROR_Si2176_SENDING_COMMAND;
    }

 return 0;
}
/************************************************************************************************************************
  NAME: Si2176_ATV_Channel_Scan_PAL
  DESCRIPTION: Performs a channel scan for PAL (Systems B/G, D/K, L/L', and I) of the band 
  Programming Guide Reference:    Flowchart A.10.0 - A10.3 (ATV Channel Scan flowchart for PAL)

  NOTE: this function requires an external sound processor to determine the PAL standard.  The user is 
  required to implement the functions: L1_InitSoundProcessor(); and L1_AcquireSoundStandard(..);

  Parameter:  Pointer to Si2176 Context (I2C address)
  Parameter:  starting Frequency Hz
  Parameter:  ending Frequency Hz
  Parameter:  min RSSI dBm
  Parameter:  max RSSI dBm
  Parameter:  min SNR 1/2 dB
  Parameter:  max SNR 1/2 dB
  Returns:    0 if successful, otherwise an error.
************************************************************************************************************************/
int Si2176_ATV_Channel_Scan_PAL(L1_Si2176_Context *Si2176, unsigned long rangeMinHz, unsigned long rangeMaxHz, int minRSSIdBm, int maxRSSIdBm, int minSNRHalfdB, int maxSNRHalfdB)
{
    Si2176_CmdReplyObj rsp;
  #define VHF_MAX 300000000
    #define SCAN_INTERVAL 1000000
  #define CHANNEL_NOT_FOUND 0
  char standard = Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B;
    unsigned long freq;
  unsigned long channelIncrement;
  char posModulation;  /* flag for pos or neg modulation */
  int i;

  /*Clear the channel list size and channel array */
  ChannelListSize=0;

  for (i=0; i< MAX_POSSIBLE_CHANNELS;i++)
  {
    ChannelList[i]=0;
    ChannelType[i][0]='\0';
  }
    /* configure the RSQ / RSSI threshold properties */
    prop.atv_rsq_rssi_threshold.lo = minRSSIdBm;
    prop.atv_rsq_rssi_threshold.hi = maxRSSIdBm;

    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_RSQ_RSSI_THRESHOLD_PROP, &prop, &rsp) != 0)
    {
       return ERROR_Si2176_SENDING_COMMAND;
    }
 /* configure the RSQ / SNR threshold properties */
    prop.atv_rsq_snr_threshold.lo = minSNRHalfdB;
    prop.atv_rsq_snr_threshold.hi = maxSNRHalfdB;

    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_RSQ_SNR_THRESHOLD_PROP, &prop, &rsp) != 0)
    {
      return ERROR_Si2176_SENDING_COMMAND;
    }
  /* setup IEN properties to enable TUNINT on TC  */
    prop.tuner_ien.tcien     =  Si2176_TUNER_IEN_PROP_TCIEN_ENABLE;
    prop.tuner_ien.rssilien  =  Si2176_TUNER_IEN_PROP_RSSILIEN_DISABLE;
    prop.tuner_ien.rssihien  =  Si2176_TUNER_IEN_PROP_RSSIHIEN_DISABLE;

    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_TUNER_IEN_PROP, &prop, &rsp) != 0)
    {
      return ERROR_Si2176_SENDING_COMMAND;
    }

   /* setup IEN properties to enable ATVINT on CHL  */
  prop.atv_ien.chlien    =  Si2176_ATV_IEN_PROP_CHLIEN_ENABLE;
    prop.atv_ien.pclien    =  Si2176_ATV_IEN_PROP_PCLIEN_DISABLE;
    prop.atv_ien.dlien     =  Si2176_ATV_IEN_PROP_DLIEN_DISABLE;
    prop.atv_ien.snrlien   =  Si2176_ATV_IEN_PROP_SNRLIEN_DISABLE;
    prop.atv_ien.snrhien   =  Si2176_ATV_IEN_PROP_SNRHIEN_DISABLE;
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_IEN_PROP, &prop, &rsp) != 0)
    {
      return ERROR_Si2176_SENDING_COMMAND;
    }
  /* setup ATV audio property for wide SIF scanning*/
    prop.atv_audio_mode.audio_sys    =  Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_DEFAULT;
    prop.atv_audio_mode.chan_bw    =  Si2176_ATV_AUDIO_MODE_PROP_CHAN_BW_DEFAULT;
    prop.atv_audio_mode.demod_mode    =  Si2176_ATV_AUDIO_MODE_PROP_DEMOD_MODE_SIF;
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_AUDIO_MODE_PROP, &prop, &rsp) != 0)
    {
      return ERROR_Si2176_SENDING_COMMAND;
    }
   /* setup AFC acquistion range property to 1.5MHz for scanning */
    prop.atv_afc_range.range_khz    =  1500;
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_AFC_RANGE_PROP, &prop, &rsp) != 0)
    {
      return ERROR_Si2176_SENDING_COMMAND;
    }
   /* Start Scanning */
    for (freq=rangeMinHz; freq < rangeMaxHz; )
    {
    /* before calling tune provide a callback stub that the user can update the frequency */
    /* if user requested abort then break from the loop */
    if (UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
      break;
    /* set the modulation flag to 0 (neg) */
    posModulation=0;
    /* Negative Modulation configure the VideoMode property to System DK, PAL*/
    prop.atv_video_mode.video_sys = Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_DK;    /* M ATV demodulation */
    prop.atv_video_mode.color     = Si2176_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;    /* PAL_NTSC color system */
    prop.atv_video_mode.trans     = Si2176_ATV_VIDEO_MODE_PROP_TRANS_TERRESTRIAL;   /* set trans to Terrestrial */
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_VIDEO_MODE_PROP, &prop, &rsp) != 0)
    {
       return ERROR_Si2176_SENDING_COMMAND;
    }

    /* Call the Tune command to tune the frequency */
    /* if successful (a station was found) then the return value will be 0. */
    if (!Si2176_Tune (Si2176, Si2176_TUNER_TUNE_FREQ_CMD_MODE_ATV, freq, &rsp ))
    {
      posModulation = 0;
         }
         else  /* We didn't find a station so try positive modulation */
         {
      /* Pos Modulation configure the VideoMode property to System DK, PAL*/
      prop.atv_video_mode.video_sys = Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_L;   /* L ATV demodulation */
      prop.atv_video_mode.color     = Si2176_ATV_VIDEO_MODE_PROP_COLOR_SECAM;   /* SECAM color system */
      prop.atv_video_mode.trans     = Si2176_ATV_VIDEO_MODE_PROP_TRANS_TERRESTRIAL;   /* set trans to Terrestrial */
      if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_VIDEO_MODE_PROP, &prop, &rsp) != 0)
      {
         return ERROR_Si2176_SENDING_COMMAND;
      }
      /* Call the Tune command to tune the frequency */
      /* if successful (a station was found) then the return value will be 0. */
      if (!Si2176_Tune (Si2176, Si2176_TUNER_TUNE_FREQ_CMD_MODE_ATV, freq, &rsp ))
      {
        posModulation=1;
      }
      else
      {
            /* if user requested abort then break from the loop */
          if (UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
            break;

        /* we didn't find any channels goto flowchart section B */
        freq += SCAN_INTERVAL;
        continue;
      }
         }
    /* Initialize the sound processor.   This may or may not be required for your application */
    L1_InitSoundProcessor();
    /* Run the sound processor and return the standard(s) */
    #define SOUND_PROCESSOR_TIMEOUT 10
    L1_AcquireSoundStandard(SOUND_PROCESSOR_TIMEOUT , &standard);
    if ((standard == Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B) || (standard == Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_GH))
    {
      /* check for positive modulation */
      if (posModulation)
      {
            /* if user requested abort then break from the loop */
          if (UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
            break;

        /* goto flowchart section B */
        freq += SCAN_INTERVAL;
        continue;
      }
      else
      {
        if (freq < VHF_MAX)
        {
          ChannelType[ChannelListSize][0]='B';
          ChannelType[ChannelListSize][1]='\0';
        }
        else
        {
          ChannelType[ChannelListSize][0]='G';
          ChannelType[ChannelListSize][1]='H';
          ChannelType[ChannelListSize][2]='\0';
        }
      }
    }
    else if (standard == Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_I)
    {
        if (posModulation)
        {
                /* if user requested abort then break from the loop */
              if (UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
                break;

          /* goto flowchart section B */
          freq += SCAN_INTERVAL;
          continue;
        }
        else
        {
          ChannelType[ChannelListSize][0]='I';
          ChannelType[ChannelListSize][1]='\0';
        }
    }
    else if ((standard == Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_L) || (standard == Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_DK))
    {
        if (posModulation)
        {
          ChannelType[ChannelListSize][0]='L';
          ChannelType[ChannelListSize][1]='\0';
        }
        else
        {
          ChannelType[ChannelListSize][0]='D';
          ChannelType[ChannelListSize][1]='K';
          ChannelType[ChannelListSize][2]='\0';
        }
    }
    else
    {
      /* standard not found */
            /* if user requested abort then break from the loop */
            if (UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
          break;

      /* goto flowchart section B */
      freq += SCAN_INTERVAL;
      continue;
    }
    /* if we got here, then we have a valid channel with a channelType */
    /* Get ATV status */
    if (Si2176_L1_ATV_STATUS (Si2176, wait_for_cts, wait_for_response, Si2176_ATV_STATUS_CMD_INTACK_OK, &rsp))
    {
      return ERROR_Si2176_SENDING_COMMAND;
    }
    if (ChannelType[ChannelListSize][0]=='B')
    {
      /* Add the afc_freq (khz) to the center frequency and add to the channel list */
      ChannelList[ChannelListSize]= freq + (rsp.atv_status.afc_freq * 1000)-500000;
      channelIncrement = 7000000;
    }
    else
    {
    /* Add the afc_freq (khz) to the center frequency and add to the channel list */
      ChannelList[ChannelListSize]= freq + (rsp.atv_status.afc_freq * 1000);
      channelIncrement = 8000000;
    }
    /* Update the callback to indicate the channel is found */
    /* if user requested abort then break from the loop */
    if (UpdateChannelScanFrequency(ChannelList[ChannelListSize], ChannelListSize+1))
      break;
    /* go to the next frequency in the loop */
    freq = ChannelList[ChannelListSize++] + channelIncrement;
    }
    /* Set AFC Range back to 100  */
    prop.atv_afc_range.range_khz    =  100;
    if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_AFC_RANGE_PROP, &prop, &rsp) != 0)
    {
        return ERROR_Si2176_SENDING_COMMAND;
    }

 return 0;
}


/*************************************************************************************************************
  Made by Semco API for compatible Si2173 API
 ************************************************************************************************************************/

 /************************************************************************************************************************
  configureSi2176 function
  Use:        Setup Si2176 output ports and clocks for EVB defaults
  Parameter:  Pointer to Si2176 Context (I2C address)
              크리스탈 외부 또는 내부 사용하는지 판단 : bXTal_Internal_External - XTAL_INTERNAL/XTAL_EXTERNAL
  Returns:    I2C transaction error code
************************************************************************************************************************/
int configureSi2176 (L1_Si2176_Context *Si2176, Si2176_CmdReplyObj  *rsp1, Si2176_PropObj *lpprop, unsigned char bXTal_Internal_External) 
{

    int return_code;
  return_code = 0;



    /* Setting DTV_CONFIG_IF_PORT_PROP property */
    lpprop->dtv_config_if_port.dtv_out_type   = Si2176_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LIF_IF1;  /* Use DLIF (LIF_IF1) */

    lpprop->dtv_config_if_port.dtv_agc_source = Si2176_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_INTERNAL; /* Use internal AGC only */
    
    if (Si2176_L1_SetProperty2(Si2176, wait_for_response, wait_for_cts, Si2176_DTV_CONFIG_IF_PORT_PROP, lpprop, rsp1) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
    }
    /* Setting DTV_LIF_FREQ_PROP */
    lpprop->dtv_lif_freq.offset = 5000;             /* set DLIF center frequency (to 5MHz) */
    if (Si2176_L1_SetProperty2(Si2176, wait_for_response, wait_for_cts, Si2176_DTV_LIF_FREQ_PROP, lpprop, rsp1) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
    }

    /* Setting DTV_MODE_PROP property */
    lpprop->dtv_mode.bw = Si2176_DTV_MODE_PROP_BW_BW_6MHZ;        /* DTV BW 6MHz */
    lpprop->dtv_mode.invert_spectrum = Si2176_DTV_MODE_PROP_INVERT_SPECTRUM_INVERTED; /* inverted spectrum */
    lpprop->dtv_mode.modulation = Si2176_DTV_MODE_PROP_MODULATION_DVBT;     /* DVBT DTV demodulation */
    if (Si2176_L1_SetProperty2(Si2176, wait_for_response, wait_for_cts, Si2176_DTV_MODE_PROP, lpprop, rsp1) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
    }

#if 1
    /* Requester : Kwon Jeoung Hun */
  /* modify code by yooheeyong 20101006 */
  /* use the external xtal */
  if(bXTal_Internal_External == SI2176_XTAL_EXTERNAL)
  {
     /* Setting CONFIG_PINS */
    if (Si2176_L1_CONFIG_PINS (Si2176, wait_for_cts, wait_for_response,   /* turn off BCLK1 and XOUT */
                      Si2176_CONFIG_PINS_CMD_GPIO1_MODE_NO_CHANGE,
                      Si2176_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ,
                      Si2176_CONFIG_PINS_CMD_GPIO2_MODE_NO_CHANGE,
                      Si2176_CONFIG_PINS_CMD_GPIO2_READ_DO_NOT_READ,
                      Si2176_CONFIG_PINS_CMD_GPIO3_MODE_NO_CHANGE,
                      Si2176_CONFIG_PINS_CMD_GPIO3_READ_DO_NOT_READ,
              Si2176_CONFIG_PINS_CMD_BCLK1_MODE_XOUT,  // 20100818 jhkwon
              Si2176_CONFIG_PINS_CMD_BCLK1_READ_DO_NOT_READ,
              Si2176_CONFIG_PINS_CMD_XOUT_MODE_DISABLE,
              rsp1) !=0) {
      return ERROR_Si2176_SENDING_COMMAND;
    }
  }else{
     /* Setting CONFIG_PINS */
    if (Si2176_L1_CONFIG_PINS (Si2176, wait_for_cts, wait_for_response,   /* turn off BCLK1 and XOUT */
                      Si2176_CONFIG_PINS_CMD_GPIO1_MODE_NO_CHANGE,
                      Si2176_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ,
                      Si2176_CONFIG_PINS_CMD_GPIO2_MODE_NO_CHANGE,
                      Si2176_CONFIG_PINS_CMD_GPIO2_READ_DO_NOT_READ,
                      Si2176_CONFIG_PINS_CMD_GPIO3_MODE_NO_CHANGE,
                      Si2176_CONFIG_PINS_CMD_GPIO3_READ_DO_NOT_READ,
              Si2176_CONFIG_PINS_CMD_BCLK1_MODE_DISABLE,  
              Si2176_CONFIG_PINS_CMD_BCLK1_READ_DO_NOT_READ,
              Si2176_CONFIG_PINS_CMD_XOUT_MODE_DISABLE,
              rsp1) !=0) {
      return ERROR_Si2176_SENDING_COMMAND;
    }
  }
#endif



    /* Setting ATV_VIDEO_MODE_PROP property */
    lpprop->atv_video_mode.video_sys = Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_GH;   /* GH ATV demodulation */
    lpprop->atv_video_mode.color     = Si2176_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;   /* PAL_NTSC color system */
    if (Si2176_L1_SetProperty2(Si2176, wait_for_response, wait_for_cts, Si2176_ATV_VIDEO_MODE_PROP, lpprop, rsp1) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
    }

/*-------------- add by yooheeyong 20110201 -----------*/
/* To solve the problem in Germany                     */

  lpprop->atv_min_lvl_lock.thrs = 34;
  if (Si2176_L1_SetProperty2(Si2176, wait_for_cts, wait_for_response, Si2176_ATV_MIN_LVL_LOCK_PROP, lpprop, rsp1) != 0)
  {
    return ERROR_Si2176_SENDING_COMMAND;
  }

/*-----------------------------------------------------*/


  /* lock 관련 체크 위해 추가 comment by kim nam min 20100813 */
  /*----- begin -----*/
    lpprop->atv_ien.chlien  = Si2176_ATV_IEN_PROP_CHLIEN_ENABLE;    //aded for quick check of ATV state
    lpprop->atv_ien.dlien   = Si2176_ATV_IEN_PROP_DLIEN_DISABLE;
    lpprop->atv_ien.pclien  = Si2176_ATV_IEN_PROP_PCLIEN_DISABLE;
    lpprop->atv_ien.snrhien = Si2176_ATV_IEN_PROP_SNRHIEN_DISABLE;
    lpprop->atv_ien.snrlien = Si2176_ATV_IEN_PROP_SNRLIEN_DISABLE;
    if(Si2176_L1_SetProperty2(Si2176, wait_for_response, wait_for_cts, Si2176_ATV_IEN_PROP, lpprop, rsp1) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
    }

  /* Property fields required for the wait for TUNINT to work */
    lpprop->master_ien.tunien = Si2176_MASTER_IEN_PROP_TUNIEN_ON;
    lpprop->master_ien.atvien = Si2176_MASTER_IEN_PROP_ATVIEN_ON;
    lpprop->master_ien.dtvien = Si2176_MASTER_IEN_PROP_DTVIEN_ON;
    if(Si2176_L1_SetProperty2(Si2176, wait_for_response, wait_for_cts, Si2176_MASTER_IEN_PROP, lpprop, rsp1) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
  }

    lpprop->tuner_ien.tcien  = Si2176_TUNER_IEN_PROP_TCIEN_ENABLE;    //aded for quick check of tune state
    lpprop->tuner_ien.rssihien  = Si2176_TUNER_IEN_PROP_RSSIHIEN_DISABLE;
    lpprop->tuner_ien.rssilien  = Si2176_TUNER_IEN_PROP_RSSILIEN_DISABLE;
    if(Si2176_L1_SetProperty2(Si2176, wait_for_response, wait_for_cts, Si2176_TUNER_IEN_PROP, lpprop, rsp1) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
  }
    lpprop->dtv_ien.chlien  = Si2176_DTV_IEN_PROP_CHLIEN_ENABLE;    //aded for quick check of DTV state
    if (Si2176_L1_SetProperty2(Si2176, wait_for_response, wait_for_cts, Si2176_DTV_IEN_PROP, lpprop, rsp1) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
  }
    /*----- end -----*/

    // added by yooheeyong 20100819 
    // amp 0 ~ 255, default = 38(change 20100819), offset 0 ~ 255, default = 135
    lpprop->atv_sif_out.offset = 135;
    lpprop->atv_sif_out.amp    = 38;
    if (Si2176_L1_SetProperty2(Si2176, wait_for_response, wait_for_cts, Si2176_ATV_SIF_OUT_PROP, lpprop, rsp1) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
    }    

#if 0
    /* load video filter comment by kim nam min 20100813 */
    Si2176_LoadVideofilter(Si2176);
#else
    /* load ATV video filter file */
  #ifdef USING_ATV_FILTER
    if ((return_code = Si2176_LoadVideofilter(Si2176,ATV_VIDFILT_TABLE,ATV_VIDFILT_LINES)) != 0)
       return return_code;
  #endif

  /* load DTV video filter file */
  #ifdef USING_DTV_FILTER
     if ((return_code = Si2176_LoadVideofilter(Si2176,DTV_VIDFILT_TABLE,DTV_VIDFILT_LINES)) != 0)
       return return_code;
  #endif
#endif
    return 0;
}

/************************************************************************************************************************
  Tune function
  Use:        Tune Si2176 in specified mode (ATV/DTV) at user entered center frequency
  Parameter:  Pointer to Si2176 Context (I2C address) and mode
  Returns:    I2C transaction error code
************************************************************************************************************************/
int Tune(L1_Si2176_Context *Si2176, unsigned char mode, Si2176_CmdReplyObj *rsp1, unsigned long rf_frequency) 
{
    unsigned long freq;

  freq = 0;

  freq = rf_frequency;

  if ((freq < 43000000) || (freq  > 1002000000)) // Response Out of Range
  { 
    return ERROR_Si2176_PARAMETER_OUT_OF_RANGE;
    }

    if (Si2176_L1_TUNER_TUNE_FREQ (Si2176, wait_for_cts, wait_for_response,
                mode,
                freq,
                rsp1) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;
    }

    return 0;
}


/************************************************************************************************************************
  TunerStatus function
  Use:        Reports tuner status from TUNER_STATUS response
  Parameter:  Pointer to Si2176 Context (I2C address)
  Returns:    I2C transaction error code
************************************************************************************************************************/
int TunerStatus (L1_Si2176_Context *Si2176, Si2176_CmdReplyObj  *rsp1) {

    if (Si2176_L1_TUNER_STATUS(Si2176, wait_for_cts, 1, Si2176_TUNER_STATUS_CMD_INTACK_CLEAR, rsp1) != 0) { /* execute TUNER_STATUS and always read response */
        return ERROR_Si2176_SENDING_COMMAND;
    }

    return 0;
}

/************************************************************************************************************************
  ATVStatus string arrays
************************************************************************************************************************/
const char ATV_STATUS_RESPONSE_AUDIO_CHAN_BW[][15] = {
    "RSVD",
    "4X_OVERMOD",
    "8X_OVERMOD",
    "12X_OVERMOD",
    "7P5_KHZ_OFFSET",
    "15_KHZ_OFFSET",
    "30_KHZ_OFFSET",
    "75_KHZ_OFFSET",
    "150_KHZ_OFFSET"
};

const char ATV_STATUS_RESPONSE_VIDEO_SYS[][3] = {
    "B",
    "GH",
    "M",
    "N",
    "I",
    "DK",
    "L",
    "LP"
};

const char ATV_STATUS_RESPONSE_AUDIO_SYS[][11] = {
    "RSVD",
    "MONO",
    "MONO_NICAM",
    "A2",
    "A2_DK2",
    "A2_DK3",
    "BTSC",
    "EIAJ",
    "SCAN"
};

const char ATV_STATUS_RESPONSE_AUDIO_DEMOD_MODE[][4] = {
    "SIF",
    "AM",
    "FM1",
    "FM2"
};

/************************************************************************************************************************
  ATVStatus function
  Use:        Reports tuner status from ATV_STATUS response
  Parameter:  Pointer to Si2176 Context (I2C address)
  Returns:    I2C transaction error code
************************************************************************************************************************/
int ATVStatus (L1_Si2176_Context *Si2176, Si2176_CmdReplyObj  *rsp1) {

    if (Si2176_L1_ATV_STATUS(Si2176, wait_for_cts, 1, Si2176_ATV_STATUS_CMD_INTACK_CLEAR, rsp1) != 0) { /* execute ATV_STATUS and always read response */
        return ERROR_Si2176_SENDING_COMMAND;
    }else{}
  
    return 0;
}

/************************************************************************************************************************
  DTVStatus string arrays
************************************************************************************************************************/
const char DTV_STATUS_RESPONSE_BW[][8] = {
    "BW_6MHZ",
    "BW_7MHZ",
    "BW_8MHZ",
    "RSVD"
};

const char DTV_STATUS_RESPONSE_MODULATION[][7] = {
    "ATSC",
    "QAM_US",
    "DVBT",
    "DVBC",
    "ISDBT",
    "ISDBC",
    "RVS"
};

/************************************************************************************************************************
  DTVStatus function
  Use:        Reports tuner status from DTV_STATUS response
  Parameter:  Pointer to Si2176 Context (I2C address)
  Returns:    I2C transaction error code
************************************************************************************************************************/
int DTVStatus (L1_Si2176_Context *Si2176, Si2176_CmdReplyObj  *rsp1) {

    if (Si2176_L1_DTV_STATUS(Si2176, wait_for_cts, 1, Si2176_DTV_STATUS_CMD_INTACK_CLEAR, rsp1) != 0) { /* execute DTV_STATUS and always read response */
        return ERROR_Si2176_SENDING_COMMAND;
    }else{}
    if((rsp1->dtv_status.bw < 6) || (rsp1->dtv_status.bw > 8))
    rsp1->dtv_status.bw = 9;
  else{}
    if(rsp1->dtv_status.modulation > 5)
    rsp1->dtv_status.modulation = 6;
  else{}

    return 0;
}




/************************************************************************************************************************
  Xout_On function
  Use:        Turns Si2176 XOUT on
  Parameter:  Pointer to Si2176 Context (I2C address)
  Returns:    I2C transaction error code
************************************************************************************************************************/
int Xout_On  (L1_Si2176_Context *Si2176, Si2176_CmdReplyObj *rsp1) {

    if (Si2176_L1_CONFIG_PINS (Si2176, wait_for_cts, wait_for_response,
                                      Si2176_CONFIG_PINS_CMD_GPIO1_MODE_NO_CHANGE,
                                      Si2176_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ,
                                      Si2176_CONFIG_PINS_CMD_GPIO2_MODE_NO_CHANGE,
                                      Si2176_CONFIG_PINS_CMD_GPIO2_READ_DO_NOT_READ,
                                      Si2176_CONFIG_PINS_CMD_GPIO3_MODE_NO_CHANGE,
                                      Si2176_CONFIG_PINS_CMD_GPIO3_READ_DO_NOT_READ,
                      Si2176_CONFIG_PINS_CMD_BCLK1_MODE_DISABLE,
                      Si2176_CONFIG_PINS_CMD_BCLK1_READ_DO_NOT_READ,
                      Si2176_CONFIG_PINS_CMD_XOUT_MODE_XOUT,
                      rsp1) != 0) {
         return ERROR_Si2176_SENDING_COMMAND;
    }
    
    return 0;
}

/************************************************************************************************************************
  Xout_Off function
  Use:        Turns Si2176 XOUT off
  Parameter:  Pointer to Si2170 Context (I2C address)
  Returns:    I2C transaction error code
************************************************************************************************************************/
int Xout_Off  (L1_Si2176_Context *Si2176, Si2176_CmdReplyObj *rsp1) {

    if (Si2176_L1_CONFIG_PINS (Si2176, wait_for_cts, wait_for_response,
                                      Si2176_CONFIG_PINS_CMD_GPIO1_MODE_NO_CHANGE,
                                      Si2176_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ,
                                      Si2176_CONFIG_PINS_CMD_GPIO2_MODE_NO_CHANGE,
                                      Si2176_CONFIG_PINS_CMD_GPIO2_READ_DO_NOT_READ,
                                      Si2176_CONFIG_PINS_CMD_GPIO3_MODE_NO_CHANGE,
                                      Si2176_CONFIG_PINS_CMD_GPIO3_READ_DO_NOT_READ,
                      Si2176_CONFIG_PINS_CMD_BCLK1_MODE_DISABLE,
                      Si2176_CONFIG_PINS_CMD_BCLK1_READ_DO_NOT_READ,
                      Si2176_CONFIG_PINS_CMD_XOUT_MODE_DISABLE,
                      rsp1) != 0) {
        return ERROR_Si2176_SENDING_COMMAND;  
    }

    return 0;
}



/************************************************************************************************************************
  PowerUp function
  Use:        Send Si2176 API PowerUp Command with PowerUp to bootloader
  Parameter:  Si2176 Context (I2C address)
  Returns:    Si2176/I2C transaction error code
************************************************************************************************************************/
int PowerUp (L1_Si2176_Context *Si2176, Si2176_CmdReplyObj  *rsp1) {
  int res;
 
    if ((res = Si2176_L1_POWER_UP (Si2176, wait_for_cts, wait_for_response,
                     Si2176_POWER_UP_CMD_SUBCODE_CODE,
                     Si2176_POWER_UP_CMD_RESERVED1_RESERVED,
                     Si2176_POWER_UP_CMD_RESERVED2_RESERVED,
                 Si2176_POWER_UP_CMD_RESERVED3_RESERVED,                     
                     Si2176_POWER_UP_CMD_CLOCK_MODE_XTAL,
                     Si2176_POWER_UP_CMD_CLOCK_FREQ_CLK_24MHZ,
                     Si2176_POWER_UP_CMD_ADDR_MODE_CURRENT,
                     Si2176_POWER_UP_CMD_FUNC_BOOTLOADER,
                     Si2176_POWER_UP_CMD_CTSIEN_DISABLE,
                     Si2176_POWER_UP_CMD_WAKE_UP_WAKE_UP,
                     rsp1)) != 0) {
        return res;
    }

    return 0;
}

/************************************************************************************************************************
  PowerDown function
  Use:        Send Si2176 API PowerDown Command with PowerDown
  Parameter:  Si2176 Context (I2C address)
  Returns:    Si2176/I2C transaction error code
************************************************************************************************************************/
int PowerDown (L1_Si2176_Context *Si2176, Si2176_CmdReplyObj  *rsp1) {

  unsigned char res;

  res = Si2176_L1_POWER_DOWN (Si2176, wait_for_cts, wait_for_response,rsp1);

    if ( res != 0) {
        return res;
    }

    return 0;
}

/************************************************************************************************************************
  checkStatus function
  Use:        Read Si2176 STATUS byte and display status bits
  Parameter:  Si2176 Context (I2C address)
  Returns:    Si2176/I2C transaction error code
************************************************************************************************************************/
int CheckStatus  (L1_Si2176_Context *Si2176, Si2176_COMMON_REPLY_struct *sstatus) 
{
    unsigned char buffer[1];
  /* read STATUS byte */
    if (Si2176_pollForResponse(Si2176, 1, 1, buffer, sstatus) != 0) 
  {     
        return ERROR_Si2176_POLLING_RESPONSE;
    }
 
    return 0;
}

