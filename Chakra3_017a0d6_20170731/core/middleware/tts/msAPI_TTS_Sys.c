
#include "Board.h"

#if( ENABLE_ATSC_TTS )
#include <string.h>

#include "sysinfo.h"

#include "BinInfo.h"
#include "SysInit.h"

#include "msAPI_BDMA.h"

#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalFunction.h"


#include "libMsTTS.h"
#include "msAPI_TTS_Sys.h"
#include "MApp_TTSControlHandler.h"

//----------------------------------------------------------------

#include "ttsConst.h"

#include "tn_en.h"
#if(ENABLE_TTS_LANG_ES_MX)
#include "tn_es.h"
#endif
#if(ENABLE_TTS_LANG_FRANCH)
#include "tn_fr.h"
#endif
#if(ENABLE_TTS_LANG_KO)
#include "tn_ko.h"
#endif

//======================================================================================
#define DEBUG_API_TTS(x)    //x

#define DEBUG_API_TTS_TIME()   //do{ printf("%u t=%u\n", __LINE__, MsOS_GetSystemTime());}while(0);
//======================================================================================

#define ENABLE_TTS_NLP_BUF      (ENABLE_TTS_LANG_ENGLISH_NLP)

// En-205K
#define TTS_PROSODY_BUF_SIZE    (210*1024)
// En-889K
#define TTS_VOICE_BUF_SIZE      (900*1024)

typedef struct
{
    U8 u8LangId;
    U32 au32ProsodyData[TTS_PROSODY_BUF_SIZE/4];
    U32 au32VoiceData[TTS_VOICE_BUF_SIZE/4];
} StuTtsBuf;

#if(ENABLE_TTS_2ND_LANG)
    #define TTS_DATA_BUF_NUM    2
#else
    #define TTS_DATA_BUF_NUM    1
#endif
static StuTtsBuf g_TTS_astTtsBuf[TTS_DATA_BUF_NUM];


#if(ENABLE_TTS_NLP_BUF)
// en.nlp - 1007K
#define TTS_NLP_BUF_SIZE        (1024*1024)
static U32 g_TTS_au8NlpData[TTS_NLP_BUF_SIZE/4]={0};
static U16 g_TTS_u16NlpBufFromBinId = 0;
static BOOLEAN g_TTS_bNlpDataExist = 0;
#endif

U8 g_TTS_u8CurLangId = 0xFF;
#if(ENABLE_TTS_2ND_LANG)
U8 g_TTS_u8CurLangId_2nd = 0xFF;
#endif

// Heap ram for Kernel (20160118):
// English: 341K
// Spanish: 315K
// French:  282K
// Korean: 442K

#if 1 // Use ttsConst.h
    #define TTS_HEAP_RAM_SIZE   TTS_HEAP_MEM_SIZE
#elif( ENABLE_TTS_LANG_KO ) // Korean
    #define TTS_HEAP_RAM_SIZE (1075*442) // 1075=1024*1.05
#elif 0//(ENABLE_TTS_LANG_ES_MX) // Spanish
    #define TTS_HEAP_RAM_SIZE (1024*315)
#else // English
    #define TTS_HEAP_RAM_SIZE (1075*341) // English
#endif

static char g_TTS_acHeapRamBuf[TTS_HEAP_RAM_SIZE];

//======================================================================================
char* msAPI_TTS_Sys_Get_Buf_HeapRam(U8 u8LangId, U32* pu32HeapRamSize)
{
    u8LangId=u8LangId;
    *pu32HeapRamSize = TTS_HEAP_RAM_SIZE;
    return g_TTS_acHeapRamBuf;
}

U8 msAPI_TTS_Sys_Get_BufIdx_ByLangId(U8 u8LangId)
{
#if( TTS_DATA_BUF_NUM >= 2 )
    U8 u8BufIdx = 0;
    int i;

    for( i = 0; i < TTS_DATA_BUF_NUM; ++ i )
    {
        if( u8LangId == g_TTS_astTtsBuf[i].u8LangId )
        {
            u8BufIdx = i;
            break;
        }
    }

    return u8BufIdx;

#else
    UNUSED(u8LangId);
    return 0;
#endif
}

