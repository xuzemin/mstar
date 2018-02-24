//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
#define MAPP_TTSCONTROLHANDLER_C
////////////////////////////////////////////////////////////////////////////////
/// @file MApp_TTSControlHandler.c
/// @author MStar Semiconductor Inc.
/// @brief Idle mode handler for APP layer
////////////////////////////////////////////////////////////////////////////////

/******************************************************************************/
/*                            Header Files                                    */
/******************************************************************************/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Board.h"

#if ENABLE_ATSC_TTS

#include "MsCommon.h"
#include "Utl.h"

#include "hal_misc.h"

#include "drvWDT.h"
#include "apiAUDIO.h"

#include "msAPI_audio.h"
#include "msAPI_Timer.h"

#include "MApp_GlobalFunction.h"

#include "MApp_TTSControlHandler.h"
#include "MApp_TTS_Cus.h"

#include "msAPI_TTS_Debug.h"
#include "msAPI_TTS_Sys.h"
#include "libMsTTS.h"

//==========================================================================
// Debug option

//#define TTS_DBG(x) // x


#define DEBUG_TTS_STATE         0
#define DEBUG_TTS_STATE_2       0

#define DEBUG_FUNC(x)           //x

#define DEBUG_TTS_DECODE(x)     //x
#define DEBUG_TTS_DECODE_2(x)   //x

#define DEBUG_SAY_STR           1

#define ENABLE_DEBUG_W_AU_BUF   0

#define ENABLE_DEBUG_TOTAL_DEC_SIZE 0

#define TTS_DEBUG_AUDIO(x)      //x

//==========================================================================

#define TTS_PATCH_AUDIO_BUF_LEVEL   1

#ifndef TTS_WAIT_AU_BUF_EMPTY_IN_ISR
    #define TTS_WAIT_AU_BUF_EMPTY_IN_ISR    0
#endif

#ifndef TTS_WAIT_AU_BUF_EMPTY_MS
    #define TTS_WAIT_AU_BUF_EMPTY_MS    10
#endif

#ifndef TTS_ADD_SILENCE_DATA_MS
    #define TTS_ADD_SILENCE_DATA_MS 0
#endif

#ifndef TTS_FORCE_DECODE_BUF_SIZE_WHEN_SPEAKING
    #define TTS_FORCE_DECODE_BUF_SIZE_WHEN_SPEAKING 300
#endif

//==========================================================================

#if( TTS_LIBRARY_SAMPLE_RATE == TTS_SAMPLE_RATE_16K)

    #define TTS_DEC_BUF_PER_MS_DATA_BYTES   (64) // 16K

#elif( TTS_LIBRARY_SAMPLE_RATE == TTS_SAMPLE_RATE_48K)

    #define TTS_DEC_BUF_PER_MS_DATA_BYTES   (64*3) // 48K

#elif( TTS_LIBRARY_SAMPLE_RATE == TTS_SAMPLE_RATE_32K)

    #define TTS_DEC_BUF_PER_MS_DATA_BYTES   (64*2) // 32K

#else
    #error "Unknown"
#endif



#if( MS_TTS_SAMPLING_RATE_SEL == MS_TTS_LIB_16_IN_16_OUT)

    #define TTS_AU_BUF_PER_MS_DATA_BYTES    (64) // 16K

#elif( MS_TTS_SAMPLING_RATE_SEL == MS_TTS_LIB_16_IN_SW_SRC_48_OUT)

    #define TTS_AU_BUF_PER_MS_DATA_BYTES    (64*3) // 48K

#elif( MS_TTS_SAMPLING_RATE_SEL == MS_TTS_LIB_48_IN_48_OUT)

    #define TTS_AU_BUF_PER_MS_DATA_BYTES    (64*3) // 48K

#elif( MS_TTS_SAMPLING_RATE_SEL == MS_TTS_LIB_32_IN_32_OUT)

    #define TTS_AU_BUF_PER_MS_DATA_BYTES    (64*2) // 32K

#else
    #error "Unknown"
#endif

//======================================================================

#if ( MS_TTS_SAMPLING_RATE_SEL == MS_TTS_LIB_16_IN_16_OUT)
#define TTS_WRITE_PCM_UNIT_BYTES            (TTS_DEC_BUF_PER_MS_DATA_BYTES * 4)
#define TTS_FIRST_WRITE_AU_BUF_TIME         2
#define TTS_WRITE_PCM_UNIT_BYTES_FristTime  (TTS_DEC_BUF_PER_MS_DATA_BYTES * 4)

#elif ( MS_TTS_SAMPLING_RATE_SEL == MS_TTS_LIB_16_IN_SW_SRC_48_OUT)
#define TTS_WRITE_PCM_UNIT_BYTES            (TTS_DEC_BUF_PER_MS_DATA_BYTES * 4)
#define TTS_FIRST_WRITE_AU_BUF_TIME         2
#define TTS_WRITE_PCM_UNIT_BYTES_FristTime  (TTS_DEC_BUF_PER_MS_DATA_BYTES * 4)

#elif ( (MS_TTS_SAMPLING_RATE_SEL == MS_TTS_LIB_48_IN_48_OUT) \
      ||(MS_TTS_SAMPLING_RATE_SEL == MS_TTS_LIB_32_IN_32_OUT) )

#define TTS_WRITE_PCM_UNIT_BYTES            (TTS_DEC_BUF_PER_MS_DATA_BYTES * 4)
#define TTS_FIRST_WRITE_AU_BUF_TIME         2
#define TTS_WRITE_PCM_UNIT_BYTES_FristTime  (TTS_DEC_BUF_PER_MS_DATA_BYTES * 4)

#else
    #error "Unknown"

#endif

#if( TTS_WRITE_PCM_UNIT_BYTES_FristTime > TTS_WRITE_PCM_UNIT_BYTES )
    #define TTS_WRITE_PCM_UNIT_BYTES_MAX    TTS_WRITE_PCM_UNIT_BYTES_FristTime
#else
    #define TTS_WRITE_PCM_UNIT_BYTES_MAX    TTS_WRITE_PCM_UNIT_BYTES
#endif

//======================================================================
// TTS Dec buffer define
#define TTS_DEC_BUF_MEM_ADR         TTS_MEM_ADR

#ifndef TTS_DEC_BUF_MEM_SIZE
  #if ( MS_TTS_SAMPLING_RATE_SEL == MS_TTS_LIB_16_IN_16_OUT)
    #define TTS_DEC_BUF_MEM_SIZE    0x10000//TTS_MEM_LEN

  #elif( MS_TTS_SAMPLING_RATE_SEL == MS_TTS_LIB_48_IN_48_OUT )
    #define TTS_DEC_BUF_MEM_SIZE    0x20000//TTS_MEM_LEN

  #elif( MS_TTS_SAMPLING_RATE_SEL == MS_TTS_LIB_32_IN_32_OUT )
    #define TTS_DEC_BUF_MEM_SIZE    0x20000//TTS_MEM_LEN

  #else
    #define TTS_DEC_BUF_MEM_SIZE    0x20000//TTS_MEM_LEN

  #endif
#endif

// Check memory size
#if( TTS_DEC_BUF_MEM_SIZE > TTS_MEM_LEN )
    #error "TTS memory size error"
#endif

// This option depend on TTS lib
#define TTS_GEN_DATA_MAX_SIZE_EACH_TIME (TTS_LIB_GEN_DATA_MAX_SIZE*2+1024)

// When DEC buf level is > TTS_DEC_BUF_LEVEL_FULL_BYTES, Pause decode
#define TTS_DEC_BUF_LEVEL_FULL_BYTES    (TTS_DEC_BUF_MEM_SIZE - TTS_GEN_DATA_MAX_SIZE_EACH_TIME - 1024)
#define TTS_DEC_BUF_LEVEL_FULL_MS       (TTS_DEC_BUF_LEVEL_FULL_BYTES / TTS_DEC_BUF_PER_MS_DATA_BYTES)

// When DEC buf level is > TTS_DEC_BUF_LEVEL_PRELOAD_BYTES, Start playing audio
#if( TTS_DEC_BUF_MEM_SIZE >= 0x20000 ) // 128k for 48KHz or 16KHz
    #define TTS_DEC_BUF_LEVEL_PRELOAD_BYTES (TTS_DEC_BUF_PER_MS_DATA_BYTES * 500)
#else // For 16KHz
    #define TTS_DEC_BUF_LEVEL_PRELOAD_BYTES (TTS_DEC_BUF_PER_MS_DATA_BYTES * 400)
#endif

#if( TTS_DEC_BUF_LEVEL_PRELOAD_BYTES >= TTS_DEC_BUF_LEVEL_FULL_BYTES )
    #error "TTS_DEC_BUF_LEVEL_PRELOAD_BYTES >= TTS_DEC_BUF_LEVEL_FULL_BYTES"
#endif

//======================================================================
// TTS Audio buffer define
#ifndef TTS_AUDIO_DSP_BUFFER_SIZE
#define TTS_AUDIO_DSP_BUFFER_SIZE   (0x8000) // Whisky is 32K
#endif

//======================================================================

#define TTS_GEN_NEXT_MS             (50) // 50ms

//==========================================================================

// Flow control
static EN_TTS_STATE enTTSState = STATE_TTS_INIT;
static BOOLEAN b_TTS_bCheckStartSpeaking;
static BOOLEAN g_TTS_bStopISR;
static BOOLEAN g_TTS_bInISR;
static BOOLEAN g_TTS_bCheckUserBreak;
static BOOLEAN g_TTS_bAutoPlayNextStr = TRUE;

// Status
static BOOLEAN g_TTS_bInitDone = FALSE;
static U32 g_TTS_u32SysTime;
static U8 g_TTS_u8StrCnt = 0;
static BOOLEAN g_TTS_bIsInSpeaking = FALSE;


