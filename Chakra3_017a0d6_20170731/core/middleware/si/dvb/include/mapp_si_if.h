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

#ifndef MAPP_SI_IF_H
#define MAPP_SI_IF_H

#if(ENABLE_DTV)
//#include "mapp_demux.h"
//#include "mapp_si.h"

#if 0
/*
#ifndef ENABLE_S2
#define ENABLE_S2 0
#endif

#ifndef ENABLE_DVB_S2
#define ENABLE_DVB_S2   ENABLE_S2
#endif
*/
//Sharp SI Project Select
#define SHARP_SI_HK 1
#define SHARP_SI_CN_DTMB 2
#define SHARP_SI_ASIA 3

#define SHARP_SI_PROJ SHARP_SI_ASIA

//#define ENABLE_DVB_S2   0
//#define ENABLE_S2_PREDIT_RENAME 0
//#define ENABLE_S2_CHANNEL_FAV_NEWSTYLE 0

//#define ENABLE_ASTRA_HD 1
#ifndef  ENABLE_ASTRA_LCN
#define  ENABLE_ASTRA_LCN    0
#endif
#define  ASTRA_LCN_ENABLE   ENABLE_ASTRA_LCN

#ifndef ENABLE_ASTRA_HD
    #define ENABLE_ASTRA_HD   0
#endif
#ifndef ASTRA_HD_ENABLE
    #define ASTRA_HD_ENABLE ENABLE_ASTRA_HD
#endif

#ifndef ENABLE_MHEG5_SIINFO
#define ENABLE_MHEG5_SIINFO   (SHARP_SI_PROJ == SHARP_SI_HK)
#endif
#define MHEG5_SIINFO_ENABLE   ENABLE_MHEG5_SIINFO

#if(MHEG5_SIINFO_ENABLE)
#define EPG_TIMER_MAX_EVENT_NAME_LEN  30
#endif //#if(MHEG5_SIINFO_ENABLE)

#define ENABLE_LCN_V2_HIGH_PRIORITY_SORTING     (SHARP_SI_PROJ == SHARP_SI_ASIA)

///M7 DVBS Fast Scan
#ifndef ENABLE_M7
#define ENABLE_M7  0 //ENABLE_S2
#endif
#define M7_DVBS_FAST_SCAN_ENABLE     ENABLE_M7
#endif

#if(MHEG5_SIINFO_ENABLE)
#define EPG_TIMER_MAX_EVENT_NAME_LEN  30
#endif //#if(MHEG5_SIINFO_ENABLE)

#define SI_MAX_TS_IN_DBVCNETWORK     100
#define SI_MAX_NETWORK 3
#define SI_MAX_TS_IN_NETWORK     8
#define SI_MAX_AUD_LANG_NUM                   32//NZ default 16, Singapore 32(mantis_1295134)
#define SI_MAX_AUD_ISOLANG_NUM                1 // 3
#define SI_MAX_SERVICE_NAME            70//34//40//48 //for HD Simulcast Logical Channel number
#define SI_MAX_VC_PER_PHYSICAL                240//120//100//67//62
#define SI_INVALID_PSI_SI_VERSION              0xFF
#define SI_INVALID_PID                         0x1FFF
#define SI_INVALID_SERVICE_ID                  0xFFFF
#define SI_INVALID_TS_ID                       0xFFFF
#define SI_INVALID_ON_ID                       0xFFFF
#define SI_INVALID_LOGICAL_CHANNEL_NUMBER      0xFFFF
#define SI_INVALID_SIMULCAST_LOGICAL_CHANNEL_NUMBER      0x7FF
#define SI_MAX_ISO639CODE_LENGTH              3
#define SI_MAX_NETWORK_NAME                 80
#define SI_MAX_FREQUENCY_LIST  16//max support 16
#define SI_UNCONFIRMED_PHYSICAL_CHANNEL_NUMBER  0xFE
#define SI_INVALID_PHYSICAL_CHANNEL_NUMBER                  0xFF
#define SI_INVALID_ALTERNATIVETIME             0
#define SI_ONID_NORWAY          0x2242
#define SI_ONID_NEWZEALAND      0x222A
#define SI_ONID_MALAYSIA        0x21CA
#define SI_ONID_THAILAND        0x22FC
#define SI_ONID_SINGAPORE       0x22BE

#define SI_INVALID_PARENTAL 0xFF

#define COMPRESS_CTRL_CODE  0x1F
#define DECOMPRESSION_TABLE1    0x01
#define DECOMPRESSION_TABLE2    0x02
/// decompression table5
#define DECOMPRESSION_TABLE5    0x05
/// decompression table6
#define DECOMPRESSION_TABLE6    0x06
#define NO_DECOMPRESSION    0x00
#define UTF8_CHAR_SET   0x15

#define SI_MAX_TS_IN_CICAMNIT   256
#define SI_MAX_CI_CONTENT_LABEL 15
#define SI_MAX_CI_PROVIDER_NAME 50
#define SI_MAX_CI_SERVICE_NAME  50
#define SI_MAX_CI_CONTENT_LABEL 15
#define SI_MAX_CIPLUS_LABEL_CHAR   24
#define SI_MAX_LOGICAL_LIST_V2  256
#define LCDV2ArrayMaxSize   5

#define ENABLE_SAVE_SQI  TRUE


#define MSAPI_SI_MEMORY_FREE(ptr)   \
{                                   \
    msAPI_SI_Memory_Free(ptr);     \
    ptr = NULL;                     \
}

typedef enum
{
    E_TYPE_INVALID    = 0x00,
    E_TYPE_DTV  = 0x01,
    E_TYPE_RADIO     = 0x02,
    E_TYPE_TTX    = 0x03,
    E_TYPE_AC_RADIO  = 0x0A,
    E_TYPE_DATA     = 0x0C,
    E_TYPE_SKIP_SERVICE    = 0x0F,
    E_TYPE_MHP    = 0x10,
    E_TYPE_HD_DTV    = 0x11,
    E_TYPE_ACSD_DTV  = 0x16,
    E_TYPE_ACHD_DTV  = 0x19,
    E_TYPE_HEVC_DTV    = 0x1F,
} MEMBER_SI_SERVICETYPE;



typedef enum
{
    EXCLUDE_NOT_VISIBLE_AND_DELETED_SI,
    INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED_SI,
    INCLUDE_ALL_SI,
    MAX_COUNT_PROGRAM_OPTION_SI
} SI_COUNT_PROGRAM_OPTION;


#define     E_SI_MUTEX_PARSE    0
#define     E_SI_MUTEX_NIT          1
#define     E_SI_MUTEX_PAT  2
#define     E_SI_MUTEX_SDT  3
#define     E_SI_MUTEX_EIT_CUR_PF   4
#define     E_SI_MUTEX_EIT_ALL_PF 5
#define     E_SI_MUTEX_EIT_SCHEDULE 6
#define     E_SI_MUTEX_PMT  7
#define     E_SI_MUTEX_TDT  8
#define     E_SI_MUTEX_TOT  9
#define     E_SI_MUTEX_UPDATE   10
#define     E_SI_MUTEX_FILTER_MONITOR   11
#define     E_SI_MUTEX_ALL   12
#define     E_SI_MUTEX_MAX  13
#define     E_SI_MUTEX_EWS  14

#if (ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
#define     E_SI_MUTEX_SGT   15
#endif //#if (ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)

#if (M7_DVBS_FAST_SCAN_ENABLE)
#define     E_SI_MUTEX_FNT   16
#define     E_SI_MUTEX_FST   17
#endif   // #if (M7_DVBS_FAST_SCAN_ENABLE)

typedef enum
{
    E_SI_VIDEOTYPE_MPEG  = 0x00,
    E_SI_VIDEOTYPE_H264  = 0x01,
    E_SI_VIDEOTYPE_AVS   = 0x02,
    E_SI_VIDEOTYPE_VC1   = 0x03,
    E_SI_VIDEOTYPE_H265  = 0x04//IMPLEMENT_DTV_H265
} SI_VIDEO_TYPE;

typedef enum{
    AAC_LEVEL1 = 0x50,
    AAC_LEVEL2 = 0x51,
    AAC_LEVEL4 = 0x52,
    AAC_LEVEL5 = 0x53,
    HE_AAC_LEVEL2 = 0x58,
    HE_AAC_LEVEL3 = 0x59,
    HE_AAC_LEVEL4 = 0x5A,
    HE_AAC_LEVEL5 = 0x5B,
    HE_AAC_V2_LEVEL2 = 0x60,
    HE_AAC_V2_LEVEL3 = 0x61,
    HE_AAC_V2_LEVEL4 = 0x62,
    HE_AAC_V2_LEVEL5 = 0x63,

} E_SI_PROFILE_AND_LEVEL;

typedef enum
{
    E_SI_SERVICETYPE_PRIORITY_HIGH    = 0x00,
    E_SI_SERVICETYPE_PRIORITY_MIDDLE  = 0x01,
    E_SI_SERVICETYPE_PRIORITY_LOW     = 0x02,
    E_SI_SERVICETYPE_PRIORITY_NONE    = 0x03
} SI_SERVICETYPE_PRIORITY;
typedef struct
{
    BYTE bPATVer;
    BYTE bPMTVer;
    BYTE bNITVer;
    BYTE bSDTVer;
    BYTE bBATVer;
} SI_TABLE_VERSION;

/// PSI/SI Version member
typedef enum
{
    E_VER_PMT=1,   ///< PMT
    E_VER_PAT=2,   ///< PAT
    E_VER_NIT=3,   ///< NIT
    E_VER_SDT=4,                           ///< SDT
    E_VER_SDT_OTHER=5,                     ///< SDT OTHER
    E_VER_BAT=6
} E_PSI_SI_VERSION;

