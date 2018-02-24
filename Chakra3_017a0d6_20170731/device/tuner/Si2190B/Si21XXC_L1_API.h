/*************************************************************************************
                  Silicon Laboratories Broadcast Si21XXC Layer 1 API

   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
     PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.

   API functions prototypes used by commands and properties
   FILE: Si21XXC_L1_API.h
   Supported IC : Si2178B,Si2190B,Si2191B,Si2191C
   Compiled for ROM 71 firmware 3_0_build_1
   Revision: 0.1
   Tag:  Si2190B_30b1_Si2178B_42b7_Si2191C_30b1_Si2191B_42b7_V0.1
   Date: August 12 2015
  (C) Copyright 2014, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#ifndef    _Si21XXC_L1_API_H_
#define    _Si21XXC_L1_API_H_

#include "Silabs_L0_API.h"


#include "Si21XXC_Commands.h"
#include "Si21XXC_Properties.h"
#include "Si21XXC_typedefs.h"
#include "Si21XXC_Commands_Prototypes.h"
#include "Si21XXC_Properties_Functions.h"

#ifdef __cplusplus
extern "C"{
#endif
#define NO_Si21XXC_ERROR                     0x00
#define ERROR_Si21XXC_PARAMETER_OUT_OF_RANGE 0x01
#define ERROR_Si21XXC_ALLOCATING_CONTEXT     0x02
#define ERROR_Si21XXC_SENDING_COMMAND        0x03
#define ERROR_Si21XXC_CTS_TIMEOUT            0x04
#define ERROR_Si21XXC_ERR                    0x05
#define ERROR_Si21XXC_POLLING_CTS            0x06
#define ERROR_Si21XXC_POLLING_RESPONSE       0x07
#define ERROR_Si21XXC_LOADING_FIRMWARE       0x08
#define ERROR_Si21XXC_LOADING_BOOTBLOCK      0x09
#define ERROR_Si21XXC_STARTING_FIRMWARE      0x0a
#define ERROR_Si21XXC_SW_RESET               0x0b
#define ERROR_Si21XXC_INCOMPATIBLE_PART      0x0c
#define ERROR_Si21XXC_TUNINT_TIMEOUT         0x0d
#define ERROR_Si21XXC_xTVINT_TIMEOUT         0x0e
#define ERROR_Si21XXC_UNKNOWN_COMMAND        0xf0
#define ERROR_Si21XXC_UNKNOWN_PROPERTY       0xf1


unsigned char Si21XXC_L1_API_Init    (L1_Si21XXC_Context *api, int add);
unsigned char Si21XXC_L1_API_Patch   (L1_Si21XXC_Context *api, int iNbBytes, unsigned char *pucDataBuffer);
unsigned char Si21XXC_L1_CheckStatus (L1_Si21XXC_Context *api);
const char*         Si21XXC_L1_API_ERROR_TEXT(int error_code);
const char*         Si21XXC_L1_API_TAG_TEXT  (void);

#define Si21XXC_TAG Si21XXC_L1_API_TAG_TEXT


#ifdef    Si21XXC_GET_PROPERTY_STRING
void Si21XXC_L1_FillPropertyStringText(L1_Si21XXC_Context *api, unsigned int prop_code, const char *separator, char *msg);
#endif /* Si21XXC_GET_PROPERTY_STRING */

#ifdef __cplusplus
}
#endif
#endif /* _Si21XXC_L1_API_H_ */