U32* msAPI_TTS_Sys_Get_Buf_Prosody(U8 u8LangId)
{
    U8 u8BufIdx = msAPI_TTS_Sys_Get_BufIdx_ByLangId(u8LangId);

    return g_TTS_astTtsBuf[u8BufIdx].au32ProsodyData;
}

U32* msAPI_TTS_Sys_Get_Buf_Voice(U8 u8LangId)
{
    U8 u8BufIdx = msAPI_TTS_Sys_Get_BufIdx_ByLangId(u8LangId);

    return g_TTS_astTtsBuf[u8BufIdx].au32VoiceData;
}

U32* msAPI_TTS_Sys_Get_Buf_Nlp(U8 u8LangId)
{
#if(ENABLE_TTS_NLP_BUF)
    UNUSED(u8LangId);

    if( g_TTS_bNlpDataExist && (u8LangId==LANG_EN_US) )
        return (U32*)g_TTS_au8NlpData;
    else
        return NULL;
#else
    UNUSED(u8LangId);
    return NULL;
#endif
}

int* msAPI_TTS_Sys_Get_Buf_TextNorm(U8 u8LangId)
{
    int* piTextNorm = NULL;

    switch(u8LangId)
    {
        case LANG_EN_US:
            piTextNorm = (int*)tn_en;
            break;

    #if(ENABLE_TTS_LANG_ES_MX)
        case LANG_ES_MX:
            piTextNorm = (int*)tn_es;
            break;
    #endif

    #if(ENABLE_TTS_LANG_FRANCH)
        case LANG_FR_FR:
            piTextNorm = (int*)tn_fr;
            break;
    #endif

    #if( ENABLE_TTS_LANG_KO )
        case LANG_KO_KR:
            piTextNorm = (int*)tn_ko;
            break;
    #endif

        default:
            printf("\nError: Unsupported lang=%u\n", u8LangId);
            break;
    }

    return piTextNorm;
}

extern void Print_Buffer(U8* pu8Buf, U32 u32Size );
BOOLEAN msAPI_TTS_Sys_LoadBinToBuf(U16 u16BinId, U8* au8Buffer, U32 u32BufSize)
{
    DEBUG_API_TTS( printf("msAPI_TTS_Sys_LoadBinToBuf(u16BinId=0x%X, au8Buffer=0x%X)\n", u16BinId, (U32)au8Buffer); );

    BININFO stBinInfo;
    BOOL bResult;


    // Load Prosody bin
    stBinInfo.B_ID = u16BinId;
    MDrv_Sys_Get_BinInfo(&stBinInfo, &bResult);
    if (!bResult)
    {
        printf("Get bin fail!!\n");
        return FALSE;
    }

    DEBUG_API_TTS(printf("BinAddr=0x%X\n",stBinInfo.B_FAddr););
    DEBUG_API_TTS(printf("BinSize=0x%X(%uK)\n", stBinInfo.B_Len, (stBinInfo.B_Len + 1023)/1024););

    //eRETCODE MDrv_DMA_LoadBin(BININFO *pBinInfo, U32 u32DstVA, U32 u32DecVA, U32 u32TmpVA)
    if( !MDrv_DMA_LoadBin( &stBinInfo,
                            (U32)au8Buffer,
                            _PA2VA(POOL_BUFFER_ADR),
                            _PA2VA(POOL_BUFFER_ADR+0x180000)
                          )
      )
    {
        printf("\nError: MDrv_DMA_LoadBin() Fail!\n");
        return FALSE;
    }

    // Check if buffer size enough
    DEBUG_API_TTS(printf("[TTS]Ori Size=0x%u\n", stBinInfo.B_Len););
    if( stBinInfo.B_Len >= u32BufSize )
    {
        printf("\nError: Bin Size=%u > Buffer size=%u!\n", stBinInfo.B_Len, u32BufSize);
        return FALSE;
    }

    //Print_Buffer(au8Buffer, 256);

    return TRUE;
}

