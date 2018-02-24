////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __API_DTVSYSTEM_H__
#define __API_DTVSYSTEM_H__


#include "Board.h"



#define ENABLE_CM_STORE_AUD_INFO_NEW_METHOD 0


#define ENABLE_DTV_STORE_TTX_PAGE_INFO FALSE

/// Program accessible boundary
typedef enum
{
    E_PROGACESS_INCLUDE_VISIBLE_ONLY        = 0x00, // if ( invisable or delete) , skip    //< Program access include visible only

    E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO    = 0x01, // if ( delete) , skip  //< Program access Also include Not visible

    E_PROGACESS_INCLUDE_ALL                 = 0x02,      ///< Program access Also include Not visible

    E_PROGACESS_OPTION_MAX                  = 3,

} E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY;

#define EXCLUDE_NOT_VISIBLE_AND_DELETED     E_PROGACESS_INCLUDE_VISIBLE_ONLY
#define INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO
#define INCLUDE_ALL                         E_PROGACESS_INCLUDE_ALL
#define MAX_COUNT_PROGRAM_OPTION            E_PROGACESS_OPTION_MAX
#define COUNT_PROGRAM_OPTION                E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY

//=======================================================================================================


//#include "msAPI_FreqTableCommon.h"
//#define DTVDATA_ID                  0xA55A

#if(ENABLE_DTV) //(ENABLE_API_DTV_SYSTEM)

#include "msAPI_FreqTableCommon.h"
#include "msAPI_Global.h"
#include "msAPI_MW_GlobalSt.h"

#include "apiAUDIO.h"

#include "mapp_si_if.h"
#include "mapp_si.h"

#include "msAPI_demux.h"
#include "msAPI_DTV_Common.h"

#include "MApp_GlobalSettingSt.h"

#if(ENABLE_ATSC)
#include "msAPI_DTVSystem_ATSC.h"
#endif

//------------------------------------------------------------------------------
// Version Check
//------------------------------------------------------------------------------
#define CM_VER()   'M','S','I','F',                   /* Version ID Header    */ \
                         '1','0',                           /* Info Class Code      */ \
                         0x66,0x66,                         /* Customer ID          */ \
                         0x66,0x66,                         /* Module ID            */ \
                         0xFF,0xFF,                         /* Chip ID              */ \
                         '1',                               /* CPU                  */ \
                         'C','M','_','_',                   /* Library Code         */ \
                         '0','0',                           /* Library Ver          */ \
                         '0','0','0','0',                   /* Build Number         */ \
                         '0','0','1','1','6','6','7','9',   /* P4 Change Number     */ \
                         '0'                                /* OS                   */ \

//------------------------------------------------------------------------------
// Public attributes.
//------------------------------------------------------------------------------

#define INVALID_FREQUENCY                   0x0

#define INVALID_SYMBRATE                    0x0

#if ENABLE_DVBC
#define FREQ_OFFSET_RANGE               300     //unit: KHz
#define INVALID_QAMMODE                     0x0
#endif


#define INVALID_PROGRAM_POSITION            0xFFFF
#define INVALID_LOGICAL_CHANNEL_NUMBER      0xFFFF
#define INVALID_LCN_MAX_NUMBER              0xF000
#define INVALID_SIMULCAST_LOGICAL_CHANNEL_NUMBER      0x7FF
#define INVALID_PHYSICAL_CHANNEL_NUMBER     0xFF
#define UNCONFIRMED_PHYSICAL_CHANNEL_NUMBER     0xFE
#define INVALID_VIRTUAL_CHANNEL_NUMBER      0xFF
#define INVALID_PSI_SI_VERSION              0xFF
#define INVALID_PID                         MSAPI_DMX_INVALID_PID
#define INVALID_SERVICE_ID                  0xFFFF
#define INVALID_TS_ID                       0xFFFF
#define INVALID_ON_ID                       0xFFFF
#define INVALID_NID                     0xFFFF
#define INVALID_SELECTED_AUDIOSTREAM        0x00
/*#if (ENABLE_CI_PLUS)
#define INVALID_IDINDEX                     0xFF
#else
#define INVALID_IDINDEX                     0x7F
#endif*/
#define INVALID_IDINDEX                     0xFFF  // 12bits
#define INVALID_RF_CHANNEL_NUMBER           0xFF  // 8bits

#define INVALID_NETWORKINDEX                0xFF//MAX_NETWOEK_NUMBER
#define INVALID_ALTERNATIVETIME             0
#define INVALID_PLPID                       0xFF

//--------------------------------------------------------------------
#define DEFAULT_REGION                      0


#if(ENABLE_CM_STORE_AUD_INFO_NEW_METHOD) // Only temp
    #define MAX_AUD_LANG_NUM                5

#elif( ENABLE_COUNTRY_SINGAPORE&&(ENABLE_S2==0) )
    #define MAX_AUD_LANG_NUM                32

//#elif (ENABLE_SBTVD_DTV_SYSTEM)
//    #define MAX_AUD_LANG_NUM                5//Brazil Prepare for 3 audio language: Eng Spa Por

#elif ENABLE_NZ_FREEVIEW
    #define MAX_AUD_LANG_NUM                16 //NZ default 16 //for SI04::SIT 21 test fail

#else
    #define MAX_AUD_LANG_NUM                8 //NZ default 16

#endif

#define MAX_AUD_ISOLANG_NUM                1 // 3
#define MAX_AUD_LANG_LENGTH                3
#define MAX_ISO639CODE_LENGTH              3
#define MAX_UNSUPPORTED_ISO639CODE_NUM     20
#define UNSUPPORT_ISO639CODE_BASE_INDEX    0xE0
//#define MAX_AUD_PER_PROGRAM                5
#define DEFAULT_AUD_LANG_NUM                 1

#if 0 //(ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
#define MAX_VC_PER_PHYSICAL                SI_MAX_VC_PER_PHYSICAL
#else
#define MAX_VC_PER_PHYSICAL                120//SI_MAX_VC_PER_PHYSICAL//67//62
#endif  //#if(ASTRA_HD_ENABLE)

//=================================================================

#if( ENABLE_DVB )

    #define MAX_NETWOEK_NUMBER                  20
    #define MAX_NETWORK_NAME                    25

//    #if( ENABLE_ISDBT && ENABLE_SBTVD_DTV_SYSTEM )// ISDBT
//        #define MAX_DTVPROGRAM              320//370//400
//        #define MAX_SERVICE_NAME           27//20+1+2//Brazil only need 20 chars+0xE Char+2 char for 10.1 channel

    //@@--Changed for Some long name Channel
    #if( ENABLE_DVBT && ENABLE_DVBC && DVB_T_C_DIFF_DB )
        #define MAX_DTVPROGRAM              600
        #define MAX_SERVICE_NAME            32
        #define MAX_DTVPROGRAM_DVBC         600 // MAX_DTV_C_PROGRAM
        //#define MAX_DTV_C_SERVICE_NAME      32

    #else // Default

        #if ENABLE_DVBT_1000_LCN  //20100707EL
            #define MAX_DTVPROGRAM              1000

        #elif ENABLE_NZ_FREEVIEW

            #define MAX_DTVPROGRAM              600//600 // Must be 600?

        #else

            #define MAX_DTVPROGRAM              280

        #endif // ENABLE_DVBT_1000_LCN


        #define MAX_SERVICE_NAME            32//48 //for HD Simulcast Logical Channel number

    #endif

    #ifndef MAX_DTVPROGRAM_DVBC
    #define MAX_DTVPROGRAM_DVBC     MAX_DTVPROGRAM
    #endif


#else // ENABLE_DVB else

    // This case is for only ATSC
    #define MAX_DTVPROGRAM              2
    #define MAX_SERVICE_NAME            4
    // Theoretically,  MAX_SERVICE_NAME is only used for DVBT/C, MAX_DTV_S2_SERVICE_NAME is used for DVBS.
    // But actually, DTV_CHANNEL_INFO is both used by DVBS & DVBT/C,
    // Due to BYTE bChannelName[MAX_SERVICE_NAME],
    // Temporarily, When DVBS in use, MAX_SERVICE_NAME must be same with MAX_DTV_S2_SERVICE_NAME.
    // If we have time, Need to refine code better.

    #define MAX_NETWOEK_NUMBER          2
    #define MAX_NETWORK_NAME            4

#endif// ENABLE_DVB




#if ENABLE_SAVE_MULTILINGUAL_SERVICE_NAME
#undef MAX_DTVPROGRAM
#define MAX_DTVPROGRAM              350//400
#undef MAX_SERVICE_NAME
#define MAX_SERVICE_NAME              32

#define MAX_MULTI_LINGUAL_SERVICE_NAME 1
#define INVALID_LANG_INDEX                       LANGUAGE_NONE
#endif



#define MAX_LCN_SERVICE_NAME_LENGTH (10+MAX_SERVICE_NAME) // 5 for LCN, 5 for dot, space, '\0', and buffer


/// Program data member
typedef BYTE    PROGRAMDATA_MEMBER;
//--------------------------------------------------
#define E_DATA_LCN                          0x01
#define E_DATA_PCN                          0x02
#define E_DATA_VERSION_PAT                  0x03
#define E_DATA_VERSION_PMT                  0x04
#define E_DATA_VERSION_NIT                  0x05
#define E_DATA_VERSION_SDT                  0x06
#define E_DATA_TS_ID                        0x07
#define E_DATA_ON_ID                        0x08
#define E_DATA_SERVICE_ID                   0x09
#define E_DATA_PCR_PID                      0x0A
#define E_DATA_VIDEO_PID                    0x0B
#define E_DATA_AUDIO_STREAM_INFO            0x0C
#define E_DATA_SERVICE_NAME                 0x0D
#define E_DATA_ORDER                        0x0E
#define E_DATA_MISC                         0x0F
#define E_DATA_SIMU_LCN                     0x10    //for HD Simulcast Logical Channel number
#define E_DATA_PMT_PID                      0x11
#define E_DATA_TTX_LIST                     0x12
#define E_DATA_ID_INDEX                     0x13
#define E_DATA_ID_TABLE                     0x14
#define E_DATA_NETWORK_ID                   0x15
#define E_DATA_CELL_ID                      0x16
#define E_DATA_PLP                          0x17
#define E_DATA_NETWORK_NAME                 0x18
#define E_DATA_NETWORK                      0x19
#define E_DATA_NETWORK_INDEX                0x20
#define E_DATA_FREQ                         0x21
#define E_DATA_SYMB_RATE                    0x22
#define E_DATA_QAM_MODE                     0x23
#define E_DATA_ORIGINAL_PCN                 0x24
#define E_DATA_ALTERNATIVE_TIME             0x25
#define E_DATA_TS_LCN                       0x26
#if ENABLE_SAVE_MULTILINGUAL_SERVICE_NAME
#define E_DATA_NAME_MULTILINGUAL_LANGUAGE   0x27
#define E_DATA_SERVICE_MULTILINGUAL_NAME    0x28
#endif
#define E_DATA_REPLACE_SERVICE              0x29

#if(MHEG5_SIINFO_ENABLE)
#define E_DATA_PROVIDER_NAME                0x30
#endif //#if(MHEG5_SIINFO_ENABLE)

