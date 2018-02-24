#ifndef _MSAPI_DEMOD_DVBT2_H_
#define _MSAPI_DEMOD_DVBT2_H_

#include "Board.h"


#if(ENABLE_DEMOD_DVBT2)


//#include "demodulator_T2.h"


//==============================================

BOOL msAPI_Demod_DVBT2_Init(void);

void msAPI_Demod_DVBT2_Set_Power(BOOL bTurnOn);

void msAPI_Demod_DVBT2_Exit(void);

EnuApiDemodLockStatus msAPI_Demod_DVBT2_Get_LockStatus(void);
EnuApiDemodLockStatus msAPI_Demod_DVBT2_DetectLockTask(void);


BOOLEAN msAPI_Demod_DVBT2_Get_PostViterbiBer(float *ber);


#endif

#endif