BOOLEAN msAPI_TTS_Sys_Init_Buf(U8 u8LangId, U8 u8LangIdx)
{
    DEBUG_API_TTS( printf("msAPI_TTS_Sys_Init_Buf(lang=%u,u8LangIdx=%u)\n", u8LangId, u8LangIdx); );

#if(!ENABLE_TTS_2ND_LANG)
    if( u8LangIdx > 0 )
    {
        return FALSE;
    }
#endif


#if(ENABLE_TTS_2ND_LANG)
    if( u8LangIdx == 1 )
    {
        if( u8LangId == TTS_LANG_NONE )
        { // Turn off 2nd lang
            // No need do anything...
            return TRUE;
        }
    }
#endif


    U16 u16BinId_Prosody = 0, u16BinId_Voice = 0;
#if(ENABLE_TTS_NLP_BUF)
    U16 u16BinId_NLP = 0;
#endif

    switch(u8LangId)
    {
        default:
            printf("\nError: Unsupported lang=%u\n", u8LangId);
            return FALSE;
            break;

        case LANG_EN_US:
#if(FLASH_SIZE <= FLASH_SIZE_4MB)    
            u16BinId_Prosody = BIN_ID_TTS_ENG_PROSODY_COMPRESS;
            u16BinId_Voice = BIN_ID_TTS_ENG_VOICE_COMPRESS;
#else
            u16BinId_Prosody = BIN_ID_TTS_ENG_PROSODY;
            u16BinId_Voice = BIN_ID_TTS_ENG_VOICE;
#endif
#if(ENABLE_TTS_LANG_ENGLISH_NLP)
            u16BinId_NLP = BIN_ID_TTS_ENG_NLP;
#endif
            break;

    #if(ENABLE_TTS_LANG_ES_MX)
        case LANG_ES_MX:
            u16BinId_Prosody = BIN_ID_TTS_MX_PROSODY;
            u16BinId_Voice = BIN_ID_TTS_MX_VOICE;
            break;
    #endif

    #if(ENABLE_TTS_LANG_FRANCH)
        case LANG_FR_FR:
            u16BinId_Prosody = BIN_ID_TTS_FR_PROSODY;
            u16BinId_Voice = BIN_ID_TTS_FR_VOICE;
            break;
    #endif

    #if(ENABLE_TTS_LANG_KO)
        case LANG_KO_KR:
            u16BinId_Prosody = BIN_ID_TTS_KR_PROSODY;
            u16BinId_Voice = BIN_ID_TTS_KR_VOICE;
            break;
    #endif

    }


    U8 u8BufIdx = 0;
#if(ENABLE_TTS_2ND_LANG)
    if( u8LangIdx == 1 ) // 2nd lang use 2nd buf
    {
        u8BufIdx = 1;
    }
#endif

    //DEBUG_API_TTS(printf("g_TTS_au8ProsodyData: 0x%X 0x%X\n", (U32)g_TTS_au8ProsodyData, sizeof(g_TTS_au8ProsodyData)););
    //DEBUG_API_TTS(printf("g_TTS_au8VoiceData: 0x%X 0x%X\n", (U32)g_TTS_au8VoiceData, sizeof(g_TTS_au8VoiceData)););

    g_TTS_astTtsBuf[u8BufIdx].u8LangId = 0xFF;
    // Load Prosody bin
    if( FALSE == msAPI_TTS_Sys_LoadBinToBuf(u16BinId_Prosody, (U8*)g_TTS_astTtsBuf[u8BufIdx].au32ProsodyData, TTS_PROSODY_BUF_SIZE) )
    {
        printf("[TTS] Load prosody bin fail!!\n");
        return FALSE;
    }

    // Load Voice bin
    if( FALSE == msAPI_TTS_Sys_LoadBinToBuf(u16BinId_Voice, (U8*)g_TTS_astTtsBuf[u8BufIdx].au32VoiceData, TTS_VOICE_BUF_SIZE) )
    {
        printf("[TTS] Load Voice bin fail!!\n");
        return FALSE;
    }

    // Assign correct langId
    g_TTS_astTtsBuf[u8BufIdx].u8LangId = u8LangId;

#if(ENABLE_TTS_NLP_BUF)
    // Load NLP bin
    g_TTS_bNlpDataExist = FALSE;
    if( u16BinId_NLP )
    {
        if( g_TTS_u16NlpBufFromBinId != u16BinId_NLP )
        {
            DEBUG_API_TTS(printf("g_TTS_au8NlpData: 0x%X 0x%X\n", (U32)g_TTS_au8NlpData, sizeof(g_TTS_au8NlpData)););
            if( FALSE == msAPI_TTS_Sys_LoadBinToBuf(u16BinId_NLP, (U8*)g_TTS_au8NlpData, TTS_NLP_BUF_SIZE) )
            {
                printf("[TTS] Load NLP bin fail!!\n");
                return FALSE;
            }
            g_TTS_u16NlpBufFromBinId = u16BinId_NLP;
        }

        g_TTS_bNlpDataExist = TRUE;
    }
#endif

    return TRUE;
}