//#define E_PRDATA_HPLP                       0x31

#if(ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
#define E_DATA_SGT_PID               0x32
#endif  //#if(ASTRA_HD_ENABLE)

#define E_DATA_ALL                          0xFF
//----------------------------------------------------

#if(ENABLE_DVB)

    #if DVB_T_C_DIFF_DB
      #if ENABLE_ZIGGO
        #define MAX_MUX_NUMBER_DVBC             120
      #else
        #define MAX_MUX_NUMBER_DVBC             40
      #endif
    #endif

    #if (ENABLE_CI_PLUS)
        #define MAX_MUX_NUMBER                  256
    #else
      #if ENABLE_T_C_CHANNEL_MIX
        #define MAX_MUX_NUMBER                  120
      #else
        #define MAX_MUX_NUMBER                  40
      #endif
    #endif

    #define MAX_MUX_NUMBER_NORMAL           50 // For DVBC APP

#else // ENABLE_DVB else

    #define MAX_MUX_NUMBER                  2

#endif // ENABLE_DVB

//----------------------------------------------------

#if ENABLE_DTV_STORE_TTX_PAGE_INFO//(ENABLE_TTX || BLOADER)
#define MAX_LISTPAGE                4
#define MAX_LISTPAGE_SIZE           ((MAX_LISTPAGE*10)/8)
#endif


#define NZ_MAX_LCN                              799

//-------------------------------------------------------------------------
#define FIRST_ORDER_OF_TV                       0
#define LAST_ORDER_OF_TV(eDbSel)                (msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDbSel) - 1 )//(MAX_DTVPROGRAM-1)
#define FIRST_ORDER_OF_RADIO(eDbSel)            (msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDbSel) - 1 )//(MAX_DTVPROGRAM-1)
#define LAST_ORDER_OF_RADIO                     0
#define FIRST_ORDER_OF_DATA(eDbSel)             (msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDbSel) - 1 )//(MAX_DTVPROGRAM-1)
#define LAST_ORDER_OF_DATA                      0
//-------------------------------------------------------------------------


#define INVALID_PRINDEX                         0x1FFF
#define INVALID_ORDER                           0x3FFF

#ifdef AUSTRALIA
#define DEFAULT_COUNTRY                         E_AUSTRALIA
#elif  ENABLE_SBTVD_DTV_SYSTEM
#define DEFAULT_COUNTRY                         E_BRAZIL
#elif (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP)
#define DEFAULT_COUNTRY                         E_CHINA
#elif ( ENABLE_DVB_TAIWAN_APP )
#define DEFAULT_COUNTRY                         E_TAIWAN
#else
#define DEFAULT_COUNTRY                         E_GERMANY //E_UK should set defualt country to Germany for CI+1.3
#endif

#define DEFAULT_PRINDEX                         INVALID_PRINDEX
#define DEFAULT_ORDER                           INVALID_ORDER

#define DEFAULT_LCN                             INVALID_LOGICAL_CHANNEL_NUMBER
#define DEFAULT_SIMU_LCN                        INVALID_SIMULCAST_LOGICAL_CHANNEL_NUMBER

#define DEFAULT_CELLID                          0x00
#define DEFAULT_PCN                             INVALID_PHYSICAL_CHANNEL_NUMBER
#define DEFAULT_VCN                             INVALID_VIRTUAL_CHANNEL_NUMBER

#define DEFAULT_VERSION                         INVALID_PSI_SI_VERSION
#define DEFAULT_VISIBLE_SERVICE_FLAG            0x01
#define DEFAULT_IS_SCRAMBLED                    0x00
#define DEFAULT_IS_STILL_PICTURE                0x00
#define DEFAULT_IS_SKIPPED                      0x00
#define DEFAULT_IS_LOCKED                       0x00
#define DEFAULT_IS_MOVED                        0x00
#define DEFAULT_IS_CABLE                        0x00
#define DEFAULT_IS_INVALID_CELL                 0x00
#define DEFAULT_IS_UNCONFIRMED_SERVICE          0x00
#define DEFAULT_IS_INVALID_SERVICE              0x00
#define DEFAULT_IS_DELETED                      0x00
#define DEFAULT_IS_REPLACE_DEL                    0x00
#define DEFAULT_IS_FAVORITE                     0x00
#define DEFAULT_IS_VIRTUAL_CHANNEL              0x00  //ENABLE_CI_PLUS_V1_4
#define DEFAULT_IS_OP_CHANNEL                   0x00  //ENABLE_CI_PLUS_V1_4
//#define DEFAULT_IS_MHEG_INCLUDED                0x00
#define DEFAULT_IS_REPLACE_SERVICE                0x00
#define DEFAULT_IS_SERVICE_ID_ONLY              0x01
#define DEFAULT_VIDEO_TYPE                      E_VIDEOTYPE_MPEG//0x00
#define DEFAULT_IS_DATA_SERVICE_AVAILABLE       0x00
#define DEFAULT_SIGNAL_STRENGTH                 0x0000
#define DEFAULT_LCN_VALID                       1
#define DEFAULT_SERVICE_TYPE                    E_SERVICETYPE_INVALID
#define DEFAULT_SERVICE_TYPE_PRIO               E_SERVICETYPE_PRIORITY_NONE
#define DEFAULT_SPECIAL_SERVICE                 0x00
#define DEFAULT_SELECTED_AUDIO_STREAM           0x00
#if(ASTRA_HD_ENABLE)
#define DEFAULT_IS_NEW_SERVICE                0x00
#endif
#define DEFAULT_TS_ID                           INVALID_TS_ID
#define DEFAULT_ON_ID                           INVALID_ON_ID
#define DEFAULT_SERVICE_ID                      INVALID_SERVICE_ID
#define DEFAULT_PMT_PID                         INVALID_PID
#define DEFAULT_PCR_PID                         INVALID_PID
#define DEFAULT_VIDEO_PID                       INVALID_PID
#define DEFAULT_SGT_PID                         0
//#define DEFAULT_AUDIO_PID                       INVALID_PID
//#define DEFAULT_AUDIO_STREAM_TYPE               E_AUDIOSTREAM_INVALID
//#define DEFAULT_AUDIO_LANGUAGE_CODE             0x00
#define DEFAULT_CURRENT_SERVICETYPE             E_SERVICETYPE_DTV

#define DEFAULT_CURRENT_ORDER_TV                FIRST_ORDER_OF_TV //0x0000
#define DEFAULT_CURRENT_ORDER_RADIO(eDbSel)     FIRST_ORDER_OF_RADIO(eDbSel)// (MAX_DTVPROGRAM-1)
#define DEFAULT_CURRENT_ORDER_DATA(eDbSel)      FIRST_ORDER_OF_DATA(eDbSel) // (MAX_DTVPROGRAM-1)

#define DEFAULT_LCN_ASSIGNMENT_TYPE             E_LCN_INVALID
// #define DEFAULT_PR_COUNTER_VALUE                0x0000
#define DEFAULT_NUMERIC_SELECTION_FLAG          0x01

#define ONID_NORWAY     0x2242
#if (ENABLE_CI_PLUS)
/// the op invalid cicam id
#define INVALID_CICAMID     0
/// max label char
#define MAX_CIPLUS_LABEL_CHAR   24
#endif



//move from $(ROOT)\chip\include\BaseType.h
typedef enum
{
    E_AUDIO_LANG_CODE_UNKNOWN              = 0x00,
    E_AUDIO_LANG_CODE_ENGLISH              = 0x01,
    E_AUDIO_LANG_CODE_FRENCH               = 0x02,
    E_AUDIO_LANG_CODE_GERMAN               = 0x03,
    E_AUDIO_LANG_CODE_SPANISH              = 0x04,
    E_AUDIO_LANG_CODE_ITALIAN              = 0x05,
    E_AUDIO_LANG_CODE_DUTCH                = 0x06,
    E_AUDIO_LANG_CODE_GREEK                = 0x07,
    E_AUDIO_LANG_CODE_PORTUGUESE           = 0x08,
    E_AUDIO_LANG_CODE_SEDISH               = 0x09,
    E_AUDIO_LANG_CODE_NORWEGIAN            = 0x0A,
    E_AUDIO_LANG_CODE_DANISH               = 0x0B,
    E_AUDIO_LANG_CODE_POLISH               = 0x0C,
    E_AUDIO_LANG_CODE_FINISH               = 0x0D,
    E_AUDIO_LANG_CODE_CZECH                = 0x0E,
    E_AUDIO_LANG_CODE_HUNGARIAN            = 0x0F,
    E_AUDIO_LANG_CODE_RUSSIAN              = 0x10,
    E_AUDIO_LANG_CODE_SLOVENIAN            = 0x11,
    E_AUDIO_LANG_CODE_ROMANIAN             = 0x12,
    E_AUDIO_LANG_CODE_SERBIAN              = 0x13,
    E_AUDIO_LANG_CODE_CROATIAN             = 0x14,
    E_AUDIO_LANG_CODE_BULGARIAN            = 0x15,
    E_AUDIO_LANG_CODE_WELSH                = 0x16,
    E_AUDIO_LANG_CODE_GALIC                = 0x17
} AUDIO_LANG_CODE;

#if (CM_MULTI_FAVORITE)
typedef enum
{
    E_FAVORITE_TYPE_1,
    E_FAVORITE_TYPE_2,
    E_FAVORITE_TYPE_3,
    E_FAVORITE_TYPE_4,
    E_FAVORITE_TYPE_ALL,
} E_FAVORITE_TYPE;
#endif

// Channel attribute member
typedef enum
{
    E_ATTRIBUTE_IS_SCRAMBLED,               ///< Attribute scrambled
    E_ATTRIBUTE_IS_STILL_PICTURE,           ///< Attribute still picture
    E_ATTRIBUTE_IS_VISIBLE,                 ///< Attribute visible

    E_ATTRIBUTE_IS_FAVORITE,                ///< Attribute favorite
#if (CM_MULTI_FAVORITE)
    E_ATTRIBUTE_IS_FAVORITE1,               ///< Attribute favorite 1
    E_ATTRIBUTE_IS_FAVORITE2,               ///< Attribute favorite 2
    E_ATTRIBUTE_IS_FAVORITE3,               ///< Attribute favorite 3
    E_ATTRIBUTE_IS_FAVORITE4,               ///< Attribute favorite 4
#endif

    E_ATTRIBUTE_IS_NUMERIC_SELECTION,       ///< Attribute numberic selection
    E_ATTRIBUTE_IS_SKIPPED,                 ///< Attribute skipped
    E_ATTRIBUTE_IS_LOCKED,                  ///< Attribute locked
//      E_ATTRIBUTE_IS_MHEG_INCLUDED,           ///< Attribute mheg included
    E_ATTRIBUTE_IS_REPLACE_SERVICE,           ///< Attribute replacement service
    E_ATTRIBUTE_IS_SERVICE_ID_ONLY,         ///< Attribute service ID only
    E_ATTRIBUTE_IS_DELETED,                 ///< Attribute deleted
    E_ATTRIBUTE_VIDEO_TYPE,              ///< Attribute HD Service
    E_ATTRIBUTE_IS_REPLACE_DEL,             ///< Attribute Replace Del
    E_ATTRIBUTE_IS_MOVED,                    ///< Attribute moved
#if ENABLE_T_C_CHANNEL_MIX
    E_ATTRIBUTE_IS_TERRESTRIAL,             ///< Attribute demod type
#endif
    E_ATTRIBUTE_IS_SPECIAL_CH,              ///< Attribute special service

    E_ATTRIBUTE_IS_UNCONFIRMED_SERVICE,
    E_ATTRIBUTE_IS_INVALID_SERVICE,
    E_ATTRIBUTE_IS_LCN_VALID,


#if(ASTRA_HD_ENABLE)
    E_ATTRIBUTE_IS_NEW_SERVICE,
#endif

    E_CH_ATTR_SERVICE_TYPE,
} E_MEMBER_CHANNEL_ATTRIBUTE;

