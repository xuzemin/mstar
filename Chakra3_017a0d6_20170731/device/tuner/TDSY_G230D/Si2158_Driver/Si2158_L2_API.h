/***************************************************************************************
                  Silicon Laboratories Broadcast Si2158 Layer 2 API
   L2 API header for commands and properties
   FILE: Si2158_L2_API.h
   Supported IC : Si2158
   Compiled for ROM 33 firmware 2_0_build_4
   Revision: 0.1
   Date: July 30 2012
  (C) Copyright 2012, Silicon Laboratories, Inc. All rights reserved.
****************************************************************************************/

#ifndef   Si2158_L2_API_H
#define   Si2158_L2_API_H

#include "Si2158_L1_API.h"
#include "Si2158_Properties_Strings.h"
#include "Si2158_firmware_0_L_build_8.h"
#include "Si2158_firmware_0_E_build_15.h"
#include "Si2158_firmware_2_0_build_x.h"

#if defined (__cplusplus)
extern "C" {
#endif

int  Si2158_Init                      (L1_Si2158_Context *api);
int  Si2158_Configure                 (L1_Si2158_Context *api);
int  Si2158_PowerUpWithPatch          (L1_Si2158_Context *api);
int  Si2158_LoadFirmware              (L1_Si2158_Context *api, unsigned char *fw_table, int lines);
int Si2158_LoadFirmware_16            (L1_Si2158_Context *api, firmware_struct58 fw_table[], int nbLines);
int  Si2158_StartFirmware             (L1_Si2158_Context *api);

/* _specific_code_insertion_start */
int Si2158_UpdateChannelScanFrequency(int freq,int channelsFound);
int Si2158_GetRF                 (L1_Si2158_Context *api);
int Si2158_Tune                  (L1_Si2158_Context *api, unsigned char mode, unsigned long freq);
int Si2158_ATVTune               (L1_Si2158_Context *api, unsigned long freq, unsigned char video_sys, unsigned char color, unsigned char invert_signal);
int Si2158_DTVTune               (L1_Si2158_Context *api, unsigned long freq, unsigned char bw, unsigned char modulation, unsigned char invert_spectrum);
int Si2158_XoutOn                (L1_Si2158_Context *api);
int Si2158_XoutOff               (L1_Si2158_Context *api);
int Si2158_Standby               (L1_Si2158_Context *api);
int Si2158_Powerdown             (L1_Si2158_Context *api);
int Si2158_LoadVideofilter     (L1_Si2158_Context *api, vid_filt_struct_58 vidFiltTable[], int lines);
int Si2158_ATV_Channel_Scan_M(L1_Si2158_Context *Si2158, unsigned long rangeMinHz, unsigned long rangeMaxHz, int minRSSIdBm, int maxRSSIdBm);
int Si2158_ATV_Channel_Scan_PAL(L1_Si2158_Context *Si2158, unsigned long rangeMinHz, unsigned long rangeMaxHz, int minRSSIdBm, int maxRSSIdBm);
#define Si2158_FORCE_NORMAL_AGC       0
#define Si2158_FORCE_MAX_AGC          1
#define Si2158_FORCE_TOP_AGC          2
int Si2158_AGC_Override    (L1_Si2158_Context *Si2158, unsigned char mode );

/* _specific_code_insertion_point */
void Send2158Command(L1_Si2158_Context *Si2158,unsigned char ucCmd, unsigned char *ucArg, unsigned char ucLen);

#if defined (__cplusplus)
};
#endif

#endif /* Si2158_L2_API_H */





