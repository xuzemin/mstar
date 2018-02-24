/***************************************************************************************
                  Silicon Laboratories Broadcast Si2151 Layer 2 API

   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
     PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.

   L2 API header for commands and properties
   FILE: Si2151_L2_API.h
   Supported IC : Si2151
   Compiled for ROM 61 firmware 1_1_build_11
   Revision: 0.4
   Date: December 15 2015
  (C) Copyright 2015, Silicon Laboratories, Inc. All rights reserved.
****************************************************************************************/

#ifndef   Si2151_L2_API_H
#define   Si2151_L2_API_H

#include "Si2151_L1_API.h"
#include "Si2151_Properties_Strings.h"

/* define some externals, required for VCO_BLOCKING */
extern int fe;
extern L1_Si2151_Context  FrontEnd_Table[];

int  Si2151_Init                      (L1_Si2151_Context *api);
int  Si2151_Configure                 (L1_Si2151_Context *api);
int  Si2151_PowerUpWithPatch          (L1_Si2151_Context *api);
int Si2151_PowerUpUsingBroadcastI2C    (L1_Si2151_Context *tuners[], int tuner_count );
int Si2151_PowerUpOnly                 (L1_Si2151_Context *api);
int  Si2151_LoadFirmware              (L1_Si2151_Context *api, unsigned char *fw_table, int lines);
int  Si2151_StartFirmware             (L1_Si2151_Context *api);

int Si2151_LoadFirmware_16    (L1_Si2151_Context *api, firmware_struct fw_table[], int nbLines);
int Si2151_UpdateChannelScanFrequency(int freq,int channelsFound);
int Si2151_GetRF                 (L1_Si2151_Context *api);
int Si2151_Tune                  (L1_Si2151_Context *api, unsigned char mode, unsigned long freq);
int Si2151_ATVTune               (L1_Si2151_Context *api, unsigned long freq, unsigned char video_sys, unsigned char invert_spectrum);
int Si2151_DTVTune               (L1_Si2151_Context *api, unsigned long freq, unsigned char bw, unsigned char modulation, unsigned char invert_spectrum);
int Si2151_XoutOn                (L1_Si2151_Context *api);
int Si2151_XoutOff               (L1_Si2151_Context *api);
int Si2151_Standby               (L1_Si2151_Context *api);
int Si2151_Powerdown             (L1_Si2151_Context *api);
int Si2151_LoadVideofilter       (L1_Si2151_Context *api, vid_filt_struct vidFiltTable[], int lines);
int Si2151_ATV_Channel_Scan_M    (L1_Si2151_Context *api, unsigned long rangeMinHz, unsigned long rangeMaxHz);
int Si2151_ATV_Channel_Scan_PAL  (L1_Si2151_Context *api, unsigned long rangeMinHz, unsigned long rangeMaxHz);
int Si2151_AGC_Override    (L1_Si2151_Context *api, unsigned char mode );
int Si2151_Tuner_Block_VCO       (L1_Si2151_Context *api, int vco_code);
int Si2151_Tuner_Block_VCO2       (L1_Si2151_Context *api, int vco_code);
int Si2151_Tuner_Block_VCO3       (L1_Si2151_Context *api, int vco_code);
int Si2151_L2_VCO_Blocking_PostTune(L1_Si2151_Context *tuners[], int tuner_num, int tuner_count);
int Si2151_L2_VCO_Blocking_PreTune(L1_Si2151_Context *tuners[], int tuner_num, int tuner_count);
int Si2151_SetVcoProperties (L1_Si2151_Context *api);

#define Si2151_FORCE_NORMAL_AGC       0
#define Si2151_FORCE_MAX_AGC          1
#define Si2151_FORCE_TOP_AGC          2

#endif /* Si2151_L2_API_H */