// Dec buffer ...
static U8* pu8waveout;
static U32 u32TTSReadPoniter;
static U32 u32TTSWritePoniter;
static U32 gu32TTSPlayPreloadBufferSize = TTS_DEC_BUF_LEVEL_PRELOAD_BYTES;


// For decoding
static U32 g_TTS_u32GenNextLastTime = 0;
static U32 g_TTS_u32GenNextLastDecBufLevel;
#if(TTS_ADD_SILENCE_DATA_MS)
static U32 g_TTS_u32AddSlienceDataSize;
#endif
static EunTTSDecodeMode g_TTS_eTTSDecodeMode = TTS_DECODE_MODE_NORMAL;
static U32 g_TTS_u32ForceDecBufSize_ms = 0;
static U32 g_TTS_32LastHasDataTime = 0;



// Audio buffer control
static BOOLEAN g_TTS_bEnableAudioBufTask = FALSE;
static BOOLEAN g_TTS_bIsAudioDriverReady = FALSE;
static U32 g_TTS_u32AuBufLevel_Last;
static U16 g_TTS_u16WriteDmaFailCount = 0;
static U16 g_TTS_u16WriteDmaEmptyCount = 0;
#if(TTS_WAIT_AU_BUF_EMPTY_IN_ISR)
static BOOL g_TTS_bEnableCheckAuBufEmptyInISR = FALSE;
#endif


// SW SRC
#if (TTS_SW_SRC_ENABLE)
static void* pAudioSrcHandle = NULL;
#define TTS_SAMPLE_RATE_16KHZ_INDEX 4 //
static void *instanceSram = NULL;
#include "mst_rsrc.h"
static U16 g_TTS_au16SrcOutBuf[(TTS_WRITE_PCM_UNIT_BYTES_MAX/2)*3];
#endif

//==========================================================================
// Debug ...

#if ENABLE_DEBUG_TOTAL_DEC_SIZE
static U32 g_TTS_u32TotalDecSize = 0;
#endif

//=========================================================================================
// Internal function

void MApp_TTSControlHandler_Reset(void);

//BOOLEAN MApp_TTS_Get_StopISR(void);
#define MApp_TTS_Get_StopISR()  (g_TTS_bStopISR)
static void MApp_TTS_Set_StopISR(BOOLEAN bStopISR);

U32 MApp_TTS_Get_AudioBufferLevel_Byte(void);
BOOLEAN MApp_TTS_Is_AudioBufEmpty(void);
//U32 MApp_TTS_Get_AudioBufLevel_Byte_ISR(void);
#define MApp_TTS_Get_AudioBufLevel_Byte_ISR()   MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_DMAReader_BufferLevel)


BOOLEAN MApp_TTS_DecodeInit(U8* pu8TextBuf_UTF8, U16 u16TextBufSize);
void MApp_TTS_MoveDataToAudioBuf(void);

void MApp_TTS_EngineStop(void);
BOOLEAN MApp_TTS_CheckIfUserBreak(void);
//=========================================================================================
// MApp_TTS_Cus
void MApp_TTS_CB_Init(void);
void MApp_TTS_CB_BeforeDecode(void);
void MApp_TTS_CB_BeforeSay(void);
void MApp_TTS_CB_SayFinish(void);
BOOLEAN MApp_TTS_CB_CheckIfUserBreak(void);
void MApp_TTS_CB_Set_MuteBGM(BOOLEAN bMuteBGM);

long MApp_TTS_UNI_2_UTF8(U8 *pDest, const U16*pSrc, long destLen, long sourceLen);

//=========================================================================================

#if( ENABLE_DEBUG_W_AU_BUF )
static U32 g_TTS_u32WriteDmaTime = 0; // For MApi_AUDIO_DmaReader_WritePCM()
static U32 g_TTS_u32WriteDmaTime_2 = 0; // For mst_rsrc_process()
#endif
void MApp_TTS_WriteAudioDmaBuf( void* pBuffer, MS_U32 u32Size)
{
    // Check if audio buffer empty
    if( g_TTS_u32AuBufLevel_Last != 0 )
    {
        if( MApp_TTS_Get_AudioBufLevel_Byte_ISR() <= 8 )
        {
            g_TTS_u16WriteDmaEmptyCount += 1;
        }
    }


#if (TTS_SW_SRC_ENABLE)
    U32 u32OutBlockSize;


  #if( ENABLE_DEBUG_W_AU_BUF )
    g_TTS_u32WriteDmaTime_2 = MDrv_PIU_TIMER_CAP_Get_Us();//MDrv_TIMER_GetUs(E_TIMER_1);
  #endif
    u32OutBlockSize = mst_rsrc_process(pAudioSrcHandle, (S16*)pBuffer, (S16*)g_TTS_au16SrcOutBuf, (u32Size/2));
  #if( ENABLE_DEBUG_W_AU_BUF )
    g_TTS_u32WriteDmaTime_2 = MDrv_PIU_TIMER_CAP_Get_Us() - g_TTS_u32WriteDmaTime_2;
  #endif

    MsOS_Dcache_Flush( (MS_U32)g_TTS_au16SrcOutBuf, (u32OutBlockSize)*2 );
    MsOS_FlushMemory();

  #if( ENABLE_DEBUG_W_AU_BUF )
    g_TTS_u32WriteDmaTime = MDrv_PIU_TIMER_CAP_Get_Us();
  #endif

    if( FALSE == MApi_AUDIO_DmaReader_WritePCM((void *)MsOS_VA2PA((U32)g_TTS_au16SrcOutBuf), (u32OutBlockSize)*2) )
    {
        g_TTS_u16WriteDmaFailCount += 1;
    }

  #if( ENABLE_DEBUG_W_AU_BUF )
    g_TTS_u32WriteDmaTime = MDrv_PIU_TIMER_CAP_Get_Us() - g_TTS_u32WriteDmaTime;
  #endif

#else

    MsOS_Dcache_Flush((MS_U32)pBuffer, u32Size);
    MsOS_FlushMemory();

  #if( ENABLE_DEBUG_W_AU_BUF )
    g_TTS_u32WriteDmaTime = MDrv_PIU_TIMER_CAP_Get_Us();
  #endif

    if( FALSE == MApi_AUDIO_DmaReader_WritePCM( (void *)MsOS_VA2PA((U32)pBuffer), u32Size) )
    {
        g_TTS_u16WriteDmaFailCount += 1;
    }

  #if( ENABLE_DEBUG_W_AU_BUF )
    g_TTS_u32WriteDmaTime = MDrv_PIU_TIMER_CAP_Get_Us() - g_TTS_u32WriteDmaTime;
  #endif

#endif

    g_TTS_u32AuBufLevel_Last = MApp_TTS_Get_AudioBufLevel_Byte_ISR();
}

#if( DEBUG_TTS_STATE )
char* MApp_TTS_Get_StateName(EN_TTS_STATE eTtsState)
{
    char* pcTtsStateName = "Unknown tts state";

    switch(eTtsState)
    {
        case STATE_TTS_INIT:
            pcTtsStateName = "INIT";
            break;

        case STATE_TTS_DECODE_INIT:
            pcTtsStateName = "DECODE_INIT";
            break;

        case STATE_TTS_DECODING:
            pcTtsStateName = "DECODING";
            break;

        case STATE_TTS_WAIT_DEC_BUF_EMPTY:
            pcTtsStateName = "WAIT_DEC_BUF_EMPTY";
            break;

        case STATE_TTS_WAIT_AUDIO_BUF_EMPTY:
            pcTtsStateName = "WAIT_AUDIO_BUF_EMPTY";
            break;

        default:
            break;
    }

    return pcTtsStateName;
}
#endif

EN_TTS_STATE MApp_TTS_Get_State(void)
{
    return enTTSState;
}

void MApp_TTS_Set_State(EN_TTS_STATE eTtsState)
{
    //printf("MApp_TTS_Set_State(%u)\n", eTtsState);

#if( DEBUG_TTS_STATE )
    //printf("TTS state: %u -> %u\n", enTTSState, eTtsState);
    printf("TTS state: %u(%s) -> %u(%s) at %u\n",
        enTTSState, MApp_TTS_Get_StateName(enTTSState),
        eTtsState, MApp_TTS_Get_StateName(eTtsState), g_TTS_u32SysTime);
#endif

    enTTSState = eTtsState;
}

BOOLEAN MApp_TTS_Is_AudioStart(void)
{
    return g_TTS_bEnableAudioBufTask;
}

BOOLEAN MApp_TTS_Is_InSpeaking(void)
{
    return g_TTS_bIsInSpeaking;
}

void MApp_TTS_Init_DecBuf(void)
{
    DEBUG_FUNC(printf("%s()\n", __FUNCTION__););

    //printf("TTS_DEC_BUF_MEM_ADR=0x%X\n", TTS_DEC_BUF_MEM_ADR);

    // Convert to cached buffer pointer
    pu8waveout = (U8*)MsOS_PA2KSEG0(TTS_DEC_BUF_MEM_ADR);
    //printf("pu8waveout=0x%X\n", pu8waveout);

    memset( pu8waveout, 0x0, TTS_DEC_BUF_MEM_SIZE);

    u32TTSReadPoniter = 0;
    u32TTSWritePoniter = 0;

#if ENABLE_DEBUG_TOTAL_DEC_SIZE
    g_TTS_u32TotalDecSize = 0;
#endif

    g_TTS_u32GenNextLastDecBufLevel = 0;

}

