/*************************************************************************************
                  Silicon Laboratories Broadcast Si2190 Layer 1 API
   API functions prototypes used by commands and properties
   FILE: Si2190_Commands_Prototypes.h
   Supported IC : Si2190
   Compiled for ROM 40 firmware 0_A_build_10
   Revision: 0.1
   Date: August 13 2012
  (C) Copyright 2012, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#ifndef    Si2190_COMMANDS_PROTOTYPES_H
#define    Si2190_COMMANDS_PROTOTYPES_H

unsigned char Si2190_CurrentResponseStatus (L1_Si2190_Context *api, unsigned char ptDataBuffer);
unsigned char Si2190_pollForCTS            (L1_Si2190_Context *api);
unsigned char Si2190_pollForResponse       (L1_Si2190_Context *api, unsigned int nbBytes, unsigned char *pByteBuffer);
unsigned char Si2190_L1_SendCommand2       (L1_Si2190_Context *api, unsigned int cmd_code);
unsigned char Si2190_L1_SetProperty        (L1_Si2190_Context *api, unsigned int prop, int  data);
unsigned char Si2190_L1_GetProperty        (L1_Si2190_Context *api, unsigned int prop, int *data);
unsigned char Si2190_L1_SetProperty2       (L1_Si2190_Context *api, unsigned int prop_code);
unsigned char Si2190_L1_GetProperty2       (L1_Si2190_Context *api, unsigned int prop_code);

#ifdef    Si2190_GET_PROPERTY_STRING
unsigned char    Si2190_L1_GetPropertyString        (L1_Si2190_Context *api, unsigned int prop_code, const char *separator, char *msg);
#endif /* Si2190_GET_PROPERTY_STRING */

#ifdef    Si2190_GET_COMMAND_STRINGS
  unsigned char   Si2190_L1_GetCommandResponseString(L1_Si2190_Context *api, unsigned int cmd_code, const char *separator, char *msg);
#endif /* Si2190_GET_COMMAND_STRINGS */

/* _commands_prototypes_insertion_start */
#ifdef    Si2190_AGC_OVERRIDE_CMD
unsigned char Si2190_L1_AGC_OVERRIDE      (L1_Si2190_Context *api,
                                           unsigned char   force_max_gain,
                                           unsigned char   force_top_gain);
#endif /* Si2190_AGC_OVERRIDE_CMD */
#ifdef    Si2190_ATV_RESTART_CMD
unsigned char Si2190_L1_ATV_RESTART       (L1_Si2190_Context *api,
                                           unsigned char   mode);
#endif /* Si2190_ATV_RESTART_CMD */
#ifdef    Si2190_ATV_STATUS_CMD
unsigned char Si2190_L1_ATV_STATUS        (L1_Si2190_Context *api,
                                           unsigned char   intack);
#endif /* Si2190_ATV_STATUS_CMD */
#ifdef    Si2190_CONFIG_CLOCKS_CMD
unsigned char Si2190_L1_CONFIG_CLOCKS     (L1_Si2190_Context *api,
                                           unsigned char   subcode,
                                           unsigned char   clock_mode,
                                           unsigned char   en_xout);
#endif /* Si2190_CONFIG_CLOCKS_CMD */
#ifdef    Si2190_CONFIG_PINS_CMD
unsigned char Si2190_L1_CONFIG_PINS       (L1_Si2190_Context *api,
                                           unsigned char   gpio1_mode,
                                           unsigned char   gpio1_read,
                                           unsigned char   gpio2_mode,
                                           unsigned char   gpio2_read,
                                           unsigned char   reserved1,
                                           unsigned char   reserved2,
                                           unsigned char   reserved3);
#endif /* Si2190_CONFIG_PINS_CMD */
#ifdef    Si2190_DTV_RESTART_CMD
unsigned char Si2190_L1_DTV_RESTART       (L1_Si2190_Context *api);
#endif /* Si2190_DTV_RESTART_CMD */
#ifdef    Si2190_DTV_STATUS_CMD
unsigned char Si2190_L1_DTV_STATUS        (L1_Si2190_Context *api,
                                           unsigned char   intack);
#endif /* Si2190_DTV_STATUS_CMD */
#ifdef    Si2190_EXIT_BOOTLOADER_CMD
unsigned char Si2190_L1_EXIT_BOOTLOADER   (L1_Si2190_Context *api,
                                           unsigned char   func,
                                           unsigned char   ctsien);
#endif /* Si2190_EXIT_BOOTLOADER_CMD */
#ifdef    Si2190_FINE_TUNE_CMD
unsigned char Si2190_L1_FINE_TUNE         (L1_Si2190_Context *api,
                                           unsigned char   persistence,
                                           unsigned char   apply_to_lif,
                                                     int   offset_500hz);
#endif /* Si2190_FINE_TUNE_CMD */
#ifdef    Si2190_GET_PROPERTY_CMD
unsigned char Si2190_L1_GET_PROPERTY      (L1_Si2190_Context *api,
                                           unsigned char   reserved,
                                           unsigned int    prop);
