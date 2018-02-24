/*************************************************************************************
                  Silicon Laboratories Broadcast Si21XXC Layer 1 API

   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
    PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.

   API functions prototypes used by commands and properties
   FILE: Si21XXC_Commands_Prototypes.h
   Supported IC : Si2178B,Si2190B,Si2191B,Si2191C
   Compiled for ROM 71 firmware 3_0_build_1
   Revision: 0.1
   Tag:  Si2190B_30b1_Si2178B_42b7_Si2191C_30b1_Si2191B_42b7_V0.1
   Date: August 12 2015
  (C) Copyright 2014, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#ifndef    Si21XXC_COMMANDS_PROTOTYPES_H
#define    Si21XXC_COMMANDS_PROTOTYPES_H

#ifdef __cplusplus
extern "C"{
#endif
unsigned char Si21XXC_CurrentResponseStatus (L1_Si21XXC_Context *api, unsigned char ptDataBuffer);
unsigned char Si21XXC_pollForResetState     (L1_Si21XXC_Context *api);
unsigned char Si21XXC_pollForCTS            (L1_Si21XXC_Context *api);
unsigned char Si21XXC_pollForResponse       (L1_Si21XXC_Context *api, unsigned int nbBytes, unsigned char *pByteBuffer);
unsigned char Si21XXC_L1_SendCommand2       (L1_Si21XXC_Context *api, unsigned int cmd_code);
unsigned char Si21XXC_L1_SetProperty        (L1_Si21XXC_Context *api, unsigned int prop_code, int  data);
unsigned char Si21XXC_L1_GetProperty        (L1_Si21XXC_Context *api, unsigned int prop_code, int *data);
unsigned char Si21XXC_L1_SetProperty2       (L1_Si21XXC_Context *api, unsigned int prop_code);
unsigned char Si21XXC_L1_GetProperty2       (L1_Si21XXC_Context *api, unsigned int prop_code);

#ifdef    Si21XXC_GET_PROPERTY_STRING
unsigned char    Si21XXC_L1_GetPropertyString        (L1_Si21XXC_Context *api, unsigned int prop_code, const char *separator, char *msg);
unsigned char Si21XXC_L1_PropertyText       (Si21XXC_PropObj   *prop, unsigned int prop_code, const char *separator, char *msg);
#endif /* Si21XXC_GET_PROPERTY_STRING */

#ifdef    Si21XXC_GET_COMMAND_STRINGS
  unsigned char   Si21XXC_L1_GetCommandResponseString(L1_Si21XXC_Context *api, unsigned int cmd_code, const char *separator, char *msg);
#endif /* Si21XXC_GET_COMMAND_STRINGS */

#ifdef    Si21XXC_AGC_OVERRIDE_CMD
unsigned char Si21XXC_L1_AGC_OVERRIDE      (L1_Si21XXC_Context *api,
                                           unsigned char   force_max_gain,
                                           unsigned char   force_top_gain);
#endif /* Si21XXC_AGC_OVERRIDE_CMD */
#ifdef    Si21XXC_ATV_RESTART_CMD
unsigned char Si21XXC_L1_ATV_RESTART       (L1_Si21XXC_Context *api,
                                           unsigned char   mode);
#endif /* Si21XXC_ATV_RESTART_CMD */
#ifdef    Si21XXC_ATV_STATUS_CMD
unsigned char Si21XXC_L1_ATV_STATUS        (L1_Si21XXC_Context *api,
                                           unsigned char   intack);
#endif /* Si21XXC_ATV_STATUS_CMD */
#ifdef    Si21XXC_CONFIG_CLOCKS_CMD
unsigned char Si21XXC_L1_CONFIG_CLOCKS     (L1_Si21XXC_Context *api,
                                           unsigned char   subcode,
                                           unsigned char   clock_mode,
                                           unsigned char   en_xout);