void MApp_TTS_Set_MuteTts(BOOLEAN bMuteTts)
{
    TTS_DEBUG_AUDIO( printf("MApp_TTS_Set_MuteTts(bMuteTts=%u) at %u\n", bMuteTts, g_TTS_u32SysTime); );

    //static U8 _s_TTS_bMuteTTS_Last = 0xff;

    //if( _s_TTS_bMuteTTS_Last == bMuteTts )
      //  return;

    TTS_DEBUG_AUDIO( printf(" => MuteTts=%u\n", bMuteTts); );

    if( bMuteTts )
    {
        MApi_AUDIO_SetMixModeMute(E_AUDIO_INFO_GAME_IN, PCM_VOL, TRUE);  // mute tts
        g_TTS_bIsInSpeaking = FALSE;
    }
    else
    {
        MApi_AUDIO_SetMixModeMute(E_AUDIO_INFO_GAME_IN, PCM_VOL, FALSE);  // Un-mute tts
        g_TTS_bIsInSpeaking = TRUE;
    }

    //_s_TTS_bMuteTTS_Last = bMuteTts;
}

void MApp_TTS_SetupAudioDriver(BOOL bTTSPlay)
{
    TTS_DEBUG_AUDIO( printf("MApp_TTS_SetupAudioDriver(bTTSPlay=%u)\n", bTTSPlay); );

    if( bTTSPlay )
    {
        g_TTS_bIsAudioDriverReady = TRUE;

        // Move this function to init
        //MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_GAME_IN);

        MApp_TTS_Set_MuteTts(TRUE); // Mute TTS sound

        // This function must be called every time
        MApi_AUDIO_DmaReader_Init(TTS_AUDIO_SAMPLE_RATE);

        MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_DMAReader_Command, 1, 0);
    }
    else
    {
        g_TTS_bIsAudioDriverReady = FALSE;

        MApp_TTS_Set_MuteTts(TRUE); // Mute TTS sound

        MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_DMAReader_Command, 0, 0);
    }
}

BOOLEAN MApp_TTS_Is_InWorking(void)
{
    return ( MApp_TTS_Get_Enable() && (enTTSState != STATE_TTS_INIT ) );
}

BOOLEAN MApp_TTS_WaitAudioBufEmpty(void)
{
    U32 u32WaitStartTime = MsOS_GetSystemTime();


    DEBUG_FUNC(printf("%s()\n", __FUNCTION__););

    // Wait play done
    while(1)
    {
        if( MApp_TTS_Is_AudioBufEmpty() )
        {
            return TRUE;
        }

        // Check if user break
        if( MApp_TTS_CheckIfUserBreak() )
        {
            MApp_TTS_Say_Stop();
            return TRUE;
        }

        if( msAPI_Timer_DiffTime_2(u32WaitStartTime, MsOS_GetSystemTime()) >= 4000 )
        {
            break;
        }

    #if 0 // Show audio buffer level
        {
            int iPrintAudioBuf = 0;
            iPrintAudioBuf += 1;
            if( iPrintAudioBuf >= 2 )
            {
                iPrintAudioBuf = 0;
                printf("<%u,%u>", MApp_TTS_Get_AudioBufferLevel_Byte(), MApp_TTS_Get_AudioBufferLevel_ms());
            }
        }
        msAPI_Timer_Delayms(5);
    #else
        msAPI_Timer_Delayms(1);
    #endif

    }

    printf("\nError: [TTS] Wait audio buf empty timeout!\n");
    return FALSE;
}

#if (TTS_SW_SRC_ENABLE)
BOOLEAN MApp_TTS_SWSRC_Init(void)
{
    U32 u32instanceRequireBytes;
    int OutBlockSize;
    int delay;


    u32instanceRequireBytes = mst_rsrc_get_sram_size((int)TTS_SAMPLE_RATE_16KHZ_INDEX, TTS_WRITE_PCM_UNIT_BYTES_MAX, &OutBlockSize);
    //printf("inSize=%u, OutBlockSize=%u, u32instanceRequireBytes=%u\n", TTS_WRITE_PCM_UNIT_BYTES_MAX, OutBlockSize, u32instanceRequireBytes);

    if( instanceSram == NULL )
    {
        instanceSram = malloc(u32instanceRequireBytes);
        if( NULL == instanceSram )
        {
            printf("\nError: [TTS] malloc failed!\n");
            return FALSE;
        }

        pAudioSrcHandle = mst_rsrc_init(instanceSram, SR_16000, &delay);
        //printf("delay=%u\n", delay);
    }

    return TRUE;
}
#endif

BOOLEAN MApp_TTSControlHandler_Init(EunMsTtsLangId eMsTtsLangId, EunMsTtsLangId eMsTtsLangId_2nd)
{
    DEBUG_FUNC( printf("MApp_TTSControlHandler_Init(eMsTtsLangId=%u, lang2=%u\n",eMsTtsLangId, eMsTtsLangId_2nd); );

    MApp_TTS_Set_State(STATE_TTS_INIT);

    MApp_TTS_Set_StopISR(FALSE);

    gu32TTSPlayPreloadBufferSize = TTS_DEC_BUF_LEVEL_PRELOAD_BYTES;

    g_TTS_bCheckUserBreak = TRUE;

    g_TTS_bIsInSpeaking = FALSE;

#if (TTS_SW_SRC_ENABLE)
    if( FALSE == MApp_TTS_SWSRC_Init() )
    {
        printf("\nError: [TTS] MApp_TTS_SWSRC_Init() failed!\n");
        return FALSE;
    }
#endif


#if ENABLE_TTS_2ND_LANG

#else
    eMsTtsLangId_2nd = MB_TTS_LANG_NONE;
#endif

    if( FALSE == msAPI_TTS_Sys_Init(eMsTtsLangId, eMsTtsLangId_2nd ) )
    {
        printf("\nError: MApp_TTSControlHandler_Init() failed!\n");
        return FALSE;
    }


    MApp_TTSControlHandler_Reset();

    g_TTS_bIsAudioDriverReady = FALSE;
    MApi_AUDIO_SetSourceInfo(E_AUDIO_INFO_GAME_IN);
    //MApi_AUDIO_DmaReader_Init(TTS_AUDIO_SAMPLE_RATE);

    // For mapp_tts_cus
    MApp_TTS_CB_Init();

    g_TTS_bInitDone = TRUE;

    return TRUE;
}

void MApp_TTSControlSetLanguage(EunMsTtsLangId eMsTtsLangId, EunMsTtsLangId eMsTtsLangId_2nd)
{
    DEBUG_FUNC( printf("MApp_TTSControlSetLanguage(eMsTtsLangId=%u, lang2=%u\n",eMsTtsLangId, eMsTtsLangId_2nd); );

    if( g_TTS_bInitDone != TRUE )
        return;

#if ENABLE_TTS_2ND_LANG
#else
    eMsTtsLangId_2nd = MB_TTS_LANG_NONE;
#endif

    BOOLEAN bRet = msAPI_TTS_Sys_Set_Langage(eMsTtsLangId, eMsTtsLangId_2nd);
    if( TRUE != bRet )
    {
        MApp_Fatal_Error("[TTS] Check hash key or library", __FUNCTION__);
    }
    else
    {
        printf("Set language success.\n");
    }
}

void MApp_TTSControlHandler_Reset(void)
{
    DEBUG_FUNC(printf("%s()\n", __FUNCTION__););

    BOOLEAN bStopISR_Backup = MApp_TTS_Get_StopISR();
    MApp_TTS_Set_StopISR(TRUE); // Stop ISR

    g_TTS_bEnableAudioBufTask = FALSE;

    b_TTS_bCheckStartSpeaking = TRUE;

    MApp_TTS_Init_DecBuf();

    MApp_TTS_Set_StopISR(bStopISR_Backup); // Recovery ISR
}

BOOLEAN MApp_TTS_CheckIfUserBreak(void)
{
    if( g_TTS_bCheckUserBreak )
    {
        if( MApp_TTS_CB_CheckIfUserBreak() )
        {
            return TRUE;
        }
    }

    return FALSE;
}

#if 0
void MApp_TTSControlSetTextAndSay(U16* u16Str, U16 len)
{
    DEBUG_FUNC(printf("%s()\n", __FUNCTION__););

    UNUSED(len);

    if( MApp_TTS_Get_Enable() == FALSE )
    {
        return;
    }

    MApp_TTS_Set_StopISR(TRUE);

    MApp_TTSControlHandler_Reset();

#define TTS_UTF8_STR_BUF_SIZE   256
    U8 au8TextBuf_UTF8[TTS_UTF8_STR_BUF_SIZE];
    U16 u16TextBufSize;

    memset(au8TextBuf_UTF8, 0x0, sizeof(au8TextBuf_UTF8));
    u16TextBufSize = MApp_TTS_UNI_2_UTF8(au8TextBuf_UTF8, u16Str, TTS_UTF8_STR_BUF_SIZE, len);
    //TTS_DBG(printf("\033[42;30m TTS text&say=%s len=%d u8TextWriteNumber=%d\033[0m\n", textBuffer, len, u8TextWriteNumber));

    if( FALSE == MApp_TTS_DecodeInit( au8TextBuf_UTF8, u16TextBufSize ) )
    { // NG
        return ;
    }

    //g_TTS_bCheckUserBreak = FALSE;

    // OK
    MApp_TTS_Set_State(STATE_TTS_DECODING);
    g_TTS_u32GenNextLastTime = MsOS_GetSystemTime();

    // Gen data
    while( enTTSState != STATE_TTS_INIT )
    {
        MApp_TTSControlHandler_Main();

        if( enTTSState == STATE_TTS_WAIT_DEC_BUF_EMPTY )
        {
            break;
        }
    }

    g_TTS_bAutoPlayNextStr = FALSE;

    BOOL bWaitSayFinish = 1;//FALSE;

    // Wait move data and say
    if( bWaitSayFinish )
    {
        while( enTTSState != STATE_TTS_INIT )
        {
            MApp_TTSControlHandler_Main();
        }

    /*
        MApp_TTS_EngineStop();

        MApp_TTS_Set_State(STATE_TTS_INIT);

    #if TTS_BUFFER_DBG
        maAPI_TTS_Debug_Set_RecordBufferEnable(DISABLE);
        // Print info after playing one string
        maAPI_TTS_Debug_PrintBuffer();
    #endif
    */
    }
}
#endif

