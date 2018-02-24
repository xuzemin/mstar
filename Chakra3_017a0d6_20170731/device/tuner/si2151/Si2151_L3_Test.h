/***************************************************************************************
                  Silicon Laboratories Broadcast Si2151 Layer 3 console application

   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
     PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.

   L3 sample application header
   FILE: Si2151_L3_Test.h
   Supported IC : Si2151
   Compiled for ROM 61 firmware 1_1_build_11
   Revision: 0.4
   Date: December 15 2015
  (C) Copyright 2015, Silicon Laboratories, Inc. All rights reserved.
****************************************************************************************/

#ifndef   Si2151_L3_TEST_H
#define   Si2151_L3_TEST_H

#define   Si2151_COMMAND_PROTOTYPES

#include "Si2151_L2_API.h"
#include "Si2151_Commands_Prototypes.h"

#define   Si2151_BASE_ADDRESS 0xc0
#define   SYSTEM_PAUSE system("pause")

void Si2151_configure_i2c_communication    (L1_Si2151_Context *api);

#ifdef    Si2151_COMMAND_LINE_APPLICATION

int  Si2151_DisplayStatusByte              (L1_Si2151_Context *api);
int  Si2151_GetRevision                    (L1_Si2151_Context *api);
int  Si2151_TunerStatus                    (L1_Si2151_Context *Si2151);
int  Si2151_GetUserFrequency               (unsigned long *fIn);
int  Si2151_help                           (void);
void Si2151_menu                           (unsigned char full);
int  Si2151_demoLoop                       (L1_Si2151_Context *api, char* choice);

#endif /* Si2151_COMMAND_LINE_APPLICATION */

#endif /* Si2151_L3_TEST_H */







