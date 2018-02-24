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
#if (ENABLE_DTV_EPG)

#ifndef MAPP_EPGDB_PUBLIC_H
#define MAPP_EPGDB_PUBLIC_H

////////////////////////////////////////////////////////////////////////////////
///
/// @file mapp_epgdb_public.h
/// @author MStar Semiconductor Inc.
/// @brief EPG DB Interface Functions
///
////////////////////////////////////////////////////////////////////////////////

/******************************************************************************/
/*                              Include files                                 */
/******************************************************************************/
//#include "msAPI_MW_GlobalSt.h"
#include "datatype.h"
#include "MsTypes.h"
#if defined(BUILD_LIB)
#include "MsVersion.h"
#endif
#include "mapp_si_if.h"
//-------------------------------------------------------------------------------------------------
// Version Control
//-------------------------------------------------------------------------------------------------
#define MSIF_EPG_LIB_CODE          {'E','P','G','_'}                    //Lib code
#define MSIF_EPG_LIBVER            {'1','8'}                            //LIB version
#define MSIF_EPG_BUILDNUM          {'0','0'}                            //Build Number
#define MSIF_EPG_CHANGELIST        {'@','9','4','6','0','4','7','3'}    //P4 ChangeList Number

#define MW_EPG_VER                  /* Character String for DRV/API version             */  \
    MSIF_TAG,                       /* 'MSIF'                                           */  \
    MSIF_CLASS,                     /* '00'                                             */  \
    MSIF_CUS,                       /* 0x0000                                           */  \
    MSIF_MOD,                       /* 0x0000                                           */  \
    MSIF_CHIP,                                                                              \
    MSIF_CPU,                                                                               \
    MSIF_EPG_LIB_CODE,              /* IP__                                             */  \
    MSIF_EPG_LIBVER,                /* 0.0 ~ Z.Z                                        */  \
    MSIF_EPG_BUILDNUM,              /* 00 ~ 99                                          */  \
    MSIF_EPG_CHANGELIST,            /* CL#                                              */  \
    MSIF_OS

/******************************************************************************/
/*                                 Macro                                      */
/******************************************************************************/
#ifdef MAPP_EPGDB_PUBLIC_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

// Database parameters
#define MW_MAX_NUM_OF_EVENT_IN_EPGDB       MApp_EPGDB_GetMaxEventNumInDB()//10400
#define MW_MAX_NUM_OF_DAY_IN_SRV           8
#define MW_MAX_NUM_OF_SEG_IN_DAY           8
#define MW_MAX_NUM_OF_SEC_IN_SEG           8
#define MW_MAX_NUM_OF_SEG_IN_SRV           ((MW_MAX_NUM_OF_SEG_IN_DAY)*(MW_MAX_NUM_OF_DAY_IN_SRV))
#define MW_MAX_NUM_OF_SEC_IN_SRV           ((MW_MAX_NUM_OF_SEG_IN_SRV)*(MW_MAX_NUM_OF_SEC_IN_SEG))
#define MW_MAX_SHORT_EVENT_DESCRIPTOR_LEN  257
#define MW_MAX_EXTEND_EVENT_DESCRIPTOR_LEN 257
#define MW_MAX_NUM_OF_EIT_TABLE            (MW_MAX_NUM_OF_DAY_IN_SRV/MW_MAX_NUM_OF_DAY_IN_TBL)
#define MW_MAX_NUM_OF_DAY_IN_TBL           MIN(MW_MAX_NUM_OF_DAY_IN_SRV, 4)

#define MW_MAX_CRID_LENGTH                 64
#define MW_MAX_GUIDANCE_DESCRIPTOR_LEN     257

// Invalid Value
#define MW_INVALID_SERVICE_IDX             0xFFFF
#define MW_INVALID_EVENT_IDX               0xFFFF

#define ENABLE_EVENT_LINKAGE 0
/******************************************************************************/
/*                                 Enum                                       */
/******************************************************************************/
typedef enum
{
    MW_EN_EPG_FUNC_STATUS_SUCCESS       = 0,
    MW_EN_EPG_FUNC_STATUS_INVALID       = 1,
    MW_EN_EPG_FUNC_STATUS_NO_EVENT      = 2,
    MW_EN_EPG_FUNC_STATUS_NO_STRING     = 3,
    MW_EN_EPG_FUNC_STATUS_ERR_INDEX     = 4,
    MW_EN_EPG_FUNC_STATUS_ERR_CH        = 5,
    MW_EN_EPG_FUNC_STATUS_ERR_TIME      = 6
} MW_EN_EPG_FUNC_STATUS;

