/* Automatically generated from a template on 2011 January 24 at 13:47 */ /*( Processed on PC0009853 (joluers) ) */
/***************************************************************************************/
/* FILE: Si2176_L1_Commands.c                                                          */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/***************************************************************************************/
/*                     Silicon Laboratories Broadcast Si2176 API Layer 1               */
/***************************************************************************************/
#undef Si2176_GET_COMMAND_STRINGS
#define Si2176_COMMAND_PROTOTYPES

//#include "Si2176_Typedefs.h"
#include "Si2176_L1_API_TV_Chassis.h"
#include "Si2176_Commands.h"
#include "Si2176_L0_TV_Chassis.h"
#define   DEBUG_RANGE_CHECK

#ifdef    Si2176_GET_COMMAND_STRINGS
#include <stdio.h>
#endif

Si2176_COMMON_REPLY_struct status;
/***********************************************************************************************************************
  Si2176_CurrentResponseStatus function
  Use:        status checking function
              Used to fill the Si2176_COMMON_REPLY_struct members with the ptDataBuffer byte's bits
  Comments:   The status byte definition being identical for all commands,
              using this function to fill the status structure hels reducing the code size

  Parameter: *ret          the Si2176_COMMON_REPLY_struct
  Parameter: ptDataBuffer  a single byte received when reading a command's response (the first byte)
  Returns:   0 if the err bit (bit 6) is unset, 1 otherwise
 ***********************************************************************************************************************/
 unsigned char  Si2176_CurrentResponseStatus (Si2176_COMMON_REPLY_struct *ret, unsigned char ptDataBuffer) {
/* _status_code_insertion_start */
    ret->tunint = ((ptDataBuffer >> 0 ) & 0x01);
    ret->atvint = ((ptDataBuffer >> 1 ) & 0x01);
    ret->dtvint = ((ptDataBuffer >> 2 ) & 0x01);
    ret->err    = ((ptDataBuffer >> 6 ) & 0x01);
    ret->cts    = ((ptDataBuffer >> 7 ) & 0x01);
/* _status_code_insertion_point */
    return (ret->err ? ERROR_Si2176_ERR : NO_Si2176_ERROR);
}

/***********************************************************************************************************************
  Si2176_pollForCTS function
  Use:        CTS checking function
              Used to check the CTS bit until it is set before sending the next command
  Comments:   The status byte definition being identical for all commands,
              using this function to fill the status structure hels reducing the code size
  Comments:   waitForCTS = 1 => I2C polling
              waitForCTS = 2 => INTB followed by a read (reading a HW byte using the cypress chip)
              max timeout = 100 ms

  Porting:    If reading INTB is not possible, the waitForCTS = 2 case can be removed

  Parameter: waitForCTS          a flag indicating if waiting for CTS is required
  Returns:   1 if the CTS bit is set, 0 otherwise
 ***********************************************************************************************************************/
 unsigned char  Si2176_pollForCTS (L1_Si2176_Context *context, unsigned char waitForCTS) {
    unsigned char error_code;
    unsigned int loop_count;

    unsigned char rspByteBuffer[1];

  for (loop_count=0;loop_count<2000;loop_count++) {   /* wait a maximum of 50*25ms = 1.25s                        */
    switch (waitForCTS) {       /* type of CTS polling?                                     */
    case 0 :              /* no polling? valid option, but shouldn't have been called */
      error_code = NO_Si2176_ERROR;     /* return no error                                          */
      goto exit;

    case 1 :              /* I2C polling status?                                      */
      if (L0_ReadCommandBytes(context->i2c, 1, rspByteBuffer) != 1)
        error_code = ERROR_Si2176_POLLING_CTS;
      else
        error_code = NO_Si2176_ERROR;
        if (error_code || (rspByteBuffer[0] & 0x80))
        goto exit;
      break;

    default :
      error_code = ERROR_Si2176_PARAMETER_OUT_OF_RANGE; /* support debug of invalid CTS poll parameter   */
      goto exit;
    }
    // a delay is not necessary here
    // use I2C duration to set timeout: Start+DevAddr+R/W+Ack+STATUS+ACK+Stop = 20bits => 50us min @ 400kHz/200us min @100kHz

  }
  error_code = ERROR_Si2176_CTS_TIMEOUT;

exit:
   return error_code;
}

/***********************************************************************************************************************
  Si2176_pollForResponse function
  Use:        command response retrieval function
              Used to retrieve the command response in the provided buffer,
              poll for response either by I2C polling or wait for INTB
  Comments:   The status byte definition being identical for all commands,
              using this function to fill the status structure hels reducing the code size
  Comments:   waitForCTS = 1 => I2C polling
              waitForCTS = 2 => INTB followed by a read (reading a HW byte using the cypress chip)
              max timeout = 100 ms

  Porting:    If reading INTB is not possible, the waitForCTS = 2 case can be removed

  Parameter:  waitForResponse  a flag indicating if waiting for the response is required
  Parameter:  nbBytes          the number of response bytes to read
  Parameter:  pByteBuffer      a buffer into which bytes will be stored
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/
 unsigned char  Si2176_pollForResponse (L1_Si2176_Context *context, unsigned char waitForResponse, unsigned int nbBytes, unsigned char *pByteBuffer, Si2176_COMMON_REPLY_struct *status1) {
    unsigned char error_code;
    unsigned int loop_count;

  for (loop_count=0;loop_count<2000;loop_count++) {   /* wait a maximum of 50*2ms = 100ms                        */
    switch (waitForResponse)  {   /* type of response polling?                                */
    case 0 :              /* no polling? valid option, but shouldn't have been called */
      error_code = NO_Si2176_ERROR;     /* return no error                                          */
      goto exit;

    case 1 :              /* I2C polling status?                                      */
      if ((unsigned int)L0_ReadCommandBytes(context->i2c, nbBytes, pByteBuffer) != nbBytes) error_code = ERROR_Si2176_POLLING_RESPONSE;
            else error_code = NO_Si2176_ERROR;
      if (error_code) goto exit;  /* if error, exit with error code                           */
      if (pByteBuffer[0] & 0x80)  { /* CTS set?                                                 */
                error_code = Si2176_CurrentResponseStatus(status1, pByteBuffer[0]);
        goto exit;          /* exit whether ERR set or not                              */
      }
      break;

    default :
      error_code = ERROR_Si2176_PARAMETER_OUT_OF_RANGE; /* support debug of invalid CTS poll parameter   */
      goto exit;
    }
    // a delay is not necessary here
    // use I2C duration to set timeout: Start+DevAddr+R/W+Ack+STATUS+ACK+Stop = 20bits => 50us min @ 400kHz/200us min @100kHz
  }
  error_code = ERROR_Si2176_CTS_TIMEOUT;

exit:
   return error_code;
}

/* _commands_insertion_start */
#ifdef    Si2176_AGC_OVERRIDE_CMD
 /*---------------------------------------------------*/
/* Si2176_AGC_OVERRIDE COMMAND                     */
/*---------------------------------------------------*/
 unsigned char  Si2176_L1_AGC_OVERRIDE              (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse,
                                                                                      unsigned char   force_max_gain,
                                                                                      unsigned char   force_top_gain,
                                                                                      Si2176_CmdReplyObj *rsp)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[1];

  #ifdef   DEBUG_RANGE_CHECK
    if ( (force_max_gain > Si2176_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_MAX)
      || (force_top_gain > Si2176_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_MAX) )
    return ERROR_Si2176_PARAMETER_OUT_OF_RANGE;
  #endif /* DEBUG_RANGE_CHECK */

    if (Si2176_waitForCTS) {
        error_code = Si2176_pollForCTS(context, Si2176_waitForCTS);
        if (error_code) goto exit;
    }

    cmdByteBuffer[0] = Si2176_AGC_OVERRIDE_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( force_max_gain & Si2176_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_MASK ) << Si2176_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_LSB|
                          ( force_top_gain & Si2176_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_MASK ) << Si2176_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_LSB);

    if (L0_WriteCommandBytes(context->i2c, 2, cmdByteBuffer) != 2) error_code = ERROR_Si2176_SENDING_COMMAND;

    if (!error_code && Si2176_waitForResponse) {
        error_code = Si2176_pollForResponse(context, Si2176_waitForResponse, 1, rspByteBuffer, &status);
        rsp->agc_override.STATUS = &status;
    }
  exit:
    return error_code;
}
#endif /* Si2176_AGC_OVERRIDE_CMD */
#ifdef    Si2176_ATV_RESTART_CMD
 /*---------------------------------------------------*/
/* Si2176_ATV_RESTART COMMAND                      */
/*---------------------------------------------------*/
 unsigned char  Si2176_L1_ATV_RESTART               (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse,
                                                                                      unsigned char   mode,
                                                                                      Si2176_CmdReplyObj *rsp)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[1];

  #ifdef   DEBUG_RANGE_CHECK
    if ( (mode > Si2176_ATV_RESTART_CMD_MODE_MAX) )
    return ERROR_Si2176_PARAMETER_OUT_OF_RANGE;
  #endif /* DEBUG_RANGE_CHECK */

    if (Si2176_waitForCTS) {
        error_code = Si2176_pollForCTS(context, Si2176_waitForCTS);
        if (error_code) goto exit;
    }

    cmdByteBuffer[0] = Si2176_ATV_RESTART_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( mode & Si2176_ATV_RESTART_CMD_MODE_MASK ) << Si2176_ATV_RESTART_CMD_MODE_LSB);

    if (L0_WriteCommandBytes(context->i2c, 2, cmdByteBuffer) != 2) error_code = ERROR_Si2176_SENDING_COMMAND;

    if (!error_code && Si2176_waitForResponse) {
        error_code = Si2176_pollForResponse(context, Si2176_waitForResponse, 1, rspByteBuffer, &status);
        rsp->atv_restart.STATUS = &status;
    }
  exit:
    return error_code;
}
#endif /* Si2176_ATV_RESTART_CMD */
#ifdef    Si2176_ATV_STATUS_CMD
 /*---------------------------------------------------*/
/* Si2176_ATV_STATUS COMMAND                       */
/*---------------------------------------------------*/
 unsigned char  Si2176_L1_ATV_STATUS                (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse,
                                                                                      unsigned char   intack,
                                                                                      Si2176_CmdReplyObj *rsp)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[11];

  #ifdef   DEBUG_RANGE_CHECK
    if ( (intack > Si2176_ATV_STATUS_CMD_INTACK_MAX) )
    return ERROR_Si2176_PARAMETER_OUT_OF_RANGE;
  #endif /* DEBUG_RANGE_CHECK */

    if (Si2176_waitForCTS) {
        error_code = Si2176_pollForCTS(context, Si2176_waitForCTS);
        if (error_code) goto exit;
    }

    cmdByteBuffer[0] = Si2176_ATV_STATUS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( intack & Si2176_ATV_STATUS_CMD_INTACK_MASK ) << Si2176_ATV_STATUS_CMD_INTACK_LSB);

    if (L0_WriteCommandBytes(context->i2c, 2, cmdByteBuffer) != 2) error_code = ERROR_Si2176_SENDING_COMMAND;

    if (!error_code && Si2176_waitForResponse) {
        error_code = Si2176_pollForResponse(context, Si2176_waitForResponse, 11, rspByteBuffer, &status);
        rsp->atv_status.STATUS = &status;
        if (!error_code)  {
          rsp->atv_status.chlint           =   (( ( (rspByteBuffer[1]  )) >> Si2176_ATV_STATUS_RESPONSE_CHLINT_LSB           ) & Si2176_ATV_STATUS_RESPONSE_CHLINT_MASK           );
          rsp->atv_status.pclint           =   (( ( (rspByteBuffer[1]  )) >> Si2176_ATV_STATUS_RESPONSE_PCLINT_LSB           ) & Si2176_ATV_STATUS_RESPONSE_PCLINT_MASK           );
          rsp->atv_status.dlint            =   (( ( (rspByteBuffer[1]  )) >> Si2176_ATV_STATUS_RESPONSE_DLINT_LSB            ) & Si2176_ATV_STATUS_RESPONSE_DLINT_MASK            );
          rsp->atv_status.snrlint          =   (( ( (rspByteBuffer[1]  )) >> Si2176_ATV_STATUS_RESPONSE_SNRLINT_LSB          ) & Si2176_ATV_STATUS_RESPONSE_SNRLINT_MASK          );
          rsp->atv_status.snrhint          =   (( ( (rspByteBuffer[1]  )) >> Si2176_ATV_STATUS_RESPONSE_SNRHINT_LSB          ) & Si2176_ATV_STATUS_RESPONSE_SNRHINT_MASK          );
          rsp->atv_status.chl              =   (( ( (rspByteBuffer[2]  )) >> Si2176_ATV_STATUS_RESPONSE_CHL_LSB              ) & Si2176_ATV_STATUS_RESPONSE_CHL_MASK              );
          rsp->atv_status.pcl              =   (( ( (rspByteBuffer[2]  )) >> Si2176_ATV_STATUS_RESPONSE_PCL_LSB              ) & Si2176_ATV_STATUS_RESPONSE_PCL_MASK              );
          rsp->atv_status.dl               =   (( ( (rspByteBuffer[2]  )) >> Si2176_ATV_STATUS_RESPONSE_DL_LSB               ) & Si2176_ATV_STATUS_RESPONSE_DL_MASK               );
          rsp->atv_status.snrl             =   (( ( (rspByteBuffer[2]  )) >> Si2176_ATV_STATUS_RESPONSE_SNRL_LSB             ) & Si2176_ATV_STATUS_RESPONSE_SNRL_MASK             );
          rsp->atv_status.snrh             =   (( ( (rspByteBuffer[2]  )) >> Si2176_ATV_STATUS_RESPONSE_SNRH_LSB             ) & Si2176_ATV_STATUS_RESPONSE_SNRH_MASK             );
          rsp->atv_status.video_snr        =   (( ( (rspByteBuffer[3]  )) >> Si2176_ATV_STATUS_RESPONSE_VIDEO_SNR_LSB        ) & Si2176_ATV_STATUS_RESPONSE_VIDEO_SNR_MASK        );
          rsp->atv_status.afc_freq         = (((( ( (rspByteBuffer[4]  ) | (rspByteBuffer[5]  << 8 )) >> Si2176_ATV_STATUS_RESPONSE_AFC_FREQ_LSB         ) & Si2176_ATV_STATUS_RESPONSE_AFC_FREQ_MASK) <<Si2176_ATV_STATUS_RESPONSE_AFC_FREQ_SHIFT ) >>Si2176_ATV_STATUS_RESPONSE_AFC_FREQ_SHIFT         );
          rsp->atv_status.video_sc_spacing = (((( ( (rspByteBuffer[6]  ) | (rspByteBuffer[7]  << 8 )) >> Si2176_ATV_STATUS_RESPONSE_VIDEO_SC_SPACING_LSB ) & Si2176_ATV_STATUS_RESPONSE_VIDEO_SC_SPACING_MASK) <<Si2176_ATV_STATUS_RESPONSE_VIDEO_SC_SPACING_SHIFT ) >>Si2176_ATV_STATUS_RESPONSE_VIDEO_SC_SPACING_SHIFT );
          rsp->atv_status.video_sys        =   (( ( (rspByteBuffer[8]  )) >> Si2176_ATV_STATUS_RESPONSE_VIDEO_SYS_LSB        ) & Si2176_ATV_STATUS_RESPONSE_VIDEO_SYS_MASK        );
          rsp->atv_status.color            =   (( ( (rspByteBuffer[8]  )) >> Si2176_ATV_STATUS_RESPONSE_COLOR_LSB            ) & Si2176_ATV_STATUS_RESPONSE_COLOR_MASK            );
          rsp->atv_status.trans            =   (( ( (rspByteBuffer[8]  )) >> Si2176_ATV_STATUS_RESPONSE_TRANS_LSB            ) & Si2176_ATV_STATUS_RESPONSE_TRANS_MASK            );
          rsp->atv_status.audio_sys        =   (( ( (rspByteBuffer[9]  )) >> Si2176_ATV_STATUS_RESPONSE_AUDIO_SYS_LSB        ) & Si2176_ATV_STATUS_RESPONSE_AUDIO_SYS_MASK        );
          rsp->atv_status.audio_demod_mode =   (( ( (rspByteBuffer[9]  )) >> Si2176_ATV_STATUS_RESPONSE_AUDIO_DEMOD_MODE_LSB ) & Si2176_ATV_STATUS_RESPONSE_AUDIO_DEMOD_MODE_MASK );
          rsp->atv_status.audio_chan_bw    =   (( ( (rspByteBuffer[10] )) >> Si2176_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_LSB    ) & Si2176_ATV_STATUS_RESPONSE_AUDIO_CHAN_BW_MASK    );
        }
    }
  exit:
    return error_code;
}
#endif /* Si2176_ATV_STATUS_CMD */
#ifdef    Si2176_CONFIG_PINS_CMD
 /*---------------------------------------------------*/
