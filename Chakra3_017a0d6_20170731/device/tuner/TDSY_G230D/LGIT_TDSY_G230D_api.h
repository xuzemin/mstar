/****************************************************************************
*
* 							LG Innotek Co.,Ltd.
*
* Copyright (C) 2012, LG Innotek, Gwangju, Korea, All Rights Reserved.
*
* File: LGIT_TDSY_G230D_api.h
*
* version: 1.00.00
*
* Description: LGIT_TDSY_G230D* Tuner API prototype
*
* Description			Version		Date		Author
* ---------------------------------------------------------------------
* Create				1.00.00		2012.03.28	JH.KIM
****************************************************************************/

#ifndef _LGIT_TUNER_TDSY_G230D_API_H
#define _LGIT_TUNER_TDSY_G230D_API_H
#include "LGIT_Tuner_Common.h"
#include "LGIT_Tuner_bsp.h"
#include "Si2158_Driver/Si2158_L2_API.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* I2C Initialize */
void LGIT_TDSY_G230D_Open(void);

/* IC Initialize, call this  function after H/W reset */
MS_BOOL LGIT_TDSY_G230D_Initialize(void);

/* Set some parameter for each standard when changing standard */
void LGIT_TDSY_G230D_ChangeStandard( 
                           Lgit_tuner_standard_t standard,
                           Lgit_tuner_bandwidth_t bandwidth);
#if 0
/* Preset some parameter before tuning for specific tuner model */
void LGIT_TDSY_G230D_PreSet(
                 unsigned int RfFreqKHz, 
                 Lgit_tuner_standard_t standard, 
                 Lgit_tuner_bandwidth_t bandwidth);
#endif
/* Tune */
void LGIT_TDSY_G230D_Tune(
                 unsigned int RfFreqKHz, 
                 Lgit_tuner_standard_t standard,
                 Lgit_tuner_bandwidth_t bandwidth);
#if 0
/* Postset some parameter after tuning for specific tuner model */
void LGIT_TDSY_G230D_PostSet(
                  unsigned int RfFreqKHz, 
                  Lgit_tuner_standard_t standard, 
                  Lgit_tuner_bandwidth_t bandwidth);
#endif
/* Monitoring */
void LGIT_TDSY_G230D_MonitorTuner(
                  Lgit_tuner_standard_t standard,
                  int *TuneComplete,
                  int *InputLevel,
                  int *AtvTunerLockStatus,
                  int *AtvOffset);

/* Get Tuner Settings */
void LGIT_TDSY_G230D_GetTunerSettings(void);

/* I2C Close */
void LGIT_TDSY_G230D_Close(void);

/* Setup Defaults property. Called by Init */
void setupATVDefaults        (L1_Si2158_Context *api);
void setupCOMMONDefaults     (L1_Si2158_Context *api);
void setupDTVDefaults        (L1_Si2158_Context *api);
void setupTUNERDefaults      (L1_Si2158_Context *api);

#ifdef __cplusplus
}
#endif

#endif /* _LGIT_TUNER_TDSY_G230D_API_H */