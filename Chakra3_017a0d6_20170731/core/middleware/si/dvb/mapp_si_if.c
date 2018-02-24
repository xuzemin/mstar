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

#define MAPP_SI_IF_C

/******************************************************************************/
/*                       Header Files                                         */
/******************************************************************************/
#include "Board.h"

#if(ENABLE_DTV)// && ENABLE_DVB)

// C Library
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

// Global Layer
#include "datatype.h"
#include "msAPI_Timer.h"
#include "msAPI_Memory.h"
#include "msAPI_MIU.h"
#include "msAPI_DTVSystem.h"
#include "msAPI_audio.h"
#include "apiAUDIO.h"

#if (ENABLE_SBTVD_SI || ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
#include "msAPI_FreqTableDTV.h"
#endif
#include "mapp_demux.h"
#include "mapp_si.h"
#if (ENABLE_DTV_EPG)
#include "mapp_eit.h"
#endif
#include "msAPI_Tuner.h"
#include "msAPI_Global.h"
#include "debug.h"

#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"
// MW Layer
#include "mw_debug.h"
#include "mapp_si_if.h"
#include "MApp_GlobalSettingSt.h"
#include "msAPI_FreqTableDTV.h"
#include "MApp_CharTable.h"
#include "MApp_HuffmanTable.h"
#include "mapp_si_util.h"
#include "msAPI_HuffmanDecode.h"
#if 1//ENABLE_SAVE_MULTILINGUAL_SERVICE_NAME
#include "MApp_GlobalFunction.h"
#endif
#include "MApp_SaveData.h"
#if ENABLE_CI
#include "MApp_CIMMI.h"
#endif
#if ENABLE_S2
#include "MApp_MenuChannel.h"
#endif
#include "msAPI_CI.h"

extern  U16 MApp_EpgUI_Func_Get_CurFocusSrvPos(void);
extern MEMBER_SERVICETYPE MApp_EpgUI_Func_Get_CurFocusSrvType(void);

//SI_MAX_VC_PER_PHYSICAL is used by lib, don't modify it
#if (MAX_VC_PER_PHYSICAL > SI_MAX_VC_PER_PHYSICAL)
#error "MAX_VC_PER_PHYSICAL should be less than SI_MAX_VC_PER_PHYSICAL"
#endif

//SI_MAX_SERVICE_NAME is used by lib, don't modify it
#if (MAX_SERVICE_NAME > SI_MAX_SERVICE_NAME)
#error "only support MAX_SERVICE_NAME => SI_MAX_SERVICE_NAME"
#endif


#define SI_ADD_PROG_ID(x)   //x


#define COUNTRY_CODE_NUM    (sizeof(iso3166_CountryCode)/4)
#define ENABLE_MUTEX 0

#ifndef SAVE_AVPIDINVALID_PROGRAM
#define SAVE_AVPIDINVALID_PROGRAM      0
#endif

static S8 _s8LCDV2Size = -1;
static LOGICAL_CHANNEL_V2 _aLCDV2[LCDV2ArrayMaxSize];
static BOOLEAN _bLCDV2RescanFlag = FALSE;
static U8 _u8ChanListId = 0xFF;
static U8 _u8CountryCode = 0xFF;

#if ENABLE_MUTEX
static MS_S32 _aSI_MUTEX_ID[E_SI_MUTEX_MAX];
#endif

#if(M7_DVBS_FAST_SCAN_ENABLE)
static EN_SATELLITE_PLATFORM _enSatellitePlatform = EN_SATEPF_OTHER;
static BOOLEAN _bM7FastScanFlag = FALSE;
#endif //#if(M7_DVBS_FAST_SCAN_ENABLE)

typedef struct TimeZone2Country
{
    EN_SI_TIMEZONE eTimeZone;
    EN_SI_COUNTRY_SETTING eCountry;
} TimeZone2Country;
typedef struct
{
    U8 au8LangCode[3];
    EN_SI_LANGUAGE enLangIndex;
} ST_ISO639_LANG;
static code TimeZone2Country stTimeZone2Country[]=
{
    {SI_TIMEZONE_CANARY,       SI_COUNTRY_SPAIN},
    {SI_TIMEZONE_LISBON,       SI_COUNTRY_PORTUGAL},
    {SI_TIMEZONE_LONDON,       SI_COUNTRY_UK},
    {SI_TIMEZONE_AMSTERDAM,    SI_COUNTRY_NETHERLANDS},
    {SI_TIMEZONE_BEOGRAD,      SI_COUNTRY_SERBIA},
    {SI_TIMEZONE_BERLIN,       SI_COUNTRY_GERMANY},
    {SI_TIMEZONE_BRUSSELS,     SI_COUNTRY_BELGIUM},
    {SI_TIMEZONE_BUDAPEST,     SI_COUNTRY_HUNGARY},
    {SI_TIMEZONE_COPENHAGEN,   SI_COUNTRY_DENMARK},
    {SI_TIMEZONE_LIUBLJANA,    SI_COUNTRY_SLOVENIA},
    {SI_TIMEZONE_LUXEMBOURG,   SI_COUNTRY_LUXEMBOURG},
    {SI_TIMEZONE_MADRID,       SI_COUNTRY_SPAIN},
    {SI_TIMEZONE_OSLO,         SI_COUNTRY_NORWAY},
    {SI_TIMEZONE_PARIS,        SI_COUNTRY_FRANCE},
    {SI_TIMEZONE_PRAGUE,       SI_COUNTRY_CZECH},
    {SI_TIMEZONE_BERN,         SI_COUNTRY_SWITZERLAND},
    {SI_TIMEZONE_ROME,         SI_COUNTRY_ITALY},
    {SI_TIMEZONE_LONDON,       SI_COUNTRY_IRELAND},
    {SI_TIMEZONE_STOCKHOLM,    SI_COUNTRY_SWEDEN},
    {SI_TIMEZONE_WARSAW,       SI_COUNTRY_POLAND},
    {SI_TIMEZONE_VIENNA,       SI_COUNTRY_AUSTRIA},
    {SI_TIMEZONE_ZAGREB,       SI_COUNTRY_CROATIA},
    {SI_TIMEZONE_ATHENS,       SI_COUNTRY_GREECE},
    {SI_TIMEZONE_BUCURESTI,    SI_COUNTRY_ROMANIA},
    {SI_TIMEZONE_HELSINKI,     SI_COUNTRY_FINLAND},
    {SI_TIMEZONE_SOFIA,        SI_COUNTRY_BULGARIA},
    {SI_TIMEZONE_MOSCOW,       SI_COUNTRY_RUSSIA},
    {SI_TIMEZONE_WA,           SI_COUNTRY_AUSTRALIA},
    {SI_TIMEZONE_SA,           SI_COUNTRY_AUSTRALIA},
    {SI_TIMEZONE_NT,           SI_COUNTRY_AUSTRALIA},
    {SI_TIMEZONE_NSW,          SI_COUNTRY_AUSTRALIA},
    {SI_TIMEZONE_VIC,          SI_COUNTRY_AUSTRALIA},
    {SI_TIMEZONE_QLD,          SI_COUNTRY_AUSTRALIA},
    {SI_TIMEZONE_TAS,          SI_COUNTRY_AUSTRALIA},
    {SI_TIMEZONE_NZST,         SI_COUNTRY_NEWZEALAND},
    {SI_TIMEZONE_AM_WEST,      SI_COUNTRY_BRAZIL},
    {SI_TIMEZONE_ACRE,         SI_COUNTRY_BRAZIL},
    {SI_TIMEZONE_M_GROSSO,     SI_COUNTRY_BRAZIL},
    {SI_TIMEZONE_NORTH,        SI_COUNTRY_BRAZIL},
    {SI_TIMEZONE_BRASILIA,     SI_COUNTRY_BRAZIL},
    {SI_TIMEZONE_NORTHEAST,    SI_COUNTRY_BRAZIL},
    {SI_TIMEZONE_F_NORONHA,    SI_COUNTRY_BRAZIL},
    {SI_TIMEZONE_BEIJING,      SI_COUNTRY_CHINA},
    {SI_TIMEZONE_RABAT,        SI_COUNTRY_MOROCCO},
    {SI_TIMEZONE_TUNIS,        SI_COUNTRY_TUNIS},
    {SI_TIMEZONE_ALGIERS,      SI_COUNTRY_ALGERIA},
    {SI_TIMEZONE_CAIRO,        SI_COUNTRY_EGYPT},
    {SI_TIMEZONE_CAPE_TOWN,    SI_COUNTRY_SOUTH_AFRICA},
    {SI_TIMEZONE_JERUSSLEM,    SI_COUNTRY_ISRAEL},
    {SI_TIMEZONE_TEHERAN,      SI_COUNTRY_IRAN},
    {SI_TIMEZONE_ABU_DHABI,    SI_COUNTRY_UNITED_ARAB_EMIRATES},
    {SI_TIMEZONE_KUWAIT,       SI_COUNTRY_KUWAIT},
    {SI_TIMEZONE_MUSCAT,       SI_COUNTRY_OMAN},
    {SI_TIMEZONE_DOHA,         SI_COUNTRY_QATAR},
    {SI_TIMEZONE_RIYADH,       SI_COUNTRY_SAUDI_ARABIA},
    {SI_TIMEZONE_MANAMA,       SI_COUNTRY_BAHRAIN},
    {SI_TIMEZONE_AZORES,       SI_COUNTRY_PORTUGAL},
    {SI_TIMEZONE_DUBLIN,       SI_COUNTRY_IRELAND},
    {SI_TIMEZONE_TURKEY,       SI_COUNTRY_TURKEY},
    {SI_TIMEZONE_THAILAND,     SI_COUNTRY_THAILAND},
    {SI_TIMEZONE_KUALA_LUMPUR,       SI_COUNTRY_MALAYSIA},
    {SI_TIMEZONE_INDONESIA_WEST, SI_COUNTRY_INDONESIA},
    {SI_TIMEZONE_SINGAPORE, SI_COUNTRY_SINGAPORE},
    {SI_TIMEZONE_VIETNAM,           SI_COUNTRY_VIETNAM},
    {SI_TIMEZONE_KENYA,             SI_COUNTRY_KENYA},
    {SI_TIMEZONE_MYANMAR,             SI_COUNTRY_MYANMAR},
    {SI_TIMEZONE_UKRAINE,             SI_COUNTRY_UKRAINE},
};

// array of iso 639 language code
static code ST_ISO639_LANG iso639_LanguageCode[] =
{
    {{'e','n','g'}, SI_LANGUAGE_ENGLISH},
    {{'f','r','a'}, SI_LANGUAGE_FRENCH},
    {{'f','r','e'}, SI_LANGUAGE_FRENCH},
    {{'g','e','r'}, SI_LANGUAGE_GERMAN},
    {{'d','e','u'}, SI_LANGUAGE_GERMAN},
    {{'i','t','a'}, SI_LANGUAGE_ITALIAN},
    {{'i','r','i'}, SI_LANGUAGE_IRELAND},
    {{'s','p','a'}, SI_LANGUAGE_SPANISH},
    {{'e','s','l'}, SI_LANGUAGE_SPANISH},
    {{'s','w','e'}, SI_LANGUAGE_SWEDISH},
    {{'f','i','n'}, SI_LANGUAGE_FINNISH},
    {{'p','o','r'}, SI_LANGUAGE_PORTUGUESE},
    {{'t','u','r'}, SI_LANGUAGE_TURKISH},
    {{'c','z','e'}, SI_LANGUAGE_CZECH},
    {{'c','e','s'}, SI_LANGUAGE_CZECH},
    {{'d','a','n'}, SI_LANGUAGE_DANISH},
    {{'d','u','t'}, SI_LANGUAGE_DUTCH},
    {{'n','l','d'}, SI_LANGUAGE_DUTCH},
    {{'p','o','l'}, SI_LANGUAGE_POLISH},
    {{'g','r','e'}, SI_LANGUAGE_GREEK},
    {{'e','l','l'}, SI_LANGUAGE_GREEK},
    {{'h','u','n'}, SI_LANGUAGE_HUNGARIAN},
    {{'n','o','r'}, SI_LANGUAGE_NORWEGIAN},
    {{'r','u','m'}, SI_LANGUAGE_ROMANIAN},
    {{'r','o','m'}, SI_LANGUAGE_ROMANIAN},
    {{'r','o','n'}, SI_LANGUAGE_ROMANIAN},
    {{'r','u','s'}, SI_LANGUAGE_RUSSIAN},
    {{'a','r','a'}, SI_LANGUAGE_ARABIC},
    {{'h','e','b'}, SI_LANGUAGE_HEBREW},
    {{'q','a','a'}, SI_LANGUAGE_QAA},   /* qaa :: Original Sound Track A*/
    {{'q','a','b'}, SI_LANGUAGE_QAB},   /* qab :: Original Sound Track B*/
    {{'q','a','c'}, SI_LANGUAGE_QAC},   /* qac :: Original Sound Track C*/
    {{'s','c','c'}, SI_LANGUAGE_SERBIAN},
    {{'s','r','p'}, SI_LANGUAGE_SERBIAN},
    {{'s','l','v'}, SI_LANGUAGE_SLOVENIAN},
    {{'s','c','r'}, SI_LANGUAGE_CROATIAN},
    {{'h','r','v'}, SI_LANGUAGE_CROATIAN},
    {{'b','u','l'}, SI_LANGUAGE_BULGARIAN},
    {{'w','e','l'}, SI_LANGUAGE_WELSH},
    {{'c','y','m'}, SI_LANGUAGE_WELSH},
    {{'g','l','a'}, SI_LANGUAGE_GAELIC},
    {{'g','a','e'}, SI_LANGUAGE_GAELIC},
    {{'g','d','h'}, SI_LANGUAGE_GAELIC},
    {{'a','k','a'}, SI_LANGUAGE_AKAN},
    {{'e','w','e'}, SI_LANGUAGE_EWE},
    {{'t','w','i'}, SI_LANGUAGE_TWI},
    {{'n','z','i'}, SI_LANGUAGE_NZEMA},
    {{'h','a','u'}, SI_LANGUAGE_HAUSA},
    {{'x','s','m'}, SI_LANGUAGE_KASEM},
    {{'g','l','e'}, SI_LANGUAGE_IRISH},
    {{'k','o','r'}, SI_LANGUAGE_KOREAN},
    {{'j','p','n'}, SI_LANGUAGE_JAPAN},
    {{'c','h','s'}, SI_LANGUAGE_CHINESE},
#if ( ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP || ENABLE_DVB_TAIWAN_APP || CHINESE_BIG5_FONT_ENABLE )
    {{'z','h','o'}, SI_LANGUAGE_CHINESE_TRAD},
    {{'c','h','i'}, SI_LANGUAGE_CHINESE_TRAD},
#else
    {{'z','h','o'}, SI_LANGUAGE_CHINESE},
    {{'c','h','i'}, SI_LANGUAGE_CHINESE},
#endif
    {{'c','m','n'}, SI_LANGUAGE_MANDARIN},
    {{'y','u','e'}, SI_LANGUAGE_CANTONESE},
    {{'g','l','g'}, SI_LANGUAGE_GALLEGAN},
    {{'b','a','q'}, SI_LANGUAGE_BASQUE},
    {{'e','u','s'}, SI_LANGUAGE_BASQUE},
    {{'l','t','z'}, SI_LANGUAGE_LUXEMBOURGISH},
    {{'i','c','e'}, SI_LANGUAGE_ICELANDIC},
    {{'i','s','l'}, SI_LANGUAGE_ICELANDIC},
    {{'l','a','v'}, SI_LANGUAGE_LATVIAN},
    {{'e','s','t'}, SI_LANGUAGE_ESTONIAN},
    {{'l','i','t'}, SI_LANGUAGE_LITHUANIAN},
    {{'u','k','r'}, SI_LANGUAGE_UKRANIAN},
    {{'b','e','l'}, SI_LANGUAGE_BELARUSIAN},
    {{'s','m','i'}, SI_LANGUAGE_SAMI},
    {{'h','i','n'}, SI_LANGUAGE_HINDI},
    {{'u','n','d'}, SI_LANGUAGE_UND},
    {{'m','a','o'}, SI_LANGUAGE_MAORI},
    {{'i','n','d'}, SI_LANGUAGE_INDONESIA},
    {{'s','l','o'}, SI_LANGUAGE_SLOVAK},
    {{'s','l','k'}, SI_LANGUAGE_SLOVAK},
    {{'c','a','t'}, SI_LANGUAGE_SPANISH_CAT},
    {{'v','.','o'}, SI_LANGUAGE_SPANISH_V_O},
    {{'a','d'},     SI_LANGUAGE_SPANISH_AD},
    {{'v','o'},     SI_LANGUAGE_SPANISH_VO},
    {{'a','c','3'}, SI_LANGUAGE_SPANISH_AC3},
    {{'t','h','a'}, SI_LANGUAGE_THAILAND},
    {{'n','a','r'}, SI_LANGUAGE_BROADCAST_MIX},
    {{'q','a','d'}, SI_LANGUAGE_BROADCAST_MIX},
    {{'s','g','a'}, SI_LANGUAGE_SGA},
    {{'t','a','m'}, SI_LANGUAGE_TAMIL},
    {{'m','s','a'}, SI_LANGUAGE_MALAYSIA},
    {{'v','i','e'}, SI_LANGUAGE_VIETNAM},
    {{'s','w','a'}, SI_LANGUAGE_SWAHILI},
    {{'m','y','a'}, SI_LANGUAGE_MYANMAR},
    {{'b','u','r'}, SI_LANGUAGE_MYANMAR},
    {{'u','k','r'}, SI_LANGUAGE_UKRAINIAN},
};

static code U8 iso3166_CountryCode[][4]=
{
    {'A','U','S',SI_COUNTRY_AUSTRALIA},    //Australia
    {'A','U','T',SI_COUNTRY_AUSTRIA},      //Austria
    {'B','E','L',SI_COUNTRY_BELGIUM},      //Belgium
    {'B','G','R',SI_COUNTRY_BULGARIA},     //Bulgaria
    {'H','R','V',SI_COUNTRY_CROATIA},      //Croatia
    {'C','Z','E',SI_COUNTRY_CZECH},        //Czech
    {'D','N','K',SI_COUNTRY_DENMARK},      //Denmark
    {'F','I','N',SI_COUNTRY_FINLAND},      //Finland
    {'F','R','A',SI_COUNTRY_FRANCE},       //France
    {'D','E','U',SI_COUNTRY_GERMANY},      //Germany
    {'G','R','C',SI_COUNTRY_GREECE},       //Greece
    {'H','U','N',SI_COUNTRY_HUNGARY},       //Hungary
    {'I','T','A',SI_COUNTRY_ITALY},        //Italy
    {'I','R','L',SI_COUNTRY_IRELAND},        //Italy
    {'L','U','X',SI_COUNTRY_LUXEMBOURG},   //Luxembourg
    {'N','L','D',SI_COUNTRY_NETHERLANDS},  //Netherlands
    {'N','O','R',SI_COUNTRY_NORWAY},       //Norway
    {'P','O','L',SI_COUNTRY_POLAND},       //Poland
    {'P','R','T',SI_COUNTRY_PORTUGAL},     //Portugal
    {'R','O','M',SI_COUNTRY_ROMANIA},   //Rumania
    {'R','U','M',SI_COUNTRY_ROMANIA},   //Rumania
    {'R','O','U',SI_COUNTRY_ROMANIA},   //Rumania
    {'R','U','S',SI_COUNTRY_RUSSIA},      //Russian
    {'S','C','G',SI_COUNTRY_SERBIA},       //Serbia
    {'S','V','N',SI_COUNTRY_SLOVENIA},     //Slovenia
    {'E','S','P',SI_COUNTRY_SPAIN},        //Spain
    {'S','W','E',SI_COUNTRY_SWEDEN},       //Sweden
    {'C','H','E',SI_COUNTRY_SWITZERLAND},  //Switzerland
    {'G','B','R',SI_COUNTRY_UK},           //UK
    {'N','Z','L',SI_COUNTRY_NEWZEALAND},//NewZealand
    {'C','H','N',SI_COUNTRY_CHINA}, //china
    {'E','S','T',SI_COUNTRY_ESTONIA}, //estonia
    {'T','U','R',SI_COUNTRY_TURKEY}, //turkey
    {'M','A','R',SI_COUNTRY_MOROCCO},
    {'T','U','N',SI_COUNTRY_TUNIS}, //TUNISIA
    {'D','Z','A',SI_COUNTRY_ALGERIA}, //ALGERIA
    {'E','G','Y',SI_COUNTRY_EGYPT}, //EGYPT
    {'Z','A','F',SI_COUNTRY_SOUTH_AFRICA}, //SOUTH AFRICA
    {'I','S','R',SI_COUNTRY_ISRAEL}, //israel
    {'I','R','N',SI_COUNTRY_IRAN},  //iran
    {'K','W','T',SI_COUNTRY_KUWAIT},  //kuwait
    {'O','M','N',SI_COUNTRY_OMAN},  //oman
    {'Q','A','T',SI_COUNTRY_QATAR},  //Qatar
    {'S','A','U',SI_COUNTRY_SAUDI_ARABIA},  //saudi arabia
    {'B','H','R',SI_COUNTRY_BAHRAIN},  //bahrain
    {'A','R','E',SI_COUNTRY_UNITED_ARAB_EMIRATES},  //UNITED ARAB EMIRATES
    {'S','V','K',SI_COUNTRY_SLOVAKIA},  //SLOVAKIA
    {'T','W','N',SI_COUNTRY_TAIWAN},    //taiwan
    {'B','R','A',SI_COUNTRY_BRAZIL},           //Brazil
    {'I','D','N',SI_COUNTRY_INDONESIA},        //Indonesia
    {'M','Y','S',SI_COUNTRY_MALAYSIA},  //Malaysia
    {'S','G','P',SI_COUNTRY_SINGAPORE},  //Singapore
    {'V','N','M',SI_COUNTRY_VIETNAM},  //Vietnam
    {'K','E','N',SI_COUNTRY_KENYA},  //Kenya
    {'G','H','A',SI_COUNTRY_GHANA},     //Ghana
    {'U','K','R',SI_COUNTRY_UKRAINE}, //
    {'M','M','R',SI_COUNTRY_MYANMAR}
};

U32 msAPI_SI_DecodeStr(const U8    *pbufEncStr,    /* compressed string */
                    U32        nLenStr,        /* the number of bytes in compressed string    */
                    U8        nEncodeType,    /* compression type */
                    U8        *pbufDecStr,    /* decompressed string */
                    U32        nMaxBufDecStr)    /* decompressed string length */
{
#if (BLOADER)
    UNUSED(pbufEncStr);
    UNUSED(nLenStr);
    UNUSED(nEncodeType);
    UNUSED(pbufDecStr);
    UNUSED(nMaxBufDecStr);
    return 0;
#else
#ifdef USED_HUFFMAN_TABLE
    msAPI_HUFFMAN_Init(_HuffmanDecodeTbl, _HuffmanDecodeTb2);
#endif
    return msAPI_DecodeStr(pbufEncStr, nLenStr, nEncodeType, pbufDecStr, nMaxBufDecStr);
#endif
}

U32 msAPI_SI_HuffmanDecode(const U8    *pbufEncStr,    /* compressed string */
                    U32        nLenStr,        /* the number of bytes in compressed string    */
                    U8        nEncodeType,    /* compression type */
                    U8        *pbufDecStr,    /* decompressed string */
                    U32        nMaxBufDecStr)    /* decompressed string length */
{
#if (BLOADER)
    UNUSED(pbufEncStr);
    UNUSED(nLenStr);
    UNUSED(nEncodeType);
    UNUSED(pbufDecStr);
    UNUSED(nMaxBufDecStr);
    return 0;
#else

    return msAPI_HuffmanDecode(pbufEncStr, nLenStr, nEncodeType, pbufDecStr, nMaxBufDecStr);
#endif
}

MEMBER_SI_SERVICETYPE msAPI_SI_GetCurrentServiceType(void)
{
    MEMBER_SERVICETYPE bServiceType;
    bServiceType=msAPI_CM_GetCurrentServiceType();
    switch(bServiceType)
    {

        case E_SERVICETYPE_RADIO: return E_TYPE_RADIO;
        case E_SERVICETYPE_DATA: return E_TYPE_DATA;
        default:
            MS_DEBUG_MSG(printf("msAPI_SI_GetCurrentServiceType unsupport service type %x\n",bServiceType));
            return E_TYPE_DTV;
        case E_SERVICETYPE_DTV: return E_TYPE_DTV;
    }
}

U16 msAPI_SI_GetCurrentPosition(MEMBER_SI_SERVICETYPE bServiceType)
{
    MEMBER_SERVICETYPE bType;
    bType=msAPI_SI_ToCM_Service_Type(bServiceType);

    return msAPI_CM_GetCurrentPosition(bType);
}

