/*************************************************************************************
                  Silicon Laboratories Broadcast Si21XXC Layer 1 API

   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
     PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.

   API functions definitions used by commands and properties
   FILE: Si21XXC_L1_API.c
   Supported IC : Si2178B,Si2190B,Si2191B,Si2191C
   Compiled for ROM 71 firmware 3_0_build_1
   Revision: 0.1
   Tag:  Si2190B_30b1_Si2178B_42b7_Si2191C_30b1_Si2191B_42b7_V0.1
   Date: August 12 2015
  (C) Copyright 2014, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#define   Si21XXC_COMMAND_PROTOTYPES

#include "Si21XXC_L1_API.h"


/***********************************************************************************************************************
  Si21XXC_L1_API_Init function
  Use:        software initialisation function
              Used to initialize the software context
  Returns:    0 if no error
  Comments:   It should be called first and once only when starting the application
  Parameter:   **ppapi         a pointer to the api context to initialize
  Parameter:  add            the Si21XXC I2C address
  Porting:    Allocation errors need to be properly managed.
  Porting:    I2C initialization needs to be adapted to use the available I2C functions
 ***********************************************************************************************************************/
unsigned char    Si21XXC_L1_API_Init      (L1_Si21XXC_Context *api, int add) {
    api->i2c = &(api->i2cObj);

    L0_Init(api->i2c);
    L0_SetAddress(api->i2c, add, 0);

    api->cmd    = &(api->cmdObj);
    api->rsp    = &(api->rspObj);
    api->prop   = &(api->propObj);
    api->status = &(api->statusObj);
    api->propShadow        = &(api->propShadowObj);
    /* Set the propertyWriteMode to DOWNLOAD_ON_CHANGE to only download property settings on change (recommended) */
    /*      if propertyWriteMode is set to DOWNLOAD_ALWAYS the properties will be downloaded regardless of change */
    api->propertyWriteMode = DOWNLOAD_ON_CHANGE;

    return NO_Si21XXC_ERROR;
}
/***********************************************************************************************************************
  Si21XXC_L1_API_Patch function
  Use:        Patch information function
              Used to send a number of bytes to the Si21XXC. Useful to download the firmware.
  Returns:    0 if no error
  Parameter:  error_code the error code.
  Porting:    Useful for application development for debug purposes.
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
unsigned char    Si21XXC_L1_API_Patch     (L1_Si21XXC_Context *api, int iNbBytes, unsigned char *pucDataBuffer) {
    int res;
    unsigned char rspByteBuffer[1];

    SiTRACE("Si21XXC Patch %d bytes\n",iNbBytes);

    res = L0_WriteCommandBytes(api->i2c, iNbBytes, pucDataBuffer);
    if (res!=iNbBytes) {
      SiTRACE("Si21XXC_L1_API_Patch error writing bytes: %s\n", Si21XXC_L1_API_ERROR_TEXT(ERROR_Si21XXC_LOADING_FIRMWARE) );
      return ERROR_Si21XXC_LOADING_FIRMWARE;
    }

    res = Si21XXC_pollForResponse(api, 1, rspByteBuffer);
    if (res != NO_Si21XXC_ERROR) {
      SiTRACE("Si21XXC_L1_API_Patch error 0x%02x polling response: %s\n", res, Si21XXC_L1_API_ERROR_TEXT(res) );
      return ERROR_Si21XXC_POLLING_RESPONSE;
    }

    return NO_Si21XXC_ERROR;
}
/***********************************************************************************************************************
  Si21XXC_L1_CheckStatus function
  Use:        Status information function
              Used to retrieve the status byte
  Returns:    0 if no error
  Parameter:  error_code the error code.
 ***********************************************************************************************************************/
unsigned char    Si21XXC_L1_CheckStatus   (L1_Si21XXC_Context *api) {
    unsigned char rspByteBuffer[1];
    return Si21XXC_pollForResponse(api, 1, rspByteBuffer);
}
/***********************************************************************************************************************
  Si21XXC_L1_API_ERROR_TEXT function
  Use:        Error information function
              Used to retrieve a text based on an error code
  Returns:    the error text
  Parameter:  error_code the error code.
  Porting:    Useful for application development for debug purposes.
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
const char*             Si21XXC_L1_API_ERROR_TEXT(int error_code) {
    switch (error_code) {
        case NO_Si21XXC_ERROR                     : return "No Si21XXC error";
        case ERROR_Si21XXC_ALLOCATING_CONTEXT     : return "Error while allocating Si21XXC context";
        case ERROR_Si21XXC_PARAMETER_OUT_OF_RANGE : return "Si21XXC parameter(s) out of range";
        case ERROR_Si21XXC_SENDING_COMMAND        : return "Error while sending Si21XXC command";
        case ERROR_Si21XXC_CTS_TIMEOUT            : return "Si21XXC CTS timeout";
        case ERROR_Si21XXC_ERR                    : return "Si21XXC Error (status 'err' bit 1)";
        case ERROR_Si21XXC_POLLING_CTS            : return "Si21XXC Error while polling CTS";
        case ERROR_Si21XXC_POLLING_RESPONSE       : return "Si21XXC Error while polling response";
        case ERROR_Si21XXC_LOADING_FIRMWARE       : return "Si21XXC Error while loading firmware";
        case ERROR_Si21XXC_LOADING_BOOTBLOCK      : return "Si21XXC Error while loading bootblock";
        case ERROR_Si21XXC_STARTING_FIRMWARE      : return "Si21XXC Error while starting firmware";
        case ERROR_Si21XXC_SW_RESET               : return "Si21XXC Error during software reset";
        case ERROR_Si21XXC_INCOMPATIBLE_PART      : return "Si21XXC Error Incompatible part";
        case ERROR_Si21XXC_UNKNOWN_COMMAND        : return "Si21XXC Error unknown command";
        case ERROR_Si21XXC_UNKNOWN_PROPERTY       : return "Si21XXC Error unknown property";
        case ERROR_Si21XXC_TUNINT_TIMEOUT         : return "Si21XXC Error TUNINT Timeout";
        case ERROR_Si21XXC_xTVINT_TIMEOUT         : return "Si21XXC Error xTVINT Timeout";
        default                                  : return "Unknown Si21XXC error code";
    }
}
/***********************************************************************************************************************
  Si21XXC_L1_API_TAG_TEXT function
  Use:        Error information function
              Used to retrieve a text containing the TAG information (related to the code version)
  Returns:    the TAG text
  Porting:    May not be required for the final application, can be removed if not used.
 ***********************************************************************************************************************/
const char*            Si21XXC_L1_API_TAG_TEXT(void) { return "Si2190B_30b1_Si2178B_42b7_Si2191C_30b1_Si2191B_42b7_V0.1";}








