/*************************************************************************************
                  Silicon Laboratories Broadcast Si2151 Layer 1 API

   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
     PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.

   API properties functions definitions
   FILE: Si2151_Properties_Functions.h
   Supported IC : Si2151
   Compiled for ROM 61 firmware 1_1_build_11
   Revision: 0.4
   Date: December 15 2015
  (C) Copyright 2015, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#ifndef   _Si2151_PROPERTIES_FUNCTIONS_H_
#define   _Si2151_PROPERTIES_FUNCTIONS_H_

void          Si2151_storeUserProperties           (Si2151_PropObj   *prop);
unsigned char Si2151_PackProperty                  (Si2151_PropObj   *prop, unsigned int prop_code, int *data);
unsigned char Si2151_UnpackProperty                (Si2151_PropObj   *prop, unsigned int prop_code, int  data);
void          Si2151_storePropertiesDefaults       (Si2151_PropObj   *prop);

int  Si2151_downloadATVProperties   (L1_Si2151_Context *api);
int  Si2151_downloadCOMMONProperties(L1_Si2151_Context *api);
int  Si2151_downloadDTVProperties   (L1_Si2151_Context *api);
int  Si2151_downloadTUNERProperties (L1_Si2151_Context *api);
int  Si2151_downloadAllProperties   (L1_Si2151_Context *api);

#endif /* _Si2151_PROPERTIES_FUNCTIONS_H_ */







