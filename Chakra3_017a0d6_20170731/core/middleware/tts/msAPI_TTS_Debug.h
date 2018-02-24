#ifndef _MAPI_TTS_DEBUG_H_
#define _MAPI_TTS_DEBUG_H_

//==========================================================================
#include "Board.h"

#if( ENABLE_ATSC_TTS )

//#include "libMsTTS.h"

#ifdef MSAPI_TTS_DEBUG_C
#define INTERFACE
#else
#define INTERFACE extern
#endif


//--------------------------------------------------------------------------------------

#define TTS_MEASURE_PERFORMANCE_SYSTEM  0 // show performance information from IR key to play pcm
#define TTS_MEASURE_PERFORMANCE         0 // show performance information from IR key to play pcm

#define TTS_BUFFER_DBG              0  //show decode/audio buffer level
#define RECORD_DECODE_ISR_TIMES     0  //sub item for TTS_BUFFER_DBG
#define RECORD_DECODE_AUDIO_BUFFER  1  //sub item for TTS_BUFFER_DBG

#define ENABLE_TTS_DUMP_DATA    0

//--------------------------------------------------------------------------------------

#if TTS_MEASURE_PERFORMANCE

enum
{
    EN_TTS_PERFORMANCE_RESET,
    EN_TTS_PERFORMANCE_KEY_DETECTED,
    EN_TTS_PERFORMANCE_TEXT_IN,
    EN_TTS_PERFORMANCE_PLAY_PCM,
};

void MApp_TTS_Measure_SayBegin(void);
void MApp_TTS_Measure_SayEnd(void);
void MApp_TTS_Measure_GenNextBegin(void);
void MApp_TTS_Measure_GenNextEnd(void);

void MApp_TTS_Measure_Start(void);
void MApp_TTS_Measure_BeforeSay(void);
#endif

#if ( TTS_MEASURE_PERFORMANCE_SYSTEM)
void MApp_TTS_Cus_Measure_IRDetect(U8 u8Key);
#endif

//--------------------------------------------------------------------------------------
#if RECORD_DECODE_AUDIO_BUFFER
void maAPI_TTS_Debug_Reset_Record(void);

void maAPI_TTS_Debug_Set_RecordBufferEnable(BOOLEAN bEn);
//U8 MApp_Debug_TTS_IsBufferLevelEnable(void);
#endif

void maAPI_TTS_Debug_1ms_ISR(void);

void maAPI_TTS_Debug_PrintBuffer(void);

//--------------------------------------------------------------------------------------

#if(ENABLE_TTS_DUMP_DATA)
void msAPI_TTS_Dump_Init(void);
void msAPI_TTS_Dump_Set_Enable(BOOLEAN bEnable);
U8* msAPI_TTS_Dump_Get_DumpBuffer(void);
U32 msAPI_TTS_Dump_Get_DumpDataSize(void);
void msAPI_TTS_Dump_GenData(U8* pu8Data, U32 u32Size);
void msAPI_TTS_Dump_GenData_Finish(void);
#endif

//==========================================================================

#endif // #if( ENABLE_ATSC_TTS )

#undef INTERFACE

#endif