U8 msAPI_SI_GetPhysicalChannelNumber(MEMBER_SI_SERVICETYPE bServiceType, U16 wPosition)
{
    MEMBER_SERVICETYPE bType;
    bType=msAPI_SI_ToCM_Service_Type(bServiceType);
    return msAPI_CM_GetPhysicalChannelNumber(bType,wPosition);
}

#if (ENABLE_S2)
U8 msAPI_SI_GetPhysicalsat(MEMBER_SI_SERVICETYPE bServiceType, U16 wPosition)
{
    MEMBER_SERVICETYPE bType;
    bType=msAPI_SI_ToCM_Service_Type(bServiceType);
    return msAPI_CM_GetPhysicalsat(bType,wPosition);
}
U16 msAPI_SI_GetPhysicalfreq(MEMBER_SI_SERVICETYPE bServiceType, U16 wPosition)
{
    MEMBER_SERVICETYPE bType;
    bType=msAPI_SI_ToCM_Service_Type(bServiceType);
    return msAPI_CM_GetPhysicalfreq(bType,wPosition);
}
#endif

U16 msAPI_SI_GetService_ID(MEMBER_SI_SERVICETYPE bServiceType, U16 wPosition)
{
    MEMBER_SERVICETYPE bType;
    bType=msAPI_SI_ToCM_Service_Type(bServiceType);
    return msAPI_CM_GetService_ID(bType,wPosition);
}

U16 msAPI_SI_GetCurrentService_ID(void)
{
    MEMBER_SERVICETYPE bServiceType;
    bServiceType = msAPI_CM_GetCurrentServiceType();
    return msAPI_CM_GetService_ID(bServiceType,msAPI_CM_GetCurrentPosition(bServiceType));
}

U16 msAPI_SI_GetPmtPID(MEMBER_SI_SERVICETYPE bServiceType, U16 wPosition)
{
    MEMBER_SERVICETYPE bType;
    bType=msAPI_SI_ToCM_Service_Type(bServiceType);
    return msAPI_CM_GetPmtPID(bType,wPosition);
}

U8 msAPI_SI_GetPSISIVersion(MEMBER_SI_SERVICETYPE bServiceType, U16 wPosition, E_PSI_SI_VERSION eVersionMember)
{
    MEMBER_SERVICETYPE bType;
    E_MEMBER_PSI_SI_VERSION bVerMember;
    bType=msAPI_SI_ToCM_Service_Type(bServiceType);
    switch(eVersionMember)
    {

        case E_VER_PMT:
            bVerMember = E_VERSION_PMT;
            break;
        case E_VER_PAT:
            bVerMember = E_VERSION_PAT;
            break;
        case E_VER_SDT:
            bVerMember = E_VERSION_SDT;
            break;
        default:
        case E_VER_NIT:
            bVerMember = E_VERSION_NIT;
            break;
    }
    return msAPI_CM_GetPSISIVersion(bType,wPosition,bVerMember);
}

U16 msAPI_SI_GetTS_ID(MEMBER_SI_SERVICETYPE bServiceType, U16 wPosition)
{
    MEMBER_SERVICETYPE bType;
    bType=msAPI_SI_ToCM_Service_Type(bServiceType);
    return msAPI_CM_GetTS_ID(bType,wPosition);
}

U16 msAPI_SI_GetON_ID(MEMBER_SI_SERVICETYPE bServiceType, U16 wPosition)
{
    MEMBER_SERVICETYPE bType;
    bType=msAPI_SI_ToCM_Service_Type(bServiceType);
    return msAPI_CM_GetON_ID(bType,wPosition);
}

U16 msAPI_SI_GetLogicalChannelNumber(MEMBER_SI_SERVICETYPE bServiceType, U16 wPosition)
{
    MEMBER_SERVICETYPE bType;
    bType=msAPI_SI_ToCM_Service_Type(bServiceType);
    return msAPI_CM_GetLogicalChannelNumber(bType,wPosition);
}

U16 msAPI_SI_GetOriginalLogicalChannelNumber(MEMBER_SI_SERVICETYPE bServiceType, U16 wPosition)
{
    MEMBER_SERVICETYPE bType;
    bType=msAPI_SI_ToCM_Service_Type(bServiceType);
    return msAPI_CM_GetOriginalLogicalChannelNumber(bType,wPosition);
}

BOOLEAN msAPI_SI_IsLogicalChannelNumberExist(MEMBER_SI_SERVICETYPE bServiceType, U16 wLCN, U16* pPosition)
{
    MEMBER_SERVICETYPE bType;

    bType=msAPI_SI_ToCM_Service_Type(bServiceType);
    return msAPI_CM_IsLCNExit(bType,wLCN,pPosition);
}

BOOLEAN msAPI_SI_GetServiceByLogicalChannelNumber(MEMBER_SI_SERVICETYPE bServiceType, U16 wLCN, WORD *pWPosition)
{
    MEMBER_SERVICETYPE bType;
    bType=msAPI_SI_ToCM_Service_Type(bServiceType);
    return msAPI_CM_IsLCNExit(bType,wLCN,pWPosition);
}

WORD msAPI_SI_GetSimuLogicalChannelNumber(MEMBER_SI_SERVICETYPE bServiceType, WORD wPosition)
{
    MEMBER_SERVICETYPE bType;
    bType=msAPI_SI_ToCM_Service_Type(bServiceType);
    return msAPI_CM_GetSimuLogicalChannelNumber(bType,wPosition);
}

BOOLEAN msAPI_SI_RecoveryDelProgram(MEMBER_SI_SERVICETYPE bServiceType, WORD wPosition)
{
    MEMBER_SERVICETYPE bType;
    bType=msAPI_SI_ToCM_Service_Type(bServiceType);
    return msAPI_CM_RecoveryDelProgram(bType,wPosition);
}

BOOLEAN msAPI_SI_DeleteProgram(MEMBER_SI_SERVICETYPE bServiceType, WORD wPosition)
{
    MEMBER_SERVICETYPE bType;
    bType=msAPI_SI_ToCM_Service_Type(bServiceType);
    return msAPI_CM_DeleteProgram(bType,wPosition, TRUE);
}

BOOLEAN msAPI_SI_ReplaceDelProgram(MEMBER_SI_SERVICETYPE bServiceType, WORD wPosition, BOOLEAN bDel)
{
    MEMBER_SERVICETYPE bType;
    bType=msAPI_SI_ToCM_Service_Type(bServiceType);
    return msAPI_CM_ReplaceDelProgram(bType,wPosition,bDel);
}

BOOLEAN msAPI_SI_SetCurrentServiceType(MEMBER_SI_SERVICETYPE bServiceType)
{
    MEMBER_SERVICETYPE bType;
    bType=msAPI_SI_ToCM_Service_Type(bServiceType);
    return msAPI_CM_SetCurrentServiceType(bType);
}

BOOLEAN msAPI_SI_SetCurrentPosition(MEMBER_SI_SERVICETYPE bServiceType, WORD wPosition)
{
    MEMBER_SERVICETYPE bType;
    bType=msAPI_SI_ToCM_Service_Type(bServiceType);
    return msAPI_CM_SetCurrentPosition(bType,wPosition);
}

