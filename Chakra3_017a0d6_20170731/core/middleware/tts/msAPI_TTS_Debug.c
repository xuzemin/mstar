
#include "Board.h"

#define MSAPI_TTS_DEBUG_C

#if( ENABLE_ATSC_TTS )

#include <string.h>

#include "msAPI_TTS_Debug.h"
#include "msAPI_Timer.h"
#include "MApp_GlobalFunction.h"

#if( TTS_BUFFER_DBG )


#include "MApp_TTSControlHandler.h"

//======================================================================================

#define TTS_ANALYSIS_SIZE (400)

#define CAPTURE_MS      20 // The freq of capture data

//------------------------------------------------------------------------------

#if RECORD_DECODE_AUDIO_BUFFER
typedef struct
{
    U8 u8State      : 7;
    U8 bAudioStart  : 1;
}StuTtsDbgBufInfo;

static U16 g_TTS_Dbg_RecordCount;
static U16 g_TTS_Dbg_RecordTimer;

static U16 sau16AudioBufMs[TTS_ANALYSIS_SIZE];
static U16 sau16DecodeBufMs[TTS_ANALYSIS_SIZE];

static StuTtsDbgBufInfo g_TTS_astTtsDbgBufInfo[TTS_ANALYSIS_SIZE];
#endif

#if RECORD_DECODE_ISR_TIMES
U16 au16ISRCnt[TTS_ANALYSIS_SIZE];
U16 au16GenNextCnt[TTS_ANALYSIS_SIZE];
U32 au32GenNextData[TTS_ANALYSIS_SIZE];
U16 u16ISRCntIdx;
U16 u16GenNextCntIdx;
U16 u16GenNextDataIdx;
U32 g_TTS_Debug_u32ISRCounter;
U32 u32GenNextCounter;
U32 u32GenNextTotalData;
static U16 su16CapMs;
#endif

static U8 u8StartToLog = FALSE;

/******************************************************************************/
/*                                 Functions                                  */
/******************************************************************************/

#if RECORD_DECODE_AUDIO_BUFFER
void maAPI_TTS_Debug_Reset_Record(void)
{
    u8StartToLog = 0;

    g_TTS_Dbg_RecordCount = 0;
    g_TTS_Dbg_RecordTimer = 0;
}
#endif

void maAPI_TTS_Debug_Set_RecordBufferEnable(BOOLEAN bEn)
{
    if( bEn )
    {
        if( u8StartToLog == FALSE )
        {
            maAPI_TTS_Debug_Reset_Record();
        }
    }

    u8StartToLog = bEn;
}

/*
U8 MApp_Debug_TTS_IsBufferLevelEnable(void)
{
    return u8StartToLog;
}
*/

// This function will be called in 1ms ISR
void maAPI_TTS_Debug_RecordBuffer(void)
{
#if RECORD_DECODE_AUDIO_BUFFER
    if( g_TTS_Dbg_RecordCount < TTS_ANALYSIS_SIZE )
    {
        g_TTS_Dbg_RecordTimer += 1;
        if( g_TTS_Dbg_RecordTimer >= CAPTURE_MS )  // capture every 50ms
        {
            g_TTS_Dbg_RecordTimer = 0;

            g_TTS_astTtsDbgBufInfo[g_TTS_Dbg_RecordCount].u8State = MApp_TTS_Get_State();
            g_TTS_astTtsDbgBufInfo[g_TTS_Dbg_RecordCount].bAudioStart = MApp_TTS_Is_AudioStart();

            // Save auido buffer level
            sau16AudioBufMs[g_TTS_Dbg_RecordCount] = MApp_TTS_Get_AudioBufLevel_ms_ISR();

            // Save Dec buffer level
            sau16DecodeBufMs[g_TTS_Dbg_RecordCount] = MApp_TTS_Get_DecodeBufferLevel_ms_ISR();

            g_TTS_Dbg_RecordCount += 1;
        }
    }
#endif

#if RECORD_DECODE_ISR_TIMES
    su16CapMs++;
    if(su16CapMs >= CAPTURE_MS)  // capture every 50ms
    {
        su16CapMs = 0;
        au16ISRCnt[u16ISRCntIdx] = g_TTS_Debug_u32ISRCounter;
        au16GenNextCnt[u16GenNextCntIdx] = u32GenNextCounter;
        au32GenNextData[u16GenNextDataIdx] = u32GenNextTotalData;
        u16ISRCntIdx++;
        u16GenNextCntIdx++;
        u16GenNextDataIdx++;
        g_TTS_Debug_u32ISRCounter = 0;
        u32GenNextCounter = 0;
        u32GenNextTotalData = 0;
    }
#endif

}

