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
   API commands definitions
   FILE: Si2158_L1_Commands.c
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
  Si2158_CurrentResponseStatus function
  Use:        status checking function
              Used to fill the Si2158_COMMON_REPLY_struct members with the ptDataBuffer byte's bits
  Comments:   The status byte definition being identical for all commands,
              using this function to fill the status structure helps reducing the code size
  Parameter: ptDataBuffer  a single byte received when reading a command's response (the first byte)
  Returns:   0 if the err bit (bit 6) is unset, 1 otherwise
 ***********************************************************************************************************************/
unsigned char Si2158_CurrentResponseStatus (L1_Si2158_Context *api, unsigned char ptDataBuffer)
{
/* _status_code_insertion_start */
    api->status->tunint = ((ptDataBuffer >> 0 ) & 0x01);
    api->status->atvint = ((ptDataBuffer >> 1 ) & 0x01);
    api->status->dtvint = ((ptDataBuffer >> 2 ) & 0x01);
    api->status->err    = ((ptDataBuffer >> 6 ) & 0x01);
    api->status->cts    = ((ptDataBuffer >> 7 ) & 0x01);
/* _status_code_insertion_point */
  return (api->status->err ? ERROR_Si2158_ERR : NO_Si2158_ERROR);
}
/***********************************************************************************************************************
  Si2158_pollForResetState function
  Use:        ResetState checking function
              Used to check the status byte for the reset code (0xFE).
  Comments:   Only required for the Si2158_L1_POWER_DOWN_HW Command

  Returns:   0 if the Status byte is = 0xFE, nonzero otherwise
 ***********************************************************************************************************************/
unsigned char Si2158_pollForResetState (L1_Si2158_Context *api)
{
  unsigned char rspByteBuffer[1] = {0};
    unsigned int loop_count;
 for (loop_count=0; loop_count < 100; loop_count++)
 { /* wait a maximum of 1000ms */
    if (L0_ReadCommandBytes(api->i2c, 1, rspByteBuffer) != 1)
    {
      SiTRACE("Si2158_pollForResetState ERROR reading byte 0!\n");
      return ERROR_Si2158_POLLING_CTS;
    }
    /* return OK if status=0xFE set */
   // printf("rspByteBuffer==%x\n",rspByteBuffer[0]);
    if (rspByteBuffer[0] == 0xFE)
    {
      return NO_Si2158_ERROR;
    }
        system_wait(5);
  }

  printf("Si2158_pollForResetState ERROR status Timeout!\n");
  return ERROR_Si2158_CTS_TIMEOUT;
}

/***********************************************************************************************************************
  Si2158_pollForCTS function
  Use:        CTS checking function
              Used to check the CTS bit until it is set before sending the next command
  Comments:   The status byte definition being identical for all commands,
              using this function to fill the status structure helps reducing the code size
              max timeout = 1000 ms

  Returns:   1 if the CTS bit is set, 0 otherwise
 ***********************************************************************************************************************/
unsigned char Si2158_pollForCTS (L1_Si2158_Context *p_api)
{
    unsigned char rspByteBuffer[1] = {0};
    unsigned int loop_count;
    for (loop_count=0; loop_count < 100; loop_count++)
    { /* wait a maximum of 100ms */
        if (L0_ReadCommandBytes(p_api->i2c, 1, rspByteBuffer) != 1)
        {
          SiTRACE("Si2158_pollForCTS ERROR reading byte 0!\n");
          return ERROR_Si2158_POLLING_CTS;
        }
    /* return OK if CTS set */
        if (rspByteBuffer[0] & 0x80)
        {
            return NO_Si2158_ERROR;
        }
        system_wait(5);
    }

    SiTRACE("Si2158_pollForCTS ERROR CTS Timeout!\n");
    return ERROR_Si2158_CTS_TIMEOUT;
}

/***********************************************************************************************************************
  Si2158_pollForResponse function
  Use:        command response retrieval function
              Used to retrieve the command response in the provided buffer
  Comments:   The status byte definition being identical for all commands,
              using this function to fill the status structure helps reducing the code size
              max timeout = 1000 ms

  Parameter:  nbBytes          the number of response bytes to read
  Parameter:  pByteBuffer      a buffer into which bytes will be stored
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/
unsigned char Si2158_pollForResponse (L1_Si2158_Context *p_api, unsigned int nbBytes, unsigned char *pByteBuffer)
{
    unsigned int loop_count;
    for (loop_count=0; loop_count < 100; loop_count++)
    { /* wait a maximum of 100ms */
        if ((unsigned int)L0_ReadCommandBytes(p_api->i2c, nbBytes, pByteBuffer) != nbBytes)
        {
            SiTRACE("Si2158_pollForResponse ERROR reading byte 0!\n");
            return ERROR_Si2158_POLLING_RESPONSE;
        }
        /* return response err flag if CTS set */
        if (pByteBuffer[0] & 0x80)
        {
            return Si2158_CurrentResponseStatus(p_api, pByteBuffer[0]);
        }
        system_wait(5);
    }

  SiTRACE("Si2158_pollForResponse ERROR CTS Timeout!\n");
  return ERROR_Si2158_CTS_TIMEOUT;
}

/* _commands_insertion_start */
#ifdef    Si2158_AGC_OVERRIDE_CMD
 /*---------------------------------------------------*/
/* Si2158_AGC_OVERRIDE COMMAND                     */
/*---------------------------------------------------*/
unsigned char Si2158_L1_AGC_OVERRIDE    (L1_Si2158_Context *api,
                                         unsigned char   force_max_gain,
                                         unsigned char   force_top_gain)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[1];
    api->rsp->agc_override.STATUS = api->status;

    SiTRACE("Si2158 AGC_OVERRIDE ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((force_max_gain > Si2158_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FORCE_MAX_GAIN %d ", force_max_gain );
    if ((force_top_gain > Si2158_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FORCE_TOP_GAIN %d ", force_top_gain );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2158_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2158_AGC_OVERRIDE_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( force_max_gain & Si2158_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_MASK ) << Si2158_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_LSB|
                                         ( force_top_gain & Si2158_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_MASK ) << Si2158_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing AGC_OVERRIDE bytes!\n");
      return ERROR_Si2158_SENDING_COMMAND;
    }

    error_code = Si2158_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling AGC_OVERRIDE response\n");
      return error_code;
    }


    return NO_Si2158_ERROR;
}
#endif /* Si2158_AGC_OVERRIDE_CMD */
#ifdef    Si2158_ATV_CW_TEST_CMD
 /*---------------------------------------------------*/
/* Si2158_ATV_CW_TEST COMMAND                      */
/*---------------------------------------------------*/
unsigned char Si2158_L1_ATV_CW_TEST     (L1_Si2158_Context *api,
                                         unsigned char   pc_lock)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[1];
    api->rsp->atv_cw_test.STATUS = api->status;

    SiTRACE("Si2158 ATV_CW_TEST ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((pc_lock > Si2158_ATV_CW_TEST_CMD_PC_LOCK_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("PC_LOCK %d ", pc_lock );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2158_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2158_ATV_CW_TEST_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( pc_lock & Si2158_ATV_CW_TEST_CMD_PC_LOCK_MASK ) << Si2158_ATV_CW_TEST_CMD_PC_LOCK_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing ATV_CW_TEST bytes!\n");
      return ERROR_Si2158_SENDING_COMMAND;
    }

    error_code = Si2158_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling ATV_CW_TEST response\n");
      return error_code;
    }


    return NO_Si2158_ERROR;
}
#endif /* Si2158_ATV_CW_TEST_CMD */
#ifdef    Si2158_ATV_RESTART_CMD
 /*---------------------------------------------------*/
/* Si2158_ATV_RESTART COMMAND                      */
/*---------------------------------------------------*/
unsigned char Si2158_L1_ATV_RESTART     (L1_Si2158_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[1];
    api->rsp->atv_restart.STATUS = api->status;

    SiTRACE("Si2158 ATV_RESTART ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2158_ATV_RESTART_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing ATV_RESTART bytes!\n");
      return ERROR_Si2158_SENDING_COMMAND;
    }

    error_code = Si2158_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling ATV_RESTART response\n");
      return error_code;
    }


    return NO_Si2158_ERROR;
}
#endif /* Si2158_ATV_RESTART_CMD */
#ifdef    Si2158_ATV_STATUS_CMD
 /*---------------------------------------------------*/
/* Si2158_ATV_STATUS COMMAND                       */
/*---------------------------------------------------*/
unsigned char Si2158_L1_ATV_STATUS      (L1_Si2158_Context *api,
                                         unsigned char   intack)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    api->rsp->atv_status.STATUS = api->status;

    SiTRACE("Si2158 ATV_STATUS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((intack > Si2158_ATV_STATUS_CMD_INTACK_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("INTACK %d ", intack );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2158_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2158_ATV_STATUS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( intack & Si2158_ATV_STATUS_CMD_INTACK_MASK ) << Si2158_ATV_STATUS_CMD_INTACK_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing ATV_STATUS bytes!\n");
      return ERROR_Si2158_SENDING_COMMAND;
    }

    error_code = Si2158_pollForResponse(api, 9, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling ATV_STATUS response\n");
      return error_code;
    }

    api->rsp->atv_status.chlint    =   (( ( (rspByteBuffer[1]  )) >> Si2158_ATV_STATUS_RESPONSE_CHLINT_LSB    ) & Si2158_ATV_STATUS_RESPONSE_CHLINT_MASK    );
    api->rsp->atv_status.pclint    =   (( ( (rspByteBuffer[1]  )) >> Si2158_ATV_STATUS_RESPONSE_PCLINT_LSB    ) & Si2158_ATV_STATUS_RESPONSE_PCLINT_MASK    );
    api->rsp->atv_status.chl       =   (( ( (rspByteBuffer[2]  )) >> Si2158_ATV_STATUS_RESPONSE_CHL_LSB       ) & Si2158_ATV_STATUS_RESPONSE_CHL_MASK       );
    api->rsp->atv_status.pcl       =   (( ( (rspByteBuffer[2]  )) >> Si2158_ATV_STATUS_RESPONSE_PCL_LSB       ) & Si2158_ATV_STATUS_RESPONSE_PCL_MASK       );
    api->rsp->atv_status.afc_freq  = (((( ( (rspByteBuffer[4]  ) | (rspByteBuffer[5]  << 8 )) >> Si2158_ATV_STATUS_RESPONSE_AFC_FREQ_LSB  ) & Si2158_ATV_STATUS_RESPONSE_AFC_FREQ_MASK) <<Si2158_ATV_STATUS_RESPONSE_AFC_FREQ_SHIFT ) >>Si2158_ATV_STATUS_RESPONSE_AFC_FREQ_SHIFT  );
    api->rsp->atv_status.video_sys =   (( ( (rspByteBuffer[8]  )) >> Si2158_ATV_STATUS_RESPONSE_VIDEO_SYS_LSB ) & Si2158_ATV_STATUS_RESPONSE_VIDEO_SYS_MASK );
    api->rsp->atv_status.color     =   (( ( (rspByteBuffer[8]  )) >> Si2158_ATV_STATUS_RESPONSE_COLOR_LSB     ) & Si2158_ATV_STATUS_RESPONSE_COLOR_MASK     );

    return NO_Si2158_ERROR;
}
#endif /* Si2158_ATV_STATUS_CMD */
#ifdef    Si2158_CONFIG_CLOCKS_CMD
 /*---------------------------------------------------*/
/* Si2158_CONFIG_CLOCKS COMMAND                    */
/*---------------------------------------------------*/
unsigned char Si2158_L1_CONFIG_CLOCKS   (L1_Si2158_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   clock_mode,
                                         unsigned char   en_xout)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[3];
    unsigned char rspByteBuffer[1];
    api->rsp->config_clocks.STATUS = api->status;

    SiTRACE("Si2158 CONFIG_CLOCKS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode    > Si2158_CONFIG_CLOCKS_CMD_SUBCODE_MAX   ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "   , subcode    );
    if ((clock_mode > Si2158_CONFIG_CLOCKS_CMD_CLOCK_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CLOCK_MODE %d ", clock_mode );
    if ((en_xout    > Si2158_CONFIG_CLOCKS_CMD_EN_XOUT_MAX   ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("EN_XOUT %d "   , en_xout    );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2158_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2158_CONFIG_CLOCKS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode    & Si2158_CONFIG_CLOCKS_CMD_SUBCODE_MASK    ) << Si2158_CONFIG_CLOCKS_CMD_SUBCODE_LSB   );
    cmdByteBuffer[2] = (unsigned char) ( ( clock_mode & Si2158_CONFIG_CLOCKS_CMD_CLOCK_MODE_MASK ) << Si2158_CONFIG_CLOCKS_CMD_CLOCK_MODE_LSB|
                                         ( en_xout    & Si2158_CONFIG_CLOCKS_CMD_EN_XOUT_MASK    ) << Si2158_CONFIG_CLOCKS_CMD_EN_XOUT_LSB   );

    if (L0_WriteCommandBytes(api->i2c, 3, cmdByteBuffer) != 3) {
      SiTRACE("Error writing CONFIG_CLOCKS bytes!\n");
      return ERROR_Si2158_SENDING_COMMAND;
    }

    error_code = Si2158_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling CONFIG_CLOCKS response\n");
      return error_code;
    }


    return NO_Si2158_ERROR;
}
#endif /* Si2158_CONFIG_CLOCKS_CMD */
#ifdef    Si2158_CONFIG_PINS_CMD
 /*---------------------------------------------------*/
