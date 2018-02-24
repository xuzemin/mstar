#ifndef _LIBMSTTS_H_
#define _LIBMSTTS_H_

//====================================================
#define MS_TTS_LIB_VERSION  "1.0.18"

// 1.0.18: Add new sample rate -> TTS_SAMPLE_RATE_32K
// 1.0.17: Add msAPI_TTS_Set_EnabledEmphasis()
// 1.0.16: Add msAPI_TTS_Set_GenDataMaxSize()
// 1.0.15: Add support MADELINE
// 1.0.14: Add support MAYA
// 1.0.13: Fix bug: Set same lang will no sound
// 1.0.12: 1. msAPI_TTS_set_Speed() range change.
//         2. Add api: msAPI_TTS_Set_SampleRate()
// 1.0.11: Refine message
// 1.0.10: Fix bug: Read chip ID failed
// 1.0.9: Refine check hash key method
// 1.0.8: Refine check hash key method
// 1.0.7: Refine check hash key
// 1.0.6: Fix bug: When wave data size == dec buffer size, WP value is wrong
// 1.0.5: Add debug function.
// 1.0.4: Add new feature: support 2nd lang

//====================================================
#define TTS_LANG_NONE 0

#define LANG_EN_US  4
#define LANG_ES_MX  7
#define LANG_FR_FR  8
#define LANG_KO_KR  10
#define LANG_PT_BR  12
#define LANG_PT_PT  27
#define LANG_ES_ES  33


typedef U8 TypTTSLangId;

//====================================================
#ifndef BUILD_TTS_LIB
typedef enum
{
	TTS_RET_STOP= -11,
	TTS_RET_PARAM_ERROR = -10,
	TTS_RET_MEMORY_FAIL=-9,
	TTS_RET_DONE= -6,
	TTS_RET_OK	= 0,
	TTS_RET_LANGUAGE_UNSUPPORT= -101
} TTS_RETURN;
/*
typedef enum
{
    TTS_SAMPLE_RATE_16K = 0,
    TTS_SAMPLE_RATE_48K = 1,
    TTS_SAMPLE_RATE_32K = 2,
} TTS_SAMPLE_RATE;
*/
// Do not change these define!!
// These define must be same as lib libTTS2.h
#define TTS_SAMPLE_RATE_16K 0
#define TTS_SAMPLE_RATE_48K 1
#define TTS_SAMPLE_RATE_32K 2
typedef U8 TTS_SAMPLE_RATE;

#endif

typedef enum
{
    TTS_PARAM_ERROR = -30,                 //tts input string error
    TTS_FAIL,                              //tts engine error
    TTS_FAIL_VOICE_NOT_SUPPORT,            //tts not support voice setting
    TTS_FAIL_LANGUAGE_NOT_SUPPORT,         //tts not support language setting
    TTS_FAIL_CANNOT_LOAD_DATABASE,         //tts engine cannt load database
    TTS_FAIL_SET_PITCH_NOT_SUPPORT,        //tts not support pitch setting
    TTS_FAIL_SET_VOICE_VOLUME_NOT_SUPPORT, //tts not support volume setting
    TTS_FAIL_SET_SPEED_NOT_SUPPORT,        //tts not support speed setting
    TTS_MEMORY_FAIL,                       //tts engine cannot malloc enough memory
    /* success status always > 0 */
    TTS_DONE = 1,                          //tts engine synthesis string done
    TTS_WAV_OUT_STOP,                      //tts engine recevies stop command
    TTS_OK,                                //tts engine temporally yield for time sharing
} EN_TTS_RETURN;

typedef enum
{
    E_TTS_DBGLV_NONE,    //disable all the debug message
    E_TTS_DBGLV_ERR,     //error conditions
    E_TTS_DBGLV_WARNING, //warning conditions
    E_TTS_DBGLV_INFO,    //information
    E_TTS_DBGLV_DEBUG,   //debug-level messages
} TTS_DbgLv;


int msAPI_TTS_SetDbgLevel(TTS_DbgLv u8DbgLevel);

BOOLEAN msAPI_TTS_Init(TypTTSLangId LangId, TypTTSLangId LangId_2nd);

EN_TTS_RETURN msAPI_TTS_set_Language(TypTTSLangId LangId, TypTTSLangId LangId_2nd);

TypTTSLangId msAPI_TTS_get_Language(void);

int msAPI_TTS_GenNext(unsigned long *count);

int msAPI_TTS_Say(unsigned char* text, unsigned int text_len, unsigned char* waveout, unsigned int waveout_len);

unsigned int msAPI_TTS_get_Pitch(void);

void msAPI_TTS_set_Volume(unsigned int Volume);

void msAPI_TTS_set_Pitch(unsigned int Pitch);

// Speed range: 50 ~ 250
void msAPI_TTS_set_Speed(unsigned int Speed);

void msAPI_TTS_set_Log(BOOLEAN bEn);
void msAPI_TTS_set_PhraseFlush(BOOLEAN bEn);

void msAPI_TTS_Set_SampleRate(TTS_SAMPLE_RATE eTtsSampleRate);

#define ENABLE_MSAPI_TTS_SET_GEN_DATA_MAX_SIZE  1
void msAPI_TTS_Set_GenDataMaxSize(U32 u32MaxSize);

const char* msAPI_TTS_Get_Version_C(void);
void msAPI_TTS_PrintVersion(void);
void* msAPI_TTS_GetHandle(void);

void msAPI_TTS_Set_EnableEmphasis(BOOLEAN bEn);

void msAPI_TTS_Set_PostFilter(BOOLEAN bEnable); //default : disable

void msAPI_TTS_Set_SentenceBreak(BOOLEAN bEnable);//default : Enable


//========================================================================

#endif // _LIBMSTTS_H_