BOOLEAN msAPI_TTS_Sys_Init_Buf_2(U8 u8LangId, U8 u8LangId_2nd)
{
    DEBUG_API_TTS( printf("msAPI_TTS_Sys_Init_Buf_2(lang=%u,u8LangId_2nd=%u)\n", u8LangId, u8LangId_2nd); );

    // Init 1st lang buf
    if( g_TTS_u8CurLangId != u8LangId )
    {
        if( FALSE == msAPI_TTS_Sys_Init_Buf(u8LangId, 0) )
        {
            return FALSE;
        }
        g_TTS_u8CurLangId = u8LangId;
    }

    // Init 2nd lang buf
#if(ENABLE_TTS_2ND_LANG)
    if( g_TTS_u8CurLangId_2nd != u8LangId_2nd )
    {
        if( FALSE == msAPI_TTS_Sys_Init_Buf(u8LangId_2nd, 1) )
        {
            return FALSE;
        }
        g_TTS_u8CurLangId_2nd = u8LangId_2nd;
    }
#else
    UNUSED(u8LangId_2nd);
#endif

    return TRUE;
}

BOOLEAN msAPI_TTS_Sys_Is_SupportedLang(U8 u8LangId)
{
    switch(u8LangId)
    {
        default:
            break;

        case LANG_EN_US:
    #if(ENABLE_TTS_LANG_ES_MX)
        case LANG_ES_MX:
    #endif
    #if(ENABLE_TTS_LANG_FRANCH)
        case LANG_FR_FR:
    #endif
    #if(ENABLE_TTS_LANG_KO)
        case LANG_KO_KR:
    #endif
            return TRUE;
            break;
    }

    return FALSE;
}