//---------------------------------------------------------------------------------------------
void MApp_TTS_Set_PreloadBuffer_ms(U32 u32DataMs)
{
    if( u32DataMs > TTS_DEC_BUF_LEVEL_FULL_MS )
        u32DataMs = TTS_DEC_BUF_LEVEL_FULL_MS;

    gu32TTSPlayPreloadBufferSize = (u32DataMs * TTS_DEC_BUF_PER_MS_DATA_BYTES);
}

void MApp_TTS_Set_EnableUserBreak(BOOLEAN bEnUserBreak)
{
    g_TTS_bCheckUserBreak = bEnUserBreak;
}

BOOLEAN MApp_TTS_Get_EnableUserBreak(void)
{
    return g_TTS_bCheckUserBreak;;
}

//---------------------------------------------------------------------------------------------

/*
BOOLEAN MApp_TTS_Get_StopISR(void)
{
    return g_TTS_bStopISR;
}
*/

static void MApp_TTS_Set_StopISR(BOOLEAN bStopISR)
{
    g_TTS_bStopISR = bStopISR;
}

void msAPI_TTS_PrintStr_UTF8(U8* pu8Str, U16 u16StrSizeMax )
{
    U16 i;
    U8 u8ByteCount;
    U8 u8CharTmp;
    U16 u16Char;


    printf("\"");

    for(i = 0; i < u16StrSizeMax; )
    {
        u8CharTmp = pu8Str[i];

        if( (u8CharTmp&0xF0) == 0xE0 ) //three byte  1110-xxxx 10xx-xxxx 10xx-xxxx
        {
            u8ByteCount = 3;
            u16Char = '?';
        }
        else if( (u8CharTmp&0xE0) == 0xC0 ) //two byte  110x-xxxx 10xx-xxxx
        {
            u8ByteCount = 2;
            u16Char = '?';
        }
        else
        {
            u8ByteCount = 1;
            u16Char = u8CharTmp&0x7F;
        }

        i += u8ByteCount;

        if( u16Char == 0 )
            break;

        if( (u16Char < 0x20) || (u16Char > 0x7F))
        {
            printf("(0x%X)", u16Char);
        }
        else
        {
            printf("%c", u16Char);
        }
    }

    printf("\"");
}

BOOLEAN MApp_TTSControlSay(U8* text, U16 text_len, U8* waveout, U32 waveout_len)
{
    BOOLEAN bRet = FALSE;

#if(DEBUG_SAY_STR)
    printf(" [TTS] Say %u: ", text_len);
    msDebug_ANSI_SetColorText_2(E_FONT_COLOR_BLACK, E_FONT_BACKGROUND_COLOR_PURPLE);
    msAPI_TTS_PrintStr_UTF8(text, text_len);
    printf("%s\n", ANSI_COLOR_OFF_STR);
#endif

#if TTS_IS_ON_HK

  #if(TTS_MEASURE_PERFORMANCE)
    MApp_TTS_Measure_SayBegin();
  #endif

    int result = msAPI_TTS_Say((unsigned char*) text, (unsigned int)text_len, (unsigned char*)waveout, (unsigned int)waveout_len);

  #if(TTS_MEASURE_PERFORMANCE)
    MApp_TTS_Measure_SayEnd();
  #endif

    if (result == TTS_RET_OK)
    {
        bRet = TRUE;
    }
    else
    {
        bRet = FALSE;
        printf("\nError: msAPI_TTS_Say() failed!\n");

        // Move out of this function
        //enTTSState = STATE_TTS_FINISH;
        //MApp_TTS_Set_State(STATE_TTS_STOP_PLAY_RIGHT_NOW);
    }

#else // run on SecureR2
    TTS_DBG(printf("TTS MApp_TTSControlSay %s  u8AudioReadNumber=%d u8TextWriteNumber=%d waveout=0x%lx\n", text, u8AudioReadNumber, u8TextWriteNumber,(U32)waveout));

    TTS_MBXWriteByte(TTS_MBX_CMDID_IDX, MB_TTS_ENGINE_SAY_CMD);
    TTS_MBXWriteByte(TTS_MBX_DATA1_IDX, (U8)(((U32)text & 0xFF000000) >> 24));
    TTS_MBXWriteByte(TTS_MBX_DATA2_IDX, (U8)(((U32)text & 0x00FF0000) >> 16));
    TTS_MBXWriteByte(TTS_MBX_DATA3_IDX, (U8)(((U32)text & 0x0000FF00) >> 8));
    TTS_MBXWriteByte(TTS_MBX_DATA4_IDX, (U8)((U32)text & 0x000000FF));

    TTS_MBXWriteByte(TTS_MBX_DATA5_IDX, (U8)(((U32)waveout & 0xFF000000) >> 24));
    TTS_MBXWriteByte(TTS_MBX_DATA6_IDX, (U8)(((U32)waveout & 0x00FF0000) >> 16));
    TTS_MBXWriteByte(TTS_MBX_DATA7_IDX, (U8)(((U32)waveout & 0x0000FF00) >> 8));
    TTS_MBXWriteByte(TTS_MBX_DATA8_IDX, (U8)((U32)waveout & 0x000000FF));

    bRet = TRUE;
#endif

    return bRet;
}

BOOLEAN MApp_TTS_DecodeInit(U8* pu8TextBuf_UTF8, U16 u16TextBufSize)
{
    DEBUG_FUNC(printf("%s()\n", __FUNCTION__););


    b_TTS_bCheckStartSpeaking = TRUE;
    g_TTS_bEnableAudioBufTask = FALSE;
    g_TTS_u16WriteDmaFailCount = 0;
    g_TTS_u16WriteDmaEmptyCount = 0;
    g_TTS_u32AuBufLevel_Last = 0;
#if(TTS_WAIT_AU_BUF_EMPTY_IN_ISR)
    g_TTS_bEnableCheckAuBufEmptyInISR = FALSE;
#endif

    //g_TTS_bCheckUserBreak = TRUE;
    g_TTS_32LastHasDataTime = 0;

#if(TTS_ADD_SILENCE_DATA_MS)
    g_TTS_u32AddSlienceDataSize = (TTS_ADD_SILENCE_DATA_MS*TTS_DEC_BUF_PER_MS_DATA_BYTES);
    printf("g_TTS_u32AddSlienceDataSize=0x%X\n", g_TTS_u32AddSlienceDataSize);
#endif


    if( pu8TextBuf_UTF8 == NULL )
    {
        printf("\nError: pu8TextBuf_UTF8=NULL!");
        return FALSE;
    }

    MApp_TTS_Init_DecBuf();

    // Notify customer to prepare string!
    MApp_TTS_CB_BeforeDecode();

    BOOLEAN bResult = MApp_TTSControlSay( pu8TextBuf_UTF8, u16TextBufSize, (U8*)pu8waveout, TTS_DEC_BUF_MEM_SIZE);
    if( bResult == FALSE )
    {
        printf("\nError: MApp_TTSControlSay() failed!\n");
        return FALSE;
    }

    //MApp_TTS_SetupAudioDriver(ENABLE);

#if TTS_BUFFER_DBG
    maAPI_TTS_Debug_Reset_Record();
    maAPI_TTS_Debug_Set_RecordBufferEnable(TRUE);
#endif

#if(ENABLE_TTS_DUMP_DATA)
    msAPI_TTS_Dump_Init();
#endif

    return TRUE;
}

void MApp_TTS_FirstWriteAudioData(void)
{
    U8 i;

    //printf("FirstWriteAudioData() at %u\n", g_TTS_u32SysTime );

#if(ENABLE_DEBUG_W_AU_BUF )
    U32 au32WriteAuBufTime[TTS_FIRST_WRITE_AU_BUF_TIME][3];

    MDrv_PIU_TIMER_CAP_Init();

    printf("Frist time: au=%u\n", MApp_TTS_Get_AudioBufferLevel_Byte());
#endif

    for( i = 0; i < TTS_FIRST_WRITE_AU_BUF_TIME; i += 1 )
    {
    #if(ENABLE_DEBUG_W_AU_BUF )
        au32WriteAuBufTime[i][0] = MDrv_PIU_TIMER_CAP_Get_Us();
    #endif

        MApp_TTS_MoveDataToAudioBuf();

    #if(ENABLE_DEBUG_W_AU_BUF )
        au32WriteAuBufTime[i][0] = MDrv_PIU_TIMER_CAP_Get_Us() - au32WriteAuBufTime[i][0];
        au32WriteAuBufTime[i][1] = g_TTS_u32WriteDmaTime;
        au32WriteAuBufTime[i][2] = g_TTS_u32WriteDmaTime_2;
    #endif
    }

#if(ENABLE_DEBUG_W_AU_BUF )
    printf(" end au=%u\n", MApp_TTS_Get_AudioBufferLevel_Byte());

    for( i = 0; i < TTS_FIRST_WRITE_AU_BUF_TIME; i += 1 )
    {
        printf("%u t=%u, %u, %u\n", i, au32WriteAuBufTime[i][0],
            au32WriteAuBufTime[i][1], au32WriteAuBufTime[i][2]);
    }
#endif

    //printf("Dec=%u, Au=%u\n", MApp_TTS_Get_DecodeBufferLevel_Byte(), MApp_TTS_Get_AudioBufferLevel_Byte());
}

