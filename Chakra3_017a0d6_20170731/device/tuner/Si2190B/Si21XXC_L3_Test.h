/***************************************************************************************
                  Silicon Laboratories Broadcast Si21XXC Layer 3 console application

   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
     PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.

   L3 sample application header
   FILE: Si21XXC_L3_Test.h
   Supported IC : Si2178B,Si2190B,Si2191B,Si2191C
   Compiled for ROM 71 firmware 3_0_build_1
   Revision: 0.1
   Tag:  Si2190B_30b1_Si2178B_42b7_Si2191C_30b1_Si2191B_42b7_V0.1
   Date: August 12 2015
(C) Copyright 2014, Silicon Laboratories, Inc. All rights reserved.
****************************************************************************************/

#ifndef   Si21XXC_L3_TEST_H
#define   Si21XXC_L3_TEST_H

#define   Si21XXC_COMMAND_PROTOTYPES

#include "Si21XXC_L2_API.h"
#include "Si21XXC_Commands_Prototypes.h"

#define   Si21XXC_BASE_ADDRESS 0xc0
#define   SYSTEM_PAUSE system("pause")

//void Si21XXC_configure_i2c_communication    (L1_Si21XXC_Context *api);

#ifdef    Si21XXC_COMMAND_LINE_APPLICATION

int  Si21XXC_DisplayStatusByte              (L1_Si21XXC_Context *api);
int  Si21XXC_GetRevision                    (L1_Si21XXC_Context *api);
int  Si21XXC_ATVStatus (L1_Si21XXC_Context *Si21XXC);
int  Si21XXC_DTVStatus (L1_Si21XXC_Context *Si21XXC);
int  Si21XXC_TunerStatus (L1_Si21XXC_Context *Si21XXC);
int  Si21XXC_GetUserFrequency(unsigned long *fIn);
int  Si21XXC_GetFineTuneOffset(int *fIn);
void Si21XXC_menu                           (L1_Si21XXC_Context *Si21XXC,unsigned char full);
int  Si21XXC_demoLoop                       (L1_Si21XXC_Context *api, char* choice);

#endif /* Si21XXC_COMMAND_LINE_APPLICATION */

#endif /* Si21XXC_L3_TEST_H */