typedef enum
{
    MW_EN_EPG_MAIN_GENRE_TYPE_UNCLASSIFIED    = 0,
    MW_EN_EPG_MAIN_GENRE_TYPE_MOVIE           = 1,
    MW_EN_EPG_MAIN_GENRE_TYPE_NEWS            = 2,
    MW_EN_EPG_MAIN_GENRE_TYPE_SHOW            = 3,
    MW_EN_EPG_MAIN_GENRE_TYPE_SPORT           = 4,
    MW_EN_EPG_MAIN_GENRE_TYPE_CHILDREN        = 5,
    MW_EN_EPG_MAIN_GENRE_TYPE_MUSIC           = 6,
    MW_EN_EPG_MAIN_GENRE_TYPE_ARTS            = 7,
    MW_EN_EPG_MAIN_GENRE_TYPE_SOCIAL          = 8,
    MW_EN_EPG_MAIN_GENRE_TYPE_EDUCATION       = 9,
    MW_EN_EPG_MAIN_GENRE_TYPE_LESISURE        = 10,
    MW_EN_EPG_MAIN_GENRE_TYPE_SPECIAL         = 11,
    MW_EN_EPG_MAIN_GENRE_TYPE_RESERVED1       = 12,
    MW_EN_EPG_MAIN_GENRE_TYPE_RESERVED2       = 13,
    MW_EN_EPG_MAIN_GENRE_TYPE_RESERVED3       = 14,
    MW_EN_EPG_MAIN_GENRE_TYPE_USER_DEFINED    = 15,
    MW_EN_EPG_MAIN_GENRE_TYPE_MIN             = MW_EN_EPG_MAIN_GENRE_TYPE_UNCLASSIFIED,
    MW_EN_EPG_MAIN_GENRE_TYPE_MAX             = MW_EN_EPG_MAIN_GENRE_TYPE_USER_DEFINED,
    MW_EN_EPG_MAIN_GENRE_TYPE_SIZE            = MW_EN_EPG_MAIN_GENRE_TYPE_MAX + 1,
    MW_EN_EPG_MAIN_GENRE_TYPE_INVALID         = MW_EN_EPG_MAIN_GENRE_TYPE_MAX + 1,
} MW_EN_EPG_MAIN_GENRE_TYPE;

typedef enum
{
    MW_EN_EPG_ISDBT_GENRE_TYPE_NEWS          = 0,
    MW_EN_EPG_ISDBT_GENRE_TYPE_SPORT         = 1,
    MW_EN_EPG_ISDBT_GENRE_TYPE_EDUCATION     = 2,
    MW_EN_EPG_ISDBT_GENRE_TYPE_SOAP          = 3,
    MW_EN_EPG_ISDBT_GENRE_TYPE_MINISERIES    = 4,
    MW_EN_EPG_ISDBT_GENRE_TYPE_SERIES        = 5,
    MW_EN_EPG_ISDBT_GENRE_TYPE_VARIETY       = 6,
    MW_EN_EPG_ISDBT_GENRE_TYPE_REALITYSHOW   = 7,
    MW_EN_EPG_ISDBT_GENRE_TYPE_INFORMATION   = 8,
    MW_EN_EPG_ISDBT_GENRE_TYPE_COMICAL       = 9,
    MW_EN_EPG_ISDBT_GENRE_TYPE_CHILDREN      = 10,
    MW_EN_EPG_ISDBT_GENRE_TYPE_EROTIC        = 11,
    MW_EN_EPG_ISDBT_GENRE_TYPE_MOVIE         = 12,
    MW_EN_EPG_ISDBT_GENRE_TYPE_RAFFLE        = 13,
    MW_EN_EPG_ISDBT_GENRE_TYPE_DEBATE        = 14,
    MW_EN_EPG_ISDBT_GENRE_TYPE_OTHER         = 15,
    MW_EN_EPG_ISDBT_GENRE_TYPE_MIN             = MW_EN_EPG_ISDBT_GENRE_TYPE_NEWS,
    MW_EN_EPG_ISDBT_GENRE_TYPE_MAX             = MW_EN_EPG_ISDBT_GENRE_TYPE_OTHER,
    MW_EN_EPG_ISDBT_GENRE_TYPE_SIZE            = MW_EN_EPG_ISDBT_GENRE_TYPE_MAX + 1,
    MW_EN_EPG_ISDBT_GENRE_TYPE_INVALID         = MW_EN_EPG_ISDBT_GENRE_TYPE_MAX + 1,
} MW_EN_EPG_ISDBT_GENRE_TYPE;


typedef enum
{
    MW_EN_EPG_EIT_TYPE_UNKNOWN,
    MW_EN_EPG_EIT_TYPE_NON_SEGMENT,
    MW_EN_EPG_EIT_TYPE_SEGMENT,
    MW_EN_EPG_EIT_TYPE_MAX_NUM,
} MW_EN_EPG_EIT_TYPE;

typedef enum
{
    MW_EN_CRID_TYPE_PROGRAM,
    MW_EN_CRID_TYPE_SERIES,
    //MW_EN_CRID_TYPE_RECOMMENDATION,
    MW_EN_CRID_TYPE_MAX_NUM,
} MW_EN_CRID_TYPE;

typedef enum
{
    MW_EN_EPG_CRID_SEARCH_NONE,
    MW_EN_EPG_CRID_SEARCH_PREV,
    MW_EN_EPG_CRID_SEARCH_NEXT,
} MW_EN_EPG_CRID_SEARCH;

typedef enum
{
    eEN_PVR_CRID = 0x01,
    eEN_SCHE_EXT = 0x02,
    eEN_GUIDANCE = 0x04
} EN_EPG_FUNC_FLAG;

#if(MHEG5_SIINFO_ENABLE)
typedef enum
{
   MW_EN_EPG_PRESENT_STATUS,
   MW_EN_EPG_FOLLOW_STATUS,
}MW_EN_EPG_PF_STATUS;
#endif //#if(MHEG5_SIINFO_ENABLE)

/******************************************************************************/
/*                                 data type                                  */
/******************************************************************************/
typedef U16 EventIndex;          // event_index in EPG database
typedef U16 EventID;              // event_id from EIT

typedef struct
{
    U32  u32StartTime;
    U32  u32Duration;
} EventTime;

/******************************************************************************/
/*                                 Structure                                  */
/******************************************************************************/
#define EPG_PACKED_PUB __attribute__ ((__packed__))

typedef struct
{
    U16 u16TransportStreamID;
    U16 u16OriginalNetworkID;
    U16 u16ServiceID;
} MW_ST_EPG_CM_ID;

