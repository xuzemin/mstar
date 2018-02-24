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
   API functions prototypes used by commands and properties
   FILE: Si2158_Commands_Prototypes.h
   Supported IC : Si2158
   Compiled for ROM 33 firmware 2_1_build_9
   Revision: 0.1
   Date: March 20 2013
  (C) Copyright 2013, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#ifndef    Si2158_COMMANDS_PROTOTYPES_H
#define    Si2158_COMMANDS_PROTOTYPES_H

unsigned char Si2158_CurrentResponseStatus (L1_Si2158_Context *api, unsigned char ptDataBuffer);
unsigned char Si2158_pollForResetState     (L1_Si2158_Context *api);
unsigned char Si2158_pollForCTS            (L1_Si2158_Context *api);
unsigned char Si2158_pollForResponse       (L1_Si2158_Context *api, unsigned int nbBytes, unsigned char *pByteBuffer);
unsigned char Si2158_L1_SendCommand2       (L1_Si2158_Context *api, unsigned int cmd_code);
unsigned char Si2158_L1_SetProperty        (L1_Si2158_Context *api, unsigned int prop, int  data);
unsigned char Si2158_L1_GetProperty        (L1_Si2158_Context *api, unsigned int prop, int *data);
unsigned char Si2158_L1_SetProperty2       (L1_Si2158_Context *api, unsigned int prop_code);
unsigned char Si2158_L1_GetProperty2       (L1_Si2158_Context *api, unsigned int prop_code);

#ifdef    Si2158_GET_PROPERTY_STRING
unsigned char    Si2158_L1_GetPropertyString        (L1_Si2158_Context *api, unsigned int prop_code, const char *separator, char *msg);
#endif /* Si2158_GET_PROPERTY_STRING */

#ifdef    Si2158_GET_COMMAND_STRINGS
  unsigned char   Si2158_L1_GetCommandResponseString(L1_Si2158_Context *api, unsigned int cmd_code, const char *separator, char *msg);
#endif /* Si2158_GET_COMMAND_STRINGS */

/* _commands_prototypes_insertion_start */
#ifdef    Si2158_AGC_OVERRIDE_CMD
unsigned char Si2158_L1_AGC_OVERRIDE    (L1_Si2158_Context *api,
                                         unsigned char   force_max_gain,
                                         unsigned char   force_top_gain);
#endif /* Si2158_AGC_OVERRIDE_CMD */
#ifdef    Si2158_ATV_CW_TEST_CMD
unsigned char Si2158_L1_ATV_CW_TEST     (L1_Si2158_Context *api,
                                         unsigned char   pc_lock);
#endif /* Si2158_ATV_CW_TEST_CMD */
#ifdef    Si2158_ATV_RESTART_CMD
unsigned char Si2158_L1_ATV_RESTART     (L1_Si2158_Context *api);
#endif /* Si2158_ATV_RESTART_CMD */
#ifdef    Si2158_ATV_STATUS_CMD
unsigned char Si2158_L1_ATV_STATUS      (L1_Si2158_Context *api,
                                         unsigned char   intack);
#endif /* Si2158_ATV_STATUS_CMD */
#ifdef    Si2158_CONFIG_CLOCKS_CMD
unsigned char Si2158_L1_CONFIG_CLOCKS   (L1_Si2158_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   clock_mode,
                                         unsigned char   en_xout);
#endif /* Si2158_CONFIG_CLOCKS_CMD */
#ifdef    Si2158_CONFIG_PINS_CMD
unsigned char Si2158_L1_CONFIG_PINS     (L1_Si2158_Context *api,
                                         unsigned char   gpio1_mode,
                                         unsigned char   gpio1_read,
                                         unsigned char   gpio2_mode,
                                         unsigned char   gpio2_read,
                                         unsigned char   reserved1,
                                         unsigned char   reserved2,
                                         unsigned char   reserved3);
