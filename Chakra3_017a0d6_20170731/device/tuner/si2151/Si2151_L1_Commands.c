/*************************************************************************************
                  Silicon Laboratories Broadcast Si2151 Layer 1 API

   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
     PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.

   API commands definitions
   FILE: Si2151_L1_Commands.c
   Supported IC : Si2151
   Compiled for ROM 61 firmware 1_1_build_6
   Revision: 0.2
   Tag:  ROM61_1_1_build_6_V0.2
   Date: October 29 2014
  (C) Copyright 2014, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#define   Si2151_COMMAND_PROTOTYPES

#include "Si2151_L1_API.h"

/******   conversion functions, used to fill command response fields ***************************************************
  These functions provide compatibility with 8 bytes processing on some compilers
 ***********************************************************************************************************************/
unsigned char Si2151_convert_to_byte (const unsigned char* buffer, unsigned char shift, unsigned char mask) {
  unsigned int rspBuffer = *buffer;
  return ((rspBuffer >> shift) & mask);
}
unsigned long Si2151_convert_to_ulong(const unsigned char* buffer, unsigned char shift,unsigned long mask) {
  return ((( ( (unsigned long)buffer[0]) | ((unsigned long)buffer[1] << 8) | ((unsigned long)buffer[2]<<16) | ((unsigned long)buffer[3]<<24)) >> shift) & mask );
}
unsigned int  Si2151_convert_to_uint (const unsigned char* buffer, unsigned char shift,unsigned int mask) {
  return (( ( (unsigned int)buffer[0]) | (((unsigned int)buffer[1]) << 8) >> shift) & mask);
}
short         Si2151_convert_to_int  (const unsigned char* buffer, unsigned char shift,unsigned int mask) {
  return (( ( (unsigned int)buffer[0]) | (((unsigned int)buffer[1]) << 8) >> shift) & mask);
}
/***********************************************************************************************************************
  Si2151_CurrentResponseStatus function
  Use:        status checking function
              Used to fill the Si2151_COMMON_REPLY_struct members with the ptDataBuffer byte's bits
  Comments:   The status byte definition being identical for all commands,
              using this function to fill the status structure helps reducing the code size
  Parameter: ptDataBuffer  a single byte received when reading a command's response (the first byte)
  Returns:   0 if the err bit (bit 6) is unset, 1 otherwise
 ***********************************************************************************************************************/
unsigned char Si2151_CurrentResponseStatus (L1_Si2151_Context *api, unsigned char ptDataBuffer)
{
    api->status->tunint =     Si2151_convert_to_byte(&ptDataBuffer, 0, 0x01);
    api->status->atvint =     Si2151_convert_to_byte(&ptDataBuffer, 1, 0x01);
    api->status->dtvint =     Si2151_convert_to_byte(&ptDataBuffer, 2, 0x01);
    api->status->err    =     Si2151_convert_to_byte(&ptDataBuffer, 6, 0x01);
    api->status->cts    =     Si2151_convert_to_byte(&ptDataBuffer, 7, 0x01);
  return (api->status->err ? ERROR_Si2151_ERR : NO_Si2151_ERROR);
}

 /***********************************************************************************************************************
  Si2151_pollForResetState function
  Use:        ResetState checking function
              Used to check the status byte for the reset code (0xFE).
  Comments:   Only required for the Si2151_L1_POWER_DOWN_HW Command

  Returns:   0 if the Status byte is = 0xFE, nonzero otherwise
 ***********************************************************************************************************************/
unsigned char Si2151_pollForResetState (L1_Si2151_Context *api)
{
  unsigned char rspByteBuffer[1] = {0};
  unsigned int start_time;

  start_time = system_time();

  while (system_time() - start_time <1000)  { /* wait a maximum of 1000ms */
    if (L0_ReadCommandBytes(api->i2c, 1, rspByteBuffer) != 1) {
      SiTRACE("Si2151_pollForResetState ERROR reading byte 0!\n");
      return ERROR_Si2151_POLLING_CTS;
    }
    /* return OK if status=0xFE set */
    if (rspByteBuffer[0] == 0xFE) {
      return NO_Si2151_ERROR;
    }
  }

  SiTRACE("Si2151_pollForResetState ERROR status Timeout!\n");
  return ERROR_Si2151_CTS_TIMEOUT;
}
/***********************************************************************************************************************
  Si2151_GetStatus function
  Use:        POWER_UP checking function
              Used to check the status byte the reset code (0xFE) to drop.
  Comments:   Only required for the Si2151_L1_POWER_UP Command

  Returns:   0 if the Status byte is = 0xFE, nonzero otherwise
 ***********************************************************************************************************************/
unsigned char Si2151_GetStatus (L1_Si2151_Context *api)
{
    unsigned char rspByteBuffer[1] = {0};

    if (L0_ReadCommandBytes(api->i2c, 1, rspByteBuffer) != 1)
    {
      SiTRACE("Si2151_GetStatus ERROR reading byte 0!\n");
      return ERROR_Si2151_POLLING_CTS;
    }

    return (rspByteBuffer[0]);
}
/***********************************************************************************************************************
  Si2151_pollForCTS function
  Use:        CTS checking function
              Used to check the CTS bit until it is set before sending the next command
  Comments:   The status byte definition being identical for all commands,
              using this function to fill the status structure helps reducing the code size
              max timeout = 1000 ms

  Returns:   1 if the CTS bit is set, 0 otherwise
 ***********************************************************************************************************************/
unsigned char Si2151_pollForCTS (L1_Si2151_Context *api)
{
  unsigned char rspByteBuffer[1] = {0};
  unsigned int start_time;

  start_time = system_time();

  while (system_time() - start_time <1000)  { /* wait a maximum of 1000ms */
    if (L0_ReadCommandBytes(api->i2c, 1, rspByteBuffer) != 1) {
      SiTRACE("Si2151_pollForCTS ERROR reading byte 0!\n");
      return ERROR_Si2151_POLLING_CTS;
    }
    /* return OK if CTS set */
    if (rspByteBuffer[0] & 0x80) {
      return NO_Si2151_ERROR;
    }
  }

  SiTRACE("Si2151_pollForCTS ERROR CTS Timeout!\n");
  return ERROR_Si2151_CTS_TIMEOUT;
}

/***********************************************************************************************************************
  Si2151_pollForResponse function
  Use:        command response retrieval function
              Used to retrieve the command response in the provided buffer
  Comments:   The status byte definition being identical for all commands,
              using this function to fill the status structure helps reducing the code size
              max timeout = 1000 ms

  Parameter:  nbBytes          the number of response bytes to read
  Parameter:  pByteBuffer      a buffer into which bytes will be stored
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/
unsigned char Si2151_pollForResponse (L1_Si2151_Context *api, unsigned int nbBytes, unsigned char *pByteBuffer)
{
  unsigned char debugBuffer[7];
  unsigned int start_time;

  start_time = system_time();

  while (system_time() - start_time <1000)  { /* wait a maximum of 1000ms */
    if ((unsigned int)L0_ReadCommandBytes(api->i2c, nbBytes, pByteBuffer) != nbBytes) {
      SiTRACE("Si2151_pollForResponse ERROR reading byte 0!\n");
      return ERROR_Si2151_POLLING_RESPONSE;
    }
    /* return response err flag if CTS set */
    if (pByteBuffer[0] & 0x80)  {
     /* for debug purpose, read and trace 2 bytes in case the error bit is set */
      if (pByteBuffer[0] & 0x40)  {
        L0_ReadCommandBytes(api->i2c, 7, &(debugBuffer[0]) );
        SiTRACE("Si2151 debug bytes 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x 0x%02x\n", debugBuffer[0], debugBuffer[1], debugBuffer[2], debugBuffer[3], debugBuffer[4], debugBuffer[5], debugBuffer[6]);
      }
      return Si2151_CurrentResponseStatus(api, pByteBuffer[0]);
    }
  }

  SiTRACE("Si2151_pollForResponse ERROR CTS Timeout!\n");
  return ERROR_Si2151_CTS_TIMEOUT;
}