typedef struct
{
    U8  au8CridLength[MW_EN_CRID_TYPE_MAX_NUM];
    U8  au8CRID[MW_EN_CRID_TYPE_MAX_NUM][MW_MAX_CRID_LENGTH];
    MW_ST_EPG_CM_ID stCMID;
} MW_ST_EPG_CRID_PARSE;

typedef struct
{
    U16 u16HashEntry;
    U16 u16HeadIndex;
} MW_ST_EPG_CRID_PARAM;

/// Define struct info for HD/SD simulcast
typedef struct EPG_PACKED_PUB
{
    MW_ST_EPG_CM_ID stTargetTripleid;
    U16        u16TargetEventId;
    BOOL       bIsSimulcast;
}MS_ST_EPG_EIT_SIMULCAST;

typedef struct EPG_PACKED_PUB
{
    U8  start_time[5];
    U8  duration[3];
    U8  u8Content_nibble_level1 : 4;
    U8  u8Content_nibble_level2 : 4;
    U8  u8ParentalRating;
    U16 u16SecNumInSrv;
    U16 u16EventId;
#if ENABLE_SCHE_EXT
    U8  u8ExtDescLen;
    U32 u32StartingExtIdx;
#endif
#if SUPPORT_PVR_CRID
    MW_ST_EPG_CRID_PARAM CRID_Param[MW_EN_CRID_TYPE_MAX_NUM];
#endif
#if ENABLE_EVENT_LINKAGE
    MS_ST_EPG_EIT_SIMULCAST stEitSimulcastinfo;  //ENABLE_EVENT_LINKAGE
#endif
#if(MHEG5_SIINFO_ENABLE)
    U8   u8FreeNotCA   : 1;
#endif //#if(MHEG5_SIINFO_ENABLE)
} MW_EN_EPG_EVENT_HDR;

typedef struct EPG_PACKED_PUB
{
    MW_EN_EPG_EVENT_HDR    header;
    U8                     short_event_descriptor[MW_MAX_SHORT_EVENT_DESCRIPTOR_LEN];
    U8                  guidance_descriptor[MW_MAX_GUIDANCE_DESCRIPTOR_LEN];
} MW_EN_EPG_EVENT;

typedef struct EPG_PACKED_PUB
{
    U8  au8SegMask[MW_MAX_NUM_OF_SEG_IN_SRV / 8];
    U8  au8SecMask_InSeg[MW_MAX_NUM_OF_SEG_IN_SRV];
    U8  au8CntSec_InSeg[MW_MAX_NUM_OF_SEG_IN_SRV];         // 136 Bytes
    U8  au8TblVerNum[MW_MAX_NUM_OF_EIT_TABLE];
    U8  au8TblVerNum_Other[MW_MAX_NUM_OF_EIT_TABLE];       // 4 Byte
    U8  u8GotSFirstSec_Other: 2;
    U8  u8GotSFirstSection  : 2;
    U8  reserved            : 4;                        // 1 Byte
    U16 u16TblEvtCount[2];                              // 4 Byte
    U8  u8EitLSN[MW_MAX_NUM_OF_EIT_TABLE];                 // 2 Byte
    MW_EN_EPG_EIT_TYPE enEitType;                       // 4 Byte

} MW_EN_EPG_SCHE_SRV_HDR;

typedef struct EPG_PACKED_PUB
{
    U8  fGotPfFirstSection  : 1;
    U8  u8PfSecMask         : 2;
    U8  u8PfTblVerNum       : 5;                        // 1 Byte
    U8  fGotPfFirstSec_Other: 1;
    U8  reserved            : 2;
    U8  u8PfTblVerNum_Other : 5;                        // 1 Byte
    U16 au16PfEvtIdx[2];                                // 4 Byte
    U32 au32CRC[2];                                     // 8 Byte
} MW_EN_EPG_PF_SRV_HDR;

typedef struct
{
    U32 u32MaxNumOfEventInEPGDB;
    U32 u32MaxNumOfEventInSrv;
}MW_EN_EPG_DB_PARAM_CONFIG;

#if(MHEG5_SIINFO_ENABLE)

typedef struct EPG_MHEG5_GENRE_TYPE
{
   /// Event genre (0x0041 + content_nibble_level_1, 0x0061 + content_nibble_level_2) A~P, a~p
    U8  u8Content_nibble_level1  : 4;
    U8  u8Content_nibble_level2  : 4;
    /// Indicates if the event is CA controlled or not (true indicates free).
    U8  u8FreeNotCA :   1;

}MW_MHEG5_EPG_GENRE_TYPE_PF_CA;

typedef struct MHEG5_EVENTTIME
{
    /// Event Start date (MJD)
    U32  u32StartDateInMJD;
   /// Event Start time of day in second
    U32  u32StartTimeInUTC;
   /// Event duration
    U32  u32Duration;

} MHEG5_EVENTTIME_INFO;

typedef struct EPG_MHEG5_PACKED_PUB
{
    /// Event rating
    U8  u8ParentalRating;
   /// Event name
    U16  u16EventName[EPG_TIMER_MAX_EVENT_NAME_LEN];
   /// Short event description
    U16  u16ShortDescriptionData[MW_MAX_SHORT_EVENT_DESCRIPTOR_LEN];
   ///Event time Or date
    MHEG5_EVENTTIME_INFO stEventTimeDate;
   ///Event part info
    MW_MHEG5_EPG_GENRE_TYPE_PF_CA stNibblePfCa;

} MW_MHEG5_GET_EPG_EVENT_INFO;

#endif //#if(MHEG5_SIINFO_ENABLE)

/******************************************************************************/
/*                              Interface Function                            */
/******************************************************************************/