/* Si2176_CONFIG_PINS COMMAND                      */
/*---------------------------------------------------*/
 unsigned char  Si2176_L1_CONFIG_PINS               (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse,
                                                                                      unsigned char   gpio1_mode,
                                                                                      unsigned char   gpio1_read,
                                                                                      unsigned char   gpio2_mode,
                                                                                      unsigned char   gpio2_read,
                                                                                      unsigned char   gpio3_mode,
                                                                                      unsigned char   gpio3_read,
                                                                                      unsigned char   bclk1_mode,
                                                                                      unsigned char   bclk1_read,
                                                                                      unsigned char   xout_mode,
                                                                                      Si2176_CmdReplyObj *rsp)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[6];
    unsigned char rspByteBuffer[6];

  #ifdef   DEBUG_RANGE_CHECK
    if ( (gpio1_mode > Si2176_CONFIG_PINS_CMD_GPIO1_MODE_MAX)
      || (gpio1_read > Si2176_CONFIG_PINS_CMD_GPIO1_READ_MAX)
      || (gpio2_mode > Si2176_CONFIG_PINS_CMD_GPIO2_MODE_MAX)
      || (gpio2_read > Si2176_CONFIG_PINS_CMD_GPIO2_READ_MAX)
      || (gpio3_mode > Si2176_CONFIG_PINS_CMD_GPIO3_MODE_MAX)
      || (gpio3_read > Si2176_CONFIG_PINS_CMD_GPIO3_READ_MAX)
      || (bclk1_mode > Si2176_CONFIG_PINS_CMD_BCLK1_MODE_MAX)
      || (bclk1_read > Si2176_CONFIG_PINS_CMD_BCLK1_READ_MAX)
      || (xout_mode  > Si2176_CONFIG_PINS_CMD_XOUT_MODE_MAX ) )
    return ERROR_Si2176_PARAMETER_OUT_OF_RANGE;
  #endif /* DEBUG_RANGE_CHECK */

    if (Si2176_waitForCTS) {
        error_code = Si2176_pollForCTS(context, Si2176_waitForCTS);
        if (error_code) goto exit;
    }

    cmdByteBuffer[0] = Si2176_CONFIG_PINS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( gpio1_mode & Si2176_CONFIG_PINS_CMD_GPIO1_MODE_MASK ) << Si2176_CONFIG_PINS_CMD_GPIO1_MODE_LSB|
                          ( gpio1_read & Si2176_CONFIG_PINS_CMD_GPIO1_READ_MASK ) << Si2176_CONFIG_PINS_CMD_GPIO1_READ_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( gpio2_mode & Si2176_CONFIG_PINS_CMD_GPIO2_MODE_MASK ) << Si2176_CONFIG_PINS_CMD_GPIO2_MODE_LSB|
                          ( gpio2_read & Si2176_CONFIG_PINS_CMD_GPIO2_READ_MASK ) << Si2176_CONFIG_PINS_CMD_GPIO2_READ_LSB);
    cmdByteBuffer[3] = (unsigned char) ( ( gpio3_mode & Si2176_CONFIG_PINS_CMD_GPIO3_MODE_MASK ) << Si2176_CONFIG_PINS_CMD_GPIO3_MODE_LSB|
                          ( gpio3_read & Si2176_CONFIG_PINS_CMD_GPIO3_READ_MASK ) << Si2176_CONFIG_PINS_CMD_GPIO3_READ_LSB);
    cmdByteBuffer[4] = (unsigned char) ( ( bclk1_mode & Si2176_CONFIG_PINS_CMD_BCLK1_MODE_MASK ) << Si2176_CONFIG_PINS_CMD_BCLK1_MODE_LSB|
                          ( bclk1_read & Si2176_CONFIG_PINS_CMD_BCLK1_READ_MASK ) << Si2176_CONFIG_PINS_CMD_BCLK1_READ_LSB);
    cmdByteBuffer[5] = (unsigned char) ( ( xout_mode  & Si2176_CONFIG_PINS_CMD_XOUT_MODE_MASK  ) << Si2176_CONFIG_PINS_CMD_XOUT_MODE_LSB );

    if (L0_WriteCommandBytes(context->i2c, 6, cmdByteBuffer) != 6) error_code = ERROR_Si2176_SENDING_COMMAND;

    if (!error_code && Si2176_waitForResponse) {
        error_code = Si2176_pollForResponse(context, Si2176_waitForResponse, 6, rspByteBuffer, &status);
        rsp->config_pins.STATUS = &status;
        if (!error_code)  {
          rsp->config_pins.gpio1_mode  =   (( ( (rspByteBuffer[1]  )) >> Si2176_CONFIG_PINS_RESPONSE_GPIO1_MODE_LSB  ) & Si2176_CONFIG_PINS_RESPONSE_GPIO1_MODE_MASK  );
          rsp->config_pins.gpio1_state =   (( ( (rspByteBuffer[1]  )) >> Si2176_CONFIG_PINS_RESPONSE_GPIO1_STATE_LSB ) & Si2176_CONFIG_PINS_RESPONSE_GPIO1_STATE_MASK );
          rsp->config_pins.gpio2_mode  =   (( ( (rspByteBuffer[2]  )) >> Si2176_CONFIG_PINS_RESPONSE_GPIO2_MODE_LSB  ) & Si2176_CONFIG_PINS_RESPONSE_GPIO2_MODE_MASK  );
          rsp->config_pins.gpio2_state =   (( ( (rspByteBuffer[2]  )) >> Si2176_CONFIG_PINS_RESPONSE_GPIO2_STATE_LSB ) & Si2176_CONFIG_PINS_RESPONSE_GPIO2_STATE_MASK );
          rsp->config_pins.gpio3_mode  =   (( ( (rspByteBuffer[3]  )) >> Si2176_CONFIG_PINS_RESPONSE_GPIO3_MODE_LSB  ) & Si2176_CONFIG_PINS_RESPONSE_GPIO3_MODE_MASK  );
          rsp->config_pins.gpio3_state =   (( ( (rspByteBuffer[3]  )) >> Si2176_CONFIG_PINS_RESPONSE_GPIO3_STATE_LSB ) & Si2176_CONFIG_PINS_RESPONSE_GPIO3_STATE_MASK );
          rsp->config_pins.bclk1_mode  =   (( ( (rspByteBuffer[4]  )) >> Si2176_CONFIG_PINS_RESPONSE_BCLK1_MODE_LSB  ) & Si2176_CONFIG_PINS_RESPONSE_BCLK1_MODE_MASK  );
          rsp->config_pins.bclk1_state =   (( ( (rspByteBuffer[4]  )) >> Si2176_CONFIG_PINS_RESPONSE_BCLK1_STATE_LSB ) & Si2176_CONFIG_PINS_RESPONSE_BCLK1_STATE_MASK );
          rsp->config_pins.xout_mode   =   (( ( (rspByteBuffer[5]  )) >> Si2176_CONFIG_PINS_RESPONSE_XOUT_MODE_LSB   ) & Si2176_CONFIG_PINS_RESPONSE_XOUT_MODE_MASK   );
        }
    }
  exit:
    return error_code;
}
#endif /* Si2176_CONFIG_PINS_CMD */
#ifdef    Si2176_DTV_RESTART_CMD
 /*---------------------------------------------------*/
/* Si2176_DTV_RESTART COMMAND                      */
/*---------------------------------------------------*/
 unsigned char  Si2176_L1_DTV_RESTART               (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse,
                                                                                      Si2176_CmdReplyObj *rsp)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[1];

    if (Si2176_waitForCTS) {
        error_code = Si2176_pollForCTS(context, Si2176_waitForCTS);
        if (error_code) goto exit;
    }

    cmdByteBuffer[0] = Si2176_DTV_RESTART_CMD;

    if (L0_WriteCommandBytes(context->i2c, 1, cmdByteBuffer) != 1) error_code = ERROR_Si2176_SENDING_COMMAND;

    if (!error_code && Si2176_waitForResponse) {
        error_code = Si2176_pollForResponse(context, Si2176_waitForResponse, 1, rspByteBuffer, &status);
        rsp->dtv_restart.STATUS = &status;
    }
  exit:
    return error_code;
}
#endif /* Si2176_DTV_RESTART_CMD */
#ifdef    Si2176_DTV_STATUS_CMD
 /*---------------------------------------------------*/
/* Si2176_DTV_STATUS COMMAND                       */
/*---------------------------------------------------*/
 unsigned char  Si2176_L1_DTV_STATUS                (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse,
                                                                                      unsigned char   intack,
                                                                                      Si2176_CmdReplyObj *rsp)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[4];

  #ifdef   DEBUG_RANGE_CHECK
    if ( (intack > Si2176_DTV_STATUS_CMD_INTACK_MAX) )
    return ERROR_Si2176_PARAMETER_OUT_OF_RANGE;
  #endif /* DEBUG_RANGE_CHECK */

    if (Si2176_waitForCTS) {
        error_code = Si2176_pollForCTS(context, Si2176_waitForCTS);
        if (error_code) goto exit;
    }

    cmdByteBuffer[0] = Si2176_DTV_STATUS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( intack & Si2176_DTV_STATUS_CMD_INTACK_MASK ) << Si2176_DTV_STATUS_CMD_INTACK_LSB);

    if (L0_WriteCommandBytes(context->i2c, 2, cmdByteBuffer) != 2) error_code = ERROR_Si2176_SENDING_COMMAND;

    if (!error_code && Si2176_waitForResponse) {
        error_code = Si2176_pollForResponse(context, Si2176_waitForResponse, 4, rspByteBuffer, &status);
        rsp->dtv_status.STATUS = &status;
        if (!error_code)  {
          rsp->dtv_status.chlint     =   (( ( (rspByteBuffer[1]  )) >> Si2176_DTV_STATUS_RESPONSE_CHLINT_LSB     ) & Si2176_DTV_STATUS_RESPONSE_CHLINT_MASK     );
          rsp->dtv_status.chl        =   (( ( (rspByteBuffer[2]  )) >> Si2176_DTV_STATUS_RESPONSE_CHL_LSB        ) & Si2176_DTV_STATUS_RESPONSE_CHL_MASK        );
          rsp->dtv_status.bw         =   (( ( (rspByteBuffer[3]  )) >> Si2176_DTV_STATUS_RESPONSE_BW_LSB         ) & Si2176_DTV_STATUS_RESPONSE_BW_MASK         );
          rsp->dtv_status.modulation =   (( ( (rspByteBuffer[3]  )) >> Si2176_DTV_STATUS_RESPONSE_MODULATION_LSB ) & Si2176_DTV_STATUS_RESPONSE_MODULATION_MASK );
        }
    }
  exit:
    return error_code;
}
#endif /* Si2176_DTV_STATUS_CMD */
#ifdef    Si2176_EXIT_BOOTLOADER_CMD
 /*---------------------------------------------------*/
/* Si2176_EXIT_BOOTLOADER COMMAND                  */
/*---------------------------------------------------*/
 unsigned char  Si2176_L1_EXIT_BOOTLOADER           (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse,
                                                                                      unsigned char   func,
                                                                                      unsigned char   ctsien,
                                                                                      Si2176_CmdReplyObj *rsp)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[1];

  #ifdef   DEBUG_RANGE_CHECK
    if ( (func   > Si2176_EXIT_BOOTLOADER_CMD_FUNC_MAX  )
      || (ctsien > Si2176_EXIT_BOOTLOADER_CMD_CTSIEN_MAX) )
    return ERROR_Si2176_PARAMETER_OUT_OF_RANGE;
  #endif /* DEBUG_RANGE_CHECK */

    if (Si2176_waitForCTS) {
        error_code = Si2176_pollForCTS(context, Si2176_waitForCTS);
        if (error_code) goto exit;
    }

    cmdByteBuffer[0] = Si2176_EXIT_BOOTLOADER_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( func   & Si2176_EXIT_BOOTLOADER_CMD_FUNC_MASK   ) << Si2176_EXIT_BOOTLOADER_CMD_FUNC_LSB  |
                          ( ctsien & Si2176_EXIT_BOOTLOADER_CMD_CTSIEN_MASK ) << Si2176_EXIT_BOOTLOADER_CMD_CTSIEN_LSB);

    if (L0_WriteCommandBytes(context->i2c, 2, cmdByteBuffer) != 2) error_code = ERROR_Si2176_SENDING_COMMAND;

    if (!error_code && Si2176_waitForResponse) {
        error_code = Si2176_pollForResponse(context, Si2176_waitForResponse, 1, rspByteBuffer, &status);
        rsp->exit_bootloader.STATUS = &status;
    }
  exit:
    return error_code;
}
#endif /* Si2176_EXIT_BOOTLOADER_CMD */
#ifdef    Si2176_FINE_TUNE_CMD
 /*---------------------------------------------------*/