#endif /* Si21XXC_CONFIG_CLOCKS_CMD */
#ifdef    Si21XXC_CONFIG_I2C_CMD
unsigned char Si21XXC_L1_CONFIG_I2C        (L1_Si21XXC_Context *api,
                                           unsigned char   subcode,
                                           unsigned char   i2c_broadcast);
#endif /* Si21XXC_CONFIG_I2C_CMD */
#ifdef    Si2190B_CONFIG_PINS_CMD
unsigned char Si2190B_L1_CONFIG_PINS       (L1_Si21XXC_Context *api,
                                           unsigned char   gpio1_mode,
                                           unsigned char   gpio1_read,
                                           unsigned char   gpio2_mode,
                                           unsigned char   gpio2_read,
                                           unsigned char   agc1_mode,
                                           unsigned char   agc1_read,
                                           unsigned char   agc2_mode,
                                           unsigned char   agc2_read,
                                           unsigned char   reserved3);
#endif /* Si2190B_CONFIG_PINS_CMD */
#ifdef    Si2178B_CONFIG_PINS_CMD
 /*---------------------------------------------------*/
/* Si2178B_CONFIG_PINS COMMAND                      */
/*---------------------------------------------------*/
unsigned char Si2178B_L1_CONFIG_PINS     (L1_Si21XXC_Context *api,
                                         unsigned char   gpio1_mode,
                                         unsigned char   gpio1_read,
                                         unsigned char   gpio2_mode,
                                         unsigned char   gpio2_read,
                                         unsigned char   reserved1,
                                         unsigned char   reserved2,
                                         unsigned char   reserved3);
#endif /* Si2178B_CONFIG_PINS_CMD */

#ifdef    Si21XXC_DTV_RESTART_CMD
unsigned char Si21XXC_L1_DTV_RESTART       (L1_Si21XXC_Context *api);
#endif /* Si21XXC_DTV_RESTART_CMD */
#ifdef    Si21XXC_DTV_STATUS_CMD
unsigned char Si21XXC_L1_DTV_STATUS        (L1_Si21XXC_Context *api,
                                           unsigned char   intack);
#endif /* Si21XXC_DTV_STATUS_CMD */
#ifdef    Si2178B_ENABLE_SSVD_ATV_CMD
unsigned char Si2178B_L1_ENABLE_SSVD_ATV (L1_Si21XXC_Context *api);
#endif /* Si2178B_ENABLE_SSVD_ATV_CMD */
#ifdef    Si21XXC_EXIT_BOOTLOADER_CMD
unsigned char Si21XXC_L1_EXIT_BOOTLOADER   (L1_Si21XXC_Context *api,
                                           unsigned char   func,
                                           unsigned char   ctsien);
#endif /* Si21XXC_EXIT_BOOTLOADER_CMD */
#ifdef    Si2178B_FINE_TUNE_CMD
unsigned char Si2178B_L1_FINE_TUNE       (L1_Si21XXC_Context *api,
                                         unsigned char   persistence,
                                         unsigned char   apply_to_lif,
                                                   int   offset_500hz);

#endif/* Si2178B_FINE_TUNE_CMD */
#ifdef    Si21XXC_FINE_TUNE_CMD
unsigned char Si21XXC_L1_FINE_TUNE         (L1_Si21XXC_Context *api,
                                           unsigned char   persistence,
                                                     int   offset_500hz);
#endif /* Si21XXC_FINE_TUNE_CMD */
#ifdef    Si21XXC_GET_PROPERTY_CMD
unsigned char Si21XXC_L1_GET_PROPERTY      (L1_Si21XXC_Context *api,
                                           unsigned char   reserved,
                                           unsigned int    prop);
#endif /* Si21XXC_GET_PROPERTY_CMD */
#ifdef    Si21XXC_GET_REV_CMD
unsigned char Si21XXC_L1_GET_REV           (L1_Si21XXC_Context *api);
#endif /* Si21XXC_GET_REV_CMD */
#ifdef    Si2191C_ISL_STATUS_CMD