typedef enum
{
    E_SI_DATA_SERVICE_NAME=1,
    E_SI_DATA_LCN=2,
    E_SI_DATA_SIMU_LCN=3,
    E_SI_DATA_VERSION_SDT=4,
    E_SI_DATA_VERSION_PAT=5,
    E_SI_DATA_VERSION_PMT=6,
    E_SI_DATA_VERSION_NIT=7,
    E_SI_DATA_ON_ID=8,
    E_SI_DATA_TS_ID=9,
    E_SI_DATA_TS_LCN=10,
    E_SI_DATA_ALL_EXCLUDE_MULTILINGUAL_NAME=11,
    E_SI_DATA_ALL=12,
    E_SI_REPLACE_SERVICE=13,
#if 1//ENABLE_SAVE_MULTILINGUAL_SERVICE_NAME
    E_SI_DATA_MULTILINGUAL_SERVICE_NAME = 14,
    E_SI_DATA_MULTILINGUAL_SERVICE_LANGUAGE = 15,
    E_SI_DATA_UPDATE_EWS =16,
#endif

#if(MHEG5_SIINFO_ENABLE)
   E_SI_DATA_PROVIDER_NAME = 17,
#endif // #if(MHEG5_SIINFO_ENABLE)

#if (M7_DVBS_FAST_SCAN_ENABLE)
    E_SI_DATA_PAT_SERVICE_INFO = 18,
    E_SI_DATA_PMT_SERVICE_INFO = 19,
    E_SI_DATA_FST_SERVICE_INFO = 20,
    E_SI_DATA_MONITOR_FST_SERVICE_INFO = 21,
    E_SI_DATA_FST_SERVICE_ID = 22,
    E_SI_DATA_FNT_NETWORK_ID = 23,
#endif //#if (M7_DVBS_FAST_SCAN_ENABLE)

#if (ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
    E_SI_DATA_VERSION_SGT = 24,  //SGT Replace SDT Table
    E_SI_DATA_PID_SGT     = 25,  //SGT pid
#endif // #if (ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)

    E_SI_DATA_MISC = 26,
    E_SI_DATA_VERSION_BAT = 27,
} E_SI_DATA_MEMBER;

#if M7_DVBS_FAST_SCAN_ENABLE

#define MAX_DTV_FNT_MUX_NUMBER                  2500

typedef enum
{
    EN_SATEPF_OTHER = 0,
    //Will Remove With Package Enum
    EN_SATEPF_M7_MIN ,
    EN_SATEPF_M7_NO_SORTING = EN_SATEPF_M7_MIN,
    EN_SATEPF_CANALDIGITALAL_HD,
    EN_SATEPF_CANALDIGITALAL_SD,
    EN_SATEPF_TV_VLAANDEREN_HD,
    EN_SATEPF_TV_VLAANDEREN_SD ,
    EN_SATEPF_TELESAT_BELGIUM,
    EN_SATEPF_TELESAT_LUXEMBOURG,
    EN_SATEPF_HD_AUSTRIASAT,
    EN_SATEPF_HELLO,
    EN_SATEPF_SKYLINK_CS_LINK_CZECH,
    EN_SATEPF_SKYLINK_CS_LINK_SLOVAK,
    EN_SATEPF_M7_MAX = EN_SATEPF_SKYLINK_CS_LINK_SLOVAK,
    EN_SATEPF_MAX,
}EN_SATELLITE_PLATFORM;

typedef enum
{
    ///900 CanalDigitaal with SD list
    CD_SD_PID = 0x384,
    ///901 CanalDigitaal with HD list
    CD_HD_PID = 0x385,
    ///910 TV VLAANDEREN with SD list
    TV_VLA_SD_PID = 0x38E,
    ///911 TV VLAANDEREN with HD list
    TV_VLA_HD_PID = 0x38F,
    ///920 TeleSAT Belgium list
    TELE_BEL_PID = 0x398,
    ///921 TeleSAT Luxemburg list
    TELE_LUX_PID = 0x399,
    ///950 AustriaSat
    AUST_PID = 0x3B6,
    ///951 Hello
    HELLO_PID = 0x3B7,
    ///30 Czech Republic
    CZE_REP_PID = 0x1E,
    ///31 Slovak Republic
    SLOV_REP_PID = 0x1F,
}EN_OPTSEN_PID;

#define SI_MAX_FST_SERVICE_NAME           32

typedef struct
{
    U16 u16ServiceID;
    U8 bChannelName[SI_MAX_FST_SERVICE_NAME];
    WORD wPCR_PID;
    WORD wVideo_PID;
    BYTE   bFSTVer;
    WORD wAudPID            : 13;           ///< Audio PID
    WORD bServiceType       : 4;
    BYTE bServiceTypePrio   : 2;
    U16 wTransportStream_ID;
    U16 wOriginalNetwork_ID;

} MS_SI_FST_DATA;

typedef struct
{
    MS_SI_FST_DATA stFstInfoList[MAX_DTV_FNT_MUX_NUMBER];
} MS_SI_FST_INFO;

#endif //#if (M7_DVBS_FAST_SCAN_ENABLE)

typedef enum
{
    E_SI_ATTRIBUTE_IS_SCRAMBLED=0,               ///< Attribute scrambled
    E_SI_ATTRIBUTE_IS_STILL_PICTURE=1,           ///< Attribute still picture
    E_SI_ATTRIBUTE_IS_VISIBLE=2,                 ///< Attribute visible
    E_SI_ATTRIBUTE_IS_NUMERIC_SELECTION=3,       ///< Attribute numberic selection
    E_SI_ATTRIBUTE_IS_SKIPPED=4,                 ///< Attribute skipped
    E_SI_ATTRIBUTE_IS_LOCKED=5,                  ///< Attribute locked
//    E_SI_ATTRIBUTE_IS_MHEG_INCLUDED=6,           ///< Attribute mheg included
    E_SI_ATTRIBUTE_IS_REPLACE_SERVICE=6,           ///< Attribute replacement service
    E_SI_ATTRIBUTE_IS_SERVICE_ID_ONLY=7,         ///< Attribute service ID only
    E_SI_ATTRIBUTE_IS_DELETED=8,                 ///< Attribute deleted
    E_SI_ATTRIBUTE_IS_REPLACE_DEL=9,             ///< Attribute Replace Del
    E_SI_ATTRIBUTE_IS_MOVED=10,                    ///< Attribute moved
    E_SI_ATTRIBUTE_IS_UNCONFIRMED_SERVICE=11,
    E_SI_ATTRIBUTE_IS_FAVORITE=12,
    E_SI_ATTRIBUTE_IS_NEW_SERVICE=13,
} E_SI_MEMBER_CHANNEL_ATTRIBUTE;


typedef enum
{
    SI_COUNTRY_AUSTRALIA,  //0
    SI_COUNTRY_AUSTRIA,
    SI_COUNTRY_BELGIUM,
    SI_COUNTRY_BULGARIA,
    SI_COUNTRY_CROATIA,
    SI_COUNTRY_CZECH,  //5
    SI_COUNTRY_DENMARK,
    SI_COUNTRY_FINLAND,
    SI_COUNTRY_FRANCE,
    SI_COUNTRY_GERMANY,
    SI_COUNTRY_GREECE,  //10
    SI_COUNTRY_HUNGARY,
    SI_COUNTRY_ITALY,
    SI_COUNTRY_IRELAND,
    SI_COUNTRY_LUXEMBOURG,
    SI_COUNTRY_NETHERLANDS,//15
    SI_COUNTRY_NORWAY,
    SI_COUNTRY_POLAND,
    SI_COUNTRY_PORTUGAL,
    SI_COUNTRY_ROMANIA,
    SI_COUNTRY_RUSSIA, //20
    SI_COUNTRY_SERBIA,
    SI_COUNTRY_SLOVENIA,
    SI_COUNTRY_SPAIN,
    SI_COUNTRY_SWEDEN,
    SI_COUNTRY_SWITZERLAND, //25
    SI_COUNTRY_UK,
    SI_COUNTRY_DEFAULT = SI_COUNTRY_UK,
    SI_COUNTRY_NEWZEALAND,
    SI_COUNTRY_CHINA,
    SI_COUNTRY_ESTONIA,
    SI_COUNTRY_TURKEY,      //30
    SI_COUNTRY_MOROCCO,
    SI_COUNTRY_TUNIS,
    SI_COUNTRY_ALGERIA,
    SI_COUNTRY_EGYPT,
    SI_COUNTRY_SOUTH_AFRICA,  //35
    SI_COUNTRY_ISRAEL,
    SI_COUNTRY_IRAN,
    SI_COUNTRY_UNITED_ARAB_EMIRATES,
    SI_COUNTRY_SLOVAKIA,
    SI_COUNTRY_TAIWAN,  //40
    SI_COUNTRY_BRAZIL,
    SI_COUNTRY_SINGAPORE,
    SI_COUNTRY_THAILAND,
    SI_COUNTRY_VIETNAM,
    SI_COUNTRY_MALAYSIA, //45
    SI_COUNTRY_INDONESIA,
    SI_COUNTRY_KUWAIT,
    SI_COUNTRY_OMAN,
    SI_COUNTRY_QATAR,
    SI_COUNTRY_SAUDI_ARABIA, //50
    SI_COUNTRY_BAHRAIN,
    SI_COUNTRY_KOREA,
    SI_COUNTRY_GHANA,
    SI_COUNTRY_KENYA,
    SI_COUNTRY_UKRAINE,
    SI_COUNTRY_IVORY_COAST,
    SI_COUNTRY_MYANMAR,
    SI_COUNTRY_NUMS,

} EN_SI_COUNTRY_SETTING;