BOOLEAN msAPI_SI_GetProgramAttribute(MEMBER_SI_SERVICETYPE bServiceType, WORD wPosition, E_SI_MEMBER_CHANNEL_ATTRIBUTE eAttributeMember)
{
    MEMBER_SERVICETYPE bType;
    bType=msAPI_SI_ToCM_Service_Type(bServiceType);
    switch(eAttributeMember)
    {
        case E_SI_ATTRIBUTE_IS_SCRAMBLED: return msAPI_CM_GetProgramAttribute(bType,wPosition,E_ATTRIBUTE_IS_SCRAMBLED);
        case E_SI_ATTRIBUTE_IS_STILL_PICTURE: return msAPI_CM_GetProgramAttribute(bType,wPosition,E_ATTRIBUTE_IS_STILL_PICTURE);
        case E_SI_ATTRIBUTE_IS_VISIBLE: return msAPI_CM_GetProgramAttribute(bType,wPosition,E_ATTRIBUTE_IS_VISIBLE);
        case E_SI_ATTRIBUTE_IS_NUMERIC_SELECTION: return msAPI_CM_GetProgramAttribute(bType,wPosition,E_ATTRIBUTE_IS_NUMERIC_SELECTION);
        case E_SI_ATTRIBUTE_IS_SKIPPED: return msAPI_CM_GetProgramAttribute(bType,wPosition,E_ATTRIBUTE_IS_SKIPPED);
        case E_SI_ATTRIBUTE_IS_LOCKED: return msAPI_CM_GetProgramAttribute(bType,wPosition,E_ATTRIBUTE_IS_LOCKED);
        case E_SI_ATTRIBUTE_IS_REPLACE_SERVICE: return msAPI_CM_GetProgramAttribute(bType,wPosition,E_ATTRIBUTE_IS_REPLACE_SERVICE);
        case E_SI_ATTRIBUTE_IS_SERVICE_ID_ONLY: return msAPI_CM_GetProgramAttribute(bType,wPosition,E_ATTRIBUTE_IS_SERVICE_ID_ONLY);
        case E_SI_ATTRIBUTE_IS_DELETED: return msAPI_CM_GetProgramAttribute(bType,wPosition,E_ATTRIBUTE_IS_DELETED);
        case E_SI_ATTRIBUTE_IS_REPLACE_DEL: return msAPI_CM_GetProgramAttribute(bType,wPosition,E_ATTRIBUTE_IS_REPLACE_DEL);
        case E_SI_ATTRIBUTE_IS_MOVED: return msAPI_CM_GetProgramAttribute(bType,wPosition,E_ATTRIBUTE_IS_MOVED);
        case E_SI_ATTRIBUTE_IS_UNCONFIRMED_SERVICE: return msAPI_CM_GetProgramAttribute(bType,wPosition,E_ATTRIBUTE_IS_UNCONFIRMED_SERVICE);
    #if 0//(ENABLE_S2_CHANNEL_FAV_NEWSTYLE)
        case E_SI_ATTRIBUTE_IS_FAVORITE: return (msAPI_CM_GetProgramAttribute(bType,wPosition,E_ATTRIBUTE_IS_FAVORITE1)
    #else
        case E_SI_ATTRIBUTE_IS_FAVORITE: return msAPI_CM_GetProgramAttribute(bType,wPosition,E_ATTRIBUTE_IS_FAVORITE);
    #endif
#if(ASTRA_HD_ENABLE)
        case E_SI_ATTRIBUTE_IS_NEW_SERVICE: return msAPI_CM_GetProgramAttribute(bType,wPosition,E_ATTRIBUTE_IS_NEW_SERVICE);
#endif
        default:return FALSE;
    }
}

U16 msAPI_SI_GetNetwork_ID(MEMBER_SI_SERVICETYPE bServiceType, U16 wPosition)
{
    MEMBER_SERVICETYPE bType;
    bType=msAPI_SI_ToCM_Service_Type(bServiceType);
    return msAPI_CM_GetNetwork_ID(bType,wPosition);
}

BOOLEAN msAPI_SI_Get_PHYSICAL_CHANNEL_NUMBER(U32 u32Frequency, U8 *u8RFIndex)
{
    return msAPI_DFT_Get_PHYSICAL_CHANNEL_NUMBER(u32Frequency,u8RFIndex);
}

U8 msAPI_SI_GetPhysicalChannelNumberByID(WORD wONID, WORD wTSID)
{
#if ENABLE_SDT_OTHER_MONITOR
    return msAPI_CM_GetPhysicalChannelNumberByID(wONID,wTSID);
#else
    wONID=wONID;
    wTSID=wTSID;
    return 0xFF;
#endif
}

BOOLEAN msAPI_SI_GetCEllID_WithID(WORD wTS_ID, WORD wON_ID, WORD *pwCell_ID, BOOLEAN *bOverOneCell)
{
#if ENABLE_SDT_OTHER_MONITOR
    return msAPI_CM_GetCEllID_WithID(wTS_ID, wON_ID, pwCell_ID, bOverOneCell);
#else
    wTS_ID=wTS_ID;
    wON_ID=wON_ID;
    pwCell_ID=pwCell_ID;
    bOverOneCell=bOverOneCell;
    return FALSE;
#endif
}

BOOLEAN msAPI_SI_GetPLP_ID_WithID(WORD wTS_ID, WORD wON_ID, U8 *pu8PLP_ID)
{
#if (ENABLE_SDT_OTHER_MONITOR && ENABLE_DVB_T2)
    return msAPI_CM_GetPLPID_WithID(wTS_ID, wON_ID, pu8PLP_ID);
#else

    UNUSED(wTS_ID);
    UNUSED(wON_ID);

    *pu8PLP_ID=0;

    return FALSE;
#endif
}

BOOLEAN msAPI_SI_GetHpLp_WithID(WORD wTS_ID, WORD wON_ID, U8 *pu8HpLp)
{
#if (ENABLE_SDT_OTHER_MONITOR && ENABLE_HIERARCHY)
    return msAPI_CM_GetHpLP_WithID(wTS_ID, wON_ID, pu8HpLp);
#else
    wTS_ID=wTS_ID;
    wON_ID=wON_ID;
    *pu8HpLp=0;
    return FALSE;
#endif
}
BOOLEAN msAPI_SI_GetCellIDByPosition(MEMBER_SI_SERVICETYPE bServiceType, U16 wPosition, U16* pCellID)
{
#if ENABLE_SDT_OTHER_MONITOR
    MEMBER_SERVICETYPE bType;
    bType=msAPI_SI_ToCM_Service_Type(bServiceType);
    return msAPI_CM_GetCellIDByPosition(bType,wPosition,pCellID);
#else
    bServiceType=bServiceType;
    wPosition=wPosition;
    pCellID=pCellID;
    return FALSE;
#endif
}
BOOLEAN msAPI_SI_Is_TSExist(WORD wONID, WORD wTSID, BYTE *pcRFChannelNumber)
{
#if ENABLE_SDT_OTHER_MONITOR
    return msAPI_CM_Is_TSExist( wONID, wTSID, pcRFChannelNumber);
#else
    wONID=wONID;
    wTSID=wTSID;
    pcRFChannelNumber=pcRFChannelNumber;
    return FALSE;
#endif
}

#if ENABLE_DVBC
U8 msAPI_SI_RemoveQuickInstallMismatchedProgram(SI_SHORT_DTV_CHANNEL_INFO *pastVirtualCh,U8 u8NumOfVch,BYTE bIDIndex, MEMBER_SI_SERVICETYPE eServiceType)
{
    WORD *wServiceID=NULL;//[SI_MAX_VC_PER_PHYSICAL];
    MEMBER_SERVICETYPE type;
    U8 u8i;
    U8 u8Result=0;
    wServiceID=(WORD*)msAPI_Memory_Allocate(sizeof(WORD)*SI_MAX_VC_PER_PHYSICAL, BUF_ID_SI_REMOVE_QUICK_PROG);
    if(wServiceID)
    {
        type = msAPI_SI_ToCM_Service_Type(eServiceType);
        for(u8i=0;u8i<u8NumOfVch;u8i++)
        {
            wServiceID[u8i] = pastVirtualCh[u8i].wService_ID;
        }
        u8Result=msAPI_CM_RemoveQuickInstallMismatchedProgram(wServiceID, u8NumOfVch, bIDIndex, type);
    }
    else
    {
        ASSERT(0);
    }
    if(wServiceID)msAPI_Memory_Free(wServiceID, BUF_ID_SI_REMOVE_QUICK_PROG);
    return u8Result;
}
#endif

#if 1//(ENABLE_S2_FAST_SCAN)
U8 msAPI_SI_RemoveMismatchedProgram(BYTE cRFChannelNumber, U16 wTS_ID, U8 u8PLP_ID,U8 u8HpLp,  U16 *pwService_ID, MEMBER_SI_SERVICETYPE *peService_Type, WORD cCountOfServiceID)
#else
U8 msAPI_SI_RemoveMismatchedProgram(BYTE cRFChannelNumber, U16 wTS_ID, U8 u8PLP_ID,U8 u8HpLp,  U16 *pwService_ID, MEMBER_SI_SERVICETYPE *peService_Type, BYTE cCountOfServiceID)
#endif //#if(ENABLE_S2_FAST_SCAN)
{
#if(ENABLE_DVB||ENABLE_ISDBT)
    int i;
    MEMBER_SERVICETYPE *aeServiceType=NULL;//[SI_MAX_VC_PER_PHYSICAL];;
    U8 result=0;

#if 1//(ENABLE_S2)
    BYTE currentsat = 0;
    WORD currentfreq = 0;
#endif

#if(ENABLE_S2)
    if( IsS2InUse() )
    {
        MEMBER_SI_SERVICETYPE bServiceType = msAPI_SI_GetCurrentServiceType();
        WORD wPosition = msAPI_SI_GetCurrentPosition(bServiceType);

        currentsat = msAPI_SI_GetPhysicalsat( bServiceType, wPosition);
        currentfreq = msAPI_SI_GetPhysicalfreq( bServiceType,wPosition);
    }
#endif

#if (ENABLE_S2_FAST_SCAN)
    if(_bM7FastScanFlag)
    {
        aeServiceType=(MEMBER_SERVICETYPE*)msAPI_Memory_Allocate(sizeof(MEMBER_SERVICETYPE)*MAX_DTV_S2_PROGRAM,(EN_BUFFER_ID)0);
    }
    else
#endif //#if (ENABLE_S2_FAST_SCAN)
    {
    aeServiceType = (MEMBER_SERVICETYPE*)msAPI_Memory_Allocate(sizeof(MEMBER_SERVICETYPE)*SI_MAX_VC_PER_PHYSICAL, BUF_ID_SI_REMOVE_PROG);
    }
    if(aeServiceType)
    {
        for(i=0;i<cCountOfServiceID;i++)
        {
            aeServiceType[i] = msAPI_SI_ToCM_Service_Type(peService_Type[i]);
        }
        msAPI_CM_Set_TS_Update(TRUE,wTS_ID);

    #if 1//(ENABLE_S2)
        #ifdef ENABLE_DELETE_PROGRAM_CONTROL
        result = msAPI_CM_HaveRemoveProgram(cRFChannelNumber,wTS_ID,u8PLP_ID, u8HpLp, pwService_ID, aeServiceType, cCountOfServiceID,currentsat,currentfreq);
        #else
        result=msAPI_CM_RemoveMismatchedProgram(cRFChannelNumber, wTS_ID,u8PLP_ID, u8HpLp, pwService_ID, aeServiceType, cCountOfServiceID,currentsat,currentfreq);
        #endif
    #else
        #ifdef ENABLE_DELETE_PROGRAM_CONTROL
        result = msAPI_CM_HaveRemoveProgram(cRFChannelNumber,wTS_ID,u8PLP_ID, u8HpLp, pwService_ID, aeServiceType, cCountOfServiceID,currentsat,currentfreq);
        #else
        result=msAPI_CM_RemoveMismatchedProgram(cRFChannelNumber, wTS_ID, u8PLP_ID, u8HpLp, pwService_ID, aeServiceType, cCountOfServiceID);
        #endif
    #endif

        msAPI_CM_Set_TS_Update(FALSE,wTS_ID);
    }
    else
    {
        ASSERT(0);
    }

    if(aeServiceType)   msAPI_Memory_Free(aeServiceType, BUF_ID_SI_REMOVE_PROG);

    return result;
#else

    UNUSED(cRFChannelNumber);
    UNUSED(wTS_ID);
    UNUSED(u8PLP_ID);
    UNUSED(u8HpLp);
    UNUSED(pwService_ID);
    UNUSED(peService_Type);
    UNUSED(cCountOfServiceID);

    return 0;
#endif
}

U16 msAPI_SI_RemoveMismatchedProgram_ALLPCN(MS_SI_SHORT_SERVICEINFO *pwService_Info, MEMBER_SI_SERVICETYPE *peService_Type, U16 cCountOfServiceID)
{
    U16 i=0;
    MEMBER_SERVICETYPE *aeServiceType=NULL;//[SI_MAX_VC_PER_PHYSICAL];;
    U16 result=0;

    aeServiceType = (MEMBER_SERVICETYPE*)msAPI_Memory_Allocate(sizeof(MEMBER_SERVICETYPE)*cCountOfServiceID, BUF_ID_SI_REMOVE_PROG);
    if(aeServiceType)
    {
        for(i=0;i<cCountOfServiceID;i++)
        {
            aeServiceType[i] = msAPI_SI_ToCM_Service_Type(peService_Type[i]);
        }

    #if 1//(ENABLE_S2)
        result=msAPI_CM_RemoveMismatchedProgram_ALLPCN(pwService_Info, aeServiceType, cCountOfServiceID);
    #endif

    }
    else
    {
        ASSERT(0);
    }

    if(aeServiceType)   msAPI_Memory_Free(aeServiceType, BUF_ID_SI_REMOVE_PROG);

    return result;
}

BOOLEAN msAPI_SI_RemoveOpAndVirtualInDb(void)
{
#if (ENABLE_CI_PLUS_V1_4)
    U16 wPosition=0;
    DTV_CHANNEL_INFO stChannelInfo;
    U8 u8ServiceTypeIdx;
    MEMBER_SERVICETYPE eServiceType;
    U16 u16ProgCount;

    for (u8ServiceTypeIdx = 0; u8ServiceTypeIdx < 3; u8ServiceTypeIdx++)
    {
        if (u8ServiceTypeIdx == 0)
        {
            eServiceType = E_SERVICETYPE_DTV;
        }
        else if (u8ServiceTypeIdx == 1)
        {
            eServiceType = E_SERVICETYPE_RADIO;
        }
        else //if( u8ServiceTypeIdx == 2 )
        {
            eServiceType = E_SERVICETYPE_DATA;
        }

        u16ProgCount = msAPI_DTV_GetProgramCount(eServiceType, INCLUDE_ALL);

        if (u16ProgCount > 0)
        {
            wPosition = u16ProgCount - 1;

            do
            {
                msAPI_CM_GetProgramInfo(eServiceType, wPosition, &stChannelInfo);

                //printf("Loop%d......(bIsVirtualSevice,bIsOpService) = (%d, %d)\n", wPosition, stChannelInfo.stCHAttribute.bIsVirtualSevice, stChannelInfo.stCHAttribute.bIsOpService);
                if ( (stChannelInfo.stCHAttribute.bIsVirtualSevice) || (stChannelInfo.stCHAttribute.bIsOpService) )
                {
                    msAPI_CM_RemoveProgram(eServiceType, wPosition);
                }

                if (wPosition > 0)
                {
                    wPosition--;
                }

            }while(wPosition>0);
        }
    }
    return TRUE;
#else
    return TRUE;
#endif
}

BOOLEAN msAPI_SI_RemoveProgram(MEMBER_SI_SERVICETYPE bServiceType, WORD wPosition)
{
    MEMBER_SERVICETYPE bType;
    bType = msAPI_SI_ToCM_Service_Type(bServiceType);
    return msAPI_CM_RemoveProgram(bType,wPosition);
}

BOOLEAN msAPI_SI_GetServiceTypeAndPositionWithIDsAndRFCH(U16 wTransportStream_ID, U16 wOriginalNetwork_ID, U16 wService_ID, U8 cOrdinal, MEMBER_SI_SERVICETYPE * peServiceType, WORD * pwPosition, BOOLEAN bCheckTsID, BOOLEAN *pbInvalid, BOOLEAN *pbVisible, U8 u8RFChannelNumber)
{
    MEMBER_SERVICETYPE bServiceType;
    BOOLEAN bResult;

    bResult = msAPI_CM_GetServiceTypeAndPositionWithIDsAndRFCH(wTransportStream_ID, wOriginalNetwork_ID, wService_ID, cOrdinal,  &bServiceType,  pwPosition,  bCheckTsID, u8RFChannelNumber);
#if HK_STREAM_NO_NIT_TABLE
    if(bResult == 0)
    {
        bResult = msAPI_CM_GetServiceTypeAndPositionWithIDs(wTransportStream_ID, INVALID_ON_ID, wService_ID, cOrdinal,  &bServiceType,  pwPosition,  bCheckTsID);
    }
#endif
    if(bResult)
    {
        if(pbInvalid)
        {
            *pbInvalid=msAPI_CM_GetProgramAttribute(bServiceType, *pwPosition, E_ATTRIBUTE_IS_INVALID_SERVICE);
        }
        if(pbVisible)
        {
            *pbVisible=msAPI_CM_GetProgramAttribute(bServiceType, *pwPosition, E_ATTRIBUTE_IS_VISIBLE);
        }
        switch(bServiceType)
        {
            case E_SERVICETYPE_RADIO:
                *peServiceType=E_TYPE_RADIO;
                break;
            case E_SERVICETYPE_DATA:
                *peServiceType=E_TYPE_DATA;
                break;
            default:
                MS_DEBUG_MSG(printf("msAPI_SI_GetServiceTypeAndPositionWithIDs unsupport service type %x\n",bServiceType));
                *peServiceType=E_TYPE_DTV;
                break;
            case E_SERVICETYPE_DTV:
                *peServiceType=E_TYPE_DTV;
                break;
        }
    }
    return bResult;

}

BOOLEAN msAPI_SI_GetServiceTypeAndPositionWithIDsandServiceType(U16 wTransportStream_ID, U16 wOriginalNetwork_ID, U16 wService_ID, MEMBER_SI_SERVICETYPE wService_Type, U8 cOrdinal, MEMBER_SI_SERVICETYPE * peServiceType, WORD * pwPosition, BOOLEAN bCheckTsID, BOOLEAN *pbInvalid, BOOLEAN *pbVisible)
{
    MEMBER_SERVICETYPE bServiceType;
    BOOLEAN bResult;
    bResult = msAPI_CM_GetServiceTypeAndPositionWithIDsandServiceType(wTransportStream_ID, wOriginalNetwork_ID, wService_ID, wService_Type, cOrdinal,  &bServiceType,  pwPosition,  bCheckTsID);
#if HK_STREAM_NO_NIT_TABLE
    if(bResult == 0)
    {
        bResult = msAPI_CM_GetServiceTypeAndPositionWithIDsandServiceType(wTransportStream_ID, INVALID_ON_ID, wService_ID, wService_Type, cOrdinal,  &bServiceType,  pwPosition,  bCheckTsID);
    }
#endif
    if(bResult)
    {
        if(pbInvalid)
        {
            *pbInvalid=msAPI_CM_GetProgramAttribute(bServiceType, *pwPosition, E_ATTRIBUTE_IS_INVALID_SERVICE);
        }
        if(pbVisible)
        {
            *pbVisible=msAPI_CM_GetProgramAttribute(bServiceType, *pwPosition, E_ATTRIBUTE_IS_VISIBLE);
        }

        switch(bServiceType)
        {
            case E_SERVICETYPE_RADIO:
                *peServiceType=E_TYPE_RADIO;
                break;
            case E_SERVICETYPE_DATA:
                *peServiceType=E_TYPE_DATA;
                break;
            default:
                MS_DEBUG_MSG(printf("msAPI_SI_GetServiceTypeAndPositionWithIDs unsupport service type %x\n",bServiceType));
                *peServiceType=E_TYPE_DTV;
                break;
            case E_SERVICETYPE_DTV:
                *peServiceType=E_TYPE_DTV;
                break;
        }
    }
    return bResult;

}

BOOLEAN msAPI_SI_GetServiceTypeAndPositionWithIDs(U16 wTransportStream_ID, U16 wOriginalNetwork_ID, U16 wService_ID, U8 cOrdinal, MEMBER_SI_SERVICETYPE * peServiceType, WORD * pwPosition, BOOLEAN bCheckTsID, BOOLEAN *pbInvalid, BOOLEAN *pbVisible)
{
    MEMBER_SERVICETYPE bServiceType;
    BOOLEAN bResult;
    bResult = msAPI_CM_GetServiceTypeAndPositionWithIDs(wTransportStream_ID, wOriginalNetwork_ID, wService_ID, cOrdinal,  &bServiceType,  pwPosition,  bCheckTsID);
#if HK_STREAM_NO_NIT_TABLE
    if(bResult == 0)
    {
        bResult = msAPI_CM_GetServiceTypeAndPositionWithIDs(wTransportStream_ID, INVALID_ON_ID, wService_ID, cOrdinal,  &bServiceType,  pwPosition,  bCheckTsID);
    }
#endif
    if(bResult)
    {
        if(pbInvalid)
        {
            *pbInvalid=msAPI_CM_GetProgramAttribute(bServiceType, *pwPosition, E_ATTRIBUTE_IS_INVALID_SERVICE);
        }
        if(pbVisible)
        {
            *pbVisible=msAPI_CM_GetProgramAttribute(bServiceType, *pwPosition, E_ATTRIBUTE_IS_VISIBLE);
        }
        switch(bServiceType)
        {
            case E_SERVICETYPE_RADIO:
                *peServiceType=E_TYPE_RADIO;
                break;
            case E_SERVICETYPE_DATA:
                *peServiceType=E_TYPE_DATA;
                break;
            default:
                MS_DEBUG_MSG(printf("msAPI_SI_GetServiceTypeAndPositionWithIDs unsupport service type %x\n",bServiceType));
                *peServiceType=E_TYPE_DTV;
                break;
            case E_SERVICETYPE_DTV:
                *peServiceType=E_TYPE_DTV;
                break;
        }
    }
    return bResult;

}

BOOLEAN msAPI_SI_GetServiceTypeAndPositionWithIDsAndPmtPid(U16 wTransportStream_ID, U16 wOriginalNetwork_ID, U16 wService_ID, U16 wPmt_Pid, U8 cOrdinal, MEMBER_SI_SERVICETYPE * peServiceType, WORD * pwPosition, BOOLEAN bCheckTsID, BOOLEAN *pbInvalid, BOOLEAN *pbVisible)
{
    MEMBER_SERVICETYPE bServiceType;
    BOOLEAN bResult;
    bResult = msAPI_CM_GetServiceTypeAndPositionWithIDsAndPmtPid(wTransportStream_ID, wOriginalNetwork_ID, wService_ID, wPmt_Pid, cOrdinal, &bServiceType, pwPosition, bCheckTsID);
#if HK_STREAM_NO_NIT_TABLE
    if(bResult == 0)
    {
        bResult = msAPI_CM_GetServiceTypeAndPositionWithIDsAndPmtPid(wTransportStream_ID, INVALID_ON_ID, wService_ID, wPmt_Pid, cOrdinal, &bServiceType, pwPosition, bCheckTsID);
    }
#endif
    if(bResult)
    {
        if(pbInvalid)
        {
            *pbInvalid=msAPI_CM_GetProgramAttribute(bServiceType, *pwPosition, E_ATTRIBUTE_IS_INVALID_SERVICE);
        }
        if(pbVisible)
        {
            *pbVisible=msAPI_CM_GetProgramAttribute(bServiceType, *pwPosition, E_ATTRIBUTE_IS_VISIBLE);
        }
        switch(bServiceType)
        {
            case E_SERVICETYPE_RADIO:
                *peServiceType=E_TYPE_RADIO;
                break;
            case E_SERVICETYPE_DATA:
                *peServiceType=E_TYPE_DATA;
                break;
            default:
                MS_DEBUG_MSG(printf("msAPI_SI_GetServiceTypeAndPositionWithIDsAndPmtPid unsupport service type %x\n",bServiceType));
                *peServiceType=E_TYPE_DTV;
                break;
            case E_SERVICETYPE_DTV:
                *peServiceType=E_TYPE_DTV;
                break;
        }
    }

    return bResult;
}

//#if (MHEG5_SIINFO_ENABLE)
BOOLEAN msAPI_SI_GetProviderName(MEMBER_SI_SERVICETYPE bServiceType, WORD wPosition, BYTE * bProviderName, U16 *pMaxLen)
{
#if(MHEG5_SIINFO_ENABLE)

    MEMBER_SERVICETYPE bType = E_SERVICETYPE_INVALID;
    BOOLEAN bResult = FALSE;
    U8 au8CurProviderName[MAX_SERVICE_NAME]={0};

    bType = msAPI_SI_ToCM_Service_Type(bServiceType);
    bResult = msAPI_CM_GetProviderName(bType, wPosition, au8CurProviderName);

    if( bResult == FALSE )
        return FALSE;

    memcpy(bProviderName,au8CurProviderName,SI_MAX_SERVICE_NAME > MAX_SERVICE_NAME ? MAX_SERVICE_NAME : SI_MAX_SERVICE_NAME);
    *pMaxLen = MAX_SERVICE_NAME;

    return TRUE;
#else

    UNUSED(bServiceType);
    UNUSED(wPosition);
    UNUSED(bProviderName);
    UNUSED(pMaxLen);

    return FALSE;
#endif
}
//#endif //#if(MHEG5_SIINFO_ENABLE)

BOOLEAN msAPI_SI_FillProgramDataWithDefault(SI_DTV_CHANNEL_INFO *pstDtvPgmData)
{
    U8 i,j;

    if(pstDtvPgmData)
    {
        pstDtvPgmData->wOrder = DEFAULT_ORDER;
        pstDtvPgmData->wLCN = DEFAULT_LCN;
        pstDtvPgmData->wSimu_LCN = DEFAULT_SIMU_LCN;
        pstDtvPgmData->stPSI_SI_Version.bPATVer = DEFAULT_VERSION;
        pstDtvPgmData->stPSI_SI_Version.bPMTVer = DEFAULT_VERSION;
        pstDtvPgmData->stPSI_SI_Version.bNITVer = DEFAULT_VERSION;
        pstDtvPgmData->stPSI_SI_Version.bSDTVer = DEFAULT_VERSION;
        pstDtvPgmData->stCHAttribute.bVisibleServiceFlag = DEFAULT_VISIBLE_SERVICE_FLAG;
        pstDtvPgmData->stCHAttribute.bNumericSelectionFlag = DEFAULT_NUMERIC_SELECTION_FLAG;
        pstDtvPgmData->stCHAttribute.bIsReplaceDel = DEFAULT_IS_REPLACE_DEL;
        pstDtvPgmData->stCHAttribute.bIsScramble = DEFAULT_IS_SCRAMBLED;
        pstDtvPgmData->stCHAttribute.bIsStillPicture = DEFAULT_IS_STILL_PICTURE;
        pstDtvPgmData->stCHAttribute.bInvalidCell = DEFAULT_IS_INVALID_CELL;
        pstDtvPgmData->stCHAttribute.bInvalidService = DEFAULT_IS_INVALID_SERVICE;
        pstDtvPgmData->stCHAttribute.bUnconfirmedService = DEFAULT_IS_UNCONFIRMED_SERVICE;
        pstDtvPgmData->stCHAttribute.bReplaceService = DEFAULT_IS_REPLACE_SERVICE;
        pstDtvPgmData->stCHAttribute.bIsServiceIdOnly = DEFAULT_IS_SERVICE_ID_ONLY;
        pstDtvPgmData->stCHAttribute.eVideoType = E_SI_VIDEOTYPE_MPEG;
        pstDtvPgmData->stCHAttribute.bServiceType = E_TYPE_INVALID;
        pstDtvPgmData->stCHAttribute.bIsSpecialService = DEFAULT_SPECIAL_SERVICE;
        pstDtvPgmData->stCHAttribute.bServiceTypePrio = E_SI_SERVICETYPE_PRIORITY_NONE;
        pstDtvPgmData->stCHAttribute.wSignalStrength = DEFAULT_SIGNAL_STRENGTH;
        pstDtvPgmData->stCHAttribute.bValidLCN = DEFAULT_LCN_VALID;
        pstDtvPgmData->stCHAttribute.bIsVirtualSevice= DEFAULT_IS_VIRTUAL_CHANNEL; // ENABLE_CI_PLUS_V1_4
        pstDtvPgmData->stCHAttribute.bIsOpService= DEFAULT_IS_OP_CHANNEL; // ENABLE_CI_PLUS_V1_4

#if ENABLE_T_C_CHANNEL_MIX
        pstDtvPgmData->stCHAttribute.bIsTerrestrial = DEFAULT_IS_CABLE;
#endif
        pstDtvPgmData->wService_ID = DEFAULT_SERVICE_ID;
        pstDtvPgmData->wPmt_PID = DEFAULT_PMT_PID;
        pstDtvPgmData->wPCR_PID = DEFAULT_PCR_PID;
        pstDtvPgmData->wVideo_PID = DEFAULT_VIDEO_PID;
#if(ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
        pstDtvPgmData->stCHAttribute.bIsNewService = DEFAULT_IS_NEW_SERVICE;
        pstDtvPgmData->wSgt_PID = DEFAULT_SGT_PID;
#endif

        for(i=0; i < SI_MAX_AUD_LANG_NUM; i++)
        {
            pstDtvPgmData->stAudInfo[i].wAudPID = INVALID_PID;
            pstDtvPgmData->stAudInfo[i].wAudType = E_SI_AUDIOSTREAM_INVALID;
#if 1//NTV_FUNCTION_ENABLE
            pstDtvPgmData->stAudInfo[i].u8ProfileAndLevel = 0;
            pstDtvPgmData->stAudInfo[i].u8Component_AAC_Type = 0;
#endif
            for(j = 0; j < SI_MAX_AUD_ISOLANG_NUM; j++)
            {
                pstDtvPgmData->stAudInfo[i].aISOLangInfo[j].bAudType = 0x00;
                pstDtvPgmData->stAudInfo[i].aISOLangInfo[j].bISOLanguageInfo = E_SI_AUDIOMODE_STEREO;
                pstDtvPgmData->stAudInfo[i].aISOLangInfo[j].bIsValid = FALSE;
                pstDtvPgmData->stAudInfo[i].aISOLangInfo[j].bBroadcastMixedAD = FALSE;
                pstDtvPgmData->stAudInfo[i].aISOLangInfo[j].bISOLangIndex = LANGUAGE_NONE;
                pstDtvPgmData->stAudInfo[i].aISOLangInfo[j].bReserved = FALSE;
            }
        }

        for(i=0; i < SI_MAX_SERVICE_NAME; i++)
        {
            pstDtvPgmData->bChannelName[i] = 0;
        }
        return TRUE;
    }
    return FALSE;

}

void msAPI_SI_FillProgramDefaultDataWithoutSrvName(SI_SHORT_DTV_CHANNEL_INFO *pstShortDtvPgmData)
{
    BYTE i,j;
    i = 0;
    j = 0;

    pstShortDtvPgmData->wOrder = DEFAULT_ORDER;
    pstShortDtvPgmData->wLCN = DEFAULT_LCN;
    pstShortDtvPgmData->wTS_LCN= DEFAULT_LCN;
    pstShortDtvPgmData->wSimu_LCN = DEFAULT_SIMU_LCN;
    pstShortDtvPgmData->wCellID = DEFAULT_CELLID;
    pstShortDtvPgmData->cRFChannelNumber = DEFAULT_PCN;
    pstShortDtvPgmData->stPSI_SI_Version.bPATVer = DEFAULT_VERSION;
    pstShortDtvPgmData->stPSI_SI_Version.bPMTVer = DEFAULT_VERSION;
    pstShortDtvPgmData->stPSI_SI_Version.bNITVer = DEFAULT_VERSION;
    pstShortDtvPgmData->stPSI_SI_Version.bSDTVer = DEFAULT_VERSION;
    pstShortDtvPgmData->stCHAttribute.wSignalStrength = DEFAULT_SIGNAL_STRENGTH;
    pstShortDtvPgmData->stCHAttribute.bValidLCN = DEFAULT_LCN_VALID;
    pstShortDtvPgmData->stCHAttribute.bIsVirtualSevice= DEFAULT_IS_VIRTUAL_CHANNEL; // ENABLE_CI_PLUS_V1_4
    pstShortDtvPgmData->stCHAttribute.bIsOpService= DEFAULT_IS_OP_CHANNEL; // ENABLE_CI_PLUS_V1_4

    pstShortDtvPgmData->stCHAttribute.bVisibleServiceFlag = DEFAULT_VISIBLE_SERVICE_FLAG;
    pstShortDtvPgmData->stCHAttribute.bNumericSelectionFlag = DEFAULT_NUMERIC_SELECTION_FLAG;
    //pstShortDtvPgmData->stCHAttribute.bIsDelete = DEFAULT_IS_DELETED;
    pstShortDtvPgmData->stCHAttribute.bIsReplaceDel = DEFAULT_IS_REPLACE_DEL;
    //pstShortDtvPgmData->stCHAttribute.bIsFavorite = DEFAULT_IS_FAVORITE;
    //pstShortDtvPgmData->stCHAttribute.bIsMove = DEFAULT_IS_MOVED;
    pstShortDtvPgmData->stCHAttribute.bInvalidCell = DEFAULT_IS_INVALID_CELL;
    pstShortDtvPgmData->stCHAttribute.bInvalidService = DEFAULT_IS_INVALID_SERVICE;
    pstShortDtvPgmData->stCHAttribute.bUnconfirmedService = DEFAULT_IS_UNCONFIRMED_SERVICE;
    //pstShortDtvPgmData->stCHAttribute.bIsSkipped = DEFAULT_IS_SKIPPED;
    //pstShortDtvPgmData->stCHAttribute.bIsLock = DEFAULT_IS_LOCKED;
    pstShortDtvPgmData->stCHAttribute.bIsScramble = DEFAULT_IS_SCRAMBLED;
    pstShortDtvPgmData->stCHAttribute.bIsStillPicture = DEFAULT_IS_STILL_PICTURE;
    pstShortDtvPgmData->stCHAttribute.bReplaceService = DEFAULT_IS_REPLACE_SERVICE;
    pstShortDtvPgmData->stCHAttribute.eVideoType = E_SI_VIDEOTYPE_MPEG;
    pstShortDtvPgmData->stCHAttribute.bIsServiceIdOnly = DEFAULT_IS_SERVICE_ID_ONLY;
    pstShortDtvPgmData->stCHAttribute.bIsDataServiceAvailable = DEFAULT_IS_DATA_SERVICE_AVAILABLE;
    pstShortDtvPgmData->stCHAttribute.bServiceType = E_TYPE_INVALID;
    pstShortDtvPgmData->stCHAttribute.bServiceTypePrio = E_SI_SERVICETYPE_PRIORITY_NONE;
    pstShortDtvPgmData->wTransportStream_ID = DEFAULT_TS_ID;
    pstShortDtvPgmData->wOriginalNetwork_ID = DEFAULT_ON_ID;
    pstShortDtvPgmData->wService_ID = DEFAULT_SERVICE_ID;
    pstShortDtvPgmData->wPmt_PID = DEFAULT_PMT_PID;
    pstShortDtvPgmData->wPCR_PID = DEFAULT_PCR_PID;
    pstShortDtvPgmData->wVideo_PID = DEFAULT_VIDEO_PID;
#if(ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
    pstShortDtvPgmData->stCHAttribute.bIsNewService = DEFAULT_IS_NEW_SERVICE;
#endif

    for(i=0; i < SI_MAX_AUD_LANG_NUM; i++)
    {
        pstShortDtvPgmData->stAudInfo[i].wAudPID = INVALID_PID;
        pstShortDtvPgmData->stAudInfo[i].wAudType = E_SI_AUDIOSTREAM_INVALID;
#if 1//NTV_FUNCTION_ENABLE
        pstShortDtvPgmData->stAudInfo[i].u8ProfileAndLevel = 0;
        pstShortDtvPgmData->stAudInfo[i].u8Component_AAC_Type = 0;
#endif
        for(j = 0; j < SI_MAX_AUD_ISOLANG_NUM; j++)
        {
            pstShortDtvPgmData->stAudInfo[i].aISOLangInfo[j].bAudType = 0x00;
            pstShortDtvPgmData->stAudInfo[i].aISOLangInfo[j].bISOLanguageInfo = E_SI_AUDIOMODE_STEREO;
            pstShortDtvPgmData->stAudInfo[i].aISOLangInfo[j].bIsValid = FALSE;
            pstShortDtvPgmData->stAudInfo[i].aISOLangInfo[j].bBroadcastMixedAD = FALSE;
            pstShortDtvPgmData->stAudInfo[i].aISOLangInfo[j].bISOLangIndex = LANGUAGE_NONE;
            pstShortDtvPgmData->stAudInfo[i].aISOLangInfo[j].bReserved = FALSE;
        }

    }
}

BOOLEAN msAPI_SI_AddProgramIDTable(SI_DTVPROGRAMID *pstSI_DtvIDTable, WORD *pu16IDIdex)
{
    DTVPROGRAMID DtvIDTable;
    U16 u16IDIndex = 0xFFFF;
    BOOLEAN bRet;


    SI_ADD_PROG_ID(printf("msAPI_SI_AddProgramIDTable()\n"););

    if (NULL == pstSI_DtvIDTable || NULL == pu16IDIdex)
        return FALSE;

    SI_ADD_PROG_ID(printf(" ->cRFChannelNumber=%u\n",pstSI_DtvIDTable->cRFChannelNumber););
    SI_ADD_PROG_ID(printf(" ->u32Frequency=%u\n",pstSI_DtvIDTable->u32Frequency););
    SI_ADD_PROG_ID(printf(" ->u32SymbRate=%u\n",pstSI_DtvIDTable->u32SymbRate););
    SI_ADD_PROG_ID(printf(" ->u32SymbRate=%u\n",pstSI_DtvIDTable->u16SymbolRate););
    SI_ADD_PROG_ID(printf(" ->QamMode=%u\n",pstSI_DtvIDTable->QamMode););
    SI_ADD_PROG_ID(printf(" ->enBandWidth=%u\n",pstSI_DtvIDTable->enBandWidth););


    memset(&DtvIDTable, 0, sizeof(DTVPROGRAMID));

    DtvIDTable.wTransportStream_ID=pstSI_DtvIDTable->wTransportStream_ID;
    DtvIDTable.wOriginalNetwork_ID=pstSI_DtvIDTable->wOriginalNetwork_ID;
    DtvIDTable.cRFChannelNumber=pstSI_DtvIDTable->cRFChannelNumber;
    DtvIDTable.wNetwork_ID=pstSI_DtvIDTable->wNetwork_ID;
    DtvIDTable.wCellID=pstSI_DtvIDTable->wCellID;
#if ENABLE_SAVE_SQI
    DtvIDTable.wStrengthQuality = pstSI_DtvIDTable->wStrengthQuality;
#endif


#if(ENABLE_S2)
    if( IsS2InUse() )
    {
        DtvIDTable.u32S2Frequency = pstSI_DtvIDTable->u32S2Frequency;
        SI_ADD_PROG_ID( printf(" u32S2Frequency=%u\n", DtvIDTable.u32S2Frequency); );
    }
    else
#endif
    {
        DtvIDTable.u32Frequency = pstSI_DtvIDTable->u32Frequency;
        SI_ADD_PROG_ID( printf(" u32Frequency=%u\n", DtvIDTable.u32Frequency); );
    }


    // Get SymbolRate ...
#if(ENABLE_S2)
    if( IsS2InUse() )
    {
        DtvIDTable.u16SymbolRate=pstSI_DtvIDTable->u16SymbolRate;
        SI_ADD_PROG_ID( printf(" u16SymbolRate=%u\n", DtvIDTable.u16SymbolRate); );
    }
    else
#endif
    {
    #if( ENABLE_DVBC )
        if( IsDVBCInUse() )
        {
            //DtvIDTable.u32SymbRate = pstSI_DtvIDTable->u32SymbRate;
            if( pstSI_DtvIDTable->u32SymbRate <= 0xFFFF )
            {
                DtvIDTable.u16SymbolRate = pstSI_DtvIDTable->u32SymbRate;
                SI_ADD_PROG_ID( printf(" u16SymbolRate=%u\n", DtvIDTable.u16SymbolRate); );
            }
            else
            {
                PRINT_CURRENT_LINE();
                printf("\nError: Data lose!\n");
            }
        }
    #endif
    }

#if 1//ENABLE_DVBC
    //DtvIDTable.u32Frequency=pstSI_DtvIDTable->u32Frequency;
    DtvIDTable.QamMode=pstSI_DtvIDTable->QamMode;
    DtvIDTable.enBandWidth = pstSI_DtvIDTable->enBandWidth;
#endif

    DtvIDTable.cPLPID=pstSI_DtvIDTable->u8PLP_ID;
    DtvIDTable.cHpLp=pstSI_DtvIDTable->u8HpLp;

#if(ENABLE_S2)
    if( IsS2InUse() )
    {
        DtvIDTable.SatelliteId =pstSI_DtvIDTable->SatelliteId;;
        DtvIDTable.u8Polarity=pstSI_DtvIDTable->u8Polarity;
    }
#endif

    SI_ADD_PROG_ID( printf(" cRFChannelNumber=%u\n", DtvIDTable.cRFChannelNumber); );
    SI_ADD_PROG_ID( printf(" enBandWidth=%u\n", DtvIDTable.enBandWidth); );

    //SI_ADD_PROG_ID( printf(" u32SymbRate=%u\n", DtvIDTable.u32SymbRate); );
#if(ENABLE_S2)
    SI_ADD_PROG_ID( printf(" u16SymbolRate=%u\n", DtvIDTable.u16SymbolRate); );
#endif

    bRet = msAPI_CM_AddProgramIDTable(&DtvIDTable, TRUE, &u16IDIndex);

    SI_ADD_PROG_ID(printf(" Line # %d, pu16IDIdex=0x%X, u16IDIndex=0x%X\n", __LINE__, pu16IDIdex, &u16IDIndex););

    if( bRet )
    {
        //*pu16IDIdex = u16IDIndex;

        /*Due to parameter "pu16IDIdex" alignment issue will caused DTMB scan DTV crash.*/
        /*Re-assign data type and refined assignment.*/
        ((U8*)pu16IDIdex)[0] = u16IDIndex;
        ((U8*)pu16IDIdex)[1] = u16IDIndex >> 8;
    }

    return bRet;
}

#define ENABLE_ADD_DEMOD_TYPE_TO_SERVICE_NAME   0

BOOLEAN msAPI_SI_AddProgram(SI_DTVPROGRAMID *stDtvIDTable, SI_DTV_CHANNEL_INFO *pSIDTVProgramData, BOOLEAN *bDBFull, BOOLEAN bSkipCheck)
{
    DTV_CHANNEL_INFO DTVProgramData;
    //int maxAudio;


    msDebug_ANSI_SetColorText(E_FONT_COLOR_CYAN);
    //msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_GREEN);

    printf("\n ---------------------------------\n");
    printf(" >>>> msAPI_SI_AddProgram()\n");
    printf(" cRFChannelNumber=%u,", stDtvIDTable->cRFChannelNumber);


#if ENABLE_DVBC
    if( (FALSE == msAPI_SI_GetOpMode())
      &&(SI_UNCONFIRMED_PHYSICAL_CHANNEL_NUMBER!=stDtvIDTable->cRFChannelNumber)
      &&(stDtvIDTable->u32Frequency==0)
      )
    {
        U8 u8PhNum=0;
        DTVPROGRAMID_M stDPI;
        memset(&stDPI, 0, sizeof(stDPI));
        u8PhNum=msAPI_CM_Get_RFChannelIndex(stDtvIDTable->cRFChannelNumber);
        if( msAPI_CM_GetIDTable(u8PhNum,(BYTE *)&stDPI,E_DATA_ID_TABLE) )
        {
            //stDtvIDTable->u32SymbRate= stDPI.u32SymbRate;
            stDtvIDTable->u32SymbRate= msAPI_CM_Get_IDTab_SymbolRate(&stDPI);

            stDtvIDTable->QamMode= stDPI.QamMode;
            stDtvIDTable->enBandWidth = stDPI.enBandWidth;
            stDtvIDTable->u32Frequency = stDPI.u32Frequency;
            stDtvIDTable->u8PLP_ID = stDPI.cPLPID;
            stDtvIDTable->u8HpLp = stDPI.cHpLp;
        }
    }
#endif

#if(ENABLE_S2)
  #if ( WATCH_DOG == ENABLE )
    msAPI_Timer_ResetWDT();
  #endif
#endif

#if(ENABLE_S2)
    if(IsS2InUse())
    {
        printf("%d,%d,,%d,%d,%d,%d,%d,", stDtvIDTable->u32S2Frequency, stDtvIDTable->u16SymbolRate,stDtvIDTable->u8Polarity,stDtvIDTable->SatelliteId, stDtvIDTable->QamMode,stDtvIDTable->enBandWidth,stDtvIDTable->u8PLP_ID);
    }
    else
#endif
    {
        printf("%d,%d,%d,%d, u8PLP_ID=0x%X,", stDtvIDTable->u32Frequency, stDtvIDTable->u32SymbRate, stDtvIDTable->QamMode,stDtvIDTable->enBandWidth,stDtvIDTable->u8PLP_ID);
    }

    printf(" ONID:%d, NID:%d, ", stDtvIDTable->wOriginalNetwork_ID, stDtvIDTable->wNetwork_ID);
    printf(" wLCN :%d, wTS_LCN:%d, sLCN:%d\n", pSIDTVProgramData->wLCN, pSIDTVProgramData->wTS_LCN, pSIDTVProgramData->wSimu_LCN);

    if (FALSE == msAPI_SI_AddProgramIDTable(stDtvIDTable, &DTVProgramData.bIDIdex))
    {
        return FALSE;
    }

#if (ENABLE_SBTVD_SI)
    if(msAPI_SRC_IS_SBTVD_InUse())
    {
        if(pSIDTVProgramData->stLCN.bPhysicalChannel > MAX_UHF_PHYSICAL_CHANNEL_NUMBER_ISDBT)
        {
            BYTE abPhysicalChannel = 0;

            msAPI_CM_GetIDTable(DTVProgramData.bIDIdex, &abPhysicalChannel, E_DATA_PCN);
            pSIDTVProgramData->stLCN.bPhysicalChannel = abPhysicalChannel;
        }
        DTVProgramData.stLCN.bPhysicalChannel=pSIDTVProgramData->stLCN.bPhysicalChannel;
        DTVProgramData.stLCN.bVirtualChannel=pSIDTVProgramData->stLCN.bVirtualChannel;
    }
    else
#endif
    {
        DTVProgramData.wLCN=pSIDTVProgramData->wLCN;
    }


    DTVProgramData.wPCR_PID=pSIDTVProgramData->wPCR_PID;
    DTVProgramData.wVideo_PID=pSIDTVProgramData->wVideo_PID;
    DTVProgramData.wOrder=pSIDTVProgramData->wOrder;

    DTVProgramData.wPmt_PID=pSIDTVProgramData->wPmt_PID;
    DTVProgramData.wService_ID=pSIDTVProgramData->wService_ID;
#if 1//NTV_FUNCTION_ENABLE
    DTVProgramData.wTS_LCN=pSIDTVProgramData->wTS_LCN;
#endif
    DTVProgramData.wSimu_LCN=pSIDTVProgramData->wSimu_LCN;

    DTVProgramData.stPSI_SI_Version.bNITVer=pSIDTVProgramData->stPSI_SI_Version.bNITVer;
    DTVProgramData.stPSI_SI_Version.bPATVer=pSIDTVProgramData->stPSI_SI_Version.bPATVer;
    DTVProgramData.stPSI_SI_Version.bPMTVer=pSIDTVProgramData->stPSI_SI_Version.bPMTVer;
    DTVProgramData.stPSI_SI_Version.bSDTVer=pSIDTVProgramData->stPSI_SI_Version.bSDTVer;

    DTVProgramData.stCHAttribute.wSignalStrength=pSIDTVProgramData->stCHAttribute.wSignalStrength;
#if 1//NTV_FUNCTION_ENABLE
        DTVProgramData.stCHAttribute.bIsSpecialService = pSIDTVProgramData->stCHAttribute.bIsSpecialService;
#endif

    DTVProgramData.stCHAttribute.bVisibleServiceFlag=pSIDTVProgramData->stCHAttribute.bVisibleServiceFlag;
    DTVProgramData.stCHAttribute.bNumericSelectionFlag=pSIDTVProgramData->stCHAttribute.bNumericSelectionFlag;
    DTVProgramData.stCHAttribute.bIsDelete=DEFAULT_IS_DELETED;
    DTVProgramData.stCHAttribute.bIsMove=DEFAULT_IS_MOVED;
    DTVProgramData.stCHAttribute.bIsScramble=pSIDTVProgramData->stCHAttribute.bIsScramble;
    DTVProgramData.stCHAttribute.bIsSkipped=DEFAULT_IS_SKIPPED;
    DTVProgramData.stCHAttribute.bIsLock=DEFAULT_IS_LOCKED;
#if ENABLE_TARGET_REGION
    DTVProgramData.stCHAttribute.cRegion=DEFAULT_REGION;
#endif
    DTVProgramData.stCHAttribute.bIsStillPicture=pSIDTVProgramData->stCHAttribute.bIsStillPicture;
    DTVProgramData.stCHAttribute.bReplaceService=pSIDTVProgramData->stCHAttribute.bReplaceService;

#if(ENABLE_S2_FAST_SCAN)
    DTVProgramData.stCHAttribute.bIsFastScan = pSIDTVProgramData->stCHAttribute.bIsFastScan;
#endif

#if ENABLE_T_C_CHANNEL_MIX
    DTVProgramData.stCHAttribute.bIsTerrestrial = (!IsDVBCInUse());
#endif
    #if (ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
    DTVProgramData.stCHAttribute.bIsNewService = pSIDTVProgramData->stCHAttribute.bIsNewService;
    #endif
    DTVProgramData.stCHAttribute.bIsServiceIdOnly=pSIDTVProgramData->stCHAttribute.bIsServiceIdOnly;
    DTVProgramData.stCHAttribute.bIsReplaceDel=pSIDTVProgramData->stCHAttribute.bIsReplaceDel;
    DTVProgramData.stCHAttribute.bServiceType = (U8)msAPI_SI_ToCM_Service_Type((MEMBER_SI_SERVICETYPE)pSIDTVProgramData->stCHAttribute.bServiceType);
    DTVProgramData.stCHAttribute.bServiceTypePrio=msAPI_SI_ToCM_Service_Priority(pSIDTVProgramData->stCHAttribute.bServiceTypePrio);
    DTVProgramData.stCHAttribute.eVideoType=msAPI_SI_ToCM_Video_Type(pSIDTVProgramData->stCHAttribute.eVideoType);

#if(ENABLE_CI_PLUS_V1_4)
    DTVProgramData.stCHAttribute.bIsVirtualSevice = pSIDTVProgramData->stCHAttribute.bIsVirtualSevice;
    DTVProgramData.stCHAttribute.bIsOpService = pSIDTVProgramData->stCHAttribute.bIsOpService;
#endif

    //DTVProgramData.stCHAttribute.eRuningStatus=pDTVProgramData->stCHAttribute.eRuningStatus;
    DTVProgramData.stCHAttribute.bIsFavorite=DEFAULT_IS_FAVORITE;

  #if(ENABLE_S2_CHANNEL_FAV_NEWSTYLE)
    DTVProgramData.stChIsFav = DEFAULT_IS_FAVORITE;
  #endif

    printf("wLCN:%d, VideoPID:%d, ", pSIDTVProgramData->wLCN, DTVProgramData.wVideo_PID);
    printf("\r\n >>>> ServiceType:0x%x, VisibleFlag:0x%x, ", pSIDTVProgramData->stCHAttribute.bServiceType, pSIDTVProgramData->stCHAttribute.bVisibleServiceFlag);
    printf("TSID:%d, SID:%d, Scram:%d, ", stDtvIDTable->wTransportStream_ID, pSIDTVProgramData->wService_ID, pSIDTVProgramData->stCHAttribute.bIsScramble);


#if( ENABLE_CM_STORE_AUD_INFO_NEW_METHOD )

    PRINT_CURRENT_LINE();

    // Pre check aud_info valid count...
    U8 u8AudInfoValidCount = 0;
    U8 u8AudIdx;
    for( u8AudIdx=0; u8AudIdx<maxAudio; u8AudIdx++)
    {
        if( (pSIDTVProgramData->stAudInfo[u8AudIdx].wAudPID) != INVALID_PID )
            u8AudInfoValidCount += 1;
    }
    printf("u8AudInfoValidCount=%u\n", u8AudInfoValidCount);

    {
        AUD_INFO astCMAudInfo[MAX_AUD_LANG_NUM];
        memset(astCMAudInfo, 0, sizeof(astCMAudInfo));

        // Copy to astCMAudInfo
        msAPI_SI_Copy_SI_AudInfo_To_CM_AudInfo(pSIDTVProgramData->stAudInfo, astCMAudInfo, u8AudInfoValidCount);

        // Set to DB
        msAPI_CM_Add_AudInfo(astCMAudInfo, u8AudInfoValidCount);

        //DTVProgramData.u16AudInfoTabIndex =
    }
#endif

    U8 maxAudio = MAX_AUD_LANG_NUM > SI_MAX_AUD_LANG_NUM ? SI_MAX_AUD_LANG_NUM : MAX_AUD_LANG_NUM;

#if 1 // Use new API
    msAPI_SI_Copy_SI_AudInfo_To_CM_AudInfo(pSIDTVProgramData->stAudInfo, DTVProgramData.stAudInfo, maxAudio);

#else
    int maxISO = MAX_AUD_ISOLANG_NUM > SI_MAX_AUD_ISOLANG_NUM ? SI_MAX_AUD_ISOLANG_NUM : MAX_AUD_ISOLANG_NUM;
    int i;
    U8 j;
    for(i=0;i<maxAudio;i++)
    {
        //DTVProgramData.stAudInfo[i].wAudType = msAPI_SI_ToCM_Audio_Type(pSIDTVProgramData->stAudInfo[i].wAudType);
        DTVProgramData.stAudInfo[i].eSIAudType = (SI_AUDIOSTREAM_TYPE)pSIDTVProgramData->stAudInfo[i].wAudType;

        //printf("\n[[In2_%x  out_%x",pDTVProgramData->stAudInfo[i].wAudType,DTVProgramData.stAudInfo[i].wAudType);

        DTVProgramData.stAudInfo[i].wAudPID = pSIDTVProgramData->stAudInfo[i].wAudPID;

    #if 1//NTV_FUNCTION_ENABLE
        //DTVProgramData.stAudInfo[i].u8ProfileAndLevel = pSIDTVProgramData->stAudInfo[i].u8ProfileAndLevel;
        DTVProgramData.stAudInfo[i].eProfileAndLevel = msAPI_SI_ToCM_ProfileAndLevel(pSIDTVProgramData->stAudInfo[i].u8ProfileAndLevel);

        //DTVProgramData.stAudInfo[i].u8Component_AAC_Type=pSIDTVProgramData->stAudInfo[i].u8Component_AAC_Type;
    #endif

        for(j=0;j<maxISO;j++)
        {
            DTVProgramData.stAudInfo[i].aISOLangInfo[j].bISOLangIndex=pSIDTVProgramData->stAudInfo[i].aISOLangInfo[j].bISOLangIndex;
            DTVProgramData.stAudInfo[i].aISOLangInfo[j].bISOLanguageInfo=msAPI_SI_ToCM_Audio_Mode(pSIDTVProgramData->stAudInfo[i].aISOLangInfo[j].bISOLanguageInfo);
            DTVProgramData.stAudInfo[i].aISOLangInfo[j].bAudType=pSIDTVProgramData->stAudInfo[i].aISOLangInfo[j].bAudType;
            DTVProgramData.stAudInfo[i].aISOLangInfo[j].bIsValid=pSIDTVProgramData->stAudInfo[i].aISOLangInfo[j].bIsValid;
            DTVProgramData.stAudInfo[i].aISOLangInfo[j].bBroadcastMixedAD=pSIDTVProgramData->stAudInfo[i].aISOLangInfo[j].bBroadcastMixedAD;
            DTVProgramData.stAudInfo[i].aISOLangInfo[j].bReserved=pSIDTVProgramData->stAudInfo[i].aISOLangInfo[j].bReserved;
        }
    }
#endif


    DTVProgramData.stCHAttribute.bInvalidCell=pSIDTVProgramData->stCHAttribute.bInvalidCell;
    DTVProgramData.stCHAttribute.bUnconfirmedService=pSIDTVProgramData->stCHAttribute.bUnconfirmedService;
    DTVProgramData.stCHAttribute.bInvalidService=pSIDTVProgramData->stCHAttribute.bInvalidService;

#if ENABLE_SAVE_MULTILINGUAL_SERVICE_NAME
    {
        U8 i;
        EN_SI_LANGUAGE eLanguage=SI_LANGUAGE_NONE;
        for(i=0;i<MAX_MULTI_LINGUAL_SERVICE_NAME;i++)
        {
            DTVProgramData.bMultiLanguage[i]=(BYTE)INVALID_LANG_INDEX;//LANGUAGE_NONE;

            if(MApp_SI_GetMultiLingualServiceNameByID(DTVProgramData.wService_ID,i,&eLanguage,
                DTVProgramData.bMultiChannelName[i],MAX_SERVICE_NAME))
            {
                DTVProgramData.bMultiLanguage[i]=(BYTE)MApp_GetLanguageBySILanguage(eLanguage);
/*
                printf("name %d(%d) %s %x %x %x %x\n",DTVProgramData.bMultiLanguage[i],eLanguage,
                    DTVProgramData.bMultiChannelName[i],
                    DTVProgramData.bMultiChannelName[i][0],
                    DTVProgramData.bMultiChannelName[i][1],
                    DTVProgramData.bMultiChannelName[i][2],
                    DTVProgramData.bMultiChannelName[i][3]);
*/
            }
        }

    }
#endif
    //MApp_SI_GetString(DTVProgramData.bChannelName, MAX_SERVICE_NAME, pDTVProgramData->bChannelName, SI_MAX_SERVICE_NAME, KEEP_CONTROL_CODE_CR_LF);

    printf("Service Name: ");
    msAPI_DtvSys_PrintServiceName(pSIDTVProgramData->bChannelName, SI_MAX_SERVICE_NAME);
    printf("\n");


    U8 u8ServiceNameCopyMaxSize = (SI_MAX_SERVICE_NAME > MAX_SERVICE_NAME) ? MAX_SERVICE_NAME : SI_MAX_SERVICE_NAME;

#if ENABLE_ADD_DEMOD_TYPE_TO_SERVICE_NAME
    U8 u8StrLen = 0;
    if( msAPI_Demod_GetCurrentDemodType() == E_DEMODULATOR_TYPE_DVBT2 )
    {
        memcpy(DTVProgramData.bChannelName, "T2 ", 3);
        u8StrLen = 3;
    }
    else if( msAPI_Demod_GetCurrentDemodType() == E_DEMODULATOR_TYPE_DVBT )
    {
        memcpy(DTVProgramData.bChannelName, "T ", 2);
        u8StrLen = 2;
    }
    else
    {
        memcpy(DTVProgramData.bChannelName, "? ", 2);
        u8StrLen = 2;
    }

    U8 u8MAX_SERVICE_NAME = MAX_SERVICE_NAME - u8StrLen;
    u8ServiceNameCopyMaxSize = (SI_MAX_SERVICE_NAME > u8MAX_SERVICE_NAME) ? u8MAX_SERVICE_NAME : SI_MAX_SERVICE_NAME;
    memcpy(DTVProgramData.bChannelName + u8StrLen, pSIDTVProgramData->bChannelName, u8ServiceNameCopyMaxSize);
    printf("=> Service Name 2: ");
    msAPI_DtvSys_PrintServiceName(DTVProgramData.bChannelName, MAX_SERVICE_NAME);
    printf("\n");

#else

    memcpy(DTVProgramData.bChannelName, pSIDTVProgramData->bChannelName, u8ServiceNameCopyMaxSize );
#endif


#if(MHEG5_SIINFO_ENABLE)
    memcpy(DTVProgramData.bProviderName,pSIDTVProgramData->bProviderName,SI_MAX_SERVICE_NAME > MAX_SERVICE_NAME ? MAX_SERVICE_NAME : SI_MAX_SERVICE_NAME );
#endif //#if(MHEG5_SIINFO_ENABLE)

#if(ENABLE_S2)
    //DTVProgramData.SatId = pSIDTVProgramData->satid;
#endif

#if(ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
    DTVProgramData.wSgt_PID = pSIDTVProgramData->wSgt_PID;
#endif

    if( (DTVProgramData.wLCN == 0)
      ||(DTVProgramData.wLCN == INVALID_LOGICAL_CHANNEL_NUMBER)
      )
    {
    #if (ENABLE_CI_PLUS)
        if( FALSE == msAPI_SI_GetOpMode() )
    #endif
        {
            DTVProgramData.stCHAttribute.bValidLCN=FALSE;
        }
    }

    printf(" ---------------------------------\n");
    msDebug_ANSI_AllAttrOffText();

#if(ENABLE_S2)
    if(IsS2InUse())
        return msAPI_CM_AddS2Program(&DTVProgramData,bDBFull,bSkipCheck);
    else
#endif
        return msAPI_CM_AddProgram(&DTVProgramData,bDBFull,bSkipCheck);
}

WORD msAPI_SI_CountProgram(MEMBER_SI_SERVICETYPE bServiceType, SI_COUNT_PROGRAM_OPTION eCountOption)
{
    E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eCountType;
    switch(eCountOption)
    {
        case EXCLUDE_NOT_VISIBLE_AND_DELETED_SI:
            eCountType = E_PROGACESS_INCLUDE_VISIBLE_ONLY;
            break;
        case INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED_SI:
            eCountType = E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO;
            break;
        default:
            eCountType = E_PROGACESS_INCLUDE_ALL;
            break;
    }
    return msAPI_CM_CountProgram( msAPI_SI_ToCM_Service_Type(bServiceType), eCountType );
}

U8 msAPI_SI_GetCountOfSameServiceWithIDs(WORD wTransportStream_ID, WORD wOriginalNetwork_ID, WORD wService_ID)
{
    return msAPI_CM_GetCountOfSameServiceWithIDs(wTransportStream_ID, wOriginalNetwork_ID, wService_ID);
}

BOOLEAN msAPI_SI_GetServiceName(MEMBER_SI_SERVICETYPE bServiceType, WORD wPosition, BYTE * bChannelName, U16 *pMaxLen)
{
    MEMBER_SERVICETYPE bType;
    BOOLEAN bResult;
    U8 au8CurServiceName[MAX_SERVICE_NAME]={0};
    bType = msAPI_SI_ToCM_Service_Type(bServiceType);
    bResult = msAPI_CM_GetServiceName(bType, wPosition, au8CurServiceName);
    memcpy(bChannelName,au8CurServiceName,SI_MAX_SERVICE_NAME > MAX_SERVICE_NAME ? MAX_SERVICE_NAME : SI_MAX_SERVICE_NAME);
    *pMaxLen=MAX_SERVICE_NAME;
    return bResult;
}

BOOLEAN msAPI_SI_Get_CELL_ID( WORD * pwCell_id)
{
    return msAPI_Tuner_Get_CELL_ID(pwCell_id);
}

BOOLEAN msAPI_SI_Get_PLP_ID( U8 * pu8PLP_ID)
{
#if (ENABLE_DVB_T2)
    return msAPI_Tuner_Get_PLP_ID(pu8PLP_ID);
#else
    *pu8PLP_ID=0;
    return FALSE;
#endif
}

U8 msAPI_SI_Get_HpLp( void)
{
#if (ENABLE_HIERARCHY)
    return msAPI_Tuner_Get_HpLp();
#else
       return 0;
#endif
}

BOOLEAN msAPI_SI_IsServiceExistWithIDsAndLCN(WORD wOriginalNetwork_ID, WORD wService_ID,  WORD wLCN)
{
    return msAPI_CM_IsServiceExistWithIDsAndLCN(wOriginalNetwork_ID, wService_ID,  wLCN);
}

BOOLEAN msAPI_SI_UpdateProgramVisibleAndSelectable(MEMBER_SI_SERVICETYPE bServiceType, WORD wPosition, BOOLEAN bVisible, BOOLEAN bSelectable)
{
    MEMBER_SERVICETYPE bType;
    bType=msAPI_SI_ToCM_Service_Type(bServiceType);

    return msAPI_CM_UpdateProgramVisibleAndSelectable(bType, wPosition, bVisible, bSelectable);
}

BOOLEAN msAPI_SI_UpdateProgramSpecialService(MEMBER_SI_SERVICETYPE bServiceType, WORD wPosition, BOOLEAN bSpecialService)
{
    MEMBER_SERVICETYPE bType;
    bType=msAPI_SI_ToCM_Service_Type(bServiceType);

    return msAPI_CM_UpdateProgramSpecialService(bType, wPosition, bSpecialService);
}

//#if ENABLE_DVBC
BOOLEAN msAPI_SI_UpdateQuickInstallProgram(MEMBER_SI_SERVICETYPE bServiceType, WORD wPosition, SI_DTV_CHANNEL_INFO *pstDtvPgmData)
{
#if ENABLE_DVBC
    DTV_CHANNEL_INFO ChannelInfo;
    MEMBER_SERVICETYPE bType;
    SI_DTV_CHANNEL_INFO stDtvPgmData;

    if( !IsDVBCInUse() )
        return FALSE;

    bType=msAPI_SI_ToCM_Service_Type(bServiceType);

    if(msAPI_CM_GetProgramInfo(bType,wPosition,&ChannelInfo) == FALSE)
    {
        return FALSE;
    }

    memcpy(&stDtvPgmData,pstDtvPgmData,sizeof(SI_DTV_CHANNEL_INFO));
    //MApp_SI_GetString(ChannelInfo.bChannelName, MAX_SERVICE_NAME, stDtvPgmData.bChannelName, SI_MAX_SERVICE_NAME, KEEP_CONTROL_CODE_CR_LF);
    memcpy(ChannelInfo.bChannelName,stDtvPgmData.bChannelName,SI_MAX_SERVICE_NAME > MAX_SERVICE_NAME ? MAX_SERVICE_NAME : SI_MAX_SERVICE_NAME);
    ChannelInfo.bChannelName[(SI_MAX_SERVICE_NAME > MAX_SERVICE_NAME ? MAX_SERVICE_NAME : SI_MAX_SERVICE_NAME)-1]=0;
    ChannelInfo.wLCN = stDtvPgmData.wLCN;
#if 1//NTV_FUNCTION_ENABLE
    ChannelInfo.wTS_LCN= stDtvPgmData.wTS_LCN;
#endif
    ChannelInfo.wSimu_LCN = stDtvPgmData.wSimu_LCN;
    ChannelInfo.stCHAttribute.bServiceType = stDtvPgmData.stCHAttribute.bServiceType;
    ChannelInfo.stCHAttribute.bVisibleServiceFlag = stDtvPgmData.stCHAttribute.bVisibleServiceFlag;
    ChannelInfo.bIDIdex = stDtvPgmData.bIDIdex;
    return msAPI_CM_UpdateProgram(bType,wPosition,(BYTE *)&ChannelInfo,E_DATA_ALL);

#else

    UNUSED(bServiceType);
    UNUSED(wPosition);
    UNUSED(pstDtvPgmData);

    return FALSE;
#endif
}
//#endif

BOOLEAN msAPI_SI_UpdateProgram(MEMBER_SI_SERVICETYPE bServiceType, WORD wPosition, BYTE *pcBuffer, E_SI_DATA_MEMBER eMember)
{
    MEMBER_SERVICETYPE bType;
    DTV_CHANNEL_INFO ChannelInfo;
    SI_DTV_CHANNEL_INFO stDtvPgmData;
    U8 member;
    bType=msAPI_SI_ToCM_Service_Type(bServiceType);

    switch(eMember)
    {
        case E_SI_REPLACE_SERVICE:
            member=E_DATA_REPLACE_SERVICE;
            break;
        case E_SI_DATA_SERVICE_NAME:
#if(ASTRA_HD_ENABLE)
            if(GetASTRA_HD_ENABLE())
            {
                member=E_DATA_SERVICE_NAME;
                break;
            }
#endif
               #if(ENABLE_S2_PREDIT_RENAME)
            if(!ISDVBS2Source())
        #endif
            {
            member=E_DATA_SERVICE_NAME;
            }
        #if(ENABLE_S2_PREDIT_RENAME)
          else
           {
                MS_DEBUG_MSG(printf("msAPI_SI_UpdateProgram unsupport member %d\n",eMember));
                return FALSE;
            }
          #endif
            break;
#if(MHEG5_SIINFO_ENABLE)
        case E_SI_DATA_PROVIDER_NAME:
        member=E_DATA_PROVIDER_NAME;
        break;
#endif //#if(MHEG5_SIINFO_ENABLE)
        case E_SI_DATA_LCN:
            member=E_DATA_LCN;
            break;
        case E_SI_DATA_SIMU_LCN:
            member=E_DATA_SIMU_LCN;
            break;
        case E_SI_DATA_VERSION_SDT:
#if(ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
        case E_SI_DATA_VERSION_SGT:
#endif  //#if(ASTRA_HD_ENABLE)
            member=E_DATA_VERSION_SDT;
            break;

#if(ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
            case E_SI_DATA_PID_SGT:
                member=E_DATA_SGT_PID;
                break;
            case E_SI_DATA_MISC:
                member=E_DATA_MISC;
                break;
#endif  //#if(ASTRA_HD_ENABLE)

        case E_SI_DATA_VERSION_PAT:
            member=E_DATA_VERSION_PAT;
            break;
        case E_SI_DATA_VERSION_PMT:
            member=E_DATA_VERSION_PMT;
            break;
        case E_SI_DATA_VERSION_NIT:
            member=E_DATA_VERSION_NIT;
            break;
        case E_SI_DATA_ON_ID:
            member=E_DATA_ON_ID;
            break;
        case E_SI_DATA_TS_ID:
            member=E_DATA_TS_ID;
            break;
        case E_SI_DATA_TS_LCN:
            member=E_DATA_TS_LCN;
            break;
        case E_SI_DATA_ALL_EXCLUDE_MULTILINGUAL_NAME:
        case E_SI_DATA_ALL:
            if(msAPI_CM_GetProgramInfo(bType,wPosition,&ChannelInfo) == FALSE)
            {
                return FALSE;
            }
            memcpy(&stDtvPgmData,pcBuffer,sizeof(SI_DTV_CHANNEL_INFO));
            //ChannelInfo.bIDIdex=pDtvPgmData.bIDIdex;
            ChannelInfo.wPCR_PID=stDtvPgmData.wPCR_PID;
            ChannelInfo.wVideo_PID=stDtvPgmData.wVideo_PID;
            ChannelInfo.wLCN=stDtvPgmData.wLCN;
            ChannelInfo.wPmt_PID=stDtvPgmData.wPmt_PID;
            ChannelInfo.wService_ID=stDtvPgmData.wService_ID;
#if 1//NTV_FUNCTION_ENABLE
            ChannelInfo.wTS_LCN=stDtvPgmData.wTS_LCN;
#endif
            ChannelInfo.wSimu_LCN=stDtvPgmData.wSimu_LCN;

            ChannelInfo.stPSI_SI_Version.bNITVer=stDtvPgmData.stPSI_SI_Version.bNITVer;
            ChannelInfo.stPSI_SI_Version.bPATVer=stDtvPgmData.stPSI_SI_Version.bPATVer;
            ChannelInfo.stPSI_SI_Version.bSDTVer=stDtvPgmData.stPSI_SI_Version.bSDTVer;
            ChannelInfo.stPSI_SI_Version.bPMTVer=stDtvPgmData.stPSI_SI_Version.bPMTVer;


            ChannelInfo.stCHAttribute.wSignalStrength=stDtvPgmData.stCHAttribute.wSignalStrength;
            ChannelInfo.stCHAttribute.bValidLCN=stDtvPgmData.stCHAttribute.bValidLCN;

            ChannelInfo.stCHAttribute.bVisibleServiceFlag=stDtvPgmData.stCHAttribute.bVisibleServiceFlag;
            ChannelInfo.stCHAttribute.bNumericSelectionFlag=stDtvPgmData.stCHAttribute.bNumericSelectionFlag;
            ChannelInfo.stCHAttribute.bIsScramble=stDtvPgmData.stCHAttribute.bIsScramble;
            ChannelInfo.stCHAttribute.bIsStillPicture=stDtvPgmData.stCHAttribute.bIsStillPicture;
            ChannelInfo.stCHAttribute.bReplaceService=stDtvPgmData.stCHAttribute.bReplaceService;

            ChannelInfo.stCHAttribute.bIsServiceIdOnly=stDtvPgmData.stCHAttribute.bIsServiceIdOnly;
            ChannelInfo.stCHAttribute.bIsReplaceDel=stDtvPgmData.stCHAttribute.bIsReplaceDel;
            ChannelInfo.stCHAttribute.bServiceTypePrio=msAPI_SI_ToCM_Service_Priority(stDtvPgmData.stCHAttribute.bServiceTypePrio);
            ChannelInfo.stCHAttribute.eVideoType=msAPI_SI_ToCM_Video_Type(stDtvPgmData.stCHAttribute.eVideoType);
            ChannelInfo.stCHAttribute.bServiceType=(U8)msAPI_SI_ToCM_Service_Type((MEMBER_SI_SERVICETYPE)stDtvPgmData.stCHAttribute.bServiceType);
            ChannelInfo.stCHAttribute.bServiceTypePrio=msAPI_SI_ToCM_Service_Priority(stDtvPgmData.stCHAttribute.bServiceTypePrio);
            ChannelInfo.stCHAttribute.bInvalidService=stDtvPgmData.stCHAttribute.bInvalidService;

#if(ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
            ChannelInfo.stCHAttribute.bIsNewService=stDtvPgmData.stCHAttribute.bIsNewService;
            ChannelInfo.wSgt_PID=stDtvPgmData.wSgt_PID;
#endif

        #if ENABLE_SAVE_MULTILINGUAL_SERVICE_NAME
            if(E_SI_DATA_ALL == eMember)
            {
                U8 i;
                EN_SI_LANGUAGE eLanguage;
                memset(ChannelInfo.bMultiChannelName,0,sizeof(BYTE)*MAX_MULTI_LINGUAL_SERVICE_NAME*MAX_SERVICE_NAME);
                for(i=0;i<MAX_MULTI_LINGUAL_SERVICE_NAME;i++)
                {
                    ChannelInfo.bMultiLanguage[i]=(BYTE)INVALID_LANG_INDEX;//LANGUAGE_NONE;
                    if(MApp_SI_GetMultiLingualServiceNameByID(ChannelInfo.wService_ID,i,&eLanguage,
                        ChannelInfo.bMultiChannelName[i],MAX_SERVICE_NAME))
                    {
                        ChannelInfo.bMultiLanguage[i]=(BYTE)MApp_GetLanguageBySILanguage(eLanguage);
                    }
                }

            }
        #endif
            //MApp_SI_GetString(ChannelInfo.bChannelName, MAX_SERVICE_NAME, stDtvPgmData.bChannelName, SI_MAX_SERVICE_NAME, KEEP_CONTROL_CODE_CR_LF);
            memcpy(ChannelInfo.bChannelName,stDtvPgmData.bChannelName,SI_MAX_SERVICE_NAME > MAX_SERVICE_NAME ? MAX_SERVICE_NAME : SI_MAX_SERVICE_NAME);
            //ChannelInfo.bChannelName[(SI_MAX_SERVICE_NAME > MAX_SERVICE_NAME ? MAX_SERVICE_NAME : SI_MAX_SERVICE_NAME)-1]=0;


        {
            U8 maxAudio = MAX_AUD_LANG_NUM > SI_MAX_AUD_LANG_NUM ? SI_MAX_AUD_LANG_NUM : MAX_AUD_LANG_NUM;

        #if 1 // Use new API

            msAPI_SI_Copy_SI_AudInfo_To_CM_AudInfo(stDtvPgmData.stAudInfo, ChannelInfo.stAudInfo, maxAudio);
        #else

            U8 maxISO = MAX_AUD_ISOLANG_NUM > SI_MAX_AUD_ISOLANG_NUM ? SI_MAX_AUD_ISOLANG_NUM : MAX_AUD_ISOLANG_NUM;
            U8 i,j;

            for(i=0;i<maxAudio;i++)
            {
                //ChannelInfo.stAudInfo[i].wAudType = msAPI_SI_ToCM_Audio_Type(stDtvPgmData.stAudInfo[i].wAudType);
                ChannelInfo.stAudInfo[i].eSIAudType = (SI_AUDIOSTREAM_TYPE)stDtvPgmData.stAudInfo[i].wAudType;
                printf("\n[[In1_%x  out_%x",stDtvPgmData.stAudInfo[i].wAudType, ChannelInfo.stAudInfo[i].eSIAudType);

                ChannelInfo.stAudInfo[i].wAudPID=stDtvPgmData.stAudInfo[i].wAudPID;

            #if 1//NTV_FUNCTION_ENABLE
                //ChannelInfo.stAudInfo[i].u8ProfileAndLevel=stDtvPgmData.stAudInfo[i].u8ProfileAndLevel;
                ChannelInfo.stAudInfo[i].eProfileAndLevel = msAPI_SI_ToCM_ProfileAndLevel(stDtvPgmData.stAudInfo[i].u8ProfileAndLevel);

                //ChannelInfo.stAudInfo[i].u8Component_AAC_Type=stDtvPgmData.stAudInfo[i].u8Component_AAC_Type;
            #endif
                for(j=0;j<maxISO;j++)
                {
                    ChannelInfo.stAudInfo[i].aISOLangInfo[j].bISOLangIndex=stDtvPgmData.stAudInfo[i].aISOLangInfo[j].bISOLangIndex;
                    ChannelInfo.stAudInfo[i].aISOLangInfo[j].bISOLanguageInfo=msAPI_SI_ToCM_Audio_Mode(stDtvPgmData.stAudInfo[i].aISOLangInfo[j].bISOLanguageInfo);
                    ChannelInfo.stAudInfo[i].aISOLangInfo[j].bAudType=stDtvPgmData.stAudInfo[i].aISOLangInfo[j].bAudType;
                    ChannelInfo.stAudInfo[i].aISOLangInfo[j].bIsValid=stDtvPgmData.stAudInfo[i].aISOLangInfo[j].bIsValid;
                    ChannelInfo.stAudInfo[i].aISOLangInfo[j].bBroadcastMixedAD=stDtvPgmData.stAudInfo[i].aISOLangInfo[j].bBroadcastMixedAD;
                    ChannelInfo.stAudInfo[i].aISOLangInfo[j].bReserved=stDtvPgmData.stAudInfo[i].aISOLangInfo[j].bReserved;
                }
            }
        #endif
        }


            pcBuffer=(BYTE *)&ChannelInfo;
            member=E_DATA_ALL;
            break;

    #if(ENABLE_S2_FAST_SCAN)
            case E_SI_DATA_FNT_NETWORK_ID:
            member=E_DATA_NETWORK_ID;
            break;
    #endif //  #if(ENABLE_S2_FAST_SCAN)

            default:
                printf("msAPI_SI_UpdateProgram unsupport member %d\n",eMember);
                return FALSE;
    }

#if ENABLE_CI
    if((eMember == E_SI_DATA_SERVICE_NAME)&&(MApp_CI_IsOpMode()==TRUE))
    {
        printf("ci op mode,not update service name!\n");
        return FALSE;
    }
    else
#endif
    return msAPI_CM_UpdateProgram(bType,wPosition,pcBuffer,member);
}


BOOLEAN msAPI_SI_ArrangeDataManager(void)
{
    return msAPI_CM_ArrangeDataManager(TRUE,FALSE);
}
void msAPI_SI_Reset_AudioValidIndex(void)
{
    msAPI_CM_Reset_AudioValidIndex();
}
U16 msAPI_SI_GetCurrentSignalStrength(void)
{
    U16 wSignalQualityStrength = 0;
    msAPI_Tuner_CheckSignalStrength(&wSignalQualityStrength);
    wSignalQualityStrength = (wSignalQualityStrength&0xFF)<<8;
    wSignalQualityStrength |= (msAPI_Tuner_GetSignalQualityPercentage()&0xFF);
    return wSignalQualityStrength;
}

U32 msAPI_SI_Timer_DiffTimeFromNow(U32 u32TaskTimer) //unit = ms
{
    return msAPI_Timer_DiffTimeFromNow(u32TaskTimer);
}
U32 msAPI_SI_Timer_GetTime(void)
{
    return msAPI_Timer_GetTime0();
}
U32 msAPI_SI_Timer_DiffTime(U32 u32Timer, U32 u32TaskTimer)
{
    return msAPI_Timer_DiffTime(u32Timer, u32TaskTimer);
}
void msAPI_SI_Timer_ResetWDT(void)
{
    msAPI_Timer_ResetWDT();
}
void msAPI_SI_Timer_Delayms(U32 u32DelayTime) //unit = ms
{
    msAPI_Timer_Delayms(u32DelayTime);
}
void * msAPI_SI_Memory_Allocate(U16 u16Number_of_bytes)
{
    return msAPI_Memory_Allocate(u16Number_of_bytes, BUF_ID_SI_DEFAULT);
}
U8 msAPI_SI_Memory_Free(void *pFree)
{
    return msAPI_Memory_Free(pFree, BUF_ID_SI_DEFAULT);
}
S32 msAPI_SI_Timer_GetOffsetTime(void)
{
    return msAPI_Timer_GetOffsetTime();
}
void msAPI_SI_Timer_SetSystemTime(U32 u32SystemTime) //unit = sec
{
    DEBUG_WAKE_UP( printf("msAPI_SI_Timer_SetSystemTime(u32SystemTime=%u)\n", u32SystemTime); );

    msAPI_Timer_SetSystemTime(u32SystemTime);
}
void msAPI_SI_Timer_SetOffsetTime(S32 s32OffsetTime) //unit = sec
{
    msAPI_Timer_SetOffsetTime(s32OffsetTime);
}
U32 msAPI_SI_Timer_GetSystemTime(void)
{
    return msAPI_Timer_GetSystemTime();
}
U16 MApp_SI_CharTable_MappingDVBTextToUCS2(U8 *pu8Str, U16 *pu16Str, U16 srcByteLen, U16 dstWideCharLen, BOOLEAN bRemoveHyphen)
{
#if (BLOADER)
    UNUSED(pu8Str);
    UNUSED(pu16Str);
    UNUSED(srcByteLen);
    UNUSED(dstWideCharLen);
    UNUSED(bRemoveHyphen);
    return 0;
#else
    return MApp_CharTable_MappingDVBTextToUCS2(pu8Str, pu16Str, srcByteLen, dstWideCharLen, bRemoveHyphen ? REMOVE_00AD_SOFT_HYPHEN : REMOVE_NONE);
#endif
}

BOOLEAN msAPI_SI_CreateMutex(U8 u8MutexID)
{
#if ENABLE_MUTEX
    char name[20];
    snprintf(name,20,"SI_MUTEX-%d",u8MutexID);
    if (-1 == (_aSI_MUTEX_ID[u8MutexID] = MsOS_CreateMutex(E_MSOS_FIFO, name, MSOS_PROCESS_PRIVATE)))
    {
        __ASSERT(0);
        return FALSE;
    }
    return TRUE;
#else
    UNUSED(u8MutexID);
    return TRUE;
#endif
}
//static MS_S32 _aSI_MUTEX_ID_dbg[E_SI_MUTEX_MAX];
BOOLEAN msAPI_SI_WaitMutex(U8 u8MutexID)
{
#if ENABLE_MUTEX
    //if(_aSI_MUTEX_ID_dbg[u8MutexID])printf("wait mutex err %d\n",u8MutexID);
    //_aSI_MUTEX_ID_dbg[u8MutexID]=1;
    return  MsOS_ObtainMutex(_aSI_MUTEX_ID[u8MutexID],MSOS_WAIT_FOREVER);
#else
    UNUSED(u8MutexID);
    return TRUE;
#endif
}
BOOLEAN msAPI_SI_ReleaseMutex(U8 u8MutexID)
{
#if ENABLE_MUTEX
    //if(_aSI_MUTEX_ID_dbg[u8MutexID] == 0)printf("release mutex err %d\n",u8MutexID);
    //_aSI_MUTEX_ID_dbg[u8MutexID]=0;
    return MsOS_ReleaseMutex(_aSI_MUTEX_ID[u8MutexID]);
#else
    UNUSED(u8MutexID);
    return TRUE;
#endif
}

BOOLEAN msAPI_SI_SetMismatchedCell(WORD wONID, WORD wTSID, WORD *pCellLsit, U8 u8CellNumber, BOOLEAN *bRemoved)
{
#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
    if(OSD_COUNTRY_SETTING == OSD_COUNTRY_NEWZEALAND)
    {
        return msAPI_CM_SetMismatchedCell(wONID, wTSID, pCellLsit,  u8CellNumber, bRemoved);
    }
    else
    {
        wONID=wONID;
        wTSID=wTSID;
        pCellLsit=pCellLsit;
        u8CellNumber=u8CellNumber;
        bRemoved=bRemoved;
        return FALSE;
    }
#else
    wONID=wONID;
    wTSID=wTSID;
    pCellLsit=pCellLsit;
    u8CellNumber=u8CellNumber;
    bRemoved=bRemoved;
    return FALSE;
#endif
}

BOOLEAN msAPI_SI_SetNewAddCell(WORD wONID, WORD wTSID, WORD *pCellLsit, U8 u8CellNumber, BOOLEAN *bRemoved)
{
#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
    if(OSD_COUNTRY_SETTING == OSD_COUNTRY_NEWZEALAND)
    {
        return msAPI_CM_SetMismatchedCell(wONID, wTSID, pCellLsit,  u8CellNumber, bRemoved);
    }
    else
    {
        wONID=wONID;
        wTSID=wTSID;
        pCellLsit=pCellLsit;
        u8CellNumber=u8CellNumber;
        bRemoved=bRemoved;
        return FALSE;
    }
#else
    wONID=wONID;
    wTSID=wTSID;
    pCellLsit=pCellLsit;
    u8CellNumber=u8CellNumber;
    bRemoved=bRemoved;
    return FALSE;
#endif
}

BOOLEAN msAPI_SI_RemoveMismatchedMux(WORD wNID, WORD *pwTS_ID,  BYTE cCountOfTS, U32 *u32NewTS, BOOLEAN bRemove)
{
#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
    if(msAPI_SI_IsSpecificCountry(MApp_GetSICountry(OSD_COUNTRY_SETTING),SI_SUPPORT_NETWORK_UPDATE_SPECIFIC_COUNTRY))
    {
        return msAPI_CM_RemoveMismatchedMux(wNID, pwTS_ID,  cCountOfTS, u32NewTS, bRemove);
    }
    else
    {
        wNID=wNID;
        pwTS_ID=pwTS_ID;
        cCountOfTS=cCountOfTS;
        u32NewTS=u32NewTS;
        bRemove=bRemove;
        return FALSE;
    }
#else
    wNID=wNID;
    pwTS_ID=pwTS_ID;
    cCountOfTS=cCountOfTS;
    u32NewTS=u32NewTS;
    bRemove=bRemove;
    return FALSE;
#endif
}
BOOLEAN msAPI_SI_CheckNetwork(WORD wNID, WORD *pwTS_ID,  BYTE cCountOfTS, U32 *u32NewTS, WORD *pwRemoveTSID, BYTE cMaxTSCnt, BOOLEAN *bRemove)
{
#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
    if((msAPI_SI_IsSpecificCountry(MApp_GetSICountry(OSD_COUNTRY_SETTING),SI_SUPPORT_NETWORK_UPDATE_SPECIFIC_COUNTRY))
        || (msAPI_SI_IsSpecificCountry(MApp_GetSICountry(OSD_COUNTRY_SETTING),SI_SUPPORT_DVB_C_NETWORK_UPDATE_SPECIFIC_COUNTRY)))
    {
        return msAPI_CM_CheckNetwork(wNID, pwTS_ID,  cCountOfTS, u32NewTS, pwRemoveTSID, cMaxTSCnt, bRemove);
    }
    else
    {
        wNID=wNID;
        pwTS_ID=pwTS_ID;
        cCountOfTS=cCountOfTS;
        u32NewTS=u32NewTS;
        bRemove=bRemove;
        return FALSE;
    }
#else
    wNID=wNID;
    pwTS_ID=pwTS_ID;
    cCountOfTS=cCountOfTS;
    u32NewTS=u32NewTS;
    bRemove=bRemove;
    pwRemoveTSID = pwRemoveTSID;
    cMaxTSCnt = cMaxTSCnt;
    return FALSE;
#endif
}
BOOLEAN msAPI_SI_SetUnconfirmedServiceInvalid(WORD wONID, WORD wTSID, BOOLEAN *bGotService)
{
#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
    if(msAPI_SI_IsSpecificCountry(MApp_GetSICountry(OSD_COUNTRY_SETTING),SI_SUPPORT_NETWORK_UPDATE_SPECIFIC_COUNTRY))
    {
        return msAPI_CM_SetUnconfirmedServiceInvalid(wONID, wTSID, bGotService);
    }
    else
    {
        wONID=wONID;
        wTSID=wTSID;
        bGotService=bGotService;
        return FALSE;
    }
#else
    wONID=wONID;
    wTSID=wTSID;
    bGotService=bGotService;
    return FALSE;
#endif
}

WORD MApp_SI_Get_Video_PID(void)//remove after CI
{
    return 0;
}

void msAPI_SI_UpdateNetworkName(WORD wNID, U8 *pu8NetwrokName, U8 u8NetworkNameLen)
{
    U8 tempNetworkName[MAX_NETWORK_NAME];

    if (NULL == pu8NetwrokName)
        return;

    memset(tempNetworkName, '\0', MAX_NETWORK_NAME);
    MApp_SI_GetString(tempNetworkName, MAX_NETWORK_NAME-1, pu8NetwrokName, u8NetworkNameLen, KEEP_CONTROL_CODE_ALL);
    msAPI_CM_UpdateNetworkNameWithNID(wNID, tempNetworkName);
}


static U8 _Ms_tolower ( U8 InChar )
{
    if ( InChar >='A'  &&  InChar <='Z')
        InChar=(InChar-'A')+'a';
    return( InChar );
}
//****************************************************************************
/// Get ISO639 language code
/// @param pSrc \b IN: point of ISO639 language
/// @return EN_LANGUAGE : language code
//****************************************************************************
EN_SI_LANGUAGE msAPI_SI_GetLanguageByISO639LangCode(U8 *pSrc)
{
    U8  i,
        nums;
    U8 u8LangCode[3];

    for(i=0;i<3;i++)
    {
        u8LangCode[i] = _Ms_tolower(pSrc[i]);
        //u8LangCode[i] = tolower(pSrc[i]);
    }
    nums=sizeof(iso639_LanguageCode)/sizeof(ST_ISO639_LANG);


    for(i=0; i<nums; i++)
    {
       if(memcmp(u8LangCode, iso639_LanguageCode[i].au8LangCode, 3) == 0)
       {
            return iso639_LanguageCode[i].enLangIndex;
       }
    }

    for(i=0; i<nums; i++)
    {
       if(memcmp(u8LangCode, iso639_LanguageCode[i].au8LangCode, 2) == 0)
       {
            return iso639_LanguageCode[i].enLangIndex;
       }
    }

    return SI_LANGUAGE_UNKNOWN;
}

EN_SI_COUNTRY_SETTING msAPI_SI_GetCountryByTimeZone(EN_SI_TIMEZONE eTimeZone)
{
    U8 u8Loop;

    //printf("Total = %bu\n",sizeof(stTimeZone2Country)/sizeof(TimeZone2Country));
    for(u8Loop = 0; u8Loop < sizeof(stTimeZone2Country)/sizeof(TimeZone2Country); u8Loop++)
    {
        if(stTimeZone2Country[u8Loop].eTimeZone == eTimeZone)
            return stTimeZone2Country[u8Loop].eCountry;
    }
    return SI_COUNTRY_UK; // Unknow timezone, return UK.
}
//****************************************************************************
/// Get Time Zone via country
/// @param eCountry \b IN: country
/// -@see EN_SI_COUNTRY_SETTING
/// @return EN_SI_TIMEZONE : time zone
//****************************************************************************
EN_SI_TIMEZONE msAPI_SI_GetTimeZoneByCountry(EN_SI_COUNTRY_SETTING eCountry)
{
    U8 u8Loop;

    //printf("Total = %bu\n",sizeof(stTimeZone2Country)/sizeof(TimeZone2Country));
    for(u8Loop = 0; u8Loop < sizeof(stTimeZone2Country)/sizeof(TimeZone2Country); u8Loop++)
    {
        if(stTimeZone2Country[u8Loop].eCountry == eCountry)
            return stTimeZone2Country[u8Loop].eTimeZone;
            }
    return SI_TIMEZONE_LONDON; // Unknow timezone, return UK.
}


//****************************************************************************
/// Get ISO3166 country code
/// @param pSrc \b IN: point of ISO3166 country
/// @return EN_SI_COUNTRY_SETTING : country code
//****************************************************************************
EN_SI_COUNTRY_SETTING msAPI_SI_GetCountryByISO3166CountryCode(U8 *pSrc)
{
    U8 i;
    U8 tmp[3];
    for(i=0;i<3;i++)//transfer to upper case
    {
        tmp[i]=(pSrc[i]>='a' && pSrc[i]<='z')?pSrc[i]-32:pSrc[i];
    }
    for(i = 0; i < COUNTRY_CODE_NUM; i++)
    {
        if(!memcmp(tmp,iso3166_CountryCode[i],3))
        {
            return (EN_SI_COUNTRY_SETTING)iso3166_CountryCode[i][3];
        }
    }
    return SI_COUNTRY_NUMS;
}
BOOLEAN msAPI_SI_GetISO3166CountryCodeFromIndex(EN_SI_COUNTRY_SETTING enIndex, U8 *pBuf)
{
    U8 i;

    for(i = 0; i < COUNTRY_CODE_NUM; i++)
    {
        if(iso3166_CountryCode[i][3] == enIndex)
        {
            memcpy(pBuf,iso3166_CountryCode[i],3);
            return TRUE;
        }
    }
    return FALSE;
}
//****************************************************************************
/// Get ISO language code from language
/// @param enIndex \b IN: language
/// -@see EN_LANGUAGE
/// @param pBuf \b IN: point of output
/// @return BOOLEAN :
/// - 1: success
/// - 0: failed
//****************************************************************************
BOOLEAN msAPI_SI_GetISOLangCodeFromIndex(EN_SI_LANGUAGE enIndex, U8 *pBuf)
{
    U8 i, nums;

    nums=sizeof(iso639_LanguageCode)/sizeof(ST_ISO639_LANG);
    for(i=0; i<nums; i++)
    {
        if(iso639_LanguageCode[i].enLangIndex == enIndex)
        {
            memcpy(pBuf,iso639_LanguageCode[i].au8LangCode,SI_MAX_ISO639CODE_LENGTH);
            return TRUE;
        }
    }
    return FALSE;
}
U8 msAPI_SI_GetDefaultRegion(EN_SI_TIMEZONE eTimeZone)
{
    U8 u8Region=0;
    if(eTimeZone == SI_TIMEZONE_CANARY)
        u8Region = 2;
    else if(eTimeZone == SI_TIMEZONE_LISBON)
        u8Region = 1;
    else if(eTimeZone == SI_TIMEZONE_MADRID)
        u8Region = 1;
    else if(eTimeZone==SI_TIMEZONE_NSW)
        u8Region = 2;
    else if(eTimeZone==SI_TIMEZONE_VIC)
        u8Region = 3;
    else if(eTimeZone==SI_TIMEZONE_QLD)
        u8Region = 4;
    else if(eTimeZone==SI_TIMEZONE_SA)
        u8Region = 5;
    else if(eTimeZone==SI_TIMEZONE_WA)
        u8Region = 6;
    else if(eTimeZone==SI_TIMEZONE_TAS)
        u8Region = 7;
    else if(eTimeZone==SI_TIMEZONE_NT)
        u8Region = 8;
#if (ENABLE_SBTVD_SI)
    else if(eTimeZone==SI_TIMEZONE_AM_WEST)
        u8Region = 7;
    else if(eTimeZone==SI_TIMEZONE_ACRE)
        u8Region = 6;
    else if(eTimeZone==SI_TIMEZONE_M_GROSSO)
        u8Region = 5;
    else if(eTimeZone==SI_TIMEZONE_NORTH)
        u8Region = 4;
    else if(eTimeZone==SI_TIMEZONE_BRASILIA)
        u8Region = 3;
    else if(eTimeZone==SI_TIMEZONE_NORTHEAST)
        u8Region = 2;
    else if(eTimeZone==SI_TIMEZONE_F_NORONHA)
        u8Region = 1;
#endif
    return u8Region;
}

void msAPI_SI_GetCurrentRfParams(SI_DTVPROGRAMID *pstDtvIDTable)
{
#if 1//ENABLE_DVBC
    if (NULL == pstDtvIDTable)
        return;

  //#if ENABLE_T_C_COMBO
    //if( IsDVBCInUse() )
  //#endif
    {
        MS_TP_SETTING stCurTPsetting;

        // Coverity 186417
        memset(&stCurTPsetting,0,sizeof(MS_TP_SETTING));

        msAPI_Tuner_GetCurTPSetting(&stCurTPsetting);

        pstDtvIDTable->u32Frequency = stCurTPsetting.u32Frequency;
        pstDtvIDTable->QamMode = stCurTPsetting.u8Modulation;
        pstDtvIDTable->enBandWidth = stCurTPsetting.enBandWidth;
        pstDtvIDTable->u32SymbRate = stCurTPsetting.u32Symbol_rate;
    }
#else
   UNUSED(pstDtvIDTable);
#endif
}

void msAPI_SI_SetTargetRegionProgram(U16 u16ONID, U16 u16TSID, U16 u16SID, U8 u8Value)
{
#if ENABLE_TARGET_REGION
    msAPI_CM_SetRegion(u16ONID,u16TSID,u16SID,u8Value);
#else
    UNUSED(u16ONID);
    UNUSED(u16TSID);
    UNUSED(u16SID);
    UNUSED(u8Value);
#endif
}


BOOLEAN msAPI_SI_IsSpecificCountry(EN_SI_COUNTRY_SETTING eCountry, E_SI_SPECIFIC_COUNTRY eSpecificCountry)
{
    switch(eSpecificCountry)
    {
        case SI_THAILAND_SPECIFIC_COUNTRY:
            if(eCountry == SI_COUNTRY_THAILAND)
            {
                return TRUE;
            }
            return FALSE;
        case SI_EWS_SPECIFIC_COUNTRY:
            if(eCountry == SI_COUNTRY_INDONESIA)
            {
                return TRUE;
            }
            return FALSE;
        case SI_INDONESIA_SPECIFIC_COUNTRY:
            if(eCountry == SI_COUNTRY_INDONESIA)
            {
                return TRUE;
            }
            return FALSE;
        case SI_MALAYSIA_SPECIFIC_COUNTRY:
            if(eCountry == SI_COUNTRY_MALAYSIA)
            {
                return TRUE;
            }
            return FALSE;
        case SI_SINGAPORE_SPECIFIC_COUNTRY:
            if(eCountry == SI_COUNTRY_SINGAPORE)
            {
                return TRUE;
            }
            return FALSE;
        case SI_KENYA_SPECIFIC_COUNTRY:
            if(eCountry == SI_COUNTRY_KENYA)
            {
                return TRUE;
            }
            return FALSE;
        case SI_SUPPORT_HEVC_SPECIFIC_COUNTRY:
            if(eCountry == SI_COUNTRY_GERMANY)
            {
                return TRUE;
            }
            return FALSE;
        case SI_DTG_SPECIFIC_COUNTRY:
            if((eCountry == SI_COUNTRY_UK) ||
                (eCountry == SI_COUNTRY_NEWZEALAND))
            {
                return TRUE;
            }
            return FALSE;
        case SI_NORDIC_SPECIFIC_COUNTRY:
            if( (eCountry == SI_COUNTRY_FINLAND) ||
                (eCountry == SI_COUNTRY_SWEDEN) ||
                (eCountry == SI_COUNTRY_DENMARK) ||
                (eCountry == SI_COUNTRY_IRELAND) ||
                (eCountry == SI_COUNTRY_NORWAY)
             )
            {
                return TRUE;
            }
            return FALSE;
        case SI_FRANCE_SPECIFIC_COUNTRY:
            if(eCountry == SI_COUNTRY_FRANCE)
            {
                return TRUE;
            }
            return FALSE;
        case SI_NZ_SPECIFIC_COUNTRY:
            if(eCountry == SI_COUNTRY_NEWZEALAND)
            {
                return TRUE;
            }
            return FALSE;

            //Fix 1294987: [Marlon_120B#26][Antenna Ready HD]The receiver lack of one service "3 Test13 (Data channel)"
            //Finland country should display data channel
        case SI_NORWAY_SPECIFIC_COUNTRY:
            if((eCountry == SI_COUNTRY_NORWAY))
            {
                return TRUE;
            }
            return FALSE;
        case SI_SPAIN_SPECIFIC_COUNTRY:
            if(eCountry == SI_COUNTRY_SPAIN)
            {
                return TRUE;
            }
            return FALSE;
        case SI_SWEDEN_SPECIFIC_COUNTRY:
            if(eCountry == SI_COUNTRY_SWEDEN)
            {
                return TRUE;
            }
            return FALSE;
        case SI_UK_SPECIFIC_COUNTRY:
            if(eCountry == SI_COUNTRY_UK)
            {
                return TRUE;
            }
            return FALSE;
        case SI_USE_DEFAULT_TIMEZONE_SPECIFIC_COUNTRY:
            if((eCountry == SI_COUNTRY_AUSTRALIA) ||
                (eCountry == SI_COUNTRY_BRAZIL) )
            {
                return FALSE;
            }
            return TRUE;
        case SI_ITALY_SPECIFIC_COUNTRY:
            if(eCountry == SI_COUNTRY_ISRAEL)
            {
                return TRUE;
            }
            return FALSE;
        case SI_SIMULCN_SPECIFIC_COUNTRY:
            if((eCountry == SI_COUNTRY_UK) ||
                (eCountry == SI_COUNTRY_FRANCE)||
                (eCountry == SI_COUNTRY_PORTUGAL)||
                (eCountry == SI_COUNTRY_NETHERLANDS)
            )
            {
                return TRUE;
            }
            return FALSE;
        case SI_MHEG5_DATA_SERVICE_TO_TV_SPECIFIC_COUNTRY:
            return FALSE;
            if((eCountry == SI_COUNTRY_UK) ||
                (eCountry == SI_COUNTRY_NEWZEALAND)
                )
            {
                return TRUE;
            }
            return FALSE;
        case SI_SUPPORT_DATA_SERVICE_TYPE_SPECIFIC_COUNTRY:
            return TRUE;
            if((eCountry == SI_COUNTRY_UK) ||
                (eCountry == SI_COUNTRY_NEWZEALAND)
                )
            {
                return FALSE;
            }
            return TRUE;

        case SI_SUPPORT_NETWORK_UPDATE_SPECIFIC_COUNTRY:
#if ENABLE_UPDATE_MULTIPLEX_VIA_NIT
            if((eCountry == SI_COUNTRY_NORWAY)
             ||(eCountry == SI_COUNTRY_SWEDEN)
             ||(eCountry == SI_COUNTRY_NEWZEALAND)
             ||(eCountry == SI_COUNTRY_MALAYSIA)
             ||(eCountry == SI_COUNTRY_SINGAPORE)
             ||(eCountry == SI_COUNTRY_KUWAIT)
             ||(eCountry == SI_COUNTRY_OMAN)
             ||(eCountry == SI_COUNTRY_QATAR)
             ||(eCountry == SI_COUNTRY_SAUDI_ARABIA)
             ||(eCountry == SI_COUNTRY_GHANA)
             ||(eCountry == SI_COUNTRY_FINLAND)
             ||(eCountry == SI_COUNTRY_GERMANY))
            {
                return TRUE;
            }
#endif
            return FALSE;

        case SI_NETWORKUPDATE_WITHOUTONID_COUNTRY:
#if ENABLE_UPDATE_MULTIPLEX_VIA_NIT
            if((eCountry == SI_COUNTRY_KUWAIT)
             ||(eCountry == SI_COUNTRY_SWEDEN)
             ||(eCountry == SI_COUNTRY_OMAN)
             ||(eCountry == SI_COUNTRY_QATAR)
             ||(eCountry == SI_COUNTRY_SAUDI_ARABIA)
             ||(eCountry == SI_COUNTRY_UNITED_ARAB_EMIRATES)
             ||(eCountry == SI_COUNTRY_GHANA)
             ||(eCountry == SI_COUNTRY_FINLAND))
            {
                return TRUE;
            }
#endif
            return FALSE;
        case SI_SUPPORT_TTX_SERVICE_TYPE_SPECIFIC_COUNTRY:
            if(eCountry == SI_COUNTRY_UK)
            {
                return FALSE;
            }
            return TRUE;
        case SI_SUPPORT_SDT_OTHER_SPECIFIC_COUNTRY:
#if ENABLE_SDT_OTHER_MONITOR
            if((eCountry == SI_COUNTRY_NORWAY) ||
                (eCountry == SI_COUNTRY_NEWZEALAND) ||
                (eCountry == SI_COUNTRY_UK) ||
                (eCountry == SI_COUNTRY_MALAYSIA)||
                (eCountry == SI_COUNTRY_SINGAPORE)||
                (eCountry == SI_COUNTRY_NETHERLANDS)
                )
            {
                return TRUE;
            }
#endif
            return FALSE;
        case SI_IS_SI_BASE_SPECIFIC_COUNTRY:
            if((eCountry == SI_COUNTRY_NORWAY) ||
                (eCountry == SI_COUNTRY_SWEDEN) ||
                (eCountry == SI_COUNTRY_FINLAND) ||
                (eCountry == SI_COUNTRY_DENMARK) ||
                (eCountry == SI_COUNTRY_NEWZEALAND) ||
                (eCountry == SI_COUNTRY_UK)
                )
            {
                return TRUE;
            }
            return FALSE;

        case SI_IS_NIT_BASE_SPECIFIC_COUNTRY:
          #if (ENABLE_DVBC)
            if (IsDVBCInUse())
            {
               //if(yousee provider)return TRUE;
               return FALSE;
            }
          #endif
            return FALSE;

        case SI_SUPPORT_DVB_C_NETWORK_UPDATE_SPECIFIC_COUNTRY:
            #if ENABLE_DVBC
            if (IsDVBCInUse())
            {
                #if ENABLE_ZIGGO
                if((eCountry == SI_COUNTRY_NETHERLANDS)
                ||(eCountry == SI_COUNTRY_AUSTRIA)
                ||(eCountry == SI_COUNTRY_HUNGARY)
                ||(eCountry == SI_COUNTRY_POLAND)
                ||(eCountry == SI_COUNTRY_ROMANIA)
                ||(eCountry == SI_COUNTRY_SWITZERLAND)
                ||(eCountry == SI_COUNTRY_IRELAND))
                {
                    return TRUE;
                }
                #endif

                #if ENABLE_CANAL_DIGITAL
                if(eCountry == SI_COUNTRY_NORWAY)
                {
                    return TRUE;
                }
                #endif

                if(eCountry == SI_COUNTRY_GERMANY)
                {
                    return TRUE;
                }
            }
            #endif

            return FALSE;

        case SI_SUPPORT_ZIGGO_SPECIFIC_COUNTRY:
            {
                #if ENABLE_DVBC
                if (IsDVBCInUse())
                {
                    #if ENABLE_ZIGGO
                    if((eCountry == SI_COUNTRY_NETHERLANDS)
                    ||(eCountry == SI_COUNTRY_AUSTRIA)
                    ||(eCountry == SI_COUNTRY_HUNGARY)
                    ||(eCountry == SI_COUNTRY_POLAND)
                    ||(eCountry == SI_COUNTRY_ROMANIA)
                    ||(eCountry == SI_COUNTRY_SWITZERLAND)
                    ||(eCountry == SI_COUNTRY_IRELAND))
                    {
                        return TRUE;
                    }
                    #endif
                }
                #endif
            }
            return FALSE;

        case SI_EITPF_WITHOUT_SDTACTUAL:
            #if ENABLE_ZIGGO && ENABLE_DVBC
            if (IsDVBCInUse())
            {
                if(eCountry == SI_COUNTRY_NETHERLANDS)
                {
                    return TRUE;
                }
            }
            #endif

            if (IsDVBCInUse())
            {
                if(eCountry == SI_COUNTRY_GERMANY)
                {
                    return TRUE;
                }
            }
            return FALSE;

        case SI_IS_DEFAULT_BROADCAST_MIXED_SPECIFIC_COUNTRY:
          #if (ENABLE_DVBC)
            if (IsDVBCInUse())
            {
                if(eCountry == SI_COUNTRY_FINLAND)
                    return TRUE;//TRUE;
            }
          #endif
            return FALSE;

        case SI_IS_USE_SI_OTHER_COUNTRY:
            return TRUE;

        case SI_EUROPE_SPECIFIC_COUNTRY:
            if ((eCountry == SI_COUNTRY_AUSTRIA) || (eCountry == SI_COUNTRY_BELGIUM)
                || (eCountry == SI_COUNTRY_BULGARIA) || (eCountry == SI_COUNTRY_CROATIA)
                || (eCountry == SI_COUNTRY_CZECH) || (eCountry == SI_COUNTRY_DENMARK)
                || (eCountry == SI_COUNTRY_FINLAND) || (eCountry == SI_COUNTRY_FRANCE)
                || (eCountry == SI_COUNTRY_GERMANY) || (eCountry == SI_COUNTRY_GREECE)
                || (eCountry == SI_COUNTRY_HUNGARY) || (eCountry == SI_COUNTRY_ITALY)
                || (eCountry == SI_COUNTRY_LUXEMBOURG) || (eCountry == SI_COUNTRY_NETHERLANDS)
                || (eCountry == SI_COUNTRY_NORWAY) || (eCountry == SI_COUNTRY_POLAND)
                || (eCountry == SI_COUNTRY_PORTUGAL) || (eCountry == SI_COUNTRY_ROMANIA)
                || (eCountry == SI_COUNTRY_SERBIA) || (eCountry == SI_COUNTRY_SLOVENIA)
                || (eCountry == SI_COUNTRY_SPAIN) || (eCountry == SI_COUNTRY_SWEDEN)
                || (eCountry == SI_COUNTRY_SWITZERLAND) || (eCountry == SI_COUNTRY_UK)
                || (eCountry == SI_COUNTRY_ESTONIA) || (eCountry == SI_COUNTRY_TURKEY)
                || (eCountry == SI_COUNTRY_SLOVAKIA) || (eCountry == SI_COUNTRY_IRELAND))
            {
                return TRUE;
            }
            return FALSE;
        case SI_AUSTRALIA_SPECIFIC_COUNTRY:
            if(eCountry == SI_COUNTRY_AUSTRALIA)
            {
                return TRUE;
            }
            return FALSE;
        case SI_UNITED_ARAB_EMIRATES_SPECIFIC_COUNTRY:
            if(eCountry == SI_COUNTRY_UNITED_ARAB_EMIRATES)
            {
                return TRUE;
            }
            return FALSE;
        case SI_LCN2_SPECIFIC_COUNTRY:
            if((eCountry == SI_COUNTRY_MALAYSIA)
             ||(eCountry == SI_COUNTRY_SINGAPORE)
             ||(eCountry == SI_COUNTRY_KUWAIT)
             ||(eCountry == SI_COUNTRY_OMAN)
             ||(eCountry == SI_COUNTRY_QATAR)
             ||(eCountry == SI_COUNTRY_SAUDI_ARABIA)
             ||(eCountry == SI_COUNTRY_UNITED_ARAB_EMIRATES)
             ||(eCountry == SI_COUNTRY_GHANA)
             ||(eCountry == SI_COUNTRY_THAILAND))
            {
                return TRUE;
            }
            return FALSE;
        case SI_SUPPPORT_USERTYPE_SERVICE_SPECIFIC_COUNTRY:
            if(eCountry == SI_COUNTRY_CHINA)
            {
                return TRUE;
            }
            return FALSE;
        case SI_NO_LCN_SPECIFIC_COUNTRY:
            if((eCountry == SI_COUNTRY_CHINA) ||
                (eCountry == SI_COUNTRY_RUSSIA))
            {
                return TRUE;
            }
            return FALSE;
        case SI_SUPPORT_LCN_ZERO_SPECIFIC_COUNTRY:
        if(eCountry == SI_COUNTRY_NETHERLANDS)
            {
                return TRUE;
            }
            return FALSE;
        case SI_NETWORKUPDATE_ADD_SERVICE_WITH_LCN:
            if(eCountry == SI_COUNTRY_NETHERLANDS)
            {
                return TRUE;
            }
            return FALSE;
        case SI_SUPPORT_14BIT_LCN_SPECIFIC_COUNTRY:
#if ENABLE_CI_PLUS_V1_4
            if(eCountry == SI_COUNTRY_GERMANY)
            {
                return FALSE;
            }
#else
            if(eCountry == SI_COUNTRY_GERMANY)
            {
                return TRUE;
            }
#endif
            return FALSE;
       case SI_EPGINFO_WITHOUT_CHECK_TIME:
            if(eCountry == SI_COUNTRY_GHANA)
            {
                return TRUE;
            }
            return FALSE;
        case SI_FORCE_PRD_COUNTRYCODE:
                if((eCountry == SI_COUNTRY_SINGAPORE)||
                    (eCountry == SI_COUNTRY_KENYA)||
                    (eCountry == SI_COUNTRY_MYANMAR))
                {
                    return TRUE;
                }
            return FALSE;
        default:
            ASSERT(0);
            return FALSE;

    }
}
#if ENABLE_S2
extern SCAN_SAVETYPE MApp_GetScanCryptedType(void);
extern SCAN_SERVICETYPE MApp_GetScanServiceType(void);
#endif
BOOLEAN msAPI_SI_Action_CheckServiceInfo_DVB( SI_DTV_CHANNEL_INFO *pstSI_DTV_CHANNEL_INFO )
{
    BOOLEAN bResult = TRUE;
    msAPI_SI_Timer_ResetWDT();
#if ENABLE_S2

#if(ENABLE_S2_FAST_SCAN)
    if(_bM7FastScanFlag)
    {
        return bResult;
    }
#endif //#if(ENABLE_S2_FAST_SCAN)
    if(MApp_GetScanServiceType() == SCAN_SERVICE_ALL)
    {
        bResult=TRUE;
    }
    else if(MApp_GetScanServiceType() == pstSI_DTV_CHANNEL_INFO->stCHAttribute.bServiceType)
    {
        bResult=TRUE;
    }
    else
    {
        bResult=FALSE;
    }
#endif
    //chekc if service id only without any valid pids
    if(pstSI_DTV_CHANNEL_INFO->stCHAttribute.bServiceType == E_TYPE_SKIP_SERVICE)
    {
        pstSI_DTV_CHANNEL_INFO->stCHAttribute.bServiceType = E_TYPE_DTV;
        bResult=FALSE;
    }
    if(pstSI_DTV_CHANNEL_INFO->wVideo_PID == SI_INVALID_PID &&
       pstSI_DTV_CHANNEL_INFO->stAudInfo[0].wAudPID == SI_INVALID_PID)
    {
        if ((pstSI_DTV_CHANNEL_INFO->stCHAttribute.bIsDataServiceAvailable == TRUE) ||
        //(pstVirtualCh->stCHAttribute.bIsMHEGIncluded == TRUE) ||
        (pstSI_DTV_CHANNEL_INFO->stCHAttribute.bIsServiceIdOnly == TRUE ))
        {
            if(msAPI_SI_IsSpecificCountry(MApp_GetSICountry(OSD_COUNTRY_SETTING), SI_SUPPORT_DATA_SERVICE_TYPE_SPECIFIC_COUNTRY))
            {
                if(pstSI_DTV_CHANNEL_INFO->stCHAttribute.bServiceType == E_TYPE_INVALID)
                {
                #if ENABLE_NZ_FREEVIEW
                    if(msAPI_CM_GetCountry() == E_NEWZEALAND)
                    {
                        bResult = FALSE;
                    }
                    else
                    {
                        pstSI_DTV_CHANNEL_INFO->stCHAttribute.bServiceType = E_TYPE_DATA;
                    }
                #else
                    pstSI_DTV_CHANNEL_INFO->stCHAttribute.bServiceType = E_TYPE_DATA;
                #endif
                }
            }
            else
            {
                if(pstSI_DTV_CHANNEL_INFO->stCHAttribute.bServiceType == E_TYPE_INVALID)
                {
                    pstSI_DTV_CHANNEL_INFO->stCHAttribute.bServiceType = E_TYPE_DTV;
                }
            }
        }
        else
        {
        #if 1
            if((msAPI_SI_IsSpecificCountry(MApp_GetSICountry(OSD_COUNTRY_SETTING),SI_NORDIC_SPECIFIC_COUNTRY))&& (pstSI_DTV_CHANNEL_INFO->stCHAttribute.bServiceType != E_TYPE_DATA))
            {
              #if SAVE_AVPIDINVALID_PROGRAM
                if((OSD_COUNTRY_SETTING==OSD_COUNTRY_NORWAY)&&(IsDVBCInUse()))
                {
                    //save program even if video/audio pid invalid for Canal Digital Test
                }
                else
              #endif
                {
                    bResult = FALSE;
                }
            }
        #else
            if(!msAPI_SI_IsSpecificCountry(MApp_GetSICountry(OSD_COUNTRY_SETTING), SI_NORDIC_SPECIFIC_COUNTRY)
            ||((msAPI_SI_IsSpecificCountry(MApp_GetSICountry(OSD_COUNTRY_SETTING),SI_NORDIC_SPECIFIC_COUNTRY))&& (pstSI_DTV_CHANNEL_INFO->stCHAttribute.bServiceType != E_TYPE_DATA)))
                bResult = FALSE;
        #endif
        }
    }

    //only accept E_TYPE_DTV/E_TYPE_RADIO for DTV
    if(pstSI_DTV_CHANNEL_INFO->stCHAttribute.bServiceType == E_TYPE_INVALID)
    {
        if(pstSI_DTV_CHANNEL_INFO->wVideo_PID != SI_INVALID_PID)
        {
            pstSI_DTV_CHANNEL_INFO->stCHAttribute.bServiceType = E_TYPE_DTV;
        }
        else if(pstSI_DTV_CHANNEL_INFO->stAudInfo[0].wAudPID != SI_INVALID_PID)
        {
            pstSI_DTV_CHANNEL_INFO->stCHAttribute.bServiceType = E_TYPE_RADIO;
        }
        else
        {
            bResult = FALSE;
        }
    }

    if(bResult == TRUE)
    {
        // Check isStillPic
        // If video pid exists and PCR pid doesn't exist, set still picture attribute TRUE
        if( ( pstSI_DTV_CHANNEL_INFO->wVideo_PID != SI_INVALID_PID ) && ( pstSI_DTV_CHANNEL_INFO->wPCR_PID == SI_INVALID_PID ) )
        {
            pstSI_DTV_CHANNEL_INFO->stCHAttribute.bIsStillPicture = TRUE;
        }
    }

#if 1//NTV_FUNCTION_ENABLE
    if((pstSI_DTV_CHANNEL_INFO->stCHAttribute.bServiceType == E_TYPE_DATA) && (msAPI_SI_IsSpecificCountry( MApp_GetSICountry(OSD_COUNTRY_SETTING), SI_NORWAY_SPECIFIC_COUNTRY )))
    {
        pstSI_DTV_CHANNEL_INFO->wLCN = SI_INVALID_LOGICAL_CHANNEL_NUMBER;
        pstSI_DTV_CHANNEL_INFO->stCHAttribute.bVisibleServiceFlag = FALSE;
        pstSI_DTV_CHANNEL_INFO->stCHAttribute.bNumericSelectionFlag = FALSE;
    }
#endif

    #if (ENABLE_CI_PLUS)
    if((FALSE == msAPI_SI_GetOpMode()) && (!msAPI_SI_IsSpecificCountry( MApp_GetSICountry(OSD_COUNTRY_SETTING), SI_DTG_SPECIFIC_COUNTRY )) && (!msAPI_SI_IsSpecificCountry( MApp_GetSICountry(OSD_COUNTRY_SETTING),SI_SUPPORT_LCN_ZERO_SPECIFIC_COUNTRY)))
    #else
    if((!msAPI_SI_IsSpecificCountry( MApp_GetSICountry(OSD_COUNTRY_SETTING), SI_DTG_SPECIFIC_COUNTRY )) && (!msAPI_SI_IsSpecificCountry( MApp_GetSICountry(OSD_COUNTRY_SETTING),SI_SUPPORT_LCN_ZERO_SPECIFIC_COUNTRY)))
    #endif
    {
        if( pstSI_DTV_CHANNEL_INFO->wLCN == 0)
        {
            pstSI_DTV_CHANNEL_INFO->stCHAttribute.bVisibleServiceFlag = FALSE;
            pstSI_DTV_CHANNEL_INFO->stCHAttribute.bNumericSelectionFlag = FALSE;
        }
    }

     // check if  IsScramble
    #if ENABLE_S2
        if(MApp_GetScanCryptedType()==SCAN_SAVEFREE && pstSI_DTV_CHANNEL_INFO->stCHAttribute.bIsScramble)
        {
            bResult= FALSE; //not save Scramble program
        }
    #endif

    #if 0//(SI_DEBUG)
    {
        U8 i,j;
        #define SAVEPROGDEBUG printf
        SAVEPROGDEBUG("\n/*******************************/\n");
        SAVEPROGDEBUG("Service Name: ");
        for(i = 0; i < SI_MAX_SERVICE_NAME; i++)
        {
            if(((U8)pstVirtualCh->bChannelName[i]) == 0)break;
            SAVEPROGDEBUG("%c",(U8)pstVirtualCh->bChannelName[i]);
        }
        SAVEPROGDEBUG("\n");
        SAVEPROGDEBUG("LCN %u\n",pstVirtualCh->wLCN);
        SAVEPROGDEBUG("Aud Pid: 0x%04x\n",pstVirtualCh->stAudInfo[0].wAudPID);
        SAVEPROGDEBUG("Vid Pid: 0x%04x\n",pstVirtualCh->wVideo_PID);
        SAVEPROGDEBUG("video type: %d\n",pstVirtualCh->stCHAttribute.eVideoType);
        SAVEPROGDEBUG("PMT Pid: 0x%04x\n",pstVirtualCh->wPmt_PID);
        SAVEPROGDEBUG("PCR Pid: 0x%04x\n",pstVirtualCh->wPCR_PID);
        //SAVEPROGDEBUG("TS ID : 0x%04x\n",pstVirtualCh->wTransportStream_ID);
        SAVEPROGDEBUG("Service ID: 0x%04x\n",pstVirtualCh->wService_ID);
        SAVEPROGDEBUG("Service type [%s]\n",
               (pstVirtualCh->stCHAttribute.bServiceType == E_TYPE_DTV)?"TV":
               (pstVirtualCh->stCHAttribute.bServiceType == E_TYPE_RADIO)?"Radio":"INVALID");
        SAVEPROGDEBUG("Visible: %s\n",(pstVirtualCh->stCHAttribute.bVisibleServiceFlag)?"TRUE":"FALSE");
        SAVEPROGDEBUG("Scramble: %s\n",(pstVirtualCh->stCHAttribute.bIsScramble)?"TRUE":"FALSE");
        SAVEPROGDEBUG("Service ID only: %s\n",(pstVirtualCh->stCHAttribute.bIsServiceIdOnly)?"TRUE":"FALSE");
        SAVEPROGDEBUG("Data service: %s\n",(pstVirtualCh->stCHAttribute.bIsDataServiceAvailable)?"TRUE":"FALSE");
        for(i = 0; i < SI_MAX_AUD_LANG_NUM; i++)
        {
            if(pstVirtualCh->stAudInfo[i].wAudPID == SI_INVALID_PID)
                break;
            SAVEPROGDEBUG("aud[%bu] mode [%s],",i,
                   (pstVirtualCh->stAudInfo[i].wAudType == E_SI_AUDIOSTREAM_MPEG)?"MPEG":
                   (pstVirtualCh->stAudInfo[i].wAudType == E_SI_AUDIOSTREAM_AC3)?"AC3":
                   (pstVirtualCh->stAudInfo[i].wAudType == E_SI_AUDIOSTREAM_MPEG4)?"MPEG4":"INVALID");
            for(j = 0; j < SI_MAX_AUD_ISOLANG_NUM; j++)
            {
                SAVEPROGDEBUG("lang[%bu] %bu, Pid [0x%x]\n",j,
                        pstVirtualCh->stAudInfo[i].aISOLangInfo[j].bISOLangIndex,
                        pstVirtualCh->stAudInfo[i].wAudPID);
            }
        }
        SAVEPROGDEBUG("Save the prog: %s\n",(bResult==TRUE)?"YES":"NO");
        SAVEPROGDEBUG("\n/*******************************/\n");
    }
    #endif

    if(!bResult)//for SDT other update
    {
        pstSI_DTV_CHANNEL_INFO->stCHAttribute.bVisibleServiceFlag = FALSE;
        pstSI_DTV_CHANNEL_INFO->stCHAttribute.bNumericSelectionFlag = FALSE;
        pstSI_DTV_CHANNEL_INFO->stCHAttribute.bInvalidService=TRUE;
    }

    return bResult;
}

BOOLEAN msAPI_SI_Action_CheckServiceInfo_SBTVD( SI_DTV_CHANNEL_INFO *pstSI_DTV_CHANNEL_INFO )
{
#if(ENABLE_SBTVD_DTV_SYSTEM)
    BOOLEAN bResult = TRUE;

    msAPI_SI_Timer_ResetWDT();
    if(pstSI_DTV_CHANNEL_INFO->stCHAttribute.bServiceType == E_TYPE_SKIP_SERVICE)
    {
        pstSI_DTV_CHANNEL_INFO->stCHAttribute.bServiceType = E_TYPE_DTV;
        bResult=FALSE;
    }
    //chekc if service id only without any valid pids
    if(pstSI_DTV_CHANNEL_INFO->wVideo_PID == SI_INVALID_PID &&
       pstSI_DTV_CHANNEL_INFO->stAudInfo[0].wAudPID == SI_INVALID_PID)
    {
        if ((pstSI_DTV_CHANNEL_INFO->stCHAttribute.bIsDataServiceAvailable == TRUE) ||
            //(pstVirtualCh->stCHAttribute.bIsMHEGIncluded == TRUE) ||
            (pstSI_DTV_CHANNEL_INFO->stCHAttribute.bIsServiceIdOnly == TRUE ))
        {

            if (TRUE == pstSI_DTV_CHANNEL_INFO->stCHAttribute.bIsServiceIdOnly)
            {
                //filter the program If the program is not shown in PAT
                bResult = FALSE;
            }
            else if(pstSI_DTV_CHANNEL_INFO->stCHAttribute.bServiceType == E_TYPE_INVALID)
            {
                pstSI_DTV_CHANNEL_INFO->stCHAttribute.bServiceType = E_TYPE_DTV;
            }
        }
        else
        {
            bResult = FALSE;

        }
    }

    //only accept E_TYPE_DTV/E_TYPE_RADIO for DTV
    if(pstSI_DTV_CHANNEL_INFO->stCHAttribute.bServiceType == E_TYPE_INVALID)
    {
        if(pstSI_DTV_CHANNEL_INFO->wVideo_PID != SI_INVALID_PID)
            pstSI_DTV_CHANNEL_INFO->stCHAttribute.bServiceType = E_TYPE_DTV;
        else if(pstSI_DTV_CHANNEL_INFO->stAudInfo[0].wAudPID != SI_INVALID_PID)
            pstSI_DTV_CHANNEL_INFO->stCHAttribute.bServiceType = E_TYPE_RADIO;
        else
        {
            bResult = FALSE;
        }
    }

    if(bResult == TRUE)
    {
        // Check isStillPic
        // If video pid exists and PCR pid doesn't exist, set still picture attribute TRUE
        if( ( pstSI_DTV_CHANNEL_INFO->wVideo_PID != SI_INVALID_PID ) && ( pstSI_DTV_CHANNEL_INFO->wPCR_PID == SI_INVALID_PID ) )
        {
            pstSI_DTV_CHANNEL_INFO->stCHAttribute.bIsStillPicture = TRUE;
        }
    }

    //assign bPhysicalChannel to current RF channel if it is out of range (1~99)
/*//move out
    if(pstVirtualCh->stLCN.bPhysicalChannel > SI_MAX_PHYSICAL_CHANNEL_NUMBER)
    {
        BYTE abPhysicalChannel[1];

        msAPI_SI_GetIDTable(pstVirtualCh->bIDIdex, abPhysicalChannel, E_DATA_PCN);
        pstVirtualCh->stLCN.bPhysicalChannel = abPhysicalChannel[0];
    }
*/
    #if 0//(SI_DEBUG)
    {
        U8 i,j;
        #define SAVEPROGDEBUG printf
        SAVEPROGDEBUG("\n/*******************************/\n");
        SAVEPROGDEBUG("Service Name: ");
        for(i = 0; i < SI_MAX_SERVICE_NAME; i++)
        {
            if(((U8)pstVirtualCh->bChannelName[i]) == 0)break;
            SAVEPROGDEBUG("%c",(U8)pstVirtualCh->bChannelName[i]);
        }
        SAVEPROGDEBUG("\n");
        SAVEPROGDEBUG("LCN %04bX\n",pstVirtualCh->wLCN);
        SAVEPROGDEBUG("Vid Pid: 0x%04x\n",pstVirtualCh->wVideo_PID);
        SAVEPROGDEBUG("video type: %d\n",pstVirtualCh->stCHAttribute.eVideoType);
        SAVEPROGDEBUG("PMT Pid: 0x%04x\n",pstVirtualCh->wPmt_PID);
        SAVEPROGDEBUG("PCR Pid: 0x%04x\n",pstVirtualCh->wPCR_PID);
        SAVEPROGDEBUG("TS ID : 0x%04x\n",pstVirtualCh->wTransportStream_ID);
        SAVEPROGDEBUG("Service ID: 0x%04x\n",pstVirtualCh->wService_ID);
        SAVEPROGDEBUG("Service type [%s]\n",
               (pstVirtualCh->stCHAttribute.bServiceType == E_TYPE_DTV)?"TV":
               (pstVirtualCh->stCHAttribute.bServiceType == E_TYPE_RADIO)?"Radio":"INVALID");
        SAVEPROGDEBUG("Visible: %s\n",(pstVirtualCh->stCHAttribute.bVisibleServiceFlag)?"TRUE":"FALSE");
        SAVEPROGDEBUG("Selectable: %s\n",(pstVirtualCh->stCHAttribute.bNumericSelectionFlag)?"TRUE":"FALSE");
        SAVEPROGDEBUG("Scramble: %s\n",(pstVirtualCh->stCHAttribute.bIsScramble)?"TRUE":"FALSE");
        SAVEPROGDEBUG("Service ID only: %s\n",(pstVirtualCh->stCHAttribute.bIsServiceIdOnly)?"TRUE":"FALSE");
        SAVEPROGDEBUG("Data service: %s\n",(pstVirtualCh->stCHAttribute.bIsDataServiceAvailable)?"TRUE":"FALSE");
        for(i = 0; i < SI_MAX_AUD_LANG_NUM; i++)
        {
            if(pstVirtualCh->stAudInfo[i].wAudPID == SI_INVALID_PID)
                break;
            SAVEPROGDEBUG("aud[%bu] mode [%s],",i,
                   (pstVirtualCh->stAudInfo[i].wAudType == E_SI_AUDIOSTREAM_MPEG)?"MPEG":
                   (pstVirtualCh->stAudInfo[i].wAudType == E_SI_AUDIOSTREAM_AC3)?"AC3":
                   (pstVirtualCh->stAudInfo[i].wAudType == E_SI_AUDIOSTREAM_MPEG4)?"MPEG4":"INVALID");
            for(j = 0; j < SI_MAX_AUD_ISOLANG_NUM; j++)
            {
                SAVEPROGDEBUG("lang[%bu] %bu, Pid [0x%x]\n",j,
                        pstVirtualCh->stAudInfo[i].aISOLangInfo[j].bISOLangIndex,
                        pstVirtualCh->stAudInfo[i].wAudPID);
            }
        }
        SAVEPROGDEBUG("Save the prog: %s\n",(bResult==TRUE)?"YES":"NO");
        SAVEPROGDEBUG("\n/*******************************/\n");
    }
    #endif

    return bResult;
#else

    UNUSED(pstSI_DTV_CHANNEL_INFO);

    return FALSE;
#endif
}

BOOLEAN msAPI_SI_Action_CheckServiceType_DVB( U8 u8OriginalType, U8* pNewType )
{
    *pNewType=u8OriginalType;
    return TRUE;
}

BOOLEAN msAPI_SI_Action_CheckServiceType_SBTVD( U8 u8OriginalType, U8* pNewType )
{
    *pNewType=u8OriginalType;
    return TRUE;

}
void msAPI_SI_Timer_SetTimeOfChange(U32 u32TimeOfChg) //unit = sec
{
    msAPI_Timer_SetTimeOfChange(u32TimeOfChg);
}
void msAPI_SI_Timer_SetNextTimeOffset(S32 s32OffsetTime) //unit = sec
{
    msAPI_Timer_SetNextTimeOffset(s32OffsetTime);
}

BOOLEAN ISDVBS2Source( void )
{
#if(ENABLE_S2)
    if( IsS2InUse() )
    {
        return TRUE;
    }
    else
#endif
    {
        return FALSE;
    }
}

#if(ENABLE_S2)
extern DTVPROGRAMID_M g_stCurS2ProggramId;
BOOLEAN MApp_SI_Get_S2_TpInfo( SI_DTVPROGRAMID  *s2currenttp )
{
    if( s2currenttp == NULL )
    {
        return FALSE;
    }

    s2currenttp->SatelliteId=g_stCurS2ProggramId.SatelliteId;
    s2currenttp->u32S2Frequency=g_stCurS2ProggramId.u32S2Frequency;
    s2currenttp->u16SymbolRate=g_stCurS2ProggramId.u16SymbolRate;
    s2currenttp->u8Polarity=g_stCurS2ProggramId.u8Polarity;
    printf("\r\n____get_s2idinfor_%d_%d_%d_%d__",s2currenttp->SatelliteId,s2currenttp->u32S2Frequency,s2currenttp->u16SymbolRate,s2currenttp->u8Polarity);
    return TRUE;
}
#else
BOOLEAN MApp_SI_Get_S2_TpInfo( SI_DTVPROGRAMID  *s2currenttp )
{
    if( s2currenttp == NULL)
    {
        return FALSE;
    }
    return FALSE;
}
#endif
BOOLEAN msAPI_SI_AutoClockMode(void)
{
    if(stGenSetting.g_Time.en_ClockMode == EN_ClockMode_Manual)
        return FALSE;
    else
        return TRUE;
}

MS_NETWORKID_TS* msAPI_SI_GetNetworkInfo(U8 u8NetworkIndex)
{
#if( (!BLOADER) && ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
    if(msAPI_SI_IsSpecificCountry(MApp_GetSICountry(OSD_COUNTRY_SETTING),SI_SUPPORT_NETWORK_UPDATE_SPECIFIC_COUNTRY))
    {
      return MApp_GetNetworkInfo(u8NetworkIndex);
    }
#else
    u8NetworkIndex=u8NetworkIndex;
#endif
    return NULL;//MApp_GetNetworkInfo(u8NetworkIndex);
}

BOOLEAN msAPI_SI_RestLCNInCurrentRF(WORD* pServiceList, U16 wNumber)
{
    MEMBER_SERVICETYPE bServiceType;
    WORD wCurrentPosition;
    BYTE cRFChannelNumber;
    bServiceType = msAPI_CM_GetCurrentServiceType();
    wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);
    cRFChannelNumber = msAPI_CM_GetPhysicalChannelNumber(bServiceType,wCurrentPosition);
    return msAPI_CM_RestLCNByRF(pServiceList,wNumber,cRFChannelNumber);
}

