/*************************************************************************************
                  Silicon Laboratories Broadcast Si21XXC Layer 1 API

   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
     PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.

   API commands definitions
   FILE: Si21XXC_L1_Commands.c
   Supported IC : Si2178B,Si2190B,Si2191B,Si2191C
   Compiled for ROM 71 firmware 3_0_build_1
   Revision: 0.1
   Tag:  Si2190B_30b1_Si2178B_42b7_Si2191C_30b1_Si2191B_42b7_V0.1
   Date: August 12 2015
  (C) Copyright 2014, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#define   Si21XXC_COMMAND_PROTOTYPES

#include "Si21XXC_L1_API.h"

/******   conversion functions, used to fill command response fields ***************************************************
  These functions provide compatibility with 8 bytes processing on some compilers
 ***********************************************************************************************************************/
unsigned char Si21XXC_convert_to_byte (const unsigned char* buffer, unsigned char shift, unsigned char mask) {
  unsigned int rspBuffer = *buffer;
  return ((rspBuffer >> shift) & mask);
}
unsigned long Si21XXC_convert_to_ulong(const unsigned char* buffer, unsigned char shift,unsigned long mask) {
  return ((( ( (unsigned long)buffer[0]) | ((unsigned long)buffer[1] << 8) | ((unsigned long)buffer[2]<<16) | ((unsigned long)buffer[3]<<24)) >> shift) & mask );
}
unsigned int  Si21XXC_convert_to_uint (const unsigned char* buffer, unsigned char shift,unsigned int mask) {
  return (( ( (unsigned int)buffer[0]) | (((unsigned int)buffer[1]) << 8) >> shift) & mask);
}
short         Si21XXC_convert_to_int  (const unsigned char* buffer, unsigned char shift,unsigned int mask) {
  return (( ( (unsigned int)buffer[0]) | (((unsigned int)buffer[1]) << 8) >> shift) & mask);
}
/***********************************************************************************************************************
  Si21XXC_CurrentResponseStatus function
  Use:        status checking function
              Used to fill the Si21XXC_COMMON_REPLY_struct members with the ptDataBuffer byte's bits
  Comments:   The status byte definition being identical for all commands,
              using this function to fill the status structure helps reducing the code size
  Parameter: ptDataBuffer  a single byte received when reading a command's response (the first byte)
  Returns:   0 if the err bit (bit 6) is unset, 1 otherwise
 ***********************************************************************************************************************/
unsigned char Si21XXC_CurrentResponseStatus (L1_Si21XXC_Context *api, unsigned char ptDataBuffer)
{
    api->status->tunint =     Si21XXC_convert_to_byte(&ptDataBuffer, 0, 0x01);
    api->status->atvint =     Si21XXC_convert_to_byte(&ptDataBuffer, 1, 0x01);
    api->status->dtvint =     Si21XXC_convert_to_byte(&ptDataBuffer, 2, 0x01);
    api->status->err    =     Si21XXC_convert_to_byte(&ptDataBuffer, 6, 0x01);
    api->status->cts    =     Si21XXC_convert_to_byte(&ptDataBuffer, 7, 0x01);
  return (api->status->err ? ERROR_Si21XXC_ERR : NO_Si21XXC_ERROR);
}
/***********************************************************************************************************************
  Si21XXC_pollForResetState function
  Use:        ResetState checking function
              Used to check the status byte for the reset code (0xFE).
  Comments:   Only required for the Si21XXC_L1_POWER_DOWN_HW Command

  Returns:   0 if the Status byte is = 0xFE, nonzero otherwise
 ***********************************************************************************************************************/
unsigned char Si21XXC_pollForResetState (L1_Si21XXC_Context *api)
{
  unsigned char rspByteBuffer[1] = {0};
  unsigned int start_time;

  start_time = system_time();

  while (system_time() - start_time <1000)  { /* wait a maximum of 1000ms */
    if (L0_ReadCommandBytes(api->i2c, 1, rspByteBuffer) != 1) {
      SiTRACE("Si21XXC_pollForResetState ERROR reading byte 0!\n");
      return ERROR_Si21XXC_POLLING_CTS;
    }
    /* return OK if status=0xFE set */
    if (rspByteBuffer[0] == 0xFE) {
      return NO_Si21XXC_ERROR;
    }
  }

  SiTRACE("Si21XXC_pollForResetState ERROR status Timeout!\n");
  return ERROR_Si21XXC_CTS_TIMEOUT;
}
/***********************************************************************************************************************
  Si21XXC_pollForCTS function
  Use:        CTS checking function
              Used to check the CTS bit until it is set before sending the next command
  Comments:   The status byte definition being identical for all commands,
              using this function to fill the status structure helps reducing the code size
              max timeout = 1000 ms

  Returns:   1 if the CTS bit is set, 0 otherwise
 ***********************************************************************************************************************/
unsigned char Si21XXC_pollForCTS (L1_Si21XXC_Context *api)
{
  unsigned char rspByteBuffer[1]={0};
  unsigned int start_time;

  start_time = system_time();

  while (system_time() - start_time <1000)  { /* wait a maximum of 1000ms */
    if (L0_ReadCommandBytes(api->i2c, 1, rspByteBuffer) != 1) {
      SiTRACE("Si21XXC_pollForCTS ERROR reading byte 0!\n");
      return ERROR_Si21XXC_POLLING_CTS;
    }
    /* return OK if CTS set */
    if (rspByteBuffer[0] & 0x80) {
      return NO_Si21XXC_ERROR;
    }
  }

  SiTRACE("Si21XXC_pollForCTS ERROR CTS Timeout!\n");
  return ERROR_Si21XXC_CTS_TIMEOUT;
}

/***********************************************************************************************************************
  Si21XXC_pollForResponse function
  Use:        command response retrieval function
              Used to retrieve the command response in the provided buffer
  Comments:   The status byte definition being identical for all commands,
              using this function to fill the status structure helps reducing the code size
              max timeout = 1000 ms

  Parameter:  nbBytes          the number of response bytes to read
  Parameter:  pByteBuffer      a buffer into which bytes will be stored
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/
unsigned char Si21XXC_pollForResponse (L1_Si21XXC_Context *api, unsigned int nbBytes, unsigned char *pByteBuffer)
{
  unsigned char debugBuffer[7];
  unsigned int start_time;

  start_time = system_time();

  while (system_time() - start_time <1000)  { /* wait a maximum of 1000ms */
    if ((unsigned int)L0_ReadCommandBytes(api->i2c, nbBytes, pByteBuffer) != nbBytes) {
      SiTRACE("Si21XXC_pollForResponse ERROR reading byte 0!\n");
      return ERROR_Si21XXC_POLLING_RESPONSE;
    }
    /* return response err flag if CTS set */
    if (pByteBuffer[0] & 0x80)  {
     if (pByteBuffer[0] & 0x40)  {
        L0_ReadCommandBytes(api->i2c, 7, &(debugBuffer[0]) );
        SiTRACE("Si21XXC debug bytes 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n", debugBuffer[0], debugBuffer[1], debugBuffer[2], debugBuffer[3], debugBuffer[4], debugBuffer[5], debugBuffer[6]);
      }
      return Si21XXC_CurrentResponseStatus(api, pByteBuffer[0]);
    }
  }

  SiTRACE("Si21XXC_pollForResponse ERROR CTS Timeout!\n");
  return ERROR_Si21XXC_CTS_TIMEOUT;
}

#ifdef    Si21XXC_AGC_OVERRIDE_CMD
 /*---------------------------------------------------*/
/* Si21XXC_AGC_OVERRIDE COMMAND                     */
/*---------------------------------------------------*/
unsigned char Si21XXC_L1_AGC_OVERRIDE      (L1_Si21XXC_Context *api,
                                           unsigned char   force_max_gain,
                                           unsigned char   force_top_gain)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[1];
    api->rsp->agc_override.STATUS = api->status;

    SiTRACE("Si21XXC AGC_OVERRIDE ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((force_max_gain > Si21XXC_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FORCE_MAX_GAIN %d ", force_max_gain );
    if ((force_top_gain > Si21XXC_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FORCE_TOP_GAIN %d ", force_top_gain );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si21XXC_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si21XXC_AGC_OVERRIDE_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( force_max_gain & Si21XXC_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_MASK ) << Si21XXC_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_LSB|
                                         ( force_top_gain & Si21XXC_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_MASK ) << Si21XXC_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing AGC_OVERRIDE bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling AGC_OVERRIDE response\n");
      return error_code;
    }


    return NO_Si21XXC_ERROR;
}
#endif /* Si21XXC_AGC_OVERRIDE_CMD */
#ifdef    Si21XXC_ATV_RESTART_CMD
 /*---------------------------------------------------*/
/* Si21XXC_ATV_RESTART COMMAND                      */
/*---------------------------------------------------*/
unsigned char Si21XXC_L1_ATV_RESTART       (L1_Si21XXC_Context *api,
                                           unsigned char   mode)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[1];
    api->rsp->atv_restart.STATUS = api->status;

    SiTRACE("Si21XXC ATV_RESTART ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((mode > Si21XXC_ATV_RESTART_CMD_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("MODE %d ", mode );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si21XXC_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si21XXC_ATV_RESTART_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( mode & Si21XXC_ATV_RESTART_CMD_MODE_MASK ) << Si21XXC_ATV_RESTART_CMD_MODE_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing ATV_RESTART bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling ATV_RESTART response\n");
      return error_code;
    }


    return NO_Si21XXC_ERROR;
}
#endif /* Si21XXC_ATV_RESTART_CMD */
#ifdef    Si21XXC_ATV_STATUS_CMD
 /*---------------------------------------------------*/
/* Si21XXC_ATV_STATUS COMMAND                       */
/*---------------------------------------------------*/
unsigned char Si21XXC_L1_ATV_STATUS        (L1_Si21XXC_Context *api,
                                           unsigned char   intack)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[12];
    api->rsp->atv_status.STATUS = api->status;

    SiTRACE("Si21XXC ATV_STATUS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((intack > Si21XXC_ATV_STATUS_CMD_INTACK_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("INTACK %d ", intack );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si21XXC_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si21XXC_ATV_STATUS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( intack & Si21XXC_ATV_STATUS_CMD_INTACK_MASK ) << Si21XXC_ATV_STATUS_CMD_INTACK_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing ATV_STATUS bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 12, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling ATV_STATUS response\n");
      return error_code;
    }

    api->rsp->atv_status.chlint           = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si21XXC_ATV_STATUS_RESPONSE_CHLINT_LSB            , Si21XXC_ATV_STATUS_RESPONSE_CHLINT_MASK           );
    api->rsp->atv_status.pclint           = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si21XXC_ATV_STATUS_RESPONSE_PCLINT_LSB            , Si21XXC_ATV_STATUS_RESPONSE_PCLINT_MASK           );
    api->rsp->atv_status.dlint            = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si21XXC_ATV_STATUS_RESPONSE_DLINT_LSB             , Si21XXC_ATV_STATUS_RESPONSE_DLINT_MASK            );
    api->rsp->atv_status.snrlint          = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si21XXC_ATV_STATUS_RESPONSE_SNRLINT_LSB           , Si21XXC_ATV_STATUS_RESPONSE_SNRLINT_MASK          );
    api->rsp->atv_status.snrhint          = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si21XXC_ATV_STATUS_RESPONSE_SNRHINT_LSB           , Si21XXC_ATV_STATUS_RESPONSE_SNRHINT_MASK          );
    api->rsp->atv_status.chl              = Si21XXC_convert_to_byte  (&rspByteBuffer[ 2] , Si21XXC_ATV_STATUS_RESPONSE_CHL_LSB               , Si21XXC_ATV_STATUS_RESPONSE_CHL_MASK              );
    api->rsp->atv_status.pcl              = Si21XXC_convert_to_byte  (&rspByteBuffer[ 2] , Si21XXC_ATV_STATUS_RESPONSE_PCL_LSB               , Si21XXC_ATV_STATUS_RESPONSE_PCL_MASK              );
    api->rsp->atv_status.dl               = Si21XXC_convert_to_byte  (&rspByteBuffer[ 2] , Si21XXC_ATV_STATUS_RESPONSE_DL_LSB                , Si21XXC_ATV_STATUS_RESPONSE_DL_MASK               );
    api->rsp->atv_status.snrl             = Si21XXC_convert_to_byte  (&rspByteBuffer[ 2] , Si21XXC_ATV_STATUS_RESPONSE_SNRL_LSB              , Si21XXC_ATV_STATUS_RESPONSE_SNRL_MASK             );
    api->rsp->atv_status.snrh             = Si21XXC_convert_to_byte  (&rspByteBuffer[ 2] , Si21XXC_ATV_STATUS_RESPONSE_SNRH_LSB              , Si21XXC_ATV_STATUS_RESPONSE_SNRH_MASK             );
    api->rsp->atv_status.video_snr        = Si21XXC_convert_to_byte  (&rspByteBuffer[ 3] , Si21XXC_ATV_STATUS_RESPONSE_VIDEO_SNR_LSB         , Si21XXC_ATV_STATUS_RESPONSE_VIDEO_SNR_MASK        );
    api->rsp->atv_status.afc_freq         = Si21XXC_convert_to_int   (&rspByteBuffer[ 4] , Si21XXC_ATV_STATUS_RESPONSE_AFC_FREQ_LSB          , Si21XXC_ATV_STATUS_RESPONSE_AFC_FREQ_MASK         );
    api->rsp->atv_status.video_sc_spacing = Si21XXC_convert_to_int   (&rspByteBuffer[ 6] , Si21XXC_ATV_STATUS_RESPONSE_VIDEO_SC_SPACING_LSB  , Si21XXC_ATV_STATUS_RESPONSE_VIDEO_SC_SPACING_MASK );
    api->rsp->atv_status.video_sys        = Si21XXC_convert_to_byte  (&rspByteBuffer[ 8] , Si21XXC_ATV_STATUS_RESPONSE_VIDEO_SYS_LSB         , Si21XXC_ATV_STATUS_RESPONSE_VIDEO_SYS_MASK        );
    api->rsp->atv_status.color            = Si21XXC_convert_to_byte  (&rspByteBuffer[ 8] , Si21XXC_ATV_STATUS_RESPONSE_COLOR_LSB             , Si21XXC_ATV_STATUS_RESPONSE_COLOR_MASK            );
    api->rsp->atv_status.lines            = Si21XXC_convert_to_byte  (&rspByteBuffer[ 8] , Si21XXC_ATV_STATUS_RESPONSE_LINES_LSB             , Si21XXC_ATV_STATUS_RESPONSE_LINES_MASK            );
    api->rsp->atv_status.audio_sys        = Si21XXC_convert_to_byte  (&rspByteBuffer[ 9] , Si21XXC_ATV_STATUS_RESPONSE_AUDIO_SYS_LSB         , Si21XXC_ATV_STATUS_RESPONSE_AUDIO_SYS_MASK        );
    api->rsp->atv_status.audio_chan_bw    = Si21XXC_convert_to_byte  (&rspByteBuffer[10] , Si21XXC_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_LSB     , Si21XXC_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_MASK    );
    api->rsp->atv_status.sound_level      = Si21XXC_convert_to_byte  (&rspByteBuffer[11] , Si21XXC_ATV_STATUS_RESPONSE_SOUND_LEVEL_LSB       , Si21XXC_ATV_STATUS_RESPONSE_SOUND_LEVEL_MASK      );

    return NO_Si21XXC_ERROR;
}
#endif /* Si21XXC_ATV_STATUS_CMD */
#ifdef    Si21XXC_CONFIG_CLOCKS_CMD
 /*---------------------------------------------------*/
/* Si21XXC_CONFIG_CLOCKS COMMAND                    */
/*---------------------------------------------------*/
unsigned char Si21XXC_L1_CONFIG_CLOCKS     (L1_Si21XXC_Context *api,
                                           unsigned char   subcode,
                                           unsigned char   clock_mode,
                                           unsigned char   en_xout)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[3];
    unsigned char rspByteBuffer[1];
    api->rsp->config_clocks.STATUS = api->status;

    SiTRACE("Si21XXC CONFIG_CLOCKS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode    > Si21XXC_CONFIG_CLOCKS_CMD_SUBCODE_MAX   ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "   , subcode    );
    if ((clock_mode > Si21XXC_CONFIG_CLOCKS_CMD_CLOCK_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CLOCK_MODE %d ", clock_mode );
    if ((en_xout    > Si21XXC_CONFIG_CLOCKS_CMD_EN_XOUT_MAX   ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("EN_XOUT %d "   , en_xout    );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si21XXC_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si21XXC_CONFIG_CLOCKS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode    & Si21XXC_CONFIG_CLOCKS_CMD_SUBCODE_MASK    ) << Si21XXC_CONFIG_CLOCKS_CMD_SUBCODE_LSB   );
    cmdByteBuffer[2] = (unsigned char) ( ( clock_mode & Si21XXC_CONFIG_CLOCKS_CMD_CLOCK_MODE_MASK ) << Si21XXC_CONFIG_CLOCKS_CMD_CLOCK_MODE_LSB|
                                         ( en_xout    & Si21XXC_CONFIG_CLOCKS_CMD_EN_XOUT_MASK    ) << Si21XXC_CONFIG_CLOCKS_CMD_EN_XOUT_LSB   );

    if (L0_WriteCommandBytes(api->i2c, 3, cmdByteBuffer) != 3) {
      SiTRACE("Error writing CONFIG_CLOCKS bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling CONFIG_CLOCKS response\n");
      return error_code;
    }


    return NO_Si21XXC_ERROR;
}
#endif /* Si21XXC_CONFIG_CLOCKS_CMD */
#ifdef    Si21XXC_CONFIG_I2C_CMD
/*---------------------------------------------------*/
/* Si21XXC_CONFIG_I2C COMMAND                               */
/*---------------------------------------------------*/
unsigned char Si21XXC_L1_CONFIG_I2C        (L1_Si21XXC_Context *api,
                                           unsigned char   subcode,
                                           unsigned char   i2c_broadcast)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[3];
    unsigned char rspByteBuffer[1];

    api->rsp->config_i2c.STATUS = api->status;

    SiTRACE("Si21XXC CONFIG_I2C ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode       > Si21XXC_CONFIG_I2C_CMD_SUBCODE_MAX      )  || (subcode       < Si21XXC_CONFIG_I2C_CMD_SUBCODE_MIN      ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "      , subcode       );
    if ((i2c_broadcast > Si21XXC_CONFIG_I2C_CMD_I2C_BROADCAST_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("I2C_BROADCAST %d ", i2c_broadcast );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si21XXC_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si21XXC_CONFIG_I2C_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode       & Si21XXC_CONFIG_I2C_CMD_SUBCODE_MASK       ) << Si21XXC_CONFIG_I2C_CMD_SUBCODE_LSB      );
    cmdByteBuffer[2] = (unsigned char) ( ( i2c_broadcast & Si21XXC_CONFIG_I2C_CMD_I2C_BROADCAST_MASK ) << Si21XXC_CONFIG_I2C_CMD_I2C_BROADCAST_LSB);

    if (L0_WriteCommandBytes(api->i2c, 3, cmdByteBuffer) != 3) {
      SiTRACE("Error writing CONFIG_I2C bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling CONFIG_CLOCKS response\n");
      return error_code;
    }

    return NO_Si21XXC_ERROR;
}
#endif /* Si21XXC_CONFIG_I2C_CMD */

#ifdef    Si2190B_CONFIG_PINS_CMD
 /*---------------------------------------------------*/
