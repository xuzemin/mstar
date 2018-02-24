#ifndef _MSAPI_ATSC_EPG_DB_H_
#define _MSAPI_ATSC_EPG_DB_H_


#include "Board.h"

#if( ENABLE_ATSC )

//===================================================================================

#if( ENABLE_ATSC_EPG_DB_2016 )
    #define MAX_CAPTION_SERVICE_NUMBER  8 // max caption service item number in CSD
#else
    #define MAX_CAPTION_SERVICE_NUMBER  16 // max caption service item number in CSD
#endif

// Default Event ID
#define INVALID_EVENT_ID                0x7FFF

#define ATSC_EPG_INVALID_RF_NUM         0xFFFF
#define ATSC_EPG_INVALID_SRC_ID         0xFFFF

#define ATSC_EPG_INVALID_EVENT_IDX      0xFFFF
#define ATSC_EPG_INVALID_ETT_IDX        0xFFFF

//------------------------------------------------------------------------------
#if(ATSC_EPG_ONLY_CUR_CHANNEL)  // One channel
    #define ATSC_EPG_VIR_CH_NUM         1
#else // Multi channel
    #define ATSC_EPG_VIR_CH_NUM         100
#endif

//===================================================================================

#define ATSC_EPGDB_PACK __attribute__ ((__packed__))

//--------------------------------------------------------------------------------------------------


typedef struct ATSC_EPGDB_PACK //__attribute__ ((__packed__))
{
    // U.S. Rating
    U8              fRatingRxIsOK       : 1;
    U8              u8MPAAFlag          : 1;    //
    U8              u8TVRatingForEntire : 3;    // rating_dimension [0]
    U8              fDialog             : 1;    // rating_dimension [1]
    U8              fLanguage           : 1;    // rating_dimension [2]
    U8              fSexualContent      : 1;    // rating_dimension [3]
    U8              fViolence           : 1;    // rating_dimension [4]
    U8              u8TVRatingForChild  : 2;    // rating_dimension [5]
    U8              fFantasyViolence    : 1;    // rating_dimension [6]
    U8              u8MPAARatingD2      ;       // rating_dimension [7]

    // Canadian Rating
    U8              u8CaEngFlag     : 1;    //
    U8              u8CaFreFlag         : 1;  //
    U8              u8CaEngRatingD0 : 3;    // rating_dimension [0]
    U8              u8CaFreRatingD1 : 3;    // rating_dimension [1]

    // Downloadable U.S. (50 states+ possessions) rating system
#if defined(ENABLE_PARSE_SAME_DIMENSION_IN_RRT5_CAD) && ENABLE_PARSE_SAME_DIMENSION_IN_RRT5_CAD
	U16						 u8DownloadableRatingD1;
	U16						 u8DownloadableRatingD2;
	U16						 u8DownloadableRatingD3;
	U16						 u8DownloadableRatingD4;
	U16						 u8DownloadableRatingD5;
	U16						 u8DownloadableRatingD6;
	U16						 u8DownloadableRatingD7;
	U16						 u8DownloadableRatingD8;
	U16						 u8DownloadableRatingD9;
	U16						 u8DownloadableRatingD10;

#if	(ENABLE_MAX_RRT_DIMENSION_NUMBER)
	U16						 u8DownloadableRatingD11;
	U16						 u8DownloadableRatingD12;
	U16						 u8DownloadableRatingD13;
	U16						 u8DownloadableRatingD14;
	U16						 u8DownloadableRatingD15;
	U16						 u8DownloadableRatingD16;
	U16						 u8DownloadableRatingD17;
	U16						 u8DownloadableRatingD18;
	U16						 u8DownloadableRatingD19;
	U16						 u8DownloadableRatingD20;
	U16						 u8DownloadableRatingD21;
	U16						 u8DownloadableRatingD22;
	U16						 u8DownloadableRatingD23;
	U16						 u8DownloadableRatingD24;
	U16						 u8DownloadableRatingD25;
	U16						 u8DownloadableRatingD26;
	U16						 u8DownloadableRatingD27;
	U16						 u8DownloadableRatingD28;
	U16						 u8DownloadableRatingD29;
	U16						 u8DownloadableRatingD30;
	U16						 u8DownloadableRatingD31;
	U16						 u8DownloadableRatingD32;
	U16						 u8DownloadableRatingD33;
	U16						 u8DownloadableRatingD34;
	U16						 u8DownloadableRatingD35;
	U16						 u8DownloadableRatingD36;
	U16						 u8DownloadableRatingD37;
	U16						 u8DownloadableRatingD38;
	U16						 u8DownloadableRatingD39;
	U16						 u8DownloadableRatingD40;
	U16						 u8DownloadableRatingD41;
#endif
#else
	U8						  u8DownloadableRatingD1 : 4;
	U8						  u8DownloadableRatingD2 : 4;
	U8						  u8DownloadableRatingD3 : 4;
	U8						  u8DownloadableRatingD4 : 4;
	U8						  u8DownloadableRatingD5 : 4;
	U8						  u8DownloadableRatingD6 : 4;
	U8						  u8DownloadableRatingD7 : 4;
	U8						  u8DownloadableRatingD8 : 4;
	U8						  u8DownloadableRatingD9 : 4;
	U8						  u8DownloadableRatingD10 : 4;
#endif
} MS_EPG_RATING;


