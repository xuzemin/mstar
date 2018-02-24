#ifndef _MSAPI_DTVSYSTEM_ATSC_H_
#define _MSAPI_DTVSYSTEM_ATSC_H_


#include "Board.h"

#if( ENABLE_ATSC )

//#include "msAPI_DTVSystem.h"

typedef struct
{
    U8 u8Test;

    U8 _u8CurrentRRT_Dimension;
    U8 _u8CurrentRRT_Option;

    U8 fEnableSignalCheck;

} StuDtvAtscInfo;

//=======================================================

extern StuDtvAtscInfo g_stDtvAtscInfo;

// todo: rename
//extern MS_U8 fEnableSignalCheck;
#define fEnableSignalCheck  (g_stDtvAtscInfo.fEnableSignalCheck)

#define MENU_LANGUAGE       (((stGenSetting.g_SysSetting.Language == LANGUAGE_ENGLISH) \
                             || (stGenSetting.g_SysSetting.Language == LANGUAGE_FRENCH) \
                             || (stGenSetting.g_SysSetting.Language == LANGUAGE_SPANISH)) ? stGenSetting.g_SysSetting.Language : LANGUAGE_ENGLISH)//current menu language

//=======================================================


void msAPI_DTVSystem_ATSC_Init(void);

BOOLEAN msAPI_DtvATSC_IsValidRfNumber(U8 u8RfNum);


#endif // ENABLE_ATSC

#endif // _MSAPI_DTVSYSTEM_ATSC_H_