//use for ENABLE_S2_NZ_FREEVIEW and ENABLE_BAT_MONITOR
typedef enum
{
    SI_REGION_MIN = 0x1000,
    SI_REGION_AUCKLAND = SI_REGION_MIN,
    SI_REGION_WAIKATO = 0x1100,
    SI_REGION_CENTRAL = 0x1200,
    SI_REGION_WELLINGTON = 0x1300,
    SI_REGION_CHRISTCHURCH = 0x1400,
    SI_REGION_DUNEDIN = 0x1500,
    SI_REGION_RESERVED_REGION7 = 0x1600,
    SI_REGION_RESERVED_REGION8 = 0x1700,
    SI_REGION_RESERVED_REGION9 = 0x1800,
    SI_REGION_RESERVED_REGION10 = 0x1900,
    SI_REGION_ENGINEERING_TEST_BOUQUET = 0x2000,
    SI_REGION_MAX = SI_REGION_ENGINEERING_TEST_BOUQUET,
    SI_REGION_UNKNOWN = 0xFFFF,
}EN_SI_BOUQUET_ID;

typedef enum
{
    SI_NORDIC_SPECIFIC_COUNTRY=0,
    SI_DTG_SPECIFIC_COUNTRY=1,
    SI_FRANCE_SPECIFIC_COUNTRY=2,
    SI_NZ_SPECIFIC_COUNTRY=3,
    SI_NORWAY_SPECIFIC_COUNTRY=4,
    SI_SPAIN_SPECIFIC_COUNTRY=5,
    SI_SWEDEN_SPECIFIC_COUNTRY=6,
    SI_UK_SPECIFIC_COUNTRY=7,
    SI_USE_DEFAULT_TIMEZONE_SPECIFIC_COUNTRY=8,//for multi-timezone country, and if use default time zone when only broadcast one region and region not match the setting of timezone
    SI_ITALY_SPECIFIC_COUNTRY=9,
    SI_SIMULCN_SPECIFIC_COUNTRY=10,
    SI_MHEG5_DATA_SERVICE_TO_TV_SPECIFIC_COUNTRY=11,
    SI_SUPPORT_DATA_SERVICE_TYPE_SPECIFIC_COUNTRY=12,
    SI_SUPPORT_NETWORK_UPDATE_SPECIFIC_COUNTRY=13,
    SI_SUPPORT_TTX_SERVICE_TYPE_SPECIFIC_COUNTRY=14,
    SI_SUPPORT_SDT_OTHER_SPECIFIC_COUNTRY=15,
    SI_IS_SI_BASE_SPECIFIC_COUNTRY=16,
    SI_IS_NIT_BASE_SPECIFIC_COUNTRY=17,
    SI_SUPPORT_DVB_C_NETWORK_UPDATE_SPECIFIC_COUNTRY=18,
    SI_IS_DEFAULT_BROADCAST_MIXED_SPECIFIC_COUNTRY=19,
    SI_IS_USE_SI_OTHER_COUNTRY=20,//for SMATV case
    SI_EUROPE_SPECIFIC_COUNTRY=21,
    SI_AUSTRALIA_SPECIFIC_COUNTRY=22,
    SI_LCN2_SPECIFIC_COUNTRY=23,
    SI_SUPPPORT_USERTYPE_SERVICE_SPECIFIC_COUNTRY=24,
    SI_NO_LCN_SPECIFIC_COUNTRY=25,
    SI_MALAYSIA_SPECIFIC_COUNTRY=26,
    SI_SUPPORT_HEVC_SPECIFIC_COUNTRY=27,
    SI_INDONESIA_SPECIFIC_COUNTRY=28,
    SI_UNITED_ARAB_EMIRATES_SPECIFIC_COUNTRY=29,
    SI_NETWORKUPDATE_WITHOUTONID_COUNTRY=30,
    SI_THAILAND_SPECIFIC_COUNTRY=31,
    SI_SINGAPORE_SPECIFIC_COUNTRY=32,
    SI_EWS_SPECIFIC_COUNTRY =33,
    SI_FORCE_USE_TOT_COUNTRY =34,
    SI_VIETNAM_SPECIFIC_COUNTRY =35,
    SI_SUPPORT_LCN_ZERO_SPECIFIC_COUNTRY =36,
    SI_SUPPORT_14BIT_LCN_SPECIFIC_COUNTRY =37,
    SI_NETWORKUPDATE_ADD_SERVICE_WITH_LCN =38,
    SI_EPGINFO_WITHOUT_CHECK_TIME =39,
    SI_FORCE_PRD_COUNTRYCODE=40,
    SI_KENYA_SPECIFIC_COUNTRY=41,
    SI_EITPF_WITHOUT_SDTACTUAL=42,
    SI_SDT_WAIT_15000MS_WHEN_CHANNEL_CHANGE=43,
    SI_SUPPORT_ZIGGO_SPECIFIC_COUNTRY=44,
    SI_NIT_CRCCHECK_COUNTRY=45,
    SI_LCN_WITHOUT_PDSD_COUNTRY=46,
} E_SI_SPECIFIC_COUNTRY;

typedef enum _EN_SI_MENU_LANGUAGE
{
    SI_LANGUAGE_CZECH,
    SI_LANGUAGE_DANISH,
    SI_LANGUAGE_GERMAN,
    SI_LANGUAGE_ENGLISH,
    SI_LANGUAGE_SPANISH,
    SI_LANGUAGE_GREEK,
    SI_LANGUAGE_FRENCH,
    SI_LANGUAGE_CROATIAN,
    SI_LANGUAGE_ITALIAN,
    SI_LANGUAGE_IRELAND,
    SI_LANGUAGE_HUNGARIAN,
    SI_LANGUAGE_DUTCH,
    SI_LANGUAGE_NORWEGIAN,
    SI_LANGUAGE_POLISH,
    SI_LANGUAGE_PORTUGUESE,
    SI_LANGUAGE_RUSSIAN,
    SI_LANGUAGE_ROMANIAN,
    SI_LANGUAGE_SLOVENIAN,
    SI_LANGUAGE_SERBIAN,
    SI_LANGUAGE_FINNISH,
    SI_LANGUAGE_SWEDISH,
    SI_LANGUAGE_BULGARIAN,
    SI_LANGUAGE_SLOVAK,
    SI_LANGUAGE_SPANISH_CAT,
    SI_LANGUAGE_SPANISH_V_O,
    SI_LANGUAGE_SPANISH_AD,
    SI_LANGUAGE_SPANISH_VO,
    SI_LANGUAGE_SPANISH_AC3,
    SI_LANGUAGE_CHINESE,
    SI_LANGUAGE_CHINESE_TRAD,
    SI_LANGUAGE_GAELIC,
    SI_LANGUAGE_TWI,
    SI_LANGUAGE_WELSH,
    SI_LANGUAGE_NUM,             // Language maximum
    SI_LANGUAGE_IRISH,
    SI_LANGUAGE_TURKISH,
    SI_LANGUAGE_NETHERLANDS,
    SI_LANGUAGE_GALLEGAN,
    SI_LANGUAGE_BASQUE,
    SI_LANGUAGE_LUXEMBOURGISH,
    SI_LANGUAGE_ICELANDIC,
    SI_LANGUAGE_LATVIAN,
    SI_LANGUAGE_ESTONIAN,
    SI_LANGUAGE_LITHUANIAN,
    SI_LANGUAGE_UKRANIAN,
    SI_LANGUAGE_BELARUSIAN,
    SI_LANGUAGE_SAMI,
    SI_LANGUAGE_ARABIC,
    SI_LANGUAGE_HEBREW,
    SI_LANGUAGE_QAA,
    SI_LANGUAGE_QAB,
    SI_LANGUAGE_QAC,
    SI_LANGUAGE_UND, //**-- Italy CI Certificate --**//
    SI_LANGUAGE_KOREAN,
    SI_LANGUAGE_JAPAN,
    SI_LANGUAGE_HINDI,
    SI_LANGUAGE_MYANMAR,
    SI_LANGUAGE_MANDARIN,
    SI_LANGUAGE_CANTONESE,
    SI_LANGUAGE_MAORI,
    SI_LANGUAGE_INDONESIA,
    SI_LANGUAGE_THAILAND,
    SI_LANGUAGE_SGA,
    SI_LANGUAGE_KURDISH,
    SI_LANGUAGE_PERSIAN,
    SI_LANGUAGE_ALBANIAN,
    SI_LANGUAGE_VIETNAM,
    SI_LANGUAGE_HAUSA,
    SI_LANGUAGE_DAGBANI,
    SI_LANGUAGE_NZEMA,
    SI_LANGUAGE_AKAN,
    SI_LANGUAGE_EWE,
    SI_LANGUAGE_KASEM,
    SI_LANGUAGE_SWAHILI,    // Kenya
    SI_LANGUAGE_UKRAINIAN,
    SI_LANGUAGE_UNKNOWN,       //move to hear to avoid haveing same value as spanish.
    SI_LANGUAGE_AUDIO1,
    SI_LANGUAGE_AUDIO2,
    SI_LANGUAGE_AUDIO3,
    SI_LANGUAGE_AUDIO4,
    SI_LANGUAGE_AUDIO5,
    SI_LANGUAGE_AUDIO6,
    SI_LANGUAGE_BROADCAST_MIX,
    SI_LANGUAGE_MALAYSIA, //TKL-10Feb2014-2
    SI_LANGUAGE_MULTIPLE, //TKL-10Feb2014-2
    //TKL-7Mar2014-2>>>
    SI_LANGUAGE_SECOND_AUDIO,
    SI_LANGUAGE_THIRD_AUDIO,
    SI_LANGUAGE_TAMIL,
    //TKL-7Mar2014-2<<<
    SI_LANGUAGE_NONE = 0xFF,
} EN_SI_LANGUAGE;


