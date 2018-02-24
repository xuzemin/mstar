/*************************************************************************************
                  Silicon Laboratories Broadcast Si21XXC Layer 1 API

   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
     PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.

   API properties user file
   FILE: Si21XXC_User_Properties.c
   Supported IC : Si2178B,Si2190B,Si2191B,Si2191C
   Compiled for ROM 71 firmware 3_0_build_1
   Revision: 0.1
   Tag:  Si2190B_30b1_Si2178B_42b7_Si2191C_30b1_Si2191B_42b7_V0.1
   Date: August 12 2015
  (C) Copyright 2014, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/

#include "Si21XXC_L1_API.h"

/***********************************************************************************************************************
  Si21XXC_storeUserProperties function
  Use:        property preparation function
              Used to fill the prop structure with user values.
  Parameter: *prop    a property structure to be filled

  Returns:    void
 ***********************************************************************************************************************/
void          Si21XXC_storeUserProperties    (Si21XXC_PropObj   *prop) {
  SiTRACE("Si21XXC_storeUserProperties\n");
#ifdef    Si21XXC_ATV_AFC_RANGE_PROP
  prop->atv_afc_range.range_khz              =  1000; /* (default  1000) */
#endif /* Si21XXC_ATV_AFC_RANGE_PROP */

#ifdef    Si21XXC_ATV_AGC_SPEED_PROP
  prop->atv_agc_speed.if_agc_speed           = Si21XXC_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO ; /* (default 'AUTO') */
#endif /* Si21XXC_ATV_AGC_SPEED_PROP */

#ifdef    Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP
  prop->atv_agc_speed_low_rssi.if_agc_speed  = Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_158 ; /* (default '158') */
  prop->atv_agc_speed_low_rssi.thld          =  -128; /* (default  -128) */
#endif /* Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP */

#ifdef    Si21XXC_ATV_ARTIFICIAL_SNOW_PROP
  prop->atv_artificial_snow.gain             =  Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_GAIN_18DB; /* (default     0) */
  prop->atv_artificial_snow.sound            = Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_SOUND_MUTE  ; /* (default 'MUTE') */
  prop->atv_artificial_snow.period           = Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_PERIOD_LONG ; /* (default 'LONG') */
  prop->atv_artificial_snow.offset           =     0; /* (default     0) */
#endif /* Si21XXC_ATV_ARTIFICIAL_SNOW_PROP */

#ifdef    Si21XXC_ATV_AUDIO_MODE_PROP
  prop->atv_audio_mode.audio_sys             = Si21XXC_ATV_AUDIO_MODE_PROP_AUDIO_SYS_DEFAULT ; /* (default 'DEFAULT') */
  prop->atv_audio_mode.chan_bw               = Si21XXC_ATV_AUDIO_MODE_PROP_CHAN_BW_DEFAULT   ; /* (default 'DEFAULT') */
#endif /* Si21XXC_ATV_AUDIO_MODE_PROP */

#ifdef    Si21XXC_ATV_CONFIG_IF_PORT_PROP
    #if FRONTEND_IF_DEMODE_TYPE == SAMSUNG_SI21XX
    prop->atv_config_if_port.atv_out_type      = Si21XXC_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE_CVBS_IF2B_SOUND_DIFF_IF1 ; /* (default 'CVBS_IF2B_SOUND_IF2A') */
    #else
    prop->atv_config_if_port.atv_out_type      = Si21XXC_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE_LIF_DIFF_IF1 ; /* (default 'CVBS_IF2B_SOUND_IF2A') */
    #endif
#endif /* Si21XXC_ATV_CONFIG_IF_PORT_PROP */

#ifdef    Si2190B_ATV_CVBS_ATTENUATION_PROP
  prop->atv_cvbs_attenuation.threshold                  =     0; /* (default     0) */
  prop->atv_cvbs_attenuation.rate                       =     0; /* (default     0) */
  prop->atv_cvbs_attenuation.bw                         =     4; /* (default     4) */
#endif /* Si2190B_ATV_CVBS_ATTENUATION_PROP */

#ifdef    Si21XXC_ATV_CVBS_OUT_PROP
  prop->atv_cvbs_out.offset                  =    25; /* (default    25) */
  prop->atv_cvbs_out.amp                     =   200; /* (default   200) */
#endif /* Si21XXC_ATV_CVBS_OUT_PROP */

#ifdef    Si21XXC_ATV_CVBS_OUT_FINE_PROP
  prop->atv_cvbs_out_fine.offset             =   32; /* (default     0) */
  prop->atv_cvbs_out_fine.amp                =   49; /* (default   100) */
#endif /* Si21XXC_ATV_CVBS_OUT_FINE_PROP */

#ifdef    Si21XXC_ATV_IEN_PROP
  prop->atv_ien.chlien                       = Si21XXC_ATV_IEN_PROP_CHLIEN_ENABLE   ; /* (default 'ENABLE') */
  prop->atv_ien.pclien                       = Si21XXC_ATV_IEN_PROP_PCLIEN_DISABLE  ; /* (default 'DISABLE') */
  prop->atv_ien.dlien                        = Si21XXC_ATV_IEN_PROP_DLIEN_DISABLE   ; /* (default 'DISABLE') */
  prop->atv_ien.snrlien                      = Si21XXC_ATV_IEN_PROP_SNRLIEN_DISABLE ; /* (default 'DISABLE') */
  prop->atv_ien.snrhien                      = Si21XXC_ATV_IEN_PROP_SNRHIEN_DISABLE ; /* (default 'DISABLE') */
#endif /* Si21XXC_ATV_IEN_PROP */

#ifdef    Si21XXC_ATV_INT_SENSE_PROP
  prop->atv_int_sense.chlnegen               = Si21XXC_ATV_INT_SENSE_PROP_CHLNEGEN_DISABLE  ; /* (default 'DISABLE') */
  prop->atv_int_sense.pclnegen               = Si21XXC_ATV_INT_SENSE_PROP_PCLNEGEN_DISABLE  ; /* (default 'DISABLE') */
  prop->atv_int_sense.dlnegen                = Si21XXC_ATV_INT_SENSE_PROP_DLNEGEN_DISABLE   ; /* (default 'DISABLE') */
  prop->atv_int_sense.snrlnegen              = Si21XXC_ATV_INT_SENSE_PROP_SNRLNEGEN_DISABLE ; /* (default 'DISABLE') */
  prop->atv_int_sense.snrhnegen              = Si21XXC_ATV_INT_SENSE_PROP_SNRHNEGEN_DISABLE ; /* (default 'DISABLE') */
  prop->atv_int_sense.chlposen               = Si21XXC_ATV_INT_SENSE_PROP_CHLPOSEN_ENABLE   ; /* (default 'ENABLE') */
  prop->atv_int_sense.pclposen               = Si21XXC_ATV_INT_SENSE_PROP_PCLPOSEN_ENABLE   ; /* (default 'ENABLE') */
  prop->atv_int_sense.dlposen                = Si21XXC_ATV_INT_SENSE_PROP_DLPOSEN_ENABLE    ; /* (default 'ENABLE') */
  prop->atv_int_sense.snrlposen              = Si21XXC_ATV_INT_SENSE_PROP_SNRLPOSEN_ENABLE  ; /* (default 'ENABLE') */
  prop->atv_int_sense.snrhposen              = Si21XXC_ATV_INT_SENSE_PROP_SNRHPOSEN_ENABLE  ; /* (default 'ENABLE') */
#endif /* Si21XXC_ATV_INT_SENSE_PROP */

#ifdef    Si21XXC_ATV_PGA_TARGET_PROP
  prop->atv_pga_target.pga_target                       =     0; /* (default     0) */
  prop->atv_pga_target.override_enable                  = Si21XXC_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_DISABLE ; /* (default 'DISABLE') */
#endif /* Si21XXC_ATV_PGA_TARGET_PROP */

#ifdef    Si21XXC_ATV_RF_TOP_PROP
  prop->atv_rf_top.atv_rf_top                = Si21XXC_ATV_RF_TOP_PROP_ATV_RF_TOP_AUTO ; /* (default 'AUTO') */
#endif /* Si21XXC_ATV_RF_TOP_PROP */

#ifdef    Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP
  prop->atv_rsq_rssi_threshold.lo            =   -70; /* (default   -70) */
  prop->atv_rsq_rssi_threshold.hi            =     0; /* (default     0) */
#endif /* Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP */

#ifdef    Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP
  prop->atv_rsq_snr_threshold.lo             =    25; /* (default    25) */
  prop->atv_rsq_snr_threshold.hi             =    45; /* (default    45) */
#endif /* Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP */

#ifdef    Si21XXC_ATV_SIF_OUT_PROP
  prop->atv_sif_out.offset                   =   135; /* (default   135) */
  prop->atv_sif_out.amp                      =    60; /* (default    60) */
#endif /* Si21XXC_ATV_SIF_OUT_PROP */

#ifdef    Si21XXC_ATV_SOUND_AGC_LIMIT_PROP
  #if defined(TARGET_NT14U) || defined(TARGET_NT14M) //20140617,ssvd req
  prop->atv_sound_agc_limit.max_gain         =    74; /* (default    84) *///20140403,Sound carrier mute
  prop->atv_sound_agc_limit.min_gain         =   -84; /* (default   -84) */
  #else
  prop->atv_sound_agc_limit.max_gain         =    84; /* (default    84) */
  prop->atv_sound_agc_limit.min_gain         =   -84; /* (default   -84) */
  #endif
#endif /* Si21XXC_ATV_SOUND_AGC_LIMIT_PROP */

#ifdef    Si21XXC_ATV_SOUND_AGC_SPEED_PROP
  prop->atv_sound_agc_speed.system_l         =     5; /* (default     5) */
  prop->atv_sound_agc_speed.other_systems    =     4; /* (default     4) */
#endif /* Si21XXC_ATV_SOUND_AGC_SPEED_PROP */

#ifdef    Si21XXC_ATV_VIDEO_EQUALIZER_PROP
  prop->atv_video_equalizer.slope            =     0; /* (default     0) */
#endif /* Si21XXC_ATV_VIDEO_EQUALIZER_PROP */

#ifdef    Si21XXC_ATV_VIDEO_MODE_PROP
  prop->atv_video_mode.video_sys             = Si21XXC_ATV_VIDEO_MODE_PROP_VIDEO_SYS_M; /* (default 'B') */
  prop->atv_video_mode.color                 = Si21XXC_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC         ; /* (default 'PAL_NTSC') */
  prop->atv_video_mode.invert_signal         = Si21XXC_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL_NORMAL   ; /* (default 'NORMAL') */
#endif /* Si21XXC_ATV_VIDEO_MODE_PROP */

#ifdef    Si21XXC_ATV_VSNR_CAP_PROP
  prop->atv_vsnr_cap.atv_vsnr_cap            =     0; /* (default     0) */
#endif /* Si21XXC_ATV_VSNR_CAP_PROP */

#ifdef    Si21XXC_CRYSTAL_TRIM_PROP
  prop->crystal_trim.xo_cap                  = Si21XXC_CRYSTAL_TRIM_PROP_XO_CAP_6P7PF ; /* (default '6p7pF') */
#endif /* Si21XXC_CRYSTAL_TRIM_PROP */

#ifdef    Si21XXC_MASTER_IEN_PROP
  prop->master_ien.tunien                    = Si21XXC_MASTER_IEN_PROP_TUNIEN_ON ; /* (default 'OFF') */
  prop->master_ien.atvien                    = Si21XXC_MASTER_IEN_PROP_ATVIEN_ON ; /* (default 'OFF') */
  prop->master_ien.dtvien                    = Si21XXC_MASTER_IEN_PROP_DTVIEN_ON ; /* (default 'OFF') */
  prop->master_ien.errien                    = Si21XXC_MASTER_IEN_PROP_ERRIEN_OFF ; /* (default 'OFF') */
  prop->master_ien.ctsien                    = Si21XXC_MASTER_IEN_PROP_CTSIEN_OFF ; /* (default 'OFF') */
#endif /* Si21XXC_MASTER_IEN_PROP */

#ifdef    Si21XXC_XOUT_PROP
  prop->xout.amp                             = Si21XXC_XOUT_PROP_AMP_HIGH ; /* (default 'HIGH') */
#endif /* Si21XXC_XOUT_PROP */

#ifdef    Si21XXC_DTV_AGC_AUTO_FREEZE_PROP
  prop->dtv_agc_auto_freeze.thld             =   255; /* (default   255) */
  prop->dtv_agc_auto_freeze.timeout          =     1; /* (default     1) */
#endif /* Si21XXC_DTV_AGC_AUTO_FREEZE_PROP */

#ifdef    Si21XXC_DTV_AGC_FREEZE_INPUT_PROP
  prop->dtv_agc_freeze_input.level           = Si21XXC_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_LOW  ; /* (default 'LOW') */
  prop->dtv_agc_freeze_input.pin             = Si21XXC_DTV_AGC_FREEZE_INPUT_PROP_PIN_NONE   ; /* (default 'NONE') */
#endif /* Si21XXC_DTV_AGC_FREEZE_INPUT_PROP */

#ifdef    Si21XXC_DTV_AGC_SPEED_PROP
  prop->dtv_agc_speed.if_agc_speed           = Si21XXC_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO ; /* (default 'AUTO') */
  prop->dtv_agc_speed.agc_decim              = Si21XXC_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF     ; /* (default 'OFF') */
#endif /* Si21XXC_DTV_AGC_SPEED_PROP */

#ifdef    Si21XXC_DTV_CONFIG_IF_PORT_PROP
  prop->dtv_config_if_port.dtv_out_type      = Si21XXC_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LIF_IF1    ; /* (default 'LIF_IF1') */
  prop->dtv_config_if_port.dtv_agc_source    = Si21XXC_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_INTERNAL ; /* (default 'INTERNAL') */
#endif /* Si21XXC_DTV_CONFIG_IF_PORT_PROP */

#ifdef    Si21XXC_DTV_EXT_AGC_PROP
  prop->dtv_ext_agc.min_10mv                 =    50; /* (default    50) */
  prop->dtv_ext_agc.max_10mv                 =   200; /* (default   200) */
#endif /* Si21XXC_DTV_EXT_AGC_PROP */

#ifdef    Si21XXC_DTV_IEN_PROP
  prop->dtv_ien.chlien                       = Si21XXC_DTV_IEN_PROP_CHLIEN_ENABLE ; /* (default 'ENABLE') */
#endif /* Si21XXC_DTV_IEN_PROP */

#ifdef    Si21XXC_DTV_IF_AGC_SPEED_PROP
  prop->dtv_if_agc_speed.attack              = Si21XXC_DTV_IF_AGC_SPEED_PROP_ATTACK_AUTO ; /* (default 'AUTO') */
  prop->dtv_if_agc_speed.decay               = Si21XXC_DTV_IF_AGC_SPEED_PROP_DECAY_AUTO  ; /* (default 'AUTO') */
#endif /* Si21XXC_DTV_IF_AGC_SPEED_PROP */

#ifdef    Si21XXC_DTV_INITIAL_AGC_SPEED_PROP
  prop->dtv_initial_agc_speed.if_agc_speed   = Si21XXC_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO ; /* (default 'AUTO') */
  prop->dtv_initial_agc_speed.agc_decim      = Si21XXC_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_OFF     ; /* (default 'OFF') */
#endif /* Si21XXC_DTV_INITIAL_AGC_SPEED_PROP */

#ifdef    Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
  prop->dtv_initial_agc_speed_period.period  =     0; /* (default     0) */
#endif /* Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */

#ifdef    Si21XXC_DTV_INTERNAL_ZIF_PROP
  prop->dtv_internal_zif.atsc                = Si21XXC_DTV_INTERNAL_ZIF_PROP_ATSC_LIF   ; /* (default 'ZIF') */
  prop->dtv_internal_zif.qam_us              = Si21XXC_DTV_INTERNAL_ZIF_PROP_QAM_US_LIF ; /* (default 'ZIF') */
  prop->dtv_internal_zif.dvbt                = Si21XXC_DTV_INTERNAL_ZIF_PROP_DVBT_LIF   ; /* (default 'ZIF') */
  prop->dtv_internal_zif.dvbc                = Si21XXC_DTV_INTERNAL_ZIF_PROP_DVBC_LIF   ; /* (default 'ZIF') */
  prop->dtv_internal_zif.isdbt               = Si21XXC_DTV_INTERNAL_ZIF_PROP_ISDBT_LIF  ; /* (default 'ZIF') */
  prop->dtv_internal_zif.isdbc               = Si21XXC_DTV_INTERNAL_ZIF_PROP_ISDBC_LIF  ; /* (default 'ZIF') */
  prop->dtv_internal_zif.dtmb                = Si21XXC_DTV_INTERNAL_ZIF_PROP_DTMB_LIF   ; /* (default 'LIF') */
#endif /* Si21XXC_DTV_INTERNAL_ZIF_PROP */

#ifdef    Si21XXC_DTV_INT_SENSE_PROP
  prop->dtv_int_sense.chlnegen               = Si21XXC_DTV_INT_SENSE_PROP_CHLNEGEN_DISABLE ; /* (default 'DISABLE') */
  prop->dtv_int_sense.chlposen               = Si21XXC_DTV_INT_SENSE_PROP_CHLPOSEN_ENABLE  ; /* (default 'ENABLE') */
#endif /* Si21XXC_DTV_INT_SENSE_PROP */

#ifdef    Si21XXC_DTV_LIF_FREQ_PROP
  prop->dtv_lif_freq.offset                  =  5000; /* (default  5000) */
#endif /* Si21XXC_DTV_LIF_FREQ_PROP */

#ifdef    Si21XXC_DTV_LIF_OUT_PROP
  prop->dtv_lif_out.offset                   =   148; /* (default   148) */
  prop->dtv_lif_out.amp                      =    32; /* (default    27) */
#endif /* Si21XXC_DTV_LIF_OUT_PROP */

#ifdef    Si21XXC_DTV_MODE_PROP
  prop->dtv_mode.bw                          = Si21XXC_DTV_MODE_PROP_BW_BW_8MHZ              ; /* (default 'BW_8MHZ') */
  prop->dtv_mode.modulation                  = Si21XXC_DTV_MODE_PROP_MODULATION_DVBT         ; /* (default 'DVBT') */
  prop->dtv_mode.invert_spectrum             = Si21XXC_DTV_MODE_PROP_INVERT_SPECTRUM_NORMAL  ; /* (default 'NORMAL') */
#endif /* Si21XXC_DTV_MODE_PROP */

#ifdef    Si21XXC_DTV_RF_AGC_SPEED_PROP
  prop->dtv_rf_agc_speed.attack              =     Si21XXC_DTV_RF_AGC_SPEED_PROP_ATTACK_AUTO; /* (default     0) */
  prop->dtv_rf_agc_speed.decay               =     Si21XXC_DTV_RF_AGC_SPEED_PROP_DECAY_AUTO; /* (default     0) */
#endif /* Si21XXC_DTV_RF_AGC_SPEED_PROP */

#ifdef    Si21XXC_DTV_RF_TOP_PROP
  prop->dtv_rf_top.dtv_rf_top                = Si21XXC_DTV_RF_TOP_PROP_DTV_RF_TOP_AUTO ; /* (default 'AUTO') */
#endif /* Si21XXC_DTV_RF_TOP_PROP */

#ifdef    Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP
  prop->dtv_rsq_rssi_threshold.lo            =   -80; /* (default   -80) */
  prop->dtv_rsq_rssi_threshold.hi            =     0; /* (default     0) */
#endif /* Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP */

#ifdef    Si21XXC_DTV_WB_AGC_SPEED_PROP
  prop->dtv_wb_agc_speed.attack              = Si21XXC_DTV_WB_AGC_SPEED_PROP_ATTACK_AUTO ; /* (default 'AUTO') */
  prop->dtv_wb_agc_speed.decay               = Si21XXC_DTV_WB_AGC_SPEED_PROP_DECAY_AUTO  ; /* (default 'AUTO') */
#endif /* Si21XXC_DTV_WB_AGC_SPEED_PROP */

#ifdef    Si21XXC_TUNER_BLOCKED_VCO_PROP
  prop->tuner_blocked_vco.vco_code           = 0x8000; /* (default 0x8000) */
#endif /* Si21XXC_TUNER_BLOCKED_VCO_PROP */

#ifdef    Si21XXC_TUNER_IEN_PROP
  prop->tuner_ien.tcien                      = Si21XXC_TUNER_IEN_PROP_TCIEN_ENABLE     ; /* (default 'ENABLE') */
  prop->tuner_ien.rssilien                   = Si21XXC_TUNER_IEN_PROP_RSSILIEN_DISABLE ; /* (default 'DISABLE') */
  prop->tuner_ien.rssihien                   = Si21XXC_TUNER_IEN_PROP_RSSIHIEN_DISABLE ; /* (default 'DISABLE') */
#endif /* Si21XXC_TUNER_IEN_PROP */

#ifdef    Si21XXC_TUNER_INT_SENSE_PROP
  prop->tuner_int_sense.tcnegen              = Si21XXC_TUNER_INT_SENSE_PROP_TCNEGEN_DISABLE    ; /* (default 'DISABLE') */
  prop->tuner_int_sense.rssilnegen           = Si21XXC_TUNER_INT_SENSE_PROP_RSSILNEGEN_DISABLE ; /* (default 'DISABLE') */
  prop->tuner_int_sense.rssihnegen           = Si21XXC_TUNER_INT_SENSE_PROP_RSSIHNEGEN_DISABLE ; /* (default 'DISABLE') */
  prop->tuner_int_sense.tcposen              = Si21XXC_TUNER_INT_SENSE_PROP_TCPOSEN_ENABLE     ; /* (default 'ENABLE') */
  prop->tuner_int_sense.rssilposen           = Si21XXC_TUNER_INT_SENSE_PROP_RSSILPOSEN_ENABLE  ; /* (default 'ENABLE') */
  prop->tuner_int_sense.rssihposen           = Si21XXC_TUNER_INT_SENSE_PROP_RSSIHPOSEN_ENABLE  ; /* (default 'ENABLE') */
#endif /* Si21XXC_TUNER_INT_SENSE_PROP */

#ifdef    Si21XXC_TUNER_LO_INJECTION_PROP
  prop->tuner_lo_injection.band_1            = Si21XXC_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE ; /* (default 'HIGH_SIDE') */
  prop->tuner_lo_injection.band_2            = Si21XXC_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE  ; /* (default 'LOW_SIDE') */
  prop->tuner_lo_injection.band_3            = Si21XXC_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE  ; /* (default 'LOW_SIDE') */
#endif /* Si21XXC_TUNER_LO_INJECTION_PROP */

#ifdef    Si21XXC_TUNER_RETURN_LOSS_PROP
  prop->tuner_return_loss.config             = Si21XXC_TUNER_RETURN_LOSS_PROP_CONFIG_127         ; /* (default '127') */
  prop->tuner_return_loss.mode               = Si21XXC_TUNER_RETURN_LOSS_PROP_MODE_TERRESTRIAL   ; /* (default 'TERRESTRIAL') */
#endif /* Si21XXC_TUNER_RETURN_LOSS_PROP */

#ifdef    Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP
  prop->tuner_return_loss_optimize.thld                 =     0; /* (default     0) */
  prop->tuner_return_loss_optimize.config               = Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_DISABLE              ; /* (default 'DISABLE') */
  prop->tuner_return_loss_optimize.engagement_delay     =     7; /* (default     7) */
  prop->tuner_return_loss_optimize.disengagement_delay  =    10; /* (default    10) */
#endif /* Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP */

#ifdef    Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP
  prop->tuner_return_loss_optimize_2.thld               =    31; /* (default    31) */
  prop->tuner_return_loss_optimize_2.window             =     0; /* (default     0) */
  prop->tuner_return_loss_optimize_2.engagement_delay   =    15; /* (default    15) */
#endif /* Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP */

#ifdef    Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP
  prop->tuner_tf1_boundary_offset.tf1_boundary_offset   =     0; /* (default     0) */
#endif /* Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP */

#ifdef    Si2190B_WIDE_BAND_ATT_THRS_PROP
  prop->wide_band_att_thrs.wb_att_thrs       = Si2190B_WIDE_BAND_ATT_THRS_PROP_WB_ATT_THRS_AUTO ; /* (default 'AUTO') */
#endif /* Si2190B_WIDE_BAND_ATT_THRS_PROP */
}