/**
 *@brief  : set function flag
 *@param   eFlag       : [IN]  be setted flag
 *@return : None
 *
 *@see
*/
INTERFACE void MAPP_EPG_SetFunctionFlag(EN_EPG_FUNC_FLAG eFlag);


/**
 *@brief  : set board information
 *@param : None
 *@return : None
 *
 *@see
*/
INTERFACE void MAPP_EPG_InitFunctionSetting(void);

/**
 *@brief  : get event start time / duration by event index
 *@param    event       : [IN]  event index
 *@param    pEventTime  : [OUT] event start time
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_GetEventTime(EventIndex event, EventTime* pEventTime);

/**
 *@brief  : get event nibble_level1  by event index
 *@param    event       : [IN]  event index
 *@param    pNibbleLevel1  : [OUT] nibble_level1
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_GetNibbleLevel1(EventIndex event, MW_EN_EPG_ISDBT_GENRE_TYPE* pNibbleLevel1);

/**
 *@brief  : get EventID by event index
 *@param    event       : [IN]  event index
 *@param    pEventID    : [OUT] event unique id from TS
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_GetEventID(EventIndex event, EventID* pEventID);


/**
 *@brief  : get event name by event index
 *@param    event   : [IN]  event index
 *@param    pName   : [OUT] event name
 *@param    length  : [IN]  max limited length of this returned event name
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_GetEventName(EventIndex event, U16* pName, U16 length);


/**
 *@brief  : get UCS1 event name by event index
 *@param    event   : [IN]  event index
 *@param    pName   : [OUT] event name
 *@param    length  : [IN]  max limited length of this returned event name
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_GetUCS1EventName(EventIndex event, U8* pName, U8 length);

/**
 *@brief  : get event short description by event index
 *@param    event        : [IN]  event index
 *@param    pDescription : [OUT] event short description
 *@param    pSrcLength   : [OUT] string length in description
 *@param    length       : [IN]  max limited length of this returned description
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_GetShortDescription(EventIndex event, U16* pDescription, U8* pSrcLength, U16 length);

/**
 *@brief  : get event detailed (Short+Ext) description by event index
 *@param    event        : [IN]  event index
 *@param    pDescription : [OUT] event short description
 *@param    pSrcLength   : [OUT] string length in description
 *@param    length       : [IN]  max limited length of this returned description
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_GetDetailDescription(EventIndex event, U16* pDescription, U16* pStrLength, U16 length);

 /**
 *@brief  : get event detailed (Ext) description by event index
 *@param    event        : [IN]  event index
 *@param    pDescription : [OUT] event short description
 *@param    pSrcLength   : [OUT] string length in description
 *@param    length       : [IN]  max limited length of this returned description
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_GetExtDetailDescription(EventIndex event, U16* pDescription, U16* pStrLength, U16 length);

/**
 *@brief  : get event detailed (Short+Ext) description by offset by event index
 *@param    event        : [IN]  event index
 *@param    pDescription : [OUT] event short description
 *@param    pSrcLength   : [OUT] string length in description
 *@param    length       : [IN]  max limited length of this returned description
 *@param    u16Shift       : [IN]  copy data offset
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_GetDetailDescriptionByOffset(EventIndex event, U16* pDescription, U16* pStrLength, U16 length, U16 u16Shift);

/**
 *@brief  : get event guidance description by event index
 *@param    event        : [IN]  event index
 *@param    pDescription : [OUT] event short description
 *@param    pSrcLength   : [OUT] string length in description
 *@param    length       : [IN]  max limited length of this returned description
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_GetGuidanceDescription(EventIndex event, U16* pDescription, U16* pStrLength, U16 length);

/**
 *@brief  : get the number of extended descriptors in this event
 *@param    event   : [IN]  event index
 *@param    pSize   : [OUT] the number of extended descriptors in this event
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_GetExtDescriptionSize(EventIndex event, U8* pSize);

/**
 *@brief  : get event Xth extended description by event index
 *@param    event        : [IN]  event index
 *@param    index        : [IN]  X; the sequence of ext descriptors of this event
                                 (X = 0 ~ (Y-1), Y == the number of extended descriptors of this event)
 *@param    pDescription : [OUT] Xth ext description of this event
 *@param    length       : [IN]  max limited length of this returned description
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_GetExtDescription(EventIndex event, U8 u8Index, U16* pDescription, U8* pStrLength, U16 length);

/**
 *@brief  : get the present event info of the current channel
 *@param    pEventTime   : [OUT] event time
 *@param    pName        : [OUT] event name
 *@param    pDescription : [OUT] event short description
 *@param    pEvent       : [OUT] event index
 *@param    pSize        : [OUT] the number of extended descriptors in this event
 *@param    length       : [IN]  max limited length of this returned name/description
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_GetCurPresentInfo(EventTime* pEventTime, U16* pName, U16* pDescription, EventIndex* pEvent, U8* pSize, U16 length);

/**
 *@brief  : get the following event info of the current channel
 *@param    pEventTime   : [OUT] event time
 *@param    pName        : [OUT] event name
 *@param    pDescription : [OUT] event short description
 *@param    pEvent       : [OUT] event index
 *@param    pSize        : [OUT] the number of extended descriptors in this event
 *@param    length       : [IN]  max limited length of this returned name/description
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_GetCurFollowInfo(EventTime* pEventTime, U16* pName, U16* pDescription, EventIndex* pEvent, U8* pSize, U16 length);

/**
 *@brief  : get event genre type by event index
 *@param    event           : [IN]  event index
 *@param    pMainGenreType  : [OUT] event nibble1
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_GetGenreType(EventIndex event, MW_EN_EPG_MAIN_GENRE_TYPE* pMainGenreType);

/**
 *@brief  : get event rating by event index
 *@param    event        : [IN]  event index
 *@param    pEventRating : [OUT] event rating
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_GetEventRating(EventIndex event, U8* pEventRating);

/**
 *@brief  : search a matched event by a given time;
            event start/end time exactly matched the given time
 *@param    enSrvType : [IN]  service type
 *@param    wSrvPos   : [IN]  service position
 *@param    pBaseTime : [IN]  given event time
 *@param    pEvent    : [OUT] matched event index
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_GetEvent(MEMBER_SI_SERVICETYPE enSrvType, U16 u16SrvPos, const U32 u32BaseTime, EventIndex* pEvent);

/**
 *@brief  : Get the present event index
 *@param    enSrvType : [IN]  service type
 *@param    wSrvPos   : [IN]  service position
 *@param    pEvent    : [OUT] event index
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_GetPresentEventIdx(MEMBER_SI_SERVICETYPE enSrvType, U16 u16SrvPos, EventIndex* pEvent);

/**
 *@brief  : Get the following event index
 *@param    enSrvType : [IN]  service type
 *@param    wSrvPos   : [IN]  service position
 *@param    pEvent    : [OUT] event index
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_GetFollowEventIdx(MEMBER_SI_SERVICETYPE enSrvType, U16 u16SrvPos, EventIndex* pEvent);

/**
 *@brief  : search a matched event by a given time;
            event start time could be equal/later than the given time
 *@param    enSrvType : [IN]  service type
 *@param    wSrvPos   : [IN]  service position
 *@param    pBaseTime : [IN]  given event time
 *@param    pEvent    : [OUT] matched event index
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_EventFindByTime(MEMBER_SI_SERVICETYPE enSrvType, U16 u16SrvPos, U32 u32BaseTime, EventIndex* pEvent);

/**
 *@brief  : search a next event by a given time;
            event start time could be equal/later than the given time
 *@param    enSrvType : [IN]  service type
 *@param    wSrvPos   : [IN]  service position
 *@param    pBaseTime : [IN]  given event time
 *@param    pEvent    : [OUT] matched event index
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_EventFindNextByTime(MEMBER_SI_SERVICETYPE enSrvType, U16 u16SrvPos, const U32 u32BaseTime, EventIndex* pEvent);

/**
 *@brief  : search a matched event by a given time;
            event start time is supposed to be later than the given time
 *@param    enSrvType  : [IN]  service type
 *@param    wSrvPos    : [IN]  service position
 *@param    baseEvent  : [IN]  given event time
 *@param    pNextEvent : [OUT] matched event index
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_EventFindNext(MEMBER_SI_SERVICETYPE enSrvType, U16 u16SrvPos, EventIndex baseEvent, EventIndex* pNextEvent);

/**
 *@brief  : search a matched event by a given time;
            event start time is supposed to be earlier than the given time
 *@param    enSrvType  : [IN]  service type
 *@param    wSrvPos    : [IN]  service position
 *@param    baseEvent  : [IN]  given event time
 *@param    pPrevEvent : [OUT] matched event index
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_EventFindPrevious(MEMBER_SI_SERVICETYPE enSrvType, U16 u16SrvPos, EventIndex baseEvent, EventIndex* pPrevEvent);

/**
 *@brief  : get event index by event unique id
 *@param    enSrvType     : [IN]  service type in CM
 *@param    wSrvPos       : [IN]  service position in CM
 *@param    u16EventID    : [IN]  event unique id from TS
 *@param    pEventIdx     : [OUT] matched event index
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_EventFindByID(MEMBER_SI_SERVICETYPE enSrvType, U16 u16SrvPos, U16 u16EventID, EventIndex* pEventIdx);

/**
 *@brief  : to see if service event info is updated by version change or not
 *@param    enSrvType  : [IN]  service type
 *@param    wSrvPos    : [IN]  service position
 *@return : Updated?
 *
 *@see
 */
