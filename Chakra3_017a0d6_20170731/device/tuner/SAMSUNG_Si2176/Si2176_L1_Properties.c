/***************************************************************************************/
/* FILE: Si2176_L1_Properties.c                                                        */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/***************************************************************************************/
/*                     Silicon Laboratories Broadcast Si2176 API Layer 1               */
/***************************************************************************************/
//#include "Si2176_Typedefs.h"
#include "Si2176_L0_TV_Chassis.h"
#include "Si2176_L1_API_TV_Chassis.h"
#include "Si2176_Commands.h"
#include "Si2176_Properties.h"

/***********************************************************************************************************************
  Si2176_L1_SetProperty function
  Use:        property set function
              Used to call L1_SET_PROPERTY with the property Id and data provided.
  Comments:   This is a way to make sure CTS is polled when setting a property
  Parameter: *api     the Si2176 context
  Parameter: wait_for_cts flag to wait for a CTS before issuing the property command
  Parameter: wait_for_response flag to wait for a CTS after issuing the property command
  Parameter: prop     the property Id
  Parameter: data     the property bytes
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/
 unsigned char  Si2176_L1_SetProperty(L1_Si2176_Context *api, unsigned char wait_for_cts, unsigned char wait_for_response, unsigned int prop, int  data, Si2176_CmdReplyObj *rsp)  {
    unsigned char  reserved          = 0;
    return Si2176_L1_SET_PROPERTY (api, wait_for_cts, wait_for_response, reserved, prop, data, rsp);
}

/***********************************************************************************************************************
  Si2176_L1_GetProperty function
  Use:        property get function
              Used to call L1_GET_PROPERTY with the property Id provided.
  Comments:   This is a way to make sure CTS is polled when retrieving a property
  Parameter: *api     the Si2176 context
  Parameter: wait_for_cts flag to wait for a CTS before issuing the property command
  Parameter: wait_for_response flag to wait for a CTS after issuing the property command
  Parameter: prop     the property Id
  Parameter: *data    a buffer to store the property bytes into
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/
 unsigned char     Si2176_L1_GetProperty(L1_Si2176_Context *api, unsigned char wait_for_cts, unsigned char wait_for_response, unsigned int prop, int *data, Si2176_CmdReplyObj *rsp) {
    unsigned char  reserved          = 0;
    unsigned char res;
    res = Si2176_L1_GET_PROPERTY (api, wait_for_cts, wait_for_response, reserved, prop, rsp);
    *data = rsp->get_property.data;
    return res;
}

/* _set_property2_insertion_start */

  /* --------------------------------------------*/
  /* SET_PROPERTY2 FUNCTION                      */
  /* --------------------------------------------*/
 unsigned char  Si2176_L1_SetProperty2(L1_Si2176_Context *api, unsigned char wait_for_cts, unsigned char wait_for_response, unsigned int prop, Si2176_PropObj *p, Si2176_CmdReplyObj *rsp) {
    int data;
     data = 0;

    switch (prop) {
    #ifdef        Si2176_ATV_AFC_RANGE_PROP
     case         Si2176_ATV_AFC_RANGE_PROP:
       data = (p->atv_afc_range.range_khz & Si2176_ATV_AFC_RANGE_PROP_RANGE_KHZ_MASK) << Si2176_ATV_AFC_RANGE_PROP_RANGE_KHZ_LSB ;
     break;
    #endif /*     Si2176_ATV_AFC_RANGE_PROP */
    #ifdef        Si2176_ATV_AF_OUT_PROP
     case         Si2176_ATV_AF_OUT_PROP:
       data = (p->atv_af_out.volume & Si2176_ATV_AF_OUT_PROP_VOLUME_MASK) << Si2176_ATV_AF_OUT_PROP_VOLUME_LSB ;
     break;
    #endif /*     Si2176_ATV_AF_OUT_PROP */
    #ifdef        Si2176_ATV_AGC_SPEED_PROP
     case         Si2176_ATV_AGC_SPEED_PROP:
       data = (p->atv_agc_speed.if_agc_speed & Si2176_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_MASK) << Si2176_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_LSB ;
     break;
    #endif /*     Si2176_ATV_AGC_SPEED_PROP */
    #ifdef        Si2176_ATV_AUDIO_MODE_PROP
     case         Si2176_ATV_AUDIO_MODE_PROP:
       data = (p->atv_audio_mode.audio_sys  & Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_MASK ) << Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_LSB  |
              (p->atv_audio_mode.demod_mode & Si2176_ATV_AUDIO_MODE_PROP_DEMOD_MODE_MASK) << Si2176_ATV_AUDIO_MODE_PROP_DEMOD_MODE_LSB  |
              (p->atv_audio_mode.chan_bw    & Si2176_ATV_AUDIO_MODE_PROP_CHAN_BW_MASK   ) << Si2176_ATV_AUDIO_MODE_PROP_CHAN_BW_LSB ;
     break;
    #endif /*     Si2176_ATV_AUDIO_MODE_PROP */
    #ifdef        Si2176_ATV_CVBS_OUT_PROP
     case         Si2176_ATV_CVBS_OUT_PROP:
       data = (p->atv_cvbs_out.offset & Si2176_ATV_CVBS_OUT_PROP_OFFSET_MASK) << Si2176_ATV_CVBS_OUT_PROP_OFFSET_LSB  |
              (p->atv_cvbs_out.amp    & Si2176_ATV_CVBS_OUT_PROP_AMP_MASK   ) << Si2176_ATV_CVBS_OUT_PROP_AMP_LSB ;
     break;
    #endif /*     Si2176_ATV_CVBS_OUT_PROP */
    #ifdef        Si2176_ATV_CVBS_OUT_FINE_PROP
     case         Si2176_ATV_CVBS_OUT_FINE_PROP:
       data = (p->atv_cvbs_out_fine.offset & Si2176_ATV_CVBS_OUT_FINE_PROP_OFFSET_MASK) << Si2176_ATV_CVBS_OUT_FINE_PROP_OFFSET_LSB  |
              (p->atv_cvbs_out_fine.amp    & Si2176_ATV_CVBS_OUT_FINE_PROP_AMP_MASK   ) << Si2176_ATV_CVBS_OUT_FINE_PROP_AMP_LSB ;
     break;
    #endif /*     Si2176_ATV_CVBS_OUT_FINE_PROP */
    #ifdef        Si2176_ATV_IEN_PROP
     case         Si2176_ATV_IEN_PROP:
       data = (p->atv_ien.chlien  & Si2176_ATV_IEN_PROP_CHLIEN_MASK ) << Si2176_ATV_IEN_PROP_CHLIEN_LSB  |
              (p->atv_ien.pclien  & Si2176_ATV_IEN_PROP_PCLIEN_MASK ) << Si2176_ATV_IEN_PROP_PCLIEN_LSB  |
              (p->atv_ien.dlien   & Si2176_ATV_IEN_PROP_DLIEN_MASK  ) << Si2176_ATV_IEN_PROP_DLIEN_LSB  |
              (p->atv_ien.snrlien & Si2176_ATV_IEN_PROP_SNRLIEN_MASK) << Si2176_ATV_IEN_PROP_SNRLIEN_LSB  |
              (p->atv_ien.snrhien & Si2176_ATV_IEN_PROP_SNRHIEN_MASK) << Si2176_ATV_IEN_PROP_SNRHIEN_LSB ;
     break;
    #endif /*     Si2176_ATV_IEN_PROP */
    #ifdef        Si2176_ATV_INT_SENSE_PROP
    #ifdef        Si2176_ATV_MIN_LVL_LOCK_PROP
     case         Si2176_ATV_MIN_LVL_LOCK_PROP:
       data = (p->atv_min_lvl_lock.thrs & Si2176_ATV_MIN_LVL_LOCK_PROP_THRS_MASK) << Si2176_ATV_MIN_LVL_LOCK_PROP_THRS_LSB ;
     break;
    #endif /*     Si2176_ATV_MIN_LVL_LOCK_PROP */    
     case         Si2176_ATV_INT_SENSE_PROP:
       data = (p->atv_int_sense.chlnegen  & Si2176_ATV_INT_SENSE_PROP_CHLNEGEN_MASK ) << Si2176_ATV_INT_SENSE_PROP_CHLNEGEN_LSB  |
              (p->atv_int_sense.pclnegen  & Si2176_ATV_INT_SENSE_PROP_PCLNEGEN_MASK ) << Si2176_ATV_INT_SENSE_PROP_PCLNEGEN_LSB  |
              (p->atv_int_sense.dlnegen   & Si2176_ATV_INT_SENSE_PROP_DLNEGEN_MASK  ) << Si2176_ATV_INT_SENSE_PROP_DLNEGEN_LSB  |
              (p->atv_int_sense.snrlnegen & Si2176_ATV_INT_SENSE_PROP_SNRLNEGEN_MASK) << Si2176_ATV_INT_SENSE_PROP_SNRLNEGEN_LSB  |
              (p->atv_int_sense.snrhnegen & Si2176_ATV_INT_SENSE_PROP_SNRHNEGEN_MASK) << Si2176_ATV_INT_SENSE_PROP_SNRHNEGEN_LSB  |
              (p->atv_int_sense.chlposen  & Si2176_ATV_INT_SENSE_PROP_CHLPOSEN_MASK ) << Si2176_ATV_INT_SENSE_PROP_CHLPOSEN_LSB  |
              (p->atv_int_sense.pclposen  & Si2176_ATV_INT_SENSE_PROP_PCLPOSEN_MASK ) << Si2176_ATV_INT_SENSE_PROP_PCLPOSEN_LSB  |
              (p->atv_int_sense.dlposen   & Si2176_ATV_INT_SENSE_PROP_DLPOSEN_MASK  ) << Si2176_ATV_INT_SENSE_PROP_DLPOSEN_LSB  |
              (p->atv_int_sense.snrlposen & Si2176_ATV_INT_SENSE_PROP_SNRLPOSEN_MASK) << Si2176_ATV_INT_SENSE_PROP_SNRLPOSEN_LSB  |
              (p->atv_int_sense.snrhposen & Si2176_ATV_INT_SENSE_PROP_SNRHPOSEN_MASK) << Si2176_ATV_INT_SENSE_PROP_SNRHPOSEN_LSB ;
     break;
    #endif /*     Si2176_ATV_INT_SENSE_PROP */
    #ifdef        Si2176_ATV_RF_TOP_PROP
     case         Si2176_ATV_RF_TOP_PROP:
       data = (p->atv_rf_top.atv_rf_top & Si2176_ATV_RF_TOP_PROP_ATV_RF_TOP_MASK) << Si2176_ATV_RF_TOP_PROP_ATV_RF_TOP_LSB ;
     break;
    #endif /*     Si2176_ATV_RF_TOP_PROP */
    #ifdef        Si2176_ATV_RSQ_RSSI_THRESHOLD_PROP
     case         Si2176_ATV_RSQ_RSSI_THRESHOLD_PROP:
       data = (p->atv_rsq_rssi_threshold.lo & Si2176_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_MASK) << Si2176_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_LSB  |
              (p->atv_rsq_rssi_threshold.hi & Si2176_ATV_RSQ_RSSI_THRESHOLD_PROP_HI_MASK) << Si2176_ATV_RSQ_RSSI_THRESHOLD_PROP_HI_LSB ;
     break;
    #endif /*     Si2176_ATV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef        Si2176_ATV_RSQ_SNR_THRESHOLD_PROP
     case         Si2176_ATV_RSQ_SNR_THRESHOLD_PROP:
       data = (p->atv_rsq_snr_threshold.lo & Si2176_ATV_RSQ_SNR_THRESHOLD_PROP_LO_MASK) << Si2176_ATV_RSQ_SNR_THRESHOLD_PROP_LO_LSB  |
              (p->atv_rsq_snr_threshold.hi & Si2176_ATV_RSQ_SNR_THRESHOLD_PROP_HI_MASK) << Si2176_ATV_RSQ_SNR_THRESHOLD_PROP_HI_LSB ;
     break;
    #endif /*     Si2176_ATV_RSQ_SNR_THRESHOLD_PROP */
    #ifdef        Si2176_ATV_SIF_OUT_PROP
     case         Si2176_ATV_SIF_OUT_PROP:
       data = (p->atv_sif_out.offset & Si2176_ATV_SIF_OUT_PROP_OFFSET_MASK) << Si2176_ATV_SIF_OUT_PROP_OFFSET_LSB  |
              (p->atv_sif_out.amp    & Si2176_ATV_SIF_OUT_PROP_AMP_MASK   ) << Si2176_ATV_SIF_OUT_PROP_AMP_LSB ;
     break;
    #endif /*     Si2176_ATV_SIF_OUT_PROP */
    #ifdef        Si2176_ATV_SOUND_AGC_LIMIT_PROP
     case         Si2176_ATV_SOUND_AGC_LIMIT_PROP:
       data = (p->atv_sound_agc_limit.max_gain & Si2176_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN_MASK) << Si2176_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN_LSB  |
              (p->atv_sound_agc_limit.min_gain & Si2176_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN_MASK) << Si2176_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN_LSB ;
     break;
    #endif /*     Si2176_ATV_SOUND_AGC_LIMIT_PROP */
    #ifdef        Si2176_ATV_SOUND_AGC_SPEED_PROP
     case         Si2176_ATV_SOUND_AGC_SPEED_PROP:
       data = (p->atv_sound_agc_speed.system_l      & Si2176_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L_MASK     ) << Si2176_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L_LSB  |
              (p->atv_sound_agc_speed.other_systems & Si2176_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS_MASK) << Si2176_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS_LSB ;
     break;
    #endif /*     Si2176_ATV_SOUND_AGC_SPEED_PROP */    
    #ifdef        Si2176_ATV_VIDEO_EQUALIZER_PROP
     case         Si2176_ATV_VIDEO_EQUALIZER_PROP:
       data = (p->atv_video_equalizer.slope & Si2176_ATV_VIDEO_EQUALIZER_PROP_SLOPE_MASK) << Si2176_ATV_VIDEO_EQUALIZER_PROP_SLOPE_LSB ;
     break;
    #endif /*     Si2176_ATV_VIDEO_EQUALIZER_PROP */
    #ifdef        Si2176_ATV_VIDEO_MODE_PROP
     case         Si2176_ATV_VIDEO_MODE_PROP:
       data = (p->atv_video_mode.video_sys       & Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_MASK      ) << Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_LSB  |
              (p->atv_video_mode.color           & Si2176_ATV_VIDEO_MODE_PROP_COLOR_MASK          ) << Si2176_ATV_VIDEO_MODE_PROP_COLOR_LSB  |
              (p->atv_video_mode.trans           & Si2176_ATV_VIDEO_MODE_PROP_TRANS_MASK          ) << Si2176_ATV_VIDEO_MODE_PROP_TRANS_LSB  |
              (p->atv_video_mode.invert_signal   & Si2176_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL_MASK  ) << Si2176_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL_LSB ;
     break;
    #endif /*     Si2176_ATV_VIDEO_MODE_PROP */
    #ifdef        Si2176_ATV_VSNR_CAP_PROP
     case         Si2176_ATV_VSNR_CAP_PROP:
       data = (p->atv_vsnr_cap.atv_vsnr_cap & Si2176_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_MASK) << Si2176_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_LSB ;
     break;
    #endif /*     Si2176_ATV_VSNR_CAP_PROP */
    #ifdef        Si2176_ATV_VSYNC_TRACKING_PROP
     case         Si2176_ATV_VSYNC_TRACKING_PROP:
       data = (p->atv_vsync_tracking.min_pulses_to_lock   & Si2176_ATV_VSYNC_TRACKING_PROP_MIN_PULSES_TO_LOCK_MASK  ) << Si2176_ATV_VSYNC_TRACKING_PROP_MIN_PULSES_TO_LOCK_LSB  |
              (p->atv_vsync_tracking.min_fields_to_unlock & Si2176_ATV_VSYNC_TRACKING_PROP_MIN_FIELDS_TO_UNLOCK_MASK) << Si2176_ATV_VSYNC_TRACKING_PROP_MIN_FIELDS_TO_UNLOCK_LSB ;
     break;
    #endif /*     Si2176_ATV_VSYNC_TRACKING_PROP */
    #ifdef        Si2176_CRYSTAL_TRIM_PROP
     case         Si2176_CRYSTAL_TRIM_PROP:
       data = (p->crystal_trim.xo_cap & Si2176_CRYSTAL_TRIM_PROP_XO_CAP_MASK) << Si2176_CRYSTAL_TRIM_PROP_XO_CAP_LSB ;
     break;
    #endif /*     Si2176_CRYSTAL_TRIM_PROP */
    #ifdef        Si2176_DTV_AGC_SPEED_PROP
     case         Si2176_DTV_AGC_SPEED_PROP:
       data = (p->dtv_agc_speed.if_agc_speed & Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_MASK) << Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_LSB  |
              (p->dtv_agc_speed.agc_decim    & Si2176_DTV_AGC_SPEED_PROP_AGC_DECIM_MASK   ) << Si2176_DTV_AGC_SPEED_PROP_AGC_DECIM_LSB ;
     break;
    #endif /*     Si2176_DTV_AGC_SPEED_PROP */
    #ifdef        Si2176_DTV_CONFIG_IF_PORT_PROP
     case         Si2176_DTV_CONFIG_IF_PORT_PROP:
       data = (p->dtv_config_if_port.dtv_out_type   & Si2176_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_MASK  ) << Si2176_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LSB  |
              (p->dtv_config_if_port.dtv_agc_source & Si2176_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_MASK) << Si2176_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_LSB ;
     break;
    #endif /*     Si2176_DTV_CONFIG_IF_PORT_PROP */
    #ifdef        Si2176_DTV_EXT_AGC_PROP
     case         Si2176_DTV_EXT_AGC_PROP:
       data = (p->dtv_ext_agc.min_10mv & Si2176_DTV_EXT_AGC_PROP_MIN_10MV_MASK) << Si2176_DTV_EXT_AGC_PROP_MIN_10MV_LSB  |
              (p->dtv_ext_agc.max_10mv & Si2176_DTV_EXT_AGC_PROP_MAX_10MV_MASK) << Si2176_DTV_EXT_AGC_PROP_MAX_10MV_LSB ;
     break;
    #endif /*     Si2176_DTV_EXT_AGC_PROP */
    #ifdef        Si2176_DTV_IEN_PROP
     case         Si2176_DTV_IEN_PROP:
       data = (p->dtv_ien.chlien & Si2176_DTV_IEN_PROP_CHLIEN_MASK) << Si2176_DTV_IEN_PROP_CHLIEN_LSB ;
     break;
    #endif /*     Si2176_DTV_IEN_PROP */
      #ifdef        Si2176_DTV_INITIAL_AGC_SPEED_PROP
     case         Si2176_DTV_INITIAL_AGC_SPEED_PROP:
       data = (p->dtv_initial_agc_speed.if_agc_speed & Si2176_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_MASK) << Si2176_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_LSB  |
              (p->dtv_initial_agc_speed.agc_decim    & Si2176_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_MASK   ) << Si2176_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_LSB ;
     break;
    #endif /*     Si2176_DTV_INITIAL_AGC_SPEED_PROP */
    #ifdef        Si2176_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
     case         Si2176_DTV_INITIAL_AGC_SPEED_PERIOD_PROP:
       data = (p->dtv_initial_agc_speed_period.period & Si2176_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_MASK) << Si2176_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_LSB ;
     break;
    #endif /*     Si2176_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */
    #ifdef        Si2176_DTV_INT_SENSE_PROP
     case         Si2176_DTV_INT_SENSE_PROP:
       data = (p->dtv_int_sense.chlnegen & Si2176_DTV_INT_SENSE_PROP_CHLNEGEN_MASK) << Si2176_DTV_INT_SENSE_PROP_CHLNEGEN_LSB  |
              (p->dtv_int_sense.chlposen & Si2176_DTV_INT_SENSE_PROP_CHLPOSEN_MASK) << Si2176_DTV_INT_SENSE_PROP_CHLPOSEN_LSB ;
     break;
    #endif /*     Si2176_DTV_INT_SENSE_PROP */
    #ifdef        Si2176_DTV_LIF_FREQ_PROP
     case         Si2176_DTV_LIF_FREQ_PROP:
       data = (p->dtv_lif_freq.offset & Si2176_DTV_LIF_FREQ_PROP_OFFSET_MASK) << Si2176_DTV_LIF_FREQ_PROP_OFFSET_LSB ;
     break;
    #endif /*     Si2176_DTV_LIF_FREQ_PROP */
    #ifdef        Si2176_DTV_LIF_OUT_PROP
     case         Si2176_DTV_LIF_OUT_PROP:
       data = (p->dtv_lif_out.offset & Si2176_DTV_LIF_OUT_PROP_OFFSET_MASK) << Si2176_DTV_LIF_OUT_PROP_OFFSET_LSB  |
              (p->dtv_lif_out.amp    & Si2176_DTV_LIF_OUT_PROP_AMP_MASK   ) << Si2176_DTV_LIF_OUT_PROP_AMP_LSB ;
     break;
    #endif /*     Si2176_DTV_LIF_OUT_PROP */
    #ifdef        Si2176_DTV_MODE_PROP
     case         Si2176_DTV_MODE_PROP:
       data = (p->dtv_mode.bw              & Si2176_DTV_MODE_PROP_BW_MASK             ) << Si2176_DTV_MODE_PROP_BW_LSB  |
              (p->dtv_mode.modulation      & Si2176_DTV_MODE_PROP_MODULATION_MASK     ) << Si2176_DTV_MODE_PROP_MODULATION_LSB  |
              (p->dtv_mode.invert_spectrum & Si2176_DTV_MODE_PROP_INVERT_SPECTRUM_MASK) << Si2176_DTV_MODE_PROP_INVERT_SPECTRUM_LSB ;
     break;
    #endif /*     Si2176_DTV_MODE_PROP */
    #ifdef        Si2176_DTV_RF_TOP_PROP
     case         Si2176_DTV_RF_TOP_PROP:
       data = (p->dtv_rf_top.dtv_rf_top & Si2176_DTV_RF_TOP_PROP_DTV_RF_TOP_MASK) << Si2176_DTV_RF_TOP_PROP_DTV_RF_TOP_LSB ;
     break;
    #endif /*     Si2176_DTV_RF_TOP_PROP */
    #ifdef        Si2176_DTV_RSQ_RSSI_THRESHOLD_PROP
     case         Si2176_DTV_RSQ_RSSI_THRESHOLD_PROP:
       data = (p->dtv_rsq_rssi_threshold.lo & Si2176_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_MASK) << Si2176_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_LSB  |
              (p->dtv_rsq_rssi_threshold.hi & Si2176_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_MASK) << Si2176_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_LSB ;
     break;
    #endif /*     Si2176_DTV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef        Si2176_MASTER_IEN_PROP
     case         Si2176_MASTER_IEN_PROP:
       data = (p->master_ien.tunien & Si2176_MASTER_IEN_PROP_TUNIEN_MASK) << Si2176_MASTER_IEN_PROP_TUNIEN_LSB  |
              (p->master_ien.atvien & Si2176_MASTER_IEN_PROP_ATVIEN_MASK) << Si2176_MASTER_IEN_PROP_ATVIEN_LSB  |
              (p->master_ien.dtvien & Si2176_MASTER_IEN_PROP_DTVIEN_MASK) << Si2176_MASTER_IEN_PROP_DTVIEN_LSB  |
              (p->master_ien.errien & Si2176_MASTER_IEN_PROP_ERRIEN_MASK) << Si2176_MASTER_IEN_PROP_ERRIEN_LSB  |
              (p->master_ien.ctsien & Si2176_MASTER_IEN_PROP_CTSIEN_MASK) << Si2176_MASTER_IEN_PROP_CTSIEN_LSB ;
     break;
    #endif /*     Si2176_MASTER_IEN_PROP */
    #ifdef        Si2176_TUNER_BLOCKED_VCO_PROP
     case         Si2176_TUNER_BLOCKED_VCO_PROP:
       data = (p->tuner_blocked_vco.vco_code & Si2176_TUNER_BLOCKED_VCO_PROP_VCO_CODE_MASK) << Si2176_TUNER_BLOCKED_VCO_PROP_VCO_CODE_LSB ;
     break;
    #endif /*     Si2176_TUNER_BLOCKED_VCO_PROP */
    #ifdef        Si2176_TUNER_IEN_PROP
     case         Si2176_TUNER_IEN_PROP:
       data = (p->tuner_ien.tcien    & Si2176_TUNER_IEN_PROP_TCIEN_MASK   ) << Si2176_TUNER_IEN_PROP_TCIEN_LSB  |
              (p->tuner_ien.rssilien & Si2176_TUNER_IEN_PROP_RSSILIEN_MASK) << Si2176_TUNER_IEN_PROP_RSSILIEN_LSB  |
              (p->tuner_ien.rssihien & Si2176_TUNER_IEN_PROP_RSSIHIEN_MASK) << Si2176_TUNER_IEN_PROP_RSSIHIEN_LSB ;
     break;
    #endif /*     Si2176_TUNER_IEN_PROP */
    #ifdef        Si2176_TUNER_INT_SENSE_PROP
     case         Si2176_TUNER_INT_SENSE_PROP:
       data = (p->tuner_int_sense.tcnegen    & Si2176_TUNER_INT_SENSE_PROP_TCNEGEN_MASK   ) << Si2176_TUNER_INT_SENSE_PROP_TCNEGEN_LSB  |
              (p->tuner_int_sense.rssilnegen & Si2176_TUNER_INT_SENSE_PROP_RSSILNEGEN_MASK) << Si2176_TUNER_INT_SENSE_PROP_RSSILNEGEN_LSB  |
              (p->tuner_int_sense.rssihnegen & Si2176_TUNER_INT_SENSE_PROP_RSSIHNEGEN_MASK) << Si2176_TUNER_INT_SENSE_PROP_RSSIHNEGEN_LSB  |
              (p->tuner_int_sense.tcposen    & Si2176_TUNER_INT_SENSE_PROP_TCPOSEN_MASK   ) << Si2176_TUNER_INT_SENSE_PROP_TCPOSEN_LSB  |
              (p->tuner_int_sense.rssilposen & Si2176_TUNER_INT_SENSE_PROP_RSSILPOSEN_MASK) << Si2176_TUNER_INT_SENSE_PROP_RSSILPOSEN_LSB  |
              (p->tuner_int_sense.rssihposen & Si2176_TUNER_INT_SENSE_PROP_RSSIHPOSEN_MASK) << Si2176_TUNER_INT_SENSE_PROP_RSSIHPOSEN_LSB ;
     break;
    #endif /*     Si2176_TUNER_INT_SENSE_PROP */
    #ifdef        Si2176_TUNER_LO_INJECTION_PROP
     case         Si2176_TUNER_LO_INJECTION_PROP:
       data = (p->tuner_lo_injection.band_1 & Si2176_TUNER_LO_INJECTION_PROP_BAND_1_MASK) << Si2176_TUNER_LO_INJECTION_PROP_BAND_1_LSB  |
              (p->tuner_lo_injection.band_2 & Si2176_TUNER_LO_INJECTION_PROP_BAND_2_MASK) << Si2176_TUNER_LO_INJECTION_PROP_BAND_2_LSB  |
              (p->tuner_lo_injection.band_3 & Si2176_TUNER_LO_INJECTION_PROP_BAND_3_MASK) << Si2176_TUNER_LO_INJECTION_PROP_BAND_3_LSB  |
              (p->tuner_lo_injection.band_4 & Si2176_TUNER_LO_INJECTION_PROP_BAND_4_MASK) << Si2176_TUNER_LO_INJECTION_PROP_BAND_4_LSB  |
              (p->tuner_lo_injection.band_5 & Si2176_TUNER_LO_INJECTION_PROP_BAND_5_MASK) << Si2176_TUNER_LO_INJECTION_PROP_BAND_5_LSB ;
     break;
    #endif /*     Si2176_TUNER_LO_INJECTION_PROP */
   default : break;
    }

    return Si2176_L1_SetProperty(api, wait_for_cts, wait_for_response, prop , data, rsp);
  }
  /* _set_property2_insertion_point */