typedef struct ATSC_EPGDB_PACK //__attribute__ ((__packed__))
{
    U8             au8Language[3];
    U8             bDigital_CC:1;
    U8             bLin21_field:1;
    U8             u8CaptionSrvNum:6;
    U8             bEasy_Reader:1;
    U8             bWide_aspect_ratio:1;
    U8             Reserved:6;
} MS_EPG_Caption_Service_Item;


typedef struct ATSC_EPGDB_PACK
{
    U8             u8NumOfService;
    MS_EPG_Caption_Service_Item     stCaptionServiceItem[MAX_CAPTION_SERVICE_NUMBER];
} MS_EPG_Caption_Service;

//===================================================================================

#if( ENABLE_ATSC_EPG_DB_2016 )

// ENABLE_MAX_RRT_DIMENSION_NUMBER=1                                        ==>  sizeof(MS_EPG_RATING)=86
// ENABLE_MAX_RRT_DIMENSION_NUMBER=0 (only 10 dimensions ) ==>  sizeof(MS_EPG_RATING)=24

// MAX_CAPTION_SERVICE_NUMBER = 16  ==> sizeof(MS_EPG_Caption_Service)=84
// MAX_CAPTION_SERVICE_NUMBER = 8  ==> sizeof(MS_EPG_Caption_Service)=41

//sizeof(MS_EPG_EVENT)=184 ==> 79
//sizeof(MS_EPG_EVENT_new)= 667

#define ATSC_EPG_TITLE_DATA_SIZE    80

typedef struct ATSC_EPGDB_PACK // __attribute__ ((__packed__))
{
    U32     start_time;

    U16     u16SrcId;
    U16     u16DbEttIdx;  // offset of event extented text in sdram database

    U16     event_id            : 15;
    U16     fHasCCInfo          : 1;

    //U8      length[3];
    U32     u32TimeLen          : 20;

    U8      fIsEitUTF16         : 1;
    //U8      fIsEttUTF16         : 1;
    //U8      Reserved             :6;

    //U16             u16DbTitlePos;      // offset of event title in sdram database
    U8  u8TitleLen;
    U8  au8Title[ATSC_EPG_TITLE_DATA_SIZE];

    U8 u8RfNum;
    U8 u8EitTblNumber;

    MS_EPG_RATING   stRating;
    MS_EPG_Caption_Service    stCaptionService;
} MS_EPG_EVENT_New;

#define ATSC_EPG_ETT_DATA_SIZE   512

typedef struct ATSC_EPGDB_PACK
{
    U16  u16EttDataLen : 10;
    U16  bIsEttUTF16   : 1 ;

    U8   au8EttData[ATSC_EPG_ETT_DATA_SIZE];
} MS_EPG_EVENT_ETT_New;

//------------------------------------------------------------------------------------------------------------

void msAPI_AtscEpgDb_Init(void);
void msAPI_AtscEpgDb_ResetDB(void);

void msAPI_AtscEpgDb_Set_DebugMode(U8 u8DebugMode);