/// PSI/SI Version member
typedef enum
{
    E_VERSION_PMT,                          ///< PMT
    E_VERSION_PAT,                          ///< PAT
    E_VERSION_NIT,                          ///< NIT
    E_VERSION_SDT                           ///< SDT
} E_MEMBER_PSI_SI_VERSION;


/// ISO 639 Language
typedef struct //__attribute__ ((__packed__))
{
    BYTE bISOLangIndex;                     ///< ISO Language index
    BYTE bISOLanguageInfo   : 2;            ///< 0x00: Stereo, 0x01: Mono right, 0x02: Mono left
    BYTE bAudType           : 3;            ///< 0x00: Undefined, 0x01: Clean effects, 0x02: Hearing impaired, 0x03: Visual impaired commentary, 0x04~0xFF: Reserved.
    BYTE bIsValid           : 1;            ///< Valid or not
    BYTE bBroadcastMixedAD  : 1;            ///< broadcast mixed AD
    BYTE bReserved          : 1;            ///< Reserved
} ATTR_PACK LANG_ISO639;


typedef enum{
    E_CM_PROFILE_NONE,

    E_CM_PROFILE_AAC_LEVEL1,
    E_CM_PROFILE_AAC_LEVEL2,
    E_CM_PROFILE_AAC_LEVEL4,
    E_CM_PROFILE_AAC_LEVEL5,
    E_CM_PROFILE_HE_AAC_LEVEL2,
    E_CM_PROFILE_HE_AAC_LEVEL3,
    E_CM_PROFILE_HE_AAC_LEVEL4,
    E_CM_PROFILE_HE_AAC_LEVEL5,

} E_CM_PROFILE_AND_LEVEL;


/// Audio information
typedef struct _AUD_INFO//__attribute__ ((__packed__))
{
    LANG_ISO639 aISOLangInfo[MAX_AUD_ISOLANG_NUM];   ///< ISO Language Info

    SI_AUDIOSTREAM_TYPE eSIAudType : 3;  // <  0x01: MPEG, 0x02: AC-3, 0x03: MPEG4_AUD, ...
    WORD wAudPID                   :13;  // < Audio PID

    //U8 u8ProfileAndLevel;
    E_CM_PROFILE_AND_LEVEL eProfileAndLevel : 4;

    //U8 u8Component_AAC_Type;
} ATTR_PACK AUD_INFO;


typedef struct
{
    BYTE bPATVer;
    BYTE bPMTVer;
    BYTE bNITVer;
    BYTE bSDTVer;
} DVB_TABLE_VERSION;

typedef enum
{
    E_SERRUNSTA_UNDEFINED                  = 0x00,
    E_SERRUNSTA_NOT_RUNNING                = 0x01,
    E_SERRUNSTA_START_IN_A_FEW_SECOND     = 0x02,
    E_SERRUNSTA_PAUSING                     = 0x03,
    E_SERRUNSTA_RUNNING                     = 0x04
} E_MEMBER_SERVICE_RUNNING_STATUS;

typedef enum
{
    E_SERVICETYPE_PRIORITY_HIGH    = 0x00,
    E_SERVICETYPE_PRIORITY_MIDDLE  = 0x01,
    E_SERVICETYPE_PRIORITY_LOW     = 0x02,
    E_SERVICETYPE_PRIORITY_NONE    = 0x03
} SERVICETYPE_PRIORITY;


typedef enum
{
    E_VIDEOTYPE_MPEG  = 0x00,
    E_VIDEOTYPE_H264  = 0x01,
    E_VIDEOTYPE_AVS   = 0x02,
    E_VIDEOTYPE_VC1   = 0x03,
    E_VIDEOTYPE_H265  = 0x04//IMPLEMENT_DTV_H265
} VIDEO_TYPE;

typedef struct _CHANNEL_ATTRIBUTE //__attribute__ ((__packed__))
{
    WORD bValidLCN              : 1;
    WORD wSignalStrength        : 15;
//--------------------------------------------
    BYTE bVisibleServiceFlag    : 1;
    BYTE bNumericSelectionFlag  : 1;    // Hidden but selectable through direct numeric entry
    BYTE bIsDelete              : 1;
    BYTE bIsMove                : 1;
    BYTE bIsScramble            : 1;    // 0=FTA, 1=Scramble
    BYTE bIsSkipped             : 1;    // for Channel Edit skip function.
    BYTE bIsLock                : 1;
    BYTE bIsStillPicture        : 1;    // for information from Video_stream_descriptor(0x02)
//--------------------------------------------
    WORD bServiceType           : 4;   //add service type 2 bit to 4 bit // for information from PMT for empty Video_PID
//      WORD bIsMHEGIncluded          : 1;
    WORD bReplaceService        : 1;
    WORD eVideoType             : 3;
//--------------------------------------------

#if ENABLE_TARGET_REGION
    WORD cRegion     : 4;
#else
    //WORD reserved2     : 4;
#endif

#if (CM_MULTI_FAVORITE)
    U8 bIsFavorite            : 4;
#endif

    U8 bServiceTypePrio       : 2;

#if( !CM_MULTI_FAVORITE )
    U8 bIsFavorite            : 1;
#endif

    WORD bIsServiceIdOnly       : 1;    // If the program is not shown in PAT, set to TRUE
    //WORD bIsDataServiceAvailable: 1;  //useless data, remove  // If ttx or subtitle is available, the flag set to TRUE
    WORD bIsReplaceDel          : 1;
    WORD bIsSpecialService      : 1;

    U8 bInvalidService        : 1;
    U8 bInvalidCell           : 1;
    U8 bUnconfirmedService    : 1;

#if(ENABLE_S2_FAST_SCAN)
    BYTE bIsFastScan            : 1;
#endif

#ifdef HSS_TWO_DEMOD
    U8 bIsMultiCarrier        : 1;    // Use for distinguish the demod type.
#elif ENABLE_T_C_CHANNEL_MIX
    U8 bIsTerrestrial         : 1;    // Use for distinguish the demod type.
#else
    //U8 reserved1              : 1;
#endif

#if(ASTRA_HD_ENABLE)
    U8 bIsNewService          : 1;
#endif

#if(ENABLE_CI_PLUS_V1_4)
    U8 bIsVirtualSevice       : 1;   // ENABLE_CI_PLUS_V1_4
    U8 bIsOpService           : 1;
#endif
    //  BYTE reserved3              : 3;

}ATTR_PACK CHANNEL_ATTRIBUTE;

typedef struct
{
    BYTE bVirtualChannel;
    BYTE bPhysicalChannel;
} ST_LCN;

typedef union
{
    ST_LCN stLCN;
    WORD wLCN;
} LOGICAL_CHANNEL_NUMBER;


/// DTV Channel info
typedef struct _DTV_CHANNEL_INFO
{
    WORD bIDIdex;
    WORD wPCR_PID;                          ///< PCR PID
    WORD wVideo_PID;                        ///< Video PID
    WORD wOrder;                            ///< Order

    union
    {
        #if ENABLE_SBTVD_DTV_SYSTEM
        ST_LCN stLCN;
        #endif
        WORD wLCN;
    };

    WORD wPmt_PID;                          ///< PMT PID
    DVB_TABLE_VERSION stPSI_SI_Version;     ///< PSI/SI Version
    CHANNEL_ATTRIBUTE stCHAttribute;        ///< Channel attribute
    WORD wService_ID;                       ///< Service ID

#if 1//NTV_FUNCTION_ENABLE
    WORD wTS_LCN;
#endif
    WORD wSimu_LCN;  //  for HD Simulcast Logical Channel number

#if ENABLE_S2
    WORD wSgt_PID;
#endif

#if(ENABLE_CM_STORE_AUD_INFO_NEW_METHOD)
    U16 u16AudInfoTabIndex;
    U8 u8AudInfoNum;
#endif

    AUD_INFO stAudInfo[MAX_AUD_LANG_NUM];   ///< Audio info

#if ENABLE_SAVE_MULTILINGUAL_SERVICE_NAME
    BYTE bMultiLanguage[MAX_MULTI_LINGUAL_SERVICE_NAME];
    BYTE bMultiChannelName[MAX_MULTI_LINGUAL_SERVICE_NAME][MAX_SERVICE_NAME];    ///< Channel name
#endif
    BYTE bChannelName[MAX_SERVICE_NAME];    ///< Channel name

#if(MHEG5_SIINFO_ENABLE)
    BYTE bProviderName[SI_MAX_SERVICE_NAME];    ///< Provider name
#endif //#if(MHEG5_SIINFO_ENABLE)

#if ENABLE_S2
    //BYTE SatId; // ID Table have it
#endif

  #if ENABLE_DTV_STORE_TTX_PAGE_INFO//(ENABLE_TTX || BLOADER)
    BYTE u8ListPage[MAX_LISTPAGE_SIZE];
  #endif

#if 0//ENABLE_S2_CHANNEL_FAV_NEWSTYLE
    BYTE stChIsFav;
#endif

} ATTR_PACK  DTV_CHANNEL_INFO;

typedef struct _DTV_SIMPLE_SERVICE_INFO
{
    BYTE bChannelName[MAX_SERVICE_NAME];
    WORD wNumber;
    DWORD dwPosition;
    BOOLEAN bServiceToSelect;
    BOOLEAN bVisible;
    BOOLEAN bCountryService;
    struct _DTV_SIMPLE_SERVICE_INFO* next;
} DTV_SIMPLE_SERVICE_INFO;

#if(ENABLE_LCN_CONFLICT)
typedef struct _DTV_LCN_CONFLICT_INFO
{
    BYTE bLcnConflictChannelName[MAX_SERVICE_NAME];
    DWORD dwLcnConflictPosition;
}DTV_LCN_CONFLICT_INFO;
#endif


#if DVB_T_C_DIFF_DB
#define MAX_DTVCHANNELTABLE_MAP_DVBC    ((MAX_DTVPROGRAM_DVBC+7)/8)
#define DTVDATA_ID_DVBC                 0xA55B
#define MAX_DTV_C_IDTABLE_MAP           ((MAX_MUX_NUMBER_DVBC+7)/8)
#endif

#define MAX_DTVCHANNELTABLE_MAP     ((MAX_DTVPROGRAM+7)/8)
#define DTVDATA_ID                  0xA55B
#define MAX_DTVIDTABLE_MAP          ((MAX_MUX_NUMBER+7)/8)