typedef enum _EN_SI_TIMEZONE
{
    // GMT
    SI_TIMEZONE_GMT_0_START,
    SI_TIMEZONE_CANARY=SI_TIMEZONE_GMT_0_START,
    SI_TIMEZONE_LISBON,
    SI_TIMEZONE_LONDON,
    SI_TIMEZONE_RABAT,
    SI_TIMEZONE_GHANA,
    SI_TIMEZONE_IVORY_COAST,
    SI_TIMEZONE_DUBLIN,
    SI_TIMEZONE_GMT_0_END=SI_TIMEZONE_DUBLIN,

    // GMT + 1
    SI_TIMEZONE_GMT_1_START,
    SI_TIMEZONE_AMSTERDAM=SI_TIMEZONE_GMT_1_START,
    SI_TIMEZONE_BEOGRAD,
    SI_TIMEZONE_BERLIN,
    SI_TIMEZONE_BRUSSELS,
    SI_TIMEZONE_BUDAPEST,
    SI_TIMEZONE_COPENHAGEN,
    SI_TIMEZONE_LIUBLJANA,
    SI_TIMEZONE_LUXEMBOURG,
    SI_TIMEZONE_MADRID,
    SI_TIMEZONE_OSLO,
    SI_TIMEZONE_PARIS,
    SI_TIMEZONE_PRAGUE,
    SI_TIMEZONE_BRATISLAVA,
    SI_TIMEZONE_BERN,
    SI_TIMEZONE_ROME,
    SI_TIMEZONE_STOCKHOLM,
    SI_TIMEZONE_WARSAW,
    SI_TIMEZONE_VIENNA,
    SI_TIMEZONE_ZAGREB,
    SI_TIMEZONE_TUNIS,
    SI_TIMEZONE_ALGIERS,
    SI_TIMEZONE_GMT_1_END=SI_TIMEZONE_ALGIERS,

    // GMT + 2
    SI_TIMEZONE_GMT_2_START,
    SI_TIMEZONE_ATHENS=SI_TIMEZONE_GMT_2_START,
    SI_TIMEZONE_BUCURESTI,
    SI_TIMEZONE_HELSINKI,
    SI_TIMEZONE_SOFIA,
    SI_TIMEZONE_CAIRO,
    SI_TIMEZONE_CAPE_TOWN,
    SI_TIMEZONE_KALININGRAD,
    SI_TIMEZONE_ESTONIA,
    SI_TIMEZONE_TURKEY,
    SI_TIMEZONE_JERUSSLEM,
    SI_TIMEZONE_UKRAINE,
    SI_TIMEZONE_GMT_2_END=SI_TIMEZONE_JERUSSLEM,

    // GMT + 3
    SI_TIMEZONE_GMT_3_START,
    SI_TIMEZONE_MOSCOW=SI_TIMEZONE_GMT_3_START,
    SI_TIMEZONE_BAGHDAD,
    SI_TIMEZONE_DOHA,
    SI_TIMEZONE_RIYADH,
    SI_TIMEZONE_MANAMA,
    SI_TIMEZONE_KUWAIT, //Update By WangBoJing
    SI_TIMEZONE_KENYA,
    SI_TIMEZONE_NAIROBI,
    SI_TIMEZONE_GMT_3_END=SI_TIMEZONE_NAIROBI,

    // GMT + 3.5
    SI_TIMEZONE_GMT_3Point5_START,
    SI_TIMEZONE_TEHERAN=SI_TIMEZONE_GMT_3Point5_START,
    SI_TIMEZONE_GMT_3Point5_END=SI_TIMEZONE_TEHERAN,

    // GMT + 4
    SI_TIMEZONE_GMT_4_START,
    SI_TIMEZONE_ABU_DHABI=SI_TIMEZONE_GMT_4_START,
    SI_TIMEZONE_MUSCAT,
    SI_TIMEZONE_SAMARA,
    SI_TIMEZONE_PORTLOUIS,
    SI_TIMEZONE_ARMENIA,
    SI_TIMEZONE_GMT_4_END=SI_TIMEZONE_ARMENIA,

	 // GMT + 5
	SI_TIMEZONE_GMT_5_START,
	SI_TIMEZONE_MALE=SI_TIMEZONE_GMT_5_START,
	SI_TIMEZONE_GMT_5_END=SI_TIMEZONE_MALE,

	//GMT + 5.5
	SI_TIMEZONE_GMT_5Point5_START,    //add by daifq 20151127  //mengchaoyang 20160219
	SI_TIMEZONE_KATHMANDU=SI_TIMEZONE_GMT_5Point5_START,
	SI_TIMEZONE_COLOMBO,
	SI_TIMEZONE_GMT_5Point5_END=SI_TIMEZONE_COLOMBO,

	//GMT + 6
	SI_TIMEZONE_GMT_6_START, //Update By WangBoJing 20150518
	SI_TIMEZONE_KYRGYZ=SI_TIMEZONE_GMT_6_START,
	SI_TIMEZONE_DHAKA,
	SI_TIMEZONE_GMT_6_END=SI_TIMEZONE_DHAKA,

	 // GMT + 6.5
    SI_TIMEZONE_GMT_6Point5_START,
    SI_TIMEZONE_YANGON=SI_TIMEZONE_GMT_6Point5_START,
    SI_TIMEZONE_MYANMAR,
    SI_TIMEZONE_GMT_6Point5_END=SI_TIMEZONE_MYANMAR,

    //GMT + 7
    SI_TIMEZONE_GMT_7_START,
    SI_TIMEZONE_HCMC=SI_TIMEZONE_GMT_7_START,
    SI_TIMEZONE_BANGKOK,
    SI_TIMEZONE_HANOI,
    SI_TIMEZONE_PHNOMPENH,
    SI_TIMEZONE_VIENTIANE,
    SI_TIMEZONE_VIETNAM,
    SI_TIMEZONE_THAILAND,
    SI_TIMEZONE_INDONESIA_WEST,
    SI_TIMEZONE_GMT_7_END=SI_TIMEZONE_INDONESIA_WEST,

    //GMT + 8
    SI_TIMEZONE_GMT_8_START,
    SI_TIMEZONE_WA=SI_TIMEZONE_GMT_8_START,
    SI_TIMEZONE_KUALA_LUMPUR,
    SI_TIMEZONE_INDONESIA_CENTER,
    SI_TIMEZONE_SINGAPORE,
    SI_TIMEZONE_ULANBATOR,
    SI_TIMEZONE_BWN,
    SI_TIMEZONE_BEIJING,
    SI_TIMEZONE_GMT_8_END=SI_TIMEZONE_BEIJING,

    //GMT + 8.5
    SI_TIMEZONE_GMT_8Point5_START,
    SI_TIMEZONE_KOREA=SI_TIMEZONE_GMT_8Point5_START,
    SI_TIMEZONE_GMT_8Point5_END=SI_TIMEZONE_KOREA,

    // GMT + 9
    SI_TIMEZONE_GMT_9_START,
    SI_TIMEZONE_INDONESIA_EAST=SI_TIMEZONE_GMT_9_START,
    SI_TIMEZONE_GMT_9_END=SI_TIMEZONE_INDONESIA_EAST,

    //GMT + 9.5
    SI_TIMEZONE_GMT_9Point5_START,
    SI_TIMEZONE_SA=SI_TIMEZONE_GMT_9Point5_START,
    SI_TIMEZONE_NT,
    SI_TIMEZONE_GMT_9Point5_END=SI_TIMEZONE_NT,

    //GMT + 10
    SI_TIMEZONE_GMT_10_START,
    SI_TIMEZONE_NSW=SI_TIMEZONE_GMT_10_START,
    SI_TIMEZONE_VIC,
    SI_TIMEZONE_QLD,
    SI_TIMEZONE_TAS,
    SI_TIMEZONE_GMT_10_END=SI_TIMEZONE_TAS,

    //GMT +  12
    SI_TIMEZONE_GMT_12_START,
    SI_TIMEZONE_NZST = SI_TIMEZONE_GMT_12_START,
    SI_TIMEZONE_SUVA,
    SI_TIMEZONE_GMT_12_END =SI_TIMEZONE_SUVA,

    //GMT - 5
    SI_TIMEZONE_GMT_Minus5_START,
    SI_TIMEZONE_AM_WEST=SI_TIMEZONE_GMT_Minus5_START,
    SI_TIMEZONE_ACRE,
    SI_TIMEZONE_GMT_Minus5_END=SI_TIMEZONE_ACRE,

    //GMT - 4
    SI_TIMEZONE_GMT_Minus4_START,
    SI_TIMEZONE_M_GROSSO=SI_TIMEZONE_GMT_Minus4_START,
    SI_TIMEZONE_NORTH,
    SI_TIMEZONE_GMT_Minus4_END=SI_TIMEZONE_NORTH,

    //GMT - 3
    SI_TIMEZONE_GMT_Minus3_START,
    SI_TIMEZONE_BRASILIA=SI_TIMEZONE_GMT_Minus3_START,
    SI_TIMEZONE_NORTHEAST,
    SI_TIMEZONE_GMT_Minus3_END=SI_TIMEZONE_NORTHEAST,

     //GMT - 2
    SI_TIMEZONE_GMT_Minus2_START,
    SI_TIMEZONE_F_NORONHA=SI_TIMEZONE_GMT_Minus2_START,
    SI_TIMEZONE_GMT_Minus2_END=SI_TIMEZONE_F_NORONHA,

     //GMT - 1
    SI_TIMEZONE_GMT_Minus1_START,
    SI_TIMEZONE_AZORES=SI_TIMEZONE_GMT_Minus1_START,
    SI_TIMEZONE_GMT_Minus1_END=SI_TIMEZONE_AZORES,

    SI_TIMEZONE_NUM, //TIMEZONE MAX
} EN_SI_TIMEZONE;
/// RF Channel bandwidth
#ifndef ENABLE_RF_CHANNEL_BANDWIDTH
#define ENABLE_RF_CHANNEL_BANDWIDTH RF_CHANNEL_BANDWIDTH
typedef enum
{
    E_RF_CH_BAND_6MHz = 0x01,       ///< 6MHz
    E_RF_CH_BAND_7MHz = 0x02,       ///< 7MHz
    E_RF_CH_BAND_8MHz = 0x03,       ///< 8MHz
    E_RF_CH_BAND_INVALID            ///< Invalid
} RF_CHANNEL_BANDWIDTH;
#endif

