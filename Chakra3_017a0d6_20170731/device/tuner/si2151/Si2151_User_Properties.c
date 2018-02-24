/*************************************************************************************
                  Silicon Laboratories Broadcast Si2151 Layer 1 API

   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
     PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.

   API user settings
   FILE: Si2151_User_Properties.c
   Supported IC : Si2151
   Compiled for ROM 61 firmware 1_1_build_6
   Revision: 0.2
   Tag:  ROM61_1_1_build_6_V0.2
   Date: October 29 2014

   (C) Copyright 2014, Silicon Laboratories, Inc. All rights reserved.

   Modify this file for the individual application.    The modified properties will be
   sent to the tuner upon initialization.
**************************************************************************************/
#define   Si2151_COMMAND_PROTOTYPES

#include "Si2151_L1_API.h"


/***********************************************************************************************************************
  Si2151_storeUserProperties function
  Use:        property preparation function
              Used to fill the prop structure with user values.
              Modify this file for the individual application.    The modified properties will be sent to the tuner
              upon initialization.
              Set the variable api->propertyWriteMode to control how the properties are written.  This flag is initialized
              in the function Si2151_L1_API_Init() .
              The options are:
              DOWNLOAD_ALWAYS -  all properties will be downloaded, regardless if they are different from default.
              DOWNLOAD_ON_CHANGE - only the properties that are different from the default settings will be downloaded.

              For most cases, the DOWNLOAD_ON_CHANGE setting is preferred.   This is the fastest and most efficient mode.

  Parameter: *prop    a property structure to be filled

  Returns:    void
 ***********************************************************************************************************************/