/* Si2176_FINE_TUNE COMMAND                        */
/*---------------------------------------------------*/
 unsigned char  Si2176_L1_FINE_TUNE                 (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse,
                                                                                      unsigned char   reserved,
                                                                                                int   offset_500hz,
                                                                                      Si2176_CmdReplyObj *rsp)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[4];
    unsigned char rspByteBuffer[1];

  #ifdef   DEBUG_RANGE_CHECK
    if ( (reserved     > Si2176_FINE_TUNE_CMD_RESERVED_MAX    )
      || (offset_500hz > Si2176_FINE_TUNE_CMD_OFFSET_500HZ_MAX)  || (offset_500hz < Si2176_FINE_TUNE_CMD_OFFSET_500HZ_MIN) )
    return ERROR_Si2176_PARAMETER_OUT_OF_RANGE;
  #endif /* DEBUG_RANGE_CHECK */

    if (Si2176_waitForCTS) {
        error_code = Si2176_pollForCTS(context, Si2176_waitForCTS);
        if (error_code) goto exit;
    }

    cmdByteBuffer[0] = Si2176_FINE_TUNE_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( reserved     & Si2176_FINE_TUNE_CMD_RESERVED_MASK     ) << Si2176_FINE_TUNE_CMD_RESERVED_LSB    );
    cmdByteBuffer[2] = (unsigned char) ( ( offset_500hz & Si2176_FINE_TUNE_CMD_OFFSET_500HZ_MASK ) << Si2176_FINE_TUNE_CMD_OFFSET_500HZ_LSB);
    cmdByteBuffer[3] = (unsigned char) ((( offset_500hz & Si2176_FINE_TUNE_CMD_OFFSET_500HZ_MASK ) << Si2176_FINE_TUNE_CMD_OFFSET_500HZ_LSB)>>8);

    if (L0_WriteCommandBytes(context->i2c, 4, cmdByteBuffer) != 4) error_code = ERROR_Si2176_SENDING_COMMAND;

    if (!error_code && Si2176_waitForResponse) {
        error_code = Si2176_pollForResponse(context, Si2176_waitForResponse, 1, rspByteBuffer, &status);
        rsp->fine_tune.STATUS = &status;
    }
  exit:
    return error_code;
}
#endif /* Si2176_FINE_TUNE_CMD */
#ifdef    Si2176_GET_PROPERTY_CMD
 /*---------------------------------------------------*/
/* Si2176_GET_PROPERTY COMMAND                     */
/*---------------------------------------------------*/
 unsigned char  Si2176_L1_GET_PROPERTY              (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse,
                                                                                      unsigned char   reserved,
                                                                                      unsigned int    prop,
                                                                                      Si2176_CmdReplyObj *rsp)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[4];
    unsigned char rspByteBuffer[4];

  #ifdef   DEBUG_RANGE_CHECK
    if ( (reserved > Si2176_GET_PROPERTY_CMD_RESERVED_MAX) )
    return ERROR_Si2176_PARAMETER_OUT_OF_RANGE;
  #endif /* DEBUG_RANGE_CHECK */

    if (Si2176_waitForCTS) {
        error_code = Si2176_pollForCTS(context, Si2176_waitForCTS);
        if (error_code) goto exit;
    }

    cmdByteBuffer[0] = Si2176_GET_PROPERTY_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( reserved & Si2176_GET_PROPERTY_CMD_RESERVED_MASK ) << Si2176_GET_PROPERTY_CMD_RESERVED_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( prop     & Si2176_GET_PROPERTY_CMD_PROP_MASK     ) << Si2176_GET_PROPERTY_CMD_PROP_LSB    );
    cmdByteBuffer[3] = (unsigned char) ((( prop     & Si2176_GET_PROPERTY_CMD_PROP_MASK     ) << Si2176_GET_PROPERTY_CMD_PROP_LSB    )>>8);

    if (L0_WriteCommandBytes(context->i2c, 4, cmdByteBuffer) != 4) error_code = ERROR_Si2176_SENDING_COMMAND;

    if (!error_code && Si2176_waitForResponse) {
        error_code = Si2176_pollForResponse(context, Si2176_waitForResponse, 4, rspByteBuffer, &status);
        rsp->get_property.STATUS = &status;
        if (!error_code)  {
          rsp->get_property.reserved =   (( ( (rspByteBuffer[1]  )) >> Si2176_GET_PROPERTY_RESPONSE_RESERVED_LSB ) & Si2176_GET_PROPERTY_RESPONSE_RESERVED_MASK );
          rsp->get_property.data     =   (( ( (rspByteBuffer[2]  ) | (rspByteBuffer[3]  << 8 )) >> Si2176_GET_PROPERTY_RESPONSE_DATA_LSB     ) & Si2176_GET_PROPERTY_RESPONSE_DATA_MASK     );
        }
    }
  exit:
    return error_code;
}
#endif /* Si2176_GET_PROPERTY_CMD */
#ifdef    Si2176_GET_REV_CMD
 /*---------------------------------------------------*/
/* Si2176_GET_REV COMMAND                          */
/*---------------------------------------------------*/
 unsigned char  Si2176_L1_GET_REV                   (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse,
                                                                                      Si2176_CmdReplyObj *rsp)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[10];

    if (Si2176_waitForCTS) {
        error_code = Si2176_pollForCTS(context, Si2176_waitForCTS);
        if (error_code) goto exit;
    }

    cmdByteBuffer[0] = Si2176_GET_REV_CMD;

    if (L0_WriteCommandBytes(context->i2c, 1, cmdByteBuffer) != 1) error_code = ERROR_Si2176_SENDING_COMMAND;

    if (!error_code && Si2176_waitForResponse) {
        error_code = Si2176_pollForResponse(context, Si2176_waitForResponse, 10, rspByteBuffer, &status);
        rsp->get_rev.STATUS = &status;
        if (!error_code)  {
          rsp->get_rev.pn       =   (( ( (rspByteBuffer[1]  )) >> Si2176_GET_REV_RESPONSE_PN_LSB       ) & Si2176_GET_REV_RESPONSE_PN_MASK       );
          rsp->get_rev.fwmajor  =   (( ( (rspByteBuffer[2]  )) >> Si2176_GET_REV_RESPONSE_FWMAJOR_LSB  ) & Si2176_GET_REV_RESPONSE_FWMAJOR_MASK  );
          rsp->get_rev.fwminor  =   (( ( (rspByteBuffer[3]  )) >> Si2176_GET_REV_RESPONSE_FWMINOR_LSB  ) & Si2176_GET_REV_RESPONSE_FWMINOR_MASK  );
          rsp->get_rev.patch    =   (( ( (rspByteBuffer[4]  ) | (rspByteBuffer[5]  << 8 )) >> Si2176_GET_REV_RESPONSE_PATCH_LSB    ) & Si2176_GET_REV_RESPONSE_PATCH_MASK    );
          rsp->get_rev.cmpmajor =   (( ( (rspByteBuffer[6]  )) >> Si2176_GET_REV_RESPONSE_CMPMAJOR_LSB ) & Si2176_GET_REV_RESPONSE_CMPMAJOR_MASK );
          rsp->get_rev.cmpminor =   (( ( (rspByteBuffer[7]  )) >> Si2176_GET_REV_RESPONSE_CMPMINOR_LSB ) & Si2176_GET_REV_RESPONSE_CMPMINOR_MASK );
          rsp->get_rev.cmpbuild =   (( ( (rspByteBuffer[8]  )) >> Si2176_GET_REV_RESPONSE_CMPBUILD_LSB ) & Si2176_GET_REV_RESPONSE_CMPBUILD_MASK );
          rsp->get_rev.chiprev  =   (( ( (rspByteBuffer[9]  )) >> Si2176_GET_REV_RESPONSE_CHIPREV_LSB  ) & Si2176_GET_REV_RESPONSE_CHIPREV_MASK  );
        }
    }
  exit:
    return error_code;
}
#endif /* Si2176_GET_REV_CMD */
#ifdef    Si2176_PART_INFO_CMD
 /*---------------------------------------------------*/
/* Si2176_PART_INFO COMMAND                        */
/*---------------------------------------------------*/
 unsigned char  Si2176_L1_PART_INFO                 (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse,
                                                                                      Si2176_CmdReplyObj *rsp)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[13];

    if (Si2176_waitForCTS) {
        error_code = Si2176_pollForCTS(context, Si2176_waitForCTS);
        if (error_code) goto exit;
    }

    cmdByteBuffer[0] = Si2176_PART_INFO_CMD;

    if (L0_WriteCommandBytes(context->i2c, 1, cmdByteBuffer) != 1) error_code = ERROR_Si2176_SENDING_COMMAND;

    if (!error_code && Si2176_waitForResponse) {
        error_code = Si2176_pollForResponse(context, Si2176_waitForResponse, 13, rspByteBuffer, &status);
        rsp->part_info.STATUS = &status;
        if (!error_code)  {
          rsp->part_info.chiprev  =   (( ( (rspByteBuffer[1]  )) >> Si2176_PART_INFO_RESPONSE_CHIPREV_LSB  ) & Si2176_PART_INFO_RESPONSE_CHIPREV_MASK  );
          rsp->part_info.part     =   (( ( (rspByteBuffer[2]  )) >> Si2176_PART_INFO_RESPONSE_PART_LSB     ) & Si2176_PART_INFO_RESPONSE_PART_MASK     );
          rsp->part_info.pmajor   =   (( ( (rspByteBuffer[3]  )) >> Si2176_PART_INFO_RESPONSE_PMAJOR_LSB   ) & Si2176_PART_INFO_RESPONSE_PMAJOR_MASK   );
          rsp->part_info.pminor   =   (( ( (rspByteBuffer[4]  )) >> Si2176_PART_INFO_RESPONSE_PMINOR_LSB   ) & Si2176_PART_INFO_RESPONSE_PMINOR_MASK   );
          rsp->part_info.pbuild   =   (( ( (rspByteBuffer[5]  )) >> Si2176_PART_INFO_RESPONSE_PBUILD_LSB   ) & Si2176_PART_INFO_RESPONSE_PBUILD_MASK   );
          rsp->part_info.reserved =   (( ( (rspByteBuffer[6]  ) | (rspByteBuffer[7]  << 8 )) >> Si2176_PART_INFO_RESPONSE_RESERVED_LSB ) & Si2176_PART_INFO_RESPONSE_RESERVED_MASK );
          rsp->part_info.serial   =   (( ( (rspByteBuffer[8]  ) | (rspByteBuffer[9]  << 8 ) | (rspByteBuffer[10] << 16 ) | (rspByteBuffer[11] << 24 )) >> Si2176_PART_INFO_RESPONSE_SERIAL_LSB   ) & Si2176_PART_INFO_RESPONSE_SERIAL_MASK   );
          rsp->part_info.romid    =   (( ( (rspByteBuffer[12] )) >> Si2176_PART_INFO_RESPONSE_ROMID_LSB    ) & Si2176_PART_INFO_RESPONSE_ROMID_MASK    );
        }
    }
  exit:
    return error_code;
}
#endif /* Si2176_PART_INFO_CMD */
#ifdef    Si2176_POWER_DOWN_CMD
 /*---------------------------------------------------*/
/* Si2176_POWER_DOWN COMMAND                       */
/*---------------------------------------------------*/
 unsigned char  Si2176_L1_POWER_DOWN                (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse,
                                                                                      Si2176_CmdReplyObj *rsp)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[1];

    if (Si2176_waitForCTS) {
        error_code = Si2176_pollForCTS(context, Si2176_waitForCTS);
        if (error_code) goto exit;
    }

    cmdByteBuffer[0] = Si2176_POWER_DOWN_CMD;

    if (L0_WriteCommandBytes(context->i2c, 1, cmdByteBuffer) != 1) error_code = ERROR_Si2176_SENDING_COMMAND;

    if (!error_code && Si2176_waitForResponse) {
        error_code = Si2176_pollForResponse(context, Si2176_waitForResponse, 1, rspByteBuffer, &status);
        rsp->power_down.STATUS = &status;
    }
  exit:
    return error_code;
}
#endif /* Si2176_POWER_DOWN_CMD */
#ifdef    Si2176_POWER_UP_CMD
 /*---------------------------------------------------*/
