#ifndef _MSAPI_DEMOD_ATSC_H_
#define _MSAPI_DEMOD_ATSC_H_

#include "Board.h"


#if (ENABLE_ATSC)

typedef enum
{
    DEMOD_ATSC_MODE_NTSC,
    DEMOD_ATSC_MODE_256QAM,
    DEMOD_ATSC_MODE_64QAM,
    DEMOD_ATSC_MODE_8VSB,
    DEMOD_ATSC_MODE_NUM
} EN_DEMOD_ATSC_MODE;

typedef enum
{
    DEMOD_ATSC_SPECTRUM_NORMAL,
    DEMOD_ATSC_SPECTRUM_INVERTER,
    DEMOD_ATSC_SPECTRUM_AUTO
} EN_DEMOD_ATSC_SPECTRUM_MODE;

//==============================================

void msAPI_Demod_ATSC_Exit(void);

BOOLEAN msAPI_Demod_ATSC_Reset(void);

FUNCTION_RESULT msAPI_Demod_ATSC_Get_SignalStrength(U16 *pu16Strength);

BOOLEAN msAPI_Demod_ATSC_Set_Mode(EN_DEMOD_ATSC_MODE enModulation, EN_DEMOD_ATSC_SPECTRUM_MODE enSpectrumType);

BOOLEAN msAPI_Demod_ATSC_Get_Lock(EN_DEMOD_ATSC_MODE enModulation);

void msAPI_Demod_ATSC_Init(void);

EN_DEMOD_ATSC_MODE msAPI_Demod_ATSC_Get_ModulationMode(void);

#if (NEW_DEMOD_SCAN)
void msAPI_Qam_No_Channel_Detect(void);
#endif

//======================================================

//======================================================

#endif // ENABLE_ATSC

#endif // _MSAPI_DEMOD_ATSC_H_