#endif /* Si2158_CONFIG_PINS_CMD */
#ifdef    Si2158_DTV_RESTART_CMD
unsigned char Si2158_L1_DTV_RESTART     (L1_Si2158_Context *api);
#endif /* Si2158_DTV_RESTART_CMD */
#ifdef    Si2158_DTV_STATUS_CMD
unsigned char Si2158_L1_DTV_STATUS      (L1_Si2158_Context *api,
                                         unsigned char   intack);
#endif /* Si2158_DTV_STATUS_CMD */
#ifdef    Si2158_EXIT_BOOTLOADER_CMD
unsigned char Si2158_L1_EXIT_BOOTLOADER (L1_Si2158_Context *api,
                                         unsigned char   func,
                                         unsigned char   ctsien);
#endif /* Si2158_EXIT_BOOTLOADER_CMD */
#ifdef    Si2158_FINE_TUNE_CMD
unsigned char Si2158_L1_FINE_TUNE       (L1_Si2158_Context *api,
                                         unsigned char   persistence,
                                         unsigned char   apply_to_lif,
                                                   int   offset_500hz);
#endif /* Si2158_FINE_TUNE_CMD */
#ifdef    Si2158_GET_PROPERTY_CMD
unsigned char Si2158_L1_GET_PROPERTY    (L1_Si2158_Context *api,
                                         unsigned char   reserved,
                                         unsigned int    prop);
#endif /* Si2158_GET_PROPERTY_CMD */
#ifdef    Si2158_GET_REV_CMD
unsigned char Si2158_L1_GET_REV         (L1_Si2158_Context *api);
#endif /* Si2158_GET_REV_CMD */
#ifdef    Si2158_PART_INFO_CMD
unsigned char Si2158_L1_PART_INFO       (L1_Si2158_Context *api);
#endif /* Si2158_PART_INFO_CMD */
#ifdef    Si2158_POWER_DOWN_CMD
unsigned char Si2158_L1_POWER_DOWN      (L1_Si2158_Context *api);
#endif /* Si2158_POWER_DOWN_CMD */
#ifdef    Si2158_POWER_DOWN_HW_CMD
unsigned char Si2158_L1_POWER_DOWN_HW   (L1_Si2158_Context *api,
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
#endif /* Si2158_POWER_DOWN_HW_CMD */
#ifdef    Si2158_POWER_UP_CMD
unsigned char Si2158_L1_POWER_UP        (L1_Si2158_Context *api,
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
#endif /* Si2158_POWER_UP_CMD */
#ifdef    Si2158_RAM_CRC_CMD
unsigned char Si2158_L1_RAM_CRC         (L1_Si2158_Context *api);
#endif /* Si2158_RAM_CRC_CMD */
#ifdef    Si2158_SET_PROPERTY_CMD
unsigned char Si2158_L1_SET_PROPERTY    (L1_Si2158_Context *api,
                                         unsigned char   reserved,
                                         unsigned int    prop,
                                         unsigned int    data);
#endif /* Si2158_SET_PROPERTY_CMD */
#ifdef    Si2158_STANDBY_CMD
unsigned char Si2158_L1_STANDBY         (L1_Si2158_Context *api,
                                         unsigned char   type);
#endif /* Si2158_STANDBY_CMD */
#ifdef    Si2158_TUNER_STATUS_CMD
unsigned char Si2158_L1_TUNER_STATUS    (L1_Si2158_Context *api,
                                         unsigned char   intack);
#endif /* Si2158_TUNER_STATUS_CMD */
#ifdef    Si2158_TUNER_TUNE_FREQ_CMD
unsigned char Si2158_L1_TUNER_TUNE_FREQ (L1_Si2158_Context *api,
                                         unsigned char   mode,
                                         unsigned long   freq);
#endif /* Si2158_TUNER_TUNE_FREQ_CMD */
/* _commands_prototypes_insertion_point */

#endif /* Si2158_COMMANDS_PROTOTYPES_H */