static void MApp_TTS_CheckBuf_BeforeGenData(void)
{
    if( g_TTS_u32GenNextLastDecBufLevel != 0 )
    {
        U32 u32CurDecBufLevel = MApp_TTS_Get_DecodeBufferLevel_Byte();
        U32 u32CurAuBufLevel = MApp_TTS_Get_AudioBufferLevel_Byte();
        U32 u32CurAuBufLevel_ms = u32CurAuBufLevel/TTS_AU_BUF_PER_MS_DATA_BYTES;

        if( u32CurDecBufLevel == 0 )
        {
            if( MApp_TTS_Is_AudioBufEmpty() )
            {
                msDebug_ANSI_SetColorText_2(E_FONT_COLOR_BLACK, E_FONT_BACKGROUND_COLOR_RED);
                printf("\nTTS Error: Dec Buf empty!(LastDec=%u,%ums), AuBuf=0 at %u %s\n",
                    g_TTS_u32GenNextLastDecBufLevel, g_TTS_u32GenNextLastDecBufLevel/TTS_DEC_BUF_PER_MS_DATA_BYTES,
                    g_TTS_u32SysTime,
                    ANSI_COLOR_OFF_STR );
            }
            else if( u32CurAuBufLevel_ms < 200 )
            {
                msDebug_ANSI_SetColorText_2(E_FONT_COLOR_BLACK, E_FONT_BACKGROUND_COLOR_YELLOW);
                printf("\nTTS Warning: Dec Buf empty!(LastDec=%u,%ums), AuBuf=%u,%ums at %u %s\n",
                    g_TTS_u32GenNextLastDecBufLevel, g_TTS_u32GenNextLastDecBufLevel/TTS_DEC_BUF_PER_MS_DATA_BYTES,
                    u32CurAuBufLevel, u32CurAuBufLevel_ms,
                    g_TTS_u32SysTime,
                    ANSI_COLOR_OFF_STR);
            }
        }
    }
}

static void MApp_TTS_UpdateWritePointer(U32 u32DecBufSpace, U32 u32NewWritePointer)
{
    // If has new data,  adjust write pointer
    if( u32NewWritePointer == u32TTSWritePoniter )
        return;


    U32 u32ThisTimeGenSize = 0;

    if( u32NewWritePointer > u32TTSWritePoniter )
    {
        u32ThisTimeGenSize = (u32NewWritePointer - u32TTSWritePoniter);
    #if(ENABLE_TTS_DUMP_DATA)
        msAPI_TTS_Dump_GenData(pu8waveout+u32TTSWritePoniter, u32ThisTimeGenSize);
    #endif
    }
    else
    {
        u32ThisTimeGenSize = (TTS_DEC_BUF_MEM_SIZE - u32TTSWritePoniter + u32NewWritePointer);
    #if(ENABLE_TTS_DUMP_DATA)
        msAPI_TTS_Dump_GenData(pu8waveout+u32TTSWritePoniter, TTS_DEC_BUF_MEM_SIZE - u32TTSWritePoniter);
        msAPI_TTS_Dump_GenData(pu8waveout, u32NewWritePointer);
    #endif
    }

    // Update write pointer
    MApp_TTS_Set_StopISR(TRUE);
    u32TTSWritePoniter = u32NewWritePointer;
    MApp_TTS_Set_StopISR(FALSE);

    //DEBUG_TTS_DECODE( printf(" u32ThisTimeGenSize=%u,%ums\n", u32ThisTimeGenSize, u32ThisTimeGenSize/TTS_DEC_BUF_PER_MS_DATA_BYTES); );
    DEBUG_TTS_DECODE( printf(" Gen %u/%u\n", u32ThisTimeGenSize/TTS_DEC_BUF_PER_MS_DATA_BYTES,  MApp_TTS_Get_DecodeBufferLevel_ms()); );

    // Check this time gen size...
    if( u32ThisTimeGenSize >= u32DecBufSpace )
    {
        msDebug_ANSI_SetColorText_2(E_FONT_COLOR_BLACK, E_FONT_BACKGROUND_COLOR_RED);
        printf("\n[TTS] Error: TTS Gen Data size=%u >= space=%u%s\n",
            u32ThisTimeGenSize, u32DecBufSpace, ANSI_COLOR_OFF_STR );
    }
    if( u32ThisTimeGenSize > TTS_GEN_DATA_MAX_SIZE_EACH_TIME )
    {
        msDebug_ANSI_SetColorText_2(E_FONT_COLOR_BLACK, E_FONT_BACKGROUND_COLOR_RED);
        printf("\n[TTS] Error: TTS Gen Data size=%u > Spec=%u%s\n",
            u32ThisTimeGenSize, TTS_GEN_DATA_MAX_SIZE_EACH_TIME, ANSI_COLOR_OFF_STR );
    }

#if ENABLE_DEBUG_TOTAL_DEC_SIZE
    g_TTS_u32TotalDecSize += u32ThisTimeGenSize;
    //if( iGenNextResult == TTS_RET_DONE )
    {
        //printf("g_TTS_u32TotalDecSize=%u\n", g_TTS_u32TotalDecSize);
    }
    printf("{TotalDec=%u/%u}\n", u32ThisTimeGenSize, g_TTS_u32TotalDecSize);
#endif

}

static void MApp_TTS_CheckDecBufAndStartSpeaking(BOOL bForceStartPlay)
{
    if( b_TTS_bCheckStartSpeaking )
    {
        U32 u32TTSDecBufLevel = MApp_TTS_Get_DecodeBufferLevel_Byte();
        //printf("{%u,%u}", u32TTSDecBufLevel, MApp_TTS_Get_DecodeBufferLevel_ms());

        if( (u32TTSDecBufLevel >= gu32TTSPlayPreloadBufferSize) // Check TTS Dec buf size > Preload size
          //||(iGenNextResult == TTS_RET_DONE)
          ||(bForceStartPlay)
          )
        {
            //PRINT_CURRENT_LINE();
            DEBUG_TTS_DECODE( printf("[TTS] Start speaking\n"); );

            b_TTS_bCheckStartSpeaking = FALSE;

        #if ( TTS_MEASURE_PERFORMANCE)
            MApp_TTS_Measure_BeforeSay();
        #endif

            MApp_TTS_CB_BeforeSay();

            MApp_TTS_CB_Set_MuteBGM(ENABLE);

            MApp_TTS_SetupAudioDriver(ENABLE);

        #if( TTS_FIRST_WRITE_AU_BUF_TIME )// First time move data to audio buffer
            MApp_TTS_FirstWriteAudioData();
        #endif

            MApp_TTS_Set_MuteTts(FALSE); // UnMute TTS sound

            g_TTS_bEnableAudioBufTask = TRUE;
        }
    }
}