INTERFACE BOOL MApp_Epg_IsEventInfoUpdated(MEMBER_SI_SERVICETYPE enSrvType, U16 u16SrvPos);

/**
 *@brief  : access service EIT schedule info
 *@param    u16SrvIdx : [IN]  VirChIdx in CM (EEPROM)
 *@param    pstSrvHdr : [OUT] service EIT schedule info
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_SCHE_SRV_HDR* MApp_Epg_Sche_SrvHdr_Load( U16 u16SrvIdx );

/**
 *@brief  : access service EIT present/following info
 *@param    u16SrvIdx : [IN]  VirChIdx in CM (EEPROM)
 *@param    pstSrvHdr : [OUT] service EIT pf info
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_PF_SRV_HDR* MApp_Epg_Pf_SrvHdr_Load( U16 u16SrvIdx );

/**
 *@brief  : get pf table version number
 *@param    enSrvType   : [IN]  service type
 *@param    u16SrvPos   : [IN]  service position
 *@param    pu8TableVer : [OUT] table version
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_Pf_GetTableVersion(MEMBER_SI_SERVICETYPE enSrvType, U16 u16SrvPos, U8* pu8TableVer);


/**
 *@brief  : if table updates in EIT pf, this function returns the pf events to event pool
 *@param    pstSrvHdr : [OUT] service EIT pf info
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_Pf_VersionUpdate(U16 u16SrvIdx, MW_EN_EPG_PF_SRV_HDR* gpSrv);

/**
 *@brief  : SI EIT pf event saving
 *@param    u16SrvIdx : [IN]  VirChIdx in CM (EEPROM)
 *@param    u8SecNum  : [IN]  0: present,
                              1: following
 *@param    pPfSrvHdr : [IN]  service EIT pf info
 *@param    pSrcEvent : [IN]  incoming EIT pf event data
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_Pf_Event_Save (U16 u16SrvIdx, U8 u8SecNum, MW_EN_EPG_PF_SRV_HDR* gpPfSrvHdr, MW_EN_EPG_EVENT* gpSrcEvent);

/**
 *@brief  : SI EIT schedule event saving
 *@param    u16SrvIdx       : [IN]  VirChIdx in CM (EEPROM)
 *@param    u16SecNum_InSrv : [IN]  section number X;
                                    (Y days, X = 0 ~ (Y*64-1))
 *@param    pSrvHdr         : [IN]  service EIT schedule info
 *@param    u8SecEvtSeq     : [IN]  Xth event in this section;
                                    ( X = 0 ~ (u8SecEvtNum-1) )
 *@param    u8SecEvtNum     : [IN]  total number of events in this section
 *@param    pSrcEvent       : [IN]  incoming EIT schedule event data
 *@param    pCridParse      : [IN]  incoming CRID data; for PVR usage
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_Sche_Event_Save (U16 u16SrvIdx, U8 u8SegLastSecNum, MW_EN_EPG_SCHE_SRV_HDR* gpSrvHdr, U8 u8SecEvtSeq, U8 u8SecEvtNum, MW_EN_EPG_EVENT* gpSrcEvent, MW_ST_EPG_CRID_PARSE* gpCridParse);

/**
 *@brief  : if table updates in EIT schedule, this function returns the schedule events to event pool
 *@param    u16SrvIdx : [IN]  VirChIdx in CM (EEPROM)
 *@param    pstSrvHdr : [OUT] service EIT pf info
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_Sche_VersionUpdate (U16 u16SrvIdx, MW_EN_EPG_SCHE_SRV_HDR* gpSrv, U8 u8TblIdx);

/**
 *@brief  : While version number changes, check event content to see if erase previous data or not
 *@param    u16SrvIdx       : [IN] VirChIdx in CM (EEPROM)
 *@param    u8SecNum        : [IN] section number
 *@param    pNewEvent       : [IN] event data to compare
 *@return : Different content?
            TRUE: different, FALSE: same.
 *
 *@see
 */