typedef struct
{
#if 1//ENABLE_DVBC
    U32  u32Frequency;
#endif
#if ENABLE_S2
    U32 u32S2Frequency;
#endif
#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
    DWORD dwAlternativeTime;
#endif

    WORD wTransportStream_ID;           // Transportstream ID
    WORD wOriginalNetwork_ID;           // Original Network ID
    WORD wNetwork_ID;           // Network ID
    WORD wCellID;                   //Cell ID

#if 1//ENABLE_S2 || ENABLE_DVBC
    U16 u16SymbolRate;
#endif

#if (ENABLE_SAVE_SQI)
    WORD wStrengthQuality;
#endif

    BYTE cRFChannelNumber;              // RF Channel Number
    BYTE cPLPID;

#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
    BYTE cOriginal_RF;
#endif

  #if 1//ENABLE_DVBC
    //U32  _u32SymbRate; // Merge to u16SymbolRate
    BYTE QamMode;
  #endif

#if ENABLE_S2
    BYTE SatelliteId;
    //U32 u32S2Frequency;
    //U16 u16SymbolRate;
    //BYTE u8Polarity;
#endif

    RF_CHANNEL_BANDWIDTH enBandWidth : 3;

    BYTE cHpLp : 1;//0=>HP, 1=>LP

#if ENABLE_S2
    BYTE u8Polarity : 1;
#endif

} DTVPROGRAMID; // For SI add channel

typedef struct _DTVPROGRAMID_M
{
    union ATTR_PACK
    {
        U32 u32Frequency; // DVBC only?
    #if ENABLE_S2
        U32 u32S2Frequency; // DVBS
    #endif
    } ;

#if 1//(ENABLE_DVBC) // todo
    //U32 _u32SymbRate; // Merge to u16SymbolRate
#endif

#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
    DWORD dwAlternativeTime;
#endif

    WORD wTransportStream_ID;           // Transportstream ID
    WORD wOriginalNetwork_ID;           // Original Network ID
    WORD wCellID;                       // Cell ID

#if (ENABLE_SAVE_SQI)
    WORD wStrengthQuality;
#endif

#if 1//ENABLE_S2 || ENABLE_DVBC
    U16 u16SymbolRate;
#endif

    BYTE cRFChannelNumber;              // RF Channel Number
    BYTE cPLPID;

#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
    BYTE cOriginal_RF;
#endif

#if 1//(ENABLE_DVBC) // todo
    BYTE QamMode;
#endif

#if ENABLE_S2
    BYTE SatelliteId;
#endif

    BYTE cNetWorkIndex;

#if PATCH_FOR_HW_LIMIT_EXT_SYNC //[step 0/4]
    BYTE Ext_Sync;
#endif

    RF_CHANNEL_BANDWIDTH enBandWidth : 3;

    BYTE cHpLp : 1; //0=>HP, 1=>LP

#if ENABLE_S2
    BYTE u8Polarity : 1;
#endif

}ATTR_PACK DTVPROGRAMID_M; // For channel manager&DB

typedef struct
{
    WORD wNetwork_ID;                       // Network ID
    BYTE bNetworkName[MAX_NETWORK_NAME];    // Network name
} DTVNETWORK;

#if(ENABLE_CM_STORE_AUD_INFO_NEW_METHOD)
    #define CM_AUDINFO_MAX_NUM_DVB  (MAX_DTVPROGRAM*5)

  #if( ENABLE_DVBC&&DVB_T_C_DIFF_DB )
    #define CM_AUDINFO_MAX_NUM_DVBC (MAX_DTVPROGRAM_DVBC*5)
  #endif

#endif


typedef struct
{
    WORD                wID;
    BYTE                bSerialNum;
    //MEMBER_COUNTRY      eCountry;
    BOOLEAN             bIsLogicalChannelNumberArranged;
#if NTV_FUNCTION_ENABLE
    BYTE                bFavorite_Region;
#endif
#if 0//(EEPROM_DB_STORAGE == EEPROM_SAVE_NONE)
    WORD                wCurOrderOfTV;
    WORD                wCurOrderOfRadio;
    WORD                wCurOrderOfData;
    MEMBER_SERVICETYPE  eDTVCurrentServiceType;
#endif

    // Program Table Map
    BYTE                bDTVChannelTableMap[MAX_DTVCHANNELTABLE_MAP];
    // Program Table
    DTV_CHANNEL_INFO    astDTVChannelTable[MAX_DTVPROGRAM];
    // ID Table Map
    BYTE                bDTVIDtableMap[MAX_DTVIDTABLE_MAP];
    // ID Table
    DTVPROGRAMID_M      astDtvIDTable[MAX_MUX_NUMBER];
    // NetWork
    DTVNETWORK          astDtvNetwork[MAX_NETWOEK_NUMBER];

#if(ENABLE_CM_STORE_AUD_INFO_NEW_METHOD)
    AUD_INFO            astAudInfoTab[CM_AUDINFO_MAX_NUM_DVB];
#endif

} DTV_CHANNEL_DATA_STRUCTURE;

#if( ENABLE_DVBC&&DVB_T_C_DIFF_DB )
typedef struct
{
    WORD                wID;
    BYTE                bSerialNum;
    MEMBER_COUNTRY      eCountry;
    BOOLEAN             bIsLogicalChannelNumberArranged;
#if NTV_FUNCTION_ENABLE
    BYTE                bFavorite_Region;
#endif
#if 0//(EEPROM_DB_STORAGE == EEPROM_SAVE_NONE)
    WORD                wCurOrderOfTV;
    WORD                wCurOrderOfRadio;
    WORD                wCurOrderOfData;
    MEMBER_SERVICETYPE  eDTVCurrentServiceType;
#endif

    // Program Table Map
    BYTE                bDTV_C_ChannelTableMap[MAX_DTVCHANNELTABLE_MAP_DVBC];
    // Program Table
    DTV_CHANNEL_INFO    astDTV_C_ChannelTable[MAX_DTVPROGRAM_DVBC];
    // ID Table Map
    BYTE                bDTV_C_IDtableMap[MAX_DTV_C_IDTABLE_MAP];
    // ID Table
    DTVPROGRAMID_M      astDtv_C_IDTable[MAX_MUX_NUMBER_DVBC];
    // NetWork
    DTVNETWORK          astDtv_C_Network[MAX_NETWOEK_NUMBER];

#if(ENABLE_CM_STORE_AUD_INFO_NEW_METHOD)
    AUD_INFO            astAudInfoTab[CM_AUDINFO_MAX_NUM_DVBC];
#endif

} DTV_C_CHANNEL_DATA_STRUCTURE;
#endif


#if (ENABLE_DTV_EPG)
typedef struct
{
    void (*pfNotify_CM_SwapProgram)(WORD wFromOrder, WORD wToOrder);
    void (*pfNotify_CM_MoveProgram)(U16 u16FromIndex, U16 u16ToIndex);
    void (*pfNotify_SrvPriorityHandler) (U16 u16MainlistIdx);
    void (*pfNotify_CM_RemoveProgram) (WORD wSrvOrder);
} DTV_CM_INIT_PARAMETER;
#endif

#if(ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)

#define MAX_SERVICE_LIST_NAME  31


typedef struct
{
     /// country code
     EN_SI_COUNTRY_SETTING enSICountry;
     /// is country available
     BOOLEAN    bIsCountryAvailability;

}DTV_COUNTRY_AVAILABILITY_INFO;

 /// servicelist id ;servicelsit name only;
 typedef struct
 {
     /// service list name
     U8  au8ServiceListName[MAX_SERVICE_LIST_NAME ];
     DTV_COUNTRY_AVAILABILITY_INFO stCountryInfo;
     /// service list id
     U16 u16ServiceListID;
     BOOLEAN iSUsed;

 }DVBS_SI_SGT_BASIC_SERVICE_LIST_INFO;

typedef struct
{
    U16 u16ServiceListID;
    //U16 u16ServiceID;
    //U16 u16ServiceLCN;
    MS_SI_SGT_SERVICE_INFO stServiceInfo;
}DVBS_SI_SGT_SERVICE_INFO;

#endif  //#if(ASTRA_HD_ENABLE)

#if(MHEG5_SIINFO_ENABLE)
typedef struct
{
     U8     u8ServiceType;      //service_type
     BYTE bServiceName[SI_MAX_SERVICE_NAME];    ///service name//< Channel name
     BYTE bProviderName[SI_MAX_SERVICE_NAME];   //service_provider_name
}DTV_CM_SI_SERVICEINFO;
#endif //#if(MHEG5_SIINFO_ENABLE)

typedef enum // channel list type
{
    E_ATV_TYPE = E_SERVICETYPE_ATV,
    E_ALL_LIST = E_SERVICETYPE_UNITED_TV,
    E_DTV_LIST = E_SERVICETYPE_DTV,
    E_RADIO_LIST = E_SERVICETYPE_RADIO,
    E_DATA_LIST = E_SERVICETYPE_DATA
} CHANNEL_LIST_TYPE;

typedef enum
{
    E_LCN_TYPE_AUTO        = 0x00,
    E_LCN_TYPE_MANUAL    = 0x01,
    E_LCN_TYPE_MOVE        = 0x02,
    E_LCN_TYPE_DELETE    = 0x03
} E_MEMBER_LCN_TYPE;

typedef enum
{
    E_CM_SERVICE_POS_DTV = 0x00,
    E_CM_SERVICE_POS_RADIO = 0x01,
    E_CM_SERVICE_POS_DATA = 0x02,
    E_CM_SERVICE_POS_NUMS = 3,
}E_CM_SERVICE_POS;
/*
typedef enum
{
    EXCLUDE_NOT_VISIBLE_AND_DELETED,
    INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED,
    INCLUDE_ALL,
    MAX_COUNT_PROGRAM_OPTION
} COUNT_PROGRAM_OPTION;
*/
typedef struct
{
    U16 wService_ID;
    //-------------------------------------------------
    union
    {
    #if ENABLE_SBTVD_DTV_SYSTEM
        ST_LCN stLCN;
    #endif
        U16 wLCN;
    };
    //-------------------------------------------------
    U16 wSimu_LCN                     : 11;
    U16 bInvalidService                : 1;
    U16 bIsSpecialService              : 1;
    //WORD bIsMHEGIncluded                  : 1;
    U16 bReplaceService                : 1;
    U16 bVisibleServiceFlag            : 1;
    U16 bIsSkipped                     : 1;
    //-------------------------------------------------
#if 1//ENABLE_S2_WORD
    U16 cIDIndex                      : 12; // Max=4096
#else
    BYTE cIDIndex                      : 7;
#endif
    U16 eVideoType                     : 3;
    U16 bIsServiceIdOnly               : 1;
    //-------------------------------------------------
    U16 wPRIndex                      : 13;
    U16 bIsLock                        : 1;
    U16 bIsMove                        : 1;
    U16 bIsScramble                    : 1;
    //-------------------------------------------------
    U8 eLCNAssignmentType             : 6;
    U8 bNumericSelectionFlag          : 1;
    U8 bIsDelete                      : 1;
    //-------------------------------------------------
    U8 bServiceType                   : 3;
    U8 bServiceTypePrio               : 2;
    U8 bIsReplaceDel                  : 1;
    U8 bInvalidCell                   : 1;
    U8 bUnconfirmedService            : 1;
    //-------------------------------------------------
#if (CM_MULTI_FAVORITE)
    U8 bIsFavorite                    : 4;
#else
    U8 bIsFavorite                    : 1;
#endif

    U8 bIsStillPicture               : 1;
#if ENABLE_T_C_CHANNEL_MIX
    U8 bIsTerrestrial                 : 1;
#endif

#if(ASTRA_HD_ENABLE)
    U8 bIsNewService                  : 1;
#endif

#if(ENABLE_S2_FAST_SCAN)
    BYTE bIsFastScan                : 1;
#endif
} DTVPROGRAMINDEX;


