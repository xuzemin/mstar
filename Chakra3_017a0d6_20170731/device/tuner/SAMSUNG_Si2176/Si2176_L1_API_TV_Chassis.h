/***************************************************************************************/
/* FILE: Si2170_L1_API_TV_Chassis.h                                                    */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/***************************************************************************************/
#ifndef SI2176_L1_API_TV_CHASSIS_H
#define SI2176_L1_API_TV_CHASSIS_H

//#include "Si2176_Typedefs.h"
//#include "Si2176_Commands.h"
#include "Si2176_L0_TV_Chassis.h"

/* move code to remove compile error by yooheeyong 20110523 */
typedef struct {
    L0_Context *i2c;
} L1_Si2176_Context;

#define NO_Si2176_ERROR                     0x00
#define ERROR_Si2176_PARAMETER_OUT_OF_RANGE 0x01
#define ERROR_Si2176_ALLOCATING_CONTEXT     0x02
#define ERROR_Si2176_SENDING_COMMAND        0x03
#define ERROR_Si2176_CTS_TIMEOUT            0x04
#define ERROR_Si2176_ERR                    0x05
#define ERROR_Si2176_POLLING_CTS            0x06
#define ERROR_Si2176_POLLING_RESPONSE       0x07
#define ERROR_Si2176_LOADING_FIRMWARE       0x08
#define ERROR_Si2176_LOADING_BOOTBLOCK      0x09
#define ERROR_Si2176_STARTING_FIRMWARE      0x0a
#define ERROR_Si2176_SW_RESET               0x0b
#define ERROR_Si2176_INCOMPATIBLE_PART    0x0c
#define ERROR_Si2176_TUNINT_TIMEOUT         0x0d
#define ERROR_Si2176_xTVINT_TIMEOUT         0x0e

unsigned char Si2176_L1_API_Init  (L1_Si2176_Context *api, L0_Context *Si2176_L0, int add);
unsigned char Si2176_L1_API_Patch (L1_Si2176_Context *api, unsigned char waitForCTS, unsigned char Si2176_waitForResponse, int iNbBytes, unsigned char *pucDataBuffer);
//int       CheckStatus  (L1_Si2176_Context *Si2176, Si2176_COMMON_REPLY_struct *status);
#endif
