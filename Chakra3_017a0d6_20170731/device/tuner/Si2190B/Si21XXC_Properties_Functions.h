/*************************************************************************************
                  Silicon Laboratories Broadcast Si21XXC Layer 1 API

   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
     PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.

   API properties functions definitions
   FILE: Si21XXC_Properties_Functions.h
   Supported IC : Si2178B,Si2190B,Si2191B,Si2191C
   Compiled for ROM 71 firmware 3_0_build_1
   Revision: 0.1
   Tag:  Si2190B_30b1_Si2178B_42b7_Si2191C_30b1_Si2191B_42b7_V0.1
   Date: August 12 2015
  (C) Copyright 2014, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#ifndef   _Si21XXC_PROPERTIES_FUNCTIONS_H_
#define   _Si21XXC_PROPERTIES_FUNCTIONS_H_

void          Si21XXC_storeUserProperties           (Si21XXC_PropObj   *prop);
unsigned char Si21XXC_PackProperty                  (Si21XXC_PropObj   *prop, unsigned int prop_code, int *data);
unsigned char Si21XXC_UnpackProperty                (Si21XXC_PropObj   *prop, unsigned int prop_code, int  data);
void          Si21XXC_storePropertiesDefaults       (Si21XXC_PropObj   *prop);

int  Si21XXC_downloadATVProperties   (L1_Si21XXC_Context *api);
int  Si21XXC_downloadCOMMONProperties(L1_Si21XXC_Context *api);
int  Si21XXC_downloadDTVProperties   (L1_Si21XXC_Context *api);
int  Si21XXC_downloadTUNERProperties (L1_Si21XXC_Context *api);
int  Si21XXC_downloadAllProperties   (L1_Si21XXC_Context *api);

#endif /* _Si21XXC_PROPERTIES_FUNCTIONS_H_ */







