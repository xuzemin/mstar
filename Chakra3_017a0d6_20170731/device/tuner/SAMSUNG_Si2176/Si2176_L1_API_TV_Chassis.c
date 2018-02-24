/***************************************************************************************/
/* FILE: Si2176_L1_API_TV_Chassis.c                                                    */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/***************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//#include "Si2176_Typedefs.h"
//#include "Si2176_L0_TV_Chassis.h"

#include "Si2176_L1_API_TV_Chassis.h"
#include "Si2176_Commands.h"
#include "Si2176_Properties.h"


#ifndef UNUSED_SAMSUNG//to avoid compile warnings...
#define UNUSED_SAMSUNG(var) ((var) = (var))
#endif
/***********************************************************************************************************************
  NAME: Si2176_L1_API_Init
  DESCRIPTION: software initialisation function
              Used to initialize the software context
  Returns:    0 if no error
  Comments:   It should be called first and once only when starting the application
  Parameter:  *api    a pointer to the api context to initialize
  Parameter:  *Si2176_L0 a pointer to the L0 Context 
  Parameter:  add  the Si2176 I2C address
 ***********************************************************************************************************************/
unsigned char Si2176_L1_API_Init  (L1_Si2176_Context *api, L0_Context *Si2176_L0, int add) 
{

   L0_Init(Si2176_L0);

    // change code by yooheeyong 20110525
    memcpy(api->i2c,Si2176_L0,sizeof(L0_Context));

    //api->i2c   = Si2176_L0;      // this part is error from changing the address by yooheeyong 20110525
    //api->i2c->address = add;
    UNUSED_SAMSUNG(add);
    return NO_Si2176_ERROR;
}
/***********************************************************************************************************************
  NAME: Si2176_L1_API_Patch
  DESCRIPTION: Patch information function
              Used to send a number of bytes to the Si2176. Useful to download the firmware.
  Parameter:   *api    a pointer to the api context to initialize
  Parameter:  waitForCTS flag for CTS checking prior to sending a Si2176 API Command 
  Parameter:  waitForResponse flag for CTS checking and Response readback after sending Si2176 API Command
  Parameter:  number of bytes to transmit
  Parameter:  Databuffer containing the bytes to transfer in an unsigned char array.
  Returns:   0 if no error, else a nonzero int representing an error
 ***********************************************************************************************************************/
unsigned char Si2176_L1_API_Patch (L1_Si2176_Context *api, unsigned char waitForCTS, unsigned char Si2176_waitForResponse, int iNbBytes, unsigned char *pucDataBuffer) {
    unsigned char res=0;
    unsigned char error_code=0;
    unsigned char rspByteBuffer[1];
    Si2176_COMMON_REPLY_struct status;

    if (waitForCTS) 
    {
        res = Si2176_pollForCTS(api, waitForCTS);
        if (res != NO_Si2176_ERROR) 
        {
            return res;
        }
    }
    
    res = L0_WriteCommandBytes(api->i2c, iNbBytes, pucDataBuffer);
    if (res!=iNbBytes)
       return ERROR_Si2176_SENDING_COMMAND;
   
 
    if (Si2176_waitForResponse) 
    {
        error_code = Si2176_pollForResponse(api, Si2176_waitForResponse, 1, rspByteBuffer, &status);
    }

    return error_code;
}

/************************************************************************************************************************
  NAME: CheckStatus
  DESCRIPTION:     Read Si2176 STATUS byte and return decoded status
  Parameter:  Si2176 Context (I2C address)
  Parameter:  Status byte (TUNINT, ATVINT, DTVINT, ERR, CTS, CHLINT, and CHL flags).
  Returns:    Si2176/I2C transaction error code
************************************************************************************************************************/
#if 0
int CheckStatus  (L1_Si2176_Context *Si2176, Si2176_COMMON_REPLY_struct *status) 
{
    unsigned char buffer[1];
  /* read STATUS byte */
    if (Si2176_pollForResponse(Si2176, 1, 1, buffer, status) != 0) 
  {     
        return ERROR_Si2176_POLLING_RESPONSE;
    }
 
    return 0;
}
#endif
/**********************************************************************************************************************/
