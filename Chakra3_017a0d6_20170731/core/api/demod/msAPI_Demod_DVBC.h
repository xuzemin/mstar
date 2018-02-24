#ifndef _MSAPI_DEMOD_DVBC_H_
#define _MSAPI_DEMOD_DVBC_H_

#include "Board.h"


typedef enum
{
    QAM_FEC_LOCK,
    QAM_PSYNC_LOCK,
    //QAM_TPS_LOCK,
    QAM_NO_CHANNEL, //ADD
    QAM_DCR_LOCK,
    QAM_AGC_LOCK,
    //QAM_MODE_DET,
    QAM_ATV_DETECT, //ADD
    QAM_TR_LOCK, //ADD

} QAM_LOCK_STATUS;

#if( ENABLE_DEMOD_DVBC )

#include "QAM_Demodulator.h"

 #if( (FRONTEND_DEMOD_DVBC_TYPE == EMBEDDED_DVBC_DEMOD) )

 #else

 #endif


//==============================================


BOOL msAPI_Demod_DVBC_Init(void);

void msAPI_Demod_DVBC_Set_Power(BOOL bTurnOn);

void msAPI_Demod_DVBC_Exit(void);

EnuApiDemodLockStatus msAPI_Demod_DVBC_Get_LockStatus(void);
EnuApiDemodLockStatus msAPI_Demod_DVBC_DetectLockTask(void);


FUNCTION_RESULT msAPI_Demod_DVBC_Get_SignalStrength(U16 *pu16Strength);


#endif

#endif