/* Si2176_POWER_UP COMMAND                         */
/*---------------------------------------------------*/
 unsigned char  Si2176_L1_POWER_UP                  (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse,
                                                                                      unsigned char   subcode,
                                                                                      unsigned char   reserved1,
                                                                                      unsigned char   reserved2,
                                                                                      unsigned char   reserved3,
                                                                                      unsigned char   clock_mode,
                                                                                      unsigned char   clock_freq,
                                                                                      unsigned char   addr_mode,
                                                                                      unsigned char   func,
                                                                                      unsigned char   ctsien,
                                                                                      unsigned char   wake_up,
                                                                                      Si2176_CmdReplyObj *rsp)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[9];
    unsigned char rspByteBuffer[1];

  #ifdef   DEBUG_RANGE_CHECK
    if ( (subcode    > Si2176_POWER_UP_CMD_SUBCODE_MAX   )  || (subcode    < Si2176_POWER_UP_CMD_SUBCODE_MIN   )
      || (reserved1  > Si2176_POWER_UP_CMD_RESERVED1_MAX )  || (reserved1  < Si2176_POWER_UP_CMD_RESERVED1_MIN )
      || (reserved2  > Si2176_POWER_UP_CMD_RESERVED2_MAX )
      || (reserved3  > Si2176_POWER_UP_CMD_RESERVED3_MAX )
      || (clock_mode > Si2176_POWER_UP_CMD_CLOCK_MODE_MAX)  || (clock_mode < Si2176_POWER_UP_CMD_CLOCK_MODE_MIN)
      || (clock_freq > Si2176_POWER_UP_CMD_CLOCK_FREQ_MAX)
      || (addr_mode  > Si2176_POWER_UP_CMD_ADDR_MODE_MAX )
      || (func       > Si2176_POWER_UP_CMD_FUNC_MAX      )
      || (ctsien     > Si2176_POWER_UP_CMD_CTSIEN_MAX    )
      || (wake_up    > Si2176_POWER_UP_CMD_WAKE_UP_MAX   )  || (wake_up    < Si2176_POWER_UP_CMD_WAKE_UP_MIN   ) )
    return ERROR_Si2176_PARAMETER_OUT_OF_RANGE;
  #endif /* DEBUG_RANGE_CHECK */

    if (Si2176_waitForCTS) {
        error_code = Si2176_pollForCTS(context, Si2176_waitForCTS);
        if (error_code)
        {
            printf("%lu:%s, err=%u\n", __LINE__, __FILE__, error_code);
            goto exit;
        }
    }

    cmdByteBuffer[0] = Si2176_POWER_UP_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( subcode    & Si2176_POWER_UP_CMD_SUBCODE_MASK    ) << Si2176_POWER_UP_CMD_SUBCODE_LSB   );
    cmdByteBuffer[2] = (unsigned char) ( ( reserved1  & Si2176_POWER_UP_CMD_RESERVED1_MASK  ) << Si2176_POWER_UP_CMD_RESERVED1_LSB );
    cmdByteBuffer[3] = (unsigned char) ( ( reserved2  & Si2176_POWER_UP_CMD_RESERVED2_MASK  ) << Si2176_POWER_UP_CMD_RESERVED2_LSB );
    cmdByteBuffer[4] = (unsigned char) ( ( reserved3  & Si2176_POWER_UP_CMD_RESERVED3_MASK  ) << Si2176_POWER_UP_CMD_RESERVED3_LSB );
    cmdByteBuffer[5] = (unsigned char) ( ( clock_mode & Si2176_POWER_UP_CMD_CLOCK_MODE_MASK ) << Si2176_POWER_UP_CMD_CLOCK_MODE_LSB|
                          ( clock_freq & Si2176_POWER_UP_CMD_CLOCK_FREQ_MASK ) << Si2176_POWER_UP_CMD_CLOCK_FREQ_LSB);
    cmdByteBuffer[6] = (unsigned char) ( ( addr_mode  & Si2176_POWER_UP_CMD_ADDR_MODE_MASK  ) << Si2176_POWER_UP_CMD_ADDR_MODE_LSB );
    cmdByteBuffer[7] = (unsigned char) ( ( func       & Si2176_POWER_UP_CMD_FUNC_MASK       ) << Si2176_POWER_UP_CMD_FUNC_LSB      |
                          ( ctsien     & Si2176_POWER_UP_CMD_CTSIEN_MASK     ) << Si2176_POWER_UP_CMD_CTSIEN_LSB    );
    cmdByteBuffer[8] = (unsigned char) ( ( wake_up    & Si2176_POWER_UP_CMD_WAKE_UP_MASK    ) << Si2176_POWER_UP_CMD_WAKE_UP_LSB   );

    if (L0_WriteCommandBytes(context->i2c, 9, cmdByteBuffer) != 9)
    {
        printf("%lu:%s\n", __LINE__, __FILE__);
        error_code = ERROR_Si2176_SENDING_COMMAND;
    }
    //printf("%u: err=%u\n", __LINE__, error_code);

    if (!error_code && Si2176_waitForResponse) {
        error_code = Si2176_pollForResponse(context, Si2176_waitForResponse, 1, rspByteBuffer, &status);
        rsp->power_up.STATUS = &status;
    }
  exit:
    return error_code;
}
#endif /* Si2176_POWER_UP_CMD */
#ifdef    Si2176_SET_PROPERTY_CMD
 /*---------------------------------------------------*/
/* Si2176_SET_PROPERTY COMMAND                     */
/*---------------------------------------------------*/
 unsigned char  Si2176_L1_SET_PROPERTY              (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse,
                                                                                      unsigned char   reserved,
                                                                                      unsigned int    prop,
                                                                                      unsigned int    data,
                                                                                      Si2176_CmdReplyObj *rsp)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[6];
    unsigned char rspByteBuffer[4];

    if (Si2176_waitForCTS) {
        error_code = Si2176_pollForCTS(context, Si2176_waitForCTS);
        if (error_code) goto exit;
    }

    cmdByteBuffer[0] = Si2176_SET_PROPERTY_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( reserved & Si2176_SET_PROPERTY_CMD_RESERVED_MASK ) << Si2176_SET_PROPERTY_CMD_RESERVED_LSB);
    cmdByteBuffer[2] = (unsigned char) ( ( prop     & Si2176_SET_PROPERTY_CMD_PROP_MASK     ) << Si2176_SET_PROPERTY_CMD_PROP_LSB    );
    cmdByteBuffer[3] = (unsigned char) ((( prop     & Si2176_SET_PROPERTY_CMD_PROP_MASK     ) << Si2176_SET_PROPERTY_CMD_PROP_LSB    )>>8);
    cmdByteBuffer[4] = (unsigned char) ( ( data     & Si2176_SET_PROPERTY_CMD_DATA_MASK     ) << Si2176_SET_PROPERTY_CMD_DATA_LSB    );
    cmdByteBuffer[5] = (unsigned char) ((( data     & Si2176_SET_PROPERTY_CMD_DATA_MASK     ) << Si2176_SET_PROPERTY_CMD_DATA_LSB    )>>8);

    if (L0_WriteCommandBytes(context->i2c, 6, cmdByteBuffer) != 6) error_code = ERROR_Si2176_SENDING_COMMAND;

    if (!error_code && Si2176_waitForResponse) {
        error_code = Si2176_pollForResponse(context, Si2176_waitForResponse, 4, rspByteBuffer, &status);
        rsp->set_property.STATUS = &status;
        if (!error_code)  {
          rsp->set_property.reserved =   (( ( (rspByteBuffer[1]  )) >> Si2176_SET_PROPERTY_RESPONSE_RESERVED_LSB ) & Si2176_SET_PROPERTY_RESPONSE_RESERVED_MASK );
          rsp->set_property.data     =   (( ( (rspByteBuffer[2]  ) | (rspByteBuffer[3]  << 8 )) >> Si2176_SET_PROPERTY_RESPONSE_DATA_LSB     ) & Si2176_SET_PROPERTY_RESPONSE_DATA_MASK     );
        }
    }
  exit:
    return error_code;
}
#endif /* Si2176_SET_PROPERTY_CMD */
#ifdef    Si2176_STANDBY_CMD
 /*---------------------------------------------------*/
/* Si2176_STANDBY COMMAND                          */
/*---------------------------------------------------*/
 unsigned char  Si2176_L1_STANDBY                   (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse,
                                                                                      Si2176_CmdReplyObj *rsp)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[1];
    unsigned char rspByteBuffer[1];

    if (Si2176_waitForCTS) {
        error_code = Si2176_pollForCTS(context, Si2176_waitForCTS);
        if (error_code) goto exit;
    }

    cmdByteBuffer[0] = Si2176_STANDBY_CMD;

    if (L0_WriteCommandBytes(context->i2c, 1, cmdByteBuffer) != 1) error_code = ERROR_Si2176_SENDING_COMMAND;

    if (!error_code && Si2176_waitForResponse) {
        error_code = Si2176_pollForResponse(context, Si2176_waitForResponse, 1, rspByteBuffer, &status);
        rsp->standby.STATUS = &status;
    }
  exit:
    return error_code;
}
#endif /* Si2176_STANDBY_CMD */
#ifdef    Si2176_TUNER_STATUS_CMD
 /*---------------------------------------------------*/
/* Si2176_TUNER_STATUS COMMAND                     */
/*---------------------------------------------------*/
 unsigned char  Si2176_L1_TUNER_STATUS              (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse,
                                                                                      unsigned char   intack,
                                                                                      Si2176_CmdReplyObj *rsp)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[2];
    unsigned char rspByteBuffer[12];

  #ifdef   DEBUG_RANGE_CHECK
    if ( (intack > Si2176_TUNER_STATUS_CMD_INTACK_MAX) )
    return ERROR_Si2176_PARAMETER_OUT_OF_RANGE;
  #endif /* DEBUG_RANGE_CHECK */

    if (Si2176_waitForCTS) {
        error_code = Si2176_pollForCTS(context, Si2176_waitForCTS);
        if (error_code) goto exit;
    }

    cmdByteBuffer[0] = Si2176_TUNER_STATUS_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( intack & Si2176_TUNER_STATUS_CMD_INTACK_MASK ) << Si2176_TUNER_STATUS_CMD_INTACK_LSB);

    if (L0_WriteCommandBytes(context->i2c, 2, cmdByteBuffer) != 2) error_code = ERROR_Si2176_SENDING_COMMAND;

    if (!error_code && Si2176_waitForResponse) {
        error_code = Si2176_pollForResponse(context, Si2176_waitForResponse, 12, rspByteBuffer, &status);
        rsp->tuner_status.STATUS = &status;
        if (!error_code)  {
          rsp->tuner_status.tcint    =   (( ( (rspByteBuffer[1]  )) >> Si2176_TUNER_STATUS_RESPONSE_TCINT_LSB    ) & Si2176_TUNER_STATUS_RESPONSE_TCINT_MASK    );
          rsp->tuner_status.rssilint =   (( ( (rspByteBuffer[1]  )) >> Si2176_TUNER_STATUS_RESPONSE_RSSILINT_LSB ) & Si2176_TUNER_STATUS_RESPONSE_RSSILINT_MASK );
          rsp->tuner_status.rssihint =   (( ( (rspByteBuffer[1]  )) >> Si2176_TUNER_STATUS_RESPONSE_RSSIHINT_LSB ) & Si2176_TUNER_STATUS_RESPONSE_RSSIHINT_MASK );
          rsp->tuner_status.tc       =   (( ( (rspByteBuffer[2]  )) >> Si2176_TUNER_STATUS_RESPONSE_TC_LSB       ) & Si2176_TUNER_STATUS_RESPONSE_TC_MASK       );
          rsp->tuner_status.rssil    =   (( ( (rspByteBuffer[2]  )) >> Si2176_TUNER_STATUS_RESPONSE_RSSIL_LSB    ) & Si2176_TUNER_STATUS_RESPONSE_RSSIL_MASK    );
          rsp->tuner_status.rssih    =   (( ( (rspByteBuffer[2]  )) >> Si2176_TUNER_STATUS_RESPONSE_RSSIH_LSB    ) & Si2176_TUNER_STATUS_RESPONSE_RSSIH_MASK    );
          rsp->tuner_status.rssi     = (((( ( (rspByteBuffer[3]  )) >> Si2176_TUNER_STATUS_RESPONSE_RSSI_LSB     ) & Si2176_TUNER_STATUS_RESPONSE_RSSI_MASK) <<Si2176_TUNER_STATUS_RESPONSE_RSSI_SHIFT ) >>Si2176_TUNER_STATUS_RESPONSE_RSSI_SHIFT     );
          rsp->tuner_status.freq     =   (( ( (rspByteBuffer[4]  ) | (rspByteBuffer[5]  << 8 ) | (rspByteBuffer[6]  << 16 ) | (rspByteBuffer[7]  << 24 )) >> Si2176_TUNER_STATUS_RESPONSE_FREQ_LSB     ) & Si2176_TUNER_STATUS_RESPONSE_FREQ_MASK     );
          rsp->tuner_status.mode     =   (( ( (rspByteBuffer[8]  )) >> Si2176_TUNER_STATUS_RESPONSE_MODE_LSB     ) & Si2176_TUNER_STATUS_RESPONSE_MODE_MASK     );
          rsp->tuner_status.vco_code = (((( ( (rspByteBuffer[10] ) | (rspByteBuffer[11] << 8 )) >> Si2176_TUNER_STATUS_RESPONSE_VCO_CODE_LSB ) & Si2176_TUNER_STATUS_RESPONSE_VCO_CODE_MASK) <<Si2176_TUNER_STATUS_RESPONSE_VCO_CODE_SHIFT ) >>Si2176_TUNER_STATUS_RESPONSE_VCO_CODE_SHIFT );
        }
    }
  exit:
    return error_code;
}
#endif /* Si2176_TUNER_STATUS_CMD */
#ifdef    Si2176_TUNER_TUNE_FREQ_CMD
 /*---------------------------------------------------*/
/* Si2176_TUNER_TUNE_FREQ COMMAND                  */
/*---------------------------------------------------*/
 unsigned char  Si2176_L1_TUNER_TUNE_FREQ           (L1_Si2176_Context *context, unsigned char Si2176_waitForCTS, unsigned char Si2176_waitForResponse,
                                                                                      unsigned char   mode,
                                                                                      unsigned long   freq,
                                                                                      Si2176_CmdReplyObj *rsp)
{
    unsigned char error_code = 0;
    unsigned char cmdByteBuffer[8];
    unsigned char rspByteBuffer[1];

  #ifdef   DEBUG_RANGE_CHECK
    if ( (mode > Si2176_TUNER_TUNE_FREQ_CMD_MODE_MAX)
      || (freq > Si2176_TUNER_TUNE_FREQ_CMD_FREQ_MAX)  || (freq < Si2176_TUNER_TUNE_FREQ_CMD_FREQ_MIN) )
    return ERROR_Si2176_PARAMETER_OUT_OF_RANGE;
  #endif /* DEBUG_RANGE_CHECK */

    if (Si2176_waitForCTS) {
        error_code = Si2176_pollForCTS(context, Si2176_waitForCTS);
        if (error_code) goto exit;
    }

    cmdByteBuffer[0] = Si2176_TUNER_TUNE_FREQ_CMD;
    cmdByteBuffer[1] = (unsigned char) ( ( mode & Si2176_TUNER_TUNE_FREQ_CMD_MODE_MASK ) << Si2176_TUNER_TUNE_FREQ_CMD_MODE_LSB);
    cmdByteBuffer[2] = (unsigned char)0x00;
    cmdByteBuffer[3] = (unsigned char)0x00;
    cmdByteBuffer[4] = (unsigned char) ( ( freq & Si2176_TUNER_TUNE_FREQ_CMD_FREQ_MASK ) << Si2176_TUNER_TUNE_FREQ_CMD_FREQ_LSB);
    cmdByteBuffer[5] = (unsigned char) ((( freq & Si2176_TUNER_TUNE_FREQ_CMD_FREQ_MASK ) << Si2176_TUNER_TUNE_FREQ_CMD_FREQ_LSB)>>8);
    cmdByteBuffer[6] = (unsigned char) ((( freq & Si2176_TUNER_TUNE_FREQ_CMD_FREQ_MASK ) << Si2176_TUNER_TUNE_FREQ_CMD_FREQ_LSB)>>16);
    cmdByteBuffer[7] = (unsigned char) ((( freq & Si2176_TUNER_TUNE_FREQ_CMD_FREQ_MASK ) << Si2176_TUNER_TUNE_FREQ_CMD_FREQ_LSB)>>24);

    if (L0_WriteCommandBytes(context->i2c, 8, cmdByteBuffer) != 8) error_code = ERROR_Si2176_SENDING_COMMAND;

    if (!error_code && Si2176_waitForResponse) {
        error_code = Si2176_pollForResponse(context, Si2176_waitForResponse, 1, rspByteBuffer, &status);
        rsp->tuner_tune_freq.STATUS = &status;
    }
  exit:
    return error_code;
}
#endif /* Si2176_TUNER_TUNE_FREQ_CMD */
/* _commands_insertion_point */

