/*************************************************************************************
                  Silicon Laboratories Broadcast Si2158 Layer 1 API
   API functions definitions used by commands and properties
   FILE: Si2158_L1_API.c
   Supported IC : Si2158
   Compiled for ROM 33 firmware 2_0_build_4
   Revision: 0.1
   Tag:  ROM33_2_0_build_4_LGIT_V0.1
   Date: July 30 2012
  (C) Copyright 2012, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#define   Si2158_COMMAND_PROTOTYPES

#include "Si2158_L1_API.h"

/*chip rev constants for integrity checking */
const char Si2158_chiprev          =  1;
/* Last 2 digits of part number */
const char Si2158_part             =  58; /* Change this value if using a chip other than a Si2158 */
const char Si2158_partMajorVersion = '2';
const char Si2158_partMinorVersion = '0';
const char Si2158_partRomid        =  0x33;


/***********************************************************************************************************************
  Si2158_L1_API_Init function
  Use:        software initialisation function
              Used to initialize the software context
  Returns:    0 if no error
  Comments:   It should be called first and once only when starting the application
  Parameter:   **ppapi         a pointer to the api context to initialize
  Parameter:  add            the Si2158 I2C address
  Porting:    Allocation errors need to be properly managed.
  Porting:    I2C initialization needs to be adapted to use the available I2C functions
 ***********************************************************************************************************************/
unsigned char    Si2158_L1_API_Init      (L1_Si2158_Context *api, int add) {
    api->i2c = &(api->i2cObj);

    Si2158_L0_Init(api->i2c);
    Si2158_L0_SetAddress(api->i2c, add, 0);

    api->cmd    = &(api->cmdObj);
    api->rsp    = &(api->rspObj);
    api->prop   = &(api->propObj);
    api->status = &(api->statusObj);

    api->part             = Si2158_part;
    api->chiprev          = Si2158_chiprev;
    api->partMajorVersion = Si2158_partMajorVersion;
    api->partMinorVersion = Si2158_partMinorVersion;
    api->partRomid        = Si2158_partRomid;

    return NO_Si2158_ERROR;
}
/***********************************************************************************************************************
  Si2158_L1_API_Patch function
  Use:        Patch information function
              Used to send a number of bytes to the Si2158. Useful to download the firmware.
  Returns:    0 if no error
  Parameter:  error_code the error code.
  Porting:    Useful for application development for debug purposes.
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
unsigned char    Si2158_L1_API_Patch     (L1_Si2158_Context *api, int iNbBytes, unsigned char *pucDataBuffer) {
    unsigned char res;
    unsigned char rspByteBuffer[1];

    SiTRACE("Si2158 Patch %d bytes\n",iNbBytes);

    res = Si2158_L0_WriteCommandBytes(api->i2c, iNbBytes, pucDataBuffer);
    if (res!=iNbBytes) {
      SiTRACE("Si2158_L1_API_Patch error 0x%02x writing bytes: %s\n", res, Si2158_L1_API_ERROR_TEXT(res) );
      return res;
    }

    res = Si2158_pollForResponse(api, 1, rspByteBuffer);
    if (res != NO_Si2158_ERROR) {
      SiTRACE("Si2158_L1_API_Patch error 0x%02x polling response: %s\n", res, Si2158_L1_API_ERROR_TEXT(res) );
      return ERROR_Si2158_POLLING_RESPONSE;
    }

    return NO_Si2158_ERROR;
}
/***********************************************************************************************************************
  Si2158_L1_CheckStatus function
  Use:        Status information function
              Used to retrieve the status byte
  Returns:    0 if no error
  Parameter:  error_code the error code.
 ***********************************************************************************************************************/
unsigned char    Si2158_L1_CheckStatus   (L1_Si2158_Context *api) {
    unsigned char rspByteBuffer[1];
    return Si2158_pollForResponse(api, 1, rspByteBuffer);
}
/***********************************************************************************************************************
  Si2158_L1_API_ERROR_TEXT function
  Use:        Error information function
              Used to retrieve a text based on an error code
  Returns:    the error text
  Parameter:  error_code the error code.
  Porting:    Useful for application development for debug purposes.
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
char*            Si2158_L1_API_ERROR_TEXT(unsigned char error_code) {
    switch (error_code) {
        case NO_Si2158_ERROR                     : return (char *)"No Si2158 error";
        case ERROR_Si2158_ALLOCATING_CONTEXT     : return (char *)"Error while allocating Si2158 context";
        case ERROR_Si2158_PARAMETER_OUT_OF_RANGE : return (char *)"Si2158 parameter(s) out of range";
        case ERROR_Si2158_SENDING_COMMAND        : return (char *)"Error while sending Si2158 command";
        case ERROR_Si2158_CTS_TIMEOUT            : return (char *)"Si2158 CTS timeout";
        case ERROR_Si2158_ERR                    : return (char *)"Si2158 Error (status 'err' bit 1)";
        case ERROR_Si2158_POLLING_CTS            : return (char *)"Si2158 Error while polling CTS";
        case ERROR_Si2158_POLLING_RESPONSE       : return (char *)"Si2158 Error while polling response";
        case ERROR_Si2158_LOADING_FIRMWARE       : return (char *)"Si2158 Error while loading firmware";
        case ERROR_Si2158_LOADING_BOOTBLOCK      : return (char *)"Si2158 Error while loading bootblock";
        case ERROR_Si2158_STARTING_FIRMWARE      : return (char *)"Si2158 Error while starting firmware";
        case ERROR_Si2158_SW_RESET               : return (char *)"Si2158 Error during software reset";
        case ERROR_Si2158_INCOMPATIBLE_PART      : return (char *)"Si2158 Error Incompatible part";
/* _specific_error_text_string_insertion_start */
        case ERROR_Si2158_TUNINT_TIMEOUT         : return (char *)"Si2158 Error TUNINT Timeout";
        case ERROR_Si2158_xTVINT_TIMEOUT         : return (char *)"Si2158 Error xTVINT Timeout";
/* _specific_error_text_string_insertion_point */
        default                                  : return (char *)"Unknown Si2158 error code";
    }
}
/***********************************************************************************************************************
  Si2158_L1_API_TAG_TEXT function
  Use:        Error information function
              Used to retrieve a text containing the TAG information (related to the code version)
  Returns:    the TAG text
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
char*            Si2158_L1_API_TAG_TEXT(void) { return (char *)"ROM33_2_0_build_4_LGIT_V0.1";}

/* _specific_code_insertion_start */
/* _specific_code_insertion_point */