void MApp_TTS_Decode(void)
{
    // If TTS decode buf full, do nothing
    if( MApp_TTS_Get_DecodeBufStatus() == TTS_DEC_BUF_FULL )
    {
        // Do nothing
        //printf(" DecBuf full\n");
        return;
    }

    if( g_TTS_32LastHasDataTime == 0 )
    {
        g_TTS_32LastHasDataTime = MsOS_GetSystemTime();
    }

    // Check buf level before gen ...
    MApp_TTS_CheckBuf_BeforeGenData();

    int iGenNextResult = TTS_RET_DONE;
    U32 u32DecBufWritePointer_New = 0;
    U32 u32DecBufSpace_BeforeGen;
    U32 u32GenNextLoopStartTime = MsOS_GetSystemTime();
    BOOLEAN bThisTimeHasData = FALSE;

    BOOL bForceDecBufSize = FALSE;
    U32 u32ForceDecBufSize = 0;

#if(TTS_FORCE_DECODE_BUF_SIZE_WHEN_SPEAKING)
    // If in speaking, force dec buf size > 300ms
    if( g_TTS_bEnableAudioBufTask )
    {
        if( MApp_TTS_Get_DecodeBufferLevel_ms() < TTS_FORCE_DECODE_BUF_SIZE_WHEN_SPEAKING )
        {
            bForceDecBufSize = TRUE;
            u32ForceDecBufSize = TTS_FORCE_DECODE_BUF_SIZE_WHEN_SPEAKING;
        }
    }
#endif

    // Check user control decode mode
    if( (g_TTS_eTTSDecodeMode == TTS_DECODE_MODE_FORCE_DEC_BUF_FULL)
      ||(g_TTS_eTTSDecodeMode == TTS_DECODE_MODE_FORCE_DEC_BUF_SIZE) )
    {
        bForceDecBufSize = TRUE;
        u32ForceDecBufSize = MsMax(u32ForceDecBufSize, g_TTS_u32ForceDecBufSize_ms);
    }

    //printf("u32ForceDecBufSize=%u\n", u32ForceDecBufSize);

    while(1)
    {
        // Check if user break
        if( MApp_TTS_CheckIfUserBreak() )
        {
            //MApp_TTS_EngineStop();
            //MApp_TTS_Set_State(STATE_TTS_INIT);
            MApp_TTS_Say_Stop();
            return;
            break;
        }


        u32DecBufWritePointer_New = 0;
        u32DecBufSpace_BeforeGen = (TTS_DEC_BUF_MEM_SIZE - MApp_TTS_Get_DecodeBufferLevel_Byte());
        bThisTimeHasData = FALSE;

        // Gen audio data
    #if(TTS_MEASURE_PERFORMANCE)
        MApp_TTS_Measure_GenNextBegin();
    #endif

        iGenNextResult = msAPI_TTS_GenNext(&u32DecBufWritePointer_New);
        //printf(" GenNext => %d %u\n", iGenNextResult, u32DecBufWritePointer_New);

    #if(TTS_MEASURE_PERFORMANCE)
        MApp_TTS_Measure_GenNextEnd();
    #endif

        if( iGenNextResult == TTS_RET_OK )
        {   //printf("[TTS_RET_OK]\n");
            U32 u32CurTime = MsOS_GetSystemTime();

            // Has new data
            if( u32DecBufWritePointer_New != u32TTSWritePoniter )
            {
                DEBUG_TTS_DECODE( printf(" {Has Data, 0x%X at %u} ", u32DecBufWritePointer_New, u32CurTime ); );
                g_TTS_32LastHasDataTime = u32CurTime;
                bThisTimeHasData = TRUE;

                // If has new data,  adjust write pointer
                MApp_TTS_UpdateWritePointer(u32DecBufSpace_BeforeGen, u32DecBufWritePointer_New);

                MApp_TTS_CheckDecBufAndStartSpeaking(FALSE);
            }

            // Check if continue decode ...
            if( bForceDecBufSize )
            {   // Check dec buffer is reach spec
                if( MApp_TTS_Get_DecodeBufferLevel_ms() >= u32ForceDecBufSize )
                {
                    break;
                }
            }
            else //if( g_TTS_eTTSDecodeMode == TTS_DECODE_MODE_NORMAL )
            {
                // Check has new data?
                if( bThisTimeHasData )
                {
                    // If hase data, exit decode
                    break;
                }

                // Check timeout
                u32CurTime = MsOS_GetSystemTime();
                if( msAPI_Timer_DiffTime_2( u32GenNextLoopStartTime, u32CurTime ) > TTS_GEN_NEXT_MS )
                {
                    DEBUG_TTS_DECODE( printf(" No Data at %u, last=%u, => %u\n", u32CurTime, g_TTS_32LastHasDataTime, msAPI_Timer_DiffTime_2(g_TTS_32LastHasDataTime, u32CurTime) ); );
                    break;
                }
            }

            // Check if decode buffer is full
            if( MApp_TTS_Get_DecodeBufStatus() == TTS_DEC_BUF_FULL )
            {
                break;
            }

        }
        else
        {
        #if(ENABLE_TTS_DUMP_DATA)
            msAPI_TTS_Dump_GenData_Finish();
        #endif

            if( iGenNextResult == TTS_RET_DONE )
            { // normal end
                DEBUG_TTS_DECODE( printf("[TTS_RET_DONE]\n"); );
                MApp_TTS_Set_State(STATE_TTS_WAIT_DEC_BUF_EMPTY);
            }
            else // abnormal end
            {
                printf("\nError: msAPI_TTS_GenNext() failed!(iGenNextResult=%d)\n", iGenNextResult);
                MApp_TTS_Say_Stop();
                return;
            }
            break;
        }
    }


    // Check if dec buf level enough to enable audio play
    if( (iGenNextResult == TTS_RET_OK) || (iGenNextResult == TTS_RET_DONE) )
    {
        MApp_TTS_CheckDecBufAndStartSpeaking(iGenNextResult == TTS_RET_DONE);
    }


    // Save this time dec buf level
    g_TTS_u32GenNextLastDecBufLevel = MApp_TTS_Get_DecodeBufferLevel_Byte();

}

void MApp_TTS_MoveDataToAudioBuf(void)
{
    // No TTS data
    if( u32TTSReadPoniter == u32TTSWritePoniter )
        return;


    U32 u32AudioBufLevel = MApp_TTS_Get_AudioBufLevel_Byte_ISR();
    U32 u32AudBufSpaceSize = TTS_AUDIO_DSP_BUFFER_SIZE - u32AudioBufLevel ;

#if(TTS_SW_SRC_ENABLE)
    if ( u32AudBufSpaceSize <= (TTS_WRITE_PCM_UNIT_BYTES_MAX*3) ) // If audio buf space  < TTS_WRITE_PCM_UNIT_BYTES_X3
#else
    if ( u32AudBufSpaceSize <= TTS_WRITE_PCM_UNIT_BYTES_MAX ) // If audio buf space < TTS_WRITE_PCM_UNIT_BYTES
#endif
    {
        return;
    }


    U32 u32CopySize = 0;
    if(g_TTS_bInISR)
    {
        u32CopySize = TTS_WRITE_PCM_UNIT_BYTES;
    }
    else
    {
        u32CopySize = TTS_WRITE_PCM_UNIT_BYTES_FristTime;
    }

    if( (u32TTSReadPoniter < u32TTSWritePoniter) )
    {
        U32 u32TTSLen = u32TTSWritePoniter - u32TTSReadPoniter;

        if (u32TTSLen < u32CopySize)
        {
            MApp_TTS_WriteAudioDmaBuf((void *)((pu8waveout)+u32TTSReadPoniter), u32TTSLen);
            u32TTSReadPoniter += u32TTSLen;
            //if( !g_TTS_bInISR ) printf("L=%u\n", u32TTSLen);
        }
        else
        {
            MApp_TTS_WriteAudioDmaBuf((void *)((pu8waveout)+u32TTSReadPoniter), u32CopySize);
            u32TTSReadPoniter += u32CopySize;
            //if( !g_TTS_bInISR ) printf("L=%u\n", u32CopySize);
        }
    }
    else if ( (u32TTSReadPoniter > u32TTSWritePoniter) )
    {
        U32 u32TTSLen = TTS_DEC_BUF_MEM_SIZE - u32TTSReadPoniter;

        if (u32TTSLen < u32CopySize)
        {
            MApp_TTS_WriteAudioDmaBuf((void *)((pu8waveout)+u32TTSReadPoniter), u32TTSLen);
            //if( !g_TTS_bInISR ) printf("L=%u\n", u32TTSLen);
            u32TTSReadPoniter = 0;
        }
        else
        {
            MApp_TTS_WriteAudioDmaBuf((void *)((pu8waveout)+u32TTSReadPoniter), u32CopySize);
            u32TTSReadPoniter += u32CopySize;
            //if( !g_TTS_bInISR ) printf("L=%u\n", u32CopySize);
        }
    }

    if( u32TTSReadPoniter >= TTS_DEC_BUF_MEM_SIZE )
    {
        u32TTSReadPoniter = 0;
    }
}

static void MApp_TTSAudioPlay(void)
{
    if( g_TTS_bStopISR )
        return;


    // Check if audio driver ready
    //if( g_TTS_bIsAudioDriverReady == FALSE )
    //    return;

    // Check if task enable, (Preload buf)
    if( g_TTS_bEnableAudioBufTask == FALSE )
        return;

    // Check state
    if( !( (STATE_TTS_DECODING == enTTSState)
         ||(STATE_TTS_WAIT_DEC_BUF_EMPTY == enTTSState)
         ||(STATE_TTS_WAIT_AUDIO_BUF_EMPTY == enTTSState)
         )
      )
    {
        return;
    }

    MApp_TTS_MoveDataToAudioBuf();

}

void MApp_TTS_ISR_1ms(void)
{
    g_TTS_bInISR = TRUE;

    g_TTS_u32SysTime += 1;

#if TTS_BUFFER_DBG
    maAPI_TTS_Debug_1ms_ISR();
#endif

    if( !MApp_TTS_Get_StopISR() )
    {

        MApp_TTSAudioPlay();


    #if TTS_WAIT_AU_BUF_EMPTY_IN_ISR
        // Check play done
        if( (enTTSState == STATE_TTS_WAIT_AUDIO_BUF_EMPTY) && g_TTS_bEnableCheckAuBufEmptyInISR )
        {
            if( MApp_TTS_Get_AudioBufLevel_ms_ISR() <= TTS_WAIT_AU_BUF_EMPTY_MS )
            {
                // Mute tts
                MApi_AUDIO_SetMixModeMute(E_AUDIO_INFO_GAME_IN, PCM_VOL, TRUE);  // mute tts
                g_TTS_bEnableCheckAuBufEmptyInISR = FALSE;
            }
        }
    #endif

    }

    g_TTS_bInISR = FALSE;
}

U32 MApp_TTS_Get_AudioBufferLevel_Byte(void)
{
    BOOLEAN bStopISR_Backup = g_TTS_bStopISR;
    U32 u32AudSize;

    g_TTS_bStopISR = TRUE; // Stop Int

    u32AudSize = MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_DMAReader_BufferLevel);

    g_TTS_bStopISR = bStopISR_Backup; // Resume Int

    return u32AudSize;
}

U32 MApp_TTS_Get_AudioBufferLevel_ms(void)
{
    return (MApp_TTS_Get_AudioBufferLevel_Byte() / TTS_AU_BUF_PER_MS_DATA_BYTES);
}

/*
U32 MApp_TTS_Get_AudioBufLevel_Byte_ISR(void)
{
    return MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_DMAReader_BufferLevel);
}
*/

U32 MApp_TTS_Get_AudioBufLevel_ms_ISR(void)
{
    return (MApp_TTS_Get_AudioBufLevel_Byte_ISR()/TTS_AU_BUF_PER_MS_DATA_BYTES);
}

BOOLEAN MApp_TTS_Is_AudioBufEmpty(void)
{
    U32 u32AudioBufDataSize = MApp_TTS_Get_AudioBufferLevel_Byte();
#if TTS_PATCH_AUDIO_BUF_LEVEL
    U32 u32AudioBufEmptyLevel = 8;
#else
    U32 u32AudioBufEmptyLevel = 0;
#endif


#if(TTS_ADD_SILENCE_DATA_MS)
    if( (g_TTS_u32AddSlienceDataSize == 0)&&(enTTSState == STATE_TTS_WAIT_AUDIO_BUF_EMPTY) )
    {
        u32AudioBufEmptyLevel = TTS_ADD_SILENCE_DATA_MS * TTS_AU_BUF_PER_MS_DATA_BYTES;
    }
#endif

    if( u32AudioBufDataSize <= u32AudioBufEmptyLevel )
    {
        return TRUE;
    }

    return FALSE;
}