INTERFACE BOOL MApp_Epg_Pf_CheckVersionDiffContent (U16 u16SrvIdx, U8 u8SecNum, MW_EN_EPG_PF_SRV_HDR* gpstPfSrvHdr, MW_EN_EPG_EVENT_HDR* gpNewEvtHdr);

/**
 *@brief  : While version number changes, check event content to see if erase previous data or not
 *@param    u16SrvIdx       : [IN] VirChIdx in CM (EEPROM)
 *@param    u16SecNum_InSrv : [IN] section number
 *@param    u8SecEvtSeq     : [IN] event sequence in this section
 *@param    pNewEvent       : [IN] event data to compare
 *@return : Different content?
            TRUE: different, FALSE: same.
 *
 *@see
 */
INTERFACE BOOL MApp_Epg_Sche_CheckVersionDiffContent (U16 u16SrvIdx, U16 u16SecNum_InSrv, U8 u8SecEvtSeq, MW_EN_EPG_SCHE_SRV_HDR* gstScheSrvHdr , MW_EN_EPG_EVENT_HDR* gpNewEvtHdr);


#if ENABLE_SCHE_EXT
/**
 *@brief  : initialize extended related variables.
            call this function before parsing descriptors in each event
 *@param    pEvent : [IN] currently parsing event data
 *@return : None
 *
 *@see
 */
INTERFACE void MApp_Epg_InitEventExtIdx ( MW_EN_EPG_EVENT* gpEvent );

/**
 *@brief  : save extended descriptors of this event
 *@param    pu8Descriptor    : [IN] extended descriptor
 *@param    u32DescriptorLen : [IN] extended descriptor length
 *@param    pEvent           : [IN] currently parsing event data
 *@return : extended pool is full,
            EPG database is going to reset, we should stop parsing this section
 *
 *@see
 */
INTERFACE BOOL MApp_Epg_ExtDesc_Save ( U8* pu8Descriptor, U32 u32DescriptorLen , MW_EN_EPG_EVENT* gpEvent );
#endif //ENABLE_SCHE_EXT

/**
 *@brief  : function used to set EPG buffer index to same service
 *@param    au8Sec : [IN]  received section data
 *@return : None
 *
 *@see
 */
INTERFACE void MApp_Epg_SameSrvHandler( U8 au8Sec[] );

/**
 *@brief  : This function is for CM usage while deleting service dynamically
 *@param    u16VirChIdx : [IN]  VirChIdx in CM (EEPROM)
 *@return : None
 *
 *@see
 */
INTERFACE void MApp_Epg_DeleteService(U16 u16VirChIdx);

/**
 *@brief  : EPG DB function used to get the service index of channel list
 *@param    u8SameSrvSerial : [IN] the order of wanted same service
 *@param    au8Sec          : [IN] received section data
 *@return : service index of channel list, INVALID_SRV_IDX for invalid service
 *
 *@see
 */
INTERFACE BOOLEAN  MApp_Epg_FindMatchSrvChannel( U8 u8SameSrvSerial, U8 au8Sec[] , U16 *pChannelIndex);

/**
 *@brief  : This function is for CM usage while deleting service dynamically
 *@param    u16VirChIdx : [IN]  VirChIdx in CM (EEPROM)
 *@return : None
 *
 *@see
 */