/* _send_command2_insertion_start */

  /* --------------------------------------------*/
  /* SEND_COMMAND2 FUNCTION                      */
  /* --------------------------------------------*/
 unsigned char    Si2176_L1_SendCommand2(L1_Si2176_Context *api, int cmd, Si2176_CmdObj *c, unsigned char wait_for_cts, unsigned char wait_for_response, Si2176_CmdReplyObj *rsp) {
    switch (cmd) {
    #ifdef        Si2176_AGC_OVERRIDE_CMD
     case         Si2176_AGC_OVERRIDE_CMD:
       return Si2176_L1_AGC_OVERRIDE (api, wait_for_cts, wait_for_response, c->agc_override.force_max_gain, c->agc_override.force_top_gain, rsp);
     break;
    #endif /*     Si2176_AGC_OVERRIDE_CMD */
    #ifdef        Si2176_ATV_RESTART_CMD
     case         Si2176_ATV_RESTART_CMD:
       return Si2176_L1_ATV_RESTART (api, wait_for_cts, wait_for_response, c->atv_restart.mode, rsp);
     break;
    #endif /*     Si2176_ATV_RESTART_CMD */
    #ifdef        Si2176_ATV_STATUS_CMD
     case         Si2176_ATV_STATUS_CMD:
       return Si2176_L1_ATV_STATUS (api, wait_for_cts, wait_for_response, c->atv_status.intack, rsp);
     break;
    #endif /*     Si2176_ATV_STATUS_CMD */
    #ifdef        Si2176_CONFIG_PINS_CMD
     case         Si2176_CONFIG_PINS_CMD:
       return Si2176_L1_CONFIG_PINS (api, wait_for_cts, wait_for_response, c->config_pins.gpio1_mode, c->config_pins.gpio1_read, c->config_pins.gpio2_mode, c->config_pins.gpio2_read, c->config_pins.gpio3_mode, c->config_pins.gpio3_read, c->config_pins.bclk1_mode, c->config_pins.bclk1_read, c->config_pins.xout_mode, rsp);
     break;
    #endif /*     Si2176_CONFIG_PINS_CMD */
    #ifdef        Si2176_DTV_RESTART_CMD
     case         Si2176_DTV_RESTART_CMD:
       return Si2176_L1_DTV_RESTART (api, wait_for_cts, wait_for_response, rsp);
     break;
    #endif /*     Si2176_DTV_RESTART_CMD */
    #ifdef        Si2176_DTV_STATUS_CMD
     case         Si2176_DTV_STATUS_CMD:
       return Si2176_L1_DTV_STATUS (api, wait_for_cts, wait_for_response, c->dtv_status.intack, rsp);
     break;
    #endif /*     Si2176_DTV_STATUS_CMD */
    #ifdef        Si2176_EXIT_BOOTLOADER_CMD
     case         Si2176_EXIT_BOOTLOADER_CMD:
       return Si2176_L1_EXIT_BOOTLOADER (api, wait_for_cts, wait_for_response, c->exit_bootloader.func, c->exit_bootloader.ctsien, rsp);
     break;
    #endif /*     Si2176_EXIT_BOOTLOADER_CMD */
    #ifdef        Si2176_FINE_TUNE_CMD
     case         Si2176_FINE_TUNE_CMD:
       return Si2176_L1_FINE_TUNE (api, wait_for_cts, wait_for_response, c->fine_tune.reserved, c->fine_tune.offset_500hz, rsp);
     break;
    #endif /*     Si2176_FINE_TUNE_CMD */
    #ifdef        Si2176_GET_PROPERTY_CMD
     case         Si2176_GET_PROPERTY_CMD:
       return Si2176_L1_GET_PROPERTY (api, wait_for_cts, wait_for_response, c->get_property.reserved, c->get_property.prop, rsp);
     break;
    #endif /*     Si2176_GET_PROPERTY_CMD */
    #ifdef        Si2176_GET_REV_CMD
     case         Si2176_GET_REV_CMD:
       return Si2176_L1_GET_REV (api, wait_for_cts, wait_for_response, rsp);
     break;
    #endif /*     Si2176_GET_REV_CMD */
    #ifdef        Si2176_PART_INFO_CMD
     case         Si2176_PART_INFO_CMD:
       return Si2176_L1_PART_INFO (api, wait_for_cts, wait_for_response, rsp);
     break;
    #endif /*     Si2176_PART_INFO_CMD */
    #ifdef        Si2176_POWER_DOWN_CMD
     case         Si2176_POWER_DOWN_CMD:
       return Si2176_L1_POWER_DOWN (api, wait_for_cts, wait_for_response, rsp);
     break;
    #endif /*     Si2176_POWER_DOWN_CMD */
    #ifdef        Si2176_POWER_UP_CMD
     case         Si2176_POWER_UP_CMD:
       return Si2176_L1_POWER_UP (api, wait_for_cts, wait_for_response, c->power_up.subcode, c->power_up.reserved1, c->power_up.reserved2, c->power_up.reserved3, c->power_up.clock_mode, c->power_up.clock_freq, c->power_up.addr_mode, c->power_up.func, c->power_up.ctsien, c->power_up.wake_up, rsp);
     break;
    #endif /*     Si2176_POWER_UP_CMD */
    #ifdef        Si2176_SET_PROPERTY_CMD
     case         Si2176_SET_PROPERTY_CMD:
       return Si2176_L1_SET_PROPERTY (api, wait_for_cts, wait_for_response, c->set_property.reserved, c->set_property.prop, c->set_property.data, rsp);
     break;
    #endif /*     Si2176_SET_PROPERTY_CMD */
    #ifdef        Si2176_STANDBY_CMD
     case         Si2176_STANDBY_CMD:
       return Si2176_L1_STANDBY (api, wait_for_cts, wait_for_response, rsp);
     break;
    #endif /*     Si2176_STANDBY_CMD */
    #ifdef        Si2176_TUNER_STATUS_CMD
     case         Si2176_TUNER_STATUS_CMD:
       return Si2176_L1_TUNER_STATUS (api, wait_for_cts, wait_for_response, c->tuner_status.intack, rsp);
     break;
    #endif /*     Si2176_TUNER_STATUS_CMD */
    #ifdef        Si2176_TUNER_TUNE_FREQ_CMD
     case         Si2176_TUNER_TUNE_FREQ_CMD:
       return Si2176_L1_TUNER_TUNE_FREQ (api, wait_for_cts, wait_for_response, c->tuner_tune_freq.mode, c->tuner_tune_freq.freq, rsp);
     break;
    #endif /*     Si2176_TUNER_TUNE_FREQ_CMD */
   default : break;
    }
    return 0;
  }
  /* _send_command2_insertion_point */