U32 MApp_TTS_Get_DecodeBufferLevel_Byte_ISR(void)
{
    U32 u32DecodeBufferLevel = 0;
    U32 u32ReadP;
    U32 u32WriteP;

    u32WriteP = u32TTSWritePoniter;
    u32ReadP = u32TTSReadPoniter;

    if (u32ReadP < u32WriteP)
    {
        u32DecodeBufferLevel = (u32WriteP - u32ReadP);
    }
    else if (u32ReadP > u32WriteP)
    {
        u32DecodeBufferLevel = (TTS_DEC_BUF_MEM_SIZE - (u32ReadP - u32WriteP) );
    }
    else
    {
        u32DecodeBufferLevel = 0;
    }

    return u32DecodeBufferLevel;
}

U32 MApp_TTS_Get_DecodeBufferLevel_Byte(void)
{
    BOOLEAN bStopISR_Backup = g_TTS_bStopISR;
    U32 u32DecodeBufferLevel = 0;

    // call by main loop, to avoid ISR access r/w point
    g_TTS_bStopISR = TRUE; // Stop Int

    u32DecodeBufferLevel = MApp_TTS_Get_DecodeBufferLevel_Byte_ISR();

    g_TTS_bStopISR = bStopISR_Backup; // Resume Int

    return u32DecodeBufferLevel;
}

U32 MApp_TTS_Get_DecodeBufferLevel_ms(void) // Unit is ms
{
    return MApp_TTS_Get_DecodeBufferLevel_Byte() / TTS_DEC_BUF_PER_MS_DATA_BYTES;
}

U32 MApp_TTS_Get_DecodeBufferLevel_ms_ISR(void) // Unit is ms
{
    return MApp_TTS_Get_DecodeBufferLevel_Byte_ISR() / TTS_DEC_BUF_PER_MS_DATA_BYTES;
}

EunTTSDecodeBufStatus MApp_TTS_Get_DecodeBufStatus(void)
{
    U32 u32DecodeBuf_B = MApp_TTS_Get_DecodeBufferLevel_Byte();

    if( u32DecodeBuf_B == 0 )
        return TTS_DEC_BUF_EMPTY;

    if( u32DecodeBuf_B >= (TTS_DEC_BUF_LEVEL_FULL_BYTES) )
        return TTS_DEC_BUF_FULL;

    return TTS_DEC_BUF_NOT_FULL;
}

void MApp_TTSControlSetPitch(U16 u16Pitch)
{
#if TTS_IS_ON_HK
    msAPI_TTS_set_Pitch(u16Pitch);
#endif
}

void MApp_TTSControlSetVolume(U16 u16Volume)
{
#if TTS_IS_ON_HK
    msAPI_TTS_set_Volume(u16Volume);
#endif
}

void MApp_TTSControlSetSpeed(U16 u16Speed)
{
#if TTS_IS_ON_HK
    msAPI_TTS_set_Speed(u16Speed);
#endif
}

////////////////////////////////////////////////////////////////////////////////
/// @param u8Vol1      \b : MSB 7-bit register value of 10-bit u8Volume
///                         range from 0x00 to 0x7E , gain: +12db to   -114db (-1 db per step)
////////////////////////////////////////////////////////////////////////////////

const char* MApp_TTSControlSpeakFormatMapping(EN_TTS_SPEAK enSpeakFormat)
{
    static char* table[]={
        TTS_SPEAK_NUMBER_CARDINAL,
        TTS_SPEAK_NUMBER_ORDINAL,
        TTS_SPEAK_NUMBER_DIGITS,
        TTS_SPEAK_CHARACTERS,
        TTS_SPEAK_WORDSCHARS,
        TTS_SPEAK_DATE_MDY,
        TTS_SPEAK_DATE_DMY,
        TTS_SPEAK_DATE_YMD,
        TTS_SPEAK_DATE_MD,
        TTS_SPEAK_DATE_DM,
        TTS_SPEAK_DATE_YM,
        TTS_SPEAK_DATE_MY,
        TTS_SPEAK_DATE_D,
        TTS_SPEAK_DATE_M,
        TTS_SPEAK_DATE_Y,
        TTS_SPEAK_TIME_HMS,
        TTS_SPEAK_TIME_HM,
        TTS_SPEAK_TIME_H
    };
    return table[enSpeakFormat];
}

BOOLEAN MApp_TTS_Get_Enable(void)
{
    return (MApp_TTS_Cus_Get_UserSetting_TTSOn() && g_TTS_bInitDone);
}

void MApp_TTS_EngineStop(void)
{
    DEBUG_FUNC(printf("%s()\n", __FUNCTION__););
    //PRINT_CURRENT_LINE();

    g_TTS_bEnableAudioBufTask = FALSE;

    // Recovery system sound
    MApp_TTS_SetupAudioDriver(DISABLE);

    // Reset TTS
    MApp_TTSControlHandler_Reset();

    MApp_TTS_CB_SayFinish();

    MApp_TTS_CB_Set_MuteBGM(FALSE);
}

BOOLEAN MApp_TTS_Say_Start(void)
{
    if( FALSE == MApp_TTS_Get_Enable() )
        return FALSE;

    if( MApp_TTS_Get_State() != STATE_TTS_INIT )
    {
        return TRUE;
    }

    g_TTS_u32SysTime = 0;
    g_TTS_u8StrCnt = 0;
    g_TTS_bAutoPlayNextStr = TRUE;

#if ( TTS_MEASURE_PERFORMANCE)
    MApp_TTS_Measure_Start();
#endif

    MApp_TTS_Set_State(STATE_TTS_DECODE_INIT);

    return TRUE;
}

BOOLEAN MApp_TTS_Say_Stop(void)
{
    DEBUG_FUNC(printf("%s()\n", __FUNCTION__););

    MApp_TTS_EngineStop();

    MApp_TTS_Set_State(STATE_TTS_INIT);

    return TRUE;
}

#if(TTS_ADD_SILENCE_DATA_MS)
void msAPI_TTS_AddSilenceDataToDecBuf(U32 u32Size)
{
    U32 u32OrgWritePoniter = u32TTSWritePoniter;
    U32 u32WriteSize_1 = 0;
    U32 u32WriteSize_2 = 0;


    // Add silence data
    if( (u32OrgWritePoniter + u32Size) >= TTS_DEC_BUF_MEM_SIZE )
    {
        u32WriteSize_1 = ( TTS_DEC_BUF_MEM_SIZE - u32TTSWritePoniter);
        u32WriteSize_2 = u32Size - u32WriteSize_1;
    }
    else
    {
        u32WriteSize_1 = u32Size;
    }

    // Write data to dec buf
    printf("Clr-1: %X, %X\n", u32TTSWritePoniter, u32WriteSize_1);
    memset(pu8waveout+u32TTSWritePoniter, 0, u32WriteSize_1);

    if( u32WriteSize_2 )
    {
        printf("Clr-2: %X\n", u32WriteSize_2);
        memset(pu8waveout, 0, u32WriteSize_2);
    }

    MApp_TTS_Set_StopISR(TRUE);

    u32TTSWritePoniter = (u32OrgWritePoniter + u32Size)%TTS_DEC_BUF_MEM_SIZE;

    MApp_TTS_Set_StopISR(FALSE);

    printf(" WP: %X -> %X\n", u32OrgWritePoniter, u32TTSWritePoniter);
}

void MApp_TTS_AddSilenceDataToDecBuf(void)
{
    U32 u32WriteSize;
    U32 u32CurDecBufLevel = MApp_TTS_Get_DecodeBufferLevel_Byte();
    U32 u32CurDecBufSpace = (TTS_DEC_BUF_MEM_SIZE - u32CurDecBufLevel);

    //printf("S=%X Dec=%X, %X \n", g_TTS_u32AddSlienceDataSize, u32CurDecBufLevel, u32CurDecBufSpace );

#define WRITE_SILENCE_DATA_SIZE 0x2000

    if( u32CurDecBufSpace < WRITE_SILENCE_DATA_SIZE )
        return;

    if( g_TTS_u32AddSlienceDataSize >= WRITE_SILENCE_DATA_SIZE )
    {
        u32WriteSize = WRITE_SILENCE_DATA_SIZE;
    }
    else
    {
        u32WriteSize = g_TTS_u32AddSlienceDataSize;
    }

    printf(" Si( %X %X %X)\n", g_TTS_u32AddSlienceDataSize, u32CurDecBufSpace, u32WriteSize );

    g_TTS_u32AddSlienceDataSize -= u32WriteSize;

    //printf("  => W=%X S=%X \n", u32WriteSize, g_TTS_u32AddSlienceDataSize);

    msAPI_TTS_AddSilenceDataToDecBuf(u32WriteSize);

}
#endif

void MApp_TTS_WaitDecodeDone(void)
{
    printf("\n===== MApp_TTS_WaitDecodeDone() =====\n");

    while( MApp_TTS_Is_InWorking() )
    {
        MApp_TTSControlHandler_Main();

        if( enTTSState > STATE_TTS_DECODING )
            break;
    }
}

