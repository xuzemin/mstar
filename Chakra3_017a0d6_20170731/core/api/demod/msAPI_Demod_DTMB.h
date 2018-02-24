#ifndef _MSAPI_DEMOD_DTMB_H_
#define _MSAPI_DEMOD_DTMB_H_

#include "Board.h"
#include "Tuner.h"
#include "COFDM_Demodulator.h"


#if(ENABLE_DTMB)

 #if ( (FRONTEND_DEMOD_DTMB_TYPE == EMBEDDED_DTMB_DEMOD)        \
     ||(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB)         \
     ||(FRONTEND_DEMOD_DTMB_TYPE == MSTAR_MSB101M_DTMB_MSD046B) \
     ||(FRONTEND_DEMOD_DTMB_TYPE == EXTERNAL_DTMB_DEMOD)        \
     )
    #include "drvDMD_common.h"
    #include "drvDMD_DTMB.h"
 #else


 #endif


//==============================================

BOOL msAPI_Demod_DTMB_Init(void);

void msAPI_Demod_DTMB_Set_Power(BOOL bTurnOn);

void msAPI_Demod_DTMB_Exit(void);

//FUNCTION_RESULT msAPI_Demod_DTMB_Get_SignalStrength(U16 *pu16Strength);

EnuApiDemodLockStatus msAPI_Demod_DTMB_Get_LockStatus(void);
EnuApiDemodLockStatus msAPI_Demod_DTMB_DetectLockTask(void);
void devCOFDM_DTMB_SetFrequency(DWORD dwFrequency, RF_CHANNEL_BANDWIDTH eBandWidth, RF_CHANNEL_HP_LP eHpLp, U8 u8PlpID);
void devCOFDM_DTMB_SwitchTransportSteamInferface(TS_INTERFACE interface);
FUNCTION_RESULT devCOFDM_DTMB_GetSignalStrength(WORD *strength);

#endif

#endif

