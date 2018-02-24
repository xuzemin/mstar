/*************************************************************************************
                  Silicon Laboratories Broadcast Si2190 Layer 1 API
   API functions definitions used by commands and properties
   FILE: Si2190_L1_API.c
   Supported IC : Si2190
   Compiled for ROM 40 firmware 0_A_build_10
   Revision: 0.1
   Tag:  ROM40_0_A_build_10_V0.1
   Date: August 13 2012
  (C) Copyright 2012, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#define   Si2190_COMMAND_PROTOTYPES

#include "Si2190_L1_API.h"

/*chip rev constants for integrity checking */
const char Si2190_chiprev          =  1;
/* Last 2 digits of part number */
const char Si2190_part             =  90; /* Change this value if using a chip other than a Si2190 */
const char Si2190_partMajorVersion = '0';
const char Si2190_partMinorVersion = 'A';
const char Si2190_partRomid        =  0x40;


/***********************************************************************************************************************
  Si2190_L1_API_Init function
  Use:        software initialisation function
              Used to initialize the software context
  Returns:    0 if no error
  Comments:   It should be called first and once only when starting the application
  Parameter:   **ppapi         a pointer to the api context to initialize
  Parameter:  add            the Si2190 I2C address
  Porting:    Allocation errors need to be properly managed.
  Porting:    I2C initialization needs to be adapted to use the available I2C functions
 ***********************************************************************************************************************/
unsigned char    Si2190_L1_API_Init      (L1_Si2190_Context *api, int add) {
    api->i2c = &(api->i2cObj);

    L0_Init(api->i2c);
    L0_SetAddress(api->i2c, add, 0);

    api->cmd    = &(api->cmdObj);
    api->rsp    = &(api->rspObj);
    api->prop   = &(api->propObj);
    api->status = &(api->statusObj);

    api->part             = Si2190_part;
    api->chiprev          = Si2190_chiprev;
    api->partMajorVersion = Si2190_partMajorVersion;
    api->partMinorVersion = Si2190_partMinorVersion;
    api->partRomid        = Si2190_partRomid;

    return NO_Si2190_ERROR;
}
/***********************************************************************************************************************
  Si2190_L1_API_Patch function
  Use:        Patch information function
              Used to send a number of bytes to the Si2190. Useful to download the firmware.
  Returns:    0 if no error
  Parameter:  error_code the error code.
  Porting:    Useful for application development for debug purposes.
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
unsigned char    Si2190_L1_API_Patch     (L1_Si2190_Context *api, int iNbBytes, unsigned char *pucDataBuffer) {
    unsigned char res;
    unsigned char rspByteBuffer[1];

    SiTRACE("Si2190 Patch %d bytes\n",iNbBytes);

    res = L0_WriteCommandBytes(api->i2c, iNbBytes, pucDataBuffer);
    if (res!=iNbBytes) {
      SiTRACE("Si2190_L1_API_Patch error 0x%02x writing bytes: %s\n", res, Si2190_L1_API_ERROR_TEXT(res) );
      return res;
    }

    res = Si2190_pollForResponse(api, 1, rspByteBuffer);
    if (res != NO_Si2190_ERROR) {
      SiTRACE("Si2190_L1_API_Patch error 0x%02x polling response: %s\n", res, Si2190_L1_API_ERROR_TEXT(res) );
      return ERROR_Si2190_POLLING_RESPONSE;
    }

    return NO_Si2190_ERROR;
}
/***********************************************************************************************************************
  Si2190_L1_CheckStatus function
  Use:        Status information function
              Used to retrieve the status byte
  Returns:    0 if no error
  Parameter:  error_code the error code.
 ***********************************************************************************************************************/
unsigned char    Si2190_L1_CheckStatus   (L1_Si2190_Context *api) {
    unsigned char rspByteBuffer[1];
    return Si2190_pollForResponse(api, 1, rspByteBuffer);
}
/***********************************************************************************************************************
  Si2190_L1_API_ERROR_TEXT function
  Use:        Error information function
              Used to retrieve a text based on an error code
  Returns:    the error text
  Parameter:  error_code the error code.
  Porting:    Useful for application development for debug purposes.
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
const char*            Si2190_L1_API_ERROR_TEXT(unsigned char error_code) {
    switch (error_code) {
        case NO_Si2190_ERROR                     : return (const char *)"No Si2190 error";
        case ERROR_Si2190_ALLOCATING_CONTEXT     : return (const char *)"Error while allocating Si2190 context";
        case ERROR_Si2190_PARAMETER_OUT_OF_RANGE : return (const char *)"Si2190 parameter(s) out of range";
        case ERROR_Si2190_SENDING_COMMAND        : return (const char *)"Error while sending Si2190 command";
        case ERROR_Si2190_CTS_TIMEOUT            : return (const char *)"Si2190 CTS timeout";
        case ERROR_Si2190_ERR                    : return (const char *)"Si2190 Error (status 'err' bit 1)";
        case ERROR_Si2190_POLLING_CTS            : return (const char *)"Si2190 Error while polling CTS";
        case ERROR_Si2190_POLLING_RESPONSE       : return (const char *)"Si2190 Error while polling response";
        case ERROR_Si2190_LOADING_FIRMWARE       : return (const char *)"Si2190 Error while loading firmware";
        case ERROR_Si2190_LOADING_BOOTBLOCK      : return (const char *)"Si2190 Error while loading bootblock";
        case ERROR_Si2190_STARTING_FIRMWARE      : return (const char *)"Si2190 Error while starting firmware";
        case ERROR_Si2190_SW_RESET               : return (const char *)"Si2190 Error during software reset";
        case ERROR_Si2190_INCOMPATIBLE_PART      : return (const char *)"Si2190 Error Incompatible part";
/* _specific_error_text_string_insertion_start */
        case ERROR_Si2190_TUNINT_TIMEOUT         : return (const char *)"Si2190 Error TUNINT Timeout";
        case ERROR_Si2190_xTVINT_TIMEOUT         : return (const char *)"Si2190 Error xTVINT Timeout";
/* _specific_error_text_string_insertion_point */
        default                                  : return (const char *)"Unknown Si2190 error code";
    }
}
/***********************************************************************************************************************
  Si2190_L1_API_TAG_TEXT function
  Use:        Error information function
              Used to retrieve a text containing the TAG information (related to the code version)
  Returns:    the TAG text
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
const char*            Si2190_L1_API_TAG_TEXT(void) { return (const char *)"ROM40_0_A_build_10_V0.1";}

/* _specific_code_insertion_start */
/* _specific_code_insertion_point */





