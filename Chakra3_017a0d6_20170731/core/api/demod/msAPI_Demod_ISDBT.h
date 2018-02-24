#ifndef _MSAPI_DEMOD_ISDBT_H_
#define _MSAPI_DEMOD_ISDBT_H_

#include "Board.h"


#if (ENABLE_ISDBT)

#include "COFDM_Demodulator.h"

#if (FRONTEND_DEMOD_ISDBT_TYPE == EMBEDDED_ISDBT_DEMOD)
    #if DEMOD_ISDBT_USE_UTOPIA
        #include "drvDMD_common.h"
        #include "drvDMD_ISDBT.h"
        //#include "INTERN_ISDBT.h"
    #else
        #include "INTERN_ISDBT.h"
    #endif

#elif (FRONTEND_DEMOD_ISDBT_TYPE == MSTAR_MSB1400_DEMOD)
    #include "drvDMD_common.h"
    #include "drvDMD_ISDBT.h"
    //#include "EXTERN_ISDBT.h"
#endif

//==============================================


BOOL msAPI_Demod_ISDBT_Init(void);

void msAPI_Demod_ISDBT_Exit(void);

FUNCTION_RESULT msAPI_Demod_ISDBT_Get_SignalStrength(U16 *pu16Strength);

EnuApiDemodLockStatus msAPI_Demod_ISDBT_Get_LockStatus(void);
EnuApiDemodLockStatus msAPI_Demod_ISDBT_DetectLockTask(void);
void devCOFDM_ISDBT_SetFrequency(DWORD dwFrequency, RF_CHANNEL_BANDWIDTH eBandWidth, RF_CHANNEL_HP_LP eHpLp, U8 u8PlpID);
void devCOFDM_ISDBT_SwitchTransportSteamInferface(TS_INTERFACE interface);
BYTE devCOFDM_ISDBT_GetSignalToNoiseRatio(void);
FUNCTION_RESULT devCOFDM_ISDBT_GetSignalStrength(WORD *strength);
FUNCTION_RESULT devCOFDM_ISDBT_GetSignalQuality(WORD *quality);

#endif

#endif