unsigned char Si2191C_L1_ISL_STATUS        (L1_Si21XXC_Context *api,
                                           unsigned char   clear);
#endif /* Si2191C_ISL_STATUS_CMD */
#ifdef    Si21XXC_PART_INFO_CMD
unsigned char Si21XXC_L1_PART_INFO         (L1_Si21XXC_Context *api);
#endif /* Si21XXC_PART_INFO_CMD */
#ifdef    Si21XXC_PART_INFO2_CMD
unsigned char Si21XXC_L1_PART_INFO2        (L1_Si21XXC_Context *api);
#endif /* Si21XXC_PART_INFO2_CMD */
#ifdef    Si21XXC_POWER_DOWN_HW_CMD
unsigned char Si21XXC_L1_POWER_DOWN_HW     (L1_Si21XXC_Context *api,
                                           unsigned char   subcode,
                                           unsigned char   pd_xo_osc,
                                           unsigned char   reserved1,
                                           unsigned char   en_xout,
                                           unsigned char   reserved2,
                                           unsigned char   pd_ldo,
                                           unsigned char   reserved3,
                                           unsigned char   reserved4,
                                           unsigned char   reserved5,
                                           unsigned char   reserved6,
                                           unsigned char   reserved7,
                                           unsigned char   reserved8);
#endif /* Si21XXC_POWER_DOWN_HW_CMD */
#ifdef    Si21XXC_POWER_UP_CMD
unsigned char Si21XXC_L1_POWER_UP          (L1_Si21XXC_Context *api,
                                           unsigned char   subcode,
                                           unsigned char   clock_mode,
                                           unsigned char   en_xout,
                                           unsigned char   pd_ldo,
                                           unsigned char   reserved2,
                                           unsigned char   reserved3,
                                           unsigned char   reserved4,
                                           unsigned char   reserved5,
                                           unsigned char   reserved6,
                                           unsigned char   reserved7,
                                           unsigned char   reset,
                                           unsigned char   clock_freq,
                                           unsigned char   reserved8,
                                           unsigned char   func,
                                           unsigned char   ctsien,
                                           unsigned char   wake_up);
#endif /* Si21XXC_POWER_UP_CMD */
#ifdef    Si2190B_REREAD_REPLY_CMD
unsigned char Si2190B_L1_REREAD_REPLY      (L1_Si21XXC_Context *api,
                                           unsigned char   offset);
#endif /* Si2190B_REREAD_REPLY_CMD */
#ifdef    Si2190B_RESET_HW_CMD
unsigned char Si2190B_L1_RESET_HW          (L1_Si21XXC_Context *api,
                                           unsigned char   subcode,
                                           unsigned char   reserved1,
                                           unsigned char   reserved2);
#endif /* Si2190B_RESET_HW_CMD */
#ifdef    Si2190B_SELF_TEST_CMD
unsigned char Si2190B_L1_SELF_TEST         (L1_Si21XXC_Context *api);
#endif /* Si2190B_SELF_TEST_CMD */
#ifdef    Si21XXC_SET_PROPERTY_CMD
unsigned char Si21XXC_L1_SET_PROPERTY      (L1_Si21XXC_Context *api,
                                           unsigned char   reserved,
                                           unsigned int    prop,
                                           unsigned int    data);
#endif /* Si21XXC_SET_PROPERTY_CMD */
#ifdef    Si2190B_SSVD_DEBUG_CONFIG_CMD
unsigned char Si2190B_L1_SSVD_DEBUG_CONFIG (L1_Si21XXC_Context *api,
                                           unsigned char   cvbs_out,
                                           unsigned char   sif_out);
#endif /* Si2190B_SSVD_DEBUG_CONFIG_CMD */
#ifdef    Si2190B_SSVD_HDIV_CMD
unsigned char Si2190B_L1_SSVD_HDIV         (L1_Si21XXC_Context *api,
                                           unsigned char   enable,
                                           unsigned int    st_ctrl0,
                                           unsigned int    ha_ctrl0);