/* _get_property2_insertion_start */

  /* --------------------------------------------*/
  /* GET_PROPERTY2 FUNCTION                       */
  /* --------------------------------------------*/
 unsigned char  Si2176_L1_GetProperty2(L1_Si2176_Context *api, unsigned char wait_for_cts, unsigned char wait_for_response, unsigned int prop, Si2176_PropObj *p, Si2176_CmdReplyObj *rsp) {
    int data, res;
    res = Si2176_L1_GetProperty(api,wait_for_cts,wait_for_response,prop,&data,rsp);
    if (res!=NO_Si2176_ERROR) return res;
    switch (prop) {
    #ifdef        Si2176_ATV_AFC_RANGE_PROP
     case         Si2176_ATV_AFC_RANGE_PROP:
               p->atv_afc_range.range_khz = (data >> Si2176_ATV_AFC_RANGE_PROP_RANGE_KHZ_LSB) & Si2176_ATV_AFC_RANGE_PROP_RANGE_KHZ_MASK;
     break;
    #endif /*     Si2176_ATV_AFC_RANGE_PROP */
    #ifdef        Si2176_ATV_AF_OUT_PROP
     case         Si2176_ATV_AF_OUT_PROP:
               p->atv_af_out.volume = (data >> Si2176_ATV_AF_OUT_PROP_VOLUME_LSB) & Si2176_ATV_AF_OUT_PROP_VOLUME_MASK;
     break;
    #endif /*     Si2176_ATV_AF_OUT_PROP */
    #ifdef        Si2176_ATV_AGC_SPEED_PROP
     case         Si2176_ATV_AGC_SPEED_PROP:
               p->atv_agc_speed.if_agc_speed = (data >> Si2176_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_LSB) & Si2176_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_MASK;
     break;
    #endif /*     Si2176_ATV_AGC_SPEED_PROP */
    #ifdef        Si2176_ATV_AUDIO_MODE_PROP
     case         Si2176_ATV_AUDIO_MODE_PROP:
               p->atv_audio_mode.audio_sys  = (data >> Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_LSB ) & Si2176_ATV_AUDIO_MODE_PROP_AUDIO_SYS_MASK;
               p->atv_audio_mode.demod_mode = (data >> Si2176_ATV_AUDIO_MODE_PROP_DEMOD_MODE_LSB) & Si2176_ATV_AUDIO_MODE_PROP_DEMOD_MODE_MASK;
               p->atv_audio_mode.chan_bw    = (data >> Si2176_ATV_AUDIO_MODE_PROP_CHAN_BW_LSB   ) & Si2176_ATV_AUDIO_MODE_PROP_CHAN_BW_MASK;
     break;
    #endif /*     Si2176_ATV_AUDIO_MODE_PROP */
    #ifdef        Si2176_ATV_CVBS_OUT_PROP
     case         Si2176_ATV_CVBS_OUT_PROP:
               p->atv_cvbs_out.offset = (data >> Si2176_ATV_CVBS_OUT_PROP_OFFSET_LSB) & Si2176_ATV_CVBS_OUT_PROP_OFFSET_MASK;
               p->atv_cvbs_out.amp    = (data >> Si2176_ATV_CVBS_OUT_PROP_AMP_LSB   ) & Si2176_ATV_CVBS_OUT_PROP_AMP_MASK;
     break;
    #endif /*     Si2176_ATV_CVBS_OUT_PROP */
    #ifdef        Si2176_ATV_CVBS_OUT_FINE_PROP
     case         Si2176_ATV_CVBS_OUT_FINE_PROP:
               p->atv_cvbs_out_fine.offset = (data >> Si2176_ATV_CVBS_OUT_FINE_PROP_OFFSET_LSB) & Si2176_ATV_CVBS_OUT_FINE_PROP_OFFSET_MASK;
               p->atv_cvbs_out_fine.amp    = (data >> Si2176_ATV_CVBS_OUT_FINE_PROP_AMP_LSB   ) & Si2176_ATV_CVBS_OUT_FINE_PROP_AMP_MASK;
     break;
    #endif /*     Si2176_ATV_CVBS_OUT_FINE_PROP */
    #ifdef        Si2176_ATV_IEN_PROP
     case         Si2176_ATV_IEN_PROP:
               p->atv_ien.chlien  = (data >> Si2176_ATV_IEN_PROP_CHLIEN_LSB ) & Si2176_ATV_IEN_PROP_CHLIEN_MASK;
               p->atv_ien.pclien  = (data >> Si2176_ATV_IEN_PROP_PCLIEN_LSB ) & Si2176_ATV_IEN_PROP_PCLIEN_MASK;
               p->atv_ien.dlien   = (data >> Si2176_ATV_IEN_PROP_DLIEN_LSB  ) & Si2176_ATV_IEN_PROP_DLIEN_MASK;
               p->atv_ien.snrlien = (data >> Si2176_ATV_IEN_PROP_SNRLIEN_LSB) & Si2176_ATV_IEN_PROP_SNRLIEN_MASK;
               p->atv_ien.snrhien = (data >> Si2176_ATV_IEN_PROP_SNRHIEN_LSB) & Si2176_ATV_IEN_PROP_SNRHIEN_MASK;
     break;
    #endif /*     Si2176_ATV_IEN_PROP */
    #ifdef        Si2176_ATV_INT_SENSE_PROP
     case         Si2176_ATV_INT_SENSE_PROP:
               p->atv_int_sense.chlnegen  = (data >> Si2176_ATV_INT_SENSE_PROP_CHLNEGEN_LSB ) & Si2176_ATV_INT_SENSE_PROP_CHLNEGEN_MASK;
               p->atv_int_sense.pclnegen  = (data >> Si2176_ATV_INT_SENSE_PROP_PCLNEGEN_LSB ) & Si2176_ATV_INT_SENSE_PROP_PCLNEGEN_MASK;
               p->atv_int_sense.dlnegen   = (data >> Si2176_ATV_INT_SENSE_PROP_DLNEGEN_LSB  ) & Si2176_ATV_INT_SENSE_PROP_DLNEGEN_MASK;
               p->atv_int_sense.snrlnegen = (data >> Si2176_ATV_INT_SENSE_PROP_SNRLNEGEN_LSB) & Si2176_ATV_INT_SENSE_PROP_SNRLNEGEN_MASK;
               p->atv_int_sense.snrhnegen = (data >> Si2176_ATV_INT_SENSE_PROP_SNRHNEGEN_LSB) & Si2176_ATV_INT_SENSE_PROP_SNRHNEGEN_MASK;
               p->atv_int_sense.chlposen  = (data >> Si2176_ATV_INT_SENSE_PROP_CHLPOSEN_LSB ) & Si2176_ATV_INT_SENSE_PROP_CHLPOSEN_MASK;
               p->atv_int_sense.pclposen  = (data >> Si2176_ATV_INT_SENSE_PROP_PCLPOSEN_LSB ) & Si2176_ATV_INT_SENSE_PROP_PCLPOSEN_MASK;
               p->atv_int_sense.dlposen   = (data >> Si2176_ATV_INT_SENSE_PROP_DLPOSEN_LSB  ) & Si2176_ATV_INT_SENSE_PROP_DLPOSEN_MASK;
               p->atv_int_sense.snrlposen = (data >> Si2176_ATV_INT_SENSE_PROP_SNRLPOSEN_LSB) & Si2176_ATV_INT_SENSE_PROP_SNRLPOSEN_MASK;
               p->atv_int_sense.snrhposen = (data >> Si2176_ATV_INT_SENSE_PROP_SNRHPOSEN_LSB) & Si2176_ATV_INT_SENSE_PROP_SNRHPOSEN_MASK;
     break;
    #endif /*     Si2176_ATV_INT_SENSE_PROP */
   #ifdef        Si2176_ATV_MIN_LVL_LOCK_PROP
     case         Si2176_ATV_MIN_LVL_LOCK_PROP:
               p->atv_min_lvl_lock.thrs = (data >> Si2176_ATV_MIN_LVL_LOCK_PROP_THRS_LSB) & Si2176_ATV_MIN_LVL_LOCK_PROP_THRS_MASK;
     break;
    #endif /*     Si2176_ATV_MIN_LVL_LOCK_PROP */    
    #ifdef        Si2176_ATV_RF_TOP_PROP
     case         Si2176_ATV_RF_TOP_PROP:
               p->atv_rf_top.atv_rf_top = (data >> Si2176_ATV_RF_TOP_PROP_ATV_RF_TOP_LSB) & Si2176_ATV_RF_TOP_PROP_ATV_RF_TOP_MASK;
     break;
    #endif /*     Si2176_ATV_RF_TOP_PROP */
    #ifdef        Si2176_ATV_RSQ_RSSI_THRESHOLD_PROP
     case         Si2176_ATV_RSQ_RSSI_THRESHOLD_PROP:
               p->atv_rsq_rssi_threshold.lo = (data >> Si2176_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_LSB) & Si2176_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_MASK;
               p->atv_rsq_rssi_threshold.hi = (data >> Si2176_ATV_RSQ_RSSI_THRESHOLD_PROP_HI_LSB) & Si2176_ATV_RSQ_RSSI_THRESHOLD_PROP_HI_MASK;
     break;
    #endif /*     Si2176_ATV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef        Si2176_ATV_RSQ_SNR_THRESHOLD_PROP
     case         Si2176_ATV_RSQ_SNR_THRESHOLD_PROP:
               p->atv_rsq_snr_threshold.lo = (data >> Si2176_ATV_RSQ_SNR_THRESHOLD_PROP_LO_LSB) & Si2176_ATV_RSQ_SNR_THRESHOLD_PROP_LO_MASK;
               p->atv_rsq_snr_threshold.hi = (data >> Si2176_ATV_RSQ_SNR_THRESHOLD_PROP_HI_LSB) & Si2176_ATV_RSQ_SNR_THRESHOLD_PROP_HI_MASK;
     break;
    #endif /*     Si2176_ATV_RSQ_SNR_THRESHOLD_PROP */
    #ifdef        Si2176_ATV_SIF_OUT_PROP
     case         Si2176_ATV_SIF_OUT_PROP:
               p->atv_sif_out.offset = (data >> Si2176_ATV_SIF_OUT_PROP_OFFSET_LSB) & Si2176_ATV_SIF_OUT_PROP_OFFSET_MASK;
               p->atv_sif_out.amp    = (data >> Si2176_ATV_SIF_OUT_PROP_AMP_LSB   ) & Si2176_ATV_SIF_OUT_PROP_AMP_MASK;
     break;
    #endif /*     Si2176_ATV_SIF_OUT_PROP */
    #ifdef        Si2176_ATV_SOUND_AGC_LIMIT_PROP
     case         Si2176_ATV_SOUND_AGC_LIMIT_PROP:
               p->atv_sound_agc_limit.max_gain = (data >> Si2176_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN_LSB) & Si2176_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN_MASK;
               p->atv_sound_agc_limit.min_gain = (data >> Si2176_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN_LSB) & Si2176_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN_MASK;
     break;
    #endif /*     Si2176_ATV_SOUND_AGC_LIMIT_PROP */
    #ifdef        Si2176_ATV_SOUND_AGC_SPEED_PROP
     case         Si2176_ATV_SOUND_AGC_SPEED_PROP:
               p->atv_sound_agc_speed.system_l      = (data >> Si2176_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L_LSB     ) & Si2176_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L_MASK;
               p->atv_sound_agc_speed.other_systems = (data >> Si2176_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS_LSB) & Si2176_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS_MASK;
     break;
    #endif /*     Si2176_ATV_SOUND_AGC_SPEED_PROP */    
    #ifdef        Si2176_ATV_VIDEO_EQUALIZER_PROP
     case         Si2176_ATV_VIDEO_EQUALIZER_PROP:
               p->atv_video_equalizer.slope = (data >> Si2176_ATV_VIDEO_EQUALIZER_PROP_SLOPE_LSB) & Si2176_ATV_VIDEO_EQUALIZER_PROP_SLOPE_MASK;
     break;
    #endif /*     Si2176_ATV_VIDEO_EQUALIZER_PROP */
    #ifdef        Si2176_ATV_VIDEO_MODE_PROP
     case         Si2176_ATV_VIDEO_MODE_PROP:
               p->atv_video_mode.video_sys       = (data >> Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_LSB      ) & Si2176_ATV_VIDEO_MODE_PROP_VIDEO_SYS_MASK;
               p->atv_video_mode.color           = (data >> Si2176_ATV_VIDEO_MODE_PROP_COLOR_LSB          ) & Si2176_ATV_VIDEO_MODE_PROP_COLOR_MASK;
               p->atv_video_mode.trans           = (data >> Si2176_ATV_VIDEO_MODE_PROP_TRANS_LSB          ) & Si2176_ATV_VIDEO_MODE_PROP_TRANS_MASK;
               p->atv_video_mode.invert_signal   = (data >> Si2176_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL_LSB  ) & Si2176_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL_MASK;
     break;
    #endif /*     Si2176_ATV_VIDEO_MODE_PROP */
    #ifdef        Si2176_ATV_VSNR_CAP_PROP
     case         Si2176_ATV_VSNR_CAP_PROP:
               p->atv_vsnr_cap.atv_vsnr_cap = (data >> Si2176_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_LSB) & Si2176_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_MASK;
     break;
    #endif /*     Si2176_ATV_VSNR_CAP_PROP */
    #ifdef        Si2176_ATV_VSYNC_TRACKING_PROP
     case         Si2176_ATV_VSYNC_TRACKING_PROP:
               p->atv_vsync_tracking.min_pulses_to_lock   = (data >> Si2176_ATV_VSYNC_TRACKING_PROP_MIN_PULSES_TO_LOCK_LSB  ) & Si2176_ATV_VSYNC_TRACKING_PROP_MIN_PULSES_TO_LOCK_MASK;
               p->atv_vsync_tracking.min_fields_to_unlock = (data >> Si2176_ATV_VSYNC_TRACKING_PROP_MIN_FIELDS_TO_UNLOCK_LSB) & Si2176_ATV_VSYNC_TRACKING_PROP_MIN_FIELDS_TO_UNLOCK_MASK;
     break;
    #endif /*     Si2176_ATV_VSYNC_TRACKING_PROP */
    #ifdef        Si2176_CRYSTAL_TRIM_PROP
     case         Si2176_CRYSTAL_TRIM_PROP:
               p->crystal_trim.xo_cap = (data >> Si2176_CRYSTAL_TRIM_PROP_XO_CAP_LSB) & Si2176_CRYSTAL_TRIM_PROP_XO_CAP_MASK;
     break;
    #endif /*     Si2176_CRYSTAL_TRIM_PROP */
    #ifdef        Si2176_DTV_AGC_SPEED_PROP
     case         Si2176_DTV_AGC_SPEED_PROP:
               p->dtv_agc_speed.if_agc_speed = (data >> Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_LSB) & Si2176_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_MASK;
               p->dtv_agc_speed.agc_decim    = (data >> Si2176_DTV_AGC_SPEED_PROP_AGC_DECIM_LSB   ) & Si2176_DTV_AGC_SPEED_PROP_AGC_DECIM_MASK;
     break;
    #endif /*     Si2176_DTV_AGC_SPEED_PROP */
    #ifdef        Si2176_DTV_CONFIG_IF_PORT_PROP
     case         Si2176_DTV_CONFIG_IF_PORT_PROP:
               p->dtv_config_if_port.dtv_out_type   = (data >> Si2176_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LSB  ) & Si2176_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_MASK;
               p->dtv_config_if_port.dtv_agc_source = (data >> Si2176_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_LSB) & Si2176_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_MASK;
     break;
    #endif /*     Si2176_DTV_CONFIG_IF_PORT_PROP */
    #ifdef        Si2176_DTV_EXT_AGC_PROP
     case         Si2176_DTV_EXT_AGC_PROP:
               p->dtv_ext_agc.min_10mv = (data >> Si2176_DTV_EXT_AGC_PROP_MIN_10MV_LSB) & Si2176_DTV_EXT_AGC_PROP_MIN_10MV_MASK;
               p->dtv_ext_agc.max_10mv = (data >> Si2176_DTV_EXT_AGC_PROP_MAX_10MV_LSB) & Si2176_DTV_EXT_AGC_PROP_MAX_10MV_MASK;
     break;
    #endif /*     Si2176_DTV_EXT_AGC_PROP */
    #ifdef        Si2176_DTV_IEN_PROP
     case         Si2176_DTV_IEN_PROP:
               p->dtv_ien.chlien = (data >> Si2176_DTV_IEN_PROP_CHLIEN_LSB) & Si2176_DTV_IEN_PROP_CHLIEN_MASK;
     break;
    #endif /*     Si2176_DTV_IEN_PROP */
   #ifdef        Si2176_DTV_INITIAL_AGC_SPEED_PROP
     case         Si2176_DTV_INITIAL_AGC_SPEED_PROP:
               p->dtv_initial_agc_speed.if_agc_speed = (data >> Si2176_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_LSB) & Si2176_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_MASK;
               p->dtv_initial_agc_speed.agc_decim    = (data >> Si2176_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_LSB   ) & Si2176_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_MASK;
     break;
    #endif /*     Si2176_DTV_INITIAL_AGC_SPEED_PROP */
    #ifdef        Si2176_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
     case         Si2176_DTV_INITIAL_AGC_SPEED_PERIOD_PROP:
               p->dtv_initial_agc_speed_period.period = (data >> Si2176_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_LSB) & Si2176_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_MASK;
     break;
    #endif /*     Si2176_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */ 
    #ifdef        Si2176_DTV_INT_SENSE_PROP
     case         Si2176_DTV_INT_SENSE_PROP:
               p->dtv_int_sense.chlnegen = (data >> Si2176_DTV_INT_SENSE_PROP_CHLNEGEN_LSB) & Si2176_DTV_INT_SENSE_PROP_CHLNEGEN_MASK;
               p->dtv_int_sense.chlposen = (data >> Si2176_DTV_INT_SENSE_PROP_CHLPOSEN_LSB) & Si2176_DTV_INT_SENSE_PROP_CHLPOSEN_MASK;
     break;
    #endif /*     Si2176_DTV_INT_SENSE_PROP */
    #ifdef        Si2176_DTV_LIF_FREQ_PROP
     case         Si2176_DTV_LIF_FREQ_PROP:
               p->dtv_lif_freq.offset = (data >> Si2176_DTV_LIF_FREQ_PROP_OFFSET_LSB) & Si2176_DTV_LIF_FREQ_PROP_OFFSET_MASK;
     break;
    #endif /*     Si2176_DTV_LIF_FREQ_PROP */
    #ifdef        Si2176_DTV_LIF_OUT_PROP
     case         Si2176_DTV_LIF_OUT_PROP:
               p->dtv_lif_out.offset = (data >> Si2176_DTV_LIF_OUT_PROP_OFFSET_LSB) & Si2176_DTV_LIF_OUT_PROP_OFFSET_MASK;
               p->dtv_lif_out.amp    = (data >> Si2176_DTV_LIF_OUT_PROP_AMP_LSB   ) & Si2176_DTV_LIF_OUT_PROP_AMP_MASK;
     break;
    #endif /*     Si2176_DTV_LIF_OUT_PROP */
    #ifdef        Si2176_DTV_MODE_PROP
     case         Si2176_DTV_MODE_PROP:
               p->dtv_mode.bw              = (data >> Si2176_DTV_MODE_PROP_BW_LSB             ) & Si2176_DTV_MODE_PROP_BW_MASK;
               p->dtv_mode.modulation      = (data >> Si2176_DTV_MODE_PROP_MODULATION_LSB     ) & Si2176_DTV_MODE_PROP_MODULATION_MASK;
               p->dtv_mode.invert_spectrum = (data >> Si2176_DTV_MODE_PROP_INVERT_SPECTRUM_LSB) & Si2176_DTV_MODE_PROP_INVERT_SPECTRUM_MASK;
     break;
    #endif /*     Si2176_DTV_MODE_PROP */
    #ifdef        Si2176_DTV_RF_TOP_PROP
     case         Si2176_DTV_RF_TOP_PROP:
               p->dtv_rf_top.dtv_rf_top = (data >> Si2176_DTV_RF_TOP_PROP_DTV_RF_TOP_LSB) & Si2176_DTV_RF_TOP_PROP_DTV_RF_TOP_MASK;
     break;
    #endif /*     Si2176_DTV_RF_TOP_PROP */
    #ifdef        Si2176_DTV_RSQ_RSSI_THRESHOLD_PROP
     case         Si2176_DTV_RSQ_RSSI_THRESHOLD_PROP:
               p->dtv_rsq_rssi_threshold.lo = (data >> Si2176_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_LSB) & Si2176_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_MASK;
               p->dtv_rsq_rssi_threshold.hi = (data >> Si2176_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_LSB) & Si2176_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_MASK;
     break;
    #endif /*     Si2176_DTV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef        Si2176_MASTER_IEN_PROP
     case         Si2176_MASTER_IEN_PROP:
               p->master_ien.tunien = (data >> Si2176_MASTER_IEN_PROP_TUNIEN_LSB) & Si2176_MASTER_IEN_PROP_TUNIEN_MASK;
               p->master_ien.atvien = (data >> Si2176_MASTER_IEN_PROP_ATVIEN_LSB) & Si2176_MASTER_IEN_PROP_ATVIEN_MASK;
               p->master_ien.dtvien = (data >> Si2176_MASTER_IEN_PROP_DTVIEN_LSB) & Si2176_MASTER_IEN_PROP_DTVIEN_MASK;
               p->master_ien.errien = (data >> Si2176_MASTER_IEN_PROP_ERRIEN_LSB) & Si2176_MASTER_IEN_PROP_ERRIEN_MASK;
               p->master_ien.ctsien = (data >> Si2176_MASTER_IEN_PROP_CTSIEN_LSB) & Si2176_MASTER_IEN_PROP_CTSIEN_MASK;
     break;
    #endif /*     Si2176_MASTER_IEN_PROP */
    #ifdef        Si2176_TUNER_BLOCKED_VCO_PROP
     case         Si2176_TUNER_BLOCKED_VCO_PROP:
               p->tuner_blocked_vco.vco_code = (data >> Si2176_TUNER_BLOCKED_VCO_PROP_VCO_CODE_LSB) & Si2176_TUNER_BLOCKED_VCO_PROP_VCO_CODE_MASK;
     break;
    #endif /*     Si2176_TUNER_BLOCKED_VCO_PROP */
    #ifdef        Si2176_TUNER_IEN_PROP
     case         Si2176_TUNER_IEN_PROP:
               p->tuner_ien.tcien    = (data >> Si2176_TUNER_IEN_PROP_TCIEN_LSB   ) & Si2176_TUNER_IEN_PROP_TCIEN_MASK;
               p->tuner_ien.rssilien = (data >> Si2176_TUNER_IEN_PROP_RSSILIEN_LSB) & Si2176_TUNER_IEN_PROP_RSSILIEN_MASK;
               p->tuner_ien.rssihien = (data >> Si2176_TUNER_IEN_PROP_RSSIHIEN_LSB) & Si2176_TUNER_IEN_PROP_RSSIHIEN_MASK;
     break;
    #endif /*     Si2176_TUNER_IEN_PROP */
    #ifdef        Si2176_TUNER_INT_SENSE_PROP
     case         Si2176_TUNER_INT_SENSE_PROP:
               p->tuner_int_sense.tcnegen    = (data >> Si2176_TUNER_INT_SENSE_PROP_TCNEGEN_LSB   ) & Si2176_TUNER_INT_SENSE_PROP_TCNEGEN_MASK;
               p->tuner_int_sense.rssilnegen = (data >> Si2176_TUNER_INT_SENSE_PROP_RSSILNEGEN_LSB) & Si2176_TUNER_INT_SENSE_PROP_RSSILNEGEN_MASK;
               p->tuner_int_sense.rssihnegen = (data >> Si2176_TUNER_INT_SENSE_PROP_RSSIHNEGEN_LSB) & Si2176_TUNER_INT_SENSE_PROP_RSSIHNEGEN_MASK;
               p->tuner_int_sense.tcposen    = (data >> Si2176_TUNER_INT_SENSE_PROP_TCPOSEN_LSB   ) & Si2176_TUNER_INT_SENSE_PROP_TCPOSEN_MASK;
               p->tuner_int_sense.rssilposen = (data >> Si2176_TUNER_INT_SENSE_PROP_RSSILPOSEN_LSB) & Si2176_TUNER_INT_SENSE_PROP_RSSILPOSEN_MASK;
               p->tuner_int_sense.rssihposen = (data >> Si2176_TUNER_INT_SENSE_PROP_RSSIHPOSEN_LSB) & Si2176_TUNER_INT_SENSE_PROP_RSSIHPOSEN_MASK;
     break;
    #endif /*     Si2176_TUNER_INT_SENSE_PROP */
    #ifdef        Si2176_TUNER_LO_INJECTION_PROP
     case         Si2176_TUNER_LO_INJECTION_PROP:
               p->tuner_lo_injection.band_1 = (data >> Si2176_TUNER_LO_INJECTION_PROP_BAND_1_LSB) & Si2176_TUNER_LO_INJECTION_PROP_BAND_1_MASK;
               p->tuner_lo_injection.band_2 = (data >> Si2176_TUNER_LO_INJECTION_PROP_BAND_2_LSB) & Si2176_TUNER_LO_INJECTION_PROP_BAND_2_MASK;
               p->tuner_lo_injection.band_3 = (data >> Si2176_TUNER_LO_INJECTION_PROP_BAND_3_LSB) & Si2176_TUNER_LO_INJECTION_PROP_BAND_3_MASK;
               p->tuner_lo_injection.band_4 = (data >> Si2176_TUNER_LO_INJECTION_PROP_BAND_4_LSB) & Si2176_TUNER_LO_INJECTION_PROP_BAND_4_MASK;
               p->tuner_lo_injection.band_5 = (data >> Si2176_TUNER_LO_INJECTION_PROP_BAND_5_LSB) & Si2176_TUNER_LO_INJECTION_PROP_BAND_5_MASK;
     break;
    #endif /*     Si2176_TUNER_LO_INJECTION_PROP */
   default : break;
    }
    return res;
  }
  /* _get_property2_insertion_point */

/* End of template (2011 January 24 at 13:47) */