void maAPI_TTS_Debug_1ms_ISR(void)
{
    if( 0 == u8StartToLog )
        return;

    maAPI_TTS_Debug_RecordBuffer();
}

void maAPI_TTS_Debug_PrintBuffer(void)
{
    U16 u16index;

#if RECORD_DECODE_AUDIO_BUFFER
    U8 u8BGColor = 0;
    U8 u8FGColor = 0;
    U8 u8TtsState;
    BOOLEAN bAudioStart;
    U16 u16DecBuf_ms;
    U16 u16AuBuf_ms;

    maAPI_TTS_Debug_Set_RecordBufferEnable(FALSE);

    printf("\n\nTTS: Decode(Audio) Buffer[%u]:\n", g_TTS_Dbg_RecordCount);

    for(u16index=0; u16index < g_TTS_Dbg_RecordCount; u16index++)
    {
        u8TtsState = g_TTS_astTtsDbgBufInfo[u16index].u8State;
        bAudioStart = g_TTS_astTtsDbgBufInfo[u16index].bAudioStart;
        u16DecBuf_ms = sau16DecodeBufMs[u16index];
        u16AuBuf_ms = sau16AudioBufMs[u16index];

        u8BGColor = 0;
        u8FGColor = 0;

        if( bAudioStart )
        {
            // Case Error: (Red)
            if( (u16AuBuf_ms == 0) /*&& (u16DecBuf_ms != 0)*/ )
            {
                u8BGColor = E_FONT_BACKGROUND_COLOR_RED;
            }
            else if( u8TtsState == STATE_TTS_DECODING )
            {
                // Just warning not error
                if( (u16DecBuf_ms + u16AuBuf_ms) < 200 )
                {
                    u8FGColor = E_FONT_COLOR_YELLOW;
                }
                /*else if( u16DecBuf_ms < 100 )
                {
                    u8FGColor = E_FONT_COLOR_YELLOW;
                }*/
            }
        }

        if( u8BGColor )
        {
            msDebug_ANSI_SetColorText(u8BGColor);
        }
        if( u8FGColor )
        {
            msDebug_ANSI_SetColorText(u8FGColor);
        }

        printf("{%u %4u %4u}", u8TtsState, u16DecBuf_ms, u16AuBuf_ms);

        // Color off
        printf("\033[0m");

        if( (u16index%8) == 7) printf("\n");
    }
    printf("\n");

    maAPI_TTS_Debug_Reset_Record();
#endif

#if RECORD_DECODE_ISR_TIMES
    printf("\n--------------------------------------------\n");
    printf("\n\nTTS: Decode Data(Decode Times)(ISR Times)\n");

    for(u16index=0; u16index<u16ISRCntIdx; u16index++)
    {
        if(au32GenNextData[u16index] == 0)
            printf("\033[1;31m%4d(%2d)(%2d)\033[0m\t",au32GenNextData[u16index], au16GenNextCnt[u16index] ,au16ISRCnt[u16index]);
        else
             printf("%4d(%2d)(%2d)\t",au32GenNextData[u16index], au16GenNextCnt[u16index] ,au16ISRCnt[u16index]);

        if(u16index%10==9) printf("\n");
    }
    printf("\n");

    u16ISRCntIdx = 0;
    u16GenNextCntIdx = 0;
    u16GenNextDataIdx = 0;
    su16CapMs = 0;
#endif
    u16index = u16index;

}