typedef enum
{
    E_SI_DELIVERY_SYS_NONE = 0,
    E_SI_DELIVERY_SYS_TDSD,
    E_SI_DELIVERY_SYS_CDSD,
    E_SI_DELIVERY_SYS_SDSD

} EN_SI_DELIVERY_SYS_TYPE;

typedef struct
{
    WORD bValidLCN              : 1;
    WORD wSignalStrength        : 15;
//    WORD bIsMHEGIncluded        : 1;
    WORD bReplaceService        : 1;
    WORD eVideoType             : 3;
    WORD bServiceType           : 4;   //add service type 2 bit to 4 bit // for information from PMT for empty Video_PID
    WORD bIsServiceIdOnly       : 1;    // If the program is not shown in PAT, set to TRUE
    WORD bIsDataServiceAvailable: 1;    // If ttx or subtitle is available, the flag set to TRUE
    WORD bIsReplaceDel          : 1;
    WORD bIsSpecialService      : 1;   //RiksTV special service
    WORD bIsTerrestrial         : 1;
    WORD bValidLCNv2            : 1;
    WORD bInvalidService        : 1;   //add service type 2 bit to 4 bit // for information from PMT for empty Video_PID
    WORD bIsNewService          : 1;
    BYTE bVisibleServiceFlag    : 1;
    BYTE bNumericSelectionFlag  : 1;    // Hidden but selectable through direct numeric entry
    BYTE bIsScramble            : 1;    // 0=FTA, 1=Scramble
    BYTE bIsStillPicture        : 1;    // for information from Video_stream_descriptor(0x02)
    BYTE bServiceTypePrio       : 2;
    BYTE bInvalidCell           : 1;
    BYTE bUnconfirmedService    : 1;
    BYTE bIsFastScan            : 1;
    BYTE bIsbissSevice          : 1;
    BYTE bIsVirtualSevice       : 1;   // ENABLE_CI_PLUS_V1_4
    BYTE bIsOpService           : 1;
    BYTE reserved1              : 4;
} SI_CHANNEL_ATTRIBUTE;

/// ISO 639 Language
typedef struct
{
    BYTE bISOLangIndex;                     ///< ISO Language index
    BYTE bISOLanguageInfo   : 2;            ///< 0x00: Stereo, 0x01: Mono right, 0x02: Mono left
    BYTE bAudType           : 3;            ///< 0x00: Undefined, 0x01: Clean effects, 0x02: Hearing impaired, 0x03: Visual impaired commentary, 0x04~0xFF: Reserved.
    BYTE bIsValid           : 1;            ///< Valid or not
    BYTE bBroadcastMixedAD  : 1;            ///< broadcast mixed AD
    BYTE bReserved          : 1;            ///< Reserved
} SI_LANG_ISO639;

/// Audio information
typedef struct
{
    SI_LANG_ISO639 aISOLangInfo[SI_MAX_AUD_ISOLANG_NUM];   ///< ISO Language Info
    WORD wAudType           : 3;            ///<  0x01: MPEG, 0x02: AC-3, 0x03: MPEG4_AUD
    WORD wAudPID            : 13;           ///< Audio PID
    //WORD Reserved           : 1;            ///< Reserved
    U8 u8ProfileAndLevel;
    U8 u8Component_AAC_Type;
}SI_AUD_INFO;

typedef struct
{
    WORD wAudType           : 3;            ///<  0x01: MPEG, 0x02: AC-3, 0x03: MPEG4_AUD
    WORD wAudPID            : 13;           ///< Audio PID
}FileIn_SI_AUD_INFO;

/// Define struct information of desc_satellite_del_sys
typedef struct
{
    U32 u32CentreFreq; ////K/10 Hz
    U16 u16Orbital_pos;
    U8 u8West_east_flag     :1;
    U8 u8Polarization       :2; //2 bits 00:linear-horizontal, 01:linear-vertical
    U8 u8Roll_off           :2; //00:0,35 , 01:0,25 ,10:0,20 for DVB-S2
    U8 u8Modulation_system  :1; //1 bits 0:DVB-S, 1:DVB-S2
    U8 u8Modulation_type    :2; //2 bits 00:Auto, 01:QPSK, 10:8PSK, 11:16-QAM(n/a for DVB-S2)
    U32  u32Symbol_rate     :28; //Ms/s
    U32  FEC_inner          :4;
    BOOLEAN fFilled;        //flag to distinguish the descriptor is parsed and the structure is filled or not
} DESC_SATELLITE_DEL_SYS1; // Satellite delivery system descript

typedef struct __attribute__ ((__packed__))
{
    BYTE bVirtualChannel;
    BYTE bPhysicalChannel;
} ST_SI_LCN;
typedef struct
{
    U8 cRFChannelNumber;
    WORD wPCR_PID;
    WORD wVideo_PID;
    WORD wTransportStream_ID;
    WORD wOriginalNetwork_ID;
    WORD wNetwork_ID;
    WORD wCellID;
    WORD wOrder;
    union
    {
        #if 1//ENABLE_SBTVD_BRAZIL_APP
        ST_SI_LCN stLCN;
        #endif
        WORD wLCN;
    };
    WORD wPmt_PID;                          ///< PMT PID
    SI_TABLE_VERSION stPSI_SI_Version;
    SI_CHANNEL_ATTRIBUTE stCHAttribute;
    WORD wService_ID;
    WORD wTS_LCN;    // TS Logical channel descriptor LCN
    WORD wSimu_LCN;  //  for HD Simulcast Logical Channel number
    SI_AUD_INFO stAudInfo[SI_MAX_AUD_LANG_NUM];
#if (1)//(M7_DVBS_FAST_SCAN_ENABLE)
    DESC_SATELLITE_DEL_SYS1 stSatDelSys;
#endif //#if (M7_DVBS_FAST_SCAN_ENABLE)
    WORD wSgt_PID;
} SI_SHORT_DTV_CHANNEL_INFO;
typedef struct __attribute__ ((__packed__))//Same TS ID and Original Network ID
{
    U16 u16ServiceID;
    union __attribute__ ((__packed__)) // unify mips and R2 lib for "union"
    {
#if 1//ENABLE_SBTVD_BRAZIL_APP
        ST_SI_LCN stLCN;
#endif
        U16 u16LCNNumber;
    };

    U16  u16SimuLCNNumber:11;//  for HD Simulcast Logical Channel number
    U16  u8fVisable :1;   // In UK, this flag is in service_attribute_descriptor.
    U16  u8fSelectable:1; // In UK, this flag is in service_attribute_descriptor.
    U16  u8IsSpecialService:1;  //RiksTV special service
    U16  u8Reserved :2;
} MS_LCN_INFO;

typedef struct __attribute__ ((__packed__))//Same TS ID and Original Network ID
{
    U16  u16ServiceID;
    U16  u16LCNNumber;
    U16  u16SimuLCNNumber:11;//  for HD Simulcast Logical Channel number
    U16  u8fVisable :1;      // In UK, this flag is in service_attribute_descriptor.
    U16  u8fSelectable:1;    // In UK, this flag is in service_attribute_descriptor.
    U16  u8IsSpecialService:1;  //RiksTV special service
    U16  u8Reserved :2;
} MS_SERVICE_LCN_INFO;



typedef struct
{
    U16 u16ProgramNumber;
    U8 u8ServiceType;
    U8 u8ServicePriority;
} MS_SERVICE_LIST_INFO;


typedef struct// __attribute__ ((__packed__))//Same TS ID and Original Network ID
{
    WORD wTransportStream_ID;
    WORD awCellID[SI_MAX_FREQUENCY_LIST];
    MS_LCN_INFO stLcnInfo[SI_MAX_VC_PER_PHYSICAL];
    BYTE   acRFIndex[SI_MAX_FREQUENCY_LIST];
    U8 bHaveService:1;
    U8 bNewServiceInNewCell:1;
    U8 reserved:6;
} MS_NETWORK_INFO;
#define NETWORK_INFO_LEN    (sizeof(MS_NETWORK_INFO)*SI_MAX_TS_IN_NETWORK)


typedef struct
{
    WORD bIDIdex;                           // Index to Program ID table
    WORD wPCR_PID;                          ///< PCR PID
    WORD wVideo_PID;                        ///< Video PID
    WORD wOrder;                            ///< Order
    union
    {
        ST_SI_LCN stLCN;
        WORD wLCN;
    };
    WORD wPmt_PID;                          ///< PMT PID
    SI_TABLE_VERSION stPSI_SI_Version;      ///< PSI/SI Version
    SI_CHANNEL_ATTRIBUTE stCHAttribute;     ///< Channel attribute
    WORD wService_ID;                       ///< Service ID
    WORD wTS_LCN;  // TS Logical channel descriptor LCN
    WORD wSimu_LCN;  //  for HD Simulcast Logical Channel number
    SI_AUD_INFO stAudInfo[SI_MAX_AUD_LANG_NUM];   ///< Audio info
    BYTE bChannelName[SI_MAX_SERVICE_NAME];    ///< Channel name
    BYTE bProviderName[SI_MAX_SERVICE_NAME];    ///< Channel Provider name
    BYTE satid;
    WORD wSgt_PID;
} SI_DTV_CHANNEL_INFO;