BYTE msAPI_SI_GetCurrentRF(void)
{
    MEMBER_SERVICETYPE bServiceType;
    WORD wCurrentPosition;
    BYTE cRFChannelNumber;
    bServiceType = msAPI_CM_GetCurrentServiceType();
    wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);
    cRFChannelNumber = msAPI_CM_GetPhysicalChannelNumber(bServiceType,wCurrentPosition);
    return cRFChannelNumber;
}

BOOLEAN msAPI_SI_RemoveMux(WORD wNID, WORD *pwTS_ID,  BYTE cCountOfTS, BOOLEAN *bRemove, BYTE sat,WORD freq)
{
    return msAPI_CM_RemoveMux(wNID, pwTS_ID,  cCountOfTS, bRemove, sat, freq);
}

BOOLEAN msAPI_SI_GetOpMode(void)
{
    return msAPI_CM_GetOpMode();
}
void msAPI_SI_SetEITUpdate(BOOLEAN bUpdate)
{
#if (ENABLE_EPG_MUX)
    msAPI_CM_SetEITUpdate(bUpdate);
#else
    UNUSED(bUpdate);
#endif
}

void msAPI_SI_UpdateNetworkCDSD(U8 u8PhNum,U32 u32Freq,U32 u32Symb,U8 u8Modu)
{
    msAPI_CM_UpdateNetworkCDSD(u8PhNum, u32Freq, u32Symb, u8Modu);
}