#define DTVPROGRAMINDEX_LEN     sizeof(DTVPROGRAMINDEX)


//--------------------------------------------------------------------------------------

#define IS_COUNTRY_SUPPORT_LCN(c)       ((c==E_DENMARK)     ||  \
                                        (c==E_FRANCE)       ||  \
                                        (c==E_FINLAND)      ||  \
                                        (c==E_ITALY)        ||  \
                                        (c==E_NETHERLANDS)  ||  \
                                        (c==E_SWEDEN)       ||  \
                                        (c==E_UK)           ||  \
                                        (c==E_AUSTRALIA)    ||  \
                                        (c==E_IRELAND)      ||  \
                                        (c==E_THAILAND)     ||  \
                                        (c==E_VIETNAM)      ||  \
                                        (c==E_IRAN)         ||  \
                                        (c==E_MOROCCO)      ||  \
                                        (c==E_MALAYSIA)     ||  \
                                        (c==E_INDONESIA)    ||  \
                                        (c==E_SINGAPORE))

#define IS_NORDIC_COUNTRY(c)            ( (c==E_FINLAND)       ||  \
                                          (c==E_SWEDEN)        ||  \
                                          (c==E_DENMARK)       ||  \
                                          (c==E_NORWAY)        ||  \
                                          (c==E_IRELAND))

#define IS_BESTMUX_COUNTRY(c)            ( (c==E_FINLAND)      ||  \
                                          (c==E_SWEDEN)        ||  \
                                          (c==E_DENMARK)       ||  \
                                          (c==E_NORWAY)        ||  \
                                          (c==E_UK)            ||  \
                                          (c==E_NEWZEALAND)       ||  \
                                          (c==E_IRELAND))


#define IS_SID_UNIQUE_COUNTRY(c)            ( (c==E_NORWAY)      ||  \
                                          (c==E_UK)   || \
                                          (c==E_NEWZEALAND))

#define IS_LCN_RANK_COUNTRY(c)            msAPI_DtvSys_Is_LCN_RANK_COUNTRY( (c) )


#define IS_MIDDLEEAST_COUNTRY(c)       ( (c==OSD_COUNTRY_UNITED_ARAB_EMIRATES)     ||  \
                                         (c==OSD_COUNTRY_KUWAIT)     ||  \
                                         (c==OSD_COUNTRY_OMAN)   ||  \
                                         (c==OSD_COUNTRY_QATAR)   ||  \
                                         (c==OSD_COUNTRY_SAUDI_ARABIA)  ||  \
                                         (c==OSD_COUNTRY_BAHRAIN))

#define IS_SBTVD_APP_COUNRTY(x)    (x == E_BRAZIL)

#ifdef API_DTVSYSTEM_C
#define INTERFACE
#else
#define INTERFACE extern
#endif
/******************************************************************************/
/*                       Global Variable Declarations                         */
/******************************************************************************/
#if(ENABLE_LCN_CONFLICT)
#define   MAX_SUPPORT_LCN_CONFLICT_NUM    5
INTERFACE DTV_LCN_CONFLICT_INFO g_ucLcnConflict[MAX_SUPPORT_LCN_CONFLICT_NUM];
#endif
//------------------------------------------------------------------------------
// Public functions.
//------------------------------------------------------------------------------


void msAPI_CM_Init(void);

#if (ENABLE_DTV_EPG)
INTERFACE void msAPI_CM_Init_EPG(DTV_CM_INIT_PARAMETER* psNotify);
#endif

INTERFACE BOOLEAN msAPI_CM_GetServiceTypeAndPositionWithPCN(WORD cPCN, WORD wService_ID, MEMBER_SERVICETYPE *peServiceType, WORD * pwPosition);
//INTERFACE BOOLEAN msAPI_CM_GetServiceTypeAndPositionWithPCN(BYTE cPCN, WORD wService_ID, MEMBER_SERVICETYPE *peServiceType, WORD * pwPosition);

INTERFACE BYTE msAPI_CM_GetCountOfSameServiceWithIDs(WORD wTransportStream_ID, WORD wOriginalNetwork_ID, WORD wService_ID);
INTERFACE BOOLEAN msAPI_CM_GetServiceTypeAndPositionWithIDsandServiceType(WORD wTransportStream_ID, WORD wOriginalNetwork_ID, WORD wService_ID, MEMBER_SI_SERVICETYPE wService_Type, BYTE cOrdinal, MEMBER_SERVICETYPE * peServiceType, WORD * pwPosition, BOOLEAN bCheckTsID);
INTERFACE BOOLEAN msAPI_CM_GetServiceTypeAndPositionWithIDs(WORD wTransportStream_ID, WORD wOriginalNetwork_ID, WORD wService_ID, BYTE cOrdinal, MEMBER_SERVICETYPE * peServiceType, WORD * pwPosition, BOOLEAN bCheckTsID);
INTERFACE BOOLEAN msAPI_CM_GetServiceTypeAndPositionWithIDsAndRFCH(WORD wTransportStream_ID, WORD wOriginalNetwork_ID, WORD wService_ID, BYTE cOrdinal, MEMBER_SERVICETYPE * peServiceType, WORD * pwPosition, BOOLEAN bCheckTsID, U8 u8RFChannelNumber);
INTERFACE BOOLEAN msAPI_CM_GetServiceTypeAndPositionWithIDsAndPmtPid(WORD wTransportStream_ID, WORD wOriginalNetwork_ID, WORD wService_ID, WORD wPmt_Pid, BYTE cOrdinal, MEMBER_SERVICETYPE * peServiceType, WORD * pwPosition, BOOLEAN bCheckTsID);
INTERFACE BOOLEAN msAPI_CM_MoveProgram(MEMBER_SERVICETYPE bServiceType, WORD wFromPosition, WORD wToPosition, MEMBER_SERVICETYPE btoServiceType);

#if(MHEG5_SIINFO_ENABLE)
INTERFACE BOOLEAN msAPI_CM_GetProviderName(MEMBER_SERVICETYPE bServiceType, WORD wPosition, BYTE *bProvidername);
INTERFACE BOOLEAN msAPI_CM_GetServiceInfo(WORD wTransportStream_ID, WORD wOriginalNetwork_ID, WORD wService_ID, DTV_CM_SI_SERVICEINFO *pstServiceInfo);
#endif //#if(MHEG5_SIINFO_ENABLE)

#if 1//(ENABLE_S2_FAST_SCAN)
INTERFACE U16 msAPI_CM_RemoveMismatchedProgram(WORD cRFChannelNumber,WORD wTSID, BYTE cPLP_ID,BYTE cHpLp, WORD *pwService_ID, MEMBER_SERVICETYPE *peService_Type, U16 u16CountOfServiceID,BYTE sat,WORD freq);
#else
INTERFACE BYTE msAPI_CM_RemoveMismatchedProgram(WORD cRFChannelNumber,WORD wTSID, BYTE cPLP_ID,BYTE cHpLp, WORD *pwService_ID, MEMBER_SERVICETYPE *peService_Type, BYTE cCountOfServiceID,BYTE sat,WORD freq);
#endif //#if(ENABLE_S2_FAST_SCAN)

INTERFACE U16 msAPI_CM_RemoveMismatchedProgram_ALLPCN(MS_SI_SHORT_SERVICEINFO *pwService_Info, MEMBER_SERVICETYPE *peService_Type, U16 cCountOfServiceID);

INTERFACE BOOLEAN msAPI_CM_FillProgramDataWithDefault(DTV_CHANNEL_INFO *pDTVProgramData);

INTERFACE WORD msAPI_CM_GetPositionbyListPosition(WORD wListPoistion, MEMBER_SERVICETYPE *eServiceType);
INTERFACE WORD msAPI_CM_GetListPositionbyPosition(WORD wPosition, MEMBER_SERVICETYPE eServiceType);
INTERFACE MEMBER_SERVICETYPE msAPI_CM_GetCurrentServiceType(void);
INTERFACE BOOLEAN msAPI_CM_SetCurrentServiceType(MEMBER_SERVICETYPE bServiceType);
INTERFACE WORD msAPI_CM_GetCurrentPosition(MEMBER_SERVICETYPE bServiceType);
INTERFACE BOOLEAN msAPI_CM_SetCurrentPosition(MEMBER_SERVICETYPE bServiceType, WORD wPosition);
INTERFACE WORD msAPI_CM_CountProgram(MEMBER_SERVICETYPE bServiceType, E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary);
INTERFACE WORD msAPI_CM_GetFirstProgramPosition(MEMBER_SERVICETYPE bServiceType, BOOLEAN bIncludeSkipped);
INTERFACE WORD msAPI_CM_GetLastProgramPosition(MEMBER_SERVICETYPE bServiceType, BOOLEAN bIncludeSkipped);
INTERFACE WORD msAPI_CM_GetNextProgramPosition(MEMBER_SERVICETYPE bServiceType, WORD wBasePosition, BOOLEAN bIncludeSkipped, CHANNEL_LIST_TYPE bList_type, MEMBER_SERVICETYPE *bNewServiceType);
INTERFACE BOOLEAN msAPI_CM_ResetAllProgram(void);

INTERFACE WORD msAPI_CM_GetLogicalChannelNumberbyListPosition(WORD wPosition);
INTERFACE WORD msAPI_CM_GetLogicalChannelNumber(MEMBER_SERVICETYPE bServiceType, WORD wPosition);
INTERFACE WORD msAPI_CM_GetOriginalLogicalChannelNumber(MEMBER_SERVICETYPE bServiceType, WORD wPosition);
INTERFACE WORD msAPI_CM_GetSimuLogicalChannelNumber(MEMBER_SERVICETYPE bServiceType, WORD wPosition);
INTERFACE U16 msAPI_CM_GetPhysicalChannelNumber(MEMBER_SERVICETYPE bServiceType, WORD wPosition);
INTERFACE BYTE msAPI_CM_GetPSISIVersion(MEMBER_SERVICETYPE bServiceType, WORD wPosition, E_MEMBER_PSI_SI_VERSION eVersionMember);

INTERFACE U16 msAPI_CM_GetProgramAttribute(MEMBER_SERVICETYPE bServiceType, WORD wPosition, E_MEMBER_CHANNEL_ATTRIBUTE eAttributeMember);
INTERFACE VIDEO_TYPE msAPI_CM_GetProgramVideoType(MEMBER_SERVICETYPE bServiceType, WORD wPosition);