#endif /* Si2190B_SSVD_HDIV_CMD */
#ifdef    Si2190B_SSVD_MULTI_REG_RD_CMD
unsigned char Si2190B_L1_SSVD_MULTI_REG_RD (L1_Si21XXC_Context *api,
                                           unsigned char   reg_sel,
                                           unsigned char   num_regs);
#endif /* Si2190B_SSVD_MULTI_REG_RD_CMD */
#ifdef    Si2190B_SSVD_MULTI_REG_WR_CMD
unsigned char Si2190B_L1_SSVD_MULTI_REG_WR (L1_Si21XXC_Context *api,
                                           unsigned char   reg_sel,
                                           unsigned char   update,
                                           unsigned char   num_regs,
                                           unsigned int    data0,
                                           unsigned int    data1,
                                           unsigned int    data2,
                                           unsigned int    data3,
                                           unsigned int    data4,
                                           unsigned int    data5,
                                           unsigned int    data6);
#endif /* Si2190B_SSVD_MULTI_REG_WR_CMD */
#ifdef    Si2190B_SSVD_POWER_DOWN_CMD
unsigned char Si2190B_L1_SSVD_POWER_DOWN   (L1_Si21XXC_Context *api);
#endif /* Si2190B_SSVD_POWER_DOWN_CMD */
#ifdef    Si2190B_SSVD_POWER_UP_CMD
unsigned char Si2190B_L1_SSVD_POWER_UP     (L1_Si21XXC_Context *api);
#endif /* Si2190B_SSVD_POWER_UP_CMD */
#ifdef    Si2190B_SSVD_REG_RD_CMD
unsigned char Si2190B_L1_SSVD_REG_RD       (L1_Si21XXC_Context *api,
                                           unsigned char   reg_sel,
                                           unsigned char   ignored);
#endif /* Si2190B_SSVD_REG_RD_CMD */
#ifdef    Si2190B_SSVD_REG_WR_CMD
unsigned char Si2190B_L1_SSVD_REG_WR       (L1_Si21XXC_Context *api,
                                           unsigned char   reg_sel,
                                           unsigned char   update,
                                           unsigned char   ignored,
                                           unsigned int    data);
#endif /* Si2190B_SSVD_REG_WR_CMD */
#ifdef    Si21XXC_STANDBY_CMD
unsigned char Si21XXC_L1_STANDBY           (L1_Si21XXC_Context *api,
                                           unsigned char   type);
#endif /* Si21XXC_STANDBY_CMD */
#ifdef    Si2190B_TUNER_CANCEL_TONE_STATUS_CMD
unsigned char Si2190B_L1_TUNER_CANCEL_TONE_STATUS (L1_Si21XXC_Context *api,
                                                  unsigned char   tc_num);
#endif /* Si2190B_TUNER_CANCEL_TONE_STATUS_CMD */
#ifdef    Si2190B_TUNER_CANCEL_TONE_CMD
unsigned char Si2190B_L1_TUNER_CANCEL_TONE (L1_Si21XXC_Context *api,
                                           unsigned int    div_a,
                                           unsigned int    div_b);
#endif /* Si2190B_TUNER_CANCEL_TONE_CMD */
#ifdef    Si21XXC_TUNER_STATUS_CMD
unsigned char Si21XXC_L1_TUNER_STATUS      (L1_Si21XXC_Context *api,
                                           unsigned char   intack);
#endif /* Si21XXC_TUNER_STATUS_CMD */
#ifdef    Si21XXC_TUNER_TUNE_FREQ_CMD
unsigned char Si21XXC_L1_TUNER_TUNE_FREQ   (L1_Si21XXC_Context *api,
                                           unsigned char   mode,
                                           unsigned long   freq);
#endif /* Si21XXC_TUNER_TUNE_FREQ_CMD */
/* _commands_prototypes_insertion_point */
#ifdef __cplusplus
}
#endif
#endif /* Si21XXC_COMMANDS_PROTOTYPES_H */











