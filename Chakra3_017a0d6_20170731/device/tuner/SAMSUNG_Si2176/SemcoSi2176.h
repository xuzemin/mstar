/********************************************************************
* SemcoSi2176.h
* Si2176 Header
* By yooheeyong 2011/05/23
*********************************************************************/


#ifndef _Si2176_H
#define _Si2176_H

#if defined( __cplusplus )
extern "C"                     /* Use "C" external linkage                  */
{
#endif

#include "Si2176_L2_TV_Chassis.h"
#define _MSTAR
/* 튜너 설정값을 위한 구조체   */
typedef struct _Si2176Config {
      unsigned char nSel_dtv_out_type;
      unsigned char nSel_dtv_agc_source;
      int           nSel_dtv_lif_freq_offset;
      unsigned char nSel_dtv_mode_bw;
      unsigned char nSel_dtv_mode_invert_spectrum;
      unsigned char nSel_dtv_mode_modulation;
      unsigned char nSel_atv_video_mode_video_sys;
    unsigned char nSel_atv_audio_mode_audio_sys;
    unsigned char nSel_atv_atv_video_mode_tran;
      unsigned char nSel_atv_video_mod_color;
      unsigned char nSel_atv_mode_invert_spectrum;
      unsigned char nSel_atv_mode_invert_signal;
    char          nSel_atv_cvbs_out_fine_amp;
    char          nSel_atv_cvbs_out_fine_offset;
    unsigned char nSel_atv_sif_out_amp;
    unsigned char nSel_atv_sif_out_offset;
      unsigned char if_agc_speed;
}Si2176Config, *lpSi2176Config;

#define  SEMCO_TUNE_DIGITAL          19
#define  SEMCO_TUNE_ANALOG_B         0
#define  SEMCO_TUNE_ANALOG_G         1
#define  SEMCO_TUNE_ANALOG_M     2
#define  SEMCO_TUNE_ANALOG_N     3
#define  SEMCO_TUNE_ANALOG_I     4
#define  SEMCO_TUNE_ANALOG_DK    5
#define  SEMCO_TUNE_ANALOG_L     6
#define  SEMCO_TUNE_ANALOG_LP    7

#define  SEMCO_ANALOG_AUDIO_RSVD         0
#define  SEMCO_ANALOG_AUDIO_MONO         1
#define  SEMCO_ANALOG_AUDIO_MONO_NICAM   2
#define  SEMCO_ANALOG_AUDIO_A2           3
#define  SEMCO_ANALOG_AUDIO_A2_DK2       4
#define  SEMCO_ANALOG_AUDIO_A2_DK3       5
#define  SEMCO_ANALOG_AUDIO_BTSC         6
#define  SEMCO_ANALOG_AUDIO_EIAJ         7
#define  SEMCO_ANALOG_AUDIO_SCAN         8

#define  SEMCO_DTV_MODE_ATSC         0
#define  SEMCO_DTV_MODE_QAM_US       1
#define  SEMCO_DTV_MODE_DVBT         2
#define  SEMCO_DTV_MODE_DVBC         3
#define  SEMCO_DTV_MODE_ISDBT        4
#define  SEMCO_DTV_MODE_ISDBC        5
#define  SEMCO_DTV_MODE_DTMB         6


/* Initialize Si2176 */
int           Si2176_Initialize(L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj *lprsp, Si2176_PropObj *lpprop, unsigned char bXTal_Internal_External);
/* Set Configuration */
unsigned char Si2176_Configure (L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj  *rsp, Si2176_PropObj *lpprop, unsigned char bXTal_Internal_External);
/* Set FEF AGC Speed */
unsigned char Si2176_Configure_AGC_FEF(L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj  *rsp, Si2176_PropObj *lpprop);
/* Reset AGC Speed */
unsigned char Si2176_Configure_AGC_RESET(L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj  *rsp, Si2176_PropObj *lpprop);
/* Set Frequency */
/* MFT 관련 파라메터 추가(nCenterFrequency_KHz), by yooheeyong 20101028 */
unsigned char Si2176_SetFrequency(unsigned char nDTV_ATV, L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj *lprsp, unsigned long nFrequency_KHz, unsigned long nCenterFrequency_KHz, int bTunTINTCheck);
/* Check Tuner status */
unsigned char Si2176_GetTunerStatus(L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj *lprsp);
/* Check Analog status */
unsigned char Si2176_GetAnalogStatus(L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj *lprsp);
/* Check Digital status */
unsigned char Si2176_GetDigitalStatus(L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj *lprsp);
/* Si2176 On */
void Si2176_On(L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj  *lprsp);
/* Si2176 StandBy */
void Si2176_StandBy(L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj  *lprsp);

/* Get Carrier Frequency Offset */
int Si2176_GetCarrierFreqOffset(L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj  *lprsp);
/* Retrun Voltage for carrier freq. offset of AFT */
float Si2176_ReturnVoltage(Si2176_CmdReplyObj  *lprsp);
/* Set recommend Amp of a CVBS and a SIF */
unsigned char Si2176_SetAmpForCVBS_SIF(unsigned char nDTV_ATV,L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj  *rsp, Si2176_PropObj *lpprop);
/* Set Audio Sys for Auto Scan */
unsigned char Si2176_SetAudioSysForAutoScan(unsigned char nSel_atv_audio_mode_audio_sys, L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj  *rsp, Si2176_PropObj *lpprop);
/*  Set MFT */
unsigned char Si2176_SetMFT(int nStep, L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj  *rsp, Si2176_PropObj *lpprop);

/* ATV Sync Lock */
unsigned char Si2176_ATV_Sync_Lock(L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj *lprsp);
/* ATV Master Lock */
unsigned char Si2176_ATV_Master_Lock(L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj *lprsp);

/* Get RSSI */
int Si2176_GetRSSI(L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj  *lprsp);

/* 임시 코드 */
/* Set AFC Range */
unsigned char Si2176_Configure_AFC_Range(L1_Si2176_Context *lpSi2176, Si2176_CmdReplyObj  *rsp, Si2176_PropObj *lpprop, int nSelAFC);



#if defined( __cplusplus )
}
#endif


#endif