INTERFACE WORD msAPI_CM_GetPmtPID(MEMBER_SERVICETYPE bServiceType, WORD wPosition);
INTERFACE WORD msAPI_CM_GetPCR_PID(MEMBER_SERVICETYPE bServiceType, WORD wPosition);
INTERFACE WORD msAPI_CM_GetVideoPID(MEMBER_SERVICETYPE bServiceType, WORD wPosition);
INTERFACE BYTE msAPI_CM_GetAudioStreamCount(MEMBER_SERVICETYPE bServiceType, WORD wPosition);
INTERFACE BYTE msAPI_CM_GetSelectedAudioStream(MEMBER_SERVICETYPE bServiceType, WORD wPosition);
INTERFACE BOOLEAN msAPI_CM_GetAudioStreamInfo(MEMBER_SERVICETYPE bServiceType, WORD wPosition, AUD_INFO * pstAudioStreamInfo, BYTE cOrdinal);
INTERFACE BOOLEAN msAPI_CM_GetProgramInfo(MEMBER_SERVICETYPE bServiceType, WORD wPosition,DTV_CHANNEL_INFO *pChannelInfo);
INTERFACE BYTE msAPI_CM_GetNextAudioStreamOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wPosition, BYTE cBaseOrdinal);
INTERFACE BYTE msAPI_CM_GetPrevAudioStreamOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wPosition, BYTE cBaseOrdinal);
INTERFACE BOOLEAN msAPI_CM_GetServiceName(MEMBER_SERVICETYPE bServiceType, WORD wPosition, BYTE * bChannelName);
INTERFACE WORD msAPI_CM_GetService_ID(MEMBER_SERVICETYPE bServiceType, WORD wPosition);
INTERFACE WORD msAPI_CM_GetTS_ID(MEMBER_SERVICETYPE bServiceType, WORD wPosition);
INTERFACE WORD msAPI_CM_GetON_ID(MEMBER_SERVICETYPE bServiceType, WORD wPosition);
INTERFACE WORD msAPI_CM_GetNetwork_ID(MEMBER_SERVICETYPE bServiceType, WORD wPosition);
INTERFACE BOOLEAN msAPI_CM_GetCellIDByPosition(MEMBER_SERVICETYPE bServiceType, WORD wPosition, WORD *pwCellID);
INTERFACE BOOLEAN msAPI_CM_ServiceIDOnlyProgram(MEMBER_SERVICETYPE bServiceType, WORD wPosition,MS_U8 IsServiceIdOnly);
INTERFACE BOOLEAN msAPI_CM_ScrambleProgram(MEMBER_SERVICETYPE bServiceType, WORD wPosition,MS_U8 IsScramble);
INTERFACE BOOLEAN msAPI_CM_SetProgramVideoType(MEMBER_SERVICETYPE bServiceType, WORD wPosition,U8 u8VideoType);
INTERFACE BOOLEAN msAPI_CM_DeleteProgram(MEMBER_SERVICETYPE bServiceType, WORD wPosition,MS_U8 fIsDelete);
INTERFACE BOOLEAN msAPI_CM_ReplaceDelProgram(MEMBER_SERVICETYPE bServiceType, WORD wPosition,BOOLEAN bDel);
INTERFACE BOOLEAN msAPI_CM_RecoveryDelProgram(MEMBER_SERVICETYPE bServiceType, WORD wPosition);

INTERFACE BOOLEAN msAPI_CM_FavorProgram(MEMBER_SERVICETYPE bServiceType, WORD wPosition, BOOLEAN bFavorite);
#if ENABLE_S2_CHANNEL_FAV_NEWSTYLE
INTERFACE BOOLEAN msAPI_CM_GetFavChannelInfo(MEMBER_SERVICETYPE bServiceType, WORD wPosition,BYTE *pChannelFavInfo);
#endif

INTERFACE BOOLEAN msAPI_CM_SkipProgram(MEMBER_SERVICETYPE bServiceType, WORD wPosition, BOOLEAN bSkip);
INTERFACE BOOLEAN msAPI_CM_UpdateProgramVisibleAndSelectable(MEMBER_SERVICETYPE bServiceType, WORD wPosition, BOOLEAN bVisible, BOOLEAN bSelectable);
INTERFACE BOOLEAN msAPI_CM_UpdateProgramSpecialService(MEMBER_SERVICETYPE bServiceType, WORD wPosition, BOOLEAN bSpecialService);
INTERFACE BOOLEAN msAPI_CM_LockProgram(MEMBER_SERVICETYPE bServiceType, WORD wPosition, BOOLEAN bLock);
INTERFACE BOOLEAN msAPI_CM_IsServiceExistWithIDsAndLCN(WORD wOriginalNetwork_ID, WORD wService_ID,  WORD wLCN);

INTERFACE BOOLEAN msAPI_CM_GetIDTable(WORD bIDIndex, BYTE * pcBuffer,PROGRAMDATA_MEMBER eMember);
INTERFACE BOOLEAN msAPI_CM_SetIDTable(WORD bIDIndex, BYTE * pcBuffer,PROGRAMDATA_MEMBER eMember);

INTERFACE void msAPI_CM_EnableStoreDataToFlash(BOOLEAN bEnable);//20090806

#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
INTERFACE BOOLEAN msAPI_CM_RemoveMismatchedMux(WORD wNID, WORD *pwTS_ID,  BYTE cCountOfTS,  U32 *u32NewTS, BOOLEAN bRemove);
INTERFACE BOOLEAN msAPI_CM_SetPhysicalChannelNumberAndCell(MEMBER_SERVICETYPE bServiceType, WORD wPosition, BYTE cRFChannelNumber, WORD wCellID);
INTERFACE BOOLEAN msAPI_CM_SetMismatchedCell(WORD wONID, WORD wTSID, WORD *pCellLsit, U8 u8CellNumber, BOOLEAN *bRemoved);
INTERFACE BOOLEAN msAPI_CM_IsServiceExistWithIDsAndLCN(WORD wOriginalNetwork_ID, WORD wService_ID,  WORD wLCN);
INTERFACE BOOLEAN msAPI_CM_CheckNetwork(WORD wNID, WORD *pwTS_ID,  BYTE cCountOfTS, U32 *u32NewTS, WORD *pwRemoveTSID, BYTE cMaxTSCnt, BOOLEAN *bRemove);
INTERFACE BOOLEAN msAPI_CM_GetCellIDByPosition(MEMBER_SERVICETYPE bServiceType, WORD wPosition, WORD *pwCellID);
INTERFACE BOOLEAN msAPI_CM_RemoveInvalidService(BOOLEAN *bCurCHIsRemoved);
INTERFACE BOOLEAN msAPI_CM_SetUnconfirmedServiceInvalid(WORD wONID, WORD wTSID, BOOLEAN *bGotService);
INTERFACE BYTE msAPI_CM_GetOriginalRFnumber(MEMBER_SERVICETYPE bServiceType, WORD wPosition);
INTERFACE BOOLEAN msAPI_CM_ResetOriginalRFnumber(MEMBER_SERVICETYPE bServiceType, WORD wPosition);
INTERFACE BOOLEAN msAPI_CM_ResetAlternativeTime(MEMBER_SERVICETYPE bServiceType, WORD wPosition);
INTERFACE U32 msAPI_CM_GetAlternativeTime(MEMBER_SERVICETYPE bServiceType, WORD wPosition);
#endif
#if (NTV_FUNCTION_ENABLE)
INTERFACE BOOLEAN msAPI_CM_IS_NorwegianNetwork(BYTE cNetworkIndex);
INTERFACE void msAPI_CM_Set_FavoriteNetwork(BYTE cNetworkIndex);
INTERFACE BYTE msAPI_CM_Get_FavoriteNetwork(void);
INTERFACE void msAPI_CM_RestoreProgramOrder(void);
INTERFACE void msAPI_CM_RestoreLCN(void);
#endif

INTERFACE U16 msAPI_CM_GetPhysicalChannelNumberByID(WORD wONID, WORD wTSID);
#if ENABLE_SDT_OTHER_MONITOR
INTERFACE BOOLEAN msAPI_CM_Is_TSExist(WORD wONID, WORD wTSID, BYTE *pcRFChannelNumber);
INTERFACE BOOLEAN msAPI_CM_GetCEllID_WithID(WORD wTS_ID, WORD wON_ID, WORD *wCell_ID, BOOLEAN *bOverOneCell);
INTERFACE BOOLEAN msAPI_CM_GetSameServiceInOtherMux(MEMBER_SERVICETYPE bServiceType, WORD wLCN, WORD wSID, WORD *pPosition);
#endif
INTERFACE WORD msAPI_CM_GetPrevProgramPosition(MEMBER_SERVICETYPE bServiceType, WORD wBasePosition, BOOLEAN bIncludeSkipped, CHANNEL_LIST_TYPE bList_type, MEMBER_SERVICETYPE *bNewServiceType);
INTERFACE WORD msAPI_CM_CountFavoriteProgram(MEMBER_SERVICETYPE bServiceType);
INTERFACE WORD msAPI_CM_GetNextFavoriteProgramPosition(MEMBER_SERVICETYPE bServiceType, WORD wBasePosition, BOOLEAN bIncludeSkipped);
INTERFACE WORD msAPI_CM_GetNextFavoriteProgramPositionbyListPosition(WORD wBasePosition,MEMBER_SERVICETYPE *eServiceType, BOOLEAN bIncludeSkipped);
INTERFACE BOOLEAN msAPI_CM_AddProgram(DTV_CHANNEL_INFO *pDTVProgramData, BOOLEAN *bDBFull, BOOLEAN bSkipCheck);
INTERFACE DTV_SIMPLE_SERVICE_INFO* msAPI_CM_GetDuplicateService(MEMBER_SERVICETYPE bServiceType, WORD wStartLCN);
INTERFACE BOOLEAN msAPI_CM_SetSelectService(DWORD dwIndex);

INTERFACE BOOLEAN msAPI_CM_UpdateProgram(MEMBER_SERVICETYPE bServiceType, WORD wPosition, BYTE *pcBuffer, PROGRAMDATA_MEMBER eMember);
INTERFACE BOOLEAN msAPI_CM_ArrangeDataManager(BOOLEAN bReArrangeLcn, BOOLEAN bSkipDupSrvRemove);
INTERFACE BOOLEAN ddmArrangeLogicalChannelNumber(MEMBER_SERVICETYPE eServiceType, E_MEMBER_LCN_TYPE eLcnType);
INTERFACE BOOLEAN msAPI_CM_SortDataManager(void);
INTERFACE BOOLEAN msAPI_CM_GetFirstPositionInPCN(MEMBER_SERVICETYPE bServiceType, U16 u16PCN, WORD * pwPosition);

#if ENABLE_SBTVD_DTV_SYSTEM

INTERFACE BOOL g_bIsSbtvdAppEn;

INTERFACE BOOLEAN msAPI_CM_GetFirstPositionInMajorNum(MEMBER_SERVICETYPE bServiceType, BYTE cMajorNum, WORD * pwPosition);
BYTE msAPI_CM_Get_FirstPhysicalChannelNumber(void);
#endif