#ifdef    Si2151_AGC_OVERRIDE_CMD
/*---------------------------------------------------*/
/* Si2151_AGC_OVERRIDE COMMAND                         */
/*---------------------------------------------------*/
unsigned char Si2151_L1_AGC_OVERRIDE    (L1_Si2151_Context *api,
                                         unsigned char   force_max_gain,
                                         unsigned char   force_top_gain)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[1];
    api->rsp->agc_override.STATUS = api->status;

    SiTRACE("Si2151 AGC_OVERRIDE ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((force_max_gain > Si2151_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FORCE_MAX_GAIN %d ", force_max_gain );
    if ((force_top_gain > Si2151_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FORCE_TOP_GAIN %d ", force_top_gain );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2151_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2151_AGC_OVERRIDE_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( force_max_gain & Si2151_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_MASK ) << Si2151_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_LSB|
                                         ( force_top_gain & Si2151_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_MASK ) << Si2151_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing AGC_OVERRIDE bytes!\n");
      return ERROR_Si2151_SENDING_COMMAND;
    }

    error_code = Si2151_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling AGC_OVERRIDE response\n");
      return error_code;
    }


    return NO_Si2151_ERROR;
}
#endif /* Si2151_AGC_OVERRIDE_CMD */
#ifdef    Si2151_ATV_SCAN_TUNE_CMD
/*---------------------------------------------------*/
/* Si2151_ATV_SCAN_TUNE COMMAND                       */
/*---------------------------------------------------*/
unsigned char Si2151_L1_ATV_SCAN_TUNE   (L1_Si2151_Context *api,
                                         unsigned long   freq)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[8];
    unsigned char rspByteBuffer[1];
    api->rsp->atv_scan_tune.STATUS = api->status;

    SiTRACE("Si2151 ATV_SCAN_TUNE ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((freq > Si2151_ATV_SCAN_TUNE_CMD_FREQ_MAX)  || (freq < Si2151_ATV_SCAN_TUNE_CMD_FREQ_MIN) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FREQ %d ", freq );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2151_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2151_ATV_SCAN_TUNE_CMD;
    cmdByteBuffer[1] = (unsigned char)0x00;
    cmdByteBuffer[2] = (unsigned char)0x00;
    cmdByteBuffer[3] = (unsigned char)0x00;
    cmdByteBuffer[4] = (unsigned char) ( ( freq & Si2151_ATV_SCAN_TUNE_CMD_FREQ_MASK ) << Si2151_ATV_SCAN_TUNE_CMD_FREQ_LSB);
    cmdByteBuffer[5] = (unsigned char) ((( freq & Si2151_ATV_SCAN_TUNE_CMD_FREQ_MASK ) << Si2151_ATV_SCAN_TUNE_CMD_FREQ_LSB)>>8);
    cmdByteBuffer[6] = (unsigned char) ((( freq & Si2151_ATV_SCAN_TUNE_CMD_FREQ_MASK ) << Si2151_ATV_SCAN_TUNE_CMD_FREQ_LSB)>>16);
    cmdByteBuffer[7] = (unsigned char) ((( freq & Si2151_ATV_SCAN_TUNE_CMD_FREQ_MASK ) << Si2151_ATV_SCAN_TUNE_CMD_FREQ_LSB)>>24);

    if (L0_WriteCommandBytes(api->i2c, 8, cmdByteBuffer) != 8) {
      SiTRACE("Error writing ATV_SCAN_TUNE bytes!\n");
      return ERROR_Si2151_SENDING_COMMAND;
    }

    error_code = Si2151_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling ATV_SCAN_TUNE response\n");
      return error_code;
    }


    return NO_Si2151_ERROR;
}
#endif /* Si2151_ATV_SCAN_TUNE_CMD */
#ifdef    Si2151_CONFIG_CLOCKS_CMD
/*---------------------------------------------------*/
/* Si2151_CONFIG_CLOCKS COMMAND                       */
/*---------------------------------------------------*/
unsigned char Si2151_L1_CONFIG_CLOCKS   (L1_Si2151_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   clock_mode,
                                         unsigned char   en_xout)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[3];
    unsigned char rspByteBuffer[1];
    api->rsp->config_clocks.STATUS = api->status;

    SiTRACE("Si2151 CONFIG_CLOCKS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode    > Si2151_CONFIG_CLOCKS_CMD_SUBCODE_MAX   ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "   , subcode    );
    if ((clock_mode > Si2151_CONFIG_CLOCKS_CMD_CLOCK_MODE_MAX)  || (clock_mode < Si2151_CONFIG_CLOCKS_CMD_CLOCK_MODE_MIN) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CLOCK_MODE %d ", clock_mode );
    if ((en_xout    > Si2151_CONFIG_CLOCKS_CMD_EN_XOUT_MAX   ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("EN_XOUT %d "   , en_xout    );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2151_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2151_CONFIG_CLOCKS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode    & Si2151_CONFIG_CLOCKS_CMD_SUBCODE_MASK    ) << Si2151_CONFIG_CLOCKS_CMD_SUBCODE_LSB   );
    cmdByteBuffer[2] = (unsigned char) ( ( clock_mode & Si2151_CONFIG_CLOCKS_CMD_CLOCK_MODE_MASK ) << Si2151_CONFIG_CLOCKS_CMD_CLOCK_MODE_LSB|
                                         ( en_xout    & Si2151_CONFIG_CLOCKS_CMD_EN_XOUT_MASK    ) << Si2151_CONFIG_CLOCKS_CMD_EN_XOUT_LSB   );

    if (L0_WriteCommandBytes(api->i2c, 3, cmdByteBuffer) != 3) {
      SiTRACE("Error writing CONFIG_CLOCKS bytes!\n");
      return ERROR_Si2151_SENDING_COMMAND;
    }

    error_code = Si2151_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling CONFIG_CLOCKS response\n");
      return error_code;
    }


    return NO_Si2151_ERROR;
}
#endif /* Si2151_CONFIG_CLOCKS_CMD */
#ifdef    Si2151_CONFIG_I2C_CMD
/*---------------------------------------------------*/
/* Si2151_CONFIG_I2C COMMAND                             */
/*---------------------------------------------------*/
unsigned char Si2151_L1_CONFIG_I2C      (L1_Si2151_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   i2c_broadcast)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[3];
    unsigned char rspByteBuffer[1];
    api->rsp->config_i2c.STATUS = api->status;

    SiTRACE("Si2151 CONFIG_I2C ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode       > Si2151_CONFIG_I2C_CMD_SUBCODE_MAX      )  || (subcode       < Si2151_CONFIG_I2C_CMD_SUBCODE_MIN      ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "      , subcode       );
    if ((i2c_broadcast > Si2151_CONFIG_I2C_CMD_I2C_BROADCAST_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("I2C_BROADCAST %d ", i2c_broadcast );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2151_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2151_CONFIG_I2C_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode       & Si2151_CONFIG_I2C_CMD_SUBCODE_MASK       ) << Si2151_CONFIG_I2C_CMD_SUBCODE_LSB      );
    cmdByteBuffer[2] = (unsigned char) ( ( i2c_broadcast & Si2151_CONFIG_I2C_CMD_I2C_BROADCAST_MASK ) << Si2151_CONFIG_I2C_CMD_I2C_BROADCAST_LSB);

    if (L0_WriteCommandBytes(api->i2c, 3, cmdByteBuffer) != 3) {
      SiTRACE("Error writing CONFIG_I2C bytes!\n");
      return ERROR_Si2151_SENDING_COMMAND;
    }

    error_code = Si2151_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling CONFIG_I2C response\n");
      return error_code;
    }
    return NO_Si2151_ERROR;
}
#endif /* Si2151_CONFIG_I2C_CMD */
#ifdef    Si2151_CONFIG_PINS_CMD
/*---------------------------------------------------*/
/* Si2151_CONFIG_PINS COMMAND                           */
/*---------------------------------------------------*/
unsigned char Si2151_L1_CONFIG_PINS     (L1_Si2151_Context *api,
                                         unsigned char   gpio1_mode,
                                         unsigned char   gpio1_read,
                                         unsigned char   gpio2_mode,
                                         unsigned char   gpio2_read,
                                         unsigned char   agc1_mode,
                                         unsigned char   agc1_read,
                                         unsigned char   agc2_mode,
                                         unsigned char   agc2_read,
                                         unsigned char   xout_mode)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[7];
    unsigned char rspByteBuffer[7] = {0}; // Fix coverity-59355
    api->rsp->config_pins.STATUS = api->status;

    SiTRACE("Si2151 CONFIG_PINS ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((gpio1_mode > Si2151_CONFIG_PINS_CMD_GPIO1_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO1_MODE %d ", gpio1_mode );
    if ((gpio1_read > Si2151_CONFIG_PINS_CMD_GPIO1_READ_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO1_READ %d ", gpio1_read );
    if ((gpio2_mode > Si2151_CONFIG_PINS_CMD_GPIO2_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO2_MODE %d ", gpio2_mode );
    if ((gpio2_read > Si2151_CONFIG_PINS_CMD_GPIO2_READ_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("GPIO2_READ %d ", gpio2_read );
    if ((agc1_mode  > Si2151_CONFIG_PINS_CMD_AGC1_MODE_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("AGC1_MODE %d " , agc1_mode  );
    if ((agc1_read  > Si2151_CONFIG_PINS_CMD_AGC1_READ_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("AGC1_READ %d " , agc1_read  );
    if ((agc2_mode  > Si2151_CONFIG_PINS_CMD_AGC2_MODE_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("AGC2_MODE %d " , agc2_mode  );
    if ((agc2_read  > Si2151_CONFIG_PINS_CMD_AGC2_READ_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("AGC2_READ %d " , agc2_read  );
    if ((xout_mode  > Si2151_CONFIG_PINS_CMD_XOUT_MODE_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("XOUT_MODE %d " , xout_mode  );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2151_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2151_CONFIG_PINS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( gpio1_mode & Si2151_CONFIG_PINS_CMD_GPIO1_MODE_MASK ) << Si2151_CONFIG_PINS_CMD_GPIO1_MODE_LSB|
                                         ( gpio1_read & Si2151_CONFIG_PINS_CMD_GPIO1_READ_MASK ) << Si2151_CONFIG_PINS_CMD_GPIO1_READ_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( gpio2_mode & Si2151_CONFIG_PINS_CMD_GPIO2_MODE_MASK ) << Si2151_CONFIG_PINS_CMD_GPIO2_MODE_LSB|
                                         ( gpio2_read & Si2151_CONFIG_PINS_CMD_GPIO2_READ_MASK ) << Si2151_CONFIG_PINS_CMD_GPIO2_READ_LSB);
    cmdByteBuffer[3] = (unsigned char) ( ( agc1_mode  & Si2151_CONFIG_PINS_CMD_AGC1_MODE_MASK  ) << Si2151_CONFIG_PINS_CMD_AGC1_MODE_LSB |
                                         ( agc1_read  & Si2151_CONFIG_PINS_CMD_AGC1_READ_MASK  ) << Si2151_CONFIG_PINS_CMD_AGC1_READ_LSB );
    cmdByteBuffer[4] = (unsigned char)0x00;
    cmdByteBuffer[5] = (unsigned char) ( ( agc2_mode  & Si2151_CONFIG_PINS_CMD_AGC2_MODE_MASK  ) << Si2151_CONFIG_PINS_CMD_AGC2_MODE_LSB |
                                         ( agc2_read  & Si2151_CONFIG_PINS_CMD_AGC2_READ_MASK  ) << Si2151_CONFIG_PINS_CMD_AGC2_READ_LSB );
    cmdByteBuffer[6] = (unsigned char) ( ( xout_mode  & Si2151_CONFIG_PINS_CMD_XOUT_MODE_MASK  ) << Si2151_CONFIG_PINS_CMD_XOUT_MODE_LSB );

    if (L0_WriteCommandBytes(api->i2c, 7, cmdByteBuffer) != 7) {
      SiTRACE("Error writing CONFIG_PINS bytes!\n");
      return ERROR_Si2151_SENDING_COMMAND;
    }

    error_code = Si2151_pollForResponse(api, 7, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling CONFIG_PINS response\n");
      return error_code;
    }

    api->rsp->config_pins.gpio1_mode  = Si2151_convert_to_byte  (&rspByteBuffer[ 1] , Si2151_CONFIG_PINS_RESPONSE_GPIO1_MODE_LSB   , Si2151_CONFIG_PINS_RESPONSE_GPIO1_MODE_MASK  );
    api->rsp->config_pins.gpio1_state = Si2151_convert_to_byte  (&rspByteBuffer[ 1] , Si2151_CONFIG_PINS_RESPONSE_GPIO1_STATE_LSB  , Si2151_CONFIG_PINS_RESPONSE_GPIO1_STATE_MASK );
    api->rsp->config_pins.gpio2_mode  = Si2151_convert_to_byte  (&rspByteBuffer[ 2] , Si2151_CONFIG_PINS_RESPONSE_GPIO2_MODE_LSB   , Si2151_CONFIG_PINS_RESPONSE_GPIO2_MODE_MASK  );
    api->rsp->config_pins.gpio2_state = Si2151_convert_to_byte  (&rspByteBuffer[ 2] , Si2151_CONFIG_PINS_RESPONSE_GPIO2_STATE_LSB  , Si2151_CONFIG_PINS_RESPONSE_GPIO2_STATE_MASK );
    api->rsp->config_pins.agc1_mode   = Si2151_convert_to_byte  (&rspByteBuffer[ 3] , Si2151_CONFIG_PINS_RESPONSE_AGC1_MODE_LSB    , Si2151_CONFIG_PINS_RESPONSE_AGC1_MODE_MASK   );
    api->rsp->config_pins.agc1_state  = Si2151_convert_to_byte  (&rspByteBuffer[ 3] , Si2151_CONFIG_PINS_RESPONSE_AGC1_STATE_LSB   , Si2151_CONFIG_PINS_RESPONSE_AGC1_STATE_MASK  );
    api->rsp->config_pins.agc2_mode   = Si2151_convert_to_byte  (&rspByteBuffer[ 5] , Si2151_CONFIG_PINS_RESPONSE_AGC2_MODE_LSB    , Si2151_CONFIG_PINS_RESPONSE_AGC2_MODE_MASK   );
    api->rsp->config_pins.agc2_state  = Si2151_convert_to_byte  (&rspByteBuffer[ 5] , Si2151_CONFIG_PINS_RESPONSE_AGC2_STATE_LSB   , Si2151_CONFIG_PINS_RESPONSE_AGC2_STATE_MASK  );
    api->rsp->config_pins.xout_mode   = Si2151_convert_to_byte  (&rspByteBuffer[ 6] , Si2151_CONFIG_PINS_RESPONSE_XOUT_MODE_LSB    , Si2151_CONFIG_PINS_RESPONSE_XOUT_MODE_MASK   );
    api->rsp->config_pins.xout_state  = Si2151_convert_to_byte  (&rspByteBuffer[ 6] , Si2151_CONFIG_PINS_RESPONSE_XOUT_STATE_LSB   , Si2151_CONFIG_PINS_RESPONSE_XOUT_STATE_MASK  );

    return NO_Si2151_ERROR;
}
#endif /* Si2151_CONFIG_PINS_CMD */
#ifdef    Si2151_EXIT_BOOTLOADER_CMD
/*---------------------------------------------------*/
/* Si2151_EXIT_BOOTLOADER COMMAND                   */
/*---------------------------------------------------*/
unsigned char Si2151_L1_EXIT_BOOTLOADER (L1_Si2151_Context *api,
                                         unsigned char   func,
                                         unsigned char   ctsien)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[1];
    api->rsp->exit_bootloader.STATUS = api->status;

    SiTRACE("Si2151 EXIT_BOOTLOADER ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((func   > Si2151_EXIT_BOOTLOADER_CMD_FUNC_MAX  )  || (func   < Si2151_EXIT_BOOTLOADER_CMD_FUNC_MIN  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FUNC %d "  , func   );
    if ((ctsien > Si2151_EXIT_BOOTLOADER_CMD_CTSIEN_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CTSIEN %d ", ctsien );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2151_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2151_EXIT_BOOTLOADER_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( func   & Si2151_EXIT_BOOTLOADER_CMD_FUNC_MASK   ) << Si2151_EXIT_BOOTLOADER_CMD_FUNC_LSB  |
                                         ( ctsien & Si2151_EXIT_BOOTLOADER_CMD_CTSIEN_MASK ) << Si2151_EXIT_BOOTLOADER_CMD_CTSIEN_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing EXIT_BOOTLOADER bytes!\n");
      return ERROR_Si2151_SENDING_COMMAND;
    }

    error_code = Si2151_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling EXIT_BOOTLOADER response\n");
      return error_code;
    }


    return NO_Si2151_ERROR;
}
#endif /* Si2151_EXIT_BOOTLOADER_CMD */
#ifdef    Si2151_FINE_TUNE_CMD
/*---------------------------------------------------*/
/* Si2151_FINE_TUNE COMMAND                               */
/*---------------------------------------------------*/
unsigned char Si2151_L1_FINE_TUNE       (L1_Si2151_Context *api,
                                         unsigned char   persistence,
                                                   int   offset_500hz)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[4];
    unsigned char rspByteBuffer[1];
    api->rsp->fine_tune.STATUS = api->status;

    SiTRACE("Si2151 FINE_TUNE ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((persistence  > Si2151_FINE_TUNE_CMD_PERSISTENCE_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("PERSISTENCE %d " , persistence  );
    if ((offset_500hz > Si2151_FINE_TUNE_CMD_OFFSET_500HZ_MAX)  || (offset_500hz < Si2151_FINE_TUNE_CMD_OFFSET_500HZ_MIN) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("OFFSET_500HZ %d ", offset_500hz );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2151_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2151_FINE_TUNE_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( persistence  & Si2151_FINE_TUNE_CMD_PERSISTENCE_MASK  ) << Si2151_FINE_TUNE_CMD_PERSISTENCE_LSB );
    cmdByteBuffer[2] = (unsigned char) ( ( offset_500hz & Si2151_FINE_TUNE_CMD_OFFSET_500HZ_MASK ) << Si2151_FINE_TUNE_CMD_OFFSET_500HZ_LSB);
    cmdByteBuffer[3] = (unsigned char) ((( offset_500hz & Si2151_FINE_TUNE_CMD_OFFSET_500HZ_MASK ) << Si2151_FINE_TUNE_CMD_OFFSET_500HZ_LSB)>>8);

    if (L0_WriteCommandBytes(api->i2c, 4, cmdByteBuffer) != 4) {
      SiTRACE("Error writing FINE_TUNE bytes!\n");
      return ERROR_Si2151_SENDING_COMMAND;
    }

    error_code = Si2151_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling FINE_TUNE response\n");
      return error_code;
    }


    return NO_Si2151_ERROR;
}
#endif /* Si2151_FINE_TUNE_CMD */
#ifdef    Si2151_GET_PROPERTY_CMD
/*---------------------------------------------------*/
/* Si2151_GET_PROPERTY COMMAND                         */
/*---------------------------------------------------*/
unsigned char Si2151_L1_GET_PROPERTY    (L1_Si2151_Context *api,
                                         unsigned char   reserved,
                                         unsigned int    prop)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[4];
    unsigned char rspByteBuffer[4] = {0}; // Fix coverity-59356
    api->rsp->get_property.STATUS = api->status;

    SiTRACE("Si2151 GET_PROPERTY ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((reserved > Si2151_GET_PROPERTY_CMD_RESERVED_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED %d ", reserved );
    SiTRACE("PROP %d "    , prop     );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2151_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2151_GET_PROPERTY_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( reserved & Si2151_GET_PROPERTY_CMD_RESERVED_MASK ) << Si2151_GET_PROPERTY_CMD_RESERVED_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( prop     & Si2151_GET_PROPERTY_CMD_PROP_MASK     ) << Si2151_GET_PROPERTY_CMD_PROP_LSB    );
    cmdByteBuffer[3] = (unsigned char) ((( prop     & Si2151_GET_PROPERTY_CMD_PROP_MASK     ) << Si2151_GET_PROPERTY_CMD_PROP_LSB    )>>8);

    if (L0_WriteCommandBytes(api->i2c, 4, cmdByteBuffer) != 4) {
      SiTRACE("Error writing GET_PROPERTY bytes!\n");
      return ERROR_Si2151_SENDING_COMMAND;
    }

    error_code = Si2151_pollForResponse(api, 4, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling GET_PROPERTY response\n");
      return error_code;
    }

    api->rsp->get_property.reserved = Si2151_convert_to_byte  (&rspByteBuffer[ 1] , Si2151_GET_PROPERTY_RESPONSE_RESERVED_LSB  , Si2151_GET_PROPERTY_RESPONSE_RESERVED_MASK );
    api->rsp->get_property.data     = Si2151_convert_to_uint  (&rspByteBuffer[ 2] , Si2151_GET_PROPERTY_RESPONSE_DATA_LSB      , Si2151_GET_PROPERTY_RESPONSE_DATA_MASK     );

    return NO_Si2151_ERROR;
}
#endif /* Si2151_GET_PROPERTY_CMD */
#ifdef    Si2151_GET_REV_CMD
/*---------------------------------------------------*/
/* Si2151_GET_REV COMMAND                                   */
/*---------------------------------------------------*/
unsigned char Si2151_L1_GET_REV         (L1_Si2151_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[13] = {0}; // Fix coverity-59357
    api->rsp->get_rev.STATUS = api->status;

    SiTRACE("Si2151 GET_REV ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2151_GET_REV_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing GET_REV bytes!\n");
      return ERROR_Si2151_SENDING_COMMAND;
    }

    error_code = Si2151_pollForResponse(api, 13, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling GET_REV response\n");
      return error_code;
    }

    api->rsp->get_rev.pn       = Si2151_convert_to_byte  (&rspByteBuffer[ 1] , Si2151_GET_REV_RESPONSE_PN_LSB        , Si2151_GET_REV_RESPONSE_PN_MASK       );
    api->rsp->get_rev.fwmajor  = Si2151_convert_to_byte  (&rspByteBuffer[ 2] , Si2151_GET_REV_RESPONSE_FWMAJOR_LSB   , Si2151_GET_REV_RESPONSE_FWMAJOR_MASK  );
    api->rsp->get_rev.fwminor  = Si2151_convert_to_byte  (&rspByteBuffer[ 3] , Si2151_GET_REV_RESPONSE_FWMINOR_LSB   , Si2151_GET_REV_RESPONSE_FWMINOR_MASK  );
    api->rsp->get_rev.patch    = Si2151_convert_to_uint  (&rspByteBuffer[ 4] , Si2151_GET_REV_RESPONSE_PATCH_LSB     , Si2151_GET_REV_RESPONSE_PATCH_MASK    );
    api->rsp->get_rev.cmpmajor = Si2151_convert_to_byte  (&rspByteBuffer[ 6] , Si2151_GET_REV_RESPONSE_CMPMAJOR_LSB  , Si2151_GET_REV_RESPONSE_CMPMAJOR_MASK );
    api->rsp->get_rev.cmpminor = Si2151_convert_to_byte  (&rspByteBuffer[ 7] , Si2151_GET_REV_RESPONSE_CMPMINOR_LSB  , Si2151_GET_REV_RESPONSE_CMPMINOR_MASK );
    api->rsp->get_rev.cmpbuild = Si2151_convert_to_byte  (&rspByteBuffer[ 8] , Si2151_GET_REV_RESPONSE_CMPBUILD_LSB  , Si2151_GET_REV_RESPONSE_CMPBUILD_MASK );
    api->rsp->get_rev.chiprev  = Si2151_convert_to_byte  (&rspByteBuffer[ 9] , Si2151_GET_REV_RESPONSE_CHIPREV_LSB   , Si2151_GET_REV_RESPONSE_CHIPREV_MASK  );
    api->rsp->get_rev.pn2      = Si2151_convert_to_byte  (&rspByteBuffer[12] , Si2151_GET_REV_RESPONSE_PN2_LSB       , Si2151_GET_REV_RESPONSE_PN2_MASK      );

    return NO_Si2151_ERROR;
}
#endif /* Si2151_GET_REV_CMD */
#ifdef    Si2151_PART_INFO_CMD
/*---------------------------------------------------*/
/* Si2151_PART_INFO COMMAND                               */
/*---------------------------------------------------*/
unsigned char Si2151_L1_PART_INFO       (L1_Si2151_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[14] = {0}; // Fix coverity-59358
    api->rsp->part_info.STATUS = api->status;

    SiTRACE("Si2151 PART_INFO ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2151_PART_INFO_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing PART_INFO bytes!\n");
      return ERROR_Si2151_SENDING_COMMAND;
    }

    error_code = Si2151_pollForResponse(api, 14, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling PART_INFO response\n");
      return error_code;
    }

    api->rsp->part_info.chiprev  = Si2151_convert_to_byte  (&rspByteBuffer[ 1] , Si2151_PART_INFO_RESPONSE_CHIPREV_LSB   , Si2151_PART_INFO_RESPONSE_CHIPREV_MASK  );
    api->rsp->part_info.part     = Si2151_convert_to_byte  (&rspByteBuffer[ 2] , Si2151_PART_INFO_RESPONSE_PART_LSB      , Si2151_PART_INFO_RESPONSE_PART_MASK     );
    api->rsp->part_info.pmajor   = Si2151_convert_to_byte  (&rspByteBuffer[ 3] , Si2151_PART_INFO_RESPONSE_PMAJOR_LSB    , Si2151_PART_INFO_RESPONSE_PMAJOR_MASK   );
    api->rsp->part_info.pminor   = Si2151_convert_to_byte  (&rspByteBuffer[ 4] , Si2151_PART_INFO_RESPONSE_PMINOR_LSB    , Si2151_PART_INFO_RESPONSE_PMINOR_MASK   );
    api->rsp->part_info.pbuild   = Si2151_convert_to_byte  (&rspByteBuffer[ 5] , Si2151_PART_INFO_RESPONSE_PBUILD_LSB    , Si2151_PART_INFO_RESPONSE_PBUILD_MASK   );
    api->rsp->part_info.reserved = Si2151_convert_to_uint  (&rspByteBuffer[ 6] , Si2151_PART_INFO_RESPONSE_RESERVED_LSB  , Si2151_PART_INFO_RESPONSE_RESERVED_MASK );
    api->rsp->part_info.serial   = Si2151_convert_to_ulong (&rspByteBuffer[ 8] , Si2151_PART_INFO_RESPONSE_SERIAL_LSB    , Si2151_PART_INFO_RESPONSE_SERIAL_MASK   );
    api->rsp->part_info.romid    = Si2151_convert_to_byte  (&rspByteBuffer[12] , Si2151_PART_INFO_RESPONSE_ROMID_LSB     , Si2151_PART_INFO_RESPONSE_ROMID_MASK    );
    api->rsp->part_info.part2    = Si2151_convert_to_byte  (&rspByteBuffer[13] , Si2151_PART_INFO_RESPONSE_PART2_LSB     , Si2151_PART_INFO_RESPONSE_PART2_MASK    );

    return NO_Si2151_ERROR;
}
#endif /* Si2151_PART_INFO_CMD */
#ifdef    Si2151_PART_INFO2_CMD
/*---------------------------------------------------*/
/* Si2151_PART_INFO2 COMMAND                             */
/*---------------------------------------------------*/
unsigned char Si2151_L1_PART_INFO2      (L1_Si2151_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[8] = {0}; // Fix coverity-59359
    api->rsp->part_info2.STATUS = api->status;

    SiTRACE("Si2151 PART_INFO2 ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2151_PART_INFO2_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing PART_INFO2 bytes!\n");
      return ERROR_Si2151_SENDING_COMMAND;
    }

    error_code = Si2151_pollForResponse(api, 8, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling PART_INFO2 response\n");
      return error_code;
    }

    api->rsp->part_info2.romid    = Si2151_convert_to_byte  (&rspByteBuffer[ 1] , Si2151_PART_INFO2_RESPONSE_ROMID_LSB     , Si2151_PART_INFO2_RESPONSE_ROMID_MASK    );
    api->rsp->part_info2.part2    = Si2151_convert_to_byte  (&rspByteBuffer[ 2] , Si2151_PART_INFO2_RESPONSE_PART2_LSB     , Si2151_PART_INFO2_RESPONSE_PART2_MASK    );
    api->rsp->part_info2.reserved = Si2151_convert_to_byte  (&rspByteBuffer[ 3] , Si2151_PART_INFO2_RESPONSE_RESERVED_LSB  , Si2151_PART_INFO2_RESPONSE_RESERVED_MASK );
    api->rsp->part_info2.serial   = Si2151_convert_to_ulong (&rspByteBuffer[ 4] , Si2151_PART_INFO2_RESPONSE_SERIAL_LSB    , Si2151_PART_INFO2_RESPONSE_SERIAL_MASK   );

    return NO_Si2151_ERROR;
}
#endif /* Si2151_PART_INFO2_CMD */
#ifdef    Si2151_POWER_DOWN_HW_CMD
/*---------------------------------------------------*/
/* Si2151_POWER_DOWN_HW COMMAND                       */
/*---------------------------------------------------*/
unsigned char Si2151_L1_POWER_DOWN_HW   (L1_Si2151_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   pdb_xo_osc,
                                         unsigned char   reserved1,
                                         unsigned char   en_xout,
                                         unsigned char   reserved2,
                                         unsigned char   reserved3,
                                         unsigned char   reserved4,
                                         unsigned char   reserved5,
                                         unsigned char   reserved6,
                                         unsigned char   reserved7,
                                         unsigned char   reserved8,
                                         unsigned char   reserved9)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[10];
    api->rsp->power_down_hw.STATUS = api->status;

    SiTRACE("Si2151 POWER_DOWN_HW ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode   > Si2151_POWER_DOWN_HW_CMD_SUBCODE_MAX  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "  , subcode   );
    if ((pdb_xo_osc > Si2151_POWER_DOWN_HW_CMD_PDB_XO_OSC_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("PDB_XO_OSC %d ", pdb_xo_osc );
    if ((reserved1 > Si2151_POWER_DOWN_HW_CMD_RESERVED1_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED1 %d ", reserved1 );
    if ((en_xout   > Si2151_POWER_DOWN_HW_CMD_EN_XOUT_MAX  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("EN_XOUT %d "  , en_xout   );
    if ((reserved2 > Si2151_POWER_DOWN_HW_CMD_RESERVED2_MAX)  || (reserved2 < Si2151_POWER_DOWN_HW_CMD_RESERVED2_MIN) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED2 %d ", reserved2 );
    if ((reserved3 > Si2151_POWER_DOWN_HW_CMD_RESERVED3_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED3 %d ", reserved3 );
    if ((reserved4  > Si2151_POWER_DOWN_HW_CMD_RESERVED4_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED4 %d " , reserved4  );
    if ((reserved5  > Si2151_POWER_DOWN_HW_CMD_RESERVED5_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED5 %d " , reserved5  );
    if ((reserved6 > Si2151_POWER_DOWN_HW_CMD_RESERVED6_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED6 %d ", reserved6 );
    if ((reserved7 > Si2151_POWER_DOWN_HW_CMD_RESERVED7_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED7 %d ", reserved7 );
    if ((reserved8 > Si2151_POWER_DOWN_HW_CMD_RESERVED8_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED8 %d ", reserved8 );
    if ((reserved9  > Si2151_POWER_DOWN_HW_CMD_RESERVED9_MAX ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED9 %d " , reserved9  );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2151_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2151_POWER_DOWN_HW_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode   & Si2151_POWER_DOWN_HW_CMD_SUBCODE_MASK   ) << Si2151_POWER_DOWN_HW_CMD_SUBCODE_LSB  );
    cmdByteBuffer[2] = (unsigned char) ( ( pdb_xo_osc & Si2151_POWER_DOWN_HW_CMD_PDB_XO_OSC_MASK ) << Si2151_POWER_DOWN_HW_CMD_PDB_XO_OSC_LSB|
                                         ( reserved1 & Si2151_POWER_DOWN_HW_CMD_RESERVED1_MASK ) << Si2151_POWER_DOWN_HW_CMD_RESERVED1_LSB|
                                         ( en_xout   & Si2151_POWER_DOWN_HW_CMD_EN_XOUT_MASK   ) << Si2151_POWER_DOWN_HW_CMD_EN_XOUT_LSB  |
                                         ( reserved2 & Si2151_POWER_DOWN_HW_CMD_RESERVED2_MASK ) << Si2151_POWER_DOWN_HW_CMD_RESERVED2_LSB);
    cmdByteBuffer[3] = (unsigned char) ( ( reserved3  & Si2151_POWER_DOWN_HW_CMD_RESERVED3_MASK  ) << Si2151_POWER_DOWN_HW_CMD_RESERVED3_LSB );
    cmdByteBuffer[4] = (unsigned char) ( ( reserved4  & Si2151_POWER_DOWN_HW_CMD_RESERVED4_MASK  ) << Si2151_POWER_DOWN_HW_CMD_RESERVED4_LSB );
    cmdByteBuffer[5] = (unsigned char) ( ( reserved5  & Si2151_POWER_DOWN_HW_CMD_RESERVED5_MASK  ) << Si2151_POWER_DOWN_HW_CMD_RESERVED5_LSB );
    cmdByteBuffer[6] = (unsigned char) ( ( reserved6  & Si2151_POWER_DOWN_HW_CMD_RESERVED6_MASK  ) << Si2151_POWER_DOWN_HW_CMD_RESERVED6_LSB );
    cmdByteBuffer[7] = (unsigned char) ( ( reserved7  & Si2151_POWER_DOWN_HW_CMD_RESERVED7_MASK  ) << Si2151_POWER_DOWN_HW_CMD_RESERVED7_LSB );
    cmdByteBuffer[8] = (unsigned char) ( ( reserved8  & Si2151_POWER_DOWN_HW_CMD_RESERVED8_MASK  ) << Si2151_POWER_DOWN_HW_CMD_RESERVED8_LSB );
    cmdByteBuffer[9] = (unsigned char) ( ( reserved9  & Si2151_POWER_DOWN_HW_CMD_RESERVED9_MASK  ) << Si2151_POWER_DOWN_HW_CMD_RESERVED9_LSB );

    if (L0_WriteCommandBytes(api->i2c, 10, cmdByteBuffer) != 10) {
      SiTRACE("Error writing POWER_DOWN_HW bytes!\n");
      return ERROR_Si2151_SENDING_COMMAND;
    }

    error_code = Si2151_pollForResetState(api);
    if (error_code) {
      SiTRACE("Error polling POWER_DOWN_HW reset state\n");
      return error_code;
    }
    return NO_Si2151_ERROR;
}
#endif /* Si2151_POWER_DOWN_HW_CMD */
#ifdef    Si2151_POWER_UP_CMD
/*---------------------------------------------------*/
/* Si2151_POWER_UP COMMAND                                 */
/*---------------------------------------------------*/
unsigned char Si2151_L1_POWER_UP        (L1_Si2151_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   clock_mode,
                                         unsigned char   en_xout,
                                         unsigned char   config_1p8v,
                                         unsigned char   reserved3,
                                         unsigned char   reserved4,
                                         unsigned char   reserved5,
                                         unsigned char   reserved6,
                                         unsigned char   reserved7,
                                         unsigned char   reserved8)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[10];
    unsigned char rspByteBuffer[1];
    api->rsp->power_up.STATUS = api->status;

    SiTRACE("Si2151 POWER_UP ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode     > Si2151_POWER_UP_CMD_SUBCODE_MAX    ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "    , subcode     );
    if ((clock_mode  > Si2151_POWER_UP_CMD_CLOCK_MODE_MAX )  || (clock_mode  < Si2151_POWER_UP_CMD_CLOCK_MODE_MIN ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CLOCK_MODE %d " , clock_mode  );
    if ((en_xout     > Si2151_POWER_UP_CMD_EN_XOUT_MAX    ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("EN_XOUT %d "    , en_xout     );
    if ((config_1p8v > Si2151_POWER_UP_CMD_CONFIG_1P8V_MAX)  || (config_1p8v < Si2151_POWER_UP_CMD_CONFIG_1P8V_MIN) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CONFIG_1P8V %d ", config_1p8v );
    if ((reserved3   > Si2151_POWER_UP_CMD_RESERVED3_MAX  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED3 %d "  , reserved3   );
    if ((reserved4   > Si2151_POWER_UP_CMD_RESERVED4_MAX  )  || (reserved4   < Si2151_POWER_UP_CMD_RESERVED4_MIN  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED4 %d "  , reserved4   );
    if ((reserved5   > Si2151_POWER_UP_CMD_RESERVED5_MAX  )  || (reserved5   < Si2151_POWER_UP_CMD_RESERVED5_MIN  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED5 %d "  , reserved5   );
    if ((reserved6   > Si2151_POWER_UP_CMD_RESERVED6_MAX  )  || (reserved6   < Si2151_POWER_UP_CMD_RESERVED6_MIN  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED6 %d "  , reserved6   );
    if ((reserved7   > Si2151_POWER_UP_CMD_RESERVED7_MAX  )  || (reserved7   < Si2151_POWER_UP_CMD_RESERVED7_MIN  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED7 %d "  , reserved7   );
    if ((reserved8   > Si2151_POWER_UP_CMD_RESERVED8_MAX  )  || (reserved8   < Si2151_POWER_UP_CMD_RESERVED8_MIN  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED8 %d "  , reserved8   );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2151_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2151_POWER_UP_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode     & Si2151_POWER_UP_CMD_SUBCODE_MASK     ) << Si2151_POWER_UP_CMD_SUBCODE_LSB    );
    cmdByteBuffer[2] = (unsigned char) ( ( clock_mode  & Si2151_POWER_UP_CMD_CLOCK_MODE_MASK  ) << Si2151_POWER_UP_CMD_CLOCK_MODE_LSB |
                                         ( en_xout     & Si2151_POWER_UP_CMD_EN_XOUT_MASK     ) << Si2151_POWER_UP_CMD_EN_XOUT_LSB    );
    cmdByteBuffer[3] = (unsigned char) ( ( config_1p8v & Si2151_POWER_UP_CMD_CONFIG_1P8V_MASK ) << Si2151_POWER_UP_CMD_CONFIG_1P8V_LSB);
    cmdByteBuffer[4] = (unsigned char) ( ( reserved3   & Si2151_POWER_UP_CMD_RESERVED3_MASK   ) << Si2151_POWER_UP_CMD_RESERVED3_LSB  );
    cmdByteBuffer[5] = (unsigned char) ( ( reserved4   & Si2151_POWER_UP_CMD_RESERVED4_MASK   ) << Si2151_POWER_UP_CMD_RESERVED4_LSB  );
    cmdByteBuffer[6] = (unsigned char) ( ( reserved5   & Si2151_POWER_UP_CMD_RESERVED5_MASK   ) << Si2151_POWER_UP_CMD_RESERVED5_LSB  );
    cmdByteBuffer[7] = (unsigned char) ( ( reserved6   & Si2151_POWER_UP_CMD_RESERVED6_MASK   ) << Si2151_POWER_UP_CMD_RESERVED6_LSB  );
    cmdByteBuffer[8] = (unsigned char) ( ( reserved7   & Si2151_POWER_UP_CMD_RESERVED7_MASK   ) << Si2151_POWER_UP_CMD_RESERVED7_LSB  );
    cmdByteBuffer[9] = (unsigned char) ( ( reserved8   & Si2151_POWER_UP_CMD_RESERVED8_MASK   ) << Si2151_POWER_UP_CMD_RESERVED8_LSB  );

    if (L0_WriteCommandBytes(api->i2c, 10, cmdByteBuffer) != 10) {
      SiTRACE("Error writing POWER_UP bytes!\n");
      return ERROR_Si2151_SENDING_COMMAND;
    }

    error_code = Si2151_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling POWER_UP response\n");
      return error_code;
    }


    return NO_Si2151_ERROR;
}
#endif /* Si2151_POWER_UP_CMD */
#ifdef    Si2151_REREAD_REPLY_CMD
/*---------------------------------------------------*/
/* Si2151_REREAD_REPLY COMMAND                         */
/*---------------------------------------------------*/
unsigned char Si2151_L1_REREAD_REPLY    (L1_Si2151_Context *api,
                                         unsigned char   offset)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[16] = {0}; // Fix coverity-59360
    api->rsp->reread_reply.STATUS = api->status;

    SiTRACE("Si2151 REREAD_REPLY ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((offset > Si2151_REREAD_REPLY_CMD_OFFSET_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("OFFSET %d ", offset );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2151_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2151_REREAD_REPLY_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( offset & Si2151_REREAD_REPLY_CMD_OFFSET_MASK ) << Si2151_REREAD_REPLY_CMD_OFFSET_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing REREAD_REPLY bytes!\n");
      return ERROR_Si2151_SENDING_COMMAND;
    }

    error_code = Si2151_pollForResponse(api, 16, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling REREAD_REPLY response\n");
      return error_code;
    }

    api->rsp->reread_reply.reply1  = Si2151_convert_to_byte  (&rspByteBuffer[ 1] , Si2151_REREAD_REPLY_RESPONSE_REPLY1_LSB   , Si2151_REREAD_REPLY_RESPONSE_REPLY1_MASK  );
    api->rsp->reread_reply.reply2  = Si2151_convert_to_byte  (&rspByteBuffer[ 2] , Si2151_REREAD_REPLY_RESPONSE_REPLY2_LSB   , Si2151_REREAD_REPLY_RESPONSE_REPLY2_MASK  );
    api->rsp->reread_reply.reply3  = Si2151_convert_to_byte  (&rspByteBuffer[ 3] , Si2151_REREAD_REPLY_RESPONSE_REPLY3_LSB   , Si2151_REREAD_REPLY_RESPONSE_REPLY3_MASK  );
    api->rsp->reread_reply.reply4  = Si2151_convert_to_byte  (&rspByteBuffer[ 4] , Si2151_REREAD_REPLY_RESPONSE_REPLY4_LSB   , Si2151_REREAD_REPLY_RESPONSE_REPLY4_MASK  );
    api->rsp->reread_reply.reply5  = Si2151_convert_to_byte  (&rspByteBuffer[ 5] , Si2151_REREAD_REPLY_RESPONSE_REPLY5_LSB   , Si2151_REREAD_REPLY_RESPONSE_REPLY5_MASK  );
    api->rsp->reread_reply.reply6  = Si2151_convert_to_byte  (&rspByteBuffer[ 6] , Si2151_REREAD_REPLY_RESPONSE_REPLY6_LSB   , Si2151_REREAD_REPLY_RESPONSE_REPLY6_MASK  );
    api->rsp->reread_reply.reply7  = Si2151_convert_to_byte  (&rspByteBuffer[ 7] , Si2151_REREAD_REPLY_RESPONSE_REPLY7_LSB   , Si2151_REREAD_REPLY_RESPONSE_REPLY7_MASK  );
    api->rsp->reread_reply.reply8  = Si2151_convert_to_byte  (&rspByteBuffer[ 8] , Si2151_REREAD_REPLY_RESPONSE_REPLY8_LSB   , Si2151_REREAD_REPLY_RESPONSE_REPLY8_MASK  );
    api->rsp->reread_reply.reply9  = Si2151_convert_to_byte  (&rspByteBuffer[ 9] , Si2151_REREAD_REPLY_RESPONSE_REPLY9_LSB   , Si2151_REREAD_REPLY_RESPONSE_REPLY9_MASK  );
    api->rsp->reread_reply.reply10 = Si2151_convert_to_byte  (&rspByteBuffer[10] , Si2151_REREAD_REPLY_RESPONSE_REPLY10_LSB  , Si2151_REREAD_REPLY_RESPONSE_REPLY10_MASK );
    api->rsp->reread_reply.reply11 = Si2151_convert_to_byte  (&rspByteBuffer[11] , Si2151_REREAD_REPLY_RESPONSE_REPLY11_LSB  , Si2151_REREAD_REPLY_RESPONSE_REPLY11_MASK );
    api->rsp->reread_reply.reply12 = Si2151_convert_to_byte  (&rspByteBuffer[12] , Si2151_REREAD_REPLY_RESPONSE_REPLY12_LSB  , Si2151_REREAD_REPLY_RESPONSE_REPLY12_MASK );
    api->rsp->reread_reply.reply13 = Si2151_convert_to_byte  (&rspByteBuffer[13] , Si2151_REREAD_REPLY_RESPONSE_REPLY13_LSB  , Si2151_REREAD_REPLY_RESPONSE_REPLY13_MASK );
    api->rsp->reread_reply.reply14 = Si2151_convert_to_byte  (&rspByteBuffer[14] , Si2151_REREAD_REPLY_RESPONSE_REPLY14_LSB  , Si2151_REREAD_REPLY_RESPONSE_REPLY14_MASK );
    api->rsp->reread_reply.reply15 = Si2151_convert_to_byte  (&rspByteBuffer[15] , Si2151_REREAD_REPLY_RESPONSE_REPLY15_LSB  , Si2151_REREAD_REPLY_RESPONSE_REPLY15_MASK );

    return NO_Si2151_ERROR;
}
#endif /* Si2151_REREAD_REPLY_CMD */
#ifdef    Si2151_RESET_HW_CMD
/*---------------------------------------------------*/
/* Si2151_RESET_HW COMMAND                                 */
/*---------------------------------------------------*/
unsigned char Si2151_L1_RESET_HW        (L1_Si2151_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   reserved1,
                                         unsigned char   reserved2)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[4];
    api->rsp->reset_hw.STATUS = api->status;

    SiTRACE("Si2151 RESET_HW ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode   > Si2151_RESET_HW_CMD_SUBCODE_MAX  )  || (subcode   < Si2151_RESET_HW_CMD_SUBCODE_MIN  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "  , subcode   );
    if ((reserved1 > Si2151_RESET_HW_CMD_RESERVED1_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED1 %d ", reserved1 );
    if ((reserved2 > Si2151_RESET_HW_CMD_RESERVED2_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED2 %d ", reserved2 );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2151_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2151_RESET_HW_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode   & Si2151_RESET_HW_CMD_SUBCODE_MASK   ) << Si2151_RESET_HW_CMD_SUBCODE_LSB  );
    cmdByteBuffer[2] = (unsigned char) ( ( reserved1 & Si2151_RESET_HW_CMD_RESERVED1_MASK ) << Si2151_RESET_HW_CMD_RESERVED1_LSB);
    cmdByteBuffer[3] = (unsigned char) ( ( reserved2 & Si2151_RESET_HW_CMD_RESERVED2_MASK ) << Si2151_RESET_HW_CMD_RESERVED2_LSB);

    if (L0_WriteCommandBytes(api->i2c, 4, cmdByteBuffer) != 4) {
      SiTRACE("Error writing RESET_HW bytes!\n");
      return ERROR_Si2151_SENDING_COMMAND;
    }
    error_code = Si2151_pollForResetState(api);
    if (error_code) {
      SiTRACE("Error polling RESET_HW response\n");
      return error_code;
    }

    return NO_Si2151_ERROR;
}
#endif /* Si2151_RESET_HW_CMD */
#ifdef    Si2151_SET_PROPERTY_CMD
/*---------------------------------------------------*/
/* Si2151_SET_PROPERTY COMMAND                         */
/*---------------------------------------------------*/
unsigned char Si2151_L1_SET_PROPERTY    (L1_Si2151_Context *api,
                                         unsigned char   reserved,
                                         unsigned int    prop,
                                         unsigned int    data)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[6];
    unsigned char rspByteBuffer[4] = {0}; // Fix coverity-59362
    unsigned int shadowData = 0; // Fix coverity-59361
    unsigned char res;
    api->rsp->set_property.STATUS = api->status;

    res = Si2151_PackProperty(api->propShadow, prop, (int *) &shadowData);

    SiTRACE("Si2151 SET_PROPERTY ");
  #ifdef   DEBUG_RANGE_CHECK
    SiTRACE("RESERVED %d ", reserved );
    SiTRACE("PROP %d "    , prop     );
    SiTRACE("DATA %d "    , data     );
  #endif /* DEBUG_RANGE_CHECK */
    if ((data != shadowData)  || (api->propertyWriteMode == DOWNLOAD_ALWAYS) || (res== ERROR_Si2151_UNKNOWN_PROPERTY) )
    {
        SiTRACE("\n");
        cmdByteBuffer[0] = Si2151_SET_PROPERTY_CMD;
        cmdByteBuffer[1] = (unsigned char) ( ( reserved & Si2151_SET_PROPERTY_CMD_RESERVED_MASK ) << Si2151_SET_PROPERTY_CMD_RESERVED_LSB);
        cmdByteBuffer[2] = (unsigned char) ( ( prop     & Si2151_SET_PROPERTY_CMD_PROP_MASK     ) << Si2151_SET_PROPERTY_CMD_PROP_LSB    );
        cmdByteBuffer[3] = (unsigned char) ((( prop     & Si2151_SET_PROPERTY_CMD_PROP_MASK     ) << Si2151_SET_PROPERTY_CMD_PROP_LSB    )>>8);
        cmdByteBuffer[4] = (unsigned char) ( ( data     & Si2151_SET_PROPERTY_CMD_DATA_MASK     ) << Si2151_SET_PROPERTY_CMD_DATA_LSB    );
        cmdByteBuffer[5] = (unsigned char) ((( data     & Si2151_SET_PROPERTY_CMD_DATA_MASK     ) << Si2151_SET_PROPERTY_CMD_DATA_LSB    )>>8);

        if (L0_WriteCommandBytes(api->i2c, 6, cmdByteBuffer) != 6) {
          SiTRACE("Error writing SET_PROPERTY bytes!\n");
          return ERROR_Si2151_SENDING_COMMAND;
        }

        error_code = Si2151_pollForResponse(api, 4, rspByteBuffer);
        if (error_code) {
          SiTRACE("Error polling SET_PROPERTY response\n");
          return error_code;
        }

        api->rsp->set_property.reserved = Si2151_convert_to_byte  (&rspByteBuffer[ 1] , Si2151_SET_PROPERTY_RESPONSE_RESERVED_LSB  , Si2151_SET_PROPERTY_RESPONSE_RESERVED_MASK );
        api->rsp->set_property.data     = Si2151_convert_to_uint  (&rspByteBuffer[ 2] , Si2151_SET_PROPERTY_RESPONSE_DATA_LSB      , Si2151_SET_PROPERTY_RESPONSE_DATA_MASK     );
       /* Update propShadow with latest data if correctly set */
        Si2151_UnpackProperty(api->propShadow, prop, data);
    }
    else
    {
        SiTRACE("\nSi2151_L1_SetProperty: Skipping Property Setting 0x%04x because value unchanged 0x%04x\n", prop,data);

    }
    return NO_Si2151_ERROR;
}
#endif /* Si2151_SET_PROPERTY_CMD */
#ifdef    Si2151_STANDBY_CMD
/*---------------------------------------------------*/
/* Si2151_STANDBY COMMAND                                   */
/*---------------------------------------------------*/
unsigned char Si2151_L1_STANDBY         (L1_Si2151_Context *api,
                                         unsigned char   type)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[1];
    api->rsp->standby.STATUS = api->status;

    SiTRACE("Si2151 STANDBY ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((type > Si2151_STANDBY_CMD_TYPE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("TYPE %d ", type );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2151_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2151_STANDBY_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( type & Si2151_STANDBY_CMD_TYPE_MASK ) << Si2151_STANDBY_CMD_TYPE_LSB);

    if (L0_WriteCommandBytes(api->i2c, 2, cmdByteBuffer) != 2) {
      SiTRACE("Error writing STANDBY bytes!\n");
      return ERROR_Si2151_SENDING_COMMAND;
    }

    error_code = Si2151_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling STANDBY response\n");
      return error_code;
    }


    return NO_Si2151_ERROR;
}
#endif /* Si2151_STANDBY_CMD */
#ifdef    Si2151_TUNER_STATUS_CMD
/*---------------------------------------------------*/
/* Si2151_TUNER_STATUS COMMAND                         */
/*---------------------------------------------------*/
unsigned char Si2151_L1_TUNER_STATUS    (L1_Si2151_Context *api)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[12] = {0}; // Fix coverity-59363

    api->rsp->tuner_status.STATUS = api->status;

    SiTRACE("Si2151 TUNER_STATUS ");
    SiTRACE("\n");
    cmdByteBuffer[0] = Si2151_TUNER_STATUS_CMD;

    if (L0_WriteCommandBytes(api->i2c, 1, cmdByteBuffer) != 1) {
      SiTRACE("Error writing TUNER_STATUS bytes!\n");
      return ERROR_Si2151_SENDING_COMMAND;
    }

    error_code = Si2151_pollForResponse(api, 12, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling TUNER_STATUS response\n");
      return error_code;
    }

    api->rsp->tuner_status.rsvd1    = Si2151_convert_to_byte  (&rspByteBuffer[ 1] , Si2151_TUNER_STATUS_RESPONSE_RSVD1_LSB     , Si2151_TUNER_STATUS_RESPONSE_RSVD1_MASK    );
    api->rsp->tuner_status.rsvd2    = Si2151_convert_to_byte  (&rspByteBuffer[ 2] , Si2151_TUNER_STATUS_RESPONSE_RSVD2_LSB     , Si2151_TUNER_STATUS_RESPONSE_RSVD2_MASK    );
    api->rsp->tuner_status.rssi     = Si2151_convert_to_byte  (&rspByteBuffer[ 3] , Si2151_TUNER_STATUS_RESPONSE_RSSI_LSB      , Si2151_TUNER_STATUS_RESPONSE_RSSI_MASK     );
    api->rsp->tuner_status.freq     = Si2151_convert_to_ulong (&rspByteBuffer[ 4] , Si2151_TUNER_STATUS_RESPONSE_FREQ_LSB      , Si2151_TUNER_STATUS_RESPONSE_FREQ_MASK     );
    api->rsp->tuner_status.mode     = Si2151_convert_to_byte  (&rspByteBuffer[ 8] , Si2151_TUNER_STATUS_RESPONSE_MODE_LSB      , Si2151_TUNER_STATUS_RESPONSE_MODE_MASK     );
    api->rsp->tuner_status.wb_att_status = Si2151_convert_to_byte  (&rspByteBuffer[ 8] , Si2151_TUNER_STATUS_RESPONSE_WB_ATT_STATUS_LSB  , Si2151_TUNER_STATUS_RESPONSE_WB_ATT_STATUS_MASK );
    api->rsp->tuner_status.vco_code = Si2151_convert_to_int   (&rspByteBuffer[10] , Si2151_TUNER_STATUS_RESPONSE_VCO_CODE_LSB  , Si2151_TUNER_STATUS_RESPONSE_VCO_CODE_MASK );

    return NO_Si2151_ERROR;
}
#endif /* Si2151_TUNER_STATUS_CMD */
#ifdef    Si2151_TUNER_TUNE_FREQ_CMD
/*---------------------------------------------------*/
/* Si2151_TUNER_TUNE_FREQ COMMAND                   */
/*---------------------------------------------------*/
unsigned char Si2151_L1_TUNER_TUNE_FREQ (L1_Si2151_Context *api,
                                         unsigned char   mode,
                                         unsigned long   freq)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[8];
    unsigned char rspByteBuffer[1];
    api->rsp->tuner_tune_freq.STATUS = api->status;

    SiTRACE("Si2151 TUNER_TUNE_FREQ ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((mode > Si2151_TUNER_TUNE_FREQ_CMD_MODE_MAX) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("MODE %d ", mode );
    if ((freq > Si2151_TUNER_TUNE_FREQ_CMD_FREQ_MAX)  || (freq < Si2151_TUNER_TUNE_FREQ_CMD_FREQ_MIN) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FREQ %d ", freq );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2151_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2151_TUNER_TUNE_FREQ_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( mode & Si2151_TUNER_TUNE_FREQ_CMD_MODE_MASK ) << Si2151_TUNER_TUNE_FREQ_CMD_MODE_LSB);
    cmdByteBuffer[2] = (unsigned char)0x00;
    cmdByteBuffer[3] = (unsigned char)0x00;
    cmdByteBuffer[4] = (unsigned char) ( ( freq & Si2151_TUNER_TUNE_FREQ_CMD_FREQ_MASK ) << Si2151_TUNER_TUNE_FREQ_CMD_FREQ_LSB);
    cmdByteBuffer[5] = (unsigned char) ((( freq & Si2151_TUNER_TUNE_FREQ_CMD_FREQ_MASK ) << Si2151_TUNER_TUNE_FREQ_CMD_FREQ_LSB)>>8);
    cmdByteBuffer[6] = (unsigned char) ((( freq & Si2151_TUNER_TUNE_FREQ_CMD_FREQ_MASK ) << Si2151_TUNER_TUNE_FREQ_CMD_FREQ_LSB)>>16);
    cmdByteBuffer[7] = (unsigned char) ((( freq & Si2151_TUNER_TUNE_FREQ_CMD_FREQ_MASK ) << Si2151_TUNER_TUNE_FREQ_CMD_FREQ_LSB)>>24);

    if (L0_WriteCommandBytes(api->i2c, 8, cmdByteBuffer) != 8) {
      SiTRACE("Error writing TUNER_TUNE_FREQ bytes!\n");
      return ERROR_Si2151_SENDING_COMMAND;
    }

    error_code = Si2151_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling TUNER_TUNE_FREQ response\n");
      return error_code;
    }


    return NO_Si2151_ERROR;
}
#endif /* Si2151_TUNER_TUNE_FREQ_CMD */
#ifdef    Si2151_WAKE_UP_CMD
/*---------------------------------------------------*/
/* Si2151_WAKE_UP COMMAND                                   */
/*---------------------------------------------------*/
unsigned char Si2151_L1_WAKE_UP         (L1_Si2151_Context *api,
                                         unsigned char   subcode,
                                         unsigned char   reset,
                                         unsigned char   clock_freq,
                                         unsigned char   reserved9,
                                         unsigned char   func,
                                         unsigned char   wake_up)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[7];
    unsigned char rspByteBuffer[1];
    api->rsp->wake_up.STATUS = api->status;

    SiTRACE("Si2151 WAKE_UP ");
  #ifdef   DEBUG_RANGE_CHECK
    if ((subcode     > Si2151_WAKE_UP_CMD_SUBCODE_MAX    )  || (subcode     < Si2151_WAKE_UP_CMD_SUBCODE_MIN    ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("SUBCODE %d "    , subcode     );
    if ((reset       > Si2151_WAKE_UP_CMD_RESET_MAX      )  || (reset       < Si2151_WAKE_UP_CMD_RESET_MIN      ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESET %d "      , reset       );
    if ((clock_freq  > Si2151_WAKE_UP_CMD_CLOCK_FREQ_MAX )  || (clock_freq  < Si2151_WAKE_UP_CMD_CLOCK_FREQ_MIN ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("CLOCK_FREQ %d " , clock_freq  );
    if ((reserved9   > Si2151_WAKE_UP_CMD_RESERVED9_MAX  ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("RESERVED9 %d "  , reserved9   );
    if ((func        > Si2151_WAKE_UP_CMD_FUNC_MAX       ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("FUNC %d "       , func        );
    if ((wake_up     > Si2151_WAKE_UP_CMD_WAKE_UP_MAX    )  || (wake_up     < Si2151_WAKE_UP_CMD_WAKE_UP_MIN    ) ) {error_code++; SiTRACE("\nOut of range: ");}; SiTRACE("WAKE_UP %d "    , wake_up     );
    if (error_code) {
      SiTRACE("%d out of range parameters\n", error_code);
      return ERROR_Si2151_PARAMETER_OUT_OF_RANGE;
    }
  #endif /* DEBUG_RANGE_CHECK */

    SiTRACE("\n");
    cmdByteBuffer[0] = Si2151_WAKE_UP_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode     & Si2151_WAKE_UP_CMD_SUBCODE_MASK     ) << Si2151_WAKE_UP_CMD_SUBCODE_LSB    );
    cmdByteBuffer[2] = (unsigned char) ( ( reset       & Si2151_WAKE_UP_CMD_RESET_MASK       ) << Si2151_WAKE_UP_CMD_RESET_LSB      );
    cmdByteBuffer[3] = (unsigned char) ( ( clock_freq  & Si2151_WAKE_UP_CMD_CLOCK_FREQ_MASK  ) << Si2151_WAKE_UP_CMD_CLOCK_FREQ_LSB );
    cmdByteBuffer[4] = (unsigned char) ( ( reserved9   & Si2151_WAKE_UP_CMD_RESERVED9_MASK   ) << Si2151_WAKE_UP_CMD_RESERVED9_LSB  );
    cmdByteBuffer[5] = (unsigned char) ( ( func       & Si2151_WAKE_UP_CMD_FUNC_MASK       ) << Si2151_WAKE_UP_CMD_FUNC_LSB         );
    cmdByteBuffer[6] = (unsigned char) ( ( wake_up     & Si2151_WAKE_UP_CMD_WAKE_UP_MASK     ) << Si2151_WAKE_UP_CMD_WAKE_UP_LSB    );

    if (L0_WriteCommandBytes(api->i2c, 7, cmdByteBuffer) != 7) {
      SiTRACE("Error writing WAKE_UP bytes!\n");
      return ERROR_Si2151_SENDING_COMMAND;
    }
    /* wait 5 ms to allow the firmware to start up */
    system_wait(5);
    /* check for CTS only */
    error_code = Si2151_pollForResponse(api, 1, rspByteBuffer);
    if (error_code) {
      SiTRACE("Error polling WAKE_UP response\n");
      return error_code;
    }


    return NO_Si2151_ERROR;
}
#endif /* Si2151_WAKE_UP_CMD */


  /* --------------------------------------------*/
  /* SEND_COMMAND2 FUNCTION                      */
  /* --------------------------------------------*/
unsigned char   Si2151_L1_SendCommand2(L1_Si2151_Context *api, unsigned int cmd_code) {
    switch (cmd_code) {
    #ifdef        Si2151_AGC_OVERRIDE_CMD
     case         Si2151_AGC_OVERRIDE_CMD_CODE:
       return Si2151_L1_AGC_OVERRIDE (api, api->cmd->agc_override.force_max_gain, api->cmd->agc_override.force_top_gain );
     break;
    #endif /*     Si2151_AGC_OVERRIDE_CMD */
    #ifdef        Si2151_ATV_SCAN_TUNE_CMD
     case         Si2151_ATV_SCAN_TUNE_CMD_CODE:
       return Si2151_L1_ATV_SCAN_TUNE (api, api->cmd->atv_scan_tune.freq );
     break;
    #endif /*     Si2151_ATV_SCAN_TUNE_CMD */
    #ifdef        Si2151_CONFIG_CLOCKS_CMD
     case         Si2151_CONFIG_CLOCKS_CMD_CODE:
       return Si2151_L1_CONFIG_CLOCKS (api, api->cmd->config_clocks.subcode, api->cmd->config_clocks.clock_mode, api->cmd->config_clocks.en_xout );
     break;
    #endif /*     Si2151_CONFIG_CLOCKS_CMD */
    #ifdef        Si2151_CONFIG_I2C_CMD
     case         Si2151_CONFIG_I2C_CMD_CODE:
       return Si2151_L1_CONFIG_I2C (api, api->cmd->config_i2c.subcode, api->cmd->config_i2c.i2c_broadcast );
     break;
    #endif /*     Si2151_CONFIG_I2C_CMD */
    #ifdef        Si2151_CONFIG_PINS_CMD
     case         Si2151_CONFIG_PINS_CMD_CODE:
       return Si2151_L1_CONFIG_PINS (api, api->cmd->config_pins.gpio1_mode, api->cmd->config_pins.gpio1_read, api->cmd->config_pins.gpio2_mode, api->cmd->config_pins.gpio2_read, api->cmd->config_pins.agc1_mode, api->cmd->config_pins.agc1_read, api->cmd->config_pins.agc2_mode, api->cmd->config_pins.agc2_read, api->cmd->config_pins.xout_mode );
     break;
    #endif /*     Si2151_CONFIG_PINS_CMD */
    #ifdef        Si2151_EXIT_BOOTLOADER_CMD
     case         Si2151_EXIT_BOOTLOADER_CMD_CODE:
       return Si2151_L1_EXIT_BOOTLOADER (api, api->cmd->exit_bootloader.func, api->cmd->exit_bootloader.ctsien );
     break;
    #endif /*     Si2151_EXIT_BOOTLOADER_CMD */
    #ifdef        Si2151_FINE_TUNE_CMD
     case         Si2151_FINE_TUNE_CMD_CODE:
       return Si2151_L1_FINE_TUNE (api, api->cmd->fine_tune.persistence, api->cmd->fine_tune.offset_500hz );
     break;
    #endif /*     Si2151_FINE_TUNE_CMD */
    #ifdef        Si2151_GET_PROPERTY_CMD
     case         Si2151_GET_PROPERTY_CMD_CODE:
       return Si2151_L1_GET_PROPERTY (api, api->cmd->get_property.reserved, api->cmd->get_property.prop );
     break;
    #endif /*     Si2151_GET_PROPERTY_CMD */
    #ifdef        Si2151_GET_REV_CMD
     case         Si2151_GET_REV_CMD_CODE:
       return Si2151_L1_GET_REV (api );
     break;
    #endif /*     Si2151_GET_REV_CMD */
    #ifdef        Si2151_PART_INFO_CMD
     case         Si2151_PART_INFO_CMD_CODE:
       return Si2151_L1_PART_INFO (api );
     break;
    #endif /*     Si2151_PART_INFO_CMD */
    #ifdef        Si2151_PART_INFO2_CMD
     case         Si2151_PART_INFO2_CMD_CODE:
       return Si2151_L1_PART_INFO2 (api );
     break;
    #endif /*     Si2151_PART_INFO2_CMD */
    #ifdef        Si2151_POWER_DOWN_HW_CMD
     case         Si2151_POWER_DOWN_HW_CMD_CODE:
       return Si2151_L1_POWER_DOWN_HW (api, api->cmd->power_down_hw.subcode, api->cmd->power_down_hw.pdb_xo_osc, api->cmd->power_down_hw.reserved1, api->cmd->power_down_hw.en_xout, api->cmd->power_down_hw.reserved2, api->cmd->power_down_hw.reserved3, api->cmd->power_down_hw.reserved4, api->cmd->power_down_hw.reserved5, api->cmd->power_down_hw.reserved6, api->cmd->power_down_hw.reserved7, api->cmd->power_down_hw.reserved8, api->cmd->power_down_hw.reserved9 );
     break;
    #endif /*     Si2151_POWER_DOWN_HW_CMD */
    #ifdef        Si2151_POWER_UP_CMD
     case         Si2151_POWER_UP_CMD_CODE:
       return Si2151_L1_POWER_UP (api, api->cmd->power_up.subcode, api->cmd->power_up.clock_mode, api->cmd->power_up.en_xout, api->cmd->power_up.config_1p8v, api->cmd->power_up.reserved3, api->cmd->power_up.reserved4, api->cmd->power_up.reserved5, api->cmd->power_up.reserved6, api->cmd->power_up.reserved7, api->cmd->power_up.reserved8 );
     break;
    #endif /*     Si2151_POWER_UP_CMD */
    #ifdef        Si2151_REREAD_REPLY_CMD
     case         Si2151_REREAD_REPLY_CMD_CODE:
       return Si2151_L1_REREAD_REPLY (api, api->cmd->reread_reply.offset );
     break;
    #endif /*     Si2151_REREAD_REPLY_CMD */
    #ifdef        Si2151_RESET_HW_CMD
     case         Si2151_RESET_HW_CMD_CODE:
       return Si2151_L1_RESET_HW (api, api->cmd->reset_hw.subcode, api->cmd->reset_hw.reserved1, api->cmd->reset_hw.reserved2 );
     break;
    #endif /*     Si2151_RESET_HW_CMD */
    #ifdef        Si2151_SET_PROPERTY_CMD
     case         Si2151_SET_PROPERTY_CMD_CODE:
       return Si2151_L1_SET_PROPERTY (api, api->cmd->set_property.reserved, api->cmd->set_property.prop, api->cmd->set_property.data );
     break;
    #endif /*     Si2151_SET_PROPERTY_CMD */
    #ifdef        Si2151_STANDBY_CMD
     case         Si2151_STANDBY_CMD_CODE:
       return Si2151_L1_STANDBY (api, api->cmd->standby.type );
     break;
    #endif /*     Si2151_STANDBY_CMD */
    #ifdef        Si2151_TUNER_STATUS_CMD
     case         Si2151_TUNER_STATUS_CMD_CODE:
       return Si2151_L1_TUNER_STATUS (api );
     break;
    #endif /*     Si2151_TUNER_STATUS_CMD */
    #ifdef        Si2151_TUNER_TUNE_FREQ_CMD
     case         Si2151_TUNER_TUNE_FREQ_CMD_CODE:
       return Si2151_L1_TUNER_TUNE_FREQ (api, api->cmd->tuner_tune_freq.mode, api->cmd->tuner_tune_freq.freq );
     break;
    #endif /*     Si2151_TUNER_TUNE_FREQ_CMD */
    #ifdef        Si2151_WAKE_UP_CMD
     case         Si2151_WAKE_UP_CMD_CODE:
       return Si2151_L1_WAKE_UP (api, api->cmd->wake_up.subcode, api->cmd->wake_up.reset, api->cmd->wake_up.clock_freq, api->cmd->wake_up.reserved9, api->cmd->wake_up.func, api->cmd->wake_up.wake_up );
     break;
    #endif /*     Si2151_WAKE_UP_CMD */
   default : break;
    }
     return 0;
  }

#ifdef    Si2151_GET_COMMAND_STRINGS

  /* --------------------------------------------*/
  /* GET_COMMAND_RESPONSE_STRING FUNCTION        */
  /* --------------------------------------------*/
unsigned char   Si2151_L1_GetCommandResponseString(L1_Si2151_Context *api, unsigned int cmd_code, const char *separator, char *msg) {
    switch (cmd_code) {
    #ifdef        Si2151_AGC_OVERRIDE_CMD
     case         Si2151_AGC_OVERRIDE_CMD_CODE:
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
    #endif /*     Si2151_AGC_OVERRIDE_CMD */

    #ifdef        Si2151_ATV_SCAN_TUNE_CMD
     case         Si2151_ATV_SCAN_TUNE_CMD_CODE:
      sprintf(msg,"ATV_SCAN_TUNE ");
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TUNINT ");
           if  (api->rsp->atv_scan_tune.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->atv_scan_tune.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                      sprintf(msg,"%s%d", msg, api->rsp->atv_scan_tune.STATUS->tunint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ATVINT ");
           if  (api->rsp->atv_scan_tune.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->atv_scan_tune.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                      sprintf(msg,"%s%d", msg, api->rsp->atv_scan_tune.STATUS->atvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DTVINT ");
           if  (api->rsp->atv_scan_tune.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->atv_scan_tune.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                      sprintf(msg,"%s%d", msg, api->rsp->atv_scan_tune.STATUS->dtvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ERR    ");
           if  (api->rsp->atv_scan_tune.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->atv_scan_tune.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                      sprintf(msg,"%s%d", msg, api->rsp->atv_scan_tune.STATUS->err);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CTS    ");
           if  (api->rsp->atv_scan_tune.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->atv_scan_tune.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                      sprintf(msg,"%s%d", msg, api->rsp->atv_scan_tune.STATUS->cts);
     break;
    #endif /*     Si2151_ATV_SCAN_TUNE_CMD */

    #ifdef        Si2151_CONFIG_CLOCKS_CMD
     case         Si2151_CONFIG_CLOCKS_CMD_CODE:
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
    #endif /*     Si2151_CONFIG_CLOCKS_CMD */

    #ifdef        Si2151_CONFIG_I2C_CMD
     case         Si2151_CONFIG_I2C_CMD_CODE:
      sprintf(msg,"CONFIG_I2C ");
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TUNINT ");
           if  (api->rsp->config_i2c.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->config_i2c.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                   sprintf(msg,"%s%d", msg, api->rsp->config_i2c.STATUS->tunint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ATVINT ");
           if  (api->rsp->config_i2c.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->config_i2c.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                   sprintf(msg,"%s%d", msg, api->rsp->config_i2c.STATUS->atvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DTVINT ");
           if  (api->rsp->config_i2c.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->config_i2c.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                   sprintf(msg,"%s%d", msg, api->rsp->config_i2c.STATUS->dtvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ERR    ");
           if  (api->rsp->config_i2c.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->config_i2c.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                   sprintf(msg,"%s%d", msg, api->rsp->config_i2c.STATUS->err);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CTS    ");
           if  (api->rsp->config_i2c.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->config_i2c.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                   sprintf(msg,"%s%d", msg, api->rsp->config_i2c.STATUS->cts);
     break;
    #endif /*     Si2151_CONFIG_I2C_CMD */

    #ifdef        Si2151_CONFIG_PINS_CMD
     case         Si2151_CONFIG_PINS_CMD_CODE:
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
           if  (api->rsp->config_pins.gpio1_mode  ==     9) strcat(msg,"ATV_HSYNC_OUT  ");
      else if  (api->rsp->config_pins.gpio1_mode  ==     1) strcat(msg,"DISABLE        ");
      else if  (api->rsp->config_pins.gpio1_mode  ==     2) strcat(msg,"DRIVE_0        ");
      else if  (api->rsp->config_pins.gpio1_mode  ==     3) strcat(msg,"DRIVE_1        ");
      else if  (api->rsp->config_pins.gpio1_mode  ==     7) strcat(msg,"DTV_FREEZE_HIGH");
      else if  (api->rsp->config_pins.gpio1_mode  ==     8) strcat(msg,"DTV_FREEZE_LOW ");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->config_pins.gpio1_mode);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-GPIO1_STATE ");
           if  (api->rsp->config_pins.gpio1_state ==     0) strcat(msg,"READ_0");
      else if  (api->rsp->config_pins.gpio1_state ==     1) strcat(msg,"READ_1");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->config_pins.gpio1_state);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-GPIO2_MODE  ");
           if  (api->rsp->config_pins.gpio2_mode  ==     9) strcat(msg,"ATV_HSYNC_OUT  ");
      else if  (api->rsp->config_pins.gpio2_mode  ==     1) strcat(msg,"DISABLE        ");
      else if  (api->rsp->config_pins.gpio2_mode  ==     2) strcat(msg,"DRIVE_0        ");
      else if  (api->rsp->config_pins.gpio2_mode  ==     3) strcat(msg,"DRIVE_1        ");
      else if  (api->rsp->config_pins.gpio2_mode  ==     7) strcat(msg,"DTV_FREEZE_HIGH");
      else if  (api->rsp->config_pins.gpio2_mode  ==     8) strcat(msg,"DTV_FREEZE_LOW ");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->config_pins.gpio2_mode);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-GPIO2_STATE ");
           if  (api->rsp->config_pins.gpio2_state ==     0) strcat(msg,"READ_0");
      else if  (api->rsp->config_pins.gpio2_state ==     1) strcat(msg,"READ_1");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->config_pins.gpio2_state);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-AGC1_MODE   ");
           if  (api->rsp->config_pins.agc1_mode   ==     4) strcat(msg,"ATV_AGC        ");
      else if  (api->rsp->config_pins.agc1_mode   ==     6) strcat(msg,"ATV_DTV_AGC    ");
      else if  (api->rsp->config_pins.agc1_mode   ==     9) strcat(msg,"ATV_HSYNC_OUT  ");
      else if  (api->rsp->config_pins.agc1_mode   ==     1) strcat(msg,"DISABLE        ");
      else if  (api->rsp->config_pins.agc1_mode   ==     2) strcat(msg,"DRIVE_0        ");
      else if  (api->rsp->config_pins.agc1_mode   ==     3) strcat(msg,"DRIVE_1        ");
      else if  (api->rsp->config_pins.agc1_mode   ==     5) strcat(msg,"DTV_AGC        ");
      else if  (api->rsp->config_pins.agc1_mode   ==     7) strcat(msg,"DTV_FREEZE_HIGH");
      else if  (api->rsp->config_pins.agc1_mode   ==     8) strcat(msg,"DTV_FREEZE_LOW ");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->config_pins.agc1_mode);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-AGC1_STATE  ");
           if  (api->rsp->config_pins.agc1_state  ==     0) strcat(msg,"READ_0");
      else if  (api->rsp->config_pins.agc1_state  ==     1) strcat(msg,"READ_1");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->config_pins.agc1_state);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-AGC2_MODE   ");
           if  (api->rsp->config_pins.agc2_mode   ==     4) strcat(msg,"ATV_AGC        ");
      else if  (api->rsp->config_pins.agc2_mode   ==     6) strcat(msg,"ATV_DTV_AGC    ");
      else if  (api->rsp->config_pins.agc2_mode   ==     1) strcat(msg,"DISABLE        ");
      else if  (api->rsp->config_pins.agc2_mode   ==     5) strcat(msg,"DTV_AGC        ");
      else if  (api->rsp->config_pins.agc2_mode   ==     7) strcat(msg,"DTV_FREEZE_HIGH");
      else if  (api->rsp->config_pins.agc2_mode   ==     8) strcat(msg,"DTV_FREEZE_LOW ");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->config_pins.agc2_mode);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-AGC2_STATE  ");
           if  (api->rsp->config_pins.agc2_state  ==     0) strcat(msg,"READ_0");
      else if  (api->rsp->config_pins.agc2_state  ==     1) strcat(msg,"READ_1");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->config_pins.agc2_state);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-XOUT_MODE   ");
           if  (api->rsp->config_pins.xout_mode   ==     9) strcat(msg,"ATV_HSYNC_OUT");
      else if  (api->rsp->config_pins.xout_mode   ==     1) strcat(msg,"DISABLE      ");
      else if  (api->rsp->config_pins.xout_mode   ==     2) strcat(msg,"DRIVE_0      ");
      else if  (api->rsp->config_pins.xout_mode   ==     3) strcat(msg,"DRIVE_1      ");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->config_pins.xout_mode);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-XOUT_STATE  ");
           if  (api->rsp->config_pins.xout_state  ==     0) strcat(msg,"READ_0");
      else if  (api->rsp->config_pins.xout_state  ==     1) strcat(msg,"READ_1");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->config_pins.xout_state);
     break;
    #endif /*     Si2151_CONFIG_PINS_CMD */

    #ifdef        Si2151_EXIT_BOOTLOADER_CMD
     case         Si2151_EXIT_BOOTLOADER_CMD_CODE:
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
    #endif /*     Si2151_EXIT_BOOTLOADER_CMD */

    #ifdef        Si2151_FINE_TUNE_CMD
     case         Si2151_FINE_TUNE_CMD_CODE:
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
    #endif /*     Si2151_FINE_TUNE_CMD */

    #ifdef        Si2151_GET_PROPERTY_CMD
     case         Si2151_GET_PROPERTY_CMD_CODE:
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
    #endif /*     Si2151_GET_PROPERTY_CMD */

    #ifdef        Si2151_GET_REV_CMD
     case         Si2151_GET_REV_CMD_CODE:
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
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-PN2      "); sprintf(msg,"%s%d", msg, api->rsp->get_rev.pn2);
     break;
    #endif /*     Si2151_GET_REV_CMD */

    #ifdef        Si2151_PART_INFO_CMD
     case         Si2151_PART_INFO_CMD_CODE:
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
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-PART2    "); sprintf(msg,"%s%d", msg, api->rsp->part_info.part2);
     break;
    #endif /*     Si2151_PART_INFO_CMD */

    #ifdef        Si2151_PART_INFO2_CMD
     case         Si2151_PART_INFO2_CMD_CODE:
      sprintf(msg,"PART_INFO2 ");
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TUNINT   ");
           if  (api->rsp->part_info2.STATUS->tunint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->part_info2.STATUS->tunint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->part_info2.STATUS->tunint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ATVINT   ");
           if  (api->rsp->part_info2.STATUS->atvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->part_info2.STATUS->atvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->part_info2.STATUS->atvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DTVINT   ");
           if  (api->rsp->part_info2.STATUS->dtvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->part_info2.STATUS->dtvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->part_info2.STATUS->dtvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ERR      ");
           if  (api->rsp->part_info2.STATUS->err      ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->part_info2.STATUS->err      ==     0) strcat(msg,"NO_ERROR");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->part_info2.STATUS->err);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CTS      ");
           if  (api->rsp->part_info2.STATUS->cts      ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->part_info2.STATUS->cts      ==     0) strcat(msg,"WAIT     ");
      else                                                     sprintf(msg,"%s%d", msg, api->rsp->part_info2.STATUS->cts);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ROMID    "); sprintf(msg,"%s%d", msg, api->rsp->part_info2.romid);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-PART2    "); sprintf(msg,"%s%d", msg, api->rsp->part_info2.part2);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-RESERVED "); sprintf(msg,"%s%d", msg, api->rsp->part_info2.reserved);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-SERIAL   "); sprintf(msg,"%s%ld", msg, api->rsp->part_info2.serial);
     break;
    #endif /*     Si2151_PART_INFO2_CMD */

    #ifdef        Si2151_POWER_DOWN_HW_CMD
     case         Si2151_POWER_DOWN_HW_CMD_CODE:
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
    #endif /*     Si2151_POWER_DOWN_HW_CMD */

    #ifdef        Si2151_POWER_UP_CMD
     case         Si2151_POWER_UP_CMD_CODE:
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
    #endif /*     Si2151_POWER_UP_CMD */

    #ifdef        Si2151_REREAD_REPLY_CMD
     case         Si2151_REREAD_REPLY_CMD_CODE:
      sprintf(msg,"REREAD_REPLY ");
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TUNINT ");
           if  (api->rsp->reread_reply.STATUS->tunint  ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->reread_reply.STATUS->tunint  ==     1) strcat(msg,"TRIGGERED    ");
      else                                                      sprintf(msg,"%s%d", msg, api->rsp->reread_reply.STATUS->tunint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ATVINT ");
           if  (api->rsp->reread_reply.STATUS->atvint  ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->reread_reply.STATUS->atvint  ==     1) strcat(msg,"TRIGGERED    ");
      else                                                      sprintf(msg,"%s%d", msg, api->rsp->reread_reply.STATUS->atvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DTVINT ");
           if  (api->rsp->reread_reply.STATUS->dtvint  ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->reread_reply.STATUS->dtvint  ==     1) strcat(msg,"TRIGGERED    ");
      else                                                      sprintf(msg,"%s%d", msg, api->rsp->reread_reply.STATUS->dtvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ERR    ");
           if  (api->rsp->reread_reply.STATUS->err     ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->reread_reply.STATUS->err     ==     0) strcat(msg,"NO_ERROR");
      else                                                      sprintf(msg,"%s%d", msg, api->rsp->reread_reply.STATUS->err);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CTS    ");
           if  (api->rsp->reread_reply.STATUS->cts     ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->reread_reply.STATUS->cts     ==     0) strcat(msg,"WAIT     ");
      else                                                      sprintf(msg,"%s%d", msg, api->rsp->reread_reply.STATUS->cts);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-REPLY1  "); sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply1);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-REPLY2  "); sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply2);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-REPLY3  "); sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply3);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-REPLY4  "); sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply4);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-REPLY5  "); sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply5);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-REPLY6  "); sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply6);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-REPLY7  "); sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply7);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-REPLY8  "); sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply8);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-REPLY9  "); sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply9);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-REPLY10 "); sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply10);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-REPLY11 "); sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply11);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-REPLY12 "); sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply12);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-REPLY13 "); sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply13);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-REPLY14 "); sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply14);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-REPLY15 "); sprintf(msg,"%s%d", msg, api->rsp->reread_reply.reply15);
     break;
    #endif /*     Si2151_REREAD_REPLY_CMD */

    #ifdef        Si2151_RESET_HW_CMD
     case         Si2151_RESET_HW_CMD_CODE:
      sprintf(msg,"RESET_HW ");
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TUNINT ");
           if  (api->rsp->reset_hw.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->reset_hw.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->reset_hw.STATUS->tunint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ATVINT ");
           if  (api->rsp->reset_hw.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->reset_hw.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->reset_hw.STATUS->atvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DTVINT ");
           if  (api->rsp->reset_hw.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->reset_hw.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->reset_hw.STATUS->dtvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ERR    ");
           if  (api->rsp->reset_hw.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->reset_hw.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->reset_hw.STATUS->err);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CTS    ");
           if  (api->rsp->reset_hw.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->reset_hw.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                 sprintf(msg,"%s%d", msg, api->rsp->reset_hw.STATUS->cts);
     break;
    #endif /*     Si2151_RESET_HW_CMD */

    #ifdef        Si2151_SET_PROPERTY_CMD
     case         Si2151_SET_PROPERTY_CMD_CODE:
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
    #endif /*     Si2151_SET_PROPERTY_CMD */

    #ifdef        Si2151_STANDBY_CMD
     case         Si2151_STANDBY_CMD_CODE:
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
    #endif /*     Si2151_STANDBY_CMD */

    #ifdef        Si2151_TUNER_STATUS_CMD
     case         Si2151_TUNER_STATUS_CMD_CODE:
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
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-RSVD1    "); sprintf(msg,"%s%d", msg, api->rsp->tuner_status.rsvd1);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-RSVD2    "); sprintf(msg,"%s%d", msg, api->rsp->tuner_status.rsvd2);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-RSSI     "); sprintf(msg,"%s%d", msg, api->rsp->tuner_status.rssi);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-FREQ     "); sprintf(msg,"%s%ld", msg, api->rsp->tuner_status.freq);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-MODE     ");
           if  (api->rsp->tuner_status.mode     ==     1) strcat(msg,"ATV");
      else if  (api->rsp->tuner_status.mode     ==     0) strcat(msg,"DTV");
      else                                               sprintf(msg,"%s%d", msg, api->rsp->tuner_status.mode);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-WB_ATT_STATUS ");
           if  (api->rsp->tuner_status.wb_att_status ==     0) strcat(msg,"OFF");
      else if  (api->rsp->tuner_status.wb_att_status ==     1) strcat(msg,"ON ");
      else                                                    sprintf(msg,"%s%d", msg, api->rsp->tuner_status.wb_att_status);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-VCO_CODE "); sprintf(msg,"%s%d", msg, api->rsp->tuner_status.vco_code);
     break;
    #endif /*     Si2151_TUNER_STATUS_CMD */

    #ifdef        Si2151_TUNER_TUNE_FREQ_CMD
     case         Si2151_TUNER_TUNE_FREQ_CMD_CODE:
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
    #endif /*     Si2151_TUNER_TUNE_FREQ_CMD */

    #ifdef        Si2151_WAKE_UP_CMD
     case         Si2151_WAKE_UP_CMD_CODE:
      sprintf(msg,"WAKE_UP ");
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-TUNINT ");
           if  (api->rsp->wake_up.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->wake_up.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                sprintf(msg,"%s%d", msg, api->rsp->wake_up.STATUS->tunint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ATVINT ");
           if  (api->rsp->wake_up.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->wake_up.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                sprintf(msg,"%s%d", msg, api->rsp->wake_up.STATUS->atvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-DTVINT ");
           if  (api->rsp->wake_up.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (api->rsp->wake_up.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                sprintf(msg,"%s%d", msg, api->rsp->wake_up.STATUS->dtvint);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-ERR    ");
           if  (api->rsp->wake_up.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (api->rsp->wake_up.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                sprintf(msg,"%s%d", msg, api->rsp->wake_up.STATUS->err);
       sprintf(msg,"%s%s",msg,separator); strcat(msg,"-CTS    ");
           if  (api->rsp->wake_up.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (api->rsp->wake_up.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                sprintf(msg,"%s%d", msg, api->rsp->wake_up.STATUS->cts);
     break;
    #endif /*     Si2151_WAKE_UP_CMD */

     default : break;
    }
    return 0;
  }
#endif /* Si2151_GET_COMMAND_STRINGS */