//#if ENABLE_DVBC
BOOLEAN msAPI_SI_GetIDIndexWithFreq(U32 u32Freq, WORD *cIDIndex)
{
    BOOLEAN bRet;
    U16 u16IDIndex = 0xFFFF;

    bRet = msAPI_CM_GetIDIndexWithFreq(u32Freq, &u16IDIndex);
    if( bRet )
    {
        *cIDIndex = u16IDIndex;
    }

    return bRet;
}
//#endif

BOOLEAN msAPI_SI_SaveLCDV2(const LOGICAL_CHANNEL_V2 *pstLCNv2, U16 u16MiniChannelId, BOOLEAN bSortFlag, BOOLEAN bReset)
{
    if(bReset == TRUE)
    {
        printf("\r\n >>>> reset LCD V2 data base");
        memset(&_aLCDV2[0], 0x00, (LCDV2ArrayMaxSize * sizeof(LOGICAL_CHANNEL_V2)));

        // reset size for the next parse
        _s8LCDV2Size = -1;

        if (_bLCDV2RescanFlag == FALSE)
        {
            _u8ChanListId = 0xFF;
            _u8CountryCode = 0xFF;
        }

        return TRUE;
    }

    if(bSortFlag == 1)
    {
        LOGICAL_CHANNEL_V2 temp[5];
        U8 u8tempIdx = 0;
        U8 u8MiniIndex = 0;
        U8 u8MiniChanListId = 0xFF;

        printf("\r\n >>>> sort LCD V2 data base");

        // find match country
        if(u16MiniChannelId != 0xFFFF)
        {
            u8tempIdx = 0;

            while(u8tempIdx < LCDV2ArrayMaxSize)
            {
                if(_aLCDV2[u8tempIdx].u8ChanListId == u16MiniChannelId)
                {
                    break;
                }
                u8tempIdx++;
            }

            if( u8tempIdx < LCDV2ArrayMaxSize )   //Fixed Coverity 59184
            {
                // swap match country LCD v2 to the first index.
                memcpy(&temp[0], &_aLCDV2[u8tempIdx], sizeof(LOGICAL_CHANNEL_V2));
                memcpy(&_aLCDV2[u8tempIdx], &_aLCDV2[0], sizeof(LOGICAL_CHANNEL_V2));
                memcpy(&_aLCDV2[0], &temp[0], sizeof(LOGICAL_CHANNEL_V2));
            }
        }
        else
        {
            u8tempIdx = 0;
            while(u8tempIdx < LCDV2ArrayMaxSize)
            {
                //find the minimum channel list id
                if((_aLCDV2[u8tempIdx].u8ChanListId <= u8MiniChanListId)&&(_aLCDV2[u8tempIdx].u8ChanListId != 0x0))
                {
                    u8MiniChanListId = _aLCDV2[u8tempIdx].u8ChanListId;
                    u8MiniIndex = u8tempIdx;
                }
                u8tempIdx++;
            }

            // if the first is not the minimum, swap minimum LCD v2 to the first index.
            if(u8MiniIndex != 0)
            {
                // swap minimum channel list id to the first index;
                memcpy(&temp[0], &_aLCDV2[u8MiniIndex], sizeof(LOGICAL_CHANNEL_V2));
                memcpy(&_aLCDV2[u8MiniIndex], &_aLCDV2[0], sizeof(LOGICAL_CHANNEL_V2));
                memcpy(&_aLCDV2[0], &temp[0], sizeof(LOGICAL_CHANNEL_V2));
            }
        }
    }
    else
    {
        printf("\r\n >>>> parse and save LCD V2 data base");
        _s8LCDV2Size++;
        memcpy((void*)&_aLCDV2[_s8LCDV2Size], (void*)pstLCNv2, sizeof(LOGICAL_CHANNEL_V2));
    }

    return TRUE;
}