INTERFACE void MApp_Epg_MoveSrvBuffer(U16 u16FromIndex, U16 u16ToIndex);
INTERFACE void MApp_Epg_SwapProgram(WORD wFromOrder, WORD wToOrder);
INTERFACE void MApp_Epg_RemoveProgram(WORD wSrvOrder);
/**
 *@brief  : calculate the service priority for the case EPG database is full.
            the EIT buffer assigned to the service with lowest priority will be replaced.
            CM/UI should call this function whenever channel change.
 *@param    u16MainlistIdx : [IN]  Mainlist index
 *@return : None
 *
 *@see
 */
INTERFACE void MApp_Epg_SrvPriorityHandler (U16 u16MainlistIdx);

/**
 *@brief  : restart EPG database
 *@param  : None
 *@return : None
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_Init( void );


/* Info Banner ********************************************************************************************/
/**
 *@brief  : EPG DB function used to load event name
 *@param    pu16Dst   : [OUT] pointer of U16 string buffer
 *@param    u16Length : [IN]  maximum length of U16 string buffer
 *@param    pSED      : [IN]  pointer to source data, short event descriptor
 *@return : string length
 *
 *@see
 */
INTERFACE U8   MApp_Epg_EventName_LoadFromSED( U16* pu16Dst, U16 Length, U8* pSED );

/**
 *@brief  : EPG DB function used to load event short text
 *@param    pu16Dst   : [OUT] pointer of U16 string buffer
 *@param    u16Length : [IN]  maximum length of U16 string buffer
 *@param    pSED      : [IN]  pointer to source data, short event descriptor
 *@return : string length
 *
 *@see
 */
INTERFACE U8   MApp_Epg_EventText_LoadFromSED( U16* pu16Dst, U16 Length, U8* pSED );

/**
 *@brief  : EPG DB function used to load event extended text
 *@param    pu16Dst   : [OUT] pointer of U16 string buffer
 *@param    u16Length : [IN]  maximum length of U16 string buffer
 *@param    pEED      : [IN]  pointer to source data, extended event descriptor
 *@return : string length
 *
 *@see
 */
INTERFACE U8   MApp_Epg_ExtendEventText_LoadFromEED( U16* pu16Dst, U16 Length, U8* pEED );

/**
 *@brief  : EPG DB function used to load item text of event extended text
 *@param    pu16Dst   : [OUT] pointer of U16 string buffer
 *@param    u16Length : [IN]  maximum length of U16 string buffer
 *@param    pEED      : [IN]  pointer to source data, extended event descriptor
 *@return : string length
 *
 *@see
 */
INTERFACE U8   MApp_Epg_ItemText_LoadFromEED( U16* pu16Dst, U16 Length, U8* pEED );

/**
 *@brief  : EPG DB function used to load guidance information text from guidance descriptor
 *@param    pu16Dst   : [OUT] pointer of U16 string buffer
 *@param    u16Length : [IN]  maximum length of U16 string buffer
 *@param    pGuid      : [IN]  pointer to source data, short event descriptor
 *@return : string length
 *
 *@see
 */
INTERFACE U8 MApp_Epg_GuidanceText_LoadFromGUD( U16* pu16Dst, U16 Length, U8* pGuid );

/* Info Banner ********************************************************************************************/


/* PVR ********************************************************************************************/
#if SUPPORT_PVR_CRID
/**
 *@brief  : Query if the event has other series events or not
 *@param    event : [IN]  event index
 *@return : has or has no
 *
 *@see
 */
INTERFACE BOOL MApp_Epg_IsEventSeries(EventIndex event);

/**
 *@brief  : Query if the event has other split events or not
 *@param    event : [IN]  event index
 *@return : has or has no
 *
 *@see
 */
INTERFACE BOOL MApp_Epg_IsEventSplit(EventIndex event);

/**
 *@brief  : Query if the event has other alternate events or not
 *@param    event : [IN]  event index
 *@return : has or has no
 *
 *@see
 */
INTERFACE BOOL MApp_Epg_IsEventAlternate(EventIndex event);

/**
 *@brief  : Get the previous/next (event time) series event
 *@param    event      : [IN]  querying event index
 *@param    enSearch   : [IN]  previous or next
 *@param    pPCN       : [OUT] physical channel number
 *@param    pServiceID : [OUT] service ID
 *@param    pEvent     : [OUT] searched event index
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_GetEventSeries(EventIndex event, MW_EN_EPG_CRID_SEARCH enSearch, U8* pPCN, U16* pServiceID, EventIndex* pEvent);

/**
 *@brief  : Get the previous/next (event time) split event
 *@param    event      : [IN]  querying event index
 *@param    enSearch   : [IN]  previous or next
 *@param    pPCN       : [OUT] physical channel number
 *@param    pServiceID : [OUT] service ID
 *@param    pEvent     : [OUT] searched event index
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_GetEventSplit(EventIndex event, MW_EN_EPG_CRID_SEARCH enSearch, U8* pPCN, U16* pServiceID, EventIndex* pEvent);

/**
 *@brief  : Get the previous/next (event time) alternate event
 *@param    event      : [IN]  querying event index
 *@param    enSearch   : [IN]  previous or next
 *@param    pPCN       : [OUT] physical channel number
 *@param    pServiceID : [OUT] service ID
 *@param    pEvent     : [OUT] searched event index
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_GetEventAlternate(EventIndex event, MW_EN_EPG_CRID_SEARCH enSearch, U8* pPCN, U16* pServiceID, EventIndex* pEvent);
#endif  //SUPPORT_PVR_CRID
/* PVR ********************************************************************************************/