typedef struct
{
    WORD wTransportStream_ID;           // Transportstream ID
    WORD wOriginalNetwork_ID;           // Original Network ID
    WORD wNetwork_ID;           // Network ID
#if 1//(ENABLE_SAVE_SQI)
    WORD wStrengthQuality;
#endif
    WORD wCellID;                   //Cell ID
    DWORD  dwAlternativeTime;    // for alternative RF start time
#if 1//(ENABLE_DVB_S2)
    WORD cRFChannelNumber;
#else
    BYTE cRFChannelNumber;              // RF Channel Number
#endif
    BYTE cOriginal_RF;           // for original RF
#if 1//(ENABLE_DVB_S2)
    BYTE SatelliteId;
    U32 u32S2Frequency;
    U16 u16SymbolRate;
    BYTE u8Polarity;
#endif
    #if 1//def ENABLE_DVBC
    U32  u32Frequency;
    U32  u32SymbRate;
    BYTE QamMode;
    RF_CHANNEL_BANDWIDTH enBandWidth;
    #endif
#if 1//def DVB_T2_ENABLE
    U8 u8PLP_ID;
#endif
    U8 u8HpLp;
    U8 u8Region;
} SI_DTVPROGRAMID;



#if 1//(ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
#define NETWORK_INFO_PACKED __attribute__ ((__packed__))
typedef struct
{
    WORD wTransportStream_ID;               ///< Transportstream ID
    U8 au8RF[SI_MAX_FREQUENCY_LIST];    ///< Channel name
    WORD awCell[SI_MAX_FREQUENCY_LIST];
} DTV_TS_RF_INFO;

typedef struct
{
    WORD wTransportStream_ID;
    U16 wService_ID;
}MS_SI_SHORT_SERVICEINFO;

typedef struct NETWORK_INFO_PACKED
{
    U16 u16Network_ID;
    DTV_TS_RF_INFO astTSRFList[SI_MAX_TS_IN_NETWORK];
    U16 bInValidNetwork :1;
    U16 bNewTS :15;
    U16 bNewService;
} MS_NETWORKID_TS;

typedef struct NETWORK_INFO_PACKED
{
    U16 NetWorkInfoCS;// check sum <<checksum should be put at top of the struct, do not move it to other place>>

    MS_NETWORKID_TS astNetworkInfo[SI_MAX_NETWORK];
} MS_ALL_NETWORKID_INFO;

typedef struct
{
    U16 u16ServiceID;
    U16 u16LCNNumber;
    BOOLEAN bIsVisable;
}LOGICAL_LIST_V2;

typedef struct
{
    U8 u8ChanListId;
    U8 u8ChanListNameLen;
    U8 u8ChanListName[23];
    U8 u8CountryCode2[3];
    U8 u8CountryCode;

    U8 u8Count;
    LOGICAL_LIST_V2 list[SI_MAX_LOGICAL_LIST_V2];
} LOGICAL_CHANNEL_V2;

//Add TOT All Information
typedef struct
{
    EN_SI_COUNTRY_SETTING  eCountryIdx;
    U8  u8RegionId    :6;
    U8  u8Reserved    :1;
    U8  u8LTOPolarity :1;  // local_time_offset_polarity
    U16 u16LTO;           // Local_time_offset
    U8  au8TimeOfChange[5];
    U16 u16NextTimeOffset;

} SI_LTOInfo;

typedef struct
{
    U8 au8UTCTime[5];
    SI_LTOInfo aLTOTInfo; // Local time offset info.

} SI_TOT_MONITOR_ALL_INFO;

#if (ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
 /// this is max length of service name
#define MAPI_SI_MAX_SERVICE_NAME     70//48 //for HD Simulcast Logical Channel number
#define SI_MAX_SGT_TABLE_NUMBER      5

/// Define struct information of Linkage descriptor
typedef struct
{
    U16 u16TSId;            /// transport_stream_id
    U16 u16ONId;           /// original_network_id
    U16 u16ServiceId;     /// service_id
    U8  u8LinkageType;   /// linkage_type
    U8  u8HandOverType      :4; //hand-over_type. Only vilid if u8LinkageType == 0x08.
    U8  u8OriginType        :1; //origin_type. Only vilid if u8LinkageType == 0x08.
    U8  u8Ser_Replacement   :1; //Only vilid if u8LinkageType == 0x08.
    U8  u8Reserved          :2; //Only vilid if u8LinkageType == 0x08.
    U16 u16NetworkId;           //Only vilid if u8LinkageType == 0x08 && u8OriginType != 0.
    U16 u16InitServiceId;       //Only vilid if u8LinkageType == 0x08 && u8OriginType == 0.
    U8  u8PrivDataLeng;
    U8  *pu8PrivData;

} MS_SI_DESC_LINKAGE_INFO;

typedef struct
{
   MS_SI_DESC_LINKAGE_INFO stSGTNitLD[SI_MAX_SGT_TABLE_NUMBER];

}MS_SI_DESC_NIT_LINKAGE_INFO;

///to record the triple id for Nvod timeshifted services
typedef struct
{
    U16 u16OnId;
    U16 u16TsId;
    U16 u16SrvId;
}ST_TRIPLE_PROGRAM_ID;

/// Define service info carried in SGT
typedef struct
{
    /// service name
    U8  au8ServiceName[MAPI_SI_MAX_SERVICE_NAME];
    /// service name length
    U8  au8ServiceNameLength;
    /// service triple id
    ST_TRIPLE_PROGRAM_ID stTripleIds;
    /// service lcn
    U16      u16LCN;
    /// virtual service id
    U16      u16VirtualServiceID;
    /// service type
    U8   u8ServiceType;
    /// service prio
    U8 u8ServiceTypePrio;
    /// serivice is visble or not
    BOOLEAN      bIsVisble;
    /// service is new service or not
    BOOLEAN      bIsNewService;
    /// CA identifier descriptor ; is this descriptor existed equal to scrambled , the behavior is like event ; do not need to care about CA_system_id;
    BOOLEAN      bIsServiceScrambled;
    /// Sgt pid
    WORD wSgt_PID;
    /// Version Number
    U8 u8Version;

}MS_SI_SGT_SERVICE_INFO;

typedef struct
{
    U16 u16ProgramNumber;  // Service_id
    U16 wPrivateSgtPID;    // SGT Table PID
    U8  u8Sgtversion;      // SGT Table version
} MS_SGT_ITEM;

#endif //#if (ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)

#if(MHEG5_SIINFO_ENABLE)

typedef struct
{
     U8     u8ServiceType;      //service_type
     BYTE bServiceName[SI_MAX_SERVICE_NAME];    ///service name//< Channel name
     BYTE bProviderName[SI_MAX_SERVICE_NAME];   //service_provider_name

}MS_SI_SERVICEINFO;

#endif //#if (M7_DVBS_FAST_SCAN_ENABLE)


#if(SI_MAX_TS_IN_NETWORK>15)
#error max SI_MAX_TS_IN_NETWORK is 15
#endif
#endif

/******************************************************************************/
/*                       Global Variable Declarations                         */
/******************************************************************************/
#ifdef MAPP_SI_IF_C
#define INTERFACE
#else
#define INTERFACE extern
#endif





/******************************************************************************/
/*                       Global Function Prototypes                           */
/******************************************************************************/
INTERFACE U16 MApp_SI_GetUI_CurFocusSrvPos(void);
INTERFACE MEMBER_SI_SERVICETYPE MApp_SI_GetUI_CurFocusSrvType(void);
INTERFACE MEMBER_SI_SERVICETYPE msAPI_SI_GetCurrentServiceType(void);
INTERFACE U16 msAPI_SI_GetCurrentPosition(MEMBER_SI_SERVICETYPE bServiceType);
INTERFACE U8 msAPI_SI_GetPhysicalChannelNumber(MEMBER_SI_SERVICETYPE bServiceType, U16 wPosition);
INTERFACE U16 msAPI_SI_GetService_ID(MEMBER_SI_SERVICETYPE bServiceType, U16 wPosition);
INTERFACE U16 msAPI_SI_GetCurrentService_ID(void);
INTERFACE U16 msAPI_SI_GetPmtPID(MEMBER_SI_SERVICETYPE bServiceType, U16 wPosition);
INTERFACE U8 msAPI_SI_GetPSISIVersion(MEMBER_SI_SERVICETYPE bServiceType, U16 wPosition, E_PSI_SI_VERSION eVersionMember);
INTERFACE U16 msAPI_SI_GetTS_ID(MEMBER_SI_SERVICETYPE bServiceType, U16 wPosition);
INTERFACE U16 msAPI_SI_GetON_ID(MEMBER_SI_SERVICETYPE bServiceType, U16 wPosition);
INTERFACE U16 msAPI_SI_GetLogicalChannelNumber(MEMBER_SI_SERVICETYPE bServiceType, U16 wPosition);
INTERFACE U16 msAPI_SI_GetOriginalLogicalChannelNumber(MEMBER_SI_SERVICETYPE bServiceType, U16 wPosition);
INTERFACE WORD msAPI_SI_GetSimuLogicalChannelNumber(MEMBER_SI_SERVICETYPE bServiceType, WORD wPosition);
INTERFACE BOOLEAN msAPI_SI_IsLogicalChannelNumberExist(MEMBER_SI_SERVICETYPE bServiceType, U16 wLCN, U16* pPosition );
INTERFACE U16 msAPI_SI_GetNetwork_ID(MEMBER_SI_SERVICETYPE bServiceType, U16 wPosition);
INTERFACE BOOLEAN msAPI_SI_Get_PHYSICAL_CHANNEL_NUMBER(U32 u32Frequency, U8 *u8RFIndex);
INTERFACE BOOLEAN msAPI_SI_GetCellIDByPosition(MEMBER_SI_SERVICETYPE bServiceType, U16 wPosition, U16* pCellID);
INTERFACE U8 msAPI_SI_GetPhysicalChannelNumberByID(WORD wONID, WORD wTSID);
INTERFACE BOOLEAN msAPI_SI_GetCEllID_WithID(WORD wTS_ID, WORD wON_ID, WORD *pwCell_ID, BOOLEAN *bOverOneCell);
INTERFACE BOOLEAN msAPI_SI_GetPLP_ID_WithID(WORD wTS_ID, WORD wON_ID, U8 *pu8PLP_ID);
INTERFACE BOOLEAN msAPI_SI_GetHpLp_WithID(WORD wTS_ID, WORD wON_ID, U8 *pu8HpLp);
INTERFACE BOOLEAN msAPI_SI_GetProgramAttribute(MEMBER_SI_SERVICETYPE bServiceType, WORD wPosition, E_SI_MEMBER_CHANNEL_ATTRIBUTE eAttributeMember);
INTERFACE U8 msAPI_SI_RemoveQuickInstallMismatchedProgram(SI_SHORT_DTV_CHANNEL_INFO *pastVirtualCh,U8 u8NumOfVch,BYTE bIDIndex, MEMBER_SI_SERVICETYPE eServiceType);

