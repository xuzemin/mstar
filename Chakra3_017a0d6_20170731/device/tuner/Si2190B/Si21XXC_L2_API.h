/***************************************************************************************
                  Silicon Laboratories Broadcast Si21XXC Layer 2 API

   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
     PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.

   L2 API header for commands and properties
   FILE: Si21XXC_L2_API.h
   Supported IC : Si2178B,Si2190B,Si2191B,Si2191C
   Compiled for ROM 71 firmware 3_0_build_1
   Revision: 0.1
   Tag:  Si2190B_30b1_Si2178B_42b7_Si2191C_30b1_Si2191B_42b7_V0.1
   Date: August 12 2015
  (C) Copyright 2012, Silicon Laboratories, Inc. All rights reserved.
****************************************************************************************/

#ifndef   Si21XXC_L2_API_H
#define   Si21XXC_L2_API_H

#include "Si21XXC_L1_API.h"
#include "Si21XXC_Properties_Strings.h"

#ifdef __cplusplus
extern "C"{
#endif
int  Si21XXC_Init                      (L1_Si21XXC_Context *api);
int  Si21XXC_Configure                 (L1_Si21XXC_Context *api);
int  Si21XXC_PowerUpOnly               (L1_Si21XXC_Context *api);//csm,13'
int  Si21XXC_PowerUpWithPatch          (L1_Si21XXC_Context *api);
int  Si21XXC_PowerUpUsingBroadcastI2C  (L1_Si21XXC_Context *tuners[], int tuner_count );
int  Si2191C_SetupISL                  (L1_Si21XXC_Context *tuners[], int tuner_no );
int  Si2191C_TestISL                   (L1_Si21XXC_Context *Tuner1,L1_Si21XXC_Context *Tuner2,unsigned long T1freq, unsigned long T2freq);
int  Si21XXC_LoadFirmware              (L1_Si21XXC_Context *api, unsigned char *fw_table, int lines);
int  Si21XXC_LoadFirmware_16           (L1_Si21XXC_Context *api, firmware_struct fw_table[], int nbLines);
int  Si21XXC_StartFirmware             (L1_Si21XXC_Context *api);

/* _specific_code_insertion_start */
int Si21XXC_UpdateChannelScanFrequency(int freq,int channelsFound);
int Si21XXC_GetRF                 (L1_Si21XXC_Context *api);
int Si21XXC_Tune                  (L1_Si21XXC_Context *api, unsigned char mode, unsigned long freq,unsigned char tunint_check,unsigned int AtvTimeout);//csm,13
int Si21XXC_ATVTune               (L1_Si21XXC_Context *api, unsigned long freq, unsigned char video_sys, unsigned char color, unsigned char invert_signal,unsigned char tunint_check,unsigned int AtvTimeoutint);//csm,13
int Si21XXC_DTVTune               (L1_Si21XXC_Context *api, unsigned long freq, unsigned char bw, unsigned char modulation, unsigned char invert_spectrum);
int Si21XXC_XoutOn                (L1_Si21XXC_Context *api);
int Si21XXC_XoutOff               (L1_Si21XXC_Context *api);
int Si21XXC_Standby               (L1_Si21XXC_Context *api);
int Si21XXC_Powerdown             (L1_Si21XXC_Context *api);
int Si21XXC_LoadVideofilter       (L1_Si21XXC_Context *api,  vid_filt_struct vidFiltTable[], int lines);
void  publishFirmwarePointer(L1_Si21XXC_Context *api,unsigned long *fw_addr,unsigned long *fw_size);//related to kernel driver
#define Si21XXC_FORCE_NORMAL_AGC       0
#define Si21XXC_FORCE_MAX_AGC          1
#define Si21XXC_FORCE_TOP_AGC          2
int Si21XXC_AGC_Override    (L1_Si21XXC_Context *Si21XXC, unsigned char mode );
int Si21XXC_Tuner_Block_VCO      (L1_Si21XXC_Context *api, int vco_code);
/* _specific_code_insertion_point */
//#if defined(MODEL_CN)
int Si21XXC_ReadPropertyArray            (L1_Si21XXC_Context *api);
//#endif

#ifdef __cplusplus
}
#endif
#endif /* Si21XXC_L2_API_H */





