#ifndef _MSAPI_DEMOD_DVBT_H_
#define _MSAPI_DEMOD_DVBT_H_

#include "Board.h"
#include "Tuner.h"
#include "COFDM_Demodulator.h"

#if(ENABLE_DEMOD_DVBT)


//#include "COFDM_Demodulator.h"


//==============================================

BOOL msAPI_Demod_DVBT_Init(void);

void msAPI_Demod_DVBT_Set_Power(BOOL bTurnOn);

void msAPI_Demod_DVBT_Exit(void);

BOOLEAN msAPI_Demod_DVBT_Get_PostViterbiBer(float *ber);

EnuApiDemodLockStatus msAPI_Demod_DVBT_Get_LockStatus(void);
EnuApiDemodLockStatus msAPI_Demod_DVBT_DetectLockTask(void);

void devCOFDM_DVBT_SetFrequency(DWORD dwFrequency, RF_CHANNEL_BANDWIDTH eBandWidth, RF_CHANNEL_HP_LP eHpLp, U8 u8PlpID);
void devCOFDM_DVBT_SwitchTransportSteamInferface(TS_INTERFACE interface);
FUNCTION_RESULT devCOFDM_DVBT_GetSignalStrength(WORD *strength);

#endif // #if(ENABLE_DEMOD_DVBT)

#endif // #ifndef _MSAPI_DEMOD_DVBT_H_