/* Debug Function *****************************************************************************************/
#if SUPPORT_PVR_CRID
/**
 *@brief  : Test the linkage relation of crid hash table, crid_head and crid_event
 *@param    None
 *@return : None
 *
 *@see
 */
INTERFACE void MApp_Epg_CRIDLinkTest( void );

/**
 *@brief  : Test crid series/split/alternate interface functions
 *@param    event   : [IN]  event index
 *@return : None
 *
 *@see
 */
INTERFACE void MApp_Epg_CRIDInterfaceTest( EventIndex event );
#endif  //SUPPORT_PVR_CRID
/**
 *@brief  : EPG DB setup
 *@param    u16MaxDTVProgram  : [IN]  maximal program
 *@param    u32EventDBSDRAMAdr    : [IN]  event DB start address
 *@param    u32EventDBSDRAMLen    : [IN]  event DB length
 *@param    u32EPGExtDBSDRAMAdr    : [IN]  extend event DB start address
 *@param    u32EPGExtDBSDRAMLen    : [IN]  extend event DB length
*@return : None
 *
 *@see
 */
INTERFACE BOOL MApp_EPGDB_Setup(U16 u16MaxDTVProgram,
                U32 u32EventDBSDRAMAdr, U32 u32EventDBSDRAMLen, U32 u32EPGExtDBSDRAMAdr, U32 u32EPGExtDBSDRAMLen);
/**
 *@brief  : EPG DB set max dtv program
 *@param    u16MaxDTVProgram  : [IN]  maximal program
*@return : None
 *
 *@see
 */
INTERFACE void MAPP_EPGDB_SetMaxDTVProgram(U16 u16MaxDTVProgram);

/**
 *@brief  : EPG DB parameters configure
 *@param    stEpgDBParam  : [IN]  configure EPG DB parameters structure
*@return : None
 *
 *@see
 */
INTERFACE void MApp_EPGDB_ParamConfig(MW_EN_EPG_DB_PARAM_CONFIG *stEpgDBParam);

/**
 *@brief  : Debug function of EPG database buffer tables
 *@param    enSrvType  : [IN]  service type
 *@param    wSrvPos    : [IN]  service position
 *@return : None
 *
 *@see
 */
INTERFACE void MApp_Epg_BufTableTest( MEMBER_SI_SERVICETYPE enSrvType, U16 u16SrvPos );

/**
 *@brief  : Debug function of EPG database service header
 *@param    enSrvType  : [IN]  service type
 *@param    wSrvPos    : [IN]  service position
 *@return : None
 *
 *@see
 */

INTERFACE void MApp_Epg_ServiceHeaderTest( MEMBER_SI_SERVICETYPE enSrvType, U16 u16SrvPos );
/* Debug Function *****************************************************************************************/

/* Version Control ****************************************************************************************/
/**
 *@brief  : Get library version
 *@param    ppVersion  : [OUT]  MSIF_Version
 *@return : status
 *
 *@see
 */
INTERFACE BOOL MApp_Epg_GetLibVer(const MSIF_Version **ppVersion);
/* Version Control ****************************************************************************************/

/**
 *@brief  : EPG DB get max event numbers in epg db
 *@param    None
*@return : U32: max event numbers in epg db
 *
 *@see
 */
INTERFACE U32 MApp_EPGDB_GetMaxEventNumInDB(void);
INTERFACE U32 MApp_EPGDB_GetMaxExtNumInDB(void);
#if(MHEG5_SIINFO_ENABLE)
/**
 *@brief  :    get  event Info by TSID ONID Service_ID
 *@param:   u16TransportStream_ID : [IN]  event  u16TransportStream_ID
 *@param:   u16OriginalNetwork_ID  : [IN]  event OriginalNetwork_ID
 *@param:   u16Service_ID        :  [IN]  event u16Service_ID
 *@param    ePfStatus   : [IN] event Parent 0r Follow
 *@param    pEvent Info   : [OUT] event Info
 *@return : error status
 *
 *@see
 */
INTERFACE BOOLEAN MApp_EPG_GetEventInfo(U16 u16TransportStream_ID, U16 u16OriginalNetwork_ID, U16 u16Service_ID,MW_EN_EPG_PF_STATUS ePfStatus, MW_MHEG5_GET_EPG_EVENT_INFO *pstEventInfo);
/**
 *@brief  : get event category and  PF  CA Status by event index
 *@param    event                       : [IN]  event index
 *@param    pNibbleLevelPfCa   : [OUT] event category and  PF  CA
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_Epg_GetNibbleLevelOneAndTwoAndPFCA(EventIndex event,MW_MHEG5_EPG_GENRE_TYPE_PF_CA *pNibbleLevelPfCa);
/**
 *@brief  :    get event Parent Or Follow Index
 *@param:   u16TransportStream_ID : event  u16TransportStream_ID
 *@param:   u16OriginalNetwork_ID  : event OriginalNetwork_ID
 *@param:   u16Service_ID        :  event u16Service_ID
 *@param    pEvent                       : [IN]  event index
 *@param    ePfStatus   : [IN] event Parent 0r Follow
 *@return : error status
 *
 *@see
 */
INTERFACE MW_EN_EPG_FUNC_STATUS MApp_EPG_GetEventParentOrFollowIndex(U16 u16TransportStream_ID, U16 u16OriginalNetwork_ID, U16 u16Service_ID, EventIndex* pEvent,MW_EN_EPG_PF_STATUS ePfStatus);

#endif //#if(MHEG5_SIINFO_ENABLE)

#endif  //(ENABLE_DTV_EPG)

#undef INTERFACE
#endif /* MAPP_EPGDB_PUBLIC_H */