#ifdef    Si2176_GET_COMMAND_STRINGS
/* _get_command_response_string_insertion_start */
#include <string.h>
  /* --------------------------------------------*/
  /* GET_COMMAND_RESPONSE_STRING FUNCTION        */
  /* --------------------------------------------*/
 unsigned char    Si2176_L1_GetCommandResponseString(L1_Si2176_Context *api, int cmd, Si2176_CmdReplyObj *rsp, char **separator, char *msg) {
    switch (cmd) {
    #ifdef        Si2176_AGC_OVERRIDE_CMD
     case         Si2176_AGC_OVERRIDE_CMD:
      sprintf(msg,"AGC_OVERRIDE ");
       strcat(msg,*separator); strcat(msg,"-TUNINT ");
           if  (rsp->agc_override.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->agc_override.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                sprintf(msg,"%s%d", msg, rsp->agc_override.STATUS->tunint);
       strcat(msg,*separator); strcat(msg,"-ATVINT ");
           if  (rsp->agc_override.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->agc_override.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                sprintf(msg,"%s%d", msg, rsp->agc_override.STATUS->atvint);
       strcat(msg,*separator); strcat(msg,"-DTVINT ");
           if  (rsp->agc_override.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->agc_override.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                sprintf(msg,"%s%d", msg, rsp->agc_override.STATUS->dtvint);
       strcat(msg,*separator); strcat(msg,"-ERR    ");
           if  (rsp->agc_override.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (rsp->agc_override.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                sprintf(msg,"%s%d", msg, rsp->agc_override.STATUS->err);
       strcat(msg,*separator); strcat(msg,"-CTS    ");
           if  (rsp->agc_override.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (rsp->agc_override.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                sprintf(msg,"%s%d", msg, rsp->agc_override.STATUS->cts);
     break;
    #endif /*     Si2176_AGC_OVERRIDE_CMD */
    #ifdef        Si2176_ATV_RESTART_CMD
     case         Si2176_ATV_RESTART_CMD:
      sprintf(msg,"ATV_RESTART ");
       strcat(msg,*separator); strcat(msg,"-TUNINT ");
           if  (rsp->atv_restart.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->atv_restart.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                               sprintf(msg,"%s%d", msg, rsp->atv_restart.STATUS->tunint);
       strcat(msg,*separator); strcat(msg,"-ATVINT ");
           if  (rsp->atv_restart.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->atv_restart.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                               sprintf(msg,"%s%d", msg, rsp->atv_restart.STATUS->atvint);
       strcat(msg,*separator); strcat(msg,"-DTVINT ");
           if  (rsp->atv_restart.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->atv_restart.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                               sprintf(msg,"%s%d", msg, rsp->atv_restart.STATUS->dtvint);
       strcat(msg,*separator); strcat(msg,"-ERR    ");
           if  (rsp->atv_restart.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (rsp->atv_restart.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                               sprintf(msg,"%s%d", msg, rsp->atv_restart.STATUS->err);
       strcat(msg,*separator); strcat(msg,"-CTS    ");
           if  (rsp->atv_restart.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (rsp->atv_restart.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                               sprintf(msg,"%s%d", msg, rsp->atv_restart.STATUS->cts);
     break;
    #endif /*     Si2176_ATV_RESTART_CMD */
    #ifdef        Si2176_ATV_STATUS_CMD
     case         Si2176_ATV_STATUS_CMD:
      sprintf(msg,"ATV_STATUS ");
       strcat(msg,*separator); strcat(msg,"-TUNINT           ");
           if  (rsp->atv_status.STATUS->tunint           ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->atv_status.STATUS->tunint           ==     1) strcat(msg,"TRIGGERED    ");
      else                                                        sprintf(msg,"%s%d", msg, rsp->atv_status.STATUS->tunint);
       strcat(msg,*separator); strcat(msg,"-ATVINT           ");
           if  (rsp->atv_status.STATUS->atvint           ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->atv_status.STATUS->atvint           ==     1) strcat(msg,"TRIGGERED    ");
      else                                                        sprintf(msg,"%s%d", msg, rsp->atv_status.STATUS->atvint);
       strcat(msg,*separator); strcat(msg,"-DTVINT           ");
           if  (rsp->atv_status.STATUS->dtvint           ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->atv_status.STATUS->dtvint           ==     1) strcat(msg,"TRIGGERED    ");
      else                                                        sprintf(msg,"%s%d", msg, rsp->atv_status.STATUS->dtvint);
       strcat(msg,*separator); strcat(msg,"-ERR              ");
           if  (rsp->atv_status.STATUS->err              ==     1) strcat(msg,"ERROR   ");
      else if  (rsp->atv_status.STATUS->err              ==     0) strcat(msg,"NO_ERROR");
      else                                                        sprintf(msg,"%s%d", msg, rsp->atv_status.STATUS->err);
       strcat(msg,*separator); strcat(msg,"-CTS              ");
           if  (rsp->atv_status.STATUS->cts              ==     1) strcat(msg,"COMPLETED");
      else if  (rsp->atv_status.STATUS->cts              ==     0) strcat(msg,"WAIT     ");
      else                                                        sprintf(msg,"%s%d", msg, rsp->atv_status.STATUS->cts);
       strcat(msg,*separator); strcat(msg,"-CHLINT           ");
           if  (rsp->atv_status.chlint           ==     1) strcat(msg,"CHANGED  ");
      else if  (rsp->atv_status.chlint           ==     0) strcat(msg,"NO_CHANGE");
      else                                                sprintf(msg,"%s%d", msg, rsp->atv_status.chlint);
       strcat(msg,*separator); strcat(msg,"-PCLINT           ");
           if  (rsp->atv_status.pclint           ==     1) strcat(msg,"CHANGED  ");
      else if  (rsp->atv_status.pclint           ==     0) strcat(msg,"NO_CHANGE");
      else                                                sprintf(msg,"%s%d", msg, rsp->atv_status.pclint);
       strcat(msg,*separator); strcat(msg,"-DLINT            ");
           if  (rsp->atv_status.dlint            ==     1) strcat(msg,"CHANGED  ");
      else if  (rsp->atv_status.dlint            ==     0) strcat(msg,"NO_CHANGE");
      else                                                sprintf(msg,"%s%d", msg, rsp->atv_status.dlint);
       strcat(msg,*separator); strcat(msg,"-SNRLINT          ");
           if  (rsp->atv_status.snrlint          ==     1) strcat(msg,"CHANGED  ");
      else if  (rsp->atv_status.snrlint          ==     0) strcat(msg,"NO_CHANGE");
      else                                                sprintf(msg,"%s%d", msg, rsp->atv_status.snrlint);
       strcat(msg,*separator); strcat(msg,"-SNRHINT          ");
           if  (rsp->atv_status.snrhint          ==     1) strcat(msg,"CHANGED  ");
      else if  (rsp->atv_status.snrhint          ==     0) strcat(msg,"NO_CHANGE");
      else                                                sprintf(msg,"%s%d", msg, rsp->atv_status.snrhint);
       strcat(msg,*separator); strcat(msg,"-CHL              ");
           if  (rsp->atv_status.chl              ==     1) strcat(msg,"CHANNEL   ");
      else if  (rsp->atv_status.chl              ==     0) strcat(msg,"NO_CHANNEL");
      else                                                sprintf(msg,"%s%d", msg, rsp->atv_status.chl);
       strcat(msg,*separator); strcat(msg,"-PCL              ");
           if  (rsp->atv_status.pcl              ==     1) strcat(msg,"LOCKED ");
      else if  (rsp->atv_status.pcl              ==     0) strcat(msg,"NO_LOCK");
      else                                                sprintf(msg,"%s%d", msg, rsp->atv_status.pcl);
       strcat(msg,*separator); strcat(msg,"-DL               ");
           if  (rsp->atv_status.dl               ==     1) strcat(msg,"LOCKED ");
      else if  (rsp->atv_status.dl               ==     0) strcat(msg,"NO_LOCK");
      else                                                sprintf(msg,"%s%d", msg, rsp->atv_status.dl);
       strcat(msg,*separator); strcat(msg,"-SNRL             ");
           if  (rsp->atv_status.snrl             ==     1) strcat(msg,"SNR_LOW    ");
      else if  (rsp->atv_status.snrl             ==     0) strcat(msg,"SNR_NOT_LOW");
      else                                                sprintf(msg,"%s%d", msg, rsp->atv_status.snrl);
       strcat(msg,*separator); strcat(msg,"-SNRH             ");
           if  (rsp->atv_status.snrh             ==     1) strcat(msg,"SNR_HIGH    ");
      else if  (rsp->atv_status.snrh             ==     0) strcat(msg,"SNR_NOT_HIGH");
      else                                                sprintf(msg,"%s%d", msg, rsp->atv_status.snrh);
       strcat(msg,*separator); strcat(msg,"-VIDEO_SNR        "); sprintf(msg,"%s%d", msg, rsp->atv_status.video_snr);
       strcat(msg,*separator); strcat(msg,"-AFC_FREQ         "); sprintf(msg,"%s%d", msg, rsp->atv_status.afc_freq);
       strcat(msg,*separator); strcat(msg,"-VIDEO_SC_SPACING "); sprintf(msg,"%s%d", msg, rsp->atv_status.video_sc_spacing);
       strcat(msg,*separator); strcat(msg,"-VIDEO_SYS        ");
           if  (rsp->atv_status.video_sys        ==     0) strcat(msg,"B ");
      else if  (rsp->atv_status.video_sys        ==     5) strcat(msg,"DK");
      else if  (rsp->atv_status.video_sys        ==     1) strcat(msg,"GH");
      else if  (rsp->atv_status.video_sys        ==     4) strcat(msg,"I ");
      else if  (rsp->atv_status.video_sys        ==     6) strcat(msg,"L ");
      else if  (rsp->atv_status.video_sys        ==     7) strcat(msg,"LP");
      else if  (rsp->atv_status.video_sys        ==     2) strcat(msg,"M ");
      else if  (rsp->atv_status.video_sys        ==     3) strcat(msg,"N ");
      else                                                sprintf(msg,"%s%d", msg, rsp->atv_status.video_sys);
       strcat(msg,*separator); strcat(msg,"-COLOR            ");
           if  (rsp->atv_status.color            ==     0) strcat(msg,"PAL_NTSC");
      else if  (rsp->atv_status.color            ==     1) strcat(msg,"SECAM   ");
      else                                                sprintf(msg,"%s%d", msg, rsp->atv_status.color);
       strcat(msg,*separator); strcat(msg,"-TRANS            ");
           if  (rsp->atv_status.trans            ==     1) strcat(msg,"CABLE      ");
      else if  (rsp->atv_status.trans            ==     0) strcat(msg,"TERRESTRIAL");
      else                                                sprintf(msg,"%s%d", msg, rsp->atv_status.trans);
       strcat(msg,*separator); strcat(msg,"-AUDIO_SYS        ");
           if  (rsp->atv_status.audio_sys        ==     3) strcat(msg,"A2        ");
      else if  (rsp->atv_status.audio_sys        ==     4) strcat(msg,"A2_DK2    ");
      else if  (rsp->atv_status.audio_sys        ==     5) strcat(msg,"A2_DK3    ");
      else if  (rsp->atv_status.audio_sys        ==     9) strcat(msg,"A2_DK4    ");
      else if  (rsp->atv_status.audio_sys        ==     6) strcat(msg,"BTSC      ");
      else if  (rsp->atv_status.audio_sys        ==     7) strcat(msg,"EIAJ      ");
      else if  (rsp->atv_status.audio_sys        ==     1) strcat(msg,"MONO      ");
      else if  (rsp->atv_status.audio_sys        ==     2) strcat(msg,"MONO_NICAM");
      else if  (rsp->atv_status.audio_sys        ==     0) strcat(msg,"RSVD      ");
      else if  (rsp->atv_status.audio_sys        ==     8) strcat(msg,"SCAN      ");
      else if  (rsp->atv_status.audio_sys        ==    10) strcat(msg,"WIDE_SCAN ");
      else                                                sprintf(msg,"%s%d", msg, rsp->atv_status.audio_sys);
       strcat(msg,*separator); strcat(msg,"-AUDIO_DEMOD_MODE ");
           if  (rsp->atv_status.audio_demod_mode ==     1) strcat(msg,"AM ");
      else if  (rsp->atv_status.audio_demod_mode ==     2) strcat(msg,"FM1");
      else if  (rsp->atv_status.audio_demod_mode ==     3) strcat(msg,"FM2");
      else if  (rsp->atv_status.audio_demod_mode ==     0) strcat(msg,"SIF");
      else                                                sprintf(msg,"%s%d", msg, rsp->atv_status.audio_demod_mode);
       strcat(msg,*separator); strcat(msg,"-AUDIO_CHAN_BW    ");
           if  (rsp->atv_status.audio_chan_bw    ==     3) strcat(msg,"12X_OVERMOD   ");
      else if  (rsp->atv_status.audio_chan_bw    ==     8) strcat(msg,"150_KHZ_OFFSET");
      else if  (rsp->atv_status.audio_chan_bw    ==     5) strcat(msg,"15_KHZ_OFFSET ");
      else if  (rsp->atv_status.audio_chan_bw    ==     6) strcat(msg,"30_KHZ_OFFSET ");
      else if  (rsp->atv_status.audio_chan_bw    ==     1) strcat(msg,"4X_OVERMOD    ");
      else if  (rsp->atv_status.audio_chan_bw    ==     7) strcat(msg,"75_KHZ_OFFSET ");
      else if  (rsp->atv_status.audio_chan_bw    ==     4) strcat(msg,"7P5_KHZ_OFFSET");
      else if  (rsp->atv_status.audio_chan_bw    ==     2) strcat(msg,"8X_OVERMOD    ");
      else if  (rsp->atv_status.audio_chan_bw    ==     0) strcat(msg,"RSVD          ");
      else                                                sprintf(msg,"%s%d", msg, rsp->atv_status.audio_chan_bw);
     break;
    #endif /*     Si2176_ATV_STATUS_CMD */
    #ifdef        Si2176_CONFIG_PINS_CMD
     case         Si2176_CONFIG_PINS_CMD:
      sprintf(msg,"CONFIG_PINS ");
       strcat(msg,*separator); strcat(msg,"-TUNINT      ");
           if  (rsp->config_pins.STATUS->tunint      ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->config_pins.STATUS->tunint      ==     1) strcat(msg,"TRIGGERED    ");
      else                                                    sprintf(msg,"%s%d", msg, rsp->config_pins.STATUS->tunint);
       strcat(msg,*separator); strcat(msg,"-ATVINT      ");
           if  (rsp->config_pins.STATUS->atvint      ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->config_pins.STATUS->atvint      ==     1) strcat(msg,"TRIGGERED    ");
      else                                                    sprintf(msg,"%s%d", msg, rsp->config_pins.STATUS->atvint);
       strcat(msg,*separator); strcat(msg,"-DTVINT      ");
           if  (rsp->config_pins.STATUS->dtvint      ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->config_pins.STATUS->dtvint      ==     1) strcat(msg,"TRIGGERED    ");
      else                                                    sprintf(msg,"%s%d", msg, rsp->config_pins.STATUS->dtvint);
       strcat(msg,*separator); strcat(msg,"-ERR         ");
           if  (rsp->config_pins.STATUS->err         ==     1) strcat(msg,"ERROR   ");
      else if  (rsp->config_pins.STATUS->err         ==     0) strcat(msg,"NO_ERROR");
      else                                                    sprintf(msg,"%s%d", msg, rsp->config_pins.STATUS->err);
       strcat(msg,*separator); strcat(msg,"-CTS         ");
           if  (rsp->config_pins.STATUS->cts         ==     1) strcat(msg,"COMPLETED");
      else if  (rsp->config_pins.STATUS->cts         ==     0) strcat(msg,"WAIT     ");
      else                                                    sprintf(msg,"%s%d", msg, rsp->config_pins.STATUS->cts);
       strcat(msg,*separator); strcat(msg,"-GPIO1_MODE  ");
           if  (rsp->config_pins.gpio1_mode  ==     1) strcat(msg,"DISABLE");
      else if  (rsp->config_pins.gpio1_mode  ==     2) strcat(msg,"DRIVE_0");
      else if  (rsp->config_pins.gpio1_mode  ==     3) strcat(msg,"DRIVE_1");
      else                                            sprintf(msg,"%s%d", msg, rsp->config_pins.gpio1_mode);
       strcat(msg,*separator); strcat(msg,"-GPIO1_STATE ");
           if  (rsp->config_pins.gpio1_state ==     0) strcat(msg,"READ_0");
      else if  (rsp->config_pins.gpio1_state ==     1) strcat(msg,"READ_1");
      else                                            sprintf(msg,"%s%d", msg, rsp->config_pins.gpio1_state);
       strcat(msg,*separator); strcat(msg,"-GPIO2_MODE  ");
           if  (rsp->config_pins.gpio2_mode  ==     1) strcat(msg,"DISABLE");
      else if  (rsp->config_pins.gpio2_mode  ==     2) strcat(msg,"DRIVE_0");
      else if  (rsp->config_pins.gpio2_mode  ==     3) strcat(msg,"DRIVE_1");
      else                                            sprintf(msg,"%s%d", msg, rsp->config_pins.gpio2_mode);
       strcat(msg,*separator); strcat(msg,"-GPIO2_STATE ");
           if  (rsp->config_pins.gpio2_state ==     0) strcat(msg,"READ_0");
      else if  (rsp->config_pins.gpio2_state ==     1) strcat(msg,"READ_1");
      else                                            sprintf(msg,"%s%d", msg, rsp->config_pins.gpio2_state);
       strcat(msg,*separator); strcat(msg,"-GPIO3_MODE  ");
           if  (rsp->config_pins.gpio3_mode  ==     1) strcat(msg,"DISABLE");
      else if  (rsp->config_pins.gpio3_mode  ==     2) strcat(msg,"DRIVE_0");
      else if  (rsp->config_pins.gpio3_mode  ==     3) strcat(msg,"DRIVE_1");
      else                                            sprintf(msg,"%s%d", msg, rsp->config_pins.gpio3_mode);
       strcat(msg,*separator); strcat(msg,"-GPIO3_STATE ");
           if  (rsp->config_pins.gpio3_state ==     0) strcat(msg,"READ_0");
      else if  (rsp->config_pins.gpio3_state ==     1) strcat(msg,"READ_1");
      else                                            sprintf(msg,"%s%d", msg, rsp->config_pins.gpio3_state);
       strcat(msg,*separator); strcat(msg,"-BCLK1_MODE  ");
           if  (rsp->config_pins.bclk1_mode  ==     1) strcat(msg,"DISABLE  ");
      else if  (rsp->config_pins.bclk1_mode  ==    10) strcat(msg,"XOUT     ");
      else if  (rsp->config_pins.bclk1_mode  ==    11) strcat(msg,"XOUT_HIGH");
      else                                            sprintf(msg,"%s%d", msg, rsp->config_pins.bclk1_mode);
       strcat(msg,*separator); strcat(msg,"-BCLK1_STATE ");
           if  (rsp->config_pins.bclk1_state ==     0) strcat(msg,"READ_0");
      else if  (rsp->config_pins.bclk1_state ==     1) strcat(msg,"READ_1");
      else                                            sprintf(msg,"%s%d", msg, rsp->config_pins.bclk1_state);
       strcat(msg,*separator); strcat(msg,"-XOUT_MODE   ");
           if  (rsp->config_pins.xout_mode   ==     1) strcat(msg,"DISABLE");
      else if  (rsp->config_pins.xout_mode   ==    10) strcat(msg,"XOUT   ");
      else                                            sprintf(msg,"%s%d", msg, rsp->config_pins.xout_mode);
     break;
    #endif /*     Si2176_CONFIG_PINS_CMD */
    #ifdef        Si2176_DTV_RESTART_CMD
     case         Si2176_DTV_RESTART_CMD:
      sprintf(msg,"DTV_RESTART ");
       strcat(msg,*separator); strcat(msg,"-TUNINT ");
           if  (rsp->dtv_restart.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->dtv_restart.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                               sprintf(msg,"%s%d", msg, rsp->dtv_restart.STATUS->tunint);
       strcat(msg,*separator); strcat(msg,"-ATVINT ");
           if  (rsp->dtv_restart.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->dtv_restart.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                               sprintf(msg,"%s%d", msg, rsp->dtv_restart.STATUS->atvint);
       strcat(msg,*separator); strcat(msg,"-DTVINT ");
           if  (rsp->dtv_restart.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->dtv_restart.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                               sprintf(msg,"%s%d", msg, rsp->dtv_restart.STATUS->dtvint);
       strcat(msg,*separator); strcat(msg,"-ERR    ");
           if  (rsp->dtv_restart.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (rsp->dtv_restart.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                               sprintf(msg,"%s%d", msg, rsp->dtv_restart.STATUS->err);
       strcat(msg,*separator); strcat(msg,"-CTS    ");
           if  (rsp->dtv_restart.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (rsp->dtv_restart.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                               sprintf(msg,"%s%d", msg, rsp->dtv_restart.STATUS->cts);
     break;
    #endif /*     Si2176_DTV_RESTART_CMD */
    #ifdef        Si2176_DTV_STATUS_CMD
     case         Si2176_DTV_STATUS_CMD:
      sprintf(msg,"DTV_STATUS ");
       strcat(msg,*separator); strcat(msg,"-TUNINT     ");
           if  (rsp->dtv_status.STATUS->tunint     ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->dtv_status.STATUS->tunint     ==     1) strcat(msg,"TRIGGERED    ");
      else                                                  sprintf(msg,"%s%d", msg, rsp->dtv_status.STATUS->tunint);
       strcat(msg,*separator); strcat(msg,"-ATVINT     ");
           if  (rsp->dtv_status.STATUS->atvint     ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->dtv_status.STATUS->atvint     ==     1) strcat(msg,"TRIGGERED    ");
      else                                                  sprintf(msg,"%s%d", msg, rsp->dtv_status.STATUS->atvint);
       strcat(msg,*separator); strcat(msg,"-DTVINT     ");
           if  (rsp->dtv_status.STATUS->dtvint     ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->dtv_status.STATUS->dtvint     ==     1) strcat(msg,"TRIGGERED    ");
      else                                                  sprintf(msg,"%s%d", msg, rsp->dtv_status.STATUS->dtvint);
       strcat(msg,*separator); strcat(msg,"-ERR        ");
           if  (rsp->dtv_status.STATUS->err        ==     1) strcat(msg,"ERROR   ");
      else if  (rsp->dtv_status.STATUS->err        ==     0) strcat(msg,"NO_ERROR");
      else                                                  sprintf(msg,"%s%d", msg, rsp->dtv_status.STATUS->err);
       strcat(msg,*separator); strcat(msg,"-CTS        ");
           if  (rsp->dtv_status.STATUS->cts        ==     1) strcat(msg,"COMPLETED");
      else if  (rsp->dtv_status.STATUS->cts        ==     0) strcat(msg,"WAIT     ");
      else                                                  sprintf(msg,"%s%d", msg, rsp->dtv_status.STATUS->cts);
       strcat(msg,*separator); strcat(msg,"-CHLINT     ");
           if  (rsp->dtv_status.chlint     ==     1) strcat(msg,"CHANGED  ");
      else if  (rsp->dtv_status.chlint     ==     0) strcat(msg,"NO_CHANGE");
      else                                          sprintf(msg,"%s%d", msg, rsp->dtv_status.chlint);
       strcat(msg,*separator); strcat(msg,"-CHL        ");
           if  (rsp->dtv_status.chl        ==     1) strcat(msg,"CHANNEL   ");
      else if  (rsp->dtv_status.chl        ==     0) strcat(msg,"NO_CHANNEL");
      else                                          sprintf(msg,"%s%d", msg, rsp->dtv_status.chl);
       strcat(msg,*separator); strcat(msg,"-BW         ");
           if  (rsp->dtv_status.bw         ==     6) strcat(msg,"BW_6MHZ");
      else if  (rsp->dtv_status.bw         ==     7) strcat(msg,"BW_7MHZ");
      else if  (rsp->dtv_status.bw         ==     8) strcat(msg,"BW_8MHZ");
      else                                          sprintf(msg,"%s%d", msg, rsp->dtv_status.bw);
       strcat(msg,*separator); strcat(msg,"-MODULATION ");
           if  (rsp->dtv_status.modulation ==     0) strcat(msg,"ATSC  ");
      else if  (rsp->dtv_status.modulation ==    15) strcat(msg,"CW    ");
      else if  (rsp->dtv_status.modulation ==     6) strcat(msg,"DTMB  ");
      else if  (rsp->dtv_status.modulation ==     3) strcat(msg,"DVBC  ");
      else if  (rsp->dtv_status.modulation ==     2) strcat(msg,"DVBT  ");
      else if  (rsp->dtv_status.modulation ==     5) strcat(msg,"ISDBC ");
      else if  (rsp->dtv_status.modulation ==     4) strcat(msg,"ISDBT ");
      else if  (rsp->dtv_status.modulation ==     1) strcat(msg,"QAM_US");
      else                                          sprintf(msg,"%s%d", msg, rsp->dtv_status.modulation);
     break;
    #endif /*     Si2176_DTV_STATUS_CMD */
    #ifdef        Si2176_EXIT_BOOTLOADER_CMD
     case         Si2176_EXIT_BOOTLOADER_CMD:
      sprintf(msg,"EXIT_BOOTLOADER ");
       strcat(msg,*separator); strcat(msg,"-TUNINT ");
           if  (rsp->exit_bootloader.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->exit_bootloader.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                   sprintf(msg,"%s%d", msg, rsp->exit_bootloader.STATUS->tunint);
       strcat(msg,*separator); strcat(msg,"-ATVINT ");
           if  (rsp->exit_bootloader.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->exit_bootloader.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                   sprintf(msg,"%s%d", msg, rsp->exit_bootloader.STATUS->atvint);
       strcat(msg,*separator); strcat(msg,"-DTVINT ");
           if  (rsp->exit_bootloader.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->exit_bootloader.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                   sprintf(msg,"%s%d", msg, rsp->exit_bootloader.STATUS->dtvint);
       strcat(msg,*separator); strcat(msg,"-ERR    ");
           if  (rsp->exit_bootloader.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (rsp->exit_bootloader.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                   sprintf(msg,"%s%d", msg, rsp->exit_bootloader.STATUS->err);
       strcat(msg,*separator); strcat(msg,"-CTS    ");
           if  (rsp->exit_bootloader.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (rsp->exit_bootloader.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                   sprintf(msg,"%s%d", msg, rsp->exit_bootloader.STATUS->cts);
     break;
    #endif /*     Si2176_EXIT_BOOTLOADER_CMD */
    #ifdef        Si2176_FINE_TUNE_CMD
     case         Si2176_FINE_TUNE_CMD:
      sprintf(msg,"FINE_TUNE ");
       strcat(msg,*separator); strcat(msg,"-TUNINT ");
           if  (rsp->fine_tune.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->fine_tune.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                             sprintf(msg,"%s%d", msg, rsp->fine_tune.STATUS->tunint);
       strcat(msg,*separator); strcat(msg,"-ATVINT ");
           if  (rsp->fine_tune.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->fine_tune.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                             sprintf(msg,"%s%d", msg, rsp->fine_tune.STATUS->atvint);
       strcat(msg,*separator); strcat(msg,"-DTVINT ");
           if  (rsp->fine_tune.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->fine_tune.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                             sprintf(msg,"%s%d", msg, rsp->fine_tune.STATUS->dtvint);
       strcat(msg,*separator); strcat(msg,"-ERR    ");
           if  (rsp->fine_tune.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (rsp->fine_tune.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                             sprintf(msg,"%s%d", msg, rsp->fine_tune.STATUS->err);
       strcat(msg,*separator); strcat(msg,"-CTS    ");
           if  (rsp->fine_tune.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (rsp->fine_tune.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                             sprintf(msg,"%s%d", msg, rsp->fine_tune.STATUS->cts);
     break;
    #endif /*     Si2176_FINE_TUNE_CMD */
    #ifdef        Si2176_GET_PROPERTY_CMD
     case         Si2176_GET_PROPERTY_CMD:
      sprintf(msg,"GET_PROPERTY ");
       strcat(msg,*separator); strcat(msg,"-TUNINT   ");
           if  (rsp->get_property.STATUS->tunint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->get_property.STATUS->tunint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                  sprintf(msg,"%s%d", msg, rsp->get_property.STATUS->tunint);
       strcat(msg,*separator); strcat(msg,"-ATVINT   ");
           if  (rsp->get_property.STATUS->atvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->get_property.STATUS->atvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                  sprintf(msg,"%s%d", msg, rsp->get_property.STATUS->atvint);
       strcat(msg,*separator); strcat(msg,"-DTVINT   ");
           if  (rsp->get_property.STATUS->dtvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->get_property.STATUS->dtvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                  sprintf(msg,"%s%d", msg, rsp->get_property.STATUS->dtvint);
       strcat(msg,*separator); strcat(msg,"-ERR      ");
           if  (rsp->get_property.STATUS->err      ==     1) strcat(msg,"ERROR   ");
      else if  (rsp->get_property.STATUS->err      ==     0) strcat(msg,"NO_ERROR");
      else                                                  sprintf(msg,"%s%d", msg, rsp->get_property.STATUS->err);
       strcat(msg,*separator); strcat(msg,"-CTS      ");
           if  (rsp->get_property.STATUS->cts      ==     1) strcat(msg,"COMPLETED");
      else if  (rsp->get_property.STATUS->cts      ==     0) strcat(msg,"WAIT     ");
      else                                                  sprintf(msg,"%s%d", msg, rsp->get_property.STATUS->cts);
       strcat(msg,*separator); strcat(msg,"-RESERVED "); sprintf(msg,"%s%d", msg, rsp->get_property.reserved);
       strcat(msg,*separator); strcat(msg,"-DATA     "); sprintf(msg,"%s%d", msg, rsp->get_property.data);
     break;
    #endif /*     Si2176_GET_PROPERTY_CMD */
    #ifdef        Si2176_GET_REV_CMD
     case         Si2176_GET_REV_CMD:
      sprintf(msg,"GET_REV ");
       strcat(msg,*separator); strcat(msg,"-TUNINT   ");
           if  (rsp->get_rev.STATUS->tunint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->get_rev.STATUS->tunint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                             sprintf(msg,"%s%d", msg, rsp->get_rev.STATUS->tunint);
       strcat(msg,*separator); strcat(msg,"-ATVINT   ");
           if  (rsp->get_rev.STATUS->atvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->get_rev.STATUS->atvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                             sprintf(msg,"%s%d", msg, rsp->get_rev.STATUS->atvint);
       strcat(msg,*separator); strcat(msg,"-DTVINT   ");
           if  (rsp->get_rev.STATUS->dtvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->get_rev.STATUS->dtvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                             sprintf(msg,"%s%d", msg, rsp->get_rev.STATUS->dtvint);
       strcat(msg,*separator); strcat(msg,"-ERR      ");
           if  (rsp->get_rev.STATUS->err      ==     1) strcat(msg,"ERROR   ");
      else if  (rsp->get_rev.STATUS->err      ==     0) strcat(msg,"NO_ERROR");
      else                                             sprintf(msg,"%s%d", msg, rsp->get_rev.STATUS->err);
       strcat(msg,*separator); strcat(msg,"-CTS      ");
           if  (rsp->get_rev.STATUS->cts      ==     1) strcat(msg,"COMPLETED");
      else if  (rsp->get_rev.STATUS->cts      ==     0) strcat(msg,"WAIT     ");
      else                                             sprintf(msg,"%s%d", msg, rsp->get_rev.STATUS->cts);
       strcat(msg,*separator); strcat(msg,"-PN       "); sprintf(msg,"%s%d", msg, rsp->get_rev.pn);
       strcat(msg,*separator); strcat(msg,"-FWMAJOR  "); sprintf(msg,"%s%d", msg, rsp->get_rev.fwmajor);
       strcat(msg,*separator); strcat(msg,"-FWMINOR  "); sprintf(msg,"%s%d", msg, rsp->get_rev.fwminor);
       strcat(msg,*separator); strcat(msg,"-PATCH    "); sprintf(msg,"%s%d", msg, rsp->get_rev.patch);
       strcat(msg,*separator); strcat(msg,"-CMPMAJOR "); sprintf(msg,"%s%d", msg, rsp->get_rev.cmpmajor);
       strcat(msg,*separator); strcat(msg,"-CMPMINOR "); sprintf(msg,"%s%d", msg, rsp->get_rev.cmpminor);
       strcat(msg,*separator); strcat(msg,"-CMPBUILD "); sprintf(msg,"%s%d", msg, rsp->get_rev.cmpbuild);
       strcat(msg,*separator); strcat(msg,"-CHIPREV  ");
           if  (rsp->get_rev.chiprev  ==     1) strcat(msg,"A");
      else if  (rsp->get_rev.chiprev  ==     2) strcat(msg,"B");
      else                                     sprintf(msg,"%s%d", msg, rsp->get_rev.chiprev);
     break;
    #endif /*     Si2176_GET_REV_CMD */
    #ifdef        Si2176_PART_INFO_CMD
     case         Si2176_PART_INFO_CMD:
      sprintf(msg,"PART_INFO ");
       strcat(msg,*separator); strcat(msg,"-TUNINT   ");
           if  (rsp->part_info.STATUS->tunint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->part_info.STATUS->tunint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                               sprintf(msg,"%s%d", msg, rsp->part_info.STATUS->tunint);
       strcat(msg,*separator); strcat(msg,"-ATVINT   ");
           if  (rsp->part_info.STATUS->atvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->part_info.STATUS->atvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                               sprintf(msg,"%s%d", msg, rsp->part_info.STATUS->atvint);
       strcat(msg,*separator); strcat(msg,"-DTVINT   ");
           if  (rsp->part_info.STATUS->dtvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->part_info.STATUS->dtvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                               sprintf(msg,"%s%d", msg, rsp->part_info.STATUS->dtvint);
       strcat(msg,*separator); strcat(msg,"-ERR      ");
           if  (rsp->part_info.STATUS->err      ==     1) strcat(msg,"ERROR   ");
      else if  (rsp->part_info.STATUS->err      ==     0) strcat(msg,"NO_ERROR");
      else                                               sprintf(msg,"%s%d", msg, rsp->part_info.STATUS->err);
       strcat(msg,*separator); strcat(msg,"-CTS      ");
           if  (rsp->part_info.STATUS->cts      ==     1) strcat(msg,"COMPLETED");
      else if  (rsp->part_info.STATUS->cts      ==     0) strcat(msg,"WAIT     ");
      else                                               sprintf(msg,"%s%d", msg, rsp->part_info.STATUS->cts);
       strcat(msg,*separator); strcat(msg,"-CHIPREV  ");
           if  (rsp->part_info.chiprev  ==     1) strcat(msg,"A");
      else if  (rsp->part_info.chiprev  ==     2) strcat(msg,"B");
      else                                       sprintf(msg,"%s%d", msg, rsp->part_info.chiprev);
       strcat(msg,*separator); strcat(msg,"-PART     "); sprintf(msg,"%s%d", msg, rsp->part_info.part);
       strcat(msg,*separator); strcat(msg,"-PMAJOR   "); sprintf(msg,"%s%d", msg, rsp->part_info.pmajor);
       strcat(msg,*separator); strcat(msg,"-PMINOR   "); sprintf(msg,"%s%d", msg, rsp->part_info.pminor);
       strcat(msg,*separator); strcat(msg,"-PBUILD   "); sprintf(msg,"%s%d", msg, rsp->part_info.pbuild);
       strcat(msg,*separator); strcat(msg,"-RESERVED "); sprintf(msg,"%s%d", msg, rsp->part_info.reserved);
       strcat(msg,*separator); strcat(msg,"-SERIAL   "); sprintf(msg,"%s%d", msg, rsp->part_info.serial);
       strcat(msg,*separator); strcat(msg,"-ROMID    "); sprintf(msg,"%s%d", msg, rsp->part_info.romid);
     break;
    #endif /*     Si2176_PART_INFO_CMD */
    #ifdef        Si2176_POWER_DOWN_CMD
     case         Si2176_POWER_DOWN_CMD:
      sprintf(msg,"POWER_DOWN ");
       strcat(msg,*separator); strcat(msg,"-TUNINT ");
           if  (rsp->power_down.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->power_down.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                              sprintf(msg,"%s%d", msg, rsp->power_down.STATUS->tunint);
       strcat(msg,*separator); strcat(msg,"-ATVINT ");
           if  (rsp->power_down.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->power_down.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                              sprintf(msg,"%s%d", msg, rsp->power_down.STATUS->atvint);
       strcat(msg,*separator); strcat(msg,"-DTVINT ");
           if  (rsp->power_down.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->power_down.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                              sprintf(msg,"%s%d", msg, rsp->power_down.STATUS->dtvint);
       strcat(msg,*separator); strcat(msg,"-ERR    ");
           if  (rsp->power_down.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (rsp->power_down.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                              sprintf(msg,"%s%d", msg, rsp->power_down.STATUS->err);
       strcat(msg,*separator); strcat(msg,"-CTS    ");
           if  (rsp->power_down.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (rsp->power_down.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                              sprintf(msg,"%s%d", msg, rsp->power_down.STATUS->cts);
     break;
    #endif /*     Si2176_POWER_DOWN_CMD */
    #ifdef        Si2176_POWER_UP_CMD
     case         Si2176_POWER_UP_CMD:
      sprintf(msg,"POWER_UP ");
       strcat(msg,*separator); strcat(msg,"-TUNINT ");
           if  (rsp->power_up.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->power_up.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                            sprintf(msg,"%s%d", msg, rsp->power_up.STATUS->tunint);
       strcat(msg,*separator); strcat(msg,"-ATVINT ");
           if  (rsp->power_up.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->power_up.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                            sprintf(msg,"%s%d", msg, rsp->power_up.STATUS->atvint);
       strcat(msg,*separator); strcat(msg,"-DTVINT ");
           if  (rsp->power_up.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->power_up.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                            sprintf(msg,"%s%d", msg, rsp->power_up.STATUS->dtvint);
       strcat(msg,*separator); strcat(msg,"-ERR    ");
           if  (rsp->power_up.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (rsp->power_up.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                            sprintf(msg,"%s%d", msg, rsp->power_up.STATUS->err);
       strcat(msg,*separator); strcat(msg,"-CTS    ");
           if  (rsp->power_up.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (rsp->power_up.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                            sprintf(msg,"%s%d", msg, rsp->power_up.STATUS->cts);
     break;
    #endif /*     Si2176_POWER_UP_CMD */
    #ifdef        Si2176_SET_PROPERTY_CMD
     case         Si2176_SET_PROPERTY_CMD:
      sprintf(msg,"SET_PROPERTY ");
       strcat(msg,*separator); strcat(msg,"-TUNINT   ");
           if  (rsp->set_property.STATUS->tunint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->set_property.STATUS->tunint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                  sprintf(msg,"%s%d", msg, rsp->set_property.STATUS->tunint);
       strcat(msg,*separator); strcat(msg,"-ATVINT   ");
           if  (rsp->set_property.STATUS->atvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->set_property.STATUS->atvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                  sprintf(msg,"%s%d", msg, rsp->set_property.STATUS->atvint);
       strcat(msg,*separator); strcat(msg,"-DTVINT   ");
           if  (rsp->set_property.STATUS->dtvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->set_property.STATUS->dtvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                  sprintf(msg,"%s%d", msg, rsp->set_property.STATUS->dtvint);
       strcat(msg,*separator); strcat(msg,"-ERR      ");
           if  (rsp->set_property.STATUS->err      ==     1) strcat(msg,"ERROR   ");
      else if  (rsp->set_property.STATUS->err      ==     0) strcat(msg,"NO_ERROR");
      else                                                  sprintf(msg,"%s%d", msg, rsp->set_property.STATUS->err);
       strcat(msg,*separator); strcat(msg,"-CTS      ");
           if  (rsp->set_property.STATUS->cts      ==     1) strcat(msg,"COMPLETED");
      else if  (rsp->set_property.STATUS->cts      ==     0) strcat(msg,"WAIT     ");
      else                                                  sprintf(msg,"%s%d", msg, rsp->set_property.STATUS->cts);
       strcat(msg,*separator); strcat(msg,"-RESERVED "); sprintf(msg,"%s%d", msg, rsp->set_property.reserved);
       strcat(msg,*separator); strcat(msg,"-DATA     "); sprintf(msg,"%s%d", msg, rsp->set_property.data);
     break;
    #endif /*     Si2176_SET_PROPERTY_CMD */
    #ifdef        Si2176_STANDBY_CMD
     case         Si2176_STANDBY_CMD:
      sprintf(msg,"STANDBY ");
       strcat(msg,*separator); strcat(msg,"-TUNINT ");
           if  (rsp->standby.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->standby.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                           sprintf(msg,"%s%d", msg, rsp->standby.STATUS->tunint);
       strcat(msg,*separator); strcat(msg,"-ATVINT ");
           if  (rsp->standby.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->standby.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                           sprintf(msg,"%s%d", msg, rsp->standby.STATUS->atvint);
       strcat(msg,*separator); strcat(msg,"-DTVINT ");
           if  (rsp->standby.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->standby.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                           sprintf(msg,"%s%d", msg, rsp->standby.STATUS->dtvint);
       strcat(msg,*separator); strcat(msg,"-ERR    ");
           if  (rsp->standby.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (rsp->standby.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                           sprintf(msg,"%s%d", msg, rsp->standby.STATUS->err);
       strcat(msg,*separator); strcat(msg,"-CTS    ");
           if  (rsp->standby.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (rsp->standby.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                           sprintf(msg,"%s%d", msg, rsp->standby.STATUS->cts);
     break;
    #endif /*     Si2176_STANDBY_CMD */
    #ifdef        Si2176_TUNER_STATUS_CMD
     case         Si2176_TUNER_STATUS_CMD:
      sprintf(msg,"TUNER_STATUS ");
       strcat(msg,*separator); strcat(msg,"-TUNINT   ");
           if  (rsp->tuner_status.STATUS->tunint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->tuner_status.STATUS->tunint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                  sprintf(msg,"%s%d", msg, rsp->tuner_status.STATUS->tunint);
       strcat(msg,*separator); strcat(msg,"-ATVINT   ");
           if  (rsp->tuner_status.STATUS->atvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->tuner_status.STATUS->atvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                  sprintf(msg,"%s%d", msg, rsp->tuner_status.STATUS->atvint);
       strcat(msg,*separator); strcat(msg,"-DTVINT   ");
           if  (rsp->tuner_status.STATUS->dtvint   ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->tuner_status.STATUS->dtvint   ==     1) strcat(msg,"TRIGGERED    ");
      else                                                  sprintf(msg,"%s%d", msg, rsp->tuner_status.STATUS->dtvint);
       strcat(msg,*separator); strcat(msg,"-ERR      ");
           if  (rsp->tuner_status.STATUS->err      ==     1) strcat(msg,"ERROR   ");
      else if  (rsp->tuner_status.STATUS->err      ==     0) strcat(msg,"NO_ERROR");
      else                                                  sprintf(msg,"%s%d", msg, rsp->tuner_status.STATUS->err);
       strcat(msg,*separator); strcat(msg,"-CTS      ");
           if  (rsp->tuner_status.STATUS->cts      ==     1) strcat(msg,"COMPLETED");
      else if  (rsp->tuner_status.STATUS->cts      ==     0) strcat(msg,"WAIT     ");
      else                                                  sprintf(msg,"%s%d", msg, rsp->tuner_status.STATUS->cts);
       strcat(msg,*separator); strcat(msg,"-TCINT    ");
           if  (rsp->tuner_status.tcint    ==     1) strcat(msg,"CHANGED  ");
      else if  (rsp->tuner_status.tcint    ==     0) strcat(msg,"NO_CHANGE");
      else                                          sprintf(msg,"%s%d", msg, rsp->tuner_status.tcint);
       strcat(msg,*separator); strcat(msg,"-RSSILINT ");
           if  (rsp->tuner_status.rssilint ==     1) strcat(msg,"CHANGED  ");
      else if  (rsp->tuner_status.rssilint ==     0) strcat(msg,"NO_CHANGE");
      else                                          sprintf(msg,"%s%d", msg, rsp->tuner_status.rssilint);
       strcat(msg,*separator); strcat(msg,"-RSSIHINT ");
           if  (rsp->tuner_status.rssihint ==     1) strcat(msg,"CHANGED  ");
      else if  (rsp->tuner_status.rssihint ==     0) strcat(msg,"NO_CHANGE");
      else                                          sprintf(msg,"%s%d", msg, rsp->tuner_status.rssihint);
       strcat(msg,*separator); strcat(msg,"-TC       ");
           if  (rsp->tuner_status.tc       ==     0) strcat(msg,"BUSY");
      else if  (rsp->tuner_status.tc       ==     1) strcat(msg,"DONE");
      else                                          sprintf(msg,"%s%d", msg, rsp->tuner_status.tc);
       strcat(msg,*separator); strcat(msg,"-RSSIL    ");
           if  (rsp->tuner_status.rssil    ==     1) strcat(msg,"LOW");
      else if  (rsp->tuner_status.rssil    ==     0) strcat(msg,"OK ");
      else                                          sprintf(msg,"%s%d", msg, rsp->tuner_status.rssil);
       strcat(msg,*separator); strcat(msg,"-RSSIH    ");
           if  (rsp->tuner_status.rssih    ==     1) strcat(msg,"HIGH");
      else if  (rsp->tuner_status.rssih    ==     0) strcat(msg,"OK  ");
      else                                          sprintf(msg,"%s%d", msg, rsp->tuner_status.rssih);
       strcat(msg,*separator); strcat(msg,"-RSSI     "); sprintf(msg,"%s%d", msg, rsp->tuner_status.rssi);
       strcat(msg,*separator); strcat(msg,"-FREQ     "); sprintf(msg,"%s%d", msg, rsp->tuner_status.freq);
       strcat(msg,*separator); strcat(msg,"-MODE     ");
           if  (rsp->tuner_status.mode     ==     1) strcat(msg,"ATV");
      else if  (rsp->tuner_status.mode     ==     0) strcat(msg,"DTV");
      else                                          sprintf(msg,"%s%d", msg, rsp->tuner_status.mode);
       strcat(msg,*separator); strcat(msg,"-VCO_CODE "); sprintf(msg,"%s%d", msg, rsp->tuner_status.vco_code);
     break;
    #endif /*     Si2176_TUNER_STATUS_CMD */
    #ifdef        Si2176_TUNER_TUNE_FREQ_CMD
     case         Si2176_TUNER_TUNE_FREQ_CMD:
      sprintf(msg,"TUNER_TUNE_FREQ ");
       strcat(msg,*separator); strcat(msg,"-TUNINT ");
           if  (rsp->tuner_tune_freq.STATUS->tunint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->tuner_tune_freq.STATUS->tunint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                   sprintf(msg,"%s%d", msg, rsp->tuner_tune_freq.STATUS->tunint);
       strcat(msg,*separator); strcat(msg,"-ATVINT ");
           if  (rsp->tuner_tune_freq.STATUS->atvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->tuner_tune_freq.STATUS->atvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                   sprintf(msg,"%s%d", msg, rsp->tuner_tune_freq.STATUS->atvint);
       strcat(msg,*separator); strcat(msg,"-DTVINT ");
           if  (rsp->tuner_tune_freq.STATUS->dtvint ==     0) strcat(msg,"NOT_TRIGGERED");
      else if  (rsp->tuner_tune_freq.STATUS->dtvint ==     1) strcat(msg,"TRIGGERED    ");
      else                                                   sprintf(msg,"%s%d", msg, rsp->tuner_tune_freq.STATUS->dtvint);
       strcat(msg,*separator); strcat(msg,"-ERR    ");
           if  (rsp->tuner_tune_freq.STATUS->err    ==     1) strcat(msg,"ERROR   ");
      else if  (rsp->tuner_tune_freq.STATUS->err    ==     0) strcat(msg,"NO_ERROR");
      else                                                   sprintf(msg,"%s%d", msg, rsp->tuner_tune_freq.STATUS->err);
       strcat(msg,*separator); strcat(msg,"-CTS    ");
           if  (rsp->tuner_tune_freq.STATUS->cts    ==     1) strcat(msg,"COMPLETED");
      else if  (rsp->tuner_tune_freq.STATUS->cts    ==     0) strcat(msg,"WAIT     ");
      else                                                   sprintf(msg,"%s%d", msg, rsp->tuner_tune_freq.STATUS->cts);
     break;
    #endif /*     Si2176_TUNER_TUNE_FREQ_CMD */
   default : break;
    }
    return 0;
  }
  /* _get_command_response_string_insertion_point */
#endif /* Si2176_GET_COMMAND_STRINGS */

/* End of template (2011 January 24 at 13:47) */