void msAPI_SI_GetLCDV2(LOGICAL_CHANNEL_V2 *pLCDV2)
{
    memcpy(pLCDV2, &_aLCDV2[0], (LCDV2ArrayMaxSize * sizeof(LOGICAL_CHANNEL_V2)));
}

void msAPI_SI_SetLCDV2Flag(BOOLEAN bRescanFlag, LOGICAL_CHANNEL_V2 *pLCDV2)
{
    _bLCDV2RescanFlag = bRescanFlag;
    _u8ChanListId = pLCDV2->u8ChanListId;
    _u8CountryCode = pLCDV2->u8CountryCode;
}

BOOLEAN msAPI_SI_GetLCDV2Flag(LOGICAL_CHANNEL_V2 *pLCDV2)
{
    if(_bLCDV2RescanFlag == TRUE)
    {
        pLCDV2->u8ChanListId = _u8ChanListId;
        pLCDV2->u8CountryCode = _u8CountryCode;
        _bLCDV2RescanFlag = FALSE;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOLEAN msAPI_SI_ResetDTVDataManager(BOOLEAN bResetAllDB)
{
#if(ENABLE_API_DTV_SYSTEM)
    return msAPI_CM_ResetDTVDataManager(bResetAllDB);
#else
    UNUSED( bResetAllDB );
    return FALSE;
#endif
}

#if(ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
BOOLEAN msAPI_SI_SaveAstraServiceInfo(U16 u16ServiceListID, MS_SI_SGT_SERVICE_INFO *stServiceInfo)
{
    return msAPI_CM_SaveAstraServiceInfo(u16ServiceListID,stServiceInfo);
}

U16 msAPI_SI_GetAvailableServiceListID(void)
{
    return msAPI_CM_GetAvailableServiceListID();
}

U16 MApp_SI_GetAvailableServiceListID(void)
{
   return msAPI_CM_GetAvailableServiceListID();
}


U16 msAPI_SI_GetCurrentServiceListID(void)
{
    return msAPI_CM_GetCurrentServiceListID();
}



BOOLEAN msAPI_SI_SaveServiceListInfo(const U8 *u8ServiceListName, U16 u16ServiceListID, EN_SI_COUNTRY_SETTING eCountry, BOOLEAN bIsCountryAvailability,BOOLEAN bListInFlag)
{
    return msAPI_CM_SaveServiceListInfo(u8ServiceListName, u16ServiceListID, eCountry, bIsCountryAvailability, bListInFlag);
}

BOOLEAN msAPI_SI_GetExistServiceListInfo(const U16 u16ServiceListID, BOOLEAN bListInFlag)
{
    return msAPI_CM_GetExistServiceListInfo(u16ServiceListID, bListInFlag);
}

U16 MApp_SI_GetCurrentServiceListID(void)
{
    return msAPI_CM_GetCurrentServiceListID();
}

void msAPI_SI_IsAdd2List(BOOLEAN Enable)
{
    printf("msAPI_SI_IsAdd2List(%d)\n",Enable);
    msAPI_CM_IsAdd2List(Enable);
}


void msAPI_SI_GetSgtVersionandPID(MS_SGT_ITEM *pCurSgtVerandPID)
{
    msAPI_CM_GetSgtVersionandPID(pCurSgtVerandPID);
}

#endif //#if(ASTRA_HD_ENABLE)

U32 msAPI_SI_Get_ServiceNameBufLen(void)
{
#if(ENABLE_DVB)
    return SRV_NAME_BUF_LEN;
#else
    return 0;
#endif
}

#if(M7_DVBS_FAST_SCAN_ENABLE)

//****************************************************************************
/// Function : Setting Sate Platform
/// Variable  : @enSatePlatform : sate platform
/// @return  : 1: Success
///                   0: Failure
//****************************************************************************
BOOLEAN msAPI_SI_SetSatePlatform(EN_SATELLITE_PLATFORM enSatePlatform)
{
    if((enSatePlatform <= EN_SATEPF_M7_MIN)  || (enSatePlatform >= EN_SATEPF_MAX))
    {
        printf("*****msAPI_SI_SetSatePlatform set sate platform error = %d***** \n",enSatePlatform);
        return  FALSE;
    }
    else
    {
        _enSatellitePlatform = enSatePlatform;
    }

    return TRUE;
}

//****************************************************************************
/// Function : Get Sate Platform
/// Variable  : @void
/// @return  : EN_SATELLITE_PLATFORM: sate platform
//****************************************************************************
EN_SATELLITE_PLATFORM msAPI_SI_GetSatePlatform(void)
{
     return _enSatellitePlatform;
}

//****************************************************************************
/// Function : Get Sate Platform PID
/// Variable  : @eSatellitePlatform : Sate Platfrom
/// @return  : PID
//****************************************************************************
U16 msAPI_SI_GetOPTSENPIDBySatePlatform(EN_SATELLITE_PLATFORM eSatellitePlatform)
{
    switch(eSatellitePlatform)
      {
          case EN_SATEPF_HD_AUSTRIASAT:
              return AUST_PID;
              break;
          case EN_SATEPF_HELLO:
              return HELLO_PID;
              break;
          case EN_SATEPF_TELESAT_BELGIUM:
              return TELE_BEL_PID;
              break;
          case EN_SATEPF_TELESAT_LUXEMBOURG:
              return TELE_LUX_PID;
              break;
          case EN_SATEPF_CANALDIGITALAL_HD:
              return CD_HD_PID;
              break;
          case EN_SATEPF_CANALDIGITALAL_SD:
              return CD_SD_PID;
              break;
          case EN_SATEPF_SKYLINK_CS_LINK_CZECH:
              return CZE_REP_PID;
              break;
          case EN_SATEPF_SKYLINK_CS_LINK_SLOVAK:
              return SLOV_REP_PID;
              break;
          case EN_SATEPF_TV_VLAANDEREN_HD:
              return TV_VLA_HD_PID;
              break;
          case EN_SATEPF_TV_VLAANDEREN_SD:
              return TV_VLA_SD_PID;
              break;
          default:
              return INVALID_PID;
              break;
      }
}

//****************************************************************************
/// Get Service Type And Position With ServiceIDs
/// @param wTransportStream_ID \b IN: Transport Stream ID
/// @param wOriginalNetwork_ID \b IN: Original Network ID
/// @param cOrdinal \b IN: Ordinal
/// @param peServiceType \b IN: pointer to Service type for return
/// -@see MEMBER_SERVICETYPE
/// @param pwPosition \b IN: pointer to Position for return
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_SI_DVBS_GetServiceTypeAndPositionWithServiceIDs(U16 wTransportStream_ID, U16 wOriginalNetwork_ID, U16 wService_ID, U8 cOrdinal, MEMBER_SI_SERVICETYPE* peServiceType, WORD* pwPosition, BOOLEAN *pbInvalid, BOOLEAN *pbVisible)
{
    MEMBER_SERVICETYPE bServiceType = E_SERVICETYPE_INVALID;
    BOOLEAN bResult = FALSE;

#if(ENABLE_S2_FAST_SCAN)
    bResult = msAPI_CM_DVBS_GetServiceTypeAndPositionWithServiceIDs(wTransportStream_ID, wOriginalNetwork_ID, wService_ID, cOrdinal, &bServiceType, pwPosition);
#else
    bResult = msAPI_CM_GetServiceTypeAndPositionWithIDs(wTransportStream_ID, wOriginalNetwork_ID, wService_ID, cOrdinal, &bServiceType, pwPosition, TRUE);
#endif //#if(ENABLE_S2_FAST_SCAN)

    if(bResult)
    {
        if(pbInvalid)
        {
            *pbInvalid=msAPI_CM_GetProgramAttribute(bServiceType, *pwPosition, E_ATTRIBUTE_IS_INVALID_SERVICE);
        }
        if(pbVisible)
        {
            *pbVisible=msAPI_CM_GetProgramAttribute(bServiceType, *pwPosition, E_ATTRIBUTE_IS_VISIBLE);
        }
        switch(bServiceType)
        {
            case E_SERVICETYPE_RADIO:
                *peServiceType=E_TYPE_RADIO;
                break;
            case E_SERVICETYPE_DATA:
                *peServiceType=E_TYPE_DATA;
                break;
            default:
                MS_DEBUG_MSG(printf("msAPI_SI_GetServiceTypeAndPositionWithIDs unsupport service type %x\n",bServiceType));
                *peServiceType=E_TYPE_DTV;
                break;
            case E_SERVICETYPE_DTV:
                *peServiceType=E_TYPE_DTV;
                break;
        }
    }

    return bResult;

}

//****************************************************************************
/// This function will update program Info
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @param *pcBuffer or *pastVirtualCh \b IN: pointer buffer
/// @param eMember \b IN: program data member
/// -@see PROGRAMDATA_MEMBER
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_SI_UpdateProgramInfo(MEMBER_SI_SERVICETYPE bServiceType, WORD wPosition, SI_SHORT_DTV_CHANNEL_INFO* pastVirtualCh, BYTE *bChanelNameBuffer, E_SI_DATA_MEMBER eMember)
{
    U8 member = 0;
    int i = 0, j = 0, maxISO = 0, maxAudio = 0;
    BYTE *pcBuffer = NULL;

    MEMBER_SERVICETYPE bType = E_SERVICETYPE_INVALID;
    DTV_CHANNEL_INFO ChannelInfo;
    memset(&ChannelInfo, 0, sizeof(DTV_CHANNEL_INFO));

    bType = msAPI_SI_ToCM_Service_Type(bServiceType);

    if(msAPI_CM_GetProgramInfo(bType, wPosition, &ChannelInfo) == FALSE)
    {
        printf("**[%s,%s,%d]*******msAPI_SI_UpdateProgramInfo Error E_SI_DATA_MEMBER = %d***********\n",__FILE__,__FUNCTION__,__LINE__,eMember);
        return FALSE;
    }

    switch(eMember)
    {
        case E_SI_DATA_PAT_SERVICE_INFO:
        {
             ChannelInfo.wPmt_PID = pastVirtualCh->wPmt_PID;
             ChannelInfo.stPSI_SI_Version.bPATVer = pastVirtualCh->stPSI_SI_Version.bPATVer;
             ChannelInfo.stCHAttribute.bIsScramble =pastVirtualCh->stCHAttribute.bIsScramble;
        }

        pcBuffer = (BYTE *)&ChannelInfo;
        member = E_DATA_ALL;
        break;

        case E_SI_DATA_PMT_SERVICE_INFO:
        {
             ChannelInfo.wPCR_PID = pastVirtualCh->wPCR_PID;
             ChannelInfo.wVideo_PID = pastVirtualCh->wVideo_PID;

             ChannelInfo.stCHAttribute.bIsServiceIdOnly = pastVirtualCh->stCHAttribute.bIsServiceIdOnly;
             ChannelInfo.stPSI_SI_Version.bPMTVer = pastVirtualCh->stPSI_SI_Version.bPMTVer;
             ChannelInfo.stCHAttribute.eVideoType=msAPI_SI_ToCM_Video_Type(pastVirtualCh->stCHAttribute.eVideoType);

             maxAudio = MAX_AUD_LANG_NUM > SI_MAX_AUD_LANG_NUM ? SI_MAX_AUD_LANG_NUM : MAX_AUD_LANG_NUM;
             maxISO = MAX_AUD_ISOLANG_NUM > SI_MAX_AUD_ISOLANG_NUM ? SI_MAX_AUD_ISOLANG_NUM : MAX_AUD_ISOLANG_NUM;

             for(i = 0; i < maxAudio ;i++)
             {
                //ChannelInfo.stAudInfo[i].wAudType = msAPI_SI_ToCM_Audio_Type(pastVirtualCh->stAudInfo[i].wAudType);
                ChannelInfo.stAudInfo[i].eSIAudType = (SI_AUDIOSTREAM_TYPE)pastVirtualCh->stAudInfo[i].wAudType;

                ChannelInfo.stAudInfo[i].wAudPID = pastVirtualCh->stAudInfo[i].wAudPID;

                //ChannelInfo.stAudInfo[i].u8ProfileAndLevel = pastVirtualCh->stAudInfo[i].u8ProfileAndLevel;
                ChannelInfo.stAudInfo[i].eProfileAndLevel = msAPI_SI_ToCM_ProfileAndLevel(pastVirtualCh->stAudInfo[i].u8ProfileAndLevel);

                //ChannelInfo.stAudInfo[i].u8Component_AAC_Type = pastVirtualCh->stAudInfo[i].u8Component_AAC_Type;

                 for(j = 0; j < maxISO; j++)
                 {
                     ChannelInfo.stAudInfo[i].aISOLangInfo[j].bISOLangIndex = pastVirtualCh->stAudInfo[i].aISOLangInfo[j].bISOLangIndex;
                     ChannelInfo.stAudInfo[i].aISOLangInfo[j].bISOLanguageInfo = msAPI_SI_ToCM_Audio_Mode(pastVirtualCh->stAudInfo[i].aISOLangInfo[j].bISOLanguageInfo);
                     ChannelInfo.stAudInfo[i].aISOLangInfo[j].bAudType = pastVirtualCh->stAudInfo[i].aISOLangInfo[j].bAudType;
                     ChannelInfo.stAudInfo[i].aISOLangInfo[j].bIsValid = pastVirtualCh->stAudInfo[i].aISOLangInfo[j].bIsValid;
                     ChannelInfo.stAudInfo[i].aISOLangInfo[j].bBroadcastMixedAD = pastVirtualCh->stAudInfo[i].aISOLangInfo[j].bBroadcastMixedAD;
                     ChannelInfo.stAudInfo[i].aISOLangInfo[j].bReserved = pastVirtualCh->stAudInfo[i].aISOLangInfo[j].bReserved;
                }
            }
         }

        pcBuffer = (BYTE *)&ChannelInfo;
        member = E_DATA_ALL;
        break;

        case E_SI_DATA_FST_SERVICE_INFO:
        {
            ChannelInfo.wPCR_PID = pastVirtualCh->wPCR_PID;
            ChannelInfo.wVideo_PID = pastVirtualCh->wVideo_PID;

            ChannelInfo.stPSI_SI_Version.bSDTVer = pastVirtualCh->stPSI_SI_Version.bSDTVer;
            ChannelInfo.stCHAttribute.bServiceType = (U8)msAPI_SI_ToCM_Service_Type((MEMBER_SI_SERVICETYPE)pastVirtualCh->stCHAttribute.bServiceType);
            ChannelInfo.stCHAttribute.bServiceTypePrio = msAPI_SI_ToCM_Service_Priority(pastVirtualCh->stCHAttribute.bServiceTypePrio);

            memcpy(ChannelInfo.bChannelName, bChanelNameBuffer, SI_MAX_SERVICE_NAME > MAX_SERVICE_NAME ? MAX_SERVICE_NAME : SI_MAX_SERVICE_NAME);
            maxAudio = MAX_AUD_LANG_NUM > SI_MAX_AUD_LANG_NUM ? SI_MAX_AUD_LANG_NUM : MAX_AUD_LANG_NUM;
            maxISO = MAX_AUD_ISOLANG_NUM > SI_MAX_AUD_ISOLANG_NUM ? SI_MAX_AUD_ISOLANG_NUM : MAX_AUD_ISOLANG_NUM;

            for(i = 0; i < maxAudio ;i++)
            {
                //ChannelInfo.stAudInfo[i].wAudType = msAPI_SI_ToCM_Audio_Type(pastVirtualCh->stAudInfo[i].wAudType);
                ChannelInfo.stAudInfo[i].eSIAudType = (SI_AUDIOSTREAM_TYPE)pastVirtualCh->stAudInfo[i].wAudType;

                ChannelInfo.stAudInfo[i].wAudPID = pastVirtualCh->stAudInfo[i].wAudPID;

                for(j = 0; j < maxISO; j++)
                {
                    ChannelInfo.stAudInfo[i].aISOLangInfo[j].bISOLangIndex=pastVirtualCh->stAudInfo[i].aISOLangInfo[j].bISOLangIndex;
                    ChannelInfo.stAudInfo[i].aISOLangInfo[j].bISOLanguageInfo=msAPI_SI_ToCM_Audio_Mode(pastVirtualCh->stAudInfo[i].aISOLangInfo[j].bISOLanguageInfo);
                    ChannelInfo.stAudInfo[i].aISOLangInfo[j].bAudType=pastVirtualCh->stAudInfo[i].aISOLangInfo[j].bAudType;
                    ChannelInfo.stAudInfo[i].aISOLangInfo[j].bIsValid=pastVirtualCh->stAudInfo[i].aISOLangInfo[j].bIsValid;
                    ChannelInfo.stAudInfo[i].aISOLangInfo[j].bBroadcastMixedAD=pastVirtualCh->stAudInfo[i].aISOLangInfo[j].bBroadcastMixedAD;
                    ChannelInfo.stAudInfo[i].aISOLangInfo[j].bReserved=pastVirtualCh->stAudInfo[i].aISOLangInfo[j].bReserved;
                }
            }

            pcBuffer = (BYTE *)&ChannelInfo;
            member = E_DATA_ALL;
            break;
         }

       case E_SI_DATA_MONITOR_FST_SERVICE_INFO:
       {
             ChannelInfo.stPSI_SI_Version.bSDTVer = pastVirtualCh->stPSI_SI_Version.bSDTVer;
             //ChannelInfo.stCHAttribute.bServiceType = (U8)msAPI_SI_ToCM_Service_Type((MEMBER_SI_SERVICETYPE)pastVirtualCh->stCHAttribute.bServiceType);
            // memcpy(ChannelInfo.bChannelName, bChanelNameBuffer, SI_MAX_SERVICE_NAME > MAX_SERVICE_NAME ? MAX_SERVICE_NAME : SI_MAX_SERVICE_NAME);
       }

         pcBuffer = (BYTE *)&ChannelInfo;
         member = E_DATA_ALL;
         break;

        case E_SI_DATA_SERVICE_NAME:
            member = E_DATA_SERVICE_NAME;
            pcBuffer = bChanelNameBuffer;
            break;

        case E_SI_DATA_FST_SERVICE_ID:
            member = E_DATA_SERVICE_ID;
            pcBuffer = bChanelNameBuffer;
            break;

        default:
           return FALSE;
    }

    return msAPI_CM_UpdateProgram(bType,wPosition,pcBuffer,member);
}

//****************************************************************************
/// Function : Open DVBS Fast Scan Flag
/// Variable  : @bEnable : Enable Flag
/// @return  : 1: Success
///                   0: Failure
//****************************************************************************
BOOLEAN msAPI_SI_Action_Set_M7DVBS_OpenMonitor(BOOLEAN bEnable)
{
    BOOLEAN bReturn = FALSE;

    _bM7FastScanFlag = bEnable;

#if(ENABLE_S2_FAST_SCAN)
    bReturn = msAPI_CM_Action_Set_M7DVBS_OpenMonitor(bEnable);

    if(bReturn == FALSE)
    {
       return bReturn;
        //printf("**[%s,%s,%d]***msAPI_SI_Action_Set_M7DVBS_OpenMonitor Error   !!***bEnable=%d*************\n",__FILE__,__FUNCTION__,__LINE__,bEnable);
    }
#endif //#if(ENABLE_S2_FAST_SCAN)

    return bReturn;
}

#endif //#if(M7_DVBS_FAST_SCAN_ENABLE)

#endif//#if(ENABLE_DTV)

#if(ENABLE_DVB)
BOOL MApp_SI_Check_LibStructureSize(void)
{
    BOOL bRtn = TRUE;

#if 0
    PRINT_CURRENT_LINE();
    printf(" NETWORK_INFO_LEN=0x%X\n", sizeof(MS_NETWORK_INFO)*SI_MAX_TS_IN_NETWORK);
    printf("sizeof(MS_NETWORK_INFO)=0x%X\n", sizeof(MS_NETWORK_INFO));
    printf("SI_MAX_VC_PER_PHYSICAL=%u\n", SI_MAX_VC_PER_PHYSICAL);
    printf("sizeof(MS_LCN_INFO)=0x%X\n", sizeof(MS_LCN_INFO));
    printf("sizeof(ST_SI_LCN)=0x%X\n", sizeof(ST_SI_LCN));
#endif


    if( sizeof(SI_AUD_INFO) != Mapp_SI_Get_SizeofStruct_SI_AUD_INFO() )
    {
        bRtn = FALSE;
        msDebug_FatalErrorHandler(FATAL_ERR_ID_SI_LIB_STRUCTURE_SIZE_ERROR, 1);
    }
    if( sizeof(SI_SHORT_DTV_CHANNEL_INFO) != Mapp_SI_Get_SizeofStruct_SI_SHORT_DTV_CHANNEL_INFO() )
    {
        bRtn = FALSE;
        msDebug_FatalErrorHandler(FATAL_ERR_ID_SI_LIB_STRUCTURE_SIZE_ERROR, 2);
    }
    if( sizeof(MS_NETWORK_INFO) != Mapp_SI_Get_SizeofStruct_MS_NETWORK_INFO() )
    {
        bRtn = FALSE;
        msDebug_FatalErrorHandler(FATAL_ERR_ID_SI_LIB_STRUCTURE_SIZE_ERROR, 3);
    }
    if( sizeof(SI_DTV_CHANNEL_INFO) != Mapp_SI_Get_SizeofStruct_SI_DTV_CHANNEL_INFO() )
    {
        bRtn = FALSE;
        msDebug_FatalErrorHandler(FATAL_ERR_ID_SI_LIB_STRUCTURE_SIZE_ERROR, 4);
    }
    if( sizeof(DTV_TS_RF_INFO) != Mapp_SI_Get_SizeofStruct_DTV_TS_RF_INFO() )
    {
        bRtn = FALSE;
        msDebug_FatalErrorHandler(FATAL_ERR_ID_SI_LIB_STRUCTURE_SIZE_ERROR, 5);
    }
    if( sizeof(MS_NETWORKID_TS) != Mapp_SI_Get_SizeofStruct_MS_NETWORKID_TS() )
    {
        bRtn = FALSE;
        msDebug_FatalErrorHandler(FATAL_ERR_ID_SI_LIB_STRUCTURE_SIZE_ERROR, 6);
    }
    if( sizeof(MS_ALL_NETWORKID_INFO) != Mapp_SI_Get_SizeofStruct_MS_ALL_NETWORKID_INFO() )
    {
        bRtn = FALSE;
        msDebug_FatalErrorHandler(FATAL_ERR_ID_SI_LIB_STRUCTURE_SIZE_ERROR, 7);
    }
#if (ASTRA_HD_ENABLE)
    if( sizeof(MS_SI_DESC_NIT_LINKAGE_INFO) != Mapp_SI_Get_SizeofStruct_MS_SI_DESC_NIT_LINKAGE_INFO() )
    {
        bRtn = FALSE;
        msDebug_FatalErrorHandler(FATAL_ERR_ID_SI_LIB_STRUCTURE_SIZE_ERROR, 8);
    }
#endif

/*
    if( sizeof(E_SI_DATA_MEMBER) != Mapp_SI_Get_SizeofEnum_E_SI_DATA_MEMBER() )
    {
        bRtn = FALSE;
        msDebug_FatalErrorHandler(FATAL_ERR_SI_LIB_STRUCTURE_SIZE_ERROR);
    }
    */

    //printf("SI_VERSION=%u, MApp_Get_SI_VersionNumber()=%u\n", SI_VERSION, MApp_Get_SI_VersionNumber() );
    if( SI_VERSION != MApp_Get_SI_VersionNumber() )
    {
        bRtn = FALSE;
        msDebug_FatalErrorHandler_Para_2(FATAL_ERR_ID_SI_LIB_VERSION_ERROR, SI_VERSION, MApp_Get_SI_VersionNumber());
    }

    return bRtn;
}

U16 MApp_SI_GetUI_CurFocusSrvPos(void)
{
    return MApp_EpgUI_Func_Get_CurFocusSrvPos();
}

MEMBER_SI_SERVICETYPE MApp_SI_GetUI_CurFocusSrvType(void)
{
    switch(MApp_EpgUI_Func_Get_CurFocusSrvType())
    {
        case E_SERVICETYPE_RADIO: return E_TYPE_RADIO;
        case E_SERVICETYPE_DATA: return E_TYPE_DATA;
        default:
            return E_TYPE_DTV;
        case E_SERVICETYPE_DTV: return E_TYPE_DTV;
    }
}
#else
U16 MApp_SI_GetUI_CurFocusSrvPos(void)
{
    return 0;
}

MEMBER_SI_SERVICETYPE MApp_SI_GetUI_CurFocusSrvType(void)
{
    return E_TYPE_INVALID;
}

#endif // #if(ENABLE_DVB)

BOOL Mapp_SI_CI_HSS_Get(void)
{
#if ENABLE_CI_PLUS && ENABLE_CI_HSS
    return msAPI_CI_HSS_Get();
#else
    return FALSE;
#endif
}

void Mapp_SI_CI_HSS_Check(void)
{
#if ENABLE_CI_PLUS && ENABLE_CI_HSS
    msAPI_CI_HSS_Check();
#endif
}

BOOLEAN msAPI_SI_SaveCIVirtualService(U8 *pu8Data)
{
#if ENABLE_CI_PLUS_V1_4
    return Mapp_CI_SaveVirtualService(pu8Data);
#else
    UNUSED (pu8Data);
    return FALSE;
#endif
}

#undef MAPP_SI_IF_C