INTERFACE WORD msAPI_CM_GetFirstFavoriteProgramPosition(MEMBER_SERVICETYPE bServiceType, BOOLEAN bIncludeSkipped);
INTERFACE WORD msAPI_CM_GetFirstFavoriteProgramPositionbylistpositon(MEMBER_SERVICETYPE *eServiceType, BOOLEAN bIncludeSkipped);
INTERFACE WORD msAPI_CM_GetLastFavoriteProgramPosition(MEMBER_SERVICETYPE bServiceType, BOOLEAN bIncludeSkipped);
INTERFACE WORD msAPI_CM_GetPrevFavoriteProgramPosition(MEMBER_SERVICETYPE bServiceType, WORD wBasePosition, BOOLEAN bIncludeSkipped);
INTERFACE void msAPI_CM_PrintAllProgram(void);
INTERFACE void msAPI_CM_PrintProgram(MEMBER_SERVICETYPE bServiceType, WORD wPosition);
#if ENABLE_SZ_DTV_ADDCH_SCAN_FUNCTION
INTERFACE BOOLEAN msAPI_IsEmptyPhysicalChannelNumber(BYTE number);
INTERFACE BYTE msAPI_CM_GetNextEmptyPhysicalChannelNumber(BYTE cRFChannelNumber);
#endif
INTERFACE void msAPI_CM_Set_TS_Update(BOOLEAN bCheck, WORD wTS_ID);
#if 0
INTERFACE BOOLEAN msAPI_CM_UpdatePCN(BYTE cOldRFCH, BYTE cNewRFCH);
#endif

//INTERFACE void msAPI_CM_ResetUnsupportedIso639Code(void);
//INTERFACE void msAPI_CM_LoadUnsupportedIso639CodeByIndex(U8 *pBuf, U8 u8BufSize, U8 u8Index);
//INTERFACE U8 msAPI_CM_SaveUnsupportedIso639Code(U8 *pCode);
INTERFACE BOOLEAN msAPI_CM_ArrangeAudioStreamInfo(MEMBER_SERVICETYPE bServiceType, WORD wPosition, U16 cValidAudIndex);

INTERFACE void msAPI_CM_Reset_AudioValidIndex(void);
INTERFACE U16 msAPI_CM_Get_AudioValidIndex(void);
INTERFACE BOOLEAN msAPI_CM_Update_AudioValidInfo(U16 u16AudioValidIndex);

INTERFACE WORD msAPI_CM_Get_RFChannelIndex(BYTE bRFChannel);
//INTERFACE BYTE msAPI_CM_Get_RFChannelIndex(BYTE bRFChannel);

#if ENABLE_DTV_STORE_TTX_PAGE_INFO//ENABLE_TTX
INTERFACE BOOLEAN msAPI_CM_GetListPageNumber(BYTE u8ListIndex, WORD * pwListPageNumber,MEMBER_SERVICETYPE bServiceType,WORD wPosition);
INTERFACE BOOLEAN msAPI_CM_SetListPageNumber(BYTE u8ListIndex, WORD wListPageNumber,MEMBER_SERVICETYPE bServiceType,WORD wPosition);
#endif

INTERFACE void msAPI_CM_SetAudioStreamValidIndex(MEMBER_SERVICETYPE bServiceType, WORD wPosition,  WORD wType, BYTE bISOLangIndex,U16 *pu16Index);

BOOLEAN msAPI_CM_AddProgramIDTable(DTVPROGRAMID *pstDtvIDTable,BOOLEAN bSave, U16 *pu16IDIndex);


INTERFACE void msAPI_CM_GetLIBVerString(U8 *pVer);
INTERFACE WORD msAPI_CM_GetPLP_ID(MEMBER_SERVICETYPE bServiceType, WORD wPosition);
INTERFACE BYTE msAPI_CM_GetHpLp(MEMBER_SERVICETYPE bServiceType, WORD wPosition);
INTERFACE BOOLEAN msAPI_CM_GetPLPID_WithID(WORD wTS_ID, WORD wON_ID, U8* pu8PLP_ID);
INTERFACE BOOLEAN msAPI_CM_GetHpLP_WithID(WORD wTS_ID, WORD wON_ID, U8* pu8HpLp);
INTERFACE BOOLEAN msAPI_CM_GetNetworkName(BYTE bIndex, BYTE * bNetworkName);
INTERFACE BOOLEAN msAPI_CM_SetNetworkName(BYTE bIndex, BYTE * bNetworkName);
INTERFACE BOOLEAN msAPI_CM_UpdateNetworkNameWithNID(WORD wNID, BYTE *bNetworkName);
INTERFACE BOOLEAN msAPI_CM_SetCurrentNetworkName(U8 *bNetworkName, U8 u8NetworkLen);
INTERFACE BOOLEAN msAPI_CM_GetCurrentNetworkName(U8 *bNetworkName, U8 *u8NetworkLen, U8 u8MaxLen);
INTERFACE WORD msAPI_CM_CountNetworkProgram(MEMBER_SERVICETYPE bServiceType, U16 u16NetworkID);
INTERFACE WORD msAPI_CM_GetFirstNetworkProgramPosition(MEMBER_SERVICETYPE bServiceType, U16 u16NetworkID);
INTERFACE WORD msAPI_CM_GetLastNetworkProgramPosition(MEMBER_SERVICETYPE bServiceType);
INTERFACE WORD msAPI_CM_GetNextNetworkProgramPosition(MEMBER_SERVICETYPE bServiceType, WORD wBasePosition, U16 u16NetworkID);
INTERFACE BOOLEAN msAPI_CM_ResetAttribute(MEMBER_SERVICETYPE bServiceType, WORD wPosition);
WORD msAPI_CM_GetPrevNetworkProgramPosition(MEMBER_SERVICETYPE bServiceType,U16 wBasePosition, U16 u16NetworkID);
INTERFACE BOOLEAN msAPI_CM_IsLCNExit(MEMBER_SERVICETYPE bServiceType, WORD wLCN, WORD *pPosition);

#if(ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
INTERFACE BOOLEAN msAPI_CM_SaveServiceListInfo(const U8 *pu8Dest, U16 u16ServiceListID, EN_SI_COUNTRY_SETTING eSICountry, BOOLEAN bIsCountryAvailability, BOOLEAN bListInFlag);
INTERFACE BOOLEAN msAPI_CM_GetExistServiceListInfo( const U16 u16ServiceListID, BOOLEAN bListInFlag);
INTERFACE BOOLEAN msAPI_CM_ResetServiceListInfoData(BOOLEAN bResetFlag);
INTERFACE U16 msAPI_CM_GetCurrentServiceListID(void);
INTERFACE U16 msAPI_CM_GetServiceListCount(void);
INTERFACE void msAPI_CM_GetServiceListName(U16 index,U8 *u8CharBuff);
INTERFACE BOOLEAN msAPI_CM_SaveAstraServiceInfo(U16 u16ServiceListID, MS_SI_SGT_SERVICE_INFO *stServiceInfo);
INTERFACE U16 msAPI_CM_GetAvailableServiceListID(void);
INTERFACE U16 msAPI_CM_GetAstraServiceCount(void);
INTERFACE MS_SI_SGT_SERVICE_INFO msAPI_CM_GetAstraServiceInfo(MS_U16 ServiceIndex);
INTERFACE U16 msAPI_CM_GetServiceListIdCount(void);
INTERFACE BOOLEAN msAPI_CM_UpdateLCNByChannellistId(U16 u16ChannellistId);
INTERFACE void msAPI_CM_SetCurrentServiceListID(U8 u8Servid);
INTERFACE U16 msAPI_CM_GetServiceListIDwithIndex(U8 _u8index);
INTERFACE void msAPI_CM_SetServiceListFocusIndex( U8 u8index);
INTERFACE U8 msAPI_CM_GetServiceListFocusIndex(void);

INTERFACE BOOLEAN msAPI_CM_GetAdd2ListFlag(void);
INTERFACE void msAPI_CM_IsAdd2List(BOOLEAN bIsAdd);
INTERFACE BOOLEAN msAPI_CM_GetAdd2ListSelectNOState(void);
INTERFACE void msAPI_CM_SetAdd2ListSelectNOState(BOOLEAN bIsNo);
INTERFACE BOOLEAN msAPI_CM_IsLCNInConflictList(WORD wlcn);
INTERFACE void msAPI_CM_SetLCNConflictListNum(MS_U8 u8Num);
INTERFACE MS_U8 msAPI_CM_GetLCNConflictListNum(void);
INTERFACE BOOLEAN MApp_Get_IsNITQuickScan(void);
INTERFACE void MApp_Set_IsNITQuickScan(BOOLEAN bquick);

INTERFACE MS_U8 msAPI_CM_GetDefaultFocusWithServListID(void);
INTERFACE void msAPI_CM_GetCurrentSatParam(BYTE *SatelliteId,U32 *u32S2Frequency,U16 *u16SymbolRate,BYTE *u8Polarity);
INTERFACE void msAPI_CM_ClearAllNewService(void);
INTERFACE void msAPI_CM_GetSgtVersionandPID(MS_SGT_ITEM *pCurSgtVerandPID);
INTERFACE BOOLEAN msAPI_CM_RemoveIsNewService(void);
#endif //(ASTRA_HD_ENABLE)

INTERFACE BOOLEAN msAPI_CM_GetIDIndexWithFreq(U32 u32Freq, U16 *pu16IDIndex);
//INTERFACE BOOLEAN msAPI_CM_GetIDIndexWithFreq(U32 u32Freq, BYTE *cIDIndex);
INTERFACE BOOLEAN msAPI_CM_UpdateNetworkCDSD(U8 u8PhNum,U32 u32Freq,U32 u32Symb,U8 u8Modu);

#if ENABLE_DVBC
INTERFACE BYTE msAPI_CM_RemoveQuickInstallMismatchedProgram(WORD *pwServiceID, U8 cCountOfServiceID, BYTE cRFChannelNumber, MEMBER_SERVICETYPE eServiceType);
INTERFACE void msAPI_CM_RemoveQuickInstallMismatchedTS(U16 *pu16TsIds, U8 u8TsIdNum);
#if ENABLE_T_C_CHANNEL_MIX
INTERFACE BOOLEAN msAPI_CM_RemoveDTVProgramOfAntenna(void);
#endif
#endif

#if(ENABLE_S2_FAST_SCAN)
INTERFACE BOOLEAN msAPI_CM_DVBS_GetServiceTypeAndPositionWithServiceIDs(WORD wTransportStream_ID, WORD wOriginalNetwork_ID, WORD wService_ID, BYTE cOrdinal, MEMBER_SERVICETYPE * peServiceType, WORD * pwPosition);
INTERFACE BOOLEAN msAPI_CM_Action_Set_M7DVBS_OpenMonitor(BOOLEAN bEnable);
INTERFACE BYTE msAPI_CM_GetScanType(MEMBER_SERVICETYPE bServiceType, WORD wPosition);

#endif //#if(ENABLE_S2_FAST_SCAN)