#endif /* Si2190_GET_PROPERTY_CMD */
#ifdef    Si2190_GET_REV_CMD
unsigned char Si2190_L1_GET_REV           (L1_Si2190_Context *api);
#endif /* Si2190_GET_REV_CMD */
#ifdef    Si2190_PART_INFO_CMD
unsigned char Si2190_L1_PART_INFO         (L1_Si2190_Context *api);
#endif /* Si2190_PART_INFO_CMD */
#ifdef    Si2190_POWER_DOWN_CMD
unsigned char Si2190_L1_POWER_DOWN        (L1_Si2190_Context *api);
#endif /* Si2190_POWER_DOWN_CMD */
#ifdef    Si2190_POWER_DOWN_HW_CMD
unsigned char Si2190_L1_POWER_DOWN_HW     (L1_Si2190_Context *api,
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
#endif /* Si2190_POWER_DOWN_HW_CMD */
#ifdef    Si2190_POWER_UP_CMD
unsigned char Si2190_L1_POWER_UP          (L1_Si2190_Context *api,
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
#endif /* Si2190_POWER_UP_CMD */
#ifdef    Si2190_SET_PROPERTY_CMD
unsigned char Si2190_L1_SET_PROPERTY      (L1_Si2190_Context *api,
                                           unsigned char   reserved,
                                           unsigned int    prop,
                                           unsigned int    data);
#endif /* Si2190_SET_PROPERTY_CMD */
#ifdef    Si2190_SSVD_DEBUG_CONFIG_CMD
unsigned char Si2190_L1_SSVD_DEBUG_CONFIG (L1_Si2190_Context *api,
                                           unsigned char   cvbs_out,
                                           unsigned char   sif_out);
#endif /* Si2190_SSVD_DEBUG_CONFIG_CMD */
#ifdef    Si2190_SSVD_HDIV_CMD
unsigned char Si2190_L1_SSVD_HDIV         (L1_Si2190_Context *api,
                                           unsigned char   enable,
                                           unsigned int    st_ctrl0,
                                           unsigned int    ha_ctrl0);
#endif /* Si2190_SSVD_HDIV_CMD */
#ifdef    Si2190_SSVD_MULTI_REG_RD_CMD
unsigned char Si2190_L1_SSVD_MULTI_REG_RD (L1_Si2190_Context *api,
                                           unsigned char   reg_sel,
                                           unsigned char   num_regs);
#endif /* Si2190_SSVD_MULTI_REG_RD_CMD */
#ifdef    Si2190_SSVD_MULTI_REG_WR_CMD
unsigned char Si2190_L1_SSVD_MULTI_REG_WR (L1_Si2190_Context *api,
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
#endif /* Si2190_SSVD_MULTI_REG_WR_CMD */
#ifdef    Si2190_SSVD_POWER_DOWN_CMD
unsigned char Si2190_L1_SSVD_POWER_DOWN   (L1_Si2190_Context *api);
#endif /* Si2190_SSVD_POWER_DOWN_CMD */
#ifdef    Si2190_SSVD_POWER_UP_CMD
unsigned char Si2190_L1_SSVD_POWER_UP     (L1_Si2190_Context *api);
#endif /* Si2190_SSVD_POWER_UP_CMD */
#ifdef    Si2190_SSVD_REG_RD_CMD
unsigned char Si2190_L1_SSVD_REG_RD       (L1_Si2190_Context *api,
                                           unsigned char   reg_sel,
                                           unsigned char   ignored);
#endif /* Si2190_SSVD_REG_RD_CMD */
#ifdef    Si2190_SSVD_REG_WR_CMD
unsigned char Si2190_L1_SSVD_REG_WR       (L1_Si2190_Context *api,
                                           unsigned char   reg_sel,
                                           unsigned char   update,
                                           unsigned char   ignored,
                                           unsigned int    data);
#endif /* Si2190_SSVD_REG_WR_CMD */
#ifdef    Si2190_STANDBY_CMD
unsigned char Si2190_L1_STANDBY           (L1_Si2190_Context *api,
                                           unsigned char   type);
#endif /* Si2190_STANDBY_CMD */
#ifdef    Si2190_TUNER_STATUS_CMD
unsigned char Si2190_L1_TUNER_STATUS      (L1_Si2190_Context *api,
                                           unsigned char   intack);
#endif /* Si2190_TUNER_STATUS_CMD */
#ifdef    Si2190_TUNER_TUNE_FREQ_CMD
unsigned char Si2190_L1_TUNER_TUNE_FREQ   (L1_Si2190_Context *api,
                                           unsigned char   mode,
                                           unsigned long   freq);
#endif /* Si2190_TUNER_TUNE_FREQ_CMD */
/* _commands_prototypes_insertion_point */

#endif /* Si2190_COMMANDS_PROTOTYPES_H */











