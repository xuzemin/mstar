/*************************************************************************************
                  Silicon Laboratories Broadcast Si2190 Layer 1 API
   API functions prototypes used by commands and properties
   FILE: Si2190_L1_API.h
   Supported IC : Si2190
   Compiled for ROM 40 firmware 0_A_build_10
   Revision: 0.1
   Date: August 13 2012
  (C) Copyright 2012, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#ifndef    _Si2190_L1_API_H_
#define    _Si2190_L1_API_H_

#include "Silabs_L0_API.h"

/* _demod_defines_insertion_start */
/* _demod_defines_insertion_point */

#include "Si2190_Commands.h"
#include "Si2190_Properties.h"
#include "Si2190_typedefs.h"
#include "Si2190_Commands_Prototypes.h"

#define NO_Si2190_ERROR                     0x00
#define ERROR_Si2190_PARAMETER_OUT_OF_RANGE 0x01
#define ERROR_Si2190_ALLOCATING_CONTEXT     0x02
#define ERROR_Si2190_SENDING_COMMAND        0x03
#define ERROR_Si2190_CTS_TIMEOUT            0x04
#define ERROR_Si2190_ERR                    0x05
#define ERROR_Si2190_POLLING_CTS            0x06
#define ERROR_Si2190_POLLING_RESPONSE       0x07
#define ERROR_Si2190_LOADING_FIRMWARE       0x08
#define ERROR_Si2190_LOADING_BOOTBLOCK      0x09
#define ERROR_Si2190_STARTING_FIRMWARE      0x0a
#define ERROR_Si2190_SW_RESET               0x0b
#define ERROR_Si2190_INCOMPATIBLE_PART      0x0c
/* _specific_error_value_insertion_start */
#define ERROR_Si2190_TUNINT_TIMEOUT         0x0d
#define ERROR_Si2190_xTVINT_TIMEOUT         0x0e
/* _specific_error_value_insertion_point */

/* define PART_INTEGRITY_CHECKS (here) and the expected part number, chip rev, pmajor, pminor, and romid (in Si2190_L1_API.c) to use integrity checking */
#undef PART_INTEGRITY_CHECKS
/* chip rev constants for integrity checking */
extern const char Si2190_chiprev;
extern const char Si2190_part;
extern const char Si2190_partMajorVersion;
extern const char Si2190_partMinorVersion;
extern const char Si2190_partRomid;

unsigned char Si2190_L1_API_Init    (L1_Si2190_Context *api, int add);
unsigned char Si2190_L1_API_Patch   (L1_Si2190_Context *api, int iNbBytes, unsigned char *pucDataBuffer);
unsigned char Si2190_L1_CheckStatus (L1_Si2190_Context *api);
const char*         Si2190_L1_API_ERROR_TEXT(unsigned char  error_code);
const char*         Si2190_L1_API_TAG_TEXT  (void);

#define Si2190_TAG Si2190_L1_API_TAG_TEXT


#ifdef    Si2190_GET_PROPERTY_STRING
void Si2190_L1_FillPropertyStringText(L1_Si2190_Context *api, unsigned int prop_code, const char *separator, char *msg);
#endif /* Si2190_GET_PROPERTY_STRING */

#endif /* _Si2190_L1_API_H_ */