/* Si2190B_CONFIG_PINS COMMAND   For Si2190B and Si2191C            */
/*---------------------------------------------------*/
unsigned char Si2190B_L1_CONFIG_PINS       (L1_Si21XXC_Context *api,
                                           unsigned char   gpio1_mode,
                                           unsigned char   gpio1_read,
                                           unsigned char   gpio2_mode,
                                           unsigned char   gpio2_read,
                                           unsigned char   agc1_mode,
                                           unsigned char   agc1_read,
                                           unsigned char   agc2_mode,
                                           unsigned char   agc2_read,
                                           unsigned char   reserved3)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[6];
    unsigned char rspByteBuffer[5];
    api->rsp->config_pins.STATUS = api->status;

    SiTRACE("Si2190B CONFIG_PINS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((gpio1_mode > Si2190B_CONFIG_PINS_CMD_GPIO1_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO1_MODE %d ", gpio1_mode );
    if ((gpio1_read > Si2190B_CONFIG_PINS_CMD_GPIO1_READ_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO1_READ %d ", gpio1_read );
    if ((gpio2_mode > Si2190B_CONFIG_PINS_CMD_GPIO2_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO2_MODE %d ", gpio2_mode );
    if ((gpio2_read > Si2190B_CONFIG_PINS_CMD_GPIO2_READ_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO2_READ %d ", gpio2_read );
    if ((agc1_mode  > Si2190B_CONFIG_PINS_CMD_AGC1_MODE_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("AGC1_MODE %d " , agc1_mode  );
    if ((agc1_read  > Si2190B_CONFIG_PINS_CMD_AGC1_READ_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("AGC1_READ %d " , agc1_read  );
    if ((agc2_mode  > Si2190B_CONFIG_PINS_CMD_AGC2_MODE_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("AGC2_MODE %d " , agc2_mode  );
    if ((agc2_read  > Si2190B_CONFIG_PINS_CMD_AGC2_READ_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("AGC2_READ %d " , agc2_read  );
    if ((reserved3  > Si2190B_CONFIG_PINS_CMD_RESERVED3_MAX )  || (reserved3  < Si2190B_CONFIG_PINS_CMD_RESERVED3_MIN ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED3 %d " , reserved3  );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si21XXC_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2190B_CONFIG_PINS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( gpio1_mode & Si2190B_CONFIG_PINS_CMD_GPIO1_MODE_MASK ) << Si2190B_CONFIG_PINS_CMD_GPIO1_MODE_LSB|
                                         ( gpio1_read & Si2190B_CONFIG_PINS_CMD_GPIO1_READ_MASK ) << Si2190B_CONFIG_PINS_CMD_GPIO1_READ_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( gpio2_mode & Si2190B_CONFIG_PINS_CMD_GPIO2_MODE_MASK ) << Si2190B_CONFIG_PINS_CMD_GPIO2_MODE_LSB|
                                         ( gpio2_read & Si2190B_CONFIG_PINS_CMD_GPIO2_READ_MASK ) << Si2190B_CONFIG_PINS_CMD_GPIO2_READ_LSB);
    cmdByteBuffer[3] = (unsigned char) ( ( agc1_mode  & Si2190B_CONFIG_PINS_CMD_AGC1_MODE_MASK  ) << Si2190B_CONFIG_PINS_CMD_AGC1_MODE_LSB |
                                         ( agc1_read  & Si2190B_CONFIG_PINS_CMD_AGC1_READ_MASK  ) << Si2190B_CONFIG_PINS_CMD_AGC1_READ_LSB );
    cmdByteBuffer[4] = (unsigned char) ( ( agc2_mode  & Si2190B_CONFIG_PINS_CMD_AGC2_MODE_MASK  ) << Si2190B_CONFIG_PINS_CMD_AGC2_MODE_LSB |
                                         ( agc2_read  & Si2190B_CONFIG_PINS_CMD_AGC2_READ_MASK  ) << Si2190B_CONFIG_PINS_CMD_AGC2_READ_LSB );
    cmdByteBuffer[5] = (unsigned char) ( ( reserved3  & Si2190B_CONFIG_PINS_CMD_RESERVED3_MASK  ) << Si2190B_CONFIG_PINS_CMD_RESERVED3_LSB );

    if (L0_WriteCommandBytes(api->i2c, 6, cmdByteBuffer) != 6) {
      SiTRACE("Error writing CONFIG_PINS bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 5, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling CONFIG_PINS response\n");
      return error_code;
    }

    api->rsp->config_pins.gpio1_mode  = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si2190B_CONFIG_PINS_RESPONSE_GPIO1_MODE_LSB   , Si2190B_CONFIG_PINS_RESPONSE_GPIO1_MODE_MASK  );
    api->rsp->config_pins.gpio1_state = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si2190B_CONFIG_PINS_RESPONSE_GPIO1_STATE_LSB  , Si2190B_CONFIG_PINS_RESPONSE_GPIO1_STATE_MASK );
    api->rsp->config_pins.gpio2_mode  = Si21XXC_convert_to_byte  (&rspByteBuffer[ 2] , Si2190B_CONFIG_PINS_RESPONSE_GPIO2_MODE_LSB   , Si2190B_CONFIG_PINS_RESPONSE_GPIO2_MODE_MASK  );
    api->rsp->config_pins.gpio2_state = Si21XXC_convert_to_byte  (&rspByteBuffer[ 2] , Si2190B_CONFIG_PINS_RESPONSE_GPIO2_STATE_LSB  , Si2190B_CONFIG_PINS_RESPONSE_GPIO2_STATE_MASK );
    api->rsp->config_pins.agc1_mode   = Si21XXC_convert_to_byte  (&rspByteBuffer[ 3] , Si2190B_CONFIG_PINS_RESPONSE_AGC1_MODE_LSB    , Si2190B_CONFIG_PINS_RESPONSE_AGC1_MODE_MASK   );
    api->rsp->config_pins.agc1_state  = Si21XXC_convert_to_byte  (&rspByteBuffer[ 3] , Si2190B_CONFIG_PINS_RESPONSE_AGC1_STATE_LSB   , Si2190B_CONFIG_PINS_RESPONSE_AGC1_STATE_MASK  );
    api->rsp->config_pins.agc2_mode   = Si21XXC_convert_to_byte  (&rspByteBuffer[ 4] , Si2190B_CONFIG_PINS_RESPONSE_AGC2_MODE_LSB    , Si2190B_CONFIG_PINS_RESPONSE_AGC2_MODE_MASK   );
    api->rsp->config_pins.agc2_state  = Si21XXC_convert_to_byte  (&rspByteBuffer[ 4] , Si2190B_CONFIG_PINS_RESPONSE_AGC2_STATE_LSB   , Si2190B_CONFIG_PINS_RESPONSE_AGC2_STATE_MASK  );

    return NO_Si21XXC_ERROR;
}
#endif /* Si2190B_CONFIG_PINS_CMD */

#ifdef    Si2178B_CONFIG_PINS_CMD
 /*---------------------------------------------------*/
/* Si2178B_CONFIG_PINS COMMAND  For Si2178B and Si2191B               */
/*---------------------------------------------------*/
unsigned char Si2178B_L1_CONFIG_PINS     (L1_Si21XXC_Context *api,
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
    unsigned char rspByteBuffer[6];
    api->rsp->config_pins.STATUS = api->status;

    SiTRACE("Si2178B CONFIG_PINS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((gpio1_mode > Si2178B_CONFIG_PINS_CMD_GPIO1_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO1_MODE %d ", gpio1_mode );
    if ((gpio1_read > Si2178B_CONFIG_PINS_CMD_GPIO1_READ_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO1_READ %d ", gpio1_read );
    if ((gpio2_mode > Si2178B_CONFIG_PINS_CMD_GPIO2_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO2_MODE %d ", gpio2_mode );
    if ((gpio2_read > Si2178B_CONFIG_PINS_CMD_GPIO2_READ_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO2_READ %d ", gpio2_read );
    if ((reserved1  > Si2178B_CONFIG_PINS_CMD_RESERVED1_MAX )  || (reserved1  < Si2178B_CONFIG_PINS_CMD_RESERVED1_MIN ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED1 %d " , reserved1  );
    if ((reserved2  > Si2178B_CONFIG_PINS_CMD_RESERVED2_MAX )  || (reserved2  < Si2178B_CONFIG_PINS_CMD_RESERVED2_MIN ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED2 %d " , reserved2  );
    if ((reserved3  > Si2178B_CONFIG_PINS_CMD_RESERVED3_MAX )  || (reserved3  < Si2178B_CONFIG_PINS_CMD_RESERVED3_MIN ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED3 %d " , reserved3  );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2178B_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2178B_CONFIG_PINS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( gpio1_mode & Si2178B_CONFIG_PINS_CMD_GPIO1_MODE_MASK ) << Si2178B_CONFIG_PINS_CMD_GPIO1_MODE_LSB|
                                         ( gpio1_read & Si2178B_CONFIG_PINS_CMD_GPIO1_READ_MASK ) << Si2178B_CONFIG_PINS_CMD_GPIO1_READ_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( gpio2_mode & Si2178B_CONFIG_PINS_CMD_GPIO2_MODE_MASK ) << Si2178B_CONFIG_PINS_CMD_GPIO2_MODE_LSB|
                                         ( gpio2_read & Si2178B_CONFIG_PINS_CMD_GPIO2_READ_MASK ) << Si2178B_CONFIG_PINS_CMD_GPIO2_READ_LSB);
    cmdByteBuffer[3] = (unsigned char) ( ( reserved1  & Si2178B_CONFIG_PINS_CMD_RESERVED1_MASK  ) << Si2178B_CONFIG_PINS_CMD_RESERVED1_LSB );
    cmdByteBuffer[4] = (unsigned char) ( ( reserved2  & Si2178B_CONFIG_PINS_CMD_RESERVED2_MASK  ) << Si2178B_CONFIG_PINS_CMD_RESERVED2_LSB );
    cmdByteBuffer[5] = (unsigned char) ( ( reserved3  & Si2178B_CONFIG_PINS_CMD_RESERVED3_MASK  ) << Si2178B_CONFIG_PINS_CMD_RESERVED3_LSB );

    if (L0_WriteCommandBytes(api->i2c, 6, cmdByteBuffer) != 6) {
      SiTRACE("Error writing CONFIG_PINS bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 6, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling CONFIG_PINS response\n");
      return error_code;
    }

    api->rsp->config_pins.gpio1_mode  = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si2178B_CONFIG_PINS_RESPONSE_GPIO1_MODE_LSB   , Si2178B_CONFIG_PINS_RESPONSE_GPIO1_MODE_MASK  );
    api->rsp->config_pins.gpio1_state = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si2178B_CONFIG_PINS_RESPONSE_GPIO1_STATE_LSB  , Si2178B_CONFIG_PINS_RESPONSE_GPIO1_STATE_MASK );
    api->rsp->config_pins.gpio2_mode  = Si21XXC_convert_to_byte  (&rspByteBuffer[ 2] , Si2178B_CONFIG_PINS_RESPONSE_GPIO2_MODE_LSB   , Si2178B_CONFIG_PINS_RESPONSE_GPIO2_MODE_MASK  );
    api->rsp->config_pins.gpio2_state = Si21XXC_convert_to_byte  (&rspByteBuffer[ 2] , Si2178B_CONFIG_PINS_RESPONSE_GPIO2_STATE_LSB  , Si2178B_CONFIG_PINS_RESPONSE_GPIO2_STATE_MASK );
    api->rsp->config_pins.reserved1   = Si21XXC_convert_to_byte  (&rspByteBuffer[ 3] , Si2178B_CONFIG_PINS_RESPONSE_RESERVED1_LSB    , Si2178B_CONFIG_PINS_RESPONSE_RESERVED1_MASK   );
    api->rsp->config_pins.reserved2   = Si21XXC_convert_to_byte  (&rspByteBuffer[ 4] , Si2178B_CONFIG_PINS_RESPONSE_RESERVED2_LSB    , Si2178B_CONFIG_PINS_RESPONSE_RESERVED2_MASK   );
    api->rsp->config_pins.reserved3   = Si21XXC_convert_to_byte  (&rspByteBuffer[ 5] , Si2178B_CONFIG_PINS_RESPONSE_RESERVED3_LSB    , Si2178B_CONFIG_PINS_RESPONSE_RESERVED3_MASK   );

    return NO_Si21XXC_ERROR;
}
#endif /* Si2178B_CONFIG_PINS_CMD */

#ifdef    Si21XXC_DTV_RESTART_CMD
 /*---------------------------------------------------*/
/* Si21XXC_DTV_RESTART COMMAND                      */
/*---------------------------------------------------*/
unsigned char Si21XXC_L1_DTV_RESTART       (L1_Si21XXC_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[1];
    api->rsp->dtv_restart.STATUS = api->status;

    SiTRACE("Si21XXC DTV_RESTART ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si21XXC_DTV_RESTART_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing DTV_RESTART bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DTV_RESTART response\n");
      return error_code;
    }


    return NO_Si21XXC_ERROR;
}
#endif /* Si21XXC_DTV_RESTART_CMD */
#ifdef    Si21XXC_DTV_STATUS_CMD
 /*---------------------------------------------------*/
/* Si21XXC_DTV_STATUS COMMAND                       */
/*---------------------------------------------------*/
unsigned char Si21XXC_L1_DTV_STATUS        (L1_Si21XXC_Context *api,
                                           unsigned char   intack)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[4];
    api->rsp->dtv_status.STATUS = api->status;

    SiTRACE("Si21XXC DTV_STATUS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((intack > Si21XXC_DTV_STATUS_CMD_INTACK_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("INTACK %d ", intack );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si21XXC_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si21XXC_DTV_STATUS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( intack & Si21XXC_DTV_STATUS_CMD_INTACK_MASK ) << Si21XXC_DTV_STATUS_CMD_INTACK_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing DTV_STATUS bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 4, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling DTV_STATUS response\n");
      return error_code;
    }

    api->rsp->dtv_status.chlint     = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si21XXC_DTV_STATUS_RESPONSE_CHLINT_LSB      , Si21XXC_DTV_STATUS_RESPONSE_CHLINT_MASK     );
    api->rsp->dtv_status.chl        = Si21XXC_convert_to_byte  (&rspByteBuffer[ 2] , Si21XXC_DTV_STATUS_RESPONSE_CHL_LSB         , Si21XXC_DTV_STATUS_RESPONSE_CHL_MASK        );
    api->rsp->dtv_status.bw         = Si21XXC_convert_to_byte  (&rspByteBuffer[ 3] , Si21XXC_DTV_STATUS_RESPONSE_BW_LSB          , Si21XXC_DTV_STATUS_RESPONSE_BW_MASK         );
    api->rsp->dtv_status.modulation = Si21XXC_convert_to_byte  (&rspByteBuffer[ 3] , Si21XXC_DTV_STATUS_RESPONSE_MODULATION_LSB  , Si21XXC_DTV_STATUS_RESPONSE_MODULATION_MASK );

    return NO_Si21XXC_ERROR;
}
#endif /* Si21XXC_DTV_STATUS_CMD */
#ifdef    Si2178B_ENABLE_SSVD_ATV_CMD
/*---------------------------------------------------*/
/* Si2178B_ENABLE_SSVD_ATV COMMAND for Si2178B and Si2191B                  */
/*---------------------------------------------------*/
unsigned char Si2178B_L1_ENABLE_SSVD_ATV (L1_Si21XXC_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[1];
    api->rsp->enable_ssvd_atv.STATUS = api->status;

    SiTRACE("Si2178B ENABLE_SSVD_ATV ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2178B_ENABLE_SSVD_ATV_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing ENABLE_SSVD_ATV bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling ENABLE_SSVD_ATV response\n");
      return error_code;
    }


    return NO_Si21XXC_ERROR;
}
#endif /* Si2178B_ENABLE_SSVD_ATV_CMD */
#ifdef    Si21XXC_EXIT_BOOTLOADER_CMD
 /*---------------------------------------------------*/
/* Si21XXC_EXIT_BOOTLOADER COMMAND                  */
/*---------------------------------------------------*/
unsigned char Si21XXC_L1_EXIT_BOOTLOADER   (L1_Si21XXC_Context *api,
                                           unsigned char   func,
                                           unsigned char   ctsien)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[1];
    api->rsp->exit_bootloader.STATUS = api->status;

    SiTRACE("Si21XXC EXIT_BOOTLOADER ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((func   > Si21XXC_EXIT_BOOTLOADER_CMD_FUNC_MAX  )  || (func   < Si21XXC_EXIT_BOOTLOADER_CMD_FUNC_MIN  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FUNC %d "  , func   );
    if ((ctsien > Si21XXC_EXIT_BOOTLOADER_CMD_CTSIEN_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CTSIEN %d ", ctsien );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si21XXC_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si21XXC_EXIT_BOOTLOADER_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( func   & Si21XXC_EXIT_BOOTLOADER_CMD_FUNC_MASK   ) << Si21XXC_EXIT_BOOTLOADER_CMD_FUNC_LSB  |
                                         ( ctsien & Si21XXC_EXIT_BOOTLOADER_CMD_CTSIEN_MASK ) << Si21XXC_EXIT_BOOTLOADER_CMD_CTSIEN_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing EXIT_BOOTLOADER bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling EXIT_BOOTLOADER response\n");
      return error_code;
    }


    return NO_Si21XXC_ERROR;
}
#endif /* Si21XXC_EXIT_BOOTLOADER_CMD */
#ifdef    Si2178B_FINE_TUNE_CMD
 /*---------------------------------------------------*/
/* Si2178B_FINE_TUNE COMMAND                        */
/*---------------------------------------------------*/
unsigned char Si2178B_L1_FINE_TUNE       (L1_Si21XXC_Context *api,
                                         unsigned char   persistence,
                                         unsigned char   apply_to_lif,
                                                   int   offset_500hz)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[4];
    unsigned char rspByteBuffer[1];
    api->rsp->fine_tune.STATUS = api->status;

    SiTRACE("Si2178B FINE_TUNE ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((persistence  > Si2178B_FINE_TUNE_CMD_PERSISTENCE_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("PERSISTENCE %d " , persistence  );
    if ((apply_to_lif > Si2178B_FINE_TUNE_CMD_APPLY_TO_LIF_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("APPLY_TO_LIF %d ", apply_to_lif );
    if ((offset_500hz > Si2178B_FINE_TUNE_CMD_OFFSET_500HZ_MAX)  || (offset_500hz < Si2178B_FINE_TUNE_CMD_OFFSET_500HZ_MIN) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("OFFSET_500HZ %d ", offset_500hz );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si21XXC_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2178B_FINE_TUNE_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( persistence  & Si2178B_FINE_TUNE_CMD_PERSISTENCE_MASK  ) << Si2178B_FINE_TUNE_CMD_PERSISTENCE_LSB |
                                         ( apply_to_lif & Si2178B_FINE_TUNE_CMD_APPLY_TO_LIF_MASK ) << Si2178B_FINE_TUNE_CMD_APPLY_TO_LIF_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( offset_500hz & Si2178B_FINE_TUNE_CMD_OFFSET_500HZ_MASK ) << Si2178B_FINE_TUNE_CMD_OFFSET_500HZ_LSB);
    cmdByteBuffer[3] = (unsigned char) ((( offset_500hz & Si2178B_FINE_TUNE_CMD_OFFSET_500HZ_MASK ) << Si2178B_FINE_TUNE_CMD_OFFSET_500HZ_LSB)>>8);

    if (L0_WriteCommandBytes(api->i2c, 4, cmdByteBuffer) != 4) {
      SiTRACE("Error writing FINE_TUNE bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling FINE_TUNE response\n");
      return error_code;
    }


    return NO_Si21XXC_ERROR;
}
#endif /* Si2178B_FINE_TUNE_CMD */

#ifdef    Si21XXC_FINE_TUNE_CMD
 /*---------------------------------------------------*/
/* Si21XXC_FINE_TUNE COMMAND   Note the apply_to_lif parameter is removed for Si2178B.    */
/*   For an Si2178B it is forced to apply_to_lif=1.  Refer to the cmdByteBuffer[1] statement below.          */
/*---------------------------------------------------*/
unsigned char Si21XXC_L1_FINE_TUNE         (L1_Si21XXC_Context *api,
                                           unsigned char   persistence,
                                                     int   offset_500hz)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[4];
    unsigned char rspByteBuffer[1];
    api->rsp->fine_tune.STATUS = api->status;

    SiTRACE("Si21XXC FINE_TUNE ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((persistence  > Si21XXC_FINE_TUNE_CMD_PERSISTENCE_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("PERSISTENCE %d " , persistence  );
    if ((offset_500hz > Si21XXC_FINE_TUNE_CMD_OFFSET_500HZ_MAX)  || (offset_500hz < Si21XXC_FINE_TUNE_CMD_OFFSET_500HZ_MIN) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("OFFSET_500HZ %d ", offset_500hz );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si21XXC_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si21XXC_FINE_TUNE_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( persistence  & Si21XXC_FINE_TUNE_CMD_PERSISTENCE_MASK  ) << Si21XXC_FINE_TUNE_CMD_PERSISTENCE_LSB );
    cmdByteBuffer[2] = (unsigned char) ( ( offset_500hz & Si21XXC_FINE_TUNE_CMD_OFFSET_500HZ_MASK ) << Si21XXC_FINE_TUNE_CMD_OFFSET_500HZ_LSB);
    cmdByteBuffer[3] = (unsigned char) ((( offset_500hz & Si21XXC_FINE_TUNE_CMD_OFFSET_500HZ_MASK ) << Si21XXC_FINE_TUNE_CMD_OFFSET_500HZ_LSB)>>8);

    if (L0_WriteCommandBytes(api->i2c, 4, cmdByteBuffer) != 4) {
      SiTRACE("Error writing FINE_TUNE bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling FINE_TUNE response\n");
      return error_code;
    }


    return NO_Si21XXC_ERROR;
}
#endif /* Si21XXC_FINE_TUNE_CMD */
#ifdef    Si21XXC_GET_PROPERTY_CMD
 /*---------------------------------------------------*/
/* Si21XXC_GET_PROPERTY COMMAND                     */
/*---------------------------------------------------*/
unsigned char Si21XXC_L1_GET_PROPERTY      (L1_Si21XXC_Context *api,
                                           unsigned char   reserved,
                                           unsigned int    prop)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[4];
    unsigned char rspByteBuffer[4];
    api->rsp->get_property.STATUS = api->status;

    SiTRACE("Si21XXC GET_PROPERTY ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((reserved > Si21XXC_GET_PROPERTY_CMD_RESERVED_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED %d ", reserved );
    SiTRACE("PROP %d "    , prop     );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si21XXC_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si21XXC_GET_PROPERTY_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( reserved & Si21XXC_GET_PROPERTY_CMD_RESERVED_MASK ) << Si21XXC_GET_PROPERTY_CMD_RESERVED_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( prop     & Si21XXC_GET_PROPERTY_CMD_PROP_MASK     ) << Si21XXC_GET_PROPERTY_CMD_PROP_LSB    );
    cmdByteBuffer[3] = (unsigned char) ((( prop     & Si21XXC_GET_PROPERTY_CMD_PROP_MASK     ) << Si21XXC_GET_PROPERTY_CMD_PROP_LSB    )>>8);

    if (L0_WriteCommandBytes(api->i2c, 4, cmdByteBuffer) != 4) {
      SiTRACE("Error writing GET_PROPERTY bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 4, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling GET_PROPERTY response\n");
      return error_code;
    }

    api->rsp->get_property.reserved = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si21XXC_GET_PROPERTY_RESPONSE_RESERVED_LSB  , Si21XXC_GET_PROPERTY_RESPONSE_RESERVED_MASK );
    api->rsp->get_property.data     = Si21XXC_convert_to_uint  (&rspByteBuffer[ 2] , Si21XXC_GET_PROPERTY_RESPONSE_DATA_LSB      , Si21XXC_GET_PROPERTY_RESPONSE_DATA_MASK     );

    return NO_Si21XXC_ERROR;
}
#endif /* Si21XXC_GET_PROPERTY_CMD */
#ifdef    Si21XXC_GET_REV_CMD
 /*---------------------------------------------------*/
/* Si21XXC_GET_REV COMMAND                          */
/*---------------------------------------------------*/
unsigned char Si21XXC_L1_GET_REV           (L1_Si21XXC_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[13];
    api->rsp->get_rev.STATUS = api->status;

    SiTRACE("Si21XXC GET_REV ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si21XXC_GET_REV_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing GET_REV bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 13, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling GET_REV response\n");
      return error_code;
    }

    api->rsp->get_rev.pn       = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si21XXC_GET_REV_RESPONSE_PN_LSB        , Si21XXC_GET_REV_RESPONSE_PN_MASK       );
    api->rsp->get_rev.fwmajor  = Si21XXC_convert_to_byte  (&rspByteBuffer[ 2] , Si21XXC_GET_REV_RESPONSE_FWMAJOR_LSB   , Si21XXC_GET_REV_RESPONSE_FWMAJOR_MASK  );
    api->rsp->get_rev.fwminor  = Si21XXC_convert_to_byte  (&rspByteBuffer[ 3] , Si21XXC_GET_REV_RESPONSE_FWMINOR_LSB   , Si21XXC_GET_REV_RESPONSE_FWMINOR_MASK  );
    api->rsp->get_rev.patch    = Si21XXC_convert_to_uint  (&rspByteBuffer[ 4] , Si21XXC_GET_REV_RESPONSE_PATCH_LSB     , Si21XXC_GET_REV_RESPONSE_PATCH_MASK    );
    api->rsp->get_rev.cmpmajor = Si21XXC_convert_to_byte  (&rspByteBuffer[ 6] , Si21XXC_GET_REV_RESPONSE_CMPMAJOR_LSB  , Si21XXC_GET_REV_RESPONSE_CMPMAJOR_MASK );
    api->rsp->get_rev.cmpminor = Si21XXC_convert_to_byte  (&rspByteBuffer[ 7] , Si21XXC_GET_REV_RESPONSE_CMPMINOR_LSB  , Si21XXC_GET_REV_RESPONSE_CMPMINOR_MASK );
    api->rsp->get_rev.cmpbuild = Si21XXC_convert_to_byte  (&rspByteBuffer[ 8] , Si21XXC_GET_REV_RESPONSE_CMPBUILD_LSB  , Si21XXC_GET_REV_RESPONSE_CMPBUILD_MASK );
    api->rsp->get_rev.chiprev  = Si21XXC_convert_to_byte  (&rspByteBuffer[ 9] , Si21XXC_GET_REV_RESPONSE_CHIPREV_LSB   , Si21XXC_GET_REV_RESPONSE_CHIPREV_MASK  );
    api->rsp->get_rev.pn2      = Si21XXC_convert_to_byte  (&rspByteBuffer[12] , Si21XXC_GET_REV_RESPONSE_PN2_LSB       , Si21XXC_GET_REV_RESPONSE_PN2_MASK      );

    return NO_Si21XXC_ERROR;
}
#endif /* Si21XXC_GET_REV_CMD */
#ifdef    Si2191C_ISL_STATUS_CMD
/*---------------------------------------------------*/
/* Si2191C_ISL_STATUS COMMAND                               */
/*---------------------------------------------------*/
unsigned char Si2191C_L1_ISL_STATUS        (L1_Si21XXC_Context *api,
                                           unsigned char   clear)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[3];
    api->rsp->isl_status.STATUS = api->status;

    SiTRACE("Si2191C ISL_STATUS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((clear > Si2191C_ISL_STATUS_CMD_CLEAR_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CLEAR %d ", clear );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si21XXC_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2191C_ISL_STATUS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( clear & Si2191C_ISL_STATUS_CMD_CLEAR_MASK ) << Si2191C_ISL_STATUS_CMD_CLEAR_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing ISL_STATUS bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 3, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling ISL_STATUS response\n");
      return error_code;
    }

    api->rsp->isl_status.tx = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si2191C_ISL_STATUS_RESPONSE_TX_LSB  , Si2191C_ISL_STATUS_RESPONSE_TX_MASK );
    api->rsp->isl_status.rx = Si21XXC_convert_to_byte  (&rspByteBuffer[ 2] , Si2191C_ISL_STATUS_RESPONSE_RX_LSB  , Si2191C_ISL_STATUS_RESPONSE_RX_MASK );

    return NO_Si21XXC_ERROR;
}
#endif /* Si2191C_ISL_STATUS_CMD */

#ifdef    Si21XXC_PART_INFO_CMD
 /*---------------------------------------------------*/
/* Si21XXC_PART_INFO COMMAND                        */
/*---------------------------------------------------*/
unsigned char Si21XXC_L1_PART_INFO         (L1_Si21XXC_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[13];
    api->rsp->part_info.STATUS = api->status;

    SiTRACE("Si21XXC PART_INFO ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si21XXC_PART_INFO_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing PART_INFO bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 13, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling PART_INFO response\n");
      return error_code;
    }

    api->rsp->part_info.chiprev  = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si21XXC_PART_INFO_RESPONSE_CHIPREV_LSB   , Si21XXC_PART_INFO_RESPONSE_CHIPREV_MASK  );
    api->rsp->part_info.part     = Si21XXC_convert_to_byte  (&rspByteBuffer[ 2] , Si21XXC_PART_INFO_RESPONSE_PART_LSB      , Si21XXC_PART_INFO_RESPONSE_PART_MASK     );
    api->rsp->part_info.pmajor   = Si21XXC_convert_to_byte  (&rspByteBuffer[ 3] , Si21XXC_PART_INFO_RESPONSE_PMAJOR_LSB    , Si21XXC_PART_INFO_RESPONSE_PMAJOR_MASK   );
    api->rsp->part_info.pminor   = Si21XXC_convert_to_byte  (&rspByteBuffer[ 4] , Si21XXC_PART_INFO_RESPONSE_PMINOR_LSB    , Si21XXC_PART_INFO_RESPONSE_PMINOR_MASK   );
    api->rsp->part_info.pbuild   = Si21XXC_convert_to_byte  (&rspByteBuffer[ 5] , Si21XXC_PART_INFO_RESPONSE_PBUILD_LSB    , Si21XXC_PART_INFO_RESPONSE_PBUILD_MASK   );
    api->rsp->part_info.reserved = Si21XXC_convert_to_uint  (&rspByteBuffer[ 6] , Si21XXC_PART_INFO_RESPONSE_RESERVED_LSB  , Si21XXC_PART_INFO_RESPONSE_RESERVED_MASK );
    api->rsp->part_info.serial   = Si21XXC_convert_to_ulong (&rspByteBuffer[ 8] , Si21XXC_PART_INFO_RESPONSE_SERIAL_LSB    , Si21XXC_PART_INFO_RESPONSE_SERIAL_MASK   );
    api->rsp->part_info.romid    = Si21XXC_convert_to_byte  (&rspByteBuffer[12] , Si21XXC_PART_INFO_RESPONSE_ROMID_LSB     , Si21XXC_PART_INFO_RESPONSE_ROMID_MASK    );
//    api->rsp->part_info.part2    = Si21XXC_convert_to_byte  (&rspByteBuffer[13] , Si21XXC_PART_INFO_RESPONSE_PART2_LSB     , Si2190B_PART_INFO_RESPONSE_PART2_MASK    );
//    api->rsp->part_info.rx       = Si21XXC_convert_to_byte  (&rspByteBuffer[13] , Si21XXC_PART_INFO_RESPONSE_RX_LSB        , Si2190B_PART_INFO_RESPONSE_RX_MASK       );

    return NO_Si21XXC_ERROR;
}
#endif /* Si21XXC_PART_INFO_CMD */
#ifdef    Si2190B_PART_INFO2_CMD
/*---------------------------------------------------*/
/* Si2190B_PART_INFO2 COMMAND                               */
/*---------------------------------------------------*/
unsigned char Si2190B_L1_PART_INFO2        (L1_Si21XXC_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[8];
    api->rsp->part_info2.STATUS = api->status;

    SiTRACE("Si2190B PART_INFO2 ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2190B_PART_INFO2_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing PART_INFO2 bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 8, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling PART_INFO2 response\n");
      return error_code;
    }

    api->rsp->part_info2.romid    = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si2190B_PART_INFO2_RESPONSE_ROMID_LSB     , Si2190B_PART_INFO2_RESPONSE_ROMID_MASK    );
    api->rsp->part_info2.part2    = Si21XXC_convert_to_byte  (&rspByteBuffer[ 2] , Si2190B_PART_INFO2_RESPONSE_PART2_LSB     , Si2190B_PART_INFO2_RESPONSE_PART2_MASK    );
    api->rsp->part_info2.reserved = Si21XXC_convert_to_byte  (&rspByteBuffer[ 3] , Si2190B_PART_INFO2_RESPONSE_RESERVED_LSB  , Si2190B_PART_INFO2_RESPONSE_RESERVED_MASK );
    api->rsp->part_info2.serial   = Si21XXC_convert_to_ulong (&rspByteBuffer[ 4] , Si2190B_PART_INFO2_RESPONSE_SERIAL_LSB    , Si2190B_PART_INFO2_RESPONSE_SERIAL_MASK   );

    return NO_Si21XXC_ERROR;
}
#endif /* Si2190B_PART_INFO2_CMD */

#ifdef    Si21XXC_POWER_DOWN_HW_CMD
 /*---------------------------------------------------*/
/* Si21XXC_POWER_DOWN_HW COMMAND                    */
/*---------------------------------------------------*/
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
                                           unsigned char   reserved8)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[10];
    api->rsp->power_down_hw.STATUS = api->status;

    SiTRACE("Si21XXC POWER_DOWN_HW ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode   > Si21XXC_POWER_DOWN_HW_CMD_SUBCODE_MAX  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "  , subcode   );
    if ((pd_xo_osc > Si21XXC_POWER_DOWN_HW_CMD_PD_XO_OSC_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("PD_XO_OSC %d ", pd_xo_osc );
    if ((reserved1 > Si21XXC_POWER_DOWN_HW_CMD_RESERVED1_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED1 %d ", reserved1 );
    if ((en_xout   > Si21XXC_POWER_DOWN_HW_CMD_EN_XOUT_MAX  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("EN_XOUT %d "  , en_xout   );
    if ((reserved2 > Si21XXC_POWER_DOWN_HW_CMD_RESERVED2_MAX)  || (reserved2 < Si21XXC_POWER_DOWN_HW_CMD_RESERVED2_MIN) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED2 %d ", reserved2 );
    if ((pd_ldo    > Si21XXC_POWER_DOWN_HW_CMD_PD_LDO_MAX   ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("PD_LDO %d "   , pd_ldo    );
    if ((reserved3 > Si21XXC_POWER_DOWN_HW_CMD_RESERVED3_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED3 %d ", reserved3 );
    if ((reserved4 > Si21XXC_POWER_DOWN_HW_CMD_RESERVED4_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED4 %d ", reserved4 );
    if ((reserved5 > Si21XXC_POWER_DOWN_HW_CMD_RESERVED5_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED5 %d ", reserved5 );
    if ((reserved6 > Si21XXC_POWER_DOWN_HW_CMD_RESERVED6_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED6 %d ", reserved6 );
    if ((reserved7 > Si21XXC_POWER_DOWN_HW_CMD_RESERVED7_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED7 %d ", reserved7 );
    if ((reserved8 > Si21XXC_POWER_DOWN_HW_CMD_RESERVED8_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED8 %d ", reserved8 );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si21XXC_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si21XXC_POWER_DOWN_HW_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode   & Si21XXC_POWER_DOWN_HW_CMD_SUBCODE_MASK   ) << Si21XXC_POWER_DOWN_HW_CMD_SUBCODE_LSB  );
    cmdByteBuffer[2] = (unsigned char) ( ( pd_xo_osc & Si21XXC_POWER_DOWN_HW_CMD_PD_XO_OSC_MASK ) << Si21XXC_POWER_DOWN_HW_CMD_PD_XO_OSC_LSB|
                                         ( reserved1 & Si21XXC_POWER_DOWN_HW_CMD_RESERVED1_MASK ) << Si21XXC_POWER_DOWN_HW_CMD_RESERVED1_LSB|
                                         ( en_xout   & Si21XXC_POWER_DOWN_HW_CMD_EN_XOUT_MASK   ) << Si21XXC_POWER_DOWN_HW_CMD_EN_XOUT_LSB  |
                                         ( reserved2 & Si21XXC_POWER_DOWN_HW_CMD_RESERVED2_MASK ) << Si21XXC_POWER_DOWN_HW_CMD_RESERVED2_LSB);
    cmdByteBuffer[3] = (unsigned char) ( ( pd_ldo    & Si21XXC_POWER_DOWN_HW_CMD_PD_LDO_MASK    ) << Si21XXC_POWER_DOWN_HW_CMD_PD_LDO_LSB   );
    cmdByteBuffer[4] = (unsigned char) ( ( reserved3 & Si21XXC_POWER_DOWN_HW_CMD_RESERVED3_MASK ) << Si21XXC_POWER_DOWN_HW_CMD_RESERVED3_LSB);
    cmdByteBuffer[5] = (unsigned char) ( ( reserved4 & Si21XXC_POWER_DOWN_HW_CMD_RESERVED4_MASK ) << Si21XXC_POWER_DOWN_HW_CMD_RESERVED4_LSB);
    cmdByteBuffer[6] = (unsigned char) ( ( reserved5 & Si21XXC_POWER_DOWN_HW_CMD_RESERVED5_MASK ) << Si21XXC_POWER_DOWN_HW_CMD_RESERVED5_LSB);
    cmdByteBuffer[7] = (unsigned char) ( ( reserved6 & Si21XXC_POWER_DOWN_HW_CMD_RESERVED6_MASK ) << Si21XXC_POWER_DOWN_HW_CMD_RESERVED6_LSB);
    cmdByteBuffer[8] = (unsigned char) ( ( reserved7 & Si21XXC_POWER_DOWN_HW_CMD_RESERVED7_MASK ) << Si21XXC_POWER_DOWN_HW_CMD_RESERVED7_LSB);
    cmdByteBuffer[9] = (unsigned char) ( ( reserved8 & Si21XXC_POWER_DOWN_HW_CMD_RESERVED8_MASK ) << Si21XXC_POWER_DOWN_HW_CMD_RESERVED8_LSB);

    if (L0_WriteCommandBytes(api->i2c, 10, cmdByteBuffer) != 10) {
      SiTRACE("Error writing POWER_DOWN_HW bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResetState(api);
    if (error_code) {
      SiTRACE("Error polling POWER_DOWN_HW reset state\n");
      return error_code;
    }
    return NO_Si21XXC_ERROR;
}
#endif /* Si21XXC_POWER_DOWN_HW_CMD */
#ifdef    Si21XXC_POWER_UP_CMD
 /*---------------------------------------------------*/
/* Si21XXC_POWER_UP COMMAND                         */
/*---------------------------------------------------*/
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
                                           unsigned char   wake_up)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[15];
    unsigned char rspByteBuffer[1];
    api->rsp->power_up.STATUS = api->status;

    SiTRACE("Si21XXC POWER_UP ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode    > Si21XXC_POWER_UP_CMD_SUBCODE_MAX   ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "   , subcode    );
    if ((clock_mode > Si21XXC_POWER_UP_CMD_CLOCK_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CLOCK_MODE %d ", clock_mode );
    if ((en_xout    > Si21XXC_POWER_UP_CMD_EN_XOUT_MAX   ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("EN_XOUT %d "   , en_xout    );
    if ((pd_ldo     > Si21XXC_POWER_UP_CMD_PD_LDO_MAX    ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("PD_LDO %d "    , pd_ldo     );
    if ((reserved2  > Si21XXC_POWER_UP_CMD_RESERVED2_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED2 %d " , reserved2  );
    if ((reserved3  > Si21XXC_POWER_UP_CMD_RESERVED3_MAX )  || (reserved3  < Si21XXC_POWER_UP_CMD_RESERVED3_MIN ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED3 %d " , reserved3  );
    if ((reserved4  > Si21XXC_POWER_UP_CMD_RESERVED4_MAX )  || (reserved4  < Si21XXC_POWER_UP_CMD_RESERVED4_MIN ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED4 %d " , reserved4  );
    if ((reserved5  > Si21XXC_POWER_UP_CMD_RESERVED5_MAX )  || (reserved5  < Si21XXC_POWER_UP_CMD_RESERVED5_MIN ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED5 %d " , reserved5  );
    if ((reserved6  > Si21XXC_POWER_UP_CMD_RESERVED6_MAX )  || (reserved6  < Si21XXC_POWER_UP_CMD_RESERVED6_MIN ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED6 %d " , reserved6  );
    if ((reserved7  > Si21XXC_POWER_UP_CMD_RESERVED7_MAX )  || (reserved7  < Si21XXC_POWER_UP_CMD_RESERVED7_MIN ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED7 %d " , reserved7  );
    if ((reset      > Si21XXC_POWER_UP_CMD_RESET_MAX     )  || (reset      < Si21XXC_POWER_UP_CMD_RESET_MIN     ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESET %d "     , reset      );
    if ((clock_freq > Si21XXC_POWER_UP_CMD_CLOCK_FREQ_MAX)  || (clock_freq < Si21XXC_POWER_UP_CMD_CLOCK_FREQ_MIN) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CLOCK_FREQ %d ", clock_freq );
    if ((reserved8  > Si21XXC_POWER_UP_CMD_RESERVED8_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED8 %d " , reserved8  );
    if ((func       > Si21XXC_POWER_UP_CMD_FUNC_MAX      ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FUNC %d "      , func       );
    if ((ctsien     > Si21XXC_POWER_UP_CMD_CTSIEN_MAX    ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CTSIEN %d "    , ctsien     );
    if ((wake_up    > Si21XXC_POWER_UP_CMD_WAKE_UP_MAX   )  || (wake_up    < Si21XXC_POWER_UP_CMD_WAKE_UP_MIN   ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("WAKE_UP %d "   , wake_up    );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si21XXC_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si21XXC_POWER_UP_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode    & Si21XXC_POWER_UP_CMD_SUBCODE_MASK    ) << Si21XXC_POWER_UP_CMD_SUBCODE_LSB   );
    cmdByteBuffer[2] = (unsigned char) ( ( clock_mode & Si21XXC_POWER_UP_CMD_CLOCK_MODE_MASK ) << Si21XXC_POWER_UP_CMD_CLOCK_MODE_LSB|
                                         ( en_xout    & Si21XXC_POWER_UP_CMD_EN_XOUT_MASK    ) << Si21XXC_POWER_UP_CMD_EN_XOUT_LSB   );
    cmdByteBuffer[3] = (unsigned char) ( ( pd_ldo     & Si21XXC_POWER_UP_CMD_PD_LDO_MASK     ) << Si21XXC_POWER_UP_CMD_PD_LDO_LSB    );
    cmdByteBuffer[4] = (unsigned char) ( ( reserved2  & Si21XXC_POWER_UP_CMD_RESERVED2_MASK  ) << Si21XXC_POWER_UP_CMD_RESERVED2_LSB );
    cmdByteBuffer[5] = (unsigned char) ( ( reserved3  & Si21XXC_POWER_UP_CMD_RESERVED3_MASK  ) << Si21XXC_POWER_UP_CMD_RESERVED3_LSB );
    cmdByteBuffer[6] = (unsigned char) ( ( reserved4  & Si21XXC_POWER_UP_CMD_RESERVED4_MASK  ) << Si21XXC_POWER_UP_CMD_RESERVED4_LSB );
    cmdByteBuffer[7] = (unsigned char) ( ( reserved5  & Si21XXC_POWER_UP_CMD_RESERVED5_MASK  ) << Si21XXC_POWER_UP_CMD_RESERVED5_LSB );
    cmdByteBuffer[8] = (unsigned char) ( ( reserved6  & Si21XXC_POWER_UP_CMD_RESERVED6_MASK  ) << Si21XXC_POWER_UP_CMD_RESERVED6_LSB );
    cmdByteBuffer[9] = (unsigned char) ( ( reserved7  & Si21XXC_POWER_UP_CMD_RESERVED7_MASK  ) << Si21XXC_POWER_UP_CMD_RESERVED7_LSB );
    cmdByteBuffer[10] = (unsigned char) ( ( reset      & Si21XXC_POWER_UP_CMD_RESET_MASK      ) << Si21XXC_POWER_UP_CMD_RESET_LSB     );
    cmdByteBuffer[11] = (unsigned char) ( ( clock_freq & Si21XXC_POWER_UP_CMD_CLOCK_FREQ_MASK ) << Si21XXC_POWER_UP_CMD_CLOCK_FREQ_LSB);
    cmdByteBuffer[12] = (unsigned char) ( ( reserved8  & Si21XXC_POWER_UP_CMD_RESERVED8_MASK  ) << Si21XXC_POWER_UP_CMD_RESERVED8_LSB );
    cmdByteBuffer[13] = (unsigned char) ( ( func       & Si21XXC_POWER_UP_CMD_FUNC_MASK       ) << Si21XXC_POWER_UP_CMD_FUNC_LSB      |
                                         ( ctsien     & Si21XXC_POWER_UP_CMD_CTSIEN_MASK     ) << Si21XXC_POWER_UP_CMD_CTSIEN_LSB    );
    cmdByteBuffer[14] = (unsigned char) ( ( wake_up    & Si21XXC_POWER_UP_CMD_WAKE_UP_MASK    ) << Si21XXC_POWER_UP_CMD_WAKE_UP_LSB   );

    if (L0_WriteCommandBytes(api->i2c, 15, cmdByteBuffer) != 15) {
      SiTRACE("Error writing POWER_UP bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling POWER_UP response\n");
      return error_code;
    }


    return NO_Si21XXC_ERROR;
}
#endif /* Si21XXC_POWER_UP_CMD */
#ifdef    Si2190B_REREAD_REPLY_CMD
/*---------------------------------------------------*/
/* Si2190B_REREAD_REPLY COMMAND                           */
/*---------------------------------------------------*/
unsigned char Si2190B_L1_REREAD_REPLY      (L1_Si21XXC_Context *api,
                                           unsigned char   offset)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[16];
    api->rsp->reread_reply.STATUS = api->status;

    SiTRACE("Si2190B REREAD_REPLY ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((offset > Si2190B_REREAD_REPLY_CMD_OFFSET_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("OFFSET %d ", offset );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2190B_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2190B_REREAD_REPLY_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( offset & Si2190B_REREAD_REPLY_CMD_OFFSET_MASK ) << Si2190B_REREAD_REPLY_CMD_OFFSET_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing REREAD_REPLY bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 16, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling REREAD_REPLY response\n");
      return error_code;
    }

    api->rsp->reread_reply.reply1  = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si2190B_REREAD_REPLY_RESPONSE_REPLY1_LSB   , Si2190B_REREAD_REPLY_RESPONSE_REPLY1_MASK  );
    api->rsp->reread_reply.reply2  = Si21XXC_convert_to_byte  (&rspByteBuffer[ 2] , Si2190B_REREAD_REPLY_RESPONSE_REPLY2_LSB   , Si2190B_REREAD_REPLY_RESPONSE_REPLY2_MASK  );
    api->rsp->reread_reply.reply3  = Si21XXC_convert_to_byte  (&rspByteBuffer[ 3] , Si2190B_REREAD_REPLY_RESPONSE_REPLY3_LSB   , Si2190B_REREAD_REPLY_RESPONSE_REPLY3_MASK  );
    api->rsp->reread_reply.reply4  = Si21XXC_convert_to_byte  (&rspByteBuffer[ 4] , Si2190B_REREAD_REPLY_RESPONSE_REPLY4_LSB   , Si2190B_REREAD_REPLY_RESPONSE_REPLY4_MASK  );
    api->rsp->reread_reply.reply5  = Si21XXC_convert_to_byte  (&rspByteBuffer[ 5] , Si2190B_REREAD_REPLY_RESPONSE_REPLY5_LSB   , Si2190B_REREAD_REPLY_RESPONSE_REPLY5_MASK  );
    api->rsp->reread_reply.reply6  = Si21XXC_convert_to_byte  (&rspByteBuffer[ 6] , Si2190B_REREAD_REPLY_RESPONSE_REPLY6_LSB   , Si2190B_REREAD_REPLY_RESPONSE_REPLY6_MASK  );
    api->rsp->reread_reply.reply7  = Si21XXC_convert_to_byte  (&rspByteBuffer[ 7] , Si2190B_REREAD_REPLY_RESPONSE_REPLY7_LSB   , Si2190B_REREAD_REPLY_RESPONSE_REPLY7_MASK  );
    api->rsp->reread_reply.reply8  = Si21XXC_convert_to_byte  (&rspByteBuffer[ 8] , Si2190B_REREAD_REPLY_RESPONSE_REPLY8_LSB   , Si2190B_REREAD_REPLY_RESPONSE_REPLY8_MASK  );
    api->rsp->reread_reply.reply9  = Si21XXC_convert_to_byte  (&rspByteBuffer[ 9] , Si2190B_REREAD_REPLY_RESPONSE_REPLY9_LSB   , Si2190B_REREAD_REPLY_RESPONSE_REPLY9_MASK  );
    api->rsp->reread_reply.reply10 = Si21XXC_convert_to_byte  (&rspByteBuffer[10] , Si2190B_REREAD_REPLY_RESPONSE_REPLY10_LSB  , Si2190B_REREAD_REPLY_RESPONSE_REPLY10_MASK );
    api->rsp->reread_reply.reply11 = Si21XXC_convert_to_byte  (&rspByteBuffer[11] , Si2190B_REREAD_REPLY_RESPONSE_REPLY11_LSB  , Si2190B_REREAD_REPLY_RESPONSE_REPLY11_MASK );
    api->rsp->reread_reply.reply12 = Si21XXC_convert_to_byte  (&rspByteBuffer[12] , Si2190B_REREAD_REPLY_RESPONSE_REPLY12_LSB  , Si2190B_REREAD_REPLY_RESPONSE_REPLY12_MASK );
    api->rsp->reread_reply.reply13 = Si21XXC_convert_to_byte  (&rspByteBuffer[13] , Si2190B_REREAD_REPLY_RESPONSE_REPLY13_LSB  , Si2190B_REREAD_REPLY_RESPONSE_REPLY13_MASK );
    api->rsp->reread_reply.reply14 = Si21XXC_convert_to_byte  (&rspByteBuffer[14] , Si2190B_REREAD_REPLY_RESPONSE_REPLY14_LSB  , Si2190B_REREAD_REPLY_RESPONSE_REPLY14_MASK );
    api->rsp->reread_reply.reply15 = Si21XXC_convert_to_byte  (&rspByteBuffer[15] , Si2190B_REREAD_REPLY_RESPONSE_REPLY15_LSB  , Si2190B_REREAD_REPLY_RESPONSE_REPLY15_MASK );

    return NO_Si21XXC_ERROR;
}
#endif /* Si2190B_REREAD_REPLY_CMD */
#ifdef    Si2190B_RESET_HW_CMD
/*---------------------------------------------------*/
/* Si2190B_RESET_HW COMMAND                                   */
/*---------------------------------------------------*/
unsigned char Si2190B_L1_RESET_HW          (L1_Si21XXC_Context *api,
                                           unsigned char   subcode,
                                           unsigned char   reserved1,
                                           unsigned char   reserved2)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[4];
    unsigned char rspByteBuffer[1];
    api->rsp->reset_hw.STATUS = api->status;

    SiTRACE("Si2190B RESET_HW ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode   > Si2190B_RESET_HW_CMD_SUBCODE_MAX  )  || (subcode   < Si2190B_RESET_HW_CMD_SUBCODE_MIN  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "  , subcode   );
    if ((reserved1 > Si2190B_RESET_HW_CMD_RESERVED1_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED1 %d ", reserved1 );
    if ((reserved2 > Si2190B_RESET_HW_CMD_RESERVED2_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED2 %d ", reserved2 );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2190B_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2190B_RESET_HW_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode   & Si2190B_RESET_HW_CMD_SUBCODE_MASK   ) << Si2190B_RESET_HW_CMD_SUBCODE_LSB  );
    cmdByteBuffer[2] = (unsigned char) ( ( reserved1 & Si2190B_RESET_HW_CMD_RESERVED1_MASK ) << Si2190B_RESET_HW_CMD_RESERVED1_LSB);
    cmdByteBuffer[3] = (unsigned char) ( ( reserved2 & Si2190B_RESET_HW_CMD_RESERVED2_MASK ) << Si2190B_RESET_HW_CMD_RESERVED2_LSB);

    if (L0_WriteCommandBytes(api->i2c, 4, cmdByteBuffer) != 4) {
      SiTRACE("Error writing RESET_HW bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling RESET_HW response\n");
      return error_code;
    }
    return NO_Si21XXC_ERROR;
}
#endif /* Si2190B_RESET_HW_CMD */
#ifdef    Si2190B_SELF_TEST_CMD
/*---------------------------------------------------*/
/* Si2190B_SELF_TEST COMMAND                                 */
/*---------------------------------------------------*/
unsigned char Si2190B_L1_SELF_TEST         (L1_Si21XXC_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[4];
    api->rsp->self_test.STATUS = api->status;

    SiTRACE("Si2190B SELF_TEST ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2190B_SELF_TEST_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing SELF_TEST bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 4, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling SELF_TEST response\n");
      return error_code;
    }

    api->rsp->self_test.adc_ref         = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si2190B_SELF_TEST_RESPONSE_ADC_REF_LSB          , Si2190B_SELF_TEST_RESPONSE_ADC_REF_MASK         );
    api->rsp->self_test.mix_cmb0        = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si2190B_SELF_TEST_RESPONSE_MIX_CMB0_LSB         , Si2190B_SELF_TEST_RESPONSE_MIX_CMB0_MASK        );
    api->rsp->self_test.mix_cmb1        = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si2190B_SELF_TEST_RESPONSE_MIX_CMB1_LSB         , Si2190B_SELF_TEST_RESPONSE_MIX_CMB1_MASK        );
    api->rsp->self_test.mix_cmb2        = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si2190B_SELF_TEST_RESPONSE_MIX_CMB2_LSB         , Si2190B_SELF_TEST_RESPONSE_MIX_CMB2_MASK        );
    api->rsp->self_test.divr_vreg       = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si2190B_SELF_TEST_RESPONSE_DIVR_VREG_LSB        , Si2190B_SELF_TEST_RESPONSE_DIVR_VREG_MASK       );
    api->rsp->self_test.pdcplf_vreg     = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si2190B_SELF_TEST_RESPONSE_PDCPLF_VREG_LSB      , Si2190B_SELF_TEST_RESPONSE_PDCPLF_VREG_MASK     );
    api->rsp->self_test.pdcplf_bias     = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si2190B_SELF_TEST_RESPONSE_PDCPLF_BIAS_LSB      , Si2190B_SELF_TEST_RESPONSE_PDCPLF_BIAS_MASK     );
    api->rsp->self_test.vco_vreg1       = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si2190B_SELF_TEST_RESPONSE_VCO_VREG1_LSB        , Si2190B_SELF_TEST_RESPONSE_VCO_VREG1_MASK       );
    api->rsp->self_test.vco_vreg2       = Si21XXC_convert_to_byte  (&rspByteBuffer[ 2] , Si2190B_SELF_TEST_RESPONSE_VCO_VREG2_LSB        , Si2190B_SELF_TEST_RESPONSE_VCO_VREG2_MASK       );
    api->rsp->self_test.fbdiv_ireg      = Si21XXC_convert_to_byte  (&rspByteBuffer[ 2] , Si2190B_SELF_TEST_RESPONSE_FBDIV_IREG_LSB       , Si2190B_SELF_TEST_RESPONSE_FBDIV_IREG_MASK      );
    api->rsp->self_test.fbdiv_vreg      = Si21XXC_convert_to_byte  (&rspByteBuffer[ 2] , Si2190B_SELF_TEST_RESPONSE_FBDIV_VREG_LSB       , Si2190B_SELF_TEST_RESPONSE_FBDIV_VREG_MASK      );
    api->rsp->self_test.pdcplf_rccal    = Si21XXC_convert_to_byte  (&rspByteBuffer[ 2] , Si2190B_SELF_TEST_RESPONSE_PDCPLF_RCCAL_LSB     , Si2190B_SELF_TEST_RESPONSE_PDCPLF_RCCAL_MASK    );
    api->rsp->self_test.dac1_vtr        = Si21XXC_convert_to_byte  (&rspByteBuffer[ 2] , Si2190B_SELF_TEST_RESPONSE_DAC1_VTR_LSB         , Si2190B_SELF_TEST_RESPONSE_DAC1_VTR_MASK        );
    api->rsp->self_test.dac1_vcom       = Si21XXC_convert_to_byte  (&rspByteBuffer[ 2] , Si2190B_SELF_TEST_RESPONSE_DAC1_VCOM_LSB        , Si2190B_SELF_TEST_RESPONSE_DAC1_VCOM_MASK       );
    api->rsp->self_test.dac2_vtr        = Si21XXC_convert_to_byte  (&rspByteBuffer[ 2] , Si2190B_SELF_TEST_RESPONSE_DAC2_VTR_LSB         , Si2190B_SELF_TEST_RESPONSE_DAC2_VTR_MASK        );
    api->rsp->self_test.dac2_vcom       = Si21XXC_convert_to_byte  (&rspByteBuffer[ 2] , Si2190B_SELF_TEST_RESPONSE_DAC2_VCOM_LSB        , Si2190B_SELF_TEST_RESPONSE_DAC2_VCOM_MASK       );
    api->rsp->self_test.if_bias         = Si21XXC_convert_to_byte  (&rspByteBuffer[ 3] , Si2190B_SELF_TEST_RESPONSE_IF_BIAS_LSB          , Si2190B_SELF_TEST_RESPONSE_IF_BIAS_MASK         );
    api->rsp->self_test.lna_vmid        = Si21XXC_convert_to_byte  (&rspByteBuffer[ 3] , Si2190B_SELF_TEST_RESPONSE_LNA_VMID_LSB         , Si2190B_SELF_TEST_RESPONSE_LNA_VMID_MASK        );
    api->rsp->self_test.lna_vreg        = Si21XXC_convert_to_byte  (&rspByteBuffer[ 3] , Si2190B_SELF_TEST_RESPONSE_LNA_VREG_LSB         , Si2190B_SELF_TEST_RESPONSE_LNA_VREG_MASK        );
    api->rsp->self_test.lna_vtr         = Si21XXC_convert_to_byte  (&rspByteBuffer[ 3] , Si2190B_SELF_TEST_RESPONSE_LNA_VTR_LSB          , Si2190B_SELF_TEST_RESPONSE_LNA_VTR_MASK         );
    api->rsp->self_test.lodiv_core_vreg = Si21XXC_convert_to_byte  (&rspByteBuffer[ 3] , Si2190B_SELF_TEST_RESPONSE_LODIV_CORE_VREG_LSB  , Si2190B_SELF_TEST_RESPONSE_LODIV_CORE_VREG_MASK );
    api->rsp->self_test.lodiv_buf_reg   = Si21XXC_convert_to_byte  (&rspByteBuffer[ 3] , Si2190B_SELF_TEST_RESPONSE_LODIV_BUF_REG_LSB    , Si2190B_SELF_TEST_RESPONSE_LODIV_BUF_REG_MASK   );
    api->rsp->self_test.rccal_filt      = Si21XXC_convert_to_byte  (&rspByteBuffer[ 3] , Si2190B_SELF_TEST_RESPONSE_RCCAL_FILT_LSB       , Si2190B_SELF_TEST_RESPONSE_RCCAL_FILT_MASK      );
    api->rsp->self_test.rccal_adc       = Si21XXC_convert_to_byte  (&rspByteBuffer[ 3] , Si2190B_SELF_TEST_RESPONSE_RCCAL_ADC_LSB        , Si2190B_SELF_TEST_RESPONSE_RCCAL_ADC_MASK       );

    return NO_Si21XXC_ERROR;
}
#endif /* Si2190B_SELF_TEST_CMD */

#ifdef    Si21XXC_SET_PROPERTY_CMD
 /*---------------------------------------------------*/
/* Si21XXC_SET_PROPERTY COMMAND                     */
/*---------------------------------------------------*/
unsigned char Si21XXC_L1_SET_PROPERTY      (L1_Si21XXC_Context *api,
                                           unsigned char   reserved,
                                           unsigned int    prop,
                                           unsigned int    data)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[6];
    unsigned char rspByteBuffer[4];
    unsigned int  shadowData = 0;//Coverity 190816 fixed
    unsigned char  res;
    api->rsp->set_property.STATUS = api->status;
    res = Si21XXC_PackProperty(api->propShadow, prop, (int *) &shadowData);

    SiTRACE("Si21XXC SET_PROPERTY ");
  #ifdef   DEBUG_RANGE_CHECK
    SiTRACE("RESERVED %d ", reserved );
    SiTRACE("PROP %d "    , prop     );
    SiTRACE("DATA %d "    , data     );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si21XXC_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */
  /* This function will only download the property if required.
               Conditions to download the property are:
                - The property changes
                - The propertyWriteMode is set to DOWNLOAD_ALWAYS
                - The property is unknown to PackProperty (this may be useful for debug purpose) */
   if ((data != shadowData)  || (api->propertyWriteMode == DOWNLOAD_ALWAYS) || (res == ERROR_Si21XXC_UNKNOWN_PROPERTY) )
   {
        SiTRACE("\n");
        cmdByteBuffer[0] = Si21XXC_SET_PROPERTY_CMD;
        cmdByteBuffer[1] = (unsigned char) ( ( reserved & Si21XXC_SET_PROPERTY_CMD_RESERVED_MASK ) << Si21XXC_SET_PROPERTY_CMD_RESERVED_LSB);
        cmdByteBuffer[2] = (unsigned char) ( ( prop     & Si21XXC_SET_PROPERTY_CMD_PROP_MASK     ) << Si21XXC_SET_PROPERTY_CMD_PROP_LSB    );
        cmdByteBuffer[3] = (unsigned char) ((( prop     & Si21XXC_SET_PROPERTY_CMD_PROP_MASK     ) << Si21XXC_SET_PROPERTY_CMD_PROP_LSB    )>>8);
        cmdByteBuffer[4] = (unsigned char) ( ( data     & Si21XXC_SET_PROPERTY_CMD_DATA_MASK     ) << Si21XXC_SET_PROPERTY_CMD_DATA_LSB    );
        cmdByteBuffer[5] = (unsigned char) ((( data     & Si21XXC_SET_PROPERTY_CMD_DATA_MASK     ) << Si21XXC_SET_PROPERTY_CMD_DATA_LSB    )>>8);

        if (L0_WriteCommandBytes(api->i2c, 6, cmdByteBuffer) != 6) {
          SiTRACE("Error writing SET_PROPERTY bytes!\n");
          return ERROR_Si21XXC_SENDING_COMMAND;
        }

        error_code = Si21XXC_pollForResponse(api, 4, rspByteBuffer);
        if (error_code) {
          SiTRACE("Error polling SET_PROPERTY response\n");
          return error_code;
        }

        api->rsp->set_property.reserved = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si21XXC_SET_PROPERTY_RESPONSE_RESERVED_LSB  , Si21XXC_SET_PROPERTY_RESPONSE_RESERVED_MASK );
        api->rsp->set_property.data     = Si21XXC_convert_to_uint  (&rspByteBuffer[ 2] , Si21XXC_SET_PROPERTY_RESPONSE_DATA_LSB      , Si21XXC_SET_PROPERTY_RESPONSE_DATA_MASK     );

        /* Update propShadow with latest data if correctly set */
        Si21XXC_UnpackProperty   (api->propShadow, prop, data);
   }
   else
   {
        SiTRACE("\nSi21XXC_L1_SetProperty: Skipping Property Setting 0x%04x because value unchanged 0x%04x\n", prop,data);
   }
    return NO_Si21XXC_ERROR;
}
#endif /* Si21XXC_SET_PROPERTY_CMD */
#ifdef    Si2190B_SSVD_DEBUG_CONFIG_CMD
/*---------------------------------------------------*/
/* Si2190B_SSVD_DEBUG_CONFIG COMMAND                 */
/*---------------------------------------------------*/
unsigned char Si2190B_L1_SSVD_DEBUG_CONFIG (L1_Si21XXC_Context *api,
                                           unsigned char   cvbs_out,
                                           unsigned char   sif_out)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[3];
    unsigned char rspByteBuffer[1];
    api->rsp->ssvd_debug_config.STATUS = api->status;

    SiTRACE("Si2190B SSVD_DEBUG_CONFIG ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((cvbs_out > Si2190B_SSVD_DEBUG_CONFIG_CMD_CVBS_OUT_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CVBS_OUT %d ", cvbs_out );
    if ((sif_out  > Si2190B_SSVD_DEBUG_CONFIG_CMD_SIF_OUT_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SIF_OUT %d " , sif_out  );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2190B_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2190B_SSVD_DEBUG_CONFIG_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( cvbs_out & Si2190B_SSVD_DEBUG_CONFIG_CMD_CVBS_OUT_MASK ) << Si2190B_SSVD_DEBUG_CONFIG_CMD_CVBS_OUT_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( sif_out  & Si2190B_SSVD_DEBUG_CONFIG_CMD_SIF_OUT_MASK  ) << Si2190B_SSVD_DEBUG_CONFIG_CMD_SIF_OUT_LSB );

    if (L0_WriteCommandBytes(api->i2c, 3, cmdByteBuffer) != 3) {
      SiTRACE("Error writing SSVD_DEBUG_CONFIG bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling SSVD_DEBUG_CONFIG response\n");
      return error_code;
    }


    return NO_Si21XXC_ERROR;
}
#endif /* Si2190B_SSVD_DEBUG_CONFIG_CMD */
#ifdef    Si2190B_SSVD_HDIV_CMD
/*---------------------------------------------------*/
/* Si2190B_SSVD_HDIV COMMAND                                 */
/*---------------------------------------------------*/
unsigned char Si2190B_L1_SSVD_HDIV         (L1_Si21XXC_Context *api,
                                           unsigned char   enable,
                                           unsigned int    st_ctrl0,
                                           unsigned int    ha_ctrl0)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[6];
    unsigned char rspByteBuffer[1];
    api->rsp->ssvd_hdiv.STATUS = api->status;

    SiTRACE("Si2190B SSVD_HDIV ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((enable   > Si2190B_SSVD_HDIV_CMD_ENABLE_MAX  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("ENABLE %d "  , enable   );
    SiTRACE("ST_CTRL0 %d ", st_ctrl0 );
    SiTRACE("HA_CTRL0 %d ", ha_ctrl0 );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2190B_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2190B_SSVD_HDIV_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( enable   & Si2190B_SSVD_HDIV_CMD_ENABLE_MASK   ) << Si2190B_SSVD_HDIV_CMD_ENABLE_LSB  );
    cmdByteBuffer[2] = (unsigned char) ( ( st_ctrl0 & Si2190B_SSVD_HDIV_CMD_ST_CTRL0_MASK ) << Si2190B_SSVD_HDIV_CMD_ST_CTRL0_LSB);
    cmdByteBuffer[3] = (unsigned char) ((( st_ctrl0 & Si2190B_SSVD_HDIV_CMD_ST_CTRL0_MASK ) << Si2190B_SSVD_HDIV_CMD_ST_CTRL0_LSB)>>8);
    cmdByteBuffer[4] = (unsigned char) ( ( ha_ctrl0 & Si2190B_SSVD_HDIV_CMD_HA_CTRL0_MASK ) << Si2190B_SSVD_HDIV_CMD_HA_CTRL0_LSB);
    cmdByteBuffer[5] = (unsigned char) ((( ha_ctrl0 & Si2190B_SSVD_HDIV_CMD_HA_CTRL0_MASK ) << Si2190B_SSVD_HDIV_CMD_HA_CTRL0_LSB)>>8);

    if (L0_WriteCommandBytes(api->i2c, 6, cmdByteBuffer) != 6) {
      SiTRACE("Error writing SSVD_HDIV bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling SSVD_HDIV response\n");
      return error_code;
    }


    return NO_Si21XXC_ERROR;
}
#endif /* Si2190B_SSVD_HDIV_CMD */
#ifdef    Si2190B_SSVD_MULTI_REG_RD_CMD
/*---------------------------------------------------*/
/* Si2190B_SSVD_MULTI_REG_RD COMMAND                 */
/*---------------------------------------------------*/
unsigned char Si2190B_L1_SSVD_MULTI_REG_RD (L1_Si21XXC_Context *api,
                                           unsigned char   reg_sel,
                                           unsigned char   num_regs)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[16];
    api->rsp->ssvd_multi_reg_rd.STATUS = api->status;

    SiTRACE("Si2190B SSVD_MULTI_REG_RD ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((reg_sel  > Si2190B_SSVD_MULTI_REG_RD_CMD_REG_SEL_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("REG_SEL %d " , reg_sel  );
    if ((num_regs > Si2190B_SSVD_MULTI_REG_RD_CMD_NUM_REGS_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("NUM_REGS %d ", num_regs );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2190B_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2190B_SSVD_MULTI_REG_RD_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( reg_sel  & Si2190B_SSVD_MULTI_REG_RD_CMD_REG_SEL_MASK  ) << Si2190B_SSVD_MULTI_REG_RD_CMD_REG_SEL_LSB |
                                         ( num_regs & Si2190B_SSVD_MULTI_REG_RD_CMD_NUM_REGS_MASK ) << Si2190B_SSVD_MULTI_REG_RD_CMD_NUM_REGS_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing SSVD_MULTI_REG_RD bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 16, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling SSVD_MULTI_REG_RD response\n");
      return error_code;
    }

    api->rsp->ssvd_multi_reg_rd.reserved = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si2190B_SSVD_MULTI_REG_RD_RESPONSE_RESERVED_LSB  , Si2190B_SSVD_MULTI_REG_RD_RESPONSE_RESERVED_MASK );
    api->rsp->ssvd_multi_reg_rd.data0    = Si21XXC_convert_to_uint  (&rspByteBuffer[ 2] , Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA0_LSB     , Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA0_MASK    );
    api->rsp->ssvd_multi_reg_rd.data1    = Si21XXC_convert_to_uint  (&rspByteBuffer[ 4] , Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA1_LSB     , Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA1_MASK    );
    api->rsp->ssvd_multi_reg_rd.data2    = Si21XXC_convert_to_uint  (&rspByteBuffer[ 6] , Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA2_LSB     , Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA2_MASK    );
    api->rsp->ssvd_multi_reg_rd.data3    = Si21XXC_convert_to_uint  (&rspByteBuffer[ 8] , Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA3_LSB     , Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA3_MASK    );
    api->rsp->ssvd_multi_reg_rd.data4    = Si21XXC_convert_to_uint  (&rspByteBuffer[10] , Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA4_LSB     , Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA4_MASK    );
    api->rsp->ssvd_multi_reg_rd.data5    = Si21XXC_convert_to_uint  (&rspByteBuffer[12] , Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA5_LSB     , Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA5_MASK    );
    api->rsp->ssvd_multi_reg_rd.data6    = Si21XXC_convert_to_uint  (&rspByteBuffer[14] , Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA6_LSB     , Si2190B_SSVD_MULTI_REG_RD_RESPONSE_DATA6_MASK    );

    return NO_Si21XXC_ERROR;
}
#endif /* Si2190B_SSVD_MULTI_REG_RD_CMD */
#ifdef    Si2190B_SSVD_MULTI_REG_WR_CMD
/*---------------------------------------------------*/
/* Si2190B_SSVD_MULTI_REG_WR COMMAND                 */
/*---------------------------------------------------*/
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
                                           unsigned int    data6)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[16];
    unsigned char rspByteBuffer[1];
    api->rsp->ssvd_multi_reg_wr.STATUS = api->status;

    SiTRACE("Si2190B SSVD_MULTI_REG_WR ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((reg_sel  > Si2190B_SSVD_MULTI_REG_WR_CMD_REG_SEL_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("REG_SEL %d " , reg_sel  );
    if ((update   > Si2190B_SSVD_MULTI_REG_WR_CMD_UPDATE_MAX  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("UPDATE %d "  , update   );
    if ((num_regs > Si2190B_SSVD_MULTI_REG_WR_CMD_NUM_REGS_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("NUM_REGS %d ", num_regs );
    SiTRACE("DATA0 %d "   , data0    );
    SiTRACE("DATA1 %d "   , data1    );
    SiTRACE("DATA2 %d "   , data2    );
    SiTRACE("DATA3 %d "   , data3    );
    SiTRACE("DATA4 %d "   , data4    );
    SiTRACE("DATA5 %d "   , data5    );
    SiTRACE("DATA6 %d "   , data6    );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2190B_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2190B_SSVD_MULTI_REG_WR_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( reg_sel  & Si2190B_SSVD_MULTI_REG_WR_CMD_REG_SEL_MASK  ) << Si2190B_SSVD_MULTI_REG_WR_CMD_REG_SEL_LSB |
                                         ( update   & Si2190B_SSVD_MULTI_REG_WR_CMD_UPDATE_MASK   ) << Si2190B_SSVD_MULTI_REG_WR_CMD_UPDATE_LSB  |
                                         ( num_regs & Si2190B_SSVD_MULTI_REG_WR_CMD_NUM_REGS_MASK ) << Si2190B_SSVD_MULTI_REG_WR_CMD_NUM_REGS_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( data0    & Si2190B_SSVD_MULTI_REG_WR_CMD_DATA0_MASK    ) << Si2190B_SSVD_MULTI_REG_WR_CMD_DATA0_LSB   );
    cmdByteBuffer[3] = (unsigned char) ((( data0    & Si2190B_SSVD_MULTI_REG_WR_CMD_DATA0_MASK    ) << Si2190B_SSVD_MULTI_REG_WR_CMD_DATA0_LSB   )>>8);
    cmdByteBuffer[4] = (unsigned char) ( ( data1    & Si2190B_SSVD_MULTI_REG_WR_CMD_DATA1_MASK    ) << Si2190B_SSVD_MULTI_REG_WR_CMD_DATA1_LSB   );
    cmdByteBuffer[5] = (unsigned char) ((( data1    & Si2190B_SSVD_MULTI_REG_WR_CMD_DATA1_MASK    ) << Si2190B_SSVD_MULTI_REG_WR_CMD_DATA1_LSB   )>>8);
    cmdByteBuffer[6] = (unsigned char) ( ( data2    & Si2190B_SSVD_MULTI_REG_WR_CMD_DATA2_MASK    ) << Si2190B_SSVD_MULTI_REG_WR_CMD_DATA2_LSB   );
    cmdByteBuffer[7] = (unsigned char) ((( data2    & Si2190B_SSVD_MULTI_REG_WR_CMD_DATA2_MASK    ) << Si2190B_SSVD_MULTI_REG_WR_CMD_DATA2_LSB   )>>8);
    cmdByteBuffer[8] = (unsigned char) ( ( data3    & Si2190B_SSVD_MULTI_REG_WR_CMD_DATA3_MASK    ) << Si2190B_SSVD_MULTI_REG_WR_CMD_DATA3_LSB   );
    cmdByteBuffer[9] = (unsigned char) ((( data3    & Si2190B_SSVD_MULTI_REG_WR_CMD_DATA3_MASK    ) << Si2190B_SSVD_MULTI_REG_WR_CMD_DATA3_LSB   )>>8);
    cmdByteBuffer[10] = (unsigned char) ( ( data4    & Si2190B_SSVD_MULTI_REG_WR_CMD_DATA4_MASK    ) << Si2190B_SSVD_MULTI_REG_WR_CMD_DATA4_LSB   );
    cmdByteBuffer[11] = (unsigned char) ((( data4    & Si2190B_SSVD_MULTI_REG_WR_CMD_DATA4_MASK    ) << Si2190B_SSVD_MULTI_REG_WR_CMD_DATA4_LSB   )>>8);
    cmdByteBuffer[12] = (unsigned char) ( ( data5    & Si2190B_SSVD_MULTI_REG_WR_CMD_DATA5_MASK    ) << Si2190B_SSVD_MULTI_REG_WR_CMD_DATA5_LSB   );
    cmdByteBuffer[13] = (unsigned char) ((( data5    & Si2190B_SSVD_MULTI_REG_WR_CMD_DATA5_MASK    ) << Si2190B_SSVD_MULTI_REG_WR_CMD_DATA5_LSB   )>>8);
    cmdByteBuffer[14] = (unsigned char) ( ( data6    & Si2190B_SSVD_MULTI_REG_WR_CMD_DATA6_MASK    ) << Si2190B_SSVD_MULTI_REG_WR_CMD_DATA6_LSB   );
    cmdByteBuffer[15] = (unsigned char) ((( data6    & Si2190B_SSVD_MULTI_REG_WR_CMD_DATA6_MASK    ) << Si2190B_SSVD_MULTI_REG_WR_CMD_DATA6_LSB   )>>8);

    if (L0_WriteCommandBytes(api->i2c, 16, cmdByteBuffer) != 16) {
      SiTRACE("Error writing SSVD_MULTI_REG_WR bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling SSVD_MULTI_REG_WR response\n");
      return error_code;
    }


    return NO_Si21XXC_ERROR;
}
#endif /* Si2190B_SSVD_MULTI_REG_WR_CMD */
#ifdef    Si2190B_SSVD_POWER_DOWN_CMD
/*---------------------------------------------------*/
/* Si2190B_SSVD_POWER_DOWN COMMAND                     */
/*---------------------------------------------------*/
unsigned char Si2190B_L1_SSVD_POWER_DOWN   (L1_Si21XXC_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[1];
    api->rsp->ssvd_power_down.STATUS = api->status;

    SiTRACE("Si2190B SSVD_POWER_DOWN ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2190B_SSVD_POWER_DOWN_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing SSVD_POWER_DOWN bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling SSVD_POWER_DOWN response\n");
      return error_code;
    }


    return NO_Si21XXC_ERROR;
}
#endif /* Si2190B_SSVD_POWER_DOWN_CMD */
#ifdef    Si2190B_SSVD_POWER_UP_CMD
/*---------------------------------------------------*/
/* Si2190B_SSVD_POWER_UP COMMAND                         */
/*---------------------------------------------------*/
unsigned char Si2190B_L1_SSVD_POWER_UP     (L1_Si21XXC_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[1];
    api->rsp->ssvd_power_up.STATUS = api->status;

    SiTRACE("Si2190B SSVD_POWER_UP ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2190B_SSVD_POWER_UP_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing SSVD_POWER_UP bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling SSVD_POWER_UP response\n");
      return error_code;
    }


    return NO_Si21XXC_ERROR;
}
#endif /* Si2190B_SSVD_POWER_UP_CMD */
#ifdef    Si2190B_SSVD_REG_RD_CMD
/*---------------------------------------------------*/
/* Si2190B_SSVD_REG_RD COMMAND                             */
/*---------------------------------------------------*/
unsigned char Si2190B_L1_SSVD_REG_RD       (L1_Si21XXC_Context *api,
                                           unsigned char   reg_sel,
                                           unsigned char   ignored)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[4];
    api->rsp->ssvd_reg_rd.STATUS = api->status;

    SiTRACE("Si2190B SSVD_REG_RD ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((reg_sel > Si2190B_SSVD_REG_RD_CMD_REG_SEL_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("REG_SEL %d ", reg_sel );
    if ((ignored > Si2190B_SSVD_REG_RD_CMD_IGNORED_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("IGNORED %d ", ignored );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2190B_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2190B_SSVD_REG_RD_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( reg_sel & Si2190B_SSVD_REG_RD_CMD_REG_SEL_MASK ) << Si2190B_SSVD_REG_RD_CMD_REG_SEL_LSB|
                                         ( ignored & Si2190B_SSVD_REG_RD_CMD_IGNORED_MASK ) << Si2190B_SSVD_REG_RD_CMD_IGNORED_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing SSVD_REG_RD bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 4, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling SSVD_REG_RD response\n");
      return error_code;
    }

    api->rsp->ssvd_reg_rd.reserved = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si2190B_SSVD_REG_RD_RESPONSE_RESERVED_LSB  , Si2190B_SSVD_REG_RD_RESPONSE_RESERVED_MASK );
    api->rsp->ssvd_reg_rd.data     = Si21XXC_convert_to_uint  (&rspByteBuffer[ 2] , Si2190B_SSVD_REG_RD_RESPONSE_DATA_LSB      , Si2190B_SSVD_REG_RD_RESPONSE_DATA_MASK     );

    return NO_Si21XXC_ERROR;
}
#endif /* Si2190B_SSVD_REG_RD_CMD */
#ifdef    Si2190B_SSVD_REG_WR_CMD
/*---------------------------------------------------*/
/* Si2190B_SSVD_REG_WR COMMAND                             */
/*---------------------------------------------------*/
unsigned char Si2190B_L1_SSVD_REG_WR       (L1_Si21XXC_Context *api,
                                           unsigned char   reg_sel,
                                           unsigned char   update,
                                           unsigned char   ignored,
                                           unsigned int    data)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[4];
    unsigned char rspByteBuffer[1];
    api->rsp->ssvd_reg_wr.STATUS = api->status;

    SiTRACE("Si2190B SSVD_REG_WR ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((reg_sel > Si2190B_SSVD_REG_WR_CMD_REG_SEL_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("REG_SEL %d ", reg_sel );
    if ((update  > Si2190B_SSVD_REG_WR_CMD_UPDATE_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("UPDATE %d " , update  );
    if ((ignored > Si2190B_SSVD_REG_WR_CMD_IGNORED_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("IGNORED %d ", ignored );
    SiTRACE("DATA %d "   , data    );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2190B_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2190B_SSVD_REG_WR_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( reg_sel & Si2190B_SSVD_REG_WR_CMD_REG_SEL_MASK ) << Si2190B_SSVD_REG_WR_CMD_REG_SEL_LSB|
                                         ( update  & Si2190B_SSVD_REG_WR_CMD_UPDATE_MASK  ) << Si2190B_SSVD_REG_WR_CMD_UPDATE_LSB |
                                         ( ignored & Si2190B_SSVD_REG_WR_CMD_IGNORED_MASK ) << Si2190B_SSVD_REG_WR_CMD_IGNORED_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( data    & Si2190B_SSVD_REG_WR_CMD_DATA_MASK    ) << Si2190B_SSVD_REG_WR_CMD_DATA_LSB   );
    cmdByteBuffer[3] = (unsigned char) ((( data    & Si2190B_SSVD_REG_WR_CMD_DATA_MASK    ) << Si2190B_SSVD_REG_WR_CMD_DATA_LSB   )>>8);

    if (L0_WriteCommandBytes(api->i2c, 4, cmdByteBuffer) != 4) {
      SiTRACE("Error writing SSVD_REG_WR bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling SSVD_REG_WR response\n");
      return error_code;
    }


    return NO_Si21XXC_ERROR;
}
#endif /* Si2190B_SSVD_REG_WR_CMD */
#ifdef    Si21XXC_STANDBY_CMD
 /*---------------------------------------------------*/
/* Si21XXC_STANDBY COMMAND                          */
/*---------------------------------------------------*/
unsigned char Si21XXC_L1_STANDBY           (L1_Si21XXC_Context *api,
                                           unsigned char   type)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[1];
    api->rsp->standby.STATUS = api->status;

    SiTRACE("Si21XXC STANDBY ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((type > Si21XXC_STANDBY_CMD_TYPE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("TYPE %d ", type );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si21XXC_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si21XXC_STANDBY_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( type & Si21XXC_STANDBY_CMD_TYPE_MASK ) << Si21XXC_STANDBY_CMD_TYPE_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing STANDBY bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling STANDBY response\n");
      return error_code;
    }


    return NO_Si21XXC_ERROR;
}
#endif /* Si21XXC_STANDBY_CMD */
#ifdef    Si2190B_TUNER_CANCEL_TONE_STATUS_CMD
/*---------------------------------------------------*/
/* Si2190B_TUNER_CANCEL_TONE_STATUS COMMAND          */
/*---------------------------------------------------*/
unsigned char Si2190B_L1_TUNER_CANCEL_TONE_STATUS (L1_Si21XXC_Context *api,
                                                  unsigned char   tc_num)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[6];
    api->rsp->tuner_cancel_tone_status.STATUS = api->status;

    SiTRACE("Si2190B TUNER_CANCEL_TONE_STATUS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((tc_num > Si2190B_TUNER_CANCEL_TONE_STATUS_CMD_TC_NUM_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("TC_NUM %d ", tc_num );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2190B_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2190B_TUNER_CANCEL_TONE_STATUS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( tc_num & Si2190B_TUNER_CANCEL_TONE_STATUS_CMD_TC_NUM_MASK ) << Si2190B_TUNER_CANCEL_TONE_STATUS_CMD_TC_NUM_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing TUNER_CANCEL_TONE_STATUS bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 6, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling TUNER_CANCEL_TONE_STATUS response\n");
      return error_code;
    }

    api->rsp->tuner_cancel_tone_status.active   = Si21XXC_convert_to_byte  (&rspByteBuffer[ 3] , Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_ACTIVE_LSB    , Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_ACTIVE_MASK   );
    api->rsp->tuner_cancel_tone_status.status   = Si21XXC_convert_to_byte  (&rspByteBuffer[ 3] , Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_STATUS_LSB    , Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_STATUS_MASK   );
    api->rsp->tuner_cancel_tone_status.type     = Si21XXC_convert_to_byte  (&rspByteBuffer[ 3] , Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_TYPE_LSB      , Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_TYPE_MASK     );
    api->rsp->tuner_cancel_tone_status.freq_khz = Si21XXC_convert_to_int   (&rspByteBuffer[ 4] , Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_FREQ_KHZ_LSB  , Si2190B_TUNER_CANCEL_TONE_STATUS_RESPONSE_FREQ_KHZ_MASK );

    return NO_Si21XXC_ERROR;
}
#endif /* Si2190B_TUNER_CANCEL_TONE_STATUS_CMD */
#ifdef    Si2190B_TUNER_CANCEL_TONE_CMD
/*---------------------------------------------------*/
/* Si2191C_TUNER_CANCEL_TONE COMMAND                 */
/*---------------------------------------------------*/
unsigned char Si2190B_L1_TUNER_CANCEL_TONE (L1_Si21XXC_Context *api,
                                           unsigned int    div_a,
                                           unsigned int    div_b)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[8];
    unsigned char rspByteBuffer[1];
    api->rsp->tuner_cancel_tone.STATUS = api->status;

    SiTRACE("Si2190B TUNER_CANCEL_TONE ");
  #ifdef   DEBUG_RANGE_CHECK
    SiTRACE("DIV_A %d ", div_a );
    SiTRACE("DIV_B %d ", div_b );
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2190B_TUNER_CANCEL_TONE_CMD;
    cmdByteBuffer[1] = (unsigned char)0x00;
    cmdByteBuffer[2] = (unsigned char)0x00;
    cmdByteBuffer[3] = (unsigned char)0x00;
    cmdByteBuffer[4] = (unsigned char) ( ( div_a & Si2190B_TUNER_CANCEL_TONE_CMD_DIV_A_MASK ) << Si2190B_TUNER_CANCEL_TONE_CMD_DIV_A_LSB);
    cmdByteBuffer[5] = (unsigned char) ((( div_a & Si2190B_TUNER_CANCEL_TONE_CMD_DIV_A_MASK ) << Si2190B_TUNER_CANCEL_TONE_CMD_DIV_A_LSB)>>8);
    cmdByteBuffer[6] = (unsigned char) ( ( div_b & Si2190B_TUNER_CANCEL_TONE_CMD_DIV_B_MASK ) << Si2190B_TUNER_CANCEL_TONE_CMD_DIV_B_LSB);
    cmdByteBuffer[7] = (unsigned char) ((( div_b & Si2190B_TUNER_CANCEL_TONE_CMD_DIV_B_MASK ) << Si2190B_TUNER_CANCEL_TONE_CMD_DIV_B_LSB)>>8);

    if (L0_WriteCommandBytes(api->i2c, 8, cmdByteBuffer) != 8) {
      SiTRACE("Error writing TUNER_CANCEL_TONE bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling TUNER_CANCEL_TONE response\n");
      return error_code;
    }


    return NO_Si21XXC_ERROR;
}
#endif /* Si2190B_TUNER_CANCEL_TONE_CMD */

#ifdef    Si21XXC_TUNER_STATUS_CMD
 /*---------------------------------------------------*/
/* Si21XXC_TUNER_STATUS COMMAND                     */
/*---------------------------------------------------*/
unsigned char Si21XXC_L1_TUNER_STATUS      (L1_Si21XXC_Context *api,
                                           unsigned char   intack)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[16];
    api->rsp->tuner_status.STATUS = api->status;

    SiTRACE("Si21XXC TUNER_STATUS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((intack > Si21XXC_TUNER_STATUS_CMD_INTACK_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("INTACK %d ", intack );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si21XXC_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si21XXC_TUNER_STATUS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( intack & Si21XXC_TUNER_STATUS_CMD_INTACK_MASK ) << Si21XXC_TUNER_STATUS_CMD_INTACK_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing TUNER_STATUS bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 16, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling TUNER_STATUS response\n");
      return error_code;
    }

    api->rsp->tuner_status.tcint    = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si21XXC_TUNER_STATUS_RESPONSE_TCINT_LSB     , Si21XXC_TUNER_STATUS_RESPONSE_TCINT_MASK    );
    api->rsp->tuner_status.rssilint = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si21XXC_TUNER_STATUS_RESPONSE_RSSILINT_LSB  , Si21XXC_TUNER_STATUS_RESPONSE_RSSILINT_MASK );
    api->rsp->tuner_status.rssihint = Si21XXC_convert_to_byte  (&rspByteBuffer[ 1] , Si21XXC_TUNER_STATUS_RESPONSE_RSSIHINT_LSB  , Si21XXC_TUNER_STATUS_RESPONSE_RSSIHINT_MASK );
    api->rsp->tuner_status.tc       = Si21XXC_convert_to_byte  (&rspByteBuffer[ 2] , Si21XXC_TUNER_STATUS_RESPONSE_TC_LSB        , Si21XXC_TUNER_STATUS_RESPONSE_TC_MASK       );
    api->rsp->tuner_status.rssil    = Si21XXC_convert_to_byte  (&rspByteBuffer[ 2] , Si21XXC_TUNER_STATUS_RESPONSE_RSSIL_LSB     , Si21XXC_TUNER_STATUS_RESPONSE_RSSIL_MASK    );
    api->rsp->tuner_status.rssih    = Si21XXC_convert_to_byte  (&rspByteBuffer[ 2] , Si21XXC_TUNER_STATUS_RESPONSE_RSSIH_LSB     , Si21XXC_TUNER_STATUS_RESPONSE_RSSIH_MASK    );
    api->rsp->tuner_status.rssi     = Si21XXC_convert_to_byte  (&rspByteBuffer[ 3] , Si21XXC_TUNER_STATUS_RESPONSE_RSSI_LSB      , Si21XXC_TUNER_STATUS_RESPONSE_RSSI_MASK     );
    api->rsp->tuner_status.freq     = Si21XXC_convert_to_ulong (&rspByteBuffer[ 4] , Si21XXC_TUNER_STATUS_RESPONSE_FREQ_LSB      , Si21XXC_TUNER_STATUS_RESPONSE_FREQ_MASK     );
    api->rsp->tuner_status.mode     = Si21XXC_convert_to_byte  (&rspByteBuffer[ 8] , Si21XXC_TUNER_STATUS_RESPONSE_MODE_LSB      , Si21XXC_TUNER_STATUS_RESPONSE_MODE_MASK     );
    api->rsp->tuner_status.wb_att_status = Si21XXC_convert_to_byte  (&rspByteBuffer[ 8] , Si21XXC_TUNER_STATUS_RESPONSE_WB_ATT_STATUS_LSB  , Si21XXC_TUNER_STATUS_RESPONSE_WB_ATT_STATUS_MASK );
    api->rsp->tuner_status.sample_freq   = Si21XXC_convert_to_byte  (&rspByteBuffer[ 9] , Si21XXC_TUNER_STATUS_RESPONSE_SAMPLE_FREQ_LSB    , Si21XXC_TUNER_STATUS_RESPONSE_SAMPLE_FREQ_MASK   );
    api->rsp->tuner_status.vco_code = Si21XXC_convert_to_int   (&rspByteBuffer[10] , Si21XXC_TUNER_STATUS_RESPONSE_VCO_CODE_LSB  , Si21XXC_TUNER_STATUS_RESPONSE_VCO_CODE_MASK );
    api->rsp->tuner_status.lo_freq  = Si21XXC_convert_to_ulong (&rspByteBuffer[12] , Si21XXC_TUNER_STATUS_RESPONSE_LO_FREQ_LSB        , Si21XXC_TUNER_STATUS_RESPONSE_LO_FREQ_MASK       );


    return NO_Si21XXC_ERROR;
}
#endif /* Si21XXC_TUNER_STATUS_CMD */
#ifdef    Si21XXC_TUNER_TUNE_FREQ_CMD
 /*---------------------------------------------------*/
/* Si21XXC_TUNER_TUNE_FREQ COMMAND                  */
/*---------------------------------------------------*/
unsigned char Si21XXC_L1_TUNER_TUNE_FREQ   (L1_Si21XXC_Context *api,
                                           unsigned char   mode,
                                           unsigned long   freq)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[8];
    unsigned char rspByteBuffer[1];
    api->rsp->tuner_tune_freq.STATUS = api->status;

    SiTRACE("Si21XXC TUNER_TUNE_FREQ ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((mode > Si21XXC_TUNER_TUNE_FREQ_CMD_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("MODE %d ", mode );
    if ((freq > Si21XXC_TUNER_TUNE_FREQ_CMD_FREQ_MAX)  || (freq < Si21XXC_TUNER_TUNE_FREQ_CMD_FREQ_MIN) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FREQ %d ", freq );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si21XXC_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si21XXC_TUNER_TUNE_FREQ_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( mode & Si21XXC_TUNER_TUNE_FREQ_CMD_MODE_MASK ) << Si21XXC_TUNER_TUNE_FREQ_CMD_MODE_LSB);
    cmdByteBuffer[2] = (unsigned char)0x00;
    cmdByteBuffer[3] = (unsigned char)0x00;
    cmdByteBuffer[4] = (unsigned char) ( ( freq & Si21XXC_TUNER_TUNE_FREQ_CMD_FREQ_MASK ) << Si21XXC_TUNER_TUNE_FREQ_CMD_FREQ_LSB);
    cmdByteBuffer[5] = (unsigned char) ((( freq & Si21XXC_TUNER_TUNE_FREQ_CMD_FREQ_MASK ) << Si21XXC_TUNER_TUNE_FREQ_CMD_FREQ_LSB)>>8);
    cmdByteBuffer[6] = (unsigned char) ((( freq & Si21XXC_TUNER_TUNE_FREQ_CMD_FREQ_MASK ) << Si21XXC_TUNER_TUNE_FREQ_CMD_FREQ_LSB)>>16);
    cmdByteBuffer[7] = (unsigned char) ((( freq & Si21XXC_TUNER_TUNE_FREQ_CMD_FREQ_MASK ) << Si21XXC_TUNER_TUNE_FREQ_CMD_FREQ_LSB)>>24);

    if (L0_WriteCommandBytes(api->i2c, 8, cmdByteBuffer) != 8) {
      SiTRACE("Error writing TUNER_TUNE_FREQ bytes!\n");
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    error_code = Si21XXC_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling TUNER_TUNE_FREQ response\n");
      return error_code;
    }


    return NO_Si21XXC_ERROR;
}
#endif /* Si21XXC_TUNER_TUNE_FREQ_CMD */
/* _commands_insertion_point */

/* _send_command2_insertion_start */

  /* --------------------------------------------*/
  /* SEND_COMMAND2 FUNCTION                      */
  /* --------------------------------------------*/
unsigned char   Si21XXC_L1_SendCommand2(L1_Si21XXC_Context *api, unsigned int cmd_code) {
    switch (cmd_code) {
    #ifdef        Si21XXC_AGC_OVERRIDE_CMD
     case         Si21XXC_AGC_OVERRIDE_CMD_CODE:
       return Si21XXC_L1_AGC_OVERRIDE (api, api->cmd->agc_override.force_max_gain, api->cmd->agc_override.force_top_gain );
     break;
    #endif /*     Si21XXC_AGC_OVERRIDE_CMD */
    #ifdef        Si21XXC_ATV_RESTART_CMD
     case         Si21XXC_ATV_RESTART_CMD_CODE:
       return Si21XXC_L1_ATV_RESTART (api, api->cmd->atv_restart.mode );
     break;
    #endif /*     Si21XXC_ATV_RESTART_CMD */
    #ifdef        Si21XXC_ATV_STATUS_CMD
     case         Si21XXC_ATV_STATUS_CMD_CODE:
       return Si21XXC_L1_ATV_STATUS (api, api->cmd->atv_status.intack );
     break;
    #endif /*     Si21XXC_ATV_STATUS_CMD */
    #ifdef        Si21XXC_CONFIG_CLOCKS_CMD
     case         Si21XXC_CONFIG_CLOCKS_CMD_CODE:
       return Si21XXC_L1_CONFIG_CLOCKS (api, api->cmd->config_clocks.subcode, api->cmd->config_clocks.clock_mode, api->cmd->config_clocks.en_xout );
     break;
    #endif /*     Si21XXC_CONFIG_CLOCKS_CMD */
    #ifdef        Si21XXC_CONFIG_I2C_CMD
     case         Si21XXC_CONFIG_I2C_CMD_CODE:
       return Si21XXC_L1_CONFIG_I2C (api, api->cmd->config_i2c.subcode, api->cmd->config_i2c.i2c_broadcast );
     break;
    #endif /*     Si21XXC_CONFIG_I2C_CMD */
    #ifdef        Si2178B_CONFIG_PINS_CMD
     case         Si2178B_CONFIG_PINS_CMD_CODE:
       return Si2178B_L1_CONFIG_PINS (api, api->cmd->config_pins.gpio1_mode, api->cmd->config_pins.gpio1_read, api->cmd->config_pins.gpio2_mode, api->cmd->config_pins.gpio2_read, api->cmd->config_pins.reserved1, api->cmd->config_pins.reserved2, api->cmd->config_pins.reserved3 );
     break;
    #endif /*     Si2178B_CONFIG_PINS_CMD */
    #ifdef        Si2190B_CONFIG_PINS_CMD
     case         Si2190B_CONFIG_PINS_CMD_CODE:
       return Si2190B_L1_CONFIG_PINS (api, api->cmd->config_pins.gpio1_mode, api->cmd->config_pins.gpio1_read, api->cmd->config_pins.gpio2_mode, api->cmd->config_pins.gpio2_read, api->cmd->config_pins.agc1_mode, api->cmd->config_pins.agc1_read,api->cmd->config_pins.agc2_mode, api->cmd->config_pins.agc2_read,api->cmd->config_pins.reserved3 );
     break;
    #endif /*     Si2190B_CONFIG_PINS_CMD */
    #ifdef        Si2190B_DTV_RESTART_CMD
     case         Si2190B_DTV_RESTART_CMD_CODE:
       return Si2190B_L1_DTV_RESTART (api );
     break;
    #endif /*     Si2190B_DTV_RESTART_CMD */
    #ifdef        Si2190B_DTV_STATUS_CMD
     case         Si2190B_DTV_STATUS_CMD_CODE:
       return Si2190B_L1_DTV_STATUS (api, api->cmd->dtv_status.intack );
     break;
    #endif /*     Si2190B_DTV_STATUS_CMD */
    #ifdef        Si2190B_EXIT_BOOTLOADER_CMD
     case         Si2190B_EXIT_BOOTLOADER_CMD_CODE:
       return Si2190B_L1_EXIT_BOOTLOADER (api, api->cmd->exit_bootloader.func, api->cmd->exit_bootloader.ctsien );
     break;
    #endif /*     Si2190B_EXIT_BOOTLOADER_CMD */
    #ifdef        Si2190B_FINE_TUNE_CMD
     case         Si2190B_FINE_TUNE_CMD_CODE:
       return Si2190B_L1_FINE_TUNE (api, api->cmd->fine_tune.persistence, api->cmd->fine_tune.offset_500hz );
     break;
    #endif /*     Si2190B_FINE_TUNE_CMD */
    #ifdef        Si2190B_GET_PROPERTY_CMD
     case         Si2190B_GET_PROPERTY_CMD_CODE:
       return Si2190B_L1_GET_PROPERTY (api, api->cmd->get_property.reserved, api->cmd->get_property.prop );
     break;
    #endif /*     Si2190B_GET_PROPERTY_CMD */
    #ifdef        Si2190B_GET_REV_CMD
     case         Si2190B_GET_REV_CMD_CODE:
       return Si2190B_L1_GET_REV (api );
     break;
    #endif /*     Si2190B_GET_REV_CMD */
    #ifdef        Si2191C_ISL_STATUS_CMD
     case         Si2191C_ISL_STATUS_CMD_CODE:
       return Si2191C_L1_ISL_STATUS(api, api->cmd->isl_status.clear );
     break;
    #endif /*     Si2191C_ISL_STATUS_CMD */
    #ifdef        Si2190B_PART_INFO_CMD
     case         Si2190B_PART_INFO_CMD_CODE:
       return Si2190B_L1_PART_INFO (api );
     break;
    #endif /*     Si2190B_PART_INFO_CMD */
    #ifdef        Si2190B_PART_INFO2_CMD
     case         Si2190B_PART_INFO2_CMD_CODE:
       return Si2190B_L1_PART_INFO2 (api );
     break;
    #endif /*     Si2190B_PART_INFO2_CMD */
    #ifdef        Si2190B_POWER_DOWN_HW_CMD
     case         Si2190B_POWER_DOWN_HW_CMD_CODE:
       return Si2190B_L1_POWER_DOWN_HW (api, api->cmd->power_down_hw.subcode, api->cmd->power_down_hw.pd_xo_osc, api->cmd->power_down_hw.reserved1, api->cmd->power_down_hw.en_xout, api->cmd->power_down_hw.reserved2, api->cmd->power_down_hw.pd_ldo, api->cmd->power_down_hw.reserved3, api->cmd->power_down_hw.reserved4, api->cmd->power_down_hw.reserved5, api->cmd->power_down_hw.reserved6, api->cmd->power_down_hw.reserved7, api->cmd->power_down_hw.reserved8 );
     break;
    #endif /*     Si2190B_POWER_DOWN_HW_CMD */
    #ifdef        Si2190B_POWER_UP_CMD
     case         Si2190B_POWER_UP_CMD_CODE:
       return Si2190B_L1_POWER_UP (api, api->cmd->power_up.subcode, api->cmd->power_up.clock_mode, api->cmd->power_up.en_xout, api->cmd->power_up.pd_ldo, api->cmd->power_up.reserved2, api->cmd->power_up.reserved3, api->cmd->power_up.reserved4, api->cmd->power_up.reserved5, api->cmd->power_up.reserved6, api->cmd->power_up.reserved7, api->cmd->power_up.reset, api->cmd->power_up.clock_freq, api->cmd->power_up.reserved8, api->cmd->power_up.func, api->cmd->power_up.ctsien, api->cmd->power_up.wake_up );
     break;
    #endif /*     Si2190B_POWER_UP_CMD */
    #ifdef        Si2190B_REREAD_REPLY_CMD
     case         Si2190B_REREAD_REPLY_CMD_CODE:
       return Si2190B_L1_REREAD_REPLY (api, api->cmd->reread_reply.offset );
     break;
    #endif /*     Si2190B_REREAD_REPLY_CMD */
    #ifdef        Si2190B_RESET_HW_CMD
     case         Si2190B_RESET_HW_CMD_CODE:
       return Si2190B_L1_RESET_HW (api, api->cmd->reset_hw.subcode, api->cmd->reset_hw.reserved1, api->cmd->reset_hw.reserved2 );
     break;
    #endif /*     Si2190B_RESET_HW_CMD */
    #ifdef        Si2190B_SELF_TEST_CMD
     case         Si2190B_SELF_TEST_CMD_CODE:
       return Si2190B_L1_SELF_TEST (api );
     break;
    #endif /*     Si2190B_SELF_TEST_CMD */
    #ifdef        Si2190B_SET_PROPERTY_CMD
     case         Si2190B_SET_PROPERTY_CMD_CODE:
       return Si2190B_L1_SET_PROPERTY (api, api->cmd->set_property.reserved, api->cmd->set_property.prop, api->cmd->set_property.data );
     break;
    #endif /*     Si2190B_SET_PROPERTY_CMD */
    #ifdef        Si2190B_SSVD_DEBUG_CONFIG_CMD
     case         Si2190B_SSVD_DEBUG_CONFIG_CMD_CODE:
       return Si2190B_L1_SSVD_DEBUG_CONFIG (api, api->cmd->ssvd_debug_config.cvbs_out, api->cmd->ssvd_debug_config.sif_out );
     break;
    #endif /*     Si2190B_SSVD_DEBUG_CONFIG_CMD */
    #ifdef        Si2190B_SSVD_HDIV_CMD
     case         Si2190B_SSVD_HDIV_CMD_CODE:
       return Si2190B_L1_SSVD_HDIV (api, api->cmd->ssvd_hdiv.enable, api->cmd->ssvd_hdiv.st_ctrl0, api->cmd->ssvd_hdiv.ha_ctrl0 );
     break;
    #endif /*     Si2190B_SSVD_HDIV_CMD */
    #ifdef        Si2190B_SSVD_MULTI_REG_RD_CMD
     case         Si2190B_SSVD_MULTI_REG_RD_CMD_CODE:
       return Si2190B_L1_SSVD_MULTI_REG_RD (api, api->cmd->ssvd_multi_reg_rd.reg_sel, api->cmd->ssvd_multi_reg_rd.num_regs );
     break;
    #endif /*     Si2190B_SSVD_MULTI_REG_RD_CMD */
    #ifdef        Si2190B_SSVD_MULTI_REG_WR_CMD
     case         Si2190B_SSVD_MULTI_REG_WR_CMD_CODE:
       return Si2190B_L1_SSVD_MULTI_REG_WR (api, api->cmd->ssvd_multi_reg_wr.reg_sel, api->cmd->ssvd_multi_reg_wr.update, api->cmd->ssvd_multi_reg_wr.num_regs, api->cmd->ssvd_multi_reg_wr.data0, api->cmd->ssvd_multi_reg_wr.data1, api->cmd->ssvd_multi_reg_wr.data2, api->cmd->ssvd_multi_reg_wr.data3, api->cmd->ssvd_multi_reg_wr.data4, api->cmd->ssvd_multi_reg_wr.data5, api->cmd->ssvd_multi_reg_wr.data6 );
     break;
    #endif /*     Si2190B_SSVD_MULTI_REG_WR_CMD */
    #ifdef        Si2190B_SSVD_POWER_DOWN_CMD
     case         Si2190B_SSVD_POWER_DOWN_CMD_CODE:
       return Si2190B_L1_SSVD_POWER_DOWN (api );
     break;
    #endif /*     Si2190B_SSVD_POWER_DOWN_CMD */
    #ifdef        Si2190B_SSVD_POWER_UP_CMD
     case         Si2190B_SSVD_POWER_UP_CMD_CODE:
       return Si2190B_L1_SSVD_POWER_UP (api );
     break;
    #endif /*     Si2190B_SSVD_POWER_UP_CMD */
    #ifdef        Si2190B_SSVD_REG_RD_CMD
     case         Si2190B_SSVD_REG_RD_CMD_CODE:
       return Si2190B_L1_SSVD_REG_RD (api, api->cmd->ssvd_reg_rd.reg_sel, api->cmd->ssvd_reg_rd.ignored );
     break;
    #endif /*     Si2190B_SSVD_REG_RD_CMD */
    #ifdef        Si2190B_SSVD_REG_WR_CMD
     case         Si2190B_SSVD_REG_WR_CMD_CODE:
       return Si2190B_L1_SSVD_REG_WR (api, api->cmd->ssvd_reg_wr.reg_sel, api->cmd->ssvd_reg_wr.update, api->cmd->ssvd_reg_wr.ignored, api->cmd->ssvd_reg_wr.data );
     break;
    #endif /*     Si2190B_SSVD_REG_WR_CMD */
    #ifdef        Si2190B_STANDBY_CMD
     case         Si2190B_STANDBY_CMD_CODE:
       return Si2190B_L1_STANDBY (api, api->cmd->standby.type );
     break;
    #endif /*     Si2190B_STANDBY_CMD */
    #ifdef        Si2190B_TUNER_CANCEL_TONE_STATUS_CMD
     case         Si2190B_TUNER_CANCEL_TONE_STATUS_CMD_CODE:
       return Si2190B_L1_TUNER_CANCEL_TONE_STATUS (api, api->cmd->tuner_cancel_tone_status.tc_num );
     break;
    #endif /*     Si2190B_TUNER_CANCEL_TONE_STATUS_CMD */
    #ifdef        Si2190B_TUNER_CANCEL_TONE_CMD
     case         Si2190B_TUNER_CANCEL_TONE_CMD_CODE:
       return Si2190B_L1_TUNER_CANCEL_TONE (api, api->cmd->tuner_cancel_tone.div_a, api->cmd->tuner_cancel_tone.div_b );
     break;
   #endif /*     Si2190B_TUNER_CANCEL_TONE_CMD */
    #ifdef        Si2190B_TUNER_STATUS_CMD
     case         Si2190B_TUNER_STATUS_CMD_CODE:
       return Si2190B_L1_TUNER_STATUS (api, api->cmd->tuner_status.intack );
     break;
    #endif /*     Si2190B_TUNER_STATUS_CMD */
    #ifdef        Si2190B_TUNER_TUNE_FREQ_CMD
     case         Si2190B_TUNER_TUNE_FREQ_CMD_CODE:
       return Si2190B_L1_TUNER_TUNE_FREQ (api, api->cmd->tuner_tune_freq.mode, api->cmd->tuner_tune_freq.freq );
     break;
    #endif /*     Si2190B_TUNER_TUNE_FREQ_CMD */
   default : break;
    }
     return 0;
  }
  /* _send_command2_insertion_point */

#ifdef    Si21XXC_GET_COMMAND_STRINGS
/* _get_command_response_string_insertion_start */

  /* --------------------------------------------*/
  /* GET_COMMAND_RESPONSE_STRING FUNCTION        */
  /* --------------------------------------------*/
unsigned char   Si21XXC_L1_GetCommandResponseString(L1_Si21XXC_Context *api, unsigned int cmd_code, const char *separator, char *msg) {
#ifdef SEM_DEBUG//20120914,SSVD,ADD.
    switch (cmd_code) {
    #ifdef        Si21XXC_AGC_OVERRIDE_CMD
     case         Si21XXC_AGC_OVERRIDE_CMD_CODE:
      safe_sprintf(msg,"AGC_OVERRIDE ");
      safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT ");
           if  (api->rsp->agc_override.STATUS->tunint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->agc_override.STATUS->tunint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                     safe_sprintf(msg,"%s%d", msg, api->rsp->agc_override.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT ");
           if  (api->rsp->agc_override.STATUS->atvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->agc_override.STATUS->atvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                     safe_sprintf(msg,"%s%d", msg, api->rsp->agc_override.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT ");
           if  (api->rsp->agc_override.STATUS->dtvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->agc_override.STATUS->dtvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                     safe_sprintf(msg,"%s%d", msg, api->rsp->agc_override.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR    ");
           if  (api->rsp->agc_override.STATUS->err    ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->agc_override.STATUS->err    ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                     safe_sprintf(msg,"%s%d", msg, api->rsp->agc_override.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS    ");
           if  (api->rsp->agc_override.STATUS->cts    ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->agc_override.STATUS->cts    ==     0) safe_strcat(msg,"WAIT     ");
      else                                                     safe_sprintf(msg,"%s%d", msg, api->rsp->agc_override.STATUS->cts);
     break;
    #endif /*     Si21XXC_AGC_OVERRIDE_CMD */

    #ifdef        Si21XXC_ATV_RESTART_CMD
     case         Si21XXC_ATV_RESTART_CMD_CODE:
      safe_sprintf(msg,"ATV_RESTART ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT ");
           if  (api->rsp->atv_restart.STATUS->tunint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->atv_restart.STATUS->tunint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                    safe_sprintf(msg,"%s%d", msg, api->rsp->atv_restart.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT ");
           if  (api->rsp->atv_restart.STATUS->atvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->atv_restart.STATUS->atvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                    safe_sprintf(msg,"%s%d", msg, api->rsp->atv_restart.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT ");
           if  (api->rsp->atv_restart.STATUS->dtvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->atv_restart.STATUS->dtvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                    safe_sprintf(msg,"%s%d", msg, api->rsp->atv_restart.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR    ");
           if  (api->rsp->atv_restart.STATUS->err    ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->atv_restart.STATUS->err    ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                    safe_sprintf(msg,"%s%d", msg, api->rsp->atv_restart.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS    ");
           if  (api->rsp->atv_restart.STATUS->cts    ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->atv_restart.STATUS->cts    ==     0) safe_strcat(msg,"WAIT     ");
      else                                                    safe_sprintf(msg,"%s%d", msg, api->rsp->atv_restart.STATUS->cts);
     break;
    #endif /*     Si21XXC_ATV_RESTART_CMD */

    #ifdef        Si21XXC_ATV_STATUS_CMD
     case         Si21XXC_ATV_STATUS_CMD_CODE:
      safe_sprintf(msg,"ATV_STATUS ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT           ");
           if  (api->rsp->atv_status.STATUS->tunint           ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->atv_status.STATUS->tunint           ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                             safe_sprintf(msg,"%s%d", msg, api->rsp->atv_status.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT           ");
           if  (api->rsp->atv_status.STATUS->atvint           ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->atv_status.STATUS->atvint           ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                             safe_sprintf(msg,"%s%d", msg, api->rsp->atv_status.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT           ");
           if  (api->rsp->atv_status.STATUS->dtvint           ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->atv_status.STATUS->dtvint           ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                             safe_sprintf(msg,"%s%d", msg, api->rsp->atv_status.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR              ");
           if  (api->rsp->atv_status.STATUS->err              ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->atv_status.STATUS->err              ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                             safe_sprintf(msg,"%s%d", msg, api->rsp->atv_status.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS              ");
           if  (api->rsp->atv_status.STATUS->cts              ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->atv_status.STATUS->cts              ==     0) safe_strcat(msg,"WAIT     ");
      else                                                             safe_sprintf(msg,"%s%d", msg, api->rsp->atv_status.STATUS->cts);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CHLINT           ");
           if  (api->rsp->atv_status.chlint           ==     1) safe_strcat(msg,"CHANGED  ");
      else if  (api->rsp->atv_status.chlint           ==     0) safe_strcat(msg,"NO_CHANGE");
      else                                                     safe_sprintf(msg,"%s%d", msg, api->rsp->atv_status.chlint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-PCLINT           ");
           if  (api->rsp->atv_status.pclint           ==     1) safe_strcat(msg,"CHANGED  ");
      else if  (api->rsp->atv_status.pclint           ==     0) safe_strcat(msg,"NO_CHANGE");
      else                                                     safe_sprintf(msg,"%s%d", msg, api->rsp->atv_status.pclint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DLINT            ");
           if  (api->rsp->atv_status.dlint            ==     1) safe_strcat(msg,"CHANGED  ");
      else if  (api->rsp->atv_status.dlint            ==     0) safe_strcat(msg,"NO_CHANGE");
      else                                                     safe_sprintf(msg,"%s%d", msg, api->rsp->atv_status.dlint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-SNRLINT          ");
           if  (api->rsp->atv_status.snrlint          ==     1) safe_strcat(msg,"CHANGED  ");
      else if  (api->rsp->atv_status.snrlint          ==     0) safe_strcat(msg,"NO_CHANGE");
      else                                                     safe_sprintf(msg,"%s%d", msg, api->rsp->atv_status.snrlint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-SNRHINT          ");
           if  (api->rsp->atv_status.snrhint          ==     1) safe_strcat(msg,"CHANGED  ");
      else if  (api->rsp->atv_status.snrhint          ==     0) safe_strcat(msg,"NO_CHANGE");
      else                                                     safe_sprintf(msg,"%s%d", msg, api->rsp->atv_status.snrhint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CHL              ");
           if  (api->rsp->atv_status.chl              ==     1) safe_strcat(msg,"CHANNEL   ");
      else if  (api->rsp->atv_status.chl              ==     0) safe_strcat(msg,"NO_CHANNEL");
      else                                                     safe_sprintf(msg,"%s%d", msg, api->rsp->atv_status.chl);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-PCL              ");
           if  (api->rsp->atv_status.pcl              ==     1) safe_strcat(msg,"LOCKED ");
      else if  (api->rsp->atv_status.pcl              ==     0) safe_strcat(msg,"NO_LOCK");
      else                                                     safe_sprintf(msg,"%s%d", msg, api->rsp->atv_status.pcl);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DL               ");
           if  (api->rsp->atv_status.dl               ==     1) safe_strcat(msg,"LOCKED ");
      else if  (api->rsp->atv_status.dl               ==     0) safe_strcat(msg,"NO_LOCK");
      else                                                     safe_sprintf(msg,"%s%d", msg, api->rsp->atv_status.dl);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-SNRL             ");
           if  (api->rsp->atv_status.snrl             ==     1) safe_strcat(msg,"SNR_LOW    ");
      else if  (api->rsp->atv_status.snrl             ==     0) safe_strcat(msg,"SNR_NOT_LOW");
      else                                                     safe_sprintf(msg,"%s%d", msg, api->rsp->atv_status.snrl);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-SNRH             ");
           if  (api->rsp->atv_status.snrh             ==     1) safe_strcat(msg,"SNR_HIGH    ");
      else if  (api->rsp->atv_status.snrh             ==     0) safe_strcat(msg,"SNR_NOT_HIGH");
      else                                                     safe_sprintf(msg,"%s%d", msg, api->rsp->atv_status.snrh);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-VIDEO_SNR        "); safe_sprintf(msg,"%s%d", msg, api->rsp->atv_status.video_snr);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-AFC_FREQ         "); safe_sprintf(msg,"%s%d", msg, api->rsp->atv_status.afc_freq);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-VIDEO_SC_SPACING "); safe_sprintf(msg,"%s%d", msg, api->rsp->atv_status.video_sc_spacing);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-VIDEO_SYS        ");
           if  (api->rsp->atv_status.video_sys        ==     0) safe_strcat(msg,"B ");
      else if  (api->rsp->atv_status.video_sys        ==     5) safe_strcat(msg,"DK");
      else if  (api->rsp->atv_status.video_sys        ==     1) safe_strcat(msg,"GH");
      else if  (api->rsp->atv_status.video_sys        ==     4) safe_strcat(msg,"I ");
      else if  (api->rsp->atv_status.video_sys        ==     6) safe_strcat(msg,"L ");
      else if  (api->rsp->atv_status.video_sys        ==     7) safe_strcat(msg,"LP");
      else if  (api->rsp->atv_status.video_sys        ==     2) safe_strcat(msg,"M ");
      else if  (api->rsp->atv_status.video_sys        ==     3) safe_strcat(msg,"N ");
      else                                                     safe_sprintf(msg,"%s%d", msg, api->rsp->atv_status.video_sys);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-COLOR            ");
           if  (api->rsp->atv_status.color            ==     0) safe_strcat(msg,"PAL_NTSC");
      else if  (api->rsp->atv_status.color            ==     1) safe_strcat(msg,"SECAM   ");
      else                                                     safe_sprintf(msg,"%s%d", msg, api->rsp->atv_status.color);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-LINES            ");
           if  (api->rsp->atv_status.lines            ==     0) safe_strcat(msg,"525");
      else if  (api->rsp->atv_status.lines            ==     1) safe_strcat(msg,"625");
      else                                                     safe_sprintf(msg,"%s%d", msg, api->rsp->atv_status.lines);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-AUDIO_SYS        ");
           if  (api->rsp->atv_status.audio_sys        ==     3) safe_strcat(msg,"A2             ");
      else if  (api->rsp->atv_status.audio_sys        ==     4) safe_strcat(msg,"A2_DK2         ");
      else if  (api->rsp->atv_status.audio_sys        ==     5) safe_strcat(msg,"A2_DK3         ");
      else if  (api->rsp->atv_status.audio_sys        ==     9) safe_strcat(msg,"A2_DK4         ");
      else if  (api->rsp->atv_status.audio_sys        ==     6) safe_strcat(msg,"BTSC           ");
      else if  (api->rsp->atv_status.audio_sys        ==     7) safe_strcat(msg,"EIAJ           ");
      else if  (api->rsp->atv_status.audio_sys        ==     1) safe_strcat(msg,"MONO           ");
      else if  (api->rsp->atv_status.audio_sys        ==     2) safe_strcat(msg,"MONO_NICAM     ");
      else if  (api->rsp->atv_status.audio_sys        ==    12) safe_strcat(msg,"MONO_NICAM_10DB");
      else if  (api->rsp->atv_status.audio_sys        ==    11) safe_strcat(msg,"MONO_NICAM_6DB ");
      else if  (api->rsp->atv_status.audio_sys        ==     0) safe_strcat(msg,"RSVD           ");
      else if  (api->rsp->atv_status.audio_sys        ==     8) safe_strcat(msg,"SCAN           ");
      else if  (api->rsp->atv_status.audio_sys        ==    10) safe_strcat(msg,"WIDE_SCAN      ");
      else                                                     safe_sprintf(msg,"%s%d", msg, api->rsp->atv_status.audio_sys);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-AUDIO_CHAN_BW    ");
           if  (api->rsp->atv_status.audio_chan_bw    ==     3) safe_strcat(msg,"12X_OVERMOD   ");
      else if  (api->rsp->atv_status.audio_chan_bw    ==     8) safe_strcat(msg,"150_KHZ_OFFSET");
      else if  (api->rsp->atv_status.audio_chan_bw    ==     5) safe_strcat(msg,"15_KHZ_OFFSET ");
      else if  (api->rsp->atv_status.audio_chan_bw    ==     6) safe_strcat(msg,"30_KHZ_OFFSET ");
      else if  (api->rsp->atv_status.audio_chan_bw    ==     1) safe_strcat(msg,"4X_OVERMOD    ");
      else if  (api->rsp->atv_status.audio_chan_bw    ==     7) safe_strcat(msg,"75_KHZ_OFFSET ");
      else if  (api->rsp->atv_status.audio_chan_bw    ==     4) safe_strcat(msg,"7P5_KHZ_OFFSET");
      else if  (api->rsp->atv_status.audio_chan_bw    ==     2) safe_strcat(msg,"8X_OVERMOD    ");
      else if  (api->rsp->atv_status.audio_chan_bw    ==     9) safe_strcat(msg,"CUSTOM        ");
      else if  (api->rsp->atv_status.audio_chan_bw    ==     0) safe_strcat(msg,"RSVD          ");
      else                                                     safe_sprintf(msg,"%s%d", msg, api->rsp->atv_status.audio_chan_bw);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-SOUND_LEVEL      "); safe_sprintf(msg,"%s%d", msg, api->rsp->atv_status.sound_level);
     break;
    #endif /*     Si21XXC_ATV_STATUS_CMD */

    #ifdef        Si21XXC_CONFIG_CLOCKS_CMD
     case         Si21XXC_CONFIG_CLOCKS_CMD_CODE:
      safe_sprintf(msg,"CONFIG_CLOCKS ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT ");
           if  (api->rsp->config_clocks.STATUS->tunint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->config_clocks.STATUS->tunint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                      safe_sprintf(msg,"%s%d", msg, api->rsp->config_clocks.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT ");
           if  (api->rsp->config_clocks.STATUS->atvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->config_clocks.STATUS->atvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                      safe_sprintf(msg,"%s%d", msg, api->rsp->config_clocks.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT ");
           if  (api->rsp->config_clocks.STATUS->dtvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->config_clocks.STATUS->dtvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                      safe_sprintf(msg,"%s%d", msg, api->rsp->config_clocks.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR    ");
           if  (api->rsp->config_clocks.STATUS->err    ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->config_clocks.STATUS->err    ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                      safe_sprintf(msg,"%s%d", msg, api->rsp->config_clocks.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS    ");
           if  (api->rsp->config_clocks.STATUS->cts    ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->config_clocks.STATUS->cts    ==     0) safe_strcat(msg,"WAIT     ");
      else                                                      safe_sprintf(msg,"%s%d", msg, api->rsp->config_clocks.STATUS->cts);
     break;
    #endif /*     Si21XXC_CONFIG_CLOCKS_CMD */

    #ifdef        Si21XXC_CONFIG_I2C_CMD
     case         Si21XXC_CONFIG_I2C_CMD_CODE:
      safe_sprintf(msg,"CONFIG_I2C ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT ");
           if  (api->rsp->config_i2c.STATUS->tunint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->config_i2c.STATUS->tunint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->config_i2c.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT ");
           if  (api->rsp->config_i2c.STATUS->atvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->config_i2c.STATUS->atvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->config_i2c.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT ");
           if  (api->rsp->config_i2c.STATUS->dtvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->config_i2c.STATUS->dtvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->config_i2c.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR    ");
           if  (api->rsp->config_i2c.STATUS->err    ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->config_i2c.STATUS->err    ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->config_i2c.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS    ");
           if  (api->rsp->config_i2c.STATUS->cts    ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->config_i2c.STATUS->cts    ==     0) safe_strcat(msg,"WAIT     ");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->config_i2c.STATUS->cts);
     break;
    #endif /*     Si21XXC_CONFIG_I2C_CMD */

    #ifdef        Si2190B_CONFIG_PINS_CMD
     case         Si2190B_CONFIG_PINS_CMD_CODE:
      safe_sprintf(msg,"CONFIG_PINS ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT      ");
           if  (api->rsp->config_pins.STATUS->tunint      ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->config_pins.STATUS->tunint      ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                         safe_sprintf(msg,"%s%d", msg, api->rsp->config_pins.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT      ");
           if  (api->rsp->config_pins.STATUS->atvint      ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->config_pins.STATUS->atvint      ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                         safe_sprintf(msg,"%s%d", msg, api->rsp->config_pins.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT      ");
           if  (api->rsp->config_pins.STATUS->dtvint      ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->config_pins.STATUS->dtvint      ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                         safe_sprintf(msg,"%s%d", msg, api->rsp->config_pins.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR         ");
           if  (api->rsp->config_pins.STATUS->err         ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->config_pins.STATUS->err         ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                         safe_sprintf(msg,"%s%d", msg, api->rsp->config_pins.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS         ");
           if  (api->rsp->config_pins.STATUS->cts         ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->config_pins.STATUS->cts         ==     0) safe_strcat(msg,"WAIT     ");
      else                                                         safe_sprintf(msg,"%s%d", msg, api->rsp->config_pins.STATUS->cts);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-GPIO1_MODE  ");
           if  (api->rsp->config_pins.gpio1_mode  ==     1) safe_strcat(msg,"DISABLE");
      else if  (api->rsp->config_pins.gpio1_mode  ==     2) safe_strcat(msg,"DRIVE_0");
      else if  (api->rsp->config_pins.gpio1_mode  ==     3) safe_strcat(msg,"DRIVE_1");
      else                                                 safe_sprintf(msg,"%s%d", msg, api->rsp->config_pins.gpio1_mode);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-GPIO1_STATE ");
           if  (api->rsp->config_pins.gpio1_state ==     0) safe_strcat(msg,"READ_0");
      else if  (api->rsp->config_pins.gpio1_state ==     1) safe_strcat(msg,"READ_1");
      else                                                 safe_sprintf(msg,"%s%d", msg, api->rsp->config_pins.gpio1_state);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-GPIO2_MODE  ");
           if  (api->rsp->config_pins.gpio2_mode  ==     1) safe_strcat(msg,"DISABLE");
      else if  (api->rsp->config_pins.gpio2_mode  ==     2) safe_strcat(msg,"DRIVE_0");
      else if  (api->rsp->config_pins.gpio2_mode  ==     3) safe_strcat(msg,"DRIVE_1");
      else                                                 safe_sprintf(msg,"%s%d", msg, api->rsp->config_pins.gpio2_mode);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-GPIO2_STATE ");
           if  (api->rsp->config_pins.gpio2_state ==     0) safe_strcat(msg,"READ_0");
      else if  (api->rsp->config_pins.gpio2_state ==     1) safe_strcat(msg,"READ_1");
      else                                                 safe_sprintf(msg,"%s%d", msg, api->rsp->config_pins.gpio2_state);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-AGC1_MODE   ");
           if  (api->rsp->config_pins.agc1_mode   ==     1) safe_strcat(msg,"DISABLE");
      else if  (api->rsp->config_pins.agc1_mode   ==     2) safe_strcat(msg,"DRIVE_0");
      else if  (api->rsp->config_pins.agc1_mode   ==     3) safe_strcat(msg,"DRIVE_1");
      else                                                 safe_sprintf(msg,"%s%d", msg, api->rsp->config_pins.agc1_mode);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-AGC1_STATE  ");
           if  (api->rsp->config_pins.agc1_state  ==     0) safe_strcat(msg,"READ_0");
      else if  (api->rsp->config_pins.agc1_state  ==     1) safe_strcat(msg,"READ_1");
      else                                                 safe_sprintf(msg,"%s%d", msg, api->rsp->config_pins.agc1_state);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-AGC2_MODE   ");
           if  (api->rsp->config_pins.agc2_mode   ==     1) safe_strcat(msg,"DISABLE");
      else if  (api->rsp->config_pins.agc2_mode   ==     2) safe_strcat(msg,"DRIVE_0");
      else if  (api->rsp->config_pins.agc2_mode   ==     3) safe_strcat(msg,"DRIVE_1");
      else                                                 safe_sprintf(msg,"%s%d", msg, api->rsp->config_pins.agc2_mode);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-AGC2_STATE  ");
           if  (api->rsp->config_pins.agc2_state  ==     0) safe_strcat(msg,"READ_0");
      else if  (api->rsp->config_pins.agc2_state  ==     1) safe_strcat(msg,"READ_1");
      else                                                 safe_sprintf(msg,"%s%d", msg, api->rsp->config_pins.agc2_state);
     break;
    #endif /*     Si2190B_CONFIG_PINS_CMD */

    #ifdef        Si21XXC_DTV_RESTART_CMD
     case         Si21XXC_DTV_RESTART_CMD_CODE:
      safe_sprintf(msg,"DTV_RESTART ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT ");
           if  (api->rsp->dtv_restart.STATUS->tunint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->dtv_restart.STATUS->tunint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                    safe_sprintf(msg,"%s%d", msg, api->rsp->dtv_restart.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT ");
           if  (api->rsp->dtv_restart.STATUS->atvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->dtv_restart.STATUS->atvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                    safe_sprintf(msg,"%s%d", msg, api->rsp->dtv_restart.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT ");
           if  (api->rsp->dtv_restart.STATUS->dtvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->dtv_restart.STATUS->dtvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                    safe_sprintf(msg,"%s%d", msg, api->rsp->dtv_restart.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR    ");
           if  (api->rsp->dtv_restart.STATUS->err    ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->dtv_restart.STATUS->err    ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                    safe_sprintf(msg,"%s%d", msg, api->rsp->dtv_restart.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS    ");
           if  (api->rsp->dtv_restart.STATUS->cts    ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->dtv_restart.STATUS->cts    ==     0) safe_strcat(msg,"WAIT     ");
      else                                                    safe_sprintf(msg,"%s%d", msg, api->rsp->dtv_restart.STATUS->cts);
     break;
    #endif /*     Si21XXC_DTV_RESTART_CMD */

    #ifdef        Si21XXC_DTV_STATUS_CMD
     case         Si21XXC_DTV_STATUS_CMD_CODE:
      safe_sprintf(msg,"DTV_STATUS ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT     ");
           if  (api->rsp->dtv_status.STATUS->tunint     ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->dtv_status.STATUS->tunint     ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                       safe_sprintf(msg,"%s%d", msg, api->rsp->dtv_status.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT     ");
           if  (api->rsp->dtv_status.STATUS->atvint     ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->dtv_status.STATUS->atvint     ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                       safe_sprintf(msg,"%s%d", msg, api->rsp->dtv_status.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT     ");
           if  (api->rsp->dtv_status.STATUS->dtvint     ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->dtv_status.STATUS->dtvint     ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                       safe_sprintf(msg,"%s%d", msg, api->rsp->dtv_status.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR        ");
           if  (api->rsp->dtv_status.STATUS->err        ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->dtv_status.STATUS->err        ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                       safe_sprintf(msg,"%s%d", msg, api->rsp->dtv_status.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS        ");
           if  (api->rsp->dtv_status.STATUS->cts        ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->dtv_status.STATUS->cts        ==     0) safe_strcat(msg,"WAIT     ");
      else                                                       safe_sprintf(msg,"%s%d", msg, api->rsp->dtv_status.STATUS->cts);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CHLINT     ");
           if  (api->rsp->dtv_status.chlint     ==     1) safe_strcat(msg,"CHANGED  ");
      else if  (api->rsp->dtv_status.chlint     ==     0) safe_strcat(msg,"NO_CHANGE");
      else                                               safe_sprintf(msg,"%s%d", msg, api->rsp->dtv_status.chlint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CHL        ");
           if  (api->rsp->dtv_status.chl        ==     1) safe_strcat(msg,"CHANNEL   ");
      else if  (api->rsp->dtv_status.chl        ==     0) safe_strcat(msg,"NO_CHANNEL");
      else                                               safe_sprintf(msg,"%s%d", msg, api->rsp->dtv_status.chl);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-BW         ");
           if  (api->rsp->dtv_status.bw         ==     9) safe_strcat(msg,"BW_1P7MHZ");
      else if  (api->rsp->dtv_status.bw         ==     6) safe_strcat(msg,"BW_6MHZ  ");
      else if  (api->rsp->dtv_status.bw         ==    10) safe_strcat(msg,"BW_6P1MHZ");
      else if  (api->rsp->dtv_status.bw         ==     7) safe_strcat(msg,"BW_7MHZ  ");
      else if  (api->rsp->dtv_status.bw         ==     8) safe_strcat(msg,"BW_8MHZ  ");
      else                                               safe_sprintf(msg,"%s%d", msg, api->rsp->dtv_status.bw);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-MODULATION ");
           if  (api->rsp->dtv_status.modulation ==     0) safe_strcat(msg,"ATSC     ");
      else if  (api->rsp->dtv_status.modulation ==    15) safe_strcat(msg,"CW       ");
      else if  (api->rsp->dtv_status.modulation ==    14) safe_strcat(msg,"CW_LEGACY");
      else if  (api->rsp->dtv_status.modulation ==     6) safe_strcat(msg,"DTMB     ");
      else if  (api->rsp->dtv_status.modulation ==     3) safe_strcat(msg,"DVBC     ");
      else if  (api->rsp->dtv_status.modulation ==     2) safe_strcat(msg,"DVBT     ");
      else if  (api->rsp->dtv_status.modulation ==     5) safe_strcat(msg,"ISDBC    ");
      else if  (api->rsp->dtv_status.modulation ==     4) safe_strcat(msg,"ISDBT    ");
      else if  (api->rsp->dtv_status.modulation ==     1) safe_strcat(msg,"QAM_US   ");
      else                                               safe_sprintf(msg,"%s%d", msg, api->rsp->dtv_status.modulation);
     break;
    #endif /*     Si21XXC_DTV_STATUS_CMD */

    #ifdef        Si21XXC_EXIT_BOOTLOADER_CMD
     case         Si21XXC_EXIT_BOOTLOADER_CMD_CODE:
      safe_sprintf(msg,"EXIT_BOOTLOADER ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT ");
           if  (api->rsp->exit_bootloader.STATUS->tunint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->exit_bootloader.STATUS->tunint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                        safe_sprintf(msg,"%s%d", msg, api->rsp->exit_bootloader.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT ");
           if  (api->rsp->exit_bootloader.STATUS->atvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->exit_bootloader.STATUS->atvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                        safe_sprintf(msg,"%s%d", msg, api->rsp->exit_bootloader.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT ");
           if  (api->rsp->exit_bootloader.STATUS->dtvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->exit_bootloader.STATUS->dtvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                        safe_sprintf(msg,"%s%d", msg, api->rsp->exit_bootloader.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR    ");
           if  (api->rsp->exit_bootloader.STATUS->err    ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->exit_bootloader.STATUS->err    ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                        safe_sprintf(msg,"%s%d", msg, api->rsp->exit_bootloader.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS    ");
           if  (api->rsp->exit_bootloader.STATUS->cts    ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->exit_bootloader.STATUS->cts    ==     0) safe_strcat(msg,"WAIT     ");
      else                                                        safe_sprintf(msg,"%s%d", msg, api->rsp->exit_bootloader.STATUS->cts);
     break;
    #endif /*     Si21XXC_EXIT_BOOTLOADER_CMD */

    #ifdef        Si21XXC_FINE_TUNE_CMD
     case         Si21XXC_FINE_TUNE_CMD_CODE:
      safe_sprintf(msg,"FINE_TUNE ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT ");
           if  (api->rsp->fine_tune.STATUS->tunint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->fine_tune.STATUS->tunint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                  safe_sprintf(msg,"%s%d", msg, api->rsp->fine_tune.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT ");
           if  (api->rsp->fine_tune.STATUS->atvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->fine_tune.STATUS->atvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                  safe_sprintf(msg,"%s%d", msg, api->rsp->fine_tune.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT ");
           if  (api->rsp->fine_tune.STATUS->dtvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->fine_tune.STATUS->dtvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                  safe_sprintf(msg,"%s%d", msg, api->rsp->fine_tune.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR    ");
           if  (api->rsp->fine_tune.STATUS->err    ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->fine_tune.STATUS->err    ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                  safe_sprintf(msg,"%s%d", msg, api->rsp->fine_tune.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS    ");
           if  (api->rsp->fine_tune.STATUS->cts    ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->fine_tune.STATUS->cts    ==     0) safe_strcat(msg,"WAIT     ");
      else                                                  safe_sprintf(msg,"%s%d", msg, api->rsp->fine_tune.STATUS->cts);
     break;
    #endif /*     Si21XXC_FINE_TUNE_CMD */

    #ifdef        Si21XXC_GET_PROPERTY_CMD
     case         Si21XXC_GET_PROPERTY_CMD_CODE:
      safe_sprintf(msg,"GET_PROPERTY ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT   ");
           if  (api->rsp->get_property.STATUS->tunint   ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->get_property.STATUS->tunint   ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                       safe_sprintf(msg,"%s%d", msg, api->rsp->get_property.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT   ");
           if  (api->rsp->get_property.STATUS->atvint   ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->get_property.STATUS->atvint   ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                       safe_sprintf(msg,"%s%d", msg, api->rsp->get_property.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT   ");
           if  (api->rsp->get_property.STATUS->dtvint   ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->get_property.STATUS->dtvint   ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                       safe_sprintf(msg,"%s%d", msg, api->rsp->get_property.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR      ");
           if  (api->rsp->get_property.STATUS->err      ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->get_property.STATUS->err      ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                       safe_sprintf(msg,"%s%d", msg, api->rsp->get_property.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS      ");
           if  (api->rsp->get_property.STATUS->cts      ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->get_property.STATUS->cts      ==     0) safe_strcat(msg,"WAIT     ");
      else                                                       safe_sprintf(msg,"%s%d", msg, api->rsp->get_property.STATUS->cts);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-RESERVED "); safe_sprintf(msg,"%s%d", msg, api->rsp->get_property.reserved);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DATA     "); safe_sprintf(msg,"%s%d", msg, api->rsp->get_property.data);
     break;
    #endif /*     Si21XXC_GET_PROPERTY_CMD */

    #ifdef        Si21XXC_GET_REV_CMD
     case         Si21XXC_GET_REV_CMD_CODE:
      safe_sprintf(msg,"GET_REV ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT   ");
           if  (api->rsp->get_rev.STATUS->tunint   ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->get_rev.STATUS->tunint   ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                  safe_sprintf(msg,"%s%d", msg, api->rsp->get_rev.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT   ");
           if  (api->rsp->get_rev.STATUS->atvint   ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->get_rev.STATUS->atvint   ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                  safe_sprintf(msg,"%s%d", msg, api->rsp->get_rev.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT   ");
           if  (api->rsp->get_rev.STATUS->dtvint   ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->get_rev.STATUS->dtvint   ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                  safe_sprintf(msg,"%s%d", msg, api->rsp->get_rev.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR      ");
           if  (api->rsp->get_rev.STATUS->err      ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->get_rev.STATUS->err      ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                  safe_sprintf(msg,"%s%d", msg, api->rsp->get_rev.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS      ");
           if  (api->rsp->get_rev.STATUS->cts      ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->get_rev.STATUS->cts      ==     0) safe_strcat(msg,"WAIT     ");
      else                                                  safe_sprintf(msg,"%s%d", msg, api->rsp->get_rev.STATUS->cts);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-PN       "); safe_sprintf(msg,"%s%d", msg, api->rsp->get_rev.pn);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-FWMAJOR  "); safe_sprintf(msg,"%s%d", msg, api->rsp->get_rev.fwmajor);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-FWMINOR  "); safe_sprintf(msg,"%s%d", msg, api->rsp->get_rev.fwminor);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-PATCH    "); safe_sprintf(msg,"%s%d", msg, api->rsp->get_rev.patch);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CMPMAJOR "); safe_sprintf(msg,"%s%d", msg, api->rsp->get_rev.cmpmajor);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CMPMINOR "); safe_sprintf(msg,"%s%d", msg, api->rsp->get_rev.cmpminor);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CMPBUILD "); safe_sprintf(msg,"%s%d", msg, api->rsp->get_rev.cmpbuild);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CHIPREV  ");
           if  (api->rsp->get_rev.chiprev  ==     1) safe_strcat(msg,"A");
      else if  (api->rsp->get_rev.chiprev  ==     2) safe_strcat(msg,"B");
      else                                          safe_sprintf(msg,"%s%d", msg, api->rsp->get_rev.chiprev);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-PN2      "); safe_sprintf(msg,"%s%d", msg, api->rsp->get_rev.pn2);
     break;
    #endif /*     Si21XXC_GET_REV_CMD */

    #ifdef        Si21XXC_PART_INFO_CMD
     case         Si21XXC_PART_INFO_CMD_CODE:
      safe_sprintf(msg,"PART_INFO ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT   ");
           if  (api->rsp->part_info.STATUS->tunint   ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->part_info.STATUS->tunint   ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                    safe_sprintf(msg,"%s%d", msg, api->rsp->part_info.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT   ");
           if  (api->rsp->part_info.STATUS->atvint   ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->part_info.STATUS->atvint   ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                    safe_sprintf(msg,"%s%d", msg, api->rsp->part_info.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT   ");
           if  (api->rsp->part_info.STATUS->dtvint   ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->part_info.STATUS->dtvint   ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                    safe_sprintf(msg,"%s%d", msg, api->rsp->part_info.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR      ");
           if  (api->rsp->part_info.STATUS->err      ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->part_info.STATUS->err      ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                    safe_sprintf(msg,"%s%d", msg, api->rsp->part_info.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS      ");
           if  (api->rsp->part_info.STATUS->cts      ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->part_info.STATUS->cts      ==     0) safe_strcat(msg,"WAIT     ");
      else                                                    safe_sprintf(msg,"%s%d", msg, api->rsp->part_info.STATUS->cts);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CHIPREV  ");
           if  (api->rsp->part_info.chiprev  ==     1) safe_strcat(msg,"A");
      else if  (api->rsp->part_info.chiprev  ==     2) safe_strcat(msg,"B");
      else                                            safe_sprintf(msg,"%s%d", msg, api->rsp->part_info.chiprev);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-PART     "); safe_sprintf(msg,"%s%d", msg, api->rsp->part_info.part);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-PMAJOR   "); safe_sprintf(msg,"%s%d", msg, api->rsp->part_info.pmajor);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-PMINOR   "); safe_sprintf(msg,"%s%d", msg, api->rsp->part_info.pminor);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-PBUILD   "); safe_sprintf(msg,"%s%d", msg, api->rsp->part_info.pbuild);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-RESERVED "); safe_sprintf(msg,"%s%d", msg, api->rsp->part_info.reserved);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-SERIAL   "); safe_sprintf(msg,"%s%ld", msg, api->rsp->part_info.serial);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ROMID    "); safe_sprintf(msg,"%s%d", msg, api->rsp->part_info.romid);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-PART2    "); safe_sprintf(msg,"%s%d", msg, api->rsp->part_info.part2);
     break;
    #endif /*     Si21XXC_PART_INFO_CMD */

    #ifdef        Si2190B_PART_INFO2_CMD
     case         Si2190B_PART_INFO2_CMD_CODE:
      safe_sprintf(msg,"PART_INFO2 ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT   ");
           if  (api->rsp->part_info2.STATUS->tunint   ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->part_info2.STATUS->tunint   ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                     safe_sprintf(msg,"%s%d", msg, api->rsp->part_info2.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT   ");
           if  (api->rsp->part_info2.STATUS->atvint   ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->part_info2.STATUS->atvint   ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                     safe_sprintf(msg,"%s%d", msg, api->rsp->part_info2.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT   ");
           if  (api->rsp->part_info2.STATUS->dtvint   ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->part_info2.STATUS->dtvint   ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                     safe_sprintf(msg,"%s%d", msg, api->rsp->part_info2.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR      ");
           if  (api->rsp->part_info2.STATUS->err      ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->part_info2.STATUS->err      ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                     safe_sprintf(msg,"%s%d", msg, api->rsp->part_info2.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS      ");
           if  (api->rsp->part_info2.STATUS->cts      ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->part_info2.STATUS->cts      ==     0) safe_strcat(msg,"WAIT     ");
      else                                                     safe_sprintf(msg,"%s%d", msg, api->rsp->part_info2.STATUS->cts);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ROMID    "); safe_sprintf(msg,"%s%d", msg, api->rsp->part_info2.romid);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-PART2    "); safe_sprintf(msg,"%s%d", msg, api->rsp->part_info2.part2);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-RESERVED "); safe_sprintf(msg,"%s%d", msg, api->rsp->part_info2.reserved);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-SERIAL   "); safe_sprintf(msg,"%s%ld", msg, api->rsp->part_info2.serial);
     break;
    #endif /*     Si2190B_PART_INFO2_CMD */

    #ifdef        Si21XXC_POWER_DOWN_HW_CMD
     case         Si21XXC_POWER_DOWN_HW_CMD_CODE:
      safe_sprintf(msg,"POWER_DOWN_HW ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT ");
           if  (api->rsp->power_down_hw.STATUS->tunint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->power_down_hw.STATUS->tunint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                      safe_sprintf(msg,"%s%d", msg, api->rsp->power_down_hw.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT ");
           if  (api->rsp->power_down_hw.STATUS->atvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->power_down_hw.STATUS->atvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                      safe_sprintf(msg,"%s%d", msg, api->rsp->power_down_hw.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT ");
           if  (api->rsp->power_down_hw.STATUS->dtvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->power_down_hw.STATUS->dtvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                      safe_sprintf(msg,"%s%d", msg, api->rsp->power_down_hw.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR    ");
           if  (api->rsp->power_down_hw.STATUS->err    ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->power_down_hw.STATUS->err    ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                      safe_sprintf(msg,"%s%d", msg, api->rsp->power_down_hw.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS    ");
           if  (api->rsp->power_down_hw.STATUS->cts    ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->power_down_hw.STATUS->cts    ==     0) safe_strcat(msg,"WAIT     ");
      else                                                      safe_sprintf(msg,"%s%d", msg, api->rsp->power_down_hw.STATUS->cts);
     break;
    #endif /*     Si21XXC_POWER_DOWN_HW_CMD */

    #ifdef        Si21XXC_POWER_UP_CMD
     case         Si21XXC_POWER_UP_CMD_CODE:
      safe_sprintf(msg,"POWER_UP ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT ");
           if  (api->rsp->power_up.STATUS->tunint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->power_up.STATUS->tunint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                 safe_sprintf(msg,"%s%d", msg, api->rsp->power_up.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT ");
           if  (api->rsp->power_up.STATUS->atvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->power_up.STATUS->atvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                 safe_sprintf(msg,"%s%d", msg, api->rsp->power_up.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT ");
           if  (api->rsp->power_up.STATUS->dtvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->power_up.STATUS->dtvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                 safe_sprintf(msg,"%s%d", msg, api->rsp->power_up.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR    ");
           if  (api->rsp->power_up.STATUS->err    ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->power_up.STATUS->err    ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                 safe_sprintf(msg,"%s%d", msg, api->rsp->power_up.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS    ");
           if  (api->rsp->power_up.STATUS->cts    ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->power_up.STATUS->cts    ==     0) safe_strcat(msg,"WAIT     ");
      else                                                 safe_sprintf(msg,"%s%d", msg, api->rsp->power_up.STATUS->cts);
     break;
    #endif /*     Si21XXC_POWER_UP_CMD */

    #ifdef        Si2190B_REREAD_REPLY_CMD
     case         Si2190B_REREAD_REPLY_CMD_CODE:
      safe_sprintf(msg,"REREAD_REPLY ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT  ");
           if  (api->rsp->reread_reply.STATUS->tunint  ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->reread_reply.STATUS->tunint  ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                      safe_sprintf(msg,"%s%d", msg, api->rsp->reread_reply.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT  ");
           if  (api->rsp->reread_reply.STATUS->atvint  ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->reread_reply.STATUS->atvint  ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                      safe_sprintf(msg,"%s%d", msg, api->rsp->reread_reply.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT  ");
           if  (api->rsp->reread_reply.STATUS->dtvint  ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->reread_reply.STATUS->dtvint  ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                      safe_sprintf(msg,"%s%d", msg, api->rsp->reread_reply.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR     ");
           if  (api->rsp->reread_reply.STATUS->err     ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->reread_reply.STATUS->err     ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                      safe_sprintf(msg,"%s%d", msg, api->rsp->reread_reply.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS     ");
           if  (api->rsp->reread_reply.STATUS->cts     ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->reread_reply.STATUS->cts     ==     0) safe_strcat(msg,"WAIT     ");
      else                                                      safe_sprintf(msg,"%s%d", msg, api->rsp->reread_reply.STATUS->cts);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-REPLY1  "); safe_sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply1);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-REPLY2  "); safe_sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply2);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-REPLY3  "); safe_sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply3);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-REPLY4  "); safe_sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply4);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-REPLY5  "); safe_sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply5);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-REPLY6  "); safe_sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply6);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-REPLY7  "); safe_sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply7);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-REPLY8  "); safe_sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply8);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-REPLY9  "); safe_sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply9);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-REPLY10 "); safe_sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply10);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-REPLY11 "); safe_sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply11);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-REPLY12 "); safe_sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply12);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-REPLY13 "); safe_sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply13);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-REPLY14 "); safe_sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply14);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-REPLY15 "); safe_sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply15);
     break;
    #endif /*     Si2190B_REREAD_REPLY_CMD */

    #ifdef        Si2190B_RESET_HW_CMD
     case         Si2190B_RESET_HW_CMD_CODE:
      safe_sprintf(msg,"RESET_HW ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT ");
           if  (api->rsp->reset_hw.STATUS->tunint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->reset_hw.STATUS->tunint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                 safe_sprintf(msg,"%s%d", msg, api->rsp->reset_hw.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT ");
           if  (api->rsp->reset_hw.STATUS->atvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->reset_hw.STATUS->atvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                 safe_sprintf(msg,"%s%d", msg, api->rsp->reset_hw.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT ");
           if  (api->rsp->reset_hw.STATUS->dtvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->reset_hw.STATUS->dtvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                 safe_sprintf(msg,"%s%d", msg, api->rsp->reset_hw.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR    ");
           if  (api->rsp->reset_hw.STATUS->err    ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->reset_hw.STATUS->err    ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                 safe_sprintf(msg,"%s%d", msg, api->rsp->reset_hw.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS    ");
           if  (api->rsp->reset_hw.STATUS->cts    ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->reset_hw.STATUS->cts    ==     0) safe_strcat(msg,"WAIT     ");
      else                                                 safe_sprintf(msg,"%s%d", msg, api->rsp->reset_hw.STATUS->cts);
     break;
    #endif /*     Si2190B_RESET_HW_CMD */

    #ifdef        Si2190B_SELF_TEST_CMD
     case         Si2190B_SELF_TEST_CMD_CODE:
      safe_sprintf(msg,"SELF_TEST ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT          ");
           if  (api->rsp->self_test.STATUS->tunint          ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->self_test.STATUS->tunint          ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                           safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT          ");
           if  (api->rsp->self_test.STATUS->atvint          ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->self_test.STATUS->atvint          ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                           safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT          ");
           if  (api->rsp->self_test.STATUS->dtvint          ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->self_test.STATUS->dtvint          ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                           safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR             ");
           if  (api->rsp->self_test.STATUS->err             ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->self_test.STATUS->err             ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                           safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS             ");
           if  (api->rsp->self_test.STATUS->cts             ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->self_test.STATUS->cts             ==     0) safe_strcat(msg,"WAIT     ");
      else                                                           safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.STATUS->cts);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ADC_REF         ");
           if  (api->rsp->self_test.adc_ref         ==     0) safe_strcat(msg,"FAIL");
      else if  (api->rsp->self_test.adc_ref         ==     1) safe_strcat(msg,"PASS");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.adc_ref);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-MIX_CMB0        ");
           if  (api->rsp->self_test.mix_cmb0        ==     0) safe_strcat(msg,"FAIL");
      else if  (api->rsp->self_test.mix_cmb0        ==     1) safe_strcat(msg,"PASS");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.mix_cmb0);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-MIX_CMB1        ");
           if  (api->rsp->self_test.mix_cmb1        ==     0) safe_strcat(msg,"FAIL");
      else if  (api->rsp->self_test.mix_cmb1        ==     1) safe_strcat(msg,"PASS");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.mix_cmb1);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-MIX_CMB2        ");
           if  (api->rsp->self_test.mix_cmb2        ==     0) safe_strcat(msg,"FAIL");
      else if  (api->rsp->self_test.mix_cmb2        ==     1) safe_strcat(msg,"PASS");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.mix_cmb2);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DIVR_VREG       ");
           if  (api->rsp->self_test.divr_vreg       ==     0) safe_strcat(msg,"FAIL");
      else if  (api->rsp->self_test.divr_vreg       ==     1) safe_strcat(msg,"PASS");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.divr_vreg);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-PDCPLF_VREG     ");
           if  (api->rsp->self_test.pdcplf_vreg     ==     0) safe_strcat(msg,"FAIL");
      else if  (api->rsp->self_test.pdcplf_vreg     ==     1) safe_strcat(msg,"PASS");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.pdcplf_vreg);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-PDCPLF_BIAS     ");
           if  (api->rsp->self_test.pdcplf_bias     ==     0) safe_strcat(msg,"FAIL");
      else if  (api->rsp->self_test.pdcplf_bias     ==     1) safe_strcat(msg,"PASS");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.pdcplf_bias);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-VCO_VREG1       ");
           if  (api->rsp->self_test.vco_vreg1       ==     0) safe_strcat(msg,"FAIL");
      else if  (api->rsp->self_test.vco_vreg1       ==     1) safe_strcat(msg,"PASS");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.vco_vreg1);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-VCO_VREG2       ");
           if  (api->rsp->self_test.vco_vreg2       ==     0) safe_strcat(msg,"FAIL");
      else if  (api->rsp->self_test.vco_vreg2       ==     1) safe_strcat(msg,"PASS");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.vco_vreg2);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-FBDIV_IREG      ");
           if  (api->rsp->self_test.fbdiv_ireg      ==     0) safe_strcat(msg,"FAIL");
      else if  (api->rsp->self_test.fbdiv_ireg      ==     1) safe_strcat(msg,"PASS");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.fbdiv_ireg);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-FBDIV_VREG      ");
           if  (api->rsp->self_test.fbdiv_vreg      ==     0) safe_strcat(msg,"FAIL");
      else if  (api->rsp->self_test.fbdiv_vreg      ==     1) safe_strcat(msg,"PASS");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.fbdiv_vreg);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-PDCPLF_RCCAL    ");
           if  (api->rsp->self_test.pdcplf_rccal    ==     0) safe_strcat(msg,"FAIL");
      else if  (api->rsp->self_test.pdcplf_rccal    ==     1) safe_strcat(msg,"PASS");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.pdcplf_rccal);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DAC1_VTR        ");
           if  (api->rsp->self_test.dac1_vtr        ==     0) safe_strcat(msg,"FAIL");
      else if  (api->rsp->self_test.dac1_vtr        ==     1) safe_strcat(msg,"PASS");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.dac1_vtr);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DAC1_VCOM       ");
           if  (api->rsp->self_test.dac1_vcom       ==     0) safe_strcat(msg,"FAIL");
      else if  (api->rsp->self_test.dac1_vcom       ==     1) safe_strcat(msg,"PASS");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.dac1_vcom);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DAC2_VTR        ");
           if  (api->rsp->self_test.dac2_vtr        ==     0) safe_strcat(msg,"FAIL");
      else if  (api->rsp->self_test.dac2_vtr        ==     1) safe_strcat(msg,"PASS");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.dac2_vtr);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DAC2_VCOM       ");
           if  (api->rsp->self_test.dac2_vcom       ==     0) safe_strcat(msg,"FAIL");
      else if  (api->rsp->self_test.dac2_vcom       ==     1) safe_strcat(msg,"PASS");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.dac2_vcom);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-IF_BIAS         ");
           if  (api->rsp->self_test.if_bias         ==     0) safe_strcat(msg,"FAIL");
      else if  (api->rsp->self_test.if_bias         ==     1) safe_strcat(msg,"PASS");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.if_bias);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-LNA_VMID        ");
           if  (api->rsp->self_test.lna_vmid        ==     0) safe_strcat(msg,"FAIL");
      else if  (api->rsp->self_test.lna_vmid        ==     1) safe_strcat(msg,"PASS");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.lna_vmid);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-LNA_VREG        ");
           if  (api->rsp->self_test.lna_vreg        ==     0) safe_strcat(msg,"FAIL");
      else if  (api->rsp->self_test.lna_vreg        ==     1) safe_strcat(msg,"PASS");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.lna_vreg);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-LNA_VTR         ");
           if  (api->rsp->self_test.lna_vtr         ==     0) safe_strcat(msg,"FAIL");
      else if  (api->rsp->self_test.lna_vtr         ==     1) safe_strcat(msg,"PASS");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.lna_vtr);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-LODIV_CORE_VREG ");
           if  (api->rsp->self_test.lodiv_core_vreg ==     0) safe_strcat(msg,"FAIL");
      else if  (api->rsp->self_test.lodiv_core_vreg ==     1) safe_strcat(msg,"PASS");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.lodiv_core_vreg);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-LODIV_BUF_REG   ");
           if  (api->rsp->self_test.lodiv_buf_reg   ==     0) safe_strcat(msg,"FAIL");
      else if  (api->rsp->self_test.lodiv_buf_reg   ==     1) safe_strcat(msg,"PASS");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.lodiv_buf_reg);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-RCCAL_FILT      ");
           if  (api->rsp->self_test.rccal_filt      ==     0) safe_strcat(msg,"FAIL");
      else if  (api->rsp->self_test.rccal_filt      ==     1) safe_strcat(msg,"PASS");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.rccal_filt);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-RCCAL_ADC       ");
           if  (api->rsp->self_test.rccal_adc       ==     0) safe_strcat(msg,"FAIL");
      else if  (api->rsp->self_test.rccal_adc       ==     1) safe_strcat(msg,"PASS");
      else                                                   safe_sprintf(msg,"%s%d", msg, api->rsp->self_test.rccal_adc);
     break;
    #endif /*     Si2190B_SELF_TEST_CMD */

    #ifdef        Si21XXC_SET_PROPERTY_CMD
     case         Si21XXC_SET_PROPERTY_CMD_CODE:
      safe_sprintf(msg,"SET_PROPERTY ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT   ");
           if  (api->rsp->set_property.STATUS->tunint   ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->set_property.STATUS->tunint   ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                       safe_sprintf(msg,"%s%d", msg, api->rsp->set_property.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT   ");
           if  (api->rsp->set_property.STATUS->atvint   ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->set_property.STATUS->atvint   ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                       safe_sprintf(msg,"%s%d", msg, api->rsp->set_property.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT   ");
           if  (api->rsp->set_property.STATUS->dtvint   ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->set_property.STATUS->dtvint   ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                       safe_sprintf(msg,"%s%d", msg, api->rsp->set_property.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR      ");
           if  (api->rsp->set_property.STATUS->err      ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->set_property.STATUS->err      ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                       safe_sprintf(msg,"%s%d", msg, api->rsp->set_property.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS      ");
           if  (api->rsp->set_property.STATUS->cts      ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->set_property.STATUS->cts      ==     0) safe_strcat(msg,"WAIT     ");
      else                                                       safe_sprintf(msg,"%s%d", msg, api->rsp->set_property.STATUS->cts);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-RESERVED "); safe_sprintf(msg,"%s%d", msg, api->rsp->set_property.reserved);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DATA     "); safe_sprintf(msg,"%s%d", msg, api->rsp->set_property.data);
     break;
    #endif /*     Si21XXC_SET_PROPERTY_CMD */

    #ifdef        Si2190B_SSVD_DEBUG_CONFIG_CMD
     case         Si2190B_SSVD_DEBUG_CONFIG_CMD_CODE:
      safe_sprintf(msg,"SSVD_DEBUG_CONFIG ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT ");
           if  (api->rsp->ssvd_debug_config.STATUS->tunint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->ssvd_debug_config.STATUS->tunint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                          safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_debug_config.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT ");
           if  (api->rsp->ssvd_debug_config.STATUS->atvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->ssvd_debug_config.STATUS->atvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                          safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_debug_config.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT ");
           if  (api->rsp->ssvd_debug_config.STATUS->dtvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->ssvd_debug_config.STATUS->dtvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                          safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_debug_config.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR    ");
           if  (api->rsp->ssvd_debug_config.STATUS->err    ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->ssvd_debug_config.STATUS->err    ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                          safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_debug_config.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS    ");
           if  (api->rsp->ssvd_debug_config.STATUS->cts    ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->ssvd_debug_config.STATUS->cts    ==     0) safe_strcat(msg,"WAIT     ");
      else                                                          safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_debug_config.STATUS->cts);
     break;
    #endif /*     Si2190B_SSVD_DEBUG_CONFIG_CMD */

    #ifdef        Si2190B_SSVD_HDIV_CMD
     case         Si2190B_SSVD_HDIV_CMD_CODE:
      safe_sprintf(msg,"SSVD_HDIV ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT ");
           if  (api->rsp->ssvd_hdiv.STATUS->tunint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->ssvd_hdiv.STATUS->tunint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                  safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_hdiv.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT ");
           if  (api->rsp->ssvd_hdiv.STATUS->atvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->ssvd_hdiv.STATUS->atvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                  safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_hdiv.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT ");
           if  (api->rsp->ssvd_hdiv.STATUS->dtvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->ssvd_hdiv.STATUS->dtvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                  safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_hdiv.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR    ");
           if  (api->rsp->ssvd_hdiv.STATUS->err    ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->ssvd_hdiv.STATUS->err    ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                  safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_hdiv.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS    ");
           if  (api->rsp->ssvd_hdiv.STATUS->cts    ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->ssvd_hdiv.STATUS->cts    ==     0) safe_strcat(msg,"WAIT     ");
      else                                                  safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_hdiv.STATUS->cts);
     break;
    #endif /*     Si2190B_SSVD_HDIV_CMD */

    #ifdef        Si2190B_SSVD_MULTI_REG_RD_CMD
     case         Si2190B_SSVD_MULTI_REG_RD_CMD_CODE:
      safe_sprintf(msg,"SSVD_MULTI_REG_RD ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT   ");
           if  (api->rsp->ssvd_multi_reg_rd.STATUS->tunint   ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->ssvd_multi_reg_rd.STATUS->tunint   ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                            safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_multi_reg_rd.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT   ");
           if  (api->rsp->ssvd_multi_reg_rd.STATUS->atvint   ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->ssvd_multi_reg_rd.STATUS->atvint   ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                            safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_multi_reg_rd.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT   ");
           if  (api->rsp->ssvd_multi_reg_rd.STATUS->dtvint   ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->ssvd_multi_reg_rd.STATUS->dtvint   ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                            safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_multi_reg_rd.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR      ");
           if  (api->rsp->ssvd_multi_reg_rd.STATUS->err      ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->ssvd_multi_reg_rd.STATUS->err      ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                            safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_multi_reg_rd.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS      ");
           if  (api->rsp->ssvd_multi_reg_rd.STATUS->cts      ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->ssvd_multi_reg_rd.STATUS->cts      ==     0) safe_strcat(msg,"WAIT     ");
      else                                                            safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_multi_reg_rd.STATUS->cts);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-RESERVED "); safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_multi_reg_rd.reserved);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DATA0    "); safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_multi_reg_rd.data0);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DATA1    "); safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_multi_reg_rd.data1);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DATA2    "); safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_multi_reg_rd.data2);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DATA3    "); safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_multi_reg_rd.data3);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DATA4    "); safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_multi_reg_rd.data4);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DATA5    "); safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_multi_reg_rd.data5);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DATA6    "); safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_multi_reg_rd.data6);
     break;
    #endif /*     Si2190B_SSVD_MULTI_REG_RD_CMD */

    #ifdef        Si2190B_SSVD_MULTI_REG_WR_CMD
     case         Si2190B_SSVD_MULTI_REG_WR_CMD_CODE:
      safe_sprintf(msg,"SSVD_MULTI_REG_WR ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT ");
           if  (api->rsp->ssvd_multi_reg_wr.STATUS->tunint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->ssvd_multi_reg_wr.STATUS->tunint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                          safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_multi_reg_wr.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT ");
           if  (api->rsp->ssvd_multi_reg_wr.STATUS->atvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->ssvd_multi_reg_wr.STATUS->atvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                          safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_multi_reg_wr.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT ");
           if  (api->rsp->ssvd_multi_reg_wr.STATUS->dtvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->ssvd_multi_reg_wr.STATUS->dtvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                          safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_multi_reg_wr.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR    ");
           if  (api->rsp->ssvd_multi_reg_wr.STATUS->err    ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->ssvd_multi_reg_wr.STATUS->err    ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                          safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_multi_reg_wr.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS    ");
           if  (api->rsp->ssvd_multi_reg_wr.STATUS->cts    ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->ssvd_multi_reg_wr.STATUS->cts    ==     0) safe_strcat(msg,"WAIT     ");
      else                                                          safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_multi_reg_wr.STATUS->cts);
     break;
    #endif /*     Si2190B_SSVD_MULTI_REG_WR_CMD */

    #ifdef        Si2190B_SSVD_POWER_DOWN_CMD
     case         Si2190B_SSVD_POWER_DOWN_CMD_CODE:
      safe_sprintf(msg,"SSVD_POWER_DOWN ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT ");
           if  (api->rsp->ssvd_power_down.STATUS->tunint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->ssvd_power_down.STATUS->tunint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                        safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_power_down.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT ");
           if  (api->rsp->ssvd_power_down.STATUS->atvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->ssvd_power_down.STATUS->atvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                        safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_power_down.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT ");
           if  (api->rsp->ssvd_power_down.STATUS->dtvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->ssvd_power_down.STATUS->dtvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                        safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_power_down.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR    ");
           if  (api->rsp->ssvd_power_down.STATUS->err    ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->ssvd_power_down.STATUS->err    ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                        safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_power_down.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS    ");
           if  (api->rsp->ssvd_power_down.STATUS->cts    ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->ssvd_power_down.STATUS->cts    ==     0) safe_strcat(msg,"WAIT     ");
      else                                                        safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_power_down.STATUS->cts);
     break;
    #endif /*     Si2190B_SSVD_POWER_DOWN_CMD */

    #ifdef        Si2190B_SSVD_POWER_UP_CMD
     case         Si2190B_SSVD_POWER_UP_CMD_CODE:
      safe_sprintf(msg,"SSVD_POWER_UP ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT ");
           if  (api->rsp->ssvd_power_up.STATUS->tunint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->ssvd_power_up.STATUS->tunint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                      safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_power_up.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT ");
           if  (api->rsp->ssvd_power_up.STATUS->atvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->ssvd_power_up.STATUS->atvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                      safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_power_up.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT ");
           if  (api->rsp->ssvd_power_up.STATUS->dtvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->ssvd_power_up.STATUS->dtvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                      safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_power_up.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR    ");
           if  (api->rsp->ssvd_power_up.STATUS->err    ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->ssvd_power_up.STATUS->err    ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                      safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_power_up.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS    ");
           if  (api->rsp->ssvd_power_up.STATUS->cts    ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->ssvd_power_up.STATUS->cts    ==     0) safe_strcat(msg,"WAIT     ");
      else                                                      safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_power_up.STATUS->cts);
     break;
    #endif /*     Si2190B_SSVD_POWER_UP_CMD */

    #ifdef        Si2190B_SSVD_REG_RD_CMD
     case         Si2190B_SSVD_REG_RD_CMD_CODE:
      safe_sprintf(msg,"SSVD_REG_RD ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT   ");
           if  (api->rsp->ssvd_reg_rd.STATUS->tunint   ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->ssvd_reg_rd.STATUS->tunint   ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                      safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_reg_rd.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT   ");
           if  (api->rsp->ssvd_reg_rd.STATUS->atvint   ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->ssvd_reg_rd.STATUS->atvint   ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                      safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_reg_rd.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT   ");
           if  (api->rsp->ssvd_reg_rd.STATUS->dtvint   ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->ssvd_reg_rd.STATUS->dtvint   ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                      safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_reg_rd.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR      ");
           if  (api->rsp->ssvd_reg_rd.STATUS->err      ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->ssvd_reg_rd.STATUS->err      ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                      safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_reg_rd.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS      ");
           if  (api->rsp->ssvd_reg_rd.STATUS->cts      ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->ssvd_reg_rd.STATUS->cts      ==     0) safe_strcat(msg,"WAIT     ");
      else                                                      safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_reg_rd.STATUS->cts);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-RESERVED "); safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_reg_rd.reserved);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DATA     "); safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_reg_rd.data);
     break;
    #endif /*     Si2190B_SSVD_REG_RD_CMD */

    #ifdef        Si2190B_SSVD_REG_WR_CMD
     case         Si2190B_SSVD_REG_WR_CMD_CODE:
      safe_sprintf(msg,"SSVD_REG_WR ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT ");
           if  (api->rsp->ssvd_reg_wr.STATUS->tunint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->ssvd_reg_wr.STATUS->tunint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                    safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_reg_wr.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT ");
           if  (api->rsp->ssvd_reg_wr.STATUS->atvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->ssvd_reg_wr.STATUS->atvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                    safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_reg_wr.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT ");
           if  (api->rsp->ssvd_reg_wr.STATUS->dtvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->ssvd_reg_wr.STATUS->dtvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                    safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_reg_wr.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR    ");
           if  (api->rsp->ssvd_reg_wr.STATUS->err    ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->ssvd_reg_wr.STATUS->err    ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                    safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_reg_wr.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS    ");
           if  (api->rsp->ssvd_reg_wr.STATUS->cts    ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->ssvd_reg_wr.STATUS->cts    ==     0) safe_strcat(msg,"WAIT     ");
      else                                                    safe_sprintf(msg,"%s%d", msg, api->rsp->ssvd_reg_wr.STATUS->cts);
     break;
    #endif /*     Si2190B_SSVD_REG_WR_CMD */

    #ifdef        Si21XXC_STANDBY_CMD
     case         Si21XXC_STANDBY_CMD_CODE:
      safe_sprintf(msg,"STANDBY ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT ");
           if  (api->rsp->standby.STATUS->tunint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->standby.STATUS->tunint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                safe_sprintf(msg,"%s%d", msg, api->rsp->standby.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT ");
           if  (api->rsp->standby.STATUS->atvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->standby.STATUS->atvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                safe_sprintf(msg,"%s%d", msg, api->rsp->standby.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT ");
           if  (api->rsp->standby.STATUS->dtvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->standby.STATUS->dtvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                safe_sprintf(msg,"%s%d", msg, api->rsp->standby.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR    ");
           if  (api->rsp->standby.STATUS->err    ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->standby.STATUS->err    ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                safe_sprintf(msg,"%s%d", msg, api->rsp->standby.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS    ");
           if  (api->rsp->standby.STATUS->cts    ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->standby.STATUS->cts    ==     0) safe_strcat(msg,"WAIT     ");
      else                                                safe_sprintf(msg,"%s%d", msg, api->rsp->standby.STATUS->cts);
     break;
    #endif /*     Si21XXC_STANDBY_CMD */

    #ifdef        Si2190B_TUNER_CANCEL_TONE_STATUS_CMD
     case         Si2190B_TUNER_CANCEL_TONE_STATUS_CMD_CODE:
      safe_sprintf(msg,"TUNER_CANCEL_TONE_STATUS ");
       safe_sprintf(msg,"%s",separator); safe_strcat(msg,"-TUNINT   ");
           if  (api->rsp->tuner_cancel_tone_status.STATUS->tunint   ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->tuner_cancel_tone_status.STATUS->tunint   ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                                   safe_sprintf(msg,"%d", api->rsp->tuner_cancel_tone_status.STATUS->tunint);
       safe_sprintf(msg,"%s",separator); safe_strcat(msg,"-ATVINT   ");
           if  (api->rsp->tuner_cancel_tone_status.STATUS->atvint   ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->tuner_cancel_tone_status.STATUS->atvint   ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                                   safe_sprintf(msg,"%d", api->rsp->tuner_cancel_tone_status.STATUS->atvint);
       safe_sprintf(msg,"%s",separator); safe_strcat(msg,"-DTVINT   ");
           if  (api->rsp->tuner_cancel_tone_status.STATUS->dtvint   ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->tuner_cancel_tone_status.STATUS->dtvint   ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                                   safe_sprintf(msg,"%d", api->rsp->tuner_cancel_tone_status.STATUS->dtvint);
       safe_sprintf(msg,"%s",separator); safe_strcat(msg,"-ERR      ");
           if  (api->rsp->tuner_cancel_tone_status.STATUS->err      ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->tuner_cancel_tone_status.STATUS->err      ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                                   safe_sprintf(msg,"%d", api->rsp->tuner_cancel_tone_status.STATUS->err);
       safe_sprintf(msg,"%s",separator); safe_strcat(msg,"-CTS      ");
           if  (api->rsp->tuner_cancel_tone_status.STATUS->cts      ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->tuner_cancel_tone_status.STATUS->cts      ==     0) safe_strcat(msg,"WAIT     ");
      else                                                                   safe_sprintf(msg,"%d", api->rsp->tuner_cancel_tone_status.STATUS->cts);
       safe_sprintf(msg,"%s",separator); safe_strcat(msg,"-ACTIVE   ");
           if  (api->rsp->tuner_cancel_tone_status.active   ==     0) safe_strcat(msg,"ACTIVE  ");
      else if  (api->rsp->tuner_cancel_tone_status.active   ==     1) safe_strcat(msg,"INACTIVE");
      else                                                           safe_sprintf(msg,"%d", api->rsp->tuner_cancel_tone_status.active);
       safe_sprintf(msg,"%s",separator); safe_strcat(msg,"-STATUS   ");
           if  (api->rsp->tuner_cancel_tone_status.status   ==     8) safe_strcat(msg,"CLOSE_PC");
      else if  (api->rsp->tuner_cancel_tone_status.status   ==     3) safe_strcat(msg,"DELAYED ");
      else if  (api->rsp->tuner_cancel_tone_status.status   ==     0) safe_strcat(msg,"ENABLED ");
      else if  (api->rsp->tuner_cancel_tone_status.status   ==     6) safe_strcat(msg,"NO_SPUR ");
      else if  (api->rsp->tuner_cancel_tone_status.status   ==     1) safe_strcat(msg,"STARTUP ");
      else                                                           safe_sprintf(msg,"%d", api->rsp->tuner_cancel_tone_status.status);
       safe_sprintf(msg,"%s",separator); safe_strcat(msg,"-TYPE     ");
           if  (api->rsp->tuner_cancel_tone_status.type     ==     4) safe_strcat(msg,"FS32_SPUR");
      else if  (api->rsp->tuner_cancel_tone_status.type     ==     1) safe_strcat(msg,"FS_SPUR  ");
      else if  (api->rsp->tuner_cancel_tone_status.type     ==     2) safe_strcat(msg,"LO_SPUR  ");
      else if  (api->rsp->tuner_cancel_tone_status.type     ==     3) safe_strcat(msg,"TS_SPUR  ");
      else if  (api->rsp->tuner_cancel_tone_status.type     ==     0) safe_strcat(msg,"UNKNOWN  ");
      else                                                           safe_sprintf(msg,"%d", api->rsp->tuner_cancel_tone_status.type);
       safe_sprintf(msg,"%s",separator); safe_strcat(msg,"-FREQ_KHZ "); safe_sprintf(msg,"%d" , api->rsp->tuner_cancel_tone_status.freq_khz);
     break;
    #endif /*     Si2190B_TUNER_CANCEL_TONE_STATUS_CMD */

    #ifdef        Si2190B_TUNER_CANCEL_TONE_CMD
     case         Si2190B_TUNER_CANCEL_TONE_CMD_CODE:
      safe_sprintf(msg,"TUNER_CANCEL_TONE ");
       safe_sprintf(msg,"%s",separator); safe_strcat(msg,"-TUNINT ");
           if  (api->rsp->tuner_cancel_tone.STATUS->tunint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->tuner_cancel_tone.STATUS->tunint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                          safe_sprintf(msg,"%d", api->rsp->tuner_cancel_tone.STATUS->tunint);
       safe_sprintf(msg,"%s",separator); safe_strcat(msg,"-ATVINT ");
           if  (api->rsp->tuner_cancel_tone.STATUS->atvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->tuner_cancel_tone.STATUS->atvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                          safe_sprintf(msg,"%d", api->rsp->tuner_cancel_tone.STATUS->atvint);
       safe_sprintf(msg,"%s",separator); safe_strcat(msg,"-DTVINT ");
           if  (api->rsp->tuner_cancel_tone.STATUS->dtvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->tuner_cancel_tone.STATUS->dtvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                          safe_sprintf(msg,"%d", api->rsp->tuner_cancel_tone.STATUS->dtvint);
       safe_sprintf(msg,"%s",separator); safe_strcat(msg,"-ERR    ");
           if  (api->rsp->tuner_cancel_tone.STATUS->err    ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->tuner_cancel_tone.STATUS->err    ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                          safe_sprintf(msg,"%d", api->rsp->tuner_cancel_tone.STATUS->err);
       safe_sprintf(msg,"%s",separator); safe_strcat(msg,"-CTS    ");
           if  (api->rsp->tuner_cancel_tone.STATUS->cts    ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->tuner_cancel_tone.STATUS->cts    ==     0) safe_strcat(msg,"WAIT     ");
      else                                                          safe_sprintf(msg,"%d", api->rsp->tuner_cancel_tone.STATUS->cts);
     break;
    #endif /*     Si2190B_TUNER_CANCEL_TONE_CMD */
    #ifdef        Si21XXC_TUNER_STATUS_CMD
     case         Si21XXC_TUNER_STATUS_CMD_CODE:
      safe_sprintf(msg,"TUNER_STATUS ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT   ");
           if  (api->rsp->tuner_status.STATUS->tunint   ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->tuner_status.STATUS->tunint   ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                       safe_sprintf(msg,"%s%d", msg, api->rsp->tuner_status.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT   ");
           if  (api->rsp->tuner_status.STATUS->atvint   ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->tuner_status.STATUS->atvint   ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                       safe_sprintf(msg,"%s%d", msg, api->rsp->tuner_status.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT   ");
           if  (api->rsp->tuner_status.STATUS->dtvint   ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->tuner_status.STATUS->dtvint   ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                       safe_sprintf(msg,"%s%d", msg, api->rsp->tuner_status.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR      ");
           if  (api->rsp->tuner_status.STATUS->err      ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->tuner_status.STATUS->err      ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                       safe_sprintf(msg,"%s%d", msg, api->rsp->tuner_status.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS      ");
           if  (api->rsp->tuner_status.STATUS->cts      ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->tuner_status.STATUS->cts      ==     0) safe_strcat(msg,"WAIT     ");
      else                                                       safe_sprintf(msg,"%s%d", msg, api->rsp->tuner_status.STATUS->cts);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TCINT    ");
           if  (api->rsp->tuner_status.tcint    ==     1) safe_strcat(msg,"CHANGED  ");
      else if  (api->rsp->tuner_status.tcint    ==     0) safe_strcat(msg,"NO_CHANGE");
      else                                               safe_sprintf(msg,"%s%d", msg, api->rsp->tuner_status.tcint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-RSSILINT ");
           if  (api->rsp->tuner_status.rssilint ==     1) safe_strcat(msg,"CHANGED  ");
      else if  (api->rsp->tuner_status.rssilint ==     0) safe_strcat(msg,"NO_CHANGE");
      else                                               safe_sprintf(msg,"%s%d", msg, api->rsp->tuner_status.rssilint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-RSSIHINT ");
           if  (api->rsp->tuner_status.rssihint ==     1) safe_strcat(msg,"CHANGED  ");
      else if  (api->rsp->tuner_status.rssihint ==     0) safe_strcat(msg,"NO_CHANGE");
      else                                               safe_sprintf(msg,"%s%d", msg, api->rsp->tuner_status.rssihint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TC       ");
           if  (api->rsp->tuner_status.tc       ==     0) safe_strcat(msg,"BUSY");
      else if  (api->rsp->tuner_status.tc       ==     1) safe_strcat(msg,"DONE");
      else                                               safe_sprintf(msg,"%s%d", msg, api->rsp->tuner_status.tc);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-RSSIL    ");
           if  (api->rsp->tuner_status.rssil    ==     1) safe_strcat(msg,"LOW");
      else if  (api->rsp->tuner_status.rssil    ==     0) safe_strcat(msg,"OK ");
      else                                               safe_sprintf(msg,"%s%d", msg, api->rsp->tuner_status.rssil);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-RSSIH    ");
           if  (api->rsp->tuner_status.rssih    ==     1) safe_strcat(msg,"HIGH");
      else if  (api->rsp->tuner_status.rssih    ==     0) safe_strcat(msg,"OK  ");
      else                                               safe_sprintf(msg,"%s%d", msg, api->rsp->tuner_status.rssih);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-RSSI     "); safe_sprintf(msg,"%s%d", msg, api->rsp->tuner_status.rssi);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-FREQ     "); safe_sprintf(msg,"%s%ld", msg, api->rsp->tuner_status.freq);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-MODE     ");
           if  (api->rsp->tuner_status.mode     ==     1) safe_strcat(msg,"ATV");
      else if  (api->rsp->tuner_status.mode     ==     0) safe_strcat(msg,"DTV");
      else                                               safe_sprintf(msg,"%s%d", msg, api->rsp->tuner_status.mode);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-VCO_CODE "); safe_sprintf(msg,"%s%d", msg, api->rsp->tuner_status.vco_code);
     break;
    #endif /*     Si21XXC_TUNER_STATUS_CMD */

    #ifdef        Si21XXC_TUNER_TUNE_FREQ_CMD
     case         Si21XXC_TUNER_TUNE_FREQ_CMD_CODE:
      safe_sprintf(msg,"TUNER_TUNE_FREQ ");
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-TUNINT ");
           if  (api->rsp->tuner_tune_freq.STATUS->tunint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->tuner_tune_freq.STATUS->tunint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                        safe_sprintf(msg,"%s%d", msg, api->rsp->tuner_tune_freq.STATUS->tunint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ATVINT ");
           if  (api->rsp->tuner_tune_freq.STATUS->atvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->tuner_tune_freq.STATUS->atvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                        safe_sprintf(msg,"%s%d", msg, api->rsp->tuner_tune_freq.STATUS->atvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-DTVINT ");
           if  (api->rsp->tuner_tune_freq.STATUS->dtvint ==     0) safe_strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->tuner_tune_freq.STATUS->dtvint ==     1) safe_strcat(msg,"TRIGGERED    ");
      else                                                        safe_sprintf(msg,"%s%d", msg, api->rsp->tuner_tune_freq.STATUS->dtvint);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-ERR    ");
           if  (api->rsp->tuner_tune_freq.STATUS->err    ==     1) safe_strcat(msg,"ERROR   ");
      else if  (api->rsp->tuner_tune_freq.STATUS->err    ==     0) safe_strcat(msg,"NO_ERROR");
      else                                                        safe_sprintf(msg,"%s%d", msg, api->rsp->tuner_tune_freq.STATUS->err);
       safe_sprintf(msg,"%s%s",msg,separator); safe_strcat(msg,"-CTS    ");
           if  (api->rsp->tuner_tune_freq.STATUS->cts    ==     1) safe_strcat(msg,"COMPLETED");
      else if  (api->rsp->tuner_tune_freq.STATUS->cts    ==     0) safe_strcat(msg,"WAIT     ");
      else                                                        safe_sprintf(msg,"%s%d", msg, api->rsp->tuner_tune_freq.STATUS->cts);
     break;
    #endif /*     Si21XXC_TUNER_TUNE_FREQ_CMD */

     default : break;
    }
#endif
    return 0;
  }
  /* _get_command_response_string_insertion_point */
#endif /* Si21XXC_GET_COMMAND_STRINGS */






