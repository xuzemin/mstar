#ifndef _NMI120_DEFINE_H
#define _NMI120_DEFINE_H
#define TN_FREQ_STEP                FREQ_STEP_50KHz//FREQ_STEP_50KHz//FREQ_STEP_62_5KHz//FREQ_STEP_50KHz//FREQ_STEP_31_25KHz

#define _TUNER_I2C_ID        0xC0

//***********No used for Silicon tuner,but for API*******************************
#define VHF_LOWMIN_FREQ        46250L    // KHz
#define VHF_LOWMAX_FREQ        142000L    // KHz
#define VHF_HIGHMIN_FREQ    149000L    // KHz
#define VHF_HIGHMAX_FREQ    426000L    // KHz
#define UHF_MIN_FREQ        434000L    // KHz
#define UHF_MAX_FREQ        863250L    // KHz
#define TUNER_IF_FREQ_KHz            38900L    // KHz
#define TUNER_L_PRIME_IF_FREQ_KHz    33950L    // KHz

MS_BOOL devTunerInit(void);
MS_BOOL devTunerSetPLLData(MS_U32 dwFreq, MS_U8 ucBw);
int NMI120_GetLockStatus(void);
int NMI120_GetRSSI(MS_U8 outputChoice);
MS_BOOL MDrv_Tuner_PowerOnOff(MS_BOOL bPowerOn);
MS_BOOL NMI120_LoopThrough(void);

#endif


