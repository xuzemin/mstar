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
/*************************************************************************************
                  Silicon Laboratories Broadcast Si2158 Layer 1 API
   API properties definitions
   FILE: Si2158_L1_Properties.c
   Supported IC : Si2158
   Compiled for ROM 33 firmware 2_1_build_9
   Revision: 0.1
   Tag:  ROM33_2_1_build_9_V0.1
   Date: March 20 2013
  (C) Copyright 2013, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
// #define   Si2158_COMMAND_PROTOTYPES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Si2158_L1_API.h"

/***********************************************************************************************************************
  Si2158_L1_SetProperty function
  Use:        property set function
              Used to call L1_SET_PROPERTY with the property Id and data provided.
  Parameter: *api     the Si2158 context
  Parameter: prop     the property Id
  Parameter: data     the property bytes
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/
unsigned char Si2158_L1_SetProperty(L1_Si2158_Context *api, unsigned int prop, int  data)  {
    unsigned char  reserved          = 0;
    return Si2158_L1_SET_PROPERTY (api, reserved, prop, data);
}

/***********************************************************************************************************************
  Si2158_L1_GetProperty function
  Use:        property get function
              Used to call L1_GET_PROPERTY with the property Id provided.
  Parameter: *api     the Si2158 context
  Parameter: prop     the property Id
  Parameter: *data    a buffer to store the property bytes into
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/
unsigned char    Si2158_L1_GetProperty(L1_Si2158_Context *api, unsigned int prop, int *data) {
    unsigned char  reserved          = 0;
    unsigned char res;
    res = Si2158_L1_GET_PROPERTY (api, reserved, prop);
    *data = api->rsp->get_property.data;
    return res;
}

/* _set_property2_insertion_start */

  /* --------------------------------------------*/
  /* SET_PROPERTY2 FUNCTION                      */
  /* --------------------------------------------*/