// If successful, return EventIdx
U16 msAPI_AtscEpgDb_Get_EmptyEventIdx(void);

BOOLEAN msAPI_AtscEpgDb_Is_EventValid(U16 u16EvtIdx );

BOOLEAN msAPI_AtscEpgDb_Set_Event(U16 u16EvtIdx, const MS_EPG_EVENT_New* pstMS_EPG_EVENT_New);
BOOLEAN msAPI_AtscEpgDb_Get_Event(U16 u16EvtIdx, MS_EPG_EVENT_New* pstMS_EPG_EVENT_New);
const MS_EPG_EVENT_New* msAPI_AtscEpgDb_Get_Event_Pointer(U16 u16EvtIdx);

BOOLEAN msAPI_AtscEpgDb_Add_Event(const MS_EPG_EVENT_New* pstMS_EPG_EVENT_New);

BOOLEAN msAPI_AtscEpgDb_Delete_Event(U16 u16EvtIdx);
U16 msAPI_AtscEpgDb_Delete_Event_By_RfNum(U8 u8RfNum);


U16 msAPI_AtscEpgDb_Get_MaxEventNum(void);
U16 msAPI_AtscEpgDb_Get_EventNum(void);

U16 msAPI_AtscEpgDb_Get_Event_By_CH_EventId_Time(const MS_EPG_EVENT_New* pstMS_EPG_EVENT_New);
U16 msAPI_AtscEpgDb_Get_Event_By_CH_EventId(const MS_EPG_EVENT_New* pstMS_EPG_EVENT_New);

U16 msAPI_AtscEpgDb_Get_EventList_Idx(U8 u8RfNum, U16 u16SrcId, U32 u32StartTime, U32 u32EndTime, U16 au16EventList[], U16 u16EventListMaxNum );
U16 msAPI_AtscEpgDb_Get_EventList_Ref(U8 u8RfNum, U16 u16SrcId, U32 u32StartTime, U32 u32EndTime, MS_EPG_EVENT_New* apstEventList[], U16 u16EventListMaxNum );


BOOLEAN msAPI_AtscEpgDb_Get_EventNum_BySrcId(U8 u8RfNum, U16 u16SrcId);

//-----------------------------------------------------------------------------------------------

U32 msAPI_AtscEpgDb_Get_EventTimeLen( const MS_EPG_EVENT_New* pstEPG_EVENT_New);
U32 msAPI_AtscEpgDb_Get_EventTimeEnd( const MS_EPG_EVENT_New* pstEPG_EVENT_New);

//-----------------------------------------------------------------------------------------------


// If successful, return EttIdx
U16 msAPI_AtscEpgDb_Get_EmptyEttIdx(void);

BOOLEAN msAPI_AtscEpgDb_Set_Ett(U16 u16EttIdx, MS_EPG_EVENT_ETT_New* pstMS_EPG_EVENT_ETT_New);
BOOLEAN msAPI_AtscEpgDb_Get_Ett(U16 u16EttIdx, MS_EPG_EVENT_ETT_New* pstMS_EPG_EVENT_ETT_New);
BOOLEAN msAPI_AtscEpgDb_Delete_Ett(U16 u16EttIdx);

U16 msAPI_AtscEpgDb_Set_EttData(MS_EPG_EVENT_ETT_New* pstMS_EPG_EVENT_ETT_New, U8* au8DataBuf, U16 u16DataLen);


void msAPI_AtscEpgDb_PrintTime(U32 u32DtvTime);
void msAPI_AtscEpgDb_PrintEventTitle(const U8* pu8Title, U16 u16MaxLen, BOOLEAN bIsUTF16);
U8 msAPI_AtscEpgDb_Get_EventTitle( const MS_EPG_EVENT_New* pstEPG_EVENT_New, U8* pu8TitleBuf, U8 u8TitleBufLen);


void msAPI_AtscEpgDb_PrintEvents(U16 u16MaxPrintNum);
void msAPI_AtscEpgDb_PrintAllEtt(void);
void msAPI_AtscEpgDb_PrintAllDb(void);

//===================================================================================

#endif // ENABLE_ATSC_EPG_DB_2016

#endif // ENABLE_ATSC

#endif // _MSAPI_ATSC_EPG_DB_H_