#if 1//(M7_DVBS_FAST_SCAN_ENABLE)
INTERFACE U8 msAPI_SI_RemoveMismatchedProgram(BYTE cRFChannelNumber, U16 wTS_ID, U8 u8PLP_ID,U8 u8HpLp,  U16 *pwService_ID, MEMBER_SI_SERVICETYPE *peService_Type, WORD cCountOfServiceID);
INTERFACE U16 msAPI_SI_RemoveMismatchedProgram_ALLPCN(MS_SI_SHORT_SERVICEINFO *pwService_Info, MEMBER_SI_SERVICETYPE *peService_Type, U16 cCountOfServiceID);
#else
INTERFACE U8 msAPI_SI_RemoveMismatchedProgram(BYTE cRFChannelNumber, U16 wTS_ID, U8 u8PLP_ID, U8 u8HpLp, U16 *pwService_ID, MEMBER_SI_SERVICETYPE *peService_Type, BYTE cCountOfServiceID);
INTERFACE U16 msAPI_SI_RemoveMismatchedProgram_ALLPCN(MS_SI_SHORT_SERVICEINFO *pwService_Info, MEMBER_SI_SERVICETYPE *peService_Type, U16 cCountOfServiceID);
#endif //#if (M7_DVBS_FAST_SCAN_ENABLE)
INTERFACE BOOLEAN msAPI_SI_RemoveProgram(MEMBER_SI_SERVICETYPE bServiceType, WORD wPosition);
INTERFACE BOOLEAN msAPI_SI_RemoveOpAndVirtualInDb(void);

INTERFACE BOOLEAN msAPI_SI_GetServiceTypeAndPositionWithIDs(U16 wTransportStream_ID, U16 wOriginalNetwork_ID, U16 wService_ID, U8 cOrdinal, MEMBER_SI_SERVICETYPE * peServiceType, WORD * pwPosition, BOOLEAN bCheckTsID, BOOLEAN *pbInvalid, BOOLEAN *pbVisible);
INTERFACE BOOLEAN msAPI_SI_GetServiceTypeAndPositionWithIDsandServiceType(U16 wTransportStream_ID, U16 wOriginalNetwork_ID, U16 wService_ID, MEMBER_SI_SERVICETYPE wService_Type, U8 cOrdinal, MEMBER_SI_SERVICETYPE * peServiceType, WORD * pwPosition, BOOLEAN bCheckTsID, BOOLEAN *pbInvalid, BOOLEAN *pbVisible);
INTERFACE BOOLEAN msAPI_SI_GetServiceTypeAndPositionWithIDsAndRFCH(U16 wTransportStream_ID, U16 wOriginalNetwork_ID, U16 wService_ID, U8 cOrdinal, MEMBER_SI_SERVICETYPE * peServiceType, WORD * pwPosition, BOOLEAN bCheckTsID, BOOLEAN *pbInvalid, BOOLEAN *pbVisible, U8 u8RFChannelNumber);
#if(MHEG5_SIINFO_ENABLE)
INTERFACE BOOLEAN msAPI_SI_GetProviderName(MEMBER_SI_SERVICETYPE bServiceType, WORD wPosition, BYTE * bProviderName, U16 *pMaxLen);
#endif //#if(MHEG5_SIINFO_ENABLE)
INTERFACE void msAPI_SI_FillProgramDefaultDataWithoutSrvName(SI_SHORT_DTV_CHANNEL_INFO *pstShortDtvPgmData);
INTERFACE BOOLEAN msAPI_SI_FillProgramDataWithDefault(SI_DTV_CHANNEL_INFO *pstShortDtvPgmData);

INTERFACE BOOLEAN msAPI_SI_AddProgramIDTable(SI_DTVPROGRAMID *pstDtvIDTable, WORD *pu16IDIdex);

INTERFACE BOOLEAN msAPI_SI_AddProgram(SI_DTVPROGRAMID *stDtvIDTable, SI_DTV_CHANNEL_INFO *pDTVProgramData, BOOLEAN *bDBFull, BOOLEAN bSkipCheck);
INTERFACE WORD msAPI_SI_CountProgram(MEMBER_SI_SERVICETYPE bServiceType, SI_COUNT_PROGRAM_OPTION eCountOption);
INTERFACE U8 msAPI_SI_GetCountOfSameServiceWithIDs(WORD wTransportStream_ID, WORD wOriginalNetwork_ID, WORD wService_ID);
INTERFACE BOOLEAN msAPI_SI_GetServiceName(MEMBER_SI_SERVICETYPE bServiceType, WORD wPosition, BYTE * bChannelName, U16 *pMaxLen);
INTERFACE BOOLEAN msAPI_SI_Get_CELL_ID( WORD * pwCell_id);
INTERFACE BOOLEAN msAPI_SI_Get_PLP_ID( U8 * pu8PLP_ID);
INTERFACE U8 msAPI_SI_Get_HpLp( void);
INTERFACE BOOLEAN msAPI_SI_Is_TSExist(WORD wONID, WORD wTSID, BYTE *pcRFChannelNumber);
INTERFACE BOOLEAN msAPI_SI_IsServiceExistWithIDsAndLCN(WORD wOriginalNetwork_ID, WORD wService_ID,  WORD wLCN);
INTERFACE BOOLEAN msAPI_SI_SetMismatchedCell(WORD wONID, WORD wTSID, WORD *pCellLsit, U8 u8CellNumber, BOOLEAN *bRemoved);
INTERFACE BOOLEAN msAPI_SI_UpdateProgramVisibleAndSelectable(MEMBER_SI_SERVICETYPE bServiceType, WORD wPosition, BOOLEAN bVisible, BOOLEAN bSelectable);
INTERFACE BOOLEAN msAPI_SI_UpdateProgramSpecialService(MEMBER_SI_SERVICETYPE bServiceType, WORD wPosition, BOOLEAN bSpecialService);
INTERFACE BOOLEAN msAPI_SI_UpdateQuickInstallProgram(MEMBER_SI_SERVICETYPE bServiceType, WORD wPosition, SI_DTV_CHANNEL_INFO *pstDtvPgmData);
INTERFACE BOOLEAN msAPI_SI_UpdateProgram(MEMBER_SI_SERVICETYPE bServiceType, WORD wPosition, BYTE *pcBuffer, E_SI_DATA_MEMBER eMember);
INTERFACE BOOLEAN msAPI_SI_RecoveryDelProgram(MEMBER_SI_SERVICETYPE bServiceType, WORD wPosition);
INTERFACE BOOLEAN msAPI_SI_DeleteProgram(MEMBER_SI_SERVICETYPE bServiceType, WORD wPosition);
INTERFACE BOOLEAN msAPI_SI_ReplaceDelProgram(MEMBER_SI_SERVICETYPE bServiceType, WORD wPosition, BOOLEAN bDel);
INTERFACE BOOLEAN msAPI_SI_SetCurrentServiceType(MEMBER_SI_SERVICETYPE bServiceType);
INTERFACE BOOLEAN msAPI_SI_SetCurrentPosition(MEMBER_SI_SERVICETYPE bServiceType, WORD wPosition);
INTERFACE BOOLEAN msAPI_SI_RemoveMismatchedMux(WORD wNID, WORD *pwTS_ID,  BYTE cCountOfTS, U32 *u32NewTS, BOOLEAN bRemove);
INTERFACE BOOLEAN msAPI_SI_Is_NetworkTSChange(void);
INTERFACE BOOLEAN msAPI_SI_CheckNetwork(WORD wNID, WORD *pwTS_ID,  BYTE cCountOfTS, U32 *u32NewTS, WORD *pwRemoveTSID, BYTE cMaxTSCnt, BOOLEAN *bRemove);
INTERFACE BOOLEAN msAPI_SI_SetUnconfirmedServiceInvalid(WORD wONID, WORD wTSID, BOOLEAN *bGotService);
INTERFACE BOOLEAN msAPI_SI_ArrangeDataManager(void);
INTERFACE U16 msAPI_SI_GetCurrentSignalStrength(void);
INTERFACE void msAPI_SI_Reset_AudioValidIndex(void);
INTERFACE U32 msAPI_SI_Timer_DiffTimeFromNow(U32 u32TaskTimer); //unit = ms
INTERFACE U32 msAPI_SI_Timer_GetTime(void);
INTERFACE U32 msAPI_SI_Timer_DiffTime(U32 u32Timer, U32 u32TaskTimer);
INTERFACE void msAPI_SI_Timer_ResetWDT(void);
INTERFACE void msAPI_SI_Timer_Delayms(U32 u32DelayTime); //unit = ms
INTERFACE S32 msAPI_SI_Timer_GetOffsetTime(void);
INTERFACE void msAPI_SI_Timer_SetSystemTime(U32 u32SystemTime); //unit = sec
INTERFACE void msAPI_SI_Timer_SetOffsetTime(S32 s32OffsetTime); //unit = sec
INTERFACE U32 msAPI_SI_Timer_GetSystemTime(void);
INTERFACE U16 MApp_SI_CharTable_MappingDVBTextToUCS2(U8 *pu8Str, U16 *pu16Str, U16 srcByteLen, U16 dstWideCharLen,  BOOLEAN bRemoveHyphen);
INTERFACE void * msAPI_SI_Memory_Allocate(U16 u16Number_of_bytes);
INTERFACE U8 msAPI_SI_Memory_Free(void *pFree);
INTERFACE BOOLEAN msAPI_SI_CreateMutex(U8 u8MutexID);
INTERFACE BOOLEAN msAPI_SI_WaitMutex(U8 u8MutexID);
INTERFACE BOOLEAN msAPI_SI_ReleaseMutex(U8 u8MutexID);
INTERFACE void msAPI_SI_UpdateNetworkName(WORD wNID, U8 *pu8NetwrokName, U8 u8NetworkNameLen);
INTERFACE U32 msAPI_SI_DecodeStr(const U8 *pbufEncStr, U32 nLenStr, U8 nEncodeType, U8 *pbufDecStr, U32 nMaxBufDecStr);
INTERFACE U32 msAPI_SI_HuffmanDecode(const U8 *pbufEncStr, U32 nLenStr, U8 nEncodeType, U8 *pbufDecStr, U32 nMaxBufDecStr);
INTERFACE EN_SI_LANGUAGE msAPI_SI_GetLanguageByISO639LangCode(U8 *pSrc);
INTERFACE EN_SI_COUNTRY_SETTING msAPI_SI_GetCountryByTimeZone(EN_SI_TIMEZONE eTimeZone);
INTERFACE EN_SI_TIMEZONE msAPI_SI_GetTimeZoneByCountry(EN_SI_COUNTRY_SETTING eCountry);
INTERFACE EN_SI_COUNTRY_SETTING msAPI_SI_GetCountryByISO3166CountryCode(U8 *pSrc);
INTERFACE BOOLEAN msAPI_SI_GetISO3166CountryCodeFromIndex(EN_SI_COUNTRY_SETTING enIndex, U8 *pBuf);
INTERFACE BOOLEAN msAPI_SI_GetISOLangCodeFromIndex(EN_SI_LANGUAGE enIndex, U8 *pBuf);
INTERFACE U8 msAPI_SI_GetDefaultRegion(EN_SI_TIMEZONE eTimeZone);
INTERFACE void msAPI_SI_GetCurrentRfParams(SI_DTVPROGRAMID *pstDtvIDTable);
INTERFACE void msAPI_SI_SetTargetRegionProgram(U16 u16ONID, U16 u16TSID, U16 u16SID, U8 u8Value);
INTERFACE BOOLEAN msAPI_SI_IsSpecificCountry(EN_SI_COUNTRY_SETTING eCountry, E_SI_SPECIFIC_COUNTRY eSpecificCountry);
INTERFACE void msAPI_SI_Timer_SetTimeOfChange(U32 u32TimeOfChg);
INTERFACE void msAPI_SI_Timer_SetNextTimeOffset(S32 s32OffsetTime);
INTERFACE BOOLEAN msAPI_SI_Action_CheckServiceInfo_SBTVD( SI_DTV_CHANNEL_INFO *pstVirtualCh );
INTERFACE BOOLEAN msAPI_SI_Action_CheckServiceInfo_DVB( SI_DTV_CHANNEL_INFO *pstVirtualCh );
INTERFACE BOOLEAN msAPI_SI_Action_CheckServiceType_DVB( U8 u8OriginalType, U8* pNewType );
INTERFACE BOOLEAN msAPI_SI_Action_CheckServiceType_SBTVD( U8 u8OriginalType, U8* pNewType );
INTERFACE BOOLEAN msAPI_SI_AutoClockMode(void);
INTERFACE BOOLEAN msAPI_SI_GetServiceByLogicalChannelNumber(MEMBER_SI_SERVICETYPE bServiceType, U16 wLCN, WORD *pWPosition);
INTERFACE MS_NETWORKID_TS* msAPI_SI_GetNetworkInfo(U8 u8NetworkIndex);
INTERFACE BOOLEAN msAPI_SI_RestLCNInCurrentRF(WORD* pServiceList, U16 wNumber);
INTERFACE BYTE msAPI_SI_GetCurrentRF(void);
#if 1 // (ENABLE_DVB_S2)
INTERFACE BOOLEAN msAPI_SI_RemoveMux(WORD wNID, WORD *pwTS_ID,  BYTE cCountOfTS, BOOLEAN *bRemove, BYTE sat,WORD freq);
#else
INTERFACE BOOLEAN msAPI_SI_RemoveMux(WORD wNID, WORD *pwTS_ID,  BYTE cCountOfTS, BOOLEAN *bRemove);
#endif
INTERFACE void msAPI_SI_CheckMuxParamChange(U16 u16TSID, U16 u16NID, U32 u32CentreFreq, U32 u32SymbolRate, BYTE cQamMode);