void MApp_TTS_WaitSayFinish(U32 u32WaitTimeout)
{
    printf("\n===== MApp_TTS_WaitSayFinish(%u) =====\n", u32WaitTimeout);

    U32 u32Time_Start = MsOS_GetSystemTime();
    U32 u32Time_Use;

    while( MApp_TTS_Is_InWorking() )
    {
        MApp_TTSControlHandler_Main();

        u32Time_Use = msAPI_Timer_DiffTime_2( u32Time_Start, MsOS_GetSystemTime() );

        if( u32Time_Use >= u32WaitTimeout )
        {
            printf("\n[TTS] Wait say finish timeout!\n");
            break;
        }
    }
}

//---------------------------------------------------------------------------------------------
void MApp_TTS_Set_DecodeDataMode(EunTTSDecodeMode eTTSDecodeMode, U32 u32Para)
{
    printf("MApp_TTS_Set_DecodeDataMode(eTTSDecodeMode=%u, u32Para=%u)\n", eTTSDecodeMode, u32Para);

    g_TTS_eTTSDecodeMode = eTTSDecodeMode;

    if( eTTSDecodeMode == TTS_DECODE_MODE_FORCE_DEC_BUF_FULL )
    {
        g_TTS_u32ForceDecBufSize_ms = TTS_DEC_BUF_LEVEL_FULL_MS;
    }
    else if( eTTSDecodeMode == TTS_DECODE_MODE_FORCE_DEC_BUF_SIZE )
    {
        if( u32Para > TTS_DEC_BUF_LEVEL_FULL_MS )
        {
            u32Para = TTS_DEC_BUF_LEVEL_FULL_MS;
        }
        g_TTS_u32ForceDecBufSize_ms = u32Para;
    }
}

void MApp_TTS_ContiuneDecodingUntilDecBufFull(void)
{
    if( !MApp_TTS_Is_InWorking() )
        return;

    MApp_TTS_Set_DecodeDataMode(TTS_DECODE_MODE_FORCE_DEC_BUF_FULL, 0);

    if( enTTSState == STATE_TTS_DECODE_INIT )
    {
        MApp_TTSControlHandler_Main();
    }

    if( enTTSState == STATE_TTS_DECODING )
    {
        MApp_TTSControlHandler_Main();
    }

    MApp_TTS_Set_DecodeDataMode(TTS_DECODE_MODE_NORMAL, 0);
}

//---------------------------------------------------------------------------------------------
#if( TTS_FORCE_DECODE_BUF_SIZE_WHEN_SPEAKING )
  #define TTS_CALL_GEN_NEXT_PERIOD    200 // ms
#else
  #if( (TTS_LIBRARY_SAMPLE_RATE == TTS_SAMPLE_RATE_48K) \
    ||(TTS_LIBRARY_SAMPLE_RATE == TTS_SAMPLE_RATE_32K) )
    #define TTS_CALL_GEN_NEXT_PERIOD    80 // ms
  #else
    #define TTS_CALL_GEN_NEXT_PERIOD    100 // ms
  #endif
#endif
void MApp_TTSControlHandler_Main(void)
{
    if( enTTSState != STATE_TTS_INIT )
    {
        if( FALSE == MApp_TTS_Get_Enable() )
        {
            MApp_TTS_Say_Stop();
            return;
        }
        else
        {
            // Check if user break
            if( MApp_TTS_CheckIfUserBreak() )
            {
                MApp_TTS_Say_Stop();
                return;
            }
        }

        // Check any error happen!
        if( g_TTS_u16WriteDmaFailCount )
        {
            msDebug_ANSI_SetColorText_2(E_FONT_COLOR_BLACK, E_FONT_BACKGROUND_COLOR_RED);
            printf("\nTTS Error: WriteDmaFail=%u, at %u %s\n", g_TTS_u16WriteDmaFailCount, g_TTS_u32SysTime, ANSI_COLOR_OFF_STR);
            g_TTS_u16WriteDmaFailCount = 0;
        }
        if( g_TTS_u16WriteDmaEmptyCount )
        {
            msDebug_ANSI_SetColorText_2(E_FONT_COLOR_BLACK, E_FONT_BACKGROUND_COLOR_RED);
            printf("\nTTS Error: WriteDmaEmpty=%u, at %u %s\n", g_TTS_u16WriteDmaEmptyCount, g_TTS_u32SysTime, ANSI_COLOR_OFF_STR);
            g_TTS_u16WriteDmaEmptyCount = 0;
        }

    }

#if DEBUG_TTS_STATE_2
    if( enTTSState != STATE_TTS_INIT )
    {
        printf(" case STATE_TTS_%s:\n", MApp_TTS_Get_StateName(enTTSState) );
    }
#endif

    switch(enTTSState)
    {
        case STATE_TTS_INIT:
        break;

        case STATE_TTS_DECODE_INIT:
        {
            //if( MApp_TTS_Get_AudioBufferLevel_Byte() == 0 )//parse string one by one to avoid overlap
            {

                U8* pu8TextBuf_UTF8;
                U16 u16TextBufSize = 0;

                pu8TextBuf_UTF8 = MApp_TTS_Cus_Get_String_UTF8(&u16TextBufSize);
                if( pu8TextBuf_UTF8 == NULL )
                {
                    //printf(" No more String!");
                    MApp_TTS_Say_Stop();
                    return;//break;
                }

                if( MApp_TTS_DecodeInit( pu8TextBuf_UTF8, u16TextBufSize ) )
                {
                    // OK: Goto decoding state
                    MApp_TTS_Set_State(STATE_TTS_DECODING);
                    g_TTS_u32GenNextLastTime = 0;//MsOS_GetSystemTime();
                }
                else
                {
                    // NG: Stop right now
                    MApp_TTS_Say_Stop();
                    return;
                }
            }
        }
        break;

        case STATE_TTS_DECODING:
        {
            U32 u32CurTime = MsOS_GetSystemTime();
            U32 u32DiffTime = 0;

            if( g_TTS_u32GenNextLastTime )
            {
                u32DiffTime = msAPI_Timer_DiffTime_2(g_TTS_u32GenNextLastTime, u32CurTime);

                U32 u32DecBuf_ms = MApp_TTS_Get_DecodeBufferLevel_ms();
                U32 u32AuBuf_ms = MApp_TTS_Get_AudioBufferLevel_ms();

                if( u32DiffTime >= TTS_CALL_GEN_NEXT_PERIOD )
                {
                    printf("\nWarning: Call MApp_TTS_Decode() too late: %u {%u,%u} at %u\n", u32DiffTime, u32DecBuf_ms, u32AuBuf_ms, g_TTS_u32SysTime );
                }
            }

            // Decoding ...
            {
                U8 i;
                U32 u32Time_Before;
                U32 u32Time_After;
            #define TTS_CALL_DECODE_TIME_PER_MAIN   1

                DEBUG_TTS_DECODE_2( printf("\nGen-Start: %u at %u, {%u,%u}\n", u32DiffTime, MsOS_GetSystemTime(), MApp_TTS_Get_DecodeBufferLevel_ms(), MApp_TTS_Get_AudioBufferLevel_ms()); );
                for( i = 0; i < TTS_CALL_DECODE_TIME_PER_MAIN; i += 1 )
                {
                    u32Time_Before = MsOS_GetSystemTime();

                    MApp_TTS_Decode();

                    u32Time_After = MsOS_GetSystemTime();

                    DEBUG_TTS_DECODE_2( printf("Gen-End: use %u at %u, {%u,%u}\n", msAPI_Timer_DiffTime_2(u32Time_Before, u32Time_After), u32Time_After, MApp_TTS_Get_DecodeBufferLevel_ms(), MApp_TTS_Get_AudioBufferLevel_ms() ); );

                    if( enTTSState != STATE_TTS_DECODING )
                    {
                        break;
                    }
                }
            }

            // Save the time
            g_TTS_u32GenNextLastTime = MsOS_GetSystemTime();

        }
        break;

        case STATE_TTS_WAIT_DEC_BUF_EMPTY:
        #if(TTS_ADD_SILENCE_DATA_MS)
            // Add silence data to dec buffer
            if( g_TTS_u32AddSlienceDataSize )
            {
                MApp_TTS_AddSilenceDataToDecBuf();
            }
        #endif

            //printf("Dec=%u, Au=%u\n", MApp_TTS_Get_DecodeBufferLevel_Byte(), MApp_TTS_Get_AudioBufferLevel_Byte());
            if( TTS_DEC_BUF_EMPTY == MApp_TTS_Get_DecodeBufStatus() )
            {
                // Stop audio dma task
                g_TTS_bEnableAudioBufTask = FALSE;

            #if(TTS_WAIT_AU_BUF_EMPTY_IN_ISR)
                // Enable check audio buffer in ISR
                g_TTS_bEnableCheckAuBufEmptyInISR = TRUE;
            #endif

                MApp_TTS_Set_State(STATE_TTS_WAIT_AUDIO_BUF_EMPTY);
            }
            break;

        case STATE_TTS_WAIT_AUDIO_BUF_EMPTY:

            if( MApp_TTS_Is_AudioBufEmpty() )
            {
                MApp_TTS_Set_MuteTts(TRUE);

                // Disable Audio DMA
                MApp_TTS_SetupAudioDriver(DISABLE);

                //PRINT_CURRENT_LINE();
                //printf("[TTS] speak end ~\n");


            #if TTS_BUFFER_DBG
                maAPI_TTS_Debug_Set_RecordBufferEnable(DISABLE);
                // Print info after playing one string
                maAPI_TTS_Debug_PrintBuffer();
            #endif

                g_TTS_u8StrCnt += 1;

                if( g_TTS_bAutoPlayNextStr )
                {
                    // Play another string
                    MApp_TTS_Set_State(STATE_TTS_DECODE_INIT);
                }
                else
                {
                    MApp_TTS_Say_Stop();
                }
            }
            break;

        default:
            MApp_TTS_Set_State(STATE_TTS_INIT);
            break;
    }

}


#endif

