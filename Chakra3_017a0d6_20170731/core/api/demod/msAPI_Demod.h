#ifndef _MSAPI_DEMOD_H_
#define _MSAPI_DEMOD_H_

#include "Board.h"

#if(ENABLE_DTV)
#include "debug.h"

#include "msAPI_Demod_Basic.h"

#define DEBUG_DEMOD(x)      //do{ msDebug_ANSI_SetColorText(E_FONT_COLOR_BLACK); msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_YELLOW); x; msDebug_ANSI_AllAttrOffText();} while(0)
#define DEBUG_DEMOD_S(x)    //do{ msDebug_ANSI_SetColorText(E_FONT_COLOR_BLACK); msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_YELLOW); x; msDebug_ANSI_AllAttrOffText();} while(0)

//#ifndef DEMOD_USE_UTOPIA
//    #define DEMOD_USE_UTOPIA    (USE_UTOPIA)
//#endif

//----------------------------------------------------------------------------
#if( ENABLE_DVBT )
    #include "msAPI_Demod_DVBT.h"
#endif

#if ENABLE_DVB_T2
    #include "msAPI_Demod_DVBT2.h"
#endif

#if(ENABLE_DTMB)
    #include "msAPI_Demod_DTMB.h"
#endif

#if (ENABLE_ATSC)
    #include "msAPI_Demod_ATSC.h"
#endif

#if 1//(ENABLE_DVBC)
    #include "msAPI_Demod_DVBC.h"
#endif

#if (ENABLE_DEMOD_ISDBT)
    #include "msAPI_Demod_ISDBT.h"
#endif

#if(ENABLE_DEMOD_DVBS)
    #include "msAPI_Demod_S.h"
#endif


//----------------------------------------------------------------------------

void msAPI_Demod_SetCurrentDemodType(EN_DEMODULATOR_TYPE eDemodType);
#if (ENABLE_CI_PLUS_V1_4)
BOOLEAN msAPI_Demod_IsSupportDemodType(EN_DEMODULATOR_TYPE eDemodType);
#endif
EN_DEMODULATOR_TYPE msAPI_Demod_GetCurrentDemodType(void);

char* msAPI_Demod_Get_DemodTypeName(EN_DEMODULATOR_TYPE eDemodType);

//----------------------------------------------------------------------------

typedef enum
{
    E_INIT_DEMOD_FOR_POWER_ON,
    E_INIT_DEMOD_FOR_SCAN,
    E_INIT_DEMOD_FOR_CHANGE_SOURCE,
    E_INIT_DEMOD_FOR_CHANGE_CHANNEL,
} EnuInitDemodCase;
//INTERFACE void msAPI_Tuner_Initialization(BOOL bSrcChg, EN_DEMODULATOR_TYPE eNewDemodTypeToInit);
void msAPI_Demod_Init(EnuInitDemodCase eInitDemodCase, EN_DEMODULATOR_TYPE eNewDemodTypeToInit);

void msAPI_Demod_Init_ForChangeSource(void);
void msAPI_Demod_Init_ForChangeChannel(void);

//----------------------------------------------------------------------------

void msAPI_Demod_Set_Power( EN_DEMODULATOR_TYPE eDemodType, BOOL bTurnOn);
void msAPI_Demod_Set_TsSerialOrParallel( EN_DEMODULATOR_TYPE eDemodType, BOOL bTsIsParallel);

void msAPI_Demodulator_Exit(void);

//void msAPI_Demod_Reset(void);

U16 msAPI_Demod_Get_CheckLockTimeout(void);

U8 msAPI_Demod_Get_SNR(EN_DEMODULATOR_TYPE eDemodType);
U16 msAPI_Demod_Get_SignalQualityPercentage(EN_DEMODULATOR_TYPE eDemodType);

BOOL msAPI_Demod_Get_SignalStrength(EN_DEMODULATOR_TYPE eDemodType, U16 * pu16SignalStrength);

//----------------------------------------------------------------------------

EnuApiDemodLockStatus msAPI_Demod_Get_LockStatus(EN_DEMODULATOR_TYPE eDemodType );

void msAPI_Demod_Init_DetectLockTask(void);
U32 msAPI_Demod_Get_DetectLockUseTime(void);
EnuApiDemodLockStatus msAPI_Demod_DetectLockTask(void);
BOOLEAN msAPI_Demod_CheckLock(BOOLEAN *CheckLockResult, BOOLEAN fScan);

//----------------------------------------------------------------------------

#include "COFDM_Demodulator.h"

//---------------------------------------------------------------------------------------
typedef enum
{
    E_DEMOD_TSP_PATH_CASE_NORMAL,
#if(ENABLE_PVR)
    E_DEMOD_TSP_PATH_CASE_PVR_REC, // What's different?
    E_DEMOD_TSP_PATH_CASE_PVR_PLAY,
#endif
#if(ENABLE_CI)
    #if(ENABLE_CI_PLUS)
    /* Pass-Through Mode */ // CI to TSP
    E_DEMOD_TSP_PATH_CASE_CI_IN_USE, //  msAPI_CI_CardDetect() && ByPass is Off
    #endif
    /* By-Pass Mode */ // Demod to TSP
    E_DEMOD_TSP_PATH_CASE_CI_BY_PASS, // This mode is almost = E_DEMOD_TSP_PATH_CASE_NORMAL
#endif
} EnuDemodTspPathUseCase;

void msAPI_Demod_SetupTSPath(EnuDemodTspPathUseCase eDemodTspPathUseCase);
EnuDemodTspPathUseCase msAPI_Demod_Get_CurTSPathCase(void);

BOOLEAN msAPI_Demod_Is_CurTSFormatParallel(void);
BOOLEAN msAPI_Demod_Is_CurCaseCIMode(void);


//----------------------------------------------------------------------------------------

#endif //if(ENABLE_DTV)

#endif