#endif

//======================================================================================

#if(ENABLE_TTS_DUMP_DATA)

#define TTS_DUMP_MEM_ADDR   0
#define TTS_DUMP_MEM_SIZE   0x200000

static BOOLEAN g_TTS_Dump_bEnable = FALSE;

static U8* g_TTS_Dump_pu8Buf;
static U32 g_TTS_Dump_u32DataCount;

void msAPI_TTS_Dump_Init(void)
{
    g_TTS_Dump_pu8Buf = (U8*)MsOS_PA2KSEG0(TTS_DUMP_MEM_ADDR);
    g_TTS_Dump_u32DataCount = 0;
}

void msAPI_TTS_Dump_Set_Enable(BOOLEAN bEnable)
{
    g_TTS_Dump_bEnable = bEnable;
}

U8* msAPI_TTS_Dump_Get_DumpBuffer(void)
{
    return g_TTS_Dump_pu8Buf;
}

U32 msAPI_TTS_Dump_Get_DumpDataSize(void)
{
    return g_TTS_Dump_u32DataCount;
}

void msAPI_TTS_Dump_GenData(U8* pu8Data, U32 u32Size)
{
    printf("msAPI_TTS_Dump_GenData(pu8Data=0x%X, u32Size=0x%X)\n", (U32)pu8Data, u32Size);

    if( FALSE == g_TTS_Dump_bEnable )
        return;

    if( u32Size == 0 )
    {
        return;
    }

    if( (u32Size + g_TTS_Dump_u32DataCount) >= TTS_DUMP_MEM_SIZE )
    {
        printf("\nWarning: TTS Dump buf full!\n");
        return;
    }

    memcpy(g_TTS_Dump_pu8Buf+g_TTS_Dump_u32DataCount, pu8Data, u32Size);

    g_TTS_Dump_u32DataCount += u32Size;
}

void msAPI_TTS_Dump_GenData_Finish(void)
{
    printf("msAPI_TTS_Dump_GenData_Finish()\n");

    if( FALSE == g_TTS_Dump_bEnable )
        return;

    printf("g_TTS_Dump_u32DataCount=0x%X\n", g_TTS_Dump_u32DataCount);

}

#endif


#if ( TTS_MEASURE_PERFORMANCE)

U8 g_TTS_Dbg_Per_KeyDetected;
U8 g_TTS_Dbg_Per_State;
U32 g_TTS_Dbg_Per_IrDetectedTime;
U32 g_TTS_Dbg_Per_TextInTime;
U32 g_TTS_Dbg_Per_PLAYTime;

U32 g_TTS_Dbg_Per_SayTimeBegin;
U32 g_TTS_Dbg_Per_SayTime;
U32 g_TTS_Dbg_Per_GenNextTimeBegin;
U32 g_TTS_Dbg_Per_GenNextTime;

void MApp_TTS_Measure_SayBegin(void)
{
    g_TTS_Dbg_Per_SayTimeBegin = MsOS_GetSystemTime();
}

void MApp_TTS_Measure_SayEnd(void)
{
    g_TTS_Dbg_Per_SayTime += msAPI_Timer_DiffTime_2(g_TTS_Dbg_Per_SayTimeBegin,MsOS_GetSystemTime());
}

void MApp_TTS_Measure_GenNextBegin(void)
{
    g_TTS_Dbg_Per_GenNextTimeBegin = MsOS_GetSystemTime();
}

void MApp_TTS_Measure_GenNextEnd(void)
{
    g_TTS_Dbg_Per_GenNextTime += msAPI_Timer_DiffTime_2(g_TTS_Dbg_Per_GenNextTimeBegin, MsOS_GetSystemTime());
}