INTERFACE BOOLEAN msAPI_SI_GetOpMode(void);
INTERFACE void msAPI_SI_SetEITUpdate(BOOLEAN bUpdate);
#if 1 // (ENABLE_DVB_S2)
INTERFACE BOOLEAN msAPI_SI_GetIDIndexWithFreq(U32 u32Freq, WORD *cIDIndex);
#else
INTERFACE BOOLEAN msAPI_SI_GetIDIndexWithFreq(U32 u32Freq, BYTE *cIDIndex);
#endif
INTERFACE BOOLEAN msAPI_SI_ResetDTVDataManager(BOOLEAN bResetAllDB);
#if 1 // (ENABLE_DVB_S2)
INTERFACE BOOLEAN ISDVBS2Source(void);
INTERFACE BOOLEAN MApp_SI_Get_S2_TpInfo( SI_DTVPROGRAMID  *s2currenttp );
#endif

INTERFACE void msAPI_SI_GetLCDV2(LOGICAL_CHANNEL_V2 *pLCDV2);
INTERFACE BOOLEAN msAPI_SI_SaveLCDV2(const LOGICAL_CHANNEL_V2 *pstLCNv2, U16 u16MiniChannelId, BOOLEAN bSortFlag, BOOLEAN bReset);
INTERFACE void msAPI_SI_SetLCDV2Flag(BOOLEAN bRescanFlag, LOGICAL_CHANNEL_V2 *pLCDV2);
INTERFACE BOOLEAN msAPI_SI_GetLCDV2Flag(LOGICAL_CHANNEL_V2 *pLCDV2);

#if (ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
INTERFACE BOOLEAN msAPI_SI_SaveServiceListInfo(const U8 *u8ServiceListName, U16 u16ServiceListID, EN_SI_COUNTRY_SETTING eCountry, BOOLEAN bIsCountryAvailability,BOOLEAN bListInFlag);
INTERFACE BOOLEAN msAPI_SI_GetExistServiceListInfo(const U16 u16ServiceListID, BOOLEAN bListInFlag);
INTERFACE U16 msAPI_SI_GetCurrentServiceListID(void);
INTERFACE U16 msAPI_SI_GetAvailableServiceListID(void);
INTERFACE BOOLEAN msAPI_SI_SaveAstraServiceInfo(U16 u16ServiceListID, MS_SI_SGT_SERVICE_INFO *stServiceInfo);
INTERFACE void msAPI_SI_IsAdd2List(BOOLEAN Enable);
INTERFACE void msAPI_SI_GetSgtVersionandPID(MS_SGT_ITEM *pstCurSgtVerandPID);
#endif   //#if(ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)

#if (M7_DVBS_FAST_SCAN_ENABLE)
INTERFACE BOOLEAN msAPI_SI_SetSatePlatform(EN_SATELLITE_PLATFORM enSatePlatform);
INTERFACE EN_SATELLITE_PLATFORM msAPI_SI_GetSatePlatform(void);
INTERFACE U16 msAPI_SI_GetOPTSENPIDBySatePlatform(EN_SATELLITE_PLATFORM eSatellitePlatform);
INTERFACE BOOLEAN msAPI_SI_UpdateProgramInfo(MEMBER_SI_SERVICETYPE bServiceType, WORD wPosition, SI_SHORT_DTV_CHANNEL_INFO* pastVirtualCh, BYTE *bChanelNameBuffer, E_SI_DATA_MEMBER eMember);
INTERFACE BOOLEAN msAPI_SI_DVBS_GetServiceTypeAndPositionWithServiceIDs(U16 wTransportStream_ID, U16 wOriginalNetwork_ID, U16 wService_ID, U8 cOrdinal, MEMBER_SI_SERVICETYPE * peServiceType, WORD * pwPosition, BOOLEAN *pbInvalid,BOOLEAN *pbVisible);
INTERFACE BOOLEAN msAPI_SI_Action_Set_M7DVBS_OpenMonitor(BOOLEAN bEnable);
#endif   //#if (M7_DVBS_FAST_SCAN_ENABLE)

INTERFACE U32 msAPI_SI_Get_ServiceNameBufLen(void);

INTERFACE BOOL MApp_SI_Check_LibStructureSize(void);
INTERFACE void msAPI_SI_UpdateNetworkCDSD(U8 u8PhNum,U32 u32Freq,U32 u32Symb,U8 u8Modu);


//use for ENABLE_S2_NZ_FREEVIEW and ENABLE_BAT_MONITOR
INTERFACE EN_SI_BOUQUET_ID MApp_SI_GET_BouquetID(void);
INTERFACE BOOLEAN MApp_SI_Need2Parse_BAT(void);

INTERFACE BOOL Mapp_SI_CI_HSS_Get(void);
INTERFACE void Mapp_SI_CI_HSS_Check(void);
//#if ENABLE_CI_PLUS_V1_4
INTERFACE BOOLEAN msAPI_SI_SaveCIVirtualService(U8 *pu8Data);
//#endif
#undef INTERFACE


#endif//#if(MAPP_SI_IF_H)
#endif