unsigned char Si2158_L1_SetProperty2(L1_Si2158_Context *api, unsigned int prop_code) {
    int data = 0;
#ifdef    Si2158_GET_PROPERTY_STRING
    char msg[1000];
#endif /* Si2158_GET_PROPERTY_STRING */
    switch (prop_code) {
    #ifdef        Si2158_ATV_AFC_RANGE_PROP
     case         Si2158_ATV_AFC_RANGE_PROP_CODE:
       data = (api->prop->atv_afc_range.range_khz & Si2158_ATV_AFC_RANGE_PROP_RANGE_KHZ_MASK) << Si2158_ATV_AFC_RANGE_PROP_RANGE_KHZ_LSB ;
     break;
    #endif /*     Si2158_ATV_AFC_RANGE_PROP */
    #ifdef        Si2158_ATV_AGC_SPEED_PROP
     case         Si2158_ATV_AGC_SPEED_PROP_CODE:
       data = (api->prop->atv_agc_speed.if_agc_speed & Si2158_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_MASK) << Si2158_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_LSB ;
     break;
    #endif /*     Si2158_ATV_AGC_SPEED_PROP */
    #ifdef        Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP
     case         Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP_CODE:
       data = (api->prop->atv_agc_speed_low_rssi.if_agc_speed & Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_MASK) << Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_LSB  |
              (api->prop->atv_agc_speed_low_rssi.thld         & Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD_MASK        ) << Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD_LSB ;
     break;
    #endif /*     Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP */
    #ifdef        Si2158_ATV_ARTIFICIAL_SNOW_PROP
     case         Si2158_ATV_ARTIFICIAL_SNOW_PROP_CODE:
       data = (api->prop->atv_artificial_snow.gain   & Si2158_ATV_ARTIFICIAL_SNOW_PROP_GAIN_MASK  ) << Si2158_ATV_ARTIFICIAL_SNOW_PROP_GAIN_LSB  |
              (api->prop->atv_artificial_snow.offset & Si2158_ATV_ARTIFICIAL_SNOW_PROP_OFFSET_MASK) << Si2158_ATV_ARTIFICIAL_SNOW_PROP_OFFSET_LSB ;
     break;
    #endif /*     Si2158_ATV_ARTIFICIAL_SNOW_PROP */
    #ifdef        Si2158_ATV_CONFIG_IF_PORT_PROP
     case         Si2158_ATV_CONFIG_IF_PORT_PROP_CODE:
       data = (api->prop->atv_config_if_port.atv_out_type   & Si2158_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE_MASK  ) << Si2158_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE_LSB  |
              (api->prop->atv_config_if_port.atv_agc_source & Si2158_ATV_CONFIG_IF_PORT_PROP_ATV_AGC_SOURCE_MASK) << Si2158_ATV_CONFIG_IF_PORT_PROP_ATV_AGC_SOURCE_LSB ;
     break;
    #endif /*     Si2158_ATV_CONFIG_IF_PORT_PROP */
    #ifdef        Si2158_ATV_EXT_AGC_PROP
     case         Si2158_ATV_EXT_AGC_PROP_CODE:
       data = (api->prop->atv_ext_agc.min_10mv & Si2158_ATV_EXT_AGC_PROP_MIN_10MV_MASK) << Si2158_ATV_EXT_AGC_PROP_MIN_10MV_LSB  |
              (api->prop->atv_ext_agc.max_10mv & Si2158_ATV_EXT_AGC_PROP_MAX_10MV_MASK) << Si2158_ATV_EXT_AGC_PROP_MAX_10MV_LSB ;
     break;
    #endif /*     Si2158_ATV_EXT_AGC_PROP */
    #ifdef        Si2158_ATV_IEN_PROP
     case         Si2158_ATV_IEN_PROP_CODE:
       data = (api->prop->atv_ien.chlien & Si2158_ATV_IEN_PROP_CHLIEN_MASK) << Si2158_ATV_IEN_PROP_CHLIEN_LSB  |
              (api->prop->atv_ien.pclien & Si2158_ATV_IEN_PROP_PCLIEN_MASK) << Si2158_ATV_IEN_PROP_PCLIEN_LSB ;
     break;
    #endif /*     Si2158_ATV_IEN_PROP */
    #ifdef        Si2158_ATV_INT_SENSE_PROP
     case         Si2158_ATV_INT_SENSE_PROP_CODE:
       data = (api->prop->atv_int_sense.chlnegen & Si2158_ATV_INT_SENSE_PROP_CHLNEGEN_MASK) << Si2158_ATV_INT_SENSE_PROP_CHLNEGEN_LSB  |
              (api->prop->atv_int_sense.pclnegen & Si2158_ATV_INT_SENSE_PROP_PCLNEGEN_MASK) << Si2158_ATV_INT_SENSE_PROP_PCLNEGEN_LSB  |
              (api->prop->atv_int_sense.chlposen & Si2158_ATV_INT_SENSE_PROP_CHLPOSEN_MASK) << Si2158_ATV_INT_SENSE_PROP_CHLPOSEN_LSB  |
              (api->prop->atv_int_sense.pclposen & Si2158_ATV_INT_SENSE_PROP_PCLPOSEN_MASK) << Si2158_ATV_INT_SENSE_PROP_PCLPOSEN_LSB ;
     break;
    #endif /*     Si2158_ATV_INT_SENSE_PROP */
    #ifdef        Si2158_ATV_LIF_FREQ_PROP
     case         Si2158_ATV_LIF_FREQ_PROP_CODE:
       data = (api->prop->atv_lif_freq.offset & Si2158_ATV_LIF_FREQ_PROP_OFFSET_MASK) << Si2158_ATV_LIF_FREQ_PROP_OFFSET_LSB ;
     break;
    #endif /*     Si2158_ATV_LIF_FREQ_PROP */
    #ifdef        Si2158_ATV_LIF_OUT_PROP
     case         Si2158_ATV_LIF_OUT_PROP_CODE:
       data = (api->prop->atv_lif_out.offset & Si2158_ATV_LIF_OUT_PROP_OFFSET_MASK) << Si2158_ATV_LIF_OUT_PROP_OFFSET_LSB  |
              (api->prop->atv_lif_out.amp    & Si2158_ATV_LIF_OUT_PROP_AMP_MASK   ) << Si2158_ATV_LIF_OUT_PROP_AMP_LSB ;
     break;
    #endif /*     Si2158_ATV_LIF_OUT_PROP */
    #ifdef        Si2158_ATV_PGA_TARGET_PROP
     case         Si2158_ATV_PGA_TARGET_PROP_CODE:
       data = (api->prop->atv_pga_target.pga_target      & Si2158_ATV_PGA_TARGET_PROP_PGA_TARGET_MASK     ) << Si2158_ATV_PGA_TARGET_PROP_PGA_TARGET_LSB  |
              (api->prop->atv_pga_target.override_enable & Si2158_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_MASK) << Si2158_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_LSB ;
     break;
    #endif /*     Si2158_ATV_PGA_TARGET_PROP */
    #ifdef        Si2158_ATV_RF_TOP_PROP
     case         Si2158_ATV_RF_TOP_PROP_CODE:
       data = (api->prop->atv_rf_top.atv_rf_top & Si2158_ATV_RF_TOP_PROP_ATV_RF_TOP_MASK) << Si2158_ATV_RF_TOP_PROP_ATV_RF_TOP_LSB ;
     break;
    #endif /*     Si2158_ATV_RF_TOP_PROP */
    #ifdef        Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP
     case         Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP_CODE:
       data = (api->prop->atv_rsq_rssi_threshold.lo & Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_MASK) << Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_LSB  |
              (api->prop->atv_rsq_rssi_threshold.hi & Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP_HI_MASK) << Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP_HI_LSB ;
     break;
    #endif /*     Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef        Si2158_ATV_VIDEO_MODE_PROP
     case         Si2158_ATV_VIDEO_MODE_PROP_CODE:
       data = (api->prop->atv_video_mode.video_sys       & Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_MASK      ) << Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_LSB  |
              (api->prop->atv_video_mode.color           & Si2158_ATV_VIDEO_MODE_PROP_COLOR_MASK          ) << Si2158_ATV_VIDEO_MODE_PROP_COLOR_LSB  |
              (api->prop->atv_video_mode.invert_spectrum & Si2158_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_MASK) << Si2158_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_LSB ;
     break;
    #endif /*     Si2158_ATV_VIDEO_MODE_PROP */
    #ifdef        Si2158_ATV_VSNR_CAP_PROP
     case         Si2158_ATV_VSNR_CAP_PROP_CODE:
       data = (api->prop->atv_vsnr_cap.atv_vsnr_cap & Si2158_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_MASK) << Si2158_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_LSB ;
     break;
    #endif /*     Si2158_ATV_VSNR_CAP_PROP */
    #ifdef        Si2158_CRYSTAL_TRIM_PROP
     case         Si2158_CRYSTAL_TRIM_PROP_CODE:
       data = (api->prop->crystal_trim.xo_cap & Si2158_CRYSTAL_TRIM_PROP_XO_CAP_MASK) << Si2158_CRYSTAL_TRIM_PROP_XO_CAP_LSB ;
     break;
    #endif /*     Si2158_CRYSTAL_TRIM_PROP */
    #ifdef        Si2158_DEBUG_SAMPLE_FREQ_PROP
     case         Si2158_DEBUG_SAMPLE_FREQ_PROP_CODE:
       data = (api->prop->debug_sample_freq.fs_mhz & Si2158_DEBUG_SAMPLE_FREQ_PROP_FS_MHZ_MASK) << Si2158_DEBUG_SAMPLE_FREQ_PROP_FS_MHZ_LSB ;
     break;
    #endif /*     Si2158_DEBUG_SAMPLE_FREQ_PROP */
    #ifdef        Si2158_DTV_AGC_FREEZE_INPUT_PROP
     case         Si2158_DTV_AGC_FREEZE_INPUT_PROP_CODE:
       data = (api->prop->dtv_agc_freeze_input.level & Si2158_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_MASK) << Si2158_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_LSB  |
              (api->prop->dtv_agc_freeze_input.pin   & Si2158_DTV_AGC_FREEZE_INPUT_PROP_PIN_MASK  ) << Si2158_DTV_AGC_FREEZE_INPUT_PROP_PIN_LSB ;
     break;
    #endif /*     Si2158_DTV_AGC_FREEZE_INPUT_PROP */
    #ifdef        Si2158_DTV_AGC_SPEED_PROP
     case         Si2158_DTV_AGC_SPEED_PROP_CODE:
       data = (api->prop->dtv_agc_speed.if_agc_speed & Si2158_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_MASK) << Si2158_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_LSB  |
              (api->prop->dtv_agc_speed.agc_decim    & Si2158_DTV_AGC_SPEED_PROP_AGC_DECIM_MASK   ) << Si2158_DTV_AGC_SPEED_PROP_AGC_DECIM_LSB ;
     break;
    #endif /*     Si2158_DTV_AGC_SPEED_PROP */
    #ifdef        Si2158_DTV_CONFIG_IF_PORT_PROP
     case         Si2158_DTV_CONFIG_IF_PORT_PROP_CODE:
       data = (api->prop->dtv_config_if_port.dtv_out_type   & Si2158_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_MASK  ) << Si2158_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LSB  |
              (api->prop->dtv_config_if_port.dtv_agc_source & Si2158_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_MASK) << Si2158_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_LSB ;
     break;
    #endif /*     Si2158_DTV_CONFIG_IF_PORT_PROP */
    #ifdef        Si2158_DTV_EXT_AGC_PROP
     case         Si2158_DTV_EXT_AGC_PROP_CODE:
       data = (api->prop->dtv_ext_agc.min_10mv & Si2158_DTV_EXT_AGC_PROP_MIN_10MV_MASK) << Si2158_DTV_EXT_AGC_PROP_MIN_10MV_LSB  |
              (api->prop->dtv_ext_agc.max_10mv & Si2158_DTV_EXT_AGC_PROP_MAX_10MV_MASK) << Si2158_DTV_EXT_AGC_PROP_MAX_10MV_LSB ;
     break;
    #endif /*     Si2158_DTV_EXT_AGC_PROP */
    #ifdef        Si2158_DTV_FILTER_SELECT_PROP
     case         Si2158_DTV_FILTER_SELECT_PROP_CODE:
       data = (api->prop->dtv_filter_select.filter & Si2158_DTV_FILTER_SELECT_PROP_FILTER_MASK) << Si2158_DTV_FILTER_SELECT_PROP_FILTER_LSB ;
     break;
    #endif /*     Si2158_DTV_FILTER_SELECT_PROP */
    #ifdef        Si2158_DTV_IEN_PROP
     case         Si2158_DTV_IEN_PROP_CODE:
       data = (api->prop->dtv_ien.chlien & Si2158_DTV_IEN_PROP_CHLIEN_MASK) << Si2158_DTV_IEN_PROP_CHLIEN_LSB ;
     break;
    #endif /*     Si2158_DTV_IEN_PROP */
    #ifdef        Si2158_DTV_INITIAL_AGC_SPEED_PROP
     case         Si2158_DTV_INITIAL_AGC_SPEED_PROP_CODE:
       data = (api->prop->dtv_initial_agc_speed.if_agc_speed & Si2158_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_MASK) << Si2158_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_LSB  |
              (api->prop->dtv_initial_agc_speed.agc_decim    & Si2158_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_MASK   ) << Si2158_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_LSB ;
     break;
    #endif /*     Si2158_DTV_INITIAL_AGC_SPEED_PROP */
    #ifdef        Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
     case         Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_CODE:
       data = (api->prop->dtv_initial_agc_speed_period.period & Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_MASK) << Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_LSB ;
     break;
    #endif /*     Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */
    #ifdef        Si2158_DTV_INTERNAL_ZIF_PROP
     case         Si2158_DTV_INTERNAL_ZIF_PROP_CODE:
       data = (api->prop->dtv_internal_zif.atsc   & Si2158_DTV_INTERNAL_ZIF_PROP_ATSC_MASK  ) << Si2158_DTV_INTERNAL_ZIF_PROP_ATSC_LSB  |
              (api->prop->dtv_internal_zif.qam_us & Si2158_DTV_INTERNAL_ZIF_PROP_QAM_US_MASK) << Si2158_DTV_INTERNAL_ZIF_PROP_QAM_US_LSB  |
              (api->prop->dtv_internal_zif.dvbt   & Si2158_DTV_INTERNAL_ZIF_PROP_DVBT_MASK  ) << Si2158_DTV_INTERNAL_ZIF_PROP_DVBT_LSB  |
              (api->prop->dtv_internal_zif.dvbc   & Si2158_DTV_INTERNAL_ZIF_PROP_DVBC_MASK  ) << Si2158_DTV_INTERNAL_ZIF_PROP_DVBC_LSB  |
              (api->prop->dtv_internal_zif.isdbt  & Si2158_DTV_INTERNAL_ZIF_PROP_ISDBT_MASK ) << Si2158_DTV_INTERNAL_ZIF_PROP_ISDBT_LSB  |
              (api->prop->dtv_internal_zif.isdbc  & Si2158_DTV_INTERNAL_ZIF_PROP_ISDBC_MASK ) << Si2158_DTV_INTERNAL_ZIF_PROP_ISDBC_LSB  |
              (api->prop->dtv_internal_zif.dtmb   & Si2158_DTV_INTERNAL_ZIF_PROP_DTMB_MASK  ) << Si2158_DTV_INTERNAL_ZIF_PROP_DTMB_LSB ;
     break;
    #endif /*     Si2158_DTV_INTERNAL_ZIF_PROP */
    #ifdef        Si2158_DTV_INT_SENSE_PROP
     case         Si2158_DTV_INT_SENSE_PROP_CODE:
       data = (api->prop->dtv_int_sense.chlnegen & Si2158_DTV_INT_SENSE_PROP_CHLNEGEN_MASK) << Si2158_DTV_INT_SENSE_PROP_CHLNEGEN_LSB  |
              (api->prop->dtv_int_sense.chlposen & Si2158_DTV_INT_SENSE_PROP_CHLPOSEN_MASK) << Si2158_DTV_INT_SENSE_PROP_CHLPOSEN_LSB ;
     break;
    #endif /*     Si2158_DTV_INT_SENSE_PROP */
    #ifdef        Si2158_DTV_LIF_FREQ_PROP
     case         Si2158_DTV_LIF_FREQ_PROP_CODE:
       data = (api->prop->dtv_lif_freq.offset & Si2158_DTV_LIF_FREQ_PROP_OFFSET_MASK) << Si2158_DTV_LIF_FREQ_PROP_OFFSET_LSB ;
     break;
    #endif /*     Si2158_DTV_LIF_FREQ_PROP */
    #ifdef        Si2158_DTV_LIF_OUT_PROP
     case         Si2158_DTV_LIF_OUT_PROP_CODE:
       data = (api->prop->dtv_lif_out.offset & Si2158_DTV_LIF_OUT_PROP_OFFSET_MASK) << Si2158_DTV_LIF_OUT_PROP_OFFSET_LSB  |
              (api->prop->dtv_lif_out.amp    & Si2158_DTV_LIF_OUT_PROP_AMP_MASK   ) << Si2158_DTV_LIF_OUT_PROP_AMP_LSB ;
     break;
    #endif /*     Si2158_DTV_LIF_OUT_PROP */
    #ifdef        Si2158_DTV_MODE_PROP
     case         Si2158_DTV_MODE_PROP_CODE:
       data = (api->prop->dtv_mode.bw              & Si2158_DTV_MODE_PROP_BW_MASK             ) << Si2158_DTV_MODE_PROP_BW_LSB  |
              (api->prop->dtv_mode.modulation      & Si2158_DTV_MODE_PROP_MODULATION_MASK     ) << Si2158_DTV_MODE_PROP_MODULATION_LSB  |
              (api->prop->dtv_mode.invert_spectrum & Si2158_DTV_MODE_PROP_INVERT_SPECTRUM_MASK) << Si2158_DTV_MODE_PROP_INVERT_SPECTRUM_LSB ;
     break;
    #endif /*     Si2158_DTV_MODE_PROP */
    #ifdef        Si2158_DTV_PGA_LIMITS_PROP
     case         Si2158_DTV_PGA_LIMITS_PROP_CODE:
       data = (api->prop->dtv_pga_limits.min & Si2158_DTV_PGA_LIMITS_PROP_MIN_MASK) << Si2158_DTV_PGA_LIMITS_PROP_MIN_LSB  |
              (api->prop->dtv_pga_limits.max & Si2158_DTV_PGA_LIMITS_PROP_MAX_MASK) << Si2158_DTV_PGA_LIMITS_PROP_MAX_LSB ;
     break;
    #endif /*     Si2158_DTV_PGA_LIMITS_PROP */
    #ifdef        Si2158_DTV_PGA_TARGET_PROP
     case         Si2158_DTV_PGA_TARGET_PROP_CODE:
       data = (api->prop->dtv_pga_target.pga_target      & Si2158_DTV_PGA_TARGET_PROP_PGA_TARGET_MASK     ) << Si2158_DTV_PGA_TARGET_PROP_PGA_TARGET_LSB  |
              (api->prop->dtv_pga_target.override_enable & Si2158_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE_MASK) << Si2158_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE_LSB ;
     break;
    #endif /*     Si2158_DTV_PGA_TARGET_PROP */
    #ifdef        Si2158_DTV_RF_TOP_PROP
     case         Si2158_DTV_RF_TOP_PROP_CODE:
       data = (api->prop->dtv_rf_top.dtv_rf_top & Si2158_DTV_RF_TOP_PROP_DTV_RF_TOP_MASK) << Si2158_DTV_RF_TOP_PROP_DTV_RF_TOP_LSB ;
     break;
    #endif /*     Si2158_DTV_RF_TOP_PROP */
    #ifdef        Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP
     case         Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP_CODE:
       data = (api->prop->dtv_rsq_rssi_threshold.lo & Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_MASK) << Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_LSB  |
              (api->prop->dtv_rsq_rssi_threshold.hi & Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_MASK) << Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_LSB ;
     break;
    #endif /*     Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef        Si2158_DTV_ZIF_DC_CANCELLER_BW_PROP
     case         Si2158_DTV_ZIF_DC_CANCELLER_BW_PROP_CODE:
       data = (api->prop->dtv_zif_dc_canceller_bw.bandwidth & Si2158_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_MASK) << Si2158_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_LSB ;
     break;
    #endif /*     Si2158_DTV_ZIF_DC_CANCELLER_BW_PROP */
    #ifdef        Si2158_MASTER_IEN_PROP
     case         Si2158_MASTER_IEN_PROP_CODE:
       data = (api->prop->master_ien.tunien & Si2158_MASTER_IEN_PROP_TUNIEN_MASK) << Si2158_MASTER_IEN_PROP_TUNIEN_LSB  |
              (api->prop->master_ien.atvien & Si2158_MASTER_IEN_PROP_ATVIEN_MASK) << Si2158_MASTER_IEN_PROP_ATVIEN_LSB  |
              (api->prop->master_ien.dtvien & Si2158_MASTER_IEN_PROP_DTVIEN_MASK) << Si2158_MASTER_IEN_PROP_DTVIEN_LSB  |
              (api->prop->master_ien.errien & Si2158_MASTER_IEN_PROP_ERRIEN_MASK) << Si2158_MASTER_IEN_PROP_ERRIEN_LSB  |
              (api->prop->master_ien.ctsien & Si2158_MASTER_IEN_PROP_CTSIEN_MASK) << Si2158_MASTER_IEN_PROP_CTSIEN_LSB ;
     break;
    #endif /*     Si2158_MASTER_IEN_PROP */
    #ifdef        Si2158_TUNER_BLOCKED_VCO_PROP
     case         Si2158_TUNER_BLOCKED_VCO_PROP_CODE:
       data = (api->prop->tuner_blocked_vco.vco_code & Si2158_TUNER_BLOCKED_VCO_PROP_VCO_CODE_MASK) << Si2158_TUNER_BLOCKED_VCO_PROP_VCO_CODE_LSB ;
     break;
    #endif /*     Si2158_TUNER_BLOCKED_VCO_PROP */
    #ifdef        Si2158_TUNER_IEN_PROP
     case         Si2158_TUNER_IEN_PROP_CODE:
       data = (api->prop->tuner_ien.tcien    & Si2158_TUNER_IEN_PROP_TCIEN_MASK   ) << Si2158_TUNER_IEN_PROP_TCIEN_LSB  |
              (api->prop->tuner_ien.rssilien & Si2158_TUNER_IEN_PROP_RSSILIEN_MASK) << Si2158_TUNER_IEN_PROP_RSSILIEN_LSB  |
              (api->prop->tuner_ien.rssihien & Si2158_TUNER_IEN_PROP_RSSIHIEN_MASK) << Si2158_TUNER_IEN_PROP_RSSIHIEN_LSB ;
     break;
    #endif /*     Si2158_TUNER_IEN_PROP */
    #ifdef        Si2158_TUNER_INT_SENSE_PROP
     case         Si2158_TUNER_INT_SENSE_PROP_CODE:
       data = (api->prop->tuner_int_sense.tcnegen    & Si2158_TUNER_INT_SENSE_PROP_TCNEGEN_MASK   ) << Si2158_TUNER_INT_SENSE_PROP_TCNEGEN_LSB  |
              (api->prop->tuner_int_sense.rssilnegen & Si2158_TUNER_INT_SENSE_PROP_RSSILNEGEN_MASK) << Si2158_TUNER_INT_SENSE_PROP_RSSILNEGEN_LSB  |
              (api->prop->tuner_int_sense.rssihnegen & Si2158_TUNER_INT_SENSE_PROP_RSSIHNEGEN_MASK) << Si2158_TUNER_INT_SENSE_PROP_RSSIHNEGEN_LSB  |
              (api->prop->tuner_int_sense.tcposen    & Si2158_TUNER_INT_SENSE_PROP_TCPOSEN_MASK   ) << Si2158_TUNER_INT_SENSE_PROP_TCPOSEN_LSB  |
              (api->prop->tuner_int_sense.rssilposen & Si2158_TUNER_INT_SENSE_PROP_RSSILPOSEN_MASK) << Si2158_TUNER_INT_SENSE_PROP_RSSILPOSEN_LSB  |
              (api->prop->tuner_int_sense.rssihposen & Si2158_TUNER_INT_SENSE_PROP_RSSIHPOSEN_MASK) << Si2158_TUNER_INT_SENSE_PROP_RSSIHPOSEN_LSB ;
     break;
    #endif /*     Si2158_TUNER_INT_SENSE_PROP */
    #ifdef        Si2158_TUNER_LO_INJECTION_PROP
     case         Si2158_TUNER_LO_INJECTION_PROP_CODE:
       data = (api->prop->tuner_lo_injection.band_1 & Si2158_TUNER_LO_INJECTION_PROP_BAND_1_MASK) << Si2158_TUNER_LO_INJECTION_PROP_BAND_1_LSB  |
              (api->prop->tuner_lo_injection.band_2 & Si2158_TUNER_LO_INJECTION_PROP_BAND_2_MASK) << Si2158_TUNER_LO_INJECTION_PROP_BAND_2_LSB  |
              (api->prop->tuner_lo_injection.band_3 & Si2158_TUNER_LO_INJECTION_PROP_BAND_3_MASK) << Si2158_TUNER_LO_INJECTION_PROP_BAND_3_LSB ;
     break;
    #endif /*     Si2158_TUNER_LO_INJECTION_PROP */
    #ifdef        Si2158_TUNER_RETURN_LOSS_PROP
     case         Si2158_TUNER_RETURN_LOSS_PROP_CODE:
       data = (api->prop->tuner_return_loss.config & Si2158_TUNER_RETURN_LOSS_PROP_CONFIG_MASK) << Si2158_TUNER_RETURN_LOSS_PROP_CONFIG_LSB  |
              (api->prop->tuner_return_loss.mode   & Si2158_TUNER_RETURN_LOSS_PROP_MODE_MASK  ) << Si2158_TUNER_RETURN_LOSS_PROP_MODE_LSB ;
     break;
    #endif /*     Si2158_TUNER_RETURN_LOSS_PROP */
    #ifdef        Si2158_XOUT_PROP
     case         Si2158_XOUT_PROP_CODE:
       data = (api->prop->xout.amp & Si2158_XOUT_PROP_AMP_MASK) << Si2158_XOUT_PROP_AMP_LSB ;
     break;
    #endif /*     Si2158_XOUT_PROP */
   default : break;
    }
#ifdef    Si2158_GET_PROPERTY_STRING
    Si2158_L1_FillPropertyStringText(api, prop_code, (char*)" ", msg);
    SiTRACE("%s\n",msg);
#endif /* Si2158_GET_PROPERTY_STRING */
    return Si2158_L1_SetProperty(api, prop_code & 0xffff , data);
  }