void MApp_TTS_Measure_Start(void)
{
    // clean up
    g_TTS_Dbg_Per_SayTime=0;
    g_TTS_Dbg_Per_GenNextTime=0;

    g_TTS_Dbg_Per_State = EN_TTS_PERFORMANCE_TEXT_IN;
    g_TTS_Dbg_Per_TextInTime = MsOS_GetSystemTime();
}

void MApp_TTS_Measure_BeforeSay(void)
{
    static U32 minRatio=100;
    static U32 maxRatio=0;
    U32 u32LibUseTime;
    U32 u32TotalTime;
    U32 Ratio;

    if(g_TTS_Dbg_Per_State == EN_TTS_PERFORMANCE_TEXT_IN)
    {
        g_TTS_Dbg_Per_State = EN_TTS_PERFORMANCE_PLAY_PCM;
        g_TTS_Dbg_Per_PLAYTime = MsOS_GetSystemTime();

        u32LibUseTime = (g_TTS_Dbg_Per_SayTime + g_TTS_Dbg_Per_GenNextTime);
        u32TotalTime = (g_TTS_Dbg_Per_PLAYTime - g_TTS_Dbg_Per_TextInTime);

        Ratio = 100.0 * (u32LibUseTime)/(u32TotalTime);

        if(Ratio>maxRatio)
        {
            maxRatio=Ratio;
        }
        if(Ratio<minRatio)
        {
            minRatio=Ratio;
        }

        if(g_TTS_Dbg_Per_KeyDetected)
        {
            printf(ANSI_COLOR_YELLOW "lib=%d preload=%d ir_preload=%d " ANSI_COLOR_RESET,
                u32LibUseTime, u32TotalTime,
                g_TTS_Dbg_Per_IrDetectedTime-g_TTS_Dbg_Per_PLAYTime
                );
        }
        else
        {
            printf(ANSI_COLOR_YELLOW "lib=%d preload=%d " ANSI_COLOR_RESET,
                u32LibUseTime, u32TotalTime );
        }

        printf(ANSI_COLOR_CYAN "decode/total ratio=%d " ANSI_COLOR_RESET, Ratio);
        printf(ANSI_COLOR_GREEN "min ratio=%d max ratio=%d\n" ANSI_COLOR_RESET, minRatio, maxRatio);


#if 0
        printf(ANSI_COLOR_YELLOW "TTS_TIME <%d,%d,%d> <%d>\n" ANSI_COLOR_RESET,
            g_TTS_Dbg_Per_TextInTime-g_TTS_Dbg_Per_IrDetectedTime,
            g_TTS_Dbg_Per_PLAYTime-g_TTS_Dbg_Per_TextInTime,
            g_TTS_Dbg_Per_PLAYTime-g_TTS_Dbg_Per_IrDetectedTime,
            g_TTS_Dbg_Per_SayTime+g_TTS_Dbg_Per_GenNextTime
        );
        printf(ANSI_COLOR_GREEN "IR=%d TEXT=%d PREload=%d   say=%d, play=%d\n" ANSI_COLOR_RESET,
            g_TTS_Dbg_Per_IrDetectedTime,
            g_TTS_Dbg_Per_TextInTime,
            g_TTS_Dbg_Per_PLAYTime,
            g_TTS_Dbg_Per_SayTime,
            g_TTS_Dbg_Per_GenNextTime
        );
#endif

    // clean-up
    g_TTS_Dbg_Per_State = EN_TTS_PERFORMANCE_RESET;
#if ( TTS_MEASURE_PERFORMANCE_SYSTEM )
    g_TTS_Dbg_Per_KeyDetected = 0;
#endif

    }
}
#endif

#if ( TTS_MEASURE_PERFORMANCE_SYSTEM )
void MApp_TTS_Cus_Measure_IRDetect(U8 u8Key)
{
    g_TTS_Dbg_Per_KeyDetected = 1;
    g_TTS_Dbg_Per_IrDetectedTime = MsOS_GetSystemTime();
    printf("<IR=%x>\n", u8Key);
}
#endif
//======================================================================================

#endif // ENABLE_ATSC_TTS