/* Si2158_CONFIG_PINS COMMAND                      */
/*---------------------------------------------------*/
unsigned char Si2158_L1_CONFIG_PINS     (L1_Si2158_Context *api,
                                         unsigned char   gpio1_mode,
                                         unsigned char   gpio1_read,
                                         unsigned char   gpio2_mode,
                                         unsigned char   gpio2_read,
                                         unsigned char   reserved1,
                                         unsigned char   reserved2,
                                         unsigned char   reserved3)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[6];
    unsigned char rspByteBuffer[6] = {0, 0, 0, 0, 0, 0};
    api->rsp->config_pins.STATUS = api->status;

    SiTRACE("Si2158 CONFIG_PINS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((gpio1_mode > Si2158_CONFIG_PINS_CMD_GPIO1_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO1_MODE %d ", gpio1_mode );
    if ((gpio1_read > Si2158_CONFIG_PINS_CMD_GPIO1_READ_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO1_READ %d ", gpio1_read );
    if ((gpio2_mode > Si2158_CONFIG_PINS_CMD_GPIO2_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO2_MODE %d ", gpio2_mode );
    if ((gpio2_read > Si2158_CONFIG_PINS_CMD_GPIO2_READ_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO2_READ %d ", gpio2_read );
    if ((reserved1  > Si2158_CONFIG_PINS_CMD_RESERVED1_MAX )  || (reserved1  < Si2158_CONFIG_PINS_CMD_RESERVED1_MIN ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED1 %d " , reserved1  );
    if ((reserved2  > Si2158_CONFIG_PINS_CMD_RESERVED2_MAX )  || (reserved2  < Si2158_CONFIG_PINS_CMD_RESERVED2_MIN ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED2 %d " , reserved2  );
    if ((reserved3  > Si2158_CONFIG_PINS_CMD_RESERVED3_MAX )  || (reserved3  < Si2158_CONFIG_PINS_CMD_RESERVED3_MIN ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED3 %d " , reserved3  );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2158_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2158_CONFIG_PINS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( gpio1_mode & Si2158_CONFIG_PINS_CMD_GPIO1_MODE_MASK ) << Si2158_CONFIG_PINS_CMD_GPIO1_MODE_LSB|
                                         ( gpio1_read & Si2158_CONFIG_PINS_CMD_GPIO1_READ_MASK ) << Si2158_CONFIG_PINS_CMD_GPIO1_READ_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( gpio2_mode & Si2158_CONFIG_PINS_CMD_GPIO2_MODE_MASK ) << Si2158_CONFIG_PINS_CMD_GPIO2_MODE_LSB|
                                         ( gpio2_read & Si2158_CONFIG_PINS_CMD_GPIO2_READ_MASK ) << Si2158_CONFIG_PINS_CMD_GPIO2_READ_LSB);
    cmdByteBuffer[3] = (unsigned char) ( ( reserved1  & Si2158_CONFIG_PINS_CMD_RESERVED1_MASK  ) << Si2158_CONFIG_PINS_CMD_RESERVED1_LSB );
    cmdByteBuffer[4] = (unsigned char) ( ( reserved2  & Si2158_CONFIG_PINS_CMD_RESERVED2_MASK  ) << Si2158_CONFIG_PINS_CMD_RESERVED2_LSB );
    cmdByteBuffer[5] = (unsigned char) ( ( reserved3  & Si2158_CONFIG_PINS_CMD_RESERVED3_MASK  ) << Si2158_CONFIG_PINS_CMD_RESERVED3_LSB );

    if (L0_WriteCommandBytes(api->i2c, 6, cmdByteBuffer) != 6) {
      SiTRACE("Error writing CONFIG_PINS bytes!\n");
      return ERROR_Si2158_SENDING_COMMAND;
    }

    error_code = Si2158_pollForResponse(api, 6, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling CONFIG_PINS response\n");
      return error_code;
    }

    api->rsp->config_pins.gpio1_mode  =   (( ( (rspByteBuffer[1]  )) >> Si2158_CONFIG_PINS_RESPONSE_GPIO1_MODE_LSB  ) & Si2158_CONFIG_PINS_RESPONSE_GPIO1_MODE_MASK  );
    api->rsp->config_pins.gpio1_state =   (( ( (rspByteBuffer[1]  )) >> Si2158_CONFIG_PINS_RESPONSE_GPIO1_STATE_LSB ) & Si2158_CONFIG_PINS_RESPONSE_GPIO1_STATE_MASK );
    api->rsp->config_pins.gpio2_mode  =   (( ( (rspByteBuffer[2]  )) >> Si2158_CONFIG_PINS_RESPONSE_GPIO2_MODE_LSB  ) & Si2158_CONFIG_PINS_RESPONSE_GPIO2_MODE_MASK  );
    api->rsp->config_pins.gpio2_state =   (( ( (rspByteBuffer[2]  )) >> Si2158_CONFIG_PINS_RESPONSE_GPIO2_STATE_LSB ) & Si2158_CONFIG_PINS_RESPONSE_GPIO2_STATE_MASK );
    api->rsp->config_pins.reserved1   =   (( ( (rspByteBuffer[3]  )) >> Si2158_CONFIG_PINS_RESPONSE_RESERVED1_LSB   ) & Si2158_CONFIG_PINS_RESPONSE_RESERVED1_MASK   );
    api->rsp->config_pins.reserved2   =   (( ( (rspByteBuffer[4]  )) >> Si2158_CONFIG_PINS_RESPONSE_RESERVED2_LSB   ) & Si2158_CONFIG_PINS_RESPONSE_RESERVED2_MASK   );
    api->rsp->config_pins.reserved3   =   (( ( (rspByteBuffer[5]  )) >> Si2158_CONFIG_PINS_RESPONSE_RESERVED3_LSB   ) & Si2158_CONFIG_PINS_RESPONSE_RESERVED3_MASK   );

    return NO_Si2158_ERROR;
}
#endif /* Si2158_CONFIG_PINS_CMD */
#ifdef    Si2158_DTV_RESTART_CMD
 /*---------------------------------------------------*/
/* Si2158_DTV_RESTART COMMAND                      */
/*---------------------------------------------------*/
unsigned char Si2158_L1_DTV_RESTART     (L1_Si2158_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[1];
    api->rsp->dtv_restart.STATUS = api->status;

    SiTRACE("Si2158 DTV_RESTART ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2158_DTV_RESTART_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing DTV_RESTART bytes!\n");
      return ERROR_Si2158_SENDING_COMMAND;
    }

    error_code = Si2158_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DTV_RESTART response\n");
      return error_code;
    }


    return NO_Si2158_ERROR;
}
#endif /* Si2158_DTV_RESTART_CMD */
#ifdef    Si2158_DTV_STATUS_CMD
 /*---------------------------------------------------*/
/* Si2158_DTV_STATUS COMMAND                       */
/*---------------------------------------------------*/
unsigned char Si2158_L1_DTV_STATUS      (L1_Si2158_Context *api,
                                         unsigned char   intack)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[4] = {0, 0, 0, 0};
    api->rsp->dtv_status.STATUS = api->status;

    SiTRACE("Si2158 DTV_STATUS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((intack > Si2158_DTV_STATUS_CMD_INTACK_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("INTACK %d ", intack );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2158_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2158_DTV_STATUS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( intack & Si2158_DTV_STATUS_CMD_INTACK_MASK ) << Si2158_DTV_STATUS_CMD_INTACK_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing DTV_STATUS bytes!\n");
      return ERROR_Si2158_SENDING_COMMAND;
    }

    error_code = Si2158_pollForResponse(api, 4, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DTV_STATUS response\n");
      return error_code;
    }

    api->rsp->dtv_status.chlint     =   (( ( (rspByteBuffer[1]  )) >> Si2158_DTV_STATUS_RESPONSE_CHLINT_LSB     ) & Si2158_DTV_STATUS_RESPONSE_CHLINT_MASK     );
    api->rsp->dtv_status.chl        =   (( ( (rspByteBuffer[2]  )) >> Si2158_DTV_STATUS_RESPONSE_CHL_LSB        ) & Si2158_DTV_STATUS_RESPONSE_CHL_MASK        );
    api->rsp->dtv_status.bw         =   (( ( (rspByteBuffer[3]  )) >> Si2158_DTV_STATUS_RESPONSE_BW_LSB         ) & Si2158_DTV_STATUS_RESPONSE_BW_MASK         );
    api->rsp->dtv_status.modulation =   (( ( (rspByteBuffer[3]  )) >> Si2158_DTV_STATUS_RESPONSE_MODULATION_LSB ) & Si2158_DTV_STATUS_RESPONSE_MODULATION_MASK );

    return NO_Si2158_ERROR;
}
#endif /* Si2158_DTV_STATUS_CMD */
#ifdef    Si2158_EXIT_BOOTLOADER_CMD
 /*---------------------------------------------------*/
/* Si2158_EXIT_BOOTLOADER COMMAND                  */
/*---------------------------------------------------*/
unsigned char Si2158_L1_EXIT_BOOTLOADER (L1_Si2158_Context *api,
                                         unsigned char   func,
                                         unsigned char   ctsien)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[1];
    api->rsp->exit_bootloader.STATUS = api->status;

    SiTRACE("Si2158 EXIT_BOOTLOADER ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((func   > Si2158_EXIT_BOOTLOADER_CMD_FUNC_MAX  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FUNC %d "  , func   );
    if ((ctsien > Si2158_EXIT_BOOTLOADER_CMD_CTSIEN_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CTSIEN %d ", ctsien );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2158_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2158_EXIT_BOOTLOADER_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( func   & Si2158_EXIT_BOOTLOADER_CMD_FUNC_MASK   ) << Si2158_EXIT_BOOTLOADER_CMD_FUNC_LSB  |
                                         ( ctsien & Si2158_EXIT_BOOTLOADER_CMD_CTSIEN_MASK ) << Si2158_EXIT_BOOTLOADER_CMD_CTSIEN_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing EXIT_BOOTLOADER bytes!\n");
      return ERROR_Si2158_SENDING_COMMAND;
    }

    error_code = Si2158_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling EXIT_BOOTLOADER response\n");
      return error_code;
    }


    return NO_Si2158_ERROR;
}
#endif /* Si2158_EXIT_BOOTLOADER_CMD */
#ifdef    Si2158_FINE_TUNE_CMD
 /*---------------------------------------------------*/
/* Si2158_FINE_TUNE COMMAND                        */
/*---------------------------------------------------*/
unsigned char Si2158_L1_FINE_TUNE       (L1_Si2158_Context *api,
                                         unsigned char   persistence,
                                         unsigned char   apply_to_lif,
                                                   int   offset_500hz)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[4];
    unsigned char rspByteBuffer[1];
    api->rsp->fine_tune.STATUS = api->status;

    SiTRACE("Si2158 FINE_TUNE ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((persistence  > Si2158_FINE_TUNE_CMD_PERSISTENCE_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("PERSISTENCE %d " , persistence  );
    if ((apply_to_lif > Si2158_FINE_TUNE_CMD_APPLY_TO_LIF_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("APPLY_TO_LIF %d ", apply_to_lif );
    if ((offset_500hz > Si2158_FINE_TUNE_CMD_OFFSET_500HZ_MAX)  || (offset_500hz < Si2158_FINE_TUNE_CMD_OFFSET_500HZ_MIN) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("OFFSET_500HZ %d ", offset_500hz );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2158_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2158_FINE_TUNE_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( persistence  & Si2158_FINE_TUNE_CMD_PERSISTENCE_MASK  ) << Si2158_FINE_TUNE_CMD_PERSISTENCE_LSB |
                                         ( apply_to_lif & Si2158_FINE_TUNE_CMD_APPLY_TO_LIF_MASK ) << Si2158_FINE_TUNE_CMD_APPLY_TO_LIF_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( offset_500hz & Si2158_FINE_TUNE_CMD_OFFSET_500HZ_MASK ) << Si2158_FINE_TUNE_CMD_OFFSET_500HZ_LSB);
    cmdByteBuffer[3] = (unsigned char) ((( offset_500hz & Si2158_FINE_TUNE_CMD_OFFSET_500HZ_MASK ) << Si2158_FINE_TUNE_CMD_OFFSET_500HZ_LSB)>>8);

    if (L0_WriteCommandBytes(api->i2c, 4, cmdByteBuffer) != 4) {
      SiTRACE("Error writing FINE_TUNE bytes!\n");
      return ERROR_Si2158_SENDING_COMMAND;
    }

    error_code = Si2158_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling FINE_TUNE response\n");
      return error_code;
    }


    return NO_Si2158_ERROR;
}
#endif /* Si2158_FINE_TUNE_CMD */
#ifdef    Si2158_GET_PROPERTY_CMD
 /*---------------------------------------------------*/
/* Si2158_GET_PROPERTY COMMAND                     */
/*---------------------------------------------------*/
unsigned char Si2158_L1_GET_PROPERTY    (L1_Si2158_Context *api,
                                         unsigned char   reserved,
                                         unsigned int    prop)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[4];
    unsigned char rspByteBuffer[4] = {0, 0, 0, 0};
    api->rsp->get_property.STATUS = api->status;

    SiTRACE("Si2158 GET_PROPERTY ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((reserved > Si2158_GET_PROPERTY_CMD_RESERVED_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED %d ", reserved );
    SiTRACE("PROP %d "    , prop     );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2158_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2158_GET_PROPERTY_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( reserved & Si2158_GET_PROPERTY_CMD_RESERVED_MASK ) << Si2158_GET_PROPERTY_CMD_RESERVED_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( prop     & Si2158_GET_PROPERTY_CMD_PROP_MASK     ) << Si2158_GET_PROPERTY_CMD_PROP_LSB    );
    cmdByteBuffer[3] = (unsigned char) ((( prop     & Si2158_GET_PROPERTY_CMD_PROP_MASK     ) << Si2158_GET_PROPERTY_CMD_PROP_LSB    )>>8);

    if (L0_WriteCommandBytes(api->i2c, 4, cmdByteBuffer) != 4) {
      SiTRACE("Error writing GET_PROPERTY bytes!\n");
      return ERROR_Si2158_SENDING_COMMAND;
    }

    error_code = Si2158_pollForResponse(api, 4, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling GET_PROPERTY response\n");
      return error_code;
    }

    api->rsp->get_property.reserved =   (( ( (rspByteBuffer[1]  )) >> Si2158_GET_PROPERTY_RESPONSE_RESERVED_LSB ) & Si2158_GET_PROPERTY_RESPONSE_RESERVED_MASK );
    api->rsp->get_property.data     =   (( ( (rspByteBuffer[2]  ) | (rspByteBuffer[3]  << 8 )) >> Si2158_GET_PROPERTY_RESPONSE_DATA_LSB     ) & Si2158_GET_PROPERTY_RESPONSE_DATA_MASK     );

    return NO_Si2158_ERROR;
}
#endif /* Si2158_GET_PROPERTY_CMD */
#ifdef    Si2158_GET_REV_CMD
 /*---------------------------------------------------*/
/* Si2158_GET_REV COMMAND                          */
/*---------------------------------------------------*/
unsigned char Si2158_L1_GET_REV         (L1_Si2158_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[10]  = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    api->rsp->get_rev.STATUS = api->status;

    SiTRACE("Si2158 GET_REV ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2158_GET_REV_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing GET_REV bytes!\n");
      return ERROR_Si2158_SENDING_COMMAND;
    }

    error_code = Si2158_pollForResponse(api, 10, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling GET_REV response\n");
      return error_code;
    }

    api->rsp->get_rev.pn       =   (( ( (rspByteBuffer[1]  )) >> Si2158_GET_REV_RESPONSE_PN_LSB       ) & Si2158_GET_REV_RESPONSE_PN_MASK       );
    api->rsp->get_rev.fwmajor  =   (( ( (rspByteBuffer[2]  )) >> Si2158_GET_REV_RESPONSE_FWMAJOR_LSB  ) & Si2158_GET_REV_RESPONSE_FWMAJOR_MASK  );
    api->rsp->get_rev.fwminor  =   (( ( (rspByteBuffer[3]  )) >> Si2158_GET_REV_RESPONSE_FWMINOR_LSB  ) & Si2158_GET_REV_RESPONSE_FWMINOR_MASK  );
    api->rsp->get_rev.patch    =   (( ( (rspByteBuffer[4]  ) | (rspByteBuffer[5]  << 8 )) >> Si2158_GET_REV_RESPONSE_PATCH_LSB    ) & Si2158_GET_REV_RESPONSE_PATCH_MASK    );
    api->rsp->get_rev.cmpmajor =   (( ( (rspByteBuffer[6]  )) >> Si2158_GET_REV_RESPONSE_CMPMAJOR_LSB ) & Si2158_GET_REV_RESPONSE_CMPMAJOR_MASK );
    api->rsp->get_rev.cmpminor =   (( ( (rspByteBuffer[7]  )) >> Si2158_GET_REV_RESPONSE_CMPMINOR_LSB ) & Si2158_GET_REV_RESPONSE_CMPMINOR_MASK );
    api->rsp->get_rev.cmpbuild =   (( ( (rspByteBuffer[8]  )) >> Si2158_GET_REV_RESPONSE_CMPBUILD_LSB ) & Si2158_GET_REV_RESPONSE_CMPBUILD_MASK );
    api->rsp->get_rev.chiprev  =   (( ( (rspByteBuffer[9]  )) >> Si2158_GET_REV_RESPONSE_CHIPREV_LSB  ) & Si2158_GET_REV_RESPONSE_CHIPREV_MASK  );

    return NO_Si2158_ERROR;
}
#endif /* Si2158_GET_REV_CMD */
#ifdef    Si2158_PART_INFO_CMD
 /*---------------------------------------------------*/
/* Si2158_PART_INFO COMMAND                        */
/*---------------------------------------------------*/
unsigned char Si2158_L1_PART_INFO       (L1_Si2158_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    api->rsp->part_info.STATUS = api->status;

    SiTRACE("Si2158 PART_INFO ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2158_PART_INFO_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing PART_INFO bytes!\n");
      return ERROR_Si2158_SENDING_COMMAND;
    }

    error_code = Si2158_pollForResponse(api, 13, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling PART_INFO response\n");
      return error_code;
    }

    api->rsp->part_info.chiprev  =   (( ( (rspByteBuffer[1]  )) >> Si2158_PART_INFO_RESPONSE_CHIPREV_LSB  ) & Si2158_PART_INFO_RESPONSE_CHIPREV_MASK  );
    api->rsp->part_info.part     =   (( ( (rspByteBuffer[2]  )) >> Si2158_PART_INFO_RESPONSE_PART_LSB     ) & Si2158_PART_INFO_RESPONSE_PART_MASK     );
    api->rsp->part_info.pmajor   =   (( ( (rspByteBuffer[3]  )) >> Si2158_PART_INFO_RESPONSE_PMAJOR_LSB   ) & Si2158_PART_INFO_RESPONSE_PMAJOR_MASK   );
    api->rsp->part_info.pminor   =   (( ( (rspByteBuffer[4]  )) >> Si2158_PART_INFO_RESPONSE_PMINOR_LSB   ) & Si2158_PART_INFO_RESPONSE_PMINOR_MASK   );
    api->rsp->part_info.pbuild   =   (( ( (rspByteBuffer[5]  )) >> Si2158_PART_INFO_RESPONSE_PBUILD_LSB   ) & Si2158_PART_INFO_RESPONSE_PBUILD_MASK   );
    api->rsp->part_info.reserved =   (( ( (rspByteBuffer[6]  ) | (rspByteBuffer[7]  << 8 )) >> Si2158_PART_INFO_RESPONSE_RESERVED_LSB ) & Si2158_PART_INFO_RESPONSE_RESERVED_MASK );
    api->rsp->part_info.serial   =   (( ( (rspByteBuffer[8]  ) | (rspByteBuffer[9]  << 8 ) | (rspByteBuffer[10] << 16 ) | (rspByteBuffer[11] << 24 )) >> Si2158_PART_INFO_RESPONSE_SERIAL_LSB   ) & Si2158_PART_INFO_RESPONSE_SERIAL_MASK   );
    api->rsp->part_info.romid    =   (( ( (rspByteBuffer[12] )) >> Si2158_PART_INFO_RESPONSE_ROMID_LSB    ) & Si2158_PART_INFO_RESPONSE_ROMID_MASK    );

    return NO_Si2158_ERROR;
}
#endif /* Si2158_PART_INFO_CMD */
#ifdef    Si2158_POWER_DOWN_CMD
 /*---------------------------------------------------*/
/* Si2158_POWER_DOWN COMMAND                       */
/*---------------------------------------------------*/
unsigned char Si2158_L1_POWER_DOWN      (L1_Si2158_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[1];
    api->rsp->power_down.STATUS = api->status;

    SiTRACE("Si2158 POWER_DOWN ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2158_POWER_DOWN_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing POWER_DOWN bytes!\n");
      return ERROR_Si2158_SENDING_COMMAND;
    }

    error_code = Si2158_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling POWER_DOWN response\n");
      return error_code;
    }


    return NO_Si2158_ERROR;
}
#endif /* Si2158_POWER_DOWN_CMD */