BOOLEAN msAPI_TTS_Sys_Init(U8 u8LangId, U8 u8LangId_2nd)
{
    DEBUG_API_TTS( printf("msAPI_TTS_Sys_Init(lang=%u,u8LangId_2nd=%u)\n", u8LangId, u8LangId_2nd); );

    DEBUG_API_TTS_TIME();

#if( !ENABLE_TTS_2ND_LANG )
    if( u8LangId_2nd != TTS_LANG_NONE )
    {
        printf("\nError: Unsupport 2nd lang mode!\n");
        return FALSE;
    }
#endif

    // Check if 1st lang supported?
    if( !msAPI_TTS_Sys_Is_SupportedLang(u8LangId) )
    {
        printf("\nError: Unsupport lang=%u\n", u8LangId);
        return FALSE;
    }

#if( ENABLE_TTS_2ND_LANG )
    // Check if 1st 2nd supported?
    if( u8LangId_2nd != TTS_LANG_NONE )
    {
        if( !msAPI_TTS_Sys_Is_SupportedLang(u8LangId_2nd) )
        {
            printf("\nError: Unsupport 2nd_lang=%u\n", u8LangId_2nd);
            return FALSE;
        }
    }
#endif

    //msAPI_TTS_SetDbgLevel(E_TTS_DBGLV_INFO);
    msAPI_TTS_SetDbgLevel(E_TTS_DBGLV_DEBUG);

    msAPI_TTS_PrintVersion();

    printf("[TTS] TTS_SW_SRC_ENABLE=%d\n", TTS_SW_SRC_ENABLE);
    printf("[TTS] TTS_LIBRARY_SAMPLE_RATE=%d\n", TTS_LIBRARY_SAMPLE_RATE);

    DEBUG_API_TTS_TIME();

    memset( g_TTS_astTtsBuf, 0, sizeof(g_TTS_astTtsBuf) );

    DEBUG_API_TTS_TIME();

    if( FALSE == msAPI_TTS_Sys_Init_Buf_2(u8LangId, u8LangId_2nd) )
    {
        printf("\nError: [TTS] msAPI_TTS_Sys_Init fail!!\n");
        return FALSE;
    }

    DEBUG_API_TTS_TIME();


#if( TTS_LIBRARY_SAMPLE_RATE != TTS_SAMPLE_RATE_16K )
  #ifdef ENABLE_MSAPI_TTS_SET_GEN_DATA_MAX_SIZE
    msAPI_TTS_Set_GenDataMaxSize(TTS_LIB_GEN_DATA_MAX_SIZE);
  #endif
#endif

    //msAPI_TTS_set_Log(FALSE);

    if( FALSE == msAPI_TTS_Init(u8LangId, u8LangId_2nd) )
    {
        MApp_Fatal_Error("[TTS] Check hash key or library or heap size", __FUNCTION__);
        return FALSE;
    }

    DEBUG_API_TTS_TIME();

#if( TTS_LIBRARY_SAMPLE_RATE != TTS_SAMPLE_RATE_16K )
    msAPI_TTS_Set_SampleRate(TTS_LIBRARY_SAMPLE_RATE);
#endif

    DEBUG_API_TTS_TIME();

    msAPI_TTS_Set_PostFilter(ENABLE);

    msAPI_TTS_SetDbgLevel(E_TTS_DBGLV_INFO);

    return TRUE;
}

BOOLEAN msAPI_TTS_Sys_Set_Langage(U8 u8LangId, U8 u8LangId_2nd)
{
    DEBUG_API_TTS( printf("msAPI_TTS_Sys_Set_Langage(lang=%u,u8LangId_2nd=%u)\n", u8LangId, u8LangId_2nd); );

#if( !ENABLE_TTS_2ND_LANG )
    if( u8LangId_2nd != TTS_LANG_NONE )
    {
        printf("\nError: Unsupport 2nd lang mode!\n");
        return FALSE;
    }
#endif

    // Check if 1st lang supported?
    if( !msAPI_TTS_Sys_Is_SupportedLang(u8LangId) )
    {
        printf("\nError: Unsupport lang=%u\n", u8LangId);
        return FALSE;
    }

#if( ENABLE_TTS_2ND_LANG )
    // Check if 1st 2nd supported?
    if( u8LangId_2nd != TTS_LANG_NONE )
    {
        if( !msAPI_TTS_Sys_Is_SupportedLang(u8LangId_2nd) )
        {
            printf("\nError: Unsupport 2nd_lang=%u\n", u8LangId_2nd);
            return FALSE;
        }
    }
#endif

    if( FALSE == msAPI_TTS_Sys_Init_Buf_2(u8LangId, u8LangId_2nd) )
        return FALSE;

    if( TTS_OK != msAPI_TTS_set_Language(u8LangId, u8LangId_2nd) )
        return FALSE;

#if( TTS_LIBRARY_SAMPLE_RATE != TTS_SAMPLE_RATE_16K )
    msAPI_TTS_Set_SampleRate(TTS_LIBRARY_SAMPLE_RATE);
#endif

    return TRUE;
}

#if 0
void TTS_Log(int en)
{
    en=en;
}
#endif

#endif

