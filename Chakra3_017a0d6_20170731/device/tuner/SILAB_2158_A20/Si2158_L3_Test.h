/***************************************************************************************
                  Silicon Laboratories Broadcast Si2158 Layer 3 console application
   L3 sample application header
   FILE: Si2158_L3_Test.h
   Supported IC : Si2158
   Compiled for ROM 33 firmware 2_1_build_9
   Revision: 0.1
   Date: March 20 2013
  (C) Copyright 2013, Silicon Laboratories, Inc. All rights reserved.
****************************************************************************************/

#ifndef   Si2158_L3_TEST_H
#define   Si2158_L3_TEST_H

#define   Si2158_COMMAND_PROTOTYPES

#include "Si2158_L2_API.h"
#include "Si2158_Commands_Prototypes.h"

#define   Si2158_BASE_ADDRESS 0xc0
#define   SYSTEM_PAUSE system("pause")

void Si2158_configure_i2c_communication    (L1_Si2158_Context *api);

#ifdef    Si2158_COMMAND_LINE_APPLICATION

int  Si2158_DisplayStatusByte              (L1_Si2158_Context *api);
int  Si2158_GetRevision                    (L1_Si2158_Context *api);
int  Si2158_ATVStatus (L1_Si2158_Context *Si2158);
int  Si2158_DTVStatus (L1_Si2158_Context *Si2158);
int  Si2158_TunerStatus (L1_Si2158_Context *Si2158);
int  Si2158_GetUserFrequency(unsigned long *fIn);
int  Si2158_help                           (void);
void Si2158_menu                           (unsigned char full);
int  Si2158_demoLoop                       (L1_Si2158_Context *api, char* choice);

#endif /* Si2158_COMMAND_LINE_APPLICATION */

#endif /* Si2158_L3_TEST_H */





