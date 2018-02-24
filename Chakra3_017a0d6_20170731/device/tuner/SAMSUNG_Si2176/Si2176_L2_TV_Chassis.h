/***************************************************************************************/
/* FILE: Si2176_L2_TV_Chassis.h                                                        */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/***************************************************************************************/
#ifndef Si2176_L2_TV_CHASSIS_H
#define Si2176_L2_TV_CHASSIS_H

#include "Si2176_L1_API_TV_Chassis.h"    /* L1 helper functions */
#include "Si2176_Commands.h"             /* Si2176 API Command defines and function prototypes */
#include "Si2176_Properties.h"           /* Si2176 API Property defines and function prototypes */


int   ProcessAPITopLevelSequence(void) ;
int     Si2176_Init(L1_Si2176_Context *Si2176);
int     Si2176_PowerUpWithPatch (L1_Si2176_Context *Si2176);
int     Si2176_LoadFirmware (L1_Si2176_Context *Si2176,unsigned char* firmwareTable,int lines);
int     Si2176_StartFirmware (L1_Si2176_Context *Si2176, Si2176_CmdReplyObj *rsp);
int     Si2176_Configure1 (L1_Si2176_Context *Si2176, Si2176_CmdReplyObj *rsp);
int   Si2176_LoadVideofilter (L1_Si2176_Context *Si2176,unsigned char* vidfiltTable,int lines) ;
int     Si2176_ATVTune (L1_Si2176_Context *Si2176, unsigned long freq, unsigned char video_sys, unsigned char trans,unsigned char color,unsigned char invert_signal,Si2176_CmdReplyObj *rsp);
int     Si2176_Tune (L1_Si2176_Context *Si2176, unsigned char mode, unsigned long freq, Si2176_CmdReplyObj *rsp );
int     Si2176_DTVTune (L1_Si2176_Context *Si2176, unsigned long freq, unsigned char bw, unsigned char modulation, unsigned char invert_spectrum, Si2176_CmdReplyObj *rsp);
int   Si2176_ATV_Channel_Scan_M  (L1_Si2176_Context *Si2176, unsigned long rangeMinHz, unsigned long rangeMaxHz, int minRSSIdBm, int maxRSSIdBm, int minSNRHalfdB, int maxSNRHalfdB);
int   Si2176_ATV_Channel_Scan_PAL(L1_Si2176_Context *Si2176, unsigned long rangeMinHz, unsigned long rangeMaxHz, int minRSSIdBm, int maxRSSIdBm, int minSNRHalfdB, int maxSNRHalfdB);

int     Si2176_ATVConfig (L1_Si2176_Context *Si2176 );
int     Si2176_DTVConfig (L1_Si2176_Context *Si2176 );
int   Si2176_CommonConfig (L1_Si2176_Context *Si2176);
int   Si2176_TunerConfig (L1_Si2176_Context *Si2176); 
int   Si2176_SetupTunerDefaults(void);
int   Si2176_SetupCommonDefaults(void);
int   Si2176_SetupATVDefaults (void);
int   Si2176_SetupDTVDefaults (void);
int   TunerFrequencyChanged(unsigned long *frequency);
int   UpdateChannelScanFrequency(int freq,int channelsFound);

/*************************************************************************************************************
  Made by Semco API for compatible Si2173 API
 ************************************************************************************************************************/

#define  SI2176_XTAL_INTERNAL   1
#define  SI2176_XTAL_EXTERNAL   2

int configureSi2176 (L1_Si2176_Context *Si2176, Si2176_CmdReplyObj  *rsp1, Si2176_PropObj *lpprop, unsigned char bXTal_Internal_External);
int Tune(L1_Si2176_Context *Si2176, unsigned char mode, Si2176_CmdReplyObj *rsp1, unsigned long rf_frequency);
int TunerStatus (L1_Si2176_Context *Si2176, Si2176_CmdReplyObj  *rsp1);
int ATVStatus (L1_Si2176_Context *Si2176, Si2176_CmdReplyObj  *rsp1);
int DTVStatus (L1_Si2176_Context *Si2176, Si2176_CmdReplyObj  *rsp1);
int Xout_On  (L1_Si2176_Context *Si2176, Si2176_CmdReplyObj *rsp1);
int Xout_Off  (L1_Si2176_Context *Si2176, Si2176_CmdReplyObj *rsp1);
int PowerUp (L1_Si2176_Context *Si2176, Si2176_CmdReplyObj  *rsp1);
int PowerDown (L1_Si2176_Context *Si2176, Si2176_CmdReplyObj  *rsp1);
int CheckStatus  (L1_Si2176_Context *Si2176, Si2176_COMMON_REPLY_struct *status);


#endif