/* _set_property2_insertion_point */

/* _get_property2_insertion_start */

  /* --------------------------------------------*/
  /* GET_PROPERTY2 FUNCTION                       */
  /* --------------------------------------------*/
unsigned char Si2158_L1_GetProperty2(L1_Si2158_Context *api, unsigned int prop_code) {
    int data, res;
    res = Si2158_L1_GetProperty(api,prop_code & 0xffff,&data);
    if (res!=NO_Si2158_ERROR) return res;
    switch (prop_code) {
    #ifdef        Si2158_ATV_AFC_RANGE_PROP
     case         Si2158_ATV_AFC_RANGE_PROP_CODE:
               api->prop->atv_afc_range.range_khz = (data >> Si2158_ATV_AFC_RANGE_PROP_RANGE_KHZ_LSB) & Si2158_ATV_AFC_RANGE_PROP_RANGE_KHZ_MASK;
     break;
    #endif /*     Si2158_ATV_AFC_RANGE_PROP */
    #ifdef        Si2158_ATV_AGC_SPEED_PROP
     case         Si2158_ATV_AGC_SPEED_PROP_CODE:
               api->prop->atv_agc_speed.if_agc_speed = (data >> Si2158_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_LSB) & Si2158_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_MASK;
     break;
    #endif /*     Si2158_ATV_AGC_SPEED_PROP */
    #ifdef        Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP
     case         Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP_CODE:
               api->prop->atv_agc_speed_low_rssi.if_agc_speed = (data >> Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_LSB) & Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_MASK;
               api->prop->atv_agc_speed_low_rssi.thld         = (data >> Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD_LSB        ) & Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD_MASK;
     break;
    #endif /*     Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP */
    #ifdef        Si2158_ATV_ARTIFICIAL_SNOW_PROP
     case         Si2158_ATV_ARTIFICIAL_SNOW_PROP_CODE:
               api->prop->atv_artificial_snow.gain   = (data >> Si2158_ATV_ARTIFICIAL_SNOW_PROP_GAIN_LSB  ) & Si2158_ATV_ARTIFICIAL_SNOW_PROP_GAIN_MASK;
               api->prop->atv_artificial_snow.offset = (data >> Si2158_ATV_ARTIFICIAL_SNOW_PROP_OFFSET_LSB) & Si2158_ATV_ARTIFICIAL_SNOW_PROP_OFFSET_MASK;
     break;
    #endif /*     Si2158_ATV_ARTIFICIAL_SNOW_PROP */
    #ifdef        Si2158_ATV_CONFIG_IF_PORT_PROP
     case         Si2158_ATV_CONFIG_IF_PORT_PROP_CODE:
               api->prop->atv_config_if_port.atv_out_type   = (data >> Si2158_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE_LSB  ) & Si2158_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE_MASK;
               api->prop->atv_config_if_port.atv_agc_source = (data >> Si2158_ATV_CONFIG_IF_PORT_PROP_ATV_AGC_SOURCE_LSB) & Si2158_ATV_CONFIG_IF_PORT_PROP_ATV_AGC_SOURCE_MASK;
     break;
    #endif /*     Si2158_ATV_CONFIG_IF_PORT_PROP */
    #ifdef        Si2158_ATV_EXT_AGC_PROP
     case         Si2158_ATV_EXT_AGC_PROP_CODE:
               api->prop->atv_ext_agc.min_10mv = (data >> Si2158_ATV_EXT_AGC_PROP_MIN_10MV_LSB) & Si2158_ATV_EXT_AGC_PROP_MIN_10MV_MASK;
               api->prop->atv_ext_agc.max_10mv = (data >> Si2158_ATV_EXT_AGC_PROP_MAX_10MV_LSB) & Si2158_ATV_EXT_AGC_PROP_MAX_10MV_MASK;
     break;
    #endif /*     Si2158_ATV_EXT_AGC_PROP */
    #ifdef        Si2158_ATV_IEN_PROP
     case         Si2158_ATV_IEN_PROP_CODE:
               api->prop->atv_ien.chlien = (data >> Si2158_ATV_IEN_PROP_CHLIEN_LSB) & Si2158_ATV_IEN_PROP_CHLIEN_MASK;
               api->prop->atv_ien.pclien = (data >> Si2158_ATV_IEN_PROP_PCLIEN_LSB) & Si2158_ATV_IEN_PROP_PCLIEN_MASK;
     break;
    #endif /*     Si2158_ATV_IEN_PROP */
    #ifdef        Si2158_ATV_INT_SENSE_PROP
     case         Si2158_ATV_INT_SENSE_PROP_CODE:
               api->prop->atv_int_sense.chlnegen = (data >> Si2158_ATV_INT_SENSE_PROP_CHLNEGEN_LSB) & Si2158_ATV_INT_SENSE_PROP_CHLNEGEN_MASK;
               api->prop->atv_int_sense.pclnegen = (data >> Si2158_ATV_INT_SENSE_PROP_PCLNEGEN_LSB) & Si2158_ATV_INT_SENSE_PROP_PCLNEGEN_MASK;
               api->prop->atv_int_sense.chlposen = (data >> Si2158_ATV_INT_SENSE_PROP_CHLPOSEN_LSB) & Si2158_ATV_INT_SENSE_PROP_CHLPOSEN_MASK;
               api->prop->atv_int_sense.pclposen = (data >> Si2158_ATV_INT_SENSE_PROP_PCLPOSEN_LSB) & Si2158_ATV_INT_SENSE_PROP_PCLPOSEN_MASK;
     break;
    #endif /*     Si2158_ATV_INT_SENSE_PROP */
    #ifdef        Si2158_ATV_LIF_FREQ_PROP
     case         Si2158_ATV_LIF_FREQ_PROP_CODE:
               api->prop->atv_lif_freq.offset = (data >> Si2158_ATV_LIF_FREQ_PROP_OFFSET_LSB) & Si2158_ATV_LIF_FREQ_PROP_OFFSET_MASK;
     break;
    #endif /*     Si2158_ATV_LIF_FREQ_PROP */
    #ifdef        Si2158_ATV_LIF_OUT_PROP
     case         Si2158_ATV_LIF_OUT_PROP_CODE:
               api->prop->atv_lif_out.offset = (data >> Si2158_ATV_LIF_OUT_PROP_OFFSET_LSB) & Si2158_ATV_LIF_OUT_PROP_OFFSET_MASK;
               api->prop->atv_lif_out.amp    = (data >> Si2158_ATV_LIF_OUT_PROP_AMP_LSB   ) & Si2158_ATV_LIF_OUT_PROP_AMP_MASK;
     break;
    #endif /*     Si2158_ATV_LIF_OUT_PROP */
    #ifdef        Si2158_ATV_PGA_TARGET_PROP
     case         Si2158_ATV_PGA_TARGET_PROP_CODE:
               api->prop->atv_pga_target.pga_target      = (data >> Si2158_ATV_PGA_TARGET_PROP_PGA_TARGET_LSB     ) & Si2158_ATV_PGA_TARGET_PROP_PGA_TARGET_MASK;
               api->prop->atv_pga_target.override_enable = (data >> Si2158_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_LSB) & Si2158_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_MASK;
     break;
    #endif /*     Si2158_ATV_PGA_TARGET_PROP */
    #ifdef        Si2158_ATV_RF_TOP_PROP
     case         Si2158_ATV_RF_TOP_PROP_CODE:
               api->prop->atv_rf_top.atv_rf_top = (data >> Si2158_ATV_RF_TOP_PROP_ATV_RF_TOP_LSB) & Si2158_ATV_RF_TOP_PROP_ATV_RF_TOP_MASK;
     break;
    #endif /*     Si2158_ATV_RF_TOP_PROP */
    #ifdef        Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP
     case         Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP_CODE:
               api->prop->atv_rsq_rssi_threshold.lo = (data >> Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_LSB) & Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_MASK;
               api->prop->atv_rsq_rssi_threshold.hi = (data >> Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP_HI_LSB) & Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP_HI_MASK;
     break;
    #endif /*     Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef        Si2158_ATV_VIDEO_MODE_PROP
     case         Si2158_ATV_VIDEO_MODE_PROP_CODE:
               api->prop->atv_video_mode.video_sys       = (data >> Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_LSB      ) & Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_MASK;
               api->prop->atv_video_mode.color           = (data >> Si2158_ATV_VIDEO_MODE_PROP_COLOR_LSB          ) & Si2158_ATV_VIDEO_MODE_PROP_COLOR_MASK;
               api->prop->atv_video_mode.invert_spectrum = (data >> Si2158_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_LSB) & Si2158_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_MASK;
     break;
    #endif /*     Si2158_ATV_VIDEO_MODE_PROP */
    #ifdef        Si2158_ATV_VSNR_CAP_PROP
     case         Si2158_ATV_VSNR_CAP_PROP_CODE:
               api->prop->atv_vsnr_cap.atv_vsnr_cap = (data >> Si2158_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_LSB) & Si2158_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_MASK;
     break;
    #endif /*     Si2158_ATV_VSNR_CAP_PROP */
    #ifdef        Si2158_CRYSTAL_TRIM_PROP
     case         Si2158_CRYSTAL_TRIM_PROP_CODE:
               api->prop->crystal_trim.xo_cap = (data >> Si2158_CRYSTAL_TRIM_PROP_XO_CAP_LSB) & Si2158_CRYSTAL_TRIM_PROP_XO_CAP_MASK;
     break;
    #endif /*     Si2158_CRYSTAL_TRIM_PROP */
    #ifdef        Si2158_DEBUG_SAMPLE_FREQ_PROP
     case         Si2158_DEBUG_SAMPLE_FREQ_PROP_CODE:
               api->prop->debug_sample_freq.fs_mhz = (data >> Si2158_DEBUG_SAMPLE_FREQ_PROP_FS_MHZ_LSB) & Si2158_DEBUG_SAMPLE_FREQ_PROP_FS_MHZ_MASK;
     break;
    #endif /*     Si2158_DEBUG_SAMPLE_FREQ_PROP */
    #ifdef        Si2158_DTV_AGC_FREEZE_INPUT_PROP
     case         Si2158_DTV_AGC_FREEZE_INPUT_PROP_CODE:
               api->prop->dtv_agc_freeze_input.level = (data >> Si2158_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_LSB) & Si2158_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_MASK;
               api->prop->dtv_agc_freeze_input.pin   = (data >> Si2158_DTV_AGC_FREEZE_INPUT_PROP_PIN_LSB  ) & Si2158_DTV_AGC_FREEZE_INPUT_PROP_PIN_MASK;
     break;
    #endif /*     Si2158_DTV_AGC_FREEZE_INPUT_PROP */
    #ifdef        Si2158_DTV_AGC_SPEED_PROP
     case         Si2158_DTV_AGC_SPEED_PROP_CODE:
               api->prop->dtv_agc_speed.if_agc_speed = (data >> Si2158_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_LSB) & Si2158_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_MASK;
               api->prop->dtv_agc_speed.agc_decim    = (data >> Si2158_DTV_AGC_SPEED_PROP_AGC_DECIM_LSB   ) & Si2158_DTV_AGC_SPEED_PROP_AGC_DECIM_MASK;
     break;
    #endif /*     Si2158_DTV_AGC_SPEED_PROP */
    #ifdef        Si2158_DTV_CONFIG_IF_PORT_PROP
     case         Si2158_DTV_CONFIG_IF_PORT_PROP_CODE:
               api->prop->dtv_config_if_port.dtv_out_type   = (data >> Si2158_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LSB  ) & Si2158_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_MASK;
               api->prop->dtv_config_if_port.dtv_agc_source = (data >> Si2158_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_LSB) & Si2158_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_MASK;
     break;
    #endif /*     Si2158_DTV_CONFIG_IF_PORT_PROP */
    #ifdef        Si2158_DTV_EXT_AGC_PROP
     case         Si2158_DTV_EXT_AGC_PROP_CODE:
               api->prop->dtv_ext_agc.min_10mv = (data >> Si2158_DTV_EXT_AGC_PROP_MIN_10MV_LSB) & Si2158_DTV_EXT_AGC_PROP_MIN_10MV_MASK;
               api->prop->dtv_ext_agc.max_10mv = (data >> Si2158_DTV_EXT_AGC_PROP_MAX_10MV_LSB) & Si2158_DTV_EXT_AGC_PROP_MAX_10MV_MASK;
     break;
    #endif /*     Si2158_DTV_EXT_AGC_PROP */
    #ifdef        Si2158_DTV_FILTER_SELECT_PROP
     case         Si2158_DTV_FILTER_SELECT_PROP_CODE:
               api->prop->dtv_filter_select.filter = (data >> Si2158_DTV_FILTER_SELECT_PROP_FILTER_LSB) & Si2158_DTV_FILTER_SELECT_PROP_FILTER_MASK;
     break;
    #endif /*     Si2158_DTV_FILTER_SELECT_PROP */
    #ifdef        Si2158_DTV_IEN_PROP
     case         Si2158_DTV_IEN_PROP_CODE:
               api->prop->dtv_ien.chlien = (data >> Si2158_DTV_IEN_PROP_CHLIEN_LSB) & Si2158_DTV_IEN_PROP_CHLIEN_MASK;
     break;
    #endif /*     Si2158_DTV_IEN_PROP */
    #ifdef        Si2158_DTV_INITIAL_AGC_SPEED_PROP
     case         Si2158_DTV_INITIAL_AGC_SPEED_PROP_CODE:
               api->prop->dtv_initial_agc_speed.if_agc_speed = (data >> Si2158_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_LSB) & Si2158_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_MASK;
               api->prop->dtv_initial_agc_speed.agc_decim    = (data >> Si2158_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_LSB   ) & Si2158_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_MASK;
     break;
    #endif /*     Si2158_DTV_INITIAL_AGC_SPEED_PROP */
    #ifdef        Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
     case         Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_CODE:
               api->prop->dtv_initial_agc_speed_period.period = (data >> Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_LSB) & Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_MASK;
     break;
    #endif /*     Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */
    #ifdef        Si2158_DTV_INTERNAL_ZIF_PROP
     case         Si2158_DTV_INTERNAL_ZIF_PROP_CODE:
               api->prop->dtv_internal_zif.atsc   = (data >> Si2158_DTV_INTERNAL_ZIF_PROP_ATSC_LSB  ) & Si2158_DTV_INTERNAL_ZIF_PROP_ATSC_MASK;
               api->prop->dtv_internal_zif.qam_us = (data >> Si2158_DTV_INTERNAL_ZIF_PROP_QAM_US_LSB) & Si2158_DTV_INTERNAL_ZIF_PROP_QAM_US_MASK;
               api->prop->dtv_internal_zif.dvbt   = (data >> Si2158_DTV_INTERNAL_ZIF_PROP_DVBT_LSB  ) & Si2158_DTV_INTERNAL_ZIF_PROP_DVBT_MASK;
               api->prop->dtv_internal_zif.dvbc   = (data >> Si2158_DTV_INTERNAL_ZIF_PROP_DVBC_LSB  ) & Si2158_DTV_INTERNAL_ZIF_PROP_DVBC_MASK;
               api->prop->dtv_internal_zif.isdbt  = (data >> Si2158_DTV_INTERNAL_ZIF_PROP_ISDBT_LSB ) & Si2158_DTV_INTERNAL_ZIF_PROP_ISDBT_MASK;
               api->prop->dtv_internal_zif.isdbc  = (data >> Si2158_DTV_INTERNAL_ZIF_PROP_ISDBC_LSB ) & Si2158_DTV_INTERNAL_ZIF_PROP_ISDBC_MASK;
               api->prop->dtv_internal_zif.dtmb   = (data >> Si2158_DTV_INTERNAL_ZIF_PROP_DTMB_LSB  ) & Si2158_DTV_INTERNAL_ZIF_PROP_DTMB_MASK;
     break;
    #endif /*     Si2158_DTV_INTERNAL_ZIF_PROP */
    #ifdef        Si2158_DTV_INT_SENSE_PROP
     case         Si2158_DTV_INT_SENSE_PROP_CODE:
               api->prop->dtv_int_sense.chlnegen = (data >> Si2158_DTV_INT_SENSE_PROP_CHLNEGEN_LSB) & Si2158_DTV_INT_SENSE_PROP_CHLNEGEN_MASK;
               api->prop->dtv_int_sense.chlposen = (data >> Si2158_DTV_INT_SENSE_PROP_CHLPOSEN_LSB) & Si2158_DTV_INT_SENSE_PROP_CHLPOSEN_MASK;
     break;
    #endif /*     Si2158_DTV_INT_SENSE_PROP */
    #ifdef        Si2158_DTV_LIF_FREQ_PROP
     case         Si2158_DTV_LIF_FREQ_PROP_CODE:
               api->prop->dtv_lif_freq.offset = (data >> Si2158_DTV_LIF_FREQ_PROP_OFFSET_LSB) & Si2158_DTV_LIF_FREQ_PROP_OFFSET_MASK;
     break;
    #endif /*     Si2158_DTV_LIF_FREQ_PROP */
    #ifdef        Si2158_DTV_LIF_OUT_PROP
     case         Si2158_DTV_LIF_OUT_PROP_CODE:
               api->prop->dtv_lif_out.offset = (data >> Si2158_DTV_LIF_OUT_PROP_OFFSET_LSB) & Si2158_DTV_LIF_OUT_PROP_OFFSET_MASK;
               api->prop->dtv_lif_out.amp    = (data >> Si2158_DTV_LIF_OUT_PROP_AMP_LSB   ) & Si2158_DTV_LIF_OUT_PROP_AMP_MASK;
     break;
    #endif /*     Si2158_DTV_LIF_OUT_PROP */
    #ifdef        Si2158_DTV_MODE_PROP
     case         Si2158_DTV_MODE_PROP_CODE:
               api->prop->dtv_mode.bw              = (data >> Si2158_DTV_MODE_PROP_BW_LSB             ) & Si2158_DTV_MODE_PROP_BW_MASK;
               api->prop->dtv_mode.modulation      = (data >> Si2158_DTV_MODE_PROP_MODULATION_LSB     ) & Si2158_DTV_MODE_PROP_MODULATION_MASK;
               api->prop->dtv_mode.invert_spectrum = (data >> Si2158_DTV_MODE_PROP_INVERT_SPECTRUM_LSB) & Si2158_DTV_MODE_PROP_INVERT_SPECTRUM_MASK;
     break;
    #endif /*     Si2158_DTV_MODE_PROP */
    #ifdef        Si2158_DTV_PGA_LIMITS_PROP
     case         Si2158_DTV_PGA_LIMITS_PROP_CODE:
               api->prop->dtv_pga_limits.min = (data >> Si2158_DTV_PGA_LIMITS_PROP_MIN_LSB) & Si2158_DTV_PGA_LIMITS_PROP_MIN_MASK;
               api->prop->dtv_pga_limits.max = (data >> Si2158_DTV_PGA_LIMITS_PROP_MAX_LSB) & Si2158_DTV_PGA_LIMITS_PROP_MAX_MASK;
     break;
    #endif /*     Si2158_DTV_PGA_LIMITS_PROP */
    #ifdef        Si2158_DTV_PGA_TARGET_PROP
     case         Si2158_DTV_PGA_TARGET_PROP_CODE:
               api->prop->dtv_pga_target.pga_target      = (data >> Si2158_DTV_PGA_TARGET_PROP_PGA_TARGET_LSB     ) & Si2158_DTV_PGA_TARGET_PROP_PGA_TARGET_MASK;
               api->prop->dtv_pga_target.override_enable = (data >> Si2158_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE_LSB) & Si2158_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE_MASK;
     break;
    #endif /*     Si2158_DTV_PGA_TARGET_PROP */
    #ifdef        Si2158_DTV_RF_TOP_PROP
     case         Si2158_DTV_RF_TOP_PROP_CODE:
               api->prop->dtv_rf_top.dtv_rf_top = (data >> Si2158_DTV_RF_TOP_PROP_DTV_RF_TOP_LSB) & Si2158_DTV_RF_TOP_PROP_DTV_RF_TOP_MASK;
     break;
    #endif /*     Si2158_DTV_RF_TOP_PROP */
    #ifdef        Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP
     case         Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP_CODE:
               api->prop->dtv_rsq_rssi_threshold.lo = (data >> Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_LSB) & Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_MASK;
               api->prop->dtv_rsq_rssi_threshold.hi = (data >> Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_LSB) & Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_MASK;
     break;
    #endif /*     Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef        Si2158_DTV_ZIF_DC_CANCELLER_BW_PROP
     case         Si2158_DTV_ZIF_DC_CANCELLER_BW_PROP_CODE:
               api->prop->dtv_zif_dc_canceller_bw.bandwidth = (data >> Si2158_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_LSB) & Si2158_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_MASK;
     break;
    #endif /*     Si2158_DTV_ZIF_DC_CANCELLER_BW_PROP */
    #ifdef        Si2158_MASTER_IEN_PROP
     case         Si2158_MASTER_IEN_PROP_CODE:
               api->prop->master_ien.tunien = (data >> Si2158_MASTER_IEN_PROP_TUNIEN_LSB) & Si2158_MASTER_IEN_PROP_TUNIEN_MASK;
               api->prop->master_ien.atvien = (data >> Si2158_MASTER_IEN_PROP_ATVIEN_LSB) & Si2158_MASTER_IEN_PROP_ATVIEN_MASK;
               api->prop->master_ien.dtvien = (data >> Si2158_MASTER_IEN_PROP_DTVIEN_LSB) & Si2158_MASTER_IEN_PROP_DTVIEN_MASK;
               api->prop->master_ien.errien = (data >> Si2158_MASTER_IEN_PROP_ERRIEN_LSB) & Si2158_MASTER_IEN_PROP_ERRIEN_MASK;
               api->prop->master_ien.ctsien = (data >> Si2158_MASTER_IEN_PROP_CTSIEN_LSB) & Si2158_MASTER_IEN_PROP_CTSIEN_MASK;
     break;
    #endif /*     Si2158_MASTER_IEN_PROP */
    #ifdef        Si2158_TUNER_BLOCKED_VCO_PROP
     case         Si2158_TUNER_BLOCKED_VCO_PROP_CODE:
               api->prop->tuner_blocked_vco.vco_code = (data >> Si2158_TUNER_BLOCKED_VCO_PROP_VCO_CODE_LSB) & Si2158_TUNER_BLOCKED_VCO_PROP_VCO_CODE_MASK;
     break;
    #endif /*     Si2158_TUNER_BLOCKED_VCO_PROP */
    #ifdef        Si2158_TUNER_IEN_PROP
     case         Si2158_TUNER_IEN_PROP_CODE:
               api->prop->tuner_ien.tcien    = (data >> Si2158_TUNER_IEN_PROP_TCIEN_LSB   ) & Si2158_TUNER_IEN_PROP_TCIEN_MASK;
               api->prop->tuner_ien.rssilien = (data >> Si2158_TUNER_IEN_PROP_RSSILIEN_LSB) & Si2158_TUNER_IEN_PROP_RSSILIEN_MASK;
               api->prop->tuner_ien.rssihien = (data >> Si2158_TUNER_IEN_PROP_RSSIHIEN_LSB) & Si2158_TUNER_IEN_PROP_RSSIHIEN_MASK;
     break;
    #endif /*     Si2158_TUNER_IEN_PROP */
    #ifdef        Si2158_TUNER_INT_SENSE_PROP
     case         Si2158_TUNER_INT_SENSE_PROP_CODE:
               api->prop->tuner_int_sense.tcnegen    = (data >> Si2158_TUNER_INT_SENSE_PROP_TCNEGEN_LSB   ) & Si2158_TUNER_INT_SENSE_PROP_TCNEGEN_MASK;
               api->prop->tuner_int_sense.rssilnegen = (data >> Si2158_TUNER_INT_SENSE_PROP_RSSILNEGEN_LSB) & Si2158_TUNER_INT_SENSE_PROP_RSSILNEGEN_MASK;
               api->prop->tuner_int_sense.rssihnegen = (data >> Si2158_TUNER_INT_SENSE_PROP_RSSIHNEGEN_LSB) & Si2158_TUNER_INT_SENSE_PROP_RSSIHNEGEN_MASK;
               api->prop->tuner_int_sense.tcposen    = (data >> Si2158_TUNER_INT_SENSE_PROP_TCPOSEN_LSB   ) & Si2158_TUNER_INT_SENSE_PROP_TCPOSEN_MASK;
               api->prop->tuner_int_sense.rssilposen = (data >> Si2158_TUNER_INT_SENSE_PROP_RSSILPOSEN_LSB) & Si2158_TUNER_INT_SENSE_PROP_RSSILPOSEN_MASK;
               api->prop->tuner_int_sense.rssihposen = (data >> Si2158_TUNER_INT_SENSE_PROP_RSSIHPOSEN_LSB) & Si2158_TUNER_INT_SENSE_PROP_RSSIHPOSEN_MASK;
     break;
    #endif /*     Si2158_TUNER_INT_SENSE_PROP */
    #ifdef        Si2158_TUNER_LO_INJECTION_PROP
     case         Si2158_TUNER_LO_INJECTION_PROP_CODE:
               api->prop->tuner_lo_injection.band_1 = (data >> Si2158_TUNER_LO_INJECTION_PROP_BAND_1_LSB) & Si2158_TUNER_LO_INJECTION_PROP_BAND_1_MASK;
               api->prop->tuner_lo_injection.band_2 = (data >> Si2158_TUNER_LO_INJECTION_PROP_BAND_2_LSB) & Si2158_TUNER_LO_INJECTION_PROP_BAND_2_MASK;
               api->prop->tuner_lo_injection.band_3 = (data >> Si2158_TUNER_LO_INJECTION_PROP_BAND_3_LSB) & Si2158_TUNER_LO_INJECTION_PROP_BAND_3_MASK;
     break;
    #endif /*     Si2158_TUNER_LO_INJECTION_PROP */
    #ifdef        Si2158_TUNER_RETURN_LOSS_PROP
     case         Si2158_TUNER_RETURN_LOSS_PROP_CODE:
               api->prop->tuner_return_loss.config = (data >> Si2158_TUNER_RETURN_LOSS_PROP_CONFIG_LSB) & Si2158_TUNER_RETURN_LOSS_PROP_CONFIG_MASK;
               api->prop->tuner_return_loss.mode   = (data >> Si2158_TUNER_RETURN_LOSS_PROP_MODE_LSB  ) & Si2158_TUNER_RETURN_LOSS_PROP_MODE_MASK;
     break;
    #endif /*     Si2158_TUNER_RETURN_LOSS_PROP */
    #ifdef        Si2158_XOUT_PROP
     case         Si2158_XOUT_PROP_CODE:
               api->prop->xout.amp = (data >> Si2158_XOUT_PROP_AMP_LSB) & Si2158_XOUT_PROP_AMP_MASK;
     break;
    #endif /*     Si2158_XOUT_PROP */
   default : break;
    }
    return res;
  }
  /* _get_property2_insertion_point */