#if ENABLE_S2
#if ENABLE_S2_PROGRAM_PREPARE
typedef struct _SERVICE_STR
{
    BYTE* sServiceName;
    BYTE eServiceType;
    BYTE bIsScrambled:1;
    WORD wLogicalChannelNumber;
    WORD wSimu_LCN;
    WORD wService_ID;
    WORD wPCR_PID;
    WORD wVideoPID;
    WORD wPmtPID;
    WORD wAudioPID[MAX_AUD_LANG_NUM];
}SERVICE_STR;
typedef struct
{
    BYTE u8SatId;//MS_U16 u16Angle;//satellite angle,is used to search satellite id
    MS_U32 u32Frequency; //frequency and polarity are used to search PCN
    MS_U8 u8Polarity;//frequency and polarity are used to search PCN
    SERVICE_STR stService;
}DTV_SERVICE_INFO;
INTERFACE void msAPI_CM_SetProgram(void );
#endif
INTERFACE MS_BOOL IsS2ChannelEntityActive(WORD wPchIndex);
INTERFACE WORD MApi_DB_DFT_PhysicalChannelBySatID(MS_U8 u8SatID);
INTERFACE BOOLEAN MApi_DB_CM_DeleteAllProgByPCHIndex(WORD wPCN);
extern void MApi_DB_DFT_DeleteAllPhysicalChannelBySatID(BYTE bSatID);
extern BOOLEAN IsS2_Current_ProgramEntityActive(void);
extern void RemoveProgram_by_Sat(U8 sat);
extern void RemoveProgram_by_TP(DTVPROGRAMID_M stTpParam);
//extern void UpdateS2IDInfo(void);
#if(ENABLE_S2_CH_CHANGE_TO_SEARCHPOSITION)
extern BOOLEAN msAPI_CM_S2SetsearchPosition(WORD wPosition);
#endif
//extern BOOLEAN msAPI_CM_GetCountryFromFlash(void);
#endif
#if (ENABLE_LCN_CONFLICT)
INTERFACE void msAPI_CM_ResetLCNConflictParams(void);
#endif

//--------------------------------------------------------------------------------------
INTERFACE BOOLEAN GetIDTable(WORD bIDIndex, BYTE * pcBuffer, PROGRAMDATA_MEMBER eMember);
INTERFACE BOOLEAN GetIDTable_DBSel(TypDtvDbSel eDtvDbSel, WORD bIDIndex, BYTE * pcBuffer, PROGRAMDATA_MEMBER eMember);

INTERFACE BOOLEAN SetIDTable(WORD bIDIndex, BYTE * pcBuffer, PROGRAMDATA_MEMBER eMember);
INTERFACE BOOLEAN SetIDTable_DBSel(TypDtvDbSel eDtvDbSel, WORD bIDIndex, BYTE * pcBuffer, PROGRAMDATA_MEMBER eMember);

INTERFACE BOOLEAN ActiveIDEntity(WORD wIDIndex, BOOLEAN bActive);
INTERFACE BOOLEAN ActiveIDEntity_DBSel(TypDtvDbSel eDtvDbSel, WORD wIDIndex, BOOLEAN bActive);

U16 msAPI_DtvSys_Get_DefaultOrderOfDtv(TypDtvDbSel eDtvDbSel);
U16 msAPI_DtvSys_Get_DefaultOrderOfRadio(TypDtvDbSel eDtvDbSel);
U16 msAPI_DtvSys_Get_DefaultOrderOfData(TypDtvDbSel eDtvDbSel);

//--------------------------------------------------------------------------------------

INTERFACE BOOLEAN msAPI_CM_IS_SID_Unique_Country(void);
INTERFACE BOOLEAN msAPI_CM_IsAVCService(WORD wOriginalNetwork_ID, WORD wService_ID);
INTERFACE BOOLEAN msAPI_CM_RestLCNByRF(WORD* pServiceList, WORD wNumber, BYTE cRFNumber);

INTERFACE BOOLEAN msAPI_CM_RemoveMux(WORD wNID, WORD *pwTS_ID,  BYTE cCountOfTS, BOOLEAN *bRemove, BYTE sat, WORD freq);
//INTERFACE BOOLEAN msAPI_CM_RemoveMux(WORD wNID, WORD *pwTS_ID,  BYTE cCountOfTS, BOOLEAN *bRemove);

#if ENABLE_FAVORITE_NETWORK
INTERFACE void msAPI_DTV_Program_Network_Info_Print(U8 u8Index);
#endif

#if ENABLE_TARGET_REGION
INTERFACE void msAPI_CM_SetRegion(WORD wONID, WORD wTSID, WORD wSID, BYTE cValue);
#endif

#if ENABLE_DVB_T2
INTERFACE BOOLEAN msAPI_CM_DVBT2_RemoveMux(BYTE cRFChannelNumber, BYTE *pu8PlpIDList,  BYTE cCountOfPlpID);
#endif

#if (ENABLE_EPG_MUX)
INTERFACE void msAPI_CM_SetEITUpdate(BOOLEAN bUpdate);
INTERFACE BOOLEAN  msAPI_CM_GetEITUpdate(void);
#endif

INTERFACE BOOLEAN msAPI_CM_GetOpMode(void);
INTERFACE BOOLEAN msAPI_CM_IsCIOpType2(void);

#if (ENABLE_CI_PLUS)
INTERFACE void msAPI_CM_SetOpMode(BOOLEAN bOpMpde);
INTERFACE void msAPI_CM_SetCIOpType2(BOOLEAN bOpType);
INTERFACE void msAPI_CM_SwitchCMDB(BOOLEAN bOpMpde);
#endif

INTERFACE U16 msAPI_CM_GetMuxMaxNumber(void);

INTERFACE WORD msAPI_DTV_GetProgramCount(MEMBER_SERVICETYPE bServiceType, COUNT_PROGRAM_OPTION eCountOption);

//#undef INTERFACE
//#endif//#if ENABLE_DTV

extern BOOLEAN IsServiceTypeValid(MEMBER_SERVICETYPE bServiceType);

extern BOOLEAN msAPI_CM_ResetDTVDataManager(BOOLEAN bResetAllDB);
extern BOOLEAN msAPI_CM_InitDTVDataManager(void);
extern BOOLEAN msAPI_CM_InitDTVDataManager_CurSource(void);


extern MEMBER_COUNTRY msAPI_CM_GetCountry(void);
extern BOOLEAN msAPI_CM_SetCountry(MEMBER_COUNTRY eCountry);

#if ENABLE_S2_FIND_PROGRAM_BYNAME
extern BOOLEAN msAPI_CM_FindProgramByNameGetServiceName(MEMBER_SERVICETYPE bServiceType, WORD wPosition, BYTE * bChannelName);
extern U16 msAPI_CM_FindProgramByNameGetProgramAttribute(MEMBER_SERVICETYPE bServiceType, WORD wPosition, E_MEMBER_CHANNEL_ATTRIBUTE eAttributeMember);
extern WORD msAPI_CM_CountFindProgramByName(MEMBER_SERVICETYPE bServiceType,BYTE *bProgramName);
extern WORD msAPI_CM_GetPrevFindProgramByNamePosition(MEMBER_SERVICETYPE bServiceType, WORD wBasePosition, BOOLEAN bIncludeSkipped,BYTE *bProgramName);
extern WORD msAPI_CM_GetNextFindProgramByNamePosition(MEMBER_SERVICETYPE bServiceType, WORD wBasePosition, BOOLEAN bIncludeSkipped,BYTE *bProgramName);
#endif

#if ENABLE_S2_PREDIT_RENAME
extern BOOLEAN msAPI_CM_SetServiceName(MEMBER_SERVICETYPE bServiceType, WORD wPosition, BYTE * bChannelName);
#endif

#if 0//def MTC_FACTORY_TEST
void    MApp_Factory_TEST_AddOneDTVch( U16 u16PhysicalChIdx);
void    MApp_Factory_TEST_AddOneDTVch_2( U16 u16PhysicalChIdx);
void TEST_CREATE_DTV_CHANNEL(void);
#endif

void SET_Default_TW_DTV_CH(void);

BOOL IS_ATV_CH(WORD wOrdinal);
BOOL IS_HIDE_CH(WORD wOrdinal);
BOOL IS_FAV_CH(WORD wOrdinal);
BOOL IS_LOCK_CH(WORD wOrdinal);

void SET_HIDE_CH(BOOL bHide);
void SET_FAV_CH(BOOL bFav);
void SET_LOCK_CH(BOOL bLock);

BOOL msAPI_CM_Is_CurChannelT2(void);

void msAPI_DtvSys_PrintServiceName(U8* pu8Name, U16 u16MaxLen);

#if (CM_MULTI_FAVORITE)
void msAPI_CM_Set_CurFavoriteType(E_FAVORITE_TYPE eFavoriteType);
#endif

//------------------------------------------------------------------------------------
BOOLEAN msAPI_DtvSys_Is_SortByLCN(void);
BOOLEAN msAPI_DtvSys_Is_LCN_RANK_COUNTRY(EN_OSD_COUNTRY_SETTING eOSD_COUNTRY);
//------------------------------------------------------------------------------------

#ifdef ENABLE_DELETE_PROGRAM_CONTROL
INTERFACE BOOLEAN msAPI_CM_IsUserRemoveProgram(BOOLEAN bRemove);
INTERFACE BOOLEAN msAPI_CM_GetRemoveProgram(E_SERVICE_CHANGE *pChangeType);
#if ENABLE_S2_WORD
INTERFACE BOOLEAN msAPI_CM_HaveRemoveProgram(BYTE cRFChannelNumber, WORD wTSID, BYTE cPLP_ID, BYTE cHpLp, WORD *pwService_ID, MEMBER_SERVICETYPE *peService_Type, BYTE cCountOfServiceID, BYTE sat,WORD freq);
#else
INTERFACE BOOLEAN msAPI_CM_HaveRemoveProgram(BYTE cRFChannelNumber, WORD wTSID, BYTE cPLP_ID, BYTE cHpLp, WORD *pwService_ID, MEMBER_SERVICETYPE *peService_Type, BYTE cCountOfServiceID);
#endif
#endif

INTERFACE BOOLEAN msAPI_CM_RemoveProgram(MEMBER_SERVICETYPE bServiceType, WORD wPosition);


#undef INTERFACE

AUDIOSTREAM_TYPE msAPI_CM_SIAudStreamType_To_AudStreamType(SI_AUDIOSTREAM_TYPE eSIAudStreamType);
AUDIOSTREAM_TYPE msAPI_CM_Get_AudStreamType_By_AudInfo(AUD_INFO* pstAudInfo);
//SI_AUDIOSTREAM_TYPE msAPI_CM_Get_SIAudStreamType_By_AudInfo(AUD_INFO* pstAudInfo);
#define msAPI_CM_Get_SIAudStreamType_By_AudInfo(pstAudInfo) ((SI_AUDIOSTREAM_TYPE)((pstAudInfo)->eSIAudType))

#define msAPI_CM_Get_IDTab_SymbolRate(pstIdTab) ( (pstIdTab)->u16SymbolRate )

BOOLEAN msAPI_CM_Get_MS_TPSetting_By_IdTabIdx(U16 u16IdTabIdx, MS_TP_SETTING* pstMS_TP_SETTING);

#if( ENABLE_CM_STORE_AUD_INFO_NEW_METHOD )
BOOLEAN msAPI_CM_Add_AudInfo(AUD_INFO * pstCMAudInfo, U8 u8Count);
#endif

//------------------------------------------------------------------------------------------

#if(ENABLE_S2)
#include "msAPI_DTVSystem_DVBS.h"
#endif

/***************************************************************************************/

#endif//#if ENABLE_DTV

#endif // __API_DTVSYSTEM_H__