void          Si2151_storeUserProperties    (Si2151_PropObj   *prop) {
#ifdef    Si2151_ATV_AGC_SPEED_PROP
  prop->atv_agc_speed.if_agc_speed           = Si2151_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO ; /* (default 'AUTO') */
#endif /* Si2151_ATV_AGC_SPEED_PROP */

#ifdef    Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP
  prop->atv_agc_speed_low_rssi.if_agc_speed  = Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_158 ; /* (default '158') */
  prop->atv_agc_speed_low_rssi.thld          =  -128; /* (default  -128) */
#endif /* Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP */

#ifdef    Si2151_ATV_ARTIFICIAL_SNOW_PROP
  prop->atv_artificial_snow.gain             =    32; /* (default    32) */
  prop->atv_artificial_snow.period           = Si2151_ATV_ARTIFICIAL_SNOW_PROP_PERIOD_SHORT ; /* (default 'SHORT') */
#endif /* Si2151_ATV_ARTIFICIAL_SNOW_PROP */

#ifdef    Si2151_ATV_CONFIG_IF_PORT_PROP
  prop->atv_config_if_port.atv_out_type      = Si2151_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE_LIF_DIFF_IF ; /* (default 'LIF_DIFF_IF') */
#endif /* Si2151_ATV_CONFIG_IF_PORT_PROP */

#ifdef    Si2151_ATV_EXT_AGC_PROP
  prop->atv_ext_agc.min_10mv                 =    50; /* (default    50) */
  prop->atv_ext_agc.max_10mv                 =   200; /* (default   200) */
#endif /* Si2151_ATV_EXT_AGC_PROP */

#ifdef    Si2151_ATV_HSYNC_OUT_PROP
  prop->atv_hsync_out.polarity               = Si2151_ATV_HSYNC_OUT_PROP_POLARITY_LOW ; /* (default 'LOW') */
  prop->atv_hsync_out.width                  =    75; /* (default    75) */
  prop->atv_hsync_out.offset                 =     0; /* (default     0) */
#endif /* Si2151_ATV_HSYNC_OUT_PROP */

#ifdef    Si2151_ATV_LIF_FREQ_PROP
  prop->atv_lif_freq.offset                  =  5000; /* (default  5000) */
#endif /* Si2151_ATV_LIF_FREQ_PROP */

#ifdef    Si2151_ATV_LIF_OUT_PROP
  prop->atv_lif_out.offset                   =   148; /* (default   148) */
  prop->atv_lif_out.amp                      =   100; /* (default   100) */
#endif /* Si2151_ATV_LIF_OUT_PROP */

#ifdef    Si2151_ATV_PGA_LIMITS_PROP
  prop->atv_pga_limits.min                   =     0; /* (default     0) */
  prop->atv_pga_limits.max                   =    56; /* (default    56) */
#endif /* Si2151_ATV_PGA_LIMITS_PROP */

#ifdef    Si2151_ATV_PGA_TARGET_PROP
  prop->atv_pga_target.pga_target            =     0; /* (default     0) */
  prop->atv_pga_target.override_enable       = Si2151_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_DISABLE ; /* (default 'DISABLE') */
#endif /* Si2151_ATV_PGA_TARGET_PROP */

#ifdef    Si2151_ATV_RF_TOP_PROP
  prop->atv_rf_top.atv_rf_top                = Si2151_ATV_RF_TOP_PROP_ATV_RF_TOP_AUTO ; /* (default 'AUTO') */
#endif /* Si2151_ATV_RF_TOP_PROP */

#ifdef    Si2151_ATV_RSQ_RSSI_THRESHOLD_PROP
  prop->atv_rsq_rssi_threshold.lo            =   -70; /* (default   -70) */
#endif /* Si2151_ATV_RSQ_RSSI_THRESHOLD_PROP */

#ifdef    Si2151_ATV_VIDEO_MODE_PROP
  prop->atv_video_mode.video_sys             = Si2151_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B              ; /* (default 'B') */
  prop->atv_video_mode.invert_spectrum       = Si2151_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_INVERTED ; /* (default 'INVERTED') */
#endif /* Si2151_ATV_VIDEO_MODE_PROP */

#ifdef    Si2151_ATV_VSNR_CAP_PROP
  prop->atv_vsnr_cap.atv_vsnr_cap            =     0; /* (default     0) */
#endif /* Si2151_ATV_VSNR_CAP_PROP */

#ifdef    Si2151_CRYSTAL_TRIM_PROP
  prop->crystal_trim.xo_cap                  = Si2151_CRYSTAL_TRIM_PROP_XO_CAP_5P7PF ; // Si2151_CRYSTAL_TRIM_PROP_XO_CAP_6P7PF ; /* (default '6p7pF') */
#endif /* Si2151_CRYSTAL_TRIM_PROP */

#ifdef    Si2151_XOUT_PROP
  prop->xout.amp                             = Si2151_XOUT_PROP_AMP_HIGH ; /* (default 'HIGH') */
#endif /* Si2151_XOUT_PROP */

#ifdef    Si2151_DTV_AGC_AUTO_FREEZE_PROP
  prop->dtv_agc_auto_freeze.thld             =   255; /* (default   255) */
  prop->dtv_agc_auto_freeze.timeout          =     1; /* (default     1) */
#endif /* Si2151_DTV_AGC_AUTO_FREEZE_PROP */

#ifdef    Si2151_DTV_AGC_SPEED_PROP
  prop->dtv_agc_speed.if_agc_speed           = Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO ; /* (default 'AUTO') */
  prop->dtv_agc_speed.agc_decim              = Si2151_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF     ; /* (default 'OFF') */
#endif /* Si2151_DTV_AGC_SPEED_PROP */

#ifdef    Si2151_DTV_CONFIG_IF_PORT_PROP
  prop->dtv_config_if_port.dtv_out_type      = Si2151_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LIF_IF ; /* (default 'LIF_IF') */
#endif /* Si2151_DTV_CONFIG_IF_PORT_PROP */

#ifdef    Si2151_DTV_EXT_AGC_PROP
  prop->dtv_ext_agc.min_10mv                 =    50; /* (default    50) */
  prop->dtv_ext_agc.max_10mv                 =   200; /* (default   200) */
#endif /* Si2151_DTV_EXT_AGC_PROP */

#ifdef    Si2151_DTV_IF_AGC_SPEED_PROP
  prop->dtv_if_agc_speed.attack              = Si2151_DTV_IF_AGC_SPEED_PROP_ATTACK_AUTO ; /* (default 'AUTO') */
  prop->dtv_if_agc_speed.decay               = Si2151_DTV_IF_AGC_SPEED_PROP_DECAY_AUTO  ; /* (default 'AUTO') */
#endif /* Si2151_DTV_IF_AGC_SPEED_PROP */

#ifdef    Si2151_DTV_INITIAL_AGC_SPEED_PROP
  prop->dtv_initial_agc_speed.if_agc_speed   = Si2151_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO ; /* (default 'AUTO') */
  prop->dtv_initial_agc_speed.agc_decim      = Si2151_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_OFF     ; /* (default 'OFF') */
#endif /* Si2151_DTV_INITIAL_AGC_SPEED_PROP */

#ifdef    Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
  prop->dtv_initial_agc_speed_period.period  =     0; /* (default     0) */
#endif /* Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */

#ifdef    Si2151_DTV_INTERNAL_ZIF_PROP
  prop->dtv_internal_zif.atsc                = Si2151_DTV_INTERNAL_ZIF_PROP_ATSC_ZIF   ; /* (default 'ZIF') */
  prop->dtv_internal_zif.qam_us              = Si2151_DTV_INTERNAL_ZIF_PROP_QAM_US_ZIF ; /* (default 'ZIF') */
  prop->dtv_internal_zif.dvbt                = Si2151_DTV_INTERNAL_ZIF_PROP_DVBT_ZIF   ; /* (default 'ZIF') */
  prop->dtv_internal_zif.dvbc                = Si2151_DTV_INTERNAL_ZIF_PROP_DVBC_ZIF   ; /* (default 'ZIF') */
  prop->dtv_internal_zif.isdbt               = Si2151_DTV_INTERNAL_ZIF_PROP_ISDBT_ZIF  ; /* (default 'ZIF') */
  prop->dtv_internal_zif.isdbc               = Si2151_DTV_INTERNAL_ZIF_PROP_ISDBC_ZIF  ; /* (default 'ZIF') */
  prop->dtv_internal_zif.dtmb                = Si2151_DTV_INTERNAL_ZIF_PROP_DTMB_LIF   ; /* (default 'LIF') */
#endif /* Si2151_DTV_INTERNAL_ZIF_PROP */

#ifdef    Si2151_DTV_LIF_FREQ_PROP
  prop->dtv_lif_freq.offset                  =  5000; /* (default  5000) */
#endif /* Si2151_DTV_LIF_FREQ_PROP */

#ifdef    Si2151_DTV_LIF_OUT_PROP
  prop->dtv_lif_out.offset                   =   148; /* (default   148) */
  prop->dtv_lif_out.amp                      =    27; /* (default    27) */
#endif /* Si2151_DTV_LIF_OUT_PROP */

#ifdef    Si2151_DTV_MODE_PROP
  prop->dtv_mode.bw                          = Si2151_DTV_MODE_PROP_BW_BW_8MHZ              ; /* (default 'BW_8MHZ') */
  prop->dtv_mode.modulation                  = Si2151_DTV_MODE_PROP_MODULATION_DVBT         ; /* (default 'DVBT') */
  prop->dtv_mode.invert_spectrum             = Si2151_DTV_MODE_PROP_INVERT_SPECTRUM_NORMAL  ; /* (default 'NORMAL') */
#endif /* Si2151_DTV_MODE_PROP */

#ifdef    Si2151_DTV_PGA_LIMITS_PROP
  prop->dtv_pga_limits.min                   =    -1; /* (default    -1) */
  prop->dtv_pga_limits.max                   =    -1; /* (default    -1) */
#endif /* Si2151_DTV_PGA_LIMITS_PROP */

#ifdef    Si2151_DTV_PGA_TARGET_PROP
  prop->dtv_pga_target.pga_target            =     0; /* (default     0) */
  prop->dtv_pga_target.override_enable       = Si2151_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE_DISABLE ; /* (default 'DISABLE') */
#endif /* Si2151_DTV_PGA_TARGET_PROP */

#ifdef    Si2151_DTV_RF_AGC_SPEED_PROP
  prop->dtv_rf_agc_speed.attack              = Si2151_DTV_RF_AGC_SPEED_PROP_ATTACK_AUTO ; /* (default 'AUTO') */
  prop->dtv_rf_agc_speed.decay               = Si2151_DTV_RF_AGC_SPEED_PROP_DECAY_AUTO  ; /* (default 'AUTO') */
#endif /* Si2151_DTV_RF_AGC_SPEED_PROP */

#ifdef    Si2151_DTV_RF_TOP_PROP
  prop->dtv_rf_top.dtv_rf_top                = Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP_AUTO ; /* (default 'AUTO') */
#endif /* Si2151_DTV_RF_TOP_PROP */

#ifdef    Si2151_DTV_RSQ_RSSI_THRESHOLD_PROP
  prop->dtv_rsq_rssi_threshold.lo            =   -80; /* (default   -80) */
#endif /* Si2151_DTV_RSQ_RSSI_THRESHOLD_PROP */

#ifdef    Si2151_DTV_WB_AGC_SPEED_PROP
  prop->dtv_wb_agc_speed.attack              = Si2151_DTV_WB_AGC_SPEED_PROP_ATTACK_AUTO ; /* (default 'AUTO') */
  prop->dtv_wb_agc_speed.decay               = Si2151_DTV_WB_AGC_SPEED_PROP_DECAY_AUTO  ; /* (default 'AUTO') */
#endif /* Si2151_DTV_WB_AGC_SPEED_PROP */

#ifdef    Si2151_TUNER_BLOCKED_VCO_PROP
  prop->tuner_blocked_vco.vco_code           = 0x8000; /* (default 0x8000) */
#endif /* Si2151_TUNER_BLOCKED_VCO_PROP */

#ifdef    Si2151_TUNER_BLOCKED_VCO2_PROP
  prop->tuner_blocked_vco2.vco_code          = 0x8000; /* (default 0x8000) */
#endif /* Si2151_TUNER_BLOCKED_VCO2_PROP */

#ifdef    Si2151_TUNER_BLOCKED_VCO3_PROP
  prop->tuner_blocked_vco3.vco_code          = 0x8000; /* (default 0x8000) */
#endif /* Si2151_TUNER_BLOCKED_VCO3_PROP */

#ifdef    Si2151_TUNER_LO_INJECTION_PROP
  prop->tuner_lo_injection.band_1            = Si2151_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE ; /* (default 'HIGH_SIDE') */
  prop->tuner_lo_injection.band_2            = Si2151_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE  ; /* (default 'LOW_SIDE') */
  prop->tuner_lo_injection.band_3            = Si2151_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE  ; /* (default 'LOW_SIDE') */
#endif /* Si2151_TUNER_LO_INJECTION_PROP */

#ifdef    Si2151_TUNER_RETURN_LOSS_PROP
  prop->tuner_return_loss.config             = Si2151_TUNER_RETURN_LOSS_PROP_CONFIG_127         ; /* (default '127') */
  prop->tuner_return_loss.mode               = Si2151_TUNER_RETURN_LOSS_PROP_MODE_TERRESTRIAL   ; /* (default 'TERRESTRIAL') */
#endif /* Si2151_TUNER_RETURN_LOSS_PROP */

#ifdef    Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP
  prop->tuner_return_loss_optimize.thld                 =     0; /* (default     0) */
  prop->tuner_return_loss_optimize.config               = Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_DISABLE              ; /* (default 'DISABLE') */
  prop->tuner_return_loss_optimize.engagement_delay     =     7; /* (default     7) */
  prop->tuner_return_loss_optimize.disengagement_delay  =    10; /* (default    10) */
#endif /* Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP */

#ifdef    Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP
  prop->tuner_return_loss_optimize_2.thld               =    31; /* (default    31) */
  prop->tuner_return_loss_optimize_2.window             =     0; /* (default     0) */
  prop->tuner_return_loss_optimize_2.engagement_delay   =    15; /* (default    15) */
#endif /* Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP */

#ifdef    Si2151_TUNER_TF1_BOUNDARY_OFFSET_PROP
  prop->tuner_tf1_boundary_offset.tf1_boundary_offset   =     0; /* (default     0) */
#endif /* Si2151_TUNER_TF1_BOUNDARY_OFFSET_PROP */

}