#ifdef    Si2158_GET_PROPERTY_STRING
/* _get_property_string_insertion_start */

  /* --------------------------------------------*/
  /* GET_PROPERTY_STRING FUNCTION                */
  /* --------------------------------------------*/
unsigned char Si2158_L1_GetPropertyString(L1_Si2158_Context *api, unsigned int prop_code, char *separator, char *msg) {
    int res;
    res = Si2158_L1_GetProperty2(api,prop_code);
    if (res!=NO_Si2158_ERROR) { sprintf(msg, "%s",Si2158_L1_API_ERROR_TEXT(res)); return res; }
    Si2158_L1_FillPropertyStringText(api, prop_code, separator, msg);
    return NO_Si2158_ERROR;
}
  /* --------------------------------------------*/
  /* FillPropertyStringText FUNCTION             */
  /* --------------------------------------------*/
void          Si2158_L1_FillPropertyStringText(L1_Si2158_Context *api, unsigned int prop_code, char *separator, char *msg) {
    switch (prop_code) {
    #ifdef        Si2158_ATV_AFC_RANGE_PROP
     case         Si2158_ATV_AFC_RANGE_PROP_CODE:
      sprintf(msg,"ATV_AFC_RANGE");
       strcat(msg,separator); strcat(msg,"-RANGE_KHZ "); sprintf(msg,"%s%d", msg, api->prop->atv_afc_range.range_khz);
     break;
    #endif /*     Si2158_ATV_AFC_RANGE_PROP */
    #ifdef        Si2158_ATV_AGC_SPEED_PROP
     case         Si2158_ATV_AGC_SPEED_PROP_CODE:
      sprintf(msg,"ATV_AGC_SPEED");
       strcat(msg,separator); strcat(msg,"-IF_AGC_SPEED ");
           if  (api->prop->atv_agc_speed.if_agc_speed ==     0) strcat(msg,"AUTO   ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==    89) strcat(msg,"89     ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   105) strcat(msg,"105    ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   121) strcat(msg,"121    ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   137) strcat(msg,"137    ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   158) strcat(msg,"158    ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   172) strcat(msg,"172    ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   178) strcat(msg,"178    ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   185) strcat(msg,"185    ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   196) strcat(msg,"196    ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   206) strcat(msg,"206    ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   216) strcat(msg,"216    ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   219) strcat(msg,"219    ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   222) strcat(msg,"222    ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   248) strcat(msg,"248    ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   250) strcat(msg,"250    ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==   251) strcat(msg,"251    ");
      else if  (api->prop->atv_agc_speed.if_agc_speed ==     1) strcat(msg,"CUSTOM ");
      else                                                     sprintf(msg,"%s%d", msg, api->prop->atv_agc_speed.if_agc_speed);
     break;
    #endif /*     Si2158_ATV_AGC_SPEED_PROP */
    #ifdef        Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP
     case         Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP_CODE:
      sprintf(msg,"ATV_AGC_SPEED_LOW_RSSI");
       strcat(msg,separator); strcat(msg,"-IF_AGC_SPEED ");
           if  (api->prop->atv_agc_speed_low_rssi.if_agc_speed ==    89) strcat(msg,"89     ");
      else if  (api->prop->atv_agc_speed_low_rssi.if_agc_speed ==   105) strcat(msg,"105    ");
      else if  (api->prop->atv_agc_speed_low_rssi.if_agc_speed ==   121) strcat(msg,"121    ");
      else if  (api->prop->atv_agc_speed_low_rssi.if_agc_speed ==   137) strcat(msg,"137    ");
      else if  (api->prop->atv_agc_speed_low_rssi.if_agc_speed ==   158) strcat(msg,"158    ");
      else if  (api->prop->atv_agc_speed_low_rssi.if_agc_speed ==   172) strcat(msg,"172    ");
      else if  (api->prop->atv_agc_speed_low_rssi.if_agc_speed ==   178) strcat(msg,"178    ");
      else if  (api->prop->atv_agc_speed_low_rssi.if_agc_speed ==   185) strcat(msg,"185    ");
      else if  (api->prop->atv_agc_speed_low_rssi.if_agc_speed ==   196) strcat(msg,"196    ");
      else if  (api->prop->atv_agc_speed_low_rssi.if_agc_speed ==   206) strcat(msg,"206    ");
      else if  (api->prop->atv_agc_speed_low_rssi.if_agc_speed ==   216) strcat(msg,"216    ");
      else if  (api->prop->atv_agc_speed_low_rssi.if_agc_speed ==   219) strcat(msg,"219    ");
      else if  (api->prop->atv_agc_speed_low_rssi.if_agc_speed ==   222) strcat(msg,"222    ");
      else if  (api->prop->atv_agc_speed_low_rssi.if_agc_speed ==   248) strcat(msg,"248    ");
      else if  (api->prop->atv_agc_speed_low_rssi.if_agc_speed ==   250) strcat(msg,"250    ");
      else if  (api->prop->atv_agc_speed_low_rssi.if_agc_speed ==   251) strcat(msg,"251    ");
      else if  (api->prop->atv_agc_speed_low_rssi.if_agc_speed ==     1) strcat(msg,"CUSTOM ");
      else                                                              sprintf(msg,"%s%d", msg, api->prop->atv_agc_speed_low_rssi.if_agc_speed);
       strcat(msg,separator); strcat(msg,"-THLD "); sprintf(msg,"%s%d", msg, api->prop->atv_agc_speed_low_rssi.thld);
     break;
    #endif /*     Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP */
    #ifdef        Si2158_ATV_ARTIFICIAL_SNOW_PROP
     case         Si2158_ATV_ARTIFICIAL_SNOW_PROP_CODE:
      sprintf(msg,"ATV_ARTIFICIAL_SNOW");
       strcat(msg,separator); strcat(msg,"-GAIN ");
           if  (api->prop->atv_artificial_snow.gain   ==     0) strcat(msg,"AUTO ");
      else if  (api->prop->atv_artificial_snow.gain   ==     1) strcat(msg,"0DB  ");
      else if  (api->prop->atv_artificial_snow.gain   ==     2) strcat(msg,"6DB  ");
      else if  (api->prop->atv_artificial_snow.gain   ==     3) strcat(msg,"12DB ");
      else if  (api->prop->atv_artificial_snow.gain   ==     4) strcat(msg,"18DB ");
      else if  (api->prop->atv_artificial_snow.gain   ==     5) strcat(msg,"24DB ");
      else if  (api->prop->atv_artificial_snow.gain   ==     6) strcat(msg,"30DB ");
      else if  (api->prop->atv_artificial_snow.gain   ==     7) strcat(msg,"36DB ");
      else if  (api->prop->atv_artificial_snow.gain   ==     8) strcat(msg,"42DB ");
      else if  (api->prop->atv_artificial_snow.gain   ==     9) strcat(msg,"OFF  ");
      else                                                     sprintf(msg,"%s%d", msg, api->prop->atv_artificial_snow.gain);
       strcat(msg,separator); strcat(msg,"-OFFSET "); sprintf(msg,"%s%d", msg, api->prop->atv_artificial_snow.offset);
     break;
    #endif /*     Si2158_ATV_ARTIFICIAL_SNOW_PROP */
    #ifdef        Si2158_ATV_CONFIG_IF_PORT_PROP
     case         Si2158_ATV_CONFIG_IF_PORT_PROP_CODE:
      sprintf(msg,"ATV_CONFIG_IF_PORT");
       strcat(msg,separator); strcat(msg,"-ATV_OUT_TYPE ");
           if  (api->prop->atv_config_if_port.atv_out_type   ==     8) strcat(msg,"LIF_DIFF_IF1 ");
      else if  (api->prop->atv_config_if_port.atv_out_type   ==    10) strcat(msg,"LIF_DIFF_IF2 ");
      else if  (api->prop->atv_config_if_port.atv_out_type   ==    12) strcat(msg,"LIF_SE_IF1A  ");
      else if  (api->prop->atv_config_if_port.atv_out_type   ==    14) strcat(msg,"LIF_SE_IF2A  ");
      else                                                            sprintf(msg,"%s%d", msg, api->prop->atv_config_if_port.atv_out_type);
       strcat(msg,separator); strcat(msg,"-ATV_AGC_SOURCE ");
           if  (api->prop->atv_config_if_port.atv_agc_source ==     0) strcat(msg,"INTERNAL ");
      else if  (api->prop->atv_config_if_port.atv_agc_source ==     1) strcat(msg,"AGC1_3DB ");
      else if  (api->prop->atv_config_if_port.atv_agc_source ==     2) strcat(msg,"AGC2_3DB ");
      else                                                            sprintf(msg,"%s%d", msg, api->prop->atv_config_if_port.atv_agc_source);
     break;
    #endif /*     Si2158_ATV_CONFIG_IF_PORT_PROP */
    #ifdef        Si2158_ATV_EXT_AGC_PROP
     case         Si2158_ATV_EXT_AGC_PROP_CODE:
      sprintf(msg,"ATV_EXT_AGC");
       strcat(msg,separator); strcat(msg,"-MIN_10MV "); sprintf(msg,"%s%d", msg, api->prop->atv_ext_agc.min_10mv);
       strcat(msg,separator); strcat(msg,"-MAX_10MV "); sprintf(msg,"%s%d", msg, api->prop->atv_ext_agc.max_10mv);
     break;
    #endif /*     Si2158_ATV_EXT_AGC_PROP */
    #ifdef        Si2158_ATV_IEN_PROP
     case         Si2158_ATV_IEN_PROP_CODE:
          sprintf(msg,"ATV_IEN");
       strcat(msg,separator); strcat(msg,"-CHLIEN ");
           if  (api->prop->atv_ien.chlien ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->atv_ien.chlien ==     1) strcat(msg,"ENABLE  ");
      else                                         sprintf(msg,"%s%d", msg, api->prop->atv_ien.chlien);
       strcat(msg,separator); strcat(msg,"-PCLIEN ");
           if  (api->prop->atv_ien.pclien ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->atv_ien.pclien ==     1) strcat(msg,"ENABLE  ");
      else                                         sprintf(msg,"%s%d", msg, api->prop->atv_ien.pclien);
     break;
    #endif /*     Si2158_ATV_IEN_PROP */
    #ifdef        Si2158_ATV_INT_SENSE_PROP
     case         Si2158_ATV_INT_SENSE_PROP_CODE:
      sprintf(msg,"ATV_INT_SENSE");
       strcat(msg,separator); strcat(msg,"-CHLNEGEN ");
           if  (api->prop->atv_int_sense.chlnegen ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->atv_int_sense.chlnegen ==     1) strcat(msg,"ENABLE  ");
      else                                                 sprintf(msg,"%s%d", msg, api->prop->atv_int_sense.chlnegen);
       strcat(msg,separator); strcat(msg,"-PCLNEGEN ");
           if  (api->prop->atv_int_sense.pclnegen ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->atv_int_sense.pclnegen ==     1) strcat(msg,"ENABLE  ");
      else                                                 sprintf(msg,"%s%d", msg, api->prop->atv_int_sense.pclnegen);
       strcat(msg,separator); strcat(msg,"-CHLPOSEN ");
           if  (api->prop->atv_int_sense.chlposen ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->atv_int_sense.chlposen ==     1) strcat(msg,"ENABLE  ");
      else                                                 sprintf(msg,"%s%d", msg, api->prop->atv_int_sense.chlposen);
       strcat(msg,separator); strcat(msg,"-PCLPOSEN ");
           if  (api->prop->atv_int_sense.pclposen ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->atv_int_sense.pclposen ==     1) strcat(msg,"ENABLE  ");
      else                                                 sprintf(msg,"%s%d", msg, api->prop->atv_int_sense.pclposen);
     break;
    #endif /*     Si2158_ATV_INT_SENSE_PROP */
    #ifdef        Si2158_ATV_LIF_FREQ_PROP
     case         Si2158_ATV_LIF_FREQ_PROP_CODE:
      sprintf(msg,"ATV_LIF_FREQ");
       strcat(msg,separator); strcat(msg,"-OFFSET "); sprintf(msg,"%s%d", msg, api->prop->atv_lif_freq.offset);
     break;
    #endif /*     Si2158_ATV_LIF_FREQ_PROP */
    #ifdef        Si2158_ATV_LIF_OUT_PROP
     case         Si2158_ATV_LIF_OUT_PROP_CODE:
      sprintf(msg,"ATV_LIF_OUT");
       strcat(msg,separator); strcat(msg,"-OFFSET "); sprintf(msg,"%s%d", msg, api->prop->atv_lif_out.offset);
       strcat(msg,separator); strcat(msg,"-AMP "); sprintf(msg,"%s%d", msg, api->prop->atv_lif_out.amp);
     break;
    #endif /*     Si2158_ATV_LIF_OUT_PROP */
    #ifdef        Si2158_ATV_PGA_TARGET_PROP
     case         Si2158_ATV_PGA_TARGET_PROP_CODE:
      sprintf(msg,"ATV_PGA_TARGET");
       strcat(msg,separator); strcat(msg,"-PGA_TARGET "); sprintf(msg,"%s%d", msg, api->prop->atv_pga_target.pga_target);
       strcat(msg,separator); strcat(msg,"-OVERRIDE_ENABLE ");
           if  (api->prop->atv_pga_target.override_enable ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->atv_pga_target.override_enable ==     1) strcat(msg,"ENABLE  ");
      else                                                         sprintf(msg,"%s%d", msg, api->prop->atv_pga_target.override_enable);
     break;
    #endif /*     Si2158_ATV_PGA_TARGET_PROP */
    #ifdef        Si2158_ATV_RF_TOP_PROP
     case         Si2158_ATV_RF_TOP_PROP_CODE:
      sprintf(msg,"ATV_RF_TOP");
       strcat(msg,separator); strcat(msg,"-ATV_RF_TOP ");
           if  (api->prop->atv_rf_top.atv_rf_top ==     0) strcat(msg,"AUTO  ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==     1) strcat(msg,"P5DB  ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==     2) strcat(msg,"P4DB  ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==     3) strcat(msg,"P3DB  ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==     4) strcat(msg,"P2DB  ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==     5) strcat(msg,"P1DB  ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==     6) strcat(msg,"0DB   ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==     7) strcat(msg,"M1DB  ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==     8) strcat(msg,"M2DB  ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==     9) strcat(msg,"M3DB  ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==    10) strcat(msg,"M4DB  ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==    11) strcat(msg,"M5DB  ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==    12) strcat(msg,"M6DB  ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==    13) strcat(msg,"M7DB  ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==    14) strcat(msg,"M8DB  ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==    15) strcat(msg,"M9DB  ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==    16) strcat(msg,"M10DB ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==    17) strcat(msg,"M11DB ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==    18) strcat(msg,"M12DB ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==    19) strcat(msg,"M13DB ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==    20) strcat(msg,"M14DB ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==    21) strcat(msg,"M15DB ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==    22) strcat(msg,"M16DB ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==    23) strcat(msg,"M17DB ");
      else if  (api->prop->atv_rf_top.atv_rf_top ==    24) strcat(msg,"M18DB ");
      else                                                sprintf(msg,"%s%d", msg, api->prop->atv_rf_top.atv_rf_top);
     break;
    #endif /*     Si2158_ATV_RF_TOP_PROP */
    #ifdef        Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP
     case         Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP_CODE:
      sprintf(msg,"ATV_RSQ_RSSI_THRESHOLD");
       strcat(msg,separator); strcat(msg,"-LO "); sprintf(msg,"%s%d", msg, api->prop->atv_rsq_rssi_threshold.lo);
       strcat(msg,separator); strcat(msg,"-HI "); sprintf(msg,"%s%d", msg, api->prop->atv_rsq_rssi_threshold.hi);
     break;
    #endif /*     Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef        Si2158_ATV_VIDEO_MODE_PROP
     case         Si2158_ATV_VIDEO_MODE_PROP_CODE:
      sprintf(msg,"ATV_VIDEO_MODE");
       strcat(msg,separator); strcat(msg,"-VIDEO_SYS ");
           if  (api->prop->atv_video_mode.video_sys       ==     0) strcat(msg,"B  ");
      else if  (api->prop->atv_video_mode.video_sys       ==     1) strcat(msg,"GH ");
      else if  (api->prop->atv_video_mode.video_sys       ==     2) strcat(msg,"M  ");
      else if  (api->prop->atv_video_mode.video_sys       ==     3) strcat(msg,"N  ");
      else if  (api->prop->atv_video_mode.video_sys       ==     4) strcat(msg,"I  ");
      else if  (api->prop->atv_video_mode.video_sys       ==     5) strcat(msg,"DK ");
      else if  (api->prop->atv_video_mode.video_sys       ==     6) strcat(msg,"L  ");
      else if  (api->prop->atv_video_mode.video_sys       ==     7) strcat(msg,"LP ");
      else                                                         sprintf(msg,"%s%d", msg, api->prop->atv_video_mode.video_sys);
       strcat(msg,separator); strcat(msg,"-COLOR ");
           if  (api->prop->atv_video_mode.color           ==     0) strcat(msg,"PAL_NTSC ");
      else if  (api->prop->atv_video_mode.color           ==     1) strcat(msg,"SECAM    ");
      else                                                         sprintf(msg,"%s%d", msg, api->prop->atv_video_mode.color);
       strcat(msg,separator); strcat(msg,"-INVERT_SPECTRUM ");
           if  (api->prop->atv_video_mode.invert_spectrum ==     0) strcat(msg,"NORMAL   ");
      else if  (api->prop->atv_video_mode.invert_spectrum ==     1) strcat(msg,"INVERTED ");
      else                                                         sprintf(msg,"%s%d", msg, api->prop->atv_video_mode.invert_spectrum);
     break;
    #endif /*     Si2158_ATV_VIDEO_MODE_PROP */
    #ifdef        Si2158_ATV_VSNR_CAP_PROP
     case         Si2158_ATV_VSNR_CAP_PROP_CODE:
      sprintf(msg,"ATV_VSNR_CAP");
       strcat(msg,separator); strcat(msg,"-ATV_VSNR_CAP "); sprintf(msg,"%s%d", msg, api->prop->atv_vsnr_cap.atv_vsnr_cap);
     break;
    #endif /*     Si2158_ATV_VSNR_CAP_PROP */
    #ifdef        Si2158_CRYSTAL_TRIM_PROP
     case         Si2158_CRYSTAL_TRIM_PROP_CODE:
      sprintf(msg,"CRYSTAL_TRIM");
       strcat(msg,separator); strcat(msg,"-XO_CAP ");
           if  (api->prop->crystal_trim.xo_cap ==     0) strcat(msg,"0  ");
      else if  (api->prop->crystal_trim.xo_cap ==     1) strcat(msg,"1  ");
      else if  (api->prop->crystal_trim.xo_cap ==     2) strcat(msg,"2  ");
      else if  (api->prop->crystal_trim.xo_cap ==     3) strcat(msg,"3  ");
      else if  (api->prop->crystal_trim.xo_cap ==     4) strcat(msg,"4  ");
      else if  (api->prop->crystal_trim.xo_cap ==     5) strcat(msg,"5  ");
      else if  (api->prop->crystal_trim.xo_cap ==     6) strcat(msg,"6  ");
      else if  (api->prop->crystal_trim.xo_cap ==     7) strcat(msg,"7  ");
      else if  (api->prop->crystal_trim.xo_cap ==     8) strcat(msg,"8  ");
      else if  (api->prop->crystal_trim.xo_cap ==     9) strcat(msg,"9  ");
      else if  (api->prop->crystal_trim.xo_cap ==    10) strcat(msg,"10 ");
      else if  (api->prop->crystal_trim.xo_cap ==    11) strcat(msg,"11 ");
      else if  (api->prop->crystal_trim.xo_cap ==    12) strcat(msg,"12 ");
      else if  (api->prop->crystal_trim.xo_cap ==    13) strcat(msg,"13 ");
      else if  (api->prop->crystal_trim.xo_cap ==    14) strcat(msg,"14 ");
      else if  (api->prop->crystal_trim.xo_cap ==    15) strcat(msg,"15 ");
      else                                              sprintf(msg,"%s%d", msg, api->prop->crystal_trim.xo_cap);
     break;
    #endif /*     Si2158_CRYSTAL_TRIM_PROP */
    #ifdef        Si2158_DEBUG_SAMPLE_FREQ_PROP
     case         Si2158_DEBUG_SAMPLE_FREQ_PROP_CODE:
      sprintf(msg,"DEBUG_SAMPLE_FREQ");
       strcat(msg,separator); strcat(msg,"-FS_MHZ "); sprintf(msg,"%s%d", msg, api->prop->debug_sample_freq.fs_mhz);
     break;
    #endif /*     Si2158_DEBUG_SAMPLE_FREQ_PROP */
    #ifdef        Si2158_DTV_AGC_FREEZE_INPUT_PROP
     case         Si2158_DTV_AGC_FREEZE_INPUT_PROP_CODE:
      sprintf(msg,"DTV_AGC_FREEZE_INPUT");
       strcat(msg,separator); strcat(msg,"-LEVEL ");
           if  (api->prop->dtv_agc_freeze_input.level ==     0) strcat(msg,"LOW  ");
      else if  (api->prop->dtv_agc_freeze_input.level ==     1) strcat(msg,"HIGH ");
      else                                                     sprintf(msg,"%s%d", msg, api->prop->dtv_agc_freeze_input.level);
       strcat(msg,separator); strcat(msg,"-PIN ");
           if  (api->prop->dtv_agc_freeze_input.pin   ==     0) strcat(msg,"NONE     ");
      else if  (api->prop->dtv_agc_freeze_input.pin   ==     1) strcat(msg,"GPIO1    ");
      else if  (api->prop->dtv_agc_freeze_input.pin   ==     2) strcat(msg,"GPIO2    ");
      else if  (api->prop->dtv_agc_freeze_input.pin   ==     3) strcat(msg,"RESERVED ");
      else if  (api->prop->dtv_agc_freeze_input.pin   ==     4) strcat(msg,"AGC1     ");
      else if  (api->prop->dtv_agc_freeze_input.pin   ==     5) strcat(msg,"AGC2     ");
      else if  (api->prop->dtv_agc_freeze_input.pin   ==     6) strcat(msg,"LIF1A    ");
      else if  (api->prop->dtv_agc_freeze_input.pin   ==     7) strcat(msg,"LIF1B    ");
      else                                                     sprintf(msg,"%s%d", msg, api->prop->dtv_agc_freeze_input.pin);
     break;
    #endif /*     Si2158_DTV_AGC_FREEZE_INPUT_PROP */
    #ifdef        Si2158_DTV_AGC_SPEED_PROP
     case         Si2158_DTV_AGC_SPEED_PROP_CODE:
      sprintf(msg,"DTV_AGC_SPEED");
       strcat(msg,separator); strcat(msg,"-IF_AGC_SPEED ");
           if  (api->prop->dtv_agc_speed.if_agc_speed ==     0) strcat(msg,"AUTO ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==    39) strcat(msg,"39   ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==    54) strcat(msg,"54   ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==    63) strcat(msg,"63   ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==    89) strcat(msg,"89   ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==   105) strcat(msg,"105  ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==   121) strcat(msg,"121  ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==   137) strcat(msg,"137  ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==   158) strcat(msg,"158  ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==   172) strcat(msg,"172  ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==   185) strcat(msg,"185  ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==   196) strcat(msg,"196  ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==   206) strcat(msg,"206  ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==   216) strcat(msg,"216  ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==   219) strcat(msg,"219  ");
      else if  (api->prop->dtv_agc_speed.if_agc_speed ==   222) strcat(msg,"222  ");
      else                                                     sprintf(msg,"%s%d", msg, api->prop->dtv_agc_speed.if_agc_speed);
       strcat(msg,separator); strcat(msg,"-AGC_DECIM ");
           if  (api->prop->dtv_agc_speed.agc_decim    ==     0) strcat(msg,"OFF ");
      else if  (api->prop->dtv_agc_speed.agc_decim    ==     1) strcat(msg,"2   ");
      else if  (api->prop->dtv_agc_speed.agc_decim    ==     2) strcat(msg,"4   ");
      else if  (api->prop->dtv_agc_speed.agc_decim    ==     3) strcat(msg,"8   ");
      else                                                     sprintf(msg,"%s%d", msg, api->prop->dtv_agc_speed.agc_decim);
     break;
    #endif /*     Si2158_DTV_AGC_SPEED_PROP */
    #ifdef        Si2158_DTV_CONFIG_IF_PORT_PROP
     case         Si2158_DTV_CONFIG_IF_PORT_PROP_CODE:
      sprintf(msg,"DTV_CONFIG_IF_PORT");
       strcat(msg,separator); strcat(msg,"-DTV_OUT_TYPE ");
           if  (api->prop->dtv_config_if_port.dtv_out_type   ==     0) strcat(msg,"LIF_IF1     ");
      else if  (api->prop->dtv_config_if_port.dtv_out_type   ==     1) strcat(msg,"LIF_IF2     ");
      else if  (api->prop->dtv_config_if_port.dtv_out_type   ==     4) strcat(msg,"LIF_SE_IF1A ");
      else if  (api->prop->dtv_config_if_port.dtv_out_type   ==     5) strcat(msg,"LIF_SE_IF2A ");
      else                                                            sprintf(msg,"%s%d", msg, api->prop->dtv_config_if_port.dtv_out_type);
       strcat(msg,separator); strcat(msg,"-DTV_AGC_SOURCE ");
           if  (api->prop->dtv_config_if_port.dtv_agc_source ==     0) strcat(msg,"INTERNAL  ");
      else if  (api->prop->dtv_config_if_port.dtv_agc_source ==     1) strcat(msg,"AGC1_3DB  ");
      else if  (api->prop->dtv_config_if_port.dtv_agc_source ==     2) strcat(msg,"AGC2_3DB  ");
      else if  (api->prop->dtv_config_if_port.dtv_agc_source ==     3) strcat(msg,"AGC1_FULL ");
      else if  (api->prop->dtv_config_if_port.dtv_agc_source ==     4) strcat(msg,"AGC2_FULL ");
      else                                                            sprintf(msg,"%s%d", msg, api->prop->dtv_config_if_port.dtv_agc_source);
     break;
    #endif /*     Si2158_DTV_CONFIG_IF_PORT_PROP */
    #ifdef        Si2158_DTV_EXT_AGC_PROP
     case         Si2158_DTV_EXT_AGC_PROP_CODE:
      sprintf(msg,"DTV_EXT_AGC");
       strcat(msg,separator); strcat(msg,"-MIN_10MV "); sprintf(msg,"%s%d", msg, api->prop->dtv_ext_agc.min_10mv);
       strcat(msg,separator); strcat(msg,"-MAX_10MV "); sprintf(msg,"%s%d", msg, api->prop->dtv_ext_agc.max_10mv);
     break;
    #endif /*     Si2158_DTV_EXT_AGC_PROP */
    #ifdef        Si2158_DTV_FILTER_SELECT_PROP
     case         Si2158_DTV_FILTER_SELECT_PROP_CODE:
      sprintf(msg,"DTV_FILTER_SELECT");
       strcat(msg,separator); strcat(msg,"-FILTER ");
           if  (api->prop->dtv_filter_select.filter ==     0) strcat(msg,"LEGACY  ");
      else if  (api->prop->dtv_filter_select.filter ==     1) strcat(msg,"CUSTOM1 ");
      else if  (api->prop->dtv_filter_select.filter ==     2) strcat(msg,"CUSTOM2 ");
      else                                                   sprintf(msg,"%s%d", msg, api->prop->dtv_filter_select.filter);
     break;
    #endif /*     Si2158_DTV_FILTER_SELECT_PROP */
    #ifdef        Si2158_DTV_IEN_PROP
     case         Si2158_DTV_IEN_PROP_CODE:
      sprintf(msg,"DTV_IEN");
       strcat(msg,separator); strcat(msg,"-CHLIEN ");
           if  (api->prop->dtv_ien.chlien ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->dtv_ien.chlien ==     1) strcat(msg,"ENABLE  ");
      else                                         sprintf(msg,"%s%d", msg, api->prop->dtv_ien.chlien);
     break;
    #endif /*     Si2158_DTV_IEN_PROP */
    #ifdef        Si2158_DTV_INITIAL_AGC_SPEED_PROP
     case         Si2158_DTV_INITIAL_AGC_SPEED_PROP_CODE:
      sprintf(msg,"DTV_INITIAL_AGC_SPEED");
       strcat(msg,separator); strcat(msg,"-IF_AGC_SPEED ");
           if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==     0) strcat(msg,"AUTO ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==    39) strcat(msg,"39   ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==    54) strcat(msg,"54   ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==    63) strcat(msg,"63   ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==    89) strcat(msg,"89   ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==   105) strcat(msg,"105  ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==   121) strcat(msg,"121  ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==   137) strcat(msg,"137  ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==   158) strcat(msg,"158  ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==   172) strcat(msg,"172  ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==   185) strcat(msg,"185  ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==   196) strcat(msg,"196  ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==   206) strcat(msg,"206  ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==   216) strcat(msg,"216  ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==   219) strcat(msg,"219  ");
      else if  (api->prop->dtv_initial_agc_speed.if_agc_speed ==   222) strcat(msg,"222  ");
      else                                                             sprintf(msg,"%s%d", msg, api->prop->dtv_initial_agc_speed.if_agc_speed);
       strcat(msg,separator); strcat(msg,"-AGC_DECIM ");
           if  (api->prop->dtv_initial_agc_speed.agc_decim    ==     0) strcat(msg,"OFF ");
      else if  (api->prop->dtv_initial_agc_speed.agc_decim    ==     1) strcat(msg,"2   ");
      else if  (api->prop->dtv_initial_agc_speed.agc_decim    ==     2) strcat(msg,"4   ");
      else if  (api->prop->dtv_initial_agc_speed.agc_decim    ==     3) strcat(msg,"8   ");
      else                                                             sprintf(msg,"%s%d", msg, api->prop->dtv_initial_agc_speed.agc_decim);
     break;
    #endif /*     Si2158_DTV_INITIAL_AGC_SPEED_PROP */
    #ifdef        Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
     case         Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_CODE:
      sprintf(msg,"DTV_INITIAL_AGC_SPEED_PERIOD");
       strcat(msg,separator); strcat(msg,"-PERIOD "); sprintf(msg,"%s%d", msg, api->prop->dtv_initial_agc_speed_period.period);
     break;
    #endif /*     Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */
    #ifdef        Si2158_DTV_INTERNAL_ZIF_PROP
     case         Si2158_DTV_INTERNAL_ZIF_PROP_CODE:
      sprintf(msg,"DTV_INTERNAL_ZIF");
       strcat(msg,separator); strcat(msg,"-ATSC ");
           if  (api->prop->dtv_internal_zif.atsc   ==     0) strcat(msg,"LIF ");
      else if  (api->prop->dtv_internal_zif.atsc   ==     1) strcat(msg,"ZIF ");
      else                                                  sprintf(msg,"%s%d", msg, api->prop->dtv_internal_zif.atsc);
       strcat(msg,separator); strcat(msg,"-QAM_US ");
           if  (api->prop->dtv_internal_zif.qam_us ==     0) strcat(msg,"LIF ");
      else if  (api->prop->dtv_internal_zif.qam_us ==     1) strcat(msg,"ZIF ");
      else                                                  sprintf(msg,"%s%d", msg, api->prop->dtv_internal_zif.qam_us);
       strcat(msg,separator); strcat(msg,"-DVBT ");
           if  (api->prop->dtv_internal_zif.dvbt   ==     0) strcat(msg,"LIF ");
      else if  (api->prop->dtv_internal_zif.dvbt   ==     1) strcat(msg,"ZIF ");
      else                                                  sprintf(msg,"%s%d", msg, api->prop->dtv_internal_zif.dvbt);
       strcat(msg,separator); strcat(msg,"-DVBC ");
           if  (api->prop->dtv_internal_zif.dvbc   ==     0) strcat(msg,"LIF ");
      else if  (api->prop->dtv_internal_zif.dvbc   ==     1) strcat(msg,"ZIF ");
      else                                                  sprintf(msg,"%s%d", msg, api->prop->dtv_internal_zif.dvbc);
       strcat(msg,separator); strcat(msg,"-ISDBT ");
           if  (api->prop->dtv_internal_zif.isdbt  ==     0) strcat(msg,"LIF ");
      else if  (api->prop->dtv_internal_zif.isdbt  ==     1) strcat(msg,"ZIF ");
      else                                                  sprintf(msg,"%s%d", msg, api->prop->dtv_internal_zif.isdbt);
       strcat(msg,separator); strcat(msg,"-ISDBC ");
           if  (api->prop->dtv_internal_zif.isdbc  ==     0) strcat(msg,"LIF ");
      else if  (api->prop->dtv_internal_zif.isdbc  ==     1) strcat(msg,"ZIF ");
      else                                                  sprintf(msg,"%s%d", msg, api->prop->dtv_internal_zif.isdbc);
       strcat(msg,separator); strcat(msg,"-DTMB ");
           if  (api->prop->dtv_internal_zif.dtmb   ==     0) strcat(msg,"LIF ");
      else if  (api->prop->dtv_internal_zif.dtmb   ==     1) strcat(msg,"ZIF ");
      else                                                  sprintf(msg,"%s%d", msg, api->prop->dtv_internal_zif.dtmb);
     break;
    #endif /*     Si2158_DTV_INTERNAL_ZIF_PROP */
    #ifdef        Si2158_DTV_INT_SENSE_PROP
     case         Si2158_DTV_INT_SENSE_PROP_CODE:
      sprintf(msg,"DTV_INT_SENSE");
       strcat(msg,separator); strcat(msg,"-CHLNEGEN ");
           if  (api->prop->dtv_int_sense.chlnegen ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->dtv_int_sense.chlnegen ==     1) strcat(msg,"ENABLE  ");
      else                                                 sprintf(msg,"%s%d", msg, api->prop->dtv_int_sense.chlnegen);
       strcat(msg,separator); strcat(msg,"-CHLPOSEN ");
           if  (api->prop->dtv_int_sense.chlposen ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->dtv_int_sense.chlposen ==     1) strcat(msg,"ENABLE  ");
      else                                                 sprintf(msg,"%s%d", msg, api->prop->dtv_int_sense.chlposen);
     break;
    #endif /*     Si2158_DTV_INT_SENSE_PROP */
    #ifdef        Si2158_DTV_LIF_FREQ_PROP
     case         Si2158_DTV_LIF_FREQ_PROP_CODE:
      sprintf(msg,"DTV_LIF_FREQ");
       strcat(msg,separator); strcat(msg,"-OFFSET "); sprintf(msg,"%s%d", msg, api->prop->dtv_lif_freq.offset);
     break;
    #endif /*     Si2158_DTV_LIF_FREQ_PROP */
    #ifdef        Si2158_DTV_LIF_OUT_PROP
     case         Si2158_DTV_LIF_OUT_PROP_CODE:
      sprintf(msg,"DTV_LIF_OUT");
       strcat(msg,separator); strcat(msg,"-OFFSET "); sprintf(msg,"%s%d", msg, api->prop->dtv_lif_out.offset);
       strcat(msg,separator); strcat(msg,"-AMP "); sprintf(msg,"%s%d", msg, api->prop->dtv_lif_out.amp);
     break;
    #endif /*     Si2158_DTV_LIF_OUT_PROP */
    #ifdef        Si2158_DTV_MODE_PROP
     case         Si2158_DTV_MODE_PROP_CODE:
      sprintf(msg,"DTV_MODE");
       strcat(msg,separator); strcat(msg,"-BW ");
           if  (api->prop->dtv_mode.bw              ==     6) strcat(msg,"BW_6MHZ ");
      else if  (api->prop->dtv_mode.bw              ==     7) strcat(msg,"BW_7MHZ ");
      else if  (api->prop->dtv_mode.bw              ==     8) strcat(msg,"BW_8MHZ ");
      else                                                   sprintf(msg,"%s%d", msg, api->prop->dtv_mode.bw);
       strcat(msg,separator); strcat(msg,"-MODULATION ");
           if  (api->prop->dtv_mode.modulation      ==     0) strcat(msg,"ATSC   ");
      else if  (api->prop->dtv_mode.modulation      ==     1) strcat(msg,"QAM_US ");
      else if  (api->prop->dtv_mode.modulation      ==     2) strcat(msg,"DVBT   ");
      else if  (api->prop->dtv_mode.modulation      ==     3) strcat(msg,"DVBC   ");
      else if  (api->prop->dtv_mode.modulation      ==     4) strcat(msg,"ISDBT  ");
      else if  (api->prop->dtv_mode.modulation      ==     5) strcat(msg,"ISDBC  ");
      else if  (api->prop->dtv_mode.modulation      ==     6) strcat(msg,"DTMB   ");
      else if  (api->prop->dtv_mode.modulation      ==    15) strcat(msg,"CW     ");
      else                                                   sprintf(msg,"%s%d", msg, api->prop->dtv_mode.modulation);
       strcat(msg,separator); strcat(msg,"-INVERT_SPECTRUM ");
           if  (api->prop->dtv_mode.invert_spectrum ==     0) strcat(msg,"NORMAL   ");
      else if  (api->prop->dtv_mode.invert_spectrum ==     1) strcat(msg,"INVERTED ");
      else                                                   sprintf(msg,"%s%d", msg, api->prop->dtv_mode.invert_spectrum);
     break;
    #endif /*     Si2158_DTV_MODE_PROP */
    #ifdef        Si2158_DTV_PGA_LIMITS_PROP
     case         Si2158_DTV_PGA_LIMITS_PROP_CODE:
      sprintf(msg,"DTV_PGA_LIMITS");
       strcat(msg,separator); strcat(msg,"-MIN "); sprintf(msg,"%s%d", msg, api->prop->dtv_pga_limits.min);
       strcat(msg,separator); strcat(msg,"-MAX "); sprintf(msg,"%s%d", msg, api->prop->dtv_pga_limits.max);
     break;
    #endif /*     Si2158_DTV_PGA_LIMITS_PROP */
    #ifdef        Si2158_DTV_PGA_TARGET_PROP
     case         Si2158_DTV_PGA_TARGET_PROP_CODE:
      sprintf(msg,"DTV_PGA_TARGET");
       strcat(msg,separator); strcat(msg,"-PGA_TARGET "); sprintf(msg,"%s%d", msg, api->prop->dtv_pga_target.pga_target);
       strcat(msg,separator); strcat(msg,"-OVERRIDE_ENABLE ");
           if  (api->prop->dtv_pga_target.override_enable ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->dtv_pga_target.override_enable ==     1) strcat(msg,"ENABLE  ");
      else                                                         sprintf(msg,"%s%d", msg, api->prop->dtv_pga_target.override_enable);
     break;
    #endif /*     Si2158_DTV_PGA_TARGET_PROP */
    #ifdef        Si2158_DTV_RF_TOP_PROP
     case         Si2158_DTV_RF_TOP_PROP_CODE:
      sprintf(msg,"DTV_RF_TOP");
       strcat(msg,separator); strcat(msg,"-DTV_RF_TOP ");
           if  (api->prop->dtv_rf_top.dtv_rf_top ==     0) strcat(msg,"AUTO    ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==     1) strcat(msg,"P10DB   ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==     2) strcat(msg,"P9P5DB  ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==     3) strcat(msg,"P9DB    ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==     4) strcat(msg,"P8P5DB  ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==     5) strcat(msg,"P8DB    ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==     6) strcat(msg,"P7P5DB  ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==     7) strcat(msg,"P7DB    ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==     8) strcat(msg,"P6P5DB  ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==     9) strcat(msg,"P6DB    ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    10) strcat(msg,"P5P5DB  ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    11) strcat(msg,"P5DB    ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    12) strcat(msg,"P4P5DB  ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    13) strcat(msg,"P4DB    ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    14) strcat(msg,"P3P5DB  ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    15) strcat(msg,"P3DB    ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    16) strcat(msg,"P2P5DB  ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    17) strcat(msg,"P2DB    ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    18) strcat(msg,"P1P5DB  ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    19) strcat(msg,"P1DB    ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    20) strcat(msg,"P0P5DB  ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    21) strcat(msg,"0DB     ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    22) strcat(msg,"M0P5DB  ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    23) strcat(msg,"M1DB    ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    24) strcat(msg,"M1P5DB  ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    25) strcat(msg,"M2DB    ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    26) strcat(msg,"M2P5DB  ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    27) strcat(msg,"M3DB    ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    28) strcat(msg,"M3P5DB  ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    29) strcat(msg,"M4DB    ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    30) strcat(msg,"M4P5DB  ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    31) strcat(msg,"M5DB    ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    32) strcat(msg,"M5P5DB  ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    33) strcat(msg,"M6DB    ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    34) strcat(msg,"M6P5DB  ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    35) strcat(msg,"M7DB    ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    36) strcat(msg,"M7P5DB  ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    37) strcat(msg,"M8DB    ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    38) strcat(msg,"M8P5DB  ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    39) strcat(msg,"M9DB    ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    40) strcat(msg,"M9P5DB  ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    41) strcat(msg,"M10DB   ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    42) strcat(msg,"M10P5DB ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    43) strcat(msg,"M11DB   ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    44) strcat(msg,"M11P5DB ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    45) strcat(msg,"M12DB   ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    46) strcat(msg,"M12P5DB ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    47) strcat(msg,"M13DB   ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    48) strcat(msg,"M13P5DB ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    49) strcat(msg,"M14DB   ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    50) strcat(msg,"M14P5DB ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    51) strcat(msg,"M15DB   ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    52) strcat(msg,"M15P5DB ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    53) strcat(msg,"M16DB   ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    54) strcat(msg,"M16P5DB ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    55) strcat(msg,"M17DB   ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    56) strcat(msg,"M17P5DB ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    57) strcat(msg,"M18DB   ");
      else if  (api->prop->dtv_rf_top.dtv_rf_top ==    58) strcat(msg,"M18P5DB ");
      else                                                sprintf(msg,"%s%d", msg, api->prop->dtv_rf_top.dtv_rf_top);
     break;
    #endif /*     Si2158_DTV_RF_TOP_PROP */
    #ifdef        Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP
     case         Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP_CODE:
      sprintf(msg,"DTV_RSQ_RSSI_THRESHOLD");
       strcat(msg,separator); strcat(msg,"-LO "); sprintf(msg,"%s%d", msg, api->prop->dtv_rsq_rssi_threshold.lo);
       strcat(msg,separator); strcat(msg,"-HI "); sprintf(msg,"%s%d", msg, api->prop->dtv_rsq_rssi_threshold.hi);
     break;
    #endif /*     Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef        Si2158_DTV_ZIF_DC_CANCELLER_BW_PROP
     case         Si2158_DTV_ZIF_DC_CANCELLER_BW_PROP_CODE:
      sprintf(msg,"DTV_ZIF_DC_CANCELLER_BW");
       strcat(msg,separator); strcat(msg,"-BANDWIDTH ");
           if  (api->prop->dtv_zif_dc_canceller_bw.bandwidth ==     0) strcat(msg,"4_Hz      ");
      else if  (api->prop->dtv_zif_dc_canceller_bw.bandwidth ==     1) strcat(msg,"8_Hz      ");
      else if  (api->prop->dtv_zif_dc_canceller_bw.bandwidth ==     2) strcat(msg,"15_Hz     ");
      else if  (api->prop->dtv_zif_dc_canceller_bw.bandwidth ==     3) strcat(msg,"30_Hz     ");
      else if  (api->prop->dtv_zif_dc_canceller_bw.bandwidth ==     4) strcat(msg,"61_Hz     ");
      else if  (api->prop->dtv_zif_dc_canceller_bw.bandwidth ==     5) strcat(msg,"121_Hz    ");
      else if  (api->prop->dtv_zif_dc_canceller_bw.bandwidth ==     6) strcat(msg,"243_Hz    ");
      else if  (api->prop->dtv_zif_dc_canceller_bw.bandwidth ==     7) strcat(msg,"486_Hz    ");
      else if  (api->prop->dtv_zif_dc_canceller_bw.bandwidth ==     8) strcat(msg,"972_Hz    ");
      else if  (api->prop->dtv_zif_dc_canceller_bw.bandwidth ==     9) strcat(msg,"1943_Hz   ");
      else if  (api->prop->dtv_zif_dc_canceller_bw.bandwidth ==    10) strcat(msg,"3888_Hz   ");
      else if  (api->prop->dtv_zif_dc_canceller_bw.bandwidth ==    11) strcat(msg,"7779_Hz   ");
      else if  (api->prop->dtv_zif_dc_canceller_bw.bandwidth ==    12) strcat(msg,"15573_Hz  ");
      else if  (api->prop->dtv_zif_dc_canceller_bw.bandwidth ==    13) strcat(msg,"31207_Hz  ");
      else if  (api->prop->dtv_zif_dc_canceller_bw.bandwidth ==    14) strcat(msg,"62658_Hz  ");
      else if  (api->prop->dtv_zif_dc_canceller_bw.bandwidth ==    15) strcat(msg,"126303_Hz ");
      else if  (api->prop->dtv_zif_dc_canceller_bw.bandwidth ==    16) strcat(msg,"DEFAULT   ");
      else                                                            sprintf(msg,"%s%d", msg, api->prop->dtv_zif_dc_canceller_bw.bandwidth);
     break;
    #endif /*     Si2158_DTV_ZIF_DC_CANCELLER_BW_PROP */
    #ifdef        Si2158_MASTER_IEN_PROP
     case         Si2158_MASTER_IEN_PROP_CODE:
      sprintf(msg,"MASTER_IEN");
       strcat(msg,separator); strcat(msg,"-TUNIEN ");
           if  (api->prop->master_ien.tunien ==     0) strcat(msg,"OFF ");
      else if  (api->prop->master_ien.tunien ==     1) strcat(msg,"ON  ");
      else                                            sprintf(msg,"%s%d", msg, api->prop->master_ien.tunien);
       strcat(msg,separator); strcat(msg,"-ATVIEN ");
           if  (api->prop->master_ien.atvien ==     0) strcat(msg,"OFF ");
      else if  (api->prop->master_ien.atvien ==     1) strcat(msg,"ON  ");
      else                                            sprintf(msg,"%s%d", msg, api->prop->master_ien.atvien);
       strcat(msg,separator); strcat(msg,"-DTVIEN ");
           if  (api->prop->master_ien.dtvien ==     0) strcat(msg,"OFF ");
      else if  (api->prop->master_ien.dtvien ==     1) strcat(msg,"ON  ");
      else                                            sprintf(msg,"%s%d", msg, api->prop->master_ien.dtvien);
       strcat(msg,separator); strcat(msg,"-ERRIEN ");
           if  (api->prop->master_ien.errien ==     0) strcat(msg,"OFF ");
      else if  (api->prop->master_ien.errien ==     1) strcat(msg,"ON  ");
      else                                            sprintf(msg,"%s%d", msg, api->prop->master_ien.errien);
       strcat(msg,separator); strcat(msg,"-CTSIEN ");
           if  (api->prop->master_ien.ctsien ==     0) strcat(msg,"OFF ");
      else if  (api->prop->master_ien.ctsien ==     1) strcat(msg,"ON  ");
      else                                            sprintf(msg,"%s%d", msg, api->prop->master_ien.ctsien);
     break;
    #endif /*     Si2158_MASTER_IEN_PROP */
    #ifdef        Si2158_TUNER_BLOCKED_VCO_PROP
     case         Si2158_TUNER_BLOCKED_VCO_PROP_CODE:
      sprintf(msg,"TUNER_BLOCKED_VCO");
       strcat(msg,separator); strcat(msg,"-VCO_CODE "); sprintf(msg,"%s%d", msg, api->prop->tuner_blocked_vco.vco_code);
     break;
    #endif /*     Si2158_TUNER_BLOCKED_VCO_PROP */
    #ifdef        Si2158_TUNER_IEN_PROP
     case         Si2158_TUNER_IEN_PROP_CODE:
      sprintf(msg,"TUNER_IEN");
       strcat(msg,separator); strcat(msg,"-TCIEN ");
           if  (api->prop->tuner_ien.tcien    ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->tuner_ien.tcien    ==     1) strcat(msg,"ENABLE  ");
      else                                             sprintf(msg,"%s%d", msg, api->prop->tuner_ien.tcien);
       strcat(msg,separator); strcat(msg,"-RSSILIEN ");
           if  (api->prop->tuner_ien.rssilien ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->tuner_ien.rssilien ==     1) strcat(msg,"ENABLE  ");
      else                                             sprintf(msg,"%s%d", msg, api->prop->tuner_ien.rssilien);
       strcat(msg,separator); strcat(msg,"-RSSIHIEN ");
           if  (api->prop->tuner_ien.rssihien ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->tuner_ien.rssihien ==     1) strcat(msg,"ENABLE  ");
      else                                             sprintf(msg,"%s%d", msg, api->prop->tuner_ien.rssihien);
     break;
    #endif /*     Si2158_TUNER_IEN_PROP */
    #ifdef        Si2158_TUNER_INT_SENSE_PROP
     case         Si2158_TUNER_INT_SENSE_PROP_CODE:
      sprintf(msg,"TUNER_INT_SENSE");
       strcat(msg,separator); strcat(msg,"-TCNEGEN ");
           if  (api->prop->tuner_int_sense.tcnegen    ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->tuner_int_sense.tcnegen    ==     1) strcat(msg,"ENABLE  ");
      else                                                     sprintf(msg,"%s%d", msg, api->prop->tuner_int_sense.tcnegen);
       strcat(msg,separator); strcat(msg,"-RSSILNEGEN ");
           if  (api->prop->tuner_int_sense.rssilnegen ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->tuner_int_sense.rssilnegen ==     1) strcat(msg,"ENABLE  ");
      else                                                     sprintf(msg,"%s%d", msg, api->prop->tuner_int_sense.rssilnegen);
       strcat(msg,separator); strcat(msg,"-RSSIHNEGEN ");
           if  (api->prop->tuner_int_sense.rssihnegen ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->tuner_int_sense.rssihnegen ==     1) strcat(msg,"ENABLE  ");
      else                                                     sprintf(msg,"%s%d", msg, api->prop->tuner_int_sense.rssihnegen);
       strcat(msg,separator); strcat(msg,"-TCPOSEN ");
           if  (api->prop->tuner_int_sense.tcposen    ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->tuner_int_sense.tcposen    ==     1) strcat(msg,"ENABLE  ");
      else                                                     sprintf(msg,"%s%d", msg, api->prop->tuner_int_sense.tcposen);
       strcat(msg,separator); strcat(msg,"-RSSILPOSEN ");
           if  (api->prop->tuner_int_sense.rssilposen ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->tuner_int_sense.rssilposen ==     1) strcat(msg,"ENABLE  ");
      else                                                     sprintf(msg,"%s%d", msg, api->prop->tuner_int_sense.rssilposen);
       strcat(msg,separator); strcat(msg,"-RSSIHPOSEN ");
           if  (api->prop->tuner_int_sense.rssihposen ==     0) strcat(msg,"DISABLE ");
      else if  (api->prop->tuner_int_sense.rssihposen ==     1) strcat(msg,"ENABLE  ");
      else                                                     sprintf(msg,"%s%d", msg, api->prop->tuner_int_sense.rssihposen);
     break;
    #endif /*     Si2158_TUNER_INT_SENSE_PROP */
    #ifdef        Si2158_TUNER_LO_INJECTION_PROP
     case         Si2158_TUNER_LO_INJECTION_PROP_CODE:
      sprintf(msg,"TUNER_LO_INJECTION");
       strcat(msg,separator); strcat(msg,"-BAND_1 ");
           if  (api->prop->tuner_lo_injection.band_1 ==     0) strcat(msg,"LOW_SIDE  ");
      else if  (api->prop->tuner_lo_injection.band_1 ==     1) strcat(msg,"HIGH_SIDE ");
      else                                                    sprintf(msg,"%s%d", msg, api->prop->tuner_lo_injection.band_1);
       strcat(msg,separator); strcat(msg,"-BAND_2 ");
           if  (api->prop->tuner_lo_injection.band_2 ==     0) strcat(msg,"LOW_SIDE  ");
      else if  (api->prop->tuner_lo_injection.band_2 ==     1) strcat(msg,"HIGH_SIDE ");
      else                                                    sprintf(msg,"%s%d", msg, api->prop->tuner_lo_injection.band_2);
       strcat(msg,separator); strcat(msg,"-BAND_3 ");
           if  (api->prop->tuner_lo_injection.band_3 ==     0) strcat(msg,"LOW_SIDE  ");
      else if  (api->prop->tuner_lo_injection.band_3 ==     1) strcat(msg,"HIGH_SIDE ");
      else                                                    sprintf(msg,"%s%d", msg, api->prop->tuner_lo_injection.band_3);
     break;
    #endif /*     Si2158_TUNER_LO_INJECTION_PROP */
    #ifdef        Si2158_TUNER_RETURN_LOSS_PROP
     case         Si2158_TUNER_RETURN_LOSS_PROP_CODE:
      sprintf(msg,"TUNER_RETURN_LOSS");
       strcat(msg,separator); strcat(msg,"-CONFIG ");
           if  (api->prop->tuner_return_loss.config ==     3) strcat(msg,"3   ");
      else if  (api->prop->tuner_return_loss.config ==     7) strcat(msg,"7   ");
      else if  (api->prop->tuner_return_loss.config ==    11) strcat(msg,"11  ");
      else if  (api->prop->tuner_return_loss.config ==    15) strcat(msg,"15  ");
      else if  (api->prop->tuner_return_loss.config ==    19) strcat(msg,"19  ");
      else if  (api->prop->tuner_return_loss.config ==    23) strcat(msg,"23  ");
      else if  (api->prop->tuner_return_loss.config ==    27) strcat(msg,"27  ");
      else if  (api->prop->tuner_return_loss.config ==    31) strcat(msg,"31  ");
      else if  (api->prop->tuner_return_loss.config ==    35) strcat(msg,"35  ");
      else if  (api->prop->tuner_return_loss.config ==    39) strcat(msg,"39  ");
      else if  (api->prop->tuner_return_loss.config ==    43) strcat(msg,"43  ");
      else if  (api->prop->tuner_return_loss.config ==    47) strcat(msg,"47  ");
      else if  (api->prop->tuner_return_loss.config ==    51) strcat(msg,"51  ");
      else if  (api->prop->tuner_return_loss.config ==    59) strcat(msg,"59  ");
      else if  (api->prop->tuner_return_loss.config ==    67) strcat(msg,"67  ");
      else if  (api->prop->tuner_return_loss.config ==    75) strcat(msg,"75  ");
      else if  (api->prop->tuner_return_loss.config ==    83) strcat(msg,"83  ");
      else if  (api->prop->tuner_return_loss.config ==    91) strcat(msg,"91  ");
      else if  (api->prop->tuner_return_loss.config ==   103) strcat(msg,"103 ");
      else if  (api->prop->tuner_return_loss.config ==   115) strcat(msg,"115 ");
      else if  (api->prop->tuner_return_loss.config ==   127) strcat(msg,"127 ");
      else                                                   sprintf(msg,"%s%d", msg, api->prop->tuner_return_loss.config);
       strcat(msg,separator); strcat(msg,"-MODE ");
           if  (api->prop->tuner_return_loss.mode   ==     0) strcat(msg,"TERRESTRIAL ");
      else if  (api->prop->tuner_return_loss.mode   ==     1) strcat(msg,"CABLE       ");
      else                                                   sprintf(msg,"%s%d", msg, api->prop->tuner_return_loss.mode);
     break;
    #endif /*     Si2158_TUNER_RETURN_LOSS_PROP */
    #ifdef        Si2158_XOUT_PROP
     case         Si2158_XOUT_PROP_CODE:
      sprintf(msg,"XOUT");
       strcat(msg,separator); strcat(msg,"-AMP ");
           if  (api->prop->xout.amp ==     0) strcat(msg,"HIGH ");
      else if  (api->prop->xout.amp ==     1) strcat(msg,"LOW  ");
      else                                   sprintf(msg,"%s%d", msg, api->prop->xout.amp);
     break;
    #endif /*     Si2158_XOUT_PROP */
   default : sprintf(msg,"Unknown property code '0x%06x'\n", prop_code); break;
    }
  }
  /* _get_property_string_insertion_point */
#endif /* Si2158_GET_PROPERTY_STRING */