#ifdef    Si2158_POWER_DOWN_HW_CMD
/*---------------------------------------------------*/
/* Si2158_POWER_DOWN_HW COMMAND                    */
/*---------------------------------------------------*/
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
                                         unsigned char   reserved8)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[10];

    api->rsp->power_down_hw.STATUS = api->status;

    SiTRACE("Si2158 POWER_DOWN_HW ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode   > Si2158_POWER_DOWN_HW_CMD_SUBCODE_MAX  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "  , subcode   );
    if ((pd_xo_osc > Si2158_POWER_DOWN_HW_CMD_PD_XO_OSC_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("PD_XO_OSC %d ", pd_xo_osc );
    if ((reserved1 > Si2158_POWER_DOWN_HW_CMD_RESERVED1_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED1 %d ", reserved1 );
    if ((en_xout   > Si2158_POWER_DOWN_HW_CMD_EN_XOUT_MAX  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("EN_XOUT %d "  , en_xout   );
    if ((reserved2 > Si2158_POWER_DOWN_HW_CMD_RESERVED2_MAX)  || (reserved2 < Si2158_POWER_DOWN_HW_CMD_RESERVED2_MIN) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED2 %d ", reserved2 );
    if ((pd_ldo    > Si2158_POWER_DOWN_HW_CMD_PD_LDO_MAX   ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("PD_LDO %d "   , pd_ldo    );
    if ((reserved3 > Si2158_POWER_DOWN_HW_CMD_RESERVED3_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED3 %d ", reserved3 );
    if ((reserved4 > Si2158_POWER_DOWN_HW_CMD_RESERVED4_MAX)  || (reserved4 < Si2158_POWER_DOWN_HW_CMD_RESERVED4_MIN) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED4 %d ", reserved4 );
    if ((reserved5 > Si2158_POWER_DOWN_HW_CMD_RESERVED5_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED5 %d ", reserved5 );
    if ((reserved6 > Si2158_POWER_DOWN_HW_CMD_RESERVED6_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED6 %d ", reserved6 );
    if ((reserved7 > Si2158_POWER_DOWN_HW_CMD_RESERVED7_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED7 %d ", reserved7 );
    if ((reserved8 > Si2158_POWER_DOWN_HW_CMD_RESERVED8_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED8 %d ", reserved8 );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2158_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2158_POWER_DOWN_HW_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode   & Si2158_POWER_DOWN_HW_CMD_SUBCODE_MASK   ) << Si2158_POWER_DOWN_HW_CMD_SUBCODE_LSB  );
    cmdByteBuffer[2] = (unsigned char) ( ( pd_xo_osc & Si2158_POWER_DOWN_HW_CMD_PD_XO_OSC_MASK ) << Si2158_POWER_DOWN_HW_CMD_PD_XO_OSC_LSB|
                                         ( reserved1 & Si2158_POWER_DOWN_HW_CMD_RESERVED1_MASK ) << Si2158_POWER_DOWN_HW_CMD_RESERVED1_LSB|
                                         ( en_xout   & Si2158_POWER_DOWN_HW_CMD_EN_XOUT_MASK   ) << Si2158_POWER_DOWN_HW_CMD_EN_XOUT_LSB  |
                                         ( reserved2 & Si2158_POWER_DOWN_HW_CMD_RESERVED2_MASK ) << Si2158_POWER_DOWN_HW_CMD_RESERVED2_LSB);
    cmdByteBuffer[3] = (unsigned char) ( ( pd_ldo    & Si2158_POWER_DOWN_HW_CMD_PD_LDO_MASK    ) << Si2158_POWER_DOWN_HW_CMD_PD_LDO_LSB   );
    cmdByteBuffer[4] = (unsigned char) ( ( reserved3 & Si2158_POWER_DOWN_HW_CMD_RESERVED3_MASK ) << Si2158_POWER_DOWN_HW_CMD_RESERVED3_LSB);
    cmdByteBuffer[5] = (unsigned char) ( ( reserved4 & Si2158_POWER_DOWN_HW_CMD_RESERVED4_MASK ) << Si2158_POWER_DOWN_HW_CMD_RESERVED4_LSB);
    cmdByteBuffer[6] = (unsigned char) ( ( reserved5 & Si2158_POWER_DOWN_HW_CMD_RESERVED5_MASK ) << Si2158_POWER_DOWN_HW_CMD_RESERVED5_LSB);
    cmdByteBuffer[7] = (unsigned char) ( ( reserved6 & Si2158_POWER_DOWN_HW_CMD_RESERVED6_MASK ) << Si2158_POWER_DOWN_HW_CMD_RESERVED6_LSB);
    cmdByteBuffer[8] = (unsigned char) ( ( reserved7 & Si2158_POWER_DOWN_HW_CMD_RESERVED7_MASK ) << Si2158_POWER_DOWN_HW_CMD_RESERVED7_LSB);
    cmdByteBuffer[9] = (unsigned char) ( ( reserved8 & Si2158_POWER_DOWN_HW_CMD_RESERVED8_MASK ) << Si2158_POWER_DOWN_HW_CMD_RESERVED8_LSB);

    if (L0_WriteCommandBytes(api->i2c, 10, cmdByteBuffer) != 10) {
      SiTRACE("Error writing POWER_DOWN_HW bytes!\n");
      return ERROR_Si2158_SENDING_COMMAND;
    }

    error_code = Si2158_pollForResetState(api);
    if (error_code) {
      SiTRACE("Error polling POWER_DOWN_HW response\n");
      return error_code;
    }

    return NO_Si2158_ERROR;
}
#endif /* Si2158_POWER_DOWN_HW_CMD */
#ifdef    Si2158_POWER_UP_CMD
 /*---------------------------------------------------*/
/* Si2158_POWER_UP COMMAND                         */
/*---------------------------------------------------*/
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
                                         unsigned char   wake_up)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[15];
    unsigned char rspByteBuffer[1];
    api->rsp->power_up.STATUS = api->status;

    SiTRACE("Si2158 POWER_UP ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode    > Si2158_POWER_UP_CMD_SUBCODE_MAX   ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "   , subcode    );
    if ((clock_mode > Si2158_POWER_UP_CMD_CLOCK_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CLOCK_MODE %d ", clock_mode );
    if ((en_xout    > Si2158_POWER_UP_CMD_EN_XOUT_MAX   ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("EN_XOUT %d "   , en_xout    );
    if ((pd_ldo     > Si2158_POWER_UP_CMD_PD_LDO_MAX    ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("PD_LDO %d "    , pd_ldo     );
    if ((reserved2  > Si2158_POWER_UP_CMD_RESERVED2_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED2 %d " , reserved2  );
    if ((reserved3  > Si2158_POWER_UP_CMD_RESERVED3_MAX )  || (reserved3  < Si2158_POWER_UP_CMD_RESERVED3_MIN ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED3 %d " , reserved3  );
    if ((reserved4  > Si2158_POWER_UP_CMD_RESERVED4_MAX )  || (reserved4  < Si2158_POWER_UP_CMD_RESERVED4_MIN ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED4 %d " , reserved4  );
    if ((reserved5  > Si2158_POWER_UP_CMD_RESERVED5_MAX )  || (reserved5  < Si2158_POWER_UP_CMD_RESERVED5_MIN ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED5 %d " , reserved5  );
    if ((reserved6  > Si2158_POWER_UP_CMD_RESERVED6_MAX )  || (reserved6  < Si2158_POWER_UP_CMD_RESERVED6_MIN ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED6 %d " , reserved6  );
    if ((reserved7  > Si2158_POWER_UP_CMD_RESERVED7_MAX )  || (reserved7  < Si2158_POWER_UP_CMD_RESERVED7_MIN ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED7 %d " , reserved7  );
    if ((reset      > Si2158_POWER_UP_CMD_RESET_MAX     )  || (reset      < Si2158_POWER_UP_CMD_RESET_MIN     ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESET %d "     , reset      );
    if ((clock_freq > Si2158_POWER_UP_CMD_CLOCK_FREQ_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CLOCK_FREQ %d ", clock_freq );
    if ((reserved8  > Si2158_POWER_UP_CMD_RESERVED8_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED8 %d " , reserved8  );
    if ((func       > Si2158_POWER_UP_CMD_FUNC_MAX      ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FUNC %d "      , func       );
    if ((ctsien     > Si2158_POWER_UP_CMD_CTSIEN_MAX    ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CTSIEN %d "    , ctsien     );
    if ((wake_up    > Si2158_POWER_UP_CMD_WAKE_UP_MAX   )  || (wake_up    < Si2158_POWER_UP_CMD_WAKE_UP_MIN   ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("WAKE_UP %d "   , wake_up    );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2158_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2158_POWER_UP_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode    & Si2158_POWER_UP_CMD_SUBCODE_MASK    ) << Si2158_POWER_UP_CMD_SUBCODE_LSB   );
    cmdByteBuffer[2] = (unsigned char) ( ( clock_mode & Si2158_POWER_UP_CMD_CLOCK_MODE_MASK ) << Si2158_POWER_UP_CMD_CLOCK_MODE_LSB|
                                         ( en_xout    & Si2158_POWER_UP_CMD_EN_XOUT_MASK    ) << Si2158_POWER_UP_CMD_EN_XOUT_LSB   );
    cmdByteBuffer[3] = (unsigned char) ( ( pd_ldo     & Si2158_POWER_UP_CMD_PD_LDO_MASK     ) << Si2158_POWER_UP_CMD_PD_LDO_LSB    );
    cmdByteBuffer[4] = (unsigned char) ( ( reserved2  & Si2158_POWER_UP_CMD_RESERVED2_MASK  ) << Si2158_POWER_UP_CMD_RESERVED2_LSB );
    cmdByteBuffer[5] = (unsigned char) ( ( reserved3  & Si2158_POWER_UP_CMD_RESERVED3_MASK  ) << Si2158_POWER_UP_CMD_RESERVED3_LSB );
    cmdByteBuffer[6] = (unsigned char) ( ( reserved4  & Si2158_POWER_UP_CMD_RESERVED4_MASK  ) << Si2158_POWER_UP_CMD_RESERVED4_LSB );
    cmdByteBuffer[7] = (unsigned char) ( ( reserved5  & Si2158_POWER_UP_CMD_RESERVED5_MASK  ) << Si2158_POWER_UP_CMD_RESERVED5_LSB );
    cmdByteBuffer[8] = (unsigned char) ( ( reserved6  & Si2158_POWER_UP_CMD_RESERVED6_MASK  ) << Si2158_POWER_UP_CMD_RESERVED6_LSB );
    cmdByteBuffer[9] = (unsigned char) ( ( reserved7  & Si2158_POWER_UP_CMD_RESERVED7_MASK  ) << Si2158_POWER_UP_CMD_RESERVED7_LSB );
    cmdByteBuffer[10] = (unsigned char) ( ( reset      & Si2158_POWER_UP_CMD_RESET_MASK      ) << Si2158_POWER_UP_CMD_RESET_LSB     );
    cmdByteBuffer[11] = (unsigned char) ( ( clock_freq & Si2158_POWER_UP_CMD_CLOCK_FREQ_MASK ) << Si2158_POWER_UP_CMD_CLOCK_FREQ_LSB);
    cmdByteBuffer[12] = (unsigned char) ( ( reserved8  & Si2158_POWER_UP_CMD_RESERVED8_MASK  ) << Si2158_POWER_UP_CMD_RESERVED8_LSB );
    cmdByteBuffer[13] = (unsigned char) ( ( func       & Si2158_POWER_UP_CMD_FUNC_MASK       ) << Si2158_POWER_UP_CMD_FUNC_LSB      |
                                         ( ctsien     & Si2158_POWER_UP_CMD_CTSIEN_MASK     ) << Si2158_POWER_UP_CMD_CTSIEN_LSB    );
    cmdByteBuffer[14] = (unsigned char) ( ( wake_up    & Si2158_POWER_UP_CMD_WAKE_UP_MASK    ) << Si2158_POWER_UP_CMD_WAKE_UP_LSB   );

    if (L0_WriteCommandBytes(api->i2c, 15, cmdByteBuffer) != 15) {
      SiTRACE("Error writing POWER_UP bytes!\n");
      return ERROR_Si2158_SENDING_COMMAND;
    }

    error_code = Si2158_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling POWER_UP response\n");
      return error_code;
    }


    return NO_Si2158_ERROR;
}
#endif /* Si2158_POWER_UP_CMD */
#ifdef    Si2158_RAM_CRC_CMD
 /*---------------------------------------------------*/
/* Si2158_RAM_CRC COMMAND                          */
/*---------------------------------------------------*/
unsigned char Si2158_L1_RAM_CRC         (L1_Si2158_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[4] = {0, 0 , 0, 0};
    api->rsp->ram_crc.STATUS = api->status;

    SiTRACE("Si2158 RAM_CRC ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2158_RAM_CRC_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing RAM_CRC bytes!\n");
      return ERROR_Si2158_SENDING_COMMAND;
    }

    error_code = Si2158_pollForResponse(api, 4, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling RAM_CRC response\n");
      return error_code;
    }

    api->rsp->ram_crc.crc =   (( ( (rspByteBuffer[2]  ) | (rspByteBuffer[3]  << 8 )) >> Si2158_RAM_CRC_RESPONSE_CRC_LSB ) & Si2158_RAM_CRC_RESPONSE_CRC_MASK );

    return NO_Si2158_ERROR;
}
#endif /* Si2158_RAM_CRC_CMD */
#ifdef    Si2158_SET_PROPERTY_CMD
 /*---------------------------------------------------*/
/* Si2158_SET_PROPERTY COMMAND                     */
/*---------------------------------------------------*/
unsigned char Si2158_L1_SET_PROPERTY    (L1_Si2158_Context *api,
                                         unsigned char   reserved,
                                         unsigned int    prop,
                                         unsigned int    data)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[6];
    unsigned char rspByteBuffer[4] = {0};
    api->rsp->set_property.STATUS = api->status;

    //printf("Si2158 SET_PROPERTY ");
  #if 1 //ifdef   DEBUG_RANGE_CHECK
    SiTRACE("RESERVED %d ", reserved );
    //printf("PROP %x "    , prop     );
    //printf("DATA %x "    , data     );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2158_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    //printf("\n");

    cmdByteBuffer[0] = Si2158_SET_PROPERTY_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( reserved & Si2158_SET_PROPERTY_CMD_RESERVED_MASK ) << Si2158_SET_PROPERTY_CMD_RESERVED_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( prop     & Si2158_SET_PROPERTY_CMD_PROP_MASK     ) << Si2158_SET_PROPERTY_CMD_PROP_LSB    );
    cmdByteBuffer[3] = (unsigned char) ((( prop     & Si2158_SET_PROPERTY_CMD_PROP_MASK     ) << Si2158_SET_PROPERTY_CMD_PROP_LSB    )>>8);
    cmdByteBuffer[4] = (unsigned char) ( ( data     & Si2158_SET_PROPERTY_CMD_DATA_MASK     ) << Si2158_SET_PROPERTY_CMD_DATA_LSB    );
    cmdByteBuffer[5] = (unsigned char) ((( data     & Si2158_SET_PROPERTY_CMD_DATA_MASK     ) << Si2158_SET_PROPERTY_CMD_DATA_LSB    )>>8);

    if (L0_WriteCommandBytes(api->i2c, 6, cmdByteBuffer) != 6) {
      SiTRACE("Error writing SET_PROPERTY bytes!\n");
      return ERROR_Si2158_SENDING_COMMAND;
    }

    error_code = Si2158_pollForResponse(api, 4, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling SET_PROPERTY response\n");
      return error_code;
    }

    api->rsp->set_property.reserved =   (( ( (rspByteBuffer[1]  )) >> Si2158_SET_PROPERTY_RESPONSE_RESERVED_LSB ) & Si2158_SET_PROPERTY_RESPONSE_RESERVED_MASK );
    api->rsp->set_property.data     =   (( ( (rspByteBuffer[2]  ) | (rspByteBuffer[3]  << 8 )) >> Si2158_SET_PROPERTY_RESPONSE_DATA_LSB     ) & Si2158_SET_PROPERTY_RESPONSE_DATA_MASK     );

    return NO_Si2158_ERROR;
}
#endif /* Si2158_SET_PROPERTY_CMD */
#ifdef    Si2158_STANDBY_CMD
 /*---------------------------------------------------*/
/* Si2158_STANDBY COMMAND                          */
/*---------------------------------------------------*/
unsigned char Si2158_L1_STANDBY         (L1_Si2158_Context *api,
                                         unsigned char   type)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[1];
    api->rsp->standby.STATUS = api->status;

    SiTRACE("Si2158 STANDBY ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((type > Si2158_STANDBY_CMD_TYPE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("TYPE %d ", type );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2158_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2158_STANDBY_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( type & Si2158_STANDBY_CMD_TYPE_MASK ) << Si2158_STANDBY_CMD_TYPE_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing STANDBY bytes!\n");
      return ERROR_Si2158_SENDING_COMMAND;
    }

    error_code = Si2158_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling STANDBY response\n");
      return error_code;
    }


    return NO_Si2158_ERROR;
}
#endif /* Si2158_STANDBY_CMD */
#ifdef    Si2158_TUNER_STATUS_CMD
 /*---------------------------------------------------*/
/* Si2158_TUNER_STATUS COMMAND                     */
/*---------------------------------------------------*/
unsigned char Si2158_L1_TUNER_STATUS    (L1_Si2158_Context *api,
                                         unsigned char   intack)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    api->rsp->tuner_status.STATUS = api->status;

    SiTRACE("Si2158 TUNER_STATUS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((intack > Si2158_TUNER_STATUS_CMD_INTACK_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("INTACK %d ", intack );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2158_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2158_TUNER_STATUS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( intack & Si2158_TUNER_STATUS_CMD_INTACK_MASK ) << Si2158_TUNER_STATUS_CMD_INTACK_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing TUNER_STATUS bytes!\n");
      return ERROR_Si2158_SENDING_COMMAND;
    }

    error_code = Si2158_pollForResponse(api, 12, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling TUNER_STATUS response\n");
      return error_code;
    }

    api->rsp->tuner_status.tcint    =   (( ( (rspByteBuffer[1]  )) >> Si2158_TUNER_STATUS_RESPONSE_TCINT_LSB    ) & Si2158_TUNER_STATUS_RESPONSE_TCINT_MASK    );
    api->rsp->tuner_status.rssilint =   (( ( (rspByteBuffer[1]  )) >> Si2158_TUNER_STATUS_RESPONSE_RSSILINT_LSB ) & Si2158_TUNER_STATUS_RESPONSE_RSSILINT_MASK );
    api->rsp->tuner_status.rssihint =   (( ( (rspByteBuffer[1]  )) >> Si2158_TUNER_STATUS_RESPONSE_RSSIHINT_LSB ) & Si2158_TUNER_STATUS_RESPONSE_RSSIHINT_MASK );
    api->rsp->tuner_status.tc       =   (( ( (rspByteBuffer[2]  )) >> Si2158_TUNER_STATUS_RESPONSE_TC_LSB       ) & Si2158_TUNER_STATUS_RESPONSE_TC_MASK       );
    api->rsp->tuner_status.rssil    =   (( ( (rspByteBuffer[2]  )) >> Si2158_TUNER_STATUS_RESPONSE_RSSIL_LSB    ) & Si2158_TUNER_STATUS_RESPONSE_RSSIL_MASK    );
    api->rsp->tuner_status.rssih    =   (( ( (rspByteBuffer[2]  )) >> Si2158_TUNER_STATUS_RESPONSE_RSSIH_LSB    ) & Si2158_TUNER_STATUS_RESPONSE_RSSIH_MASK    );
    api->rsp->tuner_status.rssi     = (((( ( (rspByteBuffer[3]  )) >> Si2158_TUNER_STATUS_RESPONSE_RSSI_LSB     ) & Si2158_TUNER_STATUS_RESPONSE_RSSI_MASK) <<Si2158_TUNER_STATUS_RESPONSE_RSSI_SHIFT ) >>Si2158_TUNER_STATUS_RESPONSE_RSSI_SHIFT     );
    api->rsp->tuner_status.freq     =   (( ( (rspByteBuffer[4]  ) | (rspByteBuffer[5]  << 8 ) | (rspByteBuffer[6]  << 16 ) | (rspByteBuffer[7]  << 24 )) >> Si2158_TUNER_STATUS_RESPONSE_FREQ_LSB     ) & Si2158_TUNER_STATUS_RESPONSE_FREQ_MASK     );
    api->rsp->tuner_status.mode     =   (( ( (rspByteBuffer[8]  )) >> Si2158_TUNER_STATUS_RESPONSE_MODE_LSB     ) & Si2158_TUNER_STATUS_RESPONSE_MODE_MASK     );
    api->rsp->tuner_status.vco_code = (((( ( (rspByteBuffer[10] ) | (rspByteBuffer[11] << 8 )) >> Si2158_TUNER_STATUS_RESPONSE_VCO_CODE_LSB ) & Si2158_TUNER_STATUS_RESPONSE_VCO_CODE_MASK) <<Si2158_TUNER_STATUS_RESPONSE_VCO_CODE_SHIFT ) >>Si2158_TUNER_STATUS_RESPONSE_VCO_CODE_SHIFT );

    return NO_Si2158_ERROR;
}
#endif /* Si2158_TUNER_STATUS_CMD */
#ifdef    Si2158_TUNER_TUNE_FREQ_CMD
 /*---------------------------------------------------*/
/* Si2158_TUNER_TUNE_FREQ COMMAND                  */
/*---------------------------------------------------*/
unsigned char Si2158_L1_TUNER_TUNE_FREQ (L1_Si2158_Context *api,
                                         unsigned char   mode,
                                         unsigned long   freq)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[8];
    unsigned char rspByteBuffer[1];
    api->rsp->tuner_tune_freq.STATUS = api->status;

    SiTRACE("Si2158 TUNER_TUNE_FREQ ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((mode > Si2158_TUNER_TUNE_FREQ_CMD_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("MODE %d ", mode );
    if ((freq > Si2158_TUNER_TUNE_FREQ_CMD_FREQ_MAX)  || (freq < Si2158_TUNER_TUNE_FREQ_CMD_FREQ_MIN) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FREQ %d ", freq );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2158_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2158_TUNER_TUNE_FREQ_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( mode & Si2158_TUNER_TUNE_FREQ_CMD_MODE_MASK ) << Si2158_TUNER_TUNE_FREQ_CMD_MODE_LSB);
    cmdByteBuffer[2] = (unsigned char)0x00;
    cmdByteBuffer[3] = (unsigned char)0x00;
    cmdByteBuffer[4] = (unsigned char) ( ( freq & Si2158_TUNER_TUNE_FREQ_CMD_FREQ_MASK ) << Si2158_TUNER_TUNE_FREQ_CMD_FREQ_LSB);
    cmdByteBuffer[5] = (unsigned char) ((( freq & Si2158_TUNER_TUNE_FREQ_CMD_FREQ_MASK ) << Si2158_TUNER_TUNE_FREQ_CMD_FREQ_LSB)>>8);
    cmdByteBuffer[6] = (unsigned char) ((( freq & Si2158_TUNER_TUNE_FREQ_CMD_FREQ_MASK ) << Si2158_TUNER_TUNE_FREQ_CMD_FREQ_LSB)>>16);
    cmdByteBuffer[7] = (unsigned char) ((( freq & Si2158_TUNER_TUNE_FREQ_CMD_FREQ_MASK ) << Si2158_TUNER_TUNE_FREQ_CMD_FREQ_LSB)>>24);

    if (L0_WriteCommandBytes(api->i2c, 8, cmdByteBuffer) != 8) {
      SiTRACE("Error writing TUNER_TUNE_FREQ bytes!\n");
      return ERROR_Si2158_SENDING_COMMAND;
    }

    error_code = Si2158_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling TUNER_TUNE_FREQ response\n");
      return error_code;
    }


    return NO_Si2158_ERROR;
}
#endif /* Si2158_TUNER_TUNE_FREQ_CMD */
/* _commands_insertion_point */

/* _send_command2_insertion_start */

  /* --------------------------------------------*/
  /* SEND_COMMAND2 FUNCTION                      */
  /* --------------------------------------------*/
unsigned char   Si2158_L1_SendCommand2(L1_Si2158_Context *api, unsigned int cmd_code) {
    switch (cmd_code) {
    #ifdef        Si2158_AGC_OVERRIDE_CMD
     case         Si2158_AGC_OVERRIDE_CMD_CODE:
       return Si2158_L1_AGC_OVERRIDE (api, api->cmd->agc_override.force_max_gain, api->cmd->agc_override.force_top_gain );
     break;
    #endif /*     Si2158_AGC_OVERRIDE_CMD */
    #ifdef        Si2158_ATV_CW_TEST_CMD
     case         Si2158_ATV_CW_TEST_CMD_CODE:
       return Si2158_L1_ATV_CW_TEST (api, api->cmd->atv_cw_test.pc_lock );
     break;
    #endif /*     Si2158_ATV_CW_TEST_CMD */
    #ifdef        Si2158_ATV_RESTART_CMD
     case         Si2158_ATV_RESTART_CMD_CODE:
       return Si2158_L1_ATV_RESTART (api );
     break;
    #endif /*     Si2158_ATV_RESTART_CMD */
    #ifdef        Si2158_ATV_STATUS_CMD
     case         Si2158_ATV_STATUS_CMD_CODE:
       return Si2158_L1_ATV_STATUS (api, api->cmd->atv_status.intack );
     break;
    #endif /*     Si2158_ATV_STATUS_CMD */
    #ifdef        Si2158_CONFIG_CLOCKS_CMD
     case         Si2158_CONFIG_CLOCKS_CMD_CODE:
       return Si2158_L1_CONFIG_CLOCKS (api, api->cmd->config_clocks.subcode, api->cmd->config_clocks.clock_mode, api->cmd->config_clocks.en_xout );
     break;
    #endif /*     Si2158_CONFIG_CLOCKS_CMD */
    #ifdef        Si2158_CONFIG_PINS_CMD
     case         Si2158_CONFIG_PINS_CMD_CODE:
       return Si2158_L1_CONFIG_PINS (api, api->cmd->config_pins.gpio1_mode, api->cmd->config_pins.gpio1_read, api->cmd->config_pins.gpio2_mode, api->cmd->config_pins.gpio2_read, api->cmd->config_pins.reserved1, api->cmd->config_pins.reserved2, api->cmd->config_pins.reserved3 );
     break;
    #endif /*     Si2158_CONFIG_PINS_CMD */
    #ifdef        Si2158_DTV_RESTART_CMD
     case         Si2158_DTV_RESTART_CMD_CODE:
       return Si2158_L1_DTV_RESTART (api );
     break;
    #endif /*     Si2158_DTV_RESTART_CMD */
    #ifdef        Si2158_DTV_STATUS_CMD
     case         Si2158_DTV_STATUS_CMD_CODE:
       return Si2158_L1_DTV_STATUS (api, api->cmd->dtv_status.intack );
     break;
    #endif /*     Si2158_DTV_STATUS_CMD */
    #ifdef        Si2158_EXIT_BOOTLOADER_CMD
     case         Si2158_EXIT_BOOTLOADER_CMD_CODE:
       return Si2158_L1_EXIT_BOOTLOADER (api, api->cmd->exit_bootloader.func, api->cmd->exit_bootloader.ctsien );
     break;
    #endif /*     Si2158_EXIT_BOOTLOADER_CMD */
    #ifdef        Si2158_FINE_TUNE_CMD
     case         Si2158_FINE_TUNE_CMD_CODE:
       return Si2158_L1_FINE_TUNE (api, api->cmd->fine_tune.persistence, api->cmd->fine_tune.apply_to_lif, api->cmd->fine_tune.offset_500hz );
     break;
    #endif /*     Si2158_FINE_TUNE_CMD */
    #ifdef        Si2158_GET_PROPERTY_CMD
     case         Si2158_GET_PROPERTY_CMD_CODE:
       return Si2158_L1_GET_PROPERTY (api, api->cmd->get_property.reserved, api->cmd->get_property.prop );
     break;
    #endif /*     Si2158_GET_PROPERTY_CMD */
    #ifdef        Si2158_GET_REV_CMD
     case         Si2158_GET_REV_CMD_CODE:
       return Si2158_L1_GET_REV (api );
     break;
    #endif /*     Si2158_GET_REV_CMD */
    #ifdef        Si2158_PART_INFO_CMD
     case         Si2158_PART_INFO_CMD_CODE:
       return Si2158_L1_PART_INFO (api );
     break;
    #endif /*     Si2158_PART_INFO_CMD */
    #ifdef        Si2158_POWER_DOWN_CMD
     case         Si2158_POWER_DOWN_CMD_CODE:
       return Si2158_L1_POWER_DOWN (api );
     break;
    #endif /*     Si2158_POWER_DOWN_CMD */
    #ifdef        Si2158_POWER_DOWN_HW_CMD
     case         Si2158_POWER_DOWN_HW_CMD_CODE:
       return Si2158_L1_POWER_DOWN_HW (api, api->cmd->power_down_hw.subcode, api->cmd->power_down_hw.pd_xo_osc, api->cmd->power_down_hw.reserved1, api->cmd->power_down_hw.en_xout, api->cmd->power_down_hw.reserved2, api->cmd->power_down_hw.pd_ldo, api->cmd->power_down_hw.reserved3, api->cmd->power_down_hw.reserved4, api->cmd->power_down_hw.reserved5, api->cmd->power_down_hw.reserved6, api->cmd->power_down_hw.reserved7, api->cmd->power_down_hw.reserved8 );
     break;
    #endif /*     Si2158_POWER_DOWN_HW_CMD */
    #ifdef        Si2158_POWER_UP_CMD
     case         Si2158_POWER_UP_CMD_CODE:
       return Si2158_L1_POWER_UP (api, api->cmd->power_up.subcode, api->cmd->power_up.clock_mode, api->cmd->power_up.en_xout, api->cmd->power_up.pd_ldo, api->cmd->power_up.reserved2, api->cmd->power_up.reserved3, api->cmd->power_up.reserved4, api->cmd->power_up.reserved5, api->cmd->power_up.reserved6, api->cmd->power_up.reserved7, api->cmd->power_up.reset, api->cmd->power_up.clock_freq, api->cmd->power_up.reserved8, api->cmd->power_up.func, api->cmd->power_up.ctsien, api->cmd->power_up.wake_up );
     break;
    #endif /*     Si2158_POWER_UP_CMD */
    #ifdef        Si2158_RAM_CRC_CMD
     case         Si2158_RAM_CRC_CMD_CODE:
       return Si2158_L1_RAM_CRC (api );
     break;
    #endif /*     Si2158_RAM_CRC_CMD */
    #ifdef        Si2158_SET_PROPERTY_CMD
     case         Si2158_SET_PROPERTY_CMD_CODE:
       return Si2158_L1_SET_PROPERTY (api, api->cmd->set_property.reserved, api->cmd->set_property.prop, api->cmd->set_property.data );
     break;
    #endif /*     Si2158_SET_PROPERTY_CMD */
    #ifdef        Si2158_STANDBY_CMD
     case         Si2158_STANDBY_CMD_CODE:
       return Si2158_L1_STANDBY (api, api->cmd->standby.type );
     break;
    #endif /*     Si2158_STANDBY_CMD */
    #ifdef        Si2158_TUNER_STATUS_CMD
     case         Si2158_TUNER_STATUS_CMD_CODE:
       return Si2158_L1_TUNER_STATUS (api, api->cmd->tuner_status.intack );
     break;
    #endif /*     Si2158_TUNER_STATUS_CMD */
    #ifdef        Si2158_TUNER_TUNE_FREQ_CMD
     case         Si2158_TUNER_TUNE_FREQ_CMD_CODE:
       return Si2158_L1_TUNER_TUNE_FREQ (api, api->cmd->tuner_tune_freq.mode, api->cmd->tuner_tune_freq.freq );
     break;
    #endif /*     Si2158_TUNER_TUNE_FREQ_CMD */
   default : break;
    }
     return 0;
  }
  /* _send_command2_insertion_point */

#ifdef    Si2158_GET_COMMAND_STRINGS
/* _get_command_response_string_insertion_start */

  /* --------------------------------------------*/
  /* GET_COMMAND_RESPONSE_STRING FUNCTION        */
  /* --------------------------------------------*/
unsigned char   Si2158_L1_GetCommandResponseString(L1_Si2158_Context *api, unsigned int cmd_code, char *separator, char *msg) {
    switch (cmd_code) {
    #ifdef        Si2158_AGC_OVERRIDE_CMD
     case         Si2158_AGC_OVERRIDE_CMD_CODE:
      sprintf(msg,"AGC_OVERRIDE ");
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TUNINT ");
           if  (api->rsp->agc_override.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->agc_override.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->agc_override.STATUS->tunint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ATVINT ");
           if  (api->rsp->agc_override.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->agc_override.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->agc_override.STATUS->atvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DTVINT ");
           if  (api->rsp->agc_override.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->agc_override.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->agc_override.STATUS->dtvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ERR    ");
           if  (api->rsp->agc_override.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->agc_override.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->agc_override.STATUS->err);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CTS    ");
           if  (api->rsp->agc_override.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->agc_override.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->agc_override.STATUS->cts);
     break;
    #endif /*     Si2158_AGC_OVERRIDE_CMD */

    #ifdef        Si2158_ATV_CW_TEST_CMD
     case         Si2158_ATV_CW_TEST_CMD_CODE:
      sprintf(msg,"ATV_CW_TEST ");
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TUNINT ");
           if  (api->rsp->atv_cw_test.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->atv_cw_test.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->atv_cw_test.STATUS->tunint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ATVINT ");
           if  (api->rsp->atv_cw_test.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->atv_cw_test.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->atv_cw_test.STATUS->atvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DTVINT ");
           if  (api->rsp->atv_cw_test.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->atv_cw_test.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->atv_cw_test.STATUS->dtvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ERR    ");
           if  (api->rsp->atv_cw_test.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->atv_cw_test.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->atv_cw_test.STATUS->err);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CTS    ");
           if  (api->rsp->atv_cw_test.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->atv_cw_test.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->atv_cw_test.STATUS->cts);
     break;
    #endif /*     Si2158_ATV_CW_TEST_CMD */

    #ifdef        Si2158_ATV_RESTART_CMD
     case         Si2158_ATV_RESTART_CMD_CODE:
      sprintf(msg,"ATV_RESTART ");
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TUNINT ");
           if  (api->rsp->atv_restart.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->atv_restart.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->atv_restart.STATUS->tunint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ATVINT ");
           if  (api->rsp->atv_restart.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->atv_restart.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->atv_restart.STATUS->atvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DTVINT ");
           if  (api->rsp->atv_restart.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->atv_restart.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->atv_restart.STATUS->dtvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ERR    ");
           if  (api->rsp->atv_restart.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->atv_restart.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->atv_restart.STATUS->err);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CTS    ");
           if  (api->rsp->atv_restart.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->atv_restart.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->atv_restart.STATUS->cts);
     break;
    #endif /*     Si2158_ATV_RESTART_CMD */

    #ifdef        Si2158_ATV_STATUS_CMD
     case         Si2158_ATV_STATUS_CMD_CODE:
      sprintf(msg,"ATV_STATUS ");
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TUNINT    ");
           if  (api->rsp->atv_status.STATUS->tunint    ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->atv_status.STATUS->tunint    ==     1) strcat(msg,"TRIGGERED    ");
      else                                                      sprintf(msg,"%s%d", msg, api->rsp->atv_status.STATUS->tunint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ATVINT    ");
           if  (api->rsp->atv_status.STATUS->atvint    ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->atv_status.STATUS->atvint    ==     1) strcat(msg,"TRIGGERED    ");
      else                                                      sprintf(msg,"%s%d", msg, api->rsp->atv_status.STATUS->atvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DTVINT    ");
           if  (api->rsp->atv_status.STATUS->dtvint    ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->atv_status.STATUS->dtvint    ==     1) strcat(msg,"TRIGGERED    ");
      else                                                      sprintf(msg,"%s%d", msg, api->rsp->atv_status.STATUS->dtvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ERR       ");
           if  (api->rsp->atv_status.STATUS->err       ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->atv_status.STATUS->err       ==     0) strcat(msg,"NO_ERROR");
      else                                                      sprintf(msg,"%s%d", msg, api->rsp->atv_status.STATUS->err);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CTS       ");
           if  (api->rsp->atv_status.STATUS->cts       ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->atv_status.STATUS->cts       ==     0) strcat(msg,"WAIT     ");
      else                                                      sprintf(msg,"%s%d", msg, api->rsp->atv_status.STATUS->cts);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CHLINT    ");
           if  (api->rsp->atv_status.chlint    ==     1) strcat(msg,"CHANGED  ");
      else if  (api->rsp->atv_status.chlint    ==     0) strcat(msg,"NO_CHANGE");
      else                                              sprintf(msg,"%s%d", msg, api->rsp->atv_status.chlint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-PCLINT    ");
           if  (api->rsp->atv_status.pclint    ==     1) strcat(msg,"CHANGED  ");
      else if  (api->rsp->atv_status.pclint    ==     0) strcat(msg,"NO_CHANGE");
      else                                              sprintf(msg,"%s%d", msg, api->rsp->atv_status.pclint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CHL       ");
           if  (api->rsp->atv_status.chl       ==     1) strcat(msg,"CHANNEL   ");
      else if  (api->rsp->atv_status.chl       ==     0) strcat(msg,"NO_CHANNEL");
      else                                              sprintf(msg,"%s%d", msg, api->rsp->atv_status.chl);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-PCL       ");
           if  (api->rsp->atv_status.pcl       ==     1) strcat(msg,"LOCKED ");
      else if  (api->rsp->atv_status.pcl       ==     0) strcat(msg,"NO_LOCK");
      else                                              sprintf(msg,"%s%d", msg, api->rsp->atv_status.pcl);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-AFC_FREQ  "); sprintf(msg,"%s%d", msg, api->rsp->atv_status.afc_freq);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-VIDEO_SYS ");
           if  (api->rsp->atv_status.video_sys ==     0) strcat(msg,"B ");
      else if  (api->rsp->atv_status.video_sys ==     5) strcat(msg,"DK");
      else if  (api->rsp->atv_status.video_sys ==     1) strcat(msg,"GH");
      else if  (api->rsp->atv_status.video_sys ==     4) strcat(msg,"I ");
      else if  (api->rsp->atv_status.video_sys ==     6) strcat(msg,"L ");
      else if  (api->rsp->atv_status.video_sys ==     7) strcat(msg,"LP");
      else if  (api->rsp->atv_status.video_sys ==     2) strcat(msg,"M ");
      else if  (api->rsp->atv_status.video_sys ==     3) strcat(msg,"N ");
      else                                              sprintf(msg,"%s%d", msg, api->rsp->atv_status.video_sys);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-COLOR     ");
           if  (api->rsp->atv_status.color     ==     0) strcat(msg,"PAL_NTSC");
      else if  (api->rsp->atv_status.color     ==     1) strcat(msg,"SECAM   ");
      else                                              sprintf(msg,"%s%d", msg, api->rsp->atv_status.color);
     break;
    #endif /*     Si2158_ATV_STATUS_CMD */

    #ifdef        Si2158_CONFIG_CLOCKS_CMD
     case         Si2158_CONFIG_CLOCKS_CMD_CODE:
      sprintf(msg,"CONFIG_CLOCKS ");
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TUNINT ");
           if  (api->rsp->config_clocks.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->config_clocks.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                      sprintf(msg,"%s%d", msg, api->rsp->config_clocks.STATUS->tunint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ATVINT ");
           if  (api->rsp->config_clocks.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->config_clocks.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                      sprintf(msg,"%s%d", msg, api->rsp->config_clocks.STATUS->atvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DTVINT ");
           if  (api->rsp->config_clocks.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->config_clocks.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                      sprintf(msg,"%s%d", msg, api->rsp->config_clocks.STATUS->dtvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ERR    ");
           if  (api->rsp->config_clocks.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->config_clocks.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                      sprintf(msg,"%s%d", msg, api->rsp->config_clocks.STATUS->err);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CTS    ");
           if  (api->rsp->config_clocks.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->config_clocks.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                      sprintf(msg,"%s%d", msg, api->rsp->config_clocks.STATUS->cts);
     break;
    #endif /*     Si2158_CONFIG_CLOCKS_CMD */

    #ifdef        Si2158_CONFIG_PINS_CMD
     case         Si2158_CONFIG_PINS_CMD_CODE:
      sprintf(msg,"CONFIG_PINS ");
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TUNINT      ");
           if  (api->rsp->config_pins.STATUS->tunint      ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->config_pins.STATUS->tunint      ==     1) strcat(msg,"TRIGGERED    ");
      else                                                         sprintf(msg,"%s%d", msg, api->rsp->config_pins.STATUS->tunint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ATVINT      ");
           if  (api->rsp->config_pins.STATUS->atvint      ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->config_pins.STATUS->atvint      ==     1) strcat(msg,"TRIGGERED    ");
      else                                                         sprintf(msg,"%s%d", msg, api->rsp->config_pins.STATUS->atvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DTVINT      ");
           if  (api->rsp->config_pins.STATUS->dtvint      ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->config_pins.STATUS->dtvint      ==     1) strcat(msg,"TRIGGERED    ");
      else                                                         sprintf(msg,"%s%d", msg, api->rsp->config_pins.STATUS->dtvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ERR         ");
           if  (api->rsp->config_pins.STATUS->err         ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->config_pins.STATUS->err         ==     0) strcat(msg,"NO_ERROR");
      else                                                         sprintf(msg,"%s%d", msg, api->rsp->config_pins.STATUS->err);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CTS         ");
           if  (api->rsp->config_pins.STATUS->cts         ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->config_pins.STATUS->cts         ==     0) strcat(msg,"WAIT     ");
      else                                                         sprintf(msg,"%s%d", msg, api->rsp->config_pins.STATUS->cts);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-GPIO1_MODE  ");
           if  (api->rsp->config_pins.gpio1_mode  ==     1) strcat(msg,"DISABLE");
      else if  (api->rsp->config_pins.gpio1_mode  ==     2) strcat(msg,"DRIVE_0");
      else if  (api->rsp->config_pins.gpio1_mode  ==     3) strcat(msg,"DRIVE_1");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->config_pins.gpio1_mode);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-GPIO1_STATE ");
           if  (api->rsp->config_pins.gpio1_state ==     0) strcat(msg,"READ_0");
      else if  (api->rsp->config_pins.gpio1_state ==     1) strcat(msg,"READ_1");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->config_pins.gpio1_state);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-GPIO2_MODE  ");
           if  (api->rsp->config_pins.gpio2_mode  ==     1) strcat(msg,"DISABLE");
      else if  (api->rsp->config_pins.gpio2_mode  ==     2) strcat(msg,"DRIVE_0");
      else if  (api->rsp->config_pins.gpio2_mode  ==     3) strcat(msg,"DRIVE_1");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->config_pins.gpio2_mode);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-GPIO2_STATE ");
           if  (api->rsp->config_pins.gpio2_state ==     0) strcat(msg,"READ_0");
      else if  (api->rsp->config_pins.gpio2_state ==     1) strcat(msg,"READ_1");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->config_pins.gpio2_state);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-RESERVED1   "); sprintf(msg,"%s%d", msg, api->rsp->config_pins.reserved1);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-RESERVED2   "); sprintf(msg,"%s%d", msg, api->rsp->config_pins.reserved2);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-RESERVED3   "); sprintf(msg,"%s%d", msg, api->rsp->config_pins.reserved3);
     break;
    #endif /*     Si2158_CONFIG_PINS_CMD */

    #ifdef        Si2158_DTV_RESTART_CMD
     case         Si2158_DTV_RESTART_CMD_CODE:
      sprintf(msg,"DTV_RESTART ");
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TUNINT ");
           if  (api->rsp->dtv_restart.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->dtv_restart.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->dtv_restart.STATUS->tunint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ATVINT ");
           if  (api->rsp->dtv_restart.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->dtv_restart.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->dtv_restart.STATUS->atvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DTVINT ");
           if  (api->rsp->dtv_restart.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->dtv_restart.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->dtv_restart.STATUS->dtvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ERR    ");
           if  (api->rsp->dtv_restart.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->dtv_restart.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->dtv_restart.STATUS->err);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CTS    ");
           if  (api->rsp->dtv_restart.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->dtv_restart.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->dtv_restart.STATUS->cts);
     break;
    #endif /*     Si2158_DTV_RESTART_CMD */

    #ifdef        Si2158_DTV_STATUS_CMD
     case         Si2158_DTV_STATUS_CMD_CODE:
      sprintf(msg,"DTV_STATUS ");
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TUNINT     ");
           if  (api->rsp->dtv_status.STATUS->tunint     ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->dtv_status.STATUS->tunint     ==     1) strcat(msg,"TRIGGERED    ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->dtv_status.STATUS->tunint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ATVINT     ");
           if  (api->rsp->dtv_status.STATUS->atvint     ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->dtv_status.STATUS->atvint     ==     1) strcat(msg,"TRIGGERED    ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->dtv_status.STATUS->atvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DTVINT     ");
           if  (api->rsp->dtv_status.STATUS->dtvint     ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->dtv_status.STATUS->dtvint     ==     1) strcat(msg,"TRIGGERED    ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->dtv_status.STATUS->dtvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ERR        ");
           if  (api->rsp->dtv_status.STATUS->err        ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->dtv_status.STATUS->err        ==     0) strcat(msg,"NO_ERROR");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->dtv_status.STATUS->err);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CTS        ");
           if  (api->rsp->dtv_status.STATUS->cts        ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->dtv_status.STATUS->cts        ==     0) strcat(msg,"WAIT     ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->dtv_status.STATUS->cts);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CHLINT     ");
           if  (api->rsp->dtv_status.chlint     ==     1) strcat(msg,"CHANGED  ");
      else if  (api->rsp->dtv_status.chlint     ==     0) strcat(msg,"NO_CHANGE");
      else                                               sprintf(msg,"%s%d", msg, api->rsp->dtv_status.chlint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CHL        ");
           if  (api->rsp->dtv_status.chl        ==     1) strcat(msg,"CHANNEL   ");
      else if  (api->rsp->dtv_status.chl        ==     0) strcat(msg,"NO_CHANNEL");
      else                                               sprintf(msg,"%s%d", msg, api->rsp->dtv_status.chl);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-BW         ");
           if  (api->rsp->dtv_status.bw         ==     6) strcat(msg,"BW_6MHZ");
      else if  (api->rsp->dtv_status.bw         ==     7) strcat(msg,"BW_7MHZ");
      else if  (api->rsp->dtv_status.bw         ==     8) strcat(msg,"BW_8MHZ");
      else                                               sprintf(msg,"%s%d", msg, api->rsp->dtv_status.bw);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-MODULATION ");
           if  (api->rsp->dtv_status.modulation ==     0) strcat(msg,"ATSC  ");
      else if  (api->rsp->dtv_status.modulation ==    15) strcat(msg,"CW    ");
      else if  (api->rsp->dtv_status.modulation ==     6) strcat(msg,"DTMB  ");
      else if  (api->rsp->dtv_status.modulation ==     3) strcat(msg,"DVBC  ");
      else if  (api->rsp->dtv_status.modulation ==     2) strcat(msg,"DVBT  ");
      else if  (api->rsp->dtv_status.modulation ==     5) strcat(msg,"ISDBC ");
      else if  (api->rsp->dtv_status.modulation ==     4) strcat(msg,"ISDBT ");
      else if  (api->rsp->dtv_status.modulation ==     1) strcat(msg,"QAM_US");
      else                                               sprintf(msg,"%s%d", msg, api->rsp->dtv_status.modulation);
     break;
    #endif /*     Si2158_DTV_STATUS_CMD */

    #ifdef        Si2158_EXIT_BOOTLOADER_CMD
     case         Si2158_EXIT_BOOTLOADER_CMD_CODE:
      sprintf(msg,"EXIT_BOOTLOADER ");
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TUNINT ");
           if  (api->rsp->exit_bootloader.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->exit_bootloader.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                        sprintf(msg,"%s%d", msg, api->rsp->exit_bootloader.STATUS->tunint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ATVINT ");
           if  (api->rsp->exit_bootloader.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->exit_bootloader.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                        sprintf(msg,"%s%d", msg, api->rsp->exit_bootloader.STATUS->atvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DTVINT ");
           if  (api->rsp->exit_bootloader.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->exit_bootloader.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                        sprintf(msg,"%s%d", msg, api->rsp->exit_bootloader.STATUS->dtvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ERR    ");
           if  (api->rsp->exit_bootloader.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->exit_bootloader.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                        sprintf(msg,"%s%d", msg, api->rsp->exit_bootloader.STATUS->err);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CTS    ");
           if  (api->rsp->exit_bootloader.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->exit_bootloader.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                        sprintf(msg,"%s%d", msg, api->rsp->exit_bootloader.STATUS->cts);
     break;
    #endif /*     Si2158_EXIT_BOOTLOADER_CMD */

    #ifdef        Si2158_FINE_TUNE_CMD
     case         Si2158_FINE_TUNE_CMD_CODE:
      sprintf(msg,"FINE_TUNE ");
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TUNINT ");
           if  (api->rsp->fine_tune.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->fine_tune.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                  sprintf(msg,"%s%d", msg, api->rsp->fine_tune.STATUS->tunint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ATVINT ");
           if  (api->rsp->fine_tune.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->fine_tune.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                  sprintf(msg,"%s%d", msg, api->rsp->fine_tune.STATUS->atvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DTVINT ");
           if  (api->rsp->fine_tune.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->fine_tune.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                  sprintf(msg,"%s%d", msg, api->rsp->fine_tune.STATUS->dtvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ERR    ");
           if  (api->rsp->fine_tune.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->fine_tune.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                  sprintf(msg,"%s%d", msg, api->rsp->fine_tune.STATUS->err);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CTS    ");
           if  (api->rsp->fine_tune.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->fine_tune.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                  sprintf(msg,"%s%d", msg, api->rsp->fine_tune.STATUS->cts);
     break;
    #endif /*     Si2158_FINE_TUNE_CMD */

    #ifdef        Si2158_GET_PROPERTY_CMD
     case         Si2158_GET_PROPERTY_CMD_CODE:
      sprintf(msg,"GET_PROPERTY ");
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TUNINT   ");
           if  (api->rsp->get_property.STATUS->tunint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->get_property.STATUS->tunint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->get_property.STATUS->tunint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ATVINT   ");
           if  (api->rsp->get_property.STATUS->atvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->get_property.STATUS->atvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->get_property.STATUS->atvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DTVINT   ");
           if  (api->rsp->get_property.STATUS->dtvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->get_property.STATUS->dtvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->get_property.STATUS->dtvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ERR      ");
           if  (api->rsp->get_property.STATUS->err      ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->get_property.STATUS->err      ==     0) strcat(msg,"NO_ERROR");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->get_property.STATUS->err);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CTS      ");
           if  (api->rsp->get_property.STATUS->cts      ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->get_property.STATUS->cts      ==     0) strcat(msg,"WAIT     ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->get_property.STATUS->cts);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-RESERVED "); sprintf(msg,"%s%d", msg, api->rsp->get_property.reserved);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DATA     "); sprintf(msg,"%s%d", msg, api->rsp->get_property.data);
     break;
    #endif /*     Si2158_GET_PROPERTY_CMD */

    #ifdef        Si2158_GET_REV_CMD
     case         Si2158_GET_REV_CMD_CODE:
      sprintf(msg,"GET_REV ");
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TUNINT   ");
           if  (api->rsp->get_rev.STATUS->tunint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->get_rev.STATUS->tunint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                  sprintf(msg,"%s%d", msg, api->rsp->get_rev.STATUS->tunint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ATVINT   ");
           if  (api->rsp->get_rev.STATUS->atvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->get_rev.STATUS->atvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                  sprintf(msg,"%s%d", msg, api->rsp->get_rev.STATUS->atvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DTVINT   ");
           if  (api->rsp->get_rev.STATUS->dtvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->get_rev.STATUS->dtvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                  sprintf(msg,"%s%d", msg, api->rsp->get_rev.STATUS->dtvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ERR      ");
           if  (api->rsp->get_rev.STATUS->err      ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->get_rev.STATUS->err      ==     0) strcat(msg,"NO_ERROR");
      else                                                  sprintf(msg,"%s%d", msg, api->rsp->get_rev.STATUS->err);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CTS      ");
           if  (api->rsp->get_rev.STATUS->cts      ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->get_rev.STATUS->cts      ==     0) strcat(msg,"WAIT     ");
      else                                                  sprintf(msg,"%s%d", msg, api->rsp->get_rev.STATUS->cts);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-PN       "); sprintf(msg,"%s%d", msg, api->rsp->get_rev.pn);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-FWMAJOR  "); sprintf(msg,"%s%d", msg, api->rsp->get_rev.fwmajor);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-FWMINOR  "); sprintf(msg,"%s%d", msg, api->rsp->get_rev.fwminor);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-PATCH    "); sprintf(msg,"%s%d", msg, api->rsp->get_rev.patch);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CMPMAJOR "); sprintf(msg,"%s%d", msg, api->rsp->get_rev.cmpmajor);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CMPMINOR "); sprintf(msg,"%s%d", msg, api->rsp->get_rev.cmpminor);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CMPBUILD "); sprintf(msg,"%s%d", msg, api->rsp->get_rev.cmpbuild);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CHIPREV  ");
           if  (api->rsp->get_rev.chiprev  ==     1) strcat(msg,"A");
      else if  (api->rsp->get_rev.chiprev  ==     2) strcat(msg,"B");
      else                                          sprintf(msg,"%s%d", msg, api->rsp->get_rev.chiprev);
     break;
    #endif /*     Si2158_GET_REV_CMD */

    #ifdef        Si2158_PART_INFO_CMD
     case         Si2158_PART_INFO_CMD_CODE:
      sprintf(msg,"PART_INFO ");
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TUNINT   ");
           if  (api->rsp->part_info.STATUS->tunint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->part_info.STATUS->tunint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->part_info.STATUS->tunint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ATVINT   ");
           if  (api->rsp->part_info.STATUS->atvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->part_info.STATUS->atvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->part_info.STATUS->atvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DTVINT   ");
           if  (api->rsp->part_info.STATUS->dtvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->part_info.STATUS->dtvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->part_info.STATUS->dtvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ERR      ");
           if  (api->rsp->part_info.STATUS->err      ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->part_info.STATUS->err      ==     0) strcat(msg,"NO_ERROR");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->part_info.STATUS->err);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CTS      ");
           if  (api->rsp->part_info.STATUS->cts      ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->part_info.STATUS->cts      ==     0) strcat(msg,"WAIT     ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->part_info.STATUS->cts);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CHIPREV  ");
           if  (api->rsp->part_info.chiprev  ==     1) strcat(msg,"A");
      else if  (api->rsp->part_info.chiprev  ==     2) strcat(msg,"B");
      else                                            sprintf(msg,"%s%d", msg, api->rsp->part_info.chiprev);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-PART     "); sprintf(msg,"%s%d", msg, api->rsp->part_info.part);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-PMAJOR   "); sprintf(msg,"%s%d", msg, api->rsp->part_info.pmajor);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-PMINOR   "); sprintf(msg,"%s%d", msg, api->rsp->part_info.pminor);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-PBUILD   "); sprintf(msg,"%s%d", msg, api->rsp->part_info.pbuild);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-RESERVED "); sprintf(msg,"%s%d", msg, api->rsp->part_info.reserved);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-SERIAL   "); sprintf(msg,"%s%ld", msg, api->rsp->part_info.serial);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ROMID    "); sprintf(msg,"%s%d", msg, api->rsp->part_info.romid);
     break;
    #endif /*     Si2158_PART_INFO_CMD */

    #ifdef        Si2158_POWER_DOWN_CMD
     case         Si2158_POWER_DOWN_CMD_CODE:
      sprintf(msg,"POWER_DOWN ");
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TUNINT ");
           if  (api->rsp->power_down.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->power_down.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                   sprintf(msg,"%s%d", msg, api->rsp->power_down.STATUS->tunint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ATVINT ");
           if  (api->rsp->power_down.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->power_down.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                   sprintf(msg,"%s%d", msg, api->rsp->power_down.STATUS->atvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DTVINT ");
           if  (api->rsp->power_down.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->power_down.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                   sprintf(msg,"%s%d", msg, api->rsp->power_down.STATUS->dtvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ERR    ");
           if  (api->rsp->power_down.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->power_down.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                   sprintf(msg,"%s%d", msg, api->rsp->power_down.STATUS->err);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CTS    ");
           if  (api->rsp->power_down.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->power_down.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                   sprintf(msg,"%s%d", msg, api->rsp->power_down.STATUS->cts);
     break;
    #endif /*     Si2158_POWER_DOWN_CMD */

    #ifdef        Si2158_POWER_DOWN_HW_CMD
     case         Si2158_POWER_DOWN_HW_CMD_CODE:
      sprintf(msg,"POWER_DOWN_HW ");
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TUNINT ");
           if  (api->rsp->power_down_hw.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->power_down_hw.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                      sprintf(msg,"%s%d", msg, api->rsp->power_down_hw.STATUS->tunint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ATVINT ");
           if  (api->rsp->power_down_hw.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->power_down_hw.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                      sprintf(msg,"%s%d", msg, api->rsp->power_down_hw.STATUS->atvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DTVINT ");
           if  (api->rsp->power_down_hw.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->power_down_hw.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                      sprintf(msg,"%s%d", msg, api->rsp->power_down_hw.STATUS->dtvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ERR    ");
           if  (api->rsp->power_down_hw.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->power_down_hw.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                      sprintf(msg,"%s%d", msg, api->rsp->power_down_hw.STATUS->err);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CTS    ");
           if  (api->rsp->power_down_hw.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->power_down_hw.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                      sprintf(msg,"%s%d", msg, api->rsp->power_down_hw.STATUS->cts);
     break;
    #endif /*     Si2158_POWER_DOWN_HW_CMD */

    #ifdef        Si2158_POWER_UP_CMD
     case         Si2158_POWER_UP_CMD_CODE:
      sprintf(msg,"POWER_UP ");
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TUNINT ");
           if  (api->rsp->power_up.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->power_up.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->power_up.STATUS->tunint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ATVINT ");
           if  (api->rsp->power_up.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->power_up.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->power_up.STATUS->atvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DTVINT ");
           if  (api->rsp->power_up.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->power_up.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->power_up.STATUS->dtvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ERR    ");
           if  (api->rsp->power_up.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->power_up.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->power_up.STATUS->err);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CTS    ");
           if  (api->rsp->power_up.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->power_up.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->power_up.STATUS->cts);
     break;
    #endif /*     Si2158_POWER_UP_CMD */

    #ifdef        Si2158_RAM_CRC_CMD
     case         Si2158_RAM_CRC_CMD_CODE:
      sprintf(msg,"RAM_CRC ");
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TUNINT ");
           if  (api->rsp->ram_crc.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->ram_crc.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                sprintf(msg,"%s%d", msg, api->rsp->ram_crc.STATUS->tunint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ATVINT ");
           if  (api->rsp->ram_crc.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->ram_crc.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                sprintf(msg,"%s%d", msg, api->rsp->ram_crc.STATUS->atvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DTVINT ");
           if  (api->rsp->ram_crc.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->ram_crc.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                sprintf(msg,"%s%d", msg, api->rsp->ram_crc.STATUS->dtvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ERR    ");
           if  (api->rsp->ram_crc.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->ram_crc.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                sprintf(msg,"%s%d", msg, api->rsp->ram_crc.STATUS->err);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CTS    ");
           if  (api->rsp->ram_crc.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->ram_crc.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                sprintf(msg,"%s%d", msg, api->rsp->ram_crc.STATUS->cts);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CRC    "); sprintf(msg,"%s%d", msg, api->rsp->ram_crc.crc);
     break;
    #endif /*     Si2158_RAM_CRC_CMD */

    #ifdef        Si2158_SET_PROPERTY_CMD
     case         Si2158_SET_PROPERTY_CMD_CODE:
      sprintf(msg,"SET_PROPERTY ");
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TUNINT   ");
           if  (api->rsp->set_property.STATUS->tunint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->set_property.STATUS->tunint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->set_property.STATUS->tunint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ATVINT   ");
           if  (api->rsp->set_property.STATUS->atvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->set_property.STATUS->atvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->set_property.STATUS->atvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DTVINT   ");
           if  (api->rsp->set_property.STATUS->dtvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->set_property.STATUS->dtvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->set_property.STATUS->dtvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ERR      ");
           if  (api->rsp->set_property.STATUS->err      ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->set_property.STATUS->err      ==     0) strcat(msg,"NO_ERROR");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->set_property.STATUS->err);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CTS      ");
           if  (api->rsp->set_property.STATUS->cts      ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->set_property.STATUS->cts      ==     0) strcat(msg,"WAIT     ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->set_property.STATUS->cts);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-RESERVED "); sprintf(msg,"%s%d", msg, api->rsp->set_property.reserved);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DATA     "); sprintf(msg,"%s%d", msg, api->rsp->set_property.data);
     break;
    #endif /*     Si2158_SET_PROPERTY_CMD */

    #ifdef        Si2158_STANDBY_CMD
     case         Si2158_STANDBY_CMD_CODE:
      sprintf(msg,"STANDBY ");
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TUNINT ");
           if  (api->rsp->standby.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->standby.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                sprintf(msg,"%s%d", msg, api->rsp->standby.STATUS->tunint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ATVINT ");
           if  (api->rsp->standby.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->standby.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                sprintf(msg,"%s%d", msg, api->rsp->standby.STATUS->atvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DTVINT ");
           if  (api->rsp->standby.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->standby.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                sprintf(msg,"%s%d", msg, api->rsp->standby.STATUS->dtvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ERR    ");
           if  (api->rsp->standby.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->standby.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                sprintf(msg,"%s%d", msg, api->rsp->standby.STATUS->err);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CTS    ");
           if  (api->rsp->standby.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->standby.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                sprintf(msg,"%s%d", msg, api->rsp->standby.STATUS->cts);
     break;
    #endif /*     Si2158_STANDBY_CMD */

    #ifdef        Si2158_TUNER_STATUS_CMD
     case         Si2158_TUNER_STATUS_CMD_CODE:
      sprintf(msg,"TUNER_STATUS ");
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TUNINT   ");
           if  (api->rsp->tuner_status.STATUS->tunint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->tuner_status.STATUS->tunint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->tuner_status.STATUS->tunint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ATVINT   ");
           if  (api->rsp->tuner_status.STATUS->atvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->tuner_status.STATUS->atvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->tuner_status.STATUS->atvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DTVINT   ");
           if  (api->rsp->tuner_status.STATUS->dtvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->tuner_status.STATUS->dtvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->tuner_status.STATUS->dtvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ERR      ");
           if  (api->rsp->tuner_status.STATUS->err      ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->tuner_status.STATUS->err      ==     0) strcat(msg,"NO_ERROR");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->tuner_status.STATUS->err);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CTS      ");
           if  (api->rsp->tuner_status.STATUS->cts      ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->tuner_status.STATUS->cts      ==     0) strcat(msg,"WAIT     ");
      else                                                       sprintf(msg,"%s%d", msg, api->rsp->tuner_status.STATUS->cts);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TCINT    ");
           if  (api->rsp->tuner_status.tcint    ==     1) strcat(msg,"CHANGED  ");
      else if  (api->rsp->tuner_status.tcint    ==     0) strcat(msg,"NO_CHANGE");
      else                                               sprintf(msg,"%s%d", msg, api->rsp->tuner_status.tcint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-RSSILINT ");
           if  (api->rsp->tuner_status.rssilint ==     1) strcat(msg,"CHANGED  ");
      else if  (api->rsp->tuner_status.rssilint ==     0) strcat(msg,"NO_CHANGE");
      else                                               sprintf(msg,"%s%d", msg, api->rsp->tuner_status.rssilint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-RSSIHINT ");
           if  (api->rsp->tuner_status.rssihint ==     1) strcat(msg,"CHANGED  ");
      else if  (api->rsp->tuner_status.rssihint ==     0) strcat(msg,"NO_CHANGE");
      else                                               sprintf(msg,"%s%d", msg, api->rsp->tuner_status.rssihint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TC       ");
           if  (api->rsp->tuner_status.tc       ==     0) strcat(msg,"BUSY");
      else if  (api->rsp->tuner_status.tc       ==     1) strcat(msg,"DONE");
      else                                               sprintf(msg,"%s%d", msg, api->rsp->tuner_status.tc);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-RSSIL    ");
           if  (api->rsp->tuner_status.rssil    ==     1) strcat(msg,"LOW");
      else if  (api->rsp->tuner_status.rssil    ==     0) strcat(msg,"OK ");
      else                                               sprintf(msg,"%s%d", msg, api->rsp->tuner_status.rssil);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-RSSIH    ");
           if  (api->rsp->tuner_status.rssih    ==     1) strcat(msg,"HIGH");
      else if  (api->rsp->tuner_status.rssih    ==     0) strcat(msg,"OK  ");
      else                                               sprintf(msg,"%s%d", msg, api->rsp->tuner_status.rssih);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-RSSI     "); sprintf(msg,"%s%d", msg, api->rsp->tuner_status.rssi);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-FREQ     "); sprintf(msg,"%s%ld", msg, api->rsp->tuner_status.freq);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-MODE     ");
           if  (api->rsp->tuner_status.mode     ==     1) strcat(msg,"ATV");
      else if  (api->rsp->tuner_status.mode     ==     0) strcat(msg,"DTV");
      else                                               sprintf(msg,"%s%d", msg, api->rsp->tuner_status.mode);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-VCO_CODE "); sprintf(msg,"%s%d", msg, api->rsp->tuner_status.vco_code);
     break;
    #endif /*     Si2158_TUNER_STATUS_CMD */

    #ifdef        Si2158_TUNER_TUNE_FREQ_CMD
     case         Si2158_TUNER_TUNE_FREQ_CMD_CODE:
      sprintf(msg,"TUNER_TUNE_FREQ ");
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TUNINT ");
           if  (api->rsp->tuner_tune_freq.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->tuner_tune_freq.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                        sprintf(msg,"%s%d", msg, api->rsp->tuner_tune_freq.STATUS->tunint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ATVINT ");
           if  (api->rsp->tuner_tune_freq.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->tuner_tune_freq.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                        sprintf(msg,"%s%d", msg, api->rsp->tuner_tune_freq.STATUS->atvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DTVINT ");
           if  (api->rsp->tuner_tune_freq.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->tuner_tune_freq.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                        sprintf(msg,"%s%d", msg, api->rsp->tuner_tune_freq.STATUS->dtvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ERR    ");
           if  (api->rsp->tuner_tune_freq.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->tuner_tune_freq.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                        sprintf(msg,"%s%d", msg, api->rsp->tuner_tune_freq.STATUS->err);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CTS    ");
           if  (api->rsp->tuner_tune_freq.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->tuner_tune_freq.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                        sprintf(msg,"%s%d", msg, api->rsp->tuner_tune_freq.STATUS->cts);
     break;
    #endif /*     Si2158_TUNER_TUNE_FREQ_CMD */

     default : break;
    }
    return 0;
  }
  /* _get_command_response_string_insertion_point */
#endif /* Si2158_GET_COMMAND_STRINGS */






