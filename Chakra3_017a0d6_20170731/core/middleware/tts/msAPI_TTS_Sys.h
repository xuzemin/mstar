#ifndef _MAPI_TTS_SYS_H_
#define _MAPI_TTS_SYS_H_


#include "Board.h"

#if( ENABLE_ATSC_TTS )

#include "libMsTTS.h"


//==========================================================================
#define MS_TTS_LIB_16_IN_16_OUT             0      // whisky like chip, include HW_SRC
#define MS_TTS_LIB_16_IN_SW_SRC_48_OUT      1
#define MS_TTS_LIB_48_IN_48_OUT             2
#define MS_TTS_LIB_32_IN_32_OUT             3

#ifndef MS_TTS_SAMPLING_RATE_SEL
    #if( CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN )
        #define MS_TTS_SAMPLING_RATE_SEL        MS_TTS_LIB_48_IN_48_OUT
    #else
        #define MS_TTS_SAMPLING_RATE_SEL        MS_TTS_LIB_16_IN_16_OUT
    #endif
#endif

#if( MS_TTS_SAMPLING_RATE_SEL == MS_TTS_LIB_16_IN_16_OUT)
    #define TTS_SW_SRC_ENABLE           DISABLE
    #define TTS_LIBRARY_SAMPLE_RATE     TTS_SAMPLE_RATE_16K
    #define TTS_AUDIO_SAMPLE_RATE       SAMPLE_RATE_16000

#elif( MS_TTS_SAMPLING_RATE_SEL == MS_TTS_LIB_16_IN_SW_SRC_48_OUT)
    #define TTS_SW_SRC_ENABLE           ENABLE
    #define TTS_LIBRARY_SAMPLE_RATE     TTS_SAMPLE_RATE_16K
    #define TTS_AUDIO_SAMPLE_RATE       SAMPLE_RATE_48000

#elif( MS_TTS_SAMPLING_RATE_SEL == MS_TTS_LIB_48_IN_48_OUT)
    #define TTS_SW_SRC_ENABLE           DISABLE
    #define TTS_LIBRARY_SAMPLE_RATE     TTS_SAMPLE_RATE_48K
    #define TTS_AUDIO_SAMPLE_RATE       SAMPLE_RATE_48000

#elif( MS_TTS_SAMPLING_RATE_SEL == MS_TTS_LIB_32_IN_32_OUT)
    #define TTS_SW_SRC_ENABLE           DISABLE
    #define TTS_LIBRARY_SAMPLE_RATE     TTS_SAMPLE_RATE_32K
    #define TTS_AUDIO_SAMPLE_RATE       SAMPLE_RATE_32000

#else
    #error "Unknown"
#endif
//==========================================================================

#ifndef ENABLE_TTS_2ND_LANG
#define ENABLE_TTS_2ND_LANG 0//ENABLE
#endif

//==========================================================================
#define MS_TTS_LIB_EN           0
#define MS_TTS_LIB_EN_SP_FR     1
#define MS_TTS_LIB_EN_KR        2
#define MS_TTS_LIB_EN_SP_FR_KR  3

#ifndef MS_TTS_LIB_SEL
//#define MS_TTS_LIB_SEL      MS_TTS_LIB_EN
#endif

//==========================================================================
#define ENABLE_TTS_LANG_ENGLISH     1
#define ENABLE_TTS_LANG_ENGLISH_NLP 0

#if( (MS_TTS_LIB_SEL == MS_TTS_LIB_EN_SP_FR)||(MS_TTS_LIB_SEL == MS_TTS_LIB_EN_SP_FR_KR) )
    #define ENABLE_TTS_LANG_ES_MX   1 // Spanish/Maxcico
#else
    #define ENABLE_TTS_LANG_ES_MX   0 // Spanish/Maxcico
#endif

#if( (MS_TTS_LIB_SEL == MS_TTS_LIB_EN_SP_FR)||(MS_TTS_LIB_SEL == MS_TTS_LIB_EN_SP_FR_KR) )
    #define ENABLE_TTS_LANG_FRANCH  1
#else
    #define ENABLE_TTS_LANG_FRANCH  0
#endif

#if( (MS_TTS_LIB_SEL == MS_TTS_LIB_EN_KR)||(MS_TTS_LIB_SEL == MS_TTS_LIB_EN_SP_FR_KR) )
    #define ENABLE_TTS_LANG_KO      1
#else
    #define ENABLE_TTS_LANG_KO      0
#endif

//==========================================================================

#if( (TTS_LIBRARY_SAMPLE_RATE == TTS_SAMPLE_RATE_48K) \
   ||(TTS_LIBRARY_SAMPLE_RATE == TTS_SAMPLE_RATE_32K) )
    #define TTS_LIB_GEN_DATA_MAX_SIZE       0x2000
#else
    #define TTS_LIB_GEN_DATA_MAX_SIZE       0x1000
#endif
//==========================================================================

#define TTS_HANDLE void*

//==========================================================================
BOOLEAN msAPI_TTS_Sys_Init(U8 u8LangId, U8 u8LangId_2nd);

BOOLEAN msAPI_TTS_Sys_Set_Langage(U8 u8LangId, U8 u8LangId_2nd);

BOOLEAN msAPI_TTS_Sys_Is_SupportedLang(U8 u8LangId);

//==========================================================================

#endif // #if( ENABLE_ATSC_TTS )

#endif

