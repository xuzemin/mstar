/***************************************************************************************
                  Silicon Laboratories Broadcast Si2190 Layer 3 console application
   L3 sample application header
   FILE: Si2190_L3_Test.h
   Supported IC : Si2190
   Compiled for ROM 40 firmware 0_A_build_10
   Revision: 0.1
   Date: August 13 2012
  (C) Copyright 2012, Silicon Laboratories, Inc. All rights reserved.
****************************************************************************************/

#ifndef   Si2190_L3_TEST_H
#define   Si2190_L3_TEST_H

#define   Si2190_COMMAND_PROTOTYPES

#include "Si2190_L2_API.h"
#include "Si2190_Commands_Prototypes.h"

#define   Si2190_BASE_ADDRESS 0xc0
#define   SYSTEM_PAUSE system("pause")

void Si2190_configure_i2c_communication    (L1_Si2190_Context *api);

#ifdef    Si2190_COMMAND_LINE_APPLICATION

int  Si2190_DisplayStatusByte              (L1_Si2190_Context *api);
int  Si2190_GetRevision                    (L1_Si2190_Context *api);
int  Si2190_ATVStatus (L1_Si2190_Context *Si2190);
int  Si2190_DTVStatus (L1_Si2190_Context *Si2190);
int  Si2190_TunerStatus (L1_Si2190_Context *Si2190);
int  Si2190_GetUserFrequency(unsigned long *fIn);
int  Si2190_GetFineTuneOffset(int *fIn);
void Si2190_menu                           (unsigned char full);
int  Si2190_demoLoop                       (L1_Si2190_Context *api, char* choice);

#endif /* Si2190_COMMAND_LINE_APPLICATION */

#endif /* Si2190_L3_TEST_H */





