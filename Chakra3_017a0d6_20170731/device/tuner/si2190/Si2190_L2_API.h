/***************************************************************************************
                  Silicon Laboratories Broadcast Si2190 Layer 2 API
   L2 API header for commands and properties
   FILE: Si2190_L2_API.h
   Supported IC : Si2190
   Compiled for ROM 40 firmware 0_A_build_10
   Revision: 0.1
   Date: August 13 2012
  (C) Copyright 2012, Silicon Laboratories, Inc. All rights reserved.
****************************************************************************************/

#ifndef   Si2190_L2_API_H
#define   Si2190_L2_API_H

#include "Si2190_L1_API.h"
#include "Si2190_Properties_Strings.h"

int  Si2190_Init                      (L1_Si2190_Context *api);
int  Si2190_Configure                 (L1_Si2190_Context *api);
int  Si2190_PowerUpWithPatch          (L1_Si2190_Context *api);
int  Si2190_LoadFirmware              (L1_Si2190_Context *api, firmware_struct *fw_table, int lines);
int  Si2190_StartFirmware             (L1_Si2190_Context *api);

/* _specific_code_insertion_start */
int Si2190_UpdateChannelScanFrequency(int freq,int channelsFound);
int Si2190_GetRF                 (L1_Si2190_Context *api);
int Si2190_Tune                  (L1_Si2190_Context *api, unsigned char mode, unsigned long freq);
int Si2190_ATVTune               (L1_Si2190_Context *api, unsigned long freq, unsigned char video_sys, unsigned char color, unsigned char invert_signal);
int Si2190_DTVTune               (L1_Si2190_Context *api, unsigned long freq, unsigned char bw, unsigned char modulation, unsigned char invert_spectrum);
int Si2190_XoutOn                (L1_Si2190_Context *api);
int Si2190_XoutOff               (L1_Si2190_Context *api);
int Si2190_Standby               (L1_Si2190_Context *api);
int Si2190_Powerdown             (L1_Si2190_Context *api);
int Si2190_LoadVideofilter       (L1_Si2190_Context *api,  vid_filt_struct vidFiltTable[], int lines);
int Si2190_ATV_Channel_Scan_M    (L1_Si2190_Context *api, unsigned long rangeMinHz, unsigned long rangeMaxHz, int minRSSIdBm, int maxRSSIdBm, int minSNRHalfdB, int maxSNRHalfdB);
int Si2190_ATV_Channel_Scan_PAL  (L1_Si2190_Context *api, unsigned long rangeMinHz, unsigned long rangeMaxHz, int minRSSIdBm, int maxRSSIdBm, int minSNRHalfdB, int maxSNRHalfdB);
#define Si2190_FORCE_NORMAL_AGC       0
#define Si2190_FORCE_MAX_AGC          1
#define Si2190_FORCE_TOP_AGC          2
int Si2190_AGC_Override    (L1_Si2190_Context *Si2190, unsigned char mode );
/* _specific_code_insertion_point */

///tqy
int SSVD_AIC_ON(L1_Si2190_Context *Si2190Ct);
int SSVD_AIC_OFF(L1_Si2190_Context *Si2190CT);

//XuGuang's Functions

unsigned char Si2190_Set_DTV_LIF_FREQ  (L1_Si2190_Context *api, unsigned int IFKHz);
unsigned char Si2190_Set_DTV_LIF_OUT  (L1_Si2190_Context *api, unsigned char lif_out_offset,  unsigned char lif_out_amp);
unsigned char Si2190_Set_DTV_MODE  (L1_Si2190_Context *api, unsigned char bw, unsigned char invert_spectrum, unsigned char modulation);
unsigned char Si2190_Set_ATV_SIF_OUT  (L1_Si2190_Context *api, unsigned char amp, unsigned char offset);
unsigned char Si2190_Set_TUNER_LO_INJECTION  (L1_Si2190_Context *api, unsigned char band_1, unsigned char band_2, unsigned char band_3);
unsigned char Si2190_Set_ATV_AGC_SPEED  (L1_Si2190_Context *api, unsigned char if_agc_speed);
unsigned char Si2190_Set_ATV_RF_TOP (L1_Si2190_Context *api, unsigned char atv_rf_top);
unsigned char Si2190_Set_DTV_RF_TOP (L1_Si2190_Context *api, unsigned char dtv_rf_top);



#endif /* Si2190_L2_API_H */





